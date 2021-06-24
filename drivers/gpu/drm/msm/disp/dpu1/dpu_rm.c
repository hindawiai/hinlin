<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2016-2018, The Linux Foundation. All rights reserved.
 */

#घोषणा pr_fmt(fmt)	"[drm:%s] " fmt, __func__
#समावेश "dpu_kms.h"
#समावेश "dpu_hw_lm.h"
#समावेश "dpu_hw_ctl.h"
#समावेश "dpu_hw_pingpong.h"
#समावेश "dpu_hw_intf.h"
#समावेश "dpu_hw_dspp.h"
#समावेश "dpu_hw_merge3d.h"
#समावेश "dpu_encoder.h"
#समावेश "dpu_trace.h"


अटल अंतरभूत bool reserved_by_other(uपूर्णांक32_t *res_map, पूर्णांक idx,
				     uपूर्णांक32_t enc_id)
अणु
	वापस res_map[idx] && res_map[idx] != enc_id;
पूर्ण

/**
 * काष्ठा dpu_rm_requirements - Reservation requirements parameter bundle
 * @topology:  selected topology क्रम the display
 * @hw_res:	   Hardware resources required as reported by the encoders
 */
काष्ठा dpu_rm_requirements अणु
	काष्ठा msm_display_topology topology;
	काष्ठा dpu_encoder_hw_resources hw_res;
पूर्ण;

पूर्णांक dpu_rm_destroy(काष्ठा dpu_rm *rm)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(rm->pingpong_blks); i++) अणु
		काष्ठा dpu_hw_pingpong *hw;

		अगर (rm->pingpong_blks[i]) अणु
			hw = to_dpu_hw_pingpong(rm->pingpong_blks[i]);
			dpu_hw_pingpong_destroy(hw);
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < ARRAY_SIZE(rm->merge_3d_blks); i++) अणु
		काष्ठा dpu_hw_merge_3d *hw;

		अगर (rm->merge_3d_blks[i]) अणु
			hw = to_dpu_hw_merge_3d(rm->merge_3d_blks[i]);
			dpu_hw_merge_3d_destroy(hw);
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < ARRAY_SIZE(rm->mixer_blks); i++) अणु
		काष्ठा dpu_hw_mixer *hw;

		अगर (rm->mixer_blks[i]) अणु
			hw = to_dpu_hw_mixer(rm->mixer_blks[i]);
			dpu_hw_lm_destroy(hw);
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < ARRAY_SIZE(rm->ctl_blks); i++) अणु
		काष्ठा dpu_hw_ctl *hw;

		अगर (rm->ctl_blks[i]) अणु
			hw = to_dpu_hw_ctl(rm->ctl_blks[i]);
			dpu_hw_ctl_destroy(hw);
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < ARRAY_SIZE(rm->पूर्णांकf_blks); i++) अणु
		काष्ठा dpu_hw_पूर्णांकf *hw;

		अगर (rm->पूर्णांकf_blks[i]) अणु
			hw = to_dpu_hw_पूर्णांकf(rm->पूर्णांकf_blks[i]);
			dpu_hw_पूर्णांकf_destroy(hw);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक dpu_rm_init(काष्ठा dpu_rm *rm,
		काष्ठा dpu_mdss_cfg *cat,
		व्योम __iomem *mmio)
अणु
	पूर्णांक rc, i;

	अगर (!rm || !cat || !mmio) अणु
		DPU_ERROR("invalid kms\n");
		वापस -EINVAL;
	पूर्ण

	/* Clear, setup lists */
	स_रखो(rm, 0, माप(*rm));

	/* Interrogate HW catalog and create tracking items क्रम hw blocks */
	क्रम (i = 0; i < cat->mixer_count; i++) अणु
		काष्ठा dpu_hw_mixer *hw;
		स्थिर काष्ठा dpu_lm_cfg *lm = &cat->mixer[i];

		अगर (lm->pingpong == PINGPONG_MAX) अणु
			DPU_DEBUG("skip mixer %d without pingpong\n", lm->id);
			जारी;
		पूर्ण

		अगर (lm->id < LM_0 || lm->id >= LM_MAX) अणु
			DPU_ERROR("skip mixer %d with invalid id\n", lm->id);
			जारी;
		पूर्ण
		hw = dpu_hw_lm_init(lm->id, mmio, cat);
		अगर (IS_ERR_OR_शून्य(hw)) अणु
			rc = PTR_ERR(hw);
			DPU_ERROR("failed lm object creation: err %d\n", rc);
			जाओ fail;
		पूर्ण
		rm->mixer_blks[lm->id - LM_0] = &hw->base;

		अगर (!rm->lm_max_width) अणु
			rm->lm_max_width = lm->sblk->maxwidth;
		पूर्ण अन्यथा अगर (rm->lm_max_width != lm->sblk->maxwidth) अणु
			/*
			 * Don't expect to have hw where lm max widths dअगरfer.
			 * If found, take the min.
			 */
			DPU_ERROR("unsupported: lm maxwidth differs\n");
			अगर (rm->lm_max_width > lm->sblk->maxwidth)
				rm->lm_max_width = lm->sblk->maxwidth;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < cat->merge_3d_count; i++) अणु
		काष्ठा dpu_hw_merge_3d *hw;
		स्थिर काष्ठा dpu_merge_3d_cfg *merge_3d = &cat->merge_3d[i];

		अगर (merge_3d->id < MERGE_3D_0 || merge_3d->id >= MERGE_3D_MAX) अणु
			DPU_ERROR("skip merge_3d %d with invalid id\n", merge_3d->id);
			जारी;
		पूर्ण
		hw = dpu_hw_merge_3d_init(merge_3d->id, mmio, cat);
		अगर (IS_ERR_OR_शून्य(hw)) अणु
			rc = PTR_ERR(hw);
			DPU_ERROR("failed merge_3d object creation: err %d\n",
				rc);
			जाओ fail;
		पूर्ण
		rm->merge_3d_blks[merge_3d->id - MERGE_3D_0] = &hw->base;
	पूर्ण

	क्रम (i = 0; i < cat->pingpong_count; i++) अणु
		काष्ठा dpu_hw_pingpong *hw;
		स्थिर काष्ठा dpu_pingpong_cfg *pp = &cat->pingpong[i];

		अगर (pp->id < PINGPONG_0 || pp->id >= PINGPONG_MAX) अणु
			DPU_ERROR("skip pingpong %d with invalid id\n", pp->id);
			जारी;
		पूर्ण
		hw = dpu_hw_pingpong_init(pp->id, mmio, cat);
		अगर (IS_ERR_OR_शून्य(hw)) अणु
			rc = PTR_ERR(hw);
			DPU_ERROR("failed pingpong object creation: err %d\n",
				rc);
			जाओ fail;
		पूर्ण
		अगर (pp->merge_3d && pp->merge_3d < MERGE_3D_MAX)
			hw->merge_3d = rm->merge_3d_blks[pp->merge_3d - MERGE_3D_0];
		rm->pingpong_blks[pp->id - PINGPONG_0] = &hw->base;
	पूर्ण

	क्रम (i = 0; i < cat->पूर्णांकf_count; i++) अणु
		काष्ठा dpu_hw_पूर्णांकf *hw;
		स्थिर काष्ठा dpu_पूर्णांकf_cfg *पूर्णांकf = &cat->पूर्णांकf[i];

		अगर (पूर्णांकf->type == INTF_NONE) अणु
			DPU_DEBUG("skip intf %d with type none\n", i);
			जारी;
		पूर्ण
		अगर (पूर्णांकf->id < INTF_0 || पूर्णांकf->id >= INTF_MAX) अणु
			DPU_ERROR("skip intf %d with invalid id\n", पूर्णांकf->id);
			जारी;
		पूर्ण
		hw = dpu_hw_पूर्णांकf_init(पूर्णांकf->id, mmio, cat);
		अगर (IS_ERR_OR_शून्य(hw)) अणु
			rc = PTR_ERR(hw);
			DPU_ERROR("failed intf object creation: err %d\n", rc);
			जाओ fail;
		पूर्ण
		rm->पूर्णांकf_blks[पूर्णांकf->id - INTF_0] = &hw->base;
	पूर्ण

	क्रम (i = 0; i < cat->ctl_count; i++) अणु
		काष्ठा dpu_hw_ctl *hw;
		स्थिर काष्ठा dpu_ctl_cfg *ctl = &cat->ctl[i];

		अगर (ctl->id < CTL_0 || ctl->id >= CTL_MAX) अणु
			DPU_ERROR("skip ctl %d with invalid id\n", ctl->id);
			जारी;
		पूर्ण
		hw = dpu_hw_ctl_init(ctl->id, mmio, cat);
		अगर (IS_ERR_OR_शून्य(hw)) अणु
			rc = PTR_ERR(hw);
			DPU_ERROR("failed ctl object creation: err %d\n", rc);
			जाओ fail;
		पूर्ण
		rm->ctl_blks[ctl->id - CTL_0] = &hw->base;
	पूर्ण

	क्रम (i = 0; i < cat->dspp_count; i++) अणु
		काष्ठा dpu_hw_dspp *hw;
		स्थिर काष्ठा dpu_dspp_cfg *dspp = &cat->dspp[i];

		अगर (dspp->id < DSPP_0 || dspp->id >= DSPP_MAX) अणु
			DPU_ERROR("skip dspp %d with invalid id\n", dspp->id);
			जारी;
		पूर्ण
		hw = dpu_hw_dspp_init(dspp->id, mmio, cat);
		अगर (IS_ERR_OR_शून्य(hw)) अणु
			rc = PTR_ERR(hw);
			DPU_ERROR("failed dspp object creation: err %d\n", rc);
			जाओ fail;
		पूर्ण
		rm->dspp_blks[dspp->id - DSPP_0] = &hw->base;
	पूर्ण

	वापस 0;

fail:
	dpu_rm_destroy(rm);

	वापस rc ? rc : -EFAULT;
पूर्ण

अटल bool _dpu_rm_needs_split_display(स्थिर काष्ठा msm_display_topology *top)
अणु
	वापस top->num_पूर्णांकf > 1;
पूर्ण

/**
 * _dpu_rm_check_lm_peer - check अगर a mixer is a peer of the primary
 * @rm: dpu resource manager handle
 * @primary_idx: index of primary mixer in rm->mixer_blks[]
 * @peer_idx: index of other mixer in rm->mixer_blks[]
 * Return: true अगर rm->mixer_blks[peer_idx] is a peer of
 *          rm->mixer_blks[primary_idx]
 */
अटल bool _dpu_rm_check_lm_peer(काष्ठा dpu_rm *rm, पूर्णांक primary_idx,
		पूर्णांक peer_idx)
अणु
	स्थिर काष्ठा dpu_lm_cfg *prim_lm_cfg;
	स्थिर काष्ठा dpu_lm_cfg *peer_cfg;

	prim_lm_cfg = to_dpu_hw_mixer(rm->mixer_blks[primary_idx])->cap;
	peer_cfg = to_dpu_hw_mixer(rm->mixer_blks[peer_idx])->cap;

	अगर (!test_bit(peer_cfg->id, &prim_lm_cfg->lm_pair_mask)) अणु
		DPU_DEBUG("lm %d not peer of lm %d\n", peer_cfg->id,
				peer_cfg->id);
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

/**
 * _dpu_rm_check_lm_and_get_connected_blks - check अगर proposed layer mixer meets
 *	proposed use हाल requirements, incl. hardwired dependent blocks like
 *	pingpong
 * @rm: dpu resource manager handle
 * @global_state: resources shared across multiple kms objects
 * @enc_id: encoder id requesting क्रम allocation
 * @lm_idx: index of proposed layer mixer in rm->mixer_blks[], function checks
 *      अगर lm, and all other hardwired blocks connected to the lm (pp) is
 *      available and appropriate
 * @pp_idx: output parameter, index of pingpong block attached to the layer
 *      mixer in rm->pingpong_blks[].
 * @dspp_idx: output parameter, index of dspp block attached to the layer
 *      mixer in rm->dspp_blks[].
 * @reqs: input parameter, rm requirements क्रम HW blocks needed in the
 *      datapath.
 * Return: true अगर lm matches all requirements, false otherwise
 */
अटल bool _dpu_rm_check_lm_and_get_connected_blks(काष्ठा dpu_rm *rm,
		काष्ठा dpu_global_state *global_state,
		uपूर्णांक32_t enc_id, पूर्णांक lm_idx, पूर्णांक *pp_idx, पूर्णांक *dspp_idx,
		काष्ठा dpu_rm_requirements *reqs)
अणु
	स्थिर काष्ठा dpu_lm_cfg *lm_cfg;
	पूर्णांक idx;

	/* Alपढ़ोy reserved? */
	अगर (reserved_by_other(global_state->mixer_to_enc_id, lm_idx, enc_id)) अणु
		DPU_DEBUG("lm %d already reserved\n", lm_idx + LM_0);
		वापस false;
	पूर्ण

	lm_cfg = to_dpu_hw_mixer(rm->mixer_blks[lm_idx])->cap;
	idx = lm_cfg->pingpong - PINGPONG_0;
	अगर (idx < 0 || idx >= ARRAY_SIZE(rm->pingpong_blks)) अणु
		DPU_ERROR("failed to get pp on lm %d\n", lm_cfg->pingpong);
		वापस false;
	पूर्ण

	अगर (reserved_by_other(global_state->pingpong_to_enc_id, idx, enc_id)) अणु
		DPU_DEBUG("lm %d pp %d already reserved\n", lm_cfg->id,
				lm_cfg->pingpong);
		वापस false;
	पूर्ण
	*pp_idx = idx;

	अगर (!reqs->topology.num_dspp)
		वापस true;

	idx = lm_cfg->dspp - DSPP_0;
	अगर (idx < 0 || idx >= ARRAY_SIZE(rm->dspp_blks)) अणु
		DPU_ERROR("failed to get dspp on lm %d\n", lm_cfg->dspp);
		वापस false;
	पूर्ण

	अगर (reserved_by_other(global_state->dspp_to_enc_id, idx, enc_id)) अणु
		DPU_DEBUG("lm %d dspp %d already reserved\n", lm_cfg->id,
				lm_cfg->dspp);
		वापस false;
	पूर्ण
	*dspp_idx = idx;

	वापस true;
पूर्ण

अटल पूर्णांक _dpu_rm_reserve_lms(काष्ठा dpu_rm *rm,
			       काष्ठा dpu_global_state *global_state,
			       uपूर्णांक32_t enc_id,
			       काष्ठा dpu_rm_requirements *reqs)

अणु
	पूर्णांक lm_idx[MAX_BLOCKS];
	पूर्णांक pp_idx[MAX_BLOCKS];
	पूर्णांक dspp_idx[MAX_BLOCKS] = अणु0पूर्ण;
	पूर्णांक i, j, lm_count = 0;

	अगर (!reqs->topology.num_lm) अणु
		DPU_ERROR("invalid number of lm: %d\n", reqs->topology.num_lm);
		वापस -EINVAL;
	पूर्ण

	/* Find a primary mixer */
	क्रम (i = 0; i < ARRAY_SIZE(rm->mixer_blks) &&
			lm_count < reqs->topology.num_lm; i++) अणु
		अगर (!rm->mixer_blks[i])
			जारी;

		lm_count = 0;
		lm_idx[lm_count] = i;

		अगर (!_dpu_rm_check_lm_and_get_connected_blks(rm, global_state,
				enc_id, i, &pp_idx[lm_count],
				&dspp_idx[lm_count], reqs)) अणु
			जारी;
		पूर्ण

		++lm_count;

		/* Valid primary mixer found, find matching peers */
		क्रम (j = i + 1; j < ARRAY_SIZE(rm->mixer_blks) &&
				lm_count < reqs->topology.num_lm; j++) अणु
			अगर (!rm->mixer_blks[j])
				जारी;

			अगर (!_dpu_rm_check_lm_peer(rm, i, j)) अणु
				DPU_DEBUG("lm %d not peer of lm %d\n", LM_0 + j,
						LM_0 + i);
				जारी;
			पूर्ण

			अगर (!_dpu_rm_check_lm_and_get_connected_blks(rm,
					global_state, enc_id, j,
					&pp_idx[lm_count], &dspp_idx[lm_count],
					reqs)) अणु
				जारी;
			पूर्ण

			lm_idx[lm_count] = j;
			++lm_count;
		पूर्ण
	पूर्ण

	अगर (lm_count != reqs->topology.num_lm) अणु
		DPU_DEBUG("unable to find appropriate mixers\n");
		वापस -ENAVAIL;
	पूर्ण

	क्रम (i = 0; i < lm_count; i++) अणु
		global_state->mixer_to_enc_id[lm_idx[i]] = enc_id;
		global_state->pingpong_to_enc_id[pp_idx[i]] = enc_id;
		global_state->dspp_to_enc_id[dspp_idx[i]] =
			reqs->topology.num_dspp ? enc_id : 0;

		trace_dpu_rm_reserve_lms(lm_idx[i] + LM_0, enc_id,
					 pp_idx[i] + PINGPONG_0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक _dpu_rm_reserve_ctls(
		काष्ठा dpu_rm *rm,
		काष्ठा dpu_global_state *global_state,
		uपूर्णांक32_t enc_id,
		स्थिर काष्ठा msm_display_topology *top)
अणु
	पूर्णांक ctl_idx[MAX_BLOCKS];
	पूर्णांक i = 0, j, num_ctls;
	bool needs_split_display;

	/* each hw_पूर्णांकf needs its own hw_ctrl to program its control path */
	num_ctls = top->num_पूर्णांकf;

	needs_split_display = _dpu_rm_needs_split_display(top);

	क्रम (j = 0; j < ARRAY_SIZE(rm->ctl_blks); j++) अणु
		स्थिर काष्ठा dpu_hw_ctl *ctl;
		अचिन्हित दीर्घ features;
		bool has_split_display;

		अगर (!rm->ctl_blks[j])
			जारी;
		अगर (reserved_by_other(global_state->ctl_to_enc_id, j, enc_id))
			जारी;

		ctl = to_dpu_hw_ctl(rm->ctl_blks[j]);
		features = ctl->caps->features;
		has_split_display = BIT(DPU_CTL_SPLIT_DISPLAY) & features;

		DPU_DEBUG("ctl %d caps 0x%lX\n", rm->ctl_blks[j]->id, features);

		अगर (needs_split_display != has_split_display)
			जारी;

		ctl_idx[i] = j;
		DPU_DEBUG("ctl %d match\n", j + CTL_0);

		अगर (++i == num_ctls)
			अवरोध;

	पूर्ण

	अगर (i != num_ctls)
		वापस -ENAVAIL;

	क्रम (i = 0; i < ARRAY_SIZE(ctl_idx) && i < num_ctls; i++) अणु
		global_state->ctl_to_enc_id[ctl_idx[i]] = enc_id;
		trace_dpu_rm_reserve_ctls(i + CTL_0, enc_id);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक _dpu_rm_reserve_पूर्णांकf(
		काष्ठा dpu_rm *rm,
		काष्ठा dpu_global_state *global_state,
		uपूर्णांक32_t enc_id,
		uपूर्णांक32_t id)
अणु
	पूर्णांक idx = id - INTF_0;

	अगर (idx < 0 || idx >= ARRAY_SIZE(rm->पूर्णांकf_blks)) अणु
		DPU_ERROR("invalid intf id: %d", id);
		वापस -EINVAL;
	पूर्ण

	अगर (!rm->पूर्णांकf_blks[idx]) अणु
		DPU_ERROR("couldn't find intf id %d\n", id);
		वापस -EINVAL;
	पूर्ण

	अगर (reserved_by_other(global_state->पूर्णांकf_to_enc_id, idx, enc_id)) अणु
		DPU_ERROR("intf id %d already reserved\n", id);
		वापस -ENAVAIL;
	पूर्ण

	global_state->पूर्णांकf_to_enc_id[idx] = enc_id;
	वापस 0;
पूर्ण

अटल पूर्णांक _dpu_rm_reserve_पूर्णांकf_related_hw(
		काष्ठा dpu_rm *rm,
		काष्ठा dpu_global_state *global_state,
		uपूर्णांक32_t enc_id,
		काष्ठा dpu_encoder_hw_resources *hw_res)
अणु
	पूर्णांक i, ret = 0;
	u32 id;

	क्रम (i = 0; i < ARRAY_SIZE(hw_res->पूर्णांकfs); i++) अणु
		अगर (hw_res->पूर्णांकfs[i] == INTF_MODE_NONE)
			जारी;
		id = i + INTF_0;
		ret = _dpu_rm_reserve_पूर्णांकf(rm, global_state, enc_id, id);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक _dpu_rm_make_reservation(
		काष्ठा dpu_rm *rm,
		काष्ठा dpu_global_state *global_state,
		काष्ठा drm_encoder *enc,
		काष्ठा dpu_rm_requirements *reqs)
अणु
	पूर्णांक ret;

	ret = _dpu_rm_reserve_lms(rm, global_state, enc->base.id, reqs);
	अगर (ret) अणु
		DPU_ERROR("unable to find appropriate mixers\n");
		वापस ret;
	पूर्ण

	ret = _dpu_rm_reserve_ctls(rm, global_state, enc->base.id,
				&reqs->topology);
	अगर (ret) अणु
		DPU_ERROR("unable to find appropriate CTL\n");
		वापस ret;
	पूर्ण

	ret = _dpu_rm_reserve_पूर्णांकf_related_hw(rm, global_state, enc->base.id,
				&reqs->hw_res);
	अगर (ret)
		वापस ret;

	वापस ret;
पूर्ण

अटल पूर्णांक _dpu_rm_populate_requirements(
		काष्ठा drm_encoder *enc,
		काष्ठा dpu_rm_requirements *reqs,
		काष्ठा msm_display_topology req_topology)
अणु
	dpu_encoder_get_hw_resources(enc, &reqs->hw_res);

	reqs->topology = req_topology;

	DRM_DEBUG_KMS("num_lm: %d num_enc: %d num_intf: %d\n",
		      reqs->topology.num_lm, reqs->topology.num_enc,
		      reqs->topology.num_पूर्णांकf);

	वापस 0;
पूर्ण

अटल व्योम _dpu_rm_clear_mapping(uपूर्णांक32_t *res_mapping, पूर्णांक cnt,
				  uपूर्णांक32_t enc_id)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < cnt; i++) अणु
		अगर (res_mapping[i] == enc_id)
			res_mapping[i] = 0;
	पूर्ण
पूर्ण

व्योम dpu_rm_release(काष्ठा dpu_global_state *global_state,
		    काष्ठा drm_encoder *enc)
अणु
	_dpu_rm_clear_mapping(global_state->pingpong_to_enc_id,
		ARRAY_SIZE(global_state->pingpong_to_enc_id), enc->base.id);
	_dpu_rm_clear_mapping(global_state->mixer_to_enc_id,
		ARRAY_SIZE(global_state->mixer_to_enc_id), enc->base.id);
	_dpu_rm_clear_mapping(global_state->ctl_to_enc_id,
		ARRAY_SIZE(global_state->ctl_to_enc_id), enc->base.id);
	_dpu_rm_clear_mapping(global_state->पूर्णांकf_to_enc_id,
		ARRAY_SIZE(global_state->पूर्णांकf_to_enc_id), enc->base.id);
पूर्ण

पूर्णांक dpu_rm_reserve(
		काष्ठा dpu_rm *rm,
		काष्ठा dpu_global_state *global_state,
		काष्ठा drm_encoder *enc,
		काष्ठा drm_crtc_state *crtc_state,
		काष्ठा msm_display_topology topology)
अणु
	काष्ठा dpu_rm_requirements reqs;
	पूर्णांक ret;

	/* Check अगर this is just a page-flip */
	अगर (!drm_atomic_crtc_needs_modeset(crtc_state))
		वापस 0;

	अगर (IS_ERR(global_state)) अणु
		DPU_ERROR("failed to global state\n");
		वापस PTR_ERR(global_state);
	पूर्ण

	DRM_DEBUG_KMS("reserving hw for enc %d crtc %d\n",
		      enc->base.id, crtc_state->crtc->base.id);

	ret = _dpu_rm_populate_requirements(enc, &reqs, topology);
	अगर (ret) अणु
		DPU_ERROR("failed to populate hw requirements\n");
		वापस ret;
	पूर्ण

	ret = _dpu_rm_make_reservation(rm, global_state, enc, &reqs);
	अगर (ret)
		DPU_ERROR("failed to reserve hw resources: %d\n", ret);



	वापस ret;
पूर्ण

पूर्णांक dpu_rm_get_asचिन्हित_resources(काष्ठा dpu_rm *rm,
	काष्ठा dpu_global_state *global_state, uपूर्णांक32_t enc_id,
	क्रमागत dpu_hw_blk_type type, काष्ठा dpu_hw_blk **blks, पूर्णांक blks_size)
अणु
	काष्ठा dpu_hw_blk **hw_blks;
	uपूर्णांक32_t *hw_to_enc_id;
	पूर्णांक i, num_blks, max_blks;

	चयन (type) अणु
	हाल DPU_HW_BLK_PINGPONG:
		hw_blks = rm->pingpong_blks;
		hw_to_enc_id = global_state->pingpong_to_enc_id;
		max_blks = ARRAY_SIZE(rm->pingpong_blks);
		अवरोध;
	हाल DPU_HW_BLK_LM:
		hw_blks = rm->mixer_blks;
		hw_to_enc_id = global_state->mixer_to_enc_id;
		max_blks = ARRAY_SIZE(rm->mixer_blks);
		अवरोध;
	हाल DPU_HW_BLK_CTL:
		hw_blks = rm->ctl_blks;
		hw_to_enc_id = global_state->ctl_to_enc_id;
		max_blks = ARRAY_SIZE(rm->ctl_blks);
		अवरोध;
	हाल DPU_HW_BLK_INTF:
		hw_blks = rm->पूर्णांकf_blks;
		hw_to_enc_id = global_state->पूर्णांकf_to_enc_id;
		max_blks = ARRAY_SIZE(rm->पूर्णांकf_blks);
		अवरोध;
	हाल DPU_HW_BLK_DSPP:
		hw_blks = rm->dspp_blks;
		hw_to_enc_id = global_state->dspp_to_enc_id;
		max_blks = ARRAY_SIZE(rm->dspp_blks);
		अवरोध;
	शेष:
		DPU_ERROR("blk type %d not managed by rm\n", type);
		वापस 0;
	पूर्ण

	num_blks = 0;
	क्रम (i = 0; i < max_blks; i++) अणु
		अगर (hw_to_enc_id[i] != enc_id)
			जारी;

		अगर (num_blks == blks_size) अणु
			DPU_ERROR("More than %d resources assigned to enc %d\n",
				  blks_size, enc_id);
			अवरोध;
		पूर्ण
		blks[num_blks++] = hw_blks[i];
	पूर्ण

	वापस num_blks;
पूर्ण
