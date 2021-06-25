<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Freescale data path resource container (DPRC) driver
 *
 * Copyright (C) 2014-2016 Freescale Semiconductor, Inc.
 * Copyright 2019-2020 NXP
 * Author: German Rivera <German.Rivera@मुक्तscale.com>
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/msi.h>
#समावेश <linux/fsl/mc.h>

#समावेश "fsl-mc-private.h"

#घोषणा FSL_MC_DPRC_DRIVER_NAME    "fsl_mc_dprc"

काष्ठा fsl_mc_child_objs अणु
	पूर्णांक child_count;
	काष्ठा fsl_mc_obj_desc *child_array;
पूर्ण;

अटल bool fsl_mc_device_match(काष्ठा fsl_mc_device *mc_dev,
				काष्ठा fsl_mc_obj_desc *obj_desc)
अणु
	वापस mc_dev->obj_desc.id == obj_desc->id &&
	       म_भेद(mc_dev->obj_desc.type, obj_desc->type) == 0;
पूर्ण

अटल bool fsl_mc_obj_desc_is_allocatable(काष्ठा fsl_mc_obj_desc *obj)
अणु
	अगर (म_भेद(obj->type, "dpmcp") == 0 ||
	    म_भेद(obj->type, "dpcon") == 0 ||
	    म_भेद(obj->type, "dpbp") == 0)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल पूर्णांक __fsl_mc_device_हटाओ_अगर_not_in_mc(काष्ठा device *dev, व्योम *data)
अणु
	पूर्णांक i;
	काष्ठा fsl_mc_child_objs *objs;
	काष्ठा fsl_mc_device *mc_dev;

	mc_dev = to_fsl_mc_device(dev);
	objs = data;

	क्रम (i = 0; i < objs->child_count; i++) अणु
		काष्ठा fsl_mc_obj_desc *obj_desc = &objs->child_array[i];

		अगर (म_माप(obj_desc->type) != 0 &&
		    fsl_mc_device_match(mc_dev, obj_desc))
			अवरोध;
	पूर्ण

	अगर (i == objs->child_count)
		fsl_mc_device_हटाओ(mc_dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __fsl_mc_device_हटाओ(काष्ठा device *dev, व्योम *data)
अणु
	fsl_mc_device_हटाओ(to_fsl_mc_device(dev));
	वापस 0;
पूर्ण

/**
 * dprc_हटाओ_devices - Removes devices क्रम objects हटाओd from a DPRC
 *
 * @mc_bus_dev: poपूर्णांकer to the fsl-mc device that represents a DPRC object
 * @obj_desc_array: array of object descriptors क्रम child objects currently
 * present in the DPRC in the MC.
 * @num_child_objects_in_mc: number of entries in obj_desc_array
 *
 * Synchronizes the state of the Linux bus driver with the actual state of
 * the MC by removing devices that represent MC objects that have
 * been dynamically हटाओd in the physical DPRC.
 */
व्योम dprc_हटाओ_devices(काष्ठा fsl_mc_device *mc_bus_dev,
			 काष्ठा fsl_mc_obj_desc *obj_desc_array,
			 पूर्णांक num_child_objects_in_mc)
अणु
	अगर (num_child_objects_in_mc != 0) अणु
		/*
		 * Remove child objects that are in the DPRC in Linux,
		 * but not in the MC:
		 */
		काष्ठा fsl_mc_child_objs objs;

		objs.child_count = num_child_objects_in_mc;
		objs.child_array = obj_desc_array;
		device_क्रम_each_child(&mc_bus_dev->dev, &objs,
				      __fsl_mc_device_हटाओ_अगर_not_in_mc);
	पूर्ण अन्यथा अणु
		/*
		 * There are no child objects क्रम this DPRC in the MC.
		 * So, हटाओ all the child devices from Linux:
		 */
		device_क्रम_each_child(&mc_bus_dev->dev, शून्य,
				      __fsl_mc_device_हटाओ);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(dprc_हटाओ_devices);

अटल पूर्णांक __fsl_mc_device_match(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा fsl_mc_obj_desc *obj_desc = data;
	काष्ठा fsl_mc_device *mc_dev = to_fsl_mc_device(dev);

	वापस fsl_mc_device_match(mc_dev, obj_desc);
पूर्ण

काष्ठा fsl_mc_device *fsl_mc_device_lookup(काष्ठा fsl_mc_obj_desc *obj_desc,
					   काष्ठा fsl_mc_device *mc_bus_dev)
अणु
	काष्ठा device *dev;

	dev = device_find_child(&mc_bus_dev->dev, obj_desc,
				__fsl_mc_device_match);

	वापस dev ? to_fsl_mc_device(dev) : शून्य;
पूर्ण

/**
 * check_plugged_state_change - Check change in an MC object's plugged state
 *
 * @mc_dev: poपूर्णांकer to the fsl-mc device क्रम a given MC object
 * @obj_desc: poपूर्णांकer to the MC object's descriptor in the MC
 *
 * If the plugged state has changed from unplugged to plugged, the fsl-mc
 * device is bound to the corresponding device driver.
 * If the plugged state has changed from plugged to unplugged, the fsl-mc
 * device is unbound from the corresponding device driver.
 */
अटल व्योम check_plugged_state_change(काष्ठा fsl_mc_device *mc_dev,
				       काष्ठा fsl_mc_obj_desc *obj_desc)
अणु
	पूर्णांक error;
	u32 plugged_flag_at_mc =
			obj_desc->state & FSL_MC_OBJ_STATE_PLUGGED;

	अगर (plugged_flag_at_mc !=
	    (mc_dev->obj_desc.state & FSL_MC_OBJ_STATE_PLUGGED)) अणु
		अगर (plugged_flag_at_mc) अणु
			mc_dev->obj_desc.state |= FSL_MC_OBJ_STATE_PLUGGED;
			error = device_attach(&mc_dev->dev);
			अगर (error < 0) अणु
				dev_err(&mc_dev->dev,
					"device_attach() failed: %d\n",
					error);
			पूर्ण
		पूर्ण अन्यथा अणु
			mc_dev->obj_desc.state &= ~FSL_MC_OBJ_STATE_PLUGGED;
			device_release_driver(&mc_dev->dev);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम fsl_mc_obj_device_add(काष्ठा fsl_mc_device *mc_bus_dev,
				  काष्ठा fsl_mc_obj_desc *obj_desc)
अणु
	पूर्णांक error;
	काष्ठा fsl_mc_device *child_dev;

	/*
	 * Check अगर device is alपढ़ोy known to Linux:
	 */
	child_dev = fsl_mc_device_lookup(obj_desc, mc_bus_dev);
	अगर (child_dev) अणु
		check_plugged_state_change(child_dev, obj_desc);
		put_device(&child_dev->dev);
	पूर्ण अन्यथा अणु
		error = fsl_mc_device_add(obj_desc, शून्य, &mc_bus_dev->dev,
					  &child_dev);
		अगर (error < 0)
			वापस;
	पूर्ण
पूर्ण

/**
 * dprc_add_new_devices - Adds devices to the logical bus क्रम a DPRC
 *
 * @mc_bus_dev: poपूर्णांकer to the fsl-mc device that represents a DPRC object
 * @obj_desc_array: array of device descriptors क्रम child devices currently
 * present in the physical DPRC.
 * @num_child_objects_in_mc: number of entries in obj_desc_array
 *
 * Synchronizes the state of the Linux bus driver with the actual
 * state of the MC by adding objects that have been newly discovered
 * in the physical DPRC.
 */
अटल व्योम dprc_add_new_devices(काष्ठा fsl_mc_device *mc_bus_dev,
				 काष्ठा fsl_mc_obj_desc *obj_desc_array,
				 पूर्णांक num_child_objects_in_mc)
अणु
	पूर्णांक i;

	/* probe the allocable objects first */
	क्रम (i = 0; i < num_child_objects_in_mc; i++) अणु
		काष्ठा fsl_mc_obj_desc *obj_desc = &obj_desc_array[i];

		अगर (म_माप(obj_desc->type) > 0 &&
		    fsl_mc_obj_desc_is_allocatable(obj_desc))
			fsl_mc_obj_device_add(mc_bus_dev, obj_desc);
	पूर्ण

	क्रम (i = 0; i < num_child_objects_in_mc; i++) अणु
		काष्ठा fsl_mc_obj_desc *obj_desc = &obj_desc_array[i];

		अगर (म_माप(obj_desc->type) > 0 &&
		    !fsl_mc_obj_desc_is_allocatable(obj_desc))
			fsl_mc_obj_device_add(mc_bus_dev, obj_desc);
	पूर्ण
पूर्ण

/**
 * dprc_scan_objects - Discover objects in a DPRC
 *
 * @mc_bus_dev: poपूर्णांकer to the fsl-mc device that represents a DPRC object
 * @alloc_पूर्णांकerrupts: अगर true the function allocates the पूर्णांकerrupt pool,
 * otherwise the पूर्णांकerrupt allocation is delayed
 *
 * Detects objects added and हटाओd from a DPRC and synchronizes the
 * state of the Linux bus driver, MC by adding and removing
 * devices accordingly.
 * Two types of devices can be found in a DPRC: allocatable objects (e.g.,
 * dpbp, dpmcp) and non-allocatable devices (e.g., dprc, dpni).
 * All allocatable devices needed to be probed beक्रमe all non-allocatable
 * devices, to ensure that device drivers क्रम non-allocatable
 * devices can allocate any type of allocatable devices.
 * That is, we need to ensure that the corresponding resource pools are
 * populated beक्रमe they can get allocation requests from probe callbacks
 * of the device drivers क्रम the non-allocatable devices.
 */
पूर्णांक dprc_scan_objects(काष्ठा fsl_mc_device *mc_bus_dev,
		      bool alloc_पूर्णांकerrupts)
अणु
	पूर्णांक num_child_objects;
	पूर्णांक dprc_get_obj_failures;
	पूर्णांक error;
	अचिन्हित पूर्णांक irq_count = mc_bus_dev->obj_desc.irq_count;
	काष्ठा fsl_mc_obj_desc *child_obj_desc_array = शून्य;
	काष्ठा fsl_mc_bus *mc_bus = to_fsl_mc_bus(mc_bus_dev);

	error = dprc_get_obj_count(mc_bus_dev->mc_io,
				   0,
				   mc_bus_dev->mc_handle,
				   &num_child_objects);
	अगर (error < 0) अणु
		dev_err(&mc_bus_dev->dev, "dprc_get_obj_count() failed: %d\n",
			error);
		वापस error;
	पूर्ण

	अगर (num_child_objects != 0) अणु
		पूर्णांक i;

		child_obj_desc_array =
		    devm_kदो_स्मृति_array(&mc_bus_dev->dev, num_child_objects,
				       माप(*child_obj_desc_array),
				       GFP_KERNEL);
		अगर (!child_obj_desc_array)
			वापस -ENOMEM;

		/*
		 * Discover objects currently present in the physical DPRC:
		 */
		dprc_get_obj_failures = 0;
		क्रम (i = 0; i < num_child_objects; i++) अणु
			काष्ठा fsl_mc_obj_desc *obj_desc =
			    &child_obj_desc_array[i];

			error = dprc_get_obj(mc_bus_dev->mc_io,
					     0,
					     mc_bus_dev->mc_handle,
					     i, obj_desc);
			अगर (error < 0) अणु
				dev_err(&mc_bus_dev->dev,
					"dprc_get_obj(i=%d) failed: %d\n",
					i, error);
				/*
				 * Mark the obj entry as "invalid", by using the
				 * empty string as obj type:
				 */
				obj_desc->type[0] = '\0';
				obj_desc->id = error;
				dprc_get_obj_failures++;
				जारी;
			पूर्ण

			/*
			 * add a quirk क्रम all versions of dpsec < 4.0...none
			 * are coherent regardless of what the MC reports.
			 */
			अगर ((म_भेद(obj_desc->type, "dpseci") == 0) &&
			    (obj_desc->ver_major < 4))
				obj_desc->flags |=
					FSL_MC_OBJ_FLAG_NO_MEM_SHAREABILITY;

			irq_count += obj_desc->irq_count;
			dev_dbg(&mc_bus_dev->dev,
				"Discovered object: type %s, id %d\n",
				obj_desc->type, obj_desc->id);
		पूर्ण

		अगर (dprc_get_obj_failures != 0) अणु
			dev_err(&mc_bus_dev->dev,
				"%d out of %d devices could not be retrieved\n",
				dprc_get_obj_failures, num_child_objects);
		पूर्ण
	पूर्ण

	/*
	 * Allocate IRQ's beक्रमe binding the scanned devices with their
	 * respective drivers.
	 */
	अगर (dev_get_msi_करोमुख्य(&mc_bus_dev->dev)) अणु
		अगर (irq_count > FSL_MC_IRQ_POOL_MAX_TOTAL_IRQS) अणु
			dev_warn(&mc_bus_dev->dev,
				 "IRQs needed (%u) exceed IRQs preallocated (%u)\n",
				 irq_count, FSL_MC_IRQ_POOL_MAX_TOTAL_IRQS);
		पूर्ण

		अगर (alloc_पूर्णांकerrupts && !mc_bus->irq_resources) अणु
			error = fsl_mc_populate_irq_pool(mc_bus_dev,
					 FSL_MC_IRQ_POOL_MAX_TOTAL_IRQS);
			अगर (error < 0)
				वापस error;
		पूर्ण
	पूर्ण

	dprc_हटाओ_devices(mc_bus_dev, child_obj_desc_array,
			    num_child_objects);

	dprc_add_new_devices(mc_bus_dev, child_obj_desc_array,
			     num_child_objects);

	अगर (child_obj_desc_array)
		devm_kमुक्त(&mc_bus_dev->dev, child_obj_desc_array);

	वापस 0;
पूर्ण

/**
 * dprc_scan_container - Scans a physical DPRC and synchronizes Linux bus state
 *
 * @mc_bus_dev: poपूर्णांकer to the fsl-mc device that represents a DPRC object
 *
 * Scans the physical DPRC and synchronizes the state of the Linux
 * bus driver with the actual state of the MC by adding and removing
 * devices as appropriate.
 */
पूर्णांक dprc_scan_container(काष्ठा fsl_mc_device *mc_bus_dev,
			bool alloc_पूर्णांकerrupts)
अणु
	पूर्णांक error = 0;
	काष्ठा fsl_mc_bus *mc_bus = to_fsl_mc_bus(mc_bus_dev);

	fsl_mc_init_all_resource_pools(mc_bus_dev);

	/*
	 * Discover objects in the DPRC:
	 */
	mutex_lock(&mc_bus->scan_mutex);
	error = dprc_scan_objects(mc_bus_dev, alloc_पूर्णांकerrupts);
	mutex_unlock(&mc_bus->scan_mutex);

	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(dprc_scan_container);
/**
 * dprc_irq0_handler - Regular ISR क्रम DPRC पूर्णांकerrupt 0
 *
 * @irq: IRQ number of the पूर्णांकerrupt being handled
 * @arg: Poपूर्णांकer to device काष्ठाure
 */
अटल irqवापस_t dprc_irq0_handler(पूर्णांक irq_num, व्योम *arg)
अणु
	वापस IRQ_WAKE_THREAD;
पूर्ण

/**
 * dprc_irq0_handler_thपढ़ो - Handler thपढ़ो function क्रम DPRC पूर्णांकerrupt 0
 *
 * @irq: IRQ number of the पूर्णांकerrupt being handled
 * @arg: Poपूर्णांकer to device काष्ठाure
 */
अटल irqवापस_t dprc_irq0_handler_thपढ़ो(पूर्णांक irq_num, व्योम *arg)
अणु
	पूर्णांक error;
	u32 status;
	काष्ठा device *dev = arg;
	काष्ठा fsl_mc_device *mc_dev = to_fsl_mc_device(dev);
	काष्ठा fsl_mc_bus *mc_bus = to_fsl_mc_bus(mc_dev);
	काष्ठा fsl_mc_io *mc_io = mc_dev->mc_io;
	काष्ठा msi_desc *msi_desc = mc_dev->irqs[0]->msi_desc;

	dev_dbg(dev, "DPRC IRQ %d triggered on CPU %u\n",
		irq_num, smp_processor_id());

	अगर (!(mc_dev->flags & FSL_MC_IS_DPRC))
		वापस IRQ_HANDLED;

	mutex_lock(&mc_bus->scan_mutex);
	अगर (!msi_desc || msi_desc->irq != (u32)irq_num)
		जाओ out;

	status = 0;
	error = dprc_get_irq_status(mc_io, 0, mc_dev->mc_handle, 0,
				    &status);
	अगर (error < 0) अणु
		dev_err(dev,
			"dprc_get_irq_status() failed: %d\n", error);
		जाओ out;
	पूर्ण

	error = dprc_clear_irq_status(mc_io, 0, mc_dev->mc_handle, 0,
				      status);
	अगर (error < 0) अणु
		dev_err(dev,
			"dprc_clear_irq_status() failed: %d\n", error);
		जाओ out;
	पूर्ण

	अगर (status & (DPRC_IRQ_EVENT_OBJ_ADDED |
		      DPRC_IRQ_EVENT_OBJ_REMOVED |
		      DPRC_IRQ_EVENT_CONTAINER_DESTROYED |
		      DPRC_IRQ_EVENT_OBJ_DESTROYED |
		      DPRC_IRQ_EVENT_OBJ_CREATED)) अणु

		error = dprc_scan_objects(mc_dev, true);
		अगर (error < 0) अणु
			/*
			 * If the error is -ENXIO, we ignore it, as it indicates
			 * that the object scan was पातed, as we detected that
			 * an object was हटाओd from the DPRC in the MC, जबतक
			 * we were scanning the DPRC.
			 */
			अगर (error != -ENXIO) अणु
				dev_err(dev, "dprc_scan_objects() failed: %d\n",
					error);
			पूर्ण

			जाओ out;
		पूर्ण
	पूर्ण

out:
	mutex_unlock(&mc_bus->scan_mutex);
	वापस IRQ_HANDLED;
पूर्ण

/*
 * Disable and clear पूर्णांकerrupt क्रम a given DPRC object
 */
पूर्णांक disable_dprc_irq(काष्ठा fsl_mc_device *mc_dev)
अणु
	काष्ठा fsl_mc_bus *mc_bus = to_fsl_mc_bus(mc_dev);
	पूर्णांक error;
	काष्ठा fsl_mc_io *mc_io = mc_dev->mc_io;

	/*
	 * Disable generation of पूर्णांकerrupt, जबतक we configure it:
	 */
	error = dprc_set_irq_enable(mc_io, 0, mc_dev->mc_handle, 0, 0);
	अगर (error < 0) अणु
		dev_err(&mc_dev->dev,
			"Disabling DPRC IRQ failed: dprc_set_irq_enable() failed: %d\n",
			error);
		वापस error;
	पूर्ण

	/*
	 * Disable all पूर्णांकerrupt causes क्रम the पूर्णांकerrupt:
	 */
	error = dprc_set_irq_mask(mc_io, 0, mc_dev->mc_handle, 0, 0x0);
	अगर (error < 0) अणु
		dev_err(&mc_dev->dev,
			"Disabling DPRC IRQ failed: dprc_set_irq_mask() failed: %d\n",
			error);
		वापस error;
	पूर्ण

	/*
	 * Clear any leftover पूर्णांकerrupts:
	 */
	error = dprc_clear_irq_status(mc_io, 0, mc_dev->mc_handle, 0, ~0x0U);
	अगर (error < 0) अणु
		dev_err(&mc_dev->dev,
			"Disabling DPRC IRQ failed: dprc_clear_irq_status() failed: %d\n",
			error);
		वापस error;
	पूर्ण

	mc_bus->irq_enabled = 0;

	वापस 0;
पूर्ण

पूर्णांक get_dprc_irq_state(काष्ठा fsl_mc_device *mc_dev)
अणु
	काष्ठा fsl_mc_bus *mc_bus = to_fsl_mc_bus(mc_dev);

	वापस mc_bus->irq_enabled;
पूर्ण

अटल पूर्णांक रेजिस्टर_dprc_irq_handler(काष्ठा fsl_mc_device *mc_dev)
अणु
	पूर्णांक error;
	काष्ठा fsl_mc_device_irq *irq = mc_dev->irqs[0];

	/*
	 * NOTE: devm_request_thपढ़ोed_irq() invokes the device-specअगरic
	 * function that programs the MSI physically in the device
	 */
	error = devm_request_thपढ़ोed_irq(&mc_dev->dev,
					  irq->msi_desc->irq,
					  dprc_irq0_handler,
					  dprc_irq0_handler_thपढ़ो,
					  IRQF_NO_SUSPEND | IRQF_ONESHOT,
					  dev_name(&mc_dev->dev),
					  &mc_dev->dev);
	अगर (error < 0) अणु
		dev_err(&mc_dev->dev,
			"devm_request_threaded_irq() failed: %d\n",
			error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक enable_dprc_irq(काष्ठा fsl_mc_device *mc_dev)
अणु
	काष्ठा fsl_mc_bus *mc_bus = to_fsl_mc_bus(mc_dev);
	पूर्णांक error;

	/*
	 * Enable all पूर्णांकerrupt causes क्रम the पूर्णांकerrupt:
	 */
	error = dprc_set_irq_mask(mc_dev->mc_io, 0, mc_dev->mc_handle, 0,
				  ~0x0u);
	अगर (error < 0) अणु
		dev_err(&mc_dev->dev,
			"Enabling DPRC IRQ failed: dprc_set_irq_mask() failed: %d\n",
			error);

		वापस error;
	पूर्ण

	/*
	 * Enable generation of the पूर्णांकerrupt:
	 */
	error = dprc_set_irq_enable(mc_dev->mc_io, 0, mc_dev->mc_handle, 0, 1);
	अगर (error < 0) अणु
		dev_err(&mc_dev->dev,
			"Enabling DPRC IRQ failed: dprc_set_irq_enable() failed: %d\n",
			error);

		वापस error;
	पूर्ण

	mc_bus->irq_enabled = 1;

	वापस 0;
पूर्ण

/*
 * Setup पूर्णांकerrupt क्रम a given DPRC device
 */
अटल पूर्णांक dprc_setup_irq(काष्ठा fsl_mc_device *mc_dev)
अणु
	पूर्णांक error;

	error = fsl_mc_allocate_irqs(mc_dev);
	अगर (error < 0)
		वापस error;

	error = disable_dprc_irq(mc_dev);
	अगर (error < 0)
		जाओ error_मुक्त_irqs;

	error = रेजिस्टर_dprc_irq_handler(mc_dev);
	अगर (error < 0)
		जाओ error_मुक्त_irqs;

	error = enable_dprc_irq(mc_dev);
	अगर (error < 0)
		जाओ error_मुक्त_irqs;

	वापस 0;

error_मुक्त_irqs:
	fsl_mc_मुक्त_irqs(mc_dev);
	वापस error;
पूर्ण

/**
 * dprc_setup - खोलोs and creates a mc_io क्रम DPRC
 *
 * @mc_dev: Poपूर्णांकer to fsl-mc device representing a DPRC
 *
 * It खोलोs the physical DPRC in the MC.
 * It configures the DPRC portal used to communicate with MC
 */

पूर्णांक dprc_setup(काष्ठा fsl_mc_device *mc_dev)
अणु
	काष्ठा device *parent_dev = mc_dev->dev.parent;
	काष्ठा fsl_mc_bus *mc_bus = to_fsl_mc_bus(mc_dev);
	काष्ठा irq_करोमुख्य *mc_msi_करोमुख्य;
	bool mc_io_created = false;
	bool msi_करोमुख्य_set = false;
	bool uapi_created = false;
	u16 major_ver, minor_ver;
	माप_प्रकार region_size;
	पूर्णांक error;

	अगर (!is_fsl_mc_bus_dprc(mc_dev))
		वापस -EINVAL;

	अगर (dev_get_msi_करोमुख्य(&mc_dev->dev))
		वापस -EINVAL;

	अगर (!mc_dev->mc_io) अणु
		/*
		 * This is a child DPRC:
		 */
		अगर (!dev_is_fsl_mc(parent_dev))
			वापस -EINVAL;

		अगर (mc_dev->obj_desc.region_count == 0)
			वापस -EINVAL;

		region_size = resource_size(mc_dev->regions);

		error = fsl_create_mc_io(&mc_dev->dev,
					 mc_dev->regions[0].start,
					 region_size,
					 शून्य,
					 FSL_MC_IO_ATOMIC_CONTEXT_PORTAL,
					 &mc_dev->mc_io);
		अगर (error < 0)
			वापस error;

		mc_io_created = true;
	पूर्ण अन्यथा अणु
		error = fsl_mc_uapi_create_device_file(mc_bus);
		अगर (error < 0)
			वापस -EPROBE_DEFER;
		uapi_created = true;
	पूर्ण

	mc_msi_करोमुख्य = fsl_mc_find_msi_करोमुख्य(&mc_dev->dev);
	अगर (!mc_msi_करोमुख्य) अणु
		dev_warn(&mc_dev->dev,
			 "WARNING: MC bus without interrupt support\n");
	पूर्ण अन्यथा अणु
		dev_set_msi_करोमुख्य(&mc_dev->dev, mc_msi_करोमुख्य);
		msi_करोमुख्य_set = true;
	पूर्ण

	error = dprc_खोलो(mc_dev->mc_io, 0, mc_dev->obj_desc.id,
			  &mc_dev->mc_handle);
	अगर (error < 0) अणु
		dev_err(&mc_dev->dev, "dprc_open() failed: %d\n", error);
		जाओ error_cleanup_msi_करोमुख्य;
	पूर्ण

	error = dprc_get_attributes(mc_dev->mc_io, 0, mc_dev->mc_handle,
				    &mc_bus->dprc_attr);
	अगर (error < 0) अणु
		dev_err(&mc_dev->dev, "dprc_get_attributes() failed: %d\n",
			error);
		जाओ error_cleanup_खोलो;
	पूर्ण

	error = dprc_get_api_version(mc_dev->mc_io, 0,
				     &major_ver,
				     &minor_ver);
	अगर (error < 0) अणु
		dev_err(&mc_dev->dev, "dprc_get_api_version() failed: %d\n",
			error);
		जाओ error_cleanup_खोलो;
	पूर्ण

	अगर (major_ver < DPRC_MIN_VER_MAJOR) अणु
		dev_err(&mc_dev->dev,
			"ERROR: DPRC version %d.%d not supported\n",
			major_ver, minor_ver);
		error = -ENOTSUPP;
		जाओ error_cleanup_खोलो;
	पूर्ण

	वापस 0;

error_cleanup_खोलो:
	(व्योम)dprc_बंद(mc_dev->mc_io, 0, mc_dev->mc_handle);

error_cleanup_msi_करोमुख्य:
	अगर (msi_करोमुख्य_set)
		dev_set_msi_करोमुख्य(&mc_dev->dev, शून्य);

	अगर (mc_io_created) अणु
		fsl_destroy_mc_io(mc_dev->mc_io);
		mc_dev->mc_io = शून्य;
	पूर्ण

	अगर (uapi_created)
		fsl_mc_uapi_हटाओ_device_file(mc_bus);

	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(dprc_setup);

/**
 * dprc_probe - callback invoked when a DPRC is being bound to this driver
 *
 * @mc_dev: Poपूर्णांकer to fsl-mc device representing a DPRC
 *
 * It खोलोs the physical DPRC in the MC.
 * It scans the DPRC to discover the MC objects contained in it.
 * It creates the पूर्णांकerrupt pool क्रम the MC bus associated with the DPRC.
 * It configures the पूर्णांकerrupts क्रम the DPRC device itself.
 */
अटल पूर्णांक dprc_probe(काष्ठा fsl_mc_device *mc_dev)
अणु
	पूर्णांक error;

	error = dprc_setup(mc_dev);
	अगर (error < 0)
		वापस error;

	/*
	 * Discover MC objects in DPRC object:
	 */
	error = dprc_scan_container(mc_dev, true);
	अगर (error < 0)
		जाओ dprc_cleanup;

	/*
	 * Configure पूर्णांकerrupt क्रम the DPRC object associated with this MC bus:
	 */
	error = dprc_setup_irq(mc_dev);
	अगर (error < 0)
		जाओ scan_cleanup;

	dev_info(&mc_dev->dev, "DPRC device bound to driver");
	वापस 0;

scan_cleanup:
	device_क्रम_each_child(&mc_dev->dev, शून्य, __fsl_mc_device_हटाओ);
dprc_cleanup:
	dprc_cleanup(mc_dev);
	वापस error;
पूर्ण

/*
 * Tear करोwn पूर्णांकerrupt क्रम a given DPRC object
 */
अटल व्योम dprc_tearकरोwn_irq(काष्ठा fsl_mc_device *mc_dev)
अणु
	काष्ठा fsl_mc_device_irq *irq = mc_dev->irqs[0];

	(व्योम)disable_dprc_irq(mc_dev);

	devm_मुक्त_irq(&mc_dev->dev, irq->msi_desc->irq, &mc_dev->dev);

	fsl_mc_मुक्त_irqs(mc_dev);
पूर्ण

/**
 * dprc_cleanup - function that cleanups a DPRC
 *
 * @mc_dev: Poपूर्णांकer to fsl-mc device representing the DPRC
 *
 * It बंदs the DPRC device in the MC.
 * It destroys the पूर्णांकerrupt pool associated with this MC bus.
 */

पूर्णांक dprc_cleanup(काष्ठा fsl_mc_device *mc_dev)
अणु
	काष्ठा fsl_mc_bus *mc_bus = to_fsl_mc_bus(mc_dev);
	पूर्णांक error;

	/* this function should be called only क्रम DPRCs, it
	 * is an error to call it क्रम regular objects
	 */
	अगर (!is_fsl_mc_bus_dprc(mc_dev))
		वापस -EINVAL;

	अगर (dev_get_msi_करोमुख्य(&mc_dev->dev)) अणु
		fsl_mc_cleanup_irq_pool(mc_dev);
		dev_set_msi_करोमुख्य(&mc_dev->dev, शून्य);
	पूर्ण

	fsl_mc_cleanup_all_resource_pools(mc_dev);

	/* अगर this step fails we cannot go further with cleanup as there is no way of
	 * communicating with the firmware
	 */
	अगर (!mc_dev->mc_io) अणु
		dev_err(&mc_dev->dev, "mc_io is NULL, tear down cannot be performed in firmware\n");
		वापस -EINVAL;
	पूर्ण

	error = dprc_बंद(mc_dev->mc_io, 0, mc_dev->mc_handle);
	अगर (error < 0)
		dev_err(&mc_dev->dev, "dprc_close() failed: %d\n", error);

	अगर (!fsl_mc_is_root_dprc(&mc_dev->dev)) अणु
		fsl_destroy_mc_io(mc_dev->mc_io);
		mc_dev->mc_io = शून्य;
	पूर्ण अन्यथा अणु
		fsl_mc_uapi_हटाओ_device_file(mc_bus);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(dprc_cleanup);

/**
 * dprc_हटाओ - callback invoked when a DPRC is being unbound from this driver
 *
 * @mc_dev: Poपूर्णांकer to fsl-mc device representing the DPRC
 *
 * It हटाओs the DPRC's child objects from Linux (not from the MC) and
 * बंदs the DPRC device in the MC.
 * It tears करोwn the पूर्णांकerrupts that were configured क्रम the DPRC device.
 * It destroys the पूर्णांकerrupt pool associated with this MC bus.
 */
अटल पूर्णांक dprc_हटाओ(काष्ठा fsl_mc_device *mc_dev)
अणु
	काष्ठा fsl_mc_bus *mc_bus = to_fsl_mc_bus(mc_dev);

	अगर (!is_fsl_mc_bus_dprc(mc_dev))
		वापस -EINVAL;

	अगर (!mc_bus->irq_resources)
		वापस -EINVAL;

	अगर (dev_get_msi_करोमुख्य(&mc_dev->dev))
		dprc_tearकरोwn_irq(mc_dev);

	device_क्रम_each_child(&mc_dev->dev, शून्य, __fsl_mc_device_हटाओ);

	dprc_cleanup(mc_dev);

	dev_info(&mc_dev->dev, "DPRC device unbound from driver");
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fsl_mc_device_id match_id_table[] = अणु
	अणु
	 .venकरोr = FSL_MC_VENDOR_FREESCALE,
	 .obj_type = "dprc"पूर्ण,
	अणु.venकरोr = 0x0पूर्ण,
पूर्ण;

अटल काष्ठा fsl_mc_driver dprc_driver = अणु
	.driver = अणु
		   .name = FSL_MC_DPRC_DRIVER_NAME,
		   .owner = THIS_MODULE,
		   .pm = शून्य,
		   पूर्ण,
	.match_id_table = match_id_table,
	.probe = dprc_probe,
	.हटाओ = dprc_हटाओ,
पूर्ण;

पूर्णांक __init dprc_driver_init(व्योम)
अणु
	वापस fsl_mc_driver_रेजिस्टर(&dprc_driver);
पूर्ण

व्योम dprc_driver_निकास(व्योम)
अणु
	fsl_mc_driver_unरेजिस्टर(&dprc_driver);
पूर्ण
