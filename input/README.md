#Using the Input Handler
This should take <5 minutes (assuming you know how to program and you are familiar with C++ syntax)

#include InputHandler.h
#include KeyMapping.h

//You need to make an InputHandler object to handle things.
InputHandler* input = new InputHandler();

//You can define key to function mappings
//To create a new mapping, create a KeyMapping object
//since the number of axes, buttons, etc. are different for every game controller, you need to specify which game controller you are defining the mapping for in the constructor
KeyMapping* map1 = new KeyMapping("XBox One");//in this example, we have XBox One controller

//after you create the KeyMapping object, you can map the buttons to the functions you defined.
//if you want a toggle button (which is if you press it once, it turns something on to low, if you press it again, it turns it to hi, and if you press it again, it turns it off), then the function NEEDS to be of the form
	void toggleFunction(int states)
//InputHandler will keep track of the states for you, but you need to give us the number of states you have
//if you want a normal button (if you hold it, you keep the thrusters on), then the function needs to be of the form
	void buttonFunction(void)
//if you want an axis (the joysticks), then the function needs to be of the form
	void axisFunction(float joystickPosition)

//the function to map things is
//map("button name", func)
//for toggle it's map("button name", func, numberOfStates)

map1.map("x", myFunc1);
map1.map("y", myFunc2);
map1.map("z", myFunc3, 3);
map1.map("leftAxis", myFunc4);
...

//after you finish mapping, add the mapping to the InputHandler
input.put(map1);
//then call .handle() every time you need it to check your input
input.handle();