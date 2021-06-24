<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2015-2018, The Linux Foundation. All rights reserved.
 */

#घोषणा pr_fmt(fmt)	"[drm:%s:%d] " fmt, __func__, __LINE__

#समावेश <linux/debugfs.h>
#समावेश <linux/delay.h>

#समावेश "dpu_vbif.h"
#समावेश "dpu_hw_vbif.h"
#समावेश "dpu_trace.h"

/**
 * _dpu_vbअगर_रुको_क्रम_xin_halt - रुको क्रम the xin to halt
 * @vbअगर:	Poपूर्णांकer to hardware vbअगर driver
 * @xin_id:	Client पूर्णांकerface identअगरier
 * @वापस:	0 अगर success; error code otherwise
 */
अटल पूर्णांक _dpu_vbअगर_रुको_क्रम_xin_halt(काष्ठा dpu_hw_vbअगर *vbअगर, u32 xin_id)
अणु
	kसमय_प्रकार समयout;
	bool status;
	पूर्णांक rc;

	अगर (!vbअगर || !vbअगर->cap || !vbअगर->ops.get_halt_ctrl) अणु
		DPU_ERROR("invalid arguments vbif %d\n", vbअगर != शून्य);
		वापस -EINVAL;
	पूर्ण

	समयout = kसमय_add_us(kसमय_get(), vbअगर->cap->xin_halt_समयout);
	क्रम (;;) अणु
		status = vbअगर->ops.get_halt_ctrl(vbअगर, xin_id);
		अगर (status)
			अवरोध;
		अगर (kसमय_compare_safe(kसमय_get(), समयout) > 0) अणु
			status = vbअगर->ops.get_halt_ctrl(vbअगर, xin_id);
			अवरोध;
		पूर्ण
		usleep_range(501, 1000);
	पूर्ण

	अगर (!status) अणु
		rc = -ETIMEDOUT;
		DPU_ERROR("VBIF %d client %d not halting. TIMEDOUT.\n",
				vbअगर->idx - VBIF_0, xin_id);
	पूर्ण अन्यथा अणु
		rc = 0;
		DPU_DEBUG("VBIF %d client %d is halted\n",
				vbअगर->idx - VBIF_0, xin_id);
	पूर्ण

	वापस rc;
पूर्ण

/**
 * _dpu_vbअगर_apply_dynamic_ot_limit - determine OT based on useहाल parameters
 * @vbअगर:	Poपूर्णांकer to hardware vbअगर driver
 * @ot_lim:	Poपूर्णांकer to OT limit to be modअगरied
 * @params:	Poपूर्णांकer to useहाल parameters
 */
अटल व्योम _dpu_vbअगर_apply_dynamic_ot_limit(काष्ठा dpu_hw_vbअगर *vbअगर,
		u32 *ot_lim, काष्ठा dpu_vbअगर_set_ot_params *params)
अणु
	u64 pps;
	स्थिर काष्ठा dpu_vbअगर_dynamic_ot_tbl *tbl;
	u32 i;

	अगर (!vbअगर || !(vbअगर->cap->features & BIT(DPU_VBIF_QOS_OTLIM)))
		वापस;

	/* Dynamic OT setting करोne only क्रम WFD */
	अगर (!params->is_wfd)
		वापस;

	pps = params->frame_rate;
	pps *= params->width;
	pps *= params->height;

	tbl = params->rd ? &vbअगर->cap->dynamic_ot_rd_tbl :
			&vbअगर->cap->dynamic_ot_wr_tbl;

	क्रम (i = 0; i < tbl->count; i++) अणु
		अगर (pps <= tbl->cfg[i].pps) अणु
			*ot_lim = tbl->cfg[i].ot_limit;
			अवरोध;
		पूर्ण
	पूर्ण

	DPU_DEBUG("vbif:%d xin:%d w:%d h:%d fps:%d pps:%llu ot:%u\n",
			vbअगर->idx - VBIF_0, params->xin_id,
			params->width, params->height, params->frame_rate,
			pps, *ot_lim);
पूर्ण

/**
 * _dpu_vbअगर_get_ot_limit - get OT based on useहाल & configuration parameters
 * @vbअगर:	Poपूर्णांकer to hardware vbअगर driver
 * @params:	Poपूर्णांकer to useहाल parameters
 * @वापस:	OT limit
 */
अटल u32 _dpu_vbअगर_get_ot_limit(काष्ठा dpu_hw_vbअगर *vbअगर,
	काष्ठा dpu_vbअगर_set_ot_params *params)
अणु
	u32 ot_lim = 0;
	u32 val;

	अगर (!vbअगर || !vbअगर->cap) अणु
		DPU_ERROR("invalid arguments vbif %d\n", vbअगर != शून्य);
		वापस -EINVAL;
	पूर्ण

	अगर (vbअगर->cap->शेष_ot_wr_limit && !params->rd)
		ot_lim = vbअगर->cap->शेष_ot_wr_limit;
	अन्यथा अगर (vbअगर->cap->शेष_ot_rd_limit && params->rd)
		ot_lim = vbअगर->cap->शेष_ot_rd_limit;

	/*
	 * If शेष ot is not set from dt/catalog,
	 * then करो not configure it.
	 */
	अगर (ot_lim == 0)
		जाओ निकास;

	/* Modअगरy the limits अगर the target and the use हाल requires it */
	_dpu_vbअगर_apply_dynamic_ot_limit(vbअगर, &ot_lim, params);

	अगर (vbअगर && vbअगर->ops.get_limit_conf) अणु
		val = vbअगर->ops.get_limit_conf(vbअगर,
				params->xin_id, params->rd);
		अगर (val == ot_lim)
			ot_lim = 0;
	पूर्ण

निकास:
	DPU_DEBUG("vbif:%d xin:%d ot_lim:%d\n",
			vbअगर->idx - VBIF_0, params->xin_id, ot_lim);
	वापस ot_lim;
पूर्ण

/**
 * dpu_vbअगर_set_ot_limit - set OT based on useहाल & configuration parameters
 * @dpu_kms:	DPU handler
 * @params:	Poपूर्णांकer to useहाल parameters
 *
 * Note this function would block रुकोing क्रम bus halt.
 */
व्योम dpu_vbअगर_set_ot_limit(काष्ठा dpu_kms *dpu_kms,
		काष्ठा dpu_vbअगर_set_ot_params *params)
अणु
	काष्ठा dpu_hw_vbअगर *vbअगर = शून्य;
	काष्ठा dpu_hw_mdp *mdp;
	bool क्रमced_on = false;
	u32 ot_lim;
	पूर्णांक ret, i;

	mdp = dpu_kms->hw_mdp;

	क्रम (i = 0; i < ARRAY_SIZE(dpu_kms->hw_vbअगर); i++) अणु
		अगर (dpu_kms->hw_vbअगर[i] &&
				dpu_kms->hw_vbअगर[i]->idx == params->vbअगर_idx)
			vbअगर = dpu_kms->hw_vbअगर[i];
	पूर्ण

	अगर (!vbअगर || !mdp) अणु
		DPU_DEBUG("invalid arguments vbif %d mdp %d\n",
				vbअगर != शून्य, mdp != शून्य);
		वापस;
	पूर्ण

	अगर (!mdp->ops.setup_clk_क्रमce_ctrl ||
			!vbअगर->ops.set_limit_conf ||
			!vbअगर->ops.set_halt_ctrl)
		वापस;

	/* set ग_लिखो_gather_en क्रम all ग_लिखो clients */
	अगर (vbअगर->ops.set_ग_लिखो_gather_en && !params->rd)
		vbअगर->ops.set_ग_लिखो_gather_en(vbअगर, params->xin_id);

	ot_lim = _dpu_vbअगर_get_ot_limit(vbअगर, params) & 0xFF;

	अगर (ot_lim == 0)
		वापस;

	trace_dpu_perf_set_ot(params->num, params->xin_id, ot_lim,
		params->vbअगर_idx);

	क्रमced_on = mdp->ops.setup_clk_क्रमce_ctrl(mdp, params->clk_ctrl, true);

	vbअगर->ops.set_limit_conf(vbअगर, params->xin_id, params->rd, ot_lim);

	vbअगर->ops.set_halt_ctrl(vbअगर, params->xin_id, true);

	ret = _dpu_vbअगर_रुको_क्रम_xin_halt(vbअगर, params->xin_id);
	अगर (ret)
		trace_dpu_vbअगर_रुको_xin_halt_fail(vbअगर->idx, params->xin_id);

	vbअगर->ops.set_halt_ctrl(vbअगर, params->xin_id, false);

	अगर (क्रमced_on)
		mdp->ops.setup_clk_क्रमce_ctrl(mdp, params->clk_ctrl, false);
पूर्ण

व्योम dpu_vbअगर_set_qos_remap(काष्ठा dpu_kms *dpu_kms,
		काष्ठा dpu_vbअगर_set_qos_params *params)
अणु
	काष्ठा dpu_hw_vbअगर *vbअगर = शून्य;
	काष्ठा dpu_hw_mdp *mdp;
	bool क्रमced_on = false;
	स्थिर काष्ठा dpu_vbअगर_qos_tbl *qos_tbl;
	पूर्णांक i;

	अगर (!params || !dpu_kms->hw_mdp) अणु
		DPU_ERROR("invalid arguments\n");
		वापस;
	पूर्ण
	mdp = dpu_kms->hw_mdp;

	क्रम (i = 0; i < ARRAY_SIZE(dpu_kms->hw_vbअगर); i++) अणु
		अगर (dpu_kms->hw_vbअगर[i] &&
				dpu_kms->hw_vbअगर[i]->idx == params->vbअगर_idx) अणु
			vbअगर = dpu_kms->hw_vbअगर[i];
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!vbअगर || !vbअगर->cap) अणु
		DPU_ERROR("invalid vbif %d\n", params->vbअगर_idx);
		वापस;
	पूर्ण

	अगर (!vbअगर->ops.set_qos_remap || !mdp->ops.setup_clk_क्रमce_ctrl) अणु
		DPU_DEBUG("qos remap not supported\n");
		वापस;
	पूर्ण

	qos_tbl = params->is_rt ? &vbअगर->cap->qos_rt_tbl :
			&vbअगर->cap->qos_nrt_tbl;

	अगर (!qos_tbl->npriority_lvl || !qos_tbl->priority_lvl) अणु
		DPU_DEBUG("qos tbl not defined\n");
		वापस;
	पूर्ण

	क्रमced_on = mdp->ops.setup_clk_क्रमce_ctrl(mdp, params->clk_ctrl, true);

	क्रम (i = 0; i < qos_tbl->npriority_lvl; i++) अणु
		DPU_DEBUG("vbif:%d xin:%d lvl:%d/%d\n",
				params->vbअगर_idx, params->xin_id, i,
				qos_tbl->priority_lvl[i]);
		vbअगर->ops.set_qos_remap(vbअगर, params->xin_id, i,
				qos_tbl->priority_lvl[i]);
	पूर्ण

	अगर (क्रमced_on)
		mdp->ops.setup_clk_क्रमce_ctrl(mdp, params->clk_ctrl, false);
पूर्ण

व्योम dpu_vbअगर_clear_errors(काष्ठा dpu_kms *dpu_kms)
अणु
	काष्ठा dpu_hw_vbअगर *vbअगर;
	u32 i, pnd, src;

	क्रम (i = 0; i < ARRAY_SIZE(dpu_kms->hw_vbअगर); i++) अणु
		vbअगर = dpu_kms->hw_vbअगर[i];
		अगर (vbअगर && vbअगर->ops.clear_errors) अणु
			vbअगर->ops.clear_errors(vbअगर, &pnd, &src);
			अगर (pnd || src) अणु
				DRM_DEBUG_KMS("VBIF %d: pnd 0x%X, src 0x%X\n",
					      vbअगर->idx - VBIF_0, pnd, src);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

व्योम dpu_vbअगर_init_memtypes(काष्ठा dpu_kms *dpu_kms)
अणु
	काष्ठा dpu_hw_vbअगर *vbअगर;
	पूर्णांक i, j;

	क्रम (i = 0; i < ARRAY_SIZE(dpu_kms->hw_vbअगर); i++) अणु
		vbअगर = dpu_kms->hw_vbअगर[i];
		अगर (vbअगर && vbअगर->cap && vbअगर->ops.set_mem_type) अणु
			क्रम (j = 0; j < vbअगर->cap->memtype_count; j++)
				vbअगर->ops.set_mem_type(
						vbअगर, j, vbअगर->cap->memtype[j]);
		पूर्ण
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS

व्योम dpu_debugfs_vbअगर_init(काष्ठा dpu_kms *dpu_kms, काष्ठा dentry *debugfs_root)
अणु
	अक्षर vbअगर_name[32];
	काष्ठा dentry *entry, *debugfs_vbअगर;
	पूर्णांक i, j;

	entry = debugfs_create_dir("vbif", debugfs_root);

	क्रम (i = 0; i < dpu_kms->catalog->vbअगर_count; i++) अणु
		स्थिर काष्ठा dpu_vbअगर_cfg *vbअगर = &dpu_kms->catalog->vbअगर[i];

		snम_लिखो(vbअगर_name, माप(vbअगर_name), "%d", vbअगर->id);

		debugfs_vbअगर = debugfs_create_dir(vbअगर_name, entry);

		debugfs_create_u32("features", 0600, debugfs_vbअगर,
			(u32 *)&vbअगर->features);

		debugfs_create_u32("xin_halt_timeout", 0400, debugfs_vbअगर,
			(u32 *)&vbअगर->xin_halt_समयout);

		debugfs_create_u32("default_rd_ot_limit", 0400, debugfs_vbअगर,
			(u32 *)&vbअगर->शेष_ot_rd_limit);

		debugfs_create_u32("default_wr_ot_limit", 0400, debugfs_vbअगर,
			(u32 *)&vbअगर->शेष_ot_wr_limit);

		क्रम (j = 0; j < vbअगर->dynamic_ot_rd_tbl.count; j++) अणु
			स्थिर काष्ठा dpu_vbअगर_dynamic_ot_cfg *cfg =
					&vbअगर->dynamic_ot_rd_tbl.cfg[j];

			snम_लिखो(vbअगर_name, माप(vbअगर_name),
					"dynamic_ot_rd_%d_pps", j);
			debugfs_create_u64(vbअगर_name, 0400, debugfs_vbअगर,
					(u64 *)&cfg->pps);
			snम_लिखो(vbअगर_name, माप(vbअगर_name),
					"dynamic_ot_rd_%d_ot_limit", j);
			debugfs_create_u32(vbअगर_name, 0400, debugfs_vbअगर,
					(u32 *)&cfg->ot_limit);
		पूर्ण

		क्रम (j = 0; j < vbअगर->dynamic_ot_wr_tbl.count; j++) अणु
			स्थिर काष्ठा dpu_vbअगर_dynamic_ot_cfg *cfg =
					&vbअगर->dynamic_ot_wr_tbl.cfg[j];

			snम_लिखो(vbअगर_name, माप(vbअगर_name),
					"dynamic_ot_wr_%d_pps", j);
			debugfs_create_u64(vbअगर_name, 0400, debugfs_vbअगर,
					(u64 *)&cfg->pps);
			snम_लिखो(vbअगर_name, माप(vbअगर_name),
					"dynamic_ot_wr_%d_ot_limit", j);
			debugfs_create_u32(vbअगर_name, 0400, debugfs_vbअगर,
					(u32 *)&cfg->ot_limit);
		पूर्ण
	पूर्ण
पूर्ण
#पूर्ण_अगर
