<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Linux/PA-RISC Project (http://www.parisc-linux.org/)
 *
 * Floating-poपूर्णांक emulation code
 *  Copyright (C) 2001 Hewlett-Packard (Paul Bame) <bame@debian.org>
 */

#अगर_अघोषित _MACHINE_FPU_INCLUDED /* allows multiple inclusion */
#घोषणा _MACHINE_FPU_INCLUDED

#घोषणा PA83_FPU_FLAG    0x00000001
#घोषणा PA89_FPU_FLAG    0x00000002
#घोषणा PA2_0_FPU_FLAG   0x00000010

#घोषणा TIMEX_EXTEN_FLAG 0x00000004

#घोषणा ROLEX_EXTEN_FLAG 0x00000008
#घोषणा COPR_FP 	0x00000080	/* Floating poपूर्णांक -- Coprocessor 0 */
#घोषणा SFU_MPY_DIVIDE	0x00008000	/* Multiply/Divide __ SFU 0 */

#घोषणा EM_FPU_TYPE_OFFSET 272

/* version of EMULATION software क्रम COPR,0,0 inकाष्ठाion */
#घोषणा EMULATION_VERSION 4

/*
 * The only way to dअगरferentiate between TIMEX and ROLEX (or PCX-S and PCX-T)
 * is through the potential type field from the PDC_MODEL call.
 * The following flags are used to assist this dअगरferentiation.
 */

#घोषणा ROLEX_POTENTIAL_KEY_FLAGS	PDC_MODEL_CPU_KEY_WORD_TO_IO
#घोषणा TIMEX_POTENTIAL_KEY_FLAGS	(PDC_MODEL_CPU_KEY_QUAD_STORE | \
					 PDC_MODEL_CPU_KEY_RECIP_SQRT)

#पूर्ण_अगर /* ! _MACHINE_FPU_INCLUDED */
