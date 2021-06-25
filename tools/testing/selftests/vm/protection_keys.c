<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Tests Memory Protection Keys (see Documentation/core-api/protection-keys.rst)
 *
 * There are examples in here of:
 *  * how to set protection keys on memory
 *  * how to set/clear bits in pkey रेजिस्टरs (the rights रेजिस्टर)
 *  * how to handle SEGV_PKUERR संकेतs and extract pkey-relevant
 *    inक्रमmation from the siginfo
 *
 * Things to add:
 *	make sure KSM and KSM COW अवरोधing works
 *	prefault pages in at दो_स्मृति, or not
 *	protect MPX bounds tables with protection keys?
 *	make sure VMA splitting/merging is working correctly
 *	OOMs can destroy mm->mmap (see निकास_mmap()), so make sure it is immune to pkeys
 *	look क्रम pkey "leaks" where it is still set on a VMA but "freed" back to the kernel
 *	करो a plain mprotect() to a mprotect_pkey() area and make sure the pkey sticks
 *
 * Compile like this:
 *	gcc      -o protection_keys    -O2 -g -std=gnu99 -pthपढ़ो -Wall protection_keys.c -lrt -ldl -lm
 *	gcc -m32 -o protection_keys_32 -O2 -g -std=gnu99 -pthपढ़ो -Wall protection_keys.c -lrt -ldl -lm
 */
#घोषणा _GNU_SOURCE
#घोषणा __SANE_USERSPACE_TYPES__
#समावेश <त्रुटिसं.स>
#समावेश <linux/futex.h>
#समावेश <समय.स>
#समावेश <sys/समय.स>
#समावेश <sys/syscall.h>
#समावेश <माला.स>
#समावेश <मानकपन.स>
#समावेश <मानक_निवेशt.h>
#समावेश <stdbool.h>
#समावेश <संकेत.स>
#समावेश <निश्चित.स>
#समावेश <मानककोष.स>
#समावेश <ucontext.h>
#समावेश <sys/mman.h>
#समावेश <sys/types.h>
#समावेश <sys/रुको.h>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>
#समावेश <unistd.h>
#समावेश <sys/ptrace.h>
#समावेश <समलाँघ.स>

#समावेश "pkey-helpers.h"

पूर्णांक iteration_nr = 1;
पूर्णांक test_nr;

u64 shaकरोw_pkey_reg;
पूर्णांक dprपूर्णांक_in_संकेत;
अक्षर dprपूर्णांक_in_संकेत_buffer[DPRINT_IN_SIGNAL_BUF_SIZE];

व्योम cat_पूर्णांकo_file(अक्षर *str, अक्षर *file)
अणु
	पूर्णांक fd = खोलो(file, O_RDWR);
	पूर्णांक ret;

	dम_लिखो2("%s(): writing '%s' to '%s'\n", __func__, str, file);
	/*
	 * these need to be raw because they are called under
	 * pkey_निश्चित()
	 */
	अगर (fd < 0) अणु
		ख_लिखो(मानक_त्रुटि, "error opening '%s'\n", str);
		लिखो_त्रुटि("error: ");
		निकास(__LINE__);
	पूर्ण

	ret = ग_लिखो(fd, str, म_माप(str));
	अगर (ret != म_माप(str)) अणु
		लिखो_त्रुटि("write to file failed");
		ख_लिखो(मानक_त्रुटि, "filename: '%s' str: '%s'\n", file, str);
		निकास(__LINE__);
	पूर्ण
	बंद(fd);
पूर्ण

#अगर CONTROL_TRACING > 0
अटल पूर्णांक warned_tracing;
पूर्णांक tracing_root_ok(व्योम)
अणु
	अगर (geteuid() != 0) अणु
		अगर (!warned_tracing)
			ख_लिखो(मानक_त्रुटि, "WARNING: not run as root, "
					"can not do tracing control\n");
		warned_tracing = 1;
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण
#पूर्ण_अगर

व्योम tracing_on(व्योम)
अणु
#अगर CONTROL_TRACING > 0
#घोषणा TRACEसूची "/sys/kernel/debug/tracing"
	अक्षर pidstr[32];

	अगर (!tracing_root_ok())
		वापस;

	प्र_लिखो(pidstr, "%d", getpid());
	cat_पूर्णांकo_file("0", TRACEसूची "/tracing_on");
	cat_पूर्णांकo_file("\n", TRACEसूची "/trace");
	अगर (1) अणु
		cat_पूर्णांकo_file("function_graph", TRACEसूची "/current_tracer");
		cat_पूर्णांकo_file("1", TRACEसूची "/options/funcgraph-proc");
	पूर्ण अन्यथा अणु
		cat_पूर्णांकo_file("nop", TRACEसूची "/current_tracer");
	पूर्ण
	cat_पूर्णांकo_file(pidstr, TRACEसूची "/set_ftrace_pid");
	cat_पूर्णांकo_file("1", TRACEसूची "/tracing_on");
	dम_लिखो1("enabled tracing\n");
#पूर्ण_अगर
पूर्ण

व्योम tracing_off(व्योम)
अणु
#अगर CONTROL_TRACING > 0
	अगर (!tracing_root_ok())
		वापस;
	cat_पूर्णांकo_file("0", "/sys/kernel/debug/tracing/tracing_on");
#पूर्ण_अगर
पूर्ण

व्योम पात_hooks(व्योम)
अणु
	ख_लिखो(मानक_त्रुटि, "running %s()...\n", __func__);
	tracing_off();
#अगर_घोषित SLEEP_ON_ABORT
	sleep(SLEEP_ON_ABORT);
#पूर्ण_अगर
पूर्ण

/*
 * This attempts to have roughly a page of inकाष्ठाions followed by a few
 * inकाष्ठाions that करो a ग_लिखो, and another page of inकाष्ठाions.  That
 * way, we are pretty sure that the ग_लिखो is in the second page of
 * inकाष्ठाions and has at least a page of padding behind it.
 *
 * *That* lets us be sure to madvise() away the ग_लिखो inकाष्ठाion, which
 * will then fault, which makes sure that the fault code handles
 * execute-only memory properly.
 */
#अगर_घोषित __घातerpc64__
/* This way, both 4K and 64K alignment are मुख्यtained */
__attribute__((__aligned__(65536)))
#अन्यथा
__attribute__((__aligned__(PAGE_SIZE)))
#पूर्ण_अगर
व्योम lots_o_noops_around_ग_लिखो(पूर्णांक *ग_लिखो_to_me)
अणु
	dम_लिखो3("running %s()\n", __func__);
	__page_o_noops();
	/* Assume this happens in the second page of inकाष्ठाions: */
	*ग_लिखो_to_me = __LINE__;
	/* pad out by another page: */
	__page_o_noops();
	dम_लिखो3("%s() done\n", __func__);
पूर्ण

व्योम dump_mem(व्योम *dumpme, पूर्णांक len_bytes)
अणु
	अक्षर *c = (व्योम *)dumpme;
	पूर्णांक i;

	क्रम (i = 0; i < len_bytes; i += माप(u64)) अणु
		u64 *ptr = (u64 *)(c + i);
		dम_लिखो1("dump[%03d][@%p]: %016llx\n", i, ptr, *ptr);
	पूर्ण
पूर्ण

अटल u32 hw_pkey_get(पूर्णांक pkey, अचिन्हित दीर्घ flags)
अणु
	u64 pkey_reg = __पढ़ो_pkey_reg();

	dम_लिखो1("%s(pkey=%d, flags=%lx) = %x / %d\n",
			__func__, pkey, flags, 0, 0);
	dम_लिखो2("%s() raw pkey_reg: %016llx\n", __func__, pkey_reg);

	वापस (u32) get_pkey_bits(pkey_reg, pkey);
पूर्ण

अटल पूर्णांक hw_pkey_set(पूर्णांक pkey, अचिन्हित दीर्घ rights, अचिन्हित दीर्घ flags)
अणु
	u32 mask = (PKEY_DISABLE_ACCESS|PKEY_DISABLE_WRITE);
	u64 old_pkey_reg = __पढ़ो_pkey_reg();
	u64 new_pkey_reg;

	/* make sure that 'rights' only contains the bits we expect: */
	निश्चित(!(rights & ~mask));

	/* modअगरy bits accordingly in old pkey_reg and assign it */
	new_pkey_reg = set_pkey_bits(old_pkey_reg, pkey, rights);

	__ग_लिखो_pkey_reg(new_pkey_reg);

	dम_लिखो3("%s(pkey=%d, rights=%lx, flags=%lx) = %x"
		" pkey_reg now: %016llx old_pkey_reg: %016llx\n",
		__func__, pkey, rights, flags, 0, __पढ़ो_pkey_reg(),
		old_pkey_reg);
	वापस 0;
पूर्ण

व्योम pkey_disable_set(पूर्णांक pkey, पूर्णांक flags)
अणु
	अचिन्हित दीर्घ syscall_flags = 0;
	पूर्णांक ret;
	पूर्णांक pkey_rights;
	u64 orig_pkey_reg = पढ़ो_pkey_reg();

	dम_लिखो1("START->%s(%d, 0x%x)\n", __func__,
		pkey, flags);
	pkey_निश्चित(flags & (PKEY_DISABLE_ACCESS | PKEY_DISABLE_WRITE));

	pkey_rights = hw_pkey_get(pkey, syscall_flags);

	dम_लिखो1("%s(%d) hw_pkey_get(%d): %x\n", __func__,
			pkey, pkey, pkey_rights);

	pkey_निश्चित(pkey_rights >= 0);

	pkey_rights |= flags;

	ret = hw_pkey_set(pkey, pkey_rights, syscall_flags);
	निश्चित(!ret);
	/* pkey_reg and flags have the same क्रमmat */
	shaकरोw_pkey_reg = set_pkey_bits(shaकरोw_pkey_reg, pkey, pkey_rights);
	dम_लिखो1("%s(%d) shadow: 0x%016llx\n",
		__func__, pkey, shaकरोw_pkey_reg);

	pkey_निश्चित(ret >= 0);

	pkey_rights = hw_pkey_get(pkey, syscall_flags);
	dम_लिखो1("%s(%d) hw_pkey_get(%d): %x\n", __func__,
			pkey, pkey, pkey_rights);

	dम_लिखो1("%s(%d) pkey_reg: 0x%016llx\n",
		__func__, pkey, पढ़ो_pkey_reg());
	अगर (flags)
		pkey_निश्चित(पढ़ो_pkey_reg() >= orig_pkey_reg);
	dम_लिखो1("END<---%s(%d, 0x%x)\n", __func__,
		pkey, flags);
पूर्ण

व्योम pkey_disable_clear(पूर्णांक pkey, पूर्णांक flags)
अणु
	अचिन्हित दीर्घ syscall_flags = 0;
	पूर्णांक ret;
	पूर्णांक pkey_rights = hw_pkey_get(pkey, syscall_flags);
	u64 orig_pkey_reg = पढ़ो_pkey_reg();

	pkey_निश्चित(flags & (PKEY_DISABLE_ACCESS | PKEY_DISABLE_WRITE));

	dम_लिखो1("%s(%d) hw_pkey_get(%d): %x\n", __func__,
			pkey, pkey, pkey_rights);
	pkey_निश्चित(pkey_rights >= 0);

	pkey_rights &= ~flags;

	ret = hw_pkey_set(pkey, pkey_rights, 0);
	shaकरोw_pkey_reg = set_pkey_bits(shaकरोw_pkey_reg, pkey, pkey_rights);
	pkey_निश्चित(ret >= 0);

	pkey_rights = hw_pkey_get(pkey, syscall_flags);
	dम_लिखो1("%s(%d) hw_pkey_get(%d): %x\n", __func__,
			pkey, pkey, pkey_rights);

	dम_लिखो1("%s(%d) pkey_reg: 0x%016llx\n", __func__,
			pkey, पढ़ो_pkey_reg());
	अगर (flags)
		निश्चित(पढ़ो_pkey_reg() <= orig_pkey_reg);
पूर्ण

व्योम pkey_ग_लिखो_allow(पूर्णांक pkey)
अणु
	pkey_disable_clear(pkey, PKEY_DISABLE_WRITE);
पूर्ण
व्योम pkey_ग_लिखो_deny(पूर्णांक pkey)
अणु
	pkey_disable_set(pkey, PKEY_DISABLE_WRITE);
पूर्ण
व्योम pkey_access_allow(पूर्णांक pkey)
अणु
	pkey_disable_clear(pkey, PKEY_DISABLE_ACCESS);
पूर्ण
व्योम pkey_access_deny(पूर्णांक pkey)
अणु
	pkey_disable_set(pkey, PKEY_DISABLE_ACCESS);
पूर्ण

/* Failed address bound checks: */
#अगर_अघोषित SEGV_BNDERR
# define SEGV_BNDERR		3
#पूर्ण_अगर

#अगर_अघोषित SEGV_PKUERR
# define SEGV_PKUERR		4
#पूर्ण_अगर

अटल अक्षर *si_code_str(पूर्णांक si_code)
अणु
	अगर (si_code == SEGV_MAPERR)
		वापस "SEGV_MAPERR";
	अगर (si_code == SEGV_ACCERR)
		वापस "SEGV_ACCERR";
	अगर (si_code == SEGV_BNDERR)
		वापस "SEGV_BNDERR";
	अगर (si_code == SEGV_PKUERR)
		वापस "SEGV_PKUERR";
	वापस "UNKNOWN";
पूर्ण

पूर्णांक pkey_faults;
पूर्णांक last_si_pkey = -1;
व्योम संकेत_handler(पूर्णांक signum, siginfo_t *si, व्योम *vucontext)
अणु
	ucontext_t *uctxt = vucontext;
	पूर्णांक trapno;
	अचिन्हित दीर्घ ip;
	अक्षर *fpregs;
#अगर defined(__i386__) || defined(__x86_64__) /* arch */
	u32 *pkey_reg_ptr;
	पूर्णांक pkey_reg_offset;
#पूर्ण_अगर /* arch */
	u64 siginfo_pkey;
	u32 *si_pkey_ptr;

	dprपूर्णांक_in_संकेत = 1;
	dम_लिखो1(">>>>===============SIGSEGV============================\n");
	dम_लिखो1("%s()::%d, pkey_reg: 0x%016llx shadow: %016llx\n",
			__func__, __LINE__,
			__पढ़ो_pkey_reg(), shaकरोw_pkey_reg);

	trapno = uctxt->uc_mcontext.gregs[REG_TRAPNO];
	ip = uctxt->uc_mcontext.gregs[REG_IP_IDX];
	fpregs = (अक्षर *) uctxt->uc_mcontext.fpregs;

	dम_लिखो2("%s() trapno: %d ip: 0x%016lx info->si_code: %s/%d\n",
			__func__, trapno, ip, si_code_str(si->si_code),
			si->si_code);

#अगर defined(__i386__) || defined(__x86_64__) /* arch */
#अगर_घोषित __i386__
	/*
	 * 32-bit has some extra padding so that userspace can tell whether
	 * the XSTATE header is present in addition to the "legacy" FPU
	 * state.  We just assume that it is here.
	 */
	fpregs += 0x70;
#पूर्ण_अगर /* i386 */
	pkey_reg_offset = pkey_reg_xstate_offset();
	pkey_reg_ptr = (व्योम *)(&fpregs[pkey_reg_offset]);

	/*
	 * If we got a PKEY fault, we *HAVE* to have at least one bit set in
	 * here.
	 */
	dम_लिखो1("pkey_reg_xstate_offset: %d\n", pkey_reg_xstate_offset());
	अगर (DEBUG_LEVEL > 4)
		dump_mem(pkey_reg_ptr - 128, 256);
	pkey_निश्चित(*pkey_reg_ptr);
#पूर्ण_अगर /* arch */

	dम_लिखो1("siginfo: %p\n", si);
	dम_लिखो1(" fpregs: %p\n", fpregs);

	अगर ((si->si_code == SEGV_MAPERR) ||
	    (si->si_code == SEGV_ACCERR) ||
	    (si->si_code == SEGV_BNDERR)) अणु
		म_लिखो("non-PK si_code, exiting...\n");
		निकास(4);
	पूर्ण

	si_pkey_ptr = siginfo_get_pkey_ptr(si);
	dम_लिखो1("si_pkey_ptr: %p\n", si_pkey_ptr);
	dump_mem((u8 *)si_pkey_ptr - 8, 24);
	siginfo_pkey = *si_pkey_ptr;
	pkey_निश्चित(siginfo_pkey < NR_PKEYS);
	last_si_pkey = siginfo_pkey;

	/*
	 * need __पढ़ो_pkey_reg() version so we करो not करो shaकरोw_pkey_reg
	 * checking
	 */
	dम_लिखो1("signal pkey_reg from  pkey_reg: %016llx\n",
			__पढ़ो_pkey_reg());
	dम_लिखो1("pkey from siginfo: %016llx\n", siginfo_pkey);
#अगर defined(__i386__) || defined(__x86_64__) /* arch */
	dम_लिखो1("signal pkey_reg from xsave: %08x\n", *pkey_reg_ptr);
	*(u64 *)pkey_reg_ptr = 0x00000000;
	dम_लिखो1("WARNING: set PKEY_REG=0 to allow faulting instruction to continue\n");
#या_अगर defined(__घातerpc64__) /* arch */
	/* restore access and let the faulting inकाष्ठाion जारी */
	pkey_access_allow(siginfo_pkey);
#पूर्ण_अगर /* arch */
	pkey_faults++;
	dम_लिखो1("<<<<==================================================\n");
	dprपूर्णांक_in_संकेत = 0;
पूर्ण

पूर्णांक रुको_all_children(व्योम)
अणु
	पूर्णांक status;
	वापस रुकोpid(-1, &status, 0);
पूर्ण

व्योम sig_chld(पूर्णांक x)
अणु
	dprपूर्णांक_in_संकेत = 1;
	dम_लिखो2("[%d] SIGCHLD: %d\n", getpid(), x);
	dprपूर्णांक_in_संकेत = 0;
पूर्ण

व्योम setup_sigsegv_handler(व्योम)
अणु
	पूर्णांक r, rs;
	काष्ठा sigaction newact;
	काष्ठा sigaction oldact;

	/* #PF is mapped to sigsegv */
	पूर्णांक signum  = संक_अंश;

	newact.sa_handler = 0;
	newact.sa_sigaction = संकेत_handler;

	/*sigset_t - संकेतs to block जबतक in the handler */
	/* get the old संकेत mask. */
	rs = sigprocmask(SIG_SETMASK, 0, &newact.sa_mask);
	pkey_निश्चित(rs == 0);

	/* call sa_sigaction, not sa_handler*/
	newact.sa_flags = SA_SIGINFO;

	newact.sa_restorer = 0;  /* व्योम(*)(), obsolete */
	r = sigaction(signum, &newact, &oldact);
	r = sigaction(SIGALRM, &newact, &oldact);
	pkey_निश्चित(r == 0);
पूर्ण

व्योम setup_handlers(व्योम)
अणु
	संकेत(SIGCHLD, &sig_chld);
	setup_sigsegv_handler();
पूर्ण

pid_t विभाजन_lazy_child(व्योम)
अणु
	pid_t विभाजनret;

	विभाजनret = विभाजन();
	pkey_निश्चित(विभाजनret >= 0);
	dम_लिखो3("[%d] fork() ret: %d\n", getpid(), विभाजनret);

	अगर (!विभाजनret) अणु
		/* in the child */
		जबतक (1) अणु
			dम_लिखो1("child sleeping...\n");
			sleep(30);
		पूर्ण
	पूर्ण
	वापस विभाजनret;
पूर्ण

पूर्णांक sys_mprotect_pkey(व्योम *ptr, माप_प्रकार size, अचिन्हित दीर्घ orig_prot,
		अचिन्हित दीर्घ pkey)
अणु
	पूर्णांक sret;

	dम_लिखो2("%s(0x%p, %zx, prot=%lx, pkey=%lx)\n", __func__,
			ptr, size, orig_prot, pkey);

	त्रुटि_सं = 0;
	sret = syscall(SYS_mprotect_key, ptr, size, orig_prot, pkey);
	अगर (त्रुटि_सं) अणु
		dम_लिखो2("SYS_mprotect_key sret: %d\n", sret);
		dम_लिखो2("SYS_mprotect_key prot: 0x%lx\n", orig_prot);
		dम_लिखो2("SYS_mprotect_key failed, errno: %d\n", त्रुटि_सं);
		अगर (DEBUG_LEVEL >= 2)
			लिखो_त्रुटि("SYS_mprotect_pkey");
	पूर्ण
	वापस sret;
पूर्ण

पूर्णांक sys_pkey_alloc(अचिन्हित दीर्घ flags, अचिन्हित दीर्घ init_val)
अणु
	पूर्णांक ret = syscall(SYS_pkey_alloc, flags, init_val);
	dम_लिखो1("%s(flags=%lx, init_val=%lx) syscall ret: %d errno: %d\n",
			__func__, flags, init_val, ret, त्रुटि_सं);
	वापस ret;
पूर्ण

पूर्णांक alloc_pkey(व्योम)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ init_val = 0x0;

	dम_लिखो1("%s()::%d, pkey_reg: 0x%016llx shadow: %016llx\n",
			__func__, __LINE__, __पढ़ो_pkey_reg(), shaकरोw_pkey_reg);
	ret = sys_pkey_alloc(0, init_val);
	/*
	 * pkey_alloc() sets PKEY रेजिस्टर, so we need to reflect it in
	 * shaकरोw_pkey_reg:
	 */
	dम_लिखो4("%s()::%d, ret: %d pkey_reg: 0x%016llx"
			" shadow: 0x%016llx\n",
			__func__, __LINE__, ret, __पढ़ो_pkey_reg(),
			shaकरोw_pkey_reg);
	अगर (ret) अणु
		/* clear both the bits: */
		shaकरोw_pkey_reg = set_pkey_bits(shaकरोw_pkey_reg, ret,
						~PKEY_MASK);
		dम_लिखो4("%s()::%d, ret: %d pkey_reg: 0x%016llx"
				" shadow: 0x%016llx\n",
				__func__,
				__LINE__, ret, __पढ़ो_pkey_reg(),
				shaकरोw_pkey_reg);
		/*
		 * move the new state in from init_val
		 * (remember, we cheated and init_val == pkey_reg क्रमmat)
		 */
		shaकरोw_pkey_reg = set_pkey_bits(shaकरोw_pkey_reg, ret,
						init_val);
	पूर्ण
	dम_लिखो4("%s()::%d, ret: %d pkey_reg: 0x%016llx"
			" shadow: 0x%016llx\n",
			__func__, __LINE__, ret, __पढ़ो_pkey_reg(),
			shaकरोw_pkey_reg);
	dम_लिखो1("%s()::%d errno: %d\n", __func__, __LINE__, त्रुटि_सं);
	/* क्रम shaकरोw checking: */
	पढ़ो_pkey_reg();
	dम_लिखो4("%s()::%d, ret: %d pkey_reg: 0x%016llx"
		 " shadow: 0x%016llx\n",
		__func__, __LINE__, ret, __पढ़ो_pkey_reg(),
		shaकरोw_pkey_reg);
	वापस ret;
पूर्ण

पूर्णांक sys_pkey_मुक्त(अचिन्हित दीर्घ pkey)
अणु
	पूर्णांक ret = syscall(SYS_pkey_मुक्त, pkey);
	dम_लिखो1("%s(pkey=%ld) syscall ret: %d\n", __func__, pkey, ret);
	वापस ret;
पूर्ण

/*
 * I had a bug where pkey bits could be set by mprotect() but
 * not cleared.  This ensures we get lots of अक्रमom bit sets
 * and clears on the vma and pte pkey bits.
 */
पूर्णांक alloc_अक्रमom_pkey(व्योम)
अणु
	पूर्णांक max_nr_pkey_allocs;
	पूर्णांक ret;
	पूर्णांक i;
	पूर्णांक alloced_pkeys[NR_PKEYS];
	पूर्णांक nr_alloced = 0;
	पूर्णांक अक्रमom_index;
	स_रखो(alloced_pkeys, 0, माप(alloced_pkeys));
	बेक्रम((अचिन्हित पूर्णांक)समय(शून्य));

	/* allocate every possible key and make a note of which ones we got */
	max_nr_pkey_allocs = NR_PKEYS;
	क्रम (i = 0; i < max_nr_pkey_allocs; i++) अणु
		पूर्णांक new_pkey = alloc_pkey();
		अगर (new_pkey < 0)
			अवरोध;
		alloced_pkeys[nr_alloced++] = new_pkey;
	पूर्ण

	pkey_निश्चित(nr_alloced > 0);
	/* select a अक्रमom one out of the allocated ones */
	अक्रमom_index = अक्रम() % nr_alloced;
	ret = alloced_pkeys[अक्रमom_index];
	/* now zero it out so we करोn't मुक्त it next */
	alloced_pkeys[अक्रमom_index] = 0;

	/* go through the allocated ones that we did not want and मुक्त them */
	क्रम (i = 0; i < nr_alloced; i++) अणु
		पूर्णांक मुक्त_ret;
		अगर (!alloced_pkeys[i])
			जारी;
		मुक्त_ret = sys_pkey_मुक्त(alloced_pkeys[i]);
		pkey_निश्चित(!मुक्त_ret);
	पूर्ण
	dम_लिखो1("%s()::%d, ret: %d pkey_reg: 0x%016llx"
			 " shadow: 0x%016llx\n", __func__,
			__LINE__, ret, __पढ़ो_pkey_reg(), shaकरोw_pkey_reg);
	वापस ret;
पूर्ण

पूर्णांक mprotect_pkey(व्योम *ptr, माप_प्रकार size, अचिन्हित दीर्घ orig_prot,
		अचिन्हित दीर्घ pkey)
अणु
	पूर्णांक nr_iterations = अक्रमom() % 100;
	पूर्णांक ret;

	जबतक (0) अणु
		पूर्णांक rpkey = alloc_अक्रमom_pkey();
		ret = sys_mprotect_pkey(ptr, size, orig_prot, pkey);
		dम_लिखो1("sys_mprotect_pkey(%p, %zx, prot=0x%lx, pkey=%ld) ret: %d\n",
				ptr, size, orig_prot, pkey, ret);
		अगर (nr_iterations-- < 0)
			अवरोध;

		dम_लिखो1("%s()::%d, ret: %d pkey_reg: 0x%016llx"
			" shadow: 0x%016llx\n",
			__func__, __LINE__, ret, __पढ़ो_pkey_reg(),
			shaकरोw_pkey_reg);
		sys_pkey_मुक्त(rpkey);
		dम_लिखो1("%s()::%d, ret: %d pkey_reg: 0x%016llx"
			" shadow: 0x%016llx\n",
			__func__, __LINE__, ret, __पढ़ो_pkey_reg(),
			shaकरोw_pkey_reg);
	पूर्ण
	pkey_निश्चित(pkey < NR_PKEYS);

	ret = sys_mprotect_pkey(ptr, size, orig_prot, pkey);
	dम_लिखो1("mprotect_pkey(%p, %zx, prot=0x%lx, pkey=%ld) ret: %d\n",
			ptr, size, orig_prot, pkey, ret);
	pkey_निश्चित(!ret);
	dम_लिखो1("%s()::%d, ret: %d pkey_reg: 0x%016llx"
			" shadow: 0x%016llx\n", __func__,
			__LINE__, ret, __पढ़ो_pkey_reg(), shaकरोw_pkey_reg);
	वापस ret;
पूर्ण

काष्ठा pkey_दो_स्मृति_record अणु
	व्योम *ptr;
	दीर्घ size;
	पूर्णांक prot;
पूर्ण;
काष्ठा pkey_दो_स्मृति_record *pkey_दो_स्मृति_records;
काष्ठा pkey_दो_स्मृति_record *pkey_last_दो_स्मृति_record;
दीर्घ nr_pkey_दो_स्मृति_records;
व्योम record_pkey_दो_स्मृति(व्योम *ptr, दीर्घ size, पूर्णांक prot)
अणु
	दीर्घ i;
	काष्ठा pkey_दो_स्मृति_record *rec = शून्य;

	क्रम (i = 0; i < nr_pkey_दो_स्मृति_records; i++) अणु
		rec = &pkey_दो_स्मृति_records[i];
		/* find a मुक्त record */
		अगर (rec)
			अवरोध;
	पूर्ण
	अगर (!rec) अणु
		/* every record is full */
		माप_प्रकार old_nr_records = nr_pkey_दो_स्मृति_records;
		माप_प्रकार new_nr_records = (nr_pkey_दो_स्मृति_records * 2 + 1);
		माप_प्रकार new_size = new_nr_records * माप(काष्ठा pkey_दो_स्मृति_record);
		dम_लिखो2("new_nr_records: %zd\n", new_nr_records);
		dम_लिखो2("new_size: %zd\n", new_size);
		pkey_दो_स्मृति_records = पुनः_स्मृति(pkey_दो_स्मृति_records, new_size);
		pkey_निश्चित(pkey_दो_स्मृति_records != शून्य);
		rec = &pkey_दो_स्मृति_records[nr_pkey_दो_स्मृति_records];
		/*
		 * पुनः_स्मृति() करोes not initialize memory, so zero it from
		 * the first new record all the way to the end.
		 */
		क्रम (i = 0; i < new_nr_records - old_nr_records; i++)
			स_रखो(rec + i, 0, माप(*rec));
	पूर्ण
	dम_लिखो3("filling malloc record[%d/%p]: {%p, %ld}\n",
		(पूर्णांक)(rec - pkey_दो_स्मृति_records), rec, ptr, size);
	rec->ptr = ptr;
	rec->size = size;
	rec->prot = prot;
	pkey_last_दो_स्मृति_record = rec;
	nr_pkey_दो_स्मृति_records++;
पूर्ण

व्योम मुक्त_pkey_दो_स्मृति(व्योम *ptr)
अणु
	दीर्घ i;
	पूर्णांक ret;
	dम_लिखो3("%s(%p)\n", __func__, ptr);
	क्रम (i = 0; i < nr_pkey_दो_स्मृति_records; i++) अणु
		काष्ठा pkey_दो_स्मृति_record *rec = &pkey_दो_स्मृति_records[i];
		dम_लिखो4("looking for ptr %p at record[%ld/%p]: {%p, %ld}\n",
				ptr, i, rec, rec->ptr, rec->size);
		अगर ((ptr <  rec->ptr) ||
		    (ptr >= rec->ptr + rec->size))
			जारी;

		dम_लिखो3("found ptr %p at record[%ld/%p]: {%p, %ld}\n",
				ptr, i, rec, rec->ptr, rec->size);
		nr_pkey_दो_स्मृति_records--;
		ret = munmap(rec->ptr, rec->size);
		dम_लिखो3("munmap ret: %d\n", ret);
		pkey_निश्चित(!ret);
		dम_लिखो3("clearing rec->ptr, rec: %p\n", rec);
		rec->ptr = शून्य;
		dम_लिखो3("done clearing rec->ptr, rec: %p\n", rec);
		वापस;
	पूर्ण
	pkey_निश्चित(false);
पूर्ण


व्योम *दो_स्मृति_pkey_with_mprotect(दीर्घ size, पूर्णांक prot, u16 pkey)
अणु
	व्योम *ptr;
	पूर्णांक ret;

	पढ़ो_pkey_reg();
	dम_लिखो1("doing %s(size=%ld, prot=0x%x, pkey=%d)\n", __func__,
			size, prot, pkey);
	pkey_निश्चित(pkey < NR_PKEYS);
	ptr = mmap(शून्य, size, prot, MAP_ANONYMOUS|MAP_PRIVATE, -1, 0);
	pkey_निश्चित(ptr != (व्योम *)-1);
	ret = mprotect_pkey((व्योम *)ptr, PAGE_SIZE, prot, pkey);
	pkey_निश्चित(!ret);
	record_pkey_दो_स्मृति(ptr, size, prot);
	पढ़ो_pkey_reg();

	dम_लिखो1("%s() for pkey %d @ %p\n", __func__, pkey, ptr);
	वापस ptr;
पूर्ण

व्योम *दो_स्मृति_pkey_anon_huge(दीर्घ size, पूर्णांक prot, u16 pkey)
अणु
	पूर्णांक ret;
	व्योम *ptr;

	dम_लिखो1("doing %s(size=%ld, prot=0x%x, pkey=%d)\n", __func__,
			size, prot, pkey);
	/*
	 * Guarantee we can fit at least one huge page in the resulting
	 * allocation by allocating space क्रम 2:
	 */
	size = ALIGN_UP(size, HPAGE_SIZE * 2);
	ptr = mmap(शून्य, size, PROT_NONE, MAP_ANONYMOUS|MAP_PRIVATE, -1, 0);
	pkey_निश्चित(ptr != (व्योम *)-1);
	record_pkey_दो_स्मृति(ptr, size, prot);
	mprotect_pkey(ptr, size, prot, pkey);

	dम_लिखो1("unaligned ptr: %p\n", ptr);
	ptr = ALIGN_PTR_UP(ptr, HPAGE_SIZE);
	dम_लिखो1("  aligned ptr: %p\n", ptr);
	ret = madvise(ptr, HPAGE_SIZE, MADV_HUGEPAGE);
	dम_लिखो1("MADV_HUGEPAGE ret: %d\n", ret);
	ret = madvise(ptr, HPAGE_SIZE, MADV_WILLNEED);
	dम_लिखो1("MADV_WILLNEED ret: %d\n", ret);
	स_रखो(ptr, 0, HPAGE_SIZE);

	dम_लिखो1("mmap()'d thp for pkey %d @ %p\n", pkey, ptr);
	वापस ptr;
पूर्ण

पूर्णांक hugetlb_setup_ok;
#घोषणा SYSFS_FMT_NR_HUGE_PAGES "/sys/kernel/mm/hugepages/hugepages-%ldkB/nr_hugepages"
#घोषणा GET_NR_HUGE_PAGES 10
व्योम setup_hugetlbfs(व्योम)
अणु
	पूर्णांक err;
	पूर्णांक fd;
	अक्षर buf[256];
	दीर्घ hpagesz_kb;
	दीर्घ hpagesz_mb;

	अगर (geteuid() != 0) अणु
		ख_लिखो(मानक_त्रुटि, "WARNING: not run as root, can not do hugetlb test\n");
		वापस;
	पूर्ण

	cat_पूर्णांकo_file(__stringअगरy(GET_NR_HUGE_PAGES), "/proc/sys/vm/nr_hugepages");

	/*
	 * Now go make sure that we got the pages and that they
	 * are PMD-level pages. Someone might have made PUD-level
	 * pages the शेष.
	 */
	hpagesz_kb = HPAGE_SIZE / 1024;
	hpagesz_mb = hpagesz_kb / 1024;
	प्र_लिखो(buf, SYSFS_FMT_NR_HUGE_PAGES, hpagesz_kb);
	fd = खोलो(buf, O_RDONLY);
	अगर (fd < 0) अणु
		ख_लिखो(मानक_त्रुटि, "opening sysfs %ldM hugetlb config: %s\n",
			hpagesz_mb, म_त्रुटि(त्रुटि_सं));
		वापस;
	पूर्ण

	/* -1 to guarantee leaving the trailing \0 */
	err = पढ़ो(fd, buf, माप(buf)-1);
	बंद(fd);
	अगर (err <= 0) अणु
		ख_लिखो(मानक_त्रुटि, "reading sysfs %ldM hugetlb config: %s\n",
			hpagesz_mb, म_त्रुटि(त्रुटि_सं));
		वापस;
	पूर्ण

	अगर (म_से_प(buf) != GET_NR_HUGE_PAGES) अणु
		ख_लिखो(मानक_त्रुटि, "could not confirm %ldM pages, got: '%s' expected %d\n",
			hpagesz_mb, buf, GET_NR_HUGE_PAGES);
		वापस;
	पूर्ण

	hugetlb_setup_ok = 1;
पूर्ण

व्योम *दो_स्मृति_pkey_hugetlb(दीर्घ size, पूर्णांक prot, u16 pkey)
अणु
	व्योम *ptr;
	पूर्णांक flags = MAP_ANONYMOUS|MAP_PRIVATE|MAP_HUGETLB;

	अगर (!hugetlb_setup_ok)
		वापस PTR_ERR_ENOTSUP;

	dम_लिखो1("doing %s(%ld, %x, %x)\n", __func__, size, prot, pkey);
	size = ALIGN_UP(size, HPAGE_SIZE * 2);
	pkey_निश्चित(pkey < NR_PKEYS);
	ptr = mmap(शून्य, size, PROT_NONE, flags, -1, 0);
	pkey_निश्चित(ptr != (व्योम *)-1);
	mprotect_pkey(ptr, size, prot, pkey);

	record_pkey_दो_स्मृति(ptr, size, prot);

	dम_लिखो1("mmap()'d hugetlbfs for pkey %d @ %p\n", pkey, ptr);
	वापस ptr;
पूर्ण

व्योम *दो_स्मृति_pkey_mmap_dax(दीर्घ size, पूर्णांक prot, u16 pkey)
अणु
	व्योम *ptr;
	पूर्णांक fd;

	dम_लिखो1("doing %s(size=%ld, prot=0x%x, pkey=%d)\n", __func__,
			size, prot, pkey);
	pkey_निश्चित(pkey < NR_PKEYS);
	fd = खोलो("/dax/foo", O_RDWR);
	pkey_निश्चित(fd >= 0);

	ptr = mmap(0, size, prot, MAP_SHARED, fd, 0);
	pkey_निश्चित(ptr != (व्योम *)-1);

	mprotect_pkey(ptr, size, prot, pkey);

	record_pkey_दो_स्मृति(ptr, size, prot);

	dम_लिखो1("mmap()'d for pkey %d @ %p\n", pkey, ptr);
	बंद(fd);
	वापस ptr;
पूर्ण

व्योम *(*pkey_दो_स्मृति[])(दीर्घ size, पूर्णांक prot, u16 pkey) = अणु

	दो_स्मृति_pkey_with_mprotect,
	दो_स्मृति_pkey_with_mprotect_subpage,
	दो_स्मृति_pkey_anon_huge,
	दो_स्मृति_pkey_hugetlb
/* can not करो direct with the pkey_mprotect() API:
	दो_स्मृति_pkey_mmap_direct,
	दो_स्मृति_pkey_mmap_dax,
*/
पूर्ण;

व्योम *दो_स्मृति_pkey(दीर्घ size, पूर्णांक prot, u16 pkey)
अणु
	व्योम *ret;
	अटल पूर्णांक दो_स्मृति_type;
	पूर्णांक nr_दो_स्मृति_types = ARRAY_SIZE(pkey_दो_स्मृति);

	pkey_निश्चित(pkey < NR_PKEYS);

	जबतक (1) अणु
		pkey_निश्चित(दो_स्मृति_type < nr_दो_स्मृति_types);

		ret = pkey_दो_स्मृति[दो_स्मृति_type](size, prot, pkey);
		pkey_निश्चित(ret != (व्योम *)-1);

		दो_स्मृति_type++;
		अगर (दो_स्मृति_type >= nr_दो_स्मृति_types)
			दो_स्मृति_type = (अक्रमom()%nr_दो_स्मृति_types);

		/* try again अगर the दो_स्मृति_type we tried is unsupported */
		अगर (ret == PTR_ERR_ENOTSUP)
			जारी;

		अवरोध;
	पूर्ण

	dम_लिखो3("%s(%ld, prot=%x, pkey=%x) returning: %p\n", __func__,
			size, prot, pkey, ret);
	वापस ret;
पूर्ण

पूर्णांक last_pkey_faults;
#घोषणा UNKNOWN_PKEY -2
व्योम expected_pkey_fault(पूर्णांक pkey)
अणु
	dम_लिखो2("%s(): last_pkey_faults: %d pkey_faults: %d\n",
			__func__, last_pkey_faults, pkey_faults);
	dम_लिखो2("%s(%d): last_si_pkey: %d\n", __func__, pkey, last_si_pkey);
	pkey_निश्चित(last_pkey_faults + 1 == pkey_faults);

       /*
	* For exec-only memory, we करो not know the pkey in
	* advance, so skip this check.
	*/
	अगर (pkey != UNKNOWN_PKEY)
		pkey_निश्चित(last_si_pkey == pkey);

#अगर defined(__i386__) || defined(__x86_64__) /* arch */
	/*
	 * The संकेत handler shold have cleared out PKEY रेजिस्टर to let the
	 * test program जारी.  We now have to restore it.
	 */
	अगर (__पढ़ो_pkey_reg() != 0)
#अन्यथा /* arch */
	अगर (__पढ़ो_pkey_reg() != shaकरोw_pkey_reg)
#पूर्ण_अगर /* arch */
		pkey_निश्चित(0);

	__ग_लिखो_pkey_reg(shaकरोw_pkey_reg);
	dम_लिखो1("%s() set pkey_reg=%016llx to restore state after signal "
		       "nuked it\n", __func__, shaकरोw_pkey_reg);
	last_pkey_faults = pkey_faults;
	last_si_pkey = -1;
पूर्ण

#घोषणा करो_not_expect_pkey_fault(msg)	करो अणु			\
	अगर (last_pkey_faults != pkey_faults)			\
		dम_लिखो0("unexpected PKey fault: %s\n", msg);	\
	pkey_निश्चित(last_pkey_faults == pkey_faults);		\
पूर्ण जबतक (0)

पूर्णांक test_fds[10] = अणु -1 पूर्ण;
पूर्णांक nr_test_fds;
व्योम __save_test_fd(पूर्णांक fd)
अणु
	pkey_निश्चित(fd >= 0);
	pkey_निश्चित(nr_test_fds < ARRAY_SIZE(test_fds));
	test_fds[nr_test_fds] = fd;
	nr_test_fds++;
पूर्ण

पूर्णांक get_test_पढ़ो_fd(व्योम)
अणु
	पूर्णांक test_fd = खोलो("/etc/passwd", O_RDONLY);
	__save_test_fd(test_fd);
	वापस test_fd;
पूर्ण

व्योम बंद_test_fds(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nr_test_fds; i++) अणु
		अगर (test_fds[i] < 0)
			जारी;
		बंद(test_fds[i]);
		test_fds[i] = -1;
	पूर्ण
	nr_test_fds = 0;
पूर्ण

#घोषणा barrier() __यंत्र__ __अस्थिर__("": : :"memory")
__attribute__((noअंतरभूत)) पूर्णांक पढ़ो_ptr(पूर्णांक *ptr)
अणु
	/*
	 * Keep GCC from optimizing this away somehow
	 */
	barrier();
	वापस *ptr;
पूर्ण

व्योम test_pkey_alloc_मुक्त_attach_pkey0(पूर्णांक *ptr, u16 pkey)
अणु
	पूर्णांक i, err;
	पूर्णांक max_nr_pkey_allocs;
	पूर्णांक alloced_pkeys[NR_PKEYS];
	पूर्णांक nr_alloced = 0;
	दीर्घ size;

	pkey_निश्चित(pkey_last_दो_स्मृति_record);
	size = pkey_last_दो_स्मृति_record->size;
	/*
	 * This is a bit of a hack.  But mprotect() requires
	 * huge-page-aligned sizes when operating on hugetlbfs.
	 * So, make sure that we use something that's a multiple
	 * of a huge page when we can.
	 */
	अगर (size >= HPAGE_SIZE)
		size = HPAGE_SIZE;

	/* allocate every possible key and make sure key-0 never got allocated */
	max_nr_pkey_allocs = NR_PKEYS;
	क्रम (i = 0; i < max_nr_pkey_allocs; i++) अणु
		पूर्णांक new_pkey = alloc_pkey();
		pkey_निश्चित(new_pkey != 0);

		अगर (new_pkey < 0)
			अवरोध;
		alloced_pkeys[nr_alloced++] = new_pkey;
	पूर्ण
	/* मुक्त all the allocated keys */
	क्रम (i = 0; i < nr_alloced; i++) अणु
		पूर्णांक मुक्त_ret;

		अगर (!alloced_pkeys[i])
			जारी;
		मुक्त_ret = sys_pkey_मुक्त(alloced_pkeys[i]);
		pkey_निश्चित(!मुक्त_ret);
	पूर्ण

	/* attach key-0 in various modes */
	err = sys_mprotect_pkey(ptr, size, PROT_READ, 0);
	pkey_निश्चित(!err);
	err = sys_mprotect_pkey(ptr, size, PROT_WRITE, 0);
	pkey_निश्चित(!err);
	err = sys_mprotect_pkey(ptr, size, PROT_EXEC, 0);
	pkey_निश्चित(!err);
	err = sys_mprotect_pkey(ptr, size, PROT_READ|PROT_WRITE, 0);
	pkey_निश्चित(!err);
	err = sys_mprotect_pkey(ptr, size, PROT_READ|PROT_WRITE|PROT_EXEC, 0);
	pkey_निश्चित(!err);
पूर्ण

व्योम test_पढ़ो_of_ग_लिखो_disabled_region(पूर्णांक *ptr, u16 pkey)
अणु
	पूर्णांक ptr_contents;

	dम_लिखो1("disabling write access to PKEY[1], doing read\n");
	pkey_ग_लिखो_deny(pkey);
	ptr_contents = पढ़ो_ptr(ptr);
	dम_लिखो1("*ptr: %d\n", ptr_contents);
	dम_लिखो1("\n");
पूर्ण
व्योम test_पढ़ो_of_access_disabled_region(पूर्णांक *ptr, u16 pkey)
अणु
	पूर्णांक ptr_contents;

	dम_लिखो1("disabling access to PKEY[%02d], doing read @ %p\n", pkey, ptr);
	पढ़ो_pkey_reg();
	pkey_access_deny(pkey);
	ptr_contents = पढ़ो_ptr(ptr);
	dम_लिखो1("*ptr: %d\n", ptr_contents);
	expected_pkey_fault(pkey);
पूर्ण

व्योम test_पढ़ो_of_access_disabled_region_with_page_alपढ़ोy_mapped(पूर्णांक *ptr,
		u16 pkey)
अणु
	पूर्णांक ptr_contents;

	dम_लिखो1("disabling access to PKEY[%02d], doing read @ %p\n",
				pkey, ptr);
	ptr_contents = पढ़ो_ptr(ptr);
	dम_लिखो1("reading ptr before disabling the read : %d\n",
			ptr_contents);
	पढ़ो_pkey_reg();
	pkey_access_deny(pkey);
	ptr_contents = पढ़ो_ptr(ptr);
	dम_लिखो1("*ptr: %d\n", ptr_contents);
	expected_pkey_fault(pkey);
पूर्ण

व्योम test_ग_लिखो_of_ग_लिखो_disabled_region_with_page_alपढ़ोy_mapped(पूर्णांक *ptr,
		u16 pkey)
अणु
	*ptr = __LINE__;
	dम_लिखो1("disabling write access; after accessing the page, "
		"to PKEY[%02d], doing write\n", pkey);
	pkey_ग_लिखो_deny(pkey);
	*ptr = __LINE__;
	expected_pkey_fault(pkey);
पूर्ण

व्योम test_ग_लिखो_of_ग_लिखो_disabled_region(पूर्णांक *ptr, u16 pkey)
अणु
	dम_लिखो1("disabling write access to PKEY[%02d], doing write\n", pkey);
	pkey_ग_लिखो_deny(pkey);
	*ptr = __LINE__;
	expected_pkey_fault(pkey);
पूर्ण
व्योम test_ग_लिखो_of_access_disabled_region(पूर्णांक *ptr, u16 pkey)
अणु
	dम_लिखो1("disabling access to PKEY[%02d], doing write\n", pkey);
	pkey_access_deny(pkey);
	*ptr = __LINE__;
	expected_pkey_fault(pkey);
पूर्ण

व्योम test_ग_लिखो_of_access_disabled_region_with_page_alपढ़ोy_mapped(पूर्णांक *ptr,
			u16 pkey)
अणु
	*ptr = __LINE__;
	dम_लिखो1("disabling access; after accessing the page, "
		" to PKEY[%02d], doing write\n", pkey);
	pkey_access_deny(pkey);
	*ptr = __LINE__;
	expected_pkey_fault(pkey);
पूर्ण

व्योम test_kernel_ग_लिखो_of_access_disabled_region(पूर्णांक *ptr, u16 pkey)
अणु
	पूर्णांक ret;
	पूर्णांक test_fd = get_test_पढ़ो_fd();

	dम_लिखो1("disabling access to PKEY[%02d], "
		 "having kernel read() to buffer\n", pkey);
	pkey_access_deny(pkey);
	ret = पढ़ो(test_fd, ptr, 1);
	dम_लिखो1("read ret: %d\n", ret);
	pkey_निश्चित(ret);
पूर्ण
व्योम test_kernel_ग_लिखो_of_ग_लिखो_disabled_region(पूर्णांक *ptr, u16 pkey)
अणु
	पूर्णांक ret;
	पूर्णांक test_fd = get_test_पढ़ो_fd();

	pkey_ग_लिखो_deny(pkey);
	ret = पढ़ो(test_fd, ptr, 100);
	dम_लिखो1("read ret: %d\n", ret);
	अगर (ret < 0 && (DEBUG_LEVEL > 0))
		लिखो_त्रुटि("verbose read result (OK for this to be bad)");
	pkey_निश्चित(ret);
पूर्ण

व्योम test_kernel_gup_of_access_disabled_region(पूर्णांक *ptr, u16 pkey)
अणु
	पूर्णांक pipe_ret, vmsplice_ret;
	काष्ठा iovec iov;
	पूर्णांक pipe_fds[2];

	pipe_ret = pipe(pipe_fds);

	pkey_निश्चित(pipe_ret == 0);
	dम_लिखो1("disabling access to PKEY[%02d], "
		 "having kernel vmsplice from buffer\n", pkey);
	pkey_access_deny(pkey);
	iov.iov_base = ptr;
	iov.iov_len = PAGE_SIZE;
	vmsplice_ret = vmsplice(pipe_fds[1], &iov, 1, SPLICE_F_GIFT);
	dम_लिखो1("vmsplice() ret: %d\n", vmsplice_ret);
	pkey_निश्चित(vmsplice_ret == -1);

	बंद(pipe_fds[0]);
	बंद(pipe_fds[1]);
पूर्ण

व्योम test_kernel_gup_ग_लिखो_to_ग_लिखो_disabled_region(पूर्णांक *ptr, u16 pkey)
अणु
	पूर्णांक ignored = 0xdada;
	पूर्णांक futex_ret;
	पूर्णांक some_पूर्णांक = __LINE__;

	dम_लिखो1("disabling write to PKEY[%02d], "
		 "doing futex gunk in buffer\n", pkey);
	*ptr = some_पूर्णांक;
	pkey_ग_लिखो_deny(pkey);
	futex_ret = syscall(SYS_futex, ptr, FUTEX_WAIT, some_पूर्णांक-1, शून्य,
			&ignored, ignored);
	अगर (DEBUG_LEVEL > 0)
		लिखो_त्रुटि("futex");
	dम_लिखो1("futex() ret: %d\n", futex_ret);
पूर्ण

/* Assumes that all pkeys other than 'pkey' are unallocated */
व्योम test_pkey_syscalls_on_non_allocated_pkey(पूर्णांक *ptr, u16 pkey)
अणु
	पूर्णांक err;
	पूर्णांक i;

	/* Note: 0 is the शेष pkey, so करोn't mess with it */
	क्रम (i = 1; i < NR_PKEYS; i++) अणु
		अगर (pkey == i)
			जारी;

		dम_लिखो1("trying get/set/free to non-allocated pkey: %2d\n", i);
		err = sys_pkey_मुक्त(i);
		pkey_निश्चित(err);

		err = sys_pkey_मुक्त(i);
		pkey_निश्चित(err);

		err = sys_mprotect_pkey(ptr, PAGE_SIZE, PROT_READ, i);
		pkey_निश्चित(err);
	पूर्ण
पूर्ण

/* Assumes that all pkeys other than 'pkey' are unallocated */
व्योम test_pkey_syscalls_bad_args(पूर्णांक *ptr, u16 pkey)
अणु
	पूर्णांक err;
	पूर्णांक bad_pkey = NR_PKEYS+99;

	/* pass a known-invalid pkey in: */
	err = sys_mprotect_pkey(ptr, PAGE_SIZE, PROT_READ, bad_pkey);
	pkey_निश्चित(err);
पूर्ण

व्योम become_child(व्योम)
अणु
	pid_t विभाजनret;

	विभाजनret = विभाजन();
	pkey_निश्चित(विभाजनret >= 0);
	dम_लिखो3("[%d] fork() ret: %d\n", getpid(), विभाजनret);

	अगर (!विभाजनret) अणु
		/* in the child */
		वापस;
	पूर्ण
	निकास(0);
पूर्ण

/* Assumes that all pkeys other than 'pkey' are unallocated */
व्योम test_pkey_alloc_exhaust(पूर्णांक *ptr, u16 pkey)
अणु
	पूर्णांक err;
	पूर्णांक allocated_pkeys[NR_PKEYS] = अणु0पूर्ण;
	पूर्णांक nr_allocated_pkeys = 0;
	पूर्णांक i;

	क्रम (i = 0; i < NR_PKEYS*3; i++) अणु
		पूर्णांक new_pkey;
		dम_लिखो1("%s() alloc loop: %d\n", __func__, i);
		new_pkey = alloc_pkey();
		dम_लिखो4("%s()::%d, err: %d pkey_reg: 0x%016llx"
				" shadow: 0x%016llx\n",
				__func__, __LINE__, err, __पढ़ो_pkey_reg(),
				shaकरोw_pkey_reg);
		पढ़ो_pkey_reg(); /* क्रम shaकरोw checking */
		dम_लिखो2("%s() errno: %d ENOSPC: %d\n", __func__, त्रुटि_सं, ENOSPC);
		अगर ((new_pkey == -1) && (त्रुटि_सं == ENOSPC)) अणु
			dम_लिखो2("%s() failed to allocate pkey after %d tries\n",
				__func__, nr_allocated_pkeys);
		पूर्ण अन्यथा अणु
			/*
			 * Ensure the number of successes never
			 * exceeds the number of keys supported
			 * in the hardware.
			 */
			pkey_निश्चित(nr_allocated_pkeys < NR_PKEYS);
			allocated_pkeys[nr_allocated_pkeys++] = new_pkey;
		पूर्ण

		/*
		 * Make sure that allocation state is properly
		 * preserved across विभाजन().
		 */
		अगर (i == NR_PKEYS*2)
			become_child();
	पूर्ण

	dम_लिखो3("%s()::%d\n", __func__, __LINE__);

	/*
	 * On x86:
	 * There are 16 pkeys supported in hardware.  Three are
	 * allocated by the समय we get here:
	 *   1. The शेष key (0)
	 *   2. One possibly consumed by an execute-only mapping.
	 *   3. One allocated by the test code and passed in via
	 *      'pkey' to this function.
	 * Ensure that we can allocate at least another 13 (16-3).
	 *
	 * On घातerpc:
	 * There are either 5, 28, 29 or 32 pkeys supported in
	 * hardware depending on the page size (4K or 64K) and
	 * platक्रमm (घातernv or घातervm). Four are allocated by
	 * the समय we get here. These include pkey-0, pkey-1,
	 * exec-only pkey and the one allocated by the test code.
	 * Ensure that we can allocate the reमुख्यing.
	 */
	pkey_निश्चित(i >= (NR_PKEYS - get_arch_reserved_keys() - 1));

	क्रम (i = 0; i < nr_allocated_pkeys; i++) अणु
		err = sys_pkey_मुक्त(allocated_pkeys[i]);
		pkey_निश्चित(!err);
		पढ़ो_pkey_reg(); /* क्रम shaकरोw checking */
	पूर्ण
पूर्ण

/*
 * pkey 0 is special.  It is allocated by शेष, so you करो not
 * have to call pkey_alloc() to use it first.  Make sure that it
 * is usable.
 */
व्योम test_mprotect_with_pkey_0(पूर्णांक *ptr, u16 pkey)
अणु
	दीर्घ size;
	पूर्णांक prot;

	निश्चित(pkey_last_दो_स्मृति_record);
	size = pkey_last_दो_स्मृति_record->size;
	/*
	 * This is a bit of a hack.  But mprotect() requires
	 * huge-page-aligned sizes when operating on hugetlbfs.
	 * So, make sure that we use something that's a multiple
	 * of a huge page when we can.
	 */
	अगर (size >= HPAGE_SIZE)
		size = HPAGE_SIZE;
	prot = pkey_last_दो_स्मृति_record->prot;

	/* Use pkey 0 */
	mprotect_pkey(ptr, size, prot, 0);

	/* Make sure that we can set it back to the original pkey. */
	mprotect_pkey(ptr, size, prot, pkey);
पूर्ण

व्योम test_ptrace_of_child(पूर्णांक *ptr, u16 pkey)
अणु
	__attribute__((__unused__)) पूर्णांक peek_result;
	pid_t child_pid;
	व्योम *ignored = 0;
	दीर्घ ret;
	पूर्णांक status;
	/*
	 * This is the "control" क्रम our little expermient.  Make sure
	 * we can always access it when ptracing.
	 */
	पूर्णांक *plain_ptr_unaligned = दो_स्मृति(HPAGE_SIZE);
	पूर्णांक *plain_ptr = ALIGN_PTR_UP(plain_ptr_unaligned, PAGE_SIZE);

	/*
	 * Fork a child which is an exact copy of this process, of course.
	 * That means we can करो all of our tests via ptrace() and then plain
	 * memory access and ensure they work dअगरferently.
	 */
	child_pid = विभाजन_lazy_child();
	dम_लिखो1("[%d] child pid: %d\n", getpid(), child_pid);

	ret = ptrace(PTRACE_ATTACH, child_pid, ignored, ignored);
	अगर (ret)
		लिखो_त्रुटि("attach");
	dम_लिखो1("[%d] attach ret: %ld %d\n", getpid(), ret, __LINE__);
	pkey_निश्चित(ret != -1);
	ret = रुकोpid(child_pid, &status, WUNTRACED);
	अगर ((ret != child_pid) || !(WIFSTOPPED(status))) अणु
		ख_लिखो(मानक_त्रुटि, "weird waitpid result %ld stat %x\n",
				ret, status);
		pkey_निश्चित(0);
	पूर्ण
	dम_लिखो2("waitpid ret: %ld\n", ret);
	dम_लिखो2("waitpid status: %d\n", status);

	pkey_access_deny(pkey);
	pkey_ग_लिखो_deny(pkey);

	/* Write access, untested क्रम now:
	ret = ptrace(PTRACE_POKEDATA, child_pid, peek_at, data);
	pkey_निश्चित(ret != -1);
	dम_लिखो1("poke at %p: %ld\n", peek_at, ret);
	*/

	/*
	 * Try to access the pkey-रक्षित "ptr" via ptrace:
	 */
	ret = ptrace(PTRACE_PEEKDATA, child_pid, ptr, ignored);
	/* expect it to work, without an error: */
	pkey_निश्चित(ret != -1);
	/* Now access from the current task, and expect an exception: */
	peek_result = पढ़ो_ptr(ptr);
	expected_pkey_fault(pkey);

	/*
	 * Try to access the NON-pkey-रक्षित "plain_ptr" via ptrace:
	 */
	ret = ptrace(PTRACE_PEEKDATA, child_pid, plain_ptr, ignored);
	/* expect it to work, without an error: */
	pkey_निश्चित(ret != -1);
	/* Now access from the current task, and expect NO exception: */
	peek_result = पढ़ो_ptr(plain_ptr);
	करो_not_expect_pkey_fault("read plain pointer after ptrace");

	ret = ptrace(PTRACE_DETACH, child_pid, ignored, 0);
	pkey_निश्चित(ret != -1);

	ret = समाप्त(child_pid, SIGKILL);
	pkey_निश्चित(ret != -1);

	रुको(&status);

	मुक्त(plain_ptr_unaligned);
पूर्ण

व्योम *get_poपूर्णांकer_to_inकाष्ठाions(व्योम)
अणु
	व्योम *p1;

	p1 = ALIGN_PTR_UP(&lots_o_noops_around_ग_लिखो, PAGE_SIZE);
	dम_लिखो3("&lots_o_noops: %p\n", &lots_o_noops_around_ग_लिखो);
	/* lots_o_noops_around_ग_लिखो should be page-aligned alपढ़ोy */
	निश्चित(p1 == &lots_o_noops_around_ग_लिखो);

	/* Poपूर्णांक 'p1' at the *second* page of the function: */
	p1 += PAGE_SIZE;

	/*
	 * Try to ensure we fault this in on next touch to ensure
	 * we get an inकाष्ठाion fault as opposed to a data one
	 */
	madvise(p1, PAGE_SIZE, MADV_DONTNEED);

	वापस p1;
पूर्ण

व्योम test_executing_on_unपढ़ोable_memory(पूर्णांक *ptr, u16 pkey)
अणु
	व्योम *p1;
	पूर्णांक scratch;
	पूर्णांक ptr_contents;
	पूर्णांक ret;

	p1 = get_poपूर्णांकer_to_inकाष्ठाions();
	lots_o_noops_around_ग_लिखो(&scratch);
	ptr_contents = पढ़ो_ptr(p1);
	dम_लिखो2("ptr (%p) contents@%d: %x\n", p1, __LINE__, ptr_contents);

	ret = mprotect_pkey(p1, PAGE_SIZE, PROT_EXEC, (u64)pkey);
	pkey_निश्चित(!ret);
	pkey_access_deny(pkey);

	dम_लिखो2("pkey_reg: %016llx\n", पढ़ो_pkey_reg());

	/*
	 * Make sure this is an *inकाष्ठाion* fault
	 */
	madvise(p1, PAGE_SIZE, MADV_DONTNEED);
	lots_o_noops_around_ग_लिखो(&scratch);
	करो_not_expect_pkey_fault("executing on PROT_EXEC memory");
	expect_fault_on_पढ़ो_execonly_key(p1, pkey);
पूर्ण

व्योम test_implicit_mprotect_exec_only_memory(पूर्णांक *ptr, u16 pkey)
अणु
	व्योम *p1;
	पूर्णांक scratch;
	पूर्णांक ptr_contents;
	पूर्णांक ret;

	dम_लिखो1("%s() start\n", __func__);

	p1 = get_poपूर्णांकer_to_inकाष्ठाions();
	lots_o_noops_around_ग_लिखो(&scratch);
	ptr_contents = पढ़ो_ptr(p1);
	dम_लिखो2("ptr (%p) contents@%d: %x\n", p1, __LINE__, ptr_contents);

	/* Use a *normal* mprotect(), not mprotect_pkey(): */
	ret = mprotect(p1, PAGE_SIZE, PROT_EXEC);
	pkey_निश्चित(!ret);

	dम_लिखो2("pkey_reg: %016llx\n", पढ़ो_pkey_reg());

	/* Make sure this is an *inकाष्ठाion* fault */
	madvise(p1, PAGE_SIZE, MADV_DONTNEED);
	lots_o_noops_around_ग_लिखो(&scratch);
	करो_not_expect_pkey_fault("executing on PROT_EXEC memory");
	expect_fault_on_पढ़ो_execonly_key(p1, UNKNOWN_PKEY);

	/*
	 * Put the memory back to non-PROT_EXEC.  Should clear the
	 * exec-only pkey off the VMA and allow it to be पढ़ोable
	 * again.  Go to PROT_NONE first to check क्रम a kernel bug
	 * that did not clear the pkey when करोing PROT_NONE.
	 */
	ret = mprotect(p1, PAGE_SIZE, PROT_NONE);
	pkey_निश्चित(!ret);

	ret = mprotect(p1, PAGE_SIZE, PROT_READ|PROT_EXEC);
	pkey_निश्चित(!ret);
	ptr_contents = पढ़ो_ptr(p1);
	करो_not_expect_pkey_fault("plain read on recently PROT_EXEC area");
पूर्ण

व्योम test_mprotect_pkey_on_unsupported_cpu(पूर्णांक *ptr, u16 pkey)
अणु
	पूर्णांक size = PAGE_SIZE;
	पूर्णांक sret;

	अगर (cpu_has_pkeys()) अणु
		dम_लिखो1("SKIP: %s: no CPU support\n", __func__);
		वापस;
	पूर्ण

	sret = syscall(SYS_mprotect_key, ptr, size, PROT_READ, pkey);
	pkey_निश्चित(sret < 0);
पूर्ण

व्योम (*pkey_tests[])(पूर्णांक *ptr, u16 pkey) = अणु
	test_पढ़ो_of_ग_लिखो_disabled_region,
	test_पढ़ो_of_access_disabled_region,
	test_पढ़ो_of_access_disabled_region_with_page_alपढ़ोy_mapped,
	test_ग_लिखो_of_ग_लिखो_disabled_region,
	test_ग_लिखो_of_ग_लिखो_disabled_region_with_page_alपढ़ोy_mapped,
	test_ग_लिखो_of_access_disabled_region,
	test_ग_लिखो_of_access_disabled_region_with_page_alपढ़ोy_mapped,
	test_kernel_ग_लिखो_of_access_disabled_region,
	test_kernel_ग_लिखो_of_ग_लिखो_disabled_region,
	test_kernel_gup_of_access_disabled_region,
	test_kernel_gup_ग_लिखो_to_ग_लिखो_disabled_region,
	test_executing_on_unपढ़ोable_memory,
	test_implicit_mprotect_exec_only_memory,
	test_mprotect_with_pkey_0,
	test_ptrace_of_child,
	test_pkey_syscalls_on_non_allocated_pkey,
	test_pkey_syscalls_bad_args,
	test_pkey_alloc_exhaust,
	test_pkey_alloc_मुक्त_attach_pkey0,
पूर्ण;

व्योम run_tests_once(व्योम)
अणु
	पूर्णांक *ptr;
	पूर्णांक prot = PROT_READ|PROT_WRITE;

	क्रम (test_nr = 0; test_nr < ARRAY_SIZE(pkey_tests); test_nr++) अणु
		पूर्णांक pkey;
		पूर्णांक orig_pkey_faults = pkey_faults;

		dम_लिखो1("======================\n");
		dम_लिखो1("test %d preparing...\n", test_nr);

		tracing_on();
		pkey = alloc_अक्रमom_pkey();
		dम_लिखो1("test %d starting with pkey: %d\n", test_nr, pkey);
		ptr = दो_स्मृति_pkey(PAGE_SIZE, prot, pkey);
		dम_लिखो1("test %d starting...\n", test_nr);
		pkey_tests[test_nr](ptr, pkey);
		dम_लिखो1("freeing test memory: %p\n", ptr);
		मुक्त_pkey_दो_स्मृति(ptr);
		sys_pkey_मुक्त(pkey);

		dम_लिखो1("pkey_faults: %d\n", pkey_faults);
		dम_लिखो1("orig_pkey_faults: %d\n", orig_pkey_faults);

		tracing_off();
		बंद_test_fds();

		म_लिखो("test %2d PASSED (iteration %d)\n", test_nr, iteration_nr);
		dम_लिखो1("======================\n\n");
	पूर्ण
	iteration_nr++;
पूर्ण

व्योम pkey_setup_shaकरोw(व्योम)
अणु
	shaकरोw_pkey_reg = __पढ़ो_pkey_reg();
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	पूर्णांक nr_iterations = 22;
	पूर्णांक pkeys_supported = is_pkeys_supported();

	setup_handlers();

	म_लिखो("has pkeys: %d\n", pkeys_supported);

	अगर (!pkeys_supported) अणु
		पूर्णांक size = PAGE_SIZE;
		पूर्णांक *ptr;

		म_लिखो("running PKEY tests for unsupported CPU/OS\n");

		ptr  = mmap(शून्य, size, PROT_NONE, MAP_ANONYMOUS|MAP_PRIVATE, -1, 0);
		निश्चित(ptr != (व्योम *)-1);
		test_mprotect_pkey_on_unsupported_cpu(ptr, 1);
		निकास(0);
	पूर्ण

	pkey_setup_shaकरोw();
	म_लिखो("startup pkey_reg: %016llx\n", पढ़ो_pkey_reg());
	setup_hugetlbfs();

	जबतक (nr_iterations-- > 0)
		run_tests_once();

	म_लिखो("done (all tests OK)\n");
	वापस 0;
पूर्ण
