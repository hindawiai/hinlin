<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Test triggering of loading of firmware from dअगरferent mount
 * namespaces. Expect firmware to be always loaded from the mount
 * namespace of PID 1. */
#घोषणा _GNU_SOURCE
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <sched.h>
#समावेश <मानकतर्क.स>
#समावेश <stdbool.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/mount.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/types.h>
#समावेश <sys/रुको.h>
#समावेश <unistd.h>

#अगर_अघोषित CLONE_NEWNS
# define CLONE_NEWNS 0x00020000
#पूर्ण_अगर

अटल अक्षर *fw_path = शून्य;

अटल व्योम die(अक्षर *fmt, ...)
अणु
	बहु_सूची ap;

	बहु_शुरू(ap, fmt);
	भख_लिखो(मानक_त्रुटि, fmt, ap);
	बहु_पूर्ण(ap);
	अगर (fw_path)
		unlink(fw_path);
	umount("/lib/firmware");
	निकास(निकास_त्रुटि);
पूर्ण

अटल व्योम trigger_fw(स्थिर अक्षर *fw_name, स्थिर अक्षर *sys_path)
अणु
	पूर्णांक fd;

	fd = खोलो(sys_path, O_WRONLY);
	अगर (fd < 0)
		die("open failed: %s\n",
		    म_त्रुटि(त्रुटि_सं));
	अगर (ग_लिखो(fd, fw_name, म_माप(fw_name)) != म_माप(fw_name))
		निकास(निकास_त्रुटि);
	बंद(fd);
पूर्ण

अटल व्योम setup_fw(स्थिर अक्षर *fw_path)
अणु
	पूर्णांक fd;
	स्थिर अक्षर fw[] = "ABCD0123";

	fd = खोलो(fw_path, O_WRONLY | O_CREAT, 0600);
	अगर (fd < 0)
		die("open failed: %s\n",
		    म_त्रुटि(त्रुटि_सं));
	अगर (ग_लिखो(fd, fw, माप(fw) -1) != माप(fw) -1)
		die("write failed: %s\n",
		    म_त्रुटि(त्रुटि_सं));
	बंद(fd);
पूर्ण

अटल bool test_fw_in_ns(स्थिर अक्षर *fw_name, स्थिर अक्षर *sys_path, bool block_fw_in_parent_ns)
अणु
	pid_t child;

	अगर (block_fw_in_parent_ns)
		अगर (mount("test", "/lib/firmware", "tmpfs", MS_RDONLY, शून्य) == -1)
			die("blocking firmware in parent ns failed\n");

	child = विभाजन();
	अगर (child == -1) अणु
		die("fork failed: %s\n",
			म_त्रुटि(त्रुटि_सं));
	पूर्ण
	अगर (child != 0) अणु /* parent */
		pid_t pid;
		पूर्णांक status;

		pid = रुकोpid(child, &status, 0);
		अगर (pid == -1) अणु
			die("waitpid failed: %s\n",
				म_त्रुटि(त्रुटि_सं));
		पूर्ण
		अगर (pid != child) अणु
			die("waited for %d got %d\n",
				child, pid);
		पूर्ण
		अगर (!WIFEXITED(status)) अणु
			die("child did not terminate cleanly\n");
		पूर्ण
		अगर (block_fw_in_parent_ns)
			umount("/lib/firmware");
		वापस WEXITSTATUS(status) == निकास_सफल;
	पूर्ण

	अगर (unshare(CLONE_NEWNS) != 0) अणु
		die("unshare(CLONE_NEWNS) failed: %s\n",
			म_त्रुटि(त्रुटि_सं));
	पूर्ण
	अगर (mount(शून्य, "/", शून्य, MS_SLAVE|MS_REC, शून्य) == -1)
		die("remount root in child ns failed\n");

	अगर (!block_fw_in_parent_ns) अणु
		अगर (mount("test", "/lib/firmware", "tmpfs", MS_RDONLY, शून्य) == -1)
			die("blocking firmware in child ns failed\n");
	पूर्ण अन्यथा
		umount("/lib/firmware");

	trigger_fw(fw_name, sys_path);

	निकास(निकास_सफल);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	स्थिर अक्षर *fw_name = "test-firmware.bin";
	अक्षर *sys_path;
	अगर (argc != 2)
		die("usage: %s sys_path\n", argv[0]);

	/* Mount पंचांगpfs to /lib/firmware so we करोn't have to assume
	   that it is writable क्रम us.*/
	अगर (mount("test", "/lib/firmware", "tmpfs", 0, शून्य) == -1)
		die("mounting tmpfs to /lib/firmware failed\n");

	sys_path = argv[1];
	aप्र_लिखो(&fw_path, "/lib/firmware/%s", fw_name);

	setup_fw(fw_path);

	रखो_भबफ(मानक_निकास, शून्य, _IONBF, 0);
	/* Positive हाल: firmware in PID1 mount namespace */
	म_लिखो("Testing with firmware in parent namespace (assumed to be same file system as PID1)\n");
	अगर (!test_fw_in_ns(fw_name, sys_path, false))
		die("error: failed to access firmware\n");

	/* Negative हाल: firmware in child mount namespace, expected to fail */
	म_लिखो("Testing with firmware in child namespace\n");
	अगर (test_fw_in_ns(fw_name, sys_path, true))
		die("error: firmware access did not fail\n");

	unlink(fw_path);
	मुक्त(fw_path);
	umount("/lib/firmware");
	निकास(निकास_सफल);
पूर्ण
