<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
  * This file configures the पूर्णांकernal USB PHY in OMAP4430. Used
  * with TWL6030 transceiver and MUSB on OMAP4430.
  *
  * Copyright (C) 2010 Texas Instruments Incorporated - https://www.ti.com
  * Author: Hema HK <hemahk@ti.com>
  */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/types.h>
#समावेश <linux/delay.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/err.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/musb.h>

#समावेश "soc.h"
#समावेश "control.h"
#समावेश "usb.h"

#घोषणा CONTROL_DEV_CONF		0x300
#घोषणा PHY_PD				0x1

/**
 * omap4430_phy_घातer_करोwn: disable MUSB PHY during early init
 *
 * OMAP4 MUSB PHY module is enabled by शेष on reset, but this will
 * prevent core retention अगर not disabled by SW. USB driver will
 * later on enable this, once and अगर the driver needs it.
 */
अटल पूर्णांक __init omap4430_phy_घातer_करोwn(व्योम)
अणु
	व्योम __iomem *ctrl_base;

	अगर (!cpu_is_omap44xx())
		वापस 0;

	ctrl_base = ioremap(OMAP443X_SCM_BASE, SZ_1K);
	अगर (!ctrl_base) अणु
		pr_err("control module ioremap failed\n");
		वापस -ENOMEM;
	पूर्ण

	/* Power करोwn the phy */
	ग_लिखोl_relaxed(PHY_PD, ctrl_base + CONTROL_DEV_CONF);

	iounmap(ctrl_base);

	वापस 0;
पूर्ण
omap_early_initcall(omap4430_phy_घातer_करोwn);

व्योम am35x_musb_reset(व्योम)
अणु
	u32	regval;

	/* Reset the musb पूर्णांकerface */
	regval = omap_ctrl_पढ़ोl(AM35XX_CONTROL_IP_SW_RESET);

	regval |= AM35XX_USBOTGSS_SW_RST;
	omap_ctrl_ग_लिखोl(regval, AM35XX_CONTROL_IP_SW_RESET);

	regval &= ~AM35XX_USBOTGSS_SW_RST;
	omap_ctrl_ग_लिखोl(regval, AM35XX_CONTROL_IP_SW_RESET);

	regval = omap_ctrl_पढ़ोl(AM35XX_CONTROL_IP_SW_RESET);
पूर्ण

व्योम am35x_musb_phy_घातer(u8 on)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(100);
	u32 devconf2;

	अगर (on) अणु
		/*
		 * Start the on-chip PHY and its PLL.
		 */
		devconf2 = omap_ctrl_पढ़ोl(AM35XX_CONTROL_DEVCONF2);

		devconf2 &= ~(CONF2_RESET | CONF2_PHYPWRDN | CONF2_OTGPWRDN);
		devconf2 |= CONF2_PHY_PLLON;

		omap_ctrl_ग_लिखोl(devconf2, AM35XX_CONTROL_DEVCONF2);

		pr_info("Waiting for PHY clock good...\n");
		जबतक (!(omap_ctrl_पढ़ोl(AM35XX_CONTROL_DEVCONF2)
				& CONF2_PHYCLKGD)) अणु
			cpu_relax();

			अगर (समय_after(jअगरfies, समयout)) अणु
				pr_err("musb PHY clock good timed out\n");
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * Power करोwn the on-chip PHY.
		 */
		devconf2 = omap_ctrl_पढ़ोl(AM35XX_CONTROL_DEVCONF2);

		devconf2 &= ~CONF2_PHY_PLLON;
		devconf2 |=  CONF2_PHYPWRDN | CONF2_OTGPWRDN;
		omap_ctrl_ग_लिखोl(devconf2, AM35XX_CONTROL_DEVCONF2);
	पूर्ण
पूर्ण

व्योम am35x_musb_clear_irq(व्योम)
अणु
	u32 regval;

	regval = omap_ctrl_पढ़ोl(AM35XX_CONTROL_LVL_INTR_CLEAR);
	regval |= AM35XX_USBOTGSS_INT_CLR;
	omap_ctrl_ग_लिखोl(regval, AM35XX_CONTROL_LVL_INTR_CLEAR);
	regval = omap_ctrl_पढ़ोl(AM35XX_CONTROL_LVL_INTR_CLEAR);
पूर्ण

व्योम am35x_set_mode(u8 musb_mode)
अणु
	u32 devconf2 = omap_ctrl_पढ़ोl(AM35XX_CONTROL_DEVCONF2);

	devconf2 &= ~CONF2_OTGMODE;
	चयन (musb_mode) अणु
	हाल MUSB_HOST:		/* Force VBUS valid, ID = 0 */
		devconf2 |= CONF2_FORCE_HOST;
		अवरोध;
	हाल MUSB_PERIPHERAL:	/* Force VBUS valid, ID = 1 */
		devconf2 |= CONF2_FORCE_DEVICE;
		अवरोध;
	हाल MUSB_OTG:		/* Don't override the VBUS/ID comparators */
		devconf2 |= CONF2_NO_OVERRIDE;
		अवरोध;
	शेष:
		pr_info("Unsupported mode %u\n", musb_mode);
	पूर्ण

	omap_ctrl_ग_लिखोl(devconf2, AM35XX_CONTROL_DEVCONF2);
पूर्ण
