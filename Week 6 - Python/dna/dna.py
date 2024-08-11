import csv
import sys


def main():
    # Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py database sequence")

    # Read database file into a variable
    db = []
    with open(sys.argv[1], "r") as d:
        reader = csv.reader(d)
        for row in reader:
            db.append(row)

    # get shape of db
    columns = len(db)
    rows = len(db[0])

    # turn STR counts from string  to int
    for c in range(1, columns):
        for r in range(1, rows):
            db[c][r] = int(db[c][r])

    # Read DNA sequence file into a variable
    with open(sys.argv[2], "r") as s:
        seq = s.read()

    # Find longest match of each STR in DNA sequence
    STRs = db[0][1:]
    STRs_count = []
    for i in range(len(STRs)):
        STRs_count.append(longest_match(seq, STRs[i]))

    # Check database for matching profiles
    for c in range(1, columns):
        if STRs_count == db[c][1:]:
            print(db[c][0])

            return 0

    print("No match")

    return 0


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
