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

extern u8 G_au8DebugScanfBuffer[];
extern u8 G_au8DebugScanfCharCount;
/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "UserApp1_" and be declared as static.
***********************************************************************************************************************/
static fnCode_type UserApp1_StateMachine;            /* The state machine function pointer */
//static u32 UserApp1_u32Timeout;                      /* Timeout counter used across states */


/**********************************************************************************************************************
Function Definitions
**********************************************************************************************************************/

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
  static u8 u8Key = 0; 
  static bool bBuzzerIsOn = FALSE;
  static u8 u8TimeCounter = 0;
  static u8 au8String[]="please press '1-7','q-u','a-j'";
  /*static u8 au8Gamut[7][3]={{262,523,1046},
                            {294,578,1175},
                            {330,628,1318},
                            {349,698,1397},
                            {392,784,1568},
                            {440,880,1760},
                            {494,988,1976}};*/
  
  if(G_au8DebugScanfBuffer[0]!='\0')
  {
    u8Key=G_au8DebugScanfBuffer[0];
    DebugScanf(G_au8DebugScanfBuffer);
    switch(u8Key)
    {
      case '1' : PWMAudioSetFrequency(BUZZER1,523);PWMAudioOn(BUZZER1);bBuzzerIsOn=TRUE;break;
      case '2' : PWMAudioSetFrequency(BUZZER1,578);PWMAudioOn(BUZZER1);bBuzzerIsOn=TRUE;break;
      case '3' : PWMAudioSetFrequency(BUZZER1,628);PWMAudioOn(BUZZER1);bBuzzerIsOn=TRUE;break;
      case '4' : PWMAudioSetFrequency(BUZZER1,698);PWMAudioOn(BUZZER1);bBuzzerIsOn=TRUE;break;
      case '5' : PWMAudioSetFrequency(BUZZER1,784);PWMAudioOn(BUZZER1);bBuzzerIsOn=TRUE;break;
      case '6' : PWMAudioSetFrequency(BUZZER1,880);PWMAudioOn(BUZZER1);bBuzzerIsOn=TRUE;break;
      case '7' : PWMAudioSetFrequency(BUZZER1,988);PWMAudioOn(BUZZER1);bBuzzerIsOn=TRUE;break;
      case 'q' : PWMAudioSetFrequency(BUZZER1,262);PWMAudioOn(BUZZER1);bBuzzerIsOn=TRUE;break;
      case 'w' : PWMAudioSetFrequency(BUZZER1,294);PWMAudioOn(BUZZER1);bBuzzerIsOn=TRUE;break;
      case 'e' : PWMAudioSetFrequency(BUZZER1,330);PWMAudioOn(BUZZER1);bBuzzerIsOn=TRUE;break;
      case 'r' : PWMAudioSetFrequency(BUZZER1,349);PWMAudioOn(BUZZER1);bBuzzerIsOn=TRUE;break;
      case 't' : PWMAudioSetFrequency(BUZZER1,392);PWMAudioOn(BUZZER1);bBuzzerIsOn=TRUE;break;
      case 'y' : PWMAudioSetFrequency(BUZZER1,440);PWMAudioOn(BUZZER1);bBuzzerIsOn=TRUE;break;
      case 'u' : PWMAudioSetFrequency(BUZZER1,494);PWMAudioOn(BUZZER1);bBuzzerIsOn=TRUE;break;
      case 'a' : PWMAudioSetFrequency(BUZZER1,1046);PWMAudioOn(BUZZER1);bBuzzerIsOn=TRUE;break;
      case 's' : PWMAudioSetFrequency(BUZZER1,1175);PWMAudioOn(BUZZER1);bBuzzerIsOn=TRUE;break;
      case 'd' : PWMAudioSetFrequency(BUZZER1,1318);PWMAudioOn(BUZZER1);bBuzzerIsOn=TRUE;break;
      case 'f' : PWMAudioSetFrequency(BUZZER1,1397);PWMAudioOn(BUZZER1);bBuzzerIsOn=TRUE;break;
      case 'g' : PWMAudioSetFrequency(BUZZER1,1568);PWMAudioOn(BUZZER1);bBuzzerIsOn=TRUE;break;
      case 'h' : PWMAudioSetFrequency(BUZZER1,1760);PWMAudioOn(BUZZER1);bBuzzerIsOn=TRUE;break;
      case 'j' : PWMAudioSetFrequency(BUZZER1,1976);PWMAudioOn(BUZZER1);bBuzzerIsOn=TRUE;break;
      default : DebugPrintf(au8String);DebugLineFeed();
    }
  }
  if(bBuzzerIsOn)
  {
    u8TimeCounter++;
    if(u8TimeCounter==250)
    {
      u8TimeCounter=0;
      bBuzzerIsOn=FALSE;
      PWMAudioOff(BUZZER1);
    }
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
