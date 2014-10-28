/* Scott Erickson
/  Lab Section L2D
/  April 5, 2013
/  email: scottebro@gmail.com
/  Student Number:44744126
/
/  Code Objective: To make a simple implimentation of the simon game 
/   while using the DAQ files for c programming.
*/

/* Necessary include statements */
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <Hardware_Utilities.h>
#include <time.h>

/* Constant for length of gameplay sequence */
#define GAME_LENGTH 5

/* Defined channel values */
#define SWITCH0_CHANNEL 0
#define SWITCH1_CHANNEL 1
#define SWITCH2_CHANNEL 2
#define SWITCH3_CHANNEL 3

/* Defined channel values */
#define LED0_CHANNEL 0
#define LED1_CHANNEL 1
#define LED2_CHANNEL 2
#define LED3_CHANNEL 3

/* Constants for switch on or off values */
#define SWITCHOFF 0
#define SWITCHON 1

/* Constants for LED on or off values */
#define LEDOFF 0
#define LEDON 1

/* Constants for true false statements */
#define TRUE 1
#define FALSE 0

/* Defined time delay in miliSecond s*/
#define ONE_SEC 1000

/* Function prototypes */
void simon_Sequence(void);
int get_Button_Pressed(void);

/* Main funtion */ 
int main(void)
{
	int config_type;
			
	srand( (unsigned) time( NULL ) );

	printf("Traffic light controller program. A supplement to lecture notes on DAQ.\n\n\n"); 
    printf("Choose type 0 to use the hardware;\n");
    printf("       type 6 to use the simulator.\n"); 
    printf("Enter configuration type: ");
    scanf("%i", &config_type);
    printf("You selected %i\n", config_type);

    if ( init_daq(config_type) == TRUE )
        simon_Sequence();
    else
        printf("ERROR: Cannot initialize system\n");
    
    system("PAUSE");
    return 0;
}

/* Function that controls the actual simon game */
void simon_Sequence(void)
{

	int newCount;
	int size = GAME_LENGTH;
	int N;
	int exitVal;
	int game;
	int game_Sequence[GAME_LENGTH];

	for (game=1; game<size; game++)
	{
		
		for (newCount=0; newCount<size; newCount++)
		{
			game_Sequence[newCount] = rand()%4;
		}

		for (N=size-1; N>=0; N--)
		{
			
			for (newCount=0; newCount<size-N; newCount++)
			{
				Sleep(ONE_SEC/2);
				write_binary(game_Sequence[newCount], LEDON);
				Sleep(ONE_SEC/4);
				write_binary(game_Sequence[newCount], LEDOFF);
			}
	
			for (newCount=0; newCount<size-N; newCount++)
			{
				
				if (get_Button_Pressed() == game_Sequence[newCount])
				{
					write_binary(game_Sequence[newCount], LEDON);
					Sleep(ONE_SEC/2);
					write_binary(game_Sequence[newCount], LEDOFF);
					Sleep(ONE_SEC/2);
					exitVal=1;
				}
				
				else 
				{
					N=-1;
					newCount=size;
					exitVal=0;
				}
			}
		}

		if (exitVal == 1)
		{
			Sleep(7*ONE_SEC/10);
			write_binary(LED0_CHANNEL, LEDON);
			Sleep(ONE_SEC/4);
			write_binary(LED0_CHANNEL, LEDOFF);
			Sleep(ONE_SEC/4);
			write_binary(LED0_CHANNEL, LEDON);
			Sleep(ONE_SEC/4);
			write_binary(LED0_CHANNEL, LEDOFF);
			Sleep(ONE_SEC/4);
			write_binary(LED0_CHANNEL, LEDON);
			Sleep(ONE_SEC/4);
			write_binary(LED0_CHANNEL, LEDOFF);
			Sleep(ONE_SEC/2);
			game=1;
		}

		else
		{
			Sleep(7*ONE_SEC/10);
			write_binary(LED1_CHANNEL, LEDON);
			Sleep(ONE_SEC/4);
			write_binary(LED1_CHANNEL, LEDOFF);
			Sleep(ONE_SEC/4);
			write_binary(LED1_CHANNEL, LEDON);
			Sleep(ONE_SEC/4);
			write_binary(LED1_CHANNEL, LEDOFF);
			Sleep(ONE_SEC/4);
			write_binary(LED1_CHANNEL, LEDON);
			Sleep(ONE_SEC/4);
			write_binary(LED1_CHANNEL, LEDOFF);
			Sleep(ONE_SEC/2);
			game=1;
		}
	}
}

/* Called function within the simon game functon that returns a number value that's the same as the button number they press. 
/  Or 4 if they don't press a button in time. */
int get_Button_Pressed(void)
{
	int count;
	int returnVal;
	for (count=0; count<50; count++)
	{
		
		if(read_binary(SWITCH0_CHANNEL) == TRUE)
		{
			returnVal=0;
			count=100;
		}
		
		else if(read_binary(SWITCH1_CHANNEL) == TRUE)
		{
			returnVal=1;
			count=100;
		}
		
		else if(read_binary(SWITCH2_CHANNEL) == TRUE)
		{
			returnVal=2;
			count=100;
		}
		
		else if(read_binary(SWITCH3_CHANNEL) == TRUE)
		{
			returnVal=3;
			count=100;
		}
		
		else
		{
			returnVal=4;
		}
	}
	return returnVal;
}

