<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित _ASM_UPROBES_H
#घोषणा _ASM_UPROBES_H
/*
 * User-space Probes (UProbes) क्रम x86
 *
 * Copyright (C) IBM Corporation, 2008-2011
 * Authors:
 *	Srikar Dronamraju
 *	Jim Keniston
 */

#समावेश <linux/notअगरier.h>

प्रकार u8 uprobe_opcode_t;

#घोषणा MAX_UINSN_BYTES			  16
#घोषणा UPROBE_XOL_SLOT_BYTES		 128	/* to keep it cache aligned */

#घोषणा UPROBE_SWBP_INSN		0xcc
#घोषणा UPROBE_SWBP_INSN_SIZE		   1

काष्ठा uprobe_xol_ops;

काष्ठा arch_uprobe अणु
	जोड़ अणु
		u8			insn[MAX_UINSN_BYTES];
		u8			ixol[MAX_UINSN_BYTES];
	पूर्ण;

	स्थिर काष्ठा uprobe_xol_ops	*ops;

	जोड़ अणु
		काष्ठा अणु
			s32	offs;
			u8	ilen;
			u8	opc1;
		पूर्ण			branch;
		काष्ठा अणु
			u8	fixups;
			u8	ilen;
		पूर्ण 			defparam;
		काष्ठा अणु
			u8	reg_offset;	/* to the start of pt_regs */
			u8	ilen;
		पूर्ण			push;
	पूर्ण;
पूर्ण;

काष्ठा arch_uprobe_task अणु
#अगर_घोषित CONFIG_X86_64
	अचिन्हित दीर्घ			saved_scratch_रेजिस्टर;
#पूर्ण_अगर
	अचिन्हित पूर्णांक			saved_trap_nr;
	अचिन्हित पूर्णांक			saved_tf;
पूर्ण;

#पूर्ण_अगर	/* _ASM_UPROBES_H */
