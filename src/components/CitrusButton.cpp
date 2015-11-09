#include "CitrusButton.h"

	// For buttons like X or Y pass in false for "axis", otherwise like the triggers on an xbox controller pass in true for "axis"
	CitrusButton::CitrusButton(Joystick *tstick, int tbutton, bool taxis, bool tneg)
	{
		axis = taxis;
		neg = tneg;
		output = false;
		oldInput = false;
		stick = tstick;
		button = tbutton;
	}

	CitrusButton::CitrusButton(Joystick *tstick, int tbutton)
	{
		axis = false;
		neg = false;
		output = false;
		oldInput = false;
		stick = tstick;
		button = tbutton;
	}

	CitrusButton::~CitrusButton() {

	}



	//All of these have clones with generic input. If we ever end up needing a button that's not from a joystick.

	//Call at the end of every loop (once per loop)!
	void CitrusButton::Update(bool input)
	{
		oldInput = input;
	}
	void CitrusButton::Update()
	{
		if (!axis) {
			Update(stick->GetRawButton(button));//Update(stick->GetRawButton(button));
		}
		else if (axis) {
			Update(stick->GetRawAxis(button));
		}
	}
	bool CitrusButton::ButtonClicked(bool input) const
	{
	//Return true if the button state changes from false to true. (not clicked to clicked)
		bool returnMe = false;
		if (input != oldInput && input == true)
		{
			returnMe = true;
		}
		return returnMe;
	}
	bool CitrusButton::ButtonClicked() const
	{
	//Return true if the button state changes from false to true. (not clicked to clicked)
		if (button > 0)
		{
			if(!axis) {
				return ButtonClicked(stick->GetRawButton(button));
			}
			else if (axis && neg) {
				return ButtonClicked(stick->GetRawAxis(button) < -0.5);
			}
			else if (axis && !neg) {
				return ButtonClicked(stick->GetRawAxis(button) > 0.5);
			}
		}
		return false;
	}
	bool CitrusButton::ButtonReleased(bool input) const
	//Return true if the button state changes from true to false. (clicked to not clicked)
	{
		bool returnMe = false;
		if (input != oldInput && input == false)
		{
			returnMe = true;
		}
		return returnMe;
	}
	bool CitrusButton::ButtonReleased() const
	{
	//Return true if the button state changes from true to false. (clicked to not clicked)
		if (button > 0)
		{
			if(!axis) {
				return ButtonReleased(stick->GetRawButton(button));
			}
			else if (axis && neg) {
				return ButtonReleased(stick->GetRawAxis(button) < -0.5);
			}
			else if (axis && !neg) {
				return ButtonReleased(stick->GetRawAxis(button) > 0.5);
			}
		}
		return false;
	}
	bool CitrusButton::ButtonPressed(bool input) const //only purpose is below. Why done this way?
	{
		return input;
	}
	bool CitrusButton::ButtonPressed() const //returns the state of the button
	{
		if (button > 0)
		{
			if(!axis) {
				return ButtonPressed(stick->GetRawButton(button));
			}
			else if (axis && neg) {
				return ButtonPressed(stick->GetRawAxis(button) < -0.5);
			}
			else if (axis && !neg) {
				return ButtonPressed(stick->GetRawAxis(button) > 0.5);
			}
		}
		return false;
	}

	//Reset to factory settings!
	void CitrusButton::Reset()
	{
		output = false;
		oldInput = false;
	}

	bool CitrusButton::ButtonState() const {
		return output;
	}


//Use the following like: input = TurnOn(myButton); input = Toggle(myButton, input);
bool TurnOn(CitrusButton *button) //used to undo below
{
	if (button->ButtonClicked())
	{
		return true;
	}
	return false;
}
bool TurnOff(CitrusButton *button) //if the button is clicked (see above) then return false
{
	if (button->ButtonClicked())
	{
		return false;
	}
	return true;
}
bool Toggle(CitrusButton *button, bool input)
//Toggle the results of clicking the button (see above). Used for clicked only. not pressed.
{
	if (button->ButtonClicked())
	{
		return !input;
	}
	return input;
}

