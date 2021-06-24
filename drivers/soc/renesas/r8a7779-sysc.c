<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Renesas R-Car H1 System Controller
 *
 * Copyright (C) 2016 Glider bvba
 */

#समावेश <linux/kernel.h>

#समावेश <dt-bindings/घातer/r8a7779-sysc.h>

#समावेश "rcar-sysc.h"

अटल स्थिर काष्ठा rcar_sysc_area r8a7779_areas[] __initस्थिर = अणु
	अणु "always-on",	    0, 0, R8A7779_PD_ALWAYS_ON,	-1, PD_ALWAYS_ON पूर्ण,
	अणु "arm1",	 0x40, 1, R8A7779_PD_ARM1,	R8A7779_PD_ALWAYS_ON,
	  PD_CPU_CR पूर्ण,
	अणु "arm2",	 0x40, 2, R8A7779_PD_ARM2,	R8A7779_PD_ALWAYS_ON,
	  PD_CPU_CR पूर्ण,
	अणु "arm3",	 0x40, 3, R8A7779_PD_ARM3,	R8A7779_PD_ALWAYS_ON,
	  PD_CPU_CR पूर्ण,
	अणु "sgx",	 0xc0, 0, R8A7779_PD_SGX,	R8A7779_PD_ALWAYS_ON पूर्ण,
	अणु "vdp",	0x100, 0, R8A7779_PD_VDP,	R8A7779_PD_ALWAYS_ON पूर्ण,
	अणु "imp",	0x140, 0, R8A7779_PD_IMP,	R8A7779_PD_ALWAYS_ON पूर्ण,
पूर्ण;

स्थिर काष्ठा rcar_sysc_info r8a7779_sysc_info __initस्थिर = अणु
	.areas = r8a7779_areas,
	.num_areas = ARRAY_SIZE(r8a7779_areas),
पूर्ण;
