<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+

#समावेश <linux/bitops.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kprobes.h>

#समावेश "decode-insn.h"
#समावेश "simulate-insn.h"

अटल अंतरभूत bool rv_insn_reg_get_val(काष्ठा pt_regs *regs, u32 index,
				       अचिन्हित दीर्घ *ptr)
अणु
	अगर (index == 0)
		*ptr = 0;
	अन्यथा अगर (index <= 31)
		*ptr = *((अचिन्हित दीर्घ *)regs + index);
	अन्यथा
		वापस false;

	वापस true;
पूर्ण

अटल अंतरभूत bool rv_insn_reg_set_val(काष्ठा pt_regs *regs, u32 index,
				       अचिन्हित दीर्घ val)
अणु
	अगर (index == 0)
		वापस false;
	अन्यथा अगर (index <= 31)
		*((अचिन्हित दीर्घ *)regs + index) = val;
	अन्यथा
		वापस false;

	वापस true;
पूर्ण

bool __kprobes simulate_jal(u32 opcode, अचिन्हित दीर्घ addr, काष्ठा pt_regs *regs)
अणु
	/*
	 *     31    30       21    20     19        12 11 7 6      0
	 * imm [20] | imm[10:1] | imm[11] | imm[19:12] | rd | opcode
	 *     1         10          1           8       5    JAL/J
	 */
	bool ret;
	u32 imm;
	u32 index = (opcode >> 7) & 0x1f;

	ret = rv_insn_reg_set_val(regs, index, addr + 4);
	अगर (!ret)
		वापस ret;

	imm  = ((opcode >> 21) & 0x3ff) << 1;
	imm |= ((opcode >> 20) & 0x1)   << 11;
	imm |= ((opcode >> 12) & 0xff)  << 12;
	imm |= ((opcode >> 31) & 0x1)   << 20;

	inकाष्ठाion_poपूर्णांकer_set(regs, addr + sign_extend32((imm), 20));

	वापस ret;
पूर्ण

bool __kprobes simulate_jalr(u32 opcode, अचिन्हित दीर्घ addr, काष्ठा pt_regs *regs)
अणु
	/*
	 * 31          20 19 15 14 12 11 7 6      0
	 *  offset[11:0] | rs1 | 010 | rd | opcode
	 *      12         5      3    5    JALR/JR
	 */
	bool ret;
	अचिन्हित दीर्घ base_addr;
	u32 imm = (opcode >> 20) & 0xfff;
	u32 rd_index = (opcode >> 7) & 0x1f;
	u32 rs1_index = (opcode >> 15) & 0x1f;

	ret = rv_insn_reg_set_val(regs, rd_index, addr + 4);
	अगर (!ret)
		वापस ret;

	ret = rv_insn_reg_get_val(regs, rs1_index, &base_addr);
	अगर (!ret)
		वापस ret;

	inकाष्ठाion_poपूर्णांकer_set(regs, (base_addr + sign_extend32((imm), 11))&~1);

	वापस ret;
पूर्ण
