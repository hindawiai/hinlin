<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा _GNU_SOURCE
#समावेश <sched.h>
#समावेश <unistd.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <संकेत.स>
#समावेश <त्रुटिसं.स>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>
#समावेश <sys/ioctl.h>
#समावेश <sys/prctl.h>
#समावेश <sys/रुको.h>

#घोषणा NSIO    0xb7
#घोषणा NS_GET_USERNS   _IO(NSIO, 0x1)

#घोषणा pr_err(fmt, ...) \
		(अणु \
			ख_लिखो(मानक_त्रुटि, "%s:%d:" fmt ": %m\n", \
				__func__, __LINE__, ##__VA_ARGS__); \
			1; \
		पूर्ण)

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argvp[])
अणु
	पूर्णांक pfd[2], ns, uns, init_uns;
	काष्ठा stat st1, st2;
	अक्षर path[128];
	pid_t pid;
	अक्षर c;

	अगर (pipe(pfd))
		वापस 1;

	pid = विभाजन();
	अगर (pid < 0)
		वापस pr_err("fork");
	अगर (pid == 0) अणु
		prctl(PR_SET_PDEATHSIG, SIGKILL);
		अगर (unshare(CLONE_NEWUTS | CLONE_NEWUSER))
			वापस pr_err("unshare");
		बंद(pfd[0]);
		बंद(pfd[1]);
		जबतक (1)
			sleep(1);
		वापस 0;
	पूर्ण
	बंद(pfd[1]);
	अगर (पढ़ो(pfd[0], &c, 1) != 0)
		वापस pr_err("Unable to read from pipe");
	बंद(pfd[0]);

	snम_लिखो(path, माप(path), "/proc/%d/ns/uts", pid);
	ns = खोलो(path, O_RDONLY);
	अगर (ns < 0)
		वापस pr_err("Unable to open %s", path);

	uns = ioctl(ns, NS_GET_USERNS);
	अगर (uns < 0)
		वापस pr_err("Unable to get an owning user namespace");

	अगर (ख_स्थिति(uns, &st1))
		वापस pr_err("fstat");

	snम_लिखो(path, माप(path), "/proc/%d/ns/user", pid);
	अगर (stat(path, &st2))
		वापस pr_err("stat");

	अगर (st1.st_ino != st2.st_ino)
		वापस pr_err("NS_GET_USERNS returned a wrong namespace");

	init_uns = ioctl(uns, NS_GET_USERNS);
	अगर (uns < 0)
		वापस pr_err("Unable to get an owning user namespace");

	अगर (ioctl(init_uns, NS_GET_USERNS) >= 0 || त्रुटि_सं != EPERM)
		वापस pr_err("Don't get EPERM");

	अगर (unshare(CLONE_NEWUSER))
		वापस pr_err("unshare");

	अगर (ioctl(ns, NS_GET_USERNS) >= 0 || त्रुटि_सं != EPERM)
		वापस pr_err("Don't get EPERM");
	अगर (ioctl(init_uns, NS_GET_USERNS) >= 0 || त्रुटि_सं != EPERM)
		वापस pr_err("Don't get EPERM");

	समाप्त(pid, SIGKILL);
	रुको(शून्य);
	वापस 0;
पूर्ण
