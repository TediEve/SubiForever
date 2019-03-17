#include "controls.hpp"

#include <unistd.h>

const unsigned int ms100 = 100 * 1000; 


    bool Controls::clearTurnIfNeeded()
    {
    	if(targetTurn!=turn){
    		if(turn > 0){
    			left.setValue(0);
    		} else if(turn < 0) {
    			right.setValue(0);
    		}
    		turn = 0;
    		return true;
    	}
    	return false;
    }

    bool Controls::clearVelocityIfNeeded(){
    	if(targetVelocity != velocity){
    		if(velocity > 0){
    			forward.setValue(0);
    		} else if(velocity < 0) {
    			backward.setValue(0);
    		}
    		velocity = 0;
    		return true;
    	}	
    	return false;
    }

    void Controls::updateTurn()
    {
    	if(targetTurn != turn){
    		if(targetTurn > 0){
    			left.setValue(1);
    		} else  if(targetTurn < 0) {
    			right.setValue(1);
    		}
    		turn = targetTurn;
    	}
    }

    void Controls::updateVelocity()
    {
    	if(targetVelocity != velocity){
    		if(targetVelocity > 0){
    			forward.setValue(1);
    		} else  if(targetVelocity < 0) {
    			backward.setValue(1);
    		}
    		velocity = targetVelocity;
    	}
    }

    std::unique_ptr<Controls>& Controls::getInstance(){
    	return instance;
    }    

    void Controls::run(){
    	while(true){
    		bool update = clearTurnIfNeeded() || clearVelocityIfNeeded();
    		if(update){
	   			usleep(ms100);
	    		updateTurn();
    			updateVelocity();
   			}
    		usleep(ms100);
    	}
    }

    Controls::Controls():
    left(2, GPIO::Direction::Out), right(3, GPIO::Direction::Out),
    forward(4, GPIO::Direction::Out), backward(17, GPIO::Direction::Out)
    {
	   	instance =  std::unique_ptr<Controls>(new Controls());
    	turn = 0;
    	velocity = 0;
    	targetTurn = 0;
    	targetVelocity = 0;
    	task = std::thread([this](){run();});
    }

    Controls::~Controls(){}

