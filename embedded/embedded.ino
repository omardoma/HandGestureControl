const int trigger1 = 2; //Trigger pin of 1st Sesnor
const int echo1 = 3;    //Echo pin of 1st Sesnor
const int trigger2 = 4; //Trigger pin of 2nd Sesnor
const int echo2 = 5;    //Echo pin of 2nd Sesnor

long time_taken;
int dist, distL, distR;

void setup()
{
  Serial.begin(9600);

  pinMode(trigger1, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(trigger2, OUTPUT);
  pinMode(echo2, INPUT);
}

// Function to calculate distance
void calculate_distance(int trigger, int echo)
{
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);

  time_taken = pulseIn(echo, HIGH);
  dist = time_taken * 0.034 / 2;
  if (dist > 100)
    dist = 100;
}

//infinite loop
void loop()
{ 
  calculate_distance(trigger1, echo1);
  distL = dist; //get distance of left sensor

  calculate_distance(trigger2, echo2);
  distR = dist; //get distance of right sensor

  //Uncomment for debudding
  Serial.print("L=");
  Serial.println(distL);
  Serial.print("R=");
  Serial.println(distR);

  //Pause Modes -Hold
  if ((distL > 0 && distR > 0) && (distL < 15 && distR < 15)) //Detect both hands
  {
    Serial.println("Play/Pause");
    delay(500);
  }

  calculate_distance(trigger1, echo1);
  distL = dist;

  calculate_distance(trigger2, echo2);
  distR = dist;

  //Control Modes
  //Lock Left - Control Mode
  if (distL >= 15 && distL <= 50)
  {
    delay(100); //Hand Hold Time
    calculate_distance(trigger1, echo1);
    distL = dist;
    if (distL >= 15 && distL <= 50)
    {
      Serial.println("Left Locked");
      while (distL <= 50)
      {
        calculate_distance(trigger1, echo1);
        distL = dist;
        if (distL < 25) //Hand pushed in
        {
          Serial.println("Vup");
          delay(300);
        }
        if (distL > 25) //Hand pulled out
        {
          Serial.println("Vdown");
          delay(300);
        }
      }
    }
  }

  //Lock Right - Control Mode
  if (distR >= 15 && distR <= 50)
  {
    delay(100); //Hand Hold Time
    calculate_distance(trigger2, echo2);
    distR = dist;
    if (distR >= 15 && distR <= 50)
    {
      Serial.println("Right Locked");
      while (distR <= 50)
      {
        calculate_distance(trigger2, echo2);
        distR = dist;
        if (distR < 25) //Right hand pushed in
        {
          Serial.println("Rewind");
          delay(300);
        }
        if (distR > 25) //Right hand pulled out
        {
          Serial.println("Forward");
          delay(300);
        }
      }
    }
  }

  delay(200);
}
