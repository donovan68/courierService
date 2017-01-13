#ifndef SIMTIME_H
#define SIMTIME_H


class SimTime
{
public:
    SimTime();
    static void Step(unsigned long int speed)
    {
        _seconds += speed;

        if(_seconds >= 24 * 60 * 60)
        {
            _seconds =_seconds % (24 * 60 * 60);
        }
    }
    static unsigned int Hour()
    {
        return _seconds / 60 / 60;
    }
    static unsigned int Minute()
    {
        return (_seconds / 60) % 60;
    }

private:
    static unsigned long _seconds;
};

#endif // SIMTIME_H
