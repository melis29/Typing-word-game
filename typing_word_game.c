#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

struct words
{
   char word[7];
};

int mix(struct words * array);
int play(struct words * phrase);

int main(int argc, char ** argv)
{
   struct words phrase[9];

   strncpy(phrase[0].word, "The", 7);
   strncpy(phrase[1].word, "quick", 7);
   strncpy(phrase[2].word, "brown", 7);
   strncpy(phrase[3].word, "fox", 7);
   strncpy(phrase[4].word, "jumps", 7);
   strncpy(phrase[5].word, "over", 7);
   strncpy(phrase[6].word, "the", 7);
   strncpy(phrase[7].word, "lazy", 7);
   strncpy(phrase[8].word, "dog", 7);

   if(!mix(phrase))
      printf("Sorry didn't work");
   else
      play(phrase);

   exit(0);
}


int mix(struct words * array)
{
   if(!array)
      return 0;
   int r = 0;
   int check[9];
   char hold[7];
   struct timeval seed;

   gettimeofday(&seed, NULL);
   srand(seed.tv_sec);

   for(int i = 0; i < 9; ++i)
      check[i] = 1;

   for(int i = 0; i < 9; ++i)
   {
      r = rand() % (8 + 1 - 0) + 0;
      while(check[r] == 0)
      {
         r = rand() % (8 + 1 - 0) + 0;
      }

      if(check[r])
      {
         strncpy(hold, array[i].word, 7);
         strncpy(array[i].word, array[r].word, 7);
         strncpy(array[r].word, hold, 7);
         check[r] = 0;
      }
   }

   return 1;
}


int play(struct words * phrase)
{
   struct timeval start_time;
   struct timeval end_time;
   struct timeval total_time;
   char user_input[15];
   char c = 0;
   int word_length = 0;
   int check_length = 0;
   int warning = 0;

   printf("This is a game that will test your typing speed! \n \nType the following words. If you answer incorrectly, the word will reappear. \n");
   gettimeofday(&start_time, NULL);

   for(int i = 0; i < 9; ++i)
   {
      do
      {
         do
         {
            printf("Type the word: ");
            printf("%s ", phrase[i].word);
            warning = scanf("%6s", user_input);

            word_length = strlen(user_input);
            check_length = strlen(phrase[i].word);
            while((c=getchar()) != '\n' && c != EOF);
         }while(word_length != check_length);

      }while(strncmp(phrase[i].word, user_input, check_length));
   }

   gettimeofday(&end_time, NULL);
   timersub(&end_time, &start_time, &total_time);

   printf("\nYou took %ld seconds and %ld microseconds", total_time.tv_sec, total_time.tv_usec);
   printf("\n");

   return 1;


}