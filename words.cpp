#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <unistd.h>


char faddress[5] = "data";

struct category {
	char catname[60];
	int now; // Number of words
	char (*words)[60];
} *categories; // Categories Declaration

int numofcats;

char *sp(char s1[], char s2[]) // merge two strings
{
	int n1, n2;
	for (n1 = 0; s1[n1] != '\0'; n1++);
	for (n2 = 0; s2[n2] != '\0'; n2++);
	
	char s3[n1 + n2 + 1 + 1]; /* 1 for space, 1 for \0 */
	for (int i = 0; i < n1; i++) 
		s3[i] = s1[i];
		
	s3[n1] = ' ';
	
	for (int i = 0; i < n2; i++)
		s3[n1 + 1 + i] = s2[i];
		
	s3[n1 + n2 + 1] = '\0';
	return s3;
}

void strcpy(char s1[], char s2[], int size, int space)
{
	for (int i = 0; i < space; i++) s1[i] = ' ';
	for (int i = 0; i < size - space; i++) s1[i + space] = s2[i];
	s1[59] = '\0';
}

void loadwords(char faddress[])
{
	char line_temp[60];
	 
	FILE *fp;
	fp = fopen(faddress, "rt");
	
	if (fp != NULL)
	{
		int cnt_cats = 0, cnt_lines = -1;
		while(line_temp[0] != '/')
		{
			cnt_lines++;
			fgets(line_temp, 60, fp);
			if (line_temp[0] == '#') cnt_cats++;
		}
		
		categories = (category *) malloc ( cnt_cats * sizeof(category) );
		
		rewind(fp);
		int cnt_words = 0, i = -1;
		line_temp[0] = '\0';
		while(true)
		{
			fgets(line_temp, 60, fp);
			
			if (line_temp[0] == '#' || line_temp[0] == '/') 
			{
				if (cnt_words != 0)
				{
					i++;
					(categories + i) -> now = cnt_words;
					(categories + i) -> words = (char (*)[60]) malloc ( (cnt_words +  1) * 60 * sizeof(char) );
				}
				cnt_words = 0;
				if (line_temp[0] == '/') break;
			}
			else cnt_words++;
		}
																											
		rewind(fp);
		int cat = -1, wrd = 0; line_temp[0] = '\0';
		while(line_temp[0] != '/')
		{
			fgets(line_temp, 60, fp);
			
			if (line_temp[0] == '#')
			{
				wrd = 0;
				cat++;
				char *name;
				name = line_temp;
				name = name + sizeof(char);
				for (int i = 0; i < 60; i++)
				{
					if ( *(name + i) == '\n' ) 
					{
						*(name + i) = '\0';
						break;
					}
				}
				strcpy( (categories + cat) -> catname, name, 60, 0);
			}
			else
			{
				for (int i = 0; i < 60; i++)
				{
					if ( line_temp[i] == '\n' ) 
					{
						line_temp[i] = '\0';
						break;
					}
				}
				strcpy( (categories + cat) -> words[wrd], line_temp, 60, 0);
				wrd++;
			}
		}
		
		fclose(fp);
		numofcats = cnt_cats;
	}
	else
	{
		system("cls");
		printf("Error: Can't Load the Data File ... Closing");
		sleep(3);
		exit(0);
	}
}

void loading();

void splash();

char menu(char items[14][60], int numofitems, bool _getch);

void mainmenu();

char game(char cat);

void savescore(char name[60], int score);
void loadscore();

void goodbye();

int main() // ------------------- MAIN ------------------- //
{
	loading();
	system("mode con lines=30");
	system("mode con cols=120");
	splash();
	mainmenu();
	goodbye();
}

void loading()
{
	system("mode con lines=3");
	system("mode con cols=70");
	for (int i = 0; i <= 50; i += 5)
	{
		system("cls");
		printf("\n  Loading %%%3d [", i * 2);
		for (int j = 0; j <= i; j++)
			printf("|");
		for (int j = 0; j < (50 - i); j++)
			printf("-");
		printf("]");
		_sleep(200);
	}
}

void splash()
{
	system("cls");
	
	printf("==================================================================================================================\n");
	printf("||                                                                                                              ||\n");
	printf("||          W               W  EEEEEEEE  L           CCCCCCCC     OOOOOOO      MMMMM   MMMMM    EEEEEEE         ||\n");
	printf("||          W               W  E         L          C        C   O       O    M     M M     M   E               ||\n");
	printf("||          W               W  E         L         C            O         O  M       M       M  E               ||\n");
	printf("||          W               W  EEEEEEEE  L         C            O         O  M               M  EEEEEEE         ||\n");
	printf("||          W       W       W  E         L         C            O         O  M               M  E               ||\n");
	printf("||           W     W W     W   E         L          C        C   O       O   M               M  E               ||\n");
	printf("||            WWWWW   WWWWW    EEEEEEEE  LLLLLLLL    CCCCCCCC     OOOOOOO    M               M  EEEEEEE         ||\n");
	printf("||                                                                                                              ||\n");
	printf("||                                              T                                                               ||\n");
	printf("||                                              T                                                               ||\n");
	printf("||                                            TTTTT                                                             ||\n");
	printf("||                                              T        OOOOO                                                  ||\n");
	printf("||                                              T       O     O                                                 ||\n");
	printf("||                                              T    T  O     O                                                 ||\n");
	printf("||                                               TTTT    OOOOO                                                  ||\n");
	printf("||                                                                                                              ||\n");
	printf("||     GGGGGGGG A       M   M       EEEEEEEE                 FFFF       W         W                 D  SSSSSS   ||\n");
	printf("||     G        AA      MM  MM      E                       F    F      W        W                  D S         ||\n");
	printf("||     G        A A     M M M M     E                       F           W       W                   D S         ||\n");
	printf("||     G   GGGG AAAA    M  MM  M    EEEEEEEE       OOOOO  FFFFF         W  WW  W   OOOOO  R R  DDDDDD  SSSSSS   ||\n");
	printf("||     G      G A   A   M       M   E             OOOOOOO   F           W W W W   O     O RR  DDDDDDD        S  ||\n");
	printf("||     G      G A    A  M        M  E             OOOOOOO   F           WW  WW    O     O R   DDDDDDD        S  ||\n");
	printf("||     GGGGGGGG A     A M         M EEEEEEEE       OOOOO    F           W   W      OOOOO  R    DDDDD   SSSSSS   ||\n");
	printf("||                                                                                                              ||\n");
	printf("||                                        Press A Key To START!!! :)                                            ||\n");
	printf("||                                                                                                              ||\n");
	printf("==================================================================================================================");

	getch();
}

char menu(char items[14][60], int numofitems, bool _getch)
{
	system("cls");
	
	for (int i = numofitems; i < 14; i++)
		items[i][0] = '\0';
	
	printf("= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = \n");
	printf("                                                                                                                  \n");
	printf("  GGGGGGGGG AAAAAAAAA MMMM MMMM EEEEEEEEE   OOOOOOOOO FFFFFFFFF   W       W OOOOOOOO RRRRRR  DDDDDD    SSSSSSSS   \n");
	printf("  G         A       A M   M   M E           O       O F           W       W O      O R     R D     D  S           \n");
	printf("  G   GGGGG AAAAAAAAA M       M EEEEEE      O       O FFFFFF      W       W O      O RRRRRR  D      D  SSSSSSS    \n");
	printf("  G       G A       A M       M E           O       O F           W   W   W O      O R     R D     D          S   \n");
	printf("  GGGGGGGGG A       A M       M EEEEEEEEE   OOOOOOOOO F           WWWW WWWW OOOOOOOO R     R DDDDDD   SSSSSSSS    \n");
	printf("                                                                                                                  \n");
	printf(" = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
	printf("                                      |                                                                           \n");
	printf("    ggggg                             |                                                                           \n");
	printf("   g     g                   eeeee    |    %s\n", items[0]);
	printf("   g     g                  e     e   |    %s\n", items[1]);
	printf("    ggggg                   e eeeee   |    %s\n", items[2]);
	printf("         g     u     u      e         |    %s\n", items[3]);
	printf("         g     u     u       eeeee    |    %s\n", items[4]);
	printf("    ggggg      u     u      -------   |    %s\n", items[5]);
	printf("   -------      uuuuu u               |    %s\n", items[6]);
	printf("               --------               |    %s\n", items[7]);
	printf("                                      |    %s\n", items[8]);
	printf("                                      |    %s\n", items[9]);
	printf("            sssss   sssss             |    %s\n", items[10]);
	printf("           s       s                  |    %s\n", items[11]);
	printf("            sssss   sssss             |    %s\n", items[12]);
	printf("                 s       s            |    %s\n", items[13]);
	printf("            sssss   sssss             |                                                                           \n");
	printf("           ------- --------           |                                                                           \n");
	printf("                                      |    By: Mostafa Kazemi - mkay1375@gmail.com                                \n");
	printf("                                      |                                                                           \n");
	
	if (_getch)
	{
		again:
		char c = getch();
		switch (c)
		{
			case 39:
				return c;
			case 'a' ... 'z':
				return c;
			case '0' ... '9':
				return c;
			default:
				goto again;
		}
	}
}

void mainmenu()
{
	char menuitems[14][60];
	
	while (true)
	{
		strcpy(menuitems[0], "1. Play the GAME!", 60, 0) ; menuitems[1][0] = '\0';
		strcpy(menuitems[2], "2. View the Scores", 60, 0) ; menuitems[3][0] = '\0';
		strcpy(menuitems[4], "3. Exit", 60, 0) ;
		char selected = menu(menuitems, 5, true);
	
		switch (selected)
		{
			case '1': // Select category
				strcpy(menuitems[0], "0. Back", 60, 0) ;
				strcpy(menuitems[1], "   Select one of the categories below:", 60, 0) ;
				
				loadwords(faddress);
				for (int i = 0; i < numofcats; i++)
				{
					char num[3] = "0.";
					num[0] = i + 1 + 48;
					
					strcpy(menuitems[i + 2], sp(num, (categories + i) -> catname), 60, 5);
				}
				
/* LABEL */		SelectCat: 
				char sel_cat;
				sel_cat = menu(menuitems, numofcats + 2, true);
				switch (sel_cat)
				{
					case '0':
						break;
					default:
						if ('0' <= sel_cat && sel_cat <= numofcats + 48)
						{
							switch (game(sel_cat))
							{
								case '2':
									goto SelectCat;
								case '3':
									break;
							}
						}
						else goto SelectCat;
				}
				break;
			
			case '2': // scores
				loadscore();
				break;
			case '3':
				return;
		}
	}
}

char game(char cat)
{
	srand(time(0));
	
	int words = (categories + (cat - 48) - 1) ->  now; // number of words in the category
	char word[60];
	strcpy(word, (categories + (cat - 48) - 1) ->  words[rand() % words], 60, 0); // the word itself
	
	char letters[60]; // the letters which should be shown
	int len;
	for(len = 0; word[len] != '\0'; len++)
	{
		if (word[len] == ' ') letters[len] = ' ';
		else letters[len] = '-';
	}
	letters[len] = '\0'; // End; letter assigned
	
	// The Game view: Set the first parameters
	char menuitems[14][60];
	strcpy(
			menuitems[0], 
			sp("Category:", (categories + (cat - 48) - 1) -> catname),
			60,
			0
			);
	strcpy(
			menuitems[1], 
			sp("The Word:", letters),
			60,
			0
			);
	menuitems[2][0] = '\0';
	menuitems[3][0] = '\0';
	menuitems[4][0] = '\0';
	strcpy(menuitems[5], "1. See the word",	60,	0);
	menuitems[6][0] = '\0';
	strcpy(menuitems[7], "2. Back to categories", 60, 0);
	menuitems[8][0] = '\0';
	strcpy(menuitems[9], "3. Back to Mainmenu", 60, 0);
	// End: The Game view: Set the first parameters
	
	int score = 0;
	char wrong_letters[60]; int w_l = 0;
	char correct_letters[60]; int c_l = 0;
	bool correct;
	char entered = menu(menuitems, 10, true); // gets the first entered letter by the user
	
	while(true)
	{
		// Options
		switch (entered)
		{
			case '1': // See the word
				strcpy(
						menuitems[0], 
						sp("Category:", (categories + (cat - 48) - 1) -> catname),
						60,
						0
						);
				strcpy(
						menuitems[1], 
						sp("The Word:", word),
						60,
						0
						);
				menuitems[2][0] = '\0';
				strcpy(menuitems[3], "Press a key to back to the categories.", 60, 0);
				menu(menuitems, 4, false);
				getch();
				return '2';
			case '2': // Back to cat
				return '2';
			case '3': // Back to mainmenu
				return '3';
		}
		// End: Options
		
		correct = false;
		
		// Check area! ==========================================================================
		bool again = false;
		for (int i = 0; i < c_l; i++)
		{
			if ( correct_letters[i] == entered )
			{
				strcpy(menuitems[3], "Oops! You've entered this letter before!", 60, 0);
				entered = menu(menuitems, 10, true);
				again = true;
			}
		}
		for (int i = 0; i < w_l; i++)
		{
			if ( wrong_letters[i] == entered )
			{
				strcpy(menuitems[3], "Oops! You've entered this letter before!", 60, 0);
				entered = menu(menuitems, 10, true);
				again = true;
			}
		}
		menuitems[3][0] = '\0';
		if (again) continue;
		// End: Check area! =====================================================================
		
		// Check wether the letter is correct or not
		for (int i = 0; i < len; i++)
		{
			if ( word[i] == entered)
			{
				letters[i] = entered;
				correct = true;
			}
		}
		// End: Check wether the letter is correct or not
		
		if (correct == true) 
		{
			correct_letters[c_l] = entered;
			correct_letters[c_l + 1] = '\0';
			c_l++;
			strcpy(
					menuitems[1], 
					sp("The Word:", letters),
					60,
					0
					);
			
			// Check win		
			bool win = true;
			for (int i = 0; i < len; i++)
				if (letters[i] == '-')
					win = false;
			if (win)
			{
				score = (len - w_l) * 100;
				menuitems[2][0] = '\0';
				strcpy(menuitems[3], "Congratulations! You have won!!", 60, 0);
				sprintf(menuitems[4], "Your Score: %d", score);
				strcpy(menuitems[5], "Please Enter Your Name: ", 60, 0);
				menu(menuitems, 6, false);
				
				int n = 0;
				char name[60];
				char c_name = getch();
				while (c_name != '\r')
				{
					menuitems[5][24 + n + 1] = '\0'; 
					menuitems[5][24 + n] = c_name;
					name[n + 1] = '\0';
					name[n] = c_name;
					menu(menuitems, 6, false);
					c_name = getch();
					n++;
				}
				
				savescore(name, score);
				break;
			}
			// End: Check win
			
			entered = menu(menuitems, 10, true);
		}
		else 
		{
			// Check Lose
			if (w_l + 1 == len)
			{
				strcpy(
						menuitems[0], 
						sp("Category:", (categories + (cat - 48) - 1) -> catname),
						60,
						0
						);
				strcpy(
						menuitems[1], 
						sp("The Word:", word),
						60,
						0
						);
				menuitems[2][0] = '\0';
				strcpy(menuitems[3], "It seems you couldn't make it ... LET'S TRY AGAIN!!!", 60, 0);
				menu(menuitems, 4, false);
				getch();
				return '2'; // Back to categories
			}
			// End: Check Lose 
			
			wrong_letters[w_l] = entered;
			wrong_letters[w_l + 1] = '\0';
			strcpy(menuitems[2], wrong_letters,	60,	10);
			entered = menu(menuitems, 10, true);
			w_l++;
		}

	} //end while
	
}

void savescore(char name[60], int score)
{
	FILE *fp;
	fp = fopen("scores", "rt");
	
	if (fp != NULL)
	{
		int l = 1;
		char line[10][60];
		fgets(line[1], 60, fp);
		while(!feof(fp) && l != 9)
		{
			l++;
			fgets(line[l], 60, fp);
		}
		sprintf(line[0], "%s %d\n", name, score);
		fclose(fp);
		fp = fopen("scores", "wt");
		
		int i = 0;
		for (i; i < l; i++)
		{
			printf("\n%d %s", i , line[i]);
			printf("\n%d %s", i + 1 , line[i+1]);
			fputs(line[i], fp);
		}
		if (i == 10) fputs("/end", fp);
		else fputs(line[i], fp);
		
		fclose(fp);
	}
	else
	{
		fclose(fp);
		fp = fopen("scores", "wt");
		
		char _name[60];
		sprintf(_name, "%s %d\n", name, score);
		system("cls");
		fputs(_name, fp);
		fputs("/end", fp);
		
		fclose(fp);
	}
}

void loadscore()
{
	FILE *fp;
	fp = fopen("scores", "rt");
	
	if (fp != NULL)
	{
		char menuitems[14][60];
		strcpy(menuitems[0], "0. Back", 60, 0);
		char line[60];
		int i;
		for (i = 0; i < 10 && !feof(fp); i++)
		{
			fgets(line, 60, fp);
			if (line[0] != '/') 
			{
				for (int j = 0; j < 60; j++)
					if (line[j] == '\n') line[j] = '\0';
				strcpy(menuitems[i + 1], line, 60, 5);
			}
			else break;
		}
		
		fclose(fp);
		menu(menuitems, i + 1, true);
	}
	else
	{
		char menuitems[14][60];
		strcpy(menuitems[0], "0. Back", 60, 0);
		strcpy(menuitems[1], "No score has been achieved!", 60, 0);
		menu(menuitems, 2, true);
	}
}

void goodbye()
{
	char temp[20];
	for (int i = 30; i > 0; i--)
	{
		sprintf(temp, "mode con lines=%d", i);
		system(temp);
	}
	
	printf("                                                       bye... :)");
	sleep(3);
}
