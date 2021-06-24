<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * VME Bridge Framework
 *
 * Author: Martyn Welch <martyn.welch@ge.com>
 * Copyright 2008 GE Intelligent Platक्रमms Embedded Systems, Inc.
 *
 * Based on work by Tom Armistead and Ajit Prem
 * Copyright 2004 Motorola Inc.
 */

#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <linux/mm.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/pci.h>
#समावेश <linux/poll.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/mutex.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <linux/vme.h>

#समावेश "vme_bridge.h"

/* Biपंचांगask and list of रेजिस्टरed buses both रक्षित by common mutex */
अटल अचिन्हित पूर्णांक vme_bus_numbers;
अटल LIST_HEAD(vme_bus_list);
अटल DEFINE_MUTEX(vme_buses_lock);

अटल पूर्णांक __init vme_init(व्योम);

अटल काष्ठा vme_dev *dev_to_vme_dev(काष्ठा device *dev)
अणु
	वापस container_of(dev, काष्ठा vme_dev, dev);
पूर्ण

/*
 * Find the bridge that the resource is associated with.
 */
अटल काष्ठा vme_bridge *find_bridge(काष्ठा vme_resource *resource)
अणु
	/* Get list to search */
	चयन (resource->type) अणु
	हाल VME_MASTER:
		वापस list_entry(resource->entry, काष्ठा vme_master_resource,
			list)->parent;
	हाल VME_SLAVE:
		वापस list_entry(resource->entry, काष्ठा vme_slave_resource,
			list)->parent;
	हाल VME_DMA:
		वापस list_entry(resource->entry, काष्ठा vme_dma_resource,
			list)->parent;
	हाल VME_LM:
		वापस list_entry(resource->entry, काष्ठा vme_lm_resource,
			list)->parent;
	शेष:
		prपूर्णांकk(KERN_ERR "Unknown resource type\n");
		वापस शून्य;
	पूर्ण
पूर्ण

/**
 * vme_alloc_consistent - Allocate contiguous memory.
 * @resource: Poपूर्णांकer to VME resource.
 * @size: Size of allocation required.
 * @dma: Poपूर्णांकer to variable to store physical address of allocation.
 *
 * Allocate a contiguous block of memory क्रम use by the driver. This is used to
 * create the buffers क्रम the slave winकरोws.
 *
 * Return: Virtual address of allocation on success, शून्य on failure.
 */
व्योम *vme_alloc_consistent(काष्ठा vme_resource *resource, माप_प्रकार size,
	dma_addr_t *dma)
अणु
	काष्ठा vme_bridge *bridge;

	अगर (!resource) अणु
		prपूर्णांकk(KERN_ERR "No resource\n");
		वापस शून्य;
	पूर्ण

	bridge = find_bridge(resource);
	अगर (!bridge) अणु
		prपूर्णांकk(KERN_ERR "Can't find bridge\n");
		वापस शून्य;
	पूर्ण

	अगर (!bridge->parent) अणु
		prपूर्णांकk(KERN_ERR "Dev entry NULL for bridge %s\n", bridge->name);
		वापस शून्य;
	पूर्ण

	अगर (!bridge->alloc_consistent) अणु
		prपूर्णांकk(KERN_ERR "alloc_consistent not supported by bridge %s\n",
		       bridge->name);
		वापस शून्य;
	पूर्ण

	वापस bridge->alloc_consistent(bridge->parent, size, dma);
पूर्ण
EXPORT_SYMBOL(vme_alloc_consistent);

/**
 * vme_मुक्त_consistent - Free previously allocated memory.
 * @resource: Poपूर्णांकer to VME resource.
 * @size: Size of allocation to मुक्त.
 * @vaddr: Virtual address of allocation.
 * @dma: Physical address of allocation.
 *
 * Free previously allocated block of contiguous memory.
 */
व्योम vme_मुक्त_consistent(काष्ठा vme_resource *resource, माप_प्रकार size,
	व्योम *vaddr, dma_addr_t dma)
अणु
	काष्ठा vme_bridge *bridge;

	अगर (!resource) अणु
		prपूर्णांकk(KERN_ERR "No resource\n");
		वापस;
	पूर्ण

	bridge = find_bridge(resource);
	अगर (!bridge) अणु
		prपूर्णांकk(KERN_ERR "Can't find bridge\n");
		वापस;
	पूर्ण

	अगर (!bridge->parent) अणु
		prपूर्णांकk(KERN_ERR "Dev entry NULL for bridge %s\n", bridge->name);
		वापस;
	पूर्ण

	अगर (!bridge->मुक्त_consistent) अणु
		prपूर्णांकk(KERN_ERR "free_consistent not supported by bridge %s\n",
		       bridge->name);
		वापस;
	पूर्ण

	bridge->मुक्त_consistent(bridge->parent, size, vaddr, dma);
पूर्ण
EXPORT_SYMBOL(vme_मुक्त_consistent);

/**
 * vme_get_size - Helper function वापसing size of a VME winकरोw
 * @resource: Poपूर्णांकer to VME slave or master resource.
 *
 * Determine the size of the VME winकरोw provided. This is a helper
 * function, wrappering the call to vme_master_get or vme_slave_get
 * depending on the type of winकरोw resource handed to it.
 *
 * Return: Size of the winकरोw on success, zero on failure.
 */
माप_प्रकार vme_get_size(काष्ठा vme_resource *resource)
अणु
	पूर्णांक enabled, retval;
	अचिन्हित दीर्घ दीर्घ base, size;
	dma_addr_t buf_base;
	u32 aspace, cycle, dwidth;

	चयन (resource->type) अणु
	हाल VME_MASTER:
		retval = vme_master_get(resource, &enabled, &base, &size,
			&aspace, &cycle, &dwidth);
		अगर (retval)
			वापस 0;

		वापस size;
	हाल VME_SLAVE:
		retval = vme_slave_get(resource, &enabled, &base, &size,
			&buf_base, &aspace, &cycle);
		अगर (retval)
			वापस 0;

		वापस size;
	हाल VME_DMA:
		वापस 0;
	शेष:
		prपूर्णांकk(KERN_ERR "Unknown resource type\n");
		वापस 0;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(vme_get_size);

पूर्णांक vme_check_winकरोw(u32 aspace, अचिन्हित दीर्घ दीर्घ vme_base,
		     अचिन्हित दीर्घ दीर्घ size)
अणु
	पूर्णांक retval = 0;

	अगर (vme_base + size < size)
		वापस -EINVAL;

	चयन (aspace) अणु
	हाल VME_A16:
		अगर (vme_base + size > VME_A16_MAX)
			retval = -EFAULT;
		अवरोध;
	हाल VME_A24:
		अगर (vme_base + size > VME_A24_MAX)
			retval = -EFAULT;
		अवरोध;
	हाल VME_A32:
		अगर (vme_base + size > VME_A32_MAX)
			retval = -EFAULT;
		अवरोध;
	हाल VME_A64:
		/* The VME_A64_MAX limit is actually U64_MAX + 1 */
		अवरोध;
	हाल VME_CRCSR:
		अगर (vme_base + size > VME_CRCSR_MAX)
			retval = -EFAULT;
		अवरोध;
	हाल VME_USER1:
	हाल VME_USER2:
	हाल VME_USER3:
	हाल VME_USER4:
		/* User Defined */
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "Invalid address space\n");
		retval = -EINVAL;
		अवरोध;
	पूर्ण

	वापस retval;
पूर्ण
EXPORT_SYMBOL(vme_check_winकरोw);

अटल u32 vme_get_aspace(पूर्णांक am)
अणु
	चयन (am) अणु
	हाल 0x29:
	हाल 0x2D:
		वापस VME_A16;
	हाल 0x38:
	हाल 0x39:
	हाल 0x3A:
	हाल 0x3B:
	हाल 0x3C:
	हाल 0x3D:
	हाल 0x3E:
	हाल 0x3F:
		वापस VME_A24;
	हाल 0x8:
	हाल 0x9:
	हाल 0xA:
	हाल 0xB:
	हाल 0xC:
	हाल 0xD:
	हाल 0xE:
	हाल 0xF:
		वापस VME_A32;
	हाल 0x0:
	हाल 0x1:
	हाल 0x3:
		वापस VME_A64;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * vme_slave_request - Request a VME slave winकरोw resource.
 * @vdev: Poपूर्णांकer to VME device काष्ठा vme_dev asचिन्हित to driver instance.
 * @address: Required VME address space.
 * @cycle: Required VME data transfer cycle type.
 *
 * Request use of a VME winकरोw resource capable of being set क्रम the requested
 * address space and data transfer cycle.
 *
 * Return: Poपूर्णांकer to VME resource on success, शून्य on failure.
 */
काष्ठा vme_resource *vme_slave_request(काष्ठा vme_dev *vdev, u32 address,
	u32 cycle)
अणु
	काष्ठा vme_bridge *bridge;
	काष्ठा list_head *slave_pos = शून्य;
	काष्ठा vme_slave_resource *allocated_image = शून्य;
	काष्ठा vme_slave_resource *slave_image = शून्य;
	काष्ठा vme_resource *resource = शून्य;

	bridge = vdev->bridge;
	अगर (!bridge) अणु
		prपूर्णांकk(KERN_ERR "Can't find VME bus\n");
		जाओ err_bus;
	पूर्ण

	/* Loop through slave resources */
	list_क्रम_each(slave_pos, &bridge->slave_resources) अणु
		slave_image = list_entry(slave_pos,
			काष्ठा vme_slave_resource, list);

		अगर (!slave_image) अणु
			prपूर्णांकk(KERN_ERR "Registered NULL Slave resource\n");
			जारी;
		पूर्ण

		/* Find an unlocked and compatible image */
		mutex_lock(&slave_image->mtx);
		अगर (((slave_image->address_attr & address) == address) &&
			((slave_image->cycle_attr & cycle) == cycle) &&
			(slave_image->locked == 0)) अणु

			slave_image->locked = 1;
			mutex_unlock(&slave_image->mtx);
			allocated_image = slave_image;
			अवरोध;
		पूर्ण
		mutex_unlock(&slave_image->mtx);
	पूर्ण

	/* No मुक्त image */
	अगर (!allocated_image)
		जाओ err_image;

	resource = kदो_स्मृति(माप(*resource), GFP_KERNEL);
	अगर (!resource)
		जाओ err_alloc;

	resource->type = VME_SLAVE;
	resource->entry = &allocated_image->list;

	वापस resource;

err_alloc:
	/* Unlock image */
	mutex_lock(&slave_image->mtx);
	slave_image->locked = 0;
	mutex_unlock(&slave_image->mtx);
err_image:
err_bus:
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(vme_slave_request);

/**
 * vme_slave_set - Set VME slave winकरोw configuration.
 * @resource: Poपूर्णांकer to VME slave resource.
 * @enabled: State to which the winकरोw should be configured.
 * @vme_base: Base address क्रम the winकरोw.
 * @size: Size of the VME winकरोw.
 * @buf_base: Based address of buffer used to provide VME slave winकरोw storage.
 * @aspace: VME address space क्रम the VME winकरोw.
 * @cycle: VME data transfer cycle type क्रम the VME winकरोw.
 *
 * Set configuration क्रम provided VME slave winकरोw.
 *
 * Return: Zero on success, -EINVAL अगर operation is not supported on this
 *         device, अगर an invalid resource has been provided or invalid
 *         attributes are provided. Hardware specअगरic errors may also be
 *         वापसed.
 */
पूर्णांक vme_slave_set(काष्ठा vme_resource *resource, पूर्णांक enabled,
	अचिन्हित दीर्घ दीर्घ vme_base, अचिन्हित दीर्घ दीर्घ size,
	dma_addr_t buf_base, u32 aspace, u32 cycle)
अणु
	काष्ठा vme_bridge *bridge = find_bridge(resource);
	काष्ठा vme_slave_resource *image;
	पूर्णांक retval;

	अगर (resource->type != VME_SLAVE) अणु
		prपूर्णांकk(KERN_ERR "Not a slave resource\n");
		वापस -EINVAL;
	पूर्ण

	image = list_entry(resource->entry, काष्ठा vme_slave_resource, list);

	अगर (!bridge->slave_set) अणु
		prपूर्णांकk(KERN_ERR "Function not supported\n");
		वापस -ENOSYS;
	पूर्ण

	अगर (!(((image->address_attr & aspace) == aspace) &&
		((image->cycle_attr & cycle) == cycle))) अणु
		prपूर्णांकk(KERN_ERR "Invalid attributes\n");
		वापस -EINVAL;
	पूर्ण

	retval = vme_check_winकरोw(aspace, vme_base, size);
	अगर (retval)
		वापस retval;

	वापस bridge->slave_set(image, enabled, vme_base, size, buf_base,
		aspace, cycle);
पूर्ण
EXPORT_SYMBOL(vme_slave_set);

/**
 * vme_slave_get - Retrieve VME slave winकरोw configuration.
 * @resource: Poपूर्णांकer to VME slave resource.
 * @enabled: Poपूर्णांकer to variable क्रम storing state.
 * @vme_base: Poपूर्णांकer to variable क्रम storing winकरोw base address.
 * @size: Poपूर्णांकer to variable क्रम storing winकरोw size.
 * @buf_base: Poपूर्णांकer to variable क्रम storing slave buffer base address.
 * @aspace: Poपूर्णांकer to variable क्रम storing VME address space.
 * @cycle: Poपूर्णांकer to variable क्रम storing VME data transfer cycle type.
 *
 * Return configuration क्रम provided VME slave winकरोw.
 *
 * Return: Zero on success, -EINVAL अगर operation is not supported on this
 *         device or अगर an invalid resource has been provided.
 */
पूर्णांक vme_slave_get(काष्ठा vme_resource *resource, पूर्णांक *enabled,
	अचिन्हित दीर्घ दीर्घ *vme_base, अचिन्हित दीर्घ दीर्घ *size,
	dma_addr_t *buf_base, u32 *aspace, u32 *cycle)
अणु
	काष्ठा vme_bridge *bridge = find_bridge(resource);
	काष्ठा vme_slave_resource *image;

	अगर (resource->type != VME_SLAVE) अणु
		prपूर्णांकk(KERN_ERR "Not a slave resource\n");
		वापस -EINVAL;
	पूर्ण

	image = list_entry(resource->entry, काष्ठा vme_slave_resource, list);

	अगर (!bridge->slave_get) अणु
		prपूर्णांकk(KERN_ERR "vme_slave_get not supported\n");
		वापस -EINVAL;
	पूर्ण

	वापस bridge->slave_get(image, enabled, vme_base, size, buf_base,
		aspace, cycle);
पूर्ण
EXPORT_SYMBOL(vme_slave_get);

/**
 * vme_slave_मुक्त - Free VME slave winकरोw
 * @resource: Poपूर्णांकer to VME slave resource.
 *
 * Free the provided slave resource so that it may be पुनः_स्मृतिated.
 */
व्योम vme_slave_मुक्त(काष्ठा vme_resource *resource)
अणु
	काष्ठा vme_slave_resource *slave_image;

	अगर (resource->type != VME_SLAVE) अणु
		prपूर्णांकk(KERN_ERR "Not a slave resource\n");
		वापस;
	पूर्ण

	slave_image = list_entry(resource->entry, काष्ठा vme_slave_resource,
		list);
	अगर (!slave_image) अणु
		prपूर्णांकk(KERN_ERR "Can't find slave resource\n");
		वापस;
	पूर्ण

	/* Unlock image */
	mutex_lock(&slave_image->mtx);
	अगर (slave_image->locked == 0)
		prपूर्णांकk(KERN_ERR "Image is already free\n");

	slave_image->locked = 0;
	mutex_unlock(&slave_image->mtx);

	/* Free up resource memory */
	kमुक्त(resource);
पूर्ण
EXPORT_SYMBOL(vme_slave_मुक्त);

/**
 * vme_master_request - Request a VME master winकरोw resource.
 * @vdev: Poपूर्णांकer to VME device काष्ठा vme_dev asचिन्हित to driver instance.
 * @address: Required VME address space.
 * @cycle: Required VME data transfer cycle type.
 * @dwidth: Required VME data transfer width.
 *
 * Request use of a VME winकरोw resource capable of being set क्रम the requested
 * address space, data transfer cycle and width.
 *
 * Return: Poपूर्णांकer to VME resource on success, शून्य on failure.
 */
काष्ठा vme_resource *vme_master_request(काष्ठा vme_dev *vdev, u32 address,
	u32 cycle, u32 dwidth)
अणु
	काष्ठा vme_bridge *bridge;
	काष्ठा list_head *master_pos = शून्य;
	काष्ठा vme_master_resource *allocated_image = शून्य;
	काष्ठा vme_master_resource *master_image = शून्य;
	काष्ठा vme_resource *resource = शून्य;

	bridge = vdev->bridge;
	अगर (!bridge) अणु
		prपूर्णांकk(KERN_ERR "Can't find VME bus\n");
		जाओ err_bus;
	पूर्ण

	/* Loop through master resources */
	list_क्रम_each(master_pos, &bridge->master_resources) अणु
		master_image = list_entry(master_pos,
			काष्ठा vme_master_resource, list);

		अगर (!master_image) अणु
			prपूर्णांकk(KERN_WARNING "Registered NULL master resource\n");
			जारी;
		पूर्ण

		/* Find an unlocked and compatible image */
		spin_lock(&master_image->lock);
		अगर (((master_image->address_attr & address) == address) &&
			((master_image->cycle_attr & cycle) == cycle) &&
			((master_image->width_attr & dwidth) == dwidth) &&
			(master_image->locked == 0)) अणु

			master_image->locked = 1;
			spin_unlock(&master_image->lock);
			allocated_image = master_image;
			अवरोध;
		पूर्ण
		spin_unlock(&master_image->lock);
	पूर्ण

	/* Check to see अगर we found a resource */
	अगर (!allocated_image) अणु
		prपूर्णांकk(KERN_ERR "Can't find a suitable resource\n");
		जाओ err_image;
	पूर्ण

	resource = kदो_स्मृति(माप(*resource), GFP_KERNEL);
	अगर (!resource)
		जाओ err_alloc;

	resource->type = VME_MASTER;
	resource->entry = &allocated_image->list;

	वापस resource;

err_alloc:
	/* Unlock image */
	spin_lock(&master_image->lock);
	master_image->locked = 0;
	spin_unlock(&master_image->lock);
err_image:
err_bus:
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(vme_master_request);

/**
 * vme_master_set - Set VME master winकरोw configuration.
 * @resource: Poपूर्णांकer to VME master resource.
 * @enabled: State to which the winकरोw should be configured.
 * @vme_base: Base address क्रम the winकरोw.
 * @size: Size of the VME winकरोw.
 * @aspace: VME address space क्रम the VME winकरोw.
 * @cycle: VME data transfer cycle type क्रम the VME winकरोw.
 * @dwidth: VME data transfer width क्रम the VME winकरोw.
 *
 * Set configuration क्रम provided VME master winकरोw.
 *
 * Return: Zero on success, -EINVAL अगर operation is not supported on this
 *         device, अगर an invalid resource has been provided or invalid
 *         attributes are provided. Hardware specअगरic errors may also be
 *         वापसed.
 */
पूर्णांक vme_master_set(काष्ठा vme_resource *resource, पूर्णांक enabled,
	अचिन्हित दीर्घ दीर्घ vme_base, अचिन्हित दीर्घ दीर्घ size, u32 aspace,
	u32 cycle, u32 dwidth)
अणु
	काष्ठा vme_bridge *bridge = find_bridge(resource);
	काष्ठा vme_master_resource *image;
	पूर्णांक retval;

	अगर (resource->type != VME_MASTER) अणु
		prपूर्णांकk(KERN_ERR "Not a master resource\n");
		वापस -EINVAL;
	पूर्ण

	image = list_entry(resource->entry, काष्ठा vme_master_resource, list);

	अगर (!bridge->master_set) अणु
		prपूर्णांकk(KERN_WARNING "vme_master_set not supported\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!(((image->address_attr & aspace) == aspace) &&
		((image->cycle_attr & cycle) == cycle) &&
		((image->width_attr & dwidth) == dwidth))) अणु
		prपूर्णांकk(KERN_WARNING "Invalid attributes\n");
		वापस -EINVAL;
	पूर्ण

	retval = vme_check_winकरोw(aspace, vme_base, size);
	अगर (retval)
		वापस retval;

	वापस bridge->master_set(image, enabled, vme_base, size, aspace,
		cycle, dwidth);
पूर्ण
EXPORT_SYMBOL(vme_master_set);

/**
 * vme_master_get - Retrieve VME master winकरोw configuration.
 * @resource: Poपूर्णांकer to VME master resource.
 * @enabled: Poपूर्णांकer to variable क्रम storing state.
 * @vme_base: Poपूर्णांकer to variable क्रम storing winकरोw base address.
 * @size: Poपूर्णांकer to variable क्रम storing winकरोw size.
 * @aspace: Poपूर्णांकer to variable क्रम storing VME address space.
 * @cycle: Poपूर्णांकer to variable क्रम storing VME data transfer cycle type.
 * @dwidth: Poपूर्णांकer to variable क्रम storing VME data transfer width.
 *
 * Return configuration क्रम provided VME master winकरोw.
 *
 * Return: Zero on success, -EINVAL अगर operation is not supported on this
 *         device or अगर an invalid resource has been provided.
 */
पूर्णांक vme_master_get(काष्ठा vme_resource *resource, पूर्णांक *enabled,
	अचिन्हित दीर्घ दीर्घ *vme_base, अचिन्हित दीर्घ दीर्घ *size, u32 *aspace,
	u32 *cycle, u32 *dwidth)
अणु
	काष्ठा vme_bridge *bridge = find_bridge(resource);
	काष्ठा vme_master_resource *image;

	अगर (resource->type != VME_MASTER) अणु
		prपूर्णांकk(KERN_ERR "Not a master resource\n");
		वापस -EINVAL;
	पूर्ण

	image = list_entry(resource->entry, काष्ठा vme_master_resource, list);

	अगर (!bridge->master_get) अणु
		prपूर्णांकk(KERN_WARNING "%s not supported\n", __func__);
		वापस -EINVAL;
	पूर्ण

	वापस bridge->master_get(image, enabled, vme_base, size, aspace,
		cycle, dwidth);
पूर्ण
EXPORT_SYMBOL(vme_master_get);

/**
 * vme_master_पढ़ो - Read data from VME space पूर्णांकo a buffer.
 * @resource: Poपूर्णांकer to VME master resource.
 * @buf: Poपूर्णांकer to buffer where data should be transferred.
 * @count: Number of bytes to transfer.
 * @offset: Offset पूर्णांकo VME master winकरोw at which to start transfer.
 *
 * Perक्रमm पढ़ो of count bytes of data from location on VME bus which maps पूर्णांकo
 * the VME master winकरोw at offset to buf.
 *
 * Return: Number of bytes पढ़ो, -EINVAL अगर resource is not a VME master
 *         resource or पढ़ो operation is not supported. -EFAULT वापसed अगर
 *         invalid offset is provided. Hardware specअगरic errors may also be
 *         वापसed.
 */
sमाप_प्रकार vme_master_पढ़ो(काष्ठा vme_resource *resource, व्योम *buf, माप_प्रकार count,
	loff_t offset)
अणु
	काष्ठा vme_bridge *bridge = find_bridge(resource);
	काष्ठा vme_master_resource *image;
	माप_प्रकार length;

	अगर (!bridge->master_पढ़ो) अणु
		prपूर्णांकk(KERN_WARNING "Reading from resource not supported\n");
		वापस -EINVAL;
	पूर्ण

	अगर (resource->type != VME_MASTER) अणु
		prपूर्णांकk(KERN_ERR "Not a master resource\n");
		वापस -EINVAL;
	पूर्ण

	image = list_entry(resource->entry, काष्ठा vme_master_resource, list);

	length = vme_get_size(resource);

	अगर (offset > length) अणु
		prपूर्णांकk(KERN_WARNING "Invalid Offset\n");
		वापस -EFAULT;
	पूर्ण

	अगर ((offset + count) > length)
		count = length - offset;

	वापस bridge->master_पढ़ो(image, buf, count, offset);

पूर्ण
EXPORT_SYMBOL(vme_master_पढ़ो);

/**
 * vme_master_ग_लिखो - Write data out to VME space from a buffer.
 * @resource: Poपूर्णांकer to VME master resource.
 * @buf: Poपूर्णांकer to buffer holding data to transfer.
 * @count: Number of bytes to transfer.
 * @offset: Offset पूर्णांकo VME master winकरोw at which to start transfer.
 *
 * Perक्रमm ग_लिखो of count bytes of data from buf to location on VME bus which
 * maps पूर्णांकo the VME master winकरोw at offset.
 *
 * Return: Number of bytes written, -EINVAL अगर resource is not a VME master
 *         resource or ग_लिखो operation is not supported. -EFAULT वापसed अगर
 *         invalid offset is provided. Hardware specअगरic errors may also be
 *         वापसed.
 */
sमाप_प्रकार vme_master_ग_लिखो(काष्ठा vme_resource *resource, व्योम *buf,
	माप_प्रकार count, loff_t offset)
अणु
	काष्ठा vme_bridge *bridge = find_bridge(resource);
	काष्ठा vme_master_resource *image;
	माप_प्रकार length;

	अगर (!bridge->master_ग_लिखो) अणु
		prपूर्णांकk(KERN_WARNING "Writing to resource not supported\n");
		वापस -EINVAL;
	पूर्ण

	अगर (resource->type != VME_MASTER) अणु
		prपूर्णांकk(KERN_ERR "Not a master resource\n");
		वापस -EINVAL;
	पूर्ण

	image = list_entry(resource->entry, काष्ठा vme_master_resource, list);

	length = vme_get_size(resource);

	अगर (offset > length) अणु
		prपूर्णांकk(KERN_WARNING "Invalid Offset\n");
		वापस -EFAULT;
	पूर्ण

	अगर ((offset + count) > length)
		count = length - offset;

	वापस bridge->master_ग_लिखो(image, buf, count, offset);
पूर्ण
EXPORT_SYMBOL(vme_master_ग_लिखो);

/**
 * vme_master_rmw - Perक्रमm पढ़ो-modअगरy-ग_लिखो cycle.
 * @resource: Poपूर्णांकer to VME master resource.
 * @mask: Bits to be compared and swapped in operation.
 * @compare: Bits to be compared with data पढ़ो from offset.
 * @swap: Bits to be swapped in data पढ़ो from offset.
 * @offset: Offset पूर्णांकo VME master winकरोw at which to perक्रमm operation.
 *
 * Perक्रमm पढ़ो-modअगरy-ग_लिखो cycle on provided location:
 * - Location on VME bus is पढ़ो.
 * - Bits selected by mask are compared with compare.
 * - Where a selected bit matches that in compare and are selected in swap,
 * the bit is swapped.
 * - Result written back to location on VME bus.
 *
 * Return: Bytes written on success, -EINVAL अगर resource is not a VME master
 *         resource or RMW operation is not supported. Hardware specअगरic
 *         errors may also be वापसed.
 */
अचिन्हित पूर्णांक vme_master_rmw(काष्ठा vme_resource *resource, अचिन्हित पूर्णांक mask,
	अचिन्हित पूर्णांक compare, अचिन्हित पूर्णांक swap, loff_t offset)
अणु
	काष्ठा vme_bridge *bridge = find_bridge(resource);
	काष्ठा vme_master_resource *image;

	अगर (!bridge->master_rmw) अणु
		prपूर्णांकk(KERN_WARNING "Writing to resource not supported\n");
		वापस -EINVAL;
	पूर्ण

	अगर (resource->type != VME_MASTER) अणु
		prपूर्णांकk(KERN_ERR "Not a master resource\n");
		वापस -EINVAL;
	पूर्ण

	image = list_entry(resource->entry, काष्ठा vme_master_resource, list);

	वापस bridge->master_rmw(image, mask, compare, swap, offset);
पूर्ण
EXPORT_SYMBOL(vme_master_rmw);

/**
 * vme_master_mmap - Mmap region of VME master winकरोw.
 * @resource: Poपूर्णांकer to VME master resource.
 * @vma: Poपूर्णांकer to definition of user mapping.
 *
 * Memory map a region of the VME master winकरोw पूर्णांकo user space.
 *
 * Return: Zero on success, -EINVAL अगर resource is not a VME master
 *         resource or -EFAULT अगर map exceeds winकरोw size. Other generic mmap
 *         errors may also be वापसed.
 */
पूर्णांक vme_master_mmap(काष्ठा vme_resource *resource, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा vme_master_resource *image;
	phys_addr_t phys_addr;
	अचिन्हित दीर्घ vma_size;

	अगर (resource->type != VME_MASTER) अणु
		pr_err("Not a master resource\n");
		वापस -EINVAL;
	पूर्ण

	image = list_entry(resource->entry, काष्ठा vme_master_resource, list);
	phys_addr = image->bus_resource.start + (vma->vm_pgoff << PAGE_SHIFT);
	vma_size = vma->vm_end - vma->vm_start;

	अगर (phys_addr + vma_size > image->bus_resource.end + 1) अणु
		pr_err("Map size cannot exceed the window size\n");
		वापस -EFAULT;
	पूर्ण

	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);

	वापस vm_iomap_memory(vma, phys_addr, vma->vm_end - vma->vm_start);
पूर्ण
EXPORT_SYMBOL(vme_master_mmap);

/**
 * vme_master_मुक्त - Free VME master winकरोw
 * @resource: Poपूर्णांकer to VME master resource.
 *
 * Free the provided master resource so that it may be पुनः_स्मृतिated.
 */
व्योम vme_master_मुक्त(काष्ठा vme_resource *resource)
अणु
	काष्ठा vme_master_resource *master_image;

	अगर (resource->type != VME_MASTER) अणु
		prपूर्णांकk(KERN_ERR "Not a master resource\n");
		वापस;
	पूर्ण

	master_image = list_entry(resource->entry, काष्ठा vme_master_resource,
		list);
	अगर (!master_image) अणु
		prपूर्णांकk(KERN_ERR "Can't find master resource\n");
		वापस;
	पूर्ण

	/* Unlock image */
	spin_lock(&master_image->lock);
	अगर (master_image->locked == 0)
		prपूर्णांकk(KERN_ERR "Image is already free\n");

	master_image->locked = 0;
	spin_unlock(&master_image->lock);

	/* Free up resource memory */
	kमुक्त(resource);
पूर्ण
EXPORT_SYMBOL(vme_master_मुक्त);

/**
 * vme_dma_request - Request a DMA controller.
 * @vdev: Poपूर्णांकer to VME device काष्ठा vme_dev asचिन्हित to driver instance.
 * @route: Required src/destination combination.
 *
 * Request a VME DMA controller with capability to perक्रमm transfers bewteen
 * requested source/destination combination.
 *
 * Return: Poपूर्णांकer to VME DMA resource on success, शून्य on failure.
 */
काष्ठा vme_resource *vme_dma_request(काष्ठा vme_dev *vdev, u32 route)
अणु
	काष्ठा vme_bridge *bridge;
	काष्ठा list_head *dma_pos = शून्य;
	काष्ठा vme_dma_resource *allocated_ctrlr = शून्य;
	काष्ठा vme_dma_resource *dma_ctrlr = शून्य;
	काष्ठा vme_resource *resource = शून्य;

	/* XXX Not checking resource attributes */
	prपूर्णांकk(KERN_ERR "No VME resource Attribute tests done\n");

	bridge = vdev->bridge;
	अगर (!bridge) अणु
		prपूर्णांकk(KERN_ERR "Can't find VME bus\n");
		जाओ err_bus;
	पूर्ण

	/* Loop through DMA resources */
	list_क्रम_each(dma_pos, &bridge->dma_resources) अणु
		dma_ctrlr = list_entry(dma_pos,
			काष्ठा vme_dma_resource, list);
		अगर (!dma_ctrlr) अणु
			prपूर्णांकk(KERN_ERR "Registered NULL DMA resource\n");
			जारी;
		पूर्ण

		/* Find an unlocked and compatible controller */
		mutex_lock(&dma_ctrlr->mtx);
		अगर (((dma_ctrlr->route_attr & route) == route) &&
			(dma_ctrlr->locked == 0)) अणु

			dma_ctrlr->locked = 1;
			mutex_unlock(&dma_ctrlr->mtx);
			allocated_ctrlr = dma_ctrlr;
			अवरोध;
		पूर्ण
		mutex_unlock(&dma_ctrlr->mtx);
	पूर्ण

	/* Check to see अगर we found a resource */
	अगर (!allocated_ctrlr)
		जाओ err_ctrlr;

	resource = kदो_स्मृति(माप(*resource), GFP_KERNEL);
	अगर (!resource)
		जाओ err_alloc;

	resource->type = VME_DMA;
	resource->entry = &allocated_ctrlr->list;

	वापस resource;

err_alloc:
	/* Unlock image */
	mutex_lock(&dma_ctrlr->mtx);
	dma_ctrlr->locked = 0;
	mutex_unlock(&dma_ctrlr->mtx);
err_ctrlr:
err_bus:
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(vme_dma_request);

/**
 * vme_new_dma_list - Create new VME DMA list.
 * @resource: Poपूर्णांकer to VME DMA resource.
 *
 * Create a new VME DMA list. It is the responsibility of the user to मुक्त
 * the list once it is no दीर्घer required with vme_dma_list_मुक्त().
 *
 * Return: Poपूर्णांकer to new VME DMA list, शून्य on allocation failure or invalid
 *         VME DMA resource.
 */
काष्ठा vme_dma_list *vme_new_dma_list(काष्ठा vme_resource *resource)
अणु
	काष्ठा vme_dma_list *dma_list;

	अगर (resource->type != VME_DMA) अणु
		prपूर्णांकk(KERN_ERR "Not a DMA resource\n");
		वापस शून्य;
	पूर्ण

	dma_list = kदो_स्मृति(माप(*dma_list), GFP_KERNEL);
	अगर (!dma_list)
		वापस शून्य;

	INIT_LIST_HEAD(&dma_list->entries);
	dma_list->parent = list_entry(resource->entry,
				      काष्ठा vme_dma_resource,
				      list);
	mutex_init(&dma_list->mtx);

	वापस dma_list;
पूर्ण
EXPORT_SYMBOL(vme_new_dma_list);

/**
 * vme_dma_pattern_attribute - Create "Pattern" type VME DMA list attribute.
 * @pattern: Value to use used as pattern
 * @type: Type of pattern to be written.
 *
 * Create VME DMA list attribute क्रम pattern generation. It is the
 * responsibility of the user to मुक्त used attributes using
 * vme_dma_मुक्त_attribute().
 *
 * Return: Poपूर्णांकer to VME DMA attribute, शून्य on failure.
 */
काष्ठा vme_dma_attr *vme_dma_pattern_attribute(u32 pattern, u32 type)
अणु
	काष्ठा vme_dma_attr *attributes;
	काष्ठा vme_dma_pattern *pattern_attr;

	attributes = kदो_स्मृति(माप(*attributes), GFP_KERNEL);
	अगर (!attributes)
		जाओ err_attr;

	pattern_attr = kदो_स्मृति(माप(*pattern_attr), GFP_KERNEL);
	अगर (!pattern_attr)
		जाओ err_pat;

	attributes->type = VME_DMA_PATTERN;
	attributes->निजी = (व्योम *)pattern_attr;

	pattern_attr->pattern = pattern;
	pattern_attr->type = type;

	वापस attributes;

err_pat:
	kमुक्त(attributes);
err_attr:
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(vme_dma_pattern_attribute);

/**
 * vme_dma_pci_attribute - Create "PCI" type VME DMA list attribute.
 * @address: PCI base address क्रम DMA transfer.
 *
 * Create VME DMA list attribute poपूर्णांकing to a location on PCI क्रम DMA
 * transfers. It is the responsibility of the user to मुक्त used attributes
 * using vme_dma_मुक्त_attribute().
 *
 * Return: Poपूर्णांकer to VME DMA attribute, शून्य on failure.
 */
काष्ठा vme_dma_attr *vme_dma_pci_attribute(dma_addr_t address)
अणु
	काष्ठा vme_dma_attr *attributes;
	काष्ठा vme_dma_pci *pci_attr;

	/* XXX Run some sanity checks here */

	attributes = kदो_स्मृति(माप(*attributes), GFP_KERNEL);
	अगर (!attributes)
		जाओ err_attr;

	pci_attr = kदो_स्मृति(माप(*pci_attr), GFP_KERNEL);
	अगर (!pci_attr)
		जाओ err_pci;

	attributes->type = VME_DMA_PCI;
	attributes->निजी = (व्योम *)pci_attr;

	pci_attr->address = address;

	वापस attributes;

err_pci:
	kमुक्त(attributes);
err_attr:
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(vme_dma_pci_attribute);

/**
 * vme_dma_vme_attribute - Create "VME" type VME DMA list attribute.
 * @address: VME base address क्रम DMA transfer.
 * @aspace: VME address space to use क्रम DMA transfer.
 * @cycle: VME bus cycle to use क्रम DMA transfer.
 * @dwidth: VME data width to use क्रम DMA transfer.
 *
 * Create VME DMA list attribute poपूर्णांकing to a location on the VME bus क्रम DMA
 * transfers. It is the responsibility of the user to मुक्त used attributes
 * using vme_dma_मुक्त_attribute().
 *
 * Return: Poपूर्णांकer to VME DMA attribute, शून्य on failure.
 */
काष्ठा vme_dma_attr *vme_dma_vme_attribute(अचिन्हित दीर्घ दीर्घ address,
	u32 aspace, u32 cycle, u32 dwidth)
अणु
	काष्ठा vme_dma_attr *attributes;
	काष्ठा vme_dma_vme *vme_attr;

	attributes = kदो_स्मृति(माप(*attributes), GFP_KERNEL);
	अगर (!attributes)
		जाओ err_attr;

	vme_attr = kदो_स्मृति(माप(*vme_attr), GFP_KERNEL);
	अगर (!vme_attr)
		जाओ err_vme;

	attributes->type = VME_DMA_VME;
	attributes->निजी = (व्योम *)vme_attr;

	vme_attr->address = address;
	vme_attr->aspace = aspace;
	vme_attr->cycle = cycle;
	vme_attr->dwidth = dwidth;

	वापस attributes;

err_vme:
	kमुक्त(attributes);
err_attr:
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(vme_dma_vme_attribute);

/**
 * vme_dma_मुक्त_attribute - Free DMA list attribute.
 * @attributes: Poपूर्णांकer to DMA list attribute.
 *
 * Free VME DMA list attribute. VME DMA list attributes can be safely मुक्तd
 * once vme_dma_list_add() has वापसed.
 */
व्योम vme_dma_मुक्त_attribute(काष्ठा vme_dma_attr *attributes)
अणु
	kमुक्त(attributes->निजी);
	kमुक्त(attributes);
पूर्ण
EXPORT_SYMBOL(vme_dma_मुक्त_attribute);

/**
 * vme_dma_list_add - Add enty to a VME DMA list.
 * @list: Poपूर्णांकer to VME list.
 * @src: Poपूर्णांकer to DMA list attribute to use as source.
 * @dest: Poपूर्णांकer to DMA list attribute to use as destination.
 * @count: Number of bytes to transfer.
 *
 * Add an entry to the provided VME DMA list. Entry requires poपूर्णांकers to source
 * and destination DMA attributes and a count.
 *
 * Please note, the attributes supported as source and destinations क्रम
 * transfers are hardware dependent.
 *
 * Return: Zero on success, -EINVAL अगर operation is not supported on this
 *         device or अगर the link list has alपढ़ोy been submitted क्रम execution.
 *         Hardware specअगरic errors also possible.
 */
पूर्णांक vme_dma_list_add(काष्ठा vme_dma_list *list, काष्ठा vme_dma_attr *src,
	काष्ठा vme_dma_attr *dest, माप_प्रकार count)
अणु
	काष्ठा vme_bridge *bridge = list->parent->parent;
	पूर्णांक retval;

	अगर (!bridge->dma_list_add) अणु
		prपूर्णांकk(KERN_WARNING "Link List DMA generation not supported\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!mutex_trylock(&list->mtx)) अणु
		prपूर्णांकk(KERN_ERR "Link List already submitted\n");
		वापस -EINVAL;
	पूर्ण

	retval = bridge->dma_list_add(list, src, dest, count);

	mutex_unlock(&list->mtx);

	वापस retval;
पूर्ण
EXPORT_SYMBOL(vme_dma_list_add);

/**
 * vme_dma_list_exec - Queue a VME DMA list क्रम execution.
 * @list: Poपूर्णांकer to VME list.
 *
 * Queue the provided VME DMA list क्रम execution. The call will वापस once the
 * list has been executed.
 *
 * Return: Zero on success, -EINVAL अगर operation is not supported on this
 *         device. Hardware specअगरic errors also possible.
 */
पूर्णांक vme_dma_list_exec(काष्ठा vme_dma_list *list)
अणु
	काष्ठा vme_bridge *bridge = list->parent->parent;
	पूर्णांक retval;

	अगर (!bridge->dma_list_exec) अणु
		prपूर्णांकk(KERN_ERR "Link List DMA execution not supported\n");
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&list->mtx);

	retval = bridge->dma_list_exec(list);

	mutex_unlock(&list->mtx);

	वापस retval;
पूर्ण
EXPORT_SYMBOL(vme_dma_list_exec);

/**
 * vme_dma_list_मुक्त - Free a VME DMA list.
 * @list: Poपूर्णांकer to VME list.
 *
 * Free the provided DMA list and all its entries.
 *
 * Return: Zero on success, -EINVAL on invalid VME resource, -EBUSY अगर resource
 *         is still in use. Hardware specअगरic errors also possible.
 */
पूर्णांक vme_dma_list_मुक्त(काष्ठा vme_dma_list *list)
अणु
	काष्ठा vme_bridge *bridge = list->parent->parent;
	पूर्णांक retval;

	अगर (!bridge->dma_list_empty) अणु
		prपूर्णांकk(KERN_WARNING "Emptying of Link Lists not supported\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!mutex_trylock(&list->mtx)) अणु
		prपूर्णांकk(KERN_ERR "Link List in use\n");
		वापस -EBUSY;
	पूर्ण

	/*
	 * Empty out all of the entries from the DMA list. We need to go to the
	 * low level driver as DMA entries are driver specअगरic.
	 */
	retval = bridge->dma_list_empty(list);
	अगर (retval) अणु
		prपूर्णांकk(KERN_ERR "Unable to empty link-list entries\n");
		mutex_unlock(&list->mtx);
		वापस retval;
	पूर्ण
	mutex_unlock(&list->mtx);
	kमुक्त(list);

	वापस retval;
पूर्ण
EXPORT_SYMBOL(vme_dma_list_मुक्त);

/**
 * vme_dma_मुक्त - Free a VME DMA resource.
 * @resource: Poपूर्णांकer to VME DMA resource.
 *
 * Free the provided DMA resource so that it may be पुनः_स्मृतिated.
 *
 * Return: Zero on success, -EINVAL on invalid VME resource, -EBUSY अगर resource
 *         is still active.
 */
पूर्णांक vme_dma_मुक्त(काष्ठा vme_resource *resource)
अणु
	काष्ठा vme_dma_resource *ctrlr;

	अगर (resource->type != VME_DMA) अणु
		prपूर्णांकk(KERN_ERR "Not a DMA resource\n");
		वापस -EINVAL;
	पूर्ण

	ctrlr = list_entry(resource->entry, काष्ठा vme_dma_resource, list);

	अगर (!mutex_trylock(&ctrlr->mtx)) अणु
		prपूर्णांकk(KERN_ERR "Resource busy, can't free\n");
		वापस -EBUSY;
	पूर्ण

	अगर (!(list_empty(&ctrlr->pending) && list_empty(&ctrlr->running))) अणु
		prपूर्णांकk(KERN_WARNING "Resource still processing transfers\n");
		mutex_unlock(&ctrlr->mtx);
		वापस -EBUSY;
	पूर्ण

	ctrlr->locked = 0;

	mutex_unlock(&ctrlr->mtx);

	kमुक्त(resource);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(vme_dma_मुक्त);

व्योम vme_bus_error_handler(काष्ठा vme_bridge *bridge,
			   अचिन्हित दीर्घ दीर्घ address, पूर्णांक am)
अणु
	काष्ठा list_head *handler_pos = शून्य;
	काष्ठा vme_error_handler *handler;
	पूर्णांक handler_triggered = 0;
	u32 aspace = vme_get_aspace(am);

	list_क्रम_each(handler_pos, &bridge->vme_error_handlers) अणु
		handler = list_entry(handler_pos, काष्ठा vme_error_handler,
				     list);
		अगर ((aspace == handler->aspace) &&
		    (address >= handler->start) &&
		    (address < handler->end)) अणु
			अगर (!handler->num_errors)
				handler->first_error = address;
			अगर (handler->num_errors != अच_पूर्णांक_उच्च)
				handler->num_errors++;
			handler_triggered = 1;
		पूर्ण
	पूर्ण

	अगर (!handler_triggered)
		dev_err(bridge->parent,
			"Unhandled VME access error at address 0x%llx\n",
			address);
पूर्ण
EXPORT_SYMBOL(vme_bus_error_handler);

काष्ठा vme_error_handler *vme_रेजिस्टर_error_handler(
	काष्ठा vme_bridge *bridge, u32 aspace,
	अचिन्हित दीर्घ दीर्घ address, माप_प्रकार len)
अणु
	काष्ठा vme_error_handler *handler;

	handler = kदो_स्मृति(माप(*handler), GFP_ATOMIC);
	अगर (!handler)
		वापस शून्य;

	handler->aspace = aspace;
	handler->start = address;
	handler->end = address + len;
	handler->num_errors = 0;
	handler->first_error = 0;
	list_add_tail(&handler->list, &bridge->vme_error_handlers);

	वापस handler;
पूर्ण
EXPORT_SYMBOL(vme_रेजिस्टर_error_handler);

व्योम vme_unरेजिस्टर_error_handler(काष्ठा vme_error_handler *handler)
अणु
	list_del(&handler->list);
	kमुक्त(handler);
पूर्ण
EXPORT_SYMBOL(vme_unरेजिस्टर_error_handler);

व्योम vme_irq_handler(काष्ठा vme_bridge *bridge, पूर्णांक level, पूर्णांक statid)
अणु
	व्योम (*call)(पूर्णांक, पूर्णांक, व्योम *);
	व्योम *priv_data;

	call = bridge->irq[level - 1].callback[statid].func;
	priv_data = bridge->irq[level - 1].callback[statid].priv_data;
	अगर (call)
		call(level, statid, priv_data);
	अन्यथा
		prपूर्णांकk(KERN_WARNING "Spurious VME interrupt, level:%x, vector:%x\n",
		       level, statid);
पूर्ण
EXPORT_SYMBOL(vme_irq_handler);

/**
 * vme_irq_request - Request a specअगरic VME पूर्णांकerrupt.
 * @vdev: Poपूर्णांकer to VME device काष्ठा vme_dev asचिन्हित to driver instance.
 * @level: Interrupt priority being requested.
 * @statid: Interrupt vector being requested.
 * @callback: Poपूर्णांकer to callback function called when VME पूर्णांकerrupt/vector
 *            received.
 * @priv_data: Generic poपूर्णांकer that will be passed to the callback function.
 *
 * Request callback to be attached as a handler क्रम VME पूर्णांकerrupts with provided
 * level and statid.
 *
 * Return: Zero on success, -EINVAL on invalid vme device, level or अगर the
 *         function is not supported, -EBUSY अगर the level/statid combination is
 *         alपढ़ोy in use. Hardware specअगरic errors also possible.
 */
पूर्णांक vme_irq_request(काष्ठा vme_dev *vdev, पूर्णांक level, पूर्णांक statid,
	व्योम (*callback)(पूर्णांक, पूर्णांक, व्योम *),
	व्योम *priv_data)
अणु
	काष्ठा vme_bridge *bridge;

	bridge = vdev->bridge;
	अगर (!bridge) अणु
		prपूर्णांकk(KERN_ERR "Can't find VME bus\n");
		वापस -EINVAL;
	पूर्ण

	अगर ((level < 1) || (level > 7)) अणु
		prपूर्णांकk(KERN_ERR "Invalid interrupt level\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!bridge->irq_set) अणु
		prपूर्णांकk(KERN_ERR "Configuring interrupts not supported\n");
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&bridge->irq_mtx);

	अगर (bridge->irq[level - 1].callback[statid].func) अणु
		mutex_unlock(&bridge->irq_mtx);
		prपूर्णांकk(KERN_WARNING "VME Interrupt already taken\n");
		वापस -EBUSY;
	पूर्ण

	bridge->irq[level - 1].count++;
	bridge->irq[level - 1].callback[statid].priv_data = priv_data;
	bridge->irq[level - 1].callback[statid].func = callback;

	/* Enable IRQ level */
	bridge->irq_set(bridge, level, 1, 1);

	mutex_unlock(&bridge->irq_mtx);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(vme_irq_request);

/**
 * vme_irq_मुक्त - Free a VME पूर्णांकerrupt.
 * @vdev: Poपूर्णांकer to VME device काष्ठा vme_dev asचिन्हित to driver instance.
 * @level: Interrupt priority of पूर्णांकerrupt being मुक्तd.
 * @statid: Interrupt vector of पूर्णांकerrupt being मुक्तd.
 *
 * Remove previously attached callback from VME पूर्णांकerrupt priority/vector.
 */
व्योम vme_irq_मुक्त(काष्ठा vme_dev *vdev, पूर्णांक level, पूर्णांक statid)
अणु
	काष्ठा vme_bridge *bridge;

	bridge = vdev->bridge;
	अगर (!bridge) अणु
		prपूर्णांकk(KERN_ERR "Can't find VME bus\n");
		वापस;
	पूर्ण

	अगर ((level < 1) || (level > 7)) अणु
		prपूर्णांकk(KERN_ERR "Invalid interrupt level\n");
		वापस;
	पूर्ण

	अगर (!bridge->irq_set) अणु
		prपूर्णांकk(KERN_ERR "Configuring interrupts not supported\n");
		वापस;
	पूर्ण

	mutex_lock(&bridge->irq_mtx);

	bridge->irq[level - 1].count--;

	/* Disable IRQ level अगर no more पूर्णांकerrupts attached at this level*/
	अगर (bridge->irq[level - 1].count == 0)
		bridge->irq_set(bridge, level, 0, 1);

	bridge->irq[level - 1].callback[statid].func = शून्य;
	bridge->irq[level - 1].callback[statid].priv_data = शून्य;

	mutex_unlock(&bridge->irq_mtx);
पूर्ण
EXPORT_SYMBOL(vme_irq_मुक्त);

/**
 * vme_irq_generate - Generate VME पूर्णांकerrupt.
 * @vdev: Poपूर्णांकer to VME device काष्ठा vme_dev asचिन्हित to driver instance.
 * @level: Interrupt priority at which to निश्चित the पूर्णांकerrupt.
 * @statid: Interrupt vector to associate with the पूर्णांकerrupt.
 *
 * Generate a VME पूर्णांकerrupt of the provided level and with the provided
 * statid.
 *
 * Return: Zero on success, -EINVAL on invalid vme device, level or अगर the
 *         function is not supported. Hardware specअगरic errors also possible.
 */
पूर्णांक vme_irq_generate(काष्ठा vme_dev *vdev, पूर्णांक level, पूर्णांक statid)
अणु
	काष्ठा vme_bridge *bridge;

	bridge = vdev->bridge;
	अगर (!bridge) अणु
		prपूर्णांकk(KERN_ERR "Can't find VME bus\n");
		वापस -EINVAL;
	पूर्ण

	अगर ((level < 1) || (level > 7)) अणु
		prपूर्णांकk(KERN_WARNING "Invalid interrupt level\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!bridge->irq_generate) अणु
		prपूर्णांकk(KERN_WARNING "Interrupt generation not supported\n");
		वापस -EINVAL;
	पूर्ण

	वापस bridge->irq_generate(bridge, level, statid);
पूर्ण
EXPORT_SYMBOL(vme_irq_generate);

/**
 * vme_lm_request - Request a VME location monitor
 * @vdev: Poपूर्णांकer to VME device काष्ठा vme_dev asचिन्हित to driver instance.
 *
 * Allocate a location monitor resource to the driver. A location monitor
 * allows the driver to monitor accesses to a contiguous number of
 * addresses on the VME bus.
 *
 * Return: Poपूर्णांकer to a VME resource on success or शून्य on failure.
 */
काष्ठा vme_resource *vme_lm_request(काष्ठा vme_dev *vdev)
अणु
	काष्ठा vme_bridge *bridge;
	काष्ठा list_head *lm_pos = शून्य;
	काष्ठा vme_lm_resource *allocated_lm = शून्य;
	काष्ठा vme_lm_resource *lm = शून्य;
	काष्ठा vme_resource *resource = शून्य;

	bridge = vdev->bridge;
	अगर (!bridge) अणु
		prपूर्णांकk(KERN_ERR "Can't find VME bus\n");
		जाओ err_bus;
	पूर्ण

	/* Loop through LM resources */
	list_क्रम_each(lm_pos, &bridge->lm_resources) अणु
		lm = list_entry(lm_pos,
			काष्ठा vme_lm_resource, list);
		अगर (!lm) अणु
			prपूर्णांकk(KERN_ERR "Registered NULL Location Monitor resource\n");
			जारी;
		पूर्ण

		/* Find an unlocked controller */
		mutex_lock(&lm->mtx);
		अगर (lm->locked == 0) अणु
			lm->locked = 1;
			mutex_unlock(&lm->mtx);
			allocated_lm = lm;
			अवरोध;
		पूर्ण
		mutex_unlock(&lm->mtx);
	पूर्ण

	/* Check to see अगर we found a resource */
	अगर (!allocated_lm)
		जाओ err_lm;

	resource = kदो_स्मृति(माप(*resource), GFP_KERNEL);
	अगर (!resource)
		जाओ err_alloc;

	resource->type = VME_LM;
	resource->entry = &allocated_lm->list;

	वापस resource;

err_alloc:
	/* Unlock image */
	mutex_lock(&lm->mtx);
	lm->locked = 0;
	mutex_unlock(&lm->mtx);
err_lm:
err_bus:
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(vme_lm_request);

/**
 * vme_lm_count - Determine number of VME Addresses monitored
 * @resource: Poपूर्णांकer to VME location monitor resource.
 *
 * The number of contiguous addresses monitored is hardware dependent.
 * Return the number of contiguous addresses monitored by the
 * location monitor.
 *
 * Return: Count of addresses monitored or -EINVAL when provided with an
 *	   invalid location monitor resource.
 */
पूर्णांक vme_lm_count(काष्ठा vme_resource *resource)
अणु
	काष्ठा vme_lm_resource *lm;

	अगर (resource->type != VME_LM) अणु
		prपूर्णांकk(KERN_ERR "Not a Location Monitor resource\n");
		वापस -EINVAL;
	पूर्ण

	lm = list_entry(resource->entry, काष्ठा vme_lm_resource, list);

	वापस lm->monitors;
पूर्ण
EXPORT_SYMBOL(vme_lm_count);

/**
 * vme_lm_set - Configure location monitor
 * @resource: Poपूर्णांकer to VME location monitor resource.
 * @lm_base: Base address to monitor.
 * @aspace: VME address space to monitor.
 * @cycle: VME bus cycle type to monitor.
 *
 * Set the base address, address space and cycle type of accesses to be
 * monitored by the location monitor.
 *
 * Return: Zero on success, -EINVAL when provided with an invalid location
 *	   monitor resource or function is not supported. Hardware specअगरic
 *	   errors may also be वापसed.
 */
पूर्णांक vme_lm_set(काष्ठा vme_resource *resource, अचिन्हित दीर्घ दीर्घ lm_base,
	u32 aspace, u32 cycle)
अणु
	काष्ठा vme_bridge *bridge = find_bridge(resource);
	काष्ठा vme_lm_resource *lm;

	अगर (resource->type != VME_LM) अणु
		prपूर्णांकk(KERN_ERR "Not a Location Monitor resource\n");
		वापस -EINVAL;
	पूर्ण

	lm = list_entry(resource->entry, काष्ठा vme_lm_resource, list);

	अगर (!bridge->lm_set) अणु
		prपूर्णांकk(KERN_ERR "vme_lm_set not supported\n");
		वापस -EINVAL;
	पूर्ण

	वापस bridge->lm_set(lm, lm_base, aspace, cycle);
पूर्ण
EXPORT_SYMBOL(vme_lm_set);

/**
 * vme_lm_get - Retrieve location monitor settings
 * @resource: Poपूर्णांकer to VME location monitor resource.
 * @lm_base: Poपूर्णांकer used to output the base address monitored.
 * @aspace: Poपूर्णांकer used to output the address space monitored.
 * @cycle: Poपूर्णांकer used to output the VME bus cycle type monitored.
 *
 * Retrieve the base address, address space and cycle type of accesses to
 * be monitored by the location monitor.
 *
 * Return: Zero on success, -EINVAL when provided with an invalid location
 *	   monitor resource or function is not supported. Hardware specअगरic
 *	   errors may also be वापसed.
 */
पूर्णांक vme_lm_get(काष्ठा vme_resource *resource, अचिन्हित दीर्घ दीर्घ *lm_base,
	u32 *aspace, u32 *cycle)
अणु
	काष्ठा vme_bridge *bridge = find_bridge(resource);
	काष्ठा vme_lm_resource *lm;

	अगर (resource->type != VME_LM) अणु
		prपूर्णांकk(KERN_ERR "Not a Location Monitor resource\n");
		वापस -EINVAL;
	पूर्ण

	lm = list_entry(resource->entry, काष्ठा vme_lm_resource, list);

	अगर (!bridge->lm_get) अणु
		prपूर्णांकk(KERN_ERR "vme_lm_get not supported\n");
		वापस -EINVAL;
	पूर्ण

	वापस bridge->lm_get(lm, lm_base, aspace, cycle);
पूर्ण
EXPORT_SYMBOL(vme_lm_get);

/**
 * vme_lm_attach - Provide callback क्रम location monitor address
 * @resource: Poपूर्णांकer to VME location monitor resource.
 * @monitor: Offset to which callback should be attached.
 * @callback: Poपूर्णांकer to callback function called when triggered.
 * @data: Generic poपूर्णांकer that will be passed to the callback function.
 *
 * Attach a callback to the specअगरiced offset पूर्णांकo the location monitors
 * monitored addresses. A generic poपूर्णांकer is provided to allow data to be
 * passed to the callback when called.
 *
 * Return: Zero on success, -EINVAL when provided with an invalid location
 *	   monitor resource or function is not supported. Hardware specअगरic
 *	   errors may also be वापसed.
 */
पूर्णांक vme_lm_attach(काष्ठा vme_resource *resource, पूर्णांक monitor,
	व्योम (*callback)(व्योम *), व्योम *data)
अणु
	काष्ठा vme_bridge *bridge = find_bridge(resource);
	काष्ठा vme_lm_resource *lm;

	अगर (resource->type != VME_LM) अणु
		prपूर्णांकk(KERN_ERR "Not a Location Monitor resource\n");
		वापस -EINVAL;
	पूर्ण

	lm = list_entry(resource->entry, काष्ठा vme_lm_resource, list);

	अगर (!bridge->lm_attach) अणु
		prपूर्णांकk(KERN_ERR "vme_lm_attach not supported\n");
		वापस -EINVAL;
	पूर्ण

	वापस bridge->lm_attach(lm, monitor, callback, data);
पूर्ण
EXPORT_SYMBOL(vme_lm_attach);

/**
 * vme_lm_detach - Remove callback क्रम location monitor address
 * @resource: Poपूर्णांकer to VME location monitor resource.
 * @monitor: Offset to which callback should be हटाओd.
 *
 * Remove the callback associated with the specअगरiced offset पूर्णांकo the
 * location monitors monitored addresses.
 *
 * Return: Zero on success, -EINVAL when provided with an invalid location
 *	   monitor resource or function is not supported. Hardware specअगरic
 *	   errors may also be वापसed.
 */
पूर्णांक vme_lm_detach(काष्ठा vme_resource *resource, पूर्णांक monitor)
अणु
	काष्ठा vme_bridge *bridge = find_bridge(resource);
	काष्ठा vme_lm_resource *lm;

	अगर (resource->type != VME_LM) अणु
		prपूर्णांकk(KERN_ERR "Not a Location Monitor resource\n");
		वापस -EINVAL;
	पूर्ण

	lm = list_entry(resource->entry, काष्ठा vme_lm_resource, list);

	अगर (!bridge->lm_detach) अणु
		prपूर्णांकk(KERN_ERR "vme_lm_detach not supported\n");
		वापस -EINVAL;
	पूर्ण

	वापस bridge->lm_detach(lm, monitor);
पूर्ण
EXPORT_SYMBOL(vme_lm_detach);

/**
 * vme_lm_मुक्त - Free allocated VME location monitor
 * @resource: Poपूर्णांकer to VME location monitor resource.
 *
 * Free allocation of a VME location monitor.
 *
 * WARNING: This function currently expects that any callbacks that have
 *          been attached to the location monitor have been हटाओd.
 *
 * Return: Zero on success, -EINVAL when provided with an invalid location
 *	   monitor resource.
 */
व्योम vme_lm_मुक्त(काष्ठा vme_resource *resource)
अणु
	काष्ठा vme_lm_resource *lm;

	अगर (resource->type != VME_LM) अणु
		prपूर्णांकk(KERN_ERR "Not a Location Monitor resource\n");
		वापस;
	पूर्ण

	lm = list_entry(resource->entry, काष्ठा vme_lm_resource, list);

	mutex_lock(&lm->mtx);

	/* XXX
	 * Check to see that there aren't any callbacks still attached, अगर
	 * there are we should probably be detaching them!
	 */

	lm->locked = 0;

	mutex_unlock(&lm->mtx);

	kमुक्त(resource);
पूर्ण
EXPORT_SYMBOL(vme_lm_मुक्त);

/**
 * vme_slot_num - Retrieve slot ID
 * @vdev: Poपूर्णांकer to VME device काष्ठा vme_dev asचिन्हित to driver instance.
 *
 * Retrieve the slot ID associated with the provided VME device.
 *
 * Return: The slot ID on success, -EINVAL अगर VME bridge cannot be determined
 *         or the function is not supported. Hardware specअगरic errors may also
 *         be वापसed.
 */
पूर्णांक vme_slot_num(काष्ठा vme_dev *vdev)
अणु
	काष्ठा vme_bridge *bridge;

	bridge = vdev->bridge;
	अगर (!bridge) अणु
		prपूर्णांकk(KERN_ERR "Can't find VME bus\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!bridge->slot_get) अणु
		prपूर्णांकk(KERN_WARNING "vme_slot_num not supported\n");
		वापस -EINVAL;
	पूर्ण

	वापस bridge->slot_get(bridge);
पूर्ण
EXPORT_SYMBOL(vme_slot_num);

/**
 * vme_bus_num - Retrieve bus number
 * @vdev: Poपूर्णांकer to VME device काष्ठा vme_dev asचिन्हित to driver instance.
 *
 * Retrieve the bus क्रमागतeration associated with the provided VME device.
 *
 * Return: The bus number on success, -EINVAL अगर VME bridge cannot be
 *         determined.
 */
पूर्णांक vme_bus_num(काष्ठा vme_dev *vdev)
अणु
	काष्ठा vme_bridge *bridge;

	bridge = vdev->bridge;
	अगर (!bridge) अणु
		pr_err("Can't find VME bus\n");
		वापस -EINVAL;
	पूर्ण

	वापस bridge->num;
पूर्ण
EXPORT_SYMBOL(vme_bus_num);

/* - Bridge Registration --------------------------------------------------- */

अटल व्योम vme_dev_release(काष्ठा device *dev)
अणु
	kमुक्त(dev_to_vme_dev(dev));
पूर्ण

/* Common bridge initialization */
काष्ठा vme_bridge *vme_init_bridge(काष्ठा vme_bridge *bridge)
अणु
	INIT_LIST_HEAD(&bridge->vme_error_handlers);
	INIT_LIST_HEAD(&bridge->master_resources);
	INIT_LIST_HEAD(&bridge->slave_resources);
	INIT_LIST_HEAD(&bridge->dma_resources);
	INIT_LIST_HEAD(&bridge->lm_resources);
	mutex_init(&bridge->irq_mtx);

	वापस bridge;
पूर्ण
EXPORT_SYMBOL(vme_init_bridge);

पूर्णांक vme_रेजिस्टर_bridge(काष्ठा vme_bridge *bridge)
अणु
	पूर्णांक i;
	पूर्णांक ret = -1;

	mutex_lock(&vme_buses_lock);
	क्रम (i = 0; i < माप(vme_bus_numbers) * 8; i++) अणु
		अगर ((vme_bus_numbers & (1 << i)) == 0) अणु
			vme_bus_numbers |= (1 << i);
			bridge->num = i;
			INIT_LIST_HEAD(&bridge->devices);
			list_add_tail(&bridge->bus_list, &vme_bus_list);
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&vme_buses_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(vme_रेजिस्टर_bridge);

व्योम vme_unरेजिस्टर_bridge(काष्ठा vme_bridge *bridge)
अणु
	काष्ठा vme_dev *vdev;
	काष्ठा vme_dev *पंचांगp;

	mutex_lock(&vme_buses_lock);
	vme_bus_numbers &= ~(1 << bridge->num);
	list_क्रम_each_entry_safe(vdev, पंचांगp, &bridge->devices, bridge_list) अणु
		list_del(&vdev->drv_list);
		list_del(&vdev->bridge_list);
		device_unरेजिस्टर(&vdev->dev);
	पूर्ण
	list_del(&bridge->bus_list);
	mutex_unlock(&vme_buses_lock);
पूर्ण
EXPORT_SYMBOL(vme_unरेजिस्टर_bridge);

/* - Driver Registration --------------------------------------------------- */

अटल पूर्णांक __vme_रेजिस्टर_driver_bus(काष्ठा vme_driver *drv,
	काष्ठा vme_bridge *bridge, अचिन्हित पूर्णांक ndevs)
अणु
	पूर्णांक err;
	अचिन्हित पूर्णांक i;
	काष्ठा vme_dev *vdev;
	काष्ठा vme_dev *पंचांगp;

	क्रम (i = 0; i < ndevs; i++) अणु
		vdev = kzalloc(माप(*vdev), GFP_KERNEL);
		अगर (!vdev) अणु
			err = -ENOMEM;
			जाओ err_devalloc;
		पूर्ण
		vdev->num = i;
		vdev->bridge = bridge;
		vdev->dev.platक्रमm_data = drv;
		vdev->dev.release = vme_dev_release;
		vdev->dev.parent = bridge->parent;
		vdev->dev.bus = &vme_bus_type;
		dev_set_name(&vdev->dev, "%s.%u-%u", drv->name, bridge->num,
			vdev->num);

		err = device_रेजिस्टर(&vdev->dev);
		अगर (err)
			जाओ err_reg;

		अगर (vdev->dev.platक्रमm_data) अणु
			list_add_tail(&vdev->drv_list, &drv->devices);
			list_add_tail(&vdev->bridge_list, &bridge->devices);
		पूर्ण अन्यथा
			device_unरेजिस्टर(&vdev->dev);
	पूर्ण
	वापस 0;

err_reg:
	put_device(&vdev->dev);
err_devalloc:
	list_क्रम_each_entry_safe(vdev, पंचांगp, &drv->devices, drv_list) अणु
		list_del(&vdev->drv_list);
		list_del(&vdev->bridge_list);
		device_unरेजिस्टर(&vdev->dev);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक __vme_रेजिस्टर_driver(काष्ठा vme_driver *drv, अचिन्हित पूर्णांक ndevs)
अणु
	काष्ठा vme_bridge *bridge;
	पूर्णांक err = 0;

	mutex_lock(&vme_buses_lock);
	list_क्रम_each_entry(bridge, &vme_bus_list, bus_list) अणु
		/*
		 * This cannot cause trouble as we alपढ़ोy have vme_buses_lock
		 * and अगर the bridge is हटाओd, it will have to go through
		 * vme_unरेजिस्टर_bridge() to करो it (which calls हटाओ() on
		 * the bridge which in turn tries to acquire vme_buses_lock and
		 * will have to रुको).
		 */
		err = __vme_रेजिस्टर_driver_bus(drv, bridge, ndevs);
		अगर (err)
			अवरोध;
	पूर्ण
	mutex_unlock(&vme_buses_lock);
	वापस err;
पूर्ण

/**
 * vme_रेजिस्टर_driver - Register a VME driver
 * @drv: Poपूर्णांकer to VME driver काष्ठाure to रेजिस्टर.
 * @ndevs: Maximum number of devices to allow to be क्रमागतerated.
 *
 * Register a VME device driver with the VME subप्रणाली.
 *
 * Return: Zero on success, error value on registration failure.
 */
पूर्णांक vme_रेजिस्टर_driver(काष्ठा vme_driver *drv, अचिन्हित पूर्णांक ndevs)
अणु
	पूर्णांक err;

	drv->driver.name = drv->name;
	drv->driver.bus = &vme_bus_type;
	INIT_LIST_HEAD(&drv->devices);

	err = driver_रेजिस्टर(&drv->driver);
	अगर (err)
		वापस err;

	err = __vme_रेजिस्टर_driver(drv, ndevs);
	अगर (err)
		driver_unरेजिस्टर(&drv->driver);

	वापस err;
पूर्ण
EXPORT_SYMBOL(vme_रेजिस्टर_driver);

/**
 * vme_unरेजिस्टर_driver - Unरेजिस्टर a VME driver
 * @drv: Poपूर्णांकer to VME driver काष्ठाure to unरेजिस्टर.
 *
 * Unरेजिस्टर a VME device driver from the VME subप्रणाली.
 */
व्योम vme_unरेजिस्टर_driver(काष्ठा vme_driver *drv)
अणु
	काष्ठा vme_dev *dev, *dev_पंचांगp;

	mutex_lock(&vme_buses_lock);
	list_क्रम_each_entry_safe(dev, dev_पंचांगp, &drv->devices, drv_list) अणु
		list_del(&dev->drv_list);
		list_del(&dev->bridge_list);
		device_unरेजिस्टर(&dev->dev);
	पूर्ण
	mutex_unlock(&vme_buses_lock);

	driver_unरेजिस्टर(&drv->driver);
पूर्ण
EXPORT_SYMBOL(vme_unरेजिस्टर_driver);

/* - Bus Registration ------------------------------------------------------ */

अटल पूर्णांक vme_bus_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	काष्ठा vme_driver *vme_drv;

	vme_drv = container_of(drv, काष्ठा vme_driver, driver);

	अगर (dev->platक्रमm_data == vme_drv) अणु
		काष्ठा vme_dev *vdev = dev_to_vme_dev(dev);

		अगर (vme_drv->match && vme_drv->match(vdev))
			वापस 1;

		dev->platक्रमm_data = शून्य;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vme_bus_probe(काष्ठा device *dev)
अणु
	काष्ठा vme_driver *driver;
	काष्ठा vme_dev *vdev = dev_to_vme_dev(dev);

	driver = dev->platक्रमm_data;
	अगर (driver->probe)
		वापस driver->probe(vdev);

	वापस -ENODEV;
पूर्ण

अटल पूर्णांक vme_bus_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा vme_driver *driver;
	काष्ठा vme_dev *vdev = dev_to_vme_dev(dev);

	driver = dev->platक्रमm_data;
	अगर (driver->हटाओ)
		driver->हटाओ(vdev);

	वापस 0;
पूर्ण

काष्ठा bus_type vme_bus_type = अणु
	.name = "vme",
	.match = vme_bus_match,
	.probe = vme_bus_probe,
	.हटाओ = vme_bus_हटाओ,
पूर्ण;
EXPORT_SYMBOL(vme_bus_type);

अटल पूर्णांक __init vme_init(व्योम)
अणु
	वापस bus_रेजिस्टर(&vme_bus_type);
पूर्ण
subsys_initcall(vme_init);
