long commandRead (){
    if(Serial.available()){
        String command = Serial.readString();
        Serial.print("$:" + command);
        //general
        if(command.startsWith("turn on"))   output = ON;
        if(command.startsWith("turn off"))  output = OFF;
        //driving engines
        if(command.startsWith("engine forward"))   output = forward;
        if(command.startsWith("engine back"))  output = back;
        if(command.startsWith("engine right")) output = right;
        if(command.startsWith("engine left"))  output = left;
        //cutter engine
        if(command.startsWith("cutter on")) output = CUT_ON * cutterPerc;
        if(command.startsWith("cutter off"))    output = CUT_OFF;
    }
//    Serial.println("Debug commandRead " + String(output));
    return output;
}