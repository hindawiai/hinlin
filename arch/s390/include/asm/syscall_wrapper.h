<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * syscall_wrapper.h - s390 specअगरic wrappers to syscall definitions
 *
 */

#अगर_अघोषित _ASM_S390_SYSCALL_WRAPPER_H
#घोषणा _ASM_S390_SYSCALL_WRAPPER_H

#घोषणा __SC_TYPE(t, a) t

#घोषणा SYSCALL_PT_ARG6(regs, m, t1, t2, t3, t4, t5, t6)\
	SYSCALL_PT_ARG5(regs, m, t1, t2, t3, t4, t5),	\
		m(t6, (regs->gprs[7]))

#घोषणा SYSCALL_PT_ARG5(regs, m, t1, t2, t3, t4, t5)	\
	SYSCALL_PT_ARG4(regs, m, t1, t2, t3, t4),	\
		m(t5, (regs->gprs[6]))

#घोषणा SYSCALL_PT_ARG4(regs, m, t1, t2, t3, t4)	\
	SYSCALL_PT_ARG3(regs, m, t1, t2, t3),		\
		m(t4, (regs->gprs[5]))

#घोषणा SYSCALL_PT_ARG3(regs, m, t1, t2, t3)		\
	SYSCALL_PT_ARG2(regs, m, t1, t2),		\
		m(t3, (regs->gprs[4]))

#घोषणा SYSCALL_PT_ARG2(regs, m, t1, t2)		\
	SYSCALL_PT_ARG1(regs, m, t1),			\
		m(t2, (regs->gprs[3]))

#घोषणा SYSCALL_PT_ARG1(regs, m, t1)			\
		m(t1, (regs->orig_gpr2))

#घोषणा SYSCALL_PT_ARGS(x, ...) SYSCALL_PT_ARG##x(__VA_ARGS__)

#अगर_घोषित CONFIG_COMPAT
#घोषणा __SC_COMPAT_TYPE(t, a) \
	__typeof(__builtin_choose_expr(माप(t) > 4, 0L, (t)0)) a

#घोषणा __SC_COMPAT_CAST(t, a)						\
(अणु									\
	दीर्घ __ReS = a;							\
									\
	BUILD_BUG_ON((माप(t) > 4) && !__TYPE_IS_L(t) &&		\
		     !__TYPE_IS_UL(t) && !__TYPE_IS_PTR(t) &&		\
		     !__TYPE_IS_LL(t));					\
	अगर (__TYPE_IS_L(t))						\
		__ReS = (s32)a;						\
	अगर (__TYPE_IS_UL(t))						\
		__ReS = (u32)a;						\
	अगर (__TYPE_IS_PTR(t))						\
		__ReS = a & 0x7fffffff;					\
	अगर (__TYPE_IS_LL(t))						\
		वापस -ENOSYS;						\
	(t)__ReS;							\
पूर्ण)

#घोषणा __S390_SYS_STUBx(x, name, ...)						\
	दीर्घ __s390_sys##name(काष्ठा pt_regs *regs);				\
	ALLOW_ERROR_INJECTION(__s390_sys##name, ERRNO);				\
	दीर्घ __s390_sys##name(काष्ठा pt_regs *regs)				\
	अणु									\
		दीर्घ ret = __करो_sys##name(SYSCALL_PT_ARGS(x, regs,		\
			__SC_COMPAT_CAST, __MAP(x, __SC_TYPE, __VA_ARGS__)));	\
		__MAP(x,__SC_TEST,__VA_ARGS__);					\
		वापस ret;							\
	पूर्ण

/*
 * To keep the naming coherent, re-define SYSCALL_DEFINE0 to create an alias
 * named __s390x_sys_*()
 */
#घोषणा COMPAT_SYSCALL_DEFINE0(sname)					\
	SYSCALL_METADATA(_##sname, 0);					\
	दीर्घ __s390_compat_sys_##sname(व्योम);				\
	ALLOW_ERROR_INJECTION(__s390_compat_sys_##sname, ERRNO);	\
	दीर्घ __s390_compat_sys_##sname(व्योम)

#घोषणा SYSCALL_DEFINE0(sname)						\
	SYSCALL_METADATA(_##sname, 0);					\
	दीर्घ __s390x_sys_##sname(व्योम);					\
	ALLOW_ERROR_INJECTION(__s390x_sys_##sname, ERRNO);		\
	दीर्घ __s390_sys_##sname(व्योम)					\
		__attribute__((alias(__stringअगरy(__s390x_sys_##sname)))); \
	दीर्घ __s390x_sys_##sname(व्योम)

#घोषणा COND_SYSCALL(name)						\
	cond_syscall(__s390x_sys_##name);				\
	cond_syscall(__s390_sys_##name)

#घोषणा SYS_NI(name)							\
	SYSCALL_ALIAS(__s390x_sys_##name, sys_ni_posix_समयrs);		\
	SYSCALL_ALIAS(__s390_sys_##name, sys_ni_posix_समयrs)

#घोषणा COMPAT_SYSCALL_DEFINEx(x, name, ...)						\
	__diag_push();									\
	__diag_ignore(GCC, 8, "-Wattribute-alias",					\
		      "Type aliasing is used to sanitize syscall arguments");		\
	दीर्घ __s390_compat_sys##name(काष्ठा pt_regs *regs);				\
	दीर्घ __s390_compat_sys##name(काष्ठा pt_regs *regs)				\
		__attribute__((alias(__stringअगरy(__se_compat_sys##name))));		\
	ALLOW_ERROR_INJECTION(__s390_compat_sys##name, ERRNO);				\
	अटल अंतरभूत दीर्घ __करो_compat_sys##name(__MAP(x,__SC_DECL,__VA_ARGS__));	\
	दीर्घ __se_compat_sys##name(काष्ठा pt_regs *regs);				\
	दीर्घ __se_compat_sys##name(काष्ठा pt_regs *regs)				\
	अणु										\
		दीर्घ ret = __करो_compat_sys##name(SYSCALL_PT_ARGS(x, regs, __SC_DELOUSE,	\
						 __MAP(x, __SC_TYPE, __VA_ARGS__)));	\
		__MAP(x,__SC_TEST,__VA_ARGS__);						\
		वापस ret;								\
	पूर्ण										\
	__diag_pop();									\
	अटल अंतरभूत दीर्घ __करो_compat_sys##name(__MAP(x,__SC_DECL,__VA_ARGS__))

/*
 * As some compat syscalls may not be implemented, we need to expand
 * COND_SYSCALL_COMPAT in kernel/sys_ni.c and COMPAT_SYS_NI in
 * kernel/समय/posix-stubs.c to cover this हाल as well.
 */
#घोषणा COND_SYSCALL_COMPAT(name)					\
	cond_syscall(__s390_compat_sys_##name)

#घोषणा COMPAT_SYS_NI(name)						\
	SYSCALL_ALIAS(__s390_compat_sys_##name, sys_ni_posix_समयrs)

#अन्यथा /* CONFIG_COMPAT */

#घोषणा __S390_SYS_STUBx(x, fullname, name, ...)

#घोषणा SYSCALL_DEFINE0(sname)						\
	SYSCALL_METADATA(_##sname, 0);					\
	दीर्घ __s390x_sys_##sname(व्योम);					\
	ALLOW_ERROR_INJECTION(__s390x_sys_##sname, ERRNO);		\
	दीर्घ __s390x_sys_##sname(व्योम)

#घोषणा COND_SYSCALL(name)						\
	cond_syscall(__s390x_sys_##name)

#घोषणा SYS_NI(name)							\
	SYSCALL_ALIAS(__s390x_sys_##name, sys_ni_posix_समयrs);

#पूर्ण_अगर /* CONFIG_COMPAT */

#घोषणा __SYSCALL_DEFINEx(x, name, ...)							\
	__diag_push();									\
	__diag_ignore(GCC, 8, "-Wattribute-alias",					\
		      "Type aliasing is used to sanitize syscall arguments");		\
	दीर्घ __s390x_sys##name(काष्ठा pt_regs *regs)					\
		__attribute__((alias(__stringअगरy(__se_sys##name))));			\
	ALLOW_ERROR_INJECTION(__s390x_sys##name, ERRNO);				\
	अटल अंतरभूत दीर्घ __करो_sys##name(__MAP(x,__SC_DECL,__VA_ARGS__));		\
	दीर्घ __se_sys##name(काष्ठा pt_regs *regs);					\
	__S390_SYS_STUBx(x, name, __VA_ARGS__)						\
	दीर्घ __se_sys##name(काष्ठा pt_regs *regs)					\
	अणु										\
		दीर्घ ret = __करो_sys##name(SYSCALL_PT_ARGS(x, regs,			\
				    __SC_CAST, __MAP(x, __SC_TYPE, __VA_ARGS__)));	\
		__MAP(x,__SC_TEST,__VA_ARGS__);						\
		वापस ret;								\
	पूर्ण										\
	__diag_pop();									\
	अटल अंतरभूत दीर्घ __करो_sys##name(__MAP(x,__SC_DECL,__VA_ARGS__))

#पूर्ण_अगर /* _ASM_X86_SYSCALL_WRAPPER_H */
