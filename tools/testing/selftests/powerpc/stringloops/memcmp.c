<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <दो_स्मृति.h>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/mman.h>
#समावेश <समय.स>

#समावेश "utils.h"

#घोषणा SIZE 256
#घोषणा ITERATIONS 10000

#घोषणा LARGE_SIZE (5 * 1024)
#घोषणा LARGE_ITERATIONS 1000
#घोषणा LARGE_MAX_OFFSET 32
#घोषणा LARGE_SIZE_START 4096

/* This is big enough to fit LARGE_SIZE and works on 4K & 64K kernels */
#घोषणा MAP_SIZE (64 * 1024)

#घोषणा MAX_OFFSET_DIFF_S1_S2 48

पूर्णांक vmx_count;
पूर्णांक enter_vmx_ops(व्योम)
अणु
	vmx_count++;
	वापस 1;
पूर्ण

व्योम निकास_vmx_ops(व्योम)
अणु
	vmx_count--;
पूर्ण
पूर्णांक test_स_भेद(स्थिर व्योम *s1, स्थिर व्योम *s2, माप_प्रकार n);

/* test all offsets and lengths */
अटल व्योम test_one(अक्षर *s1, अक्षर *s2, अचिन्हित दीर्घ max_offset,
		अचिन्हित दीर्घ size_start, अचिन्हित दीर्घ max_size)
अणु
	अचिन्हित दीर्घ offset, size;

	क्रम (offset = 0; offset < max_offset; offset++) अणु
		क्रम (size = size_start; size < (max_size - offset); size++) अणु
			पूर्णांक x, y;
			अचिन्हित दीर्घ i;

			y = स_भेद(s1+offset, s2+offset, size);
			x = test_स_भेद(s1+offset, s2+offset, size);

			अगर (((x ^ y) < 0) &&	/* Trick to compare sign */
				((x | y) != 0)) अणु /* check क्रम zero */
				म_लिखो("memcmp returned %d, should have returned %d (offset %ld size %ld)\n", x, y, offset, size);

				क्रम (i = offset; i < offset+size; i++)
					म_लिखो("%02x ", s1[i]);
				म_लिखो("\n");

				क्रम (i = offset; i < offset+size; i++)
					म_लिखो("%02x ", s2[i]);
				म_लिखो("\n");
				पात();
			पूर्ण

			अगर (vmx_count != 0) अणु
				म_लिखो("vmx enter/exit not paired.(offset:%ld size:%ld s1:%p s2:%p vc:%d\n",
					offset, size, s1, s2, vmx_count);
				म_लिखो("\n");
				पात();
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक testहाल(bool islarge)
अणु
	अचिन्हित दीर्घ i, comp_size, alloc_size;
	अक्षर *p, *s1, *s2;
	पूर्णांक iterations;

	comp_size = (islarge ? LARGE_SIZE : SIZE);
	alloc_size = comp_size + MAX_OFFSET_DIFF_S1_S2;
	iterations = islarge ? LARGE_ITERATIONS : ITERATIONS;

	p = mmap(शून्य, 4 * MAP_SIZE, PROT_READ | PROT_WRITE,
		 MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	FAIL_IF(p == MAP_FAILED);

	/* Put s1/s2 at the end of a page */
	s1 = p + MAP_SIZE - alloc_size;
	s2 = p + 3 * MAP_SIZE - alloc_size;

	/* And unmap the subsequent page to क्रमce a fault अगर we overपढ़ो */
	munmap(p + MAP_SIZE, MAP_SIZE);
	munmap(p + 3 * MAP_SIZE, MAP_SIZE);

	बेक्रमom(समय(0));

	क्रम (i = 0; i < iterations; i++) अणु
		अचिन्हित दीर्घ j;
		अचिन्हित दीर्घ change;
		अक्षर *अक्रम_s1 = s1;
		अक्षर *अक्रम_s2 = s2;

		क्रम (j = 0; j < alloc_size; j++)
			s1[j] = अक्रमom();

		अक्रम_s1 += अक्रमom() % MAX_OFFSET_DIFF_S1_S2;
		अक्रम_s2 += अक्रमom() % MAX_OFFSET_DIFF_S1_S2;
		स_नकल(अक्रम_s2, अक्रम_s1, comp_size);

		/* change one byte */
		change = अक्रमom() % comp_size;
		अक्रम_s2[change] = अक्रमom() & 0xff;

		अगर (islarge)
			test_one(अक्रम_s1, अक्रम_s2, LARGE_MAX_OFFSET,
					LARGE_SIZE_START, comp_size);
		अन्यथा
			test_one(अक्रम_s1, अक्रम_s2, SIZE, 0, comp_size);
	पूर्ण

	बेक्रमom(समय(0));

	क्रम (i = 0; i < iterations; i++) अणु
		अचिन्हित दीर्घ j;
		अचिन्हित दीर्घ change;
		अक्षर *अक्रम_s1 = s1;
		अक्षर *अक्रम_s2 = s2;

		क्रम (j = 0; j < alloc_size; j++)
			s1[j] = अक्रमom();

		अक्रम_s1 += अक्रमom() % MAX_OFFSET_DIFF_S1_S2;
		अक्रम_s2 += अक्रमom() % MAX_OFFSET_DIFF_S1_S2;
		स_नकल(अक्रम_s2, अक्रम_s1, comp_size);

		/* change multiple bytes, 1/8 of total */
		क्रम (j = 0; j < comp_size / 8; j++) अणु
			change = अक्रमom() % comp_size;
			s2[change] = अक्रमom() & 0xff;
		पूर्ण

		अगर (islarge)
			test_one(अक्रम_s1, अक्रम_s2, LARGE_MAX_OFFSET,
					LARGE_SIZE_START, comp_size);
		अन्यथा
			test_one(अक्रम_s1, अक्रम_s2, SIZE, 0, comp_size);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक testहालs(व्योम)
अणु
#अगर_घोषित __घातerpc64__
	// vcmpequd used in स_भेद_64.S is v2.07
	SKIP_IF(!have_hwcap2(PPC_FEATURE2_ARCH_2_07));
#पूर्ण_अगर

	testहाल(0);
	testहाल(1);
	वापस 0;
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	test_harness_set_समयout(300);
	वापस test_harness(testहालs, "memcmp");
पूर्ण
