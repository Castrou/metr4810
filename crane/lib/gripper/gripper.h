/** 
 **************************************************************
 * @file lib/gripper/gripper.h
 * @author Cameron Stroud - 44344968
 * @date 02052020
 * @brief Gripper Object Header file
 ***************************************************************
 * EXTERNAL FUNCTIONS 
 ***************************************************************
 * 
 *************************************************************** 
 */

#ifndef __GRIPPER_H_
#define __GRIPPER_H_

#include "mbed.h"


class Gripper {

    private:
        /* Private Variables */

        /* Private Functions */

    public:
        /* Public Variables */

        /* Public Functions */
        void release( void );
        void grasp( void );
        void write_pulsems( uint8_t pulsewidth );

        /* Constructor */
        Gripper(PinName desiredPin);    

};



#endif // __GRIPPER_H_