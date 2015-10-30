#include "WPILib.h"

//include guards
#ifndef CITRUSBUTTON_H
#define CITRUSBUTTON_H

//Designed to get input from joysticks & manipulators.
class CitrusButton
{
	bool output;
	bool oldInput;

	//Optional.
	Joystick *stick;
	int button;
public:
	
	CitrusButton(Joystick *tstick, int tbutton);
	
	~CitrusButton();


	//All of these have clones with generic input. If we ever end up needing a button that's not from a joystick.

	//Call at the end of every loop (once per loop)!
	void Update(bool input);

	void Update();

	bool ButtonClicked(bool input) const;

	bool ButtonClicked() const;

	bool ButtonReleased(bool input) const;

	bool ButtonReleased() const;

	bool ButtonPressed(bool input) const;

	bool ButtonPressed() const;

	bool ButtonState() const;

	//Reset to factory settings!
	void Reset();


};

//Use the following like: input = TurnOn(myButton); input = Toggle(myButton, input);
bool TurnOn(CitrusButton *button);

bool TurnOff(CitrusButton *button);

bool Toggle(CitrusButton *button, bool input);

#endif //CITRUSBUTTON_H
