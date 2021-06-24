<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2021 MediaTek Inc.
 * Author: Argus Lin <argus.lin@mediatek.com>
 */

#अगर_अघोषित _ACCDET_H_
#घोषणा _ACCDET_H_

#समावेश <linux/प्रकार.स>
#समावेश <linux/माला.स>

#घोषणा ACCDET_DEVNAME "accdet"

#घोषणा HEADSET_MODE_1		(1)
#घोषणा HEADSET_MODE_2		(2)
#घोषणा HEADSET_MODE_6		(6)

#घोषणा MT6359_ACCDET_NUM_BUTTONS 4
#घोषणा MT6359_ACCDET_JACK_MASK (SND_JACK_HEADPHONE | \
				SND_JACK_HEADSET | \
				SND_JACK_BTN_0 | \
				SND_JACK_BTN_1 | \
				SND_JACK_BTN_2 | \
				SND_JACK_BTN_3)
#घोषणा MT6359_ACCDET_BTN_MASK (SND_JACK_BTN_0 | \
				SND_JACK_BTN_1 | \
				SND_JACK_BTN_2 | \
				SND_JACK_BTN_3)

क्रमागत eपूर्णांक_moisture_status अणु
	M_PLUG_IN =		0,
	M_WATER_IN =		1,
	M_HP_PLUG_IN =		2,
	M_PLUG_OUT =		3,
	M_NO_ACT =		4,
	M_UNKNOWN =		5,
पूर्ण;

क्रमागत अणु
	accdet_state000 = 0,
	accdet_state001,
	accdet_state010,
	accdet_state011,
	accdet_auxadc,
	eपूर्णांक_state000,
	eपूर्णांक_state001,
	eपूर्णांक_state010,
	eपूर्णांक_state011,
	eपूर्णांक_inverter_state000,
पूर्ण;

काष्ठा three_key_threshold अणु
	अचिन्हित पूर्णांक mid;
	अचिन्हित पूर्णांक up;
	अचिन्हित पूर्णांक करोwn;
पूर्ण;

काष्ठा four_key_threshold अणु
	अचिन्हित पूर्णांक mid;
	अचिन्हित पूर्णांक voice;
	अचिन्हित पूर्णांक up;
	अचिन्हित पूर्णांक करोwn;
पूर्ण;

काष्ठा pwm_deb_settings अणु
	अचिन्हित पूर्णांक pwm_width;
	अचिन्हित पूर्णांक pwm_thresh;
	अचिन्हित पूर्णांक fall_delay;
	अचिन्हित पूर्णांक rise_delay;
	अचिन्हित पूर्णांक debounce0;
	अचिन्हित पूर्णांक debounce1;
	अचिन्हित पूर्णांक debounce3;
	अचिन्हित पूर्णांक debounce4;
	अचिन्हित पूर्णांक eपूर्णांक_pwm_width;
	अचिन्हित पूर्णांक eपूर्णांक_pwm_thresh;
	अचिन्हित पूर्णांक eपूर्णांक_debounce0;
	अचिन्हित पूर्णांक eपूर्णांक_debounce1;
	अचिन्हित पूर्णांक eपूर्णांक_debounce2;
	अचिन्हित पूर्णांक eपूर्णांक_debounce3;
	अचिन्हित पूर्णांक eपूर्णांक_inverter_debounce;

पूर्ण;

काष्ठा dts_data अणु
	अचिन्हित पूर्णांक mic_vol;
	अचिन्हित पूर्णांक mic_mode;
	अचिन्हित पूर्णांक plugout_deb;
	अचिन्हित पूर्णांक eपूर्णांक_pol;
	काष्ठा pwm_deb_settings *pwm_deb;
	काष्ठा three_key_threshold three_key;
	काष्ठा four_key_threshold four_key;
	अचिन्हित पूर्णांक moisture_detect_enable;
	अचिन्हित पूर्णांक eपूर्णांक_detect_mode;
	अचिन्हित पूर्णांक eपूर्णांक_use_ext_res;
	अचिन्हित पूर्णांक eपूर्णांक_comp_vth;
	अचिन्हित पूर्णांक moisture_detect_mode;
	अचिन्हित पूर्णांक moisture_comp_vth;
	अचिन्हित पूर्णांक moisture_comp_vref2;
	अचिन्हित पूर्णांक moisture_use_ext_res;
पूर्ण;

काष्ठा mt6359_accdet अणु
	काष्ठा snd_soc_jack *jack;
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	काष्ठा dts_data *data;
	अचिन्हित पूर्णांक caps;
	पूर्णांक accdet_irq;
	पूर्णांक accdet_eपूर्णांक0;
	पूर्णांक accdet_eपूर्णांक1;
	काष्ठा mutex res_lock; /* lock protection */
	bool jack_plugged;
	अचिन्हित पूर्णांक jack_type;
	अचिन्हित पूर्णांक btn_type;
	अचिन्हित पूर्णांक accdet_status;
	अचिन्हित पूर्णांक pre_accdet_status;
	अचिन्हित पूर्णांक cali_voltage;
	अचिन्हित पूर्णांक jd_sts;
	काष्ठा work_काष्ठा accdet_work;
	काष्ठा workqueue_काष्ठा *accdet_workqueue;
	काष्ठा work_काष्ठा jd_work;
	काष्ठा workqueue_काष्ठा *jd_workqueue;
पूर्ण;

पूर्णांक mt6359_accdet_enable_jack_detect(काष्ठा snd_soc_component *component,
				     काष्ठा snd_soc_jack *jack);
#पूर्ण_अगर
