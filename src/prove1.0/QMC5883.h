int deg_media = 0;
int i = 0;

int compassReadMedia(){
    for(i = 0; i < 10; i++){
        deg_media += sensor.compass();
    }
    deg_media = deg_media/10;
    return deg_media;
}

int * firstCompass (){
  int compass [] = {};
  int i = 0;
  long timeSet = millis();
  int deg_in = sensor.compass();
  int deg_last = deg_in + 100; // + 100 is just a way to make deg_last and dag_in different, in order to can use the while
  while ((deg_in > (deg_last + 1)) || (deg_in < (deg_last - 1))){
    deg_last = deg_in;
    deg_in = sensor.compass();
    compass [i] = deg_in;
    i ++;
    compass [i] = deg_last;
    i++;
    delay(500);
  }
  write.debug(String("FIRST COMPASS completed in: " + String(millis() - timeSet) + " ms"));
  return compass;
}

bool cdDeg (int deg_set, int direction, int deg){
  int deg_diff;
  int deg_fin;
  int deg_in = deg_set;

  if ((direction != LEFT) && (direction != RIGHT)){
  	write.info("INVALID DIRECTION: ");
  	return false;
  }

  if(direction == LEFT){
  	deg_diff = deg_set - deg; 
		if(deg_diff < 0){  
  		while (((deg_in - deg_diff) >= 0) && (deg_in < 359))  deg_in = sensor.compass();
  		while ((deg_in - deg_diff) > 360)  deg_in = sensor.compass();
    }
  	if(deg_diff >= 0){
  		deg_fin = deg_set - deg;
  		while (deg_in > deg_fin)  deg_in = sensor.compass();
  	}
  } 
  if(direction == RIGHT){
  	deg_diff = 360 - (deg_set + deg);
		if(deg_diff < 0){
  		while ((deg_in + deg_diff) < 359 && (deg_in > 0))  deg_in = sensor.compass();
      while ((deg_in + deg_diff) < 0)  deg_in = sensor.compass();
  	}
  	if(deg_diff >= 0){
  		deg_fin = deg_set + deg;
  		while (deg_in < deg_fin) deg_in = sensor.compass();
  	}
  }
  return true;
}

int compassStraight (int deg_set){
    int result = STRAIGHT;
    int deg = compassReadMedia(); //deg is current deg from the compass
    long timeSet = millis();

    if (deg_set > deg)  result = RIGHT;
    if(deg_set < (deg - 300)) result = RIGHT;
    if (deg_set < deg ) result = LEFT;
    if (deg_set > deg + 300)  result = LEFT;
    write.verbose(String("C_STRAIGHT completed in " + String(millis() - timeSet) + " ms"));
    return result;
}

void qmcCalibration() {
  int calibrationData[3][2];
  bool changed = false;
  bool done = false;
  int t = 0;
  int c = 0;

  Serial.print("CALIBRATING ");
  while (true){
    int x, y, z;
  
    // Read compass values
    qmc.read();

    // Return XYZ readings
    x = qmc.getX();
    y = qmc.getY();
    z = qmc.getZ();

    changed = false;

    if(x < calibrationData[0][0]) {
      calibrationData[0][0] = x;
      changed = true;
    }
    if(x > calibrationData[0][1]) {
      calibrationData[0][1] = x;
      changed = true;
    }

    if(y < calibrationData[1][0]) {
      calibrationData[1][0] = y;
      changed = true;
    }
    if(y > calibrationData[1][1]) {
      calibrationData[1][1] = y;
      changed = true;
    }

    if(z < calibrationData[2][0]) {
      calibrationData[2][0] = z;
      changed = true;
    }
    if(z > calibrationData[2][1]) {
      calibrationData[2][1] = z;
      changed = true;
    }

    if (changed && !done) {
      Serial.print("#");
      c = millis();
    }
      t = millis();
    
    
    if ( (t - c > 5000) && !done) {
      done = true;
      Serial.println();
      Serial.print("setCalibration: ");
      Serial.print(calibrationData[0][0]);
      Serial.print(", ");
      Serial.print(calibrationData[0][1]);
      Serial.print(", ");
      Serial.print(calibrationData[1][0]);
      Serial.print(", ");
      Serial.print(calibrationData[1][1]);
      Serial.print(", ");
      Serial.print(calibrationData[2][0]);
      Serial.print(", ");
      Serial.print(calibrationData[2][1]);
      Serial.println(");");
      qmc.setCalibration(calibrationData[0][0], calibrationData[0][1], calibrationData[1][0], calibrationData[1][1], calibrationData[2][0], calibrationData[2][1]);
    }
  }
}