<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Renesas R-Car M2-W/N System Controller
 *
 * Copyright (C) 2016 Glider bvba
 */

#समावेश <linux/kernel.h>

#समावेश <dt-bindings/घातer/r8a7791-sysc.h>

#समावेश "rcar-sysc.h"

अटल स्थिर काष्ठा rcar_sysc_area r8a7791_areas[] __initस्थिर = अणु
	अणु "always-on",	    0, 0, R8A7791_PD_ALWAYS_ON,	-1, PD_ALWAYS_ON पूर्ण,
	अणु "ca15-scu",	0x180, 0, R8A7791_PD_CA15_SCU,	R8A7791_PD_ALWAYS_ON,
	  PD_SCU पूर्ण,
	अणु "ca15-cpu0",	 0x40, 0, R8A7791_PD_CA15_CPU0,	R8A7791_PD_CA15_SCU,
	  PD_CPU_NOCR पूर्ण,
	अणु "ca15-cpu1",	 0x40, 1, R8A7791_PD_CA15_CPU1,	R8A7791_PD_CA15_SCU,
	  PD_CPU_NOCR पूर्ण,
	अणु "sh-4a",	 0x80, 0, R8A7791_PD_SH_4A,	R8A7791_PD_ALWAYS_ON पूर्ण,
	अणु "sgx",	 0xc0, 0, R8A7791_PD_SGX,	R8A7791_PD_ALWAYS_ON पूर्ण,
पूर्ण;

स्थिर काष्ठा rcar_sysc_info r8a7791_sysc_info __initस्थिर = अणु
	.areas = r8a7791_areas,
	.num_areas = ARRAY_SIZE(r8a7791_areas),
पूर्ण;
