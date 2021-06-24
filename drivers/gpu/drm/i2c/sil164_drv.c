<शैली गुरु>
/*
 * Copyright (C) 2010 Francisco Jerez.
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

#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_encoder_slave.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/i2c/sil164.h>

काष्ठा sil164_priv अणु
	काष्ठा sil164_encoder_params config;
	काष्ठा i2c_client *duallink_slave;

	uपूर्णांक8_t saved_state[0x10];
	uपूर्णांक8_t saved_slave_state[0x10];
पूर्ण;

#घोषणा to_sil164_priv(x) \
	((काष्ठा sil164_priv *)to_encoder_slave(x)->slave_priv)

#घोषणा sil164_dbg(client, क्रमmat, ...) करो अणु				\
		अगर (drm_debug_enabled(DRM_UT_KMS))			\
			dev_prपूर्णांकk(KERN_DEBUG, &client->dev,		\
				   "%s: " क्रमmat, __func__, ## __VA_ARGS__); \
	पूर्ण जबतक (0)
#घोषणा sil164_info(client, क्रमmat, ...)		\
	dev_info(&client->dev, क्रमmat, __VA_ARGS__)
#घोषणा sil164_err(client, क्रमmat, ...)			\
	dev_err(&client->dev, क्रमmat, __VA_ARGS__)

#घोषणा SIL164_I2C_ADDR_MASTER			0x38
#घोषणा SIL164_I2C_ADDR_SLAVE			0x39

/* HW रेजिस्टर definitions */

#घोषणा SIL164_VENDOR_LO			0x0
#घोषणा SIL164_VENDOR_HI			0x1
#घोषणा SIL164_DEVICE_LO			0x2
#घोषणा SIL164_DEVICE_HI			0x3
#घोषणा SIL164_REVISION				0x4
#घोषणा SIL164_FREQ_MIN				0x6
#घोषणा SIL164_FREQ_MAX				0x7
#घोषणा SIL164_CONTROL0				0x8
#  define SIL164_CONTROL0_POWER_ON		0x01
#  define SIL164_CONTROL0_EDGE_RISING		0x02
#  define SIL164_CONTROL0_INPUT_24BIT		0x04
#  define SIL164_CONTROL0_DUAL_EDGE		0x08
#  define SIL164_CONTROL0_HSYNC_ON		0x10
#  define SIL164_CONTROL0_VSYNC_ON		0x20
#घोषणा SIL164_DETECT				0x9
#  define SIL164_DETECT_INTR_STAT		0x01
#  define SIL164_DETECT_HOTPLUG_STAT		0x02
#  define SIL164_DETECT_RECEIVER_STAT		0x04
#  define SIL164_DETECT_INTR_MODE_RECEIVER	0x00
#  define SIL164_DETECT_INTR_MODE_HOTPLUG	0x08
#  define SIL164_DETECT_OUT_MODE_HIGH		0x00
#  define SIL164_DETECT_OUT_MODE_INTR		0x10
#  define SIL164_DETECT_OUT_MODE_RECEIVER	0x20
#  define SIL164_DETECT_OUT_MODE_HOTPLUG	0x30
#  define SIL164_DETECT_VSWING_STAT		0x80
#घोषणा SIL164_CONTROL1				0xa
#  define SIL164_CONTROL1_DESKEW_ENABLE		0x10
#  define SIL164_CONTROL1_DESKEW_INCR_SHIFT	5
#घोषणा SIL164_GPIO				0xb
#घोषणा SIL164_CONTROL2				0xc
#  define SIL164_CONTROL2_FILTER_ENABLE		0x01
#  define SIL164_CONTROL2_FILTER_SETTING_SHIFT	1
#  define SIL164_CONTROL2_DUALLINK_MASTER	0x40
#  define SIL164_CONTROL2_SYNC_CONT		0x80
#घोषणा SIL164_DUALLINK				0xd
#  define SIL164_DUALLINK_ENABLE		0x10
#  define SIL164_DUALLINK_SKEW_SHIFT		5
#घोषणा SIL164_PLLZONE				0xe
#  define SIL164_PLLZONE_STAT			0x08
#  define SIL164_PLLZONE_FORCE_ON		0x10
#  define SIL164_PLLZONE_FORCE_HIGH		0x20

/* HW access functions */

अटल व्योम
sil164_ग_लिखो(काष्ठा i2c_client *client, uपूर्णांक8_t addr, uपूर्णांक8_t val)
अणु
	uपूर्णांक8_t buf[] = अणुaddr, valपूर्ण;
	पूर्णांक ret;

	ret = i2c_master_send(client, buf, ARRAY_SIZE(buf));
	अगर (ret < 0)
		sil164_err(client, "Error %d writing to subaddress 0x%x\n",
			   ret, addr);
पूर्ण

अटल uपूर्णांक8_t
sil164_पढ़ो(काष्ठा i2c_client *client, uपूर्णांक8_t addr)
अणु
	uपूर्णांक8_t val;
	पूर्णांक ret;

	ret = i2c_master_send(client, &addr, माप(addr));
	अगर (ret < 0)
		जाओ fail;

	ret = i2c_master_recv(client, &val, माप(val));
	अगर (ret < 0)
		जाओ fail;

	वापस val;

fail:
	sil164_err(client, "Error %d reading from subaddress 0x%x\n",
		   ret, addr);
	वापस 0;
पूर्ण

अटल व्योम
sil164_save_state(काष्ठा i2c_client *client, uपूर्णांक8_t *state)
अणु
	पूर्णांक i;

	क्रम (i = 0x8; i <= 0xe; i++)
		state[i] = sil164_पढ़ो(client, i);
पूर्ण

अटल व्योम
sil164_restore_state(काष्ठा i2c_client *client, uपूर्णांक8_t *state)
अणु
	पूर्णांक i;

	क्रम (i = 0x8; i <= 0xe; i++)
		sil164_ग_लिखो(client, i, state[i]);
पूर्ण

अटल व्योम
sil164_set_घातer_state(काष्ठा i2c_client *client, bool on)
अणु
	uपूर्णांक8_t control0 = sil164_पढ़ो(client, SIL164_CONTROL0);

	अगर (on)
		control0 |= SIL164_CONTROL0_POWER_ON;
	अन्यथा
		control0 &= ~SIL164_CONTROL0_POWER_ON;

	sil164_ग_लिखो(client, SIL164_CONTROL0, control0);
पूर्ण

अटल व्योम
sil164_init_state(काष्ठा i2c_client *client,
		  काष्ठा sil164_encoder_params *config,
		  bool duallink)
अणु
	sil164_ग_लिखो(client, SIL164_CONTROL0,
		     SIL164_CONTROL0_HSYNC_ON |
		     SIL164_CONTROL0_VSYNC_ON |
		     (config->input_edge ? SIL164_CONTROL0_EDGE_RISING : 0) |
		     (config->input_width ? SIL164_CONTROL0_INPUT_24BIT : 0) |
		     (config->input_dual ? SIL164_CONTROL0_DUAL_EDGE : 0));

	sil164_ग_लिखो(client, SIL164_DETECT,
		     SIL164_DETECT_INTR_STAT |
		     SIL164_DETECT_OUT_MODE_RECEIVER);

	sil164_ग_लिखो(client, SIL164_CONTROL1,
		     (config->input_skew ? SIL164_CONTROL1_DESKEW_ENABLE : 0) |
		     (((config->input_skew + 4) & 0x7)
		      << SIL164_CONTROL1_DESKEW_INCR_SHIFT));

	sil164_ग_लिखो(client, SIL164_CONTROL2,
		     SIL164_CONTROL2_SYNC_CONT |
		     (config->pll_filter ? 0 : SIL164_CONTROL2_FILTER_ENABLE) |
		     (4 << SIL164_CONTROL2_FILTER_SETTING_SHIFT));

	sil164_ग_लिखो(client, SIL164_PLLZONE, 0);

	अगर (duallink)
		sil164_ग_लिखो(client, SIL164_DUALLINK,
			     SIL164_DUALLINK_ENABLE |
			     (((config->duallink_skew + 4) & 0x7)
			      << SIL164_DUALLINK_SKEW_SHIFT));
	अन्यथा
		sil164_ग_लिखो(client, SIL164_DUALLINK, 0);
पूर्ण

/* DRM encoder functions */

अटल व्योम
sil164_encoder_set_config(काष्ठा drm_encoder *encoder, व्योम *params)
अणु
	काष्ठा sil164_priv *priv = to_sil164_priv(encoder);

	priv->config = *(काष्ठा sil164_encoder_params *)params;
पूर्ण

अटल व्योम
sil164_encoder_dpms(काष्ठा drm_encoder *encoder, पूर्णांक mode)
अणु
	काष्ठा sil164_priv *priv = to_sil164_priv(encoder);
	bool on = (mode == DRM_MODE_DPMS_ON);
	bool duallink = (on && encoder->crtc->mode.घड़ी > 165000);

	sil164_set_घातer_state(drm_i2c_encoder_get_client(encoder), on);

	अगर (priv->duallink_slave)
		sil164_set_घातer_state(priv->duallink_slave, duallink);
पूर्ण

अटल व्योम
sil164_encoder_save(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा sil164_priv *priv = to_sil164_priv(encoder);

	sil164_save_state(drm_i2c_encoder_get_client(encoder),
			  priv->saved_state);

	अगर (priv->duallink_slave)
		sil164_save_state(priv->duallink_slave,
				  priv->saved_slave_state);
पूर्ण

अटल व्योम
sil164_encoder_restore(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा sil164_priv *priv = to_sil164_priv(encoder);

	sil164_restore_state(drm_i2c_encoder_get_client(encoder),
			     priv->saved_state);

	अगर (priv->duallink_slave)
		sil164_restore_state(priv->duallink_slave,
				     priv->saved_slave_state);
पूर्ण

अटल पूर्णांक
sil164_encoder_mode_valid(काष्ठा drm_encoder *encoder,
			  काष्ठा drm_display_mode *mode)
अणु
	काष्ठा sil164_priv *priv = to_sil164_priv(encoder);

	अगर (mode->घड़ी < 32000)
		वापस MODE_CLOCK_LOW;

	अगर (mode->घड़ी > 330000 ||
	    (mode->घड़ी > 165000 && !priv->duallink_slave))
		वापस MODE_CLOCK_HIGH;

	वापस MODE_OK;
पूर्ण

अटल व्योम
sil164_encoder_mode_set(काष्ठा drm_encoder *encoder,
			काष्ठा drm_display_mode *mode,
			काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा sil164_priv *priv = to_sil164_priv(encoder);
	bool duallink = adjusted_mode->घड़ी > 165000;

	sil164_init_state(drm_i2c_encoder_get_client(encoder),
			  &priv->config, duallink);

	अगर (priv->duallink_slave)
		sil164_init_state(priv->duallink_slave,
				  &priv->config, duallink);

	sil164_encoder_dpms(encoder, DRM_MODE_DPMS_ON);
पूर्ण

अटल क्रमागत drm_connector_status
sil164_encoder_detect(काष्ठा drm_encoder *encoder,
		      काष्ठा drm_connector *connector)
अणु
	काष्ठा i2c_client *client = drm_i2c_encoder_get_client(encoder);

	अगर (sil164_पढ़ो(client, SIL164_DETECT) & SIL164_DETECT_HOTPLUG_STAT)
		वापस connector_status_connected;
	अन्यथा
		वापस connector_status_disconnected;
पूर्ण

अटल पूर्णांक
sil164_encoder_get_modes(काष्ठा drm_encoder *encoder,
			 काष्ठा drm_connector *connector)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक
sil164_encoder_create_resources(काष्ठा drm_encoder *encoder,
				काष्ठा drm_connector *connector)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक
sil164_encoder_set_property(काष्ठा drm_encoder *encoder,
			    काष्ठा drm_connector *connector,
			    काष्ठा drm_property *property,
			    uपूर्णांक64_t val)
अणु
	वापस 0;
पूर्ण

अटल व्योम
sil164_encoder_destroy(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा sil164_priv *priv = to_sil164_priv(encoder);

	i2c_unरेजिस्टर_device(priv->duallink_slave);

	kमुक्त(priv);
	drm_i2c_encoder_destroy(encoder);
पूर्ण

अटल स्थिर काष्ठा drm_encoder_slave_funcs sil164_encoder_funcs = अणु
	.set_config = sil164_encoder_set_config,
	.destroy = sil164_encoder_destroy,
	.dpms = sil164_encoder_dpms,
	.save = sil164_encoder_save,
	.restore = sil164_encoder_restore,
	.mode_valid = sil164_encoder_mode_valid,
	.mode_set = sil164_encoder_mode_set,
	.detect = sil164_encoder_detect,
	.get_modes = sil164_encoder_get_modes,
	.create_resources = sil164_encoder_create_resources,
	.set_property = sil164_encoder_set_property,
पूर्ण;

/* I2C driver functions */

अटल पूर्णांक
sil164_probe(काष्ठा i2c_client *client, स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक venकरोr = sil164_पढ़ो(client, SIL164_VENDOR_HI) << 8 |
		sil164_पढ़ो(client, SIL164_VENDOR_LO);
	पूर्णांक device = sil164_पढ़ो(client, SIL164_DEVICE_HI) << 8 |
		sil164_पढ़ो(client, SIL164_DEVICE_LO);
	पूर्णांक rev = sil164_पढ़ो(client, SIL164_REVISION);

	अगर (venकरोr != 0x1 || device != 0x6) अणु
		sil164_dbg(client, "Unknown device %x:%x.%x\n",
			   venकरोr, device, rev);
		वापस -ENODEV;
	पूर्ण

	sil164_info(client, "Detected device %x:%x.%x\n",
		    venकरोr, device, rev);

	वापस 0;
पूर्ण

अटल पूर्णांक
sil164_हटाओ(काष्ठा i2c_client *client)
अणु
	वापस 0;
पूर्ण

अटल काष्ठा i2c_client *
sil164_detect_slave(काष्ठा i2c_client *client)
अणु
	काष्ठा i2c_adapter *adap = client->adapter;
	काष्ठा i2c_msg msg = अणु
		.addr = SIL164_I2C_ADDR_SLAVE,
		.len = 0,
	पूर्ण;
	स्थिर काष्ठा i2c_board_info info = अणु
		I2C_BOARD_INFO("sil164", SIL164_I2C_ADDR_SLAVE)
	पूर्ण;

	अगर (i2c_transfer(adap, &msg, 1) != 1) अणु
		sil164_dbg(adap, "No dual-link slave found.");
		वापस शून्य;
	पूर्ण

	वापस i2c_new_client_device(adap, &info);
पूर्ण

अटल पूर्णांक
sil164_encoder_init(काष्ठा i2c_client *client,
		    काष्ठा drm_device *dev,
		    काष्ठा drm_encoder_slave *encoder)
अणु
	काष्ठा sil164_priv *priv;
	काष्ठा i2c_client *slave_client;

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	encoder->slave_priv = priv;
	encoder->slave_funcs = &sil164_encoder_funcs;

	slave_client = sil164_detect_slave(client);
	अगर (!IS_ERR(slave_client))
		priv->duallink_slave = slave_client;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id sil164_ids[] = अणु
	अणु "sil164", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, sil164_ids);

अटल काष्ठा drm_i2c_encoder_driver sil164_driver = अणु
	.i2c_driver = अणु
		.probe = sil164_probe,
		.हटाओ = sil164_हटाओ,
		.driver = अणु
			.name = "sil164",
		पूर्ण,
		.id_table = sil164_ids,
	पूर्ण,
	.encoder_init = sil164_encoder_init,
पूर्ण;

/* Module initialization */

अटल पूर्णांक __init
sil164_init(व्योम)
अणु
	वापस drm_i2c_encoder_रेजिस्टर(THIS_MODULE, &sil164_driver);
पूर्ण

अटल व्योम __निकास
sil164_निकास(व्योम)
अणु
	drm_i2c_encoder_unरेजिस्टर(&sil164_driver);
पूर्ण

MODULE_AUTHOR("Francisco Jerez <currojerez@riseup.net>");
MODULE_DESCRIPTION("Silicon Image sil164 TMDS transmitter driver");
MODULE_LICENSE("GPL and additional rights");

module_init(sil164_init);
module_निकास(sil164_निकास);
