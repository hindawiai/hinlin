<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Real Time Clock Periodic Interrupt test program
 *
 * Since commit 6610e0893b8bc ("RTC: Rework RTC code to use समयrqueue क्रम
 * events"), PIE are completely handled using hrसमयrs, without actually using
 * any underlying hardware RTC.
 *
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

/*
 * This expects the new RTC class driver framework, working with
 * घड़ीs that will often not be clones of what the PC-AT had.
 * Use the command line to specअगरy another RTC अगर you need one.
 */
अटल स्थिर अक्षर शेष_rtc[] = "/dev/rtc0";

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक i, fd, retval, irqcount = 0;
	अचिन्हित दीर्घ पंचांगp, data, old_pie_rate;
	स्थिर अक्षर *rtc = शेष_rtc;
	काष्ठा समयval start, end, dअगरf;

	चयन (argc) अणु
	हाल 2:
		rtc = argv[1];
		/* FALLTHROUGH */
	हाल 1:
		अवरोध;
	शेष:
		ख_लिखो(मानक_त्रुटि, "usage:  rtctest [rtcdev] [d]\n");
		वापस 1;
	पूर्ण

	fd = खोलो(rtc, O_RDONLY);

	अगर (fd ==  -1) अणु
		लिखो_त्रुटि(rtc);
		निकास(त्रुटि_सं);
	पूर्ण

	/* Read periodic IRQ rate */
	retval = ioctl(fd, RTC_IRQP_READ, &old_pie_rate);
	अगर (retval == -1) अणु
		/* not all RTCs support periodic IRQs */
		अगर (त्रुटि_सं == EINVAL) अणु
			ख_लिखो(मानक_त्रुटि, "\nNo periodic IRQ support\n");
			जाओ करोne;
		पूर्ण
		लिखो_त्रुटि("RTC_IRQP_READ ioctl");
		निकास(त्रुटि_सं);
	पूर्ण
	ख_लिखो(मानक_त्रुटि, "\nPeriodic IRQ rate is %ldHz.\n", old_pie_rate);

	ख_लिखो(मानक_त्रुटि, "Counting 20 interrupts at:");
	ख_साफ(मानक_त्रुटि);

	/* The frequencies 128Hz, 256Hz, ... 8192Hz are only allowed क्रम root. */
	क्रम (पंचांगp=2; पंचांगp<=64; पंचांगp*=2) अणु

		retval = ioctl(fd, RTC_IRQP_SET, पंचांगp);
		अगर (retval == -1) अणु
			/* not all RTCs can change their periodic IRQ rate */
			अगर (त्रुटि_सं == EINVAL) अणु
				ख_लिखो(मानक_त्रुटि,
					"\n...Periodic IRQ rate is fixed\n");
				जाओ करोne;
			पूर्ण
			लिखो_त्रुटि("RTC_IRQP_SET ioctl");
			निकास(त्रुटि_सं);
		पूर्ण

		ख_लिखो(मानक_त्रुटि, "\n%ldHz:\t", पंचांगp);
		ख_साफ(मानक_त्रुटि);

		/* Enable periodic पूर्णांकerrupts */
		retval = ioctl(fd, RTC_PIE_ON, 0);
		अगर (retval == -1) अणु
			लिखो_त्रुटि("RTC_PIE_ON ioctl");
			निकास(त्रुटि_सं);
		पूर्ण

		क्रम (i=1; i<21; i++) अणु
			समय_लोofday(&start, शून्य);
			/* This blocks */
			retval = पढ़ो(fd, &data, माप(अचिन्हित दीर्घ));
			अगर (retval == -1) अणु
				लिखो_त्रुटि("read");
				निकास(त्रुटि_सं);
			पूर्ण
			समय_लोofday(&end, शून्य);
			समयrsub(&end, &start, &dअगरf);
			अगर (dअगरf.tv_sec > 0 ||
			    dअगरf.tv_usec > ((1000000L / पंचांगp) * 1.10)) अणु
				ख_लिखो(मानक_त्रुटि, "\nPIE delta error: %ld.%06ld should be close to 0.%06ld\n",
				       dअगरf.tv_sec, dअगरf.tv_usec,
				       (1000000L / पंचांगp));
				ख_साफ(मानक_निकास);
				निकास(-1);
			पूर्ण

			ख_लिखो(मानक_त्रुटि, " %d",i);
			ख_साफ(मानक_त्रुटि);
			irqcount++;
		पूर्ण

		/* Disable periodic पूर्णांकerrupts */
		retval = ioctl(fd, RTC_PIE_OFF, 0);
		अगर (retval == -1) अणु
			लिखो_त्रुटि("RTC_PIE_OFF ioctl");
			निकास(त्रुटि_सं);
		पूर्ण
	पूर्ण

करोne:
	ioctl(fd, RTC_IRQP_SET, old_pie_rate);

	ख_लिखो(मानक_त्रुटि, "\n\n\t\t\t *** Test complete ***\n");

	बंद(fd);

	वापस 0;
पूर्ण
