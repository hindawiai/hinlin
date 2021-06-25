<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * vDPA bridge driver क्रम modern virtio-pci device
 *
 * Copyright (c) 2020, Red Hat Inc. All rights reserved.
 * Author: Jason Wang <jasowang@redhat.com>
 *
 * Based on virtio_pci_modern.c.
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/vdpa.h>
#समावेश <linux/virtपन.स>
#समावेश <linux/virtio_config.h>
#समावेश <linux/virtio_ring.h>
#समावेश <linux/virtio_pci.h>
#समावेश <linux/virtio_pci_modern.h>

#घोषणा VP_VDPA_QUEUE_MAX 256
#घोषणा VP_VDPA_DRIVER_NAME "vp_vdpa"
#घोषणा VP_VDPA_NAME_SIZE 256

काष्ठा vp_vring अणु
	व्योम __iomem *notअगरy;
	अक्षर msix_name[VP_VDPA_NAME_SIZE];
	काष्ठा vdpa_callback cb;
	resource_माप_प्रकार notअगरy_pa;
	पूर्णांक irq;
पूर्ण;

काष्ठा vp_vdpa अणु
	काष्ठा vdpa_device vdpa;
	काष्ठा virtio_pci_modern_device mdev;
	काष्ठा vp_vring *vring;
	काष्ठा vdpa_callback config_cb;
	अक्षर msix_name[VP_VDPA_NAME_SIZE];
	पूर्णांक config_irq;
	पूर्णांक queues;
	पूर्णांक vectors;
पूर्ण;

अटल काष्ठा vp_vdpa *vdpa_to_vp(काष्ठा vdpa_device *vdpa)
अणु
	वापस container_of(vdpa, काष्ठा vp_vdpa, vdpa);
पूर्ण

अटल काष्ठा virtio_pci_modern_device *vdpa_to_mdev(काष्ठा vdpa_device *vdpa)
अणु
	काष्ठा vp_vdpa *vp_vdpa = vdpa_to_vp(vdpa);

	वापस &vp_vdpa->mdev;
पूर्ण

अटल u64 vp_vdpa_get_features(काष्ठा vdpa_device *vdpa)
अणु
	काष्ठा virtio_pci_modern_device *mdev = vdpa_to_mdev(vdpa);

	वापस vp_modern_get_features(mdev);
पूर्ण

अटल पूर्णांक vp_vdpa_set_features(काष्ठा vdpa_device *vdpa, u64 features)
अणु
	काष्ठा virtio_pci_modern_device *mdev = vdpa_to_mdev(vdpa);

	vp_modern_set_features(mdev, features);

	वापस 0;
पूर्ण

अटल u8 vp_vdpa_get_status(काष्ठा vdpa_device *vdpa)
अणु
	काष्ठा virtio_pci_modern_device *mdev = vdpa_to_mdev(vdpa);

	वापस vp_modern_get_status(mdev);
पूर्ण

अटल व्योम vp_vdpa_मुक्त_irq(काष्ठा vp_vdpa *vp_vdpa)
अणु
	काष्ठा virtio_pci_modern_device *mdev = &vp_vdpa->mdev;
	काष्ठा pci_dev *pdev = mdev->pci_dev;
	पूर्णांक i;

	क्रम (i = 0; i < vp_vdpa->queues; i++) अणु
		अगर (vp_vdpa->vring[i].irq != VIRTIO_MSI_NO_VECTOR) अणु
			vp_modern_queue_vector(mdev, i, VIRTIO_MSI_NO_VECTOR);
			devm_मुक्त_irq(&pdev->dev, vp_vdpa->vring[i].irq,
				      &vp_vdpa->vring[i]);
			vp_vdpa->vring[i].irq = VIRTIO_MSI_NO_VECTOR;
		पूर्ण
	पूर्ण

	अगर (vp_vdpa->config_irq != VIRTIO_MSI_NO_VECTOR) अणु
		vp_modern_config_vector(mdev, VIRTIO_MSI_NO_VECTOR);
		devm_मुक्त_irq(&pdev->dev, vp_vdpa->config_irq, vp_vdpa);
		vp_vdpa->config_irq = VIRTIO_MSI_NO_VECTOR;
	पूर्ण

	अगर (vp_vdpa->vectors) अणु
		pci_मुक्त_irq_vectors(pdev);
		vp_vdpa->vectors = 0;
	पूर्ण
पूर्ण

अटल irqवापस_t vp_vdpa_vq_handler(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा vp_vring *vring = arg;

	अगर (vring->cb.callback)
		वापस vring->cb.callback(vring->cb.निजी);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t vp_vdpa_config_handler(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा vp_vdpa *vp_vdpa = arg;

	अगर (vp_vdpa->config_cb.callback)
		वापस vp_vdpa->config_cb.callback(vp_vdpa->config_cb.निजी);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक vp_vdpa_request_irq(काष्ठा vp_vdpa *vp_vdpa)
अणु
	काष्ठा virtio_pci_modern_device *mdev = &vp_vdpa->mdev;
	काष्ठा pci_dev *pdev = mdev->pci_dev;
	पूर्णांक i, ret, irq;
	पूर्णांक queues = vp_vdpa->queues;
	पूर्णांक vectors = queues + 1;

	ret = pci_alloc_irq_vectors(pdev, vectors, vectors, PCI_IRQ_MSIX);
	अगर (ret != vectors) अणु
		dev_err(&pdev->dev,
			"vp_vdpa: fail to allocate irq vectors want %d but %d\n",
			vectors, ret);
		वापस ret;
	पूर्ण

	vp_vdpa->vectors = vectors;

	क्रम (i = 0; i < queues; i++) अणु
		snम_लिखो(vp_vdpa->vring[i].msix_name, VP_VDPA_NAME_SIZE,
			"vp-vdpa[%s]-%d\n", pci_name(pdev), i);
		irq = pci_irq_vector(pdev, i);
		ret = devm_request_irq(&pdev->dev, irq,
				       vp_vdpa_vq_handler,
				       0, vp_vdpa->vring[i].msix_name,
				       &vp_vdpa->vring[i]);
		अगर (ret) अणु
			dev_err(&pdev->dev,
				"vp_vdpa: fail to request irq for vq %d\n", i);
			जाओ err;
		पूर्ण
		vp_modern_queue_vector(mdev, i, i);
		vp_vdpa->vring[i].irq = irq;
	पूर्ण

	snम_लिखो(vp_vdpa->msix_name, VP_VDPA_NAME_SIZE, "vp-vdpa[%s]-config\n",
		 pci_name(pdev));
	irq = pci_irq_vector(pdev, queues);
	ret = devm_request_irq(&pdev->dev, irq,	vp_vdpa_config_handler, 0,
			       vp_vdpa->msix_name, vp_vdpa);
	अगर (ret) अणु
		dev_err(&pdev->dev,
			"vp_vdpa: fail to request irq for vq %d\n", i);
			जाओ err;
	पूर्ण
	vp_modern_config_vector(mdev, queues);
	vp_vdpa->config_irq = irq;

	वापस 0;
err:
	vp_vdpa_मुक्त_irq(vp_vdpa);
	वापस ret;
पूर्ण

अटल व्योम vp_vdpa_set_status(काष्ठा vdpa_device *vdpa, u8 status)
अणु
	काष्ठा vp_vdpa *vp_vdpa = vdpa_to_vp(vdpa);
	काष्ठा virtio_pci_modern_device *mdev = &vp_vdpa->mdev;
	u8 s = vp_vdpa_get_status(vdpa);

	अगर (status & VIRTIO_CONFIG_S_DRIVER_OK &&
	    !(s & VIRTIO_CONFIG_S_DRIVER_OK)) अणु
		vp_vdpa_request_irq(vp_vdpa);
	पूर्ण

	vp_modern_set_status(mdev, status);

	अगर (!(status & VIRTIO_CONFIG_S_DRIVER_OK) &&
	    (s & VIRTIO_CONFIG_S_DRIVER_OK))
		vp_vdpa_मुक्त_irq(vp_vdpa);
पूर्ण

अटल u16 vp_vdpa_get_vq_num_max(काष्ठा vdpa_device *vdpa)
अणु
	वापस VP_VDPA_QUEUE_MAX;
पूर्ण

अटल पूर्णांक vp_vdpa_get_vq_state(काष्ठा vdpa_device *vdpa, u16 qid,
				काष्ठा vdpa_vq_state *state)
अणु
	/* Note that this is not supported by virtio specअगरication, so
	 * we वापस -EOPNOTSUPP here. This means we can't support live
	 * migration, vhost device start/stop.
	 */
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक vp_vdpa_set_vq_state(काष्ठा vdpa_device *vdpa, u16 qid,
				स्थिर काष्ठा vdpa_vq_state *state)
अणु
	/* Note that this is not supported by virtio specअगरication, so
	 * we वापस -ENOPOTSUPP here. This means we can't support live
	 * migration, vhost device start/stop.
	 */
	वापस -EOPNOTSUPP;
पूर्ण

अटल व्योम vp_vdpa_set_vq_cb(काष्ठा vdpa_device *vdpa, u16 qid,
			      काष्ठा vdpa_callback *cb)
अणु
	काष्ठा vp_vdpa *vp_vdpa = vdpa_to_vp(vdpa);

	vp_vdpa->vring[qid].cb = *cb;
पूर्ण

अटल व्योम vp_vdpa_set_vq_पढ़ोy(काष्ठा vdpa_device *vdpa,
				 u16 qid, bool पढ़ोy)
अणु
	काष्ठा virtio_pci_modern_device *mdev = vdpa_to_mdev(vdpa);

	vp_modern_set_queue_enable(mdev, qid, पढ़ोy);
पूर्ण

अटल bool vp_vdpa_get_vq_पढ़ोy(काष्ठा vdpa_device *vdpa, u16 qid)
अणु
	काष्ठा virtio_pci_modern_device *mdev = vdpa_to_mdev(vdpa);

	वापस vp_modern_get_queue_enable(mdev, qid);
पूर्ण

अटल व्योम vp_vdpa_set_vq_num(काष्ठा vdpa_device *vdpa, u16 qid,
			       u32 num)
अणु
	काष्ठा virtio_pci_modern_device *mdev = vdpa_to_mdev(vdpa);

	vp_modern_set_queue_size(mdev, qid, num);
पूर्ण

अटल पूर्णांक vp_vdpa_set_vq_address(काष्ठा vdpa_device *vdpa, u16 qid,
				  u64 desc_area, u64 driver_area,
				  u64 device_area)
अणु
	काष्ठा virtio_pci_modern_device *mdev = vdpa_to_mdev(vdpa);

	vp_modern_queue_address(mdev, qid, desc_area,
				driver_area, device_area);

	वापस 0;
पूर्ण

अटल व्योम vp_vdpa_kick_vq(काष्ठा vdpa_device *vdpa, u16 qid)
अणु
	काष्ठा vp_vdpa *vp_vdpa = vdpa_to_vp(vdpa);

	vp_ioग_लिखो16(qid, vp_vdpa->vring[qid].notअगरy);
पूर्ण

अटल u32 vp_vdpa_get_generation(काष्ठा vdpa_device *vdpa)
अणु
	काष्ठा virtio_pci_modern_device *mdev = vdpa_to_mdev(vdpa);

	वापस vp_modern_generation(mdev);
पूर्ण

अटल u32 vp_vdpa_get_device_id(काष्ठा vdpa_device *vdpa)
अणु
	काष्ठा virtio_pci_modern_device *mdev = vdpa_to_mdev(vdpa);

	वापस mdev->id.device;
पूर्ण

अटल u32 vp_vdpa_get_venकरोr_id(काष्ठा vdpa_device *vdpa)
अणु
	काष्ठा virtio_pci_modern_device *mdev = vdpa_to_mdev(vdpa);

	वापस mdev->id.venकरोr;
पूर्ण

अटल u32 vp_vdpa_get_vq_align(काष्ठा vdpa_device *vdpa)
अणु
	वापस PAGE_SIZE;
पूर्ण

अटल माप_प्रकार vp_vdpa_get_config_size(काष्ठा vdpa_device *vdpa)
अणु
	काष्ठा virtio_pci_modern_device *mdev = vdpa_to_mdev(vdpa);

	वापस mdev->device_len;
पूर्ण

अटल व्योम vp_vdpa_get_config(काष्ठा vdpa_device *vdpa,
			       अचिन्हित पूर्णांक offset,
			       व्योम *buf, अचिन्हित पूर्णांक len)
अणु
	काष्ठा vp_vdpa *vp_vdpa = vdpa_to_vp(vdpa);
	काष्ठा virtio_pci_modern_device *mdev = &vp_vdpa->mdev;
	u8 old, new;
	u8 *p;
	पूर्णांक i;

	करो अणु
		old = vp_ioपढ़ो8(&mdev->common->config_generation);
		p = buf;
		क्रम (i = 0; i < len; i++)
			*p++ = vp_ioपढ़ो8(mdev->device + offset + i);

		new = vp_ioपढ़ो8(&mdev->common->config_generation);
	पूर्ण जबतक (old != new);
पूर्ण

अटल व्योम vp_vdpa_set_config(काष्ठा vdpa_device *vdpa,
			       अचिन्हित पूर्णांक offset, स्थिर व्योम *buf,
			       अचिन्हित पूर्णांक len)
अणु
	काष्ठा vp_vdpa *vp_vdpa = vdpa_to_vp(vdpa);
	काष्ठा virtio_pci_modern_device *mdev = &vp_vdpa->mdev;
	स्थिर u8 *p = buf;
	पूर्णांक i;

	क्रम (i = 0; i < len; i++)
		vp_ioग_लिखो8(*p++, mdev->device + offset + i);
पूर्ण

अटल व्योम vp_vdpa_set_config_cb(काष्ठा vdpa_device *vdpa,
				  काष्ठा vdpa_callback *cb)
अणु
	काष्ठा vp_vdpa *vp_vdpa = vdpa_to_vp(vdpa);

	vp_vdpa->config_cb = *cb;
पूर्ण

अटल काष्ठा vdpa_notअगरication_area
vp_vdpa_get_vq_notअगरication(काष्ठा vdpa_device *vdpa, u16 qid)
अणु
	काष्ठा vp_vdpa *vp_vdpa = vdpa_to_vp(vdpa);
	काष्ठा virtio_pci_modern_device *mdev = &vp_vdpa->mdev;
	काष्ठा vdpa_notअगरication_area notअगरy;

	notअगरy.addr = vp_vdpa->vring[qid].notअगरy_pa;
	notअगरy.size = mdev->notअगरy_offset_multiplier;

	वापस notअगरy;
पूर्ण

अटल स्थिर काष्ठा vdpa_config_ops vp_vdpa_ops = अणु
	.get_features	= vp_vdpa_get_features,
	.set_features	= vp_vdpa_set_features,
	.get_status	= vp_vdpa_get_status,
	.set_status	= vp_vdpa_set_status,
	.get_vq_num_max	= vp_vdpa_get_vq_num_max,
	.get_vq_state	= vp_vdpa_get_vq_state,
	.get_vq_notअगरication = vp_vdpa_get_vq_notअगरication,
	.set_vq_state	= vp_vdpa_set_vq_state,
	.set_vq_cb	= vp_vdpa_set_vq_cb,
	.set_vq_पढ़ोy	= vp_vdpa_set_vq_पढ़ोy,
	.get_vq_पढ़ोy	= vp_vdpa_get_vq_पढ़ोy,
	.set_vq_num	= vp_vdpa_set_vq_num,
	.set_vq_address	= vp_vdpa_set_vq_address,
	.kick_vq	= vp_vdpa_kick_vq,
	.get_generation	= vp_vdpa_get_generation,
	.get_device_id	= vp_vdpa_get_device_id,
	.get_venकरोr_id	= vp_vdpa_get_venकरोr_id,
	.get_vq_align	= vp_vdpa_get_vq_align,
	.get_config_size = vp_vdpa_get_config_size,
	.get_config	= vp_vdpa_get_config,
	.set_config	= vp_vdpa_set_config,
	.set_config_cb  = vp_vdpa_set_config_cb,
पूर्ण;

अटल व्योम vp_vdpa_मुक्त_irq_vectors(व्योम *data)
अणु
	pci_मुक्त_irq_vectors(data);
पूर्ण

अटल पूर्णांक vp_vdpa_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा virtio_pci_modern_device *mdev;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा vp_vdpa *vp_vdpa;
	पूर्णांक ret, i;

	ret = pcim_enable_device(pdev);
	अगर (ret)
		वापस ret;

	vp_vdpa = vdpa_alloc_device(काष्ठा vp_vdpa, vdpa,
				    dev, &vp_vdpa_ops, शून्य);
	अगर (vp_vdpa == शून्य) अणु
		dev_err(dev, "vp_vdpa: Failed to allocate vDPA structure\n");
		वापस -ENOMEM;
	पूर्ण

	mdev = &vp_vdpa->mdev;
	mdev->pci_dev = pdev;

	ret = vp_modern_probe(mdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to probe modern PCI device\n");
		जाओ err;
	पूर्ण

	pci_set_master(pdev);
	pci_set_drvdata(pdev, vp_vdpa);

	vp_vdpa->vdpa.dma_dev = &pdev->dev;
	vp_vdpa->queues = vp_modern_get_num_queues(mdev);

	ret = devm_add_action_or_reset(dev, vp_vdpa_मुक्त_irq_vectors, pdev);
	अगर (ret) अणु
		dev_err(&pdev->dev,
			"Failed for adding devres for freeing irq vectors\n");
		जाओ err;
	पूर्ण

	vp_vdpa->vring = devm_kसुस्मृति(&pdev->dev, vp_vdpa->queues,
				      माप(*vp_vdpa->vring),
				      GFP_KERNEL);
	अगर (!vp_vdpa->vring) अणु
		ret = -ENOMEM;
		dev_err(&pdev->dev, "Fail to allocate virtqueues\n");
		जाओ err;
	पूर्ण

	क्रम (i = 0; i < vp_vdpa->queues; i++) अणु
		vp_vdpa->vring[i].irq = VIRTIO_MSI_NO_VECTOR;
		vp_vdpa->vring[i].notअगरy =
			vp_modern_map_vq_notअगरy(mdev, i,
						&vp_vdpa->vring[i].notअगरy_pa);
		अगर (!vp_vdpa->vring[i].notअगरy) अणु
			dev_warn(&pdev->dev, "Fail to map vq notify %d\n", i);
			जाओ err;
		पूर्ण
	पूर्ण
	vp_vdpa->config_irq = VIRTIO_MSI_NO_VECTOR;

	ret = vdpa_रेजिस्टर_device(&vp_vdpa->vdpa, vp_vdpa->queues);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to register to vdpa bus\n");
		जाओ err;
	पूर्ण

	वापस 0;

err:
	put_device(&vp_vdpa->vdpa.dev);
	वापस ret;
पूर्ण

अटल व्योम vp_vdpa_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा vp_vdpa *vp_vdpa = pci_get_drvdata(pdev);

	vdpa_unरेजिस्टर_device(&vp_vdpa->vdpa);
	vp_modern_हटाओ(&vp_vdpa->mdev);
पूर्ण

अटल काष्ठा pci_driver vp_vdpa_driver = अणु
	.name		= "vp-vdpa",
	.id_table	= शून्य, /* only dynamic ids */
	.probe		= vp_vdpa_probe,
	.हटाओ		= vp_vdpa_हटाओ,
पूर्ण;

module_pci_driver(vp_vdpa_driver);

MODULE_AUTHOR("Jason Wang <jasowang@redhat.com>");
MODULE_DESCRIPTION("vp-vdpa");
MODULE_LICENSE("GPL");
MODULE_VERSION("1");
