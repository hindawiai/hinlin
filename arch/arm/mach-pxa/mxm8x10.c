<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/arch/arm/mach-pxa/mxm8x10.c
 *
 * Support क्रम the Embedian MXM-8x10 Computer on Module
 *
 * Copyright (C) 2006 Marvell International Ltd.
 * Copyright (C) 2009 Embedian Inc.
 * Copyright (C) 2009 TMT Services & Supplies (Pty) Ltd.
 *
 * 2007-09-04: eric miao <eric.y.miao@gmail.com>
 *             reग_लिखो to align with latest kernel
 *
 * 2010-01-09: Edwin Peer <epeer@पंचांगtservices.co.za>
 * 	       Hennie van der Merwe <hvdmerwe@पंचांगtservices.co.za>
 *             rework क्रम upstream merge
 */

#समावेश <linux/serial_8250.h>
#समावेश <linux/dm9000.h>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/platक्रमm_data/i2c-pxa.h>

#समावेश <linux/platक्रमm_data/mtd-nand-pxa3xx.h>

#समावेश <linux/platक्रमm_data/video-pxafb.h>
#समावेश <linux/platक्रमm_data/mmc-pxamci.h>
#समावेश <linux/platक्रमm_data/usb-ohci-pxa27x.h>
#समावेश "pxa320.h"

#समावेश "mxm8x10.h"

#समावेश "devices.h"
#समावेश "generic.h"

/* GPIO pin definition

External device stuff   - Leave unconfigured क्रम now...
---------------------
GPIO0   -   DREQ    (External DMA Request)
GPIO3   -   nGCS2   (External Chip Select) Where is nGCS0; nGCS1; nGCS4; nGCS5 ?
GPIO4   -   nGCS3
GPIO15  -   EXT_GPIO1
GPIO16  -   EXT_GPIO2
GPIO17  -   EXT_GPIO3
GPIO24  -   EXT_GPIO4
GPIO25  -   EXT_GPIO5
GPIO26  -   EXT_GPIO6
GPIO27  -   EXT_GPIO7
GPIO28  -   EXT_GPIO8
GPIO29  -   EXT_GPIO9
GPIO30  -   EXT_GPIO10
GPIO31  -   EXT_GPIO11
GPIO57  -   EXT_GPIO12
GPIO74  -   EXT_IRQ1
GPIO75  -   EXT_IRQ2
GPIO76  -   EXT_IRQ3
GPIO77  -   EXT_IRQ4
GPIO78  -   EXT_IRQ5
GPIO79  -   EXT_IRQ6
GPIO80  -   EXT_IRQ7
GPIO81  -   EXT_IRQ8
GPIO87  -   VCCIO_PWREN (External Device PWREN)

Dallas 1-Wire   - Leave unconfigured क्रम now...
-------------
GPIO0_2 -   DS - 1Wire

Ethernet
--------
GPIO1   -   DM9000 PWR
GPIO9   -   DM9K_nIRQ
GPIO36  -   DM9K_RESET

Keypad  - Leave unconfigured by क्रम now...
------
GPIO1_2 -   KP_DKIN0
GPIO5_2 -   KP_MKOUT7
GPIO82  -   KP_DKIN1
GPIO85  -   KP_DKIN2
GPIO86  -   KP_DKIN3
GPIO113 -   KP_MKIN0
GPIO114 -   KP_MKIN1
GPIO115 -   KP_MKIN2
GPIO116 -   KP_MKIN3
GPIO117 -   KP_MKIN4
GPIO118 -   KP_MKIN5
GPIO119 -   KP_MKIN6
GPIO120 -   KP_MKIN7
GPIO121 -   KP_MKOUT0
GPIO122 -   KP_MKOUT1
GPIO122 -   KP_MKOUT2
GPIO123 -   KP_MKOUT3
GPIO124 -   KP_MKOUT4
GPIO125 -   KP_MKOUT5
GPIO127 -   KP_MKOUT6

Data Bus    - Leave unconfigured क्रम now...
--------
GPIO2   -   nWait (Data Bus)

USB Device
----------
GPIO4_2 -   USBD_PULLUP
GPIO10  -   UTM_CLK (USB Device UTM Clk)
GPIO49  -   USB 2.0 Device UTM_DATA0
GPIO50  -   USB 2.0 Device UTM_DATA1
GPIO51  -   USB 2.0 Device UTM_DATA2
GPIO52  -   USB 2.0 Device UTM_DATA3
GPIO53  -   USB 2.0 Device UTM_DATA4
GPIO54  -   USB 2.0 Device UTM_DATA5
GPIO55  -   USB 2.0 Device UTM_DATA6
GPIO56  -   USB 2.0 Device UTM_DATA7
GPIO58  -   UTM_RXVALID (USB 2.0 Device)
GPIO59  -   UTM_RXACTIVE (USB 2.0 Device)
GPIO60  -   UTM_RXERROR
GPIO61  -   UTM_OPMODE0
GPIO62  -   UTM_OPMODE1
GPIO71  -   USBD_INT    (USB Device?)
GPIO73  -   UTM_TXREADY (USB 2.0 Device)
GPIO83  -   UTM_TXVALID (USB 2.0 Device)
GPIO98  -   UTM_RESET   (USB 2.0 device)
GPIO99  -   UTM_XCVR_SELECT
GPIO100 -   UTM_TERM_SELECT
GPIO101 -   UTM_SUSPENDM_X
GPIO102 -   UTM_LINESTATE0
GPIO103 -   UTM_LINESTATE1

Card-Bus Interface  - Leave unconfigured क्रम now...
------------------
GPIO5   -   nPIOR (I/O space output enable)
GPIO6   -   nPIOW (I/O space ग_लिखो enable)
GPIO7   -   nIOS16 (Input from I/O space telling size of data bus)
GPIO8   -   nPWAIT (Input क्रम inserting रुको states)

LCD
---
GPIO6_2     -   LDD0
GPIO7_2     -   LDD1
GPIO8_2     -   LDD2
GPIO9_2     -   LDD3
GPIO11_2    -   LDD5
GPIO12_2    -   LDD6
GPIO13_2    -   LDD7
GPIO14_2    -   VSYNC
GPIO15_2    -   HSYNC
GPIO16_2    -   VCLK
GPIO17_2    -   HCLK
GPIO18_2    -   VDEN
GPIO63      -   LDD8    (CPU LCD)
GPIO64      -   LDD9    (CPU LCD)
GPIO65      -   LDD10   (CPU LCD)
GPIO66      -   LDD11   (CPU LCD)
GPIO67      -   LDD12   (CPU LCD)
GPIO68      -   LDD13   (CPU LCD)
GPIO69      -   LDD14   (CPU LCD)
GPIO70      -   LDD15   (CPU LCD)
GPIO88      -   VCCLCD_PWREN (LCD Panel PWREN)
GPIO97      -   BACKLIGHT_EN
GPIO104     -   LCD_PWREN

PWM   - Leave unconfigured क्रम now...
---
GPIO11  -   PWM0
GPIO12  -   PWM1
GPIO13  -   PWM2
GPIO14  -   PWM3

SD-CARD
-------
GPIO18  -   SDDATA0
GPIO19  -   SDDATA1
GPIO20  -   SDDATA2
GPIO21  -   SDDATA3
GPIO22  -   SDCLK
GPIO23  -   SDCMD
GPIO72  -   SD_WP
GPIO84  -   SD_nIRQ_CD  (SD-Card)

I2C
---
GPIO32  -   I2CSCL
GPIO33  -   I2CSDA

AC97
----
GPIO35  -   AC97_SDATA_IN
GPIO37  -   AC97_SDATA_OUT
GPIO38  -   AC97_SYNC
GPIO39  -   AC97_BITCLK
GPIO40  -   AC97_nRESET

UART1
-----
GPIO41  -   UART_RXD1
GPIO42  -   UART_TXD1
GPIO43  -   UART_CTS1
GPIO44  -   UART_DCD1
GPIO45  -   UART_DSR1
GPIO46  -   UART_nRI1
GPIO47  -   UART_DTR1
GPIO48  -   UART_RTS1

UART2
-----
GPIO109 -   RTS2
GPIO110 -   RXD2
GPIO111 -   TXD2
GPIO112 -   nCTS2

UART3
-----
GPIO105 -   nCTS3
GPIO106 -   nRTS3
GPIO107 -   TXD3
GPIO108 -   RXD3

SSP3    - Leave unconfigured क्रम now...
----
GPIO89  -   SSP3_CLK
GPIO90  -   SSP3_SFRM
GPIO91  -   SSP3_TXD
GPIO92  -   SSP3_RXD

SSP4
GPIO93  -   SSP4_CLK
GPIO94  -   SSP4_SFRM
GPIO95  -   SSP4_TXD
GPIO96  -   SSP4_RXD
*/

अटल mfp_cfg_t mfp_cfg[] __initdata = अणु
	/* USB */
	GPIO10_UTM_CLK,
	GPIO49_U2D_PHYDATA_0,
	GPIO50_U2D_PHYDATA_1,
	GPIO51_U2D_PHYDATA_2,
	GPIO52_U2D_PHYDATA_3,
	GPIO53_U2D_PHYDATA_4,
	GPIO54_U2D_PHYDATA_5,
	GPIO55_U2D_PHYDATA_6,
	GPIO56_U2D_PHYDATA_7,
	GPIO58_UTM_RXVALID,
	GPIO59_UTM_RXACTIVE,
	GPIO60_U2D_RXERROR,
	GPIO61_U2D_OPMODE0,
	GPIO62_U2D_OPMODE1,
	GPIO71_GPIO, /* USBD_INT */
	GPIO73_UTM_TXREADY,
	GPIO83_U2D_TXVALID,
	GPIO98_U2D_RESET,
	GPIO99_U2D_XCVR_SEL,
	GPIO100_U2D_TERM_SEL,
	GPIO101_U2D_SUSPEND,
	GPIO102_UTM_LINESTATE_0,
	GPIO103_UTM_LINESTATE_1,
	GPIO4_2_GPIO | MFP_PULL_HIGH, /* UTM_PULLUP */

	/* DM9000 */
	GPIO1_GPIO,
	GPIO9_GPIO,
	GPIO36_GPIO,

	/* AC97 */
	GPIO35_AC97_SDATA_IN_0,
	GPIO37_AC97_SDATA_OUT,
	GPIO38_AC97_SYNC,
	GPIO39_AC97_BITCLK,
	GPIO40_AC97_nACRESET,

	/* UARTS */
	GPIO41_UART1_RXD,
	GPIO42_UART1_TXD,
	GPIO43_UART1_CTS,
	GPIO44_UART1_DCD,
	GPIO45_UART1_DSR,
	GPIO46_UART1_RI,
	GPIO47_UART1_DTR,
	GPIO48_UART1_RTS,

	GPIO109_UART2_RTS,
	GPIO110_UART2_RXD,
	GPIO111_UART2_TXD,
	GPIO112_UART2_CTS,

	GPIO105_UART3_CTS,
	GPIO106_UART3_RTS,
	GPIO107_UART3_TXD,
	GPIO108_UART3_RXD,

	GPIO78_GPIO,
	GPIO79_GPIO,
	GPIO80_GPIO,
	GPIO81_GPIO,

	/* I2C */
	GPIO32_I2C_SCL,
	GPIO33_I2C_SDA,

	/* MMC */
	GPIO18_MMC1_DAT0,
	GPIO19_MMC1_DAT1,
	GPIO20_MMC1_DAT2,
	GPIO21_MMC1_DAT3,
	GPIO22_MMC1_CLK,
	GPIO23_MMC1_CMD,
	GPIO72_GPIO | MFP_PULL_HIGH, /* Card Detect */
	GPIO84_GPIO | MFP_PULL_LOW, /* Write Protect */

	/* IRQ */
	GPIO74_GPIO | MFP_LPM_EDGE_RISE, /* EXT_IRQ1 */
	GPIO75_GPIO | MFP_LPM_EDGE_RISE, /* EXT_IRQ2 */
	GPIO76_GPIO | MFP_LPM_EDGE_RISE, /* EXT_IRQ3 */
	GPIO77_GPIO | MFP_LPM_EDGE_RISE, /* EXT_IRQ4 */
	GPIO78_GPIO | MFP_LPM_EDGE_RISE, /* EXT_IRQ5 */
	GPIO79_GPIO | MFP_LPM_EDGE_RISE, /* EXT_IRQ6 */
	GPIO80_GPIO | MFP_LPM_EDGE_RISE, /* EXT_IRQ7 */
	GPIO81_GPIO | MFP_LPM_EDGE_RISE  /* EXT_IRQ8 */
पूर्ण;

/* MMC/MCI Support */
#अगर defined(CONFIG_MMC)
अटल काष्ठा pxamci_platक्रमm_data mxm_8x10_mci_platक्रमm_data = अणु
	.ocr_mask = MMC_VDD_32_33 | MMC_VDD_33_34,
	.detect_delay_ms = 10,
पूर्ण;

अटल काष्ठा gpiod_lookup_table mxm_8x10_mci_gpio_table = अणु
	.dev_id = "pxa2xx-mci.0",
	.table = अणु
		/* Card detect on GPIO 72 */
		GPIO_LOOKUP("gpio-pxa", MXM_8X10_SD_nCD,
			    "cd", GPIO_ACTIVE_LOW),
		/* Write protect on GPIO 84 */
		GPIO_LOOKUP("gpio-pxa", MXM_8X10_SD_WP,
			    "wp", GPIO_ACTIVE_LOW),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

व्योम __init mxm_8x10_mmc_init(व्योम)
अणु
	gpiod_add_lookup_table(&mxm_8x10_mci_gpio_table);
	pxa_set_mci_info(&mxm_8x10_mci_platक्रमm_data);
पूर्ण
#पूर्ण_अगर

/* USB Open Host Controller Interface */
अटल काष्ठा pxaohci_platक्रमm_data mxm_8x10_ohci_platक्रमm_data = अणु
	.port_mode = PMM_NPS_MODE,
	.flags = ENABLE_PORT_ALL
पूर्ण;

व्योम __init mxm_8x10_usb_host_init(व्योम)
अणु
	pxa_set_ohci_info(&mxm_8x10_ohci_platक्रमm_data);
पूर्ण

/* AC97 Sound Support */
अटल काष्ठा platक्रमm_device mxm_8x10_ac97_device = अणु
	.name = "pxa2xx-ac97"
पूर्ण;

व्योम __init mxm_8x10_ac97_init(व्योम)
अणु
	platक्रमm_device_रेजिस्टर(&mxm_8x10_ac97_device);
पूर्ण

/* न_अंकD flash Support */
#अगर IS_ENABLED(CONFIG_MTD_न_अंकD_MARVELL)
#घोषणा न_अंकD_BLOCK_SIZE SZ_128K
#घोषणा NB(x)           (न_अंकD_BLOCK_SIZE * (x))
अटल काष्ठा mtd_partition mxm_8x10_nand_partitions[] = अणु
	[0] = अणु
	       .name = "boot",
	       .size = NB(0x002),
	       .offset = NB(0x000),
	       .mask_flags = MTD_WRITEABLE
	पूर्ण,
	[1] = अणु
	       .name = "kernel",
	       .size = NB(0x010),
	       .offset = NB(0x002),
	       .mask_flags = MTD_WRITEABLE
	पूर्ण,
	[2] = अणु
	       .name = "root",
	       .size = NB(0x36c),
	       .offset = NB(0x012)
	पूर्ण,
	[3] = अणु
	       .name = "bbt",
	       .size = NB(0x082),
	       .offset = NB(0x37e),
	       .mask_flags = MTD_WRITEABLE
	पूर्ण
पूर्ण;

अटल काष्ठा pxa3xx_nand_platक्रमm_data mxm_8x10_nand_info = अणु
	.keep_config	= 1,
	.parts		= mxm_8x10_nand_partitions,
	.nr_parts	= ARRAY_SIZE(mxm_8x10_nand_partitions)
पूर्ण;

अटल व्योम __init mxm_8x10_nand_init(व्योम)
अणु
	pxa3xx_set_nand_info(&mxm_8x10_nand_info);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम mxm_8x10_nand_init(व्योम) अणुपूर्ण
#पूर्ण_अगर /* IS_ENABLED(CONFIG_MTD_न_अंकD_MARVELL) */

/* Ethernet support: Davicom DM9000 */
अटल काष्ठा resource dm9k_resources[] = अणु
	[0] = अणु
	       .start = MXM_8X10_ETH_PHYS + 0x300,
	       .end = MXM_8X10_ETH_PHYS + 0x300,
	       .flags = IORESOURCE_MEM
	पूर्ण,
	[1] = अणु
	       .start = MXM_8X10_ETH_PHYS + 0x308,
	       .end = MXM_8X10_ETH_PHYS + 0x308,
	       .flags = IORESOURCE_MEM
	पूर्ण,
	[2] = अणु
	       .start = PXA_GPIO_TO_IRQ(mfp_to_gpio(MFP_PIN_GPIO9)),
	       .end = PXA_GPIO_TO_IRQ(mfp_to_gpio(MFP_PIN_GPIO9)),
	       .flags = IORESOURCE_IRQ | IORESOURCE_IRQ_HIGHEDGE
	पूर्ण
पूर्ण;

अटल काष्ठा dm9000_plat_data dm9k_plat_data = अणु
	.flags = DM9000_PLATF_16BITONLY
पूर्ण;

अटल काष्ठा platक्रमm_device dm9k_device = अणु
	.name = "dm9000",
	.id = 0,
	.num_resources = ARRAY_SIZE(dm9k_resources),
	.resource = dm9k_resources,
	.dev = अणु
		.platक्रमm_data = &dm9k_plat_data
	पूर्ण
पूर्ण;

अटल व्योम __init mxm_8x10_ethernet_init(व्योम)
अणु
	platक्रमm_device_रेजिस्टर(&dm9k_device);
पूर्ण

/* PXA UARTs */
अटल व्योम __init mxm_8x10_uarts_init(व्योम)
अणु
	pxa_set_ffuart_info(शून्य);
	pxa_set_btuart_info(शून्य);
	pxa_set_stuart_info(शून्य);
पूर्ण

/* I2C and Real Time Clock */
अटल काष्ठा i2c_board_info __initdata mxm_8x10_i2c_devices[] = अणु
	अणु
		I2C_BOARD_INFO("ds1337", 0x68)
	पूर्ण
पूर्ण;

अटल व्योम __init mxm_8x10_i2c_init(व्योम)
अणु
	i2c_रेजिस्टर_board_info(0, mxm_8x10_i2c_devices,
				ARRAY_SIZE(mxm_8x10_i2c_devices));
	pxa_set_i2c_info(शून्य);
पूर्ण

व्योम __init mxm_8x10_barebones_init(व्योम)
अणु
	pxa3xx_mfp_config(ARRAY_AND_SIZE(mfp_cfg));

	mxm_8x10_uarts_init();
	mxm_8x10_nand_init();
	mxm_8x10_i2c_init();
	mxm_8x10_ethernet_init();
पूर्ण
