<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * R-Car Gen3 HDMI PHY
 *
 * Copyright (C) 2016 Renesas Electronics Corporation
 *
 * Contact: Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */

#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <drm/bridge/dw_hdmi.h>
#समावेश <drm/drm_modes.h>

#घोषणा RCAR_HDMI_PHY_OPMODE_PLLCFG	0x06	/* Mode of operation and PLL भागiders */
#घोषणा RCAR_HDMI_PHY_PLLCURRGMPCTRL	0x10	/* PLL current and Gmp (conductance) */
#घोषणा RCAR_HDMI_PHY_PLLDIVCTRL	0x11	/* PLL भागiders */

काष्ठा rcar_hdmi_phy_params अणु
	अचिन्हित दीर्घ mpixelघड़ी;
	u16 opmode_भाग;	/* Mode of operation and PLL भागiders */
	u16 curr_gmp;	/* PLL current and Gmp (conductance) */
	u16 भाग;	/* PLL भागiders */
पूर्ण;

अटल स्थिर काष्ठा rcar_hdmi_phy_params rcar_hdmi_phy_params[] = अणु
	अणु 35500000,  0x0003, 0x0344, 0x0328 पूर्ण,
	अणु 44900000,  0x0003, 0x0285, 0x0128 पूर्ण,
	अणु 71000000,  0x0002, 0x1184, 0x0314 पूर्ण,
	अणु 90000000,  0x0002, 0x1144, 0x0114 पूर्ण,
	अणु 140250000, 0x0001, 0x20c4, 0x030a पूर्ण,
	अणु 182750000, 0x0001, 0x2084, 0x010a पूर्ण,
	अणु 281250000, 0x0000, 0x0084, 0x0305 पूर्ण,
	अणु 297000000, 0x0000, 0x0084, 0x0105 पूर्ण,
	अणु ~0UL,      0x0000, 0x0000, 0x0000 पूर्ण,
पूर्ण;

अटल क्रमागत drm_mode_status
rcar_hdmi_mode_valid(काष्ठा dw_hdmi *hdmi, व्योम *data,
		     स्थिर काष्ठा drm_display_info *info,
		     स्थिर काष्ठा drm_display_mode *mode)
अणु
	/*
	 * The maximum supported घड़ी frequency is 297 MHz, as shown in the PHY
	 * parameters table.
	 */
	अगर (mode->घड़ी > 297000)
		वापस MODE_CLOCK_HIGH;

	वापस MODE_OK;
पूर्ण

अटल पूर्णांक rcar_hdmi_phy_configure(काष्ठा dw_hdmi *hdmi, व्योम *data,
				   अचिन्हित दीर्घ mpixelघड़ी)
अणु
	स्थिर काष्ठा rcar_hdmi_phy_params *params = rcar_hdmi_phy_params;

	क्रम (; params->mpixelघड़ी != ~0UL; ++params) अणु
		अगर (mpixelघड़ी <= params->mpixelघड़ी)
			अवरोध;
	पूर्ण

	अगर (params->mpixelघड़ी == ~0UL)
		वापस -EINVAL;

	dw_hdmi_phy_i2c_ग_लिखो(hdmi, params->opmode_भाग,
			      RCAR_HDMI_PHY_OPMODE_PLLCFG);
	dw_hdmi_phy_i2c_ग_लिखो(hdmi, params->curr_gmp,
			      RCAR_HDMI_PHY_PLLCURRGMPCTRL);
	dw_hdmi_phy_i2c_ग_लिखो(hdmi, params->भाग, RCAR_HDMI_PHY_PLLDIVCTRL);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dw_hdmi_plat_data rcar_dw_hdmi_plat_data = अणु
	.mode_valid = rcar_hdmi_mode_valid,
	.configure_phy	= rcar_hdmi_phy_configure,
पूर्ण;

अटल पूर्णांक rcar_dw_hdmi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dw_hdmi *hdmi;

	hdmi = dw_hdmi_probe(pdev, &rcar_dw_hdmi_plat_data);
	अगर (IS_ERR(hdmi))
		वापस PTR_ERR(hdmi);

	platक्रमm_set_drvdata(pdev, hdmi);

	वापस 0;
पूर्ण

अटल पूर्णांक rcar_dw_hdmi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dw_hdmi *hdmi = platक्रमm_get_drvdata(pdev);

	dw_hdmi_हटाओ(hdmi);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id rcar_dw_hdmi_of_table[] = अणु
	अणु .compatible = "renesas,rcar-gen3-hdmi" पूर्ण,
	अणु /* Sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, rcar_dw_hdmi_of_table);

अटल काष्ठा platक्रमm_driver rcar_dw_hdmi_platक्रमm_driver = अणु
	.probe		= rcar_dw_hdmi_probe,
	.हटाओ		= rcar_dw_hdmi_हटाओ,
	.driver		= अणु
		.name	= "rcar-dw-hdmi",
		.of_match_table = rcar_dw_hdmi_of_table,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(rcar_dw_hdmi_platक्रमm_driver);

MODULE_AUTHOR("Laurent Pinchart <laurent.pinchart@ideasonboard.com>");
MODULE_DESCRIPTION("Renesas R-Car Gen3 HDMI Encoder Driver");
MODULE_LICENSE("GPL");
