<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Copyright 2019, Michael Ellerman, IBM Corp.
//
// Test that allocating memory beyond the memory limit and then विभाजनing is
// handled correctly, ie. the child is able to access the mappings beyond the
// memory limit and the child's ग_लिखोs are not visible to the parent.

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <sys/mman.h>
#समावेश <sys/types.h>
#समावेश <sys/रुको.h>
#समावेश <unistd.h>

#समावेश "utils.h"


#अगर_अघोषित MAP_FIXED_NOREPLACE
#घोषणा MAP_FIXED_NOREPLACE	MAP_FIXED	// "Should be safe" above 512TB
#पूर्ण_अगर


अटल पूर्णांक test(व्योम)
अणु
	पूर्णांक p2c[2], c2p[2], rc, status, c, *p;
	अचिन्हित दीर्घ page_size;
	pid_t pid;

	page_size = sysconf(_SC_PAGESIZE);
	SKIP_IF(page_size != 65536);

	// Create a mapping at 512TB to allocate an extended_id
	p = mmap((व्योम *)(512ul << 40), page_size, PROT_READ | PROT_WRITE,
		MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED_NOREPLACE, -1, 0);
	अगर (p == MAP_FAILED) अणु
		लिखो_त्रुटि("mmap");
		म_लिखो("Error: couldn't mmap(), confirm kernel has 4TB support?\n");
		वापस 1;
	पूर्ण

	म_लिखो("parent writing %p = 1\n", p);
	*p = 1;

	FAIL_IF(pipe(p2c) == -1 || pipe(c2p) == -1);

	pid = विभाजन();
	अगर (pid == 0) अणु
		FAIL_IF(पढ़ो(p2c[0], &c, 1) != 1);

		pid = getpid();
		म_लिखो("child writing  %p = %d\n", p, pid);
		*p = pid;

		FAIL_IF(ग_लिखो(c2p[1], &c, 1) != 1);
		FAIL_IF(पढ़ो(p2c[0], &c, 1) != 1);
		निकास(0);
	पूर्ण

	c = 0;
	FAIL_IF(ग_लिखो(p2c[1], &c, 1) != 1);
	FAIL_IF(पढ़ो(c2p[0], &c, 1) != 1);

	// Prevent compiler optimisation
	barrier();

	rc = 0;
	म_लिखो("parent reading %p = %d\n", p, *p);
	अगर (*p != 1) अणु
		म_लिखो("Error: BUG! parent saw child's write! *p = %d\n", *p);
		rc = 1;
	पूर्ण

	FAIL_IF(ग_लिखो(p2c[1], &c, 1) != 1);
	FAIL_IF(रुकोpid(pid, &status, 0) == -1);
	FAIL_IF(!WIFEXITED(status) || WEXITSTATUS(status));

	अगर (rc == 0)
		म_लिखो("success: test completed OK\n");

	वापस rc;
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	वापस test_harness(test, "large_vm_fork_separation");
पूर्ण
