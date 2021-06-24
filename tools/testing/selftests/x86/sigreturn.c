<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * sigवापस.c - tests क्रम x86 sigवापस(2) and निकास-to-userspace
 * Copyright (c) 2014-2015 Andrew Lutomirski
 *
 * This is a series of tests that exercises the sigवापस(2) syscall and
 * the IRET / SYSRET paths in the kernel.
 *
 * For now, this focuses on the effects of unusual CS and SS values,
 * and it has a bunch of tests to make sure that ESP/RSP is restored
 * properly.
 *
 * The basic idea behind these tests is to उठाओ(SIGUSR1) to create a
 * sigcontext frame, plug in the values to be tested, and then वापस,
 * which implicitly invokes sigवापस(2) and programs the user context
 * as desired.
 *
 * For tests क्रम which we expect sigवापस and the subsequent वापस to
 * user mode to succeed, we वापस to a लघु trampoline that generates
 * SIGTRAP so that the meat of the tests can be ordinary C code in a
 * SIGTRAP handler.
 *
 * The inner workings of each test is करोcumented below.
 *
 * Do not run on outdated, unpatched kernels at risk of nasty crashes.
 */

#घोषणा _GNU_SOURCE

#समावेश <sys/समय.स>
#समावेश <समय.स>
#समावेश <मानककोष.स>
#समावेश <sys/syscall.h>
#समावेश <unistd.h>
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <पूर्णांकtypes.h>
#समावेश <sys/mman.h>
#समावेश <sys/संकेत.स>
#समावेश <sys/ucontext.h>
#समावेश <यंत्र/ldt.h>
#समावेश <err.h>
#समावेश <समलाँघ.स>
#समावेश <मानकघोष.स>
#समावेश <stdbool.h>
#समावेश <sys/ptrace.h>
#समावेश <sys/user.h>

/* Pull in AR_xyz defines. */
प्रकार अचिन्हित पूर्णांक u32;
प्रकार अचिन्हित लघु u16;
#समावेश "../../../../arch/x86/include/asm/desc_defs.h"

/*
 * Copied from यंत्र/ucontext.h, as यंत्र/ucontext.h conflicts badly with the glibc
 * headers.
 */
#अगर_घोषित __x86_64__
/*
 * UC_SIGCONTEXT_SS will be set when delivering 64-bit or x32 संकेतs on
 * kernels that save SS in the sigcontext.  All kernels that set
 * UC_SIGCONTEXT_SS will correctly restore at least the low 32 bits of esp
 * regardless of SS (i.e. they implement espfix).
 *
 * Kernels that set UC_SIGCONTEXT_SS will also set UC_STRICT_RESTORE_SS
 * when delivering a संकेत that came from 64-bit code.
 *
 * Sigवापस restores SS as follows:
 *
 * अगर (saved SS is valid || UC_STRICT_RESTORE_SS is set ||
 *     saved CS is not 64-bit)
 *         new SS = saved SS  (will fail IRET and संकेत अगर invalid)
 * अन्यथा
 *         new SS = a flat 32-bit data segment
 */
#घोषणा UC_SIGCONTEXT_SS       0x2
#घोषणा UC_STRICT_RESTORE_SS   0x4
#पूर्ण_अगर

/*
 * In principle, this test can run on Linux emulation layers (e.g.
 * Illumos "LX branded zones").  Solaris-based kernels reserve LDT
 * entries 0-5 क्रम their own पूर्णांकernal purposes, so start our LDT
 * allocations above that reservation.  (The tests करोn't pass on LX
 * bअक्रमed zones, but at least this lets them run.)
 */
#घोषणा LDT_OFFSET 6

/* An aligned stack accessible through some of our segments. */
अटल अचिन्हित अक्षर stack16[65536] __attribute__((aligned(4096)));

/*
 * An aligned पूर्णांक3 inकाष्ठाion used as a trampoline.  Some of the tests
 * want to fish out their ss values, so this trampoline copies ss to eax
 * beक्रमe the पूर्णांक3.
 */
यंत्र (".pushsection .text\n\t"
     ".type int3, @function\n\t"
     ".align 4096\n\t"
     "int3:\n\t"
     "mov %ss,%ecx\n\t"
     "int3\n\t"
     ".size int3, . - int3\n\t"
     ".align 4096, 0xcc\n\t"
     ".popsection");
बाह्य अक्षर पूर्णांक3[4096];

/*
 * At startup, we prepapre:
 *
 * - ldt_nonexistent_sel: An LDT entry that करोesn't exist (all-zero
 *   descriptor or out of bounds).
 * - code16_sel: A 16-bit LDT code segment poपूर्णांकing to पूर्णांक3.
 * - data16_sel: A 16-bit LDT data segment poपूर्णांकing to stack16.
 * - npcode32_sel: A 32-bit not-present LDT code segment poपूर्णांकing to पूर्णांक3.
 * - npdata32_sel: A 32-bit not-present LDT data segment poपूर्णांकing to stack16.
 * - gdt_data16_idx: A 16-bit GDT data segment poपूर्णांकing to stack16.
 * - gdt_npdata32_idx: A 32-bit not-present GDT data segment poपूर्णांकing to
 *   stack16.
 *
 * For no particularly good reason, xyz_sel is a selector value with the
 * RPL and LDT bits filled in, whereas xyz_idx is just an index पूर्णांकo the
 * descriptor table.  These variables will be zero अगर their respective
 * segments could not be allocated.
 */
अटल अचिन्हित लघु ldt_nonexistent_sel;
अटल अचिन्हित लघु code16_sel, data16_sel, npcode32_sel, npdata32_sel;

अटल अचिन्हित लघु gdt_data16_idx, gdt_npdata32_idx;

अटल अचिन्हित लघु GDT3(पूर्णांक idx)
अणु
	वापस (idx << 3) | 3;
पूर्ण

अटल अचिन्हित लघु LDT3(पूर्णांक idx)
अणु
	वापस (idx << 3) | 7;
पूर्ण

/* Our sigaltstack scratch space. */
अटल अक्षर altstack_data[SIGSTKSZ];

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
पूर्ण

अटल व्योम clearhandler(पूर्णांक sig)
अणु
	काष्ठा sigaction sa;
	स_रखो(&sa, 0, माप(sa));
	sa.sa_handler = संक_पूर्व;
	sigemptyset(&sa.sa_mask);
	अगर (sigaction(sig, &sa, 0))
		err(1, "sigaction");
पूर्ण

अटल व्योम add_ldt(स्थिर काष्ठा user_desc *desc, अचिन्हित लघु *var,
		    स्थिर अक्षर *name)
अणु
	अगर (syscall(SYS_modअगरy_ldt, 1, desc, माप(*desc)) == 0) अणु
		*var = LDT3(desc->entry_number);
	पूर्ण अन्यथा अणु
		म_लिखो("[NOTE]\tFailed to create %s segment\n", name);
		*var = 0;
	पूर्ण
पूर्ण

अटल व्योम setup_ldt(व्योम)
अणु
	अगर ((अचिन्हित दीर्घ)stack16 > (1ULL << 32) - माप(stack16))
		errx(1, "stack16 is too high\n");
	अगर ((अचिन्हित दीर्घ)पूर्णांक3 > (1ULL << 32) - माप(पूर्णांक3))
		errx(1, "int3 is too high\n");

	ldt_nonexistent_sel = LDT3(LDT_OFFSET + 2);

	स्थिर काष्ठा user_desc code16_desc = अणु
		.entry_number    = LDT_OFFSET + 0,
		.base_addr       = (अचिन्हित दीर्घ)पूर्णांक3,
		.limit           = 4095,
		.seg_32bit       = 0,
		.contents        = 2, /* Code, not conक्रमming */
		.पढ़ो_exec_only  = 0,
		.limit_in_pages  = 0,
		.seg_not_present = 0,
		.useable         = 0
	पूर्ण;
	add_ldt(&code16_desc, &code16_sel, "code16");

	स्थिर काष्ठा user_desc data16_desc = अणु
		.entry_number    = LDT_OFFSET + 1,
		.base_addr       = (अचिन्हित दीर्घ)stack16,
		.limit           = 0xffff,
		.seg_32bit       = 0,
		.contents        = 0, /* Data, grow-up */
		.पढ़ो_exec_only  = 0,
		.limit_in_pages  = 0,
		.seg_not_present = 0,
		.useable         = 0
	पूर्ण;
	add_ldt(&data16_desc, &data16_sel, "data16");

	स्थिर काष्ठा user_desc npcode32_desc = अणु
		.entry_number    = LDT_OFFSET + 3,
		.base_addr       = (अचिन्हित दीर्घ)पूर्णांक3,
		.limit           = 4095,
		.seg_32bit       = 1,
		.contents        = 2, /* Code, not conक्रमming */
		.पढ़ो_exec_only  = 0,
		.limit_in_pages  = 0,
		.seg_not_present = 1,
		.useable         = 0
	पूर्ण;
	add_ldt(&npcode32_desc, &npcode32_sel, "npcode32");

	स्थिर काष्ठा user_desc npdata32_desc = अणु
		.entry_number    = LDT_OFFSET + 4,
		.base_addr       = (अचिन्हित दीर्घ)stack16,
		.limit           = 0xffff,
		.seg_32bit       = 1,
		.contents        = 0, /* Data, grow-up */
		.पढ़ो_exec_only  = 0,
		.limit_in_pages  = 0,
		.seg_not_present = 1,
		.useable         = 0
	पूर्ण;
	add_ldt(&npdata32_desc, &npdata32_sel, "npdata32");

	काष्ठा user_desc gdt_data16_desc = अणु
		.entry_number    = -1,
		.base_addr       = (अचिन्हित दीर्घ)stack16,
		.limit           = 0xffff,
		.seg_32bit       = 0,
		.contents        = 0, /* Data, grow-up */
		.पढ़ो_exec_only  = 0,
		.limit_in_pages  = 0,
		.seg_not_present = 0,
		.useable         = 0
	पूर्ण;

	अगर (syscall(SYS_set_thपढ़ो_area, &gdt_data16_desc) == 0) अणु
		/*
		 * This probably indicates vulnerability to CVE-2014-8133.
		 * Merely getting here isn't definitive, though, and we'll
		 * diagnose the problem क्रम real later on.
		 */
		म_लिखो("[WARN]\tset_thread_area allocated data16 at index %d\n",
		       gdt_data16_desc.entry_number);
		gdt_data16_idx = gdt_data16_desc.entry_number;
	पूर्ण अन्यथा अणु
		म_लिखो("[OK]\tset_thread_area refused 16-bit data\n");
	पूर्ण

	काष्ठा user_desc gdt_npdata32_desc = अणु
		.entry_number    = -1,
		.base_addr       = (अचिन्हित दीर्घ)stack16,
		.limit           = 0xffff,
		.seg_32bit       = 1,
		.contents        = 0, /* Data, grow-up */
		.पढ़ो_exec_only  = 0,
		.limit_in_pages  = 0,
		.seg_not_present = 1,
		.useable         = 0
	पूर्ण;

	अगर (syscall(SYS_set_thपढ़ो_area, &gdt_npdata32_desc) == 0) अणु
		/*
		 * As a hardening measure, newer kernels करोn't allow this.
		 */
		म_लिखो("[WARN]\tset_thread_area allocated npdata32 at index %d\n",
		       gdt_npdata32_desc.entry_number);
		gdt_npdata32_idx = gdt_npdata32_desc.entry_number;
	पूर्ण अन्यथा अणु
		म_लिखो("[OK]\tset_thread_area refused 16-bit data\n");
	पूर्ण
पूर्ण

/* State used by our संकेत handlers. */
अटल gregset_t initial_regs, requested_regs, resulting_regs;

/* Inकाष्ठाions क्रम the SIGUSR1 handler. */
अटल अस्थिर अचिन्हित लघु sig_cs, sig_ss;
अटल अस्थिर संक_पूर्ण_प्रकार sig_trapped, sig_err, sig_trapno;
#अगर_घोषित __x86_64__
अटल अस्थिर संक_पूर्ण_प्रकार sig_corrupt_final_ss;
#पूर्ण_अगर

/* Abstractions क्रम some 32-bit vs 64-bit dअगरferences. */
#अगर_घोषित __x86_64__
# define REG_IP REG_RIP
# define REG_SP REG_RSP
# define REG_CX REG_RCX

काष्ठा selectors अणु
	अचिन्हित लघु cs, gs, fs, ss;
पूर्ण;

अटल अचिन्हित लघु *ssptr(ucontext_t *ctx)
अणु
	काष्ठा selectors *sels = (व्योम *)&ctx->uc_mcontext.gregs[REG_CSGSFS];
	वापस &sels->ss;
पूर्ण

अटल अचिन्हित लघु *csptr(ucontext_t *ctx)
अणु
	काष्ठा selectors *sels = (व्योम *)&ctx->uc_mcontext.gregs[REG_CSGSFS];
	वापस &sels->cs;
पूर्ण
#अन्यथा
# define REG_IP REG_EIP
# define REG_SP REG_ESP
# define REG_CX REG_ECX

अटल greg_t *ssptr(ucontext_t *ctx)
अणु
	वापस &ctx->uc_mcontext.gregs[REG_SS];
पूर्ण

अटल greg_t *csptr(ucontext_t *ctx)
अणु
	वापस &ctx->uc_mcontext.gregs[REG_CS];
पूर्ण
#पूर्ण_अगर

/*
 * Checks a given selector क्रम its code bitness or वापसs -1 अगर it's not
 * a usable code segment selector.
 */
पूर्णांक cs_bitness(अचिन्हित लघु cs)
अणु
	uपूर्णांक32_t valid = 0, ar;
	यंत्र ("lar %[cs], %[ar]\n\t"
	     "jnz 1f\n\t"
	     "mov $1, %[valid]\n\t"
	     "1:"
	     : [ar] "=r" (ar), [valid] "+rm" (valid)
	     : [cs] "r" (cs));

	अगर (!valid)
		वापस -1;

	bool db = (ar & (1 << 22));
	bool l = (ar & (1 << 21));

	अगर (!(ar & (1<<11)))
	    वापस -1;	/* Not code. */

	अगर (l && !db)
		वापस 64;
	अन्यथा अगर (!l && db)
		वापस 32;
	अन्यथा अगर (!l && !db)
		वापस 16;
	अन्यथा
		वापस -1;	/* Unknown bitness. */
पूर्ण

/*
 * Checks a given selector क्रम its code bitness or वापसs -1 अगर it's not
 * a usable code segment selector.
 */
bool is_valid_ss(अचिन्हित लघु cs)
अणु
	uपूर्णांक32_t valid = 0, ar;
	यंत्र ("lar %[cs], %[ar]\n\t"
	     "jnz 1f\n\t"
	     "mov $1, %[valid]\n\t"
	     "1:"
	     : [ar] "=r" (ar), [valid] "+rm" (valid)
	     : [cs] "r" (cs));

	अगर (!valid)
		वापस false;

	अगर ((ar & AR_TYPE_MASK) != AR_TYPE_RWDATA &&
	    (ar & AR_TYPE_MASK) != AR_TYPE_RWDATA_EXPDOWN)
		वापस false;

	वापस (ar & AR_P);
पूर्ण

/* Number of errors in the current test हाल. */
अटल अस्थिर संक_पूर्ण_प्रकार nerrs;

अटल व्योम validate_संकेत_ss(पूर्णांक sig, ucontext_t *ctx)
अणु
#अगर_घोषित __x86_64__
	bool was_64bit = (cs_bitness(*csptr(ctx)) == 64);

	अगर (!(ctx->uc_flags & UC_SIGCONTEXT_SS)) अणु
		म_लिखो("[FAIL]\tUC_SIGCONTEXT_SS was not set\n");
		nerrs++;

		/*
		 * This happens on Linux 4.1.  The rest will fail, too, so
		 * वापस now to reduce the noise.
		 */
		वापस;
	पूर्ण

	/* UC_STRICT_RESTORE_SS is set अगरf we came from 64-bit mode. */
	अगर (!!(ctx->uc_flags & UC_STRICT_RESTORE_SS) != was_64bit) अणु
		म_लिखो("[FAIL]\tUC_STRICT_RESTORE_SS was wrong in signal %d\n",
		       sig);
		nerrs++;
	पूर्ण

	अगर (is_valid_ss(*ssptr(ctx))) अणु
		/*
		 * DOSEMU was written beक्रमe 64-bit sigcontext had SS, and
		 * it tries to figure out the संकेत source SS by looking at
		 * the physical रेजिस्टर.  Make sure that keeps working.
		 */
		अचिन्हित लघु hw_ss;
		यंत्र ("mov %%ss, %0" : "=rm" (hw_ss));
		अगर (hw_ss != *ssptr(ctx)) अणु
			म_लिखो("[FAIL]\tHW SS didn't match saved SS\n");
			nerrs++;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
पूर्ण

/*
 * SIGUSR1 handler.  Sets CS and SS as requested and poपूर्णांकs IP to the
 * पूर्णांक3 trampoline.  Sets SP to a large known value so that we can see
 * whether the value round-trips back to user mode correctly.
 */
अटल व्योम sigusr1(पूर्णांक sig, siginfo_t *info, व्योम *ctx_व्योम)
अणु
	ucontext_t *ctx = (ucontext_t*)ctx_व्योम;

	validate_संकेत_ss(sig, ctx);

	स_नकल(&initial_regs, &ctx->uc_mcontext.gregs, माप(gregset_t));

	*csptr(ctx) = sig_cs;
	*ssptr(ctx) = sig_ss;

	ctx->uc_mcontext.gregs[REG_IP] =
		sig_cs == code16_sel ? 0 : (अचिन्हित दीर्घ)&पूर्णांक3;
	ctx->uc_mcontext.gregs[REG_SP] = (अचिन्हित दीर्घ)0x8badf00d5aadc0deULL;
	ctx->uc_mcontext.gregs[REG_CX] = 0;

#अगर_घोषित __i386__
	/*
	 * Make sure the kernel करोesn't inadvertently use DS or ES-relative
	 * accesses in a region where user DS or ES is loaded.
	 *
	 * Skip this क्रम 64-bit builds because दीर्घ mode करोesn't care about
	 * DS and ES and skipping it increases test coverage a little bit,
	 * since 64-bit kernels can still run the 32-bit build.
	 */
	ctx->uc_mcontext.gregs[REG_DS] = 0;
	ctx->uc_mcontext.gregs[REG_ES] = 0;
#पूर्ण_अगर

	स_नकल(&requested_regs, &ctx->uc_mcontext.gregs, माप(gregset_t));
	requested_regs[REG_CX] = *ssptr(ctx);	/* The यंत्र code करोes this. */

	वापस;
पूर्ण

/*
 * Called after a successful sigवापस (via पूर्णांक3) or from a failed
 * sigवापस (directly by kernel).  Restores our state so that the
 * original उठाओ(SIGUSR1) वापसs.
 */
अटल व्योम sigtrap(पूर्णांक sig, siginfo_t *info, व्योम *ctx_व्योम)
अणु
	ucontext_t *ctx = (ucontext_t*)ctx_व्योम;

	validate_संकेत_ss(sig, ctx);

	sig_err = ctx->uc_mcontext.gregs[REG_ERR];
	sig_trapno = ctx->uc_mcontext.gregs[REG_TRAPNO];

	अचिन्हित लघु ss;
	यंत्र ("mov %%ss,%0" : "=r" (ss));

	greg_t यंत्र_ss = ctx->uc_mcontext.gregs[REG_CX];
	अगर (यंत्र_ss != sig_ss && sig == SIGTRAP) अणु
		/* Sanity check failure. */
		म_लिखो("[FAIL]\tSIGTRAP: ss = %hx, frame ss = %hx, ax = %llx\n",
		       ss, *ssptr(ctx), (अचिन्हित दीर्घ दीर्घ)यंत्र_ss);
		nerrs++;
	पूर्ण

	स_नकल(&resulting_regs, &ctx->uc_mcontext.gregs, माप(gregset_t));
	स_नकल(&ctx->uc_mcontext.gregs, &initial_regs, माप(gregset_t));

#अगर_घोषित __x86_64__
	अगर (sig_corrupt_final_ss) अणु
		अगर (ctx->uc_flags & UC_STRICT_RESTORE_SS) अणु
			म_लिखो("[FAIL]\tUC_STRICT_RESTORE_SS was set inappropriately\n");
			nerrs++;
		पूर्ण अन्यथा अणु
			/*
			 * DOSEMU transitions from 32-bit to 64-bit mode by
			 * adjusting sigcontext, and it requires that this work
			 * even अगर the saved SS is bogus.
			 */
			म_लिखो("\tCorrupting SS on return to 64-bit mode\n");
			*ssptr(ctx) = 0;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	sig_trapped = sig;
पूर्ण

#अगर_घोषित __x86_64__
/* Tests recovery अगर !UC_STRICT_RESTORE_SS */
अटल व्योम sigusr2(पूर्णांक sig, siginfo_t *info, व्योम *ctx_व्योम)
अणु
	ucontext_t *ctx = (ucontext_t*)ctx_व्योम;

	अगर (!(ctx->uc_flags & UC_STRICT_RESTORE_SS)) अणु
		म_लिखो("[FAIL]\traise(2) didn't set UC_STRICT_RESTORE_SS\n");
		nerrs++;
		वापस;  /* We can't करो the rest. */
	पूर्ण

	ctx->uc_flags &= ~UC_STRICT_RESTORE_SS;
	*ssptr(ctx) = 0;

	/* Return.  The kernel should recover without sending another संकेत. */
पूर्ण

अटल पूर्णांक test_nonstrict_ss(व्योम)
अणु
	clearhandler(SIGUSR1);
	clearhandler(SIGTRAP);
	clearhandler(संक_अंश);
	clearhandler(संक_अवैध);
	sethandler(SIGUSR2, sigusr2, 0);

	nerrs = 0;

	म_लिखो("[RUN]\tClear UC_STRICT_RESTORE_SS and corrupt SS\n");
	उठाओ(SIGUSR2);
	अगर (!nerrs)
		म_लिखो("[OK]\tIt worked\n");

	वापस nerrs;
पूर्ण
#पूर्ण_अगर

/* Finds a usable code segment of the requested bitness. */
पूर्णांक find_cs(पूर्णांक bitness)
अणु
	अचिन्हित लघु my_cs;

	यंत्र ("mov %%cs,%0" :  "=r" (my_cs));

	अगर (cs_bitness(my_cs) == bitness)
		वापस my_cs;
	अगर (cs_bitness(my_cs + (2 << 3)) == bitness)
		वापस my_cs + (2 << 3);
	अगर (my_cs > (2<<3) && cs_bitness(my_cs - (2 << 3)) == bitness)
	    वापस my_cs - (2 << 3);
	अगर (cs_bitness(code16_sel) == bitness)
		वापस code16_sel;

	म_लिखो("[WARN]\tCould not find %d-bit CS\n", bitness);
	वापस -1;
पूर्ण

अटल पूर्णांक test_valid_sigवापस(पूर्णांक cs_bits, bool use_16bit_ss, पूर्णांक क्रमce_ss)
अणु
	पूर्णांक cs = find_cs(cs_bits);
	अगर (cs == -1) अणु
		म_लिखो("[SKIP]\tCode segment unavailable for %d-bit CS, %d-bit SS\n",
		       cs_bits, use_16bit_ss ? 16 : 32);
		वापस 0;
	पूर्ण

	अगर (क्रमce_ss != -1) अणु
		sig_ss = क्रमce_ss;
	पूर्ण अन्यथा अणु
		अगर (use_16bit_ss) अणु
			अगर (!data16_sel) अणु
				म_लिखो("[SKIP]\tData segment unavailable for %d-bit CS, 16-bit SS\n",
				       cs_bits);
				वापस 0;
			पूर्ण
			sig_ss = data16_sel;
		पूर्ण अन्यथा अणु
			यंत्र अस्थिर ("mov %%ss,%0" : "=r" (sig_ss));
		पूर्ण
	पूर्ण

	sig_cs = cs;

	म_लिखो("[RUN]\tValid sigreturn: %d-bit CS (%hx), %d-bit SS (%hx%s)\n",
	       cs_bits, sig_cs, use_16bit_ss ? 16 : 32, sig_ss,
	       (sig_ss & 4) ? "" : ", GDT");

	उठाओ(SIGUSR1);

	nerrs = 0;

	/*
	 * Check that each रेजिस्टर had an acceptable value when the
	 * पूर्णांक3 trampoline was invoked.
	 */
	क्रम (पूर्णांक i = 0; i < NGREG; i++) अणु
		greg_t req = requested_regs[i], res = resulting_regs[i];

		अगर (i == REG_TRAPNO || i == REG_IP)
			जारी;	/* करोn't care */

		अगर (i == REG_SP) अणु
			/*
			 * If we were using a 16-bit stack segment, then
			 * the kernel is a bit stuck: IRET only restores
			 * the low 16 bits of ESP/RSP अगर SS is 16-bit.
			 * The kernel uses a hack to restore bits 31:16,
			 * but that hack करोesn't help with bits 63:32.
			 * On Intel CPUs, bits 63:32 end up zeroed, and, on
			 * AMD CPUs, they leak the high bits of the kernel
			 * espfix64 stack poपूर्णांकer.  There's very little that
			 * the kernel can करो about it.
			 *
			 * Similarly, अगर we are वापसing to a 32-bit context,
			 * the CPU will often lose the high 32 bits of RSP.
			 */

			अगर (res == req)
				जारी;

			अगर (cs_bits != 64 && ((res ^ req) & 0xFFFFFFFF) == 0) अणु
				म_लिखो("[NOTE]\tSP: %llx -> %llx\n",
				       (अचिन्हित दीर्घ दीर्घ)req,
				       (अचिन्हित दीर्घ दीर्घ)res);
				जारी;
			पूर्ण

			म_लिखो("[FAIL]\tSP mismatch: requested 0x%llx; got 0x%llx\n",
			       (अचिन्हित दीर्घ दीर्घ)requested_regs[i],
			       (अचिन्हित दीर्घ दीर्घ)resulting_regs[i]);
			nerrs++;
			जारी;
		पूर्ण

		bool ignore_reg = false;
#अगर __i386__
		अगर (i == REG_UESP)
			ignore_reg = true;
#अन्यथा
		अगर (i == REG_CSGSFS) अणु
			काष्ठा selectors *req_sels =
				(व्योम *)&requested_regs[REG_CSGSFS];
			काष्ठा selectors *res_sels =
				(व्योम *)&resulting_regs[REG_CSGSFS];
			अगर (req_sels->cs != res_sels->cs) अणु
				म_लिखो("[FAIL]\tCS mismatch: requested 0x%hx; got 0x%hx\n",
				       req_sels->cs, res_sels->cs);
				nerrs++;
			पूर्ण

			अगर (req_sels->ss != res_sels->ss) अणु
				म_लिखो("[FAIL]\tSS mismatch: requested 0x%hx; got 0x%hx\n",
				       req_sels->ss, res_sels->ss);
				nerrs++;
			पूर्ण

			जारी;
		पूर्ण
#पूर्ण_अगर

		/* Sanity check on the kernel */
		अगर (i == REG_CX && req != res) अणु
			म_लिखो("[FAIL]\tCX (saved SP) mismatch: requested 0x%llx; got 0x%llx\n",
			       (अचिन्हित दीर्घ दीर्घ)req,
			       (अचिन्हित दीर्घ दीर्घ)res);
			nerrs++;
			जारी;
		पूर्ण

		अगर (req != res && !ignore_reg) अणु
			म_लिखो("[FAIL]\tReg %d mismatch: requested 0x%llx; got 0x%llx\n",
			       i, (अचिन्हित दीर्घ दीर्घ)req,
			       (अचिन्हित दीर्घ दीर्घ)res);
			nerrs++;
		पूर्ण
	पूर्ण

	अगर (nerrs == 0)
		म_लिखो("[OK]\tall registers okay\n");

	वापस nerrs;
पूर्ण

अटल पूर्णांक test_bad_iret(पूर्णांक cs_bits, अचिन्हित लघु ss, पूर्णांक क्रमce_cs)
अणु
	पूर्णांक cs = क्रमce_cs == -1 ? find_cs(cs_bits) : क्रमce_cs;
	अगर (cs == -1)
		वापस 0;

	sig_cs = cs;
	sig_ss = ss;

	म_लिखो("[RUN]\t%d-bit CS (%hx), bogus SS (%hx)\n",
	       cs_bits, sig_cs, sig_ss);

	sig_trapped = 0;
	उठाओ(SIGUSR1);
	अगर (sig_trapped) अणु
		अक्षर errdesc[32] = "";
		अगर (sig_err) अणु
			स्थिर अक्षर *src = (sig_err & 1) ? " EXT" : "";
			स्थिर अक्षर *table;
			अगर ((sig_err & 0x6) == 0x0)
				table = "GDT";
			अन्यथा अगर ((sig_err & 0x6) == 0x4)
				table = "LDT";
			अन्यथा अगर ((sig_err & 0x6) == 0x2)
				table = "IDT";
			अन्यथा
				table = "???";

			प्र_लिखो(errdesc, "%s%s index %d, ",
				table, src, sig_err >> 3);
		पूर्ण

		अक्षर trapname[32];
		अगर (sig_trapno == 13)
			म_नकल(trapname, "GP");
		अन्यथा अगर (sig_trapno == 11)
			म_नकल(trapname, "NP");
		अन्यथा अगर (sig_trapno == 12)
			म_नकल(trapname, "SS");
		अन्यथा अगर (sig_trapno == 32)
			म_नकल(trapname, "IRET");  /* X86_TRAP_IRET */
		अन्यथा
			प्र_लिखो(trapname, "%d", sig_trapno);

		म_लिखो("[OK]\tGot #%s(0x%lx) (i.e. %s%s)\n",
		       trapname, (अचिन्हित दीर्घ)sig_err,
		       errdesc, strसंकेत(sig_trapped));
		वापस 0;
	पूर्ण अन्यथा अणु
		/*
		 * This also implicitly tests UC_STRICT_RESTORE_SS:
		 * We check that these संकेतs set UC_STRICT_RESTORE_SS and,
		 * अगर UC_STRICT_RESTORE_SS करोesn't cause strict behavior,
		 * then we won't get संक_अंश.
		 */
		म_लिखो("[FAIL]\tDid not get SIGSEGV\n");
		वापस 1;
	पूर्ण
पूर्ण

पूर्णांक मुख्य()
अणु
	पूर्णांक total_nerrs = 0;
	अचिन्हित लघु my_cs, my_ss;

	यंत्र अस्थिर ("mov %%cs,%0" : "=r" (my_cs));
	यंत्र अस्थिर ("mov %%ss,%0" : "=r" (my_ss));
	setup_ldt();

	stack_t stack = अणु
		.ss_sp = altstack_data,
		.ss_size = SIGSTKSZ,
	पूर्ण;
	अगर (sigaltstack(&stack, शून्य) != 0)
		err(1, "sigaltstack");

	sethandler(SIGUSR1, sigusr1, 0);
	sethandler(SIGTRAP, sigtrap, SA_ONSTACK);

	/* Easy हालs: वापस to a 32-bit SS in each possible CS bitness. */
	total_nerrs += test_valid_sigवापस(64, false, -1);
	total_nerrs += test_valid_sigवापस(32, false, -1);
	total_nerrs += test_valid_sigवापस(16, false, -1);

	/*
	 * Test easy espfix हालs: वापस to a 16-bit LDT SS in each possible
	 * CS bitness.  NB: with a दीर्घ mode CS, the SS bitness is irrelevant.
	 *
	 * This catches the original missing-espfix-on-64-bit-kernels issue
	 * as well as CVE-2014-8134.
	 */
	total_nerrs += test_valid_sigवापस(64, true, -1);
	total_nerrs += test_valid_sigवापस(32, true, -1);
	total_nerrs += test_valid_sigवापस(16, true, -1);

	अगर (gdt_data16_idx) अणु
		/*
		 * For perक्रमmance reasons, Linux skips espfix अगर SS poपूर्णांकs
		 * to the GDT.  If we were able to allocate a 16-bit SS in
		 * the GDT, see अगर it leaks parts of the kernel stack poपूर्णांकer.
		 *
		 * This tests क्रम CVE-2014-8133.
		 */
		total_nerrs += test_valid_sigवापस(64, true,
						    GDT3(gdt_data16_idx));
		total_nerrs += test_valid_sigवापस(32, true,
						    GDT3(gdt_data16_idx));
		total_nerrs += test_valid_sigवापस(16, true,
						    GDT3(gdt_data16_idx));
	पूर्ण

#अगर_घोषित __x86_64__
	/* Nasty ABI हाल: check SS corruption handling. */
	sig_corrupt_final_ss = 1;
	total_nerrs += test_valid_sigवापस(32, false, -1);
	total_nerrs += test_valid_sigवापस(32, true, -1);
	sig_corrupt_final_ss = 0;
#पूर्ण_अगर

	/*
	 * We're करोne testing valid sigवापस हालs.  Now we test states
	 * क्रम which sigवापस itself will succeed but the subsequent
	 * entry to user mode will fail.
	 *
	 * Depending on the failure mode and the kernel bitness, these
	 * entry failures can generate संक_अंश, SIGBUS, or संक_अवैध.
	 */
	clearhandler(SIGTRAP);
	sethandler(संक_अंश, sigtrap, SA_ONSTACK);
	sethandler(SIGBUS, sigtrap, SA_ONSTACK);
	sethandler(संक_अवैध, sigtrap, SA_ONSTACK);  /* 32-bit kernels करो this */

	/* Easy failures: invalid SS, resulting in #GP(0) */
	test_bad_iret(64, ldt_nonexistent_sel, -1);
	test_bad_iret(32, ldt_nonexistent_sel, -1);
	test_bad_iret(16, ldt_nonexistent_sel, -1);

	/* These fail because SS isn't a data segment, resulting in #GP(SS) */
	test_bad_iret(64, my_cs, -1);
	test_bad_iret(32, my_cs, -1);
	test_bad_iret(16, my_cs, -1);

	/* Try to वापस to a not-present code segment, triggering #NP(SS). */
	test_bad_iret(32, my_ss, npcode32_sel);

	/*
	 * Try to वापस to a not-present but otherwise valid data segment.
	 * This will cause IRET to fail with #SS on the espfix stack.  This
	 * exercises CVE-2014-9322.
	 *
	 * Note that, अगर espfix is enabled, 64-bit Linux will lose track
	 * of the actual cause of failure and report #GP(0) instead.
	 * This would be very dअगरficult क्रम Linux to aव्योम, because
	 * espfix64 causes IRET failures to be promoted to #DF, so the
	 * original exception frame is never pushed onto the stack.
	 */
	test_bad_iret(32, npdata32_sel, -1);

	/*
	 * Try to वापस to a not-present but otherwise valid data
	 * segment without invoking espfix.  Newer kernels करोn't allow
	 * this to happen in the first place.  On older kernels, though,
	 * this can trigger CVE-2014-9322.
	 */
	अगर (gdt_npdata32_idx)
		test_bad_iret(32, GDT3(gdt_npdata32_idx), -1);

#अगर_घोषित __x86_64__
	total_nerrs += test_nonstrict_ss();
#पूर्ण_अगर

	वापस total_nerrs ? 1 : 0;
पूर्ण
