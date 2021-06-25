<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause) */
/*
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * Copyright(c) 2019 Intel Corporation. All rights reserved.
 *
 * Author: Ranjani Sridharan <ranjani.sridharan@linux.पूर्णांकel.com>
 */

#अगर_अघोषित __SOUND_SOC_SOF_AUDIO_H
#घोषणा __SOUND_SOC_SOF_AUDIO_H

#समावेश <linux/workqueue.h>

#समावेश <sound/soc.h>
#समावेश <sound/control.h>
#समावेश <sound/sof/stream.h> /* needs to be included beक्रमe control.h */
#समावेश <sound/sof/control.h>
#समावेश <sound/sof/dai.h>
#समावेश <sound/sof/topology.h>
#समावेश "sof-priv.h"

#घोषणा SOF_AUDIO_PCM_DRV_NAME	"sof-audio-component"

/* max number of FE PCMs beक्रमe BEs */
#घोषणा SOF_BE_PCM_BASE		16

#घोषणा DMA_CHAN_INVALID	0xFFFFFFFF

/* PCM stream, mapped to FW component  */
काष्ठा snd_sof_pcm_stream अणु
	u32 comp_id;
	काष्ठा snd_dma_buffer page_table;
	काष्ठा sof_ipc_stream_posn posn;
	काष्ठा snd_pcm_substream *substream;
	काष्ठा work_काष्ठा period_elapsed_work;
	bool d0i3_compatible; /* DSP can be in D0I3 when this pcm is खोलोed */
	/*
	 * flag to indicate that the DSP pipelines should be kept
	 * active or not जबतक suspending the stream
	 */
	bool suspend_ignored;
पूर्ण;

/* ALSA SOF PCM device */
काष्ठा snd_sof_pcm अणु
	काष्ठा snd_soc_component *scomp;
	काष्ठा snd_soc_tplg_pcm pcm;
	काष्ठा snd_sof_pcm_stream stream[2];
	काष्ठा list_head list;	/* list in sdev pcm list */
	काष्ठा snd_pcm_hw_params params[2];
	bool prepared[2]; /* PCM_PARAMS set successfully */
पूर्ण;

काष्ठा snd_sof_led_control अणु
	अचिन्हित पूर्णांक use_led;
	अचिन्हित पूर्णांक direction;
	पूर्णांक led_value;
पूर्ण;

/* ALSA SOF Kcontrol device */
काष्ठा snd_sof_control अणु
	काष्ठा snd_soc_component *scomp;
	पूर्णांक comp_id;
	पूर्णांक min_volume_step; /* min volume step क्रम volume_table */
	पूर्णांक max_volume_step; /* max volume step क्रम volume_table */
	पूर्णांक num_channels;
	u32 पढ़ोback_offset; /* offset to mmapped data अगर used */
	काष्ठा sof_ipc_ctrl_data *control_data;
	u32 size;	/* cdata size */
	क्रमागत sof_ipc_ctrl_cmd cmd;
	u32 *volume_table; /* volume table computed from tlv data*/

	काष्ठा list_head list;	/* list in sdev control list */

	काष्ठा snd_sof_led_control led_ctl;
पूर्ण;

/* ASoC SOF DAPM widget */
काष्ठा snd_sof_widget अणु
	काष्ठा snd_soc_component *scomp;
	पूर्णांक comp_id;
	पूर्णांक pipeline_id;
	पूर्णांक complete;
	पूर्णांक core;
	पूर्णांक id;

	काष्ठा snd_soc_dapm_widget *widget;
	काष्ठा list_head list;	/* list in sdev widget list */

	/* extended data क्रम UUID components */
	काष्ठा sof_ipc_comp_ext comp_ext;

	व्योम *निजी;		/* core करोes not touch this */
पूर्ण;

/* ASoC SOF DAPM route */
काष्ठा snd_sof_route अणु
	काष्ठा snd_soc_component *scomp;

	काष्ठा snd_soc_dapm_route *route;
	काष्ठा list_head list;	/* list in sdev route list */

	व्योम *निजी;
पूर्ण;

/* ASoC DAI device */
काष्ठा snd_sof_dai अणु
	काष्ठा snd_soc_component *scomp;
	स्थिर अक्षर *name;
	स्थिर अक्षर *cpu_dai_name;

	काष्ठा sof_ipc_comp_dai comp_dai;
	पूर्णांक number_configs;
	पूर्णांक current_config;
	काष्ठा sof_ipc_dai_config *dai_config;
	काष्ठा list_head list;	/* list in sdev dai list */
पूर्ण;

/*
 * Kcontrols.
 */

पूर्णांक snd_sof_volume_get(काष्ठा snd_kcontrol *kcontrol,
		       काष्ठा snd_ctl_elem_value *ucontrol);
पूर्णांक snd_sof_volume_put(काष्ठा snd_kcontrol *kcontrol,
		       काष्ठा snd_ctl_elem_value *ucontrol);
पूर्णांक snd_sof_volume_info(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_info *uinfo);
पूर्णांक snd_sof_चयन_get(काष्ठा snd_kcontrol *kcontrol,
		       काष्ठा snd_ctl_elem_value *ucontrol);
पूर्णांक snd_sof_चयन_put(काष्ठा snd_kcontrol *kcontrol,
		       काष्ठा snd_ctl_elem_value *ucontrol);
पूर्णांक snd_sof_क्रमागत_get(काष्ठा snd_kcontrol *kcontrol,
		     काष्ठा snd_ctl_elem_value *ucontrol);
पूर्णांक snd_sof_क्रमागत_put(काष्ठा snd_kcontrol *kcontrol,
		     काष्ठा snd_ctl_elem_value *ucontrol);
पूर्णांक snd_sof_bytes_get(काष्ठा snd_kcontrol *kcontrol,
		      काष्ठा snd_ctl_elem_value *ucontrol);
पूर्णांक snd_sof_bytes_put(काष्ठा snd_kcontrol *kcontrol,
		      काष्ठा snd_ctl_elem_value *ucontrol);
पूर्णांक snd_sof_bytes_ext_put(काष्ठा snd_kcontrol *kcontrol,
			  स्थिर अचिन्हित पूर्णांक __user *binary_data,
			  अचिन्हित पूर्णांक size);
पूर्णांक snd_sof_bytes_ext_get(काष्ठा snd_kcontrol *kcontrol,
			  अचिन्हित पूर्णांक __user *binary_data,
			  अचिन्हित पूर्णांक size);
पूर्णांक snd_sof_bytes_ext_अस्थिर_get(काष्ठा snd_kcontrol *kcontrol, अचिन्हित पूर्णांक __user *binary_data,
				   अचिन्हित पूर्णांक size);

/*
 * Topology.
 * There is no snd_sof_मुक्त_topology since topology components will
 * be मुक्तd by snd_soc_unरेजिस्टर_component,
 */
पूर्णांक snd_sof_load_topology(काष्ठा snd_soc_component *scomp, स्थिर अक्षर *file);
पूर्णांक snd_sof_complete_pipeline(काष्ठा device *dev,
			      काष्ठा snd_sof_widget *swidget);

पूर्णांक sof_load_pipeline_ipc(काष्ठा device *dev,
			  काष्ठा sof_ipc_pipe_new *pipeline,
			  काष्ठा sof_ipc_comp_reply *r);
पूर्णांक sof_pipeline_core_enable(काष्ठा snd_sof_dev *sdev,
			     स्थिर काष्ठा snd_sof_widget *swidget);

/*
 * Stream IPC
 */
पूर्णांक snd_sof_ipc_stream_posn(काष्ठा snd_soc_component *scomp,
			    काष्ठा snd_sof_pcm *spcm, पूर्णांक direction,
			    काष्ठा sof_ipc_stream_posn *posn);

काष्ठा snd_sof_widget *snd_sof_find_swidget(काष्ठा snd_soc_component *scomp,
					    स्थिर अक्षर *name);
काष्ठा snd_sof_widget *
snd_sof_find_swidget_sname(काष्ठा snd_soc_component *scomp,
			   स्थिर अक्षर *pcm_name, पूर्णांक dir);
काष्ठा snd_sof_dai *snd_sof_find_dai(काष्ठा snd_soc_component *scomp,
				     स्थिर अक्षर *name);

अटल अंतरभूत
काष्ठा snd_sof_pcm *snd_sof_find_spcm_dai(काष्ठा snd_soc_component *scomp,
					  काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_sof_dev *sdev = snd_soc_component_get_drvdata(scomp);

	काष्ठा snd_sof_pcm *spcm = शून्य;

	list_क्रम_each_entry(spcm, &sdev->pcm_list, list) अणु
		अगर (le32_to_cpu(spcm->pcm.dai_id) == rtd->dai_link->id)
			वापस spcm;
	पूर्ण

	वापस शून्य;
पूर्ण

काष्ठा snd_sof_pcm *snd_sof_find_spcm_name(काष्ठा snd_soc_component *scomp,
					   स्थिर अक्षर *name);
काष्ठा snd_sof_pcm *snd_sof_find_spcm_comp(काष्ठा snd_soc_component *scomp,
					   अचिन्हित पूर्णांक comp_id,
					   पूर्णांक *direction);
काष्ठा snd_sof_pcm *snd_sof_find_spcm_pcm_id(काष्ठा snd_soc_component *scomp,
					     अचिन्हित पूर्णांक pcm_id);
स्थिर काष्ठा sof_ipc_pipe_new *snd_sof_pipeline_find(काष्ठा snd_sof_dev *sdev,
						     पूर्णांक pipeline_id);
व्योम snd_sof_pcm_period_elapsed(काष्ठा snd_pcm_substream *substream);
व्योम snd_sof_pcm_period_elapsed_work(काष्ठा work_काष्ठा *work);

/*
 * Mixer IPC
 */
पूर्णांक snd_sof_ipc_set_get_comp_data(काष्ठा snd_sof_control *scontrol,
				  u32 ipc_cmd,
				  क्रमागत sof_ipc_ctrl_type ctrl_type,
				  क्रमागत sof_ipc_ctrl_cmd ctrl_cmd,
				  bool send);

/* DAI link fixup */
पूर्णांक sof_pcm_dai_link_fixup(काष्ठा snd_soc_pcm_runसमय *rtd, काष्ठा snd_pcm_hw_params *params);

/* PM */
पूर्णांक sof_restore_pipelines(काष्ठा device *dev);
पूर्णांक sof_set_hw_params_upon_resume(काष्ठा device *dev);
bool snd_sof_stream_suspend_ignored(काष्ठा snd_sof_dev *sdev);
bool snd_sof_dsp_only_d0i3_compatible_stream_active(काष्ठा snd_sof_dev *sdev);

/* Machine driver क्रमागतeration */
पूर्णांक sof_machine_रेजिस्टर(काष्ठा snd_sof_dev *sdev, व्योम *pdata);
व्योम sof_machine_unरेजिस्टर(काष्ठा snd_sof_dev *sdev, व्योम *pdata);

#पूर्ण_अगर
