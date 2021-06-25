<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2005 Nokia Corporation
 * Author: Paul Mundt <paul.mundt@nokia.com>
 *
 * Copyright (C) 2011 Texas Instruments Incorporated - https://www.ti.com/
 *
 * Modअगरied from the original mach-omap/omap2/board-generic.c did by Paul
 * to support the OMAP2+ device tree boards with an unique board file.
 */
#समावेश <linux/पन.स>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/घड़ीsource.h>

#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/प्रणाली_info.h>

#समावेश "common.h"

अटल स्थिर काष्ठा of_device_id omap_dt_match_table[] __initस्थिर = अणु
	अणु .compatible = "simple-bus", पूर्ण,
	अणु .compatible = "ti,omap-infra", पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल व्योम __init __maybe_unused omap_generic_init(व्योम)
अणु
	pdata_quirks_init(omap_dt_match_table);
	omap_soc_device_init();
पूर्ण

/* Clocks are needed early, see drivers/घड़ीsource क्रम the rest */
अटल व्योम __init __maybe_unused omap_init_समय_of(व्योम)
अणु
	omap_clk_init();
	समयr_probe();
पूर्ण

/* Used by am437x क्रम ARM समयr in non-SMP configurations */
#अगर !defined(CONFIG_SMP) && defined(CONFIG_GENERIC_CLOCKEVENTS_BROADCAST)
व्योम tick_broadcast(स्थिर काष्ठा cpumask *mask)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SOC_OMAP2420
अटल स्थिर अक्षर *स्थिर omap242x_boards_compat[] __initस्थिर = अणु
	"ti,omap2420",
	शून्य,
पूर्ण;

DT_MACHINE_START(OMAP242X_DT, "Generic OMAP2420 (Flattened Device Tree)")
	.reserve	= omap_reserve,
	.map_io		= omap242x_map_io,
	.init_early	= omap2420_init_early,
	.init_machine	= omap_generic_init,
	.init_समय	= omap_init_समय_of,
	.dt_compat	= omap242x_boards_compat,
	.restart	= omap2xxx_restart,
MACHINE_END
#पूर्ण_अगर

#अगर_घोषित CONFIG_SOC_OMAP2430
अटल स्थिर अक्षर *स्थिर omap243x_boards_compat[] __initस्थिर = अणु
	"ti,omap2430",
	शून्य,
पूर्ण;

DT_MACHINE_START(OMAP243X_DT, "Generic OMAP2430 (Flattened Device Tree)")
	.reserve	= omap_reserve,
	.map_io		= omap243x_map_io,
	.init_early	= omap2430_init_early,
	.init_machine	= omap_generic_init,
	.init_समय	= omap_init_समय_of,
	.dt_compat	= omap243x_boards_compat,
	.restart	= omap2xxx_restart,
MACHINE_END
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_OMAP3
/* Some boards need board name क्रम legacy userspace in /proc/cpuinfo */
अटल स्थिर अक्षर *स्थिर n900_boards_compat[] __initस्थिर = अणु
	"nokia,omap3-n900",
	शून्य,
पूर्ण;

/* Set प्रणाली_rev from atags */
अटल व्योम __init rx51_set_प्रणाली_rev(स्थिर काष्ठा tag *tags)
अणु
	स्थिर काष्ठा tag *tag;

	अगर (tags->hdr.tag != ATAG_CORE)
		वापस;

	क्रम_each_tag(tag, tags) अणु
		अगर (tag->hdr.tag == ATAG_REVISION) अणु
			प्रणाली_rev = tag->u.revision.rev;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/* Legacy userspace on Nokia N900 needs ATAGS exported in /proc/atags,
 * save them जबतक the data is still not overwritten
 */
अटल व्योम __init rx51_reserve(व्योम)
अणु
	स्थिर काष्ठा tag *tags = (स्थिर काष्ठा tag *)(PAGE_OFFSET + 0x100);

	save_atags(tags);
	rx51_set_प्रणाली_rev(tags);
	omap_reserve();
पूर्ण

DT_MACHINE_START(OMAP3_N900_DT, "Nokia RX-51 board")
	.reserve	= rx51_reserve,
	.map_io		= omap3_map_io,
	.init_early	= omap3430_init_early,
	.init_machine	= omap_generic_init,
	.init_late	= omap3_init_late,
	.init_समय	= omap_init_समय_of,
	.dt_compat	= n900_boards_compat,
	.restart	= omap3xxx_restart,
MACHINE_END

/* Generic omap3 boards, most boards can use these */
अटल स्थिर अक्षर *स्थिर omap3_boards_compat[] __initस्थिर = अणु
	"ti,omap3430",
	"ti,omap3",
	शून्य,
पूर्ण;

DT_MACHINE_START(OMAP3_DT, "Generic OMAP3 (Flattened Device Tree)")
	.reserve	= omap_reserve,
	.map_io		= omap3_map_io,
	.init_early	= omap3430_init_early,
	.init_machine	= omap_generic_init,
	.init_late	= omap3_init_late,
	.init_समय	= omap_init_समय_of,
	.dt_compat	= omap3_boards_compat,
	.restart	= omap3xxx_restart,
MACHINE_END

अटल स्थिर अक्षर *स्थिर omap36xx_boards_compat[] __initस्थिर = अणु
	"ti,omap3630",
	"ti,omap36xx",
	शून्य,
पूर्ण;

DT_MACHINE_START(OMAP36XX_DT, "Generic OMAP36xx (Flattened Device Tree)")
	.reserve	= omap_reserve,
	.map_io		= omap3_map_io,
	.init_early	= omap3630_init_early,
	.init_machine	= omap_generic_init,
	.init_late	= omap3_init_late,
	.init_समय	= omap_init_समय_of,
	.dt_compat	= omap36xx_boards_compat,
	.restart	= omap3xxx_restart,
MACHINE_END

अटल स्थिर अक्षर *स्थिर omap3_gp_boards_compat[] __initस्थिर = अणु
	"ti,omap3-beagle",
	"timll,omap3-devkit8000",
	शून्य,
पूर्ण;

DT_MACHINE_START(OMAP3_GP_DT, "Generic OMAP3-GP (Flattened Device Tree)")
	.reserve	= omap_reserve,
	.map_io		= omap3_map_io,
	.init_early	= omap3430_init_early,
	.init_machine	= omap_generic_init,
	.init_late	= omap3_init_late,
	.init_समय	= omap_init_समय_of,
	.dt_compat	= omap3_gp_boards_compat,
	.restart	= omap3xxx_restart,
MACHINE_END

अटल स्थिर अक्षर *स्थिर am3517_boards_compat[] __initस्थिर = अणु
	"ti,am3517",
	शून्य,
पूर्ण;

DT_MACHINE_START(AM3517_DT, "Generic AM3517 (Flattened Device Tree)")
	.reserve	= omap_reserve,
	.map_io		= omap3_map_io,
	.init_early	= am35xx_init_early,
	.init_machine	= omap_generic_init,
	.init_late	= omap3_init_late,
	.init_समय	= omap_init_समय_of,
	.dt_compat	= am3517_boards_compat,
	.restart	= omap3xxx_restart,
MACHINE_END
#पूर्ण_अगर

#अगर_घोषित CONFIG_SOC_TI81XX
अटल स्थिर अक्षर *स्थिर ti814x_boards_compat[] __initस्थिर = अणु
	"ti,dm8148",
	"ti,dm814",
	शून्य,
पूर्ण;

DT_MACHINE_START(TI814X_DT, "Generic ti814x (Flattened Device Tree)")
	.reserve	= omap_reserve,
	.map_io		= ti81xx_map_io,
	.init_early	= ti814x_init_early,
	.init_machine	= omap_generic_init,
	.init_late	= ti81xx_init_late,
	.init_समय	= omap_init_समय_of,
	.dt_compat	= ti814x_boards_compat,
	.restart	= ti81xx_restart,
MACHINE_END

अटल स्थिर अक्षर *स्थिर ti816x_boards_compat[] __initस्थिर = अणु
	"ti,dm8168",
	"ti,dm816",
	शून्य,
पूर्ण;

DT_MACHINE_START(TI816X_DT, "Generic ti816x (Flattened Device Tree)")
	.reserve	= omap_reserve,
	.map_io		= ti81xx_map_io,
	.init_early	= ti816x_init_early,
	.init_machine	= omap_generic_init,
	.init_late	= ti81xx_init_late,
	.init_समय	= omap_init_समय_of,
	.dt_compat	= ti816x_boards_compat,
	.restart	= ti81xx_restart,
MACHINE_END
#पूर्ण_अगर

#अगर_घोषित CONFIG_SOC_AM33XX
अटल स्थिर अक्षर *स्थिर am33xx_boards_compat[] __initस्थिर = अणु
	"ti,am33xx",
	शून्य,
पूर्ण;

DT_MACHINE_START(AM33XX_DT, "Generic AM33XX (Flattened Device Tree)")
	.reserve	= omap_reserve,
	.map_io		= am33xx_map_io,
	.init_early	= am33xx_init_early,
	.init_machine	= omap_generic_init,
	.init_late	= am33xx_init_late,
	.init_समय	= omap_init_समय_of,
	.dt_compat	= am33xx_boards_compat,
	.restart	= am33xx_restart,
MACHINE_END
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_OMAP4
अटल स्थिर अक्षर *स्थिर omap4_boards_compat[] __initस्थिर = अणु
	"ti,omap4460",
	"ti,omap4430",
	"ti,omap4",
	शून्य,
पूर्ण;

DT_MACHINE_START(OMAP4_DT, "Generic OMAP4 (Flattened Device Tree)")
	.l2c_aux_val	= OMAP_L2C_AUX_CTRL,
	.l2c_aux_mask	= 0xcf9fffff,
	.l2c_ग_लिखो_sec	= omap4_l2c310_ग_लिखो_sec,
	.reserve	= omap_reserve,
	.smp		= smp_ops(omap4_smp_ops),
	.map_io		= omap4_map_io,
	.init_early	= omap4430_init_early,
	.init_irq	= omap_gic_of_init,
	.init_machine	= omap_generic_init,
	.init_late	= omap4430_init_late,
	.init_समय	= omap_init_समय_of,
	.dt_compat	= omap4_boards_compat,
	.restart	= omap44xx_restart,
MACHINE_END
#पूर्ण_अगर

#अगर_घोषित CONFIG_SOC_OMAP5
अटल स्थिर अक्षर *स्थिर omap5_boards_compat[] __initस्थिर = अणु
	"ti,omap5432",
	"ti,omap5430",
	"ti,omap5",
	शून्य,
पूर्ण;

DT_MACHINE_START(OMAP5_DT, "Generic OMAP5 (Flattened Device Tree)")
#अगर defined(CONFIG_ZONE_DMA) && defined(CONFIG_ARM_LPAE)
	.dma_zone_size	= SZ_2G,
#पूर्ण_अगर
	.reserve	= omap_reserve,
	.smp		= smp_ops(omap4_smp_ops),
	.map_io		= omap5_map_io,
	.init_early	= omap5_init_early,
	.init_irq	= omap_gic_of_init,
	.init_machine	= omap_generic_init,
	.init_late	= omap5_init_late,
	.init_समय	= omap5_realसमय_प्रकारimer_init,
	.dt_compat	= omap5_boards_compat,
	.restart	= omap44xx_restart,
MACHINE_END
#पूर्ण_अगर

#अगर_घोषित CONFIG_SOC_AM43XX
अटल स्थिर अक्षर *स्थिर am43_boards_compat[] __initस्थिर = अणु
	"ti,am4372",
	"ti,am43",
	शून्य,
पूर्ण;

DT_MACHINE_START(AM43_DT, "Generic AM43 (Flattened Device Tree)")
	.l2c_aux_val	= OMAP_L2C_AUX_CTRL,
	.l2c_aux_mask	= 0xcf9fffff,
	.l2c_ग_लिखो_sec	= omap4_l2c310_ग_लिखो_sec,
	.map_io		= am33xx_map_io,
	.init_early	= am43xx_init_early,
	.init_late	= am43xx_init_late,
	.init_irq	= omap_gic_of_init,
	.init_machine	= omap_generic_init,
	.init_समय	= omap_init_समय_of,
	.dt_compat	= am43_boards_compat,
	.restart	= omap44xx_restart,
MACHINE_END
#पूर्ण_अगर

#अगर_घोषित CONFIG_SOC_DRA7XX
अटल स्थिर अक्षर *स्थिर dra74x_boards_compat[] __initस्थिर = अणु
	"ti,dra762",
	"ti,am5728",
	"ti,am5726",
	"ti,dra742",
	"ti,dra7",
	शून्य,
पूर्ण;

DT_MACHINE_START(DRA74X_DT, "Generic DRA74X (Flattened Device Tree)")
#अगर defined(CONFIG_ZONE_DMA) && defined(CONFIG_ARM_LPAE)
	.dma_zone_size	= SZ_2G,
#पूर्ण_अगर
	.reserve	= omap_reserve,
	.smp		= smp_ops(omap4_smp_ops),
	.map_io		= dra7xx_map_io,
	.init_early	= dra7xx_init_early,
	.init_late	= dra7xx_init_late,
	.init_irq	= omap_gic_of_init,
	.init_machine	= omap_generic_init,
	.init_समय	= omap5_realसमय_प्रकारimer_init,
	.dt_compat	= dra74x_boards_compat,
	.restart	= omap44xx_restart,
MACHINE_END

अटल स्थिर अक्षर *स्थिर dra72x_boards_compat[] __initस्थिर = अणु
	"ti,am5718",
	"ti,am5716",
	"ti,dra722",
	"ti,dra718",
	शून्य,
पूर्ण;

DT_MACHINE_START(DRA72X_DT, "Generic DRA72X (Flattened Device Tree)")
#अगर defined(CONFIG_ZONE_DMA) && defined(CONFIG_ARM_LPAE)
	.dma_zone_size	= SZ_2G,
#पूर्ण_अगर
	.reserve	= omap_reserve,
	.map_io		= dra7xx_map_io,
	.init_early	= dra7xx_init_early,
	.init_late	= dra7xx_init_late,
	.init_irq	= omap_gic_of_init,
	.init_machine	= omap_generic_init,
	.init_समय	= omap5_realसमय_प्रकारimer_init,
	.dt_compat	= dra72x_boards_compat,
	.restart	= omap44xx_restart,
MACHINE_END
#पूर्ण_अगर
