<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2018 Intel Corporation
 *
 * Author: Gaurav K Singh <gaurav.k.singh@पूर्णांकel.com>
 *         Manasi Navare <manasi.d.navare@पूर्णांकel.com>
 */

#समावेश "i915_drv.h"
#समावेश "intel_display_types.h"
#समावेश "intel_dsi.h"
#समावेश "intel_vdsc.h"

क्रमागत ROW_INDEX_BPP अणु
	ROW_INDEX_6BPP = 0,
	ROW_INDEX_8BPP,
	ROW_INDEX_10BPP,
	ROW_INDEX_12BPP,
	ROW_INDEX_15BPP,
	MAX_ROW_INDEX
पूर्ण;

क्रमागत COLUMN_INDEX_BPC अणु
	COLUMN_INDEX_8BPC = 0,
	COLUMN_INDEX_10BPC,
	COLUMN_INDEX_12BPC,
	COLUMN_INDEX_14BPC,
	COLUMN_INDEX_16BPC,
	MAX_COLUMN_INDEX
पूर्ण;

/* From DSC_v1.11 spec, rc_parameter_Set syntax element typically स्थिरant */
अटल स्थिर u16 rc_buf_thresh[] = अणु
	896, 1792, 2688, 3584, 4480, 5376, 6272, 6720, 7168, 7616,
	7744, 7872, 8000, 8064
पूर्ण;

काष्ठा rc_parameters अणु
	u16 initial_xmit_delay;
	u8 first_line_bpg_offset;
	u16 initial_offset;
	u8 flatness_min_qp;
	u8 flatness_max_qp;
	u8 rc_quant_incr_limit0;
	u8 rc_quant_incr_limit1;
	काष्ठा drm_dsc_rc_range_parameters rc_range_params[DSC_NUM_BUF_RANGES];
पूर्ण;

/*
 * Selected Rate Control Related Parameter Recommended Values
 * from DSC_v1.11 spec & C Model release: DSC_model_20161212
 */
अटल स्थिर काष्ठा rc_parameters rc_parameters[][MAX_COLUMN_INDEX] = अणु
अणु
	/* 6BPP/8BPC */
	अणु 768, 15, 6144, 3, 13, 11, 11, अणु
		अणु 0, 4, 0 पूर्ण, अणु 1, 6, -2 पूर्ण, अणु 3, 8, -2 पूर्ण, अणु 4, 8, -4 पूर्ण,
		अणु 5, 9, -6 पूर्ण, अणु 5, 9, -6 पूर्ण, अणु 6, 9, -6 पूर्ण, अणु 6, 10, -8 पूर्ण,
		अणु 7, 11, -8 पूर्ण, अणु 8, 12, -10 पूर्ण, अणु 9, 12, -10 पूर्ण, अणु 10, 12, -12 पूर्ण,
		अणु 10, 12, -12 पूर्ण, अणु 11, 12, -12 पूर्ण, अणु 13, 14, -12 पूर्ण
		पूर्ण
	पूर्ण,
	/* 6BPP/10BPC */
	अणु 768, 15, 6144, 7, 17, 15, 15, अणु
		अणु 0, 8, 0 पूर्ण, अणु 3, 10, -2 पूर्ण, अणु 7, 12, -2 पूर्ण, अणु 8, 12, -4 पूर्ण,
		अणु 9, 13, -6 पूर्ण, अणु 9, 13, -6 पूर्ण, अणु 10, 13, -6 पूर्ण, अणु 10, 14, -8 पूर्ण,
		अणु 11, 15, -8 पूर्ण, अणु 12, 16, -10 पूर्ण, अणु 13, 16, -10 पूर्ण,
		अणु 14, 16, -12 पूर्ण, अणु 14, 16, -12 पूर्ण, अणु 15, 16, -12 पूर्ण,
		अणु 17, 18, -12 पूर्ण
		पूर्ण
	पूर्ण,
	/* 6BPP/12BPC */
	अणु 768, 15, 6144, 11, 21, 19, 19, अणु
		अणु 0, 12, 0 पूर्ण, अणु 5, 14, -2 पूर्ण, अणु 11, 16, -2 पूर्ण, अणु 12, 16, -4 पूर्ण,
		अणु 13, 17, -6 पूर्ण, अणु 13, 17, -6 पूर्ण, अणु 14, 17, -6 पूर्ण, अणु 14, 18, -8 पूर्ण,
		अणु 15, 19, -8 पूर्ण, अणु 16, 20, -10 पूर्ण, अणु 17, 20, -10 पूर्ण,
		अणु 18, 20, -12 पूर्ण, अणु 18, 20, -12 पूर्ण, अणु 19, 20, -12 पूर्ण,
		अणु 21, 22, -12 पूर्ण
		पूर्ण
	पूर्ण,
	/* 6BPP/14BPC */
	अणु 768, 15, 6144, 15, 25, 23, 27, अणु
		अणु 0, 16, 0 पूर्ण, अणु 7, 18, -2 पूर्ण, अणु 15, 20, -2 पूर्ण, अणु 16, 20, -4 पूर्ण,
		अणु 17, 21, -6 पूर्ण, अणु 17, 21, -6 पूर्ण, अणु 18, 21, -6 पूर्ण, अणु 18, 22, -8 पूर्ण,
		अणु 19, 23, -8 पूर्ण, अणु 20, 24, -10 पूर्ण, अणु 21, 24, -10 पूर्ण,
		अणु 22, 24, -12 पूर्ण, अणु 22, 24, -12 पूर्ण, अणु 23, 24, -12 पूर्ण,
		अणु 25, 26, -12 पूर्ण
		पूर्ण
	पूर्ण,
	/* 6BPP/16BPC */
	अणु 768, 15, 6144, 19, 29, 27, 27, अणु
		अणु 0, 20, 0 पूर्ण, अणु 9, 22, -2 पूर्ण, अणु 19, 24, -2 पूर्ण, अणु 20, 24, -4 पूर्ण,
		अणु 21, 25, -6 पूर्ण, अणु 21, 25, -6 पूर्ण, अणु 22, 25, -6 पूर्ण, अणु 22, 26, -8 पूर्ण,
		अणु 23, 27, -8 पूर्ण, अणु 24, 28, -10 पूर्ण, अणु 25, 28, -10 पूर्ण,
		अणु 26, 28, -12 पूर्ण, अणु 26, 28, -12 पूर्ण, अणु 27, 28, -12 पूर्ण,
		अणु 29, 30, -12 पूर्ण
		पूर्ण
	पूर्ण,
पूर्ण,
अणु
	/* 8BPP/8BPC */
	अणु 512, 12, 6144, 3, 12, 11, 11, अणु
		अणु 0, 4, 2 पूर्ण, अणु 0, 4, 0 पूर्ण, अणु 1, 5, 0 पूर्ण, अणु 1, 6, -2 पूर्ण,
		अणु 3, 7, -4 पूर्ण, अणु 3, 7, -6 पूर्ण, अणु 3, 7, -8 पूर्ण, अणु 3, 8, -8 पूर्ण,
		अणु 3, 9, -8 पूर्ण, अणु 3, 10, -10 पूर्ण, अणु 5, 11, -10 पूर्ण, अणु 5, 12, -12 पूर्ण,
		अणु 5, 13, -12 पूर्ण, अणु 7, 13, -12 पूर्ण, अणु 13, 15, -12 पूर्ण
		पूर्ण
	पूर्ण,
	/* 8BPP/10BPC */
	अणु 512, 12, 6144, 7, 16, 15, 15, अणु
		अणु 0, 4, 2 पूर्ण, अणु 4, 8, 0 पूर्ण, अणु 5, 9, 0 पूर्ण, अणु 5, 10, -2 पूर्ण,
		अणु 7, 11, -4 पूर्ण, अणु 7, 11, -6 पूर्ण, अणु 7, 11, -8 पूर्ण, अणु 7, 12, -8 पूर्ण,
		अणु 7, 13, -8 पूर्ण, अणु 7, 14, -10 पूर्ण, अणु 9, 15, -10 पूर्ण, अणु 9, 16, -12 पूर्ण,
		अणु 9, 17, -12 पूर्ण, अणु 11, 17, -12 पूर्ण, अणु 17, 19, -12 पूर्ण
		पूर्ण
	पूर्ण,
	/* 8BPP/12BPC */
	अणु 512, 12, 6144, 11, 20, 19, 19, अणु
		अणु 0, 12, 2 पूर्ण, अणु 4, 12, 0 पूर्ण, अणु 9, 13, 0 पूर्ण, अणु 9, 14, -2 पूर्ण,
		अणु 11, 15, -4 पूर्ण, अणु 11, 15, -6 पूर्ण, अणु 11, 15, -8 पूर्ण, अणु 11, 16, -8 पूर्ण,
		अणु 11, 17, -8 पूर्ण, अणु 11, 18, -10 पूर्ण, अणु 13, 19, -10 पूर्ण,
		अणु 13, 20, -12 पूर्ण, अणु 13, 21, -12 पूर्ण, अणु 15, 21, -12 पूर्ण,
		अणु 21, 23, -12 पूर्ण
		पूर्ण
	पूर्ण,
	/* 8BPP/14BPC */
	अणु 512, 12, 6144, 15, 24, 23, 23, अणु
		अणु 0, 12, 0 पूर्ण, अणु 5, 13, 0 पूर्ण, अणु 11, 15, 0 पूर्ण, अणु 12, 17, -2 पूर्ण,
		अणु 15, 19, -4 पूर्ण, अणु 15, 19, -6 पूर्ण, अणु 15, 19, -8 पूर्ण, अणु 15, 20, -8 पूर्ण,
		अणु 15, 21, -8 पूर्ण, अणु 15, 22, -10 पूर्ण, अणु 17, 22, -10 पूर्ण,
		अणु 17, 23, -12 पूर्ण, अणु 17, 23, -12 पूर्ण, अणु 21, 24, -12 पूर्ण,
		अणु 24, 25, -12 पूर्ण
		पूर्ण
	पूर्ण,
	/* 8BPP/16BPC */
	अणु 512, 12, 6144, 19, 28, 27, 27, अणु
		अणु 0, 12, 2 पूर्ण, अणु 6, 14, 0 पूर्ण, अणु 13, 17, 0 पूर्ण, अणु 15, 20, -2 पूर्ण,
		अणु 19, 23, -4 पूर्ण, अणु 19, 23, -6 पूर्ण, अणु 19, 23, -8 पूर्ण, अणु 19, 24, -8 पूर्ण,
		अणु 19, 25, -8 पूर्ण, अणु 19, 26, -10 पूर्ण, अणु 21, 26, -10 पूर्ण,
		अणु 21, 27, -12 पूर्ण, अणु 21, 27, -12 पूर्ण, अणु 25, 28, -12 पूर्ण,
		अणु 28, 29, -12 पूर्ण
		पूर्ण
	पूर्ण,
पूर्ण,
अणु
	/* 10BPP/8BPC */
	अणु 410, 15, 5632, 3, 12, 11, 11, अणु
		अणु 0, 3, 2 पूर्ण, अणु 0, 4, 0 पूर्ण, अणु 1, 5, 0 पूर्ण, अणु 2, 6, -2 पूर्ण,
		अणु 3, 7, -4 पूर्ण, अणु 3, 7, -6 पूर्ण, अणु 3, 7, -8 पूर्ण, अणु 3, 8, -8 पूर्ण,
		अणु 3, 9, -8 पूर्ण, अणु 3, 9, -10 पूर्ण, अणु 5, 10, -10 पूर्ण, अणु 5, 10, -10 पूर्ण,
		अणु 5, 11, -12 पूर्ण, अणु 7, 11, -12 पूर्ण, अणु 11, 12, -12 पूर्ण
		पूर्ण
	पूर्ण,
	/* 10BPP/10BPC */
	अणु 410, 15, 5632, 7, 16, 15, 15, अणु
		अणु 0, 7, 2 पूर्ण, अणु 4, 8, 0 पूर्ण, अणु 5, 9, 0 पूर्ण, अणु 6, 10, -2 पूर्ण,
		अणु 7, 11, -4 पूर्ण, अणु 7, 11, -6 पूर्ण, अणु 7, 11, -8 पूर्ण, अणु 7, 12, -8 पूर्ण,
		अणु 7, 13, -8 पूर्ण, अणु 7, 13, -10 पूर्ण, अणु 9, 14, -10 पूर्ण, अणु 9, 14, -10 पूर्ण,
		अणु 9, 15, -12 पूर्ण, अणु 11, 15, -12 पूर्ण, अणु 15, 16, -12 पूर्ण
		पूर्ण
	पूर्ण,
	/* 10BPP/12BPC */
	अणु 410, 15, 5632, 11, 20, 19, 19, अणु
		अणु 0, 11, 2 पूर्ण, अणु 4, 12, 0 पूर्ण, अणु 9, 13, 0 पूर्ण, अणु 10, 14, -2 पूर्ण,
		अणु 11, 15, -4 पूर्ण, अणु 11, 15, -6 पूर्ण, अणु 11, 15, -8 पूर्ण, अणु 11, 16, -8 पूर्ण,
		अणु 11, 17, -8 पूर्ण, अणु 11, 17, -10 पूर्ण, अणु 13, 18, -10 पूर्ण,
		अणु 13, 18, -10 पूर्ण, अणु 13, 19, -12 पूर्ण, अणु 15, 19, -12 पूर्ण,
		अणु 19, 20, -12 पूर्ण
		पूर्ण
	पूर्ण,
	/* 10BPP/14BPC */
	अणु 410, 15, 5632, 15, 24, 23, 23, अणु
		अणु 0, 11, 2 पूर्ण, अणु 5, 13, 0 पूर्ण, अणु 11, 15, 0 पूर्ण, अणु 13, 18, -2 पूर्ण,
		अणु 15, 19, -4 पूर्ण, अणु 15, 19, -6 पूर्ण, अणु 15, 19, -8 पूर्ण, अणु 15, 20, -8 पूर्ण,
		अणु 15, 21, -8 पूर्ण, अणु 15, 21, -10 पूर्ण, अणु 17, 22, -10 पूर्ण,
		अणु 17, 22, -10 पूर्ण, अणु 17, 23, -12 पूर्ण, अणु 19, 23, -12 पूर्ण,
		अणु 23, 24, -12 पूर्ण
		पूर्ण
	पूर्ण,
	/* 10BPP/16BPC */
	अणु 410, 15, 5632, 19, 28, 27, 27, अणु
		अणु 0, 11, 2 पूर्ण, अणु 6, 14, 0 पूर्ण, अणु 13, 17, 0 पूर्ण, अणु 16, 20, -2 पूर्ण,
		अणु 19, 23, -4 पूर्ण, अणु 19, 23, -6 पूर्ण, अणु 19, 23, -8 पूर्ण, अणु 19, 24, -8 पूर्ण,
		अणु 19, 25, -8 पूर्ण, अणु 19, 25, -10 पूर्ण, अणु 21, 26, -10 पूर्ण,
		अणु 21, 26, -10 पूर्ण, अणु 21, 27, -12 पूर्ण, अणु 23, 27, -12 पूर्ण,
		अणु 27, 28, -12 पूर्ण
		पूर्ण
	पूर्ण,
पूर्ण,
अणु
	/* 12BPP/8BPC */
	अणु 341, 15, 2048, 3, 12, 11, 11, अणु
		अणु 0, 2, 2 पूर्ण, अणु 0, 4, 0 पूर्ण, अणु 1, 5, 0 पूर्ण, अणु 1, 6, -2 पूर्ण,
		अणु 3, 7, -4 पूर्ण, अणु 3, 7, -6 पूर्ण, अणु 3, 7, -8 पूर्ण, अणु 3, 8, -8 पूर्ण,
		अणु 3, 9, -8 पूर्ण, अणु 3, 10, -10 पूर्ण, अणु 5, 11, -10 पूर्ण,
		अणु 5, 12, -12 पूर्ण, अणु 5, 13, -12 पूर्ण, अणु 7, 13, -12 पूर्ण, अणु 13, 15, -12 पूर्ण
		पूर्ण
	पूर्ण,
	/* 12BPP/10BPC */
	अणु 341, 15, 2048, 7, 16, 15, 15, अणु
		अणु 0, 2, 2 पूर्ण, अणु 2, 5, 0 पूर्ण, अणु 3, 7, 0 पूर्ण, अणु 4, 8, -2 पूर्ण,
		अणु 6, 9, -4 पूर्ण, अणु 7, 10, -6 पूर्ण, अणु 7, 11, -8 पूर्ण, अणु 7, 12, -8 पूर्ण,
		अणु 7, 13, -8 पूर्ण, अणु 7, 14, -10 पूर्ण, अणु 9, 15, -10 पूर्ण, अणु 9, 16, -12 पूर्ण,
		अणु 9, 17, -12 पूर्ण, अणु 11, 17, -12 पूर्ण, अणु 17, 19, -12 पूर्ण
		पूर्ण
	पूर्ण,
	/* 12BPP/12BPC */
	अणु 341, 15, 2048, 11, 20, 19, 19, अणु
		अणु 0, 6, 2 पूर्ण, अणु 4, 9, 0 पूर्ण, अणु 7, 11, 0 पूर्ण, अणु 8, 12, -2 पूर्ण,
		अणु 10, 13, -4 पूर्ण, अणु 11, 14, -6 पूर्ण, अणु 11, 15, -8 पूर्ण, अणु 11, 16, -8 पूर्ण,
		अणु 11, 17, -8 पूर्ण, अणु 11, 18, -10 पूर्ण, अणु 13, 19, -10 पूर्ण,
		अणु 13, 20, -12 पूर्ण, अणु 13, 21, -12 पूर्ण, अणु 15, 21, -12 पूर्ण,
		अणु 21, 23, -12 पूर्ण
		पूर्ण
	पूर्ण,
	/* 12BPP/14BPC */
	अणु 341, 15, 2048, 15, 24, 23, 23, अणु
		अणु 0, 6, 2 पूर्ण, अणु 7, 10, 0 पूर्ण, अणु 9, 13, 0 पूर्ण, अणु 11, 16, -2 पूर्ण,
		अणु 14, 17, -4 पूर्ण, अणु 15, 18, -6 पूर्ण, अणु 15, 19, -8 पूर्ण, अणु 15, 20, -8 पूर्ण,
		अणु 15, 20, -8 पूर्ण, अणु 15, 21, -10 पूर्ण, अणु 17, 21, -10 पूर्ण,
		अणु 17, 21, -12 पूर्ण, अणु 17, 21, -12 पूर्ण, अणु 19, 22, -12 पूर्ण,
		अणु 22, 23, -12 पूर्ण
		पूर्ण
	पूर्ण,
	/* 12BPP/16BPC */
	अणु 341, 15, 2048, 19, 28, 27, 27, अणु
		अणु 0, 6, 2 पूर्ण, अणु 6, 11, 0 पूर्ण, अणु 11, 15, 0 पूर्ण, अणु 14, 18, -2 पूर्ण,
		अणु 18, 21, -4 पूर्ण, अणु 19, 22, -6 पूर्ण, अणु 19, 23, -8 पूर्ण, अणु 19, 24, -8 पूर्ण,
		अणु 19, 24, -8 पूर्ण, अणु 19, 25, -10 पूर्ण, अणु 21, 25, -10 पूर्ण,
		अणु 21, 25, -12 पूर्ण, अणु 21, 25, -12 पूर्ण, अणु 23, 26, -12 पूर्ण,
		अणु 26, 27, -12 पूर्ण
		पूर्ण
	पूर्ण,
पूर्ण,
अणु
	/* 15BPP/8BPC */
	अणु 273, 15, 2048, 3, 12, 11, 11, अणु
		अणु 0, 0, 10 पूर्ण, अणु 0, 1, 8 पूर्ण, अणु 0, 1, 6 पूर्ण, अणु 0, 2, 4 पूर्ण,
		अणु 1, 2, 2 पूर्ण, अणु 1, 3, 0 पूर्ण, अणु 1, 3, -2 पूर्ण, अणु 2, 4, -4 पूर्ण,
		अणु 2, 5, -6 पूर्ण, अणु 3, 5, -8 पूर्ण, अणु 4, 6, -10 पूर्ण, अणु 4, 7, -10 पूर्ण,
		अणु 5, 7, -12 पूर्ण, अणु 7, 8, -12 पूर्ण, अणु 8, 9, -12 पूर्ण
		पूर्ण
	पूर्ण,
	/* 15BPP/10BPC */
	अणु 273, 15, 2048, 7, 16, 15, 15, अणु
		अणु 0, 2, 10 पूर्ण, अणु 2, 5, 8 पूर्ण, अणु 3, 5, 6 पूर्ण, अणु 4, 6, 4 पूर्ण,
		अणु 5, 6, 2 पूर्ण, अणु 5, 7, 0 पूर्ण, अणु 5, 7, -2 पूर्ण, अणु 6, 8, -4 पूर्ण,
		अणु 6, 9, -6 पूर्ण, अणु 7, 9, -8 पूर्ण, अणु 8, 10, -10 पूर्ण, अणु 8, 11, -10 पूर्ण,
		अणु 9, 11, -12 पूर्ण, अणु 11, 12, -12 पूर्ण, अणु 12, 13, -12 पूर्ण
		पूर्ण
	पूर्ण,
	/* 15BPP/12BPC */
	अणु 273, 15, 2048, 11, 20, 19, 19, अणु
		अणु 0, 4, 10 पूर्ण, अणु 2, 7, 8 पूर्ण, अणु 4, 9, 6 पूर्ण, अणु 6, 11, 4 पूर्ण,
		अणु 9, 11, 2 पूर्ण, अणु 9, 11, 0 पूर्ण, अणु 9, 12, -2 पूर्ण, अणु 10, 12, -4 पूर्ण,
		अणु 11, 13, -6 पूर्ण, अणु 11, 13, -8 पूर्ण, अणु 12, 14, -10 पूर्ण,
		अणु 13, 15, -10 पूर्ण, अणु 13, 15, -12 पूर्ण, अणु 15, 16, -12 पूर्ण,
		अणु 16, 17, -12 पूर्ण
		पूर्ण
	पूर्ण,
	/* 15BPP/14BPC */
	अणु 273, 15, 2048, 15, 24, 23, 23, अणु
		अणु 0, 4, 10 पूर्ण, अणु 3, 8, 8 पूर्ण, अणु 6, 11, 6 पूर्ण, अणु 9, 14, 4 पूर्ण,
		अणु 13, 15, 2 पूर्ण, अणु 13, 15, 0 पूर्ण, अणु 13, 16, -2 पूर्ण, अणु 14, 16, -4 पूर्ण,
		अणु 15, 17, -6 पूर्ण, अणु 15, 17, -8 पूर्ण, अणु 16, 18, -10 पूर्ण,
		अणु 17, 19, -10 पूर्ण, अणु 17, 19, -12 पूर्ण, अणु 19, 20, -12 पूर्ण,
		अणु 20, 21, -12 पूर्ण
		पूर्ण
	पूर्ण,
	/* 15BPP/16BPC */
	अणु 273, 15, 2048, 19, 28, 27, 27, अणु
		अणु 0, 4, 10 पूर्ण, अणु 4, 9, 8 पूर्ण, अणु 8, 13, 6 पूर्ण, अणु 12, 17, 4 पूर्ण,
		अणु 17, 19, 2 पूर्ण, अणु 17, 20, 0 पूर्ण, अणु 17, 20, -2 पूर्ण, अणु 18, 20, -4 पूर्ण,
		अणु 19, 21, -6 पूर्ण, अणु 19, 21, -8 पूर्ण, अणु 20, 22, -10 पूर्ण,
		अणु 21, 23, -10 पूर्ण, अणु 21, 23, -12 पूर्ण, अणु 23, 24, -12 पूर्ण,
		अणु 24, 25, -12 पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

पूर्ण;

अटल पूर्णांक get_row_index_क्रम_rc_params(u16 compressed_bpp)
अणु
	चयन (compressed_bpp) अणु
	हाल 6:
		वापस ROW_INDEX_6BPP;
	हाल 8:
		वापस ROW_INDEX_8BPP;
	हाल 10:
		वापस ROW_INDEX_10BPP;
	हाल 12:
		वापस ROW_INDEX_12BPP;
	हाल 15:
		वापस ROW_INDEX_15BPP;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक get_column_index_क्रम_rc_params(u8 bits_per_component)
अणु
	चयन (bits_per_component) अणु
	हाल 8:
		वापस COLUMN_INDEX_8BPC;
	हाल 10:
		वापस COLUMN_INDEX_10BPC;
	हाल 12:
		वापस COLUMN_INDEX_12BPC;
	हाल 14:
		वापस COLUMN_INDEX_14BPC;
	हाल 16:
		वापस COLUMN_INDEX_16BPC;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा rc_parameters *get_rc_params(u16 compressed_bpp,
						 u8 bits_per_component)
अणु
	पूर्णांक row_index, column_index;

	row_index = get_row_index_क्रम_rc_params(compressed_bpp);
	अगर (row_index < 0)
		वापस शून्य;

	column_index = get_column_index_क्रम_rc_params(bits_per_component);
	अगर (column_index < 0)
		वापस शून्य;

	वापस &rc_parameters[row_index][column_index];
पूर्ण

bool पूर्णांकel_dsc_source_support(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	स्थिर काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *i915 = to_i915(crtc->base.dev);
	क्रमागत transcoder cpu_transcoder = crtc_state->cpu_transcoder;
	क्रमागत pipe pipe = crtc->pipe;

	अगर (!INTEL_INFO(i915)->display.has_dsc)
		वापस false;

	/* On TGL, DSC is supported on all Pipes */
	अगर (DISPLAY_VER(i915) >= 12)
		वापस true;

	अगर ((DISPLAY_VER(i915) >= 11 || IS_CANNONLAKE(i915)) && (pipe != PIPE_A || (cpu_transcoder == TRANSCODER_EDP || cpu_transcoder == TRANSCODER_DSI_0 || cpu_transcoder == TRANSCODER_DSI_1)))
		वापस true;

	वापस false;
पूर्ण

अटल bool is_pipe_dsc(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	स्थिर काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	स्थिर काष्ठा drm_i915_निजी *i915 = to_i915(crtc->base.dev);
	क्रमागत transcoder cpu_transcoder = crtc_state->cpu_transcoder;

	अगर (DISPLAY_VER(i915) >= 12)
		वापस true;

	अगर (cpu_transcoder == TRANSCODER_EDP ||
	    cpu_transcoder == TRANSCODER_DSI_0 ||
	    cpu_transcoder == TRANSCODER_DSI_1)
		वापस false;

	/* There's no pipe A DSC engine on ICL */
	drm_WARN_ON(&i915->drm, crtc->pipe == PIPE_A);

	वापस true;
पूर्ण

पूर्णांक पूर्णांकel_dsc_compute_params(काष्ठा पूर्णांकel_encoder *encoder,
			     काष्ठा पूर्णांकel_crtc_state *pipe_config)
अणु
	काष्ठा drm_dsc_config *vdsc_cfg = &pipe_config->dsc.config;
	u16 compressed_bpp = pipe_config->dsc.compressed_bpp;
	स्थिर काष्ठा rc_parameters *rc_params;
	u8 i = 0;

	vdsc_cfg->pic_width = pipe_config->hw.adjusted_mode.crtc_hdisplay;
	vdsc_cfg->pic_height = pipe_config->hw.adjusted_mode.crtc_vdisplay;
	vdsc_cfg->slice_width = DIV_ROUND_UP(vdsc_cfg->pic_width,
					     pipe_config->dsc.slice_count);

	/* Gen 11 करोes not support YCbCr */
	vdsc_cfg->simple_422 = false;
	/* Gen 11 करोes not support VBR */
	vdsc_cfg->vbr_enable = false;

	/* Gen 11 only supports पूर्णांकegral values of bpp */
	vdsc_cfg->bits_per_pixel = compressed_bpp << 4;
	vdsc_cfg->bits_per_component = pipe_config->pipe_bpp / 3;

	क्रम (i = 0; i < DSC_NUM_BUF_RANGES - 1; i++) अणु
		/*
		 * six 0s are appended to the lsb of each threshold value
		 * पूर्णांकernally in h/w.
		 * Only 8 bits are allowed क्रम programming RcBufThreshold
		 */
		vdsc_cfg->rc_buf_thresh[i] = rc_buf_thresh[i] >> 6;
	पूर्ण

	/*
	 * For 6bpp, RC Buffer threshold 12 and 13 need a dअगरferent value
	 * as per C Model
	 */
	अगर (compressed_bpp == 6) अणु
		vdsc_cfg->rc_buf_thresh[12] = 0x7C;
		vdsc_cfg->rc_buf_thresh[13] = 0x7D;
	पूर्ण

	rc_params = get_rc_params(compressed_bpp, vdsc_cfg->bits_per_component);
	अगर (!rc_params)
		वापस -EINVAL;

	vdsc_cfg->first_line_bpg_offset = rc_params->first_line_bpg_offset;
	vdsc_cfg->initial_xmit_delay = rc_params->initial_xmit_delay;
	vdsc_cfg->initial_offset = rc_params->initial_offset;
	vdsc_cfg->flatness_min_qp = rc_params->flatness_min_qp;
	vdsc_cfg->flatness_max_qp = rc_params->flatness_max_qp;
	vdsc_cfg->rc_quant_incr_limit0 = rc_params->rc_quant_incr_limit0;
	vdsc_cfg->rc_quant_incr_limit1 = rc_params->rc_quant_incr_limit1;

	क्रम (i = 0; i < DSC_NUM_BUF_RANGES; i++) अणु
		vdsc_cfg->rc_range_params[i].range_min_qp =
			rc_params->rc_range_params[i].range_min_qp;
		vdsc_cfg->rc_range_params[i].range_max_qp =
			rc_params->rc_range_params[i].range_max_qp;
		/*
		 * Range BPG Offset uses 2's complement and is only a 6 bits. So
		 * mask it to get only 6 bits.
		 */
		vdsc_cfg->rc_range_params[i].range_bpg_offset =
			rc_params->rc_range_params[i].range_bpg_offset &
			DSC_RANGE_BPG_OFFSET_MASK;
	पूर्ण

	/*
	 * BitsPerComponent value determines mux_word_size:
	 * When BitsPerComponent is 12bpc, muxWordSize will be equal to 64 bits
	 * When BitsPerComponent is 8 or 10bpc, muxWordSize will be equal to
	 * 48 bits
	 */
	अगर (vdsc_cfg->bits_per_component == 8 ||
	    vdsc_cfg->bits_per_component == 10)
		vdsc_cfg->mux_word_size = DSC_MUX_WORD_SIZE_8_10_BPC;
	अन्यथा अगर (vdsc_cfg->bits_per_component == 12)
		vdsc_cfg->mux_word_size = DSC_MUX_WORD_SIZE_12_BPC;

	/* InitialScaleValue is a 6 bit value with 3 fractional bits (U3.3) */
	vdsc_cfg->initial_scale_value = (vdsc_cfg->rc_model_size << 3) /
		(vdsc_cfg->rc_model_size - vdsc_cfg->initial_offset);

	वापस 0;
पूर्ण

क्रमागत पूर्णांकel_display_घातer_करोमुख्य
पूर्णांकel_dsc_घातer_करोमुख्य(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *i915 = to_i915(crtc->base.dev);
	क्रमागत pipe pipe = crtc->pipe;

	/*
	 * VDSC/joining uses a separate घातer well, PW2, and requires
	 * POWER_DOMAIN_TRANSCODER_VDSC_PW2 घातer करोमुख्य in two हालs:
	 *
	 *  - ICL eDP/DSI transcoder
	 *  - Gen12+ (except RKL) pipe A
	 *
	 * For any other pipe, VDSC/joining uses the घातer well associated with
	 * the pipe in use. Hence another reference on the pipe घातer करोमुख्य
	 * will suffice. (Except no VDSC/joining on ICL pipe A.)
	 */
	अगर (DISPLAY_VER(i915) >= 12 && !IS_ROCKETLAKE(i915) && pipe == PIPE_A)
		वापस POWER_DOMAIN_TRANSCODER_VDSC_PW2;
	अन्यथा अगर (is_pipe_dsc(crtc_state))
		वापस POWER_DOMAIN_PIPE(pipe);
	अन्यथा
		वापस POWER_DOMAIN_TRANSCODER_VDSC_PW2;
पूर्ण

अटल व्योम पूर्णांकel_dsc_pps_configure(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	स्थिर काष्ठा drm_dsc_config *vdsc_cfg = &crtc_state->dsc.config;
	क्रमागत pipe pipe = crtc->pipe;
	u32 pps_val = 0;
	u32 rc_buf_thresh_dword[4];
	u32 rc_range_params_dword[8];
	u8 num_vdsc_instances = (crtc_state->dsc.dsc_split) ? 2 : 1;
	पूर्णांक i = 0;

	अगर (crtc_state->bigjoiner)
		num_vdsc_instances *= 2;

	/* Populate PICTURE_PARAMETER_SET_0 रेजिस्टरs */
	pps_val = DSC_VER_MAJ | vdsc_cfg->dsc_version_minor <<
		DSC_VER_MIN_SHIFT |
		vdsc_cfg->bits_per_component << DSC_BPC_SHIFT |
		vdsc_cfg->line_buf_depth << DSC_LINE_BUF_DEPTH_SHIFT;
	अगर (vdsc_cfg->block_pred_enable)
		pps_val |= DSC_BLOCK_PREDICTION;
	अगर (vdsc_cfg->convert_rgb)
		pps_val |= DSC_COLOR_SPACE_CONVERSION;
	अगर (vdsc_cfg->simple_422)
		pps_val |= DSC_422_ENABLE;
	अगर (vdsc_cfg->vbr_enable)
		pps_val |= DSC_VBR_ENABLE;
	drm_info(&dev_priv->drm, "PPS0 = 0x%08x\n", pps_val);
	अगर (!is_pipe_dsc(crtc_state)) अणु
		पूर्णांकel_de_ग_लिखो(dev_priv, DSCA_PICTURE_PARAMETER_SET_0,
			       pps_val);
		/*
		 * If 2 VDSC instances are needed, configure PPS क्रम second
		 * VDSC
		 */
		अगर (crtc_state->dsc.dsc_split)
			पूर्णांकel_de_ग_लिखो(dev_priv, DSCC_PICTURE_PARAMETER_SET_0,
				       pps_val);
	पूर्ण अन्यथा अणु
		पूर्णांकel_de_ग_लिखो(dev_priv,
			       ICL_DSC0_PICTURE_PARAMETER_SET_0(pipe),
			       pps_val);
		अगर (crtc_state->dsc.dsc_split)
			पूर्णांकel_de_ग_लिखो(dev_priv,
				       ICL_DSC1_PICTURE_PARAMETER_SET_0(pipe),
				       pps_val);
	पूर्ण

	/* Populate PICTURE_PARAMETER_SET_1 रेजिस्टरs */
	pps_val = 0;
	pps_val |= DSC_BPP(vdsc_cfg->bits_per_pixel);
	drm_info(&dev_priv->drm, "PPS1 = 0x%08x\n", pps_val);
	अगर (!is_pipe_dsc(crtc_state)) अणु
		पूर्णांकel_de_ग_लिखो(dev_priv, DSCA_PICTURE_PARAMETER_SET_1,
			       pps_val);
		/*
		 * If 2 VDSC instances are needed, configure PPS क्रम second
		 * VDSC
		 */
		अगर (crtc_state->dsc.dsc_split)
			पूर्णांकel_de_ग_लिखो(dev_priv, DSCC_PICTURE_PARAMETER_SET_1,
				       pps_val);
	पूर्ण अन्यथा अणु
		पूर्णांकel_de_ग_लिखो(dev_priv,
			       ICL_DSC0_PICTURE_PARAMETER_SET_1(pipe),
			       pps_val);
		अगर (crtc_state->dsc.dsc_split)
			पूर्णांकel_de_ग_लिखो(dev_priv,
				       ICL_DSC1_PICTURE_PARAMETER_SET_1(pipe),
				       pps_val);
	पूर्ण

	/* Populate PICTURE_PARAMETER_SET_2 रेजिस्टरs */
	pps_val = 0;
	pps_val |= DSC_PIC_HEIGHT(vdsc_cfg->pic_height) |
		DSC_PIC_WIDTH(vdsc_cfg->pic_width / num_vdsc_instances);
	drm_info(&dev_priv->drm, "PPS2 = 0x%08x\n", pps_val);
	अगर (!is_pipe_dsc(crtc_state)) अणु
		पूर्णांकel_de_ग_लिखो(dev_priv, DSCA_PICTURE_PARAMETER_SET_2,
			       pps_val);
		/*
		 * If 2 VDSC instances are needed, configure PPS क्रम second
		 * VDSC
		 */
		अगर (crtc_state->dsc.dsc_split)
			पूर्णांकel_de_ग_लिखो(dev_priv, DSCC_PICTURE_PARAMETER_SET_2,
				       pps_val);
	पूर्ण अन्यथा अणु
		पूर्णांकel_de_ग_लिखो(dev_priv,
			       ICL_DSC0_PICTURE_PARAMETER_SET_2(pipe),
			       pps_val);
		अगर (crtc_state->dsc.dsc_split)
			पूर्णांकel_de_ग_लिखो(dev_priv,
				       ICL_DSC1_PICTURE_PARAMETER_SET_2(pipe),
				       pps_val);
	पूर्ण

	/* Populate PICTURE_PARAMETER_SET_3 रेजिस्टरs */
	pps_val = 0;
	pps_val |= DSC_SLICE_HEIGHT(vdsc_cfg->slice_height) |
		DSC_SLICE_WIDTH(vdsc_cfg->slice_width);
	drm_info(&dev_priv->drm, "PPS3 = 0x%08x\n", pps_val);
	अगर (!is_pipe_dsc(crtc_state)) अणु
		पूर्णांकel_de_ग_लिखो(dev_priv, DSCA_PICTURE_PARAMETER_SET_3,
			       pps_val);
		/*
		 * If 2 VDSC instances are needed, configure PPS क्रम second
		 * VDSC
		 */
		अगर (crtc_state->dsc.dsc_split)
			पूर्णांकel_de_ग_लिखो(dev_priv, DSCC_PICTURE_PARAMETER_SET_3,
				       pps_val);
	पूर्ण अन्यथा अणु
		पूर्णांकel_de_ग_लिखो(dev_priv,
			       ICL_DSC0_PICTURE_PARAMETER_SET_3(pipe),
			       pps_val);
		अगर (crtc_state->dsc.dsc_split)
			पूर्णांकel_de_ग_लिखो(dev_priv,
				       ICL_DSC1_PICTURE_PARAMETER_SET_3(pipe),
				       pps_val);
	पूर्ण

	/* Populate PICTURE_PARAMETER_SET_4 रेजिस्टरs */
	pps_val = 0;
	pps_val |= DSC_INITIAL_XMIT_DELAY(vdsc_cfg->initial_xmit_delay) |
		DSC_INITIAL_DEC_DELAY(vdsc_cfg->initial_dec_delay);
	drm_info(&dev_priv->drm, "PPS4 = 0x%08x\n", pps_val);
	अगर (!is_pipe_dsc(crtc_state)) अणु
		पूर्णांकel_de_ग_लिखो(dev_priv, DSCA_PICTURE_PARAMETER_SET_4,
			       pps_val);
		/*
		 * If 2 VDSC instances are needed, configure PPS क्रम second
		 * VDSC
		 */
		अगर (crtc_state->dsc.dsc_split)
			पूर्णांकel_de_ग_लिखो(dev_priv, DSCC_PICTURE_PARAMETER_SET_4,
				       pps_val);
	पूर्ण अन्यथा अणु
		पूर्णांकel_de_ग_लिखो(dev_priv,
			       ICL_DSC0_PICTURE_PARAMETER_SET_4(pipe),
			       pps_val);
		अगर (crtc_state->dsc.dsc_split)
			पूर्णांकel_de_ग_लिखो(dev_priv,
				       ICL_DSC1_PICTURE_PARAMETER_SET_4(pipe),
				       pps_val);
	पूर्ण

	/* Populate PICTURE_PARAMETER_SET_5 रेजिस्टरs */
	pps_val = 0;
	pps_val |= DSC_SCALE_INC_INT(vdsc_cfg->scale_increment_पूर्णांकerval) |
		DSC_SCALE_DEC_INT(vdsc_cfg->scale_decrement_पूर्णांकerval);
	drm_info(&dev_priv->drm, "PPS5 = 0x%08x\n", pps_val);
	अगर (!is_pipe_dsc(crtc_state)) अणु
		पूर्णांकel_de_ग_लिखो(dev_priv, DSCA_PICTURE_PARAMETER_SET_5,
			       pps_val);
		/*
		 * If 2 VDSC instances are needed, configure PPS क्रम second
		 * VDSC
		 */
		अगर (crtc_state->dsc.dsc_split)
			पूर्णांकel_de_ग_लिखो(dev_priv, DSCC_PICTURE_PARAMETER_SET_5,
				       pps_val);
	पूर्ण अन्यथा अणु
		पूर्णांकel_de_ग_लिखो(dev_priv,
			       ICL_DSC0_PICTURE_PARAMETER_SET_5(pipe),
			       pps_val);
		अगर (crtc_state->dsc.dsc_split)
			पूर्णांकel_de_ग_लिखो(dev_priv,
				       ICL_DSC1_PICTURE_PARAMETER_SET_5(pipe),
				       pps_val);
	पूर्ण

	/* Populate PICTURE_PARAMETER_SET_6 रेजिस्टरs */
	pps_val = 0;
	pps_val |= DSC_INITIAL_SCALE_VALUE(vdsc_cfg->initial_scale_value) |
		DSC_FIRST_LINE_BPG_OFFSET(vdsc_cfg->first_line_bpg_offset) |
		DSC_FLATNESS_MIN_QP(vdsc_cfg->flatness_min_qp) |
		DSC_FLATNESS_MAX_QP(vdsc_cfg->flatness_max_qp);
	drm_info(&dev_priv->drm, "PPS6 = 0x%08x\n", pps_val);
	अगर (!is_pipe_dsc(crtc_state)) अणु
		पूर्णांकel_de_ग_लिखो(dev_priv, DSCA_PICTURE_PARAMETER_SET_6,
			       pps_val);
		/*
		 * If 2 VDSC instances are needed, configure PPS क्रम second
		 * VDSC
		 */
		अगर (crtc_state->dsc.dsc_split)
			पूर्णांकel_de_ग_लिखो(dev_priv, DSCC_PICTURE_PARAMETER_SET_6,
				       pps_val);
	पूर्ण अन्यथा अणु
		पूर्णांकel_de_ग_लिखो(dev_priv,
			       ICL_DSC0_PICTURE_PARAMETER_SET_6(pipe),
			       pps_val);
		अगर (crtc_state->dsc.dsc_split)
			पूर्णांकel_de_ग_लिखो(dev_priv,
				       ICL_DSC1_PICTURE_PARAMETER_SET_6(pipe),
				       pps_val);
	पूर्ण

	/* Populate PICTURE_PARAMETER_SET_7 रेजिस्टरs */
	pps_val = 0;
	pps_val |= DSC_SLICE_BPG_OFFSET(vdsc_cfg->slice_bpg_offset) |
		DSC_NFL_BPG_OFFSET(vdsc_cfg->nfl_bpg_offset);
	drm_info(&dev_priv->drm, "PPS7 = 0x%08x\n", pps_val);
	अगर (!is_pipe_dsc(crtc_state)) अणु
		पूर्णांकel_de_ग_लिखो(dev_priv, DSCA_PICTURE_PARAMETER_SET_7,
			       pps_val);
		/*
		 * If 2 VDSC instances are needed, configure PPS क्रम second
		 * VDSC
		 */
		अगर (crtc_state->dsc.dsc_split)
			पूर्णांकel_de_ग_लिखो(dev_priv, DSCC_PICTURE_PARAMETER_SET_7,
				       pps_val);
	पूर्ण अन्यथा अणु
		पूर्णांकel_de_ग_लिखो(dev_priv,
			       ICL_DSC0_PICTURE_PARAMETER_SET_7(pipe),
			       pps_val);
		अगर (crtc_state->dsc.dsc_split)
			पूर्णांकel_de_ग_लिखो(dev_priv,
				       ICL_DSC1_PICTURE_PARAMETER_SET_7(pipe),
				       pps_val);
	पूर्ण

	/* Populate PICTURE_PARAMETER_SET_8 रेजिस्टरs */
	pps_val = 0;
	pps_val |= DSC_FINAL_OFFSET(vdsc_cfg->final_offset) |
		DSC_INITIAL_OFFSET(vdsc_cfg->initial_offset);
	drm_info(&dev_priv->drm, "PPS8 = 0x%08x\n", pps_val);
	अगर (!is_pipe_dsc(crtc_state)) अणु
		पूर्णांकel_de_ग_लिखो(dev_priv, DSCA_PICTURE_PARAMETER_SET_8,
			       pps_val);
		/*
		 * If 2 VDSC instances are needed, configure PPS क्रम second
		 * VDSC
		 */
		अगर (crtc_state->dsc.dsc_split)
			पूर्णांकel_de_ग_लिखो(dev_priv, DSCC_PICTURE_PARAMETER_SET_8,
				       pps_val);
	पूर्ण अन्यथा अणु
		पूर्णांकel_de_ग_लिखो(dev_priv,
			       ICL_DSC0_PICTURE_PARAMETER_SET_8(pipe),
			       pps_val);
		अगर (crtc_state->dsc.dsc_split)
			पूर्णांकel_de_ग_लिखो(dev_priv,
				       ICL_DSC1_PICTURE_PARAMETER_SET_8(pipe),
				       pps_val);
	पूर्ण

	/* Populate PICTURE_PARAMETER_SET_9 रेजिस्टरs */
	pps_val = 0;
	pps_val |= DSC_RC_MODEL_SIZE(vdsc_cfg->rc_model_size) |
		DSC_RC_EDGE_FACTOR(DSC_RC_EDGE_FACTOR_CONST);
	drm_info(&dev_priv->drm, "PPS9 = 0x%08x\n", pps_val);
	अगर (!is_pipe_dsc(crtc_state)) अणु
		पूर्णांकel_de_ग_लिखो(dev_priv, DSCA_PICTURE_PARAMETER_SET_9,
			       pps_val);
		/*
		 * If 2 VDSC instances are needed, configure PPS क्रम second
		 * VDSC
		 */
		अगर (crtc_state->dsc.dsc_split)
			पूर्णांकel_de_ग_लिखो(dev_priv, DSCC_PICTURE_PARAMETER_SET_9,
				       pps_val);
	पूर्ण अन्यथा अणु
		पूर्णांकel_de_ग_लिखो(dev_priv,
			       ICL_DSC0_PICTURE_PARAMETER_SET_9(pipe),
			       pps_val);
		अगर (crtc_state->dsc.dsc_split)
			पूर्णांकel_de_ग_लिखो(dev_priv,
				       ICL_DSC1_PICTURE_PARAMETER_SET_9(pipe),
				       pps_val);
	पूर्ण

	/* Populate PICTURE_PARAMETER_SET_10 रेजिस्टरs */
	pps_val = 0;
	pps_val |= DSC_RC_QUANT_INC_LIMIT0(vdsc_cfg->rc_quant_incr_limit0) |
		DSC_RC_QUANT_INC_LIMIT1(vdsc_cfg->rc_quant_incr_limit1) |
		DSC_RC_TARGET_OFF_HIGH(DSC_RC_TGT_OFFSET_HI_CONST) |
		DSC_RC_TARGET_OFF_LOW(DSC_RC_TGT_OFFSET_LO_CONST);
	drm_info(&dev_priv->drm, "PPS10 = 0x%08x\n", pps_val);
	अगर (!is_pipe_dsc(crtc_state)) अणु
		पूर्णांकel_de_ग_लिखो(dev_priv, DSCA_PICTURE_PARAMETER_SET_10,
			       pps_val);
		/*
		 * If 2 VDSC instances are needed, configure PPS क्रम second
		 * VDSC
		 */
		अगर (crtc_state->dsc.dsc_split)
			पूर्णांकel_de_ग_लिखो(dev_priv,
				       DSCC_PICTURE_PARAMETER_SET_10, pps_val);
	पूर्ण अन्यथा अणु
		पूर्णांकel_de_ग_लिखो(dev_priv,
			       ICL_DSC0_PICTURE_PARAMETER_SET_10(pipe),
			       pps_val);
		अगर (crtc_state->dsc.dsc_split)
			पूर्णांकel_de_ग_लिखो(dev_priv,
				       ICL_DSC1_PICTURE_PARAMETER_SET_10(pipe),
				       pps_val);
	पूर्ण

	/* Populate Picture parameter set 16 */
	pps_val = 0;
	pps_val |= DSC_SLICE_CHUNK_SIZE(vdsc_cfg->slice_chunk_size) |
		DSC_SLICE_PER_LINE((vdsc_cfg->pic_width / num_vdsc_instances) /
				   vdsc_cfg->slice_width) |
		DSC_SLICE_ROW_PER_FRAME(vdsc_cfg->pic_height /
					vdsc_cfg->slice_height);
	drm_info(&dev_priv->drm, "PPS16 = 0x%08x\n", pps_val);
	अगर (!is_pipe_dsc(crtc_state)) अणु
		पूर्णांकel_de_ग_लिखो(dev_priv, DSCA_PICTURE_PARAMETER_SET_16,
			       pps_val);
		/*
		 * If 2 VDSC instances are needed, configure PPS क्रम second
		 * VDSC
		 */
		अगर (crtc_state->dsc.dsc_split)
			पूर्णांकel_de_ग_लिखो(dev_priv,
				       DSCC_PICTURE_PARAMETER_SET_16, pps_val);
	पूर्ण अन्यथा अणु
		पूर्णांकel_de_ग_लिखो(dev_priv,
			       ICL_DSC0_PICTURE_PARAMETER_SET_16(pipe),
			       pps_val);
		अगर (crtc_state->dsc.dsc_split)
			पूर्णांकel_de_ग_लिखो(dev_priv,
				       ICL_DSC1_PICTURE_PARAMETER_SET_16(pipe),
				       pps_val);
	पूर्ण

	/* Populate the RC_BUF_THRESH रेजिस्टरs */
	स_रखो(rc_buf_thresh_dword, 0, माप(rc_buf_thresh_dword));
	क्रम (i = 0; i < DSC_NUM_BUF_RANGES - 1; i++) अणु
		rc_buf_thresh_dword[i / 4] |=
			(u32)(vdsc_cfg->rc_buf_thresh[i] <<
			      BITS_PER_BYTE * (i % 4));
		drm_info(&dev_priv->drm, " RC_BUF_THRESH%d = 0x%08x\n", i,
			 rc_buf_thresh_dword[i / 4]);
	पूर्ण
	अगर (!is_pipe_dsc(crtc_state)) अणु
		पूर्णांकel_de_ग_लिखो(dev_priv, DSCA_RC_BUF_THRESH_0,
			       rc_buf_thresh_dword[0]);
		पूर्णांकel_de_ग_लिखो(dev_priv, DSCA_RC_BUF_THRESH_0_UDW,
			       rc_buf_thresh_dword[1]);
		पूर्णांकel_de_ग_लिखो(dev_priv, DSCA_RC_BUF_THRESH_1,
			       rc_buf_thresh_dword[2]);
		पूर्णांकel_de_ग_लिखो(dev_priv, DSCA_RC_BUF_THRESH_1_UDW,
			       rc_buf_thresh_dword[3]);
		अगर (crtc_state->dsc.dsc_split) अणु
			पूर्णांकel_de_ग_लिखो(dev_priv, DSCC_RC_BUF_THRESH_0,
				       rc_buf_thresh_dword[0]);
			पूर्णांकel_de_ग_लिखो(dev_priv, DSCC_RC_BUF_THRESH_0_UDW,
				       rc_buf_thresh_dword[1]);
			पूर्णांकel_de_ग_लिखो(dev_priv, DSCC_RC_BUF_THRESH_1,
				       rc_buf_thresh_dword[2]);
			पूर्णांकel_de_ग_लिखो(dev_priv, DSCC_RC_BUF_THRESH_1_UDW,
				       rc_buf_thresh_dword[3]);
		पूर्ण
	पूर्ण अन्यथा अणु
		पूर्णांकel_de_ग_लिखो(dev_priv, ICL_DSC0_RC_BUF_THRESH_0(pipe),
			       rc_buf_thresh_dword[0]);
		पूर्णांकel_de_ग_लिखो(dev_priv, ICL_DSC0_RC_BUF_THRESH_0_UDW(pipe),
			       rc_buf_thresh_dword[1]);
		पूर्णांकel_de_ग_लिखो(dev_priv, ICL_DSC0_RC_BUF_THRESH_1(pipe),
			       rc_buf_thresh_dword[2]);
		पूर्णांकel_de_ग_लिखो(dev_priv, ICL_DSC0_RC_BUF_THRESH_1_UDW(pipe),
			       rc_buf_thresh_dword[3]);
		अगर (crtc_state->dsc.dsc_split) अणु
			पूर्णांकel_de_ग_लिखो(dev_priv,
				       ICL_DSC1_RC_BUF_THRESH_0(pipe),
				       rc_buf_thresh_dword[0]);
			पूर्णांकel_de_ग_लिखो(dev_priv,
				       ICL_DSC1_RC_BUF_THRESH_0_UDW(pipe),
				       rc_buf_thresh_dword[1]);
			पूर्णांकel_de_ग_लिखो(dev_priv,
				       ICL_DSC1_RC_BUF_THRESH_1(pipe),
				       rc_buf_thresh_dword[2]);
			पूर्णांकel_de_ग_लिखो(dev_priv,
				       ICL_DSC1_RC_BUF_THRESH_1_UDW(pipe),
				       rc_buf_thresh_dword[3]);
		पूर्ण
	पूर्ण

	/* Populate the RC_RANGE_PARAMETERS रेजिस्टरs */
	स_रखो(rc_range_params_dword, 0, माप(rc_range_params_dword));
	क्रम (i = 0; i < DSC_NUM_BUF_RANGES; i++) अणु
		rc_range_params_dword[i / 2] |=
			(u32)(((vdsc_cfg->rc_range_params[i].range_bpg_offset <<
				RC_BPG_OFFSET_SHIFT) |
			       (vdsc_cfg->rc_range_params[i].range_max_qp <<
				RC_MAX_QP_SHIFT) |
			       (vdsc_cfg->rc_range_params[i].range_min_qp <<
				RC_MIN_QP_SHIFT)) << 16 * (i % 2));
		drm_info(&dev_priv->drm, " RC_RANGE_PARAM_%d = 0x%08x\n", i,
			 rc_range_params_dword[i / 2]);
	पूर्ण
	अगर (!is_pipe_dsc(crtc_state)) अणु
		पूर्णांकel_de_ग_लिखो(dev_priv, DSCA_RC_RANGE_PARAMETERS_0,
			       rc_range_params_dword[0]);
		पूर्णांकel_de_ग_लिखो(dev_priv, DSCA_RC_RANGE_PARAMETERS_0_UDW,
			       rc_range_params_dword[1]);
		पूर्णांकel_de_ग_लिखो(dev_priv, DSCA_RC_RANGE_PARAMETERS_1,
			       rc_range_params_dword[2]);
		पूर्णांकel_de_ग_लिखो(dev_priv, DSCA_RC_RANGE_PARAMETERS_1_UDW,
			       rc_range_params_dword[3]);
		पूर्णांकel_de_ग_लिखो(dev_priv, DSCA_RC_RANGE_PARAMETERS_2,
			       rc_range_params_dword[4]);
		पूर्णांकel_de_ग_लिखो(dev_priv, DSCA_RC_RANGE_PARAMETERS_2_UDW,
			       rc_range_params_dword[5]);
		पूर्णांकel_de_ग_लिखो(dev_priv, DSCA_RC_RANGE_PARAMETERS_3,
			       rc_range_params_dword[6]);
		पूर्णांकel_de_ग_लिखो(dev_priv, DSCA_RC_RANGE_PARAMETERS_3_UDW,
			       rc_range_params_dword[7]);
		अगर (crtc_state->dsc.dsc_split) अणु
			पूर्णांकel_de_ग_लिखो(dev_priv, DSCC_RC_RANGE_PARAMETERS_0,
				       rc_range_params_dword[0]);
			पूर्णांकel_de_ग_लिखो(dev_priv,
				       DSCC_RC_RANGE_PARAMETERS_0_UDW,
				       rc_range_params_dword[1]);
			पूर्णांकel_de_ग_लिखो(dev_priv, DSCC_RC_RANGE_PARAMETERS_1,
				       rc_range_params_dword[2]);
			पूर्णांकel_de_ग_लिखो(dev_priv,
				       DSCC_RC_RANGE_PARAMETERS_1_UDW,
				       rc_range_params_dword[3]);
			पूर्णांकel_de_ग_लिखो(dev_priv, DSCC_RC_RANGE_PARAMETERS_2,
				       rc_range_params_dword[4]);
			पूर्णांकel_de_ग_लिखो(dev_priv,
				       DSCC_RC_RANGE_PARAMETERS_2_UDW,
				       rc_range_params_dword[5]);
			पूर्णांकel_de_ग_लिखो(dev_priv, DSCC_RC_RANGE_PARAMETERS_3,
				       rc_range_params_dword[6]);
			पूर्णांकel_de_ग_लिखो(dev_priv,
				       DSCC_RC_RANGE_PARAMETERS_3_UDW,
				       rc_range_params_dword[7]);
		पूर्ण
	पूर्ण अन्यथा अणु
		पूर्णांकel_de_ग_लिखो(dev_priv, ICL_DSC0_RC_RANGE_PARAMETERS_0(pipe),
			       rc_range_params_dword[0]);
		पूर्णांकel_de_ग_लिखो(dev_priv,
			       ICL_DSC0_RC_RANGE_PARAMETERS_0_UDW(pipe),
			       rc_range_params_dword[1]);
		पूर्णांकel_de_ग_लिखो(dev_priv, ICL_DSC0_RC_RANGE_PARAMETERS_1(pipe),
			       rc_range_params_dword[2]);
		पूर्णांकel_de_ग_लिखो(dev_priv,
			       ICL_DSC0_RC_RANGE_PARAMETERS_1_UDW(pipe),
			       rc_range_params_dword[3]);
		पूर्णांकel_de_ग_लिखो(dev_priv, ICL_DSC0_RC_RANGE_PARAMETERS_2(pipe),
			       rc_range_params_dword[4]);
		पूर्णांकel_de_ग_लिखो(dev_priv,
			       ICL_DSC0_RC_RANGE_PARAMETERS_2_UDW(pipe),
			       rc_range_params_dword[5]);
		पूर्णांकel_de_ग_लिखो(dev_priv, ICL_DSC0_RC_RANGE_PARAMETERS_3(pipe),
			       rc_range_params_dword[6]);
		पूर्णांकel_de_ग_लिखो(dev_priv,
			       ICL_DSC0_RC_RANGE_PARAMETERS_3_UDW(pipe),
			       rc_range_params_dword[7]);
		अगर (crtc_state->dsc.dsc_split) अणु
			पूर्णांकel_de_ग_लिखो(dev_priv,
				       ICL_DSC1_RC_RANGE_PARAMETERS_0(pipe),
				       rc_range_params_dword[0]);
			पूर्णांकel_de_ग_लिखो(dev_priv,
				       ICL_DSC1_RC_RANGE_PARAMETERS_0_UDW(pipe),
				       rc_range_params_dword[1]);
			पूर्णांकel_de_ग_लिखो(dev_priv,
				       ICL_DSC1_RC_RANGE_PARAMETERS_1(pipe),
				       rc_range_params_dword[2]);
			पूर्णांकel_de_ग_लिखो(dev_priv,
				       ICL_DSC1_RC_RANGE_PARAMETERS_1_UDW(pipe),
				       rc_range_params_dword[3]);
			पूर्णांकel_de_ग_लिखो(dev_priv,
				       ICL_DSC1_RC_RANGE_PARAMETERS_2(pipe),
				       rc_range_params_dword[4]);
			पूर्णांकel_de_ग_लिखो(dev_priv,
				       ICL_DSC1_RC_RANGE_PARAMETERS_2_UDW(pipe),
				       rc_range_params_dword[5]);
			पूर्णांकel_de_ग_लिखो(dev_priv,
				       ICL_DSC1_RC_RANGE_PARAMETERS_3(pipe),
				       rc_range_params_dword[6]);
			पूर्णांकel_de_ग_लिखो(dev_priv,
				       ICL_DSC1_RC_RANGE_PARAMETERS_3_UDW(pipe),
				       rc_range_params_dword[7]);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_dsc_dsi_pps_ग_लिखो(काष्ठा पूर्णांकel_encoder *encoder,
				    स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	स्थिर काष्ठा drm_dsc_config *vdsc_cfg = &crtc_state->dsc.config;
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi = enc_to_पूर्णांकel_dsi(encoder);
	काष्ठा mipi_dsi_device *dsi;
	काष्ठा drm_dsc_picture_parameter_set pps;
	क्रमागत port port;

	drm_dsc_pps_payload_pack(&pps, vdsc_cfg);

	क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports) अणु
		dsi = पूर्णांकel_dsi->dsi_hosts[port]->device;

		mipi_dsi_picture_parameter_set(dsi, &pps);
		mipi_dsi_compression_mode(dsi, true);
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_dsc_dp_pps_ग_लिखो(काष्ठा पूर्णांकel_encoder *encoder,
				   स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_dp *पूर्णांकel_dp = enc_to_पूर्णांकel_dp(encoder);
	काष्ठा पूर्णांकel_digital_port *dig_port = dp_to_dig_port(पूर्णांकel_dp);
	स्थिर काष्ठा drm_dsc_config *vdsc_cfg = &crtc_state->dsc.config;
	काष्ठा drm_dsc_pps_infoframe dp_dsc_pps_sdp;

	/* Prepare DP SDP PPS header as per DP 1.4 spec, Table 2-123 */
	drm_dsc_dp_pps_header_init(&dp_dsc_pps_sdp.pps_header);

	/* Fill the PPS payload bytes as per DSC spec 1.2 Table 4-1 */
	drm_dsc_pps_payload_pack(&dp_dsc_pps_sdp.pps_payload, vdsc_cfg);

	dig_port->ग_लिखो_infoframe(encoder, crtc_state,
				  DP_SDP_PPS, &dp_dsc_pps_sdp,
				  माप(dp_dsc_pps_sdp));
पूर्ण

अटल i915_reg_t dss_ctl1_reg(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	क्रमागत pipe pipe = to_पूर्णांकel_crtc(crtc_state->uapi.crtc)->pipe;

	वापस is_pipe_dsc(crtc_state) ? ICL_PIPE_DSS_CTL1(pipe) : DSS_CTL1;
पूर्ण

अटल i915_reg_t dss_ctl2_reg(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	क्रमागत pipe pipe = to_पूर्णांकel_crtc(crtc_state->uapi.crtc)->pipe;

	वापस is_pipe_dsc(crtc_state) ? ICL_PIPE_DSS_CTL2(pipe) : DSS_CTL2;
पूर्ण

व्योम पूर्णांकel_dsc_enable(काष्ठा पूर्णांकel_encoder *encoder,
		      स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	u32 dss_ctl1_val = 0;
	u32 dss_ctl2_val = 0;

	अगर (!crtc_state->dsc.compression_enable)
		वापस;

	पूर्णांकel_dsc_pps_configure(crtc_state);

	अगर (!crtc_state->bigjoiner_slave) अणु
		अगर (पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_DSI))
			पूर्णांकel_dsc_dsi_pps_ग_लिखो(encoder, crtc_state);
		अन्यथा
			पूर्णांकel_dsc_dp_pps_ग_लिखो(encoder, crtc_state);
	पूर्ण

	dss_ctl2_val |= LEFT_BRANCH_VDSC_ENABLE;
	अगर (crtc_state->dsc.dsc_split) अणु
		dss_ctl2_val |= RIGHT_BRANCH_VDSC_ENABLE;
		dss_ctl1_val |= JOINER_ENABLE;
	पूर्ण
	अगर (crtc_state->bigjoiner) अणु
		dss_ctl1_val |= BIG_JOINER_ENABLE;
		अगर (!crtc_state->bigjoiner_slave)
			dss_ctl1_val |= MASTER_BIG_JOINER_ENABLE;
	पूर्ण
	पूर्णांकel_de_ग_लिखो(dev_priv, dss_ctl1_reg(crtc_state), dss_ctl1_val);
	पूर्णांकel_de_ग_लिखो(dev_priv, dss_ctl2_reg(crtc_state), dss_ctl2_val);
पूर्ण

व्योम पूर्णांकel_dsc_disable(स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(old_crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);

	अगर (!old_crtc_state->dsc.compression_enable)
		वापस;

	पूर्णांकel_de_ग_लिखो(dev_priv, dss_ctl1_reg(old_crtc_state), 0);
	पूर्णांकel_de_ग_लिखो(dev_priv, dss_ctl2_reg(old_crtc_state), 0);
पूर्ण

व्योम पूर्णांकel_dsc_get_config(काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_dsc_config *vdsc_cfg = &crtc_state->dsc.config;
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	क्रमागत pipe pipe = crtc->pipe;
	क्रमागत पूर्णांकel_display_घातer_करोमुख्य घातer_करोमुख्य;
	पूर्णांकel_wakeref_t wakeref;
	u32 dss_ctl1, dss_ctl2, val;

	अगर (!पूर्णांकel_dsc_source_support(crtc_state))
		वापस;

	घातer_करोमुख्य = पूर्णांकel_dsc_घातer_करोमुख्य(crtc_state);

	wakeref = पूर्णांकel_display_घातer_get_अगर_enabled(dev_priv, घातer_करोमुख्य);
	अगर (!wakeref)
		वापस;

	dss_ctl1 = पूर्णांकel_de_पढ़ो(dev_priv, dss_ctl1_reg(crtc_state));
	dss_ctl2 = पूर्णांकel_de_पढ़ो(dev_priv, dss_ctl2_reg(crtc_state));

	crtc_state->dsc.compression_enable = dss_ctl2 & LEFT_BRANCH_VDSC_ENABLE;
	अगर (!crtc_state->dsc.compression_enable)
		जाओ out;

	crtc_state->dsc.dsc_split = (dss_ctl2 & RIGHT_BRANCH_VDSC_ENABLE) &&
		(dss_ctl1 & JOINER_ENABLE);

	अगर (dss_ctl1 & BIG_JOINER_ENABLE) अणु
		crtc_state->bigjoiner = true;

		अगर (!(dss_ctl1 & MASTER_BIG_JOINER_ENABLE)) अणु
			crtc_state->bigjoiner_slave = true;
			अगर (!WARN_ON(crtc->pipe == PIPE_A))
				crtc_state->bigjoiner_linked_crtc =
					पूर्णांकel_get_crtc_क्रम_pipe(dev_priv, crtc->pipe - 1);
		पूर्ण अन्यथा अणु
			अगर (!WARN_ON(INTEL_NUM_PIPES(dev_priv) == crtc->pipe + 1))
				crtc_state->bigjoiner_linked_crtc =
					पूर्णांकel_get_crtc_क्रम_pipe(dev_priv, crtc->pipe + 1);
		पूर्ण
	पूर्ण

	/* FIXME: add more state पढ़ोout as needed */

	/* PPS1 */
	अगर (!is_pipe_dsc(crtc_state))
		val = पूर्णांकel_de_पढ़ो(dev_priv, DSCA_PICTURE_PARAMETER_SET_1);
	अन्यथा
		val = पूर्णांकel_de_पढ़ो(dev_priv,
				    ICL_DSC0_PICTURE_PARAMETER_SET_1(pipe));
	vdsc_cfg->bits_per_pixel = val;
	crtc_state->dsc.compressed_bpp = vdsc_cfg->bits_per_pixel >> 4;
out:
	पूर्णांकel_display_घातer_put(dev_priv, घातer_करोमुख्य, wakeref);
पूर्ण
