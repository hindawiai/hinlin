<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  PS3 प्रणाली bus driver.
 *
 *  Copyright (C) 2006 Sony Computer Entertainment Inc.
 *  Copyright 2006 Sony Corp.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <linux/dma-map-ops.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/udbg.h>
#समावेश <यंत्र/lv1call.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/cell-regs.h>

#समावेश "platform.h"

अटल काष्ठा device ps3_प्रणाली_bus = अणु
	.init_name = "ps3_system",
पूर्ण;

/* FIXME: need device usage counters! */
अटल काष्ठा अणु
	काष्ठा mutex mutex;
	पूर्णांक sb_11; /* usb 0 */
	पूर्णांक sb_12; /* usb 0 */
	पूर्णांक gpu;
पूर्ण usage_hack;

अटल पूर्णांक ps3_is_device(काष्ठा ps3_प्रणाली_bus_device *dev, u64 bus_id,
			 u64 dev_id)
अणु
	वापस dev->bus_id == bus_id && dev->dev_id == dev_id;
पूर्ण

अटल पूर्णांक ps3_खोलो_hv_device_sb(काष्ठा ps3_प्रणाली_bus_device *dev)
अणु
	पूर्णांक result;

	BUG_ON(!dev->bus_id);
	mutex_lock(&usage_hack.mutex);

	अगर (ps3_is_device(dev, 1, 1)) अणु
		usage_hack.sb_11++;
		अगर (usage_hack.sb_11 > 1) अणु
			result = 0;
			जाओ करोne;
		पूर्ण
	पूर्ण

	अगर (ps3_is_device(dev, 1, 2)) अणु
		usage_hack.sb_12++;
		अगर (usage_hack.sb_12 > 1) अणु
			result = 0;
			जाओ करोne;
		पूर्ण
	पूर्ण

	result = lv1_खोलो_device(dev->bus_id, dev->dev_id, 0);

	अगर (result) अणु
		pr_debug("%s:%d: lv1_open_device failed: %s\n", __func__,
			__LINE__, ps3_result(result));
			result = -EPERM;
	पूर्ण

करोne:
	mutex_unlock(&usage_hack.mutex);
	वापस result;
पूर्ण

अटल पूर्णांक ps3_बंद_hv_device_sb(काष्ठा ps3_प्रणाली_bus_device *dev)
अणु
	पूर्णांक result;

	BUG_ON(!dev->bus_id);
	mutex_lock(&usage_hack.mutex);

	अगर (ps3_is_device(dev, 1, 1)) अणु
		usage_hack.sb_11--;
		अगर (usage_hack.sb_11) अणु
			result = 0;
			जाओ करोne;
		पूर्ण
	पूर्ण

	अगर (ps3_is_device(dev, 1, 2)) अणु
		usage_hack.sb_12--;
		अगर (usage_hack.sb_12) अणु
			result = 0;
			जाओ करोne;
		पूर्ण
	पूर्ण

	result = lv1_बंद_device(dev->bus_id, dev->dev_id);
	BUG_ON(result);

करोne:
	mutex_unlock(&usage_hack.mutex);
	वापस result;
पूर्ण

अटल पूर्णांक ps3_खोलो_hv_device_gpu(काष्ठा ps3_प्रणाली_bus_device *dev)
अणु
	पूर्णांक result;

	mutex_lock(&usage_hack.mutex);

	usage_hack.gpu++;
	अगर (usage_hack.gpu > 1) अणु
		result = 0;
		जाओ करोne;
	पूर्ण

	result = lv1_gpu_खोलो(0);

	अगर (result) अणु
		pr_debug("%s:%d: lv1_gpu_open failed: %s\n", __func__,
			__LINE__, ps3_result(result));
			result = -EPERM;
	पूर्ण

करोne:
	mutex_unlock(&usage_hack.mutex);
	वापस result;
पूर्ण

अटल पूर्णांक ps3_बंद_hv_device_gpu(काष्ठा ps3_प्रणाली_bus_device *dev)
अणु
	पूर्णांक result;

	mutex_lock(&usage_hack.mutex);

	usage_hack.gpu--;
	अगर (usage_hack.gpu) अणु
		result = 0;
		जाओ करोne;
	पूर्ण

	result = lv1_gpu_बंद();
	BUG_ON(result);

करोne:
	mutex_unlock(&usage_hack.mutex);
	वापस result;
पूर्ण

पूर्णांक ps3_खोलो_hv_device(काष्ठा ps3_प्रणाली_bus_device *dev)
अणु
	BUG_ON(!dev);
	pr_debug("%s:%d: match_id: %u\n", __func__, __LINE__, dev->match_id);

	चयन (dev->match_id) अणु
	हाल PS3_MATCH_ID_EHCI:
	हाल PS3_MATCH_ID_OHCI:
	हाल PS3_MATCH_ID_GELIC:
	हाल PS3_MATCH_ID_STOR_DISK:
	हाल PS3_MATCH_ID_STOR_ROM:
	हाल PS3_MATCH_ID_STOR_FLASH:
		वापस ps3_खोलो_hv_device_sb(dev);

	हाल PS3_MATCH_ID_SOUND:
	हाल PS3_MATCH_ID_GPU:
		वापस ps3_खोलो_hv_device_gpu(dev);

	हाल PS3_MATCH_ID_AV_SETTINGS:
	हाल PS3_MATCH_ID_SYSTEM_MANAGER:
		pr_debug("%s:%d: unsupported match_id: %u\n", __func__,
			__LINE__, dev->match_id);
		pr_debug("%s:%d: bus_id: %llu\n", __func__, __LINE__,
			dev->bus_id);
		BUG();
		वापस -EINVAL;

	शेष:
		अवरोध;
	पूर्ण

	pr_debug("%s:%d: unknown match_id: %u\n", __func__, __LINE__,
		dev->match_id);
	BUG();
	वापस -ENODEV;
पूर्ण
EXPORT_SYMBOL_GPL(ps3_खोलो_hv_device);

पूर्णांक ps3_बंद_hv_device(काष्ठा ps3_प्रणाली_bus_device *dev)
अणु
	BUG_ON(!dev);
	pr_debug("%s:%d: match_id: %u\n", __func__, __LINE__, dev->match_id);

	चयन (dev->match_id) अणु
	हाल PS3_MATCH_ID_EHCI:
	हाल PS3_MATCH_ID_OHCI:
	हाल PS3_MATCH_ID_GELIC:
	हाल PS3_MATCH_ID_STOR_DISK:
	हाल PS3_MATCH_ID_STOR_ROM:
	हाल PS3_MATCH_ID_STOR_FLASH:
		वापस ps3_बंद_hv_device_sb(dev);

	हाल PS3_MATCH_ID_SOUND:
	हाल PS3_MATCH_ID_GPU:
		वापस ps3_बंद_hv_device_gpu(dev);

	हाल PS3_MATCH_ID_AV_SETTINGS:
	हाल PS3_MATCH_ID_SYSTEM_MANAGER:
		pr_debug("%s:%d: unsupported match_id: %u\n", __func__,
			__LINE__, dev->match_id);
		pr_debug("%s:%d: bus_id: %llu\n", __func__, __LINE__,
			dev->bus_id);
		BUG();
		वापस -EINVAL;

	शेष:
		अवरोध;
	पूर्ण

	pr_debug("%s:%d: unknown match_id: %u\n", __func__, __LINE__,
		dev->match_id);
	BUG();
	वापस -ENODEV;
पूर्ण
EXPORT_SYMBOL_GPL(ps3_बंद_hv_device);

#घोषणा dump_mmio_region(_a) _dump_mmio_region(_a, __func__, __LINE__)
अटल व्योम _dump_mmio_region(स्थिर काष्ठा ps3_mmio_region* r,
	स्थिर अक्षर* func, पूर्णांक line)
अणु
	pr_debug("%s:%d: dev       %llu:%llu\n", func, line, r->dev->bus_id,
		r->dev->dev_id);
	pr_debug("%s:%d: bus_addr  %lxh\n", func, line, r->bus_addr);
	pr_debug("%s:%d: len       %lxh\n", func, line, r->len);
	pr_debug("%s:%d: lpar_addr %lxh\n", func, line, r->lpar_addr);
पूर्ण

अटल पूर्णांक ps3_sb_mmio_region_create(काष्ठा ps3_mmio_region *r)
अणु
	पूर्णांक result;
	u64 lpar_addr;

	result = lv1_map_device_mmio_region(r->dev->bus_id, r->dev->dev_id,
		r->bus_addr, r->len, r->page_size, &lpar_addr);
	r->lpar_addr = lpar_addr;

	अगर (result) अणु
		pr_debug("%s:%d: lv1_map_device_mmio_region failed: %s\n",
			__func__, __LINE__, ps3_result(result));
		r->lpar_addr = 0;
	पूर्ण

	dump_mmio_region(r);
	वापस result;
पूर्ण

अटल पूर्णांक ps3_ioc0_mmio_region_create(काष्ठा ps3_mmio_region *r)
अणु
	/* device specअगरic; करो nothing currently */
	वापस 0;
पूर्ण

पूर्णांक ps3_mmio_region_create(काष्ठा ps3_mmio_region *r)
अणु
	वापस r->mmio_ops->create(r);
पूर्ण
EXPORT_SYMBOL_GPL(ps3_mmio_region_create);

अटल पूर्णांक ps3_sb_मुक्त_mmio_region(काष्ठा ps3_mmio_region *r)
अणु
	पूर्णांक result;

	dump_mmio_region(r);
	result = lv1_unmap_device_mmio_region(r->dev->bus_id, r->dev->dev_id,
		r->lpar_addr);

	अगर (result)
		pr_debug("%s:%d: lv1_unmap_device_mmio_region failed: %s\n",
			__func__, __LINE__, ps3_result(result));

	r->lpar_addr = 0;
	वापस result;
पूर्ण

अटल पूर्णांक ps3_ioc0_मुक्त_mmio_region(काष्ठा ps3_mmio_region *r)
अणु
	/* device specअगरic; करो nothing currently */
	वापस 0;
पूर्ण


पूर्णांक ps3_मुक्त_mmio_region(काष्ठा ps3_mmio_region *r)
अणु
	वापस r->mmio_ops->मुक्त(r);
पूर्ण

EXPORT_SYMBOL_GPL(ps3_मुक्त_mmio_region);

अटल स्थिर काष्ठा ps3_mmio_region_ops ps3_mmio_sb_region_ops = अणु
	.create = ps3_sb_mmio_region_create,
	.मुक्त = ps3_sb_मुक्त_mmio_region
पूर्ण;

अटल स्थिर काष्ठा ps3_mmio_region_ops ps3_mmio_ioc0_region_ops = अणु
	.create = ps3_ioc0_mmio_region_create,
	.मुक्त = ps3_ioc0_मुक्त_mmio_region
पूर्ण;

पूर्णांक ps3_mmio_region_init(काष्ठा ps3_प्रणाली_bus_device *dev,
	काष्ठा ps3_mmio_region *r, अचिन्हित दीर्घ bus_addr, अचिन्हित दीर्घ len,
	क्रमागत ps3_mmio_page_size page_size)
अणु
	r->dev = dev;
	r->bus_addr = bus_addr;
	r->len = len;
	r->page_size = page_size;
	चयन (dev->dev_type) अणु
	हाल PS3_DEVICE_TYPE_SB:
		r->mmio_ops = &ps3_mmio_sb_region_ops;
		अवरोध;
	हाल PS3_DEVICE_TYPE_IOC0:
		r->mmio_ops = &ps3_mmio_ioc0_region_ops;
		अवरोध;
	शेष:
		BUG();
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ps3_mmio_region_init);

अटल पूर्णांक ps3_प्रणाली_bus_match(काष्ठा device *_dev,
	काष्ठा device_driver *_drv)
अणु
	पूर्णांक result;
	काष्ठा ps3_प्रणाली_bus_driver *drv = ps3_drv_to_प्रणाली_bus_drv(_drv);
	काष्ठा ps3_प्रणाली_bus_device *dev = ps3_dev_to_प्रणाली_bus_dev(_dev);

	अगर (!dev->match_sub_id)
		result = dev->match_id == drv->match_id;
	अन्यथा
		result = dev->match_sub_id == drv->match_sub_id &&
			dev->match_id == drv->match_id;

	अगर (result)
		pr_info("%s:%d: dev=%u.%u(%s), drv=%u.%u(%s): match\n",
			__func__, __LINE__,
			dev->match_id, dev->match_sub_id, dev_name(&dev->core),
			drv->match_id, drv->match_sub_id, drv->core.name);
	अन्यथा
		pr_debug("%s:%d: dev=%u.%u(%s), drv=%u.%u(%s): miss\n",
			__func__, __LINE__,
			dev->match_id, dev->match_sub_id, dev_name(&dev->core),
			drv->match_id, drv->match_sub_id, drv->core.name);

	वापस result;
पूर्ण

अटल पूर्णांक ps3_प्रणाली_bus_probe(काष्ठा device *_dev)
अणु
	पूर्णांक result = 0;
	काष्ठा ps3_प्रणाली_bus_device *dev = ps3_dev_to_प्रणाली_bus_dev(_dev);
	काष्ठा ps3_प्रणाली_bus_driver *drv;

	BUG_ON(!dev);
	dev_dbg(_dev, "%s:%d\n", __func__, __LINE__);

	drv = ps3_प्रणाली_bus_dev_to_प्रणाली_bus_drv(dev);
	BUG_ON(!drv);

	अगर (drv->probe)
		result = drv->probe(dev);
	अन्यथा
		pr_debug("%s:%d: %s no probe method\n", __func__, __LINE__,
			dev_name(&dev->core));

	pr_debug(" <- %s:%d: %s\n", __func__, __LINE__, dev_name(&dev->core));
	वापस result;
पूर्ण

अटल पूर्णांक ps3_प्रणाली_bus_हटाओ(काष्ठा device *_dev)
अणु
	काष्ठा ps3_प्रणाली_bus_device *dev = ps3_dev_to_प्रणाली_bus_dev(_dev);
	काष्ठा ps3_प्रणाली_bus_driver *drv;

	BUG_ON(!dev);
	dev_dbg(_dev, "%s:%d\n", __func__, __LINE__);

	drv = ps3_प्रणाली_bus_dev_to_प्रणाली_bus_drv(dev);
	BUG_ON(!drv);

	अगर (drv->हटाओ)
		drv->हटाओ(dev);
	अन्यथा
		dev_dbg(&dev->core, "%s:%d %s: no remove method\n",
			__func__, __LINE__, drv->core.name);

	pr_debug(" <- %s:%d: %s\n", __func__, __LINE__, dev_name(&dev->core));
	वापस 0;
पूर्ण

अटल व्योम ps3_प्रणाली_bus_shutकरोwn(काष्ठा device *_dev)
अणु
	काष्ठा ps3_प्रणाली_bus_device *dev = ps3_dev_to_प्रणाली_bus_dev(_dev);
	काष्ठा ps3_प्रणाली_bus_driver *drv;

	BUG_ON(!dev);

	dev_dbg(&dev->core, " -> %s:%d: match_id %d\n", __func__, __LINE__,
		dev->match_id);

	अगर (!dev->core.driver) अणु
		dev_dbg(&dev->core, "%s:%d: no driver bound\n", __func__,
			__LINE__);
		वापस;
	पूर्ण

	drv = ps3_प्रणाली_bus_dev_to_प्रणाली_bus_drv(dev);

	BUG_ON(!drv);

	dev_dbg(&dev->core, "%s:%d: %s -> %s\n", __func__, __LINE__,
		dev_name(&dev->core), drv->core.name);

	अगर (drv->shutकरोwn)
		drv->shutकरोwn(dev);
	अन्यथा अगर (drv->हटाओ) अणु
		dev_dbg(&dev->core, "%s:%d %s: no shutdown, calling remove\n",
			__func__, __LINE__, drv->core.name);
		drv->हटाओ(dev);
	पूर्ण अन्यथा अणु
		dev_dbg(&dev->core, "%s:%d %s: no shutdown method\n",
			__func__, __LINE__, drv->core.name);
		BUG();
	पूर्ण

	dev_dbg(&dev->core, " <- %s:%d\n", __func__, __LINE__);
पूर्ण

अटल पूर्णांक ps3_प्रणाली_bus_uevent(काष्ठा device *_dev, काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा ps3_प्रणाली_bus_device *dev = ps3_dev_to_प्रणाली_bus_dev(_dev);

	अगर (add_uevent_var(env, "MODALIAS=ps3:%d:%d", dev->match_id,
			   dev->match_sub_id))
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल sमाप_प्रकार modalias_show(काष्ठा device *_dev, काष्ठा device_attribute *a,
	अक्षर *buf)
अणु
	काष्ठा ps3_प्रणाली_bus_device *dev = ps3_dev_to_प्रणाली_bus_dev(_dev);
	पूर्णांक len = snम_लिखो(buf, PAGE_SIZE, "ps3:%d:%d\n", dev->match_id,
			   dev->match_sub_id);

	वापस (len >= PAGE_SIZE) ? (PAGE_SIZE - 1) : len;
पूर्ण
अटल DEVICE_ATTR_RO(modalias);

अटल काष्ठा attribute *ps3_प्रणाली_bus_dev_attrs[] = अणु
	&dev_attr_modalias.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(ps3_प्रणाली_bus_dev);

काष्ठा bus_type ps3_प्रणाली_bus_type = अणु
	.name = "ps3_system_bus",
	.match = ps3_प्रणाली_bus_match,
	.uevent = ps3_प्रणाली_bus_uevent,
	.probe = ps3_प्रणाली_bus_probe,
	.हटाओ = ps3_प्रणाली_bus_हटाओ,
	.shutकरोwn = ps3_प्रणाली_bus_shutकरोwn,
	.dev_groups = ps3_प्रणाली_bus_dev_groups,
पूर्ण;

अटल पूर्णांक __init ps3_प्रणाली_bus_init(व्योम)
अणु
	पूर्णांक result;

	अगर (!firmware_has_feature(FW_FEATURE_PS3_LV1))
		वापस -ENODEV;

	pr_debug(" -> %s:%d\n", __func__, __LINE__);

	mutex_init(&usage_hack.mutex);

	result = device_रेजिस्टर(&ps3_प्रणाली_bus);
	BUG_ON(result);

	result = bus_रेजिस्टर(&ps3_प्रणाली_bus_type);
	BUG_ON(result);

	pr_debug(" <- %s:%d\n", __func__, __LINE__);
	वापस result;
पूर्ण

core_initcall(ps3_प्रणाली_bus_init);

/* Allocates a contiguous real buffer and creates mappings over it.
 * Returns the भव address of the buffer and sets dma_handle
 * to the dma address (mapping) of the first page.
 */
अटल व्योम * ps3_alloc_coherent(काष्ठा device *_dev, माप_प्रकार size,
				 dma_addr_t *dma_handle, gfp_t flag,
				 अचिन्हित दीर्घ attrs)
अणु
	पूर्णांक result;
	काष्ठा ps3_प्रणाली_bus_device *dev = ps3_dev_to_प्रणाली_bus_dev(_dev);
	अचिन्हित दीर्घ virt_addr;

	flag &= ~(__GFP_DMA | __GFP_HIGHMEM);
	flag |= __GFP_ZERO;

	virt_addr = __get_मुक्त_pages(flag, get_order(size));

	अगर (!virt_addr) अणु
		pr_debug("%s:%d: get_free_pages failed\n", __func__, __LINE__);
		जाओ clean_none;
	पूर्ण

	result = ps3_dma_map(dev->d_region, virt_addr, size, dma_handle,
			     CBE_IOPTE_PP_W | CBE_IOPTE_PP_R |
			     CBE_IOPTE_SO_RW | CBE_IOPTE_M);

	अगर (result) अणु
		pr_debug("%s:%d: ps3_dma_map failed (%d)\n",
			__func__, __LINE__, result);
		BUG_ON("check region type");
		जाओ clean_alloc;
	पूर्ण

	वापस (व्योम*)virt_addr;

clean_alloc:
	मुक्त_pages(virt_addr, get_order(size));
clean_none:
	dma_handle = शून्य;
	वापस शून्य;
पूर्ण

अटल व्योम ps3_मुक्त_coherent(काष्ठा device *_dev, माप_प्रकार size, व्योम *vaddr,
			      dma_addr_t dma_handle, अचिन्हित दीर्घ attrs)
अणु
	काष्ठा ps3_प्रणाली_bus_device *dev = ps3_dev_to_प्रणाली_bus_dev(_dev);

	ps3_dma_unmap(dev->d_region, dma_handle, size);
	मुक्त_pages((अचिन्हित दीर्घ)vaddr, get_order(size));
पूर्ण

/* Creates TCEs क्रम a user provided buffer.  The user buffer must be
 * contiguous real kernel storage (not vदो_स्मृति).  The address passed here
 * comprises a page address and offset पूर्णांकo that page. The dma_addr_t
 * वापसed will poपूर्णांक to the same byte within the page as was passed in.
 */

अटल dma_addr_t ps3_sb_map_page(काष्ठा device *_dev, काष्ठा page *page,
	अचिन्हित दीर्घ offset, माप_प्रकार size, क्रमागत dma_data_direction direction,
	अचिन्हित दीर्घ attrs)
अणु
	काष्ठा ps3_प्रणाली_bus_device *dev = ps3_dev_to_प्रणाली_bus_dev(_dev);
	पूर्णांक result;
	dma_addr_t bus_addr;
	व्योम *ptr = page_address(page) + offset;

	result = ps3_dma_map(dev->d_region, (अचिन्हित दीर्घ)ptr, size,
			     &bus_addr,
			     CBE_IOPTE_PP_R | CBE_IOPTE_PP_W |
			     CBE_IOPTE_SO_RW | CBE_IOPTE_M);

	अगर (result) अणु
		pr_debug("%s:%d: ps3_dma_map failed (%d)\n",
			__func__, __LINE__, result);
	पूर्ण

	वापस bus_addr;
पूर्ण

अटल dma_addr_t ps3_ioc0_map_page(काष्ठा device *_dev, काष्ठा page *page,
				    अचिन्हित दीर्घ offset, माप_प्रकार size,
				    क्रमागत dma_data_direction direction,
				    अचिन्हित दीर्घ attrs)
अणु
	काष्ठा ps3_प्रणाली_bus_device *dev = ps3_dev_to_प्रणाली_bus_dev(_dev);
	पूर्णांक result;
	dma_addr_t bus_addr;
	u64 iopte_flag;
	व्योम *ptr = page_address(page) + offset;

	iopte_flag = CBE_IOPTE_M;
	चयन (direction) अणु
	हाल DMA_BIसूचीECTIONAL:
		iopte_flag |= CBE_IOPTE_PP_R | CBE_IOPTE_PP_W | CBE_IOPTE_SO_RW;
		अवरोध;
	हाल DMA_TO_DEVICE:
		iopte_flag |= CBE_IOPTE_PP_R | CBE_IOPTE_SO_R;
		अवरोध;
	हाल DMA_FROM_DEVICE:
		iopte_flag |= CBE_IOPTE_PP_W | CBE_IOPTE_SO_RW;
		अवरोध;
	शेष:
		/* not happned */
		BUG();
	पूर्ण;
	result = ps3_dma_map(dev->d_region, (अचिन्हित दीर्घ)ptr, size,
			     &bus_addr, iopte_flag);

	अगर (result) अणु
		pr_debug("%s:%d: ps3_dma_map failed (%d)\n",
			__func__, __LINE__, result);
	पूर्ण
	वापस bus_addr;
पूर्ण

अटल व्योम ps3_unmap_page(काष्ठा device *_dev, dma_addr_t dma_addr,
	माप_प्रकार size, क्रमागत dma_data_direction direction, अचिन्हित दीर्घ attrs)
अणु
	काष्ठा ps3_प्रणाली_bus_device *dev = ps3_dev_to_प्रणाली_bus_dev(_dev);
	पूर्णांक result;

	result = ps3_dma_unmap(dev->d_region, dma_addr, size);

	अगर (result) अणु
		pr_debug("%s:%d: ps3_dma_unmap failed (%d)\n",
			__func__, __LINE__, result);
	पूर्ण
पूर्ण

अटल पूर्णांक ps3_sb_map_sg(काष्ठा device *_dev, काष्ठा scatterlist *sgl,
	पूर्णांक nents, क्रमागत dma_data_direction direction, अचिन्हित दीर्घ attrs)
अणु
#अगर defined(CONFIG_PS3_DYNAMIC_DMA)
	BUG_ON("do");
	वापस -EPERM;
#अन्यथा
	काष्ठा ps3_प्रणाली_bus_device *dev = ps3_dev_to_प्रणाली_bus_dev(_dev);
	काष्ठा scatterlist *sg;
	पूर्णांक i;

	क्रम_each_sg(sgl, sg, nents, i) अणु
		पूर्णांक result = ps3_dma_map(dev->d_region, sg_phys(sg),
					sg->length, &sg->dma_address, 0);

		अगर (result) अणु
			pr_debug("%s:%d: ps3_dma_map failed (%d)\n",
				__func__, __LINE__, result);
			वापस -EINVAL;
		पूर्ण

		sg->dma_length = sg->length;
	पूर्ण

	वापस nents;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक ps3_ioc0_map_sg(काष्ठा device *_dev, काष्ठा scatterlist *sg,
			   पूर्णांक nents,
			   क्रमागत dma_data_direction direction,
			   अचिन्हित दीर्घ attrs)
अणु
	BUG();
	वापस 0;
पूर्ण

अटल व्योम ps3_sb_unmap_sg(काष्ठा device *_dev, काष्ठा scatterlist *sg,
	पूर्णांक nents, क्रमागत dma_data_direction direction, अचिन्हित दीर्घ attrs)
अणु
#अगर defined(CONFIG_PS3_DYNAMIC_DMA)
	BUG_ON("do");
#पूर्ण_अगर
पूर्ण

अटल व्योम ps3_ioc0_unmap_sg(काष्ठा device *_dev, काष्ठा scatterlist *sg,
			    पूर्णांक nents, क्रमागत dma_data_direction direction,
			    अचिन्हित दीर्घ attrs)
अणु
	BUG();
पूर्ण

अटल पूर्णांक ps3_dma_supported(काष्ठा device *_dev, u64 mask)
अणु
	वापस mask >= DMA_BIT_MASK(32);
पूर्ण

अटल स्थिर काष्ठा dma_map_ops ps3_sb_dma_ops = अणु
	.alloc = ps3_alloc_coherent,
	.मुक्त = ps3_मुक्त_coherent,
	.map_sg = ps3_sb_map_sg,
	.unmap_sg = ps3_sb_unmap_sg,
	.dma_supported = ps3_dma_supported,
	.map_page = ps3_sb_map_page,
	.unmap_page = ps3_unmap_page,
	.mmap = dma_common_mmap,
	.get_sgtable = dma_common_get_sgtable,
	.alloc_pages = dma_common_alloc_pages,
	.मुक्त_pages = dma_common_मुक्त_pages,
पूर्ण;

अटल स्थिर काष्ठा dma_map_ops ps3_ioc0_dma_ops = अणु
	.alloc = ps3_alloc_coherent,
	.मुक्त = ps3_मुक्त_coherent,
	.map_sg = ps3_ioc0_map_sg,
	.unmap_sg = ps3_ioc0_unmap_sg,
	.dma_supported = ps3_dma_supported,
	.map_page = ps3_ioc0_map_page,
	.unmap_page = ps3_unmap_page,
	.mmap = dma_common_mmap,
	.get_sgtable = dma_common_get_sgtable,
	.alloc_pages = dma_common_alloc_pages,
	.मुक्त_pages = dma_common_मुक्त_pages,
पूर्ण;

/**
 * ps3_प्रणाली_bus_release_device - हटाओ a device from the प्रणाली bus
 */

अटल व्योम ps3_प्रणाली_bus_release_device(काष्ठा device *_dev)
अणु
	काष्ठा ps3_प्रणाली_bus_device *dev = ps3_dev_to_प्रणाली_bus_dev(_dev);
	kमुक्त(dev);
पूर्ण

/**
 * ps3_प्रणाली_bus_device_रेजिस्टर - add a device to the प्रणाली bus
 *
 * ps3_प्रणाली_bus_device_रेजिस्टर() expects the dev object to be allocated
 * dynamically by the caller.  The प्रणाली bus takes ownership of the dev
 * object and मुक्तs the object in ps3_प्रणाली_bus_release_device().
 */

पूर्णांक ps3_प्रणाली_bus_device_रेजिस्टर(काष्ठा ps3_प्रणाली_bus_device *dev)
अणु
	पूर्णांक result;
	अटल अचिन्हित पूर्णांक dev_ioc0_count;
	अटल अचिन्हित पूर्णांक dev_sb_count;
	अटल अचिन्हित पूर्णांक dev_vuart_count;
	अटल अचिन्हित पूर्णांक dev_lpm_count;

	अगर (!dev->core.parent)
		dev->core.parent = &ps3_प्रणाली_bus;
	dev->core.bus = &ps3_प्रणाली_bus_type;
	dev->core.release = ps3_प्रणाली_bus_release_device;

	चयन (dev->dev_type) अणु
	हाल PS3_DEVICE_TYPE_IOC0:
		dev->core.dma_ops = &ps3_ioc0_dma_ops;
		dev_set_name(&dev->core, "ioc0_%02x", ++dev_ioc0_count);
		अवरोध;
	हाल PS3_DEVICE_TYPE_SB:
		dev->core.dma_ops = &ps3_sb_dma_ops;
		dev_set_name(&dev->core, "sb_%02x", ++dev_sb_count);

		अवरोध;
	हाल PS3_DEVICE_TYPE_VUART:
		dev_set_name(&dev->core, "vuart_%02x", ++dev_vuart_count);
		अवरोध;
	हाल PS3_DEVICE_TYPE_LPM:
		dev_set_name(&dev->core, "lpm_%02x", ++dev_lpm_count);
		अवरोध;
	शेष:
		BUG();
	पूर्ण;

	dev->core.of_node = शून्य;
	set_dev_node(&dev->core, 0);

	pr_debug("%s:%d add %s\n", __func__, __LINE__, dev_name(&dev->core));

	result = device_रेजिस्टर(&dev->core);
	वापस result;
पूर्ण

EXPORT_SYMBOL_GPL(ps3_प्रणाली_bus_device_रेजिस्टर);

पूर्णांक ps3_प्रणाली_bus_driver_रेजिस्टर(काष्ठा ps3_प्रणाली_bus_driver *drv)
अणु
	पूर्णांक result;

	pr_debug(" -> %s:%d: %s\n", __func__, __LINE__, drv->core.name);

	अगर (!firmware_has_feature(FW_FEATURE_PS3_LV1))
		वापस -ENODEV;

	drv->core.bus = &ps3_प्रणाली_bus_type;

	result = driver_रेजिस्टर(&drv->core);
	pr_debug(" <- %s:%d: %s\n", __func__, __LINE__, drv->core.name);
	वापस result;
पूर्ण

EXPORT_SYMBOL_GPL(ps3_प्रणाली_bus_driver_रेजिस्टर);

व्योम ps3_प्रणाली_bus_driver_unरेजिस्टर(काष्ठा ps3_प्रणाली_bus_driver *drv)
अणु
	pr_debug(" -> %s:%d: %s\n", __func__, __LINE__, drv->core.name);
	driver_unरेजिस्टर(&drv->core);
	pr_debug(" <- %s:%d: %s\n", __func__, __LINE__, drv->core.name);
पूर्ण

EXPORT_SYMBOL_GPL(ps3_प्रणाली_bus_driver_unरेजिस्टर);
