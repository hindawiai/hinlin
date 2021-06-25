<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/module.h>
#समावेश <linux/virtपन.स>
#समावेश <linux/virtio_config.h>
#समावेश <linux/input.h>
#समावेश <linux/slab.h>

#समावेश <uapi/linux/virtio_ids.h>
#समावेश <uapi/linux/virtio_input.h>
#समावेश <linux/input/mt.h>

काष्ठा virtio_input अणु
	काष्ठा virtio_device       *vdev;
	काष्ठा input_dev           *idev;
	अक्षर                       name[64];
	अक्षर                       serial[64];
	अक्षर                       phys[64];
	काष्ठा virtqueue           *evt, *sts;
	काष्ठा virtio_input_event  evts[64];
	spinlock_t                 lock;
	bool                       पढ़ोy;
पूर्ण;

अटल व्योम virtinput_queue_evtbuf(काष्ठा virtio_input *vi,
				   काष्ठा virtio_input_event *evtbuf)
अणु
	काष्ठा scatterlist sg[1];

	sg_init_one(sg, evtbuf, माप(*evtbuf));
	virtqueue_add_inbuf(vi->evt, sg, 1, evtbuf, GFP_ATOMIC);
पूर्ण

अटल व्योम virtinput_recv_events(काष्ठा virtqueue *vq)
अणु
	काष्ठा virtio_input *vi = vq->vdev->priv;
	काष्ठा virtio_input_event *event;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक len;

	spin_lock_irqsave(&vi->lock, flags);
	अगर (vi->पढ़ोy) अणु
		जबतक ((event = virtqueue_get_buf(vi->evt, &len)) != शून्य) अणु
			spin_unlock_irqrestore(&vi->lock, flags);
			input_event(vi->idev,
				    le16_to_cpu(event->type),
				    le16_to_cpu(event->code),
				    le32_to_cpu(event->value));
			spin_lock_irqsave(&vi->lock, flags);
			virtinput_queue_evtbuf(vi, event);
		पूर्ण
		virtqueue_kick(vq);
	पूर्ण
	spin_unlock_irqrestore(&vi->lock, flags);
पूर्ण

/*
 * On error we are losing the status update, which isn't critical as
 * this is typically used क्रम stuff like keyboard leds.
 */
अटल पूर्णांक virtinput_send_status(काष्ठा virtio_input *vi,
				 u16 type, u16 code, s32 value)
अणु
	काष्ठा virtio_input_event *stsbuf;
	काष्ठा scatterlist sg[1];
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	/*
	 * Since 29cc309d8bf1 (HID: hid-multitouch: क्रमward MSC_TIMESTAMP),
	 * EV_MSC/MSC_TIMESTAMP is added to each beक्रमe EV_SYN event.
	 * EV_MSC is configured as INPUT_PASS_TO_ALL.
	 * In हाल of touch device:
	 *   BE pass EV_MSC/MSC_TIMESTAMP to FE on receiving event from evdev.
	 *   FE pass EV_MSC/MSC_TIMESTAMP back to BE.
	 *   BE ग_लिखोs EV_MSC/MSC_TIMESTAMP to evdev due to INPUT_PASS_TO_ALL.
	 *   BE receives extra EV_MSC/MSC_TIMESTAMP and pass to FE.
	 *   >>> Each new frame becomes larger and larger.
	 * Disable EV_MSC/MSC_TIMESTAMP क्रमwarding क्रम MT.
	 */
	अगर (vi->idev->mt && type == EV_MSC && code == MSC_TIMESTAMP)
		वापस 0;

	stsbuf = kzalloc(माप(*stsbuf), GFP_ATOMIC);
	अगर (!stsbuf)
		वापस -ENOMEM;

	stsbuf->type  = cpu_to_le16(type);
	stsbuf->code  = cpu_to_le16(code);
	stsbuf->value = cpu_to_le32(value);
	sg_init_one(sg, stsbuf, माप(*stsbuf));

	spin_lock_irqsave(&vi->lock, flags);
	अगर (vi->पढ़ोy) अणु
		rc = virtqueue_add_outbuf(vi->sts, sg, 1, stsbuf, GFP_ATOMIC);
		virtqueue_kick(vi->sts);
	पूर्ण अन्यथा अणु
		rc = -ENODEV;
	पूर्ण
	spin_unlock_irqrestore(&vi->lock, flags);

	अगर (rc != 0)
		kमुक्त(stsbuf);
	वापस rc;
पूर्ण

अटल व्योम virtinput_recv_status(काष्ठा virtqueue *vq)
अणु
	काष्ठा virtio_input *vi = vq->vdev->priv;
	काष्ठा virtio_input_event *stsbuf;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक len;

	spin_lock_irqsave(&vi->lock, flags);
	जबतक ((stsbuf = virtqueue_get_buf(vi->sts, &len)) != शून्य)
		kमुक्त(stsbuf);
	spin_unlock_irqrestore(&vi->lock, flags);
पूर्ण

अटल पूर्णांक virtinput_status(काष्ठा input_dev *idev, अचिन्हित पूर्णांक type,
			    अचिन्हित पूर्णांक code, पूर्णांक value)
अणु
	काष्ठा virtio_input *vi = input_get_drvdata(idev);

	वापस virtinput_send_status(vi, type, code, value);
पूर्ण

अटल u8 virtinput_cfg_select(काष्ठा virtio_input *vi,
			       u8 select, u8 subsel)
अणु
	u8 size;

	virtio_cग_लिखो_le(vi->vdev, काष्ठा virtio_input_config, select, &select);
	virtio_cग_लिखो_le(vi->vdev, काष्ठा virtio_input_config, subsel, &subsel);
	virtio_cपढ़ो_le(vi->vdev, काष्ठा virtio_input_config, size, &size);
	वापस size;
पूर्ण

अटल व्योम virtinput_cfg_bits(काष्ठा virtio_input *vi, पूर्णांक select, पूर्णांक subsel,
			       अचिन्हित दीर्घ *bits, अचिन्हित पूर्णांक bitcount)
अणु
	अचिन्हित पूर्णांक bit;
	u8 *virtio_bits;
	u8 bytes;

	bytes = virtinput_cfg_select(vi, select, subsel);
	अगर (!bytes)
		वापस;
	अगर (bitcount > bytes * 8)
		bitcount = bytes * 8;

	/*
	 * Biपंचांगap in virtio config space is a simple stream of bytes,
	 * with the first byte carrying bits 0-7, second bits 8-15 and
	 * so on.
	 */
	virtio_bits = kzalloc(bytes, GFP_KERNEL);
	अगर (!virtio_bits)
		वापस;
	virtio_cपढ़ो_bytes(vi->vdev, दुरत्व(काष्ठा virtio_input_config,
					      u.biपंचांगap),
			   virtio_bits, bytes);
	क्रम (bit = 0; bit < bitcount; bit++) अणु
		अगर (virtio_bits[bit / 8] & (1 << (bit % 8)))
			__set_bit(bit, bits);
	पूर्ण
	kमुक्त(virtio_bits);

	अगर (select == VIRTIO_INPUT_CFG_EV_BITS)
		__set_bit(subsel, vi->idev->evbit);
पूर्ण

अटल व्योम virtinput_cfg_असल(काष्ठा virtio_input *vi, पूर्णांक असल)
अणु
	u32 mi, ma, re, fu, fl;

	virtinput_cfg_select(vi, VIRTIO_INPUT_CFG_ABS_INFO, असल);
	virtio_cपढ़ो_le(vi->vdev, काष्ठा virtio_input_config, u.असल.min, &mi);
	virtio_cपढ़ो_le(vi->vdev, काष्ठा virtio_input_config, u.असल.max, &ma);
	virtio_cपढ़ो_le(vi->vdev, काष्ठा virtio_input_config, u.असल.res, &re);
	virtio_cपढ़ो_le(vi->vdev, काष्ठा virtio_input_config, u.असल.fuzz, &fu);
	virtio_cपढ़ो_le(vi->vdev, काष्ठा virtio_input_config, u.असल.flat, &fl);
	input_set_असल_params(vi->idev, असल, mi, ma, fu, fl);
	input_असल_set_res(vi->idev, असल, re);
पूर्ण

अटल पूर्णांक virtinput_init_vqs(काष्ठा virtio_input *vi)
अणु
	काष्ठा virtqueue *vqs[2];
	vq_callback_t *cbs[] = अणु virtinput_recv_events,
				 virtinput_recv_status पूर्ण;
	अटल स्थिर अक्षर * स्थिर names[] = अणु "events", "status" पूर्ण;
	पूर्णांक err;

	err = virtio_find_vqs(vi->vdev, 2, vqs, cbs, names, शून्य);
	अगर (err)
		वापस err;
	vi->evt = vqs[0];
	vi->sts = vqs[1];

	वापस 0;
पूर्ण

अटल व्योम virtinput_fill_evt(काष्ठा virtio_input *vi)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i, size;

	spin_lock_irqsave(&vi->lock, flags);
	size = virtqueue_get_vring_size(vi->evt);
	अगर (size > ARRAY_SIZE(vi->evts))
		size = ARRAY_SIZE(vi->evts);
	क्रम (i = 0; i < size; i++)
		virtinput_queue_evtbuf(vi, &vi->evts[i]);
	virtqueue_kick(vi->evt);
	spin_unlock_irqrestore(&vi->lock, flags);
पूर्ण

अटल पूर्णांक virtinput_probe(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtio_input *vi;
	अचिन्हित दीर्घ flags;
	माप_प्रकार size;
	पूर्णांक असल, err, nslots;

	अगर (!virtio_has_feature(vdev, VIRTIO_F_VERSION_1))
		वापस -ENODEV;

	vi = kzalloc(माप(*vi), GFP_KERNEL);
	अगर (!vi)
		वापस -ENOMEM;

	vdev->priv = vi;
	vi->vdev = vdev;
	spin_lock_init(&vi->lock);

	err = virtinput_init_vqs(vi);
	अगर (err)
		जाओ err_init_vq;

	vi->idev = input_allocate_device();
	अगर (!vi->idev) अणु
		err = -ENOMEM;
		जाओ err_input_alloc;
	पूर्ण
	input_set_drvdata(vi->idev, vi);

	size = virtinput_cfg_select(vi, VIRTIO_INPUT_CFG_ID_NAME, 0);
	virtio_cपढ़ो_bytes(vi->vdev, दुरत्व(काष्ठा virtio_input_config,
					      u.string),
			   vi->name, min(size, माप(vi->name)));
	size = virtinput_cfg_select(vi, VIRTIO_INPUT_CFG_ID_SERIAL, 0);
	virtio_cपढ़ो_bytes(vi->vdev, दुरत्व(काष्ठा virtio_input_config,
					      u.string),
			   vi->serial, min(size, माप(vi->serial)));
	snम_लिखो(vi->phys, माप(vi->phys),
		 "virtio%d/input0", vdev->index);
	vi->idev->name = vi->name;
	vi->idev->phys = vi->phys;
	vi->idev->uniq = vi->serial;

	size = virtinput_cfg_select(vi, VIRTIO_INPUT_CFG_ID_DEVIDS, 0);
	अगर (size >= माप(काष्ठा virtio_input_devids)) अणु
		virtio_cपढ़ो_le(vi->vdev, काष्ठा virtio_input_config,
				u.ids.bustype, &vi->idev->id.bustype);
		virtio_cपढ़ो_le(vi->vdev, काष्ठा virtio_input_config,
				u.ids.venकरोr, &vi->idev->id.venकरोr);
		virtio_cपढ़ो_le(vi->vdev, काष्ठा virtio_input_config,
				u.ids.product, &vi->idev->id.product);
		virtio_cपढ़ो_le(vi->vdev, काष्ठा virtio_input_config,
				u.ids.version, &vi->idev->id.version);
	पूर्ण अन्यथा अणु
		vi->idev->id.bustype = BUS_VIRTUAL;
	पूर्ण

	virtinput_cfg_bits(vi, VIRTIO_INPUT_CFG_PROP_BITS, 0,
			   vi->idev->propbit, INPUT_PROP_CNT);
	size = virtinput_cfg_select(vi, VIRTIO_INPUT_CFG_EV_BITS, EV_REP);
	अगर (size)
		__set_bit(EV_REP, vi->idev->evbit);

	vi->idev->dev.parent = &vdev->dev;
	vi->idev->event = virtinput_status;

	/* device -> kernel */
	virtinput_cfg_bits(vi, VIRTIO_INPUT_CFG_EV_BITS, EV_KEY,
			   vi->idev->keybit, KEY_CNT);
	virtinput_cfg_bits(vi, VIRTIO_INPUT_CFG_EV_BITS, EV_REL,
			   vi->idev->relbit, REL_CNT);
	virtinput_cfg_bits(vi, VIRTIO_INPUT_CFG_EV_BITS, EV_ABS,
			   vi->idev->असलbit, ABS_CNT);
	virtinput_cfg_bits(vi, VIRTIO_INPUT_CFG_EV_BITS, EV_MSC,
			   vi->idev->mscbit, MSC_CNT);
	virtinput_cfg_bits(vi, VIRTIO_INPUT_CFG_EV_BITS, EV_SW,
			   vi->idev->swbit,  SW_CNT);

	/* kernel -> device */
	virtinput_cfg_bits(vi, VIRTIO_INPUT_CFG_EV_BITS, EV_LED,
			   vi->idev->ledbit, LED_CNT);
	virtinput_cfg_bits(vi, VIRTIO_INPUT_CFG_EV_BITS, EV_SND,
			   vi->idev->sndbit, SND_CNT);

	अगर (test_bit(EV_ABS, vi->idev->evbit)) अणु
		क्रम (असल = 0; असल < ABS_CNT; असल++) अणु
			अगर (!test_bit(असल, vi->idev->असलbit))
				जारी;
			virtinput_cfg_असल(vi, असल);
		पूर्ण

		अगर (test_bit(ABS_MT_SLOT, vi->idev->असलbit)) अणु
			nslots = input_असल_get_max(vi->idev, ABS_MT_SLOT) + 1;
			err = input_mt_init_slots(vi->idev, nslots, 0);
			अगर (err)
				जाओ err_mt_init_slots;
		पूर्ण
	पूर्ण

	virtio_device_पढ़ोy(vdev);
	vi->पढ़ोy = true;
	err = input_रेजिस्टर_device(vi->idev);
	अगर (err)
		जाओ err_input_रेजिस्टर;

	virtinput_fill_evt(vi);
	वापस 0;

err_input_रेजिस्टर:
	spin_lock_irqsave(&vi->lock, flags);
	vi->पढ़ोy = false;
	spin_unlock_irqrestore(&vi->lock, flags);
err_mt_init_slots:
	input_मुक्त_device(vi->idev);
err_input_alloc:
	vdev->config->del_vqs(vdev);
err_init_vq:
	kमुक्त(vi);
	वापस err;
पूर्ण

अटल व्योम virtinput_हटाओ(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtio_input *vi = vdev->priv;
	व्योम *buf;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&vi->lock, flags);
	vi->पढ़ोy = false;
	spin_unlock_irqrestore(&vi->lock, flags);

	input_unरेजिस्टर_device(vi->idev);
	vdev->config->reset(vdev);
	जबतक ((buf = virtqueue_detach_unused_buf(vi->sts)) != शून्य)
		kमुक्त(buf);
	vdev->config->del_vqs(vdev);
	kमुक्त(vi);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक virtinput_मुक्तze(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtio_input *vi = vdev->priv;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&vi->lock, flags);
	vi->पढ़ोy = false;
	spin_unlock_irqrestore(&vi->lock, flags);

	vdev->config->del_vqs(vdev);
	वापस 0;
पूर्ण

अटल पूर्णांक virtinput_restore(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtio_input *vi = vdev->priv;
	पूर्णांक err;

	err = virtinput_init_vqs(vi);
	अगर (err)
		वापस err;

	virtio_device_पढ़ोy(vdev);
	vi->पढ़ोy = true;
	virtinput_fill_evt(vi);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल अचिन्हित पूर्णांक features[] = अणु
	/* none */
पूर्ण;
अटल स्थिर काष्ठा virtio_device_id id_table[] = अणु
	अणु VIRTIO_ID_INPUT, VIRTIO_DEV_ANY_ID पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल काष्ठा virtio_driver virtio_input_driver = अणु
	.driver.name         = KBUILD_MODNAME,
	.driver.owner        = THIS_MODULE,
	.feature_table       = features,
	.feature_table_size  = ARRAY_SIZE(features),
	.id_table            = id_table,
	.probe               = virtinput_probe,
	.हटाओ              = virtinput_हटाओ,
#अगर_घोषित CONFIG_PM_SLEEP
	.मुक्तze	             = virtinput_मुक्तze,
	.restore             = virtinput_restore,
#पूर्ण_अगर
पूर्ण;

module_virtio_driver(virtio_input_driver);
MODULE_DEVICE_TABLE(virtio, id_table);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Virtio input device driver");
MODULE_AUTHOR("Gerd Hoffmann <kraxel@redhat.com>");
