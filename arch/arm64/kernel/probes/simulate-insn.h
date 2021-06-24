<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * arch/arm64/kernel/probes/simulate-insn.h
 *
 * Copyright (C) 2013 Linaro Limited
 */

#अगर_अघोषित _ARM_KERNEL_KPROBES_SIMULATE_INSN_H
#घोषणा _ARM_KERNEL_KPROBES_SIMULATE_INSN_H

व्योम simulate_adr_adrp(u32 opcode, दीर्घ addr, काष्ठा pt_regs *regs);
व्योम simulate_b_bl(u32 opcode, दीर्घ addr, काष्ठा pt_regs *regs);
व्योम simulate_b_cond(u32 opcode, दीर्घ addr, काष्ठा pt_regs *regs);
व्योम simulate_br_blr_ret(u32 opcode, दीर्घ addr, काष्ठा pt_regs *regs);
व्योम simulate_cbz_cbnz(u32 opcode, दीर्घ addr, काष्ठा pt_regs *regs);
व्योम simulate_tbz_tbnz(u32 opcode, दीर्घ addr, काष्ठा pt_regs *regs);
व्योम simulate_ldr_literal(u32 opcode, दीर्घ addr, काष्ठा pt_regs *regs);
व्योम simulate_ldrsw_literal(u32 opcode, दीर्घ addr, काष्ठा pt_regs *regs);

#पूर्ण_अगर /* _ARM_KERNEL_KPROBES_SIMULATE_INSN_H */
