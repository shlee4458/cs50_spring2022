# TODO
from cs50 import get_int


while True:
    h = get_int("height :")
    if h < 9 and h > 0:
        break

for i in range(0, h):
    for j in range(0, h-i-1):
        print(" ", end="")
    print("#" * (i+1))
