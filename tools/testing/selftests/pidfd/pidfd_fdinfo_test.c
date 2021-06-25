<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#घोषणा _GNU_SOURCE
#समावेश <निश्चित.स>
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <linux/types.h>
#समावेश <sched.h>
#समावेश <संकेत.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <syscall.h>
#समावेश <sys/रुको.h>

#समावेश "pidfd.h"
#समावेश "../kselftest.h"

काष्ठा error अणु
	पूर्णांक  code;
	अक्षर msg[512];
पूर्ण;

अटल पूर्णांक error_set(काष्ठा error *err, पूर्णांक code, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	पूर्णांक r;

	अगर (code == PIDFD_PASS || !err || err->code != PIDFD_PASS)
		वापस code;

	err->code = code;
	बहु_शुरू(args, fmt);
	r = vsnम_लिखो(err->msg, माप(err->msg), fmt, args);
	निश्चित((माप_प्रकार)r < माप(err->msg));
	बहु_पूर्ण(args);

	वापस code;
पूर्ण

अटल व्योम error_report(काष्ठा error *err, स्थिर अक्षर *test_name)
अणु
	चयन (err->code) अणु
	हाल PIDFD_ERROR:
		ksft_निकास_fail_msg("%s test: Fatal: %s\n", test_name, err->msg);
		अवरोध;

	हाल PIDFD_FAIL:
		/* will be: not ok %d # error %s test: %s */
		ksft_test_result_error("%s test: %s\n", test_name, err->msg);
		अवरोध;

	हाल PIDFD_SKIP:
		/* will be: not ok %d # SKIP %s test: %s */
		ksft_test_result_skip("%s test: %s\n", test_name, err->msg);
		अवरोध;

	हाल PIDFD_XFAIL:
		ksft_test_result_pass("%s test: Expected failure: %s\n",
				      test_name, err->msg);
		अवरोध;

	हाल PIDFD_PASS:
		ksft_test_result_pass("%s test: Passed\n");
		अवरोध;

	शेष:
		ksft_निकास_fail_msg("%s test: Unknown code: %d %s\n",
				   test_name, err->code, err->msg);
		अवरोध;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक error_check(काष्ठा error *err, स्थिर अक्षर *test_name)
अणु
	/* In हाल of error we bail out and terminate the test program */
	अगर (err->code == PIDFD_ERROR)
		error_report(err, test_name);

	वापस err->code;
पूर्ण

काष्ठा child अणु
	pid_t pid;
	पूर्णांक   fd;
पूर्ण;

अटल काष्ठा child clone_newns(पूर्णांक (*fn)(व्योम *), व्योम *args,
				काष्ठा error *err)
अणु
	अटल पूर्णांक flags = CLONE_PIDFD | CLONE_NEWPID | CLONE_NEWNS | SIGCHLD;
	माप_प्रकार stack_size = 1024;
	अक्षर *stack[1024] = अणु 0 पूर्ण;
	काष्ठा child ret;

	अगर (!(flags & CLONE_NEWUSER) && geteuid() != 0)
		flags |= CLONE_NEWUSER;

#अगर_घोषित __ia64__
	ret.pid = __clone2(fn, stack, stack_size, flags, args, &ret.fd);
#अन्यथा
	ret.pid = clone(fn, stack + stack_size, flags, args, &ret.fd);
#पूर्ण_अगर

	अगर (ret.pid < 0) अणु
		error_set(err, PIDFD_ERROR, "clone failed (ret %d, errno %d)",
			  ret.fd, त्रुटि_सं);
		वापस ret;
	पूर्ण

	ksft_prपूर्णांक_msg("New child: %d, fd: %d\n", ret.pid, ret.fd);

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम child_बंद(काष्ठा child *child)
अणु
	बंद(child->fd);
पूर्ण

अटल अंतरभूत पूर्णांक child_join(काष्ठा child *child, काष्ठा error *err)
अणु
	पूर्णांक r;

	r = रुको_क्रम_pid(child->pid);
	अगर (r < 0)
		error_set(err, PIDFD_ERROR, "waitpid failed (ret %d, errno %d)",
			  r, त्रुटि_सं);
	अन्यथा अगर (r > 0)
		error_set(err, r, "child %d reported: %d", child->pid, r);

	वापस r;
पूर्ण

अटल अंतरभूत पूर्णांक child_join_बंद(काष्ठा child *child, काष्ठा error *err)
अणु
	child_बंद(child);
	वापस child_join(child, err);
पूर्ण

अटल अंतरभूत व्योम trim_newline(अक्षर *str)
अणु
	अक्षर *pos = म_खोजप(str, '\n');

	अगर (pos)
		*pos = '\0';
पूर्ण

अटल पूर्णांक verअगरy_fdinfo(पूर्णांक pidfd, काष्ठा error *err, स्थिर अक्षर *prefix,
			 माप_प्रकार prefix_len, स्थिर अक्षर *expect, ...)
अणु
	अक्षर buffer[512] = अणु0, पूर्ण;
	अक्षर path[512] = अणु0, पूर्ण;
	बहु_सूची args;
	खाता *f;
	अक्षर *line = शून्य;
	माप_प्रकार n = 0;
	पूर्णांक found = 0;
	पूर्णांक r;

	बहु_शुरू(args, expect);
	r = vsnम_लिखो(buffer, माप(buffer), expect, args);
	निश्चित((माप_प्रकार)r < माप(buffer));
	बहु_पूर्ण(args);

	snम_लिखो(path, माप(path), "/proc/self/fdinfo/%d", pidfd);
	f = ख_खोलो(path, "re");
	अगर (!f)
		वापस error_set(err, PIDFD_ERROR, "fdinfo open failed for %d",
				 pidfd);

	जबतक (getline(&line, &n, f) != -1) अणु
		अक्षर *val;

		अगर (म_भेदन(line, prefix, prefix_len))
			जारी;

		found = 1;

		val = line + prefix_len;
		r = म_भेद(val, buffer);
		अगर (r != 0) अणु
			trim_newline(line);
			trim_newline(buffer);
			error_set(err, PIDFD_FAIL, "%s '%s' != '%s'",
				  prefix, val, buffer);
		पूर्ण
		अवरोध;
	पूर्ण

	मुक्त(line);
	ख_बंद(f);

	अगर (found == 0)
		वापस error_set(err, PIDFD_FAIL, "%s not found for fd %d",
				 prefix, pidfd);

	वापस PIDFD_PASS;
पूर्ण

अटल पूर्णांक child_fdinfo_nspid_test(व्योम *args)
अणु
	काष्ठा error err;
	पूर्णांक pidfd;
	पूर्णांक r;

	/* अगर we got no fd क्रम the sibling, we are करोne */
	अगर (!args)
		वापस PIDFD_PASS;

	/* verअगरy that we can not resolve the pidfd क्रम a process
	 * in a sibling pid namespace, i.e. a pid namespace it is
	 * not in our or a descended namespace
	 */
	r = mount(शून्य, "/", शून्य, MS_REC | MS_PRIVATE, 0);
	अगर (r < 0) अणु
		ksft_prपूर्णांक_msg("Failed to remount / private\n");
		वापस PIDFD_ERROR;
	पूर्ण

	(व्योम)umount2("/proc", MNT_DETACH);
	r = mount("proc", "/proc", "proc", 0, शून्य);
	अगर (r < 0) अणु
		ksft_prपूर्णांक_msg("Failed to remount /proc\n");
		वापस PIDFD_ERROR;
	पूर्ण

	pidfd = *(पूर्णांक *)args;
	r = verअगरy_fdinfo(pidfd, &err, "NSpid:", 6, "\t0\n");

	अगर (r != PIDFD_PASS)
		ksft_prपूर्णांक_msg("NSpid fdinfo check failed: %s\n", err.msg);

	वापस r;
पूर्ण

अटल व्योम test_pidfd_fdinfo_nspid(व्योम)
अणु
	काष्ठा child a, b;
	काष्ठा error err = अणु0, पूर्ण;
	स्थिर अक्षर *test_name = "pidfd check for NSpid in fdinfo";

	/* Create a new child in a new pid and mount namespace */
	a = clone_newns(child_fdinfo_nspid_test, शून्य, &err);
	error_check(&err, test_name);

	/* Pass the pidfd representing the first child to the
	 * second child, which will be in a sibling pid namespace,
	 * which means that the fdinfo NSpid entry क्रम the pidfd
	 * should only contain '0'.
	 */
	b = clone_newns(child_fdinfo_nspid_test, &a.fd, &err);
	error_check(&err, test_name);

	/* The children will have pid 1 in the new pid namespace,
	 * so the line must be 'NSPid:\t<pid>\t1'.
	 */
	verअगरy_fdinfo(a.fd, &err, "NSpid:", 6, "\t%d\t%d\n", a.pid, 1);
	verअगरy_fdinfo(b.fd, &err, "NSpid:", 6, "\t%d\t%d\n", b.pid, 1);

	/* रुको क्रम the process, check the निकास status and set
	 * 'err' accordingly, अगर it is not alपढ़ोy set.
	 */
	child_join_बंद(&a, &err);
	child_join_बंद(&b, &err);

	error_report(&err, test_name);
पूर्ण

अटल व्योम test_pidfd_dead_fdinfo(व्योम)
अणु
	काष्ठा child a;
	काष्ठा error err = अणु0, पूर्ण;
	स्थिर अक्षर *test_name = "pidfd check fdinfo for dead process";

	/* Create a new child in a new pid and mount namespace */
	a = clone_newns(child_fdinfo_nspid_test, शून्य, &err);
	error_check(&err, test_name);
	child_join(&a, &err);

	verअगरy_fdinfo(a.fd, &err, "Pid:", 4, "\t-1\n");
	verअगरy_fdinfo(a.fd, &err, "NSpid:", 6, "\t-1\n");
	child_बंद(&a);
	error_report(&err, test_name);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	ksft_prपूर्णांक_header();
	ksft_set_plan(2);

	test_pidfd_fdinfo_nspid();
	test_pidfd_dead_fdinfo();

	वापस ksft_निकास_pass();
पूर्ण
