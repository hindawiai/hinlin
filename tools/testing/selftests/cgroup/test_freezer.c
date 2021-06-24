<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <stdbool.h>
#समावेश <linux/सीमा.स>
#समावेश <sys/ptrace.h>
#समावेश <sys/types.h>
#समावेश <sys/mman.h>
#समावेश <unistd.h>
#समावेश <मानकपन.स>
#समावेश <त्रुटिसं.स>
#समावेश <poll.h>
#समावेश <मानककोष.स>
#समावेश <sys/inotअगरy.h>
#समावेश <माला.स>
#समावेश <sys/रुको.h>

#समावेश "../kselftest.h"
#समावेश "cgroup_util.h"

#घोषणा DEBUG
#अगर_घोषित DEBUG
#घोषणा debug(args...) ख_लिखो(मानक_त्रुटि, args)
#अन्यथा
#घोषणा debug(args...)
#पूर्ण_अगर

/*
 * Check अगर the cgroup is frozen by looking at the cgroup.events::frozen value.
 */
अटल पूर्णांक cg_check_frozen(स्थिर अक्षर *cgroup, bool frozen)
अणु
	अगर (frozen) अणु
		अगर (cg_पढ़ो_म_माला(cgroup, "cgroup.events", "frozen 1") != 0) अणु
			debug("Cgroup %s isn't frozen\n", cgroup);
			वापस -1;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * Check the cgroup.events::frozen value.
		 */
		अगर (cg_पढ़ो_म_माला(cgroup, "cgroup.events", "frozen 0") != 0) अणु
			debug("Cgroup %s is frozen\n", cgroup);
			वापस -1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Freeze the given cgroup.
 */
अटल पूर्णांक cg_मुक्तze_noरुको(स्थिर अक्षर *cgroup, bool मुक्तze)
अणु
	वापस cg_ग_लिखो(cgroup, "cgroup.freeze", मुक्तze ? "1" : "0");
पूर्ण

/*
 * Prepare क्रम रुकोing on cgroup.events file.
 */
अटल पूर्णांक cg_prepare_क्रम_रुको(स्थिर अक्षर *cgroup)
अणु
	पूर्णांक fd, ret = -1;

	fd = inotअगरy_init1(0);
	अगर (fd == -1) अणु
		debug("Error: inotify_init1() failed\n");
		वापस fd;
	पूर्ण

	ret = inotअगरy_add_watch(fd, cg_control(cgroup, "cgroup.events"),
				IN_MODIFY);
	अगर (ret == -1) अणु
		debug("Error: inotify_add_watch() failed\n");
		बंद(fd);
		fd = -1;
	पूर्ण

	वापस fd;
पूर्ण

/*
 * Wait क्रम an event. If there are no events क्रम 10 seconds,
 * treat this an error.
 */
अटल पूर्णांक cg_रुको_क्रम(पूर्णांक fd)
अणु
	पूर्णांक ret = -1;
	काष्ठा pollfd fds = अणु
		.fd = fd,
		.events = POLLIN,
	पूर्ण;

	जबतक (true) अणु
		ret = poll(&fds, 1, 10000);

		अगर (ret == -1) अणु
			अगर (त्रुटि_सं == EINTR)
				जारी;
			debug("Error: poll() failed\n");
			अवरोध;
		पूर्ण

		अगर (ret > 0 && fds.revents & POLLIN) अणु
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Attach a task to the given cgroup and रुको क्रम a cgroup frozen event.
 * All transient events (e.g. populated) are ignored.
 */
अटल पूर्णांक cg_enter_and_रुको_क्रम_frozen(स्थिर अक्षर *cgroup, पूर्णांक pid,
					bool frozen)
अणु
	पूर्णांक fd, ret = -1;
	पूर्णांक attempts;

	fd = cg_prepare_क्रम_रुको(cgroup);
	अगर (fd < 0)
		वापस fd;

	ret = cg_enter(cgroup, pid);
	अगर (ret)
		जाओ out;

	क्रम (attempts = 0; attempts < 10; attempts++) अणु
		ret = cg_रुको_क्रम(fd);
		अगर (ret)
			अवरोध;

		ret = cg_check_frozen(cgroup, frozen);
		अगर (ret)
			जारी;
	पूर्ण

out:
	बंद(fd);
	वापस ret;
पूर्ण

/*
 * Freeze the given cgroup and रुको क्रम the inotअगरy संकेत.
 * If there are no events in 10 seconds, treat this as an error.
 * Then check that the cgroup is in the desired state.
 */
अटल पूर्णांक cg_मुक्तze_रुको(स्थिर अक्षर *cgroup, bool मुक्तze)
अणु
	पूर्णांक fd, ret = -1;

	fd = cg_prepare_क्रम_रुको(cgroup);
	अगर (fd < 0)
		वापस fd;

	ret = cg_मुक्तze_noरुको(cgroup, मुक्तze);
	अगर (ret) अणु
		debug("Error: cg_freeze_nowait() failed\n");
		जाओ out;
	पूर्ण

	ret = cg_रुको_क्रम(fd);
	अगर (ret)
		जाओ out;

	ret = cg_check_frozen(cgroup, मुक्तze);
out:
	बंद(fd);
	वापस ret;
पूर्ण

/*
 * A simple process running in a sleep loop until being
 * re-parented.
 */
अटल पूर्णांक child_fn(स्थिर अक्षर *cgroup, व्योम *arg)
अणु
	पूर्णांक ppid = getppid();

	जबतक (getppid() == ppid)
		usleep(1000);

	वापस getppid() == ppid;
पूर्ण

/*
 * A simple test क्रम the cgroup मुक्तzer: populated the cgroup with 100
 * running processes and मुक्तze it. Then unमुक्तze it. Then it समाप्तs all
 * processes and destroys the cgroup.
 */
अटल पूर्णांक test_cgमुक्तzer_simple(स्थिर अक्षर *root)
अणु
	पूर्णांक ret = KSFT_FAIL;
	अक्षर *cgroup = शून्य;
	पूर्णांक i;

	cgroup = cg_name(root, "cg_test_simple");
	अगर (!cgroup)
		जाओ cleanup;

	अगर (cg_create(cgroup))
		जाओ cleanup;

	क्रम (i = 0; i < 100; i++)
		cg_run_noरुको(cgroup, child_fn, शून्य);

	अगर (cg_रुको_क्रम_proc_count(cgroup, 100))
		जाओ cleanup;

	अगर (cg_check_frozen(cgroup, false))
		जाओ cleanup;

	अगर (cg_मुक्तze_रुको(cgroup, true))
		जाओ cleanup;

	अगर (cg_मुक्तze_रुको(cgroup, false))
		जाओ cleanup;

	ret = KSFT_PASS;

cleanup:
	अगर (cgroup)
		cg_destroy(cgroup);
	मुक्त(cgroup);
	वापस ret;
पूर्ण

/*
 * The test creates the following hierarchy:
 *       A
 *    / / \ \
 *   B  E  I K
 *  /\  |
 * C  D F
 *      |
 *      G
 *      |
 *      H
 *
 * with a process in C, H and 3 processes in K.
 * Then it tries to मुक्तze and unमुक्तze the whole tree.
 */
अटल पूर्णांक test_cgमुक्तzer_tree(स्थिर अक्षर *root)
अणु
	अक्षर *cgroup[10] = अणु0पूर्ण;
	पूर्णांक ret = KSFT_FAIL;
	पूर्णांक i;

	cgroup[0] = cg_name(root, "cg_test_tree_A");
	अगर (!cgroup[0])
		जाओ cleanup;

	cgroup[1] = cg_name(cgroup[0], "B");
	अगर (!cgroup[1])
		जाओ cleanup;

	cgroup[2] = cg_name(cgroup[1], "C");
	अगर (!cgroup[2])
		जाओ cleanup;

	cgroup[3] = cg_name(cgroup[1], "D");
	अगर (!cgroup[3])
		जाओ cleanup;

	cgroup[4] = cg_name(cgroup[0], "E");
	अगर (!cgroup[4])
		जाओ cleanup;

	cgroup[5] = cg_name(cgroup[4], "F");
	अगर (!cgroup[5])
		जाओ cleanup;

	cgroup[6] = cg_name(cgroup[5], "G");
	अगर (!cgroup[6])
		जाओ cleanup;

	cgroup[7] = cg_name(cgroup[6], "H");
	अगर (!cgroup[7])
		जाओ cleanup;

	cgroup[8] = cg_name(cgroup[0], "I");
	अगर (!cgroup[8])
		जाओ cleanup;

	cgroup[9] = cg_name(cgroup[0], "K");
	अगर (!cgroup[9])
		जाओ cleanup;

	क्रम (i = 0; i < 10; i++)
		अगर (cg_create(cgroup[i]))
			जाओ cleanup;

	cg_run_noरुको(cgroup[2], child_fn, शून्य);
	cg_run_noरुको(cgroup[7], child_fn, शून्य);
	cg_run_noरुको(cgroup[9], child_fn, शून्य);
	cg_run_noरुको(cgroup[9], child_fn, शून्य);
	cg_run_noरुको(cgroup[9], child_fn, शून्य);

	/*
	 * Wait until all child processes will enter
	 * corresponding cgroups.
	 */

	अगर (cg_रुको_क्रम_proc_count(cgroup[2], 1) ||
	    cg_रुको_क्रम_proc_count(cgroup[7], 1) ||
	    cg_रुको_क्रम_proc_count(cgroup[9], 3))
		जाओ cleanup;

	/*
	 * Freeze B.
	 */
	अगर (cg_मुक्तze_रुको(cgroup[1], true))
		जाओ cleanup;

	/*
	 * Freeze F.
	 */
	अगर (cg_मुक्तze_रुको(cgroup[5], true))
		जाओ cleanup;

	/*
	 * Freeze G.
	 */
	अगर (cg_मुक्तze_रुको(cgroup[6], true))
		जाओ cleanup;

	/*
	 * Check that A and E are not frozen.
	 */
	अगर (cg_check_frozen(cgroup[0], false))
		जाओ cleanup;

	अगर (cg_check_frozen(cgroup[4], false))
		जाओ cleanup;

	/*
	 * Freeze A. Check that A, B and E are frozen.
	 */
	अगर (cg_मुक्तze_रुको(cgroup[0], true))
		जाओ cleanup;

	अगर (cg_check_frozen(cgroup[1], true))
		जाओ cleanup;

	अगर (cg_check_frozen(cgroup[4], true))
		जाओ cleanup;

	/*
	 * Unमुक्तze B, F and G
	 */
	अगर (cg_मुक्तze_noरुको(cgroup[1], false))
		जाओ cleanup;

	अगर (cg_मुक्तze_noरुको(cgroup[5], false))
		जाओ cleanup;

	अगर (cg_मुक्तze_noरुको(cgroup[6], false))
		जाओ cleanup;

	/*
	 * Check that C and H are still frozen.
	 */
	अगर (cg_check_frozen(cgroup[2], true))
		जाओ cleanup;

	अगर (cg_check_frozen(cgroup[7], true))
		जाओ cleanup;

	/*
	 * Unमुक्तze A. Check that A, C and K are not frozen.
	 */
	अगर (cg_मुक्तze_रुको(cgroup[0], false))
		जाओ cleanup;

	अगर (cg_check_frozen(cgroup[2], false))
		जाओ cleanup;

	अगर (cg_check_frozen(cgroup[9], false))
		जाओ cleanup;

	ret = KSFT_PASS;

cleanup:
	क्रम (i = 9; i >= 0 && cgroup[i]; i--) अणु
		cg_destroy(cgroup[i]);
		मुक्त(cgroup[i]);
	पूर्ण

	वापस ret;
पूर्ण

/*
 * A विभाजन bomb emulator.
 */
अटल पूर्णांक विभाजनbomb_fn(स्थिर अक्षर *cgroup, व्योम *arg)
अणु
	पूर्णांक ppid;

	विभाजन();
	विभाजन();

	ppid = getppid();

	जबतक (getppid() == ppid)
		usleep(1000);

	वापस getppid() == ppid;
पूर्ण

/*
 * The test runs a विभाजन bomb in a cgroup and tries to मुक्तze it.
 * Then it समाप्तs all processes and checks that cgroup isn't populated
 * anymore.
 */
अटल पूर्णांक test_cgमुक्तzer_विभाजनbomb(स्थिर अक्षर *root)
अणु
	पूर्णांक ret = KSFT_FAIL;
	अक्षर *cgroup = शून्य;

	cgroup = cg_name(root, "cg_forkbomb_test");
	अगर (!cgroup)
		जाओ cleanup;

	अगर (cg_create(cgroup))
		जाओ cleanup;

	cg_run_noरुको(cgroup, विभाजनbomb_fn, शून्य);

	usleep(100000);

	अगर (cg_मुक्तze_रुको(cgroup, true))
		जाओ cleanup;

	अगर (cg_समाप्तall(cgroup))
		जाओ cleanup;

	अगर (cg_रुको_क्रम_proc_count(cgroup, 0))
		जाओ cleanup;

	ret = KSFT_PASS;

cleanup:
	अगर (cgroup)
		cg_destroy(cgroup);
	मुक्त(cgroup);
	वापस ret;
पूर्ण

/*
 * The test creates a cgroups and मुक्तzes it. Then it creates a child cgroup
 * and populates it with a task. After that it checks that the child cgroup
 * is frozen and the parent cgroup reमुख्यs frozen too.
 */
अटल पूर्णांक test_cgमुक्तzer_सूची_गढ़ो(स्थिर अक्षर *root)
अणु
	पूर्णांक ret = KSFT_FAIL;
	अक्षर *parent, *child = शून्य;
	पूर्णांक pid;

	parent = cg_name(root, "cg_test_mkdir_A");
	अगर (!parent)
		जाओ cleanup;

	child = cg_name(parent, "cg_test_mkdir_B");
	अगर (!child)
		जाओ cleanup;

	अगर (cg_create(parent))
		जाओ cleanup;

	अगर (cg_मुक्तze_रुको(parent, true))
		जाओ cleanup;

	अगर (cg_create(child))
		जाओ cleanup;

	pid = cg_run_noरुको(child, child_fn, शून्य);
	अगर (pid < 0)
		जाओ cleanup;

	अगर (cg_रुको_क्रम_proc_count(child, 1))
		जाओ cleanup;

	अगर (cg_check_frozen(child, true))
		जाओ cleanup;

	अगर (cg_check_frozen(parent, true))
		जाओ cleanup;

	ret = KSFT_PASS;

cleanup:
	अगर (child)
		cg_destroy(child);
	मुक्त(child);
	अगर (parent)
		cg_destroy(parent);
	मुक्त(parent);
	वापस ret;
पूर्ण

/*
 * The test creates two nested cgroups, मुक्तzes the parent
 * and हटाओs the child. Then it checks that the parent cgroup
 * reमुख्यs frozen and it's possible to create a new child
 * without unमुक्तzing. The new child is frozen too.
 */
अटल पूर्णांक test_cgमुक्तzer_सूची_हटाओ(स्थिर अक्षर *root)
अणु
	पूर्णांक ret = KSFT_FAIL;
	अक्षर *parent, *child = शून्य;

	parent = cg_name(root, "cg_test_rmdir_A");
	अगर (!parent)
		जाओ cleanup;

	child = cg_name(parent, "cg_test_rmdir_B");
	अगर (!child)
		जाओ cleanup;

	अगर (cg_create(parent))
		जाओ cleanup;

	अगर (cg_create(child))
		जाओ cleanup;

	अगर (cg_मुक्तze_रुको(parent, true))
		जाओ cleanup;

	अगर (cg_destroy(child))
		जाओ cleanup;

	अगर (cg_check_frozen(parent, true))
		जाओ cleanup;

	अगर (cg_create(child))
		जाओ cleanup;

	अगर (cg_check_frozen(child, true))
		जाओ cleanup;

	ret = KSFT_PASS;

cleanup:
	अगर (child)
		cg_destroy(child);
	मुक्त(child);
	अगर (parent)
		cg_destroy(parent);
	मुक्त(parent);
	वापस ret;
पूर्ण

/*
 * The test creates two cgroups: A and B, runs a process in A
 * and perक्रमms several migrations:
 * 1) A (running) -> B (frozen)
 * 2) B (frozen) -> A (running)
 * 3) A (frozen) -> B (frozen)
 *
 * On each step it checks the actual state of both cgroups.
 */
अटल पूर्णांक test_cgमुक्तzer_migrate(स्थिर अक्षर *root)
अणु
	पूर्णांक ret = KSFT_FAIL;
	अक्षर *cgroup[2] = अणु0पूर्ण;
	पूर्णांक pid;

	cgroup[0] = cg_name(root, "cg_test_migrate_A");
	अगर (!cgroup[0])
		जाओ cleanup;

	cgroup[1] = cg_name(root, "cg_test_migrate_B");
	अगर (!cgroup[1])
		जाओ cleanup;

	अगर (cg_create(cgroup[0]))
		जाओ cleanup;

	अगर (cg_create(cgroup[1]))
		जाओ cleanup;

	pid = cg_run_noरुको(cgroup[0], child_fn, शून्य);
	अगर (pid < 0)
		जाओ cleanup;

	अगर (cg_रुको_क्रम_proc_count(cgroup[0], 1))
		जाओ cleanup;

	/*
	 * Migrate from A (running) to B (frozen)
	 */
	अगर (cg_मुक्तze_रुको(cgroup[1], true))
		जाओ cleanup;

	अगर (cg_enter_and_रुको_क्रम_frozen(cgroup[1], pid, true))
		जाओ cleanup;

	अगर (cg_check_frozen(cgroup[0], false))
		जाओ cleanup;

	/*
	 * Migrate from B (frozen) to A (running)
	 */
	अगर (cg_enter_and_रुको_क्रम_frozen(cgroup[0], pid, false))
		जाओ cleanup;

	अगर (cg_check_frozen(cgroup[1], true))
		जाओ cleanup;

	/*
	 * Migrate from A (frozen) to B (frozen)
	 */
	अगर (cg_मुक्तze_रुको(cgroup[0], true))
		जाओ cleanup;

	अगर (cg_enter_and_रुको_क्रम_frozen(cgroup[1], pid, true))
		जाओ cleanup;

	अगर (cg_check_frozen(cgroup[0], true))
		जाओ cleanup;

	ret = KSFT_PASS;

cleanup:
	अगर (cgroup[0])
		cg_destroy(cgroup[0]);
	मुक्त(cgroup[0]);
	अगर (cgroup[1])
		cg_destroy(cgroup[1]);
	मुक्त(cgroup[1]);
	वापस ret;
पूर्ण

/*
 * The test checks that ptrace works with a tracing process in a frozen cgroup.
 */
अटल पूर्णांक test_cgमुक्तzer_ptrace(स्थिर अक्षर *root)
अणु
	पूर्णांक ret = KSFT_FAIL;
	अक्षर *cgroup = शून्य;
	siginfo_t siginfo;
	पूर्णांक pid;

	cgroup = cg_name(root, "cg_test_ptrace");
	अगर (!cgroup)
		जाओ cleanup;

	अगर (cg_create(cgroup))
		जाओ cleanup;

	pid = cg_run_noरुको(cgroup, child_fn, शून्य);
	अगर (pid < 0)
		जाओ cleanup;

	अगर (cg_रुको_क्रम_proc_count(cgroup, 1))
		जाओ cleanup;

	अगर (cg_मुक्तze_रुको(cgroup, true))
		जाओ cleanup;

	अगर (ptrace(PTRACE_SEIZE, pid, शून्य, शून्य))
		जाओ cleanup;

	अगर (ptrace(PTRACE_INTERRUPT, pid, शून्य, शून्य))
		जाओ cleanup;

	रुकोpid(pid, शून्य, 0);

	/*
	 * Cgroup has to reमुख्य frozen, however the test task
	 * is in traced state.
	 */
	अगर (cg_check_frozen(cgroup, true))
		जाओ cleanup;

	अगर (ptrace(PTRACE_GETSIGINFO, pid, शून्य, &siginfo))
		जाओ cleanup;

	अगर (ptrace(PTRACE_DETACH, pid, शून्य, शून्य))
		जाओ cleanup;

	अगर (cg_check_frozen(cgroup, true))
		जाओ cleanup;

	ret = KSFT_PASS;

cleanup:
	अगर (cgroup)
		cg_destroy(cgroup);
	मुक्त(cgroup);
	वापस ret;
पूर्ण

/*
 * Check अगर the process is stopped.
 */
अटल पूर्णांक proc_check_stopped(पूर्णांक pid)
अणु
	अक्षर buf[PAGE_SIZE];
	पूर्णांक len;

	len = proc_पढ़ो_text(pid, 0, "stat", buf, माप(buf));
	अगर (len == -1) अणु
		debug("Can't get %d stat\n", pid);
		वापस -1;
	पूर्ण

	अगर (म_माला(buf, "(test_freezer) T ") == शून्य) अणु
		debug("Process %d in the unexpected state: %s\n", pid, buf);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Test that it's possible to मुक्तze a cgroup with a stopped process.
 */
अटल पूर्णांक test_cgमुक्तzer_stopped(स्थिर अक्षर *root)
अणु
	पूर्णांक pid, ret = KSFT_FAIL;
	अक्षर *cgroup = शून्य;

	cgroup = cg_name(root, "cg_test_stopped");
	अगर (!cgroup)
		जाओ cleanup;

	अगर (cg_create(cgroup))
		जाओ cleanup;

	pid = cg_run_noरुको(cgroup, child_fn, शून्य);

	अगर (cg_रुको_क्रम_proc_count(cgroup, 1))
		जाओ cleanup;

	अगर (समाप्त(pid, SIGSTOP))
		जाओ cleanup;

	अगर (cg_check_frozen(cgroup, false))
		जाओ cleanup;

	अगर (cg_मुक्तze_रुको(cgroup, true))
		जाओ cleanup;

	अगर (cg_मुक्तze_रुको(cgroup, false))
		जाओ cleanup;

	अगर (proc_check_stopped(pid))
		जाओ cleanup;

	ret = KSFT_PASS;

cleanup:
	अगर (cgroup)
		cg_destroy(cgroup);
	मुक्त(cgroup);
	वापस ret;
पूर्ण

/*
 * Test that it's possible to मुक्तze a cgroup with a ptraced process.
 */
अटल पूर्णांक test_cgमुक्तzer_ptraced(स्थिर अक्षर *root)
अणु
	पूर्णांक pid, ret = KSFT_FAIL;
	अक्षर *cgroup = शून्य;
	siginfo_t siginfo;

	cgroup = cg_name(root, "cg_test_ptraced");
	अगर (!cgroup)
		जाओ cleanup;

	अगर (cg_create(cgroup))
		जाओ cleanup;

	pid = cg_run_noरुको(cgroup, child_fn, शून्य);

	अगर (cg_रुको_क्रम_proc_count(cgroup, 1))
		जाओ cleanup;

	अगर (ptrace(PTRACE_SEIZE, pid, शून्य, शून्य))
		जाओ cleanup;

	अगर (ptrace(PTRACE_INTERRUPT, pid, शून्य, शून्य))
		जाओ cleanup;

	रुकोpid(pid, शून्य, 0);

	अगर (cg_check_frozen(cgroup, false))
		जाओ cleanup;

	अगर (cg_मुक्तze_रुको(cgroup, true))
		जाओ cleanup;

	/*
	 * cg_check_frozen(cgroup, true) will fail here,
	 * because the task in in the TRACEd state.
	 */
	अगर (cg_मुक्तze_रुको(cgroup, false))
		जाओ cleanup;

	अगर (ptrace(PTRACE_GETSIGINFO, pid, शून्य, &siginfo))
		जाओ cleanup;

	अगर (ptrace(PTRACE_DETACH, pid, शून्य, शून्य))
		जाओ cleanup;

	ret = KSFT_PASS;

cleanup:
	अगर (cgroup)
		cg_destroy(cgroup);
	मुक्त(cgroup);
	वापस ret;
पूर्ण

अटल पूर्णांक vविभाजन_fn(स्थिर अक्षर *cgroup, व्योम *arg)
अणु
	पूर्णांक pid = vविभाजन();

	अगर (pid == 0)
		जबतक (true)
			sleep(1);

	वापस pid;
पूर्ण

/*
 * Test that it's possible to मुक्तze a cgroup with a process,
 * which called vविभाजन() and is रुकोing क्रम a child.
 */
अटल पूर्णांक test_cgमुक्तzer_vविभाजन(स्थिर अक्षर *root)
अणु
	पूर्णांक ret = KSFT_FAIL;
	अक्षर *cgroup = शून्य;

	cgroup = cg_name(root, "cg_test_vfork");
	अगर (!cgroup)
		जाओ cleanup;

	अगर (cg_create(cgroup))
		जाओ cleanup;

	cg_run_noरुको(cgroup, vविभाजन_fn, शून्य);

	अगर (cg_रुको_क्रम_proc_count(cgroup, 2))
		जाओ cleanup;

	अगर (cg_मुक्तze_रुको(cgroup, true))
		जाओ cleanup;

	ret = KSFT_PASS;

cleanup:
	अगर (cgroup)
		cg_destroy(cgroup);
	मुक्त(cgroup);
	वापस ret;
पूर्ण

#घोषणा T(x) अणु x, #x पूर्ण
काष्ठा cgमुक्तzer_test अणु
	पूर्णांक (*fn)(स्थिर अक्षर *root);
	स्थिर अक्षर *name;
पूर्ण tests[] = अणु
	T(test_cgमुक्तzer_simple),
	T(test_cgमुक्तzer_tree),
	T(test_cgमुक्तzer_विभाजनbomb),
	T(test_cgमुक्तzer_सूची_गढ़ो),
	T(test_cgमुक्तzer_सूची_हटाओ),
	T(test_cgमुक्तzer_migrate),
	T(test_cgमुक्तzer_ptrace),
	T(test_cgमुक्तzer_stopped),
	T(test_cgमुक्तzer_ptraced),
	T(test_cgमुक्तzer_vविभाजन),
पूर्ण;
#अघोषित T

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	अक्षर root[PATH_MAX];
	पूर्णांक i, ret = निकास_सफल;

	अगर (cg_find_unअगरied_root(root, माप(root)))
		ksft_निकास_skip("cgroup v2 isn't mounted\n");
	क्रम (i = 0; i < ARRAY_SIZE(tests); i++) अणु
		चयन (tests[i].fn(root)) अणु
		हाल KSFT_PASS:
			ksft_test_result_pass("%s\n", tests[i].name);
			अवरोध;
		हाल KSFT_SKIP:
			ksft_test_result_skip("%s\n", tests[i].name);
			अवरोध;
		शेष:
			ret = निकास_त्रुटि;
			ksft_test_result_fail("%s\n", tests[i].name);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण
