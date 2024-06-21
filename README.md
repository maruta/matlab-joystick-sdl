# Joystick Interface for MATLAB using SDL2

This project provides a MATLAB interface for joystick input using SDL2. It consists of a MATLAB class `JoystickController` and a C++ MEX file `JoystickMex` that enables communication between MATLAB and the joystick hardware.

## Usage

``` matlab
js = JoystickController();  % Create a joystick controller object
[axes, buttons] = js.getControllerStates();  % Get joystick state
js.cleanup();  % Clean up resources when done
```

## Compilation
Precompiled MEX files are provided for Windows x64. For other platforms, you need to compile the MEX file yourself.


