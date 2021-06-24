<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * syscall_wrapper.h - arm64 specअगरic wrappers to syscall definitions
 *
 * Based on arch/x86/include/यंत्र_syscall_wrapper.h
 */

#अगर_अघोषित __ASM_SYSCALL_WRAPPER_H
#घोषणा __ASM_SYSCALL_WRAPPER_H

काष्ठा pt_regs;

#घोषणा SC_ARM64_REGS_TO_ARGS(x, ...)				\
	__MAP(x,__SC_ARGS					\
	      ,,regs->regs[0],,regs->regs[1],,regs->regs[2]	\
	      ,,regs->regs[3],,regs->regs[4],,regs->regs[5])

#अगर_घोषित CONFIG_COMPAT

#घोषणा COMPAT_SYSCALL_DEFINEx(x, name, ...)						\
	यंत्रlinkage दीर्घ __arm64_compat_sys##name(स्थिर काष्ठा pt_regs *regs);		\
	ALLOW_ERROR_INJECTION(__arm64_compat_sys##name, ERRNO);				\
	अटल दीर्घ __se_compat_sys##name(__MAP(x,__SC_LONG,__VA_ARGS__));		\
	अटल अंतरभूत दीर्घ __करो_compat_sys##name(__MAP(x,__SC_DECL,__VA_ARGS__));	\
	यंत्रlinkage दीर्घ __arm64_compat_sys##name(स्थिर काष्ठा pt_regs *regs)		\
	अणु										\
		वापस __se_compat_sys##name(SC_ARM64_REGS_TO_ARGS(x,__VA_ARGS__));	\
	पूर्ण										\
	अटल दीर्घ __se_compat_sys##name(__MAP(x,__SC_LONG,__VA_ARGS__))		\
	अणु										\
		वापस __करो_compat_sys##name(__MAP(x,__SC_DELOUSE,__VA_ARGS__));	\
	पूर्ण										\
	अटल अंतरभूत दीर्घ __करो_compat_sys##name(__MAP(x,__SC_DECL,__VA_ARGS__))

#घोषणा COMPAT_SYSCALL_DEFINE0(sname)							\
	यंत्रlinkage दीर्घ __arm64_compat_sys_##sname(स्थिर काष्ठा pt_regs *__unused);	\
	ALLOW_ERROR_INJECTION(__arm64_compat_sys_##sname, ERRNO);			\
	यंत्रlinkage दीर्घ __arm64_compat_sys_##sname(स्थिर काष्ठा pt_regs *__unused)

#घोषणा COND_SYSCALL_COMPAT(name) 							\
	यंत्रlinkage दीर्घ __weak __arm64_compat_sys_##name(स्थिर काष्ठा pt_regs *regs)	\
	अणु										\
		वापस sys_ni_syscall();						\
	पूर्ण

#घोषणा COMPAT_SYS_NI(name) \
	SYSCALL_ALIAS(__arm64_compat_sys_##name, sys_ni_posix_समयrs);

#पूर्ण_अगर /* CONFIG_COMPAT */

#घोषणा __SYSCALL_DEFINEx(x, name, ...)						\
	यंत्रlinkage दीर्घ __arm64_sys##name(स्थिर काष्ठा pt_regs *regs);		\
	ALLOW_ERROR_INJECTION(__arm64_sys##name, ERRNO);			\
	अटल दीर्घ __se_sys##name(__MAP(x,__SC_LONG,__VA_ARGS__));		\
	अटल अंतरभूत दीर्घ __करो_sys##name(__MAP(x,__SC_DECL,__VA_ARGS__));	\
	यंत्रlinkage दीर्घ __arm64_sys##name(स्थिर काष्ठा pt_regs *regs)		\
	अणु									\
		वापस __se_sys##name(SC_ARM64_REGS_TO_ARGS(x,__VA_ARGS__));	\
	पूर्ण									\
	अटल दीर्घ __se_sys##name(__MAP(x,__SC_LONG,__VA_ARGS__))		\
	अणु									\
		दीर्घ ret = __करो_sys##name(__MAP(x,__SC_CAST,__VA_ARGS__));	\
		__MAP(x,__SC_TEST,__VA_ARGS__);					\
		__PROTECT(x, ret,__MAP(x,__SC_ARGS,__VA_ARGS__));		\
		वापस ret;							\
	पूर्ण									\
	अटल अंतरभूत दीर्घ __करो_sys##name(__MAP(x,__SC_DECL,__VA_ARGS__))

#घोषणा SYSCALL_DEFINE0(sname)							\
	SYSCALL_METADATA(_##sname, 0);						\
	यंत्रlinkage दीर्घ __arm64_sys_##sname(स्थिर काष्ठा pt_regs *__unused);	\
	ALLOW_ERROR_INJECTION(__arm64_sys_##sname, ERRNO);			\
	यंत्रlinkage दीर्घ __arm64_sys_##sname(स्थिर काष्ठा pt_regs *__unused)

#घोषणा COND_SYSCALL(name)							\
	यंत्रlinkage दीर्घ __weak __arm64_sys_##name(स्थिर काष्ठा pt_regs *regs)	\
	अणु									\
		वापस sys_ni_syscall();					\
	पूर्ण

#घोषणा SYS_NI(name) SYSCALL_ALIAS(__arm64_sys_##name, sys_ni_posix_समयrs);

#पूर्ण_अगर /* __ASM_SYSCALL_WRAPPER_H */
