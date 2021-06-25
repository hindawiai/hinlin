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

#अगर_अघोषित __DRM_ENCODER_SLAVE_H__
#घोषणा __DRM_ENCODER_SLAVE_H__

#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_encoder.h>

/**
 * काष्ठा drm_encoder_slave_funcs - Entry poपूर्णांकs exposed by a slave encoder driver
 * @set_config:	Initialize any encoder-specअगरic modesetting parameters.
 *		The meaning of the @params parameter is implementation
 *		dependent. It will usually be a काष्ठाure with DVO port
 *		data क्रमmat settings or timings. It's not required क्रम
 *		the new parameters to take effect until the next mode
 *		is set.
 *
 * Most of its members are analogous to the function poपूर्णांकers in
 * &drm_encoder_helper_funcs and they can optionally be used to
 * initialize the latter. Connector-like methods (e.g. @get_modes and
 * @set_property) will typically be wrapped around and only be called
 * अगर the encoder is the currently selected one क्रम the connector.
 */
काष्ठा drm_encoder_slave_funcs अणु
	व्योम (*set_config)(काष्ठा drm_encoder *encoder,
			   व्योम *params);

	व्योम (*destroy)(काष्ठा drm_encoder *encoder);
	व्योम (*dpms)(काष्ठा drm_encoder *encoder, पूर्णांक mode);
	व्योम (*save)(काष्ठा drm_encoder *encoder);
	व्योम (*restore)(काष्ठा drm_encoder *encoder);
	bool (*mode_fixup)(काष्ठा drm_encoder *encoder,
			   स्थिर काष्ठा drm_display_mode *mode,
			   काष्ठा drm_display_mode *adjusted_mode);
	पूर्णांक (*mode_valid)(काष्ठा drm_encoder *encoder,
			  काष्ठा drm_display_mode *mode);
	व्योम (*mode_set)(काष्ठा drm_encoder *encoder,
			 काष्ठा drm_display_mode *mode,
			 काष्ठा drm_display_mode *adjusted_mode);

	क्रमागत drm_connector_status (*detect)(काष्ठा drm_encoder *encoder,
					    काष्ठा drm_connector *connector);
	पूर्णांक (*get_modes)(काष्ठा drm_encoder *encoder,
			 काष्ठा drm_connector *connector);
	पूर्णांक (*create_resources)(काष्ठा drm_encoder *encoder,
				 काष्ठा drm_connector *connector);
	पूर्णांक (*set_property)(काष्ठा drm_encoder *encoder,
			    काष्ठा drm_connector *connector,
			    काष्ठा drm_property *property,
			    uपूर्णांक64_t val);

पूर्ण;

/**
 * काष्ठा drm_encoder_slave - Slave encoder काष्ठा
 * @base: DRM encoder object.
 * @slave_funcs: Slave encoder callbacks.
 * @slave_priv: Slave encoder निजी data.
 * @bus_priv: Bus specअगरic data.
 *
 * A &drm_encoder_slave has two sets of callbacks, @slave_funcs and the
 * ones in @base. The क्रमmer are never actually called by the common
 * CRTC code, it's just a convenience क्रम splitting the encoder
 * functions in an upper, GPU-specअगरic layer and a (hopefully)
 * GPU-agnostic lower layer: It's the GPU driver responsibility to
 * call the slave methods when appropriate.
 *
 * drm_i2c_encoder_init() provides a way to get an implementation of
 * this.
 */
काष्ठा drm_encoder_slave अणु
	काष्ठा drm_encoder base;

	स्थिर काष्ठा drm_encoder_slave_funcs *slave_funcs;
	व्योम *slave_priv;
	व्योम *bus_priv;
पूर्ण;
#घोषणा to_encoder_slave(x) container_of((x), काष्ठा drm_encoder_slave, base)

पूर्णांक drm_i2c_encoder_init(काष्ठा drm_device *dev,
			 काष्ठा drm_encoder_slave *encoder,
			 काष्ठा i2c_adapter *adap,
			 स्थिर काष्ठा i2c_board_info *info);


/**
 * काष्ठा drm_i2c_encoder_driver
 *
 * Describes a device driver क्रम an encoder connected to the GPU
 * through an I2C bus. In addition to the entry poपूर्णांकs in @i2c_driver
 * an @encoder_init function should be provided. It will be called to
 * give the driver an opportunity to allocate any per-encoder data
 * काष्ठाures and to initialize the @slave_funcs and (optionally)
 * @slave_priv members of @encoder.
 */
काष्ठा drm_i2c_encoder_driver अणु
	काष्ठा i2c_driver i2c_driver;

	पूर्णांक (*encoder_init)(काष्ठा i2c_client *client,
			    काष्ठा drm_device *dev,
			    काष्ठा drm_encoder_slave *encoder);

पूर्ण;
#घोषणा to_drm_i2c_encoder_driver(x) container_of((x),			\
						  काष्ठा drm_i2c_encoder_driver, \
						  i2c_driver)

/**
 * drm_i2c_encoder_get_client - Get the I2C client corresponding to an encoder
 */
अटल अंतरभूत काष्ठा i2c_client *drm_i2c_encoder_get_client(काष्ठा drm_encoder *encoder)
अणु
	वापस (काष्ठा i2c_client *)to_encoder_slave(encoder)->bus_priv;
पूर्ण

/**
 * drm_i2c_encoder_रेजिस्टर - Register an I2C encoder driver
 * @owner:	Module containing the driver.
 * @driver:	Driver to be रेजिस्टरed.
 */
अटल अंतरभूत पूर्णांक drm_i2c_encoder_रेजिस्टर(काष्ठा module *owner,
					   काष्ठा drm_i2c_encoder_driver *driver)
अणु
	वापस i2c_रेजिस्टर_driver(owner, &driver->i2c_driver);
पूर्ण

/**
 * drm_i2c_encoder_unरेजिस्टर - Unरेजिस्टर an I2C encoder driver
 * @driver:	Driver to be unरेजिस्टरed.
 */
अटल अंतरभूत व्योम drm_i2c_encoder_unरेजिस्टर(काष्ठा drm_i2c_encoder_driver *driver)
अणु
	i2c_del_driver(&driver->i2c_driver);
पूर्ण

व्योम drm_i2c_encoder_destroy(काष्ठा drm_encoder *encoder);


/*
 * Wrapper fxns which can be plugged in to drm_encoder_helper_funcs:
 */

व्योम drm_i2c_encoder_dpms(काष्ठा drm_encoder *encoder, पूर्णांक mode);
bool drm_i2c_encoder_mode_fixup(काष्ठा drm_encoder *encoder,
		स्थिर काष्ठा drm_display_mode *mode,
		काष्ठा drm_display_mode *adjusted_mode);
व्योम drm_i2c_encoder_prepare(काष्ठा drm_encoder *encoder);
व्योम drm_i2c_encoder_commit(काष्ठा drm_encoder *encoder);
व्योम drm_i2c_encoder_mode_set(काष्ठा drm_encoder *encoder,
		काष्ठा drm_display_mode *mode,
		काष्ठा drm_display_mode *adjusted_mode);
क्रमागत drm_connector_status drm_i2c_encoder_detect(काष्ठा drm_encoder *encoder,
	    काष्ठा drm_connector *connector);
व्योम drm_i2c_encoder_save(काष्ठा drm_encoder *encoder);
व्योम drm_i2c_encoder_restore(काष्ठा drm_encoder *encoder);


#पूर्ण_अगर
