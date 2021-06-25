<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * linux/arch/arm/mach-omap1/devices.c
 *
 * OMAP1 platक्रमm device setup/initialization
 */

#समावेश <linux/dma-mapping.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spi/spi.h>

#समावेश <linux/platक्रमm_data/omap-wd-समयr.h>

#समावेश <यंत्र/mach/map.h>

#समावेश <mach/tc.h>
#समावेश <mach/mux.h>

#समावेश <mach/omap7xx.h>
#समावेश <mach/hardware.h>

#समावेश "common.h"
#समावेश "clock.h"
#समावेश "mmc.h"
#समावेश "sram.h"

#अगर IS_ENABLED(CONFIG_RTC_DRV_OMAP)

#घोषणा	OMAP_RTC_BASE		0xfffb4800

अटल काष्ठा resource rtc_resources[] = अणु
	अणु
		.start		= OMAP_RTC_BASE,
		.end		= OMAP_RTC_BASE + 0x5f,
		.flags		= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start		= INT_RTC_TIMER,
		.flags		= IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.start		= INT_RTC_ALARM,
		.flags		= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device omap_rtc_device = अणु
	.name           = "omap_rtc",
	.id             = -1,
	.num_resources	= ARRAY_SIZE(rtc_resources),
	.resource	= rtc_resources,
पूर्ण;

अटल व्योम omap_init_rtc(व्योम)
अणु
	(व्योम) platक्रमm_device_रेजिस्टर(&omap_rtc_device);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम omap_init_rtc(व्योम) अणुपूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम omap_init_mbox(व्योम) अणु पूर्ण

/*-------------------------------------------------------------------------*/

#अगर IS_ENABLED(CONFIG_MMC_OMAP)

अटल अंतरभूत व्योम omap1_mmc_mux(काष्ठा omap_mmc_platक्रमm_data *mmc_controller,
			पूर्णांक controller_nr)
अणु
	अगर (controller_nr == 0) अणु
		अगर (cpu_is_omap7xx()) अणु
			omap_cfg_reg(MMC_7XX_CMD);
			omap_cfg_reg(MMC_7XX_CLK);
			omap_cfg_reg(MMC_7XX_DAT0);
		पूर्ण अन्यथा अणु
			omap_cfg_reg(MMC_CMD);
			omap_cfg_reg(MMC_CLK);
			omap_cfg_reg(MMC_DAT0);
		पूर्ण

		अगर (cpu_is_omap1710()) अणु
			omap_cfg_reg(M15_1710_MMC_CLKI);
			omap_cfg_reg(P19_1710_MMC_CMDसूची);
			omap_cfg_reg(P20_1710_MMC_DATसूची0);
		पूर्ण
		अगर (mmc_controller->slots[0].wires == 4 && !cpu_is_omap7xx()) अणु
			omap_cfg_reg(MMC_DAT1);
			/* NOTE: DAT2 can be on W10 (here) or M15 */
			अगर (!mmc_controller->slots[0].nomux)
				omap_cfg_reg(MMC_DAT2);
			omap_cfg_reg(MMC_DAT3);
		पूर्ण
	पूर्ण

	/* Block 2 is on newer chips, and has many pinout options */
	अगर (cpu_is_omap16xx() && controller_nr == 1) अणु
		अगर (!mmc_controller->slots[1].nomux) अणु
			omap_cfg_reg(Y8_1610_MMC2_CMD);
			omap_cfg_reg(Y10_1610_MMC2_CLK);
			omap_cfg_reg(R18_1610_MMC2_CLKIN);
			omap_cfg_reg(W8_1610_MMC2_DAT0);
			अगर (mmc_controller->slots[1].wires == 4) अणु
				omap_cfg_reg(V8_1610_MMC2_DAT1);
				omap_cfg_reg(W15_1610_MMC2_DAT2);
				omap_cfg_reg(R10_1610_MMC2_DAT3);
			पूर्ण

			/* These are needed क्रम the level shअगरter */
			omap_cfg_reg(V9_1610_MMC2_CMDसूची);
			omap_cfg_reg(V5_1610_MMC2_DATसूची0);
			omap_cfg_reg(W19_1610_MMC2_DATसूची1);
		पूर्ण

		/* Feedback घड़ी must be set on OMAP-1710 MMC2 */
		अगर (cpu_is_omap1710())
			omap_ग_लिखोl(omap_पढ़ोl(MOD_CONF_CTRL_1) | (1 << 24),
					MOD_CONF_CTRL_1);
	पूर्ण
पूर्ण

#घोषणा OMAP_MMC_NR_RES		4

/*
 * Register MMC devices.
 */
अटल पूर्णांक __init omap_mmc_add(स्थिर अक्षर *name, पूर्णांक id, अचिन्हित दीर्घ base,
				अचिन्हित दीर्घ size, अचिन्हित पूर्णांक irq,
				अचिन्हित rx_req, अचिन्हित tx_req,
				काष्ठा omap_mmc_platक्रमm_data *data)
अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा resource res[OMAP_MMC_NR_RES];
	पूर्णांक ret;

	pdev = platक्रमm_device_alloc(name, id);
	अगर (!pdev)
		वापस -ENOMEM;

	स_रखो(res, 0, OMAP_MMC_NR_RES * माप(काष्ठा resource));
	res[0].start = base;
	res[0].end = base + size - 1;
	res[0].flags = IORESOURCE_MEM;
	res[1].start = res[1].end = irq;
	res[1].flags = IORESOURCE_IRQ;
	res[2].start = rx_req;
	res[2].name = "rx";
	res[2].flags = IORESOURCE_DMA;
	res[3].start = tx_req;
	res[3].name = "tx";
	res[3].flags = IORESOURCE_DMA;

	अगर (cpu_is_omap7xx())
		data->slots[0].features = MMC_OMAP7XX;
	अगर (cpu_is_omap15xx())
		data->slots[0].features = MMC_OMAP15XX;
	अगर (cpu_is_omap16xx())
		data->slots[0].features = MMC_OMAP16XX;

	ret = platक्रमm_device_add_resources(pdev, res, ARRAY_SIZE(res));
	अगर (ret == 0)
		ret = platक्रमm_device_add_data(pdev, data, माप(*data));
	अगर (ret)
		जाओ fail;

	ret = platक्रमm_device_add(pdev);
	अगर (ret)
		जाओ fail;

	/* वापस device handle to board setup code */
	data->dev = &pdev->dev;
	वापस 0;

fail:
	platक्रमm_device_put(pdev);
	वापस ret;
पूर्ण

व्योम __init omap1_init_mmc(काष्ठा omap_mmc_platक्रमm_data **mmc_data,
			पूर्णांक nr_controllers)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nr_controllers; i++) अणु
		अचिन्हित दीर्घ base, size;
		अचिन्हित rx_req, tx_req;
		अचिन्हित पूर्णांक irq = 0;

		अगर (!mmc_data[i])
			जारी;

		omap1_mmc_mux(mmc_data[i], i);

		चयन (i) अणु
		हाल 0:
			base = OMAP1_MMC1_BASE;
			irq = INT_MMC;
			rx_req = 22;
			tx_req = 21;
			अवरोध;
		हाल 1:
			अगर (!cpu_is_omap16xx())
				वापस;
			base = OMAP1_MMC2_BASE;
			irq = INT_1610_MMC2;
			rx_req = 55;
			tx_req = 54;
			अवरोध;
		शेष:
			जारी;
		पूर्ण
		size = OMAP1_MMC_SIZE;

		omap_mmc_add("mmci-omap", i, base, size, irq,
				rx_req, tx_req, mmc_data[i]);
	पूर्ण
पूर्ण

#पूर्ण_अगर

/*-------------------------------------------------------------------------*/

/* OMAP7xx SPI support */
#अगर IS_ENABLED(CONFIG_SPI_OMAP_100K)

काष्ठा platक्रमm_device omap_spi1 = अणु
	.name           = "omap1_spi100k",
	.id             = 1,
पूर्ण;

काष्ठा platक्रमm_device omap_spi2 = अणु
	.name           = "omap1_spi100k",
	.id             = 2,
पूर्ण;

अटल व्योम omap_init_spi100k(व्योम)
अणु
	अगर (!cpu_is_omap7xx())
		वापस;

	omap_spi1.dev.platक्रमm_data = ioremap(OMAP7XX_SPI1_BASE, 0x7ff);
	अगर (omap_spi1.dev.platक्रमm_data)
		platक्रमm_device_रेजिस्टर(&omap_spi1);

	omap_spi2.dev.platक्रमm_data = ioremap(OMAP7XX_SPI2_BASE, 0x7ff);
	अगर (omap_spi2.dev.platक्रमm_data)
		platक्रमm_device_रेजिस्टर(&omap_spi2);
पूर्ण

#अन्यथा
अटल अंतरभूत व्योम omap_init_spi100k(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

/*-------------------------------------------------------------------------*/

अटल अंतरभूत व्योम omap_init_sti(व्योम) अणुपूर्ण

/* Numbering क्रम the SPI-capable controllers when used क्रम SPI:
 * spi		= 1
 * uwire	= 2
 * mmc1..2	= 3..4
 * mcbsp1..3	= 5..7
 */

#अगर IS_ENABLED(CONFIG_SPI_OMAP_UWIRE)

#घोषणा	OMAP_UWIRE_BASE		0xfffb3000

अटल काष्ठा resource uwire_resources[] = अणु
	अणु
		.start		= OMAP_UWIRE_BASE,
		.end		= OMAP_UWIRE_BASE + 0x20,
		.flags		= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device omap_uwire_device = अणु
	.name	   = "omap_uwire",
	.id	     = -1,
	.num_resources	= ARRAY_SIZE(uwire_resources),
	.resource	= uwire_resources,
पूर्ण;

अटल व्योम omap_init_uwire(व्योम)
अणु
	/* FIXME define and use a boot tag; not all boards will be hooking
	 * up devices to the microwire controller, and multi-board configs
	 * mean that CONFIG_SPI_OMAP_UWIRE may be configured anyway...
	 */

	/* board-specअगरic code must configure chipselects (only a few
	 * are normally used) and SCLK/SDI/SDO (each has two choices).
	 */
	(व्योम) platक्रमm_device_रेजिस्टर(&omap_uwire_device);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम omap_init_uwire(व्योम) अणुपूर्ण
#पूर्ण_अगर


#घोषणा OMAP1_RNG_BASE		0xfffe5000

अटल काष्ठा resource omap1_rng_resources[] = अणु
	अणु
		.start		= OMAP1_RNG_BASE,
		.end		= OMAP1_RNG_BASE + 0x4f,
		.flags		= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device omap1_rng_device = अणु
	.name		= "omap_rng",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(omap1_rng_resources),
	.resource	= omap1_rng_resources,
पूर्ण;

अटल व्योम omap1_init_rng(व्योम)
अणु
	अगर (!cpu_is_omap16xx())
		वापस;

	(व्योम) platक्रमm_device_रेजिस्टर(&omap1_rng_device);
पूर्ण

/*-------------------------------------------------------------------------*/

/*
 * This माला_लो called after board-specअगरic INIT_MACHINE, and initializes most
 * on-chip peripherals accessible on this board (except क्रम few like USB):
 *
 *  (a) Does any "standard config" pin muxing needed.  Board-specअगरic
 *	code will have muxed GPIO pins and करोne "nonstandard" setup;
 *	that code could live in the boot loader.
 *  (b) Populating board-specअगरic platक्रमm_data with the data drivers
 *	rely on to handle wiring variations.
 *  (c) Creating platक्रमm devices as meaningful on this board and
 *	with this kernel configuration.
 *
 * Claiming GPIOs, and setting their direction and initial values, is the
 * responsibility of the device drivers.  So is responding to probe().
 *
 * Board-specअगरic knowledge like creating devices or pin setup is to be
 * kept out of drivers as much as possible.  In particular, pin setup
 * may be handled by the boot loader, and drivers should expect it will
 * normally have been करोne by the समय they're probed.
 */
अटल पूर्णांक __init omap1_init_devices(व्योम)
अणु
	अगर (!cpu_class_is_omap1())
		वापस -ENODEV;

	omap_sram_init();
	omap1_clk_late_init();

	/* please keep these calls, and their implementations above,
	 * in alphabetical order so they're easier to sort through.
	 */

	omap_init_mbox();
	omap_init_rtc();
	omap_init_spi100k();
	omap_init_sti();
	omap_init_uwire();
	omap1_init_rng();

	वापस 0;
पूर्ण
arch_initcall(omap1_init_devices);

#अगर IS_ENABLED(CONFIG_OMAP_WATCHDOG)

अटल काष्ठा resource wdt_resources[] = अणु
	अणु
		.start		= 0xfffeb000,
		.end		= 0xfffeb07F,
		.flags		= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device omap_wdt_device = अणु
	.name		= "omap_wdt",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(wdt_resources),
	.resource	= wdt_resources,
पूर्ण;

अटल पूर्णांक __init omap_init_wdt(व्योम)
अणु
	काष्ठा omap_wd_समयr_platक्रमm_data pdata;
	पूर्णांक ret;

	अगर (!cpu_is_omap16xx())
		वापस -ENODEV;

	pdata.पढ़ो_reset_sources = omap1_get_reset_sources;

	ret = platक्रमm_device_रेजिस्टर(&omap_wdt_device);
	अगर (!ret) अणु
		ret = platक्रमm_device_add_data(&omap_wdt_device, &pdata,
					       माप(pdata));
		अगर (ret)
			platक्रमm_device_del(&omap_wdt_device);
	पूर्ण

	वापस ret;
पूर्ण
subsys_initcall(omap_init_wdt);
#पूर्ण_अगर
