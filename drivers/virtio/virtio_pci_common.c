<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Virtio PCI driver - common functionality क्रम all device versions
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

अटल bool क्रमce_legacy = false;

#अगर IS_ENABLED(CONFIG_VIRTIO_PCI_LEGACY)
module_param(क्रमce_legacy, bool, 0444);
MODULE_PARM_DESC(क्रमce_legacy,
		 "Force legacy mode for transitional virtio 1 devices");
#पूर्ण_अगर

/* रुको क्रम pending irq handlers */
व्योम vp_synchronize_vectors(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtio_pci_device *vp_dev = to_vp_device(vdev);
	पूर्णांक i;

	अगर (vp_dev->पूर्णांकx_enabled)
		synchronize_irq(vp_dev->pci_dev->irq);

	क्रम (i = 0; i < vp_dev->msix_vectors; ++i)
		synchronize_irq(pci_irq_vector(vp_dev->pci_dev, i));
पूर्ण

/* the notअगरy function used when creating a virt queue */
bool vp_notअगरy(काष्ठा virtqueue *vq)
अणु
	/* we ग_लिखो the queue's selector पूर्णांकo the notअगरication रेजिस्टर to
	 * संकेत the other end */
	ioग_लिखो16(vq->index, (व्योम __iomem *)vq->priv);
	वापस true;
पूर्ण

/* Handle a configuration change: Tell driver अगर it wants to know. */
अटल irqवापस_t vp_config_changed(पूर्णांक irq, व्योम *opaque)
अणु
	काष्ठा virtio_pci_device *vp_dev = opaque;

	virtio_config_changed(&vp_dev->vdev);
	वापस IRQ_HANDLED;
पूर्ण

/* Notअगरy all virtqueues on an पूर्णांकerrupt. */
अटल irqवापस_t vp_vring_पूर्णांकerrupt(पूर्णांक irq, व्योम *opaque)
अणु
	काष्ठा virtio_pci_device *vp_dev = opaque;
	काष्ठा virtio_pci_vq_info *info;
	irqवापस_t ret = IRQ_NONE;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&vp_dev->lock, flags);
	list_क्रम_each_entry(info, &vp_dev->virtqueues, node) अणु
		अगर (vring_पूर्णांकerrupt(irq, info->vq) == IRQ_HANDLED)
			ret = IRQ_HANDLED;
	पूर्ण
	spin_unlock_irqrestore(&vp_dev->lock, flags);

	वापस ret;
पूर्ण

/* A small wrapper to also acknowledge the पूर्णांकerrupt when it's handled.
 * I really need an EIO hook क्रम the vring so I can ack the पूर्णांकerrupt once we
 * know that we'll be handling the IRQ but beक्रमe we invoke the callback since
 * the callback may notअगरy the host which results in the host attempting to
 * उठाओ an पूर्णांकerrupt that we would then mask once we acknowledged the
 * पूर्णांकerrupt. */
अटल irqवापस_t vp_पूर्णांकerrupt(पूर्णांक irq, व्योम *opaque)
अणु
	काष्ठा virtio_pci_device *vp_dev = opaque;
	u8 isr;

	/* पढ़ोing the ISR has the effect of also clearing it so it's very
	 * important to save off the value. */
	isr = ioपढ़ो8(vp_dev->isr);

	/* It's definitely not us अगर the ISR was not high */
	अगर (!isr)
		वापस IRQ_NONE;

	/* Configuration change?  Tell driver अगर it wants to know. */
	अगर (isr & VIRTIO_PCI_ISR_CONFIG)
		vp_config_changed(irq, opaque);

	वापस vp_vring_पूर्णांकerrupt(irq, opaque);
पूर्ण

अटल पूर्णांक vp_request_msix_vectors(काष्ठा virtio_device *vdev, पूर्णांक nvectors,
				   bool per_vq_vectors, काष्ठा irq_affinity *desc)
अणु
	काष्ठा virtio_pci_device *vp_dev = to_vp_device(vdev);
	स्थिर अक्षर *name = dev_name(&vp_dev->vdev.dev);
	अचिन्हित flags = PCI_IRQ_MSIX;
	अचिन्हित i, v;
	पूर्णांक err = -ENOMEM;

	vp_dev->msix_vectors = nvectors;

	vp_dev->msix_names = kदो_स्मृति_array(nvectors,
					   माप(*vp_dev->msix_names),
					   GFP_KERNEL);
	अगर (!vp_dev->msix_names)
		जाओ error;
	vp_dev->msix_affinity_masks
		= kसुस्मृति(nvectors, माप(*vp_dev->msix_affinity_masks),
			  GFP_KERNEL);
	अगर (!vp_dev->msix_affinity_masks)
		जाओ error;
	क्रम (i = 0; i < nvectors; ++i)
		अगर (!alloc_cpumask_var(&vp_dev->msix_affinity_masks[i],
					GFP_KERNEL))
			जाओ error;

	अगर (desc) अणु
		flags |= PCI_IRQ_AFFINITY;
		desc->pre_vectors++; /* virtio config vector */
	पूर्ण

	err = pci_alloc_irq_vectors_affinity(vp_dev->pci_dev, nvectors,
					     nvectors, flags, desc);
	अगर (err < 0)
		जाओ error;
	vp_dev->msix_enabled = 1;

	/* Set the vector used क्रम configuration */
	v = vp_dev->msix_used_vectors;
	snम_लिखो(vp_dev->msix_names[v], माप *vp_dev->msix_names,
		 "%s-config", name);
	err = request_irq(pci_irq_vector(vp_dev->pci_dev, v),
			  vp_config_changed, 0, vp_dev->msix_names[v],
			  vp_dev);
	अगर (err)
		जाओ error;
	++vp_dev->msix_used_vectors;

	v = vp_dev->config_vector(vp_dev, v);
	/* Verअगरy we had enough resources to assign the vector */
	अगर (v == VIRTIO_MSI_NO_VECTOR) अणु
		err = -EBUSY;
		जाओ error;
	पूर्ण

	अगर (!per_vq_vectors) अणु
		/* Shared vector क्रम all VQs */
		v = vp_dev->msix_used_vectors;
		snम_लिखो(vp_dev->msix_names[v], माप *vp_dev->msix_names,
			 "%s-virtqueues", name);
		err = request_irq(pci_irq_vector(vp_dev->pci_dev, v),
				  vp_vring_पूर्णांकerrupt, 0, vp_dev->msix_names[v],
				  vp_dev);
		अगर (err)
			जाओ error;
		++vp_dev->msix_used_vectors;
	पूर्ण
	वापस 0;
error:
	वापस err;
पूर्ण

अटल काष्ठा virtqueue *vp_setup_vq(काष्ठा virtio_device *vdev, अचिन्हित index,
				     व्योम (*callback)(काष्ठा virtqueue *vq),
				     स्थिर अक्षर *name,
				     bool ctx,
				     u16 msix_vec)
अणु
	काष्ठा virtio_pci_device *vp_dev = to_vp_device(vdev);
	काष्ठा virtio_pci_vq_info *info = kदो_स्मृति(माप *info, GFP_KERNEL);
	काष्ठा virtqueue *vq;
	अचिन्हित दीर्घ flags;

	/* fill out our काष्ठाure that represents an active queue */
	अगर (!info)
		वापस ERR_PTR(-ENOMEM);

	vq = vp_dev->setup_vq(vp_dev, info, index, callback, name, ctx,
			      msix_vec);
	अगर (IS_ERR(vq))
		जाओ out_info;

	info->vq = vq;
	अगर (callback) अणु
		spin_lock_irqsave(&vp_dev->lock, flags);
		list_add(&info->node, &vp_dev->virtqueues);
		spin_unlock_irqrestore(&vp_dev->lock, flags);
	पूर्ण अन्यथा अणु
		INIT_LIST_HEAD(&info->node);
	पूर्ण

	vp_dev->vqs[index] = info;
	वापस vq;

out_info:
	kमुक्त(info);
	वापस vq;
पूर्ण

अटल व्योम vp_del_vq(काष्ठा virtqueue *vq)
अणु
	काष्ठा virtio_pci_device *vp_dev = to_vp_device(vq->vdev);
	काष्ठा virtio_pci_vq_info *info = vp_dev->vqs[vq->index];
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&vp_dev->lock, flags);
	list_del(&info->node);
	spin_unlock_irqrestore(&vp_dev->lock, flags);

	vp_dev->del_vq(info);
	kमुक्त(info);
पूर्ण

/* the config->del_vqs() implementation */
व्योम vp_del_vqs(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtio_pci_device *vp_dev = to_vp_device(vdev);
	काष्ठा virtqueue *vq, *n;
	पूर्णांक i;

	list_क्रम_each_entry_safe(vq, n, &vdev->vqs, list) अणु
		अगर (vp_dev->per_vq_vectors) अणु
			पूर्णांक v = vp_dev->vqs[vq->index]->msix_vector;

			अगर (v != VIRTIO_MSI_NO_VECTOR) अणु
				पूर्णांक irq = pci_irq_vector(vp_dev->pci_dev, v);

				irq_set_affinity_hपूर्णांक(irq, शून्य);
				मुक्त_irq(irq, vq);
			पूर्ण
		पूर्ण
		vp_del_vq(vq);
	पूर्ण
	vp_dev->per_vq_vectors = false;

	अगर (vp_dev->पूर्णांकx_enabled) अणु
		मुक्त_irq(vp_dev->pci_dev->irq, vp_dev);
		vp_dev->पूर्णांकx_enabled = 0;
	पूर्ण

	क्रम (i = 0; i < vp_dev->msix_used_vectors; ++i)
		मुक्त_irq(pci_irq_vector(vp_dev->pci_dev, i), vp_dev);

	अगर (vp_dev->msix_affinity_masks) अणु
		क्रम (i = 0; i < vp_dev->msix_vectors; i++)
			अगर (vp_dev->msix_affinity_masks[i])
				मुक्त_cpumask_var(vp_dev->msix_affinity_masks[i]);
	पूर्ण

	अगर (vp_dev->msix_enabled) अणु
		/* Disable the vector used क्रम configuration */
		vp_dev->config_vector(vp_dev, VIRTIO_MSI_NO_VECTOR);

		pci_मुक्त_irq_vectors(vp_dev->pci_dev);
		vp_dev->msix_enabled = 0;
	पूर्ण

	vp_dev->msix_vectors = 0;
	vp_dev->msix_used_vectors = 0;
	kमुक्त(vp_dev->msix_names);
	vp_dev->msix_names = शून्य;
	kमुक्त(vp_dev->msix_affinity_masks);
	vp_dev->msix_affinity_masks = शून्य;
	kमुक्त(vp_dev->vqs);
	vp_dev->vqs = शून्य;
पूर्ण

अटल पूर्णांक vp_find_vqs_msix(काष्ठा virtio_device *vdev, अचिन्हित nvqs,
		काष्ठा virtqueue *vqs[], vq_callback_t *callbacks[],
		स्थिर अक्षर * स्थिर names[], bool per_vq_vectors,
		स्थिर bool *ctx,
		काष्ठा irq_affinity *desc)
अणु
	काष्ठा virtio_pci_device *vp_dev = to_vp_device(vdev);
	u16 msix_vec;
	पूर्णांक i, err, nvectors, allocated_vectors, queue_idx = 0;

	vp_dev->vqs = kसुस्मृति(nvqs, माप(*vp_dev->vqs), GFP_KERNEL);
	अगर (!vp_dev->vqs)
		वापस -ENOMEM;

	अगर (per_vq_vectors) अणु
		/* Best option: one क्रम change पूर्णांकerrupt, one per vq. */
		nvectors = 1;
		क्रम (i = 0; i < nvqs; ++i)
			अगर (names[i] && callbacks[i])
				++nvectors;
	पूर्ण अन्यथा अणु
		/* Second best: one क्रम change, shared क्रम all vqs. */
		nvectors = 2;
	पूर्ण

	err = vp_request_msix_vectors(vdev, nvectors, per_vq_vectors,
				      per_vq_vectors ? desc : शून्य);
	अगर (err)
		जाओ error_find;

	vp_dev->per_vq_vectors = per_vq_vectors;
	allocated_vectors = vp_dev->msix_used_vectors;
	क्रम (i = 0; i < nvqs; ++i) अणु
		अगर (!names[i]) अणु
			vqs[i] = शून्य;
			जारी;
		पूर्ण

		अगर (!callbacks[i])
			msix_vec = VIRTIO_MSI_NO_VECTOR;
		अन्यथा अगर (vp_dev->per_vq_vectors)
			msix_vec = allocated_vectors++;
		अन्यथा
			msix_vec = VP_MSIX_VQ_VECTOR;
		vqs[i] = vp_setup_vq(vdev, queue_idx++, callbacks[i], names[i],
				     ctx ? ctx[i] : false,
				     msix_vec);
		अगर (IS_ERR(vqs[i])) अणु
			err = PTR_ERR(vqs[i]);
			जाओ error_find;
		पूर्ण

		अगर (!vp_dev->per_vq_vectors || msix_vec == VIRTIO_MSI_NO_VECTOR)
			जारी;

		/* allocate per-vq irq अगर available and necessary */
		snम_लिखो(vp_dev->msix_names[msix_vec],
			 माप *vp_dev->msix_names,
			 "%s-%s",
			 dev_name(&vp_dev->vdev.dev), names[i]);
		err = request_irq(pci_irq_vector(vp_dev->pci_dev, msix_vec),
				  vring_पूर्णांकerrupt, 0,
				  vp_dev->msix_names[msix_vec],
				  vqs[i]);
		अगर (err)
			जाओ error_find;
	पूर्ण
	वापस 0;

error_find:
	vp_del_vqs(vdev);
	वापस err;
पूर्ण

अटल पूर्णांक vp_find_vqs_पूर्णांकx(काष्ठा virtio_device *vdev, अचिन्हित nvqs,
		काष्ठा virtqueue *vqs[], vq_callback_t *callbacks[],
		स्थिर अक्षर * स्थिर names[], स्थिर bool *ctx)
अणु
	काष्ठा virtio_pci_device *vp_dev = to_vp_device(vdev);
	पूर्णांक i, err, queue_idx = 0;

	vp_dev->vqs = kसुस्मृति(nvqs, माप(*vp_dev->vqs), GFP_KERNEL);
	अगर (!vp_dev->vqs)
		वापस -ENOMEM;

	err = request_irq(vp_dev->pci_dev->irq, vp_पूर्णांकerrupt, IRQF_SHARED,
			dev_name(&vdev->dev), vp_dev);
	अगर (err)
		जाओ out_del_vqs;

	vp_dev->पूर्णांकx_enabled = 1;
	vp_dev->per_vq_vectors = false;
	क्रम (i = 0; i < nvqs; ++i) अणु
		अगर (!names[i]) अणु
			vqs[i] = शून्य;
			जारी;
		पूर्ण
		vqs[i] = vp_setup_vq(vdev, queue_idx++, callbacks[i], names[i],
				     ctx ? ctx[i] : false,
				     VIRTIO_MSI_NO_VECTOR);
		अगर (IS_ERR(vqs[i])) अणु
			err = PTR_ERR(vqs[i]);
			जाओ out_del_vqs;
		पूर्ण
	पूर्ण

	वापस 0;
out_del_vqs:
	vp_del_vqs(vdev);
	वापस err;
पूर्ण

/* the config->find_vqs() implementation */
पूर्णांक vp_find_vqs(काष्ठा virtio_device *vdev, अचिन्हित nvqs,
		काष्ठा virtqueue *vqs[], vq_callback_t *callbacks[],
		स्थिर अक्षर * स्थिर names[], स्थिर bool *ctx,
		काष्ठा irq_affinity *desc)
अणु
	पूर्णांक err;

	/* Try MSI-X with one vector per queue. */
	err = vp_find_vqs_msix(vdev, nvqs, vqs, callbacks, names, true, ctx, desc);
	अगर (!err)
		वापस 0;
	/* Fallback: MSI-X with one vector क्रम config, one shared क्रम queues. */
	err = vp_find_vqs_msix(vdev, nvqs, vqs, callbacks, names, false, ctx, desc);
	अगर (!err)
		वापस 0;
	/* Finally fall back to regular पूर्णांकerrupts. */
	वापस vp_find_vqs_पूर्णांकx(vdev, nvqs, vqs, callbacks, names, ctx);
पूर्ण

स्थिर अक्षर *vp_bus_name(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtio_pci_device *vp_dev = to_vp_device(vdev);

	वापस pci_name(vp_dev->pci_dev);
पूर्ण

/* Setup the affinity क्रम a virtqueue:
 * - क्रमce the affinity क्रम per vq vector
 * - OR over all affinities क्रम shared MSI
 * - ignore the affinity request अगर we're using INTX
 */
पूर्णांक vp_set_vq_affinity(काष्ठा virtqueue *vq, स्थिर काष्ठा cpumask *cpu_mask)
अणु
	काष्ठा virtio_device *vdev = vq->vdev;
	काष्ठा virtio_pci_device *vp_dev = to_vp_device(vdev);
	काष्ठा virtio_pci_vq_info *info = vp_dev->vqs[vq->index];
	काष्ठा cpumask *mask;
	अचिन्हित पूर्णांक irq;

	अगर (!vq->callback)
		वापस -EINVAL;

	अगर (vp_dev->msix_enabled) अणु
		mask = vp_dev->msix_affinity_masks[info->msix_vector];
		irq = pci_irq_vector(vp_dev->pci_dev, info->msix_vector);
		अगर (!cpu_mask)
			irq_set_affinity_hपूर्णांक(irq, शून्य);
		अन्यथा अणु
			cpumask_copy(mask, cpu_mask);
			irq_set_affinity_hपूर्णांक(irq, mask);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

स्थिर काष्ठा cpumask *vp_get_vq_affinity(काष्ठा virtio_device *vdev, पूर्णांक index)
अणु
	काष्ठा virtio_pci_device *vp_dev = to_vp_device(vdev);

	अगर (!vp_dev->per_vq_vectors ||
	    vp_dev->vqs[index]->msix_vector == VIRTIO_MSI_NO_VECTOR)
		वापस शून्य;

	वापस pci_irq_get_affinity(vp_dev->pci_dev,
				    vp_dev->vqs[index]->msix_vector);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक virtio_pci_मुक्तze(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pci_dev = to_pci_dev(dev);
	काष्ठा virtio_pci_device *vp_dev = pci_get_drvdata(pci_dev);
	पूर्णांक ret;

	ret = virtio_device_मुक्तze(&vp_dev->vdev);

	अगर (!ret)
		pci_disable_device(pci_dev);
	वापस ret;
पूर्ण

अटल पूर्णांक virtio_pci_restore(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pci_dev = to_pci_dev(dev);
	काष्ठा virtio_pci_device *vp_dev = pci_get_drvdata(pci_dev);
	पूर्णांक ret;

	ret = pci_enable_device(pci_dev);
	अगर (ret)
		वापस ret;

	pci_set_master(pci_dev);
	वापस virtio_device_restore(&vp_dev->vdev);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops virtio_pci_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(virtio_pci_मुक्तze, virtio_pci_restore)
पूर्ण;
#पूर्ण_अगर


/* Qumranet करोnated their venकरोr ID क्रम devices 0x1000 thru 0x10FF. */
अटल स्थिर काष्ठा pci_device_id virtio_pci_id_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_REDHAT_QUMRANET, PCI_ANY_ID) पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, virtio_pci_id_table);

अटल व्योम virtio_pci_release_dev(काष्ठा device *_d)
अणु
	काष्ठा virtio_device *vdev = dev_to_virtio(_d);
	काष्ठा virtio_pci_device *vp_dev = to_vp_device(vdev);

	/* As काष्ठा device is a kobject, it's not safe to
	 * मुक्त the memory (including the reference counter itself)
	 * until it's release callback. */
	kमुक्त(vp_dev);
पूर्ण

अटल पूर्णांक virtio_pci_probe(काष्ठा pci_dev *pci_dev,
			    स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा virtio_pci_device *vp_dev, *reg_dev = शून्य;
	पूर्णांक rc;

	/* allocate our काष्ठाure and fill it out */
	vp_dev = kzalloc(माप(काष्ठा virtio_pci_device), GFP_KERNEL);
	अगर (!vp_dev)
		वापस -ENOMEM;

	pci_set_drvdata(pci_dev, vp_dev);
	vp_dev->vdev.dev.parent = &pci_dev->dev;
	vp_dev->vdev.dev.release = virtio_pci_release_dev;
	vp_dev->pci_dev = pci_dev;
	INIT_LIST_HEAD(&vp_dev->virtqueues);
	spin_lock_init(&vp_dev->lock);

	/* enable the device */
	rc = pci_enable_device(pci_dev);
	अगर (rc)
		जाओ err_enable_device;

	अगर (क्रमce_legacy) अणु
		rc = virtio_pci_legacy_probe(vp_dev);
		/* Also try modern mode अगर we can't map BAR0 (no IO space). */
		अगर (rc == -ENODEV || rc == -ENOMEM)
			rc = virtio_pci_modern_probe(vp_dev);
		अगर (rc)
			जाओ err_probe;
	पूर्ण अन्यथा अणु
		rc = virtio_pci_modern_probe(vp_dev);
		अगर (rc == -ENODEV)
			rc = virtio_pci_legacy_probe(vp_dev);
		अगर (rc)
			जाओ err_probe;
	पूर्ण

	pci_set_master(pci_dev);

	rc = रेजिस्टर_virtio_device(&vp_dev->vdev);
	reg_dev = vp_dev;
	अगर (rc)
		जाओ err_रेजिस्टर;

	वापस 0;

err_रेजिस्टर:
	अगर (vp_dev->ioaddr)
	     virtio_pci_legacy_हटाओ(vp_dev);
	अन्यथा
	     virtio_pci_modern_हटाओ(vp_dev);
err_probe:
	pci_disable_device(pci_dev);
err_enable_device:
	अगर (reg_dev)
		put_device(&vp_dev->vdev.dev);
	अन्यथा
		kमुक्त(vp_dev);
	वापस rc;
पूर्ण

अटल व्योम virtio_pci_हटाओ(काष्ठा pci_dev *pci_dev)
अणु
	काष्ठा virtio_pci_device *vp_dev = pci_get_drvdata(pci_dev);
	काष्ठा device *dev = get_device(&vp_dev->vdev.dev);

	pci_disable_sriov(pci_dev);

	unरेजिस्टर_virtio_device(&vp_dev->vdev);

	अगर (vp_dev->ioaddr)
		virtio_pci_legacy_हटाओ(vp_dev);
	अन्यथा
		virtio_pci_modern_हटाओ(vp_dev);

	pci_disable_device(pci_dev);
	put_device(dev);
पूर्ण

अटल पूर्णांक virtio_pci_sriov_configure(काष्ठा pci_dev *pci_dev, पूर्णांक num_vfs)
अणु
	काष्ठा virtio_pci_device *vp_dev = pci_get_drvdata(pci_dev);
	काष्ठा virtio_device *vdev = &vp_dev->vdev;
	पूर्णांक ret;

	अगर (!(vdev->config->get_status(vdev) & VIRTIO_CONFIG_S_DRIVER_OK))
		वापस -EBUSY;

	अगर (!__virtio_test_bit(vdev, VIRTIO_F_SR_IOV))
		वापस -EINVAL;

	अगर (pci_vfs_asचिन्हित(pci_dev))
		वापस -EPERM;

	अगर (num_vfs == 0) अणु
		pci_disable_sriov(pci_dev);
		वापस 0;
	पूर्ण

	ret = pci_enable_sriov(pci_dev, num_vfs);
	अगर (ret < 0)
		वापस ret;

	वापस num_vfs;
पूर्ण

अटल काष्ठा pci_driver virtio_pci_driver = अणु
	.name		= "virtio-pci",
	.id_table	= virtio_pci_id_table,
	.probe		= virtio_pci_probe,
	.हटाओ		= virtio_pci_हटाओ,
#अगर_घोषित CONFIG_PM_SLEEP
	.driver.pm	= &virtio_pci_pm_ops,
#पूर्ण_अगर
	.sriov_configure = virtio_pci_sriov_configure,
पूर्ण;

module_pci_driver(virtio_pci_driver);

MODULE_AUTHOR("Anthony Liguori <aliguori@us.ibm.com>");
MODULE_DESCRIPTION("virtio-pci");
MODULE_LICENSE("GPL");
MODULE_VERSION("1");
