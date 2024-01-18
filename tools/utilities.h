namespace utilities
{
	String get_time_str()
	{
		#if !defined(PLUS2)
			M5.Rtc.GetBm8563Time();

			String time = String(M5.Rtc.Hour) + ":" + String(M5.Rtc.Minute) + ":" + String(M5.Rtc.Second);
			if (time.length() < 8)
				time += "  ";
		#else
		    auto dt = M5.Rtc.getDateTime();
			String time = String(dt.time.hours) + ":" + String(dt.time.minutes) + ":" + String(dt.time.seconds);
			if (time.length() < 8)
				time += "  ";
		#endif
		return time;
	}

	int get_battery()
	{
		#if !defined(PLUS2)
			float b = M5.Axp.GetVbatData() * 1.1 / 1000;
		#else
			float b = StickCP2.Power.getBatteryVoltage() * 1.1 / 1000;
		#endif

		int battery = ((b - 3.0) / 1.2) * 100;
		
		if (battery > 100 || battery < 0)
			return -1;

		return battery;
	}

	String get_battery_str()
	{
		int battery = get_battery();

		if (battery == -1)
			return "...";

		return String(battery) + "%";
	}
	
	String gen_random_str(int length) {
		const char characters[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
		const int charactersLength = sizeof(characters) - 1;
		String randomString = "";

		for (int i = 0; i < length; i++) {
			int randomIndex = random(charactersLength);
			randomString += characters[randomIndex];
		}

		return randomString;
	}

	uint8_t* rand_mac() {
		static uint8_t macAddr[6];
		randomSeed(micros());
		for (int i = 0; i < 6; i++) {
			macAddr[i] = random(0, 256);
		}

		return macAddr;
	}
}
