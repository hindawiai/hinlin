<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Renesas R-Car D3 System Controller
 *
 * Copyright (C) 2017 Glider bvba
 */

#समावेश <linux/kernel.h>

#समावेश <dt-bindings/घातer/r8a77995-sysc.h>

#समावेश "rcar-sysc.h"

अटल स्थिर काष्ठा rcar_sysc_area r8a77995_areas[] __initस्थिर = अणु
	अणु "always-on",     0, 0, R8A77995_PD_ALWAYS_ON, -1, PD_ALWAYS_ON पूर्ण,
	अणु "ca53-scu",  0x140, 0, R8A77995_PD_CA53_SCU,  R8A77995_PD_ALWAYS_ON,
	  PD_SCU पूर्ण,
	अणु "ca53-cpu0", 0x200, 0, R8A77995_PD_CA53_CPU0, R8A77995_PD_CA53_SCU,
	  PD_CPU_NOCR पूर्ण,
पूर्ण;


स्थिर काष्ठा rcar_sysc_info r8a77995_sysc_info __initस्थिर = अणु
	.areas = r8a77995_areas,
	.num_areas = ARRAY_SIZE(r8a77995_areas),
पूर्ण;
