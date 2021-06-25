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
#समावेश <linux/uaccess.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_mode_object.h>
#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "drm_crtc_internal.h"

/*
 * Internal function to assign a slot in the object idr and optionally
 * रेजिस्टर the object पूर्णांकo the idr.
 */
पूर्णांक __drm_mode_object_add(काष्ठा drm_device *dev, काष्ठा drm_mode_object *obj,
			  uपूर्णांक32_t obj_type, bool रेजिस्टर_obj,
			  व्योम (*obj_मुक्त_cb)(काष्ठा kref *kref))
अणु
	पूर्णांक ret;

	WARN_ON(!dev->driver->load && dev->रेजिस्टरed && !obj_मुक्त_cb);

	mutex_lock(&dev->mode_config.idr_mutex);
	ret = idr_alloc(&dev->mode_config.object_idr, रेजिस्टर_obj ? obj : शून्य,
			1, 0, GFP_KERNEL);
	अगर (ret >= 0) अणु
		/*
		 * Set up the object linking under the protection of the idr
		 * lock so that other users can't see inconsistent state.
		 */
		obj->id = ret;
		obj->type = obj_type;
		अगर (obj_मुक्त_cb) अणु
			obj->मुक्त_cb = obj_मुक्त_cb;
			kref_init(&obj->refcount);
		पूर्ण
	पूर्ण
	mutex_unlock(&dev->mode_config.idr_mutex);

	वापस ret < 0 ? ret : 0;
पूर्ण

/**
 * drm_mode_object_add - allocate a new modeset identअगरier
 * @dev: DRM device
 * @obj: object poपूर्णांकer, used to generate unique ID
 * @obj_type: object type
 *
 * Create a unique identअगरier based on @ptr in @dev's identअगरier space.  Used
 * क्रम tracking modes, CRTCs and connectors.
 *
 * Returns:
 * Zero on success, error code on failure.
 */
पूर्णांक drm_mode_object_add(काष्ठा drm_device *dev,
			काष्ठा drm_mode_object *obj, uपूर्णांक32_t obj_type)
अणु
	वापस __drm_mode_object_add(dev, obj, obj_type, true, शून्य);
पूर्ण

व्योम drm_mode_object_रेजिस्टर(काष्ठा drm_device *dev,
			      काष्ठा drm_mode_object *obj)
अणु
	mutex_lock(&dev->mode_config.idr_mutex);
	idr_replace(&dev->mode_config.object_idr, obj, obj->id);
	mutex_unlock(&dev->mode_config.idr_mutex);
पूर्ण

/**
 * drm_mode_object_unरेजिस्टर - मुक्त a modeset identअगरer
 * @dev: DRM device
 * @object: object to मुक्त
 *
 * Free @id from @dev's unique identअगरier pool.
 * This function can be called multiple बार, and guards against
 * multiple removals.
 * These modeset identअगरiers are _not_ reference counted. Hence करोn't use this
 * क्रम reference counted modeset objects like framebuffers.
 */
व्योम drm_mode_object_unरेजिस्टर(काष्ठा drm_device *dev,
				काष्ठा drm_mode_object *object)
अणु
	WARN_ON(!dev->driver->load && dev->रेजिस्टरed && !object->मुक्त_cb);

	mutex_lock(&dev->mode_config.idr_mutex);
	अगर (object->id) अणु
		idr_हटाओ(&dev->mode_config.object_idr, object->id);
		object->id = 0;
	पूर्ण
	mutex_unlock(&dev->mode_config.idr_mutex);
पूर्ण

/**
 * drm_mode_object_lease_required - check types which must be leased to be used
 * @type: type of object
 *
 * Returns whether the provided type of drm_mode_object must
 * be owned or leased to be used by a process.
 */
bool drm_mode_object_lease_required(uपूर्णांक32_t type)
अणु
	चयन(type) अणु
	हाल DRM_MODE_OBJECT_CRTC:
	हाल DRM_MODE_OBJECT_CONNECTOR:
	हाल DRM_MODE_OBJECT_PLANE:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

काष्ठा drm_mode_object *__drm_mode_object_find(काष्ठा drm_device *dev,
					       काष्ठा drm_file *file_priv,
					       uपूर्णांक32_t id, uपूर्णांक32_t type)
अणु
	काष्ठा drm_mode_object *obj = शून्य;

	mutex_lock(&dev->mode_config.idr_mutex);
	obj = idr_find(&dev->mode_config.object_idr, id);
	अगर (obj && type != DRM_MODE_OBJECT_ANY && obj->type != type)
		obj = शून्य;
	अगर (obj && obj->id != id)
		obj = शून्य;

	अगर (obj && drm_mode_object_lease_required(obj->type) &&
	    !_drm_lease_held(file_priv, obj->id))
		obj = शून्य;

	अगर (obj && obj->मुक्त_cb) अणु
		अगर (!kref_get_unless_zero(&obj->refcount))
			obj = शून्य;
	पूर्ण
	mutex_unlock(&dev->mode_config.idr_mutex);

	वापस obj;
पूर्ण

/**
 * drm_mode_object_find - look up a drm object with अटल lअगरeसमय
 * @dev: drm device
 * @file_priv: drm file
 * @id: id of the mode object
 * @type: type of the mode object
 *
 * This function is used to look up a modeset object. It will acquire a
 * reference क्रम reference counted objects. This reference must be dropped again
 * by callind drm_mode_object_put().
 */
काष्ठा drm_mode_object *drm_mode_object_find(काष्ठा drm_device *dev,
		काष्ठा drm_file *file_priv,
		uपूर्णांक32_t id, uपूर्णांक32_t type)
अणु
	काष्ठा drm_mode_object *obj = शून्य;

	obj = __drm_mode_object_find(dev, file_priv, id, type);
	वापस obj;
पूर्ण
EXPORT_SYMBOL(drm_mode_object_find);

/**
 * drm_mode_object_put - release a mode object reference
 * @obj: DRM mode object
 *
 * This function decrements the object's refcount अगर it is a refcounted modeset
 * object. It is a no-op on any other object. This is used to drop references
 * acquired with drm_mode_object_get().
 */
व्योम drm_mode_object_put(काष्ठा drm_mode_object *obj)
अणु
	अगर (obj->मुक्त_cb) अणु
		DRM_DEBUG("OBJ ID: %d (%d)\n", obj->id, kref_पढ़ो(&obj->refcount));
		kref_put(&obj->refcount, obj->मुक्त_cb);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(drm_mode_object_put);

/**
 * drm_mode_object_get - acquire a mode object reference
 * @obj: DRM mode object
 *
 * This function increments the object's refcount अगर it is a refcounted modeset
 * object. It is a no-op on any other object. References should be dropped again
 * by calling drm_mode_object_put().
 */
व्योम drm_mode_object_get(काष्ठा drm_mode_object *obj)
अणु
	अगर (obj->मुक्त_cb) अणु
		DRM_DEBUG("OBJ ID: %d (%d)\n", obj->id, kref_पढ़ो(&obj->refcount));
		kref_get(&obj->refcount);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(drm_mode_object_get);

/**
 * drm_object_attach_property - attach a property to a modeset object
 * @obj: drm modeset object
 * @property: property to attach
 * @init_val: initial value of the property
 *
 * This attaches the given property to the modeset object with the given initial
 * value. Currently this function cannot fail since the properties are stored in
 * a अटलally sized array.
 *
 * Note that all properties must be attached beक्रमe the object itself is
 * रेजिस्टरed and accessible from userspace.
 */
व्योम drm_object_attach_property(काष्ठा drm_mode_object *obj,
				काष्ठा drm_property *property,
				uपूर्णांक64_t init_val)
अणु
	पूर्णांक count = obj->properties->count;
	काष्ठा drm_device *dev = property->dev;


	अगर (obj->type == DRM_MODE_OBJECT_CONNECTOR) अणु
		काष्ठा drm_connector *connector = obj_to_connector(obj);

		WARN_ON(!dev->driver->load &&
			connector->registration_state == DRM_CONNECTOR_REGISTERED);
	पूर्ण अन्यथा अणु
		WARN_ON(!dev->driver->load && dev->रेजिस्टरed);
	पूर्ण

	अगर (count == DRM_OBJECT_MAX_PROPERTY) अणु
		WARN(1, "Failed to attach object property (type: 0x%x). Please "
			"increase DRM_OBJECT_MAX_PROPERTY by 1 for each time "
			"you see this message on the same object type.\n",
			obj->type);
		वापस;
	पूर्ण

	obj->properties->properties[count] = property;
	obj->properties->values[count] = init_val;
	obj->properties->count++;
पूर्ण
EXPORT_SYMBOL(drm_object_attach_property);

/**
 * drm_object_property_set_value - set the value of a property
 * @obj: drm mode object to set property value क्रम
 * @property: property to set
 * @val: value the property should be set to
 *
 * This function sets a given property on a given object. This function only
 * changes the software state of the property, it करोes not call पूर्णांकo the
 * driver's ->set_property callback.
 *
 * Note that atomic drivers should not have any need to call this, the core will
 * ensure consistency of values reported back to userspace through the
 * appropriate ->atomic_get_property callback. Only legacy drivers should call
 * this function to update the tracked value (after clamping and other
 * restrictions have been applied).
 *
 * Returns:
 * Zero on success, error code on failure.
 */
पूर्णांक drm_object_property_set_value(काष्ठा drm_mode_object *obj,
				  काष्ठा drm_property *property, uपूर्णांक64_t val)
अणु
	पूर्णांक i;

	WARN_ON(drm_drv_uses_atomic_modeset(property->dev) &&
		!(property->flags & DRM_MODE_PROP_IMMUTABLE));

	क्रम (i = 0; i < obj->properties->count; i++) अणु
		अगर (obj->properties->properties[i] == property) अणु
			obj->properties->values[i] = val;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL(drm_object_property_set_value);

अटल पूर्णांक __drm_object_property_get_value(काष्ठा drm_mode_object *obj,
					   काष्ठा drm_property *property,
					   uपूर्णांक64_t *val)
अणु
	पूर्णांक i;

	/* पढ़ो-only properties bypass atomic mechanism and still store
	 * their value in obj->properties->values[].. mostly to aव्योम
	 * having to deal w/ EDID and similar props in atomic paths:
	 */
	अगर (drm_drv_uses_atomic_modeset(property->dev) &&
			!(property->flags & DRM_MODE_PROP_IMMUTABLE))
		वापस drm_atomic_get_property(obj, property, val);

	क्रम (i = 0; i < obj->properties->count; i++) अणु
		अगर (obj->properties->properties[i] == property) अणु
			*val = obj->properties->values[i];
			वापस 0;
		पूर्ण

	पूर्ण

	वापस -EINVAL;
पूर्ण

/**
 * drm_object_property_get_value - retrieve the value of a property
 * @obj: drm mode object to get property value from
 * @property: property to retrieve
 * @val: storage क्रम the property value
 *
 * This function retrieves the softare state of the given property क्रम the given
 * property. Since there is no driver callback to retrieve the current property
 * value this might be out of sync with the hardware, depending upon the driver
 * and property.
 *
 * Atomic drivers should never call this function directly, the core will पढ़ो
 * out property values through the various ->atomic_get_property callbacks.
 *
 * Returns:
 * Zero on success, error code on failure.
 */
पूर्णांक drm_object_property_get_value(काष्ठा drm_mode_object *obj,
				  काष्ठा drm_property *property, uपूर्णांक64_t *val)
अणु
	WARN_ON(drm_drv_uses_atomic_modeset(property->dev));

	वापस __drm_object_property_get_value(obj, property, val);
पूर्ण
EXPORT_SYMBOL(drm_object_property_get_value);

/* helper क्रम अ_लोonnector and getproperties ioctls */
पूर्णांक drm_mode_object_get_properties(काष्ठा drm_mode_object *obj, bool atomic,
				   uपूर्णांक32_t __user *prop_ptr,
				   uपूर्णांक64_t __user *prop_values,
				   uपूर्णांक32_t *arg_count_props)
अणु
	पूर्णांक i, ret, count;

	क्रम (i = 0, count = 0; i < obj->properties->count; i++) अणु
		काष्ठा drm_property *prop = obj->properties->properties[i];
		uपूर्णांक64_t val;

		अगर ((prop->flags & DRM_MODE_PROP_ATOMIC) && !atomic)
			जारी;

		अगर (*arg_count_props > count) अणु
			ret = __drm_object_property_get_value(obj, prop, &val);
			अगर (ret)
				वापस ret;

			अगर (put_user(prop->base.id, prop_ptr + count))
				वापस -EFAULT;

			अगर (put_user(val, prop_values + count))
				वापस -EFAULT;
		पूर्ण

		count++;
	पूर्ण
	*arg_count_props = count;

	वापस 0;
पूर्ण

/**
 * drm_mode_obj_get_properties_ioctl - get the current value of a object's property
 * @dev: DRM device
 * @data: ioctl data
 * @file_priv: DRM file info
 *
 * This function retrieves the current value क्रम an object's property. Compared
 * to the connector specअगरic ioctl this one is extended to also work on crtc and
 * plane objects.
 *
 * Called by the user via ioctl.
 *
 * Returns:
 * Zero on success, negative त्रुटि_सं on failure.
 */
पूर्णांक drm_mode_obj_get_properties_ioctl(काष्ठा drm_device *dev, व्योम *data,
				      काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_mode_obj_get_properties *arg = data;
	काष्ठा drm_mode_object *obj;
	काष्ठा drm_modeset_acquire_ctx ctx;
	पूर्णांक ret = 0;

	अगर (!drm_core_check_feature(dev, DRIVER_MODESET))
		वापस -EOPNOTSUPP;

	DRM_MODESET_LOCK_ALL_BEGIN(dev, ctx, 0, ret);

	obj = drm_mode_object_find(dev, file_priv, arg->obj_id, arg->obj_type);
	अगर (!obj) अणु
		ret = -ENOENT;
		जाओ out;
	पूर्ण
	अगर (!obj->properties) अणु
		ret = -EINVAL;
		जाओ out_unref;
	पूर्ण

	ret = drm_mode_object_get_properties(obj, file_priv->atomic,
			(uपूर्णांक32_t __user *)(अचिन्हित दीर्घ)(arg->props_ptr),
			(uपूर्णांक64_t __user *)(अचिन्हित दीर्घ)(arg->prop_values_ptr),
			&arg->count_props);

out_unref:
	drm_mode_object_put(obj);
out:
	DRM_MODESET_LOCK_ALL_END(dev, ctx, ret);
	वापस ret;
पूर्ण

काष्ठा drm_property *drm_mode_obj_find_prop_id(काष्ठा drm_mode_object *obj,
					       uपूर्णांक32_t prop_id)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < obj->properties->count; i++)
		अगर (obj->properties->properties[i]->base.id == prop_id)
			वापस obj->properties->properties[i];

	वापस शून्य;
पूर्ण

अटल पूर्णांक set_property_legacy(काष्ठा drm_mode_object *obj,
			       काष्ठा drm_property *prop,
			       uपूर्णांक64_t prop_value)
अणु
	काष्ठा drm_device *dev = prop->dev;
	काष्ठा drm_mode_object *ref;
	काष्ठा drm_modeset_acquire_ctx ctx;
	पूर्णांक ret = -EINVAL;

	अगर (!drm_property_change_valid_get(prop, prop_value, &ref))
		वापस -EINVAL;

	DRM_MODESET_LOCK_ALL_BEGIN(dev, ctx, 0, ret);
	चयन (obj->type) अणु
	हाल DRM_MODE_OBJECT_CONNECTOR:
		ret = drm_connector_set_obj_prop(obj, prop, prop_value);
		अवरोध;
	हाल DRM_MODE_OBJECT_CRTC:
		ret = drm_mode_crtc_set_obj_prop(obj, prop, prop_value);
		अवरोध;
	हाल DRM_MODE_OBJECT_PLANE:
		ret = drm_mode_plane_set_obj_prop(obj_to_plane(obj),
						  prop, prop_value);
		अवरोध;
	पूर्ण
	drm_property_change_valid_put(prop, ref);
	DRM_MODESET_LOCK_ALL_END(dev, ctx, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक set_property_atomic(काष्ठा drm_mode_object *obj,
			       काष्ठा drm_file *file_priv,
			       काष्ठा drm_property *prop,
			       uपूर्णांक64_t prop_value)
अणु
	काष्ठा drm_device *dev = prop->dev;
	काष्ठा drm_atomic_state *state;
	काष्ठा drm_modeset_acquire_ctx ctx;
	पूर्णांक ret;

	state = drm_atomic_state_alloc(dev);
	अगर (!state)
		वापस -ENOMEM;

	drm_modeset_acquire_init(&ctx, 0);
	state->acquire_ctx = &ctx;

retry:
	अगर (prop == state->dev->mode_config.dpms_property) अणु
		अगर (obj->type != DRM_MODE_OBJECT_CONNECTOR) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		ret = drm_atomic_connector_commit_dpms(state,
						       obj_to_connector(obj),
						       prop_value);
	पूर्ण अन्यथा अणु
		ret = drm_atomic_set_property(state, file_priv, obj, prop, prop_value);
		अगर (ret)
			जाओ out;
		ret = drm_atomic_commit(state);
	पूर्ण
out:
	अगर (ret == -EDEADLK) अणु
		drm_atomic_state_clear(state);
		drm_modeset_backoff(&ctx);
		जाओ retry;
	पूर्ण

	drm_atomic_state_put(state);

	drm_modeset_drop_locks(&ctx);
	drm_modeset_acquire_fini(&ctx);

	वापस ret;
पूर्ण

पूर्णांक drm_mode_obj_set_property_ioctl(काष्ठा drm_device *dev, व्योम *data,
				    काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_mode_obj_set_property *arg = data;
	काष्ठा drm_mode_object *arg_obj;
	काष्ठा drm_property *property;
	पूर्णांक ret = -EINVAL;

	अगर (!drm_core_check_feature(dev, DRIVER_MODESET))
		वापस -EOPNOTSUPP;

	arg_obj = drm_mode_object_find(dev, file_priv, arg->obj_id, arg->obj_type);
	अगर (!arg_obj)
		वापस -ENOENT;

	अगर (!arg_obj->properties)
		जाओ out_unref;

	property = drm_mode_obj_find_prop_id(arg_obj, arg->prop_id);
	अगर (!property)
		जाओ out_unref;

	अगर (drm_drv_uses_atomic_modeset(property->dev))
		ret = set_property_atomic(arg_obj, file_priv, property, arg->value);
	अन्यथा
		ret = set_property_legacy(arg_obj, property, arg->value);

out_unref:
	drm_mode_object_put(arg_obj);
	वापस ret;
पूर्ण
