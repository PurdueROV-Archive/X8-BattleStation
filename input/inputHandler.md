initInputHandler()
	init SDL library
	call handleJoysticks()

handleJoysticks()
	check if there's a new joystick
	if there is
		update queue of joysticks
		create a new Joystick object (which includes # of buttons and mapping assigned)
		show it on GUI
	check if a joystick has been unplugged
	if so
		update queue
		delete Joystick objects
		show it on GUI
	check if buttons from any joysticks were pressed
	if so
		call mapped function






Questions
1. How do I know that a joystick is unplugged?
2. If someone unplugs and replugs really quickly, will it slow the button input from my program? And if so, how much?
3. If someone unpluags and replugs a new joystick, in between the two checks, how do I know if they are different joysticks? (will they have the same ID?)
4. how do I show it on GUI?
5. 