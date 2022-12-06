void newMsg(FB_msg& msg) {
  //Serial.println("Telegram request");
  if(msg.text == "/sendID"){
    bot.sendMessage(String(msg.chatID), msg.chatID);
    return;
  }

  //if(isAdmin(msg)) bot.sendMessage("Ну да, ты админ 😉", msg.chatID);

  if(msg.text == "/start"){    
    
    if(isAdmin(msg)){}
    else{
      if(!use_all){
        bot.sendMessage("Хорошая попытка, попробуй еще раз 😉", msg.chatID);
        bot.sendSticker("CAACAgIAAxkBAAEFuuljD8GPNybqr83-t6GMPKMrGSw3fwAC1gADVp29Cgl1yQziLyEKKQQ", msg.chatID);
        return;
      }
      for(int i = MAX_ADMINS; i < MAX_USERS; i++){
        if(msg.chatID == user_chatID[i]){
  
          showMenuUser(msg);
          
          return;
        }
        
      }
      for(int i = MAX_ADMINS; i < MAX_USERS; i++){
        if(user_chatID[i] == "NaN"){
          user_chatID[i] = msg.chatID;
          break;
        }
        else continue;
        bot.sendMessage("К сожалению, не удалось подключиться!😢", msg.chatID);
        bot.sendSticker("CAACAgIAAxkBAAEFvDVjERyWFdCcgQw6QUPGT4P7QUnCiQAC5AADVp29Chab7Y_u8TUEKQQ", msg.chatID);
        return;
      }
    }

    if(msg.chatID != "707106984") bot.sendSticker("CAACAgIAAxkBAAEFuudjD7_uabNfzqPL77Dj_9ifju3zNwAC0wADVp29CvUyj5fVEvk9KQQ", msg.chatID);
    else bot.sendSticker("CAACAgIAAxkBAAEFuwxjD9R_VwKmpscr1XDrJGQB0GbwKwAC0gADVp29Cg4FcjZ1gzWKKQQ", msg.chatID);
    
    bot.sendMessage("Привет, " + String(msg.username) + "! 🤖", msg.chatID);
    if(isAdmin(msg)) showMenuAdmin(msg);
    else showMenuUser(msg);

    for(int i = 0; i < MAX_USERS; i++){
      if(msg.chatID != user_chatID[i]){
        bot.sendMessage(msg.username + String(" теперь имеет доступ к управлению квартиры😎"), user_chatID[i]);
        bot.sendSticker("CAACAgIAAxkBAAEFvDNjERj_SUWZcNYo8bNfEO79a7s58wAC4QADVp29ClvBlItA-NOgKQQ", user_chatID[i]);
      }
    }
    return;
  }

  if(isAdmin(msg)){}
  else{
    if(!use_all){
      bot.sendMessage("Доступ закрыт, попробуй еще раз 😉", msg.chatID);
      bot.sendSticker("CAACAgIAAxkBAAEFuuljD8GPNybqr83-t6GMPKMrGSw3fwAC1gADVp29Cgl1yQziLyEKKQQ", msg.chatID);
      return;
    }
    else{
      for(int i = MAX_ADMINS; i < MAX_USERS; i++){
        if(msg.chatID == user_chatID[i]) break;
        if(i >= MAX_USERS - 1){
          bot.sendMessage("Активирован гостевой режим!👨‍👩‍👧‍👦", msg.chatID);
          bot.sendMessage("Авторизируйтесь, введя команду /start 😉, чтобы снять блокировку!", msg.chatID);
          bot.sendSticker("CAACAgIAAxkBAAEFvGpjETbVmJEnQyFlzoOtQIC6X7Le0gAC3wADVp29ChBIfJEjpSf9KQQ", msg.chatID);
          return;
        }
      }
    }
  }

  if(msg.text == "Обновить" || msg.text == "обновить" || msg.text == "/Обновить" || msg.text == "/обновить"){

    for(int i = 0; i < MAX_USERS; i++){
      if(msg.chatID == user_chatID[i]) {
        if(isAdmin(msg)) showMenuAdmin(msg);
        else showMenuUser(msg);
        return;
      }
    }
    return;
  }

  if(msg.text == "Скрыть меню"){

    bot.showMenuText("Закрываю меню",
    "Открыть меню", 
    msg.chatID);
    bot.sendSticker("CAACAgIAAxkBAAEFvDFjERiX5v6U7xOAA6r94RjEw7NeyQAC2AADVp29CokJ3b9L8RQnKQQ", msg.chatID);
    return;
  }

  if(msg.text == "Открыть меню"){

    if(isAdmin(msg)) showMenuAdmin(msg);
    else showMenuUser(msg);
    bot.sendSticker("CAACAgIAAxkBAAEFvDFjERiX5v6U7xOAA6r94RjEw7NeyQAC2AADVp29CokJ3b9L8RQnKQQ", msg.chatID);
    return;
  }

  if(msg.text == "Назад"){

    if(isAdmin(msg)) showMenuAdmin(msg);
    else showMenuUser(msg);
    if(sendMessageAll == msg.chatID.toInt()) sendMessageAll = 0;
    return;
  }

  if(msg.text == "Настройки⚙"){

    if(!isAdmin(msg)) return;
    bot.showMenuText(
    "Открываю настройки:", "Информация о системе\nГостевой режим\nРежим сна\nЗагрузить обновление\nНазад", 
    msg.chatID);
    bot.sendSticker("CAACAgIAAxkBAAEFvDFjERiX5v6U7xOAA6r94RjEw7NeyQAC2AADVp29CokJ3b9L8RQnKQQ", msg.chatID);
    return;
    
  }

  if(msg.text == "Загрузить обновление") {

    if(!isAdmin(msg)) return;
    if(!updateFlag){
      bot.sendMessage("Жду отправки файла .bin", msg.chatID);
      bot.sendSticker("CAACAgIAAxkBAAEFwdFjFRIPYBjG17gVnKxxtF22jl8mYgAC5QADVp29CggLFmSVBdGKKQQ", msg.chatID);
      updateFlag = true;
    }
    else{
      bot.sendMessage("Значит, в следующий раз...", msg.chatID);
      bot.sendSticker("CAACAgIAAxkBAAEFwdNjFRKlPjzE476qJDEayPUXG7hfhgACwAADVp29Ct1dnTI9q-YvKQQ", msg.chatID);
      updateFlag = false;
    }
    return;
  }

  if(msg.text == "Информация о системе"){
    if(!isAdmin(msg)) return;
    bot.sendMessage(String(VERSION) + "\n"
    + "SSID: " + WIFI_SSID + "\n"
    + "PASS: " + WIFI_PASS + "\n"
    + "Загрузка обновления: " + String((!updateFlag) ? ("выключена") : ("включена")) +
    "\nlocalhost: " + IPaddress
    
    , msg.chatID);
    return;
      
  }
  if(msg.text == "Режим сна"){
    //if(sleepModeFlag) return;
    if(!isAdmin(msg)) return;
    //sleepModeFlag = true;
    for(int i = 0; i < MAX_USERS; i++){
      if(msg.chatID != user_chatID[i]){ bot.sendMessage(msg.username 
      + " активировал(а) режим сна!", user_chatID[i]); }
      
      bot.sendMessage("Польностью выключенo всё освещение в доме!\nДоброй ночи и спокойных снов!\nДождитесь завершение режима(5-10 сек).", user_chatID[i]);
      bot.sendSticker("CAACAgIAAxkBAAEFxBxjFmieMo-z1DEtx6BCx7XR4J_Q8gACUAADQbVWDEsUyxvLOcdYKQQ", user_chatID[i]);
    }
    sleepMode();
    //sleepModeFlag = false;
    
    return;
      
  }

  if(msg.text == "Гостевой режим"){
    if(!isAdmin(msg)) return;
    
    if(!use_all){
      use_all = true;
      bot.sendMessage("Гостевой режим активирован!", msg.chatID);
      bot.sendSticker("CAACAgIAAxkBAAEFuwNjD9A4xmy-emu9j5nxo4BMZRfpQAAC3gADVp29CqXvdzhVgxXEKQQ", msg.chatID);
      
      for(int i = MAX_ADMINS; i < MAX_USERS; i++) user_chatID[i] = "NaN";
    }
    else{
      use_all = false;
      bot.sendMessage("Гостевой режим выключен!", msg.chatID);
      bot.sendSticker("CAACAgIAAxkBAAEFuv9jD8-7KNmmK737RTp1qN5VAj6YzQACxgADVp29Cm0JjjaJHS0XKQQ", msg.chatID);
      
      for(int i = MAX_ADMINS; i < MAX_USERS; i++) user_chatID[i] = "NaN";
    }
    return;
  }

  if(getCommandUser(msg)) return; 
  if (updateFlag && isAdmin(msg) && msg.OTA && msg.fileName == "update.bin"){

    bot.sendMessage("Найден подходящий файл, начинаю загрузку...", msg.chatID);
    bot.sendMessage("Сервер будет перезапущен!", msg.chatID);
    bot.sendSticker("CAACAgIAAxkBAAEFwdVjFR59gpf1NqE4OnN_cprZzpgBWAACxgADVp29Cm0JjjaJHS0XKQQ", msg.chatID);
    bot.update();
  }
  bot.sendSticker("CAACAgIAAxkBAAEFuwVjD9CckiXNTYDzOz119Hi1W16WOAAC4wADVp29Cg_4Isytpgs3KQQ", msg.chatID);
}
