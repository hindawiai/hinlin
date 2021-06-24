<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Renesas R-Car M3-N System Controller
 * Copyright (C) 2018 Jacopo Mondi <jacopo+renesas@jmondi.org>
 *
 * Based on Renesas R-Car M3-W System Controller
 * Copyright (C) 2016 Glider bvba
 */

#समावेश <linux/bits.h>
#समावेश <linux/kernel.h>

#समावेश <dt-bindings/घातer/r8a77965-sysc.h>

#समावेश "rcar-sysc.h"

अटल स्थिर काष्ठा rcar_sysc_area r8a77965_areas[] __initस्थिर = अणु
	अणु "always-on",	    0, 0, R8A77965_PD_ALWAYS_ON, -1, PD_ALWAYS_ON पूर्ण,
	अणु "ca57-scu",	0x1c0, 0, R8A77965_PD_CA57_SCU,	R8A77965_PD_ALWAYS_ON,
	  PD_SCU पूर्ण,
	अणु "ca57-cpu0",	 0x80, 0, R8A77965_PD_CA57_CPU0, R8A77965_PD_CA57_SCU,
	  PD_CPU_NOCR पूर्ण,
	अणु "ca57-cpu1",	 0x80, 1, R8A77965_PD_CA57_CPU1, R8A77965_PD_CA57_SCU,
	  PD_CPU_NOCR पूर्ण,
	अणु "cr7",	0x240, 0, R8A77965_PD_CR7,	R8A77965_PD_ALWAYS_ON पूर्ण,
	अणु "a3vc",	0x380, 0, R8A77965_PD_A3VC,	R8A77965_PD_ALWAYS_ON पूर्ण,
	अणु "a3vp",	0x340, 0, R8A77965_PD_A3VP,	R8A77965_PD_ALWAYS_ON पूर्ण,
	अणु "a2vc1",	0x3c0, 1, R8A77965_PD_A2VC1,	R8A77965_PD_A3VC पूर्ण,
	अणु "3dg-a",	0x100, 0, R8A77965_PD_3DG_A,	R8A77965_PD_ALWAYS_ON पूर्ण,
	अणु "3dg-b",	0x100, 1, R8A77965_PD_3DG_B,	R8A77965_PD_3DG_A पूर्ण,
पूर्ण;

स्थिर काष्ठा rcar_sysc_info r8a77965_sysc_info __initस्थिर = अणु
	.areas = r8a77965_areas,
	.num_areas = ARRAY_SIZE(r8a77965_areas),
	.exपंचांगask_offs = 0x2f8,
	.exपंचांगask_val = BIT(0),
पूर्ण;
