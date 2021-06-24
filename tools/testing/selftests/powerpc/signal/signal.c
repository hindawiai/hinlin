<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2016, Cyril Bur, IBM Corp.
 *
 * Sending one self a संकेत should always get delivered.
 */

#समावेश <संकेत.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/types.h>
#समावेश <sys/रुको.h>
#समावेश <unistd.h>

#समावेश <altivec.h>

#समावेश "utils.h"

#घोषणा MAX_ATTEMPT 500000
#घोषणा TIMEOUT 5

बाह्य दीर्घ संकेत_self(pid_t pid, पूर्णांक sig);

अटल संक_पूर्ण_प्रकार संकेतed;
अटल संक_पूर्ण_प्रकार fail;

अटल व्योम संकेत_handler(पूर्णांक sig)
अणु
	अगर (sig == SIGUSR1)
		संकेतed = 1;
	अन्यथा
		fail = 1;
पूर्ण

अटल पूर्णांक test_संकेत()
अणु
	पूर्णांक i;
	काष्ठा sigaction act;
	pid_t ppid = getpid();
	pid_t pid;

	act.sa_handler = संकेत_handler;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	अगर (sigaction(SIGUSR1, &act, शून्य) < 0) अणु
		लिखो_त्रुटि("sigaction SIGUSR1");
		निकास(1);
	पूर्ण
	अगर (sigaction(SIGALRM, &act, शून्य) < 0) अणु
		लिखो_त्रुटि("sigaction SIGALRM");
		निकास(1);
	पूर्ण

	/* Don't करो this क्रम MAX_ATTEMPT, its simply too दीर्घ */
	क्रम(i  = 0; i < 1000; i++) अणु
		pid = विभाजन();
		अगर (pid == -1) अणु
			लिखो_त्रुटि("fork");
			निकास(1);
		पूर्ण
		अगर (pid == 0) अणु
			संकेत_self(ppid, SIGUSR1);
			निकास(1);
		पूर्ण अन्यथा अणु
			alarm(0); /* Disable any pending */
			alarm(2);
			जबतक (!संकेतed && !fail)
				यंत्र अस्थिर("": : :"memory");
			अगर (!संकेतed) अणु
				ख_लिखो(मानक_त्रुटि, "Didn't get signal from child\n");
				FAIL_IF(1); /* For the line number */
			पूर्ण
			/* Otherwise we'll loop too fast and विभाजन() will eventually fail */
			रुकोpid(pid, शून्य, 0);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < MAX_ATTEMPT; i++) अणु
		दीर्घ rc;

		alarm(0); /* Disable any pending */
		संकेतed = 0;
		alarm(TIMEOUT);
		rc = संकेत_self(ppid, SIGUSR1);
		अगर (rc) अणु
			ख_लिखो(मानक_त्रुटि, "(%d) Fail reason: %d rc=0x%lx",
					i, fail, rc);
			FAIL_IF(1); /* For the line number */
		पूर्ण
		जबतक (!संकेतed && !fail)
			यंत्र अस्थिर("": : :"memory");
		अगर (!संकेतed) अणु
			ख_लिखो(मानक_त्रुटि, "(%d) Fail reason: %d rc=0x%lx",
					i, fail, rc);
			FAIL_IF(1); /* For the line number */
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	test_harness_set_समयout(300);
	वापस test_harness(test_संकेत, "signal");
पूर्ण
