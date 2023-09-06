#define OutputA 2
#define OutputB 3

int Counts = 0;

int LastAState;
int UpdateAState;
int UpdateBState;

void setup() {
  //Initializing pins
  pinMode(OutputA, INPUT);
  pinMode(OutputB, INPUT);
  //Initializing the first state of pin A
  LastAState = digitalRead(OutputA);
  
  Serial.begin(9600);
}

void loop() {
  //Getting the new pin A and pin B states
  UpdateAState = digitalRead(OutputA);
  UpdateBState = digitalRead(OutputB);
  //Seeing if pin A changed states
  if(UpdateAState != LastAState){ 
    if(UpdateAState != UpdateBState){
      Counts++;
    } else{
      Counts--;
    }
  }
  Serial.println(Counts/2);
  //Getting the state of pin A for the next iteration
  LastAState = UpdateAState;
}
