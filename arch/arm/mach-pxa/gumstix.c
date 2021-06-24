<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/mach-pxa/gumstix.c
 *
 *  Support क्रम the Gumstix motherboards.
 *
 *  Original Author:	Craig Hughes
 *  Created:	Feb 14, 2008
 *  Copyright:	Craig Hughes
 *
 *  Implemented based on lubbock.c by Nicolas Pitre and code from Craig
 *  Hughes
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/err.h>
#समावेश <linux/clk.h>

#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/memory.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <mach/hardware.h>
#समावेश <यंत्र/irq.h>
#समावेश <linux/sizes.h>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/irq.h>
#समावेश <यंत्र/mach/flash.h>

#समावेश "pxa25x.h"
#समावेश <linux/platक्रमm_data/mmc-pxamci.h>
#समावेश "udc.h"
#समावेश "gumstix.h"

#समावेश "generic.h"

अटल काष्ठा resource flash_resource = अणु
	.start	= 0x00000000,
	.end	= SZ_64M - 1,
	.flags	= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा mtd_partition gumstix_partitions[] = अणु
	अणु
		.name =		"Bootloader",
		.size =		0x00040000,
		.offset =	0,
		.mask_flags =	MTD_WRITEABLE  /* क्रमce पढ़ो-only */
	पूर्ण , अणु
		.name =		"rootfs",
		.size =		MTDPART_SIZ_FULL,
		.offset =	MTDPART_OFS_APPEND
	पूर्ण
पूर्ण;

अटल काष्ठा flash_platक्रमm_data gumstix_flash_data = अणु
	.map_name	= "cfi_probe",
	.parts		= gumstix_partitions,
	.nr_parts	= ARRAY_SIZE(gumstix_partitions),
	.width		= 2,
पूर्ण;

अटल काष्ठा platक्रमm_device gumstix_flash_device = अणु
	.name		= "pxa2xx-flash",
	.id		= 0,
	.dev = अणु
		.platक्रमm_data = &gumstix_flash_data,
	पूर्ण,
	.resource = &flash_resource,
	.num_resources = 1,
पूर्ण;

अटल काष्ठा platक्रमm_device *devices[] __initdata = अणु
	&gumstix_flash_device,
पूर्ण;

#अगर_घोषित CONFIG_MMC_PXA
अटल काष्ठा pxamci_platक्रमm_data gumstix_mci_platक्रमm_data = अणु
	.ocr_mask		= MMC_VDD_32_33|MMC_VDD_33_34,
पूर्ण;

अटल व्योम __init gumstix_mmc_init(व्योम)
अणु
	pxa_set_mci_info(&gumstix_mci_platक्रमm_data);
पूर्ण
#अन्यथा
अटल व्योम __init gumstix_mmc_init(व्योम)
अणु
	pr_debug("Gumstix mmc disabled\n");
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_USB_PXA25X
अटल काष्ठा gpiod_lookup_table gumstix_gpio_vbus_gpiod_table = अणु
	.dev_id = "gpio-vbus",
	.table = अणु
		GPIO_LOOKUP("gpio-pxa", GPIO_GUMSTIX_USB_GPIOn,
			    "vbus", GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("gpio-pxa", GPIO_GUMSTIX_USB_GPIOx,
			    "pullup", GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device gumstix_gpio_vbus = अणु
	.name	= "gpio-vbus",
	.id	= -1,
पूर्ण;

अटल व्योम __init gumstix_udc_init(व्योम)
अणु
	gpiod_add_lookup_table(&gumstix_gpio_vbus_gpiod_table);
	platक्रमm_device_रेजिस्टर(&gumstix_gpio_vbus);
पूर्ण
#अन्यथा
अटल व्योम gumstix_udc_init(व्योम)
अणु
	pr_debug("Gumstix udc is disabled\n");
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_BT
/* Normally, the bootloader would have enabled this 32kHz घड़ी but many
** boards still have u-boot 1.1.4 so we check अगर it has been turned on and
** अगर not, we turn it on with a warning message. */
अटल व्योम gumstix_setup_bt_घड़ी(व्योम)
अणु
	पूर्णांक समयout = 500;

	अगर (!(पढ़ोl(OSCC) & OSCC_OOK))
		pr_warn("32kHz clock was not on. Bootloader may need to be updated\n");
	अन्यथा
		वापस;

	ग_लिखोl(पढ़ोl(OSCC) | OSCC_OON, OSCC);
	करो अणु
		अगर (पढ़ोl(OSCC) & OSCC_OOK)
			अवरोध;
		udelay(1);
	पूर्ण जबतक (--समयout);
	अगर (!समयout)
		pr_err("Failed to start 32kHz clock\n");
पूर्ण

अटल व्योम __init gumstix_bluetooth_init(व्योम)
अणु
	पूर्णांक err;

	gumstix_setup_bt_घड़ी();

	err = gpio_request(GPIO_GUMSTIX_BTRESET, "BTRST");
	अगर (err) अणु
		pr_err("gumstix: failed request gpio for bluetooth reset\n");
		वापस;
	पूर्ण

	err = gpio_direction_output(GPIO_GUMSTIX_BTRESET, 1);
	अगर (err) अणु
		pr_err("gumstix: can't reset bluetooth\n");
		वापस;
	पूर्ण
	gpio_set_value(GPIO_GUMSTIX_BTRESET, 0);
	udelay(100);
	gpio_set_value(GPIO_GUMSTIX_BTRESET, 1);
पूर्ण
#अन्यथा
अटल व्योम gumstix_bluetooth_init(व्योम)
अणु
	pr_debug("Gumstix Bluetooth is disabled\n");
पूर्ण
#पूर्ण_अगर

अटल अचिन्हित दीर्घ gumstix_pin_config[] __initdata = अणु
	GPIO12_32KHz,
	/* BTUART */
	GPIO42_HWUART_RXD,
	GPIO43_HWUART_TXD,
	GPIO44_HWUART_CTS,
	GPIO45_HWUART_RTS,
	/* MMC */
	GPIO6_MMC_CLK,
	GPIO53_MMC_CLK,
	GPIO8_MMC_CS0,
पूर्ण;

पूर्णांक __attribute__((weak)) am200_init(व्योम)
अणु
	वापस 0;
पूर्ण

पूर्णांक __attribute__((weak)) am300_init(व्योम)
अणु
	वापस 0;
पूर्ण

अटल व्योम __init carrier_board_init(व्योम)
अणु
	/*
	 * put carrier/expansion board init here अगर
	 * they cannot be detected programatically
	 */
	am200_init();
	am300_init();
पूर्ण

अटल व्योम __init gumstix_init(व्योम)
अणु
	pxa2xx_mfp_config(ARRAY_AND_SIZE(gumstix_pin_config));

	pxa_set_ffuart_info(शून्य);
	pxa_set_btuart_info(शून्य);
	pxa_set_stuart_info(शून्य);
	pxa_set_hwuart_info(शून्य);

	gumstix_bluetooth_init();
	gumstix_udc_init();
	gumstix_mmc_init();
	(व्योम) platक्रमm_add_devices(devices, ARRAY_SIZE(devices));
	carrier_board_init();
पूर्ण

MACHINE_START(GUMSTIX, "Gumstix")
	.atag_offset	= 0x100, /* match u-boot bi_boot_params */
	.map_io		= pxa25x_map_io,
	.nr_irqs	= PXA_NR_IRQS,
	.init_irq	= pxa25x_init_irq,
	.handle_irq	= pxa25x_handle_irq,
	.init_समय	= pxa_समयr_init,
	.init_machine	= gumstix_init,
	.restart	= pxa_restart,
MACHINE_END
