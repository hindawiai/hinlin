<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2012-2020, The Linux Foundation. All rights reserved.
 */

#घोषणा pr_fmt(fmt)	"[drm-dp] %s: " fmt, __func__

#समावेश <linux/types.h>
#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/phy/phy-dp.h>
#समावेश <linux/pm_opp.h>
#समावेश <drm/drm_fixed.h>
#समावेश <drm/drm_dp_helper.h>
#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "dp_reg.h"
#समावेश "dp_ctrl.h"
#समावेश "dp_link.h"

#घोषणा DP_KHZ_TO_HZ 1000
#घोषणा IDLE_PATTERN_COMPLETION_TIMEOUT_JIFFIES	(30 * HZ / 1000) /* 30 ms */
#घोषणा WAIT_FOR_VIDEO_READY_TIMEOUT_JIFFIES (HZ / 2)

#घोषणा DP_CTRL_INTR_READY_FOR_VIDEO     BIT(0)
#घोषणा DP_CTRL_INTR_IDLE_PATTERN_SENT  BIT(3)

#घोषणा MR_LINK_TRAINING1  0x8
#घोषणा MR_LINK_SYMBOL_ERM 0x80
#घोषणा MR_LINK_PRBS7 0x100
#घोषणा MR_LINK_CUSTOM80 0x200
#घोषणा MR_LINK_TRAINING4  0x40

क्रमागत अणु
	DP_TRAINING_NONE,
	DP_TRAINING_1,
	DP_TRAINING_2,
पूर्ण;

काष्ठा dp_tu_calc_input अणु
	u64 lclk;        /* 162, 270, 540 and 810 */
	u64 pclk_khz;    /* in KHz */
	u64 hactive;     /* active h-width */
	u64 hporch;      /* bp + fp + pulse */
	पूर्णांक nlanes;      /* no.of.lanes */
	पूर्णांक bpp;         /* bits */
	पूर्णांक pixel_enc;   /* 444, 420, 422 */
	पूर्णांक dsc_en;     /* dsc on/off */
	पूर्णांक async_en;   /* async mode */
	पूर्णांक fec_en;     /* fec */
	पूर्णांक compress_ratio; /* 2:1 = 200, 3:1 = 300, 3.75:1 = 375 */
	पूर्णांक num_of_dsc_slices; /* number of slices per line */
पूर्ण;

काष्ठा dp_vc_tu_mapping_table अणु
	u32 vic;
	u8 lanes;
	u8 lrate; /* DP_LINK_RATE -> 162(6), 270(10), 540(20), 810 (30) */
	u8 bpp;
	u8 valid_boundary_link;
	u16 delay_start_link;
	bool boundary_moderation_en;
	u8 valid_lower_boundary_link;
	u8 upper_boundary_count;
	u8 lower_boundary_count;
	u8 tu_size_minus1;
पूर्ण;

काष्ठा dp_ctrl_निजी अणु
	काष्ठा dp_ctrl dp_ctrl;
	काष्ठा device *dev;
	काष्ठा drm_dp_aux *aux;
	काष्ठा dp_panel *panel;
	काष्ठा dp_link *link;
	काष्ठा dp_घातer *घातer;
	काष्ठा dp_parser *parser;
	काष्ठा dp_catalog *catalog;

	काष्ठा opp_table *opp_table;

	काष्ठा completion idle_comp;
	काष्ठा completion video_comp;
पूर्ण;

काष्ठा dp_cr_status अणु
	u8 lane_0_1;
	u8 lane_2_3;
पूर्ण;

#घोषणा DP_LANE0_1_CR_DONE	0x11

अटल पूर्णांक dp_aux_link_configure(काष्ठा drm_dp_aux *aux,
					काष्ठा dp_link_info *link)
अणु
	u8 values[2];
	पूर्णांक err;

	values[0] = drm_dp_link_rate_to_bw_code(link->rate);
	values[1] = link->num_lanes;

	अगर (link->capabilities & DP_LINK_CAP_ENHANCED_FRAMING)
		values[1] |= DP_LANE_COUNT_ENHANCED_FRAME_EN;

	err = drm_dp_dpcd_ग_लिखो(aux, DP_LINK_BW_SET, values, माप(values));
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

व्योम dp_ctrl_push_idle(काष्ठा dp_ctrl *dp_ctrl)
अणु
	काष्ठा dp_ctrl_निजी *ctrl;

	ctrl = container_of(dp_ctrl, काष्ठा dp_ctrl_निजी, dp_ctrl);

	reinit_completion(&ctrl->idle_comp);
	dp_catalog_ctrl_state_ctrl(ctrl->catalog, DP_STATE_CTRL_PUSH_IDLE);

	अगर (!रुको_क्रम_completion_समयout(&ctrl->idle_comp,
			IDLE_PATTERN_COMPLETION_TIMEOUT_JIFFIES))
		pr_warn("PUSH_IDLE pattern timedout\n");

	pr_debug("mainlink off done\n");
पूर्ण

अटल व्योम dp_ctrl_config_ctrl(काष्ठा dp_ctrl_निजी *ctrl)
अणु
	u32 config = 0, tbd;
	u8 *dpcd = ctrl->panel->dpcd;

	/* Default-> LSCLK DIV: 1/4 LCLK  */
	config |= (2 << DP_CONFIGURATION_CTRL_LSCLK_DIV_SHIFT);

	/* Scrambler reset enable */
	अगर (dpcd[DP_EDP_CONFIGURATION_CAP] & DP_ALTERNATE_SCRAMBLER_RESET_CAP)
		config |= DP_CONFIGURATION_CTRL_ASSR;

	tbd = dp_link_get_test_bits_depth(ctrl->link,
			ctrl->panel->dp_mode.bpp);

	अगर (tbd == DP_TEST_BIT_DEPTH_UNKNOWN) अणु
		pr_debug("BIT_DEPTH not set. Configure default\n");
		tbd = DP_TEST_BIT_DEPTH_8;
	पूर्ण

	config |= tbd << DP_CONFIGURATION_CTRL_BPC_SHIFT;

	/* Num of Lanes */
	config |= ((ctrl->link->link_params.num_lanes - 1)
			<< DP_CONFIGURATION_CTRL_NUM_OF_LANES_SHIFT);

	अगर (drm_dp_enhanced_frame_cap(dpcd))
		config |= DP_CONFIGURATION_CTRL_ENHANCED_FRAMING;

	config |= DP_CONFIGURATION_CTRL_P_INTERLACED; /* progressive video */

	/* sync घड़ी & अटल Mvid */
	config |= DP_CONFIGURATION_CTRL_STATIC_DYNAMIC_CN;
	config |= DP_CONFIGURATION_CTRL_SYNC_ASYNC_CLK;

	dp_catalog_ctrl_config_ctrl(ctrl->catalog, config);
पूर्ण

अटल व्योम dp_ctrl_configure_source_params(काष्ठा dp_ctrl_निजी *ctrl)
अणु
	u32 cc, tb;

	dp_catalog_ctrl_lane_mapping(ctrl->catalog);
	dp_catalog_ctrl_मुख्यlink_ctrl(ctrl->catalog, true);

	dp_ctrl_config_ctrl(ctrl);

	tb = dp_link_get_test_bits_depth(ctrl->link,
		ctrl->panel->dp_mode.bpp);
	cc = dp_link_get_colorimetry_config(ctrl->link);
	dp_catalog_ctrl_config_misc(ctrl->catalog, cc, tb);
	dp_panel_timing_cfg(ctrl->panel);
पूर्ण

/*
 * The काष्ठाure and few functions present below are IP/Hardware
 * specअगरic implementation. Most of the implementation will not
 * have coding comments
 */
काष्ठा tu_algo_data अणु
	s64 lclk_fp;
	s64 pclk_fp;
	s64 lwidth;
	s64 lwidth_fp;
	s64 hbp_relative_to_pclk;
	s64 hbp_relative_to_pclk_fp;
	पूर्णांक nlanes;
	पूर्णांक bpp;
	पूर्णांक pixelEnc;
	पूर्णांक dsc_en;
	पूर्णांक async_en;
	पूर्णांक bpc;

	uपूर्णांक delay_start_link_extra_pixclk;
	पूर्णांक extra_buffer_margin;
	s64 ratio_fp;
	s64 original_ratio_fp;

	s64 err_fp;
	s64 n_err_fp;
	s64 n_n_err_fp;
	पूर्णांक tu_size;
	पूर्णांक tu_size_desired;
	पूर्णांक tu_size_minus1;

	पूर्णांक valid_boundary_link;
	s64 resulting_valid_fp;
	s64 total_valid_fp;
	s64 effective_valid_fp;
	s64 effective_valid_recorded_fp;
	पूर्णांक n_tus;
	पूर्णांक n_tus_per_lane;
	पूर्णांक paired_tus;
	पूर्णांक reमुख्यder_tus;
	पूर्णांक reमुख्यder_tus_upper;
	पूर्णांक reमुख्यder_tus_lower;
	पूर्णांक extra_bytes;
	पूर्णांक filler_size;
	पूर्णांक delay_start_link;

	पूर्णांक extra_pclk_cycles;
	पूर्णांक extra_pclk_cycles_in_link_clk;
	s64 ratio_by_tu_fp;
	s64 average_valid2_fp;
	पूर्णांक new_valid_boundary_link;
	पूर्णांक reमुख्यder_symbols_exist;
	पूर्णांक n_symbols;
	s64 n_reमुख्यder_symbols_per_lane_fp;
	s64 last_partial_tu_fp;
	s64 TU_ratio_err_fp;

	पूर्णांक n_tus_incl_last_incomplete_tu;
	पूर्णांक extra_pclk_cycles_पंचांगp;
	पूर्णांक extra_pclk_cycles_in_link_clk_पंचांगp;
	पूर्णांक extra_required_bytes_new_पंचांगp;
	पूर्णांक filler_माप_प्रकारmp;
	पूर्णांक lower_filler_माप_प्रकारmp;
	पूर्णांक delay_start_link_पंचांगp;

	bool boundary_moderation_en;
	पूर्णांक boundary_mod_lower_err;
	पूर्णांक upper_boundary_count;
	पूर्णांक lower_boundary_count;
	पूर्णांक i_upper_boundary_count;
	पूर्णांक i_lower_boundary_count;
	पूर्णांक valid_lower_boundary_link;
	पूर्णांक even_distribution_BF;
	पूर्णांक even_distribution_legacy;
	पूर्णांक even_distribution;
	पूर्णांक min_hblank_violated;
	s64 delay_start_समय_fp;
	s64 hbp_समय_fp;
	s64 hactive_समय_fp;
	s64 dअगरf_असल_fp;

	s64 ratio;
पूर्ण;

अटल पूर्णांक _tu_param_compare(s64 a, s64 b)
अणु
	u32 a_sign;
	u32 b_sign;
	s64 a_temp, b_temp, minus_1;

	अगर (a == b)
		वापस 0;

	minus_1 = drm_fixp_from_fraction(-1, 1);

	a_sign = (a >> 32) & 0x80000000 ? 1 : 0;

	b_sign = (b >> 32) & 0x80000000 ? 1 : 0;

	अगर (a_sign > b_sign)
		वापस 2;
	अन्यथा अगर (b_sign > a_sign)
		वापस 1;

	अगर (!a_sign && !b_sign) अणु /* positive */
		अगर (a > b)
			वापस 1;
		अन्यथा
			वापस 2;
	पूर्ण अन्यथा अणु /* negative */
		a_temp = drm_fixp_mul(a, minus_1);
		b_temp = drm_fixp_mul(b, minus_1);

		अगर (a_temp > b_temp)
			वापस 2;
		अन्यथा
			वापस 1;
	पूर्ण
पूर्ण

अटल व्योम dp_panel_update_tu_timings(काष्ठा dp_tu_calc_input *in,
					काष्ठा tu_algo_data *tu)
अणु
	पूर्णांक nlanes = in->nlanes;
	पूर्णांक dsc_num_slices = in->num_of_dsc_slices;
	पूर्णांक dsc_num_bytes  = 0;
	पूर्णांक numerator;
	s64 pclk_dsc_fp;
	s64 dwidth_dsc_fp;
	s64 hbp_dsc_fp;

	पूर्णांक tot_num_eoc_symbols = 0;
	पूर्णांक tot_num_hor_bytes   = 0;
	पूर्णांक tot_num_dummy_bytes = 0;
	पूर्णांक dwidth_dsc_bytes    = 0;
	पूर्णांक  eoc_bytes           = 0;

	s64 temp1_fp, temp2_fp, temp3_fp;

	tu->lclk_fp              = drm_fixp_from_fraction(in->lclk, 1);
	tu->pclk_fp              = drm_fixp_from_fraction(in->pclk_khz, 1000);
	tu->lwidth               = in->hactive;
	tu->hbp_relative_to_pclk = in->hporch;
	tu->nlanes               = in->nlanes;
	tu->bpp                  = in->bpp;
	tu->pixelEnc             = in->pixel_enc;
	tu->dsc_en               = in->dsc_en;
	tu->async_en             = in->async_en;
	tu->lwidth_fp            = drm_fixp_from_fraction(in->hactive, 1);
	tu->hbp_relative_to_pclk_fp = drm_fixp_from_fraction(in->hporch, 1);

	अगर (tu->pixelEnc == 420) अणु
		temp1_fp = drm_fixp_from_fraction(2, 1);
		tu->pclk_fp = drm_fixp_भाग(tu->pclk_fp, temp1_fp);
		tu->lwidth_fp = drm_fixp_भाग(tu->lwidth_fp, temp1_fp);
		tu->hbp_relative_to_pclk_fp =
				drm_fixp_भाग(tu->hbp_relative_to_pclk_fp, 2);
	पूर्ण

	अगर (tu->pixelEnc == 422) अणु
		चयन (tu->bpp) अणु
		हाल 24:
			tu->bpp = 16;
			tu->bpc = 8;
			अवरोध;
		हाल 30:
			tu->bpp = 20;
			tu->bpc = 10;
			अवरोध;
		शेष:
			tu->bpp = 16;
			tu->bpc = 8;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		tu->bpc = tu->bpp/3;
	पूर्ण

	अगर (!in->dsc_en)
		जाओ fec_check;

	temp1_fp = drm_fixp_from_fraction(in->compress_ratio, 100);
	temp2_fp = drm_fixp_from_fraction(in->bpp, 1);
	temp3_fp = drm_fixp_भाग(temp2_fp, temp1_fp);
	temp2_fp = drm_fixp_mul(tu->lwidth_fp, temp3_fp);

	temp1_fp = drm_fixp_from_fraction(8, 1);
	temp3_fp = drm_fixp_भाग(temp2_fp, temp1_fp);

	numerator = drm_fixp2पूर्णांक(temp3_fp);

	dsc_num_bytes  = numerator / dsc_num_slices;
	eoc_bytes           = dsc_num_bytes % nlanes;
	tot_num_eoc_symbols = nlanes * dsc_num_slices;
	tot_num_hor_bytes   = dsc_num_bytes * dsc_num_slices;
	tot_num_dummy_bytes = (nlanes - eoc_bytes) * dsc_num_slices;

	अगर (dsc_num_bytes == 0)
		pr_info("incorrect no of bytes per slice=%d\n", dsc_num_bytes);

	dwidth_dsc_bytes = (tot_num_hor_bytes +
				tot_num_eoc_symbols +
				(eoc_bytes == 0 ? 0 : tot_num_dummy_bytes));

	dwidth_dsc_fp = drm_fixp_from_fraction(dwidth_dsc_bytes, 3);

	temp2_fp = drm_fixp_mul(tu->pclk_fp, dwidth_dsc_fp);
	temp1_fp = drm_fixp_भाग(temp2_fp, tu->lwidth_fp);
	pclk_dsc_fp = temp1_fp;

	temp1_fp = drm_fixp_भाग(pclk_dsc_fp, tu->pclk_fp);
	temp2_fp = drm_fixp_mul(tu->hbp_relative_to_pclk_fp, temp1_fp);
	hbp_dsc_fp = temp2_fp;

	/* output */
	tu->pclk_fp = pclk_dsc_fp;
	tu->lwidth_fp = dwidth_dsc_fp;
	tu->hbp_relative_to_pclk_fp = hbp_dsc_fp;

fec_check:
	अगर (in->fec_en) अणु
		temp1_fp = drm_fixp_from_fraction(976, 1000); /* 0.976 */
		tu->lclk_fp = drm_fixp_mul(tu->lclk_fp, temp1_fp);
	पूर्ण
पूर्ण

अटल व्योम _tu_valid_boundary_calc(काष्ठा tu_algo_data *tu)
अणु
	s64 temp1_fp, temp2_fp, temp, temp1, temp2;
	पूर्णांक compare_result_1, compare_result_2, compare_result_3;

	temp1_fp = drm_fixp_from_fraction(tu->tu_size, 1);
	temp2_fp = drm_fixp_mul(tu->ratio_fp, temp1_fp);

	tu->new_valid_boundary_link = drm_fixp2पूर्णांक_उच्चमान(temp2_fp);

	temp = (tu->i_upper_boundary_count *
				tu->new_valid_boundary_link +
				tu->i_lower_boundary_count *
				(tu->new_valid_boundary_link-1));
	tu->average_valid2_fp = drm_fixp_from_fraction(temp,
					(tu->i_upper_boundary_count +
					tu->i_lower_boundary_count));

	temp1_fp = drm_fixp_from_fraction(tu->bpp, 8);
	temp2_fp = tu->lwidth_fp;
	temp1_fp = drm_fixp_mul(temp2_fp, temp1_fp);
	temp2_fp = drm_fixp_भाग(temp1_fp, tu->average_valid2_fp);
	tu->n_tus = drm_fixp2पूर्णांक(temp2_fp);
	अगर ((temp2_fp & 0xFFFFFFFF) > 0xFFFFF000)
		tu->n_tus += 1;

	temp1_fp = drm_fixp_from_fraction(tu->n_tus, 1);
	temp2_fp = drm_fixp_mul(temp1_fp, tu->average_valid2_fp);
	temp1_fp = drm_fixp_from_fraction(tu->n_symbols, 1);
	temp2_fp = temp1_fp - temp2_fp;
	temp1_fp = drm_fixp_from_fraction(tu->nlanes, 1);
	temp2_fp = drm_fixp_भाग(temp2_fp, temp1_fp);
	tu->n_reमुख्यder_symbols_per_lane_fp = temp2_fp;

	temp1_fp = drm_fixp_from_fraction(tu->tu_size, 1);
	tu->last_partial_tu_fp =
			drm_fixp_भाग(tu->n_reमुख्यder_symbols_per_lane_fp,
					temp1_fp);

	अगर (tu->n_reमुख्यder_symbols_per_lane_fp != 0)
		tu->reमुख्यder_symbols_exist = 1;
	अन्यथा
		tu->reमुख्यder_symbols_exist = 0;

	temp1_fp = drm_fixp_from_fraction(tu->n_tus, tu->nlanes);
	tu->n_tus_per_lane = drm_fixp2पूर्णांक(temp1_fp);

	tu->paired_tus = (पूर्णांक)((tu->n_tus_per_lane) /
					(tu->i_upper_boundary_count +
					 tu->i_lower_boundary_count));

	tu->reमुख्यder_tus = tu->n_tus_per_lane - tu->paired_tus *
						(tu->i_upper_boundary_count +
						tu->i_lower_boundary_count);

	अगर ((tu->reमुख्यder_tus - tu->i_upper_boundary_count) > 0) अणु
		tu->reमुख्यder_tus_upper = tu->i_upper_boundary_count;
		tu->reमुख्यder_tus_lower = tu->reमुख्यder_tus -
						tu->i_upper_boundary_count;
	पूर्ण अन्यथा अणु
		tu->reमुख्यder_tus_upper = tu->reमुख्यder_tus;
		tu->reमुख्यder_tus_lower = 0;
	पूर्ण

	temp = tu->paired_tus * (tu->i_upper_boundary_count *
				tu->new_valid_boundary_link +
				tu->i_lower_boundary_count *
				(tu->new_valid_boundary_link - 1)) +
				(tu->reमुख्यder_tus_upper *
				 tu->new_valid_boundary_link) +
				(tu->reमुख्यder_tus_lower *
				(tu->new_valid_boundary_link - 1));
	tu->total_valid_fp = drm_fixp_from_fraction(temp, 1);

	अगर (tu->reमुख्यder_symbols_exist) अणु
		temp1_fp = tu->total_valid_fp +
				tu->n_reमुख्यder_symbols_per_lane_fp;
		temp2_fp = drm_fixp_from_fraction(tu->n_tus_per_lane, 1);
		temp2_fp = temp2_fp + tu->last_partial_tu_fp;
		temp1_fp = drm_fixp_भाग(temp1_fp, temp2_fp);
	पूर्ण अन्यथा अणु
		temp2_fp = drm_fixp_from_fraction(tu->n_tus_per_lane, 1);
		temp1_fp = drm_fixp_भाग(tu->total_valid_fp, temp2_fp);
	पूर्ण
	tu->effective_valid_fp = temp1_fp;

	temp1_fp = drm_fixp_from_fraction(tu->tu_size, 1);
	temp2_fp = drm_fixp_mul(tu->ratio_fp, temp1_fp);
	tu->n_n_err_fp = tu->effective_valid_fp - temp2_fp;

	temp1_fp = drm_fixp_from_fraction(tu->tu_size, 1);
	temp2_fp = drm_fixp_mul(tu->ratio_fp, temp1_fp);
	tu->n_err_fp = tu->average_valid2_fp - temp2_fp;

	tu->even_distribution = tu->n_tus % tu->nlanes == 0 ? 1 : 0;

	temp1_fp = drm_fixp_from_fraction(tu->bpp, 8);
	temp2_fp = tu->lwidth_fp;
	temp1_fp = drm_fixp_mul(temp2_fp, temp1_fp);
	temp2_fp = drm_fixp_भाग(temp1_fp, tu->average_valid2_fp);

	अगर (temp2_fp)
		tu->n_tus_incl_last_incomplete_tu = drm_fixp2पूर्णांक_उच्चमान(temp2_fp);
	अन्यथा
		tu->n_tus_incl_last_incomplete_tu = 0;

	temp1 = 0;
	temp1_fp = drm_fixp_from_fraction(tu->tu_size, 1);
	temp2_fp = drm_fixp_mul(tu->original_ratio_fp, temp1_fp);
	temp1_fp = tu->average_valid2_fp - temp2_fp;
	temp2_fp = drm_fixp_from_fraction(tu->n_tus_incl_last_incomplete_tu, 1);
	temp1_fp = drm_fixp_mul(temp2_fp, temp1_fp);

	अगर (temp1_fp)
		temp1 = drm_fixp2पूर्णांक_उच्चमान(temp1_fp);

	temp = tu->i_upper_boundary_count * tu->nlanes;
	temp1_fp = drm_fixp_from_fraction(tu->tu_size, 1);
	temp2_fp = drm_fixp_mul(tu->original_ratio_fp, temp1_fp);
	temp1_fp = drm_fixp_from_fraction(tu->new_valid_boundary_link, 1);
	temp2_fp = temp1_fp - temp2_fp;
	temp1_fp = drm_fixp_from_fraction(temp, 1);
	temp2_fp = drm_fixp_mul(temp1_fp, temp2_fp);

	अगर (temp2_fp)
		temp2 = drm_fixp2पूर्णांक_उच्चमान(temp2_fp);
	अन्यथा
		temp2 = 0;
	tu->extra_required_bytes_new_पंचांगp = (पूर्णांक)(temp1 + temp2);

	temp1_fp = drm_fixp_from_fraction(8, tu->bpp);
	temp2_fp = drm_fixp_from_fraction(
	tu->extra_required_bytes_new_पंचांगp, 1);
	temp1_fp = drm_fixp_mul(temp2_fp, temp1_fp);

	अगर (temp1_fp)
		tu->extra_pclk_cycles_पंचांगp = drm_fixp2पूर्णांक_उच्चमान(temp1_fp);
	अन्यथा
		tu->extra_pclk_cycles_पंचांगp = 0;

	temp1_fp = drm_fixp_from_fraction(tu->extra_pclk_cycles_पंचांगp, 1);
	temp2_fp = drm_fixp_भाग(tu->lclk_fp, tu->pclk_fp);
	temp1_fp = drm_fixp_mul(temp1_fp, temp2_fp);

	अगर (temp1_fp)
		tu->extra_pclk_cycles_in_link_clk_पंचांगp =
						drm_fixp2पूर्णांक_उच्चमान(temp1_fp);
	अन्यथा
		tu->extra_pclk_cycles_in_link_clk_पंचांगp = 0;

	tu->filler_माप_प्रकारmp = tu->tu_size - tu->new_valid_boundary_link;

	tu->lower_filler_माप_प्रकारmp = tu->filler_माप_प्रकारmp + 1;

	tu->delay_start_link_पंचांगp = tu->extra_pclk_cycles_in_link_clk_पंचांगp +
					tu->lower_filler_माप_प्रकारmp +
					tu->extra_buffer_margin;

	temp1_fp = drm_fixp_from_fraction(tu->delay_start_link_पंचांगp, 1);
	tu->delay_start_समय_fp = drm_fixp_भाग(temp1_fp, tu->lclk_fp);

	compare_result_1 = _tu_param_compare(tu->n_n_err_fp, tu->dअगरf_असल_fp);
	अगर (compare_result_1 == 2)
		compare_result_1 = 1;
	अन्यथा
		compare_result_1 = 0;

	compare_result_2 = _tu_param_compare(tu->n_n_err_fp, tu->err_fp);
	अगर (compare_result_2 == 2)
		compare_result_2 = 1;
	अन्यथा
		compare_result_2 = 0;

	compare_result_3 = _tu_param_compare(tu->hbp_समय_fp,
					tu->delay_start_समय_fp);
	अगर (compare_result_3 == 2)
		compare_result_3 = 0;
	अन्यथा
		compare_result_3 = 1;

	अगर (((tu->even_distribution == 1) ||
			((tu->even_distribution_BF == 0) &&
			(tu->even_distribution_legacy == 0))) &&
			tu->n_err_fp >= 0 && tu->n_n_err_fp >= 0 &&
			compare_result_2 &&
			(compare_result_1 || (tu->min_hblank_violated == 1)) &&
			(tu->new_valid_boundary_link - 1) > 0 &&
			compare_result_3 &&
			(tu->delay_start_link_पंचांगp <= 1023)) अणु
		tu->upper_boundary_count = tu->i_upper_boundary_count;
		tu->lower_boundary_count = tu->i_lower_boundary_count;
		tu->err_fp = tu->n_n_err_fp;
		tu->boundary_moderation_en = true;
		tu->tu_size_desired = tu->tu_size;
		tu->valid_boundary_link = tu->new_valid_boundary_link;
		tu->effective_valid_recorded_fp = tu->effective_valid_fp;
		tu->even_distribution_BF = 1;
		tu->delay_start_link = tu->delay_start_link_पंचांगp;
	पूर्ण अन्यथा अगर (tu->boundary_mod_lower_err == 0) अणु
		compare_result_1 = _tu_param_compare(tu->n_n_err_fp,
							tu->dअगरf_असल_fp);
		अगर (compare_result_1 == 2)
			tu->boundary_mod_lower_err = 1;
	पूर्ण
पूर्ण

अटल व्योम _dp_ctrl_calc_tu(काष्ठा dp_tu_calc_input *in,
				   काष्ठा dp_vc_tu_mapping_table *tu_table)
अणु
	काष्ठा tu_algo_data *tu;
	पूर्णांक compare_result_1, compare_result_2;
	u64 temp = 0;
	s64 temp_fp = 0, temp1_fp = 0, temp2_fp = 0;

	s64 LCLK_FAST_SKEW_fp = drm_fixp_from_fraction(6, 10000); /* 0.0006 */
	s64 स्थिर_p49_fp = drm_fixp_from_fraction(49, 100); /* 0.49 */
	s64 स्थिर_p56_fp = drm_fixp_from_fraction(56, 100); /* 0.56 */
	s64 RATIO_SCALE_fp = drm_fixp_from_fraction(1001, 1000);

	u8 DP_BRUTE_FORCE = 1;
	s64 BRUTE_FORCE_THRESHOLD_fp = drm_fixp_from_fraction(1, 10); /* 0.1 */
	uपूर्णांक EXTRA_PIXCLK_CYCLE_DELAY = 4;
	uपूर्णांक HBLANK_MARGIN = 4;

	tu = kzalloc(माप(*tu), GFP_KERNEL);
	अगर (!tu)
		वापस;

	dp_panel_update_tu_timings(in, tu);

	tu->err_fp = drm_fixp_from_fraction(1000, 1); /* 1000 */

	temp1_fp = drm_fixp_from_fraction(4, 1);
	temp2_fp = drm_fixp_mul(temp1_fp, tu->lclk_fp);
	temp_fp = drm_fixp_भाग(temp2_fp, tu->pclk_fp);
	tu->extra_buffer_margin = drm_fixp2पूर्णांक_उच्चमान(temp_fp);

	temp1_fp = drm_fixp_from_fraction(tu->bpp, 8);
	temp2_fp = drm_fixp_mul(tu->pclk_fp, temp1_fp);
	temp1_fp = drm_fixp_from_fraction(tu->nlanes, 1);
	temp2_fp = drm_fixp_भाग(temp2_fp, temp1_fp);
	tu->ratio_fp = drm_fixp_भाग(temp2_fp, tu->lclk_fp);

	tu->original_ratio_fp = tu->ratio_fp;
	tu->boundary_moderation_en = false;
	tu->upper_boundary_count = 0;
	tu->lower_boundary_count = 0;
	tu->i_upper_boundary_count = 0;
	tu->i_lower_boundary_count = 0;
	tu->valid_lower_boundary_link = 0;
	tu->even_distribution_BF = 0;
	tu->even_distribution_legacy = 0;
	tu->even_distribution = 0;
	tu->delay_start_समय_fp = 0;

	tu->err_fp = drm_fixp_from_fraction(1000, 1);
	tu->n_err_fp = 0;
	tu->n_n_err_fp = 0;

	tu->ratio = drm_fixp2पूर्णांक(tu->ratio_fp);
	temp1_fp = drm_fixp_from_fraction(tu->nlanes, 1);
	भाग64_u64_rem(tu->lwidth_fp, temp1_fp, &temp2_fp);
	अगर (temp2_fp != 0 &&
			!tu->ratio && tu->dsc_en == 0) अणु
		tu->ratio_fp = drm_fixp_mul(tu->ratio_fp, RATIO_SCALE_fp);
		tu->ratio = drm_fixp2पूर्णांक(tu->ratio_fp);
		अगर (tu->ratio)
			tu->ratio_fp = drm_fixp_from_fraction(1, 1);
	पूर्ण

	अगर (tu->ratio > 1)
		tu->ratio = 1;

	अगर (tu->ratio == 1)
		जाओ tu_size_calc;

	compare_result_1 = _tu_param_compare(tu->ratio_fp, स्थिर_p49_fp);
	अगर (!compare_result_1 || compare_result_1 == 1)
		compare_result_1 = 1;
	अन्यथा
		compare_result_1 = 0;

	compare_result_2 = _tu_param_compare(tu->ratio_fp, स्थिर_p56_fp);
	अगर (!compare_result_2 || compare_result_2 == 2)
		compare_result_2 = 1;
	अन्यथा
		compare_result_2 = 0;

	अगर (tu->dsc_en && compare_result_1 && compare_result_2) अणु
		HBLANK_MARGIN += 4;
		DRM_DEBUG_DP("Info: increase HBLANK_MARGIN to %d\n",
				HBLANK_MARGIN);
	पूर्ण

tu_size_calc:
	क्रम (tu->tu_size = 32; tu->tu_size <= 64; tu->tu_size++) अणु
		temp1_fp = drm_fixp_from_fraction(tu->tu_size, 1);
		temp2_fp = drm_fixp_mul(tu->ratio_fp, temp1_fp);
		temp = drm_fixp2पूर्णांक_उच्चमान(temp2_fp);
		temp1_fp = drm_fixp_from_fraction(temp, 1);
		tu->n_err_fp = temp1_fp - temp2_fp;

		अगर (tu->n_err_fp < tu->err_fp) अणु
			tu->err_fp = tu->n_err_fp;
			tu->tu_size_desired = tu->tu_size;
		पूर्ण
	पूर्ण

	tu->tu_size_minus1 = tu->tu_size_desired - 1;

	temp1_fp = drm_fixp_from_fraction(tu->tu_size_desired, 1);
	temp2_fp = drm_fixp_mul(tu->ratio_fp, temp1_fp);
	tu->valid_boundary_link = drm_fixp2पूर्णांक_उच्चमान(temp2_fp);

	temp1_fp = drm_fixp_from_fraction(tu->bpp, 8);
	temp2_fp = tu->lwidth_fp;
	temp2_fp = drm_fixp_mul(temp2_fp, temp1_fp);

	temp1_fp = drm_fixp_from_fraction(tu->valid_boundary_link, 1);
	temp2_fp = drm_fixp_भाग(temp2_fp, temp1_fp);
	tu->n_tus = drm_fixp2पूर्णांक(temp2_fp);
	अगर ((temp2_fp & 0xFFFFFFFF) > 0xFFFFF000)
		tu->n_tus += 1;

	tu->even_distribution_legacy = tu->n_tus % tu->nlanes == 0 ? 1 : 0;
	DRM_DEBUG_DP("Info: n_sym = %d, num_of_tus = %d\n",
		tu->valid_boundary_link, tu->n_tus);

	temp1_fp = drm_fixp_from_fraction(tu->tu_size_desired, 1);
	temp2_fp = drm_fixp_mul(tu->original_ratio_fp, temp1_fp);
	temp1_fp = drm_fixp_from_fraction(tu->valid_boundary_link, 1);
	temp2_fp = temp1_fp - temp2_fp;
	temp1_fp = drm_fixp_from_fraction(tu->n_tus + 1, 1);
	temp2_fp = drm_fixp_mul(temp1_fp, temp2_fp);

	temp = drm_fixp2पूर्णांक(temp2_fp);
	अगर (temp && temp2_fp)
		tu->extra_bytes = drm_fixp2पूर्णांक_उच्चमान(temp2_fp);
	अन्यथा
		tu->extra_bytes = 0;

	temp1_fp = drm_fixp_from_fraction(tu->extra_bytes, 1);
	temp2_fp = drm_fixp_from_fraction(8, tu->bpp);
	temp1_fp = drm_fixp_mul(temp1_fp, temp2_fp);

	अगर (temp && temp1_fp)
		tu->extra_pclk_cycles = drm_fixp2पूर्णांक_उच्चमान(temp1_fp);
	अन्यथा
		tu->extra_pclk_cycles = drm_fixp2पूर्णांक(temp1_fp);

	temp1_fp = drm_fixp_भाग(tu->lclk_fp, tu->pclk_fp);
	temp2_fp = drm_fixp_from_fraction(tu->extra_pclk_cycles, 1);
	temp1_fp = drm_fixp_mul(temp2_fp, temp1_fp);

	अगर (temp1_fp)
		tu->extra_pclk_cycles_in_link_clk = drm_fixp2पूर्णांक_उच्चमान(temp1_fp);
	अन्यथा
		tu->extra_pclk_cycles_in_link_clk = drm_fixp2पूर्णांक(temp1_fp);

	tu->filler_size = tu->tu_size_desired - tu->valid_boundary_link;

	temp1_fp = drm_fixp_from_fraction(tu->tu_size_desired, 1);
	tu->ratio_by_tu_fp = drm_fixp_mul(tu->ratio_fp, temp1_fp);

	tu->delay_start_link = tu->extra_pclk_cycles_in_link_clk +
				tu->filler_size + tu->extra_buffer_margin;

	tu->resulting_valid_fp =
			drm_fixp_from_fraction(tu->valid_boundary_link, 1);

	temp1_fp = drm_fixp_from_fraction(tu->tu_size_desired, 1);
	temp2_fp = drm_fixp_भाग(tu->resulting_valid_fp, temp1_fp);
	tu->TU_ratio_err_fp = temp2_fp - tu->original_ratio_fp;

	temp1_fp = drm_fixp_from_fraction(HBLANK_MARGIN, 1);
	temp1_fp = tu->hbp_relative_to_pclk_fp - temp1_fp;
	tu->hbp_समय_fp = drm_fixp_भाग(temp1_fp, tu->pclk_fp);

	temp1_fp = drm_fixp_from_fraction(tu->delay_start_link, 1);
	tu->delay_start_समय_fp = drm_fixp_भाग(temp1_fp, tu->lclk_fp);

	compare_result_1 = _tu_param_compare(tu->hbp_समय_fp,
					tu->delay_start_समय_fp);
	अगर (compare_result_1 == 2) /* अगर (hbp_समय_fp < delay_start_समय_fp) */
		tu->min_hblank_violated = 1;

	tu->hactive_समय_fp = drm_fixp_भाग(tu->lwidth_fp, tu->pclk_fp);

	compare_result_2 = _tu_param_compare(tu->hactive_समय_fp,
						tu->delay_start_समय_fp);
	अगर (compare_result_2 == 2)
		tu->min_hblank_violated = 1;

	tu->delay_start_समय_fp = 0;

	/* brute क्रमce */

	tu->delay_start_link_extra_pixclk = EXTRA_PIXCLK_CYCLE_DELAY;
	tu->dअगरf_असल_fp = tu->resulting_valid_fp - tu->ratio_by_tu_fp;

	temp = drm_fixp2पूर्णांक(tu->dअगरf_असल_fp);
	अगर (!temp && tu->dअगरf_असल_fp <= 0xffff)
		tu->dअगरf_असल_fp = 0;

	/* अगर(dअगरf_असल < 0) dअगरf_असल *= -1 */
	अगर (tu->dअगरf_असल_fp < 0)
		tu->dअगरf_असल_fp = drm_fixp_mul(tu->dअगरf_असल_fp, -1);

	tu->boundary_mod_lower_err = 0;
	अगर ((tu->dअगरf_असल_fp != 0 &&
			((tu->dअगरf_असल_fp > BRUTE_FORCE_THRESHOLD_fp) ||
			 (tu->even_distribution_legacy == 0) ||
			 (DP_BRUTE_FORCE == 1))) ||
			(tu->min_hblank_violated == 1)) अणु
		करो अणु
			tu->err_fp = drm_fixp_from_fraction(1000, 1);

			temp1_fp = drm_fixp_भाग(tu->lclk_fp, tu->pclk_fp);
			temp2_fp = drm_fixp_from_fraction(
					tu->delay_start_link_extra_pixclk, 1);
			temp1_fp = drm_fixp_mul(temp2_fp, temp1_fp);

			अगर (temp1_fp)
				tu->extra_buffer_margin =
					drm_fixp2पूर्णांक_उच्चमान(temp1_fp);
			अन्यथा
				tu->extra_buffer_margin = 0;

			temp1_fp = drm_fixp_from_fraction(tu->bpp, 8);
			temp1_fp = drm_fixp_mul(tu->lwidth_fp, temp1_fp);

			अगर (temp1_fp)
				tu->n_symbols = drm_fixp2पूर्णांक_उच्चमान(temp1_fp);
			अन्यथा
				tu->n_symbols = 0;

			क्रम (tu->tu_size = 32; tu->tu_size <= 64; tu->tu_size++) अणु
				क्रम (tu->i_upper_boundary_count = 1;
					tu->i_upper_boundary_count <= 15;
					tu->i_upper_boundary_count++) अणु
					क्रम (tu->i_lower_boundary_count = 1;
						tu->i_lower_boundary_count <= 15;
						tu->i_lower_boundary_count++) अणु
						_tu_valid_boundary_calc(tu);
					पूर्ण
				पूर्ण
			पूर्ण
			tu->delay_start_link_extra_pixclk--;
		पूर्ण जबतक (tu->boundary_moderation_en != true &&
			tu->boundary_mod_lower_err == 1 &&
			tu->delay_start_link_extra_pixclk != 0);

		अगर (tu->boundary_moderation_en == true) अणु
			temp1_fp = drm_fixp_from_fraction(
					(tu->upper_boundary_count *
					tu->valid_boundary_link +
					tu->lower_boundary_count *
					(tu->valid_boundary_link - 1)), 1);
			temp2_fp = drm_fixp_from_fraction(
					(tu->upper_boundary_count +
					tu->lower_boundary_count), 1);
			tu->resulting_valid_fp =
					drm_fixp_भाग(temp1_fp, temp2_fp);

			temp1_fp = drm_fixp_from_fraction(
					tu->tu_size_desired, 1);
			tu->ratio_by_tu_fp =
				drm_fixp_mul(tu->original_ratio_fp, temp1_fp);

			tu->valid_lower_boundary_link =
				tu->valid_boundary_link - 1;

			temp1_fp = drm_fixp_from_fraction(tu->bpp, 8);
			temp1_fp = drm_fixp_mul(tu->lwidth_fp, temp1_fp);
			temp2_fp = drm_fixp_भाग(temp1_fp,
						tu->resulting_valid_fp);
			tu->n_tus = drm_fixp2पूर्णांक(temp2_fp);

			tu->tu_size_minus1 = tu->tu_size_desired - 1;
			tu->even_distribution_BF = 1;

			temp1_fp =
				drm_fixp_from_fraction(tu->tu_size_desired, 1);
			temp2_fp =
				drm_fixp_भाग(tu->resulting_valid_fp, temp1_fp);
			tu->TU_ratio_err_fp = temp2_fp - tu->original_ratio_fp;
		पूर्ण
	पूर्ण

	temp2_fp = drm_fixp_mul(LCLK_FAST_SKEW_fp, tu->lwidth_fp);

	अगर (temp2_fp)
		temp = drm_fixp2पूर्णांक_उच्चमान(temp2_fp);
	अन्यथा
		temp = 0;

	temp1_fp = drm_fixp_from_fraction(tu->nlanes, 1);
	temp2_fp = drm_fixp_mul(tu->original_ratio_fp, temp1_fp);
	temp1_fp = drm_fixp_from_fraction(tu->bpp, 8);
	temp2_fp = drm_fixp_भाग(temp1_fp, temp2_fp);
	temp1_fp = drm_fixp_from_fraction(temp, 1);
	temp2_fp = drm_fixp_mul(temp1_fp, temp2_fp);
	temp = drm_fixp2पूर्णांक(temp2_fp);

	अगर (tu->async_en)
		tu->delay_start_link += (पूर्णांक)temp;

	temp1_fp = drm_fixp_from_fraction(tu->delay_start_link, 1);
	tu->delay_start_समय_fp = drm_fixp_भाग(temp1_fp, tu->lclk_fp);

	/* OUTPUTS */
	tu_table->valid_boundary_link       = tu->valid_boundary_link;
	tu_table->delay_start_link          = tu->delay_start_link;
	tu_table->boundary_moderation_en    = tu->boundary_moderation_en;
	tu_table->valid_lower_boundary_link = tu->valid_lower_boundary_link;
	tu_table->upper_boundary_count      = tu->upper_boundary_count;
	tu_table->lower_boundary_count      = tu->lower_boundary_count;
	tu_table->tu_size_minus1            = tu->tu_size_minus1;

	DRM_DEBUG_DP("TU: valid_boundary_link: %d\n",
				tu_table->valid_boundary_link);
	DRM_DEBUG_DP("TU: delay_start_link: %d\n",
				tu_table->delay_start_link);
	DRM_DEBUG_DP("TU: boundary_moderation_en: %d\n",
			tu_table->boundary_moderation_en);
	DRM_DEBUG_DP("TU: valid_lower_boundary_link: %d\n",
			tu_table->valid_lower_boundary_link);
	DRM_DEBUG_DP("TU: upper_boundary_count: %d\n",
			tu_table->upper_boundary_count);
	DRM_DEBUG_DP("TU: lower_boundary_count: %d\n",
			tu_table->lower_boundary_count);
	DRM_DEBUG_DP("TU: tu_size_minus1: %d\n", tu_table->tu_size_minus1);

	kमुक्त(tu);
पूर्ण

अटल व्योम dp_ctrl_calc_tu_parameters(काष्ठा dp_ctrl_निजी *ctrl,
		काष्ठा dp_vc_tu_mapping_table *tu_table)
अणु
	काष्ठा dp_tu_calc_input in;
	काष्ठा drm_display_mode *drm_mode;

	drm_mode = &ctrl->panel->dp_mode.drm_mode;

	in.lclk = ctrl->link->link_params.rate / 1000;
	in.pclk_khz = drm_mode->घड़ी;
	in.hactive = drm_mode->hdisplay;
	in.hporch = drm_mode->htotal - drm_mode->hdisplay;
	in.nlanes = ctrl->link->link_params.num_lanes;
	in.bpp = ctrl->panel->dp_mode.bpp;
	in.pixel_enc = 444;
	in.dsc_en = 0;
	in.async_en = 0;
	in.fec_en = 0;
	in.num_of_dsc_slices = 0;
	in.compress_ratio = 100;

	_dp_ctrl_calc_tu(&in, tu_table);
पूर्ण

अटल व्योम dp_ctrl_setup_tr_unit(काष्ठा dp_ctrl_निजी *ctrl)
अणु
	u32 dp_tu = 0x0;
	u32 valid_boundary = 0x0;
	u32 valid_boundary2 = 0x0;
	काष्ठा dp_vc_tu_mapping_table tu_calc_table;

	dp_ctrl_calc_tu_parameters(ctrl, &tu_calc_table);

	dp_tu |= tu_calc_table.tu_size_minus1;
	valid_boundary |= tu_calc_table.valid_boundary_link;
	valid_boundary |= (tu_calc_table.delay_start_link << 16);

	valid_boundary2 |= (tu_calc_table.valid_lower_boundary_link << 1);
	valid_boundary2 |= (tu_calc_table.upper_boundary_count << 16);
	valid_boundary2 |= (tu_calc_table.lower_boundary_count << 20);

	अगर (tu_calc_table.boundary_moderation_en)
		valid_boundary2 |= BIT(0);

	pr_debug("dp_tu=0x%x, valid_boundary=0x%x, valid_boundary2=0x%x\n",
			dp_tu, valid_boundary, valid_boundary2);

	dp_catalog_ctrl_update_transfer_unit(ctrl->catalog,
				dp_tu, valid_boundary, valid_boundary2);
पूर्ण

अटल पूर्णांक dp_ctrl_रुको4video_पढ़ोy(काष्ठा dp_ctrl_निजी *ctrl)
अणु
	पूर्णांक ret = 0;

	अगर (!रुको_क्रम_completion_समयout(&ctrl->video_comp,
				WAIT_FOR_VIDEO_READY_TIMEOUT_JIFFIES)) अणु
		DRM_ERROR("wait4video timedout\n");
		ret = -ETIMEDOUT;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक dp_ctrl_update_vx_px(काष्ठा dp_ctrl_निजी *ctrl)
अणु
	काष्ठा dp_link *link = ctrl->link;
	पूर्णांक ret = 0, lane, lane_cnt;
	u8 buf[4];
	u32 max_level_reached = 0;
	u32 voltage_swing_level = link->phy_params.v_level;
	u32 pre_emphasis_level = link->phy_params.p_level;

	ret = dp_catalog_ctrl_update_vx_px(ctrl->catalog,
		voltage_swing_level, pre_emphasis_level);

	अगर (ret)
		वापस ret;

	अगर (voltage_swing_level >= DP_TRAIN_VOLTAGE_SWING_MAX) अणु
		DRM_DEBUG_DP("max. voltage swing level reached %d\n",
				voltage_swing_level);
		max_level_reached |= DP_TRAIN_MAX_SWING_REACHED;
	पूर्ण

	अगर (pre_emphasis_level >= DP_TRAIN_PRE_EMPHASIS_MAX) अणु
		DRM_DEBUG_DP("max. pre-emphasis level reached %d\n",
				pre_emphasis_level);
		max_level_reached  |= DP_TRAIN_MAX_PRE_EMPHASIS_REACHED;
	पूर्ण

	pre_emphasis_level <<= DP_TRAIN_PRE_EMPHASIS_SHIFT;

	lane_cnt = ctrl->link->link_params.num_lanes;
	क्रम (lane = 0; lane < lane_cnt; lane++)
		buf[lane] = voltage_swing_level | pre_emphasis_level
				| max_level_reached;

	DRM_DEBUG_DP("sink: p|v=0x%x\n", voltage_swing_level
					| pre_emphasis_level);
	ret = drm_dp_dpcd_ग_लिखो(ctrl->aux, DP_TRAINING_LANE0_SET,
					buf, lane_cnt);
	अगर (ret == lane_cnt)
		ret = 0;

	वापस ret;
पूर्ण

अटल bool dp_ctrl_train_pattern_set(काष्ठा dp_ctrl_निजी *ctrl,
		u8 pattern)
अणु
	u8 buf;
	पूर्णांक ret = 0;

	DRM_DEBUG_DP("sink: pattern=%x\n", pattern);

	buf = pattern;

	अगर (pattern && pattern != DP_TRAINING_PATTERN_4)
		buf |= DP_LINK_SCRAMBLING_DISABLE;

	ret = drm_dp_dpcd_ग_लिखोb(ctrl->aux, DP_TRAINING_PATTERN_SET, buf);
	वापस ret == 1;
पूर्ण

अटल पूर्णांक dp_ctrl_पढ़ो_link_status(काष्ठा dp_ctrl_निजी *ctrl,
				    u8 *link_status)
अणु
	पूर्णांक ret = 0, len;

	len = drm_dp_dpcd_पढ़ो_link_status(ctrl->aux, link_status);
	अगर (len != DP_LINK_STATUS_SIZE) अणु
		DRM_ERROR("DP link status read failed, err: %d\n", len);
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक dp_ctrl_link_train_1(काष्ठा dp_ctrl_निजी *ctrl,
		काष्ठा dp_cr_status *cr, पूर्णांक *training_step)
अणु
	पूर्णांक tries, old_v_level, ret = 0;
	u8 link_status[DP_LINK_STATUS_SIZE];
	पूर्णांक स्थिर maximum_retries = 4;

	dp_catalog_ctrl_state_ctrl(ctrl->catalog, 0);

	*training_step = DP_TRAINING_1;

	ret = dp_catalog_ctrl_set_pattern(ctrl->catalog, DP_TRAINING_PATTERN_1);
	अगर (ret)
		वापस ret;
	dp_ctrl_train_pattern_set(ctrl, DP_TRAINING_PATTERN_1 |
		DP_LINK_SCRAMBLING_DISABLE);

	ret = dp_ctrl_update_vx_px(ctrl);
	अगर (ret)
		वापस ret;

	tries = 0;
	old_v_level = ctrl->link->phy_params.v_level;
	क्रम (tries = 0; tries < maximum_retries; tries++) अणु
		drm_dp_link_train_घड़ी_recovery_delay(ctrl->panel->dpcd);

		ret = dp_ctrl_पढ़ो_link_status(ctrl, link_status);
		अगर (ret)
			वापस ret;

		cr->lane_0_1 = link_status[0];
		cr->lane_2_3 = link_status[1];

		अगर (drm_dp_घड़ी_recovery_ok(link_status,
			ctrl->link->link_params.num_lanes)) अणु
			वापस 0;
		पूर्ण

		अगर (ctrl->link->phy_params.v_level >=
			DP_TRAIN_VOLTAGE_SWING_MAX) अणु
			DRM_ERROR_RATELIMITED("max v_level reached\n");
			वापस -EAGAIN;
		पूर्ण

		अगर (old_v_level != ctrl->link->phy_params.v_level) अणु
			tries = 0;
			old_v_level = ctrl->link->phy_params.v_level;
		पूर्ण

		DRM_DEBUG_DP("clock recovery not done, adjusting vx px\n");

		dp_link_adjust_levels(ctrl->link, link_status);
		ret = dp_ctrl_update_vx_px(ctrl);
		अगर (ret)
			वापस ret;
	पूर्ण

	DRM_ERROR("max tries reached\n");
	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक dp_ctrl_link_rate_करोwn_shअगरt(काष्ठा dp_ctrl_निजी *ctrl)
अणु
	पूर्णांक ret = 0;

	चयन (ctrl->link->link_params.rate) अणु
	हाल 810000:
		ctrl->link->link_params.rate = 540000;
		अवरोध;
	हाल 540000:
		ctrl->link->link_params.rate = 270000;
		अवरोध;
	हाल 270000:
		ctrl->link->link_params.rate = 162000;
		अवरोध;
	हाल 162000:
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	अगर (!ret)
		DRM_DEBUG_DP("new rate=0x%x\n", ctrl->link->link_params.rate);

	वापस ret;
पूर्ण

अटल पूर्णांक dp_ctrl_link_lane_करोwn_shअगरt(काष्ठा dp_ctrl_निजी *ctrl)
अणु

	अगर (ctrl->link->link_params.num_lanes == 1)
		वापस -1;

	ctrl->link->link_params.num_lanes /= 2;
	ctrl->link->link_params.rate = ctrl->panel->link_info.rate;

	ctrl->link->phy_params.p_level = 0;
	ctrl->link->phy_params.v_level = 0;

	वापस 0;
पूर्ण

अटल व्योम dp_ctrl_clear_training_pattern(काष्ठा dp_ctrl_निजी *ctrl)
अणु
	dp_ctrl_train_pattern_set(ctrl, DP_TRAINING_PATTERN_DISABLE);
	drm_dp_link_train_channel_eq_delay(ctrl->panel->dpcd);
पूर्ण

अटल पूर्णांक dp_ctrl_link_train_2(काष्ठा dp_ctrl_निजी *ctrl,
		काष्ठा dp_cr_status *cr, पूर्णांक *training_step)
अणु
	पूर्णांक tries = 0, ret = 0;
	अक्षर pattern;
	पूर्णांक स्थिर maximum_retries = 5;
	u8 link_status[DP_LINK_STATUS_SIZE];

	dp_catalog_ctrl_state_ctrl(ctrl->catalog, 0);

	*training_step = DP_TRAINING_2;

	अगर (drm_dp_tps3_supported(ctrl->panel->dpcd))
		pattern = DP_TRAINING_PATTERN_3;
	अन्यथा
		pattern = DP_TRAINING_PATTERN_2;

	ret = dp_ctrl_update_vx_px(ctrl);
	अगर (ret)
		वापस ret;

	ret = dp_catalog_ctrl_set_pattern(ctrl->catalog, pattern);
	अगर (ret)
		वापस ret;

	dp_ctrl_train_pattern_set(ctrl, pattern | DP_RECOVERED_CLOCK_OUT_EN);

	क्रम (tries = 0; tries <= maximum_retries; tries++) अणु
		drm_dp_link_train_channel_eq_delay(ctrl->panel->dpcd);

		ret = dp_ctrl_पढ़ो_link_status(ctrl, link_status);
		अगर (ret)
			वापस ret;
		cr->lane_0_1 = link_status[0];
		cr->lane_2_3 = link_status[1];

		अगर (drm_dp_channel_eq_ok(link_status,
			ctrl->link->link_params.num_lanes)) अणु
			वापस 0;
		पूर्ण

		dp_link_adjust_levels(ctrl->link, link_status);
		ret = dp_ctrl_update_vx_px(ctrl);
		अगर (ret)
			वापस ret;

	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक dp_ctrl_reinitialize_मुख्यlink(काष्ठा dp_ctrl_निजी *ctrl);

अटल पूर्णांक dp_ctrl_link_train(काष्ठा dp_ctrl_निजी *ctrl,
		काष्ठा dp_cr_status *cr, पूर्णांक *training_step)
अणु
	पूर्णांक ret = 0;
	u8 encoding = DP_SET_ANSI_8B10B;
	काष्ठा dp_link_info link_info = अणु0पूर्ण;

	dp_ctrl_config_ctrl(ctrl);

	link_info.num_lanes = ctrl->link->link_params.num_lanes;
	link_info.rate = ctrl->link->link_params.rate;
	link_info.capabilities = DP_LINK_CAP_ENHANCED_FRAMING;

	dp_aux_link_configure(ctrl->aux, &link_info);
	drm_dp_dpcd_ग_लिखो(ctrl->aux, DP_MAIN_LINK_CHANNEL_CODING_SET,
				&encoding, 1);

	ret = dp_ctrl_link_train_1(ctrl, cr, training_step);
	अगर (ret) अणु
		DRM_ERROR("link training #1 failed. ret=%d\n", ret);
		जाओ end;
	पूर्ण

	/* prपूर्णांक success info as this is a result of user initiated action */
	DRM_DEBUG_DP("link training #1 successful\n");

	ret = dp_ctrl_link_train_2(ctrl, cr, training_step);
	अगर (ret) अणु
		DRM_ERROR("link training #2 failed. ret=%d\n", ret);
		जाओ end;
	पूर्ण

	/* prपूर्णांक success info as this is a result of user initiated action */
	DRM_DEBUG_DP("link training #2 successful\n");

end:
	dp_catalog_ctrl_state_ctrl(ctrl->catalog, 0);

	वापस ret;
पूर्ण

अटल पूर्णांक dp_ctrl_setup_मुख्य_link(काष्ठा dp_ctrl_निजी *ctrl,
		काष्ठा dp_cr_status *cr, पूर्णांक *training_step)
अणु
	पूर्णांक ret = 0;

	dp_catalog_ctrl_मुख्यlink_ctrl(ctrl->catalog, true);

	अगर (ctrl->link->sink_request & DP_TEST_LINK_PHY_TEST_PATTERN)
		वापस ret;

	/*
	 * As part of previous calls, DP controller state might have
	 * transitioned to PUSH_IDLE. In order to start transmitting
	 * a link training pattern, we have to first करो soft reset.
	 */

	ret = dp_ctrl_link_train(ctrl, cr, training_step);

	वापस ret;
पूर्ण

अटल व्योम dp_ctrl_set_घड़ी_rate(काष्ठा dp_ctrl_निजी *ctrl,
			क्रमागत dp_pm_type module, अक्षर *name, अचिन्हित दीर्घ rate)
अणु
	u32 num = ctrl->parser->mp[module].num_clk;
	काष्ठा dss_clk *cfg = ctrl->parser->mp[module].clk_config;

	जबतक (num && म_भेद(cfg->clk_name, name)) अणु
		num--;
		cfg++;
	पूर्ण

	DRM_DEBUG_DP("setting rate=%lu on clk=%s\n", rate, name);

	अगर (num)
		cfg->rate = rate;
	अन्यथा
		DRM_ERROR("%s clock doesn't exit to set rate %lu\n",
				name, rate);
पूर्ण

अटल पूर्णांक dp_ctrl_enable_मुख्यlink_घड़ीs(काष्ठा dp_ctrl_निजी *ctrl)
अणु
	पूर्णांक ret = 0;
	काष्ठा dp_io *dp_io = &ctrl->parser->io;
	काष्ठा phy *phy = dp_io->phy;
	काष्ठा phy_configure_opts_dp *opts_dp = &dp_io->phy_opts.dp;

	opts_dp->lanes = ctrl->link->link_params.num_lanes;
	opts_dp->link_rate = ctrl->link->link_params.rate / 100;
	dp_ctrl_set_घड़ी_rate(ctrl, DP_CTRL_PM, "ctrl_link",
					ctrl->link->link_params.rate * 1000);

	phy_configure(phy, &dp_io->phy_opts);
	phy_घातer_on(phy);

	ret = dp_घातer_clk_enable(ctrl->घातer, DP_CTRL_PM, true);
	अगर (ret)
		DRM_ERROR("Unable to start link clocks. ret=%d\n", ret);

	DRM_DEBUG_DP("link rate=%d pixel_clk=%d\n",
		ctrl->link->link_params.rate, ctrl->dp_ctrl.pixel_rate);

	वापस ret;
पूर्ण

अटल पूर्णांक dp_ctrl_enable_stream_घड़ीs(काष्ठा dp_ctrl_निजी *ctrl)
अणु
	पूर्णांक ret = 0;

	dp_ctrl_set_घड़ी_rate(ctrl, DP_STREAM_PM, "stream_pixel",
					ctrl->dp_ctrl.pixel_rate * 1000);

	ret = dp_घातer_clk_enable(ctrl->घातer, DP_STREAM_PM, true);
	अगर (ret)
		DRM_ERROR("Unabled to start pixel clocks. ret=%d\n", ret);

	DRM_DEBUG_DP("link rate=%d pixel_clk=%d\n",
			ctrl->link->link_params.rate, ctrl->dp_ctrl.pixel_rate);

	वापस ret;
पूर्ण

पूर्णांक dp_ctrl_host_init(काष्ठा dp_ctrl *dp_ctrl, bool flip, bool reset)
अणु
	काष्ठा dp_ctrl_निजी *ctrl;
	काष्ठा dp_io *dp_io;
	काष्ठा phy *phy;

	अगर (!dp_ctrl) अणु
		DRM_ERROR("Invalid input data\n");
		वापस -EINVAL;
	पूर्ण

	ctrl = container_of(dp_ctrl, काष्ठा dp_ctrl_निजी, dp_ctrl);
	dp_io = &ctrl->parser->io;
	phy = dp_io->phy;

	ctrl->dp_ctrl.orientation = flip;

	अगर (reset)
		dp_catalog_ctrl_reset(ctrl->catalog);

	dp_catalog_ctrl_phy_reset(ctrl->catalog);
	phy_init(phy);
	dp_catalog_ctrl_enable_irq(ctrl->catalog, true);

	वापस 0;
पूर्ण

/**
 * dp_ctrl_host_deinit() - Uninitialize DP controller
 * @dp_ctrl: Display Port Driver data
 *
 * Perक्रमm required steps to uninitialize DP controller
 * and its resources.
 */
व्योम dp_ctrl_host_deinit(काष्ठा dp_ctrl *dp_ctrl)
अणु
	काष्ठा dp_ctrl_निजी *ctrl;
	काष्ठा dp_io *dp_io;
	काष्ठा phy *phy;

	अगर (!dp_ctrl) अणु
		DRM_ERROR("Invalid input data\n");
		वापस;
	पूर्ण

	ctrl = container_of(dp_ctrl, काष्ठा dp_ctrl_निजी, dp_ctrl);
	dp_io = &ctrl->parser->io;
	phy = dp_io->phy;

	dp_catalog_ctrl_enable_irq(ctrl->catalog, false);
	phy_निकास(phy);

	DRM_DEBUG_DP("Host deinitialized successfully\n");
पूर्ण

अटल bool dp_ctrl_use_fixed_nvid(काष्ठा dp_ctrl_निजी *ctrl)
अणु
	u8 *dpcd = ctrl->panel->dpcd;

	/*
	 * For better पूर्णांकerop experience, used a fixed NVID=0x8000
	 * whenever connected to a VGA करोngle करोwnstream.
	 */
	अगर (drm_dp_is_branch(dpcd))
		वापस (drm_dp_has_quirk(&ctrl->panel->desc,
					 DP_DPCD_QUIRK_CONSTANT_N));

	वापस false;
पूर्ण

अटल पूर्णांक dp_ctrl_reinitialize_मुख्यlink(काष्ठा dp_ctrl_निजी *ctrl)
अणु
	पूर्णांक ret = 0;
	काष्ठा dp_io *dp_io = &ctrl->parser->io;
	काष्ठा phy *phy = dp_io->phy;
	काष्ठा phy_configure_opts_dp *opts_dp = &dp_io->phy_opts.dp;

	dp_catalog_ctrl_मुख्यlink_ctrl(ctrl->catalog, false);
	opts_dp->lanes = ctrl->link->link_params.num_lanes;
	phy_configure(phy, &dp_io->phy_opts);
	/*
	 * Disable and re-enable the मुख्यlink घड़ी since the
	 * link घड़ी might have been adjusted as part of the
	 * link मुख्यtenance.
	 */
	ret = dp_घातer_clk_enable(ctrl->घातer, DP_CTRL_PM, false);
	अगर (ret) अणु
		DRM_ERROR("Failed to disable clocks. ret=%d\n", ret);
		वापस ret;
	पूर्ण
	phy_घातer_off(phy);
	/* hw recommended delay beक्रमe re-enabling घड़ीs */
	msleep(20);

	ret = dp_ctrl_enable_मुख्यlink_घड़ीs(ctrl);
	अगर (ret) अणु
		DRM_ERROR("Failed to enable mainlink clks. ret=%d\n", ret);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक dp_ctrl_deinitialize_मुख्यlink(काष्ठा dp_ctrl_निजी *ctrl)
अणु
	काष्ठा dp_io *dp_io;
	काष्ठा phy *phy;
	पूर्णांक ret;

	dp_io = &ctrl->parser->io;
	phy = dp_io->phy;

	dp_catalog_ctrl_मुख्यlink_ctrl(ctrl->catalog, false);

	dp_catalog_ctrl_reset(ctrl->catalog);

	ret = dp_घातer_clk_enable(ctrl->घातer, DP_CTRL_PM, false);
	अगर (ret) अणु
		DRM_ERROR("Failed to disable link clocks. ret=%d\n", ret);
	पूर्ण

	phy_घातer_off(phy);
	phy_निकास(phy);

	वापस 0;
पूर्ण

अटल पूर्णांक dp_ctrl_link_मुख्यtenance(काष्ठा dp_ctrl_निजी *ctrl)
अणु
	पूर्णांक ret = 0;
	काष्ठा dp_cr_status cr;
	पूर्णांक training_step = DP_TRAINING_NONE;

	dp_ctrl_push_idle(&ctrl->dp_ctrl);

	ctrl->dp_ctrl.pixel_rate = ctrl->panel->dp_mode.drm_mode.घड़ी;

	ret = dp_ctrl_setup_मुख्य_link(ctrl, &cr, &training_step);
	अगर (ret)
		जाओ end;

	dp_ctrl_clear_training_pattern(ctrl);

	dp_catalog_ctrl_state_ctrl(ctrl->catalog, DP_STATE_CTRL_SEND_VIDEO);

	ret = dp_ctrl_रुको4video_पढ़ोy(ctrl);
end:
	वापस ret;
पूर्ण

अटल पूर्णांक dp_ctrl_process_phy_test_request(काष्ठा dp_ctrl_निजी *ctrl)
अणु
	पूर्णांक ret = 0;

	अगर (!ctrl->link->phy_params.phy_test_pattern_sel) अणु
		DRM_DEBUG_DP("no test pattern selected by sink\n");
		वापस ret;
	पूर्ण

	/*
	 * The global reset will need DP link related घड़ीs to be
	 * running. Add the global reset just beक्रमe disabling the
	 * link घड़ीs and core घड़ीs.
	 */
	ret = dp_ctrl_off(&ctrl->dp_ctrl);
	अगर (ret) अणु
		DRM_ERROR("failed to disable DP controller\n");
		वापस ret;
	पूर्ण

	ret = dp_ctrl_on_link(&ctrl->dp_ctrl);
	अगर (!ret)
		ret = dp_ctrl_on_stream(&ctrl->dp_ctrl);
	अन्यथा
		DRM_ERROR("failed to enable DP link controller\n");

	वापस ret;
पूर्ण

अटल bool dp_ctrl_send_phy_test_pattern(काष्ठा dp_ctrl_निजी *ctrl)
अणु
	bool success = false;
	u32 pattern_sent = 0x0;
	u32 pattern_requested = ctrl->link->phy_params.phy_test_pattern_sel;

	DRM_DEBUG_DP("request: 0x%x\n", pattern_requested);

	अगर (dp_catalog_ctrl_update_vx_px(ctrl->catalog,
			ctrl->link->phy_params.v_level,
			ctrl->link->phy_params.p_level)) अणु
		DRM_ERROR("Failed to set v/p levels\n");
		वापस false;
	पूर्ण
	dp_catalog_ctrl_send_phy_pattern(ctrl->catalog, pattern_requested);
	dp_ctrl_update_vx_px(ctrl);
	dp_link_send_test_response(ctrl->link);

	pattern_sent = dp_catalog_ctrl_पढ़ो_phy_pattern(ctrl->catalog);

	चयन (pattern_sent) अणु
	हाल MR_LINK_TRAINING1:
		success = (pattern_requested ==
				DP_PHY_TEST_PATTERN_D10_2);
		अवरोध;
	हाल MR_LINK_SYMBOL_ERM:
		success = ((pattern_requested ==
			DP_PHY_TEST_PATTERN_ERROR_COUNT) ||
				(pattern_requested ==
				DP_PHY_TEST_PATTERN_CP2520));
		अवरोध;
	हाल MR_LINK_PRBS7:
		success = (pattern_requested ==
				DP_PHY_TEST_PATTERN_PRBS7);
		अवरोध;
	हाल MR_LINK_CUSTOM80:
		success = (pattern_requested ==
				DP_PHY_TEST_PATTERN_80BIT_CUSTOM);
		अवरोध;
	हाल MR_LINK_TRAINING4:
		success = (pattern_requested ==
				DP_PHY_TEST_PATTERN_SEL_MASK);
		अवरोध;
	शेष:
		success = false;
	पूर्ण

	DRM_DEBUG_DP("%s: test->0x%x\n", success ? "success" : "failed",
						pattern_requested);
	वापस success;
पूर्ण

व्योम dp_ctrl_handle_sink_request(काष्ठा dp_ctrl *dp_ctrl)
अणु
	काष्ठा dp_ctrl_निजी *ctrl;
	u32 sink_request = 0x0;

	अगर (!dp_ctrl) अणु
		DRM_ERROR("invalid input\n");
		वापस;
	पूर्ण

	ctrl = container_of(dp_ctrl, काष्ठा dp_ctrl_निजी, dp_ctrl);
	sink_request = ctrl->link->sink_request;

	अगर (sink_request & DP_TEST_LINK_PHY_TEST_PATTERN) अणु
		DRM_DEBUG_DP("PHY_TEST_PATTERN request\n");
		अगर (dp_ctrl_process_phy_test_request(ctrl)) अणु
			DRM_ERROR("process phy_test_req failed\n");
			वापस;
		पूर्ण
	पूर्ण

	अगर (sink_request & DP_LINK_STATUS_UPDATED) अणु
		अगर (dp_ctrl_link_मुख्यtenance(ctrl)) अणु
			DRM_ERROR("LM failed: TEST_LINK_TRAINING\n");
			वापस;
		पूर्ण
	पूर्ण

	अगर (sink_request & DP_TEST_LINK_TRAINING) अणु
		dp_link_send_test_response(ctrl->link);
		अगर (dp_ctrl_link_मुख्यtenance(ctrl)) अणु
			DRM_ERROR("LM failed: TEST_LINK_TRAINING\n");
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक dp_ctrl_on_link(काष्ठा dp_ctrl *dp_ctrl)
अणु
	पूर्णांक rc = 0;
	काष्ठा dp_ctrl_निजी *ctrl;
	u32 rate = 0;
	पूर्णांक link_train_max_retries = 5;
	u32 स्थिर phy_cts_pixel_clk_khz = 148500;
	काष्ठा dp_cr_status cr;
	अचिन्हित पूर्णांक training_step;

	अगर (!dp_ctrl)
		वापस -EINVAL;

	ctrl = container_of(dp_ctrl, काष्ठा dp_ctrl_निजी, dp_ctrl);

	rate = ctrl->panel->link_info.rate;

	dp_घातer_clk_enable(ctrl->घातer, DP_CORE_PM, true);

	अगर (ctrl->link->sink_request & DP_TEST_LINK_PHY_TEST_PATTERN) अणु
		DRM_DEBUG_DP("using phy test link parameters\n");
		अगर (!ctrl->panel->dp_mode.drm_mode.घड़ी)
			ctrl->dp_ctrl.pixel_rate = phy_cts_pixel_clk_khz;
	पूर्ण अन्यथा अणु
		ctrl->link->link_params.rate = rate;
		ctrl->link->link_params.num_lanes =
			ctrl->panel->link_info.num_lanes;
		ctrl->dp_ctrl.pixel_rate = ctrl->panel->dp_mode.drm_mode.घड़ी;
	पूर्ण

	DRM_DEBUG_DP("rate=%d, num_lanes=%d, pixel_rate=%d\n",
		ctrl->link->link_params.rate,
		ctrl->link->link_params.num_lanes, ctrl->dp_ctrl.pixel_rate);

	rc = dp_ctrl_enable_मुख्यlink_घड़ीs(ctrl);
	अगर (rc)
		वापस rc;

	जबतक (--link_train_max_retries) अणु
		rc = dp_ctrl_reinitialize_मुख्यlink(ctrl);
		अगर (rc) अणु
			DRM_ERROR("Failed to reinitialize mainlink. rc=%d\n",
					rc);
			अवरोध;
		पूर्ण

		training_step = DP_TRAINING_NONE;
		rc = dp_ctrl_setup_मुख्य_link(ctrl, &cr, &training_step);
		अगर (rc == 0) अणु
			/* training completed successfully */
			अवरोध;
		पूर्ण अन्यथा अगर (training_step == DP_TRAINING_1) अणु
			/* link train_1 failed */
			अगर (!dp_catalog_link_is_connected(ctrl->catalog)) अणु
				अवरोध;
			पूर्ण

			rc = dp_ctrl_link_rate_करोwn_shअगरt(ctrl);
			अगर (rc < 0) अणु /* alपढ़ोy in RBR = 1.6G */
				अगर (cr.lane_0_1 & DP_LANE0_1_CR_DONE) अणु
					/*
					 * some lanes are पढ़ोy,
					 * reduce lane number
					 */
					rc = dp_ctrl_link_lane_करोwn_shअगरt(ctrl);
					अगर (rc < 0) अणु /* lane == 1 alपढ़ोy */
						/* end with failure */
						अवरोध;
					पूर्ण
				पूर्ण अन्यथा अणु
					/* end with failure */
					अवरोध; /* lane == 1 alपढ़ोy */
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अगर (training_step == DP_TRAINING_2) अणु
			/* link train_2 failed, lower lane rate */
			अगर (!dp_catalog_link_is_connected(ctrl->catalog)) अणु
				अवरोध;
			पूर्ण

			rc = dp_ctrl_link_lane_करोwn_shअगरt(ctrl);
			अगर (rc < 0) अणु
				/* end with failure */
				अवरोध; /* lane == 1 alपढ़ोy */
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (ctrl->link->sink_request & DP_TEST_LINK_PHY_TEST_PATTERN)
		वापस rc;

	/* stop txing train pattern */
	dp_ctrl_clear_training_pattern(ctrl);

	/*
	 * keep transmitting idle pattern until video पढ़ोy
	 * to aव्योम मुख्य link from loss of sync
	 */
	अगर (rc == 0)  /* link train successfully */
		dp_ctrl_push_idle(dp_ctrl);
	अन्यथा  अणु
		/* link training failed */
		dp_ctrl_deinitialize_मुख्यlink(ctrl);
		rc = -ECONNRESET;
	पूर्ण

	वापस rc;
पूर्ण

पूर्णांक dp_ctrl_on_stream(काष्ठा dp_ctrl *dp_ctrl)
अणु
	u32 rate = 0;
	पूर्णांक ret = 0;
	bool मुख्यlink_पढ़ोy = false;
	काष्ठा dp_ctrl_निजी *ctrl;

	अगर (!dp_ctrl)
		वापस -EINVAL;

	ctrl = container_of(dp_ctrl, काष्ठा dp_ctrl_निजी, dp_ctrl);

	rate = ctrl->panel->link_info.rate;

	ctrl->link->link_params.rate = rate;
	ctrl->link->link_params.num_lanes = ctrl->panel->link_info.num_lanes;
	ctrl->dp_ctrl.pixel_rate = ctrl->panel->dp_mode.drm_mode.घड़ी;

	DRM_DEBUG_DP("rate=%d, num_lanes=%d, pixel_rate=%d\n",
		ctrl->link->link_params.rate,
		ctrl->link->link_params.num_lanes, ctrl->dp_ctrl.pixel_rate);

	अगर (!dp_घातer_clk_status(ctrl->घातer, DP_CTRL_PM)) अणु /* link clk is off */
		ret = dp_ctrl_enable_मुख्यlink_घड़ीs(ctrl);
		अगर (ret) अणु
			DRM_ERROR("Failed to start link clocks. ret=%d\n", ret);
			जाओ end;
		पूर्ण
	पूर्ण

	ret = dp_ctrl_enable_stream_घड़ीs(ctrl);
	अगर (ret) अणु
		DRM_ERROR("Failed to start pixel clocks. ret=%d\n", ret);
		जाओ end;
	पूर्ण

	अगर (ctrl->link->sink_request & DP_TEST_LINK_PHY_TEST_PATTERN) अणु
		dp_ctrl_send_phy_test_pattern(ctrl);
		वापस 0;
	पूर्ण

	/*
	 * Set up transfer unit values and set controller state to send
	 * video.
	 */
	reinit_completion(&ctrl->video_comp);

	dp_ctrl_configure_source_params(ctrl);

	dp_catalog_ctrl_config_msa(ctrl->catalog,
		ctrl->link->link_params.rate,
		ctrl->dp_ctrl.pixel_rate, dp_ctrl_use_fixed_nvid(ctrl));

	dp_ctrl_setup_tr_unit(ctrl);

	dp_catalog_ctrl_state_ctrl(ctrl->catalog, DP_STATE_CTRL_SEND_VIDEO);

	ret = dp_ctrl_रुको4video_पढ़ोy(ctrl);
	अगर (ret)
		वापस ret;

	मुख्यlink_पढ़ोy = dp_catalog_ctrl_मुख्यlink_पढ़ोy(ctrl->catalog);
	DRM_DEBUG_DP("mainlink %s\n", मुख्यlink_पढ़ोy ? "READY" : "NOT READY");

end:
	वापस ret;
पूर्ण

पूर्णांक dp_ctrl_off(काष्ठा dp_ctrl *dp_ctrl)
अणु
	काष्ठा dp_ctrl_निजी *ctrl;
	काष्ठा dp_io *dp_io;
	काष्ठा phy *phy;
	पूर्णांक ret = 0;

	अगर (!dp_ctrl)
		वापस -EINVAL;

	ctrl = container_of(dp_ctrl, काष्ठा dp_ctrl_निजी, dp_ctrl);
	dp_io = &ctrl->parser->io;
	phy = dp_io->phy;

	dp_catalog_ctrl_मुख्यlink_ctrl(ctrl->catalog, false);

	dp_catalog_ctrl_reset(ctrl->catalog);

	ret = dp_घातer_clk_enable(ctrl->घातer, DP_STREAM_PM, false);
	अगर (ret)
		DRM_ERROR("Failed to disable pixel clocks. ret=%d\n", ret);

	ret = dp_घातer_clk_enable(ctrl->घातer, DP_CTRL_PM, false);
	अगर (ret) अणु
		DRM_ERROR("Failed to disable link clocks. ret=%d\n", ret);
	पूर्ण

	phy_घातer_off(phy);
	phy_निकास(phy);

	DRM_DEBUG_DP("DP off done\n");
	वापस ret;
पूर्ण

व्योम dp_ctrl_isr(काष्ठा dp_ctrl *dp_ctrl)
अणु
	काष्ठा dp_ctrl_निजी *ctrl;
	u32 isr;

	अगर (!dp_ctrl)
		वापस;

	ctrl = container_of(dp_ctrl, काष्ठा dp_ctrl_निजी, dp_ctrl);

	isr = dp_catalog_ctrl_get_पूर्णांकerrupt(ctrl->catalog);

	अगर (isr & DP_CTRL_INTR_READY_FOR_VIDEO) अणु
		DRM_DEBUG_DP("dp_video_ready\n");
		complete(&ctrl->video_comp);
	पूर्ण

	अगर (isr & DP_CTRL_INTR_IDLE_PATTERN_SENT) अणु
		DRM_DEBUG_DP("idle_patterns_sent\n");
		complete(&ctrl->idle_comp);
	पूर्ण
पूर्ण

काष्ठा dp_ctrl *dp_ctrl_get(काष्ठा device *dev, काष्ठा dp_link *link,
			काष्ठा dp_panel *panel,	काष्ठा drm_dp_aux *aux,
			काष्ठा dp_घातer *घातer, काष्ठा dp_catalog *catalog,
			काष्ठा dp_parser *parser)
अणु
	काष्ठा dp_ctrl_निजी *ctrl;
	पूर्णांक ret;

	अगर (!dev || !panel || !aux ||
	    !link || !catalog) अणु
		DRM_ERROR("invalid input\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	ctrl = devm_kzalloc(dev, माप(*ctrl), GFP_KERNEL);
	अगर (!ctrl) अणु
		DRM_ERROR("Mem allocation failure\n");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	ctrl->opp_table = dev_pm_opp_set_clkname(dev, "ctrl_link");
	अगर (IS_ERR(ctrl->opp_table)) अणु
		dev_err(dev, "invalid DP OPP table in device tree\n");
		/* caller करो PTR_ERR(ctrl->opp_table) */
		वापस (काष्ठा dp_ctrl *)ctrl->opp_table;
	पूर्ण

	/* OPP table is optional */
	ret = dev_pm_opp_of_add_table(dev);
	अगर (ret) अणु
		dev_err(dev, "failed to add DP OPP table\n");
		dev_pm_opp_put_clkname(ctrl->opp_table);
		ctrl->opp_table = शून्य;
	पूर्ण

	init_completion(&ctrl->idle_comp);
	init_completion(&ctrl->video_comp);

	/* in parameters */
	ctrl->parser   = parser;
	ctrl->panel    = panel;
	ctrl->घातer    = घातer;
	ctrl->aux      = aux;
	ctrl->link     = link;
	ctrl->catalog  = catalog;
	ctrl->dev      = dev;

	वापस &ctrl->dp_ctrl;
पूर्ण

व्योम dp_ctrl_put(काष्ठा dp_ctrl *dp_ctrl)
अणु
	काष्ठा dp_ctrl_निजी *ctrl;

	ctrl = container_of(dp_ctrl, काष्ठा dp_ctrl_निजी, dp_ctrl);

	अगर (ctrl->opp_table) अणु
		dev_pm_opp_of_हटाओ_table(ctrl->dev);
		dev_pm_opp_put_clkname(ctrl->opp_table);
		ctrl->opp_table = शून्य;
	पूर्ण
पूर्ण
