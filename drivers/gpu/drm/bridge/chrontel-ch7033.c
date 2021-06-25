<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Chrontel CH7033 Video Encoder Driver
 *
 * Copyright (C) 2019,2020 Lubomir Rपूर्णांकel
 */

#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_edid.h>
#समावेश <drm/drm_of.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_probe_helper.h>

/* Page 0, Register 0x07 */
क्रमागत अणु
	DRI_PD		= BIT(3),
	IO_PD		= BIT(5),
पूर्ण;

/* Page 0, Register 0x08 */
क्रमागत अणु
	DRI_PDDRI	= GENMASK(7, 4),
	PDDAC		= GENMASK(3, 1),
	PANEN		= BIT(0),
पूर्ण;

/* Page 0, Register 0x09 */
क्रमागत अणु
	DPD		= BIT(7),
	GCKOFF		= BIT(6),
	TV_BP		= BIT(5),
	SCLPD		= BIT(4),
	SDPD		= BIT(3),
	VGA_PD		= BIT(2),
	HDBKPD		= BIT(1),
	HDMI_PD		= BIT(0),
पूर्ण;

/* Page 0, Register 0x0a */
क्रमागत अणु
	MEMINIT		= BIT(7),
	MEMIDLE		= BIT(6),
	MEMPD		= BIT(5),
	STOP		= BIT(4),
	LVDS_PD		= BIT(3),
	HD_DVIB		= BIT(2),
	HDCP_PD		= BIT(1),
	MCU_PD		= BIT(0),
पूर्ण;

/* Page 0, Register 0x18 */
क्रमागत अणु
	IDF		= GENMASK(7, 4),
	INTEN		= BIT(3),
	SWAP		= GENMASK(2, 0),
पूर्ण;

क्रमागत अणु
	BYTE_SWAP_RGB	= 0,
	BYTE_SWAP_RBG	= 1,
	BYTE_SWAP_GRB	= 2,
	BYTE_SWAP_GBR	= 3,
	BYTE_SWAP_BRG	= 4,
	BYTE_SWAP_BGR	= 5,
पूर्ण;

/* Page 0, Register 0x19 */
क्रमागत अणु
	HPO_I		= BIT(5),
	VPO_I		= BIT(4),
	DEPO_I		= BIT(3),
	CRYS_EN		= BIT(2),
	GCLKFREQ	= GENMASK(2, 0),
पूर्ण;

/* Page 0, Register 0x2e */
क्रमागत अणु
	HFLIP		= BIT(7),
	VFLIP		= BIT(6),
	DEPO_O		= BIT(5),
	HPO_O		= BIT(4),
	VPO_O		= BIT(3),
	TE		= GENMASK(2, 0),
पूर्ण;

/* Page 0, Register 0x2b */
क्रमागत अणु
	SWAPS		= GENMASK(7, 4),
	VFMT		= GENMASK(3, 0),
पूर्ण;

/* Page 0, Register 0x54 */
क्रमागत अणु
	COMP_BP		= BIT(7),
	DAC_EN_T	= BIT(6),
	HWO_HDMI_HI	= GENMASK(5, 3),
	HOO_HDMI_HI	= GENMASK(2, 0),
पूर्ण;

/* Page 0, Register 0x57 */
क्रमागत अणु
	FLDSEN		= BIT(7),
	VWO_HDMI_HI	= GENMASK(5, 3),
	VOO_HDMI_HI	= GENMASK(2, 0),
पूर्ण;

/* Page 0, Register 0x7e */
क्रमागत अणु
	HDMI_LVDS_SEL	= BIT(7),
	DE_GEN		= BIT(6),
	PWM_INDEX_HI	= BIT(5),
	USE_DE		= BIT(4),
	R_INT		= GENMASK(3, 0),
पूर्ण;

/* Page 1, Register 0x07 */
क्रमागत अणु
	BPCKSEL		= BIT(7),
	DRI_CMFB_EN	= BIT(6),
	CEC_PUEN	= BIT(5),
	CEC_T		= BIT(3),
	CKINV		= BIT(2),
	CK_TVINV	= BIT(1),
	DRI_CKS2	= BIT(0),
पूर्ण;

/* Page 1, Register 0x08 */
क्रमागत अणु
	DACG		= BIT(6),
	DACKTST		= BIT(5),
	DEDGEB		= BIT(4),
	SYO		= BIT(3),
	DRI_IT_LVDS	= GENMASK(2, 1),
	DISPON		= BIT(0),
पूर्ण;

/* Page 1, Register 0x0c */
क्रमागत अणु
	DRI_PLL_CP	= GENMASK(7, 6),
	DRI_PLL_DIVSEL	= BIT(5),
	DRI_PLL_N1_1	= BIT(4),
	DRI_PLL_N1_0	= BIT(3),
	DRI_PLL_N3_1	= BIT(2),
	DRI_PLL_N3_0	= BIT(1),
	DRI_PLL_CKTSTEN = BIT(0),
पूर्ण;

/* Page 1, Register 0x6b */
क्रमागत अणु
	VCO3CS		= GENMASK(7, 6),
	ICPGBK2_0	= GENMASK(5, 3),
	DRI_VCO357SC	= BIT(2),
	PDPLL2		= BIT(1),
	DRI_PD_SER	= BIT(0),
पूर्ण;

/* Page 1, Register 0x6c */
क्रमागत अणु
	PLL2N11		= GENMASK(7, 4),
	PLL2N5_4	= BIT(3),
	PLL2N5_TOP	= BIT(2),
	DRI_PLL_PD	= BIT(1),
	PD_I2CM		= BIT(0),
पूर्ण;

/* Page 3, Register 0x28 */
क्रमागत अणु
	DIFF_EN		= GENMASK(7, 6),
	CORREC_EN	= GENMASK(5, 4),
	VGACLK_BP	= BIT(3),
	HM_LV_SEL	= BIT(2),
	HD_VGA_SEL	= BIT(1),
पूर्ण;

/* Page 3, Register 0x2a */
क्रमागत अणु
	LVDSCLK_BP	= BIT(7),
	HDTVCLK_BP	= BIT(6),
	HDMICLK_BP	= BIT(5),
	HDTV_BP		= BIT(4),
	HDMI_BP		= BIT(3),
	THRWL		= GENMASK(2, 0),
पूर्ण;

/* Page 4, Register 0x52 */
क्रमागत अणु
	PGM_ARSTB	= BIT(7),
	MCU_ARSTB	= BIT(6),
	MCU_RETB	= BIT(2),
	RESETIB		= BIT(1),
	RESETDB		= BIT(0),
पूर्ण;

काष्ठा ch7033_priv अणु
	काष्ठा regmap *regmap;
	काष्ठा drm_bridge *next_bridge;
	काष्ठा drm_bridge bridge;
	काष्ठा drm_connector connector;
पूर्ण;

#घोषणा conn_to_ch7033_priv(x) \
	container_of(x, काष्ठा ch7033_priv, connector)
#घोषणा bridge_to_ch7033_priv(x) \
	container_of(x, काष्ठा ch7033_priv, bridge)


अटल क्रमागत drm_connector_status ch7033_connector_detect(
	काष्ठा drm_connector *connector, bool क्रमce)
अणु
	काष्ठा ch7033_priv *priv = conn_to_ch7033_priv(connector);

	वापस drm_bridge_detect(priv->next_bridge);
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs ch7033_connector_funcs = अणु
	.reset = drm_atomic_helper_connector_reset,
	.fill_modes = drm_helper_probe_single_connector_modes,
	.detect = ch7033_connector_detect,
	.destroy = drm_connector_cleanup,
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
पूर्ण;

अटल पूर्णांक ch7033_connector_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा ch7033_priv *priv = conn_to_ch7033_priv(connector);
	काष्ठा edid *edid;
	पूर्णांक ret;

	edid = drm_bridge_get_edid(priv->next_bridge, connector);
	drm_connector_update_edid_property(connector, edid);
	अगर (edid) अणु
		ret = drm_add_edid_modes(connector, edid);
		kमुक्त(edid);
	पूर्ण अन्यथा अणु
		ret = drm_add_modes_noedid(connector, 1920, 1080);
		drm_set_preferred_mode(connector, 1024, 768);
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा drm_encoder *ch7033_connector_best_encoder(
			काष्ठा drm_connector *connector)
अणु
	काष्ठा ch7033_priv *priv = conn_to_ch7033_priv(connector);

	वापस priv->bridge.encoder;
पूर्ण

अटल स्थिर काष्ठा drm_connector_helper_funcs ch7033_connector_helper_funcs = अणु
	.get_modes = ch7033_connector_get_modes,
	.best_encoder = ch7033_connector_best_encoder,
पूर्ण;

अटल व्योम ch7033_hpd_event(व्योम *arg, क्रमागत drm_connector_status status)
अणु
	काष्ठा ch7033_priv *priv = arg;

	अगर (priv->bridge.dev)
		drm_helper_hpd_irq_event(priv->connector.dev);
पूर्ण

अटल पूर्णांक ch7033_bridge_attach(काष्ठा drm_bridge *bridge,
				क्रमागत drm_bridge_attach_flags flags)
अणु
	काष्ठा ch7033_priv *priv = bridge_to_ch7033_priv(bridge);
	काष्ठा drm_connector *connector = &priv->connector;
	पूर्णांक ret;

	ret = drm_bridge_attach(bridge->encoder, priv->next_bridge, bridge,
				DRM_BRIDGE_ATTACH_NO_CONNECTOR);
	अगर (ret)
		वापस ret;

	अगर (flags & DRM_BRIDGE_ATTACH_NO_CONNECTOR)
		वापस 0;

	अगर (priv->next_bridge->ops & DRM_BRIDGE_OP_DETECT) अणु
		connector->polled = DRM_CONNECTOR_POLL_HPD;
	पूर्ण अन्यथा अणु
		connector->polled = DRM_CONNECTOR_POLL_CONNECT |
				    DRM_CONNECTOR_POLL_DISCONNECT;
	पूर्ण

	अगर (priv->next_bridge->ops & DRM_BRIDGE_OP_HPD) अणु
		drm_bridge_hpd_enable(priv->next_bridge, ch7033_hpd_event,
				      priv);
	पूर्ण

	drm_connector_helper_add(connector,
				 &ch7033_connector_helper_funcs);
	ret = drm_connector_init_with_ddc(bridge->dev, &priv->connector,
					  &ch7033_connector_funcs,
					  priv->next_bridge->type,
					  priv->next_bridge->ddc);
	अगर (ret) अणु
		DRM_ERROR("Failed to initialize connector\n");
		वापस ret;
	पूर्ण

	वापस drm_connector_attach_encoder(&priv->connector, bridge->encoder);
पूर्ण

अटल व्योम ch7033_bridge_detach(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा ch7033_priv *priv = bridge_to_ch7033_priv(bridge);

	अगर (priv->next_bridge->ops & DRM_BRIDGE_OP_HPD)
		drm_bridge_hpd_disable(priv->next_bridge);
	drm_connector_cleanup(&priv->connector);
पूर्ण

अटल क्रमागत drm_mode_status ch7033_bridge_mode_valid(काष्ठा drm_bridge *bridge,
				     स्थिर काष्ठा drm_display_info *info,
				     स्थिर काष्ठा drm_display_mode *mode)
अणु
	अगर (mode->घड़ी > 165000)
		वापस MODE_CLOCK_HIGH;
	अगर (mode->hdisplay >= 1920)
		वापस MODE_BAD_HVALUE;
	अगर (mode->vdisplay >= 1080)
		वापस MODE_BAD_VVALUE;
	वापस MODE_OK;
पूर्ण

अटल व्योम ch7033_bridge_disable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा ch7033_priv *priv = bridge_to_ch7033_priv(bridge);

	regmap_ग_लिखो(priv->regmap, 0x03, 0x04);
	regmap_update_bits(priv->regmap, 0x52, RESETDB, 0x00);
पूर्ण

अटल व्योम ch7033_bridge_enable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा ch7033_priv *priv = bridge_to_ch7033_priv(bridge);

	regmap_ग_लिखो(priv->regmap, 0x03, 0x04);
	regmap_update_bits(priv->regmap, 0x52, RESETDB, RESETDB);
पूर्ण

अटल व्योम ch7033_bridge_mode_set(काष्ठा drm_bridge *bridge,
				   स्थिर काष्ठा drm_display_mode *mode,
				   स्थिर काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा ch7033_priv *priv = bridge_to_ch7033_priv(bridge);
	पूर्णांक hbporch = mode->hsync_start - mode->hdisplay;
	पूर्णांक hsynclen = mode->hsync_end - mode->hsync_start;
	पूर्णांक vbporch = mode->vsync_start - mode->vdisplay;
	पूर्णांक vsynclen = mode->vsync_end - mode->vsync_start;

	/*
	 * Page 4
	 */
	regmap_ग_लिखो(priv->regmap, 0x03, 0x04);

	/* Turn everything off to set all the रेजिस्टरs to their शेषs. */
	regmap_ग_लिखो(priv->regmap, 0x52, 0x00);
	/* Bring I/O block up. */
	regmap_ग_लिखो(priv->regmap, 0x52, RESETIB);

	/*
	 * Page 0
	 */
	regmap_ग_लिखो(priv->regmap, 0x03, 0x00);

	/* Bring up parts we need from the घातer करोwn. */
	regmap_update_bits(priv->regmap, 0x07, DRI_PD | IO_PD, 0);
	regmap_update_bits(priv->regmap, 0x08, DRI_PDDRI | PDDAC | PANEN, 0);
	regmap_update_bits(priv->regmap, 0x09, DPD | GCKOFF |
					       HDMI_PD | VGA_PD, 0);
	regmap_update_bits(priv->regmap, 0x0a, HD_DVIB, 0);

	/* Horizontal input timing. */
	regmap_ग_लिखो(priv->regmap, 0x0b, (mode->htotal >> 8) << 3 |
					 (mode->hdisplay >> 8));
	regmap_ग_लिखो(priv->regmap, 0x0c, mode->hdisplay);
	regmap_ग_लिखो(priv->regmap, 0x0d, mode->htotal);
	regmap_ग_लिखो(priv->regmap, 0x0e, (hsynclen >> 8) << 3 |
					 (hbporch >> 8));
	regmap_ग_लिखो(priv->regmap, 0x0f, hbporch);
	regmap_ग_लिखो(priv->regmap, 0x10, hsynclen);

	/* Vertical input timing. */
	regmap_ग_लिखो(priv->regmap, 0x11, (mode->vtotal >> 8) << 3 |
					 (mode->vdisplay >> 8));
	regmap_ग_लिखो(priv->regmap, 0x12, mode->vdisplay);
	regmap_ग_लिखो(priv->regmap, 0x13, mode->vtotal);
	regmap_ग_लिखो(priv->regmap, 0x14, ((vsynclen >> 8) << 3) |
					 (vbporch >> 8));
	regmap_ग_लिखो(priv->regmap, 0x15, vbporch);
	regmap_ग_लिखो(priv->regmap, 0x16, vsynclen);

	/* Input color swap. */
	regmap_update_bits(priv->regmap, 0x18, SWAP, BYTE_SWAP_BGR);

	/* Input घड़ी and sync polarity. */
	regmap_update_bits(priv->regmap, 0x19, 0x1, mode->घड़ी >> 16);
	regmap_update_bits(priv->regmap, 0x19, HPO_I | VPO_I | GCLKFREQ,
			   (mode->flags & DRM_MODE_FLAG_PHSYNC) ? HPO_I : 0 |
			   (mode->flags & DRM_MODE_FLAG_PVSYNC) ? VPO_I : 0 |
			   mode->घड़ी >> 16);
	regmap_ग_लिखो(priv->regmap, 0x1a, mode->घड़ी >> 8);
	regmap_ग_लिखो(priv->regmap, 0x1b, mode->घड़ी);

	/* Horizontal output timing. */
	regmap_ग_लिखो(priv->regmap, 0x1f, (mode->htotal >> 8) << 3 |
					 (mode->hdisplay >> 8));
	regmap_ग_लिखो(priv->regmap, 0x20, mode->hdisplay);
	regmap_ग_लिखो(priv->regmap, 0x21, mode->htotal);

	/* Vertical output timing. */
	regmap_ग_लिखो(priv->regmap, 0x25, (mode->vtotal >> 8) << 3 |
					 (mode->vdisplay >> 8));
	regmap_ग_लिखो(priv->regmap, 0x26, mode->vdisplay);
	regmap_ग_लिखो(priv->regmap, 0x27, mode->vtotal);

	/* VGA channel bypass */
	regmap_update_bits(priv->regmap, 0x2b, VFMT, 9);

	/* Output sync polarity. */
	regmap_update_bits(priv->regmap, 0x2e, HPO_O | VPO_O,
			   (mode->flags & DRM_MODE_FLAG_PHSYNC) ? HPO_O : 0 |
			   (mode->flags & DRM_MODE_FLAG_PVSYNC) ? VPO_O : 0);

	/* HDMI horizontal output timing. */
	regmap_update_bits(priv->regmap, 0x54, HWO_HDMI_HI | HOO_HDMI_HI,
					       (hsynclen >> 8) << 3 |
					       (hbporch >> 8));
	regmap_ग_लिखो(priv->regmap, 0x55, hbporch);
	regmap_ग_लिखो(priv->regmap, 0x56, hsynclen);

	/* HDMI vertical output timing. */
	regmap_update_bits(priv->regmap, 0x57, VWO_HDMI_HI | VOO_HDMI_HI,
					       (vsynclen >> 8) << 3 |
					       (vbporch >> 8));
	regmap_ग_लिखो(priv->regmap, 0x58, vbporch);
	regmap_ग_लिखो(priv->regmap, 0x59, vsynclen);

	/* Pick HDMI, not LVDS. */
	regmap_update_bits(priv->regmap, 0x7e, HDMI_LVDS_SEL, HDMI_LVDS_SEL);

	/*
	 * Page 1
	 */
	regmap_ग_लिखो(priv->regmap, 0x03, 0x01);

	/* No idea what these करो, but VGA is wobbly and blinky without them. */
	regmap_update_bits(priv->regmap, 0x07, CKINV, CKINV);
	regmap_update_bits(priv->regmap, 0x08, DISPON, DISPON);

	/* DRI PLL */
	regmap_update_bits(priv->regmap, 0x0c, DRI_PLL_DIVSEL, DRI_PLL_DIVSEL);
	अगर (mode->घड़ी <= 40000) अणु
		regmap_update_bits(priv->regmap, 0x0c, DRI_PLL_N1_1 |
						       DRI_PLL_N1_0 |
						       DRI_PLL_N3_1 |
						       DRI_PLL_N3_0,
						       0);
	पूर्ण अन्यथा अगर (mode->घड़ी < 80000) अणु
		regmap_update_bits(priv->regmap, 0x0c, DRI_PLL_N1_1 |
						       DRI_PLL_N1_0 |
						       DRI_PLL_N3_1 |
						       DRI_PLL_N3_0,
						       DRI_PLL_N3_0 |
						       DRI_PLL_N1_0);
	पूर्ण अन्यथा अणु
		regmap_update_bits(priv->regmap, 0x0c, DRI_PLL_N1_1 |
						       DRI_PLL_N1_0 |
						       DRI_PLL_N3_1 |
						       DRI_PLL_N3_0,
						       DRI_PLL_N3_1 |
						       DRI_PLL_N1_1);
	पूर्ण

	/* This seems to be color calibration क्रम VGA. */
	regmap_ग_लिखो(priv->regmap, 0x64, 0x29); /* LSB Blue */
	regmap_ग_लिखो(priv->regmap, 0x65, 0x29); /* LSB Green */
	regmap_ग_लिखो(priv->regmap, 0x66, 0x29); /* LSB Red */
	regmap_ग_लिखो(priv->regmap, 0x67, 0x00); /* MSB Blue */
	regmap_ग_लिखो(priv->regmap, 0x68, 0x00); /* MSB Green */
	regmap_ग_लिखो(priv->regmap, 0x69, 0x00); /* MSB Red */

	regmap_update_bits(priv->regmap, 0x6b, DRI_PD_SER, 0x00);
	regmap_update_bits(priv->regmap, 0x6c, DRI_PLL_PD, 0x00);

	/*
	 * Page 3
	 */
	regmap_ग_लिखो(priv->regmap, 0x03, 0x03);

	/* More bypasses and apparently another HDMI/LVDS selector. */
	regmap_update_bits(priv->regmap, 0x28, VGACLK_BP | HM_LV_SEL,
					       VGACLK_BP | HM_LV_SEL);
	regmap_update_bits(priv->regmap, 0x2a, HDMICLK_BP | HDMI_BP,
					       HDMICLK_BP | HDMI_BP);

	/*
	 * Page 4
	 */
	regmap_ग_लिखो(priv->regmap, 0x03, 0x04);

	/* Output घड़ी. */
	regmap_ग_लिखो(priv->regmap, 0x10, mode->घड़ी >> 16);
	regmap_ग_लिखो(priv->regmap, 0x11, mode->घड़ी >> 8);
	regmap_ग_लिखो(priv->regmap, 0x12, mode->घड़ी);
पूर्ण

अटल स्थिर काष्ठा drm_bridge_funcs ch7033_bridge_funcs = अणु
	.attach = ch7033_bridge_attach,
	.detach = ch7033_bridge_detach,
	.mode_valid = ch7033_bridge_mode_valid,
	.disable = ch7033_bridge_disable,
	.enable = ch7033_bridge_enable,
	.mode_set = ch7033_bridge_mode_set,
पूर्ण;

अटल स्थिर काष्ठा regmap_config ch7033_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = 0x7f,
पूर्ण;

अटल पूर्णांक ch7033_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा ch7033_priv *priv;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	dev_set_drvdata(dev, priv);

	ret = drm_of_find_panel_or_bridge(dev->of_node, 1, -1, शून्य,
					  &priv->next_bridge);
	अगर (ret)
		वापस ret;

	priv->regmap = devm_regmap_init_i2c(client, &ch7033_regmap_config);
	अगर (IS_ERR(priv->regmap)) अणु
		dev_err(&client->dev, "regmap init failed\n");
		वापस PTR_ERR(priv->regmap);
	पूर्ण

	ret = regmap_पढ़ो(priv->regmap, 0x00, &val);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "error reading the model id: %d\n", ret);
		वापस ret;
	पूर्ण
	अगर ((val & 0xf7) != 0x56) अणु
		dev_err(&client->dev, "the device is not a ch7033\n");
		वापस -ENODEV;
	पूर्ण

	regmap_ग_लिखो(priv->regmap, 0x03, 0x04);
	ret = regmap_पढ़ो(priv->regmap, 0x51, &val);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "error reading the model id: %d\n", ret);
		वापस ret;
	पूर्ण
	अगर ((val & 0x0f) != 3) अणु
		dev_err(&client->dev, "unknown revision %u\n", val);
		वापस -ENODEV;
	पूर्ण

	INIT_LIST_HEAD(&priv->bridge.list);
	priv->bridge.funcs = &ch7033_bridge_funcs;
	priv->bridge.of_node = dev->of_node;
	drm_bridge_add(&priv->bridge);

	dev_info(dev, "Chrontel CH7033 Video Encoder\n");
	वापस 0;
पूर्ण

अटल पूर्णांक ch7033_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा ch7033_priv *priv = dev_get_drvdata(dev);

	drm_bridge_हटाओ(&priv->bridge);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ch7033_dt_ids[] = अणु
	अणु .compatible = "chrontel,ch7033", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ch7033_dt_ids);

अटल स्थिर काष्ठा i2c_device_id ch7033_ids[] = अणु
	अणु "ch7033", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ch7033_ids);

अटल काष्ठा i2c_driver ch7033_driver = अणु
	.probe = ch7033_probe,
	.हटाओ = ch7033_हटाओ,
	.driver = अणु
		.name = "ch7033",
		.of_match_table = of_match_ptr(ch7033_dt_ids),
	पूर्ण,
	.id_table = ch7033_ids,
पूर्ण;

module_i2c_driver(ch7033_driver);

MODULE_AUTHOR("Lubomir Rintel <lkundrak@v3.sk>");
MODULE_DESCRIPTION("Chrontel CH7033 Video Encoder Driver");
MODULE_LICENSE("GPL v2");
