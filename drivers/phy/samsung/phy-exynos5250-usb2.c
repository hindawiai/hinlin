<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Samsung SoC USB 1.1/2.0 PHY driver - Exynos 5250 support
 *
 * Copyright (C) 2013 Samsung Electronics Co., Ltd.
 * Author: Kamil Debski <k.debski@samsung.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/phy/phy.h>
#समावेश <linux/regmap.h>
#समावेश "phy-samsung-usb2.h"

/* Exynos USB PHY रेजिस्टरs */
#घोषणा EXYNOS_5250_REFCLKSEL_CRYSTAL	0x0
#घोषणा EXYNOS_5250_REFCLKSEL_XO	0x1
#घोषणा EXYNOS_5250_REFCLKSEL_CLKCORE	0x2

#घोषणा EXYNOS_5250_FSEL_9MHZ6		0x0
#घोषणा EXYNOS_5250_FSEL_10MHZ		0x1
#घोषणा EXYNOS_5250_FSEL_12MHZ		0x2
#घोषणा EXYNOS_5250_FSEL_19MHZ2		0x3
#घोषणा EXYNOS_5250_FSEL_20MHZ		0x4
#घोषणा EXYNOS_5250_FSEL_24MHZ		0x5
#घोषणा EXYNOS_5250_FSEL_50MHZ		0x7

/* Normal host */
#घोषणा EXYNOS_5250_HOSTPHYCTRL0			0x0

#घोषणा EXYNOS_5250_HOSTPHYCTRL0_PHYSWRSTALL		BIT(31)
#घोषणा EXYNOS_5250_HOSTPHYCTRL0_REFCLKSEL_SHIFT	19
#घोषणा EXYNOS_5250_HOSTPHYCTRL0_REFCLKSEL_MASK	\
		(0x3 << EXYNOS_5250_HOSTPHYCTRL0_REFCLKSEL_SHIFT)
#घोषणा EXYNOS_5250_HOSTPHYCTRL0_FSEL_SHIFT		16
#घोषणा EXYNOS_5250_HOSTPHYCTRL0_FSEL_MASK \
		(0x7 << EXYNOS_5250_HOSTPHYCTRL0_FSEL_SHIFT)
#घोषणा EXYNOS_5250_HOSTPHYCTRL0_TESTBURNIN		BIT(11)
#घोषणा EXYNOS_5250_HOSTPHYCTRL0_RETENABLE		BIT(10)
#घोषणा EXYNOS_5250_HOSTPHYCTRL0_COMMON_ON_N		BIT(9)
#घोषणा EXYNOS_5250_HOSTPHYCTRL0_VATESTENB_MASK		(0x3 << 7)
#घोषणा EXYNOS_5250_HOSTPHYCTRL0_VATESTENB_DUAL		(0x0 << 7)
#घोषणा EXYNOS_5250_HOSTPHYCTRL0_VATESTENB_ID0		(0x1 << 7)
#घोषणा EXYNOS_5250_HOSTPHYCTRL0_VATESTENB_ANALOGTEST	(0x2 << 7)
#घोषणा EXYNOS_5250_HOSTPHYCTRL0_SIDDQ			BIT(6)
#घोषणा EXYNOS_5250_HOSTPHYCTRL0_FORCESLEEP		BIT(5)
#घोषणा EXYNOS_5250_HOSTPHYCTRL0_FORCESUSPEND		BIT(4)
#घोषणा EXYNOS_5250_HOSTPHYCTRL0_WORDINTERFACE		BIT(3)
#घोषणा EXYNOS_5250_HOSTPHYCTRL0_UTMISWRST		BIT(2)
#घोषणा EXYNOS_5250_HOSTPHYCTRL0_LINKSWRST		BIT(1)
#घोषणा EXYNOS_5250_HOSTPHYCTRL0_PHYSWRST		BIT(0)

/* HSIC0 & HSIC1 */
#घोषणा EXYNOS_5250_HSICPHYCTRL1			0x10
#घोषणा EXYNOS_5250_HSICPHYCTRL2			0x20

#घोषणा EXYNOS_5250_HSICPHYCTRLX_REFCLKSEL_MASK		(0x3 << 23)
#घोषणा EXYNOS_5250_HSICPHYCTRLX_REFCLKSEL_DEFAULT	(0x2 << 23)
#घोषणा EXYNOS_5250_HSICPHYCTRLX_REFCLKDIV_MASK		(0x7f << 16)
#घोषणा EXYNOS_5250_HSICPHYCTRLX_REFCLKDIV_12		(0x24 << 16)
#घोषणा EXYNOS_5250_HSICPHYCTRLX_REFCLKDIV_15		(0x1c << 16)
#घोषणा EXYNOS_5250_HSICPHYCTRLX_REFCLKDIV_16		(0x1a << 16)
#घोषणा EXYNOS_5250_HSICPHYCTRLX_REFCLKDIV_19_2		(0x15 << 16)
#घोषणा EXYNOS_5250_HSICPHYCTRLX_REFCLKDIV_20		(0x14 << 16)
#घोषणा EXYNOS_5250_HSICPHYCTRLX_SIDDQ			BIT(6)
#घोषणा EXYNOS_5250_HSICPHYCTRLX_FORCESLEEP		BIT(5)
#घोषणा EXYNOS_5250_HSICPHYCTRLX_FORCESUSPEND		BIT(4)
#घोषणा EXYNOS_5250_HSICPHYCTRLX_WORDINTERFACE		BIT(3)
#घोषणा EXYNOS_5250_HSICPHYCTRLX_UTMISWRST		BIT(2)
#घोषणा EXYNOS_5250_HSICPHYCTRLX_PHYSWRST		BIT(0)

/* EHCI control */
#घोषणा EXYNOS_5250_HOSTEHCICTRL			0x30
#घोषणा EXYNOS_5250_HOSTEHCICTRL_ENAINCRXALIGN		BIT(29)
#घोषणा EXYNOS_5250_HOSTEHCICTRL_ENAINCR4		BIT(28)
#घोषणा EXYNOS_5250_HOSTEHCICTRL_ENAINCR8		BIT(27)
#घोषणा EXYNOS_5250_HOSTEHCICTRL_ENAINCR16		BIT(26)
#घोषणा EXYNOS_5250_HOSTEHCICTRL_AUTOPPDONOVRCUREN	BIT(25)
#घोषणा EXYNOS_5250_HOSTEHCICTRL_FLADJVAL0_SHIFT	19
#घोषणा EXYNOS_5250_HOSTEHCICTRL_FLADJVAL0_MASK	\
		(0x3f << EXYNOS_5250_HOSTEHCICTRL_FLADJVAL0_SHIFT)
#घोषणा EXYNOS_5250_HOSTEHCICTRL_FLADJVAL1_SHIFT	13
#घोषणा EXYNOS_5250_HOSTEHCICTRL_FLADJVAL1_MASK	\
		(0x3f << EXYNOS_5250_HOSTEHCICTRL_FLADJVAL1_SHIFT)
#घोषणा EXYNOS_5250_HOSTEHCICTRL_FLADJVAL2_SHIFT	7
#घोषणा EXYNOS_5250_HOSTEHCICTRL_FLADJVAL0_MASK	\
		(0x3f << EXYNOS_5250_HOSTEHCICTRL_FLADJVAL0_SHIFT)
#घोषणा EXYNOS_5250_HOSTEHCICTRL_FLADJVALHOST_SHIFT	1
#घोषणा EXYNOS_5250_HOSTEHCICTRL_FLADJVALHOST_MASK \
		(0x1 << EXYNOS_5250_HOSTEHCICTRL_FLADJVALHOST_SHIFT)
#घोषणा EXYNOS_5250_HOSTEHCICTRL_SIMULATIONMODE		BIT(0)

/* OHCI control */
#घोषणा EXYNOS_5250_HOSTOHCICTRL                        0x34
#घोषणा EXYNOS_5250_HOSTOHCICTRL_FRAMELENVAL_SHIFT	1
#घोषणा EXYNOS_5250_HOSTOHCICTRL_FRAMELENVAL_MASK \
		(0x3ff << EXYNOS_5250_HOSTOHCICTRL_FRAMELENVAL_SHIFT)
#घोषणा EXYNOS_5250_HOSTOHCICTRL_FRAMELENVALEN		BIT(0)

/* USBOTG */
#घोषणा EXYNOS_5250_USBOTGSYS				0x38
#घोषणा EXYNOS_5250_USBOTGSYS_PHYLINK_SW_RESET		BIT(14)
#घोषणा EXYNOS_5250_USBOTGSYS_LINK_SW_RST_UOTG		BIT(13)
#घोषणा EXYNOS_5250_USBOTGSYS_PHY_SW_RST		BIT(12)
#घोषणा EXYNOS_5250_USBOTGSYS_REFCLKSEL_SHIFT		9
#घोषणा EXYNOS_5250_USBOTGSYS_REFCLKSEL_MASK \
		(0x3 << EXYNOS_5250_USBOTGSYS_REFCLKSEL_SHIFT)
#घोषणा EXYNOS_5250_USBOTGSYS_ID_PULLUP			BIT(8)
#घोषणा EXYNOS_5250_USBOTGSYS_COMMON_ON			BIT(7)
#घोषणा EXYNOS_5250_USBOTGSYS_FSEL_SHIFT		4
#घोषणा EXYNOS_5250_USBOTGSYS_FSEL_MASK \
		(0x3 << EXYNOS_5250_USBOTGSYS_FSEL_SHIFT)
#घोषणा EXYNOS_5250_USBOTGSYS_FORCE_SLEEP		BIT(3)
#घोषणा EXYNOS_5250_USBOTGSYS_OTGDISABLE		BIT(2)
#घोषणा EXYNOS_5250_USBOTGSYS_SIDDQ_UOTG		BIT(1)
#घोषणा EXYNOS_5250_USBOTGSYS_FORCE_SUSPEND		BIT(0)

/* Isolation, configured in the घातer management unit */
#घोषणा EXYNOS_5250_USB_ISOL_OTG_OFFSET		0x704
#घोषणा EXYNOS_5250_USB_ISOL_HOST_OFFSET	0x708
#घोषणा EXYNOS_5420_USB_ISOL_HOST_OFFSET	0x70C
#घोषणा EXYNOS_5250_USB_ISOL_ENABLE		BIT(0)

/* Mode swtich रेजिस्टर */
#घोषणा EXYNOS_5250_MODE_SWITCH_OFFSET		0x230
#घोषणा EXYNOS_5250_MODE_SWITCH_MASK		1
#घोषणा EXYNOS_5250_MODE_SWITCH_DEVICE		0
#घोषणा EXYNOS_5250_MODE_SWITCH_HOST		1

क्रमागत exynos4x12_phy_id अणु
	EXYNOS5250_DEVICE,
	EXYNOS5250_HOST,
	EXYNOS5250_HSIC0,
	EXYNOS5250_HSIC1,
पूर्ण;

/*
 * exynos5250_rate_to_clk() converts the supplied घड़ी rate to the value that
 * can be written to the phy रेजिस्टर.
 */
अटल पूर्णांक exynos5250_rate_to_clk(अचिन्हित दीर्घ rate, u32 *reg)
अणु
	/* EXYNOS_5250_FSEL_MASK */

	चयन (rate) अणु
	हाल 9600 * KHZ:
		*reg = EXYNOS_5250_FSEL_9MHZ6;
		अवरोध;
	हाल 10 * MHZ:
		*reg = EXYNOS_5250_FSEL_10MHZ;
		अवरोध;
	हाल 12 * MHZ:
		*reg = EXYNOS_5250_FSEL_12MHZ;
		अवरोध;
	हाल 19200 * KHZ:
		*reg = EXYNOS_5250_FSEL_19MHZ2;
		अवरोध;
	हाल 20 * MHZ:
		*reg = EXYNOS_5250_FSEL_20MHZ;
		अवरोध;
	हाल 24 * MHZ:
		*reg = EXYNOS_5250_FSEL_24MHZ;
		अवरोध;
	हाल 50 * MHZ:
		*reg = EXYNOS_5250_FSEL_50MHZ;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम exynos5250_isol(काष्ठा samsung_usb2_phy_instance *inst, bool on)
अणु
	काष्ठा samsung_usb2_phy_driver *drv = inst->drv;
	u32 offset;
	u32 mask = EXYNOS_5250_USB_ISOL_ENABLE;

	अगर (drv->cfg == &exynos5250_usb2_phy_config &&
	    inst->cfg->id == EXYNOS5250_DEVICE)
		offset = EXYNOS_5250_USB_ISOL_OTG_OFFSET;
	अन्यथा अगर (drv->cfg == &exynos5250_usb2_phy_config &&
		 inst->cfg->id == EXYNOS5250_HOST)
		offset = EXYNOS_5250_USB_ISOL_HOST_OFFSET;
	अन्यथा अगर (drv->cfg == &exynos5420_usb2_phy_config &&
		 inst->cfg->id == EXYNOS5250_HOST)
		offset = EXYNOS_5420_USB_ISOL_HOST_OFFSET;
	अन्यथा
		वापस;

	regmap_update_bits(drv->reg_pmu, offset, mask, on ? 0 : mask);
पूर्ण

अटल पूर्णांक exynos5250_घातer_on(काष्ठा samsung_usb2_phy_instance *inst)
अणु
	काष्ठा samsung_usb2_phy_driver *drv = inst->drv;
	u32 ctrl0;
	u32 otg;
	u32 ehci;
	u32 ohci;
	u32 hsic;

	चयन (inst->cfg->id) अणु
	हाल EXYNOS5250_DEVICE:
		regmap_update_bits(drv->reg_sys,
				   EXYNOS_5250_MODE_SWITCH_OFFSET,
				   EXYNOS_5250_MODE_SWITCH_MASK,
				   EXYNOS_5250_MODE_SWITCH_DEVICE);

		/* OTG configuration */
		otg = पढ़ोl(drv->reg_phy + EXYNOS_5250_USBOTGSYS);
		/* The घड़ी */
		otg &= ~EXYNOS_5250_USBOTGSYS_FSEL_MASK;
		otg |= drv->ref_reg_val << EXYNOS_5250_USBOTGSYS_FSEL_SHIFT;
		/* Reset */
		otg &= ~(EXYNOS_5250_USBOTGSYS_FORCE_SUSPEND |
			EXYNOS_5250_USBOTGSYS_FORCE_SLEEP |
			EXYNOS_5250_USBOTGSYS_SIDDQ_UOTG);
		otg |=	EXYNOS_5250_USBOTGSYS_PHY_SW_RST |
			EXYNOS_5250_USBOTGSYS_PHYLINK_SW_RESET |
			EXYNOS_5250_USBOTGSYS_LINK_SW_RST_UOTG |
			EXYNOS_5250_USBOTGSYS_OTGDISABLE;
		/* Ref घड़ी */
		otg &=	~EXYNOS_5250_USBOTGSYS_REFCLKSEL_MASK;
		otg |=  EXYNOS_5250_REFCLKSEL_CLKCORE <<
					EXYNOS_5250_USBOTGSYS_REFCLKSEL_SHIFT;
		ग_लिखोl(otg, drv->reg_phy + EXYNOS_5250_USBOTGSYS);
		udelay(100);
		otg &= ~(EXYNOS_5250_USBOTGSYS_PHY_SW_RST |
			EXYNOS_5250_USBOTGSYS_LINK_SW_RST_UOTG |
			EXYNOS_5250_USBOTGSYS_PHYLINK_SW_RESET |
			EXYNOS_5250_USBOTGSYS_OTGDISABLE);
		ग_लिखोl(otg, drv->reg_phy + EXYNOS_5250_USBOTGSYS);


		अवरोध;
	हाल EXYNOS5250_HOST:
	हाल EXYNOS5250_HSIC0:
	हाल EXYNOS5250_HSIC1:
		/* Host रेजिस्टरs configuration */
		ctrl0 = पढ़ोl(drv->reg_phy + EXYNOS_5250_HOSTPHYCTRL0);
		/* The घड़ी */
		ctrl0 &= ~EXYNOS_5250_HOSTPHYCTRL0_FSEL_MASK;
		ctrl0 |= drv->ref_reg_val <<
					EXYNOS_5250_HOSTPHYCTRL0_FSEL_SHIFT;

		/* Reset */
		ctrl0 &=	~(EXYNOS_5250_HOSTPHYCTRL0_PHYSWRST |
				EXYNOS_5250_HOSTPHYCTRL0_PHYSWRSTALL |
				EXYNOS_5250_HOSTPHYCTRL0_SIDDQ |
				EXYNOS_5250_HOSTPHYCTRL0_FORCESUSPEND |
				EXYNOS_5250_HOSTPHYCTRL0_FORCESLEEP);
		ctrl0 |=	EXYNOS_5250_HOSTPHYCTRL0_LINKSWRST |
				EXYNOS_5250_HOSTPHYCTRL0_UTMISWRST |
				EXYNOS_5250_HOSTPHYCTRL0_COMMON_ON_N;
		ग_लिखोl(ctrl0, drv->reg_phy + EXYNOS_5250_HOSTPHYCTRL0);
		udelay(10);
		ctrl0 &=	~(EXYNOS_5250_HOSTPHYCTRL0_LINKSWRST |
				EXYNOS_5250_HOSTPHYCTRL0_UTMISWRST);
		ग_लिखोl(ctrl0, drv->reg_phy + EXYNOS_5250_HOSTPHYCTRL0);

		/* OTG configuration */
		otg = पढ़ोl(drv->reg_phy + EXYNOS_5250_USBOTGSYS);
		/* The घड़ी */
		otg &= ~EXYNOS_5250_USBOTGSYS_FSEL_MASK;
		otg |= drv->ref_reg_val << EXYNOS_5250_USBOTGSYS_FSEL_SHIFT;
		/* Reset */
		otg &= ~(EXYNOS_5250_USBOTGSYS_FORCE_SUSPEND |
			EXYNOS_5250_USBOTGSYS_FORCE_SLEEP |
			EXYNOS_5250_USBOTGSYS_SIDDQ_UOTG);
		otg |=	EXYNOS_5250_USBOTGSYS_PHY_SW_RST |
			EXYNOS_5250_USBOTGSYS_PHYLINK_SW_RESET |
			EXYNOS_5250_USBOTGSYS_LINK_SW_RST_UOTG |
			EXYNOS_5250_USBOTGSYS_OTGDISABLE;
		/* Ref घड़ी */
		otg &=	~EXYNOS_5250_USBOTGSYS_REFCLKSEL_MASK;
		otg |=  EXYNOS_5250_REFCLKSEL_CLKCORE <<
					EXYNOS_5250_USBOTGSYS_REFCLKSEL_SHIFT;
		ग_लिखोl(otg, drv->reg_phy + EXYNOS_5250_USBOTGSYS);
		udelay(10);
		otg &= ~(EXYNOS_5250_USBOTGSYS_PHY_SW_RST |
			EXYNOS_5250_USBOTGSYS_LINK_SW_RST_UOTG |
			EXYNOS_5250_USBOTGSYS_PHYLINK_SW_RESET);

		/* HSIC phy configuration */
		hsic = (EXYNOS_5250_HSICPHYCTRLX_REFCLKDIV_12 |
				EXYNOS_5250_HSICPHYCTRLX_REFCLKSEL_DEFAULT |
				EXYNOS_5250_HSICPHYCTRLX_PHYSWRST);
		ग_लिखोl(hsic, drv->reg_phy + EXYNOS_5250_HSICPHYCTRL1);
		ग_लिखोl(hsic, drv->reg_phy + EXYNOS_5250_HSICPHYCTRL2);
		udelay(10);
		hsic &= ~EXYNOS_5250_HSICPHYCTRLX_PHYSWRST;
		ग_लिखोl(hsic, drv->reg_phy + EXYNOS_5250_HSICPHYCTRL1);
		ग_लिखोl(hsic, drv->reg_phy + EXYNOS_5250_HSICPHYCTRL2);
		/* The following delay is necessary क्रम the reset sequence to be
		 * completed */
		udelay(80);

		/* Enable EHCI DMA burst */
		ehci = पढ़ोl(drv->reg_phy + EXYNOS_5250_HOSTEHCICTRL);
		ehci |=	EXYNOS_5250_HOSTEHCICTRL_ENAINCRXALIGN |
			EXYNOS_5250_HOSTEHCICTRL_ENAINCR4 |
			EXYNOS_5250_HOSTEHCICTRL_ENAINCR8 |
			EXYNOS_5250_HOSTEHCICTRL_ENAINCR16;
		ग_लिखोl(ehci, drv->reg_phy + EXYNOS_5250_HOSTEHCICTRL);

		/* OHCI settings */
		ohci = पढ़ोl(drv->reg_phy + EXYNOS_5250_HOSTOHCICTRL);
		/* Following code is based on the old driver */
		ohci |=	0x1 << 3;
		ग_लिखोl(ohci, drv->reg_phy + EXYNOS_5250_HOSTOHCICTRL);

		अवरोध;
	पूर्ण
	exynos5250_isol(inst, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक exynos5250_घातer_off(काष्ठा samsung_usb2_phy_instance *inst)
अणु
	काष्ठा samsung_usb2_phy_driver *drv = inst->drv;
	u32 ctrl0;
	u32 otg;
	u32 hsic;

	exynos5250_isol(inst, 1);

	चयन (inst->cfg->id) अणु
	हाल EXYNOS5250_DEVICE:
		otg = पढ़ोl(drv->reg_phy + EXYNOS_5250_USBOTGSYS);
		otg |= (EXYNOS_5250_USBOTGSYS_FORCE_SUSPEND |
			EXYNOS_5250_USBOTGSYS_SIDDQ_UOTG |
			EXYNOS_5250_USBOTGSYS_FORCE_SLEEP);
		ग_लिखोl(otg, drv->reg_phy + EXYNOS_5250_USBOTGSYS);
		अवरोध;
	हाल EXYNOS5250_HOST:
		ctrl0 = पढ़ोl(drv->reg_phy + EXYNOS_5250_HOSTPHYCTRL0);
		ctrl0 |= (EXYNOS_5250_HOSTPHYCTRL0_SIDDQ |
				EXYNOS_5250_HOSTPHYCTRL0_FORCESUSPEND |
				EXYNOS_5250_HOSTPHYCTRL0_FORCESLEEP |
				EXYNOS_5250_HOSTPHYCTRL0_PHYSWRST |
				EXYNOS_5250_HOSTPHYCTRL0_PHYSWRSTALL);
		ग_लिखोl(ctrl0, drv->reg_phy + EXYNOS_5250_HOSTPHYCTRL0);
		अवरोध;
	हाल EXYNOS5250_HSIC0:
	हाल EXYNOS5250_HSIC1:
		hsic = (EXYNOS_5250_HSICPHYCTRLX_REFCLKDIV_12 |
				EXYNOS_5250_HSICPHYCTRLX_REFCLKSEL_DEFAULT |
				EXYNOS_5250_HSICPHYCTRLX_SIDDQ |
				EXYNOS_5250_HSICPHYCTRLX_FORCESLEEP |
				EXYNOS_5250_HSICPHYCTRLX_FORCESUSPEND
				);
		ग_लिखोl(hsic, drv->reg_phy + EXYNOS_5250_HSICPHYCTRL1);
		ग_लिखोl(hsic, drv->reg_phy + EXYNOS_5250_HSICPHYCTRL2);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण


अटल स्थिर काष्ठा samsung_usb2_common_phy exynos5250_phys[] = अणु
	अणु
		.label		= "device",
		.id		= EXYNOS5250_DEVICE,
		.घातer_on	= exynos5250_घातer_on,
		.घातer_off	= exynos5250_घातer_off,
	पूर्ण,
	अणु
		.label		= "host",
		.id		= EXYNOS5250_HOST,
		.घातer_on	= exynos5250_घातer_on,
		.घातer_off	= exynos5250_घातer_off,
	पूर्ण,
	अणु
		.label		= "hsic0",
		.id		= EXYNOS5250_HSIC0,
		.घातer_on	= exynos5250_घातer_on,
		.घातer_off	= exynos5250_घातer_off,
	पूर्ण,
	अणु
		.label		= "hsic1",
		.id		= EXYNOS5250_HSIC1,
		.घातer_on	= exynos5250_घातer_on,
		.घातer_off	= exynos5250_घातer_off,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा samsung_usb2_common_phy exynos5420_phys[] = अणु
	अणु
		.label		= "host",
		.id		= EXYNOS5250_HOST,
		.घातer_on	= exynos5250_घातer_on,
		.घातer_off	= exynos5250_घातer_off,
	पूर्ण,
	अणु
		.label		= "hsic",
		.id		= EXYNOS5250_HSIC0,
		.घातer_on	= exynos5250_घातer_on,
		.घातer_off	= exynos5250_घातer_off,
	पूर्ण,
पूर्ण;

स्थिर काष्ठा samsung_usb2_phy_config exynos5250_usb2_phy_config = अणु
	.has_mode_चयन	= 1,
	.num_phys		= ARRAY_SIZE(exynos5250_phys),
	.phys			= exynos5250_phys,
	.rate_to_clk		= exynos5250_rate_to_clk,
पूर्ण;

स्थिर काष्ठा samsung_usb2_phy_config exynos5420_usb2_phy_config = अणु
	.has_mode_चयन	= 1,
	.num_phys		= ARRAY_SIZE(exynos5420_phys),
	.phys			= exynos5420_phys,
	.rate_to_clk		= exynos5250_rate_to_clk,
पूर्ण;
