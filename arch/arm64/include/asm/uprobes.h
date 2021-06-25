<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2014-2016 Pratyush Anand <panand@redhat.com>
 */

#अगर_अघोषित _ASM_UPROBES_H
#घोषणा _ASM_UPROBES_H

#समावेश <यंत्र/debug-monitors.h>
#समावेश <यंत्र/insn.h>
#समावेश <यंत्र/probes.h>

#घोषणा MAX_UINSN_BYTES		AARCH64_INSN_SIZE

#घोषणा UPROBE_SWBP_INSN	BRK64_OPCODE_UPROBES
#घोषणा UPROBE_SWBP_INSN_SIZE	AARCH64_INSN_SIZE
#घोषणा UPROBE_XOL_SLOT_BYTES	MAX_UINSN_BYTES

प्रकार u32 uprobe_opcode_t;

काष्ठा arch_uprobe_task अणु
पूर्ण;

काष्ठा arch_uprobe अणु
	जोड़ अणु
		u8 insn[MAX_UINSN_BYTES];
		u8 ixol[MAX_UINSN_BYTES];
	पूर्ण;
	काष्ठा arch_probe_insn api;
	bool simulate;
पूर्ण;

#पूर्ण_अगर
