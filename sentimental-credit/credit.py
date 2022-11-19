from cs50 import get_string, get_int


# TODO
def main():
    is_c = list()

    # take input of the credit card num
    ccm = get_string("Number: ")

    # len ->  AMEX =  15, MASTER = 16,  VISA = 13 OR 16
    if len(ccm) == 15:
        is_c.append(1)
    elif len(ccm) == 16:
        is_c.append(2)
    elif len(ccm) == 13 or len(ccm) == 16:
        is_c.append(3)

    # first num  AMEX = 34 OR 37,  MASTER = 51/52/53/54/55, VISA = 4
    if ccm[0:2] == "34" or ccm[0:2] == "37":
        is_c.append(1)
    elif ccm[0:2] in ["51", "52", "53", "54", "55"]:
        is_c.append(2)
    elif ccm[0] == "4":
        is_c.append(3)

    # checksum
    # multiply 2 every other digit
    # add every digit
    # sum added digit and all other digits that weren`t added
    # % 10 == 0
    multiplied = 0
    sum = 0
    for i in range(1, len(ccm)+1):
        # if i is even number, multiply two and if it is 2 digits add %
        if i % 2 == 0:
            multiplied = int(ccm[-i])*2
            if multiplied - 10 >= 0:
                sum += 1 + multiplied % 10
            else:
                sum += multiplied
        # if i is an odd number, just add to the sum
        else:
            sum += int(ccm[-i])

    print(f"sum : {sum}")

    if sum % 10 == 0:
        is_c.append(1)

    print(f"is_C: {is_c}")

    # output
    if is_c == [1, 1, 1]:
        print("AMEX")
    elif is_c == [2, 2, 1]:
        print("MASTERCARD")
    elif is_c == [2, 3, 1]:
        print("VISA")
    elif is_c == [3, 3, 1]:
        print("VISA")
    else:
        print("INVALID")

    return


main()
