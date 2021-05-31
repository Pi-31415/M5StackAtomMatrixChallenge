
float temperature = 0;
float humidity = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial);


  // init the CSV file with headers
  Serial.println("temperature,humidity");
}

void loop() {
  // read the sensors values
  temperature = M5.IMU.getTempData(&tempC);
  

  // print each of the sensor values
  Serial.print(temperature); 
 

  // wait 1 second to print again
  delay(1000);
}