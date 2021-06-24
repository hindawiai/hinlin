<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * tools/testing/selftests/kvm/lib/test_util.c
 *
 * Copyright (C) 2020, Google LLC.
 */

#समावेश <निश्चित.स>
#समावेश <प्रकार.स>
#समावेश <सीमा.स>
#समावेश <मानककोष.स>
#समावेश <समय.स>
#समावेश <sys/स्थिति.स>
#समावेश <linux/mman.h>
#समावेश "linux/kernel.h"

#समावेश "test_util.h"

/*
 * Parses "[0-9]+[kmgt]?".
 */
माप_प्रकार parse_size(स्थिर अक्षर *size)
अणु
	माप_प्रकार base;
	अक्षर *scale;
	पूर्णांक shअगरt = 0;

	TEST_ASSERT(size && है_अंक(size[0]), "Need at least one digit in '%s'", size);

	base = म_से_अदीर्घl(size, &scale, 0);

	TEST_ASSERT(base != ULदीर्घ_उच्च, "Overflow parsing size!");

	चयन (छोटे(*scale)) अणु
	हाल 't':
		shअगरt = 40;
		अवरोध;
	हाल 'g':
		shअगरt = 30;
		अवरोध;
	हाल 'm':
		shअगरt = 20;
		अवरोध;
	हाल 'k':
		shअगरt = 10;
		अवरोध;
	हाल 'b':
	हाल '\0':
		shअगरt = 0;
		अवरोध;
	शेष:
		TEST_ASSERT(false, "Unknown size letter %c", *scale);
	पूर्ण

	TEST_ASSERT((base << shअगरt) >> shअगरt == base, "Overflow scaling size!");

	वापस base << shअगरt;
पूर्ण

पूर्णांक64_t बारpec_to_ns(काष्ठा बारpec ts)
अणु
	वापस (पूर्णांक64_t)ts.tv_nsec + 1000000000LL * (पूर्णांक64_t)ts.tv_sec;
पूर्ण

काष्ठा बारpec बारpec_add_ns(काष्ठा बारpec ts, पूर्णांक64_t ns)
अणु
	काष्ठा बारpec res;

	res.tv_nsec = ts.tv_nsec + ns;
	res.tv_sec = ts.tv_sec + res.tv_nsec / 1000000000LL;
	res.tv_nsec %= 1000000000LL;

	वापस res;
पूर्ण

काष्ठा बारpec बारpec_add(काष्ठा बारpec ts1, काष्ठा बारpec ts2)
अणु
	पूर्णांक64_t ns1 = बारpec_to_ns(ts1);
	पूर्णांक64_t ns2 = बारpec_to_ns(ts2);
	वापस बारpec_add_ns((काष्ठा बारpec)अणु0पूर्ण, ns1 + ns2);
पूर्ण

काष्ठा बारpec बारpec_sub(काष्ठा बारpec ts1, काष्ठा बारpec ts2)
अणु
	पूर्णांक64_t ns1 = बारpec_to_ns(ts1);
	पूर्णांक64_t ns2 = बारpec_to_ns(ts2);
	वापस बारpec_add_ns((काष्ठा बारpec)अणु0पूर्ण, ns1 - ns2);
पूर्ण

काष्ठा बारpec बारpec_elapsed(काष्ठा बारpec start)
अणु
	काष्ठा बारpec end;

	घड़ी_समय_लो(CLOCK_MONOTONIC, &end);
	वापस बारpec_sub(end, start);
पूर्ण

काष्ठा बारpec बारpec_भाग(काष्ठा बारpec ts, पूर्णांक भागisor)
अणु
	पूर्णांक64_t ns = बारpec_to_ns(ts) / भागisor;

	वापस बारpec_add_ns((काष्ठा बारpec)अणु0पूर्ण, ns);
पूर्ण

व्योम prपूर्णांक_skip(स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची ap;

	निश्चित(fmt);
	बहु_शुरू(ap, fmt);
	भ_लिखो(fmt, ap);
	बहु_पूर्ण(ap);
	माला_दो(", skipping test");
पूर्ण

bool thp_configured(व्योम)
अणु
	पूर्णांक ret;
	काष्ठा stat statbuf;

	ret = stat("/sys/kernel/mm/transparent_hugepage", &statbuf);
	TEST_ASSERT(ret == 0 || (ret == -1 && त्रुटि_सं == ENOENT),
		    "Error in stating /sys/kernel/mm/transparent_hugepage");

	वापस ret == 0;
पूर्ण

माप_प्रकार get_trans_hugepagesz(व्योम)
अणु
	माप_प्रकार size;
	खाता *f;

	TEST_ASSERT(thp_configured(), "THP is not configured in host kernel");

	f = ख_खोलो("/sys/kernel/mm/transparent_hugepage/hpage_pmd_size", "r");
	TEST_ASSERT(f != शून्य, "Error in opening transparent_hugepage/hpage_pmd_size");

	ख_पूछो(f, "%ld", &size);
	ख_बंद(f);

	वापस size;
पूर्ण

माप_प्रकार get_def_hugetlb_pagesz(व्योम)
अणु
	अक्षर buf[64];
	स्थिर अक्षर *tag = "Hugepagesize:";
	खाता *f;

	f = ख_खोलो("/proc/meminfo", "r");
	TEST_ASSERT(f != शून्य, "Error in opening /proc/meminfo");

	जबतक (ख_माला_लो(buf, माप(buf), f) != शून्य) अणु
		अगर (म_माला(buf, tag) == buf) अणु
			ख_बंद(f);
			वापस म_से_अदीर्घl(buf + म_माप(tag), शून्य, 10) << 10;
		पूर्ण
	पूर्ण

	अगर (ख_पूर्ण(f))
		TEST_FAIL("HUGETLB is not configured in host kernel");
	अन्यथा
		TEST_FAIL("Error in reading /proc/meminfo");

	ख_बंद(f);
	वापस 0;
पूर्ण

#घोषणा ANON_FLAGS	(MAP_PRIVATE | MAP_ANONYMOUS)
#घोषणा ANON_HUGE_FLAGS	(ANON_FLAGS | MAP_HUGETLB)

स्थिर काष्ठा vm_mem_backing_src_alias *vm_mem_backing_src_alias(uपूर्णांक32_t i)
अणु
	अटल स्थिर काष्ठा vm_mem_backing_src_alias aliases[] = अणु
		[VM_MEM_SRC_ANONYMOUS] = अणु
			.name = "anonymous",
			.flag = ANON_FLAGS,
		पूर्ण,
		[VM_MEM_SRC_ANONYMOUS_THP] = अणु
			.name = "anonymous_thp",
			.flag = ANON_FLAGS,
		पूर्ण,
		[VM_MEM_SRC_ANONYMOUS_HUGETLB] = अणु
			.name = "anonymous_hugetlb",
			.flag = ANON_HUGE_FLAGS,
		पूर्ण,
		[VM_MEM_SRC_ANONYMOUS_HUGETLB_16KB] = अणु
			.name = "anonymous_hugetlb_16kb",
			.flag = ANON_HUGE_FLAGS | MAP_HUGE_16KB,
		पूर्ण,
		[VM_MEM_SRC_ANONYMOUS_HUGETLB_64KB] = अणु
			.name = "anonymous_hugetlb_64kb",
			.flag = ANON_HUGE_FLAGS | MAP_HUGE_64KB,
		पूर्ण,
		[VM_MEM_SRC_ANONYMOUS_HUGETLB_512KB] = अणु
			.name = "anonymous_hugetlb_512kb",
			.flag = ANON_HUGE_FLAGS | MAP_HUGE_512KB,
		पूर्ण,
		[VM_MEM_SRC_ANONYMOUS_HUGETLB_1MB] = अणु
			.name = "anonymous_hugetlb_1mb",
			.flag = ANON_HUGE_FLAGS | MAP_HUGE_1MB,
		पूर्ण,
		[VM_MEM_SRC_ANONYMOUS_HUGETLB_2MB] = अणु
			.name = "anonymous_hugetlb_2mb",
			.flag = ANON_HUGE_FLAGS | MAP_HUGE_2MB,
		पूर्ण,
		[VM_MEM_SRC_ANONYMOUS_HUGETLB_8MB] = अणु
			.name = "anonymous_hugetlb_8mb",
			.flag = ANON_HUGE_FLAGS | MAP_HUGE_8MB,
		पूर्ण,
		[VM_MEM_SRC_ANONYMOUS_HUGETLB_16MB] = अणु
			.name = "anonymous_hugetlb_16mb",
			.flag = ANON_HUGE_FLAGS | MAP_HUGE_16MB,
		पूर्ण,
		[VM_MEM_SRC_ANONYMOUS_HUGETLB_32MB] = अणु
			.name = "anonymous_hugetlb_32mb",
			.flag = ANON_HUGE_FLAGS | MAP_HUGE_32MB,
		पूर्ण,
		[VM_MEM_SRC_ANONYMOUS_HUGETLB_256MB] = अणु
			.name = "anonymous_hugetlb_256mb",
			.flag = ANON_HUGE_FLAGS | MAP_HUGE_256MB,
		पूर्ण,
		[VM_MEM_SRC_ANONYMOUS_HUGETLB_512MB] = अणु
			.name = "anonymous_hugetlb_512mb",
			.flag = ANON_HUGE_FLAGS | MAP_HUGE_512MB,
		पूर्ण,
		[VM_MEM_SRC_ANONYMOUS_HUGETLB_1GB] = अणु
			.name = "anonymous_hugetlb_1gb",
			.flag = ANON_HUGE_FLAGS | MAP_HUGE_1GB,
		पूर्ण,
		[VM_MEM_SRC_ANONYMOUS_HUGETLB_2GB] = अणु
			.name = "anonymous_hugetlb_2gb",
			.flag = ANON_HUGE_FLAGS | MAP_HUGE_2GB,
		पूर्ण,
		[VM_MEM_SRC_ANONYMOUS_HUGETLB_16GB] = अणु
			.name = "anonymous_hugetlb_16gb",
			.flag = ANON_HUGE_FLAGS | MAP_HUGE_16GB,
		पूर्ण,
		[VM_MEM_SRC_SHMEM] = अणु
			.name = "shmem",
			.flag = MAP_SHARED,
		पूर्ण,
		[VM_MEM_SRC_SHARED_HUGETLB] = अणु
			.name = "shared_hugetlb",
			/*
			 * No MAP_HUGETLB, we use MFD_HUGETLB instead. Since
			 * we're using "file backed" memory, we need to specअगरy
			 * this when the FD is created, not when the area is
			 * mapped.
			 */
			.flag = MAP_SHARED,
		पूर्ण,
	पूर्ण;
	_Static_निश्चित(ARRAY_SIZE(aliases) == NUM_SRC_TYPES,
		       "Missing new backing src types?");

	TEST_ASSERT(i < NUM_SRC_TYPES, "Backing src type ID %d too big", i);

	वापस &aliases[i];
पूर्ण

#घोषणा MAP_HUGE_PAGE_SIZE(x) (1ULL << ((x >> MAP_HUGE_SHIFT) & MAP_HUGE_MASK))

माप_प्रकार get_backing_src_pagesz(uपूर्णांक32_t i)
अणु
	uपूर्णांक32_t flag = vm_mem_backing_src_alias(i)->flag;

	चयन (i) अणु
	हाल VM_MEM_SRC_ANONYMOUS:
	हाल VM_MEM_SRC_SHMEM:
		वापस getpagesize();
	हाल VM_MEM_SRC_ANONYMOUS_THP:
		वापस get_trans_hugepagesz();
	हाल VM_MEM_SRC_ANONYMOUS_HUGETLB:
	हाल VM_MEM_SRC_SHARED_HUGETLB:
		वापस get_def_hugetlb_pagesz();
	शेष:
		वापस MAP_HUGE_PAGE_SIZE(flag);
	पूर्ण
पूर्ण

व्योम backing_src_help(व्योम)
अणु
	पूर्णांक i;

	म_लिखो("Available backing src types:\n");
	क्रम (i = 0; i < NUM_SRC_TYPES; i++)
		म_लिखो("\t%s\n", vm_mem_backing_src_alias(i)->name);
पूर्ण

क्रमागत vm_mem_backing_src_type parse_backing_src_type(स्थिर अक्षर *type_name)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NUM_SRC_TYPES; i++)
		अगर (!म_भेद(type_name, vm_mem_backing_src_alias(i)->name))
			वापस i;

	backing_src_help();
	TEST_FAIL("Unknown backing src type: %s", type_name);
	वापस -1;
पूर्ण
