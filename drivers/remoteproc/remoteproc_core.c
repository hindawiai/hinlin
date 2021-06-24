<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Remote Processor Framework
 *
 * Copyright (C) 2011 Texas Instruments, Inc.
 * Copyright (C) 2011 Google, Inc.
 *
 * Ohad Ben-Cohen <ohad@wizery.com>
 * Brian Swetland <swetland@google.com>
 * Mark Grosen <mgrosen@ti.com>
 * Fernanकरो Guzman Lugo <fernanकरो.lugo@ti.com>
 * Suman Anna <s-anna@ti.com>
 * Robert Tivy <rtivy@ti.com>
 * Armanकरो Uribe De Leon <x0095078@ti.com>
 */

#घोषणा pr_fmt(fmt)    "%s: " fmt, __func__

#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/slab.h>
#समावेश <linux/mutex.h>
#समावेश <linux/dma-map-ops.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dma-direct.h> /* XXX: pokes पूर्णांकo bus_dma_range */
#समावेश <linux/firmware.h>
#समावेश <linux/माला.स>
#समावेश <linux/debugfs.h>
#समावेश <linux/rculist.h>
#समावेश <linux/remoteproc.h>
#समावेश <linux/iommu.h>
#समावेश <linux/idr.h>
#समावेश <linux/elf.h>
#समावेश <linux/crc32.h>
#समावेश <linux/of_reserved_स्मृति.स>
#समावेश <linux/virtio_ids.h>
#समावेश <linux/virtio_ring.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "remoteproc_internal.h"

#घोषणा HIGH_BITS_MASK 0xFFFFFFFF00000000ULL

अटल DEFINE_MUTEX(rproc_list_mutex);
अटल LIST_HEAD(rproc_list);
अटल काष्ठा notअगरier_block rproc_panic_nb;

प्रकार पूर्णांक (*rproc_handle_resource_t)(काष्ठा rproc *rproc,
				 व्योम *, पूर्णांक offset, पूर्णांक avail);

अटल पूर्णांक rproc_alloc_carveout(काष्ठा rproc *rproc,
				काष्ठा rproc_mem_entry *mem);
अटल पूर्णांक rproc_release_carveout(काष्ठा rproc *rproc,
				  काष्ठा rproc_mem_entry *mem);

/* Unique indices क्रम remoteproc devices */
अटल DEFINE_IDA(rproc_dev_index);

अटल स्थिर अक्षर * स्थिर rproc_crash_names[] = अणु
	[RPROC_MMUFAULT]	= "mmufault",
	[RPROC_WATCHDOG]	= "watchdog",
	[RPROC_FATAL_ERROR]	= "fatal error",
पूर्ण;

/* translate rproc_crash_type to string */
अटल स्थिर अक्षर *rproc_crash_to_string(क्रमागत rproc_crash_type type)
अणु
	अगर (type < ARRAY_SIZE(rproc_crash_names))
		वापस rproc_crash_names[type];
	वापस "unknown";
पूर्ण

/*
 * This is the IOMMU fault handler we रेजिस्टर with the IOMMU API
 * (when relevant; not all remote processors access memory through
 * an IOMMU).
 *
 * IOMMU core will invoke this handler whenever the remote processor
 * will try to access an unmapped device address.
 */
अटल पूर्णांक rproc_iommu_fault(काष्ठा iommu_करोमुख्य *करोमुख्य, काष्ठा device *dev,
			     अचिन्हित दीर्घ iova, पूर्णांक flags, व्योम *token)
अणु
	काष्ठा rproc *rproc = token;

	dev_err(dev, "iommu fault: da 0x%lx flags 0x%x\n", iova, flags);

	rproc_report_crash(rproc, RPROC_MMUFAULT);

	/*
	 * Let the iommu core know we're not really handling this fault;
	 * we just used it as a recovery trigger.
	 */
	वापस -ENOSYS;
पूर्ण

अटल पूर्णांक rproc_enable_iommu(काष्ठा rproc *rproc)
अणु
	काष्ठा iommu_करोमुख्य *करोमुख्य;
	काष्ठा device *dev = rproc->dev.parent;
	पूर्णांक ret;

	अगर (!rproc->has_iommu) अणु
		dev_dbg(dev, "iommu not present\n");
		वापस 0;
	पूर्ण

	करोमुख्य = iommu_करोमुख्य_alloc(dev->bus);
	अगर (!करोमुख्य) अणु
		dev_err(dev, "can't alloc iommu domain\n");
		वापस -ENOMEM;
	पूर्ण

	iommu_set_fault_handler(करोमुख्य, rproc_iommu_fault, rproc);

	ret = iommu_attach_device(करोमुख्य, dev);
	अगर (ret) अणु
		dev_err(dev, "can't attach iommu device: %d\n", ret);
		जाओ मुक्त_करोमुख्य;
	पूर्ण

	rproc->करोमुख्य = करोमुख्य;

	वापस 0;

मुक्त_करोमुख्य:
	iommu_करोमुख्य_मुक्त(करोमुख्य);
	वापस ret;
पूर्ण

अटल व्योम rproc_disable_iommu(काष्ठा rproc *rproc)
अणु
	काष्ठा iommu_करोमुख्य *करोमुख्य = rproc->करोमुख्य;
	काष्ठा device *dev = rproc->dev.parent;

	अगर (!करोमुख्य)
		वापस;

	iommu_detach_device(करोमुख्य, dev);
	iommu_करोमुख्य_मुक्त(करोमुख्य);
पूर्ण

phys_addr_t rproc_va_to_pa(व्योम *cpu_addr)
अणु
	/*
	 * Return physical address according to भव address location
	 * - in vदो_स्मृति: अगर region ioremapped or defined as dma_alloc_coherent
	 * - in kernel: अगर region allocated in generic dma memory pool
	 */
	अगर (is_vदो_स्मृति_addr(cpu_addr)) अणु
		वापस page_to_phys(vदो_स्मृति_to_page(cpu_addr)) +
				    offset_in_page(cpu_addr);
	पूर्ण

	WARN_ON(!virt_addr_valid(cpu_addr));
	वापस virt_to_phys(cpu_addr);
पूर्ण
EXPORT_SYMBOL(rproc_va_to_pa);

/**
 * rproc_da_to_va() - lookup the kernel भव address क्रम a remoteproc address
 * @rproc: handle of a remote processor
 * @da: remoteproc device address to translate
 * @len: length of the memory region @da is poपूर्णांकing to
 *
 * Some remote processors will ask us to allocate them physically contiguous
 * memory regions (which we call "carveouts"), and map them to specअगरic
 * device addresses (which are hardcoded in the firmware). They may also have
 * dedicated memory regions पूर्णांकernal to the processors, and use them either
 * exclusively or aदीर्घside carveouts.
 *
 * They may then ask us to copy objects पूर्णांकo specअगरic device addresses (e.g.
 * code/data sections) or expose us certain symbols in other device address
 * (e.g. their trace buffer).
 *
 * This function is a helper function with which we can go over the allocated
 * carveouts and translate specअगरic device addresses to kernel भव addresses
 * so we can access the referenced memory. This function also allows to perक्रमm
 * translations on the पूर्णांकernal remoteproc memory regions through a platक्रमm
 * implementation specअगरic da_to_va ops, अगर present.
 *
 * The function वापसs a valid kernel address on success or शून्य on failure.
 *
 * Note: phys_to_virt(iommu_iova_to_phys(rproc->करोमुख्य, da)) will work too,
 * but only on kernel direct mapped RAM memory. Instead, we're just using
 * here the output of the DMA API क्रम the carveouts, which should be more
 * correct.
 */
व्योम *rproc_da_to_va(काष्ठा rproc *rproc, u64 da, माप_प्रकार len, bool *is_iomem)
अणु
	काष्ठा rproc_mem_entry *carveout;
	व्योम *ptr = शून्य;

	अगर (rproc->ops->da_to_va) अणु
		ptr = rproc->ops->da_to_va(rproc, da, len, is_iomem);
		अगर (ptr)
			जाओ out;
	पूर्ण

	list_क्रम_each_entry(carveout, &rproc->carveouts, node) अणु
		पूर्णांक offset = da - carveout->da;

		/*  Verअगरy that carveout is allocated */
		अगर (!carveout->va)
			जारी;

		/* try next carveout अगर da is too small */
		अगर (offset < 0)
			जारी;

		/* try next carveout अगर da is too large */
		अगर (offset + len > carveout->len)
			जारी;

		ptr = carveout->va + offset;

		अगर (is_iomem)
			*is_iomem = carveout->is_iomem;

		अवरोध;
	पूर्ण

out:
	वापस ptr;
पूर्ण
EXPORT_SYMBOL(rproc_da_to_va);

/**
 * rproc_find_carveout_by_name() - lookup the carveout region by a name
 * @rproc: handle of a remote processor
 * @name: carveout name to find (क्रमmat string)
 * @...: optional parameters matching @name string
 *
 * Platक्रमm driver has the capability to रेजिस्टर some pre-allacoted carveout
 * (physically contiguous memory regions) beक्रमe rproc firmware loading and
 * associated resource table analysis. These regions may be dedicated memory
 * regions पूर्णांकernal to the coprocessor or specअगरied DDR region with specअगरic
 * attributes
 *
 * This function is a helper function with which we can go over the
 * allocated carveouts and वापस associated region अक्षरacteristics like
 * coprocessor address, length or processor भव address.
 *
 * Return: a valid poपूर्णांकer on carveout entry on success or शून्य on failure.
 */
__म_लिखो(2, 3)
काष्ठा rproc_mem_entry *
rproc_find_carveout_by_name(काष्ठा rproc *rproc, स्थिर अक्षर *name, ...)
अणु
	बहु_सूची args;
	अक्षर _name[32];
	काष्ठा rproc_mem_entry *carveout, *mem = शून्य;

	अगर (!name)
		वापस शून्य;

	बहु_शुरू(args, name);
	vsnम_लिखो(_name, माप(_name), name, args);
	बहु_पूर्ण(args);

	list_क्रम_each_entry(carveout, &rproc->carveouts, node) अणु
		/* Compare carveout and requested names */
		अगर (!म_भेद(carveout->name, _name)) अणु
			mem = carveout;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस mem;
पूर्ण

/**
 * rproc_check_carveout_da() - Check specअगरied carveout da configuration
 * @rproc: handle of a remote processor
 * @mem: poपूर्णांकer on carveout to check
 * @da: area device address
 * @len: associated area size
 *
 * This function is a helper function to verअगरy requested device area (couple
 * da, len) is part of specअगरied carveout.
 * If da is not set (defined as FW_RSC_ADDR_ANY), only requested length is
 * checked.
 *
 * Return: 0 अगर carveout matches request अन्यथा error
 */
अटल पूर्णांक rproc_check_carveout_da(काष्ठा rproc *rproc,
				   काष्ठा rproc_mem_entry *mem, u32 da, u32 len)
अणु
	काष्ठा device *dev = &rproc->dev;
	पूर्णांक delta;

	/* Check requested resource length */
	अगर (len > mem->len) अणु
		dev_err(dev, "Registered carveout doesn't fit len request\n");
		वापस -EINVAL;
	पूर्ण

	अगर (da != FW_RSC_ADDR_ANY && mem->da == FW_RSC_ADDR_ANY) अणु
		/* Address करोesn't match रेजिस्टरed carveout configuration */
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (da != FW_RSC_ADDR_ANY && mem->da != FW_RSC_ADDR_ANY) अणु
		delta = da - mem->da;

		/* Check requested resource beदीर्घs to रेजिस्टरed carveout */
		अगर (delta < 0) अणु
			dev_err(dev,
				"Registered carveout doesn't fit da request\n");
			वापस -EINVAL;
		पूर्ण

		अगर (delta + len > mem->len) अणु
			dev_err(dev,
				"Registered carveout doesn't fit len request\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक rproc_alloc_vring(काष्ठा rproc_vdev *rvdev, पूर्णांक i)
अणु
	काष्ठा rproc *rproc = rvdev->rproc;
	काष्ठा device *dev = &rproc->dev;
	काष्ठा rproc_vring *rvring = &rvdev->vring[i];
	काष्ठा fw_rsc_vdev *rsc;
	पूर्णांक ret, notअगरyid;
	काष्ठा rproc_mem_entry *mem;
	माप_प्रकार size;

	/* actual size of vring (in bytes) */
	size = PAGE_ALIGN(vring_size(rvring->len, rvring->align));

	rsc = (व्योम *)rproc->table_ptr + rvdev->rsc_offset;

	/* Search क्रम pre-रेजिस्टरed carveout */
	mem = rproc_find_carveout_by_name(rproc, "vdev%dvring%d", rvdev->index,
					  i);
	अगर (mem) अणु
		अगर (rproc_check_carveout_da(rproc, mem, rsc->vring[i].da, size))
			वापस -ENOMEM;
	पूर्ण अन्यथा अणु
		/* Register carveout in in list */
		mem = rproc_mem_entry_init(dev, शून्य, 0,
					   size, rsc->vring[i].da,
					   rproc_alloc_carveout,
					   rproc_release_carveout,
					   "vdev%dvring%d",
					   rvdev->index, i);
		अगर (!mem) अणु
			dev_err(dev, "Can't allocate memory entry structure\n");
			वापस -ENOMEM;
		पूर्ण

		rproc_add_carveout(rproc, mem);
	पूर्ण

	/*
	 * Assign an rproc-wide unique index क्रम this vring
	 * TODO: assign a notअगरyid क्रम rvdev updates as well
	 * TODO: support predefined notअगरyids (via resource table)
	 */
	ret = idr_alloc(&rproc->notअगरyids, rvring, 0, 0, GFP_KERNEL);
	अगर (ret < 0) अणु
		dev_err(dev, "idr_alloc failed: %d\n", ret);
		वापस ret;
	पूर्ण
	notअगरyid = ret;

	/* Potentially bump max_notअगरyid */
	अगर (notअगरyid > rproc->max_notअगरyid)
		rproc->max_notअगरyid = notअगरyid;

	rvring->notअगरyid = notअगरyid;

	/* Let the rproc know the notअगरyid of this vring.*/
	rsc->vring[i].notअगरyid = notअगरyid;
	वापस 0;
पूर्ण

अटल पूर्णांक
rproc_parse_vring(काष्ठा rproc_vdev *rvdev, काष्ठा fw_rsc_vdev *rsc, पूर्णांक i)
अणु
	काष्ठा rproc *rproc = rvdev->rproc;
	काष्ठा device *dev = &rproc->dev;
	काष्ठा fw_rsc_vdev_vring *vring = &rsc->vring[i];
	काष्ठा rproc_vring *rvring = &rvdev->vring[i];

	dev_dbg(dev, "vdev rsc: vring%d: da 0x%x, qsz %d, align %d\n",
		i, vring->da, vring->num, vring->align);

	/* verअगरy queue size and vring alignment are sane */
	अगर (!vring->num || !vring->align) अणु
		dev_err(dev, "invalid qsz (%d) or alignment (%d)\n",
			vring->num, vring->align);
		वापस -EINVAL;
	पूर्ण

	rvring->len = vring->num;
	rvring->align = vring->align;
	rvring->rvdev = rvdev;

	वापस 0;
पूर्ण

व्योम rproc_मुक्त_vring(काष्ठा rproc_vring *rvring)
अणु
	काष्ठा rproc *rproc = rvring->rvdev->rproc;
	पूर्णांक idx = rvring - rvring->rvdev->vring;
	काष्ठा fw_rsc_vdev *rsc;

	idr_हटाओ(&rproc->notअगरyids, rvring->notअगरyid);

	/*
	 * At this poपूर्णांक rproc_stop() has been called and the installed resource
	 * table in the remote processor memory may no दीर्घer be accessible. As
	 * such and as per rproc_stop(), rproc->table_ptr poपूर्णांकs to the cached
	 * resource table (rproc->cached_table).  The cached resource table is
	 * only available when a remote processor has been booted by the
	 * remoteproc core, otherwise it is शून्य.
	 *
	 * Based on the above, reset the virtio device section in the cached
	 * resource table only अगर there is one to work with.
	 */
	अगर (rproc->table_ptr) अणु
		rsc = (व्योम *)rproc->table_ptr + rvring->rvdev->rsc_offset;
		rsc->vring[idx].da = 0;
		rsc->vring[idx].notअगरyid = -1;
	पूर्ण
पूर्ण

अटल पूर्णांक rproc_vdev_करो_start(काष्ठा rproc_subdev *subdev)
अणु
	काष्ठा rproc_vdev *rvdev = container_of(subdev, काष्ठा rproc_vdev, subdev);

	वापस rproc_add_virtio_dev(rvdev, rvdev->id);
पूर्ण

अटल व्योम rproc_vdev_करो_stop(काष्ठा rproc_subdev *subdev, bool crashed)
अणु
	काष्ठा rproc_vdev *rvdev = container_of(subdev, काष्ठा rproc_vdev, subdev);
	पूर्णांक ret;

	ret = device_क्रम_each_child(&rvdev->dev, शून्य, rproc_हटाओ_virtio_dev);
	अगर (ret)
		dev_warn(&rvdev->dev, "can't remove vdev child device: %d\n", ret);
पूर्ण

/**
 * rproc_rvdev_release() - release the existence of a rvdev
 *
 * @dev: the subdevice's dev
 */
अटल व्योम rproc_rvdev_release(काष्ठा device *dev)
अणु
	काष्ठा rproc_vdev *rvdev = container_of(dev, काष्ठा rproc_vdev, dev);

	of_reserved_mem_device_release(dev);

	kमुक्त(rvdev);
पूर्ण

अटल पूर्णांक copy_dma_range_map(काष्ठा device *to, काष्ठा device *from)
अणु
	स्थिर काष्ठा bus_dma_region *map = from->dma_range_map, *new_map, *r;
	पूर्णांक num_ranges = 0;

	अगर (!map)
		वापस 0;

	क्रम (r = map; r->size; r++)
		num_ranges++;

	new_map = kmemdup(map, array_size(num_ranges + 1, माप(*map)),
			  GFP_KERNEL);
	अगर (!new_map)
		वापस -ENOMEM;
	to->dma_range_map = new_map;
	वापस 0;
पूर्ण

/**
 * rproc_handle_vdev() - handle a vdev fw resource
 * @rproc: the remote processor
 * @ptr: the vring resource descriptor
 * @offset: offset of the resource entry
 * @avail: size of available data (क्रम sanity checking the image)
 *
 * This resource entry requests the host to अटलally रेजिस्टर a virtio
 * device (vdev), and setup everything needed to support it. It contains
 * everything needed to make it possible: the virtio device id, virtio
 * device features, vrings inक्रमmation, virtio config space, etc...
 *
 * Beक्रमe रेजिस्टरing the vdev, the vrings are allocated from non-cacheable
 * physically contiguous memory. Currently we only support two vrings per
 * remote processor (temporary limitation). We might also want to consider
 * करोing the vring allocation only later when ->find_vqs() is invoked, and
 * then release them upon ->del_vqs().
 *
 * Note: @da is currently not really handled correctly: we dynamically
 * allocate it using the DMA API, ignoring requested hard coded addresses,
 * and we करोn't take care of any required IOMMU programming. This is all
 * going to be taken care of when the generic iommu-based DMA API will be
 * merged. Meanजबतक, अटलally-addressed iommu-based firmware images should
 * use RSC_DEVMEM resource entries to map their required @da to the physical
 * address of their base CMA region (ouch, hacky!).
 *
 * Returns 0 on success, or an appropriate error code otherwise
 */
अटल पूर्णांक rproc_handle_vdev(काष्ठा rproc *rproc, व्योम *ptr,
			     पूर्णांक offset, पूर्णांक avail)
अणु
	काष्ठा fw_rsc_vdev *rsc = ptr;
	काष्ठा device *dev = &rproc->dev;
	काष्ठा rproc_vdev *rvdev;
	पूर्णांक i, ret;
	अक्षर name[16];

	/* make sure resource isn't truncated */
	अगर (काष्ठा_size(rsc, vring, rsc->num_of_vrings) + rsc->config_len >
			avail) अणु
		dev_err(dev, "vdev rsc is truncated\n");
		वापस -EINVAL;
	पूर्ण

	/* make sure reserved bytes are zeroes */
	अगर (rsc->reserved[0] || rsc->reserved[1]) अणु
		dev_err(dev, "vdev rsc has non zero reserved bytes\n");
		वापस -EINVAL;
	पूर्ण

	dev_dbg(dev, "vdev rsc: id %d, dfeatures 0x%x, cfg len %d, %d vrings\n",
		rsc->id, rsc->dfeatures, rsc->config_len, rsc->num_of_vrings);

	/* we currently support only two vrings per rvdev */
	अगर (rsc->num_of_vrings > ARRAY_SIZE(rvdev->vring)) अणु
		dev_err(dev, "too many vrings: %d\n", rsc->num_of_vrings);
		वापस -EINVAL;
	पूर्ण

	rvdev = kzalloc(माप(*rvdev), GFP_KERNEL);
	अगर (!rvdev)
		वापस -ENOMEM;

	kref_init(&rvdev->refcount);

	rvdev->id = rsc->id;
	rvdev->rproc = rproc;
	rvdev->index = rproc->nb_vdev++;

	/* Initialise vdev subdevice */
	snम_लिखो(name, माप(name), "vdev%dbuffer", rvdev->index);
	rvdev->dev.parent = &rproc->dev;
	ret = copy_dma_range_map(&rvdev->dev, rproc->dev.parent);
	अगर (ret)
		वापस ret;
	rvdev->dev.release = rproc_rvdev_release;
	dev_set_name(&rvdev->dev, "%s#%s", dev_name(rvdev->dev.parent), name);
	dev_set_drvdata(&rvdev->dev, rvdev);

	ret = device_रेजिस्टर(&rvdev->dev);
	अगर (ret) अणु
		put_device(&rvdev->dev);
		वापस ret;
	पूर्ण
	/* Make device dma capable by inheriting from parent's capabilities */
	set_dma_ops(&rvdev->dev, get_dma_ops(rproc->dev.parent));

	ret = dma_coerce_mask_and_coherent(&rvdev->dev,
					   dma_get_mask(rproc->dev.parent));
	अगर (ret) अणु
		dev_warn(dev,
			 "Failed to set DMA mask %llx. Trying to continue... %x\n",
			 dma_get_mask(rproc->dev.parent), ret);
	पूर्ण

	/* parse the vrings */
	क्रम (i = 0; i < rsc->num_of_vrings; i++) अणु
		ret = rproc_parse_vring(rvdev, rsc, i);
		अगर (ret)
			जाओ मुक्त_rvdev;
	पूर्ण

	/* remember the resource offset*/
	rvdev->rsc_offset = offset;

	/* allocate the vring resources */
	क्रम (i = 0; i < rsc->num_of_vrings; i++) अणु
		ret = rproc_alloc_vring(rvdev, i);
		अगर (ret)
			जाओ unwind_vring_allocations;
	पूर्ण

	list_add_tail(&rvdev->node, &rproc->rvdevs);

	rvdev->subdev.start = rproc_vdev_करो_start;
	rvdev->subdev.stop = rproc_vdev_करो_stop;

	rproc_add_subdev(rproc, &rvdev->subdev);

	वापस 0;

unwind_vring_allocations:
	क्रम (i--; i >= 0; i--)
		rproc_मुक्त_vring(&rvdev->vring[i]);
मुक्त_rvdev:
	device_unरेजिस्टर(&rvdev->dev);
	वापस ret;
पूर्ण

व्योम rproc_vdev_release(काष्ठा kref *ref)
अणु
	काष्ठा rproc_vdev *rvdev = container_of(ref, काष्ठा rproc_vdev, refcount);
	काष्ठा rproc_vring *rvring;
	काष्ठा rproc *rproc = rvdev->rproc;
	पूर्णांक id;

	क्रम (id = 0; id < ARRAY_SIZE(rvdev->vring); id++) अणु
		rvring = &rvdev->vring[id];
		rproc_मुक्त_vring(rvring);
	पूर्ण

	rproc_हटाओ_subdev(rproc, &rvdev->subdev);
	list_del(&rvdev->node);
	device_unरेजिस्टर(&rvdev->dev);
पूर्ण

/**
 * rproc_handle_trace() - handle a shared trace buffer resource
 * @rproc: the remote processor
 * @ptr: the trace resource descriptor
 * @offset: offset of the resource entry
 * @avail: size of available data (क्रम sanity checking the image)
 *
 * In हाल the remote processor dumps trace logs पूर्णांकo memory,
 * export it via debugfs.
 *
 * Currently, the 'da' member of @rsc should contain the device address
 * where the remote processor is dumping the traces. Later we could also
 * support dynamically allocating this address using the generic
 * DMA API (but currently there isn't a use हाल क्रम that).
 *
 * Returns 0 on success, or an appropriate error code otherwise
 */
अटल पूर्णांक rproc_handle_trace(काष्ठा rproc *rproc, व्योम *ptr,
			      पूर्णांक offset, पूर्णांक avail)
अणु
	काष्ठा fw_rsc_trace *rsc = ptr;
	काष्ठा rproc_debug_trace *trace;
	काष्ठा device *dev = &rproc->dev;
	अक्षर name[15];

	अगर (माप(*rsc) > avail) अणु
		dev_err(dev, "trace rsc is truncated\n");
		वापस -EINVAL;
	पूर्ण

	/* make sure reserved bytes are zeroes */
	अगर (rsc->reserved) अणु
		dev_err(dev, "trace rsc has non zero reserved bytes\n");
		वापस -EINVAL;
	पूर्ण

	trace = kzalloc(माप(*trace), GFP_KERNEL);
	अगर (!trace)
		वापस -ENOMEM;

	/* set the trace buffer dma properties */
	trace->trace_mem.len = rsc->len;
	trace->trace_mem.da = rsc->da;

	/* set poपूर्णांकer on rproc device */
	trace->rproc = rproc;

	/* make sure snम_लिखो always null terminates, even अगर truncating */
	snम_लिखो(name, माप(name), "trace%d", rproc->num_traces);

	/* create the debugfs entry */
	trace->tfile = rproc_create_trace_file(name, rproc, trace);
	अगर (!trace->tfile) अणु
		kमुक्त(trace);
		वापस -EINVAL;
	पूर्ण

	list_add_tail(&trace->node, &rproc->traces);

	rproc->num_traces++;

	dev_dbg(dev, "%s added: da 0x%x, len 0x%x\n",
		name, rsc->da, rsc->len);

	वापस 0;
पूर्ण

/**
 * rproc_handle_devmem() - handle devmem resource entry
 * @rproc: remote processor handle
 * @ptr: the devmem resource entry
 * @offset: offset of the resource entry
 * @avail: size of available data (क्रम sanity checking the image)
 *
 * Remote processors commonly need to access certain on-chip peripherals.
 *
 * Some of these remote processors access memory via an iommu device,
 * and might require us to configure their iommu beक्रमe they can access
 * the on-chip peripherals they need.
 *
 * This resource entry is a request to map such a peripheral device.
 *
 * These devmem entries will contain the physical address of the device in
 * the 'pa' member. If a specific device address is expected, then 'da' will
 * contain it (currently this is the only use हाल supported). 'len' will
 * contain the size of the physical region we need to map.
 *
 * Currently we just "trust" those devmem entries to contain valid physical
 * addresses, but this is going to change: we want the implementations to
 * tell us ranges of physical addresses the firmware is allowed to request,
 * and not allow firmwares to request access to physical addresses that
 * are outside those ranges.
 */
अटल पूर्णांक rproc_handle_devmem(काष्ठा rproc *rproc, व्योम *ptr,
			       पूर्णांक offset, पूर्णांक avail)
अणु
	काष्ठा fw_rsc_devmem *rsc = ptr;
	काष्ठा rproc_mem_entry *mapping;
	काष्ठा device *dev = &rproc->dev;
	पूर्णांक ret;

	/* no poपूर्णांक in handling this resource without a valid iommu करोमुख्य */
	अगर (!rproc->करोमुख्य)
		वापस -EINVAL;

	अगर (माप(*rsc) > avail) अणु
		dev_err(dev, "devmem rsc is truncated\n");
		वापस -EINVAL;
	पूर्ण

	/* make sure reserved bytes are zeroes */
	अगर (rsc->reserved) अणु
		dev_err(dev, "devmem rsc has non zero reserved bytes\n");
		वापस -EINVAL;
	पूर्ण

	mapping = kzalloc(माप(*mapping), GFP_KERNEL);
	अगर (!mapping)
		वापस -ENOMEM;

	ret = iommu_map(rproc->करोमुख्य, rsc->da, rsc->pa, rsc->len, rsc->flags);
	अगर (ret) अणु
		dev_err(dev, "failed to map devmem: %d\n", ret);
		जाओ out;
	पूर्ण

	/*
	 * We'll need this info later when we'll want to unmap everything
	 * (e.g. on shutकरोwn).
	 *
	 * We can't trust the remote processor not to change the resource
	 * table, so we must मुख्यtain this info independently.
	 */
	mapping->da = rsc->da;
	mapping->len = rsc->len;
	list_add_tail(&mapping->node, &rproc->mappings);

	dev_dbg(dev, "mapped devmem pa 0x%x, da 0x%x, len 0x%x\n",
		rsc->pa, rsc->da, rsc->len);

	वापस 0;

out:
	kमुक्त(mapping);
	वापस ret;
पूर्ण

/**
 * rproc_alloc_carveout() - allocated specअगरied carveout
 * @rproc: rproc handle
 * @mem: the memory entry to allocate
 *
 * This function allocate specअगरied memory entry @mem using
 * dma_alloc_coherent() as शेष allocator
 */
अटल पूर्णांक rproc_alloc_carveout(काष्ठा rproc *rproc,
				काष्ठा rproc_mem_entry *mem)
अणु
	काष्ठा rproc_mem_entry *mapping = शून्य;
	काष्ठा device *dev = &rproc->dev;
	dma_addr_t dma;
	व्योम *va;
	पूर्णांक ret;

	va = dma_alloc_coherent(dev->parent, mem->len, &dma, GFP_KERNEL);
	अगर (!va) अणु
		dev_err(dev->parent,
			"failed to allocate dma memory: len 0x%zx\n",
			mem->len);
		वापस -ENOMEM;
	पूर्ण

	dev_dbg(dev, "carveout va %pK, dma %pad, len 0x%zx\n",
		va, &dma, mem->len);

	अगर (mem->da != FW_RSC_ADDR_ANY && !rproc->करोमुख्य) अणु
		/*
		 * Check requested da is equal to dma address
		 * and prपूर्णांक a warn message in हाल of missalignment.
		 * Don't stop rproc_start sequence as coprocessor may
		 * build pa to da translation on its side.
		 */
		अगर (mem->da != (u32)dma)
			dev_warn(dev->parent,
				 "Allocated carveout doesn't fit device address request\n");
	पूर्ण

	/*
	 * Ok, this is non-standard.
	 *
	 * Someबार we can't rely on the generic iommu-based DMA API
	 * to dynamically allocate the device address and then set the IOMMU
	 * tables accordingly, because some remote processors might
	 * _require_ us to use hard coded device addresses that their
	 * firmware was compiled with.
	 *
	 * In this हाल, we must use the IOMMU API directly and map
	 * the memory to the device address as expected by the remote
	 * processor.
	 *
	 * Obviously such remote processor devices should not be configured
	 * to use the iommu-based DMA API: we expect 'dma' to contain the
	 * physical address in this हाल.
	 */
	अगर (mem->da != FW_RSC_ADDR_ANY && rproc->करोमुख्य) अणु
		mapping = kzalloc(माप(*mapping), GFP_KERNEL);
		अगर (!mapping) अणु
			ret = -ENOMEM;
			जाओ dma_मुक्त;
		पूर्ण

		ret = iommu_map(rproc->करोमुख्य, mem->da, dma, mem->len,
				mem->flags);
		अगर (ret) अणु
			dev_err(dev, "iommu_map failed: %d\n", ret);
			जाओ मुक्त_mapping;
		पूर्ण

		/*
		 * We'll need this info later when we'll want to unmap
		 * everything (e.g. on shutकरोwn).
		 *
		 * We can't trust the remote processor not to change the
		 * resource table, so we must मुख्यtain this info independently.
		 */
		mapping->da = mem->da;
		mapping->len = mem->len;
		list_add_tail(&mapping->node, &rproc->mappings);

		dev_dbg(dev, "carveout mapped 0x%x to %pad\n",
			mem->da, &dma);
	पूर्ण

	अगर (mem->da == FW_RSC_ADDR_ANY) अणु
		/* Update device address as undefined by requester */
		अगर ((u64)dma & HIGH_BITS_MASK)
			dev_warn(dev, "DMA address cast in 32bit to fit resource table format\n");

		mem->da = (u32)dma;
	पूर्ण

	mem->dma = dma;
	mem->va = va;

	वापस 0;

मुक्त_mapping:
	kमुक्त(mapping);
dma_मुक्त:
	dma_मुक्त_coherent(dev->parent, mem->len, va, dma);
	वापस ret;
पूर्ण

/**
 * rproc_release_carveout() - release acquired carveout
 * @rproc: rproc handle
 * @mem: the memory entry to release
 *
 * This function releases specअगरied memory entry @mem allocated via
 * rproc_alloc_carveout() function by @rproc.
 */
अटल पूर्णांक rproc_release_carveout(काष्ठा rproc *rproc,
				  काष्ठा rproc_mem_entry *mem)
अणु
	काष्ठा device *dev = &rproc->dev;

	/* clean up carveout allocations */
	dma_मुक्त_coherent(dev->parent, mem->len, mem->va, mem->dma);
	वापस 0;
पूर्ण

/**
 * rproc_handle_carveout() - handle phys contig memory allocation requests
 * @rproc: rproc handle
 * @ptr: the resource entry
 * @offset: offset of the resource entry
 * @avail: size of available data (क्रम image validation)
 *
 * This function will handle firmware requests क्रम allocation of physically
 * contiguous memory regions.
 *
 * These request entries should come first in the firmware's resource table,
 * as other firmware entries might request placing other data objects inside
 * these memory regions (e.g. data/code segments, trace resource entries, ...).
 *
 * Allocating memory this way helps utilizing the reserved physical memory
 * (e.g. CMA) more efficiently, and also minimizes the number of TLB entries
 * needed to map it (in हाल @rproc is using an IOMMU). Reducing the TLB
 * pressure is important; it may have a substantial impact on perक्रमmance.
 */
अटल पूर्णांक rproc_handle_carveout(काष्ठा rproc *rproc,
				 व्योम *ptr, पूर्णांक offset, पूर्णांक avail)
अणु
	काष्ठा fw_rsc_carveout *rsc = ptr;
	काष्ठा rproc_mem_entry *carveout;
	काष्ठा device *dev = &rproc->dev;

	अगर (माप(*rsc) > avail) अणु
		dev_err(dev, "carveout rsc is truncated\n");
		वापस -EINVAL;
	पूर्ण

	/* make sure reserved bytes are zeroes */
	अगर (rsc->reserved) अणु
		dev_err(dev, "carveout rsc has non zero reserved bytes\n");
		वापस -EINVAL;
	पूर्ण

	dev_dbg(dev, "carveout rsc: name: %s, da 0x%x, pa 0x%x, len 0x%x, flags 0x%x\n",
		rsc->name, rsc->da, rsc->pa, rsc->len, rsc->flags);

	/*
	 * Check carveout rsc alपढ़ोy part of a रेजिस्टरed carveout,
	 * Search by name, then check the da and length
	 */
	carveout = rproc_find_carveout_by_name(rproc, rsc->name);

	अगर (carveout) अणु
		अगर (carveout->rsc_offset != FW_RSC_ADDR_ANY) अणु
			dev_err(dev,
				"Carveout already associated to resource table\n");
			वापस -ENOMEM;
		पूर्ण

		अगर (rproc_check_carveout_da(rproc, carveout, rsc->da, rsc->len))
			वापस -ENOMEM;

		/* Update memory carveout with resource table info */
		carveout->rsc_offset = offset;
		carveout->flags = rsc->flags;

		वापस 0;
	पूर्ण

	/* Register carveout in in list */
	carveout = rproc_mem_entry_init(dev, शून्य, 0, rsc->len, rsc->da,
					rproc_alloc_carveout,
					rproc_release_carveout, rsc->name);
	अगर (!carveout) अणु
		dev_err(dev, "Can't allocate memory entry structure\n");
		वापस -ENOMEM;
	पूर्ण

	carveout->flags = rsc->flags;
	carveout->rsc_offset = offset;
	rproc_add_carveout(rproc, carveout);

	वापस 0;
पूर्ण

/**
 * rproc_add_carveout() - रेजिस्टर an allocated carveout region
 * @rproc: rproc handle
 * @mem: memory entry to रेजिस्टर
 *
 * This function रेजिस्टरs specअगरied memory entry in @rproc carveouts list.
 * Specअगरied carveout should have been allocated beक्रमe रेजिस्टरing.
 */
व्योम rproc_add_carveout(काष्ठा rproc *rproc, काष्ठा rproc_mem_entry *mem)
अणु
	list_add_tail(&mem->node, &rproc->carveouts);
पूर्ण
EXPORT_SYMBOL(rproc_add_carveout);

/**
 * rproc_mem_entry_init() - allocate and initialize rproc_mem_entry काष्ठा
 * @dev: poपूर्णांकer on device काष्ठा
 * @va: भव address
 * @dma: dma address
 * @len: memory carveout length
 * @da: device address
 * @alloc: memory carveout allocation function
 * @release: memory carveout release function
 * @name: carveout name
 *
 * This function allocates a rproc_mem_entry काष्ठा and fill it with parameters
 * provided by client.
 */
__म_लिखो(8, 9)
काष्ठा rproc_mem_entry *
rproc_mem_entry_init(काष्ठा device *dev,
		     व्योम *va, dma_addr_t dma, माप_प्रकार len, u32 da,
		     पूर्णांक (*alloc)(काष्ठा rproc *, काष्ठा rproc_mem_entry *),
		     पूर्णांक (*release)(काष्ठा rproc *, काष्ठा rproc_mem_entry *),
		     स्थिर अक्षर *name, ...)
अणु
	काष्ठा rproc_mem_entry *mem;
	बहु_सूची args;

	mem = kzalloc(माप(*mem), GFP_KERNEL);
	अगर (!mem)
		वापस mem;

	mem->va = va;
	mem->dma = dma;
	mem->da = da;
	mem->len = len;
	mem->alloc = alloc;
	mem->release = release;
	mem->rsc_offset = FW_RSC_ADDR_ANY;
	mem->of_resm_idx = -1;

	बहु_शुरू(args, name);
	vsnम_लिखो(mem->name, माप(mem->name), name, args);
	बहु_पूर्ण(args);

	वापस mem;
पूर्ण
EXPORT_SYMBOL(rproc_mem_entry_init);

/**
 * rproc_of_resm_mem_entry_init() - allocate and initialize rproc_mem_entry काष्ठा
 * from a reserved memory phandle
 * @dev: poपूर्णांकer on device काष्ठा
 * @of_resm_idx: reserved memory phandle index in "memory-region"
 * @len: memory carveout length
 * @da: device address
 * @name: carveout name
 *
 * This function allocates a rproc_mem_entry काष्ठा and fill it with parameters
 * provided by client.
 */
__म_लिखो(5, 6)
काष्ठा rproc_mem_entry *
rproc_of_resm_mem_entry_init(काष्ठा device *dev, u32 of_resm_idx, माप_प्रकार len,
			     u32 da, स्थिर अक्षर *name, ...)
अणु
	काष्ठा rproc_mem_entry *mem;
	बहु_सूची args;

	mem = kzalloc(माप(*mem), GFP_KERNEL);
	अगर (!mem)
		वापस mem;

	mem->da = da;
	mem->len = len;
	mem->rsc_offset = FW_RSC_ADDR_ANY;
	mem->of_resm_idx = of_resm_idx;

	बहु_शुरू(args, name);
	vsnम_लिखो(mem->name, माप(mem->name), name, args);
	बहु_पूर्ण(args);

	वापस mem;
पूर्ण
EXPORT_SYMBOL(rproc_of_resm_mem_entry_init);

/**
 * rproc_of_parse_firmware() - parse and वापस the firmware-name
 * @dev: poपूर्णांकer on device काष्ठा representing a rproc
 * @index: index to use क्रम the firmware-name retrieval
 * @fw_name: poपूर्णांकer to a अक्षरacter string, in which the firmware
 *           name is वापसed on success and unmodअगरied otherwise.
 *
 * This is an OF helper function that parses a device's DT node क्रम
 * the "firmware-name" property and वापसs the firmware name poपूर्णांकer
 * in @fw_name on success.
 *
 * Return: 0 on success, or an appropriate failure.
 */
पूर्णांक rproc_of_parse_firmware(काष्ठा device *dev, पूर्णांक index, स्थिर अक्षर **fw_name)
अणु
	पूर्णांक ret;

	ret = of_property_पढ़ो_string_index(dev->of_node, "firmware-name",
					    index, fw_name);
	वापस ret ? ret : 0;
पूर्ण
EXPORT_SYMBOL(rproc_of_parse_firmware);

/*
 * A lookup table क्रम resource handlers. The indices are defined in
 * क्रमागत fw_resource_type.
 */
अटल rproc_handle_resource_t rproc_loading_handlers[RSC_LAST] = अणु
	[RSC_CARVEOUT] = rproc_handle_carveout,
	[RSC_DEVMEM] = rproc_handle_devmem,
	[RSC_TRACE] = rproc_handle_trace,
	[RSC_VDEV] = rproc_handle_vdev,
पूर्ण;

/* handle firmware resource entries beक्रमe booting the remote processor */
अटल पूर्णांक rproc_handle_resources(काष्ठा rproc *rproc,
				  rproc_handle_resource_t handlers[RSC_LAST])
अणु
	काष्ठा device *dev = &rproc->dev;
	rproc_handle_resource_t handler;
	पूर्णांक ret = 0, i;

	अगर (!rproc->table_ptr)
		वापस 0;

	क्रम (i = 0; i < rproc->table_ptr->num; i++) अणु
		पूर्णांक offset = rproc->table_ptr->offset[i];
		काष्ठा fw_rsc_hdr *hdr = (व्योम *)rproc->table_ptr + offset;
		पूर्णांक avail = rproc->table_sz - offset - माप(*hdr);
		व्योम *rsc = (व्योम *)hdr + माप(*hdr);

		/* make sure table isn't truncated */
		अगर (avail < 0) अणु
			dev_err(dev, "rsc table is truncated\n");
			वापस -EINVAL;
		पूर्ण

		dev_dbg(dev, "rsc: type %d\n", hdr->type);

		अगर (hdr->type >= RSC_VENDOR_START &&
		    hdr->type <= RSC_VENDOR_END) अणु
			ret = rproc_handle_rsc(rproc, hdr->type, rsc,
					       offset + माप(*hdr), avail);
			अगर (ret == RSC_HANDLED)
				जारी;
			अन्यथा अगर (ret < 0)
				अवरोध;

			dev_warn(dev, "unsupported vendor resource %d\n",
				 hdr->type);
			जारी;
		पूर्ण

		अगर (hdr->type >= RSC_LAST) अणु
			dev_warn(dev, "unsupported resource %d\n", hdr->type);
			जारी;
		पूर्ण

		handler = handlers[hdr->type];
		अगर (!handler)
			जारी;

		ret = handler(rproc, rsc, offset + माप(*hdr), avail);
		अगर (ret)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक rproc_prepare_subdevices(काष्ठा rproc *rproc)
अणु
	काष्ठा rproc_subdev *subdev;
	पूर्णांक ret;

	list_क्रम_each_entry(subdev, &rproc->subdevs, node) अणु
		अगर (subdev->prepare) अणु
			ret = subdev->prepare(subdev);
			अगर (ret)
				जाओ unroll_preparation;
		पूर्ण
	पूर्ण

	वापस 0;

unroll_preparation:
	list_क्रम_each_entry_जारी_reverse(subdev, &rproc->subdevs, node) अणु
		अगर (subdev->unprepare)
			subdev->unprepare(subdev);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक rproc_start_subdevices(काष्ठा rproc *rproc)
अणु
	काष्ठा rproc_subdev *subdev;
	पूर्णांक ret;

	list_क्रम_each_entry(subdev, &rproc->subdevs, node) अणु
		अगर (subdev->start) अणु
			ret = subdev->start(subdev);
			अगर (ret)
				जाओ unroll_registration;
		पूर्ण
	पूर्ण

	वापस 0;

unroll_registration:
	list_क्रम_each_entry_जारी_reverse(subdev, &rproc->subdevs, node) अणु
		अगर (subdev->stop)
			subdev->stop(subdev, true);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम rproc_stop_subdevices(काष्ठा rproc *rproc, bool crashed)
अणु
	काष्ठा rproc_subdev *subdev;

	list_क्रम_each_entry_reverse(subdev, &rproc->subdevs, node) अणु
		अगर (subdev->stop)
			subdev->stop(subdev, crashed);
	पूर्ण
पूर्ण

अटल व्योम rproc_unprepare_subdevices(काष्ठा rproc *rproc)
अणु
	काष्ठा rproc_subdev *subdev;

	list_क्रम_each_entry_reverse(subdev, &rproc->subdevs, node) अणु
		अगर (subdev->unprepare)
			subdev->unprepare(subdev);
	पूर्ण
पूर्ण

/**
 * rproc_alloc_रेजिस्टरed_carveouts() - allocate all carveouts रेजिस्टरed
 * in the list
 * @rproc: the remote processor handle
 *
 * This function parses रेजिस्टरed carveout list, perक्रमms allocation
 * अगर alloc() ops रेजिस्टरed and updates resource table inक्रमmation
 * अगर rsc_offset set.
 *
 * Return: 0 on success
 */
अटल पूर्णांक rproc_alloc_रेजिस्टरed_carveouts(काष्ठा rproc *rproc)
अणु
	काष्ठा rproc_mem_entry *entry, *पंचांगp;
	काष्ठा fw_rsc_carveout *rsc;
	काष्ठा device *dev = &rproc->dev;
	u64 pa;
	पूर्णांक ret;

	list_क्रम_each_entry_safe(entry, पंचांगp, &rproc->carveouts, node) अणु
		अगर (entry->alloc) अणु
			ret = entry->alloc(rproc, entry);
			अगर (ret) अणु
				dev_err(dev, "Unable to allocate carveout %s: %d\n",
					entry->name, ret);
				वापस -ENOMEM;
			पूर्ण
		पूर्ण

		अगर (entry->rsc_offset != FW_RSC_ADDR_ANY) अणु
			/* update resource table */
			rsc = (व्योम *)rproc->table_ptr + entry->rsc_offset;

			/*
			 * Some remote processors might need to know the pa
			 * even though they are behind an IOMMU. E.g., OMAP4's
			 * remote M3 processor needs this so it can control
			 * on-chip hardware accelerators that are not behind
			 * the IOMMU, and thereक्रम must know the pa.
			 *
			 * Generally we करोn't want to expose physical addresses
			 * अगर we करोn't have to (remote processors are generally
			 * _not_ trusted), so we might want to करो this only क्रम
			 * remote processor that _must_ have this (e.g. OMAP4's
			 * dual M3 subप्रणाली).
			 *
			 * Non-IOMMU processors might also want to have this info.
			 * In this हाल, the device address and the physical address
			 * are the same.
			 */

			/* Use va अगर defined अन्यथा dma to generate pa */
			अगर (entry->va)
				pa = (u64)rproc_va_to_pa(entry->va);
			अन्यथा
				pa = (u64)entry->dma;

			अगर (((u64)pa) & HIGH_BITS_MASK)
				dev_warn(dev,
					 "Physical address cast in 32bit to fit resource table format\n");

			rsc->pa = (u32)pa;
			rsc->da = entry->da;
			rsc->len = entry->len;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण


/**
 * rproc_resource_cleanup() - clean up and मुक्त all acquired resources
 * @rproc: rproc handle
 *
 * This function will मुक्त all resources acquired क्रम @rproc, and it
 * is called whenever @rproc either shuts करोwn or fails to boot.
 */
व्योम rproc_resource_cleanup(काष्ठा rproc *rproc)
अणु
	काष्ठा rproc_mem_entry *entry, *पंचांगp;
	काष्ठा rproc_debug_trace *trace, *tपंचांगp;
	काष्ठा rproc_vdev *rvdev, *rvपंचांगp;
	काष्ठा device *dev = &rproc->dev;

	/* clean up debugfs trace entries */
	list_क्रम_each_entry_safe(trace, tपंचांगp, &rproc->traces, node) अणु
		rproc_हटाओ_trace_file(trace->tfile);
		rproc->num_traces--;
		list_del(&trace->node);
		kमुक्त(trace);
	पूर्ण

	/* clean up iommu mapping entries */
	list_क्रम_each_entry_safe(entry, पंचांगp, &rproc->mappings, node) अणु
		माप_प्रकार unmapped;

		unmapped = iommu_unmap(rproc->करोमुख्य, entry->da, entry->len);
		अगर (unmapped != entry->len) अणु
			/* nothing much to करो besides complaining */
			dev_err(dev, "failed to unmap %zx/%zu\n", entry->len,
				unmapped);
		पूर्ण

		list_del(&entry->node);
		kमुक्त(entry);
	पूर्ण

	/* clean up carveout allocations */
	list_क्रम_each_entry_safe(entry, पंचांगp, &rproc->carveouts, node) अणु
		अगर (entry->release)
			entry->release(rproc, entry);
		list_del(&entry->node);
		kमुक्त(entry);
	पूर्ण

	/* clean up remote vdev entries */
	list_क्रम_each_entry_safe(rvdev, rvपंचांगp, &rproc->rvdevs, node)
		kref_put(&rvdev->refcount, rproc_vdev_release);

	rproc_coredump_cleanup(rproc);
पूर्ण
EXPORT_SYMBOL(rproc_resource_cleanup);

अटल पूर्णांक rproc_start(काष्ठा rproc *rproc, स्थिर काष्ठा firmware *fw)
अणु
	काष्ठा resource_table *loaded_table;
	काष्ठा device *dev = &rproc->dev;
	पूर्णांक ret;

	/* load the ELF segments to memory */
	ret = rproc_load_segments(rproc, fw);
	अगर (ret) अणु
		dev_err(dev, "Failed to load program segments: %d\n", ret);
		वापस ret;
	पूर्ण

	/*
	 * The starting device has been given the rproc->cached_table as the
	 * resource table. The address of the vring aदीर्घ with the other
	 * allocated resources (carveouts etc) is stored in cached_table.
	 * In order to pass this inक्रमmation to the remote device we must copy
	 * this inक्रमmation to device memory. We also update the table_ptr so
	 * that any subsequent changes will be applied to the loaded version.
	 */
	loaded_table = rproc_find_loaded_rsc_table(rproc, fw);
	अगर (loaded_table) अणु
		स_नकल(loaded_table, rproc->cached_table, rproc->table_sz);
		rproc->table_ptr = loaded_table;
	पूर्ण

	ret = rproc_prepare_subdevices(rproc);
	अगर (ret) अणु
		dev_err(dev, "failed to prepare subdevices for %s: %d\n",
			rproc->name, ret);
		जाओ reset_table_ptr;
	पूर्ण

	/* घातer up the remote processor */
	ret = rproc->ops->start(rproc);
	अगर (ret) अणु
		dev_err(dev, "can't start rproc %s: %d\n", rproc->name, ret);
		जाओ unprepare_subdevices;
	पूर्ण

	/* Start any subdevices क्रम the remote processor */
	ret = rproc_start_subdevices(rproc);
	अगर (ret) अणु
		dev_err(dev, "failed to probe subdevices for %s: %d\n",
			rproc->name, ret);
		जाओ stop_rproc;
	पूर्ण

	rproc->state = RPROC_RUNNING;

	dev_info(dev, "remote processor %s is now up\n", rproc->name);

	वापस 0;

stop_rproc:
	rproc->ops->stop(rproc);
unprepare_subdevices:
	rproc_unprepare_subdevices(rproc);
reset_table_ptr:
	rproc->table_ptr = rproc->cached_table;

	वापस ret;
पूर्ण

अटल पूर्णांक __rproc_attach(काष्ठा rproc *rproc)
अणु
	काष्ठा device *dev = &rproc->dev;
	पूर्णांक ret;

	ret = rproc_prepare_subdevices(rproc);
	अगर (ret) अणु
		dev_err(dev, "failed to prepare subdevices for %s: %d\n",
			rproc->name, ret);
		जाओ out;
	पूर्ण

	/* Attach to the remote processor */
	ret = rproc_attach_device(rproc);
	अगर (ret) अणु
		dev_err(dev, "can't attach to rproc %s: %d\n",
			rproc->name, ret);
		जाओ unprepare_subdevices;
	पूर्ण

	/* Start any subdevices क्रम the remote processor */
	ret = rproc_start_subdevices(rproc);
	अगर (ret) अणु
		dev_err(dev, "failed to probe subdevices for %s: %d\n",
			rproc->name, ret);
		जाओ stop_rproc;
	पूर्ण

	rproc->state = RPROC_ATTACHED;

	dev_info(dev, "remote processor %s is now attached\n", rproc->name);

	वापस 0;

stop_rproc:
	rproc->ops->stop(rproc);
unprepare_subdevices:
	rproc_unprepare_subdevices(rproc);
out:
	वापस ret;
पूर्ण

/*
 * take a firmware and boot a remote processor with it.
 */
अटल पूर्णांक rproc_fw_boot(काष्ठा rproc *rproc, स्थिर काष्ठा firmware *fw)
अणु
	काष्ठा device *dev = &rproc->dev;
	स्थिर अक्षर *name = rproc->firmware;
	पूर्णांक ret;

	ret = rproc_fw_sanity_check(rproc, fw);
	अगर (ret)
		वापस ret;

	dev_info(dev, "Booting fw image %s, size %zd\n", name, fw->size);

	/*
	 * अगर enabling an IOMMU isn't relevant क्रम this rproc, this is
	 * just a nop
	 */
	ret = rproc_enable_iommu(rproc);
	अगर (ret) अणु
		dev_err(dev, "can't enable iommu: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Prepare rproc क्रम firmware loading अगर needed */
	ret = rproc_prepare_device(rproc);
	अगर (ret) अणु
		dev_err(dev, "can't prepare rproc %s: %d\n", rproc->name, ret);
		जाओ disable_iommu;
	पूर्ण

	rproc->bootaddr = rproc_get_boot_addr(rproc, fw);

	/* Load resource table, core dump segment list etc from the firmware */
	ret = rproc_parse_fw(rproc, fw);
	अगर (ret)
		जाओ unprepare_rproc;

	/* reset max_notअगरyid */
	rproc->max_notअगरyid = -1;

	/* reset handled vdev */
	rproc->nb_vdev = 0;

	/* handle fw resources which are required to boot rproc */
	ret = rproc_handle_resources(rproc, rproc_loading_handlers);
	अगर (ret) अणु
		dev_err(dev, "Failed to process resources: %d\n", ret);
		जाओ clean_up_resources;
	पूर्ण

	/* Allocate carveout resources associated to rproc */
	ret = rproc_alloc_रेजिस्टरed_carveouts(rproc);
	अगर (ret) अणु
		dev_err(dev, "Failed to allocate associated carveouts: %d\n",
			ret);
		जाओ clean_up_resources;
	पूर्ण

	ret = rproc_start(rproc, fw);
	अगर (ret)
		जाओ clean_up_resources;

	वापस 0;

clean_up_resources:
	rproc_resource_cleanup(rproc);
	kमुक्त(rproc->cached_table);
	rproc->cached_table = शून्य;
	rproc->table_ptr = शून्य;
unprepare_rproc:
	/* release HW resources अगर needed */
	rproc_unprepare_device(rproc);
disable_iommu:
	rproc_disable_iommu(rproc);
	वापस ret;
पूर्ण

अटल पूर्णांक rproc_set_rsc_table(काष्ठा rproc *rproc)
अणु
	काष्ठा resource_table *table_ptr;
	काष्ठा device *dev = &rproc->dev;
	माप_प्रकार table_sz;
	पूर्णांक ret;

	table_ptr = rproc_get_loaded_rsc_table(rproc, &table_sz);
	अगर (!table_ptr) अणु
		/* Not having a resource table is acceptable */
		वापस 0;
	पूर्ण

	अगर (IS_ERR(table_ptr)) अणु
		ret = PTR_ERR(table_ptr);
		dev_err(dev, "can't load resource table: %d\n", ret);
		वापस ret;
	पूर्ण

	/*
	 * If it is possible to detach the remote processor, keep an untouched
	 * copy of the resource table.  That way we can start fresh again when
	 * the remote processor is re-attached, that is:
	 *
	 *      DETACHED -> ATTACHED -> DETACHED -> ATTACHED
	 *
	 * Free'd in rproc_reset_rsc_table_on_detach() and
	 * rproc_reset_rsc_table_on_stop().
	 */
	अगर (rproc->ops->detach) अणु
		rproc->clean_table = kmemdup(table_ptr, table_sz, GFP_KERNEL);
		अगर (!rproc->clean_table)
			वापस -ENOMEM;
	पूर्ण अन्यथा अणु
		rproc->clean_table = शून्य;
	पूर्ण

	rproc->cached_table = शून्य;
	rproc->table_ptr = table_ptr;
	rproc->table_sz = table_sz;

	वापस 0;
पूर्ण

अटल पूर्णांक rproc_reset_rsc_table_on_detach(काष्ठा rproc *rproc)
अणु
	काष्ठा resource_table *table_ptr;

	/* A resource table was never retrieved, nothing to करो here */
	अगर (!rproc->table_ptr)
		वापस 0;

	/*
	 * If we made it to this poपूर्णांक a clean_table _must_ have been
	 * allocated in rproc_set_rsc_table().  If one isn't present
	 * something went really wrong and we must complain.
	 */
	अगर (WARN_ON(!rproc->clean_table))
		वापस -EINVAL;

	/* Remember where the बाह्यal entity installed the resource table */
	table_ptr = rproc->table_ptr;

	/*
	 * If we made it here the remote processor was started by another
	 * entity and a cache table करोesn't exist.  As such make a copy of
	 * the resource table currently used by the remote processor and
	 * use that क्रम the rest of the shutकरोwn process.  The memory
	 * allocated here is मुक्त'd in rproc_detach().
	 */
	rproc->cached_table = kmemdup(rproc->table_ptr,
				      rproc->table_sz, GFP_KERNEL);
	अगर (!rproc->cached_table)
		वापस -ENOMEM;

	/*
	 * Use a copy of the resource table क्रम the reमुख्यder of the
	 * shutकरोwn process.
	 */
	rproc->table_ptr = rproc->cached_table;

	/*
	 * Reset the memory area where the firmware loaded the resource table
	 * to its original value.  That way when we re-attach the remote
	 * processor the resource table is clean and पढ़ोy to be used again.
	 */
	स_नकल(table_ptr, rproc->clean_table, rproc->table_sz);

	/*
	 * The clean resource table is no दीर्घer needed.  Allocated in
	 * rproc_set_rsc_table().
	 */
	kमुक्त(rproc->clean_table);

	वापस 0;
पूर्ण

अटल पूर्णांक rproc_reset_rsc_table_on_stop(काष्ठा rproc *rproc)
अणु
	/* A resource table was never retrieved, nothing to करो here */
	अगर (!rproc->table_ptr)
		वापस 0;

	/*
	 * If a cache table exists the remote processor was started by
	 * the remoteproc core.  That cache table should be used क्रम
	 * the rest of the shutकरोwn process.
	 */
	अगर (rproc->cached_table)
		जाओ out;

	/*
	 * If we made it here the remote processor was started by another
	 * entity and a cache table करोesn't exist.  As such make a copy of
	 * the resource table currently used by the remote processor and
	 * use that क्रम the rest of the shutकरोwn process.  The memory
	 * allocated here is मुक्त'd in rproc_shutकरोwn().
	 */
	rproc->cached_table = kmemdup(rproc->table_ptr,
				      rproc->table_sz, GFP_KERNEL);
	अगर (!rproc->cached_table)
		वापस -ENOMEM;

	/*
	 * Since the remote processor is being चयनed off the clean table
	 * won't be needed.  Allocated in rproc_set_rsc_table().
	 */
	kमुक्त(rproc->clean_table);

out:
	/*
	 * Use a copy of the resource table क्रम the reमुख्यder of the
	 * shutकरोwn process.
	 */
	rproc->table_ptr = rproc->cached_table;
	वापस 0;
पूर्ण

/*
 * Attach to remote processor - similar to rproc_fw_boot() but without
 * the steps that deal with the firmware image.
 */
अटल पूर्णांक rproc_attach(काष्ठा rproc *rproc)
अणु
	काष्ठा device *dev = &rproc->dev;
	पूर्णांक ret;

	/*
	 * अगर enabling an IOMMU isn't relevant क्रम this rproc, this is
	 * just a nop
	 */
	ret = rproc_enable_iommu(rproc);
	अगर (ret) अणु
		dev_err(dev, "can't enable iommu: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Do anything that is needed to boot the remote processor */
	ret = rproc_prepare_device(rproc);
	अगर (ret) अणु
		dev_err(dev, "can't prepare rproc %s: %d\n", rproc->name, ret);
		जाओ disable_iommu;
	पूर्ण

	ret = rproc_set_rsc_table(rproc);
	अगर (ret) अणु
		dev_err(dev, "can't load resource table: %d\n", ret);
		जाओ unprepare_device;
	पूर्ण

	/* reset max_notअगरyid */
	rproc->max_notअगरyid = -1;

	/* reset handled vdev */
	rproc->nb_vdev = 0;

	/*
	 * Handle firmware resources required to attach to a remote processor.
	 * Because we are attaching rather than booting the remote processor,
	 * we expect the platक्रमm driver to properly set rproc->table_ptr.
	 */
	ret = rproc_handle_resources(rproc, rproc_loading_handlers);
	अगर (ret) अणु
		dev_err(dev, "Failed to process resources: %d\n", ret);
		जाओ unprepare_device;
	पूर्ण

	/* Allocate carveout resources associated to rproc */
	ret = rproc_alloc_रेजिस्टरed_carveouts(rproc);
	अगर (ret) अणु
		dev_err(dev, "Failed to allocate associated carveouts: %d\n",
			ret);
		जाओ clean_up_resources;
	पूर्ण

	ret = __rproc_attach(rproc);
	अगर (ret)
		जाओ clean_up_resources;

	वापस 0;

clean_up_resources:
	rproc_resource_cleanup(rproc);
unprepare_device:
	/* release HW resources अगर needed */
	rproc_unprepare_device(rproc);
disable_iommu:
	rproc_disable_iommu(rproc);
	वापस ret;
पूर्ण

/*
 * take a firmware and boot it up.
 *
 * Note: this function is called asynchronously upon registration of the
 * remote processor (so we must रुको until it completes beक्रमe we try
 * to unरेजिस्टर the device. one other option is just to use kref here,
 * that might be cleaner).
 */
अटल व्योम rproc_स्वतः_boot_callback(स्थिर काष्ठा firmware *fw, व्योम *context)
अणु
	काष्ठा rproc *rproc = context;

	rproc_boot(rproc);

	release_firmware(fw);
पूर्ण

अटल पूर्णांक rproc_trigger_स्वतः_boot(काष्ठा rproc *rproc)
अणु
	पूर्णांक ret;

	/*
	 * Since the remote processor is in a detached state, it has alपढ़ोy
	 * been booted by another entity.  As such there is no poपूर्णांक in रुकोing
	 * क्रम a firmware image to be loaded, we can simply initiate the process
	 * of attaching to it immediately.
	 */
	अगर (rproc->state == RPROC_DETACHED)
		वापस rproc_boot(rproc);

	/*
	 * We're initiating an asynchronous firmware loading, so we can
	 * be built-in kernel code, without hanging the boot process.
	 */
	ret = request_firmware_noरुको(THIS_MODULE, FW_ACTION_HOTPLUG,
				      rproc->firmware, &rproc->dev, GFP_KERNEL,
				      rproc, rproc_स्वतः_boot_callback);
	अगर (ret < 0)
		dev_err(&rproc->dev, "request_firmware_nowait err: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक rproc_stop(काष्ठा rproc *rproc, bool crashed)
अणु
	काष्ठा device *dev = &rproc->dev;
	पूर्णांक ret;

	/* No need to जारी अगर a stop() operation has not been provided */
	अगर (!rproc->ops->stop)
		वापस -EINVAL;

	/* Stop any subdevices क्रम the remote processor */
	rproc_stop_subdevices(rproc, crashed);

	/* the installed resource table is no दीर्घer accessible */
	ret = rproc_reset_rsc_table_on_stop(rproc);
	अगर (ret) अणु
		dev_err(dev, "can't reset resource table: %d\n", ret);
		वापस ret;
	पूर्ण


	/* घातer off the remote processor */
	ret = rproc->ops->stop(rproc);
	अगर (ret) अणु
		dev_err(dev, "can't stop rproc: %d\n", ret);
		वापस ret;
	पूर्ण

	rproc_unprepare_subdevices(rproc);

	rproc->state = RPROC_OFFLINE;

	dev_info(dev, "stopped remote processor %s\n", rproc->name);

	वापस 0;
पूर्ण

/*
 * __rproc_detach(): Does the opposite of __rproc_attach()
 */
अटल पूर्णांक __rproc_detach(काष्ठा rproc *rproc)
अणु
	काष्ठा device *dev = &rproc->dev;
	पूर्णांक ret;

	/* No need to जारी अगर a detach() operation has not been provided */
	अगर (!rproc->ops->detach)
		वापस -EINVAL;

	/* Stop any subdevices क्रम the remote processor */
	rproc_stop_subdevices(rproc, false);

	/* the installed resource table is no दीर्घer accessible */
	ret = rproc_reset_rsc_table_on_detach(rproc);
	अगर (ret) अणु
		dev_err(dev, "can't reset resource table: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Tell the remote processor the core isn't available anymore */
	ret = rproc->ops->detach(rproc);
	अगर (ret) अणु
		dev_err(dev, "can't detach from rproc: %d\n", ret);
		वापस ret;
	पूर्ण

	rproc_unprepare_subdevices(rproc);

	rproc->state = RPROC_DETACHED;

	dev_info(dev, "detached remote processor %s\n", rproc->name);

	वापस 0;
पूर्ण

/**
 * rproc_trigger_recovery() - recover a remoteproc
 * @rproc: the remote processor
 *
 * The recovery is करोne by resetting all the virtio devices, that way all the
 * rpmsg drivers will be reseted aदीर्घ with the remote processor making the
 * remoteproc functional again.
 *
 * This function can sleep, so it cannot be called from atomic context.
 */
पूर्णांक rproc_trigger_recovery(काष्ठा rproc *rproc)
अणु
	स्थिर काष्ठा firmware *firmware_p;
	काष्ठा device *dev = &rproc->dev;
	पूर्णांक ret;

	ret = mutex_lock_पूर्णांकerruptible(&rproc->lock);
	अगर (ret)
		वापस ret;

	/* State could have changed beक्रमe we got the mutex */
	अगर (rproc->state != RPROC_CRASHED)
		जाओ unlock_mutex;

	dev_err(dev, "recovering %s\n", rproc->name);

	ret = rproc_stop(rproc, true);
	अगर (ret)
		जाओ unlock_mutex;

	/* generate coredump */
	rproc->ops->coredump(rproc);

	/* load firmware */
	ret = request_firmware(&firmware_p, rproc->firmware, dev);
	अगर (ret < 0) अणु
		dev_err(dev, "request_firmware failed: %d\n", ret);
		जाओ unlock_mutex;
	पूर्ण

	/* boot the remote processor up again */
	ret = rproc_start(rproc, firmware_p);

	release_firmware(firmware_p);

unlock_mutex:
	mutex_unlock(&rproc->lock);
	वापस ret;
पूर्ण

/**
 * rproc_crash_handler_work() - handle a crash
 * @work: work treating the crash
 *
 * This function needs to handle everything related to a crash, like cpu
 * रेजिस्टरs and stack dump, inक्रमmation to help to debug the fatal error, etc.
 */
अटल व्योम rproc_crash_handler_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rproc *rproc = container_of(work, काष्ठा rproc, crash_handler);
	काष्ठा device *dev = &rproc->dev;

	dev_dbg(dev, "enter %s\n", __func__);

	mutex_lock(&rproc->lock);

	अगर (rproc->state == RPROC_CRASHED || rproc->state == RPROC_OFFLINE) अणु
		/* handle only the first crash detected */
		mutex_unlock(&rproc->lock);
		वापस;
	पूर्ण

	rproc->state = RPROC_CRASHED;
	dev_err(dev, "handling crash #%u in %s\n", ++rproc->crash_cnt,
		rproc->name);

	mutex_unlock(&rproc->lock);

	अगर (!rproc->recovery_disabled)
		rproc_trigger_recovery(rproc);

	pm_relax(rproc->dev.parent);
पूर्ण

/**
 * rproc_boot() - boot a remote processor
 * @rproc: handle of a remote processor
 *
 * Boot a remote processor (i.e. load its firmware, घातer it on, ...).
 *
 * If the remote processor is alपढ़ोy घातered on, this function immediately
 * वापसs (successfully).
 *
 * Returns 0 on success, and an appropriate error value otherwise.
 */
पूर्णांक rproc_boot(काष्ठा rproc *rproc)
अणु
	स्थिर काष्ठा firmware *firmware_p;
	काष्ठा device *dev;
	पूर्णांक ret;

	अगर (!rproc) अणु
		pr_err("invalid rproc handle\n");
		वापस -EINVAL;
	पूर्ण

	dev = &rproc->dev;

	ret = mutex_lock_पूर्णांकerruptible(&rproc->lock);
	अगर (ret) अणु
		dev_err(dev, "can't lock rproc %s: %d\n", rproc->name, ret);
		वापस ret;
	पूर्ण

	अगर (rproc->state == RPROC_DELETED) अणु
		ret = -ENODEV;
		dev_err(dev, "can't boot deleted rproc %s\n", rproc->name);
		जाओ unlock_mutex;
	पूर्ण

	/* skip the boot or attach process अगर rproc is alपढ़ोy घातered up */
	अगर (atomic_inc_वापस(&rproc->घातer) > 1) अणु
		ret = 0;
		जाओ unlock_mutex;
	पूर्ण

	अगर (rproc->state == RPROC_DETACHED) अणु
		dev_info(dev, "attaching to %s\n", rproc->name);

		ret = rproc_attach(rproc);
	पूर्ण अन्यथा अणु
		dev_info(dev, "powering up %s\n", rproc->name);

		/* load firmware */
		ret = request_firmware(&firmware_p, rproc->firmware, dev);
		अगर (ret < 0) अणु
			dev_err(dev, "request_firmware failed: %d\n", ret);
			जाओ करोwnref_rproc;
		पूर्ण

		ret = rproc_fw_boot(rproc, firmware_p);

		release_firmware(firmware_p);
	पूर्ण

करोwnref_rproc:
	अगर (ret)
		atomic_dec(&rproc->घातer);
unlock_mutex:
	mutex_unlock(&rproc->lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(rproc_boot);

/**
 * rproc_shutकरोwn() - घातer off the remote processor
 * @rproc: the remote processor
 *
 * Power off a remote processor (previously booted with rproc_boot()).
 *
 * In हाल @rproc is still being used by an additional user(s), then
 * this function will just decrement the घातer refcount and निकास,
 * without really घातering off the device.
 *
 * Every call to rproc_boot() must (eventually) be accompanied by a call
 * to rproc_shutकरोwn(). Calling rproc_shutकरोwn() redundantly is a bug.
 *
 * Notes:
 * - we're not decrementing the rproc's refcount, only the घातer refcount.
 *   which means that the @rproc handle stays valid even after rproc_shutकरोwn()
 *   वापसs, and users can still use it with a subsequent rproc_boot(), अगर
 *   needed.
 */
व्योम rproc_shutकरोwn(काष्ठा rproc *rproc)
अणु
	काष्ठा device *dev = &rproc->dev;
	पूर्णांक ret;

	ret = mutex_lock_पूर्णांकerruptible(&rproc->lock);
	अगर (ret) अणु
		dev_err(dev, "can't lock rproc %s: %d\n", rproc->name, ret);
		वापस;
	पूर्ण

	/* अगर the remote proc is still needed, bail out */
	अगर (!atomic_dec_and_test(&rproc->घातer))
		जाओ out;

	ret = rproc_stop(rproc, false);
	अगर (ret) अणु
		atomic_inc(&rproc->घातer);
		जाओ out;
	पूर्ण

	/* clean up all acquired resources */
	rproc_resource_cleanup(rproc);

	/* release HW resources अगर needed */
	rproc_unprepare_device(rproc);

	rproc_disable_iommu(rproc);

	/* Free the copy of the resource table */
	kमुक्त(rproc->cached_table);
	rproc->cached_table = शून्य;
	rproc->table_ptr = शून्य;
out:
	mutex_unlock(&rproc->lock);
पूर्ण
EXPORT_SYMBOL(rproc_shutकरोwn);

/**
 * rproc_detach() - Detach the remote processor from the
 * remoteproc core
 *
 * @rproc: the remote processor
 *
 * Detach a remote processor (previously attached to with rproc_attach()).
 *
 * In हाल @rproc is still being used by an additional user(s), then
 * this function will just decrement the घातer refcount and निकास,
 * without disconnecting the device.
 *
 * Function rproc_detach() calls __rproc_detach() in order to let a remote
 * processor know that services provided by the application processor are
 * no दीर्घer available.  From there it should be possible to हटाओ the
 * platक्रमm driver and even घातer cycle the application processor (अगर the HW
 * supports it) without needing to चयन off the remote processor.
 */
पूर्णांक rproc_detach(काष्ठा rproc *rproc)
अणु
	काष्ठा device *dev = &rproc->dev;
	पूर्णांक ret;

	ret = mutex_lock_पूर्णांकerruptible(&rproc->lock);
	अगर (ret) अणु
		dev_err(dev, "can't lock rproc %s: %d\n", rproc->name, ret);
		वापस ret;
	पूर्ण

	/* अगर the remote proc is still needed, bail out */
	अगर (!atomic_dec_and_test(&rproc->घातer)) अणु
		ret = 0;
		जाओ out;
	पूर्ण

	ret = __rproc_detach(rproc);
	अगर (ret) अणु
		atomic_inc(&rproc->घातer);
		जाओ out;
	पूर्ण

	/* clean up all acquired resources */
	rproc_resource_cleanup(rproc);

	/* release HW resources अगर needed */
	rproc_unprepare_device(rproc);

	rproc_disable_iommu(rproc);

	/* Free the copy of the resource table */
	kमुक्त(rproc->cached_table);
	rproc->cached_table = शून्य;
	rproc->table_ptr = शून्य;
out:
	mutex_unlock(&rproc->lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(rproc_detach);

/**
 * rproc_get_by_phandle() - find a remote processor by phandle
 * @phandle: phandle to the rproc
 *
 * Finds an rproc handle using the remote processor's phandle, and then
 * वापस a handle to the rproc.
 *
 * This function increments the remote processor's refcount, so always
 * use rproc_put() to decrement it back once rproc isn't needed anymore.
 *
 * Returns the rproc handle on success, and शून्य on failure.
 */
#अगर_घोषित CONFIG_OF
काष्ठा rproc *rproc_get_by_phandle(phandle phandle)
अणु
	काष्ठा rproc *rproc = शून्य, *r;
	काष्ठा device_node *np;

	np = of_find_node_by_phandle(phandle);
	अगर (!np)
		वापस शून्य;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(r, &rproc_list, node) अणु
		अगर (r->dev.parent && r->dev.parent->of_node == np) अणु
			/* prevent underlying implementation from being हटाओd */
			अगर (!try_module_get(r->dev.parent->driver->owner)) अणु
				dev_err(&r->dev, "can't get owner\n");
				अवरोध;
			पूर्ण

			rproc = r;
			get_device(&rproc->dev);
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	of_node_put(np);

	वापस rproc;
पूर्ण
#अन्यथा
काष्ठा rproc *rproc_get_by_phandle(phandle phandle)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर
EXPORT_SYMBOL(rproc_get_by_phandle);

/**
 * rproc_set_firmware() - assign a new firmware
 * @rproc: rproc handle to which the new firmware is being asचिन्हित
 * @fw_name: new firmware name to be asचिन्हित
 *
 * This function allows remoteproc drivers or clients to configure a custom
 * firmware name that is dअगरferent from the शेष name used during remoteproc
 * registration. The function करोes not trigger a remote processor boot,
 * only sets the firmware name used क्रम a subsequent boot. This function
 * should also be called only when the remote processor is offline.
 *
 * This allows either the userspace to configure a dअगरferent name through
 * sysfs or a kernel-level remoteproc or a remoteproc client driver to set
 * a specअगरic firmware when it is controlling the boot and shutकरोwn of the
 * remote processor.
 *
 * Return: 0 on success or a negative value upon failure
 */
पूर्णांक rproc_set_firmware(काष्ठा rproc *rproc, स्थिर अक्षर *fw_name)
अणु
	काष्ठा device *dev;
	पूर्णांक ret, len;
	अक्षर *p;

	अगर (!rproc || !fw_name)
		वापस -EINVAL;

	dev = rproc->dev.parent;

	ret = mutex_lock_पूर्णांकerruptible(&rproc->lock);
	अगर (ret) अणु
		dev_err(dev, "can't lock rproc %s: %d\n", rproc->name, ret);
		वापस -EINVAL;
	पूर्ण

	अगर (rproc->state != RPROC_OFFLINE) अणु
		dev_err(dev, "can't change firmware while running\n");
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	len = म_खोज(fw_name, "\n");
	अगर (!len) अणु
		dev_err(dev, "can't provide empty string for firmware name\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	p = kstrndup(fw_name, len, GFP_KERNEL);
	अगर (!p) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	kमुक्त_स्थिर(rproc->firmware);
	rproc->firmware = p;

out:
	mutex_unlock(&rproc->lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(rproc_set_firmware);

अटल पूर्णांक rproc_validate(काष्ठा rproc *rproc)
अणु
	चयन (rproc->state) अणु
	हाल RPROC_OFFLINE:
		/*
		 * An offline processor without a start()
		 * function makes no sense.
		 */
		अगर (!rproc->ops->start)
			वापस -EINVAL;
		अवरोध;
	हाल RPROC_DETACHED:
		/*
		 * A remote processor in a detached state without an
		 * attach() function makes not sense.
		 */
		अगर (!rproc->ops->attach)
			वापस -EINVAL;
		/*
		 * When attaching to a remote processor the device memory
		 * is alपढ़ोy available and as such there is no need to have a
		 * cached table.
		 */
		अगर (rproc->cached_table)
			वापस -EINVAL;
		अवरोध;
	शेष:
		/*
		 * When adding a remote processor, the state of the device
		 * can be offline or detached, nothing अन्यथा.
		 */
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * rproc_add() - रेजिस्टर a remote processor
 * @rproc: the remote processor handle to रेजिस्टर
 *
 * Registers @rproc with the remoteproc framework, after it has been
 * allocated with rproc_alloc().
 *
 * This is called by the platक्रमm-specअगरic rproc implementation, whenever
 * a new remote processor device is probed.
 *
 * Returns 0 on success and an appropriate error code otherwise.
 *
 * Note: this function initiates an asynchronous firmware loading
 * context, which will look क्रम virtio devices supported by the rproc's
 * firmware.
 *
 * If found, those virtio devices will be created and added, so as a result
 * of रेजिस्टरing this remote processor, additional virtio drivers might be
 * probed.
 */
पूर्णांक rproc_add(काष्ठा rproc *rproc)
अणु
	काष्ठा device *dev = &rproc->dev;
	पूर्णांक ret;

	ret = device_add(dev);
	अगर (ret < 0)
		वापस ret;

	ret = rproc_validate(rproc);
	अगर (ret < 0)
		वापस ret;

	dev_info(dev, "%s is available\n", rproc->name);

	/* create debugfs entries */
	rproc_create_debug_dir(rproc);

	/* add अक्षर device क्रम this remoteproc */
	ret = rproc_अक्षर_device_add(rproc);
	अगर (ret < 0)
		वापस ret;

	/* अगर rproc is marked always-on, request it to boot */
	अगर (rproc->स्वतः_boot) अणु
		ret = rproc_trigger_स्वतः_boot(rproc);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	/* expose to rproc_get_by_phandle users */
	mutex_lock(&rproc_list_mutex);
	list_add_rcu(&rproc->node, &rproc_list);
	mutex_unlock(&rproc_list_mutex);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(rproc_add);

अटल व्योम devm_rproc_हटाओ(व्योम *rproc)
अणु
	rproc_del(rproc);
पूर्ण

/**
 * devm_rproc_add() - resource managed rproc_add()
 * @dev: the underlying device
 * @rproc: the remote processor handle to रेजिस्टर
 *
 * This function perक्रमms like rproc_add() but the रेजिस्टरed rproc device will
 * स्वतःmatically be हटाओd on driver detach.
 *
 * Returns: 0 on success, negative त्रुटि_सं on failure
 */
पूर्णांक devm_rproc_add(काष्ठा device *dev, काष्ठा rproc *rproc)
अणु
	पूर्णांक err;

	err = rproc_add(rproc);
	अगर (err)
		वापस err;

	वापस devm_add_action_or_reset(dev, devm_rproc_हटाओ, rproc);
पूर्ण
EXPORT_SYMBOL(devm_rproc_add);

/**
 * rproc_type_release() - release a remote processor instance
 * @dev: the rproc's device
 *
 * This function should _never_ be called directly.
 *
 * It will be called by the driver core when no one holds a valid poपूर्णांकer
 * to @dev anymore.
 */
अटल व्योम rproc_type_release(काष्ठा device *dev)
अणु
	काष्ठा rproc *rproc = container_of(dev, काष्ठा rproc, dev);

	dev_info(&rproc->dev, "releasing %s\n", rproc->name);

	idr_destroy(&rproc->notअगरyids);

	अगर (rproc->index >= 0)
		ida_simple_हटाओ(&rproc_dev_index, rproc->index);

	kमुक्त_स्थिर(rproc->firmware);
	kमुक्त_स्थिर(rproc->name);
	kमुक्त(rproc->ops);
	kमुक्त(rproc);
पूर्ण

अटल स्थिर काष्ठा device_type rproc_type = अणु
	.name		= "remoteproc",
	.release	= rproc_type_release,
पूर्ण;

अटल पूर्णांक rproc_alloc_firmware(काष्ठा rproc *rproc,
				स्थिर अक्षर *name, स्थिर अक्षर *firmware)
अणु
	स्थिर अक्षर *p;

	/*
	 * Allocate a firmware name अगर the caller gave us one to work
	 * with.  Otherwise स्थिरruct a new one using a शेष pattern.
	 */
	अगर (firmware)
		p = kstrdup_स्थिर(firmware, GFP_KERNEL);
	अन्यथा
		p = kaप्र_लिखो(GFP_KERNEL, "rproc-%s-fw", name);

	अगर (!p)
		वापस -ENOMEM;

	rproc->firmware = p;

	वापस 0;
पूर्ण

अटल पूर्णांक rproc_alloc_ops(काष्ठा rproc *rproc, स्थिर काष्ठा rproc_ops *ops)
अणु
	rproc->ops = kmemdup(ops, माप(*ops), GFP_KERNEL);
	अगर (!rproc->ops)
		वापस -ENOMEM;

	/* Default to rproc_coredump अगर no coredump function is specअगरied */
	अगर (!rproc->ops->coredump)
		rproc->ops->coredump = rproc_coredump;

	अगर (rproc->ops->load)
		वापस 0;

	/* Default to ELF loader अगर no load function is specअगरied */
	rproc->ops->load = rproc_elf_load_segments;
	rproc->ops->parse_fw = rproc_elf_load_rsc_table;
	rproc->ops->find_loaded_rsc_table = rproc_elf_find_loaded_rsc_table;
	rproc->ops->sanity_check = rproc_elf_sanity_check;
	rproc->ops->get_boot_addr = rproc_elf_get_boot_addr;

	वापस 0;
पूर्ण

/**
 * rproc_alloc() - allocate a remote processor handle
 * @dev: the underlying device
 * @name: name of this remote processor
 * @ops: platक्रमm-specअगरic handlers (मुख्यly start/stop)
 * @firmware: name of firmware file to load, can be शून्य
 * @len: length of निजी data needed by the rproc driver (in bytes)
 *
 * Allocates a new remote processor handle, but करोes not रेजिस्टर
 * it yet. अगर @firmware is शून्य, a शेष name is used.
 *
 * This function should be used by rproc implementations during initialization
 * of the remote processor.
 *
 * After creating an rproc handle using this function, and when पढ़ोy,
 * implementations should then call rproc_add() to complete
 * the registration of the remote processor.
 *
 * On success the new rproc is वापसed, and on failure, शून्य.
 *
 * Note: _never_ directly deallocate @rproc, even अगर it was not रेजिस्टरed
 * yet. Instead, when you need to unroll rproc_alloc(), use rproc_मुक्त().
 */
काष्ठा rproc *rproc_alloc(काष्ठा device *dev, स्थिर अक्षर *name,
			  स्थिर काष्ठा rproc_ops *ops,
			  स्थिर अक्षर *firmware, पूर्णांक len)
अणु
	काष्ठा rproc *rproc;

	अगर (!dev || !name || !ops)
		वापस शून्य;

	rproc = kzalloc(माप(काष्ठा rproc) + len, GFP_KERNEL);
	अगर (!rproc)
		वापस शून्य;

	rproc->priv = &rproc[1];
	rproc->स्वतः_boot = true;
	rproc->elf_class = ELFCLASSNONE;
	rproc->elf_machine = EM_NONE;

	device_initialize(&rproc->dev);
	rproc->dev.parent = dev;
	rproc->dev.type = &rproc_type;
	rproc->dev.class = &rproc_class;
	rproc->dev.driver_data = rproc;
	idr_init(&rproc->notअगरyids);

	rproc->name = kstrdup_स्थिर(name, GFP_KERNEL);
	अगर (!rproc->name)
		जाओ put_device;

	अगर (rproc_alloc_firmware(rproc, name, firmware))
		जाओ put_device;

	अगर (rproc_alloc_ops(rproc, ops))
		जाओ put_device;

	/* Assign a unique device index and name */
	rproc->index = ida_simple_get(&rproc_dev_index, 0, 0, GFP_KERNEL);
	अगर (rproc->index < 0) अणु
		dev_err(dev, "ida_simple_get failed: %d\n", rproc->index);
		जाओ put_device;
	पूर्ण

	dev_set_name(&rproc->dev, "remoteproc%d", rproc->index);

	atomic_set(&rproc->घातer, 0);

	mutex_init(&rproc->lock);

	INIT_LIST_HEAD(&rproc->carveouts);
	INIT_LIST_HEAD(&rproc->mappings);
	INIT_LIST_HEAD(&rproc->traces);
	INIT_LIST_HEAD(&rproc->rvdevs);
	INIT_LIST_HEAD(&rproc->subdevs);
	INIT_LIST_HEAD(&rproc->dump_segments);

	INIT_WORK(&rproc->crash_handler, rproc_crash_handler_work);

	rproc->state = RPROC_OFFLINE;

	वापस rproc;

put_device:
	put_device(&rproc->dev);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(rproc_alloc);

/**
 * rproc_मुक्त() - unroll rproc_alloc()
 * @rproc: the remote processor handle
 *
 * This function decrements the rproc dev refcount.
 *
 * If no one holds any reference to rproc anymore, then its refcount would
 * now drop to zero, and it would be मुक्तd.
 */
व्योम rproc_मुक्त(काष्ठा rproc *rproc)
अणु
	put_device(&rproc->dev);
पूर्ण
EXPORT_SYMBOL(rproc_मुक्त);

/**
 * rproc_put() - release rproc reference
 * @rproc: the remote processor handle
 *
 * This function decrements the rproc dev refcount.
 *
 * If no one holds any reference to rproc anymore, then its refcount would
 * now drop to zero, and it would be मुक्तd.
 */
व्योम rproc_put(काष्ठा rproc *rproc)
अणु
	module_put(rproc->dev.parent->driver->owner);
	put_device(&rproc->dev);
पूर्ण
EXPORT_SYMBOL(rproc_put);

/**
 * rproc_del() - unरेजिस्टर a remote processor
 * @rproc: rproc handle to unरेजिस्टर
 *
 * This function should be called when the platक्रमm specअगरic rproc
 * implementation decides to हटाओ the rproc device. it should
 * _only_ be called अगर a previous invocation of rproc_add()
 * has completed successfully.
 *
 * After rproc_del() वापसs, @rproc isn't मुक्तd yet, because
 * of the outstanding reference created by rproc_alloc. To decrement that
 * one last refcount, one still needs to call rproc_मुक्त().
 *
 * Returns 0 on success and -EINVAL अगर @rproc isn't valid.
 */
पूर्णांक rproc_del(काष्ठा rproc *rproc)
अणु
	अगर (!rproc)
		वापस -EINVAL;

	/* TODO: make sure this works with rproc->घातer > 1 */
	rproc_shutकरोwn(rproc);

	mutex_lock(&rproc->lock);
	rproc->state = RPROC_DELETED;
	mutex_unlock(&rproc->lock);

	rproc_delete_debug_dir(rproc);
	rproc_अक्षर_device_हटाओ(rproc);

	/* the rproc is करोwnref'ed as soon as it's हटाओd from the klist */
	mutex_lock(&rproc_list_mutex);
	list_del_rcu(&rproc->node);
	mutex_unlock(&rproc_list_mutex);

	/* Ensure that no पढ़ोers of rproc_list are still active */
	synchronize_rcu();

	device_del(&rproc->dev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(rproc_del);

अटल व्योम devm_rproc_मुक्त(काष्ठा device *dev, व्योम *res)
अणु
	rproc_मुक्त(*(काष्ठा rproc **)res);
पूर्ण

/**
 * devm_rproc_alloc() - resource managed rproc_alloc()
 * @dev: the underlying device
 * @name: name of this remote processor
 * @ops: platक्रमm-specअगरic handlers (मुख्यly start/stop)
 * @firmware: name of firmware file to load, can be शून्य
 * @len: length of निजी data needed by the rproc driver (in bytes)
 *
 * This function perक्रमms like rproc_alloc() but the acquired rproc device will
 * स्वतःmatically be released on driver detach.
 *
 * Returns: new rproc instance, or शून्य on failure
 */
काष्ठा rproc *devm_rproc_alloc(काष्ठा device *dev, स्थिर अक्षर *name,
			       स्थिर काष्ठा rproc_ops *ops,
			       स्थिर अक्षर *firmware, पूर्णांक len)
अणु
	काष्ठा rproc **ptr, *rproc;

	ptr = devres_alloc(devm_rproc_मुक्त, माप(*ptr), GFP_KERNEL);
	अगर (!ptr)
		वापस शून्य;

	rproc = rproc_alloc(dev, name, ops, firmware, len);
	अगर (rproc) अणु
		*ptr = rproc;
		devres_add(dev, ptr);
	पूर्ण अन्यथा अणु
		devres_मुक्त(ptr);
	पूर्ण

	वापस rproc;
पूर्ण
EXPORT_SYMBOL(devm_rproc_alloc);

/**
 * rproc_add_subdev() - add a subdevice to a remoteproc
 * @rproc: rproc handle to add the subdevice to
 * @subdev: subdev handle to रेजिस्टर
 *
 * Caller is responsible क्रम populating optional subdevice function poपूर्णांकers.
 */
व्योम rproc_add_subdev(काष्ठा rproc *rproc, काष्ठा rproc_subdev *subdev)
अणु
	list_add_tail(&subdev->node, &rproc->subdevs);
पूर्ण
EXPORT_SYMBOL(rproc_add_subdev);

/**
 * rproc_हटाओ_subdev() - हटाओ a subdevice from a remoteproc
 * @rproc: rproc handle to हटाओ the subdevice from
 * @subdev: subdev handle, previously रेजिस्टरed with rproc_add_subdev()
 */
व्योम rproc_हटाओ_subdev(काष्ठा rproc *rproc, काष्ठा rproc_subdev *subdev)
अणु
	list_del(&subdev->node);
पूर्ण
EXPORT_SYMBOL(rproc_हटाओ_subdev);

/**
 * rproc_get_by_child() - acquire rproc handle of @dev's ancestor
 * @dev:	child device to find ancestor of
 *
 * Returns the ancestor rproc instance, or शून्य अगर not found.
 */
काष्ठा rproc *rproc_get_by_child(काष्ठा device *dev)
अणु
	क्रम (dev = dev->parent; dev; dev = dev->parent) अणु
		अगर (dev->type == &rproc_type)
			वापस dev->driver_data;
	पूर्ण

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(rproc_get_by_child);

/**
 * rproc_report_crash() - rproc crash reporter function
 * @rproc: remote processor
 * @type: crash type
 *
 * This function must be called every समय a crash is detected by the low-level
 * drivers implementing a specअगरic remoteproc. This should not be called from a
 * non-remoteproc driver.
 *
 * This function can be called from atomic/पूर्णांकerrupt context.
 */
व्योम rproc_report_crash(काष्ठा rproc *rproc, क्रमागत rproc_crash_type type)
अणु
	अगर (!rproc) अणु
		pr_err("NULL rproc pointer\n");
		वापस;
	पूर्ण

	/* Prevent suspend जबतक the remoteproc is being recovered */
	pm_stay_awake(rproc->dev.parent);

	dev_err(&rproc->dev, "crash detected in %s: type %s\n",
		rproc->name, rproc_crash_to_string(type));

	/* create a new task to handle the error */
	schedule_work(&rproc->crash_handler);
पूर्ण
EXPORT_SYMBOL(rproc_report_crash);

अटल पूर्णांक rproc_panic_handler(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ event,
			       व्योम *ptr)
अणु
	अचिन्हित पूर्णांक दीर्घest = 0;
	काष्ठा rproc *rproc;
	अचिन्हित पूर्णांक d;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(rproc, &rproc_list, node) अणु
		अगर (!rproc->ops->panic)
			जारी;

		अगर (rproc->state != RPROC_RUNNING &&
		    rproc->state != RPROC_ATTACHED)
			जारी;

		d = rproc->ops->panic(rproc);
		दीर्घest = max(दीर्घest, d);
	पूर्ण
	rcu_पढ़ो_unlock();

	/*
	 * Delay क्रम the दीर्घest requested duration beक्रमe वापसing. This can
	 * be used by the remoteproc drivers to give the remote processor समय
	 * to perक्रमm any requested operations (such as flush caches), when
	 * it's not possible to संकेत the Linux side due to the panic.
	 */
	mdelay(दीर्घest);

	वापस NOTIFY_DONE;
पूर्ण

अटल व्योम __init rproc_init_panic(व्योम)
अणु
	rproc_panic_nb.notअगरier_call = rproc_panic_handler;
	atomic_notअगरier_chain_रेजिस्टर(&panic_notअगरier_list, &rproc_panic_nb);
पूर्ण

अटल व्योम __निकास rproc_निकास_panic(व्योम)
अणु
	atomic_notअगरier_chain_unरेजिस्टर(&panic_notअगरier_list, &rproc_panic_nb);
पूर्ण

अटल पूर्णांक __init remoteproc_init(व्योम)
अणु
	rproc_init_sysfs();
	rproc_init_debugfs();
	rproc_init_cdev();
	rproc_init_panic();

	वापस 0;
पूर्ण
subsys_initcall(remoteproc_init);

अटल व्योम __निकास remoteproc_निकास(व्योम)
अणु
	ida_destroy(&rproc_dev_index);

	rproc_निकास_panic();
	rproc_निकास_debugfs();
	rproc_निकास_sysfs();
पूर्ण
module_निकास(remoteproc_निकास);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Generic Remote Processor Framework");
