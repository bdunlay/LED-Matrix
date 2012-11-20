/* Name: shift.h
 * Author: Brian Dunlay
 * Shift functions for LED Matrix for the ATtiny2313a
 */

#ifndef SHIFT_H
#define SHIFT_H

void initializeShift();
void interruptHandler();
void resetShiftRegisters();
void print(char frame[]);
void shiftBit(int SRCLK_Pin, int RCLK_Pin, int SER_Pin, unsigned long data);
void shiftByte(int SRCLK_Pin, int RCLK_Pin, int SER_Pin, unsigned long data);

#endif
