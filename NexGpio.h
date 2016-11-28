#ifndef _NEXGPIO_H
#define _NEXGPIO_H
     
#include "NexTouch.h"
#include "NexHardware.h"


class NexGpio
{
    public:
    /**
     * Set gpio mode
     *
     * @param port - the gpio port number
     * @param mode - set gpio port mode(0--Pull on the input
     *                                  1--the control input binding
     *                                  2--Push-pull output
     *                                  3--pwm output
     *                                  4--open mode leakage)
     * @param control_id - nextion controls id ,when the modeel is 1 to be valid
     * @return true if success, false for failure
     */
    
    bool pin_mode(uint32_t port,uint32_t mode,uint32_t control_id);
    
    /**
     * write a high or a LOW value to a digital pin
     *
     * @param port - the gpio port number
     * @param mode - the gpio port number
     * @return true if success, false for failure
     */
    
    bool digital_write(uint32_t port,uint32_t value);
    
    /**
     * read a high or a LOW value to a digital pin
     *
     * @param port - the gpio port number
     * @return the value from a specified digital pin, either high or low 
     */
    
    uint32_t digital_read(uint32_t port);
    
    /**
     * writes an analog value (PWM wave) to a pin
     *
     * @param port - the gpio port number
     * @param value - the duty cycle: between 0 (always off) and 100 (always on).
     * @return true if success, false for failure
     */
    
    bool analog_write(uint32_t port,uint32_t value);
    
    /**
     * writes pwm output frequency
     *
     * @param value - the frequency: between 1 and 65535
     * @return true if success, false for failure
     */
    
    bool set_pwmfreq(uint32_t value);
    
    /**
     * read pwm output frequency
     *
     * @param number - the frequency
     * @return true if success, false for failure
     */
    
    uint32_t get_pwmfreq(uint32_t *number);
    
    /**
     * write rtc times
     *
     * @param time - Time to write to the array
     * @return true if success, false for failure
     */
     
};
    
#endif