<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#समावेश <linux/सीमा.स>
#समावेश <sys/types.h>
#समावेश <sys/mman.h>
#समावेश <sys/रुको.h>
#समावेश <unistd.h>
#समावेश <fcntl.h>
#समावेश <मानकपन.स>
#समावेश <त्रुटिसं.स>
#समावेश <संकेत.स>
#समावेश <माला.स>
#समावेश <pthपढ़ो.h>

#समावेश "../kselftest.h"
#समावेश "cgroup_util.h"

अटल पूर्णांक touch_anon(अक्षर *buf, माप_प्रकार size)
अणु
	पूर्णांक fd;
	अक्षर *pos = buf;

	fd = खोलो("/dev/urandom", O_RDONLY);
	अगर (fd < 0)
		वापस -1;

	जबतक (size > 0) अणु
		sमाप_प्रकार ret = पढ़ो(fd, pos, size);

		अगर (ret < 0) अणु
			अगर (त्रुटि_सं != EINTR) अणु
				बंद(fd);
				वापस -1;
			पूर्ण
		पूर्ण अन्यथा अणु
			pos += ret;
			size -= ret;
		पूर्ण
	पूर्ण
	बंद(fd);

	वापस 0;
पूर्ण

अटल पूर्णांक alloc_and_touch_anon_noनिकास(स्थिर अक्षर *cgroup, व्योम *arg)
अणु
	पूर्णांक ppid = getppid();
	माप_प्रकार size = (माप_प्रकार)arg;
	व्योम *buf;

	buf = mmap(शून्य, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON,
		   0, 0);
	अगर (buf == MAP_FAILED)
		वापस -1;

	अगर (touch_anon((अक्षर *)buf, size)) अणु
		munmap(buf, size);
		वापस -1;
	पूर्ण

	जबतक (getppid() == ppid)
		sleep(1);

	munmap(buf, size);
	वापस 0;
पूर्ण

/*
 * Create a child process that allocates and touches 100MB, then रुकोs to be
 * समाप्तed. Wait until the child is attached to the cgroup, समाप्त all processes
 * in that cgroup and रुको until "cgroup.procs" is empty. At this poपूर्णांक try to
 * destroy the empty cgroup. The test helps detect race conditions between
 * dying processes leaving the cgroup and cgroup deकाष्ठाion path.
 */
अटल पूर्णांक test_cgcore_destroy(स्थिर अक्षर *root)
अणु
	पूर्णांक ret = KSFT_FAIL;
	अक्षर *cg_test = शून्य;
	पूर्णांक child_pid;
	अक्षर buf[PAGE_SIZE];

	cg_test = cg_name(root, "cg_test");

	अगर (!cg_test)
		जाओ cleanup;

	क्रम (पूर्णांक i = 0; i < 10; i++) अणु
		अगर (cg_create(cg_test))
			जाओ cleanup;

		child_pid = cg_run_noरुको(cg_test, alloc_and_touch_anon_noनिकास,
					  (व्योम *) MB(100));

		अगर (child_pid < 0)
			जाओ cleanup;

		/* रुको क्रम the child to enter cgroup */
		अगर (cg_रुको_क्रम_proc_count(cg_test, 1))
			जाओ cleanup;

		अगर (cg_समाप्तall(cg_test))
			जाओ cleanup;

		/* रुको क्रम cgroup to be empty */
		जबतक (1) अणु
			अगर (cg_पढ़ो(cg_test, "cgroup.procs", buf, माप(buf)))
				जाओ cleanup;
			अगर (buf[0] == '\0')
				अवरोध;
			usleep(1000);
		पूर्ण

		अगर (सूची_हटाओ(cg_test))
			जाओ cleanup;

		अगर (रुकोpid(child_pid, शून्य, 0) < 0)
			जाओ cleanup;
	पूर्ण
	ret = KSFT_PASS;
cleanup:
	अगर (cg_test)
		cg_destroy(cg_test);
	मुक्त(cg_test);
	वापस ret;
पूर्ण

/*
 * A(0) - B(0) - C(1)
 *        \ D(0)
 *
 * A, B and C's "populated" fields would be 1 while D's 0.
 * test that after the one process in C is moved to root,
 * A,B and C's "populated" fields would flip to "0" and file
 * modअगरied events will be generated on the
 * "cgroup.events" files of both cgroups.
 */
अटल पूर्णांक test_cgcore_populated(स्थिर अक्षर *root)
अणु
	पूर्णांक ret = KSFT_FAIL;
	पूर्णांक err;
	अक्षर *cg_test_a = शून्य, *cg_test_b = शून्य;
	अक्षर *cg_test_c = शून्य, *cg_test_d = शून्य;
	पूर्णांक cgroup_fd = -EBADF;
	pid_t pid;

	cg_test_a = cg_name(root, "cg_test_a");
	cg_test_b = cg_name(root, "cg_test_a/cg_test_b");
	cg_test_c = cg_name(root, "cg_test_a/cg_test_b/cg_test_c");
	cg_test_d = cg_name(root, "cg_test_a/cg_test_b/cg_test_d");

	अगर (!cg_test_a || !cg_test_b || !cg_test_c || !cg_test_d)
		जाओ cleanup;

	अगर (cg_create(cg_test_a))
		जाओ cleanup;

	अगर (cg_create(cg_test_b))
		जाओ cleanup;

	अगर (cg_create(cg_test_c))
		जाओ cleanup;

	अगर (cg_create(cg_test_d))
		जाओ cleanup;

	अगर (cg_enter_current(cg_test_c))
		जाओ cleanup;

	अगर (cg_पढ़ो_म_भेद(cg_test_a, "cgroup.events", "populated 1\n"))
		जाओ cleanup;

	अगर (cg_पढ़ो_म_भेद(cg_test_b, "cgroup.events", "populated 1\n"))
		जाओ cleanup;

	अगर (cg_पढ़ो_म_भेद(cg_test_c, "cgroup.events", "populated 1\n"))
		जाओ cleanup;

	अगर (cg_पढ़ो_म_भेद(cg_test_d, "cgroup.events", "populated 0\n"))
		जाओ cleanup;

	अगर (cg_enter_current(root))
		जाओ cleanup;

	अगर (cg_पढ़ो_म_भेद(cg_test_a, "cgroup.events", "populated 0\n"))
		जाओ cleanup;

	अगर (cg_पढ़ो_म_भेद(cg_test_b, "cgroup.events", "populated 0\n"))
		जाओ cleanup;

	अगर (cg_पढ़ो_म_भेद(cg_test_c, "cgroup.events", "populated 0\n"))
		जाओ cleanup;

	अगर (cg_पढ़ो_म_भेद(cg_test_d, "cgroup.events", "populated 0\n"))
		जाओ cleanup;

	/* Test that we can directly clone पूर्णांकo a new cgroup. */
	cgroup_fd = dirfd_खोलो_opath(cg_test_d);
	अगर (cgroup_fd < 0)
		जाओ cleanup;

	pid = clone_पूर्णांकo_cgroup(cgroup_fd);
	अगर (pid < 0) अणु
		अगर (त्रुटि_सं == ENOSYS)
			जाओ cleanup_pass;
		जाओ cleanup;
	पूर्ण

	अगर (pid == 0) अणु
		अगर (उठाओ(SIGSTOP))
			निकास(निकास_त्रुटि);
		निकास(निकास_सफल);
	पूर्ण

	err = cg_पढ़ो_म_भेद(cg_test_d, "cgroup.events", "populated 1\n");

	(व्योम)clone_reap(pid, WSTOPPED);
	(व्योम)समाप्त(pid, SIGCONT);
	(व्योम)clone_reap(pid, WEXITED);

	अगर (err)
		जाओ cleanup;

	अगर (cg_पढ़ो_म_भेद(cg_test_d, "cgroup.events", "populated 0\n"))
		जाओ cleanup;

	/* Remove cgroup. */
	अगर (cg_test_d) अणु
		cg_destroy(cg_test_d);
		मुक्त(cg_test_d);
		cg_test_d = शून्य;
	पूर्ण

	pid = clone_पूर्णांकo_cgroup(cgroup_fd);
	अगर (pid < 0)
		जाओ cleanup_pass;
	अगर (pid == 0)
		निकास(निकास_सफल);
	(व्योम)clone_reap(pid, WEXITED);
	जाओ cleanup;

cleanup_pass:
	ret = KSFT_PASS;

cleanup:
	अगर (cg_test_d)
		cg_destroy(cg_test_d);
	अगर (cg_test_c)
		cg_destroy(cg_test_c);
	अगर (cg_test_b)
		cg_destroy(cg_test_b);
	अगर (cg_test_a)
		cg_destroy(cg_test_a);
	मुक्त(cg_test_d);
	मुक्त(cg_test_c);
	मुक्त(cg_test_b);
	मुक्त(cg_test_a);
	अगर (cgroup_fd >= 0)
		बंद(cgroup_fd);
	वापस ret;
पूर्ण

/*
 * A (करोमुख्य thपढ़ोed) - B (thपढ़ोed) - C (करोमुख्य)
 *
 * test that C can't be used until it is turned पूर्णांकo a
 * thपढ़ोed cgroup.  "cgroup.type" file will report "domain (invalid)" in
 * these हालs. Operations which fail due to invalid topology use
 * EOPNOTSUPP as the त्रुटि_सं.
 */
अटल पूर्णांक test_cgcore_invalid_करोमुख्य(स्थिर अक्षर *root)
अणु
	पूर्णांक ret = KSFT_FAIL;
	अक्षर *gअक्रमparent = शून्य, *parent = शून्य, *child = शून्य;

	gअक्रमparent = cg_name(root, "cg_test_grandparent");
	parent = cg_name(root, "cg_test_grandparent/cg_test_parent");
	child = cg_name(root, "cg_test_grandparent/cg_test_parent/cg_test_child");
	अगर (!parent || !child || !gअक्रमparent)
		जाओ cleanup;

	अगर (cg_create(gअक्रमparent))
		जाओ cleanup;

	अगर (cg_create(parent))
		जाओ cleanup;

	अगर (cg_create(child))
		जाओ cleanup;

	अगर (cg_ग_लिखो(parent, "cgroup.type", "threaded"))
		जाओ cleanup;

	अगर (cg_पढ़ो_म_भेद(child, "cgroup.type", "domain invalid\n"))
		जाओ cleanup;

	अगर (!cg_enter_current(child))
		जाओ cleanup;

	अगर (त्रुटि_सं != EOPNOTSUPP)
		जाओ cleanup;

	अगर (!clone_पूर्णांकo_cgroup_run_रुको(child))
		जाओ cleanup;

	अगर (त्रुटि_सं == ENOSYS)
		जाओ cleanup_pass;

	अगर (त्रुटि_सं != EOPNOTSUPP)
		जाओ cleanup;

cleanup_pass:
	ret = KSFT_PASS;

cleanup:
	cg_enter_current(root);
	अगर (child)
		cg_destroy(child);
	अगर (parent)
		cg_destroy(parent);
	अगर (gअक्रमparent)
		cg_destroy(gअक्रमparent);
	मुक्त(child);
	मुक्त(parent);
	मुक्त(gअक्रमparent);
	वापस ret;
पूर्ण

/*
 * Test that when a child becomes thपढ़ोed
 * the parent type becomes करोमुख्य thपढ़ोed.
 */
अटल पूर्णांक test_cgcore_parent_becomes_thपढ़ोed(स्थिर अक्षर *root)
अणु
	पूर्णांक ret = KSFT_FAIL;
	अक्षर *parent = शून्य, *child = शून्य;

	parent = cg_name(root, "cg_test_parent");
	child = cg_name(root, "cg_test_parent/cg_test_child");
	अगर (!parent || !child)
		जाओ cleanup;

	अगर (cg_create(parent))
		जाओ cleanup;

	अगर (cg_create(child))
		जाओ cleanup;

	अगर (cg_ग_लिखो(child, "cgroup.type", "threaded"))
		जाओ cleanup;

	अगर (cg_पढ़ो_म_भेद(parent, "cgroup.type", "domain threaded\n"))
		जाओ cleanup;

	ret = KSFT_PASS;

cleanup:
	अगर (child)
		cg_destroy(child);
	अगर (parent)
		cg_destroy(parent);
	मुक्त(child);
	मुक्त(parent);
	वापस ret;

पूर्ण

/*
 * Test that there's no पूर्णांकernal process स्थिरrain on thपढ़ोed cgroups.
 * You can add thपढ़ोs/processes on a parent with a controller enabled.
 */
अटल पूर्णांक test_cgcore_no_पूर्णांकernal_process_स्थिरraपूर्णांक_on_thपढ़ोs(स्थिर अक्षर *root)
अणु
	पूर्णांक ret = KSFT_FAIL;
	अक्षर *parent = शून्य, *child = शून्य;

	अगर (cg_पढ़ो_म_माला(root, "cgroup.controllers", "cpu") ||
	    cg_ग_लिखो(root, "cgroup.subtree_control", "+cpu")) अणु
		ret = KSFT_SKIP;
		जाओ cleanup;
	पूर्ण

	parent = cg_name(root, "cg_test_parent");
	child = cg_name(root, "cg_test_parent/cg_test_child");
	अगर (!parent || !child)
		जाओ cleanup;

	अगर (cg_create(parent))
		जाओ cleanup;

	अगर (cg_create(child))
		जाओ cleanup;

	अगर (cg_ग_लिखो(parent, "cgroup.type", "threaded"))
		जाओ cleanup;

	अगर (cg_ग_लिखो(child, "cgroup.type", "threaded"))
		जाओ cleanup;

	अगर (cg_ग_लिखो(parent, "cgroup.subtree_control", "+cpu"))
		जाओ cleanup;

	अगर (cg_enter_current(parent))
		जाओ cleanup;

	ret = KSFT_PASS;

cleanup:
	cg_enter_current(root);
	cg_enter_current(root);
	अगर (child)
		cg_destroy(child);
	अगर (parent)
		cg_destroy(parent);
	मुक्त(child);
	मुक्त(parent);
	वापस ret;
पूर्ण

/*
 * Test that you can't enable a controller on a child if it's not enabled
 * on the parent.
 */
अटल पूर्णांक test_cgcore_top_करोwn_स्थिरraपूर्णांक_enable(स्थिर अक्षर *root)
अणु
	पूर्णांक ret = KSFT_FAIL;
	अक्षर *parent = शून्य, *child = शून्य;

	parent = cg_name(root, "cg_test_parent");
	child = cg_name(root, "cg_test_parent/cg_test_child");
	अगर (!parent || !child)
		जाओ cleanup;

	अगर (cg_create(parent))
		जाओ cleanup;

	अगर (cg_create(child))
		जाओ cleanup;

	अगर (!cg_ग_लिखो(child, "cgroup.subtree_control", "+memory"))
		जाओ cleanup;

	ret = KSFT_PASS;

cleanup:
	अगर (child)
		cg_destroy(child);
	अगर (parent)
		cg_destroy(parent);
	मुक्त(child);
	मुक्त(parent);
	वापस ret;
पूर्ण

/*
 * Test that you can't disable a controller on a parent
 * अगर it's enabled in a child.
 */
अटल पूर्णांक test_cgcore_top_करोwn_स्थिरraपूर्णांक_disable(स्थिर अक्षर *root)
अणु
	पूर्णांक ret = KSFT_FAIL;
	अक्षर *parent = शून्य, *child = शून्य;

	parent = cg_name(root, "cg_test_parent");
	child = cg_name(root, "cg_test_parent/cg_test_child");
	अगर (!parent || !child)
		जाओ cleanup;

	अगर (cg_create(parent))
		जाओ cleanup;

	अगर (cg_create(child))
		जाओ cleanup;

	अगर (cg_ग_लिखो(parent, "cgroup.subtree_control", "+memory"))
		जाओ cleanup;

	अगर (cg_ग_लिखो(child, "cgroup.subtree_control", "+memory"))
		जाओ cleanup;

	अगर (!cg_ग_लिखो(parent, "cgroup.subtree_control", "-memory"))
		जाओ cleanup;

	ret = KSFT_PASS;

cleanup:
	अगर (child)
		cg_destroy(child);
	अगर (parent)
		cg_destroy(parent);
	मुक्त(child);
	मुक्त(parent);
	वापस ret;
पूर्ण

/*
 * Test पूर्णांकernal process स्थिरraपूर्णांक.
 * You can't add a pid to a करोमुख्य parent अगर a controller is enabled.
 */
अटल पूर्णांक test_cgcore_पूर्णांकernal_process_स्थिरraपूर्णांक(स्थिर अक्षर *root)
अणु
	पूर्णांक ret = KSFT_FAIL;
	अक्षर *parent = शून्य, *child = शून्य;

	parent = cg_name(root, "cg_test_parent");
	child = cg_name(root, "cg_test_parent/cg_test_child");
	अगर (!parent || !child)
		जाओ cleanup;

	अगर (cg_create(parent))
		जाओ cleanup;

	अगर (cg_create(child))
		जाओ cleanup;

	अगर (cg_ग_लिखो(parent, "cgroup.subtree_control", "+memory"))
		जाओ cleanup;

	अगर (!cg_enter_current(parent))
		जाओ cleanup;

	अगर (!clone_पूर्णांकo_cgroup_run_रुको(parent))
		जाओ cleanup;

	ret = KSFT_PASS;

cleanup:
	अगर (child)
		cg_destroy(child);
	अगर (parent)
		cg_destroy(parent);
	मुक्त(child);
	मुक्त(parent);
	वापस ret;
पूर्ण

अटल व्योम *dummy_thपढ़ो_fn(व्योम *arg)
अणु
	वापस (व्योम *)(माप_प्रकार)छोड़ो();
पूर्ण

/*
 * Test thपढ़ोgroup migration.
 * All thपढ़ोs of a process are migrated together.
 */
अटल पूर्णांक test_cgcore_proc_migration(स्थिर अक्षर *root)
अणु
	पूर्णांक ret = KSFT_FAIL;
	पूर्णांक t, c_thपढ़ोs = 0, n_thपढ़ोs = 13;
	अक्षर *src = शून्य, *dst = शून्य;
	pthपढ़ो_t thपढ़ोs[n_thपढ़ोs];

	src = cg_name(root, "cg_src");
	dst = cg_name(root, "cg_dst");
	अगर (!src || !dst)
		जाओ cleanup;

	अगर (cg_create(src))
		जाओ cleanup;
	अगर (cg_create(dst))
		जाओ cleanup;

	अगर (cg_enter_current(src))
		जाओ cleanup;

	क्रम (c_thपढ़ोs = 0; c_thपढ़ोs < n_thपढ़ोs; ++c_thपढ़ोs) अणु
		अगर (pthपढ़ो_create(&thपढ़ोs[c_thपढ़ोs], शून्य, dummy_thपढ़ो_fn, शून्य))
			जाओ cleanup;
	पूर्ण

	cg_enter_current(dst);
	अगर (cg_पढ़ो_lc(dst, "cgroup.threads") != n_thपढ़ोs + 1)
		जाओ cleanup;

	ret = KSFT_PASS;

cleanup:
	क्रम (t = 0; t < c_thपढ़ोs; ++t) अणु
		pthपढ़ो_cancel(thपढ़ोs[t]);
	पूर्ण

	क्रम (t = 0; t < c_thपढ़ोs; ++t) अणु
		pthपढ़ो_join(thपढ़ोs[t], शून्य);
	पूर्ण

	cg_enter_current(root);

	अगर (dst)
		cg_destroy(dst);
	अगर (src)
		cg_destroy(src);
	मुक्त(dst);
	मुक्त(src);
	वापस ret;
पूर्ण

अटल व्योम *migrating_thपढ़ो_fn(व्योम *arg)
अणु
	पूर्णांक g, i, n_iterations = 1000;
	अक्षर **grps = arg;
	अक्षर lines[3][PATH_MAX];

	क्रम (g = 1; g < 3; ++g)
		snम_लिखो(lines[g], माप(lines[g]), "0::%s", grps[g] + म_माप(grps[0]));

	क्रम (i = 0; i < n_iterations; ++i) अणु
		cg_enter_current_thपढ़ो(grps[(i % 2) + 1]);

		अगर (proc_पढ़ो_म_माला(0, 1, "cgroup", lines[(i % 2) + 1]))
			वापस (व्योम *)-1;
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * Test single thपढ़ो migration.
 * Thपढ़ोed cgroups allow successful migration of a thपढ़ो.
 */
अटल पूर्णांक test_cgcore_thपढ़ो_migration(स्थिर अक्षर *root)
अणु
	पूर्णांक ret = KSFT_FAIL;
	अक्षर *करोm = शून्य;
	अक्षर line[PATH_MAX];
	अक्षर *grps[3] = अणु (अक्षर *)root, शून्य, शून्य पूर्ण;
	pthपढ़ो_t thr;
	व्योम *retval;

	करोm = cg_name(root, "cg_dom");
	grps[1] = cg_name(root, "cg_dom/cg_src");
	grps[2] = cg_name(root, "cg_dom/cg_dst");
	अगर (!grps[1] || !grps[2] || !करोm)
		जाओ cleanup;

	अगर (cg_create(करोm))
		जाओ cleanup;
	अगर (cg_create(grps[1]))
		जाओ cleanup;
	अगर (cg_create(grps[2]))
		जाओ cleanup;

	अगर (cg_ग_लिखो(grps[1], "cgroup.type", "threaded"))
		जाओ cleanup;
	अगर (cg_ग_लिखो(grps[2], "cgroup.type", "threaded"))
		जाओ cleanup;

	अगर (cg_enter_current(grps[1]))
		जाओ cleanup;

	अगर (pthपढ़ो_create(&thr, शून्य, migrating_thपढ़ो_fn, grps))
		जाओ cleanup;

	अगर (pthपढ़ो_join(thr, &retval))
		जाओ cleanup;

	अगर (retval)
		जाओ cleanup;

	snम_लिखो(line, माप(line), "0::%s", grps[1] + म_माप(grps[0]));
	अगर (proc_पढ़ो_म_माला(0, 1, "cgroup", line))
		जाओ cleanup;

	ret = KSFT_PASS;

cleanup:
	cg_enter_current(root);
	अगर (grps[2])
		cg_destroy(grps[2]);
	अगर (grps[1])
		cg_destroy(grps[1]);
	अगर (करोm)
		cg_destroy(करोm);
	मुक्त(grps[2]);
	मुक्त(grps[1]);
	मुक्त(करोm);
	वापस ret;
पूर्ण

#घोषणा T(x) अणु x, #x पूर्ण
काष्ठा corecg_test अणु
	पूर्णांक (*fn)(स्थिर अक्षर *root);
	स्थिर अक्षर *name;
पूर्ण tests[] = अणु
	T(test_cgcore_पूर्णांकernal_process_स्थिरraपूर्णांक),
	T(test_cgcore_top_करोwn_स्थिरraपूर्णांक_enable),
	T(test_cgcore_top_करोwn_स्थिरraपूर्णांक_disable),
	T(test_cgcore_no_पूर्णांकernal_process_स्थिरraपूर्णांक_on_thपढ़ोs),
	T(test_cgcore_parent_becomes_thपढ़ोed),
	T(test_cgcore_invalid_करोमुख्य),
	T(test_cgcore_populated),
	T(test_cgcore_proc_migration),
	T(test_cgcore_thपढ़ो_migration),
	T(test_cgcore_destroy),
पूर्ण;
#अघोषित T

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	अक्षर root[PATH_MAX];
	पूर्णांक i, ret = निकास_सफल;

	अगर (cg_find_unअगरied_root(root, माप(root)))
		ksft_निकास_skip("cgroup v2 isn't mounted\n");

	अगर (cg_पढ़ो_म_माला(root, "cgroup.subtree_control", "memory"))
		अगर (cg_ग_लिखो(root, "cgroup.subtree_control", "+memory"))
			ksft_निकास_skip("Failed to set memory controller\n");

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
