<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा _GNU_SOURCE

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <संकेत.स>
#समावेश <सीमा.स>
#समावेश <unistd.h>
#समावेश <त्रुटिसं.स>
#समावेश <माला.स>
#समावेश <fcntl.h>
#समावेश <linux/unistd.h>
#समावेश <linux/kcmp.h>

#समावेश <sys/syscall.h>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/रुको.h>
#समावेश <sys/epoll.h>

#समावेश "../kselftest.h"

अटल दीर्घ sys_kcmp(पूर्णांक pid1, पूर्णांक pid2, पूर्णांक type, अचिन्हित दीर्घ fd1, अचिन्हित दीर्घ fd2)
अणु
	वापस syscall(__NR_kcmp, pid1, pid2, type, fd1, fd2);
पूर्ण

अटल स्थिर अचिन्हित पूर्णांक duped_num = 64;

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	स्थिर अक्षर kpath[] = "kcmp-test-file";
	काष्ठा kcmp_epoll_slot epoll_slot;
	काष्ठा epoll_event ev;
	पूर्णांक pid1, pid2;
	पूर्णांक pipefd[2];
	पूर्णांक fd1, fd2;
	पूर्णांक epollfd;
	पूर्णांक status;
	पूर्णांक fddup;

	fd1 = खोलो(kpath, O_RDWR | O_CREAT | O_TRUNC, 0644);
	pid1 = getpid();

	अगर (fd1 < 0) अणु
		लिखो_त्रुटि("Can't create file");
		ksft_निकास_fail();
	पूर्ण

	अगर (pipe(pipefd)) अणु
		लिखो_त्रुटि("Can't create pipe");
		ksft_निकास_fail();
	पूर्ण

	epollfd = epoll_create1(0);
	अगर (epollfd < 0) अणु
		लिखो_त्रुटि("epoll_create1 failed");
		ksft_निकास_fail();
	पूर्ण

	स_रखो(&ev, 0xff, माप(ev));
	ev.events = EPOLLIN | EPOLLOUT;

	अगर (epoll_ctl(epollfd, EPOLL_CTL_ADD, pipefd[0], &ev)) अणु
		लिखो_त्रुटि("epoll_ctl failed");
		ksft_निकास_fail();
	पूर्ण

	fddup = dup2(pipefd[1], duped_num);
	अगर (fddup < 0) अणु
		लिखो_त्रुटि("dup2 failed");
		ksft_निकास_fail();
	पूर्ण

	अगर (epoll_ctl(epollfd, EPOLL_CTL_ADD, fddup, &ev)) अणु
		लिखो_त्रुटि("epoll_ctl failed");
		ksft_निकास_fail();
	पूर्ण
	बंद(fddup);

	pid2 = विभाजन();
	अगर (pid2 < 0) अणु
		लिखो_त्रुटि("fork failed");
		ksft_निकास_fail();
	पूर्ण

	अगर (!pid2) अणु
		पूर्णांक pid2 = getpid();
		पूर्णांक ret;

		fd2 = खोलो(kpath, O_RDWR, 0644);
		अगर (fd2 < 0) अणु
			लिखो_त्रुटि("Can't open file");
			ksft_निकास_fail();
		पूर्ण

		/* An example of output and arguments */
		म_लिखो("pid1: %6d pid2: %6d FD: %2ld FILES: %2ld VM: %2ld "
		       "FS: %2ld SIGHAND: %2ld IO: %2ld SYSVSEM: %2ld "
		       "INV: %2ld\n",
		       pid1, pid2,
		       sys_kcmp(pid1, pid2, KCMP_खाता,		fd1, fd2),
		       sys_kcmp(pid1, pid2, KCMP_खाताS,		0, 0),
		       sys_kcmp(pid1, pid2, KCMP_VM,		0, 0),
		       sys_kcmp(pid1, pid2, KCMP_FS,		0, 0),
		       sys_kcmp(pid1, pid2, KCMP_SIGHAND,	0, 0),
		       sys_kcmp(pid1, pid2, KCMP_IO,		0, 0),
		       sys_kcmp(pid1, pid2, KCMP_SYSVSEM,	0, 0),

			/* This one should fail */
		       sys_kcmp(pid1, pid2, KCMP_TYPES + 1,	0, 0));

		/* This one should वापस same fd */
		ret = sys_kcmp(pid1, pid2, KCMP_खाता, fd1, fd1);
		अगर (ret) अणु
			म_लिखो("FAIL: 0 expected but %d returned (%s)\n",
				ret, म_त्रुटि(त्रुटि_सं));
			ksft_inc_fail_cnt();
			ret = -1;
		पूर्ण अन्यथा अणु
			म_लिखो("PASS: 0 returned as expected\n");
			ksft_inc_pass_cnt();
		पूर्ण

		/* Compare with self */
		ret = sys_kcmp(pid1, pid1, KCMP_VM, 0, 0);
		अगर (ret) अणु
			म_लिखो("FAIL: 0 expected but %d returned (%s)\n",
				ret, म_त्रुटि(त्रुटि_सं));
			ksft_inc_fail_cnt();
			ret = -1;
		पूर्ण अन्यथा अणु
			म_लिखो("PASS: 0 returned as expected\n");
			ksft_inc_pass_cnt();
		पूर्ण

		/* Compare epoll target */
		epoll_slot = (काष्ठा kcmp_epoll_slot) अणु
			.efd	= epollfd,
			.tfd	= duped_num,
			.toff	= 0,
		पूर्ण;
		ret = sys_kcmp(pid1, pid1, KCMP_EPOLL_TFD, pipefd[1],
			       (अचिन्हित दीर्घ)(व्योम *)&epoll_slot);
		अगर (ret) अणु
			म_लिखो("FAIL: 0 expected but %d returned (%s)\n",
				ret, म_त्रुटि(त्रुटि_सं));
			ksft_inc_fail_cnt();
			ret = -1;
		पूर्ण अन्यथा अणु
			म_लिखो("PASS: 0 returned as expected\n");
			ksft_inc_pass_cnt();
		पूर्ण

		ksft_prपूर्णांक_cnts();

		अगर (ret)
			ksft_निकास_fail();
		अन्यथा
			ksft_निकास_pass();
	पूर्ण

	रुकोpid(pid2, &status, P_ALL);

	वापस ksft_निकास_pass();
पूर्ण
