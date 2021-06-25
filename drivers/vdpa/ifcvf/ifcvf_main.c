<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Intel IFC VF NIC driver क्रम virtio dataplane offloading
 *
 * Copyright (C) 2020 Intel Corporation.
 *
 * Author: Zhu Lingshan <lingshan.zhu@पूर्णांकel.com>
 *
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/sysfs.h>
#समावेश "ifcvf_base.h"

#घोषणा DRIVER_AUTHOR   "Intel Corporation"
#घोषणा IFCVF_DRIVER_NAME       "ifcvf"

अटल irqवापस_t अगरcvf_config_changed(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा अगरcvf_hw *vf = arg;

	अगर (vf->config_cb.callback)
		वापस vf->config_cb.callback(vf->config_cb.निजी);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t अगरcvf_पूर्णांकr_handler(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा vring_info *vring = arg;

	अगर (vring->cb.callback)
		वापस vring->cb.callback(vring->cb.निजी);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम अगरcvf_मुक्त_irq_vectors(व्योम *data)
अणु
	pci_मुक्त_irq_vectors(data);
पूर्ण

अटल व्योम अगरcvf_मुक्त_irq(काष्ठा अगरcvf_adapter *adapter, पूर्णांक queues)
अणु
	काष्ठा pci_dev *pdev = adapter->pdev;
	काष्ठा अगरcvf_hw *vf = &adapter->vf;
	पूर्णांक i;


	क्रम (i = 0; i < queues; i++) अणु
		devm_मुक्त_irq(&pdev->dev, vf->vring[i].irq, &vf->vring[i]);
		vf->vring[i].irq = -EINVAL;
	पूर्ण

	devm_मुक्त_irq(&pdev->dev, vf->config_irq, vf);
	अगरcvf_मुक्त_irq_vectors(pdev);
पूर्ण

अटल पूर्णांक अगरcvf_request_irq(काष्ठा अगरcvf_adapter *adapter)
अणु
	काष्ठा pci_dev *pdev = adapter->pdev;
	काष्ठा अगरcvf_hw *vf = &adapter->vf;
	पूर्णांक vector, i, ret, irq;

	ret = pci_alloc_irq_vectors(pdev, IFCVF_MAX_INTR,
				    IFCVF_MAX_INTR, PCI_IRQ_MSIX);
	अगर (ret < 0) अणु
		IFCVF_ERR(pdev, "Failed to alloc IRQ vectors\n");
		वापस ret;
	पूर्ण

	snम_लिखो(vf->config_msix_name, 256, "ifcvf[%s]-config\n",
		 pci_name(pdev));
	vector = 0;
	vf->config_irq = pci_irq_vector(pdev, vector);
	ret = devm_request_irq(&pdev->dev, vf->config_irq,
			       अगरcvf_config_changed, 0,
			       vf->config_msix_name, vf);
	अगर (ret) अणु
		IFCVF_ERR(pdev, "Failed to request config irq\n");
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < IFCVF_MAX_QUEUE_PAIRS * 2; i++) अणु
		snम_लिखो(vf->vring[i].msix_name, 256, "ifcvf[%s]-%d\n",
			 pci_name(pdev), i);
		vector = i + IFCVF_MSI_QUEUE_OFF;
		irq = pci_irq_vector(pdev, vector);
		ret = devm_request_irq(&pdev->dev, irq,
				       अगरcvf_पूर्णांकr_handler, 0,
				       vf->vring[i].msix_name,
				       &vf->vring[i]);
		अगर (ret) अणु
			IFCVF_ERR(pdev,
				  "Failed to request irq for vq %d\n", i);
			अगरcvf_मुक्त_irq(adapter, i);

			वापस ret;
		पूर्ण

		vf->vring[i].irq = irq;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक अगरcvf_start_datapath(व्योम *निजी)
अणु
	काष्ठा अगरcvf_hw *vf = अगरcvf_निजी_to_vf(निजी);
	u8 status;
	पूर्णांक ret;

	vf->nr_vring = IFCVF_MAX_QUEUE_PAIRS * 2;
	ret = अगरcvf_start_hw(vf);
	अगर (ret < 0) अणु
		status = अगरcvf_get_status(vf);
		status |= VIRTIO_CONFIG_S_FAILED;
		अगरcvf_set_status(vf, status);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक अगरcvf_stop_datapath(व्योम *निजी)
अणु
	काष्ठा अगरcvf_hw *vf = अगरcvf_निजी_to_vf(निजी);
	पूर्णांक i;

	क्रम (i = 0; i < IFCVF_MAX_QUEUE_PAIRS * 2; i++)
		vf->vring[i].cb.callback = शून्य;

	अगरcvf_stop_hw(vf);

	वापस 0;
पूर्ण

अटल व्योम अगरcvf_reset_vring(काष्ठा अगरcvf_adapter *adapter)
अणु
	काष्ठा अगरcvf_hw *vf = अगरcvf_निजी_to_vf(adapter);
	पूर्णांक i;

	क्रम (i = 0; i < IFCVF_MAX_QUEUE_PAIRS * 2; i++) अणु
		vf->vring[i].last_avail_idx = 0;
		vf->vring[i].desc = 0;
		vf->vring[i].avail = 0;
		vf->vring[i].used = 0;
		vf->vring[i].पढ़ोy = 0;
		vf->vring[i].cb.callback = शून्य;
		vf->vring[i].cb.निजी = शून्य;
	पूर्ण

	अगरcvf_reset(vf);
पूर्ण

अटल काष्ठा अगरcvf_adapter *vdpa_to_adapter(काष्ठा vdpa_device *vdpa_dev)
अणु
	वापस container_of(vdpa_dev, काष्ठा अगरcvf_adapter, vdpa);
पूर्ण

अटल काष्ठा अगरcvf_hw *vdpa_to_vf(काष्ठा vdpa_device *vdpa_dev)
अणु
	काष्ठा अगरcvf_adapter *adapter = vdpa_to_adapter(vdpa_dev);

	वापस &adapter->vf;
पूर्ण

अटल u64 अगरcvf_vdpa_get_features(काष्ठा vdpa_device *vdpa_dev)
अणु
	काष्ठा अगरcvf_adapter *adapter = vdpa_to_adapter(vdpa_dev);
	काष्ठा अगरcvf_hw *vf = vdpa_to_vf(vdpa_dev);
	काष्ठा pci_dev *pdev = adapter->pdev;

	u64 features;

	चयन (vf->dev_type) अणु
	हाल VIRTIO_ID_NET:
		features = अगरcvf_get_features(vf) & IFCVF_NET_SUPPORTED_FEATURES;
		अवरोध;
	हाल VIRTIO_ID_BLOCK:
		features = अगरcvf_get_features(vf);
		अवरोध;
	शेष:
		features = 0;
		IFCVF_ERR(pdev, "VIRTIO ID %u not supported\n", vf->dev_type);
	पूर्ण

	वापस features;
पूर्ण

अटल पूर्णांक अगरcvf_vdpa_set_features(काष्ठा vdpa_device *vdpa_dev, u64 features)
अणु
	काष्ठा अगरcvf_hw *vf = vdpa_to_vf(vdpa_dev);
	पूर्णांक ret;

	ret = अगरcvf_verअगरy_min_features(vf, features);
	अगर (ret)
		वापस ret;

	vf->req_features = features;

	वापस 0;
पूर्ण

अटल u8 अगरcvf_vdpa_get_status(काष्ठा vdpa_device *vdpa_dev)
अणु
	काष्ठा अगरcvf_hw *vf = vdpa_to_vf(vdpa_dev);

	वापस अगरcvf_get_status(vf);
पूर्ण

अटल व्योम अगरcvf_vdpa_set_status(काष्ठा vdpa_device *vdpa_dev, u8 status)
अणु
	काष्ठा अगरcvf_adapter *adapter;
	काष्ठा अगरcvf_hw *vf;
	u8 status_old;
	पूर्णांक ret;

	vf  = vdpa_to_vf(vdpa_dev);
	adapter = dev_get_drvdata(vdpa_dev->dev.parent);
	status_old = अगरcvf_get_status(vf);

	अगर (status_old == status)
		वापस;

	अगर ((status_old & VIRTIO_CONFIG_S_DRIVER_OK) &&
	    !(status & VIRTIO_CONFIG_S_DRIVER_OK)) अणु
		अगरcvf_stop_datapath(adapter);
		अगरcvf_मुक्त_irq(adapter, IFCVF_MAX_QUEUE_PAIRS * 2);
	पूर्ण

	अगर (status == 0) अणु
		अगरcvf_reset_vring(adapter);
		वापस;
	पूर्ण

	अगर ((status & VIRTIO_CONFIG_S_DRIVER_OK) &&
	    !(status_old & VIRTIO_CONFIG_S_DRIVER_OK)) अणु
		ret = अगरcvf_request_irq(adapter);
		अगर (ret) अणु
			status = अगरcvf_get_status(vf);
			status |= VIRTIO_CONFIG_S_FAILED;
			अगरcvf_set_status(vf, status);
			वापस;
		पूर्ण

		अगर (अगरcvf_start_datapath(adapter) < 0)
			IFCVF_ERR(adapter->pdev,
				  "Failed to set ifcvf vdpa  status %u\n",
				  status);
	पूर्ण

	अगरcvf_set_status(vf, status);
पूर्ण

अटल u16 अगरcvf_vdpa_get_vq_num_max(काष्ठा vdpa_device *vdpa_dev)
अणु
	वापस IFCVF_QUEUE_MAX;
पूर्ण

अटल पूर्णांक अगरcvf_vdpa_get_vq_state(काष्ठा vdpa_device *vdpa_dev, u16 qid,
				   काष्ठा vdpa_vq_state *state)
अणु
	काष्ठा अगरcvf_hw *vf = vdpa_to_vf(vdpa_dev);

	state->avail_index = अगरcvf_get_vq_state(vf, qid);
	वापस 0;
पूर्ण

अटल पूर्णांक अगरcvf_vdpa_set_vq_state(काष्ठा vdpa_device *vdpa_dev, u16 qid,
				   स्थिर काष्ठा vdpa_vq_state *state)
अणु
	काष्ठा अगरcvf_hw *vf = vdpa_to_vf(vdpa_dev);

	वापस अगरcvf_set_vq_state(vf, qid, state->avail_index);
पूर्ण

अटल व्योम अगरcvf_vdpa_set_vq_cb(काष्ठा vdpa_device *vdpa_dev, u16 qid,
				 काष्ठा vdpa_callback *cb)
अणु
	काष्ठा अगरcvf_hw *vf = vdpa_to_vf(vdpa_dev);

	vf->vring[qid].cb = *cb;
पूर्ण

अटल व्योम अगरcvf_vdpa_set_vq_पढ़ोy(काष्ठा vdpa_device *vdpa_dev,
				    u16 qid, bool पढ़ोy)
अणु
	काष्ठा अगरcvf_hw *vf = vdpa_to_vf(vdpa_dev);

	vf->vring[qid].पढ़ोy = पढ़ोy;
पूर्ण

अटल bool अगरcvf_vdpa_get_vq_पढ़ोy(काष्ठा vdpa_device *vdpa_dev, u16 qid)
अणु
	काष्ठा अगरcvf_hw *vf = vdpa_to_vf(vdpa_dev);

	वापस vf->vring[qid].पढ़ोy;
पूर्ण

अटल व्योम अगरcvf_vdpa_set_vq_num(काष्ठा vdpa_device *vdpa_dev, u16 qid,
				  u32 num)
अणु
	काष्ठा अगरcvf_hw *vf = vdpa_to_vf(vdpa_dev);

	vf->vring[qid].size = num;
पूर्ण

अटल पूर्णांक अगरcvf_vdpa_set_vq_address(काष्ठा vdpa_device *vdpa_dev, u16 qid,
				     u64 desc_area, u64 driver_area,
				     u64 device_area)
अणु
	काष्ठा अगरcvf_hw *vf = vdpa_to_vf(vdpa_dev);

	vf->vring[qid].desc = desc_area;
	vf->vring[qid].avail = driver_area;
	vf->vring[qid].used = device_area;

	वापस 0;
पूर्ण

अटल व्योम अगरcvf_vdpa_kick_vq(काष्ठा vdpa_device *vdpa_dev, u16 qid)
अणु
	काष्ठा अगरcvf_hw *vf = vdpa_to_vf(vdpa_dev);

	अगरcvf_notअगरy_queue(vf, qid);
पूर्ण

अटल u32 अगरcvf_vdpa_get_generation(काष्ठा vdpa_device *vdpa_dev)
अणु
	काष्ठा अगरcvf_hw *vf = vdpa_to_vf(vdpa_dev);

	वापस ioपढ़ो8(&vf->common_cfg->config_generation);
पूर्ण

अटल u32 अगरcvf_vdpa_get_device_id(काष्ठा vdpa_device *vdpa_dev)
अणु
	काष्ठा अगरcvf_hw *vf = vdpa_to_vf(vdpa_dev);

	वापस vf->dev_type;
पूर्ण

अटल u32 अगरcvf_vdpa_get_venकरोr_id(काष्ठा vdpa_device *vdpa_dev)
अणु
	काष्ठा अगरcvf_adapter *adapter = vdpa_to_adapter(vdpa_dev);
	काष्ठा pci_dev *pdev = adapter->pdev;

	वापस pdev->subप्रणाली_venकरोr;
पूर्ण

अटल u32 अगरcvf_vdpa_get_vq_align(काष्ठा vdpa_device *vdpa_dev)
अणु
	वापस IFCVF_QUEUE_ALIGNMENT;
पूर्ण

अटल माप_प्रकार अगरcvf_vdpa_get_config_size(काष्ठा vdpa_device *vdpa_dev)
अणु
	काष्ठा अगरcvf_adapter *adapter = vdpa_to_adapter(vdpa_dev);
	काष्ठा अगरcvf_hw *vf = vdpa_to_vf(vdpa_dev);
	काष्ठा pci_dev *pdev = adapter->pdev;
	माप_प्रकार size;

	चयन (vf->dev_type) अणु
	हाल VIRTIO_ID_NET:
		size = माप(काष्ठा virtio_net_config);
		अवरोध;
	हाल VIRTIO_ID_BLOCK:
		size = माप(काष्ठा virtio_blk_config);
		अवरोध;
	शेष:
		size = 0;
		IFCVF_ERR(pdev, "VIRTIO ID %u not supported\n", vf->dev_type);
	पूर्ण

	वापस size;
पूर्ण

अटल व्योम अगरcvf_vdpa_get_config(काष्ठा vdpa_device *vdpa_dev,
				  अचिन्हित पूर्णांक offset,
				  व्योम *buf, अचिन्हित पूर्णांक len)
अणु
	काष्ठा अगरcvf_hw *vf = vdpa_to_vf(vdpa_dev);

	WARN_ON(offset + len > माप(काष्ठा virtio_net_config));
	अगरcvf_पढ़ो_net_config(vf, offset, buf, len);
पूर्ण

अटल व्योम अगरcvf_vdpa_set_config(काष्ठा vdpa_device *vdpa_dev,
				  अचिन्हित पूर्णांक offset, स्थिर व्योम *buf,
				  अचिन्हित पूर्णांक len)
अणु
	काष्ठा अगरcvf_hw *vf = vdpa_to_vf(vdpa_dev);

	WARN_ON(offset + len > माप(काष्ठा virtio_net_config));
	अगरcvf_ग_लिखो_net_config(vf, offset, buf, len);
पूर्ण

अटल व्योम अगरcvf_vdpa_set_config_cb(काष्ठा vdpa_device *vdpa_dev,
				     काष्ठा vdpa_callback *cb)
अणु
	काष्ठा अगरcvf_hw *vf = vdpa_to_vf(vdpa_dev);

	vf->config_cb.callback = cb->callback;
	vf->config_cb.निजी = cb->निजी;
पूर्ण

अटल पूर्णांक अगरcvf_vdpa_get_vq_irq(काष्ठा vdpa_device *vdpa_dev,
				 u16 qid)
अणु
	काष्ठा अगरcvf_hw *vf = vdpa_to_vf(vdpa_dev);

	वापस vf->vring[qid].irq;
पूर्ण

/*
 * IFCVF currently करोes't have on-chip IOMMU, so not
 * implemented set_map()/dma_map()/dma_unmap()
 */
अटल स्थिर काष्ठा vdpa_config_ops अगरc_vdpa_ops = अणु
	.get_features	= अगरcvf_vdpa_get_features,
	.set_features	= अगरcvf_vdpa_set_features,
	.get_status	= अगरcvf_vdpa_get_status,
	.set_status	= अगरcvf_vdpa_set_status,
	.get_vq_num_max	= अगरcvf_vdpa_get_vq_num_max,
	.get_vq_state	= अगरcvf_vdpa_get_vq_state,
	.set_vq_state	= अगरcvf_vdpa_set_vq_state,
	.set_vq_cb	= अगरcvf_vdpa_set_vq_cb,
	.set_vq_पढ़ोy	= अगरcvf_vdpa_set_vq_पढ़ोy,
	.get_vq_पढ़ोy	= अगरcvf_vdpa_get_vq_पढ़ोy,
	.set_vq_num	= अगरcvf_vdpa_set_vq_num,
	.set_vq_address	= अगरcvf_vdpa_set_vq_address,
	.get_vq_irq	= अगरcvf_vdpa_get_vq_irq,
	.kick_vq	= अगरcvf_vdpa_kick_vq,
	.get_generation	= अगरcvf_vdpa_get_generation,
	.get_device_id	= अगरcvf_vdpa_get_device_id,
	.get_venकरोr_id	= अगरcvf_vdpa_get_venकरोr_id,
	.get_vq_align	= अगरcvf_vdpa_get_vq_align,
	.get_config_size	= अगरcvf_vdpa_get_config_size,
	.get_config	= अगरcvf_vdpa_get_config,
	.set_config	= अगरcvf_vdpa_set_config,
	.set_config_cb  = अगरcvf_vdpa_set_config_cb,
पूर्ण;

अटल पूर्णांक अगरcvf_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा अगरcvf_adapter *adapter;
	काष्ठा अगरcvf_hw *vf;
	पूर्णांक ret, i;

	ret = pcim_enable_device(pdev);
	अगर (ret) अणु
		IFCVF_ERR(pdev, "Failed to enable device\n");
		वापस ret;
	पूर्ण

	ret = pcim_iomap_regions(pdev, BIT(0) | BIT(2) | BIT(4),
				 IFCVF_DRIVER_NAME);
	अगर (ret) अणु
		IFCVF_ERR(pdev, "Failed to request MMIO region\n");
		वापस ret;
	पूर्ण

	ret = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(64));
	अगर (ret) अणु
		IFCVF_ERR(pdev, "No usable DMA configuration\n");
		वापस ret;
	पूर्ण

	ret = devm_add_action_or_reset(dev, अगरcvf_मुक्त_irq_vectors, pdev);
	अगर (ret) अणु
		IFCVF_ERR(pdev,
			  "Failed for adding devres for freeing irq vectors\n");
		वापस ret;
	पूर्ण

	adapter = vdpa_alloc_device(काष्ठा अगरcvf_adapter, vdpa,
				    dev, &अगरc_vdpa_ops, शून्य);
	अगर (adapter == शून्य) अणु
		IFCVF_ERR(pdev, "Failed to allocate vDPA structure");
		वापस -ENOMEM;
	पूर्ण

	pci_set_master(pdev);
	pci_set_drvdata(pdev, adapter);

	vf = &adapter->vf;

	/* This drirver drives both modern virtio devices and transitional
	 * devices in modern mode.
	 * vDPA requires feature bit VIRTIO_F_ACCESS_PLATFORM,
	 * so legacy devices and transitional devices in legacy
	 * mode will not work क्रम vDPA, this driver will not
	 * drive devices with legacy पूर्णांकerface.
	 */
	अगर (pdev->device < 0x1040)
		vf->dev_type =  pdev->subप्रणाली_device;
	अन्यथा
		vf->dev_type =  pdev->device - 0x1040;

	vf->base = pcim_iomap_table(pdev);

	adapter->pdev = pdev;
	adapter->vdpa.dma_dev = &pdev->dev;

	ret = अगरcvf_init_hw(vf, pdev);
	अगर (ret) अणु
		IFCVF_ERR(pdev, "Failed to init IFCVF hw\n");
		जाओ err;
	पूर्ण

	क्रम (i = 0; i < IFCVF_MAX_QUEUE_PAIRS * 2; i++)
		vf->vring[i].irq = -EINVAL;

	vf->hw_features = अगरcvf_get_hw_features(vf);

	ret = vdpa_रेजिस्टर_device(&adapter->vdpa, IFCVF_MAX_QUEUE_PAIRS * 2);
	अगर (ret) अणु
		IFCVF_ERR(pdev, "Failed to register ifcvf to vdpa bus");
		जाओ err;
	पूर्ण

	वापस 0;

err:
	put_device(&adapter->vdpa.dev);
	वापस ret;
पूर्ण

अटल व्योम अगरcvf_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा अगरcvf_adapter *adapter = pci_get_drvdata(pdev);

	vdpa_unरेजिस्टर_device(&adapter->vdpa);
पूर्ण

अटल काष्ठा pci_device_id अगरcvf_pci_ids[] = अणु
	अणु PCI_DEVICE_SUB(N3000_VENDOR_ID,
			 N3000_DEVICE_ID,
			 N3000_SUBSYS_VENDOR_ID,
			 N3000_SUBSYS_DEVICE_ID) पूर्ण,
	अणु PCI_DEVICE_SUB(C5000X_PL_VENDOR_ID,
			 C5000X_PL_DEVICE_ID,
			 C5000X_PL_SUBSYS_VENDOR_ID,
			 C5000X_PL_SUBSYS_DEVICE_ID) पूर्ण,
	अणु PCI_DEVICE_SUB(C5000X_PL_BLK_VENDOR_ID,
			 C5000X_PL_BLK_DEVICE_ID,
			 C5000X_PL_BLK_SUBSYS_VENDOR_ID,
			 C5000X_PL_BLK_SUBSYS_DEVICE_ID) पूर्ण,

	अणु 0 पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, अगरcvf_pci_ids);

अटल काष्ठा pci_driver अगरcvf_driver = अणु
	.name     = IFCVF_DRIVER_NAME,
	.id_table = अगरcvf_pci_ids,
	.probe    = अगरcvf_probe,
	.हटाओ   = अगरcvf_हटाओ,
पूर्ण;

module_pci_driver(अगरcvf_driver);

MODULE_LICENSE("GPL v2");
