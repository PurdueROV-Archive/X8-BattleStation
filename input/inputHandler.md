initInputHandler()
	init SDL library
	while the program is running
		check if there's a new joystick
		if so
			update queue of joysticks
			assign button-to-function mapping
			show it on GUI
		check if there's a missing joystick
		if so
			update queue
			show it on GUI
		check if button from any joysticks were pressed
		if so
			call function

a vector of SDL_Joystick* will be used to hold joysticks






Questions
1. How do I know that a joystick is unplugged?
2. If someone unplugs and replugs really quickly, will it slow the button input from my program? And if so, how much?
3. If someone unpluags and replugs a new joystick, in between the two checks, how do I know if they are different joysticks? (will they have the same ID?)
4. how do I show it on GUI?
5. 