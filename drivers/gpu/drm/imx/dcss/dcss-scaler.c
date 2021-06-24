<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2019 NXP.
 *
 * Scaling algorithms were contributed by Dzung Hoang <dzung.hoang@nxp.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/slab.h>

#समावेश "dcss-dev.h"

#घोषणा DCSS_SCALER_CTRL			0x00
#घोषणा   SCALER_EN				BIT(0)
#घोषणा   REPEAT_EN				BIT(4)
#घोषणा   SCALE2MEM_EN				BIT(8)
#घोषणा   MEM2OFIFO_EN				BIT(12)
#घोषणा DCSS_SCALER_OFIFO_CTRL			0x04
#घोषणा   OFIFO_LOW_THRES_POS			0
#घोषणा   OFIFO_LOW_THRES_MASK			GENMASK(9, 0)
#घोषणा   OFIFO_HIGH_THRES_POS			16
#घोषणा   OFIFO_HIGH_THRES_MASK			GENMASK(25, 16)
#घोषणा   UNDERRUN_DETECT_CLR			BIT(26)
#घोषणा   LOW_THRES_DETECT_CLR			BIT(27)
#घोषणा   HIGH_THRES_DETECT_CLR			BIT(28)
#घोषणा   UNDERRUN_DETECT_EN			BIT(29)
#घोषणा   LOW_THRES_DETECT_EN			BIT(30)
#घोषणा   HIGH_THRES_DETECT_EN			BIT(31)
#घोषणा DCSS_SCALER_SDATA_CTRL			0x08
#घोषणा   YUV_EN				BIT(0)
#घोषणा   RTRAM_8LINES				BIT(1)
#घोषणा   Y_UV_BYTE_SWAP			BIT(4)
#घोषणा   A2R10G10B10_FORMAT_POS		8
#घोषणा   A2R10G10B10_FORMAT_MASK		GENMASK(11, 8)
#घोषणा DCSS_SCALER_BIT_DEPTH			0x0C
#घोषणा   LUM_BIT_DEPTH_POS			0
#घोषणा   LUM_BIT_DEPTH_MASK			GENMASK(1, 0)
#घोषणा   CHR_BIT_DEPTH_POS			4
#घोषणा   CHR_BIT_DEPTH_MASK			GENMASK(5, 4)
#घोषणा DCSS_SCALER_SRC_FORMAT			0x10
#घोषणा DCSS_SCALER_DST_FORMAT			0x14
#घोषणा   FORMAT_MASK				GENMASK(1, 0)
#घोषणा DCSS_SCALER_SRC_LUM_RES			0x18
#घोषणा DCSS_SCALER_SRC_CHR_RES			0x1C
#घोषणा DCSS_SCALER_DST_LUM_RES			0x20
#घोषणा DCSS_SCALER_DST_CHR_RES			0x24
#घोषणा   WIDTH_POS				0
#घोषणा   WIDTH_MASK				GENMASK(11, 0)
#घोषणा   HEIGHT_POS				16
#घोषणा   HEIGHT_MASK				GENMASK(27, 16)
#घोषणा DCSS_SCALER_V_LUM_START			0x48
#घोषणा   V_START_MASK				GENMASK(15, 0)
#घोषणा DCSS_SCALER_V_LUM_INC			0x4C
#घोषणा   V_INC_MASK				GENMASK(15, 0)
#घोषणा DCSS_SCALER_H_LUM_START			0x50
#घोषणा   H_START_MASK				GENMASK(18, 0)
#घोषणा DCSS_SCALER_H_LUM_INC			0x54
#घोषणा   H_INC_MASK				GENMASK(15, 0)
#घोषणा DCSS_SCALER_V_CHR_START			0x58
#घोषणा DCSS_SCALER_V_CHR_INC			0x5C
#घोषणा DCSS_SCALER_H_CHR_START			0x60
#घोषणा DCSS_SCALER_H_CHR_INC			0x64
#घोषणा DCSS_SCALER_COEF_VLUM			0x80
#घोषणा DCSS_SCALER_COEF_HLUM			0x140
#घोषणा DCSS_SCALER_COEF_VCHR			0x200
#घोषणा DCSS_SCALER_COEF_HCHR			0x300

काष्ठा dcss_scaler_ch अणु
	व्योम __iomem *base_reg;
	u32 base_ofs;
	काष्ठा dcss_scaler *scl;

	u32 sdata_ctrl;
	u32 scaler_ctrl;

	bool scaler_ctrl_chgd;

	u32 c_vstart;
	u32 c_hstart;

	bool use_nn_पूर्णांकerpolation;
पूर्ण;

काष्ठा dcss_scaler अणु
	काष्ठा device *dev;

	काष्ठा dcss_ctxld *ctxld;
	u32 ctx_id;

	काष्ठा dcss_scaler_ch ch[3];
पूर्ण;

/* scaler coefficients generator */
#घोषणा PSC_FRAC_BITS 30
#घोषणा PSC_FRAC_SCALE BIT(PSC_FRAC_BITS)
#घोषणा PSC_BITS_FOR_PHASE 4
#घोषणा PSC_NUM_PHASES 16
#घोषणा PSC_STORED_PHASES (PSC_NUM_PHASES / 2 + 1)
#घोषणा PSC_NUM_TAPS 7
#घोषणा PSC_NUM_TAPS_RGBA 5
#घोषणा PSC_COEFF_PRECISION 10
#घोषणा PSC_PHASE_FRACTION_BITS 13
#घोषणा PSC_PHASE_MASK (PSC_NUM_PHASES - 1)
#घोषणा PSC_Q_FRACTION 19
#घोषणा PSC_Q_ROUND_OFFSET (1 << (PSC_Q_FRACTION - 1))

/**
 * mult_q() - Perक्रमms fixed-poपूर्णांक multiplication.
 * @A: multiplier
 * @B: multiplicand
 */
अटल पूर्णांक mult_q(पूर्णांक A, पूर्णांक B)
अणु
	पूर्णांक result;
	s64 temp;

	temp = (पूर्णांक64_t)A * (पूर्णांक64_t)B;
	temp += PSC_Q_ROUND_OFFSET;
	result = (पूर्णांक)(temp >> PSC_Q_FRACTION);
	वापस result;
पूर्ण

/**
 * भाग_q() - Perक्रमms fixed-poपूर्णांक भागision.
 * @A: भागidend
 * @B: भागisor
 */
अटल पूर्णांक भाग_q(पूर्णांक A, पूर्णांक B)
अणु
	पूर्णांक result;
	s64 temp;

	temp = (पूर्णांक64_t)A << PSC_Q_FRACTION;
	अगर ((temp >= 0 && B >= 0) || (temp < 0 && B < 0))
		temp += B / 2;
	अन्यथा
		temp -= B / 2;

	result = (पूर्णांक)(temp / B);
	वापस result;
पूर्ण

/**
 * exp_approx_q() - Compute approximation to exp(x) function using Taylor
 *		    series.
 * @x: fixed-poपूर्णांक argument of exp function
 */
अटल पूर्णांक exp_approx_q(पूर्णांक x)
अणु
	पूर्णांक sum = 1 << PSC_Q_FRACTION;
	पूर्णांक term = 1 << PSC_Q_FRACTION;

	term = mult_q(term, भाग_q(x, 1 << PSC_Q_FRACTION));
	sum += term;
	term = mult_q(term, भाग_q(x, 2 << PSC_Q_FRACTION));
	sum += term;
	term = mult_q(term, भाग_q(x, 3 << PSC_Q_FRACTION));
	sum += term;
	term = mult_q(term, भाग_q(x, 4 << PSC_Q_FRACTION));
	sum += term;

	वापस sum;
पूर्ण

/**
 * dcss_scaler_gaussian_filter() - Generate gaussian prototype filter.
 * @fc_q: fixed-poपूर्णांक cutoff frequency normalized to range [0, 1]
 * @use_5_taps: indicates whether to use 5 taps or 7 taps
 * @coef: output filter coefficients
 */
अटल व्योम dcss_scaler_gaussian_filter(पूर्णांक fc_q, bool use_5_taps,
					bool phase0_identity,
					पूर्णांक coef[][PSC_NUM_TAPS])
अणु
	पूर्णांक sigma_q, g0_q, g1_q, g2_q;
	पूर्णांक tap_cnt1, tap_cnt2, tap_idx, phase_cnt;
	पूर्णांक mid;
	पूर्णांक phase;
	पूर्णांक i;
	पूर्णांक taps;

	अगर (use_5_taps)
		क्रम (phase = 0; phase < PSC_STORED_PHASES; phase++) अणु
			coef[phase][0] = 0;
			coef[phase][PSC_NUM_TAPS - 1] = 0;
		पूर्ण

	/* seed coefficient scanner */
	taps = use_5_taps ? PSC_NUM_TAPS_RGBA : PSC_NUM_TAPS;
	mid = (PSC_NUM_PHASES * taps) / 2 - 1;
	phase_cnt = (PSC_NUM_PHASES * (PSC_NUM_TAPS + 1)) / 2;
	tap_cnt1 = (PSC_NUM_PHASES * PSC_NUM_TAPS) / 2;
	tap_cnt2 = (PSC_NUM_PHASES * PSC_NUM_TAPS) / 2;

	/* seed gaussian filter generator */
	sigma_q = भाग_q(PSC_Q_ROUND_OFFSET, fc_q);
	g0_q = 1 << PSC_Q_FRACTION;
	g1_q = exp_approx_q(भाग_q(-PSC_Q_ROUND_OFFSET,
				  mult_q(sigma_q, sigma_q)));
	g2_q = mult_q(g1_q, g1_q);
	coef[phase_cnt & PSC_PHASE_MASK][tap_cnt1 >> PSC_BITS_FOR_PHASE] = g0_q;

	क्रम (i = 0; i < mid; i++) अणु
		phase_cnt++;
		tap_cnt1--;
		tap_cnt2++;

		g0_q = mult_q(g0_q, g1_q);
		g1_q = mult_q(g1_q, g2_q);

		अगर ((phase_cnt & PSC_PHASE_MASK) <= 8) अणु
			tap_idx = tap_cnt1 >> PSC_BITS_FOR_PHASE;
			coef[phase_cnt & PSC_PHASE_MASK][tap_idx] = g0_q;
		पूर्ण
		अगर (((-phase_cnt) & PSC_PHASE_MASK) <= 8) अणु
			tap_idx = tap_cnt2 >> PSC_BITS_FOR_PHASE;
			coef[(-phase_cnt) & PSC_PHASE_MASK][tap_idx] = g0_q;
		पूर्ण
	पूर्ण

	phase_cnt++;
	tap_cnt1--;
	coef[phase_cnt & PSC_PHASE_MASK][tap_cnt1 >> PSC_BITS_FOR_PHASE] = 0;

	/* override phase 0 with identity filter अगर specअगरied */
	अगर (phase0_identity)
		क्रम (i = 0; i < PSC_NUM_TAPS; i++)
			coef[0][i] = i == (PSC_NUM_TAPS >> 1) ?
						(1 << PSC_COEFF_PRECISION) : 0;

	/* normalize coef */
	क्रम (phase = 0; phase < PSC_STORED_PHASES; phase++) अणु
		पूर्णांक sum = 0;
		s64 ll_temp;

		क्रम (i = 0; i < PSC_NUM_TAPS; i++)
			sum += coef[phase][i];
		क्रम (i = 0; i < PSC_NUM_TAPS; i++) अणु
			ll_temp = coef[phase][i];
			ll_temp <<= PSC_COEFF_PRECISION;
			ll_temp += sum >> 1;
			ll_temp /= sum;
			coef[phase][i] = (पूर्णांक)ll_temp;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम dcss_scaler_nearest_neighbor_filter(bool use_5_taps,
						पूर्णांक coef[][PSC_NUM_TAPS])
अणु
	पूर्णांक i, j;

	क्रम (i = 0; i < PSC_STORED_PHASES; i++)
		क्रम (j = 0; j < PSC_NUM_TAPS; j++)
			coef[i][j] = j == PSC_NUM_TAPS >> 1 ?
						(1 << PSC_COEFF_PRECISION) : 0;
पूर्ण

/**
 * dcss_scaler_filter_design() - Compute filter coefficients using
 *				 Gaussian filter.
 * @src_length: length of input
 * @dst_length: length of output
 * @use_5_taps: 0 क्रम 7 taps per phase, 1 क्रम 5 taps
 * @coef: output coefficients
 */
अटल व्योम dcss_scaler_filter_design(पूर्णांक src_length, पूर्णांक dst_length,
				      bool use_5_taps, bool phase0_identity,
				      पूर्णांक coef[][PSC_NUM_TAPS],
				      bool nn_पूर्णांकerpolation)
अणु
	पूर्णांक fc_q;

	/* compute cutoff frequency */
	अगर (dst_length >= src_length)
		fc_q = भाग_q(1, PSC_NUM_PHASES);
	अन्यथा
		fc_q = भाग_q(dst_length, src_length * PSC_NUM_PHASES);

	अगर (nn_पूर्णांकerpolation)
		dcss_scaler_nearest_neighbor_filter(use_5_taps, coef);
	अन्यथा
		/* compute gaussian filter coefficients */
		dcss_scaler_gaussian_filter(fc_q, use_5_taps, phase0_identity, coef);
पूर्ण

अटल व्योम dcss_scaler_ग_लिखो(काष्ठा dcss_scaler_ch *ch, u32 val, u32 ofs)
अणु
	काष्ठा dcss_scaler *scl = ch->scl;

	dcss_ctxld_ग_लिखो(scl->ctxld, scl->ctx_id, val, ch->base_ofs + ofs);
पूर्ण

अटल पूर्णांक dcss_scaler_ch_init_all(काष्ठा dcss_scaler *scl,
				   अचिन्हित दीर्घ scaler_base)
अणु
	काष्ठा dcss_scaler_ch *ch;
	पूर्णांक i;

	क्रम (i = 0; i < 3; i++) अणु
		ch = &scl->ch[i];

		ch->base_ofs = scaler_base + i * 0x400;

		ch->base_reg = ioremap(ch->base_ofs, SZ_4K);
		अगर (!ch->base_reg) अणु
			dev_err(scl->dev, "scaler: unable to remap ch base\n");
			वापस -ENOMEM;
		पूर्ण

		ch->scl = scl;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक dcss_scaler_init(काष्ठा dcss_dev *dcss, अचिन्हित दीर्घ scaler_base)
अणु
	काष्ठा dcss_scaler *scaler;

	scaler = kzalloc(माप(*scaler), GFP_KERNEL);
	अगर (!scaler)
		वापस -ENOMEM;

	dcss->scaler = scaler;
	scaler->dev = dcss->dev;
	scaler->ctxld = dcss->ctxld;
	scaler->ctx_id = CTX_SB_HP;

	अगर (dcss_scaler_ch_init_all(scaler, scaler_base)) अणु
		पूर्णांक i;

		क्रम (i = 0; i < 3; i++) अणु
			अगर (scaler->ch[i].base_reg)
				iounmap(scaler->ch[i].base_reg);
		पूर्ण

		kमुक्त(scaler);

		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

व्योम dcss_scaler_निकास(काष्ठा dcss_scaler *scl)
अणु
	पूर्णांक ch_no;

	क्रम (ch_no = 0; ch_no < 3; ch_no++) अणु
		काष्ठा dcss_scaler_ch *ch = &scl->ch[ch_no];

		dcss_ग_लिखोl(0, ch->base_reg + DCSS_SCALER_CTRL);

		अगर (ch->base_reg)
			iounmap(ch->base_reg);
	पूर्ण

	kमुक्त(scl);
पूर्ण

व्योम dcss_scaler_ch_enable(काष्ठा dcss_scaler *scl, पूर्णांक ch_num, bool en)
अणु
	काष्ठा dcss_scaler_ch *ch = &scl->ch[ch_num];
	u32 scaler_ctrl;

	scaler_ctrl = en ? SCALER_EN | REPEAT_EN : 0;

	अगर (en)
		dcss_scaler_ग_लिखो(ch, ch->sdata_ctrl, DCSS_SCALER_SDATA_CTRL);

	अगर (ch->scaler_ctrl != scaler_ctrl)
		ch->scaler_ctrl_chgd = true;

	ch->scaler_ctrl = scaler_ctrl;
पूर्ण

अटल व्योम dcss_scaler_yuv_enable(काष्ठा dcss_scaler_ch *ch, bool en)
अणु
	ch->sdata_ctrl &= ~YUV_EN;
	ch->sdata_ctrl |= en ? YUV_EN : 0;
पूर्ण

अटल व्योम dcss_scaler_rtr_8lines_enable(काष्ठा dcss_scaler_ch *ch, bool en)
अणु
	ch->sdata_ctrl &= ~RTRAM_8LINES;
	ch->sdata_ctrl |= en ? RTRAM_8LINES : 0;
पूर्ण

अटल व्योम dcss_scaler_bit_depth_set(काष्ठा dcss_scaler_ch *ch, पूर्णांक depth)
अणु
	u32 val;

	val = depth == 30 ? 2 : 0;

	dcss_scaler_ग_लिखो(ch,
			  ((val << CHR_BIT_DEPTH_POS) & CHR_BIT_DEPTH_MASK) |
			  ((val << LUM_BIT_DEPTH_POS) & LUM_BIT_DEPTH_MASK),
			  DCSS_SCALER_BIT_DEPTH);
पूर्ण

क्रमागत buffer_क्रमmat अणु
	BUF_FMT_YUV420,
	BUF_FMT_YUV422,
	BUF_FMT_ARGB8888_YUV444,
पूर्ण;

क्रमागत chroma_location अणु
	PSC_LOC_HORZ_0_VERT_1_OVER_4 = 0,
	PSC_LOC_HORZ_1_OVER_4_VERT_1_OVER_4 = 1,
	PSC_LOC_HORZ_0_VERT_0 = 2,
	PSC_LOC_HORZ_1_OVER_4_VERT_0 = 3,
	PSC_LOC_HORZ_0_VERT_1_OVER_2 = 4,
	PSC_LOC_HORZ_1_OVER_4_VERT_1_OVER_2 = 5
पूर्ण;

अटल व्योम dcss_scaler_क्रमmat_set(काष्ठा dcss_scaler_ch *ch,
				   क्रमागत buffer_क्रमmat src_fmt,
				   क्रमागत buffer_क्रमmat dst_fmt)
अणु
	dcss_scaler_ग_लिखो(ch, src_fmt, DCSS_SCALER_SRC_FORMAT);
	dcss_scaler_ग_लिखो(ch, dst_fmt, DCSS_SCALER_DST_FORMAT);
पूर्ण

अटल व्योम dcss_scaler_res_set(काष्ठा dcss_scaler_ch *ch,
				पूर्णांक src_xres, पूर्णांक src_yres,
				पूर्णांक dst_xres, पूर्णांक dst_yres,
				u32 pix_क्रमmat, क्रमागत buffer_क्रमmat dst_क्रमmat)
अणु
	u32 lsrc_xres, lsrc_yres, csrc_xres, csrc_yres;
	u32 ldst_xres, ldst_yres, cdst_xres, cdst_yres;
	bool src_is_444 = true;

	lsrc_xres = src_xres;
	csrc_xres = src_xres;
	lsrc_yres = src_yres;
	csrc_yres = src_yres;
	ldst_xres = dst_xres;
	cdst_xres = dst_xres;
	ldst_yres = dst_yres;
	cdst_yres = dst_yres;

	अगर (pix_क्रमmat == DRM_FORMAT_UYVY || pix_क्रमmat == DRM_FORMAT_VYUY ||
	    pix_क्रमmat == DRM_FORMAT_YUYV || pix_क्रमmat == DRM_FORMAT_YVYU) अणु
		csrc_xres >>= 1;
		src_is_444 = false;
	पूर्ण अन्यथा अगर (pix_क्रमmat == DRM_FORMAT_NV12 ||
		   pix_क्रमmat == DRM_FORMAT_NV21) अणु
		csrc_xres >>= 1;
		csrc_yres >>= 1;
		src_is_444 = false;
	पूर्ण

	अगर (dst_क्रमmat == BUF_FMT_YUV422)
		cdst_xres >>= 1;

	/* क्रम 4:4:4 to 4:2:2 conversion, source height should be 1 less */
	अगर (src_is_444 && dst_क्रमmat == BUF_FMT_YUV422) अणु
		lsrc_yres--;
		csrc_yres--;
	पूर्ण

	dcss_scaler_ग_लिखो(ch, (((lsrc_yres - 1) << HEIGHT_POS) & HEIGHT_MASK) |
			       (((lsrc_xres - 1) << WIDTH_POS) & WIDTH_MASK),
			  DCSS_SCALER_SRC_LUM_RES);
	dcss_scaler_ग_लिखो(ch, (((csrc_yres - 1) << HEIGHT_POS) & HEIGHT_MASK) |
			       (((csrc_xres - 1) << WIDTH_POS) & WIDTH_MASK),
			  DCSS_SCALER_SRC_CHR_RES);
	dcss_scaler_ग_लिखो(ch, (((ldst_yres - 1) << HEIGHT_POS) & HEIGHT_MASK) |
			       (((ldst_xres - 1) << WIDTH_POS) & WIDTH_MASK),
			  DCSS_SCALER_DST_LUM_RES);
	dcss_scaler_ग_लिखो(ch, (((cdst_yres - 1) << HEIGHT_POS) & HEIGHT_MASK) |
			       (((cdst_xres - 1) << WIDTH_POS) & WIDTH_MASK),
			  DCSS_SCALER_DST_CHR_RES);
पूर्ण

#घोषणा करोwnscale_fp(factor, fp_pos)		((factor) << (fp_pos))
#घोषणा upscale_fp(factor, fp_pos)		((1 << (fp_pos)) / (factor))

काष्ठा dcss_scaler_factors अणु
	पूर्णांक करोwnscale;
	पूर्णांक upscale;
पूर्ण;

अटल स्थिर काष्ठा dcss_scaler_factors dcss_scaler_factors[] = अणु
	अणु3, 8पूर्ण, अणु5, 8पूर्ण, अणु5, 8पूर्ण,
पूर्ण;

अटल व्योम dcss_scaler_fractions_set(काष्ठा dcss_scaler_ch *ch,
				      पूर्णांक src_xres, पूर्णांक src_yres,
				      पूर्णांक dst_xres, पूर्णांक dst_yres,
				      u32 src_क्रमmat, u32 dst_क्रमmat,
				      क्रमागत chroma_location src_chroma_loc)
अणु
	पूर्णांक src_c_xres, src_c_yres, dst_c_xres, dst_c_yres;
	u32 l_vinc, l_hinc, c_vinc, c_hinc;
	u32 c_vstart, c_hstart;

	src_c_xres = src_xres;
	src_c_yres = src_yres;
	dst_c_xres = dst_xres;
	dst_c_yres = dst_yres;

	c_vstart = 0;
	c_hstart = 0;

	/* adjusपंचांगents क्रम source chroma location */
	अगर (src_क्रमmat == BUF_FMT_YUV420) अणु
		/* vertical input chroma position adjusपंचांगent */
		चयन (src_chroma_loc) अणु
		हाल PSC_LOC_HORZ_0_VERT_1_OVER_4:
		हाल PSC_LOC_HORZ_1_OVER_4_VERT_1_OVER_4:
			/*
			 * move chroma up to first luma line
			 * (1/4 chroma input line spacing)
			 */
			c_vstart -= (1 << (PSC_PHASE_FRACTION_BITS - 2));
			अवरोध;
		हाल PSC_LOC_HORZ_0_VERT_1_OVER_2:
		हाल PSC_LOC_HORZ_1_OVER_4_VERT_1_OVER_2:
			/*
			 * move chroma up to first luma line
			 * (1/2 chroma input line spacing)
			 */
			c_vstart -= (1 << (PSC_PHASE_FRACTION_BITS - 1));
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		/* horizontal input chroma position adjusपंचांगent */
		चयन (src_chroma_loc) अणु
		हाल PSC_LOC_HORZ_1_OVER_4_VERT_1_OVER_4:
		हाल PSC_LOC_HORZ_1_OVER_4_VERT_0:
		हाल PSC_LOC_HORZ_1_OVER_4_VERT_1_OVER_2:
			/* move chroma left 1/4 chroma input sample spacing */
			c_hstart -= (1 << (PSC_PHASE_FRACTION_BITS - 2));
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	/* adjusपंचांगents to chroma resolution */
	अगर (src_क्रमmat == BUF_FMT_YUV420) अणु
		src_c_xres >>= 1;
		src_c_yres >>= 1;
	पूर्ण अन्यथा अगर (src_क्रमmat == BUF_FMT_YUV422) अणु
		src_c_xres >>= 1;
	पूर्ण

	अगर (dst_क्रमmat == BUF_FMT_YUV422)
		dst_c_xres >>= 1;

	l_vinc = ((src_yres << 13) + (dst_yres >> 1)) / dst_yres;
	c_vinc = ((src_c_yres << 13) + (dst_c_yres >> 1)) / dst_c_yres;
	l_hinc = ((src_xres << 13) + (dst_xres >> 1)) / dst_xres;
	c_hinc = ((src_c_xres << 13) + (dst_c_xres >> 1)) / dst_c_xres;

	/* save chroma start phase */
	ch->c_vstart = c_vstart;
	ch->c_hstart = c_hstart;

	dcss_scaler_ग_लिखो(ch, 0, DCSS_SCALER_V_LUM_START);
	dcss_scaler_ग_लिखो(ch, l_vinc, DCSS_SCALER_V_LUM_INC);

	dcss_scaler_ग_लिखो(ch, 0, DCSS_SCALER_H_LUM_START);
	dcss_scaler_ग_लिखो(ch, l_hinc, DCSS_SCALER_H_LUM_INC);

	dcss_scaler_ग_लिखो(ch, c_vstart, DCSS_SCALER_V_CHR_START);
	dcss_scaler_ग_लिखो(ch, c_vinc, DCSS_SCALER_V_CHR_INC);

	dcss_scaler_ग_लिखो(ch, c_hstart, DCSS_SCALER_H_CHR_START);
	dcss_scaler_ग_लिखो(ch, c_hinc, DCSS_SCALER_H_CHR_INC);
पूर्ण

पूर्णांक dcss_scaler_get_min_max_ratios(काष्ठा dcss_scaler *scl, पूर्णांक ch_num,
				   पूर्णांक *min, पूर्णांक *max)
अणु
	*min = upscale_fp(dcss_scaler_factors[ch_num].upscale, 16);
	*max = करोwnscale_fp(dcss_scaler_factors[ch_num].करोwnscale, 16);

	वापस 0;
पूर्ण

अटल व्योम dcss_scaler_program_5_coef_set(काष्ठा dcss_scaler_ch *ch,
					   पूर्णांक base_addr,
					   पूर्णांक coef[][PSC_NUM_TAPS])
अणु
	पूर्णांक i, phase;

	क्रम (i = 0; i < PSC_STORED_PHASES; i++) अणु
		dcss_scaler_ग_लिखो(ch, ((coef[i][1] & 0xfff) << 16 |
				       (coef[i][2] & 0xfff) << 4  |
				       (coef[i][3] & 0xf00) >> 8),
				  base_addr + i * माप(u32));
		dcss_scaler_ग_लिखो(ch, ((coef[i][3] & 0x0ff) << 20 |
				       (coef[i][4] & 0xfff) << 8  |
				       (coef[i][5] & 0xff0) >> 4),
				  base_addr + 0x40 + i * माप(u32));
		dcss_scaler_ग_लिखो(ch, ((coef[i][5] & 0x00f) << 24),
				  base_addr + 0x80 + i * माप(u32));
	पूर्ण

	/* reverse both phase and tap orderings */
	क्रम (phase = (PSC_NUM_PHASES >> 1) - 1;
			i < PSC_NUM_PHASES; i++, phase--) अणु
		dcss_scaler_ग_लिखो(ch, ((coef[phase][5] & 0xfff) << 16 |
				       (coef[phase][4] & 0xfff) << 4  |
				       (coef[phase][3] & 0xf00) >> 8),
				  base_addr + i * माप(u32));
		dcss_scaler_ग_लिखो(ch, ((coef[phase][3] & 0x0ff) << 20 |
				       (coef[phase][2] & 0xfff) << 8  |
				       (coef[phase][1] & 0xff0) >> 4),
				  base_addr + 0x40 + i * माप(u32));
		dcss_scaler_ग_लिखो(ch, ((coef[phase][1] & 0x00f) << 24),
				  base_addr + 0x80 + i * माप(u32));
	पूर्ण
पूर्ण

अटल व्योम dcss_scaler_program_7_coef_set(काष्ठा dcss_scaler_ch *ch,
					   पूर्णांक base_addr,
					   पूर्णांक coef[][PSC_NUM_TAPS])
अणु
	पूर्णांक i, phase;

	क्रम (i = 0; i < PSC_STORED_PHASES; i++) अणु
		dcss_scaler_ग_लिखो(ch, ((coef[i][0] & 0xfff) << 16 |
				       (coef[i][1] & 0xfff) << 4  |
				       (coef[i][2] & 0xf00) >> 8),
				  base_addr + i * माप(u32));
		dcss_scaler_ग_लिखो(ch, ((coef[i][2] & 0x0ff) << 20 |
				       (coef[i][3] & 0xfff) << 8  |
				       (coef[i][4] & 0xff0) >> 4),
				  base_addr + 0x40 + i * माप(u32));
		dcss_scaler_ग_लिखो(ch, ((coef[i][4] & 0x00f) << 24 |
				       (coef[i][5] & 0xfff) << 12 |
				       (coef[i][6] & 0xfff)),
				  base_addr + 0x80 + i * माप(u32));
	पूर्ण

	/* reverse both phase and tap orderings */
	क्रम (phase = (PSC_NUM_PHASES >> 1) - 1;
			i < PSC_NUM_PHASES; i++, phase--) अणु
		dcss_scaler_ग_लिखो(ch, ((coef[phase][6] & 0xfff) << 16 |
				       (coef[phase][5] & 0xfff) << 4  |
				       (coef[phase][4] & 0xf00) >> 8),
				  base_addr + i * माप(u32));
		dcss_scaler_ग_लिखो(ch, ((coef[phase][4] & 0x0ff) << 20 |
				       (coef[phase][3] & 0xfff) << 8  |
				       (coef[phase][2] & 0xff0) >> 4),
				  base_addr + 0x40 + i * माप(u32));
		dcss_scaler_ग_लिखो(ch, ((coef[phase][2] & 0x00f) << 24 |
				       (coef[phase][1] & 0xfff) << 12 |
				       (coef[phase][0] & 0xfff)),
				  base_addr + 0x80 + i * माप(u32));
	पूर्ण
पूर्ण

अटल व्योम dcss_scaler_yuv_coef_set(काष्ठा dcss_scaler_ch *ch,
				     क्रमागत buffer_क्रमmat src_क्रमmat,
				     क्रमागत buffer_क्रमmat dst_क्रमmat,
				     bool use_5_taps,
				     पूर्णांक src_xres, पूर्णांक src_yres, पूर्णांक dst_xres,
				     पूर्णांक dst_yres)
अणु
	पूर्णांक coef[PSC_STORED_PHASES][PSC_NUM_TAPS];
	bool program_5_taps = use_5_taps ||
			      (dst_क्रमmat == BUF_FMT_YUV422 &&
			       src_क्रमmat == BUF_FMT_ARGB8888_YUV444);

	/* horizontal luma */
	dcss_scaler_filter_design(src_xres, dst_xres, false,
				  src_xres == dst_xres, coef,
				  ch->use_nn_पूर्णांकerpolation);
	dcss_scaler_program_7_coef_set(ch, DCSS_SCALER_COEF_HLUM, coef);

	/* vertical luma */
	dcss_scaler_filter_design(src_yres, dst_yres, program_5_taps,
				  src_yres == dst_yres, coef,
				  ch->use_nn_पूर्णांकerpolation);

	अगर (program_5_taps)
		dcss_scaler_program_5_coef_set(ch, DCSS_SCALER_COEF_VLUM, coef);
	अन्यथा
		dcss_scaler_program_7_coef_set(ch, DCSS_SCALER_COEF_VLUM, coef);

	/* adjust chroma resolution */
	अगर (src_क्रमmat != BUF_FMT_ARGB8888_YUV444)
		src_xres >>= 1;
	अगर (src_क्रमmat == BUF_FMT_YUV420)
		src_yres >>= 1;
	अगर (dst_क्रमmat != BUF_FMT_ARGB8888_YUV444)
		dst_xres >>= 1;
	अगर (dst_क्रमmat == BUF_FMT_YUV420) /* should not happen */
		dst_yres >>= 1;

	/* horizontal chroma */
	dcss_scaler_filter_design(src_xres, dst_xres, false,
				  (src_xres == dst_xres) && (ch->c_hstart == 0),
				  coef, ch->use_nn_पूर्णांकerpolation);

	dcss_scaler_program_7_coef_set(ch, DCSS_SCALER_COEF_HCHR, coef);

	/* vertical chroma */
	dcss_scaler_filter_design(src_yres, dst_yres, program_5_taps,
				  (src_yres == dst_yres) && (ch->c_vstart == 0),
				  coef, ch->use_nn_पूर्णांकerpolation);
	अगर (program_5_taps)
		dcss_scaler_program_5_coef_set(ch, DCSS_SCALER_COEF_VCHR, coef);
	अन्यथा
		dcss_scaler_program_7_coef_set(ch, DCSS_SCALER_COEF_VCHR, coef);
पूर्ण

अटल व्योम dcss_scaler_rgb_coef_set(काष्ठा dcss_scaler_ch *ch,
				     पूर्णांक src_xres, पूर्णांक src_yres, पूर्णांक dst_xres,
				     पूर्णांक dst_yres)
अणु
	पूर्णांक coef[PSC_STORED_PHASES][PSC_NUM_TAPS];

	/* horizontal RGB */
	dcss_scaler_filter_design(src_xres, dst_xres, false,
				  src_xres == dst_xres, coef,
				  ch->use_nn_पूर्णांकerpolation);
	dcss_scaler_program_7_coef_set(ch, DCSS_SCALER_COEF_HLUM, coef);

	/* vertical RGB */
	dcss_scaler_filter_design(src_yres, dst_yres, false,
				  src_yres == dst_yres, coef,
				  ch->use_nn_पूर्णांकerpolation);
	dcss_scaler_program_7_coef_set(ch, DCSS_SCALER_COEF_VLUM, coef);
पूर्ण

अटल व्योम dcss_scaler_set_rgb10_order(काष्ठा dcss_scaler_ch *ch,
					स्थिर काष्ठा drm_क्रमmat_info *क्रमmat)
अणु
	u32 a2r10g10b10_क्रमmat;

	अगर (क्रमmat->is_yuv)
		वापस;

	ch->sdata_ctrl &= ~A2R10G10B10_FORMAT_MASK;

	अगर (क्रमmat->depth != 30)
		वापस;

	चयन (क्रमmat->क्रमmat) अणु
	हाल DRM_FORMAT_ARGB2101010:
	हाल DRM_FORMAT_XRGB2101010:
		a2r10g10b10_क्रमmat = 0;
		अवरोध;

	हाल DRM_FORMAT_ABGR2101010:
	हाल DRM_FORMAT_XBGR2101010:
		a2r10g10b10_क्रमmat = 5;
		अवरोध;

	हाल DRM_FORMAT_RGBA1010102:
	हाल DRM_FORMAT_RGBX1010102:
		a2r10g10b10_क्रमmat = 6;
		अवरोध;

	हाल DRM_FORMAT_BGRA1010102:
	हाल DRM_FORMAT_BGRX1010102:
		a2r10g10b10_क्रमmat = 11;
		अवरोध;

	शेष:
		a2r10g10b10_क्रमmat = 0;
		अवरोध;
	पूर्ण

	ch->sdata_ctrl |= a2r10g10b10_क्रमmat << A2R10G10B10_FORMAT_POS;
पूर्ण

व्योम dcss_scaler_set_filter(काष्ठा dcss_scaler *scl, पूर्णांक ch_num,
			    क्रमागत drm_scaling_filter scaling_filter)
अणु
	काष्ठा dcss_scaler_ch *ch = &scl->ch[ch_num];

	ch->use_nn_पूर्णांकerpolation = scaling_filter == DRM_SCALING_FILTER_NEAREST_NEIGHBOR;
पूर्ण

व्योम dcss_scaler_setup(काष्ठा dcss_scaler *scl, पूर्णांक ch_num,
		       स्थिर काष्ठा drm_क्रमmat_info *क्रमmat,
		       पूर्णांक src_xres, पूर्णांक src_yres, पूर्णांक dst_xres, पूर्णांक dst_yres,
		       u32 vrefresh_hz)
अणु
	काष्ठा dcss_scaler_ch *ch = &scl->ch[ch_num];
	अचिन्हित पूर्णांक pixel_depth = 0;
	bool rtr_8line_en = false;
	bool use_5_taps = false;
	क्रमागत buffer_क्रमmat src_क्रमmat = BUF_FMT_ARGB8888_YUV444;
	क्रमागत buffer_क्रमmat dst_क्रमmat = BUF_FMT_ARGB8888_YUV444;
	u32 pix_क्रमmat = क्रमmat->क्रमmat;

	अगर (क्रमmat->is_yuv) अणु
		dcss_scaler_yuv_enable(ch, true);

		अगर (pix_क्रमmat == DRM_FORMAT_NV12 ||
		    pix_क्रमmat == DRM_FORMAT_NV21) अणु
			rtr_8line_en = true;
			src_क्रमmat = BUF_FMT_YUV420;
		पूर्ण अन्यथा अगर (pix_क्रमmat == DRM_FORMAT_UYVY ||
			   pix_क्रमmat == DRM_FORMAT_VYUY ||
			   pix_क्रमmat == DRM_FORMAT_YUYV ||
			   pix_क्रमmat == DRM_FORMAT_YVYU) अणु
			src_क्रमmat = BUF_FMT_YUV422;
		पूर्ण

		use_5_taps = !rtr_8line_en;
	पूर्ण अन्यथा अणु
		dcss_scaler_yuv_enable(ch, false);

		pixel_depth = क्रमmat->depth;
	पूर्ण

	dcss_scaler_fractions_set(ch, src_xres, src_yres, dst_xres,
				  dst_yres, src_क्रमmat, dst_क्रमmat,
				  PSC_LOC_HORZ_0_VERT_1_OVER_4);

	अगर (क्रमmat->is_yuv)
		dcss_scaler_yuv_coef_set(ch, src_क्रमmat, dst_क्रमmat,
					 use_5_taps, src_xres, src_yres,
					 dst_xres, dst_yres);
	अन्यथा
		dcss_scaler_rgb_coef_set(ch, src_xres, src_yres,
					 dst_xres, dst_yres);

	dcss_scaler_rtr_8lines_enable(ch, rtr_8line_en);
	dcss_scaler_bit_depth_set(ch, pixel_depth);
	dcss_scaler_set_rgb10_order(ch, क्रमmat);
	dcss_scaler_क्रमmat_set(ch, src_क्रमmat, dst_क्रमmat);
	dcss_scaler_res_set(ch, src_xres, src_yres, dst_xres, dst_yres,
			    pix_क्रमmat, dst_क्रमmat);
पूर्ण

/* This function will be called from पूर्णांकerrupt context. */
व्योम dcss_scaler_ग_लिखो_sclctrl(काष्ठा dcss_scaler *scl)
अणु
	पूर्णांक chnum;

	dcss_ctxld_निश्चित_locked(scl->ctxld);

	क्रम (chnum = 0; chnum < 3; chnum++) अणु
		काष्ठा dcss_scaler_ch *ch = &scl->ch[chnum];

		अगर (ch->scaler_ctrl_chgd) अणु
			dcss_ctxld_ग_लिखो_irqsafe(scl->ctxld, scl->ctx_id,
						 ch->scaler_ctrl,
						 ch->base_ofs +
						 DCSS_SCALER_CTRL);
			ch->scaler_ctrl_chgd = false;
		पूर्ण
	पूर्ण
पूर्ण
