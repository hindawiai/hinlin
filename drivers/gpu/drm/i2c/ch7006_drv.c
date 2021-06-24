<शैली गुरु>
/*
 * Copyright (C) 2009 Francisco Jerez.
 * All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining
 * a copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE COPYRIGHT OWNER(S) AND/OR ITS SUPPLIERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#समावेश <linux/module.h>

#समावेश "ch7006_priv.h"

/* DRM encoder functions */

अटल व्योम ch7006_encoder_set_config(काष्ठा drm_encoder *encoder,
				      व्योम *params)
अणु
	काष्ठा ch7006_priv *priv = to_ch7006_priv(encoder);

	priv->params = *(काष्ठा ch7006_encoder_params *)params;
पूर्ण

अटल व्योम ch7006_encoder_destroy(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा ch7006_priv *priv = to_ch7006_priv(encoder);

	drm_property_destroy(encoder->dev, priv->scale_property);

	kमुक्त(priv);
	to_encoder_slave(encoder)->slave_priv = शून्य;

	drm_i2c_encoder_destroy(encoder);
पूर्ण

अटल व्योम  ch7006_encoder_dpms(काष्ठा drm_encoder *encoder, पूर्णांक mode)
अणु
	काष्ठा i2c_client *client = drm_i2c_encoder_get_client(encoder);
	काष्ठा ch7006_priv *priv = to_ch7006_priv(encoder);
	काष्ठा ch7006_state *state = &priv->state;

	ch7006_dbg(client, "\n");

	अगर (mode == priv->last_dpms)
		वापस;
	priv->last_dpms = mode;

	ch7006_setup_घातer_state(encoder);

	ch7006_load_reg(client, state, CH7006_POWER);
पूर्ण

अटल व्योम ch7006_encoder_save(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा i2c_client *client = drm_i2c_encoder_get_client(encoder);
	काष्ठा ch7006_priv *priv = to_ch7006_priv(encoder);

	ch7006_dbg(client, "\n");

	ch7006_state_save(client, &priv->saved_state);
पूर्ण

अटल व्योम ch7006_encoder_restore(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा i2c_client *client = drm_i2c_encoder_get_client(encoder);
	काष्ठा ch7006_priv *priv = to_ch7006_priv(encoder);

	ch7006_dbg(client, "\n");

	ch7006_state_load(client, &priv->saved_state);
पूर्ण

अटल bool ch7006_encoder_mode_fixup(काष्ठा drm_encoder *encoder,
				      स्थिर काष्ठा drm_display_mode *mode,
				      काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा ch7006_priv *priv = to_ch7006_priv(encoder);

	/* The ch7006 is painfully picky with the input timings so no
	 * custom modes क्रम now... */

	priv->mode = ch7006_lookup_mode(encoder, mode);

	वापस !!priv->mode;
पूर्ण

अटल पूर्णांक ch7006_encoder_mode_valid(काष्ठा drm_encoder *encoder,
				     काष्ठा drm_display_mode *mode)
अणु
	अगर (ch7006_lookup_mode(encoder, mode))
		वापस MODE_OK;
	अन्यथा
		वापस MODE_BAD;
पूर्ण

अटल व्योम ch7006_encoder_mode_set(काष्ठा drm_encoder *encoder,
				     काष्ठा drm_display_mode *drm_mode,
				     काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा i2c_client *client = drm_i2c_encoder_get_client(encoder);
	काष्ठा ch7006_priv *priv = to_ch7006_priv(encoder);
	काष्ठा ch7006_encoder_params *params = &priv->params;
	काष्ठा ch7006_state *state = &priv->state;
	uपूर्णांक8_t *regs = state->regs;
	स्थिर काष्ठा ch7006_mode *mode = priv->mode;
	स्थिर काष्ठा ch7006_tv_norm_info *norm = &ch7006_tv_norms[priv->norm];
	पूर्णांक start_active;

	ch7006_dbg(client, "\n");

	regs[CH7006_DISPMODE] = norm->dispmode | mode->dispmode;
	regs[CH7006_BWIDTH] = 0;
	regs[CH7006_INPUT_FORMAT] = bitf(CH7006_INPUT_FORMAT_FORMAT,
					 params->input_क्रमmat);

	regs[CH7006_CLKMODE] = CH7006_CLKMODE_SUBC_LOCK
		| bitf(CH7006_CLKMODE_XCM, params->xcm)
		| bitf(CH7006_CLKMODE_PCM, params->pcm);
	अगर (params->घड़ी_mode)
		regs[CH7006_CLKMODE] |= CH7006_CLKMODE_MASTER;
	अगर (params->घड़ी_edge)
		regs[CH7006_CLKMODE] |= CH7006_CLKMODE_POS_EDGE;

	start_active = (drm_mode->htotal & ~0x7) - (drm_mode->hsync_start & ~0x7);
	regs[CH7006_POV] = bitf(CH7006_POV_START_ACTIVE_8, start_active);
	regs[CH7006_START_ACTIVE] = bitf(CH7006_START_ACTIVE_0, start_active);

	regs[CH7006_INPUT_SYNC] = 0;
	अगर (params->sync_direction)
		regs[CH7006_INPUT_SYNC] |= CH7006_INPUT_SYNC_OUTPUT;
	अगर (params->sync_encoding)
		regs[CH7006_INPUT_SYNC] |= CH7006_INPUT_SYNC_EMBEDDED;
	अगर (drm_mode->flags & DRM_MODE_FLAG_PVSYNC)
		regs[CH7006_INPUT_SYNC] |= CH7006_INPUT_SYNC_PVSYNC;
	अगर (drm_mode->flags & DRM_MODE_FLAG_PHSYNC)
		regs[CH7006_INPUT_SYNC] |= CH7006_INPUT_SYNC_PHSYNC;

	regs[CH7006_DETECT] = 0;
	regs[CH7006_BCLKOUT] = 0;

	regs[CH7006_SUBC_INC3] = 0;
	अगर (params->pout_level)
		regs[CH7006_SUBC_INC3] |= CH7006_SUBC_INC3_POUT_3_3V;

	regs[CH7006_SUBC_INC4] = 0;
	अगर (params->active_detect)
		regs[CH7006_SUBC_INC4] |= CH7006_SUBC_INC4_DS_INPUT;

	regs[CH7006_PLL_CONTROL] = priv->saved_state.regs[CH7006_PLL_CONTROL];

	ch7006_setup_levels(encoder);
	ch7006_setup_subcarrier(encoder);
	ch7006_setup_pll(encoder);
	ch7006_setup_घातer_state(encoder);
	ch7006_setup_properties(encoder);

	ch7006_state_load(client, state);
पूर्ण

अटल क्रमागत drm_connector_status ch7006_encoder_detect(काष्ठा drm_encoder *encoder,
						       काष्ठा drm_connector *connector)
अणु
	काष्ठा i2c_client *client = drm_i2c_encoder_get_client(encoder);
	काष्ठा ch7006_priv *priv = to_ch7006_priv(encoder);
	काष्ठा ch7006_state *state = &priv->state;
	पूर्णांक det;

	ch7006_dbg(client, "\n");

	ch7006_save_reg(client, state, CH7006_DETECT);
	ch7006_save_reg(client, state, CH7006_POWER);
	ch7006_save_reg(client, state, CH7006_CLKMODE);

	ch7006_ग_लिखो(client, CH7006_POWER, CH7006_POWER_RESET |
					   bitfs(CH7006_POWER_LEVEL, NORMAL));
	ch7006_ग_लिखो(client, CH7006_CLKMODE, CH7006_CLKMODE_MASTER);

	ch7006_ग_लिखो(client, CH7006_DETECT, CH7006_DETECT_SENSE);

	ch7006_ग_लिखो(client, CH7006_DETECT, 0);

	det = ch7006_पढ़ो(client, CH7006_DETECT);

	ch7006_load_reg(client, state, CH7006_CLKMODE);
	ch7006_load_reg(client, state, CH7006_POWER);
	ch7006_load_reg(client, state, CH7006_DETECT);

	अगर ((det & (CH7006_DETECT_SVIDEO_Y_TEST|
		    CH7006_DETECT_SVIDEO_C_TEST|
		    CH7006_DETECT_CVBS_TEST)) == 0)
		priv->subconnector = DRM_MODE_SUBCONNECTOR_SCART;
	अन्यथा अगर ((det & (CH7006_DETECT_SVIDEO_Y_TEST|
			 CH7006_DETECT_SVIDEO_C_TEST)) == 0)
		priv->subconnector = DRM_MODE_SUBCONNECTOR_SVIDEO;
	अन्यथा अगर ((det & CH7006_DETECT_CVBS_TEST) == 0)
		priv->subconnector = DRM_MODE_SUBCONNECTOR_Composite;
	अन्यथा
		priv->subconnector = DRM_MODE_SUBCONNECTOR_Unknown;

	drm_object_property_set_value(&connector->base,
			encoder->dev->mode_config.tv_subconnector_property,
							priv->subconnector);

	वापस priv->subconnector ? connector_status_connected :
					connector_status_disconnected;
पूर्ण

अटल पूर्णांक ch7006_encoder_get_modes(काष्ठा drm_encoder *encoder,
				    काष्ठा drm_connector *connector)
अणु
	काष्ठा ch7006_priv *priv = to_ch7006_priv(encoder);
	स्थिर काष्ठा ch7006_mode *mode;
	पूर्णांक n = 0;

	क्रम (mode = ch7006_modes; mode->mode.घड़ी; mode++) अणु
		अगर (~mode->valid_scales & 1<<priv->scale ||
		    ~mode->valid_norms & 1<<priv->norm)
			जारी;

		drm_mode_probed_add(connector,
				drm_mode_duplicate(encoder->dev, &mode->mode));

		n++;
	पूर्ण

	वापस n;
पूर्ण

अटल पूर्णांक ch7006_encoder_create_resources(काष्ठा drm_encoder *encoder,
					   काष्ठा drm_connector *connector)
अणु
	काष्ठा ch7006_priv *priv = to_ch7006_priv(encoder);
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा drm_mode_config *conf = &dev->mode_config;

	drm_mode_create_tv_properties(dev, NUM_TV_NORMS, ch7006_tv_norm_names);

	priv->scale_property = drm_property_create_range(dev, 0, "scale", 0, 2);
	अगर (!priv->scale_property)
		वापस -ENOMEM;

	drm_object_attach_property(&connector->base, conf->tv_select_subconnector_property,
				      priv->select_subconnector);
	drm_object_attach_property(&connector->base, conf->tv_subconnector_property,
				      priv->subconnector);
	drm_object_attach_property(&connector->base, conf->tv_left_margin_property,
				      priv->hmargin);
	drm_object_attach_property(&connector->base, conf->tv_bottom_margin_property,
				      priv->vmargin);
	drm_object_attach_property(&connector->base, conf->tv_mode_property,
				      priv->norm);
	drm_object_attach_property(&connector->base, conf->tv_brightness_property,
				      priv->brightness);
	drm_object_attach_property(&connector->base, conf->tv_contrast_property,
				      priv->contrast);
	drm_object_attach_property(&connector->base, conf->tv_flicker_reduction_property,
				      priv->flicker);
	drm_object_attach_property(&connector->base, priv->scale_property,
				      priv->scale);

	वापस 0;
पूर्ण

अटल पूर्णांक ch7006_encoder_set_property(काष्ठा drm_encoder *encoder,
				       काष्ठा drm_connector *connector,
				       काष्ठा drm_property *property,
				       uपूर्णांक64_t val)
अणु
	काष्ठा i2c_client *client = drm_i2c_encoder_get_client(encoder);
	काष्ठा ch7006_priv *priv = to_ch7006_priv(encoder);
	काष्ठा ch7006_state *state = &priv->state;
	काष्ठा drm_mode_config *conf = &encoder->dev->mode_config;
	काष्ठा drm_crtc *crtc = encoder->crtc;
	bool modes_changed = false;

	ch7006_dbg(client, "\n");

	अगर (property == conf->tv_select_subconnector_property) अणु
		priv->select_subconnector = val;

		ch7006_setup_घातer_state(encoder);

		ch7006_load_reg(client, state, CH7006_POWER);

	पूर्ण अन्यथा अगर (property == conf->tv_left_margin_property) अणु
		priv->hmargin = val;

		ch7006_setup_properties(encoder);

		ch7006_load_reg(client, state, CH7006_POV);
		ch7006_load_reg(client, state, CH7006_HPOS);

	पूर्ण अन्यथा अगर (property == conf->tv_bottom_margin_property) अणु
		priv->vmargin = val;

		ch7006_setup_properties(encoder);

		ch7006_load_reg(client, state, CH7006_POV);
		ch7006_load_reg(client, state, CH7006_VPOS);

	पूर्ण अन्यथा अगर (property == conf->tv_mode_property) अणु
		अगर (connector->dpms != DRM_MODE_DPMS_OFF)
			वापस -EINVAL;

		priv->norm = val;

		modes_changed = true;

	पूर्ण अन्यथा अगर (property == conf->tv_brightness_property) अणु
		priv->brightness = val;

		ch7006_setup_levels(encoder);

		ch7006_load_reg(client, state, CH7006_BLACK_LEVEL);

	पूर्ण अन्यथा अगर (property == conf->tv_contrast_property) अणु
		priv->contrast = val;

		ch7006_setup_properties(encoder);

		ch7006_load_reg(client, state, CH7006_CONTRAST);

	पूर्ण अन्यथा अगर (property == conf->tv_flicker_reduction_property) अणु
		priv->flicker = val;

		ch7006_setup_properties(encoder);

		ch7006_load_reg(client, state, CH7006_FFILTER);

	पूर्ण अन्यथा अगर (property == priv->scale_property) अणु
		अगर (connector->dpms != DRM_MODE_DPMS_OFF)
			वापस -EINVAL;

		priv->scale = val;

		modes_changed = true;

	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	अगर (modes_changed) अणु
		drm_helper_probe_single_connector_modes(connector, 0, 0);

		अगर (crtc)
			drm_crtc_helper_set_mode(crtc, &crtc->mode,
						 crtc->x, crtc->y,
						 crtc->primary->fb);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_encoder_slave_funcs ch7006_encoder_funcs = अणु
	.set_config = ch7006_encoder_set_config,
	.destroy = ch7006_encoder_destroy,
	.dpms = ch7006_encoder_dpms,
	.save = ch7006_encoder_save,
	.restore = ch7006_encoder_restore,
	.mode_fixup = ch7006_encoder_mode_fixup,
	.mode_valid = ch7006_encoder_mode_valid,
	.mode_set = ch7006_encoder_mode_set,
	.detect = ch7006_encoder_detect,
	.get_modes = ch7006_encoder_get_modes,
	.create_resources = ch7006_encoder_create_resources,
	.set_property = ch7006_encoder_set_property,
पूर्ण;


/* I2C driver functions */

अटल पूर्णांक ch7006_probe(काष्ठा i2c_client *client, स्थिर काष्ठा i2c_device_id *id)
अणु
	uपूर्णांक8_t addr = CH7006_VERSION_ID;
	uपूर्णांक8_t val;
	पूर्णांक ret;

	ch7006_dbg(client, "\n");

	ret = i2c_master_send(client, &addr, माप(addr));
	अगर (ret < 0)
		जाओ fail;

	ret = i2c_master_recv(client, &val, माप(val));
	अगर (ret < 0)
		जाओ fail;

	ch7006_info(client, "Detected version ID: %x\n", val);

	/* I करोn't know what this is क्रम, but otherwise I get no
	 * संकेत.
	 */
	ch7006_ग_लिखो(client, 0x3d, 0x0);

	वापस 0;

fail:
	ch7006_err(client, "Error %d reading version ID\n", ret);

	वापस -ENODEV;
पूर्ण

अटल पूर्णांक ch7006_हटाओ(काष्ठा i2c_client *client)
अणु
	ch7006_dbg(client, "\n");

	वापस 0;
पूर्ण

अटल पूर्णांक ch7006_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);

	ch7006_dbg(client, "\n");

	ch7006_ग_लिखो(client, 0x3d, 0x0);

	वापस 0;
पूर्ण

अटल पूर्णांक ch7006_encoder_init(काष्ठा i2c_client *client,
			       काष्ठा drm_device *dev,
			       काष्ठा drm_encoder_slave *encoder)
अणु
	काष्ठा ch7006_priv *priv;
	पूर्णांक i;

	ch7006_dbg(client, "\n");

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	encoder->slave_priv = priv;
	encoder->slave_funcs = &ch7006_encoder_funcs;

	priv->norm = TV_NORM_PAL;
	priv->select_subconnector = DRM_MODE_SUBCONNECTOR_Automatic;
	priv->subconnector = DRM_MODE_SUBCONNECTOR_Unknown;
	priv->scale = 1;
	priv->contrast = 50;
	priv->brightness = 50;
	priv->flicker = 50;
	priv->hmargin = 50;
	priv->vmargin = 50;
	priv->last_dpms = -1;
	priv->chip_version = ch7006_पढ़ो(client, CH7006_VERSION_ID);

	अगर (ch7006_tv_norm) अणु
		क्रम (i = 0; i < NUM_TV_NORMS; i++) अणु
			अगर (!म_भेद(ch7006_tv_norm_names[i], ch7006_tv_norm)) अणु
				priv->norm = i;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (i == NUM_TV_NORMS)
			ch7006_err(client, "Invalid TV norm setting \"%s\".\n",
				   ch7006_tv_norm);
	पूर्ण

	अगर (ch7006_scale >= 0 && ch7006_scale <= 2)
		priv->scale = ch7006_scale;
	अन्यथा
		ch7006_err(client, "Invalid scale setting \"%d\".\n",
			   ch7006_scale);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ch7006_ids[] = अणु
	अणु "ch7006", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ch7006_ids);

अटल स्थिर काष्ठा dev_pm_ops ch7006_pm_ops = अणु
	.resume = ch7006_resume,
पूर्ण;

अटल काष्ठा drm_i2c_encoder_driver ch7006_driver = अणु
	.i2c_driver = अणु
		.probe = ch7006_probe,
		.हटाओ = ch7006_हटाओ,

		.driver = अणु
			.name = "ch7006",
			.pm = &ch7006_pm_ops,
		पूर्ण,

		.id_table = ch7006_ids,
	पूर्ण,

	.encoder_init = ch7006_encoder_init,
पूर्ण;


/* Module initialization */

अटल पूर्णांक __init ch7006_init(व्योम)
अणु
	वापस drm_i2c_encoder_रेजिस्टर(THIS_MODULE, &ch7006_driver);
पूर्ण

अटल व्योम __निकास ch7006_निकास(व्योम)
अणु
	drm_i2c_encoder_unरेजिस्टर(&ch7006_driver);
पूर्ण

पूर्णांक ch7006_debug;
module_param_named(debug, ch7006_debug, पूर्णांक, 0600);
MODULE_PARM_DESC(debug, "Enable debug output.");

अक्षर *ch7006_tv_norm;
module_param_named(tv_norm, ch7006_tv_norm, अक्षरp, 0600);
MODULE_PARM_DESC(tv_norm, "Default TV norm.\n"
		 "\t\tSupported: PAL, PAL-M, PAL-N, PAL-Nc, PAL-60, NTSC-M, NTSC-J.\n"
		 "\t\tDefault: PAL");

पूर्णांक ch7006_scale = 1;
module_param_named(scale, ch7006_scale, पूर्णांक, 0600);
MODULE_PARM_DESC(scale, "Default scale.\n"
		 "\t\tSupported: 0 -> Select video modes with a higher blanking ratio.\n"
		 "\t\t\t1 -> Select default video modes.\n"
		 "\t\t\t2 -> Select video modes with a lower blanking ratio.");

MODULE_AUTHOR("Francisco Jerez <currojerez@riseup.net>");
MODULE_DESCRIPTION("Chrontel ch7006 TV encoder driver");
MODULE_LICENSE("GPL and additional rights");

module_init(ch7006_init);
module_निकास(ch7006_निकास);
