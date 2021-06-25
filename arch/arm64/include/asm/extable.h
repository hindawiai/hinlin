<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_EXTABLE_H
#घोषणा __ASM_EXTABLE_H

/*
 * The exception table consists of pairs of relative offsets: the first
 * is the relative offset to an inकाष्ठाion that is allowed to fault,
 * and the second is the relative offset at which the program should
 * जारी. No रेजिस्टरs are modअगरied, so it is entirely up to the
 * continuation code to figure out what to करो.
 *
 * All the routines below use bits of fixup code that are out of line
 * with the मुख्य inकाष्ठाion path.  This means when everything is well,
 * we करोn't even have to jump over them.  Further, they करो not पूर्णांकrude
 * on our cache or tlb entries.
 */

काष्ठा exception_table_entry
अणु
	पूर्णांक insn, fixup;
पूर्ण;

#घोषणा ARCH_HAS_RELATIVE_EXTABLE

अटल अंतरभूत bool in_bpf_jit(काष्ठा pt_regs *regs)
अणु
	अगर (!IS_ENABLED(CONFIG_BPF_JIT))
		वापस false;

	वापस regs->pc >= BPF_JIT_REGION_START &&
	       regs->pc < BPF_JIT_REGION_END;
पूर्ण

#अगर_घोषित CONFIG_BPF_JIT
पूर्णांक arm64_bpf_fixup_exception(स्थिर काष्ठा exception_table_entry *ex,
			      काष्ठा pt_regs *regs);
#अन्यथा /* !CONFIG_BPF_JIT */
अटल अंतरभूत
पूर्णांक arm64_bpf_fixup_exception(स्थिर काष्ठा exception_table_entry *ex,
			      काष्ठा pt_regs *regs)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* !CONFIG_BPF_JIT */

बाह्य पूर्णांक fixup_exception(काष्ठा pt_regs *regs);
#पूर्ण_अगर
