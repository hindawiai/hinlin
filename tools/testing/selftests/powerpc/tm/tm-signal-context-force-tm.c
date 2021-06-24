<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2018, Breno Leitao, Gustavo Romero, IBM Corp.
 *
 * This test उठाओs a SIGUSR1 संकेत, and toggle the MSR[TS]
 * fields at the संकेत handler. With MSR[TS] being set, the kernel will
 * क्रमce a recheckpoपूर्णांक, which may cause a segfault when वापसing to
 * user space. Since the test needs to re-run, the segfault needs to be
 * caught and handled.
 *
 * In order to जारी the test even after a segfault, the context is
 * saved prior to the संकेत being उठाओd, and it is restored when there is
 * a segmentation fault. This happens क्रम COUNT_MAX बार.
 *
 * This test never fails (as वापसing निकास_त्रुटि). It either succeeds,
 * or crash the kernel (on a buggy kernel).
 */

#घोषणा _GNU_SOURCE
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <संकेत.स>
#समावेश <माला.स>
#समावेश <ucontext.h>
#समावेश <unistd.h>
#समावेश <sys/mman.h>

#समावेश "tm.h"
#समावेश "utils.h"
#समावेश "reg.h"

#घोषणा COUNT_MAX       5000		/* Number of पूर्णांकeractions */

/*
 * This test only runs on 64 bits प्रणाली. Unsetting MSR_TS_S to aव्योम
 * compilation issue on 32 bits प्रणाली. There is no side effect, since the
 * whole test will be skipped अगर it is not running on 64 bits प्रणाली.
 */
#अगर_अघोषित __घातerpc64__
#अघोषित  MSR_TS_S
#घोषणा MSR_TS_S	0
#पूर्ण_अगर

/* Setting contexts because the test will crash and we want to recover */
ucontext_t init_context;

/* count is changed in the संकेत handler, so it must be अस्थिर */
अटल अस्थिर पूर्णांक count;

व्योम usr_संकेत_handler(पूर्णांक signo, siginfo_t *si, व्योम *uc)
अणु
	ucontext_t *ucp = uc;
	पूर्णांक ret;

	/*
	 * Allocating memory in a संकेत handler, and never मुक्तing it on
	 * purpose, क्रमcing the heap increase, so, the memory leak is what
	 * we want here.
	 */
	ucp->uc_link = mmap(शून्य, माप(ucontext_t),
			    PROT_READ | PROT_WRITE,
			    MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
	अगर (ucp->uc_link == (व्योम *)-1) अणु
		लिखो_त्रुटि("Mmap failed");
		निकास(-1);
	पूर्ण

	/* Forcing the page to be allocated in a page fault */
	ret = madvise(ucp->uc_link, माप(ucontext_t), MADV_DONTNEED);
	अगर (ret) अणु
		लिखो_त्रुटि("madvise failed");
		निकास(-1);
	पूर्ण

	स_नकल(&ucp->uc_link->uc_mcontext, &ucp->uc_mcontext,
		माप(ucp->uc_mcontext));

	/* Forcing to enable MSR[TM] */
	UCONTEXT_MSR(ucp) |= MSR_TS_S;

	/*
	 * A विभाजन inside a संकेत handler seems to be more efficient than a
	 * विभाजन() prior to the संकेत being उठाओd.
	 */
	अगर (विभाजन() == 0) अणु
		/*
		 * Both child and parent will वापस, but, child वापसs
		 * with count set so it will निकास in the next segfault.
		 * Parent will जारी to loop.
		 */
		count = COUNT_MAX;
	पूर्ण

	/*
	 * If the change above करोes not hit the bug, it will cause a
	 * segmentation fault, since the ck काष्ठाures are शून्य.
	 */
पूर्ण

व्योम seg_संकेत_handler(पूर्णांक signo, siginfo_t *si, व्योम *uc)
अणु
	count++;

	/* Reexecute the test */
	setcontext(&init_context);
पूर्ण

व्योम पंचांग_trap_test(व्योम)
अणु
	काष्ठा sigaction usr_sa, seg_sa;
	stack_t ss;

	usr_sa.sa_flags = SA_SIGINFO | SA_ONSTACK;
	usr_sa.sa_sigaction = usr_संकेत_handler;

	seg_sa.sa_flags = SA_SIGINFO;
	seg_sa.sa_sigaction = seg_संकेत_handler;

	/*
	 * Set initial context. Will get back here from
	 * seg_संकेत_handler()
	 */
	अ_लोontext(&init_context);

	जबतक (count < COUNT_MAX) अणु
		/* Allocated an alternative संकेत stack area */
		ss.ss_sp = mmap(शून्य, SIGSTKSZ, PROT_READ | PROT_WRITE,
				MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
		ss.ss_size = SIGSTKSZ;
		ss.ss_flags = 0;

		अगर (ss.ss_sp == (व्योम *)-1) अणु
			लिखो_त्रुटि("mmap error\n");
			निकास(-1);
		पूर्ण

		/* Force the allocation through a page fault */
		अगर (madvise(ss.ss_sp, SIGSTKSZ, MADV_DONTNEED)) अणु
			लिखो_त्रुटि("madvise\n");
			निकास(-1);
		पूर्ण

		/*
		 * Setting an alternative stack to generate a page fault when
		 * the संकेत is उठाओd.
		 */
		अगर (sigaltstack(&ss, शून्य)) अणु
			लिखो_त्रुटि("sigaltstack\n");
			निकास(-1);
		पूर्ण

		/* The संकेत handler will enable MSR_TS */
		sigaction(SIGUSR1, &usr_sa, शून्य);
		/* If it करोes not crash, it might segfault, aव्योम it to retest */
		sigaction(संक_अंश, &seg_sa, शून्य);

		उठाओ(SIGUSR1);
		count++;
	पूर्ण
पूर्ण

पूर्णांक पंचांग_संकेत_context_क्रमce_पंचांग(व्योम)
अणु
	SKIP_IF(!have_hपंचांग());
	/*
	 * Skipping अगर not running on 64 bits प्रणाली, since I think it is
	 * not possible to set mcontext's [MSR] with TS, due to it being 32
	 * bits.
	 */
	SKIP_IF(!is_ppc64le());

	पंचांग_trap_test();

	वापस निकास_सफल;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	test_harness(पंचांग_संकेत_context_क्रमce_पंचांग, "tm_signal_context_force_tm");
पूर्ण
