<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Renesas R-Car M3-W/W+ System Controller
 *
 * Copyright (C) 2016 Glider bvba
 * Copyright (C) 2018-2019 Renesas Electronics Corporation
 */

#समावेश <linux/bits.h>
#समावेश <linux/kernel.h>

#समावेश <dt-bindings/घातer/r8a7796-sysc.h>

#समावेश "rcar-sysc.h"

अटल काष्ठा rcar_sysc_area r8a7796_areas[] __initdata = अणु
	अणु "always-on",	    0, 0, R8A7796_PD_ALWAYS_ON,	-1, PD_ALWAYS_ON पूर्ण,
	अणु "ca57-scu",	0x1c0, 0, R8A7796_PD_CA57_SCU,	R8A7796_PD_ALWAYS_ON,
	  PD_SCU पूर्ण,
	अणु "ca57-cpu0",	 0x80, 0, R8A7796_PD_CA57_CPU0,	R8A7796_PD_CA57_SCU,
	  PD_CPU_NOCR पूर्ण,
	अणु "ca57-cpu1",	 0x80, 1, R8A7796_PD_CA57_CPU1,	R8A7796_PD_CA57_SCU,
	  PD_CPU_NOCR पूर्ण,
	अणु "ca53-scu",	0x140, 0, R8A7796_PD_CA53_SCU,	R8A7796_PD_ALWAYS_ON,
	  PD_SCU पूर्ण,
	अणु "ca53-cpu0",	0x200, 0, R8A7796_PD_CA53_CPU0,	R8A7796_PD_CA53_SCU,
	  PD_CPU_NOCR पूर्ण,
	अणु "ca53-cpu1",	0x200, 1, R8A7796_PD_CA53_CPU1,	R8A7796_PD_CA53_SCU,
	  PD_CPU_NOCR पूर्ण,
	अणु "ca53-cpu2",	0x200, 2, R8A7796_PD_CA53_CPU2,	R8A7796_PD_CA53_SCU,
	  PD_CPU_NOCR पूर्ण,
	अणु "ca53-cpu3",	0x200, 3, R8A7796_PD_CA53_CPU3,	R8A7796_PD_CA53_SCU,
	  PD_CPU_NOCR पूर्ण,
	अणु "cr7",	0x240, 0, R8A7796_PD_CR7,	R8A7796_PD_ALWAYS_ON पूर्ण,
	अणु "a3vc",	0x380, 0, R8A7796_PD_A3VC,	R8A7796_PD_ALWAYS_ON पूर्ण,
	अणु "a2vc0",	0x3c0, 0, R8A7796_PD_A2VC0,	R8A7796_PD_A3VC पूर्ण,
	अणु "a2vc1",	0x3c0, 1, R8A7796_PD_A2VC1,	R8A7796_PD_A3VC पूर्ण,
	अणु "3dg-a",	0x100, 0, R8A7796_PD_3DG_A,	R8A7796_PD_ALWAYS_ON पूर्ण,
	अणु "3dg-b",	0x100, 1, R8A7796_PD_3DG_B,	R8A7796_PD_3DG_A पूर्ण,
	अणु "a3ir",	0x180, 0, R8A7796_PD_A3IR,	R8A7796_PD_ALWAYS_ON पूर्ण,
पूर्ण;


#अगर_घोषित CONFIG_SYSC_R8A77960
स्थिर काष्ठा rcar_sysc_info r8a77960_sysc_info __initस्थिर = अणु
	.areas = r8a7796_areas,
	.num_areas = ARRAY_SIZE(r8a7796_areas),
पूर्ण;
#पूर्ण_अगर /* CONFIG_SYSC_R8A77960 */

#अगर_घोषित CONFIG_SYSC_R8A77961
अटल पूर्णांक __init r8a77961_sysc_init(व्योम)
अणु
	rcar_sysc_nullअगरy(r8a7796_areas, ARRAY_SIZE(r8a7796_areas),
			  R8A7796_PD_A2VC0);

	वापस 0;
पूर्ण

स्थिर काष्ठा rcar_sysc_info r8a77961_sysc_info __initस्थिर = अणु
	.init = r8a77961_sysc_init,
	.areas = r8a7796_areas,
	.num_areas = ARRAY_SIZE(r8a7796_areas),
	.exपंचांगask_offs = 0x2f8,
	.exपंचांगask_val = BIT(0),
पूर्ण;
#पूर्ण_अगर /* CONFIG_SYSC_R8A77961 */
