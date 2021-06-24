<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2016-2018, The Linux Foundation. All rights reserved.
 */

#घोषणा pr_fmt(fmt)	"[drm:%s:%d] " fmt, __func__, __LINE__

#समावेश <linux/debugfs.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/mutex.h>
#समावेश <linux/pm_opp.h>
#समावेश <linux/sort.h>
#समावेश <linux/clk.h>
#समावेश <linux/biपंचांगap.h>

#समावेश "dpu_kms.h"
#समावेश "dpu_trace.h"
#समावेश "dpu_crtc.h"
#समावेश "dpu_core_perf.h"

/**
 * क्रमागत dpu_perf_mode - perक्रमmance tuning mode
 * @DPU_PERF_MODE_NORMAL: perक्रमmance controlled by user mode client
 * @DPU_PERF_MODE_MINIMUM: perक्रमmance bounded by minimum setting
 * @DPU_PERF_MODE_FIXED: perक्रमmance bounded by fixed setting
 * @DPU_PERF_MODE_MAX: maximum value, used क्रम error checking
 */
क्रमागत dpu_perf_mode अणु
	DPU_PERF_MODE_NORMAL,
	DPU_PERF_MODE_MINIMUM,
	DPU_PERF_MODE_FIXED,
	DPU_PERF_MODE_MAX
पूर्ण;

/**
 * _dpu_core_perf_calc_bw() - to calculate BW per crtc
 * @kms:  poपूर्णांकer to the dpu_kms
 * @crtc: poपूर्णांकer to a crtc
 * Return: वापसs aggregated BW क्रम all planes in crtc.
 */
अटल u64 _dpu_core_perf_calc_bw(काष्ठा dpu_kms *kms,
		काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_plane *plane;
	काष्ठा dpu_plane_state *pstate;
	u64 crtc_plane_bw = 0;
	u32 bw_factor;

	drm_atomic_crtc_क्रम_each_plane(plane, crtc) अणु
		pstate = to_dpu_plane_state(plane->state);
		अगर (!pstate)
			जारी;

		crtc_plane_bw += pstate->plane_fetch_bw;
	पूर्ण

	bw_factor = kms->catalog->perf.bw_inefficiency_factor;
	अगर (bw_factor) अणु
		crtc_plane_bw *= bw_factor;
		करो_भाग(crtc_plane_bw, 100);
	पूर्ण

	वापस crtc_plane_bw;
पूर्ण

/**
 * _dpu_core_perf_calc_clk() - to calculate घड़ी per crtc
 * @kms:  poपूर्णांकer to the dpu_kms
 * @crtc: poपूर्णांकer to a crtc
 * @state: poपूर्णांकer to a crtc state
 * Return: वापसs max clk क्रम all planes in crtc.
 */
अटल u64 _dpu_core_perf_calc_clk(काष्ठा dpu_kms *kms,
		काष्ठा drm_crtc *crtc, काष्ठा drm_crtc_state *state)
अणु
	काष्ठा drm_plane *plane;
	काष्ठा dpu_plane_state *pstate;
	काष्ठा drm_display_mode *mode;
	u64 crtc_clk;
	u32 clk_factor;

	mode = &state->adjusted_mode;

	crtc_clk = mode->vtotal * mode->hdisplay * drm_mode_vrefresh(mode);

	drm_atomic_crtc_क्रम_each_plane(plane, crtc) अणु
		pstate = to_dpu_plane_state(plane->state);
		अगर (!pstate)
			जारी;

		crtc_clk = max(pstate->plane_clk, crtc_clk);
	पूर्ण

	clk_factor = kms->catalog->perf.clk_inefficiency_factor;
	अगर (clk_factor) अणु
		crtc_clk *= clk_factor;
		करो_भाग(crtc_clk, 100);
	पूर्ण

	वापस crtc_clk;
पूर्ण

अटल काष्ठा dpu_kms *_dpu_crtc_get_kms(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा msm_drm_निजी *priv;
	priv = crtc->dev->dev_निजी;
	वापस to_dpu_kms(priv->kms);
पूर्ण

अटल व्योम _dpu_core_perf_calc_crtc(काष्ठा dpu_kms *kms,
		काष्ठा drm_crtc *crtc,
		काष्ठा drm_crtc_state *state,
		काष्ठा dpu_core_perf_params *perf)
अणु
	अगर (!kms || !kms->catalog || !crtc || !state || !perf) अणु
		DPU_ERROR("invalid parameters\n");
		वापस;
	पूर्ण

	स_रखो(perf, 0, माप(काष्ठा dpu_core_perf_params));

	अगर (kms->perf.perf_tune.mode == DPU_PERF_MODE_MINIMUM) अणु
		perf->bw_ctl = 0;
		perf->max_per_pipe_ib = 0;
		perf->core_clk_rate = 0;
	पूर्ण अन्यथा अगर (kms->perf.perf_tune.mode == DPU_PERF_MODE_FIXED) अणु
		perf->bw_ctl = kms->perf.fix_core_ab_vote;
		perf->max_per_pipe_ib = kms->perf.fix_core_ib_vote;
		perf->core_clk_rate = kms->perf.fix_core_clk_rate;
	पूर्ण अन्यथा अणु
		perf->bw_ctl = _dpu_core_perf_calc_bw(kms, crtc);
		perf->max_per_pipe_ib = kms->catalog->perf.min_dram_ib;
		perf->core_clk_rate = _dpu_core_perf_calc_clk(kms, crtc, state);
	पूर्ण

	DPU_DEBUG(
		"crtc=%d clk_rate=%llu core_ib=%llu core_ab=%llu\n",
			crtc->base.id, perf->core_clk_rate,
			perf->max_per_pipe_ib, perf->bw_ctl);
पूर्ण

पूर्णांक dpu_core_perf_crtc_check(काष्ठा drm_crtc *crtc,
		काष्ठा drm_crtc_state *state)
अणु
	u32 bw, threshold;
	u64 bw_sum_of_पूर्णांकfs = 0;
	क्रमागत dpu_crtc_client_type curr_client_type;
	काष्ठा dpu_crtc_state *dpu_cstate;
	काष्ठा drm_crtc *पंचांगp_crtc;
	काष्ठा dpu_kms *kms;

	अगर (!crtc || !state) अणु
		DPU_ERROR("invalid crtc\n");
		वापस -EINVAL;
	पूर्ण

	kms = _dpu_crtc_get_kms(crtc);
	अगर (!kms->catalog) अणु
		DPU_ERROR("invalid parameters\n");
		वापस 0;
	पूर्ण

	/* we only need bandwidth check on real-समय clients (पूर्णांकerfaces) */
	अगर (dpu_crtc_get_client_type(crtc) == NRT_CLIENT)
		वापस 0;

	dpu_cstate = to_dpu_crtc_state(state);

	/* obtain new values */
	_dpu_core_perf_calc_crtc(kms, crtc, state, &dpu_cstate->new_perf);

	bw_sum_of_पूर्णांकfs = dpu_cstate->new_perf.bw_ctl;
	curr_client_type = dpu_crtc_get_client_type(crtc);

	drm_क्रम_each_crtc(पंचांगp_crtc, crtc->dev) अणु
		अगर (पंचांगp_crtc->enabled &&
		    (dpu_crtc_get_client_type(पंचांगp_crtc) ==
				curr_client_type) && (पंचांगp_crtc != crtc)) अणु
			काष्ठा dpu_crtc_state *पंचांगp_cstate =
				to_dpu_crtc_state(पंचांगp_crtc->state);

			DPU_DEBUG("crtc:%d bw:%llu ctrl:%d\n",
				पंचांगp_crtc->base.id, पंचांगp_cstate->new_perf.bw_ctl,
				पंचांगp_cstate->bw_control);

				bw_sum_of_पूर्णांकfs += पंचांगp_cstate->new_perf.bw_ctl;
		पूर्ण

		/* convert bandwidth to kb */
		bw = DIV_ROUND_UP_ULL(bw_sum_of_पूर्णांकfs, 1000);
		DPU_DEBUG("calculated bandwidth=%uk\n", bw);

		threshold = kms->catalog->perf.max_bw_high;

		DPU_DEBUG("final threshold bw limit = %d\n", threshold);

		अगर (!threshold) अणु
			DPU_ERROR("no bandwidth limits specified\n");
			वापस -E2BIG;
		पूर्ण अन्यथा अगर (bw > threshold) अणु
			DPU_ERROR("exceeds bandwidth: %ukb > %ukb\n", bw,
					threshold);
			वापस -E2BIG;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक _dpu_core_perf_crtc_update_bus(काष्ठा dpu_kms *kms,
		काष्ठा drm_crtc *crtc)
अणु
	काष्ठा dpu_core_perf_params perf = अणु 0 पूर्ण;
	क्रमागत dpu_crtc_client_type curr_client_type
					= dpu_crtc_get_client_type(crtc);
	काष्ठा drm_crtc *पंचांगp_crtc;
	काष्ठा dpu_crtc_state *dpu_cstate;
	पूर्णांक i, ret = 0;
	u64 avg_bw;

	drm_क्रम_each_crtc(पंचांगp_crtc, crtc->dev) अणु
		अगर (पंचांगp_crtc->enabled &&
			curr_client_type ==
				dpu_crtc_get_client_type(पंचांगp_crtc)) अणु
			dpu_cstate = to_dpu_crtc_state(पंचांगp_crtc->state);

			perf.max_per_pipe_ib = max(perf.max_per_pipe_ib,
					dpu_cstate->new_perf.max_per_pipe_ib);

			perf.bw_ctl += dpu_cstate->new_perf.bw_ctl;

			DPU_DEBUG("crtc=%d bw=%llu paths:%d\n",
				  पंचांगp_crtc->base.id,
				  dpu_cstate->new_perf.bw_ctl, kms->num_paths);
		पूर्ण
	पूर्ण

	अगर (!kms->num_paths)
		वापस 0;

	avg_bw = perf.bw_ctl;
	करो_भाग(avg_bw, (kms->num_paths * 1000)); /*Bps_to_icc*/

	क्रम (i = 0; i < kms->num_paths; i++)
		icc_set_bw(kms->path[i], avg_bw, perf.max_per_pipe_ib);

	वापस ret;
पूर्ण

/**
 * dpu_core_perf_crtc_release_bw() - request zero bandwidth
 * @crtc: poपूर्णांकer to a crtc
 *
 * Function checks a state variable क्रम the crtc, अगर all pending commit
 * requests are करोne, meaning no more bandwidth is needed, release
 * bandwidth request.
 */
व्योम dpu_core_perf_crtc_release_bw(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा dpu_crtc *dpu_crtc;
	काष्ठा dpu_kms *kms;

	अगर (!crtc) अणु
		DPU_ERROR("invalid crtc\n");
		वापस;
	पूर्ण

	kms = _dpu_crtc_get_kms(crtc);
	अगर (!kms->catalog) अणु
		DPU_ERROR("invalid kms\n");
		वापस;
	पूर्ण

	dpu_crtc = to_dpu_crtc(crtc);

	अगर (atomic_dec_वापस(&kms->bandwidth_ref) > 0)
		वापस;

	/* Release the bandwidth */
	अगर (kms->perf.enable_bw_release) अणु
		trace_dpu_cmd_release_bw(crtc->base.id);
		DPU_DEBUG("Release BW crtc=%d\n", crtc->base.id);
		dpu_crtc->cur_perf.bw_ctl = 0;
		_dpu_core_perf_crtc_update_bus(kms, crtc);
	पूर्ण
पूर्ण

अटल पूर्णांक _dpu_core_perf_set_core_clk_rate(काष्ठा dpu_kms *kms, u64 rate)
अणु
	काष्ठा dss_clk *core_clk = kms->perf.core_clk;

	अगर (core_clk->max_rate && (rate > core_clk->max_rate))
		rate = core_clk->max_rate;

	core_clk->rate = rate;
	वापस dev_pm_opp_set_rate(&kms->pdev->dev, core_clk->rate);
पूर्ण

अटल u64 _dpu_core_perf_get_core_clk_rate(काष्ठा dpu_kms *kms)
अणु
	u64 clk_rate = kms->perf.perf_tune.min_core_clk;
	काष्ठा drm_crtc *crtc;
	काष्ठा dpu_crtc_state *dpu_cstate;

	drm_क्रम_each_crtc(crtc, kms->dev) अणु
		अगर (crtc->enabled) अणु
			dpu_cstate = to_dpu_crtc_state(crtc->state);
			clk_rate = max(dpu_cstate->new_perf.core_clk_rate,
							clk_rate);
			clk_rate = clk_round_rate(kms->perf.core_clk->clk,
					clk_rate);
		पूर्ण
	पूर्ण

	अगर (kms->perf.perf_tune.mode == DPU_PERF_MODE_FIXED)
		clk_rate = kms->perf.fix_core_clk_rate;

	DPU_DEBUG("clk:%llu\n", clk_rate);

	वापस clk_rate;
पूर्ण

पूर्णांक dpu_core_perf_crtc_update(काष्ठा drm_crtc *crtc,
		पूर्णांक params_changed, bool stop_req)
अणु
	काष्ठा dpu_core_perf_params *new, *old;
	bool update_bus = false, update_clk = false;
	u64 clk_rate = 0;
	काष्ठा dpu_crtc *dpu_crtc;
	काष्ठा dpu_crtc_state *dpu_cstate;
	काष्ठा dpu_kms *kms;
	पूर्णांक ret;

	अगर (!crtc) अणु
		DPU_ERROR("invalid crtc\n");
		वापस -EINVAL;
	पूर्ण

	kms = _dpu_crtc_get_kms(crtc);
	अगर (!kms->catalog) अणु
		DPU_ERROR("invalid kms\n");
		वापस -EINVAL;
	पूर्ण

	dpu_crtc = to_dpu_crtc(crtc);
	dpu_cstate = to_dpu_crtc_state(crtc->state);

	DPU_DEBUG("crtc:%d stop_req:%d core_clk:%llu\n",
			crtc->base.id, stop_req, kms->perf.core_clk_rate);

	old = &dpu_crtc->cur_perf;
	new = &dpu_cstate->new_perf;

	अगर (crtc->enabled && !stop_req) अणु
		/*
		 * हालs क्रम bus bandwidth update.
		 * 1. new bandwidth vote - "ab or ib vote" is higher
		 *    than current vote क्रम update request.
		 * 2. new bandwidth vote - "ab or ib vote" is lower
		 *    than current vote at end of commit or stop.
		 */
		अगर ((params_changed && ((new->bw_ctl > old->bw_ctl) ||
			(new->max_per_pipe_ib > old->max_per_pipe_ib)))	||
			(!params_changed && ((new->bw_ctl < old->bw_ctl) ||
			(new->max_per_pipe_ib < old->max_per_pipe_ib)))) अणु
			DPU_DEBUG("crtc=%d p=%d new_bw=%llu,old_bw=%llu\n",
				crtc->base.id, params_changed,
				new->bw_ctl, old->bw_ctl);
			old->bw_ctl = new->bw_ctl;
			old->max_per_pipe_ib = new->max_per_pipe_ib;
			update_bus = true;
		पूर्ण

		अगर ((params_changed &&
			(new->core_clk_rate > old->core_clk_rate)) ||
			(!params_changed &&
			(new->core_clk_rate < old->core_clk_rate))) अणु
			old->core_clk_rate = new->core_clk_rate;
			update_clk = true;
		पूर्ण
	पूर्ण अन्यथा अणु
		DPU_DEBUG("crtc=%d disable\n", crtc->base.id);
		स_रखो(old, 0, माप(*old));
		update_bus = true;
		update_clk = true;
	पूर्ण

	trace_dpu_perf_crtc_update(crtc->base.id, new->bw_ctl,
		new->core_clk_rate, stop_req, update_bus, update_clk);

	अगर (update_bus) अणु
		ret = _dpu_core_perf_crtc_update_bus(kms, crtc);
		अगर (ret) अणु
			DPU_ERROR("crtc-%d: failed to update bus bw vote\n",
				  crtc->base.id);
			वापस ret;
		पूर्ण
	पूर्ण

	/*
	 * Update the घड़ी after bandwidth vote to ensure
	 * bandwidth is available beक्रमe घड़ी rate is increased.
	 */
	अगर (update_clk) अणु
		clk_rate = _dpu_core_perf_get_core_clk_rate(kms);

		trace_dpu_core_perf_update_clk(kms->dev, stop_req, clk_rate);

		ret = _dpu_core_perf_set_core_clk_rate(kms, clk_rate);
		अगर (ret) अणु
			DPU_ERROR("failed to set %s clock rate %llu\n",
					kms->perf.core_clk->clk_name, clk_rate);
			वापस ret;
		पूर्ण

		kms->perf.core_clk_rate = clk_rate;
		DPU_DEBUG("update clk rate = %lld HZ\n", clk_rate);
	पूर्ण
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS

अटल sमाप_प्रकार _dpu_core_perf_mode_ग_लिखो(काष्ठा file *file,
		    स्थिर अक्षर __user *user_buf, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा dpu_core_perf *perf = file->निजी_data;
	काष्ठा dpu_perf_cfg *cfg = &perf->catalog->perf;
	u32 perf_mode = 0;
	पूर्णांक ret;

	ret = kstrtouपूर्णांक_from_user(user_buf, count, 0, &perf_mode);
	अगर (ret)
		वापस ret;

	अगर (perf_mode >= DPU_PERF_MODE_MAX)
		वापस -EINVAL;

	अगर (perf_mode == DPU_PERF_MODE_FIXED) अणु
		DRM_INFO("fix performance mode\n");
	पूर्ण अन्यथा अगर (perf_mode == DPU_PERF_MODE_MINIMUM) अणु
		/* run the driver with max clk and BW vote */
		perf->perf_tune.min_core_clk = perf->max_core_clk_rate;
		perf->perf_tune.min_bus_vote =
				(u64) cfg->max_bw_high * 1000;
		DRM_INFO("minimum performance mode\n");
	पूर्ण अन्यथा अगर (perf_mode == DPU_PERF_MODE_NORMAL) अणु
		/* reset the perf tune params to 0 */
		perf->perf_tune.min_core_clk = 0;
		perf->perf_tune.min_bus_vote = 0;
		DRM_INFO("normal performance mode\n");
	पूर्ण
	perf->perf_tune.mode = perf_mode;

	वापस count;
पूर्ण

अटल sमाप_प्रकार _dpu_core_perf_mode_पढ़ो(काष्ठा file *file,
			अक्षर __user *buff, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा dpu_core_perf *perf = file->निजी_data;
	पूर्णांक len;
	अक्षर buf[128];

	len = scnम_लिखो(buf, माप(buf),
			"mode %d min_mdp_clk %llu min_bus_vote %llu\n",
			perf->perf_tune.mode,
			perf->perf_tune.min_core_clk,
			perf->perf_tune.min_bus_vote);

	वापस simple_पढ़ो_from_buffer(buff, count, ppos, buf, len);
पूर्ण

अटल स्थिर काष्ठा file_operations dpu_core_perf_mode_fops = अणु
	.खोलो = simple_खोलो,
	.पढ़ो = _dpu_core_perf_mode_पढ़ो,
	.ग_लिखो = _dpu_core_perf_mode_ग_लिखो,
पूर्ण;

पूर्णांक dpu_core_perf_debugfs_init(काष्ठा dpu_kms *dpu_kms, काष्ठा dentry *parent)
अणु
	काष्ठा dpu_core_perf *perf = &dpu_kms->perf;
	काष्ठा dpu_mdss_cfg *catalog = perf->catalog;
	काष्ठा dentry *entry;

	entry = debugfs_create_dir("core_perf", parent);

	debugfs_create_u64("max_core_clk_rate", 0600, entry,
			&perf->max_core_clk_rate);
	debugfs_create_u64("core_clk_rate", 0600, entry,
			&perf->core_clk_rate);
	debugfs_create_u32("enable_bw_release", 0600, entry,
			(u32 *)&perf->enable_bw_release);
	debugfs_create_u32("threshold_low", 0600, entry,
			(u32 *)&catalog->perf.max_bw_low);
	debugfs_create_u32("threshold_high", 0600, entry,
			(u32 *)&catalog->perf.max_bw_high);
	debugfs_create_u32("min_core_ib", 0600, entry,
			(u32 *)&catalog->perf.min_core_ib);
	debugfs_create_u32("min_llcc_ib", 0600, entry,
			(u32 *)&catalog->perf.min_llcc_ib);
	debugfs_create_u32("min_dram_ib", 0600, entry,
			(u32 *)&catalog->perf.min_dram_ib);
	debugfs_create_file("perf_mode", 0600, entry,
			(u32 *)perf, &dpu_core_perf_mode_fops);
	debugfs_create_u64("fix_core_clk_rate", 0600, entry,
			&perf->fix_core_clk_rate);
	debugfs_create_u64("fix_core_ib_vote", 0600, entry,
			&perf->fix_core_ib_vote);
	debugfs_create_u64("fix_core_ab_vote", 0600, entry,
			&perf->fix_core_ab_vote);

	वापस 0;
पूर्ण
#पूर्ण_अगर

व्योम dpu_core_perf_destroy(काष्ठा dpu_core_perf *perf)
अणु
	अगर (!perf) अणु
		DPU_ERROR("invalid parameters\n");
		वापस;
	पूर्ण

	perf->max_core_clk_rate = 0;
	perf->core_clk = शून्य;
	perf->catalog = शून्य;
	perf->dev = शून्य;
पूर्ण

पूर्णांक dpu_core_perf_init(काष्ठा dpu_core_perf *perf,
		काष्ठा drm_device *dev,
		काष्ठा dpu_mdss_cfg *catalog,
		काष्ठा dss_clk *core_clk)
अणु
	perf->dev = dev;
	perf->catalog = catalog;
	perf->core_clk = core_clk;

	perf->max_core_clk_rate = core_clk->max_rate;
	अगर (!perf->max_core_clk_rate) अणु
		DPU_DEBUG("optional max core clk rate, use default\n");
		perf->max_core_clk_rate = DPU_PERF_DEFAULT_MAX_CORE_CLK_RATE;
	पूर्ण

	वापस 0;
पूर्ण
