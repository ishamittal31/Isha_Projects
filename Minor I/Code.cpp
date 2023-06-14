#include <stdio.h>

char grid (int i)
{
    switch(i)
    {
        case -1:
            return 'X';
        case 0:
            return ' ';
        case 1:
            return 'O';
    }
}


void drawGrid (int b[9])
{
    printf (" %c | %c | %c\n", grid(b[1]), grid(b[2]), grid(b[3]));
    printf ("---+---+---\n");
    printf (" %c | %c | %c\n", grid(b[4]), grid(b[5]), grid(b[6]));
    printf ("---+---+---\n");
    printf (" %c | %c | %c\n", grid(b[7]), grid(b[8]), grid(b[9]));
}


int winSituation (int bd[10])
{
    //This function returns 0 when the player winnings the game
    unsigned winnings[9][3] = {{1,2,3},{4,5,6},{7,8,9},{1,4,7},{2,5,8},{3,6,9},{1,5,9},{3,5,7}};
    for (int i = 1; i < 9; i++)
    {
        if (bd[winnings[i][0]] != 0 &&
           bd[winnings[i][0]] == bd[winnings[i][1]] &&
           bd[winnings[i][1]] == bd[winnings[i][2]])
            return bd[winnings[i][2]];
    }
    return 0;
}


int minimax (int bd[10], int player)
{
    //Minimax algo is used which helps the player to find the optimal move
    int winner = winSituation(bd);
    if (winner != 0)
        return winner*player; // -1*-1 or 1*1
    int move = -1;
    int score = -2; // Losing move is better than no move
    for (int i = 1; i < 10; i++)  
    {
        if (bd[i] == 0) // To check if move is possible
        {
            bd[i] = player; // Trying the move
            int tempScore = - minimax (bd, player*-1);
            // To count negative score for the opponent
            if (tempScore > score)
            {
                score = tempScore;
                move = i ;
             } // To choose the worst move for the opponent
            bd[i] = 0; // To reset after every try
        }
    }
    if (move == -1)
         return 0; // No more move it’s a tie
    return score;
}


void moveByComputer (int bd[10])
{
    int move = -1;
    int score = -2;
    for (int i = 1; i < 10; i++)
    {
        if(bd[i] == 0)
        {
            bd[i] = 1;
            int tempScore = - minimax (bd, -1);
            bd[i] = 0;
            if (tempScore > score)
            {
                score = tempScore;
                move = i;
            }
        }
     }
     bd[move] = 1;
}


void moveByPlayer (int bd[10])
{
    int move = 1;
    do {
          start:
          printf ("\n Enter the move ([1...9]): ");
          scanf ("%d", &move);
          if(bd[move] != 0)
          {
              printf ("This block is already occupied !");
              goto start;
          }
          printf("\n");
      } while (move >= 10 || move < 1 && bd[move] == 0);
      bd[move] = -1;
  }


int main ()
{
    int bd[10] = {0,0,0,0,0,0,0,0,0};
    //computer (1) O, player (-1) X.
    printf (" Computer: O, You: X \n Play (1)st or (2)nd? ");
    int player=0;
    scanf ("%d", &player);
    printf ("\n");
    unsigned turn;
    for (turn = 0; turn < 9 && winSituation(bd) == 0; turn++)
    {
        if ((turn+player) % 2 == 0)
        {
            moveByComputer(bd);
        }
        else
        {
            drawGrid(bd);
            moveByPlayer(bd);
         }
    }
    switch(winSituation(bd))
    {
        case 0:
            printf("It is a tie. Play again. \n");
            break;
        case 1:
            drawGrid(bd);
            printf("You lost the game. Better luck next time. \n");
            break;
        case -1:
            printf("You won the game. Congrats!! \n");
            break;
    }
}
