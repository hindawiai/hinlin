<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later

#समावेश <linux/virtio_pci_modern.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>

/*
 * vp_modern_map_capability - map a part of virtio pci capability
 * @mdev: the modern virtio-pci device
 * @off: offset of the capability
 * @minlen: minimal length of the capability
 * @align: align requirement
 * @start: start from the capability
 * @size: map size
 * @len: the length that is actually mapped
 * @pa: physical address of the capability
 *
 * Returns the io address of क्रम the part of the capability
 */
अटल व्योम __iomem *
vp_modern_map_capability(काष्ठा virtio_pci_modern_device *mdev, पूर्णांक off,
			 माप_प्रकार minlen, u32 align, u32 start, u32 size,
			 माप_प्रकार *len, resource_माप_प्रकार *pa)
अणु
	काष्ठा pci_dev *dev = mdev->pci_dev;
	u8 bar;
	u32 offset, length;
	व्योम __iomem *p;

	pci_पढ़ो_config_byte(dev, off + दुरत्व(काष्ठा virtio_pci_cap,
						 bar),
			     &bar);
	pci_पढ़ो_config_dword(dev, off + दुरत्व(काष्ठा virtio_pci_cap, offset),
			     &offset);
	pci_पढ़ो_config_dword(dev, off + दुरत्व(काष्ठा virtio_pci_cap, length),
			      &length);

	अगर (length <= start) अणु
		dev_err(&dev->dev,
			"virtio_pci: bad capability len %u (>%u expected)\n",
			length, start);
		वापस शून्य;
	पूर्ण

	अगर (length - start < minlen) अणु
		dev_err(&dev->dev,
			"virtio_pci: bad capability len %u (>=%zu expected)\n",
			length, minlen);
		वापस शून्य;
	पूर्ण

	length -= start;

	अगर (start + offset < offset) अणु
		dev_err(&dev->dev,
			"virtio_pci: map wrap-around %u+%u\n",
			start, offset);
		वापस शून्य;
	पूर्ण

	offset += start;

	अगर (offset & (align - 1)) अणु
		dev_err(&dev->dev,
			"virtio_pci: offset %u not aligned to %u\n",
			offset, align);
		वापस शून्य;
	पूर्ण

	अगर (length > size)
		length = size;

	अगर (len)
		*len = length;

	अगर (minlen + offset < minlen ||
	    minlen + offset > pci_resource_len(dev, bar)) अणु
		dev_err(&dev->dev,
			"virtio_pci: map virtio %zu@%u "
			"out of range on bar %i length %lu\n",
			minlen, offset,
			bar, (अचिन्हित दीर्घ)pci_resource_len(dev, bar));
		वापस शून्य;
	पूर्ण

	p = pci_iomap_range(dev, bar, offset, length);
	अगर (!p)
		dev_err(&dev->dev,
			"virtio_pci: unable to map virtio %u@%u on bar %i\n",
			length, offset, bar);
	अन्यथा अगर (pa)
		*pa = pci_resource_start(dev, bar) + offset;

	वापस p;
पूर्ण

/**
 * virtio_pci_find_capability - walk capabilities to find device info.
 * @dev: the pci device
 * @cfg_type: the VIRTIO_PCI_CAP_* value we seek
 * @ioresource_types: IORESOURCE_MEM and/or IORESOURCE_IO.
 * @bars: the biपंचांगask of BARs
 *
 * Returns offset of the capability, or 0.
 */
अटल अंतरभूत पूर्णांक virtio_pci_find_capability(काष्ठा pci_dev *dev, u8 cfg_type,
					     u32 ioresource_types, पूर्णांक *bars)
अणु
	पूर्णांक pos;

	क्रम (pos = pci_find_capability(dev, PCI_CAP_ID_VNDR);
	     pos > 0;
	     pos = pci_find_next_capability(dev, pos, PCI_CAP_ID_VNDR)) अणु
		u8 type, bar;
		pci_पढ़ो_config_byte(dev, pos + दुरत्व(काष्ठा virtio_pci_cap,
							 cfg_type),
				     &type);
		pci_पढ़ो_config_byte(dev, pos + दुरत्व(काष्ठा virtio_pci_cap,
							 bar),
				     &bar);

		/* Ignore काष्ठाures with reserved BAR values */
		अगर (bar > 0x5)
			जारी;

		अगर (type == cfg_type) अणु
			अगर (pci_resource_len(dev, bar) &&
			    pci_resource_flags(dev, bar) & ioresource_types) अणु
				*bars |= (1 << bar);
				वापस pos;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/* This is part of the ABI.  Don't screw with it. */
अटल अंतरभूत व्योम check_offsets(व्योम)
अणु
	/* Note: disk space was harmed in compilation of this function. */
	BUILD_BUG_ON(VIRTIO_PCI_CAP_VNDR !=
		     दुरत्व(काष्ठा virtio_pci_cap, cap_vndr));
	BUILD_BUG_ON(VIRTIO_PCI_CAP_NEXT !=
		     दुरत्व(काष्ठा virtio_pci_cap, cap_next));
	BUILD_BUG_ON(VIRTIO_PCI_CAP_LEN !=
		     दुरत्व(काष्ठा virtio_pci_cap, cap_len));
	BUILD_BUG_ON(VIRTIO_PCI_CAP_CFG_TYPE !=
		     दुरत्व(काष्ठा virtio_pci_cap, cfg_type));
	BUILD_BUG_ON(VIRTIO_PCI_CAP_BAR !=
		     दुरत्व(काष्ठा virtio_pci_cap, bar));
	BUILD_BUG_ON(VIRTIO_PCI_CAP_OFFSET !=
		     दुरत्व(काष्ठा virtio_pci_cap, offset));
	BUILD_BUG_ON(VIRTIO_PCI_CAP_LENGTH !=
		     दुरत्व(काष्ठा virtio_pci_cap, length));
	BUILD_BUG_ON(VIRTIO_PCI_NOTIFY_CAP_MULT !=
		     दुरत्व(काष्ठा virtio_pci_notअगरy_cap,
			      notअगरy_off_multiplier));
	BUILD_BUG_ON(VIRTIO_PCI_COMMON_DFSELECT !=
		     दुरत्व(काष्ठा virtio_pci_common_cfg,
			      device_feature_select));
	BUILD_BUG_ON(VIRTIO_PCI_COMMON_DF !=
		     दुरत्व(काष्ठा virtio_pci_common_cfg, device_feature));
	BUILD_BUG_ON(VIRTIO_PCI_COMMON_GFSELECT !=
		     दुरत्व(काष्ठा virtio_pci_common_cfg,
			      guest_feature_select));
	BUILD_BUG_ON(VIRTIO_PCI_COMMON_GF !=
		     दुरत्व(काष्ठा virtio_pci_common_cfg, guest_feature));
	BUILD_BUG_ON(VIRTIO_PCI_COMMON_MSIX !=
		     दुरत्व(काष्ठा virtio_pci_common_cfg, msix_config));
	BUILD_BUG_ON(VIRTIO_PCI_COMMON_NUMQ !=
		     दुरत्व(काष्ठा virtio_pci_common_cfg, num_queues));
	BUILD_BUG_ON(VIRTIO_PCI_COMMON_STATUS !=
		     दुरत्व(काष्ठा virtio_pci_common_cfg, device_status));
	BUILD_BUG_ON(VIRTIO_PCI_COMMON_CFGGENERATION !=
		     दुरत्व(काष्ठा virtio_pci_common_cfg, config_generation));
	BUILD_BUG_ON(VIRTIO_PCI_COMMON_Q_SELECT !=
		     दुरत्व(काष्ठा virtio_pci_common_cfg, queue_select));
	BUILD_BUG_ON(VIRTIO_PCI_COMMON_Q_SIZE !=
		     दुरत्व(काष्ठा virtio_pci_common_cfg, queue_size));
	BUILD_BUG_ON(VIRTIO_PCI_COMMON_Q_MSIX !=
		     दुरत्व(काष्ठा virtio_pci_common_cfg, queue_msix_vector));
	BUILD_BUG_ON(VIRTIO_PCI_COMMON_Q_ENABLE !=
		     दुरत्व(काष्ठा virtio_pci_common_cfg, queue_enable));
	BUILD_BUG_ON(VIRTIO_PCI_COMMON_Q_NOFF !=
		     दुरत्व(काष्ठा virtio_pci_common_cfg, queue_notअगरy_off));
	BUILD_BUG_ON(VIRTIO_PCI_COMMON_Q_DESCLO !=
		     दुरत्व(काष्ठा virtio_pci_common_cfg, queue_desc_lo));
	BUILD_BUG_ON(VIRTIO_PCI_COMMON_Q_DESCHI !=
		     दुरत्व(काष्ठा virtio_pci_common_cfg, queue_desc_hi));
	BUILD_BUG_ON(VIRTIO_PCI_COMMON_Q_AVAILLO !=
		     दुरत्व(काष्ठा virtio_pci_common_cfg, queue_avail_lo));
	BUILD_BUG_ON(VIRTIO_PCI_COMMON_Q_AVAILHI !=
		     दुरत्व(काष्ठा virtio_pci_common_cfg, queue_avail_hi));
	BUILD_BUG_ON(VIRTIO_PCI_COMMON_Q_USEDLO !=
		     दुरत्व(काष्ठा virtio_pci_common_cfg, queue_used_lo));
	BUILD_BUG_ON(VIRTIO_PCI_COMMON_Q_USEDHI !=
		     दुरत्व(काष्ठा virtio_pci_common_cfg, queue_used_hi));
पूर्ण

/*
 * vp_modern_probe: probe the modern virtio pci device, note that the
 * caller is required to enable PCI device beक्रमe calling this function.
 * @mdev: the modern virtio-pci device
 *
 * Return 0 on succeed otherwise fail
 */
पूर्णांक vp_modern_probe(काष्ठा virtio_pci_modern_device *mdev)
अणु
	काष्ठा pci_dev *pci_dev = mdev->pci_dev;
	पूर्णांक err, common, isr, notअगरy, device;
	u32 notअगरy_length;
	u32 notअगरy_offset;

	check_offsets();

	mdev->pci_dev = pci_dev;

	/* We only own devices >= 0x1000 and <= 0x107f: leave the rest. */
	अगर (pci_dev->device < 0x1000 || pci_dev->device > 0x107f)
		वापस -ENODEV;

	अगर (pci_dev->device < 0x1040) अणु
		/* Transitional devices: use the PCI subप्रणाली device id as
		 * virtio device id, same as legacy driver always did.
		 */
		mdev->id.device = pci_dev->subप्रणाली_device;
	पूर्ण अन्यथा अणु
		/* Modern devices: simply use PCI device id, but start from 0x1040. */
		mdev->id.device = pci_dev->device - 0x1040;
	पूर्ण
	mdev->id.venकरोr = pci_dev->subप्रणाली_venकरोr;

	/* check क्रम a common config: अगर not, use legacy mode (bar 0). */
	common = virtio_pci_find_capability(pci_dev, VIRTIO_PCI_CAP_COMMON_CFG,
					    IORESOURCE_IO | IORESOURCE_MEM,
					    &mdev->modern_bars);
	अगर (!common) अणु
		dev_info(&pci_dev->dev,
			 "virtio_pci: leaving for legacy driver\n");
		वापस -ENODEV;
	पूर्ण

	/* If common is there, these should be too... */
	isr = virtio_pci_find_capability(pci_dev, VIRTIO_PCI_CAP_ISR_CFG,
					 IORESOURCE_IO | IORESOURCE_MEM,
					 &mdev->modern_bars);
	notअगरy = virtio_pci_find_capability(pci_dev, VIRTIO_PCI_CAP_NOTIFY_CFG,
					    IORESOURCE_IO | IORESOURCE_MEM,
					    &mdev->modern_bars);
	अगर (!isr || !notअगरy) अणु
		dev_err(&pci_dev->dev,
			"virtio_pci: missing capabilities %i/%i/%i\n",
			common, isr, notअगरy);
		वापस -EINVAL;
	पूर्ण

	err = dma_set_mask_and_coherent(&pci_dev->dev, DMA_BIT_MASK(64));
	अगर (err)
		err = dma_set_mask_and_coherent(&pci_dev->dev,
						DMA_BIT_MASK(32));
	अगर (err)
		dev_warn(&pci_dev->dev, "Failed to enable 64-bit or 32-bit DMA.  Trying to continue, but this might not work.\n");

	/* Device capability is only mandatory क्रम devices that have
	 * device-specअगरic configuration.
	 */
	device = virtio_pci_find_capability(pci_dev, VIRTIO_PCI_CAP_DEVICE_CFG,
					    IORESOURCE_IO | IORESOURCE_MEM,
					    &mdev->modern_bars);

	err = pci_request_selected_regions(pci_dev, mdev->modern_bars,
					   "virtio-pci-modern");
	अगर (err)
		वापस err;

	err = -EINVAL;
	mdev->common = vp_modern_map_capability(mdev, common,
				      माप(काष्ठा virtio_pci_common_cfg), 4,
				      0, माप(काष्ठा virtio_pci_common_cfg),
				      शून्य, शून्य);
	अगर (!mdev->common)
		जाओ err_map_common;
	mdev->isr = vp_modern_map_capability(mdev, isr, माप(u8), 1,
					     0, 1,
					     शून्य, शून्य);
	अगर (!mdev->isr)
		जाओ err_map_isr;

	/* Read notअगरy_off_multiplier from config space. */
	pci_पढ़ो_config_dword(pci_dev,
			      notअगरy + दुरत्व(काष्ठा virtio_pci_notअगरy_cap,
						notअगरy_off_multiplier),
			      &mdev->notअगरy_offset_multiplier);
	/* Read notअगरy length and offset from config space. */
	pci_पढ़ो_config_dword(pci_dev,
			      notअगरy + दुरत्व(काष्ठा virtio_pci_notअगरy_cap,
						cap.length),
			      &notअगरy_length);

	pci_पढ़ो_config_dword(pci_dev,
			      notअगरy + दुरत्व(काष्ठा virtio_pci_notअगरy_cap,
						cap.offset),
			      &notअगरy_offset);

	/* We करोn't know how many VQs we'll map, ahead of the समय.
	 * If notअगरy length is small, map it all now.
	 * Otherwise, map each VQ inभागidually later.
	 */
	अगर ((u64)notअगरy_length + (notअगरy_offset % PAGE_SIZE) <= PAGE_SIZE) अणु
		mdev->notअगरy_base = vp_modern_map_capability(mdev, notअगरy,
							     2, 2,
							     0, notअगरy_length,
							     &mdev->notअगरy_len,
							     &mdev->notअगरy_pa);
		अगर (!mdev->notअगरy_base)
			जाओ err_map_notअगरy;
	पूर्ण अन्यथा अणु
		mdev->notअगरy_map_cap = notअगरy;
	पूर्ण

	/* Again, we करोn't know how much we should map, but PAGE_SIZE
	 * is more than enough क्रम all existing devices.
	 */
	अगर (device) अणु
		mdev->device = vp_modern_map_capability(mdev, device, 0, 4,
							0, PAGE_SIZE,
							&mdev->device_len,
							शून्य);
		अगर (!mdev->device)
			जाओ err_map_device;
	पूर्ण

	वापस 0;

err_map_device:
	अगर (mdev->notअगरy_base)
		pci_iounmap(pci_dev, mdev->notअगरy_base);
err_map_notअगरy:
	pci_iounmap(pci_dev, mdev->isr);
err_map_isr:
	pci_iounmap(pci_dev, mdev->common);
err_map_common:
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(vp_modern_probe);

/*
 * vp_modern_probe: हटाओ and cleanup the modern virtio pci device
 * @mdev: the modern virtio-pci device
 */
व्योम vp_modern_हटाओ(काष्ठा virtio_pci_modern_device *mdev)
अणु
	काष्ठा pci_dev *pci_dev = mdev->pci_dev;

	अगर (mdev->device)
		pci_iounmap(pci_dev, mdev->device);
	अगर (mdev->notअगरy_base)
		pci_iounmap(pci_dev, mdev->notअगरy_base);
	pci_iounmap(pci_dev, mdev->isr);
	pci_iounmap(pci_dev, mdev->common);
	pci_release_selected_regions(pci_dev, mdev->modern_bars);
पूर्ण
EXPORT_SYMBOL_GPL(vp_modern_हटाओ);

/*
 * vp_modern_get_features - get features from device
 * @mdev: the modern virtio-pci device
 *
 * Returns the features पढ़ो from the device
 */
u64 vp_modern_get_features(काष्ठा virtio_pci_modern_device *mdev)
अणु
	काष्ठा virtio_pci_common_cfg __iomem *cfg = mdev->common;

	u64 features;

	vp_ioग_लिखो32(0, &cfg->device_feature_select);
	features = vp_ioपढ़ो32(&cfg->device_feature);
	vp_ioग_लिखो32(1, &cfg->device_feature_select);
	features |= ((u64)vp_ioपढ़ो32(&cfg->device_feature) << 32);

	वापस features;
पूर्ण
EXPORT_SYMBOL_GPL(vp_modern_get_features);

/*
 * vp_modern_set_features - set features to device
 * @mdev: the modern virtio-pci device
 * @features: the features set to device
 */
व्योम vp_modern_set_features(काष्ठा virtio_pci_modern_device *mdev,
			    u64 features)
अणु
	काष्ठा virtio_pci_common_cfg __iomem *cfg = mdev->common;

	vp_ioग_लिखो32(0, &cfg->guest_feature_select);
	vp_ioग_लिखो32((u32)features, &cfg->guest_feature);
	vp_ioग_लिखो32(1, &cfg->guest_feature_select);
	vp_ioग_लिखो32(features >> 32, &cfg->guest_feature);
पूर्ण
EXPORT_SYMBOL_GPL(vp_modern_set_features);

/*
 * vp_modern_generation - get the device genreation
 * @mdev: the modern virtio-pci device
 *
 * Returns the genreation पढ़ो from device
 */
u32 vp_modern_generation(काष्ठा virtio_pci_modern_device *mdev)
अणु
	काष्ठा virtio_pci_common_cfg __iomem *cfg = mdev->common;

	वापस vp_ioपढ़ो8(&cfg->config_generation);
पूर्ण
EXPORT_SYMBOL_GPL(vp_modern_generation);

/*
 * vp_modern_get_status - get the device status
 * @mdev: the modern virtio-pci device
 *
 * Returns the status पढ़ो from device
 */
u8 vp_modern_get_status(काष्ठा virtio_pci_modern_device *mdev)
अणु
	काष्ठा virtio_pci_common_cfg __iomem *cfg = mdev->common;

	वापस vp_ioपढ़ो8(&cfg->device_status);
पूर्ण
EXPORT_SYMBOL_GPL(vp_modern_get_status);

/*
 * vp_modern_set_status - set status to device
 * @mdev: the modern virtio-pci device
 * @status: the status set to device
 */
व्योम vp_modern_set_status(काष्ठा virtio_pci_modern_device *mdev,
				 u8 status)
अणु
	काष्ठा virtio_pci_common_cfg __iomem *cfg = mdev->common;

	vp_ioग_लिखो8(status, &cfg->device_status);
पूर्ण
EXPORT_SYMBOL_GPL(vp_modern_set_status);

/*
 * vp_modern_queue_vector - set the MSIX vector क्रम a specअगरic virtqueue
 * @mdev: the modern virtio-pci device
 * @index: queue index
 * @vector: the config vector
 *
 * Returns the config vector पढ़ो from the device
 */
u16 vp_modern_queue_vector(काष्ठा virtio_pci_modern_device *mdev,
			   u16 index, u16 vector)
अणु
	काष्ठा virtio_pci_common_cfg __iomem *cfg = mdev->common;

	vp_ioग_लिखो16(index, &cfg->queue_select);
	vp_ioग_लिखो16(vector, &cfg->queue_msix_vector);
	/* Flush the ग_लिखो out to device */
	वापस vp_ioपढ़ो16(&cfg->queue_msix_vector);
पूर्ण
EXPORT_SYMBOL_GPL(vp_modern_queue_vector);

/*
 * vp_modern_config_vector - set the vector क्रम config पूर्णांकerrupt
 * @mdev: the modern virtio-pci device
 * @vector: the config vector
 *
 * Returns the config vector पढ़ो from the device
 */
u16 vp_modern_config_vector(काष्ठा virtio_pci_modern_device *mdev,
			    u16 vector)
अणु
	काष्ठा virtio_pci_common_cfg __iomem *cfg = mdev->common;

	/* Setup the vector used क्रम configuration events */
	vp_ioग_लिखो16(vector, &cfg->msix_config);
	/* Verअगरy we had enough resources to assign the vector */
	/* Will also flush the ग_लिखो out to device */
	वापस vp_ioपढ़ो16(&cfg->msix_config);
पूर्ण
EXPORT_SYMBOL_GPL(vp_modern_config_vector);

/*
 * vp_modern_queue_address - set the virtqueue address
 * @mdev: the modern virtio-pci device
 * @index: the queue index
 * @desc_addr: address of the descriptor area
 * @driver_addr: address of the driver area
 * @device_addr: address of the device area
 */
व्योम vp_modern_queue_address(काष्ठा virtio_pci_modern_device *mdev,
			     u16 index, u64 desc_addr, u64 driver_addr,
			     u64 device_addr)
अणु
	काष्ठा virtio_pci_common_cfg __iomem *cfg = mdev->common;

	vp_ioग_लिखो16(index, &cfg->queue_select);

	vp_ioग_लिखो64_twopart(desc_addr, &cfg->queue_desc_lo,
			     &cfg->queue_desc_hi);
	vp_ioग_लिखो64_twopart(driver_addr, &cfg->queue_avail_lo,
			     &cfg->queue_avail_hi);
	vp_ioग_लिखो64_twopart(device_addr, &cfg->queue_used_lo,
			     &cfg->queue_used_hi);
पूर्ण
EXPORT_SYMBOL_GPL(vp_modern_queue_address);

/*
 * vp_modern_set_queue_enable - enable a virtqueue
 * @mdev: the modern virtio-pci device
 * @index: the queue index
 * @enable: whether the virtqueue is enable or not
 */
व्योम vp_modern_set_queue_enable(काष्ठा virtio_pci_modern_device *mdev,
				u16 index, bool enable)
अणु
	vp_ioग_लिखो16(index, &mdev->common->queue_select);
	vp_ioग_लिखो16(enable, &mdev->common->queue_enable);
पूर्ण
EXPORT_SYMBOL_GPL(vp_modern_set_queue_enable);

/*
 * vp_modern_get_queue_enable - enable a virtqueue
 * @mdev: the modern virtio-pci device
 * @index: the queue index
 *
 * Returns whether a virtqueue is enabled or not
 */
bool vp_modern_get_queue_enable(काष्ठा virtio_pci_modern_device *mdev,
				u16 index)
अणु
	vp_ioग_लिखो16(index, &mdev->common->queue_select);

	वापस vp_ioपढ़ो16(&mdev->common->queue_enable);
पूर्ण
EXPORT_SYMBOL_GPL(vp_modern_get_queue_enable);

/*
 * vp_modern_set_queue_size - set size क्रम a virtqueue
 * @mdev: the modern virtio-pci device
 * @index: the queue index
 * @size: the size of the virtqueue
 */
व्योम vp_modern_set_queue_size(काष्ठा virtio_pci_modern_device *mdev,
			      u16 index, u16 size)
अणु
	vp_ioग_लिखो16(index, &mdev->common->queue_select);
	vp_ioग_लिखो16(size, &mdev->common->queue_size);

पूर्ण
EXPORT_SYMBOL_GPL(vp_modern_set_queue_size);

/*
 * vp_modern_get_queue_size - get size क्रम a virtqueue
 * @mdev: the modern virtio-pci device
 * @index: the queue index
 *
 * Returns the size of the virtqueue
 */
u16 vp_modern_get_queue_size(काष्ठा virtio_pci_modern_device *mdev,
			     u16 index)
अणु
	vp_ioग_लिखो16(index, &mdev->common->queue_select);

	वापस vp_ioपढ़ो16(&mdev->common->queue_size);

पूर्ण
EXPORT_SYMBOL_GPL(vp_modern_get_queue_size);

/*
 * vp_modern_get_num_queues - get the number of virtqueues
 * @mdev: the modern virtio-pci device
 *
 * Returns the number of virtqueues
 */
u16 vp_modern_get_num_queues(काष्ठा virtio_pci_modern_device *mdev)
अणु
	वापस vp_ioपढ़ो16(&mdev->common->num_queues);
पूर्ण
EXPORT_SYMBOL_GPL(vp_modern_get_num_queues);

/*
 * vp_modern_get_queue_notअगरy_off - get notअगरication offset क्रम a virtqueue
 * @mdev: the modern virtio-pci device
 * @index: the queue index
 *
 * Returns the notअगरication offset क्रम a virtqueue
 */
अटल u16 vp_modern_get_queue_notअगरy_off(काष्ठा virtio_pci_modern_device *mdev,
					  u16 index)
अणु
	vp_ioग_लिखो16(index, &mdev->common->queue_select);

	वापस vp_ioपढ़ो16(&mdev->common->queue_notअगरy_off);
पूर्ण

/*
 * vp_modern_map_vq_notअगरy - map notअगरication area क्रम a
 * specअगरic virtqueue
 * @mdev: the modern virtio-pci device
 * @index: the queue index
 * @pa: the poपूर्णांकer to the physical address of the nofity area
 *
 * Returns the address of the notअगरication area
 */
व्योम __iomem *vp_modern_map_vq_notअगरy(काष्ठा virtio_pci_modern_device *mdev,
				      u16 index, resource_माप_प्रकार *pa)
अणु
	u16 off = vp_modern_get_queue_notअगरy_off(mdev, index);

	अगर (mdev->notअगरy_base) अणु
		/* offset should not wrap */
		अगर ((u64)off * mdev->notअगरy_offset_multiplier + 2
			> mdev->notअगरy_len) अणु
			dev_warn(&mdev->pci_dev->dev,
				 "bad notification offset %u (x %u) "
				 "for queue %u > %zd",
				 off, mdev->notअगरy_offset_multiplier,
				 index, mdev->notअगरy_len);
			वापस शून्य;
		पूर्ण
		अगर (pa)
			*pa = mdev->notअगरy_pa +
			      off * mdev->notअगरy_offset_multiplier;
		वापस mdev->notअगरy_base + off * mdev->notअगरy_offset_multiplier;
	पूर्ण अन्यथा अणु
		वापस vp_modern_map_capability(mdev,
				       mdev->notअगरy_map_cap, 2, 2,
				       off * mdev->notअगरy_offset_multiplier, 2,
				       शून्य, pa);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(vp_modern_map_vq_notअगरy);

MODULE_VERSION("0.1");
MODULE_DESCRIPTION("Modern Virtio PCI Device");
MODULE_AUTHOR("Jason Wang <jasowang@redhat.com>");
MODULE_LICENSE("GPL");
