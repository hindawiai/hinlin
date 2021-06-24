<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// Copyright 2017-2021 NXP

#समावेश <linux/dma-mapping.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/rpmsg.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/dmaengine_pcm.h>
#समावेश <sound/soc.h>

#समावेश "imx-pcm.h"
#समावेश "fsl_rpmsg.h"
#समावेश "imx-pcm-rpmsg.h"

अटल काष्ठा snd_pcm_hardware imx_rpmsg_pcm_hardware = अणु
	.info = SNDRV_PCM_INFO_INTERLEAVED |
		SNDRV_PCM_INFO_BLOCK_TRANSFER |
		SNDRV_PCM_INFO_MMAP |
		SNDRV_PCM_INFO_MMAP_VALID |
		SNDRV_PCM_INFO_NO_PERIOD_WAKEUP |
		SNDRV_PCM_INFO_PAUSE |
		SNDRV_PCM_INFO_RESUME,
	.buffer_bytes_max = IMX_DEFAULT_DMABUF_SIZE,
	.period_bytes_min = 512,
	.period_bytes_max = 65536,
	.periods_min = 2,
	.periods_max = 6000,
	.fअगरo_size = 0,
पूर्ण;

अटल पूर्णांक imx_rpmsg_pcm_send_message(काष्ठा rpmsg_msg *msg,
				      काष्ठा rpmsg_info *info)
अणु
	काष्ठा rpmsg_device *rpdev = info->rpdev;
	पूर्णांक ret = 0;

	mutex_lock(&info->msg_lock);
	अगर (!rpdev) अणु
		dev_err(info->dev, "rpmsg channel not ready\n");
		mutex_unlock(&info->msg_lock);
		वापस -EINVAL;
	पूर्ण

	dev_dbg(&rpdev->dev, "send cmd %d\n", msg->s_msg.header.cmd);

	अगर (!(msg->s_msg.header.type == MSG_TYPE_C))
		reinit_completion(&info->cmd_complete);

	ret = rpmsg_send(rpdev->ept, (व्योम *)&msg->s_msg,
			 माप(काष्ठा rpmsg_s_msg));
	अगर (ret) अणु
		dev_err(&rpdev->dev, "rpmsg_send failed: %d\n", ret);
		mutex_unlock(&info->msg_lock);
		वापस ret;
	पूर्ण

	/* No receive msg क्रम TYPE_C command */
	अगर (msg->s_msg.header.type == MSG_TYPE_C) अणु
		mutex_unlock(&info->msg_lock);
		वापस 0;
	पूर्ण

	/* रुको response from rpmsg */
	ret = रुको_क्रम_completion_समयout(&info->cmd_complete,
					  msecs_to_jअगरfies(RPMSG_TIMEOUT));
	अगर (!ret) अणु
		dev_err(&rpdev->dev, "rpmsg_send cmd %d timeout!\n",
			msg->s_msg.header.cmd);
		mutex_unlock(&info->msg_lock);
		वापस -ETIMEDOUT;
	पूर्ण

	स_नकल(&msg->r_msg, &info->r_msg, माप(काष्ठा rpmsg_r_msg));
	स_नकल(&info->msg[msg->r_msg.header.cmd].r_msg,
	       &msg->r_msg, माप(काष्ठा rpmsg_r_msg));

	/*
	 * Reset the buffer poपूर्णांकer to be zero, actully we have
	 * set the buffer poपूर्णांकer to be zero in imx_rpmsg_terminate_all
	 * But अगर there is समयr task queued in queue, after it is
	 * executed the buffer poपूर्णांकer will be changed, so need to
	 * reset it again with TERMINATE command.
	 */
	चयन (msg->s_msg.header.cmd) अणु
	हाल TX_TERMINATE:
		info->msg[TX_POINTER].r_msg.param.buffer_offset = 0;
		अवरोध;
	हाल RX_TERMINATE:
		info->msg[RX_POINTER].r_msg.param.buffer_offset = 0;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	dev_dbg(&rpdev->dev, "cmd:%d, resp %d\n", msg->s_msg.header.cmd,
		info->r_msg.param.resp);

	mutex_unlock(&info->msg_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक imx_rpmsg_insert_workqueue(काष्ठा snd_pcm_substream *substream,
				      काष्ठा rpmsg_msg *msg,
				      काष्ठा rpmsg_info *info)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	/*
	 * Queue the work to workqueue.
	 * If the queue is full, drop the message.
	 */
	spin_lock_irqsave(&info->wq_lock, flags);
	अगर (info->work_ग_लिखो_index != info->work_पढ़ो_index) अणु
		पूर्णांक index = info->work_ग_लिखो_index;

		स_नकल(&info->work_list[index].msg, msg,
		       माप(काष्ठा rpmsg_s_msg));

		queue_work(info->rpmsg_wq, &info->work_list[index].work);
		info->work_ग_लिखो_index++;
		info->work_ग_लिखो_index %= WORK_MAX_NUM;
	पूर्ण अन्यथा अणु
		info->msg_drop_count[substream->stream]++;
		ret = -EPIPE;
	पूर्ण
	spin_unlock_irqrestore(&info->wq_lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक imx_rpmsg_pcm_hw_params(काष्ठा snd_soc_component *component,
				   काष्ठा snd_pcm_substream *substream,
				   काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा rpmsg_info *info = dev_get_drvdata(component->dev);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा rpmsg_msg *msg;
	पूर्णांक ret = 0;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		msg = &info->msg[TX_HW_PARAM];
		msg->s_msg.header.cmd = TX_HW_PARAM;
	पूर्ण अन्यथा अणु
		msg = &info->msg[RX_HW_PARAM];
		msg->s_msg.header.cmd = RX_HW_PARAM;
	पूर्ण

	msg->s_msg.param.rate = params_rate(params);

	चयन (params_क्रमmat(params)) अणु
	हाल SNDRV_PCM_FORMAT_S16_LE:
		msg->s_msg.param.क्रमmat   = RPMSG_S16_LE;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S24_LE:
		msg->s_msg.param.क्रमmat   = RPMSG_S24_LE;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_DSD_U16_LE:
		msg->s_msg.param.क्रमmat   = SNDRV_PCM_FORMAT_DSD_U16_LE;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_DSD_U32_LE:
		msg->s_msg.param.क्रमmat   = SNDRV_PCM_FORMAT_DSD_U32_LE;
		अवरोध;
	शेष:
		msg->s_msg.param.क्रमmat   = RPMSG_S32_LE;
		अवरोध;
	पूर्ण

	चयन (params_channels(params)) अणु
	हाल 1:
		msg->s_msg.param.channels = RPMSG_CH_LEFT;
		अवरोध;
	हाल 2:
		msg->s_msg.param.channels = RPMSG_CH_STEREO;
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	snd_pcm_set_runसमय_buffer(substream, &substream->dma_buffer);
	runसमय->dma_bytes = params_buffer_bytes(params);

	info->send_message(msg, info);

	वापस ret;
पूर्ण

अटल पूर्णांक imx_rpmsg_pcm_hw_मुक्त(काष्ठा snd_soc_component *component,
				 काष्ठा snd_pcm_substream *substream)
अणु
	snd_pcm_set_runसमय_buffer(substream, शून्य);
	वापस 0;
पूर्ण

अटल snd_pcm_uframes_t imx_rpmsg_pcm_poपूर्णांकer(काष्ठा snd_soc_component *component,
					       काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा rpmsg_info *info = dev_get_drvdata(component->dev);
	काष्ठा rpmsg_msg *msg;
	अचिन्हित पूर्णांक pos = 0;
	पूर्णांक buffer_tail = 0;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		msg = &info->msg[TX_PERIOD_DONE + MSG_TYPE_A_NUM];
	अन्यथा
		msg = &info->msg[RX_PERIOD_DONE + MSG_TYPE_A_NUM];

	buffer_tail = msg->r_msg.param.buffer_tail;
	pos = buffer_tail * snd_pcm_lib_period_bytes(substream);

	वापस bytes_to_frames(substream->runसमय, pos);
पूर्ण

अटल व्योम imx_rpmsg_समयr_callback(काष्ठा समयr_list *t)
अणु
	काष्ठा stream_समयr  *stream_समयr =
			from_समयr(stream_समयr, t, समयr);
	काष्ठा snd_pcm_substream *substream = stream_समयr->substream;
	काष्ठा rpmsg_info *info = stream_समयr->info;
	काष्ठा rpmsg_msg *msg;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		msg = &info->msg[TX_PERIOD_DONE + MSG_TYPE_A_NUM];
		msg->s_msg.header.cmd = TX_PERIOD_DONE;
	पूर्ण अन्यथा अणु
		msg = &info->msg[RX_PERIOD_DONE + MSG_TYPE_A_NUM];
		msg->s_msg.header.cmd = RX_PERIOD_DONE;
	पूर्ण

	imx_rpmsg_insert_workqueue(substream, msg, info);
पूर्ण

अटल पूर्णांक imx_rpmsg_pcm_खोलो(काष्ठा snd_soc_component *component,
			      काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा rpmsg_info *info = dev_get_drvdata(component->dev);
	काष्ठा rpmsg_msg *msg;
	पूर्णांक ret = 0;
	पूर्णांक cmd;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		msg = &info->msg[TX_OPEN];
		msg->s_msg.header.cmd = TX_OPEN;

		/* reinitialize buffer counter*/
		cmd = TX_PERIOD_DONE + MSG_TYPE_A_NUM;
		info->msg[cmd].s_msg.param.buffer_tail = 0;
		info->msg[cmd].r_msg.param.buffer_tail = 0;
		info->msg[TX_POINTER].r_msg.param.buffer_offset = 0;

	पूर्ण अन्यथा अणु
		msg = &info->msg[RX_OPEN];
		msg->s_msg.header.cmd = RX_OPEN;

		/* reinitialize buffer counter*/
		cmd = RX_PERIOD_DONE + MSG_TYPE_A_NUM;
		info->msg[cmd].s_msg.param.buffer_tail = 0;
		info->msg[cmd].r_msg.param.buffer_tail = 0;
		info->msg[RX_POINTER].r_msg.param.buffer_offset = 0;
	पूर्ण

	info->send_message(msg, info);

	imx_rpmsg_pcm_hardware.period_bytes_max =
			imx_rpmsg_pcm_hardware.buffer_bytes_max / 2;

	snd_soc_set_runसमय_hwparams(substream, &imx_rpmsg_pcm_hardware);

	ret = snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(substream->runसमय,
					    SNDRV_PCM_HW_PARAM_PERIODS);
	अगर (ret < 0)
		वापस ret;

	info->msg_drop_count[substream->stream] = 0;

	/* Create समयr*/
	info->stream_समयr[substream->stream].info = info;
	info->stream_समयr[substream->stream].substream = substream;
	समयr_setup(&info->stream_समयr[substream->stream].समयr,
		    imx_rpmsg_समयr_callback, 0);
	वापस ret;
पूर्ण

अटल पूर्णांक imx_rpmsg_pcm_बंद(काष्ठा snd_soc_component *component,
			       काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा rpmsg_info *info = dev_get_drvdata(component->dev);
	काष्ठा rpmsg_msg *msg;
	पूर्णांक ret = 0;

	/* Flush work in workqueue to make TX_CLOSE is the last message */
	flush_workqueue(info->rpmsg_wq);

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		msg = &info->msg[TX_CLOSE];
		msg->s_msg.header.cmd = TX_CLOSE;
	पूर्ण अन्यथा अणु
		msg = &info->msg[RX_CLOSE];
		msg->s_msg.header.cmd = RX_CLOSE;
	पूर्ण

	info->send_message(msg, info);

	del_समयr(&info->stream_समयr[substream->stream].समयr);

	rtd->dai_link->ignore_suspend = 0;

	अगर (info->msg_drop_count[substream->stream])
		dev_warn(rtd->dev, "Msg is dropped!, number is %d\n",
			 info->msg_drop_count[substream->stream]);

	वापस ret;
पूर्ण

अटल पूर्णांक imx_rpmsg_pcm_prepare(काष्ठा snd_soc_component *component,
				 काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_soc_pcm_runसमय *rtd = substream->निजी_data;
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	काष्ठा fsl_rpmsg *rpmsg = dev_get_drvdata(cpu_dai->dev);

	/*
	 * NON-MMAP mode, NONBLOCK, Version 2, enable lpa in dts
	 * four conditions to determine the lpa is enabled.
	 */
	अगर ((runसमय->access == SNDRV_PCM_ACCESS_RW_INTERLEAVED ||
	     runसमय->access == SNDRV_PCM_ACCESS_RW_NONINTERLEAVED) &&
	     rpmsg->enable_lpa) अणु
		/*
		 * Ignore suspend operation in low घातer mode
		 * M core will जारी playback music on A core suspend.
		 */
		rtd->dai_link->ignore_suspend = 1;
		rpmsg->क्रमce_lpa = 1;
	पूर्ण अन्यथा अणु
		rpmsg->क्रमce_lpa = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक imx_rpmsg_pcm_mmap(काष्ठा snd_soc_component *component,
			      काष्ठा snd_pcm_substream *substream,
			      काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	वापस dma_mmap_wc(substream->pcm->card->dev, vma,
			   runसमय->dma_area,
			   runसमय->dma_addr,
			   runसमय->dma_bytes);
पूर्ण

अटल व्योम imx_rpmsg_pcm_dma_complete(व्योम *arg)
अणु
	काष्ठा snd_pcm_substream *substream = arg;

	snd_pcm_period_elapsed(substream);
पूर्ण

अटल पूर्णांक imx_rpmsg_prepare_and_submit(काष्ठा snd_soc_component *component,
					काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा rpmsg_info *info = dev_get_drvdata(component->dev);
	काष्ठा rpmsg_msg *msg;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		msg = &info->msg[TX_BUFFER];
		msg->s_msg.header.cmd = TX_BUFFER;
	पूर्ण अन्यथा अणु
		msg = &info->msg[RX_BUFFER];
		msg->s_msg.header.cmd = RX_BUFFER;
	पूर्ण

	/* Send buffer address and buffer size */
	msg->s_msg.param.buffer_addr = substream->runसमय->dma_addr;
	msg->s_msg.param.buffer_size = snd_pcm_lib_buffer_bytes(substream);
	msg->s_msg.param.period_size = snd_pcm_lib_period_bytes(substream);
	msg->s_msg.param.buffer_tail = 0;

	info->num_period[substream->stream] = msg->s_msg.param.buffer_size /
					      msg->s_msg.param.period_size;

	info->callback[substream->stream] = imx_rpmsg_pcm_dma_complete;
	info->callback_param[substream->stream] = substream;

	वापस imx_rpmsg_insert_workqueue(substream, msg, info);
पूर्ण

अटल पूर्णांक imx_rpmsg_async_issue_pending(काष्ठा snd_soc_component *component,
					 काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा rpmsg_info *info = dev_get_drvdata(component->dev);
	काष्ठा rpmsg_msg *msg;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		msg = &info->msg[TX_START];
		msg->s_msg.header.cmd = TX_START;
	पूर्ण अन्यथा अणु
		msg = &info->msg[RX_START];
		msg->s_msg.header.cmd = RX_START;
	पूर्ण

	वापस imx_rpmsg_insert_workqueue(substream, msg, info);
पूर्ण

अटल पूर्णांक imx_rpmsg_restart(काष्ठा snd_soc_component *component,
			     काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा rpmsg_info *info = dev_get_drvdata(component->dev);
	काष्ठा rpmsg_msg *msg;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		msg = &info->msg[TX_RESTART];
		msg->s_msg.header.cmd = TX_RESTART;
	पूर्ण अन्यथा अणु
		msg = &info->msg[RX_RESTART];
		msg->s_msg.header.cmd = RX_RESTART;
	पूर्ण

	वापस imx_rpmsg_insert_workqueue(substream, msg, info);
पूर्ण

अटल पूर्णांक imx_rpmsg_छोड़ो(काष्ठा snd_soc_component *component,
			   काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा rpmsg_info *info = dev_get_drvdata(component->dev);
	काष्ठा rpmsg_msg *msg;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		msg = &info->msg[TX_PAUSE];
		msg->s_msg.header.cmd = TX_PAUSE;
	पूर्ण अन्यथा अणु
		msg = &info->msg[RX_PAUSE];
		msg->s_msg.header.cmd = RX_PAUSE;
	पूर्ण

	वापस imx_rpmsg_insert_workqueue(substream, msg, info);
पूर्ण

अटल पूर्णांक imx_rpmsg_terminate_all(काष्ठा snd_soc_component *component,
				   काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा rpmsg_info *info = dev_get_drvdata(component->dev);
	काष्ठा rpmsg_msg *msg;
	पूर्णांक cmd;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		msg = &info->msg[TX_TERMINATE];
		msg->s_msg.header.cmd = TX_TERMINATE;
		/* Clear buffer count*/
		cmd = TX_PERIOD_DONE + MSG_TYPE_A_NUM;
		info->msg[cmd].s_msg.param.buffer_tail = 0;
		info->msg[cmd].r_msg.param.buffer_tail = 0;
		info->msg[TX_POINTER].r_msg.param.buffer_offset = 0;
	पूर्ण अन्यथा अणु
		msg = &info->msg[RX_TERMINATE];
		msg->s_msg.header.cmd = RX_TERMINATE;
		/* Clear buffer count*/
		cmd = RX_PERIOD_DONE + MSG_TYPE_A_NUM;
		info->msg[cmd].s_msg.param.buffer_tail = 0;
		info->msg[cmd].r_msg.param.buffer_tail = 0;
		info->msg[RX_POINTER].r_msg.param.buffer_offset = 0;
	पूर्ण

	del_समयr(&info->stream_समयr[substream->stream].समयr);

	वापस imx_rpmsg_insert_workqueue(substream, msg, info);
पूर्ण

अटल पूर्णांक imx_rpmsg_pcm_trigger(काष्ठा snd_soc_component *component,
				 काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_soc_pcm_runसमय *rtd = substream->निजी_data;
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	काष्ठा fsl_rpmsg *rpmsg = dev_get_drvdata(cpu_dai->dev);
	पूर्णांक ret = 0;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		ret = imx_rpmsg_prepare_and_submit(component, substream);
		अगर (ret)
			वापस ret;
		ret = imx_rpmsg_async_issue_pending(component, substream);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_RESUME:
		अगर (rpmsg->क्रमce_lpa)
			अवरोध;
		fallthrough;
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		ret = imx_rpmsg_restart(component, substream);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		अगर (!rpmsg->क्रमce_lpa) अणु
			अगर (runसमय->info & SNDRV_PCM_INFO_PAUSE)
				ret = imx_rpmsg_छोड़ो(component, substream);
			अन्यथा
				ret = imx_rpmsg_terminate_all(component, substream);
		पूर्ण
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		ret = imx_rpmsg_छोड़ो(component, substream);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		ret = imx_rpmsg_terminate_all(component, substream);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

/*
 * imx_rpmsg_pcm_ack
 *
 * Send the period index to M core through rpmsg, but not send
 * all the period index to M core, reduce some unnessesary msg
 * to reduce the pressure of rpmsg bandwidth.
 */
अटल पूर्णांक imx_rpmsg_pcm_ack(काष्ठा snd_soc_component *component,
			     काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_soc_pcm_runसमय *rtd = substream->निजी_data;
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	काष्ठा fsl_rpmsg *rpmsg = dev_get_drvdata(cpu_dai->dev);
	काष्ठा rpmsg_info *info = dev_get_drvdata(component->dev);
	snd_pcm_uframes_t period_size = runसमय->period_size;
	snd_pcm_sframes_t avail;
	काष्ठा समयr_list *समयr;
	काष्ठा rpmsg_msg *msg;
	अचिन्हित दीर्घ flags;
	पूर्णांक buffer_tail = 0;
	पूर्णांक written_num = 0;

	अगर (!rpmsg->क्रमce_lpa)
		वापस 0;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		msg = &info->msg[TX_PERIOD_DONE + MSG_TYPE_A_NUM];
		msg->s_msg.header.cmd = TX_PERIOD_DONE;
	पूर्ण अन्यथा अणु
		msg = &info->msg[RX_PERIOD_DONE + MSG_TYPE_A_NUM];
		msg->s_msg.header.cmd = RX_PERIOD_DONE;
	पूर्ण

	msg->s_msg.header.type = MSG_TYPE_C;

	buffer_tail = (frames_to_bytes(runसमय, runसमय->control->appl_ptr) %
		       snd_pcm_lib_buffer_bytes(substream));
	buffer_tail = buffer_tail / snd_pcm_lib_period_bytes(substream);

	/* There is update क्रम period index */
	अगर (buffer_tail != msg->s_msg.param.buffer_tail) अणु
		written_num = buffer_tail - msg->s_msg.param.buffer_tail;
		अगर (written_num < 0)
			written_num += runसमय->periods;

		msg->s_msg.param.buffer_tail = buffer_tail;

		/* The notअगरication message is updated to latest */
		spin_lock_irqsave(&info->lock[substream->stream], flags);
		स_नकल(&info->notअगरy[substream->stream], msg,
		       माप(काष्ठा rpmsg_s_msg));
		info->notअगरy_updated[substream->stream] = true;
		spin_unlock_irqrestore(&info->lock[substream->stream], flags);

		अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
			avail = snd_pcm_playback_hw_avail(runसमय);
		अन्यथा
			avail = snd_pcm_capture_hw_avail(runसमय);

		समयr = &info->stream_समयr[substream->stream].समयr;
		/*
		 * If the data in the buffer is less than one period beक्रमe
		 * this fill, which means the data may not enough on M
		 * core side, we need to send message immediately to let
		 * M core know the poपूर्णांकer is updated.
		 * अगर there is more than one period data in the buffer beक्रमe
		 * this fill, which means the data is enough on M core side,
		 * we can delay one period (using समयr) to send the message
		 * क्रम reduce the message number in workqueue, because the
		 * poपूर्णांकer may be updated by ack function later, we can
		 * send latest poपूर्णांकer to M core side.
		 */
		अगर ((avail - written_num * period_size) <= period_size) अणु
			imx_rpmsg_insert_workqueue(substream, msg, info);
		पूर्ण अन्यथा अगर (rpmsg->क्रमce_lpa && !समयr_pending(समयr)) अणु
			पूर्णांक समय_msec;

			समय_msec = (पूर्णांक)(runसमय->period_size * 1000 / runसमय->rate);
			mod_समयr(समयr, jअगरfies + msecs_to_jअगरfies(समय_msec));
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक imx_rpmsg_pcm_pपुनः_स्मृतिate_dma_buffer(काष्ठा snd_pcm *pcm,
						पूर्णांक stream, पूर्णांक size)
अणु
	काष्ठा snd_pcm_substream *substream = pcm->streams[stream].substream;
	काष्ठा snd_dma_buffer *buf = &substream->dma_buffer;

	buf->dev.type = SNDRV_DMA_TYPE_DEV;
	buf->dev.dev = pcm->card->dev;
	buf->निजी_data = शून्य;
	buf->area = dma_alloc_wc(pcm->card->dev, size,
				 &buf->addr, GFP_KERNEL);
	अगर (!buf->area)
		वापस -ENOMEM;

	buf->bytes = size;
	वापस 0;
पूर्ण

अटल व्योम imx_rpmsg_pcm_मुक्त_dma_buffers(काष्ठा snd_soc_component *component,
					   काष्ठा snd_pcm *pcm)
अणु
	काष्ठा snd_pcm_substream *substream;
	काष्ठा snd_dma_buffer *buf;
	पूर्णांक stream;

	क्रम (stream = SNDRV_PCM_STREAM_PLAYBACK;
	     stream < SNDRV_PCM_STREAM_LAST; stream++) अणु
		substream = pcm->streams[stream].substream;
		अगर (!substream)
			जारी;

		buf = &substream->dma_buffer;
		अगर (!buf->area)
			जारी;

		dma_मुक्त_wc(pcm->card->dev, buf->bytes,
			    buf->area, buf->addr);
		buf->area = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक imx_rpmsg_pcm_new(काष्ठा snd_soc_component *component,
			     काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_card *card = rtd->card->snd_card;
	काष्ठा snd_pcm *pcm = rtd->pcm;
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	काष्ठा fsl_rpmsg *rpmsg = dev_get_drvdata(cpu_dai->dev);
	पूर्णांक ret;

	ret = dma_coerce_mask_and_coherent(card->dev, DMA_BIT_MASK(32));
	अगर (ret)
		वापस ret;

	अगर (pcm->streams[SNDRV_PCM_STREAM_PLAYBACK].substream) अणु
		ret = imx_rpmsg_pcm_pपुनः_स्मृतिate_dma_buffer(pcm, SNDRV_PCM_STREAM_PLAYBACK,
							   rpmsg->buffer_size);
		अगर (ret)
			जाओ out;
	पूर्ण

	अगर (pcm->streams[SNDRV_PCM_STREAM_CAPTURE].substream) अणु
		ret = imx_rpmsg_pcm_pपुनः_स्मृतिate_dma_buffer(pcm, SNDRV_PCM_STREAM_CAPTURE,
							   rpmsg->buffer_size);
		अगर (ret)
			जाओ out;
	पूर्ण

	imx_rpmsg_pcm_hardware.buffer_bytes_max = rpmsg->buffer_size;
out:
	/* मुक्त pपुनः_स्मृतिated buffers in हाल of error */
	अगर (ret)
		imx_rpmsg_pcm_मुक्त_dma_buffers(component, pcm);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver imx_rpmsg_soc_component = अणु
	.name		= IMX_PCM_DRV_NAME,
	.pcm_स्थिरruct	= imx_rpmsg_pcm_new,
	.pcm_deकाष्ठा	= imx_rpmsg_pcm_मुक्त_dma_buffers,
	.खोलो		= imx_rpmsg_pcm_खोलो,
	.बंद		= imx_rpmsg_pcm_बंद,
	.hw_params	= imx_rpmsg_pcm_hw_params,
	.hw_मुक्त	= imx_rpmsg_pcm_hw_मुक्त,
	.trigger	= imx_rpmsg_pcm_trigger,
	.poपूर्णांकer	= imx_rpmsg_pcm_poपूर्णांकer,
	.mmap		= imx_rpmsg_pcm_mmap,
	.ack		= imx_rpmsg_pcm_ack,
	.prepare	= imx_rpmsg_pcm_prepare,
पूर्ण;

अटल व्योम imx_rpmsg_pcm_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा work_of_rpmsg *work_of_rpmsg;
	bool is_notअगरication = false;
	काष्ठा rpmsg_info *info;
	काष्ठा rpmsg_msg msg;
	अचिन्हित दीर्घ flags;

	work_of_rpmsg = container_of(work, काष्ठा work_of_rpmsg, work);
	info = work_of_rpmsg->info;

	/*
	 * Every work in the work queue, first we check अगर there
	 * is update क्रम period is filled, because there may be not
	 * enough data in M core side, need to let M core know
	 * data is updated immediately.
	 */
	spin_lock_irqsave(&info->lock[TX], flags);
	अगर (info->notअगरy_updated[TX]) अणु
		स_नकल(&msg, &info->notअगरy[TX], माप(काष्ठा rpmsg_s_msg));
		info->notअगरy_updated[TX] = false;
		spin_unlock_irqrestore(&info->lock[TX], flags);
		info->send_message(&msg, info);
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&info->lock[TX], flags);
	पूर्ण

	spin_lock_irqsave(&info->lock[RX], flags);
	अगर (info->notअगरy_updated[RX]) अणु
		स_नकल(&msg, &info->notअगरy[RX], माप(काष्ठा rpmsg_s_msg));
		info->notअगरy_updated[RX] = false;
		spin_unlock_irqrestore(&info->lock[RX], flags);
		info->send_message(&msg, info);
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&info->lock[RX], flags);
	पूर्ण

	/* Skip the notअगरication message क्रम it has been processed above */
	अगर (work_of_rpmsg->msg.s_msg.header.type == MSG_TYPE_C &&
	    (work_of_rpmsg->msg.s_msg.header.cmd == TX_PERIOD_DONE ||
	     work_of_rpmsg->msg.s_msg.header.cmd == RX_PERIOD_DONE))
		is_notअगरication = true;

	अगर (!is_notअगरication)
		info->send_message(&work_of_rpmsg->msg, info);

	/* update पढ़ो index */
	spin_lock_irqsave(&info->wq_lock, flags);
	info->work_पढ़ो_index++;
	info->work_पढ़ो_index %= WORK_MAX_NUM;
	spin_unlock_irqrestore(&info->wq_lock, flags);
पूर्ण

अटल पूर्णांक imx_rpmsg_pcm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_component *component;
	काष्ठा rpmsg_info *info;
	पूर्णांक ret, i;

	info = devm_kzalloc(&pdev->dev, माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, info);

	info->rpdev = container_of(pdev->dev.parent, काष्ठा rpmsg_device, dev);
	info->dev = &pdev->dev;
	/* Setup work queue */
	info->rpmsg_wq = alloc_ordered_workqueue("rpmsg_audio",
						 WQ_HIGHPRI |
						 WQ_UNBOUND |
						 WQ_FREEZABLE);
	अगर (!info->rpmsg_wq) अणु
		dev_err(&pdev->dev, "workqueue create failed\n");
		वापस -ENOMEM;
	पूर्ण

	/* Write index initialize 1, make it dअगरfer with the पढ़ो index */
	info->work_ग_लिखो_index = 1;
	info->send_message = imx_rpmsg_pcm_send_message;

	क्रम (i = 0; i < WORK_MAX_NUM; i++) अणु
		INIT_WORK(&info->work_list[i].work, imx_rpmsg_pcm_work);
		info->work_list[i].info = info;
	पूर्ण

	/* Initialize msg */
	क्रम (i = 0; i < MSG_MAX_NUM; i++) अणु
		info->msg[i].s_msg.header.cate  = IMX_RPMSG_AUDIO;
		info->msg[i].s_msg.header.major = IMX_RMPSG_MAJOR;
		info->msg[i].s_msg.header.minor = IMX_RMPSG_MINOR;
		info->msg[i].s_msg.header.type  = MSG_TYPE_A;
		info->msg[i].s_msg.param.audioindex = 0;
	पूर्ण

	init_completion(&info->cmd_complete);
	mutex_init(&info->msg_lock);
	spin_lock_init(&info->lock[TX]);
	spin_lock_init(&info->lock[RX]);
	spin_lock_init(&info->wq_lock);

	ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev,
					      &imx_rpmsg_soc_component,
					      शून्य, 0);
	अगर (ret)
		जाओ fail;

	component = snd_soc_lookup_component(&pdev->dev, IMX_PCM_DRV_NAME);
	अगर (!component) अणु
		ret = -EINVAL;
		जाओ fail;
	पूर्ण
#अगर_घोषित CONFIG_DEBUG_FS
	component->debugfs_prefix = "rpmsg";
#पूर्ण_अगर

	वापस 0;

fail:
	अगर (info->rpmsg_wq)
		destroy_workqueue(info->rpmsg_wq);

	वापस ret;
पूर्ण

अटल पूर्णांक imx_rpmsg_pcm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rpmsg_info *info = platक्रमm_get_drvdata(pdev);

	अगर (info->rpmsg_wq)
		destroy_workqueue(info->rpmsg_wq);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक imx_rpmsg_pcm_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा rpmsg_info *info = dev_get_drvdata(dev);

	cpu_latency_qos_add_request(&info->pm_qos_req, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक imx_rpmsg_pcm_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा rpmsg_info *info = dev_get_drvdata(dev);

	cpu_latency_qos_हटाओ_request(&info->pm_qos_req);

	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक imx_rpmsg_pcm_suspend(काष्ठा device *dev)
अणु
	काष्ठा rpmsg_info *info = dev_get_drvdata(dev);
	काष्ठा rpmsg_msg *rpmsg_tx;
	काष्ठा rpmsg_msg *rpmsg_rx;

	rpmsg_tx = &info->msg[TX_SUSPEND];
	rpmsg_rx = &info->msg[RX_SUSPEND];

	rpmsg_tx->s_msg.header.cmd = TX_SUSPEND;
	info->send_message(rpmsg_tx, info);

	rpmsg_rx->s_msg.header.cmd = RX_SUSPEND;
	info->send_message(rpmsg_rx, info);

	वापस 0;
पूर्ण

अटल पूर्णांक imx_rpmsg_pcm_resume(काष्ठा device *dev)
अणु
	काष्ठा rpmsg_info *info = dev_get_drvdata(dev);
	काष्ठा rpmsg_msg *rpmsg_tx;
	काष्ठा rpmsg_msg *rpmsg_rx;

	rpmsg_tx = &info->msg[TX_RESUME];
	rpmsg_rx = &info->msg[RX_RESUME];

	rpmsg_tx->s_msg.header.cmd = TX_RESUME;
	info->send_message(rpmsg_tx, info);

	rpmsg_rx->s_msg.header.cmd = RX_RESUME;
	info->send_message(rpmsg_rx, info);

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल स्थिर काष्ठा dev_pm_ops imx_rpmsg_pcm_pm_ops = अणु
	SET_RUNTIME_PM_OPS(imx_rpmsg_pcm_runसमय_suspend,
			   imx_rpmsg_pcm_runसमय_resume,
			   शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(imx_rpmsg_pcm_suspend,
				imx_rpmsg_pcm_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver imx_pcm_rpmsg_driver = अणु
	.probe  = imx_rpmsg_pcm_probe,
	.हटाओ	= imx_rpmsg_pcm_हटाओ,
	.driver = अणु
		.name = IMX_PCM_DRV_NAME,
		.pm = &imx_rpmsg_pcm_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(imx_pcm_rpmsg_driver);

MODULE_DESCRIPTION("Freescale SoC Audio RPMSG PCM interface");
MODULE_AUTHOR("Shengjiu Wang <shengjiu.wang@nxp.com>");
MODULE_ALIAS("platform:" IMX_PCM_DRV_NAME);
MODULE_LICENSE("GPL v2");
