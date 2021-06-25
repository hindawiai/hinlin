<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Real Time Clock Driver Test
 *	by: Benjamin Gaignard (benjamin.gaignard@linaro.org)
 *
 * To build
 *	gcc rtctest_setdate.c -o rtctest_setdate
 */

#समावेश <मानकपन.स>
#समावेश <linux/rtc.h>
#समावेश <sys/ioctl.h>
#समावेश <sys/समय.स>
#समावेश <sys/types.h>
#समावेश <fcntl.h>
#समावेश <unistd.h>
#समावेश <मानककोष.स>
#समावेश <त्रुटिसं.स>

अटल स्थिर अक्षर शेष_समय[] = "00:00:00";

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक fd, retval;
	काष्ठा rtc_समय new, current;
	स्थिर अक्षर *rtc, *date;
	स्थिर अक्षर *समय = शेष_समय;

	चयन (argc) अणु
	हाल 4:
		समय = argv[3];
		/* FALLTHROUGH */
	हाल 3:
		date = argv[2];
		rtc = argv[1];
		अवरोध;
	शेष:
		ख_लिखो(मानक_त्रुटि, "usage: rtctest_setdate <rtcdev> <DD-MM-YYYY> [HH:MM:SS]\n");
		वापस 1;
	पूर्ण

	fd = खोलो(rtc, O_RDONLY);
	अगर (fd == -1) अणु
		लिखो_त्रुटि(rtc);
		निकास(त्रुटि_सं);
	पूर्ण

	माला_पूछो(date, "%d-%d-%d", &new.पंचांग_mday, &new.पंचांग_mon, &new.पंचांग_year);
	new.पंचांग_mon -= 1;
	new.पंचांग_year -= 1900;
	माला_पूछो(समय, "%d:%d:%d", &new.पंचांग_hour, &new.पंचांग_min, &new.पंचांग_sec);

	ख_लिखो(मानक_त्रुटि, "Test will set RTC date/time to %d-%d-%d, %02d:%02d:%02d.\n",
		new.पंचांग_mday, new.पंचांग_mon + 1, new.पंचांग_year + 1900,
		new.पंचांग_hour, new.पंचांग_min, new.पंचांग_sec);

	/* Write the new date in RTC */
	retval = ioctl(fd, RTC_SET_TIME, &new);
	अगर (retval == -1) अणु
		लिखो_त्रुटि("RTC_SET_TIME ioctl");
		बंद(fd);
		निकास(त्रुटि_सं);
	पूर्ण

	/* Read back */
	retval = ioctl(fd, RTC_RD_TIME, &current);
	अगर (retval == -1) अणु
		लिखो_त्रुटि("RTC_RD_TIME ioctl");
		निकास(त्रुटि_सं);
	पूर्ण

	ख_लिखो(मानक_त्रुटि, "\n\nCurrent RTC date/time is %d-%d-%d, %02d:%02d:%02d.\n",
		current.पंचांग_mday, current.पंचांग_mon + 1, current.पंचांग_year + 1900,
		current.पंचांग_hour, current.पंचांग_min, current.पंचांग_sec);

	बंद(fd);
	वापस 0;
पूर्ण
