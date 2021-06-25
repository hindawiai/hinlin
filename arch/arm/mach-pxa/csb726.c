<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Support क्रम Cogent CSB726
 *
 *  Copyright (c) 2008 Dmitry Eremin-Solenikov
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/sm501.h>
#समावेश <linux/smsc911x.h>
#समावेश <linux/platक्रमm_data/i2c-pxa.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश "csb726.h"
#समावेश "pxa27x.h"
#समावेश <linux/platक्रमm_data/mmc-pxamci.h>
#समावेश <linux/platक्रमm_data/usb-ohci-pxa27x.h>
#समावेश <mach/audपन.स>
#समावेश <mach/smemc.h>

#समावेश "generic.h"
#समावेश "devices.h"

/*
 * n/a: 2, 5, 6, 7, 8, 23, 24, 25, 26, 27, 87, 88, 89,
 * nu: 58 -- 77, 90, 91, 93, 102, 105-108, 114-116,
 * XXX: 21,
 * XXX: 79 CS_3 क्रम LAN9215 or PSKTSEL on R2, R3
 * XXX: 33 CS_5 क्रम LAN9215 on R1
 */

अटल अचिन्हित दीर्घ csb726_pin_config[] = अणु
	GPIO78_nCS_2, /* EXP_CS */
	GPIO79_nCS_3, /* SMSC9215 */
	GPIO80_nCS_4, /* SM501 */

	GPIO52_GPIO, /* #SMSC9251 पूर्णांक */
	GPIO53_GPIO, /* SM501 पूर्णांक */

	GPIO1_GPIO, /* GPIO0 */
	GPIO11_GPIO, /* GPIO1 */
	GPIO9_GPIO, /* GPIO2 */
	GPIO10_GPIO, /* GPIO3 */
	GPIO16_PWM0_OUT, /* or GPIO4 */
	GPIO17_PWM1_OUT, /* or GPIO5 */
	GPIO94_GPIO, /* GPIO6 */
	GPIO95_GPIO, /* GPIO7 */
	GPIO96_GPIO, /* GPIO8 */
	GPIO97_GPIO, /* GPIO9 */
	GPIO15_GPIO, /* EXP_IRQ */
	GPIO18_RDY, /* EXP_WAIT */

	GPIO0_GPIO, /* PWR_INT */
	GPIO104_GPIO, /* PWR_OFF */

	GPIO12_GPIO, /* touch irq */

	GPIO13_SSP2_TXD,
	GPIO14_SSP2_SFRM,
	MFP_CFG_OUT(GPIO19, AF1, DRIVE_LOW),/* SSP2_SYSCLK */
	GPIO22_SSP2_SCLK,

	GPIO81_SSP3_TXD,
	GPIO82_SSP3_RXD,
	GPIO83_SSP3_SFRM,
	GPIO84_SSP3_SCLK,

	GPIO20_GPIO, /* SDIO पूर्णांक */
	GPIO32_MMC_CLK,
	GPIO92_MMC_DAT_0,
	GPIO109_MMC_DAT_1,
	GPIO110_MMC_DAT_2,
	GPIO111_MMC_DAT_3,
	GPIO112_MMC_CMD,
	GPIO100_GPIO, /* SD CD */
	GPIO101_GPIO, /* SD WP */

	GPIO28_AC97_BITCLK,
	GPIO29_AC97_SDATA_IN_0,
	GPIO30_AC97_SDATA_OUT,
	GPIO31_AC97_SYNC,
	GPIO113_AC97_nRESET,

	GPIO34_FFUART_RXD,
	GPIO35_FFUART_CTS,
	GPIO36_FFUART_DCD,
	GPIO37_FFUART_DSR,
	GPIO38_FFUART_RI,
	GPIO39_FFUART_TXD,
	GPIO40_FFUART_DTR,
	GPIO41_FFUART_RTS,

	GPIO42_BTUART_RXD,
	GPIO43_BTUART_TXD,
	GPIO44_BTUART_CTS,
	GPIO45_BTUART_RTS,

	GPIO46_STUART_RXD,
	GPIO47_STUART_TXD,

	GPIO48_nPOE,
	GPIO49_nPWE,
	GPIO50_nPIOR,
	GPIO51_nPIOW,
	GPIO54_nPCE_2,
	GPIO55_nPREG,
	GPIO56_nPWAIT,
	GPIO57_nIOIS16, /* maybe unused */
	GPIO85_nPCE_1,
	GPIO98_GPIO, /* CF IRQ */
	GPIO99_GPIO, /* CF CD */
	GPIO103_GPIO, /* Reset */

	GPIO117_I2C_SCL,
	GPIO118_I2C_SDA,
पूर्ण;

अटल काष्ठा pxamci_platक्रमm_data csb726_mci = अणु
	.detect_delay_ms	= 500,
	.ocr_mask		= MMC_VDD_32_33|MMC_VDD_33_34,
	/* FIXME setघातer */
पूर्ण;

अटल काष्ठा gpiod_lookup_table csb726_mci_gpio_table = अणु
	.dev_id = "pxa2xx-mci.0",
	.table = अणु
		/* Card detect on GPIO 100 */
		GPIO_LOOKUP("gpio-pxa", CSB726_GPIO_MMC_DETECT,
			    "cd", GPIO_ACTIVE_LOW),
		/* Write protect on GPIO 101 */
		GPIO_LOOKUP("gpio-pxa", CSB726_GPIO_MMC_RO,
			    "wp", GPIO_ACTIVE_LOW),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा pxaohci_platक्रमm_data csb726_ohci_platक्रमm_data = अणु
	.port_mode	= PMM_NPS_MODE,
	.flags		= ENABLE_PORT1 | NO_OC_PROTECTION,
पूर्ण;

अटल काष्ठा mtd_partition csb726_flash_partitions[] = अणु
	अणु
		.name		= "Bootloader",
		.offset		= 0,
		.size		= CSB726_FLASH_uMON,
		.mask_flags	= MTD_WRITEABLE  /* क्रमce पढ़ो-only */
	पूर्ण,
	अणु
		.name		= "root",
		.offset		= MTDPART_OFS_APPEND,
		.size		= MTDPART_SIZ_FULL,
	पूर्ण
पूर्ण;

अटल काष्ठा physmap_flash_data csb726_flash_data = अणु
	.width		= 2,
	.parts		= csb726_flash_partitions,
	.nr_parts	= ARRAY_SIZE(csb726_flash_partitions),
पूर्ण;

अटल काष्ठा resource csb726_flash_resources[] = अणु
	अणु
		.start          = PXA_CS0_PHYS,
		.end            = PXA_CS0_PHYS + CSB726_FLASH_SIZE - 1 ,
		.flags          = IORESOURCE_MEM,
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device csb726_flash = अणु
	.name           = "physmap-flash",
	.dev            = अणु
		.platक्रमm_data  = &csb726_flash_data,
	पूर्ण,
	.resource       = csb726_flash_resources,
	.num_resources  = ARRAY_SIZE(csb726_flash_resources),
पूर्ण;

अटल काष्ठा resource csb726_sm501_resources[] = अणु
	अणु
		.start          = PXA_CS4_PHYS,
		.end            = PXA_CS4_PHYS + SZ_8M - 1,
		.flags          = IORESOURCE_MEM,
		.name		= "sm501-localmem",
	पूर्ण,
	अणु
		.start          = PXA_CS4_PHYS + SZ_64M - SZ_2M,
		.end            = PXA_CS4_PHYS + SZ_64M - 1,
		.flags          = IORESOURCE_MEM,
		.name		= "sm501-regs",
	पूर्ण,
	अणु
		.start		= CSB726_IRQ_SM501,
		.end		= CSB726_IRQ_SM501,
		.flags		= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा sm501_initdata csb726_sm501_initdata = अणु
/*	.devices	= SM501_USE_USB_HOST, */
	.devices	= SM501_USE_USB_HOST | SM501_USE_UART0 | SM501_USE_UART1,
पूर्ण;

अटल काष्ठा sm501_platdata csb726_sm501_platdata = अणु
	.init		= &csb726_sm501_initdata,
पूर्ण;

अटल काष्ठा platक्रमm_device csb726_sm501 = अणु
	.name		= "sm501",
	.id		= 0,
	.num_resources	= ARRAY_SIZE(csb726_sm501_resources),
	.resource	= csb726_sm501_resources,
	.dev		= अणु
		.platक्रमm_data = &csb726_sm501_platdata,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource csb726_lan_resources[] = अणु
	अणु
		.start	= PXA_CS3_PHYS,
		.end	= PXA_CS3_PHYS + SZ_64K - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= CSB726_IRQ_LAN,
		.end	= CSB726_IRQ_LAN,
		.flags	= IORESOURCE_IRQ | IORESOURCE_IRQ_LOWEDGE,
	पूर्ण,
पूर्ण;

काष्ठा smsc911x_platक्रमm_config csb726_lan_config = अणु
	.irq_polarity	= SMSC911X_IRQ_POLARITY_ACTIVE_LOW,
	.irq_type	= SMSC911X_IRQ_TYPE_PUSH_PULL,
	.flags		= SMSC911X_USE_32BIT,
	.phy_पूर्णांकerface	= PHY_INTERFACE_MODE_MII,
पूर्ण;


अटल काष्ठा platक्रमm_device csb726_lan = अणु
	.name		= "smsc911x",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(csb726_lan_resources),
	.resource	= csb726_lan_resources,
	.dev		= अणु
		.platक्रमm_data	= &csb726_lan_config,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device *devices[] __initdata = अणु
	&csb726_flash,
	&csb726_sm501,
	&csb726_lan,
पूर्ण;

अटल व्योम __init csb726_init(व्योम)
अणु
	pxa2xx_mfp_config(ARRAY_AND_SIZE(csb726_pin_config));
/*	__raw_ग_लिखोl(0x7ffc3ffc, MSC1); *//* LAN9215/EXP_CS */
/*	__raw_ग_लिखोl(0x06697ff4, MSC2); *//* none/SM501 */
	__raw_ग_लिखोl((__raw_पढ़ोl(MSC2) & ~0xffff) | 0x7ff4, MSC2); /* SM501 */

	pxa_set_ffuart_info(शून्य);
	pxa_set_btuart_info(शून्य);
	pxa_set_stuart_info(शून्य);
	pxa_set_i2c_info(शून्य);
	pxa27x_set_i2c_घातer_info(शून्य);
	gpiod_add_lookup_table(&csb726_mci_gpio_table);
	pxa_set_mci_info(&csb726_mci);
	pxa_set_ohci_info(&csb726_ohci_platक्रमm_data);
	pxa_set_ac97_info(शून्य);

	platक्रमm_add_devices(devices, ARRAY_SIZE(devices));
पूर्ण

MACHINE_START(CSB726, "Cogent CSB726")
	.atag_offset	= 0x100,
	.map_io         = pxa27x_map_io,
	.nr_irqs	= PXA_NR_IRQS,
	.init_irq       = pxa27x_init_irq,
	.handle_irq       = pxa27x_handle_irq,
	.init_machine   = csb726_init,
	.init_समय	= pxa_समयr_init,
	.restart	= pxa_restart,
MACHINE_END
