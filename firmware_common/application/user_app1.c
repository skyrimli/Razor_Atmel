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
  
  LedOff(RED);
  LedOff(GREEN);
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
  static u8 au8PinNum0[10]={0,1,2,0,1,2,0,1,2,0};
  static u8 au8PinNum1[10]={0,0,0,0,0,0,0,0,0,0};
  static u8 u8Counter = 0;
  static u8 u8Compare = 0;
  static u8 i = 0;
  static bool bRedLight = TRUE;
  static bool bReset = FALSE;
  static bool bButton3Held = FALSE;
  static bool bPassWord = TRUE;
  
  
  if(bButton3Held==FALSE)
  {
    if(IsButtonHeld(BUTTON3,2000))
    { 
      ButtonAcknowledge(BUTTON3);
      bReset = TRUE;
    }
  } 
  if(bReset)
  {   
      if(bPassWord)
      {
        for(i=0;i<10;i++)
        {
          au8PinNum0[i]=0;
        }
        bPassWord=FALSE;
        LedBlink(RED,LED_2HZ);
        LedBlink(GREEN,LED_2HZ);
        u8Counter = 0;
      } 
      if(WasButtonPressed(BUTTON0))
      {
        ButtonAcknowledge(BUTTON0);
        au8PinNum0[u8Counter]=0;
        u8Counter++;
      }
      if(WasButtonPressed(BUTTON1))
      {
        ButtonAcknowledge(BUTTON1);
        au8PinNum0[u8Counter]=1;
        u8Counter++;
      }
      if(WasButtonPressed(BUTTON2))
      {
        ButtonAcknowledge(BUTTON2);
        au8PinNum0[u8Counter]=2;
        u8Counter++;
      }
      if(WasButtonPressed(BUTTON3))
      {
        ButtonAcknowledge(BUTTON3);
        bReset=FALSE;
        LedOff(GREEN);
        bRedLight=TRUE;
        bButton3Held=TRUE;
        u8Counter = 0;
      }
  }

  if (bButton3Held)
  {
    if(bRedLight)
    {
      LedOn(RED);
      
      if(WasButtonPressed(BUTTON0))
      {
        ButtonAcknowledge(BUTTON0);
        au8PinNum1[u8Counter]=0;
        u8Counter++;
      }
      if(WasButtonPressed(BUTTON1))
      {
        ButtonAcknowledge(BUTTON1);
        au8PinNum1[u8Counter]=1;
        u8Counter++;
      }
      if(WasButtonPressed(BUTTON2))
      {
        ButtonAcknowledge(BUTTON2);
        au8PinNum1[u8Counter]=2;
        u8Counter++;
      }
    }
    if(WasButtonPressed(BUTTON3))
    {
      ButtonAcknowledge(BUTTON3);
      u8Counter=0;
      
      for(i=0;i<10;i++)
      {
        if(au8PinNum0[i]^au8PinNum1[i])
        {
          u8Compare++;
        }
      }
      if(u8Compare==0)
      {
        u8Counter=0;
        LedOff(RED);
        bRedLight=FALSE;
        LedBlink(GREEN,LED_2HZ);
      }
      else
      {
        u8Counter=0;
        bRedLight = FALSE;
        LedBlink(RED,LED_2HZ);
      }
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
