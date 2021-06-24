<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_ARM_FTRACE
#घोषणा _ASM_ARM_FTRACE

#अगर_घोषित CONFIG_DYNAMIC_FTRACE_WITH_REGS
#घोषणा ARCH_SUPPORTS_FTRACE_OPS 1
#पूर्ण_अगर

#अगर_घोषित CONFIG_FUNCTION_TRACER
#घोषणा MCOUNT_ADDR		((अचिन्हित दीर्घ)(__gnu_mcount_nc))
#घोषणा MCOUNT_INSN_SIZE	4 /* माप mcount call */

#अगर_अघोषित __ASSEMBLY__
बाह्य व्योम __gnu_mcount_nc(व्योम);

#अगर_घोषित CONFIG_DYNAMIC_FTRACE
काष्ठा dyn_arch_ftrace अणु
पूर्ण;

अटल अंतरभूत अचिन्हित दीर्घ ftrace_call_adjust(अचिन्हित दीर्घ addr)
अणु
	/* With Thumb-2, the recorded addresses have the lsb set */
	वापस addr & ~1;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर

#पूर्ण_अगर

#अगर_अघोषित __ASSEMBLY__

#अगर defined(CONFIG_FRAME_POINTER) && !defined(CONFIG_ARM_UNWIND)
/*
 * वापस_address uses walk_stackframe to करो it's work.  If both
 * CONFIG_FRAME_POINTER=y and CONFIG_ARM_UNWIND=y walk_stackframe uses unwind
 * inक्रमmation.  For this to work in the function tracer many functions would
 * have to be marked with __notrace.  So क्रम now just depend on
 * !CONFIG_ARM_UNWIND.
 */

व्योम *वापस_address(अचिन्हित पूर्णांक);

#अन्यथा

अटल अंतरभूत व्योम *वापस_address(अचिन्हित पूर्णांक level)
अणु
	वापस शून्य;
पूर्ण

#पूर्ण_अगर

#घोषणा ftrace_वापस_address(n) वापस_address(n)

#घोषणा ARCH_HAS_SYSCALL_MATCH_SYM_NAME

अटल अंतरभूत bool arch_syscall_match_sym_name(स्थिर अक्षर *sym,
					       स्थिर अक्षर *name)
अणु
	अगर (!म_भेद(sym, "sys_mmap2"))
		sym = "sys_mmap_pgoff";
	अन्यथा अगर (!म_भेद(sym, "sys_statfs64_wrapper"))
		sym = "sys_statfs64";
	अन्यथा अगर (!म_भेद(sym, "sys_fstatfs64_wrapper"))
		sym = "sys_fstatfs64";
	अन्यथा अगर (!म_भेद(sym, "sys_arm_fadvise64_64"))
		sym = "sys_fadvise64_64";

	/* Ignore हाल since sym may start with "SyS" instead of "sys" */
	वापस !strहालcmp(sym, name);
पूर्ण

#पूर्ण_अगर /* अगरndef __ASSEMBLY__ */

#पूर्ण_अगर /* _ASM_ARM_FTRACE */
