<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+

#समावेश <linux/dma-fence.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_vblank.h>

#समावेश "vkms_drv.h"

अटल क्रमागत hrसमयr_restart vkms_vblank_simulate(काष्ठा hrसमयr *समयr)
अणु
	काष्ठा vkms_output *output = container_of(समयr, काष्ठा vkms_output,
						  vblank_hrसमयr);
	काष्ठा drm_crtc *crtc = &output->crtc;
	काष्ठा vkms_crtc_state *state;
	u64 ret_overrun;
	bool ret, fence_cookie;

	fence_cookie = dma_fence_begin_संकेतling();

	ret_overrun = hrसमयr_क्रमward_now(&output->vblank_hrसमयr,
					  output->period_ns);
	अगर (ret_overrun != 1)
		pr_warn("%s: vblank timer overrun\n", __func__);

	spin_lock(&output->lock);
	ret = drm_crtc_handle_vblank(crtc);
	अगर (!ret)
		DRM_ERROR("vkms failure on handling vblank");

	state = output->composer_state;
	spin_unlock(&output->lock);

	अगर (state && output->composer_enabled) अणु
		u64 frame = drm_crtc_accurate_vblank_count(crtc);

		/* update frame_start only अगर a queued vkms_composer_worker()
		 * has पढ़ो the data
		 */
		spin_lock(&output->composer_lock);
		अगर (!state->crc_pending)
			state->frame_start = frame;
		अन्यथा
			DRM_DEBUG_DRIVER("crc worker falling behind, frame_start: %llu, frame_end: %llu\n",
					 state->frame_start, frame);
		state->frame_end = frame;
		state->crc_pending = true;
		spin_unlock(&output->composer_lock);

		ret = queue_work(output->composer_workq, &state->composer_work);
		अगर (!ret)
			DRM_DEBUG_DRIVER("Composer worker already queued\n");
	पूर्ण

	dma_fence_end_संकेतling(fence_cookie);

	वापस HRTIMER_RESTART;
पूर्ण

अटल पूर्णांक vkms_enable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	अचिन्हित पूर्णांक pipe = drm_crtc_index(crtc);
	काष्ठा drm_vblank_crtc *vblank = &dev->vblank[pipe];
	काष्ठा vkms_output *out = drm_crtc_to_vkms_output(crtc);

	drm_calc_बारtamping_स्थिरants(crtc, &crtc->mode);

	hrसमयr_init(&out->vblank_hrसमयr, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	out->vblank_hrसमयr.function = &vkms_vblank_simulate;
	out->period_ns = kसमय_set(0, vblank->framedur_ns);
	hrसमयr_start(&out->vblank_hrसमयr, out->period_ns, HRTIMER_MODE_REL);

	वापस 0;
पूर्ण

अटल व्योम vkms_disable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा vkms_output *out = drm_crtc_to_vkms_output(crtc);

	hrसमयr_cancel(&out->vblank_hrसमयr);
पूर्ण

अटल bool vkms_get_vblank_बारtamp(काष्ठा drm_crtc *crtc,
				      पूर्णांक *max_error, kसमय_प्रकार *vblank_समय,
				      bool in_vblank_irq)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	अचिन्हित पूर्णांक pipe = crtc->index;
	काष्ठा vkms_device *vkmsdev = drm_device_to_vkms_device(dev);
	काष्ठा vkms_output *output = &vkmsdev->output;
	काष्ठा drm_vblank_crtc *vblank = &dev->vblank[pipe];

	अगर (!READ_ONCE(vblank->enabled)) अणु
		*vblank_समय = kसमय_get();
		वापस true;
	पूर्ण

	*vblank_समय = READ_ONCE(output->vblank_hrसमयr.node.expires);

	अगर (WARN_ON(*vblank_समय == vblank->समय))
		वापस true;

	/*
	 * To prevent races we roll the hrसमयr क्रमward beक्रमe we करो any
	 * पूर्णांकerrupt processing - this is how real hw works (the पूर्णांकerrupt is
	 * only generated after all the vblank रेजिस्टरs are updated) and what
	 * the vblank core expects. Thereक्रमe we need to always correct the
	 * बारtampe by one frame.
	 */
	*vblank_समय -= output->period_ns;

	वापस true;
पूर्ण

अटल काष्ठा drm_crtc_state *
vkms_atomic_crtc_duplicate_state(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा vkms_crtc_state *vkms_state;

	अगर (WARN_ON(!crtc->state))
		वापस शून्य;

	vkms_state = kzalloc(माप(*vkms_state), GFP_KERNEL);
	अगर (!vkms_state)
		वापस शून्य;

	__drm_atomic_helper_crtc_duplicate_state(crtc, &vkms_state->base);

	INIT_WORK(&vkms_state->composer_work, vkms_composer_worker);

	वापस &vkms_state->base;
पूर्ण

अटल व्योम vkms_atomic_crtc_destroy_state(काष्ठा drm_crtc *crtc,
					   काष्ठा drm_crtc_state *state)
अणु
	काष्ठा vkms_crtc_state *vkms_state = to_vkms_crtc_state(state);

	__drm_atomic_helper_crtc_destroy_state(state);

	WARN_ON(work_pending(&vkms_state->composer_work));
	kमुक्त(vkms_state->active_planes);
	kमुक्त(vkms_state);
पूर्ण

अटल व्योम vkms_atomic_crtc_reset(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा vkms_crtc_state *vkms_state =
		kzalloc(माप(*vkms_state), GFP_KERNEL);

	अगर (crtc->state)
		vkms_atomic_crtc_destroy_state(crtc, crtc->state);

	__drm_atomic_helper_crtc_reset(crtc, &vkms_state->base);
	अगर (vkms_state)
		INIT_WORK(&vkms_state->composer_work, vkms_composer_worker);
पूर्ण

अटल स्थिर काष्ठा drm_crtc_funcs vkms_crtc_funcs = अणु
	.set_config             = drm_atomic_helper_set_config,
	.destroy                = drm_crtc_cleanup,
	.page_flip              = drm_atomic_helper_page_flip,
	.reset                  = vkms_atomic_crtc_reset,
	.atomic_duplicate_state = vkms_atomic_crtc_duplicate_state,
	.atomic_destroy_state   = vkms_atomic_crtc_destroy_state,
	.enable_vblank		= vkms_enable_vblank,
	.disable_vblank		= vkms_disable_vblank,
	.get_vblank_बारtamp	= vkms_get_vblank_बारtamp,
	.get_crc_sources	= vkms_get_crc_sources,
	.set_crc_source		= vkms_set_crc_source,
	.verअगरy_crc_source	= vkms_verअगरy_crc_source,
पूर्ण;

अटल पूर्णांक vkms_crtc_atomic_check(काष्ठा drm_crtc *crtc,
				  काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc_state *crtc_state = drm_atomic_get_new_crtc_state(state,
									  crtc);
	काष्ठा vkms_crtc_state *vkms_state = to_vkms_crtc_state(crtc_state);
	काष्ठा drm_plane *plane;
	काष्ठा drm_plane_state *plane_state;
	पूर्णांक i = 0, ret;

	अगर (vkms_state->active_planes)
		वापस 0;

	ret = drm_atomic_add_affected_planes(crtc_state->state, crtc);
	अगर (ret < 0)
		वापस ret;

	drm_क्रम_each_plane_mask(plane, crtc->dev, crtc_state->plane_mask) अणु
		plane_state = drm_atomic_get_existing_plane_state(crtc_state->state,
								  plane);
		WARN_ON(!plane_state);

		अगर (!plane_state->visible)
			जारी;

		i++;
	पूर्ण

	vkms_state->active_planes = kसुस्मृति(i, माप(plane), GFP_KERNEL);
	अगर (!vkms_state->active_planes)
		वापस -ENOMEM;
	vkms_state->num_active_planes = i;

	i = 0;
	drm_क्रम_each_plane_mask(plane, crtc->dev, crtc_state->plane_mask) अणु
		plane_state = drm_atomic_get_existing_plane_state(crtc_state->state,
								  plane);

		अगर (!plane_state->visible)
			जारी;

		vkms_state->active_planes[i++] =
			to_vkms_plane_state(plane_state);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम vkms_crtc_atomic_enable(काष्ठा drm_crtc *crtc,
				    काष्ठा drm_atomic_state *state)
अणु
	drm_crtc_vblank_on(crtc);
पूर्ण

अटल व्योम vkms_crtc_atomic_disable(काष्ठा drm_crtc *crtc,
				     काष्ठा drm_atomic_state *state)
अणु
	drm_crtc_vblank_off(crtc);
पूर्ण

अटल व्योम vkms_crtc_atomic_begin(काष्ठा drm_crtc *crtc,
				   काष्ठा drm_atomic_state *state)
अणु
	काष्ठा vkms_output *vkms_output = drm_crtc_to_vkms_output(crtc);

	/* This lock is held across the atomic commit to block vblank समयr
	 * from scheduling vkms_composer_worker until the composer is updated
	 */
	spin_lock_irq(&vkms_output->lock);
पूर्ण

अटल व्योम vkms_crtc_atomic_flush(काष्ठा drm_crtc *crtc,
				   काष्ठा drm_atomic_state *state)
अणु
	काष्ठा vkms_output *vkms_output = drm_crtc_to_vkms_output(crtc);

	अगर (crtc->state->event) अणु
		spin_lock(&crtc->dev->event_lock);

		अगर (drm_crtc_vblank_get(crtc) != 0)
			drm_crtc_send_vblank_event(crtc, crtc->state->event);
		अन्यथा
			drm_crtc_arm_vblank_event(crtc, crtc->state->event);

		spin_unlock(&crtc->dev->event_lock);

		crtc->state->event = शून्य;
	पूर्ण

	vkms_output->composer_state = to_vkms_crtc_state(crtc->state);

	spin_unlock_irq(&vkms_output->lock);
पूर्ण

अटल स्थिर काष्ठा drm_crtc_helper_funcs vkms_crtc_helper_funcs = अणु
	.atomic_check	= vkms_crtc_atomic_check,
	.atomic_begin	= vkms_crtc_atomic_begin,
	.atomic_flush	= vkms_crtc_atomic_flush,
	.atomic_enable	= vkms_crtc_atomic_enable,
	.atomic_disable	= vkms_crtc_atomic_disable,
पूर्ण;

पूर्णांक vkms_crtc_init(काष्ठा drm_device *dev, काष्ठा drm_crtc *crtc,
		   काष्ठा drm_plane *primary, काष्ठा drm_plane *cursor)
अणु
	काष्ठा vkms_output *vkms_out = drm_crtc_to_vkms_output(crtc);
	पूर्णांक ret;

	ret = drm_crtc_init_with_planes(dev, crtc, primary, cursor,
					&vkms_crtc_funcs, शून्य);
	अगर (ret) अणु
		DRM_ERROR("Failed to init CRTC\n");
		वापस ret;
	पूर्ण

	drm_crtc_helper_add(crtc, &vkms_crtc_helper_funcs);

	spin_lock_init(&vkms_out->lock);
	spin_lock_init(&vkms_out->composer_lock);

	vkms_out->composer_workq = alloc_ordered_workqueue("vkms_composer", 0);
	अगर (!vkms_out->composer_workq)
		वापस -ENOMEM;

	वापस ret;
पूर्ण
