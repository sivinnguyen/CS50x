#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);
void sortByName(candidate candi[], int count);
int greatest(candidate candi[], int count);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }

    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // Sort candidates alphabetically
    sortByName(candidates, candidate_count);

    // Get greatest number of votes
    int g = greatest(candidates, candidate_count);

    // Print out the winner(s)
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == g)
        {
            printf("%s\n", candidates[i].name);
        }
    }
}

// Sort candidates by name
void sortByName(candidate candi[], int count)
{
    candidate temp;

    for (int i = 0; i < count - 1; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            if (strcmp(candi[i].name, candi[j].name) > 0)
            {
                temp.name = candi[i].name;
                candi[i].name = candi[j].name;
                candi[j].name = temp.name;

                temp.votes = candi[i].votes;
                candi[i].votes = candi[j].votes;
                candi[j].votes = temp.votes;
            }
        }
    }
}

// Find greatest vote
int greatest(candidate candi[], int count)
{
    int g = 0;

    for (int i = 0; i < count; i++)
    {
        if (g < candi[i].votes)
        {
            g = candi[i].votes;
        }
    }

    return g;
}

