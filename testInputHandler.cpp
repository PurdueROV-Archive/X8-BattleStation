#include "testInputHandler.h"
void rotateFunc(float rotate)
{
    printf("rotate by %f\n", rotate);
}

void walkFunc(float rotate)
{
    printf("walk by %f\n", rotate);
}

void punch()
{
    printf("Punch!\n");
}

void kick(int state)
{
    if(state==0)
        printf("Kick!\n");
    if(state==1)
        printf("COMBO!\n");
    if(state==2)
        printf("SUPER COMBO!\n");
    if(state==3)
        printf("COMBO BREAKKKKKK\n");
}
void dodge()
{
    printf("dodge!?\n");
}
void slide(int state)
{
    printf("sliiiiide! State: %d\n", state);
}
void climbUp()
{
    printf("climbed up\n");
}

void climbDown()
{
    printf("climed down..\n");
}

void climbLeft()
{
    printf("climbing left\n");
}

void climbRight()
{
    printf("climbing right\n");
}
/*
int main(void)
{
    typedef void(*axisFunc)(float);
    typedef void(*buttonFunc)(void);
    std::vector<axisFunc> myAxisFuncs = {rotateFunc, walkFunc};
    std::vector<buttonFunc> myButtonFuncs = {punch, kick, dodge, slide, climbUp, climbDown, climbLeft, climbRight};
    InputHandler myInput;
    myInput.addJoystickAxis(myAxisFuncs);
    myInput.addButtons(myButtonFuncs);
    myInput.handle();
    return 1;
}*/
