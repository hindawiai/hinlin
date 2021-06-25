<शैली गुरु>
/* Time bounds setting test
 *		by: john stultz (johnstul@us.ibm.com)
 *		(C) Copyright IBM 2012
 *		Licensed under the GPLv2
 *
 *  NOTE: This is a meta-test which sets the समय to edge हालs then
 *  uses other tests to detect problems. Thus this test requires that
 *  the inconsistency-check and nanosleep tests be present in the same
 *  directory it is run from.
 *
 *  To build:
 *	$ gcc set-2038.c -o set-2038 -lrt
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
#समावेश <समय.स>
#समावेश <sys/समय.स>
#समावेश "../kselftest.h"

#घोषणा NSEC_PER_SEC 1000000000LL

#घोषणा KTIME_MAX	((दीर्घ दीर्घ)~((अचिन्हित दीर्घ दीर्घ)1 << 63))
#घोषणा KTIME_SEC_MAX	(KTIME_MAX / NSEC_PER_SEC)

#घोषणा YEAR_1901 (-0x7fffffffL)
#घोषणा YEAR_1970 1
#घोषणा YEAR_2038 0x7fffffffL			/*overflows 32bit समय_प्रकार */
#घोषणा YEAR_2262 KTIME_SEC_MAX			/*overflows 64bit kसमय_प्रकार */
#घोषणा YEAR_MAX  ((दीर्घ दीर्घ)((1ULL<<63)-1))	/*overflows 64bit समय_प्रकार */

पूर्णांक is32bits(व्योम)
अणु
	वापस (माप(दीर्घ) == 4);
पूर्ण

पूर्णांक समय_रखो(दीर्घ दीर्घ समय)
अणु
	काष्ठा समयval now;
	पूर्णांक ret;

	now.tv_sec = (समय_प्रकार)समय;
	now.tv_usec  = 0;

	ret = समय_रखोofday(&now, शून्य);

	म_लिखो("Setting time to 0x%lx: %d\n", (दीर्घ)समय, ret);
	वापस ret;
पूर्ण

पूर्णांक करो_tests(व्योम)
अणु
	पूर्णांक ret;

	ret = प्रणाली("date");
	ret = प्रणाली("./inconsistency-check -c 0 -t 20");
	ret |= प्रणाली("./nanosleep");
	ret |= प्रणाली("./nsleep-lat");
	वापस ret;

पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	पूर्णांक ret = 0;
	पूर्णांक opt, dangerous = 0;
	समय_प्रकार start;

	/* Process arguments */
	जबतक ((opt = getopt(argc, argv, "d")) != -1) अणु
		चयन (opt) अणु
		हाल 'd':
			dangerous = 1;
		पूर्ण
	पूर्ण

	start = समय(0);

	/* First test that crazy values करोn't work */
	अगर (!समय_रखो(YEAR_1901)) अणु
		ret = -1;
		जाओ out;
	पूर्ण
	अगर (!समय_रखो(YEAR_MAX)) अणु
		ret = -1;
		जाओ out;
	पूर्ण
	अगर (!is32bits() && !समय_रखो(YEAR_2262)) अणु
		ret = -1;
		जाओ out;
	पूर्ण

	/* Now test behavior near edges */
	समय_रखो(YEAR_1970);
	ret = करो_tests();
	अगर (ret)
		जाओ out;

	समय_रखो(YEAR_2038 - 600);
	ret = करो_tests();
	अगर (ret)
		जाओ out;

	/* The rest of the tests can blowup on 32bit प्रणालीs */
	अगर (is32bits() && !dangerous)
		जाओ out;
	/* Test rollover behavior 32bit edge */
	समय_रखो(YEAR_2038 - 10);
	ret = करो_tests();
	अगर (ret)
		जाओ out;

	समय_रखो(YEAR_2262 - 600);
	ret = करो_tests();

out:
	/* restore घड़ी */
	समय_रखो(start);
	अगर (ret)
		वापस ksft_निकास_fail();
	वापस ksft_निकास_pass();
पूर्ण
