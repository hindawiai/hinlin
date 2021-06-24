<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Authors: Kirill A. Shutemov <kirill.shutemov@linux.पूर्णांकel.com>
 * Authors: Aneesh Kumar K.V <aneesh.kumar@linux.vnet.ibm.com>
 */

#समावेश <मानकपन.स>
#समावेश <sys/mman.h>
#समावेश <माला.स>

#घोषणा ARRAY_SIZE(arr) (माप(arr) / माप((arr)[0]))

#अगर_घोषित __घातerpc64__
#घोषणा PAGE_SIZE	(64 << 10)
/*
 * This will work with 16M and 2M hugepage size
 */
#घोषणा HUGETLB_SIZE	(16 << 20)
#अन्यथा
#घोषणा PAGE_SIZE	(4 << 10)
#घोषणा HUGETLB_SIZE	(2 << 20)
#पूर्ण_अगर

/*
 * >= 128TB is the hपूर्णांक addr value we used to select
 * large address space.
 */
#घोषणा ADDR_SWITCH_HINT (1UL << 47)
#घोषणा LOW_ADDR	((व्योम *) (1UL << 30))
#घोषणा HIGH_ADDR	((व्योम *) (1UL << 48))

काष्ठा testहाल अणु
	व्योम *addr;
	अचिन्हित दीर्घ size;
	अचिन्हित दीर्घ flags;
	स्थिर अक्षर *msg;
	अचिन्हित पूर्णांक low_addr_required:1;
	अचिन्हित पूर्णांक keep_mapped:1;
पूर्ण;

अटल काष्ठा testहाल testहालs[] = अणु
	अणु
		/*
		 * If stack is moved, we could possibly allocate
		 * this at the requested address.
		 */
		.addr = ((व्योम *)(ADDR_SWITCH_HINT - PAGE_SIZE)),
		.size = PAGE_SIZE,
		.flags = MAP_PRIVATE | MAP_ANONYMOUS,
		.msg = "mmap(ADDR_SWITCH_HINT - PAGE_SIZE, PAGE_SIZE)",
		.low_addr_required = 1,
	पूर्ण,
	अणु
		/*
		 * We should never allocate at the requested address or above it
		 * The len cross the 128TB boundary. Without MAP_FIXED
		 * we will always search in the lower address space.
		 */
		.addr = ((व्योम *)(ADDR_SWITCH_HINT - PAGE_SIZE)),
		.size = 2 * PAGE_SIZE,
		.flags = MAP_PRIVATE | MAP_ANONYMOUS,
		.msg = "mmap(ADDR_SWITCH_HINT - PAGE_SIZE, (2 * PAGE_SIZE))",
		.low_addr_required = 1,
	पूर्ण,
	अणु
		/*
		 * Exact mapping at 128TB, the area is मुक्त we should get that
		 * even without MAP_FIXED.
		 */
		.addr = ((व्योम *)(ADDR_SWITCH_HINT)),
		.size = PAGE_SIZE,
		.flags = MAP_PRIVATE | MAP_ANONYMOUS,
		.msg = "mmap(ADDR_SWITCH_HINT, PAGE_SIZE)",
		.keep_mapped = 1,
	पूर्ण,
	अणु
		.addr = (व्योम *)(ADDR_SWITCH_HINT),
		.size = 2 * PAGE_SIZE,
		.flags = MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED,
		.msg = "mmap(ADDR_SWITCH_HINT, 2 * PAGE_SIZE, MAP_FIXED)",
	पूर्ण,
	अणु
		.addr = शून्य,
		.size = 2 * PAGE_SIZE,
		.flags = MAP_PRIVATE | MAP_ANONYMOUS,
		.msg = "mmap(NULL)",
		.low_addr_required = 1,
	पूर्ण,
	अणु
		.addr = LOW_ADDR,
		.size = 2 * PAGE_SIZE,
		.flags = MAP_PRIVATE | MAP_ANONYMOUS,
		.msg = "mmap(LOW_ADDR)",
		.low_addr_required = 1,
	पूर्ण,
	अणु
		.addr = HIGH_ADDR,
		.size = 2 * PAGE_SIZE,
		.flags = MAP_PRIVATE | MAP_ANONYMOUS,
		.msg = "mmap(HIGH_ADDR)",
		.keep_mapped = 1,
	पूर्ण,
	अणु
		.addr = HIGH_ADDR,
		.size = 2 * PAGE_SIZE,
		.flags = MAP_PRIVATE | MAP_ANONYMOUS,
		.msg = "mmap(HIGH_ADDR) again",
		.keep_mapped = 1,
	पूर्ण,
	अणु
		.addr = HIGH_ADDR,
		.size = 2 * PAGE_SIZE,
		.flags = MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED,
		.msg = "mmap(HIGH_ADDR, MAP_FIXED)",
	पूर्ण,
	अणु
		.addr = (व्योम *) -1,
		.size = 2 * PAGE_SIZE,
		.flags = MAP_PRIVATE | MAP_ANONYMOUS,
		.msg = "mmap(-1)",
		.keep_mapped = 1,
	पूर्ण,
	अणु
		.addr = (व्योम *) -1,
		.size = 2 * PAGE_SIZE,
		.flags = MAP_PRIVATE | MAP_ANONYMOUS,
		.msg = "mmap(-1) again",
	पूर्ण,
	अणु
		.addr = ((व्योम *)(ADDR_SWITCH_HINT - PAGE_SIZE)),
		.size = PAGE_SIZE,
		.flags = MAP_PRIVATE | MAP_ANONYMOUS,
		.msg = "mmap(ADDR_SWITCH_HINT - PAGE_SIZE, PAGE_SIZE)",
		.low_addr_required = 1,
	पूर्ण,
	अणु
		.addr = (व्योम *)(ADDR_SWITCH_HINT - PAGE_SIZE),
		.size = 2 * PAGE_SIZE,
		.flags = MAP_PRIVATE | MAP_ANONYMOUS,
		.msg = "mmap(ADDR_SWITCH_HINT - PAGE_SIZE, 2 * PAGE_SIZE)",
		.low_addr_required = 1,
		.keep_mapped = 1,
	पूर्ण,
	अणु
		.addr = (व्योम *)(ADDR_SWITCH_HINT - PAGE_SIZE / 2),
		.size = 2 * PAGE_SIZE,
		.flags = MAP_PRIVATE | MAP_ANONYMOUS,
		.msg = "mmap(ADDR_SWITCH_HINT - PAGE_SIZE/2 , 2 * PAGE_SIZE)",
		.low_addr_required = 1,
		.keep_mapped = 1,
	पूर्ण,
	अणु
		.addr = ((व्योम *)(ADDR_SWITCH_HINT)),
		.size = PAGE_SIZE,
		.flags = MAP_PRIVATE | MAP_ANONYMOUS,
		.msg = "mmap(ADDR_SWITCH_HINT, PAGE_SIZE)",
	पूर्ण,
	अणु
		.addr = (व्योम *)(ADDR_SWITCH_HINT),
		.size = 2 * PAGE_SIZE,
		.flags = MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED,
		.msg = "mmap(ADDR_SWITCH_HINT, 2 * PAGE_SIZE, MAP_FIXED)",
	पूर्ण,
पूर्ण;

अटल काष्ठा testहाल hugetlb_testहालs[] = अणु
	अणु
		.addr = शून्य,
		.size = HUGETLB_SIZE,
		.flags = MAP_HUGETLB | MAP_PRIVATE | MAP_ANONYMOUS,
		.msg = "mmap(NULL, MAP_HUGETLB)",
		.low_addr_required = 1,
	पूर्ण,
	अणु
		.addr = LOW_ADDR,
		.size = HUGETLB_SIZE,
		.flags = MAP_HUGETLB | MAP_PRIVATE | MAP_ANONYMOUS,
		.msg = "mmap(LOW_ADDR, MAP_HUGETLB)",
		.low_addr_required = 1,
	पूर्ण,
	अणु
		.addr = HIGH_ADDR,
		.size = HUGETLB_SIZE,
		.flags = MAP_HUGETLB | MAP_PRIVATE | MAP_ANONYMOUS,
		.msg = "mmap(HIGH_ADDR, MAP_HUGETLB)",
		.keep_mapped = 1,
	पूर्ण,
	अणु
		.addr = HIGH_ADDR,
		.size = HUGETLB_SIZE,
		.flags = MAP_HUGETLB | MAP_PRIVATE | MAP_ANONYMOUS,
		.msg = "mmap(HIGH_ADDR, MAP_HUGETLB) again",
		.keep_mapped = 1,
	पूर्ण,
	अणु
		.addr = HIGH_ADDR,
		.size = HUGETLB_SIZE,
		.flags = MAP_HUGETLB | MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED,
		.msg = "mmap(HIGH_ADDR, MAP_FIXED | MAP_HUGETLB)",
	पूर्ण,
	अणु
		.addr = (व्योम *) -1,
		.size = HUGETLB_SIZE,
		.flags = MAP_HUGETLB | MAP_PRIVATE | MAP_ANONYMOUS,
		.msg = "mmap(-1, MAP_HUGETLB)",
		.keep_mapped = 1,
	पूर्ण,
	अणु
		.addr = (व्योम *) -1,
		.size = HUGETLB_SIZE,
		.flags = MAP_HUGETLB | MAP_PRIVATE | MAP_ANONYMOUS,
		.msg = "mmap(-1, MAP_HUGETLB) again",
	पूर्ण,
	अणु
		.addr = (व्योम *)(ADDR_SWITCH_HINT - PAGE_SIZE),
		.size = 2 * HUGETLB_SIZE,
		.flags = MAP_HUGETLB | MAP_PRIVATE | MAP_ANONYMOUS,
		.msg = "mmap(ADDR_SWITCH_HINT - PAGE_SIZE, 2*HUGETLB_SIZE, MAP_HUGETLB)",
		.low_addr_required = 1,
		.keep_mapped = 1,
	पूर्ण,
	अणु
		.addr = (व्योम *)(ADDR_SWITCH_HINT),
		.size = 2 * HUGETLB_SIZE,
		.flags = MAP_HUGETLB | MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED,
		.msg = "mmap(ADDR_SWITCH_HINT , 2*HUGETLB_SIZE, MAP_FIXED | MAP_HUGETLB)",
	पूर्ण,
पूर्ण;

अटल पूर्णांक run_test(काष्ठा testहाल *test, पूर्णांक count)
अणु
	व्योम *p;
	पूर्णांक i, ret = 0;

	क्रम (i = 0; i < count; i++) अणु
		काष्ठा testहाल *t = test + i;

		p = mmap(t->addr, t->size, PROT_READ | PROT_WRITE, t->flags, -1, 0);

		म_लिखो("%s: %p - ", t->msg, p);

		अगर (p == MAP_FAILED) अणु
			म_लिखो("FAILED\n");
			ret = 1;
			जारी;
		पूर्ण

		अगर (t->low_addr_required && p >= (व्योम *)(ADDR_SWITCH_HINT)) अणु
			म_लिखो("FAILED\n");
			ret = 1;
		पूर्ण अन्यथा अणु
			/*
			 * Do a dereference of the address वापसed so that we catch
			 * bugs in page fault handling
			 */
			स_रखो(p, 0, t->size);
			म_लिखो("OK\n");
		पूर्ण
		अगर (!t->keep_mapped)
			munmap(p, t->size);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक supported_arch(व्योम)
अणु
#अगर defined(__घातerpc64__)
	वापस 1;
#या_अगर defined(__x86_64__)
	वापस 1;
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक ret;

	अगर (!supported_arch())
		वापस 0;

	ret = run_test(testहालs, ARRAY_SIZE(testहालs));
	अगर (argc == 2 && !म_भेद(argv[1], "--run-hugetlb"))
		ret = run_test(hugetlb_testहालs, ARRAY_SIZE(hugetlb_testहालs));
	वापस ret;
पूर्ण
