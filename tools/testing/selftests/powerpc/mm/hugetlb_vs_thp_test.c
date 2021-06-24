<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <मानकपन.स>
#समावेश <sys/mman.h>
#समावेश <unistd.h>

#समावेश "utils.h"

/* This must match the huge page & THP size */
#घोषणा SIZE	(16 * 1024 * 1024)

अटल पूर्णांक test_body(व्योम)
अणु
	व्योम *addr;
	अक्षर *p;

	addr = (व्योम *)0xa0000000;

	p = mmap(addr, SIZE, PROT_READ | PROT_WRITE,
		 MAP_HUGETLB | MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	अगर (p != MAP_FAILED) अणु
		/*
		 * Typically the mmap will fail because no huge pages are
		 * allocated on the प्रणाली. But अगर there are huge pages
		 * allocated the mmap will succeed. That's fine too, we just
		 * munmap here beक्रमe continuing.  munmap() length of
		 * MAP_HUGETLB memory must be hugepage aligned.
		 */
		अगर (munmap(addr, SIZE)) अणु
			लिखो_त्रुटि("munmap");
			वापस 1;
		पूर्ण
	पूर्ण

	p = mmap(addr, SIZE, PROT_READ | PROT_WRITE,
		 MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	अगर (p == MAP_FAILED) अणु
		म_लिखो("Mapping failed @ %p\n", addr);
		लिखो_त्रुटि("mmap");
		वापस 1;
	पूर्ण

	/*
	 * Either a user or kernel access is sufficient to trigger the bug.
	 * A kernel access is easier to spot & debug, as it will trigger the
	 * softlockup or RCU stall detectors, and when the प्रणाली is kicked
	 * पूर्णांकo xmon we get a backtrace in the kernel.
	 *
	 * A good option is:
	 *  अ_लोwd(p, SIZE);
	 *
	 * For the purposes of this testहाल it's preferable to spin in
	 * userspace, so the harness can समाप्त us अगर we get stuck. That way we
	 * see a test failure rather than a dead प्रणाली.
	 */
	*p = 0xf;

	munmap(addr, SIZE);

	वापस 0;
पूर्ण

अटल पूर्णांक test_मुख्य(व्योम)
अणु
	पूर्णांक i;

	/* 10,000 because it's a "bunch", and completes reasonably quickly */
	क्रम (i = 0; i < 10000; i++)
		अगर (test_body())
			वापस 1;

	वापस 0;
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	वापस test_harness(test_मुख्य, "hugetlb_vs_thp");
पूर्ण
