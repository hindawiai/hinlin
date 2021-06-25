<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2017 Linaro Ltd.
 * Copyright 2017 ZTE Corporation.
 */

#समावेश <linux/clk.h>
#समावेश <linux/component.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_simple_kms_helper.h>

#समावेश "zx_drm_drv.h"
#समावेश "zx_tvenc_regs.h"
#समावेश "zx_vou.h"

काष्ठा zx_tvenc_pwrctrl अणु
	काष्ठा regmap *regmap;
	u32 reg;
	u32 mask;
पूर्ण;

काष्ठा zx_tvenc अणु
	काष्ठा drm_connector connector;
	काष्ठा drm_encoder encoder;
	काष्ठा device *dev;
	व्योम __iomem *mmio;
	स्थिर काष्ठा vou_inf *inf;
	काष्ठा zx_tvenc_pwrctrl pwrctrl;
पूर्ण;

#घोषणा to_zx_tvenc(x) container_of(x, काष्ठा zx_tvenc, x)

काष्ठा zx_tvenc_mode अणु
	काष्ठा drm_display_mode mode;
	u32 video_info;
	u32 video_res;
	u32 field1_param;
	u32 field2_param;
	u32 burst_line_odd1;
	u32 burst_line_even1;
	u32 burst_line_odd2;
	u32 burst_line_even2;
	u32 line_timing_param;
	u32 weight_value;
	u32 blank_black_level;
	u32 burst_level;
	u32 control_param;
	u32 sub_carrier_phase1;
	u32 phase_line_incr_cvbs;
पूर्ण;

/*
 * The CRM cannot directly provide a suitable frequency, and we have to
 * ask a multiplied rate from CRM and use the भागider in VOU to get the
 * desired one.
 */
#घोषणा TVENC_CLOCK_MULTIPLIER	4

अटल स्थिर काष्ठा zx_tvenc_mode tvenc_mode_pal = अणु
	.mode = अणु
		.घड़ी = 13500 * TVENC_CLOCK_MULTIPLIER,
		.hdisplay = 720,
		.hsync_start = 720 + 12,
		.hsync_end = 720 + 12 + 2,
		.htotal = 720 + 12 + 2 + 130,
		.vdisplay = 576,
		.vsync_start = 576 + 2,
		.vsync_end = 576 + 2 + 2,
		.vtotal = 576 + 2 + 2 + 20,
		.flags = DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
			 DRM_MODE_FLAG_INTERLACE,
	पूर्ण,
	.video_info = 0x00040040,
	.video_res = 0x05a9c760,
	.field1_param = 0x0004d416,
	.field2_param = 0x0009b94f,
	.burst_line_odd1 = 0x0004d406,
	.burst_line_even1 = 0x0009b53e,
	.burst_line_odd2 = 0x0004d805,
	.burst_line_even2 = 0x0009b93f,
	.line_timing_param = 0x06a96fdf,
	.weight_value = 0x00c188a0,
	.blank_black_level = 0x0000fcfc,
	.burst_level = 0x00001595,
	.control_param = 0x00000001,
	.sub_carrier_phase1 = 0x1504c566,
	.phase_line_incr_cvbs = 0xc068db8c,
पूर्ण;

अटल स्थिर काष्ठा zx_tvenc_mode tvenc_mode_ntsc = अणु
	.mode = अणु
		.घड़ी = 13500 * TVENC_CLOCK_MULTIPLIER,
		.hdisplay = 720,
		.hsync_start = 720 + 16,
		.hsync_end = 720 + 16 + 2,
		.htotal = 720 + 16 + 2 + 120,
		.vdisplay = 480,
		.vsync_start = 480 + 3,
		.vsync_end = 480 + 3 + 2,
		.vtotal = 480 + 3 + 2 + 17,
		.flags = DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
			 DRM_MODE_FLAG_INTERLACE,
	पूर्ण,
	.video_info = 0x00040080,
	.video_res = 0x05a8375a,
	.field1_param = 0x00041817,
	.field2_param = 0x0008351e,
	.burst_line_odd1 = 0x00041006,
	.burst_line_even1 = 0x0008290d,
	.burst_line_odd2 = 0x00000000,
	.burst_line_even2 = 0x00000000,
	.line_timing_param = 0x06a8ef9e,
	.weight_value = 0x00b68197,
	.blank_black_level = 0x0000f0f0,
	.burst_level = 0x0000009c,
	.control_param = 0x00000001,
	.sub_carrier_phase1 = 0x10f83e10,
	.phase_line_incr_cvbs = 0x80000000,
पूर्ण;

अटल स्थिर काष्ठा zx_tvenc_mode *tvenc_modes[] = अणु
	&tvenc_mode_pal,
	&tvenc_mode_ntsc,
पूर्ण;

अटल स्थिर काष्ठा zx_tvenc_mode *
zx_tvenc_find_zmode(काष्ठा drm_display_mode *mode)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(tvenc_modes); i++) अणु
		स्थिर काष्ठा zx_tvenc_mode *zmode = tvenc_modes[i];

		अगर (drm_mode_equal(mode, &zmode->mode))
			वापस zmode;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम zx_tvenc_encoder_mode_set(काष्ठा drm_encoder *encoder,
				      काष्ठा drm_display_mode *mode,
				      काष्ठा drm_display_mode *adj_mode)
अणु
	काष्ठा zx_tvenc *tvenc = to_zx_tvenc(encoder);
	स्थिर काष्ठा zx_tvenc_mode *zmode;
	काष्ठा vou_भाग_config configs[] = अणु
		अणु VOU_DIV_INF,   VOU_DIV_4 पूर्ण,
		अणु VOU_DIV_TVENC, VOU_DIV_1 पूर्ण,
		अणु VOU_DIV_LAYER, VOU_DIV_2 पूर्ण,
	पूर्ण;

	zx_vou_config_भागiders(encoder->crtc, configs, ARRAY_SIZE(configs));

	zmode = zx_tvenc_find_zmode(mode);
	अगर (!zmode) अणु
		DRM_DEV_ERROR(tvenc->dev, "failed to find zmode\n");
		वापस;
	पूर्ण

	zx_ग_लिखोl(tvenc->mmio + VENC_VIDEO_INFO, zmode->video_info);
	zx_ग_लिखोl(tvenc->mmio + VENC_VIDEO_RES, zmode->video_res);
	zx_ग_लिखोl(tvenc->mmio + VENC_FIELD1_PARAM, zmode->field1_param);
	zx_ग_लिखोl(tvenc->mmio + VENC_FIELD2_PARAM, zmode->field2_param);
	zx_ग_लिखोl(tvenc->mmio + VENC_LINE_O_1, zmode->burst_line_odd1);
	zx_ग_लिखोl(tvenc->mmio + VENC_LINE_E_1, zmode->burst_line_even1);
	zx_ग_लिखोl(tvenc->mmio + VENC_LINE_O_2, zmode->burst_line_odd2);
	zx_ग_लिखोl(tvenc->mmio + VENC_LINE_E_2, zmode->burst_line_even2);
	zx_ग_लिखोl(tvenc->mmio + VENC_LINE_TIMING_PARAM,
		  zmode->line_timing_param);
	zx_ग_लिखोl(tvenc->mmio + VENC_WEIGHT_VALUE, zmode->weight_value);
	zx_ग_लिखोl(tvenc->mmio + VENC_BLANK_BLACK_LEVEL,
		  zmode->blank_black_level);
	zx_ग_लिखोl(tvenc->mmio + VENC_BURST_LEVEL, zmode->burst_level);
	zx_ग_लिखोl(tvenc->mmio + VENC_CONTROL_PARAM, zmode->control_param);
	zx_ग_लिखोl(tvenc->mmio + VENC_SUB_CARRIER_PHASE1,
		  zmode->sub_carrier_phase1);
	zx_ग_लिखोl(tvenc->mmio + VENC_PHASE_LINE_INCR_CVBS,
		  zmode->phase_line_incr_cvbs);
पूर्ण

अटल व्योम zx_tvenc_encoder_enable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा zx_tvenc *tvenc = to_zx_tvenc(encoder);
	काष्ठा zx_tvenc_pwrctrl *pwrctrl = &tvenc->pwrctrl;

	/* Set bit to घातer up TVENC DAC */
	regmap_update_bits(pwrctrl->regmap, pwrctrl->reg, pwrctrl->mask,
			   pwrctrl->mask);

	vou_inf_enable(VOU_TV_ENC, encoder->crtc);

	zx_ग_लिखोl(tvenc->mmio + VENC_ENABLE, 1);
पूर्ण

अटल व्योम zx_tvenc_encoder_disable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा zx_tvenc *tvenc = to_zx_tvenc(encoder);
	काष्ठा zx_tvenc_pwrctrl *pwrctrl = &tvenc->pwrctrl;

	zx_ग_लिखोl(tvenc->mmio + VENC_ENABLE, 0);

	vou_inf_disable(VOU_TV_ENC, encoder->crtc);

	/* Clear bit to घातer करोwn TVENC DAC */
	regmap_update_bits(pwrctrl->regmap, pwrctrl->reg, pwrctrl->mask, 0);
पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs zx_tvenc_encoder_helper_funcs = अणु
	.enable	= zx_tvenc_encoder_enable,
	.disable = zx_tvenc_encoder_disable,
	.mode_set = zx_tvenc_encoder_mode_set,
पूर्ण;

अटल पूर्णांक zx_tvenc_connector_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा zx_tvenc *tvenc = to_zx_tvenc(connector);
	काष्ठा device *dev = tvenc->dev;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(tvenc_modes); i++) अणु
		स्थिर काष्ठा zx_tvenc_mode *zmode = tvenc_modes[i];
		काष्ठा drm_display_mode *mode;

		mode = drm_mode_duplicate(connector->dev, &zmode->mode);
		अगर (!mode) अणु
			DRM_DEV_ERROR(dev, "failed to duplicate drm mode\n");
			जारी;
		पूर्ण

		drm_mode_set_name(mode);
		drm_mode_probed_add(connector, mode);
	पूर्ण

	वापस i;
पूर्ण

अटल क्रमागत drm_mode_status
zx_tvenc_connector_mode_valid(काष्ठा drm_connector *connector,
			      काष्ठा drm_display_mode *mode)
अणु
	काष्ठा zx_tvenc *tvenc = to_zx_tvenc(connector);
	स्थिर काष्ठा zx_tvenc_mode *zmode;

	zmode = zx_tvenc_find_zmode(mode);
	अगर (!zmode) अणु
		DRM_DEV_ERROR(tvenc->dev, "unsupported mode: %s\n", mode->name);
		वापस MODE_NOMODE;
	पूर्ण

	वापस MODE_OK;
पूर्ण

अटल काष्ठा drm_connector_helper_funcs zx_tvenc_connector_helper_funcs = अणु
	.get_modes = zx_tvenc_connector_get_modes,
	.mode_valid = zx_tvenc_connector_mode_valid,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_funcs zx_tvenc_connector_funcs = अणु
	.fill_modes = drm_helper_probe_single_connector_modes,
	.destroy = drm_connector_cleanup,
	.reset = drm_atomic_helper_connector_reset,
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
पूर्ण;

अटल पूर्णांक zx_tvenc_रेजिस्टर(काष्ठा drm_device *drm, काष्ठा zx_tvenc *tvenc)
अणु
	काष्ठा drm_encoder *encoder = &tvenc->encoder;
	काष्ठा drm_connector *connector = &tvenc->connector;

	/*
	 * The tvenc is deचिन्हित to use aux channel, as there is a deflicker
	 * block क्रम the channel.
	 */
	encoder->possible_crtcs = BIT(1);

	drm_simple_encoder_init(drm, encoder, DRM_MODE_ENCODER_TVDAC);
	drm_encoder_helper_add(encoder, &zx_tvenc_encoder_helper_funcs);

	connector->पूर्णांकerlace_allowed = true;

	drm_connector_init(drm, connector, &zx_tvenc_connector_funcs,
			   DRM_MODE_CONNECTOR_Composite);
	drm_connector_helper_add(connector, &zx_tvenc_connector_helper_funcs);

	drm_connector_attach_encoder(connector, encoder);

	वापस 0;
पूर्ण

अटल पूर्णांक zx_tvenc_pwrctrl_init(काष्ठा zx_tvenc *tvenc)
अणु
	काष्ठा zx_tvenc_pwrctrl *pwrctrl = &tvenc->pwrctrl;
	काष्ठा device *dev = tvenc->dev;
	काष्ठा of_phandle_args out_args;
	काष्ठा regmap *regmap;
	पूर्णांक ret;

	ret = of_parse_phandle_with_fixed_args(dev->of_node,
				"zte,tvenc-power-control", 2, 0, &out_args);
	अगर (ret)
		वापस ret;

	regmap = syscon_node_to_regmap(out_args.np);
	अगर (IS_ERR(regmap)) अणु
		ret = PTR_ERR(regmap);
		जाओ out;
	पूर्ण

	pwrctrl->regmap = regmap;
	pwrctrl->reg = out_args.args[0];
	pwrctrl->mask = out_args.args[1];

out:
	of_node_put(out_args.np);
	वापस ret;
पूर्ण

अटल पूर्णांक zx_tvenc_bind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा drm_device *drm = data;
	काष्ठा resource *res;
	काष्ठा zx_tvenc *tvenc;
	पूर्णांक ret;

	tvenc = devm_kzalloc(dev, माप(*tvenc), GFP_KERNEL);
	अगर (!tvenc)
		वापस -ENOMEM;

	tvenc->dev = dev;
	dev_set_drvdata(dev, tvenc);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	tvenc->mmio = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(tvenc->mmio)) अणु
		ret = PTR_ERR(tvenc->mmio);
		DRM_DEV_ERROR(dev, "failed to remap tvenc region: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = zx_tvenc_pwrctrl_init(tvenc);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev, "failed to init power control: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = zx_tvenc_रेजिस्टर(drm, tvenc);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev, "failed to register tvenc: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम zx_tvenc_unbind(काष्ठा device *dev, काष्ठा device *master,
			    व्योम *data)
अणु
	/* Nothing to करो */
पूर्ण

अटल स्थिर काष्ठा component_ops zx_tvenc_component_ops = अणु
	.bind = zx_tvenc_bind,
	.unbind = zx_tvenc_unbind,
पूर्ण;

अटल पूर्णांक zx_tvenc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस component_add(&pdev->dev, &zx_tvenc_component_ops);
पूर्ण

अटल पूर्णांक zx_tvenc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	component_del(&pdev->dev, &zx_tvenc_component_ops);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id zx_tvenc_of_match[] = अणु
	अणु .compatible = "zte,zx296718-tvenc", पूर्ण,
	अणु /* end */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, zx_tvenc_of_match);

काष्ठा platक्रमm_driver zx_tvenc_driver = अणु
	.probe = zx_tvenc_probe,
	.हटाओ = zx_tvenc_हटाओ,
	.driver	= अणु
		.name = "zx-tvenc",
		.of_match_table	= zx_tvenc_of_match,
	पूर्ण,
पूर्ण;
