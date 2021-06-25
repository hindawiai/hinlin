<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित _ASM_UPROBES_H
#घोषणा _ASM_UPROBES_H
/*
 * User-space Probes (UProbes) क्रम घातerpc
 *
 * Copyright IBM Corporation, 2007-2012
 *
 * Adapted from the x86 port by Ananth N Mavinakayanahalli <ananth@in.ibm.com>
 */

#समावेश <linux/notअगरier.h>
#समावेश <यंत्र/probes.h>
#समावेश <यंत्र/inst.h>

प्रकार ppc_opcode_t uprobe_opcode_t;

#घोषणा MAX_UINSN_BYTES		8
#घोषणा UPROBE_XOL_SLOT_BYTES	(MAX_UINSN_BYTES)

/* The following alias is needed क्रम reference from arch-agnostic code */
#घोषणा UPROBE_SWBP_INSN	BREAKPOINT_INSTRUCTION
#घोषणा UPROBE_SWBP_INSN_SIZE	4 /* swbp insn size in bytes */

काष्ठा arch_uprobe अणु
	जोड़ अणु
		काष्ठा ppc_inst	insn;
		काष्ठा ppc_inst	ixol;
	पूर्ण;
पूर्ण;

काष्ठा arch_uprobe_task अणु
	अचिन्हित दीर्घ	saved_trap_nr;
पूर्ण;

#पूर्ण_अगर	/* _ASM_UPROBES_H */
