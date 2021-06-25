<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  arch/arm/mach-pxa/include/mach/gumstix.h
 */

#समावेश <mach/irqs.h> /* PXA_GPIO_TO_IRQ */

/* BTRESET - Reset line to Bluetooth module, active low संकेत. */
#घोषणा GPIO_GUMSTIX_BTRESET          7
#घोषणा GPIO_GUMSTIX_BTRESET_MD		(GPIO_GUMSTIX_BTRESET | GPIO_OUT)


/*
GPIOn - Input from MAX823 (or equiv), normalizing USB +5V पूर्णांकo a clean
पूर्णांकerrupt संकेत क्रम determining cable presence. On the gumstix F,
this moves to GPIO17 and GPIO37. */

/* GPIOx - Connects to USB D+ and used as a pull-up after GPIOn
has detected a cable insertion; driven low otherwise. */

#घोषणा GPIO_GUMSTIX_USB_GPIOn		35
#घोषणा GPIO_GUMSTIX_USB_GPIOx		41

/* usb state change */
#घोषणा GUMSTIX_USB_INTR_IRQ		PXA_GPIO_TO_IRQ(GPIO_GUMSTIX_USB_GPIOn)

#घोषणा GPIO_GUMSTIX_USB_GPIOn_MD	(GPIO_GUMSTIX_USB_GPIOn | GPIO_IN)
#घोषणा GPIO_GUMSTIX_USB_GPIOx_CON_MD	(GPIO_GUMSTIX_USB_GPIOx | GPIO_OUT)
#घोषणा GPIO_GUMSTIX_USB_GPIOx_DIS_MD	(GPIO_GUMSTIX_USB_GPIOx | GPIO_IN)

/*
 * SD/MMC definitions
 */
#घोषणा GUMSTIX_GPIO_nSD_WP		22 /* SD Write Protect */
#घोषणा GUMSTIX_GPIO_nSD_DETECT		11 /* MMC/SD Card Detect */
#घोषणा GUMSTIX_IRQ_GPIO_nSD_DETECT	PXA_GPIO_TO_IRQ(GUMSTIX_GPIO_nSD_DETECT)

/*
 * SMC Ethernet definitions
 * ETH_RST provides a hardware reset line to the ethernet chip
 * ETH is the IRQ line in from the ethernet chip to the PXA
 */
#घोषणा GPIO_GUMSTIX_ETH0_RST		80
#घोषणा GPIO_GUMSTIX_ETH0_RST_MD	(GPIO_GUMSTIX_ETH0_RST | GPIO_OUT)
#घोषणा GPIO_GUMSTIX_ETH1_RST		52
#घोषणा GPIO_GUMSTIX_ETH1_RST_MD	(GPIO_GUMSTIX_ETH1_RST | GPIO_OUT)

#घोषणा GPIO_GUMSTIX_ETH0		36
#घोषणा GPIO_GUMSTIX_ETH0_MD		(GPIO_GUMSTIX_ETH0 | GPIO_IN)
#घोषणा GUMSTIX_ETH0_IRQ		PXA_GPIO_TO_IRQ(GPIO_GUMSTIX_ETH0)
#घोषणा GPIO_GUMSTIX_ETH1		27
#घोषणा GPIO_GUMSTIX_ETH1_MD		(GPIO_GUMSTIX_ETH1 | GPIO_IN)
#घोषणा GUMSTIX_ETH1_IRQ		PXA_GPIO_TO_IRQ(GPIO_GUMSTIX_ETH1)


/* CF reset line */
#घोषणा GPIO8_RESET			8

/* CF slot 0 */
#घोषणा GPIO4_nBVD1			4
#घोषणा GPIO4_nSTSCHG			GPIO4_nBVD1
#घोषणा GPIO11_nCD			11
#घोषणा GPIO26_PRDY_nBSY		26
#घोषणा GUMSTIX_S0_nSTSCHG_IRQ		PXA_GPIO_TO_IRQ(GPIO4_nSTSCHG)
#घोषणा GUMSTIX_S0_nCD_IRQ		PXA_GPIO_TO_IRQ(GPIO11_nCD)
#घोषणा GUMSTIX_S0_PRDY_nBSY_IRQ	PXA_GPIO_TO_IRQ(GPIO26_PRDY_nBSY)

/* CF slot 1 */
#घोषणा GPIO18_nBVD1			18
#घोषणा GPIO18_nSTSCHG			GPIO18_nBVD1
#घोषणा GPIO36_nCD			36
#घोषणा GPIO27_PRDY_nBSY		27
#घोषणा GUMSTIX_S1_nSTSCHG_IRQ		PXA_GPIO_TO_IRQ(GPIO18_nSTSCHG)
#घोषणा GUMSTIX_S1_nCD_IRQ		PXA_GPIO_TO_IRQ(GPIO36_nCD)
#घोषणा GUMSTIX_S1_PRDY_nBSY_IRQ	PXA_GPIO_TO_IRQ(GPIO27_PRDY_nBSY)

/* CF GPIO line modes */
#घोषणा GPIO4_nSTSCHG_MD		(GPIO4_nSTSCHG | GPIO_IN)
#घोषणा GPIO8_RESET_MD			(GPIO8_RESET | GPIO_OUT)
#घोषणा GPIO11_nCD_MD			(GPIO11_nCD | GPIO_IN)
#घोषणा GPIO18_nSTSCHG_MD		(GPIO18_nSTSCHG | GPIO_IN)
#घोषणा GPIO26_PRDY_nBSY_MD		(GPIO26_PRDY_nBSY | GPIO_IN)
#घोषणा GPIO27_PRDY_nBSY_MD		(GPIO27_PRDY_nBSY | GPIO_IN)
#घोषणा GPIO36_nCD_MD			(GPIO36_nCD | GPIO_IN)

/* क्रम expansion boards that can't be programatically detected */
बाह्य पूर्णांक am200_init(व्योम);
बाह्य पूर्णांक am300_init(व्योम);

