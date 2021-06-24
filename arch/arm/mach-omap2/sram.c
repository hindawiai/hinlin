<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * OMAP SRAM detection and management
 *
 * Copyright (C) 2005 Nokia Corporation
 * Written by Tony Lindgren <tony@atomide.com>
 *
 * Copyright (C) 2009-2012 Texas Instruments
 * Added OMAP4/5 support - Santosh Shilimkar <santosh.shilimkar@ti.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/fncpy.h>
#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/cacheflush.h>

#समावेश <यंत्र/mach/map.h>

#समावेश "soc.h"
#समावेश "iomap.h"
#समावेश "prm2xxx_3xxx.h"
#समावेश "sdrc.h"
#समावेश "sram.h"

#घोषणा OMAP2_SRAM_PUB_PA	(OMAP2_SRAM_PA + 0xf800)
#घोषणा OMAP3_SRAM_PUB_PA       (OMAP3_SRAM_PA + 0x8000)

#घोषणा SRAM_BOOTLOADER_SZ	0x00

#घोषणा OMAP24XX_VA_REQINFOPERM0	OMAP2_L3_IO_ADDRESS(0x68005048)
#घोषणा OMAP24XX_VA_READPERM0		OMAP2_L3_IO_ADDRESS(0x68005050)
#घोषणा OMAP24XX_VA_WRITEPERM0		OMAP2_L3_IO_ADDRESS(0x68005058)

#घोषणा OMAP34XX_VA_REQINFOPERM0	OMAP2_L3_IO_ADDRESS(0x68012848)
#घोषणा OMAP34XX_VA_READPERM0		OMAP2_L3_IO_ADDRESS(0x68012850)
#घोषणा OMAP34XX_VA_WRITEPERM0		OMAP2_L3_IO_ADDRESS(0x68012858)
#घोषणा OMAP34XX_VA_ADDR_MATCH2		OMAP2_L3_IO_ADDRESS(0x68012880)
#घोषणा OMAP34XX_VA_SMS_RG_ATT0		OMAP2_L3_IO_ADDRESS(0x6C000048)

#घोषणा GP_DEVICE		0x300

#घोषणा ROUND_DOWN(value,boundary)	((value) & (~((boundary)-1)))

अटल अचिन्हित दीर्घ omap_sram_start;
अटल अचिन्हित दीर्घ omap_sram_skip;
अटल अचिन्हित दीर्घ omap_sram_size;

/*
 * Depending on the target RAMFS firewall setup, the खुला usable amount of
 * SRAM varies.  The शेष accessible size क्रम all device types is 2k. A GP
 * device allows ARM11 but not other initiators क्रम full size. This
 * functionality seems ok until some nice security API happens.
 */
अटल पूर्णांक is_sram_locked(व्योम)
अणु
	अगर (OMAP2_DEVICE_TYPE_GP == omap_type()) अणु
		/* RAMFW: R/W access to all initiators क्रम all qualअगरier sets */
		अगर (cpu_is_omap242x()) अणु
			ग_लिखोl_relaxed(0xFF, OMAP24XX_VA_REQINFOPERM0); /* all q-vects */
			ग_लिखोl_relaxed(0xCFDE, OMAP24XX_VA_READPERM0);  /* all i-पढ़ो */
			ग_लिखोl_relaxed(0xCFDE, OMAP24XX_VA_WRITEPERM0); /* all i-ग_लिखो */
		पूर्ण
		अगर (cpu_is_omap34xx()) अणु
			ग_लिखोl_relaxed(0xFFFF, OMAP34XX_VA_REQINFOPERM0); /* all q-vects */
			ग_लिखोl_relaxed(0xFFFF, OMAP34XX_VA_READPERM0);  /* all i-पढ़ो */
			ग_लिखोl_relaxed(0xFFFF, OMAP34XX_VA_WRITEPERM0); /* all i-ग_लिखो */
			ग_लिखोl_relaxed(0x0, OMAP34XX_VA_ADDR_MATCH2);
			ग_लिखोl_relaxed(0xFFFFFFFF, OMAP34XX_VA_SMS_RG_ATT0);
		पूर्ण
		वापस 0;
	पूर्ण अन्यथा
		वापस 1; /* assume locked with no PPA or security driver */
पूर्ण

/*
 * The amount of SRAM depends on the core type.
 * Note that we cannot try to test क्रम SRAM here because ग_लिखोs
 * to secure SRAM will hang the प्रणाली. Also the SRAM is not
 * yet mapped at this poपूर्णांक.
 */
अटल व्योम __init omap_detect_sram(व्योम)
अणु
	omap_sram_skip = SRAM_BOOTLOADER_SZ;
	अगर (is_sram_locked()) अणु
		अगर (cpu_is_omap34xx()) अणु
			omap_sram_start = OMAP3_SRAM_PUB_PA;
			अगर ((omap_type() == OMAP2_DEVICE_TYPE_EMU) ||
			    (omap_type() == OMAP2_DEVICE_TYPE_SEC)) अणु
				omap_sram_size = 0x7000; /* 28K */
				omap_sram_skip += SZ_16K;
			पूर्ण अन्यथा अणु
				omap_sram_size = 0x8000; /* 32K */
			पूर्ण
		पूर्ण अन्यथा अणु
			omap_sram_start = OMAP2_SRAM_PUB_PA;
			omap_sram_size = 0x800; /* 2K */
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (cpu_is_omap34xx()) अणु
			omap_sram_start = OMAP3_SRAM_PA;
			omap_sram_size = 0x10000; /* 64K */
		पूर्ण अन्यथा अणु
			omap_sram_start = OMAP2_SRAM_PA;
			अगर (cpu_is_omap242x())
				omap_sram_size = 0xa0000; /* 640K */
			अन्यथा अगर (cpu_is_omap243x())
				omap_sram_size = 0x10000; /* 64K */
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Note that we cannot use ioremap क्रम SRAM, as घड़ी init needs SRAM early.
 */
अटल व्योम __init omap2_map_sram(व्योम)
अणु
	पूर्णांक cached = 1;

	अगर (cpu_is_omap34xx()) अणु
		/*
		 * SRAM must be marked as non-cached on OMAP3 since the
		 * CORE DPLL M2 भागider change code (in SRAM) runs with the
		 * SDRAM controller disabled, and अगर it is marked cached,
		 * the ARM may attempt to ग_लिखो cache lines back to SDRAM
		 * which will cause the प्रणाली to hang.
		 */
		cached = 0;
	पूर्ण

	omap_map_sram(omap_sram_start, omap_sram_size,
			omap_sram_skip, cached);
पूर्ण

अटल व्योम (*_omap2_sram_ddr_init)(u32 *slow_dll_ctrl, u32 fast_dll_ctrl,
			      u32 base_cs, u32 क्रमce_unlock);

व्योम omap2_sram_ddr_init(u32 *slow_dll_ctrl, u32 fast_dll_ctrl,
		   u32 base_cs, u32 क्रमce_unlock)
अणु
	BUG_ON(!_omap2_sram_ddr_init);
	_omap2_sram_ddr_init(slow_dll_ctrl, fast_dll_ctrl,
			     base_cs, क्रमce_unlock);
पूर्ण

अटल व्योम (*_omap2_sram_reprogram_sdrc)(u32 perf_level, u32 dll_val,
					  u32 mem_type);

व्योम omap2_sram_reprogram_sdrc(u32 perf_level, u32 dll_val, u32 mem_type)
अणु
	BUG_ON(!_omap2_sram_reprogram_sdrc);
	_omap2_sram_reprogram_sdrc(perf_level, dll_val, mem_type);
पूर्ण

अटल u32 (*_omap2_set_prcm)(u32 dpll_ctrl_val, u32 sdrc_rfr_val, पूर्णांक bypass);

u32 omap2_set_prcm(u32 dpll_ctrl_val, u32 sdrc_rfr_val, पूर्णांक bypass)
अणु
	BUG_ON(!_omap2_set_prcm);
	वापस _omap2_set_prcm(dpll_ctrl_val, sdrc_rfr_val, bypass);
पूर्ण

#अगर_घोषित CONFIG_SOC_OMAP2420
अटल पूर्णांक __init omap242x_sram_init(व्योम)
अणु
	_omap2_sram_ddr_init = omap_sram_push(omap242x_sram_ddr_init,
					omap242x_sram_ddr_init_sz);

	_omap2_sram_reprogram_sdrc = omap_sram_push(omap242x_sram_reprogram_sdrc,
					    omap242x_sram_reprogram_sdrc_sz);

	_omap2_set_prcm = omap_sram_push(omap242x_sram_set_prcm,
					 omap242x_sram_set_prcm_sz);

	वापस 0;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक omap242x_sram_init(व्योम)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SOC_OMAP2430
अटल पूर्णांक __init omap243x_sram_init(व्योम)
अणु
	_omap2_sram_ddr_init = omap_sram_push(omap243x_sram_ddr_init,
					omap243x_sram_ddr_init_sz);

	_omap2_sram_reprogram_sdrc = omap_sram_push(omap243x_sram_reprogram_sdrc,
					    omap243x_sram_reprogram_sdrc_sz);

	_omap2_set_prcm = omap_sram_push(omap243x_sram_set_prcm,
					 omap243x_sram_set_prcm_sz);

	वापस 0;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक omap243x_sram_init(व्योम)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_OMAP3

व्योम omap3_sram_restore_context(व्योम)
अणु
	omap_sram_reset();

	omap_push_sram_idle();
पूर्ण

अटल अंतरभूत पूर्णांक omap34xx_sram_init(व्योम)
अणु
	omap3_sram_restore_context();
	वापस 0;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक omap34xx_sram_init(व्योम)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_ARCH_OMAP3 */

पूर्णांक __init omap_sram_init(व्योम)
अणु
	omap_detect_sram();
	omap2_map_sram();

	अगर (cpu_is_omap242x())
		omap242x_sram_init();
	अन्यथा अगर (cpu_is_omap2430())
		omap243x_sram_init();
	अन्यथा अगर (cpu_is_omap34xx())
		omap34xx_sram_init();

	वापस 0;
पूर्ण
