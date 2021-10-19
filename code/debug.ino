void serialMonitor(float speed, int sat ) {
    Serial.print("KM/H: ");
    Serial.print(speed);
    Serial.println();

    Serial.print("SAT: ");
    Serial.print(sat);
    Serial.println();
    Serial.println("++++++++++++++++++");

    Serial.print("RANDOM TEST FLOAT: ");
    Serial.println();
    Serial.println(randomDouble(25.00, 32.00), 2);

    Serial.println("++++++++++++++++++");
}
