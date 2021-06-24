<शैली गुरु>
/* Set tz value
 *              by: John Stultz <john.stultz@linaro.org>
 *              (C) Copyright Linaro 2016
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

पूर्णांक set_tz(पूर्णांक min, पूर्णांक dst)
अणु
	काष्ठा समयzone tz;

	tz.tz_minuteswest = min;
	tz.tz_dstसमय = dst;

	वापस समय_रखोofday(0, &tz);
पूर्ण

पूर्णांक get_tz_min(व्योम)
अणु
	काष्ठा समयzone tz;
	काष्ठा समयval tv;

	स_रखो(&tz, 0, माप(tz));
	समय_लोofday(&tv, &tz);
	वापस tz.tz_minuteswest;
पूर्ण

पूर्णांक get_tz_dst(व्योम)
अणु
	काष्ठा समयzone tz;
	काष्ठा समयval tv;

	स_रखो(&tz, 0, माप(tz));
	समय_लोofday(&tv, &tz);
	वापस tz.tz_dstसमय;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक i, ret;
	पूर्णांक min, dst;

	min = get_tz_min();
	dst = get_tz_dst();
	म_लिखो("tz_minuteswest started at %i, dst at %i\n", min, dst);

	म_लिखो("Checking tz_minuteswest can be properly set: ");
	ख_साफ(मानक_निकास);
	क्रम (i = -15*60; i < 15*60; i += 30) अणु
		ret = set_tz(i, dst);
		ret = get_tz_min();
		अगर (ret != i) अणु
			म_लिखो("[FAILED] expected: %i got %i\n", i, ret);
			जाओ err;
		पूर्ण
	पूर्ण
	म_लिखो("[OK]\n");

	म_लिखो("Checking invalid tz_minuteswest values are caught: ");
	ख_साफ(मानक_निकास);

	अगर (!set_tz(-15*60-1, dst)) अणु
		म_लिखो("[FAILED] %i didn't return failure!\n", -15*60-1);
		जाओ err;
	पूर्ण

	अगर (!set_tz(15*60+1, dst)) अणु
		म_लिखो("[FAILED] %i didn't return failure!\n", 15*60+1);
		जाओ err;
	पूर्ण

	अगर (!set_tz(-24*60, dst)) अणु
		म_लिखो("[FAILED] %i didn't return failure!\n", -24*60);
		जाओ err;
	पूर्ण

	अगर (!set_tz(24*60, dst)) अणु
		म_लिखो("[FAILED] %i didn't return failure!\n", 24*60);
		जाओ err;
	पूर्ण

	म_लिखो("[OK]\n");

	set_tz(min, dst);
	वापस ksft_निकास_pass();

err:
	set_tz(min, dst);
	वापस ksft_निकास_fail();
पूर्ण
