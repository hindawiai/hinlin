<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 ARM Ltd.
 */
#अगर_अघोषित __ASM_DEBUG_MONITORS_H
#घोषणा __ASM_DEBUG_MONITORS_H

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <यंत्र/brk-imm.h>
#समावेश <यंत्र/esr.h>
#समावेश <यंत्र/insn.h>
#समावेश <यंत्र/ptrace.h>

/* Low-level stepping controls. */
#घोषणा DBG_MDSCR_SS		(1 << 0)
#घोषणा DBG_SPSR_SS		(1 << 21)

/* MDSCR_EL1 enabling bits */
#घोषणा DBG_MDSCR_KDE		(1 << 13)
#घोषणा DBG_MDSCR_MDE		(1 << 15)
#घोषणा DBG_MDSCR_MASK		~(DBG_MDSCR_KDE | DBG_MDSCR_MDE)

#घोषणा	DBG_ESR_EVT(x)		(((x) >> 27) & 0x7)

/* AArch64 */
#घोषणा DBG_ESR_EVT_HWBP	0x0
#घोषणा DBG_ESR_EVT_HWSS	0x1
#घोषणा DBG_ESR_EVT_HWWP	0x2
#घोषणा DBG_ESR_EVT_BRK		0x6

/*
 * Break poपूर्णांक inकाष्ठाion encoding
 */
#घोषणा BREAK_INSTR_SIZE		AARCH64_INSN_SIZE

/*
 * BRK inकाष्ठाion encoding
 * The #imm16 value should be placed at bits[20:5] within BRK ins
 */
#घोषणा AARCH64_BREAK_MON	0xd4200000

/*
 * BRK inकाष्ठाion क्रम provoking a fault on purpose
 * Unlike kgdb, #imm16 value with unallocated handler is used क्रम faulting.
 */
#घोषणा AARCH64_BREAK_FAULT	(AARCH64_BREAK_MON | (FAULT_BRK_IMM << 5))

#घोषणा AARCH64_BREAK_KGDB_DYN_DBG	\
	(AARCH64_BREAK_MON | (KGDB_DYN_DBG_BRK_IMM << 5))

#घोषणा CACHE_FLUSH_IS_SAFE		1

/* kprobes BRK opcodes with ESR encoding  */
#घोषणा BRK64_OPCODE_KPROBES	(AARCH64_BREAK_MON | (KPROBES_BRK_IMM << 5))
#घोषणा BRK64_OPCODE_KPROBES_SS	(AARCH64_BREAK_MON | (KPROBES_BRK_SS_IMM << 5))
/* uprobes BRK opcodes with ESR encoding  */
#घोषणा BRK64_OPCODE_UPROBES	(AARCH64_BREAK_MON | (UPROBES_BRK_IMM << 5))

/* AArch32 */
#घोषणा DBG_ESR_EVT_BKPT	0x4
#घोषणा DBG_ESR_EVT_VECC	0x5

#घोषणा AARCH32_BREAK_ARM	0x07f001f0
#घोषणा AARCH32_BREAK_THUMB	0xde01
#घोषणा AARCH32_BREAK_THUMB2_LO	0xf7f0
#घोषणा AARCH32_BREAK_THUMB2_HI	0xa000

#अगर_अघोषित __ASSEMBLY__
काष्ठा task_काष्ठा;

#घोषणा DBG_ARCH_ID_RESERVED	0	/* In हाल of ptrace ABI updates. */

#घोषणा DBG_HOOK_HANDLED	0
#घोषणा DBG_HOOK_ERROR		1

काष्ठा step_hook अणु
	काष्ठा list_head node;
	पूर्णांक (*fn)(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक esr);
पूर्ण;

व्योम रेजिस्टर_user_step_hook(काष्ठा step_hook *hook);
व्योम unरेजिस्टर_user_step_hook(काष्ठा step_hook *hook);

व्योम रेजिस्टर_kernel_step_hook(काष्ठा step_hook *hook);
व्योम unरेजिस्टर_kernel_step_hook(काष्ठा step_hook *hook);

काष्ठा अवरोध_hook अणु
	काष्ठा list_head node;
	पूर्णांक (*fn)(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक esr);
	u16 imm;
	u16 mask; /* These bits are ignored when comparing with imm */
पूर्ण;

व्योम रेजिस्टर_user_अवरोध_hook(काष्ठा अवरोध_hook *hook);
व्योम unरेजिस्टर_user_अवरोध_hook(काष्ठा अवरोध_hook *hook);

व्योम रेजिस्टर_kernel_अवरोध_hook(काष्ठा अवरोध_hook *hook);
व्योम unरेजिस्टर_kernel_अवरोध_hook(काष्ठा अवरोध_hook *hook);

u8 debug_monitors_arch(व्योम);

क्रमागत dbg_active_el अणु
	DBG_ACTIVE_EL0 = 0,
	DBG_ACTIVE_EL1,
पूर्ण;

व्योम enable_debug_monitors(क्रमागत dbg_active_el el);
व्योम disable_debug_monitors(क्रमागत dbg_active_el el);

व्योम user_शुरुआत_single_step(काष्ठा task_काष्ठा *task);
व्योम user_fastक्रमward_single_step(काष्ठा task_काष्ठा *task);
व्योम user_regs_reset_single_step(काष्ठा user_pt_regs *regs,
				 काष्ठा task_काष्ठा *task);

व्योम kernel_enable_single_step(काष्ठा pt_regs *regs);
व्योम kernel_disable_single_step(व्योम);
पूर्णांक kernel_active_single_step(व्योम);

#अगर_घोषित CONFIG_HAVE_HW_BREAKPOINT
पूर्णांक reinstall_suspended_bps(काष्ठा pt_regs *regs);
#अन्यथा
अटल अंतरभूत पूर्णांक reinstall_suspended_bps(काष्ठा pt_regs *regs)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर

पूर्णांक aarch32_अवरोध_handler(काष्ठा pt_regs *regs);

व्योम debug_traps_init(व्योम);

#पूर्ण_अगर	/* __ASSEMBLY */
#पूर्ण_अगर	/* __ASM_DEBUG_MONITORS_H */
