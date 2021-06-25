<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित _ASM_UPROBES_H
#घोषणा _ASM_UPROBES_H
/*
 * User-space Probes (UProbes) क्रम sparc
 *
 * Copyright (C) 2013 Oracle, Inc.
 *
 * Authors:
 *     Jose E. Marchesi <jose.marchesi@oracle.com>
 *	Eric Saपूर्णांक Etienne <eric.saपूर्णांक.etienne@oracle.com>
 */

प्रकार u32 uprobe_opcode_t;

#घोषणा MAX_UINSN_BYTES		4
#घोषणा UPROBE_XOL_SLOT_BYTES	(MAX_UINSN_BYTES * 2)

#घोषणा UPROBE_SWBP_INSN_SIZE	4
#घोषणा UPROBE_SWBP_INSN	0x91d02073 /* ta 0x73 */
#घोषणा UPROBE_STP_INSN		0x91d02074 /* ta 0x74 */

#घोषणा ANNUL_BIT (1 << 29)

काष्ठा arch_uprobe अणु
	जोड़ अणु
		u8  insn[MAX_UINSN_BYTES];
		u32 ixol;
	पूर्ण;
पूर्ण;

काष्ठा arch_uprobe_task अणु
	u64 saved_tpc;
	u64 saved_tnpc;
पूर्ण;

काष्ठा task_काष्ठा;
काष्ठा notअगरier_block;

बाह्य पूर्णांक  arch_uprobe_analyze_insn(काष्ठा arch_uprobe *aup, काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr);
बाह्य पूर्णांक  arch_uprobe_pre_xol(काष्ठा arch_uprobe *aup, काष्ठा pt_regs *regs);
बाह्य पूर्णांक  arch_uprobe_post_xol(काष्ठा arch_uprobe *aup, काष्ठा pt_regs *regs);
बाह्य bool arch_uprobe_xol_was_trapped(काष्ठा task_काष्ठा *tsk);
बाह्य पूर्णांक  arch_uprobe_exception_notअगरy(काष्ठा notअगरier_block *self, अचिन्हित दीर्घ val, व्योम *data);
बाह्य व्योम arch_uprobe_पात_xol(काष्ठा arch_uprobe *aup, काष्ठा pt_regs *regs);

#पूर्ण_अगर	/* _ASM_UPROBES_H */
