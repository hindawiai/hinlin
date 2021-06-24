<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (c) 2018 Jernej Skrabec <jernej.skrabec@siol.net>
 */

#समावेश <linux/component.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <drm/drm_crtc_helper.h>
#समावेश <drm/drm_of.h>
#समावेश <drm/drm_simple_kms_helper.h>

#समावेश "sun8i_dw_hdmi.h"
#समावेश "sun8i_tcon_top.h"

अटल व्योम sun8i_dw_hdmi_encoder_mode_set(काष्ठा drm_encoder *encoder,
					   काष्ठा drm_display_mode *mode,
					   काष्ठा drm_display_mode *adj_mode)
अणु
	काष्ठा sun8i_dw_hdmi *hdmi = encoder_to_sun8i_dw_hdmi(encoder);

	clk_set_rate(hdmi->clk_पंचांगds, mode->crtc_घड़ी * 1000);
पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs
sun8i_dw_hdmi_encoder_helper_funcs = अणु
	.mode_set = sun8i_dw_hdmi_encoder_mode_set,
पूर्ण;

अटल क्रमागत drm_mode_status
sun8i_dw_hdmi_mode_valid_a83t(काष्ठा dw_hdmi *hdmi, व्योम *data,
			      स्थिर काष्ठा drm_display_info *info,
			      स्थिर काष्ठा drm_display_mode *mode)
अणु
	अगर (mode->घड़ी > 297000)
		वापस MODE_CLOCK_HIGH;

	वापस MODE_OK;
पूर्ण

अटल क्रमागत drm_mode_status
sun8i_dw_hdmi_mode_valid_h6(काष्ठा dw_hdmi *hdmi, व्योम *data,
			    स्थिर काष्ठा drm_display_info *info,
			    स्थिर काष्ठा drm_display_mode *mode)
अणु
	/*
	 * Controller support maximum of 594 MHz, which correlates to
	 * 4K@60Hz 4:4:4 or RGB.
	 */
	अगर (mode->घड़ी > 594000)
		वापस MODE_CLOCK_HIGH;

	वापस MODE_OK;
पूर्ण

अटल bool sun8i_dw_hdmi_node_is_tcon_top(काष्ठा device_node *node)
अणु
	वापस IS_ENABLED(CONFIG_DRM_SUN8I_TCON_TOP) &&
		!!of_match_node(sun8i_tcon_top_of_table, node);
पूर्ण

अटल u32 sun8i_dw_hdmi_find_possible_crtcs(काष्ठा drm_device *drm,
					     काष्ठा device_node *node)
अणु
	काष्ठा device_node *port, *ep, *remote, *remote_port;
	u32 crtcs = 0;

	remote = of_graph_get_remote_node(node, 0, -1);
	अगर (!remote)
		वापस 0;

	अगर (sun8i_dw_hdmi_node_is_tcon_top(remote)) अणु
		port = of_graph_get_port_by_id(remote, 4);
		अगर (!port)
			जाओ crtcs_निकास;

		क्रम_each_child_of_node(port, ep) अणु
			remote_port = of_graph_get_remote_port(ep);
			अगर (remote_port) अणु
				crtcs |= drm_of_crtc_port_mask(drm, remote_port);
				of_node_put(remote_port);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		crtcs = drm_of_find_possible_crtcs(drm, node);
	पूर्ण

crtcs_निकास:
	of_node_put(remote);

	वापस crtcs;
पूर्ण

अटल पूर्णांक sun8i_dw_hdmi_find_connector_pdev(काष्ठा device *dev,
					     काष्ठा platक्रमm_device **pdev_out)
अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा device_node *remote;

	remote = of_graph_get_remote_node(dev->of_node, 1, -1);
	अगर (!remote)
		वापस -ENODEV;

	अगर (!of_device_is_compatible(remote, "hdmi-connector")) अणु
		of_node_put(remote);
		वापस -ENODEV;
	पूर्ण

	pdev = of_find_device_by_node(remote);
	of_node_put(remote);
	अगर (!pdev)
		वापस -ENODEV;

	*pdev_out = pdev;
	वापस 0;
पूर्ण

अटल पूर्णांक sun8i_dw_hdmi_bind(काष्ठा device *dev, काष्ठा device *master,
			      व्योम *data)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev), *connector_pdev;
	काष्ठा dw_hdmi_plat_data *plat_data;
	काष्ठा drm_device *drm = data;
	काष्ठा device_node *phy_node;
	काष्ठा drm_encoder *encoder;
	काष्ठा sun8i_dw_hdmi *hdmi;
	पूर्णांक ret;

	अगर (!pdev->dev.of_node)
		वापस -ENODEV;

	hdmi = devm_kzalloc(&pdev->dev, माप(*hdmi), GFP_KERNEL);
	अगर (!hdmi)
		वापस -ENOMEM;

	plat_data = &hdmi->plat_data;
	hdmi->dev = &pdev->dev;
	encoder = &hdmi->encoder;

	hdmi->quirks = of_device_get_match_data(dev);

	encoder->possible_crtcs =
		sun8i_dw_hdmi_find_possible_crtcs(drm, dev->of_node);
	/*
	 * If we failed to find the CRTC(s) which this encoder is
	 * supposed to be connected to, it's because the CRTC has
	 * not been रेजिस्टरed yet.  Defer probing, and hope that
	 * the required CRTC is added later.
	 */
	अगर (encoder->possible_crtcs == 0)
		वापस -EPROBE_DEFER;

	hdmi->rst_ctrl = devm_reset_control_get(dev, "ctrl");
	अगर (IS_ERR(hdmi->rst_ctrl)) अणु
		dev_err(dev, "Could not get ctrl reset control\n");
		वापस PTR_ERR(hdmi->rst_ctrl);
	पूर्ण

	hdmi->clk_पंचांगds = devm_clk_get(dev, "tmds");
	अगर (IS_ERR(hdmi->clk_पंचांगds)) अणु
		dev_err(dev, "Couldn't get the tmds clock\n");
		वापस PTR_ERR(hdmi->clk_पंचांगds);
	पूर्ण

	hdmi->regulator = devm_regulator_get(dev, "hvcc");
	अगर (IS_ERR(hdmi->regulator)) अणु
		dev_err(dev, "Couldn't get regulator\n");
		वापस PTR_ERR(hdmi->regulator);
	पूर्ण

	ret = sun8i_dw_hdmi_find_connector_pdev(dev, &connector_pdev);
	अगर (!ret) अणु
		hdmi->ddc_en = gpiod_get_optional(&connector_pdev->dev,
						  "ddc-en", GPIOD_OUT_HIGH);
		platक्रमm_device_put(connector_pdev);

		अगर (IS_ERR(hdmi->ddc_en)) अणु
			dev_err(dev, "Couldn't get ddc-en gpio\n");
			वापस PTR_ERR(hdmi->ddc_en);
		पूर्ण
	पूर्ण

	ret = regulator_enable(hdmi->regulator);
	अगर (ret) अणु
		dev_err(dev, "Failed to enable regulator\n");
		जाओ err_unref_ddc_en;
	पूर्ण

	gpiod_set_value(hdmi->ddc_en, 1);

	ret = reset_control_deनिश्चित(hdmi->rst_ctrl);
	अगर (ret) अणु
		dev_err(dev, "Could not deassert ctrl reset control\n");
		जाओ err_disable_ddc_en;
	पूर्ण

	ret = clk_prepare_enable(hdmi->clk_पंचांगds);
	अगर (ret) अणु
		dev_err(dev, "Could not enable tmds clock\n");
		जाओ err_निश्चित_ctrl_reset;
	पूर्ण

	phy_node = of_parse_phandle(dev->of_node, "phys", 0);
	अगर (!phy_node) अणु
		dev_err(dev, "Can't found PHY phandle\n");
		ret = -EINVAL;
		जाओ err_disable_clk_पंचांगds;
	पूर्ण

	ret = sun8i_hdmi_phy_get(hdmi, phy_node);
	of_node_put(phy_node);
	अगर (ret) अणु
		dev_err(dev, "Couldn't get the HDMI PHY\n");
		जाओ err_disable_clk_पंचांगds;
	पूर्ण

	drm_encoder_helper_add(encoder, &sun8i_dw_hdmi_encoder_helper_funcs);
	drm_simple_encoder_init(drm, encoder, DRM_MODE_ENCODER_TMDS);

	sun8i_hdmi_phy_init(hdmi->phy);

	plat_data->mode_valid = hdmi->quirks->mode_valid;
	plat_data->use_drm_infoframe = hdmi->quirks->use_drm_infoframe;
	sun8i_hdmi_phy_set_ops(hdmi->phy, plat_data);

	platक्रमm_set_drvdata(pdev, hdmi);

	hdmi->hdmi = dw_hdmi_bind(pdev, encoder, plat_data);

	/*
	 * If dw_hdmi_bind() fails we'll never call dw_hdmi_unbind(),
	 * which would have called the encoder cleanup.  Do it manually.
	 */
	अगर (IS_ERR(hdmi->hdmi)) अणु
		ret = PTR_ERR(hdmi->hdmi);
		जाओ cleanup_encoder;
	पूर्ण

	वापस 0;

cleanup_encoder:
	drm_encoder_cleanup(encoder);
err_disable_clk_पंचांगds:
	clk_disable_unprepare(hdmi->clk_पंचांगds);
err_निश्चित_ctrl_reset:
	reset_control_निश्चित(hdmi->rst_ctrl);
err_disable_ddc_en:
	gpiod_set_value(hdmi->ddc_en, 0);
	regulator_disable(hdmi->regulator);
err_unref_ddc_en:
	अगर (hdmi->ddc_en)
		gpiod_put(hdmi->ddc_en);

	वापस ret;
पूर्ण

अटल व्योम sun8i_dw_hdmi_unbind(काष्ठा device *dev, काष्ठा device *master,
				 व्योम *data)
अणु
	काष्ठा sun8i_dw_hdmi *hdmi = dev_get_drvdata(dev);

	dw_hdmi_unbind(hdmi->hdmi);
	clk_disable_unprepare(hdmi->clk_पंचांगds);
	reset_control_निश्चित(hdmi->rst_ctrl);
	gpiod_set_value(hdmi->ddc_en, 0);
	regulator_disable(hdmi->regulator);

	अगर (hdmi->ddc_en)
		gpiod_put(hdmi->ddc_en);
पूर्ण

अटल स्थिर काष्ठा component_ops sun8i_dw_hdmi_ops = अणु
	.bind	= sun8i_dw_hdmi_bind,
	.unbind	= sun8i_dw_hdmi_unbind,
पूर्ण;

अटल पूर्णांक sun8i_dw_hdmi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस component_add(&pdev->dev, &sun8i_dw_hdmi_ops);
पूर्ण

अटल पूर्णांक sun8i_dw_hdmi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	component_del(&pdev->dev, &sun8i_dw_hdmi_ops);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा sun8i_dw_hdmi_quirks sun8i_a83t_quirks = अणु
	.mode_valid = sun8i_dw_hdmi_mode_valid_a83t,
पूर्ण;

अटल स्थिर काष्ठा sun8i_dw_hdmi_quirks sun50i_h6_quirks = अणु
	.mode_valid = sun8i_dw_hdmi_mode_valid_h6,
	.use_drm_infoframe = true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id sun8i_dw_hdmi_dt_ids[] = अणु
	अणु
		.compatible = "allwinner,sun8i-a83t-dw-hdmi",
		.data = &sun8i_a83t_quirks,
	पूर्ण,
	अणु
		.compatible = "allwinner,sun50i-h6-dw-hdmi",
		.data = &sun50i_h6_quirks,
	पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sun8i_dw_hdmi_dt_ids);

अटल काष्ठा platक्रमm_driver sun8i_dw_hdmi_pltfm_driver = अणु
	.probe  = sun8i_dw_hdmi_probe,
	.हटाओ = sun8i_dw_hdmi_हटाओ,
	.driver = अणु
		.name = "sun8i-dw-hdmi",
		.of_match_table = sun8i_dw_hdmi_dt_ids,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init sun8i_dw_hdmi_init(व्योम)
अणु
	पूर्णांक ret;

	ret = platक्रमm_driver_रेजिस्टर(&sun8i_dw_hdmi_pltfm_driver);
	अगर (ret)
		वापस ret;

	ret = platक्रमm_driver_रेजिस्टर(&sun8i_hdmi_phy_driver);
	अगर (ret) अणु
		platक्रमm_driver_unरेजिस्टर(&sun8i_dw_hdmi_pltfm_driver);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम __निकास sun8i_dw_hdmi_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&sun8i_dw_hdmi_pltfm_driver);
	platक्रमm_driver_unरेजिस्टर(&sun8i_hdmi_phy_driver);
पूर्ण

module_init(sun8i_dw_hdmi_init);
module_निकास(sun8i_dw_hdmi_निकास);

MODULE_AUTHOR("Jernej Skrabec <jernej.skrabec@siol.net>");
MODULE_DESCRIPTION("Allwinner DW HDMI bridge");
MODULE_LICENSE("GPL");
