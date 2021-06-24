<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#अगर_अघोषित _ASM_ARC_UNALIGNED_H
#घोषणा _ASM_ARC_UNALIGNED_H

/* ARC700 can't handle unaligned Data accesses. */

#समावेश <यंत्र-generic/unaligned.h>
#समावेश <यंत्र/ptrace.h>

#अगर_घोषित CONFIG_ARC_EMUL_UNALIGNED
पूर्णांक misaligned_fixup(अचिन्हित दीर्घ address, काष्ठा pt_regs *regs,
		     काष्ठा callee_regs *cregs);
#अन्यथा
अटल अंतरभूत पूर्णांक
misaligned_fixup(अचिन्हित दीर्घ address, काष्ठा pt_regs *regs,
		 काष्ठा callee_regs *cregs)
अणु
	/* Not fixed */
	वापस 1;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_ARC_UNALIGNED_H */
