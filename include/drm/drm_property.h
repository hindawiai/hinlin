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

#अगर_अघोषित __DRM_PROPERTY_H__
#घोषणा __DRM_PROPERTY_H__

#समावेश <linux/list.h>
#समावेश <linux/प्रकार.स>
#समावेश <drm/drm_mode_object.h>

#समावेश <uapi/drm/drm_mode.h>

/**
 * काष्ठा drm_property_क्रमागत - symbolic values क्रम क्रमागतerations
 * @value: numeric property value क्रम this क्रमागत entry
 * @head: list of क्रमागत values, linked to &drm_property.क्रमागत_list
 * @name: symbolic name क्रम the क्रमागत
 *
 * For क्रमागतeration and biपंचांगask properties this काष्ठाure stores the symbolic
 * decoding क्रम each value. This is used क्रम example क्रम the rotation property.
 */
काष्ठा drm_property_क्रमागत अणु
	uपूर्णांक64_t value;
	काष्ठा list_head head;
	अक्षर name[DRM_PROP_NAME_LEN];
पूर्ण;

/**
 * काष्ठा drm_property - modeset object property
 *
 * This काष्ठाure represent a modeset object property. It combines both the name
 * of the property with the set of permissible values. This means that when a
 * driver wants to use a property with the same name on dअगरferent objects, but
 * with dअगरferent value ranges, then it must create property क्रम each one. An
 * example would be rotation of &drm_plane, when e.g. the primary plane cannot
 * be rotated. But अगर both the name and the value range match, then the same
 * property काष्ठाure can be instantiated multiple बार क्रम the same object.
 * Userspace must be able to cope with this and cannot assume that the same
 * symbolic property will have the same modeset object ID on all modeset
 * objects.
 *
 * Properties are created by one of the special functions, as explained in
 * detail in the @flags काष्ठाure member.
 *
 * To actually expose a property it must be attached to each object using
 * drm_object_attach_property(). Currently properties can only be attached to
 * &drm_connector, &drm_crtc and &drm_plane.
 *
 * Properties are also used as the generic metadatatransport क्रम the atomic
 * IOCTL. Everything that was set directly in काष्ठाures in the legacy modeset
 * IOCTLs (like the plane source or destination winकरोws, or e.g. the links to
 * the CRTC) is exposed as a property with the DRM_MODE_PROP_ATOMIC flag set.
 */
काष्ठा drm_property अणु
	/**
	 * @head: per-device list of properties, क्रम cleanup.
	 */
	काष्ठा list_head head;

	/**
	 * @base: base KMS object
	 */
	काष्ठा drm_mode_object base;

	/**
	 * @flags:
	 *
	 * Property flags and type. A property needs to be one of the following
	 * types:
	 *
	 * DRM_MODE_PROP_RANGE
	 *     Range properties report their minimum and maximum admissible अचिन्हित values.
	 *     The KMS core verअगरies that values set by application fit in that
	 *     range. The range is अचिन्हित. Range properties are created using
	 *     drm_property_create_range().
	 *
	 * DRM_MODE_PROP_SIGNED_RANGE
	 *     Range properties report their minimum and maximum admissible अचिन्हित values.
	 *     The KMS core verअगरies that values set by application fit in that
	 *     range. The range is चिन्हित. Range properties are created using
	 *     drm_property_create_चिन्हित_range().
	 *
	 * DRM_MODE_PROP_ENUM
	 *     Enumerated properties take a numerical value that ranges from 0 to
	 *     the number of क्रमागतerated values defined by the property minus one,
	 *     and associate a मुक्त-क्रमmed string name to each value. Applications
	 *     can retrieve the list of defined value-name pairs and use the
	 *     numerical value to get and set property instance values. Enum
	 *     properties are created using drm_property_create_क्रमागत().
	 *
	 * DRM_MODE_PROP_BITMASK
	 *     Biपंचांगask properties are क्रमागतeration properties that additionally
	 *     restrict all क्रमागतerated values to the 0..63 range. Biपंचांगask property
	 *     instance values combine one or more of the क्रमागतerated bits defined
	 *     by the property. Biपंचांगask properties are created using
	 *     drm_property_create_biपंचांगask().
	 *
	 * DRM_MODE_PROP_OBJECT
	 *     Object properties are used to link modeset objects. This is used
	 *     extensively in the atomic support to create the display pipeline,
	 *     by linking &drm_framebuffer to &drm_plane, &drm_plane to
	 *     &drm_crtc and &drm_connector to &drm_crtc. An object property can
	 *     only link to a specअगरic type of &drm_mode_object, this limit is
	 *     enक्रमced by the core. Object properties are created using
	 *     drm_property_create_object().
	 *
	 *     Object properties work like blob properties, but in a more
	 *     general fashion. They are limited to atomic drivers and must have
	 *     the DRM_MODE_PROP_ATOMIC flag set.
	 *
	 * DRM_MODE_PROP_BLOB
	 *     Blob properties store a binary blob without any क्रमmat restriction.
	 *     The binary blobs are created as KMS standalone objects, and blob
	 *     property instance values store the ID of their associated blob
	 *     object. Blob properties are created by calling
	 *     drm_property_create() with DRM_MODE_PROP_BLOB as the type.
	 *
	 *     Actual blob objects to contain blob data are created using
	 *     drm_property_create_blob(), or through the corresponding IOCTL.
	 *
	 *     Besides the built-in limit to only accept blob objects blob
	 *     properties work exactly like object properties. The only reasons
	 *     blob properties exist is backwards compatibility with existing
	 *     userspace.
	 *
	 * In addition a property can have any combination of the below flags:
	 *
	 * DRM_MODE_PROP_ATOMIC
	 *     Set क्रम properties which encode atomic modeset state. Such
	 *     properties are not exposed to legacy userspace.
	 *
	 * DRM_MODE_PROP_IMMUTABLE
	 *     Set क्रम properties whose values cannot be changed by
	 *     userspace. The kernel is allowed to update the value of these
	 *     properties. This is generally used to expose probe state to
	 *     userspace, e.g. the EDID, or the connector path property on DP
	 *     MST sinks. Kernel can update the value of an immutable property
	 *     by calling drm_object_property_set_value().
	 */
	uपूर्णांक32_t flags;

	/**
	 * @name: symbolic name of the properties
	 */
	अक्षर name[DRM_PROP_NAME_LEN];

	/**
	 * @num_values: size of the @values array.
	 */
	uपूर्णांक32_t num_values;

	/**
	 * @values:
	 *
	 * Array with limits and values क्रम the property. The
	 * पूर्णांकerpretation of these limits is dependent upon the type per @flags.
	 */
	uपूर्णांक64_t *values;

	/**
	 * @dev: DRM device
	 */
	काष्ठा drm_device *dev;

	/**
	 * @क्रमागत_list:
	 *
	 * List of &drm_prop_क्रमागत_list काष्ठाures with the symbolic names क्रम
	 * क्रमागत and biपंचांगask values.
	 */
	काष्ठा list_head क्रमागत_list;
पूर्ण;

/**
 * काष्ठा drm_property_blob - Blob data क्रम &drm_property
 * @base: base KMS object
 * @dev: DRM device
 * @head_global: entry on the global blob list in
 * 	&drm_mode_config.property_blob_list.
 * @head_file: entry on the per-file blob list in &drm_file.blobs list.
 * @length: size of the blob in bytes, invariant over the lअगरeसमय of the object
 * @data: actual data, embedded at the end of this काष्ठाure
 *
 * Blobs are used to store bigger values than what fits directly पूर्णांकo the 64
 * bits available क्रम a &drm_property.
 *
 * Blobs are reference counted using drm_property_blob_get() and
 * drm_property_blob_put(). They are created using drm_property_create_blob().
 */
काष्ठा drm_property_blob अणु
	काष्ठा drm_mode_object base;
	काष्ठा drm_device *dev;
	काष्ठा list_head head_global;
	काष्ठा list_head head_file;
	माप_प्रकार length;
	व्योम *data;
पूर्ण;

काष्ठा drm_prop_क्रमागत_list अणु
	पूर्णांक type;
	स्थिर अक्षर *name;
पूर्ण;

#घोषणा obj_to_property(x) container_of(x, काष्ठा drm_property, base)
#घोषणा obj_to_blob(x) container_of(x, काष्ठा drm_property_blob, base)

/**
 * drm_property_type_is - check the type of a property
 * @property: property to check
 * @type: property type to compare with
 *
 * This is a helper function becauase the uapi encoding of property types is
 * a bit special क्रम historical reasons.
 */
अटल अंतरभूत bool drm_property_type_is(काष्ठा drm_property *property,
					uपूर्णांक32_t type)
अणु
	/* instanceof क्रम props.. handles extended type vs original types: */
	अगर (property->flags & DRM_MODE_PROP_EXTENDED_TYPE)
		वापस (property->flags & DRM_MODE_PROP_EXTENDED_TYPE) == type;
	वापस property->flags & type;
पूर्ण

काष्ठा drm_property *drm_property_create(काष्ठा drm_device *dev,
					 u32 flags, स्थिर अक्षर *name,
					 पूर्णांक num_values);
काष्ठा drm_property *drm_property_create_क्रमागत(काष्ठा drm_device *dev,
					      u32 flags, स्थिर अक्षर *name,
					      स्थिर काष्ठा drm_prop_क्रमागत_list *props,
					      पूर्णांक num_values);
काष्ठा drm_property *drm_property_create_biपंचांगask(काष्ठा drm_device *dev,
						 u32 flags, स्थिर अक्षर *name,
						 स्थिर काष्ठा drm_prop_क्रमागत_list *props,
						 पूर्णांक num_props,
						 uपूर्णांक64_t supported_bits);
काष्ठा drm_property *drm_property_create_range(काष्ठा drm_device *dev,
					       u32 flags, स्थिर अक्षर *name,
					       uपूर्णांक64_t min, uपूर्णांक64_t max);
काष्ठा drm_property *drm_property_create_चिन्हित_range(काष्ठा drm_device *dev,
						      u32 flags, स्थिर अक्षर *name,
						      पूर्णांक64_t min, पूर्णांक64_t max);
काष्ठा drm_property *drm_property_create_object(काष्ठा drm_device *dev,
						u32 flags, स्थिर अक्षर *name,
						uपूर्णांक32_t type);
काष्ठा drm_property *drm_property_create_bool(काष्ठा drm_device *dev,
					      u32 flags, स्थिर अक्षर *name);
पूर्णांक drm_property_add_क्रमागत(काष्ठा drm_property *property,
			  uपूर्णांक64_t value, स्थिर अक्षर *name);
व्योम drm_property_destroy(काष्ठा drm_device *dev, काष्ठा drm_property *property);

काष्ठा drm_property_blob *drm_property_create_blob(काष्ठा drm_device *dev,
						   माप_प्रकार length,
						   स्थिर व्योम *data);
काष्ठा drm_property_blob *drm_property_lookup_blob(काष्ठा drm_device *dev,
						   uपूर्णांक32_t id);
पूर्णांक drm_property_replace_global_blob(काष्ठा drm_device *dev,
				     काष्ठा drm_property_blob **replace,
				     माप_प्रकार length,
				     स्थिर व्योम *data,
				     काष्ठा drm_mode_object *obj_holds_id,
				     काष्ठा drm_property *prop_holds_id);
bool drm_property_replace_blob(काष्ठा drm_property_blob **blob,
			       काष्ठा drm_property_blob *new_blob);
काष्ठा drm_property_blob *drm_property_blob_get(काष्ठा drm_property_blob *blob);
व्योम drm_property_blob_put(काष्ठा drm_property_blob *blob);

/**
 * drm_property_find - find property object
 * @dev: DRM device
 * @file_priv: drm file to check क्रम lease against.
 * @id: property object id
 *
 * This function looks up the property object specअगरied by id and वापसs it.
 */
अटल अंतरभूत काष्ठा drm_property *drm_property_find(काष्ठा drm_device *dev,
						     काष्ठा drm_file *file_priv,
						     uपूर्णांक32_t id)
अणु
	काष्ठा drm_mode_object *mo;
	mo = drm_mode_object_find(dev, file_priv, id, DRM_MODE_OBJECT_PROPERTY);
	वापस mo ? obj_to_property(mo) : शून्य;
पूर्ण

#पूर्ण_अगर
