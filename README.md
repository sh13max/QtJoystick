# QtJoystick
Joystick

##Regitration in QML Engine
```C++
qmlRegisterType<Joystick>("SomeModuleName", 1, 0, "Joystick");
```

##Using in QML
```QML
import SomeModuleName 1.0
Window{
	visible: true;
    width: 640;
    height: 480;
    title: qsTr("Joystick");
	Joystick{
	    width: 50 * Screen.logicalPixelDensity;
	    height: 50 * Screen.logicalPixelDensity;
	    color: "#000000";
	    background: "#aa000000";
	    borderWidth: 5;
	}
}
```