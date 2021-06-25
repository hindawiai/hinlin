<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Renesas R-Car E3 System Controller
 *
 * Copyright (C) 2018 Renesas Electronics Corp.
 */

#समावेश <linux/bits.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sys_soc.h>

#समावेश <dt-bindings/घातer/r8a77990-sysc.h>

#समावेश "rcar-sysc.h"

अटल काष्ठा rcar_sysc_area r8a77990_areas[] __initdata = अणु
	अणु "always-on",	    0, 0, R8A77990_PD_ALWAYS_ON, -1, PD_ALWAYS_ON पूर्ण,
	अणु "ca53-scu",	0x140, 0, R8A77990_PD_CA53_SCU,  R8A77990_PD_ALWAYS_ON,
	  PD_SCU पूर्ण,
	अणु "ca53-cpu0",	0x200, 0, R8A77990_PD_CA53_CPU0, R8A77990_PD_CA53_SCU,
	  PD_CPU_NOCR पूर्ण,
	अणु "ca53-cpu1",	0x200, 1, R8A77990_PD_CA53_CPU1, R8A77990_PD_CA53_SCU,
	  PD_CPU_NOCR पूर्ण,
	अणु "cr7",	0x240, 0, R8A77990_PD_CR7,	R8A77990_PD_ALWAYS_ON पूर्ण,
	अणु "a3vc",	0x380, 0, R8A77990_PD_A3VC,	R8A77990_PD_ALWAYS_ON पूर्ण,
	अणु "a2vc1",	0x3c0, 1, R8A77990_PD_A2VC1,	R8A77990_PD_A3VC पूर्ण,
	अणु "3dg-a",	0x100, 0, R8A77990_PD_3DG_A,	R8A77990_PD_ALWAYS_ON पूर्ण,
	अणु "3dg-b",	0x100, 1, R8A77990_PD_3DG_B,	R8A77990_PD_3DG_A पूर्ण,
पूर्ण;

/* Fixups क्रम R-Car E3 ES1.0 revision */
अटल स्थिर काष्ठा soc_device_attribute r8a77990[] __initस्थिर = अणु
	अणु .soc_id = "r8a77990", .revision = "ES1.0" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल पूर्णांक __init r8a77990_sysc_init(व्योम)
अणु
	अगर (soc_device_match(r8a77990)) अणु
		/* Fix incorrect 3DG hierarchy */
		swap(r8a77990_areas[7], r8a77990_areas[8]);
		r8a77990_areas[7].parent = R8A77990_PD_ALWAYS_ON;
		r8a77990_areas[8].parent = R8A77990_PD_3DG_B;
	पूर्ण

	वापस 0;
पूर्ण

स्थिर काष्ठा rcar_sysc_info r8a77990_sysc_info __initस्थिर = अणु
	.init = r8a77990_sysc_init,
	.areas = r8a77990_areas,
	.num_areas = ARRAY_SIZE(r8a77990_areas),
	.exपंचांगask_offs = 0x2f8,
	.exपंचांगask_val = BIT(0),
पूर्ण;
