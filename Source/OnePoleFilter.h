#pragma once

class OnePoleFilter
{
public:
    void reset()
    {
        state = 0.0f;
    }

    float process (float input, float coefficient)
    {
        state += coefficient * (input - state);
        return state;
    }

private:
    float state = 0.0f;
};