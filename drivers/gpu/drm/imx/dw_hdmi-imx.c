<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (C) 2011-2013 Freescale Semiconductor, Inc.
 *
 * derived from imx-hdmi.c(नामd to bridge/dw_hdmi.c now)
 */

#समावेश <linux/component.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/mfd/syscon/imx6q-iomuxc-gpr.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#समावेश <video/imx-ipu-v3.h>

#समावेश <drm/bridge/dw_hdmi.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_edid.h>
#समावेश <drm/drm_encoder.h>
#समावेश <drm/drm_managed.h>
#समावेश <drm/drm_of.h>
#समावेश <drm/drm_simple_kms_helper.h>

#समावेश "imx-drm.h"

काष्ठा imx_hdmi;

काष्ठा imx_hdmi_encoder अणु
	काष्ठा drm_encoder encoder;
	काष्ठा imx_hdmi *hdmi;
पूर्ण;

काष्ठा imx_hdmi अणु
	काष्ठा device *dev;
	काष्ठा drm_bridge *bridge;
	काष्ठा dw_hdmi *hdmi;
	काष्ठा regmap *regmap;
पूर्ण;

अटल अंतरभूत काष्ठा imx_hdmi *enc_to_imx_hdmi(काष्ठा drm_encoder *e)
अणु
	वापस container_of(e, काष्ठा imx_hdmi_encoder, encoder)->hdmi;
पूर्ण

अटल स्थिर काष्ठा dw_hdmi_mpll_config imx_mpll_cfg[] = अणु
	अणु
		45250000, अणु
			अणु 0x01e0, 0x0000 पूर्ण,
			अणु 0x21e1, 0x0000 पूर्ण,
			अणु 0x41e2, 0x0000 पूर्ण
		पूर्ण,
	पूर्ण, अणु
		92500000, अणु
			अणु 0x0140, 0x0005 पूर्ण,
			अणु 0x2141, 0x0005 पूर्ण,
			अणु 0x4142, 0x0005 पूर्ण,
	पूर्ण,
	पूर्ण, अणु
		148500000, अणु
			अणु 0x00a0, 0x000a पूर्ण,
			अणु 0x20a1, 0x000a पूर्ण,
			अणु 0x40a2, 0x000a पूर्ण,
		पूर्ण,
	पूर्ण, अणु
		216000000, अणु
			अणु 0x00a0, 0x000a पूर्ण,
			अणु 0x2001, 0x000f पूर्ण,
			अणु 0x4002, 0x000f पूर्ण,
		पूर्ण,
	पूर्ण, अणु
		~0UL, अणु
			अणु 0x0000, 0x0000 पूर्ण,
			अणु 0x0000, 0x0000 पूर्ण,
			अणु 0x0000, 0x0000 पूर्ण,
		पूर्ण,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा dw_hdmi_curr_ctrl imx_cur_ctr[] = अणु
	/*      pixelclk     bpp8    bpp10   bpp12 */
	अणु
		54000000, अणु 0x091c, 0x091c, 0x06dc पूर्ण,
	पूर्ण, अणु
		58400000, अणु 0x091c, 0x06dc, 0x06dc पूर्ण,
	पूर्ण, अणु
		72000000, अणु 0x06dc, 0x06dc, 0x091c पूर्ण,
	पूर्ण, अणु
		74250000, अणु 0x06dc, 0x0b5c, 0x091c पूर्ण,
	पूर्ण, अणु
		118800000, अणु 0x091c, 0x091c, 0x06dc पूर्ण,
	पूर्ण, अणु
		216000000, अणु 0x06dc, 0x0b5c, 0x091c पूर्ण,
	पूर्ण, अणु
		~0UL, अणु 0x0000, 0x0000, 0x0000 पूर्ण,
	पूर्ण,
पूर्ण;

/*
 * Resistance term 133Ohm Cfg
 * PREEMP config 0.00
 * TX/CK level 10
 */
अटल स्थिर काष्ठा dw_hdmi_phy_config imx_phy_config[] = अणु
	/*pixelclk   symbol   term   vlev */
	अणु 216000000, 0x800d, 0x0005, 0x01adपूर्ण,
	अणु ~0UL,      0x0000, 0x0000, 0x0000पूर्ण
पूर्ण;

अटल व्योम dw_hdmi_imx_encoder_enable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा imx_hdmi *hdmi = enc_to_imx_hdmi(encoder);
	पूर्णांक mux = drm_of_encoder_active_port_id(hdmi->dev->of_node, encoder);

	regmap_update_bits(hdmi->regmap, IOMUXC_GPR3,
			   IMX6Q_GPR3_HDMI_MUX_CTL_MASK,
			   mux << IMX6Q_GPR3_HDMI_MUX_CTL_SHIFT);
पूर्ण

अटल पूर्णांक dw_hdmi_imx_atomic_check(काष्ठा drm_encoder *encoder,
				    काष्ठा drm_crtc_state *crtc_state,
				    काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा imx_crtc_state *imx_crtc_state = to_imx_crtc_state(crtc_state);

	imx_crtc_state->bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X24;
	imx_crtc_state->di_hsync_pin = 2;
	imx_crtc_state->di_vsync_pin = 3;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs dw_hdmi_imx_encoder_helper_funcs = अणु
	.enable     = dw_hdmi_imx_encoder_enable,
	.atomic_check = dw_hdmi_imx_atomic_check,
पूर्ण;

अटल क्रमागत drm_mode_status
imx6q_hdmi_mode_valid(काष्ठा dw_hdmi *hdmi, व्योम *data,
		      स्थिर काष्ठा drm_display_info *info,
		      स्थिर काष्ठा drm_display_mode *mode)
अणु
	अगर (mode->घड़ी < 13500)
		वापस MODE_CLOCK_LOW;
	/* FIXME: Hardware is capable of 266MHz, but setup data is missing. */
	अगर (mode->घड़ी > 216000)
		वापस MODE_CLOCK_HIGH;

	वापस MODE_OK;
पूर्ण

अटल क्रमागत drm_mode_status
imx6dl_hdmi_mode_valid(काष्ठा dw_hdmi *hdmi, व्योम *data,
		       स्थिर काष्ठा drm_display_info *info,
		       स्थिर काष्ठा drm_display_mode *mode)
अणु
	अगर (mode->घड़ी < 13500)
		वापस MODE_CLOCK_LOW;
	/* FIXME: Hardware is capable of 270MHz, but setup data is missing. */
	अगर (mode->घड़ी > 216000)
		वापस MODE_CLOCK_HIGH;

	वापस MODE_OK;
पूर्ण

अटल काष्ठा dw_hdmi_plat_data imx6q_hdmi_drv_data = अणु
	.mpll_cfg   = imx_mpll_cfg,
	.cur_ctr    = imx_cur_ctr,
	.phy_config = imx_phy_config,
	.mode_valid = imx6q_hdmi_mode_valid,
पूर्ण;

अटल काष्ठा dw_hdmi_plat_data imx6dl_hdmi_drv_data = अणु
	.mpll_cfg = imx_mpll_cfg,
	.cur_ctr  = imx_cur_ctr,
	.phy_config = imx_phy_config,
	.mode_valid = imx6dl_hdmi_mode_valid,
पूर्ण;

अटल स्थिर काष्ठा of_device_id dw_hdmi_imx_dt_ids[] = अणु
	अणु .compatible = "fsl,imx6q-hdmi",
	  .data = &imx6q_hdmi_drv_data
	पूर्ण, अणु
	  .compatible = "fsl,imx6dl-hdmi",
	  .data = &imx6dl_hdmi_drv_data
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, dw_hdmi_imx_dt_ids);

अटल पूर्णांक dw_hdmi_imx_bind(काष्ठा device *dev, काष्ठा device *master,
			    व्योम *data)
अणु
	काष्ठा drm_device *drm = data;
	काष्ठा imx_hdmi_encoder *hdmi_encoder;
	काष्ठा drm_encoder *encoder;
	पूर्णांक ret;

	hdmi_encoder = drmm_simple_encoder_alloc(drm, काष्ठा imx_hdmi_encoder,
						 encoder, DRM_MODE_ENCODER_TMDS);
	अगर (IS_ERR(hdmi_encoder))
		वापस PTR_ERR(hdmi_encoder);

	hdmi_encoder->hdmi = dev_get_drvdata(dev);
	encoder = &hdmi_encoder->encoder;

	ret = imx_drm_encoder_parse_of(drm, encoder, dev->of_node);
	अगर (ret)
		वापस ret;

	drm_encoder_helper_add(encoder, &dw_hdmi_imx_encoder_helper_funcs);

	वापस drm_bridge_attach(encoder, hdmi_encoder->hdmi->bridge, शून्य, 0);
पूर्ण

अटल स्थिर काष्ठा component_ops dw_hdmi_imx_ops = अणु
	.bind	= dw_hdmi_imx_bind,
पूर्ण;

अटल पूर्णांक dw_hdmi_imx_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	स्थिर काष्ठा of_device_id *match = of_match_node(dw_hdmi_imx_dt_ids, np);
	काष्ठा imx_hdmi *hdmi;

	hdmi = devm_kzalloc(&pdev->dev, माप(*hdmi), GFP_KERNEL);
	अगर (!hdmi)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, hdmi);
	hdmi->dev = &pdev->dev;

	hdmi->regmap = syscon_regmap_lookup_by_phandle(np, "gpr");
	अगर (IS_ERR(hdmi->regmap)) अणु
		dev_err(hdmi->dev, "Unable to get gpr\n");
		वापस PTR_ERR(hdmi->regmap);
	पूर्ण

	hdmi->hdmi = dw_hdmi_probe(pdev, match->data);
	अगर (IS_ERR(hdmi->hdmi))
		वापस PTR_ERR(hdmi->hdmi);

	hdmi->bridge = of_drm_find_bridge(np);
	अगर (!hdmi->bridge) अणु
		dev_err(hdmi->dev, "Unable to find bridge\n");
		वापस -ENODEV;
	पूर्ण

	वापस component_add(&pdev->dev, &dw_hdmi_imx_ops);
पूर्ण

अटल पूर्णांक dw_hdmi_imx_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा imx_hdmi *hdmi = platक्रमm_get_drvdata(pdev);

	component_del(&pdev->dev, &dw_hdmi_imx_ops);
	dw_hdmi_हटाओ(hdmi->hdmi);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver dw_hdmi_imx_platक्रमm_driver = अणु
	.probe  = dw_hdmi_imx_probe,
	.हटाओ = dw_hdmi_imx_हटाओ,
	.driver = अणु
		.name = "dwhdmi-imx",
		.of_match_table = dw_hdmi_imx_dt_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(dw_hdmi_imx_platक्रमm_driver);

MODULE_AUTHOR("Andy Yan <andy.yan@rock-chips.com>");
MODULE_AUTHOR("Yakir Yang <ykk@rock-chips.com>");
MODULE_DESCRIPTION("IMX6 Specific DW-HDMI Driver Extension");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:dwhdmi-imx");
