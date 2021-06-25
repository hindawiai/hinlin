<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012 Avionic Design GmbH
 * Copyright (C) 2012 NVIDIA CORPORATION.  All rights reserved.
 */

#समावेश <linux/clk.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_bridge_connector.h>
#समावेश <drm/drm_simple_kms_helper.h>

#समावेश "drm.h"
#समावेश "dc.h"

काष्ठा tegra_rgb अणु
	काष्ठा tegra_output output;
	काष्ठा tegra_dc *dc;

	काष्ठा clk *clk_parent;
	काष्ठा clk *clk;
पूर्ण;

अटल अंतरभूत काष्ठा tegra_rgb *to_rgb(काष्ठा tegra_output *output)
अणु
	वापस container_of(output, काष्ठा tegra_rgb, output);
पूर्ण

काष्ठा reg_entry अणु
	अचिन्हित दीर्घ offset;
	अचिन्हित दीर्घ value;
पूर्ण;

अटल स्थिर काष्ठा reg_entry rgb_enable[] = अणु
	अणु DC_COM_PIN_OUTPUT_ENABLE(0),   0x00000000 पूर्ण,
	अणु DC_COM_PIN_OUTPUT_ENABLE(1),   0x00000000 पूर्ण,
	अणु DC_COM_PIN_OUTPUT_ENABLE(2),   0x00000000 पूर्ण,
	अणु DC_COM_PIN_OUTPUT_ENABLE(3),   0x00000000 पूर्ण,
	अणु DC_COM_PIN_OUTPUT_POLARITY(0), 0x00000000 पूर्ण,
	अणु DC_COM_PIN_OUTPUT_POLARITY(1), 0x01000000 पूर्ण,
	अणु DC_COM_PIN_OUTPUT_POLARITY(2), 0x00000000 पूर्ण,
	अणु DC_COM_PIN_OUTPUT_POLARITY(3), 0x00000000 पूर्ण,
	अणु DC_COM_PIN_OUTPUT_DATA(0),     0x00000000 पूर्ण,
	अणु DC_COM_PIN_OUTPUT_DATA(1),     0x00000000 पूर्ण,
	अणु DC_COM_PIN_OUTPUT_DATA(2),     0x00000000 पूर्ण,
	अणु DC_COM_PIN_OUTPUT_DATA(3),     0x00000000 पूर्ण,
	अणु DC_COM_PIN_OUTPUT_SELECT(0),   0x00000000 पूर्ण,
	अणु DC_COM_PIN_OUTPUT_SELECT(1),   0x00000000 पूर्ण,
	अणु DC_COM_PIN_OUTPUT_SELECT(2),   0x00000000 पूर्ण,
	अणु DC_COM_PIN_OUTPUT_SELECT(3),   0x00000000 पूर्ण,
	अणु DC_COM_PIN_OUTPUT_SELECT(4),   0x00210222 पूर्ण,
	अणु DC_COM_PIN_OUTPUT_SELECT(5),   0x00002200 पूर्ण,
	अणु DC_COM_PIN_OUTPUT_SELECT(6),   0x00020000 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_entry rgb_disable[] = अणु
	अणु DC_COM_PIN_OUTPUT_SELECT(6),   0x00000000 पूर्ण,
	अणु DC_COM_PIN_OUTPUT_SELECT(5),   0x00000000 पूर्ण,
	अणु DC_COM_PIN_OUTPUT_SELECT(4),   0x00000000 पूर्ण,
	अणु DC_COM_PIN_OUTPUT_SELECT(3),   0x00000000 पूर्ण,
	अणु DC_COM_PIN_OUTPUT_SELECT(2),   0x00000000 पूर्ण,
	अणु DC_COM_PIN_OUTPUT_SELECT(1),   0x00000000 पूर्ण,
	अणु DC_COM_PIN_OUTPUT_SELECT(0),   0x00000000 पूर्ण,
	अणु DC_COM_PIN_OUTPUT_DATA(3),     0xaaaaaaaa पूर्ण,
	अणु DC_COM_PIN_OUTPUT_DATA(2),     0xaaaaaaaa पूर्ण,
	अणु DC_COM_PIN_OUTPUT_DATA(1),     0xaaaaaaaa पूर्ण,
	अणु DC_COM_PIN_OUTPUT_DATA(0),     0xaaaaaaaa पूर्ण,
	अणु DC_COM_PIN_OUTPUT_POLARITY(3), 0x00000000 पूर्ण,
	अणु DC_COM_PIN_OUTPUT_POLARITY(2), 0x00000000 पूर्ण,
	अणु DC_COM_PIN_OUTPUT_POLARITY(1), 0x00000000 पूर्ण,
	अणु DC_COM_PIN_OUTPUT_POLARITY(0), 0x00000000 पूर्ण,
	अणु DC_COM_PIN_OUTPUT_ENABLE(3),   0x55555555 पूर्ण,
	अणु DC_COM_PIN_OUTPUT_ENABLE(2),   0x55555555 पूर्ण,
	अणु DC_COM_PIN_OUTPUT_ENABLE(1),   0x55150005 पूर्ण,
	अणु DC_COM_PIN_OUTPUT_ENABLE(0),   0x55555555 पूर्ण,
पूर्ण;

अटल व्योम tegra_dc_ग_लिखो_regs(काष्ठा tegra_dc *dc,
				स्थिर काष्ठा reg_entry *table,
				अचिन्हित पूर्णांक num)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < num; i++)
		tegra_dc_ग_लिखोl(dc, table[i].value, table[i].offset);
पूर्ण

अटल व्योम tegra_rgb_encoder_disable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा tegra_output *output = encoder_to_output(encoder);
	काष्ठा tegra_rgb *rgb = to_rgb(output);

	tegra_dc_ग_लिखो_regs(rgb->dc, rgb_disable, ARRAY_SIZE(rgb_disable));
	tegra_dc_commit(rgb->dc);
पूर्ण

अटल व्योम tegra_rgb_encoder_enable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा tegra_output *output = encoder_to_output(encoder);
	काष्ठा tegra_rgb *rgb = to_rgb(output);
	u32 value;

	tegra_dc_ग_लिखो_regs(rgb->dc, rgb_enable, ARRAY_SIZE(rgb_enable));

	value = DE_SELECT_ACTIVE | DE_CONTROL_NORMAL;
	tegra_dc_ग_लिखोl(rgb->dc, value, DC_DISP_DATA_ENABLE_OPTIONS);

	/* XXX: parameterize? */
	value = tegra_dc_पढ़ोl(rgb->dc, DC_COM_PIN_OUTPUT_POLARITY(1));
	value &= ~LVS_OUTPUT_POLARITY_LOW;
	value &= ~LHS_OUTPUT_POLARITY_LOW;
	tegra_dc_ग_लिखोl(rgb->dc, value, DC_COM_PIN_OUTPUT_POLARITY(1));

	/* XXX: parameterize? */
	value = DISP_DATA_FORMAT_DF1P1C | DISP_ALIGNMENT_MSB |
		DISP_ORDER_RED_BLUE;
	tegra_dc_ग_लिखोl(rgb->dc, value, DC_DISP_DISP_INTERFACE_CONTROL);

	/* XXX: parameterize? */
	value = SC0_H_QUALIFIER_NONE | SC1_H_QUALIFIER_NONE;
	tegra_dc_ग_लिखोl(rgb->dc, value, DC_DISP_SHIFT_CLOCK_OPTIONS);

	tegra_dc_commit(rgb->dc);
पूर्ण

अटल पूर्णांक
tegra_rgb_encoder_atomic_check(काष्ठा drm_encoder *encoder,
			       काष्ठा drm_crtc_state *crtc_state,
			       काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा tegra_output *output = encoder_to_output(encoder);
	काष्ठा tegra_dc *dc = to_tegra_dc(conn_state->crtc);
	अचिन्हित दीर्घ pclk = crtc_state->mode.घड़ी * 1000;
	काष्ठा tegra_rgb *rgb = to_rgb(output);
	अचिन्हित पूर्णांक भाग;
	पूर्णांक err;

	/*
	 * We may not want to change the frequency of the parent घड़ी, since
	 * it may be a parent क्रम other peripherals. This is due to the fact
	 * that on Tegra20 there's only a single घड़ी dedicated to display
	 * (pll_d_out0), whereas later generations have a second one that can
	 * be used to independently drive a second output (pll_d2_out0).
	 *
	 * As a way to support multiple outमाला_दो on Tegra20 as well, pll_p is
	 * typically used as the parent घड़ी क्रम the display controllers.
	 * But this comes at a cost: pll_p is the parent of several other
	 * peripherals, so its frequency shouldn't change out of the blue.
	 *
	 * The best we can करो at this poपूर्णांक is to use the shअगरt घड़ी भागider
	 * and hope that the desired frequency can be matched (or at least
	 * matched sufficiently बंद that the panel will still work).
	 */
	भाग = ((clk_get_rate(rgb->clk) * 2) / pclk) - 2;
	pclk = 0;

	err = tegra_dc_state_setup_घड़ी(dc, crtc_state, rgb->clk_parent,
					 pclk, भाग);
	अगर (err < 0) अणु
		dev_err(output->dev, "failed to setup CRTC state: %d\n", err);
		वापस err;
	पूर्ण

	वापस err;
पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs tegra_rgb_encoder_helper_funcs = अणु
	.disable = tegra_rgb_encoder_disable,
	.enable = tegra_rgb_encoder_enable,
	.atomic_check = tegra_rgb_encoder_atomic_check,
पूर्ण;

पूर्णांक tegra_dc_rgb_probe(काष्ठा tegra_dc *dc)
अणु
	काष्ठा device_node *np;
	काष्ठा tegra_rgb *rgb;
	पूर्णांक err;

	np = of_get_child_by_name(dc->dev->of_node, "rgb");
	अगर (!np || !of_device_is_available(np))
		वापस -ENODEV;

	rgb = devm_kzalloc(dc->dev, माप(*rgb), GFP_KERNEL);
	अगर (!rgb)
		वापस -ENOMEM;

	rgb->output.dev = dc->dev;
	rgb->output.of_node = np;
	rgb->dc = dc;

	err = tegra_output_probe(&rgb->output);
	अगर (err < 0)
		वापस err;

	rgb->clk = devm_clk_get(dc->dev, शून्य);
	अगर (IS_ERR(rgb->clk)) अणु
		dev_err(dc->dev, "failed to get clock\n");
		वापस PTR_ERR(rgb->clk);
	पूर्ण

	rgb->clk_parent = devm_clk_get(dc->dev, "parent");
	अगर (IS_ERR(rgb->clk_parent)) अणु
		dev_err(dc->dev, "failed to get parent clock\n");
		वापस PTR_ERR(rgb->clk_parent);
	पूर्ण

	err = clk_set_parent(rgb->clk, rgb->clk_parent);
	अगर (err < 0) अणु
		dev_err(dc->dev, "failed to set parent clock: %d\n", err);
		वापस err;
	पूर्ण

	dc->rgb = &rgb->output;

	वापस 0;
पूर्ण

पूर्णांक tegra_dc_rgb_हटाओ(काष्ठा tegra_dc *dc)
अणु
	अगर (!dc->rgb)
		वापस 0;

	tegra_output_हटाओ(dc->rgb);
	dc->rgb = शून्य;

	वापस 0;
पूर्ण

पूर्णांक tegra_dc_rgb_init(काष्ठा drm_device *drm, काष्ठा tegra_dc *dc)
अणु
	काष्ठा tegra_output *output = dc->rgb;
	काष्ठा drm_connector *connector;
	पूर्णांक err;

	अगर (!dc->rgb)
		वापस -ENODEV;

	drm_simple_encoder_init(drm, &output->encoder, DRM_MODE_ENCODER_LVDS);
	drm_encoder_helper_add(&output->encoder,
			       &tegra_rgb_encoder_helper_funcs);

	/*
	 * Wrap directly-connected panel पूर्णांकo DRM bridge in order to let
	 * DRM core to handle panel क्रम us.
	 */
	अगर (output->panel) अणु
		output->bridge = devm_drm_panel_bridge_add(output->dev,
							   output->panel);
		अगर (IS_ERR(output->bridge)) अणु
			dev_err(output->dev,
				"failed to wrap panel into bridge: %pe\n",
				output->bridge);
			वापस PTR_ERR(output->bridge);
		पूर्ण

		output->panel = शून्य;
	पूर्ण

	/*
	 * Tegra devices that have LVDS panel utilize LVDS encoder bridge
	 * क्रम converting up to 28 LCD LVTTL lanes पूर्णांकo 5/4 LVDS lanes that
	 * go to display panel's receiver.
	 *
	 * Encoder usually have a घातer-करोwn control which needs to be enabled
	 * in order to transmit data to the panel.  Historically devices that
	 * use an older device-tree version didn't model the bridge, assuming
	 * that encoder is turned ON by शेष, जबतक today's DRM allows us
	 * to model LVDS encoder properly.
	 *
	 * Newer device-trees utilize LVDS encoder bridge, which provides
	 * us with a connector and handles the display panel.
	 *
	 * For older device-trees we wrapped panel पूर्णांकo the panel-bridge.
	 */
	अगर (output->bridge) अणु
		err = drm_bridge_attach(&output->encoder, output->bridge,
					शून्य, DRM_BRIDGE_ATTACH_NO_CONNECTOR);
		अगर (err) अणु
			dev_err(output->dev, "failed to attach bridge: %d\n",
				err);
			वापस err;
		पूर्ण

		connector = drm_bridge_connector_init(drm, &output->encoder);
		अगर (IS_ERR(connector)) अणु
			dev_err(output->dev,
				"failed to initialize bridge connector: %pe\n",
				connector);
			वापस PTR_ERR(connector);
		पूर्ण

		drm_connector_attach_encoder(connector, &output->encoder);
	पूर्ण

	err = tegra_output_init(drm, output);
	अगर (err < 0) अणु
		dev_err(output->dev, "failed to initialize output: %d\n", err);
		वापस err;
	पूर्ण

	/*
	 * Other outमाला_दो can be attached to either display controller. The RGB
	 * outमाला_दो are an exception and work only with their parent display
	 * controller.
	 */
	output->encoder.possible_crtcs = drm_crtc_mask(&dc->base);

	वापस 0;
पूर्ण

पूर्णांक tegra_dc_rgb_निकास(काष्ठा tegra_dc *dc)
अणु
	अगर (dc->rgb)
		tegra_output_निकास(dc->rgb);

	वापस 0;
पूर्ण
