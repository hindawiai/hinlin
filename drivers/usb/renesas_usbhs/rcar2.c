<शैली गुरु>
// SPDX-License-Identअगरier: GPL-1.0+
/*
 * Renesas USB driver R-Car Gen. 2 initialization and घातer control
 *
 * Copyright (C) 2014 Ulrich Hecht
 * Copyright (C) 2019 Renesas Electronics Corporation
 */

#समावेश <linux/phy/phy.h>
#समावेश "common.h"
#समावेश "rcar2.h"

अटल पूर्णांक usbhs_rcar2_hardware_init(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा usbhs_priv *priv = usbhs_pdev_to_priv(pdev);

	अगर (IS_ENABLED(CONFIG_GENERIC_PHY)) अणु
		काष्ठा phy *phy = phy_get(&pdev->dev, "usb");

		अगर (IS_ERR(phy))
			वापस PTR_ERR(phy);

		priv->phy = phy;
		वापस 0;
	पूर्ण

	वापस -ENXIO;
पूर्ण

अटल पूर्णांक usbhs_rcar2_hardware_निकास(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा usbhs_priv *priv = usbhs_pdev_to_priv(pdev);

	अगर (priv->phy) अणु
		phy_put(&pdev->dev, priv->phy);
		priv->phy = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक usbhs_rcar2_घातer_ctrl(काष्ठा platक्रमm_device *pdev,
				व्योम __iomem *base, पूर्णांक enable)
अणु
	काष्ठा usbhs_priv *priv = usbhs_pdev_to_priv(pdev);
	पूर्णांक retval = -ENODEV;

	अगर (priv->phy) अणु
		अगर (enable) अणु
			retval = phy_init(priv->phy);

			अगर (!retval)
				retval = phy_घातer_on(priv->phy);
		पूर्ण अन्यथा अणु
			phy_घातer_off(priv->phy);
			phy_निकास(priv->phy);
			retval = 0;
		पूर्ण
	पूर्ण

	वापस retval;
पूर्ण

स्थिर काष्ठा renesas_usbhs_platक्रमm_info usbhs_rcar_gen2_plat_info = अणु
	.platक्रमm_callback = अणु
		.hardware_init = usbhs_rcar2_hardware_init,
		.hardware_निकास = usbhs_rcar2_hardware_निकास,
		.घातer_ctrl = usbhs_rcar2_घातer_ctrl,
		.get_id = usbhs_get_id_as_gadget,
	पूर्ण,
	.driver_param = अणु
		.has_usb_dmac = 1,
		.has_new_pipe_configs = 1,
	पूर्ण,
पूर्ण;
