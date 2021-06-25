<शैली गुरु>
/* Demo leapsecond deadlock
 *              by: John Stultz (john.stultz@linaro.org)
 *              (C) Copyright IBM 2012
 *              (C) Copyright 2013, 2015 Linaro Limited
 *              Licensed under the GPL
 *
 * This test demonstrates leapsecond deadlock that is possible
 * on kernels from 2.6.26 to 3.3.
 *
 * WARNING: THIS WILL LIKELY HARD HANG SYSTEMS AND MAY LOSE DATA
 * RUN AT YOUR OWN RISK!
 *  To build:
 *	$ gcc leapcrash.c -o leapcrash -lrt
 */



#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <समय.स>
#समावेश <sys/समय.स>
#समावेश <sys/समयx.h>
#समावेश <माला.स>
#समावेश <संकेत.स>
#समावेश "../kselftest.h"

/* clear NTP समय_status & समय_state */
पूर्णांक clear_समय_state(व्योम)
अणु
	काष्ठा समयx tx;
	पूर्णांक ret;

	/*
	 * We have to call adjसमय twice here, as kernels
	 * prior to 6b1859dba01c7 (included in 3.5 and
	 * -stable), had an issue with the state machine
	 * and wouldn't clear the STA_INS/DEL flag directly.
	 */
	tx.modes = ADJ_STATUS;
	tx.status = STA_PLL;
	ret = adjसमयx(&tx);

	tx.modes = ADJ_STATUS;
	tx.status = 0;
	ret = adjसमयx(&tx);

	वापस ret;
पूर्ण

/* Make sure we cleanup on ctrl-c */
व्योम handler(पूर्णांक unused)
अणु
	clear_समय_state();
	निकास(0);
पूर्ण


पूर्णांक मुख्य(व्योम)
अणु
	काष्ठा समयx tx;
	काष्ठा बारpec ts;
	समय_प्रकार next_leap;
	पूर्णांक count = 0;

	रखो_बफ(मानक_निकास, शून्य);

	संकेत(संक_विघ्न, handler);
	संकेत(SIGKILL, handler);
	म_लिखो("This runs for a few minutes. Press ctrl-c to stop\n");

	clear_समय_state();


	/* Get the current समय */
	घड़ी_समय_लो(CLOCK_REALTIME, &ts);

	/* Calculate the next possible leap second 23:59:60 GMT */
	next_leap = ts.tv_sec;
	next_leap += 86400 - (next_leap % 86400);

	क्रम (count = 0; count < 20; count++) अणु
		काष्ठा समयval tv;


		/* set the समय to 2 seconds beक्रमe the leap */
		tv.tv_sec = next_leap - 2;
		tv.tv_usec = 0;
		अगर (समय_रखोofday(&tv, शून्य)) अणु
			म_लिखो("Error: You're likely not running with proper (ie: root) permissions\n");
			वापस ksft_निकास_fail();
		पूर्ण
		tx.modes = 0;
		adjसमयx(&tx);

		/* hammer on adjसमय w/ STA_INS */
		जबतक (tx.समय.tv_sec < next_leap + 1) अणु
			/* Set the leap second insert flag */
			tx.modes = ADJ_STATUS;
			tx.status = STA_INS;
			adjसमयx(&tx);
		पूर्ण
		clear_समय_state();
		म_लिखो(".");
		ख_साफ(मानक_निकास);
	पूर्ण
	म_लिखो("[OK]\n");
	वापस ksft_निकास_pass();
पूर्ण
