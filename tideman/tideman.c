#include <stdio.h>
#include <string.h>
#define SIZE 20
// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
int locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
char candidates[SIZE][MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
int vote(int rank, char name[], int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
void create_strength_array(int strength[]);
void sort(int array[], int start, int end);
void merge(int array[], int start, int middle, int end);
void print_array(int array[], int n);
int check_cycle(int winner, int loser);

int main(int argc, char* argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        strcpy(candidates[i], argv[i + 1]);
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = 1;
        }
    }

    pair_count = 0;
    int voter_count;
    printf("Number of voters: ");
    scanf("%d", &voter_count);

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            fflush(stdin);
            char name[SIZE];
            printf("Rank %d: ", j + 1);
            gets(name);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
int vote(int rank, char name[], int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (!strcmp(name, candidates[i]))
        {
            ranks[rank] = i;
            return 1;
        }
    }
    return 0;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    int rank1 = 0;
    int rank2 = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            rank1 = ranks[i];
            rank2 = ranks[j];
            if (rank1 != rank2)
            {
                preferences[rank1][rank2]++;
            }
            else
            {
                preferences[rank1][rank2] = 0;
            }
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            int comparison1 = preferences[i][j];
            int comparison2 = preferences[j][i];
            if (comparison1 > comparison2)
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (comparison1 < comparison2)
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int strength_array[pair_count];
    create_strength_array(strength_array);
    sort(strength_array, 0, pair_count - 1);
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    int winner;
    int loser;
    for (int i = 0; i < pair_count; i++)
    {
        winner = pairs[i].winner;
        loser = pairs[i].loser;
        if (!check_cycle(winner, loser))
        {
            locked[winner][loser] = 1;
        }
    }
}

// Print the winner of the election
void print_winner(void)
{
    int i = 0;
    int j = 0;
    int edge;
    while (i < candidate_count)
    {
        edge = locked[j][i];
        if (j == candidate_count && !edge)
        {
            printf("%s\n", candidates[i]);
            break;
        }
        else if (!edge)
        {
            j++;
        }
        else
        {
            i++;
            j = 0;
        }
    }
}

void create_strength_array(int strength[])
{
    int winner;
    int loser;
    for (int i = 0; i < pair_count; i++)
    {
        winner = pairs[i].winner;
        loser = pairs[i].loser;
        strength[i] = preferences[winner][loser] - preferences[loser][winner];
    }
}

void sort(int array[], int start, int end)
{
    if (end > start)
    {
        int middle = (start + end) / 2;
        sort(array, start, middle);
        sort(array, middle + 1, end);

        merge(array, start, middle, end);
    }
}

void merge(int array[], int start, int middle, int end)
{
    int i = start;
    int j = middle + 1;
    int k = 0;

    typedef struct
    {
        int winner;
        int loser;
    } pair_temp;

    pair_temp pairs_temp[pair_count];

    while (i <= middle && j <= end)
    {
        if (array[i] >= array[j])
        {
            pairs_temp[k].winner = pairs[i].winner;
            pairs_temp[k].loser = pairs[i].loser;
            i++;
            k++;
        }
        else
        {
            pairs_temp[k].winner = pairs[j].winner;
            pairs_temp[k].loser = pairs[j].loser;
            j++;
            k++;
        }
    }

    while (i <= middle)
    {
        pairs_temp[k].winner = pairs[i].winner;
        pairs_temp[k].loser = pairs[i].loser;
        i++;
        k++;
    }

    while (j <= end)
    {
        pairs_temp[k].winner = pairs[j].winner;
        pairs_temp[k].loser = pairs[j].loser;
        j++;
        k++;
    }

    for (i = start; i <= end; i++)
    {
        pairs[i].winner = pairs_temp[i - start].winner;
        pairs[i].loser = pairs_temp[i - start].loser;
    }
}

void print_array(int array[], int n)
{
    for (int i = 0; i <= n; i++)
    {
        printf("%i", array[i]);
    }
    printf("\n");
}

int check_cycle(int winner, int loser)
{
    if (locked[loser][winner])
    {
        return 1;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[i][winner])
        {
            return check_cycle(i, loser);
        }
    }
    return 0;
}