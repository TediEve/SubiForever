Sources=MathematicModel/AckermanModel.cpp  MathematicModel/Car.cpp HybridAstar/src/State.cpp HybridAstar/src/Compare.cpp HybridAstar/src/Map.cpp HybridAstar/src/Gui.cpp HybridAstar/src/Planner.cpp MathematicModel/main.cpp
Target = ack

# general compiler settings
CXXFLAGS = -ggdb -O3 -ffast-math -w
LIBS = `pkg-config --libs opencv`

all:
	$(CXX) $(CXXFLAGS) $(Sources) $(LIBS) -o $(Target) $(LDFLAGS)

clean:
	@$(RM) $(Target)

.PHONY: clean