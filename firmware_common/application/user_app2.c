/**********************************************************************************************************************
File: user_app2.c                                                                

Description:
This is a user_app2.c file template 

------------------------------------------------------------------------------------------------------------------------
API:

Public functions:


Protected System functions:
void UserApp2Initialize(void)
Runs required initialzation for the task.  Should only be called once in main init section.

void UserApp2RunActiveState(void)
Runs current task state.  Should only be called once in main loop.


**********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_UserApp2"
***********************************************************************************************************************/
/* New variables */
volatile u32 G_u32UserApp2Flags;                       /* Global state flags */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemFlags;                  /* From main.c */
extern volatile u32 G_u32ApplicationFlags;             /* From main.c */

extern volatile u32 G_u32SystemTime1ms;                /* From board-specific source file */
extern volatile u32 G_u32SystemTime1s;                 /* From board-specific source file */


/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "UserApp2_" and be declared as static.
***********************************************************************************************************************/
static fnCode_type UserApp2_StateMachine;            /* The state machine function pointer */
//static u32 UserApp2_u32Timeout;                      /* Timeout counter used across states */


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
Function: UserApp2Initialize

Description:
Initializes the State Machine and its variables.

Requires:
  -

Promises:
  - 
*/
void UserApp2Initialize(void)
{
  /* If good initialization, set state to Idle */
  if( 1 )
  {
    UserApp2_StateMachine = UserApp2SM_Idle;
  }
  else
  {
    /* The task isn't properly initialized, so shut it down and don't run */
    UserApp2_StateMachine = UserApp2SM_FailedInit;
  }

  LedPWM(RED0,   LED_PWM_100);
  LedPWM(GREEN0, LED_PWM_0);
  LedPWM(BLUE0,  LED_PWM_0);
  
  LedPWM(RED1,   LED_PWM_100);
  LedPWM(GREEN1, LED_PWM_0);
  LedPWM(BLUE1,  LED_PWM_0);
  
  LedPWM(RED2,   LED_PWM_100);
  LedPWM(GREEN2, LED_PWM_0);
  LedPWM(BLUE2,  LED_PWM_0);
  
  LedPWM(RED3,   LED_PWM_100);
  LedPWM(GREEN3, LED_PWM_0);
  LedPWM(BLUE3,  LED_PWM_0);
  
  
  
  
} /* end UserApp2Initialize() */

  
/*----------------------------------------------------------------------------------------------------------------------
Function UserApp2RunActiveState()

Description:
Selects and runs one iteration of the current state in the state machine.
All state machines have a TOTAL of 1ms to execute, so on average n state machines
may take 1ms / n to execute.

Requires:
  - State machine function pointer points at current state

Promises:
  - Calls the function to pointed by the state machine function pointer
*/
void UserApp2RunActiveState(void)
{
  UserApp2_StateMachine();

  
  
  
     /*LED Cycling - LEDs alternating in sync 7/6th*/
  static LedNumberType aeCurrentLed[] = {GREEN0, RED0, BLUE0, GREEN0, RED0, BLUE0};
    static LedNumberType aeCurrentLed1[] = {GREEN1, RED1, BLUE1, GREEN1, RED1, BLUE1};
    static LedNumberType aeCurrentLed2[] = {GREEN2, RED2, BLUE2, GREEN2, RED2, BLUE2};
    static LedNumberType aeCurrentLed3[] = {GREEN3, RED3, BLUE3, GREEN3, RED3, BLUE3};
  static bool abLedRateIncreasing[] = {TRUE, FALSE, TRUE, FALSE, TRUE, FALSE};
  static u8 u8CurrentLedIndex = 0;
    static u8 u8CurrentLedIndex1 = 0;
    static u8 u8CurrentLedIndex2 = 0;
    static u8 u8CurrentLedIndex3 = 0;
  static u8 u8CurrentLedLevel;
    static u8 u8CurrentLedLevel1 = 0;
    static u8 u8CurrentLedLevel2 = 0;
    static u8 u8CurrentLedLevel3 = 0;
  static u8 u8DutyCycleCounter = 0;
    static u8 u8DutyCycleCounter1 = 0;
    static u8 u8DutyCycleCounter2 = 0;
    static u8 u8DutyCycleCounter3 = 0;
  static u16 u16Counter = COLOUR_CYCLE_TIME;
  static u16 u16CycleTracker = 0;

  
  u16Counter--;
  if(u16Counter == 0){ /*Check if its time to change colours*/
    u16Counter = COLOUR_CYCLE_TIME;
   u16CycleTracker++;
   
   if(u16CycleTracker%49 ==  0){
      if(abLedRateIncreasing[u8CurrentLedIndex]){ /*Check if value is increasing or decreasing*/
        u8CurrentLedLevel++;
      }else{
        u8CurrentLedLevel--;
      }
     
      u8DutyCycleCounter++;
        if(u8DutyCycleCounter == 20){ /*Check if light is at its maximum*/
          u8DutyCycleCounter = 0;
          
          u8CurrentLedIndex++;
          if(u8CurrentLedIndex == sizeof(aeCurrentLed)){ /*Check if we're at the end of the Array*/
            u8CurrentLedIndex = 0;
          }
        }    
   }
        
      /***LED1***/
    if(u16CycleTracker%25 ==  0){
      if(abLedRateIncreasing[u8CurrentLedIndex1]){ /*Check if value is increasing or decreasing*/
        u8CurrentLedLevel1++;
      }else{
        u8CurrentLedLevel1--;
      }
      
      u8DutyCycleCounter1++;
        if(u8DutyCycleCounter1 == 20){ /*Check if light is at its maximum*/
          u8DutyCycleCounter1 = 0;
          
          u8CurrentLedIndex1++;
          if(u8CurrentLedIndex1 == sizeof(aeCurrentLed)){ /*Check if we're at the end of the Array*/
            u8CurrentLedIndex1 = 0;
          }
        }    
    }
   
      /***LED2***/
    if(u16CycleTracker%13 ==  0){
      if(abLedRateIncreasing[u8CurrentLedIndex2]){ /*Check if value is increasing or decreasing*/
        u8CurrentLedLevel2++;
      }else{
        u8CurrentLedLevel2--;
      }
      
      u8DutyCycleCounter2++;
        if(u8DutyCycleCounter2 == 20){ /*Check if light is at its maximum*/
          u8DutyCycleCounter2 = 0;
          
          u8CurrentLedIndex2++;
          if(u8CurrentLedIndex2 == sizeof(aeCurrentLed)){ /*Check if we're at the end of the Array*/
            u8CurrentLedIndex2 = 0;
          }
        }  
    }
      
      /***LED3***/
    if(u16CycleTracker%7 ==  0){
      if(abLedRateIncreasing[u8CurrentLedIndex3]){ /*Check if value is increasing or decreasing*/
        u8CurrentLedLevel3++;
      }else{
        u8CurrentLedLevel3--;
      }
      
      u8DutyCycleCounter3++;
        if(u8DutyCycleCounter3 == 20){ /*Check if light is at its maximum*/
          u8DutyCycleCounter3 = 0;
          
          u8CurrentLedIndex3++;
          if(u8CurrentLedIndex3 == sizeof(aeCurrentLed)){ /*Check if we're at the end of the Array*/
            u8CurrentLedIndex3 = 0;
          }
        }  
    }
      
      LedPWM( (LedNumberType)aeCurrentLed[u8CurrentLedIndex], (LedRateType)u8CurrentLedLevel);
      LedPWM( (LedNumberType)aeCurrentLed1[u8CurrentLedIndex1], (LedRateType)u8CurrentLedLevel1);
      LedPWM( (LedNumberType)aeCurrentLed2[u8CurrentLedIndex2], (LedRateType)u8CurrentLedLevel2);
      LedPWM( (LedNumberType)aeCurrentLed3[u8CurrentLedIndex3], (LedRateType)u8CurrentLedLevel3);
      
      if(u16CycleTracker == 15925)
        u16CycleTracker = 0;
  }
  
} /* end UserApp2RunActiveState */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Private functions                                                                                                  */
/*--------------------------------------------------------------------------------------------------------------------*/


/**********************************************************************************************************************
State Machine Function Definitions
**********************************************************************************************************************/

/*-------------------------------------------------------------------------------------------------------------------*/
/* Wait for ??? */
static void UserApp2SM_Idle(void)
{
    
} /* end UserApp2SM_Idle() */
     
#if 0
/*-------------------------------------------------------------------------------------------------------------------*/
/* Handle an error */
static void UserApp2SM_Error(void)          
{
  
} /* end UserApp2SM_Error() */
#endif


/*-------------------------------------------------------------------------------------------------------------------*/
/* State to sit in if init failed */
static void UserApp2SM_FailedInit(void)          
{
    
} /* end UserApp2SM_FailedInit() */


/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
