<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * RapidIO पूर्णांकerconnect services
 * (RapidIO Interconnect Specअगरication, http://www.rapidio.org)
 *
 * Copyright 2005 MontaVista Software, Inc.
 * Matt Porter <mporter@kernel.crashing.org>
 *
 * Copyright 2009 - 2013 Integrated Device Technology, Inc.
 * Alex Bounine <alexandre.bounine@idt.com>
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>

#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/rपन.स>
#समावेश <linux/rio_drv.h>
#समावेश <linux/rio_ids.h>
#समावेश <linux/rio_regs.h>
#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश "rio.h"

/*
 * काष्ठा rio_pग_लिखो - RIO portग_लिखो event
 * @node:    Node in list of करोorbell events
 * @pwcback: Doorbell event callback
 * @context: Handler specअगरic context to pass on event
 */
काष्ठा rio_pग_लिखो अणु
	काष्ठा list_head node;

	पूर्णांक (*pwcback)(काष्ठा rio_mport *mport, व्योम *context,
		       जोड़ rio_pw_msg *msg, पूर्णांक step);
	व्योम *context;
पूर्ण;

MODULE_DESCRIPTION("RapidIO Subsystem Core");
MODULE_AUTHOR("Matt Porter <mporter@kernel.crashing.org>");
MODULE_AUTHOR("Alexandre Bounine <alexandre.bounine@idt.com>");
MODULE_LICENSE("GPL");

अटल पूर्णांक hdid[RIO_MAX_MPORTS];
अटल पूर्णांक ids_num;
module_param_array(hdid, पूर्णांक, &ids_num, 0);
MODULE_PARM_DESC(hdid,
	"Destination ID assignment to local RapidIO controllers");

अटल LIST_HEAD(rio_devices);
अटल LIST_HEAD(rio_nets);
अटल DEFINE_SPINLOCK(rio_global_list_lock);

अटल LIST_HEAD(rio_mports);
अटल LIST_HEAD(rio_scans);
अटल DEFINE_MUTEX(rio_mport_list_lock);
अटल अचिन्हित अक्षर next_portid;
अटल DEFINE_SPINLOCK(rio_mmap_lock);

/**
 * rio_local_get_device_id - Get the base/extended device id क्रम a port
 * @port: RIO master port from which to get the deviceid
 *
 * Reads the base/extended device id from the local device
 * implementing the master port. Returns the 8/16-bit device
 * id.
 */
u16 rio_local_get_device_id(काष्ठा rio_mport *port)
अणु
	u32 result;

	rio_local_पढ़ो_config_32(port, RIO_DID_CSR, &result);

	वापस (RIO_GET_DID(port->sys_size, result));
पूर्ण
EXPORT_SYMBOL_GPL(rio_local_get_device_id);

/**
 * rio_query_mport - Query mport device attributes
 * @port: mport device to query
 * @mport_attr: mport attributes data काष्ठाure
 *
 * Returns attributes of specअगरied mport through the
 * poपूर्णांकer to attributes data काष्ठाure.
 */
पूर्णांक rio_query_mport(काष्ठा rio_mport *port,
		    काष्ठा rio_mport_attr *mport_attr)
अणु
	अगर (!port->ops->query_mport)
		वापस -ENODATA;
	वापस port->ops->query_mport(port, mport_attr);
पूर्ण
EXPORT_SYMBOL(rio_query_mport);

/**
 * rio_alloc_net- Allocate and initialize a new RIO network data काष्ठाure
 * @mport: Master port associated with the RIO network
 *
 * Allocates a RIO network काष्ठाure, initializes per-network
 * list heads, and adds the associated master port to the
 * network list of associated master ports. Returns a
 * RIO network poपूर्णांकer on success or %शून्य on failure.
 */
काष्ठा rio_net *rio_alloc_net(काष्ठा rio_mport *mport)
अणु
	काष्ठा rio_net *net = kzalloc(माप(*net), GFP_KERNEL);

	अगर (net) अणु
		INIT_LIST_HEAD(&net->node);
		INIT_LIST_HEAD(&net->devices);
		INIT_LIST_HEAD(&net->चयनes);
		INIT_LIST_HEAD(&net->mports);
		mport->net = net;
	पूर्ण
	वापस net;
पूर्ण
EXPORT_SYMBOL_GPL(rio_alloc_net);

पूर्णांक rio_add_net(काष्ठा rio_net *net)
अणु
	पूर्णांक err;

	err = device_रेजिस्टर(&net->dev);
	अगर (err)
		वापस err;
	spin_lock(&rio_global_list_lock);
	list_add_tail(&net->node, &rio_nets);
	spin_unlock(&rio_global_list_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rio_add_net);

व्योम rio_मुक्त_net(काष्ठा rio_net *net)
अणु
	spin_lock(&rio_global_list_lock);
	अगर (!list_empty(&net->node))
		list_del(&net->node);
	spin_unlock(&rio_global_list_lock);
	अगर (net->release)
		net->release(net);
	device_unरेजिस्टर(&net->dev);
पूर्ण
EXPORT_SYMBOL_GPL(rio_मुक्त_net);

/**
 * rio_local_set_device_id - Set the base/extended device id क्रम a port
 * @port: RIO master port
 * @did: Device ID value to be written
 *
 * Writes the base/extended device id from a device.
 */
व्योम rio_local_set_device_id(काष्ठा rio_mport *port, u16 did)
अणु
	rio_local_ग_लिखो_config_32(port, RIO_DID_CSR,
				  RIO_SET_DID(port->sys_size, did));
पूर्ण
EXPORT_SYMBOL_GPL(rio_local_set_device_id);

/**
 * rio_add_device- Adds a RIO device to the device model
 * @rdev: RIO device
 *
 * Adds the RIO device to the global device list and adds the RIO
 * device to the RIO device list.  Creates the generic sysfs nodes
 * क्रम an RIO device.
 */
पूर्णांक rio_add_device(काष्ठा rio_dev *rdev)
अणु
	पूर्णांक err;

	atomic_set(&rdev->state, RIO_DEVICE_RUNNING);
	err = device_रेजिस्टर(&rdev->dev);
	अगर (err)
		वापस err;

	spin_lock(&rio_global_list_lock);
	list_add_tail(&rdev->global_list, &rio_devices);
	अगर (rdev->net) अणु
		list_add_tail(&rdev->net_list, &rdev->net->devices);
		अगर (rdev->pef & RIO_PEF_SWITCH)
			list_add_tail(&rdev->rचयन->node,
				      &rdev->net->चयनes);
	पूर्ण
	spin_unlock(&rio_global_list_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rio_add_device);

/*
 * rio_del_device - हटाओs a RIO device from the device model
 * @rdev: RIO device
 * @state: device state to set during removal process
 *
 * Removes the RIO device to the kernel device list and subप्रणाली's device list.
 * Clears sysfs entries क्रम the हटाओd device.
 */
व्योम rio_del_device(काष्ठा rio_dev *rdev, क्रमागत rio_device_state state)
अणु
	pr_debug("RIO: %s: removing %s\n", __func__, rio_name(rdev));
	atomic_set(&rdev->state, state);
	spin_lock(&rio_global_list_lock);
	list_del(&rdev->global_list);
	अगर (rdev->net) अणु
		list_del(&rdev->net_list);
		अगर (rdev->pef & RIO_PEF_SWITCH) अणु
			list_del(&rdev->rचयन->node);
			kमुक्त(rdev->rचयन->route_table);
		पूर्ण
	पूर्ण
	spin_unlock(&rio_global_list_lock);
	device_unरेजिस्टर(&rdev->dev);
पूर्ण
EXPORT_SYMBOL_GPL(rio_del_device);

/**
 * rio_request_inb_mbox - request inbound mailbox service
 * @mport: RIO master port from which to allocate the mailbox resource
 * @dev_id: Device specअगरic poपूर्णांकer to pass on event
 * @mbox: Mailbox number to claim
 * @entries: Number of entries in inbound mailbox queue
 * @minb: Callback to execute when inbound message is received
 *
 * Requests ownership of an inbound mailbox resource and binds
 * a callback function to the resource. Returns %0 on success.
 */
पूर्णांक rio_request_inb_mbox(काष्ठा rio_mport *mport,
			 व्योम *dev_id,
			 पूर्णांक mbox,
			 पूर्णांक entries,
			 व्योम (*minb) (काष्ठा rio_mport * mport, व्योम *dev_id, पूर्णांक mbox,
				       पूर्णांक slot))
अणु
	पूर्णांक rc = -ENOSYS;
	काष्ठा resource *res;

	अगर (!mport->ops->खोलो_inb_mbox)
		जाओ out;

	res = kzalloc(माप(*res), GFP_KERNEL);
	अगर (res) अणु
		rio_init_mbox_res(res, mbox, mbox);

		/* Make sure this mailbox isn't in use */
		rc = request_resource(&mport->riores[RIO_INB_MBOX_RESOURCE],
				      res);
		अगर (rc < 0) अणु
			kमुक्त(res);
			जाओ out;
		पूर्ण

		mport->inb_msg[mbox].res = res;

		/* Hook the inbound message callback */
		mport->inb_msg[mbox].mcback = minb;

		rc = mport->ops->खोलो_inb_mbox(mport, dev_id, mbox, entries);
		अगर (rc) अणु
			mport->inb_msg[mbox].mcback = शून्य;
			mport->inb_msg[mbox].res = शून्य;
			release_resource(res);
			kमुक्त(res);
		पूर्ण
	पूर्ण अन्यथा
		rc = -ENOMEM;

      out:
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(rio_request_inb_mbox);

/**
 * rio_release_inb_mbox - release inbound mailbox message service
 * @mport: RIO master port from which to release the mailbox resource
 * @mbox: Mailbox number to release
 *
 * Releases ownership of an inbound mailbox resource. Returns 0
 * अगर the request has been satisfied.
 */
पूर्णांक rio_release_inb_mbox(काष्ठा rio_mport *mport, पूर्णांक mbox)
अणु
	पूर्णांक rc;

	अगर (!mport->ops->बंद_inb_mbox || !mport->inb_msg[mbox].res)
		वापस -EINVAL;

	mport->ops->बंद_inb_mbox(mport, mbox);
	mport->inb_msg[mbox].mcback = शून्य;

	rc = release_resource(mport->inb_msg[mbox].res);
	अगर (rc)
		वापस rc;

	kमुक्त(mport->inb_msg[mbox].res);
	mport->inb_msg[mbox].res = शून्य;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rio_release_inb_mbox);

/**
 * rio_request_outb_mbox - request outbound mailbox service
 * @mport: RIO master port from which to allocate the mailbox resource
 * @dev_id: Device specअगरic poपूर्णांकer to pass on event
 * @mbox: Mailbox number to claim
 * @entries: Number of entries in outbound mailbox queue
 * @moutb: Callback to execute when outbound message is sent
 *
 * Requests ownership of an outbound mailbox resource and binds
 * a callback function to the resource. Returns 0 on success.
 */
पूर्णांक rio_request_outb_mbox(काष्ठा rio_mport *mport,
			  व्योम *dev_id,
			  पूर्णांक mbox,
			  पूर्णांक entries,
			  व्योम (*moutb) (काष्ठा rio_mport * mport, व्योम *dev_id, पूर्णांक mbox, पूर्णांक slot))
अणु
	पूर्णांक rc = -ENOSYS;
	काष्ठा resource *res;

	अगर (!mport->ops->खोलो_outb_mbox)
		जाओ out;

	res = kzalloc(माप(*res), GFP_KERNEL);
	अगर (res) अणु
		rio_init_mbox_res(res, mbox, mbox);

		/* Make sure this outbound mailbox isn't in use */
		rc = request_resource(&mport->riores[RIO_OUTB_MBOX_RESOURCE],
				      res);
		अगर (rc < 0) अणु
			kमुक्त(res);
			जाओ out;
		पूर्ण

		mport->outb_msg[mbox].res = res;

		/* Hook the inbound message callback */
		mport->outb_msg[mbox].mcback = moutb;

		rc = mport->ops->खोलो_outb_mbox(mport, dev_id, mbox, entries);
		अगर (rc) अणु
			mport->outb_msg[mbox].mcback = शून्य;
			mport->outb_msg[mbox].res = शून्य;
			release_resource(res);
			kमुक्त(res);
		पूर्ण
	पूर्ण अन्यथा
		rc = -ENOMEM;

      out:
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(rio_request_outb_mbox);

/**
 * rio_release_outb_mbox - release outbound mailbox message service
 * @mport: RIO master port from which to release the mailbox resource
 * @mbox: Mailbox number to release
 *
 * Releases ownership of an inbound mailbox resource. Returns 0
 * अगर the request has been satisfied.
 */
पूर्णांक rio_release_outb_mbox(काष्ठा rio_mport *mport, पूर्णांक mbox)
अणु
	पूर्णांक rc;

	अगर (!mport->ops->बंद_outb_mbox || !mport->outb_msg[mbox].res)
		वापस -EINVAL;

	mport->ops->बंद_outb_mbox(mport, mbox);
	mport->outb_msg[mbox].mcback = शून्य;

	rc = release_resource(mport->outb_msg[mbox].res);
	अगर (rc)
		वापस rc;

	kमुक्त(mport->outb_msg[mbox].res);
	mport->outb_msg[mbox].res = शून्य;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rio_release_outb_mbox);

/**
 * rio_setup_inb_dbell - bind inbound करोorbell callback
 * @mport: RIO master port to bind the करोorbell callback
 * @dev_id: Device specअगरic poपूर्णांकer to pass on event
 * @res: Doorbell message resource
 * @dinb: Callback to execute when करोorbell is received
 *
 * Adds a करोorbell resource/callback pair पूर्णांकo a port's
 * करोorbell event list. Returns 0 अगर the request has been
 * satisfied.
 */
अटल पूर्णांक
rio_setup_inb_dbell(काष्ठा rio_mport *mport, व्योम *dev_id, काष्ठा resource *res,
		    व्योम (*dinb) (काष्ठा rio_mport * mport, व्योम *dev_id, u16 src, u16 dst,
				  u16 info))
अणु
	काष्ठा rio_dbell *dbell = kदो_स्मृति(माप(*dbell), GFP_KERNEL);

	अगर (!dbell)
		वापस -ENOMEM;

	dbell->res = res;
	dbell->dinb = dinb;
	dbell->dev_id = dev_id;

	mutex_lock(&mport->lock);
	list_add_tail(&dbell->node, &mport->dbells);
	mutex_unlock(&mport->lock);
	वापस 0;
पूर्ण

/**
 * rio_request_inb_dbell - request inbound करोorbell message service
 * @mport: RIO master port from which to allocate the करोorbell resource
 * @dev_id: Device specअगरic poपूर्णांकer to pass on event
 * @start: Doorbell info range start
 * @end: Doorbell info range end
 * @dinb: Callback to execute when करोorbell is received
 *
 * Requests ownership of an inbound करोorbell resource and binds
 * a callback function to the resource. Returns 0 अगर the request
 * has been satisfied.
 */
पूर्णांक rio_request_inb_dbell(काष्ठा rio_mport *mport,
			  व्योम *dev_id,
			  u16 start,
			  u16 end,
			  व्योम (*dinb) (काष्ठा rio_mport * mport, व्योम *dev_id, u16 src,
					u16 dst, u16 info))
अणु
	पूर्णांक rc;
	काष्ठा resource *res = kzalloc(माप(*res), GFP_KERNEL);

	अगर (res) अणु
		rio_init_dbell_res(res, start, end);

		/* Make sure these करोorbells aren't in use */
		rc = request_resource(&mport->riores[RIO_DOORBELL_RESOURCE],
				      res);
		अगर (rc < 0) अणु
			kमुक्त(res);
			जाओ out;
		पूर्ण

		/* Hook the करोorbell callback */
		rc = rio_setup_inb_dbell(mport, dev_id, res, dinb);
	पूर्ण अन्यथा
		rc = -ENOMEM;

      out:
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(rio_request_inb_dbell);

/**
 * rio_release_inb_dbell - release inbound करोorbell message service
 * @mport: RIO master port from which to release the करोorbell resource
 * @start: Doorbell info range start
 * @end: Doorbell info range end
 *
 * Releases ownership of an inbound करोorbell resource and हटाओs
 * callback from the करोorbell event list. Returns 0 अगर the request
 * has been satisfied.
 */
पूर्णांक rio_release_inb_dbell(काष्ठा rio_mport *mport, u16 start, u16 end)
अणु
	पूर्णांक rc = 0, found = 0;
	काष्ठा rio_dbell *dbell;

	mutex_lock(&mport->lock);
	list_क्रम_each_entry(dbell, &mport->dbells, node) अणु
		अगर ((dbell->res->start == start) && (dbell->res->end == end)) अणु
			list_del(&dbell->node);
			found = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&mport->lock);

	/* If we can't find an exact match, fail */
	अगर (!found) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	/* Release the करोorbell resource */
	rc = release_resource(dbell->res);

	/* Free the करोorbell event */
	kमुक्त(dbell);

      out:
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(rio_release_inb_dbell);

/**
 * rio_request_outb_dbell - request outbound करोorbell message range
 * @rdev: RIO device from which to allocate the करोorbell resource
 * @start: Doorbell message range start
 * @end: Doorbell message range end
 *
 * Requests ownership of a करोorbell message range. Returns a resource
 * अगर the request has been satisfied or %शून्य on failure.
 */
काष्ठा resource *rio_request_outb_dbell(काष्ठा rio_dev *rdev, u16 start,
					u16 end)
अणु
	काष्ठा resource *res = kzalloc(माप(काष्ठा resource), GFP_KERNEL);

	अगर (res) अणु
		rio_init_dbell_res(res, start, end);

		/* Make sure these करोorbells aren't in use */
		अगर (request_resource(&rdev->riores[RIO_DOORBELL_RESOURCE], res)
		    < 0) अणु
			kमुक्त(res);
			res = शून्य;
		पूर्ण
	पूर्ण

	वापस res;
पूर्ण
EXPORT_SYMBOL_GPL(rio_request_outb_dbell);

/**
 * rio_release_outb_dbell - release outbound करोorbell message range
 * @rdev: RIO device from which to release the करोorbell resource
 * @res: Doorbell resource to be मुक्तd
 *
 * Releases ownership of a करोorbell message range. Returns 0 अगर the
 * request has been satisfied.
 */
पूर्णांक rio_release_outb_dbell(काष्ठा rio_dev *rdev, काष्ठा resource *res)
अणु
	पूर्णांक rc = release_resource(res);

	kमुक्त(res);

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(rio_release_outb_dbell);

/**
 * rio_add_mport_pw_handler - add port-ग_लिखो message handler पूर्णांकo the list
 *                            of mport specअगरic pw handlers
 * @mport:   RIO master port to bind the portग_लिखो callback
 * @context: Handler specअगरic context to pass on event
 * @pwcback: Callback to execute when portग_लिखो is received
 *
 * Returns 0 अगर the request has been satisfied.
 */
पूर्णांक rio_add_mport_pw_handler(काष्ठा rio_mport *mport, व्योम *context,
			     पूर्णांक (*pwcback)(काष्ठा rio_mport *mport,
			     व्योम *context, जोड़ rio_pw_msg *msg, पूर्णांक step))
अणु
	काष्ठा rio_pग_लिखो *pग_लिखो = kzalloc(माप(*pग_लिखो), GFP_KERNEL);

	अगर (!pग_लिखो)
		वापस -ENOMEM;

	pग_लिखो->pwcback = pwcback;
	pग_लिखो->context = context;
	mutex_lock(&mport->lock);
	list_add_tail(&pग_लिखो->node, &mport->pग_लिखोs);
	mutex_unlock(&mport->lock);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rio_add_mport_pw_handler);

/**
 * rio_del_mport_pw_handler - हटाओ port-ग_लिखो message handler from the list
 *                            of mport specअगरic pw handlers
 * @mport:   RIO master port to bind the portग_लिखो callback
 * @context: Registered handler specअगरic context to pass on event
 * @pwcback: Registered callback function
 *
 * Returns 0 अगर the request has been satisfied.
 */
पूर्णांक rio_del_mport_pw_handler(काष्ठा rio_mport *mport, व्योम *context,
			     पूर्णांक (*pwcback)(काष्ठा rio_mport *mport,
			     व्योम *context, जोड़ rio_pw_msg *msg, पूर्णांक step))
अणु
	पूर्णांक rc = -EINVAL;
	काष्ठा rio_pग_लिखो *pग_लिखो;

	mutex_lock(&mport->lock);
	list_क्रम_each_entry(pग_लिखो, &mport->pग_लिखोs, node) अणु
		अगर (pग_लिखो->pwcback == pwcback && pग_लिखो->context == context) अणु
			list_del(&pग_लिखो->node);
			kमुक्त(pग_लिखो);
			rc = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&mport->lock);

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(rio_del_mport_pw_handler);

/**
 * rio_request_inb_pग_लिखो - request inbound port-ग_लिखो message service क्रम
 *                          specअगरic RapidIO device
 * @rdev: RIO device to which रेजिस्टर inbound port-ग_लिखो callback routine
 * @pwcback: Callback routine to execute when port-ग_लिखो is received
 *
 * Binds a port-ग_लिखो callback function to the RapidIO device.
 * Returns 0 अगर the request has been satisfied.
 */
पूर्णांक rio_request_inb_pग_लिखो(काष्ठा rio_dev *rdev,
	पूर्णांक (*pwcback)(काष्ठा rio_dev *rdev, जोड़ rio_pw_msg *msg, पूर्णांक step))
अणु
	पूर्णांक rc = 0;

	spin_lock(&rio_global_list_lock);
	अगर (rdev->pwcback)
		rc = -ENOMEM;
	अन्यथा
		rdev->pwcback = pwcback;

	spin_unlock(&rio_global_list_lock);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(rio_request_inb_pग_लिखो);

/**
 * rio_release_inb_pग_लिखो - release inbound port-ग_लिखो message service
 *                          associated with specअगरic RapidIO device
 * @rdev: RIO device which रेजिस्टरed क्रम inbound port-ग_लिखो callback
 *
 * Removes callback from the rio_dev काष्ठाure. Returns 0 अगर the request
 * has been satisfied.
 */
पूर्णांक rio_release_inb_pग_लिखो(काष्ठा rio_dev *rdev)
अणु
	पूर्णांक rc = -ENOMEM;

	spin_lock(&rio_global_list_lock);
	अगर (rdev->pwcback) अणु
		rdev->pwcback = शून्य;
		rc = 0;
	पूर्ण

	spin_unlock(&rio_global_list_lock);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(rio_release_inb_pग_लिखो);

/**
 * rio_pw_enable - Enables/disables port-ग_लिखो handling by a master port
 * @mport: Master port associated with port-ग_लिखो handling
 * @enable:  1=enable,  0=disable
 */
व्योम rio_pw_enable(काष्ठा rio_mport *mport, पूर्णांक enable)
अणु
	अगर (mport->ops->pwenable) अणु
		mutex_lock(&mport->lock);

		अगर ((enable && ++mport->pwe_refcnt == 1) ||
		    (!enable && mport->pwe_refcnt && --mport->pwe_refcnt == 0))
			mport->ops->pwenable(mport, enable);
		mutex_unlock(&mport->lock);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(rio_pw_enable);

/**
 * rio_map_inb_region -- Map inbound memory region.
 * @mport: Master port.
 * @local: physical address of memory region to be mapped
 * @rbase: RIO base address asचिन्हित to this winकरोw
 * @size: Size of the memory region
 * @rflags: Flags क्रम mapping.
 *
 * Return: 0 -- Success.
 *
 * This function will create the mapping from RIO space to local memory.
 */
पूर्णांक rio_map_inb_region(काष्ठा rio_mport *mport, dma_addr_t local,
			u64 rbase, u32 size, u32 rflags)
अणु
	पूर्णांक rc;
	अचिन्हित दीर्घ flags;

	अगर (!mport->ops->map_inb)
		वापस -1;
	spin_lock_irqsave(&rio_mmap_lock, flags);
	rc = mport->ops->map_inb(mport, local, rbase, size, rflags);
	spin_unlock_irqrestore(&rio_mmap_lock, flags);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(rio_map_inb_region);

/**
 * rio_unmap_inb_region -- Unmap the inbound memory region
 * @mport: Master port
 * @lstart: physical address of memory region to be unmapped
 */
व्योम rio_unmap_inb_region(काष्ठा rio_mport *mport, dma_addr_t lstart)
अणु
	अचिन्हित दीर्घ flags;
	अगर (!mport->ops->unmap_inb)
		वापस;
	spin_lock_irqsave(&rio_mmap_lock, flags);
	mport->ops->unmap_inb(mport, lstart);
	spin_unlock_irqrestore(&rio_mmap_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(rio_unmap_inb_region);

/**
 * rio_map_outb_region -- Map outbound memory region.
 * @mport: Master port.
 * @destid: destination id winकरोw poपूर्णांकs to
 * @rbase: RIO base address winकरोw translates to
 * @size: Size of the memory region
 * @rflags: Flags क्रम mapping.
 * @local: physical address of memory region mapped
 *
 * Return: 0 -- Success.
 *
 * This function will create the mapping from RIO space to local memory.
 */
पूर्णांक rio_map_outb_region(काष्ठा rio_mport *mport, u16 destid, u64 rbase,
			u32 size, u32 rflags, dma_addr_t *local)
अणु
	पूर्णांक rc;
	अचिन्हित दीर्घ flags;

	अगर (!mport->ops->map_outb)
		वापस -ENODEV;

	spin_lock_irqsave(&rio_mmap_lock, flags);
	rc = mport->ops->map_outb(mport, destid, rbase, size,
		rflags, local);
	spin_unlock_irqrestore(&rio_mmap_lock, flags);

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(rio_map_outb_region);

/**
 * rio_unmap_outb_region -- Unmap the inbound memory region
 * @mport: Master port
 * @destid: destination id mapping poपूर्णांकs to
 * @rstart: RIO base address winकरोw translates to
 */
व्योम rio_unmap_outb_region(काष्ठा rio_mport *mport, u16 destid, u64 rstart)
अणु
	अचिन्हित दीर्घ flags;

	अगर (!mport->ops->unmap_outb)
		वापस;

	spin_lock_irqsave(&rio_mmap_lock, flags);
	mport->ops->unmap_outb(mport, destid, rstart);
	spin_unlock_irqrestore(&rio_mmap_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(rio_unmap_outb_region);

/**
 * rio_mport_get_physefb - Helper function that वापसs रेजिस्टर offset
 *                      क्रम Physical Layer Extended Features Block.
 * @port: Master port to issue transaction
 * @local: Indicate a local master port or remote device access
 * @destid: Destination ID of the device
 * @hopcount: Number of चयन hops to the device
 * @rmap: poपूर्णांकer to location to store रेजिस्टर map type info
 */
u32
rio_mport_get_physefb(काष्ठा rio_mport *port, पूर्णांक local,
		      u16 destid, u8 hopcount, u32 *rmap)
अणु
	u32 ext_ftr_ptr;
	u32 ftr_header;

	ext_ftr_ptr = rio_mport_get_efb(port, local, destid, hopcount, 0);

	जबतक (ext_ftr_ptr)  अणु
		अगर (local)
			rio_local_पढ़ो_config_32(port, ext_ftr_ptr,
						 &ftr_header);
		अन्यथा
			rio_mport_पढ़ो_config_32(port, destid, hopcount,
						 ext_ftr_ptr, &ftr_header);

		ftr_header = RIO_GET_BLOCK_ID(ftr_header);
		चयन (ftr_header) अणु

		हाल RIO_EFB_SER_EP_ID:
		हाल RIO_EFB_SER_EP_REC_ID:
		हाल RIO_EFB_SER_EP_FREE_ID:
		हाल RIO_EFB_SER_EP_M1_ID:
		हाल RIO_EFB_SER_EP_SW_M1_ID:
		हाल RIO_EFB_SER_EPF_M1_ID:
		हाल RIO_EFB_SER_EPF_SW_M1_ID:
			*rmap = 1;
			वापस ext_ftr_ptr;

		हाल RIO_EFB_SER_EP_M2_ID:
		हाल RIO_EFB_SER_EP_SW_M2_ID:
		हाल RIO_EFB_SER_EPF_M2_ID:
		हाल RIO_EFB_SER_EPF_SW_M2_ID:
			*rmap = 2;
			वापस ext_ftr_ptr;

		शेष:
			अवरोध;
		पूर्ण

		ext_ftr_ptr = rio_mport_get_efb(port, local, destid,
						hopcount, ext_ftr_ptr);
	पूर्ण

	वापस ext_ftr_ptr;
पूर्ण
EXPORT_SYMBOL_GPL(rio_mport_get_physefb);

/**
 * rio_get_comptag - Begin or जारी searching क्रम a RIO device by component tag
 * @comp_tag: RIO component tag to match
 * @from: Previous RIO device found in search, or %शून्य क्रम new search
 *
 * Iterates through the list of known RIO devices. If a RIO device is
 * found with a matching @comp_tag, a poपूर्णांकer to its device
 * काष्ठाure is वापसed. Otherwise, %शून्य is वापसed. A new search
 * is initiated by passing %शून्य to the @from argument. Otherwise, अगर
 * @from is not %शून्य, searches जारी from next device on the global
 * list.
 */
काष्ठा rio_dev *rio_get_comptag(u32 comp_tag, काष्ठा rio_dev *from)
अणु
	काष्ठा list_head *n;
	काष्ठा rio_dev *rdev;

	spin_lock(&rio_global_list_lock);
	n = from ? from->global_list.next : rio_devices.next;

	जबतक (n && (n != &rio_devices)) अणु
		rdev = rio_dev_g(n);
		अगर (rdev->comp_tag == comp_tag)
			जाओ निकास;
		n = n->next;
	पूर्ण
	rdev = शून्य;
निकास:
	spin_unlock(&rio_global_list_lock);
	वापस rdev;
पूर्ण
EXPORT_SYMBOL_GPL(rio_get_comptag);

/**
 * rio_set_port_lockout - Sets/clears LOCKOUT bit (RIO EM 1.3) क्रम a चयन port.
 * @rdev: Poपूर्णांकer to RIO device control काष्ठाure
 * @pnum: Switch port number to set LOCKOUT bit
 * @lock: Operation : set (=1) or clear (=0)
 */
पूर्णांक rio_set_port_lockout(काष्ठा rio_dev *rdev, u32 pnum, पूर्णांक lock)
अणु
	u32 regval;

	rio_पढ़ो_config_32(rdev,
		RIO_DEV_PORT_N_CTL_CSR(rdev, pnum),
		&regval);
	अगर (lock)
		regval |= RIO_PORT_N_CTL_LOCKOUT;
	अन्यथा
		regval &= ~RIO_PORT_N_CTL_LOCKOUT;

	rio_ग_लिखो_config_32(rdev,
		RIO_DEV_PORT_N_CTL_CSR(rdev, pnum),
		regval);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rio_set_port_lockout);

/**
 * rio_enable_rx_tx_port - enable input receiver and output transmitter of
 * given port
 * @port: Master port associated with the RIO network
 * @local: local=1 select local port otherwise a far device is reached
 * @destid: Destination ID of the device to check host bit
 * @hopcount: Number of hops to reach the target
 * @port_num: Port (-number on चयन) to enable on a far end device
 *
 * Returns 0 or 1 from on General Control Command and Status Register
 * (EXT_PTR+0x3C)
 */
पूर्णांक rio_enable_rx_tx_port(काष्ठा rio_mport *port,
			  पूर्णांक local, u16 destid,
			  u8 hopcount, u8 port_num)
अणु
#अगर_घोषित CONFIG_RAPIDIO_ENABLE_RX_TX_PORTS
	u32 regval;
	u32 ext_ftr_ptr;
	u32 rmap;

	/*
	* enable rx input tx output port
	*/
	pr_debug("rio_enable_rx_tx_port(local = %d, destid = %d, hopcount = "
		 "%d, port_num = %d)\n", local, destid, hopcount, port_num);

	ext_ftr_ptr = rio_mport_get_physefb(port, local, destid,
					    hopcount, &rmap);

	अगर (local) अणु
		rio_local_पढ़ो_config_32(port,
				ext_ftr_ptr + RIO_PORT_N_CTL_CSR(0, rmap),
				&regval);
	पूर्ण अन्यथा अणु
		अगर (rio_mport_पढ़ो_config_32(port, destid, hopcount,
			ext_ftr_ptr + RIO_PORT_N_CTL_CSR(port_num, rmap),
				&regval) < 0)
			वापस -EIO;
	पूर्ण

	regval = regval | RIO_PORT_N_CTL_EN_RX | RIO_PORT_N_CTL_EN_TX;

	अगर (local) अणु
		rio_local_ग_लिखो_config_32(port,
			ext_ftr_ptr + RIO_PORT_N_CTL_CSR(0, rmap), regval);
	पूर्ण अन्यथा अणु
		अगर (rio_mport_ग_लिखो_config_32(port, destid, hopcount,
			ext_ftr_ptr + RIO_PORT_N_CTL_CSR(port_num, rmap),
				regval) < 0)
			वापस -EIO;
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rio_enable_rx_tx_port);


/**
 * rio_chk_dev_route - Validate route to the specअगरied device.
 * @rdev:  RIO device failed to respond
 * @nrdev: Last active device on the route to rdev
 * @npnum: nrdev's port number on the route to rdev
 *
 * Follows a route to the specअगरied RIO device to determine the last available
 * device (and corresponding RIO port) on the route.
 */
अटल पूर्णांक
rio_chk_dev_route(काष्ठा rio_dev *rdev, काष्ठा rio_dev **nrdev, पूर्णांक *npnum)
अणु
	u32 result;
	पूर्णांक p_port, rc = -EIO;
	काष्ठा rio_dev *prev = शून्य;

	/* Find चयन with failed RIO link */
	जबतक (rdev->prev && (rdev->prev->pef & RIO_PEF_SWITCH)) अणु
		अगर (!rio_पढ़ो_config_32(rdev->prev, RIO_DEV_ID_CAR, &result)) अणु
			prev = rdev->prev;
			अवरोध;
		पूर्ण
		rdev = rdev->prev;
	पूर्ण

	अगर (!prev)
		जाओ err_out;

	p_port = prev->rचयन->route_table[rdev->destid];

	अगर (p_port != RIO_INVALID_ROUTE) अणु
		pr_debug("RIO: link failed on [%s]-P%d\n",
			 rio_name(prev), p_port);
		*nrdev = prev;
		*npnum = p_port;
		rc = 0;
	पूर्ण अन्यथा
		pr_debug("RIO: failed to trace route to %s\n", rio_name(rdev));
err_out:
	वापस rc;
पूर्ण

/**
 * rio_mport_chk_dev_access - Validate access to the specअगरied device.
 * @mport: Master port to send transactions
 * @destid: Device destination ID in network
 * @hopcount: Number of hops पूर्णांकo the network
 */
पूर्णांक
rio_mport_chk_dev_access(काष्ठा rio_mport *mport, u16 destid, u8 hopcount)
अणु
	पूर्णांक i = 0;
	u32 पंचांगp;

	जबतक (rio_mport_पढ़ो_config_32(mport, destid, hopcount,
					RIO_DEV_ID_CAR, &पंचांगp)) अणु
		i++;
		अगर (i == RIO_MAX_CHK_RETRY)
			वापस -EIO;
		mdelay(1);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rio_mport_chk_dev_access);

/**
 * rio_chk_dev_access - Validate access to the specअगरied device.
 * @rdev: Poपूर्णांकer to RIO device control काष्ठाure
 */
अटल पूर्णांक rio_chk_dev_access(काष्ठा rio_dev *rdev)
अणु
	वापस rio_mport_chk_dev_access(rdev->net->hport,
					rdev->destid, rdev->hopcount);
पूर्ण

/**
 * rio_get_input_status - Sends a Link-Request/Input-Status control symbol and
 *                        वापसs link-response (अगर requested).
 * @rdev: RIO devive to issue Input-status command
 * @pnum: Device port number to issue the command
 * @lnkresp: Response from a link partner
 */
अटल पूर्णांक
rio_get_input_status(काष्ठा rio_dev *rdev, पूर्णांक pnum, u32 *lnkresp)
अणु
	u32 regval;
	पूर्णांक checkcount;

	अगर (lnkresp) अणु
		/* Read from link मुख्यtenance response रेजिस्टर
		 * to clear valid bit */
		rio_पढ़ो_config_32(rdev,
			RIO_DEV_PORT_N_MNT_RSP_CSR(rdev, pnum),
			&regval);
		udelay(50);
	पूर्ण

	/* Issue Input-status command */
	rio_ग_लिखो_config_32(rdev,
		RIO_DEV_PORT_N_MNT_REQ_CSR(rdev, pnum),
		RIO_MNT_REQ_CMD_IS);

	/* Exit अगर the response is not expected */
	अगर (!lnkresp)
		वापस 0;

	checkcount = 3;
	जबतक (checkcount--) अणु
		udelay(50);
		rio_पढ़ो_config_32(rdev,
			RIO_DEV_PORT_N_MNT_RSP_CSR(rdev, pnum),
			&regval);
		अगर (regval & RIO_PORT_N_MNT_RSP_RVAL) अणु
			*lnkresp = regval;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EIO;
पूर्ण

/**
 * rio_clr_err_stopped - Clears port Error-stopped states.
 * @rdev: Poपूर्णांकer to RIO device control काष्ठाure
 * @pnum: Switch port number to clear errors
 * @err_status: port error status (अगर 0 पढ़ोs रेजिस्टर from device)
 *
 * TODO: Currently this routine is not compatible with recovery process
 * specअगरied क्रम idt_gen3 RapidIO चयन devices. It has to be reviewed
 * to implement universal recovery process that is compatible full range
 * off available devices.
 * IDT gen3 चयन driver now implements HW-specअगरic error handler that
 * issues soft port reset to the port to reset ERR_STOP bits and ackIDs.
 */
अटल पूर्णांक rio_clr_err_stopped(काष्ठा rio_dev *rdev, u32 pnum, u32 err_status)
अणु
	काष्ठा rio_dev *nextdev = rdev->rचयन->nextdev[pnum];
	u32 regval;
	u32 far_ackid, far_linkstat, near_ackid;

	अगर (err_status == 0)
		rio_पढ़ो_config_32(rdev,
			RIO_DEV_PORT_N_ERR_STS_CSR(rdev, pnum),
			&err_status);

	अगर (err_status & RIO_PORT_N_ERR_STS_OUT_ES) अणु
		pr_debug("RIO_EM: servicing Output Error-Stopped state\n");
		/*
		 * Send a Link-Request/Input-Status control symbol
		 */
		अगर (rio_get_input_status(rdev, pnum, &regval)) अणु
			pr_debug("RIO_EM: Input-status response timeout\n");
			जाओ rd_err;
		पूर्ण

		pr_debug("RIO_EM: SP%d Input-status response=0x%08x\n",
			 pnum, regval);
		far_ackid = (regval & RIO_PORT_N_MNT_RSP_ASTAT) >> 5;
		far_linkstat = regval & RIO_PORT_N_MNT_RSP_LSTAT;
		rio_पढ़ो_config_32(rdev,
			RIO_DEV_PORT_N_ACK_STS_CSR(rdev, pnum),
			&regval);
		pr_debug("RIO_EM: SP%d_ACK_STS_CSR=0x%08x\n", pnum, regval);
		near_ackid = (regval & RIO_PORT_N_ACK_INBOUND) >> 24;
		pr_debug("RIO_EM: SP%d far_ackID=0x%02x far_linkstat=0x%02x" \
			 " near_ackID=0x%02x\n",
			pnum, far_ackid, far_linkstat, near_ackid);

		/*
		 * If required, synchronize ackIDs of near and
		 * far sides.
		 */
		अगर ((far_ackid != ((regval & RIO_PORT_N_ACK_OUTSTAND) >> 8)) ||
		    (far_ackid != (regval & RIO_PORT_N_ACK_OUTBOUND))) अणु
			/* Align near outstanding/outbound ackIDs with
			 * far inbound.
			 */
			rio_ग_लिखो_config_32(rdev,
				RIO_DEV_PORT_N_ACK_STS_CSR(rdev, pnum),
				(near_ackid << 24) |
					(far_ackid << 8) | far_ackid);
			/* Align far outstanding/outbound ackIDs with
			 * near inbound.
			 */
			far_ackid++;
			अगर (!nextdev) अणु
				pr_debug("RIO_EM: nextdev pointer == NULL\n");
				जाओ rd_err;
			पूर्ण

			rio_ग_लिखो_config_32(nextdev,
				RIO_DEV_PORT_N_ACK_STS_CSR(nextdev,
					RIO_GET_PORT_NUM(nextdev->swpinfo)),
				(far_ackid << 24) |
				(near_ackid << 8) | near_ackid);
		पूर्ण
rd_err:
		rio_पढ़ो_config_32(rdev, RIO_DEV_PORT_N_ERR_STS_CSR(rdev, pnum),
				   &err_status);
		pr_debug("RIO_EM: SP%d_ERR_STS_CSR=0x%08x\n", pnum, err_status);
	पूर्ण

	अगर ((err_status & RIO_PORT_N_ERR_STS_INP_ES) && nextdev) अणु
		pr_debug("RIO_EM: servicing Input Error-Stopped state\n");
		rio_get_input_status(nextdev,
				     RIO_GET_PORT_NUM(nextdev->swpinfo), शून्य);
		udelay(50);

		rio_पढ़ो_config_32(rdev, RIO_DEV_PORT_N_ERR_STS_CSR(rdev, pnum),
				   &err_status);
		pr_debug("RIO_EM: SP%d_ERR_STS_CSR=0x%08x\n", pnum, err_status);
	पूर्ण

	वापस (err_status & (RIO_PORT_N_ERR_STS_OUT_ES |
			      RIO_PORT_N_ERR_STS_INP_ES)) ? 1 : 0;
पूर्ण

/**
 * rio_inb_pग_लिखो_handler - inbound port-ग_लिखो message handler
 * @mport:  mport device associated with port-ग_लिखो
 * @pw_msg: poपूर्णांकer to inbound port-ग_लिखो message
 *
 * Processes an inbound port-ग_लिखो message. Returns 0 अगर the request
 * has been satisfied.
 */
पूर्णांक rio_inb_pग_लिखो_handler(काष्ठा rio_mport *mport, जोड़ rio_pw_msg *pw_msg)
अणु
	काष्ठा rio_dev *rdev;
	u32 err_status, em_perrdet, em_ltlerrdet;
	पूर्णांक rc, portnum;
	काष्ठा rio_pग_लिखो *pग_लिखो;

#अगर_घोषित DEBUG_PW
	अणु
		u32 i;

		pr_debug("%s: PW to mport_%d:\n", __func__, mport->id);
		क्रम (i = 0; i < RIO_PW_MSG_SIZE / माप(u32); i = i + 4) अणु
			pr_debug("0x%02x: %08x %08x %08x %08x\n",
				i * 4, pw_msg->raw[i], pw_msg->raw[i + 1],
				pw_msg->raw[i + 2], pw_msg->raw[i + 3]);
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	rdev = rio_get_comptag((pw_msg->em.comptag & RIO_CTAG_UDEVID), शून्य);
	अगर (rdev) अणु
		pr_debug("RIO: Port-Write message from %s\n", rio_name(rdev));
	पूर्ण अन्यथा अणु
		pr_debug("RIO: %s No matching device for CTag 0x%08x\n",
			__func__, pw_msg->em.comptag);
	पूर्ण

	/* Call a device-specअगरic handler (अगर it is रेजिस्टरed क्रम the device).
	 * This may be the service क्रम endpoपूर्णांकs that send device-specअगरic
	 * port-ग_लिखो messages. End-poपूर्णांक messages expected to be handled
	 * completely by EP specअगरic device driver.
	 * For चयनes rc==0 संकेतs that no standard processing required.
	 */
	अगर (rdev && rdev->pwcback) अणु
		rc = rdev->pwcback(rdev, pw_msg, 0);
		अगर (rc == 0)
			वापस 0;
	पूर्ण

	mutex_lock(&mport->lock);
	list_क्रम_each_entry(pग_लिखो, &mport->pग_लिखोs, node)
		pग_लिखो->pwcback(mport, pग_लिखो->context, pw_msg, 0);
	mutex_unlock(&mport->lock);

	अगर (!rdev)
		वापस 0;

	/*
	 * FIXME: The code below stays as it was beक्रमe क्रम now until we decide
	 * how to करो शेष PW handling in combination with per-mport callbacks
	 */

	portnum = pw_msg->em.is_port & 0xFF;

	/* Check अगर device and route to it are functional:
	 * Someबार devices may send PW message(s) just beक्रमe being
	 * घातered करोwn (or link being lost).
	 */
	अगर (rio_chk_dev_access(rdev)) अणु
		pr_debug("RIO: device access failed - get link partner\n");
		/* Scan route to the device and identअगरy failed link.
		 * This will replace device and port reported in PW message.
		 * PW message should not be used after this poपूर्णांक.
		 */
		अगर (rio_chk_dev_route(rdev, &rdev, &portnum)) अणु
			pr_err("RIO: Route trace for %s failed\n",
				rio_name(rdev));
			वापस -EIO;
		पूर्ण
		pw_msg = शून्य;
	पूर्ण

	/* For End-poपूर्णांक devices processing stops here */
	अगर (!(rdev->pef & RIO_PEF_SWITCH))
		वापस 0;

	अगर (rdev->phys_efptr == 0) अणु
		pr_err("RIO_PW: Bad switch initialization for %s\n",
			rio_name(rdev));
		वापस 0;
	पूर्ण

	/*
	 * Process the port-ग_लिखो notअगरication from चयन
	 */
	अगर (rdev->rचयन->ops && rdev->rचयन->ops->em_handle)
		rdev->rचयन->ops->em_handle(rdev, portnum);

	rio_पढ़ो_config_32(rdev, RIO_DEV_PORT_N_ERR_STS_CSR(rdev, portnum),
			   &err_status);
	pr_debug("RIO_PW: SP%d_ERR_STS_CSR=0x%08x\n", portnum, err_status);

	अगर (err_status & RIO_PORT_N_ERR_STS_PORT_OK) अणु

		अगर (!(rdev->rचयन->port_ok & (1 << portnum))) अणु
			rdev->rचयन->port_ok |= (1 << portnum);
			rio_set_port_lockout(rdev, portnum, 0);
			/* Schedule Insertion Service */
			pr_debug("RIO_PW: Device Insertion on [%s]-P%d\n",
			       rio_name(rdev), portnum);
		पूर्ण

		/* Clear error-stopped states (अगर reported).
		 * Depending on the link partner state, two attempts
		 * may be needed क्रम successful recovery.
		 */
		अगर (err_status & (RIO_PORT_N_ERR_STS_OUT_ES |
				  RIO_PORT_N_ERR_STS_INP_ES)) अणु
			अगर (rio_clr_err_stopped(rdev, portnum, err_status))
				rio_clr_err_stopped(rdev, portnum, 0);
		पूर्ण
	पूर्ण  अन्यथा अणु /* अगर (err_status & RIO_PORT_N_ERR_STS_PORT_UNINIT) */

		अगर (rdev->rचयन->port_ok & (1 << portnum)) अणु
			rdev->rचयन->port_ok &= ~(1 << portnum);
			rio_set_port_lockout(rdev, portnum, 1);

			अगर (rdev->phys_rmap == 1) अणु
			rio_ग_लिखो_config_32(rdev,
				RIO_DEV_PORT_N_ACK_STS_CSR(rdev, portnum),
				RIO_PORT_N_ACK_CLEAR);
			पूर्ण अन्यथा अणु
				rio_ग_लिखो_config_32(rdev,
					RIO_DEV_PORT_N_OB_ACK_CSR(rdev, portnum),
					RIO_PORT_N_OB_ACK_CLEAR);
				rio_ग_लिखो_config_32(rdev,
					RIO_DEV_PORT_N_IB_ACK_CSR(rdev, portnum),
					0);
			पूर्ण

			/* Schedule Extraction Service */
			pr_debug("RIO_PW: Device Extraction on [%s]-P%d\n",
			       rio_name(rdev), portnum);
		पूर्ण
	पूर्ण

	rio_पढ़ो_config_32(rdev,
		rdev->em_efptr + RIO_EM_PN_ERR_DETECT(portnum), &em_perrdet);
	अगर (em_perrdet) अणु
		pr_debug("RIO_PW: RIO_EM_P%d_ERR_DETECT=0x%08x\n",
			 portnum, em_perrdet);
		/* Clear EM Port N Error Detect CSR */
		rio_ग_लिखो_config_32(rdev,
			rdev->em_efptr + RIO_EM_PN_ERR_DETECT(portnum), 0);
	पूर्ण

	rio_पढ़ो_config_32(rdev,
		rdev->em_efptr + RIO_EM_LTL_ERR_DETECT, &em_ltlerrdet);
	अगर (em_ltlerrdet) अणु
		pr_debug("RIO_PW: RIO_EM_LTL_ERR_DETECT=0x%08x\n",
			 em_ltlerrdet);
		/* Clear EM L/T Layer Error Detect CSR */
		rio_ग_लिखो_config_32(rdev,
			rdev->em_efptr + RIO_EM_LTL_ERR_DETECT, 0);
	पूर्ण

	/* Clear reमुख्यing error bits and Port-Write Pending bit */
	rio_ग_लिखो_config_32(rdev, RIO_DEV_PORT_N_ERR_STS_CSR(rdev, portnum),
			    err_status);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rio_inb_pग_लिखो_handler);

/**
 * rio_mport_get_efb - get poपूर्णांकer to next extended features block
 * @port: Master port to issue transaction
 * @local: Indicate a local master port or remote device access
 * @destid: Destination ID of the device
 * @hopcount: Number of चयन hops to the device
 * @from: Offset of  current Extended Feature block header (अगर 0 starts
 * from	ExtFeaturePtr)
 */
u32
rio_mport_get_efb(काष्ठा rio_mport *port, पूर्णांक local, u16 destid,
		      u8 hopcount, u32 from)
अणु
	u32 reg_val;

	अगर (from == 0) अणु
		अगर (local)
			rio_local_पढ़ो_config_32(port, RIO_ASM_INFO_CAR,
						 &reg_val);
		अन्यथा
			rio_mport_पढ़ो_config_32(port, destid, hopcount,
						 RIO_ASM_INFO_CAR, &reg_val);
		वापस reg_val & RIO_EXT_FTR_PTR_MASK;
	पूर्ण अन्यथा अणु
		अगर (local)
			rio_local_पढ़ो_config_32(port, from, &reg_val);
		अन्यथा
			rio_mport_पढ़ो_config_32(port, destid, hopcount,
						 from, &reg_val);
		वापस RIO_GET_BLOCK_ID(reg_val);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(rio_mport_get_efb);

/**
 * rio_mport_get_feature - query क्रम devices' extended features
 * @port: Master port to issue transaction
 * @local: Indicate a local master port or remote device access
 * @destid: Destination ID of the device
 * @hopcount: Number of चयन hops to the device
 * @ftr: Extended feature code
 *
 * Tell अगर a device supports a given RapidIO capability.
 * Returns the offset of the requested extended feature
 * block within the device's RIO configuration space or
 * 0 in हाल the device करोes not support it.
 */
u32
rio_mport_get_feature(काष्ठा rio_mport * port, पूर्णांक local, u16 destid,
		      u8 hopcount, पूर्णांक ftr)
अणु
	u32 यंत्र_info, ext_ftr_ptr, ftr_header;

	अगर (local)
		rio_local_पढ़ो_config_32(port, RIO_ASM_INFO_CAR, &यंत्र_info);
	अन्यथा
		rio_mport_पढ़ो_config_32(port, destid, hopcount,
					 RIO_ASM_INFO_CAR, &यंत्र_info);

	ext_ftr_ptr = यंत्र_info & RIO_EXT_FTR_PTR_MASK;

	जबतक (ext_ftr_ptr) अणु
		अगर (local)
			rio_local_पढ़ो_config_32(port, ext_ftr_ptr,
						 &ftr_header);
		अन्यथा
			rio_mport_पढ़ो_config_32(port, destid, hopcount,
						 ext_ftr_ptr, &ftr_header);
		अगर (RIO_GET_BLOCK_ID(ftr_header) == ftr)
			वापस ext_ftr_ptr;

		ext_ftr_ptr = RIO_GET_BLOCK_PTR(ftr_header);
		अगर (!ext_ftr_ptr)
			अवरोध;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rio_mport_get_feature);

/**
 * rio_std_route_add_entry - Add चयन route table entry using standard
 *   रेजिस्टरs defined in RIO specअगरication rev.1.3
 * @mport: Master port to issue transaction
 * @destid: Destination ID of the device
 * @hopcount: Number of चयन hops to the device
 * @table: routing table ID (global or port-specअगरic)
 * @route_destid: destID entry in the RT
 * @route_port: destination port क्रम specअगरied destID
 */
अटल पूर्णांक
rio_std_route_add_entry(काष्ठा rio_mport *mport, u16 destid, u8 hopcount,
			u16 table, u16 route_destid, u8 route_port)
अणु
	अगर (table == RIO_GLOBAL_TABLE) अणु
		rio_mport_ग_लिखो_config_32(mport, destid, hopcount,
				RIO_STD_RTE_CONF_DESTID_SEL_CSR,
				(u32)route_destid);
		rio_mport_ग_लिखो_config_32(mport, destid, hopcount,
				RIO_STD_RTE_CONF_PORT_SEL_CSR,
				(u32)route_port);
	पूर्ण

	udelay(10);
	वापस 0;
पूर्ण

/**
 * rio_std_route_get_entry - Read चयन route table entry (port number)
 *   associated with specअगरied destID using standard रेजिस्टरs defined in RIO
 *   specअगरication rev.1.3
 * @mport: Master port to issue transaction
 * @destid: Destination ID of the device
 * @hopcount: Number of चयन hops to the device
 * @table: routing table ID (global or port-specअगरic)
 * @route_destid: destID entry in the RT
 * @route_port: वापसed destination port क्रम specअगरied destID
 */
अटल पूर्णांक
rio_std_route_get_entry(काष्ठा rio_mport *mport, u16 destid, u8 hopcount,
			u16 table, u16 route_destid, u8 *route_port)
अणु
	u32 result;

	अगर (table == RIO_GLOBAL_TABLE) अणु
		rio_mport_ग_लिखो_config_32(mport, destid, hopcount,
				RIO_STD_RTE_CONF_DESTID_SEL_CSR, route_destid);
		rio_mport_पढ़ो_config_32(mport, destid, hopcount,
				RIO_STD_RTE_CONF_PORT_SEL_CSR, &result);

		*route_port = (u8)result;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * rio_std_route_clr_table - Clear swotch route table using standard रेजिस्टरs
 *   defined in RIO specअगरication rev.1.3.
 * @mport: Master port to issue transaction
 * @destid: Destination ID of the device
 * @hopcount: Number of चयन hops to the device
 * @table: routing table ID (global or port-specअगरic)
 */
अटल पूर्णांक
rio_std_route_clr_table(काष्ठा rio_mport *mport, u16 destid, u8 hopcount,
			u16 table)
अणु
	u32 max_destid = 0xff;
	u32 i, pef, id_inc = 1, ext_cfg = 0;
	u32 port_sel = RIO_INVALID_ROUTE;

	अगर (table == RIO_GLOBAL_TABLE) अणु
		rio_mport_पढ़ो_config_32(mport, destid, hopcount,
					 RIO_PEF_CAR, &pef);

		अगर (mport->sys_size) अणु
			rio_mport_पढ़ो_config_32(mport, destid, hopcount,
						 RIO_SWITCH_RT_LIMIT,
						 &max_destid);
			max_destid &= RIO_RT_MAX_DESTID;
		पूर्ण

		अगर (pef & RIO_PEF_EXT_RT) अणु
			ext_cfg = 0x80000000;
			id_inc = 4;
			port_sel = (RIO_INVALID_ROUTE << 24) |
				   (RIO_INVALID_ROUTE << 16) |
				   (RIO_INVALID_ROUTE << 8) |
				   RIO_INVALID_ROUTE;
		पूर्ण

		क्रम (i = 0; i <= max_destid;) अणु
			rio_mport_ग_लिखो_config_32(mport, destid, hopcount,
					RIO_STD_RTE_CONF_DESTID_SEL_CSR,
					ext_cfg | i);
			rio_mport_ग_लिखो_config_32(mport, destid, hopcount,
					RIO_STD_RTE_CONF_PORT_SEL_CSR,
					port_sel);
			i += id_inc;
		पूर्ण
	पूर्ण

	udelay(10);
	वापस 0;
पूर्ण

/**
 * rio_lock_device - Acquires host device lock क्रम specअगरied device
 * @port: Master port to send transaction
 * @destid: Destination ID क्रम device/चयन
 * @hopcount: Hopcount to reach चयन
 * @रुको_ms: Max रुको समय in msec (0 = no समयout)
 *
 * Attepts to acquire host device lock क्रम specअगरied device
 * Returns 0 अगर device lock acquired or EINVAL अगर समयout expires.
 */
पूर्णांक rio_lock_device(काष्ठा rio_mport *port, u16 destid,
		    u8 hopcount, पूर्णांक रुको_ms)
अणु
	u32 result;
	पूर्णांक tcnt = 0;

	/* Attempt to acquire device lock */
	rio_mport_ग_लिखो_config_32(port, destid, hopcount,
				  RIO_HOST_DID_LOCK_CSR, port->host_deviceid);
	rio_mport_पढ़ो_config_32(port, destid, hopcount,
				 RIO_HOST_DID_LOCK_CSR, &result);

	जबतक (result != port->host_deviceid) अणु
		अगर (रुको_ms != 0 && tcnt == रुको_ms) अणु
			pr_debug("RIO: timeout when locking device %x:%x\n",
				destid, hopcount);
			वापस -EINVAL;
		पूर्ण

		/* Delay a bit */
		mdelay(1);
		tcnt++;
		/* Try to acquire device lock again */
		rio_mport_ग_लिखो_config_32(port, destid,
			hopcount,
			RIO_HOST_DID_LOCK_CSR,
			port->host_deviceid);
		rio_mport_पढ़ो_config_32(port, destid,
			hopcount,
			RIO_HOST_DID_LOCK_CSR, &result);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rio_lock_device);

/**
 * rio_unlock_device - Releases host device lock क्रम specअगरied device
 * @port: Master port to send transaction
 * @destid: Destination ID क्रम device/चयन
 * @hopcount: Hopcount to reach चयन
 *
 * Returns 0 अगर device lock released or EINVAL अगर fails.
 */
पूर्णांक rio_unlock_device(काष्ठा rio_mport *port, u16 destid, u8 hopcount)
अणु
	u32 result;

	/* Release device lock */
	rio_mport_ग_लिखो_config_32(port, destid,
				  hopcount,
				  RIO_HOST_DID_LOCK_CSR,
				  port->host_deviceid);
	rio_mport_पढ़ो_config_32(port, destid, hopcount,
		RIO_HOST_DID_LOCK_CSR, &result);
	अगर ((result & 0xffff) != 0xffff) अणु
		pr_debug("RIO: badness when releasing device lock %x:%x\n",
			 destid, hopcount);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rio_unlock_device);

/**
 * rio_route_add_entry- Add a route entry to a चयन routing table
 * @rdev: RIO device
 * @table: Routing table ID
 * @route_destid: Destination ID to be routed
 * @route_port: Port number to be routed
 * @lock: apply a hardware lock on चयन device flag (1=lock, 0=no_lock)
 *
 * If available calls the चयन specअगरic add_entry() method to add a route
 * entry पूर्णांकo a चयन routing table. Otherwise uses standard RT update method
 * as defined by RapidIO specअगरication. A specअगरic routing table can be selected
 * using the @table argument अगर a चयन has per port routing tables or
 * the standard (or global) table may be used by passing
 * %RIO_GLOBAL_TABLE in @table.
 *
 * Returns %0 on success or %-EINVAL on failure.
 */
पूर्णांक rio_route_add_entry(काष्ठा rio_dev *rdev,
			u16 table, u16 route_destid, u8 route_port, पूर्णांक lock)
अणु
	पूर्णांक rc = -EINVAL;
	काष्ठा rio_चयन_ops *ops = rdev->rचयन->ops;

	अगर (lock) अणु
		rc = rio_lock_device(rdev->net->hport, rdev->destid,
				     rdev->hopcount, 1000);
		अगर (rc)
			वापस rc;
	पूर्ण

	spin_lock(&rdev->rचयन->lock);

	अगर (!ops || !ops->add_entry) अणु
		rc = rio_std_route_add_entry(rdev->net->hport, rdev->destid,
					     rdev->hopcount, table,
					     route_destid, route_port);
	पूर्ण अन्यथा अगर (try_module_get(ops->owner)) अणु
		rc = ops->add_entry(rdev->net->hport, rdev->destid,
				    rdev->hopcount, table, route_destid,
				    route_port);
		module_put(ops->owner);
	पूर्ण

	spin_unlock(&rdev->rचयन->lock);

	अगर (lock)
		rio_unlock_device(rdev->net->hport, rdev->destid,
				  rdev->hopcount);

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(rio_route_add_entry);

/**
 * rio_route_get_entry- Read an entry from a चयन routing table
 * @rdev: RIO device
 * @table: Routing table ID
 * @route_destid: Destination ID to be routed
 * @route_port: Poपूर्णांकer to पढ़ो port number पूर्णांकo
 * @lock: apply a hardware lock on चयन device flag (1=lock, 0=no_lock)
 *
 * If available calls the चयन specअगरic get_entry() method to fetch a route
 * entry from a चयन routing table. Otherwise uses standard RT पढ़ो method
 * as defined by RapidIO specअगरication. A specअगरic routing table can be selected
 * using the @table argument अगर a चयन has per port routing tables or
 * the standard (or global) table may be used by passing
 * %RIO_GLOBAL_TABLE in @table.
 *
 * Returns %0 on success or %-EINVAL on failure.
 */
पूर्णांक rio_route_get_entry(काष्ठा rio_dev *rdev, u16 table,
			u16 route_destid, u8 *route_port, पूर्णांक lock)
अणु
	पूर्णांक rc = -EINVAL;
	काष्ठा rio_चयन_ops *ops = rdev->rचयन->ops;

	अगर (lock) अणु
		rc = rio_lock_device(rdev->net->hport, rdev->destid,
				     rdev->hopcount, 1000);
		अगर (rc)
			वापस rc;
	पूर्ण

	spin_lock(&rdev->rचयन->lock);

	अगर (!ops || !ops->get_entry) अणु
		rc = rio_std_route_get_entry(rdev->net->hport, rdev->destid,
					     rdev->hopcount, table,
					     route_destid, route_port);
	पूर्ण अन्यथा अगर (try_module_get(ops->owner)) अणु
		rc = ops->get_entry(rdev->net->hport, rdev->destid,
				    rdev->hopcount, table, route_destid,
				    route_port);
		module_put(ops->owner);
	पूर्ण

	spin_unlock(&rdev->rचयन->lock);

	अगर (lock)
		rio_unlock_device(rdev->net->hport, rdev->destid,
				  rdev->hopcount);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(rio_route_get_entry);

/**
 * rio_route_clr_table - Clear a चयन routing table
 * @rdev: RIO device
 * @table: Routing table ID
 * @lock: apply a hardware lock on चयन device flag (1=lock, 0=no_lock)
 *
 * If available calls the चयन specअगरic clr_table() method to clear a चयन
 * routing table. Otherwise uses standard RT ग_लिखो method as defined by RapidIO
 * specअगरication. A specअगरic routing table can be selected using the @table
 * argument अगर a चयन has per port routing tables or the standard (or global)
 * table may be used by passing %RIO_GLOBAL_TABLE in @table.
 *
 * Returns %0 on success or %-EINVAL on failure.
 */
पूर्णांक rio_route_clr_table(काष्ठा rio_dev *rdev, u16 table, पूर्णांक lock)
अणु
	पूर्णांक rc = -EINVAL;
	काष्ठा rio_चयन_ops *ops = rdev->rचयन->ops;

	अगर (lock) अणु
		rc = rio_lock_device(rdev->net->hport, rdev->destid,
				     rdev->hopcount, 1000);
		अगर (rc)
			वापस rc;
	पूर्ण

	spin_lock(&rdev->rचयन->lock);

	अगर (!ops || !ops->clr_table) अणु
		rc = rio_std_route_clr_table(rdev->net->hport, rdev->destid,
					     rdev->hopcount, table);
	पूर्ण अन्यथा अगर (try_module_get(ops->owner)) अणु
		rc = ops->clr_table(rdev->net->hport, rdev->destid,
				    rdev->hopcount, table);

		module_put(ops->owner);
	पूर्ण

	spin_unlock(&rdev->rचयन->lock);

	अगर (lock)
		rio_unlock_device(rdev->net->hport, rdev->destid,
				  rdev->hopcount);

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(rio_route_clr_table);

#अगर_घोषित CONFIG_RAPIDIO_DMA_ENGINE

अटल bool rio_chan_filter(काष्ठा dma_chan *chan, व्योम *arg)
अणु
	काष्ठा rio_mport *mport = arg;

	/* Check that DMA device beदीर्घs to the right MPORT */
	वापस mport == container_of(chan->device, काष्ठा rio_mport, dma);
पूर्ण

/**
 * rio_request_mport_dma - request RapidIO capable DMA channel associated
 *   with specअगरied local RapidIO mport device.
 * @mport: RIO mport to perक्रमm DMA data transfers
 *
 * Returns poपूर्णांकer to allocated DMA channel or शून्य अगर failed.
 */
काष्ठा dma_chan *rio_request_mport_dma(काष्ठा rio_mport *mport)
अणु
	dma_cap_mask_t mask;

	dma_cap_zero(mask);
	dma_cap_set(DMA_SLAVE, mask);
	वापस dma_request_channel(mask, rio_chan_filter, mport);
पूर्ण
EXPORT_SYMBOL_GPL(rio_request_mport_dma);

/**
 * rio_request_dma - request RapidIO capable DMA channel that supports
 *   specअगरied target RapidIO device.
 * @rdev: RIO device associated with DMA transfer
 *
 * Returns poपूर्णांकer to allocated DMA channel or शून्य अगर failed.
 */
काष्ठा dma_chan *rio_request_dma(काष्ठा rio_dev *rdev)
अणु
	वापस rio_request_mport_dma(rdev->net->hport);
पूर्ण
EXPORT_SYMBOL_GPL(rio_request_dma);

/**
 * rio_release_dma - release specअगरied DMA channel
 * @dchan: DMA channel to release
 */
व्योम rio_release_dma(काष्ठा dma_chan *dchan)
अणु
	dma_release_channel(dchan);
पूर्ण
EXPORT_SYMBOL_GPL(rio_release_dma);

/**
 * rio_dma_prep_xfer - RapidIO specअगरic wrapper
 *   क्रम device_prep_slave_sg callback defined by DMAENGINE.
 * @dchan: DMA channel to configure
 * @destid: target RapidIO device destination ID
 * @data: RIO specअगरic data descriptor
 * @direction: DMA data transfer direction (TO or FROM the device)
 * @flags: dmaengine defined flags
 *
 * Initializes RapidIO capable DMA channel क्रम the specअगरied data transfer.
 * Uses DMA channel निजी extension to pass inक्रमmation related to remote
 * target RIO device.
 *
 * Returns: poपूर्णांकer to DMA transaction descriptor अगर successful,
 *          error-valued poपूर्णांकer or शून्य अगर failed.
 */
काष्ठा dma_async_tx_descriptor *rio_dma_prep_xfer(काष्ठा dma_chan *dchan,
	u16 destid, काष्ठा rio_dma_data *data,
	क्रमागत dma_transfer_direction direction, अचिन्हित दीर्घ flags)
अणु
	काष्ठा rio_dma_ext rio_ext;

	अगर (!dchan->device->device_prep_slave_sg) अणु
		pr_err("%s: prep_rio_sg == NULL\n", __func__);
		वापस शून्य;
	पूर्ण

	rio_ext.destid = destid;
	rio_ext.rio_addr_u = data->rio_addr_u;
	rio_ext.rio_addr = data->rio_addr;
	rio_ext.wr_type = data->wr_type;

	वापस dmaengine_prep_rio_sg(dchan, data->sg, data->sg_len,
				     direction, flags, &rio_ext);
पूर्ण
EXPORT_SYMBOL_GPL(rio_dma_prep_xfer);

/**
 * rio_dma_prep_slave_sg - RapidIO specअगरic wrapper
 *   क्रम device_prep_slave_sg callback defined by DMAENGINE.
 * @rdev: RIO device control काष्ठाure
 * @dchan: DMA channel to configure
 * @data: RIO specअगरic data descriptor
 * @direction: DMA data transfer direction (TO or FROM the device)
 * @flags: dmaengine defined flags
 *
 * Initializes RapidIO capable DMA channel क्रम the specअगरied data transfer.
 * Uses DMA channel निजी extension to pass inक्रमmation related to remote
 * target RIO device.
 *
 * Returns: poपूर्णांकer to DMA transaction descriptor अगर successful,
 *          error-valued poपूर्णांकer or शून्य अगर failed.
 */
काष्ठा dma_async_tx_descriptor *rio_dma_prep_slave_sg(काष्ठा rio_dev *rdev,
	काष्ठा dma_chan *dchan, काष्ठा rio_dma_data *data,
	क्रमागत dma_transfer_direction direction, अचिन्हित दीर्घ flags)
अणु
	वापस rio_dma_prep_xfer(dchan,	rdev->destid, data, direction, flags);
पूर्ण
EXPORT_SYMBOL_GPL(rio_dma_prep_slave_sg);

#पूर्ण_अगर /* CONFIG_RAPIDIO_DMA_ENGINE */

/**
 * rio_find_mport - find RIO mport by its ID
 * @mport_id: number (ID) of mport device
 *
 * Given a RIO mport number, the desired mport is located
 * in the global list of mports. If the mport is found, a poपूर्णांकer to its
 * data काष्ठाure is वापसed.  If no mport is found, %शून्य is वापसed.
 */
काष्ठा rio_mport *rio_find_mport(पूर्णांक mport_id)
अणु
	काष्ठा rio_mport *port;

	mutex_lock(&rio_mport_list_lock);
	list_क्रम_each_entry(port, &rio_mports, node) अणु
		अगर (port->id == mport_id)
			जाओ found;
	पूर्ण
	port = शून्य;
found:
	mutex_unlock(&rio_mport_list_lock);

	वापस port;
पूर्ण

/**
 * rio_रेजिस्टर_scan - क्रमागतeration/discovery method registration पूर्णांकerface
 * @mport_id: mport device ID क्रम which fabric scan routine has to be set
 *            (RIO_MPORT_ANY = set क्रम all available mports)
 * @scan_ops: क्रमागतeration/discovery operations काष्ठाure
 *
 * Registers क्रमागतeration/discovery operations with RapidIO subप्रणाली and
 * attaches it to the specअगरied mport device (or all available mports
 * अगर RIO_MPORT_ANY is specअगरied).
 *
 * Returns error अगर the mport alपढ़ोy has an क्रमागतerator attached to it.
 * In हाल of RIO_MPORT_ANY skips mports with valid scan routines (no error).
 */
पूर्णांक rio_रेजिस्टर_scan(पूर्णांक mport_id, काष्ठा rio_scan *scan_ops)
अणु
	काष्ठा rio_mport *port;
	काष्ठा rio_scan_node *scan;
	पूर्णांक rc = 0;

	pr_debug("RIO: %s for mport_id=%d\n", __func__, mport_id);

	अगर ((mport_id != RIO_MPORT_ANY && mport_id >= RIO_MAX_MPORTS) ||
	    !scan_ops)
		वापस -EINVAL;

	mutex_lock(&rio_mport_list_lock);

	/*
	 * Check अगर there is another क्रमागतerator alपढ़ोy रेजिस्टरed क्रम
	 * the same mport ID (including RIO_MPORT_ANY). Multiple क्रमागतerators
	 * क्रम the same mport ID are not supported.
	 */
	list_क्रम_each_entry(scan, &rio_scans, node) अणु
		अगर (scan->mport_id == mport_id) अणु
			rc = -EBUSY;
			जाओ err_out;
		पूर्ण
	पूर्ण

	/*
	 * Allocate and initialize new scan registration node.
	 */
	scan = kzalloc(माप(*scan), GFP_KERNEL);
	अगर (!scan) अणु
		rc = -ENOMEM;
		जाओ err_out;
	पूर्ण

	scan->mport_id = mport_id;
	scan->ops = scan_ops;

	/*
	 * Traverse the list of रेजिस्टरed mports to attach this new scan.
	 *
	 * The new scan with matching mport ID overrides any previously attached
	 * scan assuming that old scan (अगर any) is the शेष one (based on the
	 * क्रमागतerator registration check above).
	 * If the new scan is the global one, it will be attached only to mports
	 * that करो not have their own inभागidual operations alपढ़ोy attached.
	 */
	list_क्रम_each_entry(port, &rio_mports, node) अणु
		अगर (port->id == mport_id) अणु
			port->nscan = scan_ops;
			अवरोध;
		पूर्ण अन्यथा अगर (mport_id == RIO_MPORT_ANY && !port->nscan)
			port->nscan = scan_ops;
	पूर्ण

	list_add_tail(&scan->node, &rio_scans);

err_out:
	mutex_unlock(&rio_mport_list_lock);

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(rio_रेजिस्टर_scan);

/**
 * rio_unरेजिस्टर_scan - हटाओs क्रमागतeration/discovery method from mport
 * @mport_id: mport device ID क्रम which fabric scan routine has to be
 *            unरेजिस्टरed (RIO_MPORT_ANY = apply to all mports that use
 *            the specअगरied scan_ops)
 * @scan_ops: क्रमागतeration/discovery operations काष्ठाure
 *
 * Removes क्रमागतeration or discovery method asचिन्हित to the specअगरied mport
 * device. If RIO_MPORT_ANY is specअगरied, हटाओs the specअगरied operations from
 * all mports that have them attached.
 */
पूर्णांक rio_unरेजिस्टर_scan(पूर्णांक mport_id, काष्ठा rio_scan *scan_ops)
अणु
	काष्ठा rio_mport *port;
	काष्ठा rio_scan_node *scan;

	pr_debug("RIO: %s for mport_id=%d\n", __func__, mport_id);

	अगर (mport_id != RIO_MPORT_ANY && mport_id >= RIO_MAX_MPORTS)
		वापस -EINVAL;

	mutex_lock(&rio_mport_list_lock);

	list_क्रम_each_entry(port, &rio_mports, node)
		अगर (port->id == mport_id ||
		    (mport_id == RIO_MPORT_ANY && port->nscan == scan_ops))
			port->nscan = शून्य;

	list_क्रम_each_entry(scan, &rio_scans, node) अणु
		अगर (scan->mport_id == mport_id) अणु
			list_del(&scan->node);
			kमुक्त(scan);
			अवरोध;
		पूर्ण
	पूर्ण

	mutex_unlock(&rio_mport_list_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rio_unरेजिस्टर_scan);

/**
 * rio_mport_scan - execute क्रमागतeration/discovery on the specअगरied mport
 * @mport_id: number (ID) of mport device
 */
पूर्णांक rio_mport_scan(पूर्णांक mport_id)
अणु
	काष्ठा rio_mport *port = शून्य;
	पूर्णांक rc;

	mutex_lock(&rio_mport_list_lock);
	list_क्रम_each_entry(port, &rio_mports, node) अणु
		अगर (port->id == mport_id)
			जाओ found;
	पूर्ण
	mutex_unlock(&rio_mport_list_lock);
	वापस -ENODEV;
found:
	अगर (!port->nscan) अणु
		mutex_unlock(&rio_mport_list_lock);
		वापस -EINVAL;
	पूर्ण

	अगर (!try_module_get(port->nscan->owner)) अणु
		mutex_unlock(&rio_mport_list_lock);
		वापस -ENODEV;
	पूर्ण

	mutex_unlock(&rio_mport_list_lock);

	अगर (port->host_deviceid >= 0)
		rc = port->nscan->क्रमागतerate(port, 0);
	अन्यथा
		rc = port->nscan->discover(port, RIO_SCAN_ENUM_NO_WAIT);

	module_put(port->nscan->owner);
	वापस rc;
पूर्ण

अटल काष्ठा workqueue_काष्ठा *rio_wq;

काष्ठा rio_disc_work अणु
	काष्ठा work_काष्ठा	work;
	काष्ठा rio_mport	*mport;
पूर्ण;

अटल व्योम disc_work_handler(काष्ठा work_काष्ठा *_work)
अणु
	काष्ठा rio_disc_work *work;

	work = container_of(_work, काष्ठा rio_disc_work, work);
	pr_debug("RIO: discovery work for mport %d %s\n",
		 work->mport->id, work->mport->name);
	अगर (try_module_get(work->mport->nscan->owner)) अणु
		work->mport->nscan->discover(work->mport, 0);
		module_put(work->mport->nscan->owner);
	पूर्ण
पूर्ण

पूर्णांक rio_init_mports(व्योम)
अणु
	काष्ठा rio_mport *port;
	काष्ठा rio_disc_work *work;
	पूर्णांक n = 0;

	अगर (!next_portid)
		वापस -ENODEV;

	/*
	 * First, run क्रमागतerations and check अगर we need to perक्रमm discovery
	 * on any of the रेजिस्टरed mports.
	 */
	mutex_lock(&rio_mport_list_lock);
	list_क्रम_each_entry(port, &rio_mports, node) अणु
		अगर (port->host_deviceid >= 0) अणु
			अगर (port->nscan && try_module_get(port->nscan->owner)) अणु
				port->nscan->क्रमागतerate(port, 0);
				module_put(port->nscan->owner);
			पूर्ण
		पूर्ण अन्यथा
			n++;
	पूर्ण
	mutex_unlock(&rio_mport_list_lock);

	अगर (!n)
		जाओ no_disc;

	/*
	 * If we have mports that require discovery schedule a discovery work
	 * क्रम each of them. If the code below fails to allocate needed
	 * resources, निकास without error to keep results of क्रमागतeration
	 * process (अगर any).
	 * TODO: Implement restart of discovery process क्रम all or
	 * inभागidual discovering mports.
	 */
	rio_wq = alloc_workqueue("riodisc", 0, 0);
	अगर (!rio_wq) अणु
		pr_err("RIO: unable allocate rio_wq\n");
		जाओ no_disc;
	पूर्ण

	work = kसुस्मृति(n, माप *work, GFP_KERNEL);
	अगर (!work) अणु
		destroy_workqueue(rio_wq);
		जाओ no_disc;
	पूर्ण

	n = 0;
	mutex_lock(&rio_mport_list_lock);
	list_क्रम_each_entry(port, &rio_mports, node) अणु
		अगर (port->host_deviceid < 0 && port->nscan) अणु
			work[n].mport = port;
			INIT_WORK(&work[n].work, disc_work_handler);
			queue_work(rio_wq, &work[n].work);
			n++;
		पूर्ण
	पूर्ण

	flush_workqueue(rio_wq);
	mutex_unlock(&rio_mport_list_lock);
	pr_debug("RIO: destroy discovery workqueue\n");
	destroy_workqueue(rio_wq);
	kमुक्त(work);

no_disc:
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rio_init_mports);

अटल पूर्णांक rio_get_hdid(पूर्णांक index)
अणु
	अगर (ids_num == 0 || ids_num <= index || index >= RIO_MAX_MPORTS)
		वापस -1;

	वापस hdid[index];
पूर्ण

पूर्णांक rio_mport_initialize(काष्ठा rio_mport *mport)
अणु
	अगर (next_portid >= RIO_MAX_MPORTS) अणु
		pr_err("RIO: reached specified max number of mports\n");
		वापस -ENODEV;
	पूर्ण

	atomic_set(&mport->state, RIO_DEVICE_INITIALIZING);
	mport->id = next_portid++;
	mport->host_deviceid = rio_get_hdid(mport->id);
	mport->nscan = शून्य;
	mutex_init(&mport->lock);
	mport->pwe_refcnt = 0;
	INIT_LIST_HEAD(&mport->pग_लिखोs);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rio_mport_initialize);

पूर्णांक rio_रेजिस्टर_mport(काष्ठा rio_mport *port)
अणु
	काष्ठा rio_scan_node *scan = शून्य;
	पूर्णांक res = 0;

	mutex_lock(&rio_mport_list_lock);

	/*
	 * Check अगर there are any रेजिस्टरed क्रमागतeration/discovery operations
	 * that have to be attached to the added mport.
	 */
	list_क्रम_each_entry(scan, &rio_scans, node) अणु
		अगर (port->id == scan->mport_id ||
		    scan->mport_id == RIO_MPORT_ANY) अणु
			port->nscan = scan->ops;
			अगर (port->id == scan->mport_id)
				अवरोध;
		पूर्ण
	पूर्ण

	list_add_tail(&port->node, &rio_mports);
	mutex_unlock(&rio_mport_list_lock);

	dev_set_name(&port->dev, "rapidio%d", port->id);
	port->dev.class = &rio_mport_class;
	atomic_set(&port->state, RIO_DEVICE_RUNNING);

	res = device_रेजिस्टर(&port->dev);
	अगर (res)
		dev_err(&port->dev, "RIO: mport%d registration failed ERR=%d\n",
			port->id, res);
	अन्यथा
		dev_dbg(&port->dev, "RIO: registered mport%d\n", port->id);

	वापस res;
पूर्ण
EXPORT_SYMBOL_GPL(rio_रेजिस्टर_mport);

अटल पूर्णांक rio_mport_cleanup_callback(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा rio_dev *rdev = to_rio_dev(dev);

	अगर (dev->bus == &rio_bus_type)
		rio_del_device(rdev, RIO_DEVICE_SHUTDOWN);
	वापस 0;
पूर्ण

अटल पूर्णांक rio_net_हटाओ_children(काष्ठा rio_net *net)
अणु
	/*
	 * Unरेजिस्टर all RapidIO devices residing on this net (this will
	 * invoke notअगरication of रेजिस्टरed subप्रणाली पूर्णांकerfaces as well).
	 */
	device_क्रम_each_child(&net->dev, शून्य, rio_mport_cleanup_callback);
	वापस 0;
पूर्ण

पूर्णांक rio_unरेजिस्टर_mport(काष्ठा rio_mport *port)
अणु
	pr_debug("RIO: %s %s id=%d\n", __func__, port->name, port->id);

	/* Transition mport to the SHUTDOWN state */
	अगर (atomic_cmpxchg(&port->state,
			   RIO_DEVICE_RUNNING,
			   RIO_DEVICE_SHUTDOWN) != RIO_DEVICE_RUNNING) अणु
		pr_err("RIO: %s unexpected state transition for mport %s\n",
			__func__, port->name);
	पूर्ण

	अगर (port->net && port->net->hport == port) अणु
		rio_net_हटाओ_children(port->net);
		rio_मुक्त_net(port->net);
	पूर्ण

	/*
	 * Unरेजिस्टर all RapidIO devices attached to this mport (this will
	 * invoke notअगरication of रेजिस्टरed subप्रणाली पूर्णांकerfaces as well).
	 */
	mutex_lock(&rio_mport_list_lock);
	list_del(&port->node);
	mutex_unlock(&rio_mport_list_lock);
	device_unरेजिस्टर(&port->dev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rio_unरेजिस्टर_mport);
