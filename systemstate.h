#ifndef SYSTEMSTATE_H
#define SYSTEMSTATE_H

class SystemState{
public:
    SystemState(){}
    ~SystemState(){}

    static bool getIsActive(){
        return isActive;
    }

    static void setIsActive(bool arg){
        isActive = arg;
    }

private:
    static bool isActive; // True if user select a patient; false if not.
};


#endif // SYSTEMSTATE_H

