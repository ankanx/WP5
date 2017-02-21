/*
 * 
 * Group: 9 & 10
 * Members:
 * Andreas Fransson
 * Daniel Arnqvist
 * Axel Spångberg
 * Marco Koivisto
 * Philip Crockett
 * 
 * Segments of the display
 *          pin 7  
 *           ___        
 *    pin 6 |   | pin 4 
 *          |___|       
 *          |   |       
 *    pin 3 |___| pin 5 
 *          
 *          pin 2
 *          
 *
 *          ___   ___
 *         |   | |   |
 *         |___| |___|
 *         |   | |   |
 *         |___| |___|
 *     pin 12       pin 13
*/
 
int tempSensor = 0;
int temp;
int left;
int right;
int timeLeft = 0;
int updateDelay = 1000;

/*
 * DIP Switch
*/
int switchOne = 0;
int switchTwo = 0;
int switchFour = 0;
int switchEight = 0;

/*
 * For the second mode retain the highest temp.
 * A
 */
int highestTemp;
int firstRead = 1;

void setup() {
/*
 * Anode's
*/
pinMode(2, OUTPUT);
pinMode(3, OUTPUT);
pinMode(4, OUTPUT);
pinMode(5, OUTPUT);
pinMode(6, OUTPUT);
pinMode(7, OUTPUT);
pinMode(8, OUTPUT);

/*
 * Cathode's 1 & 2 (display number 1 & 2)
 */
pinMode(12, OUTPUT);
pinMode(13, OUTPUT);

/*
 * Bitswitch inputs
 */
pinMode(A1, INPUT);
pinMode(9, INPUT);
pinMode(10, INPUT);
pinMode(11, INPUT);


  Serial.begin (9600);
}

void loop() {

  switchOne = digitalRead(9);
  switchTwo = digitalRead(A1);
  switchFour = digitalRead(10);
  switchEight = digitalRead(11);
  Serial.println();
  Serial.print(switchOne);
  Serial.print(switchTwo);
  Serial.print(switchFour);
  Serial.print(switchEight);
  Serial.println();

  if(timeLeft < 1){
    timeLeft = updateDelay;
    temp = getTemp();
    if(temp > highestTemp){
      highestTemp = temp;
    }
    right = temp % 10;
    left = temp / 10;
  }
  else{
    timeLeft += -25;
  }
  
if(switchOne && switchTwo && switchFour && switchEight){

    pushToDiplay(getTemp()/10, getTemp()%10);
    
  }else{
    
    int tLeft = highestTemp / 10;
    int tRight = highestTemp % 10;
    pushToDisplay(tLeft, tRight);
  }

}


void pushToDisplay(int left, int right){
  if(left == 0){
    showRight();
    getNumber(right);
  } else {
      showRight();
      getNumber(right);
      delay(10);
      showLeft();
      getNumber(left);
      delay(10);
  }
}

void showLeft(){
  digitalWrite(13, LOW);
  digitalWrite(12, HIGH);
}

void showRight(){
  digitalWrite(13, HIGH);
  digitalWrite(12, LOW);

}

void getZero(){
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, LOW);
}
  
void getOne(){
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
}

void getTwo(){
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
}

void getThree(){
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
}

void getFour(){
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
}

void getFive(){
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
}

void getSix(){
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
}

void getSeven(){
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);
  digitalWrite(8, LOW);
}

void getEight(){
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);  
}

void getNine(){
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
}


void getNumber(int num) {
  switch (num) {
    case 0:
      getZero();
      break; 
    case 1:
      getOne();
      break; 
    case 2:
      getTwo();
      break; 
    case 3:
      getThree();
      break; 
    case 4:
      getFour();
      break; 
    case 5:
      getFive();
      break; 
    case 6:
      getSix();
      break; 
    case 7:
      getSeven();
      break; 
    case 8:
      getEight();
      break; 
    case 9:
      getNine();
      break; 
  }
}


int getTemp(){
  int temp = analogRead(tempSensor);
  temp = (5.0 * temp * 100.0)/1024.0;
  if(firstRead){
    highestTemp = temp;
    firstRead = 0;
  }
  return temp;
}
