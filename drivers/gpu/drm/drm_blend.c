<शैली गुरु>
/*
 * Copyright (C) 2016 Samsung Electronics Co.Ltd
 * Authors:
 *	Marek Szyprowski <m.szyprowski@samsung.com>
 *
 * DRM core plane blending related functions
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
#समावेश <linux/slab.h>
#समावेश <linux/sort.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_blend.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "drm_crtc_internal.h"

/**
 * DOC: overview
 *
 * The basic plane composition model supported by standard plane properties only
 * has a source rectangle (in logical pixels within the &drm_framebuffer), with
 * sub-pixel accuracy, which is scaled up to a pixel-aligned destination
 * rectangle in the visible area of a &drm_crtc. The visible area of a CRTC is
 * defined by the horizontal and vertical visible pixels (stored in @hdisplay
 * and @vdisplay) of the requested mode (stored in &drm_crtc_state.mode). These
 * two rectangles are both stored in the &drm_plane_state.
 *
 * For the atomic ioctl the following standard (atomic) properties on the plane object
 * encode the basic plane composition model:
 *
 * SRC_X:
 * 	X coordinate offset क्रम the source rectangle within the
 * 	&drm_framebuffer, in 16.16 fixed poपूर्णांक. Must be positive.
 * SRC_Y:
 * 	Y coordinate offset क्रम the source rectangle within the
 * 	&drm_framebuffer, in 16.16 fixed poपूर्णांक. Must be positive.
 * SRC_W:
 * 	Width क्रम the source rectangle within the &drm_framebuffer, in 16.16
 * 	fixed poपूर्णांक. SRC_X plus SRC_W must be within the width of the source
 * 	framebuffer. Must be positive.
 * SRC_H:
 * 	Height क्रम the source rectangle within the &drm_framebuffer, in 16.16
 * 	fixed poपूर्णांक. SRC_Y plus SRC_H must be within the height of the source
 * 	framebuffer. Must be positive.
 * CRTC_X:
 * 	X coordinate offset क्रम the destination rectangle. Can be negative.
 * CRTC_Y:
 * 	Y coordinate offset क्रम the destination rectangle. Can be negative.
 * CRTC_W:
 * 	Width क्रम the destination rectangle. CRTC_X plus CRTC_W can extend past
 * 	the currently visible horizontal area of the &drm_crtc.
 * CRTC_H:
 * 	Height क्रम the destination rectangle. CRTC_Y plus CRTC_H can extend past
 * 	the currently visible vertical area of the &drm_crtc.
 * FB_ID:
 * 	Mode object ID of the &drm_framebuffer this plane should scan out.
 * CRTC_ID:
 * 	Mode object ID of the &drm_crtc this plane should be connected to.
 *
 * Note that the source rectangle must fully lie within the bounds of the
 * &drm_framebuffer. The destination rectangle can lie outside of the visible
 * area of the current mode of the CRTC. It must be apprpriately clipped by the
 * driver, which can be करोne by calling drm_plane_helper_check_update(). Drivers
 * are also allowed to round the subpixel sampling positions appropriately, but
 * only to the next full pixel. No pixel outside of the source rectangle may
 * ever be sampled, which is important when applying more sophisticated
 * filtering than just a bilinear one when scaling. The filtering mode when
 * scaling is unspecअगरied.
 *
 * On top of this basic transक्रमmation additional properties can be exposed by
 * the driver:
 *
 * alpha:
 * 	Alpha is setup with drm_plane_create_alpha_property(). It controls the
 * 	plane-wide opacity, from transparent (0) to opaque (0xffff). It can be
 * 	combined with pixel alpha.
 *	The pixel values in the framebuffers are expected to not be
 *	pre-multiplied by the global alpha associated to the plane.
 *
 * rotation:
 *	Rotation is set up with drm_plane_create_rotation_property(). It adds a
 *	rotation and reflection step between the source and destination rectangles.
 *	Without this property the rectangle is only scaled, but not rotated or
 *	reflected.
 *
 *	Possbile values:
 *
 *	"rotate-<degrees>":
 *		Signals that a drm plane is rotated <degrees> degrees in counter
 *		घड़ीwise direction.
 *
 *	"reflect-<axis>":
 *		Signals that the contents of a drm plane is reflected aदीर्घ the
 *		<axis> axis, in the same way as mirroring.
 *
 *	reflect-x::
 *
 *			|o |    | o|
 *			|  | -> |  |
 *			| v|    |v |
 *
 *	reflect-y::
 *
 *			|o |    | ^|
 *			|  | -> |  |
 *			| v|    |o |
 *
 * zpos:
 *	Z position is set up with drm_plane_create_zpos_immutable_property() and
 *	drm_plane_create_zpos_property(). It controls the visibility of overlapping
 *	planes. Without this property the primary plane is always below the cursor
 *	plane, and ordering between all other planes is undefined. The positive
 *	Z axis poपूर्णांकs towards the user, i.e. planes with lower Z position values
 *	are underneath planes with higher Z position values. Two planes with the
 *	same Z position value have undefined ordering. Note that the Z position
 *	value can also be immutable, to inक्रमm userspace about the hard-coded
 *	stacking of planes, see drm_plane_create_zpos_immutable_property(). If
 *	any plane has a zpos property (either mutable or immutable), then all
 *	planes shall have a zpos property.
 *
 * pixel blend mode:
 *	Pixel blend mode is set up with drm_plane_create_blend_mode_property().
 *	It adds a blend mode क्रम alpha blending equation selection, describing
 *	how the pixels from the current plane are composited with the
 *	background.
 *
 *	 Three alpha blending equations are defined:
 *
 *	 "None":
 *		 Blend क्रमmula that ignores the pixel alpha::
 *
 *			 out.rgb = plane_alpha * fg.rgb +
 *				 (1 - plane_alpha) * bg.rgb
 *
 *	 "Pre-multiplied":
 *		 Blend क्रमmula that assumes the pixel color values
 *		 have been alपढ़ोy pre-multiplied with the alpha
 *		 channel values::
 *
 *			 out.rgb = plane_alpha * fg.rgb +
 *				 (1 - (plane_alpha * fg.alpha)) * bg.rgb
 *
 *	 "Coverage":
 *		 Blend क्रमmula that assumes the pixel color values have not
 *		 been pre-multiplied and will करो so when blending them to the
 *		 background color values::
 *
 *			 out.rgb = plane_alpha * fg.alpha * fg.rgb +
 *				 (1 - (plane_alpha * fg.alpha)) * bg.rgb
 *
 *	 Using the following symbols:
 *
 *	 "fg.rgb":
 *		 Each of the RGB component values from the plane's pixel
 *	 "fg.alpha":
 *		 Alpha component value from the plane's pixel. If the plane's
 *		 pixel क्रमmat has no alpha component, then this is assumed to be
 *		 1.0. In these हालs, this property has no effect, as all three
 *		 equations become equivalent.
 *	 "bg.rgb":
 *		 Each of the RGB component values from the background
 *	 "plane_alpha":
 *		 Plane alpha value set by the plane "alpha" property. If the
 *		 plane करोes not expose the "alpha" property, then this is
 *		 assumed to be 1.0
 *
 * Note that all the property extensions described here apply either to the
 * plane or the CRTC (e.g. क्रम the background color, which currently is not
 * exposed and assumed to be black).
 *
 * SCALING_FILTER:
 *     Indicates scaling filter to be used क्रम plane scaler
 *
 *     The value of this property can be one of the following:
 *
 *     Default:
 *             Driver's शेष scaling filter
 *     Nearest Neighbor:
 *             Nearest Neighbor scaling filter
 *
 * Drivers can set up this property क्रम a plane by calling
 * drm_plane_create_scaling_filter_property
 */

/**
 * drm_plane_create_alpha_property - create a new alpha property
 * @plane: drm plane
 *
 * This function creates a generic, mutable, alpha property and enables support
 * क्रम it in the DRM core. It is attached to @plane.
 *
 * The alpha property will be allowed to be within the bounds of 0
 * (transparent) to 0xffff (opaque).
 *
 * Returns:
 * 0 on success, negative error code on failure.
 */
पूर्णांक drm_plane_create_alpha_property(काष्ठा drm_plane *plane)
अणु
	काष्ठा drm_property *prop;

	prop = drm_property_create_range(plane->dev, 0, "alpha",
					 0, DRM_BLEND_ALPHA_OPAQUE);
	अगर (!prop)
		वापस -ENOMEM;

	drm_object_attach_property(&plane->base, prop, DRM_BLEND_ALPHA_OPAQUE);
	plane->alpha_property = prop;

	अगर (plane->state)
		plane->state->alpha = DRM_BLEND_ALPHA_OPAQUE;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_plane_create_alpha_property);

/**
 * drm_plane_create_rotation_property - create a new rotation property
 * @plane: drm plane
 * @rotation: initial value of the rotation property
 * @supported_rotations: biपंचांगask of supported rotations and reflections
 *
 * This creates a new property with the selected support क्रम transक्रमmations.
 *
 * Since a rotation by 180तओ degress is the same as reflecting both aदीर्घ the x
 * and the y axis the rotation property is somewhat redundant. Drivers can use
 * drm_rotation_simplअगरy() to normalize values of this property.
 *
 * The property exposed to userspace is a biपंचांगask property (see
 * drm_property_create_biपंचांगask()) called "rotation" and has the following
 * biपंचांगask क्रमागतaration values:
 *
 * DRM_MODE_ROTATE_0:
 * 	"rotate-0"
 * DRM_MODE_ROTATE_90:
 * 	"rotate-90"
 * DRM_MODE_ROTATE_180:
 * 	"rotate-180"
 * DRM_MODE_ROTATE_270:
 * 	"rotate-270"
 * DRM_MODE_REFLECT_X:
 * 	"reflect-x"
 * DRM_MODE_REFLECT_Y:
 * 	"reflect-y"
 *
 * Rotation is the specअगरied amount in degrees in counter घड़ीwise direction,
 * the X and Y axis are within the source rectangle, i.e.  the X/Y axis beक्रमe
 * rotation. After reflection, the rotation is applied to the image sampled from
 * the source rectangle, beक्रमe scaling it to fit the destination rectangle.
 */
पूर्णांक drm_plane_create_rotation_property(काष्ठा drm_plane *plane,
				       अचिन्हित पूर्णांक rotation,
				       अचिन्हित पूर्णांक supported_rotations)
अणु
	अटल स्थिर काष्ठा drm_prop_क्रमागत_list props[] = अणु
		अणु __builtin_ffs(DRM_MODE_ROTATE_0) - 1,   "rotate-0" पूर्ण,
		अणु __builtin_ffs(DRM_MODE_ROTATE_90) - 1,  "rotate-90" पूर्ण,
		अणु __builtin_ffs(DRM_MODE_ROTATE_180) - 1, "rotate-180" पूर्ण,
		अणु __builtin_ffs(DRM_MODE_ROTATE_270) - 1, "rotate-270" पूर्ण,
		अणु __builtin_ffs(DRM_MODE_REFLECT_X) - 1,  "reflect-x" पूर्ण,
		अणु __builtin_ffs(DRM_MODE_REFLECT_Y) - 1,  "reflect-y" पूर्ण,
	पूर्ण;
	काष्ठा drm_property *prop;

	WARN_ON((supported_rotations & DRM_MODE_ROTATE_MASK) == 0);
	WARN_ON(!is_घातer_of_2(rotation & DRM_MODE_ROTATE_MASK));
	WARN_ON(rotation & ~supported_rotations);

	prop = drm_property_create_biपंचांगask(plane->dev, 0, "rotation",
					   props, ARRAY_SIZE(props),
					   supported_rotations);
	अगर (!prop)
		वापस -ENOMEM;

	drm_object_attach_property(&plane->base, prop, rotation);

	अगर (plane->state)
		plane->state->rotation = rotation;

	plane->rotation_property = prop;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_plane_create_rotation_property);

/**
 * drm_rotation_simplअगरy() - Try to simplअगरy the rotation
 * @rotation: Rotation to be simplअगरied
 * @supported_rotations: Supported rotations
 *
 * Attempt to simplअगरy the rotation to a क्रमm that is supported.
 * Eg. अगर the hardware supports everything except DRM_MODE_REFLECT_X
 * one could call this function like this:
 *
 * drm_rotation_simplअगरy(rotation, DRM_MODE_ROTATE_0 |
 *                       DRM_MODE_ROTATE_90 | DRM_MODE_ROTATE_180 |
 *                       DRM_MODE_ROTATE_270 | DRM_MODE_REFLECT_Y);
 *
 * to eliminate the DRM_MODE_ROTATE_X flag. Depending on what kind of
 * transक्रमms the hardware supports, this function may not
 * be able to produce a supported transक्रमm, so the caller should
 * check the result afterwards.
 */
अचिन्हित पूर्णांक drm_rotation_simplअगरy(अचिन्हित पूर्णांक rotation,
				   अचिन्हित पूर्णांक supported_rotations)
अणु
	अगर (rotation & ~supported_rotations) अणु
		rotation ^= DRM_MODE_REFLECT_X | DRM_MODE_REFLECT_Y;
		rotation = (rotation & DRM_MODE_REFLECT_MASK) |
		           BIT((ffs(rotation & DRM_MODE_ROTATE_MASK) + 1)
		           % 4);
	पूर्ण

	वापस rotation;
पूर्ण
EXPORT_SYMBOL(drm_rotation_simplअगरy);

/**
 * drm_plane_create_zpos_property - create mutable zpos property
 * @plane: drm plane
 * @zpos: initial value of zpos property
 * @min: minimal possible value of zpos property
 * @max: maximal possible value of zpos property
 *
 * This function initializes generic mutable zpos property and enables support
 * क्रम it in drm core. Drivers can then attach this property to planes to enable
 * support क्रम configurable planes arrangement during blending operation.
 * Drivers that attach a mutable zpos property to any plane should call the
 * drm_atomic_normalize_zpos() helper during their implementation of
 * &drm_mode_config_funcs.atomic_check(), which will update the normalized zpos
 * values and store them in &drm_plane_state.normalized_zpos. Usually min
 * should be set to 0 and max to maximal number of planes क्रम given crtc - 1.
 *
 * If zpos of some planes cannot be changed (like fixed background or
 * cursor/topmost planes), drivers shall adjust the min/max values and assign
 * those planes immutable zpos properties with lower or higher values (क्रम more
 * inक्रमmation, see drm_plane_create_zpos_immutable_property() function). In such
 * हाल drivers shall also assign proper initial zpos values क्रम all planes in
 * its plane_reset() callback, so the planes will be always sorted properly.
 *
 * See also drm_atomic_normalize_zpos().
 *
 * The property exposed to userspace is called "zpos".
 *
 * Returns:
 * Zero on success, negative त्रुटि_सं on failure.
 */
पूर्णांक drm_plane_create_zpos_property(काष्ठा drm_plane *plane,
				   अचिन्हित पूर्णांक zpos,
				   अचिन्हित पूर्णांक min, अचिन्हित पूर्णांक max)
अणु
	काष्ठा drm_property *prop;

	prop = drm_property_create_range(plane->dev, 0, "zpos", min, max);
	अगर (!prop)
		वापस -ENOMEM;

	drm_object_attach_property(&plane->base, prop, zpos);

	plane->zpos_property = prop;

	अगर (plane->state) अणु
		plane->state->zpos = zpos;
		plane->state->normalized_zpos = zpos;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_plane_create_zpos_property);

/**
 * drm_plane_create_zpos_immutable_property - create immuttable zpos property
 * @plane: drm plane
 * @zpos: value of zpos property
 *
 * This function initializes generic immutable zpos property and enables
 * support क्रम it in drm core. Using this property driver lets userspace
 * to get the arrangement of the planes क्रम blending operation and notअगरies
 * it that the hardware (or driver) करोesn't support changing of the planes'
 * order. For mutable zpos see drm_plane_create_zpos_property().
 *
 * The property exposed to userspace is called "zpos".
 *
 * Returns:
 * Zero on success, negative त्रुटि_सं on failure.
 */
पूर्णांक drm_plane_create_zpos_immutable_property(काष्ठा drm_plane *plane,
					     अचिन्हित पूर्णांक zpos)
अणु
	काष्ठा drm_property *prop;

	prop = drm_property_create_range(plane->dev, DRM_MODE_PROP_IMMUTABLE,
					 "zpos", zpos, zpos);
	अगर (!prop)
		वापस -ENOMEM;

	drm_object_attach_property(&plane->base, prop, zpos);

	plane->zpos_property = prop;

	अगर (plane->state) अणु
		plane->state->zpos = zpos;
		plane->state->normalized_zpos = zpos;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_plane_create_zpos_immutable_property);

अटल पूर्णांक drm_atomic_state_zpos_cmp(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	स्थिर काष्ठा drm_plane_state *sa = *(काष्ठा drm_plane_state **)a;
	स्थिर काष्ठा drm_plane_state *sb = *(काष्ठा drm_plane_state **)b;

	अगर (sa->zpos != sb->zpos)
		वापस sa->zpos - sb->zpos;
	अन्यथा
		वापस sa->plane->base.id - sb->plane->base.id;
पूर्ण

अटल पूर्णांक drm_atomic_helper_crtc_normalize_zpos(काष्ठा drm_crtc *crtc,
					  काष्ठा drm_crtc_state *crtc_state)
अणु
	काष्ठा drm_atomic_state *state = crtc_state->state;
	काष्ठा drm_device *dev = crtc->dev;
	पूर्णांक total_planes = dev->mode_config.num_total_plane;
	काष्ठा drm_plane_state **states;
	काष्ठा drm_plane *plane;
	पूर्णांक i, n = 0;
	पूर्णांक ret = 0;

	DRM_DEBUG_ATOMIC("[CRTC:%d:%s] calculating normalized zpos values\n",
			 crtc->base.id, crtc->name);

	states = kदो_स्मृति_array(total_planes, माप(*states), GFP_KERNEL);
	अगर (!states)
		वापस -ENOMEM;

	/*
	 * Normalization process might create new states क्रम planes which
	 * normalized_zpos has to be recalculated.
	 */
	drm_क्रम_each_plane_mask(plane, dev, crtc_state->plane_mask) अणु
		काष्ठा drm_plane_state *plane_state =
			drm_atomic_get_plane_state(state, plane);
		अगर (IS_ERR(plane_state)) अणु
			ret = PTR_ERR(plane_state);
			जाओ करोne;
		पूर्ण
		states[n++] = plane_state;
		DRM_DEBUG_ATOMIC("[PLANE:%d:%s] processing zpos value %d\n",
				 plane->base.id, plane->name,
				 plane_state->zpos);
	पूर्ण

	sort(states, n, माप(*states), drm_atomic_state_zpos_cmp, शून्य);

	क्रम (i = 0; i < n; i++) अणु
		plane = states[i]->plane;

		states[i]->normalized_zpos = i;
		DRM_DEBUG_ATOMIC("[PLANE:%d:%s] normalized zpos value %d\n",
				 plane->base.id, plane->name, i);
	पूर्ण
	crtc_state->zpos_changed = true;

करोne:
	kमुक्त(states);
	वापस ret;
पूर्ण

/**
 * drm_atomic_normalize_zpos - calculate normalized zpos values क्रम all crtcs
 * @dev: DRM device
 * @state: atomic state of DRM device
 *
 * This function calculates normalized zpos value क्रम all modअगरied planes in
 * the provided atomic state of DRM device.
 *
 * For every CRTC this function checks new states of all planes asचिन्हित to
 * it and calculates normalized zpos value क्रम these planes. Planes are compared
 * first by their zpos values, then by plane id (अगर zpos is equal). The plane
 * with lowest zpos value is at the bottom. The &drm_plane_state.normalized_zpos
 * is then filled with unique values from 0 to number of active planes in crtc
 * minus one.
 *
 * RETURNS
 * Zero क्रम success or -त्रुटि_सं
 */
पूर्णांक drm_atomic_normalize_zpos(काष्ठा drm_device *dev,
			      काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_crtc_state *old_crtc_state, *new_crtc_state;
	काष्ठा drm_plane *plane;
	काष्ठा drm_plane_state *old_plane_state, *new_plane_state;
	पूर्णांक i, ret = 0;

	क्रम_each_oldnew_plane_in_state(state, plane, old_plane_state, new_plane_state, i) अणु
		crtc = new_plane_state->crtc;
		अगर (!crtc)
			जारी;
		अगर (old_plane_state->zpos != new_plane_state->zpos) अणु
			new_crtc_state = drm_atomic_get_new_crtc_state(state, crtc);
			new_crtc_state->zpos_changed = true;
		पूर्ण
	पूर्ण

	क्रम_each_oldnew_crtc_in_state(state, crtc, old_crtc_state, new_crtc_state, i) अणु
		अगर (old_crtc_state->plane_mask != new_crtc_state->plane_mask ||
		    new_crtc_state->zpos_changed) अणु
			ret = drm_atomic_helper_crtc_normalize_zpos(crtc,
								    new_crtc_state);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_atomic_normalize_zpos);

/**
 * drm_plane_create_blend_mode_property - create a new blend mode property
 * @plane: drm plane
 * @supported_modes: biपंचांगask of supported modes, must include
 *		     BIT(DRM_MODE_BLEND_PREMULTI). Current DRM assumption is
 *		     that alpha is premultiplied, and old userspace can अवरोध अगर
 *		     the property शेषs to anything अन्यथा.
 *
 * This creates a new property describing the blend mode.
 *
 * The property exposed to userspace is an क्रमागतeration property (see
 * drm_property_create_क्रमागत()) called "pixel blend mode" and has the
 * following क्रमागतeration values:
 *
 * "None":
 *	Blend क्रमmula that ignores the pixel alpha.
 *
 * "Pre-multiplied":
 *	Blend क्रमmula that assumes the pixel color values have been alपढ़ोy
 *	pre-multiplied with the alpha channel values.
 *
 * "Coverage":
 *	Blend क्रमmula that assumes the pixel color values have not been
 *	pre-multiplied and will करो so when blending them to the background color
 *	values.
 *
 * RETURNS:
 * Zero क्रम success or -त्रुटि_सं
 */
पूर्णांक drm_plane_create_blend_mode_property(काष्ठा drm_plane *plane,
					 अचिन्हित पूर्णांक supported_modes)
अणु
	काष्ठा drm_device *dev = plane->dev;
	काष्ठा drm_property *prop;
	अटल स्थिर काष्ठा drm_prop_क्रमागत_list props[] = अणु
		अणु DRM_MODE_BLEND_PIXEL_NONE, "None" पूर्ण,
		अणु DRM_MODE_BLEND_PREMULTI, "Pre-multiplied" पूर्ण,
		अणु DRM_MODE_BLEND_COVERAGE, "Coverage" पूर्ण,
	पूर्ण;
	अचिन्हित पूर्णांक valid_mode_mask = BIT(DRM_MODE_BLEND_PIXEL_NONE) |
				       BIT(DRM_MODE_BLEND_PREMULTI)   |
				       BIT(DRM_MODE_BLEND_COVERAGE);
	पूर्णांक i;

	अगर (WARN_ON((supported_modes & ~valid_mode_mask) ||
		    ((supported_modes & BIT(DRM_MODE_BLEND_PREMULTI)) == 0)))
		वापस -EINVAL;

	prop = drm_property_create(dev, DRM_MODE_PROP_ENUM,
				   "pixel blend mode",
				   hweight32(supported_modes));
	अगर (!prop)
		वापस -ENOMEM;

	क्रम (i = 0; i < ARRAY_SIZE(props); i++) अणु
		पूर्णांक ret;

		अगर (!(BIT(props[i].type) & supported_modes))
			जारी;

		ret = drm_property_add_क्रमागत(prop, props[i].type,
					    props[i].name);

		अगर (ret) अणु
			drm_property_destroy(dev, prop);

			वापस ret;
		पूर्ण
	पूर्ण

	drm_object_attach_property(&plane->base, prop, DRM_MODE_BLEND_PREMULTI);
	plane->blend_mode_property = prop;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_plane_create_blend_mode_property);
