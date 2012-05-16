/*
 * timer.h
 *
 * Created: 5/16/2012 11:08:20 AM
 *  Author: Brian
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#define PRESCALE	8
#define TARGET_F	1000
#define TIMER_CT	((F_CPU/PRESCALE)/TARGET_F - 1) // 1ms Refresh period

void init_timer(void);



#endif /* TIMER_H_ */