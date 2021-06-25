<शैली गुरु>
/* ADJ_FREQ Skew change test
 *		by: john stultz (johnstul@us.ibm.com)
 *		(C) Copyright IBM 2012
 *		Licensed under the GPLv2
 *
 *  NOTE: This is a meta-test which cranks the ADJ_FREQ knob and
 *  then uses other tests to detect problems. Thus this test requires
 *  that the raw_skew, inconsistency-check and nanosleep tests be
 *  present in the same directory it is run from.
 *
 *  To build:
 *	$ gcc change_skew.c -o change_skew -lrt
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
#समावेश <sys/समय.स>
#समावेश <sys/समयx.h>
#समावेश <समय.स>
#समावेश "../kselftest.h"

#घोषणा NSEC_PER_SEC 1000000000LL


पूर्णांक change_skew_test(पूर्णांक ppm)
अणु
	काष्ठा समयx tx;
	पूर्णांक ret;

	tx.modes = ADJ_FREQUENCY;
	tx.freq = ppm << 16;

	ret = adjसमयx(&tx);
	अगर (ret < 0) अणु
		म_लिखो("Error adjusting freq\n");
		वापस ret;
	पूर्ण

	ret = प्रणाली("./raw_skew");
	ret |= प्रणाली("./inconsistency-check");
	ret |= प्रणाली("./nanosleep");

	वापस ret;
पूर्ण


पूर्णांक मुख्य(पूर्णांक argv, अक्षर **argc)
अणु
	काष्ठा समयx tx;
	पूर्णांक i, ret;

	पूर्णांक ppm[5] = अणु0, 250, 500, -250, -500पूर्ण;

	/* Kill ntpd */
	ret = प्रणाली("killall -9 ntpd");

	/* Make sure there's no offset adjusपंचांगent going on */
	tx.modes = ADJ_OFFSET;
	tx.offset = 0;
	ret = adjसमयx(&tx);

	अगर (ret < 0) अणु
		म_लिखो("Maybe you're not running as root?\n");
		वापस -1;
	पूर्ण

	क्रम (i = 0; i < 5; i++) अणु
		म_लिखो("Using %i ppm adjustment\n", ppm[i]);
		ret = change_skew_test(ppm[i]);
		अगर (ret)
			अवरोध;
	पूर्ण

	/* Set things back */
	tx.modes = ADJ_FREQUENCY;
	tx.offset = 0;
	adjसमयx(&tx);

	अगर (ret) अणु
		म_लिखो("[FAIL]");
		वापस ksft_निकास_fail();
	पूर्ण
	म_लिखो("[OK]");
	वापस ksft_निकास_pass();
पूर्ण
