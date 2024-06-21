classdef JoystickController < handle
    % JoystickController - A class for interfacing with a joystick in MATLAB
    %
    % This class provides an interface to interact with a joystick using the
    % SDL2 library through a MEX function (JoystickMex).
    %
    % Usage:
    %   js = JoystickController();  % Create a joystick controller object
    %   [axes, buttons] = js.getControllerStates();  % Get joystick state
    %   js.cleanup();  % Clean up resources when done
    %
    % Properties:
    %   None
    %
    % Methods:
    %   JoystickController() - Constructor
    %   initialize() - Initialize the joystick
    %   getControllerStates() - Get current joystick state
    %   cleanup() - Clean up joystick resources
    %   delete() - Destructor    
    methods
        function obj = JoystickController()
            % Constructor: Creates a new JoystickController object
            obj.initialize();
        end
        
        function initialize(obj)
            % Initialize joystick
            % This calls the 'init' command of the JoystickMex function
            JoystickMex('init');
        end
        
        function [axes, buttons] = getControllerStates(obj)
            % Retrieve the current state of joystick
            % Returns:
            %   axes: Normalized axis values (range: -1 to 1)
            %   buttons: Button states (0 for not pressed, 1 for pressed)
            [axes, buttons] = JoystickMex('get');
            axes = axes/32768; % Normalize axis values
        end
        
        function cleanup(obj)
            % Cleanup joystick resources
            % This should be called when you're done using the joystick
            JoystickMex('cleanup');
        end
        
        function delete(obj)
            % Destructor: Automatically called when the object is destroyed
            obj.cleanup();
        end
    end
end