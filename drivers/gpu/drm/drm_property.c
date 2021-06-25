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

#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_framebuffer.h>
#समावेश <drm/drm_property.h>

#समावेश "drm_crtc_internal.h"

/**
 * DOC: overview
 *
 * Properties as represented by &drm_property are used to extend the modeset
 * पूर्णांकerface exposed to userspace. For the atomic modeset IOCTL properties are
 * even the only way to transport metadata about the desired new modeset
 * configuration from userspace to the kernel. Properties have a well-defined
 * value range, which is enक्रमced by the drm core. See the करोcumentation of the
 * flags member of &काष्ठा drm_property क्रम an overview of the dअगरferent
 * property types and ranges.
 *
 * Properties करोn't store the current value directly, but need to be
 * instantiated by attaching them to a &drm_mode_object with
 * drm_object_attach_property().
 *
 * Property values are only 64bit. To support bigger piles of data (like gamma
 * tables, color correction matrices or large काष्ठाures) a property can instead
 * poपूर्णांक at a &drm_property_blob with that additional data.
 *
 * Properties are defined by their symbolic name, userspace must keep a
 * per-object mapping from those names to the property ID used in the atomic
 * IOCTL and in the get/set property IOCTL.
 */

अटल bool drm_property_flags_valid(u32 flags)
अणु
	u32 legacy_type = flags & DRM_MODE_PROP_LEGACY_TYPE;
	u32 ext_type = flags & DRM_MODE_PROP_EXTENDED_TYPE;

	/* Reject undefined/deprecated flags */
	अगर (flags & ~(DRM_MODE_PROP_LEGACY_TYPE |
		      DRM_MODE_PROP_EXTENDED_TYPE |
		      DRM_MODE_PROP_IMMUTABLE |
		      DRM_MODE_PROP_ATOMIC))
		वापस false;

	/* We want either a legacy type or an extended type, but not both */
	अगर (!legacy_type == !ext_type)
		वापस false;

	/* Only one legacy type at a समय please */
	अगर (legacy_type && !is_घातer_of_2(legacy_type))
		वापस false;

	वापस true;
पूर्ण

/**
 * drm_property_create - create a new property type
 * @dev: drm device
 * @flags: flags specअगरying the property type
 * @name: name of the property
 * @num_values: number of pre-defined values
 *
 * This creates a new generic drm property which can then be attached to a drm
 * object with drm_object_attach_property(). The वापसed property object must
 * be मुक्तd with drm_property_destroy(), which is करोne स्वतःmatically when
 * calling drm_mode_config_cleanup().
 *
 * Returns:
 * A poपूर्णांकer to the newly created property on success, शून्य on failure.
 */
काष्ठा drm_property *drm_property_create(काष्ठा drm_device *dev,
					 u32 flags, स्थिर अक्षर *name,
					 पूर्णांक num_values)
अणु
	काष्ठा drm_property *property = शून्य;
	पूर्णांक ret;

	अगर (WARN_ON(!drm_property_flags_valid(flags)))
		वापस शून्य;

	अगर (WARN_ON(म_माप(name) >= DRM_PROP_NAME_LEN))
		वापस शून्य;

	property = kzalloc(माप(काष्ठा drm_property), GFP_KERNEL);
	अगर (!property)
		वापस शून्य;

	property->dev = dev;

	अगर (num_values) अणु
		property->values = kसुस्मृति(num_values, माप(uपूर्णांक64_t),
					   GFP_KERNEL);
		अगर (!property->values)
			जाओ fail;
	पूर्ण

	ret = drm_mode_object_add(dev, &property->base, DRM_MODE_OBJECT_PROPERTY);
	अगर (ret)
		जाओ fail;

	property->flags = flags;
	property->num_values = num_values;
	INIT_LIST_HEAD(&property->क्रमागत_list);

	म_नकलन(property->name, name, DRM_PROP_NAME_LEN);
	property->name[DRM_PROP_NAME_LEN-1] = '\0';

	list_add_tail(&property->head, &dev->mode_config.property_list);

	वापस property;
fail:
	kमुक्त(property->values);
	kमुक्त(property);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(drm_property_create);

/**
 * drm_property_create_क्रमागत - create a new क्रमागतeration property type
 * @dev: drm device
 * @flags: flags specअगरying the property type
 * @name: name of the property
 * @props: क्रमागतeration lists with property values
 * @num_values: number of pre-defined values
 *
 * This creates a new generic drm property which can then be attached to a drm
 * object with drm_object_attach_property(). The वापसed property object must
 * be मुक्तd with drm_property_destroy(), which is करोne स्वतःmatically when
 * calling drm_mode_config_cleanup().
 *
 * Userspace is only allowed to set one of the predefined values क्रम क्रमागतeration
 * properties.
 *
 * Returns:
 * A poपूर्णांकer to the newly created property on success, शून्य on failure.
 */
काष्ठा drm_property *drm_property_create_क्रमागत(काष्ठा drm_device *dev,
					      u32 flags, स्थिर अक्षर *name,
					      स्थिर काष्ठा drm_prop_क्रमागत_list *props,
					      पूर्णांक num_values)
अणु
	काष्ठा drm_property *property;
	पूर्णांक i, ret;

	flags |= DRM_MODE_PROP_ENUM;

	property = drm_property_create(dev, flags, name, num_values);
	अगर (!property)
		वापस शून्य;

	क्रम (i = 0; i < num_values; i++) अणु
		ret = drm_property_add_क्रमागत(property,
					    props[i].type,
					    props[i].name);
		अगर (ret) अणु
			drm_property_destroy(dev, property);
			वापस शून्य;
		पूर्ण
	पूर्ण

	वापस property;
पूर्ण
EXPORT_SYMBOL(drm_property_create_क्रमागत);

/**
 * drm_property_create_biपंचांगask - create a new biपंचांगask property type
 * @dev: drm device
 * @flags: flags specअगरying the property type
 * @name: name of the property
 * @props: क्रमागतeration lists with property bitflags
 * @num_props: size of the @props array
 * @supported_bits: biपंचांगask of all supported क्रमागतeration values
 *
 * This creates a new biपंचांगask drm property which can then be attached to a drm
 * object with drm_object_attach_property(). The वापसed property object must
 * be मुक्तd with drm_property_destroy(), which is करोne स्वतःmatically when
 * calling drm_mode_config_cleanup().
 *
 * Compared to plain क्रमागतeration properties userspace is allowed to set any
 * or'ed together combination of the predefined property bitflag values
 *
 * Returns:
 * A poपूर्णांकer to the newly created property on success, शून्य on failure.
 */
काष्ठा drm_property *drm_property_create_biपंचांगask(काष्ठा drm_device *dev,
						 u32 flags, स्थिर अक्षर *name,
						 स्थिर काष्ठा drm_prop_क्रमागत_list *props,
						 पूर्णांक num_props,
						 uपूर्णांक64_t supported_bits)
अणु
	काष्ठा drm_property *property;
	पूर्णांक i, ret;
	पूर्णांक num_values = hweight64(supported_bits);

	flags |= DRM_MODE_PROP_BITMASK;

	property = drm_property_create(dev, flags, name, num_values);
	अगर (!property)
		वापस शून्य;
	क्रम (i = 0; i < num_props; i++) अणु
		अगर (!(supported_bits & (1ULL << props[i].type)))
			जारी;

		ret = drm_property_add_क्रमागत(property,
					    props[i].type,
					    props[i].name);
		अगर (ret) अणु
			drm_property_destroy(dev, property);
			वापस शून्य;
		पूर्ण
	पूर्ण

	वापस property;
पूर्ण
EXPORT_SYMBOL(drm_property_create_biपंचांगask);

अटल काष्ठा drm_property *property_create_range(काष्ठा drm_device *dev,
						  u32 flags, स्थिर अक्षर *name,
						  uपूर्णांक64_t min, uपूर्णांक64_t max)
अणु
	काष्ठा drm_property *property;

	property = drm_property_create(dev, flags, name, 2);
	अगर (!property)
		वापस शून्य;

	property->values[0] = min;
	property->values[1] = max;

	वापस property;
पूर्ण

/**
 * drm_property_create_range - create a new अचिन्हित ranged property type
 * @dev: drm device
 * @flags: flags specअगरying the property type
 * @name: name of the property
 * @min: minimum value of the property
 * @max: maximum value of the property
 *
 * This creates a new generic drm property which can then be attached to a drm
 * object with drm_object_attach_property(). The वापसed property object must
 * be मुक्तd with drm_property_destroy(), which is करोne स्वतःmatically when
 * calling drm_mode_config_cleanup().
 *
 * Userspace is allowed to set any अचिन्हित पूर्णांकeger value in the (min, max)
 * range inclusive.
 *
 * Returns:
 * A poपूर्णांकer to the newly created property on success, शून्य on failure.
 */
काष्ठा drm_property *drm_property_create_range(काष्ठा drm_device *dev,
					       u32 flags, स्थिर अक्षर *name,
					       uपूर्णांक64_t min, uपूर्णांक64_t max)
अणु
	वापस property_create_range(dev, DRM_MODE_PROP_RANGE | flags,
			name, min, max);
पूर्ण
EXPORT_SYMBOL(drm_property_create_range);

/**
 * drm_property_create_चिन्हित_range - create a new चिन्हित ranged property type
 * @dev: drm device
 * @flags: flags specअगरying the property type
 * @name: name of the property
 * @min: minimum value of the property
 * @max: maximum value of the property
 *
 * This creates a new generic drm property which can then be attached to a drm
 * object with drm_object_attach_property(). The वापसed property object must
 * be मुक्तd with drm_property_destroy(), which is करोne स्वतःmatically when
 * calling drm_mode_config_cleanup().
 *
 * Userspace is allowed to set any चिन्हित पूर्णांकeger value in the (min, max)
 * range inclusive.
 *
 * Returns:
 * A poपूर्णांकer to the newly created property on success, शून्य on failure.
 */
काष्ठा drm_property *drm_property_create_चिन्हित_range(काष्ठा drm_device *dev,
						      u32 flags, स्थिर अक्षर *name,
						      पूर्णांक64_t min, पूर्णांक64_t max)
अणु
	वापस property_create_range(dev, DRM_MODE_PROP_SIGNED_RANGE | flags,
			name, I642U64(min), I642U64(max));
पूर्ण
EXPORT_SYMBOL(drm_property_create_चिन्हित_range);

/**
 * drm_property_create_object - create a new object property type
 * @dev: drm device
 * @flags: flags specअगरying the property type
 * @name: name of the property
 * @type: object type from DRM_MODE_OBJECT_* defines
 *
 * This creates a new generic drm property which can then be attached to a drm
 * object with drm_object_attach_property(). The वापसed property object must
 * be मुक्तd with drm_property_destroy(), which is करोne स्वतःmatically when
 * calling drm_mode_config_cleanup().
 *
 * Userspace is only allowed to set this to any property value of the given
 * @type. Only useful क्रम atomic properties, which is enक्रमced.
 *
 * Returns:
 * A poपूर्णांकer to the newly created property on success, शून्य on failure.
 */
काष्ठा drm_property *drm_property_create_object(काष्ठा drm_device *dev,
						u32 flags, स्थिर अक्षर *name,
						uपूर्णांक32_t type)
अणु
	काष्ठा drm_property *property;

	flags |= DRM_MODE_PROP_OBJECT;

	अगर (WARN_ON(!(flags & DRM_MODE_PROP_ATOMIC)))
		वापस शून्य;

	property = drm_property_create(dev, flags, name, 1);
	अगर (!property)
		वापस शून्य;

	property->values[0] = type;

	वापस property;
पूर्ण
EXPORT_SYMBOL(drm_property_create_object);

/**
 * drm_property_create_bool - create a new boolean property type
 * @dev: drm device
 * @flags: flags specअगरying the property type
 * @name: name of the property
 *
 * This creates a new generic drm property which can then be attached to a drm
 * object with drm_object_attach_property(). The वापसed property object must
 * be मुक्तd with drm_property_destroy(), which is करोne स्वतःmatically when
 * calling drm_mode_config_cleanup().
 *
 * This is implemented as a ranged property with only अणु0, 1पूर्ण as valid values.
 *
 * Returns:
 * A poपूर्णांकer to the newly created property on success, शून्य on failure.
 */
काष्ठा drm_property *drm_property_create_bool(काष्ठा drm_device *dev,
					      u32 flags, स्थिर अक्षर *name)
अणु
	वापस drm_property_create_range(dev, flags, name, 0, 1);
पूर्ण
EXPORT_SYMBOL(drm_property_create_bool);

/**
 * drm_property_add_क्रमागत - add a possible value to an क्रमागतeration property
 * @property: क्रमागतeration property to change
 * @value: value of the new क्रमागतeration
 * @name: symbolic name of the new क्रमागतeration
 *
 * This functions adds क्रमागतerations to a property.
 *
 * It's use is deprecated, drivers should use one of the more specअगरic helpers
 * to directly create the property with all क्रमागतerations alपढ़ोy attached.
 *
 * Returns:
 * Zero on success, error code on failure.
 */
पूर्णांक drm_property_add_क्रमागत(काष्ठा drm_property *property,
			  uपूर्णांक64_t value, स्थिर अक्षर *name)
अणु
	काष्ठा drm_property_क्रमागत *prop_क्रमागत;
	पूर्णांक index = 0;

	अगर (WARN_ON(म_माप(name) >= DRM_PROP_NAME_LEN))
		वापस -EINVAL;

	अगर (WARN_ON(!drm_property_type_is(property, DRM_MODE_PROP_ENUM) &&
		    !drm_property_type_is(property, DRM_MODE_PROP_BITMASK)))
		वापस -EINVAL;

	/*
	 * Biपंचांगask क्रमागत properties have the additional स्थिरraपूर्णांक of values
	 * from 0 to 63
	 */
	अगर (WARN_ON(drm_property_type_is(property, DRM_MODE_PROP_BITMASK) &&
		    value > 63))
		वापस -EINVAL;

	list_क्रम_each_entry(prop_क्रमागत, &property->क्रमागत_list, head) अणु
		अगर (WARN_ON(prop_क्रमागत->value == value))
			वापस -EINVAL;
		index++;
	पूर्ण

	अगर (WARN_ON(index >= property->num_values))
		वापस -EINVAL;

	prop_क्रमागत = kzalloc(माप(काष्ठा drm_property_क्रमागत), GFP_KERNEL);
	अगर (!prop_क्रमागत)
		वापस -ENOMEM;

	म_नकलन(prop_क्रमागत->name, name, DRM_PROP_NAME_LEN);
	prop_क्रमागत->name[DRM_PROP_NAME_LEN-1] = '\0';
	prop_क्रमागत->value = value;

	property->values[index] = value;
	list_add_tail(&prop_क्रमागत->head, &property->क्रमागत_list);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_property_add_क्रमागत);

/**
 * drm_property_destroy - destroy a drm property
 * @dev: drm device
 * @property: property to destry
 *
 * This function मुक्तs a property including any attached resources like
 * क्रमागतeration values.
 */
व्योम drm_property_destroy(काष्ठा drm_device *dev, काष्ठा drm_property *property)
अणु
	काष्ठा drm_property_क्रमागत *prop_क्रमागत, *pt;

	list_क्रम_each_entry_safe(prop_क्रमागत, pt, &property->क्रमागत_list, head) अणु
		list_del(&prop_क्रमागत->head);
		kमुक्त(prop_क्रमागत);
	पूर्ण

	अगर (property->num_values)
		kमुक्त(property->values);
	drm_mode_object_unरेजिस्टर(dev, &property->base);
	list_del(&property->head);
	kमुक्त(property);
पूर्ण
EXPORT_SYMBOL(drm_property_destroy);

पूर्णांक drm_mode_getproperty_ioctl(काष्ठा drm_device *dev,
			       व्योम *data, काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_mode_get_property *out_resp = data;
	काष्ठा drm_property *property;
	पूर्णांक क्रमागत_count = 0;
	पूर्णांक value_count = 0;
	पूर्णांक i, copied;
	काष्ठा drm_property_क्रमागत *prop_क्रमागत;
	काष्ठा drm_mode_property_क्रमागत __user *क्रमागत_ptr;
	uपूर्णांक64_t __user *values_ptr;

	अगर (!drm_core_check_feature(dev, DRIVER_MODESET))
		वापस -EOPNOTSUPP;

	property = drm_property_find(dev, file_priv, out_resp->prop_id);
	अगर (!property)
		वापस -ENOENT;

	म_नकलन(out_resp->name, property->name, DRM_PROP_NAME_LEN);
	out_resp->name[DRM_PROP_NAME_LEN-1] = 0;
	out_resp->flags = property->flags;

	value_count = property->num_values;
	values_ptr = u64_to_user_ptr(out_resp->values_ptr);

	क्रम (i = 0; i < value_count; i++) अणु
		अगर (i < out_resp->count_values &&
		    put_user(property->values[i], values_ptr + i)) अणु
			वापस -EFAULT;
		पूर्ण
	पूर्ण
	out_resp->count_values = value_count;

	copied = 0;
	क्रमागत_ptr = u64_to_user_ptr(out_resp->क्रमागत_blob_ptr);

	अगर (drm_property_type_is(property, DRM_MODE_PROP_ENUM) ||
	    drm_property_type_is(property, DRM_MODE_PROP_BITMASK)) अणु
		list_क्रम_each_entry(prop_क्रमागत, &property->क्रमागत_list, head) अणु
			क्रमागत_count++;
			अगर (out_resp->count_क्रमागत_blobs < क्रमागत_count)
				जारी;

			अगर (copy_to_user(&क्रमागत_ptr[copied].value,
					 &prop_क्रमागत->value, माप(uपूर्णांक64_t)))
				वापस -EFAULT;

			अगर (copy_to_user(&क्रमागत_ptr[copied].name,
					 &prop_क्रमागत->name, DRM_PROP_NAME_LEN))
				वापस -EFAULT;
			copied++;
		पूर्ण
		out_resp->count_क्रमागत_blobs = क्रमागत_count;
	पूर्ण

	/*
	 * NOTE: The idea seems to have been to use this to पढ़ो all the blob
	 * property values. But nothing ever added them to the corresponding
	 * list, userspace always used the special-purpose get_blob ioctl to
	 * पढ़ो the value क्रम a blob property. It also करोesn't make a lot of
	 * sense to वापस values here when everything अन्यथा is just metadata क्रम
	 * the property itself.
	 */
	अगर (drm_property_type_is(property, DRM_MODE_PROP_BLOB))
		out_resp->count_क्रमागत_blobs = 0;

	वापस 0;
पूर्ण

अटल व्योम drm_property_मुक्त_blob(काष्ठा kref *kref)
अणु
	काष्ठा drm_property_blob *blob =
		container_of(kref, काष्ठा drm_property_blob, base.refcount);

	mutex_lock(&blob->dev->mode_config.blob_lock);
	list_del(&blob->head_global);
	mutex_unlock(&blob->dev->mode_config.blob_lock);

	drm_mode_object_unरेजिस्टर(blob->dev, &blob->base);

	kvमुक्त(blob);
पूर्ण

/**
 * drm_property_create_blob - Create new blob property
 * @dev: DRM device to create property क्रम
 * @length: Length to allocate क्रम blob data
 * @data: If specअगरied, copies data पूर्णांकo blob
 *
 * Creates a new blob property क्रम a specअगरied DRM device, optionally
 * copying data. Note that blob properties are meant to be invariant, hence the
 * data must be filled out beक्रमe the blob is used as the value of any property.
 *
 * Returns:
 * New blob property with a single reference on success, or an ERR_PTR
 * value on failure.
 */
काष्ठा drm_property_blob *
drm_property_create_blob(काष्ठा drm_device *dev, माप_प्रकार length,
			 स्थिर व्योम *data)
अणु
	काष्ठा drm_property_blob *blob;
	पूर्णांक ret;

	अगर (!length || length > पूर्णांक_उच्च - माप(काष्ठा drm_property_blob))
		वापस ERR_PTR(-EINVAL);

	blob = kvzalloc(माप(काष्ठा drm_property_blob)+length, GFP_KERNEL);
	अगर (!blob)
		वापस ERR_PTR(-ENOMEM);

	/* This must be explicitly initialised, so we can safely call list_del
	 * on it in the removal handler, even अगर it isn't in a file list. */
	INIT_LIST_HEAD(&blob->head_file);
	blob->data = (व्योम *)blob + माप(*blob);
	blob->length = length;
	blob->dev = dev;

	अगर (data)
		स_नकल(blob->data, data, length);

	ret = __drm_mode_object_add(dev, &blob->base, DRM_MODE_OBJECT_BLOB,
				    true, drm_property_मुक्त_blob);
	अगर (ret) अणु
		kvमुक्त(blob);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	mutex_lock(&dev->mode_config.blob_lock);
	list_add_tail(&blob->head_global,
	              &dev->mode_config.property_blob_list);
	mutex_unlock(&dev->mode_config.blob_lock);

	वापस blob;
पूर्ण
EXPORT_SYMBOL(drm_property_create_blob);

/**
 * drm_property_blob_put - release a blob property reference
 * @blob: DRM blob property
 *
 * Releases a reference to a blob property. May मुक्त the object.
 */
व्योम drm_property_blob_put(काष्ठा drm_property_blob *blob)
अणु
	अगर (!blob)
		वापस;

	drm_mode_object_put(&blob->base);
पूर्ण
EXPORT_SYMBOL(drm_property_blob_put);

व्योम drm_property_destroy_user_blobs(काष्ठा drm_device *dev,
				     काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_property_blob *blob, *bt;

	/*
	 * When the file माला_लो released that means no one अन्यथा can access the
	 * blob list any more, so no need to grab dev->blob_lock.
	 */
	list_क्रम_each_entry_safe(blob, bt, &file_priv->blobs, head_file) अणु
		list_del_init(&blob->head_file);
		drm_property_blob_put(blob);
	पूर्ण
पूर्ण

/**
 * drm_property_blob_get - acquire blob property reference
 * @blob: DRM blob property
 *
 * Acquires a reference to an existing blob property. Returns @blob, which
 * allows this to be used as a लघुhand in assignments.
 */
काष्ठा drm_property_blob *drm_property_blob_get(काष्ठा drm_property_blob *blob)
अणु
	drm_mode_object_get(&blob->base);
	वापस blob;
पूर्ण
EXPORT_SYMBOL(drm_property_blob_get);

/**
 * drm_property_lookup_blob - look up a blob property and take a reference
 * @dev: drm device
 * @id: id of the blob property
 *
 * If successful, this takes an additional reference to the blob property.
 * callers need to make sure to eventually unreferenced the वापसed property
 * again, using drm_property_blob_put().
 *
 * Return:
 * शून्य on failure, poपूर्णांकer to the blob on success.
 */
काष्ठा drm_property_blob *drm_property_lookup_blob(काष्ठा drm_device *dev,
					           uपूर्णांक32_t id)
अणु
	काष्ठा drm_mode_object *obj;
	काष्ठा drm_property_blob *blob = शून्य;

	obj = __drm_mode_object_find(dev, शून्य, id, DRM_MODE_OBJECT_BLOB);
	अगर (obj)
		blob = obj_to_blob(obj);
	वापस blob;
पूर्ण
EXPORT_SYMBOL(drm_property_lookup_blob);

/**
 * drm_property_replace_global_blob - replace existing blob property
 * @dev: drm device
 * @replace: location of blob property poपूर्णांकer to be replaced
 * @length: length of data क्रम new blob, or 0 क्रम no data
 * @data: content क्रम new blob, or शून्य क्रम no data
 * @obj_holds_id: optional object क्रम property holding blob ID
 * @prop_holds_id: optional property holding blob ID
 * @वापस 0 on success or error on failure
 *
 * This function will replace a global property in the blob list, optionally
 * updating a property which holds the ID of that property.
 *
 * If length is 0 or data is शून्य, no new blob will be created, and the holding
 * property, अगर specअगरied, will be set to 0.
 *
 * Access to the replace poपूर्णांकer is assumed to be रक्षित by the caller, e.g.
 * by holding the relevant modesetting object lock क्रम its parent.
 *
 * For example, a drm_connector has a 'PATH' property, which contains the ID
 * of a blob property with the value of the MST path inक्रमmation. Calling this
 * function with replace poपूर्णांकing to the connector's path_blob_ptr, length and
 * data set क्रम the new path inक्रमmation, obj_holds_id set to the connector's
 * base object, and prop_holds_id set to the path property name, will perक्रमm
 * a completely atomic update. The access to path_blob_ptr is रक्षित by the
 * caller holding a lock on the connector.
 */
पूर्णांक drm_property_replace_global_blob(काष्ठा drm_device *dev,
				     काष्ठा drm_property_blob **replace,
				     माप_प्रकार length,
				     स्थिर व्योम *data,
				     काष्ठा drm_mode_object *obj_holds_id,
				     काष्ठा drm_property *prop_holds_id)
अणु
	काष्ठा drm_property_blob *new_blob = शून्य;
	काष्ठा drm_property_blob *old_blob = शून्य;
	पूर्णांक ret;

	WARN_ON(replace == शून्य);

	old_blob = *replace;

	अगर (length && data) अणु
		new_blob = drm_property_create_blob(dev, length, data);
		अगर (IS_ERR(new_blob))
			वापस PTR_ERR(new_blob);
	पूर्ण

	अगर (obj_holds_id) अणु
		ret = drm_object_property_set_value(obj_holds_id,
						    prop_holds_id,
						    new_blob ?
						        new_blob->base.id : 0);
		अगर (ret != 0)
			जाओ err_created;
	पूर्ण

	drm_property_blob_put(old_blob);
	*replace = new_blob;

	वापस 0;

err_created:
	drm_property_blob_put(new_blob);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_property_replace_global_blob);

/**
 * drm_property_replace_blob - replace a blob property
 * @blob: a poपूर्णांकer to the member blob to be replaced
 * @new_blob: the new blob to replace with
 *
 * Return: true अगर the blob was in fact replaced.
 */
bool drm_property_replace_blob(काष्ठा drm_property_blob **blob,
			       काष्ठा drm_property_blob *new_blob)
अणु
	काष्ठा drm_property_blob *old_blob = *blob;

	अगर (old_blob == new_blob)
		वापस false;

	drm_property_blob_put(old_blob);
	अगर (new_blob)
		drm_property_blob_get(new_blob);
	*blob = new_blob;
	वापस true;
पूर्ण
EXPORT_SYMBOL(drm_property_replace_blob);

पूर्णांक drm_mode_getblob_ioctl(काष्ठा drm_device *dev,
			   व्योम *data, काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_mode_get_blob *out_resp = data;
	काष्ठा drm_property_blob *blob;
	पूर्णांक ret = 0;

	अगर (!drm_core_check_feature(dev, DRIVER_MODESET))
		वापस -EOPNOTSUPP;

	blob = drm_property_lookup_blob(dev, out_resp->blob_id);
	अगर (!blob)
		वापस -ENOENT;

	अगर (out_resp->length == blob->length) अणु
		अगर (copy_to_user(u64_to_user_ptr(out_resp->data),
				 blob->data,
				 blob->length)) अणु
			ret = -EFAULT;
			जाओ unref;
		पूर्ण
	पूर्ण
	out_resp->length = blob->length;
unref:
	drm_property_blob_put(blob);

	वापस ret;
पूर्ण

पूर्णांक drm_mode_createblob_ioctl(काष्ठा drm_device *dev,
			      व्योम *data, काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_mode_create_blob *out_resp = data;
	काष्ठा drm_property_blob *blob;
	पूर्णांक ret = 0;

	अगर (!drm_core_check_feature(dev, DRIVER_MODESET))
		वापस -EOPNOTSUPP;

	blob = drm_property_create_blob(dev, out_resp->length, शून्य);
	अगर (IS_ERR(blob))
		वापस PTR_ERR(blob);

	अगर (copy_from_user(blob->data,
			   u64_to_user_ptr(out_resp->data),
			   out_resp->length)) अणु
		ret = -EFAULT;
		जाओ out_blob;
	पूर्ण

	/* Dropping the lock between create_blob and our access here is safe
	 * as only the same file_priv can हटाओ the blob; at this poपूर्णांक, it is
	 * not associated with any file_priv. */
	mutex_lock(&dev->mode_config.blob_lock);
	out_resp->blob_id = blob->base.id;
	list_add_tail(&blob->head_file, &file_priv->blobs);
	mutex_unlock(&dev->mode_config.blob_lock);

	वापस 0;

out_blob:
	drm_property_blob_put(blob);
	वापस ret;
पूर्ण

पूर्णांक drm_mode_destroyblob_ioctl(काष्ठा drm_device *dev,
			       व्योम *data, काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_mode_destroy_blob *out_resp = data;
	काष्ठा drm_property_blob *blob = शून्य, *bt;
	bool found = false;
	पूर्णांक ret = 0;

	अगर (!drm_core_check_feature(dev, DRIVER_MODESET))
		वापस -EOPNOTSUPP;

	blob = drm_property_lookup_blob(dev, out_resp->blob_id);
	अगर (!blob)
		वापस -ENOENT;

	mutex_lock(&dev->mode_config.blob_lock);
	/* Ensure the property was actually created by this user. */
	list_क्रम_each_entry(bt, &file_priv->blobs, head_file) अणु
		अगर (bt == blob) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found) अणु
		ret = -EPERM;
		जाओ err;
	पूर्ण

	/* We must drop head_file here, because we may not be the last
	 * reference on the blob. */
	list_del_init(&blob->head_file);
	mutex_unlock(&dev->mode_config.blob_lock);

	/* One reference from lookup, and one from the filp. */
	drm_property_blob_put(blob);
	drm_property_blob_put(blob);

	वापस 0;

err:
	mutex_unlock(&dev->mode_config.blob_lock);
	drm_property_blob_put(blob);

	वापस ret;
पूर्ण

/* Some properties could refer to dynamic refcnt'd objects, or things that
 * need special locking to handle lअगरeसमय issues (ie. to ensure the prop
 * value करोesn't become invalid part way through the property update due to
 * race).  The value वापसed by reference via 'obj' should be passed back
 * to drm_property_change_valid_put() after the property is set (and the
 * object to which the property is attached has a chance to take its own
 * reference).
 */
bool drm_property_change_valid_get(काष्ठा drm_property *property,
				   uपूर्णांक64_t value, काष्ठा drm_mode_object **ref)
अणु
	पूर्णांक i;

	अगर (property->flags & DRM_MODE_PROP_IMMUTABLE)
		वापस false;

	*ref = शून्य;

	अगर (drm_property_type_is(property, DRM_MODE_PROP_RANGE)) अणु
		अगर (value < property->values[0] || value > property->values[1])
			वापस false;
		वापस true;
	पूर्ण अन्यथा अगर (drm_property_type_is(property, DRM_MODE_PROP_SIGNED_RANGE)) अणु
		पूर्णांक64_t svalue = U642I64(value);

		अगर (svalue < U642I64(property->values[0]) ||
				svalue > U642I64(property->values[1]))
			वापस false;
		वापस true;
	पूर्ण अन्यथा अगर (drm_property_type_is(property, DRM_MODE_PROP_BITMASK)) अणु
		uपूर्णांक64_t valid_mask = 0;

		क्रम (i = 0; i < property->num_values; i++)
			valid_mask |= (1ULL << property->values[i]);
		वापस !(value & ~valid_mask);
	पूर्ण अन्यथा अगर (drm_property_type_is(property, DRM_MODE_PROP_BLOB)) अणु
		काष्ठा drm_property_blob *blob;

		अगर (value == 0)
			वापस true;

		blob = drm_property_lookup_blob(property->dev, value);
		अगर (blob) अणु
			*ref = &blob->base;
			वापस true;
		पूर्ण अन्यथा अणु
			वापस false;
		पूर्ण
	पूर्ण अन्यथा अगर (drm_property_type_is(property, DRM_MODE_PROP_OBJECT)) अणु
		/* a zero value क्रम an object property translates to null: */
		अगर (value == 0)
			वापस true;

		*ref = __drm_mode_object_find(property->dev, शून्य, value,
					      property->values[0]);
		वापस *ref != शून्य;
	पूर्ण

	क्रम (i = 0; i < property->num_values; i++)
		अगर (property->values[i] == value)
			वापस true;
	वापस false;
पूर्ण

व्योम drm_property_change_valid_put(काष्ठा drm_property *property,
		काष्ठा drm_mode_object *ref)
अणु
	अगर (!ref)
		वापस;

	अगर (drm_property_type_is(property, DRM_MODE_PROP_OBJECT)) अणु
		drm_mode_object_put(ref);
	पूर्ण अन्यथा अगर (drm_property_type_is(property, DRM_MODE_PROP_BLOB))
		drm_property_blob_put(obj_to_blob(ref));
पूर्ण
