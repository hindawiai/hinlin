<शैली गुरु>
/*
 * Copyright (c) 2016 Intel Corporation
 *
 * Permission to use, copy, modअगरy, distribute, and sell this software and its
 * करोcumentation क्रम any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that copyright
 * notice and this permission notice appear in supporting करोcumentation, and
 * that the name of the copyright holders not be used in advertising or
 * खुलाity pertaining to distribution of the software without specअगरic,
 * written prior permission.  The copyright holders make no representations
 * about the suitability of this software क्रम any purpose.  It is provided "as
 * is" without express or implied warranty.
 *
 * THE COPYRIGHT HOLDERS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY SPECIAL, INसूचीECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THIS SOFTWARE.
 */

#अगर_अघोषित __DRM_ENCODER_H__
#घोषणा __DRM_ENCODER_H__

#समावेश <linux/list.h>
#समावेश <linux/प्रकार.स>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_mode.h>
#समावेश <drm/drm_mode_object.h>
#समावेश <drm/drm_util.h>

काष्ठा drm_encoder;

/**
 * काष्ठा drm_encoder_funcs - encoder controls
 *
 * Encoders sit between CRTCs and connectors.
 */
काष्ठा drm_encoder_funcs अणु
	/**
	 * @reset:
	 *
	 * Reset encoder hardware and software state to off. This function isn't
	 * called by the core directly, only through drm_mode_config_reset().
	 * It's not a helper hook only क्रम historical reasons.
	 */
	व्योम (*reset)(काष्ठा drm_encoder *encoder);

	/**
	 * @destroy:
	 *
	 * Clean up encoder resources. This is only called at driver unload समय
	 * through drm_mode_config_cleanup() since an encoder cannot be
	 * hotplugged in DRM.
	 */
	व्योम (*destroy)(काष्ठा drm_encoder *encoder);

	/**
	 * @late_रेजिस्टर:
	 *
	 * This optional hook can be used to रेजिस्टर additional userspace
	 * पूर्णांकerfaces attached to the encoder like debugfs पूर्णांकerfaces.
	 * It is called late in the driver load sequence from drm_dev_रेजिस्टर().
	 * Everything added from this callback should be unरेजिस्टरed in
	 * the early_unरेजिस्टर callback.
	 *
	 * Returns:
	 *
	 * 0 on success, or a negative error code on failure.
	 */
	पूर्णांक (*late_रेजिस्टर)(काष्ठा drm_encoder *encoder);

	/**
	 * @early_unरेजिस्टर:
	 *
	 * This optional hook should be used to unरेजिस्टर the additional
	 * userspace पूर्णांकerfaces attached to the encoder from
	 * @late_रेजिस्टर. It is called from drm_dev_unरेजिस्टर(),
	 * early in the driver unload sequence to disable userspace access
	 * beक्रमe data काष्ठाures are tornकरोwn.
	 */
	व्योम (*early_unरेजिस्टर)(काष्ठा drm_encoder *encoder);
पूर्ण;

/**
 * काष्ठा drm_encoder - central DRM encoder काष्ठाure
 * @dev: parent DRM device
 * @head: list management
 * @base: base KMS object
 * @name: human पढ़ोable name, can be overwritten by the driver
 * @funcs: control functions, can be शून्य क्रम simple managed encoders
 * @helper_निजी: mid-layer निजी data
 *
 * CRTCs drive pixels to encoders, which convert them पूर्णांकo संकेतs
 * appropriate क्रम a given connector or set of connectors.
 */
काष्ठा drm_encoder अणु
	काष्ठा drm_device *dev;
	काष्ठा list_head head;

	काष्ठा drm_mode_object base;
	अक्षर *name;
	/**
	 * @encoder_type:
	 *
	 * One of the DRM_MODE_ENCODER_<foo> types in drm_mode.h. The following
	 * encoder types are defined thus far:
	 *
	 * - DRM_MODE_ENCODER_DAC क्रम VGA and analog on DVI-I/DVI-A.
	 *
	 * - DRM_MODE_ENCODER_TMDS क्रम DVI, HDMI and (embedded) DisplayPort.
	 *
	 * - DRM_MODE_ENCODER_LVDS क्रम display panels, or in general any panel
	 *   with a proprietary parallel connector.
	 *
	 * - DRM_MODE_ENCODER_TVDAC क्रम TV output (Composite, S-Video,
	 *   Component, SCART).
	 *
	 * - DRM_MODE_ENCODER_VIRTUAL क्रम भव machine displays
	 *
	 * - DRM_MODE_ENCODER_DSI क्रम panels connected using the DSI serial bus.
	 *
	 * - DRM_MODE_ENCODER_DPI क्रम panels connected using the DPI parallel
	 *   bus.
	 *
	 * - DRM_MODE_ENCODER_DPMST क्रम special fake encoders used to allow
	 *   mutliple DP MST streams to share one physical encoder.
	 */
	पूर्णांक encoder_type;

	/**
	 * @index: Position inside the mode_config.list, can be used as an array
	 * index. It is invariant over the lअगरeसमय of the encoder.
	 */
	अचिन्हित index;

	/**
	 * @possible_crtcs: Biपंचांगask of potential CRTC bindings, using
	 * drm_crtc_index() as the index पूर्णांकo the bitfield. The driver must set
	 * the bits क्रम all &drm_crtc objects this encoder can be connected to
	 * beक्रमe calling drm_dev_रेजिस्टर().
	 *
	 * You will get a WARN अगर you get this wrong in the driver.
	 *
	 * Note that since CRTC objects can't be hotplugged the asचिन्हित indices
	 * are stable and hence known beक्रमe रेजिस्टरing all objects.
	 */
	uपूर्णांक32_t possible_crtcs;

	/**
	 * @possible_clones: Biपंचांगask of potential sibling encoders क्रम cloning,
	 * using drm_encoder_index() as the index पूर्णांकo the bitfield. The driver
	 * must set the bits क्रम all &drm_encoder objects which can clone a
	 * &drm_crtc together with this encoder beक्रमe calling
	 * drm_dev_रेजिस्टर(). Drivers should set the bit representing the
	 * encoder itself, too. Cloning bits should be set such that when two
	 * encoders can be used in a cloned configuration, they both should have
	 * each another bits set.
	 *
	 * As an exception to the above rule अगर the driver करोesn't implement
	 * any cloning it can leave @possible_clones set to 0. The core will
	 * स्वतःmagically fix this up by setting the bit क्रम the encoder itself.
	 *
	 * You will get a WARN अगर you get this wrong in the driver.
	 *
	 * Note that since encoder objects can't be hotplugged the asचिन्हित indices
	 * are stable and hence known beक्रमe रेजिस्टरing all objects.
	 */
	uपूर्णांक32_t possible_clones;

	/**
	 * @crtc: Currently bound CRTC, only really meaningful क्रम non-atomic
	 * drivers.  Atomic drivers should instead check
	 * &drm_connector_state.crtc.
	 */
	काष्ठा drm_crtc *crtc;

	/**
	 * @bridge_chain: Bridges attached to this encoder. Drivers shall not
	 * access this field directly.
	 */
	काष्ठा list_head bridge_chain;

	स्थिर काष्ठा drm_encoder_funcs *funcs;
	स्थिर काष्ठा drm_encoder_helper_funcs *helper_निजी;
पूर्ण;

#घोषणा obj_to_encoder(x) container_of(x, काष्ठा drm_encoder, base)

__म_लिखो(5, 6)
पूर्णांक drm_encoder_init(काष्ठा drm_device *dev,
		     काष्ठा drm_encoder *encoder,
		     स्थिर काष्ठा drm_encoder_funcs *funcs,
		     पूर्णांक encoder_type, स्थिर अक्षर *name, ...);

__म_लिखो(6, 7)
व्योम *__drmm_encoder_alloc(काष्ठा drm_device *dev,
			   माप_प्रकार size, माप_प्रकार offset,
			   स्थिर काष्ठा drm_encoder_funcs *funcs,
			   पूर्णांक encoder_type,
			   स्थिर अक्षर *name, ...);

/**
 * drmm_encoder_alloc - Allocate and initialize an encoder
 * @dev: drm device
 * @type: the type of the काष्ठा which contains काष्ठा &drm_encoder
 * @member: the name of the &drm_encoder within @type
 * @funcs: callbacks क्रम this encoder (optional)
 * @encoder_type: user visible type of the encoder
 * @name: म_लिखो style क्रमmat string क्रम the encoder name, or शून्य क्रम शेष name
 *
 * Allocates and initializes an encoder. Encoder should be subclassed as part of
 * driver encoder objects. Cleanup is स्वतःmatically handled through रेजिस्टरing
 * drm_encoder_cleanup() with drmm_add_action().
 *
 * The @drm_encoder_funcs.destroy hook must be शून्य.
 *
 * Returns:
 * Poपूर्णांकer to new encoder, or ERR_PTR on failure.
 */
#घोषणा drmm_encoder_alloc(dev, type, member, funcs, encoder_type, name, ...) \
	((type *)__drmm_encoder_alloc(dev, माप(type), \
				      दुरत्व(type, member), funcs, \
				      encoder_type, name, ##__VA_ARGS__))

/**
 * drmm_plain_encoder_alloc - Allocate and initialize an encoder
 * @dev: drm device
 * @funcs: callbacks क्रम this encoder (optional)
 * @encoder_type: user visible type of the encoder
 * @name: म_लिखो style क्रमmat string क्रम the encoder name, or शून्य क्रम शेष name
 *
 * This is a simplअगरied version of drmm_encoder_alloc(), which only allocates
 * and वापसs a काष्ठा drm_encoder instance, with no subclassing.
 *
 * Returns:
 * Poपूर्णांकer to the new drm_encoder काष्ठा, or ERR_PTR on failure.
 */
#घोषणा drmm_plain_encoder_alloc(dev, funcs, encoder_type, name, ...) \
	((काष्ठा drm_encoder *) \
	 __drmm_encoder_alloc(dev, माप(काष्ठा drm_encoder), \
			      0, funcs, encoder_type, name, ##__VA_ARGS__))

/**
 * drm_encoder_index - find the index of a रेजिस्टरed encoder
 * @encoder: encoder to find index क्रम
 *
 * Given a रेजिस्टरed encoder, वापस the index of that encoder within a DRM
 * device's list of encoders.
 */
अटल अंतरभूत अचिन्हित पूर्णांक drm_encoder_index(स्थिर काष्ठा drm_encoder *encoder)
अणु
	वापस encoder->index;
पूर्ण

/**
 * drm_encoder_mask - find the mask of a रेजिस्टरed encoder
 * @encoder: encoder to find mask क्रम
 *
 * Given a रेजिस्टरed encoder, वापस the mask bit of that encoder क्रम an
 * encoder's possible_clones field.
 */
अटल अंतरभूत u32 drm_encoder_mask(स्थिर काष्ठा drm_encoder *encoder)
अणु
	वापस 1 << drm_encoder_index(encoder);
पूर्ण

/**
 * drm_encoder_crtc_ok - can a given crtc drive a given encoder?
 * @encoder: encoder to test
 * @crtc: crtc to test
 *
 * Returns false अगर @encoder can't be driven by @crtc, true otherwise.
 */
अटल अंतरभूत bool drm_encoder_crtc_ok(काष्ठा drm_encoder *encoder,
				       काष्ठा drm_crtc *crtc)
अणु
	वापस !!(encoder->possible_crtcs & drm_crtc_mask(crtc));
पूर्ण

/**
 * drm_encoder_find - find a &drm_encoder
 * @dev: DRM device
 * @file_priv: drm file to check क्रम lease against.
 * @id: encoder id
 *
 * Returns the encoder with @id, शून्य अगर it करोesn't exist. Simple wrapper around
 * drm_mode_object_find().
 */
अटल अंतरभूत काष्ठा drm_encoder *drm_encoder_find(काष्ठा drm_device *dev,
						   काष्ठा drm_file *file_priv,
						   uपूर्णांक32_t id)
अणु
	काष्ठा drm_mode_object *mo;

	mo = drm_mode_object_find(dev, file_priv, id, DRM_MODE_OBJECT_ENCODER);

	वापस mo ? obj_to_encoder(mo) : शून्य;
पूर्ण

व्योम drm_encoder_cleanup(काष्ठा drm_encoder *encoder);

/**
 * drm_क्रम_each_encoder_mask - iterate over encoders specअगरied by biपंचांगask
 * @encoder: the loop cursor
 * @dev: the DRM device
 * @encoder_mask: biपंचांगask of encoder indices
 *
 * Iterate over all encoders specअगरied by biपंचांगask.
 */
#घोषणा drm_क्रम_each_encoder_mask(encoder, dev, encoder_mask) \
	list_क्रम_each_entry((encoder), &(dev)->mode_config.encoder_list, head) \
		क्रम_each_अगर ((encoder_mask) & drm_encoder_mask(encoder))

/**
 * drm_क्रम_each_encoder - iterate over all encoders
 * @encoder: the loop cursor
 * @dev: the DRM device
 *
 * Iterate over all encoders of @dev.
 */
#घोषणा drm_क्रम_each_encoder(encoder, dev) \
	list_क्रम_each_entry(encoder, &(dev)->mode_config.encoder_list, head)

#पूर्ण_अगर
