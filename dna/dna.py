import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) == 4:
        print("Right format: python3 filename.py database_filename.csv DNAsequence_filename.csv")
        return 1

    # TODO: Read database file into a variable
    with open(sys.argv[1], "r") as db:
        database = csv.DictReader(db)
        db_list = list(database)

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2], "r") as dnas:
        dna_sequence = dnas.read()

    # TODO: Find longest match of each STR in DNA sequence
    # save list of column names into a variable
    keys_db = dict()
    keys_db_list = list()

    for key in db_list[0].keys():
        keys_db[key] = 0
        keys_db_list.append(key)
    keys_db_list.pop(0)

    for subsequence in keys_db_list:
        keys_db[subsequence] = longest_match(dna_sequence, subsequence)

    # TODO: Check database for matching profiles
    matches = 0

    for idx in range(0, len(db_list)):
        for keys in keys_db_list:
            if int(keys_db[keys]) == int(db_list[idx][keys]):
                matches += 1
        if matches == len(keys_db_list):
            name = db_list[idx]['name']
            keys_db['name'] = name
            break

        matches = 0

    if str(keys_db['name']) != "0":
        print(f"{keys_db['name']}")
    else:
        print("No match")

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
