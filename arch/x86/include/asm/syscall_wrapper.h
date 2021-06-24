<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * syscall_wrapper.h - x86 specअगरic wrappers to syscall definitions
 */

#अगर_अघोषित _ASM_X86_SYSCALL_WRAPPER_H
#घोषणा _ASM_X86_SYSCALL_WRAPPER_H

काष्ठा pt_regs;

बाह्य दीर्घ __x64_sys_ni_syscall(स्थिर काष्ठा pt_regs *regs);
बाह्य दीर्घ __ia32_sys_ni_syscall(स्थिर काष्ठा pt_regs *regs);

/*
 * Instead of the generic __SYSCALL_DEFINEx() definition, the x86 version takes
 * काष्ठा pt_regs *regs as the only argument of the syscall stub(s) named as:
 * __x64_sys_*()         - 64-bit native syscall
 * __ia32_sys_*()        - 32-bit native syscall or common compat syscall
 * __ia32_compat_sys_*() - 32-bit compat syscall
 * __x32_compat_sys_*()  - 64-bit X32 compat syscall
 *
 * The रेजिस्टरs are decoded according to the ABI:
 * 64-bit: RDI, RSI, RDX, R10, R8, R9
 * 32-bit: EBX, ECX, EDX, ESI, EDI, EBP
 *
 * The stub then passes the decoded arguments to the __se_sys_*() wrapper to
 * perक्रमm sign-extension (omitted क्रम zero-argument syscalls).  Finally the
 * arguments are passed to the __करो_sys_*() function which is the actual
 * syscall.  These wrappers are marked as अंतरभूत so the compiler can optimize
 * the functions where appropriate.
 *
 * Example assembly (slightly re-ordered क्रम better पढ़ोability):
 *
 * <__x64_sys_recv>:		<-- syscall with 4 parameters
 *	callq	<__fentry__>
 *
 *	mov	0x70(%rdi),%rdi	<-- decode regs->di
 *	mov	0x68(%rdi),%rsi	<-- decode regs->si
 *	mov	0x60(%rdi),%rdx	<-- decode regs->dx
 *	mov	0x38(%rdi),%rcx	<-- decode regs->r10
 *
 *	xor	%r9d,%r9d	<-- clear %r9
 *	xor	%r8d,%r8d	<-- clear %r8
 *
 *	callq	__sys_recvfrom	<-- करो the actual work in __sys_recvfrom()
 *				    which takes 6 arguments
 *
 *	cltq			<-- extend वापस value to 64-bit
 *	retq			<-- वापस
 *
 * This approach aव्योमs leaking अक्रमom user-provided रेजिस्टर content करोwn
 * the call chain.
 */

/* Mapping of रेजिस्टरs to parameters क्रम syscalls on x86-64 and x32 */
#घोषणा SC_X86_64_REGS_TO_ARGS(x, ...)					\
	__MAP(x,__SC_ARGS						\
		,,regs->di,,regs->si,,regs->dx				\
		,,regs->r10,,regs->r8,,regs->r9)			\

/* Mapping of रेजिस्टरs to parameters क्रम syscalls on i386 */
#घोषणा SC_IA32_REGS_TO_ARGS(x, ...)					\
	__MAP(x,__SC_ARGS						\
	      ,,(अचिन्हित पूर्णांक)regs->bx,,(अचिन्हित पूर्णांक)regs->cx		\
	      ,,(अचिन्हित पूर्णांक)regs->dx,,(अचिन्हित पूर्णांक)regs->si		\
	      ,,(अचिन्हित पूर्णांक)regs->di,,(अचिन्हित पूर्णांक)regs->bp)

#घोषणा __SYS_STUB0(abi, name)						\
	दीर्घ __##abi##_##name(स्थिर काष्ठा pt_regs *regs);		\
	ALLOW_ERROR_INJECTION(__##abi##_##name, ERRNO);			\
	दीर्घ __##abi##_##name(स्थिर काष्ठा pt_regs *regs)		\
		__alias(__करो_##name);

#घोषणा __SYS_STUBx(abi, name, ...)					\
	दीर्घ __##abi##_##name(स्थिर काष्ठा pt_regs *regs);		\
	ALLOW_ERROR_INJECTION(__##abi##_##name, ERRNO);			\
	दीर्घ __##abi##_##name(स्थिर काष्ठा pt_regs *regs)		\
	अणु								\
		वापस __se_##name(__VA_ARGS__);			\
	पूर्ण

#घोषणा __COND_SYSCALL(abi, name)					\
	__weak दीर्घ __##abi##_##name(स्थिर काष्ठा pt_regs *__unused);	\
	__weak दीर्घ __##abi##_##name(स्थिर काष्ठा pt_regs *__unused)	\
	अणु								\
		वापस sys_ni_syscall();				\
	पूर्ण

#घोषणा __SYS_NI(abi, name)						\
	SYSCALL_ALIAS(__##abi##_##name, sys_ni_posix_समयrs);

#अगर_घोषित CONFIG_X86_64
#घोषणा __X64_SYS_STUB0(name)						\
	__SYS_STUB0(x64, sys_##name)

#घोषणा __X64_SYS_STUBx(x, name, ...)					\
	__SYS_STUBx(x64, sys##name,					\
		    SC_X86_64_REGS_TO_ARGS(x, __VA_ARGS__))

#घोषणा __X64_COND_SYSCALL(name)					\
	__COND_SYSCALL(x64, sys_##name)

#घोषणा __X64_SYS_NI(name)						\
	__SYS_NI(x64, sys_##name)
#अन्यथा /* CONFIG_X86_64 */
#घोषणा __X64_SYS_STUB0(name)
#घोषणा __X64_SYS_STUBx(x, name, ...)
#घोषणा __X64_COND_SYSCALL(name)
#घोषणा __X64_SYS_NI(name)
#पूर्ण_अगर /* CONFIG_X86_64 */

#अगर defined(CONFIG_X86_32) || defined(CONFIG_IA32_EMULATION)
#घोषणा __IA32_SYS_STUB0(name)						\
	__SYS_STUB0(ia32, sys_##name)

#घोषणा __IA32_SYS_STUBx(x, name, ...)					\
	__SYS_STUBx(ia32, sys##name,					\
		    SC_IA32_REGS_TO_ARGS(x, __VA_ARGS__))

#घोषणा __IA32_COND_SYSCALL(name)					\
	__COND_SYSCALL(ia32, sys_##name)

#घोषणा __IA32_SYS_NI(name)						\
	__SYS_NI(ia32, sys_##name)
#अन्यथा /* CONFIG_X86_32 || CONFIG_IA32_EMULATION */
#घोषणा __IA32_SYS_STUB0(name)
#घोषणा __IA32_SYS_STUBx(x, name, ...)
#घोषणा __IA32_COND_SYSCALL(name)
#घोषणा __IA32_SYS_NI(name)
#पूर्ण_अगर /* CONFIG_X86_32 || CONFIG_IA32_EMULATION */

#अगर_घोषित CONFIG_IA32_EMULATION
/*
 * For IA32 emulation, we need to handle "compat" syscalls *and* create
 * additional wrappers (aptly named __ia32_sys_xyzzy) which decode the
 * ia32 regs in the proper order क्रम shared or "common" syscalls. As some
 * syscalls may not be implemented, we need to expand COND_SYSCALL in
 * kernel/sys_ni.c and SYS_NI in kernel/समय/posix-stubs.c to cover this
 * हाल as well.
 */
#घोषणा __IA32_COMPAT_SYS_STUB0(name)					\
	__SYS_STUB0(ia32, compat_sys_##name)

#घोषणा __IA32_COMPAT_SYS_STUBx(x, name, ...)				\
	__SYS_STUBx(ia32, compat_sys##name,				\
		    SC_IA32_REGS_TO_ARGS(x, __VA_ARGS__))

#घोषणा __IA32_COMPAT_COND_SYSCALL(name)				\
	__COND_SYSCALL(ia32, compat_sys_##name)

#घोषणा __IA32_COMPAT_SYS_NI(name)					\
	__SYS_NI(ia32, compat_sys_##name)

#अन्यथा /* CONFIG_IA32_EMULATION */
#घोषणा __IA32_COMPAT_SYS_STUB0(name)
#घोषणा __IA32_COMPAT_SYS_STUBx(x, name, ...)
#घोषणा __IA32_COMPAT_COND_SYSCALL(name)
#घोषणा __IA32_COMPAT_SYS_NI(name)
#पूर्ण_अगर /* CONFIG_IA32_EMULATION */


#अगर_घोषित CONFIG_X86_X32
/*
 * For the x32 ABI, we need to create a stub क्रम compat_sys_*() which is aware
 * of the x86-64-style parameter ordering of x32 syscalls. The syscalls common
 * with x86_64 obviously करो not need such care.
 */
#घोषणा __X32_COMPAT_SYS_STUB0(name)					\
	__SYS_STUB0(x32, compat_sys_##name)

#घोषणा __X32_COMPAT_SYS_STUBx(x, name, ...)				\
	__SYS_STUBx(x32, compat_sys##name,				\
		    SC_X86_64_REGS_TO_ARGS(x, __VA_ARGS__))

#घोषणा __X32_COMPAT_COND_SYSCALL(name)					\
	__COND_SYSCALL(x32, compat_sys_##name)

#घोषणा __X32_COMPAT_SYS_NI(name)					\
	__SYS_NI(x32, compat_sys_##name)
#अन्यथा /* CONFIG_X86_X32 */
#घोषणा __X32_COMPAT_SYS_STUB0(name)
#घोषणा __X32_COMPAT_SYS_STUBx(x, name, ...)
#घोषणा __X32_COMPAT_COND_SYSCALL(name)
#घोषणा __X32_COMPAT_SYS_NI(name)
#पूर्ण_अगर /* CONFIG_X86_X32 */


#अगर_घोषित CONFIG_COMPAT
/*
 * Compat means IA32_EMULATION and/or X86_X32. As they use a dअगरferent
 * mapping of रेजिस्टरs to parameters, we need to generate stubs क्रम each
 * of them.
 */
#घोषणा COMPAT_SYSCALL_DEFINE0(name)					\
	अटल दीर्घ							\
	__करो_compat_sys_##name(स्थिर काष्ठा pt_regs *__unused);		\
	__IA32_COMPAT_SYS_STUB0(name)					\
	__X32_COMPAT_SYS_STUB0(name)					\
	अटल दीर्घ							\
	__करो_compat_sys_##name(स्थिर काष्ठा pt_regs *__unused)

#घोषणा COMPAT_SYSCALL_DEFINEx(x, name, ...)					\
	अटल दीर्घ __se_compat_sys##name(__MAP(x,__SC_LONG,__VA_ARGS__));	\
	अटल अंतरभूत दीर्घ __करो_compat_sys##name(__MAP(x,__SC_DECL,__VA_ARGS__));\
	__IA32_COMPAT_SYS_STUBx(x, name, __VA_ARGS__)				\
	__X32_COMPAT_SYS_STUBx(x, name, __VA_ARGS__)				\
	अटल दीर्घ __se_compat_sys##name(__MAP(x,__SC_LONG,__VA_ARGS__))	\
	अणु									\
		वापस __करो_compat_sys##name(__MAP(x,__SC_DELOUSE,__VA_ARGS__));\
	पूर्ण									\
	अटल अंतरभूत दीर्घ __करो_compat_sys##name(__MAP(x,__SC_DECL,__VA_ARGS__))

/*
 * As some compat syscalls may not be implemented, we need to expand
 * COND_SYSCALL_COMPAT in kernel/sys_ni.c and COMPAT_SYS_NI in
 * kernel/समय/posix-stubs.c to cover this हाल as well.
 */
#घोषणा COND_SYSCALL_COMPAT(name) 					\
	__IA32_COMPAT_COND_SYSCALL(name)				\
	__X32_COMPAT_COND_SYSCALL(name)

#घोषणा COMPAT_SYS_NI(name)						\
	__IA32_COMPAT_SYS_NI(name)					\
	__X32_COMPAT_SYS_NI(name)

#पूर्ण_अगर /* CONFIG_COMPAT */

#घोषणा __SYSCALL_DEFINEx(x, name, ...)					\
	अटल दीर्घ __se_sys##name(__MAP(x,__SC_LONG,__VA_ARGS__));	\
	अटल अंतरभूत दीर्घ __करो_sys##name(__MAP(x,__SC_DECL,__VA_ARGS__));\
	__X64_SYS_STUBx(x, name, __VA_ARGS__)				\
	__IA32_SYS_STUBx(x, name, __VA_ARGS__)				\
	अटल दीर्घ __se_sys##name(__MAP(x,__SC_LONG,__VA_ARGS__))	\
	अणु								\
		दीर्घ ret = __करो_sys##name(__MAP(x,__SC_CAST,__VA_ARGS__));\
		__MAP(x,__SC_TEST,__VA_ARGS__);				\
		__PROTECT(x, ret,__MAP(x,__SC_ARGS,__VA_ARGS__));	\
		वापस ret;						\
	पूर्ण								\
	अटल अंतरभूत दीर्घ __करो_sys##name(__MAP(x,__SC_DECL,__VA_ARGS__))

/*
 * As the generic SYSCALL_DEFINE0() macro करोes not decode any parameters क्रम
 * obvious reasons, and passing काष्ठा pt_regs *regs to it in %rdi करोes not
 * hurt, we only need to re-define it here to keep the naming congruent to
 * SYSCALL_DEFINEx() -- which is essential क्रम the COND_SYSCALL() and SYS_NI()
 * macros to work correctly.
 */
#घोषणा SYSCALL_DEFINE0(sname)						\
	SYSCALL_METADATA(_##sname, 0);					\
	अटल दीर्घ __करो_sys_##sname(स्थिर काष्ठा pt_regs *__unused);	\
	__X64_SYS_STUB0(sname)						\
	__IA32_SYS_STUB0(sname)						\
	अटल दीर्घ __करो_sys_##sname(स्थिर काष्ठा pt_regs *__unused)

#घोषणा COND_SYSCALL(name)						\
	__X64_COND_SYSCALL(name)					\
	__IA32_COND_SYSCALL(name)

#घोषणा SYS_NI(name)							\
	__X64_SYS_NI(name)						\
	__IA32_SYS_NI(name)


/*
 * For VSYSCALLS, we need to declare these three syscalls with the new
 * pt_regs-based calling convention क्रम in-kernel use.
 */
दीर्घ __x64_sys_अ_लोpu(स्थिर काष्ठा pt_regs *regs);
दीर्घ __x64_sys_समय_लोofday(स्थिर काष्ठा pt_regs *regs);
दीर्घ __x64_sys_समय(स्थिर काष्ठा pt_regs *regs);

#पूर्ण_अगर /* _ASM_X86_SYSCALL_WRAPPER_H */
