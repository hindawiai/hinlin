<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2016-2019 Intel Corporation. All rights reserved. */
#समावेश <linux/memremap.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/memory.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/pfn_t.h>
#समावेश <linux/slab.h>
#समावेश <linux/dax.h>
#समावेश <linux/fs.h>
#समावेश <linux/mm.h>
#समावेश <linux/mman.h>
#समावेश "dax-private.h"
#समावेश "bus.h"

/* Memory resource name used क्रम add_memory_driver_managed(). */
अटल स्थिर अक्षर *kmem_name;
/* Set अगर any memory will reमुख्य added when the driver will be unloaded. */
अटल bool any_hotहटाओ_failed;

अटल पूर्णांक dax_kmem_range(काष्ठा dev_dax *dev_dax, पूर्णांक i, काष्ठा range *r)
अणु
	काष्ठा dev_dax_range *dax_range = &dev_dax->ranges[i];
	काष्ठा range *range = &dax_range->range;

	/* memory-block align the hotplug range */
	r->start = ALIGN(range->start, memory_block_size_bytes());
	r->end = ALIGN_DOWN(range->end + 1, memory_block_size_bytes()) - 1;
	अगर (r->start >= r->end) अणु
		r->start = range->start;
		r->end = range->end;
		वापस -ENOSPC;
	पूर्ण
	वापस 0;
पूर्ण

काष्ठा dax_kmem_data अणु
	स्थिर अक्षर *res_name;
	काष्ठा resource *res[];
पूर्ण;

अटल पूर्णांक dev_dax_kmem_probe(काष्ठा dev_dax *dev_dax)
अणु
	काष्ठा device *dev = &dev_dax->dev;
	काष्ठा dax_kmem_data *data;
	पूर्णांक rc = -ENOMEM;
	पूर्णांक i, mapped = 0;
	पूर्णांक numa_node;

	/*
	 * Ensure good NUMA inक्रमmation क्रम the persistent memory.
	 * Without this check, there is a risk that slow memory
	 * could be mixed in a node with faster memory, causing
	 * unaव्योमable perक्रमmance issues.
	 */
	numa_node = dev_dax->target_node;
	अगर (numa_node < 0) अणु
		dev_warn(dev, "rejecting DAX region with invalid node: %d\n",
				numa_node);
		वापस -EINVAL;
	पूर्ण

	data = kzalloc(काष्ठा_size(data, res, dev_dax->nr_range), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->res_name = kstrdup(dev_name(dev), GFP_KERNEL);
	अगर (!data->res_name)
		जाओ err_res_name;

	क्रम (i = 0; i < dev_dax->nr_range; i++) अणु
		काष्ठा resource *res;
		काष्ठा range range;

		rc = dax_kmem_range(dev_dax, i, &range);
		अगर (rc) अणु
			dev_info(dev, "mapping%d: %#llx-%#llx too small after alignment\n",
					i, range.start, range.end);
			जारी;
		पूर्ण

		/* Region is permanently reserved अगर hotहटाओ fails. */
		res = request_mem_region(range.start, range_len(&range), data->res_name);
		अगर (!res) अणु
			dev_warn(dev, "mapping%d: %#llx-%#llx could not reserve region\n",
					i, range.start, range.end);
			/*
			 * Once some memory has been onlined we can't
			 * assume that it can be un-onlined safely.
			 */
			अगर (mapped)
				जारी;
			rc = -EBUSY;
			जाओ err_request_mem;
		पूर्ण
		data->res[i] = res;

		/*
		 * Set flags appropriate क्रम System RAM.  Leave ..._BUSY clear
		 * so that add_memory() can add a child resource.  Do not
		 * inherit flags from the parent since it may set new flags
		 * unknown to us that will अवरोध add_memory() below.
		 */
		res->flags = IORESOURCE_SYSTEM_RAM;

		/*
		 * Ensure that future kexec'd kernels will not treat
		 * this as RAM स्वतःmatically.
		 */
		rc = add_memory_driver_managed(numa_node, range.start,
				range_len(&range), kmem_name, MHP_NONE);

		अगर (rc) अणु
			dev_warn(dev, "mapping%d: %#llx-%#llx memory add failed\n",
					i, range.start, range.end);
			release_resource(res);
			kमुक्त(res);
			data->res[i] = शून्य;
			अगर (mapped)
				जारी;
			जाओ err_request_mem;
		पूर्ण
		mapped++;
	पूर्ण

	dev_set_drvdata(dev, data);

	वापस 0;

err_request_mem:
	kमुक्त(data->res_name);
err_res_name:
	kमुक्त(data);
	वापस rc;
पूर्ण

#अगर_घोषित CONFIG_MEMORY_HOTREMOVE
अटल व्योम dev_dax_kmem_हटाओ(काष्ठा dev_dax *dev_dax)
अणु
	पूर्णांक i, success = 0;
	काष्ठा device *dev = &dev_dax->dev;
	काष्ठा dax_kmem_data *data = dev_get_drvdata(dev);

	/*
	 * We have one shot क्रम removing memory, अगर some memory blocks were not
	 * offline prior to calling this function हटाओ_memory() will fail, and
	 * there is no way to hotहटाओ this memory until reboot because device
	 * unbind will succeed even अगर we वापस failure.
	 */
	क्रम (i = 0; i < dev_dax->nr_range; i++) अणु
		काष्ठा range range;
		पूर्णांक rc;

		rc = dax_kmem_range(dev_dax, i, &range);
		अगर (rc)
			जारी;

		rc = हटाओ_memory(dev_dax->target_node, range.start,
				range_len(&range));
		अगर (rc == 0) अणु
			release_resource(data->res[i]);
			kमुक्त(data->res[i]);
			data->res[i] = शून्य;
			success++;
			जारी;
		पूर्ण
		any_hotहटाओ_failed = true;
		dev_err(dev,
			"mapping%d: %#llx-%#llx cannot be hotremoved until the next reboot\n",
				i, range.start, range.end);
	पूर्ण

	अगर (success >= dev_dax->nr_range) अणु
		kमुक्त(data->res_name);
		kमुक्त(data);
		dev_set_drvdata(dev, शून्य);
	पूर्ण
पूर्ण
#अन्यथा
अटल व्योम dev_dax_kmem_हटाओ(काष्ठा dev_dax *dev_dax)
अणु
	/*
	 * Without hotहटाओ purposely leak the request_mem_region() क्रम the
	 * device-dax range and वापस '0' to ->हटाओ() attempts. The removal
	 * of the device from the driver always succeeds, but the region is
	 * permanently pinned as reserved by the unreleased
	 * request_mem_region().
	 */
	any_hotहटाओ_failed = true;
पूर्ण
#पूर्ण_अगर /* CONFIG_MEMORY_HOTREMOVE */

अटल काष्ठा dax_device_driver device_dax_kmem_driver = अणु
	.probe = dev_dax_kmem_probe,
	.हटाओ = dev_dax_kmem_हटाओ,
पूर्ण;

अटल पूर्णांक __init dax_kmem_init(व्योम)
अणु
	पूर्णांक rc;

	/* Resource name is permanently allocated अगर any hotहटाओ fails. */
	kmem_name = kstrdup_स्थिर("System RAM (kmem)", GFP_KERNEL);
	अगर (!kmem_name)
		वापस -ENOMEM;

	rc = dax_driver_रेजिस्टर(&device_dax_kmem_driver);
	अगर (rc)
		kमुक्त_स्थिर(kmem_name);
	वापस rc;
पूर्ण

अटल व्योम __निकास dax_kmem_निकास(व्योम)
अणु
	dax_driver_unरेजिस्टर(&device_dax_kmem_driver);
	अगर (!any_hotहटाओ_failed)
		kमुक्त_स्थिर(kmem_name);
पूर्ण

MODULE_AUTHOR("Intel Corporation");
MODULE_LICENSE("GPL v2");
module_init(dax_kmem_init);
module_निकास(dax_kmem_निकास);
MODULE_ALIAS_DAX_DEVICE(0);
