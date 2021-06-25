<शैली गुरु>
/* Time inconsistency check test
 *		by: john stultz (johnstul@us.ibm.com)
 *		(C) Copyright IBM 2003, 2004, 2005, 2012
 *		(C) Copyright Linaro Limited 2015
 *		Licensed under the GPLv2
 *
 *  To build:
 *	$ gcc inconsistency-check.c -o inconsistency-check -lrt
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
#समावेश <समय.स>
#समावेश <sys/समय.स>
#समावेश <sys/समयx.h>
#समावेश <माला.स>
#समावेश <संकेत.स>
#समावेश "../kselftest.h"

#घोषणा CALLS_PER_LOOP 64
#घोषणा NSEC_PER_SEC 1000000000ULL

#घोषणा CLOCK_REALTIME			0
#घोषणा CLOCK_MONOTONIC			1
#घोषणा CLOCK_PROCESS_CPUTIME_ID	2
#घोषणा CLOCK_THREAD_CPUTIME_ID		3
#घोषणा CLOCK_MONOTONIC_RAW		4
#घोषणा CLOCK_REALTIME_COARSE		5
#घोषणा CLOCK_MONOTONIC_COARSE		6
#घोषणा CLOCK_BOOTTIME			7
#घोषणा CLOCK_REALTIME_ALARM		8
#घोषणा CLOCK_BOOTTIME_ALARM		9
#घोषणा CLOCK_HWSPECIFIC		10
#घोषणा CLOCK_TAI			11
#घोषणा NR_CLOCKIDS			12

अक्षर *घड़ीstring(पूर्णांक घड़ीid)
अणु
	चयन (घड़ीid) अणु
	हाल CLOCK_REALTIME:
		वापस "CLOCK_REALTIME";
	हाल CLOCK_MONOTONIC:
		वापस "CLOCK_MONOTONIC";
	हाल CLOCK_PROCESS_CPUTIME_ID:
		वापस "CLOCK_PROCESS_CPUTIME_ID";
	हाल CLOCK_THREAD_CPUTIME_ID:
		वापस "CLOCK_THREAD_CPUTIME_ID";
	हाल CLOCK_MONOTONIC_RAW:
		वापस "CLOCK_MONOTONIC_RAW";
	हाल CLOCK_REALTIME_COARSE:
		वापस "CLOCK_REALTIME_COARSE";
	हाल CLOCK_MONOTONIC_COARSE:
		वापस "CLOCK_MONOTONIC_COARSE";
	हाल CLOCK_BOOTTIME:
		वापस "CLOCK_BOOTTIME";
	हाल CLOCK_REALTIME_ALARM:
		वापस "CLOCK_REALTIME_ALARM";
	हाल CLOCK_BOOTTIME_ALARM:
		वापस "CLOCK_BOOTTIME_ALARM";
	हाल CLOCK_TAI:
		वापस "CLOCK_TAI";
	पूर्ण;
	वापस "UNKNOWN_CLOCKID";
पूर्ण

/* वापसs 1 अगर a <= b, 0 otherwise */
अटल अंतरभूत पूर्णांक in_order(काष्ठा बारpec a, काष्ठा बारpec b)
अणु
	/* use अचिन्हित to aव्योम false positives on 2038 rollover */
	अगर ((अचिन्हित दीर्घ)a.tv_sec < (अचिन्हित दीर्घ)b.tv_sec)
		वापस 1;
	अगर ((अचिन्हित दीर्घ)a.tv_sec > (अचिन्हित दीर्घ)b.tv_sec)
		वापस 0;
	अगर (a.tv_nsec > b.tv_nsec)
		वापस 0;
	वापस 1;
पूर्ण



पूर्णांक consistency_test(पूर्णांक घड़ी_प्रकारype, अचिन्हित दीर्घ seconds)
अणु
	काष्ठा बारpec list[CALLS_PER_LOOP];
	पूर्णांक i, inconsistent;
	दीर्घ now, then;
	समय_प्रकार t;
	अक्षर *start_str;

	घड़ी_समय_लो(घड़ी_प्रकारype, &list[0]);
	now = then = list[0].tv_sec;

	/* बारtamp start of test */
	t = समय(0);
	start_str = स_समय(&t);

	जबतक (seconds == -1 || now - then < seconds) अणु
		inconsistent = -1;

		/* Fill list */
		क्रम (i = 0; i < CALLS_PER_LOOP; i++)
			घड़ी_समय_लो(घड़ी_प्रकारype, &list[i]);

		/* Check क्रम inconsistencies */
		क्रम (i = 0; i < CALLS_PER_LOOP - 1; i++)
			अगर (!in_order(list[i], list[i+1]))
				inconsistent = i;

		/* display inconsistency */
		अगर (inconsistent >= 0) अणु
			अचिन्हित दीर्घ दीर्घ delta;

			म_लिखो("\%s\n", start_str);
			क्रम (i = 0; i < CALLS_PER_LOOP; i++) अणु
				अगर (i == inconsistent)
					म_लिखो("--------------------\n");
				म_लिखो("%lu:%lu\n", list[i].tv_sec,
							list[i].tv_nsec);
				अगर (i == inconsistent + 1)
					म_लिखो("--------------------\n");
			पूर्ण
			delta = list[inconsistent].tv_sec * NSEC_PER_SEC;
			delta += list[inconsistent].tv_nsec;
			delta -= list[inconsistent+1].tv_sec * NSEC_PER_SEC;
			delta -= list[inconsistent+1].tv_nsec;
			म_लिखो("Delta: %llu ns\n", delta);
			ख_साफ(0);
			/* बारtamp inconsistency*/
			t = समय(0);
			म_लिखो("%s\n", स_समय(&t));
			म_लिखो("[FAILED]\n");
			वापस -1;
		पूर्ण
		now = list[0].tv_sec;
	पूर्ण
	म_लिखो("[OK]\n");
	वापस 0;
पूर्ण


पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	पूर्णांक घड़ीid, opt;
	पूर्णांक userघड़ी = CLOCK_REALTIME;
	पूर्णांक maxघड़ीs = NR_CLOCKIDS;
	पूर्णांक runसमय = 10;
	काष्ठा बारpec ts;

	/* Process arguments */
	जबतक ((opt = getopt(argc, argv, "t:c:")) != -1) अणु
		चयन (opt) अणु
		हाल 't':
			runसमय = म_से_प(optarg);
			अवरोध;
		हाल 'c':
			userघड़ी = म_से_प(optarg);
			maxघड़ीs = userघड़ी + 1;
			अवरोध;
		शेष:
			म_लिखो("Usage: %s [-t <secs>] [-c <clockid>]\n", argv[0]);
			म_लिखो("	-t: Number of seconds to run\n");
			म_लिखो("	-c: clockid to use (default, all clockids)\n");
			निकास(-1);
		पूर्ण
	पूर्ण

	रखो_बफ(मानक_निकास, शून्य);

	क्रम (घड़ीid = userघड़ी; घड़ीid < maxघड़ीs; घड़ीid++) अणु

		अगर (घड़ीid == CLOCK_HWSPECIFIC)
			जारी;

		अगर (!घड़ी_समय_लो(घड़ीid, &ts)) अणु
			म_लिखो("Consistent %-30s ", घड़ीstring(घड़ीid));
			अगर (consistency_test(घड़ीid, runसमय))
				वापस ksft_निकास_fail();
		पूर्ण
	पूर्ण
	वापस ksft_निकास_pass();
पूर्ण
