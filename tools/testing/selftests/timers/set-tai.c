<शैली गुरु>
/* Set tai offset
 *              by: John Stultz <john.stultz@linaro.org>
 *              (C) Copyright Linaro 2013
 *              Licensed under the GPLv2
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
#समावेश <unistd.h>
#समावेश "../kselftest.h"

पूर्णांक set_tai(पूर्णांक offset)
अणु
	काष्ठा समयx tx;

	स_रखो(&tx, 0, माप(tx));

	tx.modes = ADJ_TAI;
	tx.स्थिरant = offset;

	वापस adjसमयx(&tx);
पूर्ण

पूर्णांक get_tai(व्योम)
अणु
	काष्ठा समयx tx;

	स_रखो(&tx, 0, माप(tx));

	adjसमयx(&tx);
	वापस tx.tai;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक i, ret;

	ret = get_tai();
	म_लिखो("tai offset started at %i\n", ret);

	म_लिखो("Checking tai offsets can be properly set: ");
	ख_साफ(मानक_निकास);
	क्रम (i = 1; i <= 60; i++) अणु
		ret = set_tai(i);
		ret = get_tai();
		अगर (ret != i) अणु
			म_लिखो("[FAILED] expected: %i got %i\n", i, ret);
			वापस ksft_निकास_fail();
		पूर्ण
	पूर्ण
	म_लिखो("[OK]\n");
	वापस ksft_निकास_pass();
पूर्ण
