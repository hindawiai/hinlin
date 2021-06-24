<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Test that we can take संकेतs with and without the VDSO mapped, which trigger
 * dअगरferent paths in the संकेत handling code.
 *
 * See handle_rt_संकेत64() and setup_trampoline() in संकेत_64.c
 */

#घोषणा _GNU_SOURCE

#समावेश <त्रुटिसं.स>
#समावेश <मानकपन.स>
#समावेश <संकेत.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/mman.h>
#समावेश <sys/types.h>
#समावेश <unistd.h>

// Ensure निश्चित() is not compiled out
#अघोषित न_संशोधन
#समावेश <निश्चित.स>

#समावेश "utils.h"

अटल पूर्णांक search_proc_maps(अक्षर *needle, अचिन्हित दीर्घ *low, अचिन्हित दीर्घ *high)
अणु
	अचिन्हित दीर्घ start, end;
	अटल अक्षर buf[4096];
	अक्षर name[128];
	खाता *f;
	पूर्णांक rc = -1;

	f = ख_खोलो("/proc/self/maps", "r");
	अगर (!f) अणु
		लिखो_त्रुटि("fopen");
		वापस -1;
	पूर्ण

	जबतक (ख_माला_लो(buf, माप(buf), f)) अणु
		rc = माला_पूछो(buf, "%lx-%lx %*c%*c%*c%*c %*x %*d:%*d %*d %127s\n",
			    &start, &end, name);
		अगर (rc == 2)
			जारी;

		अगर (rc != 3) अणु
			म_लिखो("sscanf errored\n");
			rc = -1;
			अवरोध;
		पूर्ण

		अगर (म_माला(name, needle)) अणु
			*low = start;
			*high = end - 1;
			rc = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	ख_बंद(f);

	वापस rc;
पूर्ण

अटल अस्थिर संक_पूर्ण_प्रकार took_संकेत = 0;

अटल व्योम sigusr1_handler(पूर्णांक sig)
अणु
	took_संकेत++;
पूर्ण

पूर्णांक test_sigवापस_vdso(व्योम)
अणु
	अचिन्हित दीर्घ low, high, size;
	काष्ठा sigaction act;
	अक्षर *p;

	act.sa_handler = sigusr1_handler;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);

	निश्चित(sigaction(SIGUSR1, &act, शून्य) == 0);

	// Confirm the VDSO is mapped, and work out where it is
	निश्चित(search_proc_maps("[vdso]", &low, &high) == 0);
	size = high - low + 1;
	म_लिखो("VDSO is at 0x%lx-0x%lx (%lu bytes)\n", low, high, size);

	समाप्त(getpid(), SIGUSR1);
	निश्चित(took_संकेत == 1);
	म_लिखो("Signal delivered OK with VDSO mapped\n");

	// Remap the VDSO somewhere अन्यथा
	p = mmap(शून्य, size, PROT_READ|PROT_WRITE, MAP_ANONYMOUS|MAP_PRIVATE, -1, 0);
	निश्चित(p != MAP_FAILED);
	निश्चित(mremap((व्योम *)low, size, size, MREMAP_MAYMOVE|MREMAP_FIXED, p) != MAP_FAILED);
	निश्चित(search_proc_maps("[vdso]", &low, &high) == 0);
	size = high - low + 1;
	म_लिखो("VDSO moved to 0x%lx-0x%lx (%lu bytes)\n", low, high, size);

	समाप्त(getpid(), SIGUSR1);
	निश्चित(took_संकेत == 2);
	म_लिखो("Signal delivered OK with VDSO moved\n");

	निश्चित(munmap((व्योम *)low, size) == 0);
	म_लिखो("Unmapped VDSO\n");

	// Confirm the VDSO is not mapped anymore
	निश्चित(search_proc_maps("[vdso]", &low, &high) != 0);

	// Make the stack executable
	निश्चित(search_proc_maps("[stack]", &low, &high) == 0);
	size = high - low + 1;
	mprotect((व्योम *)low, size, PROT_READ|PROT_WRITE|PROT_EXEC);
	म_लिखो("Remapped the stack executable\n");

	समाप्त(getpid(), SIGUSR1);
	निश्चित(took_संकेत == 3);
	म_लिखो("Signal delivered OK with VDSO unmapped\n");

	वापस 0;
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	वापस test_harness(test_sigवापस_vdso, "sigreturn_vdso");
पूर्ण
