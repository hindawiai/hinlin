<शैली गुरु>
/*
 * arch/arm/mach-spear13xx/spear1310.c
 *
 * SPEAr1310 machine source file
 *
 * Copyright (C) 2012 ST Microelectronics
 * Viresh Kumar <vireshk@kernel.org>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#घोषणा pr_fmt(fmt) "SPEAr1310: " fmt

#समावेश <linux/amba/pl022.h>
#समावेश <linux/pata_arasan_cf_data.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश "generic.h"
#समावेश <mach/spear.h>

/* Base addresses */
#घोषणा SPEAR1310_RAS_GRP1_BASE			UL(0xD8000000)
#घोषणा VA_SPEAR1310_RAS_GRP1_BASE		UL(0xFA000000)

अटल व्योम __init spear1310_dt_init(व्योम)
अणु
	platक्रमm_device_रेजिस्टर_simple("spear-cpufreq", -1, शून्य, 0);
पूर्ण

अटल स्थिर अक्षर * स्थिर spear1310_dt_board_compat[] = अणु
	"st,spear1310",
	"st,spear1310-evb",
	शून्य,
पूर्ण;

/*
 * Following will create 16MB अटल भव/physical mappings
 * PHYSICAL		VIRTUAL
 * 0xD8000000		0xFA000000
 */
अटल काष्ठा map_desc spear1310_io_desc[] __initdata = अणु
	अणु
		.भव	= VA_SPEAR1310_RAS_GRP1_BASE,
		.pfn		= __phys_to_pfn(SPEAR1310_RAS_GRP1_BASE),
		.length		= SZ_16M,
		.type		= MT_DEVICE
	पूर्ण,
पूर्ण;

अटल व्योम __init spear1310_map_io(व्योम)
अणु
	iotable_init(spear1310_io_desc, ARRAY_SIZE(spear1310_io_desc));
	spear13xx_map_io();
पूर्ण

DT_MACHINE_START(SPEAR1310_DT, "ST SPEAr1310 SoC with Flattened Device Tree")
	.smp		=	smp_ops(spear13xx_smp_ops),
	.map_io		=	spear1310_map_io,
	.init_समय	=	spear13xx_समयr_init,
	.init_machine	=	spear1310_dt_init,
	.restart	=	spear_restart,
	.dt_compat	=	spear1310_dt_board_compat,
MACHINE_END
