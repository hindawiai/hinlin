<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014-2018, The Linux Foundation. All rights reserved.
 * Copyright (C) 2013 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 */

#घोषणा pr_fmt(fmt)	"[drm:%s:%d] " fmt, __func__, __LINE__

#समावेश <linux/debugfs.h>
#समावेश <linux/dma-buf.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/pm_opp.h>

#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_vblank.h>

#समावेश "msm_drv.h"
#समावेश "msm_mmu.h"
#समावेश "msm_gem.h"

#समावेश "dpu_kms.h"
#समावेश "dpu_core_irq.h"
#समावेश "dpu_formats.h"
#समावेश "dpu_hw_vbif.h"
#समावेश "dpu_vbif.h"
#समावेश "dpu_encoder.h"
#समावेश "dpu_plane.h"
#समावेश "dpu_crtc.h"

#घोषणा CREATE_TRACE_POINTS
#समावेश "dpu_trace.h"

/*
 * To enable overall DRM driver logging
 * # echo 0x2 > /sys/module/drm/parameters/debug
 *
 * To enable DRM driver h/w logging
 * # echo <mask> > /sys/kernel/debug/dri/0/debug/hw_log_mask
 *
 * See dpu_hw_mdss.h क्रम h/w logging mask definitions (search क्रम DPU_DBG_MASK_)
 */
#घोषणा DPU_DEBUGFS_सूची "msm_dpu"
#घोषणा DPU_DEBUGFS_HWMASKNAME "hw_log_mask"

#घोषणा MIN_IB_BW	400000000ULL /* Min ib vote 400MB */

अटल पूर्णांक dpu_kms_hw_init(काष्ठा msm_kms *kms);
अटल व्योम _dpu_kms_mmu_destroy(काष्ठा dpu_kms *dpu_kms);

#अगर_घोषित CONFIG_DEBUG_FS
अटल पूर्णांक _dpu_danger_संकेत_status(काष्ठा seq_file *s,
		bool danger_status)
अणु
	काष्ठा dpu_kms *kms = (काष्ठा dpu_kms *)s->निजी;
	काष्ठा dpu_danger_safe_status status;
	पूर्णांक i;

	अगर (!kms->hw_mdp) अणु
		DPU_ERROR("invalid arg(s)\n");
		वापस 0;
	पूर्ण

	स_रखो(&status, 0, माप(काष्ठा dpu_danger_safe_status));

	pm_runसमय_get_sync(&kms->pdev->dev);
	अगर (danger_status) अणु
		seq_माला_दो(s, "\nDanger signal status:\n");
		अगर (kms->hw_mdp->ops.get_danger_status)
			kms->hw_mdp->ops.get_danger_status(kms->hw_mdp,
					&status);
	पूर्ण अन्यथा अणु
		seq_माला_दो(s, "\nSafe signal status:\n");
		अगर (kms->hw_mdp->ops.get_danger_status)
			kms->hw_mdp->ops.get_danger_status(kms->hw_mdp,
					&status);
	पूर्ण
	pm_runसमय_put_sync(&kms->pdev->dev);

	seq_म_लिखो(s, "MDP     :  0x%x\n", status.mdp);

	क्रम (i = SSPP_VIG0; i < SSPP_MAX; i++)
		seq_म_लिखो(s, "SSPP%d   :  0x%x  \t", i - SSPP_VIG0,
				status.sspp[i]);
	seq_माला_दो(s, "\n");

	वापस 0;
पूर्ण

अटल पूर्णांक dpu_debugfs_danger_stats_show(काष्ठा seq_file *s, व्योम *v)
अणु
	वापस _dpu_danger_संकेत_status(s, true);
पूर्ण
DEFINE_SHOW_ATTRIBUTE(dpu_debugfs_danger_stats);

अटल पूर्णांक dpu_debugfs_safe_stats_show(काष्ठा seq_file *s, व्योम *v)
अणु
	वापस _dpu_danger_संकेत_status(s, false);
पूर्ण
DEFINE_SHOW_ATTRIBUTE(dpu_debugfs_safe_stats);

अटल व्योम dpu_debugfs_danger_init(काष्ठा dpu_kms *dpu_kms,
		काष्ठा dentry *parent)
अणु
	काष्ठा dentry *entry = debugfs_create_dir("danger", parent);

	debugfs_create_file("danger_status", 0600, entry,
			dpu_kms, &dpu_debugfs_danger_stats_fops);
	debugfs_create_file("safe_status", 0600, entry,
			dpu_kms, &dpu_debugfs_safe_stats_fops);
पूर्ण

अटल पूर्णांक _dpu_debugfs_show_regset32(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा dpu_debugfs_regset32 *regset = s->निजी;
	काष्ठा dpu_kms *dpu_kms = regset->dpu_kms;
	व्योम __iomem *base;
	uपूर्णांक32_t i, addr;

	अगर (!dpu_kms->mmio)
		वापस 0;

	base = dpu_kms->mmio + regset->offset;

	/* insert padding spaces, अगर needed */
	अगर (regset->offset & 0xF) अणु
		seq_म_लिखो(s, "[%x]", regset->offset & ~0xF);
		क्रम (i = 0; i < (regset->offset & 0xF); i += 4)
			seq_माला_दो(s, "         ");
	पूर्ण

	pm_runसमय_get_sync(&dpu_kms->pdev->dev);

	/* मुख्य रेजिस्टर output */
	क्रम (i = 0; i < regset->blk_len; i += 4) अणु
		addr = regset->offset + i;
		अगर ((addr & 0xF) == 0x0)
			seq_म_लिखो(s, i ? "\n[%x]" : "[%x]", addr);
		seq_म_लिखो(s, " %08x", पढ़ोl_relaxed(base + i));
	पूर्ण
	seq_माला_दो(s, "\n");
	pm_runसमय_put_sync(&dpu_kms->pdev->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक dpu_debugfs_खोलो_regset32(काष्ठा inode *inode,
		काष्ठा file *file)
अणु
	वापस single_खोलो(file, _dpu_debugfs_show_regset32, inode->i_निजी);
पूर्ण

अटल स्थिर काष्ठा file_operations dpu_fops_regset32 = अणु
	.खोलो =		dpu_debugfs_खोलो_regset32,
	.पढ़ो =		seq_पढ़ो,
	.llseek =	seq_lseek,
	.release =	single_release,
पूर्ण;

व्योम dpu_debugfs_setup_regset32(काष्ठा dpu_debugfs_regset32 *regset,
		uपूर्णांक32_t offset, uपूर्णांक32_t length, काष्ठा dpu_kms *dpu_kms)
अणु
	अगर (regset) अणु
		regset->offset = offset;
		regset->blk_len = length;
		regset->dpu_kms = dpu_kms;
	पूर्ण
पूर्ण

व्योम dpu_debugfs_create_regset32(स्थिर अक्षर *name, umode_t mode,
		व्योम *parent, काष्ठा dpu_debugfs_regset32 *regset)
अणु
	अगर (!name || !regset || !regset->dpu_kms || !regset->blk_len)
		वापस;

	/* make sure offset is a multiple of 4 */
	regset->offset = round_करोwn(regset->offset, 4);

	debugfs_create_file(name, mode, parent, regset, &dpu_fops_regset32);
पूर्ण

अटल पूर्णांक dpu_kms_debugfs_init(काष्ठा msm_kms *kms, काष्ठा drm_minor *minor)
अणु
	काष्ठा dpu_kms *dpu_kms = to_dpu_kms(kms);
	व्योम *p = dpu_hw_util_get_log_mask_ptr();
	काष्ठा dentry *entry;
	काष्ठा drm_device *dev;
	काष्ठा msm_drm_निजी *priv;

	अगर (!p)
		वापस -EINVAL;

	dev = dpu_kms->dev;
	priv = dev->dev_निजी;

	entry = debugfs_create_dir("debug", minor->debugfs_root);

	debugfs_create_x32(DPU_DEBUGFS_HWMASKNAME, 0600, entry, p);

	dpu_debugfs_danger_init(dpu_kms, entry);
	dpu_debugfs_vbअगर_init(dpu_kms, entry);
	dpu_debugfs_core_irq_init(dpu_kms, entry);

	अगर (priv->dp)
		msm_dp_debugfs_init(priv->dp, minor);

	वापस dpu_core_perf_debugfs_init(dpu_kms, entry);
पूर्ण
#पूर्ण_अगर

/* Global/shared object state funcs */

/*
 * This is a helper that वापसs the निजी state currently in operation.
 * Note that this would वापस the "old_state" अगर called in the atomic check
 * path, and the "new_state" after the atomic swap has been करोne.
 */
काष्ठा dpu_global_state *
dpu_kms_get_existing_global_state(काष्ठा dpu_kms *dpu_kms)
अणु
	वापस to_dpu_global_state(dpu_kms->global_state.state);
पूर्ण

/*
 * This acquires the modeset lock set aside क्रम global state, creates
 * a new duplicated निजी object state.
 */
काष्ठा dpu_global_state *dpu_kms_get_global_state(काष्ठा drm_atomic_state *s)
अणु
	काष्ठा msm_drm_निजी *priv = s->dev->dev_निजी;
	काष्ठा dpu_kms *dpu_kms = to_dpu_kms(priv->kms);
	काष्ठा drm_निजी_state *priv_state;
	पूर्णांक ret;

	ret = drm_modeset_lock(&dpu_kms->global_state_lock, s->acquire_ctx);
	अगर (ret)
		वापस ERR_PTR(ret);

	priv_state = drm_atomic_get_निजी_obj_state(s,
						&dpu_kms->global_state);
	अगर (IS_ERR(priv_state))
		वापस ERR_CAST(priv_state);

	वापस to_dpu_global_state(priv_state);
पूर्ण

अटल काष्ठा drm_निजी_state *
dpu_kms_global_duplicate_state(काष्ठा drm_निजी_obj *obj)
अणु
	काष्ठा dpu_global_state *state;

	state = kmemdup(obj->state, माप(*state), GFP_KERNEL);
	अगर (!state)
		वापस शून्य;

	__drm_atomic_helper_निजी_obj_duplicate_state(obj, &state->base);

	वापस &state->base;
पूर्ण

अटल व्योम dpu_kms_global_destroy_state(काष्ठा drm_निजी_obj *obj,
				      काष्ठा drm_निजी_state *state)
अणु
	काष्ठा dpu_global_state *dpu_state = to_dpu_global_state(state);

	kमुक्त(dpu_state);
पूर्ण

अटल स्थिर काष्ठा drm_निजी_state_funcs dpu_kms_global_state_funcs = अणु
	.atomic_duplicate_state = dpu_kms_global_duplicate_state,
	.atomic_destroy_state = dpu_kms_global_destroy_state,
पूर्ण;

अटल पूर्णांक dpu_kms_global_obj_init(काष्ठा dpu_kms *dpu_kms)
अणु
	काष्ठा dpu_global_state *state;

	drm_modeset_lock_init(&dpu_kms->global_state_lock);

	state = kzalloc(माप(*state), GFP_KERNEL);
	अगर (!state)
		वापस -ENOMEM;

	drm_atomic_निजी_obj_init(dpu_kms->dev, &dpu_kms->global_state,
				    &state->base,
				    &dpu_kms_global_state_funcs);
	वापस 0;
पूर्ण

अटल पूर्णांक dpu_kms_parse_data_bus_icc_path(काष्ठा dpu_kms *dpu_kms)
अणु
	काष्ठा icc_path *path0;
	काष्ठा icc_path *path1;
	काष्ठा drm_device *dev = dpu_kms->dev;

	path0 = of_icc_get(dev->dev, "mdp0-mem");
	path1 = of_icc_get(dev->dev, "mdp1-mem");

	अगर (IS_ERR_OR_शून्य(path0))
		वापस PTR_ERR_OR_ZERO(path0);

	dpu_kms->path[0] = path0;
	dpu_kms->num_paths = 1;

	अगर (!IS_ERR_OR_शून्य(path1)) अणु
		dpu_kms->path[1] = path1;
		dpu_kms->num_paths++;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक dpu_kms_enable_vblank(काष्ठा msm_kms *kms, काष्ठा drm_crtc *crtc)
अणु
	वापस dpu_crtc_vblank(crtc, true);
पूर्ण

अटल व्योम dpu_kms_disable_vblank(काष्ठा msm_kms *kms, काष्ठा drm_crtc *crtc)
अणु
	dpu_crtc_vblank(crtc, false);
पूर्ण

अटल व्योम dpu_kms_enable_commit(काष्ठा msm_kms *kms)
अणु
	काष्ठा dpu_kms *dpu_kms = to_dpu_kms(kms);
	pm_runसमय_get_sync(&dpu_kms->pdev->dev);
पूर्ण

अटल व्योम dpu_kms_disable_commit(काष्ठा msm_kms *kms)
अणु
	काष्ठा dpu_kms *dpu_kms = to_dpu_kms(kms);
	pm_runसमय_put_sync(&dpu_kms->pdev->dev);
पूर्ण

अटल kसमय_प्रकार dpu_kms_vsync_समय(काष्ठा msm_kms *kms, काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_encoder *encoder;

	drm_क्रम_each_encoder_mask(encoder, crtc->dev, crtc->state->encoder_mask) अणु
		kसमय_प्रकार vsync_समय;

		अगर (dpu_encoder_vsync_समय(encoder, &vsync_समय) == 0)
			वापस vsync_समय;
	पूर्ण

	वापस kसमय_get();
पूर्ण

अटल व्योम dpu_kms_prepare_commit(काष्ठा msm_kms *kms,
		काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_crtc_state *crtc_state;
	काष्ठा drm_encoder *encoder;
	पूर्णांक i;

	अगर (!kms)
		वापस;

	/* Call prepare_commit क्रम all affected encoders */
	क्रम_each_new_crtc_in_state(state, crtc, crtc_state, i) अणु
		drm_क्रम_each_encoder_mask(encoder, crtc->dev,
					  crtc_state->encoder_mask) अणु
			dpu_encoder_prepare_commit(encoder);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम dpu_kms_flush_commit(काष्ठा msm_kms *kms, अचिन्हित crtc_mask)
अणु
	काष्ठा dpu_kms *dpu_kms = to_dpu_kms(kms);
	काष्ठा drm_crtc *crtc;

	क्रम_each_crtc_mask(dpu_kms->dev, crtc, crtc_mask) अणु
		अगर (!crtc->state->active)
			जारी;

		trace_dpu_kms_commit(DRMID(crtc));
		dpu_crtc_commit_kickoff(crtc);
	पूर्ण
पूर्ण

/*
 * Override the encoder enable since we need to setup the अंतरभूत rotator and करो
 * some crtc magic beक्रमe enabling any bridge that might be present.
 */
व्योम dpu_kms_encoder_enable(काष्ठा drm_encoder *encoder)
अणु
	स्थिर काष्ठा drm_encoder_helper_funcs *funcs = encoder->helper_निजी;
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा drm_crtc *crtc;

	/* Forward this enable call to the commit hook */
	अगर (funcs && funcs->commit)
		funcs->commit(encoder);

	drm_क्रम_each_crtc(crtc, dev) अणु
		अगर (!(crtc->state->encoder_mask & drm_encoder_mask(encoder)))
			जारी;

		trace_dpu_kms_enc_enable(DRMID(crtc));
	पूर्ण
पूर्ण

अटल व्योम dpu_kms_complete_commit(काष्ठा msm_kms *kms, अचिन्हित crtc_mask)
अणु
	काष्ठा dpu_kms *dpu_kms = to_dpu_kms(kms);
	काष्ठा drm_crtc *crtc;

	DPU_ATRACE_BEGIN("kms_complete_commit");

	क्रम_each_crtc_mask(dpu_kms->dev, crtc, crtc_mask)
		dpu_crtc_complete_commit(crtc);

	DPU_ATRACE_END("kms_complete_commit");
पूर्ण

अटल व्योम dpu_kms_रुको_क्रम_commit_करोne(काष्ठा msm_kms *kms,
		काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_encoder *encoder;
	काष्ठा drm_device *dev;
	पूर्णांक ret;

	अगर (!kms || !crtc || !crtc->state) अणु
		DPU_ERROR("invalid params\n");
		वापस;
	पूर्ण

	dev = crtc->dev;

	अगर (!crtc->state->enable) अणु
		DPU_DEBUG("[crtc:%d] not enable\n", crtc->base.id);
		वापस;
	पूर्ण

	अगर (!crtc->state->active) अणु
		DPU_DEBUG("[crtc:%d] not active\n", crtc->base.id);
		वापस;
	पूर्ण

	list_क्रम_each_entry(encoder, &dev->mode_config.encoder_list, head) अणु
		अगर (encoder->crtc != crtc)
			जारी;
		/*
		 * Wait क्रम post-flush अगर necessary to delay beक्रमe
		 * plane_cleanup. For example, रुको क्रम vsync in हाल of video
		 * mode panels. This may be a no-op क्रम command mode panels.
		 */
		trace_dpu_kms_रुको_क्रम_commit_करोne(DRMID(crtc));
		ret = dpu_encoder_रुको_क्रम_event(encoder, MSM_ENC_COMMIT_DONE);
		अगर (ret && ret != -EWOULDBLOCK) अणु
			DPU_ERROR("wait for commit done returned %d\n", ret);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम dpu_kms_रुको_flush(काष्ठा msm_kms *kms, अचिन्हित crtc_mask)
अणु
	काष्ठा dpu_kms *dpu_kms = to_dpu_kms(kms);
	काष्ठा drm_crtc *crtc;

	क्रम_each_crtc_mask(dpu_kms->dev, crtc, crtc_mask)
		dpu_kms_रुको_क्रम_commit_करोne(kms, crtc);
पूर्ण

अटल पूर्णांक _dpu_kms_initialize_dsi(काष्ठा drm_device *dev,
				    काष्ठा msm_drm_निजी *priv,
				    काष्ठा dpu_kms *dpu_kms)
अणु
	काष्ठा drm_encoder *encoder = शून्य;
	पूर्णांक i, rc = 0;

	अगर (!(priv->dsi[0] || priv->dsi[1]))
		वापस rc;

	/*TODO: Support two independent DSI connectors */
	encoder = dpu_encoder_init(dev, DRM_MODE_ENCODER_DSI);
	अगर (IS_ERR(encoder)) अणु
		DPU_ERROR("encoder init failed for dsi display\n");
		वापस PTR_ERR(encoder);
	पूर्ण

	priv->encoders[priv->num_encoders++] = encoder;

	क्रम (i = 0; i < ARRAY_SIZE(priv->dsi); i++) अणु
		अगर (!priv->dsi[i])
			जारी;

		rc = msm_dsi_modeset_init(priv->dsi[i], dev, encoder);
		अगर (rc) अणु
			DPU_ERROR("modeset_init failed for dsi[%d], rc = %d\n",
				i, rc);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक _dpu_kms_initialize_displayport(काष्ठा drm_device *dev,
					    काष्ठा msm_drm_निजी *priv,
					    काष्ठा dpu_kms *dpu_kms)
अणु
	काष्ठा drm_encoder *encoder = शून्य;
	पूर्णांक rc = 0;

	अगर (!priv->dp)
		वापस rc;

	encoder = dpu_encoder_init(dev, DRM_MODE_ENCODER_TMDS);
	अगर (IS_ERR(encoder)) अणु
		DPU_ERROR("encoder init failed for dsi display\n");
		वापस PTR_ERR(encoder);
	पूर्ण

	rc = msm_dp_modeset_init(priv->dp, dev, encoder);
	अगर (rc) अणु
		DPU_ERROR("modeset_init failed for DP, rc = %d\n", rc);
		drm_encoder_cleanup(encoder);
		वापस rc;
	पूर्ण

	priv->encoders[priv->num_encoders++] = encoder;
	वापस rc;
पूर्ण

/**
 * _dpu_kms_setup_displays - create encoders, bridges and connectors
 *                           क्रम underlying displays
 * @dev:        Poपूर्णांकer to drm device काष्ठाure
 * @priv:       Poपूर्णांकer to निजी drm device data
 * @dpu_kms:    Poपूर्णांकer to dpu kms काष्ठाure
 * Returns:     Zero on success
 */
अटल पूर्णांक _dpu_kms_setup_displays(काष्ठा drm_device *dev,
				    काष्ठा msm_drm_निजी *priv,
				    काष्ठा dpu_kms *dpu_kms)
अणु
	पूर्णांक rc = 0;

	rc = _dpu_kms_initialize_dsi(dev, priv, dpu_kms);
	अगर (rc) अणु
		DPU_ERROR("initialize_dsi failed, rc = %d\n", rc);
		वापस rc;
	पूर्ण

	rc = _dpu_kms_initialize_displayport(dev, priv, dpu_kms);
	अगर (rc) अणु
		DPU_ERROR("initialize_DP failed, rc = %d\n", rc);
		वापस rc;
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम _dpu_kms_drm_obj_destroy(काष्ठा dpu_kms *dpu_kms)
अणु
	काष्ठा msm_drm_निजी *priv;
	पूर्णांक i;

	priv = dpu_kms->dev->dev_निजी;

	क्रम (i = 0; i < priv->num_crtcs; i++)
		priv->crtcs[i]->funcs->destroy(priv->crtcs[i]);
	priv->num_crtcs = 0;

	क्रम (i = 0; i < priv->num_planes; i++)
		priv->planes[i]->funcs->destroy(priv->planes[i]);
	priv->num_planes = 0;

	क्रम (i = 0; i < priv->num_connectors; i++)
		priv->connectors[i]->funcs->destroy(priv->connectors[i]);
	priv->num_connectors = 0;

	क्रम (i = 0; i < priv->num_encoders; i++)
		priv->encoders[i]->funcs->destroy(priv->encoders[i]);
	priv->num_encoders = 0;
पूर्ण

अटल पूर्णांक _dpu_kms_drm_obj_init(काष्ठा dpu_kms *dpu_kms)
अणु
	काष्ठा drm_device *dev;
	काष्ठा drm_plane *primary_planes[MAX_PLANES], *plane;
	काष्ठा drm_plane *cursor_planes[MAX_PLANES] = अणु शून्य पूर्ण;
	काष्ठा drm_crtc *crtc;

	काष्ठा msm_drm_निजी *priv;
	काष्ठा dpu_mdss_cfg *catalog;

	पूर्णांक primary_planes_idx = 0, cursor_planes_idx = 0, i, ret;
	पूर्णांक max_crtc_count;
	dev = dpu_kms->dev;
	priv = dev->dev_निजी;
	catalog = dpu_kms->catalog;

	/*
	 * Create encoder and query display drivers to create
	 * bridges and connectors
	 */
	ret = _dpu_kms_setup_displays(dev, priv, dpu_kms);
	अगर (ret)
		जाओ fail;

	max_crtc_count = min(catalog->mixer_count, priv->num_encoders);

	/* Create the planes, keeping track of one primary/cursor per crtc */
	क्रम (i = 0; i < catalog->sspp_count; i++) अणु
		क्रमागत drm_plane_type type;

		अगर ((catalog->sspp[i].features & BIT(DPU_SSPP_CURSOR))
			&& cursor_planes_idx < max_crtc_count)
			type = DRM_PLANE_TYPE_CURSOR;
		अन्यथा अगर (primary_planes_idx < max_crtc_count)
			type = DRM_PLANE_TYPE_PRIMARY;
		अन्यथा
			type = DRM_PLANE_TYPE_OVERLAY;

		DPU_DEBUG("Create plane type %d with features %lx (cur %lx)\n",
			  type, catalog->sspp[i].features,
			  catalog->sspp[i].features & BIT(DPU_SSPP_CURSOR));

		plane = dpu_plane_init(dev, catalog->sspp[i].id, type,
				       (1UL << max_crtc_count) - 1, 0);
		अगर (IS_ERR(plane)) अणु
			DPU_ERROR("dpu_plane_init failed\n");
			ret = PTR_ERR(plane);
			जाओ fail;
		पूर्ण
		priv->planes[priv->num_planes++] = plane;

		अगर (type == DRM_PLANE_TYPE_CURSOR)
			cursor_planes[cursor_planes_idx++] = plane;
		अन्यथा अगर (type == DRM_PLANE_TYPE_PRIMARY)
			primary_planes[primary_planes_idx++] = plane;
	पूर्ण

	max_crtc_count = min(max_crtc_count, primary_planes_idx);

	/* Create one CRTC per encoder */
	क्रम (i = 0; i < max_crtc_count; i++) अणु
		crtc = dpu_crtc_init(dev, primary_planes[i], cursor_planes[i]);
		अगर (IS_ERR(crtc)) अणु
			ret = PTR_ERR(crtc);
			जाओ fail;
		पूर्ण
		priv->crtcs[priv->num_crtcs++] = crtc;
	पूर्ण

	/* All CRTCs are compatible with all encoders */
	क्रम (i = 0; i < priv->num_encoders; i++)
		priv->encoders[i]->possible_crtcs = (1 << priv->num_crtcs) - 1;

	वापस 0;
fail:
	_dpu_kms_drm_obj_destroy(dpu_kms);
	वापस ret;
पूर्ण

अटल दीर्घ dpu_kms_round_pixclk(काष्ठा msm_kms *kms, अचिन्हित दीर्घ rate,
		काष्ठा drm_encoder *encoder)
अणु
	वापस rate;
पूर्ण

अटल व्योम _dpu_kms_hw_destroy(काष्ठा dpu_kms *dpu_kms)
अणु
	पूर्णांक i;

	अगर (dpu_kms->hw_पूर्णांकr)
		dpu_hw_पूर्णांकr_destroy(dpu_kms->hw_पूर्णांकr);
	dpu_kms->hw_पूर्णांकr = शून्य;

	/* safe to call these more than once during shutकरोwn */
	_dpu_kms_mmu_destroy(dpu_kms);

	अगर (dpu_kms->catalog) अणु
		क्रम (i = 0; i < dpu_kms->catalog->vbअगर_count; i++) अणु
			u32 vbअगर_idx = dpu_kms->catalog->vbअगर[i].id;

			अगर ((vbअगर_idx < VBIF_MAX) && dpu_kms->hw_vbअगर[vbअगर_idx])
				dpu_hw_vbअगर_destroy(dpu_kms->hw_vbअगर[vbअगर_idx]);
		पूर्ण
	पूर्ण

	अगर (dpu_kms->rm_init)
		dpu_rm_destroy(&dpu_kms->rm);
	dpu_kms->rm_init = false;

	अगर (dpu_kms->catalog)
		dpu_hw_catalog_deinit(dpu_kms->catalog);
	dpu_kms->catalog = शून्य;

	अगर (dpu_kms->vbअगर[VBIF_NRT])
		devm_iounmap(&dpu_kms->pdev->dev, dpu_kms->vbअगर[VBIF_NRT]);
	dpu_kms->vbअगर[VBIF_NRT] = शून्य;

	अगर (dpu_kms->vbअगर[VBIF_RT])
		devm_iounmap(&dpu_kms->pdev->dev, dpu_kms->vbअगर[VBIF_RT]);
	dpu_kms->vbअगर[VBIF_RT] = शून्य;

	अगर (dpu_kms->hw_mdp)
		dpu_hw_mdp_destroy(dpu_kms->hw_mdp);
	dpu_kms->hw_mdp = शून्य;

	अगर (dpu_kms->mmio)
		devm_iounmap(&dpu_kms->pdev->dev, dpu_kms->mmio);
	dpu_kms->mmio = शून्य;
पूर्ण

अटल व्योम dpu_kms_destroy(काष्ठा msm_kms *kms)
अणु
	काष्ठा dpu_kms *dpu_kms;

	अगर (!kms) अणु
		DPU_ERROR("invalid kms\n");
		वापस;
	पूर्ण

	dpu_kms = to_dpu_kms(kms);

	_dpu_kms_hw_destroy(dpu_kms);

	msm_kms_destroy(&dpu_kms->base);
पूर्ण

अटल व्योम _dpu_kms_set_encoder_mode(काष्ठा msm_kms *kms,
				 काष्ठा drm_encoder *encoder,
				 bool cmd_mode)
अणु
	काष्ठा msm_display_info info;
	काष्ठा msm_drm_निजी *priv = encoder->dev->dev_निजी;
	पूर्णांक i, rc = 0;

	स_रखो(&info, 0, माप(info));

	info.पूर्णांकf_type = encoder->encoder_type;
	info.capabilities = cmd_mode ? MSM_DISPLAY_CAP_CMD_MODE :
			MSM_DISPLAY_CAP_VID_MODE;

	चयन (info.पूर्णांकf_type) अणु
	हाल DRM_MODE_ENCODER_DSI:
		/* TODO: No support क्रम DSI swap */
		क्रम (i = 0; i < ARRAY_SIZE(priv->dsi); i++) अणु
			अगर (priv->dsi[i]) अणु
				info.h_tile_instance[info.num_of_h_tiles] = i;
				info.num_of_h_tiles++;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल DRM_MODE_ENCODER_TMDS:
		info.num_of_h_tiles = 1;
		अवरोध;
	पूर्ण

	rc = dpu_encoder_setup(encoder->dev, encoder, &info);
	अगर (rc)
		DPU_ERROR("failed to setup DPU encoder %d: rc:%d\n",
			encoder->base.id, rc);
पूर्ण

अटल irqवापस_t dpu_irq(काष्ठा msm_kms *kms)
अणु
	काष्ठा dpu_kms *dpu_kms = to_dpu_kms(kms);

	वापस dpu_core_irq(dpu_kms);
पूर्ण

अटल व्योम dpu_irq_preinstall(काष्ठा msm_kms *kms)
अणु
	काष्ठा dpu_kms *dpu_kms = to_dpu_kms(kms);

	dpu_core_irq_preinstall(dpu_kms);
पूर्ण

अटल पूर्णांक dpu_irq_postinstall(काष्ठा msm_kms *kms)
अणु
	काष्ठा msm_drm_निजी *priv;
	काष्ठा dpu_kms *dpu_kms = to_dpu_kms(kms);

	अगर (!dpu_kms || !dpu_kms->dev)
		वापस -EINVAL;

	priv = dpu_kms->dev->dev_निजी;
	अगर (!priv)
		वापस -EINVAL;

	msm_dp_irq_postinstall(priv->dp);

	वापस 0;
पूर्ण

अटल व्योम dpu_irq_uninstall(काष्ठा msm_kms *kms)
अणु
	काष्ठा dpu_kms *dpu_kms = to_dpu_kms(kms);

	dpu_core_irq_uninstall(dpu_kms);
पूर्ण

अटल स्थिर काष्ठा msm_kms_funcs kms_funcs = अणु
	.hw_init         = dpu_kms_hw_init,
	.irq_preinstall  = dpu_irq_preinstall,
	.irq_postinstall = dpu_irq_postinstall,
	.irq_uninstall   = dpu_irq_uninstall,
	.irq             = dpu_irq,
	.enable_commit   = dpu_kms_enable_commit,
	.disable_commit  = dpu_kms_disable_commit,
	.vsync_समय      = dpu_kms_vsync_समय,
	.prepare_commit  = dpu_kms_prepare_commit,
	.flush_commit    = dpu_kms_flush_commit,
	.रुको_flush      = dpu_kms_रुको_flush,
	.complete_commit = dpu_kms_complete_commit,
	.enable_vblank   = dpu_kms_enable_vblank,
	.disable_vblank  = dpu_kms_disable_vblank,
	.check_modअगरied_क्रमmat = dpu_क्रमmat_check_modअगरied_क्रमmat,
	.get_क्रमmat      = dpu_get_msm_क्रमmat,
	.round_pixclk    = dpu_kms_round_pixclk,
	.destroy         = dpu_kms_destroy,
	.set_encoder_mode = _dpu_kms_set_encoder_mode,
#अगर_घोषित CONFIG_DEBUG_FS
	.debugfs_init    = dpu_kms_debugfs_init,
#पूर्ण_अगर
पूर्ण;

अटल व्योम _dpu_kms_mmu_destroy(काष्ठा dpu_kms *dpu_kms)
अणु
	काष्ठा msm_mmu *mmu;

	अगर (!dpu_kms->base.aspace)
		वापस;

	mmu = dpu_kms->base.aspace->mmu;

	mmu->funcs->detach(mmu);
	msm_gem_address_space_put(dpu_kms->base.aspace);

	dpu_kms->base.aspace = शून्य;
पूर्ण

अटल पूर्णांक _dpu_kms_mmu_init(काष्ठा dpu_kms *dpu_kms)
अणु
	काष्ठा iommu_करोमुख्य *करोमुख्य;
	काष्ठा msm_gem_address_space *aspace;
	काष्ठा msm_mmu *mmu;

	करोमुख्य = iommu_करोमुख्य_alloc(&platक्रमm_bus_type);
	अगर (!करोमुख्य)
		वापस 0;

	mmu = msm_iommu_new(dpu_kms->dev->dev, करोमुख्य);
	aspace = msm_gem_address_space_create(mmu, "dpu1",
		0x1000, 0x100000000 - 0x1000);

	अगर (IS_ERR(aspace)) अणु
		mmu->funcs->destroy(mmu);
		वापस PTR_ERR(aspace);
	पूर्ण

	dpu_kms->base.aspace = aspace;
	वापस 0;
पूर्ण

अटल काष्ठा dss_clk *_dpu_kms_get_clk(काष्ठा dpu_kms *dpu_kms,
		अक्षर *घड़ी_name)
अणु
	काष्ठा dss_module_घातer *mp = &dpu_kms->mp;
	पूर्णांक i;

	क्रम (i = 0; i < mp->num_clk; i++) अणु
		अगर (!म_भेद(mp->clk_config[i].clk_name, घड़ी_name))
			वापस &mp->clk_config[i];
	पूर्ण

	वापस शून्य;
पूर्ण

u64 dpu_kms_get_clk_rate(काष्ठा dpu_kms *dpu_kms, अक्षर *घड़ी_name)
अणु
	काष्ठा dss_clk *clk;

	clk = _dpu_kms_get_clk(dpu_kms, घड़ी_name);
	अगर (!clk)
		वापस -EINVAL;

	वापस clk_get_rate(clk->clk);
पूर्ण

अटल पूर्णांक dpu_kms_hw_init(काष्ठा msm_kms *kms)
अणु
	काष्ठा dpu_kms *dpu_kms;
	काष्ठा drm_device *dev;
	पूर्णांक i, rc = -EINVAL;

	अगर (!kms) अणु
		DPU_ERROR("invalid kms\n");
		वापस rc;
	पूर्ण

	dpu_kms = to_dpu_kms(kms);
	dev = dpu_kms->dev;

	rc = dpu_kms_global_obj_init(dpu_kms);
	अगर (rc)
		वापस rc;

	atomic_set(&dpu_kms->bandwidth_ref, 0);

	dpu_kms->mmio = msm_ioremap(dpu_kms->pdev, "mdp", "mdp");
	अगर (IS_ERR(dpu_kms->mmio)) अणु
		rc = PTR_ERR(dpu_kms->mmio);
		DPU_ERROR("mdp register memory map failed: %d\n", rc);
		dpu_kms->mmio = शून्य;
		जाओ error;
	पूर्ण
	DRM_DEBUG("mapped dpu address space @%pK\n", dpu_kms->mmio);

	dpu_kms->vbअगर[VBIF_RT] = msm_ioremap(dpu_kms->pdev, "vbif", "vbif");
	अगर (IS_ERR(dpu_kms->vbअगर[VBIF_RT])) अणु
		rc = PTR_ERR(dpu_kms->vbअगर[VBIF_RT]);
		DPU_ERROR("vbif register memory map failed: %d\n", rc);
		dpu_kms->vbअगर[VBIF_RT] = शून्य;
		जाओ error;
	पूर्ण
	dpu_kms->vbअगर[VBIF_NRT] = msm_ioremap_quiet(dpu_kms->pdev, "vbif_nrt", "vbif_nrt");
	अगर (IS_ERR(dpu_kms->vbअगर[VBIF_NRT])) अणु
		dpu_kms->vbअगर[VBIF_NRT] = शून्य;
		DPU_DEBUG("VBIF NRT is not defined");
	पूर्ण

	dpu_kms->reg_dma = msm_ioremap_quiet(dpu_kms->pdev, "regdma", "regdma");
	अगर (IS_ERR(dpu_kms->reg_dma)) अणु
		dpu_kms->reg_dma = शून्य;
		DPU_DEBUG("REG_DMA is not defined");
	पूर्ण

	dpu_kms_parse_data_bus_icc_path(dpu_kms);

	pm_runसमय_get_sync(&dpu_kms->pdev->dev);

	dpu_kms->core_rev = पढ़ोl_relaxed(dpu_kms->mmio + 0x0);

	pr_info("dpu hardware revision:0x%x\n", dpu_kms->core_rev);

	dpu_kms->catalog = dpu_hw_catalog_init(dpu_kms->core_rev);
	अगर (IS_ERR_OR_शून्य(dpu_kms->catalog)) अणु
		rc = PTR_ERR(dpu_kms->catalog);
		अगर (!dpu_kms->catalog)
			rc = -EINVAL;
		DPU_ERROR("catalog init failed: %d\n", rc);
		dpu_kms->catalog = शून्य;
		जाओ घातer_error;
	पूर्ण

	/*
	 * Now we need to पढ़ो the HW catalog and initialize resources such as
	 * घड़ीs, regulators, GDSC/MMAGIC, ioremap the रेजिस्टर ranges etc
	 */
	rc = _dpu_kms_mmu_init(dpu_kms);
	अगर (rc) अणु
		DPU_ERROR("dpu_kms_mmu_init failed: %d\n", rc);
		जाओ घातer_error;
	पूर्ण

	rc = dpu_rm_init(&dpu_kms->rm, dpu_kms->catalog, dpu_kms->mmio);
	अगर (rc) अणु
		DPU_ERROR("rm init failed: %d\n", rc);
		जाओ घातer_error;
	पूर्ण

	dpu_kms->rm_init = true;

	dpu_kms->hw_mdp = dpu_hw_mdptop_init(MDP_TOP, dpu_kms->mmio,
					     dpu_kms->catalog);
	अगर (IS_ERR(dpu_kms->hw_mdp)) अणु
		rc = PTR_ERR(dpu_kms->hw_mdp);
		DPU_ERROR("failed to get hw_mdp: %d\n", rc);
		dpu_kms->hw_mdp = शून्य;
		जाओ घातer_error;
	पूर्ण

	क्रम (i = 0; i < dpu_kms->catalog->vbअगर_count; i++) अणु
		u32 vbअगर_idx = dpu_kms->catalog->vbअगर[i].id;

		dpu_kms->hw_vbअगर[i] = dpu_hw_vbअगर_init(vbअगर_idx,
				dpu_kms->vbअगर[vbअगर_idx], dpu_kms->catalog);
		अगर (IS_ERR_OR_शून्य(dpu_kms->hw_vbअगर[vbअगर_idx])) अणु
			rc = PTR_ERR(dpu_kms->hw_vbअगर[vbअगर_idx]);
			अगर (!dpu_kms->hw_vbअगर[vbअगर_idx])
				rc = -EINVAL;
			DPU_ERROR("failed to init vbif %d: %d\n", vbअगर_idx, rc);
			dpu_kms->hw_vbअगर[vbअगर_idx] = शून्य;
			जाओ घातer_error;
		पूर्ण
	पूर्ण

	rc = dpu_core_perf_init(&dpu_kms->perf, dev, dpu_kms->catalog,
			_dpu_kms_get_clk(dpu_kms, "core"));
	अगर (rc) अणु
		DPU_ERROR("failed to init perf %d\n", rc);
		जाओ perf_err;
	पूर्ण

	dpu_kms->hw_पूर्णांकr = dpu_hw_पूर्णांकr_init(dpu_kms->mmio, dpu_kms->catalog);
	अगर (IS_ERR_OR_शून्य(dpu_kms->hw_पूर्णांकr)) अणु
		rc = PTR_ERR(dpu_kms->hw_पूर्णांकr);
		DPU_ERROR("hw_intr init failed: %d\n", rc);
		dpu_kms->hw_पूर्णांकr = शून्य;
		जाओ hw_पूर्णांकr_init_err;
	पूर्ण

	dev->mode_config.min_width = 0;
	dev->mode_config.min_height = 0;

	/*
	 * max crtc width is equal to the max mixer width * 2 and max height is
	 * is 4K
	 */
	dev->mode_config.max_width =
			dpu_kms->catalog->caps->max_mixer_width * 2;
	dev->mode_config.max_height = 4096;

	/*
	 * Support क्रमmat modअगरiers क्रम compression etc.
	 */
	dev->mode_config.allow_fb_modअगरiers = true;

	dev->max_vblank_count = 0xffffffff;
	/* Disable vblank irqs aggressively क्रम घातer-saving */
	dev->vblank_disable_immediate = true;

	/*
	 * _dpu_kms_drm_obj_init should create the DRM related objects
	 * i.e. CRTCs, planes, encoders, connectors and so क्रमth
	 */
	rc = _dpu_kms_drm_obj_init(dpu_kms);
	अगर (rc) अणु
		DPU_ERROR("modeset init failed: %d\n", rc);
		जाओ drm_obj_init_err;
	पूर्ण

	dpu_vbअगर_init_memtypes(dpu_kms);

	pm_runसमय_put_sync(&dpu_kms->pdev->dev);

	वापस 0;

drm_obj_init_err:
	dpu_core_perf_destroy(&dpu_kms->perf);
hw_पूर्णांकr_init_err:
perf_err:
घातer_error:
	pm_runसमय_put_sync(&dpu_kms->pdev->dev);
error:
	_dpu_kms_hw_destroy(dpu_kms);

	वापस rc;
पूर्ण

काष्ठा msm_kms *dpu_kms_init(काष्ठा drm_device *dev)
अणु
	काष्ठा msm_drm_निजी *priv;
	काष्ठा dpu_kms *dpu_kms;
	पूर्णांक irq;

	अगर (!dev) अणु
		DPU_ERROR("drm device node invalid\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	priv = dev->dev_निजी;
	dpu_kms = to_dpu_kms(priv->kms);

	irq = irq_of_parse_and_map(dpu_kms->pdev->dev.of_node, 0);
	अगर (irq < 0) अणु
		DPU_ERROR("failed to get irq: %d\n", irq);
		वापस ERR_PTR(irq);
	पूर्ण
	dpu_kms->base.irq = irq;

	वापस &dpu_kms->base;
पूर्ण

अटल पूर्णांक dpu_bind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	काष्ठा drm_device *ddev = dev_get_drvdata(master);
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा msm_drm_निजी *priv = ddev->dev_निजी;
	काष्ठा dpu_kms *dpu_kms;
	काष्ठा dss_module_घातer *mp;
	पूर्णांक ret = 0;

	dpu_kms = devm_kzalloc(&pdev->dev, माप(*dpu_kms), GFP_KERNEL);
	अगर (!dpu_kms)
		वापस -ENOMEM;

	dpu_kms->opp_table = dev_pm_opp_set_clkname(dev, "core");
	अगर (IS_ERR(dpu_kms->opp_table))
		वापस PTR_ERR(dpu_kms->opp_table);
	/* OPP table is optional */
	ret = dev_pm_opp_of_add_table(dev);
	अगर (ret && ret != -ENODEV) अणु
		dev_err(dev, "invalid OPP table in device tree\n");
		जाओ put_clkname;
	पूर्ण

	mp = &dpu_kms->mp;
	ret = msm_dss_parse_घड़ी(pdev, mp);
	अगर (ret) अणु
		DPU_ERROR("failed to parse clocks, ret=%d\n", ret);
		जाओ err;
	पूर्ण

	platक्रमm_set_drvdata(pdev, dpu_kms);

	ret = msm_kms_init(&dpu_kms->base, &kms_funcs);
	अगर (ret) अणु
		DPU_ERROR("failed to init kms, ret=%d\n", ret);
		जाओ err;
	पूर्ण
	dpu_kms->dev = ddev;
	dpu_kms->pdev = pdev;

	pm_runसमय_enable(&pdev->dev);
	dpu_kms->rpm_enabled = true;

	priv->kms = &dpu_kms->base;
	वापस ret;
err:
	dev_pm_opp_of_हटाओ_table(dev);
put_clkname:
	dev_pm_opp_put_clkname(dpu_kms->opp_table);
	वापस ret;
पूर्ण

अटल व्योम dpu_unbind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा dpu_kms *dpu_kms = platक्रमm_get_drvdata(pdev);
	काष्ठा dss_module_घातer *mp = &dpu_kms->mp;

	msm_dss_put_clk(mp->clk_config, mp->num_clk);
	devm_kमुक्त(&pdev->dev, mp->clk_config);
	mp->num_clk = 0;

	अगर (dpu_kms->rpm_enabled)
		pm_runसमय_disable(&pdev->dev);

	dev_pm_opp_of_हटाओ_table(dev);
	dev_pm_opp_put_clkname(dpu_kms->opp_table);
पूर्ण

अटल स्थिर काष्ठा component_ops dpu_ops = अणु
	.bind   = dpu_bind,
	.unbind = dpu_unbind,
पूर्ण;

अटल पूर्णांक dpu_dev_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस component_add(&pdev->dev, &dpu_ops);
पूर्ण

अटल पूर्णांक dpu_dev_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	component_del(&pdev->dev, &dpu_ops);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused dpu_runसमय_suspend(काष्ठा device *dev)
अणु
	पूर्णांक i, rc = -1;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा dpu_kms *dpu_kms = platक्रमm_get_drvdata(pdev);
	काष्ठा dss_module_घातer *mp = &dpu_kms->mp;

	/* Drop the perक्रमmance state vote */
	dev_pm_opp_set_rate(dev, 0);
	rc = msm_dss_enable_clk(mp->clk_config, mp->num_clk, false);
	अगर (rc)
		DPU_ERROR("clock disable failed rc:%d\n", rc);

	क्रम (i = 0; i < dpu_kms->num_paths; i++)
		icc_set_bw(dpu_kms->path[i], 0, 0);

	वापस rc;
पूर्ण

अटल पूर्णांक __maybe_unused dpu_runसमय_resume(काष्ठा device *dev)
अणु
	पूर्णांक rc = -1;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा dpu_kms *dpu_kms = platक्रमm_get_drvdata(pdev);
	काष्ठा drm_encoder *encoder;
	काष्ठा drm_device *ddev;
	काष्ठा dss_module_घातer *mp = &dpu_kms->mp;
	पूर्णांक i;

	ddev = dpu_kms->dev;

	WARN_ON(!(dpu_kms->num_paths));
	/* Min vote of BW is required beक्रमe turning on AXI clk */
	क्रम (i = 0; i < dpu_kms->num_paths; i++)
		icc_set_bw(dpu_kms->path[i], 0, Bps_to_icc(MIN_IB_BW));

	rc = msm_dss_enable_clk(mp->clk_config, mp->num_clk, true);
	अगर (rc) अणु
		DPU_ERROR("clock enable failed rc:%d\n", rc);
		वापस rc;
	पूर्ण

	dpu_vbअगर_init_memtypes(dpu_kms);

	drm_क्रम_each_encoder(encoder, ddev)
		dpu_encoder_virt_runसमय_resume(encoder);

	वापस rc;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops dpu_pm_ops = अणु
	SET_RUNTIME_PM_OPS(dpu_runसमय_suspend, dpu_runसमय_resume, शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
पूर्ण;

अटल स्थिर काष्ठा of_device_id dpu_dt_match[] = अणु
	अणु .compatible = "qcom,sdm845-dpu", पूर्ण,
	अणु .compatible = "qcom,sc7180-dpu", पूर्ण,
	अणु .compatible = "qcom,sc7280-dpu", पूर्ण,
	अणु .compatible = "qcom,sm8150-dpu", पूर्ण,
	अणु .compatible = "qcom,sm8250-dpu", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, dpu_dt_match);

अटल काष्ठा platक्रमm_driver dpu_driver = अणु
	.probe = dpu_dev_probe,
	.हटाओ = dpu_dev_हटाओ,
	.driver = अणु
		.name = "msm_dpu",
		.of_match_table = dpu_dt_match,
		.pm = &dpu_pm_ops,
	पूर्ण,
पूर्ण;

व्योम __init msm_dpu_रेजिस्टर(व्योम)
अणु
	platक्रमm_driver_रेजिस्टर(&dpu_driver);
पूर्ण

व्योम __निकास msm_dpu_unरेजिस्टर(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&dpu_driver);
पूर्ण
