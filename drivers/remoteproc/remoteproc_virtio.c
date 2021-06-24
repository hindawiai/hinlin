<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Remote processor messaging transport (OMAP platक्रमm-specअगरic bits)
 *
 * Copyright (C) 2011 Texas Instruments, Inc.
 * Copyright (C) 2011 Google, Inc.
 *
 * Ohad Ben-Cohen <ohad@wizery.com>
 * Brian Swetland <swetland@google.com>
 */

#समावेश <linux/dma-map-ops.h>
#समावेश <linux/export.h>
#समावेश <linux/of_reserved_स्मृति.स>
#समावेश <linux/remoteproc.h>
#समावेश <linux/virtपन.स>
#समावेश <linux/virtio_config.h>
#समावेश <linux/virtio_ids.h>
#समावेश <linux/virtio_ring.h>
#समावेश <linux/err.h>
#समावेश <linux/kref.h>
#समावेश <linux/slab.h>

#समावेश "remoteproc_internal.h"

/* kick the remote processor, and let it know which virtqueue to poke at */
अटल bool rproc_virtio_notअगरy(काष्ठा virtqueue *vq)
अणु
	काष्ठा rproc_vring *rvring = vq->priv;
	काष्ठा rproc *rproc = rvring->rvdev->rproc;
	पूर्णांक notअगरyid = rvring->notअगरyid;

	dev_dbg(&rproc->dev, "kicking vq index: %d\n", notअगरyid);

	rproc->ops->kick(rproc, notअगरyid);
	वापस true;
पूर्ण

/**
 * rproc_vq_पूर्णांकerrupt() - tell remoteproc that a virtqueue is पूर्णांकerrupted
 * @rproc: handle to the remote processor
 * @notअगरyid: index of the संकेतled virtqueue (unique per this @rproc)
 *
 * This function should be called by the platक्रमm-specअगरic rproc driver,
 * when the remote processor संकेतs that a specअगरic virtqueue has pending
 * messages available.
 *
 * Returns IRQ_NONE अगर no message was found in the @notअगरyid virtqueue,
 * and otherwise वापसs IRQ_HANDLED.
 */
irqवापस_t rproc_vq_पूर्णांकerrupt(काष्ठा rproc *rproc, पूर्णांक notअगरyid)
अणु
	काष्ठा rproc_vring *rvring;

	dev_dbg(&rproc->dev, "vq index %d is interrupted\n", notअगरyid);

	rvring = idr_find(&rproc->notअगरyids, notअगरyid);
	अगर (!rvring || !rvring->vq)
		वापस IRQ_NONE;

	वापस vring_पूर्णांकerrupt(0, rvring->vq);
पूर्ण
EXPORT_SYMBOL(rproc_vq_पूर्णांकerrupt);

अटल काष्ठा virtqueue *rp_find_vq(काष्ठा virtio_device *vdev,
				    अचिन्हित पूर्णांक id,
				    व्योम (*callback)(काष्ठा virtqueue *vq),
				    स्थिर अक्षर *name, bool ctx)
अणु
	काष्ठा rproc_vdev *rvdev = vdev_to_rvdev(vdev);
	काष्ठा rproc *rproc = vdev_to_rproc(vdev);
	काष्ठा device *dev = &rproc->dev;
	काष्ठा rproc_mem_entry *mem;
	काष्ठा rproc_vring *rvring;
	काष्ठा fw_rsc_vdev *rsc;
	काष्ठा virtqueue *vq;
	व्योम *addr;
	पूर्णांक len, size;

	/* we're temporarily limited to two virtqueues per rvdev */
	अगर (id >= ARRAY_SIZE(rvdev->vring))
		वापस ERR_PTR(-EINVAL);

	अगर (!name)
		वापस शून्य;

	/* Search allocated memory region by name */
	mem = rproc_find_carveout_by_name(rproc, "vdev%dvring%d", rvdev->index,
					  id);
	अगर (!mem || !mem->va)
		वापस ERR_PTR(-ENOMEM);

	rvring = &rvdev->vring[id];
	addr = mem->va;
	len = rvring->len;

	/* zero vring */
	size = vring_size(len, rvring->align);
	स_रखो(addr, 0, size);

	dev_dbg(dev, "vring%d: va %pK qsz %d notifyid %d\n",
		id, addr, len, rvring->notअगरyid);

	/*
	 * Create the new vq, and tell virtio we're not पूर्णांकerested in
	 * the 'weak' smp barriers, since we're talking with a real device.
	 */
	vq = vring_new_virtqueue(id, len, rvring->align, vdev, false, ctx,
				 addr, rproc_virtio_notअगरy, callback, name);
	अगर (!vq) अणु
		dev_err(dev, "vring_new_virtqueue %s failed\n", name);
		rproc_मुक्त_vring(rvring);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	rvring->vq = vq;
	vq->priv = rvring;

	/* Update vring in resource table */
	rsc = (व्योम *)rproc->table_ptr + rvdev->rsc_offset;
	rsc->vring[id].da = mem->da;

	वापस vq;
पूर्ण

अटल व्योम __rproc_virtio_del_vqs(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtqueue *vq, *n;
	काष्ठा rproc_vring *rvring;

	list_क्रम_each_entry_safe(vq, n, &vdev->vqs, list) अणु
		rvring = vq->priv;
		rvring->vq = शून्य;
		vring_del_virtqueue(vq);
	पूर्ण
पूर्ण

अटल व्योम rproc_virtio_del_vqs(काष्ठा virtio_device *vdev)
अणु
	__rproc_virtio_del_vqs(vdev);
पूर्ण

अटल पूर्णांक rproc_virtio_find_vqs(काष्ठा virtio_device *vdev, अचिन्हित पूर्णांक nvqs,
				 काष्ठा virtqueue *vqs[],
				 vq_callback_t *callbacks[],
				 स्थिर अक्षर * स्थिर names[],
				 स्थिर bool * ctx,
				 काष्ठा irq_affinity *desc)
अणु
	पूर्णांक i, ret, queue_idx = 0;

	क्रम (i = 0; i < nvqs; ++i) अणु
		अगर (!names[i]) अणु
			vqs[i] = शून्य;
			जारी;
		पूर्ण

		vqs[i] = rp_find_vq(vdev, queue_idx++, callbacks[i], names[i],
				    ctx ? ctx[i] : false);
		अगर (IS_ERR(vqs[i])) अणु
			ret = PTR_ERR(vqs[i]);
			जाओ error;
		पूर्ण
	पूर्ण

	वापस 0;

error:
	__rproc_virtio_del_vqs(vdev);
	वापस ret;
पूर्ण

अटल u8 rproc_virtio_get_status(काष्ठा virtio_device *vdev)
अणु
	काष्ठा rproc_vdev *rvdev = vdev_to_rvdev(vdev);
	काष्ठा fw_rsc_vdev *rsc;

	rsc = (व्योम *)rvdev->rproc->table_ptr + rvdev->rsc_offset;

	वापस rsc->status;
पूर्ण

अटल व्योम rproc_virtio_set_status(काष्ठा virtio_device *vdev, u8 status)
अणु
	काष्ठा rproc_vdev *rvdev = vdev_to_rvdev(vdev);
	काष्ठा fw_rsc_vdev *rsc;

	rsc = (व्योम *)rvdev->rproc->table_ptr + rvdev->rsc_offset;

	rsc->status = status;
	dev_dbg(&vdev->dev, "status: %d\n", status);
पूर्ण

अटल व्योम rproc_virtio_reset(काष्ठा virtio_device *vdev)
अणु
	काष्ठा rproc_vdev *rvdev = vdev_to_rvdev(vdev);
	काष्ठा fw_rsc_vdev *rsc;

	rsc = (व्योम *)rvdev->rproc->table_ptr + rvdev->rsc_offset;

	rsc->status = 0;
	dev_dbg(&vdev->dev, "reset !\n");
पूर्ण

/* provide the vdev features as retrieved from the firmware */
अटल u64 rproc_virtio_get_features(काष्ठा virtio_device *vdev)
अणु
	काष्ठा rproc_vdev *rvdev = vdev_to_rvdev(vdev);
	काष्ठा fw_rsc_vdev *rsc;

	rsc = (व्योम *)rvdev->rproc->table_ptr + rvdev->rsc_offset;

	वापस rsc->dfeatures;
पूर्ण

अटल व्योम rproc_transport_features(काष्ठा virtio_device *vdev)
अणु
	/*
	 * Packed ring isn't enabled on remoteproc क्रम now,
	 * because remoteproc uses vring_new_virtqueue() which
	 * creates virtio rings on pपुनः_स्मृतिated memory.
	 */
	__virtio_clear_bit(vdev, VIRTIO_F_RING_PACKED);
पूर्ण

अटल पूर्णांक rproc_virtio_finalize_features(काष्ठा virtio_device *vdev)
अणु
	काष्ठा rproc_vdev *rvdev = vdev_to_rvdev(vdev);
	काष्ठा fw_rsc_vdev *rsc;

	rsc = (व्योम *)rvdev->rproc->table_ptr + rvdev->rsc_offset;

	/* Give virtio_ring a chance to accept features */
	vring_transport_features(vdev);

	/* Give virtio_rproc a chance to accept features. */
	rproc_transport_features(vdev);

	/* Make sure we करोn't have any features > 32 bits! */
	BUG_ON((u32)vdev->features != vdev->features);

	/*
	 * Remember the finalized features of our vdev, and provide it
	 * to the remote processor once it is घातered on.
	 */
	rsc->gfeatures = vdev->features;

	वापस 0;
पूर्ण

अटल व्योम rproc_virtio_get(काष्ठा virtio_device *vdev, अचिन्हित पूर्णांक offset,
			     व्योम *buf, अचिन्हित पूर्णांक len)
अणु
	काष्ठा rproc_vdev *rvdev = vdev_to_rvdev(vdev);
	काष्ठा fw_rsc_vdev *rsc;
	व्योम *cfg;

	rsc = (व्योम *)rvdev->rproc->table_ptr + rvdev->rsc_offset;
	cfg = &rsc->vring[rsc->num_of_vrings];

	अगर (offset + len > rsc->config_len || offset + len < len) अणु
		dev_err(&vdev->dev, "rproc_virtio_get: access out of bounds\n");
		वापस;
	पूर्ण

	स_नकल(buf, cfg + offset, len);
पूर्ण

अटल व्योम rproc_virtio_set(काष्ठा virtio_device *vdev, अचिन्हित पूर्णांक offset,
			     स्थिर व्योम *buf, अचिन्हित पूर्णांक len)
अणु
	काष्ठा rproc_vdev *rvdev = vdev_to_rvdev(vdev);
	काष्ठा fw_rsc_vdev *rsc;
	व्योम *cfg;

	rsc = (व्योम *)rvdev->rproc->table_ptr + rvdev->rsc_offset;
	cfg = &rsc->vring[rsc->num_of_vrings];

	अगर (offset + len > rsc->config_len || offset + len < len) अणु
		dev_err(&vdev->dev, "rproc_virtio_set: access out of bounds\n");
		वापस;
	पूर्ण

	स_नकल(cfg + offset, buf, len);
पूर्ण

अटल स्थिर काष्ठा virtio_config_ops rproc_virtio_config_ops = अणु
	.get_features	= rproc_virtio_get_features,
	.finalize_features = rproc_virtio_finalize_features,
	.find_vqs	= rproc_virtio_find_vqs,
	.del_vqs	= rproc_virtio_del_vqs,
	.reset		= rproc_virtio_reset,
	.set_status	= rproc_virtio_set_status,
	.get_status	= rproc_virtio_get_status,
	.get		= rproc_virtio_get,
	.set		= rproc_virtio_set,
पूर्ण;

/*
 * This function is called whenever vdev is released, and is responsible
 * to decrement the remote processor's refcount which was taken when vdev was
 * added.
 *
 * Never call this function directly; it will be called by the driver
 * core when needed.
 */
अटल व्योम rproc_virtio_dev_release(काष्ठा device *dev)
अणु
	काष्ठा virtio_device *vdev = dev_to_virtio(dev);
	काष्ठा rproc_vdev *rvdev = vdev_to_rvdev(vdev);
	काष्ठा rproc *rproc = vdev_to_rproc(vdev);

	kमुक्त(vdev);

	kref_put(&rvdev->refcount, rproc_vdev_release);

	put_device(&rproc->dev);
पूर्ण

/**
 * rproc_add_virtio_dev() - रेजिस्टर an rproc-induced virtio device
 * @rvdev: the remote vdev
 * @id: the device type identअगरication (used to match it with a driver).
 *
 * This function रेजिस्टरs a virtio device. This vdev's partent is
 * the rproc device.
 *
 * Returns 0 on success or an appropriate error value otherwise.
 */
पूर्णांक rproc_add_virtio_dev(काष्ठा rproc_vdev *rvdev, पूर्णांक id)
अणु
	काष्ठा rproc *rproc = rvdev->rproc;
	काष्ठा device *dev = &rvdev->dev;
	काष्ठा virtio_device *vdev;
	काष्ठा rproc_mem_entry *mem;
	पूर्णांक ret;

	अगर (rproc->ops->kick == शून्य) अणु
		ret = -EINVAL;
		dev_err(dev, ".kick method not defined for %s\n", rproc->name);
		जाओ out;
	पूर्ण

	/* Try to find dedicated vdev buffer carveout */
	mem = rproc_find_carveout_by_name(rproc, "vdev%dbuffer", rvdev->index);
	अगर (mem) अणु
		phys_addr_t pa;

		अगर (mem->of_resm_idx != -1) अणु
			काष्ठा device_node *np = rproc->dev.parent->of_node;

			/* Associate reserved memory to vdev device */
			ret = of_reserved_mem_device_init_by_idx(dev, np,
								 mem->of_resm_idx);
			अगर (ret) अणु
				dev_err(dev, "Can't associate reserved memory\n");
				जाओ out;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (mem->va) अणु
				dev_warn(dev, "vdev %d buffer already mapped\n",
					 rvdev->index);
				pa = rproc_va_to_pa(mem->va);
			पूर्ण अन्यथा अणु
				/* Use dma address as carveout no memmapped yet */
				pa = (phys_addr_t)mem->dma;
			पूर्ण

			/* Associate vdev buffer memory pool to vdev subdev */
			ret = dma_declare_coherent_memory(dev, pa,
							   mem->da,
							   mem->len);
			अगर (ret < 0) अणु
				dev_err(dev, "Failed to associate buffer\n");
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा device_node *np = rproc->dev.parent->of_node;

		/*
		 * If we करोn't have dedicated buffer, just attempt to re-assign
		 * the reserved memory from our parent. A शेष memory-region
		 * at index 0 from the parent's memory-regions is asचिन्हित क्रम
		 * the rvdev dev to allocate from. Failure is non-critical and
		 * the allocations will fall back to global pools, so करोn't
		 * check वापस value either.
		 */
		of_reserved_mem_device_init_by_idx(dev, np, 0);
	पूर्ण

	/* Allocate virtio device */
	vdev = kzalloc(माप(*vdev), GFP_KERNEL);
	अगर (!vdev) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	vdev->id.device	= id,
	vdev->config = &rproc_virtio_config_ops,
	vdev->dev.parent = dev;
	vdev->dev.release = rproc_virtio_dev_release;

	/*
	 * We're indirectly making a non-temporary copy of the rproc poपूर्णांकer
	 * here, because drivers probed with this vdev will indirectly
	 * access the wrapping rproc.
	 *
	 * Thereक्रमe we must increment the rproc refcount here, and decrement
	 * it _only_ when the vdev is released.
	 */
	get_device(&rproc->dev);

	/* Reference the vdev and vring allocations */
	kref_get(&rvdev->refcount);

	ret = रेजिस्टर_virtio_device(vdev);
	अगर (ret) अणु
		put_device(&vdev->dev);
		dev_err(dev, "failed to register vdev: %d\n", ret);
		जाओ out;
	पूर्ण

	dev_info(dev, "registered %s (type %d)\n", dev_name(&vdev->dev), id);

out:
	वापस ret;
पूर्ण

/**
 * rproc_हटाओ_virtio_dev() - हटाओ an rproc-induced virtio device
 * @dev: the virtio device
 * @data: must be null
 *
 * This function unरेजिस्टरs an existing virtio device.
 */
पूर्णांक rproc_हटाओ_virtio_dev(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा virtio_device *vdev = dev_to_virtio(dev);

	unरेजिस्टर_virtio_device(vdev);
	वापस 0;
पूर्ण
