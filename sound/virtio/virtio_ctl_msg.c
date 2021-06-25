<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * virtio-snd: Virtio sound device
 * Copyright (C) 2021 OpenSynergy GmbH
 */
#समावेश <linux/moduleparam.h>
#समावेश <linux/virtio_config.h>

#समावेश "virtio_card.h"

/**
 * काष्ठा virtio_snd_msg - Control message.
 * @sg_request: Scattergather list containing a device request (header).
 * @sg_response: Scattergather list containing a device response (status).
 * @list: Pending message list entry.
 * @notअगरy: Request completed notअगरication.
 * @ref_count: Reference count used to manage a message lअगरeसमय.
 */
काष्ठा virtio_snd_msg अणु
	काष्ठा scatterlist sg_request;
	काष्ठा scatterlist sg_response;
	काष्ठा list_head list;
	काष्ठा completion notअगरy;
	refcount_t ref_count;
पूर्ण;

/**
 * virtsnd_ctl_msg_ref() - Increment reference counter क्रम the message.
 * @msg: Control message.
 *
 * Context: Any context.
 */
व्योम virtsnd_ctl_msg_ref(काष्ठा virtio_snd_msg *msg)
अणु
	refcount_inc(&msg->ref_count);
पूर्ण

/**
 * virtsnd_ctl_msg_unref() - Decrement reference counter क्रम the message.
 * @msg: Control message.
 *
 * The message will be मुक्तd when the ref_count value is 0.
 *
 * Context: Any context.
 */
व्योम virtsnd_ctl_msg_unref(काष्ठा virtio_snd_msg *msg)
अणु
	अगर (refcount_dec_and_test(&msg->ref_count))
		kमुक्त(msg);
पूर्ण

/**
 * virtsnd_ctl_msg_request() - Get a poपूर्णांकer to the request header.
 * @msg: Control message.
 *
 * Context: Any context.
 */
व्योम *virtsnd_ctl_msg_request(काष्ठा virtio_snd_msg *msg)
अणु
	वापस sg_virt(&msg->sg_request);
पूर्ण

/**
 * virtsnd_ctl_msg_response() - Get a poपूर्णांकer to the response header.
 * @msg: Control message.
 *
 * Context: Any context.
 */
व्योम *virtsnd_ctl_msg_response(काष्ठा virtio_snd_msg *msg)
अणु
	वापस sg_virt(&msg->sg_response);
पूर्ण

/**
 * virtsnd_ctl_msg_alloc() - Allocate and initialize a control message.
 * @request_size: Size of request header.
 * @response_size: Size of response header.
 * @gfp: Kernel flags क्रम memory allocation.
 *
 * The message will be स्वतःmatically मुक्तd when the ref_count value is 0.
 *
 * Context: Any context. May sleep अगर @gfp flags permit.
 * Return: Allocated message on success, शून्य on failure.
 */
काष्ठा virtio_snd_msg *virtsnd_ctl_msg_alloc(माप_प्रकार request_size,
					     माप_प्रकार response_size, gfp_t gfp)
अणु
	काष्ठा virtio_snd_msg *msg;

	अगर (!request_size || !response_size)
		वापस शून्य;

	msg = kzalloc(माप(*msg) + request_size + response_size, gfp);
	अगर (!msg)
		वापस शून्य;

	sg_init_one(&msg->sg_request, (u8 *)msg + माप(*msg), request_size);
	sg_init_one(&msg->sg_response, (u8 *)msg + माप(*msg) + request_size,
		    response_size);

	INIT_LIST_HEAD(&msg->list);
	init_completion(&msg->notअगरy);
	/* This reference is dropped in virtsnd_ctl_msg_complete(). */
	refcount_set(&msg->ref_count, 1);

	वापस msg;
पूर्ण

/**
 * virtsnd_ctl_msg_send() - Send a control message.
 * @snd: VirtIO sound device.
 * @msg: Control message.
 * @out_sgs: Additional sg-list to attach to the request header (may be शून्य).
 * @in_sgs: Additional sg-list to attach to the response header (may be शून्य).
 * @noरुको: Flag indicating whether to रुको क्रम completion.
 *
 * Context: Any context. Takes and releases the control queue spinlock.
 *          May sleep अगर @noरुको is false.
 * Return: 0 on success, -त्रुटि_सं on failure.
 */
पूर्णांक virtsnd_ctl_msg_send(काष्ठा virtio_snd *snd, काष्ठा virtio_snd_msg *msg,
			 काष्ठा scatterlist *out_sgs,
			 काष्ठा scatterlist *in_sgs, bool noरुको)
अणु
	काष्ठा virtio_device *vdev = snd->vdev;
	काष्ठा virtio_snd_queue *queue = virtsnd_control_queue(snd);
	अचिन्हित पूर्णांक js = msecs_to_jअगरfies(virtsnd_msg_समयout_ms);
	काष्ठा virtio_snd_hdr *request = virtsnd_ctl_msg_request(msg);
	काष्ठा virtio_snd_hdr *response = virtsnd_ctl_msg_response(msg);
	अचिन्हित पूर्णांक nouts = 0;
	अचिन्हित पूर्णांक nins = 0;
	काष्ठा scatterlist *psgs[4];
	bool notअगरy = false;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	virtsnd_ctl_msg_ref(msg);

	/* Set the शेष status in हाल the message was canceled. */
	response->code = cpu_to_le32(VIRTIO_SND_S_IO_ERR);

	psgs[nouts++] = &msg->sg_request;
	अगर (out_sgs)
		psgs[nouts++] = out_sgs;

	psgs[nouts + nins++] = &msg->sg_response;
	अगर (in_sgs)
		psgs[nouts + nins++] = in_sgs;

	spin_lock_irqsave(&queue->lock, flags);
	rc = virtqueue_add_sgs(queue->vqueue, psgs, nouts, nins, msg,
			       GFP_ATOMIC);
	अगर (!rc) अणु
		notअगरy = virtqueue_kick_prepare(queue->vqueue);

		list_add_tail(&msg->list, &snd->ctl_msgs);
	पूर्ण
	spin_unlock_irqrestore(&queue->lock, flags);

	अगर (rc) अणु
		dev_err(&vdev->dev, "failed to send control message (0x%08x)\n",
			le32_to_cpu(request->code));

		/*
		 * Since in this हाल virtsnd_ctl_msg_complete() will not be
		 * called, it is necessary to decrement the reference count.
		 */
		virtsnd_ctl_msg_unref(msg);

		जाओ on_निकास;
	पूर्ण

	अगर (notअगरy)
		virtqueue_notअगरy(queue->vqueue);

	अगर (noरुको)
		जाओ on_निकास;

	rc = रुको_क्रम_completion_पूर्णांकerruptible_समयout(&msg->notअगरy, js);
	अगर (rc <= 0) अणु
		अगर (!rc) अणु
			dev_err(&vdev->dev,
				"control message (0x%08x) timeout\n",
				le32_to_cpu(request->code));
			rc = -ETIMEDOUT;
		पूर्ण

		जाओ on_निकास;
	पूर्ण

	चयन (le32_to_cpu(response->code)) अणु
	हाल VIRTIO_SND_S_OK:
		rc = 0;
		अवरोध;
	हाल VIRTIO_SND_S_NOT_SUPP:
		rc = -EOPNOTSUPP;
		अवरोध;
	हाल VIRTIO_SND_S_IO_ERR:
		rc = -EIO;
		अवरोध;
	शेष:
		rc = -EINVAL;
		अवरोध;
	पूर्ण

on_निकास:
	virtsnd_ctl_msg_unref(msg);

	वापस rc;
पूर्ण

/**
 * virtsnd_ctl_msg_complete() - Complete a control message.
 * @msg: Control message.
 *
 * Context: Any context. Expects the control queue spinlock to be held by
 *          caller.
 */
व्योम virtsnd_ctl_msg_complete(काष्ठा virtio_snd_msg *msg)
अणु
	list_del(&msg->list);
	complete(&msg->notअगरy);

	virtsnd_ctl_msg_unref(msg);
पूर्ण

/**
 * virtsnd_ctl_msg_cancel_all() - Cancel all pending control messages.
 * @snd: VirtIO sound device.
 *
 * Context: Any context.
 */
व्योम virtsnd_ctl_msg_cancel_all(काष्ठा virtio_snd *snd)
अणु
	काष्ठा virtio_snd_queue *queue = virtsnd_control_queue(snd);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&queue->lock, flags);
	जबतक (!list_empty(&snd->ctl_msgs)) अणु
		काष्ठा virtio_snd_msg *msg =
			list_first_entry(&snd->ctl_msgs, काष्ठा virtio_snd_msg,
					 list);

		virtsnd_ctl_msg_complete(msg);
	पूर्ण
	spin_unlock_irqrestore(&queue->lock, flags);
पूर्ण

/**
 * virtsnd_ctl_query_info() - Query the item configuration from the device.
 * @snd: VirtIO sound device.
 * @command: Control request code (VIRTIO_SND_R_XXX_INFO).
 * @start_id: Item start identअगरier.
 * @count: Item count to query.
 * @size: Item inक्रमmation size in bytes.
 * @info: Buffer क्रम storing item inक्रमmation.
 *
 * Context: Any context that permits to sleep.
 * Return: 0 on success, -त्रुटि_सं on failure.
 */
पूर्णांक virtsnd_ctl_query_info(काष्ठा virtio_snd *snd, पूर्णांक command, पूर्णांक start_id,
			   पूर्णांक count, माप_प्रकार size, व्योम *info)
अणु
	काष्ठा virtio_snd_msg *msg;
	काष्ठा virtio_snd_query_info *query;
	काष्ठा scatterlist sg;

	msg = virtsnd_ctl_msg_alloc(माप(*query),
				    माप(काष्ठा virtio_snd_hdr), GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	query = virtsnd_ctl_msg_request(msg);
	query->hdr.code = cpu_to_le32(command);
	query->start_id = cpu_to_le32(start_id);
	query->count = cpu_to_le32(count);
	query->size = cpu_to_le32(size);

	sg_init_one(&sg, info, count * size);

	वापस virtsnd_ctl_msg_send(snd, msg, शून्य, &sg, false);
पूर्ण

/**
 * virtsnd_ctl_notअगरy_cb() - Process all completed control messages.
 * @vqueue: Underlying control virtqueue.
 *
 * This callback function is called upon a vring पूर्णांकerrupt request from the
 * device.
 *
 * Context: Interrupt context. Takes and releases the control queue spinlock.
 */
व्योम virtsnd_ctl_notअगरy_cb(काष्ठा virtqueue *vqueue)
अणु
	काष्ठा virtio_snd *snd = vqueue->vdev->priv;
	काष्ठा virtio_snd_queue *queue = virtsnd_control_queue(snd);
	काष्ठा virtio_snd_msg *msg;
	u32 length;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&queue->lock, flags);
	करो अणु
		virtqueue_disable_cb(vqueue);
		जबतक ((msg = virtqueue_get_buf(vqueue, &length)))
			virtsnd_ctl_msg_complete(msg);
		अगर (unlikely(virtqueue_is_broken(vqueue)))
			अवरोध;
	पूर्ण जबतक (!virtqueue_enable_cb(vqueue));
	spin_unlock_irqrestore(&queue->lock, flags);
पूर्ण
