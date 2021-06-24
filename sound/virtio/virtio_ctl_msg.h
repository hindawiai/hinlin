<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * virtio-snd: Virtio sound device
 * Copyright (C) 2021 OpenSynergy GmbH
 */
#अगर_अघोषित VIRTIO_SND_MSG_H
#घोषणा VIRTIO_SND_MSG_H

#समावेश <linux/atomic.h>
#समावेश <linux/virtपन.स>

काष्ठा virtio_snd;
काष्ठा virtio_snd_msg;

व्योम virtsnd_ctl_msg_ref(काष्ठा virtio_snd_msg *msg);

व्योम virtsnd_ctl_msg_unref(काष्ठा virtio_snd_msg *msg);

व्योम *virtsnd_ctl_msg_request(काष्ठा virtio_snd_msg *msg);

व्योम *virtsnd_ctl_msg_response(काष्ठा virtio_snd_msg *msg);

काष्ठा virtio_snd_msg *virtsnd_ctl_msg_alloc(माप_प्रकार request_size,
					     माप_प्रकार response_size, gfp_t gfp);

पूर्णांक virtsnd_ctl_msg_send(काष्ठा virtio_snd *snd, काष्ठा virtio_snd_msg *msg,
			 काष्ठा scatterlist *out_sgs,
			 काष्ठा scatterlist *in_sgs, bool noरुको);

/**
 * virtsnd_ctl_msg_send_sync() - Simplअगरied sending of synchronous message.
 * @snd: VirtIO sound device.
 * @msg: Control message.
 *
 * After वापसing from this function, the message will be deleted. If message
 * content is still needed, the caller must additionally to
 * virtsnd_ctl_msg_ref/unref() it.
 *
 * The msg_समयout_ms module parameter defines the message completion समयout.
 * If the message is not completed within this समय, the function will वापस an
 * error.
 *
 * Context: Any context that permits to sleep.
 * Return: 0 on success, -त्रुटि_सं on failure.
 *
 * The वापस value is a message status code (VIRTIO_SND_S_XXX) converted to an
 * appropriate -त्रुटि_सं value.
 */
अटल अंतरभूत पूर्णांक virtsnd_ctl_msg_send_sync(काष्ठा virtio_snd *snd,
					    काष्ठा virtio_snd_msg *msg)
अणु
	वापस virtsnd_ctl_msg_send(snd, msg, शून्य, शून्य, false);
पूर्ण

/**
 * virtsnd_ctl_msg_send_async() - Simplअगरied sending of asynchronous message.
 * @snd: VirtIO sound device.
 * @msg: Control message.
 *
 * Context: Any context.
 * Return: 0 on success, -त्रुटि_सं on failure.
 */
अटल अंतरभूत पूर्णांक virtsnd_ctl_msg_send_async(काष्ठा virtio_snd *snd,
					     काष्ठा virtio_snd_msg *msg)
अणु
	वापस virtsnd_ctl_msg_send(snd, msg, शून्य, शून्य, true);
पूर्ण

व्योम virtsnd_ctl_msg_cancel_all(काष्ठा virtio_snd *snd);

व्योम virtsnd_ctl_msg_complete(काष्ठा virtio_snd_msg *msg);

पूर्णांक virtsnd_ctl_query_info(काष्ठा virtio_snd *snd, पूर्णांक command, पूर्णांक start_id,
			   पूर्णांक count, माप_प्रकार size, व्योम *info);

व्योम virtsnd_ctl_notअगरy_cb(काष्ठा virtqueue *vqueue);

#पूर्ण_अगर /* VIRTIO_SND_MSG_H */
