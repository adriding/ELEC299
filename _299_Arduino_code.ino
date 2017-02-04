//test GoLeft
//test this first
#define TSLow 500
#define TSHigh 800
#define MotorSpeed 120

int MotorOneFwd = 9;//M1:L; M2:R
int MotorOneRev = 10;
int MotorTwoFwd = 5;
int MotorTwoRev = 6;
  int sensorValue1 = 0;
  int sensorValue2 = 0;
  int sensorValue3 = 0;
  int sensorValue4 = 0;
  int sensorValue5 = 0;
  int sensorValue6 = 0;

void Scan(void){
  sensorValue1 = analogRead(A0);
  sensorValue2 = analogRead(A1);
  sensorValue3 = analogRead(A2);
  sensorValue4 = analogRead(A3);
  sensorValue5 = analogRead(A4);
  sensorValue6 = analogRead(A5);
}

void Print(void){
  Serial.print("L: ");
  Serial.print(sensorValue1);
  Serial.print("\t");
  Serial.print("C: ");
  Serial.print(sensorValue2);
  Serial.print("\t");
  Serial.print("R: ");
  Serial.print(sensorValue3);
  Serial.print("\t");
  Serial.print("FC: ");
  Serial.print(sensorValue4);
  Serial.print("\t");
  Serial.print("FL: ");
  Serial.print(sensorValue5);
  Serial.print("\t");
  Serial.print("FR: ");
  Serial.print(sensorValue6);
  Serial.print("\t");
  Serial.println();
  //delay(1);// delay in between reads for stability
}


void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}//setting part ends

  void GoFwd(int time)
  {
    analogWrite(MotorOneFwd,MotorSpeed);
    analogWrite(MotorTwoFwd,MotorSpeed);
    delay(time);
    Stop();
  }
  
  void GoRight(int time)
  {
    analogWrite(MotorOneFwd,MotorSpeed);
    analogWrite(MotorTwoRev,MotorSpeed);
    delay(time);
    Stop();
  }
  
  void GoLeft(int time)
  {
    analogWrite(MotorOneRev,MotorSpeed);
    analogWrite(MotorTwoFwd,MotorSpeed);
    delay(time);
    Stop();  
  }
  
  void Stop(void)
  {
    analogWrite(MotorOneFwd,0);
    analogWrite(MotorOneRev,0);
    analogWrite(MotorTwoFwd,0);
    analogWrite(MotorTwoRev,0);    
  }
  
void loop(){
  Scan();
  Print();
  int state = 1;
  int count = 0;
  
  switch(state){
    case 1:
    //when all three missed or when the robot reaches the end of one road(adjust direction), turn left until S4 gets something
    Scan();
      if((sensorValue1 >= TSHigh) && (sensorValue2 >= TSHigh) && (sensorValue3 >= TSHigh) && (sensorValue4 >= TSHigh)){
        GoLeft(20);
      } 
      
      if((sensorValue1 <= TSLow) && (sensorValue2 >= TSHigh) && (sensorValue3 >= TSHigh) && (sensorValue4 >= TSHigh) && (sensorValue5 >= TSHigh) && (sensorValue6 >= TSHigh)){
        GoLeft(20);
      }
      
      if((sensorValue3 <= TSLow) && (sensorValue1 >= TSHigh) && (sensorValue2 >= TSHigh) && (sensorValue4 >= TSHigh) && (sensorValue5 >= TSHigh) && (sensorValue6 >= TSHigh)){
        GoLeft(20);
      }
      
      /*if((sensorValue2 <= TSLow) && (sensorValue1) >= TSHigh && (sensorValue3 >= TSHigh) && (sensorValue4 >= TSHigh) && (sensorValue5 >= TSHigh) && (sensorValue6 >= TSHigh)){
        GoLeft(20);
      }*/
      
      
      /*if((sensorValue1 <= TSLow) && (sensorValue2 >= TSHigh) && (sensorValue3 >= TSHigh) && (sensorValue4 <= TSLow) && (sensorValue5 >= TSHigh) && (sensorValue6 >= TSHigh)){
        GoLeft(20);
      }
      
      if((sensorValue1 >= TSHigh) && (sensorValue2 >= TSHigh) && (sensorValue3 <= TSLow) && (sensorValue4 <= TSLow) && (sensorValue5 >= TSHigh) && (sensorValue6 >= TSHigh)){
        GoLeft(20);
      }*/
      
      
      
      if((sensorValue4 <= TSLow) && (sensorValue2 >= TSHigh) && (sensorValue1 >= TSHigh) && (sensorValue3 >= TSHigh)){
        GoFwd(20);
        GoRight(20);
      }
      
          
        
      //if only S2 has a low value
      if((sensorValue1 >= TSHigh) && (sensorValue2 <= TSLow) && (sensorValue3 >= TSHigh) && (sensorValue4 >= TSHigh) && (sensorValue5 >= TSHigh) && (sensorValue6 >= TSHigh)){
        GoRight(20);
        GoFwd(20);
      }
      
      if((sensorValue2 <= TSLow) && (sensorValue4 <= TSLow) && (sensorValue1 >= TSHigh) && (sensorValue3 >= TSHigh) && (sensorValue5 >= TSHigh) && (sensorValue6 >= TSHigh)){
        //Stop();
        state = 2;
      }
  
    case 2:
    //go straight
    Scan();
      if((sensorValue2 <= TSLow) && (sensorValue4 <= TSLow) && (sensorValue1 >= TSHigh) && (sensorValue3 >= TSHigh)){
        GoFwd(20);
        //flag = STRAIGHT;
        //Serial.println("Forward");
      }
      else
        if((sensorValue1 <= TSLow) && (sensorValue2 <= TSLow) && (sensorValue4 <= TSLow) && (sensorValue3 >= TSHigh)){
          GoFwd(20);
        }
          
        //go straight ends
      
            //************code for adjusting the direction************//
          if(/*sensorValue2 <= TSLow && */(sensorValue5 <= TSLow) && (sensorValue4 >= TSHigh) && (sensorValue6 >= TSHigh)){
            GoLeft(20);
            //flag = TURN_LEFT;
            //Serial.println("Adjust to left");
          }
          else
          if(/*sensorValue2 <= TSLow &&*/ (sensorValue6 <= TSLow) && (sensorValue4 >= TSHigh) && (sensorValue5 >= TSHigh)){
            GoRight(20);
            //flag = TURN_RIGHT;
            //Serial.println("Adjust to right");
          }
          else
          if((sensorValue5 <= TSLow) && (sensorValue6 <= TSLow) && (sensorValue4 >= TSHigh)){
            GoRight(20);
          }//adjusting ends
          
      //turn or stop
      /*if((sensorValue1 <= TSLow) && (sensorValue2 <= TSLow) && (sensorValue3 >= TSHigh) && (sensorValue4 >= TSHigh) && (sensorValue5 >= TSHigh) && (sensorValue6 >= TSHigh)){
        Stop();
        state = 3;//turn left
      }*/
      //else
        if((sensorValue1 <= TSLow) && (sensorValue2 <= TSLow) && (sensorValue3 <= TSLow) && (sensorValue4 >= TSHigh) && (sensorValue5 >= TSHigh) && (sensorValue6 >= TSHigh)){
          //Stop();
          state = 4;//turn right
        }
        //else
          if((sensorValue2 <= TSLow) && (sensorValue3 <= TSLow) && (sensorValue4 <= TSLow) && (sensorValue1 >= TSHigh)){
            //Stop();
            state = 4;//turn right
          }
          //else
            if((sensorValue2 <= TSLow) && (sensorValue3 <= TSLow) && (sensorValue4 >= TSHigh) && (sensorValue5 >= TSHigh) && (sensorValue6 >= TSHigh)){
              //Stop();
              state = 4;//turn right
            }
      //else 
        if((sensorValue2 <= TSLow) && (sensorValue1 >= TSHigh) && (sensorValue3 >= TSHigh) && (sensorValue4 >= TSHigh) && (sensorValue5 >= TSHigh) && (sensorValue6 >= TSHigh)){
          //Stop();
          state = 1;
        } 
      //else
        if(sensorValue1 <= TSLow && sensorValue2 <= TSLow && sensorValue3 <= TSLow && sensorValue4 <= TSLow){
          Stop();//stop at the end
        }
        
    /*case 3:
    //turn left when S1 and S2 have low value
    Scan();
      if((sensorValue1 <= TSLow) && (sensorValue2 <= TSLow) && (sensorValue3 >= TSHigh) && (sensorValue4 >= TSHigh)){
        GoLeft(20);
      }//turn left ends

      //when all three missed or when the robot reaches the end of one road(adjust direction), turn left until S4 gets something
      if((sensorValue1 >= TSHigh) && (sensorValue2 >= TSHigh) && (sensorValue3 >= TSHigh) && (sensorValue4 >= TSHigh)){
        GoLeft(20);
      } 
      
      if((sensorValue1 <= TSLow) && (sensorValue2 >= TSHigh) && (sensorValue3 >= TSHigh) && (sensorValue4 >= TSHigh) && (sensorValue5 >= TSHigh) && (sensorValue6 >= TSHigh)){
        GoLeft(20);
      }
      
      if((sensorValue3 <= TSLow) && (sensorValue1 >= TSHigh) && (sensorValue2 >= TSHigh) && (sensorValue4 >= TSHigh) && (sensorValue5 >= TSHigh) && (sensorValue6 >= TSHigh)){
        GoLeft(20);
      }
      
      
      
    
      
      
      if((sensorValue4 <= TSLow) && (sensorValue2 >= TSHigh) && (sensorValue1 >= TSHigh) && (sensorValue3 >= TSHigh)){
        GoRight(20);
        GoFwd(10);
      }
      
          
        
      //if only S2 has a low value
      if((sensorValue1 >= TSHigh) && (sensorValue2 <= TSLow) && (sensorValue3 >= TSHigh) && (sensorValue4 >= TSHigh) && (sensorValue5 >= TSHigh) && (sensorValue6 >= TSHigh)){
        GoRight(20);
        GoFwd(10);
      }
      
      if((sensorValue2 <= TSLow) && (sensorValue4 <= TSLow) && (sensorValue1 >= TSHigh) && (sensorValue3 >= TSHigh) && (sensorValue5 >= TSHigh) && (sensorValue6 >= TSHigh)){
        Stop();
        state = 2;
      }*/
      
    case 4:
    //turn right when S2 and S3 have low value
      if((sensorValue1 <= TSLow) && (sensorValue2 <= TSLow) && (sensorValue3 <= TSLow) && (sensorValue4 >= TSHigh) && (sensorValue5 >= TSHigh) && (sensorValue6 >= TSHigh)){
          GoFwd(100);
          GoRight(1200);
        }
        //else
          if((sensorValue2 <= TSLow) && (sensorValue3 <= TSLow) && (sensorValue4 <= TSLow) && (sensorValue1 >= TSHigh)){
            GoFwd(100);
            GoRight(1200);
          }
          //else
            if((sensorValue2 <= TSLow) && (sensorValue3 <= TSLow) && (sensorValue4 >= TSHigh) && (sensorValue5 >= TSHigh) && (sensorValue6 >= TSHigh)){
              GoFwd(100);
              GoRight(1200);
            }
      
      if((sensorValue1 >= TSHigh) && (sensorValue2 >= TSHigh) && (sensorValue3 >= TSHigh) && (sensorValue4 >= TSHigh)){
        GoLeft(20);
      } 
      
      if((sensorValue1 <= TSLow) && (sensorValue2 >= TSHigh) && (sensorValue3 >= TSHigh) && (sensorValue4 >= TSHigh) && (sensorValue5 >= TSHigh) && (sensorValue6 >= TSHigh)){
        GoLeft(20);
      }
      
      if((sensorValue3 <= TSLow) && (sensorValue1 >= TSHigh) && (sensorValue2 >= TSHigh) && (sensorValue4 >= TSHigh) && (sensorValue5 >= TSHigh) && (sensorValue6 >= TSHigh)){
        GoLeft(20);
      }
      
      /*if((sensorValue2 <= TSLow) && (sensorValue1) >= TSHigh && (sensorValue3 >= TSHigh) && (sensorValue4 >= TSHigh) && (sensorValue5 >= TSHigh) && (sensorValue6 >= TSHigh)){
        GoLeft(20);
      }*/
      
      
      /*if((sensorValue1 <= TSLow) && (sensorValue2 >= TSHigh) && (sensorValue3 >= TSHigh) && (sensorValue4 <= TSLow) && (sensorValue5 >= TSHigh) && (sensorValue6 >= TSHigh)){
        GoLeft(20);
      }
      
      if((sensorValue1 >= TSHigh) && (sensorValue2 >= TSHigh) && (sensorValue3 <= TSLow) && (sensorValue4 <= TSLow) && (sensorValue5 >= TSHigh) && (sensorValue6 >= TSHigh)){
        GoLeft(20);
      }*/
      
      
      
      if((sensorValue4 <= TSLow) && (sensorValue2 >= TSHigh) && (sensorValue1 >= TSHigh) && (sensorValue3 >= TSHigh)){
        GoFwd(20);
        GoRight(20);
      }
      
          
        
      //if only S2 has a low value
      if((sensorValue1 >= TSHigh) && (sensorValue2 <= TSLow) && (sensorValue3 >= TSHigh) && (sensorValue4 >= TSHigh) && (sensorValue5 >= TSHigh) && (sensorValue6 >= TSHigh)){
        GoRight(20);
        GoFwd(20);
      }
      
      if((sensorValue2 <= TSLow) && (sensorValue4 <= TSLow) && (sensorValue1 >= TSHigh) && (sensorValue3 >= TSHigh) && (sensorValue5 >= TSHigh) && (sensorValue6 >= TSHigh)){
        //Stop();
        state = 2;
      }
  }
} 
