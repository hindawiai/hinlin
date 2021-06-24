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

#घोषणा pr_err(fmt, ...) \
		(अणु \
			ख_लिखो(मानक_त्रुटि, "%s:%d:" fmt ": %m\n", \
				__func__, __LINE__, ##__VA_ARGS__); \
			1; \
		पूर्ण)

#घोषणा NSIO	0xb7
#घोषणा NS_GET_USERNS   _IO(NSIO, 0x1)
#घोषणा NS_GET_PARENT   _IO(NSIO, 0x2)

#घोषणा __stack_aligned__	__attribute__((aligned(16)))
काष्ठा cr_clone_arg अणु
	अक्षर stack[128] __stack_aligned__;
	अक्षर stack_ptr[];
पूर्ण;

अटल पूर्णांक child(व्योम *args)
अणु
	prctl(PR_SET_PDEATHSIG, SIGKILL);
	जबतक (1)
		sleep(1);
	निकास(0);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	अक्षर *ns_strs[] = अणु"pid", "user"पूर्ण;
	अक्षर path[] = "/proc/0123456789/ns/pid";
	काष्ठा cr_clone_arg ca;
	काष्ठा stat st1, st2;
	पूर्णांक ns, pns, i;
	pid_t pid;

	pid = clone(child, ca.stack_ptr, CLONE_NEWUSER | CLONE_NEWPID | SIGCHLD, शून्य);
	अगर (pid < 0)
		वापस pr_err("clone");

	क्रम (i = 0; i < 2; i++) अणु
		snम_लिखो(path, माप(path), "/proc/%d/ns/%s", pid, ns_strs[i]);
		ns = खोलो(path, O_RDONLY);
		अगर (ns < 0)
			वापस pr_err("Unable to open %s", path);

		pns = ioctl(ns, NS_GET_PARENT);
		अगर (pns < 0)
			वापस pr_err("Unable to get a parent pidns");

		snम_लिखो(path, माप(path), "/proc/self/ns/%s", ns_strs[i]);
		अगर (stat(path, &st2))
			वापस pr_err("Unable to stat %s", path);
		अगर (ख_स्थिति(pns, &st1))
			वापस pr_err("Unable to stat the parent pidns");
		अगर (st1.st_ino != st2.st_ino)
			वापस pr_err("NS_GET_PARENT returned a wrong namespace");

		अगर (ioctl(pns, NS_GET_PARENT) >= 0 || त्रुटि_सं != EPERM)
			वापस pr_err("Don't get EPERM");
	पूर्ण

	समाप्त(pid, SIGKILL);
	रुको(शून्य);
	वापस 0;
पूर्ण
