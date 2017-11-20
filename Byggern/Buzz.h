#ifndef buzz_h_
#define buzz_h_
 
 //DURATION OF THE NOTES
#define BPM 120      //you can change this value changing all the others
#define H 2*Q //half 2/4
#define Q 60000/BPM //quarter 1/4
#define E Q/2   //eighth 1/8
#define S Q/4 // sixteenth 1/16
#define W 4*Q // whole 4/4


void buzzinit(void);
void buzz(unsigned int freq, int time);
void delayUS(unsigned int time);
void Shoot_sfx();
void death_sfx();


#endif