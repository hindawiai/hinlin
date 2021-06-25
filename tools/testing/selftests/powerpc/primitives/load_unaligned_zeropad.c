<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Userspace test harness क्रम load_unaligned_zeropad. Creates two
 * pages and uses mprotect to prevent access to the second page and
 * a SEGV handler that walks the exception tables and runs the fixup
 * routine.
 *
 * The results are compared against a normal load that is that is
 * perक्रमmed जबतक access to the second page is enabled via mprotect.
 *
 * Copyright (C) 2014 Anton Blanअक्षरd <anton@au.ibm.com>, IBM
 */

#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <मानकपन.स>
#समावेश <stdbool.h>
#समावेश <संकेत.स>
#समावेश <unistd.h>
#समावेश <sys/mman.h>

#घोषणा FIXUP_SECTION ".ex_fixup"

अटल अंतरभूत अचिन्हित दीर्घ __fls(अचिन्हित दीर्घ x);

#समावेश "word-at-a-time.h"

#समावेश "utils.h"

अटल अंतरभूत अचिन्हित दीर्घ __fls(अचिन्हित दीर्घ x)
अणु
	पूर्णांक lz;

	यंत्र (PPC_CNTLZL "%0,%1" : "=r" (lz) : "r" (x));
	वापस माप(अचिन्हित दीर्घ) - 1 - lz;
पूर्ण

अटल पूर्णांक page_size;
अटल अक्षर *mem_region;

अटल पूर्णांक protect_region(व्योम)
अणु
	अगर (mprotect(mem_region + page_size, page_size, PROT_NONE)) अणु
		लिखो_त्रुटि("mprotect");
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक unprotect_region(व्योम)
अणु
	अगर (mprotect(mem_region + page_size, page_size, PROT_READ|PROT_WRITE)) अणु
		लिखो_त्रुटि("mprotect");
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

बाह्य अक्षर __start___ex_table[];
बाह्य अक्षर __stop___ex_table[];

काष्ठा extbl_entry अणु
	पूर्णांक insn;
	पूर्णांक fixup;
पूर्ण;

अटल व्योम segv_handler(पूर्णांक signr, siginfo_t *info, व्योम *ptr)
अणु
	ucontext_t *uc = (ucontext_t *)ptr;
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)info->si_addr;
	अचिन्हित दीर्घ *ip = &UCONTEXT_NIA(uc);
	काष्ठा extbl_entry *entry = (काष्ठा extbl_entry *)__start___ex_table;

	जबतक (entry < (काष्ठा extbl_entry *)__stop___ex_table) अणु
		अचिन्हित दीर्घ insn, fixup;

		insn  = (अचिन्हित दीर्घ)&entry->insn + entry->insn;
		fixup = (अचिन्हित दीर्घ)&entry->fixup + entry->fixup;

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

अटल पूर्णांक करो_one_test(अक्षर *p, पूर्णांक page_offset)
अणु
	अचिन्हित दीर्घ should;
	अचिन्हित दीर्घ got;

	FAIL_IF(unprotect_region());
	should = *(अचिन्हित दीर्घ *)p;
	FAIL_IF(protect_region());

	got = load_unaligned_zeropad(p);

	अगर (should != got) अणु
		म_लिखो("offset %u load_unaligned_zeropad returned 0x%lx, should be 0x%lx\n", page_offset, got, should);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक test_body(व्योम)
अणु
	अचिन्हित दीर्घ i;

	page_size = getpagesize();
	mem_region = mmap(शून्य, page_size * 2, PROT_READ|PROT_WRITE,
		MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);

	FAIL_IF(mem_region == MAP_FAILED);

	क्रम (i = 0; i < page_size; i++)
		mem_region[i] = i;

	स_रखो(mem_region+page_size, 0, page_size);

	setup_segv_handler();

	क्रम (i = 0; i < page_size; i++)
		FAIL_IF(करो_one_test(mem_region+i, i));

	वापस 0;
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	वापस test_harness(test_body, "load_unaligned_zeropad");
पूर्ण
