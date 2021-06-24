<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा _GNU_SOURCE	/* needed to get the defines */
#समावेश <fcntl.h>	/* in glibc 2.2 this has the needed
				   values defined */
#समावेश <संकेत.स>
#समावेश <मानकपन.स>
#समावेश <unistd.h>

अटल अस्थिर पूर्णांक event_fd;

अटल व्योम handler(पूर्णांक sig, siginfo_t *si, व्योम *data)
अणु
	event_fd = si->si_fd;
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	काष्ठा sigaction act;
	पूर्णांक fd;

	act.sa_sigaction = handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGRTMIN + 1, &act, शून्य);

	fd = खोलो(".", O_RDONLY);
	fcntl(fd, F_SETSIG, SIGRTMIN + 1);
	fcntl(fd, F_NOTIFY, DN_MODIFY|DN_CREATE|DN_MULTISHOT);
	/* we will now be notअगरied अगर any of the files
	   in "." is modअगरied or new files are created */
	जबतक (1) अणु
		छोड़ो();
		म_लिखो("Got event on fd=%d\n", event_fd);
	पूर्ण
पूर्ण
