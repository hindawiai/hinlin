<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Copyright 2019, Michael Ellerman, IBM Corp.
//
// Test that out-of-bounds पढ़ोs/ग_लिखोs behave as expected.

#समावेश <समलाँघ.स>
#समावेश <stdbool.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/types.h>
#समावेश <sys/रुको.h>
#समावेश <unistd.h>

#समावेश "utils.h"

// Old distros (Ubuntu 16.04 at least) करोn't define this
#अगर_अघोषित SEGV_BNDERR
#घोषणा SEGV_BNDERR	3
#पूर्ण_अगर

// 64-bit kernel is always here
#घोषणा PAGE_OFFSET	(0xcul << 60)

अटल अचिन्हित दीर्घ kernel_virt_end;

अटल अस्थिर पूर्णांक fault_code;
अटल अस्थिर अचिन्हित दीर्घ fault_addr;
अटल लाँघ_बफ बनाओ_लाँघ_env;

अटल व्योम segv_handler(पूर्णांक n, siginfo_t *info, व्योम *ctxt_v)
अणु
	fault_code = info->si_code;
	fault_addr = (अचिन्हित दीर्घ)info->si_addr;
	sigदीर्घ_लाँघ(बनाओ_लाँघ_env, 1);
पूर्ण

पूर्णांक bad_access(अक्षर *p, bool ग_लिखो)
अणु
	अक्षर x = 0;

	fault_code = 0;
	fault_addr = 0;

	अगर (sigबनाओ_लाँघ(बनाओ_लाँघ_env, 1) == 0) अणु
		अगर (ग_लिखो)
			*p = 1;
		अन्यथा
			x = *p;

		म_लिखो("Bad - no SEGV! (%c)\n", x);
		वापस 1;
	पूर्ण

	// If we see MAPERR that means we took a page fault rather than an SLB
	// miss. We only expect to take page faults क्रम addresses within the
	// valid kernel range.
	FAIL_IF(fault_code == SEGV_MAPERR && \
		(fault_addr < PAGE_OFFSET || fault_addr >= kernel_virt_end));

	FAIL_IF(fault_code != SEGV_MAPERR && fault_code != SEGV_BNDERR);

	वापस 0;
पूर्ण

अटल पूर्णांक test(व्योम)
अणु
	अचिन्हित दीर्घ i, j, addr, region_shअगरt, page_shअगरt, page_size;
	काष्ठा sigaction sig;
	bool hash_mmu;

	sig = (काष्ठा sigaction) अणु
		.sa_sigaction = segv_handler,
		.sa_flags = SA_SIGINFO,
	पूर्ण;

	FAIL_IF(sigaction(संक_अंश, &sig, शून्य) != 0);

	FAIL_IF(using_hash_mmu(&hash_mmu));

	page_size = sysconf(_SC_PAGESIZE);
	अगर (page_size == (64 * 1024))
		page_shअगरt = 16;
	अन्यथा
		page_shअगरt = 12;

	अगर (page_size == (64 * 1024) || !hash_mmu) अणु
		region_shअगरt = 52;

		// We have 7 512T regions (4 kernel linear, vदो_स्मृति, io, vmemmap)
		kernel_virt_end = PAGE_OFFSET + (7 * (512ul << 40));
	पूर्ण अन्यथा अगर (page_size == (4 * 1024) && hash_mmu) अणु
		region_shअगरt = 46;

		// We have 7 64T regions (4 kernel linear, vदो_स्मृति, io, vmemmap)
		kernel_virt_end = PAGE_OFFSET + (7 * (64ul << 40));
	पूर्ण अन्यथा
		FAIL_IF(true);

	म_लिखो("Using %s MMU, PAGE_SIZE = %dKB start address 0x%016lx\n",
	       hash_mmu ? "hash" : "radix",
	       (1 << page_shअगरt) >> 10,
	       1ul << region_shअगरt);

	// This generates access patterns like:
	//   0x0010000000000000
	//   0x0010000000010000
	//   0x0010000000020000
	//   ...
	//   0x0014000000000000
	//   0x0018000000000000
	//   0x0020000000000000
	//   0x0020000000010000
	//   0x0020000000020000
	//   ...
	//   0xf400000000000000
	//   0xf800000000000000

	क्रम (i = 1; i <= ((0xful << 60) >> region_shअगरt); i++) अणु
		क्रम (j = page_shअगरt - 1; j < 60; j++) अणु
			अचिन्हित दीर्घ base, delta;

			base  = i << region_shअगरt;
			delta = 1ul << j;

			अगर (delta >= base)
				अवरोध;

			addr = (base | delta) & ~((1 << page_shअगरt) - 1);

			FAIL_IF(bad_access((अक्षर *)addr, false));
			FAIL_IF(bad_access((अक्षर *)addr, true));
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	test_harness_set_समयout(300);
	वापस test_harness(test, "bad_accesses");
पूर्ण
