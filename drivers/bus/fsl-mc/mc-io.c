<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause)
/*
 * Copyright 2013-2016 Freescale Semiconductor Inc.
 *
 */

#समावेश <linux/पन.स>
#समावेश <linux/fsl/mc.h>

#समावेश "fsl-mc-private.h"

अटल पूर्णांक fsl_mc_io_set_dpmcp(काष्ठा fsl_mc_io *mc_io,
			       काष्ठा fsl_mc_device *dpmcp_dev)
अणु
	पूर्णांक error;

	अगर (mc_io->dpmcp_dev)
		वापस -EINVAL;

	अगर (dpmcp_dev->mc_io)
		वापस -EINVAL;

	error = dpmcp_खोलो(mc_io,
			   0,
			   dpmcp_dev->obj_desc.id,
			   &dpmcp_dev->mc_handle);
	अगर (error < 0)
		वापस error;

	mc_io->dpmcp_dev = dpmcp_dev;
	dpmcp_dev->mc_io = mc_io;
	वापस 0;
पूर्ण

अटल व्योम fsl_mc_io_unset_dpmcp(काष्ठा fsl_mc_io *mc_io)
अणु
	पूर्णांक error;
	काष्ठा fsl_mc_device *dpmcp_dev = mc_io->dpmcp_dev;

	error = dpmcp_बंद(mc_io,
			    0,
			    dpmcp_dev->mc_handle);
	अगर (error < 0) अणु
		dev_err(&dpmcp_dev->dev, "dpmcp_close() failed: %d\n",
			error);
	पूर्ण

	mc_io->dpmcp_dev = शून्य;
	dpmcp_dev->mc_io = शून्य;
पूर्ण

/**
 * Creates an MC I/O object
 *
 * @dev: device to be associated with the MC I/O object
 * @mc_portal_phys_addr: physical address of the MC portal to use
 * @mc_portal_size: size in bytes of the MC portal
 * @dpmcp-dev: Poपूर्णांकer to the DPMCP object associated with this MC I/O
 * object or शून्य अगर none.
 * @flags: flags क्रम the new MC I/O object
 * @new_mc_io: Area to वापस poपूर्णांकer to newly created MC I/O object
 *
 * Returns '0' on Success; Error code otherwise.
 */
पूर्णांक __must_check fsl_create_mc_io(काष्ठा device *dev,
				  phys_addr_t mc_portal_phys_addr,
				  u32 mc_portal_size,
				  काष्ठा fsl_mc_device *dpmcp_dev,
				  u32 flags, काष्ठा fsl_mc_io **new_mc_io)
अणु
	पूर्णांक error;
	काष्ठा fsl_mc_io *mc_io;
	व्योम __iomem *mc_portal_virt_addr;
	काष्ठा resource *res;

	mc_io = devm_kzalloc(dev, माप(*mc_io), GFP_KERNEL);
	अगर (!mc_io)
		वापस -ENOMEM;

	mc_io->dev = dev;
	mc_io->flags = flags;
	mc_io->portal_phys_addr = mc_portal_phys_addr;
	mc_io->portal_size = mc_portal_size;
	अगर (flags & FSL_MC_IO_ATOMIC_CONTEXT_PORTAL)
		raw_spin_lock_init(&mc_io->spinlock);
	अन्यथा
		mutex_init(&mc_io->mutex);

	res = devm_request_mem_region(dev,
				      mc_portal_phys_addr,
				      mc_portal_size,
				      "mc_portal");
	अगर (!res) अणु
		dev_err(dev,
			"devm_request_mem_region failed for MC portal %pa\n",
			&mc_portal_phys_addr);
		वापस -EBUSY;
	पूर्ण

	mc_portal_virt_addr = devm_ioremap(dev,
						   mc_portal_phys_addr,
						   mc_portal_size);
	अगर (!mc_portal_virt_addr) अणु
		dev_err(dev,
			"devm_ioremap failed for MC portal %pa\n",
			&mc_portal_phys_addr);
		वापस -ENXIO;
	पूर्ण

	mc_io->portal_virt_addr = mc_portal_virt_addr;
	अगर (dpmcp_dev) अणु
		error = fsl_mc_io_set_dpmcp(mc_io, dpmcp_dev);
		अगर (error < 0)
			जाओ error_destroy_mc_io;
	पूर्ण

	*new_mc_io = mc_io;
	वापस 0;

error_destroy_mc_io:
	fsl_destroy_mc_io(mc_io);
	वापस error;
पूर्ण

/**
 * Destroys an MC I/O object
 *
 * @mc_io: MC I/O object to destroy
 */
व्योम fsl_destroy_mc_io(काष्ठा fsl_mc_io *mc_io)
अणु
	काष्ठा fsl_mc_device *dpmcp_dev;

	अगर (!mc_io)
		वापस;

	dpmcp_dev = mc_io->dpmcp_dev;

	अगर (dpmcp_dev)
		fsl_mc_io_unset_dpmcp(mc_io);

	devm_iounmap(mc_io->dev, mc_io->portal_virt_addr);
	devm_release_mem_region(mc_io->dev,
				mc_io->portal_phys_addr,
				mc_io->portal_size);

	mc_io->portal_virt_addr = शून्य;
	devm_kमुक्त(mc_io->dev, mc_io);
पूर्ण

/**
 * fsl_mc_portal_allocate - Allocates an MC portal
 *
 * @mc_dev: MC device क्रम which the MC portal is to be allocated
 * @mc_io_flags: Flags क्रम the fsl_mc_io object that wraps the allocated
 * MC portal.
 * @new_mc_io: Poपूर्णांकer to area where the poपूर्णांकer to the fsl_mc_io object
 * that wraps the allocated MC portal is to be वापसed
 *
 * This function allocates an MC portal from the device's parent DPRC,
 * from the corresponding MC bus' pool of MC portals and wraps
 * it in a new fsl_mc_io object. If 'mc_dev' is a DPRC itself, the
 * portal is allocated from its own MC bus.
 */
पूर्णांक __must_check fsl_mc_portal_allocate(काष्ठा fsl_mc_device *mc_dev,
					u16 mc_io_flags,
					काष्ठा fsl_mc_io **new_mc_io)
अणु
	काष्ठा fsl_mc_device *mc_bus_dev;
	काष्ठा fsl_mc_bus *mc_bus;
	phys_addr_t mc_portal_phys_addr;
	माप_प्रकार mc_portal_size;
	काष्ठा fsl_mc_device *dpmcp_dev;
	पूर्णांक error = -EINVAL;
	काष्ठा fsl_mc_resource *resource = शून्य;
	काष्ठा fsl_mc_io *mc_io = शून्य;

	अगर (mc_dev->flags & FSL_MC_IS_DPRC) अणु
		mc_bus_dev = mc_dev;
	पूर्ण अन्यथा अणु
		अगर (!dev_is_fsl_mc(mc_dev->dev.parent))
			वापस error;

		mc_bus_dev = to_fsl_mc_device(mc_dev->dev.parent);
	पूर्ण

	mc_bus = to_fsl_mc_bus(mc_bus_dev);
	*new_mc_io = शून्य;
	error = fsl_mc_resource_allocate(mc_bus, FSL_MC_POOL_DPMCP, &resource);
	अगर (error < 0)
		वापस error;

	error = -EINVAL;
	dpmcp_dev = resource->data;

	अगर (dpmcp_dev->obj_desc.ver_major < DPMCP_MIN_VER_MAJOR ||
	    (dpmcp_dev->obj_desc.ver_major == DPMCP_MIN_VER_MAJOR &&
	     dpmcp_dev->obj_desc.ver_minor < DPMCP_MIN_VER_MINOR)) अणु
		dev_err(&dpmcp_dev->dev,
			"ERROR: Version %d.%d of DPMCP not supported.\n",
			dpmcp_dev->obj_desc.ver_major,
			dpmcp_dev->obj_desc.ver_minor);
		error = -ENOTSUPP;
		जाओ error_cleanup_resource;
	पूर्ण

	mc_portal_phys_addr = dpmcp_dev->regions[0].start;
	mc_portal_size = resource_size(dpmcp_dev->regions);

	error = fsl_create_mc_io(&mc_bus_dev->dev,
				 mc_portal_phys_addr,
				 mc_portal_size, dpmcp_dev,
				 mc_io_flags, &mc_io);
	अगर (error < 0)
		जाओ error_cleanup_resource;

	dpmcp_dev->consumer_link = device_link_add(&mc_dev->dev,
						   &dpmcp_dev->dev,
						   DL_FLAG_AUTOREMOVE_CONSUMER);
	अगर (!dpmcp_dev->consumer_link) अणु
		error = -EINVAL;
		जाओ error_cleanup_mc_io;
	पूर्ण

	*new_mc_io = mc_io;
	वापस 0;

error_cleanup_mc_io:
	fsl_destroy_mc_io(mc_io);
error_cleanup_resource:
	fsl_mc_resource_मुक्त(resource);
	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(fsl_mc_portal_allocate);

/**
 * fsl_mc_portal_मुक्त - Returns an MC portal to the pool of मुक्त MC portals
 * of a given MC bus
 *
 * @mc_io: Poपूर्णांकer to the fsl_mc_io object that wraps the MC portal to मुक्त
 */
व्योम fsl_mc_portal_मुक्त(काष्ठा fsl_mc_io *mc_io)
अणु
	काष्ठा fsl_mc_device *dpmcp_dev;
	काष्ठा fsl_mc_resource *resource;

	/*
	 * Every mc_io obtained by calling fsl_mc_portal_allocate() is supposed
	 * to have a DPMCP object associated with.
	 */
	dpmcp_dev = mc_io->dpmcp_dev;

	resource = dpmcp_dev->resource;
	अगर (!resource || resource->type != FSL_MC_POOL_DPMCP)
		वापस;

	अगर (resource->data != dpmcp_dev)
		वापस;

	fsl_destroy_mc_io(mc_io);
	fsl_mc_resource_मुक्त(resource);

	dpmcp_dev->consumer_link = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(fsl_mc_portal_मुक्त);

/**
 * fsl_mc_portal_reset - Resets the dpmcp object क्रम a given fsl_mc_io object
 *
 * @mc_io: Poपूर्णांकer to the fsl_mc_io object that wraps the MC portal to मुक्त
 */
पूर्णांक fsl_mc_portal_reset(काष्ठा fsl_mc_io *mc_io)
अणु
	पूर्णांक error;
	काष्ठा fsl_mc_device *dpmcp_dev = mc_io->dpmcp_dev;

	error = dpmcp_reset(mc_io, 0, dpmcp_dev->mc_handle);
	अगर (error < 0) अणु
		dev_err(&dpmcp_dev->dev, "dpmcp_reset() failed: %d\n", error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(fsl_mc_portal_reset);
