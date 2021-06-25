<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * (C) COPYRIGHT 2018 ARM Limited. All rights reserved.
 * Author: James.Qian.Wang <james.qian.wang@arm.com>
 *
 */
#समावेश <linux/clk.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/spinlock.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_crtc_helper.h>
#समावेश <drm/drm_plane_helper.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_vblank.h>

#समावेश "komeda_dev.h"
#समावेश "komeda_kms.h"

व्योम komeda_crtc_get_color_config(काष्ठा drm_crtc_state *crtc_st,
				  u32 *color_depths, u32 *color_क्रमmats)
अणु
	काष्ठा drm_connector *conn;
	काष्ठा drm_connector_state *conn_st;
	u32 conn_color_क्रमmats = ~0u;
	पूर्णांक i, min_bpc = 31, conn_bpc = 0;

	क्रम_each_new_connector_in_state(crtc_st->state, conn, conn_st, i) अणु
		अगर (conn_st->crtc != crtc_st->crtc)
			जारी;

		conn_bpc = conn->display_info.bpc ? conn->display_info.bpc : 8;
		conn_color_क्रमmats &= conn->display_info.color_क्रमmats;

		अगर (conn_bpc < min_bpc)
			min_bpc = conn_bpc;
	पूर्ण

	/* connector करोesn't config any color_क्रमmat, use RGB444 as शेष */
	अगर (!conn_color_क्रमmats)
		conn_color_क्रमmats = DRM_COLOR_FORMAT_RGB444;

	*color_depths = GENMASK(min_bpc, 0);
	*color_क्रमmats = conn_color_क्रमmats;
पूर्ण

अटल व्योम komeda_crtc_update_घड़ी_ratio(काष्ठा komeda_crtc_state *kcrtc_st)
अणु
	u64 pxlclk, aclk;

	अगर (!kcrtc_st->base.active) अणु
		kcrtc_st->घड़ी_ratio = 0;
		वापस;
	पूर्ण

	pxlclk = kcrtc_st->base.adjusted_mode.crtc_घड़ी * 1000ULL;
	aclk = komeda_crtc_get_aclk(kcrtc_st);

	kcrtc_st->घड़ी_ratio = भाग64_u64(aclk << 32, pxlclk);
पूर्ण

/**
 * komeda_crtc_atomic_check - build display output data flow
 * @crtc: DRM crtc
 * @state: the crtc state object
 *
 * crtc_atomic_check is the final check stage, so beside build a display data
 * pipeline according to the crtc_state, but still needs to release or disable
 * the unclaimed pipeline resources.
 *
 * RETURNS:
 * Zero क्रम success or -त्रुटि_सं
 */
अटल पूर्णांक
komeda_crtc_atomic_check(काष्ठा drm_crtc *crtc,
			 काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc_state *crtc_state = drm_atomic_get_new_crtc_state(state,
									  crtc);
	काष्ठा komeda_crtc *kcrtc = to_kcrtc(crtc);
	काष्ठा komeda_crtc_state *kcrtc_st = to_kcrtc_st(crtc_state);
	पूर्णांक err;

	अगर (drm_atomic_crtc_needs_modeset(crtc_state))
		komeda_crtc_update_घड़ी_ratio(kcrtc_st);

	अगर (crtc_state->active) अणु
		err = komeda_build_display_data_flow(kcrtc, kcrtc_st);
		अगर (err)
			वापस err;
	पूर्ण

	/* release unclaimed pipeline resources */
	err = komeda_release_unclaimed_resources(kcrtc->slave, kcrtc_st);
	अगर (err)
		वापस err;

	err = komeda_release_unclaimed_resources(kcrtc->master, kcrtc_st);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

/* For active a crtc, मुख्यly need two parts of preparation
 * 1. adjust display operation mode.
 * 2. enable needed clk
 */
अटल पूर्णांक
komeda_crtc_prepare(काष्ठा komeda_crtc *kcrtc)
अणु
	काष्ठा komeda_dev *mdev = kcrtc->base.dev->dev_निजी;
	काष्ठा komeda_pipeline *master = kcrtc->master;
	काष्ठा komeda_crtc_state *kcrtc_st = to_kcrtc_st(kcrtc->base.state);
	काष्ठा drm_display_mode *mode = &kcrtc_st->base.adjusted_mode;
	u32 new_mode;
	पूर्णांक err;

	mutex_lock(&mdev->lock);

	new_mode = mdev->dpmode | BIT(master->id);
	अगर (WARN_ON(new_mode == mdev->dpmode)) अणु
		err = 0;
		जाओ unlock;
	पूर्ण

	err = mdev->funcs->change_opmode(mdev, new_mode);
	अगर (err) अणु
		DRM_ERROR("failed to change opmode: 0x%x -> 0x%x.\n,",
			  mdev->dpmode, new_mode);
		जाओ unlock;
	पूर्ण

	mdev->dpmode = new_mode;
	/* Only need to enable aclk on single display mode, but no need to
	 * enable aclk it on dual display mode, since the dual mode always
	 * चयन from single display mode, the aclk alपढ़ोy enabled, no need
	 * to enable it again.
	 */
	अगर (new_mode != KOMEDA_MODE_DUAL_DISP) अणु
		err = clk_set_rate(mdev->aclk, komeda_crtc_get_aclk(kcrtc_st));
		अगर (err)
			DRM_ERROR("failed to set aclk.\n");
		err = clk_prepare_enable(mdev->aclk);
		अगर (err)
			DRM_ERROR("failed to enable aclk.\n");
	पूर्ण

	err = clk_set_rate(master->pxlclk, mode->crtc_घड़ी * 1000);
	अगर (err)
		DRM_ERROR("failed to set pxlclk for pipe%d\n", master->id);
	err = clk_prepare_enable(master->pxlclk);
	अगर (err)
		DRM_ERROR("failed to enable pxl clk for pipe%d.\n", master->id);

unlock:
	mutex_unlock(&mdev->lock);

	वापस err;
पूर्ण

अटल पूर्णांक
komeda_crtc_unprepare(काष्ठा komeda_crtc *kcrtc)
अणु
	काष्ठा komeda_dev *mdev = kcrtc->base.dev->dev_निजी;
	काष्ठा komeda_pipeline *master = kcrtc->master;
	u32 new_mode;
	पूर्णांक err;

	mutex_lock(&mdev->lock);

	new_mode = mdev->dpmode & (~BIT(master->id));

	अगर (WARN_ON(new_mode == mdev->dpmode)) अणु
		err = 0;
		जाओ unlock;
	पूर्ण

	err = mdev->funcs->change_opmode(mdev, new_mode);
	अगर (err) अणु
		DRM_ERROR("failed to change opmode: 0x%x -> 0x%x.\n,",
			  mdev->dpmode, new_mode);
		जाओ unlock;
	पूर्ण

	mdev->dpmode = new_mode;

	clk_disable_unprepare(master->pxlclk);
	अगर (new_mode == KOMEDA_MODE_INACTIVE)
		clk_disable_unprepare(mdev->aclk);

unlock:
	mutex_unlock(&mdev->lock);

	वापस err;
पूर्ण

व्योम komeda_crtc_handle_event(काष्ठा komeda_crtc   *kcrtc,
			      काष्ठा komeda_events *evts)
अणु
	काष्ठा drm_crtc *crtc = &kcrtc->base;
	u32 events = evts->pipes[kcrtc->master->id];

	अगर (events & KOMEDA_EVENT_VSYNC)
		drm_crtc_handle_vblank(crtc);

	अगर (events & KOMEDA_EVENT_EOW) अणु
		काष्ठा komeda_wb_connector *wb_conn = kcrtc->wb_conn;

		अगर (wb_conn)
			drm_ग_लिखोback_संकेत_completion(&wb_conn->base, 0);
		अन्यथा
			DRM_WARN("CRTC[%d]: EOW happen but no wb_connector.\n",
				 drm_crtc_index(&kcrtc->base));
	पूर्ण
	/* will handle it together with the ग_लिखो back support */
	अगर (events & KOMEDA_EVENT_EOW)
		DRM_DEBUG("EOW.\n");

	अगर (events & KOMEDA_EVENT_FLIP) अणु
		अचिन्हित दीर्घ flags;
		काष्ठा drm_pending_vblank_event *event;

		spin_lock_irqsave(&crtc->dev->event_lock, flags);
		अगर (kcrtc->disable_करोne) अणु
			complete_all(kcrtc->disable_करोne);
			kcrtc->disable_करोne = शून्य;
		पूर्ण अन्यथा अगर (crtc->state->event) अणु
			event = crtc->state->event;
			/*
			 * Consume event beक्रमe notअगरying drm core that flip
			 * happened.
			 */
			crtc->state->event = शून्य;
			drm_crtc_send_vblank_event(crtc, event);
		पूर्ण अन्यथा अणु
			DRM_WARN("CRTC[%d]: FLIP happen but no pending commit.\n",
				 drm_crtc_index(&kcrtc->base));
		पूर्ण
		spin_unlock_irqrestore(&crtc->dev->event_lock, flags);
	पूर्ण
पूर्ण

अटल व्योम
komeda_crtc_करो_flush(काष्ठा drm_crtc *crtc,
		     काष्ठा drm_crtc_state *old)
अणु
	काष्ठा komeda_crtc *kcrtc = to_kcrtc(crtc);
	काष्ठा komeda_crtc_state *kcrtc_st = to_kcrtc_st(crtc->state);
	काष्ठा komeda_dev *mdev = kcrtc->base.dev->dev_निजी;
	काष्ठा komeda_pipeline *master = kcrtc->master;
	काष्ठा komeda_pipeline *slave = kcrtc->slave;
	काष्ठा komeda_wb_connector *wb_conn = kcrtc->wb_conn;
	काष्ठा drm_connector_state *conn_st;

	DRM_DEBUG_ATOMIC("CRTC%d_FLUSH: active_pipes: 0x%x, affected: 0x%x.\n",
			 drm_crtc_index(crtc),
			 kcrtc_st->active_pipes, kcrtc_st->affected_pipes);

	/* step 1: update the pipeline/component state to HW */
	अगर (has_bit(master->id, kcrtc_st->affected_pipes))
		komeda_pipeline_update(master, old->state);

	अगर (slave && has_bit(slave->id, kcrtc_st->affected_pipes))
		komeda_pipeline_update(slave, old->state);

	conn_st = wb_conn ? wb_conn->base.base.state : शून्य;
	अगर (conn_st && conn_st->ग_लिखोback_job)
		drm_ग_लिखोback_queue_job(&wb_conn->base, conn_st);

	/* step 2: notअगरy the HW to kickoff the update */
	mdev->funcs->flush(mdev, master->id, kcrtc_st->active_pipes);
पूर्ण

अटल व्योम
komeda_crtc_atomic_enable(काष्ठा drm_crtc *crtc,
			  काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc_state *old = drm_atomic_get_old_crtc_state(state,
								   crtc);
	pm_runसमय_get_sync(crtc->dev->dev);
	komeda_crtc_prepare(to_kcrtc(crtc));
	drm_crtc_vblank_on(crtc);
	WARN_ON(drm_crtc_vblank_get(crtc));
	komeda_crtc_करो_flush(crtc, old);
पूर्ण

अटल व्योम
komeda_crtc_flush_and_रुको_क्रम_flip_करोne(काष्ठा komeda_crtc *kcrtc,
					 काष्ठा completion *input_flip_करोne)
अणु
	काष्ठा drm_device *drm = kcrtc->base.dev;
	काष्ठा komeda_dev *mdev = kcrtc->master->mdev;
	काष्ठा completion *flip_करोne;
	काष्ठा completion temp;
	पूर्णांक समयout;

	/* अगर caller करोesn't send a flip_करोne, use a निजी flip_करोne */
	अगर (input_flip_करोne) अणु
		flip_करोne = input_flip_करोne;
	पूर्ण अन्यथा अणु
		init_completion(&temp);
		kcrtc->disable_करोne = &temp;
		flip_करोne = &temp;
	पूर्ण

	mdev->funcs->flush(mdev, kcrtc->master->id, 0);

	/* रुको the flip take affect.*/
	समयout = रुको_क्रम_completion_समयout(flip_करोne, HZ);
	अगर (समयout == 0) अणु
		DRM_ERROR("wait pipe%d flip done timeout\n", kcrtc->master->id);
		अगर (!input_flip_करोne) अणु
			अचिन्हित दीर्घ flags;

			spin_lock_irqsave(&drm->event_lock, flags);
			kcrtc->disable_करोne = शून्य;
			spin_unlock_irqrestore(&drm->event_lock, flags);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
komeda_crtc_atomic_disable(काष्ठा drm_crtc *crtc,
			   काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc_state *old = drm_atomic_get_old_crtc_state(state,
								   crtc);
	काष्ठा komeda_crtc *kcrtc = to_kcrtc(crtc);
	काष्ठा komeda_crtc_state *old_st = to_kcrtc_st(old);
	काष्ठा komeda_pipeline *master = kcrtc->master;
	काष्ठा komeda_pipeline *slave  = kcrtc->slave;
	काष्ठा completion *disable_करोne;
	bool needs_phase2 = false;

	DRM_DEBUG_ATOMIC("CRTC%d_DISABLE: active_pipes: 0x%x, affected: 0x%x\n",
			 drm_crtc_index(crtc),
			 old_st->active_pipes, old_st->affected_pipes);

	अगर (slave && has_bit(slave->id, old_st->active_pipes))
		komeda_pipeline_disable(slave, old->state);

	अगर (has_bit(master->id, old_st->active_pipes))
		needs_phase2 = komeda_pipeline_disable(master, old->state);

	/* crtc_disable has two scenarios according to the state->active चयन.
	 * 1. active -> inactive
	 *    this commit is a disable commit. and the commit will be finished
	 *    or करोne after the disable operation. on this हाल we can directly
	 *    use the crtc->state->event to tracking the HW disable operation.
	 * 2. active -> active
	 *    the crtc->commit is not क्रम disable, but a modeset operation when
	 *    crtc is active, such commit actually has been completed by 3
	 *    DRM operations:
	 *    crtc_disable, update_planes(crtc_flush), crtc_enable
	 *    so on this हाल the crtc->commit is क्रम the whole process.
	 *    we can not use it क्रम tracing the disable, we need a temporary
	 *    flip_करोne क्रम tracing the disable. and crtc->state->event क्रम
	 *    the crtc_enable operation.
	 *    That's also the reason why skip modeset commit in
	 *    komeda_crtc_atomic_flush()
	 */
	disable_करोne = (needs_phase2 || crtc->state->active) ?
		       शून्य : &crtc->state->commit->flip_करोne;

	/* रुको phase 1 disable करोne */
	komeda_crtc_flush_and_रुको_क्रम_flip_करोne(kcrtc, disable_करोne);

	/* phase 2 */
	अगर (needs_phase2) अणु
		komeda_pipeline_disable(kcrtc->master, old->state);

		disable_करोne = crtc->state->active ?
			       शून्य : &crtc->state->commit->flip_करोne;

		komeda_crtc_flush_and_रुको_क्रम_flip_करोne(kcrtc, disable_करोne);
	पूर्ण

	drm_crtc_vblank_put(crtc);
	drm_crtc_vblank_off(crtc);
	komeda_crtc_unprepare(kcrtc);
	pm_runसमय_put(crtc->dev->dev);
पूर्ण

अटल व्योम
komeda_crtc_atomic_flush(काष्ठा drm_crtc *crtc,
			 काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc_state *crtc_state = drm_atomic_get_new_crtc_state(state,
									  crtc);
	काष्ठा drm_crtc_state *old = drm_atomic_get_old_crtc_state(state,
								   crtc);
	/* commit with modeset will be handled in enable/disable */
	अगर (drm_atomic_crtc_needs_modeset(crtc_state))
		वापस;

	komeda_crtc_करो_flush(crtc, old);
पूर्ण

/* Returns the minimum frequency of the aclk rate (मुख्य engine घड़ी) in Hz */
अटल अचिन्हित दीर्घ
komeda_calc_min_aclk_rate(काष्ठा komeda_crtc *kcrtc,
			  अचिन्हित दीर्घ pxlclk)
अणु
	/* Once dual-link one display pipeline drives two display outमाला_दो,
	 * the aclk needs run on the द्विगुन rate of pxlclk
	 */
	अगर (kcrtc->master->dual_link)
		वापस pxlclk * 2;
	अन्यथा
		वापस pxlclk;
पूर्ण

/* Get current aclk rate that specअगरied by state */
अचिन्हित दीर्घ komeda_crtc_get_aclk(काष्ठा komeda_crtc_state *kcrtc_st)
अणु
	काष्ठा drm_crtc *crtc = kcrtc_st->base.crtc;
	काष्ठा komeda_dev *mdev = crtc->dev->dev_निजी;
	अचिन्हित दीर्घ pxlclk = kcrtc_st->base.adjusted_mode.crtc_घड़ी * 1000;
	अचिन्हित दीर्घ min_aclk;

	min_aclk = komeda_calc_min_aclk_rate(to_kcrtc(crtc), pxlclk);

	वापस clk_round_rate(mdev->aclk, min_aclk);
पूर्ण

अटल क्रमागत drm_mode_status
komeda_crtc_mode_valid(काष्ठा drm_crtc *crtc, स्थिर काष्ठा drm_display_mode *m)
अणु
	काष्ठा komeda_dev *mdev = crtc->dev->dev_निजी;
	काष्ठा komeda_crtc *kcrtc = to_kcrtc(crtc);
	काष्ठा komeda_pipeline *master = kcrtc->master;
	अचिन्हित दीर्घ min_pxlclk, min_aclk;

	अगर (m->flags & DRM_MODE_FLAG_INTERLACE)
		वापस MODE_NO_INTERLACE;

	min_pxlclk = m->घड़ी * 1000;
	अगर (master->dual_link)
		min_pxlclk /= 2;

	अगर (min_pxlclk != clk_round_rate(master->pxlclk, min_pxlclk)) अणु
		DRM_DEBUG_ATOMIC("pxlclk doesn't support %lu Hz\n", min_pxlclk);

		वापस MODE_NOCLOCK;
	पूर्ण

	min_aclk = komeda_calc_min_aclk_rate(to_kcrtc(crtc), min_pxlclk);
	अगर (clk_round_rate(mdev->aclk, min_aclk) < min_aclk) अणु
		DRM_DEBUG_ATOMIC("engine clk can't satisfy the requirement of %s-clk: %lu.\n",
				 m->name, min_pxlclk);

		वापस MODE_CLOCK_HIGH;
	पूर्ण

	वापस MODE_OK;
पूर्ण

अटल bool komeda_crtc_mode_fixup(काष्ठा drm_crtc *crtc,
				   स्थिर काष्ठा drm_display_mode *m,
				   काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा komeda_crtc *kcrtc = to_kcrtc(crtc);
	अचिन्हित दीर्घ clk_rate;

	drm_mode_set_crtcinfo(adjusted_mode, 0);
	/* In dual link half the horizontal settings */
	अगर (kcrtc->master->dual_link) अणु
		adjusted_mode->crtc_घड़ी /= 2;
		adjusted_mode->crtc_hdisplay /= 2;
		adjusted_mode->crtc_hsync_start /= 2;
		adjusted_mode->crtc_hsync_end /= 2;
		adjusted_mode->crtc_htotal /= 2;
	पूर्ण

	clk_rate = adjusted_mode->crtc_घड़ी * 1000;
	/* crtc_घड़ी will be used as the komeda output pixel घड़ी */
	adjusted_mode->crtc_घड़ी = clk_round_rate(kcrtc->master->pxlclk,
						   clk_rate) / 1000;

	वापस true;
पूर्ण

अटल स्थिर काष्ठा drm_crtc_helper_funcs komeda_crtc_helper_funcs = अणु
	.atomic_check	= komeda_crtc_atomic_check,
	.atomic_flush	= komeda_crtc_atomic_flush,
	.atomic_enable	= komeda_crtc_atomic_enable,
	.atomic_disable	= komeda_crtc_atomic_disable,
	.mode_valid	= komeda_crtc_mode_valid,
	.mode_fixup	= komeda_crtc_mode_fixup,
पूर्ण;

अटल व्योम komeda_crtc_reset(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा komeda_crtc_state *state;

	अगर (crtc->state)
		__drm_atomic_helper_crtc_destroy_state(crtc->state);

	kमुक्त(to_kcrtc_st(crtc->state));
	crtc->state = शून्य;

	state = kzalloc(माप(*state), GFP_KERNEL);
	अगर (state)
		__drm_atomic_helper_crtc_reset(crtc, &state->base);
पूर्ण

अटल काष्ठा drm_crtc_state *
komeda_crtc_atomic_duplicate_state(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा komeda_crtc_state *old = to_kcrtc_st(crtc->state);
	काष्ठा komeda_crtc_state *new;

	new = kzalloc(माप(*new), GFP_KERNEL);
	अगर (!new)
		वापस शून्य;

	__drm_atomic_helper_crtc_duplicate_state(crtc, &new->base);

	new->affected_pipes = old->active_pipes;
	new->घड़ी_ratio = old->घड़ी_ratio;
	new->max_slave_zorder = old->max_slave_zorder;

	वापस &new->base;
पूर्ण

अटल व्योम komeda_crtc_atomic_destroy_state(काष्ठा drm_crtc *crtc,
					     काष्ठा drm_crtc_state *state)
अणु
	__drm_atomic_helper_crtc_destroy_state(state);
	kमुक्त(to_kcrtc_st(state));
पूर्ण

अटल पूर्णांक komeda_crtc_vblank_enable(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा komeda_dev *mdev = crtc->dev->dev_निजी;
	काष्ठा komeda_crtc *kcrtc = to_kcrtc(crtc);

	mdev->funcs->on_off_vblank(mdev, kcrtc->master->id, true);
	वापस 0;
पूर्ण

अटल व्योम komeda_crtc_vblank_disable(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा komeda_dev *mdev = crtc->dev->dev_निजी;
	काष्ठा komeda_crtc *kcrtc = to_kcrtc(crtc);

	mdev->funcs->on_off_vblank(mdev, kcrtc->master->id, false);
पूर्ण

अटल स्थिर काष्ठा drm_crtc_funcs komeda_crtc_funcs = अणु
	.destroy		= drm_crtc_cleanup,
	.set_config		= drm_atomic_helper_set_config,
	.page_flip		= drm_atomic_helper_page_flip,
	.reset			= komeda_crtc_reset,
	.atomic_duplicate_state	= komeda_crtc_atomic_duplicate_state,
	.atomic_destroy_state	= komeda_crtc_atomic_destroy_state,
	.enable_vblank		= komeda_crtc_vblank_enable,
	.disable_vblank		= komeda_crtc_vblank_disable,
पूर्ण;

पूर्णांक komeda_kms_setup_crtcs(काष्ठा komeda_kms_dev *kms,
			   काष्ठा komeda_dev *mdev)
अणु
	काष्ठा komeda_crtc *crtc;
	काष्ठा komeda_pipeline *master;
	अक्षर str[16];
	पूर्णांक i;

	kms->n_crtcs = 0;

	क्रम (i = 0; i < mdev->n_pipelines; i++) अणु
		crtc = &kms->crtcs[kms->n_crtcs];
		master = mdev->pipelines[i];

		crtc->master = master;
		crtc->slave  = komeda_pipeline_get_slave(master);

		अगर (crtc->slave)
			प्र_लिखो(str, "pipe-%d", crtc->slave->id);
		अन्यथा
			प्र_लिखो(str, "None");

		DRM_INFO("CRTC-%d: master(pipe-%d) slave(%s).\n",
			 kms->n_crtcs, master->id, str);

		kms->n_crtcs++;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा drm_plane *
get_crtc_primary(काष्ठा komeda_kms_dev *kms, काष्ठा komeda_crtc *crtc)
अणु
	काष्ठा komeda_plane *kplane;
	काष्ठा drm_plane *plane;

	drm_क्रम_each_plane(plane, &kms->base) अणु
		अगर (plane->type != DRM_PLANE_TYPE_PRIMARY)
			जारी;

		kplane = to_kplane(plane);
		/* only master can be primary */
		अगर (kplane->layer->base.pipeline == crtc->master)
			वापस plane;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक komeda_crtc_add(काष्ठा komeda_kms_dev *kms,
			   काष्ठा komeda_crtc *kcrtc)
अणु
	काष्ठा drm_crtc *crtc = &kcrtc->base;
	पूर्णांक err;

	err = drm_crtc_init_with_planes(&kms->base, crtc,
					get_crtc_primary(kms, kcrtc), शून्य,
					&komeda_crtc_funcs, शून्य);
	अगर (err)
		वापस err;

	drm_crtc_helper_add(crtc, &komeda_crtc_helper_funcs);

	crtc->port = kcrtc->master->of_output_port;

	drm_crtc_enable_color_mgmt(crtc, 0, true, KOMEDA_COLOR_LUT_SIZE);

	वापस err;
पूर्ण

पूर्णांक komeda_kms_add_crtcs(काष्ठा komeda_kms_dev *kms, काष्ठा komeda_dev *mdev)
अणु
	पूर्णांक i, err;

	क्रम (i = 0; i < kms->n_crtcs; i++) अणु
		err = komeda_crtc_add(kms, &kms->crtcs[i]);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण
