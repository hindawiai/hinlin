<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Test that MAP_FIXED_NOREPLACE works.
 *
 * Copyright 2018, Jann Horn <jannh@google.com>
 * Copyright 2018, Michael Ellerman, IBM Corporation.
 */

#समावेश <sys/mman.h>
#समावेश <त्रुटिसं.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <unistd.h>

#अगर_अघोषित MAP_FIXED_NOREPLACE
#घोषणा MAP_FIXED_NOREPLACE 0x100000
#पूर्ण_अगर

#घोषणा BASE_ADDRESS	(256ul * 1024 * 1024)


अटल व्योम dump_maps(व्योम)
अणु
	अक्षर cmd[32];

	snम_लिखो(cmd, माप(cmd), "cat /proc/%d/maps", getpid());
	प्रणाली(cmd);
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	अचिन्हित दीर्घ flags, addr, size, page_size;
	अक्षर *p;

	page_size = sysconf(_SC_PAGE_SIZE);

	flags = MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED_NOREPLACE;

	// Check we can map all the areas we need below
	त्रुटि_सं = 0;
	addr = BASE_ADDRESS;
	size = 5 * page_size;
	p = mmap((व्योम *)addr, size, PROT_NONE, flags, -1, 0);

	म_लिखो("mmap() @ 0x%lx-0x%lx p=%p result=%m\n", addr, addr + size, p);

	अगर (p == MAP_FAILED) अणु
		dump_maps();
		म_लिखो("Error: couldn't map the space we need for the test\n");
		वापस 1;
	पूर्ण

	त्रुटि_सं = 0;
	अगर (munmap((व्योम *)addr, 5 * page_size) != 0) अणु
		dump_maps();
		म_लिखो("Error: munmap failed!?\n");
		वापस 1;
	पूर्ण
	म_लिखो("unmap() successful\n");

	त्रुटि_सं = 0;
	addr = BASE_ADDRESS + page_size;
	size = 3 * page_size;
	p = mmap((व्योम *)addr, size, PROT_NONE, flags, -1, 0);
	म_लिखो("mmap() @ 0x%lx-0x%lx p=%p result=%m\n", addr, addr + size, p);

	अगर (p == MAP_FAILED) अणु
		dump_maps();
		म_लिखो("Error: first mmap() failed unexpectedly\n");
		वापस 1;
	पूर्ण

	/*
	 * Exact same mapping again:
	 *   base |  मुक्त  | new
	 *     +1 | mapped | new
	 *     +2 | mapped | new
	 *     +3 | mapped | new
	 *     +4 |  मुक्त  | new
	 */
	त्रुटि_सं = 0;
	addr = BASE_ADDRESS;
	size = 5 * page_size;
	p = mmap((व्योम *)addr, size, PROT_NONE, flags, -1, 0);
	म_लिखो("mmap() @ 0x%lx-0x%lx p=%p result=%m\n", addr, addr + size, p);

	अगर (p != MAP_FAILED) अणु
		dump_maps();
		म_लिखो("Error:1: mmap() succeeded when it shouldn't have\n");
		वापस 1;
	पूर्ण

	/*
	 * Second mapping contained within first:
	 *
	 *   base |  मुक्त  |
	 *     +1 | mapped |
	 *     +2 | mapped | new
	 *     +3 | mapped |
	 *     +4 |  मुक्त  |
	 */
	त्रुटि_सं = 0;
	addr = BASE_ADDRESS + (2 * page_size);
	size = page_size;
	p = mmap((व्योम *)addr, size, PROT_NONE, flags, -1, 0);
	म_लिखो("mmap() @ 0x%lx-0x%lx p=%p result=%m\n", addr, addr + size, p);

	अगर (p != MAP_FAILED) अणु
		dump_maps();
		म_लिखो("Error:2: mmap() succeeded when it shouldn't have\n");
		वापस 1;
	पूर्ण

	/*
	 * Overlap end of existing mapping:
	 *   base |  मुक्त  |
	 *     +1 | mapped |
	 *     +2 | mapped |
	 *     +3 | mapped | new
	 *     +4 |  मुक्त  | new
	 */
	त्रुटि_सं = 0;
	addr = BASE_ADDRESS + (3 * page_size);
	size = 2 * page_size;
	p = mmap((व्योम *)addr, size, PROT_NONE, flags, -1, 0);
	म_लिखो("mmap() @ 0x%lx-0x%lx p=%p result=%m\n", addr, addr + size, p);

	अगर (p != MAP_FAILED) अणु
		dump_maps();
		म_लिखो("Error:3: mmap() succeeded when it shouldn't have\n");
		वापस 1;
	पूर्ण

	/*
	 * Overlap start of existing mapping:
	 *   base |  मुक्त  | new
	 *     +1 | mapped | new
	 *     +2 | mapped |
	 *     +3 | mapped |
	 *     +4 |  मुक्त  |
	 */
	त्रुटि_सं = 0;
	addr = BASE_ADDRESS;
	size = 2 * page_size;
	p = mmap((व्योम *)addr, size, PROT_NONE, flags, -1, 0);
	म_लिखो("mmap() @ 0x%lx-0x%lx p=%p result=%m\n", addr, addr + size, p);

	अगर (p != MAP_FAILED) अणु
		dump_maps();
		म_लिखो("Error:4: mmap() succeeded when it shouldn't have\n");
		वापस 1;
	पूर्ण

	/*
	 * Adjacent to start of existing mapping:
	 *   base |  मुक्त  | new
	 *     +1 | mapped |
	 *     +2 | mapped |
	 *     +3 | mapped |
	 *     +4 |  मुक्त  |
	 */
	त्रुटि_सं = 0;
	addr = BASE_ADDRESS;
	size = page_size;
	p = mmap((व्योम *)addr, size, PROT_NONE, flags, -1, 0);
	म_लिखो("mmap() @ 0x%lx-0x%lx p=%p result=%m\n", addr, addr + size, p);

	अगर (p == MAP_FAILED) अणु
		dump_maps();
		म_लिखो("Error:5: mmap() failed when it shouldn't have\n");
		वापस 1;
	पूर्ण

	/*
	 * Adjacent to end of existing mapping:
	 *   base |  मुक्त  |
	 *     +1 | mapped |
	 *     +2 | mapped |
	 *     +3 | mapped |
	 *     +4 |  मुक्त  |  new
	 */
	त्रुटि_सं = 0;
	addr = BASE_ADDRESS + (4 * page_size);
	size = page_size;
	p = mmap((व्योम *)addr, size, PROT_NONE, flags, -1, 0);
	म_लिखो("mmap() @ 0x%lx-0x%lx p=%p result=%m\n", addr, addr + size, p);

	अगर (p == MAP_FAILED) अणु
		dump_maps();
		म_लिखो("Error:6: mmap() failed when it shouldn't have\n");
		वापस 1;
	पूर्ण

	addr = BASE_ADDRESS;
	size = 5 * page_size;
	अगर (munmap((व्योम *)addr, size) != 0) अणु
		dump_maps();
		म_लिखो("Error: munmap failed!?\n");
		वापस 1;
	पूर्ण
	म_लिखो("unmap() successful\n");

	म_लिखो("OK\n");
	वापस 0;
पूर्ण
