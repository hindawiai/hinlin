<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/arch/arm/mach-omap2/io.c
 *
 * OMAP2 I/O mapping code
 *
 * Copyright (C) 2005 Nokia Corporation
 * Copyright (C) 2007-2009 Texas Instruments
 *
 * Author:
 *	Juha Yrjola <juha.yrjola@nokia.com>
 *	Syed Khasim <x0khasim@ti.com>
 *
 * Added OMAP4 support - Santosh Shilimkar <santosh.shilimkar@ti.com>
 */
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/clk.h>

#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/mach/map.h>

#समावेश <linux/omap-dma.h>

#समावेश "omap_hwmod.h"
#समावेश "soc.h"
#समावेश "iomap.h"
#समावेश "voltage.h"
#समावेश "powerdomain.h"
#समावेश "clockdomain.h"
#समावेश "common.h"
#समावेश "clock.h"
#समावेश "clock2xxx.h"
#समावेश "clock3xxx.h"
#समावेश "sdrc.h"
#समावेश "control.h"
#समावेश "serial.h"
#समावेश "sram.h"
#समावेश "cm2xxx.h"
#समावेश "cm3xxx.h"
#समावेश "cm33xx.h"
#समावेश "cm44xx.h"
#समावेश "prm.h"
#समावेश "cm.h"
#समावेश "prcm_mpu44xx.h"
#समावेश "prminst44xx.h"
#समावेश "prm2xxx.h"
#समावेश "prm3xxx.h"
#समावेश "prm33xx.h"
#समावेश "prm44xx.h"
#समावेश "opp2xxx.h"
#समावेश "omap-secure.h"

/*
 * omap_clk_soc_init: poपूर्णांकs to a function that करोes the SoC-specअगरic
 * घड़ी initializations
 */
अटल पूर्णांक (*omap_clk_soc_init)(व्योम);

/*
 * The machine specअगरic code may provide the extra mapping besides the
 * शेष mapping provided here.
 */

#अगर defined(CONFIG_SOC_OMAP2420) || defined(CONFIG_SOC_OMAP2430)
अटल काष्ठा map_desc omap24xx_io_desc[] __initdata = अणु
	अणु
		.भव	= L3_24XX_VIRT,
		.pfn		= __phys_to_pfn(L3_24XX_PHYS),
		.length		= L3_24XX_SIZE,
		.type		= MT_DEVICE
	पूर्ण,
	अणु
		.भव	= L4_24XX_VIRT,
		.pfn		= __phys_to_pfn(L4_24XX_PHYS),
		.length		= L4_24XX_SIZE,
		.type		= MT_DEVICE
	पूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_SOC_OMAP2420
अटल काष्ठा map_desc omap242x_io_desc[] __initdata = अणु
	अणु
		.भव	= DSP_MEM_2420_VIRT,
		.pfn		= __phys_to_pfn(DSP_MEM_2420_PHYS),
		.length		= DSP_MEM_2420_SIZE,
		.type		= MT_DEVICE
	पूर्ण,
	अणु
		.भव	= DSP_IPI_2420_VIRT,
		.pfn		= __phys_to_pfn(DSP_IPI_2420_PHYS),
		.length		= DSP_IPI_2420_SIZE,
		.type		= MT_DEVICE
	पूर्ण,
	अणु
		.भव	= DSP_MMU_2420_VIRT,
		.pfn		= __phys_to_pfn(DSP_MMU_2420_PHYS),
		.length		= DSP_MMU_2420_SIZE,
		.type		= MT_DEVICE
	पूर्ण,
पूर्ण;

#पूर्ण_अगर

#अगर_घोषित CONFIG_SOC_OMAP2430
अटल काष्ठा map_desc omap243x_io_desc[] __initdata = अणु
	अणु
		.भव	= L4_WK_243X_VIRT,
		.pfn		= __phys_to_pfn(L4_WK_243X_PHYS),
		.length		= L4_WK_243X_SIZE,
		.type		= MT_DEVICE
	पूर्ण,
	अणु
		.भव	= OMAP243X_GPMC_VIRT,
		.pfn		= __phys_to_pfn(OMAP243X_GPMC_PHYS),
		.length		= OMAP243X_GPMC_SIZE,
		.type		= MT_DEVICE
	पूर्ण,
	अणु
		.भव	= OMAP243X_SDRC_VIRT,
		.pfn		= __phys_to_pfn(OMAP243X_SDRC_PHYS),
		.length		= OMAP243X_SDRC_SIZE,
		.type		= MT_DEVICE
	पूर्ण,
	अणु
		.भव	= OMAP243X_SMS_VIRT,
		.pfn		= __phys_to_pfn(OMAP243X_SMS_PHYS),
		.length		= OMAP243X_SMS_SIZE,
		.type		= MT_DEVICE
	पूर्ण,
पूर्ण;
#पूर्ण_अगर
#पूर्ण_अगर

#अगर_घोषित	CONFIG_ARCH_OMAP3
अटल काष्ठा map_desc omap34xx_io_desc[] __initdata = अणु
	अणु
		.भव	= L3_34XX_VIRT,
		.pfn		= __phys_to_pfn(L3_34XX_PHYS),
		.length		= L3_34XX_SIZE,
		.type		= MT_DEVICE
	पूर्ण,
	अणु
		.भव	= L4_34XX_VIRT,
		.pfn		= __phys_to_pfn(L4_34XX_PHYS),
		.length		= L4_34XX_SIZE,
		.type		= MT_DEVICE
	पूर्ण,
	अणु
		.भव	= OMAP34XX_GPMC_VIRT,
		.pfn		= __phys_to_pfn(OMAP34XX_GPMC_PHYS),
		.length		= OMAP34XX_GPMC_SIZE,
		.type		= MT_DEVICE
	पूर्ण,
	अणु
		.भव	= OMAP343X_SMS_VIRT,
		.pfn		= __phys_to_pfn(OMAP343X_SMS_PHYS),
		.length		= OMAP343X_SMS_SIZE,
		.type		= MT_DEVICE
	पूर्ण,
	अणु
		.भव	= OMAP343X_SDRC_VIRT,
		.pfn		= __phys_to_pfn(OMAP343X_SDRC_PHYS),
		.length		= OMAP343X_SDRC_SIZE,
		.type		= MT_DEVICE
	पूर्ण,
	अणु
		.भव	= L4_PER_34XX_VIRT,
		.pfn		= __phys_to_pfn(L4_PER_34XX_PHYS),
		.length		= L4_PER_34XX_SIZE,
		.type		= MT_DEVICE
	पूर्ण,
	अणु
		.भव	= L4_EMU_34XX_VIRT,
		.pfn		= __phys_to_pfn(L4_EMU_34XX_PHYS),
		.length		= L4_EMU_34XX_SIZE,
		.type		= MT_DEVICE
	पूर्ण,
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_SOC_TI81XX
अटल काष्ठा map_desc omapti81xx_io_desc[] __initdata = अणु
	अणु
		.भव	= L4_34XX_VIRT,
		.pfn		= __phys_to_pfn(L4_34XX_PHYS),
		.length		= L4_34XX_SIZE,
		.type		= MT_DEVICE
	पूर्ण
पूर्ण;
#पूर्ण_अगर

#अगर defined(CONFIG_SOC_AM33XX) || defined(CONFIG_SOC_AM43XX)
अटल काष्ठा map_desc omapam33xx_io_desc[] __initdata = अणु
	अणु
		.भव	= L4_34XX_VIRT,
		.pfn		= __phys_to_pfn(L4_34XX_PHYS),
		.length		= L4_34XX_SIZE,
		.type		= MT_DEVICE
	पूर्ण,
	अणु
		.भव	= L4_WK_AM33XX_VIRT,
		.pfn		= __phys_to_pfn(L4_WK_AM33XX_PHYS),
		.length		= L4_WK_AM33XX_SIZE,
		.type		= MT_DEVICE
	पूर्ण
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित	CONFIG_ARCH_OMAP4
अटल काष्ठा map_desc omap44xx_io_desc[] __initdata = अणु
	अणु
		.भव	= L3_44XX_VIRT,
		.pfn		= __phys_to_pfn(L3_44XX_PHYS),
		.length		= L3_44XX_SIZE,
		.type		= MT_DEVICE,
	पूर्ण,
	अणु
		.भव	= L4_44XX_VIRT,
		.pfn		= __phys_to_pfn(L4_44XX_PHYS),
		.length		= L4_44XX_SIZE,
		.type		= MT_DEVICE,
	पूर्ण,
	अणु
		.भव	= L4_PER_44XX_VIRT,
		.pfn		= __phys_to_pfn(L4_PER_44XX_PHYS),
		.length		= L4_PER_44XX_SIZE,
		.type		= MT_DEVICE,
	पूर्ण,
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_SOC_OMAP5
अटल काष्ठा map_desc omap54xx_io_desc[] __initdata = अणु
	अणु
		.भव	= L3_54XX_VIRT,
		.pfn		= __phys_to_pfn(L3_54XX_PHYS),
		.length		= L3_54XX_SIZE,
		.type		= MT_DEVICE,
	पूर्ण,
	अणु
		.भव	= L4_54XX_VIRT,
		.pfn		= __phys_to_pfn(L4_54XX_PHYS),
		.length		= L4_54XX_SIZE,
		.type		= MT_DEVICE,
	पूर्ण,
	अणु
		.भव	= L4_WK_54XX_VIRT,
		.pfn		= __phys_to_pfn(L4_WK_54XX_PHYS),
		.length		= L4_WK_54XX_SIZE,
		.type		= MT_DEVICE,
	पूर्ण,
	अणु
		.भव	= L4_PER_54XX_VIRT,
		.pfn		= __phys_to_pfn(L4_PER_54XX_PHYS),
		.length		= L4_PER_54XX_SIZE,
		.type		= MT_DEVICE,
	पूर्ण,
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_SOC_DRA7XX
अटल काष्ठा map_desc dra7xx_io_desc[] __initdata = अणु
	अणु
		.भव	= L4_CFG_MPU_DRA7XX_VIRT,
		.pfn		= __phys_to_pfn(L4_CFG_MPU_DRA7XX_PHYS),
		.length		= L4_CFG_MPU_DRA7XX_SIZE,
		.type		= MT_DEVICE,
	पूर्ण,
	अणु
		.भव	= L3_MAIN_SN_DRA7XX_VIRT,
		.pfn		= __phys_to_pfn(L3_MAIN_SN_DRA7XX_PHYS),
		.length		= L3_MAIN_SN_DRA7XX_SIZE,
		.type		= MT_DEVICE,
	पूर्ण,
	अणु
		.भव	= L4_PER1_DRA7XX_VIRT,
		.pfn		= __phys_to_pfn(L4_PER1_DRA7XX_PHYS),
		.length		= L4_PER1_DRA7XX_SIZE,
		.type		= MT_DEVICE,
	पूर्ण,
	अणु
		.भव	= L4_PER2_DRA7XX_VIRT,
		.pfn		= __phys_to_pfn(L4_PER2_DRA7XX_PHYS),
		.length		= L4_PER2_DRA7XX_SIZE,
		.type		= MT_DEVICE,
	पूर्ण,
	अणु
		.भव	= L4_PER3_DRA7XX_VIRT,
		.pfn		= __phys_to_pfn(L4_PER3_DRA7XX_PHYS),
		.length		= L4_PER3_DRA7XX_SIZE,
		.type		= MT_DEVICE,
	पूर्ण,
	अणु
		.भव	= L4_CFG_DRA7XX_VIRT,
		.pfn		= __phys_to_pfn(L4_CFG_DRA7XX_PHYS),
		.length		= L4_CFG_DRA7XX_SIZE,
		.type		= MT_DEVICE,
	पूर्ण,
	अणु
		.भव	= L4_WKUP_DRA7XX_VIRT,
		.pfn		= __phys_to_pfn(L4_WKUP_DRA7XX_PHYS),
		.length		= L4_WKUP_DRA7XX_SIZE,
		.type		= MT_DEVICE,
	पूर्ण,
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_SOC_OMAP2420
व्योम __init omap242x_map_io(व्योम)
अणु
	iotable_init(omap24xx_io_desc, ARRAY_SIZE(omap24xx_io_desc));
	iotable_init(omap242x_io_desc, ARRAY_SIZE(omap242x_io_desc));
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SOC_OMAP2430
व्योम __init omap243x_map_io(व्योम)
अणु
	iotable_init(omap24xx_io_desc, ARRAY_SIZE(omap24xx_io_desc));
	iotable_init(omap243x_io_desc, ARRAY_SIZE(omap243x_io_desc));
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_OMAP3
व्योम __init omap3_map_io(व्योम)
अणु
	iotable_init(omap34xx_io_desc, ARRAY_SIZE(omap34xx_io_desc));
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SOC_TI81XX
व्योम __init ti81xx_map_io(व्योम)
अणु
	iotable_init(omapti81xx_io_desc, ARRAY_SIZE(omapti81xx_io_desc));
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_SOC_AM33XX) || defined(CONFIG_SOC_AM43XX)
व्योम __init am33xx_map_io(व्योम)
अणु
	iotable_init(omapam33xx_io_desc, ARRAY_SIZE(omapam33xx_io_desc));
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_OMAP4
व्योम __init omap4_map_io(व्योम)
अणु
	iotable_init(omap44xx_io_desc, ARRAY_SIZE(omap44xx_io_desc));
	omap_barriers_init();
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SOC_OMAP5
व्योम __init omap5_map_io(व्योम)
अणु
	iotable_init(omap54xx_io_desc, ARRAY_SIZE(omap54xx_io_desc));
	omap_barriers_init();
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SOC_DRA7XX
व्योम __init dra7xx_map_io(व्योम)
अणु
	iotable_init(dra7xx_io_desc, ARRAY_SIZE(dra7xx_io_desc));
	omap_barriers_init();
पूर्ण
#पूर्ण_अगर
/*
 * omap2_init_reprogram_sdrc - reprogram SDRC timing parameters
 *
 * Sets the CORE DPLL3 M2 भागider to the same value that it's at
 * currently.  This has the effect of setting the SDRC SDRAM AC timing
 * रेजिस्टरs to the values currently defined by the kernel.  Currently
 * only defined क्रम OMAP3; will वापस 0 अगर called on OMAP2.  Returns
 * -EINVAL अगर the dpll3_m2_ck cannot be found, 0 अगर called on OMAP2,
 * or passes aदीर्घ the वापस value of clk_set_rate().
 */
अटल पूर्णांक __init _omap2_init_reprogram_sdrc(व्योम)
अणु
	काष्ठा clk *dpll3_m2_ck;
	पूर्णांक v = -EINVAL;
	दीर्घ rate;

	अगर (!cpu_is_omap34xx())
		वापस 0;

	dpll3_m2_ck = clk_get(शून्य, "dpll3_m2_ck");
	अगर (IS_ERR(dpll3_m2_ck))
		वापस -EINVAL;

	rate = clk_get_rate(dpll3_m2_ck);
	pr_info("Reprogramming SDRC clock to %ld Hz\n", rate);
	v = clk_set_rate(dpll3_m2_ck, rate);
	अगर (v)
		pr_err("dpll3_m2_clk rate change failed: %d\n", v);

	clk_put(dpll3_m2_ck);

	वापस v;
पूर्ण

#अगर_घोषित CONFIG_OMAP_HWMOD
अटल पूर्णांक _set_hwmod_postsetup_state(काष्ठा omap_hwmod *oh, व्योम *data)
अणु
	वापस omap_hwmod_set_postsetup_state(oh, *(u8 *)data);
पूर्ण

अटल व्योम __init __maybe_unused omap_hwmod_init_postsetup(व्योम)
अणु
	u8 postsetup_state = _HWMOD_STATE_DEFAULT;

	/* Set the शेष postsetup state क्रम all hwmods */
	omap_hwmod_क्रम_each(_set_hwmod_postsetup_state, &postsetup_state);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम omap_hwmod_init_postsetup(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SOC_OMAP2420
व्योम __init omap2420_init_early(व्योम)
अणु
	omap2_set_globals_tap(OMAP242X_CLASS, OMAP2_L4_IO_ADDRESS(0x48014000));
	omap2_set_globals_sdrc(OMAP2_L3_IO_ADDRESS(OMAP2420_SDRC_BASE),
			       OMAP2_L3_IO_ADDRESS(OMAP2420_SMS_BASE));
	omap2_control_base_init();
	omap2xxx_check_revision();
	omap2_prcm_base_init();
	omap2xxx_voltageकरोमुख्यs_init();
	omap242x_घातerकरोमुख्यs_init();
	omap242x_घड़ीकरोमुख्यs_init();
	omap2420_hwmod_init();
	omap_hwmod_init_postsetup();
	omap_clk_soc_init = omap2420_dt_clk_init;
	rate_table = omap2420_rate_table;
पूर्ण

व्योम __init omap2420_init_late(व्योम)
अणु
	omap_pm_soc_init = omap2_pm_init;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SOC_OMAP2430
व्योम __init omap2430_init_early(व्योम)
अणु
	omap2_set_globals_tap(OMAP243X_CLASS, OMAP2_L4_IO_ADDRESS(0x4900a000));
	omap2_set_globals_sdrc(OMAP2_L3_IO_ADDRESS(OMAP243X_SDRC_BASE),
			       OMAP2_L3_IO_ADDRESS(OMAP243X_SMS_BASE));
	omap2_control_base_init();
	omap2xxx_check_revision();
	omap2_prcm_base_init();
	omap2xxx_voltageकरोमुख्यs_init();
	omap243x_घातerकरोमुख्यs_init();
	omap243x_घड़ीकरोमुख्यs_init();
	omap2430_hwmod_init();
	omap_hwmod_init_postsetup();
	omap_clk_soc_init = omap2430_dt_clk_init;
	rate_table = omap2430_rate_table;
पूर्ण

व्योम __init omap2430_init_late(व्योम)
अणु
	omap_pm_soc_init = omap2_pm_init;
पूर्ण
#पूर्ण_अगर

/*
 * Currently only board-omap3beagle.c should call this because of the
 * same machine_id क्रम 34xx and 36xx beagle.. Will get fixed with DT.
 */
#अगर_घोषित CONFIG_ARCH_OMAP3
व्योम __init omap3_init_early(व्योम)
अणु
	omap2_set_globals_tap(OMAP343X_CLASS, OMAP2_L4_IO_ADDRESS(0x4830A000));
	omap2_set_globals_sdrc(OMAP2_L3_IO_ADDRESS(OMAP343X_SDRC_BASE),
			       OMAP2_L3_IO_ADDRESS(OMAP343X_SMS_BASE));
	omap2_control_base_init();
	omap3xxx_check_revision();
	omap3xxx_check_features();
	omap2_prcm_base_init();
	omap3xxx_voltageकरोमुख्यs_init();
	omap3xxx_घातerकरोमुख्यs_init();
	omap3xxx_घड़ीकरोमुख्यs_init();
	omap3xxx_hwmod_init();
	omap_hwmod_init_postsetup();
	omap_secure_init();
पूर्ण

व्योम __init omap3430_init_early(व्योम)
अणु
	omap3_init_early();
	omap_clk_soc_init = omap3430_dt_clk_init;
पूर्ण

व्योम __init omap35xx_init_early(व्योम)
अणु
	omap3_init_early();
	omap_clk_soc_init = omap3430_dt_clk_init;
पूर्ण

व्योम __init omap3630_init_early(व्योम)
अणु
	omap3_init_early();
	omap_clk_soc_init = omap3630_dt_clk_init;
पूर्ण

व्योम __init am35xx_init_early(व्योम)
अणु
	omap3_init_early();
	omap_clk_soc_init = am35xx_dt_clk_init;
पूर्ण

व्योम __init omap3_init_late(व्योम)
अणु
	omap_pm_soc_init = omap3_pm_init;
पूर्ण

व्योम __init ti81xx_init_late(व्योम)
अणु
	omap_pm_soc_init = omap_pm_nop_init;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SOC_TI81XX
व्योम __init ti814x_init_early(व्योम)
अणु
	omap2_set_globals_tap(TI814X_CLASS,
			      OMAP2_L4_IO_ADDRESS(TI81XX_TAP_BASE));
	omap2_control_base_init();
	omap3xxx_check_revision();
	ti81xx_check_features();
	omap2_prcm_base_init();
	omap3xxx_voltageकरोमुख्यs_init();
	omap3xxx_घातerकरोमुख्यs_init();
	ti814x_घड़ीकरोमुख्यs_init();
	dm814x_hwmod_init();
	omap_hwmod_init_postsetup();
	omap_clk_soc_init = dm814x_dt_clk_init;
	omap_secure_init();
पूर्ण

व्योम __init ti816x_init_early(व्योम)
अणु
	omap2_set_globals_tap(TI816X_CLASS,
			      OMAP2_L4_IO_ADDRESS(TI81XX_TAP_BASE));
	omap2_control_base_init();
	omap3xxx_check_revision();
	ti81xx_check_features();
	omap2_prcm_base_init();
	omap3xxx_voltageकरोमुख्यs_init();
	omap3xxx_घातerकरोमुख्यs_init();
	ti816x_घड़ीकरोमुख्यs_init();
	dm816x_hwmod_init();
	omap_hwmod_init_postsetup();
	omap_clk_soc_init = dm816x_dt_clk_init;
	omap_secure_init();
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SOC_AM33XX
व्योम __init am33xx_init_early(व्योम)
अणु
	omap2_set_globals_tap(AM335X_CLASS,
			      AM33XX_L4_WK_IO_ADDRESS(AM33XX_TAP_BASE));
	omap2_control_base_init();
	omap3xxx_check_revision();
	am33xx_check_features();
	omap2_prcm_base_init();
	am33xx_घातerकरोमुख्यs_init();
	am33xx_घड़ीकरोमुख्यs_init();
	omap_clk_soc_init = am33xx_dt_clk_init;
	omap_secure_init();
पूर्ण

व्योम __init am33xx_init_late(व्योम)
अणु
	omap_pm_soc_init = amx3_common_pm_init;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SOC_AM43XX
व्योम __init am43xx_init_early(व्योम)
अणु
	omap2_set_globals_tap(AM335X_CLASS,
			      AM33XX_L4_WK_IO_ADDRESS(AM33XX_TAP_BASE));
	omap2_control_base_init();
	omap3xxx_check_revision();
	am33xx_check_features();
	omap2_prcm_base_init();
	am43xx_घातerकरोमुख्यs_init();
	am43xx_घड़ीकरोमुख्यs_init();
	omap_l2_cache_init();
	omap_clk_soc_init = am43xx_dt_clk_init;
	omap_secure_init();
पूर्ण

व्योम __init am43xx_init_late(व्योम)
अणु
	omap_pm_soc_init = amx3_common_pm_init;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_OMAP4
व्योम __init omap4430_init_early(व्योम)
अणु
	omap2_set_globals_tap(OMAP443X_CLASS,
			      OMAP2_L4_IO_ADDRESS(OMAP443X_SCM_BASE));
	omap2_set_globals_prcm_mpu(OMAP2_L4_IO_ADDRESS(OMAP4430_PRCM_MPU_BASE));
	omap2_control_base_init();
	omap4xxx_check_revision();
	omap4xxx_check_features();
	omap2_prcm_base_init();
	omap4_sar_ram_init();
	omap4_mpuss_early_init();
	omap4_pm_init_early();
	omap44xx_voltageकरोमुख्यs_init();
	omap44xx_घातerकरोमुख्यs_init();
	omap44xx_घड़ीकरोमुख्यs_init();
	omap_l2_cache_init();
	omap_clk_soc_init = omap4xxx_dt_clk_init;
	omap_secure_init();
पूर्ण

व्योम __init omap4430_init_late(व्योम)
अणु
	omap_pm_soc_init = omap4_pm_init;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SOC_OMAP5
व्योम __init omap5_init_early(व्योम)
अणु
	omap2_set_globals_tap(OMAP54XX_CLASS,
			      OMAP2_L4_IO_ADDRESS(OMAP54XX_SCM_BASE));
	omap2_set_globals_prcm_mpu(OMAP2_L4_IO_ADDRESS(OMAP54XX_PRCM_MPU_BASE));
	omap2_control_base_init();
	omap2_prcm_base_init();
	omap5xxx_check_revision();
	omap4_sar_ram_init();
	omap4_mpuss_early_init();
	omap4_pm_init_early();
	omap54xx_voltageकरोमुख्यs_init();
	omap54xx_घातerकरोमुख्यs_init();
	omap54xx_घड़ीकरोमुख्यs_init();
	omap_clk_soc_init = omap5xxx_dt_clk_init;
	omap_secure_init();
पूर्ण

व्योम __init omap5_init_late(व्योम)
अणु
	omap_pm_soc_init = omap4_pm_init;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SOC_DRA7XX
व्योम __init dra7xx_init_early(व्योम)
अणु
	omap2_set_globals_tap(DRA7XX_CLASS,
			      OMAP2_L4_IO_ADDRESS(DRA7XX_TAP_BASE));
	omap2_set_globals_prcm_mpu(OMAP2_L4_IO_ADDRESS(OMAP54XX_PRCM_MPU_BASE));
	omap2_control_base_init();
	omap4_pm_init_early();
	omap2_prcm_base_init();
	dra7xxx_check_revision();
	dra7xx_घातerकरोमुख्यs_init();
	dra7xx_घड़ीकरोमुख्यs_init();
	omap_clk_soc_init = dra7xx_dt_clk_init;
	omap_secure_init();
पूर्ण

व्योम __init dra7xx_init_late(व्योम)
अणु
	omap_pm_soc_init = omap4_pm_init;
पूर्ण
#पूर्ण_अगर


व्योम __init omap_sdrc_init(काष्ठा omap_sdrc_params *sdrc_cs0,
				      काष्ठा omap_sdrc_params *sdrc_cs1)
अणु
	omap_sram_init();

	अगर (cpu_is_omap24xx() || omap3_has_sdrc()) अणु
		omap2_sdrc_init(sdrc_cs0, sdrc_cs1);
		_omap2_init_reprogram_sdrc();
	पूर्ण
पूर्ण

पूर्णांक __init omap_clk_init(व्योम)
अणु
	पूर्णांक ret = 0;

	अगर (!omap_clk_soc_init)
		वापस 0;

	ti_clk_init_features();

	omap2_clk_setup_ll_ops();

	ret = omap_control_init();
	अगर (ret)
		वापस ret;

	ret = omap_prcm_init();
	अगर (ret)
		वापस ret;

	of_clk_init(शून्य);

	ti_dt_clk_init_retry_clks();

	ti_dt_घड़ीकरोमुख्यs_setup();

	ret = omap_clk_soc_init();

	वापस ret;
पूर्ण
