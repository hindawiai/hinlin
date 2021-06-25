<शैली गुरु>
/* adjसमयx() tick adjusपंचांगent test
 *		by:   John Stultz <john.stultz@linaro.org>
 *		(C) Copyright Linaro Limited 2015
 *		Licensed under the GPLv2
 *
 *  To build:
 *	$ gcc adjtick.c -o adjtick -lrt
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
#समावेश <unistd.h>
#समावेश <मानककोष.स>
#समावेश <sys/समय.स>
#समावेश <sys/समयx.h>
#समावेश <समय.स>

#समावेश "../kselftest.h"

#घोषणा CLOCK_MONOTONIC_RAW	4

#घोषणा NSEC_PER_SEC		1000000000LL
#घोषणा USEC_PER_SEC		1000000

#घोषणा MILLION			1000000

दीर्घ systick;

दीर्घ दीर्घ lद_असल(दीर्घ दीर्घ val)
अणु
	अगर (val < 0)
		val = -val;
	वापस val;
पूर्ण

अचिन्हित दीर्घ दीर्घ ts_to_nsec(काष्ठा बारpec ts)
अणु
	वापस ts.tv_sec * NSEC_PER_SEC + ts.tv_nsec;
पूर्ण

काष्ठा बारpec nsec_to_ts(दीर्घ दीर्घ ns)
अणु
	काष्ठा बारpec ts;

	ts.tv_sec = ns/NSEC_PER_SEC;
	ts.tv_nsec = ns%NSEC_PER_SEC;

	वापस ts;
पूर्ण

दीर्घ दीर्घ dअगरf_बारpec(काष्ठा बारpec start, काष्ठा बारpec end)
अणु
	दीर्घ दीर्घ start_ns, end_ns;

	start_ns = ts_to_nsec(start);
	end_ns = ts_to_nsec(end);

	वापस end_ns - start_ns;
पूर्ण

व्योम get_monotonic_and_raw(काष्ठा बारpec *mon, काष्ठा बारpec *raw)
अणु
	काष्ठा बारpec start, mid, end;
	दीर्घ दीर्घ dअगरf = 0, पंचांगp;
	पूर्णांक i;

	घड़ी_समय_लो(CLOCK_MONOTONIC, mon);
	घड़ी_समय_लो(CLOCK_MONOTONIC_RAW, raw);

	/* Try to get a more tightly bound pairing */
	क्रम (i = 0; i < 3; i++) अणु
		दीर्घ दीर्घ newdअगरf;

		घड़ी_समय_लो(CLOCK_MONOTONIC, &start);
		घड़ी_समय_लो(CLOCK_MONOTONIC_RAW, &mid);
		घड़ी_समय_लो(CLOCK_MONOTONIC, &end);

		newdअगरf = dअगरf_बारpec(start, end);
		अगर (dअगरf == 0 || newdअगरf < dअगरf) अणु
			dअगरf = newdअगरf;
			*raw = mid;
			पंचांगp = (ts_to_nsec(start) + ts_to_nsec(end))/2;
			*mon = nsec_to_ts(पंचांगp);
		पूर्ण
	पूर्ण
पूर्ण

दीर्घ दीर्घ get_ppm_drअगरt(व्योम)
अणु
	काष्ठा बारpec mon_start, raw_start, mon_end, raw_end;
	दीर्घ दीर्घ delta1, delta2, eppm;

	get_monotonic_and_raw(&mon_start, &raw_start);

	sleep(15);

	get_monotonic_and_raw(&mon_end, &raw_end);

	delta1 = dअगरf_बारpec(mon_start, mon_end);
	delta2 = dअगरf_बारpec(raw_start, raw_end);

	eppm = (delta1*MILLION)/delta2 - MILLION;

	वापस eppm;
पूर्ण

पूर्णांक check_tick_adj(दीर्घ tickval)
अणु
	दीर्घ दीर्घ eppm, ppm;
	काष्ठा समयx tx1;

	tx1.modes	 = ADJ_TICK;
	tx1.modes	|= ADJ_OFFSET;
	tx1.modes	|= ADJ_FREQUENCY;
	tx1.modes	|= ADJ_STATUS;

	tx1.status	= STA_PLL;
	tx1.offset	= 0;
	tx1.freq	= 0;
	tx1.tick	= tickval;

	adjसमयx(&tx1);

	sleep(1);

	ppm = ((दीर्घ दीर्घ)tickval * MILLION)/systick - MILLION;
	म_लिखो("Estimating tick (act: %ld usec, %lld ppm): ", tickval, ppm);

	eppm = get_ppm_drअगरt();
	म_लिखो("%lld usec, %lld ppm", systick + (systick * eppm / MILLION), eppm);
	ख_साफ(मानक_निकास);

	tx1.modes = 0;
	adjसमयx(&tx1);

	अगर (tx1.offset || tx1.freq || tx1.tick != tickval) अणु
		म_लिखो("	[ERROR]\n");
		म_लिखो("\tUnexpected adjtimex return values, make sure ntpd is not running.\n");
		वापस -1;
	पूर्ण

	/*
	 * Here we use 100ppm dअगरference as an error bound.
	 * We likely should see better, but some coarse घड़ीsources
	 * cannot match the HZ tick size accurately, so we have a
	 * पूर्णांकernal correction factor that करोesn't scale exactly
	 * with the adjusपंचांगent, resulting in > 10ppm error during
	 * a 10% adjusपंचांगent. 100ppm also gives us more breathing
	 * room क्रम पूर्णांकerruptions during the measurement.
	 */
	अगर (lद_असल(eppm - ppm) > 100) अणु
		म_लिखो("	[FAILED]\n");
		वापस -1;
	पूर्ण
	म_लिखो("	[OK]\n");

	वापस  0;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argv, अक्षर **argc)
अणु
	काष्ठा बारpec raw;
	दीर्घ tick, max, पूर्णांकerval, err;
	काष्ठा समयx tx1;

	err = 0;
	रखो_बफ(मानक_निकास, शून्य);

	अगर (घड़ी_समय_लो(CLOCK_MONOTONIC_RAW, &raw)) अणु
		म_लिखो("ERR: NO CLOCK_MONOTONIC_RAW\n");
		वापस -1;
	पूर्ण

	म_लिखो("Each iteration takes about 15 seconds\n");

	systick = sysconf(_SC_घड़ी_टिक);
	systick = USEC_PER_SEC/sysconf(_SC_घड़ी_टिक);
	max = systick/10; /* +/- 10% */
	पूर्णांकerval = max/4; /* in 4 steps each side */

	क्रम (tick = (systick - max); tick < (systick + max); tick += पूर्णांकerval) अणु
		अगर (check_tick_adj(tick)) अणु
			err = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	/* Reset things to zero */
	tx1.modes	 = ADJ_TICK;
	tx1.modes	|= ADJ_OFFSET;
	tx1.modes	|= ADJ_FREQUENCY;

	tx1.offset	 = 0;
	tx1.freq	 = 0;
	tx1.tick	 = systick;

	adjसमयx(&tx1);

	अगर (err)
		वापस ksft_निकास_fail();

	वापस ksft_निकास_pass();
पूर्ण
