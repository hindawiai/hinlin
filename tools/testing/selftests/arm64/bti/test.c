<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2019,2021  Arm Limited
 * Original author: Dave Martin <Dave.Martin@arm.com>
 */

#समावेश "system.h"

#समावेश <मानकघोष.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/auxvec.h>
#समावेश <linux/संकेत.स>
#समावेश <यंत्र/sigcontext.h>
#समावेश <यंत्र/ucontext.h>

प्रकार काष्ठा ucontext ucontext_t;

#समावेश "btitest.h"
#समावेश "compiler.h"
#समावेश "signal.h"

#घोषणा EXPECTED_TESTS 18

अटल अस्थिर अचिन्हित पूर्णांक test_num = 1;
अटल अचिन्हित पूर्णांक test_passed;
अटल अचिन्हित पूर्णांक test_failed;
अटल अचिन्हित पूर्णांक test_skipped;

अटल व्योम fdमाला_दो(पूर्णांक fd, स्थिर अक्षर *str)
अणु
	माप_प्रकार len = 0;
	स्थिर अक्षर *p = str;

	जबतक (*p++)
		++len;

	ग_लिखो(fd, str, len);
पूर्ण

अटल व्योम माला_दोtr(स्थिर अक्षर *str)
अणु
	fdमाला_दो(1, str);
पूर्ण

अटल व्योम putnum(अचिन्हित पूर्णांक num)
अणु
	अक्षर c;

	अगर (num / 10)
		putnum(num / 10);

	c = '0' + (num % 10);
	ग_लिखो(1, &c, 1);
पूर्ण

#घोषणा puttestname(test_name, trampoline_name) करो अणु	\
	माला_दोtr(test_name);				\
	माला_दोtr("/");					\
	माला_दोtr(trampoline_name);			\
पूर्ण जबतक (0)

व्योम prपूर्णांक_summary(व्योम)
अणु
	माला_दोtr("# Totals: pass:");
	putnum(test_passed);
	माला_दोtr(" fail:");
	putnum(test_failed);
	माला_दोtr(" xfail:0 xpass:0 skip:");
	putnum(test_skipped);
	माला_दोtr(" error:0\n");
पूर्ण

अटल स्थिर अक्षर *अस्थिर current_test_name;
अटल स्थिर अक्षर *अस्थिर current_trampoline_name;
अटल अस्थिर पूर्णांक sigill_expected, sigill_received;

अटल व्योम handler(पूर्णांक n, siginfo_t *si __always_unused,
		    व्योम *uc_ __always_unused)
अणु
	ucontext_t *uc = uc_;

	माला_दोtr("# \t[SIGILL in ");
	puttestname(current_test_name, current_trampoline_name);
	माला_दोtr(", BTYPE=");
	ग_लिखो(1, &"00011011"[((uc->uc_mcontext.pstate & PSR_BTYPE_MASK)
			      >> PSR_BTYPE_SHIFT) * 2], 2);
	अगर (!sigill_expected) अणु
		माला_दोtr("]\n");
		माला_दोtr("not ok ");
		putnum(test_num);
		माला_दोtr(" ");
		puttestname(current_test_name, current_trampoline_name);
		माला_दोtr("(unexpected SIGILL)\n");
		prपूर्णांक_summary();
		निकास(128 + n);
	पूर्ण

	माला_दोtr(" (expected)]\n");
	sigill_received = 1;
	/* zap BTYPE so that resuming the faulting code will work */
	uc->uc_mcontext.pstate &= ~PSR_BTYPE_MASK;
पूर्ण

अटल पूर्णांक skip_all;

अटल व्योम __करो_test(व्योम (*trampoline)(व्योम (*)(व्योम)),
		      व्योम (*fn)(व्योम),
		      स्थिर अक्षर *trampoline_name,
		      स्थिर अक्षर *name,
		      पूर्णांक expect_sigill)
अणु
	अगर (skip_all) अणु
		test_skipped++;
		माला_दोtr("ok ");
		putnum(test_num);
		माला_दोtr(" ");
		puttestname(name, trampoline_name);
		माला_दोtr(" # SKIP\n");

		वापस;
	पूर्ण

	/* Branch Target exceptions should only happen in BTI binaries: */
	अगर (!BTI)
		expect_sigill = 0;

	sigill_expected = expect_sigill;
	sigill_received = 0;
	current_test_name = name;
	current_trampoline_name = trampoline_name;

	trampoline(fn);

	अगर (expect_sigill && !sigill_received) अणु
		माला_दोtr("not ok ");
		test_failed++;
	पूर्ण अन्यथा अणु
		माला_दोtr("ok ");
		test_passed++;
	पूर्ण
	putnum(test_num++);
	माला_दोtr(" ");
	puttestname(name, trampoline_name);
	माला_दोtr("\n");
पूर्ण

#घोषणा करो_test(expect_sigill_br_x0,					\
		expect_sigill_br_x16,					\
		expect_sigill_blr,					\
		name)							\
करो अणु									\
	__करो_test(call_using_br_x0, name, "call_using_br_x0", #name,	\
		  expect_sigill_br_x0);					\
	__करो_test(call_using_br_x16, name, "call_using_br_x16", #name,	\
		  expect_sigill_br_x16);				\
	__करो_test(call_using_blr, name, "call_using_blr", #name,	\
		  expect_sigill_blr);					\
पूर्ण जबतक (0)

व्योम start(पूर्णांक *argcp)
अणु
	काष्ठा sigaction sa;
	व्योम *स्थिर *p;
	स्थिर काष्ठा auxv_entry अणु
		अचिन्हित दीर्घ type;
		अचिन्हित दीर्घ val;
	पूर्ण *auxv;
	अचिन्हित दीर्घ hwcap = 0, hwcap2 = 0;

	माला_दोtr("TAP version 13\n");
	माला_दोtr("1..");
	putnum(EXPECTED_TESTS);
	माला_दोtr("\n");

	/* Gross hack क्रम finding AT_HWCAP2 from the initial process stack: */
	p = (व्योम *स्थिर *)argcp + 1 + *argcp + 1; /* start of environment */
	/* step over environment */
	जबतक (*p++)
		;
	क्रम (auxv = (स्थिर काष्ठा auxv_entry *)p; auxv->type != AT_शून्य; ++auxv) अणु
		चयन (auxv->type) अणु
		हाल AT_HWCAP:
			hwcap = auxv->val;
			अवरोध;
		हाल AT_HWCAP2:
			hwcap2 = auxv->val;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (hwcap & HWCAP_PACA)
		माला_दोtr("# HWCAP_PACA present\n");
	अन्यथा
		माला_दोtr("# HWCAP_PACA not present\n");

	अगर (hwcap2 & HWCAP2_BTI) अणु
		माला_दोtr("# HWCAP2_BTI present\n");
		अगर (!(hwcap & HWCAP_PACA))
			माला_दोtr("# Bad hardware?  Expect problems.\n");
	पूर्ण अन्यथा अणु
		माला_दोtr("# HWCAP2_BTI not present\n");
		skip_all = 1;
	पूर्ण

	माला_दोtr("# Test binary");
	अगर (!BTI)
		माला_दोtr(" not");
	माला_दोtr(" built for BTI\n");

	sa.sa_handler = (sighandler_t)(व्योम *)handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(संक_अवैध, &sa, शून्य);
	sigaddset(&sa.sa_mask, संक_अवैध);
	sigprocmask(SIG_UNBLOCK, &sa.sa_mask, शून्य);

	करो_test(1, 1, 1, nohपूर्णांक_func);
	करो_test(1, 1, 1, bti_none_func);
	करो_test(1, 0, 0, bti_c_func);
	करो_test(0, 0, 1, bti_j_func);
	करो_test(0, 0, 0, bti_jc_func);
	करो_test(1, 0, 0, paciasp_func);

	prपूर्णांक_summary();

	अगर (test_num - 1 != EXPECTED_TESTS)
		माला_दोtr("# WARNING - EXPECTED TEST COUNT WRONG\n");

	अगर (test_failed)
		निकास(1);
	अन्यथा
		निकास(0);
पूर्ण
