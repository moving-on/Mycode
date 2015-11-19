#include<iostream>
using namespace std;

class Command
{
public:
	virtual void execute()
	{

	}
};

class Light
{
public:
	void on()
	{
		cout << "Light is on" << endl;
	}
};

class LightOnCommand :public Command
{
private:
	Light light;
public:
	LightOnCommand(Light& light) :light(light){}
	void execute()
	{
		light.on();
	}
};

class noCommand :public Command
{
	void execute()
	{

	}
};

class RemoteControl
{
private:
	Command** onCommands;
	Command** offCommands;
public:
	RemoteControl()
	{
		onCommands = new Command*[7];
		offCommands = new Command*[7];
		for (int i = 0; i < 7; i++)
		{
			onCommands[i] = new noCommand();
			offCommands[i] = new noCommand();
		}
	}
	void setCommand(int slot, Command* onCommand, Command* offCommand)
	{
		onCommands[slot] = onCommand;
		offCommands[slot] = offCommand;
	}
	void onButtonWasPressed(int slot)
	{
		onCommands[slot]->execute();
	}
	void offButtonWasPressed(int slot)
	{
		offCommands[slot]->execute();
	}

};

class GarageDoor
{
public:
	void up()
	{
		cout << "up" << endl;
	}
	void down()
	{
		cout << "down" << endl;
	}
	void stop()
	{
		cout << "stop" << endl;
	}
};

class GarageDoorOpen :public Command
{
private:
	GarageDoor garageDoor;
public:
	GarageDoorOpen(GarageDoor& gd) :garageDoor(gd){}
	void execute()
	{
		garageDoor.up();
		garageDoor.down();
		garageDoor.stop();
	}
};

int main()
{
	SimpleRemoteControl remote;
	Light light;
	LightOnCommand* lightOn=new LightOnCommand(light);
	remote.setCommand(lightOn);
	remote.buttonWasPressed();
	GarageDoor garageDoor;
	GarageDoorOpen* garageOpen = new GarageDoorOpen(garageDoor);
	remote.setCommand(garageOpen);
	remote.buttonWasPressed();
}