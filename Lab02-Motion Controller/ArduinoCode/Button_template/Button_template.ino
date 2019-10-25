/***** YOUR CODE HERE (START) *****/
// TODO: set the buttonPin
int buttonPin = D3;
/****** YOUR CODE HERE (END) ******/
int buttonVal;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  /***** YOUR CODE HERE (START) *****/
  // TODO: set pin mode
  pinMode(buttonPin, INPUT);
  
  /****** YOUR CODE HERE (END) ******/
}

void loop() {
  // put your main code here, to run repeatedly:

  /***** YOUR CODE HERE (START) *****/
  // TODO: read data from buttonPin with digitalRead()
  buttonVal = digitalRead(buttonPin);

  // TODO: print the value read from buttonPin to console
  Serial.println(buttonVal);
  
  /****** YOUR CODE HERE (END) ******/
  
  delay(1000);
}
