<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * sysret_ss_attrs.c - test that syscalls वापस valid hidden SS attributes
 * Copyright (c) 2015 Andrew Lutomirski
 *
 * On AMD CPUs, SYSRET can वापस with a valid SS descriptor with with
 * the hidden attributes set to an unusable state.  Make sure the kernel
 * करोesn't let this happen.
 */

#घोषणा _GNU_SOURCE

#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <sys/mman.h>
#समावेश <err.h>
#समावेश <मानकघोष.स>
#समावेश <stdbool.h>
#समावेश <pthपढ़ो.h>

अटल व्योम *thपढ़ोproc(व्योम *ctx)
अणु
	/*
	 * Do our best to cause sleeps on this CPU to निकास the kernel and
	 * re-enter with SS = 0.
	 */
	जबतक (true)
		;

	वापस शून्य;
पूर्ण

#अगर_घोषित __x86_64__
बाह्य अचिन्हित दीर्घ call32_from_64(व्योम *stack, व्योम (*function)(व्योम));

यंत्र (".pushsection .text\n\t"
     ".code32\n\t"
     "test_ss:\n\t"
     "pushl $0\n\t"
     "popl %eax\n\t"
     "ret\n\t"
     ".code64");
बाह्य व्योम test_ss(व्योम);
#पूर्ण_अगर

पूर्णांक मुख्य()
अणु
	/*
	 * Start a busy-looping thपढ़ो on the same CPU we're on.
	 * For simplicity, just stick everything to CPU 0.  This will
	 * fail in some containers, but that's probably okay.
	 */
	cpu_set_t cpuset;
	CPU_ZERO(&cpuset);
	CPU_SET(0, &cpuset);
	अगर (sched_setaffinity(0, माप(cpuset), &cpuset) != 0)
		म_लिखो("[WARN]\tsched_setaffinity failed\n");

	pthपढ़ो_t thपढ़ो;
	अगर (pthपढ़ो_create(&thपढ़ो, 0, thपढ़ोproc, 0) != 0)
		err(1, "pthread_create");

#अगर_घोषित __x86_64__
	अचिन्हित अक्षर *stack32 = mmap(शून्य, 4096, PROT_READ | PROT_WRITE,
				      MAP_32BIT | MAP_ANONYMOUS | MAP_PRIVATE,
				      -1, 0);
	अगर (stack32 == MAP_FAILED)
		err(1, "mmap");
#पूर्ण_अगर

	म_लिखो("[RUN]\tSyscalls followed by SS validation\n");

	क्रम (पूर्णांक i = 0; i < 1000; i++) अणु
		/*
		 * Go to sleep and वापस using sysret (अगर we're 64-bit
		 * or we're 32-bit on AMD on a 64-bit kernel).  On AMD CPUs,
		 * SYSRET करोesn't fix up the cached SS descriptor, so the
		 * kernel needs some kind of workaround to make sure that we
		 * end the प्रणाली call with a valid stack segment.  This
		 * can be a confusing failure because the SS *selector*
		 * is the same regardless.
		 */
		usleep(2);

#अगर_घोषित __x86_64__
		/*
		 * On 32-bit, just करोing a syscall through glibc is enough
		 * to cause a crash अगर our cached SS descriptor is invalid.
		 * On 64-bit, it's not, so try extra hard.
		 */
		call32_from_64(stack32 + 4088, test_ss);
#पूर्ण_अगर
	पूर्ण

	म_लिखो("[OK]\tWe survived\n");

#अगर_घोषित __x86_64__
	munmap(stack32, 4096);
#पूर्ण_अगर

	वापस 0;
पूर्ण
