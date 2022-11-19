from cs50 import get_float


# TODO
# take the input as float
while True:
    change = get_float("Change owed: ")
    if change > 0:
        break

# change owed in cents
change_c = change * 100

# number of quarters
quarters = int(change_c / 25)
print(f"{quarters}")
change_c = change_c - quarters * 25

# number of dimes
dimes = int(change_c / 10)
print(f"{dimes}")
change_c = change_c - dimes * 10

# number of nickels
nickels = int(change_c / 5)
change_c = change_c - nickels * 5
print(f"{nickels}")

# number of cents
cents = int(change_c / 1)
print(f"{cents}")

coins = quarters + dimes + nickels + cents

print(f"{coins}")
