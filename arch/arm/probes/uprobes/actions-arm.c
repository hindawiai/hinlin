<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012 Rabin Vincent <rabin at rab.in>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/रुको.h>
#समावेश <linux/uprobes.h>
#समावेश <linux/module.h>

#समावेश "../decode.h"
#समावेश "../decode-arm.h"
#समावेश "core.h"

अटल पूर्णांक uprobes_substitute_pc(अचिन्हित दीर्घ *pinsn, u32 oregs)
अणु
	probes_opcode_t insn = __mem_to_opcode_arm(*pinsn);
	probes_opcode_t temp;
	probes_opcode_t mask;
	पूर्णांक मुक्तreg;
	u32 मुक्त = 0xffff;
	u32 regs;

	क्रम (regs = oregs; regs; regs >>= 4, insn >>= 4) अणु
		अगर ((regs & 0xf) == REG_TYPE_NONE)
			जारी;

		मुक्त &= ~(1 << (insn & 0xf));
	पूर्ण

	/* No PC, no problem */
	अगर (मुक्त & (1 << 15))
		वापस 15;

	अगर (!मुक्त)
		वापस -1;

	/*
	 * fls instead of ffs ensures that क्रम "ldrd r0, r1, [pc]" we would
	 * pick LR instead of R1.
	 */
	मुक्तreg = मुक्त = fls(मुक्त) - 1;

	temp = __mem_to_opcode_arm(*pinsn);
	insn = temp;
	regs = oregs;
	mask = 0xf;

	क्रम (; regs; regs >>= 4, mask <<= 4, मुक्त <<= 4, temp >>= 4) अणु
		अगर ((regs & 0xf) == REG_TYPE_NONE)
			जारी;

		अगर ((temp & 0xf) != 15)
			जारी;

		insn &= ~mask;
		insn |= मुक्त & mask;
	पूर्ण

	*pinsn = __opcode_to_mem_arm(insn);
	वापस मुक्तreg;
पूर्ण

अटल व्योम uprobe_set_pc(काष्ठा arch_uprobe *auprobe,
			  काष्ठा arch_uprobe_task *autask,
			  काष्ठा pt_regs *regs)
अणु
	u32 pcreg = auprobe->pcreg;

	autask->backup = regs->uregs[pcreg];
	regs->uregs[pcreg] = regs->ARM_pc + 8;
पूर्ण

अटल व्योम uprobe_unset_pc(काष्ठा arch_uprobe *auprobe,
			    काष्ठा arch_uprobe_task *autask,
			    काष्ठा pt_regs *regs)
अणु
	/* PC will be taken care of by common code */
	regs->uregs[auprobe->pcreg] = autask->backup;
पूर्ण

अटल व्योम uprobe_aluग_लिखो_pc(काष्ठा arch_uprobe *auprobe,
			       काष्ठा arch_uprobe_task *autask,
			       काष्ठा pt_regs *regs)
अणु
	u32 pcreg = auprobe->pcreg;

	alu_ग_लिखो_pc(regs->uregs[pcreg], regs);
	regs->uregs[pcreg] = autask->backup;
पूर्ण

अटल व्योम uprobe_ग_लिखो_pc(काष्ठा arch_uprobe *auprobe,
			    काष्ठा arch_uprobe_task *autask,
			    काष्ठा pt_regs *regs)
अणु
	u32 pcreg = auprobe->pcreg;

	load_ग_लिखो_pc(regs->uregs[pcreg], regs);
	regs->uregs[pcreg] = autask->backup;
पूर्ण

क्रमागत probes_insn
decode_pc_ro(probes_opcode_t insn, काष्ठा arch_probes_insn *asi,
	     स्थिर काष्ठा decode_header *d)
अणु
	काष्ठा arch_uprobe *auprobe = container_of(asi, काष्ठा arch_uprobe,
						   asi);
	काष्ठा decode_emulate *decode = (काष्ठा decode_emulate *) d;
	u32 regs = decode->header.type_regs.bits >> DECODE_TYPE_BITS;
	पूर्णांक reg;

	reg = uprobes_substitute_pc(&auprobe->ixol[0], regs);
	अगर (reg == 15)
		वापस INSN_GOOD;

	अगर (reg == -1)
		वापस INSN_REJECTED;

	auprobe->pcreg = reg;
	auprobe->prehandler = uprobe_set_pc;
	auprobe->posthandler = uprobe_unset_pc;

	वापस INSN_GOOD;
पूर्ण

क्रमागत probes_insn
decode_wb_pc(probes_opcode_t insn, काष्ठा arch_probes_insn *asi,
	     स्थिर काष्ठा decode_header *d, bool alu)
अणु
	काष्ठा arch_uprobe *auprobe = container_of(asi, काष्ठा arch_uprobe,
						   asi);
	क्रमागत probes_insn ret = decode_pc_ro(insn, asi, d);

	अगर (((insn >> 12) & 0xf) == 15)
		auprobe->posthandler = alu ? uprobe_aluग_लिखो_pc
					   : uprobe_ग_लिखो_pc;

	वापस ret;
पूर्ण

क्रमागत probes_insn
decode_rd12rn16rm0rs8_rwflags(probes_opcode_t insn,
			      काष्ठा arch_probes_insn *asi,
			      स्थिर काष्ठा decode_header *d)
अणु
	वापस decode_wb_pc(insn, asi, d, true);
पूर्ण

क्रमागत probes_insn
decode_ldr(probes_opcode_t insn, काष्ठा arch_probes_insn *asi,
	   स्थिर काष्ठा decode_header *d)
अणु
	वापस decode_wb_pc(insn, asi, d, false);
पूर्ण

क्रमागत probes_insn
uprobe_decode_ldmsपंचांग(probes_opcode_t insn,
		     काष्ठा arch_probes_insn *asi,
		     स्थिर काष्ठा decode_header *d)
अणु
	काष्ठा arch_uprobe *auprobe = container_of(asi, काष्ठा arch_uprobe,
						   asi);
	अचिन्हित reglist = insn & 0xffff;
	पूर्णांक rn = (insn >> 16) & 0xf;
	पूर्णांक lbit = insn & (1 << 20);
	अचिन्हित used = reglist | (1 << rn);

	अगर (rn == 15)
		वापस INSN_REJECTED;

	अगर (!(used & (1 << 15)))
		वापस INSN_GOOD;

	अगर (used & (1 << 14))
		वापस INSN_REJECTED;

	/* Use LR instead of PC */
	insn ^= 0xc000;

	auprobe->pcreg = 14;
	auprobe->ixol[0] = __opcode_to_mem_arm(insn);

	auprobe->prehandler = uprobe_set_pc;
	अगर (lbit)
		auprobe->posthandler = uprobe_ग_लिखो_pc;
	अन्यथा
		auprobe->posthandler = uprobe_unset_pc;

	वापस INSN_GOOD;
पूर्ण

स्थिर जोड़ decode_action uprobes_probes_actions[] = अणु
	[PROBES_PRELOAD_IMM] = अणु.handler = probes_simulate_nopपूर्ण,
	[PROBES_PRELOAD_REG] = अणु.handler = probes_simulate_nopपूर्ण,
	[PROBES_BRANCH_IMM] = अणु.handler = simulate_blx1पूर्ण,
	[PROBES_MRS] = अणु.handler = simulate_mrsपूर्ण,
	[PROBES_BRANCH_REG] = अणु.handler = simulate_blx2bxपूर्ण,
	[PROBES_CLZ] = अणु.handler = probes_simulate_nopपूर्ण,
	[PROBES_SATURATING_ARITHMETIC] = अणु.handler = probes_simulate_nopपूर्ण,
	[PROBES_MUL1] = अणु.handler = probes_simulate_nopपूर्ण,
	[PROBES_MUL2] = अणु.handler = probes_simulate_nopपूर्ण,
	[PROBES_SWP] = अणु.handler = probes_simulate_nopपूर्ण,
	[PROBES_LDRSTRD] = अणु.decoder = decode_pc_roपूर्ण,
	[PROBES_LOAD_EXTRA] = अणु.decoder = decode_pc_roपूर्ण,
	[PROBES_LOAD] = अणु.decoder = decode_ldrपूर्ण,
	[PROBES_STORE_EXTRA] = अणु.decoder = decode_pc_roपूर्ण,
	[PROBES_STORE] = अणु.decoder = decode_pc_roपूर्ण,
	[PROBES_MOV_IP_SP] = अणु.handler = simulate_mov_ipspपूर्ण,
	[PROBES_DATA_PROCESSING_REG] = अणु
		.decoder = decode_rd12rn16rm0rs8_rwflagsपूर्ण,
	[PROBES_DATA_PROCESSING_IMM] = अणु
		.decoder = decode_rd12rn16rm0rs8_rwflagsपूर्ण,
	[PROBES_MOV_HALFWORD] = अणु.handler = probes_simulate_nopपूर्ण,
	[PROBES_SEV] = अणु.handler = probes_simulate_nopपूर्ण,
	[PROBES_WFE] = अणु.handler = probes_simulate_nopपूर्ण,
	[PROBES_SATURATE] = अणु.handler = probes_simulate_nopपूर्ण,
	[PROBES_REV] = अणु.handler = probes_simulate_nopपूर्ण,
	[PROBES_MMI] = अणु.handler = probes_simulate_nopपूर्ण,
	[PROBES_PACK] = अणु.handler = probes_simulate_nopपूर्ण,
	[PROBES_EXTEND] = अणु.handler = probes_simulate_nopपूर्ण,
	[PROBES_EXTEND_ADD] = अणु.handler = probes_simulate_nopपूर्ण,
	[PROBES_MUL_ADD_LONG] = अणु.handler = probes_simulate_nopपूर्ण,
	[PROBES_MUL_ADD] = अणु.handler = probes_simulate_nopपूर्ण,
	[PROBES_BITFIELD] = अणु.handler = probes_simulate_nopपूर्ण,
	[PROBES_BRANCH] = अणु.handler = simulate_bblपूर्ण,
	[PROBES_LDMSTM] = अणु.decoder = uprobe_decode_ldmsपंचांगपूर्ण
पूर्ण;
