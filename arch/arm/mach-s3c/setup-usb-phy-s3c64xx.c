<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Copyright (C) 2011 Samsung Electronics Co.Ltd
// Author: Joonyoung Shim <jy0922.shim@samsung.com>

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश "map.h"
#समावेश "cpu.h"
#समावेश "usb-phy.h"

#समावेश "regs-sys-s3c64xx.h"
#समावेश "regs-usb-hsotg-phy-s3c64xx.h"

क्रमागत samsung_usb_phy_type अणु
	USB_PHY_TYPE_DEVICE,
	USB_PHY_TYPE_HOST,
पूर्ण;

अटल पूर्णांक s3c_usb_otgphy_init(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा clk *xusbxti;
	u32 phyclk;

	ग_लिखोl(पढ़ोl(S3C64XX_OTHERS) | S3C64XX_OTHERS_USBMASK, S3C64XX_OTHERS);

	/* set घड़ी frequency क्रम PLL */
	phyclk = पढ़ोl(S3C_PHYCLK) & ~S3C_PHYCLK_CLKSEL_MASK;

	xusbxti = clk_get(&pdev->dev, "xusbxti");
	अगर (!IS_ERR(xusbxti)) अणु
		चयन (clk_get_rate(xusbxti)) अणु
		हाल 12 * MHZ:
			phyclk |= S3C_PHYCLK_CLKSEL_12M;
			अवरोध;
		हाल 24 * MHZ:
			phyclk |= S3C_PHYCLK_CLKSEL_24M;
			अवरोध;
		शेष:
		हाल 48 * MHZ:
			/* शेष reference घड़ी */
			अवरोध;
		पूर्ण
		clk_put(xusbxti);
	पूर्ण

	/* TODO: select बाह्यal घड़ी/oscillator */
	ग_लिखोl(phyclk | S3C_PHYCLK_CLK_FORCE, S3C_PHYCLK);

	/* set to normal OTG PHY */
	ग_लिखोl((पढ़ोl(S3C_PHYPWR) & ~S3C_PHYPWR_NORMAL_MASK), S3C_PHYPWR);
	mdelay(1);

	/* reset OTG PHY and Link */
	ग_लिखोl(S3C_RSTCON_PHY | S3C_RSTCON_HCLK | S3C_RSTCON_PHYCLK,
			S3C_RSTCON);
	udelay(20);	/* at-least 10uS */
	ग_लिखोl(0, S3C_RSTCON);

	वापस 0;
पूर्ण

अटल पूर्णांक s3c_usb_otgphy_निकास(काष्ठा platक्रमm_device *pdev)
अणु
	ग_लिखोl((पढ़ोl(S3C_PHYPWR) | S3C_PHYPWR_ANALOG_POWERDOWN |
				S3C_PHYPWR_OTG_DISABLE), S3C_PHYPWR);

	ग_लिखोl(पढ़ोl(S3C64XX_OTHERS) & ~S3C64XX_OTHERS_USBMASK, S3C64XX_OTHERS);

	वापस 0;
पूर्ण

पूर्णांक s3c_usb_phy_init(काष्ठा platक्रमm_device *pdev, पूर्णांक type)
अणु
	अगर (type == USB_PHY_TYPE_DEVICE)
		वापस s3c_usb_otgphy_init(pdev);

	वापस -EINVAL;
पूर्ण

पूर्णांक s3c_usb_phy_निकास(काष्ठा platक्रमm_device *pdev, पूर्णांक type)
अणु
	अगर (type == USB_PHY_TYPE_DEVICE)
		वापस s3c_usb_otgphy_निकास(pdev);

	वापस -EINVAL;
पूर्ण
