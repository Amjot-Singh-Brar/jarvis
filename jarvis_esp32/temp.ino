String internal(){
  float humidity_internal = dht_internal.readHumidity();
  float temperature_internal = dht_internal.readTemperature();

  if (isnan(humidity_internal) || isnan(temperature_internal)) {
    Serial.print("\n\nBoatTemp: " + (String)temperature_internal);
    Serial.print("BoatHumi: \n\n" + (String)humidity_internal);
    return "Failed to read from internal sensor!";
  }else{
    String internal_temp_humidity = "";
    internal_temp_humidity = "Humidity_internal: " + (String)humidity_internal;
    internal_temp_humidity += " %\t";
    internal_temp_humidity += "Temperature_internal: " + (String)temperature_internal + " *C";
    return internal_temp_humidity;
  }
}

String external(){
  float humidity_external = dht_external.readHumidity();
  float temperature_external = dht_external.readTemperature();

  if (isnan(humidity_external) || isnan(temperature_external)) {
    return "Failed to read from external sensor!";
  }else{
    String external_temp_humidity = "";
    external_temp_humidity = "Humidity_external: " + (String)humidity_external;
    external_temp_humidity += " %\t";
    external_temp_humidity += "Temperature_external: " + (String)temperature_external + " *C";
    return external_temp_humidity;
  }
}


