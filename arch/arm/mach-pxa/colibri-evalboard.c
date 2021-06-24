<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/mach-pxa/colibri-evalboard.c
 *
 *  Support क्रम Toradex Colibri Evaluation Carrier Board
 *  Daniel Mack <daniel@caiaq.de>
 *  Marek Vasut <marek.vasut@gmail.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/gpio/machine.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <mach/hardware.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <linux/i2c.h>
#समावेश <linux/platक्रमm_data/i2c-pxa.h>
#समावेश <यंत्र/पन.स>

#समावेश "pxa27x.h"
#समावेश "colibri.h"
#समावेश <linux/platक्रमm_data/mmc-pxamci.h>
#समावेश <linux/platक्रमm_data/usb-ohci-pxa27x.h>
#समावेश "pxa27x-udc.h"

#समावेश "generic.h"
#समावेश "devices.h"

/******************************************************************************
 * SD/MMC card controller
 ******************************************************************************/
#अगर defined(CONFIG_MMC_PXA) || defined(CONFIG_MMC_PXA_MODULE)
अटल काष्ठा pxamci_platक्रमm_data colibri_mci_platक्रमm_data = अणु
	.ocr_mask		= MMC_VDD_32_33 | MMC_VDD_33_34,
	.detect_delay_ms	= 200,
पूर्ण;

अटल काष्ठा gpiod_lookup_table colibri_pxa270_mci_gpio_table = अणु
	.dev_id = "pxa2xx-mci.0",
	.table = अणु
		GPIO_LOOKUP("gpio-pxa", GPIO0_COLIBRI_PXA270_SD_DETECT,
			    "cd", GPIO_ACTIVE_LOW),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpiod_lookup_table colibri_pxa300_mci_gpio_table = अणु
	.dev_id = "pxa2xx-mci.0",
	.table = अणु
		GPIO_LOOKUP("gpio-pxa", GPIO13_COLIBRI_PXA300_SD_DETECT,
			    "cd", GPIO_ACTIVE_LOW),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpiod_lookup_table colibri_pxa320_mci_gpio_table = अणु
	.dev_id = "pxa2xx-mci.0",
	.table = अणु
		GPIO_LOOKUP("gpio-pxa", GPIO28_COLIBRI_PXA320_SD_DETECT,
			    "cd", GPIO_ACTIVE_LOW),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल व्योम __init colibri_mmc_init(व्योम)
अणु
	अगर (machine_is_colibri())	/* PXA270 Colibri */
		gpiod_add_lookup_table(&colibri_pxa270_mci_gpio_table);
	अगर (machine_is_colibri300())	/* PXA300 Colibri */
		gpiod_add_lookup_table(&colibri_pxa300_mci_gpio_table);
	अन्यथा				/* PXA320 Colibri */
		gpiod_add_lookup_table(&colibri_pxa320_mci_gpio_table);

	pxa_set_mci_info(&colibri_mci_platक्रमm_data);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम colibri_mmc_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * USB Host
 ******************************************************************************/
#अगर defined(CONFIG_USB_OHCI_HCD) || defined(CONFIG_USB_OHCI_HCD_MODULE)
अटल पूर्णांक colibri_ohci_init(काष्ठा device *dev)
अणु
	UP2OCR = UP2OCR_HXS | UP2OCR_HXOE | UP2OCR_DPPDE | UP2OCR_DMPDE;
	वापस 0;
पूर्ण

अटल काष्ठा pxaohci_platक्रमm_data colibri_ohci_info = अणु
	.port_mode	= PMM_PERPORT_MODE,
	.flags		= ENABLE_PORT1 |
			  POWER_CONTROL_LOW | POWER_SENSE_LOW,
	.init		= colibri_ohci_init,
पूर्ण;

अटल व्योम __init colibri_uhc_init(व्योम)
अणु
	/* Colibri PXA270 has two usb ports, TBA क्रम 320 */
	अगर (machine_is_colibri())
		colibri_ohci_info.flags	|= ENABLE_PORT2;

	pxa_set_ohci_info(&colibri_ohci_info);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम colibri_uhc_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * I2C RTC
 ******************************************************************************/
#अगर defined(CONFIG_RTC_DRV_DS1307) || defined(CONFIG_RTC_DRV_DS1307_MODULE)
अटल काष्ठा i2c_board_info __initdata colibri_i2c_devs[] = अणु
	अणु
		I2C_BOARD_INFO("m41t00", 0x68),
	पूर्ण,
पूर्ण;

अटल व्योम __init colibri_rtc_init(व्योम)
अणु
	pxa_set_i2c_info(शून्य);
	i2c_रेजिस्टर_board_info(0, ARRAY_AND_SIZE(colibri_i2c_devs));
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम colibri_rtc_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

व्योम __init colibri_evalboard_init(व्योम)
अणु
	pxa_set_ffuart_info(शून्य);
	pxa_set_btuart_info(शून्य);
	pxa_set_stuart_info(शून्य);

	colibri_mmc_init();
	colibri_uhc_init();
	colibri_rtc_init();
पूर्ण
