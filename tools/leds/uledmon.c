<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * uledmon.c
 *
 * This program creates a new userspace LED class device and monitors it. A
 * बारtamp and brightness value is prपूर्णांकed each समय the brightness changes.
 *
 * Usage: uledmon <device-name>
 *
 * <device-name> is the name of the LED class device to be created. Pressing
 * CTRL+C will निकास.
 */

#समावेश <fcntl.h>
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <समय.स>
#समावेश <unistd.h>

#समावेश <linux/uleds.h>

पूर्णांक मुख्य(पूर्णांक argc, अक्षर स्थिर *argv[])
अणु
	काष्ठा uleds_user_dev uleds_dev;
	पूर्णांक fd, ret;
	पूर्णांक brightness;
	काष्ठा बारpec ts;

	अगर (argc != 2) अणु
		ख_लिखो(मानक_त्रुटि, "Requires <device-name> argument\n");
		वापस 1;
	पूर्ण

	म_नकलन(uleds_dev.name, argv[1], LED_MAX_NAME_SIZE);
	uleds_dev.max_brightness = 100;

	fd = खोलो("/dev/uleds", O_RDWR);
	अगर (fd == -1) अणु
		लिखो_त्रुटि("Failed to open /dev/uleds");
		वापस 1;
	पूर्ण

	ret = ग_लिखो(fd, &uleds_dev, माप(uleds_dev));
	अगर (ret == -1) अणु
		लिखो_त्रुटि("Failed to write to /dev/uleds");
		बंद(fd);
		वापस 1;
	पूर्ण

	जबतक (1) अणु
		ret = पढ़ो(fd, &brightness, माप(brightness));
		अगर (ret == -1) अणु
			लिखो_त्रुटि("Failed to read from /dev/uleds");
			बंद(fd);
			वापस 1;
		पूर्ण
		घड़ी_समय_लो(CLOCK_MONOTONIC, &ts);
		म_लिखो("[%ld.%09ld] %u\n", ts.tv_sec, ts.tv_nsec, brightness);
	पूर्ण

	बंद(fd);

	वापस 0;
पूर्ण
