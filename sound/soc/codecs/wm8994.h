<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * wm8994.h  --  WM8994 Soc Audio driver
 */

#अगर_अघोषित _WM8994_H
#घोषणा _WM8994_H

#समावेश <linux/clk.h>
#समावेश <sound/soc.h>
#समावेश <linux/firmware.h>
#समावेश <linux/completion.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/mutex.h>

#समावेश "wm_hubs.h"

क्रमागत अणु
	WM8994_MCLK1,
	WM8994_MCLK2,
	WM8994_NUM_MCLK
पूर्ण;

/* Sources क्रम AIF1/2 SYSCLK - use with set_dai_sysclk() */
#घोषणा WM8994_SYSCLK_MCLK1 1
#घोषणा WM8994_SYSCLK_MCLK2 2
#घोषणा WM8994_SYSCLK_FLL1  3
#घोषणा WM8994_SYSCLK_FLL2  4

/* OPCLK is also configured with set_dai_sysclk, specअगरy भागision*10 as rate. */
#घोषणा WM8994_SYSCLK_OPCLK 5

#घोषणा WM8994_FLL1 1
#घोषणा WM8994_FLL2 2

#घोषणा WM8994_FLL_SRC_MCLK1    1
#घोषणा WM8994_FLL_SRC_MCLK2    2
#घोषणा WM8994_FLL_SRC_LRCLK    3
#घोषणा WM8994_FLL_SRC_BCLK     4
#घोषणा WM8994_FLL_SRC_INTERNAL 5

क्रमागत wm8994_vmid_mode अणु
	WM8994_VMID_NORMAL,
	WM8994_VMID_FORCE,
पूर्ण;

प्रकार व्योम (*wm1811_micdet_cb)(व्योम *data);
प्रकार व्योम (*wm1811_mic_id_cb)(व्योम *data, u16 status);

पूर्णांक wm8994_mic_detect(काष्ठा snd_soc_component *component, काष्ठा snd_soc_jack *jack,
		      पूर्णांक micbias);
पूर्णांक wm8958_mic_detect(काष्ठा snd_soc_component *component, काष्ठा snd_soc_jack *jack,
		      wm1811_micdet_cb det_cb, व्योम *det_cb_data,
		      wm1811_mic_id_cb id_cb, व्योम *id_cb_data);

पूर्णांक wm8994_vmid_mode(काष्ठा snd_soc_component *component, क्रमागत wm8994_vmid_mode mode);

पूर्णांक wm8958_aअगर_ev(काष्ठा snd_soc_dapm_widget *w,
		  काष्ठा snd_kcontrol *kcontrol, पूर्णांक event);

व्योम wm8958_dsp2_init(काष्ठा snd_soc_component *component);

काष्ठा wm8994_micdet अणु
	काष्ठा snd_soc_jack *jack;
	bool detecting;
पूर्ण;

/* codec निजी data */
काष्ठा wm8994_fll_config अणु
	पूर्णांक src;
	पूर्णांक in;
	पूर्णांक out;
पूर्ण;

#घोषणा WM8994_NUM_DRC 3
#घोषणा WM8994_NUM_EQ  3

काष्ठा wm8994;

काष्ठा wm8994_priv अणु
	काष्ठा wm_hubs_data hubs;
	काष्ठा wm8994 *wm8994;
	काष्ठा clk_bulk_data mclk[WM8994_NUM_MCLK];
	पूर्णांक sysclk[2];
	पूर्णांक sysclk_rate[2];
	पूर्णांक mclk_rate[2];
	पूर्णांक aअगरclk[2];
	पूर्णांक aअगरभाग[2];
	पूर्णांक channels[2];
	काष्ठा wm8994_fll_config fll[2], fll_suspend[2];
	काष्ठा completion fll_locked[2];
	bool fll_locked_irq;
	bool fll_byp;
	bool clk_has_run;

	पूर्णांक vmid_refcount;
	पूर्णांक active_refcount;
	क्रमागत wm8994_vmid_mode vmid_mode;

	पूर्णांक dac_rates[2];
	पूर्णांक lrclk_shared[2];

	पूर्णांक mbc_ena[3];
	पूर्णांक hpf1_ena[3];
	पूर्णांक hpf2_ena[3];
	पूर्णांक vss_ena[3];
	पूर्णांक enh_eq_ena[3];

	/* Platक्रमm dependant DRC configuration */
	स्थिर अक्षर **drc_texts;
	पूर्णांक drc_cfg[WM8994_NUM_DRC];
	काष्ठा soc_क्रमागत drc_क्रमागत;

	/* Platक्रमm dependant ReTune mobile configuration */
	पूर्णांक num_retune_mobile_texts;
	स्थिर अक्षर **retune_mobile_texts;
	पूर्णांक retune_mobile_cfg[WM8994_NUM_EQ];
	काष्ठा soc_क्रमागत retune_mobile_क्रमागत;

	/* Platक्रमm dependant MBC configuration */
	पूर्णांक mbc_cfg;
	स्थिर अक्षर **mbc_texts;
	काष्ठा soc_क्रमागत mbc_क्रमागत;

	/* Platक्रमm dependant VSS configuration */
	पूर्णांक vss_cfg;
	स्थिर अक्षर **vss_texts;
	काष्ठा soc_क्रमागत vss_क्रमागत;

	/* Platक्रमm dependant VSS HPF configuration */
	पूर्णांक vss_hpf_cfg;
	स्थिर अक्षर **vss_hpf_texts;
	काष्ठा soc_क्रमागत vss_hpf_क्रमागत;

	/* Platक्रमm dependant enhanced EQ configuration */
	पूर्णांक enh_eq_cfg;
	स्थिर अक्षर **enh_eq_texts;
	काष्ठा soc_क्रमागत enh_eq_क्रमागत;

	काष्ठा mutex accdet_lock;
	काष्ठा wm8994_micdet micdet[2];
	काष्ठा delayed_work mic_work;
	काष्ठा delayed_work खोलो_circuit_work;
	काष्ठा delayed_work mic_complete_work;
	u16 mic_status;
	bool mic_detecting;
	bool jack_mic;
	पूर्णांक btn_mask;
	bool jackdet;
	पूर्णांक jackdet_mode;
	काष्ठा delayed_work jackdet_bootstrap;

	पूर्णांक micdet_irq;
	wm1811_micdet_cb micd_cb;
	व्योम *micd_cb_data;
	wm1811_mic_id_cb mic_id_cb;
	व्योम *mic_id_cb_data;

	अचिन्हित पूर्णांक aअगर1clk_enable:1;
	अचिन्हित पूर्णांक aअगर2clk_enable:1;

	अचिन्हित पूर्णांक aअगर1clk_disable:1;
	अचिन्हित पूर्णांक aअगर2clk_disable:1;

	काष्ठा mutex fw_lock;
	पूर्णांक dsp_active;
	स्थिर काष्ठा firmware *cur_fw;
	स्थिर काष्ठा firmware *mbc;
	स्थिर काष्ठा firmware *mbc_vss;
	स्थिर काष्ठा firmware *enh_eq;
पूर्ण;

#पूर्ण_अगर
