<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+

/*
 * Copyright 2018 IBM Corporation.
 */

#घोषणा __SANE_USERSPACE_TYPES__

#समावेश <sys/types.h>
#समावेश <मानक_निवेशt.h>
#समावेश <unistd.h>
#समावेश <संकेत.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <मानकपन.स>
#समावेश <sys/utsname.h>
#समावेश "utils.h"
#समावेश "flush_utils.h"

अटल अंतरभूत __u64 load(व्योम *addr)
अणु
	__u64 पंचांगp;

	यंत्र अस्थिर("ld %0,0(%1)" : "=r"(पंचांगp) : "b"(addr));

	वापस पंचांगp;
पूर्ण

व्योम syscall_loop(अक्षर *p, अचिन्हित दीर्घ iterations,
		  अचिन्हित दीर्घ zero_size)
अणु
	क्रम (अचिन्हित दीर्घ i = 0; i < iterations; i++) अणु
		क्रम (अचिन्हित दीर्घ j = 0; j < zero_size; j += CACHELINE_SIZE)
			load(p + j);
		getppid();
	पूर्ण
पूर्ण

व्योम syscall_loop_uaccess(अक्षर *p, अचिन्हित दीर्घ iterations,
			  अचिन्हित दीर्घ zero_size)
अणु
	काष्ठा utsname utsname;

	क्रम (अचिन्हित दीर्घ i = 0; i < iterations; i++) अणु
		क्रम (अचिन्हित दीर्घ j = 0; j < zero_size; j += CACHELINE_SIZE)
			load(p + j);
		uname(&utsname);
	पूर्ण
पूर्ण

अटल व्योम sigill_handler(पूर्णांक signr, siginfo_t *info, व्योम *unused)
अणु
	अटल पूर्णांक warned;
	ucontext_t *ctx = (ucontext_t *)unused;
	अचिन्हित दीर्घ *pc = &UCONTEXT_NIA(ctx);

	/* mtspr 3,RS to check क्रम move to DSCR below */
	अगर ((*((अचिन्हित पूर्णांक *)*pc) & 0xfc1fffff) == 0x7c0303a6) अणु
		अगर (!warned++)
			म_लिखो("WARNING: Skipping over dscr setup. Consider running 'ppc64_cpu --dscr=1' manually.\n");
		*pc += 4;
	पूर्ण अन्यथा अणु
		म_लिखो("SIGILL at %p\n", pc);
		पात();
	पूर्ण
पूर्ण

व्योम set_dscr(अचिन्हित दीर्घ val)
अणु
	अटल पूर्णांक init;
	काष्ठा sigaction sa;

	अगर (!init) अणु
		स_रखो(&sa, 0, माप(sa));
		sa.sa_sigaction = sigill_handler;
		sa.sa_flags = SA_SIGINFO;
		अगर (sigaction(संक_अवैध, &sa, शून्य))
			लिखो_त्रुटि("sigill_handler");
		init = 1;
	पूर्ण

	यंत्र अस्थिर("mtspr %1,%0" : : "r" (val), "i" (SPRN_DSCR));
पूर्ण
