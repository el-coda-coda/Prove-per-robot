long commandRead (){
    if(Serial.available()){
        String command = Serial.readString();
        Serial.print("$:" + command);
        
        //general
        if(command.startsWith("turn off")){ //all engines switch off
            output = OFF;
            generalMessage = true;
            drivEngineMessage = true;
            cutEngineMessage = true;
            sensorMessage = false; 
        }

        //driving engines
        if(command.startsWith("engine forward")){
            output = forward;
            generalMessage = false;
            cutEngineMessage = false;
            sensorMessage = false;
            drivEngineMessage = true; 
        }   
        if(command.startsWith("engine back")){
            output = back;
            generalMessage = false;
            cutEngineMessage = false;
            sensorMessage = false;
            drivEngineMessage = true; 
        }
        if(command.startsWith("engine right")){
            output = right;
            generalMessage = false;
            cutEngineMessage = false;
            sensorMessage = false;
            drivEngineMessage = true; 
        }
        if(command.startsWith("engine left")){
            output = left;
            generalMessage = false;
            cutEngineMessage = false;
            sensorMessage = false;
            drivEngineMessage = true; 
        }
        if(command.startsWith("engine stop")){
            output = OFF;
            generalMessage = false;
            cutEngineMessage = false;
            sensorMessage = false;
            drivEngineMessage = true; 
        }

        //cutter engine
        if(command.startsWith("cutter on")){ //switch on the cutter
            output = cutterPerc;
            generalMessage = false;
            drivEngineMessage = false;
            sensorMessage = false;
            cutEngineMessage = true; 
        }
        if(command.startsWith("cutter off")){ //switch off the cutter
            output = OFF;
            generalMessage = false;
            drivEngineMessage = false;
            sensorMessage = false;
            cutEngineMessage = true; 
        }

        //battery
        if(command.startsWith("battery lvl")){ //print the percentage of the battery
            output = long(read.batteryLevel());
            generalMessage = false;
            drivEngineMessage = false;
            cutEngineMessage = false;
            sensorMessage = true;
        }
    }
    Serial.print("Debug commandRead ");
    Serial.println(output);
    /*Serial.print("driv engine message ");
    Serial.println(drivEngineMessage);
    Serial.print("cut engine message ");
    Serial.println(cutEngineMessage);
    Serial.print("general message ");
    Serial.println(generalMessage);
    Serial.print("battery message ");
    Serial.println(sensorMessage);*/
    return output;
}

void turnOff(){
    if(generalMessage){
        motor.off();
        cut.off();
    }
}