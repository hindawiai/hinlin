<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * VIRTIO based driver क्रम vDPA device
 *
 * Copyright (c) 2020, Red Hat. All rights reserved.
 *     Author: Jason Wang <jasowang@redhat.com>
 *
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/uuid.h>
#समावेश <linux/virtपन.स>
#समावेश <linux/vdpa.h>
#समावेश <linux/virtio_config.h>
#समावेश <linux/virtio_ring.h>

#घोषणा MOD_VERSION  "0.1"
#घोषणा MOD_AUTHOR   "Jason Wang <jasowang@redhat.com>"
#घोषणा MOD_DESC     "vDPA bus driver for virtio devices"
#घोषणा MOD_LICENSE  "GPL v2"

काष्ठा virtio_vdpa_device अणु
	काष्ठा virtio_device vdev;
	काष्ठा vdpa_device *vdpa;
	u64 features;

	/* The lock to protect virtqueue list */
	spinlock_t lock;
	/* List of virtio_vdpa_vq_info */
	काष्ठा list_head virtqueues;
पूर्ण;

काष्ठा virtio_vdpa_vq_info अणु
	/* the actual virtqueue */
	काष्ठा virtqueue *vq;

	/* the list node क्रम the virtqueues list */
	काष्ठा list_head node;
पूर्ण;

अटल अंतरभूत काष्ठा virtio_vdpa_device *
to_virtio_vdpa_device(काष्ठा virtio_device *dev)
अणु
	वापस container_of(dev, काष्ठा virtio_vdpa_device, vdev);
पूर्ण

अटल काष्ठा vdpa_device *vd_get_vdpa(काष्ठा virtio_device *vdev)
अणु
	वापस to_virtio_vdpa_device(vdev)->vdpa;
पूर्ण

अटल व्योम virtio_vdpa_get(काष्ठा virtio_device *vdev, अचिन्हित offset,
			    व्योम *buf, अचिन्हित len)
अणु
	काष्ठा vdpa_device *vdpa = vd_get_vdpa(vdev);

	vdpa_get_config(vdpa, offset, buf, len);
पूर्ण

अटल व्योम virtio_vdpa_set(काष्ठा virtio_device *vdev, अचिन्हित offset,
			    स्थिर व्योम *buf, अचिन्हित len)
अणु
	काष्ठा vdpa_device *vdpa = vd_get_vdpa(vdev);
	स्थिर काष्ठा vdpa_config_ops *ops = vdpa->config;

	ops->set_config(vdpa, offset, buf, len);
पूर्ण

अटल u32 virtio_vdpa_generation(काष्ठा virtio_device *vdev)
अणु
	काष्ठा vdpa_device *vdpa = vd_get_vdpa(vdev);
	स्थिर काष्ठा vdpa_config_ops *ops = vdpa->config;

	अगर (ops->get_generation)
		वापस ops->get_generation(vdpa);

	वापस 0;
पूर्ण

अटल u8 virtio_vdpa_get_status(काष्ठा virtio_device *vdev)
अणु
	काष्ठा vdpa_device *vdpa = vd_get_vdpa(vdev);
	स्थिर काष्ठा vdpa_config_ops *ops = vdpa->config;

	वापस ops->get_status(vdpa);
पूर्ण

अटल व्योम virtio_vdpa_set_status(काष्ठा virtio_device *vdev, u8 status)
अणु
	काष्ठा vdpa_device *vdpa = vd_get_vdpa(vdev);
	स्थिर काष्ठा vdpa_config_ops *ops = vdpa->config;

	वापस ops->set_status(vdpa, status);
पूर्ण

अटल व्योम virtio_vdpa_reset(काष्ठा virtio_device *vdev)
अणु
	काष्ठा vdpa_device *vdpa = vd_get_vdpa(vdev);

	vdpa_reset(vdpa);
पूर्ण

अटल bool virtio_vdpa_notअगरy(काष्ठा virtqueue *vq)
अणु
	काष्ठा vdpa_device *vdpa = vd_get_vdpa(vq->vdev);
	स्थिर काष्ठा vdpa_config_ops *ops = vdpa->config;

	ops->kick_vq(vdpa, vq->index);

	वापस true;
पूर्ण

अटल irqवापस_t virtio_vdpa_config_cb(व्योम *निजी)
अणु
	काष्ठा virtio_vdpa_device *vd_dev = निजी;

	virtio_config_changed(&vd_dev->vdev);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t virtio_vdpa_virtqueue_cb(व्योम *निजी)
अणु
	काष्ठा virtio_vdpa_vq_info *info = निजी;

	वापस vring_पूर्णांकerrupt(0, info->vq);
पूर्ण

अटल काष्ठा virtqueue *
virtio_vdpa_setup_vq(काष्ठा virtio_device *vdev, अचिन्हित पूर्णांक index,
		     व्योम (*callback)(काष्ठा virtqueue *vq),
		     स्थिर अक्षर *name, bool ctx)
अणु
	काष्ठा virtio_vdpa_device *vd_dev = to_virtio_vdpa_device(vdev);
	काष्ठा vdpa_device *vdpa = vd_get_vdpa(vdev);
	स्थिर काष्ठा vdpa_config_ops *ops = vdpa->config;
	काष्ठा virtio_vdpa_vq_info *info;
	काष्ठा vdpa_callback cb;
	काष्ठा virtqueue *vq;
	u64 desc_addr, driver_addr, device_addr;
	अचिन्हित दीर्घ flags;
	u32 align, num;
	पूर्णांक err;

	अगर (!name)
		वापस शून्य;

	/* Queue shouldn't alपढ़ोy be set up. */
	अगर (ops->get_vq_पढ़ोy(vdpa, index))
		वापस ERR_PTR(-ENOENT);

	/* Allocate and fill out our active queue description */
	info = kदो_स्मृति(माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस ERR_PTR(-ENOMEM);

	num = ops->get_vq_num_max(vdpa);
	अगर (num == 0) अणु
		err = -ENOENT;
		जाओ error_new_virtqueue;
	पूर्ण

	/* Create the vring */
	align = ops->get_vq_align(vdpa);
	vq = vring_create_virtqueue(index, num, align, vdev,
				    true, true, ctx,
				    virtio_vdpa_notअगरy, callback, name);
	अगर (!vq) अणु
		err = -ENOMEM;
		जाओ error_new_virtqueue;
	पूर्ण

	/* Setup virtqueue callback */
	cb.callback = virtio_vdpa_virtqueue_cb;
	cb.निजी = info;
	ops->set_vq_cb(vdpa, index, &cb);
	ops->set_vq_num(vdpa, index, virtqueue_get_vring_size(vq));

	desc_addr = virtqueue_get_desc_addr(vq);
	driver_addr = virtqueue_get_avail_addr(vq);
	device_addr = virtqueue_get_used_addr(vq);

	अगर (ops->set_vq_address(vdpa, index,
				desc_addr, driver_addr,
				device_addr)) अणु
		err = -EINVAL;
		जाओ err_vq;
	पूर्ण

	ops->set_vq_पढ़ोy(vdpa, index, 1);

	vq->priv = info;
	info->vq = vq;

	spin_lock_irqsave(&vd_dev->lock, flags);
	list_add(&info->node, &vd_dev->virtqueues);
	spin_unlock_irqrestore(&vd_dev->lock, flags);

	वापस vq;

err_vq:
	vring_del_virtqueue(vq);
error_new_virtqueue:
	ops->set_vq_पढ़ोy(vdpa, index, 0);
	/* VDPA driver should make sure vq is stopeed here */
	WARN_ON(ops->get_vq_पढ़ोy(vdpa, index));
	kमुक्त(info);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम virtio_vdpa_del_vq(काष्ठा virtqueue *vq)
अणु
	काष्ठा virtio_vdpa_device *vd_dev = to_virtio_vdpa_device(vq->vdev);
	काष्ठा vdpa_device *vdpa = vd_dev->vdpa;
	स्थिर काष्ठा vdpa_config_ops *ops = vdpa->config;
	काष्ठा virtio_vdpa_vq_info *info = vq->priv;
	अचिन्हित पूर्णांक index = vq->index;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&vd_dev->lock, flags);
	list_del(&info->node);
	spin_unlock_irqrestore(&vd_dev->lock, flags);

	/* Select and deactivate the queue (best efक्रमt) */
	ops->set_vq_पढ़ोy(vdpa, index, 0);

	vring_del_virtqueue(vq);

	kमुक्त(info);
पूर्ण

अटल व्योम virtio_vdpa_del_vqs(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtqueue *vq, *n;

	list_क्रम_each_entry_safe(vq, n, &vdev->vqs, list)
		virtio_vdpa_del_vq(vq);
पूर्ण

अटल पूर्णांक virtio_vdpa_find_vqs(काष्ठा virtio_device *vdev, अचिन्हित nvqs,
				काष्ठा virtqueue *vqs[],
				vq_callback_t *callbacks[],
				स्थिर अक्षर * स्थिर names[],
				स्थिर bool *ctx,
				काष्ठा irq_affinity *desc)
अणु
	काष्ठा virtio_vdpa_device *vd_dev = to_virtio_vdpa_device(vdev);
	काष्ठा vdpa_device *vdpa = vd_get_vdpa(vdev);
	स्थिर काष्ठा vdpa_config_ops *ops = vdpa->config;
	काष्ठा vdpa_callback cb;
	पूर्णांक i, err, queue_idx = 0;

	क्रम (i = 0; i < nvqs; ++i) अणु
		अगर (!names[i]) अणु
			vqs[i] = शून्य;
			जारी;
		पूर्ण

		vqs[i] = virtio_vdpa_setup_vq(vdev, queue_idx++,
					      callbacks[i], names[i], ctx ?
					      ctx[i] : false);
		अगर (IS_ERR(vqs[i])) अणु
			err = PTR_ERR(vqs[i]);
			जाओ err_setup_vq;
		पूर्ण
	पूर्ण

	cb.callback = virtio_vdpa_config_cb;
	cb.निजी = vd_dev;
	ops->set_config_cb(vdpa, &cb);

	वापस 0;

err_setup_vq:
	virtio_vdpa_del_vqs(vdev);
	वापस err;
पूर्ण

अटल u64 virtio_vdpa_get_features(काष्ठा virtio_device *vdev)
अणु
	काष्ठा vdpa_device *vdpa = vd_get_vdpa(vdev);
	स्थिर काष्ठा vdpa_config_ops *ops = vdpa->config;

	वापस ops->get_features(vdpa);
पूर्ण

अटल पूर्णांक virtio_vdpa_finalize_features(काष्ठा virtio_device *vdev)
अणु
	काष्ठा vdpa_device *vdpa = vd_get_vdpa(vdev);

	/* Give virtio_ring a chance to accept features. */
	vring_transport_features(vdev);

	वापस vdpa_set_features(vdpa, vdev->features);
पूर्ण

अटल स्थिर अक्षर *virtio_vdpa_bus_name(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtio_vdpa_device *vd_dev = to_virtio_vdpa_device(vdev);
	काष्ठा vdpa_device *vdpa = vd_dev->vdpa;

	वापस dev_name(&vdpa->dev);
पूर्ण

अटल स्थिर काष्ठा virtio_config_ops virtio_vdpa_config_ops = अणु
	.get		= virtio_vdpa_get,
	.set		= virtio_vdpa_set,
	.generation	= virtio_vdpa_generation,
	.get_status	= virtio_vdpa_get_status,
	.set_status	= virtio_vdpa_set_status,
	.reset		= virtio_vdpa_reset,
	.find_vqs	= virtio_vdpa_find_vqs,
	.del_vqs	= virtio_vdpa_del_vqs,
	.get_features	= virtio_vdpa_get_features,
	.finalize_features = virtio_vdpa_finalize_features,
	.bus_name	= virtio_vdpa_bus_name,
पूर्ण;

अटल व्योम virtio_vdpa_release_dev(काष्ठा device *_d)
अणु
	काष्ठा virtio_device *vdev =
	       container_of(_d, काष्ठा virtio_device, dev);
	काष्ठा virtio_vdpa_device *vd_dev =
	       container_of(vdev, काष्ठा virtio_vdpa_device, vdev);

	kमुक्त(vd_dev);
पूर्ण

अटल पूर्णांक virtio_vdpa_probe(काष्ठा vdpa_device *vdpa)
अणु
	स्थिर काष्ठा vdpa_config_ops *ops = vdpa->config;
	काष्ठा virtio_vdpa_device *vd_dev, *reg_dev = शून्य;
	पूर्णांक ret = -EINVAL;

	vd_dev = kzalloc(माप(*vd_dev), GFP_KERNEL);
	अगर (!vd_dev)
		वापस -ENOMEM;

	vd_dev->vdev.dev.parent = vdpa_get_dma_dev(vdpa);
	vd_dev->vdev.dev.release = virtio_vdpa_release_dev;
	vd_dev->vdev.config = &virtio_vdpa_config_ops;
	vd_dev->vdpa = vdpa;
	INIT_LIST_HEAD(&vd_dev->virtqueues);
	spin_lock_init(&vd_dev->lock);

	vd_dev->vdev.id.device = ops->get_device_id(vdpa);
	अगर (vd_dev->vdev.id.device == 0)
		जाओ err;

	vd_dev->vdev.id.venकरोr = ops->get_venकरोr_id(vdpa);
	ret = रेजिस्टर_virtio_device(&vd_dev->vdev);
	reg_dev = vd_dev;
	अगर (ret)
		जाओ err;

	vdpa_set_drvdata(vdpa, vd_dev);

	वापस 0;

err:
	अगर (reg_dev)
		put_device(&vd_dev->vdev.dev);
	अन्यथा
		kमुक्त(vd_dev);
	वापस ret;
पूर्ण

अटल व्योम virtio_vdpa_हटाओ(काष्ठा vdpa_device *vdpa)
अणु
	काष्ठा virtio_vdpa_device *vd_dev = vdpa_get_drvdata(vdpa);

	unरेजिस्टर_virtio_device(&vd_dev->vdev);
पूर्ण

अटल काष्ठा vdpa_driver virtio_vdpa_driver = अणु
	.driver = अणु
		.name	= "virtio_vdpa",
	पूर्ण,
	.probe	= virtio_vdpa_probe,
	.हटाओ = virtio_vdpa_हटाओ,
पूर्ण;

module_vdpa_driver(virtio_vdpa_driver);

MODULE_VERSION(MOD_VERSION);
MODULE_LICENSE(MOD_LICENSE);
MODULE_AUTHOR(MOD_AUTHOR);
MODULE_DESCRIPTION(MOD_DESC);
