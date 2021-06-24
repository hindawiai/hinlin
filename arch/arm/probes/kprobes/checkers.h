<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * arch/arm/probes/kprobes/checkers.h
 *
 * Copyright (C) 2014 Huawei Inc.
 */
#अगर_अघोषित _ARM_KERNEL_PROBES_CHECKERS_H
#घोषणा _ARM_KERNEL_PROBES_CHECKERS_H

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश "../decode.h"

बाह्य probes_check_t checker_stack_use_none;
बाह्य probes_check_t checker_stack_use_unknown;
#अगर_घोषित CONFIG_THUMB2_KERNEL
बाह्य probes_check_t checker_stack_use_imm_0xx;
#अन्यथा
बाह्य probes_check_t checker_stack_use_imm_x0x;
#पूर्ण_अगर
बाह्य probes_check_t checker_stack_use_imm_xxx;
बाह्य probes_check_t checker_stack_use_sपंचांगdx;

क्रमागत अणु
	STACK_USE_NONE,
	STACK_USE_UNKNOWN,
#अगर_घोषित CONFIG_THUMB2_KERNEL
	STACK_USE_FIXED_0XX,
	STACK_USE_T32STRD,
#अन्यथा
	STACK_USE_FIXED_X0X,
#पूर्ण_अगर
	STACK_USE_FIXED_XXX,
	STACK_USE_STMDX,
	NUM_STACK_USE_TYPES
पूर्ण;

बाह्य स्थिर जोड़ decode_action stack_check_actions[];

#अगर_अघोषित CONFIG_THUMB2_KERNEL
बाह्य स्थिर काष्ठा decode_checker arm_stack_checker[];
बाह्य स्थिर काष्ठा decode_checker arm_regs_checker[];
#अन्यथा
#पूर्ण_अगर
बाह्य स्थिर काष्ठा decode_checker t32_stack_checker[];
बाह्य स्थिर काष्ठा decode_checker t16_stack_checker[];
#पूर्ण_अगर
