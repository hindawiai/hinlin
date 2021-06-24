<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
 /*
 *  sst-atom-controls.c - Intel MID Platक्रमm driver DPCM ALSA controls क्रम Mrfld
 *
 *  Copyright (C) 2013-14 Intel Corp
 *  Author: Omair Mohammed Abdullah <omair.m.abdullah@पूर्णांकel.com>
 *	Vinod Koul <vinod.koul@पूर्णांकel.com>
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *  In the dpcm driver modelling when a particular FE/BE/Mixer/Pipe is active
 *  we क्रमward the settings and parameters, rest we keep the values  in
 *  driver and क्रमward when DAPM enables them
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/slab.h>
#समावेश <sound/soc.h>
#समावेश <sound/tlv.h>
#समावेश "sst-mfld-platform.h"
#समावेश "sst-atom-controls.h"

अटल पूर्णांक sst_fill_byte_control(काष्ठा sst_data *drv,
					 u8 ipc_msg, u8 block,
					 u8 task_id, u8 pipe_id,
					 u16 len, व्योम *cmd_data)
अणु
	काष्ठा snd_sst_bytes_v2 *byte_data = drv->byte_stream;

	byte_data->type = SST_CMD_BYTES_SET;
	byte_data->ipc_msg = ipc_msg;
	byte_data->block = block;
	byte_data->task_id = task_id;
	byte_data->pipe_id = pipe_id;

	अगर (len > SST_MAX_BIN_BYTES - माप(*byte_data)) अणु
		dev_err(&drv->pdev->dev, "command length too big (%u)", len);
		वापस -EINVAL;
	पूर्ण
	byte_data->len = len;
	स_नकल(byte_data->bytes, cmd_data, len);
	prपूर्णांक_hex_dump_bytes("writing to lpe: ", DUMP_PREFIX_OFFSET,
			     byte_data, len + माप(*byte_data));
	वापस 0;
पूर्ण

अटल पूर्णांक sst_fill_and_send_cmd_unlocked(काष्ठा sst_data *drv,
				 u8 ipc_msg, u8 block, u8 task_id, u8 pipe_id,
				 व्योम *cmd_data, u16 len)
अणु
	पूर्णांक ret = 0;

	WARN_ON(!mutex_is_locked(&drv->lock));

	ret = sst_fill_byte_control(drv, ipc_msg,
				block, task_id, pipe_id, len, cmd_data);
	अगर (ret < 0)
		वापस ret;
	वापस sst->ops->send_byte_stream(sst->dev, drv->byte_stream);
पूर्ण

/**
 * sst_fill_and_send_cmd - generate the IPC message and send it to the FW
 * @drv: sst_data
 * @ipc_msg: type of IPC (CMD, SET_PARAMS, GET_PARAMS)
 * @block: block index
 * @task_id: task index
 * @pipe_id: pipe index
 * @cmd_data: the IPC payload
 * @len: length of data to be sent
 */
अटल पूर्णांक sst_fill_and_send_cmd(काष्ठा sst_data *drv,
				 u8 ipc_msg, u8 block, u8 task_id, u8 pipe_id,
				 व्योम *cmd_data, u16 len)
अणु
	पूर्णांक ret;

	mutex_lock(&drv->lock);
	ret = sst_fill_and_send_cmd_unlocked(drv, ipc_msg, block,
					task_id, pipe_id, cmd_data, len);
	mutex_unlock(&drv->lock);

	वापस ret;
पूर्ण

/*
 * tx map value is a bitfield where each bit represents a FW channel
 *
 *			3 2 1 0		# 0 = codec0, 1 = codec1
 *			RLRLRLRL	# 3, 4 = reserved
 *
 * e.g. slot 0 rx map =	00001100b -> data from slot 0 goes पूर्णांकo codec_in1 L,R
 */
अटल u8 sst_ssp_tx_map[SST_MAX_TDM_SLOTS] = अणु
	0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80, /* शेष rx map */
पूर्ण;

/*
 * rx map value is a bitfield where each bit represents a slot
 *
 *			  76543210	# 0 = slot 0, 1 = slot 1
 *
 * e.g. codec1_0 tx map = 00000101b -> data from codec_out1_0 goes पूर्णांकo slot 0, 2
 */
अटल u8 sst_ssp_rx_map[SST_MAX_TDM_SLOTS] = अणु
	0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80, /* शेष tx map */
पूर्ण;

/*
 * NOTE: this is invoked with lock held
 */
अटल पूर्णांक sst_send_slot_map(काष्ठा sst_data *drv)
अणु
	काष्ठा sst_param_sba_ssp_slot_map cmd;

	SST_FILL_DEFAULT_DESTINATION(cmd.header.dst);
	cmd.header.command_id = SBA_SET_SSP_SLOT_MAP;
	cmd.header.length = माप(काष्ठा sst_param_sba_ssp_slot_map)
				- माप(काष्ठा sst_dsp_header);

	cmd.param_id = SBA_SET_SSP_SLOT_MAP;
	cmd.param_len = माप(cmd.rx_slot_map) + माप(cmd.tx_slot_map)
					+ माप(cmd.ssp_index);
	cmd.ssp_index = SSP_CODEC;

	स_नकल(cmd.rx_slot_map, &sst_ssp_tx_map[0], माप(cmd.rx_slot_map));
	स_नकल(cmd.tx_slot_map, &sst_ssp_rx_map[0], माप(cmd.tx_slot_map));

	वापस sst_fill_and_send_cmd_unlocked(drv, SST_IPC_IA_SET_PARAMS,
			SST_FLAG_BLOCKED, SST_TASK_SBA, 0, &cmd,
			      माप(cmd.header) + cmd.header.length);
पूर्ण

अटल पूर्णांक sst_slot_क्रमागत_info(काष्ठा snd_kcontrol *kcontrol,
		       काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा sst_क्रमागत *e = (काष्ठा sst_क्रमागत *)kcontrol->निजी_value;

	uinfo->type = SNDRV_CTL_ELEM_TYPE_ENUMERATED;
	uinfo->count = 1;
	uinfo->value.क्रमागतerated.items = e->max;

	अगर (uinfo->value.क्रमागतerated.item > e->max - 1)
		uinfo->value.क्रमागतerated.item = e->max - 1;
	म_नकल(uinfo->value.क्रमागतerated.name,
		e->texts[uinfo->value.क्रमागतerated.item]);

	वापस 0;
पूर्ण

/**
 * sst_slot_get - get the status of the पूर्णांकerleaver/deपूर्णांकerleaver control
 * @kcontrol: control poपूर्णांकer
 * @ucontrol: User data
 * Searches the map where the control status is stored, and माला_लो the
 * channel/slot which is currently set क्रम this क्रमागतerated control. Since it is
 * an क्रमागतerated control, there is only one possible value.
 */
अटल पूर्णांक sst_slot_get(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा sst_क्रमागत *e = (व्योम *)kcontrol->निजी_value;
	काष्ठा snd_soc_component *c = snd_kcontrol_chip(kcontrol);
	काष्ठा sst_data *drv = snd_soc_component_get_drvdata(c);
	अचिन्हित पूर्णांक ctl_no = e->reg;
	अचिन्हित पूर्णांक is_tx = e->tx;
	अचिन्हित पूर्णांक val, mux;
	u8 *map = is_tx ? sst_ssp_rx_map : sst_ssp_tx_map;

	mutex_lock(&drv->lock);
	val = 1 << ctl_no;
	/* search which slot/channel has this bit set - there should be only one */
	क्रम (mux = e->max; mux > 0;  mux--)
		अगर (map[mux - 1] & val)
			अवरोध;

	ucontrol->value.क्रमागतerated.item[0] = mux;
	mutex_unlock(&drv->lock);

	dev_dbg(c->dev, "%s - %s map = %#x\n",
			is_tx ? "tx channel" : "rx slot",
			 e->texts[mux], mux ? map[mux - 1] : -1);
	वापस 0;
पूर्ण

/* sst_check_and_send_slot_map - helper क्रम checking घातer state and sending
 * slot map cmd
 *
 * called with lock held
 */
अटल पूर्णांक sst_check_and_send_slot_map(काष्ठा sst_data *drv, काष्ठा snd_kcontrol *kcontrol)
अणु
	काष्ठा sst_क्रमागत *e = (व्योम *)kcontrol->निजी_value;
	पूर्णांक ret = 0;

	अगर (e->w && e->w->घातer)
		ret = sst_send_slot_map(drv);
	अन्यथा अगर (!e->w)
		dev_err(&drv->pdev->dev, "Slot control: %s doesn't have DAPM widget!!!\n",
				kcontrol->id.name);
	वापस ret;
पूर्ण

/**
 * sst_slot_put - set the status of पूर्णांकerleaver/deपूर्णांकerleaver control
 * @kcontrol: control poपूर्णांकer
 * @ucontrol: User data
 * (de)पूर्णांकerleaver controls are defined in opposite sense to be user-मित्रly
 *
 * Instead of the क्रमागत value being the value written to the रेजिस्टर, it is the
 * रेजिस्टर address; and the kcontrol number (रेजिस्टर num) is the value written
 * to the रेजिस्टर. This is so that there can be only one value क्रम each
 * slot/channel since there is only one control क्रम each slot/channel.
 *
 * This means that whenever an क्रमागत is set, we need to clear the bit
 * क्रम that kcontrol_no क्रम all the पूर्णांकerleaver OR deपूर्णांकerleaver रेजिस्टरs
 */
अटल पूर्णांक sst_slot_put(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *c = snd_soc_kcontrol_component(kcontrol);
	काष्ठा sst_data *drv = snd_soc_component_get_drvdata(c);
	काष्ठा sst_क्रमागत *e = (व्योम *)kcontrol->निजी_value;
	पूर्णांक i, ret = 0;
	अचिन्हित पूर्णांक ctl_no = e->reg;
	अचिन्हित पूर्णांक is_tx = e->tx;
	अचिन्हित पूर्णांक slot_channel_no;
	अचिन्हित पूर्णांक val, mux;
	u8 *map;

	map = is_tx ? sst_ssp_rx_map : sst_ssp_tx_map;

	val = 1 << ctl_no;
	mux = ucontrol->value.क्रमागतerated.item[0];
	अगर (mux > e->max - 1)
		वापस -EINVAL;

	mutex_lock(&drv->lock);
	/* first clear all रेजिस्टरs of this bit */
	क्रम (i = 0; i < e->max; i++)
		map[i] &= ~val;

	अगर (mux == 0) अणु
		/* kctl set to 'none' and we reset the bits so send IPC */
		ret = sst_check_and_send_slot_map(drv, kcontrol);

		mutex_unlock(&drv->lock);
		वापस ret;
	पूर्ण

	/* offset by one to take "None" पूर्णांकo account */
	slot_channel_no = mux - 1;
	map[slot_channel_no] |= val;

	dev_dbg(c->dev, "%s %s map = %#x\n",
			is_tx ? "tx channel" : "rx slot",
			e->texts[mux], map[slot_channel_no]);

	ret = sst_check_and_send_slot_map(drv, kcontrol);

	mutex_unlock(&drv->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक sst_send_algo_cmd(काष्ठा sst_data *drv,
			      काष्ठा sst_algo_control *bc)
अणु
	पूर्णांक len, ret = 0;
	काष्ठा sst_cmd_set_params *cmd;

	/*bc->max includes माप algos + length field*/
	len = माप(cmd->dst) + माप(cmd->command_id) + bc->max;

	cmd = kzalloc(len, GFP_KERNEL);
	अगर (cmd == शून्य)
		वापस -ENOMEM;

	SST_FILL_DESTINATION(2, cmd->dst, bc->pipe_id, bc->module_id);
	cmd->command_id = bc->cmd_id;
	स_नकल(cmd->params, bc->params, bc->max);

	ret = sst_fill_and_send_cmd_unlocked(drv, SST_IPC_IA_SET_PARAMS,
				SST_FLAG_BLOCKED, bc->task_id, 0, cmd, len);
	kमुक्त(cmd);
	वापस ret;
पूर्ण

/**
 * sst_find_and_send_pipe_algo - send all the algo parameters क्रम a pipe
 * @drv: sst_data
 * @pipe: string identअगरier
 * @ids: list of algorithms
 * The algos which are in each pipeline are sent to the firmware one by one
 *
 * Called with lock held
 */
अटल पूर्णांक sst_find_and_send_pipe_algo(काष्ठा sst_data *drv,
					स्थिर अक्षर *pipe, काष्ठा sst_ids *ids)
अणु
	पूर्णांक ret = 0;
	काष्ठा sst_algo_control *bc;
	काष्ठा sst_module *algo;

	dev_dbg(&drv->pdev->dev, "Enter: widget=%s\n", pipe);

	list_क्रम_each_entry(algo, &ids->algo_list, node) अणु
		bc = (व्योम *)algo->kctl->निजी_value;

		dev_dbg(&drv->pdev->dev, "Found algo control name=%s pipe=%s\n",
				algo->kctl->id.name, pipe);
		ret = sst_send_algo_cmd(drv, bc);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक sst_algo_bytes_ctl_info(काष्ठा snd_kcontrol *kcontrol,
			    काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा sst_algo_control *bc = (व्योम *)kcontrol->निजी_value;

	uinfo->type = SNDRV_CTL_ELEM_TYPE_BYTES;
	uinfo->count = bc->max;

	वापस 0;
पूर्ण

अटल पूर्णांक sst_algo_control_get(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा sst_algo_control *bc = (व्योम *)kcontrol->निजी_value;
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);

	चयन (bc->type) अणु
	हाल SST_ALGO_PARAMS:
		स_नकल(ucontrol->value.bytes.data, bc->params, bc->max);
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid Input- algo type:%d\n",
				bc->type);
		वापस -EINVAL;

	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक sst_algo_control_set(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	पूर्णांक ret = 0;
	काष्ठा snd_soc_component *cmpnt = snd_soc_kcontrol_component(kcontrol);
	काष्ठा sst_data *drv = snd_soc_component_get_drvdata(cmpnt);
	काष्ठा sst_algo_control *bc = (व्योम *)kcontrol->निजी_value;

	dev_dbg(cmpnt->dev, "control_name=%s\n", kcontrol->id.name);
	mutex_lock(&drv->lock);
	चयन (bc->type) अणु
	हाल SST_ALGO_PARAMS:
		स_नकल(bc->params, ucontrol->value.bytes.data, bc->max);
		अवरोध;
	शेष:
		mutex_unlock(&drv->lock);
		dev_err(cmpnt->dev, "Invalid Input- algo type:%d\n",
				bc->type);
		वापस -EINVAL;
	पूर्ण
	/*अगर pipe is enabled, need to send the algo params from here*/
	अगर (bc->w && bc->w->घातer)
		ret = sst_send_algo_cmd(drv, bc);
	mutex_unlock(&drv->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक sst_gain_ctl_info(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा sst_gain_mixer_control *mc = (व्योम *)kcontrol->निजी_value;

	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = mc->stereo ? 2 : 1;
	uinfo->value.पूर्णांकeger.min = mc->min;
	uinfo->value.पूर्णांकeger.max = mc->max;

	वापस 0;
पूर्ण

/**
 * sst_send_gain_cmd - send the gain algorithm IPC to the FW
 * @drv: sst_data
 * @gv:the stored value of gain (also contains rampduration)
 * @task_id: task index
 * @loc_id: location/position index
 * @module_id: module index
 * @mute: flag that indicates whether this was called from the
 *  digital_mute callback or directly. If called from the
 *  digital_mute callback, module will be muted/unmuted based on this
 *  flag. The flag is always 0 अगर called directly.
 *
 * Called with sst_data.lock held
 *
 * The user-set gain value is sent only अगर the user-controllable 'mute' control
 * is OFF (indicated by gv->mute). Otherwise, the mute value (MIN value) is
 * sent.
 */
अटल पूर्णांक sst_send_gain_cmd(काष्ठा sst_data *drv, काष्ठा sst_gain_value *gv,
			      u16 task_id, u16 loc_id, u16 module_id, पूर्णांक mute)
अणु
	काष्ठा sst_cmd_set_gain_dual cmd;

	dev_dbg(&drv->pdev->dev, "Enter\n");

	cmd.header.command_id = MMX_SET_GAIN;
	SST_FILL_DEFAULT_DESTINATION(cmd.header.dst);
	cmd.gain_cell_num = 1;

	अगर (mute || gv->mute) अणु
		cmd.cell_gains[0].cell_gain_left = SST_GAIN_MIN_VALUE;
		cmd.cell_gains[0].cell_gain_right = SST_GAIN_MIN_VALUE;
	पूर्ण अन्यथा अणु
		cmd.cell_gains[0].cell_gain_left = gv->l_gain;
		cmd.cell_gains[0].cell_gain_right = gv->r_gain;
	पूर्ण

	SST_FILL_DESTINATION(2, cmd.cell_gains[0].dest,
			     loc_id, module_id);
	cmd.cell_gains[0].gain_समय_स्थिरant = gv->ramp_duration;

	cmd.header.length = माप(काष्ठा sst_cmd_set_gain_dual)
				- माप(काष्ठा sst_dsp_header);

	/* we are with lock held, so call the unlocked api  to send */
	वापस sst_fill_and_send_cmd_unlocked(drv, SST_IPC_IA_SET_PARAMS,
				SST_FLAG_BLOCKED, task_id, 0, &cmd,
			      माप(cmd.header) + cmd.header.length);
पूर्ण

अटल पूर्णांक sst_gain_get(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	काष्ठा sst_gain_mixer_control *mc = (व्योम *)kcontrol->निजी_value;
	काष्ठा sst_gain_value *gv = mc->gain_val;

	चयन (mc->type) अणु
	हाल SST_GAIN_TLV:
		ucontrol->value.पूर्णांकeger.value[0] = gv->l_gain;
		ucontrol->value.पूर्णांकeger.value[1] = gv->r_gain;
		अवरोध;

	हाल SST_GAIN_MUTE:
		ucontrol->value.पूर्णांकeger.value[0] = gv->mute ? 0 : 1;
		अवरोध;

	हाल SST_GAIN_RAMP_DURATION:
		ucontrol->value.पूर्णांकeger.value[0] = gv->ramp_duration;
		अवरोध;

	शेष:
		dev_err(component->dev, "Invalid Input- gain type:%d\n",
				mc->type);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sst_gain_put(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	पूर्णांक ret = 0;
	काष्ठा snd_soc_component *cmpnt = snd_soc_kcontrol_component(kcontrol);
	काष्ठा sst_data *drv = snd_soc_component_get_drvdata(cmpnt);
	काष्ठा sst_gain_mixer_control *mc = (व्योम *)kcontrol->निजी_value;
	काष्ठा sst_gain_value *gv = mc->gain_val;

	mutex_lock(&drv->lock);

	चयन (mc->type) अणु
	हाल SST_GAIN_TLV:
		gv->l_gain = ucontrol->value.पूर्णांकeger.value[0];
		gv->r_gain = ucontrol->value.पूर्णांकeger.value[1];
		dev_dbg(cmpnt->dev, "%s: Volume %d, %d\n",
				mc->pname, gv->l_gain, gv->r_gain);
		अवरोध;

	हाल SST_GAIN_MUTE:
		gv->mute = !ucontrol->value.पूर्णांकeger.value[0];
		dev_dbg(cmpnt->dev, "%s: Mute %d\n", mc->pname, gv->mute);
		अवरोध;

	हाल SST_GAIN_RAMP_DURATION:
		gv->ramp_duration = ucontrol->value.पूर्णांकeger.value[0];
		dev_dbg(cmpnt->dev, "%s: Ramp Delay%d\n",
					mc->pname, gv->ramp_duration);
		अवरोध;

	शेष:
		mutex_unlock(&drv->lock);
		dev_err(cmpnt->dev, "Invalid Input- gain type:%d\n",
				mc->type);
		वापस -EINVAL;
	पूर्ण

	अगर (mc->w && mc->w->घातer)
		ret = sst_send_gain_cmd(drv, gv, mc->task_id,
			mc->pipe_id | mc->instance_id, mc->module_id, 0);
	mutex_unlock(&drv->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक sst_set_pipe_gain(काष्ठा sst_ids *ids,
				काष्ठा sst_data *drv, पूर्णांक mute);

अटल पूर्णांक sst_send_pipe_module_params(काष्ठा snd_soc_dapm_widget *w,
		काष्ठा snd_kcontrol *kcontrol)
अणु
	काष्ठा snd_soc_component *c = snd_soc_dapm_to_component(w->dapm);
	काष्ठा sst_data *drv = snd_soc_component_get_drvdata(c);
	काष्ठा sst_ids *ids = w->priv;

	mutex_lock(&drv->lock);
	sst_find_and_send_pipe_algo(drv, w->name, ids);
	sst_set_pipe_gain(ids, drv, 0);
	mutex_unlock(&drv->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक sst_generic_modules_event(काष्ठा snd_soc_dapm_widget *w,
				     काष्ठा snd_kcontrol *k, पूर्णांक event)
अणु
	अगर (SND_SOC_DAPM_EVENT_ON(event))
		वापस sst_send_pipe_module_params(w, k);
	वापस 0;
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(sst_gain_tlv_common, SST_GAIN_MIN_VALUE * 10, 10, 0);

/* Look up table to convert MIXER SW bit regs to SWM inमाला_दो */
अटल स्थिर uपूर्णांक swm_mixer_input_ids[SST_SWM_INPUT_COUNT] = अणु
	[SST_IP_MODEM]		= SST_SWM_IN_MODEM,
	[SST_IP_CODEC0]		= SST_SWM_IN_CODEC0,
	[SST_IP_CODEC1]		= SST_SWM_IN_CODEC1,
	[SST_IP_LOOP0]		= SST_SWM_IN_SPROT_LOOP,
	[SST_IP_LOOP1]		= SST_SWM_IN_MEDIA_LOOP1,
	[SST_IP_LOOP2]		= SST_SWM_IN_MEDIA_LOOP2,
	[SST_IP_PCM0]		= SST_SWM_IN_PCM0,
	[SST_IP_PCM1]		= SST_SWM_IN_PCM1,
	[SST_IP_MEDIA0]		= SST_SWM_IN_MEDIA0,
	[SST_IP_MEDIA1]		= SST_SWM_IN_MEDIA1,
	[SST_IP_MEDIA2]		= SST_SWM_IN_MEDIA2,
	[SST_IP_MEDIA3]		= SST_SWM_IN_MEDIA3,
पूर्ण;

/**
 * fill_swm_input - fill in the SWM input ids given the रेजिस्टर
 * @cmpnt: ASoC component
 * @swm_input: array of swm_input_ids
 * @reg: the रेजिस्टर value is a bit-field inicated which mixer inमाला_दो are ON.
 *
 * Use the lookup table to get the input-id and fill it in the
 * काष्ठाure.
 */
अटल पूर्णांक fill_swm_input(काष्ठा snd_soc_component *cmpnt,
		काष्ठा swm_input_ids *swm_input, अचिन्हित पूर्णांक reg)
अणु
	uपूर्णांक i, is_set, nb_inमाला_दो = 0;
	u16 input_loc_id;

	dev_dbg(cmpnt->dev, "reg: %#x\n", reg);
	क्रम (i = 0; i < SST_SWM_INPUT_COUNT; i++) अणु
		is_set = reg & BIT(i);
		अगर (!is_set)
			जारी;

		input_loc_id = swm_mixer_input_ids[i];
		SST_FILL_DESTINATION(2, swm_input->input_id,
				     input_loc_id, SST_DEFAULT_MODULE_ID);
		nb_inमाला_दो++;
		swm_input++;
		dev_dbg(cmpnt->dev, "input id: %#x, nb_inputs: %d\n",
				input_loc_id, nb_inमाला_दो);

		अगर (nb_inमाला_दो == SST_CMD_SWM_MAX_INPUTS) अणु
			dev_warn(cmpnt->dev, "SET_SWM cmd max inputs reached");
			अवरोध;
		पूर्ण
	पूर्ण
	वापस nb_inमाला_दो;
पूर्ण


/*
 * called with lock held
 */
अटल पूर्णांक sst_set_pipe_gain(काष्ठा sst_ids *ids,
			काष्ठा sst_data *drv, पूर्णांक mute)
अणु
	पूर्णांक ret = 0;
	काष्ठा sst_gain_mixer_control *mc;
	काष्ठा sst_gain_value *gv;
	काष्ठा sst_module *gain;

	list_क्रम_each_entry(gain, &ids->gain_list, node) अणु
		काष्ठा snd_kcontrol *kctl = gain->kctl;

		dev_dbg(&drv->pdev->dev, "control name=%s\n", kctl->id.name);
		mc = (व्योम *)kctl->निजी_value;
		gv = mc->gain_val;

		ret = sst_send_gain_cmd(drv, gv, mc->task_id,
			mc->pipe_id | mc->instance_id, mc->module_id, mute);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक sst_swm_mixer_event(काष्ठा snd_soc_dapm_widget *w,
			काष्ठा snd_kcontrol *k, पूर्णांक event)
अणु
	काष्ठा sst_cmd_set_swm cmd;
	काष्ठा snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	काष्ठा sst_data *drv = snd_soc_component_get_drvdata(cmpnt);
	काष्ठा sst_ids *ids = w->priv;
	bool set_mixer = false;
	काष्ठा soc_mixer_control *mc;
	पूर्णांक val = 0;
	पूर्णांक i = 0;

	dev_dbg(cmpnt->dev, "widget = %s\n", w->name);
	/*
	 * Identअगरy which mixer input is on and send the biपंचांगap of the
	 * inमाला_दो as an IPC to the DSP.
	 */
	क्रम (i = 0; i < w->num_kcontrols; i++) अणु
		अगर (dapm_kcontrol_get_value(w->kcontrols[i])) अणु
			mc = (काष्ठा soc_mixer_control *)(w->kcontrols[i])->निजी_value;
			val |= 1 << mc->shअगरt;
		पूर्ण
	पूर्ण
	dev_dbg(cmpnt->dev, "val = %#x\n", val);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
	हाल SND_SOC_DAPM_POST_PMD:
		set_mixer = true;
		अवरोध;
	हाल SND_SOC_DAPM_POST_REG:
		अगर (w->घातer)
			set_mixer = true;
		अवरोध;
	शेष:
		set_mixer = false;
	पूर्ण

	अगर (!set_mixer)
		वापस 0;

	अगर (SND_SOC_DAPM_EVENT_ON(event) ||
	    event == SND_SOC_DAPM_POST_REG)
		cmd.चयन_state = SST_SWM_ON;
	अन्यथा
		cmd.चयन_state = SST_SWM_OFF;

	SST_FILL_DEFAULT_DESTINATION(cmd.header.dst);
	/* MMX_SET_SWM == SBA_SET_SWM */
	cmd.header.command_id = SBA_SET_SWM;

	SST_FILL_DESTINATION(2, cmd.output_id,
			     ids->location_id, SST_DEFAULT_MODULE_ID);
	cmd.nb_inमाला_दो =	fill_swm_input(cmpnt, &cmd.input[0], val);
	cmd.header.length = दुरत्व(काष्ठा sst_cmd_set_swm, input)
				- माप(काष्ठा sst_dsp_header)
				+ (cmd.nb_inमाला_दो * माप(cmd.input[0]));

	वापस sst_fill_and_send_cmd(drv, SST_IPC_IA_CMD, SST_FLAG_BLOCKED,
			      ids->task_id, 0, &cmd,
			      माप(cmd.header) + cmd.header.length);
पूर्ण

/* SBA mixers - 16 inमाला_दो */
#घोषणा SST_SBA_DECLARE_MIX_CONTROLS(kctl_name)							\
	अटल स्थिर काष्ठा snd_kcontrol_new kctl_name[] = अणु					\
		SOC_DAPM_SINGLE("modem_in Switch", SND_SOC_NOPM, SST_IP_MODEM, 1, 0),		\
		SOC_DAPM_SINGLE("codec_in0 Switch", SND_SOC_NOPM, SST_IP_CODEC0, 1, 0),		\
		SOC_DAPM_SINGLE("codec_in1 Switch", SND_SOC_NOPM, SST_IP_CODEC1, 1, 0),		\
		SOC_DAPM_SINGLE("sprot_loop_in Switch", SND_SOC_NOPM, SST_IP_LOOP0, 1, 0),	\
		SOC_DAPM_SINGLE("media_loop1_in Switch", SND_SOC_NOPM, SST_IP_LOOP1, 1, 0),	\
		SOC_DAPM_SINGLE("media_loop2_in Switch", SND_SOC_NOPM, SST_IP_LOOP2, 1, 0),	\
		SOC_DAPM_SINGLE("pcm0_in Switch", SND_SOC_NOPM, SST_IP_PCM0, 1, 0),		\
		SOC_DAPM_SINGLE("pcm1_in Switch", SND_SOC_NOPM, SST_IP_PCM1, 1, 0),		\
	पूर्ण

#घोषणा SST_SBA_MIXER_GRAPH_MAP(mix_name)			\
	अणु mix_name, "modem_in Switch",	"modem_in" पूर्ण,		\
	अणु mix_name, "codec_in0 Switch",	"codec_in0" पूर्ण,		\
	अणु mix_name, "codec_in1 Switch",	"codec_in1" पूर्ण,		\
	अणु mix_name, "sprot_loop_in Switch",	"sprot_loop_in" पूर्ण,	\
	अणु mix_name, "media_loop1_in Switch",	"media_loop1_in" पूर्ण,	\
	अणु mix_name, "media_loop2_in Switch",	"media_loop2_in" पूर्ण,	\
	अणु mix_name, "pcm0_in Switch",		"pcm0_in" पूर्ण,		\
	अणु mix_name, "pcm1_in Switch",		"pcm1_in" पूर्ण

#घोषणा SST_MMX_DECLARE_MIX_CONTROLS(kctl_name)						\
	अटल स्थिर काष्ठा snd_kcontrol_new kctl_name[] = अणु				\
		SOC_DAPM_SINGLE("media0_in Switch", SND_SOC_NOPM, SST_IP_MEDIA0, 1, 0),	\
		SOC_DAPM_SINGLE("media1_in Switch", SND_SOC_NOPM, SST_IP_MEDIA1, 1, 0),	\
		SOC_DAPM_SINGLE("media2_in Switch", SND_SOC_NOPM, SST_IP_MEDIA2, 1, 0),	\
		SOC_DAPM_SINGLE("media3_in Switch", SND_SOC_NOPM, SST_IP_MEDIA3, 1, 0),	\
	पूर्ण

SST_MMX_DECLARE_MIX_CONTROLS(sst_mix_media0_controls);
SST_MMX_DECLARE_MIX_CONTROLS(sst_mix_media1_controls);

/* 18 SBA mixers */
SST_SBA_DECLARE_MIX_CONTROLS(sst_mix_pcm0_controls);
SST_SBA_DECLARE_MIX_CONTROLS(sst_mix_pcm1_controls);
SST_SBA_DECLARE_MIX_CONTROLS(sst_mix_pcm2_controls);
SST_SBA_DECLARE_MIX_CONTROLS(sst_mix_sprot_l0_controls);
SST_SBA_DECLARE_MIX_CONTROLS(sst_mix_media_l1_controls);
SST_SBA_DECLARE_MIX_CONTROLS(sst_mix_media_l2_controls);
SST_SBA_DECLARE_MIX_CONTROLS(__maybe_unused sst_mix_voip_controls);
SST_SBA_DECLARE_MIX_CONTROLS(sst_mix_codec0_controls);
SST_SBA_DECLARE_MIX_CONTROLS(sst_mix_codec1_controls);
SST_SBA_DECLARE_MIX_CONTROLS(sst_mix_modem_controls);

/*
 * sst_handle_vb_समयr - Start/Stop the DSP scheduler
 *
 * The DSP expects first cmd to be SBA_VB_START, so at first startup send
 * that.
 * DSP expects last cmd to be SBA_VB_IDLE, so at last shutकरोwn send that.
 *
 * Do refcount पूर्णांकernally so that we send command only at first start
 * and last end. Since SST driver करोes its own ref count, invoke sst's
 * घातer ops always!
 */
पूर्णांक sst_handle_vb_समयr(काष्ठा snd_soc_dai *dai, bool enable)
अणु
	पूर्णांक ret = 0;
	काष्ठा sst_cmd_generic cmd;
	काष्ठा sst_data *drv = snd_soc_dai_get_drvdata(dai);
	अटल पूर्णांक समयr_usage;

	अगर (enable)
		cmd.header.command_id = SBA_VB_START;
	अन्यथा
		cmd.header.command_id = SBA_IDLE;
	dev_dbg(dai->dev, "enable=%u, usage=%d\n", enable, समयr_usage);

	SST_FILL_DEFAULT_DESTINATION(cmd.header.dst);
	cmd.header.length = 0;

	अगर (enable) अणु
		ret = sst->ops->घातer(sst->dev, true);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	mutex_lock(&drv->lock);
	अगर (enable)
		समयr_usage++;
	अन्यथा
		समयr_usage--;

	/*
	 * Send the command only अगर this call is the first enable or last
	 * disable
	 */
	अगर ((enable && (समयr_usage == 1)) ||
	    (!enable && (समयr_usage == 0))) अणु
		ret = sst_fill_and_send_cmd_unlocked(drv, SST_IPC_IA_CMD,
				SST_FLAG_BLOCKED, SST_TASK_SBA, 0, &cmd,
				माप(cmd.header) + cmd.header.length);
		अगर (ret && enable) अणु
			समयr_usage--;
			enable  = false;
		पूर्ण
	पूर्ण
	mutex_unlock(&drv->lock);

	अगर (!enable)
		sst->ops->घातer(sst->dev, false);
	वापस ret;
पूर्ण

पूर्णांक sst_fill_ssp_slot(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक tx_mask,
		अचिन्हित पूर्णांक rx_mask, पूर्णांक slots, पूर्णांक slot_width)
अणु
	काष्ठा sst_data *ctx = snd_soc_dai_get_drvdata(dai);

	ctx->ssp_cmd.nb_slots = slots;
	ctx->ssp_cmd.active_tx_slot_map = tx_mask;
	ctx->ssp_cmd.active_rx_slot_map = rx_mask;
	ctx->ssp_cmd.nb_bits_per_slots = slot_width;

	वापस 0;
पूर्ण

अटल पूर्णांक sst_get_frame_sync_polarity(काष्ठा snd_soc_dai *dai,
		अचिन्हित पूर्णांक fmt)
अणु
	पूर्णांक क्रमmat;

	क्रमmat = fmt & SND_SOC_DAIFMT_INV_MASK;
	dev_dbg(dai->dev, "Enter:%s, format=%x\n", __func__, क्रमmat);

	चयन (क्रमmat) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
	हाल SND_SOC_DAIFMT_IB_NF:
		वापस SSP_FS_ACTIVE_HIGH;
	हाल SND_SOC_DAIFMT_NB_IF:
	हाल SND_SOC_DAIFMT_IB_IF:
		वापस SSP_FS_ACTIVE_LOW;
	शेष:
		dev_err(dai->dev, "Invalid frame sync polarity %d\n", क्रमmat);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक sst_get_ssp_mode(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	पूर्णांक क्रमmat;

	क्रमmat = (fmt & SND_SOC_DAIFMT_CLOCK_PROVIDER_MASK);
	dev_dbg(dai->dev, "Enter:%s, format=%x\n", __func__, क्रमmat);

	चयन (क्रमmat) अणु
	हाल SND_SOC_DAIFMT_CBC_CFC:
		वापस SSP_MODE_PROVIDER;
	हाल SND_SOC_DAIFMT_CBP_CFP:
		वापस SSP_MODE_CONSUMER;
	शेष:
		dev_err(dai->dev, "Invalid ssp protocol: %d\n", क्रमmat);
	पूर्ण

	वापस -EINVAL;
पूर्ण


पूर्णांक sst_fill_ssp_config(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	अचिन्हित पूर्णांक mode;
	पूर्णांक fs_polarity;
	काष्ठा sst_data *ctx = snd_soc_dai_get_drvdata(dai);

	mode = fmt & SND_SOC_DAIFMT_FORMAT_MASK;

	चयन (mode) अणु
	हाल SND_SOC_DAIFMT_DSP_B:
		ctx->ssp_cmd.ssp_protocol = SSP_MODE_PCM;
		ctx->ssp_cmd.mode = sst_get_ssp_mode(dai, fmt) | (SSP_PCM_MODE_NETWORK << 1);
		ctx->ssp_cmd.start_delay = 0;
		ctx->ssp_cmd.data_polarity = 1;
		ctx->ssp_cmd.frame_sync_width = 1;
		अवरोध;

	हाल SND_SOC_DAIFMT_DSP_A:
		ctx->ssp_cmd.ssp_protocol = SSP_MODE_PCM;
		ctx->ssp_cmd.mode = sst_get_ssp_mode(dai, fmt) | (SSP_PCM_MODE_NETWORK << 1);
		ctx->ssp_cmd.start_delay = 1;
		ctx->ssp_cmd.data_polarity = 1;
		ctx->ssp_cmd.frame_sync_width = 1;
		अवरोध;

	हाल SND_SOC_DAIFMT_I2S:
		ctx->ssp_cmd.ssp_protocol = SSP_MODE_I2S;
		ctx->ssp_cmd.mode = sst_get_ssp_mode(dai, fmt) | (SSP_PCM_MODE_NORMAL << 1);
		ctx->ssp_cmd.start_delay = 1;
		ctx->ssp_cmd.data_polarity = 0;
		ctx->ssp_cmd.frame_sync_width = ctx->ssp_cmd.nb_bits_per_slots;
		अवरोध;

	हाल SND_SOC_DAIFMT_LEFT_J:
		ctx->ssp_cmd.ssp_protocol = SSP_MODE_I2S;
		ctx->ssp_cmd.mode = sst_get_ssp_mode(dai, fmt) | (SSP_PCM_MODE_NORMAL << 1);
		ctx->ssp_cmd.start_delay = 0;
		ctx->ssp_cmd.data_polarity = 0;
		ctx->ssp_cmd.frame_sync_width = ctx->ssp_cmd.nb_bits_per_slots;
		अवरोध;

	शेष:
		dev_dbg(dai->dev, "using default ssp configs\n");
	पूर्ण

	fs_polarity = sst_get_frame_sync_polarity(dai, fmt);
	अगर (fs_polarity < 0)
		वापस fs_polarity;

	ctx->ssp_cmd.frame_sync_polarity = fs_polarity;

	वापस 0;
पूर्ण

/*
 * sst_ssp_config - contains SSP configuration क्रम media UC
 * this can be overwritten by set_dai_xxx APIs
 */
अटल स्थिर काष्ठा sst_ssp_config sst_ssp_configs = अणु
	.ssp_id = SSP_CODEC,
	.bits_per_slot = 24,
	.slots = 4,
	.ssp_mode = SSP_MODE_PROVIDER,
	.pcm_mode = SSP_PCM_MODE_NETWORK,
	.duplex = SSP_DUPLEX,
	.ssp_protocol = SSP_MODE_PCM,
	.fs_width = 1,
	.fs_frequency = SSP_FS_48_KHZ,
	.active_slot_map = 0xF,
	.start_delay = 0,
	.frame_sync_polarity = SSP_FS_ACTIVE_HIGH,
	.data_polarity = 1,
पूर्ण;

व्योम sst_fill_ssp_शेषs(काष्ठा snd_soc_dai *dai)
अणु
	स्थिर काष्ठा sst_ssp_config *config;
	काष्ठा sst_data *ctx = snd_soc_dai_get_drvdata(dai);

	config = &sst_ssp_configs;

	ctx->ssp_cmd.selection = config->ssp_id;
	ctx->ssp_cmd.nb_bits_per_slots = config->bits_per_slot;
	ctx->ssp_cmd.nb_slots = config->slots;
	ctx->ssp_cmd.mode = config->ssp_mode | (config->pcm_mode << 1);
	ctx->ssp_cmd.duplex = config->duplex;
	ctx->ssp_cmd.active_tx_slot_map = config->active_slot_map;
	ctx->ssp_cmd.active_rx_slot_map = config->active_slot_map;
	ctx->ssp_cmd.frame_sync_frequency = config->fs_frequency;
	ctx->ssp_cmd.frame_sync_polarity = config->frame_sync_polarity;
	ctx->ssp_cmd.data_polarity = config->data_polarity;
	ctx->ssp_cmd.frame_sync_width = config->fs_width;
	ctx->ssp_cmd.ssp_protocol = config->ssp_protocol;
	ctx->ssp_cmd.start_delay = config->start_delay;
	ctx->ssp_cmd.reserved1 = ctx->ssp_cmd.reserved2 = 0xFF;
पूर्ण

पूर्णांक send_ssp_cmd(काष्ठा snd_soc_dai *dai, स्थिर अक्षर *id, bool enable)
अणु
	काष्ठा sst_data *drv = snd_soc_dai_get_drvdata(dai);
	पूर्णांक ssp_id;

	dev_dbg(dai->dev, "Enter: enable=%d port_name=%s\n", enable, id);

	अगर (म_भेद(id, "ssp0-port") == 0)
		ssp_id = SSP_MODEM;
	अन्यथा अगर (म_भेद(id, "ssp2-port") == 0)
		ssp_id = SSP_CODEC;
	अन्यथा अणु
		dev_dbg(dai->dev, "port %s is not supported\n", id);
		वापस -1;
	पूर्ण

	SST_FILL_DEFAULT_DESTINATION(drv->ssp_cmd.header.dst);
	drv->ssp_cmd.header.command_id = SBA_HW_SET_SSP;
	drv->ssp_cmd.header.length = माप(काष्ठा sst_cmd_sba_hw_set_ssp)
				- माप(काष्ठा sst_dsp_header);

	drv->ssp_cmd.selection = ssp_id;
	dev_dbg(dai->dev, "ssp_id: %u\n", ssp_id);

	अगर (enable)
		drv->ssp_cmd.चयन_state = SST_SWITCH_ON;
	अन्यथा
		drv->ssp_cmd.चयन_state = SST_SWITCH_OFF;

	वापस sst_fill_and_send_cmd(drv, SST_IPC_IA_CMD, SST_FLAG_BLOCKED,
				SST_TASK_SBA, 0, &drv->ssp_cmd,
				माप(drv->ssp_cmd.header) + drv->ssp_cmd.header.length);
पूर्ण

अटल पूर्णांक sst_set_be_modules(काष्ठा snd_soc_dapm_widget *w,
			 काष्ठा snd_kcontrol *k, पूर्णांक event)
अणु
	पूर्णांक ret = 0;
	काष्ठा snd_soc_component *c = snd_soc_dapm_to_component(w->dapm);
	काष्ठा sst_data *drv = snd_soc_component_get_drvdata(c);

	dev_dbg(c->dev, "Enter: widget=%s\n", w->name);

	अगर (SND_SOC_DAPM_EVENT_ON(event)) अणु
		mutex_lock(&drv->lock);
		ret = sst_send_slot_map(drv);
		mutex_unlock(&drv->lock);
		अगर (ret)
			वापस ret;
		ret = sst_send_pipe_module_params(w, k);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक sst_set_media_path(काष्ठा snd_soc_dapm_widget *w,
			      काष्ठा snd_kcontrol *k, पूर्णांक event)
अणु
	पूर्णांक ret = 0;
	काष्ठा sst_cmd_set_media_path cmd;
	काष्ठा snd_soc_component *c = snd_soc_dapm_to_component(w->dapm);
	काष्ठा sst_data *drv = snd_soc_component_get_drvdata(c);
	काष्ठा sst_ids *ids = w->priv;

	dev_dbg(c->dev, "widget=%s\n", w->name);
	dev_dbg(c->dev, "task=%u, location=%#x\n",
				ids->task_id, ids->location_id);

	अगर (SND_SOC_DAPM_EVENT_ON(event))
		cmd.चयन_state = SST_PATH_ON;
	अन्यथा
		cmd.चयन_state = SST_PATH_OFF;

	SST_FILL_DESTINATION(2, cmd.header.dst,
			     ids->location_id, SST_DEFAULT_MODULE_ID);

	/* MMX_SET_MEDIA_PATH == SBA_SET_MEDIA_PATH */
	cmd.header.command_id = MMX_SET_MEDIA_PATH;
	cmd.header.length = माप(काष्ठा sst_cmd_set_media_path)
				- माप(काष्ठा sst_dsp_header);

	ret = sst_fill_and_send_cmd(drv, SST_IPC_IA_CMD, SST_FLAG_BLOCKED,
			      ids->task_id, 0, &cmd,
			      माप(cmd.header) + cmd.header.length);
	अगर (ret)
		वापस ret;

	अगर (SND_SOC_DAPM_EVENT_ON(event))
		ret = sst_send_pipe_module_params(w, k);
	वापस ret;
पूर्ण

अटल पूर्णांक sst_set_media_loop(काष्ठा snd_soc_dapm_widget *w,
			काष्ठा snd_kcontrol *k, पूर्णांक event)
अणु
	पूर्णांक ret = 0;
	काष्ठा sst_cmd_sba_set_media_loop_map cmd;
	काष्ठा snd_soc_component *c = snd_soc_dapm_to_component(w->dapm);
	काष्ठा sst_data *drv = snd_soc_component_get_drvdata(c);
	काष्ठा sst_ids *ids = w->priv;

	dev_dbg(c->dev, "Enter:widget=%s\n", w->name);
	अगर (SND_SOC_DAPM_EVENT_ON(event))
		cmd.चयन_state = SST_SWITCH_ON;
	अन्यथा
		cmd.चयन_state = SST_SWITCH_OFF;

	SST_FILL_DESTINATION(2, cmd.header.dst,
			     ids->location_id, SST_DEFAULT_MODULE_ID);

	cmd.header.command_id = SBA_SET_MEDIA_LOOP_MAP;
	cmd.header.length = माप(काष्ठा sst_cmd_sba_set_media_loop_map)
				 - माप(काष्ठा sst_dsp_header);
	cmd.param.part.cfg.rate = 2; /* 48khz */

	cmd.param.part.cfg.क्रमmat = ids->क्रमmat; /* stereo/Mono */
	cmd.param.part.cfg.s_length = 1; /* 24bit left justअगरied */
	cmd.map = 0; /* Algo sequence: Gain - DRP - FIR - IIR */

	ret = sst_fill_and_send_cmd(drv, SST_IPC_IA_CMD, SST_FLAG_BLOCKED,
			      SST_TASK_SBA, 0, &cmd,
			      माप(cmd.header) + cmd.header.length);
	अगर (ret)
		वापस ret;

	अगर (SND_SOC_DAPM_EVENT_ON(event))
		ret = sst_send_pipe_module_params(w, k);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget sst_dapm_widमाला_लो[] = अणु
	SST_AIF_IN("modem_in", sst_set_be_modules),
	SST_AIF_IN("codec_in0", sst_set_be_modules),
	SST_AIF_IN("codec_in1", sst_set_be_modules),
	SST_AIF_OUT("modem_out", sst_set_be_modules),
	SST_AIF_OUT("codec_out0", sst_set_be_modules),
	SST_AIF_OUT("codec_out1", sst_set_be_modules),

	/* Media Paths */
	/* MediaX IN paths are set via ALLOC, so no SET_MEDIA_PATH command */
	SST_PATH_INPUT("media0_in", SST_TASK_MMX, SST_SWM_IN_MEDIA0, sst_generic_modules_event),
	SST_PATH_INPUT("media1_in", SST_TASK_MMX, SST_SWM_IN_MEDIA1, शून्य),
	SST_PATH_INPUT("media2_in", SST_TASK_MMX, SST_SWM_IN_MEDIA2, sst_set_media_path),
	SST_PATH_INPUT("media3_in", SST_TASK_MMX, SST_SWM_IN_MEDIA3, शून्य),
	SST_PATH_OUTPUT("media0_out", SST_TASK_MMX, SST_SWM_OUT_MEDIA0, sst_set_media_path),
	SST_PATH_OUTPUT("media1_out", SST_TASK_MMX, SST_SWM_OUT_MEDIA1, sst_set_media_path),

	/* SBA PCM Paths */
	SST_PATH_INPUT("pcm0_in", SST_TASK_SBA, SST_SWM_IN_PCM0, sst_set_media_path),
	SST_PATH_INPUT("pcm1_in", SST_TASK_SBA, SST_SWM_IN_PCM1, sst_set_media_path),
	SST_PATH_OUTPUT("pcm0_out", SST_TASK_SBA, SST_SWM_OUT_PCM0, sst_set_media_path),
	SST_PATH_OUTPUT("pcm1_out", SST_TASK_SBA, SST_SWM_OUT_PCM1, sst_set_media_path),
	SST_PATH_OUTPUT("pcm2_out", SST_TASK_SBA, SST_SWM_OUT_PCM2, sst_set_media_path),

	/* SBA Loops */
	SST_PATH_INPUT("sprot_loop_in", SST_TASK_SBA, SST_SWM_IN_SPROT_LOOP, शून्य),
	SST_PATH_INPUT("media_loop1_in", SST_TASK_SBA, SST_SWM_IN_MEDIA_LOOP1, शून्य),
	SST_PATH_INPUT("media_loop2_in", SST_TASK_SBA, SST_SWM_IN_MEDIA_LOOP2, शून्य),
	SST_PATH_MEDIA_LOOP_OUTPUT("sprot_loop_out", SST_TASK_SBA, SST_SWM_OUT_SPROT_LOOP, SST_FMT_STEREO, sst_set_media_loop),
	SST_PATH_MEDIA_LOOP_OUTPUT("media_loop1_out", SST_TASK_SBA, SST_SWM_OUT_MEDIA_LOOP1, SST_FMT_STEREO, sst_set_media_loop),
	SST_PATH_MEDIA_LOOP_OUTPUT("media_loop2_out", SST_TASK_SBA, SST_SWM_OUT_MEDIA_LOOP2, SST_FMT_STEREO, sst_set_media_loop),

	/* Media Mixers */
	SST_SWM_MIXER("media0_out mix 0", SND_SOC_NOPM, SST_TASK_MMX, SST_SWM_OUT_MEDIA0,
		      sst_mix_media0_controls, sst_swm_mixer_event),
	SST_SWM_MIXER("media1_out mix 0", SND_SOC_NOPM, SST_TASK_MMX, SST_SWM_OUT_MEDIA1,
		      sst_mix_media1_controls, sst_swm_mixer_event),

	/* SBA PCM mixers */
	SST_SWM_MIXER("pcm0_out mix 0", SND_SOC_NOPM, SST_TASK_SBA, SST_SWM_OUT_PCM0,
		      sst_mix_pcm0_controls, sst_swm_mixer_event),
	SST_SWM_MIXER("pcm1_out mix 0", SND_SOC_NOPM, SST_TASK_SBA, SST_SWM_OUT_PCM1,
		      sst_mix_pcm1_controls, sst_swm_mixer_event),
	SST_SWM_MIXER("pcm2_out mix 0", SND_SOC_NOPM, SST_TASK_SBA, SST_SWM_OUT_PCM2,
		      sst_mix_pcm2_controls, sst_swm_mixer_event),

	/* SBA Loop mixers */
	SST_SWM_MIXER("sprot_loop_out mix 0", SND_SOC_NOPM, SST_TASK_SBA, SST_SWM_OUT_SPROT_LOOP,
		      sst_mix_sprot_l0_controls, sst_swm_mixer_event),
	SST_SWM_MIXER("media_loop1_out mix 0", SND_SOC_NOPM, SST_TASK_SBA, SST_SWM_OUT_MEDIA_LOOP1,
		      sst_mix_media_l1_controls, sst_swm_mixer_event),
	SST_SWM_MIXER("media_loop2_out mix 0", SND_SOC_NOPM, SST_TASK_SBA, SST_SWM_OUT_MEDIA_LOOP2,
		      sst_mix_media_l2_controls, sst_swm_mixer_event),

	/* SBA Backend mixers */
	SST_SWM_MIXER("codec_out0 mix 0", SND_SOC_NOPM, SST_TASK_SBA, SST_SWM_OUT_CODEC0,
		      sst_mix_codec0_controls, sst_swm_mixer_event),
	SST_SWM_MIXER("codec_out1 mix 0", SND_SOC_NOPM, SST_TASK_SBA, SST_SWM_OUT_CODEC1,
		      sst_mix_codec1_controls, sst_swm_mixer_event),
	SST_SWM_MIXER("modem_out mix 0", SND_SOC_NOPM, SST_TASK_SBA, SST_SWM_OUT_MODEM,
		      sst_mix_modem_controls, sst_swm_mixer_event),

पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route पूर्णांकercon[] = अणु
	अणु"media0_in", शून्य, "Compress Playback"पूर्ण,
	अणु"media1_in", शून्य, "Headset Playback"पूर्ण,
	अणु"media2_in", शून्य, "pcm0_out"पूर्ण,
	अणु"media3_in", शून्य, "Deepbuffer Playback"पूर्ण,

	अणु"media0_out mix 0", "media0_in Switch", "media0_in"पूर्ण,
	अणु"media0_out mix 0", "media1_in Switch", "media1_in"पूर्ण,
	अणु"media0_out mix 0", "media2_in Switch", "media2_in"पूर्ण,
	अणु"media0_out mix 0", "media3_in Switch", "media3_in"पूर्ण,
	अणु"media1_out mix 0", "media0_in Switch", "media0_in"पूर्ण,
	अणु"media1_out mix 0", "media1_in Switch", "media1_in"पूर्ण,
	अणु"media1_out mix 0", "media2_in Switch", "media2_in"पूर्ण,
	अणु"media1_out mix 0", "media3_in Switch", "media3_in"पूर्ण,

	अणु"media0_out", शून्य, "media0_out mix 0"पूर्ण,
	अणु"media1_out", शून्य, "media1_out mix 0"पूर्ण,
	अणु"pcm0_in", शून्य, "media0_out"पूर्ण,
	अणु"pcm1_in", शून्य, "media1_out"पूर्ण,

	अणु"Headset Capture", शून्य, "pcm1_out"पूर्ण,
	अणु"Headset Capture", शून्य, "pcm2_out"पूर्ण,
	अणु"pcm0_out", शून्य, "pcm0_out mix 0"पूर्ण,
	SST_SBA_MIXER_GRAPH_MAP("pcm0_out mix 0"),
	अणु"pcm1_out", शून्य, "pcm1_out mix 0"पूर्ण,
	SST_SBA_MIXER_GRAPH_MAP("pcm1_out mix 0"),
	अणु"pcm2_out", शून्य, "pcm2_out mix 0"पूर्ण,
	SST_SBA_MIXER_GRAPH_MAP("pcm2_out mix 0"),

	अणु"media_loop1_in", शून्य, "media_loop1_out"पूर्ण,
	अणु"media_loop1_out", शून्य, "media_loop1_out mix 0"पूर्ण,
	SST_SBA_MIXER_GRAPH_MAP("media_loop1_out mix 0"),
	अणु"media_loop2_in", शून्य, "media_loop2_out"पूर्ण,
	अणु"media_loop2_out", शून्य, "media_loop2_out mix 0"पूर्ण,
	SST_SBA_MIXER_GRAPH_MAP("media_loop2_out mix 0"),
	अणु"sprot_loop_in", शून्य, "sprot_loop_out"पूर्ण,
	अणु"sprot_loop_out", शून्य, "sprot_loop_out mix 0"पूर्ण,
	SST_SBA_MIXER_GRAPH_MAP("sprot_loop_out mix 0"),

	अणु"codec_out0", शून्य, "codec_out0 mix 0"पूर्ण,
	SST_SBA_MIXER_GRAPH_MAP("codec_out0 mix 0"),
	अणु"codec_out1", शून्य, "codec_out1 mix 0"पूर्ण,
	SST_SBA_MIXER_GRAPH_MAP("codec_out1 mix 0"),
	अणु"modem_out", शून्य, "modem_out mix 0"पूर्ण,
	SST_SBA_MIXER_GRAPH_MAP("modem_out mix 0"),


पूर्ण;
अटल स्थिर अक्षर * स्थिर slot_names[] = अणु
	"none",
	"slot 0", "slot 1", "slot 2", "slot 3",
	"slot 4", "slot 5", "slot 6", "slot 7", /* not supported by FW */
पूर्ण;

अटल स्थिर अक्षर * स्थिर channel_names[] = अणु
	"none",
	"codec_out0_0", "codec_out0_1", "codec_out1_0", "codec_out1_1",
	"codec_out2_0", "codec_out2_1", "codec_out3_0", "codec_out3_1", /* not supported by FW */
पूर्ण;

#घोषणा SST_INTERLEAVER(xpname, slot_name, slotno) \
	SST_SSP_SLOT_CTL(xpname, "tx interleaver", slot_name, slotno, true, \
			 channel_names, sst_slot_get, sst_slot_put)

#घोषणा SST_DEINTERLEAVER(xpname, channel_name, channel_no) \
	SST_SSP_SLOT_CTL(xpname, "rx deinterleaver", channel_name, channel_no, false, \
			 slot_names, sst_slot_get, sst_slot_put)

अटल स्थिर काष्ठा snd_kcontrol_new sst_slot_controls[] = अणु
	SST_INTERLEAVER("codec_out", "slot 0", 0),
	SST_INTERLEAVER("codec_out", "slot 1", 1),
	SST_INTERLEAVER("codec_out", "slot 2", 2),
	SST_INTERLEAVER("codec_out", "slot 3", 3),
	SST_DEINTERLEAVER("codec_in", "codec_in0_0", 0),
	SST_DEINTERLEAVER("codec_in", "codec_in0_1", 1),
	SST_DEINTERLEAVER("codec_in", "codec_in1_0", 2),
	SST_DEINTERLEAVER("codec_in", "codec_in1_1", 3),
पूर्ण;

/* Gain helper with min/max set */
#घोषणा SST_GAIN(name, path_id, task_id, instance, gain_var)				\
	SST_GAIN_KCONTROLS(name, "Gain", SST_GAIN_MIN_VALUE, SST_GAIN_MAX_VALUE,	\
		SST_GAIN_TC_MIN, SST_GAIN_TC_MAX,					\
		sst_gain_get, sst_gain_put,						\
		SST_MODULE_ID_GAIN_CELL, path_id, instance, task_id,			\
		sst_gain_tlv_common, gain_var)

#घोषणा SST_VOLUME(name, path_id, task_id, instance, gain_var)				\
	SST_GAIN_KCONTROLS(name, "Volume", SST_GAIN_MIN_VALUE, SST_GAIN_MAX_VALUE,	\
		SST_GAIN_TC_MIN, SST_GAIN_TC_MAX,					\
		sst_gain_get, sst_gain_put,						\
		SST_MODULE_ID_VOLUME, path_id, instance, task_id,			\
		sst_gain_tlv_common, gain_var)

अटल काष्ठा sst_gain_value sst_gains[];

अटल स्थिर काष्ठा snd_kcontrol_new sst_gain_controls[] = अणु
	SST_GAIN("media0_in", SST_PATH_INDEX_MEDIA0_IN, SST_TASK_MMX, 0, &sst_gains[0]),
	SST_GAIN("media1_in", SST_PATH_INDEX_MEDIA1_IN, SST_TASK_MMX, 0, &sst_gains[1]),
	SST_GAIN("media2_in", SST_PATH_INDEX_MEDIA2_IN, SST_TASK_MMX, 0, &sst_gains[2]),
	SST_GAIN("media3_in", SST_PATH_INDEX_MEDIA3_IN, SST_TASK_MMX, 0, &sst_gains[3]),

	SST_GAIN("pcm0_in", SST_PATH_INDEX_PCM0_IN, SST_TASK_SBA, 0, &sst_gains[4]),
	SST_GAIN("pcm1_in", SST_PATH_INDEX_PCM1_IN, SST_TASK_SBA, 0, &sst_gains[5]),
	SST_GAIN("pcm1_out", SST_PATH_INDEX_PCM1_OUT, SST_TASK_SBA, 0, &sst_gains[6]),
	SST_GAIN("pcm2_out", SST_PATH_INDEX_PCM2_OUT, SST_TASK_SBA, 0, &sst_gains[7]),

	SST_GAIN("codec_in0", SST_PATH_INDEX_CODEC_IN0, SST_TASK_SBA, 0, &sst_gains[8]),
	SST_GAIN("codec_in1", SST_PATH_INDEX_CODEC_IN1, SST_TASK_SBA, 0, &sst_gains[9]),
	SST_GAIN("codec_out0", SST_PATH_INDEX_CODEC_OUT0, SST_TASK_SBA, 0, &sst_gains[10]),
	SST_GAIN("codec_out1", SST_PATH_INDEX_CODEC_OUT1, SST_TASK_SBA, 0, &sst_gains[11]),
	SST_GAIN("media_loop1_out", SST_PATH_INDEX_MEDIA_LOOP1_OUT, SST_TASK_SBA, 0, &sst_gains[12]),
	SST_GAIN("media_loop2_out", SST_PATH_INDEX_MEDIA_LOOP2_OUT, SST_TASK_SBA, 0, &sst_gains[13]),
	SST_GAIN("sprot_loop_out", SST_PATH_INDEX_SPROT_LOOP_OUT, SST_TASK_SBA, 0, &sst_gains[14]),
	SST_VOLUME("media0_in", SST_PATH_INDEX_MEDIA0_IN, SST_TASK_MMX, 0, &sst_gains[15]),
	SST_GAIN("modem_in", SST_PATH_INDEX_MODEM_IN, SST_TASK_SBA, 0, &sst_gains[16]),
	SST_GAIN("modem_out", SST_PATH_INDEX_MODEM_OUT, SST_TASK_SBA, 0, &sst_gains[17]),

पूर्ण;

#घोषणा SST_GAIN_NUM_CONTROLS 3
/* the SST_GAIN macro above will create three alsa controls क्रम each
 * instance invoked, gain, mute and ramp duration, which use the same gain
 * cell sst_gain to keep track of data
 * To calculate number of gain cell instances we need to device by 3 in
 * below caulcation क्रम gain cell memory.
 * This माला_लो rid of अटल number and issues जबतक adding new controls
 */
अटल काष्ठा sst_gain_value sst_gains[ARRAY_SIZE(sst_gain_controls)/SST_GAIN_NUM_CONTROLS];

अटल स्थिर काष्ठा snd_kcontrol_new sst_algo_controls[] = अणु
	SST_ALGO_KCONTROL_BYTES("media_loop1_out", "fir", 272, SST_MODULE_ID_FIR_24,
		 SST_PATH_INDEX_MEDIA_LOOP1_OUT, 0, SST_TASK_SBA, SBA_VB_SET_FIR),
	SST_ALGO_KCONTROL_BYTES("media_loop1_out", "iir", 300, SST_MODULE_ID_IIR_24,
		SST_PATH_INDEX_MEDIA_LOOP1_OUT, 0, SST_TASK_SBA, SBA_VB_SET_IIR),
	SST_ALGO_KCONTROL_BYTES("media_loop1_out", "mdrp", 286, SST_MODULE_ID_MDRP,
		SST_PATH_INDEX_MEDIA_LOOP1_OUT, 0, SST_TASK_SBA, SBA_SET_MDRP),
	SST_ALGO_KCONTROL_BYTES("media_loop2_out", "fir", 272, SST_MODULE_ID_FIR_24,
		SST_PATH_INDEX_MEDIA_LOOP2_OUT, 0, SST_TASK_SBA, SBA_VB_SET_FIR),
	SST_ALGO_KCONTROL_BYTES("media_loop2_out", "iir", 300, SST_MODULE_ID_IIR_24,
		SST_PATH_INDEX_MEDIA_LOOP2_OUT, 0, SST_TASK_SBA, SBA_VB_SET_IIR),
	SST_ALGO_KCONTROL_BYTES("media_loop2_out", "mdrp", 286, SST_MODULE_ID_MDRP,
		SST_PATH_INDEX_MEDIA_LOOP2_OUT, 0, SST_TASK_SBA, SBA_SET_MDRP),
	SST_ALGO_KCONTROL_BYTES("sprot_loop_out", "lpro", 192, SST_MODULE_ID_SPROT,
		SST_PATH_INDEX_SPROT_LOOP_OUT, 0, SST_TASK_SBA, SBA_VB_LPRO),
	SST_ALGO_KCONTROL_BYTES("codec_in0", "dcr", 52, SST_MODULE_ID_FILT_DCR,
		SST_PATH_INDEX_CODEC_IN0, 0, SST_TASK_SBA, SBA_VB_SET_IIR),
	SST_ALGO_KCONTROL_BYTES("codec_in1", "dcr", 52, SST_MODULE_ID_FILT_DCR,
		SST_PATH_INDEX_CODEC_IN1, 0, SST_TASK_SBA, SBA_VB_SET_IIR),

पूर्ण;

अटल पूर्णांक sst_algo_control_init(काष्ठा device *dev)
अणु
	पूर्णांक i = 0;
	काष्ठा sst_algo_control *bc;
	/*allocate space to cache the algo parameters in the driver*/
	क्रम (i = 0; i < ARRAY_SIZE(sst_algo_controls); i++) अणु
		bc = (काष्ठा sst_algo_control *)sst_algo_controls[i].निजी_value;
		bc->params = devm_kzalloc(dev, bc->max, GFP_KERNEL);
		अगर (bc->params == शून्य)
			वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

अटल bool is_sst_dapm_widget(काष्ठा snd_soc_dapm_widget *w)
अणु
	चयन (w->id) अणु
	हाल snd_soc_dapm_pga:
	हाल snd_soc_dapm_aअगर_in:
	हाल snd_soc_dapm_aअगर_out:
	हाल snd_soc_dapm_input:
	हाल snd_soc_dapm_output:
	हाल snd_soc_dapm_mixer:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

/**
 * sst_send_pipe_gains - send gains क्रम the front-end DAIs
 * @dai: front-end dai
 * @stream: direction
 * @mute: boolean indicating mute status
 *
 * The gains in the pipes connected to the front-ends are muted/unmuted
 * स्वतःmatically via the digital_mute() DAPM callback. This function sends the
 * gains क्रम the front-end pipes.
 */
पूर्णांक sst_send_pipe_gains(काष्ठा snd_soc_dai *dai, पूर्णांक stream, पूर्णांक mute)
अणु
	काष्ठा sst_data *drv = snd_soc_dai_get_drvdata(dai);
	काष्ठा snd_soc_dapm_widget *w;
	काष्ठा snd_soc_dapm_path *p = शून्य;

	dev_dbg(dai->dev, "enter, dai-name=%s dir=%d\n", dai->name, stream);

	अगर (stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		dev_dbg(dai->dev, "Stream name=%s\n",
				dai->playback_widget->name);
		w = dai->playback_widget;
		snd_soc_dapm_widget_क्रम_each_sink_path(w, p) अणु
			अगर (p->connected && !p->connected(w, p->sink))
				जारी;

			अगर (p->connect && p->sink->घातer &&
					is_sst_dapm_widget(p->sink)) अणु
				काष्ठा sst_ids *ids = p->sink->priv;

				dev_dbg(dai->dev, "send gains for widget=%s\n",
						p->sink->name);
				mutex_lock(&drv->lock);
				sst_set_pipe_gain(ids, drv, mute);
				mutex_unlock(&drv->lock);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_dbg(dai->dev, "Stream name=%s\n",
				dai->capture_widget->name);
		w = dai->capture_widget;
		snd_soc_dapm_widget_क्रम_each_source_path(w, p) अणु
			अगर (p->connected && !p->connected(w, p->source))
				जारी;

			अगर (p->connect &&  p->source->घातer &&
					is_sst_dapm_widget(p->source)) अणु
				काष्ठा sst_ids *ids = p->source->priv;

				dev_dbg(dai->dev, "send gain for widget=%s\n",
						p->source->name);
				mutex_lock(&drv->lock);
				sst_set_pipe_gain(ids, drv, mute);
				mutex_unlock(&drv->lock);
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/**
 * sst_fill_module_list - populate the list of modules/gains क्रम a pipe
 * @kctl: kcontrol poपूर्णांकer
 * @w: dapm widget
 * @type: widget type
 *
 * Fills the widget poपूर्णांकer in the kcontrol निजी data, and also fills the
 * kcontrol poपूर्णांकer in the widget निजी data.
 *
 * Widget poपूर्णांकer is used to send the algo/gain in the .put() handler अगर the
 * widget is घातerd on.
 *
 * Kcontrol poपूर्णांकer is used to send the algo/gain in the widget घातer ON/OFF
 * event handler. Each widget (pipe) has multiple algos stored in the algo_list.
 */
अटल पूर्णांक sst_fill_module_list(काष्ठा snd_kcontrol *kctl,
	 काष्ठा snd_soc_dapm_widget *w, पूर्णांक type)
अणु
	काष्ठा sst_module *module = शून्य;
	काष्ठा snd_soc_component *c = snd_soc_dapm_to_component(w->dapm);
	काष्ठा sst_ids *ids = w->priv;
	पूर्णांक ret = 0;

	module = devm_kzalloc(c->dev, माप(*module), GFP_KERNEL);
	अगर (!module)
		वापस -ENOMEM;

	अगर (type == SST_MODULE_GAIN) अणु
		काष्ठा sst_gain_mixer_control *mc = (व्योम *)kctl->निजी_value;

		mc->w = w;
		module->kctl = kctl;
		list_add_tail(&module->node, &ids->gain_list);
	पूर्ण अन्यथा अगर (type == SST_MODULE_ALGO) अणु
		काष्ठा sst_algo_control *bc = (व्योम *)kctl->निजी_value;

		bc->w = w;
		module->kctl = kctl;
		list_add_tail(&module->node, &ids->algo_list);
	पूर्ण अन्यथा अणु
		dev_err(c->dev, "invoked for unknown type %d module %s",
				type, kctl->id.name);
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * sst_fill_widget_module_info - fill list of gains/algos क्रम the pipe
 * @w: pipe modeled as a DAPM widget
 * @component: ASoC component
 *
 * Fill the list of gains/algos क्रम the widget by looking at all the card
 * controls and comparing the name of the widget with the first part of control
 * name. First part of control name contains the pipe name (widget name).
 */
अटल पूर्णांक sst_fill_widget_module_info(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_soc_component *component)
अणु
	काष्ठा snd_kcontrol *kctl;
	पूर्णांक index, ret = 0;
	काष्ठा snd_card *card = component->card->snd_card;
	अक्षर *idx;

	करोwn_पढ़ो(&card->controls_rwsem);

	list_क्रम_each_entry(kctl, &card->controls, list) अणु
		idx = म_अक्षर(kctl->id.name, ' ');
		अगर (idx == शून्य)
			जारी;
		index = idx - (अक्षर*)kctl->id.name;
		अगर (म_भेदन(kctl->id.name, w->name, index))
			जारी;

		अगर (म_माला(kctl->id.name, "Volume"))
			ret = sst_fill_module_list(kctl, w, SST_MODULE_GAIN);

		अन्यथा अगर (म_माला(kctl->id.name, "params"))
			ret = sst_fill_module_list(kctl, w, SST_MODULE_ALGO);

		अन्यथा अगर (म_माला(kctl->id.name, "Switch") &&
			 म_माला(kctl->id.name, "Gain")) अणु
			काष्ठा sst_gain_mixer_control *mc =
						(व्योम *)kctl->निजी_value;

			mc->w = w;

		पूर्ण अन्यथा अगर (म_माला(kctl->id.name, "interleaver")) अणु
			काष्ठा sst_क्रमागत *e = (व्योम *)kctl->निजी_value;

			e->w = w;

		पूर्ण अन्यथा अगर (म_माला(kctl->id.name, "deinterleaver")) अणु
			काष्ठा sst_क्रमागत *e = (व्योम *)kctl->निजी_value;

			e->w = w;
		पूर्ण

		अगर (ret < 0) अणु
			up_पढ़ो(&card->controls_rwsem);
			वापस ret;
		पूर्ण
	पूर्ण

	up_पढ़ो(&card->controls_rwsem);
	वापस 0;
पूर्ण

/**
 * sst_fill_linked_widमाला_लो - fill the parent poपूर्णांकer क्रम the linked widget
 * @component: ASoC component
 * @ids: sst_ids array
 */
अटल व्योम sst_fill_linked_widमाला_लो(काष्ठा snd_soc_component *component,
						काष्ठा sst_ids *ids)
अणु
	काष्ठा snd_soc_dapm_widget *w;
	अचिन्हित पूर्णांक len = म_माप(ids->parent_wname);

	list_क्रम_each_entry(w, &component->card->widमाला_लो, list) अणु
		अगर (!म_भेदन(ids->parent_wname, w->name, len)) अणु
			ids->parent_w = w;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * sst_map_modules_to_pipe - fill algo/gains list क्रम all pipes
 * @component: ASoC component
 */
अटल पूर्णांक sst_map_modules_to_pipe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा snd_soc_dapm_widget *w;
	पूर्णांक ret = 0;

	list_क्रम_each_entry(w, &component->card->widमाला_लो, list) अणु
		अगर (is_sst_dapm_widget(w) && (w->priv)) अणु
			काष्ठा sst_ids *ids = w->priv;

			dev_dbg(component->dev, "widget type=%d name=%s\n",
					w->id, w->name);
			INIT_LIST_HEAD(&ids->algo_list);
			INIT_LIST_HEAD(&ids->gain_list);
			ret = sst_fill_widget_module_info(w, component);

			अगर (ret < 0)
				वापस ret;

			/* fill linked widमाला_लो */
			अगर (ids->parent_wname !=  शून्य)
				sst_fill_linked_widमाला_लो(component, ids);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक sst_dsp_init_v2_dpcm(काष्ठा snd_soc_component *component)
अणु
	पूर्णांक i, ret = 0;
	काष्ठा snd_soc_dapm_context *dapm =
			snd_soc_component_get_dapm(component);
	काष्ठा sst_data *drv = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक gains = ARRAY_SIZE(sst_gain_controls)/3;

	drv->byte_stream = devm_kzalloc(component->dev,
					SST_MAX_BIN_BYTES, GFP_KERNEL);
	अगर (!drv->byte_stream)
		वापस -ENOMEM;

	snd_soc_dapm_new_controls(dapm, sst_dapm_widमाला_लो,
			ARRAY_SIZE(sst_dapm_widमाला_लो));
	snd_soc_dapm_add_routes(dapm, पूर्णांकercon,
			ARRAY_SIZE(पूर्णांकercon));
	snd_soc_dapm_new_widमाला_लो(dapm->card);

	क्रम (i = 0; i < gains; i++) अणु
		sst_gains[i].mute = SST_GAIN_MUTE_DEFAULT;
		sst_gains[i].l_gain = SST_GAIN_VOLUME_DEFAULT;
		sst_gains[i].r_gain = SST_GAIN_VOLUME_DEFAULT;
		sst_gains[i].ramp_duration = SST_GAIN_RAMP_DURATION_DEFAULT;
	पूर्ण

	ret = snd_soc_add_component_controls(component, sst_gain_controls,
			ARRAY_SIZE(sst_gain_controls));
	अगर (ret)
		वापस ret;

	/* Initialize algo control params */
	ret = sst_algo_control_init(component->dev);
	अगर (ret)
		वापस ret;
	ret = snd_soc_add_component_controls(component, sst_algo_controls,
			ARRAY_SIZE(sst_algo_controls));
	अगर (ret)
		वापस ret;

	ret = snd_soc_add_component_controls(component, sst_slot_controls,
			ARRAY_SIZE(sst_slot_controls));
	अगर (ret)
		वापस ret;

	ret = sst_map_modules_to_pipe(component);

	वापस ret;
पूर्ण
