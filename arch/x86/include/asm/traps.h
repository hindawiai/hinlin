<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_TRAPS_H
#घोषणा _ASM_X86_TRAPS_H

#समावेश <linux/context_tracking_state.h>
#समावेश <linux/kprobes.h>

#समावेश <यंत्र/debugreg.h>
#समावेश <यंत्र/idtentry.h>
#समावेश <यंत्र/siginfo.h>			/* TRAP_TRACE, ... */
#समावेश <यंत्र/trap_pf.h>

#अगर_घोषित CONFIG_X86_64
यंत्रlinkage __visible notrace काष्ठा pt_regs *sync_regs(काष्ठा pt_regs *eregs);
यंत्रlinkage __visible notrace
काष्ठा bad_iret_stack *fixup_bad_iret(काष्ठा bad_iret_stack *s);
व्योम __init trap_init(व्योम);
यंत्रlinkage __visible noinstr काष्ठा pt_regs *vc_चयन_off_ist(काष्ठा pt_regs *eregs);
#पूर्ण_अगर

#अगर_घोषित CONFIG_X86_F00F_BUG
/* For handling the FOOF bug */
व्योम handle_invalid_op(काष्ठा pt_regs *regs);
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक get_si_code(अचिन्हित दीर्घ condition)
अणु
	अगर (condition & DR_STEP)
		वापस TRAP_TRACE;
	अन्यथा अगर (condition & (DR_TRAP0|DR_TRAP1|DR_TRAP2|DR_TRAP3))
		वापस TRAP_HWBKPT;
	अन्यथा
		वापस TRAP_BRKPT;
पूर्ण

बाह्य पूर्णांक panic_on_unrecovered_nmi;

व्योम math_emulate(काष्ठा math_emu_info *);

bool fault_in_kernel_space(अचिन्हित दीर्घ address);

#अगर_घोषित CONFIG_VMAP_STACK
व्योम __noवापस handle_stack_overflow(स्थिर अक्षर *message,
				      काष्ठा pt_regs *regs,
				      अचिन्हित दीर्घ fault_address);
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_X86_TRAPS_H */
