clear joystick
joystick = JoystickController();

while true
    [ax,btn] = joystick.getControllerStates;
    fprintf('ax: ');
    fprintf("%f ",ax);  
    fprintf('btn: ');
    fprintf("%d ",btn);
    fprintf("\n");
end