import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import date

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd
app.jinja_env.globals.update(usd=usd)

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    id = session["user_id"]

    # select list of stocks owned
    stocks = db.execute(
        "SELECT symbol, SUM(share) AS total_shares FROM history GROUP BY symbol HAVING id=?", id)
    agg_list = list()
    total_stock_value = 0
    for stock in stocks:
        agg_dict = dict()
        current_info = lookup(stock["symbol"])
        agg_dict["symbol"] = stock["symbol"]
        agg_dict["name"] = current_info["name"]
        agg_dict["price"] = current_info["price"]
        agg_dict["share"] = stock["total_shares"]
        agg_dict["total"] = agg_dict["price"] * agg_dict["share"]
        total_stock_value += agg_dict["total"]
        agg_list.append(agg_dict)

    # assign cash
    cash = db.execute("SELECT cash FROM users WHERE id = ?", id)

    # current data

    """Show portfolio of stocks"""
    return render_template("index.html", agg_list=agg_list, total_stock_value=total_stock_value, cash=cash)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():

    if request.method == "POST":

        # Define variables
        symbol = request.form.get("symbol").upper()
        share = request.form.get("shares")
        cash = db.execute(
            "SELECT cash FROM users WHERE id = ?", session["user_id"])

        today = date.today()

        time = today.strftime("%m/%d/%Y")

        # fractional share
        if not share.isdigit():
            return apology("Enter full number")

        share = int(share)

        # validate symbol
        if not lookup(symbol):
            return apology("Symbol does not exist", 400)

        stock_info = lookup(symbol)
        price = stock_info["price"]

        # validate shares
        if share < 1:
            return apology("Input positive number of shares", 400)

        # validate amount of money
        if cash[0]["cash"] < (share * price):
            return apology("You don`t have enough cash", 400)

        # update cash
        db.execute("UPDATE users SET cash = cash - ? WHERE id = ?",
                   share*price, session["user_id"])

        # record in the history db
        db.execute("INSERT INTO history (id, symbol, share, price, date, ts) VALUES (?,?,?,?,?,?)",
                   session["user_id"], symbol, share, price, time, "BUY")

        return render_template("success.html")

    else:
        return render_template("buy.html")

    """Buy shares of stock"""


@app.route("/history")
@login_required
def history():
    id = session["user_id"]

    # select list of stocks owned
    stocks = db.execute(
        "SELECT * FROM history WHERE id=?", id)

    """Show history of transactions"""
    return render_template("history.html", stocks=stocks)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?",
                          request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":

        # define input
        symbol = request.form.get("symbol")

        # input in the lookup function
        # if none value, return apology
        symbol_info = lookup(symbol)
        if not symbol_info:
            return apology("Symbol does not exist")

        # render quoted
        return render_template("quoted.html", symbol_info=symbol_info)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():

    username = request.form.get("username")
    password = request.form.get("password")
    confirmation = request.form.get("confirmation")

    if request.method == "POST":

        # check duplicate
        existing_username = db.execute(
            "SELECT * FROM users WHERE username = ?", username)
        if len(existing_username) > 0:
            return apology("Duplicate Username")

        # if not duplicate add to the database

        db.execute("INSERT INTO users (username, hash) VALUES (?,?)",
                   username, generate_password_hash(password))

        if confirmation != password:
            return apology("Password does not match confirmation")

        if len(username) == 0:
            return apology("Input ID")

        return render_template("success.html")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    if request.method == "POST":

        # define var of stocks that session["user_id"] owns
        symbol = request.form.get("symbol").upper()
        share = int(request.form.get("share"))
        price = lookup(symbol)["price"]

        # date var
        today = date.today()
        time = today.strftime("%m/%d/%Y")

        # pull data from sql
        stocks = db.execute(
            "SELECT symbol, SUM(share) AS share FROM history GROUP BY symbol HAVING id = ?", session["user_id"])
        own = False

        # symbol does not exist:
        if not lookup(symbol):
            return apology("Please check the symbol again")

        # return apology if you don`t own enough stocks
        for stock in stocks:
            if symbol == stock["symbol"]:
                own = True
                if share > stock["share"] or share < 1:
                    return apology("You don`t have enough stocks")

        # return apology if the symbol does not exist
        if own == False:
            return apology("Please check the symbol again")

        # update history
        db.execute("INSERT INTO history (id, symbol, share, price, date, ts) VALUES(?,?,?,?,?,?)",
                   session["user_id"], symbol, -share, price, time, "SELL")

        # update cash
        db.execute("UPDATE users SET cash = cash + ? WHERE id = ?",
                   share * price, session["user_id"])

        return render_template("success.html")

    else:
        return render_template("sell.html")

        #
    """Sell shares of stock"""
