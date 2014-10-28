    scanf("%i", &config_type);
    
	//printf("You selected %i\n", config_type);

    if ( init_daq(config_type) == TRUE )
        LED_control();
    else
        printf("ERROR: Cannot initialize system\n");

    system("PAUSE");	
    return 0;
}
/* Note: the following is the most simple and logical way for the implementation 
   of the LED_control() funciton.
   There are of course other implementations. 
*/
void LED_control(void)
{
    /* variable delcarations */
	int switch0_state;
	int switch1_state;
   
    while( user_has_quit() == FALSE ) 
	{
		/* Get an update on current state of the switches */
		switch0_state = read_binary(SWITCH0_CHANNEL);
		switch1_state = read_binary(SWITCH1_CHANNEL);
		
		/* See which of the four possible switch configurations
		    we are in and turn on/off the appropriate LEDs */
		if(switch0_state == SWITCHON && switch1_state == SWITCHON) 
		{
			write_binary(LED0_CHANNEL, LEDOFF);
			write_binary(LED1_CHANNEL, LEDOFF);
			write_binary(LED2_CHANNEL, LEDON);
		} 
		else if(switch0_state == SWITCHOFF && switch1_state == SWITCHON) 
		{
			write_binary(LED0_CHANNEL, LEDOFF);
			write_binary(LED1_CHANNEL, LEDON);
			write_binary(LED2_CHANNEL, LEDOFF);
		}
		else if(switch0_state == SWITCHON && switch1_state == SWITCHOFF) 
		{
			write_binary(LED0_CHANNEL, LEDON);
			write_binary(LED1_CHANNEL, LEDOFF);
			write_binary(LED2_CHANNEL, LEDOFF);
		}
		else 
		{
			write_binary(LED0_CHANNEL, LEDOFF);
			write_binary(LED1_CHANNEL, LEDOFF);
			write_binary(LED2_CHANNEL, LEDOFF);
		}
	}        
}        



