bool internalTemperature = true; // Flag to track whether to display internal or external temperature

void draw(void) {
  float t, h;
  if (internalTemperature) {
    // Read internal temperature and humidity
    t = dht_internal.readTemperature();
    h = dht_internal.readHumidity();
    u8g2.setFont(u8g2_font_helvB10_tf);
    u8g2.setCursor(0, 16);
    u8g2.print("         Internal");
  } else {
    // Read external temperature and humidity
    t = dht_external.readTemperature();
    h = dht_external.readHumidity();
    u8g2.setFont(u8g2_font_helvB10_tf);
    u8g2.setCursor(0, 16);
    u8g2.print("         External");
  }

  // Comment these lines later --> Current purpose debugging
  if(internalTemperature){
    Serial.println("\tInternal to Display:");
    Serial.println("\tTemp: " + (String)t + "\t\t\tHumi: " + (String)h);
  }
  else{
    Serial.println("\tExternal to Display:");
    Serial.println("\tTemp: " + (String)t + "\t\t\tHumi: " + (String)h);
  }
  // Print temperature and humidity
  u8g2.setFont(u8g2_font_helvB18_tf);
  u8g2.setCursor(0, 42);
  u8g2.print("T= "); u8g2.print(t); u8g2.print(" *C");
  u8g2.setCursor(0, 64);
  u8g2.print("H= "); u8g2.print(h); u8g2.print(" %");
}

void updateDisplay(void) {
  // // Wait a few seconds between measurements.
  delay(3000);

  internalTemperature = !internalTemperature;
  u8g2.firstPage();
  do {
    draw();
  } while ( u8g2.nextPage() );
}
