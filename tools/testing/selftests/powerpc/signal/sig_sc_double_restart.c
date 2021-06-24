<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Test that a syscall करोes not get restarted twice, handled by trap_norestart()
 *
 * Based on Al's description, and a test क्रम the bug fixed in this commit:
 *
 * commit 9a81c16b527528ad307843be5571111aa8d35a80
 * Author: Al Viro <viro@zeniv.linux.org.uk>
 * Date:   Mon Sep 20 21:48:57 2010 +0100
 *
 *  घातerpc: fix द्विगुन syscall restarts
 *
 *  Make sigवापस zero regs->trap, make करो_संकेत() करो the same on all
 *  paths.  As it is, संकेत पूर्णांकerrupting e.g. पढ़ो() from fd 512 (==
 *  ERESTARTSYS) with another संकेत getting unblocked when the first
 *  handler finishes will lead to restart one insn earlier than it ought
 *  to.  Same क्रम multiple संकेतs with in-kernel handlers पूर्णांकerrupting
 *  that sucker at the same समय.  Same क्रम multiple संकेतs of any kind
 *  पूर्णांकerrupting that sucker on 64bit...
 */
#घोषणा _GNU_SOURCE
#समावेश <sys/types.h>
#समावेश <sys/रुको.h>
#समावेश <sys/syscall.h>
#समावेश <unistd.h>
#समावेश <संकेत.स>
#समावेश <त्रुटिसं.स>
#समावेश <मानककोष.स>
#समावेश <मानकपन.स>
#समावेश <माला.स>

#समावेश "utils.h"

अटल व्योम SIGUSR1_handler(पूर्णांक sig)
अणु
	समाप्त(getpid(), SIGUSR2);
	/*
	 * SIGUSR2 is blocked until the handler निकासs, at which poपूर्णांक it will
	 * be उठाओd again and think there is a restart to be करोne because the
	 * pending restarted syscall has 512 (ERESTARTSYS) in r3. The second
	 * restart will retreat NIP another 4 bytes to fail हाल branch.
	 */
पूर्ण

अटल व्योम SIGUSR2_handler(पूर्णांक sig)
अणु
पूर्ण

अटल sमाप_प्रकार raw_पढ़ो(पूर्णांक fd, व्योम *buf, माप_प्रकार count)
अणु
	रेजिस्टर दीर्घ nr यंत्र("r0") = __NR_पढ़ो;
	रेजिस्टर दीर्घ _fd यंत्र("r3") = fd;
	रेजिस्टर व्योम *_buf यंत्र("r4") = buf;
	रेजिस्टर माप_प्रकार _count यंत्र("r5") = count;

	यंत्र अस्थिर(
"		b	0f		\n"
"		b	1f		\n"
"	0:	sc	0		\n"
"		bns	2f		\n"
"		neg	%0,%0		\n"
"		b	2f		\n"
"	1:				\n"
"		li	%0,%4		\n"
"	2:				\n"
		: "+r"(_fd), "+r"(nr), "+r"(_buf), "+r"(_count)
		: "i"(-ENOANO)
		: "memory", "r6", "r7", "r8", "r9", "r10", "r11", "r12", "ctr", "cr0");

	अगर (_fd < 0) अणु
		त्रुटि_सं = -_fd;
		_fd = -1;
	पूर्ण

	वापस _fd;
पूर्ण

#घोषणा DATA "test 123"
#घोषणा DLEN (म_माप(DATA)+1)

पूर्णांक test_restart(व्योम)
अणु
	पूर्णांक pipefd[2];
	pid_t pid;
	अक्षर buf[512];

	अगर (pipe(pipefd) == -1) अणु
		लिखो_त्रुटि("pipe");
		निकास(निकास_त्रुटि);
	पूर्ण

	pid = विभाजन();
	अगर (pid == -1) अणु
		लिखो_त्रुटि("fork");
		निकास(निकास_त्रुटि);
	पूर्ण

	अगर (pid == 0) अणु /* Child पढ़ोs from pipe */
		काष्ठा sigaction act;
		पूर्णांक fd;

		स_रखो(&act, 0, माप(act));
		sigaddset(&act.sa_mask, SIGUSR2);
		act.sa_handler = SIGUSR1_handler;
		act.sa_flags = SA_RESTART;
		अगर (sigaction(SIGUSR1, &act, शून्य) == -1) अणु
			लिखो_त्रुटि("sigaction");
			निकास(निकास_त्रुटि);
		पूर्ण

		स_रखो(&act, 0, माप(act));
		act.sa_handler = SIGUSR2_handler;
		act.sa_flags = SA_RESTART;
		अगर (sigaction(SIGUSR2, &act, शून्य) == -1) अणु
			लिखो_त्रुटि("sigaction");
			निकास(निकास_त्रुटि);
		पूर्ण

		/* Let's get ERESTARTSYS पूर्णांकo r3 */
		जबतक ((fd = dup(pipefd[0])) != 512) अणु
			अगर (fd == -1) अणु
				लिखो_त्रुटि("dup");
				निकास(निकास_त्रुटि);
			पूर्ण
		पूर्ण

		अगर (raw_पढ़ो(fd, buf, 512) == -1) अणु
			अगर (त्रुटि_सं == ENOANO) अणु
				ख_लिखो(मानक_त्रुटि, "Double restart moved restart before sc instruction.\n");
				_निकास(निकास_त्रुटि);
			पूर्ण
			लिखो_त्रुटि("read");
			निकास(निकास_त्रुटि);
		पूर्ण

		अगर (म_भेदन(buf, DATA, DLEN)) अणु
			ख_लिखो(मानक_त्रुटि, "bad test string %s\n", buf);
			निकास(निकास_त्रुटि);
		पूर्ण

		वापस 0;

	पूर्ण अन्यथा अणु
		पूर्णांक wstatus;

		usleep(100000);		/* Hack to get पढ़ोer रुकोing */
		समाप्त(pid, SIGUSR1);
		usleep(100000);
		अगर (ग_लिखो(pipefd[1], DATA, DLEN) != DLEN) अणु
			लिखो_त्रुटि("write");
			निकास(निकास_त्रुटि);
		पूर्ण
		बंद(pipefd[0]);
		बंद(pipefd[1]);
		अगर (रुको(&wstatus) == -1) अणु
			लिखो_त्रुटि("wait");
			निकास(निकास_त्रुटि);
		पूर्ण
		अगर (!WIFEXITED(wstatus)) अणु
			ख_लिखो(मानक_त्रुटि, "child exited abnormally\n");
			निकास(निकास_त्रुटि);
		पूर्ण

		FAIL_IF(WEXITSTATUS(wstatus) != निकास_सफल);

		वापस 0;
	पूर्ण
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	test_harness_set_समयout(10);
	वापस test_harness(test_restart, "sig sys restart");
पूर्ण
