<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2014-2018 The Linux Foundation. All rights reserved.
 * Copyright (C) 2013 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 */

#घोषणा pr_fmt(fmt)	"[drm:%s:%d] " fmt, __func__, __LINE__

#समावेश <linux/debugfs.h>
#समावेश <linux/dma-buf.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_uapi.h>
#समावेश <drm/drm_damage_helper.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_gem_atomic_helper.h>

#समावेश "msm_drv.h"
#समावेश "dpu_kms.h"
#समावेश "dpu_formats.h"
#समावेश "dpu_hw_sspp.h"
#समावेश "dpu_trace.h"
#समावेश "dpu_crtc.h"
#समावेश "dpu_vbif.h"
#समावेश "dpu_plane.h"

#घोषणा DPU_DEBUG_PLANE(pl, fmt, ...) DPU_DEBUG("plane%d " fmt,\
		(pl) ? (pl)->base.base.id : -1, ##__VA_ARGS__)

#घोषणा DPU_ERROR_PLANE(pl, fmt, ...) DPU_ERROR("plane%d " fmt,\
		(pl) ? (pl)->base.base.id : -1, ##__VA_ARGS__)

#घोषणा DECIMATED_DIMENSION(dim, deci) (((dim) + ((1 << (deci)) - 1)) >> (deci))
#घोषणा PHASE_STEP_SHIFT	21
#घोषणा PHASE_STEP_UNIT_SCALE   ((पूर्णांक) (1 << PHASE_STEP_SHIFT))
#घोषणा PHASE_RESIDUAL		15

#घोषणा SHARP_STRENGTH_DEFAULT	32
#घोषणा SHARP_EDGE_THR_DEFAULT	112
#घोषणा SHARP_SMOOTH_THR_DEFAULT	8
#घोषणा SHARP_NOISE_THR_DEFAULT	2

#घोषणा DPU_NAME_SIZE  12

#घोषणा DPU_PLANE_COLOR_FILL_FLAG	BIT(31)
#घोषणा DPU_ZPOS_MAX 255

/* multirect rect index */
क्रमागत अणु
	R0,
	R1,
	R_MAX
पूर्ण;

/*
 * Default Preload Values
 */
#घोषणा DPU_QSEED3_DEFAULT_PRELOAD_H 0x4
#घोषणा DPU_QSEED3_DEFAULT_PRELOAD_V 0x3
#घोषणा DPU_QSEED4_DEFAULT_PRELOAD_V 0x2
#घोषणा DPU_QSEED4_DEFAULT_PRELOAD_H 0x4

#घोषणा DEFAULT_REFRESH_RATE	60

अटल स्थिर uपूर्णांक32_t qcom_compressed_supported_क्रमmats[] = अणु
	DRM_FORMAT_ABGR8888,
	DRM_FORMAT_ARGB8888,
	DRM_FORMAT_XBGR8888,
	DRM_FORMAT_XRGB8888,
	DRM_FORMAT_BGR565,

	DRM_FORMAT_NV12,
पूर्ण;

/**
 * क्रमागत dpu_plane_qos - Dअगरferent qos configurations क्रम each pipe
 *
 * @DPU_PLANE_QOS_VBLANK_CTRL: Setup VBLANK qos क्रम the pipe.
 * @DPU_PLANE_QOS_VBLANK_AMORTIZE: Enables Amortization within pipe.
 *	this configuration is mutually exclusive from VBLANK_CTRL.
 * @DPU_PLANE_QOS_PANIC_CTRL: Setup panic क्रम the pipe.
 */
क्रमागत dpu_plane_qos अणु
	DPU_PLANE_QOS_VBLANK_CTRL = BIT(0),
	DPU_PLANE_QOS_VBLANK_AMORTIZE = BIT(1),
	DPU_PLANE_QOS_PANIC_CTRL = BIT(2),
पूर्ण;

/*
 * काष्ठा dpu_plane - local dpu plane काष्ठाure
 * @aspace: address space poपूर्णांकer
 * @csc_ptr: Poपूर्णांकs to dpu_csc_cfg काष्ठाure to use क्रम current
 * @mplane_list: List of multirect planes of the same pipe
 * @catalog: Poपूर्णांकs to dpu catalog काष्ठाure
 * @revalidate: क्रमce revalidation of all the plane properties
 */
काष्ठा dpu_plane अणु
	काष्ठा drm_plane base;

	काष्ठा mutex lock;

	क्रमागत dpu_sspp pipe;
	uपूर्णांक32_t features;      /* capabilities from catalog */

	काष्ठा dpu_hw_pipe *pipe_hw;
	काष्ठा dpu_hw_pipe_cfg pipe_cfg;
	काष्ठा dpu_hw_pipe_qos_cfg pipe_qos_cfg;
	uपूर्णांक32_t color_fill;
	bool is_error;
	bool is_rt_pipe;
	bool is_भव;
	काष्ठा list_head mplane_list;
	काष्ठा dpu_mdss_cfg *catalog;

	काष्ठा dpu_csc_cfg *csc_ptr;

	स्थिर काष्ठा dpu_sspp_sub_blks *pipe_sblk;
	अक्षर pipe_name[DPU_NAME_SIZE];

	/* debugfs related stuff */
	काष्ठा dentry *debugfs_root;
	काष्ठा dpu_debugfs_regset32 debugfs_src;
	काष्ठा dpu_debugfs_regset32 debugfs_scaler;
	काष्ठा dpu_debugfs_regset32 debugfs_csc;
	bool debugfs_शेष_scale;
पूर्ण;

अटल स्थिर uपूर्णांक64_t supported_क्रमmat_modअगरiers[] = अणु
	DRM_FORMAT_MOD_QCOM_COMPRESSED,
	DRM_FORMAT_MOD_LINEAR,
	DRM_FORMAT_MOD_INVALID
पूर्ण;

#घोषणा to_dpu_plane(x) container_of(x, काष्ठा dpu_plane, base)

अटल काष्ठा dpu_kms *_dpu_plane_get_kms(काष्ठा drm_plane *plane)
अणु
	काष्ठा msm_drm_निजी *priv = plane->dev->dev_निजी;

	वापस to_dpu_kms(priv->kms);
पूर्ण

/**
 * _dpu_plane_calc_bw - calculate bandwidth required क्रम a plane
 * @plane: Poपूर्णांकer to drm plane.
 * @fb:   Poपूर्णांकer to framebuffer associated with the given plane
 * Result: Updates calculated bandwidth in the plane state.
 * BW Equation: src_w * src_h * bpp * fps * (v_total / v_dest)
 * Prefill BW Equation: line src bytes * line_समय
 */
अटल व्योम _dpu_plane_calc_bw(काष्ठा drm_plane *plane,
	काष्ठा drm_framebuffer *fb)
अणु
	काष्ठा dpu_plane *pdpu = to_dpu_plane(plane);
	काष्ठा dpu_plane_state *pstate;
	काष्ठा drm_display_mode *mode;
	स्थिर काष्ठा dpu_क्रमmat *fmt = शून्य;
	काष्ठा dpu_kms *dpu_kms = _dpu_plane_get_kms(plane);
	पूर्णांक src_width, src_height, dst_height, fps;
	u64 plane_prefill_bw;
	u64 plane_bw;
	u32 hw_latency_lines;
	u64 scale_factor;
	पूर्णांक vbp, vpw, vfp;

	pstate = to_dpu_plane_state(plane->state);
	mode = &plane->state->crtc->mode;

	fmt = dpu_get_dpu_क्रमmat_ext(fb->क्रमmat->क्रमmat, fb->modअगरier);

	src_width = drm_rect_width(&pdpu->pipe_cfg.src_rect);
	src_height = drm_rect_height(&pdpu->pipe_cfg.src_rect);
	dst_height = drm_rect_height(&pdpu->pipe_cfg.dst_rect);
	fps = drm_mode_vrefresh(mode);
	vbp = mode->vtotal - mode->vsync_end;
	vpw = mode->vsync_end - mode->vsync_start;
	vfp = mode->vsync_start - mode->vdisplay;
	hw_latency_lines =  dpu_kms->catalog->perf.min_prefill_lines;
	scale_factor = src_height > dst_height ?
		mult_frac(src_height, 1, dst_height) : 1;

	plane_bw =
		src_width * mode->vtotal * fps * fmt->bpp *
		scale_factor;

	plane_prefill_bw =
		src_width * hw_latency_lines * fps * fmt->bpp *
		scale_factor * mode->vtotal;

	अगर ((vbp+vpw) > hw_latency_lines)
		करो_भाग(plane_prefill_bw, (vbp+vpw));
	अन्यथा अगर ((vbp+vpw+vfp) < hw_latency_lines)
		करो_भाग(plane_prefill_bw, (vbp+vpw+vfp));
	अन्यथा
		करो_भाग(plane_prefill_bw, hw_latency_lines);


	pstate->plane_fetch_bw = max(plane_bw, plane_prefill_bw);
पूर्ण

/**
 * _dpu_plane_calc_clk - calculate घड़ी required क्रम a plane
 * @plane: Poपूर्णांकer to drm plane.
 * Result: Updates calculated घड़ी in the plane state.
 * Clock equation: dst_w * v_total * fps * (src_h / dst_h)
 */
अटल व्योम _dpu_plane_calc_clk(काष्ठा drm_plane *plane)
अणु
	काष्ठा dpu_plane *pdpu = to_dpu_plane(plane);
	काष्ठा dpu_plane_state *pstate;
	काष्ठा drm_display_mode *mode;
	पूर्णांक dst_width, src_height, dst_height, fps;

	pstate = to_dpu_plane_state(plane->state);
	mode = &plane->state->crtc->mode;

	src_height = drm_rect_height(&pdpu->pipe_cfg.src_rect);
	dst_width = drm_rect_width(&pdpu->pipe_cfg.dst_rect);
	dst_height = drm_rect_height(&pdpu->pipe_cfg.dst_rect);
	fps = drm_mode_vrefresh(mode);

	pstate->plane_clk =
		dst_width * mode->vtotal * fps;

	अगर (src_height > dst_height) अणु
		pstate->plane_clk *= src_height;
		करो_भाग(pstate->plane_clk, dst_height);
	पूर्ण
पूर्ण

/**
 * _dpu_plane_calc_fill_level - calculate fill level of the given source क्रमmat
 * @plane:		Poपूर्णांकer to drm plane
 * @fmt:		Poपूर्णांकer to source buffer क्रमmat
 * @src_width:		width of source buffer
 * Return: fill level corresponding to the source buffer/क्रमmat or 0 अगर error
 */
अटल पूर्णांक _dpu_plane_calc_fill_level(काष्ठा drm_plane *plane,
		स्थिर काष्ठा dpu_क्रमmat *fmt, u32 src_width)
अणु
	काष्ठा dpu_plane *pdpu, *पंचांगp;
	काष्ठा dpu_plane_state *pstate;
	u32 fixed_buff_size;
	u32 total_fl;

	अगर (!fmt || !plane->state || !src_width || !fmt->bpp) अणु
		DPU_ERROR("invalid arguments\n");
		वापस 0;
	पूर्ण

	pdpu = to_dpu_plane(plane);
	pstate = to_dpu_plane_state(plane->state);
	fixed_buff_size = pdpu->catalog->caps->pixel_ram_size;

	list_क्रम_each_entry(पंचांगp, &pdpu->mplane_list, mplane_list) अणु
		अगर (!पंचांगp->base.state->visible)
			जारी;
		DPU_DEBUG("plane%d/%d src_width:%d/%d\n",
				pdpu->base.base.id, पंचांगp->base.base.id,
				src_width,
				drm_rect_width(&पंचांगp->pipe_cfg.src_rect));
		src_width = max_t(u32, src_width,
				  drm_rect_width(&पंचांगp->pipe_cfg.src_rect));
	पूर्ण

	अगर (fmt->fetch_planes == DPU_PLANE_PSEUDO_PLANAR) अणु
		अगर (fmt->chroma_sample == DPU_CHROMA_420) अणु
			/* NV12 */
			total_fl = (fixed_buff_size / 2) /
				((src_width + 32) * fmt->bpp);
		पूर्ण अन्यथा अणु
			/* non NV12 */
			total_fl = (fixed_buff_size / 2) * 2 /
				((src_width + 32) * fmt->bpp);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (pstate->multirect_mode == DPU_SSPP_MULTIRECT_PARALLEL) अणु
			total_fl = (fixed_buff_size / 2) * 2 /
				((src_width + 32) * fmt->bpp);
		पूर्ण अन्यथा अणु
			total_fl = (fixed_buff_size) * 2 /
				((src_width + 32) * fmt->bpp);
		पूर्ण
	पूर्ण

	DPU_DEBUG("plane%u: pnum:%d fmt: %4.4s w:%u fl:%u\n",
			plane->base.id, pdpu->pipe - SSPP_VIG0,
			(अक्षर *)&fmt->base.pixel_क्रमmat,
			src_width, total_fl);

	वापस total_fl;
पूर्ण

/**
 * _dpu_plane_get_qos_lut - get LUT mapping based on fill level
 * @tbl:		Poपूर्णांकer to LUT table
 * @total_fl:		fill level
 * Return: LUT setting corresponding to the fill level
 */
अटल u64 _dpu_plane_get_qos_lut(स्थिर काष्ठा dpu_qos_lut_tbl *tbl,
		u32 total_fl)
अणु
	पूर्णांक i;

	अगर (!tbl || !tbl->nentry || !tbl->entries)
		वापस 0;

	क्रम (i = 0; i < tbl->nentry; i++)
		अगर (total_fl <= tbl->entries[i].fl)
			वापस tbl->entries[i].lut;

	/* अगर last fl is zero, use as शेष */
	अगर (!tbl->entries[i-1].fl)
		वापस tbl->entries[i-1].lut;

	वापस 0;
पूर्ण

/**
 * _dpu_plane_set_qos_lut - set QoS LUT of the given plane
 * @plane:		Poपूर्णांकer to drm plane
 * @fb:			Poपूर्णांकer to framebuffer associated with the given plane
 */
अटल व्योम _dpu_plane_set_qos_lut(काष्ठा drm_plane *plane,
		काष्ठा drm_framebuffer *fb)
अणु
	काष्ठा dpu_plane *pdpu = to_dpu_plane(plane);
	स्थिर काष्ठा dpu_क्रमmat *fmt = शून्य;
	u64 qos_lut;
	u32 total_fl = 0, lut_usage;

	अगर (!pdpu->is_rt_pipe) अणु
		lut_usage = DPU_QOS_LUT_USAGE_NRT;
	पूर्ण अन्यथा अणु
		fmt = dpu_get_dpu_क्रमmat_ext(
				fb->क्रमmat->क्रमmat,
				fb->modअगरier);
		total_fl = _dpu_plane_calc_fill_level(plane, fmt,
				drm_rect_width(&pdpu->pipe_cfg.src_rect));

		अगर (fmt && DPU_FORMAT_IS_LINEAR(fmt))
			lut_usage = DPU_QOS_LUT_USAGE_LINEAR;
		अन्यथा
			lut_usage = DPU_QOS_LUT_USAGE_MACROTILE;
	पूर्ण

	qos_lut = _dpu_plane_get_qos_lut(
			&pdpu->catalog->perf.qos_lut_tbl[lut_usage], total_fl);

	pdpu->pipe_qos_cfg.creq_lut = qos_lut;

	trace_dpu_perf_set_qos_luts(pdpu->pipe - SSPP_VIG0,
			(fmt) ? fmt->base.pixel_क्रमmat : 0,
			pdpu->is_rt_pipe, total_fl, qos_lut, lut_usage);

	DPU_DEBUG("plane%u: pnum:%d fmt: %4.4s rt:%d fl:%u lut:0x%llx\n",
			plane->base.id,
			pdpu->pipe - SSPP_VIG0,
			fmt ? (अक्षर *)&fmt->base.pixel_क्रमmat : शून्य,
			pdpu->is_rt_pipe, total_fl, qos_lut);

	pdpu->pipe_hw->ops.setup_creq_lut(pdpu->pipe_hw, &pdpu->pipe_qos_cfg);
पूर्ण

/**
 * _dpu_plane_set_panic_lut - set danger/safe LUT of the given plane
 * @plane:		Poपूर्णांकer to drm plane
 * @fb:			Poपूर्णांकer to framebuffer associated with the given plane
 */
अटल व्योम _dpu_plane_set_danger_lut(काष्ठा drm_plane *plane,
		काष्ठा drm_framebuffer *fb)
अणु
	काष्ठा dpu_plane *pdpu = to_dpu_plane(plane);
	स्थिर काष्ठा dpu_क्रमmat *fmt = शून्य;
	u32 danger_lut, safe_lut;

	अगर (!pdpu->is_rt_pipe) अणु
		danger_lut = pdpu->catalog->perf.danger_lut_tbl
				[DPU_QOS_LUT_USAGE_NRT];
		safe_lut = pdpu->catalog->perf.safe_lut_tbl
				[DPU_QOS_LUT_USAGE_NRT];
	पूर्ण अन्यथा अणु
		fmt = dpu_get_dpu_क्रमmat_ext(
				fb->क्रमmat->क्रमmat,
				fb->modअगरier);

		अगर (fmt && DPU_FORMAT_IS_LINEAR(fmt)) अणु
			danger_lut = pdpu->catalog->perf.danger_lut_tbl
					[DPU_QOS_LUT_USAGE_LINEAR];
			safe_lut = pdpu->catalog->perf.safe_lut_tbl
					[DPU_QOS_LUT_USAGE_LINEAR];
		पूर्ण अन्यथा अणु
			danger_lut = pdpu->catalog->perf.danger_lut_tbl
					[DPU_QOS_LUT_USAGE_MACROTILE];
			safe_lut = pdpu->catalog->perf.safe_lut_tbl
					[DPU_QOS_LUT_USAGE_MACROTILE];
		पूर्ण
	पूर्ण

	pdpu->pipe_qos_cfg.danger_lut = danger_lut;
	pdpu->pipe_qos_cfg.safe_lut = safe_lut;

	trace_dpu_perf_set_danger_luts(pdpu->pipe - SSPP_VIG0,
			(fmt) ? fmt->base.pixel_क्रमmat : 0,
			(fmt) ? fmt->fetch_mode : 0,
			pdpu->pipe_qos_cfg.danger_lut,
			pdpu->pipe_qos_cfg.safe_lut);

	DPU_DEBUG("plane%u: pnum:%d fmt: %4.4s mode:%d luts[0x%x, 0x%x]\n",
		plane->base.id,
		pdpu->pipe - SSPP_VIG0,
		fmt ? (अक्षर *)&fmt->base.pixel_क्रमmat : शून्य,
		fmt ? fmt->fetch_mode : -1,
		pdpu->pipe_qos_cfg.danger_lut,
		pdpu->pipe_qos_cfg.safe_lut);

	pdpu->pipe_hw->ops.setup_danger_safe_lut(pdpu->pipe_hw,
			&pdpu->pipe_qos_cfg);
पूर्ण

/**
 * _dpu_plane_set_qos_ctrl - set QoS control of the given plane
 * @plane:		Poपूर्णांकer to drm plane
 * @enable:		true to enable QoS control
 * @flags:		QoS control mode (क्रमागत dpu_plane_qos)
 */
अटल व्योम _dpu_plane_set_qos_ctrl(काष्ठा drm_plane *plane,
	bool enable, u32 flags)
अणु
	काष्ठा dpu_plane *pdpu = to_dpu_plane(plane);

	अगर (flags & DPU_PLANE_QOS_VBLANK_CTRL) अणु
		pdpu->pipe_qos_cfg.creq_vblank = pdpu->pipe_sblk->creq_vblank;
		pdpu->pipe_qos_cfg.danger_vblank =
				pdpu->pipe_sblk->danger_vblank;
		pdpu->pipe_qos_cfg.vblank_en = enable;
	पूर्ण

	अगर (flags & DPU_PLANE_QOS_VBLANK_AMORTIZE) अणु
		/* this feature overrules previous VBLANK_CTRL */
		pdpu->pipe_qos_cfg.vblank_en = false;
		pdpu->pipe_qos_cfg.creq_vblank = 0; /* clear vblank bits */
	पूर्ण

	अगर (flags & DPU_PLANE_QOS_PANIC_CTRL)
		pdpu->pipe_qos_cfg.danger_safe_en = enable;

	अगर (!pdpu->is_rt_pipe) अणु
		pdpu->pipe_qos_cfg.vblank_en = false;
		pdpu->pipe_qos_cfg.danger_safe_en = false;
	पूर्ण

	DPU_DEBUG("plane%u: pnum:%d ds:%d vb:%d pri[0x%x, 0x%x] is_rt:%d\n",
		plane->base.id,
		pdpu->pipe - SSPP_VIG0,
		pdpu->pipe_qos_cfg.danger_safe_en,
		pdpu->pipe_qos_cfg.vblank_en,
		pdpu->pipe_qos_cfg.creq_vblank,
		pdpu->pipe_qos_cfg.danger_vblank,
		pdpu->is_rt_pipe);

	pdpu->pipe_hw->ops.setup_qos_ctrl(pdpu->pipe_hw,
			&pdpu->pipe_qos_cfg);
पूर्ण

/**
 * _dpu_plane_set_ot_limit - set OT limit क्रम the given plane
 * @plane:		Poपूर्णांकer to drm plane
 * @crtc:		Poपूर्णांकer to drm crtc
 */
अटल व्योम _dpu_plane_set_ot_limit(काष्ठा drm_plane *plane,
		काष्ठा drm_crtc *crtc)
अणु
	काष्ठा dpu_plane *pdpu = to_dpu_plane(plane);
	काष्ठा dpu_vbअगर_set_ot_params ot_params;
	काष्ठा dpu_kms *dpu_kms = _dpu_plane_get_kms(plane);

	स_रखो(&ot_params, 0, माप(ot_params));
	ot_params.xin_id = pdpu->pipe_hw->cap->xin_id;
	ot_params.num = pdpu->pipe_hw->idx - SSPP_NONE;
	ot_params.width = drm_rect_width(&pdpu->pipe_cfg.src_rect);
	ot_params.height = drm_rect_height(&pdpu->pipe_cfg.src_rect);
	ot_params.is_wfd = !pdpu->is_rt_pipe;
	ot_params.frame_rate = drm_mode_vrefresh(&crtc->mode);
	ot_params.vbअगर_idx = VBIF_RT;
	ot_params.clk_ctrl = pdpu->pipe_hw->cap->clk_ctrl;
	ot_params.rd = true;

	dpu_vbअगर_set_ot_limit(dpu_kms, &ot_params);
पूर्ण

/**
 * _dpu_plane_set_vbअगर_qos - set vbअगर QoS क्रम the given plane
 * @plane:		Poपूर्णांकer to drm plane
 */
अटल व्योम _dpu_plane_set_qos_remap(काष्ठा drm_plane *plane)
अणु
	काष्ठा dpu_plane *pdpu = to_dpu_plane(plane);
	काष्ठा dpu_vbअगर_set_qos_params qos_params;
	काष्ठा dpu_kms *dpu_kms = _dpu_plane_get_kms(plane);

	स_रखो(&qos_params, 0, माप(qos_params));
	qos_params.vbअगर_idx = VBIF_RT;
	qos_params.clk_ctrl = pdpu->pipe_hw->cap->clk_ctrl;
	qos_params.xin_id = pdpu->pipe_hw->cap->xin_id;
	qos_params.num = pdpu->pipe_hw->idx - SSPP_VIG0;
	qos_params.is_rt = pdpu->is_rt_pipe;

	DPU_DEBUG("plane%d pipe:%d vbif:%d xin:%d rt:%d, clk_ctrl:%d\n",
			plane->base.id, qos_params.num,
			qos_params.vbअगर_idx,
			qos_params.xin_id, qos_params.is_rt,
			qos_params.clk_ctrl);

	dpu_vbअगर_set_qos_remap(dpu_kms, &qos_params);
पूर्ण

अटल व्योम _dpu_plane_set_scanout(काष्ठा drm_plane *plane,
		काष्ठा dpu_plane_state *pstate,
		काष्ठा dpu_hw_pipe_cfg *pipe_cfg,
		काष्ठा drm_framebuffer *fb)
अणु
	काष्ठा dpu_plane *pdpu = to_dpu_plane(plane);
	काष्ठा dpu_kms *kms = _dpu_plane_get_kms(&pdpu->base);
	काष्ठा msm_gem_address_space *aspace = kms->base.aspace;
	पूर्णांक ret;

	ret = dpu_क्रमmat_populate_layout(aspace, fb, &pipe_cfg->layout);
	अगर (ret == -EAGAIN)
		DPU_DEBUG_PLANE(pdpu, "not updating same src addrs\n");
	अन्यथा अगर (ret)
		DPU_ERROR_PLANE(pdpu, "failed to get format layout, %d\n", ret);
	अन्यथा अगर (pdpu->pipe_hw->ops.setup_sourceaddress) अणु
		trace_dpu_plane_set_scanout(pdpu->pipe_hw->idx,
					    &pipe_cfg->layout,
					    pstate->multirect_index);
		pdpu->pipe_hw->ops.setup_sourceaddress(pdpu->pipe_hw, pipe_cfg,
						pstate->multirect_index);
	पूर्ण
पूर्ण

अटल व्योम _dpu_plane_setup_scaler3(काष्ठा dpu_plane *pdpu,
		काष्ठा dpu_plane_state *pstate,
		uपूर्णांक32_t src_w, uपूर्णांक32_t src_h, uपूर्णांक32_t dst_w, uपूर्णांक32_t dst_h,
		काष्ठा dpu_hw_scaler3_cfg *scale_cfg,
		स्थिर काष्ठा dpu_क्रमmat *fmt,
		uपूर्णांक32_t chroma_subsmpl_h, uपूर्णांक32_t chroma_subsmpl_v)
अणु
	uपूर्णांक32_t i;

	स_रखो(scale_cfg, 0, माप(*scale_cfg));
	स_रखो(&pstate->pixel_ext, 0, माप(काष्ठा dpu_hw_pixel_ext));

	scale_cfg->phase_step_x[DPU_SSPP_COMP_0] =
		mult_frac((1 << PHASE_STEP_SHIFT), src_w, dst_w);
	scale_cfg->phase_step_y[DPU_SSPP_COMP_0] =
		mult_frac((1 << PHASE_STEP_SHIFT), src_h, dst_h);


	scale_cfg->phase_step_y[DPU_SSPP_COMP_1_2] =
		scale_cfg->phase_step_y[DPU_SSPP_COMP_0] / chroma_subsmpl_v;
	scale_cfg->phase_step_x[DPU_SSPP_COMP_1_2] =
		scale_cfg->phase_step_x[DPU_SSPP_COMP_0] / chroma_subsmpl_h;

	scale_cfg->phase_step_x[DPU_SSPP_COMP_2] =
		scale_cfg->phase_step_x[DPU_SSPP_COMP_1_2];
	scale_cfg->phase_step_y[DPU_SSPP_COMP_2] =
		scale_cfg->phase_step_y[DPU_SSPP_COMP_1_2];

	scale_cfg->phase_step_x[DPU_SSPP_COMP_3] =
		scale_cfg->phase_step_x[DPU_SSPP_COMP_0];
	scale_cfg->phase_step_y[DPU_SSPP_COMP_3] =
		scale_cfg->phase_step_y[DPU_SSPP_COMP_0];

	क्रम (i = 0; i < DPU_MAX_PLANES; i++) अणु
		scale_cfg->src_width[i] = src_w;
		scale_cfg->src_height[i] = src_h;
		अगर (i == DPU_SSPP_COMP_1_2 || i == DPU_SSPP_COMP_2) अणु
			scale_cfg->src_width[i] /= chroma_subsmpl_h;
			scale_cfg->src_height[i] /= chroma_subsmpl_v;
		पूर्ण

		अगर (pdpu->pipe_hw->cap->features &
			BIT(DPU_SSPP_SCALER_QSEED4)) अणु
			scale_cfg->preload_x[i] = DPU_QSEED4_DEFAULT_PRELOAD_H;
			scale_cfg->preload_y[i] = DPU_QSEED4_DEFAULT_PRELOAD_V;
		पूर्ण अन्यथा अणु
			scale_cfg->preload_x[i] = DPU_QSEED3_DEFAULT_PRELOAD_H;
			scale_cfg->preload_y[i] = DPU_QSEED3_DEFAULT_PRELOAD_V;
		पूर्ण

		pstate->pixel_ext.num_ext_pxls_top[i] =
			scale_cfg->src_height[i];
		pstate->pixel_ext.num_ext_pxls_left[i] =
			scale_cfg->src_width[i];
	पूर्ण
	अगर (!(DPU_FORMAT_IS_YUV(fmt)) && (src_h == dst_h)
		&& (src_w == dst_w))
		वापस;

	scale_cfg->dst_width = dst_w;
	scale_cfg->dst_height = dst_h;
	scale_cfg->y_rgb_filter_cfg = DPU_SCALE_BIL;
	scale_cfg->uv_filter_cfg = DPU_SCALE_BIL;
	scale_cfg->alpha_filter_cfg = DPU_SCALE_ALPHA_BIL;
	scale_cfg->lut_flag = 0;
	scale_cfg->blend_cfg = 1;
	scale_cfg->enable = 1;
पूर्ण

अटल व्योम _dpu_plane_setup_csc(काष्ठा dpu_plane *pdpu)
अणु
	अटल स्थिर काष्ठा dpu_csc_cfg dpu_csc_YUV2RGB_601L = अणु
		अणु
			/* S15.16 क्रमmat */
			0x00012A00, 0x00000000, 0x00019880,
			0x00012A00, 0xFFFF9B80, 0xFFFF3000,
			0x00012A00, 0x00020480, 0x00000000,
		पूर्ण,
		/* चिन्हित bias */
		अणु 0xfff0, 0xff80, 0xff80,पूर्ण,
		अणु 0x0, 0x0, 0x0,पूर्ण,
		/* अचिन्हित clamp */
		अणु 0x10, 0xeb, 0x10, 0xf0, 0x10, 0xf0,पूर्ण,
		अणु 0x00, 0xff, 0x00, 0xff, 0x00, 0xff,पूर्ण,
	पूर्ण;
	अटल स्थिर काष्ठा dpu_csc_cfg dpu_csc10_YUV2RGB_601L = अणु
		अणु
			/* S15.16 क्रमmat */
			0x00012A00, 0x00000000, 0x00019880,
			0x00012A00, 0xFFFF9B80, 0xFFFF3000,
			0x00012A00, 0x00020480, 0x00000000,
			पूर्ण,
		/* चिन्हित bias */
		अणु 0xffc0, 0xfe00, 0xfe00,पूर्ण,
		अणु 0x0, 0x0, 0x0,पूर्ण,
		/* अचिन्हित clamp */
		अणु 0x40, 0x3ac, 0x40, 0x3c0, 0x40, 0x3c0,पूर्ण,
		अणु 0x00, 0x3ff, 0x00, 0x3ff, 0x00, 0x3ff,पूर्ण,
	पूर्ण;

	अगर (!pdpu) अणु
		DPU_ERROR("invalid plane\n");
		वापस;
	पूर्ण

	अगर (BIT(DPU_SSPP_CSC_10BIT) & pdpu->features)
		pdpu->csc_ptr = (काष्ठा dpu_csc_cfg *)&dpu_csc10_YUV2RGB_601L;
	अन्यथा
		pdpu->csc_ptr = (काष्ठा dpu_csc_cfg *)&dpu_csc_YUV2RGB_601L;

	DPU_DEBUG_PLANE(pdpu, "using 0x%X 0x%X 0x%X...\n",
			pdpu->csc_ptr->csc_mv[0],
			pdpu->csc_ptr->csc_mv[1],
			pdpu->csc_ptr->csc_mv[2]);
पूर्ण

अटल व्योम _dpu_plane_setup_scaler(काष्ठा dpu_plane *pdpu,
		काष्ठा dpu_plane_state *pstate,
		स्थिर काष्ठा dpu_क्रमmat *fmt, bool color_fill)
अणु
	स्थिर काष्ठा drm_क्रमmat_info *info = drm_क्रमmat_info(fmt->base.pixel_क्रमmat);

	/* करोn't chroma subsample अगर decimating */
	/* update scaler. calculate शेष config क्रम QSEED3 */
	_dpu_plane_setup_scaler3(pdpu, pstate,
			drm_rect_width(&pdpu->pipe_cfg.src_rect),
			drm_rect_height(&pdpu->pipe_cfg.src_rect),
			drm_rect_width(&pdpu->pipe_cfg.dst_rect),
			drm_rect_height(&pdpu->pipe_cfg.dst_rect),
			&pstate->scaler3_cfg, fmt,
			info->hsub, info->vsub);
पूर्ण

/**
 * _dpu_plane_color_fill - enables color fill on plane
 * @pdpu:   Poपूर्णांकer to DPU plane object
 * @color:  RGB fill color value, [23..16] Blue, [15..8] Green, [7..0] Red
 * @alpha:  8-bit fill alpha value, 255 selects 100% alpha
 * Returns: 0 on success
 */
अटल पूर्णांक _dpu_plane_color_fill(काष्ठा dpu_plane *pdpu,
		uपूर्णांक32_t color, uपूर्णांक32_t alpha)
अणु
	स्थिर काष्ठा dpu_क्रमmat *fmt;
	स्थिर काष्ठा drm_plane *plane = &pdpu->base;
	काष्ठा dpu_plane_state *pstate = to_dpu_plane_state(plane->state);

	DPU_DEBUG_PLANE(pdpu, "\n");

	/*
	 * select fill क्रमmat to match user property expectation,
	 * h/w only supports RGB variants
	 */
	fmt = dpu_get_dpu_क्रमmat(DRM_FORMAT_ABGR8888);

	/* update sspp */
	अगर (fmt && pdpu->pipe_hw->ops.setup_solidfill) अणु
		pdpu->pipe_hw->ops.setup_solidfill(pdpu->pipe_hw,
				(color & 0xFFFFFF) | ((alpha & 0xFF) << 24),
				pstate->multirect_index);

		/* override scaler/decimation अगर solid fill */
		pdpu->pipe_cfg.src_rect.x1 = 0;
		pdpu->pipe_cfg.src_rect.y1 = 0;
		pdpu->pipe_cfg.src_rect.x2 =
			drm_rect_width(&pdpu->pipe_cfg.dst_rect);
		pdpu->pipe_cfg.src_rect.y2 =
			drm_rect_height(&pdpu->pipe_cfg.dst_rect);
		_dpu_plane_setup_scaler(pdpu, pstate, fmt, true);

		अगर (pdpu->pipe_hw->ops.setup_क्रमmat)
			pdpu->pipe_hw->ops.setup_क्रमmat(pdpu->pipe_hw,
					fmt, DPU_SSPP_SOLID_FILL,
					pstate->multirect_index);

		अगर (pdpu->pipe_hw->ops.setup_rects)
			pdpu->pipe_hw->ops.setup_rects(pdpu->pipe_hw,
					&pdpu->pipe_cfg,
					pstate->multirect_index);

		अगर (pdpu->pipe_hw->ops.setup_pe)
			pdpu->pipe_hw->ops.setup_pe(pdpu->pipe_hw,
					&pstate->pixel_ext);

		अगर (pdpu->pipe_hw->ops.setup_scaler &&
				pstate->multirect_index != DPU_SSPP_RECT_1)
			pdpu->pipe_hw->ops.setup_scaler(pdpu->pipe_hw,
					&pdpu->pipe_cfg, &pstate->pixel_ext,
					&pstate->scaler3_cfg);
	पूर्ण

	वापस 0;
पूर्ण

व्योम dpu_plane_clear_multirect(स्थिर काष्ठा drm_plane_state *drm_state)
अणु
	काष्ठा dpu_plane_state *pstate = to_dpu_plane_state(drm_state);

	pstate->multirect_index = DPU_SSPP_RECT_SOLO;
	pstate->multirect_mode = DPU_SSPP_MULTIRECT_NONE;
पूर्ण

पूर्णांक dpu_plane_validate_multirect_v2(काष्ठा dpu_multirect_plane_states *plane)
अणु
	काष्ठा dpu_plane_state *pstate[R_MAX];
	स्थिर काष्ठा drm_plane_state *drm_state[R_MAX];
	काष्ठा drm_rect src[R_MAX], dst[R_MAX];
	काष्ठा dpu_plane *dpu_plane[R_MAX];
	स्थिर काष्ठा dpu_क्रमmat *fmt[R_MAX];
	पूर्णांक i, buffer_lines;
	अचिन्हित पूर्णांक max_tile_height = 1;
	bool parallel_fetch_qualअगरied = true;
	bool has_tiled_rect = false;

	क्रम (i = 0; i < R_MAX; i++) अणु
		स्थिर काष्ठा msm_क्रमmat *msm_fmt;

		drm_state[i] = i ? plane->r1 : plane->r0;
		msm_fmt = msm_framebuffer_क्रमmat(drm_state[i]->fb);
		fmt[i] = to_dpu_क्रमmat(msm_fmt);

		अगर (DPU_FORMAT_IS_UBWC(fmt[i])) अणु
			has_tiled_rect = true;
			अगर (fmt[i]->tile_height > max_tile_height)
				max_tile_height = fmt[i]->tile_height;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < R_MAX; i++) अणु
		पूर्णांक width_threshold;

		pstate[i] = to_dpu_plane_state(drm_state[i]);
		dpu_plane[i] = to_dpu_plane(drm_state[i]->plane);

		अगर (pstate[i] == शून्य) अणु
			DPU_ERROR("DPU plane state of plane id %d is NULL\n",
				drm_state[i]->plane->base.id);
			वापस -EINVAL;
		पूर्ण

		src[i].x1 = drm_state[i]->src_x >> 16;
		src[i].y1 = drm_state[i]->src_y >> 16;
		src[i].x2 = src[i].x1 + (drm_state[i]->src_w >> 16);
		src[i].y2 = src[i].y1 + (drm_state[i]->src_h >> 16);

		dst[i] = drm_plane_state_dest(drm_state[i]);

		अगर (drm_rect_calc_hscale(&src[i], &dst[i], 1, 1) != 1 ||
		    drm_rect_calc_vscale(&src[i], &dst[i], 1, 1) != 1) अणु
			DPU_ERROR_PLANE(dpu_plane[i],
				"scaling is not supported in multirect mode\n");
			वापस -EINVAL;
		पूर्ण

		अगर (DPU_FORMAT_IS_YUV(fmt[i])) अणु
			DPU_ERROR_PLANE(dpu_plane[i],
				"Unsupported format for multirect mode\n");
			वापस -EINVAL;
		पूर्ण

		/**
		 * SSPP PD_MEM is split half - one क्रम each RECT.
		 * Tiled क्रमmats need 5 lines of buffering जबतक fetching
		 * whereas linear क्रमmats need only 2 lines.
		 * So we cannot support more than half of the supported SSPP
		 * width क्रम tiled क्रमmats.
		 */
		width_threshold = dpu_plane[i]->catalog->caps->max_linewidth;
		अगर (has_tiled_rect)
			width_threshold /= 2;

		अगर (parallel_fetch_qualअगरied &&
		    drm_rect_width(&src[i]) > width_threshold)
			parallel_fetch_qualअगरied = false;

	पूर्ण

	/* Validate RECT's and set the mode */

	/* Prefer PARALLEL FETCH Mode over TIME_MX Mode */
	अगर (parallel_fetch_qualअगरied) अणु
		pstate[R0]->multirect_mode = DPU_SSPP_MULTIRECT_PARALLEL;
		pstate[R1]->multirect_mode = DPU_SSPP_MULTIRECT_PARALLEL;

		जाओ करोne;
	पूर्ण

	/* TIME_MX Mode */
	buffer_lines = 2 * max_tile_height;

	अगर (dst[R1].y1 >= dst[R0].y2 + buffer_lines ||
	    dst[R0].y1 >= dst[R1].y2 + buffer_lines) अणु
		pstate[R0]->multirect_mode = DPU_SSPP_MULTIRECT_TIME_MX;
		pstate[R1]->multirect_mode = DPU_SSPP_MULTIRECT_TIME_MX;
	पूर्ण अन्यथा अणु
		DPU_ERROR(
			"No multirect mode possible for the planes (%d - %d)\n",
			drm_state[R0]->plane->base.id,
			drm_state[R1]->plane->base.id);
		वापस -EINVAL;
	पूर्ण

करोne:
	अगर (dpu_plane[R0]->is_भव) अणु
		pstate[R0]->multirect_index = DPU_SSPP_RECT_1;
		pstate[R1]->multirect_index = DPU_SSPP_RECT_0;
	पूर्ण अन्यथा अणु
		pstate[R0]->multirect_index = DPU_SSPP_RECT_0;
		pstate[R1]->multirect_index = DPU_SSPP_RECT_1;
	पूर्ण

	DPU_DEBUG_PLANE(dpu_plane[R0], "R0: %d - %d\n",
		pstate[R0]->multirect_mode, pstate[R0]->multirect_index);
	DPU_DEBUG_PLANE(dpu_plane[R1], "R1: %d - %d\n",
		pstate[R1]->multirect_mode, pstate[R1]->multirect_index);
	वापस 0;
पूर्ण

/**
 * dpu_plane_get_ctl_flush - get control flush क्रम the given plane
 * @plane: Poपूर्णांकer to drm plane काष्ठाure
 * @ctl: Poपूर्णांकer to hardware control driver
 * @flush_sspp: Poपूर्णांकer to sspp flush control word
 */
व्योम dpu_plane_get_ctl_flush(काष्ठा drm_plane *plane, काष्ठा dpu_hw_ctl *ctl,
		u32 *flush_sspp)
अणु
	*flush_sspp = ctl->ops.get_biपंचांगask_sspp(ctl, dpu_plane_pipe(plane));
पूर्ण

अटल पूर्णांक dpu_plane_prepare_fb(काष्ठा drm_plane *plane,
		काष्ठा drm_plane_state *new_state)
अणु
	काष्ठा drm_framebuffer *fb = new_state->fb;
	काष्ठा dpu_plane *pdpu = to_dpu_plane(plane);
	काष्ठा dpu_plane_state *pstate = to_dpu_plane_state(new_state);
	काष्ठा dpu_hw_fmt_layout layout;
	काष्ठा dpu_kms *kms = _dpu_plane_get_kms(&pdpu->base);
	पूर्णांक ret;

	अगर (!new_state->fb)
		वापस 0;

	DPU_DEBUG_PLANE(pdpu, "FB[%u]\n", fb->base.id);

	/* cache aspace */
	pstate->aspace = kms->base.aspace;

	/*
	 * TODO: Need to sort out the msm_framebuffer_prepare() call below so
	 *       we can use msm_atomic_prepare_fb() instead of करोing the
	 *       implicit fence and fb prepare by hand here.
	 */
	drm_gem_plane_helper_prepare_fb(plane, new_state);

	अगर (pstate->aspace) अणु
		ret = msm_framebuffer_prepare(new_state->fb,
				pstate->aspace);
		अगर (ret) अणु
			DPU_ERROR("failed to prepare framebuffer\n");
			वापस ret;
		पूर्ण
	पूर्ण

	/* validate framebuffer layout beक्रमe commit */
	ret = dpu_क्रमmat_populate_layout(pstate->aspace,
			new_state->fb, &layout);
	अगर (ret) अणु
		DPU_ERROR_PLANE(pdpu, "failed to get format layout, %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम dpu_plane_cleanup_fb(काष्ठा drm_plane *plane,
		काष्ठा drm_plane_state *old_state)
अणु
	काष्ठा dpu_plane *pdpu = to_dpu_plane(plane);
	काष्ठा dpu_plane_state *old_pstate;

	अगर (!old_state || !old_state->fb)
		वापस;

	old_pstate = to_dpu_plane_state(old_state);

	DPU_DEBUG_PLANE(pdpu, "FB[%u]\n", old_state->fb->base.id);

	msm_framebuffer_cleanup(old_state->fb, old_pstate->aspace);
पूर्ण

अटल bool dpu_plane_validate_src(काष्ठा drm_rect *src,
				   काष्ठा drm_rect *fb_rect,
				   uपूर्णांक32_t min_src_size)
अणु
	/* Ensure fb size is supported */
	अगर (drm_rect_width(fb_rect) > MAX_IMG_WIDTH ||
	    drm_rect_height(fb_rect) > MAX_IMG_HEIGHT)
		वापस false;

	/* Ensure src rect is above the minimum size */
	अगर (drm_rect_width(src) < min_src_size ||
	    drm_rect_height(src) < min_src_size)
		वापस false;

	/* Ensure src is fully encapsulated in fb */
	वापस drm_rect_पूर्णांकersect(fb_rect, src) &&
		drm_rect_equals(fb_rect, src);
पूर्ण

अटल पूर्णांक dpu_plane_atomic_check(काष्ठा drm_plane *plane,
				  काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_plane_state = drm_atomic_get_new_plane_state(state,
										 plane);
	पूर्णांक ret = 0, min_scale;
	काष्ठा dpu_plane *pdpu = to_dpu_plane(plane);
	काष्ठा dpu_plane_state *pstate = to_dpu_plane_state(new_plane_state);
	स्थिर काष्ठा drm_crtc_state *crtc_state = शून्य;
	स्थिर काष्ठा dpu_क्रमmat *fmt;
	काष्ठा drm_rect src, dst, fb_rect = अणु 0 पूर्ण;
	uपूर्णांक32_t min_src_size, max_linewidth;

	अगर (new_plane_state->crtc)
		crtc_state = drm_atomic_get_new_crtc_state(state,
							   new_plane_state->crtc);

	min_scale = FRAC_16_16(1, pdpu->pipe_sblk->maxupscale);
	ret = drm_atomic_helper_check_plane_state(new_plane_state, crtc_state,
						  min_scale,
						  pdpu->pipe_sblk->maxdwnscale << 16,
						  true, true);
	अगर (ret) अणु
		DPU_DEBUG_PLANE(pdpu, "Check plane state failed (%d)\n", ret);
		वापस ret;
	पूर्ण
	अगर (!new_plane_state->visible)
		वापस 0;

	src.x1 = new_plane_state->src_x >> 16;
	src.y1 = new_plane_state->src_y >> 16;
	src.x2 = src.x1 + (new_plane_state->src_w >> 16);
	src.y2 = src.y1 + (new_plane_state->src_h >> 16);

	dst = drm_plane_state_dest(new_plane_state);

	fb_rect.x2 = new_plane_state->fb->width;
	fb_rect.y2 = new_plane_state->fb->height;

	max_linewidth = pdpu->catalog->caps->max_linewidth;

	fmt = to_dpu_क्रमmat(msm_framebuffer_क्रमmat(new_plane_state->fb));

	min_src_size = DPU_FORMAT_IS_YUV(fmt) ? 2 : 1;

	अगर (DPU_FORMAT_IS_YUV(fmt) &&
		(!(pdpu->features & DPU_SSPP_SCALER) ||
		 !(pdpu->features & (BIT(DPU_SSPP_CSC)
		 | BIT(DPU_SSPP_CSC_10BIT))))) अणु
		DPU_DEBUG_PLANE(pdpu,
				"plane doesn't have scaler/csc for yuv\n");
		वापस -EINVAL;

	/* check src bounds */
	पूर्ण अन्यथा अगर (!dpu_plane_validate_src(&src, &fb_rect, min_src_size)) अणु
		DPU_DEBUG_PLANE(pdpu, "invalid source " DRM_RECT_FMT "\n",
				DRM_RECT_ARG(&src));
		वापस -E2BIG;

	/* valid yuv image */
	पूर्ण अन्यथा अगर (DPU_FORMAT_IS_YUV(fmt) &&
		   (src.x1 & 0x1 || src.y1 & 0x1 ||
		    drm_rect_width(&src) & 0x1 ||
		    drm_rect_height(&src) & 0x1)) अणु
		DPU_DEBUG_PLANE(pdpu, "invalid yuv source " DRM_RECT_FMT "\n",
				DRM_RECT_ARG(&src));
		वापस -EINVAL;

	/* min dst support */
	पूर्ण अन्यथा अगर (drm_rect_width(&dst) < 0x1 || drm_rect_height(&dst) < 0x1) अणु
		DPU_DEBUG_PLANE(pdpu, "invalid dest rect " DRM_RECT_FMT "\n",
				DRM_RECT_ARG(&dst));
		वापस -EINVAL;

	/* check decimated source width */
	पूर्ण अन्यथा अगर (drm_rect_width(&src) > max_linewidth) अणु
		DPU_DEBUG_PLANE(pdpu, "invalid src " DRM_RECT_FMT " line:%u\n",
				DRM_RECT_ARG(&src), max_linewidth);
		वापस -E2BIG;
	पूर्ण

	pstate->needs_qos_remap = drm_atomic_crtc_needs_modeset(crtc_state);

	वापस 0;
पूर्ण

व्योम dpu_plane_flush(काष्ठा drm_plane *plane)
अणु
	काष्ठा dpu_plane *pdpu;
	काष्ठा dpu_plane_state *pstate;

	अगर (!plane || !plane->state) अणु
		DPU_ERROR("invalid plane\n");
		वापस;
	पूर्ण

	pdpu = to_dpu_plane(plane);
	pstate = to_dpu_plane_state(plane->state);

	/*
	 * These updates have to be करोne immediately beक्रमe the plane flush
	 * timing, and may not be moved to the atomic_update/mode_set functions.
	 */
	अगर (pdpu->is_error)
		/* क्रमce white frame with 100% alpha pipe output on error */
		_dpu_plane_color_fill(pdpu, 0xFFFFFF, 0xFF);
	अन्यथा अगर (pdpu->color_fill & DPU_PLANE_COLOR_FILL_FLAG)
		/* क्रमce 100% alpha */
		_dpu_plane_color_fill(pdpu, pdpu->color_fill, 0xFF);
	अन्यथा अगर (pdpu->pipe_hw && pdpu->csc_ptr && pdpu->pipe_hw->ops.setup_csc)
		pdpu->pipe_hw->ops.setup_csc(pdpu->pipe_hw, pdpu->csc_ptr);

	/* flag h/w flush complete */
	अगर (plane->state)
		pstate->pending = false;
पूर्ण

/**
 * dpu_plane_set_error: enable/disable error condition
 * @plane: poपूर्णांकer to drm_plane काष्ठाure
 * @error: error value to set
 */
व्योम dpu_plane_set_error(काष्ठा drm_plane *plane, bool error)
अणु
	काष्ठा dpu_plane *pdpu;

	अगर (!plane)
		वापस;

	pdpu = to_dpu_plane(plane);
	pdpu->is_error = error;
पूर्ण

अटल व्योम dpu_plane_sspp_atomic_update(काष्ठा drm_plane *plane)
अणु
	uपूर्णांक32_t src_flags;
	काष्ठा dpu_plane *pdpu = to_dpu_plane(plane);
	काष्ठा drm_plane_state *state = plane->state;
	काष्ठा dpu_plane_state *pstate = to_dpu_plane_state(state);
	काष्ठा drm_crtc *crtc = state->crtc;
	काष्ठा drm_framebuffer *fb = state->fb;
	bool is_rt_pipe, update_qos_remap;
	स्थिर काष्ठा dpu_क्रमmat *fmt =
		to_dpu_क्रमmat(msm_framebuffer_क्रमmat(fb));

	स_रखो(&(pdpu->pipe_cfg), 0, माप(काष्ठा dpu_hw_pipe_cfg));

	_dpu_plane_set_scanout(plane, pstate, &pdpu->pipe_cfg, fb);

	pstate->pending = true;

	is_rt_pipe = (dpu_crtc_get_client_type(crtc) != NRT_CLIENT);
	_dpu_plane_set_qos_ctrl(plane, false, DPU_PLANE_QOS_PANIC_CTRL);

	DPU_DEBUG_PLANE(pdpu, "FB[%u] " DRM_RECT_FP_FMT "->crtc%u " DRM_RECT_FMT
			", %4.4s ubwc %d\n", fb->base.id, DRM_RECT_FP_ARG(&state->src),
			crtc->base.id, DRM_RECT_ARG(&state->dst),
			(अक्षर *)&fmt->base.pixel_क्रमmat, DPU_FORMAT_IS_UBWC(fmt));

	pdpu->pipe_cfg.src_rect = state->src;

	/* state->src is 16.16, src_rect is not */
	pdpu->pipe_cfg.src_rect.x1 >>= 16;
	pdpu->pipe_cfg.src_rect.x2 >>= 16;
	pdpu->pipe_cfg.src_rect.y1 >>= 16;
	pdpu->pipe_cfg.src_rect.y2 >>= 16;

	pdpu->pipe_cfg.dst_rect = state->dst;

	_dpu_plane_setup_scaler(pdpu, pstate, fmt, false);

	/* override क्रम color fill */
	अगर (pdpu->color_fill & DPU_PLANE_COLOR_FILL_FLAG) अणु
		/* skip reमुख्यing processing on color fill */
		वापस;
	पूर्ण

	अगर (pdpu->pipe_hw->ops.setup_rects) अणु
		pdpu->pipe_hw->ops.setup_rects(pdpu->pipe_hw,
				&pdpu->pipe_cfg,
				pstate->multirect_index);
	पूर्ण

	अगर (pdpu->pipe_hw->ops.setup_pe &&
			(pstate->multirect_index != DPU_SSPP_RECT_1))
		pdpu->pipe_hw->ops.setup_pe(pdpu->pipe_hw,
				&pstate->pixel_ext);

	/**
	 * when programmed in multirect mode, scalar block will be
	 * bypassed. Still we need to update alpha and bitwidth
	 * ONLY क्रम RECT0
	 */
	अगर (pdpu->pipe_hw->ops.setup_scaler &&
			pstate->multirect_index != DPU_SSPP_RECT_1)
		pdpu->pipe_hw->ops.setup_scaler(pdpu->pipe_hw,
				&pdpu->pipe_cfg, &pstate->pixel_ext,
				&pstate->scaler3_cfg);

	अगर (pdpu->pipe_hw->ops.setup_multirect)
		pdpu->pipe_hw->ops.setup_multirect(
				pdpu->pipe_hw,
				pstate->multirect_index,
				pstate->multirect_mode);

	अगर (pdpu->pipe_hw->ops.setup_क्रमmat) अणु
		अचिन्हित पूर्णांक rotation;

		src_flags = 0x0;

		rotation = drm_rotation_simplअगरy(state->rotation,
						 DRM_MODE_ROTATE_0 |
						 DRM_MODE_REFLECT_X |
						 DRM_MODE_REFLECT_Y);

		अगर (rotation & DRM_MODE_REFLECT_X)
			src_flags |= DPU_SSPP_FLIP_LR;

		अगर (rotation & DRM_MODE_REFLECT_Y)
			src_flags |= DPU_SSPP_FLIP_UD;

		/* update क्रमmat */
		pdpu->pipe_hw->ops.setup_क्रमmat(pdpu->pipe_hw, fmt, src_flags,
				pstate->multirect_index);

		अगर (pdpu->pipe_hw->ops.setup_cdp) अणु
			काष्ठा dpu_hw_pipe_cdp_cfg *cdp_cfg = &pstate->cdp_cfg;

			स_रखो(cdp_cfg, 0, माप(काष्ठा dpu_hw_pipe_cdp_cfg));

			cdp_cfg->enable = pdpu->catalog->perf.cdp_cfg
					[DPU_PERF_CDP_USAGE_RT].rd_enable;
			cdp_cfg->ubwc_meta_enable =
					DPU_FORMAT_IS_UBWC(fmt);
			cdp_cfg->tile_amortize_enable =
					DPU_FORMAT_IS_UBWC(fmt) ||
					DPU_FORMAT_IS_TILE(fmt);
			cdp_cfg->preload_ahead = DPU_SSPP_CDP_PRELOAD_AHEAD_64;

			pdpu->pipe_hw->ops.setup_cdp(pdpu->pipe_hw, cdp_cfg);
		पूर्ण

		/* update csc */
		अगर (DPU_FORMAT_IS_YUV(fmt))
			_dpu_plane_setup_csc(pdpu);
		अन्यथा
			pdpu->csc_ptr = 0;
	पूर्ण

	_dpu_plane_set_qos_lut(plane, fb);
	_dpu_plane_set_danger_lut(plane, fb);

	अगर (plane->type != DRM_PLANE_TYPE_CURSOR) अणु
		_dpu_plane_set_qos_ctrl(plane, true, DPU_PLANE_QOS_PANIC_CTRL);
		_dpu_plane_set_ot_limit(plane, crtc);
	पूर्ण

	update_qos_remap = (is_rt_pipe != pdpu->is_rt_pipe) ||
			pstate->needs_qos_remap;

	अगर (update_qos_remap) अणु
		अगर (is_rt_pipe != pdpu->is_rt_pipe)
			pdpu->is_rt_pipe = is_rt_pipe;
		अन्यथा अगर (pstate->needs_qos_remap)
			pstate->needs_qos_remap = false;
		_dpu_plane_set_qos_remap(plane);
	पूर्ण

	_dpu_plane_calc_bw(plane, fb);

	_dpu_plane_calc_clk(plane);
पूर्ण

अटल व्योम _dpu_plane_atomic_disable(काष्ठा drm_plane *plane)
अणु
	काष्ठा dpu_plane *pdpu = to_dpu_plane(plane);
	काष्ठा drm_plane_state *state = plane->state;
	काष्ठा dpu_plane_state *pstate = to_dpu_plane_state(state);

	trace_dpu_plane_disable(DRMID(plane), is_dpu_plane_भव(plane),
				pstate->multirect_mode);

	pstate->pending = true;

	अगर (is_dpu_plane_भव(plane) &&
			pdpu->pipe_hw && pdpu->pipe_hw->ops.setup_multirect)
		pdpu->pipe_hw->ops.setup_multirect(pdpu->pipe_hw,
				DPU_SSPP_RECT_SOLO, DPU_SSPP_MULTIRECT_NONE);
पूर्ण

अटल व्योम dpu_plane_atomic_update(काष्ठा drm_plane *plane,
				काष्ठा drm_atomic_state *state)
अणु
	काष्ठा dpu_plane *pdpu = to_dpu_plane(plane);
	काष्ठा drm_plane_state *new_state = drm_atomic_get_new_plane_state(state,
									   plane);

	pdpu->is_error = false;

	DPU_DEBUG_PLANE(pdpu, "\n");

	अगर (!new_state->visible) अणु
		_dpu_plane_atomic_disable(plane);
	पूर्ण अन्यथा अणु
		dpu_plane_sspp_atomic_update(plane);
	पूर्ण
पूर्ण

अटल व्योम dpu_plane_destroy(काष्ठा drm_plane *plane)
अणु
	काष्ठा dpu_plane *pdpu = plane ? to_dpu_plane(plane) : शून्य;

	DPU_DEBUG_PLANE(pdpu, "\n");

	अगर (pdpu) अणु
		_dpu_plane_set_qos_ctrl(plane, false, DPU_PLANE_QOS_PANIC_CTRL);

		mutex_destroy(&pdpu->lock);

		/* this will destroy the states as well */
		drm_plane_cleanup(plane);

		dpu_hw_sspp_destroy(pdpu->pipe_hw);

		kमुक्त(pdpu);
	पूर्ण
पूर्ण

अटल व्योम dpu_plane_destroy_state(काष्ठा drm_plane *plane,
		काष्ठा drm_plane_state *state)
अणु
	__drm_atomic_helper_plane_destroy_state(state);
	kमुक्त(to_dpu_plane_state(state));
पूर्ण

अटल काष्ठा drm_plane_state *
dpu_plane_duplicate_state(काष्ठा drm_plane *plane)
अणु
	काष्ठा dpu_plane *pdpu;
	काष्ठा dpu_plane_state *pstate;
	काष्ठा dpu_plane_state *old_state;

	अगर (!plane) अणु
		DPU_ERROR("invalid plane\n");
		वापस शून्य;
	पूर्ण अन्यथा अगर (!plane->state) अणु
		DPU_ERROR("invalid plane state\n");
		वापस शून्य;
	पूर्ण

	old_state = to_dpu_plane_state(plane->state);
	pdpu = to_dpu_plane(plane);
	pstate = kmemdup(old_state, माप(*old_state), GFP_KERNEL);
	अगर (!pstate) अणु
		DPU_ERROR_PLANE(pdpu, "failed to allocate state\n");
		वापस शून्य;
	पूर्ण

	DPU_DEBUG_PLANE(pdpu, "\n");

	pstate->pending = false;

	__drm_atomic_helper_plane_duplicate_state(plane, &pstate->base);

	वापस &pstate->base;
पूर्ण

अटल व्योम dpu_plane_reset(काष्ठा drm_plane *plane)
अणु
	काष्ठा dpu_plane *pdpu;
	काष्ठा dpu_plane_state *pstate;

	अगर (!plane) अणु
		DPU_ERROR("invalid plane\n");
		वापस;
	पूर्ण

	pdpu = to_dpu_plane(plane);
	DPU_DEBUG_PLANE(pdpu, "\n");

	/* हटाओ previous state, अगर present */
	अगर (plane->state) अणु
		dpu_plane_destroy_state(plane, plane->state);
		plane->state = 0;
	पूर्ण

	pstate = kzalloc(माप(*pstate), GFP_KERNEL);
	अगर (!pstate) अणु
		DPU_ERROR_PLANE(pdpu, "failed to allocate state\n");
		वापस;
	पूर्ण

	pstate->base.plane = plane;

	plane->state = &pstate->base;
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
अटल व्योम dpu_plane_danger_संकेत_ctrl(काष्ठा drm_plane *plane, bool enable)
अणु
	काष्ठा dpu_plane *pdpu = to_dpu_plane(plane);
	काष्ठा dpu_kms *dpu_kms = _dpu_plane_get_kms(plane);

	अगर (!pdpu->is_rt_pipe)
		वापस;

	pm_runसमय_get_sync(&dpu_kms->pdev->dev);
	_dpu_plane_set_qos_ctrl(plane, enable, DPU_PLANE_QOS_PANIC_CTRL);
	pm_runसमय_put_sync(&dpu_kms->pdev->dev);
पूर्ण

अटल sमाप_प्रकार _dpu_plane_danger_पढ़ो(काष्ठा file *file,
			अक्षर __user *buff, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा dpu_kms *kms = file->निजी_data;
	पूर्णांक len;
	अक्षर buf[40];

	len = scnम_लिखो(buf, माप(buf), "%d\n", !kms->has_danger_ctrl);

	वापस simple_पढ़ो_from_buffer(buff, count, ppos, buf, len);
पूर्ण

अटल व्योम _dpu_plane_set_danger_state(काष्ठा dpu_kms *kms, bool enable)
अणु
	काष्ठा drm_plane *plane;

	drm_क्रम_each_plane(plane, kms->dev) अणु
		अगर (plane->fb && plane->state) अणु
			dpu_plane_danger_संकेत_ctrl(plane, enable);
			DPU_DEBUG("plane:%d img:%dx%d ",
				plane->base.id, plane->fb->width,
				plane->fb->height);
			DPU_DEBUG("src[%d,%d,%d,%d] dst[%d,%d,%d,%d]\n",
				plane->state->src_x >> 16,
				plane->state->src_y >> 16,
				plane->state->src_w >> 16,
				plane->state->src_h >> 16,
				plane->state->crtc_x, plane->state->crtc_y,
				plane->state->crtc_w, plane->state->crtc_h);
		पूर्ण अन्यथा अणु
			DPU_DEBUG("Inactive plane:%d\n", plane->base.id);
		पूर्ण
	पूर्ण
पूर्ण

अटल sमाप_प्रकार _dpu_plane_danger_ग_लिखो(काष्ठा file *file,
		    स्थिर अक्षर __user *user_buf, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा dpu_kms *kms = file->निजी_data;
	पूर्णांक disable_panic;
	पूर्णांक ret;

	ret = kstrtouपूर्णांक_from_user(user_buf, count, 0, &disable_panic);
	अगर (ret)
		वापस ret;

	अगर (disable_panic) अणु
		/* Disable panic संकेत क्रम all active pipes */
		DPU_DEBUG("Disabling danger:\n");
		_dpu_plane_set_danger_state(kms, false);
		kms->has_danger_ctrl = false;
	पूर्ण अन्यथा अणु
		/* Enable panic संकेत क्रम all active pipes */
		DPU_DEBUG("Enabling danger:\n");
		kms->has_danger_ctrl = true;
		_dpu_plane_set_danger_state(kms, true);
	पूर्ण

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations dpu_plane_danger_enable = अणु
	.खोलो = simple_खोलो,
	.पढ़ो = _dpu_plane_danger_पढ़ो,
	.ग_लिखो = _dpu_plane_danger_ग_लिखो,
पूर्ण;

अटल पूर्णांक _dpu_plane_init_debugfs(काष्ठा drm_plane *plane)
अणु
	काष्ठा dpu_plane *pdpu = to_dpu_plane(plane);
	काष्ठा dpu_kms *kms = _dpu_plane_get_kms(plane);
	स्थिर काष्ठा dpu_sspp_cfg *cfg = pdpu->pipe_hw->cap;
	स्थिर काष्ठा dpu_sspp_sub_blks *sblk = cfg->sblk;

	/* create overall sub-directory क्रम the pipe */
	pdpu->debugfs_root =
		debugfs_create_dir(pdpu->pipe_name,
				plane->dev->primary->debugfs_root);

	/* करोn't error check these */
	debugfs_create_x32("features", 0600,
			pdpu->debugfs_root, &pdpu->features);

	/* add रेजिस्टर dump support */
	dpu_debugfs_setup_regset32(&pdpu->debugfs_src,
			sblk->src_blk.base + cfg->base,
			sblk->src_blk.len,
			kms);
	dpu_debugfs_create_regset32("src_blk", 0400,
			pdpu->debugfs_root, &pdpu->debugfs_src);

	अगर (cfg->features & BIT(DPU_SSPP_SCALER_QSEED3) ||
			cfg->features & BIT(DPU_SSPP_SCALER_QSEED3LITE) ||
			cfg->features & BIT(DPU_SSPP_SCALER_QSEED2) ||
			cfg->features & BIT(DPU_SSPP_SCALER_QSEED4)) अणु
		dpu_debugfs_setup_regset32(&pdpu->debugfs_scaler,
				sblk->scaler_blk.base + cfg->base,
				sblk->scaler_blk.len,
				kms);
		dpu_debugfs_create_regset32("scaler_blk", 0400,
				pdpu->debugfs_root,
				&pdpu->debugfs_scaler);
		debugfs_create_bool("default_scaling",
				0600,
				pdpu->debugfs_root,
				&pdpu->debugfs_शेष_scale);
	पूर्ण

	अगर (cfg->features & BIT(DPU_SSPP_CSC) ||
			cfg->features & BIT(DPU_SSPP_CSC_10BIT)) अणु
		dpu_debugfs_setup_regset32(&pdpu->debugfs_csc,
				sblk->csc_blk.base + cfg->base,
				sblk->csc_blk.len,
				kms);
		dpu_debugfs_create_regset32("csc_blk", 0400,
				pdpu->debugfs_root, &pdpu->debugfs_csc);
	पूर्ण

	debugfs_create_u32("xin_id",
			0400,
			pdpu->debugfs_root,
			(u32 *) &cfg->xin_id);
	debugfs_create_u32("clk_ctrl",
			0400,
			pdpu->debugfs_root,
			(u32 *) &cfg->clk_ctrl);
	debugfs_create_x32("creq_vblank",
			0600,
			pdpu->debugfs_root,
			(u32 *) &sblk->creq_vblank);
	debugfs_create_x32("danger_vblank",
			0600,
			pdpu->debugfs_root,
			(u32 *) &sblk->danger_vblank);

	debugfs_create_file("disable_danger",
			0600,
			pdpu->debugfs_root,
			kms, &dpu_plane_danger_enable);

	वापस 0;
पूर्ण
#अन्यथा
अटल पूर्णांक _dpu_plane_init_debugfs(काष्ठा drm_plane *plane)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक dpu_plane_late_रेजिस्टर(काष्ठा drm_plane *plane)
अणु
	वापस _dpu_plane_init_debugfs(plane);
पूर्ण

अटल व्योम dpu_plane_early_unरेजिस्टर(काष्ठा drm_plane *plane)
अणु
	काष्ठा dpu_plane *pdpu = to_dpu_plane(plane);

	debugfs_हटाओ_recursive(pdpu->debugfs_root);
पूर्ण

अटल bool dpu_plane_क्रमmat_mod_supported(काष्ठा drm_plane *plane,
		uपूर्णांक32_t क्रमmat, uपूर्णांक64_t modअगरier)
अणु
	अगर (modअगरier == DRM_FORMAT_MOD_LINEAR)
		वापस true;

	अगर (modअगरier == DRM_FORMAT_MOD_QCOM_COMPRESSED) अणु
		पूर्णांक i;
		क्रम (i = 0; i < ARRAY_SIZE(qcom_compressed_supported_क्रमmats); i++) अणु
			अगर (क्रमmat == qcom_compressed_supported_क्रमmats[i])
				वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल स्थिर काष्ठा drm_plane_funcs dpu_plane_funcs = अणु
		.update_plane = drm_atomic_helper_update_plane,
		.disable_plane = drm_atomic_helper_disable_plane,
		.destroy = dpu_plane_destroy,
		.reset = dpu_plane_reset,
		.atomic_duplicate_state = dpu_plane_duplicate_state,
		.atomic_destroy_state = dpu_plane_destroy_state,
		.late_रेजिस्टर = dpu_plane_late_रेजिस्टर,
		.early_unरेजिस्टर = dpu_plane_early_unरेजिस्टर,
		.क्रमmat_mod_supported = dpu_plane_क्रमmat_mod_supported,
पूर्ण;

अटल स्थिर काष्ठा drm_plane_helper_funcs dpu_plane_helper_funcs = अणु
		.prepare_fb = dpu_plane_prepare_fb,
		.cleanup_fb = dpu_plane_cleanup_fb,
		.atomic_check = dpu_plane_atomic_check,
		.atomic_update = dpu_plane_atomic_update,
पूर्ण;

क्रमागत dpu_sspp dpu_plane_pipe(काष्ठा drm_plane *plane)
अणु
	वापस plane ? to_dpu_plane(plane)->pipe : SSPP_NONE;
पूर्ण

bool is_dpu_plane_भव(काष्ठा drm_plane *plane)
अणु
	वापस plane ? to_dpu_plane(plane)->is_भव : false;
पूर्ण

/* initialize plane */
काष्ठा drm_plane *dpu_plane_init(काष्ठा drm_device *dev,
		uपूर्णांक32_t pipe, क्रमागत drm_plane_type type,
		अचिन्हित दीर्घ possible_crtcs, u32 master_plane_id)
अणु
	काष्ठा drm_plane *plane = शून्य, *master_plane = शून्य;
	स्थिर uपूर्णांक32_t *क्रमmat_list;
	काष्ठा dpu_plane *pdpu;
	काष्ठा msm_drm_निजी *priv = dev->dev_निजी;
	काष्ठा dpu_kms *kms = to_dpu_kms(priv->kms);
	पूर्णांक zpos_max = DPU_ZPOS_MAX;
	uपूर्णांक32_t num_क्रमmats;
	पूर्णांक ret = -EINVAL;

	/* create and zero local काष्ठाure */
	pdpu = kzalloc(माप(*pdpu), GFP_KERNEL);
	अगर (!pdpu) अणु
		DPU_ERROR("[%u]failed to allocate local plane struct\n", pipe);
		ret = -ENOMEM;
		वापस ERR_PTR(ret);
	पूर्ण

	/* cache local stuff क्रम later */
	plane = &pdpu->base;
	pdpu->pipe = pipe;
	pdpu->is_भव = (master_plane_id != 0);
	INIT_LIST_HEAD(&pdpu->mplane_list);
	master_plane = drm_plane_find(dev, शून्य, master_plane_id);
	अगर (master_plane) अणु
		काष्ठा dpu_plane *mpdpu = to_dpu_plane(master_plane);

		list_add_tail(&pdpu->mplane_list, &mpdpu->mplane_list);
	पूर्ण

	/* initialize underlying h/w driver */
	pdpu->pipe_hw = dpu_hw_sspp_init(pipe, kms->mmio, kms->catalog,
							master_plane_id != 0);
	अगर (IS_ERR(pdpu->pipe_hw)) अणु
		DPU_ERROR("[%u]SSPP init failed\n", pipe);
		ret = PTR_ERR(pdpu->pipe_hw);
		जाओ clean_plane;
	पूर्ण अन्यथा अगर (!pdpu->pipe_hw->cap || !pdpu->pipe_hw->cap->sblk) अणु
		DPU_ERROR("[%u]SSPP init returned invalid cfg\n", pipe);
		जाओ clean_sspp;
	पूर्ण

	/* cache features mask क्रम later */
	pdpu->features = pdpu->pipe_hw->cap->features;
	pdpu->pipe_sblk = pdpu->pipe_hw->cap->sblk;
	अगर (!pdpu->pipe_sblk) अणु
		DPU_ERROR("[%u]invalid sblk\n", pipe);
		जाओ clean_sspp;
	पूर्ण

	अगर (pdpu->is_भव) अणु
		क्रमmat_list = pdpu->pipe_sblk->virt_क्रमmat_list;
		num_क्रमmats = pdpu->pipe_sblk->virt_num_क्रमmats;
	पूर्ण
	अन्यथा अणु
		क्रमmat_list = pdpu->pipe_sblk->क्रमmat_list;
		num_क्रमmats = pdpu->pipe_sblk->num_क्रमmats;
	पूर्ण

	ret = drm_universal_plane_init(dev, plane, 0xff, &dpu_plane_funcs,
				क्रमmat_list, num_क्रमmats,
				supported_क्रमmat_modअगरiers, type, शून्य);
	अगर (ret)
		जाओ clean_sspp;

	pdpu->catalog = kms->catalog;

	अगर (kms->catalog->mixer_count &&
		kms->catalog->mixer[0].sblk->maxblendstages) अणु
		zpos_max = kms->catalog->mixer[0].sblk->maxblendstages - 1;
		अगर (zpos_max > DPU_STAGE_MAX - DPU_STAGE_0 - 1)
			zpos_max = DPU_STAGE_MAX - DPU_STAGE_0 - 1;
	पूर्ण

	ret = drm_plane_create_zpos_property(plane, 0, 0, zpos_max);
	अगर (ret)
		DPU_ERROR("failed to install zpos property, rc = %d\n", ret);

	drm_plane_create_rotation_property(plane,
			DRM_MODE_ROTATE_0,
			DRM_MODE_ROTATE_0 |
			DRM_MODE_ROTATE_180 |
			DRM_MODE_REFLECT_X |
			DRM_MODE_REFLECT_Y);

	drm_plane_enable_fb_damage_clips(plane);

	/* success! finalize initialization */
	drm_plane_helper_add(plane, &dpu_plane_helper_funcs);

	/* save user मित्रly pipe name क्रम later */
	snम_लिखो(pdpu->pipe_name, DPU_NAME_SIZE, "plane%u", plane->base.id);

	mutex_init(&pdpu->lock);

	DPU_DEBUG("%s created for pipe:%u id:%u virtual:%u\n", pdpu->pipe_name,
					pipe, plane->base.id, master_plane_id);
	वापस plane;

clean_sspp:
	अगर (pdpu && pdpu->pipe_hw)
		dpu_hw_sspp_destroy(pdpu->pipe_hw);
clean_plane:
	kमुक्त(pdpu);
	वापस ERR_PTR(ret);
पूर्ण
