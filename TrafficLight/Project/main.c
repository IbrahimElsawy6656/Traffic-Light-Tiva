#include "stdint.h"
#include "stdbool.h"

#include "Driverlib/tm4c123gh6pm.h"
#include "Driverlib/Timer1A.h"
#include "Driverlib/Timer0A.h"
#include "Driverlib/GPIOA.h"
#include "Driverlib/GPIOB.h"
#include "Driverlib/Systick.h"
#include "Driverlib/UART0.h"

static volatile char currentSwitch;

void portAInit (void){

  enablePortAClock();

  setPortAPinOutput(0x02); //RED 1  (RIGHT-UP) - (NORTH-SOUTH)
  setPortAPinOutput(0x03); //GREEN 1
  setPortAPinOutput(0x04); //YELLOW 1

  setPortAPinOutput(0x05); //RED 2  (LEFT-DOWN) - (EAST-WEST)
  setPortAPinOutput(0x06); //GREEN 2
  setPortAPinOutput(0x07); //YELLOW 2


}
void portBInit (void){

    enablePortBClock();

    setPortBPinOutput(0x00); //RED 3   (LEFT-UP) - ( RELATED TO TRAFFIC LIGHT 1 - (NORTH-SOUTH) )
    setPortBPinOutput(0x01); //GREEN 3

    setPortBPinOutput(0x02); //RED 4   (RIGHT-DOWN) ( RELATED TO TRAFFIC LIGHT 2 - (EAST-WEST) )
    setPortBPinOutput(0x03); //GREEN 4

    setPortBPinInput(0x05);  //Switch 3 (LEFT-UP)
    setPortBPinInput(0x06);  //Switch 4 (RIGHT-DOWN)

    enablePortBNVIC ();    //Enable NVIC for PORT B
    enablePortBInt (0x05); //Enable interrupts for switch 3 in PIN 0x05 PORT B
    enablePortBInt (0x06); //Enable interrupts for switch 4 in PIN 0x06 PORT B

    setPortBPriority (0x03);
}
void Timer0Init (void){

    enableTimer0AClock ();
    disableTimer0A ();
    configTimer0A ();
    enableTimer0AInt();
    setTimer0APriority (0x01);
}
void Timer1Init (){

    enableTimer1AClock ();
    disableTimer1A ();
    configTimer1A ();
    enableTimer1AInt();
    setTimer1APriority (0x04);
}

void SystickInit (void){

    disableSystick ();
    enableSystickInt();
    setSystickPriority (0x02);
}

void initialState(void)
{

    setTimer0ALoad(0x05);
    writePortAPin(0x05, 0x01); //Enable Red 2
    writePortAPin(0x03, 0x01); //Enable Green 1
    writePortBPin(0x00, 0x01); //Enable Red 3
    writePortBPin(0x03, 0x01); //Enable Green 4
    disablePortBInt(0x06);  //Disable switch 4 interrupt
    enableTimer0A();
}
void main(void)
{

    //System Initialization

    UART0init();
    Timer0Init ();
    portBInit ();
    Timer1Init ();
    SystickInit ();
    portAInit ();
    initialState();


    while(1)
    {

    }
}


void Timer0_Handler (void)
{
    //Traffic Lights States

    static int state = 0;
    clearTimer0AFlag();

    if(state == 0)
    {
     disablePortBInt(0x05); //Disable interrupt switch 3
     writePortAPin(0x03, 0x00); //Disable Green 1
     writePortAPin(0x04, 0x01); //Enable Yellow 1

     state++;
     setTimer0ALoad(0x03);
    }
    else if (state == 1) //PEDESTRIAN NORTH SOUTH
    {
    sendState("PEDESTRIAN NORTH-SOUTH\n\r");
    writePortAPin(0x04, 0x00); //Disable Yellow 1
    writePortAPin(0x02, 0x01); //Enable Red 1
    writePortBPin(0x00, 0x00); //Disable red 3
    writePortBPin(0x01, 0X01); //Enable Green 3

    state++;
    setTimer0ALoad(0x01);
    }
    else if (state == 2) //CARS EAST WEST
    {
        sendState("CARS EAST-WEST\n\r");
        writePortAPin(0x05, 0x00); //Disable Red 2
        writePortAPin(0x06, 0x01); //Enable Green 2
        writePortBPin(0x03, 0x00); //disable green 4
        writePortBPin(0x02, 0x01); //enable red 4
        clearPortBFlag(0x06); //Clear switch 4 flag
        enablePortBInt(0x06);  //Enable interrupts switch 4

        state++;
        setTimer0ALoad(0x05);
    }
    else if (state == 3)
    {
        disablePortBInt(0x06); //Disable interrupts switch 4
        writePortAPin(0x06, 0x00); //Disable Green 2
        writePortAPin(0x07, 0x01); //Enable Yellow 2



        state++;
        setTimer0ALoad(0x03);
    }
    else if(state == 4) //PEDESTRAIN EAST-WEST
    {
        sendState("PEDESTRAIN EAST-WEST\n\r");
        writePortAPin(0x07, 0x00); //Disable Yellow 2
        writePortAPin(0x05, 0x01); //Enable Red 2
        writePortBPin(0x02, 0x00); //Disable red 4
        writePortBPin(0x03, 0x01); //Enable green 4

        state++;
        setTimer0ALoad(0x01);
    }
    else if (state == 5) // CARS NORTH-SOUTH
    {
        sendState("CARS NORTH-SOUTH\n\r");
        writePortAPin(0x02, 0x00); //Disable Red 1
        writePortAPin(0x03, 0x01); //Enable Green 1
        writePortBPin(0x00, 0x01); //Enable red 3
        writePortBPin(0x01, 0x00); //Disable green 3

        clearPortBFlag(0x05); //Clear switch 3 flag
        enablePortBInt(0x05); //Enable interrupts switch 3

        state = 0;
        setTimer0ALoad(0x05);
    }

}


void Timer1_Handler (void)
{
    //Two seconds pedestrian traffic

    disableTimer1A();  //Disable timer1
    clearTimer1AFlag(); //Clear interrupt timer1

    //Turn red for Pedestrian Traffic and green for Cars Traffic
    if(currentSwitch == 0x05) //Switch 3
    {
        sendState("CARS NORTH-SOUTH\n\r");
        writePortBPin(0x01, 0x00); //Disable Green 3
        writePortBPin(0x00, 0x01); //Enable Red 3
        writePortAPin(0x03, 0x01); //Enable Green 1
        writePortAPin(0x02, 0x00); //Disable Red 1
    }
    else if (currentSwitch == 0x06) //Switch 4
    {
        sendState("CARS EAST-WEST\n\r");
        writePortBPin(0x03, 0x00); //Disable Green 4
        writePortBPin(0x02, 0x01); //Enable Red 4
        writePortAPin(0x06, 0x01); //Enable Green 2
        writePortAPin(0x05, 0x00); //Disable Red 2
    }
    clearPortBFlag(currentSwitch); //Clear interrupts for pressed switch
    enableTimer0A(); //Enable timer0

    setSysTickLoad(0x01); //Setload systick
    enableSystick(); //Enable Systick

}


void Systick_Handler (void)
{
   //Case one second delay


    disableSystick(); //Disable systick
    enablePortBInt(currentSwitch); //Enable interrupts for previous pressed button

}


void PortB_Handler (void)
{
    //Switches Pressed

    disableTimer0A();  //Disable timer0

    if(readPortBFlag(0x05) == 0x01) //Detecting pressed switch
    {
       currentSwitch = 0x05;
    }
    else if (readPortBFlag(0x06) == 0x01)
        currentSwitch = 0x06;

    clearPortBFlag(currentSwitch); //Clear interrupt for pressed switch
    disablePortBInt(currentSwitch); //Disable interrupts for pressed switch

    //Turn green for Pedestrian Traffic and red for Cars Traffic
    if(currentSwitch == 0x05) //Switch 3
    {
        sendState("PEDESTRAIN NORTH-SOUTH\n\r");
        writePortBPin(0x01, 0x01); //Enable Green 3
        writePortBPin(0x00, 0x00); //Disable Red 3
        writePortAPin(0x03, 0x00); //Disable Green 1
        writePortAPin(0x02, 0x01); //Enable Red 1
    }
    else if (currentSwitch == 0x06) //Switch 4
    {
        sendState("PEDESTRAIN EAST-WEST\n\r");
        writePortBPin(0x03, 0x01); //Enable Green 4
        writePortBPin(0x02, 0x00); //Disable Red 4
        writePortAPin(0x06, 0x00); //Disable Green 2
        writePortAPin(0x05, 0x01); //Enable Red 2
    }

    setTimer1ALoad(0x02); //Setload timer1
    enableTimer1A(); //Enable timer1

}








