/**
 * fifteen.c
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */

#define _XOPEN_SOURCE 500

/**
 * fifteen.c
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */

#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);
void swapping (int tile);
// definition of data types
int tile_i;
int tile_j;
int zero_i;
int zero_j;

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = get_int();

        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }

    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).
 */
void init(void)
{
    int n = (d*d)-1;
    for (int i = 0; i < d; i++)
        for (int j = 0; j < d; j++)
        {
            board [i][j] = n;
            n--;
        }
    if ((d*d - 1) % 2 != 0)
    {
        int temp = board[d-1][d-3];
        board[d-1][d-3] = board [d-1][d-2];
        board[d-1][d-2] = temp;
    }
    zero_i = d-1;
    zero_j = d-1;
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                if (board [i][j] == 0)
                    {
                    printf (" _\t");
                    }
                else
                {
                    printf ("%2i\t", board [i][j]);
                }
            }
            printf ("\n");
        }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false.
 */
bool move(int tile)
{
    if (tile > (d*d - 1) || tile < 1)
    return false;

    //SEARCH of tile
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if (board [i][j] == tile)
            {
                tile_i = i;
                tile_j = j;
            }
        }
    }
    //CHECKING for tile borders empty space
    //TOP
    if ( ((tile_i - 1) >= 0) && board[tile_i - 1][tile_j] == 0)
    {
        swapping (tile);
        return true;
    }
    //BOTTOM
    else if ( ((tile_i + 1) <= d - 1) && board[tile_i + 1][tile_j] == 0)
    {
        swapping (tile);
        return true;
    }
    //LEFT
    else if ( ((tile_j - 1) >= 0) && board[tile_i][tile_j - 1] == 0)
    {
        swapping (tile);
        return true;
    }
    //RIGHT
    else if ( ((tile_j + 1) <= d - 1) && board[tile_i][tile_j + 1] == 0)
    {
        swapping (tile);
        return true;
    }
    else return false;

return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration),
 * else false.
 */
bool won(void)
{
    int count = 1;
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if (board [i][j] == count)
            {
                count ++;
            }
        }
    }
    if (count == d*d && board [d-1][d-1] == 0 )
    {
        return true;
    }
    else
    {
        return false;
    }
}

void swapping (tile)
{
    int temp = board[tile_i][tile_j];
    board[tile_i][tile_j] = board[zero_i][zero_j];
    board[zero_i][zero_j] = temp;
    //NEW PLACE for BLANK TILE;
    zero_i = tile_i;
    zero_j = tile_j;
}
