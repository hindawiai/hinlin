<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_FTRACE
#घोषणा _ASM_POWERPC_FTRACE

#समावेश <यंत्र/types.h>

#अगर_घोषित CONFIG_FUNCTION_TRACER
#घोषणा MCOUNT_ADDR		((अचिन्हित दीर्घ)(_mcount))
#घोषणा MCOUNT_INSN_SIZE	4 /* माप mcount call */

#घोषणा HAVE_FUNCTION_GRAPH_RET_ADDR_PTR

#अगर_घोषित __ASSEMBLY__

/* Based off of objdump output from glibc */

#घोषणा MCOUNT_SAVE_FRAME			\
	stwu	r1,-48(r1);			\
	stw	r3, 12(r1);			\
	stw	r4, 16(r1);			\
	stw	r5, 20(r1);			\
	stw	r6, 24(r1);			\
	mflr	r3;				\
	lwz	r4, 52(r1);			\
	mfcr	r5;				\
	stw	r7, 28(r1);			\
	stw	r8, 32(r1);			\
	stw	r9, 36(r1);			\
	stw	r10,40(r1);			\
	stw	r3, 44(r1);			\
	stw	r5, 8(r1)

#घोषणा MCOUNT_RESTORE_FRAME			\
	lwz	r6, 8(r1);			\
	lwz	r0, 44(r1);			\
	lwz	r3, 12(r1);			\
	mtctr	r0;				\
	lwz	r4, 16(r1);			\
	mtcr	r6;				\
	lwz	r5, 20(r1);			\
	lwz	r6, 24(r1);			\
	lwz	r0, 52(r1);			\
	lwz	r7, 28(r1);			\
	lwz	r8, 32(r1);			\
	mtlr	r0;				\
	lwz	r9, 36(r1);			\
	lwz	r10,40(r1);			\
	addi	r1, r1, 48

#अन्यथा /* !__ASSEMBLY__ */
बाह्य व्योम _mcount(व्योम);

अटल अंतरभूत अचिन्हित दीर्घ ftrace_call_adjust(अचिन्हित दीर्घ addr)
अणु
       /* relocation of mcount call site is the same as the address */
       वापस addr;
पूर्ण

काष्ठा dyn_arch_ftrace अणु
	काष्ठा module *mod;
पूर्ण;
#पूर्ण_अगर /* __ASSEMBLY__ */

#अगर_घोषित CONFIG_DYNAMIC_FTRACE_WITH_REGS
#घोषणा ARCH_SUPPORTS_FTRACE_OPS 1
#पूर्ण_अगर
#पूर्ण_अगर /* CONFIG_FUNCTION_TRACER */

#अगर_अघोषित __ASSEMBLY__
#अगर_घोषित CONFIG_FTRACE_SYSCALLS
/*
 * Some syscall entry functions on घातerpc start with "ppc_" (विभाजन and clone,
 * क्रम instance) or ppc32_/ppc64_. We should also match the sys_ variant with
 * those.
 */
#घोषणा ARCH_HAS_SYSCALL_MATCH_SYM_NAME
#अगर_घोषित PPC64_ELF_ABI_v1
अटल अंतरभूत bool arch_syscall_match_sym_name(स्थिर अक्षर *sym, स्थिर अक्षर *name)
अणु
	/* We need to skip past the initial करोt, and the __se_sys alias */
	वापस !म_भेद(sym + 1, name) ||
		(!म_भेदन(sym, ".__se_sys", 9) && !म_भेद(sym + 6, name)) ||
		(!म_भेदन(sym, ".ppc_", 5) && !म_भेद(sym + 5, name + 4)) ||
		(!म_भेदन(sym, ".ppc32_", 7) && !म_भेद(sym + 7, name + 4)) ||
		(!म_भेदन(sym, ".ppc64_", 7) && !म_भेद(sym + 7, name + 4));
पूर्ण
#अन्यथा
अटल अंतरभूत bool arch_syscall_match_sym_name(स्थिर अक्षर *sym, स्थिर अक्षर *name)
अणु
	वापस !म_भेद(sym, name) ||
		(!म_भेदन(sym, "__se_sys", 8) && !म_भेद(sym + 5, name)) ||
		(!म_भेदन(sym, "ppc_", 4) && !म_भेद(sym + 4, name + 4)) ||
		(!म_भेदन(sym, "ppc32_", 6) && !म_भेद(sym + 6, name + 4)) ||
		(!म_भेदन(sym, "ppc64_", 6) && !म_भेद(sym + 6, name + 4));
पूर्ण
#पूर्ण_अगर /* PPC64_ELF_ABI_v1 */
#पूर्ण_अगर /* CONFIG_FTRACE_SYSCALLS */

#अगर_घोषित CONFIG_PPC64
#समावेश <यंत्र/paca.h>

अटल अंतरभूत व्योम this_cpu_disable_ftrace(व्योम)
अणु
	get_paca()->ftrace_enabled = 0;
पूर्ण

अटल अंतरभूत व्योम this_cpu_enable_ftrace(व्योम)
अणु
	get_paca()->ftrace_enabled = 1;
पूर्ण

/* Disable ftrace on this CPU अगर possible (may not be implemented) */
अटल अंतरभूत व्योम this_cpu_set_ftrace_enabled(u8 ftrace_enabled)
अणु
	get_paca()->ftrace_enabled = ftrace_enabled;
पूर्ण

अटल अंतरभूत u8 this_cpu_get_ftrace_enabled(व्योम)
अणु
	वापस get_paca()->ftrace_enabled;
पूर्ण

#अन्यथा /* CONFIG_PPC64 */
अटल अंतरभूत व्योम this_cpu_disable_ftrace(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम this_cpu_enable_ftrace(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम this_cpu_set_ftrace_enabled(u8 ftrace_enabled) अणु पूर्ण
अटल अंतरभूत u8 this_cpu_get_ftrace_enabled(व्योम) अणु वापस 1; पूर्ण
#पूर्ण_अगर /* CONFIG_PPC64 */
#पूर्ण_अगर /* !__ASSEMBLY__ */

#पूर्ण_अगर /* _ASM_POWERPC_FTRACE */
