int deg_media = 0;
int i = 0;

int compassReadMedia(){
    for(i = 0; i < 10; i++){
        deg_media += sensor.compass();
    }
    deg_media = deg_media/10;
    write.verbose(String("DEG :") + deg_media + String("°"));
    return deg_media;
}

bool cdDeg (int deg_set, String direction, int deg){
	int deg_diff;
	int deg_fin;
    int deg_in = deg_set;

	if ((direction != LEFT) && (direction != RIGHT)){
		write.info("INVALID DIRECTION: " + String(direction));
		return false;
	}

	write.debug(String("---COMPASS---"));
    write.debug(String("SET: ") + String(deg_set));
    write.debug(String("DIR: " + direction));
    write.debug(String("DEG: ") + String(deg));

	if(direction == LEFT){
		deg_diff = deg_set - deg;

		if(deg_diff < 0){
            write.debug(String("CASE 1"));  
			while ((sensor.compass() - deg_diff) > 0) write.debug(String("CURR DEG: ") + String(sensor.compass()));
		}
		if(deg_diff >= 0){
            write.debug(String("CASE 2"));
			deg_fin = deg_set - deg;
			while (sensor.compass() > deg_fin)    write.debug(String("CURR DEG: ") + String(sensor.compass()));
		}
	}

	if(direction == RIGHT){
		deg_diff = 360 - (deg_set + deg);
        write.debug(String("DEG DIFF: ") + String(deg_diff));

		if(deg_diff < 0){
      write.debug(String("CASE 3 pt 1"));
			while ((deg_in + deg_diff) < 360){
        deg_in = sensor.compass();
        write.debug(String("COMP DEG: ") + String(sensor.compass()));
        write.debug(String("CURR DEG: ") + String(deg_in));
        write.debug(String("DEG + DIFF: ") + String(deg_in + deg_diff));
        }
      write.debug(String("CASE 3 pt 2"));
      while ((deg_in + deg_diff) < 0){
        deg_in = sensor.compass();
        write.debug(String("COMP DEG: ") + String(sensor.compass()));
        write.debug(String("CURR DEG: ") + String(deg_in));
        write.debug(String("DEG + DIFF: ") + String(deg_in + deg_diff));
        }
		}
		if(deg_diff >= 0){
            write.debug(String("CASE 4"));
			deg_fin = deg_set + deg;
			while(sensor.compass() < deg_fin) write.debug(String("CURR DEG: ") + String(sensor.compass()));
		}
	}
	write.debug(String("-------------"));
	return true;
}

String compassStraight (int deg_set){
    String result = "OK";
    int deg = compassReadMedia(); //deg is the live deg from the compass
    long timeSet = millis();
    write.info(String("DEG: ") + String(deg));
    write.info(String("DEG SET: ") + String(deg_set));
    int deg_diff = 0;
    if (deg_set > deg){
        result = "RIGHT";
        deg_diff = deg_set - deg;
    }
    
    if(deg_set < deg - 300){
        result = "RIGHT";
        deg_diff = 360 - deg_set + deg;
    }

    if (deg_set < deg ){
        result = "LEFT";
        deg_diff = deg - deg_set;
    }

    if (deg_set > deg + 300){
        result = "LEFT";
        deg_diff = 360 - deg + deg_set;
    }
    write.info(String("C_STRAIGHT FINISHED IN ") + String(millis() - timeSet) + String(" ms"));
    return String(result + " " + String(deg_diff));
}

String qmcCalibration() {
  int calibrationData[3][2];
  bool changed = false;
  bool done = false;
  int t = 0;
  int c = 0;

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
    Serial.println("CALIBRATING... Keep moving your sensor around.");
    c = millis();
  }
    t = millis();
  
  
  if ( (t - c > 5000) && !done) {
    done = true;
      
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
    return String(calibrationData[0][0] + String(" ") + calibrationData[0][1] + String(" ") + calibrationData[1][0] + String(" ") + calibrationData[1][1] + String(" ") + calibrationData[2][0] + String(" ") + calibrationData[2][1]);
    }
  }
}