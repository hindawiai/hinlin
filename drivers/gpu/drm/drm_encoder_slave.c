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

#समावेश <drm/drm_encoder_slave.h>

/**
 * drm_i2c_encoder_init - Initialize an I2C slave encoder
 * @dev:	DRM device.
 * @encoder:    Encoder to be attached to the I2C device. You aren't
 *		required to have called drm_encoder_init() beक्रमe.
 * @adap:	I2C adapter that will be used to communicate with
 *		the device.
 * @info:	Inक्रमmation that will be used to create the I2C device.
 *		Required fields are @addr and @type.
 *
 * Create an I2C device on the specअगरied bus (the module containing its
 * driver is transparently loaded) and attach it to the specअगरied
 * &drm_encoder_slave. The @slave_funcs field will be initialized with
 * the hooks provided by the slave driver.
 *
 * If @info.platक्रमm_data is non-शून्य it will be used as the initial
 * slave config.
 *
 * Returns 0 on success or a negative त्रुटि_सं on failure, in particular,
 * -ENODEV is वापसed when no matching driver is found.
 */
पूर्णांक drm_i2c_encoder_init(काष्ठा drm_device *dev,
			 काष्ठा drm_encoder_slave *encoder,
			 काष्ठा i2c_adapter *adap,
			 स्थिर काष्ठा i2c_board_info *info)
अणु
	काष्ठा module *module = शून्य;
	काष्ठा i2c_client *client;
	काष्ठा drm_i2c_encoder_driver *encoder_drv;
	पूर्णांक err = 0;

	request_module("%s%s", I2C_MODULE_PREFIX, info->type);

	client = i2c_new_client_device(adap, info);
	अगर (!i2c_client_has_driver(client)) अणु
		err = -ENODEV;
		जाओ fail_unरेजिस्टर;
	पूर्ण

	module = client->dev.driver->owner;
	अगर (!try_module_get(module)) अणु
		err = -ENODEV;
		जाओ fail_unरेजिस्टर;
	पूर्ण

	encoder->bus_priv = client;

	encoder_drv = to_drm_i2c_encoder_driver(to_i2c_driver(client->dev.driver));

	err = encoder_drv->encoder_init(client, dev, encoder);
	अगर (err)
		जाओ fail_module_put;

	अगर (info->platक्रमm_data)
		encoder->slave_funcs->set_config(&encoder->base,
						 info->platक्रमm_data);

	वापस 0;

fail_module_put:
	module_put(module);
fail_unरेजिस्टर:
	i2c_unरेजिस्टर_device(client);
	वापस err;
पूर्ण
EXPORT_SYMBOL(drm_i2c_encoder_init);

/**
 * drm_i2c_encoder_destroy - Unरेजिस्टर the I2C device backing an encoder
 * @drm_encoder:	Encoder to be unरेजिस्टरed.
 *
 * This should be called from the @destroy method of an I2C slave
 * encoder driver once I2C access is no दीर्घer needed.
 */
व्योम drm_i2c_encoder_destroy(काष्ठा drm_encoder *drm_encoder)
अणु
	काष्ठा drm_encoder_slave *encoder = to_encoder_slave(drm_encoder);
	काष्ठा i2c_client *client = drm_i2c_encoder_get_client(drm_encoder);
	काष्ठा module *module = client->dev.driver->owner;

	i2c_unरेजिस्टर_device(client);
	encoder->bus_priv = शून्य;

	module_put(module);
पूर्ण
EXPORT_SYMBOL(drm_i2c_encoder_destroy);

/*
 * Wrapper fxns which can be plugged in to drm_encoder_helper_funcs:
 */

अटल अंतरभूत स्थिर काष्ठा drm_encoder_slave_funcs *
get_slave_funcs(काष्ठा drm_encoder *enc)
अणु
	वापस to_encoder_slave(enc)->slave_funcs;
पूर्ण

व्योम drm_i2c_encoder_dpms(काष्ठा drm_encoder *encoder, पूर्णांक mode)
अणु
	get_slave_funcs(encoder)->dpms(encoder, mode);
पूर्ण
EXPORT_SYMBOL(drm_i2c_encoder_dpms);

bool drm_i2c_encoder_mode_fixup(काष्ठा drm_encoder *encoder,
		स्थिर काष्ठा drm_display_mode *mode,
		काष्ठा drm_display_mode *adjusted_mode)
अणु
	अगर (!get_slave_funcs(encoder)->mode_fixup)
		वापस true;

	वापस get_slave_funcs(encoder)->mode_fixup(encoder, mode, adjusted_mode);
पूर्ण
EXPORT_SYMBOL(drm_i2c_encoder_mode_fixup);

व्योम drm_i2c_encoder_prepare(काष्ठा drm_encoder *encoder)
अणु
	drm_i2c_encoder_dpms(encoder, DRM_MODE_DPMS_OFF);
पूर्ण
EXPORT_SYMBOL(drm_i2c_encoder_prepare);

व्योम drm_i2c_encoder_commit(काष्ठा drm_encoder *encoder)
अणु
	drm_i2c_encoder_dpms(encoder, DRM_MODE_DPMS_ON);
पूर्ण
EXPORT_SYMBOL(drm_i2c_encoder_commit);

व्योम drm_i2c_encoder_mode_set(काष्ठा drm_encoder *encoder,
		काष्ठा drm_display_mode *mode,
		काष्ठा drm_display_mode *adjusted_mode)
अणु
	get_slave_funcs(encoder)->mode_set(encoder, mode, adjusted_mode);
पूर्ण
EXPORT_SYMBOL(drm_i2c_encoder_mode_set);

क्रमागत drm_connector_status drm_i2c_encoder_detect(काष्ठा drm_encoder *encoder,
	    काष्ठा drm_connector *connector)
अणु
	वापस get_slave_funcs(encoder)->detect(encoder, connector);
पूर्ण
EXPORT_SYMBOL(drm_i2c_encoder_detect);

व्योम drm_i2c_encoder_save(काष्ठा drm_encoder *encoder)
अणु
	get_slave_funcs(encoder)->save(encoder);
पूर्ण
EXPORT_SYMBOL(drm_i2c_encoder_save);

व्योम drm_i2c_encoder_restore(काष्ठा drm_encoder *encoder)
अणु
	get_slave_funcs(encoder)->restore(encoder);
पूर्ण
EXPORT_SYMBOL(drm_i2c_encoder_restore);
