<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Platक्रमm level USB initialization क्रम FS USB OTG controller on omap1
 *
 * Copyright (C) 2004 Texas Instruments, Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dma-map-ops.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/irq.h>

#समावेश <mach/mux.h>

#समावेश <mach/usb.h>

#समावेश "common.h"

/* These routines should handle the standard chip-specअगरic modes
 * क्रम usb0/1/2 ports, covering basic mux and transceiver setup.
 *
 * Some board-*.c files will need to set up additional mux options,
 * like क्रम suspend handling, vbus sensing, GPIOs, and the D+ pullup.
 */

/* TESTED ON:
 *  - 1611B H2 (with usb1 mini-AB) using standard Mini-B or OTG cables
 *  - 5912 OSK OHCI (with usb0 standard-A), standard A-to-B cables
 *  - 5912 OSK UDC, with *nonstandard* A-to-A cable
 *  - 1510 Innovator UDC with bundled usb0 cable
 *  - 1510 Innovator OHCI with bundled usb1/usb2 cable
 *  - 1510 Innovator OHCI with custom usb0 cable, feeding 5V VBUS
 *  - 1710 custom development board using alternate pin group
 *  - 1710 H3 (with usb1 mini-AB) using standard Mini-B or OTG cables
 */

#घोषणा INT_USB_IRQ_GEN		IH2_BASE + 20
#घोषणा INT_USB_IRQ_NISO	IH2_BASE + 30
#घोषणा INT_USB_IRQ_ISO		IH2_BASE + 29
#घोषणा INT_USB_IRQ_HGEN	INT_USB_HHC_1
#घोषणा INT_USB_IRQ_OTG		IH2_BASE + 8

#अगर_घोषित	CONFIG_ARCH_OMAP_OTG

अटल व्योम __init
omap_otg_init(काष्ठा omap_usb_config *config)
अणु
	u32		syscon;
	पूर्णांक		alt_pingroup = 0;
	u16		w;

	/* NOTE:  no bus or घड़ी setup (yet?) */

	syscon = omap_पढ़ोl(OTG_SYSCON_1) & 0xffff;
	अगर (!(syscon & OTG_RESET_DONE))
		pr_debug("USB resets not complete?\n");

	//omap_ग_लिखोw(0, OTG_IRQ_EN);

	/* pin muxing and transceiver pinouts */
	अगर (config->pins[0] > 2)	/* alt pingroup 2 */
		alt_pingroup = 1;
	syscon |= config->usb0_init(config->pins[0], is_usb0_device(config));
	syscon |= config->usb1_init(config->pins[1]);
	syscon |= config->usb2_init(config->pins[2], alt_pingroup);
	pr_debug("OTG_SYSCON_1 = %08x\n", omap_पढ़ोl(OTG_SYSCON_1));
	omap_ग_लिखोl(syscon, OTG_SYSCON_1);

	syscon = config->hmc_mode;
	syscon |= USBX_SYNCHRO | (4 << 16) /* B_ASE0_BRST */;
#अगर_घोषित	CONFIG_USB_OTG
	अगर (config->otg)
		syscon |= OTG_EN;
#पूर्ण_अगर
	pr_debug("USB_TRANSCEIVER_CTRL = %03x\n",
		 omap_पढ़ोl(USB_TRANSCEIVER_CTRL));
	pr_debug("OTG_SYSCON_2 = %08x\n", omap_पढ़ोl(OTG_SYSCON_2));
	omap_ग_लिखोl(syscon, OTG_SYSCON_2);

	prपूर्णांकk("USB: hmc %d", config->hmc_mode);
	अगर (!alt_pingroup)
		pr_cont(", usb2 alt %d wires", config->pins[2]);
	अन्यथा अगर (config->pins[0])
		pr_cont(", usb0 %d wires%s", config->pins[0],
			is_usb0_device(config) ? " (dev)" : "");
	अगर (config->pins[1])
		pr_cont(", usb1 %d wires", config->pins[1]);
	अगर (!alt_pingroup && config->pins[2])
		pr_cont(", usb2 %d wires", config->pins[2]);
	अगर (config->otg)
		pr_cont(", Mini-AB on usb%d", config->otg - 1);
	pr_cont("\n");

	/* leave USB घड़ीs/controllers off until needed */
	w = omap_पढ़ोw(ULPD_SOFT_REQ);
	w &= ~SOFT_USB_CLK_REQ;
	omap_ग_लिखोw(w, ULPD_SOFT_REQ);

	w = omap_पढ़ोw(ULPD_CLOCK_CTRL);
	w &= ~USB_MCLK_EN;
	w |= DIS_USB_PVCI_CLK;
	omap_ग_लिखोw(w, ULPD_CLOCK_CTRL);

	syscon = omap_पढ़ोl(OTG_SYSCON_1);
	syscon |= HST_IDLE_EN|DEV_IDLE_EN|OTG_IDLE_EN;

#अगर IS_ENABLED(CONFIG_USB_OMAP)
	अगर (config->otg || config->रेजिस्टर_dev) अणु
		काष्ठा platक्रमm_device *udc_device = config->udc_device;
		पूर्णांक status;

		syscon &= ~DEV_IDLE_EN;
		udc_device->dev.platक्रमm_data = config;
		status = platक्रमm_device_रेजिस्टर(udc_device);
		अगर (status)
			pr_debug("can't register UDC device, %d\n", status);
	पूर्ण
#पूर्ण_अगर

#अगर	IS_ENABLED(CONFIG_USB_OHCI_HCD)
	अगर (config->otg || config->रेजिस्टर_host) अणु
		काष्ठा platक्रमm_device *ohci_device = config->ohci_device;
		पूर्णांक status;

		syscon &= ~HST_IDLE_EN;
		ohci_device->dev.platक्रमm_data = config;
		status = platक्रमm_device_रेजिस्टर(ohci_device);
		अगर (status)
			pr_debug("can't register OHCI device, %d\n", status);
	पूर्ण
#पूर्ण_अगर

#अगर_घोषित	CONFIG_USB_OTG
	अगर (config->otg) अणु
		काष्ठा platक्रमm_device *otg_device = config->otg_device;
		पूर्णांक status;

		syscon &= ~OTG_IDLE_EN;
		otg_device->dev.platक्रमm_data = config;
		status = platक्रमm_device_रेजिस्टर(otg_device);
		अगर (status)
			pr_debug("can't register OTG device, %d\n", status);
	पूर्ण
#पूर्ण_अगर
	pr_debug("OTG_SYSCON_1 = %08x\n", omap_पढ़ोl(OTG_SYSCON_1));
	omap_ग_लिखोl(syscon, OTG_SYSCON_1);
पूर्ण

#अन्यथा
अटल व्योम omap_otg_init(काष्ठा omap_usb_config *config) अणुपूर्ण
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_USB_OMAP)

अटल काष्ठा resource udc_resources[] = अणु
	/* order is signअगरicant! */
	अणु		/* रेजिस्टरs */
		.start		= UDC_BASE,
		.end		= UDC_BASE + 0xff,
		.flags		= IORESOURCE_MEM,
	पूर्ण, अणु		/* general IRQ */
		.start		= INT_USB_IRQ_GEN,
		.flags		= IORESOURCE_IRQ,
	पूर्ण, अणु		/* PIO IRQ */
		.start		= INT_USB_IRQ_NISO,
		.flags		= IORESOURCE_IRQ,
	पूर्ण, अणु		/* SOF IRQ */
		.start		= INT_USB_IRQ_ISO,
		.flags		= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल u64 udc_dmamask = ~(u32)0;

अटल काष्ठा platक्रमm_device udc_device = अणु
	.name		= "omap_udc",
	.id		= -1,
	.dev = अणु
		.dma_mask		= &udc_dmamask,
		.coherent_dma_mask	= 0xffffffff,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(udc_resources),
	.resource	= udc_resources,
पूर्ण;

अटल अंतरभूत व्योम udc_device_init(काष्ठा omap_usb_config *pdata)
अणु
	/* IRQ numbers क्रम omap7xx */
	अगर(cpu_is_omap7xx()) अणु
		udc_resources[1].start = INT_7XX_USB_GENI;
		udc_resources[2].start = INT_7XX_USB_NON_ISO;
		udc_resources[3].start = INT_7XX_USB_ISO;
	पूर्ण
	pdata->udc_device = &udc_device;
पूर्ण

#अन्यथा

अटल अंतरभूत व्योम udc_device_init(काष्ठा omap_usb_config *pdata)
अणु
पूर्ण

#पूर्ण_अगर

#अगर	IS_ENABLED(CONFIG_USB_OHCI_HCD)

/* The dmamask must be set क्रम OHCI to work */
अटल u64 ohci_dmamask = ~(u32)0;

अटल काष्ठा resource ohci_resources[] = अणु
	अणु
		.start	= OMAP_OHCI_BASE,
		.end	= OMAP_OHCI_BASE + 0xff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= INT_USB_IRQ_HGEN,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device ohci_device = अणु
	.name			= "ohci",
	.id			= -1,
	.dev = अणु
		.dma_mask		= &ohci_dmamask,
		.coherent_dma_mask	= 0xffffffff,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(ohci_resources),
	.resource		= ohci_resources,
पूर्ण;

अटल अंतरभूत व्योम ohci_device_init(काष्ठा omap_usb_config *pdata)
अणु
	अगर (cpu_is_omap7xx())
		ohci_resources[1].start = INT_7XX_USB_HHC_1;
	pdata->ohci_device = &ohci_device;
	pdata->ocpi_enable = &ocpi_enable;
पूर्ण

#अन्यथा

अटल अंतरभूत व्योम ohci_device_init(काष्ठा omap_usb_config *pdata)
अणु
पूर्ण

#पूर्ण_अगर

#अगर	defined(CONFIG_USB_OTG) && defined(CONFIG_ARCH_OMAP_OTG)

अटल काष्ठा resource otg_resources[] = अणु
	/* order is signअगरicant! */
	अणु
		.start		= OTG_BASE,
		.end		= OTG_BASE + 0xff,
		.flags		= IORESOURCE_MEM,
	पूर्ण, अणु
		.start		= INT_USB_IRQ_OTG,
		.flags		= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device otg_device = अणु
	.name		= "omap_otg",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(otg_resources),
	.resource	= otg_resources,
पूर्ण;

अटल अंतरभूत व्योम otg_device_init(काष्ठा omap_usb_config *pdata)
अणु
	अगर (cpu_is_omap7xx())
		otg_resources[1].start = INT_7XX_USB_OTG;
	pdata->otg_device = &otg_device;
पूर्ण

#अन्यथा

अटल अंतरभूत व्योम otg_device_init(काष्ठा omap_usb_config *pdata)
अणु
पूर्ण

#पूर्ण_अगर

अटल u32 __init omap1_usb0_init(अचिन्हित nwires, अचिन्हित is_device)
अणु
	u32	syscon1 = 0;

	अगर (nwires == 0) अणु
		अगर (!cpu_is_omap15xx()) अणु
			u32 l;

			/* pullकरोwn D+/D- */
			l = omap_पढ़ोl(USB_TRANSCEIVER_CTRL);
			l &= ~(3 << 1);
			omap_ग_लिखोl(l, USB_TRANSCEIVER_CTRL);
		पूर्ण
		वापस 0;
	पूर्ण

	अगर (is_device) अणु
		अगर (cpu_is_omap7xx()) अणु
			omap_cfg_reg(AA17_7XX_USB_DM);
			omap_cfg_reg(W16_7XX_USB_PU_EN);
			omap_cfg_reg(W17_7XX_USB_VBUSI);
			omap_cfg_reg(W18_7XX_USB_DMCK_OUT);
			omap_cfg_reg(W19_7XX_USB_DCRST);
		पूर्ण अन्यथा
			omap_cfg_reg(W4_USB_PUEN);
	पूर्ण

	अगर (nwires == 2) अणु
		u32 l;

		// omap_cfg_reg(P9_USB_DP);
		// omap_cfg_reg(R8_USB_DM);

		अगर (cpu_is_omap15xx()) अणु
			/* This works on 1510-Innovator */
			वापस 0;
		पूर्ण

		/* NOTES:
		 *  - peripheral should configure VBUS detection!
		 *  - only peripherals may use the पूर्णांकernal D+/D- pullकरोwns
		 *  - OTG support on this port not yet written
		 */

		/* Don't करो this क्रम omap7xx -- it causes USB to not work correctly */
		अगर (!cpu_is_omap7xx()) अणु
			l = omap_पढ़ोl(USB_TRANSCEIVER_CTRL);
			l &= ~(7 << 4);
			अगर (!is_device)
				l |= (3 << 1);
			omap_ग_लिखोl(l, USB_TRANSCEIVER_CTRL);
		पूर्ण

		वापस 3 << 16;
	पूर्ण

	/* alternate pin config, बाह्यal transceiver */
	अगर (cpu_is_omap15xx()) अणु
		prपूर्णांकk(KERN_ERR "no usb0 alt pin config on 15xx\n");
		वापस 0;
	पूर्ण

	omap_cfg_reg(V6_USB0_TXD);
	omap_cfg_reg(W9_USB0_TXEN);
	omap_cfg_reg(W5_USB0_SE0);
	अगर (nwires != 3)
		omap_cfg_reg(Y5_USB0_RCV);

	/* NOTE:  SPEED and SUSP aren't configured here.  OTG hosts
	 * may be able to use I2C requests to set those bits aदीर्घ
	 * with VBUS चयनing and overcurrent detection.
	 */

	अगर (nwires != 6) अणु
		u32 l;

		l = omap_पढ़ोl(USB_TRANSCEIVER_CTRL);
		l &= ~CONF_USB2_UNI_R;
		omap_ग_लिखोl(l, USB_TRANSCEIVER_CTRL);
	पूर्ण

	चयन (nwires) अणु
	हाल 3:
		syscon1 = 2;
		अवरोध;
	हाल 4:
		syscon1 = 1;
		अवरोध;
	हाल 6:
		syscon1 = 3;
		अणु
			u32 l;

			omap_cfg_reg(AA9_USB0_VP);
			omap_cfg_reg(R9_USB0_VM);
			l = omap_पढ़ोl(USB_TRANSCEIVER_CTRL);
			l |= CONF_USB2_UNI_R;
			omap_ग_लिखोl(l, USB_TRANSCEIVER_CTRL);
		पूर्ण
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "illegal usb%d %d-wire transceiver\n",
			0, nwires);
	पूर्ण

	वापस syscon1 << 16;
पूर्ण

अटल u32 __init omap1_usb1_init(अचिन्हित nwires)
अणु
	u32	syscon1 = 0;

	अगर (!cpu_is_omap15xx() && nwires != 6) अणु
		u32 l;

		l = omap_पढ़ोl(USB_TRANSCEIVER_CTRL);
		l &= ~CONF_USB1_UNI_R;
		omap_ग_लिखोl(l, USB_TRANSCEIVER_CTRL);
	पूर्ण
	अगर (nwires == 0)
		वापस 0;

	/* बाह्यal transceiver */
	omap_cfg_reg(USB1_TXD);
	omap_cfg_reg(USB1_TXEN);
	अगर (nwires != 3)
		omap_cfg_reg(USB1_RCV);

	अगर (cpu_is_omap15xx()) अणु
		omap_cfg_reg(USB1_SEO);
		omap_cfg_reg(USB1_SPEED);
		// SUSP
	पूर्ण अन्यथा अगर (cpu_is_omap1610() || cpu_is_omap5912()) अणु
		omap_cfg_reg(W13_1610_USB1_SE0);
		omap_cfg_reg(R13_1610_USB1_SPEED);
		// SUSP
	पूर्ण अन्यथा अगर (cpu_is_omap1710()) अणु
		omap_cfg_reg(R13_1710_USB1_SE0);
		// SUSP
	पूर्ण अन्यथा अणु
		pr_debug("usb%d cpu unrecognized\n", 1);
		वापस 0;
	पूर्ण

	चयन (nwires) अणु
	हाल 2:
		जाओ bad;
	हाल 3:
		syscon1 = 2;
		अवरोध;
	हाल 4:
		syscon1 = 1;
		अवरोध;
	हाल 6:
		syscon1 = 3;
		omap_cfg_reg(USB1_VP);
		omap_cfg_reg(USB1_VM);
		अगर (!cpu_is_omap15xx()) अणु
			u32 l;

			l = omap_पढ़ोl(USB_TRANSCEIVER_CTRL);
			l |= CONF_USB1_UNI_R;
			omap_ग_लिखोl(l, USB_TRANSCEIVER_CTRL);
		पूर्ण
		अवरोध;
	शेष:
bad:
		prपूर्णांकk(KERN_ERR "illegal usb%d %d-wire transceiver\n",
			1, nwires);
	पूर्ण

	वापस syscon1 << 20;
पूर्ण

अटल u32 __init omap1_usb2_init(अचिन्हित nwires, अचिन्हित alt_pingroup)
अणु
	u32	syscon1 = 0;

	/* NOTE omap1 erratum: must leave USB2_UNI_R set अगर usb0 in use */
	अगर (alt_pingroup || nwires == 0)
		वापस 0;

	अगर (!cpu_is_omap15xx() && nwires != 6) अणु
		u32 l;

		l = omap_पढ़ोl(USB_TRANSCEIVER_CTRL);
		l &= ~CONF_USB2_UNI_R;
		omap_ग_लिखोl(l, USB_TRANSCEIVER_CTRL);
	पूर्ण

	/* बाह्यal transceiver */
	अगर (cpu_is_omap15xx()) अणु
		omap_cfg_reg(USB2_TXD);
		omap_cfg_reg(USB2_TXEN);
		omap_cfg_reg(USB2_SEO);
		अगर (nwires != 3)
			omap_cfg_reg(USB2_RCV);
		/* there is no USB2_SPEED */
	पूर्ण अन्यथा अगर (cpu_is_omap16xx()) अणु
		omap_cfg_reg(V6_USB2_TXD);
		omap_cfg_reg(W9_USB2_TXEN);
		omap_cfg_reg(W5_USB2_SE0);
		अगर (nwires != 3)
			omap_cfg_reg(Y5_USB2_RCV);
		// FIXME omap_cfg_reg(USB2_SPEED);
	पूर्ण अन्यथा अणु
		pr_debug("usb%d cpu unrecognized\n", 1);
		वापस 0;
	पूर्ण

	// omap_cfg_reg(USB2_SUSP);

	चयन (nwires) अणु
	हाल 2:
		जाओ bad;
	हाल 3:
		syscon1 = 2;
		अवरोध;
	हाल 4:
		syscon1 = 1;
		अवरोध;
	हाल 5:
		जाओ bad;
	हाल 6:
		syscon1 = 3;
		अगर (cpu_is_omap15xx()) अणु
			omap_cfg_reg(USB2_VP);
			omap_cfg_reg(USB2_VM);
		पूर्ण अन्यथा अणु
			u32 l;

			omap_cfg_reg(AA9_USB2_VP);
			omap_cfg_reg(R9_USB2_VM);
			l = omap_पढ़ोl(USB_TRANSCEIVER_CTRL);
			l |= CONF_USB2_UNI_R;
			omap_ग_लिखोl(l, USB_TRANSCEIVER_CTRL);
		पूर्ण
		अवरोध;
	शेष:
bad:
		prपूर्णांकk(KERN_ERR "illegal usb%d %d-wire transceiver\n",
			2, nwires);
	पूर्ण

	वापस syscon1 << 24;
पूर्ण

#अगर_घोषित	CONFIG_ARCH_OMAP15XX

/* ULPD_DPLL_CTRL */
#घोषणा DPLL_IOB		(1 << 13)
#घोषणा DPLL_PLL_ENABLE		(1 << 4)
#घोषणा DPLL_LOCK		(1 << 0)

/* ULPD_APLL_CTRL */
#घोषणा APLL_NDPLL_SWITCH	(1 << 0)

अटल पूर्णांक omap_1510_usb_ohci_notअगरier(काष्ठा notअगरier_block *nb,
		अचिन्हित दीर्घ event, व्योम *data)
अणु
	काष्ठा device *dev = data;

	अगर (event != BUS_NOTIFY_ADD_DEVICE)
		वापस NOTIFY_DONE;

	अगर (म_भेदन(dev_name(dev), "ohci", 4) == 0 &&
	    dma_direct_set_offset(dev, PHYS_OFFSET, OMAP1510_LB_OFFSET,
			(u64)-1))
		WARN_ONCE(1, "failed to set DMA offset\n");
	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block omap_1510_usb_ohci_nb = अणु
	.notअगरier_call		= omap_1510_usb_ohci_notअगरier,
पूर्ण;

अटल व्योम __init omap_1510_usb_init(काष्ठा omap_usb_config *config)
अणु
	अचिन्हित पूर्णांक val;
	u16 w;

	config->usb0_init(config->pins[0], is_usb0_device(config));
	config->usb1_init(config->pins[1]);
	config->usb2_init(config->pins[2], 0);

	val = omap_पढ़ोl(MOD_CONF_CTRL_0) & ~(0x3f << 1);
	val |= (config->hmc_mode << 1);
	omap_ग_लिखोl(val, MOD_CONF_CTRL_0);

	prपूर्णांकk("USB: hmc %d", config->hmc_mode);
	अगर (config->pins[0])
		pr_cont(", usb0 %d wires%s", config->pins[0],
			is_usb0_device(config) ? " (dev)" : "");
	अगर (config->pins[1])
		pr_cont(", usb1 %d wires", config->pins[1]);
	अगर (config->pins[2])
		pr_cont(", usb2 %d wires", config->pins[2]);
	pr_cont("\n");

	/* use DPLL क्रम 48 MHz function घड़ी */
	pr_debug("APLL %04x DPLL %04x REQ %04x\n", omap_पढ़ोw(ULPD_APLL_CTRL),
			omap_पढ़ोw(ULPD_DPLL_CTRL), omap_पढ़ोw(ULPD_SOFT_REQ));

	w = omap_पढ़ोw(ULPD_APLL_CTRL);
	w &= ~APLL_NDPLL_SWITCH;
	omap_ग_लिखोw(w, ULPD_APLL_CTRL);

	w = omap_पढ़ोw(ULPD_DPLL_CTRL);
	w |= DPLL_IOB | DPLL_PLL_ENABLE;
	omap_ग_लिखोw(w, ULPD_DPLL_CTRL);

	w = omap_पढ़ोw(ULPD_SOFT_REQ);
	w |= SOFT_UDC_REQ | SOFT_DPLL_REQ;
	omap_ग_लिखोw(w, ULPD_SOFT_REQ);

	जबतक (!(omap_पढ़ोw(ULPD_DPLL_CTRL) & DPLL_LOCK))
		cpu_relax();

#अगर IS_ENABLED(CONFIG_USB_OMAP)
	अगर (config->रेजिस्टर_dev) अणु
		पूर्णांक status;

		udc_device.dev.platक्रमm_data = config;
		status = platक्रमm_device_रेजिस्टर(&udc_device);
		अगर (status)
			pr_debug("can't register UDC device, %d\n", status);
		/* udc driver gates 48MHz by D+ pullup */
	पूर्ण
#पूर्ण_अगर

#अगर	IS_ENABLED(CONFIG_USB_OHCI_HCD)
	अगर (config->रेजिस्टर_host) अणु
		पूर्णांक status;

		bus_रेजिस्टर_notअगरier(&platक्रमm_bus_type,
				      &omap_1510_usb_ohci_nb);
		ohci_device.dev.platक्रमm_data = config;
		status = platक्रमm_device_रेजिस्टर(&ohci_device);
		अगर (status)
			pr_debug("can't register OHCI device, %d\n", status);
		/* hcd explicitly gates 48MHz */
	पूर्ण
#पूर्ण_अगर
पूर्ण

#अन्यथा
अटल अंतरभूत व्योम omap_1510_usb_init(काष्ठा omap_usb_config *config) अणुपूर्ण
#पूर्ण_अगर

व्योम __init omap1_usb_init(काष्ठा omap_usb_config *_pdata)
अणु
	काष्ठा omap_usb_config *pdata;

	pdata = kmemdup(_pdata, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस;

	pdata->usb0_init = omap1_usb0_init;
	pdata->usb1_init = omap1_usb1_init;
	pdata->usb2_init = omap1_usb2_init;
	udc_device_init(pdata);
	ohci_device_init(pdata);
	otg_device_init(pdata);

	अगर (cpu_is_omap7xx() || cpu_is_omap16xx())
		omap_otg_init(pdata);
	अन्यथा अगर (cpu_is_omap15xx())
		omap_1510_usb_init(pdata);
	अन्यथा
		prपूर्णांकk(KERN_ERR "USB: No init for your chip yet\n");
पूर्ण
