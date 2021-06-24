<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *    User-space Probes (UProbes) क्रम s390
 *
 *    Copyright IBM Corp. 2014
 *    Author(s): Jan Willeke,
 */

#अगर_अघोषित _ASM_UPROBES_H
#घोषणा _ASM_UPROBES_H

#समावेश <linux/notअगरier.h>

प्रकार u16 uprobe_opcode_t;

#घोषणा UPROBE_XOL_SLOT_BYTES	256 /* cache aligned */

#घोषणा UPROBE_SWBP_INSN	0x0002
#घोषणा UPROBE_SWBP_INSN_SIZE	2

काष्ठा arch_uprobe अणु
	जोड़अणु
		uprobe_opcode_t insn[3];
		uprobe_opcode_t ixol[3];
	पूर्ण;
	अचिन्हित पूर्णांक saved_per : 1;
	अचिन्हित पूर्णांक saved_पूर्णांक_code;
पूर्ण;

काष्ठा arch_uprobe_task अणु
पूर्ण;

#पूर्ण_अगर	/* _ASM_UPROBES_H */
