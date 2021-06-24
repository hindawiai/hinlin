<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा _GNU_SOURCE
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <sched.h>
#समावेश <stdbool.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश <यंत्र/ioctls.h>
#समावेश <sys/mount.h>
#समावेश <sys/रुको.h>
#समावेश "../kselftest.h"

अटल bool terminal_dup2(पूर्णांक duplicate, पूर्णांक original)
अणु
	पूर्णांक ret;

	ret = dup2(duplicate, original);
	अगर (ret < 0)
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक terminal_set_stdfds(पूर्णांक fd)
अणु
	पूर्णांक i;

	अगर (fd < 0)
		वापस 0;

	क्रम (i = 0; i < 3; i++)
		अगर (!terminal_dup2(fd, (पूर्णांक[])अणुSTDIN_खाताNO, STDOUT_खाताNO,
					       STDERR_खाताNOपूर्ण[i]))
			वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक login_pty(पूर्णांक fd)
अणु
	पूर्णांक ret;

	setsid();

	ret = ioctl(fd, TIOCSCTTY, शून्य);
	अगर (ret < 0)
		वापस -1;

	ret = terminal_set_stdfds(fd);
	अगर (ret < 0)
		वापस -1;

	अगर (fd > STDERR_खाताNO)
		बंद(fd);

	वापस 0;
पूर्ण

अटल पूर्णांक रुको_क्रम_pid(pid_t pid)
अणु
	पूर्णांक status, ret;

again:
	ret = रुकोpid(pid, &status, 0);
	अगर (ret == -1) अणु
		अगर (त्रुटि_सं == EINTR)
			जाओ again;
		वापस -1;
	पूर्ण
	अगर (ret != pid)
		जाओ again;

	अगर (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक resolve_procfd_symlink(पूर्णांक fd, अक्षर *buf, माप_प्रकार buflen)
अणु
	पूर्णांक ret;
	अक्षर procfd[4096];

	ret = snम_लिखो(procfd, 4096, "/proc/self/fd/%d", fd);
	अगर (ret < 0 || ret >= 4096)
		वापस -1;

	ret = पढ़ोlink(procfd, buf, buflen);
	अगर (ret < 0 || (माप_प्रकार)ret >= buflen)
		वापस -1;

	buf[ret] = '\0';

	वापस 0;
पूर्ण

अटल पूर्णांक करो_tiocgptpeer(अक्षर *pपंचांगx, अक्षर *expected_procfd_contents)
अणु
	पूर्णांक ret;
	पूर्णांक master = -1, slave = -1, fret = -1;

	master = खोलो(pपंचांगx, O_RDWR | O_NOCTTY | O_CLOEXEC);
	अगर (master < 0) अणु
		ख_लिखो(मानक_त्रुटि, "Failed to open \"%s\": %s\n", pपंचांगx,
			म_त्रुटि(त्रुटि_सं));
		वापस -1;
	पूर्ण

	/*
	 * grantpt() makes assumptions about /dev/pts/ so ignore it. It's also
	 * not really needed.
	 */
	ret = unlockpt(master);
	अगर (ret < 0) अणु
		ख_लिखो(मानक_त्रुटि, "Failed to unlock terminal\n");
		जाओ करो_cleanup;
	पूर्ण

#अगर_घोषित TIOCGPTPEER
	slave = ioctl(master, TIOCGPTPEER, O_RDWR | O_NOCTTY | O_CLOEXEC);
#पूर्ण_अगर
	अगर (slave < 0) अणु
		अगर (त्रुटि_सं == EINVAL) अणु
			ख_लिखो(मानक_त्रुटि, "TIOCGPTPEER is not supported. "
					"Skipping test.\n");
			fret = KSFT_SKIP;
		पूर्ण अन्यथा अणु
			ख_लिखो(मानक_त्रुटि,
				"Failed to perform TIOCGPTPEER ioctl\n");
			fret = निकास_त्रुटि;
		पूर्ण
		जाओ करो_cleanup;
	पूर्ण

	pid_t pid = विभाजन();
	अगर (pid < 0)
		जाओ करो_cleanup;

	अगर (pid == 0) अणु
		अक्षर buf[4096];

		ret = login_pty(slave);
		अगर (ret < 0) अणु
			ख_लिखो(मानक_त्रुटि, "Failed to setup terminal\n");
			_निकास(निकास_त्रुटि);
		पूर्ण

		ret = resolve_procfd_symlink(STDIN_खाताNO, buf, माप(buf));
		अगर (ret < 0) अणु
			ख_लिखो(मानक_त्रुटि, "Failed to retrieve pathname of pts "
					"slave file descriptor\n");
			_निकास(निकास_त्रुटि);
		पूर्ण

		अगर (म_भेदन(expected_procfd_contents, buf,
			    म_माप(expected_procfd_contents)) != 0) अणु
			ख_लिखो(मानक_त्रुटि, "Received invalid contents for "
					"\"/proc/<pid>/fd/%d\" symlink: %s\n",
					STDIN_खाताNO, buf);
			_निकास(-1);
		पूर्ण

		ख_लिखो(मानक_त्रुटि, "Contents of \"/proc/<pid>/fd/%d\" "
				"symlink are valid: %s\n", STDIN_खाताNO, buf);

		_निकास(निकास_सफल);
	पूर्ण

	ret = रुको_क्रम_pid(pid);
	अगर (ret < 0)
		जाओ करो_cleanup;

	fret = निकास_सफल;

करो_cleanup:
	अगर (master >= 0)
		बंद(master);
	अगर (slave >= 0)
		बंद(slave);

	वापस fret;
पूर्ण

अटल पूर्णांक verअगरy_non_standard_devpts_mount(व्योम)
अणु
	अक्षर *mntpoपूर्णांक;
	पूर्णांक ret = -1;
	अक्षर devpts[] = P_पंचांगpdir "/devpts_fs_XXXXXX";
	अक्षर pपंचांगx[] = P_पंचांगpdir "/devpts_fs_XXXXXX/ptmx";

	ret = umount("/dev/pts");
	अगर (ret < 0) अणु
		ख_लिखो(मानक_त्रुटि, "Failed to unmount \"/dev/pts\": %s\n",
				म_त्रुटि(त्रुटि_सं));
		वापस -1;
	पूर्ण

	(व्योम)umount("/dev/ptmx");

	mntpoपूर्णांक = mkdtemp(devpts);
	अगर (!mntpoपूर्णांक) अणु
		ख_लिखो(मानक_त्रुटि, "Failed to create temporary mountpoint: %s\n",
				 म_त्रुटि(त्रुटि_सं));
		वापस -1;
	पूर्ण

	ret = mount("devpts", mntpoपूर्णांक, "devpts", MS_NOSUID | MS_NOEXEC,
		    "newinstance,ptmxmode=0666,mode=0620,gid=5");
	अगर (ret < 0) अणु
		ख_लिखो(मानक_त्रुटि, "Failed to mount devpts fs to \"%s\" in new "
				"mount namespace: %s\n", mntpoपूर्णांक,
				म_त्रुटि(त्रुटि_सं));
		unlink(mntpoपूर्णांक);
		वापस -1;
	पूर्ण

	ret = snम_लिखो(pपंचांगx, माप(pपंचांगx), "%s/ptmx", devpts);
	अगर (ret < 0 || (माप_प्रकार)ret >= माप(pपंचांगx)) अणु
		unlink(mntpoपूर्णांक);
		वापस -1;
	पूर्ण

	ret = करो_tiocgptpeer(pपंचांगx, mntpoपूर्णांक);
	unlink(mntpoपूर्णांक);
	अगर (ret < 0)
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक verअगरy_pपंचांगx_bind_mount(व्योम)
अणु
	पूर्णांक ret;

	ret = mount("/dev/pts/ptmx", "/dev/ptmx", शून्य, MS_BIND, शून्य);
	अगर (ret < 0) अणु
		ख_लिखो(मानक_त्रुटि, "Failed to bind mount \"/dev/pts/ptmx\" to "
				"\"/dev/ptmx\" mount namespace\n");
		वापस -1;
	पूर्ण

	ret = करो_tiocgptpeer("/dev/ptmx", "/dev/pts/");
	अगर (ret < 0)
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक verअगरy_invalid_pपंचांगx_bind_mount(व्योम)
अणु
	पूर्णांक ret;
	अक्षर mntpoपूर्णांक_fd;
	अक्षर pपंचांगx[] = P_पंचांगpdir "/devpts_ptmx_XXXXXX";

	mntpoपूर्णांक_fd = mkstemp(pपंचांगx);
	अगर (mntpoपूर्णांक_fd < 0) अणु
		ख_लिखो(मानक_त्रुटि, "Failed to create temporary directory: %s\n",
				 म_त्रुटि(त्रुटि_सं));
		वापस -1;
	पूर्ण

	ret = mount("/dev/pts/ptmx", pपंचांगx, शून्य, MS_BIND, शून्य);
	बंद(mntpoपूर्णांक_fd);
	अगर (ret < 0) अणु
		ख_लिखो(मानक_त्रुटि, "Failed to bind mount \"/dev/pts/ptmx\" to "
				"\"%s\" mount namespace\n", pपंचांगx);
		वापस -1;
	पूर्ण

	ret = करो_tiocgptpeer(pपंचांगx, "/dev/pts/");
	अगर (ret == 0)
		वापस -1;

	वापस 0;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	पूर्णांक ret;

	अगर (!isatty(STDIN_खाताNO)) अणु
		ख_लिखो(मानक_त्रुटि, "Standard input file descriptor is not attached "
				"to a terminal. Skipping test\n");
		निकास(KSFT_SKIP);
	पूर्ण

	ret = unshare(CLONE_NEWNS);
	अगर (ret < 0) अणु
		ख_लिखो(मानक_त्रुटि, "Failed to unshare mount namespace\n");
		निकास(निकास_त्रुटि);
	पूर्ण

	ret = mount("", "/", शून्य, MS_PRIVATE | MS_REC, 0);
	अगर (ret < 0) अणु
		ख_लिखो(मानक_त्रुटि, "Failed to make \"/\" MS_PRIVATE in new mount "
				"namespace\n");
		निकास(निकास_त्रुटि);
	पूर्ण

	ret = verअगरy_pपंचांगx_bind_mount();
	अगर (ret < 0)
		निकास(निकास_त्रुटि);

	ret = verअगरy_invalid_pपंचांगx_bind_mount();
	अगर (ret < 0)
		निकास(निकास_त्रुटि);

	ret = verअगरy_non_standard_devpts_mount();
	अगर (ret < 0)
		निकास(निकास_त्रुटि);

	निकास(निकास_सफल);
पूर्ण
