<शैली गुरु>
/*
 * Copyright (c) 2004 Topspin Communications.  All rights reserved.
 * Copyright (c) 2005 Sun Microप्रणालीs, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/netdevice.h>
#समावेश <net/net_namespace.h>
#समावेश <linux/security.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/hashtable.h>
#समावेश <rdma/rdma_netlink.h>
#समावेश <rdma/ib_addr.h>
#समावेश <rdma/ib_cache.h>
#समावेश <rdma/rdma_counter.h>

#समावेश "core_priv.h"
#समावेश "restrack.h"

MODULE_AUTHOR("Roland Dreier");
MODULE_DESCRIPTION("core kernel InfiniBand API");
MODULE_LICENSE("Dual BSD/GPL");

काष्ठा workqueue_काष्ठा *ib_comp_wq;
काष्ठा workqueue_काष्ठा *ib_comp_unbound_wq;
काष्ठा workqueue_काष्ठा *ib_wq;
EXPORT_SYMBOL_GPL(ib_wq);

/*
 * Each of the three rwsem locks (devices, clients, client_data) protects the
 * xarray of the same name. Specअगरically it allows the caller to निश्चित that
 * the MARK will/will not be changing under the lock, and क्रम devices and
 * clients, that the value in the xarray is still a valid poपूर्णांकer. Change of
 * the MARK is linked to the object state, so holding the lock and testing the
 * MARK also निश्चितs that the contained object is in a certain state.
 *
 * This is used to build a two stage रेजिस्टर/unरेजिस्टर flow where objects
 * can जारी to be in the xarray even though they are still in progress to
 * रेजिस्टर/unरेजिस्टर.
 *
 * The xarray itself provides additional locking, and restartable iteration,
 * which is also relied on.
 *
 * Locks should not be nested, with the exception of client_data, which is
 * allowed to nest under the पढ़ो side of the other two locks.
 *
 * The devices_rwsem also protects the device name list, any change or
 * assignment of device name must also hold the ग_लिखो side to guarantee unique
 * names.
 */

/*
 * devices contains devices that have had their names asचिन्हित. The
 * devices may not be रेजिस्टरed. Users that care about the registration
 * status need to call ib_device_try_get() on the device to ensure it is
 * रेजिस्टरed, and keep it रेजिस्टरed, क्रम the required duration.
 *
 */
अटल DEFINE_XARRAY_FLAGS(devices, XA_FLAGS_ALLOC);
अटल DECLARE_RWSEM(devices_rwsem);
#घोषणा DEVICE_REGISTERED XA_MARK_1

अटल u32 highest_client_id;
#घोषणा CLIENT_REGISTERED XA_MARK_1
अटल DEFINE_XARRAY_FLAGS(clients, XA_FLAGS_ALLOC);
अटल DECLARE_RWSEM(clients_rwsem);

अटल व्योम ib_client_put(काष्ठा ib_client *client)
अणु
	अगर (refcount_dec_and_test(&client->uses))
		complete(&client->uses_zero);
पूर्ण

/*
 * If client_data is रेजिस्टरed then the corresponding client must also still
 * be रेजिस्टरed.
 */
#घोषणा CLIENT_DATA_REGISTERED XA_MARK_1

अचिन्हित पूर्णांक rdma_dev_net_id;

/*
 * A list of net namespaces is मुख्यtained in an xarray. This is necessary
 * because we can't get the locking right using the existing net ns list. We
 * would require a init_net callback after the list is updated.
 */
अटल DEFINE_XARRAY_FLAGS(rdma_nets, XA_FLAGS_ALLOC);
/*
 * rwsem to protect accessing the rdma_nets xarray entries.
 */
अटल DECLARE_RWSEM(rdma_nets_rwsem);

bool ib_devices_shared_netns = true;
module_param_named(netns_mode, ib_devices_shared_netns, bool, 0444);
MODULE_PARM_DESC(netns_mode,
		 "Share device among net namespaces; default=1 (shared)");
/**
 * rdma_dev_access_netns() - Return whether an rdma device can be accessed
 *			     from a specअगरied net namespace or not.
 * @dev:	Poपूर्णांकer to rdma device which needs to be checked
 * @net:	Poपूर्णांकer to net namesapce क्रम which access to be checked
 *
 * When the rdma device is in shared mode, it ignores the net namespace.
 * When the rdma device is exclusive to a net namespace, rdma device net
 * namespace is checked against the specअगरied one.
 */
bool rdma_dev_access_netns(स्थिर काष्ठा ib_device *dev, स्थिर काष्ठा net *net)
अणु
	वापस (ib_devices_shared_netns ||
		net_eq(पढ़ो_pnet(&dev->coredev.rdma_net), net));
पूर्ण
EXPORT_SYMBOL(rdma_dev_access_netns);

/*
 * xarray has this behavior where it won't iterate over शून्य values stored in
 * allocated arrays.  So we need our own iterator to see all values stored in
 * the array. This करोes the same thing as xa_क्रम_each except that it also
 * वापसs शून्य valued entries अगर the array is allocating. Simplअगरied to only
 * work on simple xarrays.
 */
अटल व्योम *xan_find_marked(काष्ठा xarray *xa, अचिन्हित दीर्घ *indexp,
			     xa_mark_t filter)
अणु
	XA_STATE(xas, xa, *indexp);
	व्योम *entry;

	rcu_पढ़ो_lock();
	करो अणु
		entry = xas_find_marked(&xas, अच_दीर्घ_उच्च, filter);
		अगर (xa_is_zero(entry))
			अवरोध;
	पूर्ण जबतक (xas_retry(&xas, entry));
	rcu_पढ़ो_unlock();

	अगर (entry) अणु
		*indexp = xas.xa_index;
		अगर (xa_is_zero(entry))
			वापस शून्य;
		वापस entry;
	पूर्ण
	वापस XA_ERROR(-ENOENT);
पूर्ण
#घोषणा xan_क्रम_each_marked(xa, index, entry, filter)                          \
	क्रम (index = 0, entry = xan_find_marked(xa, &(index), filter);         \
	     !xa_is_err(entry);                                                \
	     (index)++, entry = xan_find_marked(xa, &(index), filter))

/* RCU hash table mapping netdevice poपूर्णांकers to काष्ठा ib_port_data */
अटल DEFINE_SPINLOCK(ndev_hash_lock);
अटल DECLARE_HASHTABLE(ndev_hash, 5);

अटल व्योम मुक्त_netdevs(काष्ठा ib_device *ib_dev);
अटल व्योम ib_unरेजिस्टर_work(काष्ठा work_काष्ठा *work);
अटल व्योम __ib_unरेजिस्टर_device(काष्ठा ib_device *device);
अटल पूर्णांक ib_security_change(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ event,
			      व्योम *lsm_data);
अटल व्योम ib_policy_change_task(काष्ठा work_काष्ठा *work);
अटल DECLARE_WORK(ib_policy_change_work, ib_policy_change_task);

अटल व्योम __ibdev_prपूर्णांकk(स्थिर अक्षर *level, स्थिर काष्ठा ib_device *ibdev,
			   काष्ठा va_क्रमmat *vaf)
अणु
	अगर (ibdev && ibdev->dev.parent)
		dev_prपूर्णांकk_emit(level[1] - '0',
				ibdev->dev.parent,
				"%s %s %s: %pV",
				dev_driver_string(ibdev->dev.parent),
				dev_name(ibdev->dev.parent),
				dev_name(&ibdev->dev),
				vaf);
	अन्यथा अगर (ibdev)
		prपूर्णांकk("%s%s: %pV",
		       level, dev_name(&ibdev->dev), vaf);
	अन्यथा
		prपूर्णांकk("%s(NULL ib_device): %pV", level, vaf);
पूर्ण

व्योम ibdev_prपूर्णांकk(स्थिर अक्षर *level, स्थिर काष्ठा ib_device *ibdev,
		  स्थिर अक्षर *क्रमmat, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	बहु_शुरू(args, क्रमmat);

	vaf.fmt = क्रमmat;
	vaf.va = &args;

	__ibdev_prपूर्णांकk(level, ibdev, &vaf);

	बहु_पूर्ण(args);
पूर्ण
EXPORT_SYMBOL(ibdev_prपूर्णांकk);

#घोषणा define_ibdev_prपूर्णांकk_level(func, level)                  \
व्योम func(स्थिर काष्ठा ib_device *ibdev, स्थिर अक्षर *fmt, ...)  \
अणु                                                               \
	काष्ठा va_क्रमmat vaf;                                   \
	बहु_सूची args;                                           \
								\
	बहु_शुरू(args, fmt);                                    \
								\
	vaf.fmt = fmt;                                          \
	vaf.va = &args;                                         \
								\
	__ibdev_prपूर्णांकk(level, ibdev, &vaf);                     \
								\
	बहु_पूर्ण(args);                                           \
पूर्ण                                                               \
EXPORT_SYMBOL(func);

define_ibdev_prपूर्णांकk_level(ibdev_emerg, KERN_EMERG);
define_ibdev_prपूर्णांकk_level(ibdev_alert, KERN_ALERT);
define_ibdev_prपूर्णांकk_level(ibdev_crit, KERN_CRIT);
define_ibdev_prपूर्णांकk_level(ibdev_err, KERN_ERR);
define_ibdev_prपूर्णांकk_level(ibdev_warn, KERN_WARNING);
define_ibdev_prपूर्णांकk_level(ibdev_notice, KERN_NOTICE);
define_ibdev_prपूर्णांकk_level(ibdev_info, KERN_INFO);

अटल काष्ठा notअगरier_block ibdev_lsm_nb = अणु
	.notअगरier_call = ib_security_change,
पूर्ण;

अटल पूर्णांक rdma_dev_change_netns(काष्ठा ib_device *device, काष्ठा net *cur_net,
				 काष्ठा net *net);

/* Poपूर्णांकer to the RCU head at the start of the ib_port_data array */
काष्ठा ib_port_data_rcu अणु
	काष्ठा rcu_head rcu_head;
	काष्ठा ib_port_data pdata[];
पूर्ण;

अटल व्योम ib_device_check_mandatory(काष्ठा ib_device *device)
अणु
#घोषणा IB_MANDATORY_FUNC(x) अणु दुरत्व(काष्ठा ib_device_ops, x), #x पूर्ण
	अटल स्थिर काष्ठा अणु
		माप_प्रकार offset;
		अक्षर  *name;
	पूर्ण mandatory_table[] = अणु
		IB_MANDATORY_FUNC(query_device),
		IB_MANDATORY_FUNC(query_port),
		IB_MANDATORY_FUNC(alloc_pd),
		IB_MANDATORY_FUNC(dealloc_pd),
		IB_MANDATORY_FUNC(create_qp),
		IB_MANDATORY_FUNC(modअगरy_qp),
		IB_MANDATORY_FUNC(destroy_qp),
		IB_MANDATORY_FUNC(post_send),
		IB_MANDATORY_FUNC(post_recv),
		IB_MANDATORY_FUNC(create_cq),
		IB_MANDATORY_FUNC(destroy_cq),
		IB_MANDATORY_FUNC(poll_cq),
		IB_MANDATORY_FUNC(req_notअगरy_cq),
		IB_MANDATORY_FUNC(get_dma_mr),
		IB_MANDATORY_FUNC(reg_user_mr),
		IB_MANDATORY_FUNC(dereg_mr),
		IB_MANDATORY_FUNC(get_port_immutable)
	पूर्ण;
	पूर्णांक i;

	device->kverbs_provider = true;
	क्रम (i = 0; i < ARRAY_SIZE(mandatory_table); ++i) अणु
		अगर (!*(व्योम **) ((व्योम *) &device->ops +
				 mandatory_table[i].offset)) अणु
			device->kverbs_provider = false;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Caller must perक्रमm ib_device_put() to वापस the device reference count
 * when ib_device_get_by_index() वापसs valid device poपूर्णांकer.
 */
काष्ठा ib_device *ib_device_get_by_index(स्थिर काष्ठा net *net, u32 index)
अणु
	काष्ठा ib_device *device;

	करोwn_पढ़ो(&devices_rwsem);
	device = xa_load(&devices, index);
	अगर (device) अणु
		अगर (!rdma_dev_access_netns(device, net)) अणु
			device = शून्य;
			जाओ out;
		पूर्ण

		अगर (!ib_device_try_get(device))
			device = शून्य;
	पूर्ण
out:
	up_पढ़ो(&devices_rwsem);
	वापस device;
पूर्ण

/**
 * ib_device_put - Release IB device reference
 * @device: device whose reference to be released
 *
 * ib_device_put() releases reference to the IB device to allow it to be
 * unरेजिस्टरed and eventually मुक्त.
 */
व्योम ib_device_put(काष्ठा ib_device *device)
अणु
	अगर (refcount_dec_and_test(&device->refcount))
		complete(&device->unreg_completion);
पूर्ण
EXPORT_SYMBOL(ib_device_put);

अटल काष्ठा ib_device *__ib_device_get_by_name(स्थिर अक्षर *name)
अणु
	काष्ठा ib_device *device;
	अचिन्हित दीर्घ index;

	xa_क्रम_each (&devices, index, device)
		अगर (!म_भेद(name, dev_name(&device->dev)))
			वापस device;

	वापस शून्य;
पूर्ण

/**
 * ib_device_get_by_name - Find an IB device by name
 * @name: The name to look क्रम
 * @driver_id: The driver ID that must match (RDMA_DRIVER_UNKNOWN matches all)
 *
 * Find and hold an ib_device by its name. The caller must call
 * ib_device_put() on the वापसed poपूर्णांकer.
 */
काष्ठा ib_device *ib_device_get_by_name(स्थिर अक्षर *name,
					क्रमागत rdma_driver_id driver_id)
अणु
	काष्ठा ib_device *device;

	करोwn_पढ़ो(&devices_rwsem);
	device = __ib_device_get_by_name(name);
	अगर (device && driver_id != RDMA_DRIVER_UNKNOWN &&
	    device->ops.driver_id != driver_id)
		device = शून्य;

	अगर (device) अणु
		अगर (!ib_device_try_get(device))
			device = शून्य;
	पूर्ण
	up_पढ़ो(&devices_rwsem);
	वापस device;
पूर्ण
EXPORT_SYMBOL(ib_device_get_by_name);

अटल पूर्णांक नाम_compat_devs(काष्ठा ib_device *device)
अणु
	काष्ठा ib_core_device *cdev;
	अचिन्हित दीर्घ index;
	पूर्णांक ret = 0;

	mutex_lock(&device->compat_devs_mutex);
	xa_क्रम_each (&device->compat_devs, index, cdev) अणु
		ret = device_नाम(&cdev->dev, dev_name(&device->dev));
		अगर (ret) अणु
			dev_warn(&cdev->dev,
				 "Fail to rename compatdev to new name %s\n",
				 dev_name(&device->dev));
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&device->compat_devs_mutex);
	वापस ret;
पूर्ण

पूर्णांक ib_device_नाम(काष्ठा ib_device *ibdev, स्थिर अक्षर *name)
अणु
	अचिन्हित दीर्घ index;
	व्योम *client_data;
	पूर्णांक ret;

	करोwn_ग_लिखो(&devices_rwsem);
	अगर (!म_भेद(name, dev_name(&ibdev->dev))) अणु
		up_ग_लिखो(&devices_rwsem);
		वापस 0;
	पूर्ण

	अगर (__ib_device_get_by_name(name)) अणु
		up_ग_लिखो(&devices_rwsem);
		वापस -EEXIST;
	पूर्ण

	ret = device_नाम(&ibdev->dev, name);
	अगर (ret) अणु
		up_ग_लिखो(&devices_rwsem);
		वापस ret;
	पूर्ण

	strlcpy(ibdev->name, name, IB_DEVICE_NAME_MAX);
	ret = नाम_compat_devs(ibdev);

	करोwngrade_ग_लिखो(&devices_rwsem);
	करोwn_पढ़ो(&ibdev->client_data_rwsem);
	xan_क्रम_each_marked(&ibdev->client_data, index, client_data,
			    CLIENT_DATA_REGISTERED) अणु
		काष्ठा ib_client *client = xa_load(&clients, index);

		अगर (!client || !client->नाम)
			जारी;

		client->नाम(ibdev, client_data);
	पूर्ण
	up_पढ़ो(&ibdev->client_data_rwsem);
	up_पढ़ो(&devices_rwsem);
	वापस 0;
पूर्ण

पूर्णांक ib_device_set_dim(काष्ठा ib_device *ibdev, u8 use_dim)
अणु
	अगर (use_dim > 1)
		वापस -EINVAL;
	ibdev->use_cq_dim = use_dim;

	वापस 0;
पूर्ण

अटल पूर्णांक alloc_name(काष्ठा ib_device *ibdev, स्थिर अक्षर *name)
अणु
	काष्ठा ib_device *device;
	अचिन्हित दीर्घ index;
	काष्ठा ida inuse;
	पूर्णांक rc;
	पूर्णांक i;

	lockdep_निश्चित_held_ग_लिखो(&devices_rwsem);
	ida_init(&inuse);
	xa_क्रम_each (&devices, index, device) अणु
		अक्षर buf[IB_DEVICE_NAME_MAX];

		अगर (माला_पूछो(dev_name(&device->dev), name, &i) != 1)
			जारी;
		अगर (i < 0 || i >= पूर्णांक_उच्च)
			जारी;
		snम_लिखो(buf, माप buf, name, i);
		अगर (म_भेद(buf, dev_name(&device->dev)) != 0)
			जारी;

		rc = ida_alloc_range(&inuse, i, i, GFP_KERNEL);
		अगर (rc < 0)
			जाओ out;
	पूर्ण

	rc = ida_alloc(&inuse, GFP_KERNEL);
	अगर (rc < 0)
		जाओ out;

	rc = dev_set_name(&ibdev->dev, name, rc);
out:
	ida_destroy(&inuse);
	वापस rc;
पूर्ण

अटल व्योम ib_device_release(काष्ठा device *device)
अणु
	काष्ठा ib_device *dev = container_of(device, काष्ठा ib_device, dev);

	मुक्त_netdevs(dev);
	WARN_ON(refcount_पढ़ो(&dev->refcount));
	अगर (dev->port_data) अणु
		ib_cache_release_one(dev);
		ib_security_release_port_pkey_list(dev);
		rdma_counter_release(dev);
		kमुक्त_rcu(container_of(dev->port_data, काष्ठा ib_port_data_rcu,
				       pdata[0]),
			  rcu_head);
	पूर्ण

	mutex_destroy(&dev->unregistration_lock);
	mutex_destroy(&dev->compat_devs_mutex);

	xa_destroy(&dev->compat_devs);
	xa_destroy(&dev->client_data);
	kमुक्त_rcu(dev, rcu_head);
पूर्ण

अटल पूर्णांक ib_device_uevent(काष्ठा device *device,
			    काष्ठा kobj_uevent_env *env)
अणु
	अगर (add_uevent_var(env, "NAME=%s", dev_name(device)))
		वापस -ENOMEM;

	/*
	 * It would be nice to pass the node GUID with the event...
	 */

	वापस 0;
पूर्ण

अटल स्थिर व्योम *net_namespace(काष्ठा device *d)
अणु
	काष्ठा ib_core_device *coredev =
			container_of(d, काष्ठा ib_core_device, dev);

	वापस पढ़ो_pnet(&coredev->rdma_net);
पूर्ण

अटल काष्ठा class ib_class = अणु
	.name    = "infiniband",
	.dev_release = ib_device_release,
	.dev_uevent = ib_device_uevent,
	.ns_type = &net_ns_type_operations,
	.namespace = net_namespace,
पूर्ण;

अटल व्योम rdma_init_coredev(काष्ठा ib_core_device *coredev,
			      काष्ठा ib_device *dev, काष्ठा net *net)
अणु
	/* This BUILD_BUG_ON is पूर्णांकended to catch layout change
	 * of जोड़ of ib_core_device and device.
	 * dev must be the first element as ib_core and providers
	 * driver uses it. Adding anything in ib_core_device beक्रमe
	 * device will अवरोध this assumption.
	 */
	BUILD_BUG_ON(दुरत्व(काष्ठा ib_device, coredev.dev) !=
		     दुरत्व(काष्ठा ib_device, dev));

	coredev->dev.class = &ib_class;
	coredev->dev.groups = dev->groups;
	device_initialize(&coredev->dev);
	coredev->owner = dev;
	INIT_LIST_HEAD(&coredev->port_list);
	ग_लिखो_pnet(&coredev->rdma_net, net);
पूर्ण

/**
 * _ib_alloc_device - allocate an IB device काष्ठा
 * @size:size of काष्ठाure to allocate
 *
 * Low-level drivers should use ib_alloc_device() to allocate &काष्ठा
 * ib_device.  @size is the size of the काष्ठाure to be allocated,
 * including any निजी data used by the low-level driver.
 * ib_dealloc_device() must be used to मुक्त काष्ठाures allocated with
 * ib_alloc_device().
 */
काष्ठा ib_device *_ib_alloc_device(माप_प्रकार size)
अणु
	काष्ठा ib_device *device;
	अचिन्हित पूर्णांक i;

	अगर (WARN_ON(size < माप(काष्ठा ib_device)))
		वापस शून्य;

	device = kzalloc(size, GFP_KERNEL);
	अगर (!device)
		वापस शून्य;

	अगर (rdma_restrack_init(device)) अणु
		kमुक्त(device);
		वापस शून्य;
	पूर्ण

	device->groups[0] = &ib_dev_attr_group;
	rdma_init_coredev(&device->coredev, device, &init_net);

	INIT_LIST_HEAD(&device->event_handler_list);
	spin_lock_init(&device->qp_खोलो_list_lock);
	init_rwsem(&device->event_handler_rwsem);
	mutex_init(&device->unregistration_lock);
	/*
	 * client_data needs to be alloc because we करोn't want our mark to be
	 * destroyed अगर the user stores शून्य in the client data.
	 */
	xa_init_flags(&device->client_data, XA_FLAGS_ALLOC);
	init_rwsem(&device->client_data_rwsem);
	xa_init_flags(&device->compat_devs, XA_FLAGS_ALLOC);
	mutex_init(&device->compat_devs_mutex);
	init_completion(&device->unreg_completion);
	INIT_WORK(&device->unregistration_work, ib_unरेजिस्टर_work);

	spin_lock_init(&device->cq_pools_lock);
	क्रम (i = 0; i < ARRAY_SIZE(device->cq_pools); i++)
		INIT_LIST_HEAD(&device->cq_pools[i]);

	device->uverbs_cmd_mask =
		BIT_ULL(IB_USER_VERBS_CMD_ALLOC_MW) |
		BIT_ULL(IB_USER_VERBS_CMD_ALLOC_PD) |
		BIT_ULL(IB_USER_VERBS_CMD_ATTACH_MCAST) |
		BIT_ULL(IB_USER_VERBS_CMD_CLOSE_XRCD) |
		BIT_ULL(IB_USER_VERBS_CMD_CREATE_AH) |
		BIT_ULL(IB_USER_VERBS_CMD_CREATE_COMP_CHANNEL) |
		BIT_ULL(IB_USER_VERBS_CMD_CREATE_CQ) |
		BIT_ULL(IB_USER_VERBS_CMD_CREATE_QP) |
		BIT_ULL(IB_USER_VERBS_CMD_CREATE_SRQ) |
		BIT_ULL(IB_USER_VERBS_CMD_CREATE_XSRQ) |
		BIT_ULL(IB_USER_VERBS_CMD_DEALLOC_MW) |
		BIT_ULL(IB_USER_VERBS_CMD_DEALLOC_PD) |
		BIT_ULL(IB_USER_VERBS_CMD_DEREG_MR) |
		BIT_ULL(IB_USER_VERBS_CMD_DESTROY_AH) |
		BIT_ULL(IB_USER_VERBS_CMD_DESTROY_CQ) |
		BIT_ULL(IB_USER_VERBS_CMD_DESTROY_QP) |
		BIT_ULL(IB_USER_VERBS_CMD_DESTROY_SRQ) |
		BIT_ULL(IB_USER_VERBS_CMD_DETACH_MCAST) |
		BIT_ULL(IB_USER_VERBS_CMD_GET_CONTEXT) |
		BIT_ULL(IB_USER_VERBS_CMD_MODIFY_QP) |
		BIT_ULL(IB_USER_VERBS_CMD_MODIFY_SRQ) |
		BIT_ULL(IB_USER_VERBS_CMD_OPEN_QP) |
		BIT_ULL(IB_USER_VERBS_CMD_OPEN_XRCD) |
		BIT_ULL(IB_USER_VERBS_CMD_QUERY_DEVICE) |
		BIT_ULL(IB_USER_VERBS_CMD_QUERY_PORT) |
		BIT_ULL(IB_USER_VERBS_CMD_QUERY_QP) |
		BIT_ULL(IB_USER_VERBS_CMD_QUERY_SRQ) |
		BIT_ULL(IB_USER_VERBS_CMD_REG_MR) |
		BIT_ULL(IB_USER_VERBS_CMD_REREG_MR) |
		BIT_ULL(IB_USER_VERBS_CMD_RESIZE_CQ);
	वापस device;
पूर्ण
EXPORT_SYMBOL(_ib_alloc_device);

/**
 * ib_dealloc_device - मुक्त an IB device काष्ठा
 * @device:काष्ठाure to मुक्त
 *
 * Free a काष्ठाure allocated with ib_alloc_device().
 */
व्योम ib_dealloc_device(काष्ठा ib_device *device)
अणु
	अगर (device->ops.dealloc_driver)
		device->ops.dealloc_driver(device);

	/*
	 * ib_unरेजिस्टर_driver() requires all devices to reमुख्य in the xarray
	 * जबतक their ops are callable. The last op we call is dealloc_driver
	 * above.  This is needed to create a fence on op callbacks prior to
	 * allowing the driver module to unload.
	 */
	करोwn_ग_लिखो(&devices_rwsem);
	अगर (xa_load(&devices, device->index) == device)
		xa_erase(&devices, device->index);
	up_ग_लिखो(&devices_rwsem);

	/* Expedite releasing netdev references */
	मुक्त_netdevs(device);

	WARN_ON(!xa_empty(&device->compat_devs));
	WARN_ON(!xa_empty(&device->client_data));
	WARN_ON(refcount_पढ़ो(&device->refcount));
	rdma_restrack_clean(device);
	/* Balances with device_initialize */
	put_device(&device->dev);
पूर्ण
EXPORT_SYMBOL(ib_dealloc_device);

/*
 * add_client_context() and हटाओ_client_context() must be safe against
 * parallel calls on the same device - registration/unregistration of both the
 * device and client can be occurring in parallel.
 *
 * The routines need to be a fence, any caller must not वापस until the add
 * or हटाओ is fully completed.
 */
अटल पूर्णांक add_client_context(काष्ठा ib_device *device,
			      काष्ठा ib_client *client)
अणु
	पूर्णांक ret = 0;

	अगर (!device->kverbs_provider && !client->no_kverbs_req)
		वापस 0;

	करोwn_ग_लिखो(&device->client_data_rwsem);
	/*
	 * So दीर्घ as the client is रेजिस्टरed hold both the client and device
	 * unregistration locks.
	 */
	अगर (!refcount_inc_not_zero(&client->uses))
		जाओ out_unlock;
	refcount_inc(&device->refcount);

	/*
	 * Another caller to add_client_context got here first and has alपढ़ोy
	 * completely initialized context.
	 */
	अगर (xa_get_mark(&device->client_data, client->client_id,
		    CLIENT_DATA_REGISTERED))
		जाओ out;

	ret = xa_err(xa_store(&device->client_data, client->client_id, शून्य,
			      GFP_KERNEL));
	अगर (ret)
		जाओ out;
	करोwngrade_ग_लिखो(&device->client_data_rwsem);
	अगर (client->add) अणु
		अगर (client->add(device)) अणु
			/*
			 * If a client fails to add then the error code is
			 * ignored, but we won't call any more ops on this
			 * client.
			 */
			xa_erase(&device->client_data, client->client_id);
			up_पढ़ो(&device->client_data_rwsem);
			ib_device_put(device);
			ib_client_put(client);
			वापस 0;
		पूर्ण
	पूर्ण

	/* Readers shall not see a client until add has been completed */
	xa_set_mark(&device->client_data, client->client_id,
		    CLIENT_DATA_REGISTERED);
	up_पढ़ो(&device->client_data_rwsem);
	वापस 0;

out:
	ib_device_put(device);
	ib_client_put(client);
out_unlock:
	up_ग_लिखो(&device->client_data_rwsem);
	वापस ret;
पूर्ण

अटल व्योम हटाओ_client_context(काष्ठा ib_device *device,
				  अचिन्हित पूर्णांक client_id)
अणु
	काष्ठा ib_client *client;
	व्योम *client_data;

	करोwn_ग_लिखो(&device->client_data_rwsem);
	अगर (!xa_get_mark(&device->client_data, client_id,
			 CLIENT_DATA_REGISTERED)) अणु
		up_ग_लिखो(&device->client_data_rwsem);
		वापस;
	पूर्ण
	client_data = xa_load(&device->client_data, client_id);
	xa_clear_mark(&device->client_data, client_id, CLIENT_DATA_REGISTERED);
	client = xa_load(&clients, client_id);
	up_ग_लिखो(&device->client_data_rwsem);

	/*
	 * Notice we cannot be holding any exclusive locks when calling the
	 * हटाओ callback as the हटाओ callback can recurse back पूर्णांकo any
	 * खुला functions in this module and thus try क्रम any locks those
	 * functions take.
	 *
	 * For this reason clients and drivers should not call the
	 * unregistration functions will holdling any locks.
	 */
	अगर (client->हटाओ)
		client->हटाओ(device, client_data);

	xa_erase(&device->client_data, client_id);
	ib_device_put(device);
	ib_client_put(client);
पूर्ण

अटल पूर्णांक alloc_port_data(काष्ठा ib_device *device)
अणु
	काष्ठा ib_port_data_rcu *pdata_rcu;
	u32 port;

	अगर (device->port_data)
		वापस 0;

	/* This can only be called once the physical port range is defined */
	अगर (WARN_ON(!device->phys_port_cnt))
		वापस -EINVAL;

	/* Reserve U32_MAX so the logic to go over all the ports is sane */
	अगर (WARN_ON(device->phys_port_cnt == U32_MAX))
		वापस -EINVAL;

	/*
	 * device->port_data is indexed directly by the port number to make
	 * access to this data as efficient as possible.
	 *
	 * Thereक्रमe port_data is declared as a 1 based array with potential
	 * empty slots at the beginning.
	 */
	pdata_rcu = kzalloc(काष्ठा_size(pdata_rcu, pdata,
					rdma_end_port(device) + 1),
			    GFP_KERNEL);
	अगर (!pdata_rcu)
		वापस -ENOMEM;
	/*
	 * The rcu_head is put in front of the port data array and the stored
	 * poपूर्णांकer is adjusted since we never need to see that member until
	 * kमुक्त_rcu.
	 */
	device->port_data = pdata_rcu->pdata;

	rdma_क्रम_each_port (device, port) अणु
		काष्ठा ib_port_data *pdata = &device->port_data[port];

		pdata->ib_dev = device;
		spin_lock_init(&pdata->pkey_list_lock);
		INIT_LIST_HEAD(&pdata->pkey_list);
		spin_lock_init(&pdata->netdev_lock);
		INIT_HLIST_NODE(&pdata->ndev_hash_link);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक verअगरy_immutable(स्थिर काष्ठा ib_device *dev, u32 port)
अणु
	वापस WARN_ON(!rdma_cap_ib_mad(dev, port) &&
			    rdma_max_mad_size(dev, port) != 0);
पूर्ण

अटल पूर्णांक setup_port_data(काष्ठा ib_device *device)
अणु
	u32 port;
	पूर्णांक ret;

	ret = alloc_port_data(device);
	अगर (ret)
		वापस ret;

	rdma_क्रम_each_port (device, port) अणु
		काष्ठा ib_port_data *pdata = &device->port_data[port];

		ret = device->ops.get_port_immutable(device, port,
						     &pdata->immutable);
		अगर (ret)
			वापस ret;

		अगर (verअगरy_immutable(device, port))
			वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * ib_port_immutable_पढ़ो() - Read rdma port's immutable data
 * @dev: IB device
 * @port: port number whose immutable data to पढ़ो. It starts with index 1 and
 *        valid upto including rdma_end_port().
 */
स्थिर काष्ठा ib_port_immutable*
ib_port_immutable_पढ़ो(काष्ठा ib_device *dev, अचिन्हित पूर्णांक port)
अणु
	WARN_ON(!rdma_is_port_valid(dev, port));
	वापस &dev->port_data[port].immutable;
पूर्ण
EXPORT_SYMBOL(ib_port_immutable_पढ़ो);

व्योम ib_get_device_fw_str(काष्ठा ib_device *dev, अक्षर *str)
अणु
	अगर (dev->ops.get_dev_fw_str)
		dev->ops.get_dev_fw_str(dev, str);
	अन्यथा
		str[0] = '\0';
पूर्ण
EXPORT_SYMBOL(ib_get_device_fw_str);

अटल व्योम ib_policy_change_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ib_device *dev;
	अचिन्हित दीर्घ index;

	करोwn_पढ़ो(&devices_rwsem);
	xa_क्रम_each_marked (&devices, index, dev, DEVICE_REGISTERED) अणु
		अचिन्हित पूर्णांक i;

		rdma_क्रम_each_port (dev, i) अणु
			u64 sp;
			पूर्णांक ret = ib_get_cached_subnet_prefix(dev,
							      i,
							      &sp);

			WARN_ONCE(ret,
				  "ib_get_cached_subnet_prefix err: %d, this should never happen here\n",
				  ret);
			अगर (!ret)
				ib_security_cache_change(dev, i, sp);
		पूर्ण
	पूर्ण
	up_पढ़ो(&devices_rwsem);
पूर्ण

अटल पूर्णांक ib_security_change(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ event,
			      व्योम *lsm_data)
अणु
	अगर (event != LSM_POLICY_CHANGE)
		वापस NOTIFY_DONE;

	schedule_work(&ib_policy_change_work);
	ib_mad_agent_security_change();

	वापस NOTIFY_OK;
पूर्ण

अटल व्योम compatdev_release(काष्ठा device *dev)
अणु
	काष्ठा ib_core_device *cdev =
		container_of(dev, काष्ठा ib_core_device, dev);

	kमुक्त(cdev);
पूर्ण

अटल पूर्णांक add_one_compat_dev(काष्ठा ib_device *device,
			      काष्ठा rdma_dev_net *rnet)
अणु
	काष्ठा ib_core_device *cdev;
	पूर्णांक ret;

	lockdep_निश्चित_held(&rdma_nets_rwsem);
	अगर (!ib_devices_shared_netns)
		वापस 0;

	/*
	 * Create and add compat device in all namespaces other than where it
	 * is currently bound to.
	 */
	अगर (net_eq(पढ़ो_pnet(&rnet->net),
		   पढ़ो_pnet(&device->coredev.rdma_net)))
		वापस 0;

	/*
	 * The first of init_net() or ib_रेजिस्टर_device() to take the
	 * compat_devs_mutex wins and माला_लो to add the device. Others will रुको
	 * क्रम completion here.
	 */
	mutex_lock(&device->compat_devs_mutex);
	cdev = xa_load(&device->compat_devs, rnet->id);
	अगर (cdev) अणु
		ret = 0;
		जाओ करोne;
	पूर्ण
	ret = xa_reserve(&device->compat_devs, rnet->id, GFP_KERNEL);
	अगर (ret)
		जाओ करोne;

	cdev = kzalloc(माप(*cdev), GFP_KERNEL);
	अगर (!cdev) अणु
		ret = -ENOMEM;
		जाओ cdev_err;
	पूर्ण

	cdev->dev.parent = device->dev.parent;
	rdma_init_coredev(cdev, device, पढ़ो_pnet(&rnet->net));
	cdev->dev.release = compatdev_release;
	ret = dev_set_name(&cdev->dev, "%s", dev_name(&device->dev));
	अगर (ret)
		जाओ add_err;

	ret = device_add(&cdev->dev);
	अगर (ret)
		जाओ add_err;
	ret = ib_setup_port_attrs(cdev);
	अगर (ret)
		जाओ port_err;

	ret = xa_err(xa_store(&device->compat_devs, rnet->id,
			      cdev, GFP_KERNEL));
	अगर (ret)
		जाओ insert_err;

	mutex_unlock(&device->compat_devs_mutex);
	वापस 0;

insert_err:
	ib_मुक्त_port_attrs(cdev);
port_err:
	device_del(&cdev->dev);
add_err:
	put_device(&cdev->dev);
cdev_err:
	xa_release(&device->compat_devs, rnet->id);
करोne:
	mutex_unlock(&device->compat_devs_mutex);
	वापस ret;
पूर्ण

अटल व्योम हटाओ_one_compat_dev(काष्ठा ib_device *device, u32 id)
अणु
	काष्ठा ib_core_device *cdev;

	mutex_lock(&device->compat_devs_mutex);
	cdev = xa_erase(&device->compat_devs, id);
	mutex_unlock(&device->compat_devs_mutex);
	अगर (cdev) अणु
		ib_मुक्त_port_attrs(cdev);
		device_del(&cdev->dev);
		put_device(&cdev->dev);
	पूर्ण
पूर्ण

अटल व्योम हटाओ_compat_devs(काष्ठा ib_device *device)
अणु
	काष्ठा ib_core_device *cdev;
	अचिन्हित दीर्घ index;

	xa_क्रम_each (&device->compat_devs, index, cdev)
		हटाओ_one_compat_dev(device, index);
पूर्ण

अटल पूर्णांक add_compat_devs(काष्ठा ib_device *device)
अणु
	काष्ठा rdma_dev_net *rnet;
	अचिन्हित दीर्घ index;
	पूर्णांक ret = 0;

	lockdep_निश्चित_held(&devices_rwsem);

	करोwn_पढ़ो(&rdma_nets_rwsem);
	xa_क्रम_each (&rdma_nets, index, rnet) अणु
		ret = add_one_compat_dev(device, rnet);
		अगर (ret)
			अवरोध;
	पूर्ण
	up_पढ़ो(&rdma_nets_rwsem);
	वापस ret;
पूर्ण

अटल व्योम हटाओ_all_compat_devs(व्योम)
अणु
	काष्ठा ib_compat_device *cdev;
	काष्ठा ib_device *dev;
	अचिन्हित दीर्घ index;

	करोwn_पढ़ो(&devices_rwsem);
	xa_क्रम_each (&devices, index, dev) अणु
		अचिन्हित दीर्घ c_index = 0;

		/* Hold nets_rwsem so that any other thपढ़ो modअगरying this
		 * प्रणाली param can sync with this thपढ़ो.
		 */
		करोwn_पढ़ो(&rdma_nets_rwsem);
		xa_क्रम_each (&dev->compat_devs, c_index, cdev)
			हटाओ_one_compat_dev(dev, c_index);
		up_पढ़ो(&rdma_nets_rwsem);
	पूर्ण
	up_पढ़ो(&devices_rwsem);
पूर्ण

अटल पूर्णांक add_all_compat_devs(व्योम)
अणु
	काष्ठा rdma_dev_net *rnet;
	काष्ठा ib_device *dev;
	अचिन्हित दीर्घ index;
	पूर्णांक ret = 0;

	करोwn_पढ़ो(&devices_rwsem);
	xa_क्रम_each_marked (&devices, index, dev, DEVICE_REGISTERED) अणु
		अचिन्हित दीर्घ net_index = 0;

		/* Hold nets_rwsem so that any other thपढ़ो modअगरying this
		 * प्रणाली param can sync with this thपढ़ो.
		 */
		करोwn_पढ़ो(&rdma_nets_rwsem);
		xa_क्रम_each (&rdma_nets, net_index, rnet) अणु
			ret = add_one_compat_dev(dev, rnet);
			अगर (ret)
				अवरोध;
		पूर्ण
		up_पढ़ो(&rdma_nets_rwsem);
	पूर्ण
	up_पढ़ो(&devices_rwsem);
	अगर (ret)
		हटाओ_all_compat_devs();
	वापस ret;
पूर्ण

पूर्णांक rdma_compatdev_set(u8 enable)
अणु
	काष्ठा rdma_dev_net *rnet;
	अचिन्हित दीर्घ index;
	पूर्णांक ret = 0;

	करोwn_ग_लिखो(&rdma_nets_rwsem);
	अगर (ib_devices_shared_netns == enable) अणु
		up_ग_लिखो(&rdma_nets_rwsem);
		वापस 0;
	पूर्ण

	/* enable/disable of compat devices is not supported
	 * when more than शेष init_net exists.
	 */
	xa_क्रम_each (&rdma_nets, index, rnet) अणु
		ret++;
		अवरोध;
	पूर्ण
	अगर (!ret)
		ib_devices_shared_netns = enable;
	up_ग_लिखो(&rdma_nets_rwsem);
	अगर (ret)
		वापस -EBUSY;

	अगर (enable)
		ret = add_all_compat_devs();
	अन्यथा
		हटाओ_all_compat_devs();
	वापस ret;
पूर्ण

अटल व्योम rdma_dev_निकास_net(काष्ठा net *net)
अणु
	काष्ठा rdma_dev_net *rnet = rdma_net_to_dev_net(net);
	काष्ठा ib_device *dev;
	अचिन्हित दीर्घ index;
	पूर्णांक ret;

	करोwn_ग_लिखो(&rdma_nets_rwsem);
	/*
	 * Prevent the ID from being re-used and hide the id from xa_क्रम_each.
	 */
	ret = xa_err(xa_store(&rdma_nets, rnet->id, शून्य, GFP_KERNEL));
	WARN_ON(ret);
	up_ग_लिखो(&rdma_nets_rwsem);

	करोwn_पढ़ो(&devices_rwsem);
	xa_क्रम_each (&devices, index, dev) अणु
		get_device(&dev->dev);
		/*
		 * Release the devices_rwsem so that pontentially blocking
		 * device_del, करोesn't hold the devices_rwsem क्रम too दीर्घ.
		 */
		up_पढ़ो(&devices_rwsem);

		हटाओ_one_compat_dev(dev, rnet->id);

		/*
		 * If the real device is in the NS then move it back to init.
		 */
		rdma_dev_change_netns(dev, net, &init_net);

		put_device(&dev->dev);
		करोwn_पढ़ो(&devices_rwsem);
	पूर्ण
	up_पढ़ो(&devices_rwsem);

	rdma_nl_net_निकास(rnet);
	xa_erase(&rdma_nets, rnet->id);
पूर्ण

अटल __net_init पूर्णांक rdma_dev_init_net(काष्ठा net *net)
अणु
	काष्ठा rdma_dev_net *rnet = rdma_net_to_dev_net(net);
	अचिन्हित दीर्घ index;
	काष्ठा ib_device *dev;
	पूर्णांक ret;

	ग_लिखो_pnet(&rnet->net, net);

	ret = rdma_nl_net_init(rnet);
	अगर (ret)
		वापस ret;

	/* No need to create any compat devices in शेष init_net. */
	अगर (net_eq(net, &init_net))
		वापस 0;

	ret = xa_alloc(&rdma_nets, &rnet->id, rnet, xa_limit_32b, GFP_KERNEL);
	अगर (ret) अणु
		rdma_nl_net_निकास(rnet);
		वापस ret;
	पूर्ण

	करोwn_पढ़ो(&devices_rwsem);
	xa_क्रम_each_marked (&devices, index, dev, DEVICE_REGISTERED) अणु
		/* Hold nets_rwsem so that netlink command cannot change
		 * प्रणाली configuration क्रम device sharing mode.
		 */
		करोwn_पढ़ो(&rdma_nets_rwsem);
		ret = add_one_compat_dev(dev, rnet);
		up_पढ़ो(&rdma_nets_rwsem);
		अगर (ret)
			अवरोध;
	पूर्ण
	up_पढ़ो(&devices_rwsem);

	अगर (ret)
		rdma_dev_निकास_net(net);

	वापस ret;
पूर्ण

/*
 * Assign the unique string device name and the unique device index. This is
 * unकरोne by ib_dealloc_device.
 */
अटल पूर्णांक assign_name(काष्ठा ib_device *device, स्थिर अक्षर *name)
अणु
	अटल u32 last_id;
	पूर्णांक ret;

	करोwn_ग_लिखो(&devices_rwsem);
	/* Assign a unique name to the device */
	अगर (म_अक्षर(name, '%'))
		ret = alloc_name(device, name);
	अन्यथा
		ret = dev_set_name(&device->dev, name);
	अगर (ret)
		जाओ out;

	अगर (__ib_device_get_by_name(dev_name(&device->dev))) अणु
		ret = -ENखाता;
		जाओ out;
	पूर्ण
	strlcpy(device->name, dev_name(&device->dev), IB_DEVICE_NAME_MAX);

	ret = xa_alloc_cyclic(&devices, &device->index, device, xa_limit_31b,
			&last_id, GFP_KERNEL);
	अगर (ret > 0)
		ret = 0;

out:
	up_ग_लिखो(&devices_rwsem);
	वापस ret;
पूर्ण

/*
 * setup_device() allocates memory and sets up data that requires calling the
 * device ops, this is the only reason these actions are not करोne during
 * ib_alloc_device. It is unकरोne by ib_dealloc_device().
 */
अटल पूर्णांक setup_device(काष्ठा ib_device *device)
अणु
	काष्ठा ib_udata uhw = अणु.outlen = 0, .inlen = 0पूर्ण;
	पूर्णांक ret;

	ib_device_check_mandatory(device);

	ret = setup_port_data(device);
	अगर (ret) अणु
		dev_warn(&device->dev, "Couldn't create per-port data\n");
		वापस ret;
	पूर्ण

	स_रखो(&device->attrs, 0, माप(device->attrs));
	ret = device->ops.query_device(device, &device->attrs, &uhw);
	अगर (ret) अणु
		dev_warn(&device->dev,
			 "Couldn't query the device attributes\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम disable_device(काष्ठा ib_device *device)
अणु
	u32 cid;

	WARN_ON(!refcount_पढ़ो(&device->refcount));

	करोwn_ग_लिखो(&devices_rwsem);
	xa_clear_mark(&devices, device->index, DEVICE_REGISTERED);
	up_ग_लिखो(&devices_rwsem);

	/*
	 * Remove clients in LIFO order, see assign_client_id. This could be
	 * more efficient अगर xarray learns to reverse iterate. Since no new
	 * clients can be added to this ib_device past this poपूर्णांक we only need
	 * the maximum possible client_id value here.
	 */
	करोwn_पढ़ो(&clients_rwsem);
	cid = highest_client_id;
	up_पढ़ो(&clients_rwsem);
	जबतक (cid) अणु
		cid--;
		हटाओ_client_context(device, cid);
	पूर्ण

	ib_cq_pool_cleanup(device);

	/* Pairs with refcount_set in enable_device */
	ib_device_put(device);
	रुको_क्रम_completion(&device->unreg_completion);

	/*
	 * compat devices must be हटाओd after device refcount drops to zero.
	 * Otherwise init_net() may add more compatdevs after removing compat
	 * devices and beक्रमe device is disabled.
	 */
	हटाओ_compat_devs(device);
पूर्ण

/*
 * An enabled device is visible to all clients and to all the खुला facing
 * APIs that वापस a device poपूर्णांकer. This always वापसs with a new get, even
 * अगर it fails.
 */
अटल पूर्णांक enable_device_and_get(काष्ठा ib_device *device)
अणु
	काष्ठा ib_client *client;
	अचिन्हित दीर्घ index;
	पूर्णांक ret = 0;

	/*
	 * One ref beदीर्घs to the xa and the other beदीर्घs to this
	 * thपढ़ो. This is needed to guard against parallel unregistration.
	 */
	refcount_set(&device->refcount, 2);
	करोwn_ग_लिखो(&devices_rwsem);
	xa_set_mark(&devices, device->index, DEVICE_REGISTERED);

	/*
	 * By using करोwngrade_ग_लिखो() we ensure that no other thपढ़ो can clear
	 * DEVICE_REGISTERED जबतक we are completing the client setup.
	 */
	करोwngrade_ग_लिखो(&devices_rwsem);

	अगर (device->ops.enable_driver) अणु
		ret = device->ops.enable_driver(device);
		अगर (ret)
			जाओ out;
	पूर्ण

	करोwn_पढ़ो(&clients_rwsem);
	xa_क्रम_each_marked (&clients, index, client, CLIENT_REGISTERED) अणु
		ret = add_client_context(device, client);
		अगर (ret)
			अवरोध;
	पूर्ण
	up_पढ़ो(&clients_rwsem);
	अगर (!ret)
		ret = add_compat_devs(device);
out:
	up_पढ़ो(&devices_rwsem);
	वापस ret;
पूर्ण

अटल व्योम prevent_dealloc_device(काष्ठा ib_device *ib_dev)
अणु
पूर्ण

/**
 * ib_रेजिस्टर_device - Register an IB device with IB core
 * @device: Device to रेजिस्टर
 * @name: unique string device name. This may include a '%' which will
 * 	  cause a unique index to be added to the passed device name.
 * @dma_device: poपूर्णांकer to a DMA-capable device. If %शून्य, then the IB
 *	        device will be used. In this हाल the caller should fully
 *		setup the ibdev क्रम DMA. This usually means using dma_virt_ops.
 *
 * Low-level drivers use ib_रेजिस्टर_device() to रेजिस्टर their
 * devices with the IB core.  All रेजिस्टरed clients will receive a
 * callback क्रम each device that is added. @device must be allocated
 * with ib_alloc_device().
 *
 * If the driver uses ops.dealloc_driver and calls any ib_unरेजिस्टर_device()
 * asynchronously then the device poपूर्णांकer may become मुक्तd as soon as this
 * function वापसs.
 */
पूर्णांक ib_रेजिस्टर_device(काष्ठा ib_device *device, स्थिर अक्षर *name,
		       काष्ठा device *dma_device)
अणु
	पूर्णांक ret;

	ret = assign_name(device, name);
	अगर (ret)
		वापस ret;

	/*
	 * If the caller करोes not provide a DMA capable device then the IB core
	 * will set up ib_sge and scatterlist काष्ठाures that stash the kernel
	 * भव address पूर्णांकo the address field.
	 */
	WARN_ON(dma_device && !dma_device->dma_parms);
	device->dma_device = dma_device;

	ret = setup_device(device);
	अगर (ret)
		वापस ret;

	ret = ib_cache_setup_one(device);
	अगर (ret) अणु
		dev_warn(&device->dev,
			 "Couldn't set up InfiniBand P_Key/GID cache\n");
		वापस ret;
	पूर्ण

	ib_device_रेजिस्टर_rdmacg(device);

	rdma_counter_init(device);

	/*
	 * Ensure that ADD uevent is not fired because it
	 * is too early amd device is not initialized yet.
	 */
	dev_set_uevent_suppress(&device->dev, true);
	ret = device_add(&device->dev);
	अगर (ret)
		जाओ cg_cleanup;

	ret = ib_device_रेजिस्टर_sysfs(device);
	अगर (ret) अणु
		dev_warn(&device->dev,
			 "Couldn't register device with driver model\n");
		जाओ dev_cleanup;
	पूर्ण

	ret = enable_device_and_get(device);
	अगर (ret) अणु
		व्योम (*dealloc_fn)(काष्ठा ib_device *);

		/*
		 * If we hit this error flow then we करोn't want to
		 * स्वतःmatically dealloc the device since the caller is
		 * expected to call ib_dealloc_device() after
		 * ib_रेजिस्टर_device() fails. This is tricky due to the
		 * possibility क्रम a parallel unregistration aदीर्घ with this
		 * error flow. Since we have a refcount here we know any
		 * parallel flow is stopped in disable_device and will see the
		 * special dealloc_driver poपूर्णांकer, causing the responsibility to
		 * ib_dealloc_device() to revert back to this thपढ़ो.
		 */
		dealloc_fn = device->ops.dealloc_driver;
		device->ops.dealloc_driver = prevent_dealloc_device;
		ib_device_put(device);
		__ib_unरेजिस्टर_device(device);
		device->ops.dealloc_driver = dealloc_fn;
		dev_set_uevent_suppress(&device->dev, false);
		वापस ret;
	पूर्ण
	dev_set_uevent_suppress(&device->dev, false);
	/* Mark क्रम userspace that device is पढ़ोy */
	kobject_uevent(&device->dev.kobj, KOBJ_ADD);
	ib_device_put(device);

	वापस 0;

dev_cleanup:
	device_del(&device->dev);
cg_cleanup:
	dev_set_uevent_suppress(&device->dev, false);
	ib_device_unरेजिस्टर_rdmacg(device);
	ib_cache_cleanup_one(device);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ib_रेजिस्टर_device);

/* Callers must hold a get on the device. */
अटल व्योम __ib_unरेजिस्टर_device(काष्ठा ib_device *ib_dev)
अणु
	/*
	 * We have a registration lock so that all the calls to unरेजिस्टर are
	 * fully fenced, once any unरेजिस्टर वापसs the device is truely
	 * unरेजिस्टरed even अगर multiple callers are unरेजिस्टरing it at the
	 * same समय. This also पूर्णांकeracts with the registration flow and
	 * provides sane semantics अगर रेजिस्टर and unरेजिस्टर are racing.
	 */
	mutex_lock(&ib_dev->unregistration_lock);
	अगर (!refcount_पढ़ो(&ib_dev->refcount))
		जाओ out;

	disable_device(ib_dev);

	/* Expedite removing unरेजिस्टरed poपूर्णांकers from the hash table */
	मुक्त_netdevs(ib_dev);

	ib_device_unरेजिस्टर_sysfs(ib_dev);
	device_del(&ib_dev->dev);
	ib_device_unरेजिस्टर_rdmacg(ib_dev);
	ib_cache_cleanup_one(ib_dev);

	/*
	 * Drivers using the new flow may not call ib_dealloc_device except
	 * in error unwind prior to registration success.
	 */
	अगर (ib_dev->ops.dealloc_driver &&
	    ib_dev->ops.dealloc_driver != prevent_dealloc_device) अणु
		WARN_ON(kref_पढ़ो(&ib_dev->dev.kobj.kref) <= 1);
		ib_dealloc_device(ib_dev);
	पूर्ण
out:
	mutex_unlock(&ib_dev->unregistration_lock);
पूर्ण

/**
 * ib_unरेजिस्टर_device - Unरेजिस्टर an IB device
 * @ib_dev: The device to unरेजिस्टर
 *
 * Unरेजिस्टर an IB device.  All clients will receive a हटाओ callback.
 *
 * Callers should call this routine only once, and protect against races with
 * registration. Typically it should only be called as part of a हटाओ
 * callback in an implementation of driver core's काष्ठा device_driver and
 * related.
 *
 * If ops.dealloc_driver is used then ib_dev will be मुक्तd upon वापस from
 * this function.
 */
व्योम ib_unरेजिस्टर_device(काष्ठा ib_device *ib_dev)
अणु
	get_device(&ib_dev->dev);
	__ib_unरेजिस्टर_device(ib_dev);
	put_device(&ib_dev->dev);
पूर्ण
EXPORT_SYMBOL(ib_unरेजिस्टर_device);

/**
 * ib_unरेजिस्टर_device_and_put - Unरेजिस्टर a device जबतक holding a 'get'
 * @ib_dev: The device to unरेजिस्टर
 *
 * This is the same as ib_unरेजिस्टर_device(), except it includes an पूर्णांकernal
 * ib_device_put() that should match a 'get' obtained by the caller.
 *
 * It is safe to call this routine concurrently from multiple thपढ़ोs जबतक
 * holding the 'get'. When the function वापसs the device is fully
 * unरेजिस्टरed.
 *
 * Drivers using this flow MUST use the driver_unरेजिस्टर callback to clean up
 * their resources associated with the device and dealloc it.
 */
व्योम ib_unरेजिस्टर_device_and_put(काष्ठा ib_device *ib_dev)
अणु
	WARN_ON(!ib_dev->ops.dealloc_driver);
	get_device(&ib_dev->dev);
	ib_device_put(ib_dev);
	__ib_unरेजिस्टर_device(ib_dev);
	put_device(&ib_dev->dev);
पूर्ण
EXPORT_SYMBOL(ib_unरेजिस्टर_device_and_put);

/**
 * ib_unरेजिस्टर_driver - Unरेजिस्टर all IB devices क्रम a driver
 * @driver_id: The driver to unरेजिस्टर
 *
 * This implements a fence क्रम device unregistration. It only वापसs once all
 * devices associated with the driver_id have fully completed their
 * unregistration and वापसed from ib_unरेजिस्टर_device*().
 *
 * If device's are not yet unरेजिस्टरed it goes ahead and starts unरेजिस्टरing
 * them.
 *
 * This करोes not block creation of new devices with the given driver_id, that
 * is the responsibility of the caller.
 */
व्योम ib_unरेजिस्टर_driver(क्रमागत rdma_driver_id driver_id)
अणु
	काष्ठा ib_device *ib_dev;
	अचिन्हित दीर्घ index;

	करोwn_पढ़ो(&devices_rwsem);
	xa_क्रम_each (&devices, index, ib_dev) अणु
		अगर (ib_dev->ops.driver_id != driver_id)
			जारी;

		get_device(&ib_dev->dev);
		up_पढ़ो(&devices_rwsem);

		WARN_ON(!ib_dev->ops.dealloc_driver);
		__ib_unरेजिस्टर_device(ib_dev);

		put_device(&ib_dev->dev);
		करोwn_पढ़ो(&devices_rwsem);
	पूर्ण
	up_पढ़ो(&devices_rwsem);
पूर्ण
EXPORT_SYMBOL(ib_unरेजिस्टर_driver);

अटल व्योम ib_unरेजिस्टर_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ib_device *ib_dev =
		container_of(work, काष्ठा ib_device, unregistration_work);

	__ib_unरेजिस्टर_device(ib_dev);
	put_device(&ib_dev->dev);
पूर्ण

/**
 * ib_unरेजिस्टर_device_queued - Unरेजिस्टर a device using a work queue
 * @ib_dev: The device to unरेजिस्टर
 *
 * This schedules an asynchronous unregistration using a WQ क्रम the device. A
 * driver should use this to aव्योम holding locks जबतक करोing unregistration,
 * such as holding the RTNL lock.
 *
 * Drivers using this API must use ib_unरेजिस्टर_driver beक्रमe module unload
 * to ensure that all scheduled unregistrations have completed.
 */
व्योम ib_unरेजिस्टर_device_queued(काष्ठा ib_device *ib_dev)
अणु
	WARN_ON(!refcount_पढ़ो(&ib_dev->refcount));
	WARN_ON(!ib_dev->ops.dealloc_driver);
	get_device(&ib_dev->dev);
	अगर (!queue_work(प्रणाली_unbound_wq, &ib_dev->unregistration_work))
		put_device(&ib_dev->dev);
पूर्ण
EXPORT_SYMBOL(ib_unरेजिस्टर_device_queued);

/*
 * The caller must pass in a device that has the kref held and the refcount
 * released. If the device is in cur_net and still रेजिस्टरed then it is moved
 * पूर्णांकo net.
 */
अटल पूर्णांक rdma_dev_change_netns(काष्ठा ib_device *device, काष्ठा net *cur_net,
				 काष्ठा net *net)
अणु
	पूर्णांक ret2 = -EINVAL;
	पूर्णांक ret;

	mutex_lock(&device->unregistration_lock);

	/*
	 * If a device not under ib_device_get() or अगर the unregistration_lock
	 * is not held, the namespace can be changed, or it can be unरेजिस्टरed.
	 * Check again under the lock.
	 */
	अगर (refcount_पढ़ो(&device->refcount) == 0 ||
	    !net_eq(cur_net, पढ़ो_pnet(&device->coredev.rdma_net))) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	kobject_uevent(&device->dev.kobj, KOBJ_REMOVE);
	disable_device(device);

	/*
	 * At this poपूर्णांक no one can be using the device, so it is safe to
	 * change the namespace.
	 */
	ग_लिखो_pnet(&device->coredev.rdma_net, net);

	करोwn_पढ़ो(&devices_rwsem);
	/*
	 * Currently rdma devices are प्रणाली wide unique. So the device name
	 * is guaranteed मुक्त in the new namespace. Publish the new namespace
	 * at the sysfs level.
	 */
	ret = device_नाम(&device->dev, dev_name(&device->dev));
	up_पढ़ो(&devices_rwsem);
	अगर (ret) अणु
		dev_warn(&device->dev,
			 "%s: Couldn't rename device after namespace change\n",
			 __func__);
		/* Try and put things back and re-enable the device */
		ग_लिखो_pnet(&device->coredev.rdma_net, cur_net);
	पूर्ण

	ret2 = enable_device_and_get(device);
	अगर (ret2) अणु
		/*
		 * This shouldn't really happen, but अगर it करोes, let the user
		 * retry at later poपूर्णांक. So करोn't disable the device.
		 */
		dev_warn(&device->dev,
			 "%s: Couldn't re-enable device after namespace change\n",
			 __func__);
	पूर्ण
	kobject_uevent(&device->dev.kobj, KOBJ_ADD);

	ib_device_put(device);
out:
	mutex_unlock(&device->unregistration_lock);
	अगर (ret)
		वापस ret;
	वापस ret2;
पूर्ण

पूर्णांक ib_device_set_netns_put(काष्ठा sk_buff *skb,
			    काष्ठा ib_device *dev, u32 ns_fd)
अणु
	काष्ठा net *net;
	पूर्णांक ret;

	net = get_net_ns_by_fd(ns_fd);
	अगर (IS_ERR(net)) अणु
		ret = PTR_ERR(net);
		जाओ net_err;
	पूर्ण

	अगर (!netlink_ns_capable(skb, net->user_ns, CAP_NET_ADMIN)) अणु
		ret = -EPERM;
		जाओ ns_err;
	पूर्ण

	/*
	 * Currently supported only क्रम those providers which support
	 * disassociation and करोn't करो port specअगरic sysfs init. Once a
	 * port_cleanup infraकाष्ठाure is implemented, this limitation will be
	 * हटाओd.
	 */
	अगर (!dev->ops.disassociate_ucontext || dev->ops.init_port ||
	    ib_devices_shared_netns) अणु
		ret = -EOPNOTSUPP;
		जाओ ns_err;
	पूर्ण

	get_device(&dev->dev);
	ib_device_put(dev);
	ret = rdma_dev_change_netns(dev, current->nsproxy->net_ns, net);
	put_device(&dev->dev);

	put_net(net);
	वापस ret;

ns_err:
	put_net(net);
net_err:
	ib_device_put(dev);
	वापस ret;
पूर्ण

अटल काष्ठा pernet_operations rdma_dev_net_ops = अणु
	.init = rdma_dev_init_net,
	.निकास = rdma_dev_निकास_net,
	.id = &rdma_dev_net_id,
	.size = माप(काष्ठा rdma_dev_net),
पूर्ण;

अटल पूर्णांक assign_client_id(काष्ठा ib_client *client)
अणु
	पूर्णांक ret;

	करोwn_ग_लिखो(&clients_rwsem);
	/*
	 * The add/हटाओ callbacks must be called in FIFO/LIFO order. To
	 * achieve this we assign client_ids so they are sorted in
	 * registration order.
	 */
	client->client_id = highest_client_id;
	ret = xa_insert(&clients, client->client_id, client, GFP_KERNEL);
	अगर (ret)
		जाओ out;

	highest_client_id++;
	xa_set_mark(&clients, client->client_id, CLIENT_REGISTERED);

out:
	up_ग_लिखो(&clients_rwsem);
	वापस ret;
पूर्ण

अटल व्योम हटाओ_client_id(काष्ठा ib_client *client)
अणु
	करोwn_ग_लिखो(&clients_rwsem);
	xa_erase(&clients, client->client_id);
	क्रम (; highest_client_id; highest_client_id--)
		अगर (xa_load(&clients, highest_client_id - 1))
			अवरोध;
	up_ग_लिखो(&clients_rwsem);
पूर्ण

/**
 * ib_रेजिस्टर_client - Register an IB client
 * @client:Client to रेजिस्टर
 *
 * Upper level users of the IB drivers can use ib_रेजिस्टर_client() to
 * रेजिस्टर callbacks क्रम IB device addition and removal.  When an IB
 * device is added, each रेजिस्टरed client's add method will be called
 * (in the order the clients were रेजिस्टरed), and when a device is
 * हटाओd, each client's हटाओ method will be called (in the reverse
 * order that clients were रेजिस्टरed).  In addition, when
 * ib_रेजिस्टर_client() is called, the client will receive an add
 * callback क्रम all devices alपढ़ोy रेजिस्टरed.
 */
पूर्णांक ib_रेजिस्टर_client(काष्ठा ib_client *client)
अणु
	काष्ठा ib_device *device;
	अचिन्हित दीर्घ index;
	पूर्णांक ret;

	refcount_set(&client->uses, 1);
	init_completion(&client->uses_zero);
	ret = assign_client_id(client);
	अगर (ret)
		वापस ret;

	करोwn_पढ़ो(&devices_rwsem);
	xa_क्रम_each_marked (&devices, index, device, DEVICE_REGISTERED) अणु
		ret = add_client_context(device, client);
		अगर (ret) अणु
			up_पढ़ो(&devices_rwsem);
			ib_unरेजिस्टर_client(client);
			वापस ret;
		पूर्ण
	पूर्ण
	up_पढ़ो(&devices_rwsem);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(ib_रेजिस्टर_client);

/**
 * ib_unरेजिस्टर_client - Unरेजिस्टर an IB client
 * @client:Client to unरेजिस्टर
 *
 * Upper level users use ib_unरेजिस्टर_client() to हटाओ their client
 * registration.  When ib_unरेजिस्टर_client() is called, the client
 * will receive a हटाओ callback क्रम each IB device still रेजिस्टरed.
 *
 * This is a full fence, once it वापसs no client callbacks will be called,
 * or are running in another thपढ़ो.
 */
व्योम ib_unरेजिस्टर_client(काष्ठा ib_client *client)
अणु
	काष्ठा ib_device *device;
	अचिन्हित दीर्घ index;

	करोwn_ग_लिखो(&clients_rwsem);
	ib_client_put(client);
	xa_clear_mark(&clients, client->client_id, CLIENT_REGISTERED);
	up_ग_लिखो(&clients_rwsem);

	/* We करो not want to have locks जबतक calling client->हटाओ() */
	rcu_पढ़ो_lock();
	xa_क्रम_each (&devices, index, device) अणु
		अगर (!ib_device_try_get(device))
			जारी;
		rcu_पढ़ो_unlock();

		हटाओ_client_context(device, client->client_id);

		ib_device_put(device);
		rcu_पढ़ो_lock();
	पूर्ण
	rcu_पढ़ो_unlock();

	/*
	 * हटाओ_client_context() is not a fence, it can वापस even though a
	 * removal is ongoing. Wait until all removals are completed.
	 */
	रुको_क्रम_completion(&client->uses_zero);
	हटाओ_client_id(client);
पूर्ण
EXPORT_SYMBOL(ib_unरेजिस्टर_client);

अटल पूर्णांक __ib_get_global_client_nl_info(स्थिर अक्षर *client_name,
					  काष्ठा ib_client_nl_info *res)
अणु
	काष्ठा ib_client *client;
	अचिन्हित दीर्घ index;
	पूर्णांक ret = -ENOENT;

	करोwn_पढ़ो(&clients_rwsem);
	xa_क्रम_each_marked (&clients, index, client, CLIENT_REGISTERED) अणु
		अगर (म_भेद(client->name, client_name) != 0)
			जारी;
		अगर (!client->get_global_nl_info) अणु
			ret = -EOPNOTSUPP;
			अवरोध;
		पूर्ण
		ret = client->get_global_nl_info(res);
		अगर (WARN_ON(ret == -ENOENT))
			ret = -EINVAL;
		अगर (!ret && res->cdev)
			get_device(res->cdev);
		अवरोध;
	पूर्ण
	up_पढ़ो(&clients_rwsem);
	वापस ret;
पूर्ण

अटल पूर्णांक __ib_get_client_nl_info(काष्ठा ib_device *ibdev,
				   स्थिर अक्षर *client_name,
				   काष्ठा ib_client_nl_info *res)
अणु
	अचिन्हित दीर्घ index;
	व्योम *client_data;
	पूर्णांक ret = -ENOENT;

	करोwn_पढ़ो(&ibdev->client_data_rwsem);
	xan_क्रम_each_marked (&ibdev->client_data, index, client_data,
			     CLIENT_DATA_REGISTERED) अणु
		काष्ठा ib_client *client = xa_load(&clients, index);

		अगर (!client || म_भेद(client->name, client_name) != 0)
			जारी;
		अगर (!client->get_nl_info) अणु
			ret = -EOPNOTSUPP;
			अवरोध;
		पूर्ण
		ret = client->get_nl_info(ibdev, client_data, res);
		अगर (WARN_ON(ret == -ENOENT))
			ret = -EINVAL;

		/*
		 * The cdev is guaranteed valid as दीर्घ as we are inside the
		 * client_data_rwsem as हटाओ_one can't be called. Keep it
		 * valid क्रम the caller.
		 */
		अगर (!ret && res->cdev)
			get_device(res->cdev);
		अवरोध;
	पूर्ण
	up_पढ़ो(&ibdev->client_data_rwsem);

	वापस ret;
पूर्ण

/**
 * ib_get_client_nl_info - Fetch the nl_info from a client
 * @ibdev: IB device
 * @client_name: Name of the client
 * @res: Result of the query
 */
पूर्णांक ib_get_client_nl_info(काष्ठा ib_device *ibdev, स्थिर अक्षर *client_name,
			  काष्ठा ib_client_nl_info *res)
अणु
	पूर्णांक ret;

	अगर (ibdev)
		ret = __ib_get_client_nl_info(ibdev, client_name, res);
	अन्यथा
		ret = __ib_get_global_client_nl_info(client_name, res);
#अगर_घोषित CONFIG_MODULES
	अगर (ret == -ENOENT) अणु
		request_module("rdma-client-%s", client_name);
		अगर (ibdev)
			ret = __ib_get_client_nl_info(ibdev, client_name, res);
		अन्यथा
			ret = __ib_get_global_client_nl_info(client_name, res);
	पूर्ण
#पूर्ण_अगर
	अगर (ret) अणु
		अगर (ret == -ENOENT)
			वापस -EOPNOTSUPP;
		वापस ret;
	पूर्ण

	अगर (WARN_ON(!res->cdev))
		वापस -EINVAL;
	वापस 0;
पूर्ण

/**
 * ib_set_client_data - Set IB client context
 * @device:Device to set context क्रम
 * @client:Client to set context क्रम
 * @data:Context to set
 *
 * ib_set_client_data() sets client context data that can be retrieved with
 * ib_get_client_data(). This can only be called जबतक the client is
 * रेजिस्टरed to the device, once the ib_client हटाओ() callback वापसs this
 * cannot be called.
 */
व्योम ib_set_client_data(काष्ठा ib_device *device, काष्ठा ib_client *client,
			व्योम *data)
अणु
	व्योम *rc;

	अगर (WARN_ON(IS_ERR(data)))
		data = शून्य;

	rc = xa_store(&device->client_data, client->client_id, data,
		      GFP_KERNEL);
	WARN_ON(xa_is_err(rc));
पूर्ण
EXPORT_SYMBOL(ib_set_client_data);

/**
 * ib_रेजिस्टर_event_handler - Register an IB event handler
 * @event_handler:Handler to रेजिस्टर
 *
 * ib_रेजिस्टर_event_handler() रेजिस्टरs an event handler that will be
 * called back when asynchronous IB events occur (as defined in
 * chapter 11 of the InfiniBand Architecture Specअगरication). This
 * callback occurs in workqueue context.
 */
व्योम ib_रेजिस्टर_event_handler(काष्ठा ib_event_handler *event_handler)
अणु
	करोwn_ग_लिखो(&event_handler->device->event_handler_rwsem);
	list_add_tail(&event_handler->list,
		      &event_handler->device->event_handler_list);
	up_ग_लिखो(&event_handler->device->event_handler_rwsem);
पूर्ण
EXPORT_SYMBOL(ib_रेजिस्टर_event_handler);

/**
 * ib_unरेजिस्टर_event_handler - Unरेजिस्टर an event handler
 * @event_handler:Handler to unरेजिस्टर
 *
 * Unरेजिस्टर an event handler रेजिस्टरed with
 * ib_रेजिस्टर_event_handler().
 */
व्योम ib_unरेजिस्टर_event_handler(काष्ठा ib_event_handler *event_handler)
अणु
	करोwn_ग_लिखो(&event_handler->device->event_handler_rwsem);
	list_del(&event_handler->list);
	up_ग_लिखो(&event_handler->device->event_handler_rwsem);
पूर्ण
EXPORT_SYMBOL(ib_unरेजिस्टर_event_handler);

व्योम ib_dispatch_event_clients(काष्ठा ib_event *event)
अणु
	काष्ठा ib_event_handler *handler;

	करोwn_पढ़ो(&event->device->event_handler_rwsem);

	list_क्रम_each_entry(handler, &event->device->event_handler_list, list)
		handler->handler(handler, event);

	up_पढ़ो(&event->device->event_handler_rwsem);
पूर्ण

अटल पूर्णांक iw_query_port(काष्ठा ib_device *device,
			   u32 port_num,
			   काष्ठा ib_port_attr *port_attr)
अणु
	काष्ठा in_device *inetdev;
	काष्ठा net_device *netdev;

	स_रखो(port_attr, 0, माप(*port_attr));

	netdev = ib_device_get_netdev(device, port_num);
	अगर (!netdev)
		वापस -ENODEV;

	port_attr->max_mtu = IB_MTU_4096;
	port_attr->active_mtu = ib_mtu_पूर्णांक_to_क्रमागत(netdev->mtu);

	अगर (!netअगर_carrier_ok(netdev)) अणु
		port_attr->state = IB_PORT_DOWN;
		port_attr->phys_state = IB_PORT_PHYS_STATE_DISABLED;
	पूर्ण अन्यथा अणु
		rcu_पढ़ो_lock();
		inetdev = __in_dev_get_rcu(netdev);

		अगर (inetdev && inetdev->अगरa_list) अणु
			port_attr->state = IB_PORT_ACTIVE;
			port_attr->phys_state = IB_PORT_PHYS_STATE_LINK_UP;
		पूर्ण अन्यथा अणु
			port_attr->state = IB_PORT_INIT;
			port_attr->phys_state =
				IB_PORT_PHYS_STATE_PORT_CONFIGURATION_TRAINING;
		पूर्ण

		rcu_पढ़ो_unlock();
	पूर्ण

	dev_put(netdev);
	वापस device->ops.query_port(device, port_num, port_attr);
पूर्ण

अटल पूर्णांक __ib_query_port(काष्ठा ib_device *device,
			   u32 port_num,
			   काष्ठा ib_port_attr *port_attr)
अणु
	जोड़ ib_gid gid = अणुपूर्ण;
	पूर्णांक err;

	स_रखो(port_attr, 0, माप(*port_attr));

	err = device->ops.query_port(device, port_num, port_attr);
	अगर (err || port_attr->subnet_prefix)
		वापस err;

	अगर (rdma_port_get_link_layer(device, port_num) !=
	    IB_LINK_LAYER_INFINIBAND)
		वापस 0;

	err = device->ops.query_gid(device, port_num, 0, &gid);
	अगर (err)
		वापस err;

	port_attr->subnet_prefix = be64_to_cpu(gid.global.subnet_prefix);
	वापस 0;
पूर्ण

/**
 * ib_query_port - Query IB port attributes
 * @device:Device to query
 * @port_num:Port number to query
 * @port_attr:Port attributes
 *
 * ib_query_port() वापसs the attributes of a port through the
 * @port_attr poपूर्णांकer.
 */
पूर्णांक ib_query_port(काष्ठा ib_device *device,
		  u32 port_num,
		  काष्ठा ib_port_attr *port_attr)
अणु
	अगर (!rdma_is_port_valid(device, port_num))
		वापस -EINVAL;

	अगर (rdma_protocol_iwarp(device, port_num))
		वापस iw_query_port(device, port_num, port_attr);
	अन्यथा
		वापस __ib_query_port(device, port_num, port_attr);
पूर्ण
EXPORT_SYMBOL(ib_query_port);

अटल व्योम add_ndev_hash(काष्ठा ib_port_data *pdata)
अणु
	अचिन्हित दीर्घ flags;

	might_sleep();

	spin_lock_irqsave(&ndev_hash_lock, flags);
	अगर (hash_hashed(&pdata->ndev_hash_link)) अणु
		hash_del_rcu(&pdata->ndev_hash_link);
		spin_unlock_irqrestore(&ndev_hash_lock, flags);
		/*
		 * We cannot करो hash_add_rcu after a hash_del_rcu until the
		 * grace period
		 */
		synchronize_rcu();
		spin_lock_irqsave(&ndev_hash_lock, flags);
	पूर्ण
	अगर (pdata->netdev)
		hash_add_rcu(ndev_hash, &pdata->ndev_hash_link,
			     (uपूर्णांकptr_t)pdata->netdev);
	spin_unlock_irqrestore(&ndev_hash_lock, flags);
पूर्ण

/**
 * ib_device_set_netdev - Associate the ib_dev with an underlying net_device
 * @ib_dev: Device to modअगरy
 * @ndev: net_device to affiliate, may be शून्य
 * @port: IB port the net_device is connected to
 *
 * Drivers should use this to link the ib_device to a netdev so the netdev
 * shows up in पूर्णांकerfaces like ib_क्रमागत_roce_netdev. Only one netdev may be
 * affiliated with any port.
 *
 * The caller must ensure that the given ndev is not unरेजिस्टरed or
 * unरेजिस्टरing, and that either the ib_device is unरेजिस्टरed or
 * ib_device_set_netdev() is called with शून्य when the ndev sends a
 * NETDEV_UNREGISTER event.
 */
पूर्णांक ib_device_set_netdev(काष्ठा ib_device *ib_dev, काष्ठा net_device *ndev,
			 u32 port)
अणु
	काष्ठा net_device *old_ndev;
	काष्ठा ib_port_data *pdata;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	/*
	 * Drivers wish to call this beक्रमe ib_रेजिस्टर_driver, so we have to
	 * setup the port data early.
	 */
	ret = alloc_port_data(ib_dev);
	अगर (ret)
		वापस ret;

	अगर (!rdma_is_port_valid(ib_dev, port))
		वापस -EINVAL;

	pdata = &ib_dev->port_data[port];
	spin_lock_irqsave(&pdata->netdev_lock, flags);
	old_ndev = rcu_dereference_रक्षित(
		pdata->netdev, lockdep_is_held(&pdata->netdev_lock));
	अगर (old_ndev == ndev) अणु
		spin_unlock_irqrestore(&pdata->netdev_lock, flags);
		वापस 0;
	पूर्ण

	अगर (ndev)
		dev_hold(ndev);
	rcu_assign_poपूर्णांकer(pdata->netdev, ndev);
	spin_unlock_irqrestore(&pdata->netdev_lock, flags);

	add_ndev_hash(pdata);
	अगर (old_ndev)
		dev_put(old_ndev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ib_device_set_netdev);

अटल व्योम मुक्त_netdevs(काष्ठा ib_device *ib_dev)
अणु
	अचिन्हित दीर्घ flags;
	u32 port;

	अगर (!ib_dev->port_data)
		वापस;

	rdma_क्रम_each_port (ib_dev, port) अणु
		काष्ठा ib_port_data *pdata = &ib_dev->port_data[port];
		काष्ठा net_device *ndev;

		spin_lock_irqsave(&pdata->netdev_lock, flags);
		ndev = rcu_dereference_रक्षित(
			pdata->netdev, lockdep_is_held(&pdata->netdev_lock));
		अगर (ndev) अणु
			spin_lock(&ndev_hash_lock);
			hash_del_rcu(&pdata->ndev_hash_link);
			spin_unlock(&ndev_hash_lock);

			/*
			 * If this is the last dev_put there is still a
			 * synchronize_rcu beक्रमe the netdev is kमुक्तd, so we
			 * can जारी to rely on unlocked poपूर्णांकer
			 * comparisons after the put
			 */
			rcu_assign_poपूर्णांकer(pdata->netdev, शून्य);
			dev_put(ndev);
		पूर्ण
		spin_unlock_irqrestore(&pdata->netdev_lock, flags);
	पूर्ण
पूर्ण

काष्ठा net_device *ib_device_get_netdev(काष्ठा ib_device *ib_dev,
					u32 port)
अणु
	काष्ठा ib_port_data *pdata;
	काष्ठा net_device *res;

	अगर (!rdma_is_port_valid(ib_dev, port))
		वापस शून्य;

	pdata = &ib_dev->port_data[port];

	/*
	 * New drivers should use ib_device_set_netdev() not the legacy
	 * get_netdev().
	 */
	अगर (ib_dev->ops.get_netdev)
		res = ib_dev->ops.get_netdev(ib_dev, port);
	अन्यथा अणु
		spin_lock(&pdata->netdev_lock);
		res = rcu_dereference_रक्षित(
			pdata->netdev, lockdep_is_held(&pdata->netdev_lock));
		अगर (res)
			dev_hold(res);
		spin_unlock(&pdata->netdev_lock);
	पूर्ण

	/*
	 * If we are starting to unरेजिस्टर expedite things by preventing
	 * propagation of an unरेजिस्टरing netdev.
	 */
	अगर (res && res->reg_state != NETREG_REGISTERED) अणु
		dev_put(res);
		वापस शून्य;
	पूर्ण

	वापस res;
पूर्ण

/**
 * ib_device_get_by_netdev - Find an IB device associated with a netdev
 * @ndev: netdev to locate
 * @driver_id: The driver ID that must match (RDMA_DRIVER_UNKNOWN matches all)
 *
 * Find and hold an ib_device that is associated with a netdev via
 * ib_device_set_netdev(). The caller must call ib_device_put() on the
 * वापसed poपूर्णांकer.
 */
काष्ठा ib_device *ib_device_get_by_netdev(काष्ठा net_device *ndev,
					  क्रमागत rdma_driver_id driver_id)
अणु
	काष्ठा ib_device *res = शून्य;
	काष्ठा ib_port_data *cur;

	rcu_पढ़ो_lock();
	hash_क्रम_each_possible_rcu (ndev_hash, cur, ndev_hash_link,
				    (uपूर्णांकptr_t)ndev) अणु
		अगर (rcu_access_poपूर्णांकer(cur->netdev) == ndev &&
		    (driver_id == RDMA_DRIVER_UNKNOWN ||
		     cur->ib_dev->ops.driver_id == driver_id) &&
		    ib_device_try_get(cur->ib_dev)) अणु
			res = cur->ib_dev;
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस res;
पूर्ण
EXPORT_SYMBOL(ib_device_get_by_netdev);

/**
 * ib_क्रमागत_roce_netdev - क्रमागतerate all RoCE ports
 * @ib_dev : IB device we want to query
 * @filter: Should we call the callback?
 * @filter_cookie: Cookie passed to filter
 * @cb: Callback to call क्रम each found RoCE ports
 * @cookie: Cookie passed back to the callback
 *
 * Enumerates all of the physical RoCE ports of ib_dev
 * which are related to netdevice and calls callback() on each
 * device क्रम which filter() function वापसs non zero.
 */
व्योम ib_क्रमागत_roce_netdev(काष्ठा ib_device *ib_dev,
			 roce_netdev_filter filter,
			 व्योम *filter_cookie,
			 roce_netdev_callback cb,
			 व्योम *cookie)
अणु
	u32 port;

	rdma_क्रम_each_port (ib_dev, port)
		अगर (rdma_protocol_roce(ib_dev, port)) अणु
			काष्ठा net_device *idev =
				ib_device_get_netdev(ib_dev, port);

			अगर (filter(ib_dev, port, idev, filter_cookie))
				cb(ib_dev, port, idev, cookie);

			अगर (idev)
				dev_put(idev);
		पूर्ण
पूर्ण

/**
 * ib_क्रमागत_all_roce_netdevs - क्रमागतerate all RoCE devices
 * @filter: Should we call the callback?
 * @filter_cookie: Cookie passed to filter
 * @cb: Callback to call क्रम each found RoCE ports
 * @cookie: Cookie passed back to the callback
 *
 * Enumerates all RoCE devices' physical ports which are related
 * to netdevices and calls callback() on each device क्रम which
 * filter() function वापसs non zero.
 */
व्योम ib_क्रमागत_all_roce_netdevs(roce_netdev_filter filter,
			      व्योम *filter_cookie,
			      roce_netdev_callback cb,
			      व्योम *cookie)
अणु
	काष्ठा ib_device *dev;
	अचिन्हित दीर्घ index;

	करोwn_पढ़ो(&devices_rwsem);
	xa_क्रम_each_marked (&devices, index, dev, DEVICE_REGISTERED)
		ib_क्रमागत_roce_netdev(dev, filter, filter_cookie, cb, cookie);
	up_पढ़ो(&devices_rwsem);
पूर्ण

/*
 * ib_क्रमागत_all_devs - क्रमागतerate all ib_devices
 * @cb: Callback to call क्रम each found ib_device
 *
 * Enumerates all ib_devices and calls callback() on each device.
 */
पूर्णांक ib_क्रमागत_all_devs(nldev_callback nldev_cb, काष्ठा sk_buff *skb,
		     काष्ठा netlink_callback *cb)
अणु
	अचिन्हित दीर्घ index;
	काष्ठा ib_device *dev;
	अचिन्हित पूर्णांक idx = 0;
	पूर्णांक ret = 0;

	करोwn_पढ़ो(&devices_rwsem);
	xa_क्रम_each_marked (&devices, index, dev, DEVICE_REGISTERED) अणु
		अगर (!rdma_dev_access_netns(dev, sock_net(skb->sk)))
			जारी;

		ret = nldev_cb(dev, skb, cb, idx);
		अगर (ret)
			अवरोध;
		idx++;
	पूर्ण
	up_पढ़ो(&devices_rwsem);
	वापस ret;
पूर्ण

/**
 * ib_query_pkey - Get P_Key table entry
 * @device:Device to query
 * @port_num:Port number to query
 * @index:P_Key table index to query
 * @pkey:Returned P_Key
 *
 * ib_query_pkey() fetches the specअगरied P_Key table entry.
 */
पूर्णांक ib_query_pkey(काष्ठा ib_device *device,
		  u32 port_num, u16 index, u16 *pkey)
अणु
	अगर (!rdma_is_port_valid(device, port_num))
		वापस -EINVAL;

	अगर (!device->ops.query_pkey)
		वापस -EOPNOTSUPP;

	वापस device->ops.query_pkey(device, port_num, index, pkey);
पूर्ण
EXPORT_SYMBOL(ib_query_pkey);

/**
 * ib_modअगरy_device - Change IB device attributes
 * @device:Device to modअगरy
 * @device_modअगरy_mask:Mask of attributes to change
 * @device_modअगरy:New attribute values
 *
 * ib_modअगरy_device() changes a device's attributes as specअगरied by
 * the @device_modअगरy_mask and @device_modअगरy काष्ठाure.
 */
पूर्णांक ib_modअगरy_device(काष्ठा ib_device *device,
		     पूर्णांक device_modअगरy_mask,
		     काष्ठा ib_device_modअगरy *device_modअगरy)
अणु
	अगर (!device->ops.modअगरy_device)
		वापस -EOPNOTSUPP;

	वापस device->ops.modअगरy_device(device, device_modअगरy_mask,
					 device_modअगरy);
पूर्ण
EXPORT_SYMBOL(ib_modअगरy_device);

/**
 * ib_modअगरy_port - Modअगरies the attributes क्रम the specअगरied port.
 * @device: The device to modअगरy.
 * @port_num: The number of the port to modअगरy.
 * @port_modअगरy_mask: Mask used to specअगरy which attributes of the port
 *   to change.
 * @port_modअगरy: New attribute values क्रम the port.
 *
 * ib_modअगरy_port() changes a port's attributes as specअगरied by the
 * @port_modअगरy_mask and @port_modअगरy काष्ठाure.
 */
पूर्णांक ib_modअगरy_port(काष्ठा ib_device *device,
		   u32 port_num, पूर्णांक port_modअगरy_mask,
		   काष्ठा ib_port_modअगरy *port_modअगरy)
अणु
	पूर्णांक rc;

	अगर (!rdma_is_port_valid(device, port_num))
		वापस -EINVAL;

	अगर (device->ops.modअगरy_port)
		rc = device->ops.modअगरy_port(device, port_num,
					     port_modअगरy_mask,
					     port_modअगरy);
	अन्यथा अगर (rdma_protocol_roce(device, port_num) &&
		 ((port_modअगरy->set_port_cap_mask & ~IB_PORT_CM_SUP) == 0 ||
		  (port_modअगरy->clr_port_cap_mask & ~IB_PORT_CM_SUP) == 0))
		rc = 0;
	अन्यथा
		rc = -EOPNOTSUPP;
	वापस rc;
पूर्ण
EXPORT_SYMBOL(ib_modअगरy_port);

/**
 * ib_find_gid - Returns the port number and GID table index where
 *   a specअगरied GID value occurs. Its searches only क्रम IB link layer.
 * @device: The device to query.
 * @gid: The GID value to search क्रम.
 * @port_num: The port number of the device where the GID value was found.
 * @index: The index पूर्णांकo the GID table where the GID was found.  This
 *   parameter may be शून्य.
 */
पूर्णांक ib_find_gid(काष्ठा ib_device *device, जोड़ ib_gid *gid,
		u32 *port_num, u16 *index)
अणु
	जोड़ ib_gid पंचांगp_gid;
	u32 port;
	पूर्णांक ret, i;

	rdma_क्रम_each_port (device, port) अणु
		अगर (!rdma_protocol_ib(device, port))
			जारी;

		क्रम (i = 0; i < device->port_data[port].immutable.gid_tbl_len;
		     ++i) अणु
			ret = rdma_query_gid(device, port, i, &पंचांगp_gid);
			अगर (ret)
				वापस ret;
			अगर (!स_भेद(&पंचांगp_gid, gid, माप *gid)) अणु
				*port_num = port;
				अगर (index)
					*index = i;
				वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस -ENOENT;
पूर्ण
EXPORT_SYMBOL(ib_find_gid);

/**
 * ib_find_pkey - Returns the PKey table index where a specअगरied
 *   PKey value occurs.
 * @device: The device to query.
 * @port_num: The port number of the device to search क्रम the PKey.
 * @pkey: The PKey value to search क्रम.
 * @index: The index पूर्णांकo the PKey table where the PKey was found.
 */
पूर्णांक ib_find_pkey(काष्ठा ib_device *device,
		 u32 port_num, u16 pkey, u16 *index)
अणु
	पूर्णांक ret, i;
	u16 पंचांगp_pkey;
	पूर्णांक partial_ix = -1;

	क्रम (i = 0; i < device->port_data[port_num].immutable.pkey_tbl_len;
	     ++i) अणु
		ret = ib_query_pkey(device, port_num, i, &पंचांगp_pkey);
		अगर (ret)
			वापस ret;
		अगर ((pkey & 0x7fff) == (पंचांगp_pkey & 0x7fff)) अणु
			/* अगर there is full-member pkey take it.*/
			अगर (पंचांगp_pkey & 0x8000) अणु
				*index = i;
				वापस 0;
			पूर्ण
			अगर (partial_ix < 0)
				partial_ix = i;
		पूर्ण
	पूर्ण

	/*no full-member, अगर exists take the limited*/
	अगर (partial_ix >= 0) अणु
		*index = partial_ix;
		वापस 0;
	पूर्ण
	वापस -ENOENT;
पूर्ण
EXPORT_SYMBOL(ib_find_pkey);

/**
 * ib_get_net_dev_by_params() - Return the appropriate net_dev
 * क्रम a received CM request
 * @dev:	An RDMA device on which the request has been received.
 * @port:	Port number on the RDMA device.
 * @pkey:	The Pkey the request came on.
 * @gid:	A GID that the net_dev uses to communicate.
 * @addr:	Contains the IP address that the request specअगरied as its
 *		destination.
 *
 */
काष्ठा net_device *ib_get_net_dev_by_params(काष्ठा ib_device *dev,
					    u32 port,
					    u16 pkey,
					    स्थिर जोड़ ib_gid *gid,
					    स्थिर काष्ठा sockaddr *addr)
अणु
	काष्ठा net_device *net_dev = शून्य;
	अचिन्हित दीर्घ index;
	व्योम *client_data;

	अगर (!rdma_protocol_ib(dev, port))
		वापस शून्य;

	/*
	 * Holding the पढ़ो side guarantees that the client will not become
	 * unरेजिस्टरed जबतक we are calling get_net_dev_by_params()
	 */
	करोwn_पढ़ो(&dev->client_data_rwsem);
	xan_क्रम_each_marked (&dev->client_data, index, client_data,
			     CLIENT_DATA_REGISTERED) अणु
		काष्ठा ib_client *client = xa_load(&clients, index);

		अगर (!client || !client->get_net_dev_by_params)
			जारी;

		net_dev = client->get_net_dev_by_params(dev, port, pkey, gid,
							addr, client_data);
		अगर (net_dev)
			अवरोध;
	पूर्ण
	up_पढ़ो(&dev->client_data_rwsem);

	वापस net_dev;
पूर्ण
EXPORT_SYMBOL(ib_get_net_dev_by_params);

व्योम ib_set_device_ops(काष्ठा ib_device *dev, स्थिर काष्ठा ib_device_ops *ops)
अणु
	काष्ठा ib_device_ops *dev_ops = &dev->ops;
#घोषणा SET_DEVICE_OP(ptr, name)                                               \
	करो अणु                                                                   \
		अगर (ops->name)                                                 \
			अगर (!((ptr)->name))				       \
				(ptr)->name = ops->name;                       \
	पूर्ण जबतक (0)

#घोषणा SET_OBJ_SIZE(ptr, name) SET_DEVICE_OP(ptr, size_##name)

	अगर (ops->driver_id != RDMA_DRIVER_UNKNOWN) अणु
		WARN_ON(dev_ops->driver_id != RDMA_DRIVER_UNKNOWN &&
			dev_ops->driver_id != ops->driver_id);
		dev_ops->driver_id = ops->driver_id;
	पूर्ण
	अगर (ops->owner) अणु
		WARN_ON(dev_ops->owner && dev_ops->owner != ops->owner);
		dev_ops->owner = ops->owner;
	पूर्ण
	अगर (ops->uverbs_abi_ver)
		dev_ops->uverbs_abi_ver = ops->uverbs_abi_ver;

	dev_ops->uverbs_no_driver_id_binding |=
		ops->uverbs_no_driver_id_binding;

	SET_DEVICE_OP(dev_ops, add_gid);
	SET_DEVICE_OP(dev_ops, advise_mr);
	SET_DEVICE_OP(dev_ops, alloc_dm);
	SET_DEVICE_OP(dev_ops, alloc_hw_stats);
	SET_DEVICE_OP(dev_ops, alloc_mr);
	SET_DEVICE_OP(dev_ops, alloc_mr_पूर्णांकegrity);
	SET_DEVICE_OP(dev_ops, alloc_mw);
	SET_DEVICE_OP(dev_ops, alloc_pd);
	SET_DEVICE_OP(dev_ops, alloc_rdma_netdev);
	SET_DEVICE_OP(dev_ops, alloc_ucontext);
	SET_DEVICE_OP(dev_ops, alloc_xrcd);
	SET_DEVICE_OP(dev_ops, attach_mcast);
	SET_DEVICE_OP(dev_ops, check_mr_status);
	SET_DEVICE_OP(dev_ops, counter_alloc_stats);
	SET_DEVICE_OP(dev_ops, counter_bind_qp);
	SET_DEVICE_OP(dev_ops, counter_dealloc);
	SET_DEVICE_OP(dev_ops, counter_unbind_qp);
	SET_DEVICE_OP(dev_ops, counter_update_stats);
	SET_DEVICE_OP(dev_ops, create_ah);
	SET_DEVICE_OP(dev_ops, create_counters);
	SET_DEVICE_OP(dev_ops, create_cq);
	SET_DEVICE_OP(dev_ops, create_flow);
	SET_DEVICE_OP(dev_ops, create_flow_action_esp);
	SET_DEVICE_OP(dev_ops, create_qp);
	SET_DEVICE_OP(dev_ops, create_rwq_ind_table);
	SET_DEVICE_OP(dev_ops, create_srq);
	SET_DEVICE_OP(dev_ops, create_user_ah);
	SET_DEVICE_OP(dev_ops, create_wq);
	SET_DEVICE_OP(dev_ops, dealloc_dm);
	SET_DEVICE_OP(dev_ops, dealloc_driver);
	SET_DEVICE_OP(dev_ops, dealloc_mw);
	SET_DEVICE_OP(dev_ops, dealloc_pd);
	SET_DEVICE_OP(dev_ops, dealloc_ucontext);
	SET_DEVICE_OP(dev_ops, dealloc_xrcd);
	SET_DEVICE_OP(dev_ops, del_gid);
	SET_DEVICE_OP(dev_ops, dereg_mr);
	SET_DEVICE_OP(dev_ops, destroy_ah);
	SET_DEVICE_OP(dev_ops, destroy_counters);
	SET_DEVICE_OP(dev_ops, destroy_cq);
	SET_DEVICE_OP(dev_ops, destroy_flow);
	SET_DEVICE_OP(dev_ops, destroy_flow_action);
	SET_DEVICE_OP(dev_ops, destroy_qp);
	SET_DEVICE_OP(dev_ops, destroy_rwq_ind_table);
	SET_DEVICE_OP(dev_ops, destroy_srq);
	SET_DEVICE_OP(dev_ops, destroy_wq);
	SET_DEVICE_OP(dev_ops, detach_mcast);
	SET_DEVICE_OP(dev_ops, disassociate_ucontext);
	SET_DEVICE_OP(dev_ops, drain_rq);
	SET_DEVICE_OP(dev_ops, drain_sq);
	SET_DEVICE_OP(dev_ops, enable_driver);
	SET_DEVICE_OP(dev_ops, fill_res_cm_id_entry);
	SET_DEVICE_OP(dev_ops, fill_res_cq_entry);
	SET_DEVICE_OP(dev_ops, fill_res_cq_entry_raw);
	SET_DEVICE_OP(dev_ops, fill_res_mr_entry);
	SET_DEVICE_OP(dev_ops, fill_res_mr_entry_raw);
	SET_DEVICE_OP(dev_ops, fill_res_qp_entry);
	SET_DEVICE_OP(dev_ops, fill_res_qp_entry_raw);
	SET_DEVICE_OP(dev_ops, fill_stat_mr_entry);
	SET_DEVICE_OP(dev_ops, get_dev_fw_str);
	SET_DEVICE_OP(dev_ops, get_dma_mr);
	SET_DEVICE_OP(dev_ops, get_hw_stats);
	SET_DEVICE_OP(dev_ops, get_link_layer);
	SET_DEVICE_OP(dev_ops, get_netdev);
	SET_DEVICE_OP(dev_ops, get_port_immutable);
	SET_DEVICE_OP(dev_ops, get_vector_affinity);
	SET_DEVICE_OP(dev_ops, get_vf_config);
	SET_DEVICE_OP(dev_ops, get_vf_guid);
	SET_DEVICE_OP(dev_ops, get_vf_stats);
	SET_DEVICE_OP(dev_ops, init_port);
	SET_DEVICE_OP(dev_ops, iw_accept);
	SET_DEVICE_OP(dev_ops, iw_add_ref);
	SET_DEVICE_OP(dev_ops, iw_connect);
	SET_DEVICE_OP(dev_ops, iw_create_listen);
	SET_DEVICE_OP(dev_ops, iw_destroy_listen);
	SET_DEVICE_OP(dev_ops, iw_get_qp);
	SET_DEVICE_OP(dev_ops, iw_reject);
	SET_DEVICE_OP(dev_ops, iw_rem_ref);
	SET_DEVICE_OP(dev_ops, map_mr_sg);
	SET_DEVICE_OP(dev_ops, map_mr_sg_pi);
	SET_DEVICE_OP(dev_ops, mmap);
	SET_DEVICE_OP(dev_ops, mmap_मुक्त);
	SET_DEVICE_OP(dev_ops, modअगरy_ah);
	SET_DEVICE_OP(dev_ops, modअगरy_cq);
	SET_DEVICE_OP(dev_ops, modअगरy_device);
	SET_DEVICE_OP(dev_ops, modअगरy_flow_action_esp);
	SET_DEVICE_OP(dev_ops, modअगरy_port);
	SET_DEVICE_OP(dev_ops, modअगरy_qp);
	SET_DEVICE_OP(dev_ops, modअगरy_srq);
	SET_DEVICE_OP(dev_ops, modअगरy_wq);
	SET_DEVICE_OP(dev_ops, peek_cq);
	SET_DEVICE_OP(dev_ops, poll_cq);
	SET_DEVICE_OP(dev_ops, post_recv);
	SET_DEVICE_OP(dev_ops, post_send);
	SET_DEVICE_OP(dev_ops, post_srq_recv);
	SET_DEVICE_OP(dev_ops, process_mad);
	SET_DEVICE_OP(dev_ops, query_ah);
	SET_DEVICE_OP(dev_ops, query_device);
	SET_DEVICE_OP(dev_ops, query_gid);
	SET_DEVICE_OP(dev_ops, query_pkey);
	SET_DEVICE_OP(dev_ops, query_port);
	SET_DEVICE_OP(dev_ops, query_qp);
	SET_DEVICE_OP(dev_ops, query_srq);
	SET_DEVICE_OP(dev_ops, query_ucontext);
	SET_DEVICE_OP(dev_ops, rdma_netdev_get_params);
	SET_DEVICE_OP(dev_ops, पढ़ो_counters);
	SET_DEVICE_OP(dev_ops, reg_dm_mr);
	SET_DEVICE_OP(dev_ops, reg_user_mr);
	SET_DEVICE_OP(dev_ops, reg_user_mr_dmabuf);
	SET_DEVICE_OP(dev_ops, req_notअगरy_cq);
	SET_DEVICE_OP(dev_ops, rereg_user_mr);
	SET_DEVICE_OP(dev_ops, resize_cq);
	SET_DEVICE_OP(dev_ops, set_vf_guid);
	SET_DEVICE_OP(dev_ops, set_vf_link_state);

	SET_OBJ_SIZE(dev_ops, ib_ah);
	SET_OBJ_SIZE(dev_ops, ib_counters);
	SET_OBJ_SIZE(dev_ops, ib_cq);
	SET_OBJ_SIZE(dev_ops, ib_mw);
	SET_OBJ_SIZE(dev_ops, ib_pd);
	SET_OBJ_SIZE(dev_ops, ib_rwq_ind_table);
	SET_OBJ_SIZE(dev_ops, ib_srq);
	SET_OBJ_SIZE(dev_ops, ib_ucontext);
	SET_OBJ_SIZE(dev_ops, ib_xrcd);
पूर्ण
EXPORT_SYMBOL(ib_set_device_ops);

#अगर_घोषित CONFIG_INFINIBAND_VIRT_DMA
पूर्णांक ib_dma_virt_map_sg(काष्ठा ib_device *dev, काष्ठा scatterlist *sg, पूर्णांक nents)
अणु
	काष्ठा scatterlist *s;
	पूर्णांक i;

	क्रम_each_sg(sg, s, nents, i) अणु
		sg_dma_address(s) = (uपूर्णांकptr_t)sg_virt(s);
		sg_dma_len(s) = s->length;
	पूर्ण
	वापस nents;
पूर्ण
EXPORT_SYMBOL(ib_dma_virt_map_sg);
#पूर्ण_अगर /* CONFIG_INFINIBAND_VIRT_DMA */

अटल स्थिर काष्ठा rdma_nl_cbs ibnl_ls_cb_table[RDMA_NL_LS_NUM_OPS] = अणु
	[RDMA_NL_LS_OP_RESOLVE] = अणु
		.करोit = ib_nl_handle_resolve_resp,
		.flags = RDMA_NL_ADMIN_PERM,
	पूर्ण,
	[RDMA_NL_LS_OP_SET_TIMEOUT] = अणु
		.करोit = ib_nl_handle_set_समयout,
		.flags = RDMA_NL_ADMIN_PERM,
	पूर्ण,
	[RDMA_NL_LS_OP_IP_RESOLVE] = अणु
		.करोit = ib_nl_handle_ip_res_resp,
		.flags = RDMA_NL_ADMIN_PERM,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init ib_core_init(व्योम)
अणु
	पूर्णांक ret;

	ib_wq = alloc_workqueue("infiniband", 0, 0);
	अगर (!ib_wq)
		वापस -ENOMEM;

	ib_comp_wq = alloc_workqueue("ib-comp-wq",
			WQ_HIGHPRI | WQ_MEM_RECLAIM | WQ_SYSFS, 0);
	अगर (!ib_comp_wq) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	ib_comp_unbound_wq =
		alloc_workqueue("ib-comp-unb-wq",
				WQ_UNBOUND | WQ_HIGHPRI | WQ_MEM_RECLAIM |
				WQ_SYSFS, WQ_UNBOUND_MAX_ACTIVE);
	अगर (!ib_comp_unbound_wq) अणु
		ret = -ENOMEM;
		जाओ err_comp;
	पूर्ण

	ret = class_रेजिस्टर(&ib_class);
	अगर (ret) अणु
		pr_warn("Couldn't create InfiniBand device class\n");
		जाओ err_comp_unbound;
	पूर्ण

	rdma_nl_init();

	ret = addr_init();
	अगर (ret) अणु
		pr_warn("Couldn't init IB address resolution\n");
		जाओ err_ibnl;
	पूर्ण

	ret = ib_mad_init();
	अगर (ret) अणु
		pr_warn("Couldn't init IB MAD\n");
		जाओ err_addr;
	पूर्ण

	ret = ib_sa_init();
	अगर (ret) अणु
		pr_warn("Couldn't init SA\n");
		जाओ err_mad;
	पूर्ण

	ret = रेजिस्टर_blocking_lsm_notअगरier(&ibdev_lsm_nb);
	अगर (ret) अणु
		pr_warn("Couldn't register LSM notifier. ret %d\n", ret);
		जाओ err_sa;
	पूर्ण

	ret = रेजिस्टर_pernet_device(&rdma_dev_net_ops);
	अगर (ret) अणु
		pr_warn("Couldn't init compat dev. ret %d\n", ret);
		जाओ err_compat;
	पूर्ण

	nldev_init();
	rdma_nl_रेजिस्टर(RDMA_NL_LS, ibnl_ls_cb_table);
	roce_gid_mgmt_init();

	वापस 0;

err_compat:
	unरेजिस्टर_blocking_lsm_notअगरier(&ibdev_lsm_nb);
err_sa:
	ib_sa_cleanup();
err_mad:
	ib_mad_cleanup();
err_addr:
	addr_cleanup();
err_ibnl:
	class_unरेजिस्टर(&ib_class);
err_comp_unbound:
	destroy_workqueue(ib_comp_unbound_wq);
err_comp:
	destroy_workqueue(ib_comp_wq);
err:
	destroy_workqueue(ib_wq);
	वापस ret;
पूर्ण

अटल व्योम __निकास ib_core_cleanup(व्योम)
अणु
	roce_gid_mgmt_cleanup();
	nldev_निकास();
	rdma_nl_unरेजिस्टर(RDMA_NL_LS);
	unरेजिस्टर_pernet_device(&rdma_dev_net_ops);
	unरेजिस्टर_blocking_lsm_notअगरier(&ibdev_lsm_nb);
	ib_sa_cleanup();
	ib_mad_cleanup();
	addr_cleanup();
	rdma_nl_निकास();
	class_unरेजिस्टर(&ib_class);
	destroy_workqueue(ib_comp_unbound_wq);
	destroy_workqueue(ib_comp_wq);
	/* Make sure that any pending umem accounting work is करोne. */
	destroy_workqueue(ib_wq);
	flush_workqueue(प्रणाली_unbound_wq);
	WARN_ON(!xa_empty(&clients));
	WARN_ON(!xa_empty(&devices));
पूर्ण

MODULE_ALIAS_RDMA_NETLINK(RDMA_NL_LS, 4);

/* ib core relies on netdev stack to first रेजिस्टर net_ns_type_operations
 * ns kobject type beक्रमe ib_core initialization.
 */
fs_initcall(ib_core_init);
module_निकास(ib_core_cleanup);
