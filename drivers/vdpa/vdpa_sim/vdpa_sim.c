<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * VDPA device simulator core.
 *
 * Copyright (c) 2020, Red Hat Inc. All rights reserved.
 *     Author: Jason Wang <jasowang@redhat.com>
 *
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>
#समावेश <linux/dma-map-ops.h>
#समावेश <linux/vringh.h>
#समावेश <linux/vdpa.h>
#समावेश <linux/vhost_iotlb.h>
#समावेश <linux/iova.h>

#समावेश "vdpa_sim.h"

#घोषणा DRV_VERSION  "0.1"
#घोषणा DRV_AUTHOR   "Jason Wang <jasowang@redhat.com>"
#घोषणा DRV_DESC     "vDPA Device Simulator core"
#घोषणा DRV_LICENSE  "GPL v2"

अटल पूर्णांक batch_mapping = 1;
module_param(batch_mapping, पूर्णांक, 0444);
MODULE_PARM_DESC(batch_mapping, "Batched mapping 1 -Enable; 0 - Disable");

अटल पूर्णांक max_iotlb_entries = 2048;
module_param(max_iotlb_entries, पूर्णांक, 0444);
MODULE_PARM_DESC(max_iotlb_entries,
		 "Maximum number of iotlb entries. 0 means unlimited. (default: 2048)");

#घोषणा VDPASIM_QUEUE_ALIGN PAGE_SIZE
#घोषणा VDPASIM_QUEUE_MAX 256
#घोषणा VDPASIM_VENDOR_ID 0

अटल काष्ठा vdpasim *vdpa_to_sim(काष्ठा vdpa_device *vdpa)
अणु
	वापस container_of(vdpa, काष्ठा vdpasim, vdpa);
पूर्ण

अटल काष्ठा vdpasim *dev_to_sim(काष्ठा device *dev)
अणु
	काष्ठा vdpa_device *vdpa = dev_to_vdpa(dev);

	वापस vdpa_to_sim(vdpa);
पूर्ण

अटल व्योम vdpasim_vq_notअगरy(काष्ठा vringh *vring)
अणु
	काष्ठा vdpasim_virtqueue *vq =
		container_of(vring, काष्ठा vdpasim_virtqueue, vring);

	अगर (!vq->cb)
		वापस;

	vq->cb(vq->निजी);
पूर्ण

अटल व्योम vdpasim_queue_पढ़ोy(काष्ठा vdpasim *vdpasim, अचिन्हित पूर्णांक idx)
अणु
	काष्ठा vdpasim_virtqueue *vq = &vdpasim->vqs[idx];

	vringh_init_iotlb(&vq->vring, vdpasim->dev_attr.supported_features,
			  VDPASIM_QUEUE_MAX, false,
			  (काष्ठा vring_desc *)(uपूर्णांकptr_t)vq->desc_addr,
			  (काष्ठा vring_avail *)
			  (uपूर्णांकptr_t)vq->driver_addr,
			  (काष्ठा vring_used *)
			  (uपूर्णांकptr_t)vq->device_addr);

	vq->vring.notअगरy = vdpasim_vq_notअगरy;
पूर्ण

अटल व्योम vdpasim_vq_reset(काष्ठा vdpasim *vdpasim,
			     काष्ठा vdpasim_virtqueue *vq)
अणु
	vq->पढ़ोy = false;
	vq->desc_addr = 0;
	vq->driver_addr = 0;
	vq->device_addr = 0;
	vq->cb = शून्य;
	vq->निजी = शून्य;
	vringh_init_iotlb(&vq->vring, vdpasim->dev_attr.supported_features,
			  VDPASIM_QUEUE_MAX, false, शून्य, शून्य, शून्य);

	vq->vring.notअगरy = शून्य;
पूर्ण

अटल व्योम vdpasim_reset(काष्ठा vdpasim *vdpasim)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < vdpasim->dev_attr.nvqs; i++)
		vdpasim_vq_reset(vdpasim, &vdpasim->vqs[i]);

	spin_lock(&vdpasim->iommu_lock);
	vhost_iotlb_reset(vdpasim->iommu);
	spin_unlock(&vdpasim->iommu_lock);

	vdpasim->features = 0;
	vdpasim->status = 0;
	++vdpasim->generation;
पूर्ण

अटल पूर्णांक dir_to_perm(क्रमागत dma_data_direction dir)
अणु
	पूर्णांक perm = -EFAULT;

	चयन (dir) अणु
	हाल DMA_FROM_DEVICE:
		perm = VHOST_MAP_WO;
		अवरोध;
	हाल DMA_TO_DEVICE:
		perm = VHOST_MAP_RO;
		अवरोध;
	हाल DMA_BIसूचीECTIONAL:
		perm = VHOST_MAP_RW;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस perm;
पूर्ण

अटल dma_addr_t vdpasim_map_range(काष्ठा vdpasim *vdpasim, phys_addr_t paddr,
				    माप_प्रकार size, अचिन्हित पूर्णांक perm)
अणु
	काष्ठा iova *iova;
	dma_addr_t dma_addr;
	पूर्णांक ret;

	/* We set the limit_pfn to the maximum (अच_दीर्घ_उच्च - 1) */
	iova = alloc_iova(&vdpasim->iova, size, अच_दीर्घ_उच्च - 1, true);
	अगर (!iova)
		वापस DMA_MAPPING_ERROR;

	dma_addr = iova_dma_addr(&vdpasim->iova, iova);

	spin_lock(&vdpasim->iommu_lock);
	ret = vhost_iotlb_add_range(vdpasim->iommu, (u64)dma_addr,
				    (u64)dma_addr + size - 1, (u64)paddr, perm);
	spin_unlock(&vdpasim->iommu_lock);

	अगर (ret) अणु
		__मुक्त_iova(&vdpasim->iova, iova);
		वापस DMA_MAPPING_ERROR;
	पूर्ण

	वापस dma_addr;
पूर्ण

अटल व्योम vdpasim_unmap_range(काष्ठा vdpasim *vdpasim, dma_addr_t dma_addr,
				माप_प्रकार size)
अणु
	spin_lock(&vdpasim->iommu_lock);
	vhost_iotlb_del_range(vdpasim->iommu, (u64)dma_addr,
			      (u64)dma_addr + size - 1);
	spin_unlock(&vdpasim->iommu_lock);

	मुक्त_iova(&vdpasim->iova, iova_pfn(&vdpasim->iova, dma_addr));
पूर्ण

अटल dma_addr_t vdpasim_map_page(काष्ठा device *dev, काष्ठा page *page,
				   अचिन्हित दीर्घ offset, माप_प्रकार size,
				   क्रमागत dma_data_direction dir,
				   अचिन्हित दीर्घ attrs)
अणु
	काष्ठा vdpasim *vdpasim = dev_to_sim(dev);
	phys_addr_t paddr = page_to_phys(page) + offset;
	पूर्णांक perm = dir_to_perm(dir);

	अगर (perm < 0)
		वापस DMA_MAPPING_ERROR;

	वापस vdpasim_map_range(vdpasim, paddr, size, perm);
पूर्ण

अटल व्योम vdpasim_unmap_page(काष्ठा device *dev, dma_addr_t dma_addr,
			       माप_प्रकार size, क्रमागत dma_data_direction dir,
			       अचिन्हित दीर्घ attrs)
अणु
	काष्ठा vdpasim *vdpasim = dev_to_sim(dev);

	vdpasim_unmap_range(vdpasim, dma_addr, size);
पूर्ण

अटल व्योम *vdpasim_alloc_coherent(काष्ठा device *dev, माप_प्रकार size,
				    dma_addr_t *dma_addr, gfp_t flag,
				    अचिन्हित दीर्घ attrs)
अणु
	काष्ठा vdpasim *vdpasim = dev_to_sim(dev);
	phys_addr_t paddr;
	व्योम *addr;

	addr = kदो_स्मृति(size, flag);
	अगर (!addr) अणु
		*dma_addr = DMA_MAPPING_ERROR;
		वापस शून्य;
	पूर्ण

	paddr = virt_to_phys(addr);

	*dma_addr = vdpasim_map_range(vdpasim, paddr, size, VHOST_MAP_RW);
	अगर (*dma_addr == DMA_MAPPING_ERROR) अणु
		kमुक्त(addr);
		वापस शून्य;
	पूर्ण

	वापस addr;
पूर्ण

अटल व्योम vdpasim_मुक्त_coherent(काष्ठा device *dev, माप_प्रकार size,
				  व्योम *vaddr, dma_addr_t dma_addr,
				  अचिन्हित दीर्घ attrs)
अणु
	काष्ठा vdpasim *vdpasim = dev_to_sim(dev);

	vdpasim_unmap_range(vdpasim, dma_addr, size);

	kमुक्त(vaddr);
पूर्ण

अटल स्थिर काष्ठा dma_map_ops vdpasim_dma_ops = अणु
	.map_page = vdpasim_map_page,
	.unmap_page = vdpasim_unmap_page,
	.alloc = vdpasim_alloc_coherent,
	.मुक्त = vdpasim_मुक्त_coherent,
पूर्ण;

अटल स्थिर काष्ठा vdpa_config_ops vdpasim_config_ops;
अटल स्थिर काष्ठा vdpa_config_ops vdpasim_batch_config_ops;

काष्ठा vdpasim *vdpasim_create(काष्ठा vdpasim_dev_attr *dev_attr)
अणु
	स्थिर काष्ठा vdpa_config_ops *ops;
	काष्ठा vdpasim *vdpasim;
	काष्ठा device *dev;
	पूर्णांक i, ret = -ENOMEM;

	अगर (batch_mapping)
		ops = &vdpasim_batch_config_ops;
	अन्यथा
		ops = &vdpasim_config_ops;

	vdpasim = vdpa_alloc_device(काष्ठा vdpasim, vdpa, शून्य, ops,
				    dev_attr->name);
	अगर (!vdpasim)
		जाओ err_alloc;

	vdpasim->dev_attr = *dev_attr;
	INIT_WORK(&vdpasim->work, dev_attr->work_fn);
	spin_lock_init(&vdpasim->lock);
	spin_lock_init(&vdpasim->iommu_lock);

	dev = &vdpasim->vdpa.dev;
	dev->dma_mask = &dev->coherent_dma_mask;
	अगर (dma_set_mask_and_coherent(dev, DMA_BIT_MASK(64)))
		जाओ err_iommu;
	set_dma_ops(dev, &vdpasim_dma_ops);
	vdpasim->vdpa.mdev = dev_attr->mgmt_dev;

	vdpasim->config = kzalloc(dev_attr->config_size, GFP_KERNEL);
	अगर (!vdpasim->config)
		जाओ err_iommu;

	vdpasim->vqs = kसुस्मृति(dev_attr->nvqs, माप(काष्ठा vdpasim_virtqueue),
			       GFP_KERNEL);
	अगर (!vdpasim->vqs)
		जाओ err_iommu;

	vdpasim->iommu = vhost_iotlb_alloc(max_iotlb_entries, 0);
	अगर (!vdpasim->iommu)
		जाओ err_iommu;

	vdpasim->buffer = kvदो_स्मृति(dev_attr->buffer_size, GFP_KERNEL);
	अगर (!vdpasim->buffer)
		जाओ err_iommu;

	क्रम (i = 0; i < dev_attr->nvqs; i++)
		vringh_set_iotlb(&vdpasim->vqs[i].vring, vdpasim->iommu,
				 &vdpasim->iommu_lock);

	ret = iova_cache_get();
	अगर (ret)
		जाओ err_iommu;

	/* For simplicity we use an IOVA allocator with byte granularity */
	init_iova_करोमुख्य(&vdpasim->iova, 1, 0);

	vdpasim->vdpa.dma_dev = dev;

	वापस vdpasim;

err_iommu:
	put_device(dev);
err_alloc:
	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL_GPL(vdpasim_create);

अटल पूर्णांक vdpasim_set_vq_address(काष्ठा vdpa_device *vdpa, u16 idx,
				  u64 desc_area, u64 driver_area,
				  u64 device_area)
अणु
	काष्ठा vdpasim *vdpasim = vdpa_to_sim(vdpa);
	काष्ठा vdpasim_virtqueue *vq = &vdpasim->vqs[idx];

	vq->desc_addr = desc_area;
	vq->driver_addr = driver_area;
	vq->device_addr = device_area;

	वापस 0;
पूर्ण

अटल व्योम vdpasim_set_vq_num(काष्ठा vdpa_device *vdpa, u16 idx, u32 num)
अणु
	काष्ठा vdpasim *vdpasim = vdpa_to_sim(vdpa);
	काष्ठा vdpasim_virtqueue *vq = &vdpasim->vqs[idx];

	vq->num = num;
पूर्ण

अटल व्योम vdpasim_kick_vq(काष्ठा vdpa_device *vdpa, u16 idx)
अणु
	काष्ठा vdpasim *vdpasim = vdpa_to_sim(vdpa);
	काष्ठा vdpasim_virtqueue *vq = &vdpasim->vqs[idx];

	अगर (vq->पढ़ोy)
		schedule_work(&vdpasim->work);
पूर्ण

अटल व्योम vdpasim_set_vq_cb(काष्ठा vdpa_device *vdpa, u16 idx,
			      काष्ठा vdpa_callback *cb)
अणु
	काष्ठा vdpasim *vdpasim = vdpa_to_sim(vdpa);
	काष्ठा vdpasim_virtqueue *vq = &vdpasim->vqs[idx];

	vq->cb = cb->callback;
	vq->निजी = cb->निजी;
पूर्ण

अटल व्योम vdpasim_set_vq_पढ़ोy(काष्ठा vdpa_device *vdpa, u16 idx, bool पढ़ोy)
अणु
	काष्ठा vdpasim *vdpasim = vdpa_to_sim(vdpa);
	काष्ठा vdpasim_virtqueue *vq = &vdpasim->vqs[idx];

	spin_lock(&vdpasim->lock);
	vq->पढ़ोy = पढ़ोy;
	अगर (vq->पढ़ोy)
		vdpasim_queue_पढ़ोy(vdpasim, idx);
	spin_unlock(&vdpasim->lock);
पूर्ण

अटल bool vdpasim_get_vq_पढ़ोy(काष्ठा vdpa_device *vdpa, u16 idx)
अणु
	काष्ठा vdpasim *vdpasim = vdpa_to_sim(vdpa);
	काष्ठा vdpasim_virtqueue *vq = &vdpasim->vqs[idx];

	वापस vq->पढ़ोy;
पूर्ण

अटल पूर्णांक vdpasim_set_vq_state(काष्ठा vdpa_device *vdpa, u16 idx,
				स्थिर काष्ठा vdpa_vq_state *state)
अणु
	काष्ठा vdpasim *vdpasim = vdpa_to_sim(vdpa);
	काष्ठा vdpasim_virtqueue *vq = &vdpasim->vqs[idx];
	काष्ठा vringh *vrh = &vq->vring;

	spin_lock(&vdpasim->lock);
	vrh->last_avail_idx = state->avail_index;
	spin_unlock(&vdpasim->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक vdpasim_get_vq_state(काष्ठा vdpa_device *vdpa, u16 idx,
				काष्ठा vdpa_vq_state *state)
अणु
	काष्ठा vdpasim *vdpasim = vdpa_to_sim(vdpa);
	काष्ठा vdpasim_virtqueue *vq = &vdpasim->vqs[idx];
	काष्ठा vringh *vrh = &vq->vring;

	state->avail_index = vrh->last_avail_idx;
	वापस 0;
पूर्ण

अटल u32 vdpasim_get_vq_align(काष्ठा vdpa_device *vdpa)
अणु
	वापस VDPASIM_QUEUE_ALIGN;
पूर्ण

अटल u64 vdpasim_get_features(काष्ठा vdpa_device *vdpa)
अणु
	काष्ठा vdpasim *vdpasim = vdpa_to_sim(vdpa);

	वापस vdpasim->dev_attr.supported_features;
पूर्ण

अटल पूर्णांक vdpasim_set_features(काष्ठा vdpa_device *vdpa, u64 features)
अणु
	काष्ठा vdpasim *vdpasim = vdpa_to_sim(vdpa);

	/* DMA mapping must be करोne by driver */
	अगर (!(features & (1ULL << VIRTIO_F_ACCESS_PLATFORM)))
		वापस -EINVAL;

	vdpasim->features = features & vdpasim->dev_attr.supported_features;

	वापस 0;
पूर्ण

अटल व्योम vdpasim_set_config_cb(काष्ठा vdpa_device *vdpa,
				  काष्ठा vdpa_callback *cb)
अणु
	/* We करोn't support config पूर्णांकerrupt */
पूर्ण

अटल u16 vdpasim_get_vq_num_max(काष्ठा vdpa_device *vdpa)
अणु
	वापस VDPASIM_QUEUE_MAX;
पूर्ण

अटल u32 vdpasim_get_device_id(काष्ठा vdpa_device *vdpa)
अणु
	काष्ठा vdpasim *vdpasim = vdpa_to_sim(vdpa);

	वापस vdpasim->dev_attr.id;
पूर्ण

अटल u32 vdpasim_get_venकरोr_id(काष्ठा vdpa_device *vdpa)
अणु
	वापस VDPASIM_VENDOR_ID;
पूर्ण

अटल u8 vdpasim_get_status(काष्ठा vdpa_device *vdpa)
अणु
	काष्ठा vdpasim *vdpasim = vdpa_to_sim(vdpa);
	u8 status;

	spin_lock(&vdpasim->lock);
	status = vdpasim->status;
	spin_unlock(&vdpasim->lock);

	वापस status;
पूर्ण

अटल व्योम vdpasim_set_status(काष्ठा vdpa_device *vdpa, u8 status)
अणु
	काष्ठा vdpasim *vdpasim = vdpa_to_sim(vdpa);

	spin_lock(&vdpasim->lock);
	vdpasim->status = status;
	अगर (status == 0)
		vdpasim_reset(vdpasim);
	spin_unlock(&vdpasim->lock);
पूर्ण

अटल माप_प्रकार vdpasim_get_config_size(काष्ठा vdpa_device *vdpa)
अणु
	काष्ठा vdpasim *vdpasim = vdpa_to_sim(vdpa);

	वापस vdpasim->dev_attr.config_size;
पूर्ण

अटल व्योम vdpasim_get_config(काष्ठा vdpa_device *vdpa, अचिन्हित पूर्णांक offset,
			     व्योम *buf, अचिन्हित पूर्णांक len)
अणु
	काष्ठा vdpasim *vdpasim = vdpa_to_sim(vdpa);

	अगर (offset + len > vdpasim->dev_attr.config_size)
		वापस;

	अगर (vdpasim->dev_attr.get_config)
		vdpasim->dev_attr.get_config(vdpasim, vdpasim->config);

	स_नकल(buf, vdpasim->config + offset, len);
पूर्ण

अटल व्योम vdpasim_set_config(काष्ठा vdpa_device *vdpa, अचिन्हित पूर्णांक offset,
			     स्थिर व्योम *buf, अचिन्हित पूर्णांक len)
अणु
	काष्ठा vdpasim *vdpasim = vdpa_to_sim(vdpa);

	अगर (offset + len > vdpasim->dev_attr.config_size)
		वापस;

	स_नकल(vdpasim->config + offset, buf, len);

	अगर (vdpasim->dev_attr.set_config)
		vdpasim->dev_attr.set_config(vdpasim, vdpasim->config);
पूर्ण

अटल u32 vdpasim_get_generation(काष्ठा vdpa_device *vdpa)
अणु
	काष्ठा vdpasim *vdpasim = vdpa_to_sim(vdpa);

	वापस vdpasim->generation;
पूर्ण

अटल काष्ठा vdpa_iova_range vdpasim_get_iova_range(काष्ठा vdpa_device *vdpa)
अणु
	काष्ठा vdpa_iova_range range = अणु
		.first = 0ULL,
		.last = ULदीर्घ_उच्च,
	पूर्ण;

	वापस range;
पूर्ण

अटल पूर्णांक vdpasim_set_map(काष्ठा vdpa_device *vdpa,
			   काष्ठा vhost_iotlb *iotlb)
अणु
	काष्ठा vdpasim *vdpasim = vdpa_to_sim(vdpa);
	काष्ठा vhost_iotlb_map *map;
	u64 start = 0ULL, last = 0ULL - 1;
	पूर्णांक ret;

	spin_lock(&vdpasim->iommu_lock);
	vhost_iotlb_reset(vdpasim->iommu);

	क्रम (map = vhost_iotlb_itree_first(iotlb, start, last); map;
	     map = vhost_iotlb_itree_next(map, start, last)) अणु
		ret = vhost_iotlb_add_range(vdpasim->iommu, map->start,
					    map->last, map->addr, map->perm);
		अगर (ret)
			जाओ err;
	पूर्ण
	spin_unlock(&vdpasim->iommu_lock);
	वापस 0;

err:
	vhost_iotlb_reset(vdpasim->iommu);
	spin_unlock(&vdpasim->iommu_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक vdpasim_dma_map(काष्ठा vdpa_device *vdpa, u64 iova, u64 size,
			   u64 pa, u32 perm)
अणु
	काष्ठा vdpasim *vdpasim = vdpa_to_sim(vdpa);
	पूर्णांक ret;

	spin_lock(&vdpasim->iommu_lock);
	ret = vhost_iotlb_add_range(vdpasim->iommu, iova, iova + size - 1, pa,
				    perm);
	spin_unlock(&vdpasim->iommu_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक vdpasim_dma_unmap(काष्ठा vdpa_device *vdpa, u64 iova, u64 size)
अणु
	काष्ठा vdpasim *vdpasim = vdpa_to_sim(vdpa);

	spin_lock(&vdpasim->iommu_lock);
	vhost_iotlb_del_range(vdpasim->iommu, iova, iova + size - 1);
	spin_unlock(&vdpasim->iommu_lock);

	वापस 0;
पूर्ण

अटल व्योम vdpasim_मुक्त(काष्ठा vdpa_device *vdpa)
अणु
	काष्ठा vdpasim *vdpasim = vdpa_to_sim(vdpa);
	पूर्णांक i;

	cancel_work_sync(&vdpasim->work);

	क्रम (i = 0; i < vdpasim->dev_attr.nvqs; i++) अणु
		vringh_kiov_cleanup(&vdpasim->vqs[i].out_iov);
		vringh_kiov_cleanup(&vdpasim->vqs[i].in_iov);
	पूर्ण

	put_iova_करोमुख्य(&vdpasim->iova);
	iova_cache_put();
	kvमुक्त(vdpasim->buffer);
	अगर (vdpasim->iommu)
		vhost_iotlb_मुक्त(vdpasim->iommu);
	kमुक्त(vdpasim->vqs);
	kमुक्त(vdpasim->config);
पूर्ण

अटल स्थिर काष्ठा vdpa_config_ops vdpasim_config_ops = अणु
	.set_vq_address         = vdpasim_set_vq_address,
	.set_vq_num             = vdpasim_set_vq_num,
	.kick_vq                = vdpasim_kick_vq,
	.set_vq_cb              = vdpasim_set_vq_cb,
	.set_vq_पढ़ोy           = vdpasim_set_vq_पढ़ोy,
	.get_vq_पढ़ोy           = vdpasim_get_vq_पढ़ोy,
	.set_vq_state           = vdpasim_set_vq_state,
	.get_vq_state           = vdpasim_get_vq_state,
	.get_vq_align           = vdpasim_get_vq_align,
	.get_features           = vdpasim_get_features,
	.set_features           = vdpasim_set_features,
	.set_config_cb          = vdpasim_set_config_cb,
	.get_vq_num_max         = vdpasim_get_vq_num_max,
	.get_device_id          = vdpasim_get_device_id,
	.get_venकरोr_id          = vdpasim_get_venकरोr_id,
	.get_status             = vdpasim_get_status,
	.set_status             = vdpasim_set_status,
	.get_config_size        = vdpasim_get_config_size,
	.get_config             = vdpasim_get_config,
	.set_config             = vdpasim_set_config,
	.get_generation         = vdpasim_get_generation,
	.get_iova_range         = vdpasim_get_iova_range,
	.dma_map                = vdpasim_dma_map,
	.dma_unmap              = vdpasim_dma_unmap,
	.मुक्त                   = vdpasim_मुक्त,
पूर्ण;

अटल स्थिर काष्ठा vdpa_config_ops vdpasim_batch_config_ops = अणु
	.set_vq_address         = vdpasim_set_vq_address,
	.set_vq_num             = vdpasim_set_vq_num,
	.kick_vq                = vdpasim_kick_vq,
	.set_vq_cb              = vdpasim_set_vq_cb,
	.set_vq_पढ़ोy           = vdpasim_set_vq_पढ़ोy,
	.get_vq_पढ़ोy           = vdpasim_get_vq_पढ़ोy,
	.set_vq_state           = vdpasim_set_vq_state,
	.get_vq_state           = vdpasim_get_vq_state,
	.get_vq_align           = vdpasim_get_vq_align,
	.get_features           = vdpasim_get_features,
	.set_features           = vdpasim_set_features,
	.set_config_cb          = vdpasim_set_config_cb,
	.get_vq_num_max         = vdpasim_get_vq_num_max,
	.get_device_id          = vdpasim_get_device_id,
	.get_venकरोr_id          = vdpasim_get_venकरोr_id,
	.get_status             = vdpasim_get_status,
	.set_status             = vdpasim_set_status,
	.get_config_size        = vdpasim_get_config_size,
	.get_config             = vdpasim_get_config,
	.set_config             = vdpasim_set_config,
	.get_generation         = vdpasim_get_generation,
	.get_iova_range         = vdpasim_get_iova_range,
	.set_map                = vdpasim_set_map,
	.मुक्त                   = vdpasim_मुक्त,
पूर्ण;

MODULE_VERSION(DRV_VERSION);
MODULE_LICENSE(DRV_LICENSE);
MODULE_AUTHOR(DRV_AUTHOR);
MODULE_DESCRIPTION(DRV_DESC);
