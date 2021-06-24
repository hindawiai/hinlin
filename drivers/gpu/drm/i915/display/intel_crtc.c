<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2020 Intel Corporation
 */
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_plane.h>
#समावेश <drm/drm_plane_helper.h>

#समावेश "i915_trace.h"
#समावेश "i915_vgpu.h"

#समावेश "intel_atomic.h"
#समावेश "intel_atomic_plane.h"
#समावेश "intel_color.h"
#समावेश "intel_crtc.h"
#समावेश "intel_cursor.h"
#समावेश "intel_display_debugfs.h"
#समावेश "intel_display_types.h"
#समावेश "intel_dsi.h"
#समावेश "intel_pipe_crc.h"
#समावेश "intel_psr.h"
#समावेश "intel_sprite.h"
#समावेश "intel_vrr.h"
#समावेश "i9xx_plane.h"
#समावेश "skl_universal_plane.h"

अटल व्योम निश्चित_vblank_disabled(काष्ठा drm_crtc *crtc)
अणु
	अगर (I915_STATE_WARN_ON(drm_crtc_vblank_get(crtc) == 0))
		drm_crtc_vblank_put(crtc);
पूर्ण

u32 पूर्णांकel_crtc_get_vblank_counter(काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा drm_device *dev = crtc->base.dev;
	काष्ठा drm_vblank_crtc *vblank = &dev->vblank[drm_crtc_index(&crtc->base)];

	अगर (!crtc->active)
		वापस 0;

	अगर (!vblank->max_vblank_count)
		वापस (u32)drm_crtc_accurate_vblank_count(&crtc->base);

	वापस crtc->base.funcs->get_vblank_counter(&crtc->base);
पूर्ण

u32 पूर्णांकel_crtc_max_vblank_count(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc_state->uapi.crtc->dev);

	/*
	 * From Gen 11, In हाल of dsi cmd mode, frame counter wouldnt
	 * have updated at the beginning of TE, अगर we want to use
	 * the hw counter, then we would find it updated in only
	 * the next TE, hence चयनing to sw counter.
	 */
	अगर (crtc_state->mode_flags & (I915_MODE_FLAG_DSI_USE_TE0 |
				      I915_MODE_FLAG_DSI_USE_TE1))
		वापस 0;

	/*
	 * On i965gm the hardware frame counter पढ़ोs
	 * zero when the TV encoder is enabled :(
	 */
	अगर (IS_I965GM(dev_priv) &&
	    (crtc_state->output_types & BIT(INTEL_OUTPUT_TVOUT)))
		वापस 0;

	अगर (DISPLAY_VER(dev_priv) >= 5 || IS_G4X(dev_priv))
		वापस 0xffffffff; /* full 32 bit counter */
	अन्यथा अगर (DISPLAY_VER(dev_priv) >= 3)
		वापस 0xffffff; /* only 24 bits of frame count */
	अन्यथा
		वापस 0; /* Gen2 करोesn't have a hardware frame counter */
पूर्ण

व्योम पूर्णांकel_crtc_vblank_on(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);

	निश्चित_vblank_disabled(&crtc->base);
	drm_crtc_set_max_vblank_count(&crtc->base,
				      पूर्णांकel_crtc_max_vblank_count(crtc_state));
	drm_crtc_vblank_on(&crtc->base);

	/*
	 * Should really happen exactly when we enable the pipe
	 * but we want the frame counters in the trace, and that
	 * requires vblank support on some platक्रमms/outमाला_दो.
	 */
	trace_पूर्णांकel_pipe_enable(crtc);
पूर्ण

व्योम पूर्णांकel_crtc_vblank_off(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);

	/*
	 * Should really happen exactly when we disable the pipe
	 * but we want the frame counters in the trace, and that
	 * requires vblank support on some platक्रमms/outमाला_दो.
	 */
	trace_पूर्णांकel_pipe_disable(crtc);

	drm_crtc_vblank_off(&crtc->base);
	निश्चित_vblank_disabled(&crtc->base);
पूर्ण

काष्ठा पूर्णांकel_crtc_state *पूर्णांकel_crtc_state_alloc(काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा पूर्णांकel_crtc_state *crtc_state;

	crtc_state = kदो_स्मृति(माप(*crtc_state), GFP_KERNEL);

	अगर (crtc_state)
		पूर्णांकel_crtc_state_reset(crtc_state, crtc);

	वापस crtc_state;
पूर्ण

व्योम पूर्णांकel_crtc_state_reset(काष्ठा पूर्णांकel_crtc_state *crtc_state,
			    काष्ठा पूर्णांकel_crtc *crtc)
अणु
	स_रखो(crtc_state, 0, माप(*crtc_state));

	__drm_atomic_helper_crtc_state_reset(&crtc_state->uapi, &crtc->base);

	crtc_state->cpu_transcoder = INVALID_TRANSCODER;
	crtc_state->master_transcoder = INVALID_TRANSCODER;
	crtc_state->hsw_workaround_pipe = INVALID_PIPE;
	crtc_state->scaler_state.scaler_id = -1;
	crtc_state->mst_master_transcoder = INVALID_TRANSCODER;
पूर्ण

अटल काष्ठा पूर्णांकel_crtc *पूर्णांकel_crtc_alloc(व्योम)
अणु
	काष्ठा पूर्णांकel_crtc_state *crtc_state;
	काष्ठा पूर्णांकel_crtc *crtc;

	crtc = kzalloc(माप(*crtc), GFP_KERNEL);
	अगर (!crtc)
		वापस ERR_PTR(-ENOMEM);

	crtc_state = पूर्णांकel_crtc_state_alloc(crtc);
	अगर (!crtc_state) अणु
		kमुक्त(crtc);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	crtc->base.state = &crtc_state->uapi;
	crtc->config = crtc_state;

	वापस crtc;
पूर्ण

अटल व्योम पूर्णांकel_crtc_मुक्त(काष्ठा पूर्णांकel_crtc *crtc)
अणु
	पूर्णांकel_crtc_destroy_state(&crtc->base, crtc->base.state);
	kमुक्त(crtc);
पूर्ण

अटल व्योम पूर्णांकel_crtc_destroy(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा पूर्णांकel_crtc *पूर्णांकel_crtc = to_पूर्णांकel_crtc(crtc);

	drm_crtc_cleanup(crtc);
	kमुक्त(पूर्णांकel_crtc);
पूर्ण

अटल पूर्णांक पूर्णांकel_crtc_late_रेजिस्टर(काष्ठा drm_crtc *crtc)
अणु
	पूर्णांकel_crtc_debugfs_add(crtc);
	वापस 0;
पूर्ण

#घोषणा INTEL_CRTC_FUNCS \
	.set_config = drm_atomic_helper_set_config, \
	.destroy = पूर्णांकel_crtc_destroy, \
	.page_flip = drm_atomic_helper_page_flip, \
	.atomic_duplicate_state = पूर्णांकel_crtc_duplicate_state, \
	.atomic_destroy_state = पूर्णांकel_crtc_destroy_state, \
	.set_crc_source = पूर्णांकel_crtc_set_crc_source, \
	.verअगरy_crc_source = पूर्णांकel_crtc_verअगरy_crc_source, \
	.get_crc_sources = पूर्णांकel_crtc_get_crc_sources, \
	.late_रेजिस्टर = पूर्णांकel_crtc_late_रेजिस्टर

अटल स्थिर काष्ठा drm_crtc_funcs bdw_crtc_funcs = अणु
	INTEL_CRTC_FUNCS,

	.get_vblank_counter = g4x_get_vblank_counter,
	.enable_vblank = bdw_enable_vblank,
	.disable_vblank = bdw_disable_vblank,
	.get_vblank_बारtamp = पूर्णांकel_crtc_get_vblank_बारtamp,
पूर्ण;

अटल स्थिर काष्ठा drm_crtc_funcs ilk_crtc_funcs = अणु
	INTEL_CRTC_FUNCS,

	.get_vblank_counter = g4x_get_vblank_counter,
	.enable_vblank = ilk_enable_vblank,
	.disable_vblank = ilk_disable_vblank,
	.get_vblank_बारtamp = पूर्णांकel_crtc_get_vblank_बारtamp,
पूर्ण;

अटल स्थिर काष्ठा drm_crtc_funcs g4x_crtc_funcs = अणु
	INTEL_CRTC_FUNCS,

	.get_vblank_counter = g4x_get_vblank_counter,
	.enable_vblank = i965_enable_vblank,
	.disable_vblank = i965_disable_vblank,
	.get_vblank_बारtamp = पूर्णांकel_crtc_get_vblank_बारtamp,
पूर्ण;

अटल स्थिर काष्ठा drm_crtc_funcs i965_crtc_funcs = अणु
	INTEL_CRTC_FUNCS,

	.get_vblank_counter = i915_get_vblank_counter,
	.enable_vblank = i965_enable_vblank,
	.disable_vblank = i965_disable_vblank,
	.get_vblank_बारtamp = पूर्णांकel_crtc_get_vblank_बारtamp,
पूर्ण;

अटल स्थिर काष्ठा drm_crtc_funcs i915gm_crtc_funcs = अणु
	INTEL_CRTC_FUNCS,

	.get_vblank_counter = i915_get_vblank_counter,
	.enable_vblank = i915gm_enable_vblank,
	.disable_vblank = i915gm_disable_vblank,
	.get_vblank_बारtamp = पूर्णांकel_crtc_get_vblank_बारtamp,
पूर्ण;

अटल स्थिर काष्ठा drm_crtc_funcs i915_crtc_funcs = अणु
	INTEL_CRTC_FUNCS,

	.get_vblank_counter = i915_get_vblank_counter,
	.enable_vblank = i8xx_enable_vblank,
	.disable_vblank = i8xx_disable_vblank,
	.get_vblank_बारtamp = पूर्णांकel_crtc_get_vblank_बारtamp,
पूर्ण;

अटल स्थिर काष्ठा drm_crtc_funcs i8xx_crtc_funcs = अणु
	INTEL_CRTC_FUNCS,

	/* no hw vblank counter */
	.enable_vblank = i8xx_enable_vblank,
	.disable_vblank = i8xx_disable_vblank,
	.get_vblank_बारtamp = पूर्णांकel_crtc_get_vblank_बारtamp,
पूर्ण;

पूर्णांक पूर्णांकel_crtc_init(काष्ठा drm_i915_निजी *dev_priv, क्रमागत pipe pipe)
अणु
	काष्ठा पूर्णांकel_plane *primary, *cursor;
	स्थिर काष्ठा drm_crtc_funcs *funcs;
	काष्ठा पूर्णांकel_crtc *crtc;
	पूर्णांक sprite, ret;

	crtc = पूर्णांकel_crtc_alloc();
	अगर (IS_ERR(crtc))
		वापस PTR_ERR(crtc);

	crtc->pipe = pipe;
	crtc->num_scalers = RUNTIME_INFO(dev_priv)->num_scalers[pipe];

	अगर (DISPLAY_VER(dev_priv) >= 9)
		primary = skl_universal_plane_create(dev_priv, pipe,
						     PLANE_PRIMARY);
	अन्यथा
		primary = पूर्णांकel_primary_plane_create(dev_priv, pipe);
	अगर (IS_ERR(primary)) अणु
		ret = PTR_ERR(primary);
		जाओ fail;
	पूर्ण
	crtc->plane_ids_mask |= BIT(primary->id);

	क्रम_each_sprite(dev_priv, pipe, sprite) अणु
		काष्ठा पूर्णांकel_plane *plane;

		अगर (DISPLAY_VER(dev_priv) >= 9)
			plane = skl_universal_plane_create(dev_priv, pipe,
							   PLANE_SPRITE0 + sprite);
		अन्यथा
			plane = पूर्णांकel_sprite_plane_create(dev_priv, pipe, sprite);
		अगर (IS_ERR(plane)) अणु
			ret = PTR_ERR(plane);
			जाओ fail;
		पूर्ण
		crtc->plane_ids_mask |= BIT(plane->id);
	पूर्ण

	cursor = पूर्णांकel_cursor_plane_create(dev_priv, pipe);
	अगर (IS_ERR(cursor)) अणु
		ret = PTR_ERR(cursor);
		जाओ fail;
	पूर्ण
	crtc->plane_ids_mask |= BIT(cursor->id);

	अगर (HAS_GMCH(dev_priv)) अणु
		अगर (IS_CHERRYVIEW(dev_priv) ||
		    IS_VALLEYVIEW(dev_priv) || IS_G4X(dev_priv))
			funcs = &g4x_crtc_funcs;
		अन्यथा अगर (IS_DISPLAY_VER(dev_priv, 4))
			funcs = &i965_crtc_funcs;
		अन्यथा अगर (IS_I945GM(dev_priv) || IS_I915GM(dev_priv))
			funcs = &i915gm_crtc_funcs;
		अन्यथा अगर (IS_DISPLAY_VER(dev_priv, 3))
			funcs = &i915_crtc_funcs;
		अन्यथा
			funcs = &i8xx_crtc_funcs;
	पूर्ण अन्यथा अणु
		अगर (DISPLAY_VER(dev_priv) >= 8)
			funcs = &bdw_crtc_funcs;
		अन्यथा
			funcs = &ilk_crtc_funcs;
	पूर्ण

	ret = drm_crtc_init_with_planes(&dev_priv->drm, &crtc->base,
					&primary->base, &cursor->base,
					funcs, "pipe %c", pipe_name(pipe));
	अगर (ret)
		जाओ fail;

	BUG_ON(pipe >= ARRAY_SIZE(dev_priv->pipe_to_crtc_mapping) ||
	       dev_priv->pipe_to_crtc_mapping[pipe] != शून्य);
	dev_priv->pipe_to_crtc_mapping[pipe] = crtc;

	अगर (DISPLAY_VER(dev_priv) < 9) अणु
		क्रमागत i9xx_plane_id i9xx_plane = primary->i9xx_plane;

		BUG_ON(i9xx_plane >= ARRAY_SIZE(dev_priv->plane_to_crtc_mapping) ||
		       dev_priv->plane_to_crtc_mapping[i9xx_plane] != शून्य);
		dev_priv->plane_to_crtc_mapping[i9xx_plane] = crtc;
	पूर्ण

	अगर (DISPLAY_VER(dev_priv) >= 11 || IS_CANNONLAKE(dev_priv))
		drm_crtc_create_scaling_filter_property(&crtc->base,
						BIT(DRM_SCALING_FILTER_DEFAULT) |
						BIT(DRM_SCALING_FILTER_NEAREST_NEIGHBOR));

	पूर्णांकel_color_init(crtc);

	पूर्णांकel_crtc_crc_init(crtc);

	drm_WARN_ON(&dev_priv->drm, drm_crtc_index(&crtc->base) != crtc->pipe);

	वापस 0;

fail:
	पूर्णांकel_crtc_मुक्त(crtc);

	वापस ret;
पूर्ण

पूर्णांक पूर्णांकel_usecs_to_scanlines(स्थिर काष्ठा drm_display_mode *adjusted_mode,
			     पूर्णांक usecs)
अणु
	/* paranoia */
	अगर (!adjusted_mode->crtc_htotal)
		वापस 1;

	वापस DIV_ROUND_UP(usecs * adjusted_mode->crtc_घड़ी,
			    1000 * adjusted_mode->crtc_htotal);
पूर्ण

अटल पूर्णांक पूर्णांकel_mode_vblank_start(स्थिर काष्ठा drm_display_mode *mode)
अणु
	पूर्णांक vblank_start = mode->crtc_vblank_start;

	अगर (mode->flags & DRM_MODE_FLAG_INTERLACE)
		vblank_start = DIV_ROUND_UP(vblank_start, 2);

	वापस vblank_start;
पूर्ण

/**
 * पूर्णांकel_pipe_update_start() - start update of a set of display रेजिस्टरs
 * @new_crtc_state: the new crtc state
 *
 * Mark the start of an update to pipe रेजिस्टरs that should be updated
 * atomically regarding vblank. If the next vblank will happens within
 * the next 100 us, this function रुकोs until the vblank passes.
 *
 * After a successful call to this function, पूर्णांकerrupts will be disabled
 * until a subsequent call to पूर्णांकel_pipe_update_end(). That is करोne to
 * aव्योम अक्रमom delays.
 */
व्योम पूर्णांकel_pipe_update_start(स्थिर काष्ठा पूर्णांकel_crtc_state *new_crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(new_crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	स्थिर काष्ठा drm_display_mode *adjusted_mode = &new_crtc_state->hw.adjusted_mode;
	दीर्घ समयout = msecs_to_jअगरfies_समयout(1);
	पूर्णांक scanline, min, max, vblank_start;
	रुको_queue_head_t *wq = drm_crtc_vblank_रुकोqueue(&crtc->base);
	bool need_vlv_dsi_wa = (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv)) &&
		पूर्णांकel_crtc_has_type(new_crtc_state, INTEL_OUTPUT_DSI);
	DEFINE_WAIT(रुको);

	अगर (new_crtc_state->uapi.async_flip)
		वापस;

	अगर (new_crtc_state->vrr.enable)
		vblank_start = पूर्णांकel_vrr_vmax_vblank_start(new_crtc_state);
	अन्यथा
		vblank_start = पूर्णांकel_mode_vblank_start(adjusted_mode);

	/* FIXME needs to be calibrated sensibly */
	min = vblank_start - पूर्णांकel_usecs_to_scanlines(adjusted_mode,
						      VBLANK_EVASION_TIME_US);
	max = vblank_start - 1;

	अगर (min <= 0 || max <= 0)
		जाओ irq_disable;

	अगर (drm_WARN_ON(&dev_priv->drm, drm_crtc_vblank_get(&crtc->base)))
		जाओ irq_disable;

	/*
	 * Wait क्रम psr to idle out after enabling the VBL पूर्णांकerrupts
	 * VBL पूर्णांकerrupts will start the PSR निकास and prevent a PSR
	 * re-entry as well.
	 */
	पूर्णांकel_psr_रुको_क्रम_idle(new_crtc_state);

	local_irq_disable();

	crtc->debug.min_vbl = min;
	crtc->debug.max_vbl = max;
	trace_पूर्णांकel_pipe_update_start(crtc);

	क्रम (;;) अणु
		/*
		 * prepare_to_रुको() has a memory barrier, which guarantees
		 * other CPUs can see the task state update by the समय we
		 * पढ़ो the scanline.
		 */
		prepare_to_रुको(wq, &रुको, TASK_UNINTERRUPTIBLE);

		scanline = पूर्णांकel_get_crtc_scanline(crtc);
		अगर (scanline < min || scanline > max)
			अवरोध;

		अगर (!समयout) अणु
			drm_err(&dev_priv->drm,
				"Potential atomic update failure on pipe %c\n",
				pipe_name(crtc->pipe));
			अवरोध;
		पूर्ण

		local_irq_enable();

		समयout = schedule_समयout(समयout);

		local_irq_disable();
	पूर्ण

	finish_रुको(wq, &रुको);

	drm_crtc_vblank_put(&crtc->base);

	/*
	 * On VLV/CHV DSI the scanline counter would appear to
	 * increment approx. 1/3 of a scanline beक्रमe start of vblank.
	 * The रेजिस्टरs still get latched at start of vblank however.
	 * This means we must not ग_लिखो any रेजिस्टरs on the first
	 * line of vblank (since not the whole line is actually in
	 * vblank). And unक्रमtunately we can't use the पूर्णांकerrupt to
	 * रुको here since it will fire too soon. We could use the
	 * frame start पूर्णांकerrupt instead since it will fire after the
	 * critical scanline, but that would require more changes
	 * in the पूर्णांकerrupt code. So क्रम now we'll just करो the nasty
	 * thing and poll क्रम the bad scanline to pass us by.
	 *
	 * FIXME figure out अगर BXT+ DSI suffers from this as well
	 */
	जबतक (need_vlv_dsi_wa && scanline == vblank_start)
		scanline = पूर्णांकel_get_crtc_scanline(crtc);

	crtc->debug.scanline_start = scanline;
	crtc->debug.start_vbl_समय = kसमय_get();
	crtc->debug.start_vbl_count = पूर्णांकel_crtc_get_vblank_counter(crtc);

	trace_पूर्णांकel_pipe_update_vblank_evaded(crtc);
	वापस;

irq_disable:
	local_irq_disable();
पूर्ण

#अगर IS_ENABLED(CONFIG_DRM_I915_DEBUG_VBLANK_EVADE)
अटल व्योम dbg_vblank_evade(काष्ठा पूर्णांकel_crtc *crtc, kसमय_प्रकार end)
अणु
	u64 delta = kसमय_प्रकारo_ns(kसमय_sub(end, crtc->debug.start_vbl_समय));
	अचिन्हित पूर्णांक h;

	h = ilog2(delta >> 9);
	अगर (h >= ARRAY_SIZE(crtc->debug.vbl.बार))
		h = ARRAY_SIZE(crtc->debug.vbl.बार) - 1;
	crtc->debug.vbl.बार[h]++;

	crtc->debug.vbl.sum += delta;
	अगर (!crtc->debug.vbl.min || delta < crtc->debug.vbl.min)
		crtc->debug.vbl.min = delta;
	अगर (delta > crtc->debug.vbl.max)
		crtc->debug.vbl.max = delta;

	अगर (delta > 1000 * VBLANK_EVASION_TIME_US) अणु
		drm_dbg_kms(crtc->base.dev,
			    "Atomic update on pipe (%c) took %lld us, max time under evasion is %u us\n",
			    pipe_name(crtc->pipe),
			    भाग_u64(delta, 1000),
			    VBLANK_EVASION_TIME_US);
		crtc->debug.vbl.over++;
	पूर्ण
पूर्ण
#अन्यथा
अटल व्योम dbg_vblank_evade(काष्ठा पूर्णांकel_crtc *crtc, kसमय_प्रकार end) अणुपूर्ण
#पूर्ण_अगर

/**
 * पूर्णांकel_pipe_update_end() - end update of a set of display रेजिस्टरs
 * @new_crtc_state: the new crtc state
 *
 * Mark the end of an update started with पूर्णांकel_pipe_update_start(). This
 * re-enables पूर्णांकerrupts and verअगरies the update was actually completed
 * beक्रमe a vblank.
 */
व्योम पूर्णांकel_pipe_update_end(काष्ठा पूर्णांकel_crtc_state *new_crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(new_crtc_state->uapi.crtc);
	क्रमागत pipe pipe = crtc->pipe;
	पूर्णांक scanline_end = पूर्णांकel_get_crtc_scanline(crtc);
	u32 end_vbl_count = पूर्णांकel_crtc_get_vblank_counter(crtc);
	kसमय_प्रकार end_vbl_समय = kसमय_get();
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);

	अगर (new_crtc_state->uapi.async_flip)
		वापस;

	trace_पूर्णांकel_pipe_update_end(crtc, end_vbl_count, scanline_end);

	/*
	 * Inहाल of mipi dsi command mode, we need to set frame update
	 * request क्रम every commit.
	 */
	अगर (DISPLAY_VER(dev_priv) >= 11 &&
	    पूर्णांकel_crtc_has_type(new_crtc_state, INTEL_OUTPUT_DSI))
		icl_dsi_frame_update(new_crtc_state);

	/* We're still in the vblank-evade critical section, this can't race.
	 * Would be slightly nice to just grab the vblank count and arm the
	 * event outside of the critical section - the spinlock might spin क्रम a
	 * जबतक ... */
	अगर (new_crtc_state->uapi.event) अणु
		drm_WARN_ON(&dev_priv->drm,
			    drm_crtc_vblank_get(&crtc->base) != 0);

		spin_lock(&crtc->base.dev->event_lock);
		drm_crtc_arm_vblank_event(&crtc->base,
					  new_crtc_state->uapi.event);
		spin_unlock(&crtc->base.dev->event_lock);

		new_crtc_state->uapi.event = शून्य;
	पूर्ण

	local_irq_enable();

	/* Send VRR Push to terminate Vblank */
	पूर्णांकel_vrr_send_push(new_crtc_state);

	अगर (पूर्णांकel_vgpu_active(dev_priv))
		वापस;

	अगर (crtc->debug.start_vbl_count &&
	    crtc->debug.start_vbl_count != end_vbl_count) अणु
		drm_err(&dev_priv->drm,
			"Atomic update failure on pipe %c (start=%u end=%u) time %lld us, min %d, max %d, scanline start %d, end %d\n",
			pipe_name(pipe), crtc->debug.start_vbl_count,
			end_vbl_count,
			kसमय_us_delta(end_vbl_समय,
				       crtc->debug.start_vbl_समय),
			crtc->debug.min_vbl, crtc->debug.max_vbl,
			crtc->debug.scanline_start, scanline_end);
	पूर्ण

	dbg_vblank_evade(crtc, end_vbl_समय);
पूर्ण
