<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * wm_hubs.h  --  WM899x common code
 *
 * Copyright 2009 Wolfson Microelectronics plc
 *
 * Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
 */

#अगर_अघोषित _WM_HUBS_H
#घोषणा _WM_HUBS_H

#समावेश <linux/completion.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <sound/control.h>

काष्ठा snd_soc_component;

बाह्य स्थिर अचिन्हित पूर्णांक wm_hubs_spkmix_tlv[];

/* This *must* be the first element of the codec->निजी_data काष्ठा */
काष्ठा wm_hubs_data अणु
	पूर्णांक dcs_codes_l;
	पूर्णांक dcs_codes_r;
	पूर्णांक dcs_पढ़ोback_mode;
	पूर्णांक hp_startup_mode;
	पूर्णांक series_startup;
	पूर्णांक no_series_update;
	bool micd_scthr;

	bool no_cache_dac_hp_direct;
	काष्ठा list_head dcs_cache;
	bool (*check_class_w_digital)(काष्ठा snd_soc_component *);

	पूर्णांक micb1_delay;
	पूर्णांक micb2_delay;

	bool lineout1_se;
	bool lineout1n_ena;
	bool lineout1p_ena;

	bool lineout2_se;
	bool lineout2n_ena;
	bool lineout2p_ena;

	bool dcs_करोne_irq;
	काष्ठा completion dcs_करोne;

	काष्ठा snd_soc_component *component;
पूर्ण;

बाह्य पूर्णांक wm_hubs_add_analogue_controls(काष्ठा snd_soc_component *);
बाह्य पूर्णांक wm_hubs_add_analogue_routes(काष्ठा snd_soc_component *, पूर्णांक, पूर्णांक);
बाह्य पूर्णांक wm_hubs_handle_analogue_pdata(काष्ठा snd_soc_component *,
					 पूर्णांक lineout1_dअगरf, पूर्णांक lineout2_dअगरf,
					 पूर्णांक lineout1fb, पूर्णांक lineout2fb,
					 पूर्णांक jd_scthr, पूर्णांक jd_thr,
					 पूर्णांक micbias1_delay, पूर्णांक micbias2_delay,
					 पूर्णांक micbias1_lvl, पूर्णांक micbias2_lvl);

बाह्य irqवापस_t wm_hubs_dcs_करोne(पूर्णांक irq, व्योम *data);
बाह्य व्योम wm_hubs_vmid_ena(काष्ठा snd_soc_component *component);
बाह्य व्योम wm_hubs_set_bias_level(काष्ठा snd_soc_component *component,
				   क्रमागत snd_soc_bias_level level);
बाह्य व्योम wm_hubs_update_class_w(काष्ठा snd_soc_component *component);

बाह्य स्थिर काष्ठा snd_kcontrol_new wm_hubs_hpl_mux;
बाह्य स्थिर काष्ठा snd_kcontrol_new wm_hubs_hpr_mux;

#पूर्ण_अगर
