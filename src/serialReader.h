long commandRead (){
    if(Serial.available()){
        String command = Serial.readString();
        Serial.print("$:" + command);
        //general
        if(command.startsWith("turn off")){
            output = OFF;
            generalMessage = true;
            drivEngineMessage = true;
            cutEngineMessage = true;
            batteryMessage = false; 
        }
        //driving engines
        if(command.startsWith("engine forward")){
            output = forward;
            generalMessage = false;
            cutEngineMessage = false;
            batteryMessage = false;
            drivEngineMessage = true; 
        }   
        if(command.startsWith("engine back")){
            output = back;
            generalMessage = false;
            cutEngineMessage = false;
            batteryMessage = false;
            drivEngineMessage = true; 
        }
        if(command.startsWith("engine right")){
            output = right;
            generalMessage = false;
            cutEngineMessage = false;
            batteryMessage = false;
            drivEngineMessage = true; 
        }
        if(command.startsWith("engine left")){
            output = left;
            generalMessage = false;
            cutEngineMessage = false;
            batteryMessage = false;
            drivEngineMessage = true; 
        }
        if(command.startsWith("engine stop")){
            output = OFF;
            generalMessage = false;
            cutEngineMessage = false;
            batteryMessage = false;
            drivEngineMessage = true; 
        }
        //cutter engine
        if(command.startsWith("cutter on")){
            output = cutterPerc;
            generalMessage = false;
            drivEngineMessage = false;
            batteryMessage = false;
            cutEngineMessage = true; 
        }
        if(command.startsWith("cutter off")){
            output = OFF;
            generalMessage = false;
            drivEngineMessage = false;
            batteryMessage = false;
            cutEngineMessage = true; 
        }
        if(command.startsWith("battery lvl")){
            output = long(read.batteryLevel());
            generalMessage = false;
            drivEngineMessage = false;
            cutEngineMessage = false;
            batteryMessage = true;
        }
    }
    Serial.println("Debug commandRead " + String(output));
    Serial.println();
    Serial.print("Driv engine message ");
    Serial.println(drivEngineMessage);
    Serial.print("cut engine message ");
    Serial.println(cutEngineMessage);
    Serial.print("general message ");
    Serial.println(generalMessage);
    Serial.print("battery message ");
    Serial.println(batteryMessage);
    return output;
}

void turnOff(){
    if(generalMessage){
        motor.off();
        cut.off();
    }
}