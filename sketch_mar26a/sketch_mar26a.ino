#include <TM1637.h>
#define CLK 3
#define DIO 2
TM1637 disp(CLK,DIO);

byte arr[]={1,2,3,4};

struct hour{
  byte hour_1;//для левой части
  byte hour_2;//для правой части
  public:
  hour(){}
  hour(byte ho_1,byte ho_2){
    hour_1=ho_1;
    hour_2=ho_2;
  }

  void increase(){
    hour_2++;
    if(hour_2>9){
      hour_2=0;
      hour_1++;
    }
    //if( ((hour_1*10)+hour_2)>23 ){
      //hour_1=0;
      //hour_2=0;
    //}
  }

  void Create_NULLL(){
    hour_1=0;
    hour_2=0;
  }
  
};

struct minute{
  byte minute_1; //для левой
  byte minute_2; //для правой
  public:
  minute(){}
  minute(byte min_1,byte min_2){
    minute_1=min_1;
    minute_2=min_2;
  }
  void increase(){
    minute_2++;
    if(minute_2>9){
      minute_2=0;
      minute_1++;
    }
    //if( ((minute_1*10)+minute_2) >59){
    //  minute_1=0;
    //  minute_2=0;
    //}
  }

  void Create_NULLL(){
    minute_1=0;
    minute_2=0;
  }
  
};

void start(hour start_check_hour,minute start_check_minute );
bool hour_define(hour h,minute m);
bool minute_define(hour h,minute m);
void output(hour start_check_hour , minute start_check_minute);
void settings( hour start_check_hour , minute start_check_minute );
bool check_switch(); //true-если включен и false если выключен

void setup() {
  // put your setup code here, to run once:
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(6 , INPUT_PULLUP); //для кнопки
  pinMode(5, INPUT_PULLUP); //для тумблера
  disp.init();
  disp.set(7);

  digitalWrite(2,HIGH);
  digitalWrite(3,HIGH);
  digitalWrite(12,HIGH);
  digitalWrite(13, HIGH);  

  hour start_check_hour(0,0); //часы начало
  minute start_check_minute(0,0); //мин начало
  start(start_check_hour,start_check_minute ); 

}



void loop() {
  // put your main code here, to run repeatedly:  
  
}

void start(hour start_check_hour , minute start_check_minute){
  output( start_check_hour ,  start_check_minute);

  while(true){
    
    if((minute_define(start_check_hour , start_check_minute))==true){
      
      output( start_check_hour ,  start_check_minute);

      

      //задержка минута
      for(int i=0;i<12;i++){
        delay(5000);
        output( start_check_hour ,  start_check_minute);
        
        
        //обрабатываем нажатие на кнопку
      
        if((digitalRead(6)== 1) ){
          settings(  start_check_hour ,  start_check_minute );
        }
      
        //заканчиваем обработку
      }

      start_check_minute.increase();
      
      
      
      output( start_check_hour ,  start_check_minute);
      
      continue;
    }
    else{
      output( start_check_hour ,  start_check_minute);
      
      start_check_minute.Create_NULLL();
      
      if( (hour_define(start_check_hour , start_check_minute))&&(minute_define(start_check_hour , start_check_minute)) ==true ){
        start_check_hour.increase();
      }
      
      if( ((hour_define(start_check_hour , start_check_minute)) && (minute_define(start_check_hour , start_check_minute)) )==false  ){
        start_check_hour.Create_NULLL();
        start_check_minute.Create_NULLL();
      }
      
      output( start_check_hour ,  start_check_minute);

      //delay(1000);
      
    }
    
    
    
  }
}
bool minute_define(hour h,minute m){
  if( ((m.minute_1*10)+m.minute_2) <60 ){
    return(true);
  }
  else{
    return(false);
  }
}
bool hour_define(hour h,minute m){
  if( ((h.hour_1*10)+h.hour_2) <24 ){
    return(true);
  }
  else{
    return(false);
  }
}

void settings( hour start_check_hour , minute start_check_minute ){
  /*
  output( start_check_hour ,  start_check_minute);
  disp.point(1);
  output( start_check_hour ,  start_check_minute);
  delay(1000);
  disp.point(0);
  output( start_check_hour ,  start_check_minute);
  delay(1000);
  */
  
  while(true){
    disp.point(1);
    
    

    
    if((digitalRead(6)!= 1) ){
      disp.point(0);
      break;    
      //start( start_check_hour ,  start_check_minute);
    }
    
    output( start_check_hour ,  start_check_minute);
    
    delay(500);
    
    disp.point(0);

// проверяем тумблер
    if(check_switch()==true ){
      if((hour_define(start_check_hour,start_check_minute) ==true) && (  ((start_check_hour.hour_1*10)+start_check_hour.hour_2)!=23  ) ){
          start_check_hour.increase();
      }
      else{
        start_check_hour.Create_NULLL();
      }
        
    }
    else{
      
      if((minute_define(start_check_hour,start_check_minute)==true)&& ( ((start_check_minute.minute_1*10)+start_check_minute.minute_2)!=59 ) )
        start_check_minute.increase();
      else{
        start_check_minute.Create_NULLL();
      }
      
    }
// конец проверки    

    output( start_check_hour ,  start_check_minute);
    delay(500);
    
    
    
    
  }
  
  start(start_check_hour , start_check_minute);
}

void output(hour start_check_hour , minute start_check_minute){
      disp.display(3,start_check_minute.minute_2);
      disp.display(2,start_check_minute.minute_1);
      disp.display(1,start_check_hour.hour_2);
      disp.display(0,start_check_hour.hour_1);
}

bool check_switch(){
  if( digitalRead(5)== 1 ){
    return true;
  }

  else{
    return false;
  }
  
}
