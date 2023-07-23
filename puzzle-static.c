/*

Author  : M.F.M. FASEEH (E/19/106)
        : M.H.M. FAHMAN (E/19/105)

Topic   : CO222 PROJECT

Group   : GROUP 25

*/

#include <stdio.h>
#include <string.h>
#include<stdlib.h>

// Define...
#define MAX_WORDS 1000
#define MAX_WORD_LEN 1000
#define MAX_GRID_ROWS 1000
#define MAX_GRID_COLS 1000
#define SIZE 1000

// Functions declarations....

int fits_horizontally(char word[], int row, int col);
int fits_vertically(char word[], int row, int col);
void fill_horizontally(char word[], int row, int col);
void fill_vertically(char word[], int row, int col) ;

// variable declaration...
char grid[MAX_GRID_ROWS][MAX_GRID_COLS];
char words[MAX_WORDS][MAX_WORD_LEN];
int word_length_list[MAX_WORDS];

int grid_rows;
int grid_cols;
int words_count;


int main()
{
    int row_count=0;
    char temp;

    // Get grid input from user.
    while(scanf("%[^\n]%*c",grid[row_count]) == 1)
    {
        row_count++;
    }

    scanf("%c",&temp); // scan a empty line input.

    // Get words from.
    int count_word=0;
    while(scanf("%[^\n]%*c",words[count_word]) == 1)
    {
        count_word++;
    }

    words_count = count_word;       // Number of words user input to Fill the spaces.

    grid_cols = strlen(grid[0]);    // Find the number of columns of grid
    grid_rows = row_count;          // Find the number of Rows of grid



    // store each word length in an array.
    int r;
    for(r=0; r< words_count; r++)
    {
        word_length_list[r]= strlen(words[r]);
    }

// Invalid Input check......................

    // check the lengths
    for (int i=0; i< grid_rows-1; i++)
    {

        if (sizeof(grid[i]) == sizeof(grid[i+1]))
        {
            continue;
        }
        else
        {
            printf("INVALID INPUT");
            return 0;
        }
    }

    // check whether grid inputs are correct or not.
    for (int i=0; i< grid_rows; i++)
    {
        for (int j=0; j< grid_cols; j++)
        {
            if (grid[i][j] == '#' || grid[i][j] == '*' || (grid[i][j] >= 'A' && grid[i][j] <= 'Z') || (grid[i][j] >= 'a' && grid[i][j] <= 'z'))
            {
                continue;
            }
            else
            {
                printf("INVALID INPUT");
                return 0;
            }
        }
    }

      // check whether word inputs are correct or not.

    for (int i=0; i< words_count; i++)
    {
        for (int j=0; j< word_length_list[i]; j++)
        {
            if ((words[i][j] >= 'A' && words[i][j] <= 'Z') || (words[i][j] >= 'a' && words[i][j] <= 'z'))
            {
                continue;
            }
            else
            {
                printf("INVALID INPUT");
                return 0;
            }
        }
    }

// Try to fit the words into the grid..............

    // copy the grid.
    char Fixed_grid[SIZE][SIZE];
    for (int i=0; i< grid_rows; i++){
        strcpy(Fixed_grid[i],grid[i]);
    }


        for (int i=0; i< words_count; i++)
    {
        strcpy(words[words_count+i], words[i]);
    }


    int times =0, j=0, k=0, counted_words;
    counted_words = words_count;

    while(j < counted_words)
    {
        int placed = 0;
        for (int row = 0; row < grid_rows && !placed; row++)
        {
            for (int col = 0; col < grid_cols && !placed; col++)
            {
                if (fits_horizontally(words[times+k], row, col))
                {
                    fill_horizontally(words[times+k], row, col); //Fill Horizonal Mached word.
                    placed = 1;
                }

                else if (fits_vertically(words[times+k], row, col))
                {
                    fill_vertically(words[times+k], row, col);  //Fill Horizonal Mached word.
                    placed = 1;
                }
            }
        }

        if (!placed && (times<words_count))
        {
            times++;
            counted_words++;
            j=times;
            k=0;

            // To Get input grid again.
            for (int i=0; i< grid_rows; i++){
            strcpy(grid[i],Fixed_grid[i]);
            }

            continue;
        }

        if (!placed)
        {
            printf("IMPOSSIBLE\n"); // Print imposible if unable to fit into the grid.
            return 0;
        }

        j++;
        k++;
    }


   // Print the solved puzzle
    for (int row = 0; row < grid_rows; row++) {
        for (int col = 0; col < grid_cols; col++) {
            printf("%c", grid[row][col]);
        }
        printf("\n");
    }

    return 0;
}



// Check if the word fits horizontally in the grid at the given position
int fits_horizontally(char word[], int row, int col) {
    int word_len = strlen(word);
    if (col + word_len > grid_cols) {
        return 0;
    }

    if (grid[row][col+word_len] == '#'){
        return 0;
    }

    for (int i = 0; i < word_len; i++) {
        if (grid[row][col + i] != '#' && grid[row][col + i] != word[i]) {
            return 0;
        }
    }

    return 1;   // Return 1 if can fit horizonally into the grid.
}


// Check if the word fits vertically in the grid at the given position
int fits_vertically(char word[], int row, int col) {
    int word_len = strlen(word);
    if (row + word_len > grid_rows) {
        return 0;
    }

    if (grid[row+word_len][col] == '#'){
    return 0;
    }

     for (int i = 0; i < word_len; i++) {
        if (grid[row + i][col] != '#' && grid[row + i][col] != word[i]) {
            return 0;
        }
    }



    return 1;   // Return 1 if can fit vertically into the grid.
}

// Fill in the word horizontally in the grid at the given position
void fill_horizontally(char word[], int row, int col) {
    int word_len = strlen(word);
    for (int i = 0; i < word_len; i++) {
        grid[row][col + i] = word[i];
    }
}

// Fill in the word vertically in the grid at the given position
void fill_vertically(char word[], int row, int col) {
    int word_len = strlen(word);
    for (int i = 0; i < word_len; i++) {
        grid[row + i][col] = word[i];
    }
}
