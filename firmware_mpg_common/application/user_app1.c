/**********************************************************************************************************************
File: user_app1.c                                                                

Description:
Provides a Tera-Term driven system to display, read and write an LED command list.

Test1.
Test2 from Engenuics.
Test3.

------------------------------------------------------------------------------------------------------------------------
API:

Public functions:
None.

Protected System functions:
void UserApp1Initialize(void)
Runs required initialzation for the task.  Should only be called once in main init section.

void UserApp1RunActiveState(void)
Runs current task state.  Should only be called once in main loop.


**********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_"
***********************************************************************************************************************/
/* New variables */
volatile u32 G_u32UserApp1Flags;                       /* Global state flags */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemFlags;                  /* From main.c */
extern volatile u32 G_u32ApplicationFlags;             /* From main.c */

extern volatile u32 G_u32SystemTime1ms;                /* From board-specific source file */
extern volatile u32 G_u32SystemTime1s;                 /* From board-specific source file */

extern u8 G_au8DebugScanfBuffer[DEBUG_SCANF_BUFFER_SIZE]; /* From debug.c */
extern u8 G_u8DebugScanfCharCount;                        /* From debug.c */


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
  u8 au8UserApp1Start1[] = "LED program task started\n\r";
  
  /* Turn off the Debug task command processor and announce the task is ready */
  DebugSetPassthrough();
  DebugPrintf(au8UserApp1Start1);
  
    /* If good initialization, set state to Idle */
  if( 1 )
  {
    UserApp1_StateMachine = UserApp1SM_Idle;
  }
  else
  {
    /* The task isn't properly initialized, so shut it down and don't run */
    UserApp1_StateMachine = UserApp1SM_FailedInit;
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
/* Wait for input */
static void UserApp1SM_Idle(void)
{
  static u8 u8String0[] = "LED Programming Interface\n\r";
  static u8 u8String1[] = "Press 1 to program LED command sequence\n\r";
  static u8 u8String2[] = "Press 2 to show current USER program\n\r";
  static u8 u8String3[] = "****************************************************************\n\r";
  static bool bMenuOn = FALSE;
  static u8 u8State = 0;
  static u8 au8Buffer0[]={0};
  static u32 u32CommandNum = 0;
  static u8 au8Buffer[20]={0};
  static u8 au8Num1[10]={0};
  static u8 au8Num2[10]={0};
  static bool bPrint = FALSE;
  static u8 u8Num1_Message1[] = "Enter commands as LED-ONTIME-OFFTIME and press Enter\n\r";
  static u8 u8Num1_Message2[] = "Time is in milliseconds, max 100 commands\n\r";
  static u8 u8Num1_Message3[] = "LED colors : R, O, Y, G, C, B, P, W\n\r";
  static u8 u8Num1_Message4[] = "Example: R-100-2000(Red on at 100ms and off at 200ms)\n\r";
  static u8 u8Num1_Message5[] = "Press Enter on blank line to end\n\r";
  static u8 u8Num2_Message1[] = "Current USER program\n\r";
  static u8 u8Num2_Message2[] = "LED   ON TIME  OFF TIME\n\r";
  static u8 u8Num2_Message3[] = "-----------------------\n\r";
  static u8 u8Num2_Message7[] = "-----------Continue-input-----------\n\r";
  static u8 u8Num1_Message6[] = "Invalid command: incorrect format. Please use L-ONTIME-OFFTIME\n\r";
  static u8 u8Num2_Message4[] = "When show USER program, press 0 to WIPE DATA and reset\n\r";
  static u8 u8Num2_Message5[] = "When show USER program, press Enter to continue intut\n\r";
  static u8 u8Num2_Message6[] = "Command Number: ";
  static u8 u8FigureCounter1 = 0;
  static u8 u8FigureCounter2 = 0;
  static u8 u8CommandCounter = 0;
  static u8 bInputRight = TRUE;
  static LedCommandType order1[200];
  if(u8State==0)
  {
    u32CommandNum=0;
    if(bMenuOn==FALSE)
    {
      DebugPrintf(u8String0);
      DebugPrintf(u8String1);
      DebugPrintf(u8String2);
      DebugPrintf(u8String3);
      DebugPrintf(u8Num2_Message4);
      DebugPrintf(u8Num2_Message5);
      DebugPrintf(u8String3);
      bMenuOn = TRUE;
    }
    
    if(G_au8DebugScanfBuffer[0]=='1')
    {
      u8State = 1;
      bPrint = TRUE;
      DebugScanf(au8Buffer0);
      if(bPrint)
      {
        DebugLineFeed();
        DebugPrintf(u8Num1_Message1);
        DebugPrintf(u8Num1_Message2);
        DebugPrintf(u8Num1_Message3);
        DebugPrintf(u8Num1_Message4);
        DebugPrintf(u8Num1_Message5);
        bPrint = FALSE;
      }
    }
    if(G_au8DebugScanfBuffer[0]=='2')
    {
      u8State = 2;
      bPrint = TRUE;
      DebugScanf(au8Buffer0);
      if(bPrint)
      {
        DebugLineFeed();
        DebugPrintf(u8Num2_Message1);
        DebugPrintf(u8Num2_Message2);
        DebugPrintf(u8Num2_Message3);
        bPrint = FALSE;
      }
    }
  }
  if(u8State==1)
  {
    if(G_au8DebugScanfBuffer[0]==0x0d)
    {
      u8State = 2; 
      bPrint = TRUE;
      DebugScanf(au8Buffer0);
      if(bPrint)
      {
        DebugLineFeed();       
        u32CommandNum = (u8CommandCounter/2);       
        DebugPrintf(u8Num2_Message6);
        DebugPrintNumber(u32CommandNum);
        DebugLineFeed();
        DebugPrintf(u8Num2_Message1);
        DebugPrintf(u8Num2_Message2);
        DebugPrintf(u8Num2_Message3);
        for(u8 i=0;i<(u8CommandCounter/2);i++)
        {
          LedDisplayPrintListLine(i);
          DebugLineFeed();
        }
        DebugPrintf(u8Num2_Message3);
        bPrint = FALSE;
      }   
    }
    if(G_au8DebugScanfBuffer[G_u8DebugScanfCharCount-1]==0x0d)
    {
      bInputRight = TRUE;
      DebugScanf(au8Buffer);
      DebugLineFeed(); 
      if(au8Buffer[1]=='-')
      {
        switch(au8Buffer[0])
        {
        case 'R': 
        case 'O': 
        case 'Y': 
        case 'G': 
        case 'C': 
        case 'B': 
        case 'P': 
        case 'W': bInputRight = TRUE;break;
        default: bInputRight = FALSE;
        }
        for(u8 i=0;i<sizeof(au8Buffer);i++)
        {
          if(au8Buffer[i]==0x0d)
          {
            u8FigureCounter2=i;
          }
        }
        for(u8 i=2;i<sizeof(au8Buffer);i++)
        {
          if(au8Buffer[i]=='-')
          {
            u8FigureCounter1=i;
          }
        }
        for(u8 i=2;i<u8FigureCounter1;i++)
        {
          au8Num1[i-2]=au8Buffer[i];
        }
        for(u8 i=u8FigureCounter1+1;i<=u8FigureCounter2;i++)
        {
          au8Num2[i-(u8FigureCounter1+1)]=au8Buffer[i];
        }
      }
      else
      {
        bInputRight = FALSE;
      }
      
      if(bInputRight)
      {
        for(u8 i=0;i<u8FigureCounter1-2;i++)
        {
          switch(au8Num1[i])
          {
          case '0':
          case '1':
          case '2':
          case '3':
          case '4':
          case '5':
          case '6':
          case '7':
          case '8':
          case '9': bInputRight = TRUE;break;
          default: bInputRight = FALSE;
          }
        }
        if(bInputRight)
        {
          for(u8 i=0;i<(u8FigureCounter2-u8FigureCounter1-1);i++)
          {
            switch(au8Num2[i])
            {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9': bInputRight = TRUE;break;
            default: bInputRight = FALSE;
            }
          }
          
          if(bInputRight)
          {
            if(atoi((char*)au8Num1)>=atoi((char*)au8Num2))
            {
              bInputRight=FALSE;
            }
            if(bInputRight)
            {
              switch(au8Buffer[0])
              {
              case 'R': order1[u8CommandCounter].eLED = RED;break;
              case 'O': order1[u8CommandCounter].eLED = ORANGE;break;
              case 'Y': order1[u8CommandCounter].eLED = YELLOW;break;
              case 'G': order1[u8CommandCounter].eLED = GREEN;break;
              case 'C': order1[u8CommandCounter].eLED = CYAN;break;
              case 'B': order1[u8CommandCounter].eLED = BLUE;break;
              case 'P': order1[u8CommandCounter].eLED = PURPLE;break;
              case 'W': order1[u8CommandCounter].eLED = WHITE;break;
              default: bInputRight = FALSE;
              }         
              order1[u8CommandCounter].u32Time = atoi((char*)au8Num1);
              order1[u8CommandCounter].bOn = TRUE;
              order1[u8CommandCounter].eCurrentRate = LED_PWM_100;
              LedDisplayAddCommand(USER_LIST, &order1[u8CommandCounter]);
              u8CommandCounter++;
              order1[u8CommandCounter].u32Time = atoi((char*)au8Num2);
              order1[u8CommandCounter].eLED = order1[u8CommandCounter-1].eLED;
              order1[u8CommandCounter].bOn = FALSE;
              order1[u8CommandCounter].eCurrentRate = LED_PWM_0;
              LedDisplayAddCommand(USER_LIST, &order1[u8CommandCounter]);
              u8CommandCounter++;
              for(u8 i=0;i<10;i++)
              {
                au8Num1[i]=0;
                au8Num2[i]=0;
              }
              for(u8 i=0;i<20;i++)
              {
                au8Buffer[i]=0;
              }
            }
          }
        }
      }
      
      if(bInputRight==FALSE)
      {  
        DebugPrintf(u8Num1_Message6);
        DebugLineFeed();
        bInputRight = TRUE;   
      }
    }
  }
  if(u8State==2)
  {     
    if(G_au8DebugScanfBuffer[0]=='0')
    {
      u8State = 0; 
      bMenuOn = FALSE;
      LedDisplayStartList();
      DebugScanf(au8Buffer0);
    }
    if(G_au8DebugScanfBuffer[0]==0x0d)
    {
      u8State=1;
      DebugScanf(au8Buffer0);
      DebugPrintf(u8Num2_Message7);
    }
  }
} /* end UserApp1SM_Idle() */
                      
            
#if 0
/*-------------------------------------------------------------------------------------------------------------------*/
/* Handle an error */
static void UserApp1SM_Error(void)          
{
  
} /* end UserApp1SM_Error() */
#endif


/*-------------------------------------------------------------------------------------------------------------------*/
/* State to sit in if init failed */
static void UserApp1SM_FailedInit(void)          
{
    
} /* end UserApp1SM_FailedInit() */


/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
