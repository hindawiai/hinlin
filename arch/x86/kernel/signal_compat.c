<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/compat.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/ptrace.h>

/*
 * The compat_siginfo_t काष्ठाure and handing code is very easy
 * to अवरोध in several ways.  It must always be updated when new
 * updates are made to the मुख्य siginfo_t, and
 * copy_siginfo_to_user32() must be updated when the
 * (arch-independent) copy_siginfo_to_user() is updated.
 *
 * It is also easy to put a new member in the compat_siginfo_t
 * which has implicit alignment which can move पूर्णांकernal काष्ठाure
 * alignment around अवरोधing the ABI.  This can happen अगर you,
 * क्रम instance, put a plain 64-bit value in there.
 */
अटल अंतरभूत व्योम संकेत_compat_build_tests(व्योम)
अणु
	पूर्णांक _sअगरields_offset = दुरत्व(compat_siginfo_t, _sअगरields);

	/*
	 * If adding a new si_code, there is probably new data in
	 * the siginfo.  Make sure folks bumping the si_code
	 * limits also have to look at this code.  Make sure any
	 * new fields are handled in copy_siginfo_to_user32()!
	 */
	BUILD_BUG_ON(Nसंक_अवैध  != 11);
	BUILD_BUG_ON(Nसंक_भ_त्रुटि  != 15);
	BUILD_BUG_ON(Nसंक_अंश != 9);
	BUILD_BUG_ON(NSIGBUS  != 5);
	BUILD_BUG_ON(NSIGTRAP != 6);
	BUILD_BUG_ON(NSIGCHLD != 6);
	BUILD_BUG_ON(NSIGSYS  != 2);

	/* This is part of the ABI and can never change in size: */
	BUILD_BUG_ON(माप(compat_siginfo_t) != 128);
	/*
	 * The offsets of all the (जोड़ed) si_fields are fixed
	 * in the ABI, of course.  Make sure none of them ever
	 * move and are always at the beginning:
	 */
	BUILD_BUG_ON(दुरत्व(compat_siginfo_t, _sअगरields) != 3 * माप(पूर्णांक));
#घोषणा CHECK_CSI_OFFSET(name)	  BUILD_BUG_ON(_sअगरields_offset != दुरत्व(compat_siginfo_t, _sअगरields.name))

	BUILD_BUG_ON(दुरत्व(siginfo_t, si_signo) != 0);
	BUILD_BUG_ON(दुरत्व(siginfo_t, si_त्रुटि_सं) != 4);
	BUILD_BUG_ON(दुरत्व(siginfo_t, si_code)  != 8);

	BUILD_BUG_ON(दुरत्व(compat_siginfo_t, si_signo) != 0);
	BUILD_BUG_ON(दुरत्व(compat_siginfo_t, si_त्रुटि_सं) != 4);
	BUILD_BUG_ON(दुरत्व(compat_siginfo_t, si_code)  != 8);
	 /*
	 * Ensure that the size of each si_field never changes.
	 * If it करोes, it is a sign that the
	 * copy_siginfo_to_user32() code below needs to updated
	 * aदीर्घ with the size in the CHECK_SI_SIZE().
	 *
	 * We repeat this check क्रम both the generic and compat
	 * siginfos.
	 *
	 * Note: it is OK क्रम these to grow as दीर्घ as the whole
	 * काष्ठाure stays within the padding size (checked
	 * above).
	 */
#घोषणा CHECK_CSI_SIZE(name, size) BUILD_BUG_ON(size != माप(((compat_siginfo_t *)0)->_sअगरields.name))
#घोषणा CHECK_SI_SIZE(name, size) BUILD_BUG_ON(size != माप(((siginfo_t *)0)->_sअगरields.name))

	CHECK_CSI_OFFSET(_समाप्त);
	CHECK_CSI_SIZE  (_समाप्त, 2*माप(पूर्णांक));
	CHECK_SI_SIZE   (_समाप्त, 2*माप(पूर्णांक));

	BUILD_BUG_ON(दुरत्व(siginfo_t, si_pid) != 0x10);
	BUILD_BUG_ON(दुरत्व(siginfo_t, si_uid) != 0x14);
	BUILD_BUG_ON(दुरत्व(compat_siginfo_t, si_pid) != 0xC);
	BUILD_BUG_ON(दुरत्व(compat_siginfo_t, si_uid) != 0x10);

	CHECK_CSI_OFFSET(_समयr);
	CHECK_CSI_SIZE  (_समयr, 3*माप(पूर्णांक));
	CHECK_SI_SIZE   (_समयr, 6*माप(पूर्णांक));

	BUILD_BUG_ON(दुरत्व(siginfo_t, si_tid)     != 0x10);
	BUILD_BUG_ON(दुरत्व(siginfo_t, si_overrun) != 0x14);
	BUILD_BUG_ON(दुरत्व(siginfo_t, si_value)   != 0x18);
	BUILD_BUG_ON(दुरत्व(compat_siginfo_t, si_tid)     != 0x0C);
	BUILD_BUG_ON(दुरत्व(compat_siginfo_t, si_overrun) != 0x10);
	BUILD_BUG_ON(दुरत्व(compat_siginfo_t, si_value)   != 0x14);

	CHECK_CSI_OFFSET(_rt);
	CHECK_CSI_SIZE  (_rt, 3*माप(पूर्णांक));
	CHECK_SI_SIZE   (_rt, 4*माप(पूर्णांक));

	BUILD_BUG_ON(दुरत्व(siginfo_t, si_pid)   != 0x10);
	BUILD_BUG_ON(दुरत्व(siginfo_t, si_uid)   != 0x14);
	BUILD_BUG_ON(दुरत्व(siginfo_t, si_value) != 0x18);
	BUILD_BUG_ON(दुरत्व(compat_siginfo_t, si_pid)   != 0x0C);
	BUILD_BUG_ON(दुरत्व(compat_siginfo_t, si_uid)   != 0x10);
	BUILD_BUG_ON(दुरत्व(compat_siginfo_t, si_value) != 0x14);

	CHECK_CSI_OFFSET(_sigchld);
	CHECK_CSI_SIZE  (_sigchld, 5*माप(पूर्णांक));
	CHECK_SI_SIZE   (_sigchld, 8*माप(पूर्णांक));

	BUILD_BUG_ON(दुरत्व(siginfo_t, si_pid)    != 0x10);
	BUILD_BUG_ON(दुरत्व(siginfo_t, si_uid)    != 0x14);
	BUILD_BUG_ON(दुरत्व(siginfo_t, si_status) != 0x18);
	BUILD_BUG_ON(दुरत्व(siginfo_t, si_uसमय)  != 0x20);
	BUILD_BUG_ON(दुरत्व(siginfo_t, si_sसमय)  != 0x28);
	BUILD_BUG_ON(दुरत्व(compat_siginfo_t, si_pid)    != 0x0C);
	BUILD_BUG_ON(दुरत्व(compat_siginfo_t, si_uid)    != 0x10);
	BUILD_BUG_ON(दुरत्व(compat_siginfo_t, si_status) != 0x14);
	BUILD_BUG_ON(दुरत्व(compat_siginfo_t, si_uसमय)  != 0x18);
	BUILD_BUG_ON(दुरत्व(compat_siginfo_t, si_sसमय)  != 0x1C);

#अगर_घोषित CONFIG_X86_X32_ABI
	CHECK_CSI_OFFSET(_sigchld_x32);
	CHECK_CSI_SIZE  (_sigchld_x32, 7*माप(पूर्णांक));
	/* no _sigchld_x32 in the generic siginfo_t */
	BUILD_BUG_ON(दुरत्व(compat_siginfo_t, _sअगरields._sigchld_x32._uसमय)  != 0x18);
	BUILD_BUG_ON(दुरत्व(compat_siginfo_t, _sअगरields._sigchld_x32._sसमय)  != 0x20);
#पूर्ण_अगर

	CHECK_CSI_OFFSET(_sigfault);
	CHECK_CSI_SIZE  (_sigfault, 4*माप(पूर्णांक));
	CHECK_SI_SIZE   (_sigfault, 8*माप(पूर्णांक));

	BUILD_BUG_ON(दुरत्व(siginfo_t, si_addr) != 0x10);
	BUILD_BUG_ON(दुरत्व(compat_siginfo_t, si_addr) != 0x0C);

	BUILD_BUG_ON(दुरत्व(siginfo_t, si_trapno) != 0x18);
	BUILD_BUG_ON(दुरत्व(compat_siginfo_t, si_trapno) != 0x10);

	BUILD_BUG_ON(दुरत्व(siginfo_t, si_addr_lsb) != 0x18);
	BUILD_BUG_ON(दुरत्व(compat_siginfo_t, si_addr_lsb) != 0x10);

	BUILD_BUG_ON(दुरत्व(siginfo_t, si_lower) != 0x20);
	BUILD_BUG_ON(दुरत्व(siginfo_t, si_upper) != 0x28);
	BUILD_BUG_ON(दुरत्व(compat_siginfo_t, si_lower) != 0x14);
	BUILD_BUG_ON(दुरत्व(compat_siginfo_t, si_upper) != 0x18);

	BUILD_BUG_ON(दुरत्व(siginfo_t, si_pkey) != 0x20);
	BUILD_BUG_ON(दुरत्व(compat_siginfo_t, si_pkey) != 0x14);

	BUILD_BUG_ON(दुरत्व(siginfo_t, si_perf_data) != 0x18);
	BUILD_BUG_ON(दुरत्व(siginfo_t, si_perf_type) != 0x20);
	BUILD_BUG_ON(दुरत्व(compat_siginfo_t, si_perf_data) != 0x10);
	BUILD_BUG_ON(दुरत्व(compat_siginfo_t, si_perf_type) != 0x14);

	CHECK_CSI_OFFSET(_sigpoll);
	CHECK_CSI_SIZE  (_sigpoll, 2*माप(पूर्णांक));
	CHECK_SI_SIZE   (_sigpoll, 4*माप(पूर्णांक));

	BUILD_BUG_ON(दुरत्व(siginfo_t, si_band)   != 0x10);
	BUILD_BUG_ON(दुरत्व(siginfo_t, si_fd)     != 0x18);
	BUILD_BUG_ON(दुरत्व(compat_siginfo_t, si_band) != 0x0C);
	BUILD_BUG_ON(दुरत्व(compat_siginfo_t, si_fd)   != 0x10);

	CHECK_CSI_OFFSET(_sigsys);
	CHECK_CSI_SIZE  (_sigsys, 3*माप(पूर्णांक));
	CHECK_SI_SIZE   (_sigsys, 4*माप(पूर्णांक));

	BUILD_BUG_ON(दुरत्व(siginfo_t, si_call_addr) != 0x10);
	BUILD_BUG_ON(दुरत्व(siginfo_t, si_syscall)   != 0x18);
	BUILD_BUG_ON(दुरत्व(siginfo_t, si_arch)      != 0x1C);
	BUILD_BUG_ON(दुरत्व(compat_siginfo_t, si_call_addr) != 0x0C);
	BUILD_BUG_ON(दुरत्व(compat_siginfo_t, si_syscall)   != 0x10);
	BUILD_BUG_ON(दुरत्व(compat_siginfo_t, si_arch)      != 0x14);

	/* any new si_fields should be added here */
पूर्ण

व्योम sigaction_compat_abi(काष्ठा k_sigaction *act, काष्ठा k_sigaction *oact)
अणु
	संकेत_compat_build_tests();

	अगर (!act)
		वापस;

	अगर (in_ia32_syscall())
		act->sa.sa_flags |= SA_IA32_ABI;
	अगर (in_x32_syscall())
		act->sa.sa_flags |= SA_X32_ABI;
पूर्ण
