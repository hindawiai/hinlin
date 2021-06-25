<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Renesas RZ/G2M System Controller
 * Copyright (C) 2018 Renesas Electronics Corp.
 *
 * Based on Renesas R-Car M3-W System Controller
 * Copyright (C) 2016 Glider bvba
 */

#समावेश <linux/kernel.h>

#समावेश <dt-bindings/घातer/r8a774a1-sysc.h>

#समावेश "rcar-sysc.h"

अटल स्थिर काष्ठा rcar_sysc_area r8a774a1_areas[] __initस्थिर = अणु
	अणु "always-on",	    0, 0, R8A774A1_PD_ALWAYS_ON, -1, PD_ALWAYS_ON पूर्ण,
	अणु "ca57-scu",	0x1c0, 0, R8A774A1_PD_CA57_SCU,	R8A774A1_PD_ALWAYS_ON,
	  PD_SCU पूर्ण,
	अणु "ca57-cpu0",	 0x80, 0, R8A774A1_PD_CA57_CPU0, R8A774A1_PD_CA57_SCU,
	  PD_CPU_NOCR पूर्ण,
	अणु "ca57-cpu1",	 0x80, 1, R8A774A1_PD_CA57_CPU1, R8A774A1_PD_CA57_SCU,
	  PD_CPU_NOCR पूर्ण,
	अणु "ca53-scu",	0x140, 0, R8A774A1_PD_CA53_SCU,	R8A774A1_PD_ALWAYS_ON,
	  PD_SCU पूर्ण,
	अणु "ca53-cpu0",	0x200, 0, R8A774A1_PD_CA53_CPU0, R8A774A1_PD_CA53_SCU,
	  PD_CPU_NOCR पूर्ण,
	अणु "ca53-cpu1",	0x200, 1, R8A774A1_PD_CA53_CPU1, R8A774A1_PD_CA53_SCU,
	  PD_CPU_NOCR पूर्ण,
	अणु "ca53-cpu2",	0x200, 2, R8A774A1_PD_CA53_CPU2, R8A774A1_PD_CA53_SCU,
	  PD_CPU_NOCR पूर्ण,
	अणु "ca53-cpu3",	0x200, 3, R8A774A1_PD_CA53_CPU3, R8A774A1_PD_CA53_SCU,
	  PD_CPU_NOCR पूर्ण,
	अणु "a3vc",	0x380, 0, R8A774A1_PD_A3VC,	R8A774A1_PD_ALWAYS_ON पूर्ण,
	अणु "a2vc0",	0x3c0, 0, R8A774A1_PD_A2VC0,	R8A774A1_PD_A3VC पूर्ण,
	अणु "a2vc1",	0x3c0, 1, R8A774A1_PD_A2VC1,	R8A774A1_PD_A3VC पूर्ण,
	अणु "3dg-a",	0x100, 0, R8A774A1_PD_3DG_A,	R8A774A1_PD_ALWAYS_ON पूर्ण,
	अणु "3dg-b",	0x100, 1, R8A774A1_PD_3DG_B,	R8A774A1_PD_3DG_A पूर्ण,
पूर्ण;

स्थिर काष्ठा rcar_sysc_info r8a774a1_sysc_info __initस्थिर = अणु
	.areas = r8a774a1_areas,
	.num_areas = ARRAY_SIZE(r8a774a1_areas),
पूर्ण;
