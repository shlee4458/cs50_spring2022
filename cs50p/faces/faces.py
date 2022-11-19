def convert(userInput):
    return userInput.replace(":)","🙂").replace(":(","🙁")


def main():
    userInput = input("Input: ")
    print(convert(userInput))

main()