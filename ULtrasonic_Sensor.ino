/*
  SparkFun Inventor’s Kit
  Circuit 3B-Distance Sensor

  Measure distance using an ultrasonic distance sensor in centimeters with filtering.
  The program stores 4 distance values per second, removes the largest and smallest,
  calculates the mean of the remaining values, and prints it every 1 second.

  This sketch was written by SparkFun Electronics, modified for filtering by ChatGPT.
  This code is completely free for any use.

  View circuit diagram and instructions at: https://learn.sparkfun.com/tutorials/sparkfun-inventors-kit-experiment-guide---v41
  Download drawings and code at: https://github.com/sparkfun/SIK-Guide-Code
*/

const int trigPin = 11;           //connects to the trigger pin on the distance sensor
const int echoPin = 12;           //connects to the echo pin on the distance sensor

float distanceValues[4];          //array to store 4 distance readings

void setup() {
  Serial.begin(9600);        //set up a serial connection with the computer

  pinMode(trigPin, OUTPUT);   //the trigger pin will output pulses of electricity
  pinMode(echoPin, INPUT);    //the echo pin will measure the duration of pulses coming back from the distance sensor
}

void loop() {
  // Collect 4 distance readings (4 times per second)
  for (int i = 0; i < 4; i++) {
    distanceValues[i] = getDistance();
    delay(250);  // 4 readings per second
  }

  // Calculate the mean of the filtered values
  float filteredMean = calculateFilteredMean(distanceValues);

  // Output the filtered mean
  Serial.print("Filtered Mean Distance: ");
  Serial.print(filteredMean);
  Serial.println(" cm");

  delay(1000); // Wait 1 second before taking new readings
}

//------------------FUNCTIONS-------------------------------

//RETURNS THE DISTANCE MEASURED BY THE HC-SR04 DISTANCE SENSOR IN CENTIMETERS
float getDistance() {
  float echoTime;
  float calculatedDistance;

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  echoTime = pulseIn(echoPin, HIGH);
  calculatedDistance = (echoTime * 0.0343) / 2;

  return calculatedDistance;
}

//CALCULATES THE MEAN OF THE ARRAY AFTER REMOVING THE LARGEST AND SMALLEST VALUES
float calculateFilteredMean(float values[4]) {
  float minVal = values[0];
  float maxVal = values[0];
  float sum = 0;

  // Find the minimum and maximum values
  for (int i = 0; i < 4; i++) {
    if (values[i] < minVal) minVal = values[i];
    if (values[i] > maxVal) maxVal = values[i];
    sum += values[i];
  }

  // Calculate the mean of the middle two values
  float filteredSum = sum - minVal - maxVal;
  return filteredSum / 2.0;
}
