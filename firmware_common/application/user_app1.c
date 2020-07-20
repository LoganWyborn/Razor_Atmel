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

static void rockDraw(tRockObject sTargetRock)
{
  static u8 j, k;
  for(j = sTargetRock.u8XPosition; j < (sTargetRock.u8XPosition + sTargetRock.u8Size); j++)
    for(k = sTargetRock.u8YPosition; k < (sTargetRock.u8YPosition + sTargetRock.u8Size); k++)
      LcdSetPixel(k, j);
}

static void rockSelector(bool *abExists, tRockObject sRock0, tRockObject sRock1, tRockObject sRock2, tRockObject sRock3,
                         tRockObject sRock4, tRockObject sRock5, tRockObject sRock6, tRockObject sRock7, 
                         tRockObject sRock8, tRockObject sRock9)
{
  static u8 u8SelectedRock;
  u8SelectedRock = rand() % 10;
  if(!abExists[u8SelectedRock]) /* If it doesn't already exist, make it exist. */
  {
    abExists[u8SelectedRock] = TRUE;
    
    if(u8SelectedRock == 0)
      rockInitializer(sRock0);
    else if(u8SelectedRock == 1)
      rockIntializer(sRock1);
    else if(u8SelectedRock == 2)
      rockIntializer(sRock2);
    else if(u8SelectedRock == 3)
      rockIntializer(sRock3);
    else if(u8SelectedRock == 4)
      rockIntializer(sRock4);
    else if(u8SelectedRock == 5)
      rockIntializer(sRock5);
    else if(u8SelectedRock == 6)
      rockIntializer(sRock6);
    else if(u8SelectedRock == 7)
      rockIntializer(sRock7);
    else if(u8SelectedRock == 8)
      rockIntializer(sRock8);
    else if(u8SelectedRock == 9)
      rockIntializer(sRock9);
  }
}

static void rockInitializer(tRockObject sTargetRock)
{
  u8 u8Temp;
  static u8 u8StartingSide = (rand() % 4);
  if(u8StartingSide == 0)       //Start on TOP
  {
    sTargetRock.u8Direction  = ((rand() % 7) + 5);
    sTargetRock.u8YPosition = 0;
    sTargetRock.u8XPosition = (rand() % (127 - sTargetRock.u8Size));
    
    
  }else if(u8StartingSide == 1) //Start on LEFT
  {
    sTargetRock.u8Direction  = ((rand() % 7) + 9);
    sTargetRock.u8XPosition = 0;
    sTargetRock.u8YPosition = (rand() % (63 - sTargetRock.u8Size));
    
  }else if(u8StartingSide == 2) //Start on BOTTOM
  {
    /* MUST differentiate directions 13-15 from 0-3 */
    u8Temp = ((rand() % 7) + 13);
    if(u8Temp > 15)
      u8Temp -= 16;
    sTargetRock.u8Direction = u8Temp;
    sTargetRock.u8YPosition = (63 - sTargetRock.u8Size);
    sTargetRock.u8XPositon = (rand() % (127 - sTargetRock.u8Size));
    
  }else                         //Start on RIGHT
  {
    sTargetRock.u8Direction  = ((rand() % 7) + 1);
    sTargetRock.u8XPosition = (127 - sTargetRock.u8Size);
    sTargetRock.u8YPosition = (rand() % (63 - sTargetRock.u8Size));
    
  }/* End of diretion selector */
  
  if(sTargetRock.u8Direction == 0)
  {
    
  }
  
}

static void rockActiveCheck(bool *abExists, tRockObject sRock0, tRockObject sRock1, tRockObject sRock2,
                       tRockObject sRock3, tRockObject sRock4, tRockObject sRock5, tRockObject sRock6,
                       tRockObject sRock7, tRockObject sRock8, tRockObject sRock9)
{
  if(abExists[0])
  {
    rockMovement(sRock0);
  }
  if(abExists[1])
  {
    rockMovement(sRock1);
  }
  if(abExists[2])
  {
    rockMovement(sRock2);
  }
  if(abExists[3])
  {
    rockMovement(sRock3);
  }
  if(abExists[4])
  {
    rockMovement(sRock4);
  }
  if(abExists[5])
  {
    rockMovement(sRock5);
  }
  if(abExists[6])
  {
    rockMovement(sRock6);
  }
  if(abExists[7])
  {
    rockMovement(sRock7);
  }
  if(abExists[8])
  {
    rockMovement(sRock8);
  }
  if(abExists[9])
  {
    rockMovement(sRock9);
  }
}

static void rockMovement(tRockObject sTargetRock)
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
  static u16 u16CurrentScore;
  static bool bDisplayUpdate = TRUE;
  static u8 u8GameSpeedMultiplier = 1;
  static PixelAddressType sTargetPixel = {0, 0};
  static u8 i; /* Iterator variable for loops */
  
  //Object Declarations
  static tPlayerObject sPlayer;
  
  static tRockObject sRockObject0;
  sRockObject0.u8Size = 5;
  sRockObject0.fSpeedFactor = 0.5;
  static tRockObject sRockObject1;
  sRockObject1.u8Size = 4;
  sRockObject1.fSpeedFactor = 1;
  static tRockObject sRockObject2;
  sRockObject2.u8Size = 4;
  sRockObject2.fSpeedFactor = 1.3;
  static tRockObject sRockObject3;
  sRockObject3.u8Size = 3;
  sRockObject3.fSpeedFactor = 1.2;
  static tRockObject sRockObject4;
  sRockObject4.u8Size = 3;
  sRockObject4.fSpeedFactor = 1.3;
  static tRockObject sRockObject5;
  sRockObject5.u8Size = 3;
  sRockObject5.fSpeedFactor = 1.4;
  static tRockObject sRockObject6;
  sRockObject6.u8Size = 2;
  sRockObject6.fSpeedFactor = 1.5;
  static tRockObject sRockObject7;
  sRockObject7.u8Size = 2;
  sRockObject7.fSpeedFactor = 1.5;
  static tRockObject sRockObject8;
  sRockObject8.u8Size = 2;
  sRockObject8.fSpeedFactor = 2;
  static tRockObject sRockObject9;
  sRockObject9.u8Size = 2;
  sRockObject9.fSpeedFactor = 2;
  
  static bool abDoesRockExist[10];  
  
  if(u8CurrentState == 0) /* MAIN MENU STATE ------------------------------------------------------ */
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
  }else if(u8CurrentState == 1) /* Initialize Game ------------------------------------------------ */
  {
    srand(G_u32SystemTime1ms);
    for(u8 i = 0; i < 10; i++)
      abDoesRockExist[i] = FALSE;
    bDisplayUpdate = TRUE;
    u16CurrentScore = 0;
    CapTouchOn();
    u8CurrentState = 2;
  }else if(u8CurrentState == 2) /* Gamelay Time!! ------------------------------------------------- */
  {
    //Timer Functions
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
        sTargetPixel.u16PixelRowAddress = 3;
        LcdSetPixel(&sTargetPixel);
        sTargetPixel.u16PixelRowAddress = 124;
        LcdSetPixel(&sTargetPixel);
        sTargetPixel.u16PixelColumnAddress = i;
      }
      for(i = 4; i < 124; i++)
      {
        sTargetPixel.u16PixelColumnAddress = 3;
        LcdSetPixel(&sTargetPixel);
        sTargetPixel.u16PixelColumnAddress = 60;
        LcdSetPixel(&sTargetPixel);
        sTargetPixel.u16PixelRowAddress = i;
      }
      
      //Draw all active rock objects
      if(abDoesRockExist[0])
      {
        rockDraw(sRockObject0);
      }
      if(abDoesRockExist[1])
      {
        rockDraw(sRockObject1);
      }
      if(abDoesRockExist[2])
      {
        rockDraw(sRockObject2);
      }
      if(abDoesRockExist[3])
      {
        rockDraw(sRockObject3);
      }
      if(abDoesRockExist[4])
      {
        rockDraw(sRockObject4);
      }
      if(abDoesRockExist[5])
      {
        rockDraw(sRockObject5);
      }
      if(abDoesRockExist[6])
      {
        rockDraw(sRockObject6);
      }
      if(abDoesRockExist[7])
      {
        rockDraw(sRockObject7);
      }
      if(abDoesRockExist[8])
      {
        rockDraw(sRockObject8);
      }
      if(abDoesRockExist[9])
      {
       rockDraw(sRockObject9); 
      }
      
      //Draw player
      
      
      //Write score, life information maybe game speed?
      
     bDisplayUpdate = FALSE; 
    }                       /* END OF GENERATE DISPLAY */
    
    if((u32GameTimer % 200) == 0||u32GameTimer < 5)/* Attempt to generate a rock */
    {
      rockSelector(&abDoesRockExist, sRockObject0, sRockObject1, sRockObject2, sRockObject3, sRockObject4,
                                    sRockObject5, sRockObject6, sRockObject7, sRockObject8, sRockObject9);  
    }/* End of rock generation */
    
    if(u32GameTimer % 30 == 0)/* Check if rocks exist - if they do, move them. */
    {
      rockActiveCheck(&abDoesRockExist, sRockObject0, sRockObject1, sRockObject2, sRockObject3, sRockObject4,
                                     sRockObject5, sRockObject6, sRockObject7, sRockObject8, sRockObject9);
    }
      
      
    /* END OF ACTIVE GAMEPLAY */
  }else if(u8CurrentState == 3) /* Update High Score and pass back to S0 */
  {
    if(u16CurrentScore > u16HighScore)
      u16HighScore = u16CurrentScore;
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
