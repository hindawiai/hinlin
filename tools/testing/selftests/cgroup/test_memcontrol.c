<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#घोषणा _GNU_SOURCE

#समावेश <linux/सीमा.स>
#समावेश <linux/oom.h>
#समावेश <fcntl.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/स्थिति.स>
#समावेश <sys/types.h>
#समावेश <unistd.h>
#समावेश <sys/socket.h>
#समावेश <sys/रुको.h>
#समावेश <arpa/inet.h>
#समावेश <netinet/in.h>
#समावेश <netdb.h>
#समावेश <त्रुटिसं.स>

#समावेश "../kselftest.h"
#समावेश "cgroup_util.h"

/*
 * This test creates two nested cgroups with and without enabling
 * the memory controller.
 */
अटल पूर्णांक test_memcg_subtree_control(स्थिर अक्षर *root)
अणु
	अक्षर *parent, *child, *parent2 = शून्य, *child2 = शून्य;
	पूर्णांक ret = KSFT_FAIL;
	अक्षर buf[PAGE_SIZE];

	/* Create two nested cgroups with the memory controller enabled */
	parent = cg_name(root, "memcg_test_0");
	child = cg_name(root, "memcg_test_0/memcg_test_1");
	अगर (!parent || !child)
		जाओ cleanup_मुक्त;

	अगर (cg_create(parent))
		जाओ cleanup_मुक्त;

	अगर (cg_ग_लिखो(parent, "cgroup.subtree_control", "+memory"))
		जाओ cleanup_parent;

	अगर (cg_create(child))
		जाओ cleanup_parent;

	अगर (cg_पढ़ो_म_माला(child, "cgroup.controllers", "memory"))
		जाओ cleanup_child;

	/* Create two nested cgroups without enabling memory controller */
	parent2 = cg_name(root, "memcg_test_1");
	child2 = cg_name(root, "memcg_test_1/memcg_test_1");
	अगर (!parent2 || !child2)
		जाओ cleanup_मुक्त2;

	अगर (cg_create(parent2))
		जाओ cleanup_मुक्त2;

	अगर (cg_create(child2))
		जाओ cleanup_parent2;

	अगर (cg_पढ़ो(child2, "cgroup.controllers", buf, माप(buf)))
		जाओ cleanup_all;

	अगर (!cg_पढ़ो_म_माला(child2, "cgroup.controllers", "memory"))
		जाओ cleanup_all;

	ret = KSFT_PASS;

cleanup_all:
	cg_destroy(child2);
cleanup_parent2:
	cg_destroy(parent2);
cleanup_मुक्त2:
	मुक्त(parent2);
	मुक्त(child2);
cleanup_child:
	cg_destroy(child);
cleanup_parent:
	cg_destroy(parent);
cleanup_मुक्त:
	मुक्त(parent);
	मुक्त(child);

	वापस ret;
पूर्ण

अटल पूर्णांक alloc_anon_50M_check(स्थिर अक्षर *cgroup, व्योम *arg)
अणु
	माप_प्रकार size = MB(50);
	अक्षर *buf, *ptr;
	दीर्घ anon, current;
	पूर्णांक ret = -1;

	buf = दो_स्मृति(size);
	क्रम (ptr = buf; ptr < buf + size; ptr += PAGE_SIZE)
		*ptr = 0;

	current = cg_पढ़ो_दीर्घ(cgroup, "memory.current");
	अगर (current < size)
		जाओ cleanup;

	अगर (!values_बंद(size, current, 3))
		जाओ cleanup;

	anon = cg_पढ़ो_key_दीर्घ(cgroup, "memory.stat", "anon ");
	अगर (anon < 0)
		जाओ cleanup;

	अगर (!values_बंद(anon, current, 3))
		जाओ cleanup;

	ret = 0;
cleanup:
	मुक्त(buf);
	वापस ret;
पूर्ण

अटल पूर्णांक alloc_pagecache_50M_check(स्थिर अक्षर *cgroup, व्योम *arg)
अणु
	माप_प्रकार size = MB(50);
	पूर्णांक ret = -1;
	दीर्घ current, file;
	पूर्णांक fd;

	fd = get_temp_fd();
	अगर (fd < 0)
		वापस -1;

	अगर (alloc_pagecache(fd, size))
		जाओ cleanup;

	current = cg_पढ़ो_दीर्घ(cgroup, "memory.current");
	अगर (current < size)
		जाओ cleanup;

	file = cg_पढ़ो_key_दीर्घ(cgroup, "memory.stat", "file ");
	अगर (file < 0)
		जाओ cleanup;

	अगर (!values_बंद(file, current, 10))
		जाओ cleanup;

	ret = 0;

cleanup:
	बंद(fd);
	वापस ret;
पूर्ण

/*
 * This test create a memory cgroup, allocates
 * some anonymous memory and some pagecache
 * and check memory.current and some memory.stat values.
 */
अटल पूर्णांक test_memcg_current(स्थिर अक्षर *root)
अणु
	पूर्णांक ret = KSFT_FAIL;
	दीर्घ current;
	अक्षर *memcg;

	memcg = cg_name(root, "memcg_test");
	अगर (!memcg)
		जाओ cleanup;

	अगर (cg_create(memcg))
		जाओ cleanup;

	current = cg_पढ़ो_दीर्घ(memcg, "memory.current");
	अगर (current != 0)
		जाओ cleanup;

	अगर (cg_run(memcg, alloc_anon_50M_check, शून्य))
		जाओ cleanup;

	अगर (cg_run(memcg, alloc_pagecache_50M_check, शून्य))
		जाओ cleanup;

	ret = KSFT_PASS;

cleanup:
	cg_destroy(memcg);
	मुक्त(memcg);

	वापस ret;
पूर्ण

अटल पूर्णांक alloc_pagecache_50M(स्थिर अक्षर *cgroup, व्योम *arg)
अणु
	पूर्णांक fd = (दीर्घ)arg;

	वापस alloc_pagecache(fd, MB(50));
पूर्ण

अटल पूर्णांक alloc_pagecache_50M_noनिकास(स्थिर अक्षर *cgroup, व्योम *arg)
अणु
	पूर्णांक fd = (दीर्घ)arg;
	पूर्णांक ppid = getppid();

	अगर (alloc_pagecache(fd, MB(50)))
		वापस -1;

	जबतक (getppid() == ppid)
		sleep(1);

	वापस 0;
पूर्ण

अटल पूर्णांक alloc_anon_noनिकास(स्थिर अक्षर *cgroup, व्योम *arg)
अणु
	पूर्णांक ppid = getppid();

	अगर (alloc_anon(cgroup, arg))
		वापस -1;

	जबतक (getppid() == ppid)
		sleep(1);

	वापस 0;
पूर्ण

/*
 * Wait until processes are समाप्तed asynchronously by the OOM समाप्तer
 * If we exceed a समयout, fail.
 */
अटल पूर्णांक cg_test_proc_समाप्तed(स्थिर अक्षर *cgroup)
अणु
	पूर्णांक limit;

	क्रम (limit = 10; limit > 0; limit--) अणु
		अगर (cg_पढ़ो_म_भेद(cgroup, "cgroup.procs", "") == 0)
			वापस 0;

		usleep(100000);
	पूर्ण
	वापस -1;
पूर्ण

/*
 * First, this test creates the following hierarchy:
 * A       memory.min = 50M,  memory.max = 200M
 * A/B     memory.min = 50M,  memory.current = 50M
 * A/B/C   memory.min = 75M,  memory.current = 50M
 * A/B/D   memory.min = 25M,  memory.current = 50M
 * A/B/E   memory.min = 500M, memory.current = 0
 * A/B/F   memory.min = 0,    memory.current = 50M
 *
 * Usages are pagecache, but the test keeps a running
 * process in every leaf cgroup.
 * Then it creates A/G and creates a signअगरicant
 * memory pressure in it.
 *
 * A/B    memory.current ~= 50M
 * A/B/C  memory.current ~= 33M
 * A/B/D  memory.current ~= 17M
 * A/B/E  memory.current ~= 0
 *
 * After that it tries to allocate more than there is
 * unरक्षित memory in A available, and checks
 * checks that memory.min protects pagecache even
 * in this हाल.
 */
अटल पूर्णांक test_memcg_min(स्थिर अक्षर *root)
अणु
	पूर्णांक ret = KSFT_FAIL;
	अक्षर *parent[3] = अणुशून्यपूर्ण;
	अक्षर *children[4] = अणुशून्यपूर्ण;
	दीर्घ c[4];
	पूर्णांक i, attempts;
	पूर्णांक fd;

	fd = get_temp_fd();
	अगर (fd < 0)
		जाओ cleanup;

	parent[0] = cg_name(root, "memcg_test_0");
	अगर (!parent[0])
		जाओ cleanup;

	parent[1] = cg_name(parent[0], "memcg_test_1");
	अगर (!parent[1])
		जाओ cleanup;

	parent[2] = cg_name(parent[0], "memcg_test_2");
	अगर (!parent[2])
		जाओ cleanup;

	अगर (cg_create(parent[0]))
		जाओ cleanup;

	अगर (cg_पढ़ो_दीर्घ(parent[0], "memory.min")) अणु
		ret = KSFT_SKIP;
		जाओ cleanup;
	पूर्ण

	अगर (cg_ग_लिखो(parent[0], "cgroup.subtree_control", "+memory"))
		जाओ cleanup;

	अगर (cg_ग_लिखो(parent[0], "memory.max", "200M"))
		जाओ cleanup;

	अगर (cg_ग_लिखो(parent[0], "memory.swap.max", "0"))
		जाओ cleanup;

	अगर (cg_create(parent[1]))
		जाओ cleanup;

	अगर (cg_ग_लिखो(parent[1], "cgroup.subtree_control", "+memory"))
		जाओ cleanup;

	अगर (cg_create(parent[2]))
		जाओ cleanup;

	क्रम (i = 0; i < ARRAY_SIZE(children); i++) अणु
		children[i] = cg_name_indexed(parent[1], "child_memcg", i);
		अगर (!children[i])
			जाओ cleanup;

		अगर (cg_create(children[i]))
			जाओ cleanup;

		अगर (i == 2)
			जारी;

		cg_run_noरुको(children[i], alloc_pagecache_50M_noनिकास,
			      (व्योम *)(दीर्घ)fd);
	पूर्ण

	अगर (cg_ग_लिखो(parent[0], "memory.min", "50M"))
		जाओ cleanup;
	अगर (cg_ग_लिखो(parent[1], "memory.min", "50M"))
		जाओ cleanup;
	अगर (cg_ग_लिखो(children[0], "memory.min", "75M"))
		जाओ cleanup;
	अगर (cg_ग_लिखो(children[1], "memory.min", "25M"))
		जाओ cleanup;
	अगर (cg_ग_लिखो(children[2], "memory.min", "500M"))
		जाओ cleanup;
	अगर (cg_ग_लिखो(children[3], "memory.min", "0"))
		जाओ cleanup;

	attempts = 0;
	जबतक (!values_बंद(cg_पढ़ो_दीर्घ(parent[1], "memory.current"),
			     MB(150), 3)) अणु
		अगर (attempts++ > 5)
			अवरोध;
		sleep(1);
	पूर्ण

	अगर (cg_run(parent[2], alloc_anon, (व्योम *)MB(148)))
		जाओ cleanup;

	अगर (!values_बंद(cg_पढ़ो_दीर्घ(parent[1], "memory.current"), MB(50), 3))
		जाओ cleanup;

	क्रम (i = 0; i < ARRAY_SIZE(children); i++)
		c[i] = cg_पढ़ो_दीर्घ(children[i], "memory.current");

	अगर (!values_बंद(c[0], MB(33), 10))
		जाओ cleanup;

	अगर (!values_बंद(c[1], MB(17), 10))
		जाओ cleanup;

	अगर (!values_बंद(c[2], 0, 1))
		जाओ cleanup;

	अगर (!cg_run(parent[2], alloc_anon, (व्योम *)MB(170)))
		जाओ cleanup;

	अगर (!values_बंद(cg_पढ़ो_दीर्घ(parent[1], "memory.current"), MB(50), 3))
		जाओ cleanup;

	ret = KSFT_PASS;

cleanup:
	क्रम (i = ARRAY_SIZE(children) - 1; i >= 0; i--) अणु
		अगर (!children[i])
			जारी;

		cg_destroy(children[i]);
		मुक्त(children[i]);
	पूर्ण

	क्रम (i = ARRAY_SIZE(parent) - 1; i >= 0; i--) अणु
		अगर (!parent[i])
			जारी;

		cg_destroy(parent[i]);
		मुक्त(parent[i]);
	पूर्ण
	बंद(fd);
	वापस ret;
पूर्ण

/*
 * First, this test creates the following hierarchy:
 * A       memory.low = 50M,  memory.max = 200M
 * A/B     memory.low = 50M,  memory.current = 50M
 * A/B/C   memory.low = 75M,  memory.current = 50M
 * A/B/D   memory.low = 25M,  memory.current = 50M
 * A/B/E   memory.low = 500M, memory.current = 0
 * A/B/F   memory.low = 0,    memory.current = 50M
 *
 * Usages are pagecache.
 * Then it creates A/G an creates a signअगरicant
 * memory pressure in it.
 *
 * Then it checks actual memory usages and expects that:
 * A/B    memory.current ~= 50M
 * A/B/   memory.current ~= 33M
 * A/B/D  memory.current ~= 17M
 * A/B/E  memory.current ~= 0
 *
 * After that it tries to allocate more than there is
 * unरक्षित memory in A available,
 * and checks low and oom events in memory.events.
 */
अटल पूर्णांक test_memcg_low(स्थिर अक्षर *root)
अणु
	पूर्णांक ret = KSFT_FAIL;
	अक्षर *parent[3] = अणुशून्यपूर्ण;
	अक्षर *children[4] = अणुशून्यपूर्ण;
	दीर्घ low, oom;
	दीर्घ c[4];
	पूर्णांक i;
	पूर्णांक fd;

	fd = get_temp_fd();
	अगर (fd < 0)
		जाओ cleanup;

	parent[0] = cg_name(root, "memcg_test_0");
	अगर (!parent[0])
		जाओ cleanup;

	parent[1] = cg_name(parent[0], "memcg_test_1");
	अगर (!parent[1])
		जाओ cleanup;

	parent[2] = cg_name(parent[0], "memcg_test_2");
	अगर (!parent[2])
		जाओ cleanup;

	अगर (cg_create(parent[0]))
		जाओ cleanup;

	अगर (cg_पढ़ो_दीर्घ(parent[0], "memory.low"))
		जाओ cleanup;

	अगर (cg_ग_लिखो(parent[0], "cgroup.subtree_control", "+memory"))
		जाओ cleanup;

	अगर (cg_ग_लिखो(parent[0], "memory.max", "200M"))
		जाओ cleanup;

	अगर (cg_ग_लिखो(parent[0], "memory.swap.max", "0"))
		जाओ cleanup;

	अगर (cg_create(parent[1]))
		जाओ cleanup;

	अगर (cg_ग_लिखो(parent[1], "cgroup.subtree_control", "+memory"))
		जाओ cleanup;

	अगर (cg_create(parent[2]))
		जाओ cleanup;

	क्रम (i = 0; i < ARRAY_SIZE(children); i++) अणु
		children[i] = cg_name_indexed(parent[1], "child_memcg", i);
		अगर (!children[i])
			जाओ cleanup;

		अगर (cg_create(children[i]))
			जाओ cleanup;

		अगर (i == 2)
			जारी;

		अगर (cg_run(children[i], alloc_pagecache_50M, (व्योम *)(दीर्घ)fd))
			जाओ cleanup;
	पूर्ण

	अगर (cg_ग_लिखो(parent[0], "memory.low", "50M"))
		जाओ cleanup;
	अगर (cg_ग_लिखो(parent[1], "memory.low", "50M"))
		जाओ cleanup;
	अगर (cg_ग_लिखो(children[0], "memory.low", "75M"))
		जाओ cleanup;
	अगर (cg_ग_लिखो(children[1], "memory.low", "25M"))
		जाओ cleanup;
	अगर (cg_ग_लिखो(children[2], "memory.low", "500M"))
		जाओ cleanup;
	अगर (cg_ग_लिखो(children[3], "memory.low", "0"))
		जाओ cleanup;

	अगर (cg_run(parent[2], alloc_anon, (व्योम *)MB(148)))
		जाओ cleanup;

	अगर (!values_बंद(cg_पढ़ो_दीर्घ(parent[1], "memory.current"), MB(50), 3))
		जाओ cleanup;

	क्रम (i = 0; i < ARRAY_SIZE(children); i++)
		c[i] = cg_पढ़ो_दीर्घ(children[i], "memory.current");

	अगर (!values_बंद(c[0], MB(33), 10))
		जाओ cleanup;

	अगर (!values_बंद(c[1], MB(17), 10))
		जाओ cleanup;

	अगर (!values_बंद(c[2], 0, 1))
		जाओ cleanup;

	अगर (cg_run(parent[2], alloc_anon, (व्योम *)MB(166))) अणु
		ख_लिखो(मानक_त्रुटि,
			"memory.low prevents from allocating anon memory\n");
		जाओ cleanup;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(children); i++) अणु
		oom = cg_पढ़ो_key_दीर्घ(children[i], "memory.events", "oom ");
		low = cg_पढ़ो_key_दीर्घ(children[i], "memory.events", "low ");

		अगर (oom)
			जाओ cleanup;
		अगर (i < 2 && low <= 0)
			जाओ cleanup;
		अगर (i >= 2 && low)
			जाओ cleanup;
	पूर्ण

	ret = KSFT_PASS;

cleanup:
	क्रम (i = ARRAY_SIZE(children) - 1; i >= 0; i--) अणु
		अगर (!children[i])
			जारी;

		cg_destroy(children[i]);
		मुक्त(children[i]);
	पूर्ण

	क्रम (i = ARRAY_SIZE(parent) - 1; i >= 0; i--) अणु
		अगर (!parent[i])
			जारी;

		cg_destroy(parent[i]);
		मुक्त(parent[i]);
	पूर्ण
	बंद(fd);
	वापस ret;
पूर्ण

अटल पूर्णांक alloc_pagecache_max_30M(स्थिर अक्षर *cgroup, व्योम *arg)
अणु
	माप_प्रकार size = MB(50);
	पूर्णांक ret = -1;
	दीर्घ current;
	पूर्णांक fd;

	fd = get_temp_fd();
	अगर (fd < 0)
		वापस -1;

	अगर (alloc_pagecache(fd, size))
		जाओ cleanup;

	current = cg_पढ़ो_दीर्घ(cgroup, "memory.current");
	अगर (current <= MB(29) || current > MB(30))
		जाओ cleanup;

	ret = 0;

cleanup:
	बंद(fd);
	वापस ret;

पूर्ण

/*
 * This test checks that memory.high limits the amount of
 * memory which can be consumed by either anonymous memory
 * or pagecache.
 */
अटल पूर्णांक test_memcg_high(स्थिर अक्षर *root)
अणु
	पूर्णांक ret = KSFT_FAIL;
	अक्षर *memcg;
	दीर्घ high;

	memcg = cg_name(root, "memcg_test");
	अगर (!memcg)
		जाओ cleanup;

	अगर (cg_create(memcg))
		जाओ cleanup;

	अगर (cg_पढ़ो_म_भेद(memcg, "memory.high", "max\n"))
		जाओ cleanup;

	अगर (cg_ग_लिखो(memcg, "memory.swap.max", "0"))
		जाओ cleanup;

	अगर (cg_ग_लिखो(memcg, "memory.high", "30M"))
		जाओ cleanup;

	अगर (cg_run(memcg, alloc_anon, (व्योम *)MB(100)))
		जाओ cleanup;

	अगर (!cg_run(memcg, alloc_pagecache_50M_check, शून्य))
		जाओ cleanup;

	अगर (cg_run(memcg, alloc_pagecache_max_30M, शून्य))
		जाओ cleanup;

	high = cg_पढ़ो_key_दीर्घ(memcg, "memory.events", "high ");
	अगर (high <= 0)
		जाओ cleanup;

	ret = KSFT_PASS;

cleanup:
	cg_destroy(memcg);
	मुक्त(memcg);

	वापस ret;
पूर्ण

/*
 * This test checks that memory.max limits the amount of
 * memory which can be consumed by either anonymous memory
 * or pagecache.
 */
अटल पूर्णांक test_memcg_max(स्थिर अक्षर *root)
अणु
	पूर्णांक ret = KSFT_FAIL;
	अक्षर *memcg;
	दीर्घ current, max;

	memcg = cg_name(root, "memcg_test");
	अगर (!memcg)
		जाओ cleanup;

	अगर (cg_create(memcg))
		जाओ cleanup;

	अगर (cg_पढ़ो_म_भेद(memcg, "memory.max", "max\n"))
		जाओ cleanup;

	अगर (cg_ग_लिखो(memcg, "memory.swap.max", "0"))
		जाओ cleanup;

	अगर (cg_ग_लिखो(memcg, "memory.max", "30M"))
		जाओ cleanup;

	/* Should be समाप्तed by OOM समाप्तer */
	अगर (!cg_run(memcg, alloc_anon, (व्योम *)MB(100)))
		जाओ cleanup;

	अगर (cg_run(memcg, alloc_pagecache_max_30M, शून्य))
		जाओ cleanup;

	current = cg_पढ़ो_दीर्घ(memcg, "memory.current");
	अगर (current > MB(30) || !current)
		जाओ cleanup;

	max = cg_पढ़ो_key_दीर्घ(memcg, "memory.events", "max ");
	अगर (max <= 0)
		जाओ cleanup;

	ret = KSFT_PASS;

cleanup:
	cg_destroy(memcg);
	मुक्त(memcg);

	वापस ret;
पूर्ण

अटल पूर्णांक alloc_anon_50M_check_swap(स्थिर अक्षर *cgroup, व्योम *arg)
अणु
	दीर्घ mem_max = (दीर्घ)arg;
	माप_प्रकार size = MB(50);
	अक्षर *buf, *ptr;
	दीर्घ mem_current, swap_current;
	पूर्णांक ret = -1;

	buf = दो_स्मृति(size);
	क्रम (ptr = buf; ptr < buf + size; ptr += PAGE_SIZE)
		*ptr = 0;

	mem_current = cg_पढ़ो_दीर्घ(cgroup, "memory.current");
	अगर (!mem_current || !values_बंद(mem_current, mem_max, 3))
		जाओ cleanup;

	swap_current = cg_पढ़ो_दीर्घ(cgroup, "memory.swap.current");
	अगर (!swap_current ||
	    !values_बंद(mem_current + swap_current, size, 3))
		जाओ cleanup;

	ret = 0;
cleanup:
	मुक्त(buf);
	वापस ret;
पूर्ण

/*
 * This test checks that memory.swap.max limits the amount of
 * anonymous memory which can be swapped out.
 */
अटल पूर्णांक test_memcg_swap_max(स्थिर अक्षर *root)
अणु
	पूर्णांक ret = KSFT_FAIL;
	अक्षर *memcg;
	दीर्घ max;

	अगर (!is_swap_enabled())
		वापस KSFT_SKIP;

	memcg = cg_name(root, "memcg_test");
	अगर (!memcg)
		जाओ cleanup;

	अगर (cg_create(memcg))
		जाओ cleanup;

	अगर (cg_पढ़ो_दीर्घ(memcg, "memory.swap.current")) अणु
		ret = KSFT_SKIP;
		जाओ cleanup;
	पूर्ण

	अगर (cg_पढ़ो_म_भेद(memcg, "memory.max", "max\n"))
		जाओ cleanup;

	अगर (cg_पढ़ो_म_भेद(memcg, "memory.swap.max", "max\n"))
		जाओ cleanup;

	अगर (cg_ग_लिखो(memcg, "memory.swap.max", "30M"))
		जाओ cleanup;

	अगर (cg_ग_लिखो(memcg, "memory.max", "30M"))
		जाओ cleanup;

	/* Should be समाप्तed by OOM समाप्तer */
	अगर (!cg_run(memcg, alloc_anon, (व्योम *)MB(100)))
		जाओ cleanup;

	अगर (cg_पढ़ो_key_दीर्घ(memcg, "memory.events", "oom ") != 1)
		जाओ cleanup;

	अगर (cg_पढ़ो_key_दीर्घ(memcg, "memory.events", "oom_kill ") != 1)
		जाओ cleanup;

	अगर (cg_run(memcg, alloc_anon_50M_check_swap, (व्योम *)MB(30)))
		जाओ cleanup;

	max = cg_पढ़ो_key_दीर्घ(memcg, "memory.events", "max ");
	अगर (max <= 0)
		जाओ cleanup;

	ret = KSFT_PASS;

cleanup:
	cg_destroy(memcg);
	मुक्त(memcg);

	वापस ret;
पूर्ण

/*
 * This test disables swapping and tries to allocate anonymous memory
 * up to OOM. Then it checks क्रम oom and oom_समाप्त events in
 * memory.events.
 */
अटल पूर्णांक test_memcg_oom_events(स्थिर अक्षर *root)
अणु
	पूर्णांक ret = KSFT_FAIL;
	अक्षर *memcg;

	memcg = cg_name(root, "memcg_test");
	अगर (!memcg)
		जाओ cleanup;

	अगर (cg_create(memcg))
		जाओ cleanup;

	अगर (cg_ग_लिखो(memcg, "memory.max", "30M"))
		जाओ cleanup;

	अगर (cg_ग_लिखो(memcg, "memory.swap.max", "0"))
		जाओ cleanup;

	अगर (!cg_run(memcg, alloc_anon, (व्योम *)MB(100)))
		जाओ cleanup;

	अगर (cg_पढ़ो_म_भेद(memcg, "cgroup.procs", ""))
		जाओ cleanup;

	अगर (cg_पढ़ो_key_दीर्घ(memcg, "memory.events", "oom ") != 1)
		जाओ cleanup;

	अगर (cg_पढ़ो_key_दीर्घ(memcg, "memory.events", "oom_kill ") != 1)
		जाओ cleanup;

	ret = KSFT_PASS;

cleanup:
	cg_destroy(memcg);
	मुक्त(memcg);

	वापस ret;
पूर्ण

काष्ठा tcp_server_args अणु
	अचिन्हित लघु port;
	पूर्णांक ctl[2];
पूर्ण;

अटल पूर्णांक tcp_server(स्थिर अक्षर *cgroup, व्योम *arg)
अणु
	काष्ठा tcp_server_args *srv_args = arg;
	काष्ठा sockaddr_in6 saddr = अणु 0 पूर्ण;
	socklen_t slen = माप(saddr);
	पूर्णांक sk, client_sk, ctl_fd, yes = 1, ret = -1;

	बंद(srv_args->ctl[0]);
	ctl_fd = srv_args->ctl[1];

	saddr.sin6_family = AF_INET6;
	saddr.sin6_addr = in6addr_any;
	saddr.sin6_port = htons(srv_args->port);

	sk = socket(AF_INET6, SOCK_STREAM, 0);
	अगर (sk < 0)
		वापस ret;

	अगर (setsockopt(sk, SOL_SOCKET, SO_REUSEADDR, &yes, माप(yes)) < 0)
		जाओ cleanup;

	अगर (bind(sk, (काष्ठा sockaddr *)&saddr, slen)) अणु
		ग_लिखो(ctl_fd, &त्रुटि_सं, माप(त्रुटि_सं));
		जाओ cleanup;
	पूर्ण

	अगर (listen(sk, 1))
		जाओ cleanup;

	ret = 0;
	अगर (ग_लिखो(ctl_fd, &ret, माप(ret)) != माप(ret)) अणु
		ret = -1;
		जाओ cleanup;
	पूर्ण

	client_sk = accept(sk, शून्य, शून्य);
	अगर (client_sk < 0)
		जाओ cleanup;

	ret = -1;
	क्रम (;;) अणु
		uपूर्णांक8_t buf[0x100000];

		अगर (ग_लिखो(client_sk, buf, माप(buf)) <= 0) अणु
			अगर (त्रुटि_सं == ECONNRESET)
				ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	बंद(client_sk);

cleanup:
	बंद(sk);
	वापस ret;
पूर्ण

अटल पूर्णांक tcp_client(स्थिर अक्षर *cgroup, अचिन्हित लघु port)
अणु
	स्थिर अक्षर server[] = "localhost";
	काष्ठा addrinfo *ai;
	अक्षर servport[6];
	पूर्णांक retries = 0x10; /* nice round number */
	पूर्णांक sk, ret;

	snम_लिखो(servport, माप(servport), "%hd", port);
	ret = getaddrinfo(server, servport, शून्य, &ai);
	अगर (ret)
		वापस ret;

	sk = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
	अगर (sk < 0)
		जाओ मुक्त_ainfo;

	ret = connect(sk, ai->ai_addr, ai->ai_addrlen);
	अगर (ret < 0)
		जाओ बंद_sk;

	ret = KSFT_FAIL;
	जबतक (retries--) अणु
		uपूर्णांक8_t buf[0x100000];
		दीर्घ current, sock;

		अगर (पढ़ो(sk, buf, माप(buf)) <= 0)
			जाओ बंद_sk;

		current = cg_पढ़ो_दीर्घ(cgroup, "memory.current");
		sock = cg_पढ़ो_key_दीर्घ(cgroup, "memory.stat", "sock ");

		अगर (current < 0 || sock < 0)
			जाओ बंद_sk;

		अगर (current < sock)
			जाओ बंद_sk;

		अगर (values_बंद(current, sock, 10)) अणु
			ret = KSFT_PASS;
			अवरोध;
		पूर्ण
	पूर्ण

बंद_sk:
	बंद(sk);
मुक्त_ainfo:
	मुक्तaddrinfo(ai);
	वापस ret;
पूर्ण

/*
 * This test checks socket memory accounting.
 * The test विभाजनs a TCP server listens on a अक्रमom port between 1000
 * and 61000. Once it माला_लो a client connection, it starts writing to
 * its socket.
 * The TCP client पूर्णांकerleaves पढ़ोs from the socket with check whether
 * memory.current and memory.stat.sock are similar.
 */
अटल पूर्णांक test_memcg_sock(स्थिर अक्षर *root)
अणु
	पूर्णांक bind_retries = 5, ret = KSFT_FAIL, pid, err;
	अचिन्हित लघु port;
	अक्षर *memcg;

	memcg = cg_name(root, "memcg_test");
	अगर (!memcg)
		जाओ cleanup;

	अगर (cg_create(memcg))
		जाओ cleanup;

	जबतक (bind_retries--) अणु
		काष्ठा tcp_server_args args;

		अगर (pipe(args.ctl))
			जाओ cleanup;

		port = args.port = 1000 + अक्रम() % 60000;

		pid = cg_run_noरुको(memcg, tcp_server, &args);
		अगर (pid < 0)
			जाओ cleanup;

		बंद(args.ctl[1]);
		अगर (पढ़ो(args.ctl[0], &err, माप(err)) != माप(err))
			जाओ cleanup;
		बंद(args.ctl[0]);

		अगर (!err)
			अवरोध;
		अगर (err != EADDRINUSE)
			जाओ cleanup;

		रुकोpid(pid, शून्य, 0);
	पूर्ण

	अगर (err == EADDRINUSE) अणु
		ret = KSFT_SKIP;
		जाओ cleanup;
	पूर्ण

	अगर (tcp_client(memcg, port) != KSFT_PASS)
		जाओ cleanup;

	रुकोpid(pid, &err, 0);
	अगर (WEXITSTATUS(err))
		जाओ cleanup;

	अगर (cg_पढ़ो_दीर्घ(memcg, "memory.current") < 0)
		जाओ cleanup;

	अगर (cg_पढ़ो_key_दीर्घ(memcg, "memory.stat", "sock "))
		जाओ cleanup;

	ret = KSFT_PASS;

cleanup:
	cg_destroy(memcg);
	मुक्त(memcg);

	वापस ret;
पूर्ण

/*
 * This test disables swapping and tries to allocate anonymous memory
 * up to OOM with memory.group.oom set. Then it checks that all
 * processes in the leaf (but not the parent) were समाप्तed.
 */
अटल पूर्णांक test_memcg_oom_group_leaf_events(स्थिर अक्षर *root)
अणु
	पूर्णांक ret = KSFT_FAIL;
	अक्षर *parent, *child;

	parent = cg_name(root, "memcg_test_0");
	child = cg_name(root, "memcg_test_0/memcg_test_1");

	अगर (!parent || !child)
		जाओ cleanup;

	अगर (cg_create(parent))
		जाओ cleanup;

	अगर (cg_create(child))
		जाओ cleanup;

	अगर (cg_ग_लिखो(parent, "cgroup.subtree_control", "+memory"))
		जाओ cleanup;

	अगर (cg_ग_लिखो(child, "memory.max", "50M"))
		जाओ cleanup;

	अगर (cg_ग_लिखो(child, "memory.swap.max", "0"))
		जाओ cleanup;

	अगर (cg_ग_लिखो(child, "memory.oom.group", "1"))
		जाओ cleanup;

	cg_run_noरुको(parent, alloc_anon_noनिकास, (व्योम *) MB(60));
	cg_run_noरुको(child, alloc_anon_noनिकास, (व्योम *) MB(1));
	cg_run_noरुको(child, alloc_anon_noनिकास, (व्योम *) MB(1));
	अगर (!cg_run(child, alloc_anon, (व्योम *)MB(100)))
		जाओ cleanup;

	अगर (cg_test_proc_समाप्तed(child))
		जाओ cleanup;

	अगर (cg_पढ़ो_key_दीर्घ(child, "memory.events", "oom_kill ") <= 0)
		जाओ cleanup;

	अगर (cg_पढ़ो_key_दीर्घ(parent, "memory.events", "oom_kill ") != 0)
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
 * This test disables swapping and tries to allocate anonymous memory
 * up to OOM with memory.group.oom set. Then it checks that all
 * processes in the parent and leaf were समाप्तed.
 */
अटल पूर्णांक test_memcg_oom_group_parent_events(स्थिर अक्षर *root)
अणु
	पूर्णांक ret = KSFT_FAIL;
	अक्षर *parent, *child;

	parent = cg_name(root, "memcg_test_0");
	child = cg_name(root, "memcg_test_0/memcg_test_1");

	अगर (!parent || !child)
		जाओ cleanup;

	अगर (cg_create(parent))
		जाओ cleanup;

	अगर (cg_create(child))
		जाओ cleanup;

	अगर (cg_ग_लिखो(parent, "memory.max", "80M"))
		जाओ cleanup;

	अगर (cg_ग_लिखो(parent, "memory.swap.max", "0"))
		जाओ cleanup;

	अगर (cg_ग_लिखो(parent, "memory.oom.group", "1"))
		जाओ cleanup;

	cg_run_noरुको(parent, alloc_anon_noनिकास, (व्योम *) MB(60));
	cg_run_noरुको(child, alloc_anon_noनिकास, (व्योम *) MB(1));
	cg_run_noरुको(child, alloc_anon_noनिकास, (व्योम *) MB(1));

	अगर (!cg_run(child, alloc_anon, (व्योम *)MB(100)))
		जाओ cleanup;

	अगर (cg_test_proc_समाप्तed(child))
		जाओ cleanup;
	अगर (cg_test_proc_समाप्तed(parent))
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
 * This test disables swapping and tries to allocate anonymous memory
 * up to OOM with memory.group.oom set. Then it checks that all
 * processes were समाप्तed except those set with OOM_SCORE_ADJ_MIN
 */
अटल पूर्णांक test_memcg_oom_group_score_events(स्थिर अक्षर *root)
अणु
	पूर्णांक ret = KSFT_FAIL;
	अक्षर *memcg;
	पूर्णांक safe_pid;

	memcg = cg_name(root, "memcg_test_0");

	अगर (!memcg)
		जाओ cleanup;

	अगर (cg_create(memcg))
		जाओ cleanup;

	अगर (cg_ग_लिखो(memcg, "memory.max", "50M"))
		जाओ cleanup;

	अगर (cg_ग_लिखो(memcg, "memory.swap.max", "0"))
		जाओ cleanup;

	अगर (cg_ग_लिखो(memcg, "memory.oom.group", "1"))
		जाओ cleanup;

	safe_pid = cg_run_noरुको(memcg, alloc_anon_noनिकास, (व्योम *) MB(1));
	अगर (set_oom_adj_score(safe_pid, OOM_SCORE_ADJ_MIN))
		जाओ cleanup;

	cg_run_noरुको(memcg, alloc_anon_noनिकास, (व्योम *) MB(1));
	अगर (!cg_run(memcg, alloc_anon, (व्योम *)MB(100)))
		जाओ cleanup;

	अगर (cg_पढ़ो_key_दीर्घ(memcg, "memory.events", "oom_kill ") != 3)
		जाओ cleanup;

	अगर (समाप्त(safe_pid, SIGKILL))
		जाओ cleanup;

	ret = KSFT_PASS;

cleanup:
	अगर (memcg)
		cg_destroy(memcg);
	मुक्त(memcg);

	वापस ret;
पूर्ण


#घोषणा T(x) अणु x, #x पूर्ण
काष्ठा memcg_test अणु
	पूर्णांक (*fn)(स्थिर अक्षर *root);
	स्थिर अक्षर *name;
पूर्ण tests[] = अणु
	T(test_memcg_subtree_control),
	T(test_memcg_current),
	T(test_memcg_min),
	T(test_memcg_low),
	T(test_memcg_high),
	T(test_memcg_max),
	T(test_memcg_oom_events),
	T(test_memcg_swap_max),
	T(test_memcg_sock),
	T(test_memcg_oom_group_leaf_events),
	T(test_memcg_oom_group_parent_events),
	T(test_memcg_oom_group_score_events),
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
