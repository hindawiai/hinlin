<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause)
/*
 * Copyright 2013-2016 Freescale Semiconductor Inc.
 * Copyright 2016-2017,2019-2020 NXP
 */

#समावेश <linux/device.h>
#समावेश <linux/iommu.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/vfपन.स>
#समावेश <linux/fsl/mc.h>
#समावेश <linux/delay.h>
#समावेश <linux/io-64-nonatomic-hi-lo.h>

#समावेश "vfio_fsl_mc_private.h"

अटल काष्ठा fsl_mc_driver vfio_fsl_mc_driver;

अटल DEFINE_MUTEX(reflck_lock);

अटल व्योम vfio_fsl_mc_reflck_get(काष्ठा vfio_fsl_mc_reflck *reflck)
अणु
	kref_get(&reflck->kref);
पूर्ण

अटल व्योम vfio_fsl_mc_reflck_release(काष्ठा kref *kref)
अणु
	काष्ठा vfio_fsl_mc_reflck *reflck = container_of(kref,
						      काष्ठा vfio_fsl_mc_reflck,
						      kref);

	mutex_destroy(&reflck->lock);
	kमुक्त(reflck);
	mutex_unlock(&reflck_lock);
पूर्ण

अटल व्योम vfio_fsl_mc_reflck_put(काष्ठा vfio_fsl_mc_reflck *reflck)
अणु
	kref_put_mutex(&reflck->kref, vfio_fsl_mc_reflck_release, &reflck_lock);
पूर्ण

अटल काष्ठा vfio_fsl_mc_reflck *vfio_fsl_mc_reflck_alloc(व्योम)
अणु
	काष्ठा vfio_fsl_mc_reflck *reflck;

	reflck = kzalloc(माप(*reflck), GFP_KERNEL);
	अगर (!reflck)
		वापस ERR_PTR(-ENOMEM);

	kref_init(&reflck->kref);
	mutex_init(&reflck->lock);

	वापस reflck;
पूर्ण

अटल पूर्णांक vfio_fsl_mc_reflck_attach(काष्ठा vfio_fsl_mc_device *vdev)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&reflck_lock);
	अगर (is_fsl_mc_bus_dprc(vdev->mc_dev)) अणु
		vdev->reflck = vfio_fsl_mc_reflck_alloc();
		ret = PTR_ERR_OR_ZERO(vdev->reflck);
	पूर्ण अन्यथा अणु
		काष्ठा device *mc_cont_dev = vdev->mc_dev->dev.parent;
		काष्ठा vfio_device *device;
		काष्ठा vfio_fsl_mc_device *cont_vdev;

		device = vfio_device_get_from_dev(mc_cont_dev);
		अगर (!device) अणु
			ret = -ENODEV;
			जाओ unlock;
		पूर्ण

		cont_vdev =
			container_of(device, काष्ठा vfio_fsl_mc_device, vdev);
		अगर (!cont_vdev || !cont_vdev->reflck) अणु
			vfio_device_put(device);
			ret = -ENODEV;
			जाओ unlock;
		पूर्ण
		vfio_fsl_mc_reflck_get(cont_vdev->reflck);
		vdev->reflck = cont_vdev->reflck;
		vfio_device_put(device);
	पूर्ण

unlock:
	mutex_unlock(&reflck_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक vfio_fsl_mc_regions_init(काष्ठा vfio_fsl_mc_device *vdev)
अणु
	काष्ठा fsl_mc_device *mc_dev = vdev->mc_dev;
	पूर्णांक count = mc_dev->obj_desc.region_count;
	पूर्णांक i;

	vdev->regions = kसुस्मृति(count, माप(काष्ठा vfio_fsl_mc_region),
				GFP_KERNEL);
	अगर (!vdev->regions)
		वापस -ENOMEM;

	क्रम (i = 0; i < count; i++) अणु
		काष्ठा resource *res = &mc_dev->regions[i];
		पूर्णांक no_mmap = is_fsl_mc_bus_dprc(mc_dev);

		vdev->regions[i].addr = res->start;
		vdev->regions[i].size = resource_size(res);
		vdev->regions[i].type = mc_dev->regions[i].flags & IORESOURCE_BITS;
		/*
		 * Only regions addressed with PAGE granularity may be
		 * MMAPed securely.
		 */
		अगर (!no_mmap && !(vdev->regions[i].addr & ~PAGE_MASK) &&
				!(vdev->regions[i].size & ~PAGE_MASK))
			vdev->regions[i].flags |=
					VFIO_REGION_INFO_FLAG_MMAP;
		vdev->regions[i].flags |= VFIO_REGION_INFO_FLAG_READ;
		अगर (!(mc_dev->regions[i].flags & IORESOURCE_READONLY))
			vdev->regions[i].flags |= VFIO_REGION_INFO_FLAG_WRITE;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम vfio_fsl_mc_regions_cleanup(काष्ठा vfio_fsl_mc_device *vdev)
अणु
	काष्ठा fsl_mc_device *mc_dev = vdev->mc_dev;
	पूर्णांक i;

	क्रम (i = 0; i < mc_dev->obj_desc.region_count; i++)
		iounmap(vdev->regions[i].ioaddr);
	kमुक्त(vdev->regions);
पूर्ण

अटल पूर्णांक vfio_fsl_mc_खोलो(काष्ठा vfio_device *core_vdev)
अणु
	काष्ठा vfio_fsl_mc_device *vdev =
		container_of(core_vdev, काष्ठा vfio_fsl_mc_device, vdev);
	पूर्णांक ret;

	अगर (!try_module_get(THIS_MODULE))
		वापस -ENODEV;

	mutex_lock(&vdev->reflck->lock);
	अगर (!vdev->refcnt) अणु
		ret = vfio_fsl_mc_regions_init(vdev);
		अगर (ret)
			जाओ err_reg_init;
	पूर्ण
	vdev->refcnt++;

	mutex_unlock(&vdev->reflck->lock);

	वापस 0;

err_reg_init:
	mutex_unlock(&vdev->reflck->lock);
	module_put(THIS_MODULE);
	वापस ret;
पूर्ण

अटल व्योम vfio_fsl_mc_release(काष्ठा vfio_device *core_vdev)
अणु
	काष्ठा vfio_fsl_mc_device *vdev =
		container_of(core_vdev, काष्ठा vfio_fsl_mc_device, vdev);
	पूर्णांक ret;

	mutex_lock(&vdev->reflck->lock);

	अगर (!(--vdev->refcnt)) अणु
		काष्ठा fsl_mc_device *mc_dev = vdev->mc_dev;
		काष्ठा device *cont_dev = fsl_mc_cont_dev(&mc_dev->dev);
		काष्ठा fsl_mc_device *mc_cont = to_fsl_mc_device(cont_dev);

		vfio_fsl_mc_regions_cleanup(vdev);

		/* reset the device beक्रमe cleaning up the पूर्णांकerrupts */
		ret = dprc_reset_container(mc_cont->mc_io, 0,
		      mc_cont->mc_handle,
			  mc_cont->obj_desc.id,
			  DPRC_RESET_OPTION_NON_RECURSIVE);

		अगर (ret) अणु
			dev_warn(&mc_cont->dev, "VFIO_FLS_MC: reset device has failed (%d)\n",
				 ret);
			WARN_ON(1);
		पूर्ण

		vfio_fsl_mc_irqs_cleanup(vdev);

		fsl_mc_cleanup_irq_pool(mc_cont);
	पूर्ण

	mutex_unlock(&vdev->reflck->lock);

	module_put(THIS_MODULE);
पूर्ण

अटल दीर्घ vfio_fsl_mc_ioctl(काष्ठा vfio_device *core_vdev,
			      अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	अचिन्हित दीर्घ minsz;
	काष्ठा vfio_fsl_mc_device *vdev =
		container_of(core_vdev, काष्ठा vfio_fsl_mc_device, vdev);
	काष्ठा fsl_mc_device *mc_dev = vdev->mc_dev;

	चयन (cmd) अणु
	हाल VFIO_DEVICE_GET_INFO:
	अणु
		काष्ठा vfio_device_info info;

		minsz = दुरत्वend(काष्ठा vfio_device_info, num_irqs);

		अगर (copy_from_user(&info, (व्योम __user *)arg, minsz))
			वापस -EFAULT;

		अगर (info.argsz < minsz)
			वापस -EINVAL;

		info.flags = VFIO_DEVICE_FLAGS_FSL_MC;

		अगर (is_fsl_mc_bus_dprc(mc_dev))
			info.flags |= VFIO_DEVICE_FLAGS_RESET;

		info.num_regions = mc_dev->obj_desc.region_count;
		info.num_irqs = mc_dev->obj_desc.irq_count;

		वापस copy_to_user((व्योम __user *)arg, &info, minsz) ?
			-EFAULT : 0;
	पूर्ण
	हाल VFIO_DEVICE_GET_REGION_INFO:
	अणु
		काष्ठा vfio_region_info info;

		minsz = दुरत्वend(काष्ठा vfio_region_info, offset);

		अगर (copy_from_user(&info, (व्योम __user *)arg, minsz))
			वापस -EFAULT;

		अगर (info.argsz < minsz)
			वापस -EINVAL;

		अगर (info.index >= mc_dev->obj_desc.region_count)
			वापस -EINVAL;

		/* map offset to the physical address  */
		info.offset = VFIO_FSL_MC_INDEX_TO_OFFSET(info.index);
		info.size = vdev->regions[info.index].size;
		info.flags = vdev->regions[info.index].flags;

		अगर (copy_to_user((व्योम __user *)arg, &info, minsz))
			वापस -EFAULT;
		वापस 0;
	पूर्ण
	हाल VFIO_DEVICE_GET_IRQ_INFO:
	अणु
		काष्ठा vfio_irq_info info;

		minsz = दुरत्वend(काष्ठा vfio_irq_info, count);
		अगर (copy_from_user(&info, (व्योम __user *)arg, minsz))
			वापस -EFAULT;

		अगर (info.argsz < minsz)
			वापस -EINVAL;

		अगर (info.index >= mc_dev->obj_desc.irq_count)
			वापस -EINVAL;

		info.flags = VFIO_IRQ_INFO_EVENTFD;
		info.count = 1;

		अगर (copy_to_user((व्योम __user *)arg, &info, minsz))
			वापस -EFAULT;
		वापस 0;
	पूर्ण
	हाल VFIO_DEVICE_SET_IRQS:
	अणु
		काष्ठा vfio_irq_set hdr;
		u8 *data = शून्य;
		पूर्णांक ret = 0;
		माप_प्रकार data_size = 0;

		minsz = दुरत्वend(काष्ठा vfio_irq_set, count);

		अगर (copy_from_user(&hdr, (व्योम __user *)arg, minsz))
			वापस -EFAULT;

		ret = vfio_set_irqs_validate_and_prepare(&hdr, mc_dev->obj_desc.irq_count,
					mc_dev->obj_desc.irq_count, &data_size);
		अगर (ret)
			वापस ret;

		अगर (data_size) अणु
			data = memdup_user((व्योम __user *)(arg + minsz),
				   data_size);
			अगर (IS_ERR(data))
				वापस PTR_ERR(data);
		पूर्ण

		mutex_lock(&vdev->igate);
		ret = vfio_fsl_mc_set_irqs_ioctl(vdev, hdr.flags,
						 hdr.index, hdr.start,
						 hdr.count, data);
		mutex_unlock(&vdev->igate);
		kमुक्त(data);

		वापस ret;
	पूर्ण
	हाल VFIO_DEVICE_RESET:
	अणु
		पूर्णांक ret;
		काष्ठा fsl_mc_device *mc_dev = vdev->mc_dev;

		/* reset is supported only क्रम the DPRC */
		अगर (!is_fsl_mc_bus_dprc(mc_dev))
			वापस -ENOTTY;

		ret = dprc_reset_container(mc_dev->mc_io, 0,
					   mc_dev->mc_handle,
					   mc_dev->obj_desc.id,
					   DPRC_RESET_OPTION_NON_RECURSIVE);
		वापस ret;

	पूर्ण
	शेष:
		वापस -ENOTTY;
	पूर्ण
पूर्ण

अटल sमाप_प्रकार vfio_fsl_mc_पढ़ो(काष्ठा vfio_device *core_vdev, अक्षर __user *buf,
				माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा vfio_fsl_mc_device *vdev =
		container_of(core_vdev, काष्ठा vfio_fsl_mc_device, vdev);
	अचिन्हित पूर्णांक index = VFIO_FSL_MC_OFFSET_TO_INDEX(*ppos);
	loff_t off = *ppos & VFIO_FSL_MC_OFFSET_MASK;
	काष्ठा fsl_mc_device *mc_dev = vdev->mc_dev;
	काष्ठा vfio_fsl_mc_region *region;
	u64 data[8];
	पूर्णांक i;

	अगर (index >= mc_dev->obj_desc.region_count)
		वापस -EINVAL;

	region = &vdev->regions[index];

	अगर (!(region->flags & VFIO_REGION_INFO_FLAG_READ))
		वापस -EINVAL;

	अगर (!region->ioaddr) अणु
		region->ioaddr = ioremap(region->addr, region->size);
		अगर (!region->ioaddr)
			वापस -ENOMEM;
	पूर्ण

	अगर (count != 64 || off != 0)
		वापस -EINVAL;

	क्रम (i = 7; i >= 0; i--)
		data[i] = पढ़ोq(region->ioaddr + i * माप(uपूर्णांक64_t));

	अगर (copy_to_user(buf, data, 64))
		वापस -EFAULT;

	वापस count;
पूर्ण

#घोषणा MC_CMD_COMPLETION_TIMEOUT_MS    5000
#घोषणा MC_CMD_COMPLETION_POLLING_MAX_SLEEP_USECS    500

अटल पूर्णांक vfio_fsl_mc_send_command(व्योम __iomem *ioaddr, uपूर्णांक64_t *cmd_data)
अणु
	पूर्णांक i;
	क्रमागत mc_cmd_status status;
	अचिन्हित दीर्घ समयout_usecs = MC_CMD_COMPLETION_TIMEOUT_MS * 1000;

	/* Write at command parameter पूर्णांकo portal */
	क्रम (i = 7; i >= 1; i--)
		ग_लिखोq_relaxed(cmd_data[i], ioaddr + i * माप(uपूर्णांक64_t));

	/* Write command header in the end */
	ग_लिखोq(cmd_data[0], ioaddr);

	/* Wait क्रम response beक्रमe वापसing to user-space
	 * This can be optimized in future to even prepare response
	 * beक्रमe वापसing to user-space and aव्योम पढ़ो ioctl.
	 */
	क्रम (;;) अणु
		u64 header;
		काष्ठा mc_cmd_header *resp_hdr;

		header = cpu_to_le64(पढ़ोq_relaxed(ioaddr));

		resp_hdr = (काष्ठा mc_cmd_header *)&header;
		status = (क्रमागत mc_cmd_status)resp_hdr->status;
		अगर (status != MC_CMD_STATUS_READY)
			अवरोध;

		udelay(MC_CMD_COMPLETION_POLLING_MAX_SLEEP_USECS);
		समयout_usecs -= MC_CMD_COMPLETION_POLLING_MAX_SLEEP_USECS;
		अगर (समयout_usecs == 0)
			वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार vfio_fsl_mc_ग_लिखो(काष्ठा vfio_device *core_vdev,
				 स्थिर अक्षर __user *buf, माप_प्रकार count,
				 loff_t *ppos)
अणु
	काष्ठा vfio_fsl_mc_device *vdev =
		container_of(core_vdev, काष्ठा vfio_fsl_mc_device, vdev);
	अचिन्हित पूर्णांक index = VFIO_FSL_MC_OFFSET_TO_INDEX(*ppos);
	loff_t off = *ppos & VFIO_FSL_MC_OFFSET_MASK;
	काष्ठा fsl_mc_device *mc_dev = vdev->mc_dev;
	काष्ठा vfio_fsl_mc_region *region;
	u64 data[8];
	पूर्णांक ret;

	अगर (index >= mc_dev->obj_desc.region_count)
		वापस -EINVAL;

	region = &vdev->regions[index];

	अगर (!(region->flags & VFIO_REGION_INFO_FLAG_WRITE))
		वापस -EINVAL;

	अगर (!region->ioaddr) अणु
		region->ioaddr = ioremap(region->addr, region->size);
		अगर (!region->ioaddr)
			वापस -ENOMEM;
	पूर्ण

	अगर (count != 64 || off != 0)
		वापस -EINVAL;

	अगर (copy_from_user(&data, buf, 64))
		वापस -EFAULT;

	ret = vfio_fsl_mc_send_command(region->ioaddr, data);
	अगर (ret)
		वापस ret;

	वापस count;

पूर्ण

अटल पूर्णांक vfio_fsl_mc_mmap_mmio(काष्ठा vfio_fsl_mc_region region,
				 काष्ठा vm_area_काष्ठा *vma)
अणु
	u64 size = vma->vm_end - vma->vm_start;
	u64 pgoff, base;
	u8 region_cacheable;

	pgoff = vma->vm_pgoff &
		((1U << (VFIO_FSL_MC_OFFSET_SHIFT - PAGE_SHIFT)) - 1);
	base = pgoff << PAGE_SHIFT;

	अगर (region.size < PAGE_SIZE || base + size > region.size)
		वापस -EINVAL;

	region_cacheable = (region.type & FSL_MC_REGION_CACHEABLE) &&
			   (region.type & FSL_MC_REGION_SHAREABLE);
	अगर (!region_cacheable)
		vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);

	vma->vm_pgoff = (region.addr >> PAGE_SHIFT) + pgoff;

	वापस remap_pfn_range(vma, vma->vm_start, vma->vm_pgoff,
			       size, vma->vm_page_prot);
पूर्ण

अटल पूर्णांक vfio_fsl_mc_mmap(काष्ठा vfio_device *core_vdev,
			    काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा vfio_fsl_mc_device *vdev =
		container_of(core_vdev, काष्ठा vfio_fsl_mc_device, vdev);
	काष्ठा fsl_mc_device *mc_dev = vdev->mc_dev;
	अचिन्हित पूर्णांक index;

	index = vma->vm_pgoff >> (VFIO_FSL_MC_OFFSET_SHIFT - PAGE_SHIFT);

	अगर (vma->vm_end < vma->vm_start)
		वापस -EINVAL;
	अगर (vma->vm_start & ~PAGE_MASK)
		वापस -EINVAL;
	अगर (vma->vm_end & ~PAGE_MASK)
		वापस -EINVAL;
	अगर (!(vma->vm_flags & VM_SHARED))
		वापस -EINVAL;
	अगर (index >= mc_dev->obj_desc.region_count)
		वापस -EINVAL;

	अगर (!(vdev->regions[index].flags & VFIO_REGION_INFO_FLAG_MMAP))
		वापस -EINVAL;

	अगर (!(vdev->regions[index].flags & VFIO_REGION_INFO_FLAG_READ)
			&& (vma->vm_flags & VM_READ))
		वापस -EINVAL;

	अगर (!(vdev->regions[index].flags & VFIO_REGION_INFO_FLAG_WRITE)
			&& (vma->vm_flags & VM_WRITE))
		वापस -EINVAL;

	vma->vm_निजी_data = mc_dev;

	वापस vfio_fsl_mc_mmap_mmio(vdev->regions[index], vma);
पूर्ण

अटल स्थिर काष्ठा vfio_device_ops vfio_fsl_mc_ops = अणु
	.name		= "vfio-fsl-mc",
	.खोलो		= vfio_fsl_mc_खोलो,
	.release	= vfio_fsl_mc_release,
	.ioctl		= vfio_fsl_mc_ioctl,
	.पढ़ो		= vfio_fsl_mc_पढ़ो,
	.ग_लिखो		= vfio_fsl_mc_ग_लिखो,
	.mmap		= vfio_fsl_mc_mmap,
पूर्ण;

अटल पूर्णांक vfio_fsl_mc_bus_notअगरier(काष्ठा notअगरier_block *nb,
				    अचिन्हित दीर्घ action, व्योम *data)
अणु
	काष्ठा vfio_fsl_mc_device *vdev = container_of(nb,
					काष्ठा vfio_fsl_mc_device, nb);
	काष्ठा device *dev = data;
	काष्ठा fsl_mc_device *mc_dev = to_fsl_mc_device(dev);
	काष्ठा fsl_mc_device *mc_cont = to_fsl_mc_device(mc_dev->dev.parent);

	अगर (action == BUS_NOTIFY_ADD_DEVICE &&
	    vdev->mc_dev == mc_cont) अणु
		mc_dev->driver_override = kaप्र_लिखो(GFP_KERNEL, "%s",
						    vfio_fsl_mc_ops.name);
		अगर (!mc_dev->driver_override)
			dev_warn(dev, "VFIO_FSL_MC: Setting driver override for device in dprc %s failed\n",
				 dev_name(&mc_cont->dev));
		अन्यथा
			dev_info(dev, "VFIO_FSL_MC: Setting driver override for device in dprc %s\n",
				 dev_name(&mc_cont->dev));
	पूर्ण अन्यथा अगर (action == BUS_NOTIFY_BOUND_DRIVER &&
		vdev->mc_dev == mc_cont) अणु
		काष्ठा fsl_mc_driver *mc_drv = to_fsl_mc_driver(dev->driver);

		अगर (mc_drv && mc_drv != &vfio_fsl_mc_driver)
			dev_warn(dev, "VFIO_FSL_MC: Object %s bound to driver %s while DPRC bound to vfio-fsl-mc\n",
				 dev_name(dev), mc_drv->driver.name);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vfio_fsl_mc_init_device(काष्ठा vfio_fsl_mc_device *vdev)
अणु
	काष्ठा fsl_mc_device *mc_dev = vdev->mc_dev;
	पूर्णांक ret;

	/* Non-dprc devices share mc_io from parent */
	अगर (!is_fsl_mc_bus_dprc(mc_dev)) अणु
		काष्ठा fsl_mc_device *mc_cont = to_fsl_mc_device(mc_dev->dev.parent);

		mc_dev->mc_io = mc_cont->mc_io;
		वापस 0;
	पूर्ण

	vdev->nb.notअगरier_call = vfio_fsl_mc_bus_notअगरier;
	ret = bus_रेजिस्टर_notअगरier(&fsl_mc_bus_type, &vdev->nb);
	अगर (ret)
		वापस ret;

	/* खोलो DPRC, allocate a MC portal */
	ret = dprc_setup(mc_dev);
	अगर (ret) अणु
		dev_err(&mc_dev->dev, "VFIO_FSL_MC: Failed to setup DPRC (%d)\n", ret);
		जाओ out_nc_unreg;
	पूर्ण
	वापस 0;

out_nc_unreg:
	bus_unरेजिस्टर_notअगरier(&fsl_mc_bus_type, &vdev->nb);
	वापस ret;
पूर्ण

अटल पूर्णांक vfio_fsl_mc_scan_container(काष्ठा fsl_mc_device *mc_dev)
अणु
	पूर्णांक ret;

	/* non dprc devices करो not scan क्रम other devices */
	अगर (!is_fsl_mc_bus_dprc(mc_dev))
		वापस 0;
	ret = dprc_scan_container(mc_dev, false);
	अगर (ret) अणु
		dev_err(&mc_dev->dev,
			"VFIO_FSL_MC: Container scanning failed (%d)\n", ret);
		dprc_हटाओ_devices(mc_dev, शून्य, 0);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम vfio_fsl_uninit_device(काष्ठा vfio_fsl_mc_device *vdev)
अणु
	काष्ठा fsl_mc_device *mc_dev = vdev->mc_dev;

	अगर (!is_fsl_mc_bus_dprc(mc_dev))
		वापस;

	dprc_cleanup(mc_dev);
	bus_unरेजिस्टर_notअगरier(&fsl_mc_bus_type, &vdev->nb);
पूर्ण

अटल पूर्णांक vfio_fsl_mc_probe(काष्ठा fsl_mc_device *mc_dev)
अणु
	काष्ठा iommu_group *group;
	काष्ठा vfio_fsl_mc_device *vdev;
	काष्ठा device *dev = &mc_dev->dev;
	पूर्णांक ret;

	group = vfio_iommu_group_get(dev);
	अगर (!group) अणु
		dev_err(dev, "VFIO_FSL_MC: No IOMMU group\n");
		वापस -EINVAL;
	पूर्ण

	vdev = kzalloc(माप(*vdev), GFP_KERNEL);
	अगर (!vdev) अणु
		ret = -ENOMEM;
		जाओ out_group_put;
	पूर्ण

	vfio_init_group_dev(&vdev->vdev, dev, &vfio_fsl_mc_ops);
	vdev->mc_dev = mc_dev;
	mutex_init(&vdev->igate);

	ret = vfio_fsl_mc_reflck_attach(vdev);
	अगर (ret)
		जाओ out_kमुक्त;

	ret = vfio_fsl_mc_init_device(vdev);
	अगर (ret)
		जाओ out_reflck;

	ret = vfio_रेजिस्टर_group_dev(&vdev->vdev);
	अगर (ret) अणु
		dev_err(dev, "VFIO_FSL_MC: Failed to add to vfio group\n");
		जाओ out_device;
	पूर्ण

	/*
	 * This triggers recursion पूर्णांकo vfio_fsl_mc_probe() on another device
	 * and the vfio_fsl_mc_reflck_attach() must succeed, which relies on the
	 * vfio_add_group_dev() above. It has no impact on this vdev, so it is
	 * safe to be after the vfio device is made live.
	 */
	ret = vfio_fsl_mc_scan_container(mc_dev);
	अगर (ret)
		जाओ out_group_dev;
	dev_set_drvdata(dev, vdev);
	वापस 0;

out_group_dev:
	vfio_unरेजिस्टर_group_dev(&vdev->vdev);
out_device:
	vfio_fsl_uninit_device(vdev);
out_reflck:
	vfio_fsl_mc_reflck_put(vdev->reflck);
out_kमुक्त:
	kमुक्त(vdev);
out_group_put:
	vfio_iommu_group_put(group, dev);
	वापस ret;
पूर्ण

अटल पूर्णांक vfio_fsl_mc_हटाओ(काष्ठा fsl_mc_device *mc_dev)
अणु
	काष्ठा device *dev = &mc_dev->dev;
	काष्ठा vfio_fsl_mc_device *vdev = dev_get_drvdata(dev);

	vfio_unरेजिस्टर_group_dev(&vdev->vdev);
	mutex_destroy(&vdev->igate);

	dprc_हटाओ_devices(mc_dev, शून्य, 0);
	vfio_fsl_uninit_device(vdev);
	vfio_fsl_mc_reflck_put(vdev->reflck);

	kमुक्त(vdev);
	vfio_iommu_group_put(mc_dev->dev.iommu_group, dev);

	वापस 0;
पूर्ण

अटल काष्ठा fsl_mc_driver vfio_fsl_mc_driver = अणु
	.probe		= vfio_fsl_mc_probe,
	.हटाओ		= vfio_fsl_mc_हटाओ,
	.driver	= अणु
		.name	= "vfio-fsl-mc",
		.owner	= THIS_MODULE,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init vfio_fsl_mc_driver_init(व्योम)
अणु
	वापस fsl_mc_driver_रेजिस्टर(&vfio_fsl_mc_driver);
पूर्ण

अटल व्योम __निकास vfio_fsl_mc_driver_निकास(व्योम)
अणु
	fsl_mc_driver_unरेजिस्टर(&vfio_fsl_mc_driver);
पूर्ण

module_init(vfio_fsl_mc_driver_init);
module_निकास(vfio_fsl_mc_driver_निकास);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("VFIO for FSL-MC devices - User Level meta-driver");
