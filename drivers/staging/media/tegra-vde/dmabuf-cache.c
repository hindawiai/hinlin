<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * NVIDIA Tegra Video decoder driver
 *
 * Copyright (C) 2016-2019 GRATE-DRIVER project
 */

#समावेश <linux/dma-buf.h>
#समावेश <linux/iova.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>

#समावेश "vde.h"

काष्ठा tegra_vde_cache_entry अणु
	क्रमागत dma_data_direction dma_dir;
	काष्ठा dma_buf_attachment *a;
	काष्ठा delayed_work dwork;
	काष्ठा tegra_vde *vde;
	काष्ठा list_head list;
	काष्ठा sg_table *sgt;
	काष्ठा iova *iova;
	अचिन्हित पूर्णांक refcnt;
पूर्ण;

अटल व्योम tegra_vde_release_entry(काष्ठा tegra_vde_cache_entry *entry)
अणु
	काष्ठा dma_buf *dmabuf = entry->a->dmabuf;

	WARN_ON_ONCE(entry->refcnt);

	अगर (entry->vde->करोमुख्य)
		tegra_vde_iommu_unmap(entry->vde, entry->iova);

	dma_buf_unmap_attachment(entry->a, entry->sgt, entry->dma_dir);
	dma_buf_detach(dmabuf, entry->a);
	dma_buf_put(dmabuf);

	list_del(&entry->list);
	kमुक्त(entry);
पूर्ण

अटल व्योम tegra_vde_delayed_unmap(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा tegra_vde_cache_entry *entry;
	काष्ठा tegra_vde *vde;

	entry = container_of(work, काष्ठा tegra_vde_cache_entry,
			     dwork.work);
	vde = entry->vde;

	mutex_lock(&vde->map_lock);
	tegra_vde_release_entry(entry);
	mutex_unlock(&vde->map_lock);
पूर्ण

पूर्णांक tegra_vde_dmabuf_cache_map(काष्ठा tegra_vde *vde,
			       काष्ठा dma_buf *dmabuf,
			       क्रमागत dma_data_direction dma_dir,
			       काष्ठा dma_buf_attachment **ap,
			       dma_addr_t *addrp)
अणु
	काष्ठा device *dev = vde->miscdev.parent;
	काष्ठा dma_buf_attachment *attachment;
	काष्ठा tegra_vde_cache_entry *entry;
	काष्ठा sg_table *sgt;
	काष्ठा iova *iova;
	पूर्णांक err;

	mutex_lock(&vde->map_lock);

	list_क्रम_each_entry(entry, &vde->map_list, list) अणु
		अगर (entry->a->dmabuf != dmabuf)
			जारी;

		अगर (!cancel_delayed_work(&entry->dwork))
			जारी;

		अगर (entry->dma_dir != dma_dir)
			entry->dma_dir = DMA_BIसूचीECTIONAL;

		dma_buf_put(dmabuf);

		अगर (vde->करोमुख्य)
			*addrp = iova_dma_addr(&vde->iova, entry->iova);
		अन्यथा
			*addrp = sg_dma_address(entry->sgt->sgl);

		जाओ ref;
	पूर्ण

	attachment = dma_buf_attach(dmabuf, dev);
	अगर (IS_ERR(attachment)) अणु
		dev_err(dev, "Failed to attach dmabuf\n");
		err = PTR_ERR(attachment);
		जाओ err_unlock;
	पूर्ण

	sgt = dma_buf_map_attachment(attachment, dma_dir);
	अगर (IS_ERR(sgt)) अणु
		dev_err(dev, "Failed to get dmabufs sg_table\n");
		err = PTR_ERR(sgt);
		जाओ err_detach;
	पूर्ण

	अगर (!vde->करोमुख्य && sgt->nents > 1) अणु
		dev_err(dev, "Sparse DMA region is unsupported, please enable IOMMU\n");
		err = -EINVAL;
		जाओ err_unmap;
	पूर्ण

	entry = kzalloc(माप(*entry), GFP_KERNEL);
	अगर (!entry) अणु
		err = -ENOMEM;
		जाओ err_unmap;
	पूर्ण

	अगर (vde->करोमुख्य) अणु
		err = tegra_vde_iommu_map(vde, sgt, &iova, dmabuf->size);
		अगर (err)
			जाओ err_मुक्त;

		*addrp = iova_dma_addr(&vde->iova, iova);
	पूर्ण अन्यथा अणु
		*addrp = sg_dma_address(sgt->sgl);
		iova = शून्य;
	पूर्ण

	INIT_DELAYED_WORK(&entry->dwork, tegra_vde_delayed_unmap);
	list_add(&entry->list, &vde->map_list);

	entry->dma_dir = dma_dir;
	entry->iova = iova;
	entry->vde = vde;
	entry->sgt = sgt;
	entry->a = attachment;
ref:
	entry->refcnt++;

	*ap = entry->a;

	mutex_unlock(&vde->map_lock);

	वापस 0;

err_मुक्त:
	kमुक्त(entry);
err_unmap:
	dma_buf_unmap_attachment(attachment, sgt, dma_dir);
err_detach:
	dma_buf_detach(dmabuf, attachment);
err_unlock:
	mutex_unlock(&vde->map_lock);

	वापस err;
पूर्ण

व्योम tegra_vde_dmabuf_cache_unmap(काष्ठा tegra_vde *vde,
				  काष्ठा dma_buf_attachment *a,
				  bool release)
अणु
	काष्ठा tegra_vde_cache_entry *entry;

	mutex_lock(&vde->map_lock);

	list_क्रम_each_entry(entry, &vde->map_list, list) अणु
		अगर (entry->a != a)
			जारी;

		WARN_ON_ONCE(!entry->refcnt);

		अगर (--entry->refcnt == 0) अणु
			अगर (release)
				tegra_vde_release_entry(entry);
			अन्यथा
				schedule_delayed_work(&entry->dwork, 5 * HZ);
		पूर्ण
		अवरोध;
	पूर्ण

	mutex_unlock(&vde->map_lock);
पूर्ण

व्योम tegra_vde_dmabuf_cache_unmap_sync(काष्ठा tegra_vde *vde)
अणु
	काष्ठा tegra_vde_cache_entry *entry, *पंचांगp;

	mutex_lock(&vde->map_lock);

	list_क्रम_each_entry_safe(entry, पंचांगp, &vde->map_list, list) अणु
		अगर (entry->refcnt)
			जारी;

		अगर (!cancel_delayed_work(&entry->dwork))
			जारी;

		tegra_vde_release_entry(entry);
	पूर्ण

	mutex_unlock(&vde->map_lock);
पूर्ण

व्योम tegra_vde_dmabuf_cache_unmap_all(काष्ठा tegra_vde *vde)
अणु
	काष्ठा tegra_vde_cache_entry *entry, *पंचांगp;

	mutex_lock(&vde->map_lock);

	जबतक (!list_empty(&vde->map_list)) अणु
		list_क्रम_each_entry_safe(entry, पंचांगp, &vde->map_list, list) अणु
			अगर (!cancel_delayed_work(&entry->dwork))
				जारी;

			tegra_vde_release_entry(entry);
		पूर्ण

		mutex_unlock(&vde->map_lock);
		schedule();
		mutex_lock(&vde->map_lock);
	पूर्ण

	mutex_unlock(&vde->map_lock);
पूर्ण
