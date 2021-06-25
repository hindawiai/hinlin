<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * virtio-snd: Virtio sound device
 * Copyright (C) 2021 OpenSynergy GmbH
 */
#समावेश <sound/pcm_params.h>

#समावेश "virtio_card.h"

/**
 * काष्ठा virtio_pcm_msg - VirtIO I/O message.
 * @substream: VirtIO PCM substream.
 * @xfer: Request header payload.
 * @status: Response header payload.
 * @length: Data length in bytes.
 * @sgs: Payload scatter-gather table.
 */
काष्ठा virtio_pcm_msg अणु
	काष्ठा virtio_pcm_substream *substream;
	काष्ठा virtio_snd_pcm_xfer xfer;
	काष्ठा virtio_snd_pcm_status status;
	माप_प्रकार length;
	काष्ठा scatterlist sgs[0];
पूर्ण;

/**
 * क्रमागत pcm_msg_sg_index - Index values क्रम the virtio_pcm_msg->sgs field in
 *                         an I/O message.
 * @PCM_MSG_SG_XFER: Element containing a virtio_snd_pcm_xfer काष्ठाure.
 * @PCM_MSG_SG_STATUS: Element containing a virtio_snd_pcm_status काष्ठाure.
 * @PCM_MSG_SG_DATA: The first element containing a data buffer.
 */
क्रमागत pcm_msg_sg_index अणु
	PCM_MSG_SG_XFER = 0,
	PCM_MSG_SG_STATUS,
	PCM_MSG_SG_DATA
पूर्ण;

/**
 * virtsnd_pcm_sg_num() - Count the number of sg-elements required to represent
 *                        vदो_स्मृति'ed buffer.
 * @data: Poपूर्णांकer to vदो_स्मृति'ed buffer.
 * @length: Buffer size.
 *
 * Context: Any context.
 * Return: Number of physically contiguous parts in the @data.
 */
अटल पूर्णांक virtsnd_pcm_sg_num(u8 *data, अचिन्हित पूर्णांक length)
अणु
	phys_addr_t sg_address;
	अचिन्हित पूर्णांक sg_length;
	पूर्णांक num = 0;

	जबतक (length) अणु
		काष्ठा page *pg = vदो_स्मृति_to_page(data);
		phys_addr_t pg_address = page_to_phys(pg);
		माप_प्रकार pg_length;

		pg_length = PAGE_SIZE - offset_in_page(data);
		अगर (pg_length > length)
			pg_length = length;

		अगर (!num || sg_address + sg_length != pg_address) अणु
			sg_address = pg_address;
			sg_length = pg_length;
			num++;
		पूर्ण अन्यथा अणु
			sg_length += pg_length;
		पूर्ण

		data += pg_length;
		length -= pg_length;
	पूर्ण

	वापस num;
पूर्ण

/**
 * virtsnd_pcm_sg_from() - Build sg-list from vदो_स्मृति'ed buffer.
 * @sgs: Pपुनः_स्मृतिated sg-list to populate.
 * @nsgs: The maximum number of elements in the @sgs.
 * @data: Poपूर्णांकer to vदो_स्मृति'ed buffer.
 * @length: Buffer size.
 *
 * Splits the buffer पूर्णांकo physically contiguous parts and makes an sg-list of
 * such parts.
 *
 * Context: Any context.
 */
अटल व्योम virtsnd_pcm_sg_from(काष्ठा scatterlist *sgs, पूर्णांक nsgs, u8 *data,
				अचिन्हित पूर्णांक length)
अणु
	पूर्णांक idx = -1;

	जबतक (length) अणु
		काष्ठा page *pg = vदो_स्मृति_to_page(data);
		माप_प्रकार pg_length;

		pg_length = PAGE_SIZE - offset_in_page(data);
		अगर (pg_length > length)
			pg_length = length;

		अगर (idx == -1 ||
		    sg_phys(&sgs[idx]) + sgs[idx].length != page_to_phys(pg)) अणु
			अगर (idx + 1 == nsgs)
				अवरोध;
			sg_set_page(&sgs[++idx], pg, pg_length,
				    offset_in_page(data));
		पूर्ण अन्यथा अणु
			sgs[idx].length += pg_length;
		पूर्ण

		data += pg_length;
		length -= pg_length;
	पूर्ण

	sg_mark_end(&sgs[idx]);
पूर्ण

/**
 * virtsnd_pcm_msg_alloc() - Allocate I/O messages.
 * @vss: VirtIO PCM substream.
 * @periods: Current number of periods.
 * @period_bytes: Current period size in bytes.
 *
 * The function slices the buffer पूर्णांकo @periods parts (each with the size of
 * @period_bytes), and creates @periods corresponding I/O messages.
 *
 * Context: Any context that permits to sleep.
 * Return: 0 on success, -ENOMEM on failure.
 */
पूर्णांक virtsnd_pcm_msg_alloc(काष्ठा virtio_pcm_substream *vss,
			  अचिन्हित पूर्णांक periods, अचिन्हित पूर्णांक period_bytes)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = vss->substream->runसमय;
	अचिन्हित पूर्णांक i;

	vss->msgs = kसुस्मृति(periods, माप(*vss->msgs), GFP_KERNEL);
	अगर (!vss->msgs)
		वापस -ENOMEM;

	vss->nmsgs = periods;

	क्रम (i = 0; i < periods; ++i) अणु
		u8 *data = runसमय->dma_area + period_bytes * i;
		पूर्णांक sg_num = virtsnd_pcm_sg_num(data, period_bytes);
		काष्ठा virtio_pcm_msg *msg;

		msg = kzalloc(माप(*msg) + माप(*msg->sgs) * (sg_num + 2),
			      GFP_KERNEL);
		अगर (!msg)
			वापस -ENOMEM;

		msg->substream = vss;
		sg_init_one(&msg->sgs[PCM_MSG_SG_XFER], &msg->xfer,
			    माप(msg->xfer));
		sg_init_one(&msg->sgs[PCM_MSG_SG_STATUS], &msg->status,
			    माप(msg->status));
		msg->length = period_bytes;
		virtsnd_pcm_sg_from(&msg->sgs[PCM_MSG_SG_DATA], sg_num, data,
				    period_bytes);

		vss->msgs[i] = msg;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * virtsnd_pcm_msg_मुक्त() - Free all allocated I/O messages.
 * @vss: VirtIO PCM substream.
 *
 * Context: Any context.
 */
व्योम virtsnd_pcm_msg_मुक्त(काष्ठा virtio_pcm_substream *vss)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; vss->msgs && i < vss->nmsgs; ++i)
		kमुक्त(vss->msgs[i]);
	kमुक्त(vss->msgs);

	vss->msgs = शून्य;
	vss->nmsgs = 0;
पूर्ण

/**
 * virtsnd_pcm_msg_send() - Send asynchronous I/O messages.
 * @vss: VirtIO PCM substream.
 *
 * All messages are organized in an ordered circular list. Each समय the
 * function is called, all currently non-enqueued messages are added to the
 * virtqueue. For this, the function keeps track of two values:
 *
 *   msg_last_enqueued = index of the last enqueued message,
 *   msg_count = # of pending messages in the virtqueue.
 *
 * Context: Any context. Expects the tx/rx queue and the VirtIO substream
 *          spinlocks to be held by caller.
 * Return: 0 on success, -त्रुटि_सं on failure.
 */
पूर्णांक virtsnd_pcm_msg_send(काष्ठा virtio_pcm_substream *vss)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = vss->substream->runसमय;
	काष्ठा virtio_snd *snd = vss->snd;
	काष्ठा virtio_device *vdev = snd->vdev;
	काष्ठा virtqueue *vqueue = virtsnd_pcm_queue(vss)->vqueue;
	पूर्णांक i;
	पूर्णांक n;
	bool notअगरy = false;

	i = (vss->msg_last_enqueued + 1) % runसमय->periods;
	n = runसमय->periods - vss->msg_count;

	क्रम (; n; --n, i = (i + 1) % runसमय->periods) अणु
		काष्ठा virtio_pcm_msg *msg = vss->msgs[i];
		काष्ठा scatterlist *psgs[] = अणु
			&msg->sgs[PCM_MSG_SG_XFER],
			&msg->sgs[PCM_MSG_SG_DATA],
			&msg->sgs[PCM_MSG_SG_STATUS]
		पूर्ण;
		पूर्णांक rc;

		msg->xfer.stream_id = cpu_to_le32(vss->sid);
		स_रखो(&msg->status, 0, माप(msg->status));

		अगर (vss->direction == SNDRV_PCM_STREAM_PLAYBACK)
			rc = virtqueue_add_sgs(vqueue, psgs, 2, 1, msg,
					       GFP_ATOMIC);
		अन्यथा
			rc = virtqueue_add_sgs(vqueue, psgs, 1, 2, msg,
					       GFP_ATOMIC);

		अगर (rc) अणु
			dev_err(&vdev->dev,
				"SID %u: failed to send I/O message\n",
				vss->sid);
			वापस rc;
		पूर्ण

		vss->msg_last_enqueued = i;
		vss->msg_count++;
	पूर्ण

	अगर (!(vss->features & (1U << VIRTIO_SND_PCM_F_MSG_POLLING)))
		notअगरy = virtqueue_kick_prepare(vqueue);

	अगर (notअगरy)
		virtqueue_notअगरy(vqueue);

	वापस 0;
पूर्ण

/**
 * virtsnd_pcm_msg_pending_num() - Returns the number of pending I/O messages.
 * @vss: VirtIO substream.
 *
 * Context: Any context.
 * Return: Number of messages.
 */
अचिन्हित पूर्णांक virtsnd_pcm_msg_pending_num(काष्ठा virtio_pcm_substream *vss)
अणु
	अचिन्हित पूर्णांक num;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&vss->lock, flags);
	num = vss->msg_count;
	spin_unlock_irqrestore(&vss->lock, flags);

	वापस num;
पूर्ण

/**
 * virtsnd_pcm_msg_complete() - Complete an I/O message.
 * @msg: I/O message.
 * @written_bytes: Number of bytes written to the message.
 *
 * Completion of the message means the elapsed period. If transmission is
 * allowed, then each completed message is immediately placed back at the end
 * of the queue.
 *
 * For the playback substream, @written_bytes is equal to माप(msg->status).
 *
 * For the capture substream, @written_bytes is equal to माप(msg->status)
 * plus the number of captured bytes.
 *
 * Context: Interrupt context. Takes and releases the VirtIO substream spinlock.
 */
अटल व्योम virtsnd_pcm_msg_complete(काष्ठा virtio_pcm_msg *msg,
				     माप_प्रकार written_bytes)
अणु
	काष्ठा virtio_pcm_substream *vss = msg->substream;

	/*
	 * hw_ptr always indicates the buffer position of the first I/O message
	 * in the virtqueue. Thereक्रमe, on each completion of an I/O message,
	 * the hw_ptr value is unconditionally advanced.
	 */
	spin_lock(&vss->lock);
	/*
	 * If the capture substream वापसed an incorrect status, then just
	 * increase the hw_ptr by the message size.
	 */
	अगर (vss->direction == SNDRV_PCM_STREAM_PLAYBACK ||
	    written_bytes <= माप(msg->status))
		vss->hw_ptr += msg->length;
	अन्यथा
		vss->hw_ptr += written_bytes - माप(msg->status);

	अगर (vss->hw_ptr >= vss->buffer_bytes)
		vss->hw_ptr -= vss->buffer_bytes;

	vss->xfer_xrun = false;
	vss->msg_count--;

	अगर (vss->xfer_enabled) अणु
		काष्ठा snd_pcm_runसमय *runसमय = vss->substream->runसमय;

		runसमय->delay =
			bytes_to_frames(runसमय,
					le32_to_cpu(msg->status.latency_bytes));

		schedule_work(&vss->elapsed_period);

		virtsnd_pcm_msg_send(vss);
	पूर्ण अन्यथा अगर (!vss->msg_count) अणु
		wake_up_all(&vss->msg_empty);
	पूर्ण
	spin_unlock(&vss->lock);
पूर्ण

/**
 * virtsnd_pcm_notअगरy_cb() - Process all completed I/O messages.
 * @queue: Underlying tx/rx virtqueue.
 *
 * Context: Interrupt context. Takes and releases the tx/rx queue spinlock.
 */
अटल अंतरभूत व्योम virtsnd_pcm_notअगरy_cb(काष्ठा virtio_snd_queue *queue)
अणु
	काष्ठा virtio_pcm_msg *msg;
	u32 written_bytes;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&queue->lock, flags);
	करो अणु
		virtqueue_disable_cb(queue->vqueue);
		जबतक ((msg = virtqueue_get_buf(queue->vqueue, &written_bytes)))
			virtsnd_pcm_msg_complete(msg, written_bytes);
		अगर (unlikely(virtqueue_is_broken(queue->vqueue)))
			अवरोध;
	पूर्ण जबतक (!virtqueue_enable_cb(queue->vqueue));
	spin_unlock_irqrestore(&queue->lock, flags);
पूर्ण

/**
 * virtsnd_pcm_tx_notअगरy_cb() - Process all completed TX messages.
 * @vqueue: Underlying tx virtqueue.
 *
 * Context: Interrupt context.
 */
व्योम virtsnd_pcm_tx_notअगरy_cb(काष्ठा virtqueue *vqueue)
अणु
	काष्ठा virtio_snd *snd = vqueue->vdev->priv;

	virtsnd_pcm_notअगरy_cb(virtsnd_tx_queue(snd));
पूर्ण

/**
 * virtsnd_pcm_rx_notअगरy_cb() - Process all completed RX messages.
 * @vqueue: Underlying rx virtqueue.
 *
 * Context: Interrupt context.
 */
व्योम virtsnd_pcm_rx_notअगरy_cb(काष्ठा virtqueue *vqueue)
अणु
	काष्ठा virtio_snd *snd = vqueue->vdev->priv;

	virtsnd_pcm_notअगरy_cb(virtsnd_rx_queue(snd));
पूर्ण

/**
 * virtsnd_pcm_ctl_msg_alloc() - Allocate and initialize the PCM device control
 *                               message क्रम the specअगरied substream.
 * @vss: VirtIO PCM substream.
 * @command: Control request code (VIRTIO_SND_R_PCM_XXX).
 * @gfp: Kernel flags क्रम memory allocation.
 *
 * Context: Any context. May sleep अगर @gfp flags permit.
 * Return: Allocated message on success, शून्य on failure.
 */
काष्ठा virtio_snd_msg *
virtsnd_pcm_ctl_msg_alloc(काष्ठा virtio_pcm_substream *vss,
			  अचिन्हित पूर्णांक command, gfp_t gfp)
अणु
	माप_प्रकार request_size = माप(काष्ठा virtio_snd_pcm_hdr);
	माप_प्रकार response_size = माप(काष्ठा virtio_snd_hdr);
	काष्ठा virtio_snd_msg *msg;

	चयन (command) अणु
	हाल VIRTIO_SND_R_PCM_SET_PARAMS:
		request_size = माप(काष्ठा virtio_snd_pcm_set_params);
		अवरोध;
	पूर्ण

	msg = virtsnd_ctl_msg_alloc(request_size, response_size, gfp);
	अगर (msg) अणु
		काष्ठा virtio_snd_pcm_hdr *hdr = virtsnd_ctl_msg_request(msg);

		hdr->hdr.code = cpu_to_le32(command);
		hdr->stream_id = cpu_to_le32(vss->sid);
	पूर्ण

	वापस msg;
पूर्ण
