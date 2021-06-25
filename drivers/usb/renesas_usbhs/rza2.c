<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Renesas USB driver RZ/A2 initialization and घातer control
 *
 * Copyright (C) 2019 Chris Bअक्रमt
 * Copyright (C) 2019 Renesas Electronics Corporation
 */

#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_device.h>
#समावेश <linux/phy/phy.h>
#समावेश "common.h"
#समावेश "rza.h"

अटल पूर्णांक usbhs_rza2_hardware_init(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा usbhs_priv *priv = usbhs_pdev_to_priv(pdev);
	काष्ठा phy *phy = phy_get(&pdev->dev, "usb");

	अगर (IS_ERR(phy))
		वापस PTR_ERR(phy);

	priv->phy = phy;
	वापस 0;
पूर्ण

अटल पूर्णांक usbhs_rza2_hardware_निकास(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा usbhs_priv *priv = usbhs_pdev_to_priv(pdev);

	phy_put(&pdev->dev, priv->phy);
	priv->phy = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक usbhs_rza2_घातer_ctrl(काष्ठा platक्रमm_device *pdev,
				व्योम __iomem *base, पूर्णांक enable)
अणु
	काष्ठा usbhs_priv *priv = usbhs_pdev_to_priv(pdev);
	पूर्णांक retval = 0;

	अगर (!priv->phy)
		वापस -ENODEV;

	अगर (enable) अणु
		retval = phy_init(priv->phy);
		usbhs_bset(priv, SUSPMODE, SUSPM, SUSPM);
		udelay(100);	/* Wait क्रम PLL to become stable */
		अगर (!retval)
			retval = phy_घातer_on(priv->phy);
	पूर्ण अन्यथा अणु
		usbhs_bset(priv, SUSPMODE, SUSPM, 0);
		phy_घातer_off(priv->phy);
		phy_निकास(priv->phy);
	पूर्ण

	वापस retval;
पूर्ण

स्थिर काष्ठा renesas_usbhs_platक्रमm_info usbhs_rza2_plat_info = अणु
	.platक्रमm_callback = अणु
		.hardware_init = usbhs_rza2_hardware_init,
		.hardware_निकास = usbhs_rza2_hardware_निकास,
		.घातer_ctrl = usbhs_rza2_घातer_ctrl,
		.get_id = usbhs_get_id_as_gadget,
	पूर्ण,
	.driver_param = अणु
		.has_cnen = 1,
		.cfअगरo_byte_addr = 1,
		.has_new_pipe_configs = 1,
	पूर्ण,
पूर्ण;
