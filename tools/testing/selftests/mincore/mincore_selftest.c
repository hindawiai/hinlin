<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * kselftest suite क्रम mincore().
 *
 * Copyright (C) 2020 Collabora, Ltd.
 */

#घोषणा _GNU_SOURCE

#समावेश <मानकपन.स>
#समावेश <त्रुटिसं.स>
#समावेश <unistd.h>
#समावेश <मानककोष.स>
#समावेश <sys/mman.h>
#समावेश <माला.स>
#समावेश <fcntl.h>

#समावेश "../kselftest.h"
#समावेश "../kselftest_harness.h"

/* Default test file size: 4MB */
#घोषणा MB (1UL << 20)
#घोषणा खाता_SIZE (4 * MB)


/*
 * Tests the user पूर्णांकerface. This test triggers most of the करोcumented
 * error conditions in mincore().
 */
TEST(basic_पूर्णांकerface)
अणु
	पूर्णांक retval;
	पूर्णांक page_size;
	अचिन्हित अक्षर vec[1];
	अक्षर *addr;

	page_size = sysconf(_SC_PAGESIZE);

	/* Query a 0 byte sized range */
	retval = mincore(0, 0, vec);
	EXPECT_EQ(0, retval);

	/* Addresses in the specअगरied range are invalid or unmapped */
	त्रुटि_सं = 0;
	retval = mincore(शून्य, page_size, vec);
	EXPECT_EQ(-1, retval);
	EXPECT_EQ(ENOMEM, त्रुटि_सं);

	त्रुटि_सं = 0;
	addr = mmap(शून्य, page_size, PROT_READ | PROT_WRITE,
		MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	ASSERT_NE(MAP_FAILED, addr) अणु
		TH_LOG("mmap error: %s", म_त्रुटि(त्रुटि_सं));
	पूर्ण

	/* <addr> argument is not page-aligned */
	त्रुटि_सं = 0;
	retval = mincore(addr + 1, page_size, vec);
	EXPECT_EQ(-1, retval);
	EXPECT_EQ(EINVAL, त्रुटि_सं);

	/* <length> argument is too large */
	त्रुटि_सं = 0;
	retval = mincore(addr, -1, vec);
	EXPECT_EQ(-1, retval);
	EXPECT_EQ(ENOMEM, त्रुटि_सं);

	/* <vec> argument poपूर्णांकs to an illegal address */
	त्रुटि_सं = 0;
	retval = mincore(addr, page_size, शून्य);
	EXPECT_EQ(-1, retval);
	EXPECT_EQ(EFAULT, त्रुटि_सं);
	munmap(addr, page_size);
पूर्ण


/*
 * Test mincore() behavior on a निजी anonymous page mapping.
 * Check that the page is not loaded पूर्णांकo memory right after the mapping
 * but after accessing it (on-demand allocation).
 * Then मुक्त the page and check that it's not memory-resident.
 */
TEST(check_anonymous_locked_pages)
अणु
	अचिन्हित अक्षर vec[1];
	अक्षर *addr;
	पूर्णांक retval;
	पूर्णांक page_size;

	page_size = sysconf(_SC_PAGESIZE);

	/* Map one page and check it's not memory-resident */
	त्रुटि_सं = 0;
	addr = mmap(शून्य, page_size, PROT_READ | PROT_WRITE,
			MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	ASSERT_NE(MAP_FAILED, addr) अणु
		TH_LOG("mmap error: %s", म_त्रुटि(त्रुटि_सं));
	पूर्ण
	retval = mincore(addr, page_size, vec);
	ASSERT_EQ(0, retval);
	ASSERT_EQ(0, vec[0]) अणु
		TH_LOG("Page found in memory before use");
	पूर्ण

	/* Touch the page and check again. It should now be in memory */
	addr[0] = 1;
	mlock(addr, page_size);
	retval = mincore(addr, page_size, vec);
	ASSERT_EQ(0, retval);
	ASSERT_EQ(1, vec[0]) अणु
		TH_LOG("Page not found in memory after use");
	पूर्ण

	/*
	 * It shouldn't be memory-resident after unlocking it and
	 * marking it as unneeded.
	 */
	munlock(addr, page_size);
	madvise(addr, page_size, MADV_DONTNEED);
	retval = mincore(addr, page_size, vec);
	ASSERT_EQ(0, retval);
	ASSERT_EQ(0, vec[0]) अणु
		TH_LOG("Page in memory after being zapped");
	पूर्ण
	munmap(addr, page_size);
पूर्ण


/*
 * Check mincore() behavior on huge pages.
 * This test will be skipped अगर the mapping fails (ie. अगर there are no
 * huge pages available).
 *
 * Make sure the प्रणाली has at least one मुक्त huge page, check
 * "HugePages_Free" in /proc/meminfo.
 * Increment /sys/kernel/mm/hugepages/hugepages-2048kB/nr_hugepages अगर
 * needed.
 */
TEST(check_huge_pages)
अणु
	अचिन्हित अक्षर vec[1];
	अक्षर *addr;
	पूर्णांक retval;
	पूर्णांक page_size;

	page_size = sysconf(_SC_PAGESIZE);

	त्रुटि_सं = 0;
	addr = mmap(शून्य, page_size, PROT_READ | PROT_WRITE,
		MAP_PRIVATE | MAP_ANONYMOUS | MAP_HUGETLB,
		-1, 0);
	अगर (addr == MAP_FAILED) अणु
		अगर (त्रुटि_सं == ENOMEM)
			SKIP(वापस, "No huge pages available.");
		अन्यथा
			TH_LOG("mmap error: %s", म_त्रुटि(त्रुटि_सं));
	पूर्ण
	retval = mincore(addr, page_size, vec);
	ASSERT_EQ(0, retval);
	ASSERT_EQ(0, vec[0]) अणु
		TH_LOG("Page found in memory before use");
	पूर्ण

	addr[0] = 1;
	mlock(addr, page_size);
	retval = mincore(addr, page_size, vec);
	ASSERT_EQ(0, retval);
	ASSERT_EQ(1, vec[0]) अणु
		TH_LOG("Page not found in memory after use");
	पूर्ण

	munlock(addr, page_size);
	munmap(addr, page_size);
पूर्ण


/*
 * Test mincore() behavior on a file-backed page.
 * No pages should be loaded पूर्णांकo memory right after the mapping. Then,
 * accessing any address in the mapping range should load the page
 * containing the address and a number of subsequent pages (पढ़ोahead).
 *
 * The actual पढ़ोahead settings depend on the test environment, so we
 * can't make a lot of assumptions about that. This test covers the most
 * general हालs.
 */
TEST(check_file_mmap)
अणु
	अचिन्हित अक्षर *vec;
	पूर्णांक vec_size;
	अक्षर *addr;
	पूर्णांक retval;
	पूर्णांक page_size;
	पूर्णांक fd;
	पूर्णांक i;
	पूर्णांक ra_pages = 0;

	page_size = sysconf(_SC_PAGESIZE);
	vec_size = खाता_SIZE / page_size;
	अगर (खाता_SIZE % page_size)
		vec_size++;

	vec = सुस्मृति(vec_size, माप(अचिन्हित अक्षर));
	ASSERT_NE(शून्य, vec) अणु
		TH_LOG("Can't allocate array");
	पूर्ण

	त्रुटि_सं = 0;
	fd = खोलो(".", O_TMPखाता | O_RDWR, 0600);
	ASSERT_NE(-1, fd) अणु
		TH_LOG("Can't create temporary file: %s",
			म_त्रुटि(त्रुटि_सं));
	पूर्ण
	त्रुटि_सं = 0;
	retval = fallocate(fd, 0, 0, खाता_SIZE);
	ASSERT_EQ(0, retval) अणु
		TH_LOG("Error allocating space for the temporary file: %s",
			म_त्रुटि(त्रुटि_सं));
	पूर्ण

	/*
	 * Map the whole file, the pages shouldn't be fetched yet.
	 */
	त्रुटि_सं = 0;
	addr = mmap(शून्य, खाता_SIZE, PROT_READ | PROT_WRITE,
			MAP_SHARED, fd, 0);
	ASSERT_NE(MAP_FAILED, addr) अणु
		TH_LOG("mmap error: %s", म_त्रुटि(त्रुटि_सं));
	पूर्ण
	retval = mincore(addr, खाता_SIZE, vec);
	ASSERT_EQ(0, retval);
	क्रम (i = 0; i < vec_size; i++) अणु
		ASSERT_EQ(0, vec[i]) अणु
			TH_LOG("Unexpected page in memory");
		पूर्ण
	पूर्ण

	/*
	 * Touch a page in the middle of the mapping. We expect the next
	 * few pages (the पढ़ोahead winकरोw) to be populated too.
	 */
	addr[खाता_SIZE / 2] = 1;
	retval = mincore(addr, खाता_SIZE, vec);
	ASSERT_EQ(0, retval);
	ASSERT_EQ(1, vec[खाता_SIZE / 2 / page_size]) अणु
		TH_LOG("Page not found in memory after use");
	पूर्ण

	i = खाता_SIZE / 2 / page_size + 1;
	जबतक (i < vec_size && vec[i]) अणु
		ra_pages++;
		i++;
	पूर्ण
	EXPECT_GT(ra_pages, 0) अणु
		TH_LOG("No read-ahead pages found in memory");
	पूर्ण

	EXPECT_LT(i, vec_size) अणु
		TH_LOG("Read-ahead pages reached the end of the file");
	पूर्ण
	/*
	 * End of the पढ़ोahead winकरोw. The rest of the pages shouldn't
	 * be in memory.
	 */
	अगर (i < vec_size) अणु
		जबतक (i < vec_size && !vec[i])
			i++;
		EXPECT_EQ(vec_size, i) अणु
			TH_LOG("Unexpected page in memory beyond readahead window");
		पूर्ण
	पूर्ण

	munmap(addr, खाता_SIZE);
	बंद(fd);
	मुक्त(vec);
पूर्ण


/*
 * Test mincore() behavior on a page backed by a पंचांगpfs file.  This test
 * perक्रमms the same steps as the previous one. However, we करोn't expect
 * any पढ़ोahead in this हाल.
 */
TEST(check_पंचांगpfs_mmap)
अणु
	अचिन्हित अक्षर *vec;
	पूर्णांक vec_size;
	अक्षर *addr;
	पूर्णांक retval;
	पूर्णांक page_size;
	पूर्णांक fd;
	पूर्णांक i;
	पूर्णांक ra_pages = 0;

	page_size = sysconf(_SC_PAGESIZE);
	vec_size = खाता_SIZE / page_size;
	अगर (खाता_SIZE % page_size)
		vec_size++;

	vec = सुस्मृति(vec_size, माप(अचिन्हित अक्षर));
	ASSERT_NE(शून्य, vec) अणु
		TH_LOG("Can't allocate array");
	पूर्ण

	त्रुटि_सं = 0;
	fd = खोलो("/dev/shm", O_TMPखाता | O_RDWR, 0600);
	ASSERT_NE(-1, fd) अणु
		TH_LOG("Can't create temporary file: %s",
			म_त्रुटि(त्रुटि_सं));
	पूर्ण
	त्रुटि_सं = 0;
	retval = fallocate(fd, 0, 0, खाता_SIZE);
	ASSERT_EQ(0, retval) अणु
		TH_LOG("Error allocating space for the temporary file: %s",
			म_त्रुटि(त्रुटि_सं));
	पूर्ण

	/*
	 * Map the whole file, the pages shouldn't be fetched yet.
	 */
	त्रुटि_सं = 0;
	addr = mmap(शून्य, खाता_SIZE, PROT_READ | PROT_WRITE,
			MAP_SHARED, fd, 0);
	ASSERT_NE(MAP_FAILED, addr) अणु
		TH_LOG("mmap error: %s", म_त्रुटि(त्रुटि_सं));
	पूर्ण
	retval = mincore(addr, खाता_SIZE, vec);
	ASSERT_EQ(0, retval);
	क्रम (i = 0; i < vec_size; i++) अणु
		ASSERT_EQ(0, vec[i]) अणु
			TH_LOG("Unexpected page in memory");
		पूर्ण
	पूर्ण

	/*
	 * Touch a page in the middle of the mapping. We expect only
	 * that page to be fetched पूर्णांकo memory.
	 */
	addr[खाता_SIZE / 2] = 1;
	retval = mincore(addr, खाता_SIZE, vec);
	ASSERT_EQ(0, retval);
	ASSERT_EQ(1, vec[खाता_SIZE / 2 / page_size]) अणु
		TH_LOG("Page not found in memory after use");
	पूर्ण

	i = खाता_SIZE / 2 / page_size + 1;
	जबतक (i < vec_size && vec[i]) अणु
		ra_pages++;
		i++;
	पूर्ण
	ASSERT_EQ(ra_pages, 0) अणु
		TH_LOG("Read-ahead pages found in memory");
	पूर्ण

	munmap(addr, खाता_SIZE);
	बंद(fd);
	मुक्त(vec);
पूर्ण

TEST_HARNESS_MAIN
