<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * (C) COPYRIGHT 2018 ARM Limited. All rights reserved.
 * Author: James.Qian.Wang <james.qian.wang@arm.com>
 *
 */
#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_plane_helper.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश "komeda_dev.h"
#समावेश "komeda_kms.h"
#समावेश "komeda_framebuffer.h"

अटल पूर्णांक
komeda_plane_init_data_flow(काष्ठा drm_plane_state *st,
			    काष्ठा komeda_crtc_state *kcrtc_st,
			    काष्ठा komeda_data_flow_cfg *dflow)
अणु
	काष्ठा komeda_plane *kplane = to_kplane(st->plane);
	काष्ठा drm_framebuffer *fb = st->fb;
	स्थिर काष्ठा komeda_क्रमmat_caps *caps = to_kfb(fb)->क्रमmat_caps;
	काष्ठा komeda_pipeline *pipe = kplane->layer->base.pipeline;

	स_रखो(dflow, 0, माप(*dflow));

	dflow->blending_zorder = st->normalized_zpos;
	अगर (pipe == to_kcrtc(st->crtc)->master)
		dflow->blending_zorder -= kcrtc_st->max_slave_zorder;
	अगर (dflow->blending_zorder < 0) अणु
		DRM_DEBUG_ATOMIC("%s zorder:%d < max_slave_zorder: %d.\n",
				 st->plane->name, st->normalized_zpos,
				 kcrtc_st->max_slave_zorder);
		वापस -EINVAL;
	पूर्ण

	dflow->pixel_blend_mode = st->pixel_blend_mode;
	dflow->layer_alpha = st->alpha >> 8;

	dflow->out_x = st->crtc_x;
	dflow->out_y = st->crtc_y;
	dflow->out_w = st->crtc_w;
	dflow->out_h = st->crtc_h;

	dflow->in_x = st->src_x >> 16;
	dflow->in_y = st->src_y >> 16;
	dflow->in_w = st->src_w >> 16;
	dflow->in_h = st->src_h >> 16;

	dflow->rot = drm_rotation_simplअगरy(st->rotation, caps->supported_rots);
	अगर (!has_bits(dflow->rot, caps->supported_rots)) अणु
		DRM_DEBUG_ATOMIC("rotation(0x%x) isn't supported by %p4cc with modifier: 0x%llx.\n",
				 dflow->rot, &caps->fourcc, fb->modअगरier);
		वापस -EINVAL;
	पूर्ण

	komeda_complete_data_flow_cfg(kplane->layer, dflow, fb);

	वापस 0;
पूर्ण

/**
 * komeda_plane_atomic_check - build input data flow
 * @plane: DRM plane
 * @state: the plane state object
 *
 * RETURNS:
 * Zero क्रम success or -त्रुटि_सं
 */
अटल पूर्णांक
komeda_plane_atomic_check(काष्ठा drm_plane *plane,
			  काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_plane_state = drm_atomic_get_new_plane_state(state,
										 plane);
	काष्ठा komeda_plane *kplane = to_kplane(plane);
	काष्ठा komeda_plane_state *kplane_st = to_kplane_st(new_plane_state);
	काष्ठा komeda_layer *layer = kplane->layer;
	काष्ठा drm_crtc_state *crtc_st;
	काष्ठा komeda_crtc_state *kcrtc_st;
	काष्ठा komeda_data_flow_cfg dflow;
	पूर्णांक err;

	अगर (!new_plane_state->crtc || !new_plane_state->fb)
		वापस 0;

	crtc_st = drm_atomic_get_crtc_state(state,
					    new_plane_state->crtc);
	अगर (IS_ERR(crtc_st) || !crtc_st->enable) अणु
		DRM_DEBUG_ATOMIC("Cannot update plane on a disabled CRTC.\n");
		वापस -EINVAL;
	पूर्ण

	/* crtc is inactive, skip the resource assignment */
	अगर (!crtc_st->active)
		वापस 0;

	kcrtc_st = to_kcrtc_st(crtc_st);

	err = komeda_plane_init_data_flow(new_plane_state, kcrtc_st, &dflow);
	अगर (err)
		वापस err;

	अगर (dflow.en_split)
		err = komeda_build_layer_split_data_flow(layer,
				kplane_st, kcrtc_st, &dflow);
	अन्यथा
		err = komeda_build_layer_data_flow(layer,
				kplane_st, kcrtc_st, &dflow);

	वापस err;
पूर्ण

/* plane करोesn't represent a real HW, so there is no HW update क्रम plane.
 * komeda handles all the HW update in crtc->atomic_flush
 */
अटल व्योम
komeda_plane_atomic_update(काष्ठा drm_plane *plane,
			   काष्ठा drm_atomic_state *state)
अणु
पूर्ण

अटल स्थिर काष्ठा drm_plane_helper_funcs komeda_plane_helper_funcs = अणु
	.atomic_check	= komeda_plane_atomic_check,
	.atomic_update	= komeda_plane_atomic_update,
पूर्ण;

अटल व्योम komeda_plane_destroy(काष्ठा drm_plane *plane)
अणु
	drm_plane_cleanup(plane);

	kमुक्त(to_kplane(plane));
पूर्ण

अटल व्योम komeda_plane_reset(काष्ठा drm_plane *plane)
अणु
	काष्ठा komeda_plane_state *state;
	काष्ठा komeda_plane *kplane = to_kplane(plane);

	अगर (plane->state)
		__drm_atomic_helper_plane_destroy_state(plane->state);

	kमुक्त(plane->state);
	plane->state = शून्य;

	state = kzalloc(माप(*state), GFP_KERNEL);
	अगर (state) अणु
		state->base.rotation = DRM_MODE_ROTATE_0;
		state->base.pixel_blend_mode = DRM_MODE_BLEND_PREMULTI;
		state->base.alpha = DRM_BLEND_ALPHA_OPAQUE;
		state->base.zpos = kplane->layer->base.id;
		state->base.color_encoding = DRM_COLOR_YCBCR_BT601;
		state->base.color_range = DRM_COLOR_YCBCR_LIMITED_RANGE;
		plane->state = &state->base;
		plane->state->plane = plane;
	पूर्ण
पूर्ण

अटल काष्ठा drm_plane_state *
komeda_plane_atomic_duplicate_state(काष्ठा drm_plane *plane)
अणु
	काष्ठा komeda_plane_state *new;

	अगर (WARN_ON(!plane->state))
		वापस शून्य;

	new = kzalloc(माप(*new), GFP_KERNEL);
	अगर (!new)
		वापस शून्य;

	__drm_atomic_helper_plane_duplicate_state(plane, &new->base);

	वापस &new->base;
पूर्ण

अटल व्योम
komeda_plane_atomic_destroy_state(काष्ठा drm_plane *plane,
				  काष्ठा drm_plane_state *state)
अणु
	__drm_atomic_helper_plane_destroy_state(state);
	kमुक्त(to_kplane_st(state));
पूर्ण

अटल bool
komeda_plane_क्रमmat_mod_supported(काष्ठा drm_plane *plane,
				  u32 क्रमmat, u64 modअगरier)
अणु
	काष्ठा komeda_dev *mdev = plane->dev->dev_निजी;
	काष्ठा komeda_plane *kplane = to_kplane(plane);
	u32 layer_type = kplane->layer->layer_type;

	वापस komeda_क्रमmat_mod_supported(&mdev->fmt_tbl, layer_type,
					   क्रमmat, modअगरier, 0);
पूर्ण

अटल स्थिर काष्ठा drm_plane_funcs komeda_plane_funcs = अणु
	.update_plane		= drm_atomic_helper_update_plane,
	.disable_plane		= drm_atomic_helper_disable_plane,
	.destroy		= komeda_plane_destroy,
	.reset			= komeda_plane_reset,
	.atomic_duplicate_state	= komeda_plane_atomic_duplicate_state,
	.atomic_destroy_state	= komeda_plane_atomic_destroy_state,
	.क्रमmat_mod_supported	= komeda_plane_क्रमmat_mod_supported,
पूर्ण;

/* क्रम komeda, which is pipeline can be share between crtcs */
अटल u32 get_possible_crtcs(काष्ठा komeda_kms_dev *kms,
			      काष्ठा komeda_pipeline *pipe)
अणु
	काष्ठा komeda_crtc *crtc;
	u32 possible_crtcs = 0;
	पूर्णांक i;

	क्रम (i = 0; i < kms->n_crtcs; i++) अणु
		crtc = &kms->crtcs[i];

		अगर ((pipe == crtc->master) || (pipe == crtc->slave))
			possible_crtcs |= BIT(i);
	पूर्ण

	वापस possible_crtcs;
पूर्ण

अटल व्योम
komeda_set_crtc_plane_mask(काष्ठा komeda_kms_dev *kms,
			   काष्ठा komeda_pipeline *pipe,
			   काष्ठा drm_plane *plane)
अणु
	काष्ठा komeda_crtc *kcrtc;
	पूर्णांक i;

	क्रम (i = 0; i < kms->n_crtcs; i++) अणु
		kcrtc = &kms->crtcs[i];

		अगर (pipe == kcrtc->slave)
			kcrtc->slave_planes |= BIT(drm_plane_index(plane));
	पूर्ण
पूर्ण

/* use Layer0 as primary */
अटल u32 get_plane_type(काष्ठा komeda_kms_dev *kms,
			  काष्ठा komeda_component *c)
अणु
	bool is_primary = (c->id == KOMEDA_COMPONENT_LAYER0);

	वापस is_primary ? DRM_PLANE_TYPE_PRIMARY : DRM_PLANE_TYPE_OVERLAY;
पूर्ण

अटल पूर्णांक komeda_plane_add(काष्ठा komeda_kms_dev *kms,
			    काष्ठा komeda_layer *layer)
अणु
	काष्ठा komeda_dev *mdev = kms->base.dev_निजी;
	काष्ठा komeda_component *c = &layer->base;
	काष्ठा komeda_plane *kplane;
	काष्ठा drm_plane *plane;
	u32 *क्रमmats, n_क्रमmats = 0;
	पूर्णांक err;

	kplane = kzalloc(माप(*kplane), GFP_KERNEL);
	अगर (!kplane)
		वापस -ENOMEM;

	plane = &kplane->base;
	kplane->layer = layer;

	क्रमmats = komeda_get_layer_fourcc_list(&mdev->fmt_tbl,
					       layer->layer_type, &n_क्रमmats);

	err = drm_universal_plane_init(&kms->base, plane,
			get_possible_crtcs(kms, c->pipeline),
			&komeda_plane_funcs,
			क्रमmats, n_क्रमmats, komeda_supported_modअगरiers,
			get_plane_type(kms, c),
			"%s", c->name);

	komeda_put_fourcc_list(क्रमmats);

	अगर (err)
		जाओ cleanup;

	drm_plane_helper_add(plane, &komeda_plane_helper_funcs);

	err = drm_plane_create_rotation_property(plane, DRM_MODE_ROTATE_0,
						 layer->supported_rots);
	अगर (err)
		जाओ cleanup;

	err = drm_plane_create_alpha_property(plane);
	अगर (err)
		जाओ cleanup;

	err = drm_plane_create_blend_mode_property(plane,
			BIT(DRM_MODE_BLEND_PIXEL_NONE) |
			BIT(DRM_MODE_BLEND_PREMULTI)   |
			BIT(DRM_MODE_BLEND_COVERAGE));
	अगर (err)
		जाओ cleanup;

	err = drm_plane_create_color_properties(plane,
			BIT(DRM_COLOR_YCBCR_BT601) |
			BIT(DRM_COLOR_YCBCR_BT709) |
			BIT(DRM_COLOR_YCBCR_BT2020),
			BIT(DRM_COLOR_YCBCR_LIMITED_RANGE) |
			BIT(DRM_COLOR_YCBCR_FULL_RANGE),
			DRM_COLOR_YCBCR_BT601,
			DRM_COLOR_YCBCR_LIMITED_RANGE);
	अगर (err)
		जाओ cleanup;

	err = drm_plane_create_zpos_property(plane, layer->base.id, 0, 8);
	अगर (err)
		जाओ cleanup;

	komeda_set_crtc_plane_mask(kms, c->pipeline, plane);

	वापस 0;
cleanup:
	komeda_plane_destroy(plane);
	वापस err;
पूर्ण

पूर्णांक komeda_kms_add_planes(काष्ठा komeda_kms_dev *kms, काष्ठा komeda_dev *mdev)
अणु
	काष्ठा komeda_pipeline *pipe;
	पूर्णांक i, j, err;

	क्रम (i = 0; i < mdev->n_pipelines; i++) अणु
		pipe = mdev->pipelines[i];

		क्रम (j = 0; j < pipe->n_layers; j++) अणु
			err = komeda_plane_add(kms, pipe->layers[j]);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
