<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/mach-pxa/colibri-pxa270.c
 *
 *  Support क्रम Toradex PXA270 based Colibri module
 *  Daniel Mack <daniel@caiaq.de>
 *  Marek Vasut <marek.vasut@gmail.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/ucb1400.h>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/flash.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <linux/sizes.h>

#समावेश <mach/audपन.स>
#समावेश "colibri.h"
#समावेश "pxa27x.h"

#समावेश "devices.h"
#समावेश "generic.h"

/******************************************************************************
 * Evaluation board MFP
 ******************************************************************************/
#अगर_घोषित	 CONFIG_MACH_COLIBRI_EVALBOARD
अटल mfp_cfg_t colibri_pxa270_evalboard_pin_config[] __initdata = अणु
	/* MMC */
	GPIO32_MMC_CLK,
	GPIO92_MMC_DAT_0,
	GPIO109_MMC_DAT_1,
	GPIO110_MMC_DAT_2,
	GPIO111_MMC_DAT_3,
	GPIO112_MMC_CMD,
	GPIO0_GPIO,	/* SD detect */

	/* FFUART */
	GPIO39_FFUART_TXD,
	GPIO34_FFUART_RXD,

	/* UHC */
	GPIO88_USBH1_PWR,
	GPIO89_USBH1_PEN,
	GPIO119_USBH2_PWR,
	GPIO120_USBH2_PEN,

	/* PCMCIA */
	GPIO85_nPCE_1,
	GPIO54_nPCE_2,
	GPIO55_nPREG,
	GPIO50_nPIOR,
	GPIO51_nPIOW,
	GPIO49_nPWE,
	GPIO48_nPOE,
	GPIO57_nIOIS16,
	GPIO56_nPWAIT,
	GPIO104_PSKTSEL,
	GPIO53_GPIO,	/* RESET */
	GPIO83_GPIO,	/* BVD1 */
	GPIO82_GPIO,	/* BVD2 */
	GPIO1_GPIO,	/* READY */
	GPIO84_GPIO,	/* DETECT */
	GPIO107_GPIO,	/* PPEN */

	/* I2C */
	GPIO117_I2C_SCL,
	GPIO118_I2C_SDA,
पूर्ण;
#अन्यथा
अटल mfp_cfg_t colibri_pxa270_evalboard_pin_config[] __initdata = अणुपूर्ण;
#पूर्ण_अगर

#अगर_घोषित	CONFIG_MACH_COLIBRI_PXA270_INCOME
अटल mfp_cfg_t income_pin_config[] __initdata = अणु
	/* MMC */
	GPIO32_MMC_CLK,
	GPIO92_MMC_DAT_0,
	GPIO109_MMC_DAT_1,
	GPIO110_MMC_DAT_2,
	GPIO111_MMC_DAT_3,
	GPIO112_MMC_CMD,
	GPIO0_GPIO,	/* SD detect */
	GPIO1_GPIO,	/* SD पढ़ो-only */

	/* FFUART */
	GPIO39_FFUART_TXD,
	GPIO34_FFUART_RXD,

	/* BFUART */
	GPIO42_BTUART_RXD,
	GPIO43_BTUART_TXD,
	GPIO45_BTUART_RTS,

	/* STUART */
	GPIO46_STUART_RXD,
	GPIO47_STUART_TXD,

	/* UHC */
	GPIO88_USBH1_PWR,
	GPIO89_USBH1_PEN,

	/* LCD */
	GPIOxx_LCD_TFT_16BPP,

	/* PWM */
	GPIO16_PWM0_OUT,

	/* I2C */
	GPIO117_I2C_SCL,
	GPIO118_I2C_SDA,

	/* LED */
	GPIO54_GPIO,	/* LED A */
	GPIO55_GPIO,	/* LED B */
पूर्ण;
#अन्यथा
अटल mfp_cfg_t income_pin_config[] __initdata = अणुपूर्ण;
#पूर्ण_अगर

/******************************************************************************
 * Pin configuration
 ******************************************************************************/
अटल mfp_cfg_t colibri_pxa270_pin_config[] __initdata = अणु
	/* Ethernet */
	GPIO78_nCS_2,	/* Ethernet CS */
	GPIO114_GPIO,	/* Ethernet IRQ */

	/* AC97 */
	GPIO28_AC97_BITCLK,
	GPIO29_AC97_SDATA_IN_0,
	GPIO30_AC97_SDATA_OUT,
	GPIO31_AC97_SYNC,
	GPIO95_AC97_nRESET,
	GPIO98_AC97_SYSCLK,
	GPIO113_GPIO,	/* Touchscreen IRQ */
पूर्ण;

/******************************************************************************
 * NOR Flash
 ******************************************************************************/
#अगर defined(CONFIG_MTD_PHYSMAP) || defined(CONFIG_MTD_PHYSMAP_MODULE)
अटल काष्ठा mtd_partition colibri_partitions[] = अणु
	अणु
		.name =		"Bootloader",
		.offset =	0x00000000,
		.size =		0x00040000,
		.mask_flags =	MTD_WRITEABLE	/* क्रमce पढ़ो-only */
	पूर्ण, अणु
		.name =		"Kernel",
		.offset =	0x00040000,
		.size =		0x00400000,
		.mask_flags =	0
	पूर्ण, अणु
		.name =		"Rootfs",
		.offset =	0x00440000,
		.size =		MTDPART_SIZ_FULL,
		.mask_flags =	0
	पूर्ण
पूर्ण;

अटल काष्ठा physmap_flash_data colibri_flash_data[] = अणु
	अणु
		.width		= 4,			/* bankwidth in bytes */
		.parts		= colibri_partitions,
		.nr_parts	= ARRAY_SIZE(colibri_partitions)
	पूर्ण
पूर्ण;

अटल काष्ठा resource colibri_pxa270_flash_resource = अणु
	.start	= PXA_CS0_PHYS,
	.end	= PXA_CS0_PHYS + SZ_32M - 1,
	.flags	= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा platक्रमm_device colibri_pxa270_flash_device = अणु
	.name	= "physmap-flash",
	.id	= 0,
	.dev 	= अणु
		.platक्रमm_data = colibri_flash_data,
	पूर्ण,
	.resource = &colibri_pxa270_flash_resource,
	.num_resources = 1,
पूर्ण;

अटल व्योम __init colibri_pxa270_nor_init(व्योम)
अणु
	platक्रमm_device_रेजिस्टर(&colibri_pxa270_flash_device);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम colibri_pxa270_nor_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * Ethernet
 ******************************************************************************/
#अगर defined(CONFIG_DM9000) || defined(CONFIG_DM9000_MODULE)
अटल काष्ठा resource colibri_pxa270_dm9000_resources[] = अणु
	अणु
		.start	= PXA_CS2_PHYS,
		.end	= PXA_CS2_PHYS + 3,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= PXA_CS2_PHYS + 4,
		.end	= PXA_CS2_PHYS + 4 + 500,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= PXA_GPIO_TO_IRQ(GPIO114_COLIBRI_PXA270_ETH_IRQ),
		.end	= PXA_GPIO_TO_IRQ(GPIO114_COLIBRI_PXA270_ETH_IRQ),
		.flags	= IORESOURCE_IRQ | IRQF_TRIGGER_RISING,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device colibri_pxa270_dm9000_device = अणु
	.name		= "dm9000",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(colibri_pxa270_dm9000_resources),
	.resource	= colibri_pxa270_dm9000_resources,
पूर्ण;

अटल व्योम __init colibri_pxa270_eth_init(व्योम)
अणु
	platक्रमm_device_रेजिस्टर(&colibri_pxa270_dm9000_device);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम colibri_pxa270_eth_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * Audio and Touchscreen
 ******************************************************************************/
#अगर	defined(CONFIG_TOUCHSCREEN_UCB1400) || \
	defined(CONFIG_TOUCHSCREEN_UCB1400_MODULE)
अटल pxa2xx_audio_ops_t colibri_pxa270_ac97_pdata = अणु
	.reset_gpio	= 95,
पूर्ण;

अटल काष्ठा ucb1400_pdata colibri_pxa270_ucb1400_pdata = अणु
	.irq		= PXA_GPIO_TO_IRQ(GPIO113_COLIBRI_PXA270_TS_IRQ),
पूर्ण;

अटल काष्ठा platक्रमm_device colibri_pxa270_ucb1400_device = अणु
	.name		= "ucb1400_core",
	.id		= -1,
	.dev		= अणु
		.platक्रमm_data = &colibri_pxa270_ucb1400_pdata,
	पूर्ण,
पूर्ण;

अटल व्योम __init colibri_pxa270_tsc_init(व्योम)
अणु
	pxa_set_ac97_info(&colibri_pxa270_ac97_pdata);
	platक्रमm_device_रेजिस्टर(&colibri_pxa270_ucb1400_device);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम colibri_pxa270_tsc_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

अटल पूर्णांक colibri_pxa270_baseboard;
core_param(colibri_pxa270_baseboard, colibri_pxa270_baseboard, पूर्णांक, 0444);

अटल व्योम __init colibri_pxa270_init(व्योम)
अणु
	pxa2xx_mfp_config(ARRAY_AND_SIZE(colibri_pxa270_pin_config));

	colibri_pxa270_nor_init();
	colibri_pxa270_eth_init();
	colibri_pxa270_tsc_init();

	चयन (colibri_pxa270_baseboard) अणु
	हाल COLIBRI_EVALBOARD:
		pxa2xx_mfp_config(ARRAY_AND_SIZE(
			colibri_pxa270_evalboard_pin_config));
		colibri_evalboard_init();
		अवरोध;
	हाल COLIBRI_PXA270_INCOME:
		pxa2xx_mfp_config(ARRAY_AND_SIZE(income_pin_config));
		colibri_pxa270_income_boardinit();
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "Illegal colibri_pxa270_baseboard type %d\n",
				colibri_pxa270_baseboard);
	पूर्ण

	regulator_has_full_स्थिरraपूर्णांकs();
पूर्ण

/* The "Income s.r.o. SH-Dmaster PXA270 SBC" board can be booted either
 * with the INCOME mach type or with COLIBRI and the kernel parameter
 * "colibri_pxa270_baseboard=1"
 */
अटल व्योम __init colibri_pxa270_income_init(व्योम)
अणु
	colibri_pxa270_baseboard = COLIBRI_PXA270_INCOME;
	colibri_pxa270_init();
पूर्ण

MACHINE_START(COLIBRI, "Toradex Colibri PXA270")
	.atag_offset	= 0x100,
	.init_machine	= colibri_pxa270_init,
	.map_io		= pxa27x_map_io,
	.nr_irqs	= PXA_NR_IRQS,
	.init_irq	= pxa27x_init_irq,
	.handle_irq	= pxa27x_handle_irq,
	.init_समय	= pxa_समयr_init,
	.restart	= pxa_restart,
MACHINE_END

MACHINE_START(INCOME, "Income s.r.o. SH-Dmaster PXA270 SBC")
	.atag_offset	= 0x100,
	.init_machine	= colibri_pxa270_income_init,
	.map_io		= pxa27x_map_io,
	.nr_irqs	= PXA_NR_IRQS,
	.init_irq	= pxa27x_init_irq,
	.handle_irq	= pxa27x_handle_irq,
	.init_समय	= pxa_समयr_init,
	.restart	= pxa_restart,
MACHINE_END

