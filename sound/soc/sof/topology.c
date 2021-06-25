<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause)
//
// This file is provided under a dual BSD/GPLv2 license.  When using or
// redistributing this file, you may करो so under either license.
//
// Copyright(c) 2018 Intel Corporation. All rights reserved.
//
// Author: Liam Girdwood <liam.r.girdwood@linux.पूर्णांकel.com>
//

#समावेश <linux/bits.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/firmware.h>
#समावेश <linux/workqueue.h>
#समावेश <sound/tlv.h>
#समावेश <sound/pcm_params.h>
#समावेश <uapi/sound/sof/tokens.h>
#समावेश "sof-priv.h"
#समावेश "sof-audio.h"
#समावेश "ops.h"

#घोषणा COMP_ID_UNASSIGNED		0xffffffff
/*
 * Constants used in the computation of linear volume gain
 * from dB gain 20th root of 10 in Q1.16 fixed-poपूर्णांक notation
 */
#घोषणा VOL_TWENTIETH_ROOT_OF_TEN	73533
/* 40th root of 10 in Q1.16 fixed-poपूर्णांक notation*/
#घोषणा VOL_FORTIETH_ROOT_OF_TEN	69419
/*
 * Volume fractional word length define to 16 sets
 * the volume linear gain value to use Qx.16 क्रमmat
 */
#घोषणा VOLUME_FWL	16
/* 0.5 dB step value in topology TLV */
#घोषणा VOL_HALF_DB_STEP	50
/* Full volume क्रम शेष values */
#घोषणा VOL_ZERO_DB	BIT(VOLUME_FWL)

/* TLV data items */
#घोषणा TLV_ITEMS	3
#घोषणा TLV_MIN		0
#घोषणा TLV_STEP	1
#घोषणा TLV_MUTE	2

/* size of tplg abi in byte */
#घोषणा SOF_TPLG_ABI_SIZE 3

काष्ठा sof_widget_data अणु
	पूर्णांक ctrl_type;
	पूर्णांक ipc_cmd;
	काष्ठा sof_abi_hdr *pdata;
	काष्ठा snd_sof_control *control;
पूर्ण;

/* send pcm params ipc */
अटल पूर्णांक ipc_pcm_params(काष्ठा snd_sof_widget *swidget, पूर्णांक dir)
अणु
	काष्ठा sof_ipc_pcm_params_reply ipc_params_reply;
	काष्ठा snd_soc_component *scomp = swidget->scomp;
	काष्ठा snd_sof_dev *sdev = snd_soc_component_get_drvdata(scomp);
	काष्ठा sof_ipc_pcm_params pcm;
	काष्ठा snd_pcm_hw_params *params;
	काष्ठा snd_sof_pcm *spcm;
	पूर्णांक ret;

	स_रखो(&pcm, 0, माप(pcm));

	/* get runसमय PCM params using widget's stream name */
	spcm = snd_sof_find_spcm_name(scomp, swidget->widget->sname);
	अगर (!spcm) अणु
		dev_err(scomp->dev, "error: cannot find PCM for %s\n",
			swidget->widget->name);
		वापस -EINVAL;
	पूर्ण

	params = &spcm->params[dir];

	/* set IPC PCM params */
	pcm.hdr.size = माप(pcm);
	pcm.hdr.cmd = SOF_IPC_GLB_STREAM_MSG | SOF_IPC_STREAM_PCM_PARAMS;
	pcm.comp_id = swidget->comp_id;
	pcm.params.hdr.size = माप(pcm.params);
	pcm.params.direction = dir;
	pcm.params.sample_valid_bytes = params_width(params) >> 3;
	pcm.params.buffer_fmt = SOF_IPC_BUFFER_INTERLEAVED;
	pcm.params.rate = params_rate(params);
	pcm.params.channels = params_channels(params);
	pcm.params.host_period_bytes = params_period_bytes(params);

	/* set क्रमmat */
	चयन (params_क्रमmat(params)) अणु
	हाल SNDRV_PCM_FORMAT_S16:
		pcm.params.frame_fmt = SOF_IPC_FRAME_S16_LE;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S24:
		pcm.params.frame_fmt = SOF_IPC_FRAME_S24_4LE;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S32:
		pcm.params.frame_fmt = SOF_IPC_FRAME_S32_LE;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* send IPC to the DSP */
	ret = sof_ipc_tx_message(sdev->ipc, pcm.hdr.cmd, &pcm, माप(pcm),
				 &ipc_params_reply, माप(ipc_params_reply));
	अगर (ret < 0)
		dev_err(scomp->dev, "error: pcm params failed for %s\n",
			swidget->widget->name);

	वापस ret;
पूर्ण

 /* send stream trigger ipc */
अटल पूर्णांक ipc_trigger(काष्ठा snd_sof_widget *swidget, पूर्णांक cmd)
अणु
	काष्ठा snd_soc_component *scomp = swidget->scomp;
	काष्ठा snd_sof_dev *sdev = snd_soc_component_get_drvdata(scomp);
	काष्ठा sof_ipc_stream stream;
	काष्ठा sof_ipc_reply reply;
	पूर्णांक ret;

	/* set IPC stream params */
	stream.hdr.size = माप(stream);
	stream.hdr.cmd = SOF_IPC_GLB_STREAM_MSG | cmd;
	stream.comp_id = swidget->comp_id;

	/* send IPC to the DSP */
	ret = sof_ipc_tx_message(sdev->ipc, stream.hdr.cmd, &stream,
				 माप(stream), &reply, माप(reply));
	अगर (ret < 0)
		dev_err(scomp->dev, "error: failed to trigger %s\n",
			swidget->widget->name);

	वापस ret;
पूर्ण

अटल पूर्णांक sof_keyword_dapm_event(काष्ठा snd_soc_dapm_widget *w,
				  काष्ठा snd_kcontrol *k, पूर्णांक event)
अणु
	काष्ठा snd_sof_widget *swidget = w->करोbj.निजी;
	काष्ठा snd_soc_component *scomp;
	पूर्णांक stream = SNDRV_PCM_STREAM_CAPTURE;
	काष्ठा snd_sof_pcm *spcm;
	पूर्णांक ret = 0;

	अगर (!swidget)
		वापस 0;

	scomp = swidget->scomp;

	dev_dbg(scomp->dev, "received event %d for widget %s\n",
		event, w->name);

	/* get runसमय PCM params using widget's stream name */
	spcm = snd_sof_find_spcm_name(scomp, swidget->widget->sname);
	अगर (!spcm) अणु
		dev_err(scomp->dev, "error: cannot find PCM for %s\n",
			swidget->widget->name);
		वापस -EINVAL;
	पूर्ण

	/* process events */
	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		अगर (spcm->stream[stream].suspend_ignored) अणु
			dev_dbg(scomp->dev, "PRE_PMU event ignored, KWD pipeline is already RUNNING\n");
			वापस 0;
		पूर्ण

		/* set pcm params */
		ret = ipc_pcm_params(swidget, stream);
		अगर (ret < 0) अणु
			dev_err(scomp->dev,
				"error: failed to set pcm params for widget %s\n",
				swidget->widget->name);
			अवरोध;
		पूर्ण

		/* start trigger */
		ret = ipc_trigger(swidget, SOF_IPC_STREAM_TRIG_START);
		अगर (ret < 0)
			dev_err(scomp->dev,
				"error: failed to trigger widget %s\n",
				swidget->widget->name);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		अगर (spcm->stream[stream].suspend_ignored) अणु
			dev_dbg(scomp->dev, "POST_PMD even ignored, KWD pipeline will remain RUNNING\n");
			वापस 0;
		पूर्ण

		/* stop trigger */
		ret = ipc_trigger(swidget, SOF_IPC_STREAM_TRIG_STOP);
		अगर (ret < 0)
			dev_err(scomp->dev,
				"error: failed to trigger widget %s\n",
				swidget->widget->name);

		/* pcm मुक्त */
		ret = ipc_trigger(swidget, SOF_IPC_STREAM_PCM_FREE);
		अगर (ret < 0)
			dev_err(scomp->dev,
				"error: failed to trigger widget %s\n",
				swidget->widget->name);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/* event handlers क्रम keyword detect component */
अटल स्थिर काष्ठा snd_soc_tplg_widget_events sof_kwd_events[] = अणु
	अणुSOF_KEYWORD_DETECT_DAPM_EVENT, sof_keyword_dapm_eventपूर्ण,
पूर्ण;

अटल अंतरभूत पूर्णांक get_tlv_data(स्थिर पूर्णांक *p, पूर्णांक tlv[TLV_ITEMS])
अणु
	/* we only support dB scale TLV type at the moment */
	अगर ((पूर्णांक)p[SNDRV_CTL_TLVO_TYPE] != SNDRV_CTL_TLVT_DB_SCALE)
		वापस -EINVAL;

	/* min value in topology tlv data is multiplied by 100 */
	tlv[TLV_MIN] = (पूर्णांक)p[SNDRV_CTL_TLVO_DB_SCALE_MIN] / 100;

	/* volume steps */
	tlv[TLV_STEP] = (पूर्णांक)(p[SNDRV_CTL_TLVO_DB_SCALE_MUTE_AND_STEP] &
				TLV_DB_SCALE_MASK);

	/* mute ON/OFF */
	अगर ((p[SNDRV_CTL_TLVO_DB_SCALE_MUTE_AND_STEP] &
		TLV_DB_SCALE_MUTE) == 0)
		tlv[TLV_MUTE] = 0;
	अन्यथा
		tlv[TLV_MUTE] = 1;

	वापस 0;
पूर्ण

/*
 * Function to truncate an अचिन्हित 64-bit number
 * by x bits and वापस 32-bit अचिन्हित number. This
 * function also takes care of rounding जबतक truncating
 */
अटल अंतरभूत u32 vol_shअगरt_64(u64 i, u32 x)
अणु
	/* करो not truncate more than 32 bits */
	अगर (x > 32)
		x = 32;

	अगर (x == 0)
		वापस (u32)i;

	वापस (u32)(((i >> (x - 1)) + 1) >> 1);
पूर्ण

/*
 * Function to compute a ^ exp where,
 * a is a fractional number represented by a fixed-poपूर्णांक
 * पूर्णांकeger with a fractional world length of "fwl"
 * exp is an पूर्णांकeger
 * fwl is the fractional word length
 * Return value is a fractional number represented by a
 * fixed-poपूर्णांक पूर्णांकeger with a fractional word length of "fwl"
 */
अटल u32 vol_घात32(u32 a, पूर्णांक exp, u32 fwl)
अणु
	पूर्णांक i, iter;
	u32 घातer = 1 << fwl;
	u64 numerator;

	/* अगर exponent is 0, वापस 1 */
	अगर (exp == 0)
		वापस घातer;

	/* determine the number of iterations based on the exponent */
	अगर (exp < 0)
		iter = exp * -1;
	अन्यथा
		iter = exp;

	/* mutiply a "iter" बार to compute घातer */
	क्रम (i = 0; i < iter; i++) अणु
		/*
		 * Product of 2 Qx.fwl fixed-poपूर्णांक numbers yields a Q2*x.2*fwl
		 * Truncate product back to fwl fractional bits with rounding
		 */
		घातer = vol_shअगरt_64((u64)घातer * a, fwl);
	पूर्ण

	अगर (exp > 0) अणु
		/* अगर exp is positive, वापस the result */
		वापस घातer;
	पूर्ण

	/* अगर exp is negative, वापस the multiplicative inverse */
	numerator = (u64)1 << (fwl << 1);
	करो_भाग(numerator, घातer);

	वापस (u32)numerator;
पूर्ण

/*
 * Function to calculate volume gain from TLV data.
 * This function can only handle gain steps that are multiples of 0.5 dB
 */
अटल u32 vol_compute_gain(u32 value, पूर्णांक *tlv)
अणु
	पूर्णांक dB_gain;
	u32 linear_gain;
	पूर्णांक f_step;

	/* mute volume */
	अगर (value == 0 && tlv[TLV_MUTE])
		वापस 0;

	/*
	 * compute dB gain from tlv. tlv_step
	 * in topology is multiplied by 100
	 */
	dB_gain = tlv[TLV_MIN] + (value * tlv[TLV_STEP]) / 100;

	/*
	 * compute linear gain represented by fixed-poपूर्णांक
	 * पूर्णांक with VOLUME_FWL fractional bits
	 */
	linear_gain = vol_घात32(VOL_TWENTIETH_ROOT_OF_TEN, dB_gain, VOLUME_FWL);

	/* extract the fractional part of volume step */
	f_step = tlv[TLV_STEP] - (tlv[TLV_STEP] / 100);

	/* अगर volume step is an odd multiple of 0.5 dB */
	अगर (f_step == VOL_HALF_DB_STEP && (value & 1))
		linear_gain = vol_shअगरt_64((u64)linear_gain *
						  VOL_FORTIETH_ROOT_OF_TEN,
						  VOLUME_FWL);

	वापस linear_gain;
पूर्ण

/*
 * Set up volume table क्रम kcontrols from tlv data
 * "size" specअगरies the number of entries in the table
 */
अटल पूर्णांक set_up_volume_table(काष्ठा snd_sof_control *scontrol,
			       पूर्णांक tlv[TLV_ITEMS], पूर्णांक size)
अणु
	पूर्णांक j;

	/* init the volume table */
	scontrol->volume_table = kसुस्मृति(size, माप(u32), GFP_KERNEL);
	अगर (!scontrol->volume_table)
		वापस -ENOMEM;

	/* populate the volume table */
	क्रम (j = 0; j < size ; j++)
		scontrol->volume_table[j] = vol_compute_gain(j, tlv);

	वापस 0;
पूर्ण

काष्ठा sof_dai_types अणु
	स्थिर अक्षर *name;
	क्रमागत sof_ipc_dai_type type;
पूर्ण;

अटल स्थिर काष्ठा sof_dai_types sof_dais[] = अणु
	अणु"SSP", SOF_DAI_INTEL_SSPपूर्ण,
	अणु"HDA", SOF_DAI_INTEL_HDAपूर्ण,
	अणु"DMIC", SOF_DAI_INTEL_DMICपूर्ण,
	अणु"ALH", SOF_DAI_INTEL_ALHपूर्ण,
	अणु"SAI", SOF_DAI_IMX_SAIपूर्ण,
	अणु"ESAI", SOF_DAI_IMX_ESAIपूर्ण,
पूर्ण;

अटल क्रमागत sof_ipc_dai_type find_dai(स्थिर अक्षर *name)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(sof_dais); i++) अणु
		अगर (म_भेद(name, sof_dais[i].name) == 0)
			वापस sof_dais[i].type;
	पूर्ण

	वापस SOF_DAI_INTEL_NONE;
पूर्ण

/*
 * Supported Frame क्रमmat types and lookup, add new ones to end of list.
 */

काष्ठा sof_frame_types अणु
	स्थिर अक्षर *name;
	क्रमागत sof_ipc_frame frame;
पूर्ण;

अटल स्थिर काष्ठा sof_frame_types sof_frames[] = अणु
	अणु"s16le", SOF_IPC_FRAME_S16_LEपूर्ण,
	अणु"s24le", SOF_IPC_FRAME_S24_4LEपूर्ण,
	अणु"s32le", SOF_IPC_FRAME_S32_LEपूर्ण,
	अणु"float", SOF_IPC_FRAME_FLOATपूर्ण,
पूर्ण;

अटल क्रमागत sof_ipc_frame find_क्रमmat(स्थिर अक्षर *name)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(sof_frames); i++) अणु
		अगर (म_भेद(name, sof_frames[i].name) == 0)
			वापस sof_frames[i].frame;
	पूर्ण

	/* use s32le अगर nothing is specअगरied */
	वापस SOF_IPC_FRAME_S32_LE;
पूर्ण

काष्ठा sof_process_types अणु
	स्थिर अक्षर *name;
	क्रमागत sof_ipc_process_type type;
	क्रमागत sof_comp_type comp_type;
पूर्ण;

अटल स्थिर काष्ठा sof_process_types sof_process[] = अणु
	अणु"EQFIR", SOF_PROCESS_EQFIR, SOF_COMP_EQ_FIRपूर्ण,
	अणु"EQIIR", SOF_PROCESS_EQIIR, SOF_COMP_EQ_IIRपूर्ण,
	अणु"KEYWORD_DETECT", SOF_PROCESS_KEYWORD_DETECT, SOF_COMP_KEYWORD_DETECTपूर्ण,
	अणु"KPB", SOF_PROCESS_KPB, SOF_COMP_KPBपूर्ण,
	अणु"CHAN_SELECTOR", SOF_PROCESS_CHAN_SELECTOR, SOF_COMP_SELECTORपूर्ण,
	अणु"MUX", SOF_PROCESS_MUX, SOF_COMP_MUXपूर्ण,
	अणु"DEMUX", SOF_PROCESS_DEMUX, SOF_COMP_DEMUXपूर्ण,
	अणु"DCBLOCK", SOF_PROCESS_DCBLOCK, SOF_COMP_DCBLOCKपूर्ण,
	अणु"SMART_AMP", SOF_PROCESS_SMART_AMP, SOF_COMP_SMART_AMPपूर्ण,
पूर्ण;

अटल क्रमागत sof_ipc_process_type find_process(स्थिर अक्षर *name)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(sof_process); i++) अणु
		अगर (म_भेद(name, sof_process[i].name) == 0)
			वापस sof_process[i].type;
	पूर्ण

	वापस SOF_PROCESS_NONE;
पूर्ण

अटल क्रमागत sof_comp_type find_process_comp_type(क्रमागत sof_ipc_process_type type)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(sof_process); i++) अणु
		अगर (sof_process[i].type == type)
			वापस sof_process[i].comp_type;
	पूर्ण

	वापस SOF_COMP_NONE;
पूर्ण

/*
 * Topology Token Parsing.
 * New tokens should be added to headers and parsing tables below.
 */

काष्ठा sof_topology_token अणु
	u32 token;
	u32 type;
	पूर्णांक (*get_token)(व्योम *elem, व्योम *object, u32 offset, u32 size);
	u32 offset;
	u32 size;
पूर्ण;

अटल पूर्णांक get_token_u32(व्योम *elem, व्योम *object, u32 offset, u32 size)
अणु
	काष्ठा snd_soc_tplg_venकरोr_value_elem *velem = elem;
	u32 *val = (u32 *)((u8 *)object + offset);

	*val = le32_to_cpu(velem->value);
	वापस 0;
पूर्ण

अटल पूर्णांक get_token_u16(व्योम *elem, व्योम *object, u32 offset, u32 size)
अणु
	काष्ठा snd_soc_tplg_venकरोr_value_elem *velem = elem;
	u16 *val = (u16 *)((u8 *)object + offset);

	*val = (u16)le32_to_cpu(velem->value);
	वापस 0;
पूर्ण

अटल पूर्णांक get_token_uuid(व्योम *elem, व्योम *object, u32 offset, u32 size)
अणु
	काष्ठा snd_soc_tplg_venकरोr_uuid_elem *velem = elem;
	u8 *dst = (u8 *)object + offset;

	स_नकल(dst, velem->uuid, UUID_SIZE);

	वापस 0;
पूर्ण

अटल पूर्णांक get_token_comp_क्रमmat(व्योम *elem, व्योम *object, u32 offset, u32 size)
अणु
	काष्ठा snd_soc_tplg_venकरोr_string_elem *velem = elem;
	u32 *val = (u32 *)((u8 *)object + offset);

	*val = find_क्रमmat(velem->string);
	वापस 0;
पूर्ण

अटल पूर्णांक get_token_dai_type(व्योम *elem, व्योम *object, u32 offset, u32 size)
अणु
	काष्ठा snd_soc_tplg_venकरोr_string_elem *velem = elem;
	u32 *val = (u32 *)((u8 *)object + offset);

	*val = find_dai(velem->string);
	वापस 0;
पूर्ण

अटल पूर्णांक get_token_process_type(व्योम *elem, व्योम *object, u32 offset,
				  u32 size)
अणु
	काष्ठा snd_soc_tplg_venकरोr_string_elem *velem = elem;
	u32 *val = (u32 *)((u8 *)object + offset);

	*val = find_process(velem->string);
	वापस 0;
पूर्ण

/* Buffers */
अटल स्थिर काष्ठा sof_topology_token buffer_tokens[] = अणु
	अणुSOF_TKN_BUF_SIZE, SND_SOC_TPLG_TUPLE_TYPE_WORD, get_token_u32,
		दुरत्व(काष्ठा sof_ipc_buffer, size), 0पूर्ण,
	अणुSOF_TKN_BUF_CAPS, SND_SOC_TPLG_TUPLE_TYPE_WORD, get_token_u32,
		दुरत्व(काष्ठा sof_ipc_buffer, caps), 0पूर्ण,
पूर्ण;

/* DAI */
अटल स्थिर काष्ठा sof_topology_token dai_tokens[] = अणु
	अणुSOF_TKN_DAI_TYPE, SND_SOC_TPLG_TUPLE_TYPE_STRING, get_token_dai_type,
		दुरत्व(काष्ठा sof_ipc_comp_dai, type), 0पूर्ण,
	अणुSOF_TKN_DAI_INDEX, SND_SOC_TPLG_TUPLE_TYPE_WORD, get_token_u32,
		दुरत्व(काष्ठा sof_ipc_comp_dai, dai_index), 0पूर्ण,
	अणुSOF_TKN_DAI_सूचीECTION, SND_SOC_TPLG_TUPLE_TYPE_WORD, get_token_u32,
		दुरत्व(काष्ठा sof_ipc_comp_dai, direction), 0पूर्ण,
पूर्ण;

/* BE DAI link */
अटल स्थिर काष्ठा sof_topology_token dai_link_tokens[] = अणु
	अणुSOF_TKN_DAI_TYPE, SND_SOC_TPLG_TUPLE_TYPE_STRING, get_token_dai_type,
		दुरत्व(काष्ठा sof_ipc_dai_config, type), 0पूर्ण,
	अणुSOF_TKN_DAI_INDEX, SND_SOC_TPLG_TUPLE_TYPE_WORD, get_token_u32,
		दुरत्व(काष्ठा sof_ipc_dai_config, dai_index), 0पूर्ण,
पूर्ण;

/* scheduling */
अटल स्थिर काष्ठा sof_topology_token sched_tokens[] = अणु
	अणुSOF_TKN_SCHED_PERIOD, SND_SOC_TPLG_TUPLE_TYPE_WORD, get_token_u32,
		दुरत्व(काष्ठा sof_ipc_pipe_new, period), 0पूर्ण,
	अणुSOF_TKN_SCHED_PRIORITY, SND_SOC_TPLG_TUPLE_TYPE_WORD, get_token_u32,
		दुरत्व(काष्ठा sof_ipc_pipe_new, priority), 0पूर्ण,
	अणुSOF_TKN_SCHED_MIPS, SND_SOC_TPLG_TUPLE_TYPE_WORD, get_token_u32,
		दुरत्व(काष्ठा sof_ipc_pipe_new, period_mips), 0पूर्ण,
	अणुSOF_TKN_SCHED_CORE, SND_SOC_TPLG_TUPLE_TYPE_WORD, get_token_u32,
		दुरत्व(काष्ठा sof_ipc_pipe_new, core), 0पूर्ण,
	अणुSOF_TKN_SCHED_FRAMES, SND_SOC_TPLG_TUPLE_TYPE_WORD, get_token_u32,
		दुरत्व(काष्ठा sof_ipc_pipe_new, frames_per_sched), 0पूर्ण,
	अणुSOF_TKN_SCHED_TIME_DOMAIN, SND_SOC_TPLG_TUPLE_TYPE_WORD, get_token_u32,
		दुरत्व(काष्ठा sof_ipc_pipe_new, समय_करोमुख्य), 0पूर्ण,
पूर्ण;

/* volume */
अटल स्थिर काष्ठा sof_topology_token volume_tokens[] = अणु
	अणुSOF_TKN_VOLUME_RAMP_STEP_TYPE, SND_SOC_TPLG_TUPLE_TYPE_WORD,
		get_token_u32, दुरत्व(काष्ठा sof_ipc_comp_volume, ramp), 0पूर्ण,
	अणुSOF_TKN_VOLUME_RAMP_STEP_MS,
		SND_SOC_TPLG_TUPLE_TYPE_WORD, get_token_u32,
		दुरत्व(काष्ठा sof_ipc_comp_volume, initial_ramp), 0पूर्ण,
पूर्ण;

/* SRC */
अटल स्थिर काष्ठा sof_topology_token src_tokens[] = अणु
	अणुSOF_TKN_SRC_RATE_IN, SND_SOC_TPLG_TUPLE_TYPE_WORD, get_token_u32,
		दुरत्व(काष्ठा sof_ipc_comp_src, source_rate), 0पूर्ण,
	अणुSOF_TKN_SRC_RATE_OUT, SND_SOC_TPLG_TUPLE_TYPE_WORD, get_token_u32,
		दुरत्व(काष्ठा sof_ipc_comp_src, sink_rate), 0पूर्ण,
पूर्ण;

/* ASRC */
अटल स्थिर काष्ठा sof_topology_token asrc_tokens[] = अणु
	अणुSOF_TKN_ASRC_RATE_IN, SND_SOC_TPLG_TUPLE_TYPE_WORD, get_token_u32,
		दुरत्व(काष्ठा sof_ipc_comp_asrc, source_rate), 0पूर्ण,
	अणुSOF_TKN_ASRC_RATE_OUT, SND_SOC_TPLG_TUPLE_TYPE_WORD, get_token_u32,
		दुरत्व(काष्ठा sof_ipc_comp_asrc, sink_rate), 0पूर्ण,
	अणुSOF_TKN_ASRC_ASYNCHRONOUS_MODE, SND_SOC_TPLG_TUPLE_TYPE_WORD,
		get_token_u32,
		दुरत्व(काष्ठा sof_ipc_comp_asrc, asynchronous_mode), 0पूर्ण,
	अणुSOF_TKN_ASRC_OPERATION_MODE, SND_SOC_TPLG_TUPLE_TYPE_WORD,
		get_token_u32,
		दुरत्व(काष्ठा sof_ipc_comp_asrc, operation_mode), 0पूर्ण,
पूर्ण;

/* Tone */
अटल स्थिर काष्ठा sof_topology_token tone_tokens[] = अणु
पूर्ण;

/* EFFECT */
अटल स्थिर काष्ठा sof_topology_token process_tokens[] = अणु
	अणुSOF_TKN_PROCESS_TYPE, SND_SOC_TPLG_TUPLE_TYPE_STRING,
		get_token_process_type,
		दुरत्व(काष्ठा sof_ipc_comp_process, type), 0पूर्ण,
पूर्ण;

/* PCM */
अटल स्थिर काष्ठा sof_topology_token pcm_tokens[] = अणु
	अणुSOF_TKN_PCM_DMAC_CONFIG, SND_SOC_TPLG_TUPLE_TYPE_WORD, get_token_u32,
		दुरत्व(काष्ठा sof_ipc_comp_host, dmac_config), 0पूर्ण,
पूर्ण;

/* PCM */
अटल स्थिर काष्ठा sof_topology_token stream_tokens[] = अणु
	अणुSOF_TKN_STREAM_PLAYBACK_COMPATIBLE_D0I3,
		SND_SOC_TPLG_TUPLE_TYPE_BOOL, get_token_u16,
		दुरत्व(काष्ठा snd_sof_pcm, stream[0].d0i3_compatible), 0पूर्ण,
	अणुSOF_TKN_STREAM_CAPTURE_COMPATIBLE_D0I3,
		SND_SOC_TPLG_TUPLE_TYPE_BOOL, get_token_u16,
		दुरत्व(काष्ठा snd_sof_pcm, stream[1].d0i3_compatible), 0पूर्ण,
पूर्ण;

/* Generic components */
अटल स्थिर काष्ठा sof_topology_token comp_tokens[] = अणु
	अणुSOF_TKN_COMP_PERIOD_SINK_COUNT,
		SND_SOC_TPLG_TUPLE_TYPE_WORD, get_token_u32,
		दुरत्व(काष्ठा sof_ipc_comp_config, periods_sink), 0पूर्ण,
	अणुSOF_TKN_COMP_PERIOD_SOURCE_COUNT,
		SND_SOC_TPLG_TUPLE_TYPE_WORD, get_token_u32,
		दुरत्व(काष्ठा sof_ipc_comp_config, periods_source), 0पूर्ण,
	अणुSOF_TKN_COMP_FORMAT,
		SND_SOC_TPLG_TUPLE_TYPE_STRING, get_token_comp_क्रमmat,
		दुरत्व(काष्ठा sof_ipc_comp_config, frame_fmt), 0पूर्ण,
पूर्ण;

/* SSP */
अटल स्थिर काष्ठा sof_topology_token ssp_tokens[] = अणु
	अणुSOF_TKN_INTEL_SSP_CLKS_CONTROL,
		SND_SOC_TPLG_TUPLE_TYPE_WORD, get_token_u32,
		दुरत्व(काष्ठा sof_ipc_dai_ssp_params, clks_control), 0पूर्ण,
	अणुSOF_TKN_INTEL_SSP_MCLK_ID,
		SND_SOC_TPLG_TUPLE_TYPE_SHORT, get_token_u16,
		दुरत्व(काष्ठा sof_ipc_dai_ssp_params, mclk_id), 0पूर्ण,
	अणुSOF_TKN_INTEL_SSP_SAMPLE_BITS, SND_SOC_TPLG_TUPLE_TYPE_WORD,
		get_token_u32,
		दुरत्व(काष्ठा sof_ipc_dai_ssp_params, sample_valid_bits), 0पूर्ण,
	अणुSOF_TKN_INTEL_SSP_FRAME_PULSE_WIDTH, SND_SOC_TPLG_TUPLE_TYPE_SHORT,
		get_token_u16,
		दुरत्व(काष्ठा sof_ipc_dai_ssp_params, frame_pulse_width), 0पूर्ण,
	अणुSOF_TKN_INTEL_SSP_QUIRKS, SND_SOC_TPLG_TUPLE_TYPE_WORD,
		get_token_u32,
		दुरत्व(काष्ठा sof_ipc_dai_ssp_params, quirks), 0पूर्ण,
	अणुSOF_TKN_INTEL_SSP_TDM_PADDING_PER_SLOT, SND_SOC_TPLG_TUPLE_TYPE_BOOL,
		get_token_u16,
		दुरत्व(काष्ठा sof_ipc_dai_ssp_params,
			 tdm_per_slot_padding_flag), 0पूर्ण,
	अणुSOF_TKN_INTEL_SSP_BCLK_DELAY, SND_SOC_TPLG_TUPLE_TYPE_WORD,
		get_token_u32,
		दुरत्व(काष्ठा sof_ipc_dai_ssp_params, bclk_delay), 0पूर्ण,

पूर्ण;

/* ALH */
अटल स्थिर काष्ठा sof_topology_token alh_tokens[] = अणु
	अणुSOF_TKN_INTEL_ALH_RATE,
		SND_SOC_TPLG_TUPLE_TYPE_WORD, get_token_u32,
		दुरत्व(काष्ठा sof_ipc_dai_alh_params, rate), 0पूर्ण,
	अणुSOF_TKN_INTEL_ALH_CH,
		SND_SOC_TPLG_TUPLE_TYPE_WORD, get_token_u32,
		दुरत्व(काष्ठा sof_ipc_dai_alh_params, channels), 0पूर्ण,
पूर्ण;

/* DMIC */
अटल स्थिर काष्ठा sof_topology_token dmic_tokens[] = अणु
	अणुSOF_TKN_INTEL_DMIC_DRIVER_VERSION,
		SND_SOC_TPLG_TUPLE_TYPE_WORD, get_token_u32,
		दुरत्व(काष्ठा sof_ipc_dai_dmic_params, driver_ipc_version),
		0पूर्ण,
	अणुSOF_TKN_INTEL_DMIC_CLK_MIN,
		SND_SOC_TPLG_TUPLE_TYPE_WORD, get_token_u32,
		दुरत्व(काष्ठा sof_ipc_dai_dmic_params, pdmclk_min), 0पूर्ण,
	अणुSOF_TKN_INTEL_DMIC_CLK_MAX,
		SND_SOC_TPLG_TUPLE_TYPE_WORD, get_token_u32,
		दुरत्व(काष्ठा sof_ipc_dai_dmic_params, pdmclk_max), 0पूर्ण,
	अणुSOF_TKN_INTEL_DMIC_SAMPLE_RATE,
		SND_SOC_TPLG_TUPLE_TYPE_WORD, get_token_u32,
		दुरत्व(काष्ठा sof_ipc_dai_dmic_params, fअगरo_fs), 0पूर्ण,
	अणुSOF_TKN_INTEL_DMIC_DUTY_MIN,
		SND_SOC_TPLG_TUPLE_TYPE_SHORT, get_token_u16,
		दुरत्व(काष्ठा sof_ipc_dai_dmic_params, duty_min), 0पूर्ण,
	अणुSOF_TKN_INTEL_DMIC_DUTY_MAX,
		SND_SOC_TPLG_TUPLE_TYPE_SHORT, get_token_u16,
		दुरत्व(काष्ठा sof_ipc_dai_dmic_params, duty_max), 0पूर्ण,
	अणुSOF_TKN_INTEL_DMIC_NUM_PDM_ACTIVE,
		SND_SOC_TPLG_TUPLE_TYPE_WORD, get_token_u32,
		दुरत्व(काष्ठा sof_ipc_dai_dmic_params,
			 num_pdm_active), 0पूर्ण,
	अणुSOF_TKN_INTEL_DMIC_FIFO_WORD_LENGTH,
		SND_SOC_TPLG_TUPLE_TYPE_SHORT, get_token_u16,
		दुरत्व(काष्ठा sof_ipc_dai_dmic_params, fअगरo_bits), 0पूर्ण,
	अणुSOF_TKN_INTEL_DMIC_UNMUTE_RAMP_TIME_MS,
		SND_SOC_TPLG_TUPLE_TYPE_WORD, get_token_u32,
		दुरत्व(काष्ठा sof_ipc_dai_dmic_params, unmute_ramp_समय), 0पूर्ण,

पूर्ण;

/* ESAI */
अटल स्थिर काष्ठा sof_topology_token esai_tokens[] = अणु
	अणुSOF_TKN_IMX_ESAI_MCLK_ID,
		SND_SOC_TPLG_TUPLE_TYPE_SHORT, get_token_u16,
		दुरत्व(काष्ठा sof_ipc_dai_esai_params, mclk_id), 0पूर्ण,
पूर्ण;

/* SAI */
अटल स्थिर काष्ठा sof_topology_token sai_tokens[] = अणु
	अणुSOF_TKN_IMX_SAI_MCLK_ID,
		SND_SOC_TPLG_TUPLE_TYPE_SHORT, get_token_u16,
		दुरत्व(काष्ठा sof_ipc_dai_sai_params, mclk_id), 0पूर्ण,
पूर्ण;

/* Core tokens */
अटल स्थिर काष्ठा sof_topology_token core_tokens[] = अणु
	अणुSOF_TKN_COMP_CORE_ID,
		SND_SOC_TPLG_TUPLE_TYPE_WORD, get_token_u32,
		दुरत्व(काष्ठा sof_ipc_comp, core), 0पूर्ण,
पूर्ण;

/* Component extended tokens */
अटल स्थिर काष्ठा sof_topology_token comp_ext_tokens[] = अणु
	अणुSOF_TKN_COMP_UUID,
		SND_SOC_TPLG_TUPLE_TYPE_UUID, get_token_uuid,
		दुरत्व(काष्ठा sof_ipc_comp_ext, uuid), 0पूर्ण,
पूर्ण;

/*
 * DMIC PDM Tokens
 * SOF_TKN_INTEL_DMIC_PDM_CTRL_ID should be the first token
 * as it increments the index जबतक parsing the array of pdm tokens
 * and determines the correct offset
 */
अटल स्थिर काष्ठा sof_topology_token dmic_pdm_tokens[] = अणु
	अणुSOF_TKN_INTEL_DMIC_PDM_CTRL_ID,
		SND_SOC_TPLG_TUPLE_TYPE_SHORT, get_token_u16,
		दुरत्व(काष्ठा sof_ipc_dai_dmic_pdm_ctrl, id),
		0पूर्ण,
	अणुSOF_TKN_INTEL_DMIC_PDM_MIC_A_Enable,
		SND_SOC_TPLG_TUPLE_TYPE_SHORT, get_token_u16,
		दुरत्व(काष्ठा sof_ipc_dai_dmic_pdm_ctrl, enable_mic_a),
		0पूर्ण,
	अणुSOF_TKN_INTEL_DMIC_PDM_MIC_B_Enable,
		SND_SOC_TPLG_TUPLE_TYPE_SHORT, get_token_u16,
		दुरत्व(काष्ठा sof_ipc_dai_dmic_pdm_ctrl, enable_mic_b),
		0पूर्ण,
	अणुSOF_TKN_INTEL_DMIC_PDM_POLARITY_A,
		SND_SOC_TPLG_TUPLE_TYPE_SHORT, get_token_u16,
		दुरत्व(काष्ठा sof_ipc_dai_dmic_pdm_ctrl, polarity_mic_a),
		0पूर्ण,
	अणुSOF_TKN_INTEL_DMIC_PDM_POLARITY_B,
		SND_SOC_TPLG_TUPLE_TYPE_SHORT, get_token_u16,
		दुरत्व(काष्ठा sof_ipc_dai_dmic_pdm_ctrl, polarity_mic_b),
		0पूर्ण,
	अणुSOF_TKN_INTEL_DMIC_PDM_CLK_EDGE,
		SND_SOC_TPLG_TUPLE_TYPE_SHORT, get_token_u16,
		दुरत्व(काष्ठा sof_ipc_dai_dmic_pdm_ctrl, clk_edge),
		0पूर्ण,
	अणुSOF_TKN_INTEL_DMIC_PDM_SKEW,
		SND_SOC_TPLG_TUPLE_TYPE_SHORT, get_token_u16,
		दुरत्व(काष्ठा sof_ipc_dai_dmic_pdm_ctrl, skew),
		0पूर्ण,
पूर्ण;

/* HDA */
अटल स्थिर काष्ठा sof_topology_token hda_tokens[] = अणु
	अणुSOF_TKN_INTEL_HDA_RATE,
		SND_SOC_TPLG_TUPLE_TYPE_WORD, get_token_u32,
		दुरत्व(काष्ठा sof_ipc_dai_hda_params, rate), 0पूर्ण,
	अणुSOF_TKN_INTEL_HDA_CH,
		SND_SOC_TPLG_TUPLE_TYPE_WORD, get_token_u32,
		दुरत्व(काष्ठा sof_ipc_dai_hda_params, channels), 0पूर्ण,
पूर्ण;

/* Leds */
अटल स्थिर काष्ठा sof_topology_token led_tokens[] = अणु
	अणुSOF_TKN_MUTE_LED_USE, SND_SOC_TPLG_TUPLE_TYPE_WORD, get_token_u32,
	 दुरत्व(काष्ठा snd_sof_led_control, use_led), 0पूर्ण,
	अणुSOF_TKN_MUTE_LED_सूचीECTION, SND_SOC_TPLG_TUPLE_TYPE_WORD,
	 get_token_u32, दुरत्व(काष्ठा snd_sof_led_control, direction), 0पूर्ण,
पूर्ण;

अटल पूर्णांक sof_parse_uuid_tokens(काष्ठा snd_soc_component *scomp,
				 व्योम *object,
				 स्थिर काष्ठा sof_topology_token *tokens,
				 पूर्णांक count,
				 काष्ठा snd_soc_tplg_venकरोr_array *array,
				 माप_प्रकार offset)
अणु
	काष्ठा snd_soc_tplg_venकरोr_uuid_elem *elem;
	पूर्णांक found = 0;
	पूर्णांक i, j;

	/* parse element by element */
	क्रम (i = 0; i < le32_to_cpu(array->num_elems); i++) अणु
		elem = &array->uuid[i];

		/* search क्रम token */
		क्रम (j = 0; j < count; j++) अणु
			/* match token type */
			अगर (tokens[j].type != SND_SOC_TPLG_TUPLE_TYPE_UUID)
				जारी;

			/* match token id */
			अगर (tokens[j].token != le32_to_cpu(elem->token))
				जारी;

			/* matched - now load token */
			tokens[j].get_token(elem, object,
					    offset + tokens[j].offset,
					    tokens[j].size);

			found++;
		पूर्ण
	पूर्ण

	वापस found;
पूर्ण

अटल पूर्णांक sof_parse_string_tokens(काष्ठा snd_soc_component *scomp,
				   व्योम *object,
				   स्थिर काष्ठा sof_topology_token *tokens,
				   पूर्णांक count,
				   काष्ठा snd_soc_tplg_venकरोr_array *array,
				   माप_प्रकार offset)
अणु
	काष्ठा snd_soc_tplg_venकरोr_string_elem *elem;
	पूर्णांक found = 0;
	पूर्णांक i, j;

	/* parse element by element */
	क्रम (i = 0; i < le32_to_cpu(array->num_elems); i++) अणु
		elem = &array->string[i];

		/* search क्रम token */
		क्रम (j = 0; j < count; j++) अणु
			/* match token type */
			अगर (tokens[j].type != SND_SOC_TPLG_TUPLE_TYPE_STRING)
				जारी;

			/* match token id */
			अगर (tokens[j].token != le32_to_cpu(elem->token))
				जारी;

			/* matched - now load token */
			tokens[j].get_token(elem, object,
					    offset + tokens[j].offset,
					    tokens[j].size);

			found++;
		पूर्ण
	पूर्ण

	वापस found;
पूर्ण

अटल पूर्णांक sof_parse_word_tokens(काष्ठा snd_soc_component *scomp,
				 व्योम *object,
				 स्थिर काष्ठा sof_topology_token *tokens,
				 पूर्णांक count,
				 काष्ठा snd_soc_tplg_venकरोr_array *array,
				 माप_प्रकार offset)
अणु
	काष्ठा snd_soc_tplg_venकरोr_value_elem *elem;
	पूर्णांक found = 0;
	पूर्णांक i, j;

	/* parse element by element */
	क्रम (i = 0; i < le32_to_cpu(array->num_elems); i++) अणु
		elem = &array->value[i];

		/* search क्रम token */
		क्रम (j = 0; j < count; j++) अणु
			/* match token type */
			अगर (!(tokens[j].type == SND_SOC_TPLG_TUPLE_TYPE_WORD ||
			      tokens[j].type == SND_SOC_TPLG_TUPLE_TYPE_SHORT ||
			      tokens[j].type == SND_SOC_TPLG_TUPLE_TYPE_BYTE ||
			      tokens[j].type == SND_SOC_TPLG_TUPLE_TYPE_BOOL))
				जारी;

			/* match token id */
			अगर (tokens[j].token != le32_to_cpu(elem->token))
				जारी;

			/* load token */
			tokens[j].get_token(elem, object,
					    offset + tokens[j].offset,
					    tokens[j].size);

			found++;
		पूर्ण
	पूर्ण

	वापस found;
पूर्ण

/**
 * sof_parse_token_sets - Parse multiple sets of tokens
 * @scomp: poपूर्णांकer to soc component
 * @object: target ipc काष्ठा क्रम parsed values
 * @tokens: token definition array describing what tokens to parse
 * @count: number of tokens in definition array
 * @array: source poपूर्णांकer to consecutive venकरोr arrays to be parsed
 * @priv_size: total size of the consecutive source arrays
 * @sets: number of similar token sets to be parsed, 1 set has count elements
 * @object_size: offset to next target ipc काष्ठा with multiple sets
 *
 * This function parses multiple sets of tokens in venकरोr arrays पूर्णांकo
 * consecutive ipc काष्ठाs.
 */
अटल पूर्णांक sof_parse_token_sets(काष्ठा snd_soc_component *scomp,
				व्योम *object,
				स्थिर काष्ठा sof_topology_token *tokens,
				पूर्णांक count,
				काष्ठा snd_soc_tplg_venकरोr_array *array,
				पूर्णांक priv_size, पूर्णांक sets, माप_प्रकार object_size)
अणु
	माप_प्रकार offset = 0;
	पूर्णांक found = 0;
	पूर्णांक total = 0;
	पूर्णांक asize;

	जबतक (priv_size > 0 && total < count * sets) अणु
		asize = le32_to_cpu(array->size);

		/* validate asize */
		अगर (asize < 0) अणु /* FIXME: A zero-size array makes no sense */
			dev_err(scomp->dev, "error: invalid array size 0x%x\n",
				asize);
			वापस -EINVAL;
		पूर्ण

		/* make sure there is enough data beक्रमe parsing */
		priv_size -= asize;
		अगर (priv_size < 0) अणु
			dev_err(scomp->dev, "error: invalid array size 0x%x\n",
				asize);
			वापस -EINVAL;
		पूर्ण

		/* call correct parser depending on type */
		चयन (le32_to_cpu(array->type)) अणु
		हाल SND_SOC_TPLG_TUPLE_TYPE_UUID:
			found += sof_parse_uuid_tokens(scomp, object, tokens,
						       count, array, offset);
			अवरोध;
		हाल SND_SOC_TPLG_TUPLE_TYPE_STRING:
			found += sof_parse_string_tokens(scomp, object, tokens,
							 count, array, offset);
			अवरोध;
		हाल SND_SOC_TPLG_TUPLE_TYPE_BOOL:
		हाल SND_SOC_TPLG_TUPLE_TYPE_BYTE:
		हाल SND_SOC_TPLG_TUPLE_TYPE_WORD:
		हाल SND_SOC_TPLG_TUPLE_TYPE_SHORT:
			found += sof_parse_word_tokens(scomp, object, tokens,
						       count, array, offset);
			अवरोध;
		शेष:
			dev_err(scomp->dev, "error: unknown token type %d\n",
				array->type);
			वापस -EINVAL;
		पूर्ण

		/* next array */
		array = (काष्ठा snd_soc_tplg_venकरोr_array *)((u8 *)array
			+ asize);

		/* move to next target काष्ठा */
		अगर (found >= count) अणु
			offset += object_size;
			total += found;
			found = 0;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sof_parse_tokens(काष्ठा snd_soc_component *scomp,
			    व्योम *object,
			    स्थिर काष्ठा sof_topology_token *tokens,
			    पूर्णांक count,
			    काष्ठा snd_soc_tplg_venकरोr_array *array,
			    पूर्णांक priv_size)
अणु
	/*
	 * sof_parse_tokens is used when topology contains only a single set of
	 * identical tuples arrays. So additional parameters to
	 * sof_parse_token_sets are sets = 1 (only 1 set) and
	 * object_size = 0 (irrelevant).
	 */
	वापस sof_parse_token_sets(scomp, object, tokens, count, array,
				    priv_size, 1, 0);
पूर्ण

अटल व्योम sof_dbg_comp_config(काष्ठा snd_soc_component *scomp,
				काष्ठा sof_ipc_comp_config *config)
अणु
	dev_dbg(scomp->dev, " config: periods snk %d src %d fmt %d\n",
		config->periods_sink, config->periods_source,
		config->frame_fmt);
पूर्ण

/*
 * Standard Kcontrols.
 */

अटल पूर्णांक sof_control_load_volume(काष्ठा snd_soc_component *scomp,
				   काष्ठा snd_sof_control *scontrol,
				   काष्ठा snd_kcontrol_new *kc,
				   काष्ठा snd_soc_tplg_ctl_hdr *hdr)
अणु
	काष्ठा snd_sof_dev *sdev = snd_soc_component_get_drvdata(scomp);
	काष्ठा snd_soc_tplg_mixer_control *mc =
		container_of(hdr, काष्ठा snd_soc_tplg_mixer_control, hdr);
	काष्ठा sof_ipc_ctrl_data *cdata;
	पूर्णांक tlv[TLV_ITEMS];
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	/* validate topology data */
	अगर (le32_to_cpu(mc->num_channels) > SND_SOC_TPLG_MAX_CHAN) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/*
	 * If control has more than 2 channels we need to override the info. This is because even अगर
	 * ASoC layer has defined topology's max channel count to SND_SOC_TPLG_MAX_CHAN = 8, the
	 * pre-defined dapm control types (and related functions) creating the actual control
	 * restrict the channels only to mono or stereo.
	 */
	अगर (le32_to_cpu(mc->num_channels) > 2)
		kc->info = snd_sof_volume_info;

	/* init the volume get/put data */
	scontrol->size = काष्ठा_size(scontrol->control_data, chanv,
				     le32_to_cpu(mc->num_channels));
	scontrol->control_data = kzalloc(scontrol->size, GFP_KERNEL);
	अगर (!scontrol->control_data) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	scontrol->comp_id = sdev->next_comp_id;
	scontrol->min_volume_step = le32_to_cpu(mc->min);
	scontrol->max_volume_step = le32_to_cpu(mc->max);
	scontrol->num_channels = le32_to_cpu(mc->num_channels);

	/* set cmd क्रम mixer control */
	अगर (le32_to_cpu(mc->max) == 1) अणु
		scontrol->cmd = SOF_CTRL_CMD_SWITCH;
		जाओ skip;
	पूर्ण

	scontrol->cmd = SOF_CTRL_CMD_VOLUME;

	/* extract tlv data */
	अगर (!kc->tlv.p || get_tlv_data(kc->tlv.p, tlv) < 0) अणु
		dev_err(scomp->dev, "error: invalid TLV data\n");
		ret = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण

	/* set up volume table */
	ret = set_up_volume_table(scontrol, tlv, le32_to_cpu(mc->max) + 1);
	अगर (ret < 0) अणु
		dev_err(scomp->dev, "error: setting up volume table\n");
		जाओ out_मुक्त;
	पूर्ण

	/* set शेष volume values to 0dB in control */
	cdata = scontrol->control_data;
	क्रम (i = 0; i < scontrol->num_channels; i++) अणु
		cdata->chanv[i].channel = i;
		cdata->chanv[i].value = VOL_ZERO_DB;
	पूर्ण

skip:
	/* set up possible led control from mixer निजी data */
	ret = sof_parse_tokens(scomp, &scontrol->led_ctl, led_tokens,
			       ARRAY_SIZE(led_tokens), mc->priv.array,
			       le32_to_cpu(mc->priv.size));
	अगर (ret != 0) अणु
		dev_err(scomp->dev, "error: parse led tokens failed %d\n",
			le32_to_cpu(mc->priv.size));
		जाओ out_मुक्त_table;
	पूर्ण

	dev_dbg(scomp->dev, "tplg: load kcontrol index %d chans %d\n",
		scontrol->comp_id, scontrol->num_channels);

	वापस 0;

out_मुक्त_table:
	अगर (le32_to_cpu(mc->max) > 1)
		kमुक्त(scontrol->volume_table);
out_मुक्त:
	kमुक्त(scontrol->control_data);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक sof_control_load_क्रमागत(काष्ठा snd_soc_component *scomp,
				 काष्ठा snd_sof_control *scontrol,
				 काष्ठा snd_kcontrol_new *kc,
				 काष्ठा snd_soc_tplg_ctl_hdr *hdr)
अणु
	काष्ठा snd_sof_dev *sdev = snd_soc_component_get_drvdata(scomp);
	काष्ठा snd_soc_tplg_क्रमागत_control *ec =
		container_of(hdr, काष्ठा snd_soc_tplg_क्रमागत_control, hdr);

	/* validate topology data */
	अगर (le32_to_cpu(ec->num_channels) > SND_SOC_TPLG_MAX_CHAN)
		वापस -EINVAL;

	/* init the क्रमागत get/put data */
	scontrol->size = काष्ठा_size(scontrol->control_data, chanv,
				     le32_to_cpu(ec->num_channels));
	scontrol->control_data = kzalloc(scontrol->size, GFP_KERNEL);
	अगर (!scontrol->control_data)
		वापस -ENOMEM;

	scontrol->comp_id = sdev->next_comp_id;
	scontrol->num_channels = le32_to_cpu(ec->num_channels);

	scontrol->cmd = SOF_CTRL_CMD_ENUM;

	dev_dbg(scomp->dev, "tplg: load kcontrol index %d chans %d comp_id %d\n",
		scontrol->comp_id, scontrol->num_channels, scontrol->comp_id);

	वापस 0;
पूर्ण

अटल पूर्णांक sof_control_load_bytes(काष्ठा snd_soc_component *scomp,
				  काष्ठा snd_sof_control *scontrol,
				  काष्ठा snd_kcontrol_new *kc,
				  काष्ठा snd_soc_tplg_ctl_hdr *hdr)
अणु
	काष्ठा snd_sof_dev *sdev = snd_soc_component_get_drvdata(scomp);
	काष्ठा sof_ipc_ctrl_data *cdata;
	काष्ठा snd_soc_tplg_bytes_control *control =
		container_of(hdr, काष्ठा snd_soc_tplg_bytes_control, hdr);
	काष्ठा soc_bytes_ext *sbe = (काष्ठा soc_bytes_ext *)kc->निजी_value;
	माप_प्रकार max_size = sbe->max;
	माप_प्रकार priv_size = le32_to_cpu(control->priv.size);
	पूर्णांक ret;

	अगर (max_size < माप(काष्ठा sof_ipc_ctrl_data) ||
	    max_size < माप(काष्ठा sof_abi_hdr)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/* init the get/put bytes data */
	अगर (priv_size > max_size - माप(काष्ठा sof_ipc_ctrl_data)) अणु
		dev_err(scomp->dev, "err: bytes data size %zu exceeds max %zu.\n",
			priv_size, max_size - माप(काष्ठा sof_ipc_ctrl_data));
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	scontrol->size = माप(काष्ठा sof_ipc_ctrl_data) + priv_size;

	scontrol->control_data = kzalloc(max_size, GFP_KERNEL);
	cdata = scontrol->control_data;
	अगर (!scontrol->control_data) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	scontrol->comp_id = sdev->next_comp_id;
	scontrol->cmd = SOF_CTRL_CMD_BINARY;

	dev_dbg(scomp->dev, "tplg: load kcontrol index %d chans %d\n",
		scontrol->comp_id, scontrol->num_channels);

	अगर (le32_to_cpu(control->priv.size) > 0) अणु
		स_नकल(cdata->data, control->priv.data,
		       le32_to_cpu(control->priv.size));

		अगर (cdata->data->magic != SOF_ABI_MAGIC) अणु
			dev_err(scomp->dev, "error: Wrong ABI magic 0x%08x.\n",
				cdata->data->magic);
			ret = -EINVAL;
			जाओ out_मुक्त;
		पूर्ण
		अगर (SOF_ABI_VERSION_INCOMPATIBLE(SOF_ABI_VERSION,
						 cdata->data->abi)) अणु
			dev_err(scomp->dev,
				"error: Incompatible ABI version 0x%08x.\n",
				cdata->data->abi);
			ret = -EINVAL;
			जाओ out_मुक्त;
		पूर्ण
		अगर (cdata->data->size + माप(काष्ठा sof_abi_hdr) !=
		    le32_to_cpu(control->priv.size)) अणु
			dev_err(scomp->dev,
				"error: Conflict in bytes vs. priv size.\n");
			ret = -EINVAL;
			जाओ out_मुक्त;
		पूर्ण
	पूर्ण

	वापस 0;

out_मुक्त:
	kमुक्त(scontrol->control_data);
out:
	वापस ret;
पूर्ण

/* बाह्यal kcontrol init - used क्रम any driver specअगरic init */
अटल पूर्णांक sof_control_load(काष्ठा snd_soc_component *scomp, पूर्णांक index,
			    काष्ठा snd_kcontrol_new *kc,
			    काष्ठा snd_soc_tplg_ctl_hdr *hdr)
अणु
	काष्ठा soc_mixer_control *sm;
	काष्ठा soc_bytes_ext *sbe;
	काष्ठा soc_क्रमागत *se;
	काष्ठा snd_sof_dev *sdev = snd_soc_component_get_drvdata(scomp);
	काष्ठा snd_soc_करोbj *करोbj;
	काष्ठा snd_sof_control *scontrol;
	पूर्णांक ret;

	dev_dbg(scomp->dev, "tplg: load control type %d name : %s\n",
		hdr->type, hdr->name);

	scontrol = kzalloc(माप(*scontrol), GFP_KERNEL);
	अगर (!scontrol)
		वापस -ENOMEM;

	scontrol->scomp = scomp;

	चयन (le32_to_cpu(hdr->ops.info)) अणु
	हाल SND_SOC_TPLG_CTL_VOLSW:
	हाल SND_SOC_TPLG_CTL_VOLSW_SX:
	हाल SND_SOC_TPLG_CTL_VOLSW_XR_SX:
		sm = (काष्ठा soc_mixer_control *)kc->निजी_value;
		करोbj = &sm->करोbj;
		ret = sof_control_load_volume(scomp, scontrol, kc, hdr);
		अवरोध;
	हाल SND_SOC_TPLG_CTL_BYTES:
		sbe = (काष्ठा soc_bytes_ext *)kc->निजी_value;
		करोbj = &sbe->करोbj;
		ret = sof_control_load_bytes(scomp, scontrol, kc, hdr);
		अवरोध;
	हाल SND_SOC_TPLG_CTL_ENUM:
	हाल SND_SOC_TPLG_CTL_ENUM_VALUE:
		se = (काष्ठा soc_क्रमागत *)kc->निजी_value;
		करोbj = &se->करोbj;
		ret = sof_control_load_क्रमागत(scomp, scontrol, kc, hdr);
		अवरोध;
	हाल SND_SOC_TPLG_CTL_RANGE:
	हाल SND_SOC_TPLG_CTL_STROBE:
	हाल SND_SOC_TPLG_DAPM_CTL_VOLSW:
	हाल SND_SOC_TPLG_DAPM_CTL_ENUM_DOUBLE:
	हाल SND_SOC_TPLG_DAPM_CTL_ENUM_VIRT:
	हाल SND_SOC_TPLG_DAPM_CTL_ENUM_VALUE:
	हाल SND_SOC_TPLG_DAPM_CTL_PIN:
	शेष:
		dev_warn(scomp->dev, "control type not supported %d:%d:%d\n",
			 hdr->ops.get, hdr->ops.put, hdr->ops.info);
		kमुक्त(scontrol);
		वापस 0;
	पूर्ण

	अगर (ret < 0) अणु
		kमुक्त(scontrol);
		वापस ret;
	पूर्ण

	scontrol->led_ctl.led_value = -1;

	करोbj->निजी = scontrol;
	list_add(&scontrol->list, &sdev->kcontrol_list);
	वापस 0;
पूर्ण

अटल पूर्णांक sof_control_unload(काष्ठा snd_soc_component *scomp,
			      काष्ठा snd_soc_करोbj *करोbj)
अणु
	काष्ठा snd_sof_dev *sdev = snd_soc_component_get_drvdata(scomp);
	काष्ठा sof_ipc_मुक्त fcomp;
	काष्ठा snd_sof_control *scontrol = करोbj->निजी;

	dev_dbg(scomp->dev, "tplg: unload control name : %s\n", scomp->name);

	fcomp.hdr.cmd = SOF_IPC_GLB_TPLG_MSG | SOF_IPC_TPLG_COMP_FREE;
	fcomp.hdr.size = माप(fcomp);
	fcomp.id = scontrol->comp_id;

	kमुक्त(scontrol->control_data);
	list_del(&scontrol->list);
	kमुक्त(scontrol);
	/* send IPC to the DSP */
	वापस sof_ipc_tx_message(sdev->ipc,
				  fcomp.hdr.cmd, &fcomp, माप(fcomp),
				  शून्य, 0);
पूर्ण

/*
 * DAI Topology
 */

/* Static DSP core घातer management so far, should be extended in the future */
अटल पूर्णांक sof_core_enable(काष्ठा snd_sof_dev *sdev, पूर्णांक core)
अणु
	काष्ठा sof_ipc_pm_core_config pm_core_config = अणु
		.hdr = अणु
			.cmd = SOF_IPC_GLB_PM_MSG | SOF_IPC_PM_CORE_ENABLE,
			.size = माप(pm_core_config),
		पूर्ण,
		.enable_mask = sdev->enabled_cores_mask | BIT(core),
	पूर्ण;
	पूर्णांक ret;

	अगर (sdev->enabled_cores_mask & BIT(core))
		वापस 0;

	/* घातer up the core अगर it is host managed */
	ret = snd_sof_dsp_core_घातer_up(sdev, BIT(core));
	अगर (ret < 0) अणु
		dev_err(sdev->dev, "error: %d powering up core %d\n",
			ret, core);
		वापस ret;
	पूर्ण

	/* Now notअगरy DSP */
	ret = sof_ipc_tx_message(sdev->ipc, pm_core_config.hdr.cmd,
				 &pm_core_config, माप(pm_core_config),
				 &pm_core_config, माप(pm_core_config));
	अगर (ret < 0) अणु
		dev_err(sdev->dev, "error: core %d enable ipc failure %d\n",
			core, ret);
		जाओ err;
	पूर्ण
	वापस ret;
err:
	/* घातer करोwn core अगर it is host managed and वापस the original error अगर this fails too */
	अगर (snd_sof_dsp_core_घातer_करोwn(sdev, BIT(core)) < 0)
		dev_err(sdev->dev, "error: powering down core %d\n", core);

	वापस ret;
पूर्ण

पूर्णांक sof_pipeline_core_enable(काष्ठा snd_sof_dev *sdev,
			     स्थिर काष्ठा snd_sof_widget *swidget)
अणु
	स्थिर काष्ठा sof_ipc_pipe_new *pipeline;
	पूर्णांक ret;

	अगर (swidget->id == snd_soc_dapm_scheduler) अणु
		pipeline = swidget->निजी;
	पूर्ण अन्यथा अणु
		pipeline = snd_sof_pipeline_find(sdev, swidget->pipeline_id);
		अगर (!pipeline)
			वापस -ENOENT;
	पूर्ण

	/* First enable the pipeline core */
	ret = sof_core_enable(sdev, pipeline->core);
	अगर (ret < 0)
		वापस ret;

	वापस sof_core_enable(sdev, swidget->core);
पूर्ण

अटल पूर्णांक sof_connect_dai_widget(काष्ठा snd_soc_component *scomp,
				  काष्ठा snd_soc_dapm_widget *w,
				  काष्ठा snd_soc_tplg_dapm_widget *tw,
				  काष्ठा snd_sof_dai *dai)
अणु
	काष्ठा snd_soc_card *card = scomp->card;
	काष्ठा snd_soc_pcm_runसमय *rtd;
	काष्ठा snd_soc_dai *cpu_dai;
	पूर्णांक i;

	list_क्रम_each_entry(rtd, &card->rtd_list, list) अणु
		dev_vdbg(scomp->dev, "tplg: check widget: %s stream: %s dai stream: %s\n",
			 w->name,  w->sname, rtd->dai_link->stream_name);

		अगर (!w->sname || !rtd->dai_link->stream_name)
			जारी;

		/* करोes stream match DAI link ? */
		अगर (म_भेद(w->sname, rtd->dai_link->stream_name))
			जारी;

		चयन (w->id) अणु
		हाल snd_soc_dapm_dai_out:
			क्रम_each_rtd_cpu_dais(rtd, i, cpu_dai) अणु
				/*
				 * Please create DAI widget in the right order
				 * to ensure BE will connect to the right DAI
				 * widget.
				 */
				अगर (!cpu_dai->capture_widget) अणु
					cpu_dai->capture_widget = w;
					अवरोध;
				पूर्ण
			पूर्ण
			अगर (i == rtd->num_cpus) अणु
				dev_err(scomp->dev, "error: can't find BE for DAI %s\n",
					w->name);

				वापस -EINVAL;
			पूर्ण
			dai->name = rtd->dai_link->name;
			dev_dbg(scomp->dev, "tplg: connected widget %s -> DAI link %s\n",
				w->name, rtd->dai_link->name);
			अवरोध;
		हाल snd_soc_dapm_dai_in:
			क्रम_each_rtd_cpu_dais(rtd, i, cpu_dai) अणु
				/*
				 * Please create DAI widget in the right order
				 * to ensure BE will connect to the right DAI
				 * widget.
				 */
				अगर (!cpu_dai->playback_widget) अणु
					cpu_dai->playback_widget = w;
					अवरोध;
				पूर्ण
			पूर्ण
			अगर (i == rtd->num_cpus) अणु
				dev_err(scomp->dev, "error: can't find BE for DAI %s\n",
					w->name);

				वापस -EINVAL;
			पूर्ण
			dai->name = rtd->dai_link->name;
			dev_dbg(scomp->dev, "tplg: connected widget %s -> DAI link %s\n",
				w->name, rtd->dai_link->name);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	/* check we have a connection */
	अगर (!dai->name) अणु
		dev_err(scomp->dev, "error: can't connect DAI %s stream %s\n",
			w->name, w->sname);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * sof_comp_alloc - allocate and initialize buffer क्रम a new component
 * @swidget: poपूर्णांकer to काष्ठा snd_sof_widget containing extended data
 * @ipc_size: IPC payload size that will be updated depending on valid
 *  extended data.
 * @index: ID of the pipeline the component beदीर्घs to
 *
 * Return: The poपूर्णांकer to the new allocated component, शून्य अगर failed.
 */
अटल काष्ठा sof_ipc_comp *sof_comp_alloc(काष्ठा snd_sof_widget *swidget,
					   माप_प्रकार *ipc_size, पूर्णांक index)
अणु
	u8 nil_uuid[SOF_UUID_SIZE] = अणु0पूर्ण;
	काष्ठा sof_ipc_comp *comp;
	माप_प्रकार total_size = *ipc_size;

	/* only non-zero UUID is valid */
	अगर (स_भेद(&swidget->comp_ext, nil_uuid, SOF_UUID_SIZE))
		total_size += माप(swidget->comp_ext);

	comp = kzalloc(total_size, GFP_KERNEL);
	अगर (!comp)
		वापस शून्य;

	/* configure comp new IPC message */
	comp->hdr.size = total_size;
	comp->hdr.cmd = SOF_IPC_GLB_TPLG_MSG | SOF_IPC_TPLG_COMP_NEW;
	comp->id = swidget->comp_id;
	comp->pipeline_id = index;
	comp->core = swidget->core;

	/* handle the extended data अगर needed */
	अगर (total_size > *ipc_size) अणु
		/* append extended data to the end of the component */
		स_नकल((u8 *)comp + *ipc_size, &swidget->comp_ext, माप(swidget->comp_ext));
		comp->ext_data_length = माप(swidget->comp_ext);
	पूर्ण

	/* update ipc_size and वापस */
	*ipc_size = total_size;
	वापस comp;
पूर्ण

अटल पूर्णांक sof_widget_load_dai(काष्ठा snd_soc_component *scomp, पूर्णांक index,
			       काष्ठा snd_sof_widget *swidget,
			       काष्ठा snd_soc_tplg_dapm_widget *tw,
			       काष्ठा sof_ipc_comp_reply *r,
			       काष्ठा snd_sof_dai *dai)
अणु
	काष्ठा snd_sof_dev *sdev = snd_soc_component_get_drvdata(scomp);
	काष्ठा snd_soc_tplg_निजी *निजी = &tw->priv;
	काष्ठा sof_ipc_comp_dai *comp_dai;
	माप_प्रकार ipc_size = माप(*comp_dai);
	पूर्णांक ret;

	comp_dai = (काष्ठा sof_ipc_comp_dai *)
		   sof_comp_alloc(swidget, &ipc_size, index);
	अगर (!comp_dai)
		वापस -ENOMEM;

	/* configure dai IPC message */
	comp_dai->comp.type = SOF_COMP_DAI;
	comp_dai->config.hdr.size = माप(comp_dai->config);

	ret = sof_parse_tokens(scomp, comp_dai, dai_tokens,
			       ARRAY_SIZE(dai_tokens), निजी->array,
			       le32_to_cpu(निजी->size));
	अगर (ret != 0) अणु
		dev_err(scomp->dev, "error: parse dai tokens failed %d\n",
			le32_to_cpu(निजी->size));
		जाओ finish;
	पूर्ण

	ret = sof_parse_tokens(scomp, &comp_dai->config, comp_tokens,
			       ARRAY_SIZE(comp_tokens), निजी->array,
			       le32_to_cpu(निजी->size));
	अगर (ret != 0) अणु
		dev_err(scomp->dev, "error: parse dai.cfg tokens failed %d\n",
			निजी->size);
		जाओ finish;
	पूर्ण

	dev_dbg(scomp->dev, "dai %s: type %d index %d\n",
		swidget->widget->name, comp_dai->type, comp_dai->dai_index);
	sof_dbg_comp_config(scomp, &comp_dai->config);

	ret = sof_ipc_tx_message(sdev->ipc, comp_dai->comp.hdr.cmd,
				 comp_dai, ipc_size, r, माप(*r));

	अगर (ret == 0 && dai) अणु
		dai->scomp = scomp;

		/*
		 * copy only the sof_ipc_comp_dai to aव्योम collapsing
		 * the snd_sof_dai, the extended data is kept in the
		 * snd_sof_widget.
		 */
		स_नकल(&dai->comp_dai, comp_dai, माप(*comp_dai));
	पूर्ण

finish:
	kमुक्त(comp_dai);
	वापस ret;
पूर्ण

/*
 * Buffer topology
 */

अटल पूर्णांक sof_widget_load_buffer(काष्ठा snd_soc_component *scomp, पूर्णांक index,
				  काष्ठा snd_sof_widget *swidget,
				  काष्ठा snd_soc_tplg_dapm_widget *tw,
				  काष्ठा sof_ipc_comp_reply *r)
अणु
	काष्ठा snd_sof_dev *sdev = snd_soc_component_get_drvdata(scomp);
	काष्ठा snd_soc_tplg_निजी *निजी = &tw->priv;
	काष्ठा sof_ipc_buffer *buffer;
	पूर्णांक ret;

	buffer = kzalloc(माप(*buffer), GFP_KERNEL);
	अगर (!buffer)
		वापस -ENOMEM;

	/* configure dai IPC message */
	buffer->comp.hdr.size = माप(*buffer);
	buffer->comp.hdr.cmd = SOF_IPC_GLB_TPLG_MSG | SOF_IPC_TPLG_BUFFER_NEW;
	buffer->comp.id = swidget->comp_id;
	buffer->comp.type = SOF_COMP_BUFFER;
	buffer->comp.pipeline_id = index;
	buffer->comp.core = swidget->core;

	ret = sof_parse_tokens(scomp, buffer, buffer_tokens,
			       ARRAY_SIZE(buffer_tokens), निजी->array,
			       le32_to_cpu(निजी->size));
	अगर (ret != 0) अणु
		dev_err(scomp->dev, "error: parse buffer tokens failed %d\n",
			निजी->size);
		kमुक्त(buffer);
		वापस ret;
	पूर्ण

	dev_dbg(scomp->dev, "buffer %s: size %d caps 0x%x\n",
		swidget->widget->name, buffer->size, buffer->caps);

	swidget->निजी = buffer;

	ret = sof_ipc_tx_message(sdev->ipc, buffer->comp.hdr.cmd, buffer,
				 माप(*buffer), r, माप(*r));
	अगर (ret < 0) अणु
		dev_err(scomp->dev, "error: buffer %s load failed\n",
			swidget->widget->name);
		kमुक्त(buffer);
	पूर्ण

	वापस ret;
पूर्ण

/* bind PCM ID to host component ID */
अटल पूर्णांक spcm_bind(काष्ठा snd_soc_component *scomp, काष्ठा snd_sof_pcm *spcm,
		     पूर्णांक dir)
अणु
	काष्ठा snd_sof_widget *host_widget;

	host_widget = snd_sof_find_swidget_sname(scomp,
						 spcm->pcm.caps[dir].name,
						 dir);
	अगर (!host_widget) अणु
		dev_err(scomp->dev, "can't find host comp to bind pcm\n");
		वापस -EINVAL;
	पूर्ण

	spcm->stream[dir].comp_id = host_widget->comp_id;

	वापस 0;
पूर्ण

/*
 * PCM Topology
 */

अटल पूर्णांक sof_widget_load_pcm(काष्ठा snd_soc_component *scomp, पूर्णांक index,
			       काष्ठा snd_sof_widget *swidget,
			       क्रमागत sof_ipc_stream_direction dir,
			       काष्ठा snd_soc_tplg_dapm_widget *tw,
			       काष्ठा sof_ipc_comp_reply *r)
अणु
	काष्ठा snd_sof_dev *sdev = snd_soc_component_get_drvdata(scomp);
	काष्ठा snd_soc_tplg_निजी *निजी = &tw->priv;
	काष्ठा sof_ipc_comp_host *host;
	माप_प्रकार ipc_size = माप(*host);
	पूर्णांक ret;

	host = (काष्ठा sof_ipc_comp_host *)
	       sof_comp_alloc(swidget, &ipc_size, index);
	अगर (!host)
		वापस -ENOMEM;

	/* configure host comp IPC message */
	host->comp.type = SOF_COMP_HOST;
	host->direction = dir;
	host->config.hdr.size = माप(host->config);

	ret = sof_parse_tokens(scomp, host, pcm_tokens,
			       ARRAY_SIZE(pcm_tokens), निजी->array,
			       le32_to_cpu(निजी->size));
	अगर (ret != 0) अणु
		dev_err(scomp->dev, "error: parse host tokens failed %d\n",
			निजी->size);
		जाओ err;
	पूर्ण

	ret = sof_parse_tokens(scomp, &host->config, comp_tokens,
			       ARRAY_SIZE(comp_tokens), निजी->array,
			       le32_to_cpu(निजी->size));
	अगर (ret != 0) अणु
		dev_err(scomp->dev, "error: parse host.cfg tokens failed %d\n",
			le32_to_cpu(निजी->size));
		जाओ err;
	पूर्ण

	dev_dbg(scomp->dev, "loaded host %s\n", swidget->widget->name);
	sof_dbg_comp_config(scomp, &host->config);

	swidget->निजी = host;

	ret = sof_ipc_tx_message(sdev->ipc, host->comp.hdr.cmd, host,
				 ipc_size, r, माप(*r));
	अगर (ret >= 0)
		वापस ret;
err:
	kमुक्त(host);
	वापस ret;
पूर्ण

/*
 * Pipeline Topology
 */
पूर्णांक sof_load_pipeline_ipc(काष्ठा device *dev,
			  काष्ठा sof_ipc_pipe_new *pipeline,
			  काष्ठा sof_ipc_comp_reply *r)
अणु
	काष्ठा snd_sof_dev *sdev = dev_get_drvdata(dev);
	पूर्णांक ret = sof_core_enable(sdev, pipeline->core);

	अगर (ret < 0)
		वापस ret;

	ret = sof_ipc_tx_message(sdev->ipc, pipeline->hdr.cmd, pipeline,
				 माप(*pipeline), r, माप(*r));
	अगर (ret < 0)
		dev_err(dev, "error: load pipeline ipc failure\n");

	वापस ret;
पूर्ण

अटल पूर्णांक sof_widget_load_pipeline(काष्ठा snd_soc_component *scomp, पूर्णांक index,
				    काष्ठा snd_sof_widget *swidget,
				    काष्ठा snd_soc_tplg_dapm_widget *tw,
				    काष्ठा sof_ipc_comp_reply *r)
अणु
	काष्ठा snd_soc_tplg_निजी *निजी = &tw->priv;
	काष्ठा sof_ipc_pipe_new *pipeline;
	काष्ठा snd_sof_widget *comp_swidget;
	पूर्णांक ret;

	pipeline = kzalloc(माप(*pipeline), GFP_KERNEL);
	अगर (!pipeline)
		वापस -ENOMEM;

	/* configure dai IPC message */
	pipeline->hdr.size = माप(*pipeline);
	pipeline->hdr.cmd = SOF_IPC_GLB_TPLG_MSG | SOF_IPC_TPLG_PIPE_NEW;
	pipeline->pipeline_id = index;
	pipeline->comp_id = swidget->comp_id;

	/* component at start of pipeline is our stream id */
	comp_swidget = snd_sof_find_swidget(scomp, tw->sname);
	अगर (!comp_swidget) अणु
		dev_err(scomp->dev, "error: widget %s refers to non existent widget %s\n",
			tw->name, tw->sname);
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	pipeline->sched_id = comp_swidget->comp_id;

	dev_dbg(scomp->dev, "tplg: pipeline id %d comp %d scheduling comp id %d\n",
		pipeline->pipeline_id, pipeline->comp_id, pipeline->sched_id);

	ret = sof_parse_tokens(scomp, pipeline, sched_tokens,
			       ARRAY_SIZE(sched_tokens), निजी->array,
			       le32_to_cpu(निजी->size));
	अगर (ret != 0) अणु
		dev_err(scomp->dev, "error: parse pipeline tokens failed %d\n",
			निजी->size);
		जाओ err;
	पूर्ण

	dev_dbg(scomp->dev, "pipeline %s: period %d pri %d mips %d core %d frames %d\n",
		swidget->widget->name, pipeline->period, pipeline->priority,
		pipeline->period_mips, pipeline->core, pipeline->frames_per_sched);

	swidget->निजी = pipeline;

	/* send ipc's to create pipeline comp and घातer up schedule core */
	ret = sof_load_pipeline_ipc(scomp->dev, pipeline, r);
	अगर (ret >= 0)
		वापस ret;
err:
	kमुक्त(pipeline);
	वापस ret;
पूर्ण

/*
 * Mixer topology
 */

अटल पूर्णांक sof_widget_load_mixer(काष्ठा snd_soc_component *scomp, पूर्णांक index,
				 काष्ठा snd_sof_widget *swidget,
				 काष्ठा snd_soc_tplg_dapm_widget *tw,
				 काष्ठा sof_ipc_comp_reply *r)
अणु
	काष्ठा snd_sof_dev *sdev = snd_soc_component_get_drvdata(scomp);
	काष्ठा snd_soc_tplg_निजी *निजी = &tw->priv;
	काष्ठा sof_ipc_comp_mixer *mixer;
	माप_प्रकार ipc_size = माप(*mixer);
	पूर्णांक ret;

	mixer = (काष्ठा sof_ipc_comp_mixer *)
		sof_comp_alloc(swidget, &ipc_size, index);
	अगर (!mixer)
		वापस -ENOMEM;

	/* configure mixer IPC message */
	mixer->comp.type = SOF_COMP_MIXER;
	mixer->config.hdr.size = माप(mixer->config);

	ret = sof_parse_tokens(scomp, &mixer->config, comp_tokens,
			       ARRAY_SIZE(comp_tokens), निजी->array,
			       le32_to_cpu(निजी->size));
	अगर (ret != 0) अणु
		dev_err(scomp->dev, "error: parse mixer.cfg tokens failed %d\n",
			निजी->size);
		kमुक्त(mixer);
		वापस ret;
	पूर्ण

	sof_dbg_comp_config(scomp, &mixer->config);

	swidget->निजी = mixer;

	ret = sof_ipc_tx_message(sdev->ipc, mixer->comp.hdr.cmd, mixer,
				 ipc_size, r, माप(*r));
	अगर (ret < 0)
		kमुक्त(mixer);

	वापस ret;
पूर्ण

/*
 * Mux topology
 */
अटल पूर्णांक sof_widget_load_mux(काष्ठा snd_soc_component *scomp, पूर्णांक index,
			       काष्ठा snd_sof_widget *swidget,
			       काष्ठा snd_soc_tplg_dapm_widget *tw,
			       काष्ठा sof_ipc_comp_reply *r)
अणु
	काष्ठा snd_sof_dev *sdev = snd_soc_component_get_drvdata(scomp);
	काष्ठा snd_soc_tplg_निजी *निजी = &tw->priv;
	काष्ठा sof_ipc_comp_mux *mux;
	माप_प्रकार ipc_size = माप(*mux);
	पूर्णांक ret;

	mux = (काष्ठा sof_ipc_comp_mux *)
	      sof_comp_alloc(swidget, &ipc_size, index);
	अगर (!mux)
		वापस -ENOMEM;

	/* configure mux IPC message */
	mux->comp.type = SOF_COMP_MUX;
	mux->config.hdr.size = माप(mux->config);

	ret = sof_parse_tokens(scomp, &mux->config, comp_tokens,
			       ARRAY_SIZE(comp_tokens), निजी->array,
			       le32_to_cpu(निजी->size));
	अगर (ret != 0) अणु
		dev_err(scomp->dev, "error: parse mux.cfg tokens failed %d\n",
			निजी->size);
		kमुक्त(mux);
		वापस ret;
	पूर्ण

	sof_dbg_comp_config(scomp, &mux->config);

	swidget->निजी = mux;

	ret = sof_ipc_tx_message(sdev->ipc, mux->comp.hdr.cmd, mux,
				 ipc_size, r, माप(*r));
	अगर (ret < 0)
		kमुक्त(mux);

	वापस ret;
पूर्ण

/*
 * PGA Topology
 */

अटल पूर्णांक sof_widget_load_pga(काष्ठा snd_soc_component *scomp, पूर्णांक index,
			       काष्ठा snd_sof_widget *swidget,
			       काष्ठा snd_soc_tplg_dapm_widget *tw,
			       काष्ठा sof_ipc_comp_reply *r)
अणु
	काष्ठा snd_sof_dev *sdev = snd_soc_component_get_drvdata(scomp);
	काष्ठा snd_soc_tplg_निजी *निजी = &tw->priv;
	काष्ठा sof_ipc_comp_volume *volume;
	काष्ठा snd_sof_control *scontrol;
	माप_प्रकार ipc_size = माप(*volume);
	पूर्णांक min_step;
	पूर्णांक max_step;
	पूर्णांक ret;

	volume = (काष्ठा sof_ipc_comp_volume *)
		 sof_comp_alloc(swidget, &ipc_size, index);
	अगर (!volume)
		वापस -ENOMEM;

	अगर (!le32_to_cpu(tw->num_kcontrols)) अणु
		dev_err(scomp->dev, "error: invalid kcontrol count %d for volume\n",
			tw->num_kcontrols);
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	/* configure volume IPC message */
	volume->comp.type = SOF_COMP_VOLUME;
	volume->config.hdr.size = माप(volume->config);

	ret = sof_parse_tokens(scomp, volume, volume_tokens,
			       ARRAY_SIZE(volume_tokens), निजी->array,
			       le32_to_cpu(निजी->size));
	अगर (ret != 0) अणु
		dev_err(scomp->dev, "error: parse volume tokens failed %d\n",
			निजी->size);
		जाओ err;
	पूर्ण
	ret = sof_parse_tokens(scomp, &volume->config, comp_tokens,
			       ARRAY_SIZE(comp_tokens), निजी->array,
			       le32_to_cpu(निजी->size));
	अगर (ret != 0) अणु
		dev_err(scomp->dev, "error: parse volume.cfg tokens failed %d\n",
			le32_to_cpu(निजी->size));
		जाओ err;
	पूर्ण

	sof_dbg_comp_config(scomp, &volume->config);

	swidget->निजी = volume;

	list_क्रम_each_entry(scontrol, &sdev->kcontrol_list, list) अणु
		अगर (scontrol->comp_id == swidget->comp_id &&
		    scontrol->volume_table) अणु
			min_step = scontrol->min_volume_step;
			max_step = scontrol->max_volume_step;
			volume->min_value = scontrol->volume_table[min_step];
			volume->max_value = scontrol->volume_table[max_step];
			volume->channels = scontrol->num_channels;
			अवरोध;
		पूर्ण
	पूर्ण

	ret = sof_ipc_tx_message(sdev->ipc, volume->comp.hdr.cmd, volume,
				 ipc_size, r, माप(*r));
	अगर (ret >= 0)
		वापस ret;
err:
	kमुक्त(volume);
	वापस ret;
पूर्ण

/*
 * SRC Topology
 */

अटल पूर्णांक sof_widget_load_src(काष्ठा snd_soc_component *scomp, पूर्णांक index,
			       काष्ठा snd_sof_widget *swidget,
			       काष्ठा snd_soc_tplg_dapm_widget *tw,
			       काष्ठा sof_ipc_comp_reply *r)
अणु
	काष्ठा snd_sof_dev *sdev = snd_soc_component_get_drvdata(scomp);
	काष्ठा snd_soc_tplg_निजी *निजी = &tw->priv;
	काष्ठा sof_ipc_comp_src *src;
	माप_प्रकार ipc_size = माप(*src);
	पूर्णांक ret;

	src = (काष्ठा sof_ipc_comp_src *)
	      sof_comp_alloc(swidget, &ipc_size, index);
	अगर (!src)
		वापस -ENOMEM;

	/* configure src IPC message */
	src->comp.type = SOF_COMP_SRC;
	src->config.hdr.size = माप(src->config);

	ret = sof_parse_tokens(scomp, src, src_tokens,
			       ARRAY_SIZE(src_tokens), निजी->array,
			       le32_to_cpu(निजी->size));
	अगर (ret != 0) अणु
		dev_err(scomp->dev, "error: parse src tokens failed %d\n",
			निजी->size);
		जाओ err;
	पूर्ण

	ret = sof_parse_tokens(scomp, &src->config, comp_tokens,
			       ARRAY_SIZE(comp_tokens), निजी->array,
			       le32_to_cpu(निजी->size));
	अगर (ret != 0) अणु
		dev_err(scomp->dev, "error: parse src.cfg tokens failed %d\n",
			le32_to_cpu(निजी->size));
		जाओ err;
	पूर्ण

	dev_dbg(scomp->dev, "src %s: source rate %d sink rate %d\n",
		swidget->widget->name, src->source_rate, src->sink_rate);
	sof_dbg_comp_config(scomp, &src->config);

	swidget->निजी = src;

	ret = sof_ipc_tx_message(sdev->ipc, src->comp.hdr.cmd, src,
				 ipc_size, r, माप(*r));
	अगर (ret >= 0)
		वापस ret;
err:
	kमुक्त(src);
	वापस ret;
पूर्ण

/*
 * ASRC Topology
 */

अटल पूर्णांक sof_widget_load_asrc(काष्ठा snd_soc_component *scomp, पूर्णांक index,
				काष्ठा snd_sof_widget *swidget,
				काष्ठा snd_soc_tplg_dapm_widget *tw,
				काष्ठा sof_ipc_comp_reply *r)
अणु
	काष्ठा snd_sof_dev *sdev = snd_soc_component_get_drvdata(scomp);
	काष्ठा snd_soc_tplg_निजी *निजी = &tw->priv;
	काष्ठा sof_ipc_comp_asrc *asrc;
	माप_प्रकार ipc_size = माप(*asrc);
	पूर्णांक ret;

	asrc = (काष्ठा sof_ipc_comp_asrc *)
	       sof_comp_alloc(swidget, &ipc_size, index);
	अगर (!asrc)
		वापस -ENOMEM;

	/* configure ASRC IPC message */
	asrc->comp.type = SOF_COMP_ASRC;
	asrc->config.hdr.size = माप(asrc->config);

	ret = sof_parse_tokens(scomp, asrc, asrc_tokens,
			       ARRAY_SIZE(asrc_tokens), निजी->array,
			       le32_to_cpu(निजी->size));
	अगर (ret != 0) अणु
		dev_err(scomp->dev, "error: parse asrc tokens failed %d\n",
			निजी->size);
		जाओ err;
	पूर्ण

	ret = sof_parse_tokens(scomp, &asrc->config, comp_tokens,
			       ARRAY_SIZE(comp_tokens), निजी->array,
			       le32_to_cpu(निजी->size));
	अगर (ret != 0) अणु
		dev_err(scomp->dev, "error: parse asrc.cfg tokens failed %d\n",
			le32_to_cpu(निजी->size));
		जाओ err;
	पूर्ण

	dev_dbg(scomp->dev, "asrc %s: source rate %d sink rate %d "
		"asynch %d operation %d\n",
		swidget->widget->name, asrc->source_rate, asrc->sink_rate,
		asrc->asynchronous_mode, asrc->operation_mode);
	sof_dbg_comp_config(scomp, &asrc->config);

	swidget->निजी = asrc;

	ret = sof_ipc_tx_message(sdev->ipc, asrc->comp.hdr.cmd, asrc,
				 ipc_size, r, माप(*r));
	अगर (ret >= 0)
		वापस ret;
err:
	kमुक्त(asrc);
	वापस ret;
पूर्ण

/*
 * Signal Generator Topology
 */

अटल पूर्णांक sof_widget_load_siggen(काष्ठा snd_soc_component *scomp, पूर्णांक index,
				  काष्ठा snd_sof_widget *swidget,
				  काष्ठा snd_soc_tplg_dapm_widget *tw,
				  काष्ठा sof_ipc_comp_reply *r)
अणु
	काष्ठा snd_sof_dev *sdev = snd_soc_component_get_drvdata(scomp);
	काष्ठा snd_soc_tplg_निजी *निजी = &tw->priv;
	काष्ठा sof_ipc_comp_tone *tone;
	माप_प्रकार ipc_size = माप(*tone);
	पूर्णांक ret;

	tone = (काष्ठा sof_ipc_comp_tone *)
	       sof_comp_alloc(swidget, &ipc_size, index);
	अगर (!tone)
		वापस -ENOMEM;

	/* configure siggen IPC message */
	tone->comp.type = SOF_COMP_TONE;
	tone->config.hdr.size = माप(tone->config);

	ret = sof_parse_tokens(scomp, tone, tone_tokens,
			       ARRAY_SIZE(tone_tokens), निजी->array,
			       le32_to_cpu(निजी->size));
	अगर (ret != 0) अणु
		dev_err(scomp->dev, "error: parse tone tokens failed %d\n",
			le32_to_cpu(निजी->size));
		जाओ err;
	पूर्ण

	ret = sof_parse_tokens(scomp, &tone->config, comp_tokens,
			       ARRAY_SIZE(comp_tokens), निजी->array,
			       le32_to_cpu(निजी->size));
	अगर (ret != 0) अणु
		dev_err(scomp->dev, "error: parse tone.cfg tokens failed %d\n",
			le32_to_cpu(निजी->size));
		जाओ err;
	पूर्ण

	dev_dbg(scomp->dev, "tone %s: frequency %d amplitude %d\n",
		swidget->widget->name, tone->frequency, tone->amplitude);
	sof_dbg_comp_config(scomp, &tone->config);

	swidget->निजी = tone;

	ret = sof_ipc_tx_message(sdev->ipc, tone->comp.hdr.cmd, tone,
				 ipc_size, r, माप(*r));
	अगर (ret >= 0)
		वापस ret;
err:
	kमुक्त(tone);
	वापस ret;
पूर्ण

अटल पूर्णांक sof_get_control_data(काष्ठा snd_soc_component *scomp,
				काष्ठा snd_soc_dapm_widget *widget,
				काष्ठा sof_widget_data *wdata,
				माप_प्रकार *size)
अणु
	स्थिर काष्ठा snd_kcontrol_new *kc;
	काष्ठा soc_mixer_control *sm;
	काष्ठा soc_bytes_ext *sbe;
	काष्ठा soc_क्रमागत *se;
	पूर्णांक i;

	*size = 0;

	क्रम (i = 0; i < widget->num_kcontrols; i++) अणु
		kc = &widget->kcontrol_news[i];

		चयन (widget->करोbj.widget.kcontrol_type) अणु
		हाल SND_SOC_TPLG_TYPE_MIXER:
			sm = (काष्ठा soc_mixer_control *)kc->निजी_value;
			wdata[i].control = sm->करोbj.निजी;
			अवरोध;
		हाल SND_SOC_TPLG_TYPE_BYTES:
			sbe = (काष्ठा soc_bytes_ext *)kc->निजी_value;
			wdata[i].control = sbe->करोbj.निजी;
			अवरोध;
		हाल SND_SOC_TPLG_TYPE_ENUM:
			se = (काष्ठा soc_क्रमागत *)kc->निजी_value;
			wdata[i].control = se->करोbj.निजी;
			अवरोध;
		शेष:
			dev_err(scomp->dev, "error: unknown kcontrol type %d in widget %s\n",
				widget->करोbj.widget.kcontrol_type,
				widget->name);
			वापस -EINVAL;
		पूर्ण

		अगर (!wdata[i].control) अणु
			dev_err(scomp->dev, "error: no scontrol for widget %s\n",
				widget->name);
			वापस -EINVAL;
		पूर्ण

		wdata[i].pdata = wdata[i].control->control_data->data;
		अगर (!wdata[i].pdata)
			वापस -EINVAL;

		/* make sure data is valid - data can be updated at runसमय */
		अगर (wdata[i].pdata->magic != SOF_ABI_MAGIC)
			वापस -EINVAL;

		*size += wdata[i].pdata->size;

		/* get data type */
		चयन (wdata[i].control->cmd) अणु
		हाल SOF_CTRL_CMD_VOLUME:
		हाल SOF_CTRL_CMD_ENUM:
		हाल SOF_CTRL_CMD_SWITCH:
			wdata[i].ipc_cmd = SOF_IPC_COMP_SET_VALUE;
			wdata[i].ctrl_type = SOF_CTRL_TYPE_VALUE_CHAN_SET;
			अवरोध;
		हाल SOF_CTRL_CMD_BINARY:
			wdata[i].ipc_cmd = SOF_IPC_COMP_SET_DATA;
			wdata[i].ctrl_type = SOF_CTRL_TYPE_DATA_SET;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sof_process_load(काष्ठा snd_soc_component *scomp, पूर्णांक index,
			    काष्ठा snd_sof_widget *swidget,
			    काष्ठा snd_soc_tplg_dapm_widget *tw,
			    काष्ठा sof_ipc_comp_reply *r,
			    पूर्णांक type)
अणु
	काष्ठा snd_sof_dev *sdev = snd_soc_component_get_drvdata(scomp);
	काष्ठा snd_soc_dapm_widget *widget = swidget->widget;
	काष्ठा snd_soc_tplg_निजी *निजी = &tw->priv;
	काष्ठा sof_ipc_comp_process *process;
	काष्ठा sof_widget_data *wdata = शून्य;
	माप_प्रकार ipc_data_size = 0;
	माप_प्रकार ipc_size;
	पूर्णांक offset = 0;
	पूर्णांक ret;
	पूर्णांक i;

	/* allocate काष्ठा क्रम widget control data sizes and types */
	अगर (widget->num_kcontrols) अणु
		wdata = kसुस्मृति(widget->num_kcontrols,
				माप(*wdata),
				GFP_KERNEL);

		अगर (!wdata)
			वापस -ENOMEM;

		/* get possible component controls and get size of all pdata */
		ret = sof_get_control_data(scomp, widget, wdata,
					   &ipc_data_size);

		अगर (ret < 0)
			जाओ out;
	पूर्ण

	ipc_size = माप(काष्ठा sof_ipc_comp_process) + ipc_data_size;

	/* we are exceeding max ipc size, config needs to be sent separately */
	अगर (ipc_size > SOF_IPC_MSG_MAX_SIZE) अणु
		ipc_size -= ipc_data_size;
		ipc_data_size = 0;
	पूर्ण

	process = (काष्ठा sof_ipc_comp_process *)
		  sof_comp_alloc(swidget, &ipc_size, index);
	अगर (!process) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	/* configure iir IPC message */
	process->comp.type = type;
	process->config.hdr.size = माप(process->config);

	ret = sof_parse_tokens(scomp, &process->config, comp_tokens,
			       ARRAY_SIZE(comp_tokens), निजी->array,
			       le32_to_cpu(निजी->size));
	अगर (ret != 0) अणु
		dev_err(scomp->dev, "error: parse process.cfg tokens failed %d\n",
			le32_to_cpu(निजी->size));
		जाओ err;
	पूर्ण

	sof_dbg_comp_config(scomp, &process->config);

	/*
	 * found निजी data in control, so copy it.
	 * get possible component controls - get size of all pdata,
	 * then स_नकल with headers
	 */
	अगर (ipc_data_size) अणु
		क्रम (i = 0; i < widget->num_kcontrols; i++) अणु
			स_नकल(&process->data + offset,
			       wdata[i].pdata->data,
			       wdata[i].pdata->size);
			offset += wdata[i].pdata->size;
		पूर्ण
	पूर्ण

	process->size = ipc_data_size;
	swidget->निजी = process;

	ret = sof_ipc_tx_message(sdev->ipc, process->comp.hdr.cmd, process,
				 ipc_size, r, माप(*r));

	अगर (ret < 0) अणु
		dev_err(scomp->dev, "error: create process failed\n");
		जाओ err;
	पूर्ण

	/* we sent the data in single message so वापस */
	अगर (ipc_data_size)
		जाओ out;

	/* send control data with large message supported method */
	क्रम (i = 0; i < widget->num_kcontrols; i++) अणु
		wdata[i].control->पढ़ोback_offset = 0;
		ret = snd_sof_ipc_set_get_comp_data(wdata[i].control,
						    wdata[i].ipc_cmd,
						    wdata[i].ctrl_type,
						    wdata[i].control->cmd,
						    true);
		अगर (ret != 0) अणु
			dev_err(scomp->dev, "error: send control failed\n");
			अवरोध;
		पूर्ण
	पूर्ण

err:
	अगर (ret < 0)
		kमुक्त(process);
out:
	kमुक्त(wdata);
	वापस ret;
पूर्ण

/*
 * Processing Component Topology - can be "effect", "codec", or general
 * "processing".
 */

अटल पूर्णांक sof_widget_load_process(काष्ठा snd_soc_component *scomp, पूर्णांक index,
				   काष्ठा snd_sof_widget *swidget,
				   काष्ठा snd_soc_tplg_dapm_widget *tw,
				   काष्ठा sof_ipc_comp_reply *r)
अणु
	काष्ठा snd_soc_tplg_निजी *निजी = &tw->priv;
	काष्ठा sof_ipc_comp_process config;
	पूर्णांक ret;

	/* check we have some tokens - we need at least process type */
	अगर (le32_to_cpu(निजी->size) == 0) अणु
		dev_err(scomp->dev, "error: process tokens not found\n");
		वापस -EINVAL;
	पूर्ण

	स_रखो(&config, 0, माप(config));
	config.comp.core = swidget->core;

	/* get the process token */
	ret = sof_parse_tokens(scomp, &config, process_tokens,
			       ARRAY_SIZE(process_tokens), निजी->array,
			       le32_to_cpu(निजी->size));
	अगर (ret != 0) अणु
		dev_err(scomp->dev, "error: parse process tokens failed %d\n",
			le32_to_cpu(निजी->size));
		वापस ret;
	पूर्ण

	/* now load process specअगरic data and send IPC */
	ret = sof_process_load(scomp, index, swidget, tw, r,
			       find_process_comp_type(config.type));
	अगर (ret < 0) अणु
		dev_err(scomp->dev, "error: process loading failed\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sof_widget_bind_event(काष्ठा snd_soc_component *scomp,
				 काष्ठा snd_sof_widget *swidget,
				 u16 event_type)
अणु
	काष्ठा sof_ipc_comp *ipc_comp;

	/* validate widget event type */
	चयन (event_type) अणु
	हाल SOF_KEYWORD_DETECT_DAPM_EVENT:
		/* only KEYWORD_DETECT comps should handle this */
		अगर (swidget->id != snd_soc_dapm_effect)
			अवरोध;

		ipc_comp = swidget->निजी;
		अगर (ipc_comp && ipc_comp->type != SOF_COMP_KEYWORD_DETECT)
			अवरोध;

		/* bind event to keyword detect comp */
		वापस snd_soc_tplg_widget_bind_event(swidget->widget,
						      sof_kwd_events,
						      ARRAY_SIZE(sof_kwd_events),
						      event_type);
	शेष:
		अवरोध;
	पूर्ण

	dev_err(scomp->dev,
		"error: invalid event type %d for widget %s\n",
		event_type, swidget->widget->name);
	वापस -EINVAL;
पूर्ण

/* बाह्यal widget init - used क्रम any driver specअगरic init */
अटल पूर्णांक sof_widget_पढ़ोy(काष्ठा snd_soc_component *scomp, पूर्णांक index,
			    काष्ठा snd_soc_dapm_widget *w,
			    काष्ठा snd_soc_tplg_dapm_widget *tw)
अणु
	काष्ठा snd_sof_dev *sdev = snd_soc_component_get_drvdata(scomp);
	काष्ठा snd_sof_widget *swidget;
	काष्ठा snd_sof_dai *dai;
	काष्ठा sof_ipc_comp_reply reply;
	काष्ठा snd_sof_control *scontrol;
	काष्ठा sof_ipc_comp comp = अणु
		.core = SOF_DSP_PRIMARY_CORE,
	पूर्ण;
	पूर्णांक ret = 0;

	swidget = kzalloc(माप(*swidget), GFP_KERNEL);
	अगर (!swidget)
		वापस -ENOMEM;

	swidget->scomp = scomp;
	swidget->widget = w;
	swidget->comp_id = sdev->next_comp_id++;
	swidget->complete = 0;
	swidget->id = w->id;
	swidget->pipeline_id = index;
	swidget->निजी = शून्य;
	स_रखो(&reply, 0, माप(reply));

	dev_dbg(scomp->dev, "tplg: ready widget id %d pipe %d type %d name : %s stream %s\n",
		swidget->comp_id, index, swidget->id, tw->name,
		strnlen(tw->sname, SNDRV_CTL_ELEM_ID_NAME_MAXLEN) > 0
			? tw->sname : "none");

	ret = sof_parse_tokens(scomp, &comp, core_tokens,
			       ARRAY_SIZE(core_tokens), tw->priv.array,
			       le32_to_cpu(tw->priv.size));
	अगर (ret != 0) अणु
		dev_err(scomp->dev, "error: parsing core tokens failed %d\n",
			ret);
		kमुक्त(swidget);
		वापस ret;
	पूर्ण

	swidget->core = comp.core;

	/* शेष is primary core, safe to call क्रम alपढ़ोy enabled cores */
	ret = sof_core_enable(sdev, comp.core);
	अगर (ret < 0) अणु
		dev_err(scomp->dev, "error: enable core: %d\n", ret);
		kमुक्त(swidget);
		वापस ret;
	पूर्ण

	ret = sof_parse_tokens(scomp, &swidget->comp_ext, comp_ext_tokens,
			       ARRAY_SIZE(comp_ext_tokens), tw->priv.array,
			       le32_to_cpu(tw->priv.size));
	अगर (ret != 0) अणु
		dev_err(scomp->dev, "error: parsing comp_ext_tokens failed %d\n",
			ret);
		kमुक्त(swidget);
		वापस ret;
	पूर्ण

	/* handle any special हाल widमाला_लो */
	चयन (w->id) अणु
	हाल snd_soc_dapm_dai_in:
	हाल snd_soc_dapm_dai_out:
		dai = kzalloc(माप(*dai), GFP_KERNEL);
		अगर (!dai) अणु
			kमुक्त(swidget);
			वापस -ENOMEM;
		पूर्ण

		ret = sof_widget_load_dai(scomp, index, swidget, tw, &reply, dai);
		अगर (ret == 0) अणु
			sof_connect_dai_widget(scomp, w, tw, dai);
			list_add(&dai->list, &sdev->dai_list);
			swidget->निजी = dai;
		पूर्ण अन्यथा अणु
			kमुक्त(dai);
		पूर्ण
		अवरोध;
	हाल snd_soc_dapm_mixer:
		ret = sof_widget_load_mixer(scomp, index, swidget, tw, &reply);
		अवरोध;
	हाल snd_soc_dapm_pga:
		ret = sof_widget_load_pga(scomp, index, swidget, tw, &reply);
		/* Find scontrol क्रम this pga and set पढ़ोback offset*/
		list_क्रम_each_entry(scontrol, &sdev->kcontrol_list, list) अणु
			अगर (scontrol->comp_id == swidget->comp_id) अणु
				scontrol->पढ़ोback_offset = reply.offset;
				अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल snd_soc_dapm_buffer:
		ret = sof_widget_load_buffer(scomp, index, swidget, tw, &reply);
		अवरोध;
	हाल snd_soc_dapm_scheduler:
		ret = sof_widget_load_pipeline(scomp, index, swidget, tw, &reply);
		अवरोध;
	हाल snd_soc_dapm_aअगर_out:
		ret = sof_widget_load_pcm(scomp, index, swidget,
					  SOF_IPC_STREAM_CAPTURE, tw, &reply);
		अवरोध;
	हाल snd_soc_dapm_aअगर_in:
		ret = sof_widget_load_pcm(scomp, index, swidget,
					  SOF_IPC_STREAM_PLAYBACK, tw, &reply);
		अवरोध;
	हाल snd_soc_dapm_src:
		ret = sof_widget_load_src(scomp, index, swidget, tw, &reply);
		अवरोध;
	हाल snd_soc_dapm_asrc:
		ret = sof_widget_load_asrc(scomp, index, swidget, tw, &reply);
		अवरोध;
	हाल snd_soc_dapm_siggen:
		ret = sof_widget_load_siggen(scomp, index, swidget, tw, &reply);
		अवरोध;
	हाल snd_soc_dapm_effect:
		ret = sof_widget_load_process(scomp, index, swidget, tw, &reply);
		अवरोध;
	हाल snd_soc_dapm_mux:
	हाल snd_soc_dapm_demux:
		ret = sof_widget_load_mux(scomp, index, swidget, tw, &reply);
		अवरोध;
	हाल snd_soc_dapm_चयन:
	हाल snd_soc_dapm_dai_link:
	हाल snd_soc_dapm_kcontrol:
	शेष:
		dev_dbg(scomp->dev, "widget type %d name %s not handled\n", swidget->id, tw->name);
		अवरोध;
	पूर्ण

	/* check IPC reply */
	अगर (ret < 0 || reply.rhdr.error < 0) अणु
		dev_err(scomp->dev,
			"error: DSP failed to add widget id %d type %d name : %s stream %s reply %d\n",
			tw->shअगरt, swidget->id, tw->name,
			strnlen(tw->sname, SNDRV_CTL_ELEM_ID_NAME_MAXLEN) > 0
				? tw->sname : "none", reply.rhdr.error);
		kमुक्त(swidget);
		वापस ret;
	पूर्ण

	/* bind widget to बाह्यal event */
	अगर (tw->event_type) अणु
		ret = sof_widget_bind_event(scomp, swidget,
					    le16_to_cpu(tw->event_type));
		अगर (ret) अणु
			dev_err(scomp->dev, "error: widget event binding failed\n");
			kमुक्त(swidget->निजी);
			kमुक्त(swidget);
			वापस ret;
		पूर्ण
	पूर्ण

	w->करोbj.निजी = swidget;
	list_add(&swidget->list, &sdev->widget_list);
	वापस ret;
पूर्ण

अटल पूर्णांक sof_route_unload(काष्ठा snd_soc_component *scomp,
			    काष्ठा snd_soc_करोbj *करोbj)
अणु
	काष्ठा snd_sof_route *sroute;

	sroute = करोbj->निजी;
	अगर (!sroute)
		वापस 0;

	/* मुक्त sroute and its निजी data */
	kमुक्त(sroute->निजी);
	list_del(&sroute->list);
	kमुक्त(sroute);

	वापस 0;
पूर्ण

अटल पूर्णांक sof_widget_unload(काष्ठा snd_soc_component *scomp,
			     काष्ठा snd_soc_करोbj *करोbj)
अणु
	काष्ठा snd_sof_dev *sdev = snd_soc_component_get_drvdata(scomp);
	स्थिर काष्ठा snd_kcontrol_new *kc;
	काष्ठा snd_soc_dapm_widget *widget;
	काष्ठा sof_ipc_pipe_new *pipeline;
	काष्ठा snd_sof_control *scontrol;
	काष्ठा snd_sof_widget *swidget;
	काष्ठा soc_mixer_control *sm;
	काष्ठा soc_bytes_ext *sbe;
	काष्ठा snd_sof_dai *dai;
	काष्ठा soc_क्रमागत *se;
	पूर्णांक ret = 0;
	पूर्णांक i;

	swidget = करोbj->निजी;
	अगर (!swidget)
		वापस 0;

	widget = swidget->widget;

	चयन (swidget->id) अणु
	हाल snd_soc_dapm_dai_in:
	हाल snd_soc_dapm_dai_out:
		dai = swidget->निजी;

		अगर (dai) अणु
			/* मुक्त dai config */
			kमुक्त(dai->dai_config);
			list_del(&dai->list);
		पूर्ण
		अवरोध;
	हाल snd_soc_dapm_scheduler:

		/* घातer करोwn the pipeline schedule core */
		pipeline = swidget->निजी;
		ret = snd_sof_dsp_core_घातer_करोwn(sdev, 1 << pipeline->core);
		अगर (ret < 0)
			dev_err(scomp->dev, "error: powering down pipeline schedule core %d\n",
				pipeline->core);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	क्रम (i = 0; i < widget->num_kcontrols; i++) अणु
		kc = &widget->kcontrol_news[i];
		चयन (करोbj->widget.kcontrol_type) अणु
		हाल SND_SOC_TPLG_TYPE_MIXER:
			sm = (काष्ठा soc_mixer_control *)kc->निजी_value;
			scontrol = sm->करोbj.निजी;
			अगर (sm->max > 1)
				kमुक्त(scontrol->volume_table);
			अवरोध;
		हाल SND_SOC_TPLG_TYPE_ENUM:
			se = (काष्ठा soc_क्रमागत *)kc->निजी_value;
			scontrol = se->करोbj.निजी;
			अवरोध;
		हाल SND_SOC_TPLG_TYPE_BYTES:
			sbe = (काष्ठा soc_bytes_ext *)kc->निजी_value;
			scontrol = sbe->करोbj.निजी;
			अवरोध;
		शेष:
			dev_warn(scomp->dev, "unsupported kcontrol_type\n");
			जाओ out;
		पूर्ण
		kमुक्त(scontrol->control_data);
		list_del(&scontrol->list);
		kमुक्त(scontrol);
	पूर्ण

out:
	/* मुक्त निजी value */
	kमुक्त(swidget->निजी);

	/* हटाओ and मुक्त swidget object */
	list_del(&swidget->list);
	kमुक्त(swidget);

	वापस ret;
पूर्ण

/*
 * DAI HW configuration.
 */

/* FE DAI - used क्रम any driver specअगरic init */
अटल पूर्णांक sof_dai_load(काष्ठा snd_soc_component *scomp, पूर्णांक index,
			काष्ठा snd_soc_dai_driver *dai_drv,
			काष्ठा snd_soc_tplg_pcm *pcm, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_sof_dev *sdev = snd_soc_component_get_drvdata(scomp);
	काष्ठा snd_soc_tplg_stream_caps *caps;
	काष्ठा snd_soc_tplg_निजी *निजी = &pcm->priv;
	काष्ठा snd_sof_pcm *spcm;
	पूर्णांक stream;
	पूर्णांक ret;

	/* nothing to करो क्रम BEs aपंचांग */
	अगर (!pcm)
		वापस 0;

	spcm = kzalloc(माप(*spcm), GFP_KERNEL);
	अगर (!spcm)
		वापस -ENOMEM;

	spcm->scomp = scomp;

	क्रम_each_pcm_streams(stream) अणु
		spcm->stream[stream].comp_id = COMP_ID_UNASSIGNED;
		INIT_WORK(&spcm->stream[stream].period_elapsed_work,
			  snd_sof_pcm_period_elapsed_work);
	पूर्ण

	spcm->pcm = *pcm;
	dev_dbg(scomp->dev, "tplg: load pcm %s\n", pcm->dai_name);

	dai_drv->करोbj.निजी = spcm;
	list_add(&spcm->list, &sdev->pcm_list);

	ret = sof_parse_tokens(scomp, spcm, stream_tokens,
			       ARRAY_SIZE(stream_tokens), निजी->array,
			       le32_to_cpu(निजी->size));
	अगर (ret) अणु
		dev_err(scomp->dev, "error: parse stream tokens failed %d\n",
			le32_to_cpu(निजी->size));
		वापस ret;
	पूर्ण

	/* करो we need to allocate playback PCM DMA pages */
	अगर (!spcm->pcm.playback)
		जाओ capture;

	stream = SNDRV_PCM_STREAM_PLAYBACK;

	dev_vdbg(scomp->dev, "tplg: pcm %s stream tokens: playback d0i3:%d\n",
		 spcm->pcm.pcm_name, spcm->stream[stream].d0i3_compatible);

	caps = &spcm->pcm.caps[stream];

	/* allocate playback page table buffer */
	ret = snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV, sdev->dev,
				  PAGE_SIZE, &spcm->stream[stream].page_table);
	अगर (ret < 0) अणु
		dev_err(scomp->dev, "error: can't alloc page table for %s %d\n",
			caps->name, ret);

		वापस ret;
	पूर्ण

	/* bind pcm to host comp */
	ret = spcm_bind(scomp, spcm, stream);
	अगर (ret) अणु
		dev_err(scomp->dev,
			"error: can't bind pcm to host\n");
		जाओ मुक्त_playback_tables;
	पूर्ण

capture:
	stream = SNDRV_PCM_STREAM_CAPTURE;

	/* करो we need to allocate capture PCM DMA pages */
	अगर (!spcm->pcm.capture)
		वापस ret;

	dev_vdbg(scomp->dev, "tplg: pcm %s stream tokens: capture d0i3:%d\n",
		 spcm->pcm.pcm_name, spcm->stream[stream].d0i3_compatible);

	caps = &spcm->pcm.caps[stream];

	/* allocate capture page table buffer */
	ret = snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV, sdev->dev,
				  PAGE_SIZE, &spcm->stream[stream].page_table);
	अगर (ret < 0) अणु
		dev_err(scomp->dev, "error: can't alloc page table for %s %d\n",
			caps->name, ret);
		जाओ मुक्त_playback_tables;
	पूर्ण

	/* bind pcm to host comp */
	ret = spcm_bind(scomp, spcm, stream);
	अगर (ret) अणु
		dev_err(scomp->dev,
			"error: can't bind pcm to host\n");
		snd_dma_मुक्त_pages(&spcm->stream[stream].page_table);
		जाओ मुक्त_playback_tables;
	पूर्ण

	वापस ret;

मुक्त_playback_tables:
	अगर (spcm->pcm.playback)
		snd_dma_मुक्त_pages(&spcm->stream[SNDRV_PCM_STREAM_PLAYBACK].page_table);

	वापस ret;
पूर्ण

अटल पूर्णांक sof_dai_unload(काष्ठा snd_soc_component *scomp,
			  काष्ठा snd_soc_करोbj *करोbj)
अणु
	काष्ठा snd_sof_pcm *spcm = करोbj->निजी;

	/* मुक्त PCM DMA pages */
	अगर (spcm->pcm.playback)
		snd_dma_मुक्त_pages(&spcm->stream[SNDRV_PCM_STREAM_PLAYBACK].page_table);

	अगर (spcm->pcm.capture)
		snd_dma_मुक्त_pages(&spcm->stream[SNDRV_PCM_STREAM_CAPTURE].page_table);

	/* हटाओ from list and मुक्त spcm */
	list_del(&spcm->list);
	kमुक्त(spcm);

	वापस 0;
पूर्ण

अटल व्योम sof_dai_set_क्रमmat(काष्ठा snd_soc_tplg_hw_config *hw_config,
			       काष्ठा sof_ipc_dai_config *config)
अणु
	/* घड़ी directions wrt codec */
	अगर (hw_config->bclk_provider == SND_SOC_TPLG_BCLK_CP) अणु
		/* codec is bclk provider */
		अगर (hw_config->fsync_provider == SND_SOC_TPLG_FSYNC_CP)
			config->क्रमmat |= SOF_DAI_FMT_CBP_CFP;
		अन्यथा
			config->क्रमmat |= SOF_DAI_FMT_CBP_CFC;
	पूर्ण अन्यथा अणु
		/* codec is bclk consumer */
		अगर (hw_config->fsync_provider == SND_SOC_TPLG_FSYNC_CP)
			config->क्रमmat |= SOF_DAI_FMT_CBC_CFP;
		अन्यथा
			config->क्रमmat |= SOF_DAI_FMT_CBC_CFC;
	पूर्ण

	/* inverted घड़ीs ? */
	अगर (hw_config->invert_bclk) अणु
		अगर (hw_config->invert_fsync)
			config->क्रमmat |= SOF_DAI_FMT_IB_IF;
		अन्यथा
			config->क्रमmat |= SOF_DAI_FMT_IB_NF;
	पूर्ण अन्यथा अणु
		अगर (hw_config->invert_fsync)
			config->क्रमmat |= SOF_DAI_FMT_NB_IF;
		अन्यथा
			config->क्रमmat |= SOF_DAI_FMT_NB_NF;
	पूर्ण
पूर्ण

/*
 * Send IPC and set the same config क्रम all DAIs with name matching the link
 * name. Note that the function can only be used क्रम the हाल that all DAIs
 * have a common DAI config क्रम now.
 */
अटल पूर्णांक sof_set_dai_config_multi(काष्ठा snd_sof_dev *sdev, u32 size,
				    काष्ठा snd_soc_dai_link *link,
				    काष्ठा sof_ipc_dai_config *config,
				    पूर्णांक num_conf, पूर्णांक curr_conf)
अणु
	काष्ठा snd_sof_dai *dai;
	पूर्णांक found = 0;
	पूर्णांक i;

	list_क्रम_each_entry(dai, &sdev->dai_list, list) अणु
		अगर (!dai->name)
			जारी;

		अगर (म_भेद(link->name, dai->name) == 0) अणु
			काष्ठा sof_ipc_reply reply;
			पूर्णांक ret;

			/*
			 * the same dai config will be applied to all DAIs in
			 * the same dai link. We have to ensure that the ipc
			 * dai config's dai_index match to the component's
			 * dai_index.
			 */
			क्रम (i = 0; i < num_conf; i++)
				config[i].dai_index = dai->comp_dai.dai_index;

			dev_dbg(sdev->dev, "set DAI config for %s index %d\n",
				dai->name, config[curr_conf].dai_index);
			/* send message to DSP */
			ret = sof_ipc_tx_message(sdev->ipc,
						 config[curr_conf].hdr.cmd,
						 &config[curr_conf], size,
						 &reply, माप(reply));

			अगर (ret < 0) अणु
				dev_err(sdev->dev,
					"error: failed to set DAI config for %s index %d\n",
					dai->name, config[curr_conf].dai_index);
				वापस ret;
			पूर्ण

			dai->number_configs = num_conf;
			dai->current_config = curr_conf;
			dai->dai_config = kmemdup(config, size * num_conf, GFP_KERNEL);
			अगर (!dai->dai_config)
				वापस -ENOMEM;

			/* set cpu_dai_name */
			dai->cpu_dai_name = link->cpus->dai_name;

			found = 1;
		पूर्ण
	पूर्ण

	/*
	 * machine driver may define a dai link with playback and capture
	 * dai enabled, but the dai link in topology would support both, one
	 * or none of them. Here prपूर्णांक a warning message to notअगरy user
	 */
	अगर (!found) अणु
		dev_warn(sdev->dev, "warning: failed to find dai for dai link %s",
			 link->name);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sof_set_dai_config(काष्ठा snd_sof_dev *sdev, u32 size,
			      काष्ठा snd_soc_dai_link *link,
			      काष्ठा sof_ipc_dai_config *config)
अणु
	वापस sof_set_dai_config_multi(sdev, size, link, config, 1, 0);
पूर्ण

अटल पूर्णांक sof_link_ssp_load(काष्ठा snd_soc_component *scomp, पूर्णांक index,
			     काष्ठा snd_soc_dai_link *link,
			     काष्ठा snd_soc_tplg_link_config *cfg,
			     काष्ठा snd_soc_tplg_hw_config *hw_config,
			     काष्ठा sof_ipc_dai_config *config, पूर्णांक curr_conf)
अणु
	काष्ठा snd_sof_dev *sdev = snd_soc_component_get_drvdata(scomp);
	काष्ठा snd_soc_tplg_निजी *निजी = &cfg->priv;
	पूर्णांक num_conf = le32_to_cpu(cfg->num_hw_configs);
	u32 size = माप(*config);
	पूर्णांक ret;
	पूर्णांक i;

	/*
	 * Parse common data, we should have 1 common data per hw_config.
	 */
	ret = sof_parse_token_sets(scomp, &config->ssp, ssp_tokens,
				   ARRAY_SIZE(ssp_tokens), निजी->array,
				   le32_to_cpu(निजी->size),
				   num_conf, size);

	अगर (ret != 0) अणु
		dev_err(scomp->dev, "error: parse ssp tokens failed %d\n",
			le32_to_cpu(निजी->size));
		वापस ret;
	पूर्ण

	/* process all possible hw configs */
	क्रम (i = 0; i < num_conf; i++) अणु

		/* handle master/slave and inverted घड़ीs */
		sof_dai_set_क्रमmat(&hw_config[i], &config[i]);

		config[i].hdr.size = size;

		/* copy dअगरferentiating hw configs to ipc काष्ठाs */
		config[i].ssp.mclk_rate = le32_to_cpu(hw_config[i].mclk_rate);
		config[i].ssp.bclk_rate = le32_to_cpu(hw_config[i].bclk_rate);
		config[i].ssp.fsync_rate = le32_to_cpu(hw_config[i].fsync_rate);
		config[i].ssp.tdm_slots = le32_to_cpu(hw_config[i].tdm_slots);
		config[i].ssp.tdm_slot_width = le32_to_cpu(hw_config[i].tdm_slot_width);
		config[i].ssp.mclk_direction = hw_config[i].mclk_direction;
		config[i].ssp.rx_slots = le32_to_cpu(hw_config[i].rx_slots);
		config[i].ssp.tx_slots = le32_to_cpu(hw_config[i].tx_slots);

		dev_dbg(scomp->dev, "tplg: config SSP%d fmt 0x%x mclk %d bclk %d fclk %d width (%d)%d slots %d mclk id %d quirks %d\n",
			config[i].dai_index, config[i].क्रमmat,
			config[i].ssp.mclk_rate, config[i].ssp.bclk_rate,
			config[i].ssp.fsync_rate, config[i].ssp.sample_valid_bits,
			config[i].ssp.tdm_slot_width, config[i].ssp.tdm_slots,
			config[i].ssp.mclk_id, config[i].ssp.quirks);

		/* validate SSP fsync rate and channel count */
		अगर (config[i].ssp.fsync_rate < 8000 || config[i].ssp.fsync_rate > 192000) अणु
			dev_err(scomp->dev, "error: invalid fsync rate for SSP%d\n",
				config[i].dai_index);
			वापस -EINVAL;
		पूर्ण

		अगर (config[i].ssp.tdm_slots < 1 || config[i].ssp.tdm_slots > 8) अणु
			dev_err(scomp->dev, "error: invalid channel count for SSP%d\n",
				config[i].dai_index);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* set config क्रम all DAI's with name matching the link name */
	ret = sof_set_dai_config_multi(sdev, size, link, config, num_conf, curr_conf);
	अगर (ret < 0)
		dev_err(scomp->dev, "error: failed to save DAI config for SSP%d\n",
			config->dai_index);

	वापस ret;
पूर्ण

अटल पूर्णांक sof_link_sai_load(काष्ठा snd_soc_component *scomp, पूर्णांक index,
			     काष्ठा snd_soc_dai_link *link,
			     काष्ठा snd_soc_tplg_link_config *cfg,
			     काष्ठा snd_soc_tplg_hw_config *hw_config,
			     काष्ठा sof_ipc_dai_config *config)
अणु
	काष्ठा snd_sof_dev *sdev = snd_soc_component_get_drvdata(scomp);
	काष्ठा snd_soc_tplg_निजी *निजी = &cfg->priv;
	u32 size = माप(*config);
	पूर्णांक ret;

	/* handle master/slave and inverted घड़ीs */
	sof_dai_set_क्रमmat(hw_config, config);

	/* init IPC */
	स_रखो(&config->sai, 0, माप(काष्ठा sof_ipc_dai_sai_params));
	config->hdr.size = size;

	ret = sof_parse_tokens(scomp, &config->sai, sai_tokens,
			       ARRAY_SIZE(sai_tokens), निजी->array,
			       le32_to_cpu(निजी->size));
	अगर (ret != 0) अणु
		dev_err(scomp->dev, "error: parse sai tokens failed %d\n",
			le32_to_cpu(निजी->size));
		वापस ret;
	पूर्ण

	config->sai.mclk_rate = le32_to_cpu(hw_config->mclk_rate);
	config->sai.bclk_rate = le32_to_cpu(hw_config->bclk_rate);
	config->sai.fsync_rate = le32_to_cpu(hw_config->fsync_rate);
	config->sai.mclk_direction = hw_config->mclk_direction;

	config->sai.tdm_slots = le32_to_cpu(hw_config->tdm_slots);
	config->sai.tdm_slot_width = le32_to_cpu(hw_config->tdm_slot_width);
	config->sai.rx_slots = le32_to_cpu(hw_config->rx_slots);
	config->sai.tx_slots = le32_to_cpu(hw_config->tx_slots);

	dev_info(scomp->dev,
		 "tplg: config SAI%d fmt 0x%x mclk %d width %d slots %d mclk id %d\n",
		config->dai_index, config->क्रमmat,
		config->sai.mclk_rate, config->sai.tdm_slot_width,
		config->sai.tdm_slots, config->sai.mclk_id);

	अगर (config->sai.tdm_slots < 1 || config->sai.tdm_slots > 8) अणु
		dev_err(scomp->dev, "error: invalid channel count for SAI%d\n",
			config->dai_index);
		वापस -EINVAL;
	पूर्ण

	/* set config क्रम all DAI's with name matching the link name */
	ret = sof_set_dai_config(sdev, size, link, config);
	अगर (ret < 0)
		dev_err(scomp->dev, "error: failed to save DAI config for SAI%d\n",
			config->dai_index);

	वापस ret;
पूर्ण

अटल पूर्णांक sof_link_esai_load(काष्ठा snd_soc_component *scomp, पूर्णांक index,
			      काष्ठा snd_soc_dai_link *link,
			      काष्ठा snd_soc_tplg_link_config *cfg,
			      काष्ठा snd_soc_tplg_hw_config *hw_config,
			      काष्ठा sof_ipc_dai_config *config)
अणु
	काष्ठा snd_sof_dev *sdev = snd_soc_component_get_drvdata(scomp);
	काष्ठा snd_soc_tplg_निजी *निजी = &cfg->priv;
	u32 size = माप(*config);
	पूर्णांक ret;

	/* handle master/slave and inverted घड़ीs */
	sof_dai_set_क्रमmat(hw_config, config);

	/* init IPC */
	स_रखो(&config->esai, 0, माप(काष्ठा sof_ipc_dai_esai_params));
	config->hdr.size = size;

	ret = sof_parse_tokens(scomp, &config->esai, esai_tokens,
			       ARRAY_SIZE(esai_tokens), निजी->array,
			       le32_to_cpu(निजी->size));
	अगर (ret != 0) अणु
		dev_err(scomp->dev, "error: parse esai tokens failed %d\n",
			le32_to_cpu(निजी->size));
		वापस ret;
	पूर्ण

	config->esai.mclk_rate = le32_to_cpu(hw_config->mclk_rate);
	config->esai.bclk_rate = le32_to_cpu(hw_config->bclk_rate);
	config->esai.fsync_rate = le32_to_cpu(hw_config->fsync_rate);
	config->esai.mclk_direction = hw_config->mclk_direction;
	config->esai.tdm_slots = le32_to_cpu(hw_config->tdm_slots);
	config->esai.tdm_slot_width = le32_to_cpu(hw_config->tdm_slot_width);
	config->esai.rx_slots = le32_to_cpu(hw_config->rx_slots);
	config->esai.tx_slots = le32_to_cpu(hw_config->tx_slots);

	dev_info(scomp->dev,
		 "tplg: config ESAI%d fmt 0x%x mclk %d width %d slots %d mclk id %d\n",
		config->dai_index, config->क्रमmat,
		config->esai.mclk_rate, config->esai.tdm_slot_width,
		config->esai.tdm_slots, config->esai.mclk_id);

	अगर (config->esai.tdm_slots < 1 || config->esai.tdm_slots > 8) अणु
		dev_err(scomp->dev, "error: invalid channel count for ESAI%d\n",
			config->dai_index);
		वापस -EINVAL;
	पूर्ण

	/* set config क्रम all DAI's with name matching the link name */
	ret = sof_set_dai_config(sdev, size, link, config);
	अगर (ret < 0)
		dev_err(scomp->dev, "error: failed to save DAI config for ESAI%d\n",
			config->dai_index);

	वापस ret;
पूर्ण

अटल पूर्णांक sof_link_dmic_load(काष्ठा snd_soc_component *scomp, पूर्णांक index,
			      काष्ठा snd_soc_dai_link *link,
			      काष्ठा snd_soc_tplg_link_config *cfg,
			      काष्ठा snd_soc_tplg_hw_config *hw_config,
			      काष्ठा sof_ipc_dai_config *config)
अणु
	काष्ठा snd_sof_dev *sdev = snd_soc_component_get_drvdata(scomp);
	काष्ठा snd_soc_tplg_निजी *निजी = &cfg->priv;
	काष्ठा sof_ipc_fw_पढ़ोy *पढ़ोy = &sdev->fw_पढ़ोy;
	काष्ठा sof_ipc_fw_version *v = &पढ़ोy->version;
	माप_प्रकार size = माप(*config);
	पूर्णांक ret, j;

	/* Ensure the entire DMIC config काष्ठा is zeros */
	स_रखो(&config->dmic, 0, माप(काष्ठा sof_ipc_dai_dmic_params));

	/* get DMIC tokens */
	ret = sof_parse_tokens(scomp, &config->dmic, dmic_tokens,
			       ARRAY_SIZE(dmic_tokens), निजी->array,
			       le32_to_cpu(निजी->size));
	अगर (ret != 0) अणु
		dev_err(scomp->dev, "error: parse dmic tokens failed %d\n",
			le32_to_cpu(निजी->size));
		वापस ret;
	पूर्ण

	/* get DMIC PDM tokens */
	ret = sof_parse_token_sets(scomp, &config->dmic.pdm[0], dmic_pdm_tokens,
			       ARRAY_SIZE(dmic_pdm_tokens), निजी->array,
			       le32_to_cpu(निजी->size),
			       config->dmic.num_pdm_active,
			       माप(काष्ठा sof_ipc_dai_dmic_pdm_ctrl));

	अगर (ret != 0) अणु
		dev_err(scomp->dev, "error: parse dmic pdm tokens failed %d\n",
			le32_to_cpu(निजी->size));
		वापस ret;
	पूर्ण

	/* set IPC header size */
	config->hdr.size = size;

	/* debug messages */
	dev_dbg(scomp->dev, "tplg: config DMIC%d driver version %d\n",
		config->dai_index, config->dmic.driver_ipc_version);
	dev_dbg(scomp->dev, "pdmclk_min %d pdm_clkmax %d duty_min %hd\n",
		config->dmic.pdmclk_min, config->dmic.pdmclk_max,
		config->dmic.duty_min);
	dev_dbg(scomp->dev, "duty_max %hd fifo_fs %d num_pdms active %d\n",
		config->dmic.duty_max, config->dmic.fअगरo_fs,
		config->dmic.num_pdm_active);
	dev_dbg(scomp->dev, "fifo word length %hd\n", config->dmic.fअगरo_bits);

	क्रम (j = 0; j < config->dmic.num_pdm_active; j++) अणु
		dev_dbg(scomp->dev, "pdm %hd mic a %hd mic b %hd\n",
			config->dmic.pdm[j].id,
			config->dmic.pdm[j].enable_mic_a,
			config->dmic.pdm[j].enable_mic_b);
		dev_dbg(scomp->dev, "pdm %hd polarity a %hd polarity b %hd\n",
			config->dmic.pdm[j].id,
			config->dmic.pdm[j].polarity_mic_a,
			config->dmic.pdm[j].polarity_mic_b);
		dev_dbg(scomp->dev, "pdm %hd clk_edge %hd skew %hd\n",
			config->dmic.pdm[j].id,
			config->dmic.pdm[j].clk_edge,
			config->dmic.pdm[j].skew);
	पूर्ण

	/*
	 * this takes care of backwards compatible handling of fअगरo_bits_b.
	 * It is deprecated since firmware ABI version 3.0.1.
	 */
	अगर (SOF_ABI_VER(v->major, v->minor, v->micro) < SOF_ABI_VER(3, 0, 1))
		config->dmic.fअगरo_bits_b = config->dmic.fअगरo_bits;

	/* set config क्रम all DAI's with name matching the link name */
	ret = sof_set_dai_config(sdev, size, link, config);
	अगर (ret < 0)
		dev_err(scomp->dev, "error: failed to save DAI config for DMIC%d\n",
			config->dai_index);

	वापस ret;
पूर्ण

अटल पूर्णांक sof_link_hda_load(काष्ठा snd_soc_component *scomp, पूर्णांक index,
			     काष्ठा snd_soc_dai_link *link,
			     काष्ठा snd_soc_tplg_link_config *cfg,
			     काष्ठा snd_soc_tplg_hw_config *hw_config,
			     काष्ठा sof_ipc_dai_config *config)
अणु
	काष्ठा snd_sof_dev *sdev = snd_soc_component_get_drvdata(scomp);
	काष्ठा snd_soc_tplg_निजी *निजी = &cfg->priv;
	काष्ठा snd_soc_dai *dai;
	u32 size = माप(*config);
	पूर्णांक ret;

	/* init IPC */
	स_रखो(&config->hda, 0, माप(काष्ठा sof_ipc_dai_hda_params));
	config->hdr.size = size;

	/* get any bespoke DAI tokens */
	ret = sof_parse_tokens(scomp, &config->hda, hda_tokens,
			       ARRAY_SIZE(hda_tokens), निजी->array,
			       le32_to_cpu(निजी->size));
	अगर (ret != 0) अणु
		dev_err(scomp->dev, "error: parse hda tokens failed %d\n",
			le32_to_cpu(निजी->size));
		वापस ret;
	पूर्ण

	dev_dbg(scomp->dev, "HDA config rate %d channels %d\n",
		config->hda.rate, config->hda.channels);

	dai = snd_soc_find_dai(link->cpus);
	अगर (!dai) अणु
		dev_err(scomp->dev, "error: failed to find dai %s in %s",
			link->cpus->dai_name, __func__);
		वापस -EINVAL;
	पूर्ण

	config->hda.link_dma_ch = DMA_CHAN_INVALID;

	ret = sof_set_dai_config(sdev, size, link, config);
	अगर (ret < 0)
		dev_err(scomp->dev, "error: failed to process hda dai link %s",
			link->name);

	वापस ret;
पूर्ण

अटल पूर्णांक sof_link_alh_load(काष्ठा snd_soc_component *scomp, पूर्णांक index,
			     काष्ठा snd_soc_dai_link *link,
			     काष्ठा snd_soc_tplg_link_config *cfg,
			     काष्ठा snd_soc_tplg_hw_config *hw_config,
			     काष्ठा sof_ipc_dai_config *config)
अणु
	काष्ठा snd_sof_dev *sdev = snd_soc_component_get_drvdata(scomp);
	काष्ठा snd_soc_tplg_निजी *निजी = &cfg->priv;
	u32 size = माप(*config);
	पूर्णांक ret;

	ret = sof_parse_tokens(scomp, &config->alh, alh_tokens,
			       ARRAY_SIZE(alh_tokens), निजी->array,
			       le32_to_cpu(निजी->size));
	अगर (ret != 0) अणु
		dev_err(scomp->dev, "error: parse alh tokens failed %d\n",
			le32_to_cpu(निजी->size));
		वापस ret;
	पूर्ण

	/* init IPC */
	config->hdr.size = size;

	/* set config क्रम all DAI's with name matching the link name */
	ret = sof_set_dai_config(sdev, size, link, config);
	अगर (ret < 0)
		dev_err(scomp->dev, "error: failed to save DAI config for ALH %d\n",
			config->dai_index);

	वापस ret;
पूर्ण

/* DAI link - used क्रम any driver specअगरic init */
अटल पूर्णांक sof_link_load(काष्ठा snd_soc_component *scomp, पूर्णांक index,
			 काष्ठा snd_soc_dai_link *link,
			 काष्ठा snd_soc_tplg_link_config *cfg)
अणु
	काष्ठा snd_soc_tplg_निजी *निजी = &cfg->priv;
	काष्ठा snd_soc_tplg_hw_config *hw_config;
	काष्ठा sof_ipc_dai_config common_config;
	काष्ठा sof_ipc_dai_config *config;
	पूर्णांक curr_conf;
	पूर्णांक num_conf;
	पूर्णांक ret;
	पूर्णांक i;

	अगर (!link->platक्रमms) अणु
		dev_err(scomp->dev, "error: no platforms\n");
		वापस -EINVAL;
	पूर्ण
	link->platक्रमms->name = dev_name(scomp->dev);

	/*
	 * Set nonatomic property क्रम FE dai links as their trigger action
	 * involves IPC's.
	 */
	अगर (!link->no_pcm) अणु
		link->nonatomic = true;

		/*
		 * set शेष trigger order क्रम all links. Exceptions to
		 * the rule will be handled in sof_pcm_dai_link_fixup()
		 * For playback, the sequence is the following: start FE,
		 * start BE, stop BE, stop FE; क्रम Capture the sequence is
		 * inverted start BE, start FE, stop FE, stop BE
		 */
		link->trigger[SNDRV_PCM_STREAM_PLAYBACK] =
					SND_SOC_DPCM_TRIGGER_PRE;
		link->trigger[SNDRV_PCM_STREAM_CAPTURE] =
					SND_SOC_DPCM_TRIGGER_POST;

		/* nothing more to करो क्रम FE dai links */
		वापस 0;
	पूर्ण

	/* check we have some tokens - we need at least DAI type */
	अगर (le32_to_cpu(निजी->size) == 0) अणु
		dev_err(scomp->dev, "error: expected tokens for DAI, none found\n");
		वापस -EINVAL;
	पूर्ण

	स_रखो(&common_config, 0, माप(common_config));

	/* get any common DAI tokens */
	ret = sof_parse_tokens(scomp, &common_config, dai_link_tokens, ARRAY_SIZE(dai_link_tokens),
			       निजी->array, le32_to_cpu(निजी->size));
	अगर (ret != 0) अणु
		dev_err(scomp->dev, "error: parse link tokens failed %d\n",
			le32_to_cpu(निजी->size));
		वापस ret;
	पूर्ण

	/*
	 * DAI links are expected to have at least 1 hw_config.
	 * But some older topologies might have no hw_config क्रम HDA dai links.
	 */
	hw_config = cfg->hw_config;
	num_conf = le32_to_cpu(cfg->num_hw_configs);
	अगर (!num_conf) अणु
		अगर (common_config.type != SOF_DAI_INTEL_HDA) अणु
			dev_err(scomp->dev, "error: unexpected DAI config count %d!\n",
				le32_to_cpu(cfg->num_hw_configs));
			वापस -EINVAL;
		पूर्ण
		num_conf = 1;
		curr_conf = 0;
	पूर्ण अन्यथा अणु
		dev_dbg(scomp->dev, "tplg: %d hw_configs found, default id: %d!\n",
			cfg->num_hw_configs, le32_to_cpu(cfg->शेष_hw_config_id));

		क्रम (curr_conf = 0; curr_conf < num_conf; curr_conf++) अणु
			अगर (hw_config[curr_conf].id == cfg->शेष_hw_config_id)
				अवरोध;
		पूर्ण

		अगर (curr_conf == num_conf) अणु
			dev_err(scomp->dev, "error: default hw_config id: %d not found!\n",
				le32_to_cpu(cfg->शेष_hw_config_id));
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* Reserve memory क्रम all hw configs, eventually मुक्तd by widget */
	config = kसुस्मृति(num_conf, माप(*config), GFP_KERNEL);
	अगर (!config)
		वापस -ENOMEM;

	/* Copy common data to all config ipc काष्ठाs */
	क्रम (i = 0; i < num_conf; i++) अणु
		config[i].hdr.cmd = SOF_IPC_GLB_DAI_MSG | SOF_IPC_DAI_CONFIG;
		config[i].क्रमmat = hw_config[i].fmt;
		config[i].type = common_config.type;
		config[i].dai_index = common_config.dai_index;
	पूर्ण

	/* now load DAI specअगरic data and send IPC - type comes from token */
	चयन (common_config.type) अणु
	हाल SOF_DAI_INTEL_SSP:
		ret = sof_link_ssp_load(scomp, index, link, cfg, hw_config, config, curr_conf);
		अवरोध;
	हाल SOF_DAI_INTEL_DMIC:
		ret = sof_link_dmic_load(scomp, index, link, cfg, hw_config + curr_conf, config);
		अवरोध;
	हाल SOF_DAI_INTEL_HDA:
		ret = sof_link_hda_load(scomp, index, link, cfg, hw_config + curr_conf, config);
		अवरोध;
	हाल SOF_DAI_INTEL_ALH:
		ret = sof_link_alh_load(scomp, index, link, cfg, hw_config + curr_conf, config);
		अवरोध;
	हाल SOF_DAI_IMX_SAI:
		ret = sof_link_sai_load(scomp, index, link, cfg, hw_config + curr_conf, config);
		अवरोध;
	हाल SOF_DAI_IMX_ESAI:
		ret = sof_link_esai_load(scomp, index, link, cfg, hw_config + curr_conf, config);
		अवरोध;
	शेष:
		dev_err(scomp->dev, "error: invalid DAI type %d\n", common_config.type);
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	kमुक्त(config);

	वापस ret;
पूर्ण

/* DAI link - used क्रम any driver specअगरic init */
अटल पूर्णांक sof_route_load(काष्ठा snd_soc_component *scomp, पूर्णांक index,
			  काष्ठा snd_soc_dapm_route *route)
अणु
	काष्ठा snd_sof_dev *sdev = snd_soc_component_get_drvdata(scomp);
	काष्ठा sof_ipc_pipe_comp_connect *connect;
	काष्ठा snd_sof_widget *source_swidget, *sink_swidget;
	काष्ठा snd_soc_करोbj *करोbj = &route->करोbj;
	काष्ठा snd_sof_route *sroute;
	काष्ठा sof_ipc_reply reply;
	पूर्णांक ret = 0;

	/* allocate memory क्रम sroute and connect */
	sroute = kzalloc(माप(*sroute), GFP_KERNEL);
	अगर (!sroute)
		वापस -ENOMEM;

	sroute->scomp = scomp;

	connect = kzalloc(माप(*connect), GFP_KERNEL);
	अगर (!connect) अणु
		kमुक्त(sroute);
		वापस -ENOMEM;
	पूर्ण

	connect->hdr.size = माप(*connect);
	connect->hdr.cmd = SOF_IPC_GLB_TPLG_MSG | SOF_IPC_TPLG_COMP_CONNECT;

	dev_dbg(scomp->dev, "sink %s control %s source %s\n",
		route->sink, route->control ? route->control : "none",
		route->source);

	/* source component */
	source_swidget = snd_sof_find_swidget(scomp, (अक्षर *)route->source);
	अगर (!source_swidget) अणु
		dev_err(scomp->dev, "error: source %s not found\n",
			route->source);
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	/*
	 * Virtual widमाला_लो of type output/out_drv may be added in topology
	 * क्रम compatibility. These are not handled by the FW.
	 * So, करोn't send routes whose source/sink widget is of such types
	 * to the DSP.
	 */
	अगर (source_swidget->id == snd_soc_dapm_out_drv ||
	    source_swidget->id == snd_soc_dapm_output)
		जाओ err;

	connect->source_id = source_swidget->comp_id;

	/* sink component */
	sink_swidget = snd_sof_find_swidget(scomp, (अक्षर *)route->sink);
	अगर (!sink_swidget) अणु
		dev_err(scomp->dev, "error: sink %s not found\n",
			route->sink);
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	/*
	 * Don't send routes whose sink widget is of type
	 * output or out_drv to the DSP
	 */
	अगर (sink_swidget->id == snd_soc_dapm_out_drv ||
	    sink_swidget->id == snd_soc_dapm_output)
		जाओ err;

	connect->sink_id = sink_swidget->comp_id;

	/*
	 * For भव routes, both sink and source are not
	 * buffer. Since only buffer linked to component is supported by
	 * FW, others are reported as error, add check in route function,
	 * करो not send it to FW when both source and sink are not buffer
	 */
	अगर (source_swidget->id != snd_soc_dapm_buffer &&
	    sink_swidget->id != snd_soc_dapm_buffer) अणु
		dev_dbg(scomp->dev, "warning: neither Linked source component %s nor sink component %s is of buffer type, ignoring link\n",
			route->source, route->sink);
		जाओ err;
	पूर्ण अन्यथा अणु
		ret = sof_ipc_tx_message(sdev->ipc,
					 connect->hdr.cmd,
					 connect, माप(*connect),
					 &reply, माप(reply));

		/* check IPC वापस value */
		अगर (ret < 0) अणु
			dev_err(scomp->dev, "error: failed to add route sink %s control %s source %s\n",
				route->sink,
				route->control ? route->control : "none",
				route->source);
			जाओ err;
		पूर्ण

		/* check IPC reply */
		अगर (reply.error < 0) अणु
			dev_err(scomp->dev, "error: DSP failed to add route sink %s control %s source %s result %d\n",
				route->sink,
				route->control ? route->control : "none",
				route->source, reply.error);
			ret = reply.error;
			जाओ err;
		पूर्ण

		sroute->route = route;
		करोbj->निजी = sroute;
		sroute->निजी = connect;

		/* add route to route list */
		list_add(&sroute->list, &sdev->route_list);

		वापस 0;
	पूर्ण

err:
	kमुक्त(connect);
	kमुक्त(sroute);
	वापस ret;
पूर्ण

/* Function to set the initial value of SOF kcontrols.
 * The value will be stored in scontrol->control_data
 */
अटल पूर्णांक snd_sof_cache_kcontrol_val(काष्ठा snd_soc_component *scomp)
अणु
	काष्ठा snd_sof_dev *sdev = snd_soc_component_get_drvdata(scomp);
	काष्ठा snd_sof_control *scontrol = शून्य;
	पूर्णांक ipc_cmd, ctrl_type;
	पूर्णांक ret = 0;

	list_क्रम_each_entry(scontrol, &sdev->kcontrol_list, list) अणु

		/* notअगरy DSP of kcontrol values */
		चयन (scontrol->cmd) अणु
		हाल SOF_CTRL_CMD_VOLUME:
		हाल SOF_CTRL_CMD_ENUM:
		हाल SOF_CTRL_CMD_SWITCH:
			ipc_cmd = SOF_IPC_COMP_GET_VALUE;
			ctrl_type = SOF_CTRL_TYPE_VALUE_CHAN_GET;
			अवरोध;
		हाल SOF_CTRL_CMD_BINARY:
			ipc_cmd = SOF_IPC_COMP_GET_DATA;
			ctrl_type = SOF_CTRL_TYPE_DATA_GET;
			अवरोध;
		शेष:
			dev_err(scomp->dev,
				"error: Invalid scontrol->cmd: %d\n",
				scontrol->cmd);
			वापस -EINVAL;
		पूर्ण
		ret = snd_sof_ipc_set_get_comp_data(scontrol,
						    ipc_cmd, ctrl_type,
						    scontrol->cmd,
						    false);
		अगर (ret < 0) अणु
			dev_warn(scomp->dev,
				 "error: kcontrol value get for widget: %d\n",
				 scontrol->comp_id);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक snd_sof_complete_pipeline(काष्ठा device *dev,
			      काष्ठा snd_sof_widget *swidget)
अणु
	काष्ठा snd_sof_dev *sdev = dev_get_drvdata(dev);
	काष्ठा sof_ipc_pipe_पढ़ोy पढ़ोy;
	काष्ठा sof_ipc_reply reply;
	पूर्णांक ret;

	dev_dbg(dev, "tplg: complete pipeline %s id %d\n",
		swidget->widget->name, swidget->comp_id);

	स_रखो(&पढ़ोy, 0, माप(पढ़ोy));
	पढ़ोy.hdr.size = माप(पढ़ोy);
	पढ़ोy.hdr.cmd = SOF_IPC_GLB_TPLG_MSG | SOF_IPC_TPLG_PIPE_COMPLETE;
	पढ़ोy.comp_id = swidget->comp_id;

	ret = sof_ipc_tx_message(sdev->ipc,
				 पढ़ोy.hdr.cmd, &पढ़ोy, माप(पढ़ोy), &reply,
				 माप(reply));
	अगर (ret < 0)
		वापस ret;
	वापस 1;
पूर्ण

/* completion - called at completion of firmware loading */
अटल व्योम sof_complete(काष्ठा snd_soc_component *scomp)
अणु
	काष्ठा snd_sof_dev *sdev = snd_soc_component_get_drvdata(scomp);
	काष्ठा snd_sof_widget *swidget;

	/* some widget types require completion notअगरicattion */
	list_क्रम_each_entry(swidget, &sdev->widget_list, list) अणु
		अगर (swidget->complete)
			जारी;

		चयन (swidget->id) अणु
		हाल snd_soc_dapm_scheduler:
			swidget->complete =
				snd_sof_complete_pipeline(scomp->dev, swidget);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	/*
	 * cache initial values of SOF kcontrols by पढ़ोing DSP value over
	 * IPC. It may be overwritten by alsa-mixer after booting up
	 */
	snd_sof_cache_kcontrol_val(scomp);
पूर्ण

/* manअगरest - optional to inक्रमm component of manअगरest */
अटल पूर्णांक sof_manअगरest(काष्ठा snd_soc_component *scomp, पूर्णांक index,
			काष्ठा snd_soc_tplg_manअगरest *man)
अणु
	u32 size;
	u32 abi_version;

	size = le32_to_cpu(man->priv.size);

	/* backward compatible with tplg without ABI info */
	अगर (!size) अणु
		dev_dbg(scomp->dev, "No topology ABI info\n");
		वापस 0;
	पूर्ण

	अगर (size != SOF_TPLG_ABI_SIZE) अणु
		dev_err(scomp->dev, "error: invalid topology ABI size\n");
		वापस -EINVAL;
	पूर्ण

	dev_info(scomp->dev,
		 "Topology: ABI %d:%d:%d Kernel ABI %d:%d:%d\n",
		 man->priv.data[0], man->priv.data[1],
		 man->priv.data[2], SOF_ABI_MAJOR, SOF_ABI_MINOR,
		 SOF_ABI_PATCH);

	abi_version = SOF_ABI_VER(man->priv.data[0],
				  man->priv.data[1],
				  man->priv.data[2]);

	अगर (SOF_ABI_VERSION_INCOMPATIBLE(SOF_ABI_VERSION, abi_version)) अणु
		dev_err(scomp->dev, "error: incompatible topology ABI version\n");
		वापस -EINVAL;
	पूर्ण

	अगर (SOF_ABI_VERSION_MINOR(abi_version) > SOF_ABI_MINOR) अणु
		अगर (!IS_ENABLED(CONFIG_SND_SOC_SOF_STRICT_ABI_CHECKS)) अणु
			dev_warn(scomp->dev, "warn: topology ABI is more recent than kernel\n");
		पूर्ण अन्यथा अणु
			dev_err(scomp->dev, "error: topology ABI is more recent than kernel\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* venकरोr specअगरic kcontrol handlers available क्रम binding */
अटल स्थिर काष्ठा snd_soc_tplg_kcontrol_ops sof_io_ops[] = अणु
	अणुSOF_TPLG_KCTL_VOL_ID, snd_sof_volume_get, snd_sof_volume_putपूर्ण,
	अणुSOF_TPLG_KCTL_BYTES_ID, snd_sof_bytes_get, snd_sof_bytes_putपूर्ण,
	अणुSOF_TPLG_KCTL_ENUM_ID, snd_sof_क्रमागत_get, snd_sof_क्रमागत_putपूर्ण,
	अणुSOF_TPLG_KCTL_SWITCH_ID, snd_sof_चयन_get, snd_sof_चयन_putपूर्ण,
पूर्ण;

/* venकरोr specअगरic bytes ext handlers available क्रम binding */
अटल स्थिर काष्ठा snd_soc_tplg_bytes_ext_ops sof_bytes_ext_ops[] = अणु
	अणुSOF_TPLG_KCTL_BYTES_ID, snd_sof_bytes_ext_get, snd_sof_bytes_ext_putपूर्ण,
	अणुSOF_TPLG_KCTL_BYTES_VOLATILE_RO, snd_sof_bytes_ext_अस्थिर_getपूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_tplg_ops sof_tplg_ops = अणु
	/* बाह्यal kcontrol init - used क्रम any driver specअगरic init */
	.control_load	= sof_control_load,
	.control_unload	= sof_control_unload,

	/* बाह्यal kcontrol init - used क्रम any driver specअगरic init */
	.dapm_route_load	= sof_route_load,
	.dapm_route_unload	= sof_route_unload,

	/* बाह्यal widget init - used क्रम any driver specअगरic init */
	/* .widget_load is not currently used */
	.widget_पढ़ोy	= sof_widget_पढ़ोy,
	.widget_unload	= sof_widget_unload,

	/* FE DAI - used क्रम any driver specअगरic init */
	.dai_load	= sof_dai_load,
	.dai_unload	= sof_dai_unload,

	/* DAI link - used क्रम any driver specअगरic init */
	.link_load	= sof_link_load,

	/* completion - called at completion of firmware loading */
	.complete	= sof_complete,

	/* manअगरest - optional to inक्रमm component of manअगरest */
	.manअगरest	= sof_manअगरest,

	/* venकरोr specअगरic kcontrol handlers available क्रम binding */
	.io_ops		= sof_io_ops,
	.io_ops_count	= ARRAY_SIZE(sof_io_ops),

	/* venकरोr specअगरic bytes ext handlers available क्रम binding */
	.bytes_ext_ops	= sof_bytes_ext_ops,
	.bytes_ext_ops_count	= ARRAY_SIZE(sof_bytes_ext_ops),
पूर्ण;

पूर्णांक snd_sof_load_topology(काष्ठा snd_soc_component *scomp, स्थिर अक्षर *file)
अणु
	स्थिर काष्ठा firmware *fw;
	पूर्णांक ret;

	dev_dbg(scomp->dev, "loading topology:%s\n", file);

	ret = request_firmware(&fw, file, scomp->dev);
	अगर (ret < 0) अणु
		dev_err(scomp->dev, "error: tplg request firmware %s failed err: %d\n",
			file, ret);
		dev_err(scomp->dev,
			"you may need to download the firmware from https://github.com/thesofproject/sof-bin/\n");
		वापस ret;
	पूर्ण

	ret = snd_soc_tplg_component_load(scomp, &sof_tplg_ops, fw);
	अगर (ret < 0) अणु
		dev_err(scomp->dev, "error: tplg component load failed %d\n",
			ret);
		ret = -EINVAL;
	पूर्ण

	release_firmware(fw);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(snd_sof_load_topology);
