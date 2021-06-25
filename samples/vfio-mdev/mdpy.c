<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Mediated भव PCI display host device driver
 *
 * See mdpy-defs.h क्रम device specs
 *
 *   (c) Gerd Hoffmann <kraxel@redhat.com>
 *
 * based on mtty driver which is:
 *   Copyright (c) 2016, NVIDIA CORPORATION. All rights reserved.
 *	 Author: Neo Jia <cjia@nvidia.com>
 *		 Kirti Wankhede <kwankhede@nvidia.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/cdev.h>
#समावेश <linux/vfपन.स>
#समावेश <linux/iommu.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/mdev.h>
#समावेश <linux/pci.h>
#समावेश <drm/drm_fourcc.h>
#समावेश "mdpy-defs.h"

#घोषणा MDPY_NAME		"mdpy"
#घोषणा MDPY_CLASS_NAME		"mdpy"

#घोषणा MDPY_CONFIG_SPACE_SIZE	0xff
#घोषणा MDPY_MEMORY_BAR_OFFSET	PAGE_SIZE
#घोषणा MDPY_DISPLAY_REGION	16

#घोषणा STORE_LE16(addr, val)	(*(u16 *)addr = val)
#घोषणा STORE_LE32(addr, val)	(*(u32 *)addr = val)


MODULE_LICENSE("GPL v2");

अटल पूर्णांक max_devices = 4;
module_param_named(count, max_devices, पूर्णांक, 0444);
MODULE_PARM_DESC(count, "number of " MDPY_NAME " devices");


#घोषणा MDPY_TYPE_1 "vga"
#घोषणा MDPY_TYPE_2 "xga"
#घोषणा MDPY_TYPE_3 "hd"

अटल स्थिर काष्ठा mdpy_type अणु
	स्थिर अक्षर *name;
	u32 क्रमmat;
	u32 bytepp;
	u32 width;
	u32 height;
पूर्ण mdpy_types[] = अणु
	अणु
		.name	= MDPY_CLASS_NAME "-" MDPY_TYPE_1,
		.क्रमmat = DRM_FORMAT_XRGB8888,
		.bytepp = 4,
		.width	= 640,
		.height = 480,
	पूर्ण, अणु
		.name	= MDPY_CLASS_NAME "-" MDPY_TYPE_2,
		.क्रमmat = DRM_FORMAT_XRGB8888,
		.bytepp = 4,
		.width	= 1024,
		.height = 768,
	पूर्ण, अणु
		.name	= MDPY_CLASS_NAME "-" MDPY_TYPE_3,
		.क्रमmat = DRM_FORMAT_XRGB8888,
		.bytepp = 4,
		.width	= 1920,
		.height = 1080,
	पूर्ण,
पूर्ण;

अटल dev_t		mdpy_devt;
अटल काष्ठा class	*mdpy_class;
अटल काष्ठा cdev	mdpy_cdev;
अटल काष्ठा device	mdpy_dev;
अटल u32		mdpy_count;

/* State of each mdev device */
काष्ठा mdev_state अणु
	u8 *vconfig;
	u32 bar_mask;
	काष्ठा mutex ops_lock;
	काष्ठा mdev_device *mdev;
	काष्ठा vfio_device_info dev_info;

	स्थिर काष्ठा mdpy_type *type;
	u32 memsize;
	व्योम *memblk;
पूर्ण;

अटल व्योम mdpy_create_config_space(काष्ठा mdev_state *mdev_state)
अणु
	STORE_LE16((u16 *) &mdev_state->vconfig[PCI_VENDOR_ID],
		   MDPY_PCI_VENDOR_ID);
	STORE_LE16((u16 *) &mdev_state->vconfig[PCI_DEVICE_ID],
		   MDPY_PCI_DEVICE_ID);
	STORE_LE16((u16 *) &mdev_state->vconfig[PCI_SUBSYSTEM_VENDOR_ID],
		   MDPY_PCI_SUBVENDOR_ID);
	STORE_LE16((u16 *) &mdev_state->vconfig[PCI_SUBSYSTEM_ID],
		   MDPY_PCI_SUBDEVICE_ID);

	STORE_LE16((u16 *) &mdev_state->vconfig[PCI_COMMAND],
		   PCI_COMMAND_IO | PCI_COMMAND_MEMORY);
	STORE_LE16((u16 *) &mdev_state->vconfig[PCI_STATUS],
		   PCI_STATUS_CAP_LIST);
	STORE_LE16((u16 *) &mdev_state->vconfig[PCI_CLASS_DEVICE],
		   PCI_CLASS_DISPLAY_OTHER);
	mdev_state->vconfig[PCI_CLASS_REVISION] =  0x01;

	STORE_LE32((u32 *) &mdev_state->vconfig[PCI_BASE_ADDRESS_0],
		   PCI_BASE_ADDRESS_SPACE_MEMORY |
		   PCI_BASE_ADDRESS_MEM_TYPE_32	 |
		   PCI_BASE_ADDRESS_MEM_PREFETCH);
	mdev_state->bar_mask = ~(mdev_state->memsize) + 1;

	/* venकरोr specअगरic capability क्रम the config रेजिस्टरs */
	mdev_state->vconfig[PCI_CAPABILITY_LIST]       = MDPY_VENDORCAP_OFFSET;
	mdev_state->vconfig[MDPY_VENDORCAP_OFFSET + 0] = 0x09; /* venकरोr cap */
	mdev_state->vconfig[MDPY_VENDORCAP_OFFSET + 1] = 0x00; /* next ptr */
	mdev_state->vconfig[MDPY_VENDORCAP_OFFSET + 2] = MDPY_VENDORCAP_SIZE;
	STORE_LE32((u32 *) &mdev_state->vconfig[MDPY_FORMAT_OFFSET],
		   mdev_state->type->क्रमmat);
	STORE_LE32((u32 *) &mdev_state->vconfig[MDPY_WIDTH_OFFSET],
		   mdev_state->type->width);
	STORE_LE32((u32 *) &mdev_state->vconfig[MDPY_HEIGHT_OFFSET],
		   mdev_state->type->height);
पूर्ण

अटल व्योम handle_pci_cfg_ग_लिखो(काष्ठा mdev_state *mdev_state, u16 offset,
				 अक्षर *buf, u32 count)
अणु
	काष्ठा device *dev = mdev_dev(mdev_state->mdev);
	u32 cfg_addr;

	चयन (offset) अणु
	हाल PCI_BASE_ADDRESS_0:
		cfg_addr = *(u32 *)buf;

		अगर (cfg_addr == 0xffffffff) अणु
			cfg_addr = (cfg_addr & mdev_state->bar_mask);
		पूर्ण अन्यथा अणु
			cfg_addr &= PCI_BASE_ADDRESS_MEM_MASK;
			अगर (cfg_addr)
				dev_info(dev, "BAR0 @ 0x%x\n", cfg_addr);
		पूर्ण

		cfg_addr |= (mdev_state->vconfig[offset] &
			     ~PCI_BASE_ADDRESS_MEM_MASK);
		STORE_LE32(&mdev_state->vconfig[offset], cfg_addr);
		अवरोध;
	पूर्ण
पूर्ण

अटल sमाप_प्रकार mdev_access(काष्ठा mdev_device *mdev, अक्षर *buf, माप_प्रकार count,
			   loff_t pos, bool is_ग_लिखो)
अणु
	काष्ठा mdev_state *mdev_state = mdev_get_drvdata(mdev);
	काष्ठा device *dev = mdev_dev(mdev);
	पूर्णांक ret = 0;

	mutex_lock(&mdev_state->ops_lock);

	अगर (pos < MDPY_CONFIG_SPACE_SIZE) अणु
		अगर (is_ग_लिखो)
			handle_pci_cfg_ग_लिखो(mdev_state, pos, buf, count);
		अन्यथा
			स_नकल(buf, (mdev_state->vconfig + pos), count);

	पूर्ण अन्यथा अगर ((pos >= MDPY_MEMORY_BAR_OFFSET) &&
		   (pos + count <=
		    MDPY_MEMORY_BAR_OFFSET + mdev_state->memsize)) अणु
		pos -= MDPY_MEMORY_BAR_OFFSET;
		अगर (is_ग_लिखो)
			स_नकल(mdev_state->memblk, buf, count);
		अन्यथा
			स_नकल(buf, mdev_state->memblk, count);

	पूर्ण अन्यथा अणु
		dev_info(dev, "%s: %s @0x%llx (unhandled)\n",
			 __func__, is_ग_लिखो ? "WR" : "RD", pos);
		ret = -1;
		जाओ accessfailed;
	पूर्ण

	ret = count;


accessfailed:
	mutex_unlock(&mdev_state->ops_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक mdpy_reset(काष्ठा mdev_device *mdev)
अणु
	काष्ठा mdev_state *mdev_state = mdev_get_drvdata(mdev);
	u32 stride, i;

	/* initialize with gray gradient */
	stride = mdev_state->type->width * mdev_state->type->bytepp;
	क्रम (i = 0; i < mdev_state->type->height; i++)
		स_रखो(mdev_state->memblk + i * stride,
		       i * 255 / mdev_state->type->height,
		       stride);
	वापस 0;
पूर्ण

अटल पूर्णांक mdpy_create(काष्ठा mdev_device *mdev)
अणु
	स्थिर काष्ठा mdpy_type *type =
		&mdpy_types[mdev_get_type_group_id(mdev)];
	काष्ठा device *dev = mdev_dev(mdev);
	काष्ठा mdev_state *mdev_state;
	u32 fbsize;

	अगर (mdpy_count >= max_devices)
		वापस -ENOMEM;

	mdev_state = kzalloc(माप(काष्ठा mdev_state), GFP_KERNEL);
	अगर (mdev_state == शून्य)
		वापस -ENOMEM;

	mdev_state->vconfig = kzalloc(MDPY_CONFIG_SPACE_SIZE, GFP_KERNEL);
	अगर (mdev_state->vconfig == शून्य) अणु
		kमुक्त(mdev_state);
		वापस -ENOMEM;
	पूर्ण

	fbsize = roundup_घात_of_two(type->width * type->height * type->bytepp);

	mdev_state->memblk = vदो_स्मृति_user(fbsize);
	अगर (!mdev_state->memblk) अणु
		kमुक्त(mdev_state->vconfig);
		kमुक्त(mdev_state);
		वापस -ENOMEM;
	पूर्ण
	dev_info(dev, "%s: %s (%dx%d)\n", __func__, type->name, type->width,
		 type->height);

	mutex_init(&mdev_state->ops_lock);
	mdev_state->mdev = mdev;
	mdev_set_drvdata(mdev, mdev_state);

	mdev_state->type    = type;
	mdev_state->memsize = fbsize;
	mdpy_create_config_space(mdev_state);
	mdpy_reset(mdev);

	mdpy_count++;
	वापस 0;
पूर्ण

अटल पूर्णांक mdpy_हटाओ(काष्ठा mdev_device *mdev)
अणु
	काष्ठा mdev_state *mdev_state = mdev_get_drvdata(mdev);
	काष्ठा device *dev = mdev_dev(mdev);

	dev_info(dev, "%s\n", __func__);

	mdev_set_drvdata(mdev, शून्य);
	vमुक्त(mdev_state->memblk);
	kमुक्त(mdev_state->vconfig);
	kमुक्त(mdev_state);

	mdpy_count--;
	वापस 0;
पूर्ण

अटल sमाप_प्रकार mdpy_पढ़ो(काष्ठा mdev_device *mdev, अक्षर __user *buf,
			 माप_प्रकार count, loff_t *ppos)
अणु
	अचिन्हित पूर्णांक करोne = 0;
	पूर्णांक ret;

	जबतक (count) अणु
		माप_प्रकार filled;

		अगर (count >= 4 && !(*ppos % 4)) अणु
			u32 val;

			ret =  mdev_access(mdev, (अक्षर *)&val, माप(val),
					   *ppos, false);
			अगर (ret <= 0)
				जाओ पढ़ो_err;

			अगर (copy_to_user(buf, &val, माप(val)))
				जाओ पढ़ो_err;

			filled = 4;
		पूर्ण अन्यथा अगर (count >= 2 && !(*ppos % 2)) अणु
			u16 val;

			ret = mdev_access(mdev, (अक्षर *)&val, माप(val),
					  *ppos, false);
			अगर (ret <= 0)
				जाओ पढ़ो_err;

			अगर (copy_to_user(buf, &val, माप(val)))
				जाओ पढ़ो_err;

			filled = 2;
		पूर्ण अन्यथा अणु
			u8 val;

			ret = mdev_access(mdev, (अक्षर *)&val, माप(val),
					  *ppos, false);
			अगर (ret <= 0)
				जाओ पढ़ो_err;

			अगर (copy_to_user(buf, &val, माप(val)))
				जाओ पढ़ो_err;

			filled = 1;
		पूर्ण

		count -= filled;
		करोne += filled;
		*ppos += filled;
		buf += filled;
	पूर्ण

	वापस करोne;

पढ़ो_err:
	वापस -EFAULT;
पूर्ण

अटल sमाप_प्रकार mdpy_ग_लिखो(काष्ठा mdev_device *mdev, स्थिर अक्षर __user *buf,
			  माप_प्रकार count, loff_t *ppos)
अणु
	अचिन्हित पूर्णांक करोne = 0;
	पूर्णांक ret;

	जबतक (count) अणु
		माप_प्रकार filled;

		अगर (count >= 4 && !(*ppos % 4)) अणु
			u32 val;

			अगर (copy_from_user(&val, buf, माप(val)))
				जाओ ग_लिखो_err;

			ret = mdev_access(mdev, (अक्षर *)&val, माप(val),
					  *ppos, true);
			अगर (ret <= 0)
				जाओ ग_लिखो_err;

			filled = 4;
		पूर्ण अन्यथा अगर (count >= 2 && !(*ppos % 2)) अणु
			u16 val;

			अगर (copy_from_user(&val, buf, माप(val)))
				जाओ ग_लिखो_err;

			ret = mdev_access(mdev, (अक्षर *)&val, माप(val),
					  *ppos, true);
			अगर (ret <= 0)
				जाओ ग_लिखो_err;

			filled = 2;
		पूर्ण अन्यथा अणु
			u8 val;

			अगर (copy_from_user(&val, buf, माप(val)))
				जाओ ग_लिखो_err;

			ret = mdev_access(mdev, (अक्षर *)&val, माप(val),
					  *ppos, true);
			अगर (ret <= 0)
				जाओ ग_लिखो_err;

			filled = 1;
		पूर्ण
		count -= filled;
		करोne += filled;
		*ppos += filled;
		buf += filled;
	पूर्ण

	वापस करोne;
ग_लिखो_err:
	वापस -EFAULT;
पूर्ण

अटल पूर्णांक mdpy_mmap(काष्ठा mdev_device *mdev, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा mdev_state *mdev_state = mdev_get_drvdata(mdev);

	अगर (vma->vm_pgoff != MDPY_MEMORY_BAR_OFFSET >> PAGE_SHIFT)
		वापस -EINVAL;
	अगर (vma->vm_end < vma->vm_start)
		वापस -EINVAL;
	अगर (vma->vm_end - vma->vm_start > mdev_state->memsize)
		वापस -EINVAL;
	अगर ((vma->vm_flags & VM_SHARED) == 0)
		वापस -EINVAL;

	वापस remap_vदो_स्मृति_range(vma, mdev_state->memblk, 0);
पूर्ण

अटल पूर्णांक mdpy_get_region_info(काष्ठा mdev_device *mdev,
				काष्ठा vfio_region_info *region_info,
				u16 *cap_type_id, व्योम **cap_type)
अणु
	काष्ठा mdev_state *mdev_state;

	mdev_state = mdev_get_drvdata(mdev);
	अगर (!mdev_state)
		वापस -EINVAL;

	अगर (region_info->index >= VFIO_PCI_NUM_REGIONS &&
	    region_info->index != MDPY_DISPLAY_REGION)
		वापस -EINVAL;

	चयन (region_info->index) अणु
	हाल VFIO_PCI_CONFIG_REGION_INDEX:
		region_info->offset = 0;
		region_info->size   = MDPY_CONFIG_SPACE_SIZE;
		region_info->flags  = (VFIO_REGION_INFO_FLAG_READ |
				       VFIO_REGION_INFO_FLAG_WRITE);
		अवरोध;
	हाल VFIO_PCI_BAR0_REGION_INDEX:
	हाल MDPY_DISPLAY_REGION:
		region_info->offset = MDPY_MEMORY_BAR_OFFSET;
		region_info->size   = mdev_state->memsize;
		region_info->flags  = (VFIO_REGION_INFO_FLAG_READ  |
				       VFIO_REGION_INFO_FLAG_WRITE |
				       VFIO_REGION_INFO_FLAG_MMAP);
		अवरोध;
	शेष:
		region_info->size   = 0;
		region_info->offset = 0;
		region_info->flags  = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mdpy_get_irq_info(काष्ठा mdev_device *mdev,
			     काष्ठा vfio_irq_info *irq_info)
अणु
	irq_info->count = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक mdpy_get_device_info(काष्ठा mdev_device *mdev,
				काष्ठा vfio_device_info *dev_info)
अणु
	dev_info->flags = VFIO_DEVICE_FLAGS_PCI;
	dev_info->num_regions = VFIO_PCI_NUM_REGIONS;
	dev_info->num_irqs = VFIO_PCI_NUM_IRQS;
	वापस 0;
पूर्ण

अटल पूर्णांक mdpy_query_gfx_plane(काष्ठा mdev_device *mdev,
				काष्ठा vfio_device_gfx_plane_info *plane)
अणु
	काष्ठा mdev_state *mdev_state = mdev_get_drvdata(mdev);

	अगर (plane->flags & VFIO_GFX_PLANE_TYPE_PROBE) अणु
		अगर (plane->flags == (VFIO_GFX_PLANE_TYPE_PROBE |
				     VFIO_GFX_PLANE_TYPE_REGION))
			वापस 0;
		वापस -EINVAL;
	पूर्ण

	अगर (plane->flags != VFIO_GFX_PLANE_TYPE_REGION)
		वापस -EINVAL;

	plane->drm_क्रमmat     = mdev_state->type->क्रमmat;
	plane->width	      = mdev_state->type->width;
	plane->height	      = mdev_state->type->height;
	plane->stride	      = (mdev_state->type->width *
				 mdev_state->type->bytepp);
	plane->size	      = mdev_state->memsize;
	plane->region_index   = MDPY_DISPLAY_REGION;

	/* unused */
	plane->drm_क्रमmat_mod = 0;
	plane->x_pos	      = 0;
	plane->y_pos	      = 0;
	plane->x_hot	      = 0;
	plane->y_hot	      = 0;

	वापस 0;
पूर्ण

अटल दीर्घ mdpy_ioctl(काष्ठा mdev_device *mdev, अचिन्हित पूर्णांक cmd,
		       अचिन्हित दीर्घ arg)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ minsz;
	काष्ठा mdev_state *mdev_state;

	mdev_state = mdev_get_drvdata(mdev);

	चयन (cmd) अणु
	हाल VFIO_DEVICE_GET_INFO:
	अणु
		काष्ठा vfio_device_info info;

		minsz = दुरत्वend(काष्ठा vfio_device_info, num_irqs);

		अगर (copy_from_user(&info, (व्योम __user *)arg, minsz))
			वापस -EFAULT;

		अगर (info.argsz < minsz)
			वापस -EINVAL;

		ret = mdpy_get_device_info(mdev, &info);
		अगर (ret)
			वापस ret;

		स_नकल(&mdev_state->dev_info, &info, माप(info));

		अगर (copy_to_user((व्योम __user *)arg, &info, minsz))
			वापस -EFAULT;

		वापस 0;
	पूर्ण
	हाल VFIO_DEVICE_GET_REGION_INFO:
	अणु
		काष्ठा vfio_region_info info;
		u16 cap_type_id = 0;
		व्योम *cap_type = शून्य;

		minsz = दुरत्वend(काष्ठा vfio_region_info, offset);

		अगर (copy_from_user(&info, (व्योम __user *)arg, minsz))
			वापस -EFAULT;

		अगर (info.argsz < minsz)
			वापस -EINVAL;

		ret = mdpy_get_region_info(mdev, &info, &cap_type_id,
					   &cap_type);
		अगर (ret)
			वापस ret;

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

		अगर ((info.argsz < minsz) ||
		    (info.index >= mdev_state->dev_info.num_irqs))
			वापस -EINVAL;

		ret = mdpy_get_irq_info(mdev, &info);
		अगर (ret)
			वापस ret;

		अगर (copy_to_user((व्योम __user *)arg, &info, minsz))
			वापस -EFAULT;

		वापस 0;
	पूर्ण

	हाल VFIO_DEVICE_QUERY_GFX_PLANE:
	अणु
		काष्ठा vfio_device_gfx_plane_info plane;

		minsz = दुरत्वend(काष्ठा vfio_device_gfx_plane_info,
				    region_index);

		अगर (copy_from_user(&plane, (व्योम __user *)arg, minsz))
			वापस -EFAULT;

		अगर (plane.argsz < minsz)
			वापस -EINVAL;

		ret = mdpy_query_gfx_plane(mdev, &plane);
		अगर (ret)
			वापस ret;

		अगर (copy_to_user((व्योम __user *)arg, &plane, minsz))
			वापस -EFAULT;

		वापस 0;
	पूर्ण

	हाल VFIO_DEVICE_SET_IRQS:
		वापस -EINVAL;

	हाल VFIO_DEVICE_RESET:
		वापस mdpy_reset(mdev);
	पूर्ण
	वापस -ENOTTY;
पूर्ण

अटल पूर्णांक mdpy_खोलो(काष्ठा mdev_device *mdev)
अणु
	अगर (!try_module_get(THIS_MODULE))
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल व्योम mdpy_बंद(काष्ठा mdev_device *mdev)
अणु
	module_put(THIS_MODULE);
पूर्ण

अटल sमाप_प्रकार
resolution_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	काष्ठा mdev_device *mdev = mdev_from_dev(dev);
	काष्ठा mdev_state *mdev_state = mdev_get_drvdata(mdev);

	वापस प्र_लिखो(buf, "%dx%d\n",
		       mdev_state->type->width,
		       mdev_state->type->height);
पूर्ण
अटल DEVICE_ATTR_RO(resolution);

अटल काष्ठा attribute *mdev_dev_attrs[] = अणु
	&dev_attr_resolution.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group mdev_dev_group = अणु
	.name  = "vendor",
	.attrs = mdev_dev_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *mdev_dev_groups[] = अणु
	&mdev_dev_group,
	शून्य,
पूर्ण;

अटल sमाप_प्रकार name_show(काष्ठा mdev_type *mtype,
			 काष्ठा mdev_type_attribute *attr, अक्षर *buf)
अणु
	स्थिर काष्ठा mdpy_type *type =
		&mdpy_types[mtype_get_type_group_id(mtype)];

	वापस प्र_लिखो(buf, "%s\n", type->name);
पूर्ण
अटल MDEV_TYPE_ATTR_RO(name);

अटल sमाप_प्रकार description_show(काष्ठा mdev_type *mtype,
				काष्ठा mdev_type_attribute *attr, अक्षर *buf)
अणु
	स्थिर काष्ठा mdpy_type *type =
		&mdpy_types[mtype_get_type_group_id(mtype)];

	वापस प्र_लिखो(buf, "virtual display, %dx%d framebuffer\n",
		       type->width, type->height);
पूर्ण
अटल MDEV_TYPE_ATTR_RO(description);

अटल sमाप_प्रकार available_instances_show(काष्ठा mdev_type *mtype,
					काष्ठा mdev_type_attribute *attr,
					अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", max_devices - mdpy_count);
पूर्ण
अटल MDEV_TYPE_ATTR_RO(available_instances);

अटल sमाप_प्रकार device_api_show(काष्ठा mdev_type *mtype,
			       काष्ठा mdev_type_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%s\n", VFIO_DEVICE_API_PCI_STRING);
पूर्ण
अटल MDEV_TYPE_ATTR_RO(device_api);

अटल काष्ठा attribute *mdev_types_attrs[] = अणु
	&mdev_type_attr_name.attr,
	&mdev_type_attr_description.attr,
	&mdev_type_attr_device_api.attr,
	&mdev_type_attr_available_instances.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group mdev_type_group1 = अणु
	.name  = MDPY_TYPE_1,
	.attrs = mdev_types_attrs,
पूर्ण;

अटल काष्ठा attribute_group mdev_type_group2 = अणु
	.name  = MDPY_TYPE_2,
	.attrs = mdev_types_attrs,
पूर्ण;

अटल काष्ठा attribute_group mdev_type_group3 = अणु
	.name  = MDPY_TYPE_3,
	.attrs = mdev_types_attrs,
पूर्ण;

अटल काष्ठा attribute_group *mdev_type_groups[] = अणु
	&mdev_type_group1,
	&mdev_type_group2,
	&mdev_type_group3,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा mdev_parent_ops mdev_fops = अणु
	.owner			= THIS_MODULE,
	.mdev_attr_groups	= mdev_dev_groups,
	.supported_type_groups	= mdev_type_groups,
	.create			= mdpy_create,
	.हटाओ			= mdpy_हटाओ,
	.खोलो			= mdpy_खोलो,
	.release		= mdpy_बंद,
	.पढ़ो			= mdpy_पढ़ो,
	.ग_लिखो			= mdpy_ग_लिखो,
	.ioctl			= mdpy_ioctl,
	.mmap			= mdpy_mmap,
पूर्ण;

अटल स्थिर काष्ठा file_operations vd_fops = अणु
	.owner		= THIS_MODULE,
पूर्ण;

अटल व्योम mdpy_device_release(काष्ठा device *dev)
अणु
	/* nothing */
पूर्ण

अटल पूर्णांक __init mdpy_dev_init(व्योम)
अणु
	पूर्णांक ret = 0;

	ret = alloc_chrdev_region(&mdpy_devt, 0, MINORMASK + 1, MDPY_NAME);
	अगर (ret < 0) अणु
		pr_err("Error: failed to register mdpy_dev, err: %d\n", ret);
		वापस ret;
	पूर्ण
	cdev_init(&mdpy_cdev, &vd_fops);
	cdev_add(&mdpy_cdev, mdpy_devt, MINORMASK + 1);
	pr_info("%s: major %d\n", __func__, MAJOR(mdpy_devt));

	mdpy_class = class_create(THIS_MODULE, MDPY_CLASS_NAME);
	अगर (IS_ERR(mdpy_class)) अणु
		pr_err("Error: failed to register mdpy_dev class\n");
		ret = PTR_ERR(mdpy_class);
		जाओ failed1;
	पूर्ण
	mdpy_dev.class = mdpy_class;
	mdpy_dev.release = mdpy_device_release;
	dev_set_name(&mdpy_dev, "%s", MDPY_NAME);

	ret = device_रेजिस्टर(&mdpy_dev);
	अगर (ret)
		जाओ failed2;

	ret = mdev_रेजिस्टर_device(&mdpy_dev, &mdev_fops);
	अगर (ret)
		जाओ failed3;

	वापस 0;

failed3:
	device_unरेजिस्टर(&mdpy_dev);
failed2:
	class_destroy(mdpy_class);
failed1:
	cdev_del(&mdpy_cdev);
	unरेजिस्टर_chrdev_region(mdpy_devt, MINORMASK + 1);
	वापस ret;
पूर्ण

अटल व्योम __निकास mdpy_dev_निकास(व्योम)
अणु
	mdpy_dev.bus = शून्य;
	mdev_unरेजिस्टर_device(&mdpy_dev);

	device_unरेजिस्टर(&mdpy_dev);
	cdev_del(&mdpy_cdev);
	unरेजिस्टर_chrdev_region(mdpy_devt, MINORMASK + 1);
	class_destroy(mdpy_class);
	mdpy_class = शून्य;
पूर्ण

module_init(mdpy_dev_init)
module_निकास(mdpy_dev_निकास)
