<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * RapidIO क्रमागतeration and discovery support
 *
 * Copyright 2005 MontaVista Software, Inc.
 * Matt Porter <mporter@kernel.crashing.org>
 *
 * Copyright 2009 Integrated Device Technology, Inc.
 * Alex Bounine <alexandre.bounine@idt.com>
 * - Added Port-Write/Error Management initialization and handling
 *
 * Copyright 2009 Sysgo AG
 * Thomas Moll <thomas.moll@sysgo.com>
 * - Added Input- Output- enable functionality, to allow full communication
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>

#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/init.h>
#समावेश <linux/rपन.स>
#समावेश <linux/rio_drv.h>
#समावेश <linux/rio_ids.h>
#समावेश <linux/rio_regs.h>
#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/समयr.h>
#समावेश <linux/sched.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/slab.h>

#समावेश "rio.h"

अटल व्योम rio_init_em(काष्ठा rio_dev *rdev);

काष्ठा rio_id_table अणु
	u16 start;	/* logical minimal id */
	u32 max;	/* max number of IDs in table */
	spinlock_t lock;
	अचिन्हित दीर्घ table[];
पूर्ण;

अटल पूर्णांक next_destid = 0;
अटल पूर्णांक next_comptag = 1;

/**
 * rio_destid_alloc - Allocate next available destID क्रम given network
 * @net: RIO network
 *
 * Returns next available device destination ID क्रम the specअगरied RIO network.
 * Marks allocated ID as one in use.
 * Returns RIO_INVALID_DESTID अगर new destID is not available.
 */
अटल u16 rio_destid_alloc(काष्ठा rio_net *net)
अणु
	पूर्णांक destid;
	काष्ठा rio_id_table *idtab = (काष्ठा rio_id_table *)net->क्रमागत_data;

	spin_lock(&idtab->lock);
	destid = find_first_zero_bit(idtab->table, idtab->max);

	अगर (destid < idtab->max) अणु
		set_bit(destid, idtab->table);
		destid += idtab->start;
	पूर्ण अन्यथा
		destid = RIO_INVALID_DESTID;

	spin_unlock(&idtab->lock);
	वापस (u16)destid;
पूर्ण

/**
 * rio_destid_reserve - Reserve the specअगरied destID
 * @net: RIO network
 * @destid: destID to reserve
 *
 * Tries to reserve the specअगरied destID.
 * Returns 0 अगर successful.
 */
अटल पूर्णांक rio_destid_reserve(काष्ठा rio_net *net, u16 destid)
अणु
	पूर्णांक oldbit;
	काष्ठा rio_id_table *idtab = (काष्ठा rio_id_table *)net->क्रमागत_data;

	destid -= idtab->start;
	spin_lock(&idtab->lock);
	oldbit = test_and_set_bit(destid, idtab->table);
	spin_unlock(&idtab->lock);
	वापस oldbit;
पूर्ण

/**
 * rio_destid_मुक्त - मुक्त a previously allocated destID
 * @net: RIO network
 * @destid: destID to मुक्त
 *
 * Makes the specअगरied destID available क्रम use.
 */
अटल व्योम rio_destid_मुक्त(काष्ठा rio_net *net, u16 destid)
अणु
	काष्ठा rio_id_table *idtab = (काष्ठा rio_id_table *)net->क्रमागत_data;

	destid -= idtab->start;
	spin_lock(&idtab->lock);
	clear_bit(destid, idtab->table);
	spin_unlock(&idtab->lock);
पूर्ण

/**
 * rio_destid_first - वापस first destID in use
 * @net: RIO network
 */
अटल u16 rio_destid_first(काष्ठा rio_net *net)
अणु
	पूर्णांक destid;
	काष्ठा rio_id_table *idtab = (काष्ठा rio_id_table *)net->क्रमागत_data;

	spin_lock(&idtab->lock);
	destid = find_first_bit(idtab->table, idtab->max);
	अगर (destid >= idtab->max)
		destid = RIO_INVALID_DESTID;
	अन्यथा
		destid += idtab->start;
	spin_unlock(&idtab->lock);
	वापस (u16)destid;
पूर्ण

/**
 * rio_destid_next - वापस next destID in use
 * @net: RIO network
 * @from: destination ID from which search shall जारी
 */
अटल u16 rio_destid_next(काष्ठा rio_net *net, u16 from)
अणु
	पूर्णांक destid;
	काष्ठा rio_id_table *idtab = (काष्ठा rio_id_table *)net->क्रमागत_data;

	spin_lock(&idtab->lock);
	destid = find_next_bit(idtab->table, idtab->max, from);
	अगर (destid >= idtab->max)
		destid = RIO_INVALID_DESTID;
	अन्यथा
		destid += idtab->start;
	spin_unlock(&idtab->lock);
	वापस (u16)destid;
पूर्ण

/**
 * rio_get_device_id - Get the base/extended device id क्रम a device
 * @port: RIO master port
 * @destid: Destination ID of device
 * @hopcount: Hopcount to device
 *
 * Reads the base/extended device id from a device. Returns the
 * 8/16-bit device ID.
 */
अटल u16 rio_get_device_id(काष्ठा rio_mport *port, u16 destid, u8 hopcount)
अणु
	u32 result;

	rio_mport_पढ़ो_config_32(port, destid, hopcount, RIO_DID_CSR, &result);

	वापस RIO_GET_DID(port->sys_size, result);
पूर्ण

/**
 * rio_set_device_id - Set the base/extended device id क्रम a device
 * @port: RIO master port
 * @destid: Destination ID of device
 * @hopcount: Hopcount to device
 * @did: Device ID value to be written
 *
 * Writes the base/extended device id from a device.
 */
अटल व्योम rio_set_device_id(काष्ठा rio_mport *port, u16 destid, u8 hopcount, u16 did)
अणु
	rio_mport_ग_लिखो_config_32(port, destid, hopcount, RIO_DID_CSR,
				  RIO_SET_DID(port->sys_size, did));
पूर्ण

/**
 * rio_clear_locks- Release all host locks and संकेत क्रमागतeration complete
 * @net: RIO network to run on
 *
 * Marks the component tag CSR on each device with the क्रमागतeration
 * complete flag. When complete, it then release the host locks on
 * each device. Returns 0 on success or %-EINVAL on failure.
 */
अटल पूर्णांक rio_clear_locks(काष्ठा rio_net *net)
अणु
	काष्ठा rio_mport *port = net->hport;
	काष्ठा rio_dev *rdev;
	u32 result;
	पूर्णांक ret = 0;

	/* Release host device id locks */
	rio_local_ग_लिखो_config_32(port, RIO_HOST_DID_LOCK_CSR,
				  port->host_deviceid);
	rio_local_पढ़ो_config_32(port, RIO_HOST_DID_LOCK_CSR, &result);
	अगर ((result & 0xffff) != 0xffff) अणु
		prपूर्णांकk(KERN_INFO
		       "RIO: badness when releasing host lock on master port, result %8.8x\n",
		       result);
		ret = -EINVAL;
	पूर्ण
	list_क्रम_each_entry(rdev, &net->devices, net_list) अणु
		rio_ग_लिखो_config_32(rdev, RIO_HOST_DID_LOCK_CSR,
				    port->host_deviceid);
		rio_पढ़ो_config_32(rdev, RIO_HOST_DID_LOCK_CSR, &result);
		अगर ((result & 0xffff) != 0xffff) अणु
			prपूर्णांकk(KERN_INFO
			       "RIO: badness when releasing host lock on vid %4.4x did %4.4x\n",
			       rdev->vid, rdev->did);
			ret = -EINVAL;
		पूर्ण

		/* Mark device as discovered and enable master */
		rio_पढ़ो_config_32(rdev,
				   rdev->phys_efptr + RIO_PORT_GEN_CTL_CSR,
				   &result);
		result |= RIO_PORT_GEN_DISCOVERED | RIO_PORT_GEN_MASTER;
		rio_ग_लिखो_config_32(rdev,
				    rdev->phys_efptr + RIO_PORT_GEN_CTL_CSR,
				    result);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * rio_क्रमागत_host- Set host lock and initialize host destination ID
 * @port: Master port to issue transaction
 *
 * Sets the local host master port lock and destination ID रेजिस्टर
 * with the host device ID value. The host device ID value is provided
 * by the platक्रमm. Returns %0 on success or %-1 on failure.
 */
अटल पूर्णांक rio_क्रमागत_host(काष्ठा rio_mport *port)
अणु
	u32 result;

	/* Set master port host device id lock */
	rio_local_ग_लिखो_config_32(port, RIO_HOST_DID_LOCK_CSR,
				  port->host_deviceid);

	rio_local_पढ़ो_config_32(port, RIO_HOST_DID_LOCK_CSR, &result);
	अगर ((result & 0xffff) != port->host_deviceid)
		वापस -1;

	/* Set master port destid and init destid ctr */
	rio_local_set_device_id(port, port->host_deviceid);
	वापस 0;
पूर्ण

/**
 * rio_device_has_destid- Test अगर a device contains a destination ID रेजिस्टर
 * @port: Master port to issue transaction
 * @src_ops: RIO device source operations
 * @dst_ops: RIO device destination operations
 *
 * Checks the provided @src_ops and @dst_ops क्रम the necessary transaction
 * capabilities that indicate whether or not a device will implement a
 * destination ID रेजिस्टर. Returns 1 अगर true or 0 अगर false.
 */
अटल पूर्णांक rio_device_has_destid(काष्ठा rio_mport *port, पूर्णांक src_ops,
				 पूर्णांक dst_ops)
अणु
	u32 mask = RIO_OPS_READ | RIO_OPS_WRITE | RIO_OPS_ATOMIC_TST_SWP | RIO_OPS_ATOMIC_INC | RIO_OPS_ATOMIC_DEC | RIO_OPS_ATOMIC_SET | RIO_OPS_ATOMIC_CLR;

	वापस !!((src_ops | dst_ops) & mask);
पूर्ण

/**
 * rio_release_dev- Frees a RIO device काष्ठा
 * @dev: LDM device associated with a RIO device काष्ठा
 *
 * Gets the RIO device काष्ठा associated a RIO device काष्ठा.
 * The RIO device काष्ठा is मुक्तd.
 */
अटल व्योम rio_release_dev(काष्ठा device *dev)
अणु
	काष्ठा rio_dev *rdev;

	rdev = to_rio_dev(dev);
	kमुक्त(rdev);
पूर्ण

/**
 * rio_is_चयन- Tests अगर a RIO device has चयन capabilities
 * @rdev: RIO device
 *
 * Gets the RIO device Processing Element Features रेजिस्टर
 * contents and tests क्रम चयन capabilities. Returns 1 अगर
 * the device is a चयन or 0 अगर it is not a चयन.
 * The RIO device काष्ठा is मुक्तd.
 */
अटल पूर्णांक rio_is_चयन(काष्ठा rio_dev *rdev)
अणु
	अगर (rdev->pef & RIO_PEF_SWITCH)
		वापस 1;
	वापस 0;
पूर्ण

/**
 * rio_setup_device- Allocates and sets up a RIO device
 * @net: RIO network
 * @port: Master port to send transactions
 * @destid: Current destination ID
 * @hopcount: Current hopcount
 * @करो_क्रमागत: Enumeration/Discovery mode flag
 *
 * Allocates a RIO device and configures fields based on configuration
 * space contents. If device has a destination ID रेजिस्टर, a destination
 * ID is either asचिन्हित in क्रमागतeration mode or पढ़ो from configuration
 * space in discovery mode.  If the device has चयन capabilities, then
 * a चयन is allocated and configured appropriately. Returns a poपूर्णांकer
 * to a RIO device on success or शून्य on failure.
 *
 */
अटल काष्ठा rio_dev *rio_setup_device(काष्ठा rio_net *net,
					काष्ठा rio_mport *port, u16 destid,
					u8 hopcount, पूर्णांक करो_क्रमागत)
अणु
	पूर्णांक ret = 0;
	काष्ठा rio_dev *rdev;
	काष्ठा rio_चयन *rचयन = शून्य;
	पूर्णांक result, rdid;
	माप_प्रकार size;
	u32 swpinfo = 0;

	size = माप(*rdev);
	अगर (rio_mport_पढ़ो_config_32(port, destid, hopcount,
				     RIO_PEF_CAR, &result))
		वापस शून्य;

	अगर (result & (RIO_PEF_SWITCH | RIO_PEF_MULTIPORT)) अणु
		rio_mport_पढ़ो_config_32(port, destid, hopcount,
					 RIO_SWP_INFO_CAR, &swpinfo);
		अगर (result & RIO_PEF_SWITCH)
			size += काष्ठा_size(rचयन, nextdev, RIO_GET_TOTAL_PORTS(swpinfo));
	पूर्ण

	rdev = kzalloc(size, GFP_KERNEL);
	अगर (!rdev)
		वापस शून्य;

	rdev->net = net;
	rdev->pef = result;
	rdev->swpinfo = swpinfo;
	rio_mport_पढ़ो_config_32(port, destid, hopcount, RIO_DEV_ID_CAR,
				 &result);
	rdev->did = result >> 16;
	rdev->vid = result & 0xffff;
	rio_mport_पढ़ो_config_32(port, destid, hopcount, RIO_DEV_INFO_CAR,
				 &rdev->device_rev);
	rio_mport_पढ़ो_config_32(port, destid, hopcount, RIO_ASM_ID_CAR,
				 &result);
	rdev->यंत्र_did = result >> 16;
	rdev->यंत्र_vid = result & 0xffff;
	rio_mport_पढ़ो_config_32(port, destid, hopcount, RIO_ASM_INFO_CAR,
				 &result);
	rdev->यंत्र_rev = result >> 16;
	अगर (rdev->pef & RIO_PEF_EXT_FEATURES) अणु
		rdev->efptr = result & 0xffff;
		rdev->phys_efptr = rio_mport_get_physefb(port, 0, destid,
						hopcount, &rdev->phys_rmap);
		pr_debug("RIO: %s Register Map %d device\n",
			 __func__, rdev->phys_rmap);

		rdev->em_efptr = rio_mport_get_feature(port, 0, destid,
						hopcount, RIO_EFB_ERR_MGMNT);
		अगर (!rdev->em_efptr)
			rdev->em_efptr = rio_mport_get_feature(port, 0, destid,
						hopcount, RIO_EFB_ERR_MGMNT_HS);
	पूर्ण

	rio_mport_पढ़ो_config_32(port, destid, hopcount, RIO_SRC_OPS_CAR,
				 &rdev->src_ops);
	rio_mport_पढ़ो_config_32(port, destid, hopcount, RIO_DST_OPS_CAR,
				 &rdev->dst_ops);

	अगर (करो_क्रमागत) अणु
		/* Assign component tag to device */
		अगर (next_comptag >= 0x10000) अणु
			pr_err("RIO: Component Tag Counter Overflow\n");
			जाओ cleanup;
		पूर्ण
		rio_mport_ग_लिखो_config_32(port, destid, hopcount,
					  RIO_COMPONENT_TAG_CSR, next_comptag);
		rdev->comp_tag = next_comptag++;
		rdev->करो_क्रमागत = true;
	पूर्ण  अन्यथा अणु
		rio_mport_पढ़ो_config_32(port, destid, hopcount,
					 RIO_COMPONENT_TAG_CSR,
					 &rdev->comp_tag);
	पूर्ण

	अगर (rio_device_has_destid(port, rdev->src_ops, rdev->dst_ops)) अणु
		अगर (करो_क्रमागत) अणु
			rio_set_device_id(port, destid, hopcount, next_destid);
			rdev->destid = next_destid;
			next_destid = rio_destid_alloc(net);
		पूर्ण अन्यथा
			rdev->destid = rio_get_device_id(port, destid, hopcount);

		rdev->hopcount = 0xff;
	पूर्ण अन्यथा अणु
		/* Switch device has an associated destID which
		 * will be adjusted later
		 */
		rdev->destid = destid;
		rdev->hopcount = hopcount;
	पूर्ण

	/* If a PE has both चयन and other functions, show it as a चयन */
	अगर (rio_is_चयन(rdev)) अणु
		rचयन = rdev->rचयन;
		rचयन->port_ok = 0;
		spin_lock_init(&rचयन->lock);
		rचयन->route_table =
			kzalloc(RIO_MAX_ROUTE_ENTRIES(port->sys_size),
				GFP_KERNEL);
		अगर (!rचयन->route_table)
			जाओ cleanup;
		/* Initialize चयन route table */
		क्रम (rdid = 0; rdid < RIO_MAX_ROUTE_ENTRIES(port->sys_size);
				rdid++)
			rचयन->route_table[rdid] = RIO_INVALID_ROUTE;
		dev_set_name(&rdev->dev, "%02x:s:%04x", rdev->net->id,
			     rdev->comp_tag & RIO_CTAG_UDEVID);

		अगर (करो_क्रमागत)
			rio_route_clr_table(rdev, RIO_GLOBAL_TABLE, 0);
	पूर्ण अन्यथा अणु
		अगर (करो_क्रमागत)
			/*Enable Input Output Port (transmitter receiver)*/
			rio_enable_rx_tx_port(port, 0, destid, hopcount, 0);

		dev_set_name(&rdev->dev, "%02x:e:%04x", rdev->net->id,
			     rdev->comp_tag & RIO_CTAG_UDEVID);
	पूर्ण

	rdev->dev.parent = &net->dev;
	rio_attach_device(rdev);
	rdev->dev.release = rio_release_dev;
	rdev->dma_mask = DMA_BIT_MASK(32);
	rdev->dev.dma_mask = &rdev->dma_mask;
	rdev->dev.coherent_dma_mask = DMA_BIT_MASK(32);

	अगर (rdev->dst_ops & RIO_DST_OPS_DOORBELL)
		rio_init_dbell_res(&rdev->riores[RIO_DOORBELL_RESOURCE],
				   0, 0xffff);

	ret = rio_add_device(rdev);
	अगर (ret)
		जाओ cleanup;

	rio_dev_get(rdev);

	वापस rdev;

cleanup:
	अगर (rचयन)
		kमुक्त(rचयन->route_table);

	kमुक्त(rdev);
	वापस शून्य;
पूर्ण

/**
 * rio_sport_is_active- Tests अगर a चयन port has an active connection.
 * @rdev: RapidIO device object
 * @sp: Switch port number
 *
 * Reads the port error status CSR क्रम a particular चयन port to
 * determine अगर the port has an active link.  Returns
 * %RIO_PORT_N_ERR_STS_PORT_OK अगर the port is active or %0 अगर it is
 * inactive.
 */
अटल पूर्णांक
rio_sport_is_active(काष्ठा rio_dev *rdev, पूर्णांक sp)
अणु
	u32 result = 0;

	rio_पढ़ो_config_32(rdev, RIO_DEV_PORT_N_ERR_STS_CSR(rdev, sp),
			   &result);

	वापस result & RIO_PORT_N_ERR_STS_PORT_OK;
पूर्ण

/**
 * rio_get_host_deviceid_lock- Reads the Host Device ID Lock CSR on a device
 * @port: Master port to send transaction
 * @hopcount: Number of hops to the device
 *
 * Used during क्रमागतeration to पढ़ो the Host Device ID Lock CSR on a
 * RIO device. Returns the value of the lock रेजिस्टर.
 */
अटल u16 rio_get_host_deviceid_lock(काष्ठा rio_mport *port, u8 hopcount)
अणु
	u32 result;

	rio_mport_पढ़ो_config_32(port, RIO_ANY_DESTID(port->sys_size), hopcount,
				 RIO_HOST_DID_LOCK_CSR, &result);

	वापस (u16) (result & 0xffff);
पूर्ण

/**
 * rio_क्रमागत_peer- Recursively क्रमागतerate a RIO network through a master port
 * @net: RIO network being क्रमागतerated
 * @port: Master port to send transactions
 * @hopcount: Number of hops पूर्णांकo the network
 * @prev: Previous RIO device connected to the क्रमागतerated one
 * @prev_port: Port on previous RIO device
 *
 * Recursively क्रमागतerates a RIO network.  Transactions are sent via the
 * master port passed in @port.
 */
अटल पूर्णांक rio_क्रमागत_peer(काष्ठा rio_net *net, काष्ठा rio_mport *port,
			 u8 hopcount, काष्ठा rio_dev *prev, पूर्णांक prev_port)
अणु
	काष्ठा rio_dev *rdev;
	u32 regval;
	पूर्णांक पंचांगp;

	अगर (rio_mport_chk_dev_access(port,
			RIO_ANY_DESTID(port->sys_size), hopcount)) अणु
		pr_debug("RIO: device access check failed\n");
		वापस -1;
	पूर्ण

	अगर (rio_get_host_deviceid_lock(port, hopcount) == port->host_deviceid) अणु
		pr_debug("RIO: PE already discovered by this host\n");
		/*
		 * Alपढ़ोy discovered by this host. Add it as another
		 * link to the existing device.
		 */
		rio_mport_पढ़ो_config_32(port, RIO_ANY_DESTID(port->sys_size),
				hopcount, RIO_COMPONENT_TAG_CSR, &regval);

		अगर (regval) अणु
			rdev = rio_get_comptag((regval & 0xffff), शून्य);

			अगर (rdev && prev && rio_is_चयन(prev)) अणु
				pr_debug("RIO: redundant path to %s\n",
					 rio_name(rdev));
				prev->rचयन->nextdev[prev_port] = rdev;
			पूर्ण
		पूर्ण

		वापस 0;
	पूर्ण

	/* Attempt to acquire device lock */
	rio_mport_ग_लिखो_config_32(port, RIO_ANY_DESTID(port->sys_size),
				  hopcount,
				  RIO_HOST_DID_LOCK_CSR, port->host_deviceid);
	जबतक ((पंचांगp = rio_get_host_deviceid_lock(port, hopcount))
	       < port->host_deviceid) अणु
		/* Delay a bit */
		mdelay(1);
		/* Attempt to acquire device lock again */
		rio_mport_ग_लिखो_config_32(port, RIO_ANY_DESTID(port->sys_size),
					  hopcount,
					  RIO_HOST_DID_LOCK_CSR,
					  port->host_deviceid);
	पूर्ण

	अगर (rio_get_host_deviceid_lock(port, hopcount) > port->host_deviceid) अणु
		pr_debug(
		    "RIO: PE locked by a higher priority host...retreating\n");
		वापस -1;
	पूर्ण

	/* Setup new RIO device */
	rdev = rio_setup_device(net, port, RIO_ANY_DESTID(port->sys_size),
					hopcount, 1);
	अगर (rdev) अणु
		rdev->prev = prev;
		अगर (prev && rio_is_चयन(prev))
			prev->rचयन->nextdev[prev_port] = rdev;
	पूर्ण अन्यथा
		वापस -1;

	अगर (rio_is_चयन(rdev)) अणु
		पूर्णांक sw_destid;
		पूर्णांक cur_destid;
		पूर्णांक sw_inport;
		u16 destid;
		पूर्णांक port_num;

		sw_inport = RIO_GET_PORT_NUM(rdev->swpinfo);
		rio_route_add_entry(rdev, RIO_GLOBAL_TABLE,
				    port->host_deviceid, sw_inport, 0);
		rdev->rचयन->route_table[port->host_deviceid] = sw_inport;

		destid = rio_destid_first(net);
		जबतक (destid != RIO_INVALID_DESTID && destid < next_destid) अणु
			अगर (destid != port->host_deviceid) अणु
				rio_route_add_entry(rdev, RIO_GLOBAL_TABLE,
						    destid, sw_inport, 0);
				rdev->rचयन->route_table[destid] = sw_inport;
			पूर्ण
			destid = rio_destid_next(net, destid + 1);
		पूर्ण
		pr_debug(
		    "RIO: found %s (vid %4.4x did %4.4x) with %d ports\n",
		    rio_name(rdev), rdev->vid, rdev->did,
		    RIO_GET_TOTAL_PORTS(rdev->swpinfo));
		sw_destid = next_destid;
		क्रम (port_num = 0;
		     port_num < RIO_GET_TOTAL_PORTS(rdev->swpinfo);
		     port_num++) अणु
			अगर (sw_inport == port_num) अणु
				rio_enable_rx_tx_port(port, 0,
					      RIO_ANY_DESTID(port->sys_size),
					      hopcount, port_num);
				rdev->rचयन->port_ok |= (1 << port_num);
				जारी;
			पूर्ण

			cur_destid = next_destid;

			अगर (rio_sport_is_active(rdev, port_num)) अणु
				pr_debug(
				    "RIO: scanning device on port %d\n",
				    port_num);
				rio_enable_rx_tx_port(port, 0,
					      RIO_ANY_DESTID(port->sys_size),
					      hopcount, port_num);
				rdev->rचयन->port_ok |= (1 << port_num);
				rio_route_add_entry(rdev, RIO_GLOBAL_TABLE,
						RIO_ANY_DESTID(port->sys_size),
						port_num, 0);

				अगर (rio_क्रमागत_peer(net, port, hopcount + 1,
						  rdev, port_num) < 0)
					वापस -1;

				/* Update routing tables */
				destid = rio_destid_next(net, cur_destid + 1);
				अगर (destid != RIO_INVALID_DESTID) अणु
					क्रम (destid = cur_destid;
					     destid < next_destid;) अणु
						अगर (destid != port->host_deviceid) अणु
							rio_route_add_entry(rdev,
								    RIO_GLOBAL_TABLE,
								    destid,
								    port_num,
								    0);
							rdev->rचयन->
								route_table[destid] =
								port_num;
						पूर्ण
						destid = rio_destid_next(net,
								destid + 1);
					पूर्ण
				पूर्ण
			पूर्ण अन्यथा अणु
				/* If चयन supports Error Management,
				 * set PORT_LOCKOUT bit क्रम unused port
				 */
				अगर (rdev->em_efptr)
					rio_set_port_lockout(rdev, port_num, 1);

				rdev->rचयन->port_ok &= ~(1 << port_num);
			पूर्ण
		पूर्ण

		/* Direct Port-ग_लिखो messages to the क्रमागतeratiing host */
		अगर ((rdev->src_ops & RIO_SRC_OPS_PORT_WRITE) &&
		    (rdev->em_efptr)) अणु
			rio_ग_लिखो_config_32(rdev,
					rdev->em_efptr + RIO_EM_PW_TGT_DEVID,
					(port->host_deviceid << 16) |
					(port->sys_size << 15));
		पूर्ण

		rio_init_em(rdev);

		/* Check क्रम empty चयन */
		अगर (next_destid == sw_destid)
			next_destid = rio_destid_alloc(net);

		rdev->destid = sw_destid;
	पूर्ण अन्यथा
		pr_debug("RIO: found %s (vid %4.4x did %4.4x)\n",
		    rio_name(rdev), rdev->vid, rdev->did);

	वापस 0;
पूर्ण

/**
 * rio_क्रमागत_complete- Tests अगर क्रमागतeration of a network is complete
 * @port: Master port to send transaction
 *
 * Tests the PGCCSR discovered bit क्रम non-zero value (क्रमागतeration
 * complete flag). Return %1 अगर क्रमागतeration is complete or %0 अगर
 * क्रमागतeration is incomplete.
 */
अटल पूर्णांक rio_क्रमागत_complete(काष्ठा rio_mport *port)
अणु
	u32 regval;

	rio_local_पढ़ो_config_32(port, port->phys_efptr + RIO_PORT_GEN_CTL_CSR,
				 &regval);
	वापस (regval & RIO_PORT_GEN_DISCOVERED) ? 1 : 0;
पूर्ण

/**
 * rio_disc_peer- Recursively discovers a RIO network through a master port
 * @net: RIO network being discovered
 * @port: Master port to send transactions
 * @destid: Current destination ID in network
 * @hopcount: Number of hops पूर्णांकo the network
 * @prev: previous rio_dev
 * @prev_port: previous port number
 *
 * Recursively discovers a RIO network.  Transactions are sent via the
 * master port passed in @port.
 */
अटल पूर्णांक
rio_disc_peer(काष्ठा rio_net *net, काष्ठा rio_mport *port, u16 destid,
	      u8 hopcount, काष्ठा rio_dev *prev, पूर्णांक prev_port)
अणु
	u8 port_num, route_port;
	काष्ठा rio_dev *rdev;
	u16 ndestid;

	/* Setup new RIO device */
	अगर ((rdev = rio_setup_device(net, port, destid, hopcount, 0))) अणु
		rdev->prev = prev;
		अगर (prev && rio_is_चयन(prev))
			prev->rचयन->nextdev[prev_port] = rdev;
	पूर्ण अन्यथा
		वापस -1;

	अगर (rio_is_चयन(rdev)) अणु
		/* Associated destid is how we accessed this चयन */
		rdev->destid = destid;

		pr_debug(
		    "RIO: found %s (vid %4.4x did %4.4x) with %d ports\n",
		    rio_name(rdev), rdev->vid, rdev->did,
		    RIO_GET_TOTAL_PORTS(rdev->swpinfo));
		क्रम (port_num = 0;
		     port_num < RIO_GET_TOTAL_PORTS(rdev->swpinfo);
		     port_num++) अणु
			अगर (RIO_GET_PORT_NUM(rdev->swpinfo) == port_num)
				जारी;

			अगर (rio_sport_is_active(rdev, port_num)) अणु
				pr_debug(
				    "RIO: scanning device on port %d\n",
				    port_num);

				rio_lock_device(port, destid, hopcount, 1000);

				क्रम (ndestid = 0;
				     ndestid < RIO_ANY_DESTID(port->sys_size);
				     ndestid++) अणु
					rio_route_get_entry(rdev,
							    RIO_GLOBAL_TABLE,
							    ndestid,
							    &route_port, 0);
					अगर (route_port == port_num)
						अवरोध;
				पूर्ण

				अगर (ndestid == RIO_ANY_DESTID(port->sys_size))
					जारी;
				rio_unlock_device(port, destid, hopcount);
				अगर (rio_disc_peer(net, port, ndestid,
					hopcount + 1, rdev, port_num) < 0)
					वापस -1;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा
		pr_debug("RIO: found %s (vid %4.4x did %4.4x)\n",
		    rio_name(rdev), rdev->vid, rdev->did);

	वापस 0;
पूर्ण

/**
 * rio_mport_is_active- Tests अगर master port link is active
 * @port: Master port to test
 *
 * Reads the port error status CSR क्रम the master port to
 * determine अगर the port has an active link.  Returns
 * %RIO_PORT_N_ERR_STS_PORT_OK अगर the  master port is active
 * or %0 अगर it is inactive.
 */
अटल पूर्णांक rio_mport_is_active(काष्ठा rio_mport *port)
अणु
	u32 result = 0;

	rio_local_पढ़ो_config_32(port,
		port->phys_efptr +
			RIO_PORT_N_ERR_STS_CSR(port->index, port->phys_rmap),
		&result);
	वापस result & RIO_PORT_N_ERR_STS_PORT_OK;
पूर्ण

अटल व्योम rio_scan_release_net(काष्ठा rio_net *net)
अणु
	pr_debug("RIO-SCAN: %s: net_%d\n", __func__, net->id);
	kमुक्त(net->क्रमागत_data);
पूर्ण

अटल व्योम rio_scan_release_dev(काष्ठा device *dev)
अणु
	काष्ठा rio_net *net;

	net = to_rio_net(dev);
	pr_debug("RIO-SCAN: %s: net_%d\n", __func__, net->id);
	kमुक्त(net);
पूर्ण

/*
 * rio_scan_alloc_net - Allocate and configure a new RIO network
 * @mport: Master port associated with the RIO network
 * @करो_क्रमागत: Enumeration/Discovery mode flag
 * @start: logical minimal start id क्रम new net
 *
 * Allocates a new RIO network काष्ठाure and initializes क्रमागतerator-specअगरic
 * part of it (अगर required).
 * Returns a RIO network poपूर्णांकer on success or %शून्य on failure.
 */
अटल काष्ठा rio_net *rio_scan_alloc_net(काष्ठा rio_mport *mport,
					  पूर्णांक करो_क्रमागत, u16 start)
अणु
	काष्ठा rio_net *net;

	net = rio_alloc_net(mport);

	अगर (net && करो_क्रमागत) अणु
		काष्ठा rio_id_table *idtab;
		माप_प्रकार size;

		size = माप(काष्ठा rio_id_table) +
				BITS_TO_LONGS(
					RIO_MAX_ROUTE_ENTRIES(mport->sys_size)
					) * माप(दीर्घ);

		idtab = kzalloc(size, GFP_KERNEL);

		अगर (idtab == शून्य) अणु
			pr_err("RIO: failed to allocate destID table\n");
			rio_मुक्त_net(net);
			net = शून्य;
		पूर्ण अन्यथा अणु
			net->क्रमागत_data = idtab;
			net->release = rio_scan_release_net;
			idtab->start = start;
			idtab->max = RIO_MAX_ROUTE_ENTRIES(mport->sys_size);
			spin_lock_init(&idtab->lock);
		पूर्ण
	पूर्ण

	अगर (net) अणु
		net->id = mport->id;
		net->hport = mport;
		dev_set_name(&net->dev, "rnet_%d", net->id);
		net->dev.parent = &mport->dev;
		net->dev.release = rio_scan_release_dev;
		rio_add_net(net);
	पूर्ण

	वापस net;
पूर्ण

/**
 * rio_update_route_tables- Updates route tables in चयनes
 * @net: RIO network to run update on
 *
 * For each क्रमागतerated device, ensure that each चयन in a प्रणाली
 * has correct routing entries. Add routes क्रम devices that where
 * unknown during the first क्रमागतeration pass through the चयन.
 */
अटल व्योम rio_update_route_tables(काष्ठा rio_net *net)
अणु
	काष्ठा rio_dev *rdev, *swrdev;
	काष्ठा rio_चयन *rचयन;
	u8 sport;
	u16 destid;

	list_क्रम_each_entry(rdev, &net->devices, net_list) अणु

		destid = rdev->destid;

		list_क्रम_each_entry(rचयन, &net->चयनes, node) अणु

			अगर (rio_is_चयन(rdev)	&& (rdev->rचयन == rचयन))
				जारी;

			अगर (RIO_INVALID_ROUTE == rचयन->route_table[destid]) अणु
				swrdev = sw_to_rio_dev(rचयन);

				/* Skip अगर destid ends in empty चयन*/
				अगर (swrdev->destid == destid)
					जारी;

				sport = RIO_GET_PORT_NUM(swrdev->swpinfo);

				rio_route_add_entry(swrdev, RIO_GLOBAL_TABLE,
						    destid, sport, 0);
				rचयन->route_table[destid] = sport;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/**
 * rio_init_em - Initializes RIO Error Management (क्रम चयनes)
 * @rdev: RIO device
 *
 * For each क्रमागतerated चयन, call device-specअगरic error management
 * initialization routine (अगर supplied by the चयन driver).
 */
अटल व्योम rio_init_em(काष्ठा rio_dev *rdev)
अणु
	अगर (rio_is_चयन(rdev) && (rdev->em_efptr) &&
	    rdev->rचयन->ops && rdev->rचयन->ops->em_init) अणु
		rdev->rचयन->ops->em_init(rdev);
	पूर्ण
पूर्ण

/**
 * rio_क्रमागत_mport- Start क्रमागतeration through a master port
 * @mport: Master port to send transactions
 * @flags: Enumeration control flags
 *
 * Starts the क्रमागतeration process. If somebody has क्रमागतerated our
 * master port device, then give up. If not and we have an active
 * link, then start recursive peer क्रमागतeration. Returns %0 अगर
 * क्रमागतeration succeeds or %-EBUSY अगर क्रमागतeration fails.
 */
अटल पूर्णांक rio_क्रमागत_mport(काष्ठा rio_mport *mport, u32 flags)
अणु
	काष्ठा rio_net *net = शून्य;
	पूर्णांक rc = 0;

	prपूर्णांकk(KERN_INFO "RIO: enumerate master port %d, %s\n", mport->id,
	       mport->name);

	/*
	 * To aव्योम multiple start requests (repeat क्रमागतeration is not supported
	 * by this method) check अगर क्रमागतeration/discovery was perक्रमmed क्रम this
	 * mport: अगर mport was added पूर्णांकo the list of mports क्रम a net निकास
	 * with error.
	 */
	अगर (mport->nnode.next || mport->nnode.prev)
		वापस -EBUSY;

	/* If somebody अन्यथा क्रमागतerated our master port device, bail. */
	अगर (rio_क्रमागत_host(mport) < 0) अणु
		prपूर्णांकk(KERN_INFO
		       "RIO: master port %d device has been enumerated by a remote host\n",
		       mport->id);
		rc = -EBUSY;
		जाओ out;
	पूर्ण

	/* If master port has an active link, allocate net and क्रमागत peers */
	अगर (rio_mport_is_active(mport)) अणु
		net = rio_scan_alloc_net(mport, 1, 0);
		अगर (!net) अणु
			prपूर्णांकk(KERN_ERR "RIO: failed to allocate new net\n");
			rc = -ENOMEM;
			जाओ out;
		पूर्ण

		/* reserve mport destID in new net */
		rio_destid_reserve(net, mport->host_deviceid);

		/* Enable Input Output Port (transmitter receiver) */
		rio_enable_rx_tx_port(mport, 1, 0, 0, 0);

		/* Set component tag क्रम host */
		rio_local_ग_लिखो_config_32(mport, RIO_COMPONENT_TAG_CSR,
					  next_comptag++);

		next_destid = rio_destid_alloc(net);

		अगर (rio_क्रमागत_peer(net, mport, 0, शून्य, 0) < 0) अणु
			/* A higher priority host won क्रमागतeration, bail. */
			prपूर्णांकk(KERN_INFO
			       "RIO: master port %d device has lost enumeration to a remote host\n",
			       mport->id);
			rio_clear_locks(net);
			rc = -EBUSY;
			जाओ out;
		पूर्ण
		/* मुक्त the last allocated destID (unused) */
		rio_destid_मुक्त(net, next_destid);
		rio_update_route_tables(net);
		rio_clear_locks(net);
		rio_pw_enable(mport, 1);
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_INFO "RIO: master port %d link inactive\n",
		       mport->id);
		rc = -EINVAL;
	पूर्ण

      out:
	वापस rc;
पूर्ण

/**
 * rio_build_route_tables- Generate route tables from चयन route entries
 * @net: RIO network to run route tables scan on
 *
 * For each चयन device, generate a route table by copying existing
 * route entries from the चयन.
 */
अटल व्योम rio_build_route_tables(काष्ठा rio_net *net)
अणु
	काष्ठा rio_चयन *rचयन;
	काष्ठा rio_dev *rdev;
	पूर्णांक i;
	u8 sport;

	list_क्रम_each_entry(rचयन, &net->चयनes, node) अणु
		rdev = sw_to_rio_dev(rचयन);

		rio_lock_device(net->hport, rdev->destid,
				rdev->hopcount, 1000);
		क्रम (i = 0;
		     i < RIO_MAX_ROUTE_ENTRIES(net->hport->sys_size);
		     i++) अणु
			अगर (rio_route_get_entry(rdev, RIO_GLOBAL_TABLE,
						i, &sport, 0) < 0)
				जारी;
			rचयन->route_table[i] = sport;
		पूर्ण

		rio_unlock_device(net->hport, rdev->destid, rdev->hopcount);
	पूर्ण
पूर्ण

/**
 * rio_disc_mport- Start discovery through a master port
 * @mport: Master port to send transactions
 * @flags: discovery control flags
 *
 * Starts the discovery process. If we have an active link,
 * then रुको क्रम the संकेत that क्रमागतeration is complete (अगर रुको
 * is allowed).
 * When क्रमागतeration completion is संकेतed, start recursive
 * peer discovery. Returns %0 अगर discovery succeeds or %-EBUSY
 * on failure.
 */
अटल पूर्णांक rio_disc_mport(काष्ठा rio_mport *mport, u32 flags)
अणु
	काष्ठा rio_net *net = शून्य;
	अचिन्हित दीर्घ to_end;

	prपूर्णांकk(KERN_INFO "RIO: discover master port %d, %s\n", mport->id,
	       mport->name);

	/* If master port has an active link, allocate net and discover peers */
	अगर (rio_mport_is_active(mport)) अणु
		अगर (rio_क्रमागत_complete(mport))
			जाओ क्रमागत_करोne;
		अन्यथा अगर (flags & RIO_SCAN_ENUM_NO_WAIT)
			वापस -EAGAIN;

		pr_debug("RIO: wait for enumeration to complete...\n");

		to_end = jअगरfies + CONFIG_RAPIDIO_DISC_TIMEOUT * HZ;
		जबतक (समय_beक्रमe(jअगरfies, to_end)) अणु
			अगर (rio_क्रमागत_complete(mport))
				जाओ क्रमागत_करोne;
			msleep(10);
		पूर्ण

		pr_debug("RIO: discovery timeout on mport %d %s\n",
			 mport->id, mport->name);
		जाओ bail;
क्रमागत_करोne:
		pr_debug("RIO: ... enumeration done\n");

		net = rio_scan_alloc_net(mport, 0, 0);
		अगर (!net) अणु
			prपूर्णांकk(KERN_ERR "RIO: Failed to allocate new net\n");
			जाओ bail;
		पूर्ण

		/* Read DestID asचिन्हित by क्रमागतerator */
		rio_local_पढ़ो_config_32(mport, RIO_DID_CSR,
					 &mport->host_deviceid);
		mport->host_deviceid = RIO_GET_DID(mport->sys_size,
						   mport->host_deviceid);

		अगर (rio_disc_peer(net, mport, RIO_ANY_DESTID(mport->sys_size),
					0, शून्य, 0) < 0) अणु
			prपूर्णांकk(KERN_INFO
			       "RIO: master port %d device has failed discovery\n",
			       mport->id);
			जाओ bail;
		पूर्ण

		rio_build_route_tables(net);
	पूर्ण

	वापस 0;
bail:
	वापस -EBUSY;
पूर्ण

अटल काष्ठा rio_scan rio_scan_ops = अणु
	.owner = THIS_MODULE,
	.क्रमागतerate = rio_क्रमागत_mport,
	.discover = rio_disc_mport,
पूर्ण;

अटल bool scan;
module_param(scan, bool, 0);
MODULE_PARM_DESC(scan, "Start RapidIO network enumeration/discovery "
			"(default = 0)");

/**
 * rio_basic_attach:
 *
 * When this क्रमागतeration/discovery method is loaded as a module this function
 * रेजिस्टरs its specअगरic क्रमागतeration and discover routines क्रम all available
 * RapidIO mport devices. The "scan" command line parameter controls ability of
 * the module to start RapidIO क्रमागतeration/discovery स्वतःmatically.
 *
 * Returns 0 क्रम success or -EIO अगर unable to रेजिस्टर itself.
 *
 * This क्रमागतeration/discovery method cannot be unloaded and thereक्रमe करोes not
 * provide a matching cleanup_module routine.
 */

अटल पूर्णांक __init rio_basic_attach(व्योम)
अणु
	अगर (rio_रेजिस्टर_scan(RIO_MPORT_ANY, &rio_scan_ops))
		वापस -EIO;
	अगर (scan)
		rio_init_mports();
	वापस 0;
पूर्ण

late_initcall(rio_basic_attach);

MODULE_DESCRIPTION("Basic RapidIO enumeration/discovery");
MODULE_LICENSE("GPL");
