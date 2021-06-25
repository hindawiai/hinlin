<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Copyright (c) 2015-2018, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _DPU_HW_UTIL_H
#घोषणा _DPU_HW_UTIL_H

#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश "dpu_hw_mdss.h"

#घोषणा REG_MASK(n)                     ((BIT(n)) - 1)

/*
 * This is the common काष्ठा मुख्यtained by each sub block
 * क्रम mapping the रेजिस्टर offsets in this block to the
 * असलoulute IO address
 * @base_off:     mdp रेजिस्टर mapped offset
 * @blk_off:      pipe offset relative to mdss offset
 * @length        length of रेजिस्टर block offset
 * @xin_id        xin id
 * @hwversion     mdss hw version number
 */
काष्ठा dpu_hw_blk_reg_map अणु
	व्योम __iomem *base_off;
	u32 blk_off;
	u32 length;
	u32 xin_id;
	u32 hwversion;
	u32 log_mask;
पूर्ण;

/**
 * काष्ठा dpu_hw_scaler3_de_cfg : QSEEDv3 detail enhancer configuration
 * @enable:         detail enhancer enable/disable
 * @sharpen_level1: sharpening strength क्रम noise
 * @sharpen_level2: sharpening strength क्रम संकेत
 * @ clip:          clip shअगरt
 * @ limit:         limit value
 * @ thr_quiet:     quiet threshold
 * @ thr_dieout:    dieout threshold
 * @ thr_high:      low threshold
 * @ thr_high:      high threshold
 * @ prec_shअगरt:    precision shअगरt
 * @ adjust_a:      A-coefficients क्रम mapping curve
 * @ adjust_b:      B-coefficients क्रम mapping curve
 * @ adjust_c:      C-coefficients क्रम mapping curve
 */
काष्ठा dpu_hw_scaler3_de_cfg अणु
	u32 enable;
	पूर्णांक16_t sharpen_level1;
	पूर्णांक16_t sharpen_level2;
	uपूर्णांक16_t clip;
	uपूर्णांक16_t limit;
	uपूर्णांक16_t thr_quiet;
	uपूर्णांक16_t thr_dieout;
	uपूर्णांक16_t thr_low;
	uपूर्णांक16_t thr_high;
	uपूर्णांक16_t prec_shअगरt;
	पूर्णांक16_t adjust_a[DPU_MAX_DE_CURVES];
	पूर्णांक16_t adjust_b[DPU_MAX_DE_CURVES];
	पूर्णांक16_t adjust_c[DPU_MAX_DE_CURVES];
पूर्ण;


/**
 * काष्ठा dpu_hw_scaler3_cfg : QSEEDv3 configuration
 * @enable:        scaler enable
 * @dir_en:        direction detection block enable
 * @ init_phase_x: horizontal initial phase
 * @ phase_step_x: horizontal phase step
 * @ init_phase_y: vertical initial phase
 * @ phase_step_y: vertical phase step
 * @ preload_x:    horizontal preload value
 * @ preload_y:    vertical preload value
 * @ src_width:    source width
 * @ src_height:   source height
 * @ dst_width:    destination width
 * @ dst_height:   destination height
 * @ y_rgb_filter_cfg: y/rgb plane filter configuration
 * @ uv_filter_cfg: uv plane filter configuration
 * @ alpha_filter_cfg: alpha filter configuration
 * @ blend_cfg:    blend coefficients configuration
 * @ lut_flag:     scaler LUT update flags
 *                 0x1 swap LUT bank
 *                 0x2 update 2D filter LUT
 *                 0x4 update y circular filter LUT
 *                 0x8 update uv circular filter LUT
 *                 0x10 update y separable filter LUT
 *                 0x20 update uv separable filter LUT
 * @ dir_lut_idx:  2D filter LUT index
 * @ y_rgb_cir_lut_idx: y circular filter LUT index
 * @ uv_cir_lut_idx: uv circular filter LUT index
 * @ y_rgb_sep_lut_idx: y circular filter LUT index
 * @ uv_sep_lut_idx: uv separable filter LUT index
 * @ dir_lut:      poपूर्णांकer to 2D LUT
 * @ cir_lut:      poपूर्णांकer to circular filter LUT
 * @ sep_lut:      poपूर्णांकer to separable filter LUT
 * @ de: detail enhancer configuration
 * @ dir_weight:   Directional weight
 */
काष्ठा dpu_hw_scaler3_cfg अणु
	u32 enable;
	u32 dir_en;
	पूर्णांक32_t init_phase_x[DPU_MAX_PLANES];
	पूर्णांक32_t phase_step_x[DPU_MAX_PLANES];
	पूर्णांक32_t init_phase_y[DPU_MAX_PLANES];
	पूर्णांक32_t phase_step_y[DPU_MAX_PLANES];

	u32 preload_x[DPU_MAX_PLANES];
	u32 preload_y[DPU_MAX_PLANES];
	u32 src_width[DPU_MAX_PLANES];
	u32 src_height[DPU_MAX_PLANES];

	u32 dst_width;
	u32 dst_height;

	u32 y_rgb_filter_cfg;
	u32 uv_filter_cfg;
	u32 alpha_filter_cfg;
	u32 blend_cfg;

	u32 lut_flag;
	u32 dir_lut_idx;

	u32 y_rgb_cir_lut_idx;
	u32 uv_cir_lut_idx;
	u32 y_rgb_sep_lut_idx;
	u32 uv_sep_lut_idx;
	u32 *dir_lut;
	माप_प्रकार dir_len;
	u32 *cir_lut;
	माप_प्रकार cir_len;
	u32 *sep_lut;
	माप_प्रकार sep_len;

	/*
	 * Detail enhancer settings
	 */
	काष्ठा dpu_hw_scaler3_de_cfg de;

	u32 dir_weight;
पूर्ण;

/**
 * काष्ठा dpu_drm_pix_ext_v1 - version 1 of pixel ext काष्ठाure
 * @num_ext_pxls_lr: Number of total horizontal pixels
 * @num_ext_pxls_tb: Number of total vertical lines
 * @left_ftch:       Number of extra pixels to overfetch from left
 * @right_ftch:      Number of extra pixels to overfetch from right
 * @top_ftch:        Number of extra lines to overfetch from top
 * @bपंचांग_ftch:        Number of extra lines to overfetch from bottom
 * @left_rpt:        Number of extra pixels to repeat from left
 * @right_rpt:       Number of extra pixels to repeat from right
 * @top_rpt:         Number of extra lines to repeat from top
 * @bपंचांग_rpt:         Number of extra lines to repeat from bottom
 */
काष्ठा dpu_drm_pix_ext_v1 अणु
	/*
	 * Number of pixels ext in left, right, top and bottom direction
	 * क्रम all color components.
	 */
	पूर्णांक32_t num_ext_pxls_lr[DPU_MAX_PLANES];
	पूर्णांक32_t num_ext_pxls_tb[DPU_MAX_PLANES];

	/*
	 * Number of pixels needs to be overfetched in left, right, top
	 * and bottom directions from source image क्रम scaling.
	 */
	पूर्णांक32_t left_ftch[DPU_MAX_PLANES];
	पूर्णांक32_t right_ftch[DPU_MAX_PLANES];
	पूर्णांक32_t top_ftch[DPU_MAX_PLANES];
	पूर्णांक32_t bपंचांग_ftch[DPU_MAX_PLANES];
	/*
	 * Number of pixels needs to be repeated in left, right, top and
	 * bottom directions क्रम scaling.
	 */
	पूर्णांक32_t left_rpt[DPU_MAX_PLANES];
	पूर्णांक32_t right_rpt[DPU_MAX_PLANES];
	पूर्णांक32_t top_rpt[DPU_MAX_PLANES];
	पूर्णांक32_t bपंचांग_rpt[DPU_MAX_PLANES];

पूर्ण;

/**
 * काष्ठा dpu_drm_de_v1 - version 1 of detail enhancer काष्ठाure
 * @enable:         Enables/disables detail enhancer
 * @sharpen_level1: Sharpening strength क्रम noise
 * @sharpen_level2: Sharpening strength क्रम context
 * @clip:           Clip coefficient
 * @limit:          Detail enhancer limit factor
 * @thr_quiet:      Quite zone threshold
 * @thr_dieout:     Die-out zone threshold
 * @thr_low:        Linear zone left threshold
 * @thr_high:       Linear zone right threshold
 * @prec_shअगरt:     Detail enhancer precision
 * @adjust_a:       Mapping curves A coefficients
 * @adjust_b:       Mapping curves B coefficients
 * @adjust_c:       Mapping curves C coefficients
 */
काष्ठा dpu_drm_de_v1 अणु
	uपूर्णांक32_t enable;
	पूर्णांक16_t sharpen_level1;
	पूर्णांक16_t sharpen_level2;
	uपूर्णांक16_t clip;
	uपूर्णांक16_t limit;
	uपूर्णांक16_t thr_quiet;
	uपूर्णांक16_t thr_dieout;
	uपूर्णांक16_t thr_low;
	uपूर्णांक16_t thr_high;
	uपूर्णांक16_t prec_shअगरt;
	पूर्णांक16_t adjust_a[DPU_MAX_DE_CURVES];
	पूर्णांक16_t adjust_b[DPU_MAX_DE_CURVES];
	पूर्णांक16_t adjust_c[DPU_MAX_DE_CURVES];
पूर्ण;

/**
 * काष्ठा dpu_drm_scaler_v2 - version 2 of काष्ठा dpu_drm_scaler
 * @enable:            Scaler enable
 * @dir_en:            Detail enhancer enable
 * @pe:                Pixel extension settings
 * @horz_decimate:     Horizontal decimation factor
 * @vert_decimate:     Vertical decimation factor
 * @init_phase_x:      Initial scaler phase values क्रम x
 * @phase_step_x:      Phase step values क्रम x
 * @init_phase_y:      Initial scaler phase values क्रम y
 * @phase_step_y:      Phase step values क्रम y
 * @preload_x:         Horizontal preload value
 * @preload_y:         Vertical preload value
 * @src_width:         Source width
 * @src_height:        Source height
 * @dst_width:         Destination width
 * @dst_height:        Destination height
 * @y_rgb_filter_cfg:  Y/RGB plane filter configuration
 * @uv_filter_cfg:     UV plane filter configuration
 * @alpha_filter_cfg:  Alpha filter configuration
 * @blend_cfg:         Selection of blend coefficients
 * @lut_flag:          LUT configuration flags
 * @dir_lut_idx:       2d 4x4 LUT index
 * @y_rgb_cir_lut_idx: Y/RGB circular LUT index
 * @uv_cir_lut_idx:    UV circular LUT index
 * @y_rgb_sep_lut_idx: Y/RGB separable LUT index
 * @uv_sep_lut_idx:    UV separable LUT index
 * @de:                Detail enhancer settings
 */
काष्ठा dpu_drm_scaler_v2 अणु
	/*
	 * General definitions
	 */
	uपूर्णांक32_t enable;
	uपूर्णांक32_t dir_en;

	/*
	 * Pix ext settings
	 */
	काष्ठा dpu_drm_pix_ext_v1 pe;

	/*
	 * Decimation settings
	 */
	uपूर्णांक32_t horz_decimate;
	uपूर्णांक32_t vert_decimate;

	/*
	 * Phase settings
	 */
	पूर्णांक32_t init_phase_x[DPU_MAX_PLANES];
	पूर्णांक32_t phase_step_x[DPU_MAX_PLANES];
	पूर्णांक32_t init_phase_y[DPU_MAX_PLANES];
	पूर्णांक32_t phase_step_y[DPU_MAX_PLANES];

	uपूर्णांक32_t preload_x[DPU_MAX_PLANES];
	uपूर्णांक32_t preload_y[DPU_MAX_PLANES];
	uपूर्णांक32_t src_width[DPU_MAX_PLANES];
	uपूर्णांक32_t src_height[DPU_MAX_PLANES];

	uपूर्णांक32_t dst_width;
	uपूर्णांक32_t dst_height;

	uपूर्णांक32_t y_rgb_filter_cfg;
	uपूर्णांक32_t uv_filter_cfg;
	uपूर्णांक32_t alpha_filter_cfg;
	uपूर्णांक32_t blend_cfg;

	uपूर्णांक32_t lut_flag;
	uपूर्णांक32_t dir_lut_idx;

	/* क्रम Y(RGB) and UV planes*/
	uपूर्णांक32_t y_rgb_cir_lut_idx;
	uपूर्णांक32_t uv_cir_lut_idx;
	uपूर्णांक32_t y_rgb_sep_lut_idx;
	uपूर्णांक32_t uv_sep_lut_idx;

	/*
	 * Detail enhancer settings
	 */
	काष्ठा dpu_drm_de_v1 de;
पूर्ण;


u32 *dpu_hw_util_get_log_mask_ptr(व्योम);

व्योम dpu_reg_ग_लिखो(काष्ठा dpu_hw_blk_reg_map *c,
		u32 reg_off,
		u32 val,
		स्थिर अक्षर *name);
पूर्णांक dpu_reg_पढ़ो(काष्ठा dpu_hw_blk_reg_map *c, u32 reg_off);

#घोषणा DPU_REG_WRITE(c, off, val) dpu_reg_ग_लिखो(c, off, val, #off)
#घोषणा DPU_REG_READ(c, off) dpu_reg_पढ़ो(c, off)

व्योम *dpu_hw_util_get_dir(व्योम);

व्योम dpu_hw_setup_scaler3(काष्ठा dpu_hw_blk_reg_map *c,
		काष्ठा dpu_hw_scaler3_cfg *scaler3_cfg,
		u32 scaler_offset, u32 scaler_version,
		स्थिर काष्ठा dpu_क्रमmat *क्रमmat);

u32 dpu_hw_get_scaler3_ver(काष्ठा dpu_hw_blk_reg_map *c,
		u32 scaler_offset);

व्योम dpu_hw_csc_setup(काष्ठा dpu_hw_blk_reg_map  *c,
		u32 csc_reg_off,
		काष्ठा dpu_csc_cfg *data, bool csc10);

#पूर्ण_अगर /* _DPU_HW_UTIL_H */
