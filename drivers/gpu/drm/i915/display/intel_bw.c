<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#समावेश <drm/drm_atomic_state_helper.h>

#समावेश "intel_atomic.h"
#समावेश "intel_bw.h"
#समावेश "intel_cdclk.h"
#समावेश "intel_display_types.h"
#समावेश "intel_pm.h"
#समावेश "intel_sideband.h"

/* Parameters क्रम Qclk Geyserville (QGV) */
काष्ठा पूर्णांकel_qgv_poपूर्णांक अणु
	u16 dclk, t_rp, t_rdpre, t_rc, t_ras, t_rcd;
पूर्ण;

काष्ठा पूर्णांकel_qgv_info अणु
	काष्ठा पूर्णांकel_qgv_poपूर्णांक poपूर्णांकs[I915_NUM_QGV_POINTS];
	u8 num_poपूर्णांकs;
	u8 t_bl;
पूर्ण;

अटल पूर्णांक icl_pcode_पढ़ो_qgv_poपूर्णांक_info(काष्ठा drm_i915_निजी *dev_priv,
					 काष्ठा पूर्णांकel_qgv_poपूर्णांक *sp,
					 पूर्णांक poपूर्णांक)
अणु
	u32 val = 0, val2 = 0;
	पूर्णांक ret;

	ret = sandybridge_pcode_पढ़ो(dev_priv,
				     ICL_PCODE_MEM_SUBSYSYSTEM_INFO |
				     ICL_PCODE_MEM_SS_READ_QGV_POINT_INFO(poपूर्णांक),
				     &val, &val2);
	अगर (ret)
		वापस ret;

	sp->dclk = val & 0xffff;
	sp->t_rp = (val & 0xff0000) >> 16;
	sp->t_rcd = (val & 0xff000000) >> 24;

	sp->t_rdpre = val2 & 0xff;
	sp->t_ras = (val2 & 0xff00) >> 8;

	sp->t_rc = sp->t_rp + sp->t_ras;

	वापस 0;
पूर्ण

पूर्णांक icl_pcode_restrict_qgv_poपूर्णांकs(काष्ठा drm_i915_निजी *dev_priv,
				  u32 poपूर्णांकs_mask)
अणु
	पूर्णांक ret;

	/* bspec says to keep retrying क्रम at least 1 ms */
	ret = skl_pcode_request(dev_priv, ICL_PCODE_SAGV_DE_MEM_SS_CONFIG,
				poपूर्णांकs_mask,
				ICL_PCODE_POINTS_RESTRICTED_MASK,
				ICL_PCODE_POINTS_RESTRICTED,
				1);

	अगर (ret < 0) अणु
		drm_err(&dev_priv->drm, "Failed to disable qgv points (%d)\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक icl_get_qgv_poपूर्णांकs(काष्ठा drm_i915_निजी *dev_priv,
			      काष्ठा पूर्णांकel_qgv_info *qi)
अणु
	स्थिर काष्ठा dram_info *dram_info = &dev_priv->dram_info;
	पूर्णांक i, ret;

	qi->num_poपूर्णांकs = dram_info->num_qgv_poपूर्णांकs;

	अगर (IS_DISPLAY_VER(dev_priv, 12))
		चयन (dram_info->type) अणु
		हाल INTEL_DRAM_DDR4:
			qi->t_bl = 4;
			अवरोध;
		हाल INTEL_DRAM_DDR5:
			qi->t_bl = 8;
			अवरोध;
		शेष:
			qi->t_bl = 16;
			अवरोध;
		पूर्ण
	अन्यथा अगर (IS_DISPLAY_VER(dev_priv, 11))
		qi->t_bl = dev_priv->dram_info.type == INTEL_DRAM_DDR4 ? 4 : 8;

	अगर (drm_WARN_ON(&dev_priv->drm,
			qi->num_poपूर्णांकs > ARRAY_SIZE(qi->poपूर्णांकs)))
		qi->num_poपूर्णांकs = ARRAY_SIZE(qi->poपूर्णांकs);

	क्रम (i = 0; i < qi->num_poपूर्णांकs; i++) अणु
		काष्ठा पूर्णांकel_qgv_poपूर्णांक *sp = &qi->poपूर्णांकs[i];

		ret = icl_pcode_पढ़ो_qgv_poपूर्णांक_info(dev_priv, sp, i);
		अगर (ret)
			वापस ret;

		drm_dbg_kms(&dev_priv->drm,
			    "QGV %d: DCLK=%d tRP=%d tRDPRE=%d tRAS=%d tRCD=%d tRC=%d\n",
			    i, sp->dclk, sp->t_rp, sp->t_rdpre, sp->t_ras,
			    sp->t_rcd, sp->t_rc);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक icl_calc_bw(पूर्णांक dclk, पूर्णांक num, पूर्णांक den)
अणु
	/* multiples of 16.666MHz (100/6) */
	वापस DIV_ROUND_CLOSEST(num * dclk * 100, den * 6);
पूर्ण

अटल पूर्णांक icl_sagv_max_dclk(स्थिर काष्ठा पूर्णांकel_qgv_info *qi)
अणु
	u16 dclk = 0;
	पूर्णांक i;

	क्रम (i = 0; i < qi->num_poपूर्णांकs; i++)
		dclk = max(dclk, qi->poपूर्णांकs[i].dclk);

	वापस dclk;
पूर्ण

काष्ठा पूर्णांकel_sa_info अणु
	u16 displayrtids;
	u8 deburst, deprogbwlimit;
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_sa_info icl_sa_info = अणु
	.deburst = 8,
	.deprogbwlimit = 25, /* GB/s */
	.displayrtids = 128,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_sa_info tgl_sa_info = अणु
	.deburst = 16,
	.deprogbwlimit = 34, /* GB/s */
	.displayrtids = 256,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_sa_info rkl_sa_info = अणु
	.deburst = 16,
	.deprogbwlimit = 20, /* GB/s */
	.displayrtids = 128,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_sa_info adls_sa_info = अणु
	.deburst = 16,
	.deprogbwlimit = 38, /* GB/s */
	.displayrtids = 256,
पूर्ण;

अटल पूर्णांक icl_get_bw_info(काष्ठा drm_i915_निजी *dev_priv, स्थिर काष्ठा पूर्णांकel_sa_info *sa)
अणु
	काष्ठा पूर्णांकel_qgv_info qi = अणुपूर्ण;
	bool is_y_tile = true; /* assume y tile may be used */
	पूर्णांक num_channels = dev_priv->dram_info.num_channels;
	पूर्णांक deपूर्णांकerleave;
	पूर्णांक ipqdepth, ipqdepthpch;
	पूर्णांक dclk_max;
	पूर्णांक maxdebw;
	पूर्णांक i, ret;

	ret = icl_get_qgv_poपूर्णांकs(dev_priv, &qi);
	अगर (ret) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "Failed to get memory subsystem information, ignoring bandwidth limits");
		वापस ret;
	पूर्ण

	deपूर्णांकerleave = DIV_ROUND_UP(num_channels, is_y_tile ? 4 : 2);
	dclk_max = icl_sagv_max_dclk(&qi);

	ipqdepthpch = 16;

	maxdebw = min(sa->deprogbwlimit * 1000,
		      icl_calc_bw(dclk_max, 16, 1) * 6 / 10); /* 60% */
	ipqdepth = min(ipqdepthpch, sa->displayrtids / num_channels);

	क्रम (i = 0; i < ARRAY_SIZE(dev_priv->max_bw); i++) अणु
		काष्ठा पूर्णांकel_bw_info *bi = &dev_priv->max_bw[i];
		पूर्णांक clpchgroup;
		पूर्णांक j;

		clpchgroup = (sa->deburst * deपूर्णांकerleave / num_channels) << i;
		bi->num_planes = (ipqdepth - clpchgroup) / clpchgroup + 1;

		bi->num_qgv_poपूर्णांकs = qi.num_poपूर्णांकs;

		क्रम (j = 0; j < qi.num_poपूर्णांकs; j++) अणु
			स्थिर काष्ठा पूर्णांकel_qgv_poपूर्णांक *sp = &qi.poपूर्णांकs[j];
			पूर्णांक ct, bw;

			/*
			 * Max row cycle समय
			 *
			 * FIXME what is the logic behind the
			 * assumed burst length?
			 */
			ct = max_t(पूर्णांक, sp->t_rc, sp->t_rp + sp->t_rcd +
				   (clpchgroup - 1) * qi.t_bl + sp->t_rdpre);
			bw = icl_calc_bw(sp->dclk, clpchgroup * 32 * num_channels, ct);

			bi->deratedbw[j] = min(maxdebw,
					       bw * 9 / 10); /* 90% */

			drm_dbg_kms(&dev_priv->drm,
				    "BW%d / QGV %d: num_planes=%d deratedbw=%u\n",
				    i, j, bi->num_planes, bi->deratedbw[j]);
		पूर्ण

		अगर (bi->num_planes == 1)
			अवरोध;
	पूर्ण

	/*
	 * In हाल अगर SAGV is disabled in BIOS, we always get 1
	 * SAGV poपूर्णांक, but we can't send PCode commands to restrict it
	 * as it will fail and poपूर्णांकless anyway.
	 */
	अगर (qi.num_poपूर्णांकs == 1)
		dev_priv->sagv_status = I915_SAGV_NOT_CONTROLLED;
	अन्यथा
		dev_priv->sagv_status = I915_SAGV_ENABLED;

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक icl_max_bw(काष्ठा drm_i915_निजी *dev_priv,
			       पूर्णांक num_planes, पूर्णांक qgv_poपूर्णांक)
अणु
	पूर्णांक i;

	/*
	 * Let's वापस max bw क्रम 0 planes
	 */
	num_planes = max(1, num_planes);

	क्रम (i = 0; i < ARRAY_SIZE(dev_priv->max_bw); i++) अणु
		स्थिर काष्ठा पूर्णांकel_bw_info *bi =
			&dev_priv->max_bw[i];

		/*
		 * Pcode will not expose all QGV poपूर्णांकs when
		 * SAGV is क्रमced to off/min/med/max.
		 */
		अगर (qgv_poपूर्णांक >= bi->num_qgv_poपूर्णांकs)
			वापस अच_पूर्णांक_उच्च;

		अगर (num_planes >= bi->num_planes)
			वापस bi->deratedbw[qgv_poपूर्णांक];
	पूर्ण

	वापस 0;
पूर्ण

व्योम पूर्णांकel_bw_init_hw(काष्ठा drm_i915_निजी *dev_priv)
अणु
	अगर (!HAS_DISPLAY(dev_priv))
		वापस;

	अगर (IS_ALDERLAKE_S(dev_priv))
		icl_get_bw_info(dev_priv, &adls_sa_info);
	अन्यथा अगर (IS_ROCKETLAKE(dev_priv))
		icl_get_bw_info(dev_priv, &rkl_sa_info);
	अन्यथा अगर (IS_DISPLAY_VER(dev_priv, 12))
		icl_get_bw_info(dev_priv, &tgl_sa_info);
	अन्यथा अगर (IS_DISPLAY_VER(dev_priv, 11))
		icl_get_bw_info(dev_priv, &icl_sa_info);
पूर्ण

अटल अचिन्हित पूर्णांक पूर्णांकel_bw_crtc_num_active_planes(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	/*
	 * We assume cursors are small enough
	 * to not not cause bandwidth problems.
	 */
	वापस hweight8(crtc_state->active_planes & ~BIT(PLANE_CURSOR));
पूर्ण

अटल अचिन्हित पूर्णांक पूर्णांकel_bw_crtc_data_rate(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	अचिन्हित पूर्णांक data_rate = 0;
	क्रमागत plane_id plane_id;

	क्रम_each_plane_id_on_crtc(crtc, plane_id) अणु
		/*
		 * We assume cursors are small enough
		 * to not not cause bandwidth problems.
		 */
		अगर (plane_id == PLANE_CURSOR)
			जारी;

		data_rate += crtc_state->data_rate[plane_id];
	पूर्ण

	वापस data_rate;
पूर्ण

व्योम पूर्णांकel_bw_crtc_update(काष्ठा पूर्णांकel_bw_state *bw_state,
			  स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *i915 = to_i915(crtc->base.dev);

	bw_state->data_rate[crtc->pipe] =
		पूर्णांकel_bw_crtc_data_rate(crtc_state);
	bw_state->num_active_planes[crtc->pipe] =
		पूर्णांकel_bw_crtc_num_active_planes(crtc_state);

	drm_dbg_kms(&i915->drm, "pipe %c data rate %u num active planes %u\n",
		    pipe_name(crtc->pipe),
		    bw_state->data_rate[crtc->pipe],
		    bw_state->num_active_planes[crtc->pipe]);
पूर्ण

अटल अचिन्हित पूर्णांक पूर्णांकel_bw_num_active_planes(काष्ठा drm_i915_निजी *dev_priv,
					       स्थिर काष्ठा पूर्णांकel_bw_state *bw_state)
अणु
	अचिन्हित पूर्णांक num_active_planes = 0;
	क्रमागत pipe pipe;

	क्रम_each_pipe(dev_priv, pipe)
		num_active_planes += bw_state->num_active_planes[pipe];

	वापस num_active_planes;
पूर्ण

अटल अचिन्हित पूर्णांक पूर्णांकel_bw_data_rate(काष्ठा drm_i915_निजी *dev_priv,
				       स्थिर काष्ठा पूर्णांकel_bw_state *bw_state)
अणु
	अचिन्हित पूर्णांक data_rate = 0;
	क्रमागत pipe pipe;

	क्रम_each_pipe(dev_priv, pipe)
		data_rate += bw_state->data_rate[pipe];

	वापस data_rate;
पूर्ण

काष्ठा पूर्णांकel_bw_state *
पूर्णांकel_atomic_get_old_bw_state(काष्ठा पूर्णांकel_atomic_state *state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(state->base.dev);
	काष्ठा पूर्णांकel_global_state *bw_state;

	bw_state = पूर्णांकel_atomic_get_old_global_obj_state(state, &dev_priv->bw_obj);

	वापस to_पूर्णांकel_bw_state(bw_state);
पूर्ण

काष्ठा पूर्णांकel_bw_state *
पूर्णांकel_atomic_get_new_bw_state(काष्ठा पूर्णांकel_atomic_state *state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(state->base.dev);
	काष्ठा पूर्णांकel_global_state *bw_state;

	bw_state = पूर्णांकel_atomic_get_new_global_obj_state(state, &dev_priv->bw_obj);

	वापस to_पूर्णांकel_bw_state(bw_state);
पूर्ण

काष्ठा पूर्णांकel_bw_state *
पूर्णांकel_atomic_get_bw_state(काष्ठा पूर्णांकel_atomic_state *state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(state->base.dev);
	काष्ठा पूर्णांकel_global_state *bw_state;

	bw_state = पूर्णांकel_atomic_get_global_obj_state(state, &dev_priv->bw_obj);
	अगर (IS_ERR(bw_state))
		वापस ERR_CAST(bw_state);

	वापस to_पूर्णांकel_bw_state(bw_state);
पूर्ण

पूर्णांक skl_bw_calc_min_cdclk(काष्ठा पूर्णांकel_atomic_state *state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(state->base.dev);
	काष्ठा पूर्णांकel_bw_state *new_bw_state = शून्य;
	काष्ठा पूर्णांकel_bw_state *old_bw_state = शून्य;
	स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state;
	काष्ठा पूर्णांकel_crtc *crtc;
	पूर्णांक max_bw = 0;
	पूर्णांक slice_id;
	क्रमागत pipe pipe;
	पूर्णांक i;

	क्रम_each_new_पूर्णांकel_crtc_in_state(state, crtc, crtc_state, i) अणु
		क्रमागत plane_id plane_id;
		काष्ठा पूर्णांकel_dbuf_bw *crtc_bw;

		new_bw_state = पूर्णांकel_atomic_get_bw_state(state);
		अगर (IS_ERR(new_bw_state))
			वापस PTR_ERR(new_bw_state);

		old_bw_state = पूर्णांकel_atomic_get_old_bw_state(state);

		crtc_bw = &new_bw_state->dbuf_bw[crtc->pipe];

		स_रखो(&crtc_bw->used_bw, 0, माप(crtc_bw->used_bw));

		अगर (!crtc_state->hw.active)
			जारी;

		क्रम_each_plane_id_on_crtc(crtc, plane_id) अणु
			स्थिर काष्ठा skl_ddb_entry *plane_alloc =
				&crtc_state->wm.skl.plane_ddb_y[plane_id];
			स्थिर काष्ठा skl_ddb_entry *uv_plane_alloc =
				&crtc_state->wm.skl.plane_ddb_uv[plane_id];
			अचिन्हित पूर्णांक data_rate = crtc_state->data_rate[plane_id];
			अचिन्हित पूर्णांक dbuf_mask = 0;

			dbuf_mask |= skl_ddb_dbuf_slice_mask(dev_priv, plane_alloc);
			dbuf_mask |= skl_ddb_dbuf_slice_mask(dev_priv, uv_plane_alloc);

			/*
			 * FIXME: To calculate that more properly we probably
			 * need to to split per plane data_rate पूर्णांकo data_rate_y
			 * and data_rate_uv क्रम multiplanar क्रमmats in order not
			 * to get accounted those twice अगर they happen to reside
			 * on dअगरferent slices.
			 * However क्रम pre-icl this would work anyway because
			 * we have only single slice and क्रम icl+ uv plane has
			 * non-zero data rate.
			 * So in worst हाल those calculation are a bit
			 * pessimistic, which shouldn't pose any signअगरicant
			 * problem anyway.
			 */
			क्रम_each_dbuf_slice_in_mask(slice_id, dbuf_mask)
				crtc_bw->used_bw[slice_id] += data_rate;
		पूर्ण
	पूर्ण

	अगर (!old_bw_state)
		वापस 0;

	क्रम_each_pipe(dev_priv, pipe) अणु
		काष्ठा पूर्णांकel_dbuf_bw *crtc_bw;

		crtc_bw = &new_bw_state->dbuf_bw[pipe];

		क्रम_each_dbuf_slice(slice_id) अणु
			/*
			 * Current experimental observations show that contrary
			 * to BSpec we get underruns once we exceed 64 * CDCLK
			 * क्रम slices in total.
			 * As a temporary measure in order not to keep CDCLK
			 * bumped up all the समय we calculate CDCLK according
			 * to this क्रमmula क्रम  overall bw consumed by slices.
			 */
			max_bw += crtc_bw->used_bw[slice_id];
		पूर्ण
	पूर्ण

	new_bw_state->min_cdclk = max_bw / 64;

	अगर (new_bw_state->min_cdclk != old_bw_state->min_cdclk) अणु
		पूर्णांक ret = पूर्णांकel_atomic_lock_global_state(&new_bw_state->base);

		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक पूर्णांकel_bw_calc_min_cdclk(काष्ठा पूर्णांकel_atomic_state *state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(state->base.dev);
	काष्ठा पूर्णांकel_bw_state *new_bw_state = शून्य;
	काष्ठा पूर्णांकel_bw_state *old_bw_state = शून्य;
	स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state;
	काष्ठा पूर्णांकel_crtc *crtc;
	पूर्णांक min_cdclk = 0;
	क्रमागत pipe pipe;
	पूर्णांक i;

	क्रम_each_new_पूर्णांकel_crtc_in_state(state, crtc, crtc_state, i) अणु
		new_bw_state = पूर्णांकel_atomic_get_bw_state(state);
		अगर (IS_ERR(new_bw_state))
			वापस PTR_ERR(new_bw_state);

		old_bw_state = पूर्णांकel_atomic_get_old_bw_state(state);
	पूर्ण

	अगर (!old_bw_state)
		वापस 0;

	क्रम_each_pipe(dev_priv, pipe) अणु
		काष्ठा पूर्णांकel_cdclk_state *cdclk_state;

		cdclk_state = पूर्णांकel_atomic_get_new_cdclk_state(state);
		अगर (!cdclk_state)
			वापस 0;

		min_cdclk = max(cdclk_state->min_cdclk[pipe], min_cdclk);
	पूर्ण

	new_bw_state->min_cdclk = min_cdclk;

	अगर (new_bw_state->min_cdclk != old_bw_state->min_cdclk) अणु
		पूर्णांक ret = पूर्णांकel_atomic_lock_global_state(&new_bw_state->base);

		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक पूर्णांकel_bw_atomic_check(काष्ठा पूर्णांकel_atomic_state *state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(state->base.dev);
	काष्ठा पूर्णांकel_crtc_state *new_crtc_state, *old_crtc_state;
	काष्ठा पूर्णांकel_bw_state *new_bw_state = शून्य;
	स्थिर काष्ठा पूर्णांकel_bw_state *old_bw_state = शून्य;
	अचिन्हित पूर्णांक data_rate;
	अचिन्हित पूर्णांक num_active_planes;
	काष्ठा पूर्णांकel_crtc *crtc;
	पूर्णांक i, ret;
	u32 allowed_poपूर्णांकs = 0;
	अचिन्हित पूर्णांक max_bw_poपूर्णांक = 0, max_bw = 0;
	अचिन्हित पूर्णांक num_qgv_poपूर्णांकs = dev_priv->max_bw[0].num_qgv_poपूर्णांकs;
	u32 mask = (1 << num_qgv_poपूर्णांकs) - 1;

	/* FIXME earlier gens need some checks too */
	अगर (DISPLAY_VER(dev_priv) < 11)
		वापस 0;

	क्रम_each_oldnew_पूर्णांकel_crtc_in_state(state, crtc, old_crtc_state,
					    new_crtc_state, i) अणु
		अचिन्हित पूर्णांक old_data_rate =
			पूर्णांकel_bw_crtc_data_rate(old_crtc_state);
		अचिन्हित पूर्णांक new_data_rate =
			पूर्णांकel_bw_crtc_data_rate(new_crtc_state);
		अचिन्हित पूर्णांक old_active_planes =
			पूर्णांकel_bw_crtc_num_active_planes(old_crtc_state);
		अचिन्हित पूर्णांक new_active_planes =
			पूर्णांकel_bw_crtc_num_active_planes(new_crtc_state);

		/*
		 * Aव्योम locking the bw state when
		 * nothing signअगरicant has changed.
		 */
		अगर (old_data_rate == new_data_rate &&
		    old_active_planes == new_active_planes)
			जारी;

		new_bw_state = पूर्णांकel_atomic_get_bw_state(state);
		अगर (IS_ERR(new_bw_state))
			वापस PTR_ERR(new_bw_state);

		new_bw_state->data_rate[crtc->pipe] = new_data_rate;
		new_bw_state->num_active_planes[crtc->pipe] = new_active_planes;

		drm_dbg_kms(&dev_priv->drm,
			    "pipe %c data rate %u num active planes %u\n",
			    pipe_name(crtc->pipe),
			    new_bw_state->data_rate[crtc->pipe],
			    new_bw_state->num_active_planes[crtc->pipe]);
	पूर्ण

	अगर (!new_bw_state)
		वापस 0;

	ret = पूर्णांकel_atomic_lock_global_state(&new_bw_state->base);
	अगर (ret)
		वापस ret;

	data_rate = पूर्णांकel_bw_data_rate(dev_priv, new_bw_state);
	data_rate = DIV_ROUND_UP(data_rate, 1000);

	num_active_planes = पूर्णांकel_bw_num_active_planes(dev_priv, new_bw_state);

	क्रम (i = 0; i < num_qgv_poपूर्णांकs; i++) अणु
		अचिन्हित पूर्णांक max_data_rate;

		max_data_rate = icl_max_bw(dev_priv, num_active_planes, i);
		/*
		 * We need to know which qgv poपूर्णांक gives us
		 * maximum bandwidth in order to disable SAGV
		 * अगर we find that we exceed SAGV block समय
		 * with watermarks. By that moment we alपढ़ोy
		 * have those, as it is calculated earlier in
		 * पूर्णांकel_atomic_check,
		 */
		अगर (max_data_rate > max_bw) अणु
			max_bw_poपूर्णांक = i;
			max_bw = max_data_rate;
		पूर्ण
		अगर (max_data_rate >= data_rate)
			allowed_poपूर्णांकs |= BIT(i);
		drm_dbg_kms(&dev_priv->drm, "QGV point %d: max bw %d required %d\n",
			    i, max_data_rate, data_rate);
	पूर्ण

	/*
	 * BSpec states that we always should have at least one allowed poपूर्णांक
	 * left, so अगर we couldn't - simply reject the configuration क्रम obvious
	 * reasons.
	 */
	अगर (allowed_poपूर्णांकs == 0) अणु
		drm_dbg_kms(&dev_priv->drm, "No QGV points provide sufficient memory"
			    " bandwidth %d for display configuration(%d active planes).\n",
			    data_rate, num_active_planes);
		वापस -EINVAL;
	पूर्ण

	/*
	 * Leave only single poपूर्णांक with highest bandwidth, अगर
	 * we can't enable SAGV due to the increased memory latency it may
	 * cause.
	 */
	अगर (!पूर्णांकel_can_enable_sagv(dev_priv, new_bw_state)) अणु
		allowed_poपूर्णांकs = BIT(max_bw_poपूर्णांक);
		drm_dbg_kms(&dev_priv->drm, "No SAGV, using single QGV point %d\n",
			    max_bw_poपूर्णांक);
	पूर्ण
	/*
	 * We store the ones which need to be masked as that is what PCode
	 * actually accepts as a parameter.
	 */
	new_bw_state->qgv_poपूर्णांकs_mask = ~allowed_poपूर्णांकs & mask;

	old_bw_state = पूर्णांकel_atomic_get_old_bw_state(state);
	/*
	 * If the actual mask had changed we need to make sure that
	 * the commits are serialized(in हाल this is a nomodeset, nonblocking)
	 */
	अगर (new_bw_state->qgv_poपूर्णांकs_mask != old_bw_state->qgv_poपूर्णांकs_mask) अणु
		ret = पूर्णांकel_atomic_serialize_global_state(&new_bw_state->base);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा पूर्णांकel_global_state *
पूर्णांकel_bw_duplicate_state(काष्ठा पूर्णांकel_global_obj *obj)
अणु
	काष्ठा पूर्णांकel_bw_state *state;

	state = kmemdup(obj->state, माप(*state), GFP_KERNEL);
	अगर (!state)
		वापस शून्य;

	वापस &state->base;
पूर्ण

अटल व्योम पूर्णांकel_bw_destroy_state(काष्ठा पूर्णांकel_global_obj *obj,
				   काष्ठा पूर्णांकel_global_state *state)
अणु
	kमुक्त(state);
पूर्ण

अटल स्थिर काष्ठा पूर्णांकel_global_state_funcs पूर्णांकel_bw_funcs = अणु
	.atomic_duplicate_state = पूर्णांकel_bw_duplicate_state,
	.atomic_destroy_state = पूर्णांकel_bw_destroy_state,
पूर्ण;

पूर्णांक पूर्णांकel_bw_init(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_bw_state *state;

	state = kzalloc(माप(*state), GFP_KERNEL);
	अगर (!state)
		वापस -ENOMEM;

	पूर्णांकel_atomic_global_obj_init(dev_priv, &dev_priv->bw_obj,
				     &state->base, &पूर्णांकel_bw_funcs);

	वापस 0;
पूर्ण
