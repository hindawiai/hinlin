<शैली गुरु>
/* Measure mqueue समयout latency
 *              by: john stultz (john.stultz@linaro.org)
 *		(C) Copyright Linaro 2013
 *
 *		Inspired with permission from example test by:
 *			Roमुख्य Francoise <roमुख्य@orebokech.com>
 *              Licensed under the GPLv2
 *
 *  To build:
 *	$ gcc mqueue-lat.c -o mqueue-lat -lrt
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
#समावेश <माला.स>
#समावेश <संकेत.स>
#समावेश <त्रुटिसं.स>
#समावेश <mqueue.h>
#समावेश "../kselftest.h"

#घोषणा NSEC_PER_SEC 1000000000ULL

#घोषणा TARGET_TIMEOUT		100000000	/* 100ms in nanoseconds */
#घोषणा UNRESONABLE_LATENCY	40000000	/* 40ms in nanosecs */


दीर्घ दीर्घ बारpec_sub(काष्ठा बारpec a, काष्ठा बारpec b)
अणु
	दीर्घ दीर्घ ret = NSEC_PER_SEC * b.tv_sec + b.tv_nsec;

	ret -= NSEC_PER_SEC * a.tv_sec + a.tv_nsec;
	वापस ret;
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

पूर्णांक mqueue_lat_test(व्योम)
अणु

	mqd_t q;
	काष्ठा mq_attr attr;
	काष्ठा बारpec start, end, now, target;
	पूर्णांक i, count, ret;

	q = mq_खोलो("/foo", O_CREAT | O_RDONLY, 0666, शून्य);
	अगर (q < 0) अणु
		लिखो_त्रुटि("mq_open");
		वापस -1;
	पूर्ण
	mq_getattr(q, &attr);


	count = 100;
	घड़ी_समय_लो(CLOCK_MONOTONIC, &start);

	क्रम (i = 0; i < count; i++) अणु
		अक्षर buf[attr.mq_msgsize];

		घड़ी_समय_लो(CLOCK_REALTIME, &now);
		target = now;
		target = बारpec_add(now, TARGET_TIMEOUT); /* 100ms */

		ret = mq_समयdreceive(q, buf, माप(buf), शून्य, &target);
		अगर (ret < 0 && त्रुटि_सं != ETIMEDOUT) अणु
			लिखो_त्रुटि("mq_timedreceive");
			वापस -1;
		पूर्ण
	पूर्ण
	घड़ी_समय_लो(CLOCK_MONOTONIC, &end);

	mq_बंद(q);

	अगर ((बारpec_sub(start, end)/count) > TARGET_TIMEOUT + UNRESONABLE_LATENCY)
		वापस -1;

	वापस 0;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक ret;

	म_लिखो("Mqueue latency :                          ");
	ख_साफ(मानक_निकास);

	ret = mqueue_lat_test();
	अगर (ret < 0) अणु
		म_लिखो("[FAILED]\n");
		वापस ksft_निकास_fail();
	पूर्ण
	म_लिखो("[OK]\n");
	वापस ksft_निकास_pass();
पूर्ण
