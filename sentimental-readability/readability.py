from cs50 import get_string

# TODO
text = get_string("Input: ")


# count number of letters
letters = 0
for c in text:
    if c.isalpha():
        letters += 1
    else:
        continue
print(f"{letters}")

# count number of words
words = 1
for c in text:
    if c == " ":
        words += 1
    else:
        continue

print(f"{words}")

# count number of sentences
sentences = 0
for c in text:
    if c in [".", "?", "!"]:
        sentences += 1
    else:
        continue

print(f"{sentences}")

# CC formula

L = letters/words*100
S = sentences/words*100

CLI = 0.0588 * L - 0.296 * S - 15.8

if CLI >= 16:
    print("Grade 16+")
elif CLI < 1:
    print("Before Grade 1")
else:
    print(f"Grade {round(CLI)}")

# print the grade
