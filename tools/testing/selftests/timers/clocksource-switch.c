<शैली गुरु>
/* Clocksource change test
 *		by: john stultz (johnstul@us.ibm.com)
 *		(C) Copyright IBM 2012
 *		Licensed under the GPLv2
 *
 *  NOTE: This is a meta-test which quickly changes the घड़ीsource and
 *  then uses other tests to detect problems. Thus this test requires
 *  that the inconsistency-check and nanosleep tests be present in the
 *  same directory it is run from.
 *
 *  To build:
 *	$ gcc घड़ीsource-चयन.c -o घड़ीsource-चयन -lrt
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
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>
#समावेश <माला.स>
#समावेश <sys/रुको.h>
#समावेश "../kselftest.h"


पूर्णांक get_घड़ीsources(अक्षर list[][30])
अणु
	पूर्णांक fd, i;
	माप_प्रकार size;
	अक्षर buf[512];
	अक्षर *head, *पंचांगp;

	fd = खोलो("/sys/devices/system/clocksource/clocksource0/available_clocksource", O_RDONLY);

	size = पढ़ो(fd, buf, 512);

	बंद(fd);

	क्रम (i = 0; i < 10; i++)
		list[i][0] = '\0';

	head = buf;
	i = 0;
	जबतक (head - buf < size) अणु
		/* Find the next space */
		क्रम (पंचांगp = head; *पंचांगp != ' '; पंचांगp++) अणु
			अगर (*पंचांगp == '\n')
				अवरोध;
			अगर (*पंचांगp == '\0')
				अवरोध;
		पूर्ण
		*पंचांगp = '\0';
		म_नकल(list[i], head);
		head = पंचांगp + 1;
		i++;
	पूर्ण

	वापस i-1;
पूर्ण

पूर्णांक get_cur_घड़ीsource(अक्षर *buf, माप_प्रकार size)
अणु
	पूर्णांक fd;

	fd = खोलो("/sys/devices/system/clocksource/clocksource0/current_clocksource", O_RDONLY);

	size = पढ़ो(fd, buf, size);

	वापस 0;
पूर्ण

पूर्णांक change_घड़ीsource(अक्षर *घड़ीsource)
अणु
	पूर्णांक fd;
	sमाप_प्रकार size;

	fd = खोलो("/sys/devices/system/clocksource/clocksource0/current_clocksource", O_WRONLY);

	अगर (fd < 0)
		वापस -1;

	size = ग_लिखो(fd, घड़ीsource, म_माप(घड़ीsource));

	अगर (size < 0)
		वापस -1;

	बंद(fd);
	वापस 0;
पूर्ण


पूर्णांक run_tests(पूर्णांक secs)
अणु
	पूर्णांक ret;
	अक्षर buf[255];

	प्र_लिखो(buf, "./inconsistency-check -t %i", secs);
	ret = प्रणाली(buf);
	अगर (ret)
		वापस ret;
	ret = प्रणाली("./nanosleep");
	वापस ret;
पूर्ण


अक्षर घड़ीsource_list[10][30];

पूर्णांक मुख्य(पूर्णांक argv, अक्षर **argc)
अणु
	अक्षर orig_clk[512];
	पूर्णांक count, i, status;
	pid_t pid;

	get_cur_घड़ीsource(orig_clk, 512);

	count = get_घड़ीsources(घड़ीsource_list);

	अगर (change_घड़ीsource(घड़ीsource_list[0])) अणु
		म_लिखो("Error: You probably need to run this as root\n");
		वापस -1;
	पूर्ण

	/* Check everything is sane beक्रमe we start चयनing asynchronously */
	क्रम (i = 0; i < count; i++) अणु
		म_लिखो("Validating clocksource %s\n", घड़ीsource_list[i]);
		अगर (change_घड़ीsource(घड़ीsource_list[i])) अणु
			status = -1;
			जाओ out;
		पूर्ण
		अगर (run_tests(5)) अणु
			status = -1;
			जाओ out;
		पूर्ण
	पूर्ण


	म_लिखो("Running Asynchronous Switching Tests...\n");
	pid = विभाजन();
	अगर (!pid)
		वापस run_tests(60);

	जबतक (pid != रुकोpid(pid, &status, WNOHANG))
		क्रम (i = 0; i < count; i++)
			अगर (change_घड़ीsource(घड़ीsource_list[i])) अणु
				status = -1;
				जाओ out;
			पूर्ण
out:
	change_घड़ीsource(orig_clk);

	अगर (status)
		वापस ksft_निकास_fail();
	वापस ksft_निकास_pass();
पूर्ण
