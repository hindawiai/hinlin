<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  sst_stream.c - Intel SST Driver क्रम audio engine
 *
 *  Copyright (C) 2008-14 Intel Corp
 *  Authors:	Vinod Koul <vinod.koul@पूर्णांकel.com>
 *		Harsha Priya <priya.harsha@पूर्णांकel.com>
 *		Dharageswari R <dharageswari.r@पूर्णांकel.com>
 *		KP Jeeja <jeeja.kp@पूर्णांकel.com>
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
#समावेश <linux/pci.h>
#समावेश <linux/firmware.h>
#समावेश <linux/sched.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/soc.h>
#समावेश <sound/compress_driver.h>
#समावेश <यंत्र/platक्रमm_sst_audपन.स>
#समावेश "../sst-mfld-platform.h"
#समावेश "sst.h"

पूर्णांक sst_alloc_stream_mrfld(काष्ठा पूर्णांकel_sst_drv *sst_drv_ctx, व्योम *params)
अणु
	काष्ठा snd_pcm_params *pcm_params;
	काष्ठा snd_sst_params *str_params;
	काष्ठा snd_sst_tstamp fw_tstamp;
	काष्ठा stream_info *str_info;
	पूर्णांक i, num_ch, str_id;

	dev_dbg(sst_drv_ctx->dev, "Enter\n");

	str_params = (काष्ठा snd_sst_params *)params;
	str_id = str_params->stream_id;
	str_info = get_stream_info(sst_drv_ctx, str_id);
	अगर (!str_info)
		वापस -EINVAL;

	स_रखो(&str_info->alloc_param, 0, माप(str_info->alloc_param));
	str_info->alloc_param.operation = str_params->ops;
	str_info->alloc_param.codec_type = str_params->codec;
	str_info->alloc_param.sg_count = str_params->aparams.sg_count;
	str_info->alloc_param.ring_buf_info[0].addr =
		str_params->aparams.ring_buf_info[0].addr;
	str_info->alloc_param.ring_buf_info[0].size =
		str_params->aparams.ring_buf_info[0].size;
	str_info->alloc_param.frag_size = str_params->aparams.frag_size;

	स_नकल(&str_info->alloc_param.codec_params, &str_params->sparams,
			माप(काष्ठा snd_sst_stream_params));

	/*
	 * fill channel map params क्रम multichannel support.
	 * Ideally channel map should be received from upper layers
	 * क्रम multichannel support.
	 * Currently hardcoding as per FW reqm.
	 */
	num_ch = sst_get_num_channel(str_params);
	pcm_params = &str_info->alloc_param.codec_params.uc.pcm_params;
	क्रम (i = 0; i < 8; i++) अणु
		अगर (i < num_ch)
			pcm_params->channel_map[i] = i;
		अन्यथा
			pcm_params->channel_map[i] = 0xff;
	पूर्ण

	sst_drv_ctx->streams[str_id].status = STREAM_INIT;
	sst_drv_ctx->streams[str_id].prev = STREAM_UN_INIT;
	sst_drv_ctx->streams[str_id].pipe_id = str_params->device_type;
	sst_drv_ctx->streams[str_id].task_id = str_params->task;
	sst_drv_ctx->streams[str_id].num_ch = num_ch;

	अगर (sst_drv_ctx->info.lpe_viewpt_rqd)
		str_info->alloc_param.ts = sst_drv_ctx->info.mailbox_start +
			sst_drv_ctx->tstamp + (str_id * माप(fw_tstamp));
	अन्यथा
		str_info->alloc_param.ts = sst_drv_ctx->mailbox_add +
			sst_drv_ctx->tstamp + (str_id * माप(fw_tstamp));

	dev_dbg(sst_drv_ctx->dev, "alloc tstamp location = 0x%x\n",
			str_info->alloc_param.ts);
	dev_dbg(sst_drv_ctx->dev, "assigned pipe id 0x%x to task %d\n",
			str_info->pipe_id, str_info->task_id);

	वापस sst_पुनः_स्मृति_stream(sst_drv_ctx, str_id);
पूर्ण

/**
 * sst_पुनः_स्मृति_stream - Send msg क्रम (re-)allocating a stream using the
 * @sst_drv_ctx: पूर्णांकel_sst_drv context poपूर्णांकer
 * @str_id: stream ID
 *
 * Send a msg क्रम (re-)allocating a stream using the parameters previously
 * passed to sst_alloc_stream_mrfld() क्रम the same stream ID.
 * Return: 0 or negative त्रुटि_सं value.
 */
पूर्णांक sst_पुनः_स्मृति_stream(काष्ठा पूर्णांकel_sst_drv *sst_drv_ctx, पूर्णांक str_id)
अणु
	काष्ठा snd_sst_alloc_response *response;
	काष्ठा stream_info *str_info;
	व्योम *data = शून्य;
	पूर्णांक ret;

	str_info = get_stream_info(sst_drv_ctx, str_id);
	अगर (!str_info)
		वापस -EINVAL;

	dev_dbg(sst_drv_ctx->dev, "Alloc for str %d pipe %#x\n",
		str_id, str_info->pipe_id);

	ret = sst_prepare_and_post_msg(sst_drv_ctx, str_info->task_id, IPC_CMD,
			IPC_IA_ALLOC_STREAM_MRFLD, str_info->pipe_id,
			माप(str_info->alloc_param), &str_info->alloc_param,
			&data, true, true, false, true);

	अगर (ret < 0) अणु
		dev_err(sst_drv_ctx->dev, "FW alloc failed ret %d\n", ret);
		/* alloc failed, so reset the state to uninit */
		str_info->status = STREAM_UN_INIT;
		str_id = ret;
	पूर्ण अन्यथा अगर (data) अणु
		response = (काष्ठा snd_sst_alloc_response *)data;
		ret = response->str_type.result;
		अगर (!ret)
			जाओ out;
		dev_err(sst_drv_ctx->dev, "FW alloc failed ret %d\n", ret);
		अगर (ret == SST_ERR_STREAM_IN_USE) अणु
			dev_err(sst_drv_ctx->dev,
				"FW not in clean state, send free for:%d\n", str_id);
			sst_मुक्त_stream(sst_drv_ctx, str_id);
		पूर्ण
		str_id = -ret;
	पूर्ण
out:
	kमुक्त(data);
	वापस str_id;
पूर्ण

/**
 * sst_start_stream - Send msg क्रम a starting stream
 * @sst_drv_ctx: पूर्णांकel_sst_drv context poपूर्णांकer
 * @str_id: stream ID
 *
 * This function is called by any function which wants to start
 * a stream.
 */
पूर्णांक sst_start_stream(काष्ठा पूर्णांकel_sst_drv *sst_drv_ctx, पूर्णांक str_id)
अणु
	पूर्णांक retval = 0;
	काष्ठा stream_info *str_info;
	u16 data = 0;

	dev_dbg(sst_drv_ctx->dev, "sst_start_stream for %d\n", str_id);
	str_info = get_stream_info(sst_drv_ctx, str_id);
	अगर (!str_info)
		वापस -EINVAL;
	अगर (str_info->status != STREAM_RUNNING)
		वापस -EBADRQC;

	retval = sst_prepare_and_post_msg(sst_drv_ctx, str_info->task_id,
			IPC_CMD, IPC_IA_START_STREAM_MRFLD, str_info->pipe_id,
			माप(u16), &data, शून्य, true, true, true, false);

	वापस retval;
पूर्ण

पूर्णांक sst_send_byte_stream_mrfld(काष्ठा पूर्णांकel_sst_drv *sst_drv_ctx,
		काष्ठा snd_sst_bytes_v2 *bytes)
अणु	काष्ठा ipc_post *msg = शून्य;
	u32 length;
	पूर्णांक pvt_id, ret = 0;
	काष्ठा sst_block *block = शून्य;

	dev_dbg(sst_drv_ctx->dev,
		"type:%u ipc_msg:%u block:%u task_id:%u pipe: %#x length:%#x\n",
		bytes->type, bytes->ipc_msg, bytes->block, bytes->task_id,
		bytes->pipe_id, bytes->len);

	अगर (sst_create_ipc_msg(&msg, true))
		वापस -ENOMEM;

	pvt_id = sst_assign_pvt_id(sst_drv_ctx);
	sst_fill_header_mrfld(&msg->mrfld_header, bytes->ipc_msg,
			bytes->task_id, 1, pvt_id);
	msg->mrfld_header.p.header_high.part.res_rqd = bytes->block;
	length = bytes->len;
	msg->mrfld_header.p.header_low_payload = length;
	dev_dbg(sst_drv_ctx->dev, "length is %d\n", length);
	स_नकल(msg->mailbox_data, &bytes->bytes, bytes->len);
	अगर (bytes->block) अणु
		block = sst_create_block(sst_drv_ctx, bytes->ipc_msg, pvt_id);
		अगर (block == शून्य) अणु
			kमुक्त(msg);
			ret = -ENOMEM;
			जाओ out;
		पूर्ण
	पूर्ण

	sst_add_to_dispatch_list_and_post(sst_drv_ctx, msg);
	dev_dbg(sst_drv_ctx->dev, "msg->mrfld_header.p.header_low_payload:%d",
			msg->mrfld_header.p.header_low_payload);

	अगर (bytes->block) अणु
		ret = sst_रुको_समयout(sst_drv_ctx, block);
		अगर (ret) अणु
			dev_err(sst_drv_ctx->dev, "fw returned err %d\n", ret);
			sst_मुक्त_block(sst_drv_ctx, block);
			जाओ out;
		पूर्ण
	पूर्ण
	अगर (bytes->type == SND_SST_BYTES_GET) अणु
		/*
		 * copy the reply and send back
		 * we need to update only sz and payload
		 */
		अगर (bytes->block) अणु
			अचिन्हित अक्षर *r = block->data;

			dev_dbg(sst_drv_ctx->dev, "read back %d bytes",
					bytes->len);
			स_नकल(bytes->bytes, r, bytes->len);
		पूर्ण
	पूर्ण
	अगर (bytes->block)
		sst_मुक्त_block(sst_drv_ctx, block);
out:
	test_and_clear_bit(pvt_id, &sst_drv_ctx->pvt_id);
	वापस ret;
पूर्ण

/**
 * sst_छोड़ो_stream - Send msg क्रम a pausing stream
 * @sst_drv_ctx: पूर्णांकel_sst_drv context poपूर्णांकer
 * @str_id: stream ID
 *
 * This function is called by any function which wants to छोड़ो
 * an alपढ़ोy running stream.
 */
पूर्णांक sst_छोड़ो_stream(काष्ठा पूर्णांकel_sst_drv *sst_drv_ctx, पूर्णांक str_id)
अणु
	पूर्णांक retval = 0;
	काष्ठा stream_info *str_info;

	dev_dbg(sst_drv_ctx->dev, "SST DBG:sst_pause_stream for %d\n", str_id);
	str_info = get_stream_info(sst_drv_ctx, str_id);
	अगर (!str_info)
		वापस -EINVAL;
	अगर (str_info->status == STREAM_PAUSED)
		वापस 0;
	अगर (str_info->status == STREAM_RUNNING ||
		str_info->status == STREAM_INIT) अणु
		अगर (str_info->prev == STREAM_UN_INIT)
			वापस -EBADRQC;

		retval = sst_prepare_and_post_msg(sst_drv_ctx, str_info->task_id, IPC_CMD,
				IPC_IA_PAUSE_STREAM_MRFLD, str_info->pipe_id,
				0, शून्य, शून्य, true, true, false, true);

		अगर (retval == 0) अणु
			str_info->prev = str_info->status;
			str_info->status = STREAM_PAUSED;
		पूर्ण अन्यथा अगर (retval == -SST_ERR_INVALID_STREAM_ID) अणु
			retval = -EINVAL;
			mutex_lock(&sst_drv_ctx->sst_lock);
			sst_clean_stream(str_info);
			mutex_unlock(&sst_drv_ctx->sst_lock);
		पूर्ण
	पूर्ण अन्यथा अणु
		retval = -EBADRQC;
		dev_dbg(sst_drv_ctx->dev, "SST DBG:BADRQC for stream\n");
	पूर्ण

	वापस retval;
पूर्ण

/**
 * sst_resume_stream - Send msg क्रम resuming stream
 * @sst_drv_ctx: पूर्णांकel_sst_drv context poपूर्णांकer
 * @str_id: stream ID
 *
 * This function is called by any function which wants to resume
 * an alपढ़ोy छोड़ोd stream.
 */
पूर्णांक sst_resume_stream(काष्ठा पूर्णांकel_sst_drv *sst_drv_ctx, पूर्णांक str_id)
अणु
	पूर्णांक retval = 0;
	काष्ठा stream_info *str_info;

	dev_dbg(sst_drv_ctx->dev, "SST DBG:sst_resume_stream for %d\n", str_id);
	str_info = get_stream_info(sst_drv_ctx, str_id);
	अगर (!str_info)
		वापस -EINVAL;
	अगर (str_info->status == STREAM_RUNNING)
		वापस 0;

	अगर (str_info->resume_status == STREAM_PAUSED &&
	    str_info->resume_prev == STREAM_RUNNING) अणु
		/*
		 * Stream was running beक्रमe suspend and re-created on resume,
		 * start it to get back to running state.
		 */
		dev_dbg(sst_drv_ctx->dev, "restart recreated stream after resume\n");
		str_info->status = STREAM_RUNNING;
		str_info->prev = STREAM_PAUSED;
		retval = sst_start_stream(sst_drv_ctx, str_id);
		str_info->resume_status = STREAM_UN_INIT;
	पूर्ण अन्यथा अगर (str_info->resume_status == STREAM_PAUSED &&
		   str_info->resume_prev == STREAM_INIT) अणु
		/*
		 * Stream was idle beक्रमe suspend and re-created on resume,
		 * keep it as is.
		 */
		dev_dbg(sst_drv_ctx->dev, "leaving recreated stream idle after resume\n");
		str_info->status = STREAM_INIT;
		str_info->prev = STREAM_PAUSED;
		str_info->resume_status = STREAM_UN_INIT;
	पूर्ण अन्यथा अगर (str_info->status == STREAM_PAUSED) अणु
		retval = sst_prepare_and_post_msg(sst_drv_ctx, str_info->task_id,
				IPC_CMD, IPC_IA_RESUME_STREAM_MRFLD,
				str_info->pipe_id, 0, शून्य, शून्य,
				true, true, false, true);

		अगर (!retval) अणु
			अगर (str_info->prev == STREAM_RUNNING)
				str_info->status = STREAM_RUNNING;
			अन्यथा
				str_info->status = STREAM_INIT;
			str_info->prev = STREAM_PAUSED;
		पूर्ण अन्यथा अगर (retval == -SST_ERR_INVALID_STREAM_ID) अणु
			retval = -EINVAL;
			mutex_lock(&sst_drv_ctx->sst_lock);
			sst_clean_stream(str_info);
			mutex_unlock(&sst_drv_ctx->sst_lock);
		पूर्ण
	पूर्ण अन्यथा अणु
		retval = -EBADRQC;
		dev_err(sst_drv_ctx->dev, "SST ERR: BADQRC for stream\n");
	पूर्ण

	वापस retval;
पूर्ण


/**
 * sst_drop_stream - Send msg क्रम stopping stream
 * @sst_drv_ctx: पूर्णांकel_sst_drv context poपूर्णांकer
 * @str_id: stream ID
 *
 * This function is called by any function which wants to stop
 * a stream.
 */
पूर्णांक sst_drop_stream(काष्ठा पूर्णांकel_sst_drv *sst_drv_ctx, पूर्णांक str_id)
अणु
	पूर्णांक retval = 0;
	काष्ठा stream_info *str_info;

	dev_dbg(sst_drv_ctx->dev, "SST DBG:sst_drop_stream for %d\n", str_id);
	str_info = get_stream_info(sst_drv_ctx, str_id);
	अगर (!str_info)
		वापस -EINVAL;

	अगर (str_info->status != STREAM_UN_INIT) अणु
		str_info->prev = STREAM_UN_INIT;
		str_info->status = STREAM_INIT;
		str_info->cumm_bytes = 0;
		retval = sst_prepare_and_post_msg(sst_drv_ctx, str_info->task_id,
				IPC_CMD, IPC_IA_DROP_STREAM_MRFLD,
				str_info->pipe_id, 0, शून्य, शून्य,
				true, true, true, false);
	पूर्ण अन्यथा अणु
		retval = -EBADRQC;
		dev_dbg(sst_drv_ctx->dev, "BADQRC for stream, state %x\n",
				str_info->status);
	पूर्ण
	वापस retval;
पूर्ण

/**
 * sst_drain_stream - Send msg क्रम draining stream
 * @sst_drv_ctx: पूर्णांकel_sst_drv context poपूर्णांकer
 * @str_id: stream ID
 * @partial_drain: boolean indicating अगर a gapless transition is taking place
 *
 * This function is called by any function which wants to drain
 * a stream.
 */
पूर्णांक sst_drain_stream(काष्ठा पूर्णांकel_sst_drv *sst_drv_ctx,
			पूर्णांक str_id, bool partial_drain)
अणु
	पूर्णांक retval = 0;
	काष्ठा stream_info *str_info;

	dev_dbg(sst_drv_ctx->dev, "SST DBG:sst_drain_stream for %d\n", str_id);
	str_info = get_stream_info(sst_drv_ctx, str_id);
	अगर (!str_info)
		वापस -EINVAL;
	अगर (str_info->status != STREAM_RUNNING &&
		str_info->status != STREAM_INIT &&
		str_info->status != STREAM_PAUSED) अणु
			dev_err(sst_drv_ctx->dev, "SST ERR: BADQRC for stream = %d\n",
				       str_info->status);
			वापस -EBADRQC;
	पूर्ण

	retval = sst_prepare_and_post_msg(sst_drv_ctx, str_info->task_id, IPC_CMD,
			IPC_IA_DRAIN_STREAM_MRFLD, str_info->pipe_id,
			माप(u8), &partial_drain, शून्य, true, true, false, false);
	/*
	 * with new non blocked drain implementation in core we करोnt need to
	 * रुको क्रम respsonse, and need to only invoke callback क्रम drain
	 * complete
	 */

	वापस retval;
पूर्ण

/**
 * sst_मुक्त_stream - Frees a stream
 * @sst_drv_ctx: पूर्णांकel_sst_drv context poपूर्णांकer
 * @str_id: stream ID
 *
 * This function is called by any function which wants to मुक्त
 * a stream.
 */
पूर्णांक sst_मुक्त_stream(काष्ठा पूर्णांकel_sst_drv *sst_drv_ctx, पूर्णांक str_id)
अणु
	पूर्णांक retval = 0;
	काष्ठा stream_info *str_info;

	dev_dbg(sst_drv_ctx->dev, "SST DBG:sst_free_stream for %d\n", str_id);

	mutex_lock(&sst_drv_ctx->sst_lock);
	अगर (sst_drv_ctx->sst_state == SST_RESET) अणु
		mutex_unlock(&sst_drv_ctx->sst_lock);
		वापस -ENODEV;
	पूर्ण
	mutex_unlock(&sst_drv_ctx->sst_lock);
	str_info = get_stream_info(sst_drv_ctx, str_id);
	अगर (!str_info)
		वापस -EINVAL;

	mutex_lock(&str_info->lock);
	अगर (str_info->status != STREAM_UN_INIT) अणु
		str_info->prev =  str_info->status;
		str_info->status = STREAM_UN_INIT;
		mutex_unlock(&str_info->lock);

		dev_dbg(sst_drv_ctx->dev, "Free for str %d pipe %#x\n",
				str_id, str_info->pipe_id);
		retval = sst_prepare_and_post_msg(sst_drv_ctx, str_info->task_id, IPC_CMD,
				IPC_IA_FREE_STREAM_MRFLD, str_info->pipe_id, 0,
				शून्य, शून्य, true, true, false, true);

		dev_dbg(sst_drv_ctx->dev, "sst: wait for free returned %d\n",
				retval);
		mutex_lock(&sst_drv_ctx->sst_lock);
		sst_clean_stream(str_info);
		mutex_unlock(&sst_drv_ctx->sst_lock);
		dev_dbg(sst_drv_ctx->dev, "SST DBG:Stream freed\n");
	पूर्ण अन्यथा अणु
		mutex_unlock(&str_info->lock);
		retval = -EBADRQC;
		dev_dbg(sst_drv_ctx->dev, "SST DBG:BADQRC for stream\n");
	पूर्ण

	वापस retval;
पूर्ण
