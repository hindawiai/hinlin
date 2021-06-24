<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Stas Sergeev <stsp@users.sourceक्रमge.net>
 *
 * test sigaltstack(SS_ONSTACK | SS_AUTODISARM)
 * If that succeeds, then swapcontext() can be used inside sighandler safely.
 *
 */

#घोषणा _GNU_SOURCE
#समावेश <संकेत.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <sys/mman.h>
#समावेश <ucontext.h>
#समावेश <alloca.h>
#समावेश <माला.स>
#समावेश <निश्चित.स>
#समावेश <त्रुटिसं.स>

#समावेश "../kselftest.h"

#अगर_अघोषित SS_AUTODISARM
#घोषणा SS_AUTODISARM  (1U << 31)
#पूर्ण_अगर

अटल व्योम *sstack, *ustack;
अटल ucontext_t uc, sc;
अटल स्थिर अक्षर *msg = "[OK]\tStack preserved";
अटल स्थिर अक्षर *msg2 = "[FAIL]\tStack corrupted";
काष्ठा stk_data अणु
	अक्षर msg[128];
	पूर्णांक flag;
पूर्ण;

व्योम my_usr1(पूर्णांक sig, siginfo_t *si, व्योम *u)
अणु
	अक्षर *aa;
	पूर्णांक err;
	stack_t stk;
	काष्ठा stk_data *p;

#अगर __s390x__
	रेजिस्टर अचिन्हित दीर्घ sp यंत्र("%15");
#अन्यथा
	रेजिस्टर अचिन्हित दीर्घ sp यंत्र("sp");
#पूर्ण_अगर

	अगर (sp < (अचिन्हित दीर्घ)sstack ||
			sp >= (अचिन्हित दीर्घ)sstack + SIGSTKSZ) अणु
		ksft_निकास_fail_msg("SP is not on sigaltstack\n");
	पूर्ण
	/* put some data on stack. other sighandler will try to overग_लिखो it */
	aa = alloca(1024);
	निश्चित(aa);
	p = (काष्ठा stk_data *)(aa + 512);
	म_नकल(p->msg, msg);
	p->flag = 1;
	ksft_prपूर्णांक_msg("[RUN]\tsignal USR1\n");
	err = sigaltstack(शून्य, &stk);
	अगर (err) अणु
		ksft_निकास_fail_msg("sigaltstack() - %s\n", म_त्रुटि(त्रुटि_सं));
		निकास(निकास_त्रुटि);
	पूर्ण
	अगर (stk.ss_flags != SS_DISABLE)
		ksft_test_result_fail("tss_flags=%x, should be SS_DISABLE\n",
				stk.ss_flags);
	अन्यथा
		ksft_test_result_pass(
				"sigaltstack is disabled in sighandler\n");
	swapcontext(&sc, &uc);
	ksft_prपूर्णांक_msg("%s\n", p->msg);
	अगर (!p->flag) अणु
		ksft_निकास_fail_msg("[RUN]\tAborting\n");
		निकास(निकास_त्रुटि);
	पूर्ण
पूर्ण

व्योम my_usr2(पूर्णांक sig, siginfo_t *si, व्योम *u)
अणु
	अक्षर *aa;
	काष्ठा stk_data *p;

	ksft_prपूर्णांक_msg("[RUN]\tsignal USR2\n");
	aa = alloca(1024);
	/* करोnt run valgrind on this */
	/* try to find the data stored by previous sighandler */
	p = memmem(aa, 1024, msg, म_माप(msg));
	अगर (p) अणु
		ksft_test_result_fail("sigaltstack re-used\n");
		/* corrupt the data */
		म_नकल(p->msg, msg2);
		/* tell other sighandler that his data is corrupted */
		p->flag = 0;
	पूर्ण
पूर्ण

अटल व्योम चयन_fn(व्योम)
अणु
	ksft_prपूर्णांक_msg("[RUN]\tswitched to user ctx\n");
	उठाओ(SIGUSR2);
	setcontext(&sc);
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	काष्ठा sigaction act;
	stack_t stk;
	पूर्णांक err;

	ksft_prपूर्णांक_header();
	ksft_set_plan(3);

	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_ONSTACK | SA_SIGINFO;
	act.sa_sigaction = my_usr1;
	sigaction(SIGUSR1, &act, शून्य);
	act.sa_sigaction = my_usr2;
	sigaction(SIGUSR2, &act, शून्य);
	sstack = mmap(शून्य, SIGSTKSZ, PROT_READ | PROT_WRITE,
		      MAP_PRIVATE | MAP_ANONYMOUS | MAP_STACK, -1, 0);
	अगर (sstack == MAP_FAILED) अणु
		ksft_निकास_fail_msg("mmap() - %s\n", म_त्रुटि(त्रुटि_सं));
		वापस निकास_त्रुटि;
	पूर्ण

	err = sigaltstack(शून्य, &stk);
	अगर (err) अणु
		ksft_निकास_fail_msg("sigaltstack() - %s\n", म_त्रुटि(त्रुटि_सं));
		निकास(निकास_त्रुटि);
	पूर्ण
	अगर (stk.ss_flags == SS_DISABLE) अणु
		ksft_test_result_pass(
				"Initial sigaltstack state was SS_DISABLE\n");
	पूर्ण अन्यथा अणु
		ksft_निकास_fail_msg("Initial sigaltstack state was %x; "
		       "should have been SS_DISABLE\n", stk.ss_flags);
		वापस निकास_त्रुटि;
	पूर्ण

	stk.ss_sp = sstack;
	stk.ss_size = SIGSTKSZ;
	stk.ss_flags = SS_ONSTACK | SS_AUTODISARM;
	err = sigaltstack(&stk, शून्य);
	अगर (err) अणु
		अगर (त्रुटि_सं == EINVAL) अणु
			ksft_test_result_skip(
				"[NOTE]\tThe running kernel doesn't support SS_AUTODISARM\n");
			/*
			 * If test हालs क्रम the !SS_AUTODISARM variant were
			 * added, we could still run them.  We करोn't have any
			 * test हालs like that yet, so just निकास and report
			 * success.
			 */
			वापस 0;
		पूर्ण अन्यथा अणु
			ksft_निकास_fail_msg(
				"sigaltstack(SS_ONSTACK | SS_AUTODISARM)  %s\n",
					म_त्रुटि(त्रुटि_सं));
			वापस निकास_त्रुटि;
		पूर्ण
	पूर्ण

	ustack = mmap(शून्य, SIGSTKSZ, PROT_READ | PROT_WRITE,
		      MAP_PRIVATE | MAP_ANONYMOUS | MAP_STACK, -1, 0);
	अगर (ustack == MAP_FAILED) अणु
		ksft_निकास_fail_msg("mmap() - %s\n", म_त्रुटि(त्रुटि_सं));
		वापस निकास_त्रुटि;
	पूर्ण
	अ_लोontext(&uc);
	uc.uc_link = शून्य;
	uc.uc_stack.ss_sp = ustack;
	uc.uc_stack.ss_size = SIGSTKSZ;
	makecontext(&uc, चयन_fn, 0);
	उठाओ(SIGUSR1);

	err = sigaltstack(शून्य, &stk);
	अगर (err) अणु
		ksft_निकास_fail_msg("sigaltstack() - %s\n", म_त्रुटि(त्रुटि_सं));
		निकास(निकास_त्रुटि);
	पूर्ण
	अगर (stk.ss_flags != SS_AUTODISARM) अणु
		ksft_निकास_fail_msg("ss_flags=%x, should be SS_AUTODISARM\n",
				stk.ss_flags);
		निकास(निकास_त्रुटि);
	पूर्ण
	ksft_test_result_pass(
			"sigaltstack is still SS_AUTODISARM after signal\n");

	ksft_निकास_pass();
	वापस 0;
पूर्ण
