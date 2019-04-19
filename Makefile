Sources= MathematicModel/Utils.cpp MathematicModel/DrawUtils.cpp MathematicModel/Map.cpp MathematicModel/AckermanModel.cpp  MathematicModel/Car.cpp MathematicModel/KinematicCar.cpp MathematicModel/TestImplHybridAstar.cpp MathematicModel/main.cpp
Target = ack

# general compiler settings
#set flag -02 when ready for shipping
CXXFLAGS = -ggdb -Wall
LIBS = `pkg-config --libs opencv`

all:
	$(CXX) $(CXXFLAGS) $(Sources) $(LIBS) -o $(Target) $(LDFLAGS)

clean:
	@$(RM) $(Target)

.PHONY: clean