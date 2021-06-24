<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * led_hw_brightness_mon.c
 *
 * This program monitors LED brightness level changes having its origin
 * in hardware/firmware, i.e. outside of kernel control.
 * A बारtamp and brightness value is prपूर्णांकed each समय the brightness changes.
 *
 * Usage: led_hw_brightness_mon <device-name>
 *
 * <device-name> is the name of the LED class device to be monitored. Pressing
 * CTRL+C will निकास.
 */

#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <poll.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <समय.स>
#समावेश <unistd.h>

#समावेश <linux/uleds.h>

पूर्णांक मुख्य(पूर्णांक argc, अक्षर स्थिर *argv[])
अणु
	पूर्णांक fd, ret;
	अक्षर brightness_file_path[LED_MAX_NAME_SIZE + 11];
	काष्ठा pollfd pollfd;
	काष्ठा बारpec ts;
	अक्षर buf[11];

	अगर (argc != 2) अणु
		ख_लिखो(मानक_त्रुटि, "Requires <device-name> argument\n");
		वापस 1;
	पूर्ण

	snम_लिखो(brightness_file_path, LED_MAX_NAME_SIZE,
		 "/sys/class/leds/%s/brightness_hw_changed", argv[1]);

	fd = खोलो(brightness_file_path, O_RDONLY);
	अगर (fd == -1) अणु
		म_लिखो("Failed to open %s file\n", brightness_file_path);
		वापस 1;
	पूर्ण

	/*
	 * पढ़ो may fail अगर no hw brightness change has occurred so far,
	 * but it is required to aव्योम spurious poll notअगरications in
	 * the opposite हाल.
	 */
	पढ़ो(fd, buf, माप(buf));

	pollfd.fd = fd;
	pollfd.events = POLLPRI;

	जबतक (1) अणु
		ret = poll(&pollfd, 1, -1);
		अगर (ret == -1) अणु
			म_लिखो("Failed to poll %s file (%d)\n",
				brightness_file_path, ret);
			ret = 1;
			अवरोध;
		पूर्ण

		घड़ी_समय_लो(CLOCK_MONOTONIC, &ts);

		ret = पढ़ो(fd, buf, माप(buf));
		अगर (ret < 0)
			अवरोध;

		ret = lseek(pollfd.fd, 0, शुरू_से);
		अगर (ret < 0) अणु
			म_लिखो("lseek failed (%d)\n", ret);
			अवरोध;
		पूर्ण

		म_लिखो("[%ld.%09ld] %d\n", ts.tv_sec, ts.tv_nsec, म_से_प(buf));
	पूर्ण

	बंद(fd);

	वापस ret;
पूर्ण
