<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2013 - Virtual Open Systems
 * Author: Antonios Motakis <a.motakis@भवखोलोप्रणालीs.com>
 */

#घोषणा dev_fmt(fmt)	"VFIO: " fmt

#समावेश <linux/device.h>
#समावेश <linux/acpi.h>
#समावेश <linux/iommu.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/vfपन.स>

#समावेश "vfio_platform_private.h"

#घोषणा DRIVER_VERSION  "0.10"
#घोषणा DRIVER_AUTHOR   "Antonios Motakis <a.motakis@virtualopensystems.com>"
#घोषणा DRIVER_DESC     "VFIO platform base module"

#घोषणा VFIO_PLATFORM_IS_ACPI(vdev) ((vdev)->acpihid != शून्य)

अटल LIST_HEAD(reset_list);
अटल DEFINE_MUTEX(driver_lock);

अटल vfio_platक्रमm_reset_fn_t vfio_platक्रमm_lookup_reset(स्थिर अक्षर *compat,
					काष्ठा module **module)
अणु
	काष्ठा vfio_platक्रमm_reset_node *iter;
	vfio_platक्रमm_reset_fn_t reset_fn = शून्य;

	mutex_lock(&driver_lock);
	list_क्रम_each_entry(iter, &reset_list, link) अणु
		अगर (!म_भेद(iter->compat, compat) &&
			try_module_get(iter->owner)) अणु
			*module = iter->owner;
			reset_fn = iter->of_reset;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&driver_lock);
	वापस reset_fn;
पूर्ण

अटल पूर्णांक vfio_platक्रमm_acpi_probe(काष्ठा vfio_platक्रमm_device *vdev,
				    काष्ठा device *dev)
अणु
	काष्ठा acpi_device *adev;

	अगर (acpi_disabled)
		वापस -ENOENT;

	adev = ACPI_COMPANION(dev);
	अगर (!adev) अणु
		dev_err(dev, "ACPI companion device not found for %s\n",
			vdev->name);
		वापस -ENODEV;
	पूर्ण

#अगर_घोषित CONFIG_ACPI
	vdev->acpihid = acpi_device_hid(adev);
#पूर्ण_अगर
	वापस WARN_ON(!vdev->acpihid) ? -EINVAL : 0;
पूर्ण

अटल पूर्णांक vfio_platक्रमm_acpi_call_reset(काष्ठा vfio_platक्रमm_device *vdev,
				  स्थिर अक्षर **extra_dbg)
अणु
#अगर_घोषित CONFIG_ACPI
	काष्ठा acpi_buffer buffer = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	काष्ठा device *dev = vdev->device;
	acpi_handle handle = ACPI_HANDLE(dev);
	acpi_status acpi_ret;

	acpi_ret = acpi_evaluate_object(handle, "_RST", शून्य, &buffer);
	अगर (ACPI_FAILURE(acpi_ret)) अणु
		अगर (extra_dbg)
			*extra_dbg = acpi_क्रमmat_exception(acpi_ret);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
#अन्यथा
	वापस -ENOENT;
#पूर्ण_अगर
पूर्ण

अटल bool vfio_platक्रमm_acpi_has_reset(काष्ठा vfio_platक्रमm_device *vdev)
अणु
#अगर_घोषित CONFIG_ACPI
	काष्ठा device *dev = vdev->device;
	acpi_handle handle = ACPI_HANDLE(dev);

	वापस acpi_has_method(handle, "_RST");
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण

अटल bool vfio_platक्रमm_has_reset(काष्ठा vfio_platक्रमm_device *vdev)
अणु
	अगर (VFIO_PLATFORM_IS_ACPI(vdev))
		वापस vfio_platक्रमm_acpi_has_reset(vdev);

	वापस vdev->of_reset ? true : false;
पूर्ण

अटल पूर्णांक vfio_platक्रमm_get_reset(काष्ठा vfio_platक्रमm_device *vdev)
अणु
	अगर (VFIO_PLATFORM_IS_ACPI(vdev))
		वापस vfio_platक्रमm_acpi_has_reset(vdev) ? 0 : -ENOENT;

	vdev->of_reset = vfio_platक्रमm_lookup_reset(vdev->compat,
						    &vdev->reset_module);
	अगर (!vdev->of_reset) अणु
		request_module("vfio-reset:%s", vdev->compat);
		vdev->of_reset = vfio_platक्रमm_lookup_reset(vdev->compat,
							&vdev->reset_module);
	पूर्ण

	वापस vdev->of_reset ? 0 : -ENOENT;
पूर्ण

अटल व्योम vfio_platक्रमm_put_reset(काष्ठा vfio_platक्रमm_device *vdev)
अणु
	अगर (VFIO_PLATFORM_IS_ACPI(vdev))
		वापस;

	अगर (vdev->of_reset)
		module_put(vdev->reset_module);
पूर्ण

अटल पूर्णांक vfio_platक्रमm_regions_init(काष्ठा vfio_platक्रमm_device *vdev)
अणु
	पूर्णांक cnt = 0, i;

	जबतक (vdev->get_resource(vdev, cnt))
		cnt++;

	vdev->regions = kसुस्मृति(cnt, माप(काष्ठा vfio_platक्रमm_region),
				GFP_KERNEL);
	अगर (!vdev->regions)
		वापस -ENOMEM;

	क्रम (i = 0; i < cnt;  i++) अणु
		काष्ठा resource *res =
			vdev->get_resource(vdev, i);

		अगर (!res)
			जाओ err;

		vdev->regions[i].addr = res->start;
		vdev->regions[i].size = resource_size(res);
		vdev->regions[i].flags = 0;

		चयन (resource_type(res)) अणु
		हाल IORESOURCE_MEM:
			vdev->regions[i].type = VFIO_PLATFORM_REGION_TYPE_MMIO;
			vdev->regions[i].flags |= VFIO_REGION_INFO_FLAG_READ;
			अगर (!(res->flags & IORESOURCE_READONLY))
				vdev->regions[i].flags |=
					VFIO_REGION_INFO_FLAG_WRITE;

			/*
			 * Only regions addressed with PAGE granularity may be
			 * MMAPed securely.
			 */
			अगर (!(vdev->regions[i].addr & ~PAGE_MASK) &&
					!(vdev->regions[i].size & ~PAGE_MASK))
				vdev->regions[i].flags |=
					VFIO_REGION_INFO_FLAG_MMAP;

			अवरोध;
		हाल IORESOURCE_IO:
			vdev->regions[i].type = VFIO_PLATFORM_REGION_TYPE_PIO;
			अवरोध;
		शेष:
			जाओ err;
		पूर्ण
	पूर्ण

	vdev->num_regions = cnt;

	वापस 0;
err:
	kमुक्त(vdev->regions);
	वापस -EINVAL;
पूर्ण

अटल व्योम vfio_platक्रमm_regions_cleanup(काष्ठा vfio_platक्रमm_device *vdev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < vdev->num_regions; i++)
		iounmap(vdev->regions[i].ioaddr);

	vdev->num_regions = 0;
	kमुक्त(vdev->regions);
पूर्ण

अटल पूर्णांक vfio_platक्रमm_call_reset(काष्ठा vfio_platक्रमm_device *vdev,
				    स्थिर अक्षर **extra_dbg)
अणु
	अगर (VFIO_PLATFORM_IS_ACPI(vdev)) अणु
		dev_info(vdev->device, "reset\n");
		वापस vfio_platक्रमm_acpi_call_reset(vdev, extra_dbg);
	पूर्ण अन्यथा अगर (vdev->of_reset) अणु
		dev_info(vdev->device, "reset\n");
		वापस vdev->of_reset(vdev);
	पूर्ण

	dev_warn(vdev->device, "no reset function found!\n");
	वापस -EINVAL;
पूर्ण

अटल व्योम vfio_platक्रमm_release(काष्ठा vfio_device *core_vdev)
अणु
	काष्ठा vfio_platक्रमm_device *vdev =
		container_of(core_vdev, काष्ठा vfio_platक्रमm_device, vdev);

	mutex_lock(&driver_lock);

	अगर (!(--vdev->refcnt)) अणु
		स्थिर अक्षर *extra_dbg = शून्य;
		पूर्णांक ret;

		ret = vfio_platक्रमm_call_reset(vdev, &extra_dbg);
		अगर (ret && vdev->reset_required) अणु
			dev_warn(vdev->device, "reset driver is required and reset call failed in release (%d) %s\n",
				 ret, extra_dbg ? extra_dbg : "");
			WARN_ON(1);
		पूर्ण
		pm_runसमय_put(vdev->device);
		vfio_platक्रमm_regions_cleanup(vdev);
		vfio_platक्रमm_irq_cleanup(vdev);
	पूर्ण

	mutex_unlock(&driver_lock);

	module_put(vdev->parent_module);
पूर्ण

अटल पूर्णांक vfio_platक्रमm_खोलो(काष्ठा vfio_device *core_vdev)
अणु
	काष्ठा vfio_platक्रमm_device *vdev =
		container_of(core_vdev, काष्ठा vfio_platक्रमm_device, vdev);
	पूर्णांक ret;

	अगर (!try_module_get(vdev->parent_module))
		वापस -ENODEV;

	mutex_lock(&driver_lock);

	अगर (!vdev->refcnt) अणु
		स्थिर अक्षर *extra_dbg = शून्य;

		ret = vfio_platक्रमm_regions_init(vdev);
		अगर (ret)
			जाओ err_reg;

		ret = vfio_platक्रमm_irq_init(vdev);
		अगर (ret)
			जाओ err_irq;

		ret = pm_runसमय_get_sync(vdev->device);
		अगर (ret < 0)
			जाओ err_rst;

		ret = vfio_platक्रमm_call_reset(vdev, &extra_dbg);
		अगर (ret && vdev->reset_required) अणु
			dev_warn(vdev->device, "reset driver is required and reset call failed in open (%d) %s\n",
				 ret, extra_dbg ? extra_dbg : "");
			जाओ err_rst;
		पूर्ण
	पूर्ण

	vdev->refcnt++;

	mutex_unlock(&driver_lock);
	वापस 0;

err_rst:
	pm_runसमय_put(vdev->device);
	vfio_platक्रमm_irq_cleanup(vdev);
err_irq:
	vfio_platक्रमm_regions_cleanup(vdev);
err_reg:
	mutex_unlock(&driver_lock);
	module_put(vdev->parent_module);
	वापस ret;
पूर्ण

अटल दीर्घ vfio_platक्रमm_ioctl(काष्ठा vfio_device *core_vdev,
				अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा vfio_platक्रमm_device *vdev =
		container_of(core_vdev, काष्ठा vfio_platक्रमm_device, vdev);

	अचिन्हित दीर्घ minsz;

	अगर (cmd == VFIO_DEVICE_GET_INFO) अणु
		काष्ठा vfio_device_info info;

		minsz = दुरत्वend(काष्ठा vfio_device_info, num_irqs);

		अगर (copy_from_user(&info, (व्योम __user *)arg, minsz))
			वापस -EFAULT;

		अगर (info.argsz < minsz)
			वापस -EINVAL;

		अगर (vfio_platक्रमm_has_reset(vdev))
			vdev->flags |= VFIO_DEVICE_FLAGS_RESET;
		info.flags = vdev->flags;
		info.num_regions = vdev->num_regions;
		info.num_irqs = vdev->num_irqs;

		वापस copy_to_user((व्योम __user *)arg, &info, minsz) ?
			-EFAULT : 0;

	पूर्ण अन्यथा अगर (cmd == VFIO_DEVICE_GET_REGION_INFO) अणु
		काष्ठा vfio_region_info info;

		minsz = दुरत्वend(काष्ठा vfio_region_info, offset);

		अगर (copy_from_user(&info, (व्योम __user *)arg, minsz))
			वापस -EFAULT;

		अगर (info.argsz < minsz)
			वापस -EINVAL;

		अगर (info.index >= vdev->num_regions)
			वापस -EINVAL;

		/* map offset to the physical address  */
		info.offset = VFIO_PLATFORM_INDEX_TO_OFFSET(info.index);
		info.size = vdev->regions[info.index].size;
		info.flags = vdev->regions[info.index].flags;

		वापस copy_to_user((व्योम __user *)arg, &info, minsz) ?
			-EFAULT : 0;

	पूर्ण अन्यथा अगर (cmd == VFIO_DEVICE_GET_IRQ_INFO) अणु
		काष्ठा vfio_irq_info info;

		minsz = दुरत्वend(काष्ठा vfio_irq_info, count);

		अगर (copy_from_user(&info, (व्योम __user *)arg, minsz))
			वापस -EFAULT;

		अगर (info.argsz < minsz)
			वापस -EINVAL;

		अगर (info.index >= vdev->num_irqs)
			वापस -EINVAL;

		info.flags = vdev->irqs[info.index].flags;
		info.count = vdev->irqs[info.index].count;

		वापस copy_to_user((व्योम __user *)arg, &info, minsz) ?
			-EFAULT : 0;

	पूर्ण अन्यथा अगर (cmd == VFIO_DEVICE_SET_IRQS) अणु
		काष्ठा vfio_irq_set hdr;
		u8 *data = शून्य;
		पूर्णांक ret = 0;
		माप_प्रकार data_size = 0;

		minsz = दुरत्वend(काष्ठा vfio_irq_set, count);

		अगर (copy_from_user(&hdr, (व्योम __user *)arg, minsz))
			वापस -EFAULT;

		ret = vfio_set_irqs_validate_and_prepare(&hdr, vdev->num_irqs,
						 vdev->num_irqs, &data_size);
		अगर (ret)
			वापस ret;

		अगर (data_size) अणु
			data = memdup_user((व्योम __user *)(arg + minsz),
					    data_size);
			अगर (IS_ERR(data))
				वापस PTR_ERR(data);
		पूर्ण

		mutex_lock(&vdev->igate);

		ret = vfio_platक्रमm_set_irqs_ioctl(vdev, hdr.flags, hdr.index,
						   hdr.start, hdr.count, data);
		mutex_unlock(&vdev->igate);
		kमुक्त(data);

		वापस ret;

	पूर्ण अन्यथा अगर (cmd == VFIO_DEVICE_RESET) अणु
		वापस vfio_platक्रमm_call_reset(vdev, शून्य);
	पूर्ण

	वापस -ENOTTY;
पूर्ण

अटल sमाप_प्रकार vfio_platक्रमm_पढ़ो_mmio(काष्ठा vfio_platक्रमm_region *reg,
				       अक्षर __user *buf, माप_प्रकार count,
				       loff_t off)
अणु
	अचिन्हित पूर्णांक करोne = 0;

	अगर (!reg->ioaddr) अणु
		reg->ioaddr =
			ioremap(reg->addr, reg->size);

		अगर (!reg->ioaddr)
			वापस -ENOMEM;
	पूर्ण

	जबतक (count) अणु
		माप_प्रकार filled;

		अगर (count >= 4 && !(off % 4)) अणु
			u32 val;

			val = ioपढ़ो32(reg->ioaddr + off);
			अगर (copy_to_user(buf, &val, 4))
				जाओ err;

			filled = 4;
		पूर्ण अन्यथा अगर (count >= 2 && !(off % 2)) अणु
			u16 val;

			val = ioपढ़ो16(reg->ioaddr + off);
			अगर (copy_to_user(buf, &val, 2))
				जाओ err;

			filled = 2;
		पूर्ण अन्यथा अणु
			u8 val;

			val = ioपढ़ो8(reg->ioaddr + off);
			अगर (copy_to_user(buf, &val, 1))
				जाओ err;

			filled = 1;
		पूर्ण


		count -= filled;
		करोne += filled;
		off += filled;
		buf += filled;
	पूर्ण

	वापस करोne;
err:
	वापस -EFAULT;
पूर्ण

अटल sमाप_प्रकार vfio_platक्रमm_पढ़ो(काष्ठा vfio_device *core_vdev,
				  अक्षर __user *buf, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा vfio_platक्रमm_device *vdev =
		container_of(core_vdev, काष्ठा vfio_platक्रमm_device, vdev);
	अचिन्हित पूर्णांक index = VFIO_PLATFORM_OFFSET_TO_INDEX(*ppos);
	loff_t off = *ppos & VFIO_PLATFORM_OFFSET_MASK;

	अगर (index >= vdev->num_regions)
		वापस -EINVAL;

	अगर (!(vdev->regions[index].flags & VFIO_REGION_INFO_FLAG_READ))
		वापस -EINVAL;

	अगर (vdev->regions[index].type & VFIO_PLATFORM_REGION_TYPE_MMIO)
		वापस vfio_platक्रमm_पढ़ो_mmio(&vdev->regions[index],
							buf, count, off);
	अन्यथा अगर (vdev->regions[index].type & VFIO_PLATFORM_REGION_TYPE_PIO)
		वापस -EINVAL; /* not implemented */

	वापस -EINVAL;
पूर्ण

अटल sमाप_प्रकार vfio_platक्रमm_ग_लिखो_mmio(काष्ठा vfio_platक्रमm_region *reg,
					स्थिर अक्षर __user *buf, माप_प्रकार count,
					loff_t off)
अणु
	अचिन्हित पूर्णांक करोne = 0;

	अगर (!reg->ioaddr) अणु
		reg->ioaddr =
			ioremap(reg->addr, reg->size);

		अगर (!reg->ioaddr)
			वापस -ENOMEM;
	पूर्ण

	जबतक (count) अणु
		माप_प्रकार filled;

		अगर (count >= 4 && !(off % 4)) अणु
			u32 val;

			अगर (copy_from_user(&val, buf, 4))
				जाओ err;
			ioग_लिखो32(val, reg->ioaddr + off);

			filled = 4;
		पूर्ण अन्यथा अगर (count >= 2 && !(off % 2)) अणु
			u16 val;

			अगर (copy_from_user(&val, buf, 2))
				जाओ err;
			ioग_लिखो16(val, reg->ioaddr + off);

			filled = 2;
		पूर्ण अन्यथा अणु
			u8 val;

			अगर (copy_from_user(&val, buf, 1))
				जाओ err;
			ioग_लिखो8(val, reg->ioaddr + off);

			filled = 1;
		पूर्ण

		count -= filled;
		करोne += filled;
		off += filled;
		buf += filled;
	पूर्ण

	वापस करोne;
err:
	वापस -EFAULT;
पूर्ण

अटल sमाप_प्रकार vfio_platक्रमm_ग_लिखो(काष्ठा vfio_device *core_vdev, स्थिर अक्षर __user *buf,
				   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा vfio_platक्रमm_device *vdev =
		container_of(core_vdev, काष्ठा vfio_platक्रमm_device, vdev);
	अचिन्हित पूर्णांक index = VFIO_PLATFORM_OFFSET_TO_INDEX(*ppos);
	loff_t off = *ppos & VFIO_PLATFORM_OFFSET_MASK;

	अगर (index >= vdev->num_regions)
		वापस -EINVAL;

	अगर (!(vdev->regions[index].flags & VFIO_REGION_INFO_FLAG_WRITE))
		वापस -EINVAL;

	अगर (vdev->regions[index].type & VFIO_PLATFORM_REGION_TYPE_MMIO)
		वापस vfio_platक्रमm_ग_लिखो_mmio(&vdev->regions[index],
							buf, count, off);
	अन्यथा अगर (vdev->regions[index].type & VFIO_PLATFORM_REGION_TYPE_PIO)
		वापस -EINVAL; /* not implemented */

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक vfio_platक्रमm_mmap_mmio(काष्ठा vfio_platक्रमm_region region,
				   काष्ठा vm_area_काष्ठा *vma)
अणु
	u64 req_len, pgoff, req_start;

	req_len = vma->vm_end - vma->vm_start;
	pgoff = vma->vm_pgoff &
		((1U << (VFIO_PLATFORM_OFFSET_SHIFT - PAGE_SHIFT)) - 1);
	req_start = pgoff << PAGE_SHIFT;

	अगर (region.size < PAGE_SIZE || req_start + req_len > region.size)
		वापस -EINVAL;

	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
	vma->vm_pgoff = (region.addr >> PAGE_SHIFT) + pgoff;

	वापस remap_pfn_range(vma, vma->vm_start, vma->vm_pgoff,
			       req_len, vma->vm_page_prot);
पूर्ण

अटल पूर्णांक vfio_platक्रमm_mmap(काष्ठा vfio_device *core_vdev, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा vfio_platक्रमm_device *vdev =
		container_of(core_vdev, काष्ठा vfio_platक्रमm_device, vdev);
	अचिन्हित पूर्णांक index;

	index = vma->vm_pgoff >> (VFIO_PLATFORM_OFFSET_SHIFT - PAGE_SHIFT);

	अगर (vma->vm_end < vma->vm_start)
		वापस -EINVAL;
	अगर (!(vma->vm_flags & VM_SHARED))
		वापस -EINVAL;
	अगर (index >= vdev->num_regions)
		वापस -EINVAL;
	अगर (vma->vm_start & ~PAGE_MASK)
		वापस -EINVAL;
	अगर (vma->vm_end & ~PAGE_MASK)
		वापस -EINVAL;

	अगर (!(vdev->regions[index].flags & VFIO_REGION_INFO_FLAG_MMAP))
		वापस -EINVAL;

	अगर (!(vdev->regions[index].flags & VFIO_REGION_INFO_FLAG_READ)
			&& (vma->vm_flags & VM_READ))
		वापस -EINVAL;

	अगर (!(vdev->regions[index].flags & VFIO_REGION_INFO_FLAG_WRITE)
			&& (vma->vm_flags & VM_WRITE))
		वापस -EINVAL;

	vma->vm_निजी_data = vdev;

	अगर (vdev->regions[index].type & VFIO_PLATFORM_REGION_TYPE_MMIO)
		वापस vfio_platक्रमm_mmap_mmio(vdev->regions[index], vma);

	अन्यथा अगर (vdev->regions[index].type & VFIO_PLATFORM_REGION_TYPE_PIO)
		वापस -EINVAL; /* not implemented */

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा vfio_device_ops vfio_platक्रमm_ops = अणु
	.name		= "vfio-platform",
	.खोलो		= vfio_platक्रमm_खोलो,
	.release	= vfio_platक्रमm_release,
	.ioctl		= vfio_platक्रमm_ioctl,
	.पढ़ो		= vfio_platक्रमm_पढ़ो,
	.ग_लिखो		= vfio_platक्रमm_ग_लिखो,
	.mmap		= vfio_platक्रमm_mmap,
पूर्ण;

अटल पूर्णांक vfio_platक्रमm_of_probe(काष्ठा vfio_platक्रमm_device *vdev,
			   काष्ठा device *dev)
अणु
	पूर्णांक ret;

	ret = device_property_पढ़ो_string(dev, "compatible",
					  &vdev->compat);
	अगर (ret)
		dev_err(dev, "Cannot retrieve compat for %s\n", vdev->name);

	वापस ret;
पूर्ण

/*
 * There can be two kernel build combinations. One build where
 * ACPI is not selected in Kconfig and another one with the ACPI Kconfig.
 *
 * In the first हाल, vfio_platक्रमm_acpi_probe will वापस since
 * acpi_disabled is 1. DT user will not see any kind of messages from
 * ACPI.
 *
 * In the second हाल, both DT and ACPI is compiled in but the प्रणाली is
 * booting with any of these combinations.
 *
 * If the firmware is DT type, then acpi_disabled is 1. The ACPI probe routine
 * terminates immediately without any messages.
 *
 * If the firmware is ACPI type, then acpi_disabled is 0. All other checks are
 * valid checks. We cannot claim that this प्रणाली is DT.
 */
पूर्णांक vfio_platक्रमm_probe_common(काष्ठा vfio_platक्रमm_device *vdev,
			       काष्ठा device *dev)
अणु
	काष्ठा iommu_group *group;
	पूर्णांक ret;

	vfio_init_group_dev(&vdev->vdev, dev, &vfio_platक्रमm_ops);

	ret = vfio_platक्रमm_acpi_probe(vdev, dev);
	अगर (ret)
		ret = vfio_platक्रमm_of_probe(vdev, dev);

	अगर (ret)
		वापस ret;

	vdev->device = dev;

	ret = vfio_platक्रमm_get_reset(vdev);
	अगर (ret && vdev->reset_required) अणु
		dev_err(dev, "No reset function found for device %s\n",
			vdev->name);
		वापस ret;
	पूर्ण

	group = vfio_iommu_group_get(dev);
	अगर (!group) अणु
		dev_err(dev, "No IOMMU group for device %s\n", vdev->name);
		ret = -EINVAL;
		जाओ put_reset;
	पूर्ण

	ret = vfio_रेजिस्टर_group_dev(&vdev->vdev);
	अगर (ret)
		जाओ put_iommu;

	mutex_init(&vdev->igate);

	pm_runसमय_enable(dev);
	वापस 0;

put_iommu:
	vfio_iommu_group_put(group, dev);
put_reset:
	vfio_platक्रमm_put_reset(vdev);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(vfio_platक्रमm_probe_common);

व्योम vfio_platक्रमm_हटाओ_common(काष्ठा vfio_platक्रमm_device *vdev)
अणु
	vfio_unरेजिस्टर_group_dev(&vdev->vdev);

	pm_runसमय_disable(vdev->device);
	vfio_platक्रमm_put_reset(vdev);
	vfio_iommu_group_put(vdev->vdev.dev->iommu_group, vdev->vdev.dev);
पूर्ण
EXPORT_SYMBOL_GPL(vfio_platक्रमm_हटाओ_common);

व्योम __vfio_platक्रमm_रेजिस्टर_reset(काष्ठा vfio_platक्रमm_reset_node *node)
अणु
	mutex_lock(&driver_lock);
	list_add(&node->link, &reset_list);
	mutex_unlock(&driver_lock);
पूर्ण
EXPORT_SYMBOL_GPL(__vfio_platक्रमm_रेजिस्टर_reset);

व्योम vfio_platक्रमm_unरेजिस्टर_reset(स्थिर अक्षर *compat,
				    vfio_platक्रमm_reset_fn_t fn)
अणु
	काष्ठा vfio_platक्रमm_reset_node *iter, *temp;

	mutex_lock(&driver_lock);
	list_क्रम_each_entry_safe(iter, temp, &reset_list, link) अणु
		अगर (!म_भेद(iter->compat, compat) && (iter->of_reset == fn)) अणु
			list_del(&iter->link);
			अवरोध;
		पूर्ण
	पूर्ण

	mutex_unlock(&driver_lock);

पूर्ण
EXPORT_SYMBOL_GPL(vfio_platक्रमm_unरेजिस्टर_reset);

MODULE_VERSION(DRIVER_VERSION);
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
