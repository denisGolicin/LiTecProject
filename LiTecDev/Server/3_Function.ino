bool isAdmin(FB_msg& msg){
  
  for(int i = 0; i < MAX_ADMINS; i++){
    if(msg.chatID == user_chatID[i]) return true;
  }
  return false;
}

void showMenuAdmin(FB_msg& msg){
  bot.showMenuText("🏠 Отправляю меню управления!", 
  "Кухня\tA:✅\tA:❌\tB:✅\tB:❌\nКоридор\tC:✅\tC:❌\nКомната\tD:✅\tD:❌\nНастройки⚙\nСкрыть меню", 
  msg.chatID);
}
void showMenuUser(FB_msg& msg){
  bot.showMenuText("🏠 Отправляю меню управления!", 
  "Кухня\tA:✅\tA:❌\tB:✅\tB:❌\nКоридор\tC:✅\tC:❌\nКомната\tD:✅\tD:❌\nСкрыть меню", 
  msg.chatID);
}
int getCommandUser(FB_msg& msg){
  
  if(msg.text == "A:✅"){

    updateDevice(0x11, REQUEST_TYPE_RELE, REQUEST_RELE1_ON);
    kyx_A = true;
    
    for(int i = 0; i < MAX_USERS; i++){
      if(msg.chatID != user_chatID[i])  bot.sendMessage(msg.username + String(" включил(а) свет на кухне!✅"), user_chatID[i]);
    }
    return true;
  }
  if(msg.text == "A:❌"){
 
    updateDevice(0x11, REQUEST_TYPE_RELE, REQUEST_RELE1_OFF);
    kyx_A = false;
    for(int i = 0; i < MAX_USERS; i++){
      if(msg.chatID != user_chatID[i]) bot.sendMessage(msg.username + String(" выключил(а) свет на кухне!❌"), user_chatID[i]);
    }
    return true;
  }

  if(msg.text == "B:✅"){

    updateDevice(0x11, REQUEST_TYPE_RELE, REQUEST_RELE2_ON);
    kyx_B = true;
    
    for(int i = 0; i < MAX_USERS; i++){
      if(msg.chatID != user_chatID[i])  bot.sendMessage(msg.username + String(" включил(а) свет на кухне!✅"), user_chatID[i]);
    }
    return true;
  }
  if(msg.text == "B:❌"){
 
    updateDevice(0x11, REQUEST_TYPE_RELE, REQUEST_RELE2_OFF);
    kyx_B = false;
    for(int i = 0; i < MAX_USERS; i++){
      if(msg.chatID != user_chatID[i]) bot.sendMessage(msg.username + String(" выключил(а) свет на кухне!❌"), user_chatID[i]);
    }
    return true;
  }

  //----------------------------
  if(msg.text == "C:✅"){

    updateDevice(0x12, REQUEST_TYPE_RELE, REQUEST_RELE1_ON);
    kop_A = true;
    
    for(int i = 0; i < MAX_USERS; i++){
      if(msg.chatID != user_chatID[i])  bot.sendMessage(msg.username + String(" включил(а) свет в коридоре!✅"), user_chatID[i]);
    }
    return true;
  }
  if(msg.text == "C:❌"){
 
    updateDevice(0x12, REQUEST_TYPE_RELE, REQUEST_RELE1_OFF);
    
    kop_A = false;
    for(int i = 0; i < MAX_USERS; i++){
      if(msg.chatID != user_chatID[i]) bot.sendMessage(msg.username + String(" выключил(а) свет в коридоре!❌"), user_chatID[i]);
    }
    return true;
  }
  //-------------------------------------
  if(msg.text == "D:✅"){

    updateDevice(0x13, REQUEST_TYPE_RELE, REQUEST_RELE1_ON);
    kom_A = true;
    
    for(int i = 0; i < MAX_USERS; i++){
      if(msg.chatID != user_chatID[i])  bot.sendMessage(msg.username + String(" включил(а) свет в комнате!✅"), user_chatID[i]);
    }
    return true;
  }
  if(msg.text == "D:❌"){
 
    updateDevice(0x13, REQUEST_TYPE_RELE, REQUEST_RELE1_OFF);
    kom_A = false;
    for(int i = 0; i < MAX_USERS; i++){
      if(msg.chatID != user_chatID[i]) bot.sendMessage(msg.username + String(" выключил(а) свет в комнате!❌"), user_chatID[i]);
    }
    return true;
  }
  return false;
}
void updateDevice(byte deviceid, byte type, byte sInfo){
  uint32_t data;
  data = (data << 8) | REQUEST_SERVER_ID;
  data = (data << 8) | deviceid;
  data = (data << 8) | type;
  data = (data << 8) | sInfo;

  mySwitch.send(data, 32);
  return;
}
void updateSystem(){
  uint32_t data;
  data = (data << 8) | REQUEST_SERVER_ID;
  data = (data << 8) | 0x11;
  data = (data << 8) | REQUEST_TYPE_RELE;
  data = (data << 8) | (kyx_A) ? (REQUEST_RELE1_OFF) : (REQUEST_RELE1_ON);
  mySwitch.send(data, 32);

  data = (data << 8) | REQUEST_SERVER_ID;
  data = (data << 8) | 0x12;
  data = (data << 8) | REQUEST_TYPE_RELE;
  data = (data << 8) | (kop_A) ? (REQUEST_RELE1_OFF) : (REQUEST_RELE1_ON);
  mySwitch.send(data, 32);

  data = (data << 8) | REQUEST_SERVER_ID;
  data = (data << 8) | 0x13;
  data = (data << 8) | REQUEST_TYPE_RELE;
  data = (data << 8) | (kom_A) ? (REQUEST_RELE1_OFF) : (REQUEST_RELE1_ON);
  mySwitch.send(data, 32);
  return;
}

void sleepMode(){
  updateDevice(0x11, REQUEST_TYPE_RELE, REQUEST_RELE1_OFF);
  updateDevice(0x11, REQUEST_TYPE_RELE, REQUEST_RELE2_OFF);
  updateDevice(0x12, REQUEST_TYPE_RELE, REQUEST_RELE1_OFF);
  updateDevice(0x13, REQUEST_TYPE_RELE, REQUEST_RELE1_OFF);
  return;
}
