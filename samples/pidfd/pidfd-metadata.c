<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#घोषणा _GNU_SOURCE
#समावेश <err.h>
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <पूर्णांकtypes.h>
#समावेश <सीमा.स>
#समावेश <sched.h>
#समावेश <संकेत.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/स्थिति.स>
#समावेश <sys/syscall.h>
#समावेश <sys/types.h>
#समावेश <sys/रुको.h>
#समावेश <unistd.h>

#अगर_अघोषित CLONE_PIDFD
#घोषणा CLONE_PIDFD 0x00001000
#पूर्ण_अगर

#अगर_अघोषित __NR_pidfd_send_संकेत
#घोषणा __NR_pidfd_send_संकेत -1
#पूर्ण_अगर

अटल पूर्णांक करो_child(व्योम *args)
अणु
	म_लिखो("%d\n", getpid());
	_निकास(निकास_सफल);
पूर्ण

अटल pid_t pidfd_clone(पूर्णांक flags, पूर्णांक *pidfd)
अणु
	माप_प्रकार stack_size = 1024;
	अक्षर *stack[1024] = अणु 0 पूर्ण;

#अगर_घोषित __ia64__
	वापस __clone2(करो_child, stack, stack_size, flags | SIGCHLD, शून्य, pidfd);
#अन्यथा
	वापस clone(करो_child, stack + stack_size, flags | SIGCHLD, शून्य, pidfd);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत पूर्णांक sys_pidfd_send_संकेत(पूर्णांक pidfd, पूर्णांक sig, siginfo_t *info,
					अचिन्हित पूर्णांक flags)
अणु
	वापस syscall(__NR_pidfd_send_संकेत, pidfd, sig, info, flags);
पूर्ण

अटल पूर्णांक pidfd_metadata_fd(pid_t pid, पूर्णांक pidfd)
अणु
	पूर्णांक procfd, ret;
	अक्षर path[100];

	snम_लिखो(path, माप(path), "/proc/%d", pid);
	procfd = खोलो(path, O_सूचीECTORY | O_RDONLY | O_CLOEXEC);
	अगर (procfd < 0) अणु
		warn("Failed to open %s\n", path);
		वापस -1;
	पूर्ण

	/*
	 * Verअगरy that the pid has not been recycled and our /proc/<pid> handle
	 * is still valid.
	 */
	ret = sys_pidfd_send_संकेत(pidfd, 0, शून्य, 0);
	अगर (ret < 0) अणु
		चयन (त्रुटि_सं) अणु
		हाल EPERM:
			/* Process exists, just not allowed to संकेत it. */
			अवरोध;
		शेष:
			warn("Failed to signal process\n");
			बंद(procfd);
			procfd = -1;
		पूर्ण
	पूर्ण

	वापस procfd;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	पूर्णांक pidfd = -1, ret = निकास_त्रुटि;
	अक्षर buf[4096] = अणु 0 पूर्ण;
	pid_t pid;
	पूर्णांक procfd, statusfd;
	sमाप_प्रकार bytes;

	pid = pidfd_clone(CLONE_PIDFD, &pidfd);
	अगर (pid < 0)
		err(ret, "CLONE_PIDFD");
	अगर (pidfd == -1) अणु
		warnx("CLONE_PIDFD is not supported by the kernel");
		जाओ out;
	पूर्ण

	procfd = pidfd_metadata_fd(pid, pidfd);
	बंद(pidfd);
	अगर (procfd < 0)
		जाओ out;

	statusfd = खोलोat(procfd, "status", O_RDONLY | O_CLOEXEC);
	बंद(procfd);
	अगर (statusfd < 0)
		जाओ out;

	bytes = पढ़ो(statusfd, buf, माप(buf));
	अगर (bytes > 0)
		bytes = ग_लिखो(STDOUT_खाताNO, buf, bytes);
	बंद(statusfd);
	ret = निकास_सफल;

out:
	(व्योम)रुको(शून्य);

	निकास(ret);
पूर्ण
