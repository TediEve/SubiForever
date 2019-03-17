#ifndef _CONTROLS_HPP_ 
#define _CONTROLS_HPP_

#include <atomic>
#include <thread>
#include <memory>
#include <unistd.h>

#include "gpio.hpp"

class Controls{
public:
    std::unique_ptr<Controls>& getInstance();    

    std::atomic<int> targetTurn;
    std::atomic<int> targetVelocity;
    ~Controls();
private:
    Controls();

    void run();

    bool clearTurnIfNeeded();
    bool clearVelocityIfNeeded();

    void updateTurn();
    void updateVelocity();

    static std::unique_ptr<Controls> instance;

    int turn = 0;
    int velocity = 0;

    GPIO left;
    GPIO right;
    GPIO forward;
    GPIO backward;

    std::thread task;
};

#endif