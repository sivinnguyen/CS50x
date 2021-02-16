from sys import argv, exit
import csv


def main():
    if len(argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        exit(1)

    # argv[0] is the name of program (dna.py)
    db_path = argv[1]
    seq_path = argv[2]

    # load database from file to memory
    with open(db_path, newline='') as csvfile:
        #database = list(DictReader(csvfile))
        database = csv.reader(csvfile)
        for row in database:
            print(row)


    exit(0)


main()