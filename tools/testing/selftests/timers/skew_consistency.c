<शैली गुरु>
/* ADJ_FREQ Skew consistency test
 *		by: john stultz (johnstul@us.ibm.com)
 *		(C) Copyright IBM 2012
 *		Licensed under the GPLv2
 *
 *  NOTE: This is a meta-test which cranks the ADJ_FREQ knob back
 *  and क्रमth and watches क्रम consistency problems. Thus this test requires
 *  that the inconsistency-check tests be present in the same directory it
 *  is run from.
 *
 *  To build:
 *	$ gcc skew_consistency.c -o skew_consistency -lrt
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
#समावेश <unistd.h>
#समावेश <sys/समय.स>
#समावेश <sys/समयx.h>
#समावेश <समय.स>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>
#समावेश <माला.स>
#समावेश <sys/रुको.h>
#समावेश "../kselftest.h"

#घोषणा NSEC_PER_SEC 1000000000LL

पूर्णांक मुख्य(पूर्णांक argv, अक्षर **argc)
अणु
	काष्ठा समयx tx;
	पूर्णांक ret, ppm;
	pid_t pid;


	म_लिखो("Running Asynchronous Frequency Changing Tests...\n");

	pid = विभाजन();
	अगर (!pid)
		वापस प्रणाली("./inconsistency-check -c 1 -t 600");

	ppm = 500;
	ret = 0;

	जबतक (pid != रुकोpid(pid, &ret, WNOHANG)) अणु
		ppm = -ppm;
		tx.modes = ADJ_FREQUENCY;
		tx.freq = ppm << 16;
		adjसमयx(&tx);
		usleep(500000);
	पूर्ण

	/* Set things back */
	tx.modes = ADJ_FREQUENCY;
	tx.offset = 0;
	adjसमयx(&tx);


	अगर (ret) अणु
		म_लिखो("[FAILED]\n");
		वापस ksft_निकास_fail();
	पूर्ण
	म_लिखो("[OK]\n");
	वापस ksft_निकास_pass();
पूर्ण
