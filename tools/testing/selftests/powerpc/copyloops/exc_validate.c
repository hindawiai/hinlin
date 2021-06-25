<शैली गुरु>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <मानकपन.स>
#समावेश <संकेत.स>
#समावेश <unistd.h>
#समावेश <sys/mman.h>

#समावेश "utils.h"

बाह्य अक्षर __start___ex_table[];
बाह्य अक्षर __stop___ex_table[];

#अगर defined(__घातerpc64__)
#घोषणा UCONTEXT_NIA(UC)	(UC)->uc_mcontext.gp_regs[PT_NIP]
#या_अगर defined(__घातerpc__)
#घोषणा UCONTEXT_NIA(UC)	(UC)->uc_mcontext.uc_regs->gregs[PT_NIP]
#अन्यथा
#त्रुटि implement UCONTEXT_NIA
#पूर्ण_अगर

अटल व्योम segv_handler(पूर्णांक signr, siginfo_t *info, व्योम *ptr)
अणु
	ucontext_t *uc = (ucontext_t *)ptr;
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)info->si_addr;
	अचिन्हित दीर्घ *ip = &UCONTEXT_NIA(uc);
	अचिन्हित दीर्घ *ex_p = (अचिन्हित दीर्घ *)__start___ex_table;

	जबतक (ex_p < (अचिन्हित दीर्घ *)__stop___ex_table) अणु
		अचिन्हित दीर्घ insn, fixup;

		insn = *ex_p++;
		fixup = *ex_p++;

		अगर (insn == *ip) अणु
			*ip = fixup;
			वापस;
		पूर्ण
	पूर्ण

	म_लिखो("No exception table match for NIA %lx ADDR %lx\n", *ip, addr);
	पात();
पूर्ण

अटल व्योम setup_segv_handler(व्योम)
अणु
	काष्ठा sigaction action;

	स_रखो(&action, 0, माप(action));
	action.sa_sigaction = segv_handler;
	action.sa_flags = SA_SIGINFO;
	sigaction(संक_अंश, &action, शून्य);
पूर्ण

अचिन्हित दीर्घ COPY_LOOP(व्योम *to, स्थिर व्योम *from, अचिन्हित दीर्घ size);
अचिन्हित दीर्घ test_copy_tofrom_user_reference(व्योम *to, स्थिर व्योम *from, अचिन्हित दीर्घ size);

अटल पूर्णांक total_passed;
अटल पूर्णांक total_failed;

अटल व्योम करो_one_test(अक्षर *dstp, अक्षर *srcp, अचिन्हित दीर्घ len)
अणु
	अचिन्हित दीर्घ got, expected;

	got = COPY_LOOP(dstp, srcp, len);
	expected = test_copy_tofrom_user_reference(dstp, srcp, len);

	अगर (got != expected) अणु
		total_failed++;
		म_लिखो("FAIL from=%p to=%p len=%ld returned %ld, expected %ld\n",
		       srcp, dstp, len, got, expected);
		//पात();
	पूर्ण अन्यथा
		total_passed++;
पूर्ण

//#घोषणा MAX_LEN 512
#घोषणा MAX_LEN 16

पूर्णांक test_copy_exception(व्योम)
अणु
	पूर्णांक page_size;
	अटल अक्षर *p, *q;
	अचिन्हित दीर्घ src, dst, len;

	page_size = getpagesize();
	p = mmap(शून्य, page_size * 2, PROT_READ|PROT_WRITE,
		MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);

	अगर (p == MAP_FAILED) अणु
		लिखो_त्रुटि("mmap");
		निकास(1);
	पूर्ण

	स_रखो(p, 0, page_size);

	setup_segv_handler();

	अगर (mprotect(p + page_size, page_size, PROT_NONE)) अणु
		लिखो_त्रुटि("mprotect");
		निकास(1);
	पूर्ण

	q = p + page_size - MAX_LEN;

	क्रम (src = 0; src < MAX_LEN; src++) अणु
		क्रम (dst = 0; dst < MAX_LEN; dst++) अणु
			क्रम (len = 0; len < MAX_LEN+1; len++) अणु
				// म_लिखो("from=%p to=%p len=%ld\n", q+dst, q+src, len);
				करो_one_test(q+dst, q+src, len);
			पूर्ण
		पूर्ण
	पूर्ण

	म_लिखो("Totals:\n");
	म_लिखो("  Pass: %d\n", total_passed);
	म_लिखो("  Fail: %d\n", total_failed);

	वापस 0;
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	वापस test_harness(test_copy_exception, str(COPY_LOOP));
पूर्ण
