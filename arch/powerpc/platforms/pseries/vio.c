<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * IBM PowerPC Virtual I/O Infraकाष्ठाure Support.
 *
 *    Copyright (c) 2003,2008 IBM Corp.
 *     Dave Engebretsen engebret@us.ibm.com
 *     Santiago Leon santil@us.ibm.com
 *     Hollis Blanअक्षरd <hollisb@us.ibm.com>
 *     Stephen Rothwell
 *     Robert Jennings <rcjenn@us.ibm.com>
 */

#समावेश <linux/cpu.h>
#समावेश <linux/types.h>
#समावेश <linux/delay.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/device.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/console.h>
#समावेश <linux/export.h>
#समावेश <linux/mm.h>
#समावेश <linux/dma-map-ops.h>
#समावेश <linux/kobject.h>
#समावेश <linux/kexec.h>

#समावेश <यंत्र/iommu.h>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/vपन.स>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/tce.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/hvcall.h>
#समावेश <यंत्र/machdep.h>

अटल काष्ठा vio_dev vio_bus_device  = अणु /* fake "parent" device */
	.name = "vio",
	.type = "",
	.dev.init_name = "vio",
	.dev.bus = &vio_bus_type,
पूर्ण;

#अगर_घोषित CONFIG_PPC_SMLPAR
/**
 * vio_cmo_pool - A pool of IO memory क्रम CMO use
 *
 * @size: The size of the pool in bytes
 * @मुक्त: The amount of मुक्त memory in the pool
 */
काष्ठा vio_cmo_pool अणु
	माप_प्रकार size;
	माप_प्रकार मुक्त;
पूर्ण;

/* How many ms to delay queued balance work */
#घोषणा VIO_CMO_BALANCE_DELAY 100

/* Portion out IO memory to CMO devices by this chunk size */
#घोषणा VIO_CMO_BALANCE_CHUNK 131072

/**
 * vio_cmo_dev_entry - A device that is CMO-enabled and requires entitlement
 *
 * @vio_dev: काष्ठा vio_dev poपूर्णांकer
 * @list: poपूर्णांकer to other devices on bus that are being tracked
 */
काष्ठा vio_cmo_dev_entry अणु
	काष्ठा vio_dev *viodev;
	काष्ठा list_head list;
पूर्ण;

/**
 * vio_cmo - VIO bus accounting काष्ठाure क्रम CMO entitlement
 *
 * @lock: spinlock क्रम entire काष्ठाure
 * @balance_q: work queue क्रम balancing प्रणाली entitlement
 * @device_list: list of CMO-enabled devices requiring entitlement
 * @entitled: total प्रणाली entitlement in bytes
 * @reserve: pool of memory from which devices reserve entitlement, incl. spare
 * @excess: pool of excess entitlement not needed क्रम device reserves or spare
 * @spare: IO memory क्रम device hotplug functionality
 * @min: minimum necessary क्रम प्रणाली operation
 * @desired: desired memory क्रम प्रणाली operation
 * @curr: bytes currently allocated
 * @high: high water mark क्रम IO data usage
 */
अटल काष्ठा vio_cmo अणु
	spinlock_t lock;
	काष्ठा delayed_work balance_q;
	काष्ठा list_head device_list;
	माप_प्रकार entitled;
	काष्ठा vio_cmo_pool reserve;
	काष्ठा vio_cmo_pool excess;
	माप_प्रकार spare;
	माप_प्रकार min;
	माप_प्रकार desired;
	माप_प्रकार curr;
	माप_प्रकार high;
पूर्ण vio_cmo;

/**
 * vio_cmo_OF_devices - Count the number of OF devices that have DMA winकरोws
 */
अटल पूर्णांक vio_cmo_num_OF_devs(व्योम)
अणु
	काष्ठा device_node *node_vroot;
	पूर्णांक count = 0;

	/*
	 * Count the number of vdevice entries with an
	 * ibm,my-dma-winकरोw OF property
	 */
	node_vroot = of_find_node_by_name(शून्य, "vdevice");
	अगर (node_vroot) अणु
		काष्ठा device_node *of_node;
		काष्ठा property *prop;

		क्रम_each_child_of_node(node_vroot, of_node) अणु
			prop = of_find_property(of_node, "ibm,my-dma-window",
			                       शून्य);
			अगर (prop)
				count++;
		पूर्ण
	पूर्ण
	of_node_put(node_vroot);
	वापस count;
पूर्ण

/**
 * vio_cmo_alloc - allocate IO memory क्रम CMO-enable devices
 *
 * @viodev: VIO device requesting IO memory
 * @size: size of allocation requested
 *
 * Allocations come from memory reserved क्रम the devices and any excess
 * IO memory available to all devices.  The spare pool used to service
 * hotplug must be equal to %VIO_CMO_MIN_ENT क्रम the excess pool to be
 * made available.
 *
 * Return codes:
 *  0 क्रम successful allocation and -ENOMEM क्रम a failure
 */
अटल अंतरभूत पूर्णांक vio_cmo_alloc(काष्ठा vio_dev *viodev, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ flags;
	माप_प्रकार reserve_मुक्त = 0;
	माप_प्रकार excess_मुक्त = 0;
	पूर्णांक ret = -ENOMEM;

	spin_lock_irqsave(&vio_cmo.lock, flags);

	/* Determine the amount of मुक्त entitlement available in reserve */
	अगर (viodev->cmo.entitled > viodev->cmo.allocated)
		reserve_मुक्त = viodev->cmo.entitled - viodev->cmo.allocated;

	/* If spare is not fulfilled, the excess pool can not be used. */
	अगर (vio_cmo.spare >= VIO_CMO_MIN_ENT)
		excess_मुक्त = vio_cmo.excess.मुक्त;

	/* The request can be satisfied */
	अगर ((reserve_मुक्त + excess_मुक्त) >= size) अणु
		vio_cmo.curr += size;
		अगर (vio_cmo.curr > vio_cmo.high)
			vio_cmo.high = vio_cmo.curr;
		viodev->cmo.allocated += size;
		size -= min(reserve_मुक्त, size);
		vio_cmo.excess.मुक्त -= size;
		ret = 0;
	पूर्ण

	spin_unlock_irqrestore(&vio_cmo.lock, flags);
	वापस ret;
पूर्ण

/**
 * vio_cmo_dealloc - deallocate IO memory from CMO-enable devices
 * @viodev: VIO device मुक्तing IO memory
 * @size: size of deallocation
 *
 * IO memory is मुक्तd by the device back to the correct memory pools.
 * The spare pool is replenished first from either memory pool, then
 * the reserve pool is used to reduce device entitlement, the excess
 * pool is used to increase the reserve pool toward the desired entitlement
 * target, and then the reमुख्यing memory is वापसed to the pools.
 *
 */
अटल अंतरभूत व्योम vio_cmo_dealloc(काष्ठा vio_dev *viodev, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ flags;
	माप_प्रकार spare_needed = 0;
	माप_प्रकार excess_मुक्तd = 0;
	माप_प्रकार reserve_मुक्तd = size;
	माप_प्रकार पंचांगp;
	पूर्णांक balance = 0;

	spin_lock_irqsave(&vio_cmo.lock, flags);
	vio_cmo.curr -= size;

	/* Amount of memory मुक्तd from the excess pool */
	अगर (viodev->cmo.allocated > viodev->cmo.entitled) अणु
		excess_मुक्तd = min(reserve_मुक्तd, (viodev->cmo.allocated -
		                                   viodev->cmo.entitled));
		reserve_मुक्तd -= excess_मुक्तd;
	पूर्ण

	/* Remove allocation from device */
	viodev->cmo.allocated -= (reserve_मुक्तd + excess_मुक्तd);

	/* Spare is a subset of the reserve pool, replenish it first. */
	spare_needed = VIO_CMO_MIN_ENT - vio_cmo.spare;

	/*
	 * Replenish the spare in the reserve pool from the excess pool.
	 * This moves entitlement पूर्णांकo the reserve pool.
	 */
	अगर (spare_needed && excess_मुक्तd) अणु
		पंचांगp = min(excess_मुक्तd, spare_needed);
		vio_cmo.excess.size -= पंचांगp;
		vio_cmo.reserve.size += पंचांगp;
		vio_cmo.spare += पंचांगp;
		excess_मुक्तd -= पंचांगp;
		spare_needed -= पंचांगp;
		balance = 1;
	पूर्ण

	/*
	 * Replenish the spare in the reserve pool from the reserve pool.
	 * This हटाओs entitlement from the device करोwn to VIO_CMO_MIN_ENT,
	 * अगर needed, and gives it to the spare pool. The amount of used
	 * memory in this pool करोes not change.
	 */
	अगर (spare_needed && reserve_मुक्तd) अणु
		पंचांगp = min3(spare_needed, reserve_मुक्तd, (viodev->cmo.entitled - VIO_CMO_MIN_ENT));

		vio_cmo.spare += पंचांगp;
		viodev->cmo.entitled -= पंचांगp;
		reserve_मुक्तd -= पंचांगp;
		spare_needed -= पंचांगp;
		balance = 1;
	पूर्ण

	/*
	 * Increase the reserve pool until the desired allocation is met.
	 * Move an allocation मुक्तd from the excess pool पूर्णांकo the reserve
	 * pool and schedule a balance operation.
	 */
	अगर (excess_मुक्तd && (vio_cmo.desired > vio_cmo.reserve.size)) अणु
		पंचांगp = min(excess_मुक्तd, (vio_cmo.desired - vio_cmo.reserve.size));

		vio_cmo.excess.size -= पंचांगp;
		vio_cmo.reserve.size += पंचांगp;
		excess_मुक्तd -= पंचांगp;
		balance = 1;
	पूर्ण

	/* Return memory from the excess pool to that pool */
	अगर (excess_मुक्तd)
		vio_cmo.excess.मुक्त += excess_मुक्तd;

	अगर (balance)
		schedule_delayed_work(&vio_cmo.balance_q, VIO_CMO_BALANCE_DELAY);
	spin_unlock_irqrestore(&vio_cmo.lock, flags);
पूर्ण

/**
 * vio_cmo_entitlement_update - Manage प्रणाली entitlement changes
 *
 * @new_entitlement: new प्रणाली entitlement to attempt to accommodate
 *
 * Increases in entitlement will be used to fulfill the spare entitlement
 * and the rest is given to the excess pool.  Decreases, अगर they are
 * possible, come from the excess pool and from unused device entitlement
 *
 * Returns: 0 on success, -ENOMEM when change can not be made
 */
पूर्णांक vio_cmo_entitlement_update(माप_प्रकार new_entitlement)
अणु
	काष्ठा vio_dev *viodev;
	काष्ठा vio_cmo_dev_entry *dev_ent;
	अचिन्हित दीर्घ flags;
	माप_प्रकार avail, delta, पंचांगp;

	spin_lock_irqsave(&vio_cmo.lock, flags);

	/* Entitlement increases */
	अगर (new_entitlement > vio_cmo.entitled) अणु
		delta = new_entitlement - vio_cmo.entitled;

		/* Fulfill spare allocation */
		अगर (vio_cmo.spare < VIO_CMO_MIN_ENT) अणु
			पंचांगp = min(delta, (VIO_CMO_MIN_ENT - vio_cmo.spare));
			vio_cmo.spare += पंचांगp;
			vio_cmo.reserve.size += पंचांगp;
			delta -= पंचांगp;
		पूर्ण

		/* Reमुख्यing new allocation goes to the excess pool */
		vio_cmo.entitled += delta;
		vio_cmo.excess.size += delta;
		vio_cmo.excess.मुक्त += delta;

		जाओ out;
	पूर्ण

	/* Entitlement decreases */
	delta = vio_cmo.entitled - new_entitlement;
	avail = vio_cmo.excess.मुक्त;

	/*
	 * Need to check how much unused entitlement each device can
	 * sacrअगरice to fulfill entitlement change.
	 */
	list_क्रम_each_entry(dev_ent, &vio_cmo.device_list, list) अणु
		अगर (avail >= delta)
			अवरोध;

		viodev = dev_ent->viodev;
		अगर ((viodev->cmo.entitled > viodev->cmo.allocated) &&
		    (viodev->cmo.entitled > VIO_CMO_MIN_ENT))
				avail += viodev->cmo.entitled -
				         max_t(माप_प्रकार, viodev->cmo.allocated,
				               VIO_CMO_MIN_ENT);
	पूर्ण

	अगर (delta <= avail) अणु
		vio_cmo.entitled -= delta;

		/* Take entitlement from the excess pool first */
		पंचांगp = min(vio_cmo.excess.मुक्त, delta);
		vio_cmo.excess.size -= पंचांगp;
		vio_cmo.excess.मुक्त -= पंचांगp;
		delta -= पंचांगp;

		/*
		 * Remove all but VIO_CMO_MIN_ENT bytes from devices
		 * until entitlement change is served
		 */
		list_क्रम_each_entry(dev_ent, &vio_cmo.device_list, list) अणु
			अगर (!delta)
				अवरोध;

			viodev = dev_ent->viodev;
			पंचांगp = 0;
			अगर ((viodev->cmo.entitled > viodev->cmo.allocated) &&
			    (viodev->cmo.entitled > VIO_CMO_MIN_ENT))
				पंचांगp = viodev->cmo.entitled -
				      max_t(माप_प्रकार, viodev->cmo.allocated,
				            VIO_CMO_MIN_ENT);
			viodev->cmo.entitled -= min(पंचांगp, delta);
			delta -= min(पंचांगp, delta);
		पूर्ण
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&vio_cmo.lock, flags);
		वापस -ENOMEM;
	पूर्ण

out:
	schedule_delayed_work(&vio_cmo.balance_q, 0);
	spin_unlock_irqrestore(&vio_cmo.lock, flags);
	वापस 0;
पूर्ण

/**
 * vio_cmo_balance - Balance entitlement among devices
 *
 * @work: work queue काष्ठाure क्रम this operation
 *
 * Any प्रणाली entitlement above the minimum needed क्रम devices, or
 * alपढ़ोy allocated to devices, can be distributed to the devices.
 * The list of devices is iterated through to recalculate the desired
 * entitlement level and to determine how much entitlement above the
 * minimum entitlement is allocated to devices.
 *
 * Small chunks of the available entitlement are given to devices until
 * their requirements are fulfilled or there is no entitlement left to give.
 * Upon completion sizes of the reserve and excess pools are calculated.
 *
 * The प्रणाली minimum entitlement level is also recalculated here.
 * Entitlement will be reserved क्रम devices even after vio_bus_हटाओ to
 * accommodate reloading the driver.  The OF tree is walked to count the
 * number of devices present and this will हटाओ entitlement क्रम devices
 * that have actually left the प्रणाली after having vio_bus_हटाओ called.
 */
अटल व्योम vio_cmo_balance(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा vio_cmo *cmo;
	काष्ठा vio_dev *viodev;
	काष्ठा vio_cmo_dev_entry *dev_ent;
	अचिन्हित दीर्घ flags;
	माप_प्रकार avail = 0, level, chunk, need;
	पूर्णांक devcount = 0, fulfilled;

	cmo = container_of(work, काष्ठा vio_cmo, balance_q.work);

	spin_lock_irqsave(&vio_cmo.lock, flags);

	/* Calculate minimum entitlement and fulfill spare */
	cmo->min = vio_cmo_num_OF_devs() * VIO_CMO_MIN_ENT;
	BUG_ON(cmo->min > cmo->entitled);
	cmo->spare = min_t(माप_प्रकार, VIO_CMO_MIN_ENT, (cmo->entitled - cmo->min));
	cmo->min += cmo->spare;
	cmo->desired = cmo->min;

	/*
	 * Determine how much entitlement is available and reset device
	 * entitlements
	 */
	avail = cmo->entitled - cmo->spare;
	list_क्रम_each_entry(dev_ent, &vio_cmo.device_list, list) अणु
		viodev = dev_ent->viodev;
		devcount++;
		viodev->cmo.entitled = VIO_CMO_MIN_ENT;
		cmo->desired += (viodev->cmo.desired - VIO_CMO_MIN_ENT);
		avail -= max_t(माप_प्रकार, viodev->cmo.allocated, VIO_CMO_MIN_ENT);
	पूर्ण

	/*
	 * Having provided each device with the minimum entitlement, loop
	 * over the devices portioning out the reमुख्यing entitlement
	 * until there is nothing left.
	 */
	level = VIO_CMO_MIN_ENT;
	जबतक (avail) अणु
		fulfilled = 0;
		list_क्रम_each_entry(dev_ent, &vio_cmo.device_list, list) अणु
			viodev = dev_ent->viodev;

			अगर (viodev->cmo.desired <= level) अणु
				fulfilled++;
				जारी;
			पूर्ण

			/*
			 * Give the device up to VIO_CMO_BALANCE_CHUNK
			 * bytes of entitlement, but करो not exceed the
			 * desired level of entitlement क्रम the device.
			 */
			chunk = min_t(माप_प्रकार, avail, VIO_CMO_BALANCE_CHUNK);
			chunk = min(chunk, (viodev->cmo.desired -
			                    viodev->cmo.entitled));
			viodev->cmo.entitled += chunk;

			/*
			 * If the memory क्रम this entitlement increase was
			 * alपढ़ोy allocated to the device it करोes not come
			 * from the available pool being portioned out.
			 */
			need = max(viodev->cmo.allocated, viodev->cmo.entitled)-
			       max(viodev->cmo.allocated, level);
			avail -= need;

		पूर्ण
		अगर (fulfilled == devcount)
			अवरोध;
		level += VIO_CMO_BALANCE_CHUNK;
	पूर्ण

	/* Calculate new reserve and excess pool sizes */
	cmo->reserve.size = cmo->min;
	cmo->excess.मुक्त = 0;
	cmo->excess.size = 0;
	need = 0;
	list_क्रम_each_entry(dev_ent, &vio_cmo.device_list, list) अणु
		viodev = dev_ent->viodev;
		/* Calculated reserve size above the minimum entitlement */
		अगर (viodev->cmo.entitled)
			cmo->reserve.size += (viodev->cmo.entitled -
			                      VIO_CMO_MIN_ENT);
		/* Calculated used excess entitlement */
		अगर (viodev->cmo.allocated > viodev->cmo.entitled)
			need += viodev->cmo.allocated - viodev->cmo.entitled;
	पूर्ण
	cmo->excess.size = cmo->entitled - cmo->reserve.size;
	cmo->excess.मुक्त = cmo->excess.size - need;

	cancel_delayed_work(to_delayed_work(work));
	spin_unlock_irqrestore(&vio_cmo.lock, flags);
पूर्ण

अटल व्योम *vio_dma_iommu_alloc_coherent(काष्ठा device *dev, माप_प्रकार size,
					  dma_addr_t *dma_handle, gfp_t flag,
					  अचिन्हित दीर्घ attrs)
अणु
	काष्ठा vio_dev *viodev = to_vio_dev(dev);
	व्योम *ret;

	अगर (vio_cmo_alloc(viodev, roundup(size, PAGE_SIZE))) अणु
		atomic_inc(&viodev->cmo.allocs_failed);
		वापस शून्य;
	पूर्ण

	ret = iommu_alloc_coherent(dev, get_iommu_table_base(dev), size,
				    dma_handle, dev->coherent_dma_mask, flag,
				    dev_to_node(dev));
	अगर (unlikely(ret == शून्य)) अणु
		vio_cmo_dealloc(viodev, roundup(size, PAGE_SIZE));
		atomic_inc(&viodev->cmo.allocs_failed);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम vio_dma_iommu_मुक्त_coherent(काष्ठा device *dev, माप_प्रकार size,
					व्योम *vaddr, dma_addr_t dma_handle,
					अचिन्हित दीर्घ attrs)
अणु
	काष्ठा vio_dev *viodev = to_vio_dev(dev);

	iommu_मुक्त_coherent(get_iommu_table_base(dev), size, vaddr, dma_handle);
	vio_cmo_dealloc(viodev, roundup(size, PAGE_SIZE));
पूर्ण

अटल dma_addr_t vio_dma_iommu_map_page(काष्ठा device *dev, काष्ठा page *page,
                                         अचिन्हित दीर्घ offset, माप_प्रकार size,
                                         क्रमागत dma_data_direction direction,
                                         अचिन्हित दीर्घ attrs)
अणु
	काष्ठा vio_dev *viodev = to_vio_dev(dev);
	काष्ठा iommu_table *tbl = get_iommu_table_base(dev);
	dma_addr_t ret = DMA_MAPPING_ERROR;

	अगर (vio_cmo_alloc(viodev, roundup(size, IOMMU_PAGE_SIZE(tbl))))
		जाओ out_fail;
	ret = iommu_map_page(dev, tbl, page, offset, size, dma_get_mask(dev),
			direction, attrs);
	अगर (unlikely(ret == DMA_MAPPING_ERROR))
		जाओ out_deallocate;
	वापस ret;

out_deallocate:
	vio_cmo_dealloc(viodev, roundup(size, IOMMU_PAGE_SIZE(tbl)));
out_fail:
	atomic_inc(&viodev->cmo.allocs_failed);
	वापस DMA_MAPPING_ERROR;
पूर्ण

अटल व्योम vio_dma_iommu_unmap_page(काष्ठा device *dev, dma_addr_t dma_handle,
				     माप_प्रकार size,
				     क्रमागत dma_data_direction direction,
				     अचिन्हित दीर्घ attrs)
अणु
	काष्ठा vio_dev *viodev = to_vio_dev(dev);
	काष्ठा iommu_table *tbl = get_iommu_table_base(dev);

	iommu_unmap_page(tbl, dma_handle, size, direction, attrs);
	vio_cmo_dealloc(viodev, roundup(size, IOMMU_PAGE_SIZE(tbl)));
पूर्ण

अटल पूर्णांक vio_dma_iommu_map_sg(काष्ठा device *dev, काष्ठा scatterlist *sglist,
                                पूर्णांक nelems, क्रमागत dma_data_direction direction,
                                अचिन्हित दीर्घ attrs)
अणु
	काष्ठा vio_dev *viodev = to_vio_dev(dev);
	काष्ठा iommu_table *tbl = get_iommu_table_base(dev);
	काष्ठा scatterlist *sgl;
	पूर्णांक ret, count;
	माप_प्रकार alloc_size = 0;

	क्रम_each_sg(sglist, sgl, nelems, count)
		alloc_size += roundup(sgl->length, IOMMU_PAGE_SIZE(tbl));

	अगर (vio_cmo_alloc(viodev, alloc_size))
		जाओ out_fail;
	ret = ppc_iommu_map_sg(dev, tbl, sglist, nelems, dma_get_mask(dev),
			direction, attrs);
	अगर (unlikely(!ret))
		जाओ out_deallocate;

	क्रम_each_sg(sglist, sgl, ret, count)
		alloc_size -= roundup(sgl->dma_length, IOMMU_PAGE_SIZE(tbl));
	अगर (alloc_size)
		vio_cmo_dealloc(viodev, alloc_size);
	वापस ret;

out_deallocate:
	vio_cmo_dealloc(viodev, alloc_size);
out_fail:
	atomic_inc(&viodev->cmo.allocs_failed);
	वापस 0;
पूर्ण

अटल व्योम vio_dma_iommu_unmap_sg(काष्ठा device *dev,
		काष्ठा scatterlist *sglist, पूर्णांक nelems,
		क्रमागत dma_data_direction direction,
		अचिन्हित दीर्घ attrs)
अणु
	काष्ठा vio_dev *viodev = to_vio_dev(dev);
	काष्ठा iommu_table *tbl = get_iommu_table_base(dev);
	काष्ठा scatterlist *sgl;
	माप_प्रकार alloc_size = 0;
	पूर्णांक count;

	क्रम_each_sg(sglist, sgl, nelems, count)
		alloc_size += roundup(sgl->dma_length, IOMMU_PAGE_SIZE(tbl));

	ppc_iommu_unmap_sg(tbl, sglist, nelems, direction, attrs);
	vio_cmo_dealloc(viodev, alloc_size);
पूर्ण

अटल स्थिर काष्ठा dma_map_ops vio_dma_mapping_ops = अणु
	.alloc             = vio_dma_iommu_alloc_coherent,
	.मुक्त              = vio_dma_iommu_मुक्त_coherent,
	.map_sg            = vio_dma_iommu_map_sg,
	.unmap_sg          = vio_dma_iommu_unmap_sg,
	.map_page          = vio_dma_iommu_map_page,
	.unmap_page        = vio_dma_iommu_unmap_page,
	.dma_supported     = dma_iommu_dma_supported,
	.get_required_mask = dma_iommu_get_required_mask,
	.mmap		   = dma_common_mmap,
	.get_sgtable	   = dma_common_get_sgtable,
	.alloc_pages	   = dma_common_alloc_pages,
	.मुक्त_pages	   = dma_common_मुक्त_pages,
पूर्ण;

/**
 * vio_cmo_set_dev_desired - Set desired entitlement क्रम a device
 *
 * @viodev: काष्ठा vio_dev क्रम device to alter
 * @desired: new desired entitlement level in bytes
 *
 * For use by devices to request a change to their entitlement at runसमय or
 * through sysfs.  The desired entitlement level is changed and a balancing
 * of प्रणाली resources is scheduled to run in the future.
 */
व्योम vio_cmo_set_dev_desired(काष्ठा vio_dev *viodev, माप_प्रकार desired)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा vio_cmo_dev_entry *dev_ent;
	पूर्णांक found = 0;

	अगर (!firmware_has_feature(FW_FEATURE_CMO))
		वापस;

	spin_lock_irqsave(&vio_cmo.lock, flags);
	अगर (desired < VIO_CMO_MIN_ENT)
		desired = VIO_CMO_MIN_ENT;

	/*
	 * Changes will not be made क्रम devices not in the device list.
	 * If it is not in the device list, then no driver is loaded
	 * क्रम the device and it can not receive entitlement.
	 */
	list_क्रम_each_entry(dev_ent, &vio_cmo.device_list, list)
		अगर (viodev == dev_ent->viodev) अणु
			found = 1;
			अवरोध;
		पूर्ण
	अगर (!found) अणु
		spin_unlock_irqrestore(&vio_cmo.lock, flags);
		वापस;
	पूर्ण

	/* Increase/decrease in desired device entitlement */
	अगर (desired >= viodev->cmo.desired) अणु
		/* Just bump the bus and device values prior to a balance*/
		vio_cmo.desired += desired - viodev->cmo.desired;
		viodev->cmo.desired = desired;
	पूर्ण अन्यथा अणु
		/* Decrease bus and device values क्रम desired entitlement */
		vio_cmo.desired -= viodev->cmo.desired - desired;
		viodev->cmo.desired = desired;
		/*
		 * If less entitlement is desired than current entitlement, move
		 * any reserve memory in the change region to the excess pool.
		 */
		अगर (viodev->cmo.entitled > desired) अणु
			vio_cmo.reserve.size -= viodev->cmo.entitled - desired;
			vio_cmo.excess.size += viodev->cmo.entitled - desired;
			/*
			 * If entitlement moving from the reserve pool to the
			 * excess pool is currently unused, add to the excess
			 * मुक्त counter.
			 */
			अगर (viodev->cmo.allocated < viodev->cmo.entitled)
				vio_cmo.excess.मुक्त += viodev->cmo.entitled -
				                       max(viodev->cmo.allocated, desired);
			viodev->cmo.entitled = desired;
		पूर्ण
	पूर्ण
	schedule_delayed_work(&vio_cmo.balance_q, 0);
	spin_unlock_irqrestore(&vio_cmo.lock, flags);
पूर्ण

/**
 * vio_cmo_bus_probe - Handle CMO specअगरic bus probe activities
 *
 * @viodev - Poपूर्णांकer to काष्ठा vio_dev क्रम device
 *
 * Determine the devices IO memory entitlement needs, attempting
 * to satisfy the प्रणाली minimum entitlement at first and scheduling
 * a balance operation to take care of the rest at a later समय.
 *
 * Returns: 0 on success, -EINVAL when device करोesn't support CMO, and
 *          -ENOMEM when entitlement is not available क्रम device or
 *          device entry.
 *
 */
अटल पूर्णांक vio_cmo_bus_probe(काष्ठा vio_dev *viodev)
अणु
	काष्ठा vio_cmo_dev_entry *dev_ent;
	काष्ठा device *dev = &viodev->dev;
	काष्ठा iommu_table *tbl;
	काष्ठा vio_driver *viodrv = to_vio_driver(dev->driver);
	अचिन्हित दीर्घ flags;
	माप_प्रकार size;
	bool dma_capable = false;

	tbl = get_iommu_table_base(dev);

	/* A device requires entitlement अगर it has a DMA winकरोw property */
	चयन (viodev->family) अणु
	हाल VDEVICE:
		अगर (of_get_property(viodev->dev.of_node,
					"ibm,my-dma-window", शून्य))
			dma_capable = true;
		अवरोध;
	हाल PFO:
		dma_capable = false;
		अवरोध;
	शेष:
		dev_warn(dev, "unknown device family: %d\n", viodev->family);
		BUG();
		अवरोध;
	पूर्ण

	/* Configure entitlement क्रम the device. */
	अगर (dma_capable) अणु
		/* Check that the driver is CMO enabled and get desired DMA */
		अगर (!viodrv->get_desired_dma) अणु
			dev_err(dev, "%s: device driver does not support CMO\n",
			        __func__);
			वापस -EINVAL;
		पूर्ण

		viodev->cmo.desired =
			IOMMU_PAGE_ALIGN(viodrv->get_desired_dma(viodev), tbl);
		अगर (viodev->cmo.desired < VIO_CMO_MIN_ENT)
			viodev->cmo.desired = VIO_CMO_MIN_ENT;
		size = VIO_CMO_MIN_ENT;

		dev_ent = kदो_स्मृति(माप(काष्ठा vio_cmo_dev_entry),
		                  GFP_KERNEL);
		अगर (!dev_ent)
			वापस -ENOMEM;

		dev_ent->viodev = viodev;
		spin_lock_irqsave(&vio_cmo.lock, flags);
		list_add(&dev_ent->list, &vio_cmo.device_list);
	पूर्ण अन्यथा अणु
		viodev->cmo.desired = 0;
		size = 0;
		spin_lock_irqsave(&vio_cmo.lock, flags);
	पूर्ण

	/*
	 * If the needs क्रम vio_cmo.min have not changed since they
	 * were last set, the number of devices in the OF tree has
	 * been स्थिरant and the IO memory क्रम this is alपढ़ोy in
	 * the reserve pool.
	 */
	अगर (vio_cmo.min == ((vio_cmo_num_OF_devs() + 1) *
	                    VIO_CMO_MIN_ENT)) अणु
		/* Updated desired entitlement अगर device requires it */
		अगर (size)
			vio_cmo.desired += (viodev->cmo.desired -
		                        VIO_CMO_MIN_ENT);
	पूर्ण अन्यथा अणु
		माप_प्रकार पंचांगp;

		पंचांगp = vio_cmo.spare + vio_cmo.excess.मुक्त;
		अगर (पंचांगp < size) अणु
			dev_err(dev, "%s: insufficient free "
			        "entitlement to add device. "
			        "Need %lu, have %lu\n", __func__,
				size, (vio_cmo.spare + पंचांगp));
			spin_unlock_irqrestore(&vio_cmo.lock, flags);
			वापस -ENOMEM;
		पूर्ण

		/* Use excess pool first to fulfill request */
		पंचांगp = min(size, vio_cmo.excess.मुक्त);
		vio_cmo.excess.मुक्त -= पंचांगp;
		vio_cmo.excess.size -= पंचांगp;
		vio_cmo.reserve.size += पंचांगp;

		/* Use spare अगर excess pool was insufficient */
		vio_cmo.spare -= size - पंचांगp;

		/* Update bus accounting */
		vio_cmo.min += size;
		vio_cmo.desired += viodev->cmo.desired;
	पूर्ण
	spin_unlock_irqrestore(&vio_cmo.lock, flags);
	वापस 0;
पूर्ण

/**
 * vio_cmo_bus_हटाओ - Handle CMO specअगरic bus removal activities
 *
 * @viodev - Poपूर्णांकer to काष्ठा vio_dev क्रम device
 *
 * Remove the device from the cmo device list.  The minimum entitlement
 * will be reserved क्रम the device as दीर्घ as it is in the प्रणाली.  The
 * rest of the entitlement the device had been allocated will be वापसed
 * to the प्रणाली.
 */
अटल व्योम vio_cmo_bus_हटाओ(काष्ठा vio_dev *viodev)
अणु
	काष्ठा vio_cmo_dev_entry *dev_ent;
	अचिन्हित दीर्घ flags;
	माप_प्रकार पंचांगp;

	spin_lock_irqsave(&vio_cmo.lock, flags);
	अगर (viodev->cmo.allocated) अणु
		dev_err(&viodev->dev, "%s: device had %lu bytes of IO "
		        "allocated after remove operation.\n",
		        __func__, viodev->cmo.allocated);
		BUG();
	पूर्ण

	/*
	 * Remove the device from the device list being मुख्यtained क्रम
	 * CMO enabled devices.
	 */
	list_क्रम_each_entry(dev_ent, &vio_cmo.device_list, list)
		अगर (viodev == dev_ent->viodev) अणु
			list_del(&dev_ent->list);
			kमुक्त(dev_ent);
			अवरोध;
		पूर्ण

	/*
	 * Devices may not require any entitlement and they करो not need
	 * to be processed.  Otherwise, वापस the device's entitlement
	 * back to the pools.
	 */
	अगर (viodev->cmo.entitled) अणु
		/*
		 * This device has not yet left the OF tree, it's
		 * minimum entitlement reमुख्यs in vio_cmo.min and
		 * vio_cmo.desired
		 */
		vio_cmo.desired -= (viodev->cmo.desired - VIO_CMO_MIN_ENT);

		/*
		 * Save min allocation क्रम device in reserve as दीर्घ
		 * as it exists in OF tree as determined by later
		 * balance operation
		 */
		viodev->cmo.entitled -= VIO_CMO_MIN_ENT;

		/* Replenish spare from मुक्तd reserve pool */
		अगर (viodev->cmo.entitled && (vio_cmo.spare < VIO_CMO_MIN_ENT)) अणु
			पंचांगp = min(viodev->cmo.entitled, (VIO_CMO_MIN_ENT -
			                                 vio_cmo.spare));
			vio_cmo.spare += पंचांगp;
			viodev->cmo.entitled -= पंचांगp;
		पूर्ण

		/* Reमुख्यing reserve goes to excess pool */
		vio_cmo.excess.size += viodev->cmo.entitled;
		vio_cmo.excess.मुक्त += viodev->cmo.entitled;
		vio_cmo.reserve.size -= viodev->cmo.entitled;

		/*
		 * Until the device is हटाओd it will keep a
		 * minimum entitlement; this will guarantee that
		 * a module unload/load will result in a success.
		 */
		viodev->cmo.entitled = VIO_CMO_MIN_ENT;
		viodev->cmo.desired = VIO_CMO_MIN_ENT;
		atomic_set(&viodev->cmo.allocs_failed, 0);
	पूर्ण

	spin_unlock_irqrestore(&vio_cmo.lock, flags);
पूर्ण

अटल व्योम vio_cmo_set_dma_ops(काष्ठा vio_dev *viodev)
अणु
	set_dma_ops(&viodev->dev, &vio_dma_mapping_ops);
पूर्ण

/**
 * vio_cmo_bus_init - CMO entitlement initialization at bus init समय
 *
 * Set up the reserve and excess entitlement pools based on available
 * प्रणाली entitlement and the number of devices in the OF tree that
 * require entitlement in the reserve pool.
 */
अटल व्योम vio_cmo_bus_init(व्योम)
अणु
	काष्ठा hvcall_mpp_data mpp_data;
	पूर्णांक err;

	स_रखो(&vio_cmo, 0, माप(काष्ठा vio_cmo));
	spin_lock_init(&vio_cmo.lock);
	INIT_LIST_HEAD(&vio_cmo.device_list);
	INIT_DELAYED_WORK(&vio_cmo.balance_q, vio_cmo_balance);

	/* Get current प्रणाली entitlement */
	err = h_get_mpp(&mpp_data);

	/*
	 * On failure, जारी with entitlement set to 0, will panic()
	 * later when spare is reserved.
	 */
	अगर (err != H_SUCCESS) अणु
		prपूर्णांकk(KERN_ERR "%s: unable to determine system IO "\
		       "entitlement. (%d)\n", __func__, err);
		vio_cmo.entitled = 0;
	पूर्ण अन्यथा अणु
		vio_cmo.entitled = mpp_data.entitled_mem;
	पूर्ण

	/* Set reservation and check against entitlement */
	vio_cmo.spare = VIO_CMO_MIN_ENT;
	vio_cmo.reserve.size = vio_cmo.spare;
	vio_cmo.reserve.size += (vio_cmo_num_OF_devs() *
	                         VIO_CMO_MIN_ENT);
	अगर (vio_cmo.reserve.size > vio_cmo.entitled) अणु
		prपूर्णांकk(KERN_ERR "%s: insufficient system entitlement\n",
		       __func__);
		panic("%s: Insufficient system entitlement", __func__);
	पूर्ण

	/* Set the reमुख्यing accounting variables */
	vio_cmo.excess.size = vio_cmo.entitled - vio_cmo.reserve.size;
	vio_cmo.excess.मुक्त = vio_cmo.excess.size;
	vio_cmo.min = vio_cmo.reserve.size;
	vio_cmo.desired = vio_cmo.reserve.size;
पूर्ण

/* sysfs device functions and data काष्ठाures क्रम CMO */

#घोषणा viodev_cmo_rd_attr(name)                                        \
अटल sमाप_प्रकार cmo_##name##_show(काष्ठा device *dev,                    \
                                        काष्ठा device_attribute *attr,  \
                                         अक्षर *buf)                     \
अणु                                                                       \
	वापस प्र_लिखो(buf, "%lu\n", to_vio_dev(dev)->cmo.name);        \
पूर्ण

अटल sमाप_प्रकार cmo_allocs_failed_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा vio_dev *viodev = to_vio_dev(dev);
	वापस प्र_लिखो(buf, "%d\n", atomic_पढ़ो(&viodev->cmo.allocs_failed));
पूर्ण

अटल sमाप_प्रकार cmo_allocs_failed_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा vio_dev *viodev = to_vio_dev(dev);
	atomic_set(&viodev->cmo.allocs_failed, 0);
	वापस count;
पूर्ण

अटल sमाप_प्रकार cmo_desired_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा vio_dev *viodev = to_vio_dev(dev);
	माप_प्रकार new_desired;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 10, &new_desired);
	अगर (ret)
		वापस ret;

	vio_cmo_set_dev_desired(viodev, new_desired);
	वापस count;
पूर्ण

viodev_cmo_rd_attr(desired);
viodev_cmo_rd_attr(entitled);
viodev_cmo_rd_attr(allocated);

अटल sमाप_प्रकार name_show(काष्ठा device *, काष्ठा device_attribute *, अक्षर *);
अटल sमाप_प्रकार devspec_show(काष्ठा device *, काष्ठा device_attribute *, अक्षर *);
अटल sमाप_प्रकार modalias_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf);

अटल काष्ठा device_attribute dev_attr_name;
अटल काष्ठा device_attribute dev_attr_devspec;
अटल काष्ठा device_attribute dev_attr_modalias;

अटल DEVICE_ATTR_RO(cmo_entitled);
अटल DEVICE_ATTR_RO(cmo_allocated);
अटल DEVICE_ATTR_RW(cmo_desired);
अटल DEVICE_ATTR_RW(cmo_allocs_failed);

अटल काष्ठा attribute *vio_cmo_dev_attrs[] = अणु
	&dev_attr_name.attr,
	&dev_attr_devspec.attr,
	&dev_attr_modalias.attr,
	&dev_attr_cmo_entitled.attr,
	&dev_attr_cmo_allocated.attr,
	&dev_attr_cmo_desired.attr,
	&dev_attr_cmo_allocs_failed.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(vio_cmo_dev);

/* sysfs bus functions and data काष्ठाures क्रम CMO */

#घोषणा viobus_cmo_rd_attr(name)                                        \
अटल sमाप_प्रकार cmo_bus_##name##_show(काष्ठा bus_type *bt, अक्षर *buf)    \
अणु                                                                       \
	वापस प्र_लिखो(buf, "%lu\n", vio_cmo.name);                     \
पूर्ण                                                                       \
अटल काष्ठा bus_attribute bus_attr_cmo_bus_##name =			\
	__ATTR(cmo_##name, S_IRUGO, cmo_bus_##name##_show, शून्य)

#घोषणा viobus_cmo_pool_rd_attr(name, var)                              \
अटल sमाप_प्रकार                                                          \
cmo_##name##_##var##_show(काष्ठा bus_type *bt, अक्षर *buf)               \
अणु                                                                       \
	वापस प्र_लिखो(buf, "%lu\n", vio_cmo.name.var);                 \
पूर्ण                                                                       \
अटल BUS_ATTR_RO(cmo_##name##_##var)

viobus_cmo_rd_attr(entitled);
viobus_cmo_rd_attr(spare);
viobus_cmo_rd_attr(min);
viobus_cmo_rd_attr(desired);
viobus_cmo_rd_attr(curr);
viobus_cmo_pool_rd_attr(reserve, size);
viobus_cmo_pool_rd_attr(excess, size);
viobus_cmo_pool_rd_attr(excess, मुक्त);

अटल sमाप_प्रकार cmo_high_show(काष्ठा bus_type *bt, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%lu\n", vio_cmo.high);
पूर्ण

अटल sमाप_प्रकार cmo_high_store(काष्ठा bus_type *bt, स्थिर अक्षर *buf,
			      माप_प्रकार count)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&vio_cmo.lock, flags);
	vio_cmo.high = vio_cmo.curr;
	spin_unlock_irqrestore(&vio_cmo.lock, flags);

	वापस count;
पूर्ण
अटल BUS_ATTR_RW(cmo_high);

अटल काष्ठा attribute *vio_bus_attrs[] = अणु
	&bus_attr_cmo_bus_entitled.attr,
	&bus_attr_cmo_bus_spare.attr,
	&bus_attr_cmo_bus_min.attr,
	&bus_attr_cmo_bus_desired.attr,
	&bus_attr_cmo_bus_curr.attr,
	&bus_attr_cmo_high.attr,
	&bus_attr_cmo_reserve_size.attr,
	&bus_attr_cmo_excess_size.attr,
	&bus_attr_cmo_excess_मुक्त.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(vio_bus);

अटल व्योम vio_cmo_sysfs_init(व्योम)
अणु
	vio_bus_type.dev_groups = vio_cmo_dev_groups;
	vio_bus_type.bus_groups = vio_bus_groups;
पूर्ण
#अन्यथा /* CONFIG_PPC_SMLPAR */
पूर्णांक vio_cmo_entitlement_update(माप_प्रकार new_entitlement) अणु वापस 0; पूर्ण
व्योम vio_cmo_set_dev_desired(काष्ठा vio_dev *viodev, माप_प्रकार desired) अणुपूर्ण
अटल पूर्णांक vio_cmo_bus_probe(काष्ठा vio_dev *viodev) अणु वापस 0; पूर्ण
अटल व्योम vio_cmo_bus_हटाओ(काष्ठा vio_dev *viodev) अणुपूर्ण
अटल व्योम vio_cmo_set_dma_ops(काष्ठा vio_dev *viodev) अणुपूर्ण
अटल व्योम vio_cmo_bus_init(व्योम) अणुपूर्ण
अटल व्योम vio_cmo_sysfs_init(व्योम) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_SMLPAR */
EXPORT_SYMBOL(vio_cmo_entitlement_update);
EXPORT_SYMBOL(vio_cmo_set_dev_desired);


/*
 * Platक्रमm Facilities Option (PFO) support
 */

/**
 * vio_h_cop_sync - Perक्रमm a synchronous PFO co-processor operation
 *
 * @vdev - Poपूर्णांकer to a काष्ठा vio_dev क्रम device
 * @op - Poपूर्णांकer to a काष्ठा vio_pfo_op क्रम the operation parameters
 *
 * Calls the hypervisor to synchronously perक्रमm the PFO operation
 * described in @op.  In the हाल of a busy response from the hypervisor,
 * the operation will be re-submitted indefinitely unless a non-zero समयout
 * is specअगरied or an error occurs. The समयout places a limit on when to
 * stop re-submitting a operation, the total समय can be exceeded अगर an
 * operation is in progress.
 *
 * If op->hcall_ret is not शून्य, this will be set to the वापस from the
 * last h_cop_op call or it will be 0 अगर an error not involving the h_call
 * was encountered.
 *
 * Returns:
 *	0 on success,
 *	-EINVAL अगर the h_call fails due to an invalid parameter,
 *	-E2BIG अगर the h_call can not be perक्रमmed synchronously,
 *	-EBUSY अगर a समयout is specअगरied and has elapsed,
 *	-EACCES अगर the memory area क्रम data/status has been rescinded, or
 *	-EPERM अगर a hardware fault has been indicated
 */
पूर्णांक vio_h_cop_sync(काष्ठा vio_dev *vdev, काष्ठा vio_pfo_op *op)
अणु
	काष्ठा device *dev = &vdev->dev;
	अचिन्हित दीर्घ deadline = 0;
	दीर्घ hret = 0;
	पूर्णांक ret = 0;

	अगर (op->समयout)
		deadline = jअगरfies + msecs_to_jअगरfies(op->समयout);

	जबतक (true) अणु
		hret = plpar_hcall_norets(H_COP, op->flags,
				vdev->resource_id,
				op->in, op->inlen, op->out,
				op->outlen, op->csbcpb);

		अगर (hret == H_SUCCESS ||
		    (hret != H_NOT_ENOUGH_RESOURCES &&
		     hret != H_BUSY && hret != H_RESOURCE) ||
		    (op->समयout && समय_after(deadline, jअगरfies)))
			अवरोध;

		dev_dbg(dev, "%s: hcall ret(%ld), retrying.\n", __func__, hret);
	पूर्ण

	चयन (hret) अणु
	हाल H_SUCCESS:
		ret = 0;
		अवरोध;
	हाल H_OP_MODE:
	हाल H_TOO_BIG:
		ret = -E2BIG;
		अवरोध;
	हाल H_RESCINDED:
		ret = -EACCES;
		अवरोध;
	हाल H_HARDWARE:
		ret = -EPERM;
		अवरोध;
	हाल H_NOT_ENOUGH_RESOURCES:
	हाल H_RESOURCE:
	हाल H_BUSY:
		ret = -EBUSY;
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	अगर (ret)
		dev_dbg(dev, "%s: Sync h_cop_op failure (ret:%d) (hret:%ld)\n",
				__func__, ret, hret);

	op->hcall_err = hret;
	वापस ret;
पूर्ण
EXPORT_SYMBOL(vio_h_cop_sync);

अटल काष्ठा iommu_table *vio_build_iommu_table(काष्ठा vio_dev *dev)
अणु
	स्थिर __be32 *dma_winकरोw;
	काष्ठा iommu_table *tbl;
	अचिन्हित दीर्घ offset, size;

	dma_winकरोw = of_get_property(dev->dev.of_node,
				  "ibm,my-dma-window", शून्य);
	अगर (!dma_winकरोw)
		वापस शून्य;

	tbl = kzalloc(माप(*tbl), GFP_KERNEL);
	अगर (tbl == शून्य)
		वापस शून्य;

	kref_init(&tbl->it_kref);

	of_parse_dma_winकरोw(dev->dev.of_node, dma_winकरोw,
			    &tbl->it_index, &offset, &size);

	/* TCE table size - measured in tce entries */
	tbl->it_page_shअगरt = IOMMU_PAGE_SHIFT_4K;
	tbl->it_size = size >> tbl->it_page_shअगरt;
	/* offset क्रम VIO should always be 0 */
	tbl->it_offset = offset >> tbl->it_page_shअगरt;
	tbl->it_busno = 0;
	tbl->it_type = TCE_VB;
	tbl->it_blocksize = 16;

	अगर (firmware_has_feature(FW_FEATURE_LPAR))
		tbl->it_ops = &iommu_table_lpar_multi_ops;
	अन्यथा
		tbl->it_ops = &iommu_table_pseries_ops;

	वापस iommu_init_table(tbl, -1, 0, 0);
पूर्ण

/**
 * vio_match_device: - Tell अगर a VIO device has a matching
 *			VIO device id काष्ठाure.
 * @ids:	array of VIO device id काष्ठाures to search in
 * @dev:	the VIO device काष्ठाure to match against
 *
 * Used by a driver to check whether a VIO device present in the
 * प्रणाली is in its list of supported devices. Returns the matching
 * vio_device_id काष्ठाure or शून्य अगर there is no match.
 */
अटल स्थिर काष्ठा vio_device_id *vio_match_device(
		स्थिर काष्ठा vio_device_id *ids, स्थिर काष्ठा vio_dev *dev)
अणु
	जबतक (ids->type[0] != '\0') अणु
		अगर ((म_भेदन(dev->type, ids->type, म_माप(ids->type)) == 0) &&
		    of_device_is_compatible(dev->dev.of_node,
					 ids->compat))
			वापस ids;
		ids++;
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * Convert from काष्ठा device to काष्ठा vio_dev and pass to driver.
 * dev->driver has alपढ़ोy been set by generic code because vio_bus_match
 * succeeded.
 */
अटल पूर्णांक vio_bus_probe(काष्ठा device *dev)
अणु
	काष्ठा vio_dev *viodev = to_vio_dev(dev);
	काष्ठा vio_driver *viodrv = to_vio_driver(dev->driver);
	स्थिर काष्ठा vio_device_id *id;
	पूर्णांक error = -ENODEV;

	अगर (!viodrv->probe)
		वापस error;

	id = vio_match_device(viodrv->id_table, viodev);
	अगर (id) अणु
		स_रखो(&viodev->cmo, 0, माप(viodev->cmo));
		अगर (firmware_has_feature(FW_FEATURE_CMO)) अणु
			error = vio_cmo_bus_probe(viodev);
			अगर (error)
				वापस error;
		पूर्ण
		error = viodrv->probe(viodev, id);
		अगर (error && firmware_has_feature(FW_FEATURE_CMO))
			vio_cmo_bus_हटाओ(viodev);
	पूर्ण

	वापस error;
पूर्ण

/* convert from काष्ठा device to काष्ठा vio_dev and pass to driver. */
अटल पूर्णांक vio_bus_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा vio_dev *viodev = to_vio_dev(dev);
	काष्ठा vio_driver *viodrv = to_vio_driver(dev->driver);
	काष्ठा device *devptr;

	/*
	 * Hold a reference to the device after the हटाओ function is called
	 * to allow क्रम CMO accounting cleanup क्रम the device.
	 */
	devptr = get_device(dev);

	अगर (viodrv->हटाओ)
		viodrv->हटाओ(viodev);

	अगर (firmware_has_feature(FW_FEATURE_CMO))
		vio_cmo_bus_हटाओ(viodev);

	put_device(devptr);
	वापस 0;
पूर्ण

अटल व्योम vio_bus_shutकरोwn(काष्ठा device *dev)
अणु
	काष्ठा vio_dev *viodev = to_vio_dev(dev);
	काष्ठा vio_driver *viodrv;

	अगर (dev->driver) अणु
		viodrv = to_vio_driver(dev->driver);
		अगर (viodrv->shutकरोwn)
			viodrv->shutकरोwn(viodev);
		अन्यथा अगर (kexec_in_progress)
			vio_bus_हटाओ(dev);
	पूर्ण
पूर्ण

/**
 * vio_रेजिस्टर_driver: - Register a new vio driver
 * @viodrv:	The vio_driver काष्ठाure to be रेजिस्टरed.
 */
पूर्णांक __vio_रेजिस्टर_driver(काष्ठा vio_driver *viodrv, काष्ठा module *owner,
			  स्थिर अक्षर *mod_name)
अणु
	// vio_bus_type is only initialised क्रम pseries
	अगर (!machine_is(pseries))
		वापस -ENODEV;

	pr_debug("%s: driver %s registering\n", __func__, viodrv->name);

	/* fill in 'struct driver' fields */
	viodrv->driver.name = viodrv->name;
	viodrv->driver.pm = viodrv->pm;
	viodrv->driver.bus = &vio_bus_type;
	viodrv->driver.owner = owner;
	viodrv->driver.mod_name = mod_name;

	वापस driver_रेजिस्टर(&viodrv->driver);
पूर्ण
EXPORT_SYMBOL(__vio_रेजिस्टर_driver);

/**
 * vio_unरेजिस्टर_driver - Remove registration of vio driver.
 * @viodrv:	The vio_driver काष्ठा to be हटाओd क्रमm registration
 */
व्योम vio_unरेजिस्टर_driver(काष्ठा vio_driver *viodrv)
अणु
	driver_unरेजिस्टर(&viodrv->driver);
पूर्ण
EXPORT_SYMBOL(vio_unरेजिस्टर_driver);

/* vio_dev refcount hit 0 */
अटल व्योम vio_dev_release(काष्ठा device *dev)
अणु
	काष्ठा iommu_table *tbl = get_iommu_table_base(dev);

	अगर (tbl)
		iommu_tce_table_put(tbl);
	of_node_put(dev->of_node);
	kमुक्त(to_vio_dev(dev));
पूर्ण

/**
 * vio_रेजिस्टर_device_node: - Register a new vio device.
 * @of_node:	The OF node क्रम this device.
 *
 * Creates and initializes a vio_dev काष्ठाure from the data in
 * of_node and adds it to the list of भव devices.
 * Returns a poपूर्णांकer to the created vio_dev or शून्य अगर node has
 * शून्य device_type or compatible fields.
 */
काष्ठा vio_dev *vio_रेजिस्टर_device_node(काष्ठा device_node *of_node)
अणु
	काष्ठा vio_dev *viodev;
	काष्ठा device_node *parent_node;
	स्थिर __be32 *prop;
	क्रमागत vio_dev_family family;

	/*
	 * Determine अगर this node is a under the /vdevice node or under the
	 * /ibm,platक्रमm-facilities node.  This decides the device's family.
	 */
	parent_node = of_get_parent(of_node);
	अगर (parent_node) अणु
		अगर (of_node_is_type(parent_node, "ibm,platform-facilities"))
			family = PFO;
		अन्यथा अगर (of_node_is_type(parent_node, "vdevice"))
			family = VDEVICE;
		अन्यथा अणु
			pr_warn("%s: parent(%pOF) of %pOFn not recognized.\n",
					__func__,
					parent_node,
					of_node);
			of_node_put(parent_node);
			वापस शून्य;
		पूर्ण
		of_node_put(parent_node);
	पूर्ण अन्यथा अणु
		pr_warn("%s: could not determine the parent of node %pOFn.\n",
				__func__, of_node);
		वापस शून्य;
	पूर्ण

	अगर (family == PFO) अणु
		अगर (of_get_property(of_node, "interrupt-controller", शून्य)) अणु
			pr_debug("%s: Skipping the interrupt controller %pOFn.\n",
					__func__, of_node);
			वापस शून्य;
		पूर्ण
	पूर्ण

	/* allocate a vio_dev क्रम this node */
	viodev = kzalloc(माप(काष्ठा vio_dev), GFP_KERNEL);
	अगर (viodev == शून्य) अणु
		pr_warn("%s: allocation failure for VIO device.\n", __func__);
		वापस शून्य;
	पूर्ण

	/* we need the 'device_type' property, in order to match with drivers */
	viodev->family = family;
	अगर (viodev->family == VDEVICE) अणु
		अचिन्हित पूर्णांक unit_address;

		viodev->type = of_node_get_device_type(of_node);
		अगर (!viodev->type) अणु
			pr_warn("%s: node %pOFn is missing the 'device_type' "
					"property.\n", __func__, of_node);
			जाओ out;
		पूर्ण

		prop = of_get_property(of_node, "reg", शून्य);
		अगर (prop == शून्य) अणु
			pr_warn("%s: node %pOFn missing 'reg'\n",
					__func__, of_node);
			जाओ out;
		पूर्ण
		unit_address = of_पढ़ो_number(prop, 1);
		dev_set_name(&viodev->dev, "%x", unit_address);
		viodev->irq = irq_of_parse_and_map(of_node, 0);
		viodev->unit_address = unit_address;
	पूर्ण अन्यथा अणु
		/* PFO devices need their resource_id क्रम submitting COP_OPs
		 * This is an optional field क्रम devices, but is required when
		 * perक्रमming synchronous ops */
		prop = of_get_property(of_node, "ibm,resource-id", शून्य);
		अगर (prop != शून्य)
			viodev->resource_id = of_पढ़ो_number(prop, 1);

		dev_set_name(&viodev->dev, "%pOFn", of_node);
		viodev->type = dev_name(&viodev->dev);
		viodev->irq = 0;
	पूर्ण

	viodev->name = of_node->name;
	viodev->dev.of_node = of_node_get(of_node);

	set_dev_node(&viodev->dev, of_node_to_nid(of_node));

	/* init generic 'struct device' fields: */
	viodev->dev.parent = &vio_bus_device.dev;
	viodev->dev.bus = &vio_bus_type;
	viodev->dev.release = vio_dev_release;

	अगर (of_get_property(viodev->dev.of_node, "ibm,my-dma-window", शून्य)) अणु
		अगर (firmware_has_feature(FW_FEATURE_CMO))
			vio_cmo_set_dma_ops(viodev);
		अन्यथा
			set_dma_ops(&viodev->dev, &dma_iommu_ops);

		set_iommu_table_base(&viodev->dev,
				     vio_build_iommu_table(viodev));

		/* needed to ensure proper operation of coherent allocations
		 * later, in हाल driver करोesn't set it explicitly */
		viodev->dev.coherent_dma_mask = DMA_BIT_MASK(64);
		viodev->dev.dma_mask = &viodev->dev.coherent_dma_mask;
	पूर्ण

	/* रेजिस्टर with generic device framework */
	अगर (device_रेजिस्टर(&viodev->dev)) अणु
		prपूर्णांकk(KERN_ERR "%s: failed to register device %s\n",
				__func__, dev_name(&viodev->dev));
		put_device(&viodev->dev);
		वापस शून्य;
	पूर्ण

	वापस viodev;

out:	/* Use this निकास poपूर्णांक क्रम any वापस prior to device_रेजिस्टर */
	kमुक्त(viodev);

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(vio_रेजिस्टर_device_node);

/*
 * vio_bus_scan_क्रम_devices - Scan OF and रेजिस्टर each child device
 * @root_name - OF node name क्रम the root of the subtree to search.
 *		This must be non-शून्य
 *
 * Starting from the root node provide, रेजिस्टर the device node क्रम
 * each child beneath the root.
 */
अटल व्योम vio_bus_scan_रेजिस्टर_devices(अक्षर *root_name)
अणु
	काष्ठा device_node *node_root, *node_child;

	अगर (!root_name)
		वापस;

	node_root = of_find_node_by_name(शून्य, root_name);
	अगर (node_root) अणु

		/*
		 * Create काष्ठा vio_devices क्रम each भव device in
		 * the device tree. Drivers will associate with them later.
		 */
		node_child = of_get_next_child(node_root, शून्य);
		जबतक (node_child) अणु
			vio_रेजिस्टर_device_node(node_child);
			node_child = of_get_next_child(node_root, node_child);
		पूर्ण
		of_node_put(node_root);
	पूर्ण
पूर्ण

/**
 * vio_bus_init: - Initialize the भव IO bus
 */
अटल पूर्णांक __init vio_bus_init(व्योम)
अणु
	पूर्णांक err;

	अगर (firmware_has_feature(FW_FEATURE_CMO))
		vio_cmo_sysfs_init();

	err = bus_रेजिस्टर(&vio_bus_type);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "failed to register VIO bus\n");
		वापस err;
	पूर्ण

	/*
	 * The fake parent of all vio devices, just to give us
	 * a nice directory
	 */
	err = device_रेजिस्टर(&vio_bus_device.dev);
	अगर (err) अणु
		prपूर्णांकk(KERN_WARNING "%s: device_register returned %i\n",
				__func__, err);
		वापस err;
	पूर्ण

	अगर (firmware_has_feature(FW_FEATURE_CMO))
		vio_cmo_bus_init();

	वापस 0;
पूर्ण
machine_postcore_initcall(pseries, vio_bus_init);

अटल पूर्णांक __init vio_device_init(व्योम)
अणु
	vio_bus_scan_रेजिस्टर_devices("vdevice");
	vio_bus_scan_रेजिस्टर_devices("ibm,platform-facilities");

	वापस 0;
पूर्ण
machine_device_initcall(pseries, vio_device_init);

अटल sमाप_प्रकार name_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%s\n", to_vio_dev(dev)->name);
पूर्ण
अटल DEVICE_ATTR_RO(name);

अटल sमाप_प्रकार devspec_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा device_node *of_node = dev->of_node;

	वापस प्र_लिखो(buf, "%pOF\n", of_node);
पूर्ण
अटल DEVICE_ATTR_RO(devspec);

अटल sमाप_प्रकार modalias_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	स्थिर काष्ठा vio_dev *vio_dev = to_vio_dev(dev);
	काष्ठा device_node *dn;
	स्थिर अक्षर *cp;

	dn = dev->of_node;
	अगर (!dn) अणु
		म_नकल(buf, "\n");
		वापस म_माप(buf);
	पूर्ण
	cp = of_get_property(dn, "compatible", शून्य);
	अगर (!cp) अणु
		म_नकल(buf, "\n");
		वापस म_माप(buf);
	पूर्ण

	वापस प्र_लिखो(buf, "vio:T%sS%s\n", vio_dev->type, cp);
पूर्ण
अटल DEVICE_ATTR_RO(modalias);

अटल काष्ठा attribute *vio_dev_attrs[] = अणु
	&dev_attr_name.attr,
	&dev_attr_devspec.attr,
	&dev_attr_modalias.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(vio_dev);

व्योम vio_unरेजिस्टर_device(काष्ठा vio_dev *viodev)
अणु
	device_unरेजिस्टर(&viodev->dev);
	अगर (viodev->family == VDEVICE)
		irq_dispose_mapping(viodev->irq);
पूर्ण
EXPORT_SYMBOL(vio_unरेजिस्टर_device);

अटल पूर्णांक vio_bus_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	स्थिर काष्ठा vio_dev *vio_dev = to_vio_dev(dev);
	काष्ठा vio_driver *vio_drv = to_vio_driver(drv);
	स्थिर काष्ठा vio_device_id *ids = vio_drv->id_table;

	वापस (ids != शून्य) && (vio_match_device(ids, vio_dev) != शून्य);
पूर्ण

अटल पूर्णांक vio_hotplug(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	स्थिर काष्ठा vio_dev *vio_dev = to_vio_dev(dev);
	काष्ठा device_node *dn;
	स्थिर अक्षर *cp;

	dn = dev->of_node;
	अगर (!dn)
		वापस -ENODEV;
	cp = of_get_property(dn, "compatible", शून्य);
	अगर (!cp)
		वापस -ENODEV;

	add_uevent_var(env, "MODALIAS=vio:T%sS%s", vio_dev->type, cp);
	वापस 0;
पूर्ण

काष्ठा bus_type vio_bus_type = अणु
	.name = "vio",
	.dev_groups = vio_dev_groups,
	.uevent = vio_hotplug,
	.match = vio_bus_match,
	.probe = vio_bus_probe,
	.हटाओ = vio_bus_हटाओ,
	.shutकरोwn = vio_bus_shutकरोwn,
पूर्ण;

/**
 * vio_get_attribute: - get attribute क्रम भव device
 * @vdev:	The vio device to get property.
 * @which:	The property/attribute to be extracted.
 * @length:	Poपूर्णांकer to length of वापसed data size (unused अगर शून्य).
 *
 * Calls prom.c's of_get_property() to वापस the value of the
 * attribute specअगरied by @which
*/
स्थिर व्योम *vio_get_attribute(काष्ठा vio_dev *vdev, अक्षर *which, पूर्णांक *length)
अणु
	वापस of_get_property(vdev->dev.of_node, which, length);
पूर्ण
EXPORT_SYMBOL(vio_get_attribute);

/* vio_find_name() - पूर्णांकernal because only vio.c knows how we क्रमmatted the
 * kobject name
 */
अटल काष्ठा vio_dev *vio_find_name(स्थिर अक्षर *name)
अणु
	काष्ठा device *found;

	found = bus_find_device_by_name(&vio_bus_type, शून्य, name);
	अगर (!found)
		वापस शून्य;

	वापस to_vio_dev(found);
पूर्ण

/**
 * vio_find_node - find an alपढ़ोy-रेजिस्टरed vio_dev
 * @vnode: device_node of the भव device we're looking क्रम
 *
 * Takes a reference to the embedded काष्ठा device which needs to be dropped
 * after use.
 */
काष्ठा vio_dev *vio_find_node(काष्ठा device_node *vnode)
अणु
	अक्षर kobj_name[20];
	काष्ठा device_node *vnode_parent;

	vnode_parent = of_get_parent(vnode);
	अगर (!vnode_parent)
		वापस शून्य;

	/* स्थिरruct the kobject name from the device node */
	अगर (of_node_is_type(vnode_parent, "vdevice")) अणु
		स्थिर __be32 *prop;
		
		prop = of_get_property(vnode, "reg", शून्य);
		अगर (!prop)
			जाओ out;
		snम_लिखो(kobj_name, माप(kobj_name), "%x",
			 (uपूर्णांक32_t)of_पढ़ो_number(prop, 1));
	पूर्ण अन्यथा अगर (of_node_is_type(vnode_parent, "ibm,platform-facilities"))
		snम_लिखो(kobj_name, माप(kobj_name), "%pOFn", vnode);
	अन्यथा
		जाओ out;

	of_node_put(vnode_parent);
	वापस vio_find_name(kobj_name);
out:
	of_node_put(vnode_parent);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(vio_find_node);

पूर्णांक vio_enable_पूर्णांकerrupts(काष्ठा vio_dev *dev)
अणु
	पूर्णांक rc = h_vio_संकेत(dev->unit_address, VIO_IRQ_ENABLE);
	अगर (rc != H_SUCCESS)
		prपूर्णांकk(KERN_ERR "vio: Error 0x%x enabling interrupts\n", rc);
	वापस rc;
पूर्ण
EXPORT_SYMBOL(vio_enable_पूर्णांकerrupts);

पूर्णांक vio_disable_पूर्णांकerrupts(काष्ठा vio_dev *dev)
अणु
	पूर्णांक rc = h_vio_संकेत(dev->unit_address, VIO_IRQ_DISABLE);
	अगर (rc != H_SUCCESS)
		prपूर्णांकk(KERN_ERR "vio: Error 0x%x disabling interrupts\n", rc);
	वापस rc;
पूर्ण
EXPORT_SYMBOL(vio_disable_पूर्णांकerrupts);

अटल पूर्णांक __init vio_init(व्योम)
अणु
	dma_debug_add_bus(&vio_bus_type);
	वापस 0;
पूर्ण
machine_fs_initcall(pseries, vio_init);
