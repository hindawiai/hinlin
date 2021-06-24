<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2016, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/of_graph.h>

#समावेश "adv7511.h"

अटल स्थिर काष्ठा reg_sequence adv7533_fixed_रेजिस्टरs[] = अणु
	अणु 0x16, 0x20 पूर्ण,
	अणु 0x9a, 0xe0 पूर्ण,
	अणु 0xba, 0x70 पूर्ण,
	अणु 0xde, 0x82 पूर्ण,
	अणु 0xe4, 0x40 पूर्ण,
	अणु 0xe5, 0x80 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_sequence adv7533_cec_fixed_रेजिस्टरs[] = अणु
	अणु 0x15, 0xd0 पूर्ण,
	अणु 0x17, 0xd0 पूर्ण,
	अणु 0x24, 0x20 पूर्ण,
	अणु 0x57, 0x11 पूर्ण,
	अणु 0x05, 0xc8 पूर्ण,
पूर्ण;

अटल व्योम adv7511_dsi_config_timing_gen(काष्ठा adv7511 *adv)
अणु
	काष्ठा mipi_dsi_device *dsi = adv->dsi;
	काष्ठा drm_display_mode *mode = &adv->curr_mode;
	अचिन्हित पूर्णांक hsw, hfp, hbp, vsw, vfp, vbp;
	u8 घड़ी_भाग_by_lanes[] = अणु 6, 4, 3 पूर्ण;	/* 2, 3, 4 lanes */

	hsw = mode->hsync_end - mode->hsync_start;
	hfp = mode->hsync_start - mode->hdisplay;
	hbp = mode->htotal - mode->hsync_end;
	vsw = mode->vsync_end - mode->vsync_start;
	vfp = mode->vsync_start - mode->vdisplay;
	vbp = mode->vtotal - mode->vsync_end;

	/* set pixel घड़ी भागider mode */
	regmap_ग_लिखो(adv->regmap_cec, 0x16,
		     घड़ी_भाग_by_lanes[dsi->lanes - 2] << 3);

	/* horizontal porch params */
	regmap_ग_लिखो(adv->regmap_cec, 0x28, mode->htotal >> 4);
	regmap_ग_लिखो(adv->regmap_cec, 0x29, (mode->htotal << 4) & 0xff);
	regmap_ग_लिखो(adv->regmap_cec, 0x2a, hsw >> 4);
	regmap_ग_लिखो(adv->regmap_cec, 0x2b, (hsw << 4) & 0xff);
	regmap_ग_लिखो(adv->regmap_cec, 0x2c, hfp >> 4);
	regmap_ग_लिखो(adv->regmap_cec, 0x2d, (hfp << 4) & 0xff);
	regmap_ग_लिखो(adv->regmap_cec, 0x2e, hbp >> 4);
	regmap_ग_लिखो(adv->regmap_cec, 0x2f, (hbp << 4) & 0xff);

	/* vertical porch params */
	regmap_ग_लिखो(adv->regmap_cec, 0x30, mode->vtotal >> 4);
	regmap_ग_लिखो(adv->regmap_cec, 0x31, (mode->vtotal << 4) & 0xff);
	regmap_ग_लिखो(adv->regmap_cec, 0x32, vsw >> 4);
	regmap_ग_लिखो(adv->regmap_cec, 0x33, (vsw << 4) & 0xff);
	regmap_ग_लिखो(adv->regmap_cec, 0x34, vfp >> 4);
	regmap_ग_लिखो(adv->regmap_cec, 0x35, (vfp << 4) & 0xff);
	regmap_ग_लिखो(adv->regmap_cec, 0x36, vbp >> 4);
	regmap_ग_लिखो(adv->regmap_cec, 0x37, (vbp << 4) & 0xff);
पूर्ण

व्योम adv7533_dsi_घातer_on(काष्ठा adv7511 *adv)
अणु
	काष्ठा mipi_dsi_device *dsi = adv->dsi;

	अगर (adv->use_timing_gen)
		adv7511_dsi_config_timing_gen(adv);

	/* set number of dsi lanes */
	regmap_ग_लिखो(adv->regmap_cec, 0x1c, dsi->lanes << 4);

	अगर (adv->use_timing_gen) अणु
		/* reset पूर्णांकernal timing generator */
		regmap_ग_लिखो(adv->regmap_cec, 0x27, 0xcb);
		regmap_ग_लिखो(adv->regmap_cec, 0x27, 0x8b);
		regmap_ग_लिखो(adv->regmap_cec, 0x27, 0xcb);
	पूर्ण अन्यथा अणु
		/* disable पूर्णांकernal timing generator */
		regmap_ग_लिखो(adv->regmap_cec, 0x27, 0x0b);
	पूर्ण

	/* enable hdmi */
	regmap_ग_लिखो(adv->regmap_cec, 0x03, 0x89);
	/* disable test mode */
	regmap_ग_लिखो(adv->regmap_cec, 0x55, 0x00);

	regmap_रेजिस्टर_patch(adv->regmap_cec, adv7533_cec_fixed_रेजिस्टरs,
			      ARRAY_SIZE(adv7533_cec_fixed_रेजिस्टरs));
पूर्ण

व्योम adv7533_dsi_घातer_off(काष्ठा adv7511 *adv)
अणु
	/* disable hdmi */
	regmap_ग_लिखो(adv->regmap_cec, 0x03, 0x0b);
	/* disable पूर्णांकernal timing generator */
	regmap_ग_लिखो(adv->regmap_cec, 0x27, 0x0b);
पूर्ण

व्योम adv7533_mode_set(काष्ठा adv7511 *adv, स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा mipi_dsi_device *dsi = adv->dsi;
	पूर्णांक lanes, ret;

	अगर (adv->num_dsi_lanes != 4)
		वापस;

	अगर (mode->घड़ी > 80000)
		lanes = 4;
	अन्यथा
		lanes = 3;

	अगर (lanes != dsi->lanes) अणु
		mipi_dsi_detach(dsi);
		dsi->lanes = lanes;
		ret = mipi_dsi_attach(dsi);
		अगर (ret)
			dev_err(&dsi->dev, "failed to change host lanes\n");
	पूर्ण
पूर्ण

पूर्णांक adv7533_patch_रेजिस्टरs(काष्ठा adv7511 *adv)
अणु
	वापस regmap_रेजिस्टर_patch(adv->regmap,
				     adv7533_fixed_रेजिस्टरs,
				     ARRAY_SIZE(adv7533_fixed_रेजिस्टरs));
पूर्ण

पूर्णांक adv7533_patch_cec_रेजिस्टरs(काष्ठा adv7511 *adv)
अणु
	वापस regmap_रेजिस्टर_patch(adv->regmap_cec,
				    adv7533_cec_fixed_रेजिस्टरs,
				    ARRAY_SIZE(adv7533_cec_fixed_रेजिस्टरs));
पूर्ण

पूर्णांक adv7533_attach_dsi(काष्ठा adv7511 *adv)
अणु
	काष्ठा device *dev = &adv->i2c_मुख्य->dev;
	काष्ठा mipi_dsi_host *host;
	काष्ठा mipi_dsi_device *dsi;
	पूर्णांक ret = 0;
	स्थिर काष्ठा mipi_dsi_device_info info = अणु .type = "adv7533",
						   .channel = 0,
						   .node = शून्य,
						 पूर्ण;

	host = of_find_mipi_dsi_host_by_node(adv->host_node);
	अगर (!host) अणु
		dev_err(dev, "failed to find dsi host\n");
		वापस -EPROBE_DEFER;
	पूर्ण

	dsi = mipi_dsi_device_रेजिस्टर_full(host, &info);
	अगर (IS_ERR(dsi)) अणु
		dev_err(dev, "failed to create dsi device\n");
		ret = PTR_ERR(dsi);
		जाओ err_dsi_device;
	पूर्ण

	adv->dsi = dsi;

	dsi->lanes = adv->num_dsi_lanes;
	dsi->क्रमmat = MIPI_DSI_FMT_RGB888;
	dsi->mode_flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_SYNC_PULSE |
			  MIPI_DSI_MODE_EOT_PACKET | MIPI_DSI_MODE_VIDEO_HSE;

	ret = mipi_dsi_attach(dsi);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to attach dsi to host\n");
		जाओ err_dsi_attach;
	पूर्ण

	वापस 0;

err_dsi_attach:
	mipi_dsi_device_unरेजिस्टर(dsi);
err_dsi_device:
	वापस ret;
पूर्ण

व्योम adv7533_detach_dsi(काष्ठा adv7511 *adv)
अणु
	mipi_dsi_detach(adv->dsi);
	mipi_dsi_device_unरेजिस्टर(adv->dsi);
पूर्ण

पूर्णांक adv7533_parse_dt(काष्ठा device_node *np, काष्ठा adv7511 *adv)
अणु
	u32 num_lanes;

	of_property_पढ़ो_u32(np, "adi,dsi-lanes", &num_lanes);

	अगर (num_lanes < 1 || num_lanes > 4)
		वापस -EINVAL;

	adv->num_dsi_lanes = num_lanes;

	adv->host_node = of_graph_get_remote_node(np, 0, 0);
	अगर (!adv->host_node)
		वापस -ENODEV;

	of_node_put(adv->host_node);

	adv->use_timing_gen = !of_property_पढ़ो_bool(np,
						"adi,disable-timing-generator");

	/* TODO: Check अगर these need to be parsed by DT or not */
	adv->rgb = true;
	adv->embedded_sync = false;

	वापस 0;
पूर्ण
