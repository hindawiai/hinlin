<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा _GNU_SOURCE

#समावेश <cap-ng.h>
#समावेश <linux/capability.h>
#समावेश <stdbool.h>
#समावेश <माला.स>
#समावेश <मानकपन.स>
#समावेश <fcntl.h>
#समावेश <त्रुटिसं.स>
#समावेश <मानकतर्क.स>
#समावेश <sched.h>
#समावेश <sys/mount.h>
#समावेश <सीमा.स>
#समावेश <libgen.h>
#समावेश <दो_स्मृति.h>
#समावेश <sys/रुको.h>
#समावेश <sys/prctl.h>
#समावेश <sys/स्थिति.स>

#समावेश "../kselftest.h"

#अगर_अघोषित PR_CAP_AMBIENT
#घोषणा PR_CAP_AMBIENT			47
# define PR_CAP_AMBIENT_IS_SET		1
# define PR_CAP_AMBIENT_RAISE		2
# define PR_CAP_AMBIENT_LOWER		3
# define PR_CAP_AMBIENT_CLEAR_ALL	4
#पूर्ण_अगर

अटल पूर्णांक nerrs;
अटल pid_t mpid;	/*  मुख्य() pid is used to aव्योम duplicate test counts */

अटल व्योम vmaybe_ग_लिखो_file(bool enoent_ok, अक्षर *filename, अक्षर *fmt, बहु_सूची ap)
अणु
	अक्षर buf[4096];
	पूर्णांक fd;
	sमाप_प्रकार written;
	पूर्णांक buf_len;

	buf_len = vsnम_लिखो(buf, माप(buf), fmt, ap);
	अगर (buf_len < 0)
		ksft_निकास_fail_msg("vsnprintf failed - %s\n", म_त्रुटि(त्रुटि_सं));

	अगर (buf_len >= माप(buf))
		ksft_निकास_fail_msg("vsnprintf output truncated\n");


	fd = खोलो(filename, O_WRONLY);
	अगर (fd < 0) अणु
		अगर ((त्रुटि_सं == ENOENT) && enoent_ok)
			वापस;
		ksft_निकास_fail_msg("open of %s failed - %s\n",
					filename, म_त्रुटि(त्रुटि_सं));
	पूर्ण
	written = ग_लिखो(fd, buf, buf_len);
	अगर (written != buf_len) अणु
		अगर (written >= 0) अणु
			ksft_निकास_fail_msg("short write to %s\n", filename);
		पूर्ण अन्यथा अणु
			ksft_निकास_fail_msg("write to %s failed - %s\n",
						filename, म_त्रुटि(त्रुटि_सं));
		पूर्ण
	पूर्ण
	अगर (बंद(fd) != 0) अणु
		ksft_निकास_fail_msg("close of %s failed - %s\n",
					filename, म_त्रुटि(त्रुटि_सं));
	पूर्ण
पूर्ण

अटल व्योम maybe_ग_लिखो_file(अक्षर *filename, अक्षर *fmt, ...)
अणु
	बहु_सूची ap;

	बहु_शुरू(ap, fmt);
	vmaybe_ग_लिखो_file(true, filename, fmt, ap);
	बहु_पूर्ण(ap);
पूर्ण

अटल व्योम ग_लिखो_file(अक्षर *filename, अक्षर *fmt, ...)
अणु
	बहु_सूची ap;

	बहु_शुरू(ap, fmt);
	vmaybe_ग_लिखो_file(false, filename, fmt, ap);
	बहु_पूर्ण(ap);
पूर्ण

अटल bool create_and_enter_ns(uid_t inner_uid)
अणु
	uid_t outer_uid;
	gid_t outer_gid;
	पूर्णांक i;
	bool have_outer_privilege;

	outer_uid = getuid();
	outer_gid = getgid();

	/*
	 * TODO: If we're alपढ़ोy root, we could skip creating the userns.
	 */

	अगर (unshare(CLONE_NEWNS) == 0) अणु
		ksft_prपूर्णांक_msg("[NOTE]\tUsing global UIDs for tests\n");
		अगर (prctl(PR_SET_KEEPCAPS, 1, 0, 0, 0) != 0)
			ksft_निकास_fail_msg("PR_SET_KEEPCAPS - %s\n",
						म_त्रुटि(त्रुटि_सं));
		अगर (setresuid(inner_uid, inner_uid, -1) != 0)
			ksft_निकास_fail_msg("setresuid - %s\n", म_त्रुटि(त्रुटि_सं));

		// Re-enable effective caps
		capng_get_caps_process();
		क्रम (i = 0; i < CAP_LAST_CAP; i++)
			अगर (capng_have_capability(CAPNG_PERMITTED, i))
				capng_update(CAPNG_ADD, CAPNG_EFFECTIVE, i);
		अगर (capng_apply(CAPNG_SELECT_CAPS) != 0)
			ksft_निकास_fail_msg(
					"capng_apply - %s\n", म_त्रुटि(त्रुटि_सं));

		have_outer_privilege = true;
	पूर्ण अन्यथा अगर (unshare(CLONE_NEWUSER | CLONE_NEWNS) == 0) अणु
		ksft_prपूर्णांक_msg("[NOTE]\tUsing a user namespace for tests\n");
		maybe_ग_लिखो_file("/proc/self/setgroups", "deny");
		ग_लिखो_file("/proc/self/uid_map", "%d %d 1", inner_uid, outer_uid);
		ग_लिखो_file("/proc/self/gid_map", "0 %d 1", outer_gid);

		have_outer_privilege = false;
	पूर्ण अन्यथा अणु
		ksft_निकास_skip("must be root or be able to create a userns\n");
	पूर्ण

	अगर (mount("none", "/", शून्य, MS_REC | MS_PRIVATE, शून्य) != 0)
		ksft_निकास_fail_msg("remount everything private - %s\n",
					म_त्रुटि(त्रुटि_सं));

	वापस have_outer_privilege;
पूर्ण

अटल व्योम स_बदलो_to_पंचांगpfs(व्योम)
अणु
	अक्षर cwd[PATH_MAX];
	अगर (अ_लोwd(cwd, माप(cwd)) != cwd)
		ksft_निकास_fail_msg("getcwd - %s\n", म_त्रुटि(त्रुटि_सं));

	अगर (mount("private_tmp", ".", "tmpfs", 0, "mode=0777") != 0)
		ksft_निकास_fail_msg("mount private tmpfs - %s\n",
					म_त्रुटि(त्रुटि_सं));

	अगर (स_बदलो(cwd) != 0)
		ksft_निकास_fail_msg("chdir to private tmpfs - %s\n",
					म_त्रुटि(त्रुटि_सं));
पूर्ण

अटल व्योम copy_fromat_to(पूर्णांक fromfd, स्थिर अक्षर *fromname, स्थिर अक्षर *toname)
अणु
	पूर्णांक from = खोलोat(fromfd, fromname, O_RDONLY);
	अगर (from == -1)
		ksft_निकास_fail_msg("open copy source - %s\n", म_त्रुटि(त्रुटि_सं));

	पूर्णांक to = खोलो(toname, O_CREAT | O_WRONLY | O_EXCL, 0700);

	जबतक (true) अणु
		अक्षर buf[4096];
		sमाप_प्रकार sz = पढ़ो(from, buf, माप(buf));
		अगर (sz == 0)
			अवरोध;
		अगर (sz < 0)
			ksft_निकास_fail_msg("read - %s\n", म_त्रुटि(त्रुटि_सं));

		अगर (ग_लिखो(to, buf, sz) != sz)
			/* no लघु ग_लिखोs on पंचांगpfs */
			ksft_निकास_fail_msg("write - %s\n", म_त्रुटि(त्रुटि_सं));
	पूर्ण

	बंद(from);
	बंद(to);
पूर्ण

अटल bool विभाजन_रुको(व्योम)
अणु
	pid_t child = विभाजन();
	अगर (child == 0) अणु
		nerrs = 0;
		वापस true;
	पूर्ण अन्यथा अगर (child > 0) अणु
		पूर्णांक status;
		अगर (रुकोpid(child, &status, 0) != child ||
		    !WIFEXITED(status)) अणु
			ksft_prपूर्णांक_msg("Child died\n");
			nerrs++;
		पूर्ण अन्यथा अगर (WEXITSTATUS(status) != 0) अणु
			ksft_prपूर्णांक_msg("Child failed\n");
			nerrs++;
		पूर्ण अन्यथा अणु
			/* करोn't prपूर्णांक this message क्रम mpid */
			अगर (getpid() != mpid)
				ksft_test_result_pass("Passed\n");
		पूर्ण
		वापस false;
	पूर्ण अन्यथा अणु
		ksft_निकास_fail_msg("fork - %s\n", म_त्रुटि(त्रुटि_सं));
		वापस false;
	पूर्ण
पूर्ण

अटल व्योम exec_other_validate_cap(स्थिर अक्षर *name,
				    bool eff, bool perm, bool inh, bool ambient)
अणु
	execl(name, name, (eff ? "1" : "0"),
	      (perm ? "1" : "0"), (inh ? "1" : "0"), (ambient ? "1" : "0"),
	      शून्य);
	ksft_निकास_fail_msg("execl - %s\n", म_त्रुटि(त्रुटि_सं));
पूर्ण

अटल व्योम exec_validate_cap(bool eff, bool perm, bool inh, bool ambient)
अणु
	exec_other_validate_cap("./validate_cap", eff, perm, inh, ambient);
पूर्ण

अटल पूर्णांक करो_tests(पूर्णांक uid, स्थिर अक्षर *our_path)
अणु
	bool have_outer_privilege = create_and_enter_ns(uid);

	पूर्णांक ourpath_fd = खोलो(our_path, O_RDONLY | O_सूचीECTORY);
	अगर (ourpath_fd == -1)
		ksft_निकास_fail_msg("open '%s' - %s\n",
					our_path, म_त्रुटि(त्रुटि_सं));

	स_बदलो_to_पंचांगpfs();

	copy_fromat_to(ourpath_fd, "validate_cap", "validate_cap");

	अगर (have_outer_privilege) अणु
		uid_t gid = getegid();

		copy_fromat_to(ourpath_fd, "validate_cap",
			       "validate_cap_suidroot");
		अगर (chown("validate_cap_suidroot", 0, -1) != 0)
			ksft_निकास_fail_msg("chown - %s\n", म_त्रुटि(त्रुटि_सं));
		अगर (chmod("validate_cap_suidroot", S_ISUID | 0700) != 0)
			ksft_निकास_fail_msg("chmod - %s\n", म_त्रुटि(त्रुटि_सं));

		copy_fromat_to(ourpath_fd, "validate_cap",
			       "validate_cap_suidnonroot");
		अगर (chown("validate_cap_suidnonroot", uid + 1, -1) != 0)
			ksft_निकास_fail_msg("chown - %s\n", म_त्रुटि(त्रुटि_सं));
		अगर (chmod("validate_cap_suidnonroot", S_ISUID | 0700) != 0)
			ksft_निकास_fail_msg("chmod - %s\n", म_त्रुटि(त्रुटि_सं));

		copy_fromat_to(ourpath_fd, "validate_cap",
			       "validate_cap_sgidroot");
		अगर (chown("validate_cap_sgidroot", -1, 0) != 0)
			ksft_निकास_fail_msg("chown - %s\n", म_त्रुटि(त्रुटि_सं));
		अगर (chmod("validate_cap_sgidroot", S_ISGID | 0710) != 0)
			ksft_निकास_fail_msg("chmod - %s\n", म_त्रुटि(त्रुटि_सं));

		copy_fromat_to(ourpath_fd, "validate_cap",
			       "validate_cap_sgidnonroot");
		अगर (chown("validate_cap_sgidnonroot", -1, gid + 1) != 0)
			ksft_निकास_fail_msg("chown - %s\n", म_त्रुटि(त्रुटि_सं));
		अगर (chmod("validate_cap_sgidnonroot", S_ISGID | 0710) != 0)
			ksft_निकास_fail_msg("chmod - %s\n", म_त्रुटि(त्रुटि_सं));
	पूर्ण

	capng_get_caps_process();

	/* Make sure that i starts out clear */
	capng_update(CAPNG_DROP, CAPNG_INHERITABLE, CAP_NET_BIND_SERVICE);
	अगर (capng_apply(CAPNG_SELECT_CAPS) != 0)
		ksft_निकास_fail_msg("capng_apply - %s\n", म_त्रुटि(त्रुटि_सं));

	अगर (uid == 0) अणु
		ksft_prपूर्णांक_msg("[RUN]\tRoot => ep\n");
		अगर (विभाजन_रुको())
			exec_validate_cap(true, true, false, false);
	पूर्ण अन्यथा अणु
		ksft_prपूर्णांक_msg("[RUN]\tNon-root => no caps\n");
		अगर (विभाजन_रुको())
			exec_validate_cap(false, false, false, false);
	पूर्ण

	ksft_prपूर्णांक_msg("Check cap_ambient manipulation rules\n");

	/* We should not be able to add ambient caps yet. */
	अगर (prctl(PR_CAP_AMBIENT, PR_CAP_AMBIENT_RAISE, CAP_NET_BIND_SERVICE, 0, 0, 0) != -1 || त्रुटि_सं != EPERM) अणु
		अगर (त्रुटि_सं == EINVAL)
			ksft_test_result_fail(
				"PR_CAP_AMBIENT_RAISE isn't supported\n");
		अन्यथा
			ksft_test_result_fail(
				"PR_CAP_AMBIENT_RAISE should have failed eith EPERM on a non-inheritable cap\n");
		वापस 1;
	पूर्ण
	ksft_test_result_pass(
		"PR_CAP_AMBIENT_RAISE failed on non-inheritable cap\n");

	capng_update(CAPNG_ADD, CAPNG_INHERITABLE, CAP_NET_RAW);
	capng_update(CAPNG_DROP, CAPNG_PERMITTED, CAP_NET_RAW);
	capng_update(CAPNG_DROP, CAPNG_EFFECTIVE, CAP_NET_RAW);
	अगर (capng_apply(CAPNG_SELECT_CAPS) != 0)
		ksft_निकास_fail_msg("capng_apply - %s\n", म_त्रुटि(त्रुटि_सं));
	अगर (prctl(PR_CAP_AMBIENT, PR_CAP_AMBIENT_RAISE, CAP_NET_RAW, 0, 0, 0) != -1 || त्रुटि_सं != EPERM) अणु
		ksft_test_result_fail(
			"PR_CAP_AMBIENT_RAISE should have failed on a non-permitted cap\n");
		वापस 1;
	पूर्ण
	ksft_test_result_pass(
		"PR_CAP_AMBIENT_RAISE failed on non-permitted cap\n");

	capng_update(CAPNG_ADD, CAPNG_INHERITABLE, CAP_NET_BIND_SERVICE);
	अगर (capng_apply(CAPNG_SELECT_CAPS) != 0)
		ksft_निकास_fail_msg("capng_apply - %s\n", म_त्रुटि(त्रुटि_सं));
	अगर (prctl(PR_CAP_AMBIENT, PR_CAP_AMBIENT_RAISE, CAP_NET_BIND_SERVICE, 0, 0, 0) != 0) अणु
		ksft_test_result_fail(
			"PR_CAP_AMBIENT_RAISE should have succeeded\n");
		वापस 1;
	पूर्ण
	ksft_test_result_pass("PR_CAP_AMBIENT_RAISE worked\n");

	अगर (prctl(PR_CAP_AMBIENT, PR_CAP_AMBIENT_IS_SET, CAP_NET_BIND_SERVICE, 0, 0, 0) != 1) अणु
		ksft_test_result_fail("PR_CAP_AMBIENT_IS_SET is broken\n");
		वापस 1;
	पूर्ण

	अगर (prctl(PR_CAP_AMBIENT, PR_CAP_AMBIENT_CLEAR_ALL, 0, 0, 0, 0) != 0)
		ksft_निकास_fail_msg("PR_CAP_AMBIENT_CLEAR_ALL - %s\n",
					म_त्रुटि(त्रुटि_सं));

	अगर (prctl(PR_CAP_AMBIENT, PR_CAP_AMBIENT_IS_SET, CAP_NET_BIND_SERVICE, 0, 0, 0) != 0) अणु
		ksft_test_result_fail(
			"PR_CAP_AMBIENT_CLEAR_ALL didn't work\n");
		वापस 1;
	पूर्ण

	अगर (prctl(PR_CAP_AMBIENT, PR_CAP_AMBIENT_RAISE, CAP_NET_BIND_SERVICE, 0, 0, 0) != 0)
		ksft_निकास_fail_msg("PR_CAP_AMBIENT_RAISE - %s\n",
					म_त्रुटि(त्रुटि_सं));

	capng_update(CAPNG_DROP, CAPNG_INHERITABLE, CAP_NET_BIND_SERVICE);
	अगर (capng_apply(CAPNG_SELECT_CAPS) != 0)
		ksft_निकास_fail_msg("capng_apply - %s\n", म_त्रुटि(त्रुटि_सं));

	अगर (prctl(PR_CAP_AMBIENT, PR_CAP_AMBIENT_IS_SET, CAP_NET_BIND_SERVICE, 0, 0, 0) != 0) अणु
		ksft_test_result_fail("Dropping I should have dropped A\n");
		वापस 1;
	पूर्ण

	ksft_test_result_pass("Basic manipulation appears to work\n");

	capng_update(CAPNG_ADD, CAPNG_INHERITABLE, CAP_NET_BIND_SERVICE);
	अगर (capng_apply(CAPNG_SELECT_CAPS) != 0)
		ksft_निकास_fail_msg("capng_apply - %s\n", म_त्रुटि(त्रुटि_सं));
	अगर (uid == 0) अणु
		ksft_prपूर्णांक_msg("[RUN]\tRoot +i => eip\n");
		अगर (विभाजन_रुको())
			exec_validate_cap(true, true, true, false);
	पूर्ण अन्यथा अणु
		ksft_prपूर्णांक_msg("[RUN]\tNon-root +i => i\n");
		अगर (विभाजन_रुको())
			exec_validate_cap(false, false, true, false);
	पूर्ण

	अगर (prctl(PR_CAP_AMBIENT, PR_CAP_AMBIENT_RAISE, CAP_NET_BIND_SERVICE, 0, 0, 0) != 0)
		ksft_निकास_fail_msg("PR_CAP_AMBIENT_RAISE - %s\n",
					म_त्रुटि(त्रुटि_सं));

	ksft_prपूर्णांक_msg("[RUN]\tUID %d +ia => eipa\n", uid);
	अगर (विभाजन_रुको())
		exec_validate_cap(true, true, true, true);

	/* The reमुख्यing tests need real privilege */

	अगर (!have_outer_privilege) अणु
		ksft_test_result_skip("SUID/SGID tests (needs privilege)\n");
		जाओ करोne;
	पूर्ण

	अगर (uid == 0) अणु
		ksft_prपूर्णांक_msg("[RUN]\tRoot +ia, suidroot => eipa\n");
		अगर (विभाजन_रुको())
			exec_other_validate_cap("./validate_cap_suidroot",
						true, true, true, true);

		ksft_prपूर्णांक_msg("[RUN]\tRoot +ia, suidnonroot => ip\n");
		अगर (विभाजन_रुको())
			exec_other_validate_cap("./validate_cap_suidnonroot",
						false, true, true, false);

		ksft_prपूर्णांक_msg("[RUN]\tRoot +ia, sgidroot => eipa\n");
		अगर (विभाजन_रुको())
			exec_other_validate_cap("./validate_cap_sgidroot",
						true, true, true, true);

		अगर (विभाजन_रुको()) अणु
			ksft_prपूर्णांक_msg(
				"[RUN]\tRoot, gid != 0, +ia, sgidroot => eip\n");
			अगर (setresgid(1, 1, 1) != 0)
				ksft_निकास_fail_msg("setresgid - %s\n",
							म_त्रुटि(त्रुटि_सं));
			exec_other_validate_cap("./validate_cap_sgidroot",
						true, true, true, false);
		पूर्ण

		ksft_prपूर्णांक_msg("[RUN]\tRoot +ia, sgidnonroot => eip\n");
		अगर (विभाजन_रुको())
			exec_other_validate_cap("./validate_cap_sgidnonroot",
						true, true, true, false);
	पूर्ण अन्यथा अणु
		ksft_prपूर्णांक_msg("[RUN]\tNon-root +ia, sgidnonroot => i\n");
		अगर (विभाजन_रुको())
			exec_other_validate_cap("./validate_cap_sgidnonroot",
					false, false, true, false);

		अगर (विभाजन_रुको()) अणु
			ksft_prपूर्णांक_msg("[RUN]\tNon-root +ia, sgidroot => i\n");
			अगर (setresgid(1, 1, 1) != 0)
				ksft_निकास_fail_msg("setresgid - %s\n",
							म_त्रुटि(त्रुटि_सं));
			exec_other_validate_cap("./validate_cap_sgidroot",
						false, false, true, false);
		पूर्ण
	पूर्ण

करोne:
	ksft_prपूर्णांक_cnts();
	वापस nerrs ? 1 : 0;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	अक्षर *पंचांगp1, *पंचांगp2, *our_path;

	/* Find our path */
	पंचांगp1 = strdup(argv[0]);
	अगर (!पंचांगp1)
		ksft_निकास_fail_msg("strdup - %s\n", म_त्रुटि(त्रुटि_सं));
	पंचांगp2 = स_नाम(पंचांगp1);
	our_path = strdup(पंचांगp2);
	अगर (!our_path)
		ksft_निकास_fail_msg("strdup - %s\n", म_त्रुटि(त्रुटि_सं));
	मुक्त(पंचांगp1);

	mpid = getpid();

	अगर (विभाजन_रुको()) अणु
		ksft_prपूर्णांक_header();
		ksft_set_plan(12);
		ksft_prपूर्णांक_msg("[RUN]\t+++ Tests with uid == 0 +++\n");
		वापस करो_tests(0, our_path);
	पूर्ण

	ksft_prपूर्णांक_msg("==================================================\n");

	अगर (विभाजन_रुको()) अणु
		ksft_prपूर्णांक_header();
		ksft_set_plan(9);
		ksft_prपूर्णांक_msg("[RUN]\t+++ Tests with uid != 0 +++\n");
		वापस करो_tests(1, our_path);
	पूर्ण

	वापस nerrs ? 1 : 0;
पूर्ण
