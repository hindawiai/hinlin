<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * unwind_vdso.c - tests unwind info क्रम AT_SYSINFO in the vDSO
 * Copyright (c) 2014-2015 Andrew Lutomirski
 *
 * This tests __kernel_vsyscall's unwind info.
 */

#घोषणा _GNU_SOURCE

#समावेश <features.h>
#समावेश <मानकपन.स>

#समावेश "helpers.h"

#अगर defined(__GLIBC__) && __GLIBC__ == 2 && __GLIBC_MINOR__ < 16

पूर्णांक मुख्य()
अणु
	/* We need getauxval(). */
	म_लिखो("[SKIP]\tGLIBC before 2.16 cannot compile this test\n");
	वापस 0;
पूर्ण

#अन्यथा

#समावेश <sys/समय.स>
#समावेश <मानककोष.स>
#समावेश <syscall.h>
#समावेश <unistd.h>
#समावेश <माला.स>
#समावेश <पूर्णांकtypes.h>
#समावेश <sys/mman.h>
#समावेश <संकेत.स>
#समावेश <sys/ucontext.h>
#समावेश <err.h>
#समावेश <मानकघोष.स>
#समावेश <stdbool.h>
#समावेश <sys/ptrace.h>
#समावेश <sys/user.h>
#समावेश <link.h>
#समावेश <sys/auxv.h>
#समावेश <dlfcn.h>
#समावेश <unwind.h>

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

अटल अस्थिर संक_पूर्ण_प्रकार nerrs;
अटल अचिन्हित दीर्घ sysinfo;
अटल bool got_sysinfo = false;
अटल अचिन्हित दीर्घ वापस_address;

काष्ठा unwind_state अणु
	अचिन्हित दीर्घ ip;	/* trap source */
	पूर्णांक depth;		/* -1 until we hit the trap source */
पूर्ण;

_Unwind_Reason_Code trace_fn(काष्ठा _Unwind_Context * ctx, व्योम *opaque)
अणु
	काष्ठा unwind_state *state = opaque;
	अचिन्हित दीर्घ ip = _Unwind_GetIP(ctx);

	अगर (state->depth == -1) अणु
		अगर (ip == state->ip)
			state->depth = 0;
		अन्यथा
			वापस _URC_NO_REASON;	/* Not there yet */
	पूर्ण
	म_लिखो("\t  0x%lx\n", ip);

	अगर (ip == वापस_address) अणु
		/* Here we are. */
		अचिन्हित दीर्घ eax = _Unwind_GetGR(ctx, 0);
		अचिन्हित दीर्घ ecx = _Unwind_GetGR(ctx, 1);
		अचिन्हित दीर्घ edx = _Unwind_GetGR(ctx, 2);
		अचिन्हित दीर्घ ebx = _Unwind_GetGR(ctx, 3);
		अचिन्हित दीर्घ ebp = _Unwind_GetGR(ctx, 5);
		अचिन्हित दीर्घ esi = _Unwind_GetGR(ctx, 6);
		अचिन्हित दीर्घ edi = _Unwind_GetGR(ctx, 7);
		bool ok = (eax == SYS_getpid || eax == getpid()) &&
			ebx == 1 && ecx == 2 && edx == 3 &&
			esi == 4 && edi == 5 && ebp == 6;

		अगर (!ok)
			nerrs++;
		म_लिखो("[%s]\t  NR = %ld, args = %ld, %ld, %ld, %ld, %ld, %ld\n",
		       (ok ? "OK" : "FAIL"),
		       eax, ebx, ecx, edx, esi, edi, ebp);

		वापस _URC_NORMAL_STOP;
	पूर्ण अन्यथा अणु
		state->depth++;
		वापस _URC_NO_REASON;
	पूर्ण
पूर्ण

अटल व्योम sigtrap(पूर्णांक sig, siginfo_t *info, व्योम *ctx_व्योम)
अणु
	ucontext_t *ctx = (ucontext_t *)ctx_व्योम;
	काष्ठा unwind_state state;
	अचिन्हित दीर्घ ip = ctx->uc_mcontext.gregs[REG_EIP];

	अगर (!got_sysinfo && ip == sysinfo) अणु
		got_sysinfo = true;

		/* Find the वापस address. */
		वापस_address = *(अचिन्हित दीर्घ *)(अचिन्हित दीर्घ)ctx->uc_mcontext.gregs[REG_ESP];

		म_लिखो("\tIn vsyscall at 0x%lx, returning to 0x%lx\n",
		       ip, वापस_address);
	पूर्ण

	अगर (!got_sysinfo)
		वापस;		/* Not there yet */

	अगर (ip == वापस_address) अणु
		ctx->uc_mcontext.gregs[REG_EFL] &= ~X86_EFLAGS_TF;
		म_लिखो("\tVsyscall is done\n");
		वापस;
	पूर्ण

	म_लिखो("\tSIGTRAP at 0x%lx\n", ip);

	state.ip = ip;
	state.depth = -1;
	_Unwind_Backtrace(trace_fn, &state);
पूर्ण

पूर्णांक मुख्य()
अणु
	sysinfo = getauxval(AT_SYSINFO);
	म_लिखो("\tAT_SYSINFO is 0x%lx\n", sysinfo);

	Dl_info info;
	अगर (!dladdr((व्योम *)sysinfo, &info)) अणु
		म_लिखो("[WARN]\tdladdr failed on AT_SYSINFO\n");
	पूर्ण अन्यथा अणु
		म_लिखो("[OK]\tAT_SYSINFO maps to %s, loaded at 0x%p\n",
		       info.dli_fname, info.dli_fbase);
	पूर्ण

	sethandler(SIGTRAP, sigtrap, 0);

	syscall(SYS_getpid);  /* Force symbol binding without TF set. */
	म_लिखो("[RUN]\tSet TF and check a fast syscall\n");
	set_eflags(get_eflags() | X86_EFLAGS_TF);
	syscall(SYS_getpid, 1, 2, 3, 4, 5, 6);
	अगर (!got_sysinfo) अणु
		set_eflags(get_eflags() & ~X86_EFLAGS_TF);

		/*
		 * The most likely cause of this is that you're on Debian or
		 * a Debian-based distro, you're missing libc6-i686, and you're
		 * affected by libc/19006 (https://sourceware.org/PR19006).
		 */
		म_लिखो("[WARN]\tsyscall(2) didn't enter AT_SYSINFO\n");
	पूर्ण

	अगर (get_eflags() & X86_EFLAGS_TF) अणु
		म_लिखो("[FAIL]\tTF is still set\n");
		nerrs++;
	पूर्ण

	अगर (nerrs) अणु
		म_लिखो("[FAIL]\tThere were errors\n");
		वापस 1;
	पूर्ण अन्यथा अणु
		म_लिखो("[OK]\tAll is well\n");
		वापस 0;
	पूर्ण
पूर्ण

#पूर्ण_अगर	/* New enough libc */
