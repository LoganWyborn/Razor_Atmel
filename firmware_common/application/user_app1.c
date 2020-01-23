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
static void displayMainMenu(u16 highScore)
{
  static PixelAddressType sStartPixel = {LCD_SMALL_FONT_LINE2, LCD_LEFT_MOST_COLUMN};
  static u8 au8HighScore[11];
  NumberToAscii(highScore, au8HighScore);
  
  LcdClearScreen();
  LcdLoadString("    Welcome To :", LCD_FONT_SMALL, &sStartPixel); 
  sStartPixel.u16PixelRowAddress = LCD_SMALL_FONT_LINE3;
  LcdLoadString("   *SPACE++ROCKS*", LCD_FONT_SMALL, &sStartPixel);
  sStartPixel.u16PixelRowAddress = LCD_SMALL_FONT_LINE6;
  LcdLoadString("High Score : ", LCD_FONT_SMALL, &sStartPixel);
  sStartPixel.u16PixelRowAddress = LCD_SMALL_FONT_LINE7;
  LcdLoadString(au8HighScore, LCD_FONT_SMALL, &sStartPixel);
}

static void rockInitialize(tRockObject tTargetRock)
{
  
}

/**********************************************************************************************************************
State Machine Function Definitions
**********************************************************************************************************************/

/*-------------------------------------------------------------------------------------------------------------------*/
/* Wait for ??? */
static void UserApp1SM_Idle(void)
{
  static u32 u32GameTimer = 0;
  static u8 u8CurrentState = 0;
  static u16 u16HighScore = 0;
  static bool bDisplayUpdate = TRUE;
  static u8 u8GameSpeedMultiplier = 1;
  static PixelAddressType sTargetPixel = {0, 0};
  static u8 i; /* Iterator variable for loops */
  
  //Object Declarations
  static tPlayerObject sPlayer;
  static tRockObject sRockObject0;
  sRockObject0.u8Size = 5;
  sRockObject0.u8SpeedFactor = 0.5;
  static tRockObject sRockObject1;
  sRockObject1.u8Size = 4;
  sRockObject1.u8SpeedFactor = 1;
  static tRockObject sRockObject2;
  sRockObject2.u8Size = 4;
  sRockObject2.u8SpeedFactor = 1.3;
  static tRockObject sRockObject3;
  sRockObject3.u8Size = 3;
  sRockObject3.u8SpeedFactor = 1.2;
  static tRockObject sRockObject4;
  sRockObject4.u8Size = 3;
  sRockObject4.u8SpeedFactor = 1.3;
  static tRockObject sRockObject5;
  sRockObject5.u8Size = 3;
  sRockObject5.u8SpeedFactor = 1.4;
  static tRockObject sRockObject6;
  sRockObject6.u8Size = 2;
  sRockObject6.u8SpeedFactor = 1.5;
  static tRockObject sRockObject7;
  sRockObject7.u8Size = 2;
  sRockObject7.u8SpeedFactor = 1.5;
  static tRockObject sRockObject8;
  sRockObject8.u8Size = 2;
  sRockObject8.u8SpeedFactor = 2;
  static tRockObject sRockObject9;
  sRockObject9.u8Size = 2;
  sRockObject9.u8SpeedFactor = 2;
  static bool abDoesRockExist[10];  
  
  if(u8CurrentState == 0) /* MAIN MENU STATE */
  {
    if(bDisplayUpdate)
    {
      displayMainMenu(u16HighScore);
      bDisplayUpdate = FALSE;
    }
    if(WasButtonPressed(BUTTON0))
    {
      ButtonAcknowledge(BUTTON0);
      u8CurrentState = 1;
    }
  }else if(u8CurrentState == 1) /* Initialize Game */
  {
    for(u8 i = 0; i < 10; i++)
      abDoesRockExist[i] = TRUE;
    bDisplayUpdate = TRUE;
    CapTouchOn();
    u8CurrentState = 2;
  }else if(u8CurrentState == 2) /* Gamelay Time!! */
  {
    u32GameTimer++;
    if(u32GameTimer % 30 == 0)
    {
      bDisplayUpdate = TRUE;
    }
    if(bDisplayUpdate) /* Generate Game Display */
    {
      LcdClearScreen();
      
      //Draw a border around the gameplay area
      sTargetPixel.u16PixelColumnAddress = 3;
      sTargetPixel.u16PixelRowAddress = 3;
      for(i = 4; i <= 60; i++)
      {
        LcdSetPixel(&sTargetPixel);
        sTargetPixel.u16PixelColumnAddress = i;
      }
      for(i = 
      
      
      //Draw all active rock objects
      
      
      //Draw player
      
      
      //Write score, life information maybe game speed?
      
      
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
