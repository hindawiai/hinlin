<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+

/*
 * Ptrace test क्रम hw अवरोधpoपूर्णांकs
 *
 * Based on tools/testing/selftests/अवरोधpoपूर्णांकs/अवरोधpoपूर्णांक_test.c
 *
 * This test विभाजनs and the parent then traces the child करोing various
 * types of ptrace enabled अवरोधpoपूर्णांकs
 *
 * Copyright (C) 2018 Michael Neuling, IBM Corporation.
 */

#समावेश <sys/ptrace.h>
#समावेश <unistd.h>
#समावेश <मानकघोष.स>
#समावेश <sys/user.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <संकेत.स>
#समावेश <sys/types.h>
#समावेश <sys/रुको.h>
#समावेश <sys/syscall.h>
#समावेश <linux/सीमा.स>
#समावेश "ptrace.h"

#घोषणा SPRN_PVR	0x11F
#घोषणा PVR_8xx		0x00500000

bool is_8xx;

/*
 * Use अस्थिर on all global var so that compiler करोesn't
 * optimise their load/stores. Otherwise selftest can fail.
 */
अटल अस्थिर __u64 glvar;

#घोषणा DAWR_MAX_LEN 512
अटल अस्थिर __u8 big_var[DAWR_MAX_LEN] __attribute__((aligned(512)));

#घोषणा A_LEN 6
#घोषणा B_LEN 6
काष्ठा gकाष्ठा अणु
	__u8 a[A_LEN]; /* द्विगुन word aligned */
	__u8 b[B_LEN]; /* द्विगुन word unaligned */
पूर्ण;
अटल अस्थिर काष्ठा gकाष्ठा gकाष्ठा __attribute__((aligned(512)));

अटल अस्थिर अक्षर cwd[PATH_MAX] __attribute__((aligned(8)));

अटल व्योम get_dbginfo(pid_t child_pid, काष्ठा ppc_debug_info *dbginfo)
अणु
	अगर (ptrace(PPC_PTRACE_GETHWDBGINFO, child_pid, शून्य, dbginfo)) अणु
		लिखो_त्रुटि("Can't get breakpoint info");
		निकास(-1);
	पूर्ण
पूर्ण

अटल bool dawr_present(काष्ठा ppc_debug_info *dbginfo)
अणु
	वापस !!(dbginfo->features & PPC_DEBUG_FEATURE_DATA_BP_DAWR);
पूर्ण

अटल व्योम ग_लिखो_var(पूर्णांक len)
अणु
	__u8 *pcvar;
	__u16 *psvar;
	__u32 *pivar;
	__u64 *plvar;

	चयन (len) अणु
	हाल 1:
		pcvar = (__u8 *)&glvar;
		*pcvar = 0xff;
		अवरोध;
	हाल 2:
		psvar = (__u16 *)&glvar;
		*psvar = 0xffff;
		अवरोध;
	हाल 4:
		pivar = (__u32 *)&glvar;
		*pivar = 0xffffffff;
		अवरोध;
	हाल 8:
		plvar = (__u64 *)&glvar;
		*plvar = 0xffffffffffffffffLL;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम पढ़ो_var(पूर्णांक len)
अणु
	__u8 cvar __attribute__((unused));
	__u16 svar __attribute__((unused));
	__u32 ivar __attribute__((unused));
	__u64 lvar __attribute__((unused));

	चयन (len) अणु
	हाल 1:
		cvar = (__u8)glvar;
		अवरोध;
	हाल 2:
		svar = (__u16)glvar;
		अवरोध;
	हाल 4:
		ivar = (__u32)glvar;
		अवरोध;
	हाल 8:
		lvar = (__u64)glvar;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम test_workload(व्योम)
अणु
	__u8 cvar __attribute__((unused));
	__u32 ivar __attribute__((unused));
	पूर्णांक len = 0;

	अगर (ptrace(PTRACE_TRACEME, 0, शून्य, 0)) अणु
		लिखो_त्रुटि("Child can't be traced?");
		निकास(-1);
	पूर्ण

	/* Wake up father so that it sets up the first test */
	समाप्त(getpid(), SIGUSR1);

	/* PTRACE_SET_DEBUGREG, WO test */
	क्रम (len = 1; len <= माप(glvar); len <<= 1)
		ग_लिखो_var(len);

	/* PTRACE_SET_DEBUGREG, RO test */
	क्रम (len = 1; len <= माप(glvar); len <<= 1)
		पढ़ो_var(len);

	/* PTRACE_SET_DEBUGREG, RW test */
	क्रम (len = 1; len <= माप(glvar); len <<= 1) अणु
		अगर (अक्रम() % 2)
			पढ़ो_var(len);
		अन्यथा
			ग_लिखो_var(len);
	पूर्ण

	/* PTRACE_SET_DEBUGREG, Kernel Access Userspace test */
	syscall(__NR_अ_लोwd, &cwd, PATH_MAX);

	/* PPC_PTRACE_SETHWDEBUG, MODE_EXACT, WO test */
	ग_लिखो_var(1);

	/* PPC_PTRACE_SETHWDEBUG, MODE_EXACT, RO test */
	पढ़ो_var(1);

	/* PPC_PTRACE_SETHWDEBUG, MODE_EXACT, RW test */
	अगर (अक्रम() % 2)
		ग_लिखो_var(1);
	अन्यथा
		पढ़ो_var(1);

	/* PPC_PTRACE_SETHWDEBUG, MODE_EXACT, Kernel Access Userspace test */
	syscall(__NR_अ_लोwd, &cwd, PATH_MAX);

	/* PPC_PTRACE_SETHWDEBUG, MODE_RANGE, DW ALIGNED, WO test */
	gकाष्ठा.a[अक्रम() % A_LEN] = 'a';

	/* PPC_PTRACE_SETHWDEBUG, MODE_RANGE, DW ALIGNED, RO test */
	cvar = gकाष्ठा.a[अक्रम() % A_LEN];

	/* PPC_PTRACE_SETHWDEBUG, MODE_RANGE, DW ALIGNED, RW test */
	अगर (अक्रम() % 2)
		gकाष्ठा.a[अक्रम() % A_LEN] = 'a';
	अन्यथा
		cvar = gकाष्ठा.a[अक्रम() % A_LEN];

	/* PPC_PTRACE_SETHWDEBUG, MODE_RANGE, DW UNALIGNED, WO test */
	gकाष्ठा.b[अक्रम() % B_LEN] = 'b';

	/* PPC_PTRACE_SETHWDEBUG, MODE_RANGE, DW UNALIGNED, RO test */
	cvar = gकाष्ठा.b[अक्रम() % B_LEN];

	/* PPC_PTRACE_SETHWDEBUG, MODE_RANGE, DW UNALIGNED, RW test */
	अगर (अक्रम() % 2)
		gकाष्ठा.b[अक्रम() % B_LEN] = 'b';
	अन्यथा
		cvar = gकाष्ठा.b[अक्रम() % B_LEN];

	/* PPC_PTRACE_SETHWDEBUG, MODE_RANGE, DW UNALIGNED, DAR OUTSIDE, RW test */
	अगर (अक्रम() % 2)
		*((पूर्णांक *)(gकाष्ठा.a + 4)) = 10;
	अन्यथा
		ivar = *((पूर्णांक *)(gकाष्ठा.a + 4));

	/* PPC_PTRACE_SETHWDEBUG. DAWR_MAX_LEN. RW test */
	अगर (अक्रम() % 2)
		big_var[अक्रम() % DAWR_MAX_LEN] = 'a';
	अन्यथा
		cvar = big_var[अक्रम() % DAWR_MAX_LEN];

	/* PPC_PTRACE_SETHWDEBUG 2, MODE_RANGE, DW ALIGNED, WO test */
	gकाष्ठा.a[अक्रम() % A_LEN] = 'a';

	/* PPC_PTRACE_SETHWDEBUG 2, MODE_RANGE, DW UNALIGNED, RO test */
	cvar = gकाष्ठा.b[अक्रम() % B_LEN];

	/* PPC_PTRACE_SETHWDEBUG 2, MODE_RANGE, DAWR Overlap, WO test */
	gकाष्ठा.a[अक्रम() % A_LEN] = 'a';

	/* PPC_PTRACE_SETHWDEBUG 2, MODE_RANGE, DAWR Overlap, RO test */
	cvar = gकाष्ठा.a[अक्रम() % A_LEN];
पूर्ण

अटल व्योम check_success(pid_t child_pid, स्थिर अक्षर *name, स्थिर अक्षर *type,
			  अचिन्हित दीर्घ saddr, पूर्णांक len)
अणु
	पूर्णांक status;
	siginfo_t siginfo;
	अचिन्हित दीर्घ eaddr = (saddr + len - 1) | 0x7;

	saddr &= ~0x7;

	/* Wait क्रम the child to SIGTRAP */
	रुको(&status);

	ptrace(PTRACE_GETSIGINFO, child_pid, शून्य, &siginfo);

	अगर (!WIFSTOPPED(status) || WSTOPSIG(status) != SIGTRAP ||
	    (अचिन्हित दीर्घ)siginfo.si_addr < saddr ||
	    (अचिन्हित दीर्घ)siginfo.si_addr > eaddr) अणु
		म_लिखो("%s, %s, len: %d: Fail\n", name, type, len);
		निकास(-1);
	पूर्ण

	म_लिखो("%s, %s, len: %d: Ok\n", name, type, len);

	अगर (!is_8xx) अणु
		/*
		 * For ptrace रेजिस्टरed watchpoपूर्णांक, संकेत is generated
		 * beक्रमe executing load/store. Singlestep the inकाष्ठाion
		 * and then जारी the test.
		 */
		ptrace(PTRACE_SINGLESTEP, child_pid, शून्य, 0);
		रुको(शून्य);
	पूर्ण
पूर्ण

अटल व्योम ptrace_set_debugreg(pid_t child_pid, अचिन्हित दीर्घ wp_addr)
अणु
	अगर (ptrace(PTRACE_SET_DEBUGREG, child_pid, 0, wp_addr)) अणु
		लिखो_त्रुटि("PTRACE_SET_DEBUGREG failed");
		निकास(-1);
	पूर्ण
पूर्ण

अटल पूर्णांक ptrace_sethwdebug(pid_t child_pid, काष्ठा ppc_hw_अवरोधpoपूर्णांक *info)
अणु
	पूर्णांक wh = ptrace(PPC_PTRACE_SETHWDEBUG, child_pid, 0, info);

	अगर (wh <= 0) अणु
		लिखो_त्रुटि("PPC_PTRACE_SETHWDEBUG failed");
		निकास(-1);
	पूर्ण
	वापस wh;
पूर्ण

अटल व्योम ptrace_delhwdebug(pid_t child_pid, पूर्णांक wh)
अणु
	अगर (ptrace(PPC_PTRACE_DELHWDEBUG, child_pid, 0, wh) < 0) अणु
		लिखो_त्रुटि("PPC_PTRACE_DELHWDEBUG failed");
		निकास(-1);
	पूर्ण
पूर्ण

#घोषणा DABR_READ_SHIFT		0
#घोषणा DABR_WRITE_SHIFT	1
#घोषणा DABR_TRANSLATION_SHIFT	2

अटल पूर्णांक test_set_debugreg(pid_t child_pid)
अणु
	अचिन्हित दीर्घ wp_addr = (अचिन्हित दीर्घ)&glvar;
	अक्षर *name = "PTRACE_SET_DEBUGREG";
	पूर्णांक len;

	/* PTRACE_SET_DEBUGREG, WO test*/
	wp_addr &= ~0x7UL;
	wp_addr |= (1UL << DABR_WRITE_SHIFT);
	wp_addr |= (1UL << DABR_TRANSLATION_SHIFT);
	क्रम (len = 1; len <= माप(glvar); len <<= 1) अणु
		ptrace_set_debugreg(child_pid, wp_addr);
		ptrace(PTRACE_CONT, child_pid, शून्य, 0);
		check_success(child_pid, name, "WO", wp_addr, len);
	पूर्ण

	/* PTRACE_SET_DEBUGREG, RO test */
	wp_addr &= ~0x7UL;
	wp_addr |= (1UL << DABR_READ_SHIFT);
	wp_addr |= (1UL << DABR_TRANSLATION_SHIFT);
	क्रम (len = 1; len <= माप(glvar); len <<= 1) अणु
		ptrace_set_debugreg(child_pid, wp_addr);
		ptrace(PTRACE_CONT, child_pid, शून्य, 0);
		check_success(child_pid, name, "RO", wp_addr, len);
	पूर्ण

	/* PTRACE_SET_DEBUGREG, RW test */
	wp_addr &= ~0x7UL;
	wp_addr |= (1Ul << DABR_READ_SHIFT);
	wp_addr |= (1UL << DABR_WRITE_SHIFT);
	wp_addr |= (1UL << DABR_TRANSLATION_SHIFT);
	क्रम (len = 1; len <= माप(glvar); len <<= 1) अणु
		ptrace_set_debugreg(child_pid, wp_addr);
		ptrace(PTRACE_CONT, child_pid, शून्य, 0);
		check_success(child_pid, name, "RW", wp_addr, len);
	पूर्ण

	ptrace_set_debugreg(child_pid, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक test_set_debugreg_kernel_userspace(pid_t child_pid)
अणु
	अचिन्हित दीर्घ wp_addr = (अचिन्हित दीर्घ)cwd;
	अक्षर *name = "PTRACE_SET_DEBUGREG";

	/* PTRACE_SET_DEBUGREG, Kernel Access Userspace test */
	wp_addr &= ~0x7UL;
	wp_addr |= (1Ul << DABR_READ_SHIFT);
	wp_addr |= (1UL << DABR_WRITE_SHIFT);
	wp_addr |= (1UL << DABR_TRANSLATION_SHIFT);
	ptrace_set_debugreg(child_pid, wp_addr);
	ptrace(PTRACE_CONT, child_pid, शून्य, 0);
	check_success(child_pid, name, "Kernel Access Userspace", wp_addr, 8);

	ptrace_set_debugreg(child_pid, 0);
	वापस 0;
पूर्ण

अटल व्योम get_ppc_hw_अवरोधpoपूर्णांक(काष्ठा ppc_hw_अवरोधpoपूर्णांक *info, पूर्णांक type,
				  अचिन्हित दीर्घ addr, पूर्णांक len)
अणु
	info->version = 1;
	info->trigger_type = type;
	info->condition_mode = PPC_BREAKPOINT_CONDITION_NONE;
	info->addr = (__u64)addr;
	info->addr2 = (__u64)addr + len;
	info->condition_value = 0;
	अगर (!len)
		info->addr_mode = PPC_BREAKPOINT_MODE_EXACT;
	अन्यथा
		info->addr_mode = PPC_BREAKPOINT_MODE_RANGE_INCLUSIVE;
पूर्ण

अटल व्योम test_sethwdebug_exact(pid_t child_pid)
अणु
	काष्ठा ppc_hw_अवरोधpoपूर्णांक info;
	अचिन्हित दीर्घ wp_addr = (अचिन्हित दीर्घ)&glvar;
	अक्षर *name = "PPC_PTRACE_SETHWDEBUG, MODE_EXACT";
	पूर्णांक len = 1; /* hardcoded in kernel */
	पूर्णांक wh;

	/* PPC_PTRACE_SETHWDEBUG, MODE_EXACT, WO test */
	get_ppc_hw_अवरोधpoपूर्णांक(&info, PPC_BREAKPOINT_TRIGGER_WRITE, wp_addr, 0);
	wh = ptrace_sethwdebug(child_pid, &info);
	ptrace(PTRACE_CONT, child_pid, शून्य, 0);
	check_success(child_pid, name, "WO", wp_addr, len);
	ptrace_delhwdebug(child_pid, wh);

	/* PPC_PTRACE_SETHWDEBUG, MODE_EXACT, RO test */
	get_ppc_hw_अवरोधpoपूर्णांक(&info, PPC_BREAKPOINT_TRIGGER_READ, wp_addr, 0);
	wh = ptrace_sethwdebug(child_pid, &info);
	ptrace(PTRACE_CONT, child_pid, शून्य, 0);
	check_success(child_pid, name, "RO", wp_addr, len);
	ptrace_delhwdebug(child_pid, wh);

	/* PPC_PTRACE_SETHWDEBUG, MODE_EXACT, RW test */
	get_ppc_hw_अवरोधpoपूर्णांक(&info, PPC_BREAKPOINT_TRIGGER_RW, wp_addr, 0);
	wh = ptrace_sethwdebug(child_pid, &info);
	ptrace(PTRACE_CONT, child_pid, शून्य, 0);
	check_success(child_pid, name, "RW", wp_addr, len);
	ptrace_delhwdebug(child_pid, wh);
पूर्ण

अटल व्योम test_sethwdebug_exact_kernel_userspace(pid_t child_pid)
अणु
	काष्ठा ppc_hw_अवरोधpoपूर्णांक info;
	अचिन्हित दीर्घ wp_addr = (अचिन्हित दीर्घ)&cwd;
	अक्षर *name = "PPC_PTRACE_SETHWDEBUG, MODE_EXACT";
	पूर्णांक len = 1; /* hardcoded in kernel */
	पूर्णांक wh;

	/* PPC_PTRACE_SETHWDEBUG, MODE_EXACT, Kernel Access Userspace test */
	get_ppc_hw_अवरोधpoपूर्णांक(&info, PPC_BREAKPOINT_TRIGGER_WRITE, wp_addr, 0);
	wh = ptrace_sethwdebug(child_pid, &info);
	ptrace(PTRACE_CONT, child_pid, शून्य, 0);
	check_success(child_pid, name, "Kernel Access Userspace", wp_addr, len);
	ptrace_delhwdebug(child_pid, wh);
पूर्ण

अटल व्योम test_sethwdebug_range_aligned(pid_t child_pid)
अणु
	काष्ठा ppc_hw_अवरोधpoपूर्णांक info;
	अचिन्हित दीर्घ wp_addr;
	अक्षर *name = "PPC_PTRACE_SETHWDEBUG, MODE_RANGE, DW ALIGNED";
	पूर्णांक len;
	पूर्णांक wh;

	/* PPC_PTRACE_SETHWDEBUG, MODE_RANGE, DW ALIGNED, WO test */
	wp_addr = (अचिन्हित दीर्घ)&gकाष्ठा.a;
	len = A_LEN;
	get_ppc_hw_अवरोधpoपूर्णांक(&info, PPC_BREAKPOINT_TRIGGER_WRITE, wp_addr, len);
	wh = ptrace_sethwdebug(child_pid, &info);
	ptrace(PTRACE_CONT, child_pid, शून्य, 0);
	check_success(child_pid, name, "WO", wp_addr, len);
	ptrace_delhwdebug(child_pid, wh);

	/* PPC_PTRACE_SETHWDEBUG, MODE_RANGE, DW ALIGNED, RO test */
	wp_addr = (अचिन्हित दीर्घ)&gकाष्ठा.a;
	len = A_LEN;
	get_ppc_hw_अवरोधpoपूर्णांक(&info, PPC_BREAKPOINT_TRIGGER_READ, wp_addr, len);
	wh = ptrace_sethwdebug(child_pid, &info);
	ptrace(PTRACE_CONT, child_pid, शून्य, 0);
	check_success(child_pid, name, "RO", wp_addr, len);
	ptrace_delhwdebug(child_pid, wh);

	/* PPC_PTRACE_SETHWDEBUG, MODE_RANGE, DW ALIGNED, RW test */
	wp_addr = (अचिन्हित दीर्घ)&gकाष्ठा.a;
	len = A_LEN;
	get_ppc_hw_अवरोधpoपूर्णांक(&info, PPC_BREAKPOINT_TRIGGER_RW, wp_addr, len);
	wh = ptrace_sethwdebug(child_pid, &info);
	ptrace(PTRACE_CONT, child_pid, शून्य, 0);
	check_success(child_pid, name, "RW", wp_addr, len);
	ptrace_delhwdebug(child_pid, wh);
पूर्ण

अटल व्योम test_multi_sethwdebug_range(pid_t child_pid)
अणु
	काष्ठा ppc_hw_अवरोधpoपूर्णांक info1, info2;
	अचिन्हित दीर्घ wp_addr1, wp_addr2;
	अक्षर *name1 = "PPC_PTRACE_SETHWDEBUG 2, MODE_RANGE, DW ALIGNED";
	अक्षर *name2 = "PPC_PTRACE_SETHWDEBUG 2, MODE_RANGE, DW UNALIGNED";
	पूर्णांक len1, len2;
	पूर्णांक wh1, wh2;

	wp_addr1 = (अचिन्हित दीर्घ)&gकाष्ठा.a;
	wp_addr2 = (अचिन्हित दीर्घ)&gकाष्ठा.b;
	len1 = A_LEN;
	len2 = B_LEN;
	get_ppc_hw_अवरोधpoपूर्णांक(&info1, PPC_BREAKPOINT_TRIGGER_WRITE, wp_addr1, len1);
	get_ppc_hw_अवरोधpoपूर्णांक(&info2, PPC_BREAKPOINT_TRIGGER_READ, wp_addr2, len2);

	/* PPC_PTRACE_SETHWDEBUG 2, MODE_RANGE, DW ALIGNED, WO test */
	wh1 = ptrace_sethwdebug(child_pid, &info1);

	/* PPC_PTRACE_SETHWDEBUG 2, MODE_RANGE, DW UNALIGNED, RO test */
	wh2 = ptrace_sethwdebug(child_pid, &info2);

	ptrace(PTRACE_CONT, child_pid, शून्य, 0);
	check_success(child_pid, name1, "WO", wp_addr1, len1);

	ptrace(PTRACE_CONT, child_pid, शून्य, 0);
	check_success(child_pid, name2, "RO", wp_addr2, len2);

	ptrace_delhwdebug(child_pid, wh1);
	ptrace_delhwdebug(child_pid, wh2);
पूर्ण

अटल व्योम test_multi_sethwdebug_range_dawr_overlap(pid_t child_pid)
अणु
	काष्ठा ppc_hw_अवरोधpoपूर्णांक info1, info2;
	अचिन्हित दीर्घ wp_addr1, wp_addr2;
	अक्षर *name = "PPC_PTRACE_SETHWDEBUG 2, MODE_RANGE, DAWR Overlap";
	पूर्णांक len1, len2;
	पूर्णांक wh1, wh2;

	wp_addr1 = (अचिन्हित दीर्घ)&gकाष्ठा.a;
	wp_addr2 = (अचिन्हित दीर्घ)&gकाष्ठा.a;
	len1 = A_LEN;
	len2 = A_LEN;
	get_ppc_hw_अवरोधpoपूर्णांक(&info1, PPC_BREAKPOINT_TRIGGER_WRITE, wp_addr1, len1);
	get_ppc_hw_अवरोधpoपूर्णांक(&info2, PPC_BREAKPOINT_TRIGGER_READ, wp_addr2, len2);

	/* PPC_PTRACE_SETHWDEBUG 2, MODE_RANGE, DAWR Overlap, WO test */
	wh1 = ptrace_sethwdebug(child_pid, &info1);

	/* PPC_PTRACE_SETHWDEBUG 2, MODE_RANGE, DAWR Overlap, RO test */
	wh2 = ptrace_sethwdebug(child_pid, &info2);

	ptrace(PTRACE_CONT, child_pid, शून्य, 0);
	check_success(child_pid, name, "WO", wp_addr1, len1);

	ptrace(PTRACE_CONT, child_pid, शून्य, 0);
	check_success(child_pid, name, "RO", wp_addr2, len2);

	ptrace_delhwdebug(child_pid, wh1);
	ptrace_delhwdebug(child_pid, wh2);
पूर्ण

अटल व्योम test_sethwdebug_range_unaligned(pid_t child_pid)
अणु
	काष्ठा ppc_hw_अवरोधpoपूर्णांक info;
	अचिन्हित दीर्घ wp_addr;
	अक्षर *name = "PPC_PTRACE_SETHWDEBUG, MODE_RANGE, DW UNALIGNED";
	पूर्णांक len;
	पूर्णांक wh;

	/* PPC_PTRACE_SETHWDEBUG, MODE_RANGE, DW UNALIGNED, WO test */
	wp_addr = (अचिन्हित दीर्घ)&gकाष्ठा.b;
	len = B_LEN;
	get_ppc_hw_अवरोधpoपूर्णांक(&info, PPC_BREAKPOINT_TRIGGER_WRITE, wp_addr, len);
	wh = ptrace_sethwdebug(child_pid, &info);
	ptrace(PTRACE_CONT, child_pid, शून्य, 0);
	check_success(child_pid, name, "WO", wp_addr, len);
	ptrace_delhwdebug(child_pid, wh);

	/* PPC_PTRACE_SETHWDEBUG, MODE_RANGE, DW UNALIGNED, RO test */
	wp_addr = (अचिन्हित दीर्घ)&gकाष्ठा.b;
	len = B_LEN;
	get_ppc_hw_अवरोधpoपूर्णांक(&info, PPC_BREAKPOINT_TRIGGER_READ, wp_addr, len);
	wh = ptrace_sethwdebug(child_pid, &info);
	ptrace(PTRACE_CONT, child_pid, शून्य, 0);
	check_success(child_pid, name, "RO", wp_addr, len);
	ptrace_delhwdebug(child_pid, wh);

	/* PPC_PTRACE_SETHWDEBUG, MODE_RANGE, DW UNALIGNED, RW test */
	wp_addr = (अचिन्हित दीर्घ)&gकाष्ठा.b;
	len = B_LEN;
	get_ppc_hw_अवरोधpoपूर्णांक(&info, PPC_BREAKPOINT_TRIGGER_RW, wp_addr, len);
	wh = ptrace_sethwdebug(child_pid, &info);
	ptrace(PTRACE_CONT, child_pid, शून्य, 0);
	check_success(child_pid, name, "RW", wp_addr, len);
	ptrace_delhwdebug(child_pid, wh);

पूर्ण

अटल व्योम test_sethwdebug_range_unaligned_dar(pid_t child_pid)
अणु
	काष्ठा ppc_hw_अवरोधpoपूर्णांक info;
	अचिन्हित दीर्घ wp_addr;
	अक्षर *name = "PPC_PTRACE_SETHWDEBUG, MODE_RANGE, DW UNALIGNED, DAR OUTSIDE";
	पूर्णांक len;
	पूर्णांक wh;

	/* PPC_PTRACE_SETHWDEBUG, MODE_RANGE, DW UNALIGNED, DAR OUTSIDE, RW test */
	wp_addr = (अचिन्हित दीर्घ)&gकाष्ठा.b;
	len = B_LEN;
	get_ppc_hw_अवरोधpoपूर्णांक(&info, PPC_BREAKPOINT_TRIGGER_WRITE, wp_addr, len);
	wh = ptrace_sethwdebug(child_pid, &info);
	ptrace(PTRACE_CONT, child_pid, शून्य, 0);
	check_success(child_pid, name, "RW", wp_addr, len);
	ptrace_delhwdebug(child_pid, wh);
पूर्ण

अटल व्योम test_sethwdebug_dawr_max_range(pid_t child_pid)
अणु
	काष्ठा ppc_hw_अवरोधpoपूर्णांक info;
	अचिन्हित दीर्घ wp_addr;
	अक्षर *name = "PPC_PTRACE_SETHWDEBUG, DAWR_MAX_LEN";
	पूर्णांक len;
	पूर्णांक wh;

	/* PPC_PTRACE_SETHWDEBUG, DAWR_MAX_LEN, RW test */
	wp_addr = (अचिन्हित दीर्घ)big_var;
	len = DAWR_MAX_LEN;
	get_ppc_hw_अवरोधpoपूर्णांक(&info, PPC_BREAKPOINT_TRIGGER_RW, wp_addr, len);
	wh = ptrace_sethwdebug(child_pid, &info);
	ptrace(PTRACE_CONT, child_pid, शून्य, 0);
	check_success(child_pid, name, "RW", wp_addr, len);
	ptrace_delhwdebug(child_pid, wh);
पूर्ण

/* Set the अवरोधpoपूर्णांकs and check the child successfully trigger them */
अटल व्योम
run_tests(pid_t child_pid, काष्ठा ppc_debug_info *dbginfo, bool dawr)
अणु
	test_set_debugreg(child_pid);
	test_set_debugreg_kernel_userspace(child_pid);
	test_sethwdebug_exact(child_pid);
	test_sethwdebug_exact_kernel_userspace(child_pid);
	अगर (dbginfo->features & PPC_DEBUG_FEATURE_DATA_BP_RANGE) अणु
		test_sethwdebug_range_aligned(child_pid);
		अगर (dawr || is_8xx) अणु
			test_sethwdebug_range_unaligned(child_pid);
			test_sethwdebug_range_unaligned_dar(child_pid);
			test_sethwdebug_dawr_max_range(child_pid);
			अगर (dbginfo->num_data_bps > 1) अणु
				test_multi_sethwdebug_range(child_pid);
				test_multi_sethwdebug_range_dawr_overlap(child_pid);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक ptrace_hwअवरोध(व्योम)
अणु
	pid_t child_pid;
	काष्ठा ppc_debug_info dbginfo;
	bool dawr;

	child_pid = विभाजन();
	अगर (!child_pid) अणु
		test_workload();
		वापस 0;
	पूर्ण

	रुको(शून्य);

	get_dbginfo(child_pid, &dbginfo);
	SKIP_IF(dbginfo.num_data_bps == 0);

	dawr = dawr_present(&dbginfo);
	run_tests(child_pid, &dbginfo, dawr);

	/* Let the child निकास first. */
	ptrace(PTRACE_CONT, child_pid, शून्य, 0);
	रुको(शून्य);

	/*
	 * Testहालs निकासs immediately with -1 on any failure. If
	 * it has reached here, it means all tests were successful.
	 */
	वापस TEST_PASS;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv, अक्षर **envp)
अणु
	पूर्णांक pvr = 0;
	यंत्र __अस्थिर__ ("mfspr %0,%1" : "=r"(pvr) : "i"(SPRN_PVR));
	अगर (pvr == PVR_8xx)
		is_8xx = true;

	वापस test_harness(ptrace_hwअवरोध, "ptrace-hwbreak");
पूर्ण
