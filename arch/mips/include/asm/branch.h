<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1996, 1997, 1998, 2001 by Ralf Baechle
 */
#अगर_अघोषित _ASM_BRANCH_H
#घोषणा _ASM_BRANCH_H

#समावेश <यंत्र/cpu-features.h>
#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/inst.h>

बाह्य पूर्णांक __isa_exception_epc(काष्ठा pt_regs *regs);
बाह्य पूर्णांक __compute_वापस_epc(काष्ठा pt_regs *regs);
बाह्य पूर्णांक __compute_वापस_epc_क्रम_insn(काष्ठा pt_regs *regs,
					 जोड़ mips_inकाष्ठाion insn);
बाह्य पूर्णांक __microMIPS_compute_वापस_epc(काष्ठा pt_regs *regs);
बाह्य पूर्णांक __MIPS16e_compute_वापस_epc(काष्ठा pt_regs *regs);

/*
 * microMIPS bitfields
 */
#घोषणा MM_POOL32A_MINOR_MASK	0x3f
#घोषणा MM_POOL32A_MINOR_SHIFT	0x6
#घोषणा MM_MIPS32_COND_FC	0x30

पूर्णांक isBranchInstr(काष्ठा pt_regs *regs,
	काष्ठा mm_decoded_insn dec_insn, अचिन्हित दीर्घ *contpc);

बाह्य पूर्णांक __mm_isBranchInstr(काष्ठा pt_regs *regs,
	काष्ठा mm_decoded_insn dec_insn, अचिन्हित दीर्घ *contpc);

अटल अंतरभूत पूर्णांक mm_isBranchInstr(काष्ठा pt_regs *regs,
	काष्ठा mm_decoded_insn dec_insn, अचिन्हित दीर्घ *contpc)
अणु
	अगर (!cpu_has_mmips)
		वापस 0;

	वापस __mm_isBranchInstr(regs, dec_insn, contpc);
पूर्ण

अटल अंतरभूत पूर्णांक delay_slot(काष्ठा pt_regs *regs)
अणु
	वापस regs->cp0_cause & CAUSEF_BD;
पूर्ण

अटल अंतरभूत व्योम clear_delay_slot(काष्ठा pt_regs *regs)
अणु
	regs->cp0_cause &= ~CAUSEF_BD;
पूर्ण

अटल अंतरभूत व्योम set_delay_slot(काष्ठा pt_regs *regs)
अणु
	regs->cp0_cause |= CAUSEF_BD;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ exception_epc(काष्ठा pt_regs *regs)
अणु
	अगर (likely(!delay_slot(regs)))
		वापस regs->cp0_epc;

	अगर (get_isa16_mode(regs->cp0_epc))
		वापस __isa_exception_epc(regs);

	वापस regs->cp0_epc + 4;
पूर्ण

#घोषणा BRANCH_LIKELY_TAKEN 0x0001

अटल अंतरभूत पूर्णांक compute_वापस_epc(काष्ठा pt_regs *regs)
अणु
	अगर (get_isa16_mode(regs->cp0_epc)) अणु
		अगर (cpu_has_mmips)
			वापस __microMIPS_compute_वापस_epc(regs);
		अगर (cpu_has_mips16)
			वापस __MIPS16e_compute_वापस_epc(regs);
	पूर्ण अन्यथा अगर (!delay_slot(regs)) अणु
		regs->cp0_epc += 4;
		वापस 0;
	पूर्ण

	वापस __compute_वापस_epc(regs);
पूर्ण

अटल अंतरभूत पूर्णांक MIPS16e_compute_वापस_epc(काष्ठा pt_regs *regs,
					     जोड़ mips16e_inकाष्ठाion *inst)
अणु
	अगर (likely(!delay_slot(regs))) अणु
		अगर (inst->ri.opcode == MIPS16e_extend_op) अणु
			regs->cp0_epc += 4;
			वापस 0;
		पूर्ण
		regs->cp0_epc += 2;
		वापस 0;
	पूर्ण

	वापस __MIPS16e_compute_वापस_epc(regs);
पूर्ण

#पूर्ण_अगर /* _ASM_BRANCH_H */
