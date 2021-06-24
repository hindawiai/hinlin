<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा _GNU_SOURCE

#समावेश <linux/सीमा.स>
#समावेश <fcntl.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/स्थिति.स>
#समावेश <sys/types.h>
#समावेश <unistd.h>
#समावेश <sys/रुको.h>
#समावेश <त्रुटिसं.स>
#समावेश <sys/sysinfo.h>
#समावेश <pthपढ़ो.h>

#समावेश "../kselftest.h"
#समावेश "cgroup_util.h"


/*
 * Memory cgroup अक्षरging is perक्रमmed using percpu batches 32 pages
 * big (look at MEMCG_CHARGE_BATCH), whereas memory.stat is exact. So
 * the maximum discrepancy between अक्षरge and vmstat entries is number
 * of cpus multiplied by 32 pages.
 */
#घोषणा MAX_VMSTAT_ERROR (4096 * 32 * get_nprocs())


अटल पूर्णांक alloc_dcache(स्थिर अक्षर *cgroup, व्योम *arg)
अणु
	अचिन्हित दीर्घ i;
	काष्ठा stat st;
	अक्षर buf[128];

	क्रम (i = 0; i < (अचिन्हित दीर्घ)arg; i++) अणु
		snम_लिखो(buf, माप(buf),
			"/something-non-existent-with-a-long-name-%64lu-%d",
			 i, getpid());
		stat(buf, &st);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * This test allocates 100000 of negative dentries with दीर्घ names.
 * Then it checks that "slab" in memory.stat is larger than 1M.
 * Then it sets memory.high to 1M and checks that at least 1/2
 * of slab memory has been reclaimed.
 */
अटल पूर्णांक test_kmem_basic(स्थिर अक्षर *root)
अणु
	पूर्णांक ret = KSFT_FAIL;
	अक्षर *cg = शून्य;
	दीर्घ slab0, slab1, current;

	cg = cg_name(root, "kmem_basic_test");
	अगर (!cg)
		जाओ cleanup;

	अगर (cg_create(cg))
		जाओ cleanup;

	अगर (cg_run(cg, alloc_dcache, (व्योम *)100000))
		जाओ cleanup;

	slab0 = cg_पढ़ो_key_दीर्घ(cg, "memory.stat", "slab ");
	अगर (slab0 < (1 << 20))
		जाओ cleanup;

	cg_ग_लिखो(cg, "memory.high", "1M");
	slab1 = cg_पढ़ो_key_दीर्घ(cg, "memory.stat", "slab ");
	अगर (slab1 <= 0)
		जाओ cleanup;

	current = cg_पढ़ो_दीर्घ(cg, "memory.current");
	अगर (current <= 0)
		जाओ cleanup;

	अगर (slab1 < slab0 / 2 && current < slab0 / 2)
		ret = KSFT_PASS;
cleanup:
	cg_destroy(cg);
	मुक्त(cg);

	वापस ret;
पूर्ण

अटल व्योम *alloc_kmem_fn(व्योम *arg)
अणु
	alloc_dcache(शून्य, (व्योम *)100);
	वापस शून्य;
पूर्ण

अटल पूर्णांक alloc_kmem_smp(स्थिर अक्षर *cgroup, व्योम *arg)
अणु
	पूर्णांक nr_thपढ़ोs = 2 * get_nprocs();
	pthपढ़ो_t *tinfo;
	अचिन्हित दीर्घ i;
	पूर्णांक ret = -1;

	tinfo = सुस्मृति(nr_thपढ़ोs, माप(pthपढ़ो_t));
	अगर (tinfo == शून्य)
		वापस -1;

	क्रम (i = 0; i < nr_thपढ़ोs; i++) अणु
		अगर (pthपढ़ो_create(&tinfo[i], शून्य, &alloc_kmem_fn,
				   (व्योम *)i)) अणु
			मुक्त(tinfo);
			वापस -1;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < nr_thपढ़ोs; i++) अणु
		ret = pthपढ़ो_join(tinfo[i], शून्य);
		अगर (ret)
			अवरोध;
	पूर्ण

	मुक्त(tinfo);
	वापस ret;
पूर्ण

अटल पूर्णांक cg_run_in_subcgroups(स्थिर अक्षर *parent,
				पूर्णांक (*fn)(स्थिर अक्षर *cgroup, व्योम *arg),
				व्योम *arg, पूर्णांक बार)
अणु
	अक्षर *child;
	पूर्णांक i;

	क्रम (i = 0; i < बार; i++) अणु
		child = cg_name_indexed(parent, "child", i);
		अगर (!child)
			वापस -1;

		अगर (cg_create(child)) अणु
			cg_destroy(child);
			मुक्त(child);
			वापस -1;
		पूर्ण

		अगर (cg_run(child, fn, शून्य)) अणु
			cg_destroy(child);
			मुक्त(child);
			वापस -1;
		पूर्ण

		cg_destroy(child);
		मुक्त(child);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * The test creates and destroys a large number of cgroups. In each cgroup it
 * allocates some slab memory (mostly negative dentries) using 2 * NR_CPUS
 * thपढ़ोs. Then it checks the sanity of numbers on the parent level:
 * the total size of the cgroups should be roughly equal to
 * anon + file + slab + kernel_stack.
 */
अटल पूर्णांक test_kmem_memcg_deletion(स्थिर अक्षर *root)
अणु
	दीर्घ current, slab, anon, file, kernel_stack, pagetables, percpu, sock, sum;
	पूर्णांक ret = KSFT_FAIL;
	अक्षर *parent;

	parent = cg_name(root, "kmem_memcg_deletion_test");
	अगर (!parent)
		जाओ cleanup;

	अगर (cg_create(parent))
		जाओ cleanup;

	अगर (cg_ग_लिखो(parent, "cgroup.subtree_control", "+memory"))
		जाओ cleanup;

	अगर (cg_run_in_subcgroups(parent, alloc_kmem_smp, शून्य, 100))
		जाओ cleanup;

	current = cg_पढ़ो_दीर्घ(parent, "memory.current");
	slab = cg_पढ़ो_key_दीर्घ(parent, "memory.stat", "slab ");
	anon = cg_पढ़ो_key_दीर्घ(parent, "memory.stat", "anon ");
	file = cg_पढ़ो_key_दीर्घ(parent, "memory.stat", "file ");
	kernel_stack = cg_पढ़ो_key_दीर्घ(parent, "memory.stat", "kernel_stack ");
	pagetables = cg_पढ़ो_key_दीर्घ(parent, "memory.stat", "pagetables ");
	percpu = cg_पढ़ो_key_दीर्घ(parent, "memory.stat", "percpu ");
	sock = cg_पढ़ो_key_दीर्घ(parent, "memory.stat", "sock ");
	अगर (current < 0 || slab < 0 || anon < 0 || file < 0 ||
	    kernel_stack < 0 || pagetables < 0 || percpu < 0 || sock < 0)
		जाओ cleanup;

	sum = slab + anon + file + kernel_stack + pagetables + percpu + sock;
	अगर (असल(sum - current) < MAX_VMSTAT_ERROR) अणु
		ret = KSFT_PASS;
	पूर्ण अन्यथा अणु
		म_लिखो("memory.current = %ld\n", current);
		म_लिखो("slab + anon + file + kernel_stack = %ld\n", sum);
		म_लिखो("slab = %ld\n", slab);
		म_लिखो("anon = %ld\n", anon);
		म_लिखो("file = %ld\n", file);
		म_लिखो("kernel_stack = %ld\n", kernel_stack);
		म_लिखो("pagetables = %ld\n", pagetables);
		म_लिखो("percpu = %ld\n", percpu);
		म_लिखो("sock = %ld\n", sock);
	पूर्ण

cleanup:
	cg_destroy(parent);
	मुक्त(parent);

	वापस ret;
पूर्ण

/*
 * The test पढ़ोs the entire /proc/kpagecgroup. If the operation went
 * successfully (and the kernel didn't panic), the test is treated as passed.
 */
अटल पूर्णांक test_kmem_proc_kpagecgroup(स्थिर अक्षर *root)
अणु
	अचिन्हित दीर्घ buf[128];
	पूर्णांक ret = KSFT_FAIL;
	sमाप_प्रकार len;
	पूर्णांक fd;

	fd = खोलो("/proc/kpagecgroup", O_RDONLY);
	अगर (fd < 0)
		वापस ret;

	करो अणु
		len = पढ़ो(fd, buf, माप(buf));
	पूर्ण जबतक (len > 0);

	अगर (len == 0)
		ret = KSFT_PASS;

	बंद(fd);
	वापस ret;
पूर्ण

अटल व्योम *pthपढ़ो_रुको_fn(व्योम *arg)
अणु
	sleep(100);
	वापस शून्य;
पूर्ण

अटल पूर्णांक spawn_1000_thपढ़ोs(स्थिर अक्षर *cgroup, व्योम *arg)
अणु
	पूर्णांक nr_thपढ़ोs = 1000;
	pthपढ़ो_t *tinfo;
	अचिन्हित दीर्घ i;
	दीर्घ stack;
	पूर्णांक ret = -1;

	tinfo = सुस्मृति(nr_thपढ़ोs, माप(pthपढ़ो_t));
	अगर (tinfo == शून्य)
		वापस -1;

	क्रम (i = 0; i < nr_thपढ़ोs; i++) अणु
		अगर (pthपढ़ो_create(&tinfo[i], शून्य, &pthपढ़ो_रुको_fn,
				   (व्योम *)i)) अणु
			मुक्त(tinfo);
			वापस(-1);
		पूर्ण
	पूर्ण

	stack = cg_पढ़ो_key_दीर्घ(cgroup, "memory.stat", "kernel_stack ");
	अगर (stack >= 4096 * 1000)
		ret = 0;

	मुक्त(tinfo);
	वापस ret;
पूर्ण

/*
 * The test spawns a process, which spawns 1000 thपढ़ोs. Then it checks
 * that memory.stat's kernel_stack is at least 1000 pages large.
 */
अटल पूर्णांक test_kmem_kernel_stacks(स्थिर अक्षर *root)
अणु
	पूर्णांक ret = KSFT_FAIL;
	अक्षर *cg = शून्य;

	cg = cg_name(root, "kmem_kernel_stacks_test");
	अगर (!cg)
		जाओ cleanup;

	अगर (cg_create(cg))
		जाओ cleanup;

	अगर (cg_run(cg, spawn_1000_thपढ़ोs, शून्य))
		जाओ cleanup;

	ret = KSFT_PASS;
cleanup:
	cg_destroy(cg);
	मुक्त(cg);

	वापस ret;
पूर्ण

/*
 * This test sequentionally creates 30 child cgroups, allocates some
 * kernel memory in each of them, and deletes them. Then it checks
 * that the number of dying cgroups on the parent level is 0.
 */
अटल पूर्णांक test_kmem_dead_cgroups(स्थिर अक्षर *root)
अणु
	पूर्णांक ret = KSFT_FAIL;
	अक्षर *parent;
	दीर्घ dead;
	पूर्णांक i;

	parent = cg_name(root, "kmem_dead_cgroups_test");
	अगर (!parent)
		जाओ cleanup;

	अगर (cg_create(parent))
		जाओ cleanup;

	अगर (cg_ग_लिखो(parent, "cgroup.subtree_control", "+memory"))
		जाओ cleanup;

	अगर (cg_run_in_subcgroups(parent, alloc_dcache, (व्योम *)100, 30))
		जाओ cleanup;

	क्रम (i = 0; i < 5; i++) अणु
		dead = cg_पढ़ो_key_दीर्घ(parent, "cgroup.stat",
					"nr_dying_descendants ");
		अगर (dead == 0) अणु
			ret = KSFT_PASS;
			अवरोध;
		पूर्ण
		/*
		 * Reclaiming cgroups might take some समय,
		 * let's रुको a bit and repeat.
		 */
		sleep(1);
	पूर्ण

cleanup:
	cg_destroy(parent);
	मुक्त(parent);

	वापस ret;
पूर्ण

/*
 * This test creates a sub-tree with 1000 memory cgroups.
 * Then it checks that the memory.current on the parent level
 * is greater than 0 and approximates matches the percpu value
 * from memory.stat.
 */
अटल पूर्णांक test_percpu_basic(स्थिर अक्षर *root)
अणु
	पूर्णांक ret = KSFT_FAIL;
	अक्षर *parent, *child;
	दीर्घ current, percpu;
	पूर्णांक i;

	parent = cg_name(root, "percpu_basic_test");
	अगर (!parent)
		जाओ cleanup;

	अगर (cg_create(parent))
		जाओ cleanup;

	अगर (cg_ग_लिखो(parent, "cgroup.subtree_control", "+memory"))
		जाओ cleanup;

	क्रम (i = 0; i < 1000; i++) अणु
		child = cg_name_indexed(parent, "child", i);
		अगर (!child)
			वापस -1;

		अगर (cg_create(child))
			जाओ cleanup_children;

		मुक्त(child);
	पूर्ण

	current = cg_पढ़ो_दीर्घ(parent, "memory.current");
	percpu = cg_पढ़ो_key_दीर्घ(parent, "memory.stat", "percpu ");

	अगर (current > 0 && percpu > 0 && असल(current - percpu) <
	    MAX_VMSTAT_ERROR)
		ret = KSFT_PASS;
	अन्यथा
		म_लिखो("memory.current %ld\npercpu %ld\n",
		       current, percpu);

cleanup_children:
	क्रम (i = 0; i < 1000; i++) अणु
		child = cg_name_indexed(parent, "child", i);
		cg_destroy(child);
		मुक्त(child);
	पूर्ण

cleanup:
	cg_destroy(parent);
	मुक्त(parent);

	वापस ret;
पूर्ण

#घोषणा T(x) अणु x, #x पूर्ण
काष्ठा kmem_test अणु
	पूर्णांक (*fn)(स्थिर अक्षर *root);
	स्थिर अक्षर *name;
पूर्ण tests[] = अणु
	T(test_kmem_basic),
	T(test_kmem_memcg_deletion),
	T(test_kmem_proc_kpagecgroup),
	T(test_kmem_kernel_stacks),
	T(test_kmem_dead_cgroups),
	T(test_percpu_basic),
पूर्ण;
#अघोषित T

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	अक्षर root[PATH_MAX];
	पूर्णांक i, ret = निकास_सफल;

	अगर (cg_find_unअगरied_root(root, माप(root)))
		ksft_निकास_skip("cgroup v2 isn't mounted\n");

	/*
	 * Check that memory controller is available:
	 * memory is listed in cgroup.controllers
	 */
	अगर (cg_पढ़ो_म_माला(root, "cgroup.controllers", "memory"))
		ksft_निकास_skip("memory controller isn't available\n");

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
