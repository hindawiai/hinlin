<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Renesas R-Car H3 System Controller
 *
 * Copyright (C) 2016-2017 Glider bvba
 */

#समावेश <linux/bits.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sys_soc.h>

#समावेश <dt-bindings/घातer/r8a7795-sysc.h>

#समावेश "rcar-sysc.h"

अटल काष्ठा rcar_sysc_area r8a7795_areas[] __initdata = अणु
	अणु "always-on",	    0, 0, R8A7795_PD_ALWAYS_ON,	-1, PD_ALWAYS_ON पूर्ण,
	अणु "ca57-scu",	0x1c0, 0, R8A7795_PD_CA57_SCU,	R8A7795_PD_ALWAYS_ON,
	  PD_SCU पूर्ण,
	अणु "ca57-cpu0",	 0x80, 0, R8A7795_PD_CA57_CPU0,	R8A7795_PD_CA57_SCU,
	  PD_CPU_NOCR पूर्ण,
	अणु "ca57-cpu1",	 0x80, 1, R8A7795_PD_CA57_CPU1,	R8A7795_PD_CA57_SCU,
	  PD_CPU_NOCR पूर्ण,
	अणु "ca57-cpu2",	 0x80, 2, R8A7795_PD_CA57_CPU2,	R8A7795_PD_CA57_SCU,
	  PD_CPU_NOCR पूर्ण,
	अणु "ca57-cpu3",	 0x80, 3, R8A7795_PD_CA57_CPU3,	R8A7795_PD_CA57_SCU,
	  PD_CPU_NOCR पूर्ण,
	अणु "ca53-scu",	0x140, 0, R8A7795_PD_CA53_SCU,	R8A7795_PD_ALWAYS_ON,
	  PD_SCU पूर्ण,
	अणु "ca53-cpu0",	0x200, 0, R8A7795_PD_CA53_CPU0,	R8A7795_PD_CA53_SCU,
	  PD_CPU_NOCR पूर्ण,
	अणु "ca53-cpu1",	0x200, 1, R8A7795_PD_CA53_CPU1,	R8A7795_PD_CA53_SCU,
	  PD_CPU_NOCR पूर्ण,
	अणु "ca53-cpu2",	0x200, 2, R8A7795_PD_CA53_CPU2,	R8A7795_PD_CA53_SCU,
	  PD_CPU_NOCR पूर्ण,
	अणु "ca53-cpu3",	0x200, 3, R8A7795_PD_CA53_CPU3,	R8A7795_PD_CA53_SCU,
	  PD_CPU_NOCR पूर्ण,
	अणु "a3vp",	0x340, 0, R8A7795_PD_A3VP,	R8A7795_PD_ALWAYS_ON पूर्ण,
	अणु "cr7",	0x240, 0, R8A7795_PD_CR7,	R8A7795_PD_ALWAYS_ON पूर्ण,
	अणु "a3vc",	0x380, 0, R8A7795_PD_A3VC,	R8A7795_PD_ALWAYS_ON पूर्ण,
	/* A2VC0 exists on ES1.x only */
	अणु "a2vc0",	0x3c0, 0, R8A7795_PD_A2VC0,	R8A7795_PD_A3VC पूर्ण,
	अणु "a2vc1",	0x3c0, 1, R8A7795_PD_A2VC1,	R8A7795_PD_A3VC पूर्ण,
	अणु "3dg-a",	0x100, 0, R8A7795_PD_3DG_A,	R8A7795_PD_ALWAYS_ON पूर्ण,
	अणु "3dg-b",	0x100, 1, R8A7795_PD_3DG_B,	R8A7795_PD_3DG_A पूर्ण,
	अणु "3dg-c",	0x100, 2, R8A7795_PD_3DG_C,	R8A7795_PD_3DG_B पूर्ण,
	अणु "3dg-d",	0x100, 3, R8A7795_PD_3DG_D,	R8A7795_PD_3DG_C पूर्ण,
	अणु "3dg-e",	0x100, 4, R8A7795_PD_3DG_E,	R8A7795_PD_3DG_D पूर्ण,
	अणु "a3ir",	0x180, 0, R8A7795_PD_A3IR,	R8A7795_PD_ALWAYS_ON पूर्ण,
पूर्ण;


	/*
	 * Fixups क्रम R-Car H3 revisions
	 */

#घोषणा HAS_A2VC0	BIT(0)		/* Power करोमुख्य A2VC0 is present */
#घोषणा NO_EXTMASK	BIT(1)		/* Missing SYSCEXTMASK रेजिस्टर */

अटल स्थिर काष्ठा soc_device_attribute r8a7795_quirks_match[] __initस्थिर = अणु
	अणु
		.soc_id = "r8a7795", .revision = "ES1.*",
		.data = (व्योम *)(HAS_A2VC0 | NO_EXTMASK),
	पूर्ण, अणु
		.soc_id = "r8a7795", .revision = "ES2.*",
		.data = (व्योम *)(NO_EXTMASK),
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल पूर्णांक __init r8a7795_sysc_init(व्योम)
अणु
	स्थिर काष्ठा soc_device_attribute *attr;
	u32 quirks = 0;

	attr = soc_device_match(r8a7795_quirks_match);
	अगर (attr)
		quirks = (uपूर्णांकptr_t)attr->data;

	अगर (!(quirks & HAS_A2VC0))
		rcar_sysc_nullअगरy(r8a7795_areas, ARRAY_SIZE(r8a7795_areas),
				  R8A7795_PD_A2VC0);

	अगर (quirks & NO_EXTMASK)
		r8a7795_sysc_info.exपंचांगask_val = 0;

	वापस 0;
पूर्ण

काष्ठा rcar_sysc_info r8a7795_sysc_info __initdata = अणु
	.init = r8a7795_sysc_init,
	.areas = r8a7795_areas,
	.num_areas = ARRAY_SIZE(r8a7795_areas),
	.exपंचांगask_offs = 0x2f8,
	.exपंचांगask_val = BIT(0),
पूर्ण;
