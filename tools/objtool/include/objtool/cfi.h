<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2015-2017 Josh Poimboeuf <jpoimboe@redhat.com>
 */

#अगर_अघोषित _OBJTOOL_CFI_H
#घोषणा _OBJTOOL_CFI_H

#समावेश <arch/cfi_regs.h>

#घोषणा CFI_UNDEFINED		-1
#घोषणा CFI_CFA			-2
#घोषणा CFI_SP_INसूचीECT		-3
#घोषणा CFI_BP_INसूचीECT		-4

काष्ठा cfi_reg अणु
	पूर्णांक base;
	पूर्णांक offset;
पूर्ण;

काष्ठा cfi_init_state अणु
	काष्ठा cfi_reg regs[CFI_NUM_REGS];
	काष्ठा cfi_reg cfa;
पूर्ण;

काष्ठा cfi_state अणु
	काष्ठा cfi_reg regs[CFI_NUM_REGS];
	काष्ठा cfi_reg vals[CFI_NUM_REGS];
	काष्ठा cfi_reg cfa;
	पूर्णांक stack_size;
	पूर्णांक drap_reg, drap_offset;
	अचिन्हित अक्षर type;
	bool bp_scratch;
	bool drap;
	bool end;
पूर्ण;

#पूर्ण_अगर /* _OBJTOOL_CFI_H */
