<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2017 Josh Poimboeuf <jpoimboe@redhat.com>
 */

#अगर_अघोषित _ORC_TYPES_H
#घोषणा _ORC_TYPES_H

#समावेश <linux/types.h>
#समावेश <linux/compiler.h>

/*
 * The ORC_REG_* रेजिस्टरs are base रेजिस्टरs which are used to find other
 * रेजिस्टरs on the stack.
 *
 * ORC_REG_PREV_SP, also known as DWARF Call Frame Address (CFA), is the
 * address of the previous frame: the caller's SP beक्रमe it called the current
 * function.
 *
 * ORC_REG_UNDEFINED means the corresponding रेजिस्टर's value didn't change in
 * the current frame.
 *
 * The most commonly used base रेजिस्टरs are SP and BP -- which the previous SP
 * is usually based on -- and PREV_SP and UNDEFINED -- which the previous BP is
 * usually based on.
 *
 * The rest of the base रेजिस्टरs are needed क्रम special हालs like entry code
 * and GCC realigned stacks.
 */
#घोषणा ORC_REG_UNDEFINED		0
#घोषणा ORC_REG_PREV_SP			1
#घोषणा ORC_REG_DX			2
#घोषणा ORC_REG_DI			3
#घोषणा ORC_REG_BP			4
#घोषणा ORC_REG_SP			5
#घोषणा ORC_REG_R10			6
#घोषणा ORC_REG_R13			7
#घोषणा ORC_REG_BP_INसूचीECT		8
#घोषणा ORC_REG_SP_INसूचीECT		9
#घोषणा ORC_REG_MAX			15

#अगर_अघोषित __ASSEMBLY__
#समावेश <यंत्र/byteorder.h>

/*
 * This काष्ठा is more or less a vastly simplअगरied version of the DWARF Call
 * Frame Inक्रमmation standard.  It contains only the necessary parts of DWARF
 * CFI, simplअगरied क्रम ease of access by the in-kernel unwinder.  It tells the
 * unwinder how to find the previous SP and BP (and someबार entry regs) on
 * the stack क्रम a given code address.  Each instance of the काष्ठा corresponds
 * to one or more code locations.
 */
काष्ठा orc_entry अणु
	s16		sp_offset;
	s16		bp_offset;
#अगर defined(__LITTLE_ENDIAN_BITFIELD)
	अचिन्हित	sp_reg:4;
	अचिन्हित	bp_reg:4;
	अचिन्हित	type:2;
	अचिन्हित	end:1;
#या_अगर defined(__BIG_ENDIAN_BITFIELD)
	अचिन्हित	bp_reg:4;
	अचिन्हित	sp_reg:4;
	अचिन्हित	unused:5;
	अचिन्हित	end:1;
	अचिन्हित	type:2;
#पूर्ण_अगर
पूर्ण __packed;

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* _ORC_TYPES_H */
