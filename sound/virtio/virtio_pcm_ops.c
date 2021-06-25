<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * virtio-snd: Virtio sound device
 * Copyright (C) 2021 OpenSynergy GmbH
 */
#समावेश <sound/pcm_params.h>

#समावेश "virtio_card.h"

/*
 * I/O messages lअगरeसमय
 * ---------------------
 *
 * Allocation:
 *   Messages are initially allocated in the ops->hw_params() after the size and
 *   number of periods have been successfully negotiated.
 *
 * Freeing:
 *   Messages can be safely मुक्तd after the queue has been successfully flushed
 *   (RELEASE command in the ops->sync_stop()) and the ops->hw_मुक्त() has been
 *   called.
 *
 *   When the substream stops, the ops->sync_stop() रुकोs until the device has
 *   completed all pending messages. This रुको can be पूर्णांकerrupted either by a
 *   संकेत or due to a समयout. In this हाल, the device can still access
 *   messages even after calling ops->hw_मुक्त(). It can also issue an पूर्णांकerrupt,
 *   and the पूर्णांकerrupt handler will also try to access message काष्ठाures.
 *
 *   Thereक्रमe, मुक्तing of alपढ़ोy allocated messages occurs:
 *
 *   - in ops->hw_params(), अगर this चालक was called several बार in a row,
 *     or अगर ops->hw_मुक्त() failed to मुक्त messages previously;
 *
 *   - in ops->hw_मुक्त(), अगर the queue has been successfully flushed;
 *
 *   - in dev->release().
 */

/* Map क्रम converting ALSA क्रमmat to VirtIO क्रमmat. */
काष्ठा virtsnd_a2v_क्रमmat अणु
	snd_pcm_क्रमmat_t alsa_bit;
	अचिन्हित पूर्णांक vio_bit;
पूर्ण;

अटल स्थिर काष्ठा virtsnd_a2v_क्रमmat g_a2v_क्रमmat_map[] = अणु
	अणु SNDRV_PCM_FORMAT_IMA_ADPCM, VIRTIO_SND_PCM_FMT_IMA_ADPCM पूर्ण,
	अणु SNDRV_PCM_FORMAT_MU_LAW, VIRTIO_SND_PCM_FMT_MU_LAW पूर्ण,
	अणु SNDRV_PCM_FORMAT_A_LAW, VIRTIO_SND_PCM_FMT_A_LAW पूर्ण,
	अणु SNDRV_PCM_FORMAT_S8, VIRTIO_SND_PCM_FMT_S8 पूर्ण,
	अणु SNDRV_PCM_FORMAT_U8, VIRTIO_SND_PCM_FMT_U8 पूर्ण,
	अणु SNDRV_PCM_FORMAT_S16_LE, VIRTIO_SND_PCM_FMT_S16 पूर्ण,
	अणु SNDRV_PCM_FORMAT_U16_LE, VIRTIO_SND_PCM_FMT_U16 पूर्ण,
	अणु SNDRV_PCM_FORMAT_S18_3LE, VIRTIO_SND_PCM_FMT_S18_3 पूर्ण,
	अणु SNDRV_PCM_FORMAT_U18_3LE, VIRTIO_SND_PCM_FMT_U18_3 पूर्ण,
	अणु SNDRV_PCM_FORMAT_S20_3LE, VIRTIO_SND_PCM_FMT_S20_3 पूर्ण,
	अणु SNDRV_PCM_FORMAT_U20_3LE, VIRTIO_SND_PCM_FMT_U20_3 पूर्ण,
	अणु SNDRV_PCM_FORMAT_S24_3LE, VIRTIO_SND_PCM_FMT_S24_3 पूर्ण,
	अणु SNDRV_PCM_FORMAT_U24_3LE, VIRTIO_SND_PCM_FMT_U24_3 पूर्ण,
	अणु SNDRV_PCM_FORMAT_S20_LE, VIRTIO_SND_PCM_FMT_S20 पूर्ण,
	अणु SNDRV_PCM_FORMAT_U20_LE, VIRTIO_SND_PCM_FMT_U20 पूर्ण,
	अणु SNDRV_PCM_FORMAT_S24_LE, VIRTIO_SND_PCM_FMT_S24 पूर्ण,
	अणु SNDRV_PCM_FORMAT_U24_LE, VIRTIO_SND_PCM_FMT_U24 पूर्ण,
	अणु SNDRV_PCM_FORMAT_S32_LE, VIRTIO_SND_PCM_FMT_S32 पूर्ण,
	अणु SNDRV_PCM_FORMAT_U32_LE, VIRTIO_SND_PCM_FMT_U32 पूर्ण,
	अणु SNDRV_PCM_FORMAT_FLOAT_LE, VIRTIO_SND_PCM_FMT_FLOAT पूर्ण,
	अणु SNDRV_PCM_FORMAT_FLOAT64_LE, VIRTIO_SND_PCM_FMT_FLOAT64 पूर्ण,
	अणु SNDRV_PCM_FORMAT_DSD_U8, VIRTIO_SND_PCM_FMT_DSD_U8 पूर्ण,
	अणु SNDRV_PCM_FORMAT_DSD_U16_LE, VIRTIO_SND_PCM_FMT_DSD_U16 पूर्ण,
	अणु SNDRV_PCM_FORMAT_DSD_U32_LE, VIRTIO_SND_PCM_FMT_DSD_U32 पूर्ण,
	अणु SNDRV_PCM_FORMAT_IEC958_SUBFRAME_LE,
	  VIRTIO_SND_PCM_FMT_IEC958_SUBFRAME पूर्ण
पूर्ण;

/* Map क्रम converting ALSA frame rate to VirtIO frame rate. */
काष्ठा virtsnd_a2v_rate अणु
	अचिन्हित पूर्णांक rate;
	अचिन्हित पूर्णांक vio_bit;
पूर्ण;

अटल स्थिर काष्ठा virtsnd_a2v_rate g_a2v_rate_map[] = अणु
	अणु 5512, VIRTIO_SND_PCM_RATE_5512 पूर्ण,
	अणु 8000, VIRTIO_SND_PCM_RATE_8000 पूर्ण,
	अणु 11025, VIRTIO_SND_PCM_RATE_11025 पूर्ण,
	अणु 16000, VIRTIO_SND_PCM_RATE_16000 पूर्ण,
	अणु 22050, VIRTIO_SND_PCM_RATE_22050 पूर्ण,
	अणु 32000, VIRTIO_SND_PCM_RATE_32000 पूर्ण,
	अणु 44100, VIRTIO_SND_PCM_RATE_44100 पूर्ण,
	अणु 48000, VIRTIO_SND_PCM_RATE_48000 पूर्ण,
	अणु 64000, VIRTIO_SND_PCM_RATE_64000 पूर्ण,
	अणु 88200, VIRTIO_SND_PCM_RATE_88200 पूर्ण,
	अणु 96000, VIRTIO_SND_PCM_RATE_96000 पूर्ण,
	अणु 176400, VIRTIO_SND_PCM_RATE_176400 पूर्ण,
	अणु 192000, VIRTIO_SND_PCM_RATE_192000 पूर्ण
पूर्ण;

अटल पूर्णांक virtsnd_pcm_sync_stop(काष्ठा snd_pcm_substream *substream);

/**
 * virtsnd_pcm_खोलो() - Open the PCM substream.
 * @substream: Kernel ALSA substream.
 *
 * Context: Process context.
 * Return: 0 on success, -त्रुटि_सं on failure.
 */
अटल पूर्णांक virtsnd_pcm_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा virtio_pcm *vpcm = snd_pcm_substream_chip(substream);
	काष्ठा virtio_pcm_stream *vs = &vpcm->streams[substream->stream];
	काष्ठा virtio_pcm_substream *vss = vs->substreams[substream->number];

	substream->runसमय->hw = vss->hw;
	substream->निजी_data = vss;

	snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(substream->runसमय,
				      SNDRV_PCM_HW_PARAM_PERIODS);

	vss->stopped = !!virtsnd_pcm_msg_pending_num(vss);
	vss->suspended = false;

	/*
	 * If the substream has alपढ़ोy been used, then the I/O queue may be in
	 * an invalid state. Just in हाल, we करो a check and try to वापस the
	 * queue to its original state, अगर necessary.
	 */
	वापस virtsnd_pcm_sync_stop(substream);
पूर्ण

/**
 * virtsnd_pcm_बंद() - Close the PCM substream.
 * @substream: Kernel ALSA substream.
 *
 * Context: Process context.
 * Return: 0.
 */
अटल पूर्णांक virtsnd_pcm_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	वापस 0;
पूर्ण

/**
 * virtsnd_pcm_dev_set_params() - Set the parameters of the PCM substream on
 *                                the device side.
 * @vss: VirtIO PCM substream.
 * @buffer_bytes: Size of the hardware buffer.
 * @period_bytes: Size of the hardware period.
 * @channels: Selected number of channels.
 * @क्रमmat: Selected sample क्रमmat (SNDRV_PCM_FORMAT_XXX).
 * @rate: Selected frame rate.
 *
 * Context: Any context that permits to sleep.
 * Return: 0 on success, -त्रुटि_सं on failure.
 */
अटल पूर्णांक virtsnd_pcm_dev_set_params(काष्ठा virtio_pcm_substream *vss,
				      अचिन्हित पूर्णांक buffer_bytes,
				      अचिन्हित पूर्णांक period_bytes,
				      अचिन्हित पूर्णांक channels,
				      snd_pcm_क्रमmat_t क्रमmat,
				      अचिन्हित पूर्णांक rate)
अणु
	काष्ठा virtio_snd_msg *msg;
	काष्ठा virtio_snd_pcm_set_params *request;
	अचिन्हित पूर्णांक i;
	पूर्णांक vक्रमmat = -1;
	पूर्णांक vrate = -1;

	क्रम (i = 0; i < ARRAY_SIZE(g_a2v_क्रमmat_map); ++i)
		अगर (g_a2v_क्रमmat_map[i].alsa_bit == क्रमmat) अणु
			vक्रमmat = g_a2v_क्रमmat_map[i].vio_bit;

			अवरोध;
		पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(g_a2v_rate_map); ++i)
		अगर (g_a2v_rate_map[i].rate == rate) अणु
			vrate = g_a2v_rate_map[i].vio_bit;

			अवरोध;
		पूर्ण

	अगर (vक्रमmat == -1 || vrate == -1)
		वापस -EINVAL;

	msg = virtsnd_pcm_ctl_msg_alloc(vss, VIRTIO_SND_R_PCM_SET_PARAMS,
					GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	request = virtsnd_ctl_msg_request(msg);
	request->buffer_bytes = cpu_to_le32(buffer_bytes);
	request->period_bytes = cpu_to_le32(period_bytes);
	request->channels = channels;
	request->क्रमmat = vक्रमmat;
	request->rate = vrate;

	अगर (vss->features & (1U << VIRTIO_SND_PCM_F_MSG_POLLING))
		request->features |=
			cpu_to_le32(1U << VIRTIO_SND_PCM_F_MSG_POLLING);

	अगर (vss->features & (1U << VIRTIO_SND_PCM_F_EVT_XRUNS))
		request->features |=
			cpu_to_le32(1U << VIRTIO_SND_PCM_F_EVT_XRUNS);

	वापस virtsnd_ctl_msg_send_sync(vss->snd, msg);
पूर्ण

/**
 * virtsnd_pcm_hw_params() - Set the parameters of the PCM substream.
 * @substream: Kernel ALSA substream.
 * @hw_params: Hardware parameters.
 *
 * Context: Process context.
 * Return: 0 on success, -त्रुटि_सं on failure.
 */
अटल पूर्णांक virtsnd_pcm_hw_params(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा virtio_pcm_substream *vss = snd_pcm_substream_chip(substream);
	काष्ठा virtio_device *vdev = vss->snd->vdev;
	पूर्णांक rc;

	अगर (virtsnd_pcm_msg_pending_num(vss)) अणु
		dev_err(&vdev->dev, "SID %u: invalid I/O queue state\n",
			vss->sid);
		वापस -EBADFD;
	पूर्ण

	rc = virtsnd_pcm_dev_set_params(vss, params_buffer_bytes(hw_params),
					params_period_bytes(hw_params),
					params_channels(hw_params),
					params_क्रमmat(hw_params),
					params_rate(hw_params));
	अगर (rc)
		वापस rc;

	/*
	 * Free previously allocated messages अगर ops->hw_params() is called
	 * several बार in a row, or अगर ops->hw_मुक्त() failed to मुक्त messages.
	 */
	virtsnd_pcm_msg_मुक्त(vss);

	वापस virtsnd_pcm_msg_alloc(vss, params_periods(hw_params),
				     params_period_bytes(hw_params));
पूर्ण

/**
 * virtsnd_pcm_hw_मुक्त() - Reset the parameters of the PCM substream.
 * @substream: Kernel ALSA substream.
 *
 * Context: Process context.
 * Return: 0
 */
अटल पूर्णांक virtsnd_pcm_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा virtio_pcm_substream *vss = snd_pcm_substream_chip(substream);

	/* If the queue is flushed, we can safely मुक्त the messages here. */
	अगर (!virtsnd_pcm_msg_pending_num(vss))
		virtsnd_pcm_msg_मुक्त(vss);

	वापस 0;
पूर्ण

/**
 * virtsnd_pcm_prepare() - Prepare the PCM substream.
 * @substream: Kernel ALSA substream.
 *
 * Context: Process context.
 * Return: 0 on success, -त्रुटि_सं on failure.
 */
अटल पूर्णांक virtsnd_pcm_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा virtio_pcm_substream *vss = snd_pcm_substream_chip(substream);
	काष्ठा virtio_device *vdev = vss->snd->vdev;
	काष्ठा virtio_snd_msg *msg;

	अगर (!vss->suspended) अणु
		अगर (virtsnd_pcm_msg_pending_num(vss)) अणु
			dev_err(&vdev->dev, "SID %u: invalid I/O queue state\n",
				vss->sid);
			वापस -EBADFD;
		पूर्ण

		vss->buffer_bytes = snd_pcm_lib_buffer_bytes(substream);
		vss->hw_ptr = 0;
		vss->msg_last_enqueued = -1;
	पूर्ण अन्यथा अणु
		काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
		अचिन्हित पूर्णांक buffer_bytes = snd_pcm_lib_buffer_bytes(substream);
		अचिन्हित पूर्णांक period_bytes = snd_pcm_lib_period_bytes(substream);
		पूर्णांक rc;

		rc = virtsnd_pcm_dev_set_params(vss, buffer_bytes, period_bytes,
						runसमय->channels,
						runसमय->क्रमmat, runसमय->rate);
		अगर (rc)
			वापस rc;
	पूर्ण

	vss->xfer_xrun = false;
	vss->suspended = false;
	vss->msg_count = 0;

	msg = virtsnd_pcm_ctl_msg_alloc(vss, VIRTIO_SND_R_PCM_PREPARE,
					GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	वापस virtsnd_ctl_msg_send_sync(vss->snd, msg);
पूर्ण

/**
 * virtsnd_pcm_trigger() - Process command क्रम the PCM substream.
 * @substream: Kernel ALSA substream.
 * @command: Substream command (SNDRV_PCM_TRIGGER_XXX).
 *
 * Context: Any context. Takes and releases the VirtIO substream spinlock.
 *          May take and release the tx/rx queue spinlock.
 * Return: 0 on success, -त्रुटि_सं on failure.
 */
अटल पूर्णांक virtsnd_pcm_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक command)
अणु
	काष्ठा virtio_pcm_substream *vss = snd_pcm_substream_chip(substream);
	काष्ठा virtio_snd *snd = vss->snd;
	काष्ठा virtio_snd_queue *queue;
	काष्ठा virtio_snd_msg *msg;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	चयन (command) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		queue = virtsnd_pcm_queue(vss);

		spin_lock_irqsave(&queue->lock, flags);
		spin_lock(&vss->lock);
		rc = virtsnd_pcm_msg_send(vss);
		अगर (!rc)
			vss->xfer_enabled = true;
		spin_unlock(&vss->lock);
		spin_unlock_irqrestore(&queue->lock, flags);
		अगर (rc)
			वापस rc;

		msg = virtsnd_pcm_ctl_msg_alloc(vss, VIRTIO_SND_R_PCM_START,
						GFP_KERNEL);
		अगर (!msg) अणु
			spin_lock_irqsave(&vss->lock, flags);
			vss->xfer_enabled = false;
			spin_unlock_irqrestore(&vss->lock, flags);

			वापस -ENOMEM;
		पूर्ण

		वापस virtsnd_ctl_msg_send_sync(snd, msg);
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		vss->suspended = true;
		fallthrough;
	हाल SNDRV_PCM_TRIGGER_STOP:
		vss->stopped = true;
		fallthrough;
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		spin_lock_irqsave(&vss->lock, flags);
		vss->xfer_enabled = false;
		spin_unlock_irqrestore(&vss->lock, flags);

		msg = virtsnd_pcm_ctl_msg_alloc(vss, VIRTIO_SND_R_PCM_STOP,
						GFP_KERNEL);
		अगर (!msg)
			वापस -ENOMEM;

		वापस virtsnd_ctl_msg_send_sync(snd, msg);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

/**
 * virtsnd_pcm_sync_stop() - Synchronous PCM substream stop.
 * @substream: Kernel ALSA substream.
 *
 * The function can be called both from the upper level or from the driver
 * itself.
 *
 * Context: Process context. Takes and releases the VirtIO substream spinlock.
 * Return: 0 on success, -त्रुटि_सं on failure.
 */
अटल पूर्णांक virtsnd_pcm_sync_stop(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा virtio_pcm_substream *vss = snd_pcm_substream_chip(substream);
	काष्ठा virtio_snd *snd = vss->snd;
	काष्ठा virtio_snd_msg *msg;
	अचिन्हित पूर्णांक js = msecs_to_jअगरfies(virtsnd_msg_समयout_ms);
	पूर्णांक rc;

	cancel_work_sync(&vss->elapsed_period);

	अगर (!vss->stopped)
		वापस 0;

	msg = virtsnd_pcm_ctl_msg_alloc(vss, VIRTIO_SND_R_PCM_RELEASE,
					GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	rc = virtsnd_ctl_msg_send_sync(snd, msg);
	अगर (rc)
		वापस rc;

	/*
	 * The spec states that upon receipt of the RELEASE command "the device
	 * MUST complete all pending I/O messages क्रम the specअगरied stream ID".
	 * Thus, we consider the असलence of I/O messages in the queue as an
	 * indication that the substream has been released.
	 */
	rc = रुको_event_पूर्णांकerruptible_समयout(vss->msg_empty,
					      !virtsnd_pcm_msg_pending_num(vss),
					      js);
	अगर (rc <= 0) अणु
		dev_warn(&snd->vdev->dev, "SID %u: failed to flush I/O queue\n",
			 vss->sid);

		वापस !rc ? -ETIMEDOUT : rc;
	पूर्ण

	vss->stopped = false;

	वापस 0;
पूर्ण

/**
 * virtsnd_pcm_poपूर्णांकer() - Get the current hardware position क्रम the PCM
 *                         substream.
 * @substream: Kernel ALSA substream.
 *
 * Context: Any context. Takes and releases the VirtIO substream spinlock.
 * Return: Hardware position in frames inside [0 ... buffer_size) range.
 */
अटल snd_pcm_uframes_t
virtsnd_pcm_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा virtio_pcm_substream *vss = snd_pcm_substream_chip(substream);
	snd_pcm_uframes_t hw_ptr = SNDRV_PCM_POS_XRUN;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&vss->lock, flags);
	अगर (!vss->xfer_xrun)
		hw_ptr = bytes_to_frames(substream->runसमय, vss->hw_ptr);
	spin_unlock_irqrestore(&vss->lock, flags);

	वापस hw_ptr;
पूर्ण

/* PCM substream चालकs map. */
स्थिर काष्ठा snd_pcm_ops virtsnd_pcm_ops = अणु
	.खोलो = virtsnd_pcm_खोलो,
	.बंद = virtsnd_pcm_बंद,
	.ioctl = snd_pcm_lib_ioctl,
	.hw_params = virtsnd_pcm_hw_params,
	.hw_मुक्त = virtsnd_pcm_hw_मुक्त,
	.prepare = virtsnd_pcm_prepare,
	.trigger = virtsnd_pcm_trigger,
	.sync_stop = virtsnd_pcm_sync_stop,
	.poपूर्णांकer = virtsnd_pcm_poपूर्णांकer,
पूर्ण;
