<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * fsl-mc object allocator driver
 *
 * Copyright (C) 2013-2016 Freescale Semiconductor, Inc.
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/msi.h>
#समावेश <linux/fsl/mc.h>

#समावेश "fsl-mc-private.h"

अटल bool __must_check fsl_mc_is_allocatable(काष्ठा fsl_mc_device *mc_dev)
अणु
	वापस is_fsl_mc_bus_dpbp(mc_dev) ||
	       is_fsl_mc_bus_dpmcp(mc_dev) ||
	       is_fsl_mc_bus_dpcon(mc_dev);
पूर्ण

/**
 * fsl_mc_resource_pool_add_device - add allocatable object to a resource
 * pool of a given fsl-mc bus
 *
 * @mc_bus: poपूर्णांकer to the fsl-mc bus
 * @pool_type: pool type
 * @mc_dev: poपूर्णांकer to allocatable fsl-mc device
 */
अटल पूर्णांक __must_check fsl_mc_resource_pool_add_device(काष्ठा fsl_mc_bus
								*mc_bus,
							क्रमागत fsl_mc_pool_type
								pool_type,
							काष्ठा fsl_mc_device
								*mc_dev)
अणु
	काष्ठा fsl_mc_resource_pool *res_pool;
	काष्ठा fsl_mc_resource *resource;
	काष्ठा fsl_mc_device *mc_bus_dev = &mc_bus->mc_dev;
	पूर्णांक error = -EINVAL;

	अगर (pool_type < 0 || pool_type >= FSL_MC_NUM_POOL_TYPES)
		जाओ out;
	अगर (!fsl_mc_is_allocatable(mc_dev))
		जाओ out;
	अगर (mc_dev->resource)
		जाओ out;

	res_pool = &mc_bus->resource_pools[pool_type];
	अगर (res_pool->type != pool_type)
		जाओ out;
	अगर (res_pool->mc_bus != mc_bus)
		जाओ out;

	mutex_lock(&res_pool->mutex);

	अगर (res_pool->max_count < 0)
		जाओ out_unlock;
	अगर (res_pool->मुक्त_count < 0 ||
	    res_pool->मुक्त_count > res_pool->max_count)
		जाओ out_unlock;

	resource = devm_kzalloc(&mc_bus_dev->dev, माप(*resource),
				GFP_KERNEL);
	अगर (!resource) अणु
		error = -ENOMEM;
		dev_err(&mc_bus_dev->dev,
			"Failed to allocate memory for fsl_mc_resource\n");
		जाओ out_unlock;
	पूर्ण

	resource->type = pool_type;
	resource->id = mc_dev->obj_desc.id;
	resource->data = mc_dev;
	resource->parent_pool = res_pool;
	INIT_LIST_HEAD(&resource->node);
	list_add_tail(&resource->node, &res_pool->मुक्त_list);
	mc_dev->resource = resource;
	res_pool->मुक्त_count++;
	res_pool->max_count++;
	error = 0;
out_unlock:
	mutex_unlock(&res_pool->mutex);
out:
	वापस error;
पूर्ण

/**
 * fsl_mc_resource_pool_हटाओ_device - हटाओ an allocatable device from a
 * resource pool
 *
 * @mc_dev: poपूर्णांकer to allocatable fsl-mc device
 *
 * It permanently हटाओs an allocatable fsl-mc device from the resource
 * pool. It's an error अगर the device is in use.
 */
अटल पूर्णांक __must_check fsl_mc_resource_pool_हटाओ_device(काष्ठा fsl_mc_device
								   *mc_dev)
अणु
	काष्ठा fsl_mc_device *mc_bus_dev;
	काष्ठा fsl_mc_bus *mc_bus;
	काष्ठा fsl_mc_resource_pool *res_pool;
	काष्ठा fsl_mc_resource *resource;
	पूर्णांक error = -EINVAL;

	अगर (!fsl_mc_is_allocatable(mc_dev))
		जाओ out;

	resource = mc_dev->resource;
	अगर (!resource || resource->data != mc_dev)
		जाओ out;

	mc_bus_dev = to_fsl_mc_device(mc_dev->dev.parent);
	mc_bus = to_fsl_mc_bus(mc_bus_dev);
	res_pool = resource->parent_pool;
	अगर (res_pool != &mc_bus->resource_pools[resource->type])
		जाओ out;

	mutex_lock(&res_pool->mutex);

	अगर (res_pool->max_count <= 0)
		जाओ out_unlock;
	अगर (res_pool->मुक्त_count <= 0 ||
	    res_pool->मुक्त_count > res_pool->max_count)
		जाओ out_unlock;

	/*
	 * If the device is currently allocated, its resource is not
	 * in the मुक्त list and thus, the device cannot be हटाओd.
	 */
	अगर (list_empty(&resource->node)) अणु
		error = -EBUSY;
		dev_err(&mc_bus_dev->dev,
			"Device %s cannot be removed from resource pool\n",
			dev_name(&mc_dev->dev));
		जाओ out_unlock;
	पूर्ण

	list_del_init(&resource->node);
	res_pool->मुक्त_count--;
	res_pool->max_count--;

	devm_kमुक्त(&mc_bus_dev->dev, resource);
	mc_dev->resource = शून्य;
	error = 0;
out_unlock:
	mutex_unlock(&res_pool->mutex);
out:
	वापस error;
पूर्ण

अटल स्थिर अक्षर *स्थिर fsl_mc_pool_type_strings[] = अणु
	[FSL_MC_POOL_DPMCP] = "dpmcp",
	[FSL_MC_POOL_DPBP] = "dpbp",
	[FSL_MC_POOL_DPCON] = "dpcon",
	[FSL_MC_POOL_IRQ] = "irq",
पूर्ण;

अटल पूर्णांक __must_check object_type_to_pool_type(स्थिर अक्षर *object_type,
						 क्रमागत fsl_mc_pool_type
								*pool_type)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(fsl_mc_pool_type_strings); i++) अणु
		अगर (म_भेद(object_type, fsl_mc_pool_type_strings[i]) == 0) अणु
			*pool_type = i;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

पूर्णांक __must_check fsl_mc_resource_allocate(काष्ठा fsl_mc_bus *mc_bus,
					  क्रमागत fsl_mc_pool_type pool_type,
					  काष्ठा fsl_mc_resource **new_resource)
अणु
	काष्ठा fsl_mc_resource_pool *res_pool;
	काष्ठा fsl_mc_resource *resource;
	काष्ठा fsl_mc_device *mc_bus_dev = &mc_bus->mc_dev;
	पूर्णांक error = -EINVAL;

	BUILD_BUG_ON(ARRAY_SIZE(fsl_mc_pool_type_strings) !=
		     FSL_MC_NUM_POOL_TYPES);

	*new_resource = शून्य;
	अगर (pool_type < 0 || pool_type >= FSL_MC_NUM_POOL_TYPES)
		जाओ out;

	res_pool = &mc_bus->resource_pools[pool_type];
	अगर (res_pool->mc_bus != mc_bus)
		जाओ out;

	mutex_lock(&res_pool->mutex);
	resource = list_first_entry_or_null(&res_pool->मुक्त_list,
					    काष्ठा fsl_mc_resource, node);

	अगर (!resource) अणु
		error = -ENXIO;
		dev_err(&mc_bus_dev->dev,
			"No more resources of type %s left\n",
			fsl_mc_pool_type_strings[pool_type]);
		जाओ out_unlock;
	पूर्ण

	अगर (resource->type != pool_type)
		जाओ out_unlock;
	अगर (resource->parent_pool != res_pool)
		जाओ out_unlock;
	अगर (res_pool->मुक्त_count <= 0 ||
	    res_pool->मुक्त_count > res_pool->max_count)
		जाओ out_unlock;

	list_del_init(&resource->node);

	res_pool->मुक्त_count--;
	error = 0;
out_unlock:
	mutex_unlock(&res_pool->mutex);
	*new_resource = resource;
out:
	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(fsl_mc_resource_allocate);

व्योम fsl_mc_resource_मुक्त(काष्ठा fsl_mc_resource *resource)
अणु
	काष्ठा fsl_mc_resource_pool *res_pool;

	res_pool = resource->parent_pool;
	अगर (resource->type != res_pool->type)
		वापस;

	mutex_lock(&res_pool->mutex);
	अगर (res_pool->मुक्त_count < 0 ||
	    res_pool->मुक्त_count >= res_pool->max_count)
		जाओ out_unlock;

	अगर (!list_empty(&resource->node))
		जाओ out_unlock;

	list_add_tail(&resource->node, &res_pool->मुक्त_list);
	res_pool->मुक्त_count++;
out_unlock:
	mutex_unlock(&res_pool->mutex);
पूर्ण
EXPORT_SYMBOL_GPL(fsl_mc_resource_मुक्त);

/**
 * fsl_mc_object_allocate - Allocates an fsl-mc object of the given
 * pool type from a given fsl-mc bus instance
 *
 * @mc_dev: fsl-mc device which is used in conjunction with the
 * allocated object
 * @pool_type: pool type
 * @new_mc_dev: poपूर्णांकer to area where the poपूर्णांकer to the allocated device
 * is to be वापसed
 *
 * Allocatable objects are always used in conjunction with some functional
 * device.  This function allocates an object of the specअगरied type from
 * the DPRC containing the functional device.
 *
 * NOTE: pool_type must be dअगरferent from FSL_MC_POOL_MCP, since MC
 * portals are allocated using fsl_mc_portal_allocate(), instead of
 * this function.
 */
पूर्णांक __must_check fsl_mc_object_allocate(काष्ठा fsl_mc_device *mc_dev,
					क्रमागत fsl_mc_pool_type pool_type,
					काष्ठा fsl_mc_device **new_mc_adev)
अणु
	काष्ठा fsl_mc_device *mc_bus_dev;
	काष्ठा fsl_mc_bus *mc_bus;
	काष्ठा fsl_mc_device *mc_adev;
	पूर्णांक error = -EINVAL;
	काष्ठा fsl_mc_resource *resource = शून्य;

	*new_mc_adev = शून्य;
	अगर (mc_dev->flags & FSL_MC_IS_DPRC)
		जाओ error;

	अगर (!dev_is_fsl_mc(mc_dev->dev.parent))
		जाओ error;

	अगर (pool_type == FSL_MC_POOL_DPMCP)
		जाओ error;

	mc_bus_dev = to_fsl_mc_device(mc_dev->dev.parent);
	mc_bus = to_fsl_mc_bus(mc_bus_dev);
	error = fsl_mc_resource_allocate(mc_bus, pool_type, &resource);
	अगर (error < 0)
		जाओ error;

	mc_adev = resource->data;
	अगर (!mc_adev) अणु
		error = -EINVAL;
		जाओ error;
	पूर्ण

	mc_adev->consumer_link = device_link_add(&mc_dev->dev,
						 &mc_adev->dev,
						 DL_FLAG_AUTOREMOVE_CONSUMER);
	अगर (!mc_adev->consumer_link) अणु
		error = -EINVAL;
		जाओ error;
	पूर्ण

	*new_mc_adev = mc_adev;
	वापस 0;
error:
	अगर (resource)
		fsl_mc_resource_मुक्त(resource);

	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(fsl_mc_object_allocate);

/**
 * fsl_mc_object_मुक्त - Returns an fsl-mc object to the resource
 * pool where it came from.
 * @mc_adev: Poपूर्णांकer to the fsl-mc device
 */
व्योम fsl_mc_object_मुक्त(काष्ठा fsl_mc_device *mc_adev)
अणु
	काष्ठा fsl_mc_resource *resource;

	resource = mc_adev->resource;
	अगर (resource->type == FSL_MC_POOL_DPMCP)
		वापस;
	अगर (resource->data != mc_adev)
		वापस;

	fsl_mc_resource_मुक्त(resource);

	mc_adev->consumer_link = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(fsl_mc_object_मुक्त);

/*
 * A DPRC and the devices in the DPRC all share the same GIC-ITS device
 * ID.  A block of IRQs is pre-allocated and मुख्यtained in a pool
 * from which devices can allocate them when needed.
 */

/*
 * Initialize the पूर्णांकerrupt pool associated with an fsl-mc bus.
 * It allocates a block of IRQs from the GIC-ITS.
 */
पूर्णांक fsl_mc_populate_irq_pool(काष्ठा fsl_mc_device *mc_bus_dev,
			     अचिन्हित पूर्णांक irq_count)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा msi_desc *msi_desc;
	काष्ठा fsl_mc_device_irq *irq_resources;
	काष्ठा fsl_mc_device_irq *mc_dev_irq;
	पूर्णांक error;
	काष्ठा fsl_mc_bus *mc_bus = to_fsl_mc_bus(mc_bus_dev);
	काष्ठा fsl_mc_resource_pool *res_pool =
			&mc_bus->resource_pools[FSL_MC_POOL_IRQ];

	/* करो nothing अगर the IRQ pool is alपढ़ोy populated */
	अगर (mc_bus->irq_resources)
		वापस 0;

	अगर (irq_count == 0 ||
	    irq_count > FSL_MC_IRQ_POOL_MAX_TOTAL_IRQS)
		वापस -EINVAL;

	error = fsl_mc_msi_करोमुख्य_alloc_irqs(&mc_bus_dev->dev, irq_count);
	अगर (error < 0)
		वापस error;

	irq_resources = devm_kसुस्मृति(&mc_bus_dev->dev,
				     irq_count, माप(*irq_resources),
				     GFP_KERNEL);
	अगर (!irq_resources) अणु
		error = -ENOMEM;
		जाओ cleanup_msi_irqs;
	पूर्ण

	क्रम (i = 0; i < irq_count; i++) अणु
		mc_dev_irq = &irq_resources[i];

		/*
		 * NOTE: This mc_dev_irq's MSI addr/value pair will be set
		 * by the fsl_mc_msi_ग_लिखो_msg() callback
		 */
		mc_dev_irq->resource.type = res_pool->type;
		mc_dev_irq->resource.data = mc_dev_irq;
		mc_dev_irq->resource.parent_pool = res_pool;
		INIT_LIST_HEAD(&mc_dev_irq->resource.node);
		list_add_tail(&mc_dev_irq->resource.node, &res_pool->मुक्त_list);
	पूर्ण

	क्रम_each_msi_entry(msi_desc, &mc_bus_dev->dev) अणु
		mc_dev_irq = &irq_resources[msi_desc->fsl_mc.msi_index];
		mc_dev_irq->msi_desc = msi_desc;
		mc_dev_irq->resource.id = msi_desc->irq;
	पूर्ण

	res_pool->max_count = irq_count;
	res_pool->मुक्त_count = irq_count;
	mc_bus->irq_resources = irq_resources;
	वापस 0;

cleanup_msi_irqs:
	fsl_mc_msi_करोमुख्य_मुक्त_irqs(&mc_bus_dev->dev);
	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(fsl_mc_populate_irq_pool);

/**
 * Tearकरोwn the पूर्णांकerrupt pool associated with an fsl-mc bus.
 * It मुक्तs the IRQs that were allocated to the pool, back to the GIC-ITS.
 */
व्योम fsl_mc_cleanup_irq_pool(काष्ठा fsl_mc_device *mc_bus_dev)
अणु
	काष्ठा fsl_mc_bus *mc_bus = to_fsl_mc_bus(mc_bus_dev);
	काष्ठा fsl_mc_resource_pool *res_pool =
			&mc_bus->resource_pools[FSL_MC_POOL_IRQ];

	अगर (!mc_bus->irq_resources)
		वापस;

	अगर (res_pool->max_count == 0)
		वापस;

	अगर (res_pool->मुक्त_count != res_pool->max_count)
		वापस;

	INIT_LIST_HEAD(&res_pool->मुक्त_list);
	res_pool->max_count = 0;
	res_pool->मुक्त_count = 0;
	mc_bus->irq_resources = शून्य;
	fsl_mc_msi_करोमुख्य_मुक्त_irqs(&mc_bus_dev->dev);
पूर्ण
EXPORT_SYMBOL_GPL(fsl_mc_cleanup_irq_pool);

/**
 * Allocate the IRQs required by a given fsl-mc device.
 */
पूर्णांक __must_check fsl_mc_allocate_irqs(काष्ठा fsl_mc_device *mc_dev)
अणु
	पूर्णांक i;
	पूर्णांक irq_count;
	पूर्णांक res_allocated_count = 0;
	पूर्णांक error = -EINVAL;
	काष्ठा fsl_mc_device_irq **irqs = शून्य;
	काष्ठा fsl_mc_bus *mc_bus;
	काष्ठा fsl_mc_resource_pool *res_pool;

	अगर (mc_dev->irqs)
		वापस -EINVAL;

	irq_count = mc_dev->obj_desc.irq_count;
	अगर (irq_count == 0)
		वापस -EINVAL;

	अगर (is_fsl_mc_bus_dprc(mc_dev))
		mc_bus = to_fsl_mc_bus(mc_dev);
	अन्यथा
		mc_bus = to_fsl_mc_bus(to_fsl_mc_device(mc_dev->dev.parent));

	अगर (!mc_bus->irq_resources)
		वापस -EINVAL;

	res_pool = &mc_bus->resource_pools[FSL_MC_POOL_IRQ];
	अगर (res_pool->मुक्त_count < irq_count) अणु
		dev_err(&mc_dev->dev,
			"Not able to allocate %u irqs for device\n", irq_count);
		वापस -ENOSPC;
	पूर्ण

	irqs = devm_kसुस्मृति(&mc_dev->dev, irq_count, माप(irqs[0]),
			    GFP_KERNEL);
	अगर (!irqs)
		वापस -ENOMEM;

	क्रम (i = 0; i < irq_count; i++) अणु
		काष्ठा fsl_mc_resource *resource;

		error = fsl_mc_resource_allocate(mc_bus, FSL_MC_POOL_IRQ,
						 &resource);
		अगर (error < 0)
			जाओ error_resource_alloc;

		irqs[i] = to_fsl_mc_irq(resource);
		res_allocated_count++;

		irqs[i]->mc_dev = mc_dev;
		irqs[i]->dev_irq_index = i;
	पूर्ण

	mc_dev->irqs = irqs;
	वापस 0;

error_resource_alloc:
	क्रम (i = 0; i < res_allocated_count; i++) अणु
		irqs[i]->mc_dev = शून्य;
		fsl_mc_resource_मुक्त(&irqs[i]->resource);
	पूर्ण

	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(fsl_mc_allocate_irqs);

/*
 * Frees the IRQs that were allocated क्रम an fsl-mc device.
 */
व्योम fsl_mc_मुक्त_irqs(काष्ठा fsl_mc_device *mc_dev)
अणु
	पूर्णांक i;
	पूर्णांक irq_count;
	काष्ठा fsl_mc_bus *mc_bus;
	काष्ठा fsl_mc_device_irq **irqs = mc_dev->irqs;

	अगर (!irqs)
		वापस;

	irq_count = mc_dev->obj_desc.irq_count;

	अगर (is_fsl_mc_bus_dprc(mc_dev))
		mc_bus = to_fsl_mc_bus(mc_dev);
	अन्यथा
		mc_bus = to_fsl_mc_bus(to_fsl_mc_device(mc_dev->dev.parent));

	अगर (!mc_bus->irq_resources)
		वापस;

	क्रम (i = 0; i < irq_count; i++) अणु
		irqs[i]->mc_dev = शून्य;
		fsl_mc_resource_मुक्त(&irqs[i]->resource);
	पूर्ण

	mc_dev->irqs = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(fsl_mc_मुक्त_irqs);

व्योम fsl_mc_init_all_resource_pools(काष्ठा fsl_mc_device *mc_bus_dev)
अणु
	पूर्णांक pool_type;
	काष्ठा fsl_mc_bus *mc_bus = to_fsl_mc_bus(mc_bus_dev);

	क्रम (pool_type = 0; pool_type < FSL_MC_NUM_POOL_TYPES; pool_type++) अणु
		काष्ठा fsl_mc_resource_pool *res_pool =
		    &mc_bus->resource_pools[pool_type];

		res_pool->type = pool_type;
		res_pool->max_count = 0;
		res_pool->मुक्त_count = 0;
		res_pool->mc_bus = mc_bus;
		INIT_LIST_HEAD(&res_pool->मुक्त_list);
		mutex_init(&res_pool->mutex);
	पूर्ण
पूर्ण

अटल व्योम fsl_mc_cleanup_resource_pool(काष्ठा fsl_mc_device *mc_bus_dev,
					 क्रमागत fsl_mc_pool_type pool_type)
अणु
	काष्ठा fsl_mc_resource *resource;
	काष्ठा fsl_mc_resource *next;
	काष्ठा fsl_mc_bus *mc_bus = to_fsl_mc_bus(mc_bus_dev);
	काष्ठा fsl_mc_resource_pool *res_pool =
					&mc_bus->resource_pools[pool_type];
	पूर्णांक मुक्त_count = 0;

	list_क्रम_each_entry_safe(resource, next, &res_pool->मुक्त_list, node) अणु
		मुक्त_count++;
		devm_kमुक्त(&mc_bus_dev->dev, resource);
	पूर्ण
पूर्ण

व्योम fsl_mc_cleanup_all_resource_pools(काष्ठा fsl_mc_device *mc_bus_dev)
अणु
	पूर्णांक pool_type;

	क्रम (pool_type = 0; pool_type < FSL_MC_NUM_POOL_TYPES; pool_type++)
		fsl_mc_cleanup_resource_pool(mc_bus_dev, pool_type);
पूर्ण

/**
 * fsl_mc_allocator_probe - callback invoked when an allocatable device is
 * being added to the प्रणाली
 */
अटल पूर्णांक fsl_mc_allocator_probe(काष्ठा fsl_mc_device *mc_dev)
अणु
	क्रमागत fsl_mc_pool_type pool_type;
	काष्ठा fsl_mc_device *mc_bus_dev;
	काष्ठा fsl_mc_bus *mc_bus;
	पूर्णांक error;

	अगर (!fsl_mc_is_allocatable(mc_dev))
		वापस -EINVAL;

	mc_bus_dev = to_fsl_mc_device(mc_dev->dev.parent);
	अगर (!dev_is_fsl_mc(&mc_bus_dev->dev))
		वापस -EINVAL;

	mc_bus = to_fsl_mc_bus(mc_bus_dev);
	error = object_type_to_pool_type(mc_dev->obj_desc.type, &pool_type);
	अगर (error < 0)
		वापस error;

	error = fsl_mc_resource_pool_add_device(mc_bus, pool_type, mc_dev);
	अगर (error < 0)
		वापस error;

	dev_dbg(&mc_dev->dev,
		"Allocatable fsl-mc device bound to fsl_mc_allocator driver");
	वापस 0;
पूर्ण

/**
 * fsl_mc_allocator_हटाओ - callback invoked when an allocatable device is
 * being हटाओd from the प्रणाली
 */
अटल पूर्णांक fsl_mc_allocator_हटाओ(काष्ठा fsl_mc_device *mc_dev)
अणु
	पूर्णांक error;

	अगर (!fsl_mc_is_allocatable(mc_dev))
		वापस -EINVAL;

	अगर (mc_dev->resource) अणु
		error = fsl_mc_resource_pool_हटाओ_device(mc_dev);
		अगर (error < 0)
			वापस error;
	पूर्ण

	dev_dbg(&mc_dev->dev,
		"Allocatable fsl-mc device unbound from fsl_mc_allocator driver");
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fsl_mc_device_id match_id_table[] = अणु
	अणु
	 .venकरोr = FSL_MC_VENDOR_FREESCALE,
	 .obj_type = "dpbp",
	पूर्ण,
	अणु
	 .venकरोr = FSL_MC_VENDOR_FREESCALE,
	 .obj_type = "dpmcp",
	पूर्ण,
	अणु
	 .venकरोr = FSL_MC_VENDOR_FREESCALE,
	 .obj_type = "dpcon",
	पूर्ण,
	अणु.venकरोr = 0x0पूर्ण,
पूर्ण;

अटल काष्ठा fsl_mc_driver fsl_mc_allocator_driver = अणु
	.driver = अणु
		   .name = "fsl_mc_allocator",
		   .pm = शून्य,
		   पूर्ण,
	.match_id_table = match_id_table,
	.probe = fsl_mc_allocator_probe,
	.हटाओ = fsl_mc_allocator_हटाओ,
पूर्ण;

पूर्णांक __init fsl_mc_allocator_driver_init(व्योम)
अणु
	वापस fsl_mc_driver_रेजिस्टर(&fsl_mc_allocator_driver);
पूर्ण

व्योम fsl_mc_allocator_driver_निकास(व्योम)
अणु
	fsl_mc_driver_unरेजिस्टर(&fsl_mc_allocator_driver);
पूर्ण
