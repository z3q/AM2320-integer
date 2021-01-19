# AM2320 sensor library for Arduino/Launchpad
Original Arduino AM2320 I2C temperature/humidity library: https://github.com/Ten04031977/AM2320-master

The difference is usage of integer math. Temperature is multiplied by 10 and can be printed using code like:

    lcd.print(th.t / 10);
    lcd.print(".");
    lcd.print(abs(th.t) % 10);
    
Nobody cares about relative humidity % fraction, so it is simply rounded (truncated).
