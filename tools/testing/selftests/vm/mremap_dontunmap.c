<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Tests क्रम mremap w/ MREMAP_DONTUNMAP.
 *
 * Copyright 2020, Brian Geffon <bgeffon@google.com>
 */
#घोषणा _GNU_SOURCE
#समावेश <sys/mman.h>
#समावेश <त्रुटिसं.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <unistd.h>

#समावेश "../kselftest.h"

#अगर_अघोषित MREMAP_DONTUNMAP
#घोषणा MREMAP_DONTUNMAP 4
#पूर्ण_अगर

अचिन्हित दीर्घ page_size;
अक्षर *page_buffer;

अटल व्योम dump_maps(व्योम)
अणु
	अक्षर cmd[32];

	snम_लिखो(cmd, माप(cmd), "cat /proc/%d/maps", getpid());
	प्रणाली(cmd);
पूर्ण

#घोषणा BUG_ON(condition, description)					      \
	करो अणु								      \
		अगर (condition) अणु					      \
			ख_लिखो(मानक_त्रुटि, "[FAIL]\t%s():%d\t%s:%s\n", __func__, \
				__LINE__, (description), म_त्रुटि(त्रुटि_सं));    \
			dump_maps();					  \
			निकास(1);					      \
		पूर्ण 							      \
	पूर्ण जबतक (0)

// Try a simple operation क्रम to "test" क्रम kernel support this prevents
// reporting tests as failed when it's run on an older kernel.
अटल पूर्णांक kernel_support_क्रम_mremap_करोntunmap()
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ num_pages = 1;
	व्योम *source_mapping = mmap(शून्य, num_pages * page_size, PROT_NONE,
				    MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	BUG_ON(source_mapping == MAP_FAILED, "mmap");

	// This simple remap should only fail अगर MREMAP_DONTUNMAP isn't
	// supported.
	व्योम *dest_mapping =
	    mremap(source_mapping, num_pages * page_size, num_pages * page_size,
		   MREMAP_DONTUNMAP | MREMAP_MAYMOVE, 0);
	अगर (dest_mapping == MAP_FAILED) अणु
		ret = त्रुटि_सं;
	पूर्ण अन्यथा अणु
		BUG_ON(munmap(dest_mapping, num_pages * page_size) == -1,
		       "unable to unmap destination mapping");
	पूर्ण

	BUG_ON(munmap(source_mapping, num_pages * page_size) == -1,
	       "unable to unmap source mapping");
	वापस ret;
पूर्ण

// This helper will just validate that an entire mapping contains the expected
// byte.
अटल पूर्णांक check_region_contains_byte(व्योम *addr, अचिन्हित दीर्घ size, अक्षर byte)
अणु
	BUG_ON(size & (page_size - 1),
	       "check_region_contains_byte expects page multiples");
	BUG_ON((अचिन्हित दीर्घ)addr & (page_size - 1),
	       "check_region_contains_byte expects page alignment");

	स_रखो(page_buffer, byte, page_size);

	अचिन्हित दीर्घ num_pages = size / page_size;
	अचिन्हित दीर्घ i;

	// Compare each page checking that it contains our expected byte.
	क्रम (i = 0; i < num_pages; ++i) अणु
		पूर्णांक ret =
		    स_भेद(addr + (i * page_size), page_buffer, page_size);
		अगर (ret) अणु
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

// this test validates that MREMAP_DONTUNMAP moves the pagetables जबतक leaving
// the source mapping mapped.
अटल व्योम mremap_करोntunmap_simple()
अणु
	अचिन्हित दीर्घ num_pages = 5;

	व्योम *source_mapping =
	    mmap(शून्य, num_pages * page_size, PROT_READ | PROT_WRITE,
		 MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	BUG_ON(source_mapping == MAP_FAILED, "mmap");

	स_रखो(source_mapping, 'a', num_pages * page_size);

	// Try to just move the whole mapping anywhere (not fixed).
	व्योम *dest_mapping =
	    mremap(source_mapping, num_pages * page_size, num_pages * page_size,
		   MREMAP_DONTUNMAP | MREMAP_MAYMOVE, शून्य);
	BUG_ON(dest_mapping == MAP_FAILED, "mremap");

	// Validate that the pages have been moved, we know they were moved अगर
	// the dest_mapping contains a's.
	BUG_ON(check_region_contains_byte
	       (dest_mapping, num_pages * page_size, 'a') != 0,
	       "pages did not migrate");
	BUG_ON(check_region_contains_byte
	       (source_mapping, num_pages * page_size, 0) != 0,
	       "source should have no ptes");

	BUG_ON(munmap(dest_mapping, num_pages * page_size) == -1,
	       "unable to unmap destination mapping");
	BUG_ON(munmap(source_mapping, num_pages * page_size) == -1,
	       "unable to unmap source mapping");
पूर्ण

// This test validates that MREMAP_DONTUNMAP on a shared mapping works as expected.
अटल व्योम mremap_करोntunmap_simple_shmem()
अणु
	अचिन्हित दीर्घ num_pages = 5;

	पूर्णांक mem_fd = memfd_create("memfd", MFD_CLOEXEC);
	BUG_ON(mem_fd < 0, "memfd_create");

	BUG_ON(ftruncate(mem_fd, num_pages * page_size) < 0,
			"ftruncate");

	व्योम *source_mapping =
	    mmap(शून्य, num_pages * page_size, PROT_READ | PROT_WRITE,
		 MAP_खाता | MAP_SHARED, mem_fd, 0);
	BUG_ON(source_mapping == MAP_FAILED, "mmap");

	BUG_ON(बंद(mem_fd) < 0, "close");

	स_रखो(source_mapping, 'a', num_pages * page_size);

	// Try to just move the whole mapping anywhere (not fixed).
	व्योम *dest_mapping =
	    mremap(source_mapping, num_pages * page_size, num_pages * page_size,
		   MREMAP_DONTUNMAP | MREMAP_MAYMOVE, शून्य);
	अगर (dest_mapping == MAP_FAILED && त्रुटि_सं == EINVAL) अणु
		// Old kernel which करोesn't support MREMAP_DONTUNMAP on shmem.
		BUG_ON(munmap(source_mapping, num_pages * page_size) == -1,
			"unable to unmap source mapping");
		वापस;
	पूर्ण

	BUG_ON(dest_mapping == MAP_FAILED, "mremap");

	// Validate that the pages have been moved, we know they were moved अगर
	// the dest_mapping contains a's.
	BUG_ON(check_region_contains_byte
	       (dest_mapping, num_pages * page_size, 'a') != 0,
	       "pages did not migrate");

	// Because the region is backed by shmem, we will actually see the same
	// memory at the source location still.
	BUG_ON(check_region_contains_byte
	       (source_mapping, num_pages * page_size, 'a') != 0,
	       "source should have no ptes");

	BUG_ON(munmap(dest_mapping, num_pages * page_size) == -1,
	       "unable to unmap destination mapping");
	BUG_ON(munmap(source_mapping, num_pages * page_size) == -1,
	       "unable to unmap source mapping");
पूर्ण

// This test validates MREMAP_DONTUNMAP will move page tables to a specअगरic
// destination using MREMAP_FIXED, also जबतक validating that the source
// reमुख्यs पूर्णांकact.
अटल व्योम mremap_करोntunmap_simple_fixed()
अणु
	अचिन्हित दीर्घ num_pages = 5;

	// Since we want to guarantee that we can remap to a poपूर्णांक, we will
	// create a mapping up front.
	व्योम *dest_mapping =
	    mmap(शून्य, num_pages * page_size, PROT_READ | PROT_WRITE,
		 MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	BUG_ON(dest_mapping == MAP_FAILED, "mmap");
	स_रखो(dest_mapping, 'X', num_pages * page_size);

	व्योम *source_mapping =
	    mmap(शून्य, num_pages * page_size, PROT_READ | PROT_WRITE,
		 MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	BUG_ON(source_mapping == MAP_FAILED, "mmap");
	स_रखो(source_mapping, 'a', num_pages * page_size);

	व्योम *remapped_mapping =
	    mremap(source_mapping, num_pages * page_size, num_pages * page_size,
		   MREMAP_FIXED | MREMAP_DONTUNMAP | MREMAP_MAYMOVE,
		   dest_mapping);
	BUG_ON(remapped_mapping == MAP_FAILED, "mremap");
	BUG_ON(remapped_mapping != dest_mapping,
	       "mremap should have placed the remapped mapping at dest_mapping");

	// The dest mapping will have been unmap by mremap so we expect the Xs
	// to be gone and replaced with a's.
	BUG_ON(check_region_contains_byte
	       (dest_mapping, num_pages * page_size, 'a') != 0,
	       "pages did not migrate");

	// And the source mapping will have had its ptes dropped.
	BUG_ON(check_region_contains_byte
	       (source_mapping, num_pages * page_size, 0) != 0,
	       "source should have no ptes");

	BUG_ON(munmap(dest_mapping, num_pages * page_size) == -1,
	       "unable to unmap destination mapping");
	BUG_ON(munmap(source_mapping, num_pages * page_size) == -1,
	       "unable to unmap source mapping");
पूर्ण

// This test validates that we can MREMAP_DONTUNMAP क्रम a portion of an
// existing mapping.
अटल व्योम mremap_करोntunmap_partial_mapping()
अणु
	/*
	 *  source mapping:
	 *  --------------
	 *  | aaaaaaaaaa |
	 *  --------------
	 *  to become:
	 *  --------------
	 *  | aaaaa00000 |
	 *  --------------
	 *  With the destination mapping containing 5 pages of As.
	 *  ---------
	 *  | aaaaa |
	 *  ---------
	 */
	अचिन्हित दीर्घ num_pages = 10;
	व्योम *source_mapping =
	    mmap(शून्य, num_pages * page_size, PROT_READ | PROT_WRITE,
		 MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	BUG_ON(source_mapping == MAP_FAILED, "mmap");
	स_रखो(source_mapping, 'a', num_pages * page_size);

	// We will grab the last 5 pages of the source and move them.
	व्योम *dest_mapping =
	    mremap(source_mapping + (5 * page_size), 5 * page_size,
		   5 * page_size,
		   MREMAP_DONTUNMAP | MREMAP_MAYMOVE, शून्य);
	BUG_ON(dest_mapping == MAP_FAILED, "mremap");

	// We expect the first 5 pages of the source to contain a's and the
	// final 5 pages to contain zeros.
	BUG_ON(check_region_contains_byte(source_mapping, 5 * page_size, 'a') !=
	       0, "first 5 pages of source should have original pages");
	BUG_ON(check_region_contains_byte
	       (source_mapping + (5 * page_size), 5 * page_size, 0) != 0,
	       "final 5 pages of source should have no ptes");

	// Finally we expect the destination to have 5 pages worth of a's.
	BUG_ON(check_region_contains_byte(dest_mapping, 5 * page_size, 'a') !=
	       0, "dest mapping should contain ptes from the source");

	BUG_ON(munmap(dest_mapping, 5 * page_size) == -1,
	       "unable to unmap destination mapping");
	BUG_ON(munmap(source_mapping, num_pages * page_size) == -1,
	       "unable to unmap source mapping");
पूर्ण

// This test validates that we can remap over only a portion of a mapping.
अटल व्योम mremap_करोntunmap_partial_mapping_overग_लिखो(व्योम)
अणु
	/*
	 *  source mapping:
	 *  ---------
	 *  |aaaaa|
	 *  ---------
	 *  dest mapping initially:
	 *  -----------
	 *  |XXXXXXXXXX|
	 *  ------------
	 *  Source to become:
	 *  ---------
	 *  |00000|
	 *  ---------
	 *  With the destination mapping containing 5 pages of As.
	 *  ------------
	 *  |aaaaaXXXXX|
	 *  ------------
	 */
	व्योम *source_mapping =
	    mmap(शून्य, 5 * page_size, PROT_READ | PROT_WRITE,
		 MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	BUG_ON(source_mapping == MAP_FAILED, "mmap");
	स_रखो(source_mapping, 'a', 5 * page_size);

	व्योम *dest_mapping =
	    mmap(शून्य, 10 * page_size, PROT_READ | PROT_WRITE,
		 MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	BUG_ON(dest_mapping == MAP_FAILED, "mmap");
	स_रखो(dest_mapping, 'X', 10 * page_size);

	// We will grab the last 5 pages of the source and move them.
	व्योम *remapped_mapping =
	    mremap(source_mapping, 5 * page_size,
		   5 * page_size,
		   MREMAP_DONTUNMAP | MREMAP_MAYMOVE | MREMAP_FIXED, dest_mapping);
	BUG_ON(dest_mapping == MAP_FAILED, "mremap");
	BUG_ON(dest_mapping != remapped_mapping, "expected to remap to dest_mapping");

	BUG_ON(check_region_contains_byte(source_mapping, 5 * page_size, 0) !=
	       0, "first 5 pages of source should have no ptes");

	// Finally we expect the destination to have 5 pages worth of a's.
	BUG_ON(check_region_contains_byte(dest_mapping, 5 * page_size, 'a') != 0,
			"dest mapping should contain ptes from the source");

	// Finally the last 5 pages shouldn't have been touched.
	BUG_ON(check_region_contains_byte(dest_mapping + (5 * page_size),
				5 * page_size, 'X') != 0,
			"dest mapping should have retained the last 5 pages");

	BUG_ON(munmap(dest_mapping, 10 * page_size) == -1,
	       "unable to unmap destination mapping");
	BUG_ON(munmap(source_mapping, 5 * page_size) == -1,
	       "unable to unmap source mapping");
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	page_size = sysconf(_SC_PAGE_SIZE);

	// test क्रम kernel support क्रम MREMAP_DONTUNMAP skipping the test अगर
	// not.
	अगर (kernel_support_क्रम_mremap_करोntunmap() != 0) अणु
		म_लिखो("No kernel support for MREMAP_DONTUNMAP\n");
		वापस KSFT_SKIP;
	पूर्ण

	// Keep a page sized buffer around क्रम when we need it.
	page_buffer =
	    mmap(शून्य, page_size, PROT_READ | PROT_WRITE,
		 MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	BUG_ON(page_buffer == MAP_FAILED, "unable to mmap a page.");

	mremap_करोntunmap_simple();
	mremap_करोntunmap_simple_shmem();
	mremap_करोntunmap_simple_fixed();
	mremap_करोntunmap_partial_mapping();
	mremap_करोntunmap_partial_mapping_overग_लिखो();

	BUG_ON(munmap(page_buffer, page_size) == -1,
	       "unable to unmap page buffer");

	म_लिखो("OK\n");
	वापस 0;
पूर्ण
