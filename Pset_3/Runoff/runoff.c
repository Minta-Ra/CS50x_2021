#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

//////////////////////////////////////////////////////////////////////////

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // TODO
    // IF THIS PERSON EXIST
    for (int n = 0; n < candidate_count; n++)
    {
        if (strcmp(candidates[n].name, name) == 0)
        {
            preferences[voter][rank] = n;
            return true;
        }
    }
    return false;
}

//////////////////////////////////////////////////////////////////////////

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // TODO
    // LOOP THROUGH VOTERS
    for (int n = 0; n < voter_count; n++)
    {
        int rank = 0;
        bool lookingToAddVote = true;
        while (lookingToAddVote)
        {
            // CHECK VOTER'S PREFERENCE
            int choice = preferences[n][rank];
            // IF NOT ELIMINATED ADD VOTE
            if (!candidates[choice].eliminated)
            {
                candidates[choice].votes++;
                lookingToAddVote = false;
            }
            else
            {
                // IF ELIMINATED CHECK NEXT PREFERENCE
                rank++;
            }
        }
    }
    return;
}

//////////////////////////////////////////////////////////////////////////

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // TODO
    // LOOP THROUGH CANDIDATES
    for (int m = 0; m < candidate_count; m++)
    {
        // FIND THE CANDIDATE WITH MORE THAN HALF VOTES
        if (candidates[m].votes > (voter_count / 2))
        {
            // PRINT THE WINNER
            printf("%s\n", candidates[m].name);
            return true;
        }
    }
    return false;
}

//////////////////////////////////////////////////////////////////////////

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // TODO
    // RETURN MIN NUMBER OF VOTES WHO ARE STILL IN THE ELECTION
    int min = 90; // THIS IS THE HIGH NUMBER SO THE MINIMUM WILL ALWAYS GO DOWN AFTER THE FIRST ITERATION

    // LOOP THROUGH CANDIDATES
    for (int l = 0; l < candidate_count; l++)
    {
        if (!candidates[l].eliminated && candidates[l].votes < min)
        {
            min = candidates[l].votes;
        }
    }
    return min;
}

//////////////////////////////////////////////////////////////////////////

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    bool tie = true;

    for (int p = 0; p < candidate_count; p++)
    {
        if ((!candidates[p].eliminated) && candidates[p].votes != min)
        {
            tie = false;
        }
    }

    return tie;
}

//////////////////////////////////////////////////////////////////////////

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // TODO
    for (int z = 0; z < candidate_count; z++)
    {
        if (candidates[z].votes == min)
        {
            candidates[z].eliminated = true;
        }
    }
    return;
}