<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * arch/arm64/kernel/probes/simulate-insn.c
 *
 * Copyright (C) 2013 Linaro Limited.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kprobes.h>

#समावेश <यंत्र/ptrace.h>

#समावेश "simulate-insn.h"

#घोषणा bbl_displacement(insn)		\
	sign_extend32(((insn) & 0x3ffffff) << 2, 27)

#घोषणा bcond_displacement(insn)	\
	sign_extend32(((insn >> 5) & 0x7ffff) << 2, 20)

#घोषणा cbz_displacement(insn)	\
	sign_extend32(((insn >> 5) & 0x7ffff) << 2, 20)

#घोषणा tbz_displacement(insn)	\
	sign_extend32(((insn >> 5) & 0x3fff) << 2, 15)

#घोषणा ldr_displacement(insn)	\
	sign_extend32(((insn >> 5) & 0x7ffff) << 2, 20)

अटल अंतरभूत व्योम set_x_reg(काष्ठा pt_regs *regs, पूर्णांक reg, u64 val)
अणु
	pt_regs_ग_लिखो_reg(regs, reg, val);
पूर्ण

अटल अंतरभूत व्योम set_w_reg(काष्ठा pt_regs *regs, पूर्णांक reg, u64 val)
अणु
	pt_regs_ग_लिखो_reg(regs, reg, lower_32_bits(val));
पूर्ण

अटल अंतरभूत u64 get_x_reg(काष्ठा pt_regs *regs, पूर्णांक reg)
अणु
	वापस pt_regs_पढ़ो_reg(regs, reg);
पूर्ण

अटल अंतरभूत u32 get_w_reg(काष्ठा pt_regs *regs, पूर्णांक reg)
अणु
	वापस lower_32_bits(pt_regs_पढ़ो_reg(regs, reg));
पूर्ण

अटल bool __kprobes check_cbz(u32 opcode, काष्ठा pt_regs *regs)
अणु
	पूर्णांक xn = opcode & 0x1f;

	वापस (opcode & (1 << 31)) ?
	    (get_x_reg(regs, xn) == 0) : (get_w_reg(regs, xn) == 0);
पूर्ण

अटल bool __kprobes check_cbnz(u32 opcode, काष्ठा pt_regs *regs)
अणु
	पूर्णांक xn = opcode & 0x1f;

	वापस (opcode & (1 << 31)) ?
	    (get_x_reg(regs, xn) != 0) : (get_w_reg(regs, xn) != 0);
पूर्ण

अटल bool __kprobes check_tbz(u32 opcode, काष्ठा pt_regs *regs)
अणु
	पूर्णांक xn = opcode & 0x1f;
	पूर्णांक bit_pos = ((opcode & (1 << 31)) >> 26) | ((opcode >> 19) & 0x1f);

	वापस ((get_x_reg(regs, xn) >> bit_pos) & 0x1) == 0;
पूर्ण

अटल bool __kprobes check_tbnz(u32 opcode, काष्ठा pt_regs *regs)
अणु
	पूर्णांक xn = opcode & 0x1f;
	पूर्णांक bit_pos = ((opcode & (1 << 31)) >> 26) | ((opcode >> 19) & 0x1f);

	वापस ((get_x_reg(regs, xn) >> bit_pos) & 0x1) != 0;
पूर्ण

/*
 * inकाष्ठाion simulation functions
 */
व्योम __kprobes
simulate_adr_adrp(u32 opcode, दीर्घ addr, काष्ठा pt_regs *regs)
अणु
	दीर्घ imm, xn, val;

	xn = opcode & 0x1f;
	imm = ((opcode >> 3) & 0x1ffffc) | ((opcode >> 29) & 0x3);
	imm = sign_extend64(imm, 20);
	अगर (opcode & 0x80000000)
		val = (imm<<12) + (addr & 0xfffffffffffff000);
	अन्यथा
		val = imm + addr;

	set_x_reg(regs, xn, val);

	inकाष्ठाion_poपूर्णांकer_set(regs, inकाष्ठाion_poपूर्णांकer(regs) + 4);
पूर्ण

व्योम __kprobes
simulate_b_bl(u32 opcode, दीर्घ addr, काष्ठा pt_regs *regs)
अणु
	पूर्णांक disp = bbl_displacement(opcode);

	/* Link रेजिस्टर is x30 */
	अगर (opcode & (1 << 31))
		set_x_reg(regs, 30, addr + 4);

	inकाष्ठाion_poपूर्णांकer_set(regs, addr + disp);
पूर्ण

व्योम __kprobes
simulate_b_cond(u32 opcode, दीर्घ addr, काष्ठा pt_regs *regs)
अणु
	पूर्णांक disp = 4;

	अगर (aarch32_opcode_cond_checks[opcode & 0xf](regs->pstate & 0xffffffff))
		disp = bcond_displacement(opcode);

	inकाष्ठाion_poपूर्णांकer_set(regs, addr + disp);
पूर्ण

व्योम __kprobes
simulate_br_blr_ret(u32 opcode, दीर्घ addr, काष्ठा pt_regs *regs)
अणु
	पूर्णांक xn = (opcode >> 5) & 0x1f;

	/* update pc first in हाल we're करोing a "blr lr" */
	inकाष्ठाion_poपूर्णांकer_set(regs, get_x_reg(regs, xn));

	/* Link रेजिस्टर is x30 */
	अगर (((opcode >> 21) & 0x3) == 1)
		set_x_reg(regs, 30, addr + 4);
पूर्ण

व्योम __kprobes
simulate_cbz_cbnz(u32 opcode, दीर्घ addr, काष्ठा pt_regs *regs)
अणु
	पूर्णांक disp = 4;

	अगर (opcode & (1 << 24)) अणु
		अगर (check_cbnz(opcode, regs))
			disp = cbz_displacement(opcode);
	पूर्ण अन्यथा अणु
		अगर (check_cbz(opcode, regs))
			disp = cbz_displacement(opcode);
	पूर्ण
	inकाष्ठाion_poपूर्णांकer_set(regs, addr + disp);
पूर्ण

व्योम __kprobes
simulate_tbz_tbnz(u32 opcode, दीर्घ addr, काष्ठा pt_regs *regs)
अणु
	पूर्णांक disp = 4;

	अगर (opcode & (1 << 24)) अणु
		अगर (check_tbnz(opcode, regs))
			disp = tbz_displacement(opcode);
	पूर्ण अन्यथा अणु
		अगर (check_tbz(opcode, regs))
			disp = tbz_displacement(opcode);
	पूर्ण
	inकाष्ठाion_poपूर्णांकer_set(regs, addr + disp);
पूर्ण

व्योम __kprobes
simulate_ldr_literal(u32 opcode, दीर्घ addr, काष्ठा pt_regs *regs)
अणु
	u64 *load_addr;
	पूर्णांक xn = opcode & 0x1f;
	पूर्णांक disp;

	disp = ldr_displacement(opcode);
	load_addr = (u64 *) (addr + disp);

	अगर (opcode & (1 << 30))	/* x0-x30 */
		set_x_reg(regs, xn, *load_addr);
	अन्यथा			/* w0-w30 */
		set_w_reg(regs, xn, *load_addr);

	inकाष्ठाion_poपूर्णांकer_set(regs, inकाष्ठाion_poपूर्णांकer(regs) + 4);
पूर्ण

व्योम __kprobes
simulate_ldrsw_literal(u32 opcode, दीर्घ addr, काष्ठा pt_regs *regs)
अणु
	s32 *load_addr;
	पूर्णांक xn = opcode & 0x1f;
	पूर्णांक disp;

	disp = ldr_displacement(opcode);
	load_addr = (s32 *) (addr + disp);

	set_x_reg(regs, xn, *load_addr);

	inकाष्ठाion_poपूर्णांकer_set(regs, inकाष्ठाion_poपूर्णांकer(regs) + 4);
पूर्ण
