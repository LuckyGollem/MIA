#define OutputA 2
#define OutputB 3

int Counts = 0;

int UpdateAState;
int UpdateBState;

void InterruptFunc(){
    if(digitalRead(OutputA) != digitalRead(OutputB)){
      Counts++;
    } else{
      Counts--;
    }
}

void setup() {
  //Initializing pins
  pinMode(OutputA, INPUT);
  pinMode(OutputB, INPUT);

  attachInterrupt(digitalPinToInterrupt(OutputA), InterruptFunc, CHANGE);

  Serial.begin(9600);
}

void loop() {

  //Seeing if pin A changed states
  Serial.println(Counts/2);
}
