#include <iostream>
#include <vector>
#include "mex.h"
#include <SDL.h>

class Joystick {
private:
    SDL_Joystick* aJoystick;
    bool isInitialized;

public:
    Joystick() : aJoystick(nullptr), isInitialized(false) {}

    ~Joystick() {
        if (isInitialized) {
            cleanup();
        }
    }

    void initialize() {
        if (SDL_Init(SDL_INIT_JOYSTICK) < 0) {
            mexErrMsgTxt("SDL could not initialize!");
        }
        SDL_JoystickEventState(SDL_ENABLE);
        aJoystick = SDL_JoystickOpen(0);
        if (!aJoystick) {
            mexErrMsgTxt("Unable to open the first joystick.");
        }
        isInitialized = true;
    }

    void cleanup() {
        if (aJoystick) {
            SDL_JoystickClose(aJoystick);
        }
        SDL_Quit();
        isInitialized = false;
    }

    void getControllerStates(std::vector<double>& jsAxes, std::vector<double>& jsButtons) {
        if (!isInitialized || !aJoystick) {
            mexErrMsgTxt("Joystick not initialized or opened.");
        }
        SDL_JoystickUpdate();
        int nAxes = SDL_JoystickNumAxes(aJoystick);
        int nButtons = SDL_JoystickNumButtons(aJoystick);
        jsAxes.resize(nAxes);
        jsButtons.resize(nButtons);
        for (int i = 0; i < nAxes; ++i) {
            jsAxes[i] = SDL_JoystickGetAxis(aJoystick, i);
        }
        for (int i = 0; i < nButtons; ++i) {
            jsButtons[i] = SDL_JoystickGetButton(aJoystick, i);
        }
    }
};

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    char cmd[64];
    if (nrhs < 1 || mxGetString(prhs[0], cmd, sizeof(cmd))) {
        mexErrMsgTxt("First input should be a command string ('init', 'get', 'cleanup')");
    }
    static Joystick myJoystick;
    
    if (!strcmp("init", cmd)) {
        myJoystick.initialize();
    } else if (!strcmp("get", cmd)) {
        std::vector<double> jsAxes, jsButtons;
        myJoystick.getControllerStates(jsAxes, jsButtons);
        plhs[0] = mxCreateDoubleMatrix(jsAxes.size(), 1, mxREAL);
        plhs[1] = mxCreateDoubleMatrix(jsButtons.size(), 1, mxREAL);
        std::copy(jsAxes.begin(), jsAxes.end(), mxGetPr(plhs[0]));
        std::copy(jsButtons.begin(), jsButtons.end(), mxGetPr(plhs[1]));
    } else if (!strcmp("cleanup", cmd)) {
        myJoystick.cleanup();
    } else {
        mexErrMsgTxt("Command not recognized.");
    }
}
