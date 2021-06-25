<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Virtio PCI driver - modern (virtio 1.0) device support
 *
 * This module allows virtio devices to be used over a भव PCI device.
 * This can be used with QEMU based VMMs like KVM or Xen.
 *
 * Copyright IBM Corp. 2007
 * Copyright Red Hat, Inc. 2014
 *
 * Authors:
 *  Anthony Liguori  <aliguori@us.ibm.com>
 *  Rusty Russell <rusty@rustcorp.com.au>
 *  Michael S. Tsirkin <mst@redhat.com>
 */

#समावेश <linux/delay.h>
#घोषणा VIRTIO_PCI_NO_LEGACY
#घोषणा VIRTIO_RING_NO_LEGACY
#समावेश "virtio_pci_common.h"

अटल u64 vp_get_features(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtio_pci_device *vp_dev = to_vp_device(vdev);

	वापस vp_modern_get_features(&vp_dev->mdev);
पूर्ण

अटल व्योम vp_transport_features(काष्ठा virtio_device *vdev, u64 features)
अणु
	काष्ठा virtio_pci_device *vp_dev = to_vp_device(vdev);
	काष्ठा pci_dev *pci_dev = vp_dev->pci_dev;

	अगर ((features & BIT_ULL(VIRTIO_F_SR_IOV)) &&
			pci_find_ext_capability(pci_dev, PCI_EXT_CAP_ID_SRIOV))
		__virtio_set_bit(vdev, VIRTIO_F_SR_IOV);
पूर्ण

/* virtio config->finalize_features() implementation */
अटल पूर्णांक vp_finalize_features(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtio_pci_device *vp_dev = to_vp_device(vdev);
	u64 features = vdev->features;

	/* Give virtio_ring a chance to accept features. */
	vring_transport_features(vdev);

	/* Give virtio_pci a chance to accept features. */
	vp_transport_features(vdev, features);

	अगर (!__virtio_test_bit(vdev, VIRTIO_F_VERSION_1)) अणु
		dev_err(&vdev->dev, "virtio: device uses modern interface "
			"but does not have VIRTIO_F_VERSION_1\n");
		वापस -EINVAL;
	पूर्ण

	vp_modern_set_features(&vp_dev->mdev, vdev->features);

	वापस 0;
पूर्ण

/* virtio config->get() implementation */
अटल व्योम vp_get(काष्ठा virtio_device *vdev, अचिन्हित offset,
		   व्योम *buf, अचिन्हित len)
अणु
	काष्ठा virtio_pci_device *vp_dev = to_vp_device(vdev);
	काष्ठा virtio_pci_modern_device *mdev = &vp_dev->mdev;
	व्योम __iomem *device = mdev->device;
	u8 b;
	__le16 w;
	__le32 l;

	BUG_ON(offset + len > mdev->device_len);

	चयन (len) अणु
	हाल 1:
		b = ioपढ़ो8(device + offset);
		स_नकल(buf, &b, माप b);
		अवरोध;
	हाल 2:
		w = cpu_to_le16(ioपढ़ो16(device + offset));
		स_नकल(buf, &w, माप w);
		अवरोध;
	हाल 4:
		l = cpu_to_le32(ioपढ़ो32(device + offset));
		स_नकल(buf, &l, माप l);
		अवरोध;
	हाल 8:
		l = cpu_to_le32(ioपढ़ो32(device + offset));
		स_नकल(buf, &l, माप l);
		l = cpu_to_le32(ioपढ़ो32(device + offset + माप l));
		स_नकल(buf + माप l, &l, माप l);
		अवरोध;
	शेष:
		BUG();
	पूर्ण
पूर्ण

/* the config->set() implementation.  it's symmetric to the config->get()
 * implementation */
अटल व्योम vp_set(काष्ठा virtio_device *vdev, अचिन्हित offset,
		   स्थिर व्योम *buf, अचिन्हित len)
अणु
	काष्ठा virtio_pci_device *vp_dev = to_vp_device(vdev);
	काष्ठा virtio_pci_modern_device *mdev = &vp_dev->mdev;
	व्योम __iomem *device = mdev->device;
	u8 b;
	__le16 w;
	__le32 l;

	BUG_ON(offset + len > mdev->device_len);

	चयन (len) अणु
	हाल 1:
		स_नकल(&b, buf, माप b);
		ioग_लिखो8(b, device + offset);
		अवरोध;
	हाल 2:
		स_नकल(&w, buf, माप w);
		ioग_लिखो16(le16_to_cpu(w), device + offset);
		अवरोध;
	हाल 4:
		स_नकल(&l, buf, माप l);
		ioग_लिखो32(le32_to_cpu(l), device + offset);
		अवरोध;
	हाल 8:
		स_नकल(&l, buf, माप l);
		ioग_लिखो32(le32_to_cpu(l), device + offset);
		स_नकल(&l, buf + माप l, माप l);
		ioग_लिखो32(le32_to_cpu(l), device + offset + माप l);
		अवरोध;
	शेष:
		BUG();
	पूर्ण
पूर्ण

अटल u32 vp_generation(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtio_pci_device *vp_dev = to_vp_device(vdev);

	वापस vp_modern_generation(&vp_dev->mdev);
पूर्ण

/* config->अणुget,setपूर्ण_status() implementations */
अटल u8 vp_get_status(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtio_pci_device *vp_dev = to_vp_device(vdev);

	वापस vp_modern_get_status(&vp_dev->mdev);
पूर्ण

अटल व्योम vp_set_status(काष्ठा virtio_device *vdev, u8 status)
अणु
	काष्ठा virtio_pci_device *vp_dev = to_vp_device(vdev);

	/* We should never be setting status to 0. */
	BUG_ON(status == 0);
	vp_modern_set_status(&vp_dev->mdev, status);
पूर्ण

अटल व्योम vp_reset(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtio_pci_device *vp_dev = to_vp_device(vdev);
	काष्ठा virtio_pci_modern_device *mdev = &vp_dev->mdev;

	/* 0 status means a reset. */
	vp_modern_set_status(mdev, 0);
	/* After writing 0 to device_status, the driver MUST रुको क्रम a पढ़ो of
	 * device_status to वापस 0 beक्रमe reinitializing the device.
	 * This will flush out the status ग_लिखो, and flush in device ग_लिखोs,
	 * including MSI-X पूर्णांकerrupts, अगर any.
	 */
	जबतक (vp_modern_get_status(mdev))
		msleep(1);
	/* Flush pending VQ/configuration callbacks. */
	vp_synchronize_vectors(vdev);
पूर्ण

अटल u16 vp_config_vector(काष्ठा virtio_pci_device *vp_dev, u16 vector)
अणु
	वापस vp_modern_config_vector(&vp_dev->mdev, vector);
पूर्ण

अटल काष्ठा virtqueue *setup_vq(काष्ठा virtio_pci_device *vp_dev,
				  काष्ठा virtio_pci_vq_info *info,
				  अचिन्हित index,
				  व्योम (*callback)(काष्ठा virtqueue *vq),
				  स्थिर अक्षर *name,
				  bool ctx,
				  u16 msix_vec)
अणु

	काष्ठा virtio_pci_modern_device *mdev = &vp_dev->mdev;
	काष्ठा virtqueue *vq;
	u16 num;
	पूर्णांक err;

	अगर (index >= vp_modern_get_num_queues(mdev))
		वापस ERR_PTR(-ENOENT);

	/* Check अगर queue is either not available or alपढ़ोy active. */
	num = vp_modern_get_queue_size(mdev, index);
	अगर (!num || vp_modern_get_queue_enable(mdev, index))
		वापस ERR_PTR(-ENOENT);

	अगर (num & (num - 1)) अणु
		dev_warn(&vp_dev->pci_dev->dev, "bad queue size %u", num);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	info->msix_vector = msix_vec;

	/* create the vring */
	vq = vring_create_virtqueue(index, num,
				    SMP_CACHE_BYTES, &vp_dev->vdev,
				    true, true, ctx,
				    vp_notअगरy, callback, name);
	अगर (!vq)
		वापस ERR_PTR(-ENOMEM);

	/* activate the queue */
	vp_modern_set_queue_size(mdev, index, virtqueue_get_vring_size(vq));
	vp_modern_queue_address(mdev, index, virtqueue_get_desc_addr(vq),
				virtqueue_get_avail_addr(vq),
				virtqueue_get_used_addr(vq));

	vq->priv = (व्योम __क्रमce *)vp_modern_map_vq_notअगरy(mdev, index, शून्य);
	अगर (!vq->priv) अणु
		err = -ENOMEM;
		जाओ err_map_notअगरy;
	पूर्ण

	अगर (msix_vec != VIRTIO_MSI_NO_VECTOR) अणु
		msix_vec = vp_modern_queue_vector(mdev, index, msix_vec);
		अगर (msix_vec == VIRTIO_MSI_NO_VECTOR) अणु
			err = -EBUSY;
			जाओ err_assign_vector;
		पूर्ण
	पूर्ण

	वापस vq;

err_assign_vector:
	अगर (!mdev->notअगरy_base)
		pci_iounmap(mdev->pci_dev, (व्योम __iomem __क्रमce *)vq->priv);
err_map_notअगरy:
	vring_del_virtqueue(vq);
	वापस ERR_PTR(err);
पूर्ण

अटल पूर्णांक vp_modern_find_vqs(काष्ठा virtio_device *vdev, अचिन्हित nvqs,
			      काष्ठा virtqueue *vqs[],
			      vq_callback_t *callbacks[],
			      स्थिर अक्षर * स्थिर names[], स्थिर bool *ctx,
			      काष्ठा irq_affinity *desc)
अणु
	काष्ठा virtio_pci_device *vp_dev = to_vp_device(vdev);
	काष्ठा virtqueue *vq;
	पूर्णांक rc = vp_find_vqs(vdev, nvqs, vqs, callbacks, names, ctx, desc);

	अगर (rc)
		वापस rc;

	/* Select and activate all queues. Has to be करोne last: once we करो
	 * this, there's no way to go back except reset.
	 */
	list_क्रम_each_entry(vq, &vdev->vqs, list)
		vp_modern_set_queue_enable(&vp_dev->mdev, vq->index, true);

	वापस 0;
पूर्ण

अटल व्योम del_vq(काष्ठा virtio_pci_vq_info *info)
अणु
	काष्ठा virtqueue *vq = info->vq;
	काष्ठा virtio_pci_device *vp_dev = to_vp_device(vq->vdev);
	काष्ठा virtio_pci_modern_device *mdev = &vp_dev->mdev;

	अगर (vp_dev->msix_enabled)
		vp_modern_queue_vector(mdev, vq->index,
				       VIRTIO_MSI_NO_VECTOR);

	अगर (!mdev->notअगरy_base)
		pci_iounmap(mdev->pci_dev, (व्योम __क्रमce __iomem *)vq->priv);

	vring_del_virtqueue(vq);
पूर्ण

अटल पूर्णांक virtio_pci_find_shm_cap(काष्ठा pci_dev *dev, u8 required_id,
				   u8 *bar, u64 *offset, u64 *len)
अणु
	पूर्णांक pos;

	क्रम (pos = pci_find_capability(dev, PCI_CAP_ID_VNDR); pos > 0;
	     pos = pci_find_next_capability(dev, pos, PCI_CAP_ID_VNDR)) अणु
		u8 type, cap_len, id;
		u32 पंचांगp32;
		u64 res_offset, res_length;

		pci_पढ़ो_config_byte(dev, pos + दुरत्व(काष्ठा virtio_pci_cap,
							 cfg_type), &type);
		अगर (type != VIRTIO_PCI_CAP_SHARED_MEMORY_CFG)
			जारी;

		pci_पढ़ो_config_byte(dev, pos + दुरत्व(काष्ठा virtio_pci_cap,
							 cap_len), &cap_len);
		अगर (cap_len != माप(काष्ठा virtio_pci_cap64)) अणु
			dev_err(&dev->dev, "%s: shm cap with bad size offset:"
				" %d size: %d\n", __func__, pos, cap_len);
			जारी;
		पूर्ण

		pci_पढ़ो_config_byte(dev, pos + दुरत्व(काष्ठा virtio_pci_cap,
							 id), &id);
		अगर (id != required_id)
			जारी;

		/* Type, and ID match, looks good */
		pci_पढ़ो_config_byte(dev, pos + दुरत्व(काष्ठा virtio_pci_cap,
							 bar), bar);

		/* Read the lower 32bit of length and offset */
		pci_पढ़ो_config_dword(dev, pos + दुरत्व(काष्ठा virtio_pci_cap,
							  offset), &पंचांगp32);
		res_offset = पंचांगp32;
		pci_पढ़ो_config_dword(dev, pos + दुरत्व(काष्ठा virtio_pci_cap,
							  length), &पंचांगp32);
		res_length = पंचांगp32;

		/* and now the top half */
		pci_पढ़ो_config_dword(dev,
				      pos + दुरत्व(काष्ठा virtio_pci_cap64,
						     offset_hi), &पंचांगp32);
		res_offset |= ((u64)पंचांगp32) << 32;
		pci_पढ़ो_config_dword(dev,
				      pos + दुरत्व(काष्ठा virtio_pci_cap64,
						     length_hi), &पंचांगp32);
		res_length |= ((u64)पंचांगp32) << 32;

		*offset = res_offset;
		*len = res_length;

		वापस pos;
	पूर्ण
	वापस 0;
पूर्ण

अटल bool vp_get_shm_region(काष्ठा virtio_device *vdev,
			      काष्ठा virtio_shm_region *region, u8 id)
अणु
	काष्ठा virtio_pci_device *vp_dev = to_vp_device(vdev);
	काष्ठा pci_dev *pci_dev = vp_dev->pci_dev;
	u8 bar;
	u64 offset, len;
	phys_addr_t phys_addr;
	माप_प्रकार bar_len;

	अगर (!virtio_pci_find_shm_cap(pci_dev, id, &bar, &offset, &len))
		वापस false;

	phys_addr = pci_resource_start(pci_dev, bar);
	bar_len = pci_resource_len(pci_dev, bar);

	अगर ((offset + len) < offset) अणु
		dev_err(&pci_dev->dev, "%s: cap offset+len overflow detected\n",
			__func__);
		वापस false;
	पूर्ण

	अगर (offset + len > bar_len) अणु
		dev_err(&pci_dev->dev, "%s: bar shorter than cap offset+len\n",
			__func__);
		वापस false;
	पूर्ण

	region->len = len;
	region->addr = (u64) phys_addr + offset;

	वापस true;
पूर्ण

अटल स्थिर काष्ठा virtio_config_ops virtio_pci_config_nodev_ops = अणु
	.get		= शून्य,
	.set		= शून्य,
	.generation	= vp_generation,
	.get_status	= vp_get_status,
	.set_status	= vp_set_status,
	.reset		= vp_reset,
	.find_vqs	= vp_modern_find_vqs,
	.del_vqs	= vp_del_vqs,
	.get_features	= vp_get_features,
	.finalize_features = vp_finalize_features,
	.bus_name	= vp_bus_name,
	.set_vq_affinity = vp_set_vq_affinity,
	.get_vq_affinity = vp_get_vq_affinity,
	.get_shm_region  = vp_get_shm_region,
पूर्ण;

अटल स्थिर काष्ठा virtio_config_ops virtio_pci_config_ops = अणु
	.get		= vp_get,
	.set		= vp_set,
	.generation	= vp_generation,
	.get_status	= vp_get_status,
	.set_status	= vp_set_status,
	.reset		= vp_reset,
	.find_vqs	= vp_modern_find_vqs,
	.del_vqs	= vp_del_vqs,
	.get_features	= vp_get_features,
	.finalize_features = vp_finalize_features,
	.bus_name	= vp_bus_name,
	.set_vq_affinity = vp_set_vq_affinity,
	.get_vq_affinity = vp_get_vq_affinity,
	.get_shm_region  = vp_get_shm_region,
पूर्ण;

/* the PCI probing function */
पूर्णांक virtio_pci_modern_probe(काष्ठा virtio_pci_device *vp_dev)
अणु
	काष्ठा virtio_pci_modern_device *mdev = &vp_dev->mdev;
	काष्ठा pci_dev *pci_dev = vp_dev->pci_dev;
	पूर्णांक err;

	mdev->pci_dev = pci_dev;

	err = vp_modern_probe(mdev);
	अगर (err)
		वापस err;

	अगर (mdev->device)
		vp_dev->vdev.config = &virtio_pci_config_ops;
	अन्यथा
		vp_dev->vdev.config = &virtio_pci_config_nodev_ops;

	vp_dev->config_vector = vp_config_vector;
	vp_dev->setup_vq = setup_vq;
	vp_dev->del_vq = del_vq;
	vp_dev->isr = mdev->isr;
	vp_dev->vdev.id = mdev->id;

	वापस 0;
पूर्ण

व्योम virtio_pci_modern_हटाओ(काष्ठा virtio_pci_device *vp_dev)
अणु
	काष्ठा virtio_pci_modern_device *mdev = &vp_dev->mdev;

	vp_modern_हटाओ(mdev);
पूर्ण
