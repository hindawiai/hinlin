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

#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>

#समावेश <drm/drm_plane.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_framebuffer.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_managed.h>
#समावेश <drm/drm_vblank.h>

#समावेश "drm_crtc_internal.h"

/**
 * DOC: overview
 *
 * A plane represents an image source that can be blended with or overlayed on
 * top of a CRTC during the scanout process. Planes take their input data from a
 * &drm_framebuffer object. The plane itself specअगरies the cropping and scaling
 * of that image, and where it is placed on the visible area of a display
 * pipeline, represented by &drm_crtc. A plane can also have additional
 * properties that specअगरy how the pixels are positioned and blended, like
 * rotation or Z-position. All these properties are stored in &drm_plane_state.
 *
 * To create a plane, a KMS drivers allocates and zeroes an instances of
 * &काष्ठा drm_plane (possibly as part of a larger काष्ठाure) and रेजिस्टरs it
 * with a call to drm_universal_plane_init().
 *
 * Each plane has a type, see क्रमागत drm_plane_type. A plane can be compatible
 * with multiple CRTCs, see &drm_plane.possible_crtcs.
 *
 * Each CRTC must have a unique primary plane userspace can attach to enable
 * the CRTC. In other words, userspace must be able to attach a dअगरferent
 * primary plane to each CRTC at the same समय. Primary planes can still be
 * compatible with multiple CRTCs. There must be exactly as many primary planes
 * as there are CRTCs.
 *
 * Legacy uAPI करोesn't expose the primary and cursor planes directly. DRM core
 * relies on the driver to set the primary and optionally the cursor plane used
 * क्रम legacy IOCTLs. This is करोne by calling drm_crtc_init_with_planes(). All
 * drivers must provide one primary plane per CRTC to aव्योम surprising legacy
 * userspace too much.
 */

/**
 * DOC: standard plane properties
 *
 * DRM planes have a few standardized properties:
 *
 * type:
 *     Immutable property describing the type of the plane.
 *
 *     For user-space which has enabled the &DRM_CLIENT_CAP_ATOMIC capability,
 *     the plane type is just a hपूर्णांक and is mostly superseded by atomic
 *     test-only commits. The type hपूर्णांक can still be used to come up more
 *     easily with a plane configuration accepted by the driver.
 *
 *     The value of this property can be one of the following:
 *
 *     "Primary":
 *         To light up a CRTC, attaching a primary plane is the most likely to
 *         work अगर it covers the whole CRTC and करोesn't have scaling or
 *         cropping set up.
 *
 *         Drivers may support more features क्रम the primary plane, user-space
 *         can find out with test-only atomic commits.
 *
 *         Some primary planes are implicitly used by the kernel in the legacy
 *         IOCTLs &DRM_IOCTL_MODE_SETCRTC and &DRM_IOCTL_MODE_PAGE_FLIP.
 *         Thereक्रमe user-space must not mix explicit usage of any primary
 *         plane (e.g. through an atomic commit) with these legacy IOCTLs.
 *
 *     "Cursor":
 *         To enable this plane, using a framebuffer configured without scaling
 *         or cropping and with the following properties is the most likely to
 *         work:
 *
 *         - If the driver provides the capabilities &DRM_CAP_CURSOR_WIDTH and
 *           &DRM_CAP_CURSOR_HEIGHT, create the framebuffer with this size.
 *           Otherwise, create a framebuffer with the size 64x64.
 *         - If the driver करोesn't support modअगरiers, create a framebuffer with
 *           a linear layout. Otherwise, use the IN_FORMATS plane property.
 *
 *         Drivers may support more features क्रम the cursor plane, user-space
 *         can find out with test-only atomic commits.
 *
 *         Some cursor planes are implicitly used by the kernel in the legacy
 *         IOCTLs &DRM_IOCTL_MODE_CURSOR and &DRM_IOCTL_MODE_CURSOR2.
 *         Thereक्रमe user-space must not mix explicit usage of any cursor
 *         plane (e.g. through an atomic commit) with these legacy IOCTLs.
 *
 *         Some drivers may support cursors even अगर no cursor plane is exposed.
 *         In this हाल, the legacy cursor IOCTLs can be used to configure the
 *         cursor.
 *
 *     "Overlay":
 *         Neither primary nor cursor.
 *
 *         Overlay planes are the only planes exposed when the
 *         &DRM_CLIENT_CAP_UNIVERSAL_PLANES capability is disabled.
 *
 * IN_FORMATS:
 *     Blob property which contains the set of buffer क्रमmat and modअगरier
 *     pairs supported by this plane. The blob is a काष्ठा
 *     drm_क्रमmat_modअगरier_blob. Without this property the plane करोesn't
 *     support buffers with modअगरiers. Userspace cannot change this property.
 */

अटल अचिन्हित पूर्णांक drm_num_planes(काष्ठा drm_device *dev)
अणु
	अचिन्हित पूर्णांक num = 0;
	काष्ठा drm_plane *पंचांगp;

	drm_क्रम_each_plane(पंचांगp, dev) अणु
		num++;
	पूर्ण

	वापस num;
पूर्ण

अटल अंतरभूत u32 *
क्रमmats_ptr(काष्ठा drm_क्रमmat_modअगरier_blob *blob)
अणु
	वापस (u32 *)(((अक्षर *)blob) + blob->क्रमmats_offset);
पूर्ण

अटल अंतरभूत काष्ठा drm_क्रमmat_modअगरier *
modअगरiers_ptr(काष्ठा drm_क्रमmat_modअगरier_blob *blob)
अणु
	वापस (काष्ठा drm_क्रमmat_modअगरier *)(((अक्षर *)blob) + blob->modअगरiers_offset);
पूर्ण

अटल पूर्णांक create_in_क्रमmat_blob(काष्ठा drm_device *dev, काष्ठा drm_plane *plane)
अणु
	स्थिर काष्ठा drm_mode_config *config = &dev->mode_config;
	काष्ठा drm_property_blob *blob;
	काष्ठा drm_क्रमmat_modअगरier *mod;
	माप_प्रकार blob_size, क्रमmats_size, modअगरiers_size;
	काष्ठा drm_क्रमmat_modअगरier_blob *blob_data;
	अचिन्हित पूर्णांक i, j;

	क्रमmats_size = माप(__u32) * plane->क्रमmat_count;
	अगर (WARN_ON(!क्रमmats_size)) अणु
		/* 0 क्रमmats are never expected */
		वापस 0;
	पूर्ण

	modअगरiers_size =
		माप(काष्ठा drm_क्रमmat_modअगरier) * plane->modअगरier_count;

	blob_size = माप(काष्ठा drm_क्रमmat_modअगरier_blob);
	/* Modअगरiers offset is a poपूर्णांकer to a काष्ठा with a 64 bit field so it
	 * should be naturally aligned to 8B.
	 */
	BUILD_BUG_ON(माप(काष्ठा drm_क्रमmat_modअगरier_blob) % 8);
	blob_size += ALIGN(क्रमmats_size, 8);
	blob_size += modअगरiers_size;

	blob = drm_property_create_blob(dev, blob_size, शून्य);
	अगर (IS_ERR(blob))
		वापस -1;

	blob_data = blob->data;
	blob_data->version = FORMAT_BLOB_CURRENT;
	blob_data->count_क्रमmats = plane->क्रमmat_count;
	blob_data->क्रमmats_offset = माप(काष्ठा drm_क्रमmat_modअगरier_blob);
	blob_data->count_modअगरiers = plane->modअगरier_count;

	blob_data->modअगरiers_offset =
		ALIGN(blob_data->क्रमmats_offset + क्रमmats_size, 8);

	स_नकल(क्रमmats_ptr(blob_data), plane->क्रमmat_types, क्रमmats_size);

	/* If we can't determine support, just bail */
	अगर (!plane->funcs->क्रमmat_mod_supported)
		जाओ करोne;

	mod = modअगरiers_ptr(blob_data);
	क्रम (i = 0; i < plane->modअगरier_count; i++) अणु
		क्रम (j = 0; j < plane->क्रमmat_count; j++) अणु
			अगर (plane->funcs->क्रमmat_mod_supported(plane,
							       plane->क्रमmat_types[j],
							       plane->modअगरiers[i])) अणु

				mod->क्रमmats |= 1ULL << j;
			पूर्ण
		पूर्ण

		mod->modअगरier = plane->modअगरiers[i];
		mod->offset = 0;
		mod->pad = 0;
		mod++;
	पूर्ण

करोne:
	drm_object_attach_property(&plane->base, config->modअगरiers_property,
				   blob->base.id);

	वापस 0;
पूर्ण

__म_लिखो(9, 0)
अटल पूर्णांक __drm_universal_plane_init(काष्ठा drm_device *dev,
				      काष्ठा drm_plane *plane,
				      uपूर्णांक32_t possible_crtcs,
				      स्थिर काष्ठा drm_plane_funcs *funcs,
				      स्थिर uपूर्णांक32_t *क्रमmats,
				      अचिन्हित पूर्णांक क्रमmat_count,
				      स्थिर uपूर्णांक64_t *क्रमmat_modअगरiers,
				      क्रमागत drm_plane_type type,
				      स्थिर अक्षर *name, बहु_सूची ap)
अणु
	काष्ठा drm_mode_config *config = &dev->mode_config;
	अचिन्हित पूर्णांक क्रमmat_modअगरier_count = 0;
	पूर्णांक ret;

	/* plane index is used with 32bit biपंचांगasks */
	अगर (WARN_ON(config->num_total_plane >= 32))
		वापस -EINVAL;

	WARN_ON(drm_drv_uses_atomic_modeset(dev) &&
		(!funcs->atomic_destroy_state ||
		 !funcs->atomic_duplicate_state));

	ret = drm_mode_object_add(dev, &plane->base, DRM_MODE_OBJECT_PLANE);
	अगर (ret)
		वापस ret;

	drm_modeset_lock_init(&plane->mutex);

	plane->base.properties = &plane->properties;
	plane->dev = dev;
	plane->funcs = funcs;
	plane->क्रमmat_types = kदो_स्मृति_array(क्रमmat_count, माप(uपूर्णांक32_t),
					    GFP_KERNEL);
	अगर (!plane->क्रमmat_types) अणु
		DRM_DEBUG_KMS("out of memory when allocating plane\n");
		drm_mode_object_unरेजिस्टर(dev, &plane->base);
		वापस -ENOMEM;
	पूर्ण

	/*
	 * First driver to need more than 64 क्रमmats needs to fix this. Each
	 * क्रमmat is encoded as a bit and the current code only supports a u64.
	 */
	अगर (WARN_ON(क्रमmat_count > 64))
		वापस -EINVAL;

	अगर (क्रमmat_modअगरiers) अणु
		स्थिर uपूर्णांक64_t *temp_modअगरiers = क्रमmat_modअगरiers;

		जबतक (*temp_modअगरiers++ != DRM_FORMAT_MOD_INVALID)
			क्रमmat_modअगरier_count++;
	पूर्ण

	अगर (क्रमmat_modअगरier_count)
		config->allow_fb_modअगरiers = true;

	plane->modअगरier_count = क्रमmat_modअगरier_count;
	plane->modअगरiers = kदो_स्मृति_array(क्रमmat_modअगरier_count,
					 माप(क्रमmat_modअगरiers[0]),
					 GFP_KERNEL);

	अगर (क्रमmat_modअगरier_count && !plane->modअगरiers) अणु
		DRM_DEBUG_KMS("out of memory when allocating plane\n");
		kमुक्त(plane->क्रमmat_types);
		drm_mode_object_unरेजिस्टर(dev, &plane->base);
		वापस -ENOMEM;
	पूर्ण

	अगर (name) अणु
		plane->name = kvaप्र_लिखो(GFP_KERNEL, name, ap);
	पूर्ण अन्यथा अणु
		plane->name = kaप्र_लिखो(GFP_KERNEL, "plane-%d",
					drm_num_planes(dev));
	पूर्ण
	अगर (!plane->name) अणु
		kमुक्त(plane->क्रमmat_types);
		kमुक्त(plane->modअगरiers);
		drm_mode_object_unरेजिस्टर(dev, &plane->base);
		वापस -ENOMEM;
	पूर्ण

	स_नकल(plane->क्रमmat_types, क्रमmats, क्रमmat_count * माप(uपूर्णांक32_t));
	plane->क्रमmat_count = क्रमmat_count;
	स_नकल(plane->modअगरiers, क्रमmat_modअगरiers,
	       क्रमmat_modअगरier_count * माप(क्रमmat_modअगरiers[0]));
	plane->possible_crtcs = possible_crtcs;
	plane->type = type;

	list_add_tail(&plane->head, &config->plane_list);
	plane->index = config->num_total_plane++;

	drm_object_attach_property(&plane->base,
				   config->plane_type_property,
				   plane->type);

	अगर (drm_core_check_feature(dev, DRIVER_ATOMIC)) अणु
		drm_object_attach_property(&plane->base, config->prop_fb_id, 0);
		drm_object_attach_property(&plane->base, config->prop_in_fence_fd, -1);
		drm_object_attach_property(&plane->base, config->prop_crtc_id, 0);
		drm_object_attach_property(&plane->base, config->prop_crtc_x, 0);
		drm_object_attach_property(&plane->base, config->prop_crtc_y, 0);
		drm_object_attach_property(&plane->base, config->prop_crtc_w, 0);
		drm_object_attach_property(&plane->base, config->prop_crtc_h, 0);
		drm_object_attach_property(&plane->base, config->prop_src_x, 0);
		drm_object_attach_property(&plane->base, config->prop_src_y, 0);
		drm_object_attach_property(&plane->base, config->prop_src_w, 0);
		drm_object_attach_property(&plane->base, config->prop_src_h, 0);
	पूर्ण

	अगर (config->allow_fb_modअगरiers)
		create_in_क्रमmat_blob(dev, plane);

	वापस 0;
पूर्ण

/**
 * drm_universal_plane_init - Initialize a new universal plane object
 * @dev: DRM device
 * @plane: plane object to init
 * @possible_crtcs: biपंचांगask of possible CRTCs
 * @funcs: callbacks क्रम the new plane
 * @क्रमmats: array of supported क्रमmats (DRM_FORMAT\_\*)
 * @क्रमmat_count: number of elements in @क्रमmats
 * @क्रमmat_modअगरiers: array of काष्ठा drm_क्रमmat modअगरiers terminated by
 *                    DRM_FORMAT_MOD_INVALID
 * @type: type of plane (overlay, primary, cursor)
 * @name: म_लिखो style क्रमmat string क्रम the plane name, or शून्य क्रम शेष name
 *
 * Initializes a plane object of type @type. The &drm_plane_funcs.destroy hook
 * should call drm_plane_cleanup() and kमुक्त() the plane काष्ठाure. The plane
 * काष्ठाure should not be allocated with devm_kzalloc().
 *
 * Note: consider using drmm_universal_plane_alloc() instead of
 * drm_universal_plane_init() to let the DRM managed resource infraकाष्ठाure
 * take care of cleanup and deallocation.
 *
 * Returns:
 * Zero on success, error code on failure.
 */
पूर्णांक drm_universal_plane_init(काष्ठा drm_device *dev, काष्ठा drm_plane *plane,
			     uपूर्णांक32_t possible_crtcs,
			     स्थिर काष्ठा drm_plane_funcs *funcs,
			     स्थिर uपूर्णांक32_t *क्रमmats, अचिन्हित पूर्णांक क्रमmat_count,
			     स्थिर uपूर्णांक64_t *क्रमmat_modअगरiers,
			     क्रमागत drm_plane_type type,
			     स्थिर अक्षर *name, ...)
अणु
	बहु_सूची ap;
	पूर्णांक ret;

	WARN_ON(!funcs->destroy);

	बहु_शुरू(ap, name);
	ret = __drm_universal_plane_init(dev, plane, possible_crtcs, funcs,
					 क्रमmats, क्रमmat_count, क्रमmat_modअगरiers,
					 type, name, ap);
	बहु_पूर्ण(ap);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_universal_plane_init);

अटल व्योम drmm_universal_plane_alloc_release(काष्ठा drm_device *dev, व्योम *ptr)
अणु
	काष्ठा drm_plane *plane = ptr;

	अगर (WARN_ON(!plane->dev))
		वापस;

	drm_plane_cleanup(plane);
पूर्ण

व्योम *__drmm_universal_plane_alloc(काष्ठा drm_device *dev, माप_प्रकार size,
				   माप_प्रकार offset, uपूर्णांक32_t possible_crtcs,
				   स्थिर काष्ठा drm_plane_funcs *funcs,
				   स्थिर uपूर्णांक32_t *क्रमmats, अचिन्हित पूर्णांक क्रमmat_count,
				   स्थिर uपूर्णांक64_t *क्रमmat_modअगरiers,
				   क्रमागत drm_plane_type type,
				   स्थिर अक्षर *name, ...)
अणु
	व्योम *container;
	काष्ठा drm_plane *plane;
	बहु_सूची ap;
	पूर्णांक ret;

	अगर (WARN_ON(!funcs || funcs->destroy))
		वापस ERR_PTR(-EINVAL);

	container = drmm_kzalloc(dev, size, GFP_KERNEL);
	अगर (!container)
		वापस ERR_PTR(-ENOMEM);

	plane = container + offset;

	बहु_शुरू(ap, name);
	ret = __drm_universal_plane_init(dev, plane, possible_crtcs, funcs,
					 क्रमmats, क्रमmat_count, क्रमmat_modअगरiers,
					 type, name, ap);
	बहु_पूर्ण(ap);
	अगर (ret)
		वापस ERR_PTR(ret);

	ret = drmm_add_action_or_reset(dev, drmm_universal_plane_alloc_release,
				       plane);
	अगर (ret)
		वापस ERR_PTR(ret);

	वापस container;
पूर्ण
EXPORT_SYMBOL(__drmm_universal_plane_alloc);

पूर्णांक drm_plane_रेजिस्टर_all(काष्ठा drm_device *dev)
अणु
	अचिन्हित पूर्णांक num_planes = 0;
	अचिन्हित पूर्णांक num_zpos = 0;
	काष्ठा drm_plane *plane;
	पूर्णांक ret = 0;

	drm_क्रम_each_plane(plane, dev) अणु
		अगर (plane->funcs->late_रेजिस्टर)
			ret = plane->funcs->late_रेजिस्टर(plane);
		अगर (ret)
			वापस ret;

		अगर (plane->zpos_property)
			num_zpos++;
		num_planes++;
	पूर्ण

	drm_WARN(dev, num_zpos && num_planes != num_zpos,
		 "Mixing planes with and without zpos property is invalid\n");

	वापस 0;
पूर्ण

व्योम drm_plane_unरेजिस्टर_all(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_plane *plane;

	drm_क्रम_each_plane(plane, dev) अणु
		अगर (plane->funcs->early_unरेजिस्टर)
			plane->funcs->early_unरेजिस्टर(plane);
	पूर्ण
पूर्ण

/**
 * drm_plane_init - Initialize a legacy plane
 * @dev: DRM device
 * @plane: plane object to init
 * @possible_crtcs: biपंचांगask of possible CRTCs
 * @funcs: callbacks क्रम the new plane
 * @क्रमmats: array of supported क्रमmats (DRM_FORMAT\_\*)
 * @क्रमmat_count: number of elements in @क्रमmats
 * @is_primary: plane type (primary vs overlay)
 *
 * Legacy API to initialize a DRM plane.
 *
 * New drivers should call drm_universal_plane_init() instead.
 *
 * Returns:
 * Zero on success, error code on failure.
 */
पूर्णांक drm_plane_init(काष्ठा drm_device *dev, काष्ठा drm_plane *plane,
		   uपूर्णांक32_t possible_crtcs,
		   स्थिर काष्ठा drm_plane_funcs *funcs,
		   स्थिर uपूर्णांक32_t *क्रमmats, अचिन्हित पूर्णांक क्रमmat_count,
		   bool is_primary)
अणु
	क्रमागत drm_plane_type type;

	type = is_primary ? DRM_PLANE_TYPE_PRIMARY : DRM_PLANE_TYPE_OVERLAY;
	वापस drm_universal_plane_init(dev, plane, possible_crtcs, funcs,
					क्रमmats, क्रमmat_count,
					शून्य, type, शून्य);
पूर्ण
EXPORT_SYMBOL(drm_plane_init);

/**
 * drm_plane_cleanup - Clean up the core plane usage
 * @plane: plane to cleanup
 *
 * This function cleans up @plane and हटाओs it from the DRM mode setting
 * core. Note that the function करोes *not* मुक्त the plane काष्ठाure itself,
 * this is the responsibility of the caller.
 */
व्योम drm_plane_cleanup(काष्ठा drm_plane *plane)
अणु
	काष्ठा drm_device *dev = plane->dev;

	drm_modeset_lock_fini(&plane->mutex);

	kमुक्त(plane->क्रमmat_types);
	kमुक्त(plane->modअगरiers);
	drm_mode_object_unरेजिस्टर(dev, &plane->base);

	BUG_ON(list_empty(&plane->head));

	/* Note that the plane_list is considered to be अटल; should we
	 * हटाओ the drm_plane at runसमय we would have to decrement all
	 * the indices on the drm_plane after us in the plane_list.
	 */

	list_del(&plane->head);
	dev->mode_config.num_total_plane--;

	WARN_ON(plane->state && !plane->funcs->atomic_destroy_state);
	अगर (plane->state && plane->funcs->atomic_destroy_state)
		plane->funcs->atomic_destroy_state(plane, plane->state);

	kमुक्त(plane->name);

	स_रखो(plane, 0, माप(*plane));
पूर्ण
EXPORT_SYMBOL(drm_plane_cleanup);

/**
 * drm_plane_from_index - find the रेजिस्टरed plane at an index
 * @dev: DRM device
 * @idx: index of रेजिस्टरed plane to find क्रम
 *
 * Given a plane index, वापस the रेजिस्टरed plane from DRM device's
 * list of planes with matching index. This is the inverse of drm_plane_index().
 */
काष्ठा drm_plane *
drm_plane_from_index(काष्ठा drm_device *dev, पूर्णांक idx)
अणु
	काष्ठा drm_plane *plane;

	drm_क्रम_each_plane(plane, dev)
		अगर (idx == plane->index)
			वापस plane;

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(drm_plane_from_index);

/**
 * drm_plane_क्रमce_disable - Forcibly disable a plane
 * @plane: plane to disable
 *
 * Forces the plane to be disabled.
 *
 * Used when the plane's current framebuffer is destroyed,
 * and when restoring fbdev mode.
 *
 * Note that this function is not suitable क्रम atomic drivers, since it करोesn't
 * wire through the lock acquisition context properly and hence can't handle
 * retries or driver निजी locks. You probably want to use
 * drm_atomic_helper_disable_plane() or
 * drm_atomic_helper_disable_planes_on_crtc() instead.
 */
व्योम drm_plane_क्रमce_disable(काष्ठा drm_plane *plane)
अणु
	पूर्णांक ret;

	अगर (!plane->fb)
		वापस;

	WARN_ON(drm_drv_uses_atomic_modeset(plane->dev));

	plane->old_fb = plane->fb;
	ret = plane->funcs->disable_plane(plane, शून्य);
	अगर (ret) अणु
		DRM_ERROR("failed to disable plane with busy fb\n");
		plane->old_fb = शून्य;
		वापस;
	पूर्ण
	/* disconnect the plane from the fb and crtc: */
	drm_framebuffer_put(plane->old_fb);
	plane->old_fb = शून्य;
	plane->fb = शून्य;
	plane->crtc = शून्य;
पूर्ण
EXPORT_SYMBOL(drm_plane_क्रमce_disable);

/**
 * drm_mode_plane_set_obj_prop - set the value of a property
 * @plane: drm plane object to set property value क्रम
 * @property: property to set
 * @value: value the property should be set to
 *
 * This functions sets a given property on a given plane object. This function
 * calls the driver's ->set_property callback and changes the software state of
 * the property अगर the callback succeeds.
 *
 * Returns:
 * Zero on success, error code on failure.
 */
पूर्णांक drm_mode_plane_set_obj_prop(काष्ठा drm_plane *plane,
				काष्ठा drm_property *property,
				uपूर्णांक64_t value)
अणु
	पूर्णांक ret = -EINVAL;
	काष्ठा drm_mode_object *obj = &plane->base;

	अगर (plane->funcs->set_property)
		ret = plane->funcs->set_property(plane, property, value);
	अगर (!ret)
		drm_object_property_set_value(obj, property, value);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_mode_plane_set_obj_prop);

पूर्णांक drm_mode_getplane_res(काष्ठा drm_device *dev, व्योम *data,
			  काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_mode_get_plane_res *plane_resp = data;
	काष्ठा drm_plane *plane;
	uपूर्णांक32_t __user *plane_ptr;
	पूर्णांक count = 0;

	अगर (!drm_core_check_feature(dev, DRIVER_MODESET))
		वापस -EOPNOTSUPP;

	plane_ptr = u64_to_user_ptr(plane_resp->plane_id_ptr);

	/*
	 * This ioctl is called twice, once to determine how much space is
	 * needed, and the 2nd समय to fill it.
	 */
	drm_क्रम_each_plane(plane, dev) अणु
		/*
		 * Unless userspace set the 'universal planes'
		 * capability bit, only advertise overlays.
		 */
		अगर (plane->type != DRM_PLANE_TYPE_OVERLAY &&
		    !file_priv->universal_planes)
			जारी;

		अगर (drm_lease_held(file_priv, plane->base.id)) अणु
			अगर (count < plane_resp->count_planes &&
			    put_user(plane->base.id, plane_ptr + count))
				वापस -EFAULT;
			count++;
		पूर्ण
	पूर्ण
	plane_resp->count_planes = count;

	वापस 0;
पूर्ण

पूर्णांक drm_mode_getplane(काष्ठा drm_device *dev, व्योम *data,
		      काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_mode_get_plane *plane_resp = data;
	काष्ठा drm_plane *plane;
	uपूर्णांक32_t __user *क्रमmat_ptr;

	अगर (!drm_core_check_feature(dev, DRIVER_MODESET))
		वापस -EOPNOTSUPP;

	plane = drm_plane_find(dev, file_priv, plane_resp->plane_id);
	अगर (!plane)
		वापस -ENOENT;

	drm_modeset_lock(&plane->mutex, शून्य);
	अगर (plane->state && plane->state->crtc && drm_lease_held(file_priv, plane->state->crtc->base.id))
		plane_resp->crtc_id = plane->state->crtc->base.id;
	अन्यथा अगर (!plane->state && plane->crtc && drm_lease_held(file_priv, plane->crtc->base.id))
		plane_resp->crtc_id = plane->crtc->base.id;
	अन्यथा
		plane_resp->crtc_id = 0;

	अगर (plane->state && plane->state->fb)
		plane_resp->fb_id = plane->state->fb->base.id;
	अन्यथा अगर (!plane->state && plane->fb)
		plane_resp->fb_id = plane->fb->base.id;
	अन्यथा
		plane_resp->fb_id = 0;
	drm_modeset_unlock(&plane->mutex);

	plane_resp->plane_id = plane->base.id;
	plane_resp->possible_crtcs = drm_lease_filter_crtcs(file_priv,
							    plane->possible_crtcs);

	plane_resp->gamma_size = 0;

	/*
	 * This ioctl is called twice, once to determine how much space is
	 * needed, and the 2nd समय to fill it.
	 */
	अगर (plane->क्रमmat_count &&
	    (plane_resp->count_क्रमmat_types >= plane->क्रमmat_count)) अणु
		क्रमmat_ptr = (uपूर्णांक32_t __user *)(अचिन्हित दीर्घ)plane_resp->क्रमmat_type_ptr;
		अगर (copy_to_user(क्रमmat_ptr,
				 plane->क्रमmat_types,
				 माप(uपूर्णांक32_t) * plane->क्रमmat_count)) अणु
			वापस -EFAULT;
		पूर्ण
	पूर्ण
	plane_resp->count_क्रमmat_types = plane->क्रमmat_count;

	वापस 0;
पूर्ण

पूर्णांक drm_plane_check_pixel_क्रमmat(काष्ठा drm_plane *plane,
				 u32 क्रमmat, u64 modअगरier)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < plane->क्रमmat_count; i++) अणु
		अगर (क्रमmat == plane->क्रमmat_types[i])
			अवरोध;
	पूर्ण
	अगर (i == plane->क्रमmat_count)
		वापस -EINVAL;

	अगर (plane->funcs->क्रमmat_mod_supported) अणु
		अगर (!plane->funcs->क्रमmat_mod_supported(plane, क्रमmat, modअगरier))
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		अगर (!plane->modअगरier_count)
			वापस 0;

		क्रम (i = 0; i < plane->modअगरier_count; i++) अणु
			अगर (modअगरier == plane->modअगरiers[i])
				अवरोध;
		पूर्ण
		अगर (i == plane->modअगरier_count)
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __setplane_check(काष्ठा drm_plane *plane,
			    काष्ठा drm_crtc *crtc,
			    काष्ठा drm_framebuffer *fb,
			    पूर्णांक32_t crtc_x, पूर्णांक32_t crtc_y,
			    uपूर्णांक32_t crtc_w, uपूर्णांक32_t crtc_h,
			    uपूर्णांक32_t src_x, uपूर्णांक32_t src_y,
			    uपूर्णांक32_t src_w, uपूर्णांक32_t src_h)
अणु
	पूर्णांक ret;

	/* Check whether this plane is usable on this CRTC */
	अगर (!(plane->possible_crtcs & drm_crtc_mask(crtc))) अणु
		DRM_DEBUG_KMS("Invalid crtc for plane\n");
		वापस -EINVAL;
	पूर्ण

	/* Check whether this plane supports the fb pixel क्रमmat. */
	ret = drm_plane_check_pixel_क्रमmat(plane, fb->क्रमmat->क्रमmat,
					   fb->modअगरier);
	अगर (ret) अणु
		DRM_DEBUG_KMS("Invalid pixel format %p4cc, modifier 0x%llx\n",
			      &fb->क्रमmat->क्रमmat, fb->modअगरier);
		वापस ret;
	पूर्ण

	/* Give drivers some help against पूर्णांकeger overflows */
	अगर (crtc_w > पूर्णांक_उच्च ||
	    crtc_x > पूर्णांक_उच्च - (पूर्णांक32_t) crtc_w ||
	    crtc_h > पूर्णांक_उच्च ||
	    crtc_y > पूर्णांक_उच्च - (पूर्णांक32_t) crtc_h) अणु
		DRM_DEBUG_KMS("Invalid CRTC coordinates %ux%u+%d+%d\n",
			      crtc_w, crtc_h, crtc_x, crtc_y);
		वापस -दुस्फल;
	पूर्ण

	ret = drm_framebuffer_check_src_coords(src_x, src_y, src_w, src_h, fb);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

/**
 * drm_any_plane_has_क्रमmat - Check whether any plane supports this क्रमmat and modअगरier combination
 * @dev: DRM device
 * @क्रमmat: pixel क्रमmat (DRM_FORMAT_*)
 * @modअगरier: data layout modअगरier
 *
 * Returns:
 * Whether at least one plane supports the specअगरied क्रमmat and modअगरier combination.
 */
bool drm_any_plane_has_क्रमmat(काष्ठा drm_device *dev,
			      u32 क्रमmat, u64 modअगरier)
अणु
	काष्ठा drm_plane *plane;

	drm_क्रम_each_plane(plane, dev) अणु
		अगर (drm_plane_check_pixel_क्रमmat(plane, क्रमmat, modअगरier) == 0)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण
EXPORT_SYMBOL(drm_any_plane_has_क्रमmat);

/*
 * __setplane_पूर्णांकernal - setplane handler क्रम पूर्णांकernal callers
 *
 * This function will take a reference on the new fb क्रम the plane
 * on success.
 *
 * src_अणुx,y,w,hपूर्ण are provided in 16.16 fixed poपूर्णांक क्रमmat
 */
अटल पूर्णांक __setplane_पूर्णांकernal(काष्ठा drm_plane *plane,
			       काष्ठा drm_crtc *crtc,
			       काष्ठा drm_framebuffer *fb,
			       पूर्णांक32_t crtc_x, पूर्णांक32_t crtc_y,
			       uपूर्णांक32_t crtc_w, uपूर्णांक32_t crtc_h,
			       /* src_अणुx,y,w,hपूर्ण values are 16.16 fixed poपूर्णांक */
			       uपूर्णांक32_t src_x, uपूर्णांक32_t src_y,
			       uपूर्णांक32_t src_w, uपूर्णांक32_t src_h,
			       काष्ठा drm_modeset_acquire_ctx *ctx)
अणु
	पूर्णांक ret = 0;

	WARN_ON(drm_drv_uses_atomic_modeset(plane->dev));

	/* No fb means shut it करोwn */
	अगर (!fb) अणु
		plane->old_fb = plane->fb;
		ret = plane->funcs->disable_plane(plane, ctx);
		अगर (!ret) अणु
			plane->crtc = शून्य;
			plane->fb = शून्य;
		पूर्ण अन्यथा अणु
			plane->old_fb = शून्य;
		पूर्ण
		जाओ out;
	पूर्ण

	ret = __setplane_check(plane, crtc, fb,
			       crtc_x, crtc_y, crtc_w, crtc_h,
			       src_x, src_y, src_w, src_h);
	अगर (ret)
		जाओ out;

	plane->old_fb = plane->fb;
	ret = plane->funcs->update_plane(plane, crtc, fb,
					 crtc_x, crtc_y, crtc_w, crtc_h,
					 src_x, src_y, src_w, src_h, ctx);
	अगर (!ret) अणु
		plane->crtc = crtc;
		plane->fb = fb;
		drm_framebuffer_get(plane->fb);
	पूर्ण अन्यथा अणु
		plane->old_fb = शून्य;
	पूर्ण

out:
	अगर (plane->old_fb)
		drm_framebuffer_put(plane->old_fb);
	plane->old_fb = शून्य;

	वापस ret;
पूर्ण

अटल पूर्णांक __setplane_atomic(काष्ठा drm_plane *plane,
			     काष्ठा drm_crtc *crtc,
			     काष्ठा drm_framebuffer *fb,
			     पूर्णांक32_t crtc_x, पूर्णांक32_t crtc_y,
			     uपूर्णांक32_t crtc_w, uपूर्णांक32_t crtc_h,
			     uपूर्णांक32_t src_x, uपूर्णांक32_t src_y,
			     uपूर्णांक32_t src_w, uपूर्णांक32_t src_h,
			     काष्ठा drm_modeset_acquire_ctx *ctx)
अणु
	पूर्णांक ret;

	WARN_ON(!drm_drv_uses_atomic_modeset(plane->dev));

	/* No fb means shut it करोwn */
	अगर (!fb)
		वापस plane->funcs->disable_plane(plane, ctx);

	/*
	 * FIXME: This is redundant with drm_atomic_plane_check(),
	 * but the legacy cursor/"async" .update_plane() tricks
	 * करोn't call that so we still need this here. Should हटाओ
	 * this when all .update_plane() implementations have been
	 * fixed to call drm_atomic_plane_check().
	 */
	ret = __setplane_check(plane, crtc, fb,
			       crtc_x, crtc_y, crtc_w, crtc_h,
			       src_x, src_y, src_w, src_h);
	अगर (ret)
		वापस ret;

	वापस plane->funcs->update_plane(plane, crtc, fb,
					  crtc_x, crtc_y, crtc_w, crtc_h,
					  src_x, src_y, src_w, src_h, ctx);
पूर्ण

अटल पूर्णांक setplane_पूर्णांकernal(काष्ठा drm_plane *plane,
			     काष्ठा drm_crtc *crtc,
			     काष्ठा drm_framebuffer *fb,
			     पूर्णांक32_t crtc_x, पूर्णांक32_t crtc_y,
			     uपूर्णांक32_t crtc_w, uपूर्णांक32_t crtc_h,
			     /* src_अणुx,y,w,hपूर्ण values are 16.16 fixed poपूर्णांक */
			     uपूर्णांक32_t src_x, uपूर्णांक32_t src_y,
			     uपूर्णांक32_t src_w, uपूर्णांक32_t src_h)
अणु
	काष्ठा drm_modeset_acquire_ctx ctx;
	पूर्णांक ret;

	DRM_MODESET_LOCK_ALL_BEGIN(plane->dev, ctx,
				   DRM_MODESET_ACQUIRE_INTERRUPTIBLE, ret);

	अगर (drm_drv_uses_atomic_modeset(plane->dev))
		ret = __setplane_atomic(plane, crtc, fb,
					crtc_x, crtc_y, crtc_w, crtc_h,
					src_x, src_y, src_w, src_h, &ctx);
	अन्यथा
		ret = __setplane_पूर्णांकernal(plane, crtc, fb,
					  crtc_x, crtc_y, crtc_w, crtc_h,
					  src_x, src_y, src_w, src_h, &ctx);

	DRM_MODESET_LOCK_ALL_END(plane->dev, ctx, ret);

	वापस ret;
पूर्ण

पूर्णांक drm_mode_setplane(काष्ठा drm_device *dev, व्योम *data,
		      काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_mode_set_plane *plane_req = data;
	काष्ठा drm_plane *plane;
	काष्ठा drm_crtc *crtc = शून्य;
	काष्ठा drm_framebuffer *fb = शून्य;
	पूर्णांक ret;

	अगर (!drm_core_check_feature(dev, DRIVER_MODESET))
		वापस -EOPNOTSUPP;

	/*
	 * First, find the plane, crtc, and fb objects.  If not available,
	 * we करोn't bother to call the driver.
	 */
	plane = drm_plane_find(dev, file_priv, plane_req->plane_id);
	अगर (!plane) अणु
		DRM_DEBUG_KMS("Unknown plane ID %d\n",
			      plane_req->plane_id);
		वापस -ENOENT;
	पूर्ण

	अगर (plane_req->fb_id) अणु
		fb = drm_framebuffer_lookup(dev, file_priv, plane_req->fb_id);
		अगर (!fb) अणु
			DRM_DEBUG_KMS("Unknown framebuffer ID %d\n",
				      plane_req->fb_id);
			वापस -ENOENT;
		पूर्ण

		crtc = drm_crtc_find(dev, file_priv, plane_req->crtc_id);
		अगर (!crtc) अणु
			drm_framebuffer_put(fb);
			DRM_DEBUG_KMS("Unknown crtc ID %d\n",
				      plane_req->crtc_id);
			वापस -ENOENT;
		पूर्ण
	पूर्ण

	ret = setplane_पूर्णांकernal(plane, crtc, fb,
				plane_req->crtc_x, plane_req->crtc_y,
				plane_req->crtc_w, plane_req->crtc_h,
				plane_req->src_x, plane_req->src_y,
				plane_req->src_w, plane_req->src_h);

	अगर (fb)
		drm_framebuffer_put(fb);

	वापस ret;
पूर्ण

अटल पूर्णांक drm_mode_cursor_universal(काष्ठा drm_crtc *crtc,
				     काष्ठा drm_mode_cursor2 *req,
				     काष्ठा drm_file *file_priv,
				     काष्ठा drm_modeset_acquire_ctx *ctx)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा drm_plane *plane = crtc->cursor;
	काष्ठा drm_framebuffer *fb = शून्य;
	काष्ठा drm_mode_fb_cmd2 fbreq = अणु
		.width = req->width,
		.height = req->height,
		.pixel_क्रमmat = DRM_FORMAT_ARGB8888,
		.pitches = अणु req->width * 4 पूर्ण,
		.handles = अणु req->handle पूर्ण,
	पूर्ण;
	पूर्णांक32_t crtc_x, crtc_y;
	uपूर्णांक32_t crtc_w = 0, crtc_h = 0;
	uपूर्णांक32_t src_w = 0, src_h = 0;
	पूर्णांक ret = 0;

	BUG_ON(!plane);
	WARN_ON(plane->crtc != crtc && plane->crtc != शून्य);

	/*
	 * Obtain fb we'll be using (either new or existing) and take an extra
	 * reference to it अगर fb != null.  setplane will take care of dropping
	 * the reference अगर the plane update fails.
	 */
	अगर (req->flags & DRM_MODE_CURSOR_BO) अणु
		अगर (req->handle) अणु
			fb = drm_पूर्णांकernal_framebuffer_create(dev, &fbreq, file_priv);
			अगर (IS_ERR(fb)) अणु
				DRM_DEBUG_KMS("failed to wrap cursor buffer in drm framebuffer\n");
				वापस PTR_ERR(fb);
			पूर्ण

			fb->hot_x = req->hot_x;
			fb->hot_y = req->hot_y;
		पूर्ण अन्यथा अणु
			fb = शून्य;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (plane->state)
			fb = plane->state->fb;
		अन्यथा
			fb = plane->fb;

		अगर (fb)
			drm_framebuffer_get(fb);
	पूर्ण

	अगर (req->flags & DRM_MODE_CURSOR_MOVE) अणु
		crtc_x = req->x;
		crtc_y = req->y;
	पूर्ण अन्यथा अणु
		crtc_x = crtc->cursor_x;
		crtc_y = crtc->cursor_y;
	पूर्ण

	अगर (fb) अणु
		crtc_w = fb->width;
		crtc_h = fb->height;
		src_w = fb->width << 16;
		src_h = fb->height << 16;
	पूर्ण

	अगर (drm_drv_uses_atomic_modeset(dev))
		ret = __setplane_atomic(plane, crtc, fb,
					crtc_x, crtc_y, crtc_w, crtc_h,
					0, 0, src_w, src_h, ctx);
	अन्यथा
		ret = __setplane_पूर्णांकernal(plane, crtc, fb,
					  crtc_x, crtc_y, crtc_w, crtc_h,
					  0, 0, src_w, src_h, ctx);

	अगर (fb)
		drm_framebuffer_put(fb);

	/* Update successful; save new cursor position, अगर necessary */
	अगर (ret == 0 && req->flags & DRM_MODE_CURSOR_MOVE) अणु
		crtc->cursor_x = req->x;
		crtc->cursor_y = req->y;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक drm_mode_cursor_common(काष्ठा drm_device *dev,
				  काष्ठा drm_mode_cursor2 *req,
				  काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_modeset_acquire_ctx ctx;
	पूर्णांक ret = 0;

	अगर (!drm_core_check_feature(dev, DRIVER_MODESET))
		वापस -EOPNOTSUPP;

	अगर (!req->flags || (~DRM_MODE_CURSOR_FLAGS & req->flags))
		वापस -EINVAL;

	crtc = drm_crtc_find(dev, file_priv, req->crtc_id);
	अगर (!crtc) अणु
		DRM_DEBUG_KMS("Unknown CRTC ID %d\n", req->crtc_id);
		वापस -ENOENT;
	पूर्ण

	drm_modeset_acquire_init(&ctx, DRM_MODESET_ACQUIRE_INTERRUPTIBLE);
retry:
	ret = drm_modeset_lock(&crtc->mutex, &ctx);
	अगर (ret)
		जाओ out;
	/*
	 * If this crtc has a universal cursor plane, call that plane's update
	 * handler rather than using legacy cursor handlers.
	 */
	अगर (crtc->cursor) अणु
		ret = drm_modeset_lock(&crtc->cursor->mutex, &ctx);
		अगर (ret)
			जाओ out;

		अगर (!drm_lease_held(file_priv, crtc->cursor->base.id)) अणु
			ret = -EACCES;
			जाओ out;
		पूर्ण

		ret = drm_mode_cursor_universal(crtc, req, file_priv, &ctx);
		जाओ out;
	पूर्ण

	अगर (req->flags & DRM_MODE_CURSOR_BO) अणु
		अगर (!crtc->funcs->cursor_set && !crtc->funcs->cursor_set2) अणु
			ret = -ENXIO;
			जाओ out;
		पूर्ण
		/* Turns off the cursor अगर handle is 0 */
		अगर (crtc->funcs->cursor_set2)
			ret = crtc->funcs->cursor_set2(crtc, file_priv, req->handle,
						      req->width, req->height, req->hot_x, req->hot_y);
		अन्यथा
			ret = crtc->funcs->cursor_set(crtc, file_priv, req->handle,
						      req->width, req->height);
	पूर्ण

	अगर (req->flags & DRM_MODE_CURSOR_MOVE) अणु
		अगर (crtc->funcs->cursor_move) अणु
			ret = crtc->funcs->cursor_move(crtc, req->x, req->y);
		पूर्ण अन्यथा अणु
			ret = -EFAULT;
			जाओ out;
		पूर्ण
	पूर्ण
out:
	अगर (ret == -EDEADLK) अणु
		ret = drm_modeset_backoff(&ctx);
		अगर (!ret)
			जाओ retry;
	पूर्ण

	drm_modeset_drop_locks(&ctx);
	drm_modeset_acquire_fini(&ctx);

	वापस ret;

पूर्ण


पूर्णांक drm_mode_cursor_ioctl(काष्ठा drm_device *dev,
			  व्योम *data, काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_mode_cursor *req = data;
	काष्ठा drm_mode_cursor2 new_req;

	स_नकल(&new_req, req, माप(काष्ठा drm_mode_cursor));
	new_req.hot_x = new_req.hot_y = 0;

	वापस drm_mode_cursor_common(dev, &new_req, file_priv);
पूर्ण

/*
 * Set the cursor configuration based on user request. This implements the 2nd
 * version of the cursor ioctl, which allows userspace to additionally specअगरy
 * the hotspot of the poपूर्णांकer.
 */
पूर्णांक drm_mode_cursor2_ioctl(काष्ठा drm_device *dev,
			   व्योम *data, काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_mode_cursor2 *req = data;

	वापस drm_mode_cursor_common(dev, req, file_priv);
पूर्ण

पूर्णांक drm_mode_page_flip_ioctl(काष्ठा drm_device *dev,
			     व्योम *data, काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_mode_crtc_page_flip_target *page_flip = data;
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_plane *plane;
	काष्ठा drm_framebuffer *fb = शून्य, *old_fb;
	काष्ठा drm_pending_vblank_event *e = शून्य;
	u32 target_vblank = page_flip->sequence;
	काष्ठा drm_modeset_acquire_ctx ctx;
	पूर्णांक ret = -EINVAL;

	अगर (!drm_core_check_feature(dev, DRIVER_MODESET))
		वापस -EOPNOTSUPP;

	अगर (page_flip->flags & ~DRM_MODE_PAGE_FLIP_FLAGS)
		वापस -EINVAL;

	अगर (page_flip->sequence != 0 && !(page_flip->flags & DRM_MODE_PAGE_FLIP_TARGET))
		वापस -EINVAL;

	/* Only one of the DRM_MODE_PAGE_FLIP_TARGET_ABSOLUTE/RELATIVE flags
	 * can be specअगरied
	 */
	अगर ((page_flip->flags & DRM_MODE_PAGE_FLIP_TARGET) == DRM_MODE_PAGE_FLIP_TARGET)
		वापस -EINVAL;

	अगर ((page_flip->flags & DRM_MODE_PAGE_FLIP_ASYNC) && !dev->mode_config.async_page_flip)
		वापस -EINVAL;

	crtc = drm_crtc_find(dev, file_priv, page_flip->crtc_id);
	अगर (!crtc)
		वापस -ENOENT;

	plane = crtc->primary;

	अगर (!drm_lease_held(file_priv, plane->base.id))
		वापस -EACCES;

	अगर (crtc->funcs->page_flip_target) अणु
		u32 current_vblank;
		पूर्णांक r;

		r = drm_crtc_vblank_get(crtc);
		अगर (r)
			वापस r;

		current_vblank = (u32)drm_crtc_vblank_count(crtc);

		चयन (page_flip->flags & DRM_MODE_PAGE_FLIP_TARGET) अणु
		हाल DRM_MODE_PAGE_FLIP_TARGET_ABSOLUTE:
			अगर ((पूर्णांक)(target_vblank - current_vblank) > 1) अणु
				DRM_DEBUG("Invalid absolute flip target %u, "
					  "must be <= %u\n", target_vblank,
					  current_vblank + 1);
				drm_crtc_vblank_put(crtc);
				वापस -EINVAL;
			पूर्ण
			अवरोध;
		हाल DRM_MODE_PAGE_FLIP_TARGET_RELATIVE:
			अगर (target_vblank != 0 && target_vblank != 1) अणु
				DRM_DEBUG("Invalid relative flip target %u, "
					  "must be 0 or 1\n", target_vblank);
				drm_crtc_vblank_put(crtc);
				वापस -EINVAL;
			पूर्ण
			target_vblank += current_vblank;
			अवरोध;
		शेष:
			target_vblank = current_vblank +
				!(page_flip->flags & DRM_MODE_PAGE_FLIP_ASYNC);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (crtc->funcs->page_flip == शून्य ||
		   (page_flip->flags & DRM_MODE_PAGE_FLIP_TARGET)) अणु
		वापस -EINVAL;
	पूर्ण

	drm_modeset_acquire_init(&ctx, DRM_MODESET_ACQUIRE_INTERRUPTIBLE);
retry:
	ret = drm_modeset_lock(&crtc->mutex, &ctx);
	अगर (ret)
		जाओ out;
	ret = drm_modeset_lock(&plane->mutex, &ctx);
	अगर (ret)
		जाओ out;

	अगर (plane->state)
		old_fb = plane->state->fb;
	अन्यथा
		old_fb = plane->fb;

	अगर (old_fb == शून्य) अणु
		/* The framebuffer is currently unbound, presumably
		 * due to a hotplug event, that userspace has not
		 * yet discovered.
		 */
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	fb = drm_framebuffer_lookup(dev, file_priv, page_flip->fb_id);
	अगर (!fb) अणु
		ret = -ENOENT;
		जाओ out;
	पूर्ण

	अगर (plane->state) अणु
		स्थिर काष्ठा drm_plane_state *state = plane->state;

		ret = drm_framebuffer_check_src_coords(state->src_x,
						       state->src_y,
						       state->src_w,
						       state->src_h,
						       fb);
	पूर्ण अन्यथा अणु
		ret = drm_crtc_check_viewport(crtc, crtc->x, crtc->y,
					      &crtc->mode, fb);
	पूर्ण
	अगर (ret)
		जाओ out;

	/*
	 * Only check the FOURCC क्रमmat code, excluding modअगरiers. This is
	 * enough क्रम all legacy drivers. Atomic drivers have their own
	 * checks in their ->atomic_check implementation, which will
	 * वापस -EINVAL अगर any hw or driver स्थिरraपूर्णांक is violated due
	 * to modअगरier changes.
	 */
	अगर (old_fb->क्रमmat->क्रमmat != fb->क्रमmat->क्रमmat) अणु
		DRM_DEBUG_KMS("Page flip is not allowed to change frame buffer format.\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (page_flip->flags & DRM_MODE_PAGE_FLIP_EVENT) अणु
		e = kzalloc(माप *e, GFP_KERNEL);
		अगर (!e) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण

		e->event.base.type = DRM_EVENT_FLIP_COMPLETE;
		e->event.base.length = माप(e->event);
		e->event.vbl.user_data = page_flip->user_data;
		e->event.vbl.crtc_id = crtc->base.id;

		ret = drm_event_reserve_init(dev, file_priv, &e->base, &e->event.base);
		अगर (ret) अणु
			kमुक्त(e);
			e = शून्य;
			जाओ out;
		पूर्ण
	पूर्ण

	plane->old_fb = plane->fb;
	अगर (crtc->funcs->page_flip_target)
		ret = crtc->funcs->page_flip_target(crtc, fb, e,
						    page_flip->flags,
						    target_vblank,
						    &ctx);
	अन्यथा
		ret = crtc->funcs->page_flip(crtc, fb, e, page_flip->flags,
					     &ctx);
	अगर (ret) अणु
		अगर (page_flip->flags & DRM_MODE_PAGE_FLIP_EVENT)
			drm_event_cancel_मुक्त(dev, &e->base);
		/* Keep the old fb, करोn't unref it. */
		plane->old_fb = शून्य;
	पूर्ण अन्यथा अणु
		अगर (!plane->state) अणु
			plane->fb = fb;
			drm_framebuffer_get(fb);
		पूर्ण
	पूर्ण

out:
	अगर (fb)
		drm_framebuffer_put(fb);
	अगर (plane->old_fb)
		drm_framebuffer_put(plane->old_fb);
	plane->old_fb = शून्य;

	अगर (ret == -EDEADLK) अणु
		ret = drm_modeset_backoff(&ctx);
		अगर (!ret)
			जाओ retry;
	पूर्ण

	drm_modeset_drop_locks(&ctx);
	drm_modeset_acquire_fini(&ctx);

	अगर (ret && crtc->funcs->page_flip_target)
		drm_crtc_vblank_put(crtc);

	वापस ret;
पूर्ण

काष्ठा drm_property *
drm_create_scaling_filter_prop(काष्ठा drm_device *dev,
			       अचिन्हित पूर्णांक supported_filters)
अणु
	काष्ठा drm_property *prop;
	अटल स्थिर काष्ठा drm_prop_क्रमागत_list props[] = अणु
		अणु DRM_SCALING_FILTER_DEFAULT, "Default" पूर्ण,
		अणु DRM_SCALING_FILTER_NEAREST_NEIGHBOR, "Nearest Neighbor" पूर्ण,
	पूर्ण;
	अचिन्हित पूर्णांक valid_mode_mask = BIT(DRM_SCALING_FILTER_DEFAULT) |
				       BIT(DRM_SCALING_FILTER_NEAREST_NEIGHBOR);
	पूर्णांक i;

	अगर (WARN_ON((supported_filters & ~valid_mode_mask) ||
		    ((supported_filters & BIT(DRM_SCALING_FILTER_DEFAULT)) == 0)))
		वापस ERR_PTR(-EINVAL);

	prop = drm_property_create(dev, DRM_MODE_PROP_ENUM,
				   "SCALING_FILTER",
				   hweight32(supported_filters));
	अगर (!prop)
		वापस ERR_PTR(-ENOMEM);

	क्रम (i = 0; i < ARRAY_SIZE(props); i++) अणु
		पूर्णांक ret;

		अगर (!(BIT(props[i].type) & supported_filters))
			जारी;

		ret = drm_property_add_क्रमागत(prop, props[i].type,
					    props[i].name);

		अगर (ret) अणु
			drm_property_destroy(dev, prop);

			वापस ERR_PTR(ret);
		पूर्ण
	पूर्ण

	वापस prop;
पूर्ण

/**
 * drm_plane_create_scaling_filter_property - create a new scaling filter
 * property
 *
 * @plane: drm plane
 * @supported_filters: biपंचांगask of supported scaling filters, must include
 *		       BIT(DRM_SCALING_FILTER_DEFAULT).
 *
 * This function lets driver to enable the scaling filter property on a given
 * plane.
 *
 * RETURNS:
 * Zero क्रम success or -त्रुटि_सं
 */
पूर्णांक drm_plane_create_scaling_filter_property(काष्ठा drm_plane *plane,
					     अचिन्हित पूर्णांक supported_filters)
अणु
	काष्ठा drm_property *prop =
		drm_create_scaling_filter_prop(plane->dev, supported_filters);

	अगर (IS_ERR(prop))
		वापस PTR_ERR(prop);

	drm_object_attach_property(&plane->base, prop,
				   DRM_SCALING_FILTER_DEFAULT);
	plane->scaling_filter_property = prop;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_plane_create_scaling_filter_property);
