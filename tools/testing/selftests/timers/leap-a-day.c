<शैली गुरु>
/* Leap second stress test
 *              by: John Stultz (john.stultz@linaro.org)
 *              (C) Copyright IBM 2012
 *              (C) Copyright 2013, 2015 Linaro Limited
 *              Licensed under the GPLv2
 *
 *  This test संकेतs the kernel to insert a leap second
 *  every day at midnight GMT. This allows क्रम stressing the
 *  kernel's leap-second behavior, as well as how well applications
 *  handle the leap-second discontinuity.
 *
 *  Usage: leap-a-day [-s] [-i <num>]
 *
 *  Options:
 *	-s:	Each iteration, set the date to 10 seconds beक्रमe midnight GMT.
 *		This speeds up the number of leapsecond transitions tested,
 *		but because it calls समय_रखोofday frequently, advancing the
 *		समय by 24 hours every ~16 seconds, it may cause application
 *		disruption.
 *
 *	-i:	Number of iterations to run (शेष: infinite)
 *
 *  Other notes: Disabling NTP prior to running this is advised, as the two
 *		 may conflict in their commands to the kernel.
 *
 *  To build:
 *	$ gcc leap-a-day.c -o leap-a-day -lrt
 *
 *   This program is मुक्त software: you can redistribute it and/or modअगरy
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License क्रम more details.
 */



#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <समय.स>
#समावेश <sys/समय.स>
#समावेश <sys/समयx.h>
#समावेश <sys/त्रुटिसं.स>
#समावेश <माला.स>
#समावेश <संकेत.स>
#समावेश <unistd.h>
#समावेश "../kselftest.h"

#घोषणा NSEC_PER_SEC 1000000000ULL
#घोषणा CLOCK_TAI 11

समय_प्रकार next_leap;
पूर्णांक error_found;

/* वापसs 1 अगर a <= b, 0 otherwise */
अटल अंतरभूत पूर्णांक in_order(काष्ठा बारpec a, काष्ठा बारpec b)
अणु
	अगर (a.tv_sec < b.tv_sec)
		वापस 1;
	अगर (a.tv_sec > b.tv_sec)
		वापस 0;
	अगर (a.tv_nsec > b.tv_nsec)
		वापस 0;
	वापस 1;
पूर्ण

काष्ठा बारpec बारpec_add(काष्ठा बारpec ts, अचिन्हित दीर्घ दीर्घ ns)
अणु
	ts.tv_nsec += ns;
	जबतक (ts.tv_nsec >= NSEC_PER_SEC) अणु
		ts.tv_nsec -= NSEC_PER_SEC;
		ts.tv_sec++;
	पूर्ण
	वापस ts;
पूर्ण

अक्षर *समय_state_str(पूर्णांक state)
अणु
	चयन (state) अणु
	हाल TIME_OK:	वापस "TIME_OK";
	हाल TIME_INS:	वापस "TIME_INS";
	हाल TIME_DEL:	वापस "TIME_DEL";
	हाल TIME_OOP:	वापस "TIME_OOP";
	हाल TIME_WAIT:	वापस "TIME_WAIT";
	हाल TIME_BAD:	वापस "TIME_BAD";
	पूर्ण
	वापस "ERROR";
पूर्ण

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

	/* Clear maxerror, as it can cause UNSYNC to be set */
	tx.modes = ADJ_MAXERROR;
	tx.maxerror = 0;
	ret = adjसमयx(&tx);

	/* Clear the status */
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

व्योम sigalarm(पूर्णांक signo)
अणु
	काष्ठा समयx tx;
	पूर्णांक ret;

	tx.modes = 0;
	ret = adjसमयx(&tx);

	अगर (tx.समय.tv_sec < next_leap) अणु
		म_लिखो("Error: Early timer expiration! (Should be %ld)\n", next_leap);
		error_found = 1;
		म_लिखो("adjtimex: %10ld sec + %6ld us (%i)\t%s\n",
					tx.समय.tv_sec,
					tx.समय.tv_usec,
					tx.tai,
					समय_state_str(ret));
	पूर्ण
	अगर (ret != TIME_WAIT) अणु
		म_लिखो("Error: Timer seeing incorrect NTP state? (Should be TIME_WAIT)\n");
		error_found = 1;
		म_लिखो("adjtimex: %10ld sec + %6ld us (%i)\t%s\n",
					tx.समय.tv_sec,
					tx.समय.tv_usec,
					tx.tai,
					समय_state_str(ret));
	पूर्ण
पूर्ण


/* Test क्रम known hrसमयr failure */
व्योम test_hrसमयr_failure(व्योम)
अणु
	काष्ठा बारpec now, target;

	घड़ी_समय_लो(CLOCK_REALTIME, &now);
	target = बारpec_add(now, NSEC_PER_SEC/2);
	घड़ी_nanosleep(CLOCK_REALTIME, TIMER_ABSTIME, &target, शून्य);
	घड़ी_समय_लो(CLOCK_REALTIME, &now);

	अगर (!in_order(target, now)) अणु
		म_लिखो("ERROR: hrtimer early expiration failure observed.\n");
		error_found = 1;
	पूर्ण
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	समयr_t पंचांग1;
	काष्ठा iसमयrspec its1;
	काष्ठा sigevent se;
	काष्ठा sigaction act;
	पूर्णांक signum = SIGRTMAX;
	पूर्णांक समय_रखो = 1;
	पूर्णांक tai_समय = 0;
	पूर्णांक insert = 1;
	पूर्णांक iterations = 10;
	पूर्णांक opt;

	/* Process arguments */
	जबतक ((opt = getopt(argc, argv, "sti:")) != -1) अणु
		चयन (opt) अणु
		हाल 'w':
			म_लिखो("Only setting leap-flag, not changing time. It could take up to a day for leap to trigger.\n");
			समय_रखो = 0;
			अवरोध;
		हाल 'i':
			iterations = म_से_प(optarg);
			अवरोध;
		हाल 't':
			tai_समय = 1;
			अवरोध;
		शेष:
			म_लिखो("Usage: %s [-w] [-i <iterations>]\n", argv[0]);
			म_लिखो("	-w: Set flag and wait for leap second each iteration");
			म_लिखो("	    (default sets time to right before leapsecond)\n");
			म_लिखो("	-i: Number of iterations (-1 = infinite, default is 10)\n");
			म_लिखो("	-t: Print TAI time\n");
			निकास(-1);
		पूर्ण
	पूर्ण

	/* Make sure TAI support is present अगर -t was used */
	अगर (tai_समय) अणु
		काष्ठा बारpec ts;

		अगर (घड़ी_समय_लो(CLOCK_TAI, &ts)) अणु
			म_लिखो("System doesn't support CLOCK_TAI\n");
			ksft_निकास_fail();
		पूर्ण
	पूर्ण

	संकेत(संक_विघ्न, handler);
	संकेत(SIGKILL, handler);

	/* Set up समयr संकेत handler: */
	sigfillset(&act.sa_mask);
	act.sa_flags = 0;
	act.sa_handler = sigalarm;
	sigaction(signum, &act, शून्य);

	अगर (iterations < 0)
		म_लिखो("This runs continuously. Press ctrl-c to stop\n");
	अन्यथा
		म_लिखो("Running for %i iterations. Press ctrl-c to stop\n", iterations);

	म_लिखो("\n");
	जबतक (1) अणु
		पूर्णांक ret;
		काष्ठा बारpec ts;
		काष्ठा समयx tx;
		समय_प्रकार now;

		/* Get the current समय */
		घड़ी_समय_लो(CLOCK_REALTIME, &ts);

		/* Calculate the next possible leap second 23:59:60 GMT */
		next_leap = ts.tv_sec;
		next_leap += 86400 - (next_leap % 86400);

		अगर (समय_रखो) अणु
			काष्ठा समयval tv;

			tv.tv_sec = next_leap - 10;
			tv.tv_usec = 0;
			समय_रखोofday(&tv, शून्य);
			म_लिखो("Setting time to %s", स_समय(&tv.tv_sec));
		पूर्ण

		/* Reset NTP समय state */
		clear_समय_state();

		/* Set the leap second insert flag */
		tx.modes = ADJ_STATUS;
		अगर (insert)
			tx.status = STA_INS;
		अन्यथा
			tx.status = STA_DEL;
		ret = adjसमयx(&tx);
		अगर (ret < 0) अणु
			म_लिखो("Error: Problem setting STA_INS/STA_DEL!: %s\n",
							समय_state_str(ret));
			वापस ksft_निकास_fail();
		पूर्ण

		/* Validate STA_INS was set */
		tx.modes = 0;
		ret = adjसमयx(&tx);
		अगर (tx.status != STA_INS && tx.status != STA_DEL) अणु
			म_लिखो("Error: STA_INS/STA_DEL not set!: %s\n",
							समय_state_str(ret));
			वापस ksft_निकास_fail();
		पूर्ण

		अगर (tai_समय) अणु
			म_लिखो("Using TAI time,"
				" no inconsistencies should be seen!\n");
		पूर्ण

		म_लिखो("Scheduling leap second for %s", स_समय(&next_leap));

		/* Set up समयr */
		म_लिखो("Setting timer for %ld -  %s", next_leap, स_समय(&next_leap));
		स_रखो(&se, 0, माप(se));
		se.sigev_notअगरy = SIGEV_SIGNAL;
		se.sigev_signo = signum;
		se.sigev_value.sival_पूर्णांक = 0;
		अगर (समयr_create(CLOCK_REALTIME, &se, &पंचांग1) == -1) अणु
			म_लिखो("Error: timer_create failed\n");
			वापस ksft_निकास_fail();
		पूर्ण
		its1.it_value.tv_sec = next_leap;
		its1.it_value.tv_nsec = 0;
		its1.it_पूर्णांकerval.tv_sec = 0;
		its1.it_पूर्णांकerval.tv_nsec = 0;
		समयr_समय_रखो(पंचांग1, TIMER_ABSTIME, &its1, शून्य);

		/* Wake up 3 seconds beक्रमe leap */
		ts.tv_sec = next_leap - 3;
		ts.tv_nsec = 0;


		जबतक (घड़ी_nanosleep(CLOCK_REALTIME, TIMER_ABSTIME, &ts, शून्य))
			म_लिखो("Something woke us up, returning to sleep\n");

		/* Validate STA_INS is still set */
		tx.modes = 0;
		ret = adjसमयx(&tx);
		अगर (tx.status != STA_INS && tx.status != STA_DEL) अणु
			म_लिखो("Something cleared STA_INS/STA_DEL, setting it again.\n");
			tx.modes = ADJ_STATUS;
			अगर (insert)
				tx.status = STA_INS;
			अन्यथा
				tx.status = STA_DEL;
			ret = adjसमयx(&tx);
		पूर्ण

		/* Check adjसमयx output every half second */
		now = tx.समय.tv_sec;
		जबतक (now < next_leap + 2) अणु
			अक्षर buf[26];
			काष्ठा बारpec tai;
			पूर्णांक ret;

			tx.modes = 0;
			ret = adjसमयx(&tx);

			अगर (tai_समय) अणु
				घड़ी_समय_लो(CLOCK_TAI, &tai);
				म_लिखो("%ld sec, %9ld ns\t%s\n",
						tai.tv_sec,
						tai.tv_nsec,
						समय_state_str(ret));
			पूर्ण अन्यथा अणु
				स_समय_r(&tx.समय.tv_sec, buf);
				buf[म_माप(buf)-1] = 0; /*हटाओ trailing\न */

				म_लिखो("%s + %6ld us (%i)\t%s\n",
						buf,
						tx.समय.tv_usec,
						tx.tai,
						समय_state_str(ret));
			पूर्ण
			now = tx.समय.tv_sec;
			/* Sleep क्रम another half second */
			ts.tv_sec = 0;
			ts.tv_nsec = NSEC_PER_SEC / 2;
			घड़ी_nanosleep(CLOCK_MONOTONIC, 0, &ts, शून्य);
		पूर्ण
		/* Switch to using other mode */
		insert = !insert;

		/* Note अगर kernel has known hrसमयr failure */
		test_hrसमयr_failure();

		म_लिखो("Leap complete\n");
		अगर (error_found) अणु
			म_लिखो("Errors observed\n");
			clear_समय_state();
			वापस ksft_निकास_fail();
		पूर्ण
		म_लिखो("\n");
		अगर ((iterations != -1) && !(--iterations))
			अवरोध;
	पूर्ण

	clear_समय_state();
	वापस ksft_निकास_pass();
पूर्ण
