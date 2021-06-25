<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा _GNU_SOURCE
#समावेश <मानकपन.स>
#समावेश <त्रुटिसं.स>
#समावेश <pwd.h>
#समावेश <माला.स>
#समावेश <syscall.h>
#समावेश <sys/capability.h>
#समावेश <sys/types.h>
#समावेश <sys/mount.h>
#समावेश <sys/prctl.h>
#समावेश <sys/रुको.h>
#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <fcntl.h>
#समावेश <stdbool.h>
#समावेश <मानकतर्क.स>

#अगर_अघोषित CLONE_NEWUSER
# define CLONE_NEWUSER 0x10000000
#पूर्ण_अगर

#घोषणा ROOT_USER 0
#घोषणा RESTRICTED_PARENT 1
#घोषणा ALLOWED_CHILD1 2
#घोषणा ALLOWED_CHILD2 3
#घोषणा NO_POLICY_USER 4

अक्षर* add_whitelist_policy_file = "/sys/kernel/security/safesetid/add_whitelist_policy";

अटल व्योम die(अक्षर *fmt, ...)
अणु
	बहु_सूची ap;
	बहु_शुरू(ap, fmt);
	भख_लिखो(मानक_त्रुटि, fmt, ap);
	बहु_पूर्ण(ap);
	निकास(निकास_त्रुटि);
पूर्ण

अटल bool vmaybe_ग_लिखो_file(bool enoent_ok, अक्षर *filename, अक्षर *fmt, बहु_सूची ap)
अणु
	अक्षर buf[4096];
	पूर्णांक fd;
	sमाप_प्रकार written;
	पूर्णांक buf_len;

	buf_len = vsnम_लिखो(buf, माप(buf), fmt, ap);
	अगर (buf_len < 0) अणु
		म_लिखो("vsnprintf failed: %s\n",
		    म_त्रुटि(त्रुटि_सं));
		वापस false;
	पूर्ण
	अगर (buf_len >= माप(buf)) अणु
		म_लिखो("vsnprintf output truncated\n");
		वापस false;
	पूर्ण

	fd = खोलो(filename, O_WRONLY);
	अगर (fd < 0) अणु
		अगर ((त्रुटि_सं == ENOENT) && enoent_ok)
			वापस true;
		वापस false;
	पूर्ण
	written = ग_लिखो(fd, buf, buf_len);
	अगर (written != buf_len) अणु
		अगर (written >= 0) अणु
			म_लिखो("short write to %s\n", filename);
			वापस false;
		पूर्ण अन्यथा अणु
			म_लिखो("write to %s failed: %s\n",
				filename, म_त्रुटि(त्रुटि_सं));
			वापस false;
		पूर्ण
	पूर्ण
	अगर (बंद(fd) != 0) अणु
		म_लिखो("close of %s failed: %s\n",
			filename, म_त्रुटि(त्रुटि_सं));
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल bool ग_लिखो_file(अक्षर *filename, अक्षर *fmt, ...)
अणु
	बहु_सूची ap;
	bool ret;

	बहु_शुरू(ap, fmt);
	ret = vmaybe_ग_लिखो_file(false, filename, fmt, ap);
	बहु_पूर्ण(ap);

	वापस ret;
पूर्ण

अटल व्योम ensure_user_exists(uid_t uid)
अणु
	काष्ठा passwd p;

	खाता *fd;
	अक्षर name_str[10];

	अगर (getpwuid(uid) == शून्य) अणु
		स_रखो(&p,0x00,माप(p));
		fd=ख_खोलो("/etc/passwd","a");
		अगर (fd == शून्य)
			die("couldn't open file\n");
		अगर (ख_जाओ(fd, 0, अंत_से))
			die("couldn't fseek\n");
		snम_लिखो(name_str, 10, "%d", uid);
		p.pw_name=name_str;
		p.pw_uid=uid;
		p.pw_gecos="Test account";
		p.pw_dir="/dev/null";
		p.pw_shell="/bin/false";
		पूर्णांक value = putpwent(&p,fd);
		अगर (value != 0)
			die("putpwent failed\n");
		अगर (ख_बंद(fd))
			die("fclose failed\n");
	पूर्ण
पूर्ण

अटल व्योम ensure_securityfs_mounted(व्योम)
अणु
	पूर्णांक fd = खोलो(add_whitelist_policy_file, O_WRONLY);
	अगर (fd < 0) अणु
		अगर (त्रुटि_सं == ENOENT) अणु
			// Need to mount securityfs
			अगर (mount("securityfs", "/sys/kernel/security",
						"securityfs", 0, शून्य) < 0)
				die("mounting securityfs failed\n");
		पूर्ण अन्यथा अणु
			die("couldn't find securityfs for unknown reason\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (बंद(fd) != 0) अणु
			die("close of %s failed: %s\n",
				add_whitelist_policy_file, म_त्रुटि(त्रुटि_सं));
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम ग_लिखो_policies(व्योम)
अणु
	अटल अक्षर *policy_str =
		"1:2\n"
		"1:3\n"
		"2:2\n"
		"3:3\n";
	sमाप_प्रकार written;
	पूर्णांक fd;

	fd = खोलो(add_whitelist_policy_file, O_WRONLY);
	अगर (fd < 0)
		die("cant open add_whitelist_policy file\n");
	written = ग_लिखो(fd, policy_str, म_माप(policy_str));
	अगर (written != म_माप(policy_str)) अणु
		अगर (written >= 0) अणु
			die("short write to %s\n", add_whitelist_policy_file);
		पूर्ण अन्यथा अणु
			die("write to %s failed: %s\n",
				add_whitelist_policy_file, म_त्रुटि(त्रुटि_सं));
		पूर्ण
	पूर्ण
	अगर (बंद(fd) != 0) अणु
		die("close of %s failed: %s\n",
			add_whitelist_policy_file, म_त्रुटि(त्रुटि_सं));
	पूर्ण
पूर्ण

अटल bool test_userns(bool expect_success)
अणु
	uid_t uid;
	अक्षर map_file_name[32];
	माप_प्रकार sz = माप(map_file_name);
	pid_t cpid;
	bool success;

	uid = getuid();

	पूर्णांक clone_flags = CLONE_NEWUSER;
	cpid = syscall(SYS_clone, clone_flags, शून्य);
	अगर (cpid == -1) अणु
	    म_लिखो("clone failed");
	    वापस false;
	पूर्ण

	अगर (cpid == 0) अणु	/* Code executed by child */
		// Give parent 1 second to ग_लिखो map file
		sleep(1);
		निकास(निकास_सफल);
	पूर्ण अन्यथा अणु		/* Code executed by parent */
		अगर(snम_लिखो(map_file_name, sz, "/proc/%d/uid_map", cpid) < 0) अणु
			म_लिखो("preparing file name string failed");
			वापस false;
		पूर्ण
		success = ग_लिखो_file(map_file_name, "0 0 1", uid);
		वापस success == expect_success;
	पूर्ण

	म_लिखो("should not reach here");
	वापस false;
पूर्ण

अटल व्योम test_setuid(uid_t child_uid, bool expect_success)
अणु
	pid_t cpid, w;
	पूर्णांक wstatus;

	cpid = विभाजन();
	अगर (cpid == -1) अणु
		die("fork\n");
	पूर्ण

	अगर (cpid == 0) अणु	    /* Code executed by child */
		अगर (setuid(child_uid) < 0)
			निकास(निकास_त्रुटि);
		अगर (getuid() == child_uid)
			निकास(निकास_सफल);
		अन्यथा
			निकास(निकास_त्रुटि);
	पूर्ण अन्यथा अणु		 /* Code executed by parent */
		करो अणु
			w = रुकोpid(cpid, &wstatus, WUNTRACED | WCONTINUED);
			अगर (w == -1) अणु
				die("waitpid\n");
			पूर्ण

			अगर (WIFEXITED(wstatus)) अणु
				अगर (WEXITSTATUS(wstatus) == निकास_सफल) अणु
					अगर (expect_success) अणु
						वापस;
					पूर्ण अन्यथा अणु
						die("unexpected success\n");
					पूर्ण
				पूर्ण अन्यथा अणु
					अगर (expect_success) अणु
						die("unexpected failure\n");
					पूर्ण अन्यथा अणु
						वापस;
					पूर्ण
				पूर्ण
			पूर्ण अन्यथा अगर (WIFSIGNALED(wstatus)) अणु
				अगर (WTERMSIG(wstatus) == 9) अणु
					अगर (expect_success)
						die("killed unexpectedly\n");
					अन्यथा
						वापस;
				पूर्ण अन्यथा अणु
					die("unexpected signal: %d\n", wstatus);
				पूर्ण
			पूर्ण अन्यथा अणु
				die("unexpected status: %d\n", wstatus);
			पूर्ण
		पूर्ण जबतक (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));
	पूर्ण

	die("should not reach here\n");
पूर्ण

अटल व्योम ensure_users_exist(व्योम)
अणु
	ensure_user_exists(ROOT_USER);
	ensure_user_exists(RESTRICTED_PARENT);
	ensure_user_exists(ALLOWED_CHILD1);
	ensure_user_exists(ALLOWED_CHILD2);
	ensure_user_exists(NO_POLICY_USER);
पूर्ण

अटल व्योम drop_caps(bool setid_retained)
अणु
	cap_value_t cap_values[] = अणुCAP_SETUID, CAP_SETGIDपूर्ण;
	cap_t caps;

	caps = cap_get_proc();
	अगर (setid_retained)
		cap_set_flag(caps, CAP_EFFECTIVE, 2, cap_values, CAP_SET);
	अन्यथा
		cap_clear(caps);
	cap_set_proc(caps);
	cap_मुक्त(caps);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	ensure_users_exist();
	ensure_securityfs_mounted();
	ग_लिखो_policies();

	अगर (prctl(PR_SET_KEEPCAPS, 1L))
		die("Error with set keepcaps\n");

	// First test to make sure we can ग_लिखो userns mappings from a user
	// that करोesn't have any restrictions (as दीर्घ as it has CAP_SETUID);
	अगर (setuid(NO_POLICY_USER) < 0)
		die("Error with set uid(%d)\n", NO_POLICY_USER);
	अगर (setgid(NO_POLICY_USER) < 0)
		die("Error with set gid(%d)\n", NO_POLICY_USER);

	// Take away all but setid caps
	drop_caps(true);

	// Need PR_SET_DUMPABLE flag set so we can ग_लिखो /proc/[pid]/uid_map
	// from non-root parent process.
	अगर (prctl(PR_SET_DUMPABLE, 1, 0, 0, 0))
		die("Error with set dumpable\n");

	अगर (!test_userns(true)) अणु
		die("test_userns failed when it should work\n");
	पूर्ण

	अगर (setuid(RESTRICTED_PARENT) < 0)
		die("Error with set uid(%d)\n", RESTRICTED_PARENT);
	अगर (setgid(RESTRICTED_PARENT) < 0)
		die("Error with set gid(%d)\n", RESTRICTED_PARENT);

	test_setuid(ROOT_USER, false);
	test_setuid(ALLOWED_CHILD1, true);
	test_setuid(ALLOWED_CHILD2, true);
	test_setuid(NO_POLICY_USER, false);

	अगर (!test_userns(false)) अणु
		die("test_userns worked when it should fail\n");
	पूर्ण

	// Now take away all caps
	drop_caps(false);
	test_setuid(2, false);
	test_setuid(3, false);
	test_setuid(4, false);

	// NOTE: this test करोesn't clean up users that were created in
	// /etc/passwd or flush policies that were added to the LSM.
	वापस निकास_सफल;
पूर्ण
