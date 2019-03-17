#ifndef _SUBI_FOREVER_GPIO_HPP_
#define _SUBI_FOREVER_GPIO_HPP_

class GPIO{
public:
    enum class Direction{
    	In = 0, Out = 1
    };

    GPIO(unsigned int const gpio, Direction const direction);

    void setValue(bool active);

    unsigned int getValue();

    ~GPIO();

private:
	unsigned int const gpio;
	Direction const direction;
};

#endif
