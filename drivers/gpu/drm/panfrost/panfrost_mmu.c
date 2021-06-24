<शैली गुरु>
// SPDX-License-Identअगरier:	GPL-2.0
/* Copyright 2019 Linaro, Ltd, Rob Herring <robh@kernel.org> */
#समावेश <linux/atomic.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/io-pgtable.h>
#समावेश <linux/iommu.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/shmem_fs.h>
#समावेश <linux/sizes.h>

#समावेश "panfrost_device.h"
#समावेश "panfrost_mmu.h"
#समावेश "panfrost_gem.h"
#समावेश "panfrost_features.h"
#समावेश "panfrost_regs.h"

#घोषणा mmu_ग_लिखो(dev, reg, data) ग_लिखोl(data, dev->iomem + reg)
#घोषणा mmu_पढ़ो(dev, reg) पढ़ोl(dev->iomem + reg)

अटल पूर्णांक रुको_पढ़ोy(काष्ठा panfrost_device *pfdev, u32 as_nr)
अणु
	पूर्णांक ret;
	u32 val;

	/* Wait क्रम the MMU status to indicate there is no active command, in
	 * हाल one is pending. */
	ret = पढ़ोl_relaxed_poll_समयout_atomic(pfdev->iomem + AS_STATUS(as_nr),
		val, !(val & AS_STATUS_AS_ACTIVE), 10, 1000);

	अगर (ret)
		dev_err(pfdev->dev, "AS_ACTIVE bit stuck\n");

	वापस ret;
पूर्ण

अटल पूर्णांक ग_लिखो_cmd(काष्ठा panfrost_device *pfdev, u32 as_nr, u32 cmd)
अणु
	पूर्णांक status;

	/* ग_लिखो AS_COMMAND when MMU is पढ़ोy to accept another command */
	status = रुको_पढ़ोy(pfdev, as_nr);
	अगर (!status)
		mmu_ग_लिखो(pfdev, AS_COMMAND(as_nr), cmd);

	वापस status;
पूर्ण

अटल व्योम lock_region(काष्ठा panfrost_device *pfdev, u32 as_nr,
			u64 iova, माप_प्रकार size)
अणु
	u8 region_width;
	u64 region = iova & PAGE_MASK;
	/*
	 * fls वापसs:
	 * 1 .. 32
	 *
	 * 10 + fls(num_pages)
	 * results in the range (11 .. 42)
	 */

	size = round_up(size, PAGE_SIZE);

	region_width = 10 + fls(size >> PAGE_SHIFT);
	अगर ((size >> PAGE_SHIFT) != (1ul << (region_width - 11))) अणु
		/* not घात2, so must go up to the next घात2 */
		region_width += 1;
	पूर्ण
	region |= region_width;

	/* Lock the region that needs to be updated */
	mmu_ग_लिखो(pfdev, AS_LOCKADDR_LO(as_nr), region & 0xFFFFFFFFUL);
	mmu_ग_लिखो(pfdev, AS_LOCKADDR_HI(as_nr), (region >> 32) & 0xFFFFFFFFUL);
	ग_लिखो_cmd(pfdev, as_nr, AS_COMMAND_LOCK);
पूर्ण


अटल पूर्णांक mmu_hw_करो_operation_locked(काष्ठा panfrost_device *pfdev, पूर्णांक as_nr,
				      u64 iova, माप_प्रकार size, u32 op)
अणु
	अगर (as_nr < 0)
		वापस 0;

	अगर (op != AS_COMMAND_UNLOCK)
		lock_region(pfdev, as_nr, iova, size);

	/* Run the MMU operation */
	ग_लिखो_cmd(pfdev, as_nr, op);

	/* Wait क्रम the flush to complete */
	वापस रुको_पढ़ोy(pfdev, as_nr);
पूर्ण

अटल पूर्णांक mmu_hw_करो_operation(काष्ठा panfrost_device *pfdev,
			       काष्ठा panfrost_mmu *mmu,
			       u64 iova, माप_प्रकार size, u32 op)
अणु
	पूर्णांक ret;

	spin_lock(&pfdev->as_lock);
	ret = mmu_hw_करो_operation_locked(pfdev, mmu->as, iova, size, op);
	spin_unlock(&pfdev->as_lock);
	वापस ret;
पूर्ण

अटल व्योम panfrost_mmu_enable(काष्ठा panfrost_device *pfdev, काष्ठा panfrost_mmu *mmu)
अणु
	पूर्णांक as_nr = mmu->as;
	काष्ठा io_pgtable_cfg *cfg = &mmu->pgtbl_cfg;
	u64 transtab = cfg->arm_mali_lpae_cfg.transtab;
	u64 memattr = cfg->arm_mali_lpae_cfg.memattr;

	mmu_hw_करो_operation_locked(pfdev, as_nr, 0, ~0UL, AS_COMMAND_FLUSH_MEM);

	mmu_ग_लिखो(pfdev, AS_TRANSTAB_LO(as_nr), transtab & 0xffffffffUL);
	mmu_ग_लिखो(pfdev, AS_TRANSTAB_HI(as_nr), transtab >> 32);

	/* Need to revisit mem attrs.
	 * NC is the शेष, Mali driver is inner WT.
	 */
	mmu_ग_लिखो(pfdev, AS_MEMATTR_LO(as_nr), memattr & 0xffffffffUL);
	mmu_ग_लिखो(pfdev, AS_MEMATTR_HI(as_nr), memattr >> 32);

	ग_लिखो_cmd(pfdev, as_nr, AS_COMMAND_UPDATE);
पूर्ण

अटल व्योम panfrost_mmu_disable(काष्ठा panfrost_device *pfdev, u32 as_nr)
अणु
	mmu_hw_करो_operation_locked(pfdev, as_nr, 0, ~0UL, AS_COMMAND_FLUSH_MEM);

	mmu_ग_लिखो(pfdev, AS_TRANSTAB_LO(as_nr), 0);
	mmu_ग_लिखो(pfdev, AS_TRANSTAB_HI(as_nr), 0);

	mmu_ग_लिखो(pfdev, AS_MEMATTR_LO(as_nr), 0);
	mmu_ग_लिखो(pfdev, AS_MEMATTR_HI(as_nr), 0);

	ग_लिखो_cmd(pfdev, as_nr, AS_COMMAND_UPDATE);
पूर्ण

u32 panfrost_mmu_as_get(काष्ठा panfrost_device *pfdev, काष्ठा panfrost_mmu *mmu)
अणु
	पूर्णांक as;

	spin_lock(&pfdev->as_lock);

	as = mmu->as;
	अगर (as >= 0) अणु
		पूर्णांक en = atomic_inc_वापस(&mmu->as_count);

		/*
		 * AS can be retained by active jobs or a perfcnt context,
		 * hence the '+ 1' here.
		 */
		WARN_ON(en >= (NUM_JOB_SLOTS + 1));

		list_move(&mmu->list, &pfdev->as_lru_list);
		जाओ out;
	पूर्ण

	/* Check क्रम a मुक्त AS */
	as = ffz(pfdev->as_alloc_mask);
	अगर (!(BIT(as) & pfdev->features.as_present)) अणु
		काष्ठा panfrost_mmu *lru_mmu;

		list_क्रम_each_entry_reverse(lru_mmu, &pfdev->as_lru_list, list) अणु
			अगर (!atomic_पढ़ो(&lru_mmu->as_count))
				अवरोध;
		पूर्ण
		WARN_ON(&lru_mmu->list == &pfdev->as_lru_list);

		list_del_init(&lru_mmu->list);
		as = lru_mmu->as;

		WARN_ON(as < 0);
		lru_mmu->as = -1;
	पूर्ण

	/* Assign the मुक्त or reclaimed AS to the FD */
	mmu->as = as;
	set_bit(as, &pfdev->as_alloc_mask);
	atomic_set(&mmu->as_count, 1);
	list_add(&mmu->list, &pfdev->as_lru_list);

	dev_dbg(pfdev->dev, "Assigned AS%d to mmu %p, alloc_mask=%lx", as, mmu, pfdev->as_alloc_mask);

	panfrost_mmu_enable(pfdev, mmu);

out:
	spin_unlock(&pfdev->as_lock);
	वापस as;
पूर्ण

व्योम panfrost_mmu_as_put(काष्ठा panfrost_device *pfdev, काष्ठा panfrost_mmu *mmu)
अणु
	atomic_dec(&mmu->as_count);
	WARN_ON(atomic_पढ़ो(&mmu->as_count) < 0);
पूर्ण

व्योम panfrost_mmu_reset(काष्ठा panfrost_device *pfdev)
अणु
	काष्ठा panfrost_mmu *mmu, *mmu_पंचांगp;

	spin_lock(&pfdev->as_lock);

	pfdev->as_alloc_mask = 0;

	list_क्रम_each_entry_safe(mmu, mmu_पंचांगp, &pfdev->as_lru_list, list) अणु
		mmu->as = -1;
		atomic_set(&mmu->as_count, 0);
		list_del_init(&mmu->list);
	पूर्ण

	spin_unlock(&pfdev->as_lock);

	mmu_ग_लिखो(pfdev, MMU_INT_CLEAR, ~0);
	mmu_ग_लिखो(pfdev, MMU_INT_MASK, ~0);
पूर्ण

अटल माप_प्रकार get_pgsize(u64 addr, माप_प्रकार size)
अणु
	अगर (addr & (SZ_2M - 1) || size < SZ_2M)
		वापस SZ_4K;

	वापस SZ_2M;
पूर्ण

अटल व्योम panfrost_mmu_flush_range(काष्ठा panfrost_device *pfdev,
				     काष्ठा panfrost_mmu *mmu,
				     u64 iova, माप_प्रकार size)
अणु
	अगर (mmu->as < 0)
		वापस;

	pm_runसमय_get_noresume(pfdev->dev);

	/* Flush the PTs only अगर we're alपढ़ोy awake */
	अगर (pm_runसमय_active(pfdev->dev))
		mmu_hw_करो_operation(pfdev, mmu, iova, size, AS_COMMAND_FLUSH_PT);

	pm_runसमय_put_sync_स्वतःsuspend(pfdev->dev);
पूर्ण

अटल पूर्णांक mmu_map_sg(काष्ठा panfrost_device *pfdev, काष्ठा panfrost_mmu *mmu,
		      u64 iova, पूर्णांक prot, काष्ठा sg_table *sgt)
अणु
	अचिन्हित पूर्णांक count;
	काष्ठा scatterlist *sgl;
	काष्ठा io_pgtable_ops *ops = mmu->pgtbl_ops;
	u64 start_iova = iova;

	क्रम_each_sgtable_dma_sg(sgt, sgl, count) अणु
		अचिन्हित दीर्घ paddr = sg_dma_address(sgl);
		माप_प्रकार len = sg_dma_len(sgl);

		dev_dbg(pfdev->dev, "map: as=%d, iova=%llx, paddr=%lx, len=%zx", mmu->as, iova, paddr, len);

		जबतक (len) अणु
			माप_प्रकार pgsize = get_pgsize(iova | paddr, len);

			ops->map(ops, iova, paddr, pgsize, prot, GFP_KERNEL);
			iova += pgsize;
			paddr += pgsize;
			len -= pgsize;
		पूर्ण
	पूर्ण

	panfrost_mmu_flush_range(pfdev, mmu, start_iova, iova - start_iova);

	वापस 0;
पूर्ण

पूर्णांक panfrost_mmu_map(काष्ठा panfrost_gem_mapping *mapping)
अणु
	काष्ठा panfrost_gem_object *bo = mapping->obj;
	काष्ठा drm_gem_object *obj = &bo->base.base;
	काष्ठा panfrost_device *pfdev = to_panfrost_device(obj->dev);
	काष्ठा sg_table *sgt;
	पूर्णांक prot = IOMMU_READ | IOMMU_WRITE;

	अगर (WARN_ON(mapping->active))
		वापस 0;

	अगर (bo->noexec)
		prot |= IOMMU_NOEXEC;

	sgt = drm_gem_shmem_get_pages_sgt(obj);
	अगर (WARN_ON(IS_ERR(sgt)))
		वापस PTR_ERR(sgt);

	mmu_map_sg(pfdev, mapping->mmu, mapping->mmnode.start << PAGE_SHIFT,
		   prot, sgt);
	mapping->active = true;

	वापस 0;
पूर्ण

व्योम panfrost_mmu_unmap(काष्ठा panfrost_gem_mapping *mapping)
अणु
	काष्ठा panfrost_gem_object *bo = mapping->obj;
	काष्ठा drm_gem_object *obj = &bo->base.base;
	काष्ठा panfrost_device *pfdev = to_panfrost_device(obj->dev);
	काष्ठा io_pgtable_ops *ops = mapping->mmu->pgtbl_ops;
	u64 iova = mapping->mmnode.start << PAGE_SHIFT;
	माप_प्रकार len = mapping->mmnode.size << PAGE_SHIFT;
	माप_प्रकार unmapped_len = 0;

	अगर (WARN_ON(!mapping->active))
		वापस;

	dev_dbg(pfdev->dev, "unmap: as=%d, iova=%llx, len=%zx",
		mapping->mmu->as, iova, len);

	जबतक (unmapped_len < len) अणु
		माप_प्रकार unmapped_page;
		माप_प्रकार pgsize = get_pgsize(iova, len - unmapped_len);

		अगर (ops->iova_to_phys(ops, iova)) अणु
			unmapped_page = ops->unmap(ops, iova, pgsize, शून्य);
			WARN_ON(unmapped_page != pgsize);
		पूर्ण
		iova += pgsize;
		unmapped_len += pgsize;
	पूर्ण

	panfrost_mmu_flush_range(pfdev, mapping->mmu,
				 mapping->mmnode.start << PAGE_SHIFT, len);
	mapping->active = false;
पूर्ण

अटल व्योम mmu_tlb_inv_context_s1(व्योम *cookie)
अणुपूर्ण

अटल व्योम mmu_tlb_sync_context(व्योम *cookie)
अणु
	//काष्ठा panfrost_device *pfdev = cookie;
	// TODO: Wait 1000 GPU cycles क्रम HW_ISSUE_6367/T60X
पूर्ण

अटल व्योम mmu_tlb_flush_walk(अचिन्हित दीर्घ iova, माप_प्रकार size, माप_प्रकार granule,
			       व्योम *cookie)
अणु
	mmu_tlb_sync_context(cookie);
पूर्ण

अटल स्थिर काष्ठा iommu_flush_ops mmu_tlb_ops = अणु
	.tlb_flush_all	= mmu_tlb_inv_context_s1,
	.tlb_flush_walk = mmu_tlb_flush_walk,
पूर्ण;

पूर्णांक panfrost_mmu_pgtable_alloc(काष्ठा panfrost_file_priv *priv)
अणु
	काष्ठा panfrost_mmu *mmu = &priv->mmu;
	काष्ठा panfrost_device *pfdev = priv->pfdev;

	INIT_LIST_HEAD(&mmu->list);
	mmu->as = -1;

	mmu->pgtbl_cfg = (काष्ठा io_pgtable_cfg) अणु
		.pgsize_biपंचांगap	= SZ_4K | SZ_2M,
		.ias		= FIELD_GET(0xff, pfdev->features.mmu_features),
		.oas		= FIELD_GET(0xff00, pfdev->features.mmu_features),
		.coherent_walk	= pfdev->coherent,
		.tlb		= &mmu_tlb_ops,
		.iommu_dev	= pfdev->dev,
	पूर्ण;

	mmu->pgtbl_ops = alloc_io_pgtable_ops(ARM_MALI_LPAE, &mmu->pgtbl_cfg,
					      priv);
	अगर (!mmu->pgtbl_ops)
		वापस -EINVAL;

	वापस 0;
पूर्ण

व्योम panfrost_mmu_pgtable_मुक्त(काष्ठा panfrost_file_priv *priv)
अणु
	काष्ठा panfrost_device *pfdev = priv->pfdev;
	काष्ठा panfrost_mmu *mmu = &priv->mmu;

	spin_lock(&pfdev->as_lock);
	अगर (mmu->as >= 0) अणु
		pm_runसमय_get_noresume(pfdev->dev);
		अगर (pm_runसमय_active(pfdev->dev))
			panfrost_mmu_disable(pfdev, mmu->as);
		pm_runसमय_put_स्वतःsuspend(pfdev->dev);

		clear_bit(mmu->as, &pfdev->as_alloc_mask);
		clear_bit(mmu->as, &pfdev->as_in_use_mask);
		list_del(&mmu->list);
	पूर्ण
	spin_unlock(&pfdev->as_lock);

	मुक्त_io_pgtable_ops(mmu->pgtbl_ops);
पूर्ण

अटल काष्ठा panfrost_gem_mapping *
addr_to_mapping(काष्ठा panfrost_device *pfdev, पूर्णांक as, u64 addr)
अणु
	काष्ठा panfrost_gem_mapping *mapping = शून्य;
	काष्ठा panfrost_file_priv *priv;
	काष्ठा drm_mm_node *node;
	u64 offset = addr >> PAGE_SHIFT;
	काष्ठा panfrost_mmu *mmu;

	spin_lock(&pfdev->as_lock);
	list_क्रम_each_entry(mmu, &pfdev->as_lru_list, list) अणु
		अगर (as == mmu->as)
			जाओ found_mmu;
	पूर्ण
	जाओ out;

found_mmu:
	priv = container_of(mmu, काष्ठा panfrost_file_priv, mmu);

	spin_lock(&priv->mm_lock);

	drm_mm_क्रम_each_node(node, &priv->mm) अणु
		अगर (offset >= node->start &&
		    offset < (node->start + node->size)) अणु
			mapping = drm_mm_node_to_panfrost_mapping(node);

			kref_get(&mapping->refcount);
			अवरोध;
		पूर्ण
	पूर्ण

	spin_unlock(&priv->mm_lock);
out:
	spin_unlock(&pfdev->as_lock);
	वापस mapping;
पूर्ण

#घोषणा NUM_FAULT_PAGES (SZ_2M / PAGE_SIZE)

अटल पूर्णांक panfrost_mmu_map_fault_addr(काष्ठा panfrost_device *pfdev, पूर्णांक as,
				       u64 addr)
अणु
	पूर्णांक ret, i;
	काष्ठा panfrost_gem_mapping *bomapping;
	काष्ठा panfrost_gem_object *bo;
	काष्ठा address_space *mapping;
	pgoff_t page_offset;
	काष्ठा sg_table *sgt;
	काष्ठा page **pages;

	bomapping = addr_to_mapping(pfdev, as, addr);
	अगर (!bomapping)
		वापस -ENOENT;

	bo = bomapping->obj;
	अगर (!bo->is_heap) अणु
		dev_WARN(pfdev->dev, "matching BO is not heap type (GPU VA = %llx)",
			 bomapping->mmnode.start << PAGE_SHIFT);
		ret = -EINVAL;
		जाओ err_bo;
	पूर्ण
	WARN_ON(bomapping->mmu->as != as);

	/* Assume 2MB alignment and size multiple */
	addr &= ~((u64)SZ_2M - 1);
	page_offset = addr >> PAGE_SHIFT;
	page_offset -= bomapping->mmnode.start;

	mutex_lock(&bo->base.pages_lock);

	अगर (!bo->base.pages) अणु
		bo->sgts = kvदो_स्मृति_array(bo->base.base.size / SZ_2M,
				     माप(काष्ठा sg_table), GFP_KERNEL | __GFP_ZERO);
		अगर (!bo->sgts) अणु
			mutex_unlock(&bo->base.pages_lock);
			ret = -ENOMEM;
			जाओ err_bo;
		पूर्ण

		pages = kvदो_स्मृति_array(bo->base.base.size >> PAGE_SHIFT,
				       माप(काष्ठा page *), GFP_KERNEL | __GFP_ZERO);
		अगर (!pages) अणु
			kvमुक्त(bo->sgts);
			bo->sgts = शून्य;
			mutex_unlock(&bo->base.pages_lock);
			ret = -ENOMEM;
			जाओ err_bo;
		पूर्ण
		bo->base.pages = pages;
		bo->base.pages_use_count = 1;
	पूर्ण अन्यथा अणु
		pages = bo->base.pages;
		अगर (pages[page_offset]) अणु
			/* Pages are alपढ़ोy mapped, bail out. */
			mutex_unlock(&bo->base.pages_lock);
			जाओ out;
		पूर्ण
	पूर्ण

	mapping = bo->base.base.filp->f_mapping;
	mapping_set_unevictable(mapping);

	क्रम (i = page_offset; i < page_offset + NUM_FAULT_PAGES; i++) अणु
		pages[i] = shmem_पढ़ो_mapping_page(mapping, i);
		अगर (IS_ERR(pages[i])) अणु
			mutex_unlock(&bo->base.pages_lock);
			ret = PTR_ERR(pages[i]);
			जाओ err_pages;
		पूर्ण
	पूर्ण

	mutex_unlock(&bo->base.pages_lock);

	sgt = &bo->sgts[page_offset / (SZ_2M / PAGE_SIZE)];
	ret = sg_alloc_table_from_pages(sgt, pages + page_offset,
					NUM_FAULT_PAGES, 0, SZ_2M, GFP_KERNEL);
	अगर (ret)
		जाओ err_pages;

	ret = dma_map_sgtable(pfdev->dev, sgt, DMA_BIसूचीECTIONAL, 0);
	अगर (ret)
		जाओ err_map;

	mmu_map_sg(pfdev, bomapping->mmu, addr,
		   IOMMU_WRITE | IOMMU_READ | IOMMU_NOEXEC, sgt);

	bomapping->active = true;

	dev_dbg(pfdev->dev, "mapped page fault @ AS%d %llx", as, addr);

out:
	panfrost_gem_mapping_put(bomapping);

	वापस 0;

err_map:
	sg_मुक्त_table(sgt);
err_pages:
	drm_gem_shmem_put_pages(&bo->base);
err_bo:
	drm_gem_object_put(&bo->base.base);
	वापस ret;
पूर्ण

अटल स्थिर अक्षर *access_type_name(काष्ठा panfrost_device *pfdev,
		u32 fault_status)
अणु
	चयन (fault_status & AS_FAULTSTATUS_ACCESS_TYPE_MASK) अणु
	हाल AS_FAULTSTATUS_ACCESS_TYPE_ATOMIC:
		अगर (panfrost_has_hw_feature(pfdev, HW_FEATURE_AARCH64_MMU))
			वापस "ATOMIC";
		अन्यथा
			वापस "UNKNOWN";
	हाल AS_FAULTSTATUS_ACCESS_TYPE_READ:
		वापस "READ";
	हाल AS_FAULTSTATUS_ACCESS_TYPE_WRITE:
		वापस "WRITE";
	हाल AS_FAULTSTATUS_ACCESS_TYPE_EX:
		वापस "EXECUTE";
	शेष:
		WARN_ON(1);
		वापस शून्य;
	पूर्ण
पूर्ण

अटल irqवापस_t panfrost_mmu_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा panfrost_device *pfdev = data;

	अगर (!mmu_पढ़ो(pfdev, MMU_INT_STAT))
		वापस IRQ_NONE;

	mmu_ग_लिखो(pfdev, MMU_INT_MASK, 0);
	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल irqवापस_t panfrost_mmu_irq_handler_thपढ़ो(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा panfrost_device *pfdev = data;
	u32 status = mmu_पढ़ो(pfdev, MMU_INT_RAWSTAT);
	पूर्णांक ret;

	जबतक (status) अणु
		u32 as = ffs(status | (status >> 16)) - 1;
		u32 mask = BIT(as) | BIT(as + 16);
		u64 addr;
		u32 fault_status;
		u32 exception_type;
		u32 access_type;
		u32 source_id;

		fault_status = mmu_पढ़ो(pfdev, AS_FAULTSTATUS(as));
		addr = mmu_पढ़ो(pfdev, AS_FAULTADDRESS_LO(as));
		addr |= (u64)mmu_पढ़ो(pfdev, AS_FAULTADDRESS_HI(as)) << 32;

		/* decode the fault status */
		exception_type = fault_status & 0xFF;
		access_type = (fault_status >> 8) & 0x3;
		source_id = (fault_status >> 16);

		mmu_ग_लिखो(pfdev, MMU_INT_CLEAR, mask);

		/* Page fault only */
		ret = -1;
		अगर ((status & mask) == BIT(as) && (exception_type & 0xF8) == 0xC0)
			ret = panfrost_mmu_map_fault_addr(pfdev, as, addr);

		अगर (ret)
			/* terminal fault, prपूर्णांक info about the fault */
			dev_err(pfdev->dev,
				"Unhandled Page fault in AS%d at VA 0x%016llX\n"
				"Reason: %s\n"
				"raw fault status: 0x%X\n"
				"decoded fault status: %s\n"
				"exception type 0x%X: %s\n"
				"access type 0x%X: %s\n"
				"source id 0x%X\n",
				as, addr,
				"TODO",
				fault_status,
				(fault_status & (1 << 10) ? "DECODER FAULT" : "SLAVE FAULT"),
				exception_type, panfrost_exception_name(pfdev, exception_type),
				access_type, access_type_name(pfdev, fault_status),
				source_id);

		status &= ~mask;

		/* If we received new MMU पूर्णांकerrupts, process them beक्रमe वापसing. */
		अगर (!status)
			status = mmu_पढ़ो(pfdev, MMU_INT_RAWSTAT);
	पूर्ण

	mmu_ग_लिखो(pfdev, MMU_INT_MASK, ~0);
	वापस IRQ_HANDLED;
पूर्ण;

पूर्णांक panfrost_mmu_init(काष्ठा panfrost_device *pfdev)
अणु
	पूर्णांक err, irq;

	irq = platक्रमm_get_irq_byname(to_platक्रमm_device(pfdev->dev), "mmu");
	अगर (irq <= 0)
		वापस -ENODEV;

	err = devm_request_thपढ़ोed_irq(pfdev->dev, irq,
					panfrost_mmu_irq_handler,
					panfrost_mmu_irq_handler_thपढ़ो,
					IRQF_SHARED, KBUILD_MODNAME "-mmu",
					pfdev);

	अगर (err) अणु
		dev_err(pfdev->dev, "failed to request mmu irq");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

व्योम panfrost_mmu_fini(काष्ठा panfrost_device *pfdev)
अणु
	mmu_ग_लिखो(pfdev, MMU_INT_MASK, 0);
पूर्ण
