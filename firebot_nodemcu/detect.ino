void detect() {
  // NodeMCU Communication with Arduino NANO ========================
  unsigned long currentMillis = millis();
  if (currentMillis - prevMillis >= interval) {
    prevMillis = currentMillis;
    String data = "";
    while (Serial.available() > 0) {
      data += char(Serial.read());
    }
    data.trim();

    if (data != "") {
      int index = 0;
      for (int i = 0; i <= data.length(); i++) {
        char parsing = '!';
        if (data[i] != parsing) {
          arrData[index] += data[i];
        }
        else {
          index++;
        }
      }
      // urutan data 0 = asap, 1 = api
      if (index == 1) {
        Serial.println(arrData[0]);
        Serial.println(arrData[1]);
      }
      //change to int
      data1 = arrData[0].toInt();
      data2 = arrData[1].toInt();
      arrData[0] = "";
      arrData[1] = "";
    }
    //permintaan data ke nano
  }
  // ====================== END ========================
}
