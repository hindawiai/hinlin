<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "dsi_phy.h"

#घोषणा S_DIV_ROUND_UP(n, d)	\
	(((n) >= 0) ? (((n) + (d) - 1) / (d)) : (((n) - (d) + 1) / (d)))

अटल अंतरभूत s32 linear_पूर्णांकer(s32 पंचांगax, s32 पंचांगin, s32 percent,
				s32 min_result, bool even)
अणु
	s32 v;

	v = (पंचांगax - पंचांगin) * percent;
	v = S_DIV_ROUND_UP(v, 100) + पंचांगin;
	अगर (even && (v & 0x1))
		वापस max_t(s32, min_result, v - 1);
	अन्यथा
		वापस max_t(s32, min_result, v);
पूर्ण

अटल व्योम dsi_dphy_timing_calc_clk_zero(काष्ठा msm_dsi_dphy_timing *timing,
					s32 ui, s32 coeff, s32 pcnt)
अणु
	s32 पंचांगax, पंचांगin, clk_z;
	s32 temp;

	/* reset */
	temp = 300 * coeff - ((timing->clk_prepare >> 1) + 1) * 2 * ui;
	पंचांगin = S_DIV_ROUND_UP(temp, ui) - 2;
	अगर (पंचांगin > 255) अणु
		पंचांगax = 511;
		clk_z = linear_पूर्णांकer(2 * पंचांगin, पंचांगin, pcnt, 0, true);
	पूर्ण अन्यथा अणु
		पंचांगax = 255;
		clk_z = linear_पूर्णांकer(पंचांगax, पंचांगin, pcnt, 0, true);
	पूर्ण

	/* adjust */
	temp = (timing->hs_rqst + timing->clk_prepare + clk_z) & 0x7;
	timing->clk_zero = clk_z + 8 - temp;
पूर्ण

पूर्णांक msm_dsi_dphy_timing_calc(काष्ठा msm_dsi_dphy_timing *timing,
			     काष्ठा msm_dsi_phy_clk_request *clk_req)
अणु
	स्थिर अचिन्हित दीर्घ bit_rate = clk_req->bitclk_rate;
	स्थिर अचिन्हित दीर्घ esc_rate = clk_req->escclk_rate;
	s32 ui, lpx;
	s32 पंचांगax, पंचांगin;
	s32 pcnt0 = 10;
	s32 pcnt1 = (bit_rate > 1200000000) ? 15 : 10;
	s32 pcnt2 = 10;
	s32 pcnt3 = (bit_rate > 180000000) ? 10 : 40;
	s32 coeff = 1000; /* Precision, should aव्योम overflow */
	s32 temp;

	अगर (!bit_rate || !esc_rate)
		वापस -EINVAL;

	ui = mult_frac(NSEC_PER_MSEC, coeff, bit_rate / 1000);
	lpx = mult_frac(NSEC_PER_MSEC, coeff, esc_rate / 1000);

	पंचांगax = S_DIV_ROUND_UP(95 * coeff, ui) - 2;
	पंचांगin = S_DIV_ROUND_UP(38 * coeff, ui) - 2;
	timing->clk_prepare = linear_पूर्णांकer(पंचांगax, पंचांगin, pcnt0, 0, true);

	temp = lpx / ui;
	अगर (temp & 0x1)
		timing->hs_rqst = temp;
	अन्यथा
		timing->hs_rqst = max_t(s32, 0, temp - 2);

	/* Calculate clk_zero after clk_prepare and hs_rqst */
	dsi_dphy_timing_calc_clk_zero(timing, ui, coeff, pcnt2);

	temp = 105 * coeff + 12 * ui - 20 * coeff;
	पंचांगax = S_DIV_ROUND_UP(temp, ui) - 2;
	पंचांगin = S_DIV_ROUND_UP(60 * coeff, ui) - 2;
	timing->clk_trail = linear_पूर्णांकer(पंचांगax, पंचांगin, pcnt3, 0, true);

	temp = 85 * coeff + 6 * ui;
	पंचांगax = S_DIV_ROUND_UP(temp, ui) - 2;
	temp = 40 * coeff + 4 * ui;
	पंचांगin = S_DIV_ROUND_UP(temp, ui) - 2;
	timing->hs_prepare = linear_पूर्णांकer(पंचांगax, पंचांगin, pcnt1, 0, true);

	पंचांगax = 255;
	temp = ((timing->hs_prepare >> 1) + 1) * 2 * ui + 2 * ui;
	temp = 145 * coeff + 10 * ui - temp;
	पंचांगin = S_DIV_ROUND_UP(temp, ui) - 2;
	timing->hs_zero = linear_पूर्णांकer(पंचांगax, पंचांगin, pcnt2, 24, true);

	temp = 105 * coeff + 12 * ui - 20 * coeff;
	पंचांगax = S_DIV_ROUND_UP(temp, ui) - 2;
	temp = 60 * coeff + 4 * ui;
	पंचांगin = DIV_ROUND_UP(temp, ui) - 2;
	timing->hs_trail = linear_पूर्णांकer(पंचांगax, पंचांगin, pcnt3, 0, true);

	पंचांगax = 255;
	पंचांगin = S_DIV_ROUND_UP(100 * coeff, ui) - 2;
	timing->hs_निकास = linear_पूर्णांकer(पंचांगax, पंचांगin, pcnt2, 0, true);

	पंचांगax = 63;
	temp = ((timing->hs_निकास >> 1) + 1) * 2 * ui;
	temp = 60 * coeff + 52 * ui - 24 * ui - temp;
	पंचांगin = S_DIV_ROUND_UP(temp, 8 * ui) - 1;
	timing->shared_timings.clk_post = linear_पूर्णांकer(पंचांगax, पंचांगin, pcnt2, 0,
						       false);
	पंचांगax = 63;
	temp = ((timing->clk_prepare >> 1) + 1) * 2 * ui;
	temp += ((timing->clk_zero >> 1) + 1) * 2 * ui;
	temp += 8 * ui + lpx;
	पंचांगin = S_DIV_ROUND_UP(temp, 8 * ui) - 1;
	अगर (पंचांगin > पंचांगax) अणु
		temp = linear_पूर्णांकer(2 * पंचांगax, पंचांगin, pcnt2, 0, false);
		timing->shared_timings.clk_pre = temp >> 1;
		timing->shared_timings.clk_pre_inc_by_2 = true;
	पूर्ण अन्यथा अणु
		timing->shared_timings.clk_pre =
				linear_पूर्णांकer(पंचांगax, पंचांगin, pcnt2, 0, false);
		timing->shared_timings.clk_pre_inc_by_2 = false;
	पूर्ण

	timing->ta_go = 3;
	timing->ta_sure = 0;
	timing->ta_get = 4;

	DBG("PHY timings: %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d",
		timing->shared_timings.clk_pre, timing->shared_timings.clk_post,
		timing->shared_timings.clk_pre_inc_by_2, timing->clk_zero,
		timing->clk_trail, timing->clk_prepare, timing->hs_निकास,
		timing->hs_zero, timing->hs_prepare, timing->hs_trail,
		timing->hs_rqst);

	वापस 0;
पूर्ण

पूर्णांक msm_dsi_dphy_timing_calc_v2(काष्ठा msm_dsi_dphy_timing *timing,
				काष्ठा msm_dsi_phy_clk_request *clk_req)
अणु
	स्थिर अचिन्हित दीर्घ bit_rate = clk_req->bitclk_rate;
	स्थिर अचिन्हित दीर्घ esc_rate = clk_req->escclk_rate;
	s32 ui, ui_x8;
	s32 पंचांगax, पंचांगin;
	s32 pcnt0 = 50;
	s32 pcnt1 = 50;
	s32 pcnt2 = 10;
	s32 pcnt3 = 30;
	s32 pcnt4 = 10;
	s32 pcnt5 = 2;
	s32 coeff = 1000; /* Precision, should aव्योम overflow */
	s32 hb_en, hb_en_ckln, pd_ckln, pd;
	s32 val, val_ckln;
	s32 temp;

	अगर (!bit_rate || !esc_rate)
		वापस -EINVAL;

	timing->hs_halfbyte_en = 0;
	hb_en = 0;
	timing->hs_halfbyte_en_ckln = 0;
	hb_en_ckln = 0;
	timing->hs_prep_dly_ckln = (bit_rate > 100000000) ? 0 : 3;
	pd_ckln = timing->hs_prep_dly_ckln;
	timing->hs_prep_dly = (bit_rate > 120000000) ? 0 : 1;
	pd = timing->hs_prep_dly;

	val = (hb_en << 2) + (pd << 1);
	val_ckln = (hb_en_ckln << 2) + (pd_ckln << 1);

	ui = mult_frac(NSEC_PER_MSEC, coeff, bit_rate / 1000);
	ui_x8 = ui << 3;

	temp = S_DIV_ROUND_UP(38 * coeff - val_ckln * ui, ui_x8);
	पंचांगin = max_t(s32, temp, 0);
	temp = (95 * coeff - val_ckln * ui) / ui_x8;
	पंचांगax = max_t(s32, temp, 0);
	timing->clk_prepare = linear_पूर्णांकer(पंचांगax, पंचांगin, pcnt0, 0, false);

	temp = 300 * coeff - ((timing->clk_prepare << 3) + val_ckln) * ui;
	पंचांगin = S_DIV_ROUND_UP(temp - 11 * ui, ui_x8) - 3;
	पंचांगax = (पंचांगin > 255) ? 511 : 255;
	timing->clk_zero = linear_पूर्णांकer(पंचांगax, पंचांगin, pcnt5, 0, false);

	पंचांगin = DIV_ROUND_UP(60 * coeff + 3 * ui, ui_x8);
	temp = 105 * coeff + 12 * ui - 20 * coeff;
	पंचांगax = (temp + 3 * ui) / ui_x8;
	timing->clk_trail = linear_पूर्णांकer(पंचांगax, पंचांगin, pcnt3, 0, false);

	temp = S_DIV_ROUND_UP(40 * coeff + 4 * ui - val * ui, ui_x8);
	पंचांगin = max_t(s32, temp, 0);
	temp = (85 * coeff + 6 * ui - val * ui) / ui_x8;
	पंचांगax = max_t(s32, temp, 0);
	timing->hs_prepare = linear_पूर्णांकer(पंचांगax, पंचांगin, pcnt1, 0, false);

	temp = 145 * coeff + 10 * ui - ((timing->hs_prepare << 3) + val) * ui;
	पंचांगin = S_DIV_ROUND_UP(temp - 11 * ui, ui_x8) - 3;
	पंचांगax = 255;
	timing->hs_zero = linear_पूर्णांकer(पंचांगax, पंचांगin, pcnt4, 0, false);

	पंचांगin = DIV_ROUND_UP(60 * coeff + 4 * ui + 3 * ui, ui_x8);
	temp = 105 * coeff + 12 * ui - 20 * coeff;
	पंचांगax = (temp + 3 * ui) / ui_x8;
	timing->hs_trail = linear_पूर्णांकer(पंचांगax, पंचांगin, pcnt3, 0, false);

	temp = 50 * coeff + ((hb_en << 2) - 8) * ui;
	timing->hs_rqst = S_DIV_ROUND_UP(temp, ui_x8);

	पंचांगin = DIV_ROUND_UP(100 * coeff, ui_x8) - 1;
	पंचांगax = 255;
	timing->hs_निकास = linear_पूर्णांकer(पंचांगax, पंचांगin, pcnt2, 0, false);

	temp = 50 * coeff + ((hb_en_ckln << 2) - 8) * ui;
	timing->hs_rqst_ckln = S_DIV_ROUND_UP(temp, ui_x8);

	temp = 60 * coeff + 52 * ui - 43 * ui;
	पंचांगin = DIV_ROUND_UP(temp, ui_x8) - 1;
	पंचांगax = 63;
	timing->shared_timings.clk_post =
				linear_पूर्णांकer(पंचांगax, पंचांगin, pcnt2, 0, false);

	temp = 8 * ui + ((timing->clk_prepare << 3) + val_ckln) * ui;
	temp += (((timing->clk_zero + 3) << 3) + 11 - (pd_ckln << 1)) * ui;
	temp += hb_en_ckln ? (((timing->hs_rqst_ckln << 3) + 4) * ui) :
				(((timing->hs_rqst_ckln << 3) + 8) * ui);
	पंचांगin = S_DIV_ROUND_UP(temp, ui_x8) - 1;
	पंचांगax = 63;
	अगर (पंचांगin > पंचांगax) अणु
		temp = linear_पूर्णांकer(पंचांगax << 1, पंचांगin, pcnt2, 0, false);
		timing->shared_timings.clk_pre = temp >> 1;
		timing->shared_timings.clk_pre_inc_by_2 = 1;
	पूर्ण अन्यथा अणु
		timing->shared_timings.clk_pre =
				linear_पूर्णांकer(पंचांगax, पंचांगin, pcnt2, 0, false);
		timing->shared_timings.clk_pre_inc_by_2 = 0;
	पूर्ण

	timing->ta_go = 3;
	timing->ta_sure = 0;
	timing->ta_get = 4;

	DBG("%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d",
	    timing->shared_timings.clk_pre, timing->shared_timings.clk_post,
	    timing->shared_timings.clk_pre_inc_by_2, timing->clk_zero,
	    timing->clk_trail, timing->clk_prepare, timing->hs_निकास,
	    timing->hs_zero, timing->hs_prepare, timing->hs_trail,
	    timing->hs_rqst, timing->hs_rqst_ckln, timing->hs_halfbyte_en,
	    timing->hs_halfbyte_en_ckln, timing->hs_prep_dly,
	    timing->hs_prep_dly_ckln);

	वापस 0;
पूर्ण

पूर्णांक msm_dsi_dphy_timing_calc_v3(काष्ठा msm_dsi_dphy_timing *timing,
	काष्ठा msm_dsi_phy_clk_request *clk_req)
अणु
	स्थिर अचिन्हित दीर्घ bit_rate = clk_req->bitclk_rate;
	स्थिर अचिन्हित दीर्घ esc_rate = clk_req->escclk_rate;
	s32 ui, ui_x8;
	s32 पंचांगax, पंचांगin;
	s32 pcnt0 = 50;
	s32 pcnt1 = 50;
	s32 pcnt2 = 10;
	s32 pcnt3 = 30;
	s32 pcnt4 = 10;
	s32 pcnt5 = 2;
	s32 coeff = 1000; /* Precision, should aव्योम overflow */
	s32 hb_en, hb_en_ckln;
	s32 temp;

	अगर (!bit_rate || !esc_rate)
		वापस -EINVAL;

	timing->hs_halfbyte_en = 0;
	hb_en = 0;
	timing->hs_halfbyte_en_ckln = 0;
	hb_en_ckln = 0;

	ui = mult_frac(NSEC_PER_MSEC, coeff, bit_rate / 1000);
	ui_x8 = ui << 3;

	temp = S_DIV_ROUND_UP(38 * coeff, ui_x8);
	पंचांगin = max_t(s32, temp, 0);
	temp = (95 * coeff) / ui_x8;
	पंचांगax = max_t(s32, temp, 0);
	timing->clk_prepare = linear_पूर्णांकer(पंचांगax, पंचांगin, pcnt0, 0, false);

	temp = 300 * coeff - (timing->clk_prepare << 3) * ui;
	पंचांगin = S_DIV_ROUND_UP(temp, ui_x8) - 1;
	पंचांगax = (पंचांगin > 255) ? 511 : 255;
	timing->clk_zero = linear_पूर्णांकer(पंचांगax, पंचांगin, pcnt5, 0, false);

	पंचांगin = DIV_ROUND_UP(60 * coeff + 3 * ui, ui_x8);
	temp = 105 * coeff + 12 * ui - 20 * coeff;
	पंचांगax = (temp + 3 * ui) / ui_x8;
	timing->clk_trail = linear_पूर्णांकer(पंचांगax, पंचांगin, pcnt3, 0, false);

	temp = S_DIV_ROUND_UP(40 * coeff + 4 * ui, ui_x8);
	पंचांगin = max_t(s32, temp, 0);
	temp = (85 * coeff + 6 * ui) / ui_x8;
	पंचांगax = max_t(s32, temp, 0);
	timing->hs_prepare = linear_पूर्णांकer(पंचांगax, पंचांगin, pcnt1, 0, false);

	temp = 145 * coeff + 10 * ui - (timing->hs_prepare << 3) * ui;
	पंचांगin = S_DIV_ROUND_UP(temp, ui_x8) - 1;
	पंचांगax = 255;
	timing->hs_zero = linear_पूर्णांकer(पंचांगax, पंचांगin, pcnt4, 0, false);

	पंचांगin = DIV_ROUND_UP(60 * coeff + 4 * ui, ui_x8) - 1;
	temp = 105 * coeff + 12 * ui - 20 * coeff;
	पंचांगax = (temp / ui_x8) - 1;
	timing->hs_trail = linear_पूर्णांकer(पंचांगax, पंचांगin, pcnt3, 0, false);

	temp = 50 * coeff + ((hb_en << 2) - 8) * ui;
	timing->hs_rqst = S_DIV_ROUND_UP(temp, ui_x8);

	पंचांगin = DIV_ROUND_UP(100 * coeff, ui_x8) - 1;
	पंचांगax = 255;
	timing->hs_निकास = linear_पूर्णांकer(पंचांगax, पंचांगin, pcnt2, 0, false);

	temp = 50 * coeff + ((hb_en_ckln << 2) - 8) * ui;
	timing->hs_rqst_ckln = S_DIV_ROUND_UP(temp, ui_x8);

	temp = 60 * coeff + 52 * ui - 43 * ui;
	पंचांगin = DIV_ROUND_UP(temp, ui_x8) - 1;
	पंचांगax = 63;
	timing->shared_timings.clk_post =
		linear_पूर्णांकer(पंचांगax, पंचांगin, pcnt2, 0, false);

	temp = 8 * ui + (timing->clk_prepare << 3) * ui;
	temp += (((timing->clk_zero + 3) << 3) + 11) * ui;
	temp += hb_en_ckln ? (((timing->hs_rqst_ckln << 3) + 4) * ui) :
		(((timing->hs_rqst_ckln << 3) + 8) * ui);
	पंचांगin = S_DIV_ROUND_UP(temp, ui_x8) - 1;
	पंचांगax = 63;
	अगर (पंचांगin > पंचांगax) अणु
		temp = linear_पूर्णांकer(पंचांगax << 1, पंचांगin, pcnt2, 0, false);
		timing->shared_timings.clk_pre = temp >> 1;
		timing->shared_timings.clk_pre_inc_by_2 = 1;
	पूर्ण अन्यथा अणु
		timing->shared_timings.clk_pre =
			linear_पूर्णांकer(पंचांगax, पंचांगin, pcnt2, 0, false);
			timing->shared_timings.clk_pre_inc_by_2 = 0;
	पूर्ण

	timing->ta_go = 3;
	timing->ta_sure = 0;
	timing->ta_get = 4;

	DBG("%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d",
		timing->shared_timings.clk_pre, timing->shared_timings.clk_post,
		timing->shared_timings.clk_pre_inc_by_2, timing->clk_zero,
		timing->clk_trail, timing->clk_prepare, timing->hs_निकास,
		timing->hs_zero, timing->hs_prepare, timing->hs_trail,
		timing->hs_rqst, timing->hs_rqst_ckln, timing->hs_halfbyte_en,
		timing->hs_halfbyte_en_ckln, timing->hs_prep_dly,
		timing->hs_prep_dly_ckln);

	वापस 0;
पूर्ण

पूर्णांक msm_dsi_dphy_timing_calc_v4(काष्ठा msm_dsi_dphy_timing *timing,
	काष्ठा msm_dsi_phy_clk_request *clk_req)
अणु
	स्थिर अचिन्हित दीर्घ bit_rate = clk_req->bitclk_rate;
	स्थिर अचिन्हित दीर्घ esc_rate = clk_req->escclk_rate;
	s32 ui, ui_x8;
	s32 पंचांगax, पंचांगin;
	s32 pcnt_clk_prep = 50;
	s32 pcnt_clk_zero = 2;
	s32 pcnt_clk_trail = 30;
	s32 pcnt_hs_prep = 50;
	s32 pcnt_hs_zero = 10;
	s32 pcnt_hs_trail = 30;
	s32 pcnt_hs_निकास = 10;
	s32 coeff = 1000; /* Precision, should aव्योम overflow */
	s32 hb_en;
	s32 temp;

	अगर (!bit_rate || !esc_rate)
		वापस -EINVAL;

	hb_en = 0;

	ui = mult_frac(NSEC_PER_MSEC, coeff, bit_rate / 1000);
	ui_x8 = ui << 3;

	/* TODO: verअगरy these calculations against latest करोwnstream driver
	 * everything except clk_post/clk_pre uses calculations from v3 based
	 * on the करोwnstream driver having the same calculations क्रम v3 and v4
	 */

	temp = S_DIV_ROUND_UP(38 * coeff, ui_x8);
	पंचांगin = max_t(s32, temp, 0);
	temp = (95 * coeff) / ui_x8;
	पंचांगax = max_t(s32, temp, 0);
	timing->clk_prepare = linear_पूर्णांकer(पंचांगax, पंचांगin, pcnt_clk_prep, 0, false);

	temp = 300 * coeff - (timing->clk_prepare << 3) * ui;
	पंचांगin = S_DIV_ROUND_UP(temp, ui_x8) - 1;
	पंचांगax = (पंचांगin > 255) ? 511 : 255;
	timing->clk_zero = linear_पूर्णांकer(पंचांगax, पंचांगin, pcnt_clk_zero, 0, false);

	पंचांगin = DIV_ROUND_UP(60 * coeff + 3 * ui, ui_x8);
	temp = 105 * coeff + 12 * ui - 20 * coeff;
	पंचांगax = (temp + 3 * ui) / ui_x8;
	timing->clk_trail = linear_पूर्णांकer(पंचांगax, पंचांगin, pcnt_clk_trail, 0, false);

	temp = S_DIV_ROUND_UP(40 * coeff + 4 * ui, ui_x8);
	पंचांगin = max_t(s32, temp, 0);
	temp = (85 * coeff + 6 * ui) / ui_x8;
	पंचांगax = max_t(s32, temp, 0);
	timing->hs_prepare = linear_पूर्णांकer(पंचांगax, पंचांगin, pcnt_hs_prep, 0, false);

	temp = 145 * coeff + 10 * ui - (timing->hs_prepare << 3) * ui;
	पंचांगin = S_DIV_ROUND_UP(temp, ui_x8) - 1;
	पंचांगax = 255;
	timing->hs_zero = linear_पूर्णांकer(पंचांगax, पंचांगin, pcnt_hs_zero, 0, false);

	पंचांगin = DIV_ROUND_UP(60 * coeff + 4 * ui, ui_x8) - 1;
	temp = 105 * coeff + 12 * ui - 20 * coeff;
	पंचांगax = (temp / ui_x8) - 1;
	timing->hs_trail = linear_पूर्णांकer(पंचांगax, पंचांगin, pcnt_hs_trail, 0, false);

	temp = 50 * coeff + ((hb_en << 2) - 8) * ui;
	timing->hs_rqst = S_DIV_ROUND_UP(temp, ui_x8);

	पंचांगin = DIV_ROUND_UP(100 * coeff, ui_x8) - 1;
	पंचांगax = 255;
	timing->hs_निकास = linear_पूर्णांकer(पंचांगax, पंचांगin, pcnt_hs_निकास, 0, false);

	/* recommended min
	 * = roundup((mipi_min_ns + t_hs_trail_ns)/(16*bit_clk_ns), 0) - 1
	 */
	temp = 60 * coeff + 52 * ui + + (timing->hs_trail + 1) * ui_x8;
	पंचांगin = DIV_ROUND_UP(temp, 16 * ui) - 1;
	पंचांगax = 255;
	timing->shared_timings.clk_post = linear_पूर्णांकer(पंचांगax, पंचांगin, 5, 0, false);

	/* recommended min
	 * val1 = (tlpx_ns + clk_prepare_ns + clk_zero_ns + hs_rqst_ns)
	 * val2 = (16 * bit_clk_ns)
	 * final = roundup(val1/val2, 0) - 1
	 */
	temp = 52 * coeff + (timing->clk_prepare + timing->clk_zero + 1) * ui_x8 + 54 * coeff;
	पंचांगin = DIV_ROUND_UP(temp, 16 * ui) - 1;
	पंचांगax = 255;
	timing->shared_timings.clk_pre = DIV_ROUND_UP((पंचांगax - पंचांगin) * 125, 10000) + पंचांगin;

	DBG("%d, %d, %d, %d, %d, %d, %d, %d, %d, %d",
		timing->shared_timings.clk_pre, timing->shared_timings.clk_post,
		timing->clk_zero, timing->clk_trail, timing->clk_prepare, timing->hs_निकास,
		timing->hs_zero, timing->hs_prepare, timing->hs_trail, timing->hs_rqst);

	वापस 0;
पूर्ण

अटल पूर्णांक dsi_phy_regulator_init(काष्ठा msm_dsi_phy *phy)
अणु
	काष्ठा regulator_bulk_data *s = phy->supplies;
	स्थिर काष्ठा dsi_reg_entry *regs = phy->cfg->reg_cfg.regs;
	काष्ठा device *dev = &phy->pdev->dev;
	पूर्णांक num = phy->cfg->reg_cfg.num;
	पूर्णांक i, ret;

	क्रम (i = 0; i < num; i++)
		s[i].supply = regs[i].name;

	ret = devm_regulator_bulk_get(dev, num, s);
	अगर (ret < 0) अणु
		अगर (ret != -EPROBE_DEFER) अणु
			DRM_DEV_ERROR(dev,
				      "%s: failed to init regulator, ret=%d\n",
				      __func__, ret);
		पूर्ण

		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम dsi_phy_regulator_disable(काष्ठा msm_dsi_phy *phy)
अणु
	काष्ठा regulator_bulk_data *s = phy->supplies;
	स्थिर काष्ठा dsi_reg_entry *regs = phy->cfg->reg_cfg.regs;
	पूर्णांक num = phy->cfg->reg_cfg.num;
	पूर्णांक i;

	DBG("");
	क्रम (i = num - 1; i >= 0; i--)
		अगर (regs[i].disable_load >= 0)
			regulator_set_load(s[i].consumer, regs[i].disable_load);

	regulator_bulk_disable(num, s);
पूर्ण

अटल पूर्णांक dsi_phy_regulator_enable(काष्ठा msm_dsi_phy *phy)
अणु
	काष्ठा regulator_bulk_data *s = phy->supplies;
	स्थिर काष्ठा dsi_reg_entry *regs = phy->cfg->reg_cfg.regs;
	काष्ठा device *dev = &phy->pdev->dev;
	पूर्णांक num = phy->cfg->reg_cfg.num;
	पूर्णांक ret, i;

	DBG("");
	क्रम (i = 0; i < num; i++) अणु
		अगर (regs[i].enable_load >= 0) अणु
			ret = regulator_set_load(s[i].consumer,
							regs[i].enable_load);
			अगर (ret < 0) अणु
				DRM_DEV_ERROR(dev,
					"regulator %d set op mode failed, %d\n",
					i, ret);
				जाओ fail;
			पूर्ण
		पूर्ण
	पूर्ण

	ret = regulator_bulk_enable(num, s);
	अगर (ret < 0) अणु
		DRM_DEV_ERROR(dev, "regulator enable failed, %d\n", ret);
		जाओ fail;
	पूर्ण

	वापस 0;

fail:
	क्रम (i--; i >= 0; i--)
		regulator_set_load(s[i].consumer, regs[i].disable_load);
	वापस ret;
पूर्ण

अटल पूर्णांक dsi_phy_enable_resource(काष्ठा msm_dsi_phy *phy)
अणु
	काष्ठा device *dev = &phy->pdev->dev;
	पूर्णांक ret;

	pm_runसमय_get_sync(dev);

	ret = clk_prepare_enable(phy->ahb_clk);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev, "%s: can't enable ahb clk, %d\n", __func__, ret);
		pm_runसमय_put_sync(dev);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम dsi_phy_disable_resource(काष्ठा msm_dsi_phy *phy)
अणु
	clk_disable_unprepare(phy->ahb_clk);
	pm_runसमय_put_स्वतःsuspend(&phy->pdev->dev);
पूर्ण

अटल स्थिर काष्ठा of_device_id dsi_phy_dt_match[] = अणु
#अगर_घोषित CONFIG_DRM_MSM_DSI_28NM_PHY
	अणु .compatible = "qcom,dsi-phy-28nm-hpm",
	  .data = &dsi_phy_28nm_hpm_cfgs पूर्ण,
	अणु .compatible = "qcom,dsi-phy-28nm-hpm-fam-b",
	  .data = &dsi_phy_28nm_hpm_famb_cfgs पूर्ण,
	अणु .compatible = "qcom,dsi-phy-28nm-lp",
	  .data = &dsi_phy_28nm_lp_cfgs पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_DRM_MSM_DSI_20NM_PHY
	अणु .compatible = "qcom,dsi-phy-20nm",
	  .data = &dsi_phy_20nm_cfgs पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_DRM_MSM_DSI_28NM_8960_PHY
	अणु .compatible = "qcom,dsi-phy-28nm-8960",
	  .data = &dsi_phy_28nm_8960_cfgs पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_DRM_MSM_DSI_14NM_PHY
	अणु .compatible = "qcom,dsi-phy-14nm",
	  .data = &dsi_phy_14nm_cfgs पूर्ण,
	अणु .compatible = "qcom,dsi-phy-14nm-660",
	  .data = &dsi_phy_14nm_660_cfgs पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_DRM_MSM_DSI_10NM_PHY
	अणु .compatible = "qcom,dsi-phy-10nm",
	  .data = &dsi_phy_10nm_cfgs पूर्ण,
	अणु .compatible = "qcom,dsi-phy-10nm-8998",
	  .data = &dsi_phy_10nm_8998_cfgs पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_DRM_MSM_DSI_7NM_PHY
	अणु .compatible = "qcom,dsi-phy-7nm",
	  .data = &dsi_phy_7nm_cfgs पूर्ण,
	अणु .compatible = "qcom,dsi-phy-7nm-8150",
	  .data = &dsi_phy_7nm_8150_cfgs पूर्ण,
#पूर्ण_अगर
	अणुपूर्ण
पूर्ण;

/*
 * Currently, we only support one SoC क्रम each PHY type. When we have multiple
 * SoCs क्रम the same PHY, we can try to make the index searching a bit more
 * clever.
 */
अटल पूर्णांक dsi_phy_get_id(काष्ठा msm_dsi_phy *phy)
अणु
	काष्ठा platक्रमm_device *pdev = phy->pdev;
	स्थिर काष्ठा msm_dsi_phy_cfg *cfg = phy->cfg;
	काष्ठा resource *res;
	पूर्णांक i;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "dsi_phy");
	अगर (!res)
		वापस -EINVAL;

	क्रम (i = 0; i < cfg->num_dsi_phy; i++) अणु
		अगर (cfg->io_start[i] == res->start)
			वापस i;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक dsi_phy_driver_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा msm_dsi_phy *phy;
	काष्ठा device *dev = &pdev->dev;
	स्थिर काष्ठा of_device_id *match;
	पूर्णांक ret;

	phy = devm_kzalloc(dev, माप(*phy), GFP_KERNEL);
	अगर (!phy)
		वापस -ENOMEM;

	match = of_match_node(dsi_phy_dt_match, dev->of_node);
	अगर (!match)
		वापस -ENODEV;

	phy->provided_घड़ीs = devm_kzalloc(dev,
			काष्ठा_size(phy->provided_घड़ीs, hws, NUM_PROVIDED_CLKS),
			GFP_KERNEL);
	अगर (!phy->provided_घड़ीs)
		वापस -ENOMEM;

	phy->provided_घड़ीs->num = NUM_PROVIDED_CLKS;

	phy->cfg = match->data;
	phy->pdev = pdev;

	phy->id = dsi_phy_get_id(phy);
	अगर (phy->id < 0) अणु
		ret = phy->id;
		DRM_DEV_ERROR(dev, "%s: couldn't identify PHY index, %d\n",
			__func__, ret);
		जाओ fail;
	पूर्ण

	phy->regulator_lकरो_mode = of_property_पढ़ो_bool(dev->of_node,
				"qcom,dsi-phy-regulator-ldo-mode");

	phy->base = msm_ioremap(pdev, "dsi_phy", "DSI_PHY");
	अगर (IS_ERR(phy->base)) अणु
		DRM_DEV_ERROR(dev, "%s: failed to map phy base\n", __func__);
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	phy->pll_base = msm_ioremap(pdev, "dsi_pll", "DSI_PLL");
	अगर (IS_ERR(phy->pll_base)) अणु
		DRM_DEV_ERROR(&pdev->dev, "%s: failed to map pll base\n", __func__);
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	अगर (phy->cfg->has_phy_lane) अणु
		phy->lane_base = msm_ioremap(pdev, "dsi_phy_lane", "DSI_PHY_LANE");
		अगर (IS_ERR(phy->lane_base)) अणु
			DRM_DEV_ERROR(&pdev->dev, "%s: failed to map phy lane base\n", __func__);
			ret = -ENOMEM;
			जाओ fail;
		पूर्ण
	पूर्ण

	अगर (phy->cfg->has_phy_regulator) अणु
		phy->reg_base = msm_ioremap(pdev, "dsi_phy_regulator", "DSI_PHY_REG");
		अगर (IS_ERR(phy->reg_base)) अणु
			DRM_DEV_ERROR(&pdev->dev, "%s: failed to map phy regulator base\n", __func__);
			ret = -ENOMEM;
			जाओ fail;
		पूर्ण
	पूर्ण

	ret = dsi_phy_regulator_init(phy);
	अगर (ret)
		जाओ fail;

	phy->ahb_clk = msm_clk_get(pdev, "iface");
	अगर (IS_ERR(phy->ahb_clk)) अणु
		DRM_DEV_ERROR(dev, "%s: Unable to get ahb clk\n", __func__);
		ret = PTR_ERR(phy->ahb_clk);
		जाओ fail;
	पूर्ण

	/* PLL init will call पूर्णांकo clk_रेजिस्टर which requires
	 * रेजिस्टर access, so we need to enable घातer and ahb घड़ी.
	 */
	ret = dsi_phy_enable_resource(phy);
	अगर (ret)
		जाओ fail;

	अगर (phy->cfg->ops.pll_init) अणु
		ret = phy->cfg->ops.pll_init(phy);
		अगर (ret) अणु
			DRM_DEV_INFO(dev,
				"%s: pll init failed: %d, need separate pll clk driver\n",
				__func__, ret);
			जाओ fail;
		पूर्ण
	पूर्ण

	ret = devm_of_clk_add_hw_provider(dev, of_clk_hw_onecell_get,
				     phy->provided_घड़ीs);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev, "%s: failed to register clk provider: %d\n", __func__, ret);
		जाओ fail;
	पूर्ण

	dsi_phy_disable_resource(phy);

	platक्रमm_set_drvdata(pdev, phy);

	वापस 0;

fail:
	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver dsi_phy_platक्रमm_driver = अणु
	.probe      = dsi_phy_driver_probe,
	.driver     = अणु
		.name   = "msm_dsi_phy",
		.of_match_table = dsi_phy_dt_match,
	पूर्ण,
पूर्ण;

व्योम __init msm_dsi_phy_driver_रेजिस्टर(व्योम)
अणु
	platक्रमm_driver_रेजिस्टर(&dsi_phy_platक्रमm_driver);
पूर्ण

व्योम __निकास msm_dsi_phy_driver_unरेजिस्टर(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&dsi_phy_platक्रमm_driver);
पूर्ण

पूर्णांक msm_dsi_phy_enable(काष्ठा msm_dsi_phy *phy,
			काष्ठा msm_dsi_phy_clk_request *clk_req)
अणु
	काष्ठा device *dev = &phy->pdev->dev;
	पूर्णांक ret;

	अगर (!phy || !phy->cfg->ops.enable)
		वापस -EINVAL;

	ret = dsi_phy_enable_resource(phy);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev, "%s: resource enable failed, %d\n",
			__func__, ret);
		जाओ res_en_fail;
	पूर्ण

	ret = dsi_phy_regulator_enable(phy);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev, "%s: regulator enable failed, %d\n",
			__func__, ret);
		जाओ reg_en_fail;
	पूर्ण

	ret = phy->cfg->ops.enable(phy, clk_req);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev, "%s: phy enable failed, %d\n", __func__, ret);
		जाओ phy_en_fail;
	पूर्ण

	/*
	 * Resetting DSI PHY silently changes its PLL रेजिस्टरs to reset status,
	 * which will confuse घड़ी driver and result in wrong output rate of
	 * link घड़ीs. Restore PLL status अगर its PLL is being used as घड़ी
	 * source.
	 */
	अगर (phy->useहाल != MSM_DSI_PHY_SLAVE) अणु
		ret = msm_dsi_phy_pll_restore_state(phy);
		अगर (ret) अणु
			DRM_DEV_ERROR(dev, "%s: failed to restore phy state, %d\n",
				__func__, ret);
			जाओ pll_restor_fail;
		पूर्ण
	पूर्ण

	वापस 0;

pll_restor_fail:
	अगर (phy->cfg->ops.disable)
		phy->cfg->ops.disable(phy);
phy_en_fail:
	dsi_phy_regulator_disable(phy);
reg_en_fail:
	dsi_phy_disable_resource(phy);
res_en_fail:
	वापस ret;
पूर्ण

व्योम msm_dsi_phy_disable(काष्ठा msm_dsi_phy *phy)
अणु
	अगर (!phy || !phy->cfg->ops.disable)
		वापस;

	phy->cfg->ops.disable(phy);

	dsi_phy_regulator_disable(phy);
	dsi_phy_disable_resource(phy);
पूर्ण

व्योम msm_dsi_phy_get_shared_timings(काष्ठा msm_dsi_phy *phy,
			काष्ठा msm_dsi_phy_shared_timings *shared_timings)
अणु
	स_नकल(shared_timings, &phy->timing.shared_timings,
	       माप(*shared_timings));
पूर्ण

व्योम msm_dsi_phy_set_useहाल(काष्ठा msm_dsi_phy *phy,
			     क्रमागत msm_dsi_phy_useहाल uc)
अणु
	अगर (phy)
		phy->useहाल = uc;
पूर्ण

पूर्णांक msm_dsi_phy_get_clk_provider(काष्ठा msm_dsi_phy *phy,
	काष्ठा clk **byte_clk_provider, काष्ठा clk **pixel_clk_provider)
अणु
	अगर (byte_clk_provider)
		*byte_clk_provider = phy->provided_घड़ीs->hws[DSI_BYTE_PLL_CLK]->clk;
	अगर (pixel_clk_provider)
		*pixel_clk_provider = phy->provided_घड़ीs->hws[DSI_PIXEL_PLL_CLK]->clk;

	वापस 0;
पूर्ण

व्योम msm_dsi_phy_pll_save_state(काष्ठा msm_dsi_phy *phy)
अणु
	अगर (phy->cfg->ops.save_pll_state) अणु
		phy->cfg->ops.save_pll_state(phy);
		phy->state_saved = true;
	पूर्ण
पूर्ण

पूर्णांक msm_dsi_phy_pll_restore_state(काष्ठा msm_dsi_phy *phy)
अणु
	पूर्णांक ret;

	अगर (phy->cfg->ops.restore_pll_state && phy->state_saved) अणु
		ret = phy->cfg->ops.restore_pll_state(phy);
		अगर (ret)
			वापस ret;

		phy->state_saved = false;
	पूर्ण

	वापस 0;
पूर्ण
