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
static u8 au8Message1[]="B0 name B1 debug";
static u8 au8Message2[]="B3 return menu";
static u8 UserApp_CursorPosition;
extern u8 G_au8DebugScanfBuffer[];
extern u8 G_u8DebugScanfCharCount;

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
  LCDClearChars(LINE1_START_ADDR,20);
  LCDClearChars(LINE2_START_ADDR,20);
  LCDMessage(LINE1_START_ADDR,au8Message1);
  LCDMessage(LINE2_START_ADDR,au8Message2);
  UserApp_CursorPosition=LINE1_START_ADDR;
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
  static u8 au8MessageButton0[] = "B0 right B1 left";
  static u8 au8Name[] = "Lizhihao";
  static u8 au8MessageButton1[] = "Please Input Message";
  static u8 au8StringButton11[20];
  static u8 au8StringButton12[20];
  static u8 au8StringButton13[20];
  static u8 u8State = 0;
  static u8 u8LCDState = 0;
  static u8 u8Counter1 = 0;
  static u8 u8Counter2 = 0;
  static u16 u16TimeCounter = 0;
  static bool bEmpty = FALSE;
  static bool bBuzzer = FALSE;
  static bool bDisplay = FALSE;
  
  if(u8State==0)
  {
    if(WasButtonPressed(BUTTON0))
    {
      ButtonAcknowledge(BUTTON0);
      LCDClearChars(LINE1_START_ADDR,20);
      LCDClearChars(LINE2_START_ADDR,20);
      LCDMessage(LINE1_START_ADDR,au8Name);
      LCDMessage(LINE2_START_ADDR,au8MessageButton0);
      u8State=1;
    }
    if(WasButtonPressed(BUTTON1))
    {
      ButtonAcknowledge(BUTTON1);
      LCDClearChars(LINE1_START_ADDR,20);
      LCDClearChars(LINE2_START_ADDR,20);
      LCDMessage(LINE1_START_ADDR,au8MessageButton1);
      u8State=2;
    }
  }
  if(u8State==1) 
  {
    if(WasButtonPressed(BUTTON0))
    {
      PWMAudioSetFrequency(BUZZER2,3000);
      PWMAudioOn(BUZZER2);
      bBuzzer = TRUE;
      ButtonAcknowledge(BUTTON0);
      if(UserApp_CursorPosition != LINE1_START_ADDR+28)
      {
        UserApp_CursorPosition++;
        LCDClearChars(LINE1_START_ADDR,40);
        LCDClearChars(LINE2_START_ADDR,40);
        LCDMessage(UserApp_CursorPosition,au8Name);
        LCDMessage(UserApp_CursorPosition+20,au8Name);
      }
    }
    if(WasButtonPressed(BUTTON1))
    {
      PWMAudioSetFrequency(BUZZER2,1000);
      PWMAudioOn(BUZZER2);
      bBuzzer = TRUE;
      ButtonAcknowledge(BUTTON1);
      if(UserApp_CursorPosition != LINE1_START_ADDR)
      {
        UserApp_CursorPosition--;
        LCDClearChars(LINE1_START_ADDR,40);
        LCDClearChars(LINE2_START_ADDR,40);
        LCDMessage(UserApp_CursorPosition,au8Name);
        LCDMessage(UserApp_CursorPosition+20,au8Name);      
      }    
    }
    if(bBuzzer)
    {
      u16TimeCounter++;
      if(u16TimeCounter==500)
      {
        u16TimeCounter=0;
        PWMAudioOff(BUZZER2);
        bBuzzer=FALSE;
      }
    }
    if(UserApp_CursorPosition==LINE1_START_ADDR+28||UserApp_CursorPosition==LINE1_START_ADDR)
    {
      PWMAudioSetFrequency(BUZZER1,10000);
      PWMAudioOn(BUZZER1);
    }
    else
    {
      PWMAudioOff(BUZZER1);
    }
  }
  if(u8State==2)
  {
    if(bEmpty==FALSE)
    {
      if(G_u8DebugScanfCharCount!=0)
      {
        LCDCommand(LCD_CLEAR_CMD);
        bEmpty=TRUE;
        for(u8Counter1=0;u8Counter1<20;u8Counter1++)
        {
          au8StringButton11[u8Counter1]=0;
          au8StringButton12[u8Counter1]=0;        
        }
      }
      
    }
    for(u8Counter1=0;u8Counter1<G_u8DebugScanfCharCount;u8Counter1++)
    {  
      if(G_au8DebugScanfBuffer[u8Counter1]==0x0d&&G_u8DebugScanfCharCount<20)
      {
        for(u8Counter2=0;u8Counter2<u8Counter1;u8Counter2++)
        {
          au8StringButton11[u8Counter2]=G_au8DebugScanfBuffer[u8Counter2]; 
        }
        for(u8Counter2=0;u8Counter2+u8Counter1+1<G_u8DebugScanfCharCount;u8Counter2++)
        {
          au8StringButton12[u8Counter2]=G_au8DebugScanfBuffer[u8Counter2+u8Counter1+1];
        }
      }/*press 'Enter' Once to line feed*/
      if(G_u8DebugScanfCharCount>=20&&G_u8DebugScanfCharCount<=40)
      {
        au8StringButton11[u8Counter1]=G_au8DebugScanfBuffer[u8Counter1]; 
        au8StringButton12[u8Counter1]=G_au8DebugScanfBuffer[u8Counter1+20]; 
      }
    }
    
      if(G_u8DebugScanfCharCount>40)
      {
        for(u8Counter1=0;u8Counter1<20;u8Counter1++)
        {
          au8StringButton11[u8Counter1]=G_au8DebugScanfBuffer[u8Counter1];        
        }
        for(u8Counter1=20;u8Counter1<40;u8Counter1++)
        {
          au8StringButton12[u8Counter1]=G_au8DebugScanfBuffer[u8Counter1+20];
        }
        for(u8Counter1=40;u8Counter1<=G_u8DebugScanfCharCount;u8Counter1++)
        {
          au8StringButton13[u8Counter1]=G_au8DebugScanfBuffer[u8Counter1+40];
        }
      }
    
    if(G_u8DebugScanfCharCount<=40)
    {
      if(WasButtonPressed(BUTTON1)) 
      {
        ButtonAcknowledge(BUTTON1);
        LCDMessage(LINE1_START_ADDR,au8StringButton11);
        LCDMessage(LINE2_START_ADDR,au8StringButton12);
      }
    }
    if(G_u8DebugScanfCharCount>40)
    {
      if(WasButtonPressed(BUTTON1)) 
      {
        ButtonAcknowledge(BUTTON1);
        bDisplay=TRUE;
      }
    }
    if(bDisplay)
    {
      if(u16TimeCounter<2000&&u8LCDState==0)
      {
        u8LCDState=1;
        LCDClearChars(LINE1_START_ADDR,40);
        LCDMessage(LINE1_START_ADDR,au8StringButton11);
        LCDClearChars(LINE2_START_ADDR,40);
      }
      if(u16TimeCounter>=2000&&u16TimeCounter<4000&&u8LCDState==1)
      {
        u8LCDState=2;
        LCDClearChars(LINE1_START_ADDR,40);
        LCDMessage(LINE1_START_ADDR,au8StringButton12);
        LCDClearChars(LINE2_START_ADDR,40);
      }
      if(u16TimeCounter>=4000&&u8LCDState==2)
      {
        u8LCDState=3;
        LCDClearChars(LINE1_START_ADDR,40);
        LCDMessage(LINE1_START_ADDR,au8StringButton13);
        LCDClearChars(LINE2_START_ADDR,40);
      }
      if(u16TimeCounter==6000)
      {
        u8LCDState=0;
        u16TimeCounter=0;
      }
      u16TimeCounter++;
    }
        
  }
  if(u8State!=0)
  {
    if(WasButtonPressed(BUTTON3))
    {
      ButtonAcknowledge(BUTTON3);
      u8State=0;
      LCDClearChars(LINE1_START_ADDR,20);
      LCDClearChars(LINE2_START_ADDR,20);
      LCDMessage(LINE1_START_ADDR,au8Message1);
      LCDMessage(LINE2_START_ADDR,au8Message2);
      DebugScanf(G_au8DebugScanfBuffer);
      bEmpty=FALSE;
      bDisplay=FALSE;
      u16TimeCounter=0;
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
