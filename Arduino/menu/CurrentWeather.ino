// current weather tab

void CurrentWeatherLoop() { 
  OledWrite(0, 1, 1, "Getting weather..");
  RenderScene(); // render our scene
  display.clearDisplay(); // clear our oled display (removes old display items)
  while (Serial.available()) {
     Serial.println("hi");
  }
  CurrentWeatherLoop(); // loop
}
