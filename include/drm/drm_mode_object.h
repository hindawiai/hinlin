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

#अगर_अघोषित __DRM_MODESET_H__
#घोषणा __DRM_MODESET_H__

#समावेश <linux/kref.h>
#समावेश <drm/drm_lease.h>
काष्ठा drm_object_properties;
काष्ठा drm_property;
काष्ठा drm_device;
काष्ठा drm_file;

/**
 * काष्ठा drm_mode_object - base काष्ठाure क्रम modeset objects
 * @id: userspace visible identअगरier
 * @type: type of the object, one of DRM_MODE_OBJECT\_\*
 * @properties: properties attached to this object, including values
 * @refcount: reference count क्रम objects which with dynamic lअगरeसमय
 * @मुक्त_cb: मुक्त function callback, only set क्रम objects with dynamic lअगरeसमय
 *
 * Base काष्ठाure क्रम modeset objects visible to userspace. Objects can be
 * looked up using drm_mode_object_find(). Besides basic uapi पूर्णांकerface
 * properties like @id and @type it provides two services:
 *
 * - It tracks attached properties and their values. This is used by &drm_crtc,
 *   &drm_plane and &drm_connector. Properties are attached by calling
 *   drm_object_attach_property() beक्रमe the object is visible to userspace.
 *
 * - For objects with dynamic lअगरeबार (as indicated by a non-शून्य @मुक्त_cb) it
 *   provides reference counting through drm_mode_object_get() and
 *   drm_mode_object_put(). This is used by &drm_framebuffer, &drm_connector
 *   and &drm_property_blob. These objects provide specialized reference
 *   counting wrappers.
 */
काष्ठा drm_mode_object अणु
	uपूर्णांक32_t id;
	uपूर्णांक32_t type;
	काष्ठा drm_object_properties *properties;
	काष्ठा kref refcount;
	व्योम (*मुक्त_cb)(काष्ठा kref *kref);
पूर्ण;

#घोषणा DRM_OBJECT_MAX_PROPERTY 24
/**
 * काष्ठा drm_object_properties - property tracking क्रम &drm_mode_object
 */
काष्ठा drm_object_properties अणु
	/**
	 * @count: number of valid properties, must be less than or equal to
	 * DRM_OBJECT_MAX_PROPERTY.
	 */

	पूर्णांक count;
	/**
	 * @properties: Array of poपूर्णांकers to &drm_property.
	 *
	 * NOTE: अगर we ever start dynamically destroying properties (ie.
	 * not at drm_mode_config_cleanup() समय), then we'd have to करो
	 * a better job of detaching property from mode objects to aव्योम
	 * dangling property poपूर्णांकers:
	 */
	काष्ठा drm_property *properties[DRM_OBJECT_MAX_PROPERTY];

	/**
	 * @values: Array to store the property values, matching @properties. Do
	 * not पढ़ो/ग_लिखो values directly, but use
	 * drm_object_property_get_value() and drm_object_property_set_value().
	 *
	 * Note that atomic drivers करो not store mutable properties in this
	 * array, but only the decoded values in the corresponding state
	 * काष्ठाure. The decoding is करोne using the &drm_crtc.atomic_get_property and
	 * &drm_crtc.atomic_set_property hooks क्रम &काष्ठा drm_crtc. For
	 * &काष्ठा drm_plane the hooks are &drm_plane_funcs.atomic_get_property and
	 * &drm_plane_funcs.atomic_set_property. And क्रम &काष्ठा drm_connector
	 * the hooks are &drm_connector_funcs.atomic_get_property and
	 * &drm_connector_funcs.atomic_set_property .
	 *
	 * Hence atomic drivers should not use drm_object_property_set_value()
	 * and drm_object_property_get_value() on mutable objects, i.e. those
	 * without the DRM_MODE_PROP_IMMUTABLE flag set.
	 */
	uपूर्णांक64_t values[DRM_OBJECT_MAX_PROPERTY];
पूर्ण;

/* Aव्योम boilerplate.  I'm tired of typing. */
#घोषणा DRM_ENUM_NAME_FN(fnname, list)				\
	स्थिर अक्षर *fnname(पूर्णांक val)				\
	अणु							\
		पूर्णांक i;						\
		क्रम (i = 0; i < ARRAY_SIZE(list); i++) अणु	\
			अगर (list[i].type == val)		\
				वापस list[i].name;		\
		पूर्ण						\
		वापस "(unknown)";				\
	पूर्ण

काष्ठा drm_mode_object *drm_mode_object_find(काष्ठा drm_device *dev,
					     काष्ठा drm_file *file_priv,
					     uपूर्णांक32_t id, uपूर्णांक32_t type);
व्योम drm_mode_object_get(काष्ठा drm_mode_object *obj);
व्योम drm_mode_object_put(काष्ठा drm_mode_object *obj);

पूर्णांक drm_object_property_set_value(काष्ठा drm_mode_object *obj,
				  काष्ठा drm_property *property,
				  uपूर्णांक64_t val);
पूर्णांक drm_object_property_get_value(काष्ठा drm_mode_object *obj,
				  काष्ठा drm_property *property,
				  uपूर्णांक64_t *value);

व्योम drm_object_attach_property(काष्ठा drm_mode_object *obj,
				काष्ठा drm_property *property,
				uपूर्णांक64_t init_val);

bool drm_mode_object_lease_required(uपूर्णांक32_t type);
#पूर्ण_अगर
