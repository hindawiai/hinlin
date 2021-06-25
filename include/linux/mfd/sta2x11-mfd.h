<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2009-2011 Wind River Systems, Inc.
 * Copyright (c) 2011 ST Microelectronics (Alessandro Rubini)
 *
 * The STMicroelectronics ConneXt (STA2X11) chip has several unrelated
 * functions in one PCI endpoपूर्णांक functions. This driver simply
 * रेजिस्टरs the platक्रमm devices in this iomemregion and exports a few
 * functions to access common रेजिस्टरs
 */

#अगर_अघोषित __STA2X11_MFD_H
#घोषणा __STA2X11_MFD_H
#समावेश <linux/types.h>
#समावेश <linux/pci.h>

क्रमागत sta2x11_mfd_plat_dev अणु
	sta2x11_sctl = 0,
	sta2x11_gpio,
	sta2x11_scr,
	sta2x11_समय,
	sta2x11_apbreg,
	sta2x11_apb_soc_regs,
	sta2x11_vic,
	sta2x11_n_mfd_plat_devs,
पूर्ण;

#घोषणा STA2X11_MFD_SCTL_NAME	       "sta2x11-sctl"
#घोषणा STA2X11_MFD_GPIO_NAME	       "sta2x11-gpio"
#घोषणा STA2X11_MFD_SCR_NAME	       "sta2x11-scr"
#घोषणा STA2X11_MFD_TIME_NAME	       "sta2x11-time"
#घोषणा STA2X11_MFD_APBREG_NAME	       "sta2x11-apbreg"
#घोषणा STA2X11_MFD_APB_SOC_REGS_NAME  "sta2x11-apb-soc-regs"
#घोषणा STA2X11_MFD_VIC_NAME	       "sta2x11-vic"

बाह्य u32
__sta2x11_mfd_mask(काष्ठा pci_dev *, u32, u32, u32, क्रमागत sta2x11_mfd_plat_dev);

/*
 * The MFD PCI block includes the GPIO peripherals and other रेजिस्टर blocks.
 * For GPIO, we have 32*4 bits (I use "gsta" क्रम "gpio sta2x11".)
 */
#घोषणा GSTA_GPIO_PER_BLOCK	32
#घोषणा GSTA_NR_BLOCKS		4
#घोषणा GSTA_NR_GPIO		(GSTA_GPIO_PER_BLOCK * GSTA_NR_BLOCKS)

/* Pinconfig is set by the board definition: altfunc, pull-up, pull-करोwn */
काष्ठा sta2x11_gpio_pdata अणु
	अचिन्हित pinconfig[GSTA_NR_GPIO];
पूर्ण;

/* Macros below lअगरted from sh_pfc.h, with minor dअगरferences */
#घोषणा PINMUX_TYPE_NONE		0
#घोषणा PINMUX_TYPE_FUNCTION		1
#घोषणा PINMUX_TYPE_OUTPUT_LOW		2
#घोषणा PINMUX_TYPE_OUTPUT_HIGH		3
#घोषणा PINMUX_TYPE_INPUT		4
#घोषणा PINMUX_TYPE_INPUT_PULLUP	5
#घोषणा PINMUX_TYPE_INPUT_PULLDOWN	6

/* Give names to GPIO pins, like PXA करोes, taken from the manual */
#घोषणा STA2X11_GPIO0			0
#घोषणा STA2X11_GPIO1			1
#घोषणा STA2X11_GPIO2			2
#घोषणा STA2X11_GPIO3			3
#घोषणा STA2X11_GPIO4			4
#घोषणा STA2X11_GPIO5			5
#घोषणा STA2X11_GPIO6			6
#घोषणा STA2X11_GPIO7			7
#घोषणा STA2X11_GPIO8_RGBOUT_RED7	8
#घोषणा STA2X11_GPIO9_RGBOUT_RED6	9
#घोषणा STA2X11_GPIO10_RGBOUT_RED5	10
#घोषणा STA2X11_GPIO11_RGBOUT_RED4	11
#घोषणा STA2X11_GPIO12_RGBOUT_RED3	12
#घोषणा STA2X11_GPIO13_RGBOUT_RED2	13
#घोषणा STA2X11_GPIO14_RGBOUT_RED1	14
#घोषणा STA2X11_GPIO15_RGBOUT_RED0	15
#घोषणा STA2X11_GPIO16_RGBOUT_GREEN7	16
#घोषणा STA2X11_GPIO17_RGBOUT_GREEN6	17
#घोषणा STA2X11_GPIO18_RGBOUT_GREEN5	18
#घोषणा STA2X11_GPIO19_RGBOUT_GREEN4	19
#घोषणा STA2X11_GPIO20_RGBOUT_GREEN3	20
#घोषणा STA2X11_GPIO21_RGBOUT_GREEN2	21
#घोषणा STA2X11_GPIO22_RGBOUT_GREEN1	22
#घोषणा STA2X11_GPIO23_RGBOUT_GREEN0	23
#घोषणा STA2X11_GPIO24_RGBOUT_BLUE7	24
#घोषणा STA2X11_GPIO25_RGBOUT_BLUE6	25
#घोषणा STA2X11_GPIO26_RGBOUT_BLUE5	26
#घोषणा STA2X11_GPIO27_RGBOUT_BLUE4	27
#घोषणा STA2X11_GPIO28_RGBOUT_BLUE3	28
#घोषणा STA2X11_GPIO29_RGBOUT_BLUE2	29
#घोषणा STA2X11_GPIO30_RGBOUT_BLUE1	30
#घोषणा STA2X11_GPIO31_RGBOUT_BLUE0	31
#घोषणा STA2X11_GPIO32_RGBOUT_VSYNCH	32
#घोषणा STA2X11_GPIO33_RGBOUT_HSYNCH	33
#घोषणा STA2X11_GPIO34_RGBOUT_DEN	34
#घोषणा STA2X11_GPIO35_ETH_CRS_DV	35
#घोषणा STA2X11_GPIO36_ETH_TXD1		36
#घोषणा STA2X11_GPIO37_ETH_TXD0		37
#घोषणा STA2X11_GPIO38_ETH_TX_EN	38
#घोषणा STA2X11_GPIO39_MDIO		39
#घोषणा STA2X11_GPIO40_ETH_REF_CLK	40
#घोषणा STA2X11_GPIO41_ETH_RXD1		41
#घोषणा STA2X11_GPIO42_ETH_RXD0		42
#घोषणा STA2X11_GPIO43_MDC		43
#घोषणा STA2X11_GPIO44_CAN_TX		44
#घोषणा STA2X11_GPIO45_CAN_RX		45
#घोषणा STA2X11_GPIO46_MLB_DAT		46
#घोषणा STA2X11_GPIO47_MLB_SIG		47
#घोषणा STA2X11_GPIO48_SPI0_CLK		48
#घोषणा STA2X11_GPIO49_SPI0_TXD		49
#घोषणा STA2X11_GPIO50_SPI0_RXD		50
#घोषणा STA2X11_GPIO51_SPI0_FRM		51
#घोषणा STA2X11_GPIO52_SPI1_CLK		52
#घोषणा STA2X11_GPIO53_SPI1_TXD		53
#घोषणा STA2X11_GPIO54_SPI1_RXD		54
#घोषणा STA2X11_GPIO55_SPI1_FRM		55
#घोषणा STA2X11_GPIO56_SPI2_CLK		56
#घोषणा STA2X11_GPIO57_SPI2_TXD		57
#घोषणा STA2X11_GPIO58_SPI2_RXD		58
#घोषणा STA2X11_GPIO59_SPI2_FRM		59
#घोषणा STA2X11_GPIO60_I2C0_SCL		60
#घोषणा STA2X11_GPIO61_I2C0_SDA		61
#घोषणा STA2X11_GPIO62_I2C1_SCL		62
#घोषणा STA2X11_GPIO63_I2C1_SDA		63
#घोषणा STA2X11_GPIO64_I2C2_SCL		64
#घोषणा STA2X11_GPIO65_I2C2_SDA		65
#घोषणा STA2X11_GPIO66_I2C3_SCL		66
#घोषणा STA2X11_GPIO67_I2C3_SDA		67
#घोषणा STA2X11_GPIO68_MSP0_RCK		68
#घोषणा STA2X11_GPIO69_MSP0_RXD		69
#घोषणा STA2X11_GPIO70_MSP0_RFS		70
#घोषणा STA2X11_GPIO71_MSP0_TCK		71
#घोषणा STA2X11_GPIO72_MSP0_TXD		72
#घोषणा STA2X11_GPIO73_MSP0_TFS		73
#घोषणा STA2X11_GPIO74_MSP0_SCK		74
#घोषणा STA2X11_GPIO75_MSP1_CK		75
#घोषणा STA2X11_GPIO76_MSP1_RXD		76
#घोषणा STA2X11_GPIO77_MSP1_FS		77
#घोषणा STA2X11_GPIO78_MSP1_TXD		78
#घोषणा STA2X11_GPIO79_MSP2_CK		79
#घोषणा STA2X11_GPIO80_MSP2_RXD		80
#घोषणा STA2X11_GPIO81_MSP2_FS		81
#घोषणा STA2X11_GPIO82_MSP2_TXD		82
#घोषणा STA2X11_GPIO83_MSP3_CK		83
#घोषणा STA2X11_GPIO84_MSP3_RXD		84
#घोषणा STA2X11_GPIO85_MSP3_FS		85
#घोषणा STA2X11_GPIO86_MSP3_TXD		86
#घोषणा STA2X11_GPIO87_MSP4_CK		87
#घोषणा STA2X11_GPIO88_MSP4_RXD		88
#घोषणा STA2X11_GPIO89_MSP4_FS		89
#घोषणा STA2X11_GPIO90_MSP4_TXD		90
#घोषणा STA2X11_GPIO91_MSP5_CK		91
#घोषणा STA2X11_GPIO92_MSP5_RXD		92
#घोषणा STA2X11_GPIO93_MSP5_FS		93
#घोषणा STA2X11_GPIO94_MSP5_TXD		94
#घोषणा STA2X11_GPIO95_SDIO3_DAT3	95
#घोषणा STA2X11_GPIO96_SDIO3_DAT2	96
#घोषणा STA2X11_GPIO97_SDIO3_DAT1	97
#घोषणा STA2X11_GPIO98_SDIO3_DAT0	98
#घोषणा STA2X11_GPIO99_SDIO3_CLK	99
#घोषणा STA2X11_GPIO100_SDIO3_CMD	100
#घोषणा STA2X11_GPIO101			101
#घोषणा STA2X11_GPIO102			102
#घोषणा STA2X11_GPIO103			103
#घोषणा STA2X11_GPIO104			104
#घोषणा STA2X11_GPIO105_SDIO2_DAT3	105
#घोषणा STA2X11_GPIO106_SDIO2_DAT2	106
#घोषणा STA2X11_GPIO107_SDIO2_DAT1	107
#घोषणा STA2X11_GPIO108_SDIO2_DAT0	108
#घोषणा STA2X11_GPIO109_SDIO2_CLK	109
#घोषणा STA2X11_GPIO110_SDIO2_CMD	110
#घोषणा STA2X11_GPIO111			111
#घोषणा STA2X11_GPIO112			112
#घोषणा STA2X11_GPIO113			113
#घोषणा STA2X11_GPIO114			114
#घोषणा STA2X11_GPIO115_SDIO1_DAT3	115
#घोषणा STA2X11_GPIO116_SDIO1_DAT2	116
#घोषणा STA2X11_GPIO117_SDIO1_DAT1	117
#घोषणा STA2X11_GPIO118_SDIO1_DAT0	118
#घोषणा STA2X11_GPIO119_SDIO1_CLK	119
#घोषणा STA2X11_GPIO120_SDIO1_CMD	120
#घोषणा STA2X11_GPIO121			121
#घोषणा STA2X11_GPIO122			122
#घोषणा STA2X11_GPIO123			123
#घोषणा STA2X11_GPIO124			124
#घोषणा STA2X11_GPIO125_UART2_TXD	125
#घोषणा STA2X11_GPIO126_UART2_RXD	126
#घोषणा STA2X11_GPIO127_UART3_TXD	127

/*
 * The APB bridge has its own रेजिस्टरs, needed by our users as well.
 * They are accessed with the following पढ़ो/mask/ग_लिखो function.
 */
अटल अंतरभूत u32
sta2x11_apbreg_mask(काष्ठा pci_dev *pdev, u32 reg, u32 mask, u32 val)
अणु
	वापस __sta2x11_mfd_mask(pdev, reg, mask, val, sta2x11_apbreg);
पूर्ण

/* CAN and MLB */
#घोषणा APBREG_BSR	0x00	/* Bridge Status Reg */
#घोषणा APBREG_PAER	0x08	/* Peripherals Address Error Reg */
#घोषणा APBREG_PWAC	0x20	/* Peripheral Write Access Control reg */
#घोषणा APBREG_PRAC	0x40	/* Peripheral Read Access Control reg */
#घोषणा APBREG_PCG	0x60	/* Peripheral Clock Gating Reg */
#घोषणा APBREG_PUR	0x80	/* Peripheral Under Reset Reg */
#घोषणा APBREG_EMU_PCG	0xA0	/* Emulator Peripheral Clock Gating Reg */

#घोषणा APBREG_CAN	(1 << 1)
#घोषणा APBREG_MLB	(1 << 3)

/* SARAC */
#घोषणा APBREG_BSR_SARAC     0x100 /* Bridge Status Reg */
#घोषणा APBREG_PAER_SARAC    0x108 /* Peripherals Address Error Reg */
#घोषणा APBREG_PWAC_SARAC    0x120 /* Peripheral Write Access Control reg */
#घोषणा APBREG_PRAC_SARAC    0x140 /* Peripheral Read Access Control reg */
#घोषणा APBREG_PCG_SARAC     0x160 /* Peripheral Clock Gating Reg */
#घोषणा APBREG_PUR_SARAC     0x180 /* Peripheral Under Reset Reg */
#घोषणा APBREG_EMU_PCG_SARAC 0x1A0 /* Emulator Peripheral Clock Gating Reg */

#घोषणा APBREG_SARAC	(1 << 2)

/*
 * The प्रणाली controller has its own रेजिस्टरs. Some of these are accessed
 * by out users as well, using the following पढ़ो/mask/ग_लिखो/function
 */
अटल अंतरभूत
u32 sta2x11_sctl_mask(काष्ठा pci_dev *pdev, u32 reg, u32 mask, u32 val)
अणु
	वापस __sta2x11_mfd_mask(pdev, reg, mask, val, sta2x11_sctl);
पूर्ण

#घोषणा SCTL_SCCTL		0x00	/* System controller control रेजिस्टर */
#घोषणा SCTL_ARMCFG		0x04	/* ARM configuration रेजिस्टर */
#घोषणा SCTL_SCPLLCTL		0x08	/* PLL control status रेजिस्टर */

#घोषणा SCTL_SCPLLCTL_AUDIO_PLL_PD	     BIT(1)
#घोषणा SCTL_SCPLLCTL_FRAC_CONTROL	     BIT(3)
#घोषणा SCTL_SCPLLCTL_STRB_BYPASS	     BIT(6)
#घोषणा SCTL_SCPLLCTL_STRB_INPUT	     BIT(8)

#घोषणा SCTL_SCPLLFCTRL		0x0c	/* PLL frequency control रेजिस्टर */

#घोषणा SCTL_SCPLLFCTRL_AUDIO_PLL_NDIV_MASK	0xff
#घोषणा SCTL_SCPLLFCTRL_AUDIO_PLL_NDIV_SHIFT	  10
#घोषणा SCTL_SCPLLFCTRL_AUDIO_PLL_IDF_MASK	   7
#घोषणा SCTL_SCPLLFCTRL_AUDIO_PLL_IDF_SHIFT	  21
#घोषणा SCTL_SCPLLFCTRL_AUDIO_PLL_ODF_MASK	   7
#घोषणा SCTL_SCPLLFCTRL_AUDIO_PLL_ODF_SHIFT	  18
#घोषणा SCTL_SCPLLFCTRL_DITHER_DISABLE_MASK     0x03
#घोषणा SCTL_SCPLLFCTRL_DITHER_DISABLE_SHIFT       4


#घोषणा SCTL_SCRESFRACT		0x10	/* PLL fractional input रेजिस्टर */

#घोषणा SCTL_SCRESFRACT_MASK	0x0000ffff


#घोषणा SCTL_SCRESCTRL1		0x14	/* Peripheral reset control 1 */
#घोषणा SCTL_SCRESXTRL2		0x18	/* Peripheral reset control 2 */
#घोषणा SCTL_SCPEREN0		0x1c	/* Peripheral घड़ी enable रेजिस्टर 0 */
#घोषणा SCTL_SCPEREN1		0x20	/* Peripheral घड़ी enable रेजिस्टर 1 */
#घोषणा SCTL_SCPEREN2		0x24	/* Peripheral घड़ी enable रेजिस्टर 2 */
#घोषणा SCTL_SCGRST		0x28	/* Peripheral global reset */
#घोषणा SCTL_SCPCIECSBRST       0x2c    /* PCIe PAB CSB reset status रेजिस्टर */
#घोषणा SCTL_SCPCIPMCR1		0x30	/* PCI घातer management control 1 */
#घोषणा SCTL_SCPCIPMCR2		0x34	/* PCI घातer management control 2 */
#घोषणा SCTL_SCPCIPMSR1		0x38	/* PCI घातer management status 1 */
#घोषणा SCTL_SCPCIPMSR2		0x3c	/* PCI घातer management status 2 */
#घोषणा SCTL_SCPCIPMSR3		0x40	/* PCI घातer management status 3 */
#घोषणा SCTL_SCINTREN		0x44	/* Interrupt enable */
#घोषणा SCTL_SCRISR		0x48	/* RAW पूर्णांकerrupt status */
#घोषणा SCTL_SCCLKSTAT0		0x4c	/* Peripheral घड़ीs status 0 */
#घोषणा SCTL_SCCLKSTAT1		0x50	/* Peripheral घड़ीs status 1 */
#घोषणा SCTL_SCCLKSTAT2		0x54	/* Peripheral घड़ीs status 2 */
#घोषणा SCTL_SCRSTSTA		0x58	/* Reset status रेजिस्टर */

#घोषणा SCTL_SCRESCTRL1_USB_PHY_POR	(1 << 0)
#घोषणा SCTL_SCRESCTRL1_USB_OTG	(1 << 1)
#घोषणा SCTL_SCRESCTRL1_USB_HRST	(1 << 2)
#घोषणा SCTL_SCRESCTRL1_USB_PHY_HOST	(1 << 3)
#घोषणा SCTL_SCRESCTRL1_SATAII	(1 << 4)
#घोषणा SCTL_SCRESCTRL1_VIP		(1 << 5)
#घोषणा SCTL_SCRESCTRL1_PER_MMC0	(1 << 6)
#घोषणा SCTL_SCRESCTRL1_PER_MMC1	(1 << 7)
#घोषणा SCTL_SCRESCTRL1_PER_GPIO0	(1 << 8)
#घोषणा SCTL_SCRESCTRL1_PER_GPIO1	(1 << 9)
#घोषणा SCTL_SCRESCTRL1_PER_GPIO2	(1 << 10)
#घोषणा SCTL_SCRESCTRL1_PER_GPIO3	(1 << 11)
#घोषणा SCTL_SCRESCTRL1_PER_MTU0	(1 << 12)
#घोषणा SCTL_SCRESCTRL1_KER_SPI0	(1 << 13)
#घोषणा SCTL_SCRESCTRL1_KER_SPI1	(1 << 14)
#घोषणा SCTL_SCRESCTRL1_KER_SPI2	(1 << 15)
#घोषणा SCTL_SCRESCTRL1_KER_MCI0	(1 << 16)
#घोषणा SCTL_SCRESCTRL1_KER_MCI1	(1 << 17)
#घोषणा SCTL_SCRESCTRL1_PRE_HSI2C0	(1 << 18)
#घोषणा SCTL_SCRESCTRL1_PER_HSI2C1	(1 << 19)
#घोषणा SCTL_SCRESCTRL1_PER_HSI2C2	(1 << 20)
#घोषणा SCTL_SCRESCTRL1_PER_HSI2C3	(1 << 21)
#घोषणा SCTL_SCRESCTRL1_PER_MSP0	(1 << 22)
#घोषणा SCTL_SCRESCTRL1_PER_MSP1	(1 << 23)
#घोषणा SCTL_SCRESCTRL1_PER_MSP2	(1 << 24)
#घोषणा SCTL_SCRESCTRL1_PER_MSP3	(1 << 25)
#घोषणा SCTL_SCRESCTRL1_PER_MSP4	(1 << 26)
#घोषणा SCTL_SCRESCTRL1_PER_MSP5	(1 << 27)
#घोषणा SCTL_SCRESCTRL1_PER_MMC	(1 << 28)
#घोषणा SCTL_SCRESCTRL1_KER_MSP0	(1 << 29)
#घोषणा SCTL_SCRESCTRL1_KER_MSP1	(1 << 30)
#घोषणा SCTL_SCRESCTRL1_KER_MSP2	(1 << 31)

#घोषणा SCTL_SCPEREN0_UART0		(1 << 0)
#घोषणा SCTL_SCPEREN0_UART1		(1 << 1)
#घोषणा SCTL_SCPEREN0_UART2		(1 << 2)
#घोषणा SCTL_SCPEREN0_UART3		(1 << 3)
#घोषणा SCTL_SCPEREN0_MSP0		(1 << 4)
#घोषणा SCTL_SCPEREN0_MSP1		(1 << 5)
#घोषणा SCTL_SCPEREN0_MSP2		(1 << 6)
#घोषणा SCTL_SCPEREN0_MSP3		(1 << 7)
#घोषणा SCTL_SCPEREN0_MSP4		(1 << 8)
#घोषणा SCTL_SCPEREN0_MSP5		(1 << 9)
#घोषणा SCTL_SCPEREN0_SPI0		(1 << 10)
#घोषणा SCTL_SCPEREN0_SPI1		(1 << 11)
#घोषणा SCTL_SCPEREN0_SPI2		(1 << 12)
#घोषणा SCTL_SCPEREN0_I2C0		(1 << 13)
#घोषणा SCTL_SCPEREN0_I2C1		(1 << 14)
#घोषणा SCTL_SCPEREN0_I2C2		(1 << 15)
#घोषणा SCTL_SCPEREN0_I2C3		(1 << 16)
#घोषणा SCTL_SCPEREN0_SVDO_LVDS		(1 << 17)
#घोषणा SCTL_SCPEREN0_USB_HOST		(1 << 18)
#घोषणा SCTL_SCPEREN0_USB_OTG		(1 << 19)
#घोषणा SCTL_SCPEREN0_MCI0		(1 << 20)
#घोषणा SCTL_SCPEREN0_MCI1		(1 << 21)
#घोषणा SCTL_SCPEREN0_MCI2		(1 << 22)
#घोषणा SCTL_SCPEREN0_MCI3		(1 << 23)
#घोषणा SCTL_SCPEREN0_SATA		(1 << 24)
#घोषणा SCTL_SCPEREN0_ETHERNET		(1 << 25)
#घोषणा SCTL_SCPEREN0_VIC		(1 << 26)
#घोषणा SCTL_SCPEREN0_DMA_AUDIO		(1 << 27)
#घोषणा SCTL_SCPEREN0_DMA_SOC		(1 << 28)
#घोषणा SCTL_SCPEREN0_RAM		(1 << 29)
#घोषणा SCTL_SCPEREN0_VIP		(1 << 30)
#घोषणा SCTL_SCPEREN0_ARM		(1 << 31)

#घोषणा SCTL_SCPEREN1_UART0		(1 << 0)
#घोषणा SCTL_SCPEREN1_UART1		(1 << 1)
#घोषणा SCTL_SCPEREN1_UART2		(1 << 2)
#घोषणा SCTL_SCPEREN1_UART3		(1 << 3)
#घोषणा SCTL_SCPEREN1_MSP0		(1 << 4)
#घोषणा SCTL_SCPEREN1_MSP1		(1 << 5)
#घोषणा SCTL_SCPEREN1_MSP2		(1 << 6)
#घोषणा SCTL_SCPEREN1_MSP3		(1 << 7)
#घोषणा SCTL_SCPEREN1_MSP4		(1 << 8)
#घोषणा SCTL_SCPEREN1_MSP5		(1 << 9)
#घोषणा SCTL_SCPEREN1_SPI0		(1 << 10)
#घोषणा SCTL_SCPEREN1_SPI1		(1 << 11)
#घोषणा SCTL_SCPEREN1_SPI2		(1 << 12)
#घोषणा SCTL_SCPEREN1_I2C0		(1 << 13)
#घोषणा SCTL_SCPEREN1_I2C1		(1 << 14)
#घोषणा SCTL_SCPEREN1_I2C2		(1 << 15)
#घोषणा SCTL_SCPEREN1_I2C3		(1 << 16)
#घोषणा SCTL_SCPEREN1_USB_PHY		(1 << 17)

/*
 * APB-SOC रेजिस्टरs
 */
अटल अंतरभूत
u32 sta2x11_apb_soc_regs_mask(काष्ठा pci_dev *pdev, u32 reg, u32 mask, u32 val)
अणु
	वापस __sta2x11_mfd_mask(pdev, reg, mask, val, sta2x11_apb_soc_regs);
पूर्ण

#घोषणा PCIE_EP1_FUNC3_0_INTR_REG	0x000
#घोषणा PCIE_EP1_FUNC7_4_INTR_REG	0x004
#घोषणा PCIE_EP2_FUNC3_0_INTR_REG	0x008
#घोषणा PCIE_EP2_FUNC7_4_INTR_REG	0x00c
#घोषणा PCIE_EP3_FUNC3_0_INTR_REG	0x010
#घोषणा PCIE_EP3_FUNC7_4_INTR_REG	0x014
#घोषणा PCIE_EP4_FUNC3_0_INTR_REG	0x018
#घोषणा PCIE_EP4_FUNC7_4_INTR_REG	0x01c
#घोषणा PCIE_INTR_ENABLE0_REG		0x020
#घोषणा PCIE_INTR_ENABLE1_REG		0x024
#घोषणा PCIE_EP1_FUNC_TC_REG		0x028
#घोषणा PCIE_EP2_FUNC_TC_REG		0x02c
#घोषणा PCIE_EP3_FUNC_TC_REG		0x030
#घोषणा PCIE_EP4_FUNC_TC_REG		0x034
#घोषणा PCIE_EP1_FUNC_F_REG		0x038
#घोषणा PCIE_EP2_FUNC_F_REG		0x03c
#घोषणा PCIE_EP3_FUNC_F_REG		0x040
#घोषणा PCIE_EP4_FUNC_F_REG		0x044
#घोषणा PCIE_PAB_AMBA_SW_RST_REG	0x048
#घोषणा PCIE_PM_STATUS_0_PORT_0_4	0x04c
#घोषणा PCIE_PM_STATUS_7_0_EP1		0x050
#घोषणा PCIE_PM_STATUS_7_0_EP2		0x054
#घोषणा PCIE_PM_STATUS_7_0_EP3		0x058
#घोषणा PCIE_PM_STATUS_7_0_EP4		0x05c
#घोषणा PCIE_DEV_ID_0_EP1_REG		0x060
#घोषणा PCIE_CC_REV_ID_0_EP1_REG	0x064
#घोषणा PCIE_DEV_ID_1_EP1_REG		0x068
#घोषणा PCIE_CC_REV_ID_1_EP1_REG	0x06c
#घोषणा PCIE_DEV_ID_2_EP1_REG		0x070
#घोषणा PCIE_CC_REV_ID_2_EP1_REG	0x074
#घोषणा PCIE_DEV_ID_3_EP1_REG		0x078
#घोषणा PCIE_CC_REV_ID_3_EP1_REG	0x07c
#घोषणा PCIE_DEV_ID_4_EP1_REG		0x080
#घोषणा PCIE_CC_REV_ID_4_EP1_REG	0x084
#घोषणा PCIE_DEV_ID_5_EP1_REG		0x088
#घोषणा PCIE_CC_REV_ID_5_EP1_REG	0x08c
#घोषणा PCIE_DEV_ID_6_EP1_REG		0x090
#घोषणा PCIE_CC_REV_ID_6_EP1_REG	0x094
#घोषणा PCIE_DEV_ID_7_EP1_REG		0x098
#घोषणा PCIE_CC_REV_ID_7_EP1_REG	0x09c
#घोषणा PCIE_DEV_ID_0_EP2_REG		0x0a0
#घोषणा PCIE_CC_REV_ID_0_EP2_REG	0x0a4
#घोषणा PCIE_DEV_ID_1_EP2_REG		0x0a8
#घोषणा PCIE_CC_REV_ID_1_EP2_REG	0x0ac
#घोषणा PCIE_DEV_ID_2_EP2_REG		0x0b0
#घोषणा PCIE_CC_REV_ID_2_EP2_REG	0x0b4
#घोषणा PCIE_DEV_ID_3_EP2_REG		0x0b8
#घोषणा PCIE_CC_REV_ID_3_EP2_REG	0x0bc
#घोषणा PCIE_DEV_ID_4_EP2_REG		0x0c0
#घोषणा PCIE_CC_REV_ID_4_EP2_REG	0x0c4
#घोषणा PCIE_DEV_ID_5_EP2_REG		0x0c8
#घोषणा PCIE_CC_REV_ID_5_EP2_REG	0x0cc
#घोषणा PCIE_DEV_ID_6_EP2_REG		0x0d0
#घोषणा PCIE_CC_REV_ID_6_EP2_REG	0x0d4
#घोषणा PCIE_DEV_ID_7_EP2_REG		0x0d8
#घोषणा PCIE_CC_REV_ID_7_EP2_REG	0x0dC
#घोषणा PCIE_DEV_ID_0_EP3_REG		0x0e0
#घोषणा PCIE_CC_REV_ID_0_EP3_REG	0x0e4
#घोषणा PCIE_DEV_ID_1_EP3_REG		0x0e8
#घोषणा PCIE_CC_REV_ID_1_EP3_REG	0x0ec
#घोषणा PCIE_DEV_ID_2_EP3_REG		0x0f0
#घोषणा PCIE_CC_REV_ID_2_EP3_REG	0x0f4
#घोषणा PCIE_DEV_ID_3_EP3_REG		0x0f8
#घोषणा PCIE_CC_REV_ID_3_EP3_REG	0x0fc
#घोषणा PCIE_DEV_ID_4_EP3_REG		0x100
#घोषणा PCIE_CC_REV_ID_4_EP3_REG	0x104
#घोषणा PCIE_DEV_ID_5_EP3_REG		0x108
#घोषणा PCIE_CC_REV_ID_5_EP3_REG	0x10c
#घोषणा PCIE_DEV_ID_6_EP3_REG		0x110
#घोषणा PCIE_CC_REV_ID_6_EP3_REG	0x114
#घोषणा PCIE_DEV_ID_7_EP3_REG		0x118
#घोषणा PCIE_CC_REV_ID_7_EP3_REG	0x11c
#घोषणा PCIE_DEV_ID_0_EP4_REG		0x120
#घोषणा PCIE_CC_REV_ID_0_EP4_REG	0x124
#घोषणा PCIE_DEV_ID_1_EP4_REG		0x128
#घोषणा PCIE_CC_REV_ID_1_EP4_REG	0x12c
#घोषणा PCIE_DEV_ID_2_EP4_REG		0x130
#घोषणा PCIE_CC_REV_ID_2_EP4_REG	0x134
#घोषणा PCIE_DEV_ID_3_EP4_REG		0x138
#घोषणा PCIE_CC_REV_ID_3_EP4_REG	0x13c
#घोषणा PCIE_DEV_ID_4_EP4_REG		0x140
#घोषणा PCIE_CC_REV_ID_4_EP4_REG	0x144
#घोषणा PCIE_DEV_ID_5_EP4_REG		0x148
#घोषणा PCIE_CC_REV_ID_5_EP4_REG	0x14c
#घोषणा PCIE_DEV_ID_6_EP4_REG		0x150
#घोषणा PCIE_CC_REV_ID_6_EP4_REG	0x154
#घोषणा PCIE_DEV_ID_7_EP4_REG		0x158
#घोषणा PCIE_CC_REV_ID_7_EP4_REG	0x15c
#घोषणा PCIE_SUBSYS_VEN_ID_REG		0x160
#घोषणा PCIE_COMMON_CLOCK_CONFIG_0_4_0	0x164
#घोषणा PCIE_MIPHYP_SSC_EN_REG		0x168
#घोषणा PCIE_MIPHYP_ADDR_REG		0x16c
#घोषणा PCIE_L1_ASPM_READY_REG		0x170
#घोषणा PCIE_EXT_CFG_RDY_REG		0x174
#घोषणा PCIE_SoC_INT_ROUTER_STATUS0_REG 0x178
#घोषणा PCIE_SoC_INT_ROUTER_STATUS1_REG 0x17c
#घोषणा PCIE_SoC_INT_ROUTER_STATUS2_REG 0x180
#घोषणा PCIE_SoC_INT_ROUTER_STATUS3_REG 0x184
#घोषणा DMA_IP_CTRL_REG			0x324
#घोषणा DISP_BRIDGE_PU_PD_CTRL_REG	0x328
#घोषणा VIP_PU_PD_CTRL_REG		0x32c
#घोषणा USB_MLB_PU_PD_CTRL_REG		0x330
#घोषणा SDIO_PU_PD_MISCFUNC_CTRL_REG1	0x334
#घोषणा SDIO_PU_PD_MISCFUNC_CTRL_REG2	0x338
#घोषणा UART_PU_PD_CTRL_REG		0x33c
#घोषणा ARM_Lock			0x340
#घोषणा SYS_IO_CHAR_REG1		0x344
#घोषणा SYS_IO_CHAR_REG2		0x348
#घोषणा SATA_CORE_ID_REG		0x34c
#घोषणा SATA_CTRL_REG			0x350
#घोषणा I2C_HSFIX_MISC_REG		0x354
#घोषणा SPARE2_RESERVED			0x358
#घोषणा SPARE3_RESERVED			0x35c
#घोषणा MASTER_LOCK_REG			0x368
#घोषणा SYSTEM_CONFIG_STATUS_REG	0x36c
#घोषणा MSP_CLK_CTRL_REG		0x39c
#घोषणा COMPENSATION_REG1		0x3c4
#घोषणा COMPENSATION_REG2		0x3c8
#घोषणा COMPENSATION_REG3		0x3cc
#घोषणा TEST_CTL_REG			0x3d0

/*
 * SECR (OTP) रेजिस्टरs
 */
#घोषणा STA2X11_SECR_CR			0x00
#घोषणा STA2X11_SECR_FVR0		0x10
#घोषणा STA2X11_SECR_FVR1		0x14

बाह्य पूर्णांक sta2x11_mfd_get_regs_data(काष्ठा platक्रमm_device *pdev,
				     क्रमागत sta2x11_mfd_plat_dev index,
				     व्योम __iomem **regs,
				     spinlock_t **lock);

#पूर्ण_अगर /* __STA2X11_MFD_H */
