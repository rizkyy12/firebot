void handleNewMsg(int numNewMsg) {
  Serial.println(String(numNewMsg));

  for (int i = 0; i < numNewMsg; i++) {

    String chat_id = String(myBot.messages[i].chat_id);
    String pesan = myBot.messages[i].text;
    String from_name = myBot.messages[i].from_name;
    String welcome, info_bot, fire_status, info_status;

    if (from_name == "") {
      from_name = "Guest";
    }

    else if (pesan == (bot_info)) {
      info_bot = "fireBot merupakan bot Telegram yang digunakan untuk ";
      info_bot += "melaporkan titik api yang dapat memicu terjadinya kebakaran.\n";
      info_bot += "Project ini dibuat untuk menyelesaikan tugas pada mata kuliah Mikrokontroler 2.\n";
      info_bot += "Group : Rizky Andhika A & M. Zaky Al-Farish";
      myBot.sendMessage(chat_id, info_bot, "");
    }

    else if (pesan == (bot_start)) {
      welcome = "Selamat datang di bot kami, " + from_name + "!\n";
      welcome += "Pendeteksi titik api dengan peringatan dini melalui Telegram.\n";
      welcome += (bot_info);
      welcome += " <-- info mengenai Bot\n";
      welcome += (bot_status);
      welcome += " <-- status kondisi saat ini";
      myBot.sendMessage(chat_id, welcome, "Markdown");
    }

    if (asap >= 10 and sensorValue_d == 0) {
      fire_status = "Api kecil terdeteksi pada ruangan 1 \n";
      myBot.sendMessage(fire_status, "");
      String pesan = myBot.messages[i].text;
      if (pesan == (bot_status)) {
        info_status = "Ruangan 1 status TIDAK AMAN";
        myBot.sendMessage(chat_id, info_status, "");
      }
      delay(100);
    }

    else if (asap < 9 and sensorValue_d == 1) {
      String pesan = myBot.messages[i].text;
      if (pesan == (bot_status)) {
        info_status = "Ruangan 1 status AMAN";
        myBot.sendMessage(chat_id, info_status, "");
      }
    }
  }
}
