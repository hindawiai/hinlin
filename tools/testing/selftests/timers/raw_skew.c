<शैली गुरु>
/* CLOCK_MONOTONIC vs CLOCK_MONOTONIC_RAW skew test
 *		by: john stultz (johnstul@us.ibm.com)
 *		    John Stultz <john.stultz@linaro.org>
 *		(C) Copyright IBM 2012
 *		(C) Copyright Linaro Limited 2015
 *		Licensed under the GPLv2
 *
 *  To build:
 *	$ gcc raw_skew.c -o raw_skew -lrt
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

#घोषणा CLOCK_MONOTONIC_RAW		4
#घोषणा NSEC_PER_SEC 1000000000LL

#घोषणा shअगरt_right(x, s) (अणु		\
	__typeof__(x) __x = (x);	\
	__typeof__(s) __s = (s);	\
	__x < 0 ? -(-__x >> __s) : __x >> __s; \
पूर्ण)

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

पूर्णांक मुख्य(पूर्णांक argv, अक्षर **argc)
अणु
	काष्ठा बारpec mon, raw, start, end;
	दीर्घ दीर्घ delta1, delta2, पूर्णांकerval, eppm, ppm;
	काष्ठा समयx tx1, tx2;

	रखो_बफ(मानक_निकास, शून्य);

	अगर (घड़ी_समय_लो(CLOCK_MONOTONIC_RAW, &raw)) अणु
		म_लिखो("ERR: NO CLOCK_MONOTONIC_RAW\n");
		वापस -1;
	पूर्ण

	tx1.modes = 0;
	adjसमयx(&tx1);
	get_monotonic_and_raw(&mon, &raw);
	start = mon;
	delta1 = dअगरf_बारpec(mon, raw);

	अगर (tx1.offset)
		म_लिखो("WARNING: ADJ_OFFSET in progress, this will cause inaccurate results\n");

	म_लिखो("Estimating clock drift: ");
	ख_साफ(मानक_निकास);
	sleep(120);

	get_monotonic_and_raw(&mon, &raw);
	end = mon;
	tx2.modes = 0;
	adjसमयx(&tx2);
	delta2 = dअगरf_बारpec(mon, raw);

	पूर्णांकerval = dअगरf_बारpec(start, end);

	/* calculate measured ppm between MONOTONIC and MONOTONIC_RAW */
	eppm = ((delta2-delta1)*NSEC_PER_SEC)/पूर्णांकerval;
	eppm = -eppm;
	म_लिखो("%lld.%i(est)", eppm/1000, असल((पूर्णांक)(eppm%1000)));

	/* Avg the two actual freq samples adjसमयx gave us */
	ppm = (tx1.freq + tx2.freq) * 1000 / 2;
	ppm = (दीर्घ दीर्घ)tx1.freq * 1000;
	ppm = shअगरt_right(ppm, 16);
	म_लिखो(" %lld.%i(act)", ppm/1000, असल((पूर्णांक)(ppm%1000)));

	अगर (lद_असल(eppm - ppm) > 1000) अणु
		अगर (tx1.offset || tx2.offset ||
		    tx1.freq != tx2.freq || tx1.tick != tx2.tick) अणु
			म_लिखो("	[SKIP]\n");
			वापस ksft_निकास_skip("The clock was adjusted externally. Shutdown NTPd or other time sync daemons\n");
		पूर्ण
		म_लिखो("	[FAILED]\n");
		वापस ksft_निकास_fail();
	पूर्ण
	म_लिखो("	[OK]\n");
	वापस  ksft_निकास_pass();
पूर्ण
