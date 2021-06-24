<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2004, 2013 Intel Corporation
 * Author: Naveen B S <naveen.b.s@पूर्णांकel.com>
 * Author: Rafael J. Wysocki <rafael.j.wysocki@पूर्णांकel.com>
 *
 * All rights reserved.
 *
 * ACPI based HotPlug driver that supports Memory Hotplug
 * This driver fields notअगरications from firmware क्रम memory add
 * and हटाओ operations and alerts the VM of the affected memory
 * ranges.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/memory.h>
#समावेश <linux/memory_hotplug.h>

#समावेश "internal.h"

#घोषणा ACPI_MEMORY_DEVICE_CLASS		"memory"
#घोषणा ACPI_MEMORY_DEVICE_HID			"PNP0C80"
#घोषणा ACPI_MEMORY_DEVICE_NAME			"Hotplug Mem Device"

अटल स्थिर काष्ठा acpi_device_id memory_device_ids[] = अणु
	अणुACPI_MEMORY_DEVICE_HID, 0पूर्ण,
	अणु"", 0पूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_ACPI_HOTPLUG_MEMORY

अटल पूर्णांक acpi_memory_device_add(काष्ठा acpi_device *device,
				  स्थिर काष्ठा acpi_device_id *not_used);
अटल व्योम acpi_memory_device_हटाओ(काष्ठा acpi_device *device);

अटल काष्ठा acpi_scan_handler memory_device_handler = अणु
	.ids = memory_device_ids,
	.attach = acpi_memory_device_add,
	.detach = acpi_memory_device_हटाओ,
	.hotplug = अणु
		.enabled = true,
	पूर्ण,
पूर्ण;

काष्ठा acpi_memory_info अणु
	काष्ठा list_head list;
	u64 start_addr;		/* Memory Range start physical addr */
	u64 length;		/* Memory Range length */
	अचिन्हित लघु caching;	/* memory cache attribute */
	अचिन्हित लघु ग_लिखो_protect;	/* memory पढ़ो/ग_लिखो attribute */
	अचिन्हित पूर्णांक enabled:1;
पूर्ण;

काष्ठा acpi_memory_device अणु
	काष्ठा acpi_device *device;
	काष्ठा list_head res_list;
पूर्ण;

अटल acpi_status
acpi_memory_get_resource(काष्ठा acpi_resource *resource, व्योम *context)
अणु
	काष्ठा acpi_memory_device *mem_device = context;
	काष्ठा acpi_resource_address64 address64;
	काष्ठा acpi_memory_info *info, *new;
	acpi_status status;

	status = acpi_resource_to_address64(resource, &address64);
	अगर (ACPI_FAILURE(status) ||
	    (address64.resource_type != ACPI_MEMORY_RANGE))
		वापस AE_OK;

	list_क्रम_each_entry(info, &mem_device->res_list, list) अणु
		/* Can we combine the resource range inक्रमmation? */
		अगर ((info->caching == address64.info.mem.caching) &&
		    (info->ग_लिखो_protect == address64.info.mem.ग_लिखो_protect) &&
		    (info->start_addr + info->length == address64.address.minimum)) अणु
			info->length += address64.address.address_length;
			वापस AE_OK;
		पूर्ण
	पूर्ण

	new = kzalloc(माप(काष्ठा acpi_memory_info), GFP_KERNEL);
	अगर (!new)
		वापस AE_ERROR;

	INIT_LIST_HEAD(&new->list);
	new->caching = address64.info.mem.caching;
	new->ग_लिखो_protect = address64.info.mem.ग_लिखो_protect;
	new->start_addr = address64.address.minimum;
	new->length = address64.address.address_length;
	list_add_tail(&new->list, &mem_device->res_list);

	वापस AE_OK;
पूर्ण

अटल व्योम
acpi_memory_मुक्त_device_resources(काष्ठा acpi_memory_device *mem_device)
अणु
	काष्ठा acpi_memory_info *info, *n;

	list_क्रम_each_entry_safe(info, n, &mem_device->res_list, list)
		kमुक्त(info);
	INIT_LIST_HEAD(&mem_device->res_list);
पूर्ण

अटल पूर्णांक
acpi_memory_get_device_resources(काष्ठा acpi_memory_device *mem_device)
अणु
	acpi_status status;

	अगर (!list_empty(&mem_device->res_list))
		वापस 0;

	status = acpi_walk_resources(mem_device->device->handle, METHOD_NAME__CRS,
				     acpi_memory_get_resource, mem_device);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_memory_मुक्त_device_resources(mem_device);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक acpi_memory_check_device(काष्ठा acpi_memory_device *mem_device)
अणु
	अचिन्हित दीर्घ दीर्घ current_status;

	/* Get device present/असलent inक्रमmation from the _STA */
	अगर (ACPI_FAILURE(acpi_evaluate_पूर्णांकeger(mem_device->device->handle,
					       METHOD_NAME__STA, शून्य,
					       &current_status)))
		वापस -ENODEV;
	/*
	 * Check क्रम device status. Device should be
	 * present/enabled/functioning.
	 */
	अगर (!((current_status & ACPI_STA_DEVICE_PRESENT)
	      && (current_status & ACPI_STA_DEVICE_ENABLED)
	      && (current_status & ACPI_STA_DEVICE_FUNCTIONING)))
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल पूर्णांक acpi_bind_memblk(काष्ठा memory_block *mem, व्योम *arg)
अणु
	वापस acpi_bind_one(&mem->dev, arg);
पूर्ण

अटल पूर्णांक acpi_bind_memory_blocks(काष्ठा acpi_memory_info *info,
				   काष्ठा acpi_device *adev)
अणु
	वापस walk_memory_blocks(info->start_addr, info->length, adev,
				  acpi_bind_memblk);
पूर्ण

अटल पूर्णांक acpi_unbind_memblk(काष्ठा memory_block *mem, व्योम *arg)
अणु
	acpi_unbind_one(&mem->dev);
	वापस 0;
पूर्ण

अटल व्योम acpi_unbind_memory_blocks(काष्ठा acpi_memory_info *info)
अणु
	walk_memory_blocks(info->start_addr, info->length, शून्य,
			   acpi_unbind_memblk);
पूर्ण

अटल पूर्णांक acpi_memory_enable_device(काष्ठा acpi_memory_device *mem_device)
अणु
	acpi_handle handle = mem_device->device->handle;
	पूर्णांक result, num_enabled = 0;
	काष्ठा acpi_memory_info *info;
	mhp_t mhp_flags = MHP_NONE;
	पूर्णांक node;

	node = acpi_get_node(handle);
	/*
	 * Tell the VM there is more memory here...
	 * Note: Assume that this function वापसs zero on success
	 * We करोn't have memory-hot-add rollback function,now.
	 * (i.e. memory-hot-हटाओ function)
	 */
	list_क्रम_each_entry(info, &mem_device->res_list, list) अणु
		अगर (info->enabled) अणु /* just sanity check...*/
			num_enabled++;
			जारी;
		पूर्ण
		/*
		 * If the memory block size is zero, please ignore it.
		 * Don't try to करो the following memory hotplug flowअक्षरt.
		 */
		अगर (!info->length)
			जारी;
		अगर (node < 0)
			node = memory_add_physaddr_to_nid(info->start_addr);

		अगर (mhp_supports_memmap_on_memory(info->length))
			mhp_flags |= MHP_MEMMAP_ON_MEMORY;
		result = __add_memory(node, info->start_addr, info->length,
				      mhp_flags);

		/*
		 * If the memory block has been used by the kernel, add_memory()
		 * वापसs -EEXIST. If add_memory() वापसs the other error, it
		 * means that this memory block is not used by the kernel.
		 */
		अगर (result && result != -EEXIST)
			जारी;

		result = acpi_bind_memory_blocks(info, mem_device->device);
		अगर (result) अणु
			acpi_unbind_memory_blocks(info);
			वापस -ENODEV;
		पूर्ण

		info->enabled = 1;

		/*
		 * Add num_enable even अगर add_memory() वापसs -EEXIST, so the
		 * device is bound to this driver.
		 */
		num_enabled++;
	पूर्ण
	अगर (!num_enabled) अणु
		dev_err(&mem_device->device->dev, "add_memory failed\n");
		वापस -EINVAL;
	पूर्ण
	/*
	 * Someबार the memory device will contain several memory blocks.
	 * When one memory block is hot-added to the प्रणाली memory, it will
	 * be regarded as a success.
	 * Otherwise अगर the last memory block can't be hot-added to the प्रणाली
	 * memory, it will be failure and the memory device can't be bound with
	 * driver.
	 */
	वापस 0;
पूर्ण

अटल व्योम acpi_memory_हटाओ_memory(काष्ठा acpi_memory_device *mem_device)
अणु
	acpi_handle handle = mem_device->device->handle;
	काष्ठा acpi_memory_info *info, *n;
	पूर्णांक nid = acpi_get_node(handle);

	list_क्रम_each_entry_safe(info, n, &mem_device->res_list, list) अणु
		अगर (!info->enabled)
			जारी;

		अगर (nid == NUMA_NO_NODE)
			nid = memory_add_physaddr_to_nid(info->start_addr);

		acpi_unbind_memory_blocks(info);
		__हटाओ_memory(nid, info->start_addr, info->length);
		list_del(&info->list);
		kमुक्त(info);
	पूर्ण
पूर्ण

अटल व्योम acpi_memory_device_मुक्त(काष्ठा acpi_memory_device *mem_device)
अणु
	अगर (!mem_device)
		वापस;

	acpi_memory_मुक्त_device_resources(mem_device);
	mem_device->device->driver_data = शून्य;
	kमुक्त(mem_device);
पूर्ण

अटल पूर्णांक acpi_memory_device_add(काष्ठा acpi_device *device,
				  स्थिर काष्ठा acpi_device_id *not_used)
अणु
	काष्ठा acpi_memory_device *mem_device;
	पूर्णांक result;

	अगर (!device)
		वापस -EINVAL;

	mem_device = kzalloc(माप(काष्ठा acpi_memory_device), GFP_KERNEL);
	अगर (!mem_device)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&mem_device->res_list);
	mem_device->device = device;
	प्र_लिखो(acpi_device_name(device), "%s", ACPI_MEMORY_DEVICE_NAME);
	प्र_लिखो(acpi_device_class(device), "%s", ACPI_MEMORY_DEVICE_CLASS);
	device->driver_data = mem_device;

	/* Get the range from the _CRS */
	result = acpi_memory_get_device_resources(mem_device);
	अगर (result) अणु
		device->driver_data = शून्य;
		kमुक्त(mem_device);
		वापस result;
	पूर्ण

	result = acpi_memory_check_device(mem_device);
	अगर (result) अणु
		acpi_memory_device_मुक्त(mem_device);
		वापस 0;
	पूर्ण

	result = acpi_memory_enable_device(mem_device);
	अगर (result) अणु
		dev_err(&device->dev, "acpi_memory_enable_device() error\n");
		acpi_memory_device_मुक्त(mem_device);
		वापस result;
	पूर्ण

	dev_dbg(&device->dev, "Memory device configured by ACPI\n");
	वापस 1;
पूर्ण

अटल व्योम acpi_memory_device_हटाओ(काष्ठा acpi_device *device)
अणु
	काष्ठा acpi_memory_device *mem_device;

	अगर (!device || !acpi_driver_data(device))
		वापस;

	mem_device = acpi_driver_data(device);
	acpi_memory_हटाओ_memory(mem_device);
	acpi_memory_device_मुक्त(mem_device);
पूर्ण

अटल bool __initdata acpi_no_memhotplug;

व्योम __init acpi_memory_hotplug_init(व्योम)
अणु
	अगर (acpi_no_memhotplug) अणु
		memory_device_handler.attach = शून्य;
		acpi_scan_add_handler(&memory_device_handler);
		वापस;
	पूर्ण
	acpi_scan_add_handler_with_hotplug(&memory_device_handler, "memory");
पूर्ण

अटल पूर्णांक __init disable_acpi_memory_hotplug(अक्षर *str)
अणु
	acpi_no_memhotplug = true;
	वापस 1;
पूर्ण
__setup("acpi_no_memhotplug", disable_acpi_memory_hotplug);

#अन्यथा

अटल काष्ठा acpi_scan_handler memory_device_handler = अणु
	.ids = memory_device_ids,
पूर्ण;

व्योम __init acpi_memory_hotplug_init(व्योम)
अणु
	acpi_scan_add_handler(&memory_device_handler);
पूर्ण

#पूर्ण_अगर /* CONFIG_ACPI_HOTPLUG_MEMORY */
