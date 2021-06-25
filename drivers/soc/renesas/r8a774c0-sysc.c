<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Renesas RZ/G2E System Controller
 * Copyright (C) 2018 Renesas Electronics Corp.
 *
 * Based on Renesas R-Car E3 System Controller
 */

#समावेश <linux/bits.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sys_soc.h>

#समावेश <dt-bindings/घातer/r8a774c0-sysc.h>

#समावेश "rcar-sysc.h"

अटल काष्ठा rcar_sysc_area r8a774c0_areas[] __initdata = अणु
	अणु "always-on",	    0, 0, R8A774C0_PD_ALWAYS_ON, -1, PD_ALWAYS_ON पूर्ण,
	अणु "ca53-scu",	0x140, 0, R8A774C0_PD_CA53_SCU,  R8A774C0_PD_ALWAYS_ON,
	  PD_SCU पूर्ण,
	अणु "ca53-cpu0",	0x200, 0, R8A774C0_PD_CA53_CPU0, R8A774C0_PD_CA53_SCU,
	  PD_CPU_NOCR पूर्ण,
	अणु "ca53-cpu1",	0x200, 1, R8A774C0_PD_CA53_CPU1, R8A774C0_PD_CA53_SCU,
	  PD_CPU_NOCR पूर्ण,
	अणु "a3vc",	0x380, 0, R8A774C0_PD_A3VC,	R8A774C0_PD_ALWAYS_ON पूर्ण,
	अणु "a2vc1",	0x3c0, 1, R8A774C0_PD_A2VC1,	R8A774C0_PD_A3VC पूर्ण,
	अणु "3dg-a",	0x100, 0, R8A774C0_PD_3DG_A,	R8A774C0_PD_ALWAYS_ON पूर्ण,
	अणु "3dg-b",	0x100, 1, R8A774C0_PD_3DG_B,	R8A774C0_PD_3DG_A पूर्ण,
पूर्ण;

/* Fixups क्रम RZ/G2E ES1.0 revision */
अटल स्थिर काष्ठा soc_device_attribute r8a774c0[] __initस्थिर = अणु
	अणु .soc_id = "r8a774c0", .revision = "ES1.0" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल पूर्णांक __init r8a774c0_sysc_init(व्योम)
अणु
	अगर (soc_device_match(r8a774c0)) अणु
		/* Fix incorrect 3DG hierarchy */
		swap(r8a774c0_areas[6], r8a774c0_areas[7]);
		r8a774c0_areas[6].parent = R8A774C0_PD_ALWAYS_ON;
		r8a774c0_areas[7].parent = R8A774C0_PD_3DG_B;
	पूर्ण

	वापस 0;
पूर्ण

स्थिर काष्ठा rcar_sysc_info r8a774c0_sysc_info __initस्थिर = अणु
	.init = r8a774c0_sysc_init,
	.areas = r8a774c0_areas,
	.num_areas = ARRAY_SIZE(r8a774c0_areas),
	.exपंचांगask_offs = 0x2f8,
	.exपंचांगask_val = BIT(0),
पूर्ण;
