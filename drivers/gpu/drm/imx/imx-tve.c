<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * i.MX drm driver - Television Encoder (TVEv2)
 *
 * Copyright (C) 2013 Philipp Zabel, Pengutronix
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/clk.h>
#समावेश <linux/component.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/videodev2.h>

#समावेश <video/imx-ipu-v3.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_managed.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_simple_kms_helper.h>

#समावेश "imx-drm.h"

#घोषणा TVE_COM_CONF_REG	0x00
#घोषणा TVE_TVDAC0_CONT_REG	0x28
#घोषणा TVE_TVDAC1_CONT_REG	0x2c
#घोषणा TVE_TVDAC2_CONT_REG	0x30
#घोषणा TVE_CD_CONT_REG		0x34
#घोषणा TVE_INT_CONT_REG	0x64
#घोषणा TVE_STAT_REG		0x68
#घोषणा TVE_TST_MODE_REG	0x6c
#घोषणा TVE_MV_CONT_REG		0xdc

/* TVE_COM_CONF_REG */
#घोषणा TVE_SYNC_CH_2_EN	BIT(22)
#घोषणा TVE_SYNC_CH_1_EN	BIT(21)
#घोषणा TVE_SYNC_CH_0_EN	BIT(20)
#घोषणा TVE_TV_OUT_MODE_MASK	(0x7 << 12)
#घोषणा TVE_TV_OUT_DISABLE	(0x0 << 12)
#घोषणा TVE_TV_OUT_CVBS_0	(0x1 << 12)
#घोषणा TVE_TV_OUT_CVBS_2	(0x2 << 12)
#घोषणा TVE_TV_OUT_CVBS_0_2	(0x3 << 12)
#घोषणा TVE_TV_OUT_SVIDEO_0_1	(0x4 << 12)
#घोषणा TVE_TV_OUT_SVIDEO_0_1_CVBS2_2	(0x5 << 12)
#घोषणा TVE_TV_OUT_YPBPR	(0x6 << 12)
#घोषणा TVE_TV_OUT_RGB		(0x7 << 12)
#घोषणा TVE_TV_STAND_MASK	(0xf << 8)
#घोषणा TVE_TV_STAND_HD_1080P30	(0xc << 8)
#घोषणा TVE_P2I_CONV_EN		BIT(7)
#घोषणा TVE_INP_VIDEO_FORM	BIT(6)
#घोषणा TVE_INP_YCBCR_422	(0x0 << 6)
#घोषणा TVE_INP_YCBCR_444	(0x1 << 6)
#घोषणा TVE_DATA_SOURCE_MASK	(0x3 << 4)
#घोषणा TVE_DATA_SOURCE_BUS1	(0x0 << 4)
#घोषणा TVE_DATA_SOURCE_BUS2	(0x1 << 4)
#घोषणा TVE_DATA_SOURCE_EXT	(0x2 << 4)
#घोषणा TVE_DATA_SOURCE_TESTGEN	(0x3 << 4)
#घोषणा TVE_IPU_CLK_EN_OFS	3
#घोषणा TVE_IPU_CLK_EN		BIT(3)
#घोषणा TVE_DAC_SAMP_RATE_OFS	1
#घोषणा TVE_DAC_SAMP_RATE_WIDTH	2
#घोषणा TVE_DAC_SAMP_RATE_MASK	(0x3 << 1)
#घोषणा TVE_DAC_FULL_RATE	(0x0 << 1)
#घोषणा TVE_DAC_DIV2_RATE	(0x1 << 1)
#घोषणा TVE_DAC_DIV4_RATE	(0x2 << 1)
#घोषणा TVE_EN			BIT(0)

/* TVE_TVDACx_CONT_REG */
#घोषणा TVE_TVDAC_GAIN_MASK	(0x3f << 0)

/* TVE_CD_CONT_REG */
#घोषणा TVE_CD_CH_2_SM_EN	BIT(22)
#घोषणा TVE_CD_CH_1_SM_EN	BIT(21)
#घोषणा TVE_CD_CH_0_SM_EN	BIT(20)
#घोषणा TVE_CD_CH_2_LM_EN	BIT(18)
#घोषणा TVE_CD_CH_1_LM_EN	BIT(17)
#घोषणा TVE_CD_CH_0_LM_EN	BIT(16)
#घोषणा TVE_CD_CH_2_REF_LVL	BIT(10)
#घोषणा TVE_CD_CH_1_REF_LVL	BIT(9)
#घोषणा TVE_CD_CH_0_REF_LVL	BIT(8)
#घोषणा TVE_CD_EN		BIT(0)

/* TVE_INT_CONT_REG */
#घोषणा TVE_FRAME_END_IEN	BIT(13)
#घोषणा TVE_CD_MON_END_IEN	BIT(2)
#घोषणा TVE_CD_SM_IEN		BIT(1)
#घोषणा TVE_CD_LM_IEN		BIT(0)

/* TVE_TST_MODE_REG */
#घोषणा TVE_TVDAC_TEST_MODE_MASK	(0x7 << 0)

#घोषणा IMX_TVE_DAC_VOLTAGE	2750000

क्रमागत अणु
	TVE_MODE_TVOUT,
	TVE_MODE_VGA,
पूर्ण;

काष्ठा imx_tve_encoder अणु
	काष्ठा drm_connector connector;
	काष्ठा drm_encoder encoder;
	काष्ठा imx_tve *tve;
पूर्ण;

काष्ठा imx_tve अणु
	काष्ठा device *dev;
	पूर्णांक mode;
	पूर्णांक di_hsync_pin;
	पूर्णांक di_vsync_pin;

	काष्ठा regmap *regmap;
	काष्ठा regulator *dac_reg;
	काष्ठा i2c_adapter *ddc;
	काष्ठा clk *clk;
	काष्ठा clk *di_sel_clk;
	काष्ठा clk_hw clk_hw_di;
	काष्ठा clk *di_clk;
पूर्ण;

अटल अंतरभूत काष्ठा imx_tve *con_to_tve(काष्ठा drm_connector *c)
अणु
	वापस container_of(c, काष्ठा imx_tve_encoder, connector)->tve;
पूर्ण

अटल अंतरभूत काष्ठा imx_tve *enc_to_tve(काष्ठा drm_encoder *e)
अणु
	वापस container_of(e, काष्ठा imx_tve_encoder, encoder)->tve;
पूर्ण

अटल व्योम tve_enable(काष्ठा imx_tve *tve)
अणु
	clk_prepare_enable(tve->clk);
	regmap_update_bits(tve->regmap, TVE_COM_CONF_REG, TVE_EN, TVE_EN);

	/* clear पूर्णांकerrupt status रेजिस्टर */
	regmap_ग_लिखो(tve->regmap, TVE_STAT_REG, 0xffffffff);

	/* cable detection irq disabled in VGA mode, enabled in TVOUT mode */
	अगर (tve->mode == TVE_MODE_VGA)
		regmap_ग_लिखो(tve->regmap, TVE_INT_CONT_REG, 0);
	अन्यथा
		regmap_ग_लिखो(tve->regmap, TVE_INT_CONT_REG,
			     TVE_CD_SM_IEN |
			     TVE_CD_LM_IEN |
			     TVE_CD_MON_END_IEN);
पूर्ण

अटल व्योम tve_disable(काष्ठा imx_tve *tve)
अणु
	regmap_update_bits(tve->regmap, TVE_COM_CONF_REG, TVE_EN, 0);
	clk_disable_unprepare(tve->clk);
पूर्ण

अटल पूर्णांक tve_setup_tvout(काष्ठा imx_tve *tve)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल पूर्णांक tve_setup_vga(काष्ठा imx_tve *tve)
अणु
	अचिन्हित पूर्णांक mask;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	/* set gain to (1 + 10/128) to provide 0.7V peak-to-peak amplitude */
	ret = regmap_update_bits(tve->regmap, TVE_TVDAC0_CONT_REG,
				 TVE_TVDAC_GAIN_MASK, 0x0a);
	अगर (ret)
		वापस ret;

	ret = regmap_update_bits(tve->regmap, TVE_TVDAC1_CONT_REG,
				 TVE_TVDAC_GAIN_MASK, 0x0a);
	अगर (ret)
		वापस ret;

	ret = regmap_update_bits(tve->regmap, TVE_TVDAC2_CONT_REG,
				 TVE_TVDAC_GAIN_MASK, 0x0a);
	अगर (ret)
		वापस ret;

	/* set configuration रेजिस्टर */
	mask = TVE_DATA_SOURCE_MASK | TVE_INP_VIDEO_FORM;
	val  = TVE_DATA_SOURCE_BUS2 | TVE_INP_YCBCR_444;
	mask |= TVE_TV_STAND_MASK       | TVE_P2I_CONV_EN;
	val  |= TVE_TV_STAND_HD_1080P30 | 0;
	mask |= TVE_TV_OUT_MODE_MASK | TVE_SYNC_CH_0_EN;
	val  |= TVE_TV_OUT_RGB       | TVE_SYNC_CH_0_EN;
	ret = regmap_update_bits(tve->regmap, TVE_COM_CONF_REG, mask, val);
	अगर (ret)
		वापस ret;

	/* set test mode (as करोcumented) */
	वापस regmap_update_bits(tve->regmap, TVE_TST_MODE_REG,
				 TVE_TVDAC_TEST_MODE_MASK, 1);
पूर्ण

अटल पूर्णांक imx_tve_connector_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा imx_tve *tve = con_to_tve(connector);
	काष्ठा edid *edid;
	पूर्णांक ret = 0;

	अगर (!tve->ddc)
		वापस 0;

	edid = drm_get_edid(connector, tve->ddc);
	अगर (edid) अणु
		drm_connector_update_edid_property(connector, edid);
		ret = drm_add_edid_modes(connector, edid);
		kमुक्त(edid);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक imx_tve_connector_mode_valid(काष्ठा drm_connector *connector,
					काष्ठा drm_display_mode *mode)
अणु
	काष्ठा imx_tve *tve = con_to_tve(connector);
	अचिन्हित दीर्घ rate;

	/* pixel घड़ी with 2x oversampling */
	rate = clk_round_rate(tve->clk, 2000UL * mode->घड़ी) / 2000;
	अगर (rate == mode->घड़ी)
		वापस MODE_OK;

	/* pixel घड़ी without oversampling */
	rate = clk_round_rate(tve->clk, 1000UL * mode->घड़ी) / 1000;
	अगर (rate == mode->घड़ी)
		वापस MODE_OK;

	dev_warn(tve->dev, "ignoring mode %dx%d\n",
		 mode->hdisplay, mode->vdisplay);

	वापस MODE_BAD;
पूर्ण

अटल व्योम imx_tve_encoder_mode_set(काष्ठा drm_encoder *encoder,
				     काष्ठा drm_display_mode *orig_mode,
				     काष्ठा drm_display_mode *mode)
अणु
	काष्ठा imx_tve *tve = enc_to_tve(encoder);
	अचिन्हित दीर्घ rounded_rate;
	अचिन्हित दीर्घ rate;
	पूर्णांक भाग = 1;
	पूर्णांक ret;

	/*
	 * FIXME
	 * we should try 4k * mode->घड़ी first,
	 * and enable 4x oversampling क्रम lower resolutions
	 */
	rate = 2000UL * mode->घड़ी;
	clk_set_rate(tve->clk, rate);
	rounded_rate = clk_get_rate(tve->clk);
	अगर (rounded_rate >= rate)
		भाग = 2;
	clk_set_rate(tve->di_clk, rounded_rate / भाग);

	ret = clk_set_parent(tve->di_sel_clk, tve->di_clk);
	अगर (ret < 0) अणु
		dev_err(tve->dev, "failed to set di_sel parent to tve_di: %d\n",
			ret);
	पूर्ण

	regmap_update_bits(tve->regmap, TVE_COM_CONF_REG,
			   TVE_IPU_CLK_EN, TVE_IPU_CLK_EN);

	अगर (tve->mode == TVE_MODE_VGA)
		ret = tve_setup_vga(tve);
	अन्यथा
		ret = tve_setup_tvout(tve);
	अगर (ret)
		dev_err(tve->dev, "failed to set configuration: %d\n", ret);
पूर्ण

अटल व्योम imx_tve_encoder_enable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा imx_tve *tve = enc_to_tve(encoder);

	tve_enable(tve);
पूर्ण

अटल व्योम imx_tve_encoder_disable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा imx_tve *tve = enc_to_tve(encoder);

	tve_disable(tve);
पूर्ण

अटल पूर्णांक imx_tve_atomic_check(काष्ठा drm_encoder *encoder,
				काष्ठा drm_crtc_state *crtc_state,
				काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा imx_crtc_state *imx_crtc_state = to_imx_crtc_state(crtc_state);
	काष्ठा imx_tve *tve = enc_to_tve(encoder);

	imx_crtc_state->bus_क्रमmat = MEDIA_BUS_FMT_GBR888_1X24;
	imx_crtc_state->di_hsync_pin = tve->di_hsync_pin;
	imx_crtc_state->di_vsync_pin = tve->di_vsync_pin;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs imx_tve_connector_funcs = अणु
	.fill_modes = drm_helper_probe_single_connector_modes,
	.destroy = imx_drm_connector_destroy,
	.reset = drm_atomic_helper_connector_reset,
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_helper_funcs imx_tve_connector_helper_funcs = अणु
	.get_modes = imx_tve_connector_get_modes,
	.mode_valid = imx_tve_connector_mode_valid,
पूर्ण;

अटल स्थिर काष्ठा drm_encoder_helper_funcs imx_tve_encoder_helper_funcs = अणु
	.mode_set = imx_tve_encoder_mode_set,
	.enable = imx_tve_encoder_enable,
	.disable = imx_tve_encoder_disable,
	.atomic_check = imx_tve_atomic_check,
पूर्ण;

अटल irqवापस_t imx_tve_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा imx_tve *tve = data;
	अचिन्हित पूर्णांक val;

	regmap_पढ़ो(tve->regmap, TVE_STAT_REG, &val);

	/* clear पूर्णांकerrupt status रेजिस्टर */
	regmap_ग_लिखो(tve->regmap, TVE_STAT_REG, 0xffffffff);

	वापस IRQ_HANDLED;
पूर्ण

अटल अचिन्हित दीर्घ clk_tve_di_recalc_rate(काष्ठा clk_hw *hw,
					    अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा imx_tve *tve = container_of(hw, काष्ठा imx_tve, clk_hw_di);
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(tve->regmap, TVE_COM_CONF_REG, &val);
	अगर (ret < 0)
		वापस 0;

	चयन (val & TVE_DAC_SAMP_RATE_MASK) अणु
	हाल TVE_DAC_DIV4_RATE:
		वापस parent_rate / 4;
	हाल TVE_DAC_DIV2_RATE:
		वापस parent_rate / 2;
	हाल TVE_DAC_FULL_RATE:
	शेष:
		वापस parent_rate;
	पूर्ण

	वापस 0;
पूर्ण

अटल दीर्घ clk_tve_di_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				  अचिन्हित दीर्घ *prate)
अणु
	अचिन्हित दीर्घ भाग;

	भाग = *prate / rate;
	अगर (भाग >= 4)
		वापस *prate / 4;
	अन्यथा अगर (भाग >= 2)
		वापस *prate / 2;
	वापस *prate;
पूर्ण

अटल पूर्णांक clk_tve_di_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			       अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा imx_tve *tve = container_of(hw, काष्ठा imx_tve, clk_hw_di);
	अचिन्हित दीर्घ भाग;
	u32 val;
	पूर्णांक ret;

	भाग = parent_rate / rate;
	अगर (भाग >= 4)
		val = TVE_DAC_DIV4_RATE;
	अन्यथा अगर (भाग >= 2)
		val = TVE_DAC_DIV2_RATE;
	अन्यथा
		val = TVE_DAC_FULL_RATE;

	ret = regmap_update_bits(tve->regmap, TVE_COM_CONF_REG,
				 TVE_DAC_SAMP_RATE_MASK, val);

	अगर (ret < 0) अणु
		dev_err(tve->dev, "failed to set divider: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_tve_di_ops = अणु
	.round_rate = clk_tve_di_round_rate,
	.set_rate = clk_tve_di_set_rate,
	.recalc_rate = clk_tve_di_recalc_rate,
पूर्ण;

अटल पूर्णांक tve_clk_init(काष्ठा imx_tve *tve, व्योम __iomem *base)
अणु
	स्थिर अक्षर *tve_di_parent[1];
	काष्ठा clk_init_data init = अणु
		.name = "tve_di",
		.ops = &clk_tve_di_ops,
		.num_parents = 1,
		.flags = 0,
	पूर्ण;

	tve_di_parent[0] = __clk_get_name(tve->clk);
	init.parent_names = (स्थिर अक्षर **)&tve_di_parent;

	tve->clk_hw_di.init = &init;
	tve->di_clk = devm_clk_रेजिस्टर(tve->dev, &tve->clk_hw_di);
	अगर (IS_ERR(tve->di_clk)) अणु
		dev_err(tve->dev, "failed to register TVE output clock: %ld\n",
			PTR_ERR(tve->di_clk));
		वापस PTR_ERR(tve->di_clk);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम imx_tve_disable_regulator(व्योम *data)
अणु
	काष्ठा imx_tve *tve = data;

	regulator_disable(tve->dac_reg);
पूर्ण

अटल bool imx_tve_पढ़ोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	वापस (reg % 4 == 0) && (reg <= 0xdc);
पूर्ण

अटल काष्ठा regmap_config tve_regmap_config = अणु
	.reg_bits = 32,
	.val_bits = 32,
	.reg_stride = 4,

	.पढ़ोable_reg = imx_tve_पढ़ोable_reg,

	.fast_io = true,

	.max_रेजिस्टर = 0xdc,
पूर्ण;

अटल स्थिर अक्षर * स्थिर imx_tve_modes[] = अणु
	[TVE_MODE_TVOUT]  = "tvout",
	[TVE_MODE_VGA] = "vga",
पूर्ण;

अटल पूर्णांक of_get_tve_mode(काष्ठा device_node *np)
अणु
	स्थिर अक्षर *bm;
	पूर्णांक ret, i;

	ret = of_property_पढ़ो_string(np, "fsl,tve-mode", &bm);
	अगर (ret < 0)
		वापस ret;

	क्रम (i = 0; i < ARRAY_SIZE(imx_tve_modes); i++)
		अगर (!strहालcmp(bm, imx_tve_modes[i]))
			वापस i;

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक imx_tve_bind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	काष्ठा drm_device *drm = data;
	काष्ठा imx_tve *tve = dev_get_drvdata(dev);
	काष्ठा imx_tve_encoder *tvee;
	काष्ठा drm_encoder *encoder;
	काष्ठा drm_connector *connector;
	पूर्णांक encoder_type;
	पूर्णांक ret;

	encoder_type = tve->mode == TVE_MODE_VGA ?
		       DRM_MODE_ENCODER_DAC : DRM_MODE_ENCODER_TVDAC;

	tvee = drmm_simple_encoder_alloc(drm, काष्ठा imx_tve_encoder, encoder,
					 encoder_type);
	अगर (IS_ERR(tvee))
		वापस PTR_ERR(tvee);

	tvee->tve = tve;
	encoder = &tvee->encoder;
	connector = &tvee->connector;

	ret = imx_drm_encoder_parse_of(drm, encoder, tve->dev->of_node);
	अगर (ret)
		वापस ret;

	drm_encoder_helper_add(encoder, &imx_tve_encoder_helper_funcs);

	drm_connector_helper_add(connector, &imx_tve_connector_helper_funcs);
	ret = drm_connector_init_with_ddc(drm, connector,
					  &imx_tve_connector_funcs,
					  DRM_MODE_CONNECTOR_VGA, tve->ddc);
	अगर (ret)
		वापस ret;

	वापस drm_connector_attach_encoder(connector, encoder);
पूर्ण

अटल स्थिर काष्ठा component_ops imx_tve_ops = अणु
	.bind	= imx_tve_bind,
पूर्ण;

अटल पूर्णांक imx_tve_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा device_node *ddc_node;
	काष्ठा imx_tve *tve;
	काष्ठा resource *res;
	व्योम __iomem *base;
	अचिन्हित पूर्णांक val;
	पूर्णांक irq;
	पूर्णांक ret;

	tve = devm_kzalloc(dev, माप(*tve), GFP_KERNEL);
	अगर (!tve)
		वापस -ENOMEM;

	tve->dev = dev;

	ddc_node = of_parse_phandle(np, "ddc-i2c-bus", 0);
	अगर (ddc_node) अणु
		tve->ddc = of_find_i2c_adapter_by_node(ddc_node);
		of_node_put(ddc_node);
	पूर्ण

	tve->mode = of_get_tve_mode(np);
	अगर (tve->mode != TVE_MODE_VGA) अणु
		dev_err(dev, "only VGA mode supported, currently\n");
		वापस -EINVAL;
	पूर्ण

	अगर (tve->mode == TVE_MODE_VGA) अणु
		ret = of_property_पढ़ो_u32(np, "fsl,hsync-pin",
					   &tve->di_hsync_pin);

		अगर (ret < 0) अणु
			dev_err(dev, "failed to get hsync pin\n");
			वापस ret;
		पूर्ण

		ret = of_property_पढ़ो_u32(np, "fsl,vsync-pin",
					   &tve->di_vsync_pin);

		अगर (ret < 0) अणु
			dev_err(dev, "failed to get vsync pin\n");
			वापस ret;
		पूर्ण
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	tve_regmap_config.lock_arg = tve;
	tve->regmap = devm_regmap_init_mmio_clk(dev, "tve", base,
						&tve_regmap_config);
	अगर (IS_ERR(tve->regmap)) अणु
		dev_err(dev, "failed to init regmap: %ld\n",
			PTR_ERR(tve->regmap));
		वापस PTR_ERR(tve->regmap);
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	ret = devm_request_thपढ़ोed_irq(dev, irq, शून्य,
					imx_tve_irq_handler, IRQF_ONESHOT,
					"imx-tve", tve);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to request irq: %d\n", ret);
		वापस ret;
	पूर्ण

	tve->dac_reg = devm_regulator_get(dev, "dac");
	अगर (!IS_ERR(tve->dac_reg)) अणु
		अगर (regulator_get_voltage(tve->dac_reg) != IMX_TVE_DAC_VOLTAGE)
			dev_warn(dev, "dac voltage is not %d uV\n", IMX_TVE_DAC_VOLTAGE);
		ret = regulator_enable(tve->dac_reg);
		अगर (ret)
			वापस ret;
		ret = devm_add_action_or_reset(dev, imx_tve_disable_regulator, tve);
		अगर (ret)
			वापस ret;
	पूर्ण

	tve->clk = devm_clk_get(dev, "tve");
	अगर (IS_ERR(tve->clk)) अणु
		dev_err(dev, "failed to get high speed tve clock: %ld\n",
			PTR_ERR(tve->clk));
		वापस PTR_ERR(tve->clk);
	पूर्ण

	/* this is the IPU DI घड़ी input selector, can be parented to tve_di */
	tve->di_sel_clk = devm_clk_get(dev, "di_sel");
	अगर (IS_ERR(tve->di_sel_clk)) अणु
		dev_err(dev, "failed to get ipu di mux clock: %ld\n",
			PTR_ERR(tve->di_sel_clk));
		वापस PTR_ERR(tve->di_sel_clk);
	पूर्ण

	ret = tve_clk_init(tve, base);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_पढ़ो(tve->regmap, TVE_COM_CONF_REG, &val);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to read configuration register: %d\n",
			ret);
		वापस ret;
	पूर्ण
	अगर (val != 0x00100000) अणु
		dev_err(dev, "configuration register default value indicates this is not a TVEv2\n");
		वापस -ENODEV;
	पूर्ण

	/* disable cable detection क्रम VGA mode */
	ret = regmap_ग_लिखो(tve->regmap, TVE_CD_CONT_REG, 0);
	अगर (ret)
		वापस ret;

	platक्रमm_set_drvdata(pdev, tve);

	वापस component_add(dev, &imx_tve_ops);
पूर्ण

अटल पूर्णांक imx_tve_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	component_del(&pdev->dev, &imx_tve_ops);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id imx_tve_dt_ids[] = अणु
	अणु .compatible = "fsl,imx53-tve", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, imx_tve_dt_ids);

अटल काष्ठा platक्रमm_driver imx_tve_driver = अणु
	.probe		= imx_tve_probe,
	.हटाओ		= imx_tve_हटाओ,
	.driver		= अणु
		.of_match_table = imx_tve_dt_ids,
		.name	= "imx-tve",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(imx_tve_driver);

MODULE_DESCRIPTION("i.MX Television Encoder driver");
MODULE_AUTHOR("Philipp Zabel, Pengutronix");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:imx-tve");
