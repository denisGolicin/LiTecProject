// конструктор страницы
void build() {
  BUILD_BEGIN();
  GP.THEME(GP_DARK);
  GP.AJAX_UPDATE("val");

  GP.LABEL("Панель управления домом");
  GP.HR();
  GP.LABEL("Температура: 26 °С"); GP.BREAK();
  GP.LABEL("Влажность: 56%");     GP.BREAK();
  GP.HR();
  
  GP.TITLE("Кухня", "t1");
  GP.LABEL("Люстра A: ");
  GP.SWITCH("kyx_A", kyx_A);  GP.BREAK();
  GP.LABEL("Люстра B: ");
  GP.SWITCH("kyx_B", kyx_B);  GP.BREAK();
  GP.HR();

  GP.TITLE("Комната", "t1");
  GP.LABEL("Люстра A: ");
  GP.SWITCH("kom_A", kom_A);  GP.BREAK();
  GP.HR();

  GP.TITLE("Коридор", "t1");
  GP.LABEL("Люстра A: ");
  GP.SWITCH("kop_A", kop_A);  GP.BREAK();
  GP.LABEL("Датчик движения: ");
  GP.CHECK("kop_moveSensor", kop_moveSensor);    GP.BREAK();
  GP.LABEL("Интервал"); 
  GP.LABEL("", "val"); 
  GP.LABEL("секунд"); GP.BREAK();
  GP.SLIDER("kop_moveSensorInterval", kop_moveSensorInterval, 10, 60); GP.BREAK();
  GP.HR();

  GP.BUTTON("btn", "Обновить");
  GP.BUTTON("btn", "Настройки");
  GP.HR();
  GP.LABEL(VERSION);

  BUILD_END();
}

void action() {
  if (portal.update("val")) portal.answer(kop_moveSensorInterval); 
  // был клик по компоненту
  if (portal.click()) {
    if (portal.click("kop_moveSensorInterval")) {
      kop_moveSensorInterval = portal.getInt("kop_moveSensorInterval");
      updateDevice(0x12, REQUEST_TYPE_MOVE_SENSOR, byte(kop_moveSensorInterval));
    }
    if (portal.click("kop_moveSensor")) {
      kop_moveSensor = portal.getCheck("kop_moveSensor");
      updateDevice(0x12, REQUEST_TYPE_MOVE_SENSOR, (kop_moveSensor) ? (REQUEST_MOVE_SENSOR_ON) : (REQUEST_MOVE_SENSOR_OFF));
    }
    if (portal.click("kyx_A")) {
      kyx_A = portal.getCheck("kyx_A");

      updateDevice(0x11, REQUEST_TYPE_RELE,(kyx_A) ? (REQUEST_RELE1_ON) : (REQUEST_RELE1_OFF));
      
      //bot.sendMessage("kyx_A:" + String(kyx_A), "1763784965");
      return;
    }
    if (portal.click("kyx_B")) {
      kyx_B = portal.getCheck("kyx_B");

      updateDevice(0x11, REQUEST_TYPE_RELE,(kyx_B) ? (REQUEST_RELE2_ON) : (REQUEST_RELE2_OFF));
      
      //bot.sendMessage("kyx_A:" + String(kyx_A), "1763784965");
      return;
    }
    if (portal.click("kop_A")) {
      kop_A = portal.getCheck("kop_A");

      updateDevice(0x12, REQUEST_TYPE_RELE, (kop_A) ? (REQUEST_RELE1_ON) : (REQUEST_RELE1_OFF));
      
      //bot.sendMessage("kyx_A:" + String(kyx_A), "1763784965");
      return;
    }
    if (portal.click("kom_A")) {
      kom_A = portal.getCheck("kom_A");

      updateDevice(0x13, REQUEST_TYPE_RELE, (kom_A) ? (REQUEST_RELE1_ON) : (REQUEST_RELE1_OFF));
      
      //bot.sendMessage("kyx_A:" + String(kyx_A), "1763784965");
      return;
    }
  }
}
