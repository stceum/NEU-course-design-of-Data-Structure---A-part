#include "uiparts.h"
#include "elevator.h"

int main()
{
	Elevator e;
	ui u;
	//e.request(1, 3, 1);
	//e.request(12, 1, 10);
	//e.request(3, 5, 100);
	//e.request(2, 3, 200);
	while (true)
	{
		while (MouseHit())
		{
			switch (u.mousechoose())
			{
			case 0:
				break;
			case 1:
				u.inputbyhand(e);
				break;
			case 2:
				u.inputbyfile(e);
				break;
			case 3:
				u.inputbyrand(e);
				break;
			}
		}

		e.nexttask();
		u.refreshdata(e.tar);
		while (u.draw(e.stat, e))
		{
			while (MouseHit())
			{
				switch (u.mousechoose())
				{
				case 0:
					break;
				case 1:
					u.inputbyhand(e);
					break;
				case 2:
					u.inputbyfile(e);
					break;
				case 3:
					u.inputbyrand(e);
					break;
				}
			}
		};
		Sleep(1000);
		e.onoff();
	}
}