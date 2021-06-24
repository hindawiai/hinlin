<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2016, Michael Ellerman, IBM Corp.
 */

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/mman.h>
#समावेश <unistd.h>

#समावेश <यंत्र/cputable.h>

#समावेश "utils.h"

#घोषणा SIZE (64 * 1024)

पूर्णांक test_prot_sao(व्योम)
अणु
	अक्षर *p;

	/*
	 * SAO was पूर्णांकroduced in 2.06 and हटाओd in 3.1. It's disabled in
	 * guests/LPARs by शेष, so also skip अगर we are running in a guest.
	 */
	SKIP_IF(!have_hwcap(PPC_FEATURE_ARCH_2_06) ||
		have_hwcap2(PPC_FEATURE2_ARCH_3_1) ||
		access("/proc/device-tree/rtas/ibm,hypertas-functions", F_OK) == 0);

	/*
	 * Ensure we can ask क्रम PROT_SAO.
	 * We can't really verअगरy that it करोes the right thing, but at least we
	 * confirm the kernel will accept it.
	 */
	p = mmap(शून्य, SIZE, PROT_READ | PROT_WRITE | PROT_SAO,
		 MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	FAIL_IF(p == MAP_FAILED);

	/* Write to the mapping, to at least cause a fault */
	स_रखो(p, 0xaa, SIZE);

	वापस 0;
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	वापस test_harness(test_prot_sao, "prot-sao");
पूर्ण
