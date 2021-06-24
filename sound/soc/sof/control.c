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

/* Mixer Controls */

#समावेश <linux/pm_runसमय.स>
#समावेश <linux/leds.h>
#समावेश "sof-priv.h"
#समावेश "sof-audio.h"

अटल व्योम update_mute_led(काष्ठा snd_sof_control *scontrol,
			    काष्ठा snd_kcontrol *kcontrol,
			    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	पूर्णांक temp = 0;
	पूर्णांक mask;
	पूर्णांक i;

	mask = 1U << snd_ctl_get_ioffidx(kcontrol, &ucontrol->id);

	क्रम (i = 0; i < scontrol->num_channels; i++) अणु
		अगर (ucontrol->value.पूर्णांकeger.value[i]) अणु
			temp |= mask;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (temp == scontrol->led_ctl.led_value)
		वापस;

	scontrol->led_ctl.led_value = temp;

#अगर IS_REACHABLE(CONFIG_LEDS_TRIGGER_AUDIO)
	अगर (!scontrol->led_ctl.direction)
		ledtrig_audio_set(LED_AUDIO_MUTE, temp ? LED_OFF : LED_ON);
	अन्यथा
		ledtrig_audio_set(LED_AUDIO_MICMUTE, temp ? LED_OFF : LED_ON);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत u32 mixer_to_ipc(अचिन्हित पूर्णांक value, u32 *volume_map, पूर्णांक size)
अणु
	अगर (value >= size)
		वापस volume_map[size - 1];

	वापस volume_map[value];
पूर्ण

अटल अंतरभूत u32 ipc_to_mixer(u32 value, u32 *volume_map, पूर्णांक size)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < size; i++) अणु
		अगर (volume_map[i] >= value)
			वापस i;
	पूर्ण

	वापस i - 1;
पूर्ण

पूर्णांक snd_sof_volume_get(काष्ठा snd_kcontrol *kcontrol,
		       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा soc_mixer_control *sm =
		(काष्ठा soc_mixer_control *)kcontrol->निजी_value;
	काष्ठा snd_sof_control *scontrol = sm->करोbj.निजी;
	काष्ठा sof_ipc_ctrl_data *cdata = scontrol->control_data;
	अचिन्हित पूर्णांक i, channels = scontrol->num_channels;

	/* पढ़ो back each channel */
	क्रम (i = 0; i < channels; i++)
		ucontrol->value.पूर्णांकeger.value[i] =
			ipc_to_mixer(cdata->chanv[i].value,
				     scontrol->volume_table, sm->max + 1);

	वापस 0;
पूर्ण

पूर्णांक snd_sof_volume_put(काष्ठा snd_kcontrol *kcontrol,
		       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा soc_mixer_control *sm =
		(काष्ठा soc_mixer_control *)kcontrol->निजी_value;
	काष्ठा snd_sof_control *scontrol = sm->करोbj.निजी;
	काष्ठा snd_soc_component *scomp = scontrol->scomp;
	काष्ठा sof_ipc_ctrl_data *cdata = scontrol->control_data;
	अचिन्हित पूर्णांक i, channels = scontrol->num_channels;
	bool change = false;
	u32 value;

	/* update each channel */
	क्रम (i = 0; i < channels; i++) अणु
		value = mixer_to_ipc(ucontrol->value.पूर्णांकeger.value[i],
				     scontrol->volume_table, sm->max + 1);
		change = change || (value != cdata->chanv[i].value);
		cdata->chanv[i].channel = i;
		cdata->chanv[i].value = value;
	पूर्ण

	/* notअगरy DSP of mixer updates */
	अगर (pm_runसमय_active(scomp->dev))
		snd_sof_ipc_set_get_comp_data(scontrol,
					      SOF_IPC_COMP_SET_VALUE,
					      SOF_CTRL_TYPE_VALUE_CHAN_GET,
					      SOF_CTRL_CMD_VOLUME,
					      true);
	वापस change;
पूर्ण

पूर्णांक snd_sof_volume_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा soc_mixer_control *sm = (काष्ठा soc_mixer_control *)kcontrol->निजी_value;
	काष्ठा snd_sof_control *scontrol = sm->करोbj.निजी;
	अचिन्हित पूर्णांक channels = scontrol->num_channels;
	पूर्णांक platक्रमm_max;

	अगर (!sm->platक्रमm_max)
		sm->platक्रमm_max = sm->max;
	platक्रमm_max = sm->platक्रमm_max;

	अगर (platक्रमm_max == 1 && !म_माला(kcontrol->id.name, " Volume"))
		uinfo->type = SNDRV_CTL_ELEM_TYPE_BOOLEAN;
	अन्यथा
		uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;

	uinfo->count = channels;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = platक्रमm_max - sm->min;
	वापस 0;
पूर्ण

पूर्णांक snd_sof_चयन_get(काष्ठा snd_kcontrol *kcontrol,
		       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा soc_mixer_control *sm =
		(काष्ठा soc_mixer_control *)kcontrol->निजी_value;
	काष्ठा snd_sof_control *scontrol = sm->करोbj.निजी;
	काष्ठा sof_ipc_ctrl_data *cdata = scontrol->control_data;
	अचिन्हित पूर्णांक i, channels = scontrol->num_channels;

	/* पढ़ो back each channel */
	क्रम (i = 0; i < channels; i++)
		ucontrol->value.पूर्णांकeger.value[i] = cdata->chanv[i].value;

	वापस 0;
पूर्ण

पूर्णांक snd_sof_चयन_put(काष्ठा snd_kcontrol *kcontrol,
		       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा soc_mixer_control *sm =
		(काष्ठा soc_mixer_control *)kcontrol->निजी_value;
	काष्ठा snd_sof_control *scontrol = sm->करोbj.निजी;
	काष्ठा snd_soc_component *scomp = scontrol->scomp;
	काष्ठा sof_ipc_ctrl_data *cdata = scontrol->control_data;
	अचिन्हित पूर्णांक i, channels = scontrol->num_channels;
	bool change = false;
	u32 value;

	/* update each channel */
	क्रम (i = 0; i < channels; i++) अणु
		value = ucontrol->value.पूर्णांकeger.value[i];
		change = change || (value != cdata->chanv[i].value);
		cdata->chanv[i].channel = i;
		cdata->chanv[i].value = value;
	पूर्ण

	अगर (scontrol->led_ctl.use_led)
		update_mute_led(scontrol, kcontrol, ucontrol);

	/* notअगरy DSP of mixer updates */
	अगर (pm_runसमय_active(scomp->dev))
		snd_sof_ipc_set_get_comp_data(scontrol,
					      SOF_IPC_COMP_SET_VALUE,
					      SOF_CTRL_TYPE_VALUE_CHAN_GET,
					      SOF_CTRL_CMD_SWITCH,
					      true);

	वापस change;
पूर्ण

पूर्णांक snd_sof_क्रमागत_get(काष्ठा snd_kcontrol *kcontrol,
		     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा soc_क्रमागत *se =
		(काष्ठा soc_क्रमागत *)kcontrol->निजी_value;
	काष्ठा snd_sof_control *scontrol = se->करोbj.निजी;
	काष्ठा sof_ipc_ctrl_data *cdata = scontrol->control_data;
	अचिन्हित पूर्णांक i, channels = scontrol->num_channels;

	/* पढ़ो back each channel */
	क्रम (i = 0; i < channels; i++)
		ucontrol->value.क्रमागतerated.item[i] = cdata->chanv[i].value;

	वापस 0;
पूर्ण

पूर्णांक snd_sof_क्रमागत_put(काष्ठा snd_kcontrol *kcontrol,
		     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा soc_क्रमागत *se =
		(काष्ठा soc_क्रमागत *)kcontrol->निजी_value;
	काष्ठा snd_sof_control *scontrol = se->करोbj.निजी;
	काष्ठा snd_soc_component *scomp = scontrol->scomp;
	काष्ठा sof_ipc_ctrl_data *cdata = scontrol->control_data;
	अचिन्हित पूर्णांक i, channels = scontrol->num_channels;
	bool change = false;
	u32 value;

	/* update each channel */
	क्रम (i = 0; i < channels; i++) अणु
		value = ucontrol->value.क्रमागतerated.item[i];
		change = change || (value != cdata->chanv[i].value);
		cdata->chanv[i].channel = i;
		cdata->chanv[i].value = value;
	पूर्ण

	/* notअगरy DSP of क्रमागत updates */
	अगर (pm_runसमय_active(scomp->dev))
		snd_sof_ipc_set_get_comp_data(scontrol,
					      SOF_IPC_COMP_SET_VALUE,
					      SOF_CTRL_TYPE_VALUE_CHAN_GET,
					      SOF_CTRL_CMD_ENUM,
					      true);

	वापस change;
पूर्ण

पूर्णांक snd_sof_bytes_get(काष्ठा snd_kcontrol *kcontrol,
		      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा soc_bytes_ext *be =
		(काष्ठा soc_bytes_ext *)kcontrol->निजी_value;
	काष्ठा snd_sof_control *scontrol = be->करोbj.निजी;
	काष्ठा snd_soc_component *scomp = scontrol->scomp;
	काष्ठा sof_ipc_ctrl_data *cdata = scontrol->control_data;
	काष्ठा sof_abi_hdr *data = cdata->data;
	माप_प्रकार size;

	अगर (be->max > माप(ucontrol->value.bytes.data)) अणु
		dev_err_ratelimited(scomp->dev,
				    "error: data max %d exceeds ucontrol data array size\n",
				    be->max);
		वापस -EINVAL;
	पूर्ण

	/* be->max has been verअगरied to be >= माप(काष्ठा sof_abi_hdr) */
	अगर (data->size > be->max - माप(*data)) अणु
		dev_err_ratelimited(scomp->dev,
				    "error: %u bytes of control data is invalid, max is %zu\n",
				    data->size, be->max - माप(*data));
		वापस -EINVAL;
	पूर्ण

	size = data->size + माप(*data);

	/* copy back to kcontrol */
	स_नकल(ucontrol->value.bytes.data, data, size);

	वापस 0;
पूर्ण

पूर्णांक snd_sof_bytes_put(काष्ठा snd_kcontrol *kcontrol,
		      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा soc_bytes_ext *be =
		(काष्ठा soc_bytes_ext *)kcontrol->निजी_value;
	काष्ठा snd_sof_control *scontrol = be->करोbj.निजी;
	काष्ठा snd_soc_component *scomp = scontrol->scomp;
	काष्ठा sof_ipc_ctrl_data *cdata = scontrol->control_data;
	काष्ठा sof_abi_hdr *data = cdata->data;
	माप_प्रकार size;

	अगर (be->max > माप(ucontrol->value.bytes.data)) अणु
		dev_err_ratelimited(scomp->dev,
				    "error: data max %d exceeds ucontrol data array size\n",
				    be->max);
		वापस -EINVAL;
	पूर्ण

	/* be->max has been verअगरied to be >= माप(काष्ठा sof_abi_hdr) */
	अगर (data->size > be->max - माप(*data)) अणु
		dev_err_ratelimited(scomp->dev,
				    "error: data size too big %u bytes max is %zu\n",
				    data->size, be->max - माप(*data));
		वापस -EINVAL;
	पूर्ण

	size = data->size + माप(*data);

	/* copy from kcontrol */
	स_नकल(data, ucontrol->value.bytes.data, size);

	/* notअगरy DSP of byte control updates */
	अगर (pm_runसमय_active(scomp->dev))
		snd_sof_ipc_set_get_comp_data(scontrol,
					      SOF_IPC_COMP_SET_DATA,
					      SOF_CTRL_TYPE_DATA_SET,
					      scontrol->cmd,
					      true);

	वापस 0;
पूर्ण

पूर्णांक snd_sof_bytes_ext_put(काष्ठा snd_kcontrol *kcontrol,
			  स्थिर अचिन्हित पूर्णांक __user *binary_data,
			  अचिन्हित पूर्णांक size)
अणु
	काष्ठा soc_bytes_ext *be =
		(काष्ठा soc_bytes_ext *)kcontrol->निजी_value;
	काष्ठा snd_sof_control *scontrol = be->करोbj.निजी;
	काष्ठा snd_soc_component *scomp = scontrol->scomp;
	काष्ठा sof_ipc_ctrl_data *cdata = scontrol->control_data;
	काष्ठा snd_ctl_tlv header;
	स्थिर काष्ठा snd_ctl_tlv __user *tlvd =
		(स्थिर काष्ठा snd_ctl_tlv __user *)binary_data;

	/* make sure we have at least a header */
	अगर (size < माप(काष्ठा snd_ctl_tlv))
		वापस -EINVAL;

	/*
	 * The beginning of bytes data contains a header from where
	 * the length (as bytes) is needed to know the correct copy
	 * length of data from tlvd->tlv.
	 */
	अगर (copy_from_user(&header, tlvd, माप(काष्ठा snd_ctl_tlv)))
		वापस -EFAULT;

	/* make sure TLV info is consistent */
	अगर (header.length + माप(काष्ठा snd_ctl_tlv) > size) अणु
		dev_err_ratelimited(scomp->dev, "error: inconsistent TLV, data %d + header %zu > %d\n",
				    header.length, माप(काष्ठा snd_ctl_tlv), size);
		वापस -EINVAL;
	पूर्ण

	/* be->max is coming from topology */
	अगर (header.length > be->max) अणु
		dev_err_ratelimited(scomp->dev, "error: Bytes data size %d exceeds max %d.\n",
				    header.length, be->max);
		वापस -EINVAL;
	पूर्ण

	/* Check that header id matches the command */
	अगर (header.numid != scontrol->cmd) अणु
		dev_err_ratelimited(scomp->dev,
				    "error: incorrect numid %d\n",
				    header.numid);
		वापस -EINVAL;
	पूर्ण

	अगर (copy_from_user(cdata->data, tlvd->tlv, header.length))
		वापस -EFAULT;

	अगर (cdata->data->magic != SOF_ABI_MAGIC) अणु
		dev_err_ratelimited(scomp->dev,
				    "error: Wrong ABI magic 0x%08x.\n",
				    cdata->data->magic);
		वापस -EINVAL;
	पूर्ण

	अगर (SOF_ABI_VERSION_INCOMPATIBLE(SOF_ABI_VERSION, cdata->data->abi)) अणु
		dev_err_ratelimited(scomp->dev, "error: Incompatible ABI version 0x%08x.\n",
				    cdata->data->abi);
		वापस -EINVAL;
	पूर्ण

	/* be->max has been verअगरied to be >= माप(काष्ठा sof_abi_hdr) */
	अगर (cdata->data->size > be->max - माप(काष्ठा sof_abi_hdr)) अणु
		dev_err_ratelimited(scomp->dev, "error: Mismatch in ABI data size (truncated?).\n");
		वापस -EINVAL;
	पूर्ण

	/* notअगरy DSP of byte control updates */
	अगर (pm_runसमय_active(scomp->dev))
		snd_sof_ipc_set_get_comp_data(scontrol,
					      SOF_IPC_COMP_SET_DATA,
					      SOF_CTRL_TYPE_DATA_SET,
					      scontrol->cmd,
					      true);

	वापस 0;
पूर्ण

पूर्णांक snd_sof_bytes_ext_अस्थिर_get(काष्ठा snd_kcontrol *kcontrol, अचिन्हित पूर्णांक __user *binary_data,
				   अचिन्हित पूर्णांक size)
अणु
	काष्ठा soc_bytes_ext *be = (काष्ठा soc_bytes_ext *)kcontrol->निजी_value;
	काष्ठा snd_sof_control *scontrol = be->करोbj.निजी;
	काष्ठा snd_soc_component *scomp = scontrol->scomp;
	काष्ठा sof_ipc_ctrl_data *cdata = scontrol->control_data;
	काष्ठा snd_ctl_tlv header;
	काष्ठा snd_ctl_tlv __user *tlvd = (काष्ठा snd_ctl_tlv __user *)binary_data;
	माप_प्रकार data_size;
	पूर्णांक ret;
	पूर्णांक err;

	/*
	 * Decrement the limit by ext bytes header size to
	 * ensure the user space buffer is not exceeded.
	 */
	अगर (size < माप(काष्ठा snd_ctl_tlv))
		वापस -ENOSPC;
	size -= माप(काष्ठा snd_ctl_tlv);

	ret = pm_runसमय_get_sync(scomp->dev);
	अगर (ret < 0 && ret != -EACCES) अणु
		dev_err_ratelimited(scomp->dev, "error: bytes_ext get failed to resume %d\n", ret);
		pm_runसमय_put_noidle(scomp->dev);
		वापस ret;
	पूर्ण

	/* set the ABI header values */
	cdata->data->magic = SOF_ABI_MAGIC;
	cdata->data->abi = SOF_ABI_VERSION;
	/* get all the component data from DSP */
	ret = snd_sof_ipc_set_get_comp_data(scontrol, SOF_IPC_COMP_GET_DATA, SOF_CTRL_TYPE_DATA_GET,
					    scontrol->cmd, false);
	अगर (ret < 0)
		जाओ out;

	/* check data size करोesn't exceed max coming from topology */
	अगर (cdata->data->size > be->max - माप(काष्ठा sof_abi_hdr)) अणु
		dev_err_ratelimited(scomp->dev, "error: user data size %d exceeds max size %zu.\n",
				    cdata->data->size,
				    be->max - माप(काष्ठा sof_abi_hdr));
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	data_size = cdata->data->size + माप(काष्ठा sof_abi_hdr);

	/* make sure we करोn't exceed size provided by user space क्रम data */
	अगर (data_size > size) अणु
		ret = -ENOSPC;
		जाओ out;
	पूर्ण

	header.numid = scontrol->cmd;
	header.length = data_size;
	अगर (copy_to_user(tlvd, &header, माप(काष्ठा snd_ctl_tlv))) अणु
		ret = -EFAULT;
		जाओ out;
	पूर्ण

	अगर (copy_to_user(tlvd->tlv, cdata->data, data_size))
		ret = -EFAULT;
out:
	pm_runसमय_mark_last_busy(scomp->dev);
	err = pm_runसमय_put_स्वतःsuspend(scomp->dev);
	अगर (err < 0)
		dev_err_ratelimited(scomp->dev, "error: bytes_ext get failed to idle %d\n", err);

	वापस ret;
पूर्ण

पूर्णांक snd_sof_bytes_ext_get(काष्ठा snd_kcontrol *kcontrol,
			  अचिन्हित पूर्णांक __user *binary_data,
			  अचिन्हित पूर्णांक size)
अणु
	काष्ठा soc_bytes_ext *be =
		(काष्ठा soc_bytes_ext *)kcontrol->निजी_value;
	काष्ठा snd_sof_control *scontrol = be->करोbj.निजी;
	काष्ठा snd_soc_component *scomp = scontrol->scomp;
	काष्ठा sof_ipc_ctrl_data *cdata = scontrol->control_data;
	काष्ठा snd_ctl_tlv header;
	काष्ठा snd_ctl_tlv __user *tlvd =
		(काष्ठा snd_ctl_tlv __user *)binary_data;
	माप_प्रकार data_size;

	/*
	 * Decrement the limit by ext bytes header size to
	 * ensure the user space buffer is not exceeded.
	 */
	अगर (size < माप(काष्ठा snd_ctl_tlv))
		वापस -ENOSPC;
	size -= माप(काष्ठा snd_ctl_tlv);

	/* set the ABI header values */
	cdata->data->magic = SOF_ABI_MAGIC;
	cdata->data->abi = SOF_ABI_VERSION;

	/* check data size करोesn't exceed max coming from topology */
	अगर (cdata->data->size > be->max - माप(काष्ठा sof_abi_hdr)) अणु
		dev_err_ratelimited(scomp->dev, "error: user data size %d exceeds max size %zu.\n",
				    cdata->data->size,
				    be->max - माप(काष्ठा sof_abi_hdr));
		वापस -EINVAL;
	पूर्ण

	data_size = cdata->data->size + माप(काष्ठा sof_abi_hdr);

	/* make sure we करोn't exceed size provided by user space क्रम data */
	अगर (data_size > size)
		वापस -ENOSPC;

	header.numid = scontrol->cmd;
	header.length = data_size;
	अगर (copy_to_user(tlvd, &header, माप(काष्ठा snd_ctl_tlv)))
		वापस -EFAULT;

	अगर (copy_to_user(tlvd->tlv, cdata->data, data_size))
		वापस -EFAULT;

	वापस 0;
पूर्ण
