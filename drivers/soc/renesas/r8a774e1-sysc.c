<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Renesas RZ/G2H System Controller
 * Copyright (C) 2020 Renesas Electronics Corp.
 *
 * Based on Renesas R-Car H3 System Controller
 * Copyright (C) 2016-2017 Glider bvba
 */

#समावेश <linux/kernel.h>

#समावेश <dt-bindings/घातer/r8a774e1-sysc.h>

#समावेश "rcar-sysc.h"

अटल स्थिर काष्ठा rcar_sysc_area r8a774e1_areas[] __initस्थिर = अणु
	अणु "always-on",	    0, 0, R8A774E1_PD_ALWAYS_ON, -1, PD_ALWAYS_ON पूर्ण,
	अणु "ca57-scu",	0x1c0, 0, R8A774E1_PD_CA57_SCU, R8A774E1_PD_ALWAYS_ON, PD_SCU पूर्ण,
	अणु "ca57-cpu0",	 0x80, 0, R8A774E1_PD_CA57_CPU0, R8A774E1_PD_CA57_SCU, PD_CPU_NOCR पूर्ण,
	अणु "ca57-cpu1",	 0x80, 1, R8A774E1_PD_CA57_CPU1, R8A774E1_PD_CA57_SCU, PD_CPU_NOCR पूर्ण,
	अणु "ca57-cpu2",	 0x80, 2, R8A774E1_PD_CA57_CPU2, R8A774E1_PD_CA57_SCU, PD_CPU_NOCR पूर्ण,
	अणु "ca57-cpu3",	 0x80, 3, R8A774E1_PD_CA57_CPU3, R8A774E1_PD_CA57_SCU, PD_CPU_NOCR पूर्ण,
	अणु "ca53-scu",	0x140, 0, R8A774E1_PD_CA53_SCU, R8A774E1_PD_ALWAYS_ON, PD_SCU पूर्ण,
	अणु "ca53-cpu0",	0x200, 0, R8A774E1_PD_CA53_CPU0, R8A774E1_PD_CA53_SCU, PD_CPU_NOCR पूर्ण,
	अणु "ca53-cpu1",	0x200, 1, R8A774E1_PD_CA53_CPU1, R8A774E1_PD_CA53_SCU, PD_CPU_NOCR पूर्ण,
	अणु "ca53-cpu2",	0x200, 2, R8A774E1_PD_CA53_CPU2, R8A774E1_PD_CA53_SCU, PD_CPU_NOCR पूर्ण,
	अणु "ca53-cpu3",	0x200, 3, R8A774E1_PD_CA53_CPU3, R8A774E1_PD_CA53_SCU, PD_CPU_NOCR पूर्ण,
	अणु "a3vp",	0x340, 0, R8A774E1_PD_A3VP, R8A774E1_PD_ALWAYS_ON पूर्ण,
	अणु "a3vc",	0x380, 0, R8A774E1_PD_A3VC, R8A774E1_PD_ALWAYS_ON पूर्ण,
	अणु "a2vc1",	0x3c0, 1, R8A774E1_PD_A2VC1, R8A774E1_PD_A3VC पूर्ण,
	अणु "3dg-a",	0x100, 0, R8A774E1_PD_3DG_A, R8A774E1_PD_ALWAYS_ON पूर्ण,
	अणु "3dg-b",	0x100, 1, R8A774E1_PD_3DG_B, R8A774E1_PD_3DG_A पूर्ण,
	अणु "3dg-c",	0x100, 2, R8A774E1_PD_3DG_C, R8A774E1_PD_3DG_B पूर्ण,
	अणु "3dg-d",	0x100, 3, R8A774E1_PD_3DG_D, R8A774E1_PD_3DG_C पूर्ण,
	अणु "3dg-e",	0x100, 4, R8A774E1_PD_3DG_E, R8A774E1_PD_3DG_D पूर्ण,
पूर्ण;

स्थिर काष्ठा rcar_sysc_info r8a774e1_sysc_info __initस्थिर = अणु
	.areas = r8a774e1_areas,
	.num_areas = ARRAY_SIZE(r8a774e1_areas),
	.exपंचांगask_offs = 0x2f8,
	.exपंचांगask_val = BIT(0),
पूर्ण;
