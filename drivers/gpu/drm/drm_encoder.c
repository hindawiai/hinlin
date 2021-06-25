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

#समावेश <linux/export.h>

#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_encoder.h>
#समावेश <drm/drm_managed.h>

#समावेश "drm_crtc_internal.h"

/**
 * DOC: overview
 *
 * Encoders represent the connecting element between the CRTC (as the overall
 * pixel pipeline, represented by &काष्ठा drm_crtc) and the connectors (as the
 * generic sink entity, represented by &काष्ठा drm_connector). An encoder takes
 * pixel data from a CRTC and converts it to a क्रमmat suitable क्रम any attached
 * connector. Encoders are objects exposed to userspace, originally to allow
 * userspace to infer cloning and connector/CRTC restrictions. Unक्रमtunately
 * almost all drivers get this wrong, making the uabi pretty much useless. On
 * top of that the exposed restrictions are too simple क्रम today's hardware, and
 * the recommended way to infer restrictions is by using the
 * DRM_MODE_ATOMIC_TEST_ONLY flag क्रम the atomic IOCTL.
 *
 * Otherwise encoders aren't used in the uapi at all (any modeset request from
 * userspace directly connects a connector with a CRTC), drivers are thereक्रमe
 * मुक्त to use them however they wish. Modeset helper libraries make strong use
 * of encoders to facilitate code sharing. But क्रम more complex settings it is
 * usually better to move shared code पूर्णांकo a separate &drm_bridge. Compared to
 * encoders, bridges also have the benefit of being purely an पूर्णांकernal
 * असलtraction since they are not exposed to userspace at all.
 *
 * Encoders are initialized with drm_encoder_init() and cleaned up using
 * drm_encoder_cleanup().
 */
अटल स्थिर काष्ठा drm_prop_क्रमागत_list drm_encoder_क्रमागत_list[] = अणु
	अणु DRM_MODE_ENCODER_NONE, "None" पूर्ण,
	अणु DRM_MODE_ENCODER_DAC, "DAC" पूर्ण,
	अणु DRM_MODE_ENCODER_TMDS, "TMDS" पूर्ण,
	अणु DRM_MODE_ENCODER_LVDS, "LVDS" पूर्ण,
	अणु DRM_MODE_ENCODER_TVDAC, "TV" पूर्ण,
	अणु DRM_MODE_ENCODER_VIRTUAL, "Virtual" पूर्ण,
	अणु DRM_MODE_ENCODER_DSI, "DSI" पूर्ण,
	अणु DRM_MODE_ENCODER_DPMST, "DP MST" पूर्ण,
	अणु DRM_MODE_ENCODER_DPI, "DPI" पूर्ण,
पूर्ण;

पूर्णांक drm_encoder_रेजिस्टर_all(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_encoder *encoder;
	पूर्णांक ret = 0;

	drm_क्रम_each_encoder(encoder, dev) अणु
		अगर (encoder->funcs && encoder->funcs->late_रेजिस्टर)
			ret = encoder->funcs->late_रेजिस्टर(encoder);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

व्योम drm_encoder_unरेजिस्टर_all(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_encoder *encoder;

	drm_क्रम_each_encoder(encoder, dev) अणु
		अगर (encoder->funcs && encoder->funcs->early_unरेजिस्टर)
			encoder->funcs->early_unरेजिस्टर(encoder);
	पूर्ण
पूर्ण

__म_लिखो(5, 0)
अटल पूर्णांक __drm_encoder_init(काष्ठा drm_device *dev,
			      काष्ठा drm_encoder *encoder,
			      स्थिर काष्ठा drm_encoder_funcs *funcs,
			      पूर्णांक encoder_type, स्थिर अक्षर *name, बहु_सूची ap)
अणु
	पूर्णांक ret;

	/* encoder index is used with 32bit biपंचांगasks */
	अगर (WARN_ON(dev->mode_config.num_encoder >= 32))
		वापस -EINVAL;

	ret = drm_mode_object_add(dev, &encoder->base, DRM_MODE_OBJECT_ENCODER);
	अगर (ret)
		वापस ret;

	encoder->dev = dev;
	encoder->encoder_type = encoder_type;
	encoder->funcs = funcs;
	अगर (name) अणु
		encoder->name = kvaप्र_लिखो(GFP_KERNEL, name, ap);
	पूर्ण अन्यथा अणु
		encoder->name = kaप्र_लिखो(GFP_KERNEL, "%s-%d",
					  drm_encoder_क्रमागत_list[encoder_type].name,
					  encoder->base.id);
	पूर्ण
	अगर (!encoder->name) अणु
		ret = -ENOMEM;
		जाओ out_put;
	पूर्ण

	INIT_LIST_HEAD(&encoder->bridge_chain);
	list_add_tail(&encoder->head, &dev->mode_config.encoder_list);
	encoder->index = dev->mode_config.num_encoder++;

out_put:
	अगर (ret)
		drm_mode_object_unरेजिस्टर(dev, &encoder->base);

	वापस ret;
पूर्ण

/**
 * drm_encoder_init - Init a pपुनः_स्मृतिated encoder
 * @dev: drm device
 * @encoder: the encoder to init
 * @funcs: callbacks क्रम this encoder
 * @encoder_type: user visible type of the encoder
 * @name: म_लिखो style क्रमmat string क्रम the encoder name, or शून्य क्रम शेष name
 *
 * Initializes a pपुनः_स्मृतिated encoder. Encoder should be subclassed as part of
 * driver encoder objects. At driver unload समय the driver's
 * &drm_encoder_funcs.destroy hook should call drm_encoder_cleanup() and kमुक्त()
 * the encoder काष्ठाure. The encoder काष्ठाure should not be allocated with
 * devm_kzalloc().
 *
 * Note: consider using drmm_encoder_alloc() instead of drm_encoder_init() to
 * let the DRM managed resource infraकाष्ठाure take care of cleanup and
 * deallocation.
 *
 * Returns:
 * Zero on success, error code on failure.
 */
पूर्णांक drm_encoder_init(काष्ठा drm_device *dev,
		     काष्ठा drm_encoder *encoder,
		     स्थिर काष्ठा drm_encoder_funcs *funcs,
		     पूर्णांक encoder_type, स्थिर अक्षर *name, ...)
अणु
	बहु_सूची ap;
	पूर्णांक ret;

	WARN_ON(!funcs->destroy);

	बहु_शुरू(ap, name);
	ret = __drm_encoder_init(dev, encoder, funcs, encoder_type, name, ap);
	बहु_पूर्ण(ap);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_encoder_init);

/**
 * drm_encoder_cleanup - cleans up an initialised encoder
 * @encoder: encoder to cleanup
 *
 * Cleans up the encoder but करोesn't मुक्त the object.
 */
व्योम drm_encoder_cleanup(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा drm_bridge *bridge, *next;

	/* Note that the encoder_list is considered to be अटल; should we
	 * हटाओ the drm_encoder at runसमय we would have to decrement all
	 * the indices on the drm_encoder after us in the encoder_list.
	 */

	list_क्रम_each_entry_safe(bridge, next, &encoder->bridge_chain,
				 chain_node)
		drm_bridge_detach(bridge);

	drm_mode_object_unरेजिस्टर(dev, &encoder->base);
	kमुक्त(encoder->name);
	list_del(&encoder->head);
	dev->mode_config.num_encoder--;

	स_रखो(encoder, 0, माप(*encoder));
पूर्ण
EXPORT_SYMBOL(drm_encoder_cleanup);

अटल व्योम drmm_encoder_alloc_release(काष्ठा drm_device *dev, व्योम *ptr)
अणु
	काष्ठा drm_encoder *encoder = ptr;

	अगर (WARN_ON(!encoder->dev))
		वापस;

	drm_encoder_cleanup(encoder);
पूर्ण

व्योम *__drmm_encoder_alloc(काष्ठा drm_device *dev, माप_प्रकार size, माप_प्रकार offset,
			   स्थिर काष्ठा drm_encoder_funcs *funcs,
			   पूर्णांक encoder_type, स्थिर अक्षर *name, ...)
अणु
	व्योम *container;
	काष्ठा drm_encoder *encoder;
	बहु_सूची ap;
	पूर्णांक ret;

	अगर (WARN_ON(funcs && funcs->destroy))
		वापस ERR_PTR(-EINVAL);

	container = drmm_kzalloc(dev, size, GFP_KERNEL);
	अगर (!container)
		वापस ERR_PTR(-EINVAL);

	encoder = container + offset;

	बहु_शुरू(ap, name);
	ret = __drm_encoder_init(dev, encoder, funcs, encoder_type, name, ap);
	बहु_पूर्ण(ap);
	अगर (ret)
		वापस ERR_PTR(ret);

	ret = drmm_add_action_or_reset(dev, drmm_encoder_alloc_release, encoder);
	अगर (ret)
		वापस ERR_PTR(ret);

	वापस container;
पूर्ण
EXPORT_SYMBOL(__drmm_encoder_alloc);

अटल काष्ठा drm_crtc *drm_encoder_get_crtc(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_connector *connector;
	काष्ठा drm_device *dev = encoder->dev;
	bool uses_atomic = false;
	काष्ठा drm_connector_list_iter conn_iter;

	/* For atomic drivers only state objects are synchronously updated and
	 * रक्षित by modeset locks, so check those first. */
	drm_connector_list_iter_begin(dev, &conn_iter);
	drm_क्रम_each_connector_iter(connector, &conn_iter) अणु
		अगर (!connector->state)
			जारी;

		uses_atomic = true;

		अगर (connector->state->best_encoder != encoder)
			जारी;

		drm_connector_list_iter_end(&conn_iter);
		वापस connector->state->crtc;
	पूर्ण
	drm_connector_list_iter_end(&conn_iter);

	/* Don't वापस stale data (e.g. pending async disable). */
	अगर (uses_atomic)
		वापस शून्य;

	वापस encoder->crtc;
पूर्ण

पूर्णांक drm_mode_getencoder(काष्ठा drm_device *dev, व्योम *data,
			काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_mode_get_encoder *enc_resp = data;
	काष्ठा drm_encoder *encoder;
	काष्ठा drm_crtc *crtc;

	अगर (!drm_core_check_feature(dev, DRIVER_MODESET))
		वापस -EOPNOTSUPP;

	encoder = drm_encoder_find(dev, file_priv, enc_resp->encoder_id);
	अगर (!encoder)
		वापस -ENOENT;

	drm_modeset_lock(&dev->mode_config.connection_mutex, शून्य);
	crtc = drm_encoder_get_crtc(encoder);
	अगर (crtc && drm_lease_held(file_priv, crtc->base.id))
		enc_resp->crtc_id = crtc->base.id;
	अन्यथा
		enc_resp->crtc_id = 0;
	drm_modeset_unlock(&dev->mode_config.connection_mutex);

	enc_resp->encoder_type = encoder->encoder_type;
	enc_resp->encoder_id = encoder->base.id;
	enc_resp->possible_crtcs = drm_lease_filter_crtcs(file_priv,
							  encoder->possible_crtcs);
	enc_resp->possible_clones = encoder->possible_clones;

	वापस 0;
पूर्ण
