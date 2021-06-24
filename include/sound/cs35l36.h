<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * linux/sound/cs35l36.h -- Platक्रमm data क्रम CS35L36
 *
 * Copyright 2018 Cirrus Logic, Inc.
 *
 * Author: James Schulman <james.schulman@cirrus.com>
 *
 */

#अगर_अघोषित __CS35L36_H
#घोषणा __CS35L36_H

काष्ठा cs35l36_vpbr_cfg अणु
	bool is_present;
	bool vpbr_en;
	पूर्णांक vpbr_thld;
	पूर्णांक vpbr_atk_rate;
	पूर्णांक vpbr_atk_vol;
	पूर्णांक vpbr_max_attn;
	पूर्णांक vpbr_रुको;
	पूर्णांक vpbr_rel_rate;
	पूर्णांक vpbr_mute_en;
पूर्ण;

काष्ठा cs35l36_platक्रमm_data अणु
	bool multi_amp_mode;
	bool dcm_mode;
	bool amp_pcm_inv;
	bool imon_pol_inv;
	bool vmon_pol_inv;
	पूर्णांक boost_ind;
	पूर्णांक bst_vctl;
	पूर्णांक bst_vctl_sel;
	पूर्णांक bst_ipk;
	bool बाह्य_boost;
	पूर्णांक temp_warn_thld;
	पूर्णांक irq_drv_sel;
	पूर्णांक irq_gpio_sel;
	काष्ठा cs35l36_vpbr_cfg vpbr_config;
पूर्ण;

#पूर्ण_अगर /* __CS35L36_H */
