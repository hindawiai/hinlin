<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2015, Michael Neuling, IBM Corp.
 *
 * Original: Michael Neuling 4/12/2013
 * Edited: Rashmica Gupta 4/12/2015
 *
 * See अगर the altivec state is leaked out of an पातed transaction due to
 * kernel vmx copy loops.
 *
 * When the transaction पातs, VSR values should rollback to the values
 * they held beक्रमe the transaction commenced. Using VSRs जबतक transaction
 * is suspended should not affect the checkpoपूर्णांकed values.
 *
 * (1) ग_लिखो A to a VSR
 * (2) start transaction
 * (3) suspend transaction
 * (4) change the VSR to B
 * (5) trigger kernel vmx copy loop
 * (6) पात transaction
 * (7) check that the VSR value is A
 */

#समावेश <पूर्णांकtypes.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <sys/mman.h>
#समावेश <माला.स>
#समावेश <निश्चित.स>

#समावेश "tm.h"
#समावेश "utils.h"

पूर्णांक test_vmxcopy()
अणु
	दीर्घ द्विगुन vecin = 1.3;
	दीर्घ द्विगुन vecout;
	अचिन्हित दीर्घ pgsize = getpagesize();
	पूर्णांक i;
	पूर्णांक fd;
	पूर्णांक size = pgsize*16;
	अक्षर क्षणिक_ख[] = "/tmp/page_faultXXXXXX";
	अक्षर buf[pgsize];
	अक्षर *a;
	uपूर्णांक64_t पातed = 0;

	SKIP_IF(!have_hपंचांग());
	SKIP_IF(!is_ppc64le());

	fd = mkstemp(क्षणिक_ख);
	निश्चित(fd >= 0);

	स_रखो(buf, 0, pgsize);
	क्रम (i = 0; i < size; i += pgsize)
		निश्चित(ग_लिखो(fd, buf, pgsize) == pgsize);

	unlink(क्षणिक_ख);

	a = mmap(शून्य, size, PROT_READ|PROT_WRITE, MAP_PRIVATE, fd, 0);
	निश्चित(a != MAP_FAILED);

	यंत्र __अस्थिर__(
		"lxvd2x 40,0,%[vecinptr];"	/* set 40 to initial value*/
		"tbegin.;"
		"beq	3f;"
		"tsuspend.;"
		"xxlxor 40,40,40;"		/* set 40 to 0 */
		"std	5, 0(%[map]);"		/* cause kernel vmx copy page */
		"tabort. 0;"
		"tresume.;"
		"tend.;"
		"li	%[res], 0;"
		"b	5f;"

		/* Abort handler */
		"3:;"
		"li	%[res], 1;"

		"5:;"
		"stxvd2x 40,0,%[vecoutptr];"
		: [res]"=&r"(पातed)
		: [vecinptr]"r"(&vecin),
		  [vecoutptr]"r"(&vecout),
		  [map]"r"(a)
		: "memory", "r0", "r3", "r4", "r5", "r6", "r7");

	अगर (पातed && (vecin != vecout))अणु
		म_लिखो("FAILED: vector state leaked on abort %f != %f\n",
		       (द्विगुन)vecin, (द्विगुन)vecout);
		वापस 1;
	पूर्ण

	munmap(a, size);

	बंद(fd);

	वापस 0;
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	वापस test_harness(test_vmxcopy, "tm_vmxcopy");
पूर्ण
