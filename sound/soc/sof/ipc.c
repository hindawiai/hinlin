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
// Generic IPC layer that can work over MMIO and SPI/I2C. PHY layer provided
// by platक्रमm driver code.
//

#समावेश <linux/mutex.h>
#समावेश <linux/types.h>

#समावेश "sof-priv.h"
#समावेश "sof-audio.h"
#समावेश "ops.h"

अटल व्योम ipc_trace_message(काष्ठा snd_sof_dev *sdev, u32 msg_id);
अटल व्योम ipc_stream_message(काष्ठा snd_sof_dev *sdev, u32 msg_cmd);

/*
 * IPC message Tx/Rx message handling.
 */

/* SOF generic IPC data */
काष्ठा snd_sof_ipc अणु
	काष्ठा snd_sof_dev *sdev;

	/* protects messages and the disable flag */
	काष्ठा mutex tx_mutex;
	/* disables further sending of ipc's */
	bool disable_ipc_tx;

	काष्ठा snd_sof_ipc_msg msg;
पूर्ण;

काष्ठा sof_ipc_ctrl_data_params अणु
	माप_प्रकार msg_bytes;
	माप_प्रकार hdr_bytes;
	माप_प्रकार pl_size;
	माप_प्रकार elems;
	u32 num_msg;
	u8 *src;
	u8 *dst;
पूर्ण;

#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_DEBUG_VERBOSE_IPC)
अटल व्योम ipc_log_header(काष्ठा device *dev, u8 *text, u32 cmd)
अणु
	u8 *str;
	u8 *str2 = शून्य;
	u32 glb;
	u32 type;
	bool vdbg = false;

	glb = cmd & SOF_GLB_TYPE_MASK;
	type = cmd & SOF_CMD_TYPE_MASK;

	चयन (glb) अणु
	हाल SOF_IPC_GLB_REPLY:
		str = "GLB_REPLY"; अवरोध;
	हाल SOF_IPC_GLB_COMPOUND:
		str = "GLB_COMPOUND"; अवरोध;
	हाल SOF_IPC_GLB_TPLG_MSG:
		str = "GLB_TPLG_MSG";
		चयन (type) अणु
		हाल SOF_IPC_TPLG_COMP_NEW:
			str2 = "COMP_NEW"; अवरोध;
		हाल SOF_IPC_TPLG_COMP_FREE:
			str2 = "COMP_FREE"; अवरोध;
		हाल SOF_IPC_TPLG_COMP_CONNECT:
			str2 = "COMP_CONNECT"; अवरोध;
		हाल SOF_IPC_TPLG_PIPE_NEW:
			str2 = "PIPE_NEW"; अवरोध;
		हाल SOF_IPC_TPLG_PIPE_FREE:
			str2 = "PIPE_FREE"; अवरोध;
		हाल SOF_IPC_TPLG_PIPE_CONNECT:
			str2 = "PIPE_CONNECT"; अवरोध;
		हाल SOF_IPC_TPLG_PIPE_COMPLETE:
			str2 = "PIPE_COMPLETE"; अवरोध;
		हाल SOF_IPC_TPLG_BUFFER_NEW:
			str2 = "BUFFER_NEW"; अवरोध;
		हाल SOF_IPC_TPLG_BUFFER_FREE:
			str2 = "BUFFER_FREE"; अवरोध;
		शेष:
			str2 = "unknown type"; अवरोध;
		पूर्ण
		अवरोध;
	हाल SOF_IPC_GLB_PM_MSG:
		str = "GLB_PM_MSG";
		चयन (type) अणु
		हाल SOF_IPC_PM_CTX_SAVE:
			str2 = "CTX_SAVE"; अवरोध;
		हाल SOF_IPC_PM_CTX_RESTORE:
			str2 = "CTX_RESTORE"; अवरोध;
		हाल SOF_IPC_PM_CTX_SIZE:
			str2 = "CTX_SIZE"; अवरोध;
		हाल SOF_IPC_PM_CLK_SET:
			str2 = "CLK_SET"; अवरोध;
		हाल SOF_IPC_PM_CLK_GET:
			str2 = "CLK_GET"; अवरोध;
		हाल SOF_IPC_PM_CLK_REQ:
			str2 = "CLK_REQ"; अवरोध;
		हाल SOF_IPC_PM_CORE_ENABLE:
			str2 = "CORE_ENABLE"; अवरोध;
		हाल SOF_IPC_PM_GATE:
			str2 = "GATE"; अवरोध;
		शेष:
			str2 = "unknown type"; अवरोध;
		पूर्ण
		अवरोध;
	हाल SOF_IPC_GLB_COMP_MSG:
		str = "GLB_COMP_MSG";
		चयन (type) अणु
		हाल SOF_IPC_COMP_SET_VALUE:
			str2 = "SET_VALUE"; अवरोध;
		हाल SOF_IPC_COMP_GET_VALUE:
			str2 = "GET_VALUE"; अवरोध;
		हाल SOF_IPC_COMP_SET_DATA:
			str2 = "SET_DATA"; अवरोध;
		हाल SOF_IPC_COMP_GET_DATA:
			str2 = "GET_DATA"; अवरोध;
		शेष:
			str2 = "unknown type"; अवरोध;
		पूर्ण
		अवरोध;
	हाल SOF_IPC_GLB_STREAM_MSG:
		str = "GLB_STREAM_MSG";
		चयन (type) अणु
		हाल SOF_IPC_STREAM_PCM_PARAMS:
			str2 = "PCM_PARAMS"; अवरोध;
		हाल SOF_IPC_STREAM_PCM_PARAMS_REPLY:
			str2 = "PCM_REPLY"; अवरोध;
		हाल SOF_IPC_STREAM_PCM_FREE:
			str2 = "PCM_FREE"; अवरोध;
		हाल SOF_IPC_STREAM_TRIG_START:
			str2 = "TRIG_START"; अवरोध;
		हाल SOF_IPC_STREAM_TRIG_STOP:
			str2 = "TRIG_STOP"; अवरोध;
		हाल SOF_IPC_STREAM_TRIG_PAUSE:
			str2 = "TRIG_PAUSE"; अवरोध;
		हाल SOF_IPC_STREAM_TRIG_RELEASE:
			str2 = "TRIG_RELEASE"; अवरोध;
		हाल SOF_IPC_STREAM_TRIG_DRAIN:
			str2 = "TRIG_DRAIN"; अवरोध;
		हाल SOF_IPC_STREAM_TRIG_XRUN:
			str2 = "TRIG_XRUN"; अवरोध;
		हाल SOF_IPC_STREAM_POSITION:
			vdbg = true;
			str2 = "POSITION"; अवरोध;
		हाल SOF_IPC_STREAM_VORBIS_PARAMS:
			str2 = "VORBIS_PARAMS"; अवरोध;
		हाल SOF_IPC_STREAM_VORBIS_FREE:
			str2 = "VORBIS_FREE"; अवरोध;
		शेष:
			str2 = "unknown type"; अवरोध;
		पूर्ण
		अवरोध;
	हाल SOF_IPC_FW_READY:
		str = "FW_READY"; अवरोध;
	हाल SOF_IPC_GLB_DAI_MSG:
		str = "GLB_DAI_MSG";
		चयन (type) अणु
		हाल SOF_IPC_DAI_CONFIG:
			str2 = "CONFIG"; अवरोध;
		हाल SOF_IPC_DAI_LOOPBACK:
			str2 = "LOOPBACK"; अवरोध;
		शेष:
			str2 = "unknown type"; अवरोध;
		पूर्ण
		अवरोध;
	हाल SOF_IPC_GLB_TRACE_MSG:
		str = "GLB_TRACE_MSG"; अवरोध;
	हाल SOF_IPC_GLB_TEST_MSG:
		str = "GLB_TEST_MSG";
		चयन (type) अणु
		हाल SOF_IPC_TEST_IPC_FLOOD:
			str2 = "IPC_FLOOD"; अवरोध;
		शेष:
			str2 = "unknown type"; अवरोध;
		पूर्ण
		अवरोध;
	हाल SOF_IPC_GLB_DEBUG:
		str = "GLB_DEBUG";
		चयन (type) अणु
		हाल SOF_IPC_DEBUG_MEM_USAGE:
			str2 = "MEM_USAGE"; अवरोध;
		शेष:
			str2 = "unknown type"; अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		str = "unknown GLB command"; अवरोध;
	पूर्ण

	अगर (str2) अणु
		अगर (vdbg)
			dev_vdbg(dev, "%s: 0x%x: %s: %s\n", text, cmd, str, str2);
		अन्यथा
			dev_dbg(dev, "%s: 0x%x: %s: %s\n", text, cmd, str, str2);
	पूर्ण अन्यथा अणु
		dev_dbg(dev, "%s: 0x%x: %s\n", text, cmd, str);
	पूर्ण
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम ipc_log_header(काष्ठा device *dev, u8 *text, u32 cmd)
अणु
	अगर ((cmd & SOF_GLB_TYPE_MASK) != SOF_IPC_GLB_TRACE_MSG)
		dev_dbg(dev, "%s: 0x%x\n", text, cmd);
पूर्ण
#पूर्ण_अगर

/* रुको क्रम IPC message reply */
अटल पूर्णांक tx_रुको_करोne(काष्ठा snd_sof_ipc *ipc, काष्ठा snd_sof_ipc_msg *msg,
			व्योम *reply_data)
अणु
	काष्ठा snd_sof_dev *sdev = ipc->sdev;
	काष्ठा sof_ipc_cmd_hdr *hdr = msg->msg_data;
	पूर्णांक ret;

	/* रुको क्रम DSP IPC completion */
	ret = रुको_event_समयout(msg->रुकोq, msg->ipc_complete,
				 msecs_to_jअगरfies(sdev->ipc_समयout));

	अगर (ret == 0) अणु
		dev_err(sdev->dev, "error: ipc timed out for 0x%x size %d\n",
			hdr->cmd, hdr->size);
		snd_sof_handle_fw_exception(ipc->sdev);
		ret = -ETIMEDOUT;
	पूर्ण अन्यथा अणु
		ret = msg->reply_error;
		अगर (ret < 0) अणु
			dev_err(sdev->dev, "error: ipc error for 0x%x size %zu\n",
				hdr->cmd, msg->reply_size);
		पूर्ण अन्यथा अणु
			ipc_log_header(sdev->dev, "ipc tx succeeded", hdr->cmd);
			अगर (msg->reply_size)
				/* copy the data वापसed from DSP */
				स_नकल(reply_data, msg->reply_data,
				       msg->reply_size);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/* send IPC message from host to DSP */
अटल पूर्णांक sof_ipc_tx_message_unlocked(काष्ठा snd_sof_ipc *ipc, u32 header,
				       व्योम *msg_data, माप_प्रकार msg_bytes,
				       व्योम *reply_data, माप_प्रकार reply_bytes)
अणु
	काष्ठा snd_sof_dev *sdev = ipc->sdev;
	काष्ठा snd_sof_ipc_msg *msg;
	पूर्णांक ret;

	अगर (ipc->disable_ipc_tx)
		वापस -ENODEV;

	/*
	 * The spin-lock is also still needed to protect message objects against
	 * other atomic contexts.
	 */
	spin_lock_irq(&sdev->ipc_lock);

	/* initialise the message */
	msg = &ipc->msg;

	msg->header = header;
	msg->msg_size = msg_bytes;
	msg->reply_size = reply_bytes;
	msg->reply_error = 0;

	/* attach any data */
	अगर (msg_bytes)
		स_नकल(msg->msg_data, msg_data, msg_bytes);

	sdev->msg = msg;

	ret = snd_sof_dsp_send_msg(sdev, msg);
	/* Next reply that we receive will be related to this message */
	अगर (!ret)
		msg->ipc_complete = false;

	spin_unlock_irq(&sdev->ipc_lock);

	अगर (ret < 0) अणु
		dev_err_ratelimited(sdev->dev,
				    "error: ipc tx failed with error %d\n",
				    ret);
		वापस ret;
	पूर्ण

	ipc_log_header(sdev->dev, "ipc tx", msg->header);

	/* now रुको क्रम completion */
	अगर (!ret)
		ret = tx_रुको_करोne(ipc, msg, reply_data);

	वापस ret;
पूर्ण

/* send IPC message from host to DSP */
पूर्णांक sof_ipc_tx_message(काष्ठा snd_sof_ipc *ipc, u32 header,
		       व्योम *msg_data, माप_प्रकार msg_bytes, व्योम *reply_data,
		       माप_प्रकार reply_bytes)
अणु
	स्थिर काष्ठा sof_dsp_घातer_state target_state = अणु
		.state = SOF_DSP_PM_D0,
	पूर्ण;
	पूर्णांक ret;

	/* ensure the DSP is in D0 beक्रमe sending a new IPC */
	ret = snd_sof_dsp_set_घातer_state(ipc->sdev, &target_state);
	अगर (ret < 0) अणु
		dev_err(ipc->sdev->dev, "error: resuming DSP %d\n", ret);
		वापस ret;
	पूर्ण

	वापस sof_ipc_tx_message_no_pm(ipc, header, msg_data, msg_bytes,
					reply_data, reply_bytes);
पूर्ण
EXPORT_SYMBOL(sof_ipc_tx_message);

/*
 * send IPC message from host to DSP without modअगरying the DSP state.
 * This will be used क्रम IPC's that can be handled by the DSP
 * even in a low-घातer D0 substate.
 */
पूर्णांक sof_ipc_tx_message_no_pm(काष्ठा snd_sof_ipc *ipc, u32 header,
			     व्योम *msg_data, माप_प्रकार msg_bytes,
			     व्योम *reply_data, माप_प्रकार reply_bytes)
अणु
	पूर्णांक ret;

	अगर (msg_bytes > SOF_IPC_MSG_MAX_SIZE ||
	    reply_bytes > SOF_IPC_MSG_MAX_SIZE)
		वापस -ENOBUFS;

	/* Serialise IPC TX */
	mutex_lock(&ipc->tx_mutex);

	ret = sof_ipc_tx_message_unlocked(ipc, header, msg_data, msg_bytes,
					  reply_data, reply_bytes);

	mutex_unlock(&ipc->tx_mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(sof_ipc_tx_message_no_pm);

/* handle reply message from DSP */
व्योम snd_sof_ipc_reply(काष्ठा snd_sof_dev *sdev, u32 msg_id)
अणु
	काष्ठा snd_sof_ipc_msg *msg = &sdev->ipc->msg;

	अगर (msg->ipc_complete) अणु
		dev_dbg(sdev->dev,
			"no reply expected, received 0x%x, will be ignored",
			msg_id);
		वापस;
	पूर्ण

	/* wake up and वापस the error अगर we have रुकोers on this message ? */
	msg->ipc_complete = true;
	wake_up(&msg->रुकोq);
पूर्ण
EXPORT_SYMBOL(snd_sof_ipc_reply);

/* DSP firmware has sent host a message  */
व्योम snd_sof_ipc_msgs_rx(काष्ठा snd_sof_dev *sdev)
अणु
	काष्ठा sof_ipc_cmd_hdr hdr;
	u32 cmd, type;
	पूर्णांक err = 0;

	/* पढ़ो back header */
	snd_sof_ipc_msg_data(sdev, शून्य, &hdr, माप(hdr));
	ipc_log_header(sdev->dev, "ipc rx", hdr.cmd);

	cmd = hdr.cmd & SOF_GLB_TYPE_MASK;
	type = hdr.cmd & SOF_CMD_TYPE_MASK;

	/* check message type */
	चयन (cmd) अणु
	हाल SOF_IPC_GLB_REPLY:
		dev_err(sdev->dev, "error: ipc reply unknown\n");
		अवरोध;
	हाल SOF_IPC_FW_READY:
		/* check क्रम FW boot completion */
		अगर (sdev->fw_state == SOF_FW_BOOT_IN_PROGRESS) अणु
			err = sof_ops(sdev)->fw_पढ़ोy(sdev, cmd);
			अगर (err < 0)
				sdev->fw_state = SOF_FW_BOOT_READY_FAILED;
			अन्यथा
				sdev->fw_state = SOF_FW_BOOT_COMPLETE;

			/* wake up firmware loader */
			wake_up(&sdev->boot_रुको);
		पूर्ण
		अवरोध;
	हाल SOF_IPC_GLB_COMPOUND:
	हाल SOF_IPC_GLB_TPLG_MSG:
	हाल SOF_IPC_GLB_PM_MSG:
	हाल SOF_IPC_GLB_COMP_MSG:
		अवरोध;
	हाल SOF_IPC_GLB_STREAM_MSG:
		/* need to pass msg id पूर्णांकo the function */
		ipc_stream_message(sdev, hdr.cmd);
		अवरोध;
	हाल SOF_IPC_GLB_TRACE_MSG:
		ipc_trace_message(sdev, type);
		अवरोध;
	शेष:
		dev_err(sdev->dev, "error: unknown DSP message 0x%x\n", cmd);
		अवरोध;
	पूर्ण

	ipc_log_header(sdev->dev, "ipc rx done", hdr.cmd);
पूर्ण
EXPORT_SYMBOL(snd_sof_ipc_msgs_rx);

/*
 * IPC trace mechanism.
 */

अटल व्योम ipc_trace_message(काष्ठा snd_sof_dev *sdev, u32 msg_id)
अणु
	काष्ठा sof_ipc_dma_trace_posn posn;

	चयन (msg_id) अणु
	हाल SOF_IPC_TRACE_DMA_POSITION:
		/* पढ़ो back full message */
		snd_sof_ipc_msg_data(sdev, शून्य, &posn, माप(posn));
		snd_sof_trace_update_pos(sdev, &posn);
		अवरोध;
	शेष:
		dev_err(sdev->dev, "error: unhandled trace message %x\n",
			msg_id);
		अवरोध;
	पूर्ण
पूर्ण

/*
 * IPC stream position.
 */

अटल व्योम ipc_period_elapsed(काष्ठा snd_sof_dev *sdev, u32 msg_id)
अणु
	काष्ठा snd_soc_component *scomp = sdev->component;
	काष्ठा snd_sof_pcm_stream *stream;
	काष्ठा sof_ipc_stream_posn posn;
	काष्ठा snd_sof_pcm *spcm;
	पूर्णांक direction;

	spcm = snd_sof_find_spcm_comp(scomp, msg_id, &direction);
	अगर (!spcm) अणु
		dev_err(sdev->dev,
			"error: period elapsed for unknown stream, msg_id %d\n",
			msg_id);
		वापस;
	पूर्ण

	stream = &spcm->stream[direction];
	snd_sof_ipc_msg_data(sdev, stream->substream, &posn, माप(posn));

	dev_vdbg(sdev->dev, "posn : host 0x%llx dai 0x%llx wall 0x%llx\n",
		 posn.host_posn, posn.dai_posn, posn.wallघड़ी);

	स_नकल(&stream->posn, &posn, माप(posn));

	/* only inक्रमm ALSA क्रम period_wakeup mode */
	अगर (!stream->substream->runसमय->no_period_wakeup)
		snd_sof_pcm_period_elapsed(stream->substream);
पूर्ण

/* DSP notअगरies host of an XRUN within FW */
अटल व्योम ipc_xrun(काष्ठा snd_sof_dev *sdev, u32 msg_id)
अणु
	काष्ठा snd_soc_component *scomp = sdev->component;
	काष्ठा snd_sof_pcm_stream *stream;
	काष्ठा sof_ipc_stream_posn posn;
	काष्ठा snd_sof_pcm *spcm;
	पूर्णांक direction;

	spcm = snd_sof_find_spcm_comp(scomp, msg_id, &direction);
	अगर (!spcm) अणु
		dev_err(sdev->dev, "error: XRUN for unknown stream, msg_id %d\n",
			msg_id);
		वापस;
	पूर्ण

	stream = &spcm->stream[direction];
	snd_sof_ipc_msg_data(sdev, stream->substream, &posn, माप(posn));

	dev_dbg(sdev->dev,  "posn XRUN: host %llx comp %d size %d\n",
		posn.host_posn, posn.xrun_comp_id, posn.xrun_size);

#अगर defined(CONFIG_SND_SOC_SOF_DEBUG_XRUN_STOP)
	/* stop PCM on XRUN - used क्रम pipeline debug */
	स_नकल(&stream->posn, &posn, माप(posn));
	snd_pcm_stop_xrun(stream->substream);
#पूर्ण_अगर
पूर्ण

/* stream notअगरications from DSP FW */
अटल व्योम ipc_stream_message(काष्ठा snd_sof_dev *sdev, u32 msg_cmd)
अणु
	/* get msg cmd type and msd id */
	u32 msg_type = msg_cmd & SOF_CMD_TYPE_MASK;
	u32 msg_id = SOF_IPC_MESSAGE_ID(msg_cmd);

	चयन (msg_type) अणु
	हाल SOF_IPC_STREAM_POSITION:
		ipc_period_elapsed(sdev, msg_id);
		अवरोध;
	हाल SOF_IPC_STREAM_TRIG_XRUN:
		ipc_xrun(sdev, msg_id);
		अवरोध;
	शेष:
		dev_err(sdev->dev, "error: unhandled stream message %x\n",
			msg_id);
		अवरोध;
	पूर्ण
पूर्ण

/* get stream position IPC - use faster MMIO method अगर available on platक्रमm */
पूर्णांक snd_sof_ipc_stream_posn(काष्ठा snd_soc_component *scomp,
			    काष्ठा snd_sof_pcm *spcm, पूर्णांक direction,
			    काष्ठा sof_ipc_stream_posn *posn)
अणु
	काष्ठा snd_sof_dev *sdev = snd_soc_component_get_drvdata(scomp);
	काष्ठा sof_ipc_stream stream;
	पूर्णांक err;

	/* पढ़ो position via slower IPC */
	stream.hdr.size = माप(stream);
	stream.hdr.cmd = SOF_IPC_GLB_STREAM_MSG | SOF_IPC_STREAM_POSITION;
	stream.comp_id = spcm->stream[direction].comp_id;

	/* send IPC to the DSP */
	err = sof_ipc_tx_message(sdev->ipc,
				 stream.hdr.cmd, &stream, माप(stream), posn,
				 माप(*posn));
	अगर (err < 0) अणु
		dev_err(sdev->dev, "error: failed to get stream %d position\n",
			stream.comp_id);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_sof_ipc_stream_posn);

अटल पूर्णांक sof_get_ctrl_copy_params(क्रमागत sof_ipc_ctrl_type ctrl_type,
				    काष्ठा sof_ipc_ctrl_data *src,
				    काष्ठा sof_ipc_ctrl_data *dst,
				    काष्ठा sof_ipc_ctrl_data_params *sparams)
अणु
	चयन (ctrl_type) अणु
	हाल SOF_CTRL_TYPE_VALUE_CHAN_GET:
	हाल SOF_CTRL_TYPE_VALUE_CHAN_SET:
		sparams->src = (u8 *)src->chanv;
		sparams->dst = (u8 *)dst->chanv;
		अवरोध;
	हाल SOF_CTRL_TYPE_VALUE_COMP_GET:
	हाल SOF_CTRL_TYPE_VALUE_COMP_SET:
		sparams->src = (u8 *)src->compv;
		sparams->dst = (u8 *)dst->compv;
		अवरोध;
	हाल SOF_CTRL_TYPE_DATA_GET:
	हाल SOF_CTRL_TYPE_DATA_SET:
		sparams->src = (u8 *)src->data->data;
		sparams->dst = (u8 *)dst->data->data;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* calculate payload size and number of messages */
	sparams->pl_size = SOF_IPC_MSG_MAX_SIZE - sparams->hdr_bytes;
	sparams->num_msg = DIV_ROUND_UP(sparams->msg_bytes, sparams->pl_size);

	वापस 0;
पूर्ण

अटल पूर्णांक sof_set_get_large_ctrl_data(काष्ठा snd_sof_dev *sdev,
				       काष्ठा sof_ipc_ctrl_data *cdata,
				       काष्ठा sof_ipc_ctrl_data_params *sparams,
				       bool send)
अणु
	काष्ठा sof_ipc_ctrl_data *partdata;
	माप_प्रकार send_bytes;
	माप_प्रकार offset = 0;
	माप_प्रकार msg_bytes;
	माप_प्रकार pl_size;
	पूर्णांक err;
	पूर्णांक i;

	/* allocate max ipc size because we have at least one */
	partdata = kzalloc(SOF_IPC_MSG_MAX_SIZE, GFP_KERNEL);
	अगर (!partdata)
		वापस -ENOMEM;

	अगर (send)
		err = sof_get_ctrl_copy_params(cdata->type, cdata, partdata,
					       sparams);
	अन्यथा
		err = sof_get_ctrl_copy_params(cdata->type, partdata, cdata,
					       sparams);
	अगर (err < 0) अणु
		kमुक्त(partdata);
		वापस err;
	पूर्ण

	msg_bytes = sparams->msg_bytes;
	pl_size = sparams->pl_size;

	/* copy the header data */
	स_नकल(partdata, cdata, sparams->hdr_bytes);

	/* Serialise IPC TX */
	mutex_lock(&sdev->ipc->tx_mutex);

	/* copy the payload data in a loop */
	क्रम (i = 0; i < sparams->num_msg; i++) अणु
		send_bytes = min(msg_bytes, pl_size);
		partdata->num_elems = send_bytes;
		partdata->rhdr.hdr.size = sparams->hdr_bytes + send_bytes;
		partdata->msg_index = i;
		msg_bytes -= send_bytes;
		partdata->elems_reमुख्यing = msg_bytes;

		अगर (send)
			स_नकल(sparams->dst, sparams->src + offset, send_bytes);

		err = sof_ipc_tx_message_unlocked(sdev->ipc,
						  partdata->rhdr.hdr.cmd,
						  partdata,
						  partdata->rhdr.hdr.size,
						  partdata,
						  partdata->rhdr.hdr.size);
		अगर (err < 0)
			अवरोध;

		अगर (!send)
			स_नकल(sparams->dst + offset, sparams->src, send_bytes);

		offset += pl_size;
	पूर्ण

	mutex_unlock(&sdev->ipc->tx_mutex);

	kमुक्त(partdata);
	वापस err;
पूर्ण

/*
 * IPC get()/set() क्रम kcontrols.
 */
पूर्णांक snd_sof_ipc_set_get_comp_data(काष्ठा snd_sof_control *scontrol,
				  u32 ipc_cmd,
				  क्रमागत sof_ipc_ctrl_type ctrl_type,
				  क्रमागत sof_ipc_ctrl_cmd ctrl_cmd,
				  bool send)
अणु
	काष्ठा snd_soc_component *scomp = scontrol->scomp;
	काष्ठा sof_ipc_ctrl_data *cdata = scontrol->control_data;
	काष्ठा snd_sof_dev *sdev = snd_soc_component_get_drvdata(scomp);
	काष्ठा sof_ipc_fw_पढ़ोy *पढ़ोy = &sdev->fw_पढ़ोy;
	काष्ठा sof_ipc_fw_version *v = &पढ़ोy->version;
	काष्ठा sof_ipc_ctrl_data_params sparams;
	माप_प्रकार send_bytes;
	पूर्णांक err;

	/* पढ़ो or ग_लिखो firmware volume */
	अगर (scontrol->पढ़ोback_offset != 0) अणु
		/* ग_लिखो/पढ़ो value header via mmaped region */
		send_bytes = माप(काष्ठा sof_ipc_ctrl_value_chan) *
		cdata->num_elems;
		अगर (send)
			snd_sof_dsp_block_ग_लिखो(sdev, sdev->mmio_bar,
						scontrol->पढ़ोback_offset,
						cdata->chanv, send_bytes);

		अन्यथा
			snd_sof_dsp_block_पढ़ो(sdev, sdev->mmio_bar,
					       scontrol->पढ़ोback_offset,
					       cdata->chanv, send_bytes);
		वापस 0;
	पूर्ण

	cdata->rhdr.hdr.cmd = SOF_IPC_GLB_COMP_MSG | ipc_cmd;
	cdata->cmd = ctrl_cmd;
	cdata->type = ctrl_type;
	cdata->comp_id = scontrol->comp_id;
	cdata->msg_index = 0;

	/* calculate header and data size */
	चयन (cdata->type) अणु
	हाल SOF_CTRL_TYPE_VALUE_CHAN_GET:
	हाल SOF_CTRL_TYPE_VALUE_CHAN_SET:
		sparams.msg_bytes = scontrol->num_channels *
			माप(काष्ठा sof_ipc_ctrl_value_chan);
		sparams.hdr_bytes = माप(काष्ठा sof_ipc_ctrl_data);
		sparams.elems = scontrol->num_channels;
		अवरोध;
	हाल SOF_CTRL_TYPE_VALUE_COMP_GET:
	हाल SOF_CTRL_TYPE_VALUE_COMP_SET:
		sparams.msg_bytes = scontrol->num_channels *
			माप(काष्ठा sof_ipc_ctrl_value_comp);
		sparams.hdr_bytes = माप(काष्ठा sof_ipc_ctrl_data);
		sparams.elems = scontrol->num_channels;
		अवरोध;
	हाल SOF_CTRL_TYPE_DATA_GET:
	हाल SOF_CTRL_TYPE_DATA_SET:
		sparams.msg_bytes = cdata->data->size;
		sparams.hdr_bytes = माप(काष्ठा sof_ipc_ctrl_data) +
			माप(काष्ठा sof_abi_hdr);
		sparams.elems = cdata->data->size;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	cdata->rhdr.hdr.size = sparams.msg_bytes + sparams.hdr_bytes;
	cdata->num_elems = sparams.elems;
	cdata->elems_reमुख्यing = 0;

	/* send normal size ipc in one part */
	अगर (cdata->rhdr.hdr.size <= SOF_IPC_MSG_MAX_SIZE) अणु
		err = sof_ipc_tx_message(sdev->ipc, cdata->rhdr.hdr.cmd, cdata,
					 cdata->rhdr.hdr.size, cdata,
					 cdata->rhdr.hdr.size);

		अगर (err < 0)
			dev_err(sdev->dev, "error: set/get ctrl ipc comp %d\n",
				cdata->comp_id);

		वापस err;
	पूर्ण

	/* data is bigger than max ipc size, chop पूर्णांकo smaller pieces */
	dev_dbg(sdev->dev, "large ipc size %u, control size %u\n",
		cdata->rhdr.hdr.size, scontrol->size);

	/* large messages is only supported from ABI 3.3.0 onwards */
	अगर (v->abi_version < SOF_ABI_VER(3, 3, 0)) अणु
		dev_err(sdev->dev, "error: incompatible FW ABI version\n");
		वापस -EINVAL;
	पूर्ण

	err = sof_set_get_large_ctrl_data(sdev, cdata, &sparams, send);

	अगर (err < 0)
		dev_err(sdev->dev, "error: set/get large ctrl ipc comp %d\n",
			cdata->comp_id);

	वापस err;
पूर्ण
EXPORT_SYMBOL(snd_sof_ipc_set_get_comp_data);

/*
 * IPC layer क्रमागतeration.
 */

पूर्णांक snd_sof_dsp_mailbox_init(काष्ठा snd_sof_dev *sdev, u32 dspbox,
			     माप_प्रकार dspbox_size, u32 hostbox,
			     माप_प्रकार hostbox_size)
अणु
	sdev->dsp_box.offset = dspbox;
	sdev->dsp_box.size = dspbox_size;
	sdev->host_box.offset = hostbox;
	sdev->host_box.size = hostbox_size;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_sof_dsp_mailbox_init);

पूर्णांक snd_sof_ipc_valid(काष्ठा snd_sof_dev *sdev)
अणु
	काष्ठा sof_ipc_fw_पढ़ोy *पढ़ोy = &sdev->fw_पढ़ोy;
	काष्ठा sof_ipc_fw_version *v = &पढ़ोy->version;

	dev_info(sdev->dev,
		 "Firmware info: version %d:%d:%d-%s\n",  v->major, v->minor,
		 v->micro, v->tag);
	dev_info(sdev->dev,
		 "Firmware: ABI %d:%d:%d Kernel ABI %d:%d:%d\n",
		 SOF_ABI_VERSION_MAJOR(v->abi_version),
		 SOF_ABI_VERSION_MINOR(v->abi_version),
		 SOF_ABI_VERSION_PATCH(v->abi_version),
		 SOF_ABI_MAJOR, SOF_ABI_MINOR, SOF_ABI_PATCH);

	अगर (SOF_ABI_VERSION_INCOMPATIBLE(SOF_ABI_VERSION, v->abi_version)) अणु
		dev_err(sdev->dev, "error: incompatible FW ABI version\n");
		वापस -EINVAL;
	पूर्ण

	अगर (SOF_ABI_VERSION_MINOR(v->abi_version) > SOF_ABI_MINOR) अणु
		अगर (!IS_ENABLED(CONFIG_SND_SOC_SOF_STRICT_ABI_CHECKS)) अणु
			dev_warn(sdev->dev, "warn: FW ABI is more recent than kernel\n");
		पूर्ण अन्यथा अणु
			dev_err(sdev->dev, "error: FW ABI is more recent than kernel\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (पढ़ोy->flags & SOF_IPC_INFO_BUILD) अणु
		dev_info(sdev->dev,
			 "Firmware debug build %d on %s-%s - options:\n"
			 " GDB: %s\n"
			 " lock debug: %s\n"
			 " lock vdebug: %s\n",
			 v->build, v->date, v->समय,
			 (पढ़ोy->flags & SOF_IPC_INFO_GDB) ?
				"enabled" : "disabled",
			 (पढ़ोy->flags & SOF_IPC_INFO_LOCKS) ?
				"enabled" : "disabled",
			 (पढ़ोy->flags & SOF_IPC_INFO_LOCKSV) ?
				"enabled" : "disabled");
	पूर्ण

	/* copy the fw_version पूर्णांकo debugfs at first boot */
	स_नकल(&sdev->fw_version, v, माप(*v));

	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_sof_ipc_valid);

काष्ठा snd_sof_ipc *snd_sof_ipc_init(काष्ठा snd_sof_dev *sdev)
अणु
	काष्ठा snd_sof_ipc *ipc;
	काष्ठा snd_sof_ipc_msg *msg;

	ipc = devm_kzalloc(sdev->dev, माप(*ipc), GFP_KERNEL);
	अगर (!ipc)
		वापस शून्य;

	mutex_init(&ipc->tx_mutex);
	ipc->sdev = sdev;
	msg = &ipc->msg;

	/* indicate that we aren't sending a message ATM */
	msg->ipc_complete = true;

	/* pre-allocate message data */
	msg->msg_data = devm_kzalloc(sdev->dev, SOF_IPC_MSG_MAX_SIZE,
				     GFP_KERNEL);
	अगर (!msg->msg_data)
		वापस शून्य;

	msg->reply_data = devm_kzalloc(sdev->dev, SOF_IPC_MSG_MAX_SIZE,
				       GFP_KERNEL);
	अगर (!msg->reply_data)
		वापस शून्य;

	init_रुकोqueue_head(&msg->रुकोq);

	वापस ipc;
पूर्ण
EXPORT_SYMBOL(snd_sof_ipc_init);

व्योम snd_sof_ipc_मुक्त(काष्ठा snd_sof_dev *sdev)
अणु
	काष्ठा snd_sof_ipc *ipc = sdev->ipc;

	अगर (!ipc)
		वापस;

	/* disable sending of ipc's */
	mutex_lock(&ipc->tx_mutex);
	ipc->disable_ipc_tx = true;
	mutex_unlock(&ipc->tx_mutex);
पूर्ण
EXPORT_SYMBOL(snd_sof_ipc_मुक्त);
