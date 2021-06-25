<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * arch/arm/probes/kprobes/checkers-common.c
 *
 * Copyright (C) 2014 Huawei Inc.
 */

#समावेश <linux/kernel.h>
#समावेश "../decode.h"
#समावेश "../decode-arm.h"
#समावेश "checkers.h"

क्रमागत probes_insn checker_stack_use_none(probes_opcode_t insn,
		काष्ठा arch_probes_insn *asi,
		स्थिर काष्ठा decode_header *h)
अणु
	asi->stack_space = 0;
	वापस INSN_GOOD_NO_SLOT;
पूर्ण

क्रमागत probes_insn checker_stack_use_unknown(probes_opcode_t insn,
		काष्ठा arch_probes_insn *asi,
		स्थिर काष्ठा decode_header *h)
अणु
	asi->stack_space = -1;
	वापस INSN_GOOD_NO_SLOT;
पूर्ण

#अगर_घोषित CONFIG_THUMB2_KERNEL
क्रमागत probes_insn checker_stack_use_imm_0xx(probes_opcode_t insn,
		काष्ठा arch_probes_insn *asi,
		स्थिर काष्ठा decode_header *h)
अणु
	पूर्णांक imm = insn & 0xff;
	asi->stack_space = imm;
	वापस INSN_GOOD_NO_SLOT;
पूर्ण

/*
 * Dअगरferent from other insn uses imm8, the real addressing offset of
 * STRD in T32 encoding should be imm8 * 4. See ARMARM description.
 */
क्रमागत probes_insn checker_stack_use_t32strd(probes_opcode_t insn,
		काष्ठा arch_probes_insn *asi,
		स्थिर काष्ठा decode_header *h)
अणु
	पूर्णांक imm = insn & 0xff;
	asi->stack_space = imm << 2;
	वापस INSN_GOOD_NO_SLOT;
पूर्ण
#अन्यथा
क्रमागत probes_insn checker_stack_use_imm_x0x(probes_opcode_t insn,
		काष्ठा arch_probes_insn *asi,
		स्थिर काष्ठा decode_header *h)
अणु
	पूर्णांक imm = ((insn & 0xf00) >> 4) + (insn & 0xf);
	asi->stack_space = imm;
	वापस INSN_GOOD_NO_SLOT;
पूर्ण
#पूर्ण_अगर

क्रमागत probes_insn checker_stack_use_imm_xxx(probes_opcode_t insn,
		काष्ठा arch_probes_insn *asi,
		स्थिर काष्ठा decode_header *h)
अणु
	पूर्णांक imm = insn & 0xfff;
	asi->stack_space = imm;
	वापस INSN_GOOD_NO_SLOT;
पूर्ण

क्रमागत probes_insn checker_stack_use_sपंचांगdx(probes_opcode_t insn,
		काष्ठा arch_probes_insn *asi,
		स्थिर काष्ठा decode_header *h)
अणु
	अचिन्हित पूर्णांक reglist = insn & 0xffff;
	पूर्णांक pbit = insn & (1 << 24);
	asi->stack_space = (hweight32(reglist) - (!pbit ? 1 : 0)) * 4;

	वापस INSN_GOOD_NO_SLOT;
पूर्ण

स्थिर जोड़ decode_action stack_check_actions[] = अणु
	[STACK_USE_NONE] = अणु.decoder = checker_stack_use_noneपूर्ण,
	[STACK_USE_UNKNOWN] = अणु.decoder = checker_stack_use_unknownपूर्ण,
#अगर_घोषित CONFIG_THUMB2_KERNEL
	[STACK_USE_FIXED_0XX] = अणु.decoder = checker_stack_use_imm_0xxपूर्ण,
	[STACK_USE_T32STRD] = अणु.decoder = checker_stack_use_t32strdपूर्ण,
#अन्यथा
	[STACK_USE_FIXED_X0X] = अणु.decoder = checker_stack_use_imm_x0xपूर्ण,
#पूर्ण_अगर
	[STACK_USE_FIXED_XXX] = अणु.decoder = checker_stack_use_imm_xxxपूर्ण,
	[STACK_USE_STMDX] = अणु.decoder = checker_stack_use_sपंचांगdxपूर्ण,
पूर्ण;
