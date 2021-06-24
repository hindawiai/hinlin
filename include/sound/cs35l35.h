<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * linux/sound/cs35l35.h -- Platक्रमm data क्रम CS35l35
 *
 * Copyright (c) 2016 Cirrus Logic Inc.
 */

#अगर_अघोषित __CS35L35_H
#घोषणा __CS35L35_H

काष्ठा classh_cfg अणु
	/*
	 * Class H Algorithm Control Variables
	 * You can either have it करोne
	 * स्वतःmatically or you can adjust
	 * these variables क्रम tuning
	 *
	 * अगर you करो not enable the पूर्णांकernal algorithm
	 * you will get a set of mixer controls क्रम
	 * Class H tuning
	 *
	 * Section 4.3 of the datasheet
	 */
	bool classh_bst_override;
	bool classh_algo_enable;
	पूर्णांक classh_bst_max_limit;
	पूर्णांक classh_mem_depth;
	पूर्णांक classh_release_rate;
	पूर्णांक classh_headroom;
	पूर्णांक classh_wk_fet_disable;
	पूर्णांक classh_wk_fet_delay;
	पूर्णांक classh_wk_fet_thld;
	पूर्णांक classh_vpch_स्वतः;
	पूर्णांक classh_vpch_rate;
	पूर्णांक classh_vpch_man;
पूर्ण;

काष्ठा monitor_cfg अणु
	/*
	 * Signal Monitor Data
	 * highly configurable संकेत monitoring
	 * data positioning and dअगरferent types of
	 * monitoring data.
	 *
	 * Section 4.8.2 - 4.8.4 of the datasheet
	 */
	bool is_present;
	bool imon_specs;
	bool vmon_specs;
	bool vpmon_specs;
	bool vbsपंचांगon_specs;
	bool vpbrstat_specs;
	bool zerofill_specs;
	u8 imon_dpth;
	u8 imon_loc;
	u8 imon_frm;
	u8 imon_scale;
	u8 vmon_dpth;
	u8 vmon_loc;
	u8 vmon_frm;
	u8 vpmon_dpth;
	u8 vpmon_loc;
	u8 vpmon_frm;
	u8 vbsपंचांगon_dpth;
	u8 vbsपंचांगon_loc;
	u8 vbsपंचांगon_frm;
	u8 vpbrstat_dpth;
	u8 vpbrstat_loc;
	u8 vpbrstat_frm;
	u8 zerofill_dpth;
	u8 zerofill_loc;
	u8 zerofill_frm;
पूर्ण;

काष्ठा cs35l35_platक्रमm_data अणु

	/* Stereo (2 Device) */
	bool stereo;
	/* serial port drive strength */
	पूर्णांक sp_drv_str;
	/* serial port drive in unused slots */
	पूर्णांक sp_drv_unused;
	/* Boost Power Down with FET */
	bool bst_pdn_fet_on;
	/* Boost Voltage : used अगर ClassH Algo Enabled */
	पूर्णांक bst_vctl;
	/* Boost Converter Peak Current CTRL */
	पूर्णांक bst_ipk;
	/* Amp Gain Zero Cross */
	bool gain_zc;
	/* Audio Input Location */
	पूर्णांक aud_channel;
	/* Advisory Input Location */
	पूर्णांक adv_channel;
	/* Shared Boost क्रम stereo */
	bool shared_bst;
	/* Specअगरies this amp is using an बाह्यal boost supply */
	bool ext_bst;
	/* Inductor Value */
	पूर्णांक boost_ind;
	/* ClassH Algorithm */
	काष्ठा classh_cfg classh_algo;
	/* Monitor Config */
	काष्ठा monitor_cfg mon_cfg;
पूर्ण;

#पूर्ण_अगर /* __CS35L35_H */
