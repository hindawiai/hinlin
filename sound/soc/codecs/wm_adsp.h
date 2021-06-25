<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * wm_adsp.h  --  Wolfson ADSP support
 *
 * Copyright 2012 Wolfson Microelectronics plc
 *
 * Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
 */

#अगर_अघोषित __WM_ADSP_H
#घोषणा __WM_ADSP_H

#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/compress_driver.h>

#समावेश "wmfw.h"

/* Return values क्रम wm_adsp_compr_handle_irq */
#घोषणा WM_ADSP_COMPR_OK                 0
#घोषणा WM_ADSP_COMPR_VOICE_TRIGGER      1

#घोषणा WM_ADSP2_REGION_0 BIT(0)
#घोषणा WM_ADSP2_REGION_1 BIT(1)
#घोषणा WM_ADSP2_REGION_2 BIT(2)
#घोषणा WM_ADSP2_REGION_3 BIT(3)
#घोषणा WM_ADSP2_REGION_4 BIT(4)
#घोषणा WM_ADSP2_REGION_5 BIT(5)
#घोषणा WM_ADSP2_REGION_6 BIT(6)
#घोषणा WM_ADSP2_REGION_7 BIT(7)
#घोषणा WM_ADSP2_REGION_8 BIT(8)
#घोषणा WM_ADSP2_REGION_9 BIT(9)
#घोषणा WM_ADSP2_REGION_1_9 (WM_ADSP2_REGION_1 | \
		WM_ADSP2_REGION_2 | WM_ADSP2_REGION_3 | \
		WM_ADSP2_REGION_4 | WM_ADSP2_REGION_5 | \
		WM_ADSP2_REGION_6 | WM_ADSP2_REGION_7 | \
		WM_ADSP2_REGION_8 | WM_ADSP2_REGION_9)
#घोषणा WM_ADSP2_REGION_ALL (WM_ADSP2_REGION_0 | WM_ADSP2_REGION_1_9)

काष्ठा wm_adsp_region अणु
	पूर्णांक type;
	अचिन्हित पूर्णांक base;
पूर्ण;

काष्ठा wm_adsp_alg_region अणु
	काष्ठा list_head list;
	अचिन्हित पूर्णांक alg;
	पूर्णांक type;
	अचिन्हित पूर्णांक base;
पूर्ण;

काष्ठा wm_adsp_compr;
काष्ठा wm_adsp_compr_buf;
काष्ठा wm_adsp_ops;

काष्ठा wm_adsp अणु
	स्थिर अक्षर *part;
	स्थिर अक्षर *name;
	स्थिर अक्षर *fwf_name;
	पूर्णांक rev;
	पूर्णांक num;
	पूर्णांक type;
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	काष्ठा snd_soc_component *component;

	काष्ठा wm_adsp_ops *ops;

	अचिन्हित पूर्णांक base;
	अचिन्हित पूर्णांक base_sysinfo;
	अचिन्हित पूर्णांक sysclk_reg;
	अचिन्हित पूर्णांक sysclk_mask;
	अचिन्हित पूर्णांक sysclk_shअगरt;

	काष्ठा list_head alg_regions;

	अचिन्हित पूर्णांक fw_id;
	अचिन्हित पूर्णांक fw_id_version;
	अचिन्हित पूर्णांक fw_venकरोr_id;

	स्थिर काष्ठा wm_adsp_region *mem;
	पूर्णांक num_mems;

	पूर्णांक fw;
	पूर्णांक fw_ver;

	bool preloaded;
	bool booted;
	bool running;
	bool fatal_error;

	काष्ठा list_head ctl_list;

	काष्ठा work_काष्ठा boot_work;

	काष्ठा list_head compr_list;
	काष्ठा list_head buffer_list;

	काष्ठा mutex pwr_lock;

	अचिन्हित पूर्णांक lock_regions;

#अगर_घोषित CONFIG_DEBUG_FS
	काष्ठा dentry *debugfs_root;
	अक्षर *wmfw_file_name;
	अक्षर *bin_file_name;
#पूर्ण_अगर

पूर्ण;

काष्ठा wm_adsp_ops अणु
	अचिन्हित पूर्णांक sys_config_size;

	bool (*validate_version)(काष्ठा wm_adsp *dsp, अचिन्हित पूर्णांक version);
	अचिन्हित पूर्णांक (*parse_sizes)(काष्ठा wm_adsp *dsp,
				    स्थिर अक्षर * स्थिर file,
				    अचिन्हित पूर्णांक pos,
				    स्थिर काष्ठा firmware *firmware);
	पूर्णांक (*setup_algs)(काष्ठा wm_adsp *dsp);
	अचिन्हित पूर्णांक (*region_to_reg)(काष्ठा wm_adsp_region स्थिर *mem,
				      अचिन्हित पूर्णांक offset);

	व्योम (*show_fw_status)(काष्ठा wm_adsp *dsp);
	व्योम (*stop_watchकरोg)(काष्ठा wm_adsp *dsp);

	पूर्णांक (*enable_memory)(काष्ठा wm_adsp *dsp);
	व्योम (*disable_memory)(काष्ठा wm_adsp *dsp);
	पूर्णांक (*lock_memory)(काष्ठा wm_adsp *dsp, अचिन्हित पूर्णांक lock_regions);

	पूर्णांक (*enable_core)(काष्ठा wm_adsp *dsp);
	व्योम (*disable_core)(काष्ठा wm_adsp *dsp);

	पूर्णांक (*start_core)(काष्ठा wm_adsp *dsp);
	व्योम (*stop_core)(काष्ठा wm_adsp *dsp);
पूर्ण;

#घोषणा WM_ADSP1(wname, num) \
	SND_SOC_DAPM_PGA_E(wname, SND_SOC_NOPM, num, 0, शून्य, 0, \
		wm_adsp1_event, SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD)

#घोषणा WM_ADSP2_PRELOAD_SWITCH(wname, num) \
	SOC_SINGLE_EXT(wname " Preload Switch", SND_SOC_NOPM, num, 1, 0, \
		wm_adsp2_preloader_get, wm_adsp2_preloader_put)

#घोषणा WM_ADSP2(wname, num, event_fn) \
	SND_SOC_DAPM_SPK(wname " Preload", शून्य), \
अणु	.id = snd_soc_dapm_supply, .name = wname " Preloader", \
	.reg = SND_SOC_NOPM, .shअगरt = num, .event = event_fn, \
	.event_flags = SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_PRE_PMD, \
	.subseq = 100, /* Ensure we run after SYSCLK supply widget */ पूर्ण, \
अणु	.id = snd_soc_dapm_out_drv, .name = wname, \
	.reg = SND_SOC_NOPM, .shअगरt = num, .event = wm_adsp_event, \
	.event_flags = SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD पूर्ण

#घोषणा WM_ADSP_FW_CONTROL(dspname, num) \
	SOC_ENUM_EXT(dspname " Firmware", wm_adsp_fw_क्रमागत[num], \
		     wm_adsp_fw_get, wm_adsp_fw_put)

बाह्य स्थिर काष्ठा soc_क्रमागत wm_adsp_fw_क्रमागत[];

पूर्णांक wm_adsp1_init(काष्ठा wm_adsp *dsp);
पूर्णांक wm_adsp2_init(काष्ठा wm_adsp *dsp);
व्योम wm_adsp2_हटाओ(काष्ठा wm_adsp *dsp);
पूर्णांक wm_adsp2_component_probe(काष्ठा wm_adsp *dsp, काष्ठा snd_soc_component *component);
पूर्णांक wm_adsp2_component_हटाओ(काष्ठा wm_adsp *dsp, काष्ठा snd_soc_component *component);
पूर्णांक wm_halo_init(काष्ठा wm_adsp *dsp);

पूर्णांक wm_adsp1_event(काष्ठा snd_soc_dapm_widget *w,
		   काष्ठा snd_kcontrol *kcontrol, पूर्णांक event);

पूर्णांक wm_adsp_early_event(काष्ठा snd_soc_dapm_widget *w,
			काष्ठा snd_kcontrol *kcontrol, पूर्णांक event);

irqवापस_t wm_adsp2_bus_error(पूर्णांक irq, व्योम *data);
irqवापस_t wm_halo_bus_error(पूर्णांक irq, व्योम *data);
irqवापस_t wm_halo_wdt_expire(पूर्णांक irq, व्योम *data);

पूर्णांक wm_adsp_event(काष्ठा snd_soc_dapm_widget *w,
		  काष्ठा snd_kcontrol *kcontrol, पूर्णांक event);

पूर्णांक wm_adsp2_set_dspclk(काष्ठा snd_soc_dapm_widget *w, अचिन्हित पूर्णांक freq);

पूर्णांक wm_adsp2_preloader_get(काष्ठा snd_kcontrol *kcontrol,
			   काष्ठा snd_ctl_elem_value *ucontrol);
पूर्णांक wm_adsp2_preloader_put(काष्ठा snd_kcontrol *kcontrol,
			   काष्ठा snd_ctl_elem_value *ucontrol);
पूर्णांक wm_adsp_fw_get(काष्ठा snd_kcontrol *kcontrol,
		   काष्ठा snd_ctl_elem_value *ucontrol);
पूर्णांक wm_adsp_fw_put(काष्ठा snd_kcontrol *kcontrol,
		   काष्ठा snd_ctl_elem_value *ucontrol);

पूर्णांक wm_adsp_compr_खोलो(काष्ठा wm_adsp *dsp, काष्ठा snd_compr_stream *stream);
पूर्णांक wm_adsp_compr_मुक्त(काष्ठा snd_soc_component *component,
		       काष्ठा snd_compr_stream *stream);
पूर्णांक wm_adsp_compr_set_params(काष्ठा snd_soc_component *component,
			     काष्ठा snd_compr_stream *stream,
			     काष्ठा snd_compr_params *params);
पूर्णांक wm_adsp_compr_get_caps(काष्ठा snd_soc_component *component,
			   काष्ठा snd_compr_stream *stream,
			   काष्ठा snd_compr_caps *caps);
पूर्णांक wm_adsp_compr_trigger(काष्ठा snd_soc_component *component,
			  काष्ठा snd_compr_stream *stream, पूर्णांक cmd);
पूर्णांक wm_adsp_compr_handle_irq(काष्ठा wm_adsp *dsp);
पूर्णांक wm_adsp_compr_poपूर्णांकer(काष्ठा snd_soc_component *component,
			  काष्ठा snd_compr_stream *stream,
			  काष्ठा snd_compr_tstamp *tstamp);
पूर्णांक wm_adsp_compr_copy(काष्ठा snd_soc_component *component,
		       काष्ठा snd_compr_stream *stream,
		       अक्षर __user *buf, माप_प्रकार count);
पूर्णांक wm_adsp_ग_लिखो_ctl(काष्ठा wm_adsp *dsp, स्थिर अक्षर *name,  पूर्णांक type,
		      अचिन्हित पूर्णांक alg, व्योम *buf, माप_प्रकार len);
पूर्णांक wm_adsp_पढ़ो_ctl(काष्ठा wm_adsp *dsp, स्थिर अक्षर *name,  पूर्णांक type,
		      अचिन्हित पूर्णांक alg, व्योम *buf, माप_प्रकार len);

#पूर्ण_अगर
