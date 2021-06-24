<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ldt_gdt.c - Test हालs क्रम LDT and GDT access
 * Copyright (c) 2015 Andrew Lutomirski
 */

#घोषणा _GNU_SOURCE
#समावेश <err.h>
#समावेश <मानकपन.स>
#समावेश <मानक_निवेशt.h>
#समावेश <संकेत.स>
#समावेश <समलाँघ.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <त्रुटिसं.स>
#समावेश <unistd.h>
#समावेश <sys/syscall.h>
#समावेश <यंत्र/ldt.h>
#समावेश <sys/types.h>
#समावेश <sys/रुको.h>
#समावेश <stdbool.h>
#समावेश <pthपढ़ो.h>
#समावेश <sched.h>
#समावेश <linux/futex.h>
#समावेश <sys/mman.h>
#समावेश <यंत्र/prctl.h>
#समावेश <sys/prctl.h>

#घोषणा AR_ACCESSED		(1<<8)

#घोषणा AR_TYPE_RODATA		(0 * (1<<9))
#घोषणा AR_TYPE_RWDATA		(1 * (1<<9))
#घोषणा AR_TYPE_RODATA_EXPDOWN	(2 * (1<<9))
#घोषणा AR_TYPE_RWDATA_EXPDOWN	(3 * (1<<9))
#घोषणा AR_TYPE_XOCODE		(4 * (1<<9))
#घोषणा AR_TYPE_XRCODE		(5 * (1<<9))
#घोषणा AR_TYPE_XOCODE_CONF	(6 * (1<<9))
#घोषणा AR_TYPE_XRCODE_CONF	(7 * (1<<9))

#घोषणा AR_DPL3			(3 * (1<<13))

#घोषणा AR_S			(1 << 12)
#घोषणा AR_P			(1 << 15)
#घोषणा AR_AVL			(1 << 20)
#घोषणा AR_L			(1 << 21)
#घोषणा AR_DB			(1 << 22)
#घोषणा AR_G			(1 << 23)

#अगर_घोषित __x86_64__
# define INT80_CLOBBERS "r8", "r9", "r10", "r11"
#अन्यथा
# define INT80_CLOBBERS
#पूर्ण_अगर

अटल पूर्णांक nerrs;

/* Poपूर्णांकs to an array of 1024 पूर्णांकs, each holding its own index. */
अटल स्थिर अचिन्हित पूर्णांक *counter_page;
अटल काष्ठा user_desc *low_user_desc;
अटल काष्ठा user_desc *low_user_desc_clear;  /* Use to delete GDT entry */
अटल पूर्णांक gdt_entry_num;

अटल व्योम check_invalid_segment(uपूर्णांक16_t index, पूर्णांक ldt)
अणु
	uपूर्णांक32_t has_limit = 0, has_ar = 0, limit, ar;
	uपूर्णांक32_t selector = (index << 3) | (ldt << 2) | 3;

	यंत्र ("lsl %[selector], %[limit]\n\t"
	     "jnz 1f\n\t"
	     "movl $1, %[has_limit]\n\t"
	     "1:"
	     : [limit] "=r" (limit), [has_limit] "+rm" (has_limit)
	     : [selector] "r" (selector));
	यंत्र ("larl %[selector], %[ar]\n\t"
	     "jnz 1f\n\t"
	     "movl $1, %[has_ar]\n\t"
	     "1:"
	     : [ar] "=r" (ar), [has_ar] "+rm" (has_ar)
	     : [selector] "r" (selector));

	अगर (has_limit || has_ar) अणु
		म_लिखो("[FAIL]\t%s entry %hu is valid but should be invalid\n",
		       (ldt ? "LDT" : "GDT"), index);
		nerrs++;
	पूर्ण अन्यथा अणु
		म_लिखो("[OK]\t%s entry %hu is invalid\n",
		       (ldt ? "LDT" : "GDT"), index);
	पूर्ण
पूर्ण

अटल व्योम check_valid_segment(uपूर्णांक16_t index, पूर्णांक ldt,
				uपूर्णांक32_t expected_ar, uपूर्णांक32_t expected_limit,
				bool verbose)
अणु
	uपूर्णांक32_t has_limit = 0, has_ar = 0, limit, ar;
	uपूर्णांक32_t selector = (index << 3) | (ldt << 2) | 3;

	यंत्र ("lsl %[selector], %[limit]\n\t"
	     "jnz 1f\n\t"
	     "movl $1, %[has_limit]\n\t"
	     "1:"
	     : [limit] "=r" (limit), [has_limit] "+rm" (has_limit)
	     : [selector] "r" (selector));
	यंत्र ("larl %[selector], %[ar]\n\t"
	     "jnz 1f\n\t"
	     "movl $1, %[has_ar]\n\t"
	     "1:"
	     : [ar] "=r" (ar), [has_ar] "+rm" (has_ar)
	     : [selector] "r" (selector));

	अगर (!has_limit || !has_ar) अणु
		म_लिखो("[FAIL]\t%s entry %hu is invalid but should be valid\n",
		       (ldt ? "LDT" : "GDT"), index);
		nerrs++;
		वापस;
	पूर्ण

	/* The SDM says "bits 19:16 are undefined".  Thanks. */
	ar &= ~0xF0000;

	/*
	 * NB: Dअगरferent Linux versions करो dअगरferent things with the
	 * accessed bit in set_thपढ़ो_area().
	 */
	अगर (ar != expected_ar && ar != (expected_ar | AR_ACCESSED)) अणु
		म_लिखो("[FAIL]\t%s entry %hu has AR 0x%08X but expected 0x%08X\n",
		       (ldt ? "LDT" : "GDT"), index, ar, expected_ar);
		nerrs++;
	पूर्ण अन्यथा अगर (limit != expected_limit) अणु
		म_लिखो("[FAIL]\t%s entry %hu has limit 0x%08X but expected 0x%08X\n",
		       (ldt ? "LDT" : "GDT"), index, limit, expected_limit);
		nerrs++;
	पूर्ण अन्यथा अगर (verbose) अणु
		म_लिखो("[OK]\t%s entry %hu has AR 0x%08X and limit 0x%08X\n",
		       (ldt ? "LDT" : "GDT"), index, ar, limit);
	पूर्ण
पूर्ण

अटल bool install_valid_mode(स्थिर काष्ठा user_desc *d, uपूर्णांक32_t ar,
			       bool oldmode, bool ldt)
अणु
	काष्ठा user_desc desc = *d;
	पूर्णांक ret;

	अगर (!ldt) अणु
#अगर_अघोषित __i386__
		/* No poपूर्णांक testing set_thपढ़ो_area in a 64-bit build */
		वापस false;
#पूर्ण_अगर
		अगर (!gdt_entry_num)
			वापस false;
		desc.entry_number = gdt_entry_num;

		ret = syscall(SYS_set_thपढ़ो_area, &desc);
	पूर्ण अन्यथा अणु
		ret = syscall(SYS_modअगरy_ldt, oldmode ? 1 : 0x11,
			      &desc, माप(desc));

		अगर (ret < -1)
			त्रुटि_सं = -ret;

		अगर (ret != 0 && त्रुटि_सं == ENOSYS) अणु
			म_लिखो("[OK]\tmodify_ldt returned -ENOSYS\n");
			वापस false;
		पूर्ण
	पूर्ण

	अगर (ret == 0) अणु
		uपूर्णांक32_t limit = desc.limit;
		अगर (desc.limit_in_pages)
			limit = (limit << 12) + 4095;
		check_valid_segment(desc.entry_number, ldt, ar, limit, true);
		वापस true;
	पूर्ण अन्यथा अणु
		अगर (desc.seg_32bit) अणु
			म_लिखो("[FAIL]\tUnexpected %s failure %d\n",
			       ldt ? "modify_ldt" : "set_thread_area",
			       त्रुटि_सं);
			nerrs++;
			वापस false;
		पूर्ण अन्यथा अणु
			म_लिखो("[OK]\t%s rejected 16 bit segment\n",
			       ldt ? "modify_ldt" : "set_thread_area");
			वापस false;
		पूर्ण
	पूर्ण
पूर्ण

अटल bool install_valid(स्थिर काष्ठा user_desc *desc, uपूर्णांक32_t ar)
अणु
	bool ret = install_valid_mode(desc, ar, false, true);

	अगर (desc->contents <= 1 && desc->seg_32bit &&
	    !desc->seg_not_present) अणु
		/* Should work in the GDT, too. */
		install_valid_mode(desc, ar, false, false);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम install_invalid(स्थिर काष्ठा user_desc *desc, bool oldmode)
अणु
	पूर्णांक ret = syscall(SYS_modअगरy_ldt, oldmode ? 1 : 0x11,
			  desc, माप(*desc));
	अगर (ret < -1)
		त्रुटि_सं = -ret;
	अगर (ret == 0) अणु
		check_invalid_segment(desc->entry_number, 1);
	पूर्ण अन्यथा अगर (त्रुटि_सं == ENOSYS) अणु
		म_लिखो("[OK]\tmodify_ldt returned -ENOSYS\n");
	पूर्ण अन्यथा अणु
		अगर (desc->seg_32bit) अणु
			म_लिखो("[FAIL]\tUnexpected modify_ldt failure %d\n",
			       त्रुटि_सं);
			nerrs++;
		पूर्ण अन्यथा अणु
			म_लिखो("[OK]\tmodify_ldt rejected 16 bit segment\n");
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक safe_modअगरy_ldt(पूर्णांक func, काष्ठा user_desc *ptr,
			   अचिन्हित दीर्घ bytecount)
अणु
	पूर्णांक ret = syscall(SYS_modअगरy_ldt, 0x11, ptr, bytecount);
	अगर (ret < -1)
		त्रुटि_सं = -ret;
	वापस ret;
पूर्ण

अटल व्योम fail_install(काष्ठा user_desc *desc)
अणु
	अगर (safe_modअगरy_ldt(0x11, desc, माप(*desc)) == 0) अणु
		म_लिखो("[FAIL]\tmodify_ldt accepted a bad descriptor\n");
		nerrs++;
	पूर्ण अन्यथा अगर (त्रुटि_सं == ENOSYS) अणु
		म_लिखो("[OK]\tmodify_ldt returned -ENOSYS\n");
	पूर्ण अन्यथा अणु
		म_लिखो("[OK]\tmodify_ldt failure %d\n", त्रुटि_सं);
	पूर्ण
पूर्ण

अटल व्योम करो_simple_tests(व्योम)
अणु
	काष्ठा user_desc desc = अणु
		.entry_number    = 0,
		.base_addr       = 0,
		.limit           = 10,
		.seg_32bit       = 1,
		.contents        = 2, /* Code, not conक्रमming */
		.पढ़ो_exec_only  = 0,
		.limit_in_pages  = 0,
		.seg_not_present = 0,
		.useable         = 0
	पूर्ण;
	install_valid(&desc, AR_DPL3 | AR_TYPE_XRCODE | AR_S | AR_P | AR_DB);

	desc.limit_in_pages = 1;
	install_valid(&desc, AR_DPL3 | AR_TYPE_XRCODE |
		      AR_S | AR_P | AR_DB | AR_G);

	check_invalid_segment(1, 1);

	desc.entry_number = 2;
	install_valid(&desc, AR_DPL3 | AR_TYPE_XRCODE |
		      AR_S | AR_P | AR_DB | AR_G);

	check_invalid_segment(1, 1);

	desc.base_addr = 0xf0000000;
	install_valid(&desc, AR_DPL3 | AR_TYPE_XRCODE |
		      AR_S | AR_P | AR_DB | AR_G);

	desc.useable = 1;
	install_valid(&desc, AR_DPL3 | AR_TYPE_XRCODE |
		      AR_S | AR_P | AR_DB | AR_G | AR_AVL);

	desc.seg_not_present = 1;
	install_valid(&desc, AR_DPL3 | AR_TYPE_XRCODE |
		      AR_S | AR_DB | AR_G | AR_AVL);

	desc.seg_32bit = 0;
	install_valid(&desc, AR_DPL3 | AR_TYPE_XRCODE |
		      AR_S | AR_G | AR_AVL);

	desc.seg_32bit = 1;
	desc.contents = 0;
	install_valid(&desc, AR_DPL3 | AR_TYPE_RWDATA |
		      AR_S | AR_DB | AR_G | AR_AVL);

	desc.पढ़ो_exec_only = 1;
	install_valid(&desc, AR_DPL3 | AR_TYPE_RODATA |
		      AR_S | AR_DB | AR_G | AR_AVL);

	desc.contents = 1;
	install_valid(&desc, AR_DPL3 | AR_TYPE_RODATA_EXPDOWN |
		      AR_S | AR_DB | AR_G | AR_AVL);

	desc.पढ़ो_exec_only = 0;
	desc.limit_in_pages = 0;
	install_valid(&desc, AR_DPL3 | AR_TYPE_RWDATA_EXPDOWN |
		      AR_S | AR_DB | AR_AVL);

	desc.contents = 3;
	install_valid(&desc, AR_DPL3 | AR_TYPE_XRCODE_CONF |
		      AR_S | AR_DB | AR_AVL);

	desc.पढ़ो_exec_only = 1;
	install_valid(&desc, AR_DPL3 | AR_TYPE_XOCODE_CONF |
		      AR_S | AR_DB | AR_AVL);

	desc.पढ़ो_exec_only = 0;
	desc.contents = 2;
	install_valid(&desc, AR_DPL3 | AR_TYPE_XRCODE |
		      AR_S | AR_DB | AR_AVL);

	desc.पढ़ो_exec_only = 1;

#अगर_घोषित __x86_64__
	desc.lm = 1;
	install_valid(&desc, AR_DPL3 | AR_TYPE_XOCODE |
		      AR_S | AR_DB | AR_AVL);
	desc.lm = 0;
#पूर्ण_अगर

	bool entry1_okay = install_valid(&desc, AR_DPL3 | AR_TYPE_XOCODE |
					 AR_S | AR_DB | AR_AVL);

	अगर (entry1_okay) अणु
		म_लिखो("[RUN]\tTest fork\n");
		pid_t child = विभाजन();
		अगर (child == 0) अणु
			nerrs = 0;
			check_valid_segment(desc.entry_number, 1,
					    AR_DPL3 | AR_TYPE_XOCODE |
					    AR_S | AR_DB | AR_AVL, desc.limit,
					    true);
			check_invalid_segment(1, 1);
			निकास(nerrs ? 1 : 0);
		पूर्ण अन्यथा अणु
			पूर्णांक status;
			अगर (रुकोpid(child, &status, 0) != child ||
			    !WIFEXITED(status)) अणु
				म_लिखो("[FAIL]\tChild died\n");
				nerrs++;
			पूर्ण अन्यथा अगर (WEXITSTATUS(status) != 0) अणु
				म_लिखो("[FAIL]\tChild failed\n");
				nerrs++;
			पूर्ण अन्यथा अणु
				म_लिखो("[OK]\tChild succeeded\n");
			पूर्ण
		पूर्ण

		म_लिखो("[RUN]\tTest size\n");
		पूर्णांक i;
		क्रम (i = 0; i < 8192; i++) अणु
			desc.entry_number = i;
			desc.limit = i;
			अगर (safe_modअगरy_ldt(0x11, &desc, माप(desc)) != 0) अणु
				म_लिखो("[FAIL]\tFailed to install entry %d\n", i);
				nerrs++;
				अवरोध;
			पूर्ण
		पूर्ण
		क्रम (पूर्णांक j = 0; j < i; j++) अणु
			check_valid_segment(j, 1, AR_DPL3 | AR_TYPE_XOCODE |
					    AR_S | AR_DB | AR_AVL, j, false);
		पूर्ण
		म_लिखो("[DONE]\tSize test\n");
	पूर्ण अन्यथा अणु
		म_लिखो("[SKIP]\tSkipping fork and size tests because we have no LDT\n");
	पूर्ण

	/* Test entry_number too high. */
	desc.entry_number = 8192;
	fail_install(&desc);

	/* Test deletion and actions mistakeable क्रम deletion. */
	स_रखो(&desc, 0, माप(desc));
	install_valid(&desc, AR_DPL3 | AR_TYPE_RWDATA | AR_S | AR_P);

	desc.seg_not_present = 1;
	install_valid(&desc, AR_DPL3 | AR_TYPE_RWDATA | AR_S);

	desc.seg_not_present = 0;
	desc.पढ़ो_exec_only = 1;
	install_valid(&desc, AR_DPL3 | AR_TYPE_RODATA | AR_S | AR_P);

	desc.पढ़ो_exec_only = 0;
	desc.seg_not_present = 1;
	install_valid(&desc, AR_DPL3 | AR_TYPE_RWDATA | AR_S);

	desc.पढ़ो_exec_only = 1;
	desc.limit = 1;
	install_valid(&desc, AR_DPL3 | AR_TYPE_RODATA | AR_S);

	desc.limit = 0;
	desc.base_addr = 1;
	install_valid(&desc, AR_DPL3 | AR_TYPE_RODATA | AR_S);

	desc.base_addr = 0;
	install_invalid(&desc, false);

	desc.seg_not_present = 0;
	desc.seg_32bit = 1;
	desc.पढ़ो_exec_only = 0;
	desc.limit = 0xfffff;

	install_valid(&desc, AR_DPL3 | AR_TYPE_RWDATA | AR_S | AR_P | AR_DB);

	desc.limit_in_pages = 1;

	install_valid(&desc, AR_DPL3 | AR_TYPE_RWDATA | AR_S | AR_P | AR_DB | AR_G);
	desc.पढ़ो_exec_only = 1;
	install_valid(&desc, AR_DPL3 | AR_TYPE_RODATA | AR_S | AR_P | AR_DB | AR_G);
	desc.contents = 1;
	desc.पढ़ो_exec_only = 0;
	install_valid(&desc, AR_DPL3 | AR_TYPE_RWDATA_EXPDOWN | AR_S | AR_P | AR_DB | AR_G);
	desc.पढ़ो_exec_only = 1;
	install_valid(&desc, AR_DPL3 | AR_TYPE_RODATA_EXPDOWN | AR_S | AR_P | AR_DB | AR_G);

	desc.limit = 0;
	install_invalid(&desc, true);
पूर्ण

/*
 * 0: thपढ़ो is idle
 * 1: thपढ़ो armed
 * 2: thपढ़ो should clear LDT entry 0
 * 3: thपढ़ो should निकास
 */
अटल अस्थिर अचिन्हित पूर्णांक ftx;

अटल व्योम *thपढ़ोproc(व्योम *ctx)
अणु
	cpu_set_t cpuset;
	CPU_ZERO(&cpuset);
	CPU_SET(1, &cpuset);
	अगर (sched_setaffinity(0, माप(cpuset), &cpuset) != 0)
		err(1, "sched_setaffinity to CPU 1");	/* should never fail */

	जबतक (1) अणु
		syscall(SYS_futex, &ftx, FUTEX_WAIT, 0, शून्य, शून्य, 0);
		जबतक (ftx != 2) अणु
			अगर (ftx >= 3)
				वापस शून्य;
		पूर्ण

		/* clear LDT entry 0 */
		स्थिर काष्ठा user_desc desc = अणुपूर्ण;
		अगर (syscall(SYS_modअगरy_ldt, 1, &desc, माप(desc)) != 0)
			err(1, "modify_ldt");

		/* If ftx == 2, set it to zero.  If ftx == 100, quit. */
		अचिन्हित पूर्णांक x = -2;
		यंत्र अस्थिर ("lock xaddl %[x], %[ftx]" :
			      [x] "+r" (x), [ftx] "+m" (ftx));
		अगर (x != 2)
			वापस शून्य;
	पूर्ण
पूर्ण

#अगर_घोषित __i386__

#अगर_अघोषित SA_RESTORE
#घोषणा SA_RESTORER 0x04000000
#पूर्ण_अगर

/*
 * The UAPI header calls this 'struct sigaction', which conflicts with
 * glibc.  Sigh.
 */
काष्ठा fake_ksigaction अणु
	व्योम *handler;  /* the real type is nasty */
	अचिन्हित दीर्घ sa_flags;
	व्योम (*sa_restorer)(व्योम);
	अचिन्हित अक्षर sigset[8];
पूर्ण;

अटल व्योम fix_sa_restorer(पूर्णांक sig)
अणु
	काष्ठा fake_ksigaction ksa;

	अगर (syscall(SYS_rt_sigaction, sig, शून्य, &ksa, 8) == 0) अणु
		/*
		 * glibc has a nasty bug: it someबार ग_लिखोs garbage to
		 * sa_restorer.  This पूर्णांकeracts quite badly with anything
		 * that fiddles with SS because it can trigger legacy
		 * stack चयनing.  Patch it up.  See:
		 *
		 * https://sourceware.org/bugzilla/show_bug.cgi?id=21269
		 */
		अगर (!(ksa.sa_flags & SA_RESTORER) && ksa.sa_restorer) अणु
			ksa.sa_restorer = शून्य;
			अगर (syscall(SYS_rt_sigaction, sig, &ksa, शून्य,
				    माप(ksa.sigset)) != 0)
				err(1, "rt_sigaction");
		पूर्ण
	पूर्ण
पूर्ण
#अन्यथा
अटल व्योम fix_sa_restorer(पूर्णांक sig)
अणु
	/* 64-bit glibc works fine. */
पूर्ण
#पूर्ण_अगर

अटल व्योम sethandler(पूर्णांक sig, व्योम (*handler)(पूर्णांक, siginfo_t *, व्योम *),
		       पूर्णांक flags)
अणु
	काष्ठा sigaction sa;
	स_रखो(&sa, 0, माप(sa));
	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO | flags;
	sigemptyset(&sa.sa_mask);
	अगर (sigaction(sig, &sa, 0))
		err(1, "sigaction");

	fix_sa_restorer(sig);
पूर्ण

अटल लाँघ_बफ jmpbuf;

अटल व्योम sigsegv(पूर्णांक sig, siginfo_t *info, व्योम *ctx_व्योम)
अणु
	sigदीर्घ_लाँघ(jmpbuf, 1);
पूर्ण

अटल व्योम करो_multicpu_tests(व्योम)
अणु
	cpu_set_t cpuset;
	pthपढ़ो_t thपढ़ो;
	पूर्णांक failures = 0, iters = 5, i;
	अचिन्हित लघु orig_ss;

	CPU_ZERO(&cpuset);
	CPU_SET(1, &cpuset);
	अगर (sched_setaffinity(0, माप(cpuset), &cpuset) != 0) अणु
		म_लिखो("[SKIP]\tCannot set affinity to CPU 1\n");
		वापस;
	पूर्ण

	CPU_ZERO(&cpuset);
	CPU_SET(0, &cpuset);
	अगर (sched_setaffinity(0, माप(cpuset), &cpuset) != 0) अणु
		म_लिखो("[SKIP]\tCannot set affinity to CPU 0\n");
		वापस;
	पूर्ण

	sethandler(संक_अंश, sigsegv, 0);
#अगर_घोषित __i386__
	/* True 32-bit kernels send संक_अवैध instead of संक_अंश on IRET faults. */
	sethandler(संक_अवैध, sigsegv, 0);
#पूर्ण_अगर

	म_लिखो("[RUN]\tCross-CPU LDT invalidation\n");

	अगर (pthपढ़ो_create(&thपढ़ो, 0, thपढ़ोproc, 0) != 0)
		err(1, "pthread_create");

	यंत्र अस्थिर ("mov %%ss, %0" : "=rm" (orig_ss));

	क्रम (i = 0; i < 5; i++) अणु
		अगर (sigबनाओ_लाँघ(jmpbuf, 1) != 0)
			जारी;

		/* Make sure the thपढ़ो is पढ़ोy after the last test. */
		जबतक (ftx != 0)
			;

		काष्ठा user_desc desc = अणु
			.entry_number    = 0,
			.base_addr       = 0,
			.limit           = 0xfffff,
			.seg_32bit       = 1,
			.contents        = 0, /* Data */
			.पढ़ो_exec_only  = 0,
			.limit_in_pages  = 1,
			.seg_not_present = 0,
			.useable         = 0
		पूर्ण;

		अगर (safe_modअगरy_ldt(0x11, &desc, माप(desc)) != 0) अणु
			अगर (त्रुटि_सं != ENOSYS)
				err(1, "modify_ldt");
			म_लिखो("[SKIP]\tmodify_ldt unavailable\n");
			अवरोध;
		पूर्ण

		/* Arm the thपढ़ो. */
		ftx = 1;
		syscall(SYS_futex, &ftx, FUTEX_WAKE, 0, शून्य, शून्य, 0);

		यंत्र अस्थिर ("mov %0, %%ss" : : "r" (0x7));

		/* Go! */
		ftx = 2;

		जबतक (ftx != 0)
			;

		/*
		 * On success, modअगरy_ldt will segfault us synchronously,
		 * and we'll escape via sigदीर्घ_लाँघ.
		 */

		failures++;
		यंत्र अस्थिर ("mov %0, %%ss" : : "rm" (orig_ss));
	पूर्ण

	ftx = 100;  /* Kill the thपढ़ो. */
	syscall(SYS_futex, &ftx, FUTEX_WAKE, 0, शून्य, शून्य, 0);

	अगर (pthपढ़ो_join(thपढ़ो, शून्य) != 0)
		err(1, "pthread_join");

	अगर (failures) अणु
		म_लिखो("[FAIL]\t%d of %d iterations failed\n", failures, iters);
		nerrs++;
	पूर्ण अन्यथा अणु
		म_लिखो("[OK]\tAll %d iterations succeeded\n", iters);
	पूर्ण
पूर्ण

अटल पूर्णांक finish_exec_test(व्योम)
अणु
	/*
	 * Older kernel versions did inherit the LDT on exec() which is
	 * wrong because exec() starts from a clean state.
	 */
	check_invalid_segment(0, 1);

	वापस nerrs ? 1 : 0;
पूर्ण

अटल व्योम करो_exec_test(व्योम)
अणु
	म_लिखो("[RUN]\tTest exec\n");

	काष्ठा user_desc desc = अणु
		.entry_number    = 0,
		.base_addr       = 0,
		.limit           = 42,
		.seg_32bit       = 1,
		.contents        = 2, /* Code, not conक्रमming */
		.पढ़ो_exec_only  = 0,
		.limit_in_pages  = 0,
		.seg_not_present = 0,
		.useable         = 0
	पूर्ण;
	install_valid(&desc, AR_DPL3 | AR_TYPE_XRCODE | AR_S | AR_P | AR_DB);

	pid_t child = विभाजन();
	अगर (child == 0) अणु
		execl("/proc/self/exe", "ldt_gdt_test_exec", शून्य);
		म_लिखो("[FAIL]\tCould not exec self\n");
		निकास(1);	/* exec failed */
	पूर्ण अन्यथा अणु
		पूर्णांक status;
		अगर (रुकोpid(child, &status, 0) != child ||
		    !WIFEXITED(status)) अणु
			म_लिखो("[FAIL]\tChild died\n");
			nerrs++;
		पूर्ण अन्यथा अगर (WEXITSTATUS(status) != 0) अणु
			म_लिखो("[FAIL]\tChild failed\n");
			nerrs++;
		पूर्ण अन्यथा अणु
			म_लिखो("[OK]\tChild succeeded\n");
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम setup_counter_page(व्योम)
अणु
	अचिन्हित पूर्णांक *page = mmap(शून्य, 4096, PROT_READ | PROT_WRITE,
			 MAP_ANONYMOUS | MAP_PRIVATE | MAP_32BIT, -1, 0);
	अगर (page == MAP_FAILED)
		err(1, "mmap");

	क्रम (पूर्णांक i = 0; i < 1024; i++)
		page[i] = i;
	counter_page = page;
पूर्ण

अटल पूर्णांक invoke_set_thपढ़ो_area(व्योम)
अणु
	पूर्णांक ret;
	यंत्र अस्थिर ("int $0x80"
		      : "=a" (ret), "+m" (low_user_desc) :
			"a" (243), "b" (low_user_desc)
		      : INT80_CLOBBERS);
	वापस ret;
पूर्ण

अटल व्योम setup_low_user_desc(व्योम)
अणु
	low_user_desc = mmap(शून्य, 2 * माप(काष्ठा user_desc),
			     PROT_READ | PROT_WRITE,
			     MAP_ANONYMOUS | MAP_PRIVATE | MAP_32BIT, -1, 0);
	अगर (low_user_desc == MAP_FAILED)
		err(1, "mmap");

	low_user_desc->entry_number	= -1;
	low_user_desc->base_addr	= (अचिन्हित दीर्घ)&counter_page[1];
	low_user_desc->limit		= 0xfffff;
	low_user_desc->seg_32bit	= 1;
	low_user_desc->contents		= 0; /* Data, grow-up*/
	low_user_desc->पढ़ो_exec_only	= 0;
	low_user_desc->limit_in_pages	= 1;
	low_user_desc->seg_not_present	= 0;
	low_user_desc->useable		= 0;

	अगर (invoke_set_thपढ़ो_area() == 0) अणु
		gdt_entry_num = low_user_desc->entry_number;
		म_लिखो("[NOTE]\tset_thread_area is available; will use GDT index %d\n", gdt_entry_num);
	पूर्ण अन्यथा अणु
		म_लिखो("[NOTE]\tset_thread_area is unavailable\n");
	पूर्ण

	low_user_desc_clear = low_user_desc + 1;
	low_user_desc_clear->entry_number = gdt_entry_num;
	low_user_desc_clear->पढ़ो_exec_only = 1;
	low_user_desc_clear->seg_not_present = 1;
पूर्ण

अटल व्योम test_gdt_invalidation(व्योम)
अणु
	अगर (!gdt_entry_num)
		वापस;	/* 64-bit only प्रणाली -- we can't use set_thपढ़ो_area */

	अचिन्हित लघु prev_sel;
	अचिन्हित लघु sel;
	अचिन्हित पूर्णांक eax;
	स्थिर अक्षर *result;
#अगर_घोषित __x86_64__
	अचिन्हित दीर्घ saved_base;
	अचिन्हित दीर्घ new_base;
#पूर्ण_अगर

	/* Test DS */
	invoke_set_thपढ़ो_area();
	eax = 243;
	sel = (gdt_entry_num << 3) | 3;
	यंत्र अस्थिर ("movw %%ds, %[prev_sel]\n\t"
		      "movw %[sel], %%ds\n\t"
#अगर_घोषित __i386__
		      "pushl %%ebx\n\t"
#पूर्ण_अगर
		      "movl %[arg1], %%ebx\n\t"
		      "int $0x80\n\t"	/* Should invalidate ds */
#अगर_घोषित __i386__
		      "popl %%ebx\n\t"
#पूर्ण_अगर
		      "movw %%ds, %[sel]\n\t"
		      "movw %[prev_sel], %%ds"
		      : [prev_sel] "=&r" (prev_sel), [sel] "+r" (sel),
			"+a" (eax)
		      : "m" (low_user_desc_clear),
			[arg1] "r" ((अचिन्हित पूर्णांक)(अचिन्हित दीर्घ)low_user_desc_clear)
		      : INT80_CLOBBERS);

	अगर (sel != 0) अणु
		result = "FAIL";
		nerrs++;
	पूर्ण अन्यथा अणु
		result = "OK";
	पूर्ण
	म_लिखो("[%s]\tInvalidate DS with set_thread_area: new DS = 0x%hx\n",
	       result, sel);

	/* Test ES */
	invoke_set_thपढ़ो_area();
	eax = 243;
	sel = (gdt_entry_num << 3) | 3;
	यंत्र अस्थिर ("movw %%es, %[prev_sel]\n\t"
		      "movw %[sel], %%es\n\t"
#अगर_घोषित __i386__
		      "pushl %%ebx\n\t"
#पूर्ण_अगर
		      "movl %[arg1], %%ebx\n\t"
		      "int $0x80\n\t"	/* Should invalidate es */
#अगर_घोषित __i386__
		      "popl %%ebx\n\t"
#पूर्ण_अगर
		      "movw %%es, %[sel]\n\t"
		      "movw %[prev_sel], %%es"
		      : [prev_sel] "=&r" (prev_sel), [sel] "+r" (sel),
			"+a" (eax)
		      : "m" (low_user_desc_clear),
			[arg1] "r" ((अचिन्हित पूर्णांक)(अचिन्हित दीर्घ)low_user_desc_clear)
		      : INT80_CLOBBERS);

	अगर (sel != 0) अणु
		result = "FAIL";
		nerrs++;
	पूर्ण अन्यथा अणु
		result = "OK";
	पूर्ण
	म_लिखो("[%s]\tInvalidate ES with set_thread_area: new ES = 0x%hx\n",
	       result, sel);

	/* Test FS */
	invoke_set_thपढ़ो_area();
	eax = 243;
	sel = (gdt_entry_num << 3) | 3;
#अगर_घोषित __x86_64__
	syscall(SYS_arch_prctl, ARCH_GET_FS, &saved_base);
#पूर्ण_अगर
	यंत्र अस्थिर ("movw %%fs, %[prev_sel]\n\t"
		      "movw %[sel], %%fs\n\t"
#अगर_घोषित __i386__
		      "pushl %%ebx\n\t"
#पूर्ण_अगर
		      "movl %[arg1], %%ebx\n\t"
		      "int $0x80\n\t"	/* Should invalidate fs */
#अगर_घोषित __i386__
		      "popl %%ebx\n\t"
#पूर्ण_अगर
		      "movw %%fs, %[sel]\n\t"
		      : [prev_sel] "=&r" (prev_sel), [sel] "+r" (sel),
			"+a" (eax)
		      : "m" (low_user_desc_clear),
			[arg1] "r" ((अचिन्हित पूर्णांक)(अचिन्हित दीर्घ)low_user_desc_clear)
		      : INT80_CLOBBERS);

#अगर_घोषित __x86_64__
	syscall(SYS_arch_prctl, ARCH_GET_FS, &new_base);
#पूर्ण_अगर

	/* Restore FS/BASE क्रम glibc */
	यंत्र अस्थिर ("movw %[prev_sel], %%fs" : : [prev_sel] "rm" (prev_sel));
#अगर_घोषित __x86_64__
	अगर (saved_base)
		syscall(SYS_arch_prctl, ARCH_SET_FS, saved_base);
#पूर्ण_अगर

	अगर (sel != 0) अणु
		result = "FAIL";
		nerrs++;
	पूर्ण अन्यथा अणु
		result = "OK";
	पूर्ण
	म_लिखो("[%s]\tInvalidate FS with set_thread_area: new FS = 0x%hx\n",
	       result, sel);

#अगर_घोषित __x86_64__
	अगर (sel == 0 && new_base != 0) अणु
		nerrs++;
		म_लिखो("[FAIL]\tNew FSBASE was 0x%lx\n", new_base);
	पूर्ण अन्यथा अणु
		म_लिखो("[OK]\tNew FSBASE was zero\n");
	पूर्ण
#पूर्ण_अगर

	/* Test GS */
	invoke_set_thपढ़ो_area();
	eax = 243;
	sel = (gdt_entry_num << 3) | 3;
#अगर_घोषित __x86_64__
	syscall(SYS_arch_prctl, ARCH_GET_GS, &saved_base);
#पूर्ण_अगर
	यंत्र अस्थिर ("movw %%gs, %[prev_sel]\n\t"
		      "movw %[sel], %%gs\n\t"
#अगर_घोषित __i386__
		      "pushl %%ebx\n\t"
#पूर्ण_अगर
		      "movl %[arg1], %%ebx\n\t"
		      "int $0x80\n\t"	/* Should invalidate gs */
#अगर_घोषित __i386__
		      "popl %%ebx\n\t"
#पूर्ण_अगर
		      "movw %%gs, %[sel]\n\t"
		      : [prev_sel] "=&r" (prev_sel), [sel] "+r" (sel),
			"+a" (eax)
		      : "m" (low_user_desc_clear),
			[arg1] "r" ((अचिन्हित पूर्णांक)(अचिन्हित दीर्घ)low_user_desc_clear)
		      : INT80_CLOBBERS);

#अगर_घोषित __x86_64__
	syscall(SYS_arch_prctl, ARCH_GET_GS, &new_base);
#पूर्ण_अगर

	/* Restore GS/BASE क्रम glibc */
	यंत्र अस्थिर ("movw %[prev_sel], %%gs" : : [prev_sel] "rm" (prev_sel));
#अगर_घोषित __x86_64__
	अगर (saved_base)
		syscall(SYS_arch_prctl, ARCH_SET_GS, saved_base);
#पूर्ण_अगर

	अगर (sel != 0) अणु
		result = "FAIL";
		nerrs++;
	पूर्ण अन्यथा अणु
		result = "OK";
	पूर्ण
	म_लिखो("[%s]\tInvalidate GS with set_thread_area: new GS = 0x%hx\n",
	       result, sel);

#अगर_घोषित __x86_64__
	अगर (sel == 0 && new_base != 0) अणु
		nerrs++;
		म_लिखो("[FAIL]\tNew GSBASE was 0x%lx\n", new_base);
	पूर्ण अन्यथा अणु
		म_लिखो("[OK]\tNew GSBASE was zero\n");
	पूर्ण
#पूर्ण_अगर
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	अगर (argc == 1 && !म_भेद(argv[0], "ldt_gdt_test_exec"))
		वापस finish_exec_test();

	setup_counter_page();
	setup_low_user_desc();

	करो_simple_tests();

	करो_multicpu_tests();

	करो_exec_test();

	test_gdt_invalidation();

	वापस nerrs ? 1 : 0;
पूर्ण
