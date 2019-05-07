//
// Created by Alex Almansa on 18/04/2019.
//

#include "PWM.h"
#include "time.h"
//#define TEMPSA1 20;
static char estatPWM;
static char timerPWM, temps;
static char countPWM, start = 0, startAntic;
static int TEMPSA1= 4, GRAUSXFLANC = 1, FREQ = 20;


    void PWMInit(void){
        timerPWM = TiGetTimer();
        estatPWM = 0;
        PWMV = '0';
        //TRISBbits.TRISB10 = 0;
}
    void changePWM(void) {

        //Post: Posa a 1 o 0 el PWM , depenent del temps que estigui

        PWMV = (TEMPSA1 >= temps ? 1 : 0);


    }

    

    void incrementPWM(void) {

        //Post: Incrementa el valor de countPWM
        countPWM = countPWM + 1;

    }

    void setGraus(int graus) {
      startAntic = start;
      start = graus * GRAUSXFLANC;
      
    }

    void MotorPWM (void) {
        switch(estatPWM) {
            case 0:

                if(start > countPWM && start != startAntic){
                    estatPWM = 1;
                    TiResetTics(timerPWM);
                } else{
                    PWMV = 0;
                    
                }

                break;
            case 1:
                if(countPWM >= start){
                    estatPWM = 0;
                    countPWM = 0;
                }else{
                    temps = TiGetTics(timerPWM) ;
                    changePWM();

                    if(temps > FREQ){
                        estatPWM = 2;
                    }
                }

                break;

                case 2:
                    TiResetTics(timerPWM);
                    incrementPWM();
                    estatPWM = 1;
                    break;
        }
    }

