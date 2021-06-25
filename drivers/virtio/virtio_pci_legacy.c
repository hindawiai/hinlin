<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Virtio PCI driver - legacy device support
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

#समावेश "virtio_pci_common.h"

/* virtio config->get_features() implementation */
अटल u64 vp_get_features(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtio_pci_device *vp_dev = to_vp_device(vdev);

	/* When someone needs more than 32 feature bits, we'll need to
	 * steal a bit to indicate that the rest are somewhere अन्यथा. */
	वापस ioपढ़ो32(vp_dev->ioaddr + VIRTIO_PCI_HOST_FEATURES);
पूर्ण

/* virtio config->finalize_features() implementation */
अटल पूर्णांक vp_finalize_features(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtio_pci_device *vp_dev = to_vp_device(vdev);

	/* Give virtio_ring a chance to accept features. */
	vring_transport_features(vdev);

	/* Make sure we करोn't have any features > 32 bits! */
	BUG_ON((u32)vdev->features != vdev->features);

	/* We only support 32 feature bits. */
	ioग_लिखो32(vdev->features, vp_dev->ioaddr + VIRTIO_PCI_GUEST_FEATURES);

	वापस 0;
पूर्ण

/* virtio config->get() implementation */
अटल व्योम vp_get(काष्ठा virtio_device *vdev, अचिन्हित offset,
		   व्योम *buf, अचिन्हित len)
अणु
	काष्ठा virtio_pci_device *vp_dev = to_vp_device(vdev);
	व्योम __iomem *ioaddr = vp_dev->ioaddr +
			VIRTIO_PCI_CONFIG_OFF(vp_dev->msix_enabled) +
			offset;
	u8 *ptr = buf;
	पूर्णांक i;

	क्रम (i = 0; i < len; i++)
		ptr[i] = ioपढ़ो8(ioaddr + i);
पूर्ण

/* the config->set() implementation.  it's symmetric to the config->get()
 * implementation */
अटल व्योम vp_set(काष्ठा virtio_device *vdev, अचिन्हित offset,
		   स्थिर व्योम *buf, अचिन्हित len)
अणु
	काष्ठा virtio_pci_device *vp_dev = to_vp_device(vdev);
	व्योम __iomem *ioaddr = vp_dev->ioaddr +
			VIRTIO_PCI_CONFIG_OFF(vp_dev->msix_enabled) +
			offset;
	स्थिर u8 *ptr = buf;
	पूर्णांक i;

	क्रम (i = 0; i < len; i++)
		ioग_लिखो8(ptr[i], ioaddr + i);
पूर्ण

/* config->अणुget,setपूर्ण_status() implementations */
अटल u8 vp_get_status(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtio_pci_device *vp_dev = to_vp_device(vdev);
	वापस ioपढ़ो8(vp_dev->ioaddr + VIRTIO_PCI_STATUS);
पूर्ण

अटल व्योम vp_set_status(काष्ठा virtio_device *vdev, u8 status)
अणु
	काष्ठा virtio_pci_device *vp_dev = to_vp_device(vdev);
	/* We should never be setting status to 0. */
	BUG_ON(status == 0);
	ioग_लिखो8(status, vp_dev->ioaddr + VIRTIO_PCI_STATUS);
पूर्ण

अटल व्योम vp_reset(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtio_pci_device *vp_dev = to_vp_device(vdev);
	/* 0 status means a reset. */
	ioग_लिखो8(0, vp_dev->ioaddr + VIRTIO_PCI_STATUS);
	/* Flush out the status ग_लिखो, and flush in device ग_लिखोs,
	 * including MSi-X पूर्णांकerrupts, अगर any. */
	ioपढ़ो8(vp_dev->ioaddr + VIRTIO_PCI_STATUS);
	/* Flush pending VQ/configuration callbacks. */
	vp_synchronize_vectors(vdev);
पूर्ण

अटल u16 vp_config_vector(काष्ठा virtio_pci_device *vp_dev, u16 vector)
अणु
	/* Setup the vector used क्रम configuration events */
	ioग_लिखो16(vector, vp_dev->ioaddr + VIRTIO_MSI_CONFIG_VECTOR);
	/* Verअगरy we had enough resources to assign the vector */
	/* Will also flush the ग_लिखो out to device */
	वापस ioपढ़ो16(vp_dev->ioaddr + VIRTIO_MSI_CONFIG_VECTOR);
पूर्ण

अटल काष्ठा virtqueue *setup_vq(काष्ठा virtio_pci_device *vp_dev,
				  काष्ठा virtio_pci_vq_info *info,
				  अचिन्हित index,
				  व्योम (*callback)(काष्ठा virtqueue *vq),
				  स्थिर अक्षर *name,
				  bool ctx,
				  u16 msix_vec)
अणु
	काष्ठा virtqueue *vq;
	u16 num;
	पूर्णांक err;
	u64 q_pfn;

	/* Select the queue we're पूर्णांकerested in */
	ioग_लिखो16(index, vp_dev->ioaddr + VIRTIO_PCI_QUEUE_SEL);

	/* Check अगर queue is either not available or alपढ़ोy active. */
	num = ioपढ़ो16(vp_dev->ioaddr + VIRTIO_PCI_QUEUE_NUM);
	अगर (!num || ioपढ़ो32(vp_dev->ioaddr + VIRTIO_PCI_QUEUE_PFN))
		वापस ERR_PTR(-ENOENT);

	info->msix_vector = msix_vec;

	/* create the vring */
	vq = vring_create_virtqueue(index, num,
				    VIRTIO_PCI_VRING_ALIGN, &vp_dev->vdev,
				    true, false, ctx,
				    vp_notअगरy, callback, name);
	अगर (!vq)
		वापस ERR_PTR(-ENOMEM);

	q_pfn = virtqueue_get_desc_addr(vq) >> VIRTIO_PCI_QUEUE_ADDR_SHIFT;
	अगर (q_pfn >> 32) अणु
		dev_err(&vp_dev->pci_dev->dev,
			"platform bug: legacy virtio-mmio must not be used with RAM above 0x%llxGB\n",
			0x1ULL << (32 + PAGE_SHIFT - 30));
		err = -E2BIG;
		जाओ out_del_vq;
	पूर्ण

	/* activate the queue */
	ioग_लिखो32(q_pfn, vp_dev->ioaddr + VIRTIO_PCI_QUEUE_PFN);

	vq->priv = (व्योम __क्रमce *)vp_dev->ioaddr + VIRTIO_PCI_QUEUE_NOTIFY;

	अगर (msix_vec != VIRTIO_MSI_NO_VECTOR) अणु
		ioग_लिखो16(msix_vec, vp_dev->ioaddr + VIRTIO_MSI_QUEUE_VECTOR);
		msix_vec = ioपढ़ो16(vp_dev->ioaddr + VIRTIO_MSI_QUEUE_VECTOR);
		अगर (msix_vec == VIRTIO_MSI_NO_VECTOR) अणु
			err = -EBUSY;
			जाओ out_deactivate;
		पूर्ण
	पूर्ण

	वापस vq;

out_deactivate:
	ioग_लिखो32(0, vp_dev->ioaddr + VIRTIO_PCI_QUEUE_PFN);
out_del_vq:
	vring_del_virtqueue(vq);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम del_vq(काष्ठा virtio_pci_vq_info *info)
अणु
	काष्ठा virtqueue *vq = info->vq;
	काष्ठा virtio_pci_device *vp_dev = to_vp_device(vq->vdev);

	ioग_लिखो16(vq->index, vp_dev->ioaddr + VIRTIO_PCI_QUEUE_SEL);

	अगर (vp_dev->msix_enabled) अणु
		ioग_लिखो16(VIRTIO_MSI_NO_VECTOR,
			  vp_dev->ioaddr + VIRTIO_MSI_QUEUE_VECTOR);
		/* Flush the ग_लिखो out to device */
		ioपढ़ो8(vp_dev->ioaddr + VIRTIO_PCI_ISR);
	पूर्ण

	/* Select and deactivate the queue */
	ioग_लिखो32(0, vp_dev->ioaddr + VIRTIO_PCI_QUEUE_PFN);

	vring_del_virtqueue(vq);
पूर्ण

अटल स्थिर काष्ठा virtio_config_ops virtio_pci_config_ops = अणु
	.get		= vp_get,
	.set		= vp_set,
	.get_status	= vp_get_status,
	.set_status	= vp_set_status,
	.reset		= vp_reset,
	.find_vqs	= vp_find_vqs,
	.del_vqs	= vp_del_vqs,
	.get_features	= vp_get_features,
	.finalize_features = vp_finalize_features,
	.bus_name	= vp_bus_name,
	.set_vq_affinity = vp_set_vq_affinity,
	.get_vq_affinity = vp_get_vq_affinity,
पूर्ण;

/* the PCI probing function */
पूर्णांक virtio_pci_legacy_probe(काष्ठा virtio_pci_device *vp_dev)
अणु
	काष्ठा pci_dev *pci_dev = vp_dev->pci_dev;
	पूर्णांक rc;

	/* We only own devices >= 0x1000 and <= 0x103f: leave the rest. */
	अगर (pci_dev->device < 0x1000 || pci_dev->device > 0x103f)
		वापस -ENODEV;

	अगर (pci_dev->revision != VIRTIO_PCI_ABI_VERSION) अणु
		prपूर्णांकk(KERN_ERR "virtio_pci: expected ABI version %d, got %d\n",
		       VIRTIO_PCI_ABI_VERSION, pci_dev->revision);
		वापस -ENODEV;
	पूर्ण

	rc = dma_set_mask(&pci_dev->dev, DMA_BIT_MASK(64));
	अगर (rc) अणु
		rc = dma_set_mask_and_coherent(&pci_dev->dev, DMA_BIT_MASK(32));
	पूर्ण अन्यथा अणु
		/*
		 * The virtio ring base address is expressed as a 32-bit PFN,
		 * with a page size of 1 << VIRTIO_PCI_QUEUE_ADDR_SHIFT.
		 */
		dma_set_coherent_mask(&pci_dev->dev,
				DMA_BIT_MASK(32 + VIRTIO_PCI_QUEUE_ADDR_SHIFT));
	पूर्ण

	अगर (rc)
		dev_warn(&pci_dev->dev, "Failed to enable 64-bit or 32-bit DMA.  Trying to continue, but this might not work.\n");

	rc = pci_request_region(pci_dev, 0, "virtio-pci-legacy");
	अगर (rc)
		वापस rc;

	rc = -ENOMEM;
	vp_dev->ioaddr = pci_iomap(pci_dev, 0, 0);
	अगर (!vp_dev->ioaddr)
		जाओ err_iomap;

	vp_dev->isr = vp_dev->ioaddr + VIRTIO_PCI_ISR;

	/* we use the subप्रणाली venकरोr/device id as the virtio venकरोr/device
	 * id.  this allows us to use the same PCI venकरोr/device id क्रम all
	 * virtio devices and to identअगरy the particular virtio driver by
	 * the subप्रणाली ids */
	vp_dev->vdev.id.venकरोr = pci_dev->subप्रणाली_venकरोr;
	vp_dev->vdev.id.device = pci_dev->subप्रणाली_device;

	vp_dev->vdev.config = &virtio_pci_config_ops;

	vp_dev->config_vector = vp_config_vector;
	vp_dev->setup_vq = setup_vq;
	vp_dev->del_vq = del_vq;

	वापस 0;

err_iomap:
	pci_release_region(pci_dev, 0);
	वापस rc;
पूर्ण

व्योम virtio_pci_legacy_हटाओ(काष्ठा virtio_pci_device *vp_dev)
अणु
	काष्ठा pci_dev *pci_dev = vp_dev->pci_dev;

	pci_iounmap(pci_dev, vp_dev->ioaddr);
	pci_release_region(pci_dev, 0);
पूर्ण
