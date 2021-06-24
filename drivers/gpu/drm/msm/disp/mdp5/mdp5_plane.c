<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2014-2015 The Linux Foundation. All rights reserved.
 * Copyright (C) 2013 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 */

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_damage_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "mdp5_kms.h"

काष्ठा mdp5_plane अणु
	काष्ठा drm_plane base;

	uपूर्णांक32_t nक्रमmats;
	uपूर्णांक32_t क्रमmats[32];
पूर्ण;
#घोषणा to_mdp5_plane(x) container_of(x, काष्ठा mdp5_plane, base)

अटल पूर्णांक mdp5_plane_mode_set(काष्ठा drm_plane *plane,
		काष्ठा drm_crtc *crtc, काष्ठा drm_framebuffer *fb,
		काष्ठा drm_rect *src, काष्ठा drm_rect *dest);

अटल काष्ठा mdp5_kms *get_kms(काष्ठा drm_plane *plane)
अणु
	काष्ठा msm_drm_निजी *priv = plane->dev->dev_निजी;
	वापस to_mdp5_kms(to_mdp_kms(priv->kms));
पूर्ण

अटल bool plane_enabled(काष्ठा drm_plane_state *state)
अणु
	वापस state->visible;
पूर्ण

अटल व्योम mdp5_plane_destroy(काष्ठा drm_plane *plane)
अणु
	काष्ठा mdp5_plane *mdp5_plane = to_mdp5_plane(plane);

	drm_plane_cleanup(plane);

	kमुक्त(mdp5_plane);
पूर्ण

अटल व्योम mdp5_plane_install_rotation_property(काष्ठा drm_device *dev,
		काष्ठा drm_plane *plane)
अणु
	drm_plane_create_rotation_property(plane,
					   DRM_MODE_ROTATE_0,
					   DRM_MODE_ROTATE_0 |
					   DRM_MODE_ROTATE_180 |
					   DRM_MODE_REFLECT_X |
					   DRM_MODE_REFLECT_Y);
पूर्ण

/* helper to install properties which are common to planes and crtcs */
अटल व्योम mdp5_plane_install_properties(काष्ठा drm_plane *plane,
		काष्ठा drm_mode_object *obj)
अणु
	काष्ठा drm_device *dev = plane->dev;
	काष्ठा msm_drm_निजी *dev_priv = dev->dev_निजी;
	काष्ठा drm_property *prop;

#घोषणा INSTALL_PROPERTY(name, NAME, init_val, fnc, ...) करो अणु \
		prop = dev_priv->plane_property[PLANE_PROP_##NAME]; \
		अगर (!prop) अणु \
			prop = drm_property_##fnc(dev, 0, #name, \
				##__VA_ARGS__); \
			अगर (!prop) अणु \
				dev_warn(dev->dev, \
					"Create property %s failed\n", \
					#name); \
				वापस; \
			पूर्ण \
			dev_priv->plane_property[PLANE_PROP_##NAME] = prop; \
		पूर्ण \
		drm_object_attach_property(&plane->base, prop, init_val); \
	पूर्ण जबतक (0)

#घोषणा INSTALL_RANGE_PROPERTY(name, NAME, min, max, init_val) \
		INSTALL_PROPERTY(name, NAME, init_val, \
				create_range, min, max)

#घोषणा INSTALL_ENUM_PROPERTY(name, NAME, init_val) \
		INSTALL_PROPERTY(name, NAME, init_val, \
				create_क्रमागत, name##_prop_क्रमागत_list, \
				ARRAY_SIZE(name##_prop_क्रमागत_list))

	INSTALL_RANGE_PROPERTY(zpos, ZPOS, 1, 255, 1);

	mdp5_plane_install_rotation_property(dev, plane);

#अघोषित INSTALL_RANGE_PROPERTY
#अघोषित INSTALL_ENUM_PROPERTY
#अघोषित INSTALL_PROPERTY
पूर्ण

अटल पूर्णांक mdp5_plane_atomic_set_property(काष्ठा drm_plane *plane,
		काष्ठा drm_plane_state *state, काष्ठा drm_property *property,
		uपूर्णांक64_t val)
अणु
	काष्ठा drm_device *dev = plane->dev;
	काष्ठा mdp5_plane_state *pstate;
	काष्ठा msm_drm_निजी *dev_priv = dev->dev_निजी;
	पूर्णांक ret = 0;

	pstate = to_mdp5_plane_state(state);

#घोषणा SET_PROPERTY(name, NAME, type) करो अणु \
		अगर (dev_priv->plane_property[PLANE_PROP_##NAME] == property) अणु \
			pstate->name = (type)val; \
			DBG("Set property %s %d", #name, (type)val); \
			जाओ करोne; \
		पूर्ण \
	पूर्ण जबतक (0)

	SET_PROPERTY(zpos, ZPOS, uपूर्णांक8_t);

	DRM_DEV_ERROR(dev->dev, "Invalid property\n");
	ret = -EINVAL;
करोne:
	वापस ret;
#अघोषित SET_PROPERTY
पूर्ण

अटल पूर्णांक mdp5_plane_atomic_get_property(काष्ठा drm_plane *plane,
		स्थिर काष्ठा drm_plane_state *state,
		काष्ठा drm_property *property, uपूर्णांक64_t *val)
अणु
	काष्ठा drm_device *dev = plane->dev;
	काष्ठा mdp5_plane_state *pstate;
	काष्ठा msm_drm_निजी *dev_priv = dev->dev_निजी;
	पूर्णांक ret = 0;

	pstate = to_mdp5_plane_state(state);

#घोषणा GET_PROPERTY(name, NAME, type) करो अणु \
		अगर (dev_priv->plane_property[PLANE_PROP_##NAME] == property) अणु \
			*val = pstate->name; \
			DBG("Get property %s %lld", #name, *val); \
			जाओ करोne; \
		पूर्ण \
	पूर्ण जबतक (0)

	GET_PROPERTY(zpos, ZPOS, uपूर्णांक8_t);

	DRM_DEV_ERROR(dev->dev, "Invalid property\n");
	ret = -EINVAL;
करोne:
	वापस ret;
#अघोषित SET_PROPERTY
पूर्ण

अटल व्योम
mdp5_plane_atomic_prपूर्णांक_state(काष्ठा drm_prपूर्णांकer *p,
		स्थिर काष्ठा drm_plane_state *state)
अणु
	काष्ठा mdp5_plane_state *pstate = to_mdp5_plane_state(state);
	काष्ठा mdp5_kms *mdp5_kms = get_kms(state->plane);

	drm_म_लिखो(p, "\thwpipe=%s\n", pstate->hwpipe ?
			pstate->hwpipe->name : "(null)");
	अगर (mdp5_kms->caps & MDP_CAP_SRC_SPLIT)
		drm_म_लिखो(p, "\tright-hwpipe=%s\n",
			   pstate->r_hwpipe ? pstate->r_hwpipe->name :
					      "(null)");
	drm_म_लिखो(p, "\tpremultiplied=%u\n", pstate->premultiplied);
	drm_म_लिखो(p, "\tzpos=%u\n", pstate->zpos);
	drm_म_लिखो(p, "\talpha=%u\n", pstate->alpha);
	drm_म_लिखो(p, "\tstage=%s\n", stage2name(pstate->stage));
पूर्ण

अटल व्योम mdp5_plane_reset(काष्ठा drm_plane *plane)
अणु
	काष्ठा mdp5_plane_state *mdp5_state;

	अगर (plane->state && plane->state->fb)
		drm_framebuffer_put(plane->state->fb);

	kमुक्त(to_mdp5_plane_state(plane->state));
	mdp5_state = kzalloc(माप(*mdp5_state), GFP_KERNEL);

	/* assign शेष blend parameters */
	mdp5_state->alpha = 255;
	mdp5_state->premultiplied = 0;

	अगर (plane->type == DRM_PLANE_TYPE_PRIMARY)
		mdp5_state->zpos = STAGE_BASE;
	अन्यथा
		mdp5_state->zpos = STAGE0 + drm_plane_index(plane);

	mdp5_state->base.plane = plane;

	plane->state = &mdp5_state->base;
पूर्ण

अटल काष्ठा drm_plane_state *
mdp5_plane_duplicate_state(काष्ठा drm_plane *plane)
अणु
	काष्ठा mdp5_plane_state *mdp5_state;

	अगर (WARN_ON(!plane->state))
		वापस शून्य;

	mdp5_state = kmemdup(to_mdp5_plane_state(plane->state),
			माप(*mdp5_state), GFP_KERNEL);
	अगर (!mdp5_state)
		वापस शून्य;

	__drm_atomic_helper_plane_duplicate_state(plane, &mdp5_state->base);

	वापस &mdp5_state->base;
पूर्ण

अटल व्योम mdp5_plane_destroy_state(काष्ठा drm_plane *plane,
		काष्ठा drm_plane_state *state)
अणु
	काष्ठा mdp5_plane_state *pstate = to_mdp5_plane_state(state);

	अगर (state->fb)
		drm_framebuffer_put(state->fb);

	kमुक्त(pstate);
पूर्ण

अटल स्थिर काष्ठा drm_plane_funcs mdp5_plane_funcs = अणु
		.update_plane = drm_atomic_helper_update_plane,
		.disable_plane = drm_atomic_helper_disable_plane,
		.destroy = mdp5_plane_destroy,
		.atomic_set_property = mdp5_plane_atomic_set_property,
		.atomic_get_property = mdp5_plane_atomic_get_property,
		.reset = mdp5_plane_reset,
		.atomic_duplicate_state = mdp5_plane_duplicate_state,
		.atomic_destroy_state = mdp5_plane_destroy_state,
		.atomic_prपूर्णांक_state = mdp5_plane_atomic_prपूर्णांक_state,
पूर्ण;

अटल व्योम mdp5_plane_cleanup_fb(काष्ठा drm_plane *plane,
				  काष्ठा drm_plane_state *old_state)
अणु
	काष्ठा mdp5_kms *mdp5_kms = get_kms(plane);
	काष्ठा msm_kms *kms = &mdp5_kms->base.base;
	काष्ठा drm_framebuffer *fb = old_state->fb;

	अगर (!fb)
		वापस;

	DBG("%s: cleanup: FB[%u]", plane->name, fb->base.id);
	msm_framebuffer_cleanup(fb, kms->aspace);
पूर्ण

अटल पूर्णांक mdp5_plane_atomic_check_with_state(काष्ठा drm_crtc_state *crtc_state,
					      काष्ठा drm_plane_state *state)
अणु
	काष्ठा mdp5_plane_state *mdp5_state = to_mdp5_plane_state(state);
	काष्ठा drm_plane *plane = state->plane;
	काष्ठा drm_plane_state *old_state = plane->state;
	काष्ठा mdp5_cfg *config = mdp5_cfg_get_config(get_kms(plane)->cfg);
	bool new_hwpipe = false;
	bool need_right_hwpipe = false;
	uपूर्णांक32_t max_width, max_height;
	bool out_of_bounds = false;
	uपूर्णांक32_t caps = 0;
	पूर्णांक min_scale, max_scale;
	पूर्णांक ret;

	DBG("%s: check (%d -> %d)", plane->name,
			plane_enabled(old_state), plane_enabled(state));

	max_width = config->hw->lm.max_width << 16;
	max_height = config->hw->lm.max_height << 16;

	/* Make sure source dimensions are within bounds. */
	अगर (state->src_h > max_height)
		out_of_bounds = true;

	अगर (state->src_w > max_width) अणु
		/* If source split is supported, we can go up to 2x
		 * the max LM width, but we'd need to stage another
		 * hwpipe to the right LM. So, the drm_plane would
		 * consist of 2 hwpipes.
		 */
		अगर (config->hw->mdp.caps & MDP_CAP_SRC_SPLIT &&
		    (state->src_w <= 2 * max_width))
			need_right_hwpipe = true;
		अन्यथा
			out_of_bounds = true;
	पूर्ण

	अगर (out_of_bounds) अणु
		काष्ठा drm_rect src = drm_plane_state_src(state);
		DBG("Invalid source size "DRM_RECT_FP_FMT,
				DRM_RECT_FP_ARG(&src));
		वापस -दुस्फल;
	पूर्ण

	min_scale = FRAC_16_16(1, 8);
	max_scale = FRAC_16_16(8, 1);

	ret = drm_atomic_helper_check_plane_state(state, crtc_state,
						  min_scale, max_scale,
						  true, true);
	अगर (ret)
		वापस ret;

	अगर (plane_enabled(state)) अणु
		अचिन्हित पूर्णांक rotation;
		स्थिर काष्ठा mdp_क्रमmat *क्रमmat;
		काष्ठा mdp5_kms *mdp5_kms = get_kms(plane);
		uपूर्णांक32_t blkcfg = 0;

		क्रमmat = to_mdp_क्रमmat(msm_framebuffer_क्रमmat(state->fb));
		अगर (MDP_FORMAT_IS_YUV(क्रमmat))
			caps |= MDP_PIPE_CAP_SCALE | MDP_PIPE_CAP_CSC;

		अगर (((state->src_w >> 16) != state->crtc_w) ||
				((state->src_h >> 16) != state->crtc_h))
			caps |= MDP_PIPE_CAP_SCALE;

		rotation = drm_rotation_simplअगरy(state->rotation,
						 DRM_MODE_ROTATE_0 |
						 DRM_MODE_REFLECT_X |
						 DRM_MODE_REFLECT_Y);

		अगर (rotation & DRM_MODE_REFLECT_X)
			caps |= MDP_PIPE_CAP_HFLIP;

		अगर (rotation & DRM_MODE_REFLECT_Y)
			caps |= MDP_PIPE_CAP_VFLIP;

		अगर (plane->type == DRM_PLANE_TYPE_CURSOR)
			caps |= MDP_PIPE_CAP_CURSOR;

		/* (re)allocate hw pipe अगर we करोn't have one or caps-mismatch: */
		अगर (!mdp5_state->hwpipe || (caps & ~mdp5_state->hwpipe->caps))
			new_hwpipe = true;

		/*
		 * (re)allocte hw pipe अगर we're either requesting क्रम 2 hw pipes
		 * or we're चयनing from 2 hw pipes to 1 hw pipe because the
		 * new src_w can be supported by 1 hw pipe itself.
		 */
		अगर ((need_right_hwpipe && !mdp5_state->r_hwpipe) ||
		    (!need_right_hwpipe && mdp5_state->r_hwpipe))
			new_hwpipe = true;

		अगर (mdp5_kms->smp) अणु
			स्थिर काष्ठा mdp_क्रमmat *क्रमmat =
				to_mdp_क्रमmat(msm_framebuffer_क्रमmat(state->fb));

			blkcfg = mdp5_smp_calculate(mdp5_kms->smp, क्रमmat,
					state->src_w >> 16, false);

			अगर (mdp5_state->hwpipe && (mdp5_state->hwpipe->blkcfg != blkcfg))
				new_hwpipe = true;
		पूर्ण

		/* (re)assign hwpipe अगर needed, otherwise keep old one: */
		अगर (new_hwpipe) अणु
			/* TODO maybe we want to re-assign hwpipe someबार
			 * in हालs when we no-दीर्घer need some caps to make
			 * it available क्रम other planes?
			 */
			काष्ठा mdp5_hw_pipe *old_hwpipe = mdp5_state->hwpipe;
			काष्ठा mdp5_hw_pipe *old_right_hwpipe =
							  mdp5_state->r_hwpipe;
			काष्ठा mdp5_hw_pipe *new_hwpipe = शून्य;
			काष्ठा mdp5_hw_pipe *new_right_hwpipe = शून्य;

			ret = mdp5_pipe_assign(state->state, plane, caps,
					       blkcfg, &new_hwpipe,
					       need_right_hwpipe ?
					       &new_right_hwpipe : शून्य);
			अगर (ret) अणु
				DBG("%s: failed to assign hwpipe(s)!",
				    plane->name);
				वापस ret;
			पूर्ण

			mdp5_state->hwpipe = new_hwpipe;
			अगर (need_right_hwpipe)
				mdp5_state->r_hwpipe = new_right_hwpipe;
			अन्यथा
				/*
				 * set it to शून्य so that the driver knows we
				 * करोn't have a right hwpipe when committing a
				 * new state
				 */
				mdp5_state->r_hwpipe = शून्य;


			mdp5_pipe_release(state->state, old_hwpipe);
			mdp5_pipe_release(state->state, old_right_hwpipe);
		पूर्ण
	पूर्ण अन्यथा अणु
		mdp5_pipe_release(state->state, mdp5_state->hwpipe);
		mdp5_pipe_release(state->state, mdp5_state->r_hwpipe);
		mdp5_state->hwpipe = mdp5_state->r_hwpipe = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mdp5_plane_atomic_check(काष्ठा drm_plane *plane,
				   काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *old_plane_state = drm_atomic_get_old_plane_state(state,
										 plane);
	काष्ठा drm_plane_state *new_plane_state = drm_atomic_get_new_plane_state(state,
										 plane);
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_crtc_state *crtc_state;

	crtc = new_plane_state->crtc ? new_plane_state->crtc : old_plane_state->crtc;
	अगर (!crtc)
		वापस 0;

	crtc_state = drm_atomic_get_existing_crtc_state(state,
							crtc);
	अगर (WARN_ON(!crtc_state))
		वापस -EINVAL;

	वापस mdp5_plane_atomic_check_with_state(crtc_state, new_plane_state);
पूर्ण

अटल व्योम mdp5_plane_atomic_update(काष्ठा drm_plane *plane,
				     काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_state = drm_atomic_get_new_plane_state(state,
									   plane);

	DBG("%s: update", plane->name);

	अगर (plane_enabled(new_state)) अणु
		पूर्णांक ret;

		ret = mdp5_plane_mode_set(plane,
				new_state->crtc, new_state->fb,
				&new_state->src, &new_state->dst);
		/* atomic_check should have ensured that this करोesn't fail */
		WARN_ON(ret < 0);
	पूर्ण
पूर्ण

अटल पूर्णांक mdp5_plane_atomic_async_check(काष्ठा drm_plane *plane,
					 काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_plane_state = drm_atomic_get_new_plane_state(state,
										 plane);
	काष्ठा mdp5_plane_state *mdp5_state = to_mdp5_plane_state(new_plane_state);
	काष्ठा drm_crtc_state *crtc_state;
	पूर्णांक min_scale, max_scale;
	पूर्णांक ret;

	crtc_state = drm_atomic_get_existing_crtc_state(state,
							new_plane_state->crtc);
	अगर (WARN_ON(!crtc_state))
		वापस -EINVAL;

	अगर (!crtc_state->active)
		वापस -EINVAL;

	mdp5_state = to_mdp5_plane_state(new_plane_state);

	/* करोn't use fast path if we don't have a hwpipe allocated yet */
	अगर (!mdp5_state->hwpipe)
		वापस -EINVAL;

	/* only allow changing of position(crtc x/y or src x/y) in fast path */
	अगर (plane->state->crtc != new_plane_state->crtc ||
	    plane->state->src_w != new_plane_state->src_w ||
	    plane->state->src_h != new_plane_state->src_h ||
	    plane->state->crtc_w != new_plane_state->crtc_w ||
	    plane->state->crtc_h != new_plane_state->crtc_h ||
	    !plane->state->fb ||
	    plane->state->fb != new_plane_state->fb)
		वापस -EINVAL;

	min_scale = FRAC_16_16(1, 8);
	max_scale = FRAC_16_16(8, 1);

	ret = drm_atomic_helper_check_plane_state(new_plane_state, crtc_state,
						  min_scale, max_scale,
						  true, true);
	अगर (ret)
		वापस ret;

	/*
	 * अगर the visibility of the plane changes (i.e, अगर the cursor is
	 * clipped out completely, we can't take the async path because
	 * we need to stage/unstage the plane from the Layer Mixer(s). We
	 * also assign/unassign the hwpipe(s) tied to the plane. We aव्योम
	 * taking the fast path क्रम both these reasons.
	 */
	अगर (new_plane_state->visible != plane->state->visible)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल व्योम mdp5_plane_atomic_async_update(काष्ठा drm_plane *plane,
					   काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_state = drm_atomic_get_new_plane_state(state,
									   plane);
	काष्ठा drm_framebuffer *old_fb = plane->state->fb;

	plane->state->src_x = new_state->src_x;
	plane->state->src_y = new_state->src_y;
	plane->state->crtc_x = new_state->crtc_x;
	plane->state->crtc_y = new_state->crtc_y;

	अगर (plane_enabled(new_state)) अणु
		काष्ठा mdp5_ctl *ctl;
		काष्ठा mdp5_pipeline *pipeline =
					mdp5_crtc_get_pipeline(new_state->crtc);
		पूर्णांक ret;

		ret = mdp5_plane_mode_set(plane, new_state->crtc, new_state->fb,
				&new_state->src, &new_state->dst);
		WARN_ON(ret < 0);

		ctl = mdp5_crtc_get_ctl(new_state->crtc);

		mdp5_ctl_commit(ctl, pipeline, mdp5_plane_get_flush(plane), true);
	पूर्ण

	*to_mdp5_plane_state(plane->state) =
		*to_mdp5_plane_state(new_state);

	new_state->fb = old_fb;
पूर्ण

अटल स्थिर काष्ठा drm_plane_helper_funcs mdp5_plane_helper_funcs = अणु
		.prepare_fb = msm_atomic_prepare_fb,
		.cleanup_fb = mdp5_plane_cleanup_fb,
		.atomic_check = mdp5_plane_atomic_check,
		.atomic_update = mdp5_plane_atomic_update,
		.atomic_async_check = mdp5_plane_atomic_async_check,
		.atomic_async_update = mdp5_plane_atomic_async_update,
पूर्ण;

अटल व्योम set_scanout_locked(काष्ठा mdp5_kms *mdp5_kms,
			       क्रमागत mdp5_pipe pipe,
			       काष्ठा drm_framebuffer *fb)
अणु
	काष्ठा msm_kms *kms = &mdp5_kms->base.base;

	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_PIPE_SRC_STRIDE_A(pipe),
			MDP5_PIPE_SRC_STRIDE_A_P0(fb->pitches[0]) |
			MDP5_PIPE_SRC_STRIDE_A_P1(fb->pitches[1]));

	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_PIPE_SRC_STRIDE_B(pipe),
			MDP5_PIPE_SRC_STRIDE_B_P2(fb->pitches[2]) |
			MDP5_PIPE_SRC_STRIDE_B_P3(fb->pitches[3]));

	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_PIPE_SRC0_ADDR(pipe),
			msm_framebuffer_iova(fb, kms->aspace, 0));
	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_PIPE_SRC1_ADDR(pipe),
			msm_framebuffer_iova(fb, kms->aspace, 1));
	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_PIPE_SRC2_ADDR(pipe),
			msm_framebuffer_iova(fb, kms->aspace, 2));
	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_PIPE_SRC3_ADDR(pipe),
			msm_framebuffer_iova(fb, kms->aspace, 3));
पूर्ण

/* Note: mdp5_plane->pipe_lock must be locked */
अटल व्योम csc_disable(काष्ठा mdp5_kms *mdp5_kms, क्रमागत mdp5_pipe pipe)
अणु
	uपूर्णांक32_t value = mdp5_पढ़ो(mdp5_kms, REG_MDP5_PIPE_OP_MODE(pipe)) &
			 ~MDP5_PIPE_OP_MODE_CSC_1_EN;

	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_PIPE_OP_MODE(pipe), value);
पूर्ण

/* Note: mdp5_plane->pipe_lock must be locked */
अटल व्योम csc_enable(काष्ठा mdp5_kms *mdp5_kms, क्रमागत mdp5_pipe pipe,
		काष्ठा csc_cfg *csc)
अणु
	uपूर्णांक32_t  i, mode = 0; /* RGB, no CSC */
	uपूर्णांक32_t *matrix;

	अगर (unlikely(!csc))
		वापस;

	अगर ((csc->type == CSC_YUV2RGB) || (CSC_YUV2YUV == csc->type))
		mode |= MDP5_PIPE_OP_MODE_CSC_SRC_DATA_FORMAT(DATA_FORMAT_YUV);
	अगर ((csc->type == CSC_RGB2YUV) || (CSC_YUV2YUV == csc->type))
		mode |= MDP5_PIPE_OP_MODE_CSC_DST_DATA_FORMAT(DATA_FORMAT_YUV);
	mode |= MDP5_PIPE_OP_MODE_CSC_1_EN;
	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_PIPE_OP_MODE(pipe), mode);

	matrix = csc->matrix;
	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_PIPE_CSC_1_MATRIX_COEFF_0(pipe),
			MDP5_PIPE_CSC_1_MATRIX_COEFF_0_COEFF_11(matrix[0]) |
			MDP5_PIPE_CSC_1_MATRIX_COEFF_0_COEFF_12(matrix[1]));
	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_PIPE_CSC_1_MATRIX_COEFF_1(pipe),
			MDP5_PIPE_CSC_1_MATRIX_COEFF_1_COEFF_13(matrix[2]) |
			MDP5_PIPE_CSC_1_MATRIX_COEFF_1_COEFF_21(matrix[3]));
	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_PIPE_CSC_1_MATRIX_COEFF_2(pipe),
			MDP5_PIPE_CSC_1_MATRIX_COEFF_2_COEFF_22(matrix[4]) |
			MDP5_PIPE_CSC_1_MATRIX_COEFF_2_COEFF_23(matrix[5]));
	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_PIPE_CSC_1_MATRIX_COEFF_3(pipe),
			MDP5_PIPE_CSC_1_MATRIX_COEFF_3_COEFF_31(matrix[6]) |
			MDP5_PIPE_CSC_1_MATRIX_COEFF_3_COEFF_32(matrix[7]));
	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_PIPE_CSC_1_MATRIX_COEFF_4(pipe),
			MDP5_PIPE_CSC_1_MATRIX_COEFF_4_COEFF_33(matrix[8]));

	क्रम (i = 0; i < ARRAY_SIZE(csc->pre_bias); i++) अणु
		uपूर्णांक32_t *pre_clamp = csc->pre_clamp;
		uपूर्णांक32_t *post_clamp = csc->post_clamp;

		mdp5_ग_लिखो(mdp5_kms, REG_MDP5_PIPE_CSC_1_PRE_CLAMP(pipe, i),
			MDP5_PIPE_CSC_1_PRE_CLAMP_REG_HIGH(pre_clamp[2*i+1]) |
			MDP5_PIPE_CSC_1_PRE_CLAMP_REG_LOW(pre_clamp[2*i]));

		mdp5_ग_लिखो(mdp5_kms, REG_MDP5_PIPE_CSC_1_POST_CLAMP(pipe, i),
			MDP5_PIPE_CSC_1_POST_CLAMP_REG_HIGH(post_clamp[2*i+1]) |
			MDP5_PIPE_CSC_1_POST_CLAMP_REG_LOW(post_clamp[2*i]));

		mdp5_ग_लिखो(mdp5_kms, REG_MDP5_PIPE_CSC_1_PRE_BIAS(pipe, i),
			MDP5_PIPE_CSC_1_PRE_BIAS_REG_VALUE(csc->pre_bias[i]));

		mdp5_ग_लिखो(mdp5_kms, REG_MDP5_PIPE_CSC_1_POST_BIAS(pipe, i),
			MDP5_PIPE_CSC_1_POST_BIAS_REG_VALUE(csc->post_bias[i]));
	पूर्ण
पूर्ण

#घोषणा PHASE_STEP_SHIFT	21
#घोषणा DOWN_SCALE_RATIO_MAX	32	/* 2^(26-21) */

अटल पूर्णांक calc_phase_step(uपूर्णांक32_t src, uपूर्णांक32_t dst, uपूर्णांक32_t *out_phase)
अणु
	uपूर्णांक32_t unit;

	अगर (src == 0 || dst == 0)
		वापस -EINVAL;

	/*
	 * PHASE_STEP_X/Y is coded on 26 bits (25:0),
	 * where 2^21 represents the unity "1" in fixed-poपूर्णांक hardware design.
	 * This leaves 5 bits क्रम the पूर्णांकeger part (करोwnscale हाल):
	 *	-> maximum करोwnscale ratio = 0b1_1111 = 31
	 */
	अगर (src > (dst * DOWN_SCALE_RATIO_MAX))
		वापस -EOVERFLOW;

	unit = 1 << PHASE_STEP_SHIFT;
	*out_phase = mult_frac(unit, src, dst);

	वापस 0;
पूर्ण

अटल पूर्णांक calc_scalex_steps(काष्ठा drm_plane *plane,
		uपूर्णांक32_t pixel_क्रमmat, uपूर्णांक32_t src, uपूर्णांक32_t dest,
		uपूर्णांक32_t phasex_steps[COMP_MAX])
अणु
	स्थिर काष्ठा drm_क्रमmat_info *info = drm_क्रमmat_info(pixel_क्रमmat);
	काष्ठा mdp5_kms *mdp5_kms = get_kms(plane);
	काष्ठा device *dev = mdp5_kms->dev->dev;
	uपूर्णांक32_t phasex_step;
	पूर्णांक ret;

	ret = calc_phase_step(src, dest, &phasex_step);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev, "X scaling (%d->%d) failed: %d\n", src, dest, ret);
		वापस ret;
	पूर्ण

	phasex_steps[COMP_0]   = phasex_step;
	phasex_steps[COMP_3]   = phasex_step;
	phasex_steps[COMP_1_2] = phasex_step / info->hsub;

	वापस 0;
पूर्ण

अटल पूर्णांक calc_scaley_steps(काष्ठा drm_plane *plane,
		uपूर्णांक32_t pixel_क्रमmat, uपूर्णांक32_t src, uपूर्णांक32_t dest,
		uपूर्णांक32_t phasey_steps[COMP_MAX])
अणु
	स्थिर काष्ठा drm_क्रमmat_info *info = drm_क्रमmat_info(pixel_क्रमmat);
	काष्ठा mdp5_kms *mdp5_kms = get_kms(plane);
	काष्ठा device *dev = mdp5_kms->dev->dev;
	uपूर्णांक32_t phasey_step;
	पूर्णांक ret;

	ret = calc_phase_step(src, dest, &phasey_step);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev, "Y scaling (%d->%d) failed: %d\n", src, dest, ret);
		वापस ret;
	पूर्ण

	phasey_steps[COMP_0]   = phasey_step;
	phasey_steps[COMP_3]   = phasey_step;
	phasey_steps[COMP_1_2] = phasey_step / info->vsub;

	वापस 0;
पूर्ण

अटल uपूर्णांक32_t get_scale_config(स्थिर काष्ठा mdp_क्रमmat *क्रमmat,
		uपूर्णांक32_t src, uपूर्णांक32_t dst, bool horz)
अणु
	स्थिर काष्ठा drm_क्रमmat_info *info = drm_क्रमmat_info(क्रमmat->base.pixel_क्रमmat);
	bool scaling = क्रमmat->is_yuv ? true : (src != dst);
	uपूर्णांक32_t sub;
	uपूर्णांक32_t ya_filter, uv_filter;
	bool yuv = क्रमmat->is_yuv;

	अगर (!scaling)
		वापस 0;

	अगर (yuv) अणु
		sub = horz ? info->hsub : info->vsub;
		uv_filter = ((src / sub) <= dst) ?
				   SCALE_FILTER_BIL : SCALE_FILTER_PCMN;
	पूर्ण
	ya_filter = (src <= dst) ? SCALE_FILTER_BIL : SCALE_FILTER_PCMN;

	अगर (horz)
		वापस  MDP5_PIPE_SCALE_CONFIG_SCALEX_EN |
			MDP5_PIPE_SCALE_CONFIG_SCALEX_FILTER_COMP_0(ya_filter) |
			MDP5_PIPE_SCALE_CONFIG_SCALEX_FILTER_COMP_3(ya_filter) |
			COND(yuv, MDP5_PIPE_SCALE_CONFIG_SCALEX_FILTER_COMP_1_2(uv_filter));
	अन्यथा
		वापस  MDP5_PIPE_SCALE_CONFIG_SCALEY_EN |
			MDP5_PIPE_SCALE_CONFIG_SCALEY_FILTER_COMP_0(ya_filter) |
			MDP5_PIPE_SCALE_CONFIG_SCALEY_FILTER_COMP_3(ya_filter) |
			COND(yuv, MDP5_PIPE_SCALE_CONFIG_SCALEY_FILTER_COMP_1_2(uv_filter));
पूर्ण

अटल व्योम calc_pixel_ext(स्थिर काष्ठा mdp_क्रमmat *क्रमmat,
		uपूर्णांक32_t src, uपूर्णांक32_t dst, uपूर्णांक32_t phase_step[2],
		पूर्णांक pix_ext_edge1[COMP_MAX], पूर्णांक pix_ext_edge2[COMP_MAX],
		bool horz)
अणु
	bool scaling = क्रमmat->is_yuv ? true : (src != dst);
	पूर्णांक i;

	/*
	 * Note:
	 * We assume here that:
	 *     1. PCMN filter is used क्रम करोwnscale
	 *     2. bilinear filter is used क्रम upscale
	 *     3. we are in a single pipe configuration
	 */

	क्रम (i = 0; i < COMP_MAX; i++) अणु
		pix_ext_edge1[i] = 0;
		pix_ext_edge2[i] = scaling ? 1 : 0;
	पूर्ण
पूर्ण

अटल व्योम mdp5_ग_लिखो_pixel_ext(काष्ठा mdp5_kms *mdp5_kms, क्रमागत mdp5_pipe pipe,
	स्थिर काष्ठा mdp_क्रमmat *क्रमmat,
	uपूर्णांक32_t src_w, पूर्णांक pe_left[COMP_MAX], पूर्णांक pe_right[COMP_MAX],
	uपूर्णांक32_t src_h, पूर्णांक pe_top[COMP_MAX], पूर्णांक pe_bottom[COMP_MAX])
अणु
	स्थिर काष्ठा drm_क्रमmat_info *info = drm_क्रमmat_info(क्रमmat->base.pixel_क्रमmat);
	uपूर्णांक32_t lr, tb, req;
	पूर्णांक i;

	क्रम (i = 0; i < COMP_MAX; i++) अणु
		uपूर्णांक32_t roi_w = src_w;
		uपूर्णांक32_t roi_h = src_h;

		अगर (क्रमmat->is_yuv && i == COMP_1_2) अणु
			roi_w /= info->hsub;
			roi_h /= info->vsub;
		पूर्ण

		lr  = (pe_left[i] >= 0) ?
			MDP5_PIPE_SW_PIX_EXT_LR_LEFT_RPT(pe_left[i]) :
			MDP5_PIPE_SW_PIX_EXT_LR_LEFT_OVF(pe_left[i]);

		lr |= (pe_right[i] >= 0) ?
			MDP5_PIPE_SW_PIX_EXT_LR_RIGHT_RPT(pe_right[i]) :
			MDP5_PIPE_SW_PIX_EXT_LR_RIGHT_OVF(pe_right[i]);

		tb  = (pe_top[i] >= 0) ?
			MDP5_PIPE_SW_PIX_EXT_TB_TOP_RPT(pe_top[i]) :
			MDP5_PIPE_SW_PIX_EXT_TB_TOP_OVF(pe_top[i]);

		tb |= (pe_bottom[i] >= 0) ?
			MDP5_PIPE_SW_PIX_EXT_TB_BOTTOM_RPT(pe_bottom[i]) :
			MDP5_PIPE_SW_PIX_EXT_TB_BOTTOM_OVF(pe_bottom[i]);

		req  = MDP5_PIPE_SW_PIX_EXT_REQ_PIXELS_LEFT_RIGHT(roi_w +
				pe_left[i] + pe_right[i]);

		req |= MDP5_PIPE_SW_PIX_EXT_REQ_PIXELS_TOP_BOTTOM(roi_h +
				pe_top[i] + pe_bottom[i]);

		mdp5_ग_लिखो(mdp5_kms, REG_MDP5_PIPE_SW_PIX_EXT_LR(pipe, i), lr);
		mdp5_ग_लिखो(mdp5_kms, REG_MDP5_PIPE_SW_PIX_EXT_TB(pipe, i), tb);
		mdp5_ग_लिखो(mdp5_kms, REG_MDP5_PIPE_SW_PIX_EXT_REQ_PIXELS(pipe, i), req);

		DBG("comp-%d (L/R): rpt=%d/%d, ovf=%d/%d, req=%d", i,
			FIELD(lr,  MDP5_PIPE_SW_PIX_EXT_LR_LEFT_RPT),
			FIELD(lr,  MDP5_PIPE_SW_PIX_EXT_LR_RIGHT_RPT),
			FIELD(lr,  MDP5_PIPE_SW_PIX_EXT_LR_LEFT_OVF),
			FIELD(lr,  MDP5_PIPE_SW_PIX_EXT_LR_RIGHT_OVF),
			FIELD(req, MDP5_PIPE_SW_PIX_EXT_REQ_PIXELS_LEFT_RIGHT));

		DBG("comp-%d (T/B): rpt=%d/%d, ovf=%d/%d, req=%d", i,
			FIELD(tb,  MDP5_PIPE_SW_PIX_EXT_TB_TOP_RPT),
			FIELD(tb,  MDP5_PIPE_SW_PIX_EXT_TB_BOTTOM_RPT),
			FIELD(tb,  MDP5_PIPE_SW_PIX_EXT_TB_TOP_OVF),
			FIELD(tb,  MDP5_PIPE_SW_PIX_EXT_TB_BOTTOM_OVF),
			FIELD(req, MDP5_PIPE_SW_PIX_EXT_REQ_PIXELS_TOP_BOTTOM));
	पूर्ण
पूर्ण

काष्ठा pixel_ext अणु
	पूर्णांक left[COMP_MAX];
	पूर्णांक right[COMP_MAX];
	पूर्णांक top[COMP_MAX];
	पूर्णांक bottom[COMP_MAX];
पूर्ण;

काष्ठा phase_step अणु
	u32 x[COMP_MAX];
	u32 y[COMP_MAX];
पूर्ण;

अटल व्योम mdp5_hwpipe_mode_set(काष्ठा mdp5_kms *mdp5_kms,
				 काष्ठा mdp5_hw_pipe *hwpipe,
				 काष्ठा drm_framebuffer *fb,
				 काष्ठा phase_step *step,
				 काष्ठा pixel_ext *pe,
				 u32 scale_config, u32 hdecm, u32 vdecm,
				 bool hflip, bool vflip,
				 पूर्णांक crtc_x, पूर्णांक crtc_y,
				 अचिन्हित पूर्णांक crtc_w, अचिन्हित पूर्णांक crtc_h,
				 u32 src_img_w, u32 src_img_h,
				 u32 src_x, u32 src_y,
				 u32 src_w, u32 src_h)
अणु
	क्रमागत mdp5_pipe pipe = hwpipe->pipe;
	bool has_pe = hwpipe->caps & MDP_PIPE_CAP_SW_PIX_EXT;
	स्थिर काष्ठा mdp_क्रमmat *क्रमmat =
			to_mdp_क्रमmat(msm_framebuffer_क्रमmat(fb));

	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_PIPE_SRC_IMG_SIZE(pipe),
			MDP5_PIPE_SRC_IMG_SIZE_WIDTH(src_img_w) |
			MDP5_PIPE_SRC_IMG_SIZE_HEIGHT(src_img_h));

	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_PIPE_SRC_SIZE(pipe),
			MDP5_PIPE_SRC_SIZE_WIDTH(src_w) |
			MDP5_PIPE_SRC_SIZE_HEIGHT(src_h));

	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_PIPE_SRC_XY(pipe),
			MDP5_PIPE_SRC_XY_X(src_x) |
			MDP5_PIPE_SRC_XY_Y(src_y));

	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_PIPE_OUT_SIZE(pipe),
			MDP5_PIPE_OUT_SIZE_WIDTH(crtc_w) |
			MDP5_PIPE_OUT_SIZE_HEIGHT(crtc_h));

	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_PIPE_OUT_XY(pipe),
			MDP5_PIPE_OUT_XY_X(crtc_x) |
			MDP5_PIPE_OUT_XY_Y(crtc_y));

	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_PIPE_SRC_FORMAT(pipe),
			MDP5_PIPE_SRC_FORMAT_A_BPC(क्रमmat->bpc_a) |
			MDP5_PIPE_SRC_FORMAT_R_BPC(क्रमmat->bpc_r) |
			MDP5_PIPE_SRC_FORMAT_G_BPC(क्रमmat->bpc_g) |
			MDP5_PIPE_SRC_FORMAT_B_BPC(क्रमmat->bpc_b) |
			COND(क्रमmat->alpha_enable, MDP5_PIPE_SRC_FORMAT_ALPHA_ENABLE) |
			MDP5_PIPE_SRC_FORMAT_CPP(क्रमmat->cpp - 1) |
			MDP5_PIPE_SRC_FORMAT_UNPACK_COUNT(क्रमmat->unpack_count - 1) |
			COND(क्रमmat->unpack_tight, MDP5_PIPE_SRC_FORMAT_UNPACK_TIGHT) |
			MDP5_PIPE_SRC_FORMAT_FETCH_TYPE(क्रमmat->fetch_type) |
			MDP5_PIPE_SRC_FORMAT_CHROMA_SAMP(क्रमmat->chroma_sample));

	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_PIPE_SRC_UNPACK(pipe),
			MDP5_PIPE_SRC_UNPACK_ELEM0(क्रमmat->unpack[0]) |
			MDP5_PIPE_SRC_UNPACK_ELEM1(क्रमmat->unpack[1]) |
			MDP5_PIPE_SRC_UNPACK_ELEM2(क्रमmat->unpack[2]) |
			MDP5_PIPE_SRC_UNPACK_ELEM3(क्रमmat->unpack[3]));

	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_PIPE_SRC_OP_MODE(pipe),
			(hflip ? MDP5_PIPE_SRC_OP_MODE_FLIP_LR : 0) |
			(vflip ? MDP5_PIPE_SRC_OP_MODE_FLIP_UD : 0) |
			COND(has_pe, MDP5_PIPE_SRC_OP_MODE_SW_PIX_EXT_OVERRIDE) |
			MDP5_PIPE_SRC_OP_MODE_BWC(BWC_LOSSLESS));

	/* not using secure mode: */
	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_PIPE_SRC_ADDR_SW_STATUS(pipe), 0);

	अगर (hwpipe->caps & MDP_PIPE_CAP_SW_PIX_EXT)
		mdp5_ग_लिखो_pixel_ext(mdp5_kms, pipe, क्रमmat,
				src_w, pe->left, pe->right,
				src_h, pe->top, pe->bottom);

	अगर (hwpipe->caps & MDP_PIPE_CAP_SCALE) अणु
		mdp5_ग_लिखो(mdp5_kms, REG_MDP5_PIPE_SCALE_PHASE_STEP_X(pipe),
				step->x[COMP_0]);
		mdp5_ग_लिखो(mdp5_kms, REG_MDP5_PIPE_SCALE_PHASE_STEP_Y(pipe),
				step->y[COMP_0]);
		mdp5_ग_लिखो(mdp5_kms, REG_MDP5_PIPE_SCALE_CR_PHASE_STEP_X(pipe),
				step->x[COMP_1_2]);
		mdp5_ग_लिखो(mdp5_kms, REG_MDP5_PIPE_SCALE_CR_PHASE_STEP_Y(pipe),
				step->y[COMP_1_2]);
		mdp5_ग_लिखो(mdp5_kms, REG_MDP5_PIPE_DECIMATION(pipe),
				MDP5_PIPE_DECIMATION_VERT(vdecm) |
				MDP5_PIPE_DECIMATION_HORZ(hdecm));
		mdp5_ग_लिखो(mdp5_kms, REG_MDP5_PIPE_SCALE_CONFIG(pipe),
			   scale_config);
	पूर्ण

	अगर (hwpipe->caps & MDP_PIPE_CAP_CSC) अणु
		अगर (MDP_FORMAT_IS_YUV(क्रमmat))
			csc_enable(mdp5_kms, pipe,
					mdp_get_शेष_csc_cfg(CSC_YUV2RGB));
		अन्यथा
			csc_disable(mdp5_kms, pipe);
	पूर्ण

	set_scanout_locked(mdp5_kms, pipe, fb);
पूर्ण

अटल पूर्णांक mdp5_plane_mode_set(काष्ठा drm_plane *plane,
		काष्ठा drm_crtc *crtc, काष्ठा drm_framebuffer *fb,
		काष्ठा drm_rect *src, काष्ठा drm_rect *dest)
अणु
	काष्ठा drm_plane_state *pstate = plane->state;
	काष्ठा mdp5_hw_pipe *hwpipe = to_mdp5_plane_state(pstate)->hwpipe;
	काष्ठा mdp5_kms *mdp5_kms = get_kms(plane);
	क्रमागत mdp5_pipe pipe = hwpipe->pipe;
	काष्ठा mdp5_hw_pipe *right_hwpipe;
	स्थिर काष्ठा mdp_क्रमmat *क्रमmat;
	uपूर्णांक32_t nplanes, config = 0;
	काष्ठा phase_step step = अणु अणु 0 पूर्ण पूर्ण;
	काष्ठा pixel_ext pe = अणु अणु 0 पूर्ण पूर्ण;
	uपूर्णांक32_t hdecm = 0, vdecm = 0;
	uपूर्णांक32_t pix_क्रमmat;
	अचिन्हित पूर्णांक rotation;
	bool vflip, hflip;
	पूर्णांक crtc_x, crtc_y;
	अचिन्हित पूर्णांक crtc_w, crtc_h;
	uपूर्णांक32_t src_x, src_y;
	uपूर्णांक32_t src_w, src_h;
	uपूर्णांक32_t src_img_w, src_img_h;
	पूर्णांक ret;

	nplanes = fb->क्रमmat->num_planes;

	/* bad क्रमmats should alपढ़ोy be rejected: */
	अगर (WARN_ON(nplanes > pipe2nclients(pipe)))
		वापस -EINVAL;

	क्रमmat = to_mdp_क्रमmat(msm_framebuffer_क्रमmat(fb));
	pix_क्रमmat = क्रमmat->base.pixel_क्रमmat;

	src_x = src->x1;
	src_y = src->y1;
	src_w = drm_rect_width(src);
	src_h = drm_rect_height(src);

	crtc_x = dest->x1;
	crtc_y = dest->y1;
	crtc_w = drm_rect_width(dest);
	crtc_h = drm_rect_height(dest);

	/* src values are in Q16 fixed poपूर्णांक, convert to पूर्णांकeger: */
	src_x = src_x >> 16;
	src_y = src_y >> 16;
	src_w = src_w >> 16;
	src_h = src_h >> 16;

	src_img_w = min(fb->width, src_w);
	src_img_h = min(fb->height, src_h);

	DBG("%s: FB[%u] %u,%u,%u,%u -> CRTC[%u] %d,%d,%u,%u", plane->name,
			fb->base.id, src_x, src_y, src_w, src_h,
			crtc->base.id, crtc_x, crtc_y, crtc_w, crtc_h);

	right_hwpipe = to_mdp5_plane_state(pstate)->r_hwpipe;
	अगर (right_hwpipe) अणु
		/*
		 * अगर the plane comprises of 2 hw pipes, assume that the width
		 * is split equally across them. The only parameters that varies
		 * between the 2 pipes are src_x and crtc_x
		 */
		crtc_w /= 2;
		src_w /= 2;
		src_img_w /= 2;
	पूर्ण

	ret = calc_scalex_steps(plane, pix_क्रमmat, src_w, crtc_w, step.x);
	अगर (ret)
		वापस ret;

	ret = calc_scaley_steps(plane, pix_क्रमmat, src_h, crtc_h, step.y);
	अगर (ret)
		वापस ret;

	अगर (hwpipe->caps & MDP_PIPE_CAP_SW_PIX_EXT) अणु
		calc_pixel_ext(क्रमmat, src_w, crtc_w, step.x,
			       pe.left, pe.right, true);
		calc_pixel_ext(क्रमmat, src_h, crtc_h, step.y,
			       pe.top, pe.bottom, false);
	पूर्ण

	/* TODO calc hdecm, vdecm */

	/* SCALE is used to both scale and up-sample chroma components */
	config |= get_scale_config(क्रमmat, src_w, crtc_w, true);
	config |= get_scale_config(क्रमmat, src_h, crtc_h, false);
	DBG("scale config = %x", config);

	rotation = drm_rotation_simplअगरy(pstate->rotation,
					 DRM_MODE_ROTATE_0 |
					 DRM_MODE_REFLECT_X |
					 DRM_MODE_REFLECT_Y);
	hflip = !!(rotation & DRM_MODE_REFLECT_X);
	vflip = !!(rotation & DRM_MODE_REFLECT_Y);

	mdp5_hwpipe_mode_set(mdp5_kms, hwpipe, fb, &step, &pe,
			     config, hdecm, vdecm, hflip, vflip,
			     crtc_x, crtc_y, crtc_w, crtc_h,
			     src_img_w, src_img_h,
			     src_x, src_y, src_w, src_h);
	अगर (right_hwpipe)
		mdp5_hwpipe_mode_set(mdp5_kms, right_hwpipe, fb, &step, &pe,
				     config, hdecm, vdecm, hflip, vflip,
				     crtc_x + crtc_w, crtc_y, crtc_w, crtc_h,
				     src_img_w, src_img_h,
				     src_x + src_w, src_y, src_w, src_h);

	वापस ret;
पूर्ण

/*
 * Use this func and the one below only after the atomic state has been
 * successfully swapped
 */
क्रमागत mdp5_pipe mdp5_plane_pipe(काष्ठा drm_plane *plane)
अणु
	काष्ठा mdp5_plane_state *pstate = to_mdp5_plane_state(plane->state);

	अगर (WARN_ON(!pstate->hwpipe))
		वापस SSPP_NONE;

	वापस pstate->hwpipe->pipe;
पूर्ण

क्रमागत mdp5_pipe mdp5_plane_right_pipe(काष्ठा drm_plane *plane)
अणु
	काष्ठा mdp5_plane_state *pstate = to_mdp5_plane_state(plane->state);

	अगर (!pstate->r_hwpipe)
		वापस SSPP_NONE;

	वापस pstate->r_hwpipe->pipe;
पूर्ण

uपूर्णांक32_t mdp5_plane_get_flush(काष्ठा drm_plane *plane)
अणु
	काष्ठा mdp5_plane_state *pstate = to_mdp5_plane_state(plane->state);
	u32 mask;

	अगर (WARN_ON(!pstate->hwpipe))
		वापस 0;

	mask = pstate->hwpipe->flush_mask;

	अगर (pstate->r_hwpipe)
		mask |= pstate->r_hwpipe->flush_mask;

	वापस mask;
पूर्ण

/* initialize plane */
काष्ठा drm_plane *mdp5_plane_init(काष्ठा drm_device *dev,
				  क्रमागत drm_plane_type type)
अणु
	काष्ठा drm_plane *plane = शून्य;
	काष्ठा mdp5_plane *mdp5_plane;
	पूर्णांक ret;

	mdp5_plane = kzalloc(माप(*mdp5_plane), GFP_KERNEL);
	अगर (!mdp5_plane) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	plane = &mdp5_plane->base;

	mdp5_plane->nक्रमmats = mdp_get_क्रमmats(mdp5_plane->क्रमmats,
		ARRAY_SIZE(mdp5_plane->क्रमmats), false);

	ret = drm_universal_plane_init(dev, plane, 0xff, &mdp5_plane_funcs,
			mdp5_plane->क्रमmats, mdp5_plane->nक्रमmats,
			शून्य, type, शून्य);
	अगर (ret)
		जाओ fail;

	drm_plane_helper_add(plane, &mdp5_plane_helper_funcs);

	mdp5_plane_install_properties(plane, &plane->base);

	drm_plane_enable_fb_damage_clips(plane);

	वापस plane;

fail:
	अगर (plane)
		mdp5_plane_destroy(plane);

	वापस ERR_PTR(ret);
पूर्ण
