<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2018, Breno Leitao, IBM Corp.
 * Licensed under GPLv2.
 *
 * Sigfuz(पंचांग): A PowerPC TM-aware संकेत fuzzer.
 *
 * This is a new selftest that उठाओs SIGUSR1 संकेतs and handles it in a set
 * of dअगरferent ways, trying to create dअगरferent scenario क्रम testing
 * purpose.
 *
 * This test works raising a संकेत and calling sigवापस पूर्णांकerleaved with
 * TM operations, as starting, suspending and terminating a transaction. The
 * test depends on अक्रमom numbers, and, based on them, it sets dअगरferent TM
 * states.
 *
 * Other than that, the test fills out the user context काष्ठा that is passed
 * to the sigवापस प्रणाली call with अक्रमom data, in order to make sure that
 * the संकेत handler syscall can handle dअगरferent and invalid states
 * properly.
 *
 * This selftest has command line parameters to control what kind of tests the
 * user wants to run, as क्रम example, अगर a transaction should be started prior
 * to संकेत being उठाओd, or, after the संकेत being उठाओd and beक्रमe the
 * sigवापस. If no parameter is given, the शेष is enabling all options.
 *
 * This test करोes not check अगर the user context is being पढ़ो and set
 * properly by the kernel. Its purpose, at this समय, is basically
 * guaranteeing that the kernel करोes not crash on invalid scenarios.
 */

#समावेश <मानकपन.स>
#समावेश <सीमा.स>
#समावेश <sys/रुको.h>
#समावेश <unistd.h>
#समावेश <मानककोष.स>
#समावेश <संकेत.स>
#समावेश <माला.स>
#समावेश <ucontext.h>
#समावेश <sys/mman.h>
#समावेश <pthपढ़ो.h>
#समावेश "utils.h"

/* Selftest शेषs */
#घोषणा COUNT_MAX	600		/* Number of पूर्णांकeractions */
#घोषणा THREADS		16		/* Number of thपढ़ोs */

/* Arguments options */
#घोषणा ARG_MESS_WITH_TM_AT	0x1
#घोषणा ARG_MESS_WITH_TM_BEFORE	0x2
#घोषणा ARG_MESS_WITH_MSR_AT	0x4
#घोषणा ARG_FOREVER		0x10
#घोषणा ARG_COMPLETE		(ARG_MESS_WITH_TM_AT |		\
				ARG_MESS_WITH_TM_BEFORE |	\
				ARG_MESS_WITH_MSR_AT)

अटल पूर्णांक args;
अटल पूर्णांक nthपढ़ो = THREADS;
अटल पूर्णांक count_max = COUNT_MAX;

/* checkpoपूर्णांक context */
अटल ucontext_t *पंचांगp_uc;

/* Return true with 1/x probability */
अटल पूर्णांक one_in_chance(पूर्णांक x)
अणु
	वापस अक्रम() % x == 0;
पूर्ण

/* Change TM states */
अटल व्योम mess_with_पंचांग(व्योम)
अणु
	/* Starts a transaction 33% of the समय */
	अगर (one_in_chance(3)) अणु
		यंत्र ("tbegin.	;"
		     "beq 8	;");

		/* And suspended half of them */
		अगर (one_in_chance(2))
			यंत्र("tsuspend.	;");
	पूर्ण

	/* Call 'tend' in 5% of the runs */
	अगर (one_in_chance(20))
		यंत्र("tend.	;");
पूर्ण

/* Signal handler that will be invoked with उठाओ() */
अटल व्योम trap_संकेत_handler(पूर्णांक signo, siginfo_t *si, व्योम *uc)
अणु
	ucontext_t *ucp = uc;

	ucp->uc_link = पंचांगp_uc;

	/*
	 * Set uc_link in three possible ways:
	 *  - Setting a single 'int' in the whole chunk
	 *  - Cloning ucp पूर्णांकo uc_link
	 *  - Allocating a new memory chunk
	 */
	अगर (one_in_chance(3)) अणु
		स_रखो(ucp->uc_link, अक्रम(), माप(ucontext_t));
	पूर्ण अन्यथा अगर (one_in_chance(2)) अणु
		स_नकल(ucp->uc_link, uc, माप(ucontext_t));
	पूर्ण अन्यथा अगर (one_in_chance(2)) अणु
		अगर (पंचांगp_uc) अणु
			मुक्त(पंचांगp_uc);
			पंचांगp_uc = शून्य;
		पूर्ण
		पंचांगp_uc = दो_स्मृति(माप(ucontext_t));
		ucp->uc_link = पंचांगp_uc;
		/* Trying to cause a major page fault at Kernel level */
		madvise(ucp->uc_link, माप(ucontext_t), MADV_DONTNEED);
	पूर्ण

	अगर (args & ARG_MESS_WITH_MSR_AT) अणु
		/* Changing the checkpoपूर्णांकed रेजिस्टरs */
		अगर (one_in_chance(4)) अणु
			ucp->uc_link->uc_mcontext.gp_regs[PT_MSR] |= MSR_TS_S;
		पूर्ण अन्यथा अणु
			अगर (one_in_chance(2)) अणु
				ucp->uc_link->uc_mcontext.gp_regs[PT_MSR] |=
						 MSR_TS_T;
			पूर्ण अन्यथा अगर (one_in_chance(2)) अणु
				ucp->uc_link->uc_mcontext.gp_regs[PT_MSR] |=
						MSR_TS_T | MSR_TS_S;
			पूर्ण
		पूर्ण

		/* Checking the current रेजिस्टर context */
		अगर (one_in_chance(2)) अणु
			ucp->uc_mcontext.gp_regs[PT_MSR] |= MSR_TS_S;
		पूर्ण अन्यथा अगर (one_in_chance(2)) अणु
			अगर (one_in_chance(2))
				ucp->uc_mcontext.gp_regs[PT_MSR] |=
					MSR_TS_T;
			अन्यथा अगर (one_in_chance(2))
				ucp->uc_mcontext.gp_regs[PT_MSR] |=
					MSR_TS_T | MSR_TS_S;
		पूर्ण
	पूर्ण

	अगर (one_in_chance(20)) अणु
		/* Nested transaction start */
		अगर (one_in_chance(5))
			mess_with_पंचांग();

		/* Return without changing any other context info */
		वापस;
	पूर्ण

	अगर (one_in_chance(10))
		ucp->uc_mcontext.gp_regs[PT_MSR] = अक्रमom();
	अगर (one_in_chance(10))
		ucp->uc_mcontext.gp_regs[PT_NIP] = अक्रमom();
	अगर (one_in_chance(10))
		ucp->uc_link->uc_mcontext.gp_regs[PT_MSR] = अक्रमom();
	अगर (one_in_chance(10))
		ucp->uc_link->uc_mcontext.gp_regs[PT_NIP] = अक्रमom();

	ucp->uc_mcontext.gp_regs[PT_TRAP] = अक्रमom();
	ucp->uc_mcontext.gp_regs[PT_DSISR] = अक्रमom();
	ucp->uc_mcontext.gp_regs[PT_DAR] = अक्रमom();
	ucp->uc_mcontext.gp_regs[PT_ORIG_R3] = अक्रमom();
	ucp->uc_mcontext.gp_regs[PT_XER] = अक्रमom();
	ucp->uc_mcontext.gp_regs[PT_RESULT] = अक्रमom();
	ucp->uc_mcontext.gp_regs[PT_SOFTE] = अक्रमom();
	ucp->uc_mcontext.gp_regs[PT_DSCR] = अक्रमom();
	ucp->uc_mcontext.gp_regs[PT_CTR] = अक्रमom();
	ucp->uc_mcontext.gp_regs[PT_LNK] = अक्रमom();
	ucp->uc_mcontext.gp_regs[PT_CCR] = अक्रमom();
	ucp->uc_mcontext.gp_regs[PT_REGS_COUNT] = अक्रमom();

	ucp->uc_link->uc_mcontext.gp_regs[PT_TRAP] = अक्रमom();
	ucp->uc_link->uc_mcontext.gp_regs[PT_DSISR] = अक्रमom();
	ucp->uc_link->uc_mcontext.gp_regs[PT_DAR] = अक्रमom();
	ucp->uc_link->uc_mcontext.gp_regs[PT_ORIG_R3] = अक्रमom();
	ucp->uc_link->uc_mcontext.gp_regs[PT_XER] = अक्रमom();
	ucp->uc_link->uc_mcontext.gp_regs[PT_RESULT] = अक्रमom();
	ucp->uc_link->uc_mcontext.gp_regs[PT_SOFTE] = अक्रमom();
	ucp->uc_link->uc_mcontext.gp_regs[PT_DSCR] = अक्रमom();
	ucp->uc_link->uc_mcontext.gp_regs[PT_CTR] = अक्रमom();
	ucp->uc_link->uc_mcontext.gp_regs[PT_LNK] = अक्रमom();
	ucp->uc_link->uc_mcontext.gp_regs[PT_CCR] = अक्रमom();
	ucp->uc_link->uc_mcontext.gp_regs[PT_REGS_COUNT] = अक्रमom();

	अगर (args & ARG_MESS_WITH_TM_BEFORE) अणु
		अगर (one_in_chance(2))
			mess_with_पंचांग();
	पूर्ण
पूर्ण

अटल व्योम seg_संकेत_handler(पूर्णांक signo, siginfo_t *si, व्योम *uc)
अणु
	/* Clear निकास क्रम process that segfaults */
	निकास(0);
पूर्ण

अटल व्योम *sigfuz_test(व्योम *thrid)
अणु
	काष्ठा sigaction trap_sa, seg_sa;
	पूर्णांक ret, i = 0;
	pid_t t;

	पंचांगp_uc = दो_स्मृति(माप(ucontext_t));

	/* Main संकेत handler */
	trap_sa.sa_flags = SA_SIGINFO;
	trap_sa.sa_sigaction = trap_संकेत_handler;

	/* संक_अंश संकेत handler */
	seg_sa.sa_flags = SA_SIGINFO;
	seg_sa.sa_sigaction = seg_संकेत_handler;

	/* The संकेत handler will enable MSR_TS */
	sigaction(SIGUSR1, &trap_sa, शून्य);

	/* If it करोes not crash, it will segfault, aव्योम it to retest */
	sigaction(संक_अंश, &seg_sa, शून्य);

	जबतक (i < count_max) अणु
		t = विभाजन();

		अगर (t == 0) अणु
			/* Once seed per process */
			बेक्रम(समय(शून्य) + getpid());
			अगर (args & ARG_MESS_WITH_TM_AT) अणु
				अगर (one_in_chance(2))
					mess_with_पंचांग();
			पूर्ण
			उठाओ(SIGUSR1);
			निकास(0);
		पूर्ण अन्यथा अणु
			रुकोpid(t, &ret, 0);
		पूर्ण
		अगर (!(args & ARG_FOREVER))
			i++;
	पूर्ण

	/* If not मुक्तd alपढ़ोy, मुक्त now */
	अगर (पंचांगp_uc) अणु
		मुक्त(पंचांगp_uc);
		पंचांगp_uc = शून्य;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक संकेत_fuzzer(व्योम)
अणु
	पूर्णांक t, rc;
	pthपढ़ो_t *thपढ़ोs;

	thपढ़ोs = दो_स्मृति(nthपढ़ो * माप(pthपढ़ो_t));

	क्रम (t = 0; t < nthपढ़ो; t++) अणु
		rc = pthपढ़ो_create(&thपढ़ोs[t], शून्य, sigfuz_test,
				    (व्योम *)&t);
		अगर (rc)
			लिखो_त्रुटि("Thread creation error\n");
	पूर्ण

	क्रम (t = 0; t < nthपढ़ो; t++) अणु
		rc = pthपढ़ो_join(thपढ़ोs[t], शून्य);
		अगर (rc)
			लिखो_त्रुटि("Thread join error\n");
	पूर्ण

	मुक्त(thपढ़ोs);

	वापस निकास_सफल;
पूर्ण

अटल व्योम show_help(अक्षर *name)
अणु
	म_लिखो("%s: Sigfuzzer for powerpc\n", name);
	म_लिखो("Usage:\n");
	म_लिखो("\t-b\t Mess with TM before raising a SIGUSR1 signal\n");
	म_लिखो("\t-a\t Mess with TM after raising a SIGUSR1 signal\n");
	म_लिखो("\t-m\t Mess with MSR[TS] bits at mcontext\n");
	म_लिखो("\t-x\t Mess with everything above\n");
	म_लिखो("\ट-f\ट Run क्रमever (Press ^C to Quit)\न");
	म_लिखो("\t-i\t Amount of interactions.	(Default = %d)\n", COUNT_MAX);
	म_लिखो("\t-t\t Amount of threads.	(Default = %d)\n", THREADS);
	निकास(-1);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक opt;

	जबतक ((opt = getopt(argc, argv, "bamxt:fi:h")) != -1) अणु
		अगर (opt == 'b') अणु
			म_लिखो("Mess with TM before signal\n");
			args |= ARG_MESS_WITH_TM_BEFORE;
		पूर्ण अन्यथा अगर (opt == 'a') अणु
			म_लिखो("Mess with TM at signal handler\n");
			args |= ARG_MESS_WITH_TM_AT;
		पूर्ण अन्यथा अगर (opt == 'm') अणु
			म_लिखो("Mess with MSR[TS] bits in mcontext\n");
			args |= ARG_MESS_WITH_MSR_AT;
		पूर्ण अन्यथा अगर (opt == 'x') अणु
			म_लिखो("Running with all options enabled\n");
			args |= ARG_COMPLETE;
		पूर्ण अन्यथा अगर (opt == 't') अणु
			nthपढ़ो = म_से_प(optarg);
			म_लिखो("Threads = %d\n", nthपढ़ो);
		पूर्ण अन्यथा अगर (opt == 'f') अणु
			args |= ARG_FOREVER;
			म_लिखो("Press ^C to stop\न");
			test_harness_set_समयout(-1);
		पूर्ण अन्यथा अगर (opt == 'i') अणु
			count_max = म_से_प(optarg);
			म_लिखो("Running for %d interactions\n", count_max);
		पूर्ण अन्यथा अगर (opt == 'h') अणु
			show_help(argv[0]);
		पूर्ण
	पूर्ण

	/* Default test suite */
	अगर (!args)
		args = ARG_COMPLETE;

	test_harness(संकेत_fuzzer, "signal_fuzzer");
पूर्ण
