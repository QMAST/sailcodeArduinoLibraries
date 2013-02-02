/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation; 
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307,
 * USA.
 *
 * Copyright (C) Stephen Cripps, 2013
 */

/* Pololu Micro Servo controller class
 *
 * Basically the servo controller only needs to have serial commands sent
 * to it, in accord with the mode of operation you choose. In this case,
 * the library is using the MiniServo commands as opposed to the Pololu
 * specific commands, which you can read about in the documentation
 * posted on the wiki
 */

#ifndef pololu_servo_h
#define pololu_servo_h

#include <Arduino.h>

class PololuMSC {
    private:
        static const int RESET_HIGH_WAIT = 100;
        static const int RESET_LOW_WAIT = 1000;

        Stream* serialCom;
        int reset_pin;
    public:
        /** One instance of an initialised serial port and the pin for
         * the reset on the Pololu
         */
        PololuMSC(Stream*, int);
        int restart();
};

#endif
