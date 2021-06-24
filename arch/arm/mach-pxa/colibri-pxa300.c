<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  arch/arm/mach-pxa/colibri-pxa300.c
 *
 *  Support क्रम Toradex PXA300/310 based Colibri module
 *
 *  Daniel Mack <daniel@caiaq.de>
 *  Matthias Meier <matthias.j.meier@gmx.net>
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <linux/sizes.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/irq.h>

#समावेश "pxa300.h"
#समावेश "colibri.h"
#समावेश <linux/platक्रमm_data/usb-ohci-pxa27x.h>
#समावेश <linux/platक्रमm_data/video-pxafb.h>
#समावेश <mach/audपन.स>

#समावेश "generic.h"
#समावेश "devices.h"


#अगर_घोषित CONFIG_MACH_COLIBRI_EVALBOARD
अटल mfp_cfg_t colibri_pxa300_evalboard_pin_config[] __initdata = अणु
	/* MMC */
	GPIO7_MMC1_CLK,
	GPIO14_MMC1_CMD,
	GPIO3_MMC1_DAT0,
	GPIO4_MMC1_DAT1,
	GPIO5_MMC1_DAT2,
	GPIO6_MMC1_DAT3,
	GPIO13_GPIO,	/* GPIO13_COLIBRI_PXA300_SD_DETECT */

	/* UHC */
	GPIO0_2_USBH_PEN,
	GPIO1_2_USBH_PWR,
	GPIO77_USB_P3_1,
	GPIO78_USB_P3_2,
	GPIO79_USB_P3_3,
	GPIO80_USB_P3_4,
	GPIO81_USB_P3_5,
	GPIO82_USB_P3_6,

	/* I2C */
	GPIO21_I2C_SCL,
	GPIO22_I2C_SDA,
पूर्ण;
#अन्यथा
अटल mfp_cfg_t colibri_pxa300_evalboard_pin_config[] __initdata = अणुपूर्ण;
#पूर्ण_अगर

#अगर defined(CONFIG_AX88796)
#घोषणा COLIBRI_ETH_IRQ_GPIO	mfp_to_gpio(GPIO26_GPIO)
/*
 * Asix AX88796 Ethernet
 */
अटल काष्ठा ax_plat_data colibri_asix_platdata = अणु
	.flags		= 0, /* defined later */
	.wordlength	= 2,
पूर्ण;

अटल काष्ठा resource colibri_asix_resource[] = अणु
	[0] = अणु
		.start = PXA3xx_CS2_PHYS,
		.end   = PXA3xx_CS2_PHYS + (0x20 * 2) - 1,
		.flags = IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start = PXA_GPIO_TO_IRQ(COLIBRI_ETH_IRQ_GPIO),
		.end   = PXA_GPIO_TO_IRQ(COLIBRI_ETH_IRQ_GPIO),
		.flags = IORESOURCE_IRQ | IRQF_TRIGGER_FALLING,
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device asix_device = अणु
	.name		= "ax88796",
	.id		= 0,
	.num_resources 	= ARRAY_SIZE(colibri_asix_resource),
	.resource	= colibri_asix_resource,
	.dev		= अणु
		.platक्रमm_data = &colibri_asix_platdata
	पूर्ण
पूर्ण;

अटल mfp_cfg_t colibri_pxa300_eth_pin_config[] __initdata = अणु
	GPIO1_nCS2,			/* AX88796 chip select */
	GPIO26_GPIO | MFP_PULL_HIGH	/* AX88796 IRQ */
पूर्ण;

अटल व्योम __init colibri_pxa300_init_eth(व्योम)
अणु
	colibri_pxa3xx_init_eth(&colibri_asix_platdata);
	pxa3xx_mfp_config(ARRAY_AND_SIZE(colibri_pxa300_eth_pin_config));
	platक्रमm_device_रेजिस्टर(&asix_device);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम __init colibri_pxa300_init_eth(व्योम) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_AX88796 */

#अगर defined(CONFIG_FB_PXA) || defined(CONFIG_FB_PXA_MODULE)
अटल mfp_cfg_t colibri_pxa300_lcd_pin_config[] __initdata = अणु
	GPIO54_LCD_LDD_0,
	GPIO55_LCD_LDD_1,
	GPIO56_LCD_LDD_2,
	GPIO57_LCD_LDD_3,
	GPIO58_LCD_LDD_4,
	GPIO59_LCD_LDD_5,
	GPIO60_LCD_LDD_6,
	GPIO61_LCD_LDD_7,
	GPIO62_LCD_LDD_8,
	GPIO63_LCD_LDD_9,
	GPIO64_LCD_LDD_10,
	GPIO65_LCD_LDD_11,
	GPIO66_LCD_LDD_12,
	GPIO67_LCD_LDD_13,
	GPIO68_LCD_LDD_14,
	GPIO69_LCD_LDD_15,
	GPIO70_LCD_LDD_16,
	GPIO71_LCD_LDD_17,
	GPIO62_LCD_CS_N,
	GPIO72_LCD_FCLK,
	GPIO73_LCD_LCLK,
	GPIO74_LCD_PCLK,
	GPIO75_LCD_BIAS,
	GPIO76_LCD_VSYNC,
पूर्ण;

अटल व्योम __init colibri_pxa300_init_lcd(व्योम)
अणु
	pxa3xx_mfp_config(ARRAY_AND_SIZE(colibri_pxa300_lcd_pin_config));
पूर्ण

#अन्यथा
अटल अंतरभूत व्योम colibri_pxa300_init_lcd(व्योम) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_FB_PXA || CONFIG_FB_PXA_MODULE */

#अगर defined(CONFIG_SND_AC97_CODEC) || defined(CONFIG_SND_AC97_CODEC_MODULE)
अटल mfp_cfg_t colibri_pxa310_ac97_pin_config[] __initdata = अणु
	GPIO24_AC97_SYSCLK,
	GPIO23_AC97_nACRESET,
	GPIO25_AC97_SDATA_IN_0,
	GPIO27_AC97_SDATA_OUT,
	GPIO28_AC97_SYNC,
	GPIO29_AC97_BITCLK
पूर्ण;

अटल अंतरभूत व्योम __init colibri_pxa310_init_ac97(व्योम)
अणु
	/* no AC97 codec on Colibri PXA300 */
	अगर (!cpu_is_pxa310())
		वापस;

	pxa3xx_mfp_config(ARRAY_AND_SIZE(colibri_pxa310_ac97_pin_config));
	pxa_set_ac97_info(शून्य);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम colibri_pxa310_init_ac97(व्योम) अणुपूर्ण
#पूर्ण_अगर

व्योम __init colibri_pxa300_init(व्योम)
अणु
	colibri_pxa300_init_eth();
	colibri_pxa3xx_init_nand();
	colibri_pxa300_init_lcd();
	colibri_pxa3xx_init_lcd(mfp_to_gpio(GPIO39_GPIO));
	colibri_pxa310_init_ac97();

	/* Evalboard init */
	pxa3xx_mfp_config(ARRAY_AND_SIZE(colibri_pxa300_evalboard_pin_config));
	colibri_evalboard_init();
पूर्ण

MACHINE_START(COLIBRI300, "Toradex Colibri PXA300")
	.atag_offset	= 0x100,
	.init_machine	= colibri_pxa300_init,
	.map_io		= pxa3xx_map_io,
	.nr_irqs	= PXA_NR_IRQS,
	.init_irq	= pxa3xx_init_irq,
	.handle_irq	= pxa3xx_handle_irq,
	.init_समय	= pxa_समयr_init,
	.restart	= pxa_restart,
MACHINE_END

