String angleUS (int distanceRight, int distanceLeft){
    String result;
    int distanceOffSet = 0;
    int deg, distanceMax;
    if ((distanceRight < stop_distance) || (distanceLeft < stop_distance)){
        if (distanceRight > distanceLeft){
            distanceOffSet = distanceLeft;
            distanceMax = distanceRight - distanceOffSet;

            deg = calc.distaneToDeg(distanceMax, WIDTH);   
            result = RIGHT;// + " " + String(deg);
        } 
        if (distanceLeft > distanceRight){
            distanceOffSet = distanceRight;
            distanceMax = distanceLeft - distanceOffSet;

            deg = calc.distaneToDeg(distanceMax, WIDTH); 
            result = LEFT; //+ "  " + String(deg);
        }
        if (distanceLeft == distanceRight)  result = LEFT;// + "  " + String(90); //this is just a personal desicion, anywey we can decide to make the robot turn right or go back
    }
    else    result = STRAIGHT;
    write.info(String("angleUS: ") + String(result));
    return result;
}