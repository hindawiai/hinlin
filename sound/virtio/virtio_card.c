<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * virtio-snd: Virtio sound device
 * Copyright (C) 2021 OpenSynergy GmbH
 */
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/virtio_config.h>
#समावेश <sound/initval.h>
#समावेश <uapi/linux/virtio_ids.h>

#समावेश "virtio_card.h"

u32 virtsnd_msg_समयout_ms = MSEC_PER_SEC;
module_param_named(msg_समयout_ms, virtsnd_msg_समयout_ms, uपूर्णांक, 0644);
MODULE_PARM_DESC(msg_समयout_ms, "Message completion timeout in milliseconds");

अटल व्योम virtsnd_हटाओ(काष्ठा virtio_device *vdev);

/**
 * virtsnd_event_send() - Add an event to the event queue.
 * @vqueue: Underlying event virtqueue.
 * @event: Event.
 * @notअगरy: Indicates whether or not to send a notअगरication to the device.
 * @gfp: Kernel flags क्रम memory allocation.
 *
 * Context: Any context.
 */
अटल व्योम virtsnd_event_send(काष्ठा virtqueue *vqueue,
			       काष्ठा virtio_snd_event *event, bool notअगरy,
			       gfp_t gfp)
अणु
	काष्ठा scatterlist sg;
	काष्ठा scatterlist *psgs[1] = अणु &sg पूर्ण;

	/* reset event content */
	स_रखो(event, 0, माप(*event));

	sg_init_one(&sg, event, माप(*event));

	अगर (virtqueue_add_sgs(vqueue, psgs, 0, 1, event, gfp) || !notअगरy)
		वापस;

	अगर (virtqueue_kick_prepare(vqueue))
		virtqueue_notअगरy(vqueue);
पूर्ण

/**
 * virtsnd_event_dispatch() - Dispatch an event from the device side.
 * @snd: VirtIO sound device.
 * @event: VirtIO sound event.
 *
 * Context: Any context.
 */
अटल व्योम virtsnd_event_dispatch(काष्ठा virtio_snd *snd,
				   काष्ठा virtio_snd_event *event)
अणु
	चयन (le32_to_cpu(event->hdr.code)) अणु
	हाल VIRTIO_SND_EVT_JACK_CONNECTED:
	हाल VIRTIO_SND_EVT_JACK_DISCONNECTED:
		virtsnd_jack_event(snd, event);
		अवरोध;
	हाल VIRTIO_SND_EVT_PCM_PERIOD_ELAPSED:
	हाल VIRTIO_SND_EVT_PCM_XRUN:
		virtsnd_pcm_event(snd, event);
		अवरोध;
	पूर्ण
पूर्ण

/**
 * virtsnd_event_notअगरy_cb() - Dispatch all reported events from the event queue.
 * @vqueue: Underlying event virtqueue.
 *
 * This callback function is called upon a vring पूर्णांकerrupt request from the
 * device.
 *
 * Context: Interrupt context.
 */
अटल व्योम virtsnd_event_notअगरy_cb(काष्ठा virtqueue *vqueue)
अणु
	काष्ठा virtio_snd *snd = vqueue->vdev->priv;
	काष्ठा virtio_snd_queue *queue = virtsnd_event_queue(snd);
	काष्ठा virtio_snd_event *event;
	u32 length;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&queue->lock, flags);
	करो अणु
		virtqueue_disable_cb(vqueue);
		जबतक ((event = virtqueue_get_buf(vqueue, &length))) अणु
			virtsnd_event_dispatch(snd, event);
			virtsnd_event_send(vqueue, event, true, GFP_ATOMIC);
		पूर्ण
		अगर (unlikely(virtqueue_is_broken(vqueue)))
			अवरोध;
	पूर्ण जबतक (!virtqueue_enable_cb(vqueue));
	spin_unlock_irqrestore(&queue->lock, flags);
पूर्ण

/**
 * virtsnd_find_vqs() - Enumerate and initialize all virtqueues.
 * @snd: VirtIO sound device.
 *
 * After calling this function, the event queue is disabled.
 *
 * Context: Any context.
 * Return: 0 on success, -त्रुटि_सं on failure.
 */
अटल पूर्णांक virtsnd_find_vqs(काष्ठा virtio_snd *snd)
अणु
	काष्ठा virtio_device *vdev = snd->vdev;
	अटल vq_callback_t *callbacks[VIRTIO_SND_VQ_MAX] = अणु
		[VIRTIO_SND_VQ_CONTROL] = virtsnd_ctl_notअगरy_cb,
		[VIRTIO_SND_VQ_EVENT] = virtsnd_event_notअगरy_cb,
		[VIRTIO_SND_VQ_TX] = virtsnd_pcm_tx_notअगरy_cb,
		[VIRTIO_SND_VQ_RX] = virtsnd_pcm_rx_notअगरy_cb
	पूर्ण;
	अटल स्थिर अक्षर *names[VIRTIO_SND_VQ_MAX] = अणु
		[VIRTIO_SND_VQ_CONTROL] = "virtsnd-ctl",
		[VIRTIO_SND_VQ_EVENT] = "virtsnd-event",
		[VIRTIO_SND_VQ_TX] = "virtsnd-tx",
		[VIRTIO_SND_VQ_RX] = "virtsnd-rx"
	पूर्ण;
	काष्ठा virtqueue *vqs[VIRTIO_SND_VQ_MAX] = अणु 0 पूर्ण;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक n;
	पूर्णांक rc;

	rc = virtio_find_vqs(vdev, VIRTIO_SND_VQ_MAX, vqs, callbacks, names,
			     शून्य);
	अगर (rc) अणु
		dev_err(&vdev->dev, "failed to initialize virtqueues\n");
		वापस rc;
	पूर्ण

	क्रम (i = 0; i < VIRTIO_SND_VQ_MAX; ++i)
		snd->queues[i].vqueue = vqs[i];

	/* Allocate events and populate the event queue */
	virtqueue_disable_cb(vqs[VIRTIO_SND_VQ_EVENT]);

	n = virtqueue_get_vring_size(vqs[VIRTIO_SND_VQ_EVENT]);

	snd->event_msgs = kदो_स्मृति_array(n, माप(*snd->event_msgs),
					GFP_KERNEL);
	अगर (!snd->event_msgs)
		वापस -ENOMEM;

	क्रम (i = 0; i < n; ++i)
		virtsnd_event_send(vqs[VIRTIO_SND_VQ_EVENT],
				   &snd->event_msgs[i], false, GFP_KERNEL);

	वापस 0;
पूर्ण

/**
 * virtsnd_enable_event_vq() - Enable the event virtqueue.
 * @snd: VirtIO sound device.
 *
 * Context: Any context.
 */
अटल व्योम virtsnd_enable_event_vq(काष्ठा virtio_snd *snd)
अणु
	काष्ठा virtio_snd_queue *queue = virtsnd_event_queue(snd);

	अगर (!virtqueue_enable_cb(queue->vqueue))
		virtsnd_event_notअगरy_cb(queue->vqueue);
पूर्ण

/**
 * virtsnd_disable_event_vq() - Disable the event virtqueue.
 * @snd: VirtIO sound device.
 *
 * Context: Any context.
 */
अटल व्योम virtsnd_disable_event_vq(काष्ठा virtio_snd *snd)
अणु
	काष्ठा virtio_snd_queue *queue = virtsnd_event_queue(snd);
	काष्ठा virtio_snd_event *event;
	u32 length;
	अचिन्हित दीर्घ flags;

	अगर (queue->vqueue) अणु
		spin_lock_irqsave(&queue->lock, flags);
		virtqueue_disable_cb(queue->vqueue);
		जबतक ((event = virtqueue_get_buf(queue->vqueue, &length)))
			virtsnd_event_dispatch(snd, event);
		spin_unlock_irqrestore(&queue->lock, flags);
	पूर्ण
पूर्ण

/**
 * virtsnd_build_devs() - Read configuration and build ALSA devices.
 * @snd: VirtIO sound device.
 *
 * Context: Any context that permits to sleep.
 * Return: 0 on success, -त्रुटि_सं on failure.
 */
अटल पूर्णांक virtsnd_build_devs(काष्ठा virtio_snd *snd)
अणु
	काष्ठा virtio_device *vdev = snd->vdev;
	काष्ठा device *dev = &vdev->dev;
	पूर्णांक rc;

	rc = snd_card_new(dev, SNDRV_DEFAULT_IDX1, SNDRV_DEFAULT_STR1,
			  THIS_MODULE, 0, &snd->card);
	अगर (rc < 0)
		वापस rc;

	snd->card->निजी_data = snd;

	strscpy(snd->card->driver, VIRTIO_SND_CARD_DRIVER,
		माप(snd->card->driver));
	strscpy(snd->card->लघुname, VIRTIO_SND_CARD_NAME,
		माप(snd->card->लघुname));
	अगर (dev->parent->bus)
		snम_लिखो(snd->card->दीर्घname, माप(snd->card->दीर्घname),
			 VIRTIO_SND_CARD_NAME " at %s/%s/%s",
			 dev->parent->bus->name, dev_name(dev->parent),
			 dev_name(dev));
	अन्यथा
		snम_लिखो(snd->card->दीर्घname, माप(snd->card->दीर्घname),
			 VIRTIO_SND_CARD_NAME " at %s/%s",
			 dev_name(dev->parent), dev_name(dev));

	rc = virtsnd_jack_parse_cfg(snd);
	अगर (rc)
		वापस rc;

	rc = virtsnd_pcm_parse_cfg(snd);
	अगर (rc)
		वापस rc;

	rc = virtsnd_chmap_parse_cfg(snd);
	अगर (rc)
		वापस rc;

	अगर (snd->njacks) अणु
		rc = virtsnd_jack_build_devs(snd);
		अगर (rc)
			वापस rc;
	पूर्ण

	अगर (snd->nsubstreams) अणु
		rc = virtsnd_pcm_build_devs(snd);
		अगर (rc)
			वापस rc;
	पूर्ण

	अगर (snd->nchmaps) अणु
		rc = virtsnd_chmap_build_devs(snd);
		अगर (rc)
			वापस rc;
	पूर्ण

	वापस snd_card_रेजिस्टर(snd->card);
पूर्ण

/**
 * virtsnd_validate() - Validate अगर the device can be started.
 * @vdev: VirtIO parent device.
 *
 * Context: Any context.
 * Return: 0 on success, -EINVAL on failure.
 */
अटल पूर्णांक virtsnd_validate(काष्ठा virtio_device *vdev)
अणु
	अगर (!vdev->config->get) अणु
		dev_err(&vdev->dev, "configuration access disabled\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!virtio_has_feature(vdev, VIRTIO_F_VERSION_1)) अणु
		dev_err(&vdev->dev,
			"device does not comply with spec version 1.x\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!virtsnd_msg_समयout_ms) अणु
		dev_err(&vdev->dev, "msg_timeout_ms value cannot be zero\n");
		वापस -EINVAL;
	पूर्ण

	अगर (virtsnd_pcm_validate(vdev))
		वापस -EINVAL;

	वापस 0;
पूर्ण

/**
 * virtsnd_probe() - Create and initialize the device.
 * @vdev: VirtIO parent device.
 *
 * Context: Any context that permits to sleep.
 * Return: 0 on success, -त्रुटि_सं on failure.
 */
अटल पूर्णांक virtsnd_probe(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtio_snd *snd;
	अचिन्हित पूर्णांक i;
	पूर्णांक rc;

	snd = devm_kzalloc(&vdev->dev, माप(*snd), GFP_KERNEL);
	अगर (!snd)
		वापस -ENOMEM;

	snd->vdev = vdev;
	INIT_LIST_HEAD(&snd->ctl_msgs);
	INIT_LIST_HEAD(&snd->pcm_list);

	vdev->priv = snd;

	क्रम (i = 0; i < VIRTIO_SND_VQ_MAX; ++i)
		spin_lock_init(&snd->queues[i].lock);

	rc = virtsnd_find_vqs(snd);
	अगर (rc)
		जाओ on_निकास;

	virtio_device_पढ़ोy(vdev);

	rc = virtsnd_build_devs(snd);
	अगर (rc)
		जाओ on_निकास;

	virtsnd_enable_event_vq(snd);

on_निकास:
	अगर (rc)
		virtsnd_हटाओ(vdev);

	वापस rc;
पूर्ण

/**
 * virtsnd_हटाओ() - Remove VirtIO and ALSA devices.
 * @vdev: VirtIO parent device.
 *
 * Context: Any context that permits to sleep.
 */
अटल व्योम virtsnd_हटाओ(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtio_snd *snd = vdev->priv;
	अचिन्हित पूर्णांक i;

	virtsnd_disable_event_vq(snd);
	virtsnd_ctl_msg_cancel_all(snd);

	अगर (snd->card)
		snd_card_मुक्त(snd->card);

	vdev->config->del_vqs(vdev);
	vdev->config->reset(vdev);

	क्रम (i = 0; snd->substreams && i < snd->nsubstreams; ++i) अणु
		काष्ठा virtio_pcm_substream *vss = &snd->substreams[i];

		cancel_work_sync(&vss->elapsed_period);
		virtsnd_pcm_msg_मुक्त(vss);
	पूर्ण

	kमुक्त(snd->event_msgs);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
/**
 * virtsnd_मुक्तze() - Suspend device.
 * @vdev: VirtIO parent device.
 *
 * Context: Any context.
 * Return: 0 on success, -त्रुटि_सं on failure.
 */
अटल पूर्णांक virtsnd_मुक्तze(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtio_snd *snd = vdev->priv;
	अचिन्हित पूर्णांक i;

	virtsnd_disable_event_vq(snd);
	virtsnd_ctl_msg_cancel_all(snd);

	vdev->config->del_vqs(vdev);
	vdev->config->reset(vdev);

	क्रम (i = 0; i < snd->nsubstreams; ++i)
		cancel_work_sync(&snd->substreams[i].elapsed_period);

	kमुक्त(snd->event_msgs);
	snd->event_msgs = शून्य;

	वापस 0;
पूर्ण

/**
 * virtsnd_restore() - Resume device.
 * @vdev: VirtIO parent device.
 *
 * Context: Any context.
 * Return: 0 on success, -त्रुटि_सं on failure.
 */
अटल पूर्णांक virtsnd_restore(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtio_snd *snd = vdev->priv;
	पूर्णांक rc;

	rc = virtsnd_find_vqs(snd);
	अगर (rc)
		वापस rc;

	virtio_device_पढ़ोy(vdev);

	virtsnd_enable_event_vq(snd);

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल स्थिर काष्ठा virtio_device_id id_table[] = अणु
	अणु VIRTIO_ID_SOUND, VIRTIO_DEV_ANY_ID पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल काष्ठा virtio_driver virtsnd_driver = अणु
	.driver.name = KBUILD_MODNAME,
	.driver.owner = THIS_MODULE,
	.id_table = id_table,
	.validate = virtsnd_validate,
	.probe = virtsnd_probe,
	.हटाओ = virtsnd_हटाओ,
#अगर_घोषित CONFIG_PM_SLEEP
	.मुक्तze = virtsnd_मुक्तze,
	.restore = virtsnd_restore,
#पूर्ण_अगर
पूर्ण;

module_virtio_driver(virtsnd_driver);

MODULE_DEVICE_TABLE(virtio, id_table);
MODULE_DESCRIPTION("Virtio sound card driver");
MODULE_LICENSE("GPL");
