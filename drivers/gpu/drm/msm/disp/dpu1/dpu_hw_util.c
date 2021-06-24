<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2015-2018, The Linux Foundation. All rights reserved.
 */
#घोषणा pr_fmt(fmt)	"[drm:%s:%d] " fmt, __func__, __LINE__

#समावेश "msm_drv.h"
#समावेश "dpu_kms.h"
#समावेश "dpu_hw_mdss.h"
#समावेश "dpu_hw_util.h"

/* using a file अटल variables क्रम debugfs access */
अटल u32 dpu_hw_util_log_mask = DPU_DBG_MASK_NONE;

/* DPU_SCALER_QSEED3 */
#घोषणा QSEED3_HW_VERSION                  0x00
#घोषणा QSEED3_OP_MODE                     0x04
#घोषणा QSEED3_RGB2Y_COEFF                 0x08
#घोषणा QSEED3_PHASE_INIT                  0x0C
#घोषणा QSEED3_PHASE_STEP_Y_H              0x10
#घोषणा QSEED3_PHASE_STEP_Y_V              0x14
#घोषणा QSEED3_PHASE_STEP_UV_H             0x18
#घोषणा QSEED3_PHASE_STEP_UV_V             0x1C
#घोषणा QSEED3_PRELOAD                     0x20
#घोषणा QSEED3_DE_SHARPEN                  0x24
#घोषणा QSEED3_DE_SHARPEN_CTL              0x28
#घोषणा QSEED3_DE_SHAPE_CTL                0x2C
#घोषणा QSEED3_DE_THRESHOLD                0x30
#घोषणा QSEED3_DE_ADJUST_DATA_0            0x34
#घोषणा QSEED3_DE_ADJUST_DATA_1            0x38
#घोषणा QSEED3_DE_ADJUST_DATA_2            0x3C
#घोषणा QSEED3_SRC_SIZE_Y_RGB_A            0x40
#घोषणा QSEED3_SRC_SIZE_UV                 0x44
#घोषणा QSEED3_DST_SIZE                    0x48
#घोषणा QSEED3_COEF_LUT_CTRL               0x4C
#घोषणा QSEED3_COEF_LUT_SWAP_BIT           0
#घोषणा QSEED3_COEF_LUT_सूची_BIT            1
#घोषणा QSEED3_COEF_LUT_Y_CIR_BIT          2
#घोषणा QSEED3_COEF_LUT_UV_CIR_BIT         3
#घोषणा QSEED3_COEF_LUT_Y_SEP_BIT          4
#घोषणा QSEED3_COEF_LUT_UV_SEP_BIT         5
#घोषणा QSEED3_BUFFER_CTRL                 0x50
#घोषणा QSEED3_CLK_CTRL0                   0x54
#घोषणा QSEED3_CLK_CTRL1                   0x58
#घोषणा QSEED3_CLK_STATUS                  0x5C
#घोषणा QSEED3_PHASE_INIT_Y_H              0x90
#घोषणा QSEED3_PHASE_INIT_Y_V              0x94
#घोषणा QSEED3_PHASE_INIT_UV_H             0x98
#घोषणा QSEED3_PHASE_INIT_UV_V             0x9C
#घोषणा QSEED3_COEF_LUT                    0x100
#घोषणा QSEED3_FILTERS                     5
#घोषणा QSEED3_LUT_REGIONS                 4
#घोषणा QSEED3_CIRCULAR_LUTS               9
#घोषणा QSEED3_SEPARABLE_LUTS              10
#घोषणा QSEED3_LUT_SIZE                    60
#घोषणा QSEED3_ENABLE                      2
#घोषणा QSEED3_सूची_LUT_SIZE                (200 * माप(u32))
#घोषणा QSEED3_CIR_LUT_SIZE \
	(QSEED3_LUT_SIZE * QSEED3_CIRCULAR_LUTS * माप(u32))
#घोषणा QSEED3_SEP_LUT_SIZE \
	(QSEED3_LUT_SIZE * QSEED3_SEPARABLE_LUTS * माप(u32))

/* DPU_SCALER_QSEED3LITE */
#घोषणा QSEED3LITE_COEF_LUT_Y_SEP_BIT         4
#घोषणा QSEED3LITE_COEF_LUT_UV_SEP_BIT        5
#घोषणा QSEED3LITE_COEF_LUT_CTRL              0x4C
#घोषणा QSEED3LITE_COEF_LUT_SWAP_BIT          0
#घोषणा QSEED3LITE_सूची_FILTER_WEIGHT          0x60
#घोषणा QSEED3LITE_FILTERS                 2
#घोषणा QSEED3LITE_SEPARABLE_LUTS             10
#घोषणा QSEED3LITE_LUT_SIZE                   33
#घोषणा QSEED3LITE_SEP_LUT_SIZE \
	        (QSEED3LITE_LUT_SIZE * QSEED3LITE_SEPARABLE_LUTS * माप(u32))


व्योम dpu_reg_ग_लिखो(काष्ठा dpu_hw_blk_reg_map *c,
		u32 reg_off,
		u32 val,
		स्थिर अक्षर *name)
अणु
	/* करोn't need to mutex protect this */
	अगर (c->log_mask & dpu_hw_util_log_mask)
		DPU_DEBUG_DRIVER("[%s:0x%X] <= 0x%X\n",
				name, c->blk_off + reg_off, val);
	ग_लिखोl_relaxed(val, c->base_off + c->blk_off + reg_off);
पूर्ण

पूर्णांक dpu_reg_पढ़ो(काष्ठा dpu_hw_blk_reg_map *c, u32 reg_off)
अणु
	वापस पढ़ोl_relaxed(c->base_off + c->blk_off + reg_off);
पूर्ण

u32 *dpu_hw_util_get_log_mask_ptr(व्योम)
अणु
	वापस &dpu_hw_util_log_mask;
पूर्ण

अटल व्योम _dpu_hw_setup_scaler3_lut(काष्ठा dpu_hw_blk_reg_map *c,
		काष्ठा dpu_hw_scaler3_cfg *scaler3_cfg, u32 offset)
अणु
	पूर्णांक i, j, filter;
	पूर्णांक config_lut = 0x0;
	अचिन्हित दीर्घ lut_flags;
	u32 lut_addr, lut_offset, lut_len;
	u32 *lut[QSEED3_FILTERS] = अणुशून्य, शून्य, शून्य, शून्य, शून्यपूर्ण;
	अटल स्थिर uपूर्णांक32_t off_tbl[QSEED3_FILTERS][QSEED3_LUT_REGIONS][2] = अणु
		अणुअणु18, 0x000पूर्ण, अणु12, 0x120पूर्ण, अणु12, 0x1E0पूर्ण, अणु8, 0x2A0पूर्ण पूर्ण,
		अणुअणु6, 0x320पूर्ण, अणु3, 0x3E0पूर्ण, अणु3, 0x440पूर्ण, अणु3, 0x4A0पूर्ण पूर्ण,
		अणुअणु6, 0x500पूर्ण, अणु3, 0x5c0पूर्ण, अणु3, 0x620पूर्ण, अणु3, 0x680पूर्ण पूर्ण,
		अणुअणु6, 0x380पूर्ण, अणु3, 0x410पूर्ण, अणु3, 0x470पूर्ण, अणु3, 0x4d0पूर्ण पूर्ण,
		अणुअणु6, 0x560पूर्ण, अणु3, 0x5f0पूर्ण, अणु3, 0x650पूर्ण, अणु3, 0x6b0पूर्ण पूर्ण,
	पूर्ण;

	lut_flags = (अचिन्हित दीर्घ) scaler3_cfg->lut_flag;
	अगर (test_bit(QSEED3_COEF_LUT_सूची_BIT, &lut_flags) &&
		(scaler3_cfg->dir_len == QSEED3_सूची_LUT_SIZE)) अणु
		lut[0] = scaler3_cfg->dir_lut;
		config_lut = 1;
	पूर्ण
	अगर (test_bit(QSEED3_COEF_LUT_Y_CIR_BIT, &lut_flags) &&
		(scaler3_cfg->y_rgb_cir_lut_idx < QSEED3_CIRCULAR_LUTS) &&
		(scaler3_cfg->cir_len == QSEED3_CIR_LUT_SIZE)) अणु
		lut[1] = scaler3_cfg->cir_lut +
			scaler3_cfg->y_rgb_cir_lut_idx * QSEED3_LUT_SIZE;
		config_lut = 1;
	पूर्ण
	अगर (test_bit(QSEED3_COEF_LUT_UV_CIR_BIT, &lut_flags) &&
		(scaler3_cfg->uv_cir_lut_idx < QSEED3_CIRCULAR_LUTS) &&
		(scaler3_cfg->cir_len == QSEED3_CIR_LUT_SIZE)) अणु
		lut[2] = scaler3_cfg->cir_lut +
			scaler3_cfg->uv_cir_lut_idx * QSEED3_LUT_SIZE;
		config_lut = 1;
	पूर्ण
	अगर (test_bit(QSEED3_COEF_LUT_Y_SEP_BIT, &lut_flags) &&
		(scaler3_cfg->y_rgb_sep_lut_idx < QSEED3_SEPARABLE_LUTS) &&
		(scaler3_cfg->sep_len == QSEED3_SEP_LUT_SIZE)) अणु
		lut[3] = scaler3_cfg->sep_lut +
			scaler3_cfg->y_rgb_sep_lut_idx * QSEED3_LUT_SIZE;
		config_lut = 1;
	पूर्ण
	अगर (test_bit(QSEED3_COEF_LUT_UV_SEP_BIT, &lut_flags) &&
		(scaler3_cfg->uv_sep_lut_idx < QSEED3_SEPARABLE_LUTS) &&
		(scaler3_cfg->sep_len == QSEED3_SEP_LUT_SIZE)) अणु
		lut[4] = scaler3_cfg->sep_lut +
			scaler3_cfg->uv_sep_lut_idx * QSEED3_LUT_SIZE;
		config_lut = 1;
	पूर्ण

	अगर (config_lut) अणु
		क्रम (filter = 0; filter < QSEED3_FILTERS; filter++) अणु
			अगर (!lut[filter])
				जारी;
			lut_offset = 0;
			क्रम (i = 0; i < QSEED3_LUT_REGIONS; i++) अणु
				lut_addr = QSEED3_COEF_LUT + offset
					+ off_tbl[filter][i][1];
				lut_len = off_tbl[filter][i][0] << 2;
				क्रम (j = 0; j < lut_len; j++) अणु
					DPU_REG_WRITE(c,
						lut_addr,
						(lut[filter])[lut_offset++]);
					lut_addr += 4;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (test_bit(QSEED3_COEF_LUT_SWAP_BIT, &lut_flags))
		DPU_REG_WRITE(c, QSEED3_COEF_LUT_CTRL + offset, BIT(0));

पूर्ण

अटल व्योम _dpu_hw_setup_scaler3lite_lut(काष्ठा dpu_hw_blk_reg_map *c,
		काष्ठा dpu_hw_scaler3_cfg *scaler3_cfg, u32 offset)
अणु
	पूर्णांक j, filter;
	पूर्णांक config_lut = 0x0;
	अचिन्हित दीर्घ lut_flags;
	u32 lut_addr, lut_offset;
	u32 *lut[QSEED3LITE_FILTERS] = अणुशून्य, शून्यपूर्ण;
	अटल स्थिर uपूर्णांक32_t off_tbl[QSEED3_FILTERS] = अणु 0x000, 0x200 पूर्ण;

	DPU_REG_WRITE(c, QSEED3LITE_सूची_FILTER_WEIGHT + offset, scaler3_cfg->dir_weight);

	अगर (!scaler3_cfg->sep_lut)
		वापस;

	lut_flags = (अचिन्हित दीर्घ) scaler3_cfg->lut_flag;
	अगर (test_bit(QSEED3_COEF_LUT_Y_SEP_BIT, &lut_flags) &&
		(scaler3_cfg->y_rgb_sep_lut_idx < QSEED3LITE_SEPARABLE_LUTS) &&
		(scaler3_cfg->sep_len == QSEED3LITE_SEP_LUT_SIZE)) अणु
		lut[0] = scaler3_cfg->sep_lut +
			scaler3_cfg->y_rgb_sep_lut_idx * QSEED3LITE_LUT_SIZE;
		config_lut = 1;
	पूर्ण
	अगर (test_bit(QSEED3_COEF_LUT_UV_SEP_BIT, &lut_flags) &&
		(scaler3_cfg->uv_sep_lut_idx < QSEED3LITE_SEPARABLE_LUTS) &&
		(scaler3_cfg->sep_len == QSEED3LITE_SEP_LUT_SIZE)) अणु
		lut[1] = scaler3_cfg->sep_lut +
			scaler3_cfg->uv_sep_lut_idx * QSEED3LITE_LUT_SIZE;
		config_lut = 1;
	पूर्ण

	अगर (config_lut) अणु
		क्रम (filter = 0; filter < QSEED3LITE_FILTERS; filter++) अणु
			अगर (!lut[filter])
				जारी;
			lut_offset = 0;
			lut_addr = QSEED3_COEF_LUT + offset + off_tbl[filter];
			क्रम (j = 0; j < QSEED3LITE_LUT_SIZE; j++) अणु
				DPU_REG_WRITE(c,
					lut_addr,
					(lut[filter])[lut_offset++]);
				lut_addr += 4;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (test_bit(QSEED3_COEF_LUT_SWAP_BIT, &lut_flags))
		DPU_REG_WRITE(c, QSEED3_COEF_LUT_CTRL + offset, BIT(0));

पूर्ण

अटल व्योम _dpu_hw_setup_scaler3_de(काष्ठा dpu_hw_blk_reg_map *c,
		काष्ठा dpu_hw_scaler3_de_cfg *de_cfg, u32 offset)
अणु
	u32 sharp_lvl, sharp_ctl, shape_ctl, de_thr;
	u32 adjust_a, adjust_b, adjust_c;

	अगर (!de_cfg->enable)
		वापस;

	sharp_lvl = (de_cfg->sharpen_level1 & 0x1FF) |
		((de_cfg->sharpen_level2 & 0x1FF) << 16);

	sharp_ctl = ((de_cfg->limit & 0xF) << 9) |
		((de_cfg->prec_shअगरt & 0x7) << 13) |
		((de_cfg->clip & 0x7) << 16);

	shape_ctl = (de_cfg->thr_quiet & 0xFF) |
		((de_cfg->thr_dieout & 0x3FF) << 16);

	de_thr = (de_cfg->thr_low & 0x3FF) |
		((de_cfg->thr_high & 0x3FF) << 16);

	adjust_a = (de_cfg->adjust_a[0] & 0x3FF) |
		((de_cfg->adjust_a[1] & 0x3FF) << 10) |
		((de_cfg->adjust_a[2] & 0x3FF) << 20);

	adjust_b = (de_cfg->adjust_b[0] & 0x3FF) |
		((de_cfg->adjust_b[1] & 0x3FF) << 10) |
		((de_cfg->adjust_b[2] & 0x3FF) << 20);

	adjust_c = (de_cfg->adjust_c[0] & 0x3FF) |
		((de_cfg->adjust_c[1] & 0x3FF) << 10) |
		((de_cfg->adjust_c[2] & 0x3FF) << 20);

	DPU_REG_WRITE(c, QSEED3_DE_SHARPEN + offset, sharp_lvl);
	DPU_REG_WRITE(c, QSEED3_DE_SHARPEN_CTL + offset, sharp_ctl);
	DPU_REG_WRITE(c, QSEED3_DE_SHAPE_CTL + offset, shape_ctl);
	DPU_REG_WRITE(c, QSEED3_DE_THRESHOLD + offset, de_thr);
	DPU_REG_WRITE(c, QSEED3_DE_ADJUST_DATA_0 + offset, adjust_a);
	DPU_REG_WRITE(c, QSEED3_DE_ADJUST_DATA_1 + offset, adjust_b);
	DPU_REG_WRITE(c, QSEED3_DE_ADJUST_DATA_2 + offset, adjust_c);

पूर्ण

व्योम dpu_hw_setup_scaler3(काष्ठा dpu_hw_blk_reg_map *c,
		काष्ठा dpu_hw_scaler3_cfg *scaler3_cfg,
		u32 scaler_offset, u32 scaler_version,
		स्थिर काष्ठा dpu_क्रमmat *क्रमmat)
अणु
	u32 op_mode = 0;
	u32 phase_init, preload, src_y_rgb, src_uv, dst;

	अगर (!scaler3_cfg->enable)
		जाओ end;

	op_mode |= BIT(0);
	op_mode |= (scaler3_cfg->y_rgb_filter_cfg & 0x3) << 16;

	अगर (क्रमmat && DPU_FORMAT_IS_YUV(क्रमmat)) अणु
		op_mode |= BIT(12);
		op_mode |= (scaler3_cfg->uv_filter_cfg & 0x3) << 24;
	पूर्ण

	op_mode |= (scaler3_cfg->blend_cfg & 1) << 31;
	op_mode |= (scaler3_cfg->dir_en) ? BIT(4) : 0;

	preload =
		((scaler3_cfg->preload_x[0] & 0x7F) << 0) |
		((scaler3_cfg->preload_y[0] & 0x7F) << 8) |
		((scaler3_cfg->preload_x[1] & 0x7F) << 16) |
		((scaler3_cfg->preload_y[1] & 0x7F) << 24);

	src_y_rgb = (scaler3_cfg->src_width[0] & 0x1FFFF) |
		((scaler3_cfg->src_height[0] & 0x1FFFF) << 16);

	src_uv = (scaler3_cfg->src_width[1] & 0x1FFFF) |
		((scaler3_cfg->src_height[1] & 0x1FFFF) << 16);

	dst = (scaler3_cfg->dst_width & 0x1FFFF) |
		((scaler3_cfg->dst_height & 0x1FFFF) << 16);

	अगर (scaler3_cfg->de.enable) अणु
		_dpu_hw_setup_scaler3_de(c, &scaler3_cfg->de, scaler_offset);
		op_mode |= BIT(8);
	पूर्ण

	अगर (scaler3_cfg->lut_flag) अणु
		अगर (scaler_version < 0x2004)
			_dpu_hw_setup_scaler3_lut(c, scaler3_cfg, scaler_offset);
		अन्यथा
			_dpu_hw_setup_scaler3lite_lut(c, scaler3_cfg, scaler_offset);
	पूर्ण

	अगर (scaler_version == 0x1002) अणु
		phase_init =
			((scaler3_cfg->init_phase_x[0] & 0x3F) << 0) |
			((scaler3_cfg->init_phase_y[0] & 0x3F) << 8) |
			((scaler3_cfg->init_phase_x[1] & 0x3F) << 16) |
			((scaler3_cfg->init_phase_y[1] & 0x3F) << 24);
		DPU_REG_WRITE(c, QSEED3_PHASE_INIT + scaler_offset, phase_init);
	पूर्ण अन्यथा अणु
		DPU_REG_WRITE(c, QSEED3_PHASE_INIT_Y_H + scaler_offset,
			scaler3_cfg->init_phase_x[0] & 0x1FFFFF);
		DPU_REG_WRITE(c, QSEED3_PHASE_INIT_Y_V + scaler_offset,
			scaler3_cfg->init_phase_y[0] & 0x1FFFFF);
		DPU_REG_WRITE(c, QSEED3_PHASE_INIT_UV_H + scaler_offset,
			scaler3_cfg->init_phase_x[1] & 0x1FFFFF);
		DPU_REG_WRITE(c, QSEED3_PHASE_INIT_UV_V + scaler_offset,
			scaler3_cfg->init_phase_y[1] & 0x1FFFFF);
	पूर्ण

	DPU_REG_WRITE(c, QSEED3_PHASE_STEP_Y_H + scaler_offset,
		scaler3_cfg->phase_step_x[0] & 0xFFFFFF);

	DPU_REG_WRITE(c, QSEED3_PHASE_STEP_Y_V + scaler_offset,
		scaler3_cfg->phase_step_y[0] & 0xFFFFFF);

	DPU_REG_WRITE(c, QSEED3_PHASE_STEP_UV_H + scaler_offset,
		scaler3_cfg->phase_step_x[1] & 0xFFFFFF);

	DPU_REG_WRITE(c, QSEED3_PHASE_STEP_UV_V + scaler_offset,
		scaler3_cfg->phase_step_y[1] & 0xFFFFFF);

	DPU_REG_WRITE(c, QSEED3_PRELOAD + scaler_offset, preload);

	DPU_REG_WRITE(c, QSEED3_SRC_SIZE_Y_RGB_A + scaler_offset, src_y_rgb);

	DPU_REG_WRITE(c, QSEED3_SRC_SIZE_UV + scaler_offset, src_uv);

	DPU_REG_WRITE(c, QSEED3_DST_SIZE + scaler_offset, dst);

end:
	अगर (क्रमmat && !DPU_FORMAT_IS_DX(क्रमmat))
		op_mode |= BIT(14);

	अगर (क्रमmat && क्रमmat->alpha_enable) अणु
		op_mode |= BIT(10);
		अगर (scaler_version == 0x1002)
			op_mode |= (scaler3_cfg->alpha_filter_cfg & 0x1) << 30;
		अन्यथा
			op_mode |= (scaler3_cfg->alpha_filter_cfg & 0x3) << 29;
	पूर्ण

	DPU_REG_WRITE(c, QSEED3_OP_MODE + scaler_offset, op_mode);
पूर्ण

u32 dpu_hw_get_scaler3_ver(काष्ठा dpu_hw_blk_reg_map *c,
			u32 scaler_offset)
अणु
	वापस DPU_REG_READ(c, QSEED3_HW_VERSION + scaler_offset);
पूर्ण

व्योम dpu_hw_csc_setup(काष्ठा dpu_hw_blk_reg_map *c,
		u32 csc_reg_off,
		काष्ठा dpu_csc_cfg *data, bool csc10)
अणु
	अटल स्थिर u32 matrix_shअगरt = 7;
	u32 clamp_shअगरt = csc10 ? 16 : 8;
	u32 val;

	/* matrix coeff - convert S15.16 to S4.9 */
	val = ((data->csc_mv[0] >> matrix_shअगरt) & 0x1FFF) |
		(((data->csc_mv[1] >> matrix_shअगरt) & 0x1FFF) << 16);
	DPU_REG_WRITE(c, csc_reg_off, val);
	val = ((data->csc_mv[2] >> matrix_shअगरt) & 0x1FFF) |
		(((data->csc_mv[3] >> matrix_shअगरt) & 0x1FFF) << 16);
	DPU_REG_WRITE(c, csc_reg_off + 0x4, val);
	val = ((data->csc_mv[4] >> matrix_shअगरt) & 0x1FFF) |
		(((data->csc_mv[5] >> matrix_shअगरt) & 0x1FFF) << 16);
	DPU_REG_WRITE(c, csc_reg_off + 0x8, val);
	val = ((data->csc_mv[6] >> matrix_shअगरt) & 0x1FFF) |
		(((data->csc_mv[7] >> matrix_shअगरt) & 0x1FFF) << 16);
	DPU_REG_WRITE(c, csc_reg_off + 0xc, val);
	val = (data->csc_mv[8] >> matrix_shअगरt) & 0x1FFF;
	DPU_REG_WRITE(c, csc_reg_off + 0x10, val);

	/* Pre clamp */
	val = (data->csc_pre_lv[0] << clamp_shअगरt) | data->csc_pre_lv[1];
	DPU_REG_WRITE(c, csc_reg_off + 0x14, val);
	val = (data->csc_pre_lv[2] << clamp_shअगरt) | data->csc_pre_lv[3];
	DPU_REG_WRITE(c, csc_reg_off + 0x18, val);
	val = (data->csc_pre_lv[4] << clamp_shअगरt) | data->csc_pre_lv[5];
	DPU_REG_WRITE(c, csc_reg_off + 0x1c, val);

	/* Post clamp */
	val = (data->csc_post_lv[0] << clamp_shअगरt) | data->csc_post_lv[1];
	DPU_REG_WRITE(c, csc_reg_off + 0x20, val);
	val = (data->csc_post_lv[2] << clamp_shअगरt) | data->csc_post_lv[3];
	DPU_REG_WRITE(c, csc_reg_off + 0x24, val);
	val = (data->csc_post_lv[4] << clamp_shअगरt) | data->csc_post_lv[5];
	DPU_REG_WRITE(c, csc_reg_off + 0x28, val);

	/* Pre-Bias */
	DPU_REG_WRITE(c, csc_reg_off + 0x2c, data->csc_pre_bv[0]);
	DPU_REG_WRITE(c, csc_reg_off + 0x30, data->csc_pre_bv[1]);
	DPU_REG_WRITE(c, csc_reg_off + 0x34, data->csc_pre_bv[2]);

	/* Post-Bias */
	DPU_REG_WRITE(c, csc_reg_off + 0x38, data->csc_post_bv[0]);
	DPU_REG_WRITE(c, csc_reg_off + 0x3c, data->csc_post_bv[1]);
	DPU_REG_WRITE(c, csc_reg_off + 0x40, data->csc_post_bv[2]);
पूर्ण
