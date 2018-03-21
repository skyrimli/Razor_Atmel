/**********************************************************************************************************************
File: user_app1.c                                                                

----------------------------------------------------------------------------------------------------------------------
To start a new task using this user_app1 as a template:
 1. Copy both user_app1.c and user_app1.h to the Application directory
 2. Rename the files yournewtaskname.c and yournewtaskname.h
 3. Add yournewtaskname.c and yournewtaskname.h to the Application Include and Source groups in the IAR project
 4. Use ctrl-h (make sure "Match Case" is checked) to find and replace all instances of "user_app1" with "yournewtaskname"
 5. Use ctrl-h to find and replace all instances of "UserApp1" with "YourNewTaskName"
 6. Use ctrl-h to find and replace all instances of "USER_APP1" with "YOUR_NEW_TASK_NAME"
 7. Add a call to YourNewTaskNameInitialize() in the init section of main
 8. Add a call to YourNewTaskNameRunActiveState() in the Super Loop section of main
 9. Update yournewtaskname.h per the instructions at the top of yournewtaskname.h
10. Delete this text (between the dashed lines) and update the Description below to describe your task
----------------------------------------------------------------------------------------------------------------------

Description:
This is a user_app1.c file template 

------------------------------------------------------------------------------------------------------------------------
API:

Public functions:


Protected System functions:
void UserApp1Initialize(void)
Runs required initialzation for the task.  Should only be called once in main init section.

void UserApp1RunActiveState(void)
Runs current task state.  Should only be called once in main loop.


**********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_UserApp1"
***********************************************************************************************************************/
/* New variables */
volatile u32 G_u32UserApp1Flags;                       /* Global state flags */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemFlags;                  /* From main.c */
extern volatile u32 G_u32ApplicationFlags;             /* From main.c */

extern volatile u32 G_u32SystemTime1ms;                /* From board-specific source file */
extern volatile u32 G_u32SystemTime1s;                 /* From board-specific source file */


/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "UserApp1_" and be declared as static.
***********************************************************************************************************************/
static fnCode_type UserApp1_StateMachine;            /* The state machine function pointer */
//static u32 UserApp1_u32Timeout;                      /* Timeout counter used across states */


/**********************************************************************************************************************
Function Definitions
**********************************************************************************************************************/
extern u8 G_au8DebugScanfBuffer[];
/*--------------------------------------------------------------------------------------------------------------------*/
/* Public functions                                                                                                   */
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
/* Protected functions                                                                                                */
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------
Function: UserApp1Initialize

Description:
Initializes the State Machine and its variables.

Requires:
  -

Promises:
  - 
*/
void UserApp1Initialize(void)
{
 
  /* If good initialization, set state to Idle */
  if( 1 )
  {
    UserApp1_StateMachine = UserApp1SM_Idle;
  }
  else
  {
    /* The task isn't properly initialized, so shut it down and don't run */
    UserApp1_StateMachine = UserApp1SM_Error;
  }

} /* end UserApp1Initialize() */

  
/*----------------------------------------------------------------------------------------------------------------------
Function UserApp1RunActiveState()

Description:
Selects and runs one iteration of the current state in the state machine.
All state machines have a TOTAL of 1ms to execute, so on average n state machines
may take 1ms / n to execute.

Requires:
  - State machine function pointer points at current state

Promises:
  - Calls the function to pointed by the state machine function pointer
*/
void UserApp1RunActiveState(void)
{
  UserApp1_StateMachine();

} /* end UserApp1RunActiveState */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Private functions                                                                                                  */
/*--------------------------------------------------------------------------------------------------------------------*/


/**********************************************************************************************************************
State Machine Function Definitions
**********************************************************************************************************************/

/*-------------------------------------------------------------------------------------------------------------------*/
/* Wait for ??? */
static void UserApp1SM_Idle(void)
{
  static u8 u8Message1[] = "Enter 1 or press button1 to get into state 1\n";
  static u8 u8Message2[] = "Enter 2 or press button2 to get into state 2\n";
  static u8 u8Message3[] = "*************************************************\n";
  static u8 u8LcdMessage1[] = "STATE 1";
  static u8 u8LcdMessage2[] = "STATE 2";
  static bool bPrint = TRUE;
  static u8 u8state = 0;
  static u8 u8IsAudioOn = FALSE;
  static u16 u16Counter = 0;
  static u8 u8aurry[]={0};
  
  if(u8state==0)
  {
    if(bPrint)
    {
      DebugPrintf(u8Message1);
      DebugPrintf(u8Message2);
      DebugPrintf(u8Message3);
      bPrint = FALSE;
    }
    if(u8IsAudioOn)
    {
      if(u16Counter==0)
      {
        PWMAudioOn(BUZZER1);
      }
      u16Counter++;
      if(u16Counter==100)
      {
        PWMAudioOff(BUZZER1);
      }
      if(u16Counter==1000)
      {
        u16Counter=0;
      }
      
    }
    if(G_au8DebugScanfBuffer[]=='1')
    {
      DebugScanf(u8aurry);
      ButtonAcknowledge(BUTTON1);
      LCDClearChars(0,10);
      LedOff(WHITE);
      LedOff(PURPLE);
      LedOff(BLUE);
      LedOff(CYAN);
      LedOff(GREEN);
      LedOff(YELLOW);
      LedOff(ORANGE);
      LedOff(RED);
      LedOn(LCD_RED);
      LedOn(LCD_GREEN);
      LedOn(LCD_BLUE);
      PWMAudioOff(BUZZER1);
      u8state=1;
    }
    if(WasButtonPressed(BUTTON1))
    {
      DebugScanf(u8aurry);
      ButtonAcknowledge(BUTTON1);
      LCDClearChars(0,10);
      LedOff(WHITE);
      LedOff(PURPLE);
      LedOff(BLUE);
      LedOff(CYAN);
      LedOff(GREEN);
      LedOff(YELLOW);
      LedOff(ORANGE);
      LedOff(RED);
      LedOn(LCD_RED);
      LedOn(LCD_GREEN);
      LedOn(LCD_BLUE);
      PWMAudioOff(BUZZER1);
      u8state=1;
    }
    if(G_au8DebugScanfBuffer[]=='2')
    {
      DebugScanf(u8aurry);
      ButtonAcknowledge(BUTTON2);
      LCDClearChars(0,10);
      LedOff(WHITE);
      LedOff(PURPLE);
      LedOff(BLUE);
      LedOff(CYAN);
      LedOff(GREEN);
      LedOff(YELLOW);
      LedOff(ORANGE);
      LedOff(RED);
      LedOn(LCD_RED);
      LedOn(LCD_GREEN);
      LedOn(LCD_BLUE);
      PWMAudioOff(BUZZER1);
      u8state=2;
    }
    if(WasButtonPressed(BUTTON2))
    {
      DebugScanf(u8aurry);
      ButtonAcknowledge(BUTTON2);
      LCDClearChars(0,10);
      LedOff(WHITE);
      LedOff(PURPLE);
      LedOff(BLUE);
      LedOff(CYAN);
      LedOff(GREEN);
      LedOff(YELLOW);
      LedOff(ORANGE);
      LedOff(RED);
      LedOn(LCD_RED);
      LedOn(LCD_GREEN);
      LedOn(LCD_BLUE);
      PWMAudioOff(BUZZER1);
      u8state=2;
    }
    if((G_au8DebugScanfBuffer[]!='1'&&G_au8DebugScanfBuffer[]!='2'))
    {
      bPrint = TRUE;
      DebugScanf(u8aurry);
      ButtonAcknowledge(BUTTON1);
    }
    if(WasButtonPressed(BUTTON0)||WasButtonPressed(BUTTON3))
    {
      bPrint = TRUE;
      DebugScanf(u8aurry);
      ButtonAcknowledge(BUTTON1);
    }
  }
  if(u8state==1)
  {
    LedOn(WHITE);
    LedOn(PURPLE);
    LedOn(BLUE);
    LedOn(CYAN);
    LedOff(LCD_BLUE);
    LCDMessage(0,u8LcdMessage1);
    u8state=0;
    u8IsAudioOn = FALSE;
  }
  if(u8state==2)
  {
    LedBlink(GREEN,LED_1HZ);
    LedBlink(YELLOW,LED_2HZ);
    LedBlink(ORANGE,LED_4HZ);
    LedBlink(RED,LED_8HZ);
    LedOff(LCD_GREEN);
    LCDMessage(0,u8LcdMessage2);
    PWMAudioSetFrequency(BUZZER1,200);
    u16Counter=0;
    u8IsAudioOn = TRUE;
    u8state = 0;
  }
  
} /* end UserApp1SM_Idle() */
    

/*-------------------------------------------------------------------------------------------------------------------*/
/* Handle an error */
static void UserApp1SM_Error(void)          
{
  
} /* end UserApp1SM_Error() */



/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
