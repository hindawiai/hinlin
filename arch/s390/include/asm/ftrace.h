<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_S390_FTRACE_H
#घोषणा _ASM_S390_FTRACE_H

#घोषणा HAVE_FUNCTION_GRAPH_RET_ADDR_PTR
#घोषणा ARCH_SUPPORTS_FTRACE_OPS 1
#घोषणा MCOUNT_INSN_SIZE	6

#अगर_अघोषित __ASSEMBLY__

#अगर_घोषित CONFIG_CC_IS_CLANG
/* https://bugs.llvm.org/show_bug.cgi?id=41424 */
#घोषणा ftrace_वापस_address(n) 0UL
#अन्यथा
#घोषणा ftrace_वापस_address(n) __builtin_वापस_address(n)
#पूर्ण_अगर

व्योम ftrace_caller(व्योम);

बाह्य अक्षर ftrace_graph_caller_end;
बाह्य अचिन्हित दीर्घ ftrace_plt;

काष्ठा dyn_arch_ftrace अणु पूर्ण;

#घोषणा MCOUNT_ADDR 0
#घोषणा FTRACE_ADDR ((अचिन्हित दीर्घ)ftrace_caller)

#घोषणा KPROBE_ON_FTRACE_NOP	0
#घोषणा KPROBE_ON_FTRACE_CALL	1

काष्ठा module;
काष्ठा dyn_ftrace;
/*
 * Either -mhotpatch or -mnop-mcount is used - no explicit init is required
 */
अटल अंतरभूत पूर्णांक ftrace_init_nop(काष्ठा module *mod, काष्ठा dyn_ftrace *rec) अणु वापस 0; पूर्ण
#घोषणा ftrace_init_nop ftrace_init_nop

अटल अंतरभूत अचिन्हित दीर्घ ftrace_call_adjust(अचिन्हित दीर्घ addr)
अणु
	वापस addr;
पूर्ण

काष्ठा ftrace_insn अणु
	u16 opc;
	s32 disp;
पूर्ण __packed;

अटल अंतरभूत व्योम ftrace_generate_nop_insn(काष्ठा ftrace_insn *insn)
अणु
#अगर_घोषित CONFIG_FUNCTION_TRACER
	/* brcl 0,0 */
	insn->opc = 0xc004;
	insn->disp = 0;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत पूर्णांक is_ftrace_nop(काष्ठा ftrace_insn *insn)
अणु
#अगर_घोषित CONFIG_FUNCTION_TRACER
	अगर (insn->disp == 0)
		वापस 1;
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ftrace_generate_call_insn(काष्ठा ftrace_insn *insn,
					     अचिन्हित दीर्घ ip)
अणु
#अगर_घोषित CONFIG_FUNCTION_TRACER
	अचिन्हित दीर्घ target;

	/* brasl r0,ftrace_caller */
	target = is_module_addr((व्योम *) ip) ? ftrace_plt : FTRACE_ADDR;
	insn->opc = 0xc005;
	insn->disp = (target - ip) / 2;
#पूर्ण_अगर
पूर्ण

/*
 * Even though the प्रणाली call numbers are identical क्रम s390/s390x a
 * dअगरferent प्रणाली call table is used क्रम compat tasks. This may lead
 * to e.g. incorrect or missing trace event sysfs files.
 * Thereक्रमe simply करो not trace compat प्रणाली calls at all.
 * See kernel/trace/trace_syscalls.c.
 */
#घोषणा ARCH_TRACE_IGNORE_COMPAT_SYSCALLS
अटल अंतरभूत bool arch_trace_is_compat_syscall(काष्ठा pt_regs *regs)
अणु
	वापस is_compat_task();
पूर्ण

#घोषणा ARCH_HAS_SYSCALL_MATCH_SYM_NAME
अटल अंतरभूत bool arch_syscall_match_sym_name(स्थिर अक्षर *sym,
					       स्थिर अक्षर *name)
अणु
	/*
	 * Skip __s390_ and __s390x_ prefix - due to compat wrappers
	 * and aliasing some symbols of 64 bit प्रणाली call functions
	 * may get the __s390_ prefix instead of the __s390x_ prefix.
	 */
	वापस !म_भेद(sym + 7, name) || !म_भेद(sym + 8, name);
पूर्ण

#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* _ASM_S390_FTRACE_H */
