Sources=MathematicModel/AckermanModel.cpp  MathematicModel/Car.cpp MathematicModel/main.cpp
Target = ack

# general compiler settings
CXXFLAGS = -ggdb -O3 -ffast-math -w
LIBS = `pkg-config --libs opencv`

all:
	$(CXX) $(CXXFLAGS) $(Sources) $(LIBS) -o $(Target) $(LDFLAGS)

clean:
	@$(RM) $(Target)

.PHONY: clean