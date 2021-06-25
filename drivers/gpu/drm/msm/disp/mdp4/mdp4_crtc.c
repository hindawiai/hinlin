<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2013 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 */

#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_flip_work.h>
#समावेश <drm/drm_mode.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_vblank.h>

#समावेश "mdp4_kms.h"
#समावेश "msm_gem.h"

काष्ठा mdp4_crtc अणु
	काष्ठा drm_crtc base;
	अक्षर name[8];
	पूर्णांक id;
	पूर्णांक ovlp;
	क्रमागत mdp4_dma dma;
	bool enabled;

	/* which mixer/encoder we route output to: */
	पूर्णांक mixer;

	काष्ठा अणु
		spinlock_t lock;
		bool stale;
		uपूर्णांक32_t width, height;
		uपूर्णांक32_t x, y;

		/* next cursor to scan-out: */
		uपूर्णांक32_t next_iova;
		काष्ठा drm_gem_object *next_bo;

		/* current cursor being scanned out: */
		काष्ठा drm_gem_object *scanout_bo;
	पूर्ण cursor;


	/* अगर there is a pending flip, these will be non-null: */
	काष्ठा drm_pending_vblank_event *event;

	/* Bits have been flushed at the last commit,
	 * used to decide अगर a vsync has happened since last commit.
	 */
	u32 flushed_mask;

#घोषणा PENDING_CURSOR 0x1
#घोषणा PENDING_FLIP   0x2
	atomic_t pending;

	/* क्रम unref'ing cursor bo's after scanout completes: */
	काष्ठा drm_flip_work unref_cursor_work;

	काष्ठा mdp_irq vblank;
	काष्ठा mdp_irq err;
पूर्ण;
#घोषणा to_mdp4_crtc(x) container_of(x, काष्ठा mdp4_crtc, base)

अटल काष्ठा mdp4_kms *get_kms(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा msm_drm_निजी *priv = crtc->dev->dev_निजी;
	वापस to_mdp4_kms(to_mdp_kms(priv->kms));
पूर्ण

अटल व्योम request_pending(काष्ठा drm_crtc *crtc, uपूर्णांक32_t pending)
अणु
	काष्ठा mdp4_crtc *mdp4_crtc = to_mdp4_crtc(crtc);

	atomic_or(pending, &mdp4_crtc->pending);
	mdp_irq_रेजिस्टर(&get_kms(crtc)->base, &mdp4_crtc->vblank);
पूर्ण

अटल व्योम crtc_flush(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा mdp4_crtc *mdp4_crtc = to_mdp4_crtc(crtc);
	काष्ठा mdp4_kms *mdp4_kms = get_kms(crtc);
	काष्ठा drm_plane *plane;
	uपूर्णांक32_t flush = 0;

	drm_atomic_crtc_क्रम_each_plane(plane, crtc) अणु
		क्रमागत mdp4_pipe pipe_id = mdp4_plane_pipe(plane);
		flush |= pipe2flush(pipe_id);
	पूर्ण

	flush |= ovlp2flush(mdp4_crtc->ovlp);

	DBG("%s: flush=%08x", mdp4_crtc->name, flush);

	mdp4_crtc->flushed_mask = flush;

	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_OVERLAY_FLUSH, flush);
पूर्ण

/* अगर file!=शून्य, this is preबंद potential cancel-flip path */
अटल व्योम complete_flip(काष्ठा drm_crtc *crtc, काष्ठा drm_file *file)
अणु
	काष्ठा mdp4_crtc *mdp4_crtc = to_mdp4_crtc(crtc);
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा drm_pending_vblank_event *event;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->event_lock, flags);
	event = mdp4_crtc->event;
	अगर (event) अणु
		mdp4_crtc->event = शून्य;
		DBG("%s: send event: %p", mdp4_crtc->name, event);
		drm_crtc_send_vblank_event(crtc, event);
	पूर्ण
	spin_unlock_irqrestore(&dev->event_lock, flags);
पूर्ण

अटल व्योम unref_cursor_worker(काष्ठा drm_flip_work *work, व्योम *val)
अणु
	काष्ठा mdp4_crtc *mdp4_crtc =
		container_of(work, काष्ठा mdp4_crtc, unref_cursor_work);
	काष्ठा mdp4_kms *mdp4_kms = get_kms(&mdp4_crtc->base);
	काष्ठा msm_kms *kms = &mdp4_kms->base.base;

	msm_gem_unpin_iova(val, kms->aspace);
	drm_gem_object_put(val);
पूर्ण

अटल व्योम mdp4_crtc_destroy(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा mdp4_crtc *mdp4_crtc = to_mdp4_crtc(crtc);

	drm_crtc_cleanup(crtc);
	drm_flip_work_cleanup(&mdp4_crtc->unref_cursor_work);

	kमुक्त(mdp4_crtc);
पूर्ण

/* अटलally (क्रम now) map planes to mixer stage (z-order): */
अटल स्थिर पूर्णांक idxs[] = अणु
		[VG1]  = 1,
		[VG2]  = 2,
		[RGB1] = 0,
		[RGB2] = 0,
		[RGB3] = 0,
		[VG3]  = 3,
		[VG4]  = 4,

पूर्ण;

/* setup mixer config, क्रम which we need to consider all crtc's and
 * the planes attached to them
 *
 * TODO may possibly need some extra locking here
 */
अटल व्योम setup_mixer(काष्ठा mdp4_kms *mdp4_kms)
अणु
	काष्ठा drm_mode_config *config = &mdp4_kms->dev->mode_config;
	काष्ठा drm_crtc *crtc;
	uपूर्णांक32_t mixer_cfg = 0;
	अटल स्थिर क्रमागत mdp_mixer_stage_id stages[] = अणु
			STAGE_BASE, STAGE0, STAGE1, STAGE2, STAGE3,
	पूर्ण;

	list_क्रम_each_entry(crtc, &config->crtc_list, head) अणु
		काष्ठा mdp4_crtc *mdp4_crtc = to_mdp4_crtc(crtc);
		काष्ठा drm_plane *plane;

		drm_atomic_crtc_क्रम_each_plane(plane, crtc) अणु
			क्रमागत mdp4_pipe pipe_id = mdp4_plane_pipe(plane);
			पूर्णांक idx = idxs[pipe_id];
			mixer_cfg = mixercfg(mixer_cfg, mdp4_crtc->mixer,
					pipe_id, stages[idx]);
		पूर्ण
	पूर्ण

	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_LAYERMIXER_IN_CFG, mixer_cfg);
पूर्ण

अटल व्योम blend_setup(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा mdp4_crtc *mdp4_crtc = to_mdp4_crtc(crtc);
	काष्ठा mdp4_kms *mdp4_kms = get_kms(crtc);
	काष्ठा drm_plane *plane;
	पूर्णांक i, ovlp = mdp4_crtc->ovlp;
	bool alpha[4]= अणु false, false, false, false पूर्ण;

	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_OVLP_TRANSP_LOW0(ovlp), 0);
	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_OVLP_TRANSP_LOW1(ovlp), 0);
	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_OVLP_TRANSP_HIGH0(ovlp), 0);
	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_OVLP_TRANSP_HIGH1(ovlp), 0);

	drm_atomic_crtc_क्रम_each_plane(plane, crtc) अणु
		क्रमागत mdp4_pipe pipe_id = mdp4_plane_pipe(plane);
		पूर्णांक idx = idxs[pipe_id];
		अगर (idx > 0) अणु
			स्थिर काष्ठा mdp_क्रमmat *क्रमmat =
					to_mdp_क्रमmat(msm_framebuffer_क्रमmat(plane->state->fb));
			alpha[idx-1] = क्रमmat->alpha_enable;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < 4; i++) अणु
		uपूर्णांक32_t op;

		अगर (alpha[i]) अणु
			op = MDP4_OVLP_STAGE_OP_FG_ALPHA(FG_PIXEL) |
					MDP4_OVLP_STAGE_OP_BG_ALPHA(FG_PIXEL) |
					MDP4_OVLP_STAGE_OP_BG_INV_ALPHA;
		पूर्ण अन्यथा अणु
			op = MDP4_OVLP_STAGE_OP_FG_ALPHA(FG_CONST) |
					MDP4_OVLP_STAGE_OP_BG_ALPHA(BG_CONST);
		पूर्ण

		mdp4_ग_लिखो(mdp4_kms, REG_MDP4_OVLP_STAGE_FG_ALPHA(ovlp, i), 0xff);
		mdp4_ग_लिखो(mdp4_kms, REG_MDP4_OVLP_STAGE_BG_ALPHA(ovlp, i), 0x00);
		mdp4_ग_लिखो(mdp4_kms, REG_MDP4_OVLP_STAGE_OP(ovlp, i), op);
		mdp4_ग_लिखो(mdp4_kms, REG_MDP4_OVLP_STAGE_CO3(ovlp, i), 1);
		mdp4_ग_लिखो(mdp4_kms, REG_MDP4_OVLP_STAGE_TRANSP_LOW0(ovlp, i), 0);
		mdp4_ग_लिखो(mdp4_kms, REG_MDP4_OVLP_STAGE_TRANSP_LOW1(ovlp, i), 0);
		mdp4_ग_लिखो(mdp4_kms, REG_MDP4_OVLP_STAGE_TRANSP_HIGH0(ovlp, i), 0);
		mdp4_ग_लिखो(mdp4_kms, REG_MDP4_OVLP_STAGE_TRANSP_HIGH1(ovlp, i), 0);
	पूर्ण

	setup_mixer(mdp4_kms);
पूर्ण

अटल व्योम mdp4_crtc_mode_set_nofb(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा mdp4_crtc *mdp4_crtc = to_mdp4_crtc(crtc);
	काष्ठा mdp4_kms *mdp4_kms = get_kms(crtc);
	क्रमागत mdp4_dma dma = mdp4_crtc->dma;
	पूर्णांक ovlp = mdp4_crtc->ovlp;
	काष्ठा drm_display_mode *mode;

	अगर (WARN_ON(!crtc->state))
		वापस;

	mode = &crtc->state->adjusted_mode;

	DBG("%s: set mode: " DRM_MODE_FMT,
			mdp4_crtc->name, DRM_MODE_ARG(mode));

	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_DMA_SRC_SIZE(dma),
			MDP4_DMA_SRC_SIZE_WIDTH(mode->hdisplay) |
			MDP4_DMA_SRC_SIZE_HEIGHT(mode->vdisplay));

	/* take data from pipe: */
	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_DMA_SRC_BASE(dma), 0);
	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_DMA_SRC_STRIDE(dma), 0);
	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_DMA_DST_SIZE(dma),
			MDP4_DMA_DST_SIZE_WIDTH(0) |
			MDP4_DMA_DST_SIZE_HEIGHT(0));

	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_OVLP_BASE(ovlp), 0);
	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_OVLP_SIZE(ovlp),
			MDP4_OVLP_SIZE_WIDTH(mode->hdisplay) |
			MDP4_OVLP_SIZE_HEIGHT(mode->vdisplay));
	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_OVLP_STRIDE(ovlp), 0);

	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_OVLP_CFG(ovlp), 1);

	अगर (dma == DMA_E) अणु
		mdp4_ग_लिखो(mdp4_kms, REG_MDP4_DMA_E_QUANT(0), 0x00ff0000);
		mdp4_ग_लिखो(mdp4_kms, REG_MDP4_DMA_E_QUANT(1), 0x00ff0000);
		mdp4_ग_लिखो(mdp4_kms, REG_MDP4_DMA_E_QUANT(2), 0x00ff0000);
	पूर्ण
पूर्ण

अटल व्योम mdp4_crtc_atomic_disable(काष्ठा drm_crtc *crtc,
				     काष्ठा drm_atomic_state *state)
अणु
	काष्ठा mdp4_crtc *mdp4_crtc = to_mdp4_crtc(crtc);
	काष्ठा mdp4_kms *mdp4_kms = get_kms(crtc);

	DBG("%s", mdp4_crtc->name);

	अगर (WARN_ON(!mdp4_crtc->enabled))
		वापस;

	/* Disable/save vblank irq handling beक्रमe घातer is disabled */
	drm_crtc_vblank_off(crtc);

	mdp_irq_unरेजिस्टर(&mdp4_kms->base, &mdp4_crtc->err);
	mdp4_disable(mdp4_kms);

	mdp4_crtc->enabled = false;
पूर्ण

अटल व्योम mdp4_crtc_atomic_enable(काष्ठा drm_crtc *crtc,
				    काष्ठा drm_atomic_state *state)
अणु
	काष्ठा mdp4_crtc *mdp4_crtc = to_mdp4_crtc(crtc);
	काष्ठा mdp4_kms *mdp4_kms = get_kms(crtc);

	DBG("%s", mdp4_crtc->name);

	अगर (WARN_ON(mdp4_crtc->enabled))
		वापस;

	mdp4_enable(mdp4_kms);

	/* Restore vblank irq handling after घातer is enabled */
	drm_crtc_vblank_on(crtc);

	mdp_irq_रेजिस्टर(&mdp4_kms->base, &mdp4_crtc->err);

	crtc_flush(crtc);

	mdp4_crtc->enabled = true;
पूर्ण

अटल पूर्णांक mdp4_crtc_atomic_check(काष्ठा drm_crtc *crtc,
		काष्ठा drm_atomic_state *state)
अणु
	काष्ठा mdp4_crtc *mdp4_crtc = to_mdp4_crtc(crtc);
	DBG("%s: check", mdp4_crtc->name);
	// TODO anything अन्यथा to check?
	वापस 0;
पूर्ण

अटल व्योम mdp4_crtc_atomic_begin(काष्ठा drm_crtc *crtc,
				   काष्ठा drm_atomic_state *state)
अणु
	काष्ठा mdp4_crtc *mdp4_crtc = to_mdp4_crtc(crtc);
	DBG("%s: begin", mdp4_crtc->name);
पूर्ण

अटल व्योम mdp4_crtc_atomic_flush(काष्ठा drm_crtc *crtc,
				   काष्ठा drm_atomic_state *state)
अणु
	काष्ठा mdp4_crtc *mdp4_crtc = to_mdp4_crtc(crtc);
	काष्ठा drm_device *dev = crtc->dev;
	अचिन्हित दीर्घ flags;

	DBG("%s: event: %p", mdp4_crtc->name, crtc->state->event);

	WARN_ON(mdp4_crtc->event);

	spin_lock_irqsave(&dev->event_lock, flags);
	mdp4_crtc->event = crtc->state->event;
	crtc->state->event = शून्य;
	spin_unlock_irqrestore(&dev->event_lock, flags);

	blend_setup(crtc);
	crtc_flush(crtc);
	request_pending(crtc, PENDING_FLIP);
पूर्ण

#घोषणा CURSOR_WIDTH 64
#घोषणा CURSOR_HEIGHT 64

/* called from IRQ to update cursor related रेजिस्टरs (अगर needed).  The
 * cursor रेजिस्टरs, other than x/y position, appear not to be द्विगुन
 * buffered, and changing them other than from vblank seems to trigger
 * underflow.
 */
अटल व्योम update_cursor(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा mdp4_crtc *mdp4_crtc = to_mdp4_crtc(crtc);
	काष्ठा mdp4_kms *mdp4_kms = get_kms(crtc);
	काष्ठा msm_kms *kms = &mdp4_kms->base.base;
	क्रमागत mdp4_dma dma = mdp4_crtc->dma;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mdp4_crtc->cursor.lock, flags);
	अगर (mdp4_crtc->cursor.stale) अणु
		काष्ठा drm_gem_object *next_bo = mdp4_crtc->cursor.next_bo;
		काष्ठा drm_gem_object *prev_bo = mdp4_crtc->cursor.scanout_bo;
		uपूर्णांक64_t iova = mdp4_crtc->cursor.next_iova;

		अगर (next_bo) अणु
			/* take a obj ref + iova ref when we start scanning out: */
			drm_gem_object_get(next_bo);
			msm_gem_get_and_pin_iova(next_bo, kms->aspace, &iova);

			/* enable cursor: */
			mdp4_ग_लिखो(mdp4_kms, REG_MDP4_DMA_CURSOR_SIZE(dma),
					MDP4_DMA_CURSOR_SIZE_WIDTH(mdp4_crtc->cursor.width) |
					MDP4_DMA_CURSOR_SIZE_HEIGHT(mdp4_crtc->cursor.height));
			mdp4_ग_लिखो(mdp4_kms, REG_MDP4_DMA_CURSOR_BASE(dma), iova);
			mdp4_ग_लिखो(mdp4_kms, REG_MDP4_DMA_CURSOR_BLEND_CONFIG(dma),
					MDP4_DMA_CURSOR_BLEND_CONFIG_FORMAT(CURSOR_ARGB) |
					MDP4_DMA_CURSOR_BLEND_CONFIG_CURSOR_EN);
		पूर्ण अन्यथा अणु
			/* disable cursor: */
			mdp4_ग_लिखो(mdp4_kms, REG_MDP4_DMA_CURSOR_BASE(dma),
					mdp4_kms->blank_cursor_iova);
		पूर्ण

		/* and drop the iova ref + obj rev when करोne scanning out: */
		अगर (prev_bo)
			drm_flip_work_queue(&mdp4_crtc->unref_cursor_work, prev_bo);

		mdp4_crtc->cursor.scanout_bo = next_bo;
		mdp4_crtc->cursor.stale = false;
	पूर्ण

	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_DMA_CURSOR_POS(dma),
			MDP4_DMA_CURSOR_POS_X(mdp4_crtc->cursor.x) |
			MDP4_DMA_CURSOR_POS_Y(mdp4_crtc->cursor.y));

	spin_unlock_irqrestore(&mdp4_crtc->cursor.lock, flags);
पूर्ण

अटल पूर्णांक mdp4_crtc_cursor_set(काष्ठा drm_crtc *crtc,
		काष्ठा drm_file *file_priv, uपूर्णांक32_t handle,
		uपूर्णांक32_t width, uपूर्णांक32_t height)
अणु
	काष्ठा mdp4_crtc *mdp4_crtc = to_mdp4_crtc(crtc);
	काष्ठा mdp4_kms *mdp4_kms = get_kms(crtc);
	काष्ठा msm_kms *kms = &mdp4_kms->base.base;
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा drm_gem_object *cursor_bo, *old_bo;
	अचिन्हित दीर्घ flags;
	uपूर्णांक64_t iova;
	पूर्णांक ret;

	अगर ((width > CURSOR_WIDTH) || (height > CURSOR_HEIGHT)) अणु
		DRM_DEV_ERROR(dev->dev, "bad cursor size: %dx%d\n", width, height);
		वापस -EINVAL;
	पूर्ण

	अगर (handle) अणु
		cursor_bo = drm_gem_object_lookup(file_priv, handle);
		अगर (!cursor_bo)
			वापस -ENOENT;
	पूर्ण अन्यथा अणु
		cursor_bo = शून्य;
	पूर्ण

	अगर (cursor_bo) अणु
		ret = msm_gem_get_and_pin_iova(cursor_bo, kms->aspace, &iova);
		अगर (ret)
			जाओ fail;
	पूर्ण अन्यथा अणु
		iova = 0;
	पूर्ण

	spin_lock_irqsave(&mdp4_crtc->cursor.lock, flags);
	old_bo = mdp4_crtc->cursor.next_bo;
	mdp4_crtc->cursor.next_bo   = cursor_bo;
	mdp4_crtc->cursor.next_iova = iova;
	mdp4_crtc->cursor.width     = width;
	mdp4_crtc->cursor.height    = height;
	mdp4_crtc->cursor.stale     = true;
	spin_unlock_irqrestore(&mdp4_crtc->cursor.lock, flags);

	अगर (old_bo) अणु
		/* drop our previous reference: */
		drm_flip_work_queue(&mdp4_crtc->unref_cursor_work, old_bo);
	पूर्ण

	request_pending(crtc, PENDING_CURSOR);

	वापस 0;

fail:
	drm_gem_object_put(cursor_bo);
	वापस ret;
पूर्ण

अटल पूर्णांक mdp4_crtc_cursor_move(काष्ठा drm_crtc *crtc, पूर्णांक x, पूर्णांक y)
अणु
	काष्ठा mdp4_crtc *mdp4_crtc = to_mdp4_crtc(crtc);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mdp4_crtc->cursor.lock, flags);
	mdp4_crtc->cursor.x = x;
	mdp4_crtc->cursor.y = y;
	spin_unlock_irqrestore(&mdp4_crtc->cursor.lock, flags);

	crtc_flush(crtc);
	request_pending(crtc, PENDING_CURSOR);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_crtc_funcs mdp4_crtc_funcs = अणु
	.set_config = drm_atomic_helper_set_config,
	.destroy = mdp4_crtc_destroy,
	.page_flip = drm_atomic_helper_page_flip,
	.cursor_set = mdp4_crtc_cursor_set,
	.cursor_move = mdp4_crtc_cursor_move,
	.reset = drm_atomic_helper_crtc_reset,
	.atomic_duplicate_state = drm_atomic_helper_crtc_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_crtc_destroy_state,
	.enable_vblank  = msm_crtc_enable_vblank,
	.disable_vblank = msm_crtc_disable_vblank,
पूर्ण;

अटल स्थिर काष्ठा drm_crtc_helper_funcs mdp4_crtc_helper_funcs = अणु
	.mode_set_nofb = mdp4_crtc_mode_set_nofb,
	.atomic_check = mdp4_crtc_atomic_check,
	.atomic_begin = mdp4_crtc_atomic_begin,
	.atomic_flush = mdp4_crtc_atomic_flush,
	.atomic_enable = mdp4_crtc_atomic_enable,
	.atomic_disable = mdp4_crtc_atomic_disable,
पूर्ण;

अटल व्योम mdp4_crtc_vblank_irq(काष्ठा mdp_irq *irq, uपूर्णांक32_t irqstatus)
अणु
	काष्ठा mdp4_crtc *mdp4_crtc = container_of(irq, काष्ठा mdp4_crtc, vblank);
	काष्ठा drm_crtc *crtc = &mdp4_crtc->base;
	काष्ठा msm_drm_निजी *priv = crtc->dev->dev_निजी;
	अचिन्हित pending;

	mdp_irq_unरेजिस्टर(&get_kms(crtc)->base, &mdp4_crtc->vblank);

	pending = atomic_xchg(&mdp4_crtc->pending, 0);

	अगर (pending & PENDING_FLIP) अणु
		complete_flip(crtc, शून्य);
	पूर्ण

	अगर (pending & PENDING_CURSOR) अणु
		update_cursor(crtc);
		drm_flip_work_commit(&mdp4_crtc->unref_cursor_work, priv->wq);
	पूर्ण
पूर्ण

अटल व्योम mdp4_crtc_err_irq(काष्ठा mdp_irq *irq, uपूर्णांक32_t irqstatus)
अणु
	काष्ठा mdp4_crtc *mdp4_crtc = container_of(irq, काष्ठा mdp4_crtc, err);
	काष्ठा drm_crtc *crtc = &mdp4_crtc->base;
	DBG("%s: error: %08x", mdp4_crtc->name, irqstatus);
	crtc_flush(crtc);
पूर्ण

अटल व्योम mdp4_crtc_रुको_क्रम_flush_करोne(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा mdp4_crtc *mdp4_crtc = to_mdp4_crtc(crtc);
	काष्ठा mdp4_kms *mdp4_kms = get_kms(crtc);
	पूर्णांक ret;

	ret = drm_crtc_vblank_get(crtc);
	अगर (ret)
		वापस;

	ret = रुको_event_समयout(dev->vblank[drm_crtc_index(crtc)].queue,
		!(mdp4_पढ़ो(mdp4_kms, REG_MDP4_OVERLAY_FLUSH) &
			mdp4_crtc->flushed_mask),
		msecs_to_jअगरfies(50));
	अगर (ret <= 0)
		dev_warn(dev->dev, "vblank time out, crtc=%d\n", mdp4_crtc->id);

	mdp4_crtc->flushed_mask = 0;

	drm_crtc_vblank_put(crtc);
पूर्ण

uपूर्णांक32_t mdp4_crtc_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा mdp4_crtc *mdp4_crtc = to_mdp4_crtc(crtc);
	वापस mdp4_crtc->vblank.irqmask;
पूर्ण

/* set dma config, ie. the क्रमmat the encoder wants. */
व्योम mdp4_crtc_set_config(काष्ठा drm_crtc *crtc, uपूर्णांक32_t config)
अणु
	काष्ठा mdp4_crtc *mdp4_crtc = to_mdp4_crtc(crtc);
	काष्ठा mdp4_kms *mdp4_kms = get_kms(crtc);

	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_DMA_CONFIG(mdp4_crtc->dma), config);
पूर्ण

/* set पूर्णांकerface क्रम routing crtc->encoder: */
व्योम mdp4_crtc_set_पूर्णांकf(काष्ठा drm_crtc *crtc, क्रमागत mdp4_पूर्णांकf पूर्णांकf, पूर्णांक mixer)
अणु
	काष्ठा mdp4_crtc *mdp4_crtc = to_mdp4_crtc(crtc);
	काष्ठा mdp4_kms *mdp4_kms = get_kms(crtc);
	uपूर्णांक32_t पूर्णांकf_sel;

	पूर्णांकf_sel = mdp4_पढ़ो(mdp4_kms, REG_MDP4_DISP_INTF_SEL);

	चयन (mdp4_crtc->dma) अणु
	हाल DMA_P:
		पूर्णांकf_sel &= ~MDP4_DISP_INTF_SEL_PRIM__MASK;
		पूर्णांकf_sel |= MDP4_DISP_INTF_SEL_PRIM(पूर्णांकf);
		अवरोध;
	हाल DMA_S:
		पूर्णांकf_sel &= ~MDP4_DISP_INTF_SEL_SEC__MASK;
		पूर्णांकf_sel |= MDP4_DISP_INTF_SEL_SEC(पूर्णांकf);
		अवरोध;
	हाल DMA_E:
		पूर्णांकf_sel &= ~MDP4_DISP_INTF_SEL_EXT__MASK;
		पूर्णांकf_sel |= MDP4_DISP_INTF_SEL_EXT(पूर्णांकf);
		अवरोध;
	पूर्ण

	अगर (पूर्णांकf == INTF_DSI_VIDEO) अणु
		पूर्णांकf_sel &= ~MDP4_DISP_INTF_SEL_DSI_CMD;
		पूर्णांकf_sel |= MDP4_DISP_INTF_SEL_DSI_VIDEO;
	पूर्ण अन्यथा अगर (पूर्णांकf == INTF_DSI_CMD) अणु
		पूर्णांकf_sel &= ~MDP4_DISP_INTF_SEL_DSI_VIDEO;
		पूर्णांकf_sel |= MDP4_DISP_INTF_SEL_DSI_CMD;
	पूर्ण

	mdp4_crtc->mixer = mixer;

	blend_setup(crtc);

	DBG("%s: intf_sel=%08x", mdp4_crtc->name, पूर्णांकf_sel);

	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_DISP_INTF_SEL, पूर्णांकf_sel);
पूर्ण

व्योम mdp4_crtc_रुको_क्रम_commit_करोne(काष्ठा drm_crtc *crtc)
अणु
	/* रुको_क्रम_flush_करोne is the only हाल क्रम now.
	 * Later we will have command mode CRTC to रुको क्रम
	 * other event.
	 */
	mdp4_crtc_रुको_क्रम_flush_करोne(crtc);
पूर्ण

अटल स्थिर अक्षर *dma_names[] = अणु
		"DMA_P", "DMA_S", "DMA_E",
पूर्ण;

/* initialize crtc */
काष्ठा drm_crtc *mdp4_crtc_init(काष्ठा drm_device *dev,
		काष्ठा drm_plane *plane, पूर्णांक id, पूर्णांक ovlp_id,
		क्रमागत mdp4_dma dma_id)
अणु
	काष्ठा drm_crtc *crtc = शून्य;
	काष्ठा mdp4_crtc *mdp4_crtc;

	mdp4_crtc = kzalloc(माप(*mdp4_crtc), GFP_KERNEL);
	अगर (!mdp4_crtc)
		वापस ERR_PTR(-ENOMEM);

	crtc = &mdp4_crtc->base;

	mdp4_crtc->id = id;

	mdp4_crtc->ovlp = ovlp_id;
	mdp4_crtc->dma = dma_id;

	mdp4_crtc->vblank.irqmask = dma2irq(mdp4_crtc->dma);
	mdp4_crtc->vblank.irq = mdp4_crtc_vblank_irq;

	mdp4_crtc->err.irqmask = dma2err(mdp4_crtc->dma);
	mdp4_crtc->err.irq = mdp4_crtc_err_irq;

	snम_लिखो(mdp4_crtc->name, माप(mdp4_crtc->name), "%s:%d",
			dma_names[dma_id], ovlp_id);

	spin_lock_init(&mdp4_crtc->cursor.lock);

	drm_flip_work_init(&mdp4_crtc->unref_cursor_work,
			"unref cursor", unref_cursor_worker);

	drm_crtc_init_with_planes(dev, crtc, plane, शून्य, &mdp4_crtc_funcs,
				  शून्य);
	drm_crtc_helper_add(crtc, &mdp4_crtc_helper_funcs);

	वापस crtc;
पूर्ण
