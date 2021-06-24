<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * drivers/base/core.c - core driver model code (device registration, etc)
 *
 * Copyright (c) 2002-3 Patrick Mochel
 * Copyright (c) 2002-3 Open Source Development Lअसल
 * Copyright (c) 2006 Greg Kroah-Harपंचांगan <gregkh@suse.de>
 * Copyright (c) 2006 Novell, Inc.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/fwnode.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/kdev_t.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/genhd.h>
#समावेश <linux/mutex.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/netdevice.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/mm.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/dma-map-ops.h> /* क्रम dma_शेष_coherent */

#समावेश "base.h"
#समावेश "power/power.h"

#अगर_घोषित CONFIG_SYSFS_DEPRECATED
#अगर_घोषित CONFIG_SYSFS_DEPRECATED_V2
दीर्घ sysfs_deprecated = 1;
#अन्यथा
दीर्घ sysfs_deprecated = 0;
#पूर्ण_अगर
अटल पूर्णांक __init sysfs_deprecated_setup(अक्षर *arg)
अणु
	वापस kम_से_दीर्घ(arg, 10, &sysfs_deprecated);
पूर्ण
early_param("sysfs.deprecated", sysfs_deprecated_setup);
#पूर्ण_अगर

/* Device links support. */
अटल LIST_HEAD(deferred_sync);
अटल अचिन्हित पूर्णांक defer_sync_state_count = 1;
अटल DEFINE_MUTEX(fwnode_link_lock);
अटल bool fw_devlink_is_permissive(व्योम);
अटल bool fw_devlink_drv_reg_करोne;

/**
 * fwnode_link_add - Create a link between two fwnode_handles.
 * @con: Consumer end of the link.
 * @sup: Supplier end of the link.
 *
 * Create a fwnode link between fwnode handles @con and @sup. The fwnode link
 * represents the detail that the firmware lists @sup fwnode as supplying a
 * resource to @con.
 *
 * The driver core will use the fwnode link to create a device link between the
 * two device objects corresponding to @con and @sup when they are created. The
 * driver core will स्वतःmatically delete the fwnode link between @con and @sup
 * after करोing that.
 *
 * Attempts to create duplicate links between the same pair of fwnode handles
 * are ignored and there is no reference counting.
 */
पूर्णांक fwnode_link_add(काष्ठा fwnode_handle *con, काष्ठा fwnode_handle *sup)
अणु
	काष्ठा fwnode_link *link;
	पूर्णांक ret = 0;

	mutex_lock(&fwnode_link_lock);

	list_क्रम_each_entry(link, &sup->consumers, s_hook)
		अगर (link->consumer == con)
			जाओ out;

	link = kzalloc(माप(*link), GFP_KERNEL);
	अगर (!link) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	link->supplier = sup;
	INIT_LIST_HEAD(&link->s_hook);
	link->consumer = con;
	INIT_LIST_HEAD(&link->c_hook);

	list_add(&link->s_hook, &sup->consumers);
	list_add(&link->c_hook, &con->suppliers);
out:
	mutex_unlock(&fwnode_link_lock);

	वापस ret;
पूर्ण

/**
 * fwnode_links_purge_suppliers - Delete all supplier links of fwnode_handle.
 * @fwnode: fwnode whose supplier links need to be deleted
 *
 * Deletes all supplier links connecting directly to @fwnode.
 */
अटल व्योम fwnode_links_purge_suppliers(काष्ठा fwnode_handle *fwnode)
अणु
	काष्ठा fwnode_link *link, *पंचांगp;

	mutex_lock(&fwnode_link_lock);
	list_क्रम_each_entry_safe(link, पंचांगp, &fwnode->suppliers, c_hook) अणु
		list_del(&link->s_hook);
		list_del(&link->c_hook);
		kमुक्त(link);
	पूर्ण
	mutex_unlock(&fwnode_link_lock);
पूर्ण

/**
 * fwnode_links_purge_consumers - Delete all consumer links of fwnode_handle.
 * @fwnode: fwnode whose consumer links need to be deleted
 *
 * Deletes all consumer links connecting directly to @fwnode.
 */
अटल व्योम fwnode_links_purge_consumers(काष्ठा fwnode_handle *fwnode)
अणु
	काष्ठा fwnode_link *link, *पंचांगp;

	mutex_lock(&fwnode_link_lock);
	list_क्रम_each_entry_safe(link, पंचांगp, &fwnode->consumers, s_hook) अणु
		list_del(&link->s_hook);
		list_del(&link->c_hook);
		kमुक्त(link);
	पूर्ण
	mutex_unlock(&fwnode_link_lock);
पूर्ण

/**
 * fwnode_links_purge - Delete all links connected to a fwnode_handle.
 * @fwnode: fwnode whose links needs to be deleted
 *
 * Deletes all links connecting directly to a fwnode.
 */
व्योम fwnode_links_purge(काष्ठा fwnode_handle *fwnode)
अणु
	fwnode_links_purge_suppliers(fwnode);
	fwnode_links_purge_consumers(fwnode);
पूर्ण

व्योम fw_devlink_purge_असलent_suppliers(काष्ठा fwnode_handle *fwnode)
अणु
	काष्ठा fwnode_handle *child;

	/* Don't purge consumer links of an added child */
	अगर (fwnode->dev)
		वापस;

	fwnode->flags |= FWNODE_FLAG_NOT_DEVICE;
	fwnode_links_purge_consumers(fwnode);

	fwnode_क्रम_each_available_child_node(fwnode, child)
		fw_devlink_purge_असलent_suppliers(child);
पूर्ण
EXPORT_SYMBOL_GPL(fw_devlink_purge_असलent_suppliers);

#अगर_घोषित CONFIG_SRCU
अटल DEFINE_MUTEX(device_links_lock);
DEFINE_STATIC_SRCU(device_links_srcu);

अटल अंतरभूत व्योम device_links_ग_लिखो_lock(व्योम)
अणु
	mutex_lock(&device_links_lock);
पूर्ण

अटल अंतरभूत व्योम device_links_ग_लिखो_unlock(व्योम)
अणु
	mutex_unlock(&device_links_lock);
पूर्ण

पूर्णांक device_links_पढ़ो_lock(व्योम) __acquires(&device_links_srcu)
अणु
	वापस srcu_पढ़ो_lock(&device_links_srcu);
पूर्ण

व्योम device_links_पढ़ो_unlock(पूर्णांक idx) __releases(&device_links_srcu)
अणु
	srcu_पढ़ो_unlock(&device_links_srcu, idx);
पूर्ण

पूर्णांक device_links_पढ़ो_lock_held(व्योम)
अणु
	वापस srcu_पढ़ो_lock_held(&device_links_srcu);
पूर्ण

अटल व्योम device_link_synchronize_removal(व्योम)
अणु
	synchronize_srcu(&device_links_srcu);
पूर्ण

अटल व्योम device_link_हटाओ_from_lists(काष्ठा device_link *link)
अणु
	list_del_rcu(&link->s_node);
	list_del_rcu(&link->c_node);
पूर्ण
#अन्यथा /* !CONFIG_SRCU */
अटल DECLARE_RWSEM(device_links_lock);

अटल अंतरभूत व्योम device_links_ग_लिखो_lock(व्योम)
अणु
	करोwn_ग_लिखो(&device_links_lock);
पूर्ण

अटल अंतरभूत व्योम device_links_ग_लिखो_unlock(व्योम)
अणु
	up_ग_लिखो(&device_links_lock);
पूर्ण

पूर्णांक device_links_पढ़ो_lock(व्योम)
अणु
	करोwn_पढ़ो(&device_links_lock);
	वापस 0;
पूर्ण

व्योम device_links_पढ़ो_unlock(पूर्णांक not_used)
अणु
	up_पढ़ो(&device_links_lock);
पूर्ण

#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
पूर्णांक device_links_पढ़ो_lock_held(व्योम)
अणु
	वापस lockdep_is_held(&device_links_lock);
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम device_link_synchronize_removal(व्योम)
अणु
पूर्ण

अटल व्योम device_link_हटाओ_from_lists(काष्ठा device_link *link)
अणु
	list_del(&link->s_node);
	list_del(&link->c_node);
पूर्ण
#पूर्ण_अगर /* !CONFIG_SRCU */

अटल bool device_is_ancestor(काष्ठा device *dev, काष्ठा device *target)
अणु
	जबतक (target->parent) अणु
		target = target->parent;
		अगर (dev == target)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

/**
 * device_is_dependent - Check अगर one device depends on another one
 * @dev: Device to check dependencies क्रम.
 * @target: Device to check against.
 *
 * Check अगर @target depends on @dev or any device dependent on it (its child or
 * its consumer etc).  Return 1 अगर that is the हाल or 0 otherwise.
 */
पूर्णांक device_is_dependent(काष्ठा device *dev, व्योम *target)
अणु
	काष्ठा device_link *link;
	पूर्णांक ret;

	/*
	 * The "ancestors" check is needed to catch the हाल when the target
	 * device has not been completely initialized yet and it is still
	 * missing from the list of children of its parent device.
	 */
	अगर (dev == target || device_is_ancestor(dev, target))
		वापस 1;

	ret = device_क्रम_each_child(dev, target, device_is_dependent);
	अगर (ret)
		वापस ret;

	list_क्रम_each_entry(link, &dev->links.consumers, s_node) अणु
		अगर ((link->flags & ~DL_FLAG_INFERRED) ==
		    (DL_FLAG_SYNC_STATE_ONLY | DL_FLAG_MANAGED))
			जारी;

		अगर (link->consumer == target)
			वापस 1;

		ret = device_is_dependent(link->consumer, target);
		अगर (ret)
			अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम device_link_init_status(काष्ठा device_link *link,
				    काष्ठा device *consumer,
				    काष्ठा device *supplier)
अणु
	चयन (supplier->links.status) अणु
	हाल DL_DEV_PROBING:
		चयन (consumer->links.status) अणु
		हाल DL_DEV_PROBING:
			/*
			 * A consumer driver can create a link to a supplier
			 * that has not completed its probing yet as दीर्घ as it
			 * knows that the supplier is alपढ़ोy functional (क्रम
			 * example, it has just acquired some resources from the
			 * supplier).
			 */
			link->status = DL_STATE_CONSUMER_PROBE;
			अवरोध;
		शेष:
			link->status = DL_STATE_DORMANT;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल DL_DEV_DRIVER_BOUND:
		चयन (consumer->links.status) अणु
		हाल DL_DEV_PROBING:
			link->status = DL_STATE_CONSUMER_PROBE;
			अवरोध;
		हाल DL_DEV_DRIVER_BOUND:
			link->status = DL_STATE_ACTIVE;
			अवरोध;
		शेष:
			link->status = DL_STATE_AVAILABLE;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल DL_DEV_UNBINDING:
		link->status = DL_STATE_SUPPLIER_UNBIND;
		अवरोध;
	शेष:
		link->status = DL_STATE_DORMANT;
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक device_reorder_to_tail(काष्ठा device *dev, व्योम *not_used)
अणु
	काष्ठा device_link *link;

	/*
	 * Devices that have not been रेजिस्टरed yet will be put to the ends
	 * of the lists during the registration, so skip them here.
	 */
	अगर (device_is_रेजिस्टरed(dev))
		devices_kset_move_last(dev);

	अगर (device_pm_initialized(dev))
		device_pm_move_last(dev);

	device_क्रम_each_child(dev, शून्य, device_reorder_to_tail);
	list_क्रम_each_entry(link, &dev->links.consumers, s_node) अणु
		अगर ((link->flags & ~DL_FLAG_INFERRED) ==
		    (DL_FLAG_SYNC_STATE_ONLY | DL_FLAG_MANAGED))
			जारी;
		device_reorder_to_tail(link->consumer, शून्य);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * device_pm_move_to_tail - Move set of devices to the end of device lists
 * @dev: Device to move
 *
 * This is a device_reorder_to_tail() wrapper taking the requisite locks.
 *
 * It moves the @dev aदीर्घ with all of its children and all of its consumers
 * to the ends of the device_kset and dpm_list, recursively.
 */
व्योम device_pm_move_to_tail(काष्ठा device *dev)
अणु
	पूर्णांक idx;

	idx = device_links_पढ़ो_lock();
	device_pm_lock();
	device_reorder_to_tail(dev, शून्य);
	device_pm_unlock();
	device_links_पढ़ो_unlock(idx);
पूर्ण

#घोषणा to_devlink(dev)	container_of((dev), काष्ठा device_link, link_dev)

अटल sमाप_प्रकार status_show(काष्ठा device *dev,
			   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	स्थिर अक्षर *output;

	चयन (to_devlink(dev)->status) अणु
	हाल DL_STATE_NONE:
		output = "not tracked";
		अवरोध;
	हाल DL_STATE_DORMANT:
		output = "dormant";
		अवरोध;
	हाल DL_STATE_AVAILABLE:
		output = "available";
		अवरोध;
	हाल DL_STATE_CONSUMER_PROBE:
		output = "consumer probing";
		अवरोध;
	हाल DL_STATE_ACTIVE:
		output = "active";
		अवरोध;
	हाल DL_STATE_SUPPLIER_UNBIND:
		output = "supplier unbinding";
		अवरोध;
	शेष:
		output = "unknown";
		अवरोध;
	पूर्ण

	वापस sysfs_emit(buf, "%s\n", output);
पूर्ण
अटल DEVICE_ATTR_RO(status);

अटल sमाप_प्रकार स्वतः_हटाओ_on_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा device_link *link = to_devlink(dev);
	स्थिर अक्षर *output;

	अगर (link->flags & DL_FLAG_AUTOREMOVE_SUPPLIER)
		output = "supplier unbind";
	अन्यथा अगर (link->flags & DL_FLAG_AUTOREMOVE_CONSUMER)
		output = "consumer unbind";
	अन्यथा
		output = "never";

	वापस sysfs_emit(buf, "%s\n", output);
पूर्ण
अटल DEVICE_ATTR_RO(स्वतः_हटाओ_on);

अटल sमाप_प्रकार runसमय_pm_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा device_link *link = to_devlink(dev);

	वापस sysfs_emit(buf, "%d\n", !!(link->flags & DL_FLAG_PM_RUNTIME));
पूर्ण
अटल DEVICE_ATTR_RO(runसमय_pm);

अटल sमाप_प्रकार sync_state_only_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा device_link *link = to_devlink(dev);

	वापस sysfs_emit(buf, "%d\n",
			  !!(link->flags & DL_FLAG_SYNC_STATE_ONLY));
पूर्ण
अटल DEVICE_ATTR_RO(sync_state_only);

अटल काष्ठा attribute *devlink_attrs[] = अणु
	&dev_attr_status.attr,
	&dev_attr_स्वतः_हटाओ_on.attr,
	&dev_attr_runसमय_pm.attr,
	&dev_attr_sync_state_only.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(devlink);

अटल व्योम device_link_release_fn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा device_link *link = container_of(work, काष्ठा device_link, rm_work);

	/* Ensure that all references to the link object have been dropped. */
	device_link_synchronize_removal();

	जबतक (refcount_dec_not_one(&link->rpm_active))
		pm_runसमय_put(link->supplier);

	put_device(link->consumer);
	put_device(link->supplier);
	kमुक्त(link);
पूर्ण

अटल व्योम devlink_dev_release(काष्ठा device *dev)
अणु
	काष्ठा device_link *link = to_devlink(dev);

	INIT_WORK(&link->rm_work, device_link_release_fn);
	/*
	 * It may take a जबतक to complete this work because of the SRCU
	 * synchronization in device_link_release_fn() and अगर the consumer or
	 * supplier devices get deleted when it runs, so put it पूर्णांकo the "long"
	 * workqueue.
	 */
	queue_work(प्रणाली_दीर्घ_wq, &link->rm_work);
पूर्ण

अटल काष्ठा class devlink_class = अणु
	.name = "devlink",
	.owner = THIS_MODULE,
	.dev_groups = devlink_groups,
	.dev_release = devlink_dev_release,
पूर्ण;

अटल पूर्णांक devlink_add_symlinks(काष्ठा device *dev,
				काष्ठा class_पूर्णांकerface *class_पूर्णांकf)
अणु
	पूर्णांक ret;
	माप_प्रकार len;
	काष्ठा device_link *link = to_devlink(dev);
	काष्ठा device *sup = link->supplier;
	काष्ठा device *con = link->consumer;
	अक्षर *buf;

	len = max(म_माप(dev_bus_name(sup)) + म_माप(dev_name(sup)),
		  म_माप(dev_bus_name(con)) + म_माप(dev_name(con)));
	len += म_माप(":");
	len += म_माप("supplier:") + 1;
	buf = kzalloc(len, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	ret = sysfs_create_link(&link->link_dev.kobj, &sup->kobj, "supplier");
	अगर (ret)
		जाओ out;

	ret = sysfs_create_link(&link->link_dev.kobj, &con->kobj, "consumer");
	अगर (ret)
		जाओ err_con;

	snम_लिखो(buf, len, "consumer:%s:%s", dev_bus_name(con), dev_name(con));
	ret = sysfs_create_link(&sup->kobj, &link->link_dev.kobj, buf);
	अगर (ret)
		जाओ err_con_dev;

	snम_लिखो(buf, len, "supplier:%s:%s", dev_bus_name(sup), dev_name(sup));
	ret = sysfs_create_link(&con->kobj, &link->link_dev.kobj, buf);
	अगर (ret)
		जाओ err_sup_dev;

	जाओ out;

err_sup_dev:
	snम_लिखो(buf, len, "consumer:%s:%s", dev_bus_name(con), dev_name(con));
	sysfs_हटाओ_link(&sup->kobj, buf);
err_con_dev:
	sysfs_हटाओ_link(&link->link_dev.kobj, "consumer");
err_con:
	sysfs_हटाओ_link(&link->link_dev.kobj, "supplier");
out:
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल व्योम devlink_हटाओ_symlinks(काष्ठा device *dev,
				   काष्ठा class_पूर्णांकerface *class_पूर्णांकf)
अणु
	काष्ठा device_link *link = to_devlink(dev);
	माप_प्रकार len;
	काष्ठा device *sup = link->supplier;
	काष्ठा device *con = link->consumer;
	अक्षर *buf;

	sysfs_हटाओ_link(&link->link_dev.kobj, "consumer");
	sysfs_हटाओ_link(&link->link_dev.kobj, "supplier");

	len = max(म_माप(dev_bus_name(sup)) + म_माप(dev_name(sup)),
		  म_माप(dev_bus_name(con)) + म_माप(dev_name(con)));
	len += म_माप(":");
	len += म_माप("supplier:") + 1;
	buf = kzalloc(len, GFP_KERNEL);
	अगर (!buf) अणु
		WARN(1, "Unable to properly free device link symlinks!\n");
		वापस;
	पूर्ण

	snम_लिखो(buf, len, "supplier:%s:%s", dev_bus_name(sup), dev_name(sup));
	sysfs_हटाओ_link(&con->kobj, buf);
	snम_लिखो(buf, len, "consumer:%s:%s", dev_bus_name(con), dev_name(con));
	sysfs_हटाओ_link(&sup->kobj, buf);
	kमुक्त(buf);
पूर्ण

अटल काष्ठा class_पूर्णांकerface devlink_class_पूर्णांकf = अणु
	.class = &devlink_class,
	.add_dev = devlink_add_symlinks,
	.हटाओ_dev = devlink_हटाओ_symlinks,
पूर्ण;

अटल पूर्णांक __init devlink_class_init(व्योम)
अणु
	पूर्णांक ret;

	ret = class_रेजिस्टर(&devlink_class);
	अगर (ret)
		वापस ret;

	ret = class_पूर्णांकerface_रेजिस्टर(&devlink_class_पूर्णांकf);
	अगर (ret)
		class_unरेजिस्टर(&devlink_class);

	वापस ret;
पूर्ण
postcore_initcall(devlink_class_init);

#घोषणा DL_MANAGED_LINK_FLAGS (DL_FLAG_AUTOREMOVE_CONSUMER | \
			       DL_FLAG_AUTOREMOVE_SUPPLIER | \
			       DL_FLAG_AUTOPROBE_CONSUMER  | \
			       DL_FLAG_SYNC_STATE_ONLY | \
			       DL_FLAG_INFERRED)

#घोषणा DL_ADD_VALID_FLAGS (DL_MANAGED_LINK_FLAGS | DL_FLAG_STATELESS | \
			    DL_FLAG_PM_RUNTIME | DL_FLAG_RPM_ACTIVE)

/**
 * device_link_add - Create a link between two devices.
 * @consumer: Consumer end of the link.
 * @supplier: Supplier end of the link.
 * @flags: Link flags.
 *
 * The caller is responsible क्रम the proper synchronization of the link creation
 * with runसमय PM.  First, setting the DL_FLAG_PM_RUNTIME flag will cause the
 * runसमय PM framework to take the link पूर्णांकo account.  Second, अगर the
 * DL_FLAG_RPM_ACTIVE flag is set in addition to it, the supplier devices will
 * be क्रमced पूर्णांकo the active meta state and reference-counted upon the creation
 * of the link.  If DL_FLAG_PM_RUNTIME is not set, DL_FLAG_RPM_ACTIVE will be
 * ignored.
 *
 * If DL_FLAG_STATELESS is set in @flags, the caller of this function is
 * expected to release the link वापसed by it directly with the help of either
 * device_link_del() or device_link_हटाओ().
 *
 * If that flag is not set, however, the caller of this function is handing the
 * management of the link over to the driver core entirely and its वापस value
 * can only be used to check whether or not the link is present.  In that हाल,
 * the DL_FLAG_AUTOREMOVE_CONSUMER and DL_FLAG_AUTOREMOVE_SUPPLIER device link
 * flags can be used to indicate to the driver core when the link can be safely
 * deleted.  Namely, setting one of them in @flags indicates to the driver core
 * that the link is not going to be used (by the given caller of this function)
 * after unbinding the consumer or supplier driver, respectively, from its
 * device, so the link can be deleted at that poपूर्णांक.  If none of them is set,
 * the link will be मुख्यtained until one of the devices poपूर्णांकed to by it (either
 * the consumer or the supplier) is unरेजिस्टरed.
 *
 * Also, अगर DL_FLAG_STATELESS, DL_FLAG_AUTOREMOVE_CONSUMER and
 * DL_FLAG_AUTOREMOVE_SUPPLIER are not set in @flags (that is, a persistent
 * managed device link is being added), the DL_FLAG_AUTOPROBE_CONSUMER flag can
 * be used to request the driver core to स्वतःmatically probe क्रम a consumer
 * driver after successfully binding a driver to the supplier device.
 *
 * The combination of DL_FLAG_STATELESS and one of DL_FLAG_AUTOREMOVE_CONSUMER,
 * DL_FLAG_AUTOREMOVE_SUPPLIER, or DL_FLAG_AUTOPROBE_CONSUMER set in @flags at
 * the same समय is invalid and will cause शून्य to be वापसed upfront.
 * However, अगर a device link between the given @consumer and @supplier pair
 * exists alपढ़ोy when this function is called क्रम them, the existing link will
 * be वापसed regardless of its current type and status (the link's flags may
 * be modअगरied then).  The caller of this function is then expected to treat
 * the link as though it has just been created, so (in particular) अगर
 * DL_FLAG_STATELESS was passed in @flags, the link needs to be released
 * explicitly when not needed any more (as stated above).
 *
 * A side effect of the link creation is re-ordering of dpm_list and the
 * devices_kset list by moving the consumer device and all devices depending
 * on it to the ends of these lists (that करोes not happen to devices that have
 * not been रेजिस्टरed when this function is called).
 *
 * The supplier device is required to be रेजिस्टरed when this function is called
 * and शून्य will be वापसed अगर that is not the हाल.  The consumer device need
 * not be रेजिस्टरed, however.
 */
काष्ठा device_link *device_link_add(काष्ठा device *consumer,
				    काष्ठा device *supplier, u32 flags)
अणु
	काष्ठा device_link *link;

	अगर (!consumer || !supplier || flags & ~DL_ADD_VALID_FLAGS ||
	    (flags & DL_FLAG_STATELESS && flags & DL_MANAGED_LINK_FLAGS) ||
	    (flags & DL_FLAG_SYNC_STATE_ONLY &&
	     (flags & ~DL_FLAG_INFERRED) != DL_FLAG_SYNC_STATE_ONLY) ||
	    (flags & DL_FLAG_AUTOPROBE_CONSUMER &&
	     flags & (DL_FLAG_AUTOREMOVE_CONSUMER |
		      DL_FLAG_AUTOREMOVE_SUPPLIER)))
		वापस शून्य;

	अगर (flags & DL_FLAG_PM_RUNTIME && flags & DL_FLAG_RPM_ACTIVE) अणु
		अगर (pm_runसमय_get_sync(supplier) < 0) अणु
			pm_runसमय_put_noidle(supplier);
			वापस शून्य;
		पूर्ण
	पूर्ण

	अगर (!(flags & DL_FLAG_STATELESS))
		flags |= DL_FLAG_MANAGED;

	device_links_ग_लिखो_lock();
	device_pm_lock();

	/*
	 * If the supplier has not been fully रेजिस्टरed yet or there is a
	 * reverse (non-SYNC_STATE_ONLY) dependency between the consumer and
	 * the supplier alपढ़ोy in the graph, वापस शून्य. If the link is a
	 * SYNC_STATE_ONLY link, we करोn't check क्रम reverse dependencies
	 * because it only affects sync_state() callbacks.
	 */
	अगर (!device_pm_initialized(supplier)
	    || (!(flags & DL_FLAG_SYNC_STATE_ONLY) &&
		  device_is_dependent(consumer, supplier))) अणु
		link = शून्य;
		जाओ out;
	पूर्ण

	/*
	 * SYNC_STATE_ONLY links are useless once a consumer device has probed.
	 * So, only create it अगर the consumer hasn't probed yet.
	 */
	अगर (flags & DL_FLAG_SYNC_STATE_ONLY &&
	    consumer->links.status != DL_DEV_NO_DRIVER &&
	    consumer->links.status != DL_DEV_PROBING) अणु
		link = शून्य;
		जाओ out;
	पूर्ण

	/*
	 * DL_FLAG_AUTOREMOVE_SUPPLIER indicates that the link will be needed
	 * दीर्घer than क्रम DL_FLAG_AUTOREMOVE_CONSUMER and setting them both
	 * together करोesn't make sense, so prefer DL_FLAG_AUTOREMOVE_SUPPLIER.
	 */
	अगर (flags & DL_FLAG_AUTOREMOVE_SUPPLIER)
		flags &= ~DL_FLAG_AUTOREMOVE_CONSUMER;

	list_क्रम_each_entry(link, &supplier->links.consumers, s_node) अणु
		अगर (link->consumer != consumer)
			जारी;

		अगर (link->flags & DL_FLAG_INFERRED &&
		    !(flags & DL_FLAG_INFERRED))
			link->flags &= ~DL_FLAG_INFERRED;

		अगर (flags & DL_FLAG_PM_RUNTIME) अणु
			अगर (!(link->flags & DL_FLAG_PM_RUNTIME)) अणु
				pm_runसमय_new_link(consumer);
				link->flags |= DL_FLAG_PM_RUNTIME;
			पूर्ण
			अगर (flags & DL_FLAG_RPM_ACTIVE)
				refcount_inc(&link->rpm_active);
		पूर्ण

		अगर (flags & DL_FLAG_STATELESS) अणु
			kref_get(&link->kref);
			अगर (link->flags & DL_FLAG_SYNC_STATE_ONLY &&
			    !(link->flags & DL_FLAG_STATELESS)) अणु
				link->flags |= DL_FLAG_STATELESS;
				जाओ reorder;
			पूर्ण अन्यथा अणु
				link->flags |= DL_FLAG_STATELESS;
				जाओ out;
			पूर्ण
		पूर्ण

		/*
		 * If the lअगरe समय of the link following from the new flags is
		 * दीर्घer than indicated by the flags of the existing link,
		 * update the existing link to stay around दीर्घer.
		 */
		अगर (flags & DL_FLAG_AUTOREMOVE_SUPPLIER) अणु
			अगर (link->flags & DL_FLAG_AUTOREMOVE_CONSUMER) अणु
				link->flags &= ~DL_FLAG_AUTOREMOVE_CONSUMER;
				link->flags |= DL_FLAG_AUTOREMOVE_SUPPLIER;
			पूर्ण
		पूर्ण अन्यथा अगर (!(flags & DL_FLAG_AUTOREMOVE_CONSUMER)) अणु
			link->flags &= ~(DL_FLAG_AUTOREMOVE_CONSUMER |
					 DL_FLAG_AUTOREMOVE_SUPPLIER);
		पूर्ण
		अगर (!(link->flags & DL_FLAG_MANAGED)) अणु
			kref_get(&link->kref);
			link->flags |= DL_FLAG_MANAGED;
			device_link_init_status(link, consumer, supplier);
		पूर्ण
		अगर (link->flags & DL_FLAG_SYNC_STATE_ONLY &&
		    !(flags & DL_FLAG_SYNC_STATE_ONLY)) अणु
			link->flags &= ~DL_FLAG_SYNC_STATE_ONLY;
			जाओ reorder;
		पूर्ण

		जाओ out;
	पूर्ण

	link = kzalloc(माप(*link), GFP_KERNEL);
	अगर (!link)
		जाओ out;

	refcount_set(&link->rpm_active, 1);

	get_device(supplier);
	link->supplier = supplier;
	INIT_LIST_HEAD(&link->s_node);
	get_device(consumer);
	link->consumer = consumer;
	INIT_LIST_HEAD(&link->c_node);
	link->flags = flags;
	kref_init(&link->kref);

	link->link_dev.class = &devlink_class;
	device_set_pm_not_required(&link->link_dev);
	dev_set_name(&link->link_dev, "%s:%s--%s:%s",
		     dev_bus_name(supplier), dev_name(supplier),
		     dev_bus_name(consumer), dev_name(consumer));
	अगर (device_रेजिस्टर(&link->link_dev)) अणु
		put_device(consumer);
		put_device(supplier);
		kमुक्त(link);
		link = शून्य;
		जाओ out;
	पूर्ण

	अगर (flags & DL_FLAG_PM_RUNTIME) अणु
		अगर (flags & DL_FLAG_RPM_ACTIVE)
			refcount_inc(&link->rpm_active);

		pm_runसमय_new_link(consumer);
	पूर्ण

	/* Determine the initial link state. */
	अगर (flags & DL_FLAG_STATELESS)
		link->status = DL_STATE_NONE;
	अन्यथा
		device_link_init_status(link, consumer, supplier);

	/*
	 * Some callers expect the link creation during consumer driver probe to
	 * resume the supplier even without DL_FLAG_RPM_ACTIVE.
	 */
	अगर (link->status == DL_STATE_CONSUMER_PROBE &&
	    flags & DL_FLAG_PM_RUNTIME)
		pm_runसमय_resume(supplier);

	list_add_tail_rcu(&link->s_node, &supplier->links.consumers);
	list_add_tail_rcu(&link->c_node, &consumer->links.suppliers);

	अगर (flags & DL_FLAG_SYNC_STATE_ONLY) अणु
		dev_dbg(consumer,
			"Linked as a sync state only consumer to %s\n",
			dev_name(supplier));
		जाओ out;
	पूर्ण

reorder:
	/*
	 * Move the consumer and all of the devices depending on it to the end
	 * of dpm_list and the devices_kset list.
	 *
	 * It is necessary to hold dpm_list locked throughout all that or अन्यथा
	 * we may end up suspending with a wrong ordering of it.
	 */
	device_reorder_to_tail(consumer, शून्य);

	dev_dbg(consumer, "Linked as a consumer to %s\n", dev_name(supplier));

out:
	device_pm_unlock();
	device_links_ग_लिखो_unlock();

	अगर ((flags & DL_FLAG_PM_RUNTIME && flags & DL_FLAG_RPM_ACTIVE) && !link)
		pm_runसमय_put(supplier);

	वापस link;
पूर्ण
EXPORT_SYMBOL_GPL(device_link_add);

अटल व्योम __device_link_del(काष्ठा kref *kref)
अणु
	काष्ठा device_link *link = container_of(kref, काष्ठा device_link, kref);

	dev_dbg(link->consumer, "Dropping the link to %s\n",
		dev_name(link->supplier));

	pm_runसमय_drop_link(link);

	device_link_हटाओ_from_lists(link);
	device_unरेजिस्टर(&link->link_dev);
पूर्ण

अटल व्योम device_link_put_kref(काष्ठा device_link *link)
अणु
	अगर (link->flags & DL_FLAG_STATELESS)
		kref_put(&link->kref, __device_link_del);
	अन्यथा
		WARN(1, "Unable to drop a managed device link reference\n");
पूर्ण

/**
 * device_link_del - Delete a stateless link between two devices.
 * @link: Device link to delete.
 *
 * The caller must ensure proper synchronization of this function with runसमय
 * PM.  If the link was added multiple बार, it needs to be deleted as often.
 * Care is required क्रम hotplugged devices:  Their links are purged on removal
 * and calling device_link_del() is then no दीर्घer allowed.
 */
व्योम device_link_del(काष्ठा device_link *link)
अणु
	device_links_ग_लिखो_lock();
	device_link_put_kref(link);
	device_links_ग_लिखो_unlock();
पूर्ण
EXPORT_SYMBOL_GPL(device_link_del);

/**
 * device_link_हटाओ - Delete a stateless link between two devices.
 * @consumer: Consumer end of the link.
 * @supplier: Supplier end of the link.
 *
 * The caller must ensure proper synchronization of this function with runसमय
 * PM.
 */
व्योम device_link_हटाओ(व्योम *consumer, काष्ठा device *supplier)
अणु
	काष्ठा device_link *link;

	अगर (WARN_ON(consumer == supplier))
		वापस;

	device_links_ग_लिखो_lock();

	list_क्रम_each_entry(link, &supplier->links.consumers, s_node) अणु
		अगर (link->consumer == consumer) अणु
			device_link_put_kref(link);
			अवरोध;
		पूर्ण
	पूर्ण

	device_links_ग_लिखो_unlock();
पूर्ण
EXPORT_SYMBOL_GPL(device_link_हटाओ);

अटल व्योम device_links_missing_supplier(काष्ठा device *dev)
अणु
	काष्ठा device_link *link;

	list_क्रम_each_entry(link, &dev->links.suppliers, c_node) अणु
		अगर (link->status != DL_STATE_CONSUMER_PROBE)
			जारी;

		अगर (link->supplier->links.status == DL_DEV_DRIVER_BOUND) अणु
			WRITE_ONCE(link->status, DL_STATE_AVAILABLE);
		पूर्ण अन्यथा अणु
			WARN_ON(!(link->flags & DL_FLAG_SYNC_STATE_ONLY));
			WRITE_ONCE(link->status, DL_STATE_DORMANT);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * device_links_check_suppliers - Check presence of supplier drivers.
 * @dev: Consumer device.
 *
 * Check links from this device to any suppliers.  Walk the list of the device's
 * links to suppliers and see अगर all of them are available.  If not, simply
 * वापस -EPROBE_DEFER.
 *
 * We need to guarantee that the supplier will not go away after the check has
 * been positive here.  It only can go away in __device_release_driver() and
 * that function  checks the device's links to consumers.  This means we need to
 * mark the link as "consumer probe in progress" to make the supplier removal
 * रुको क्रम us to complete (or bad things may happen).
 *
 * Links without the DL_FLAG_MANAGED flag set are ignored.
 */
पूर्णांक device_links_check_suppliers(काष्ठा device *dev)
अणु
	काष्ठा device_link *link;
	पूर्णांक ret = 0;

	/*
	 * Device रुकोing क्रम supplier to become available is not allowed to
	 * probe.
	 */
	mutex_lock(&fwnode_link_lock);
	अगर (dev->fwnode && !list_empty(&dev->fwnode->suppliers) &&
	    !fw_devlink_is_permissive()) अणु
		dev_dbg(dev, "probe deferral - wait for supplier %pfwP\n",
			list_first_entry(&dev->fwnode->suppliers,
			काष्ठा fwnode_link,
			c_hook)->supplier);
		mutex_unlock(&fwnode_link_lock);
		वापस -EPROBE_DEFER;
	पूर्ण
	mutex_unlock(&fwnode_link_lock);

	device_links_ग_लिखो_lock();

	list_क्रम_each_entry(link, &dev->links.suppliers, c_node) अणु
		अगर (!(link->flags & DL_FLAG_MANAGED))
			जारी;

		अगर (link->status != DL_STATE_AVAILABLE &&
		    !(link->flags & DL_FLAG_SYNC_STATE_ONLY)) अणु
			device_links_missing_supplier(dev);
			dev_dbg(dev, "probe deferral - supplier %s not ready\n",
				dev_name(link->supplier));
			ret = -EPROBE_DEFER;
			अवरोध;
		पूर्ण
		WRITE_ONCE(link->status, DL_STATE_CONSUMER_PROBE);
	पूर्ण
	dev->links.status = DL_DEV_PROBING;

	device_links_ग_लिखो_unlock();
	वापस ret;
पूर्ण

/**
 * __device_links_queue_sync_state - Queue a device क्रम sync_state() callback
 * @dev: Device to call sync_state() on
 * @list: List head to queue the @dev on
 *
 * Queues a device क्रम a sync_state() callback when the device links ग_लिखो lock
 * isn't held. This allows the sync_state() execution flow to use device links
 * APIs.  The caller must ensure this function is called with
 * device_links_ग_लिखो_lock() held.
 *
 * This function करोes a get_device() to make sure the device is not मुक्तd जबतक
 * on this list.
 *
 * So the caller must also ensure that device_links_flush_sync_list() is called
 * as soon as the caller releases device_links_ग_लिखो_lock().  This is necessary
 * to make sure the sync_state() is called in a समयly fashion and the
 * put_device() is called on this device.
 */
अटल व्योम __device_links_queue_sync_state(काष्ठा device *dev,
					    काष्ठा list_head *list)
अणु
	काष्ठा device_link *link;

	अगर (!dev_has_sync_state(dev))
		वापस;
	अगर (dev->state_synced)
		वापस;

	list_क्रम_each_entry(link, &dev->links.consumers, s_node) अणु
		अगर (!(link->flags & DL_FLAG_MANAGED))
			जारी;
		अगर (link->status != DL_STATE_ACTIVE)
			वापस;
	पूर्ण

	/*
	 * Set the flag here to aव्योम adding the same device to a list more
	 * than once. This can happen अगर new consumers get added to the device
	 * and probed beक्रमe the list is flushed.
	 */
	dev->state_synced = true;

	अगर (WARN_ON(!list_empty(&dev->links.defer_sync)))
		वापस;

	get_device(dev);
	list_add_tail(&dev->links.defer_sync, list);
पूर्ण

/**
 * device_links_flush_sync_list - Call sync_state() on a list of devices
 * @list: List of devices to call sync_state() on
 * @करोnt_lock_dev: Device क्रम which lock is alपढ़ोy held by the caller
 *
 * Calls sync_state() on all the devices that have been queued क्रम it. This
 * function is used in conjunction with __device_links_queue_sync_state(). The
 * @करोnt_lock_dev parameter is useful when this function is called from a
 * context where a device lock is alपढ़ोy held.
 */
अटल व्योम device_links_flush_sync_list(काष्ठा list_head *list,
					 काष्ठा device *करोnt_lock_dev)
अणु
	काष्ठा device *dev, *पंचांगp;

	list_क्रम_each_entry_safe(dev, पंचांगp, list, links.defer_sync) अणु
		list_del_init(&dev->links.defer_sync);

		अगर (dev != करोnt_lock_dev)
			device_lock(dev);

		अगर (dev->bus->sync_state)
			dev->bus->sync_state(dev);
		अन्यथा अगर (dev->driver && dev->driver->sync_state)
			dev->driver->sync_state(dev);

		अगर (dev != करोnt_lock_dev)
			device_unlock(dev);

		put_device(dev);
	पूर्ण
पूर्ण

व्योम device_links_supplier_sync_state_छोड़ो(व्योम)
अणु
	device_links_ग_लिखो_lock();
	defer_sync_state_count++;
	device_links_ग_लिखो_unlock();
पूर्ण

व्योम device_links_supplier_sync_state_resume(व्योम)
अणु
	काष्ठा device *dev, *पंचांगp;
	LIST_HEAD(sync_list);

	device_links_ग_लिखो_lock();
	अगर (!defer_sync_state_count) अणु
		WARN(true, "Unmatched sync_state pause/resume!");
		जाओ out;
	पूर्ण
	defer_sync_state_count--;
	अगर (defer_sync_state_count)
		जाओ out;

	list_क्रम_each_entry_safe(dev, पंचांगp, &deferred_sync, links.defer_sync) अणु
		/*
		 * Delete from deferred_sync list beक्रमe queuing it to
		 * sync_list because defer_sync is used क्रम both lists.
		 */
		list_del_init(&dev->links.defer_sync);
		__device_links_queue_sync_state(dev, &sync_list);
	पूर्ण
out:
	device_links_ग_लिखो_unlock();

	device_links_flush_sync_list(&sync_list, शून्य);
पूर्ण

अटल पूर्णांक sync_state_resume_initcall(व्योम)
अणु
	device_links_supplier_sync_state_resume();
	वापस 0;
पूर्ण
late_initcall(sync_state_resume_initcall);

अटल व्योम __device_links_supplier_defer_sync(काष्ठा device *sup)
अणु
	अगर (list_empty(&sup->links.defer_sync) && dev_has_sync_state(sup))
		list_add_tail(&sup->links.defer_sync, &deferred_sync);
पूर्ण

अटल व्योम device_link_drop_managed(काष्ठा device_link *link)
अणु
	link->flags &= ~DL_FLAG_MANAGED;
	WRITE_ONCE(link->status, DL_STATE_NONE);
	kref_put(&link->kref, __device_link_del);
पूर्ण

अटल sमाप_प्रकार रुकोing_क्रम_supplier_show(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 अक्षर *buf)
अणु
	bool val;

	device_lock(dev);
	val = !list_empty(&dev->fwnode->suppliers);
	device_unlock(dev);
	वापस sysfs_emit(buf, "%u\n", val);
पूर्ण
अटल DEVICE_ATTR_RO(रुकोing_क्रम_supplier);

/**
 * device_links_क्रमce_bind - Prepares device to be क्रमce bound
 * @dev: Consumer device.
 *
 * device_bind_driver() क्रमce binds a device to a driver without calling any
 * driver probe functions. So the consumer really isn't going to रुको क्रम any
 * supplier beक्रमe it's bound to the driver. We still want the device link
 * states to be sensible when this happens.
 *
 * In preparation क्रम device_bind_driver(), this function goes through each
 * supplier device links and checks अगर the supplier is bound. If it is, then
 * the device link status is set to CONSUMER_PROBE. Otherwise, the device link
 * is dropped. Links without the DL_FLAG_MANAGED flag set are ignored.
 */
व्योम device_links_क्रमce_bind(काष्ठा device *dev)
अणु
	काष्ठा device_link *link, *ln;

	device_links_ग_लिखो_lock();

	list_क्रम_each_entry_safe(link, ln, &dev->links.suppliers, c_node) अणु
		अगर (!(link->flags & DL_FLAG_MANAGED))
			जारी;

		अगर (link->status != DL_STATE_AVAILABLE) अणु
			device_link_drop_managed(link);
			जारी;
		पूर्ण
		WRITE_ONCE(link->status, DL_STATE_CONSUMER_PROBE);
	पूर्ण
	dev->links.status = DL_DEV_PROBING;

	device_links_ग_लिखो_unlock();
पूर्ण

/**
 * device_links_driver_bound - Update device links after probing its driver.
 * @dev: Device to update the links क्रम.
 *
 * The probe has been successful, so update links from this device to any
 * consumers by changing their status to "available".
 *
 * Also change the status of @dev's links to suppliers to "active".
 *
 * Links without the DL_FLAG_MANAGED flag set are ignored.
 */
व्योम device_links_driver_bound(काष्ठा device *dev)
अणु
	काष्ठा device_link *link, *ln;
	LIST_HEAD(sync_list);

	/*
	 * If a device binds successfully, it's expected to have created all
	 * the device links it needs to or make new device links as it needs
	 * them. So, fw_devlink no दीर्घer needs to create device links to any
	 * of the device's suppliers.
	 *
	 * Also, अगर a child firmware node of this bound device is not added as
	 * a device by now, assume it is never going to be added and make sure
	 * other devices करोn't defer probe indefinitely by रुकोing क्रम such a
	 * child device.
	 */
	अगर (dev->fwnode && dev->fwnode->dev == dev) अणु
		काष्ठा fwnode_handle *child;
		fwnode_links_purge_suppliers(dev->fwnode);
		fwnode_क्रम_each_available_child_node(dev->fwnode, child)
			fw_devlink_purge_असलent_suppliers(child);
	पूर्ण
	device_हटाओ_file(dev, &dev_attr_रुकोing_क्रम_supplier);

	device_links_ग_लिखो_lock();

	list_क्रम_each_entry(link, &dev->links.consumers, s_node) अणु
		अगर (!(link->flags & DL_FLAG_MANAGED))
			जारी;

		/*
		 * Links created during consumer probe may be in the "consumer
		 * probe" state to start with अगर the supplier is still probing
		 * when they are created and they may become "active" अगर the
		 * consumer probe वापसs first.  Skip them here.
		 */
		अगर (link->status == DL_STATE_CONSUMER_PROBE ||
		    link->status == DL_STATE_ACTIVE)
			जारी;

		WARN_ON(link->status != DL_STATE_DORMANT);
		WRITE_ONCE(link->status, DL_STATE_AVAILABLE);

		अगर (link->flags & DL_FLAG_AUTOPROBE_CONSUMER)
			driver_deferred_probe_add(link->consumer);
	पूर्ण

	अगर (defer_sync_state_count)
		__device_links_supplier_defer_sync(dev);
	अन्यथा
		__device_links_queue_sync_state(dev, &sync_list);

	list_क्रम_each_entry_safe(link, ln, &dev->links.suppliers, c_node) अणु
		काष्ठा device *supplier;

		अगर (!(link->flags & DL_FLAG_MANAGED))
			जारी;

		supplier = link->supplier;
		अगर (link->flags & DL_FLAG_SYNC_STATE_ONLY) अणु
			/*
			 * When DL_FLAG_SYNC_STATE_ONLY is set, it means no
			 * other DL_MANAGED_LINK_FLAGS have been set. So, it's
			 * save to drop the managed link completely.
			 */
			device_link_drop_managed(link);
		पूर्ण अन्यथा अणु
			WARN_ON(link->status != DL_STATE_CONSUMER_PROBE);
			WRITE_ONCE(link->status, DL_STATE_ACTIVE);
		पूर्ण

		/*
		 * This needs to be करोne even क्रम the deleted
		 * DL_FLAG_SYNC_STATE_ONLY device link in हाल it was the last
		 * device link that was preventing the supplier from getting a
		 * sync_state() call.
		 */
		अगर (defer_sync_state_count)
			__device_links_supplier_defer_sync(supplier);
		अन्यथा
			__device_links_queue_sync_state(supplier, &sync_list);
	पूर्ण

	dev->links.status = DL_DEV_DRIVER_BOUND;

	device_links_ग_लिखो_unlock();

	device_links_flush_sync_list(&sync_list, dev);
पूर्ण

/**
 * __device_links_no_driver - Update links of a device without a driver.
 * @dev: Device without a drvier.
 *
 * Delete all non-persistent links from this device to any suppliers.
 *
 * Persistent links stay around, but their status is changed to "available",
 * unless they alपढ़ोy are in the "supplier unbind in progress" state in which
 * हाल they need not be updated.
 *
 * Links without the DL_FLAG_MANAGED flag set are ignored.
 */
अटल व्योम __device_links_no_driver(काष्ठा device *dev)
अणु
	काष्ठा device_link *link, *ln;

	list_क्रम_each_entry_safe_reverse(link, ln, &dev->links.suppliers, c_node) अणु
		अगर (!(link->flags & DL_FLAG_MANAGED))
			जारी;

		अगर (link->flags & DL_FLAG_AUTOREMOVE_CONSUMER) अणु
			device_link_drop_managed(link);
			जारी;
		पूर्ण

		अगर (link->status != DL_STATE_CONSUMER_PROBE &&
		    link->status != DL_STATE_ACTIVE)
			जारी;

		अगर (link->supplier->links.status == DL_DEV_DRIVER_BOUND) अणु
			WRITE_ONCE(link->status, DL_STATE_AVAILABLE);
		पूर्ण अन्यथा अणु
			WARN_ON(!(link->flags & DL_FLAG_SYNC_STATE_ONLY));
			WRITE_ONCE(link->status, DL_STATE_DORMANT);
		पूर्ण
	पूर्ण

	dev->links.status = DL_DEV_NO_DRIVER;
पूर्ण

/**
 * device_links_no_driver - Update links after failing driver probe.
 * @dev: Device whose driver has just failed to probe.
 *
 * Clean up leftover links to consumers क्रम @dev and invoke
 * %__device_links_no_driver() to update links to suppliers क्रम it as
 * appropriate.
 *
 * Links without the DL_FLAG_MANAGED flag set are ignored.
 */
व्योम device_links_no_driver(काष्ठा device *dev)
अणु
	काष्ठा device_link *link;

	device_links_ग_लिखो_lock();

	list_क्रम_each_entry(link, &dev->links.consumers, s_node) अणु
		अगर (!(link->flags & DL_FLAG_MANAGED))
			जारी;

		/*
		 * The probe has failed, so अगर the status of the link is
		 * "consumer probe" or "active", it must have been added by
		 * a probing consumer जबतक this device was still probing.
		 * Change its state to "dormant", as it represents a valid
		 * relationship, but it is not functionally meaningful.
		 */
		अगर (link->status == DL_STATE_CONSUMER_PROBE ||
		    link->status == DL_STATE_ACTIVE)
			WRITE_ONCE(link->status, DL_STATE_DORMANT);
	पूर्ण

	__device_links_no_driver(dev);

	device_links_ग_लिखो_unlock();
पूर्ण

/**
 * device_links_driver_cleanup - Update links after driver removal.
 * @dev: Device whose driver has just gone away.
 *
 * Update links to consumers क्रम @dev by changing their status to "dormant" and
 * invoke %__device_links_no_driver() to update links to suppliers क्रम it as
 * appropriate.
 *
 * Links without the DL_FLAG_MANAGED flag set are ignored.
 */
व्योम device_links_driver_cleanup(काष्ठा device *dev)
अणु
	काष्ठा device_link *link, *ln;

	device_links_ग_लिखो_lock();

	list_क्रम_each_entry_safe(link, ln, &dev->links.consumers, s_node) अणु
		अगर (!(link->flags & DL_FLAG_MANAGED))
			जारी;

		WARN_ON(link->flags & DL_FLAG_AUTOREMOVE_CONSUMER);
		WARN_ON(link->status != DL_STATE_SUPPLIER_UNBIND);

		/*
		 * स्वतःहटाओ the links between this @dev and its consumer
		 * devices that are not active, i.e. where the link state
		 * has moved to DL_STATE_SUPPLIER_UNBIND.
		 */
		अगर (link->status == DL_STATE_SUPPLIER_UNBIND &&
		    link->flags & DL_FLAG_AUTOREMOVE_SUPPLIER)
			device_link_drop_managed(link);

		WRITE_ONCE(link->status, DL_STATE_DORMANT);
	पूर्ण

	list_del_init(&dev->links.defer_sync);
	__device_links_no_driver(dev);

	device_links_ग_लिखो_unlock();
पूर्ण

/**
 * device_links_busy - Check अगर there are any busy links to consumers.
 * @dev: Device to check.
 *
 * Check each consumer of the device and वापस 'true' if its link's status
 * is one of "consumer probe" or "active" (meaning that the given consumer is
 * probing right now or its driver is present).  Otherwise, change the link
 * state to "supplier unbind" to prevent the consumer from being probed
 * successfully going क्रमward.
 *
 * Return 'false' अगर there are no probing or active consumers.
 *
 * Links without the DL_FLAG_MANAGED flag set are ignored.
 */
bool device_links_busy(काष्ठा device *dev)
अणु
	काष्ठा device_link *link;
	bool ret = false;

	device_links_ग_लिखो_lock();

	list_क्रम_each_entry(link, &dev->links.consumers, s_node) अणु
		अगर (!(link->flags & DL_FLAG_MANAGED))
			जारी;

		अगर (link->status == DL_STATE_CONSUMER_PROBE
		    || link->status == DL_STATE_ACTIVE) अणु
			ret = true;
			अवरोध;
		पूर्ण
		WRITE_ONCE(link->status, DL_STATE_SUPPLIER_UNBIND);
	पूर्ण

	dev->links.status = DL_DEV_UNBINDING;

	device_links_ग_लिखो_unlock();
	वापस ret;
पूर्ण

/**
 * device_links_unbind_consumers - Force unbind consumers of the given device.
 * @dev: Device to unbind the consumers of.
 *
 * Walk the list of links to consumers क्रम @dev and अगर any of them is in the
 * "consumer probe" state, रुको क्रम all device probes in progress to complete
 * and start over.
 *
 * If that's not the हाल, change the status of the link to "supplier unbind"
 * and check अगर the link was in the "active" state.  If so, क्रमce the consumer
 * driver to unbind and start over (the consumer will not re-probe as we have
 * changed the state of the link alपढ़ोy).
 *
 * Links without the DL_FLAG_MANAGED flag set are ignored.
 */
व्योम device_links_unbind_consumers(काष्ठा device *dev)
अणु
	काष्ठा device_link *link;

 start:
	device_links_ग_लिखो_lock();

	list_क्रम_each_entry(link, &dev->links.consumers, s_node) अणु
		क्रमागत device_link_state status;

		अगर (!(link->flags & DL_FLAG_MANAGED) ||
		    link->flags & DL_FLAG_SYNC_STATE_ONLY)
			जारी;

		status = link->status;
		अगर (status == DL_STATE_CONSUMER_PROBE) अणु
			device_links_ग_लिखो_unlock();

			रुको_क्रम_device_probe();
			जाओ start;
		पूर्ण
		WRITE_ONCE(link->status, DL_STATE_SUPPLIER_UNBIND);
		अगर (status == DL_STATE_ACTIVE) अणु
			काष्ठा device *consumer = link->consumer;

			get_device(consumer);

			device_links_ग_लिखो_unlock();

			device_release_driver_पूर्णांकernal(consumer, शून्य,
						       consumer->parent);
			put_device(consumer);
			जाओ start;
		पूर्ण
	पूर्ण

	device_links_ग_लिखो_unlock();
पूर्ण

/**
 * device_links_purge - Delete existing links to other devices.
 * @dev: Target device.
 */
अटल व्योम device_links_purge(काष्ठा device *dev)
अणु
	काष्ठा device_link *link, *ln;

	अगर (dev->class == &devlink_class)
		वापस;

	/*
	 * Delete all of the reमुख्यing links from this device to any other
	 * devices (either consumers or suppliers).
	 */
	device_links_ग_लिखो_lock();

	list_क्रम_each_entry_safe_reverse(link, ln, &dev->links.suppliers, c_node) अणु
		WARN_ON(link->status == DL_STATE_ACTIVE);
		__device_link_del(&link->kref);
	पूर्ण

	list_क्रम_each_entry_safe_reverse(link, ln, &dev->links.consumers, s_node) अणु
		WARN_ON(link->status != DL_STATE_DORMANT &&
			link->status != DL_STATE_NONE);
		__device_link_del(&link->kref);
	पूर्ण

	device_links_ग_लिखो_unlock();
पूर्ण

#घोषणा FW_DEVLINK_FLAGS_PERMISSIVE	(DL_FLAG_INFERRED | \
					 DL_FLAG_SYNC_STATE_ONLY)
#घोषणा FW_DEVLINK_FLAGS_ON		(DL_FLAG_INFERRED | \
					 DL_FLAG_AUTOPROBE_CONSUMER)
#घोषणा FW_DEVLINK_FLAGS_RPM		(FW_DEVLINK_FLAGS_ON | \
					 DL_FLAG_PM_RUNTIME)

अटल u32 fw_devlink_flags = FW_DEVLINK_FLAGS_ON;
अटल पूर्णांक __init fw_devlink_setup(अक्षर *arg)
अणु
	अगर (!arg)
		वापस -EINVAL;

	अगर (म_भेद(arg, "off") == 0) अणु
		fw_devlink_flags = 0;
	पूर्ण अन्यथा अगर (म_भेद(arg, "permissive") == 0) अणु
		fw_devlink_flags = FW_DEVLINK_FLAGS_PERMISSIVE;
	पूर्ण अन्यथा अगर (म_भेद(arg, "on") == 0) अणु
		fw_devlink_flags = FW_DEVLINK_FLAGS_ON;
	पूर्ण अन्यथा अगर (म_भेद(arg, "rpm") == 0) अणु
		fw_devlink_flags = FW_DEVLINK_FLAGS_RPM;
	पूर्ण
	वापस 0;
पूर्ण
early_param("fw_devlink", fw_devlink_setup);

अटल bool fw_devlink_strict;
अटल पूर्णांक __init fw_devlink_strict_setup(अक्षर *arg)
अणु
	वापस strtobool(arg, &fw_devlink_strict);
पूर्ण
early_param("fw_devlink.strict", fw_devlink_strict_setup);

u32 fw_devlink_get_flags(व्योम)
अणु
	वापस fw_devlink_flags;
पूर्ण

अटल bool fw_devlink_is_permissive(व्योम)
अणु
	वापस fw_devlink_flags == FW_DEVLINK_FLAGS_PERMISSIVE;
पूर्ण

bool fw_devlink_is_strict(व्योम)
अणु
	वापस fw_devlink_strict && !fw_devlink_is_permissive();
पूर्ण

अटल व्योम fw_devlink_parse_fwnode(काष्ठा fwnode_handle *fwnode)
अणु
	अगर (fwnode->flags & FWNODE_FLAG_LINKS_ADDED)
		वापस;

	fwnode_call_पूर्णांक_op(fwnode, add_links);
	fwnode->flags |= FWNODE_FLAG_LINKS_ADDED;
पूर्ण

अटल व्योम fw_devlink_parse_fwtree(काष्ठा fwnode_handle *fwnode)
अणु
	काष्ठा fwnode_handle *child = शून्य;

	fw_devlink_parse_fwnode(fwnode);

	जबतक ((child = fwnode_get_next_available_child_node(fwnode, child)))
		fw_devlink_parse_fwtree(child);
पूर्ण

अटल व्योम fw_devlink_relax_link(काष्ठा device_link *link)
अणु
	अगर (!(link->flags & DL_FLAG_INFERRED))
		वापस;

	अगर (link->flags == (DL_FLAG_MANAGED | FW_DEVLINK_FLAGS_PERMISSIVE))
		वापस;

	pm_runसमय_drop_link(link);
	link->flags = DL_FLAG_MANAGED | FW_DEVLINK_FLAGS_PERMISSIVE;
	dev_dbg(link->consumer, "Relaxing link with %s\n",
		dev_name(link->supplier));
पूर्ण

अटल पूर्णांक fw_devlink_no_driver(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा device_link *link = to_devlink(dev);

	अगर (!link->supplier->can_match)
		fw_devlink_relax_link(link);

	वापस 0;
पूर्ण

व्योम fw_devlink_drivers_करोne(व्योम)
अणु
	fw_devlink_drv_reg_करोne = true;
	device_links_ग_लिखो_lock();
	class_क्रम_each_device(&devlink_class, शून्य, शून्य,
			      fw_devlink_no_driver);
	device_links_ग_लिखो_unlock();
पूर्ण

अटल व्योम fw_devlink_unblock_consumers(काष्ठा device *dev)
अणु
	काष्ठा device_link *link;

	अगर (!fw_devlink_flags || fw_devlink_is_permissive())
		वापस;

	device_links_ग_लिखो_lock();
	list_क्रम_each_entry(link, &dev->links.consumers, s_node)
		fw_devlink_relax_link(link);
	device_links_ग_लिखो_unlock();
पूर्ण

/**
 * fw_devlink_relax_cycle - Convert cyclic links to SYNC_STATE_ONLY links
 * @con: Device to check dependencies क्रम.
 * @sup: Device to check against.
 *
 * Check अगर @sup depends on @con or any device dependent on it (its child or
 * its consumer etc).  When such a cyclic dependency is found, convert all
 * device links created solely by fw_devlink पूर्णांकo SYNC_STATE_ONLY device links.
 * This is the equivalent of करोing fw_devlink=permissive just between the
 * devices in the cycle. We need to करो this because, at this poपूर्णांक, fw_devlink
 * can't tell which of these dependencies is not a real dependency.
 *
 * Return 1 अगर a cycle is found. Otherwise, वापस 0.
 */
अटल पूर्णांक fw_devlink_relax_cycle(काष्ठा device *con, व्योम *sup)
अणु
	काष्ठा device_link *link;
	पूर्णांक ret;

	अगर (con == sup)
		वापस 1;

	ret = device_क्रम_each_child(con, sup, fw_devlink_relax_cycle);
	अगर (ret)
		वापस ret;

	list_क्रम_each_entry(link, &con->links.consumers, s_node) अणु
		अगर ((link->flags & ~DL_FLAG_INFERRED) ==
		    (DL_FLAG_SYNC_STATE_ONLY | DL_FLAG_MANAGED))
			जारी;

		अगर (!fw_devlink_relax_cycle(link->consumer, sup))
			जारी;

		ret = 1;

		fw_devlink_relax_link(link);
	पूर्ण
	वापस ret;
पूर्ण

/**
 * fw_devlink_create_devlink - Create a device link from a consumer to fwnode
 * @con: consumer device क्रम the device link
 * @sup_handle: fwnode handle of supplier
 * @flags: devlink flags
 *
 * This function will try to create a device link between the consumer device
 * @con and the supplier device represented by @sup_handle.
 *
 * The supplier has to be provided as a fwnode because incorrect cycles in
 * fwnode links can someबार cause the supplier device to never be created.
 * This function detects such हालs and वापसs an error अगर it cannot create a
 * device link from the consumer to a missing supplier.
 *
 * Returns,
 * 0 on successfully creating a device link
 * -EINVAL अगर the device link cannot be created as expected
 * -EAGAIN अगर the device link cannot be created right now, but it may be
 *  possible to करो that in the future
 */
अटल पूर्णांक fw_devlink_create_devlink(काष्ठा device *con,
				     काष्ठा fwnode_handle *sup_handle, u32 flags)
अणु
	काष्ठा device *sup_dev;
	पूर्णांक ret = 0;

	sup_dev = get_dev_from_fwnode(sup_handle);
	अगर (sup_dev) अणु
		/*
		 * If it's one of those drivers that don't actually bind to
		 * their device using driver core, then करोn't रुको on this
		 * supplier device indefinitely.
		 */
		अगर (sup_dev->links.status == DL_DEV_NO_DRIVER &&
		    sup_handle->flags & FWNODE_FLAG_INITIALIZED) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		/*
		 * If this fails, it is due to cycles in device links.  Just
		 * give up on this link and treat it as invalid.
		 */
		अगर (!device_link_add(con, sup_dev, flags) &&
		    !(flags & DL_FLAG_SYNC_STATE_ONLY)) अणु
			dev_info(con, "Fixing up cyclic dependency with %s\n",
				 dev_name(sup_dev));
			device_links_ग_लिखो_lock();
			fw_devlink_relax_cycle(con, sup_dev);
			device_links_ग_लिखो_unlock();
			device_link_add(con, sup_dev,
					FW_DEVLINK_FLAGS_PERMISSIVE);
			ret = -EINVAL;
		पूर्ण

		जाओ out;
	पूर्ण

	/* Supplier that's alपढ़ोy initialized without a काष्ठा device. */
	अगर (sup_handle->flags & FWNODE_FLAG_INITIALIZED)
		वापस -EINVAL;

	/*
	 * DL_FLAG_SYNC_STATE_ONLY करोesn't block probing and supports
	 * cycles. So cycle detection isn't necessary and shouldn't be
	 * करोne.
	 */
	अगर (flags & DL_FLAG_SYNC_STATE_ONLY)
		वापस -EAGAIN;

	/*
	 * If we can't find the supplier device from its fwnode, it might be
	 * due to a cyclic dependency between fwnodes. Some of these cycles can
	 * be broken by applying logic. Check क्रम these types of cycles and
	 * अवरोध them so that devices in the cycle probe properly.
	 *
	 * If the supplier's parent is dependent on the consumer, then
	 * the consumer-supplier dependency is a false dependency. So,
	 * treat it as an invalid link.
	 */
	sup_dev = fwnode_get_next_parent_dev(sup_handle);
	अगर (sup_dev && device_is_dependent(con, sup_dev)) अणु
		dev_dbg(con, "Not linking to %pfwP - False link\n",
			sup_handle);
		ret = -EINVAL;
	पूर्ण अन्यथा अणु
		/*
		 * Can't check for cycles or no cycles. So let's try
		 * again later.
		 */
		ret = -EAGAIN;
	पूर्ण

out:
	put_device(sup_dev);
	वापस ret;
पूर्ण

/**
 * __fw_devlink_link_to_consumers - Create device links to consumers of a device
 * @dev: Device that needs to be linked to its consumers
 *
 * This function looks at all the consumer fwnodes of @dev and creates device
 * links between the consumer device and @dev (supplier).
 *
 * If the consumer device has not been added yet, then this function creates a
 * SYNC_STATE_ONLY link between @dev (supplier) and the बंदst ancestor device
 * of the consumer fwnode. This is necessary to make sure @dev करोesn't get a
 * sync_state() callback beक्रमe the real consumer device माला_लो to be added and
 * then probed.
 *
 * Once device links are created from the real consumer to @dev (supplier), the
 * fwnode links are deleted.
 */
अटल व्योम __fw_devlink_link_to_consumers(काष्ठा device *dev)
अणु
	काष्ठा fwnode_handle *fwnode = dev->fwnode;
	काष्ठा fwnode_link *link, *पंचांगp;

	list_क्रम_each_entry_safe(link, पंचांगp, &fwnode->consumers, s_hook) अणु
		u32 dl_flags = fw_devlink_get_flags();
		काष्ठा device *con_dev;
		bool own_link = true;
		पूर्णांक ret;

		con_dev = get_dev_from_fwnode(link->consumer);
		/*
		 * If consumer device is not available yet, make a "proxy"
		 * SYNC_STATE_ONLY link from the consumer's parent device to
		 * the supplier device. This is necessary to make sure the
		 * supplier करोesn't get a sync_state() callback beक्रमe the real
		 * consumer can create a device link to the supplier.
		 *
		 * This proxy link step is needed to handle the हाल where the
		 * consumer's parent device is added beक्रमe the supplier.
		 */
		अगर (!con_dev) अणु
			con_dev = fwnode_get_next_parent_dev(link->consumer);
			/*
			 * However, अगर the consumer's parent device is also the
			 * parent of the supplier, करोn't create a
			 * consumer-supplier link from the parent to its child
			 * device. Such a dependency is impossible.
			 */
			अगर (con_dev &&
			    fwnode_is_ancestor_of(con_dev->fwnode, fwnode)) अणु
				put_device(con_dev);
				con_dev = शून्य;
			पूर्ण अन्यथा अणु
				own_link = false;
				dl_flags = FW_DEVLINK_FLAGS_PERMISSIVE;
			पूर्ण
		पूर्ण

		अगर (!con_dev)
			जारी;

		ret = fw_devlink_create_devlink(con_dev, fwnode, dl_flags);
		put_device(con_dev);
		अगर (!own_link || ret == -EAGAIN)
			जारी;

		list_del(&link->s_hook);
		list_del(&link->c_hook);
		kमुक्त(link);
	पूर्ण
पूर्ण

/**
 * __fw_devlink_link_to_suppliers - Create device links to suppliers of a device
 * @dev: The consumer device that needs to be linked to its suppliers
 * @fwnode: Root of the fwnode tree that is used to create device links
 *
 * This function looks at all the supplier fwnodes of fwnode tree rooted at
 * @fwnode and creates device links between @dev (consumer) and all the
 * supplier devices of the entire fwnode tree at @fwnode.
 *
 * The function creates normal (non-SYNC_STATE_ONLY) device links between @dev
 * and the real suppliers of @dev. Once these device links are created, the
 * fwnode links are deleted. When such device links are successfully created,
 * this function is called recursively on those supplier devices. This is
 * needed to detect and अवरोध some invalid cycles in fwnode links.  See
 * fw_devlink_create_devlink() क्रम more details.
 *
 * In addition, it also looks at all the suppliers of the entire fwnode tree
 * because some of the child devices of @dev that have not been added yet
 * (because @dev hasn't probed) might alपढ़ोy have their suppliers added to
 * driver core. So, this function creates SYNC_STATE_ONLY device links between
 * @dev (consumer) and these suppliers to make sure they करोn't execute their
 * sync_state() callbacks beक्रमe these child devices have a chance to create
 * their device links. The fwnode links that correspond to the child devices
 * aren't delete because they are needed later to create the device links
 * between the real consumer and supplier devices.
 */
अटल व्योम __fw_devlink_link_to_suppliers(काष्ठा device *dev,
					   काष्ठा fwnode_handle *fwnode)
अणु
	bool own_link = (dev->fwnode == fwnode);
	काष्ठा fwnode_link *link, *पंचांगp;
	काष्ठा fwnode_handle *child = शून्य;
	u32 dl_flags;

	अगर (own_link)
		dl_flags = fw_devlink_get_flags();
	अन्यथा
		dl_flags = FW_DEVLINK_FLAGS_PERMISSIVE;

	list_क्रम_each_entry_safe(link, पंचांगp, &fwnode->suppliers, c_hook) अणु
		पूर्णांक ret;
		काष्ठा device *sup_dev;
		काष्ठा fwnode_handle *sup = link->supplier;

		ret = fw_devlink_create_devlink(dev, sup, dl_flags);
		अगर (!own_link || ret == -EAGAIN)
			जारी;

		list_del(&link->s_hook);
		list_del(&link->c_hook);
		kमुक्त(link);

		/* If no device link was created, nothing more to करो. */
		अगर (ret)
			जारी;

		/*
		 * If a device link was successfully created to a supplier, we
		 * now need to try and link the supplier to all its suppliers.
		 *
		 * This is needed to detect and delete false dependencies in
		 * fwnode links that haven't been converted to a device link
		 * yet. See comments in fw_devlink_create_devlink() क्रम more
		 * details on the false dependency.
		 *
		 * Without deleting these false dependencies, some devices will
		 * never probe because they'll keep रुकोing क्रम their false
		 * dependency fwnode links to be converted to device links.
		 */
		sup_dev = get_dev_from_fwnode(sup);
		__fw_devlink_link_to_suppliers(sup_dev, sup_dev->fwnode);
		put_device(sup_dev);
	पूर्ण

	/*
	 * Make "proxy" SYNC_STATE_ONLY device links to represent the needs of
	 * all the descendants. This proxy link step is needed to handle the
	 * हाल where the supplier is added beक्रमe the consumer's parent device
	 * (@dev).
	 */
	जबतक ((child = fwnode_get_next_available_child_node(fwnode, child)))
		__fw_devlink_link_to_suppliers(dev, child);
पूर्ण

अटल व्योम fw_devlink_link_device(काष्ठा device *dev)
अणु
	काष्ठा fwnode_handle *fwnode = dev->fwnode;

	अगर (!fw_devlink_flags)
		वापस;

	fw_devlink_parse_fwtree(fwnode);

	mutex_lock(&fwnode_link_lock);
	__fw_devlink_link_to_consumers(dev);
	__fw_devlink_link_to_suppliers(dev, fwnode);
	mutex_unlock(&fwnode_link_lock);
पूर्ण

/* Device links support end. */

पूर्णांक (*platक्रमm_notअगरy)(काष्ठा device *dev) = शून्य;
पूर्णांक (*platक्रमm_notअगरy_हटाओ)(काष्ठा device *dev) = शून्य;
अटल काष्ठा kobject *dev_kobj;
काष्ठा kobject *sysfs_dev_अक्षर_kobj;
काष्ठा kobject *sysfs_dev_block_kobj;

अटल DEFINE_MUTEX(device_hotplug_lock);

व्योम lock_device_hotplug(व्योम)
अणु
	mutex_lock(&device_hotplug_lock);
पूर्ण

व्योम unlock_device_hotplug(व्योम)
अणु
	mutex_unlock(&device_hotplug_lock);
पूर्ण

पूर्णांक lock_device_hotplug_sysfs(व्योम)
अणु
	अगर (mutex_trylock(&device_hotplug_lock))
		वापस 0;

	/* Aव्योम busy looping (5 ms of sleep should करो). */
	msleep(5);
	वापस restart_syscall();
पूर्ण

#अगर_घोषित CONFIG_BLOCK
अटल अंतरभूत पूर्णांक device_is_not_partition(काष्ठा device *dev)
अणु
	वापस !(dev->type == &part_type);
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक device_is_not_partition(काष्ठा device *dev)
अणु
	वापस 1;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक
device_platक्रमm_notअगरy(काष्ठा device *dev, क्रमागत kobject_action action)
अणु
	पूर्णांक ret;

	ret = acpi_platक्रमm_notअगरy(dev, action);
	अगर (ret)
		वापस ret;

	ret = software_node_notअगरy(dev, action);
	अगर (ret)
		वापस ret;

	अगर (platक्रमm_notअगरy && action == KOBJ_ADD)
		platक्रमm_notअगरy(dev);
	अन्यथा अगर (platक्रमm_notअगरy_हटाओ && action == KOBJ_REMOVE)
		platक्रमm_notअगरy_हटाओ(dev);
	वापस 0;
पूर्ण

/**
 * dev_driver_string - Return a device's driver name, अगर at all possible
 * @dev: काष्ठा device to get the name of
 *
 * Will वापस the device's driver's name अगर it is bound to a device.  If
 * the device is not bound to a driver, it will वापस the name of the bus
 * it is attached to.  If it is not attached to a bus either, an empty
 * string will be वापसed.
 */
स्थिर अक्षर *dev_driver_string(स्थिर काष्ठा device *dev)
अणु
	काष्ठा device_driver *drv;

	/* dev->driver can change to शून्य underneath us because of unbinding,
	 * so be careful about accessing it.  dev->bus and dev->class should
	 * never change once they are set, so they करोn't need special care.
	 */
	drv = READ_ONCE(dev->driver);
	वापस drv ? drv->name : dev_bus_name(dev);
पूर्ण
EXPORT_SYMBOL(dev_driver_string);

#घोषणा to_dev_attr(_attr) container_of(_attr, काष्ठा device_attribute, attr)

अटल sमाप_प्रकार dev_attr_show(काष्ठा kobject *kobj, काष्ठा attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा device_attribute *dev_attr = to_dev_attr(attr);
	काष्ठा device *dev = kobj_to_dev(kobj);
	sमाप_प्रकार ret = -EIO;

	अगर (dev_attr->show)
		ret = dev_attr->show(dev, dev_attr, buf);
	अगर (ret >= (sमाप_प्रकार)PAGE_SIZE) अणु
		prपूर्णांकk("dev_attr_show: %pS returned bad count\n",
				dev_attr->show);
	पूर्ण
	वापस ret;
पूर्ण

अटल sमाप_प्रकार dev_attr_store(काष्ठा kobject *kobj, काष्ठा attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा device_attribute *dev_attr = to_dev_attr(attr);
	काष्ठा device *dev = kobj_to_dev(kobj);
	sमाप_प्रकार ret = -EIO;

	अगर (dev_attr->store)
		ret = dev_attr->store(dev, dev_attr, buf, count);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा sysfs_ops dev_sysfs_ops = अणु
	.show	= dev_attr_show,
	.store	= dev_attr_store,
पूर्ण;

#घोषणा to_ext_attr(x) container_of(x, काष्ठा dev_ext_attribute, attr)

sमाप_प्रकार device_store_uदीर्घ(काष्ठा device *dev,
			   काष्ठा device_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा dev_ext_attribute *ea = to_ext_attr(attr);
	पूर्णांक ret;
	अचिन्हित दीर्घ new;

	ret = kम_से_अदीर्घ(buf, 0, &new);
	अगर (ret)
		वापस ret;
	*(अचिन्हित दीर्घ *)(ea->var) = new;
	/* Always वापस full ग_लिखो size even अगर we didn't consume all */
	वापस size;
पूर्ण
EXPORT_SYMBOL_GPL(device_store_uदीर्घ);

sमाप_प्रकार device_show_uदीर्घ(काष्ठा device *dev,
			  काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	काष्ठा dev_ext_attribute *ea = to_ext_attr(attr);
	वापस sysfs_emit(buf, "%lx\n", *(अचिन्हित दीर्घ *)(ea->var));
पूर्ण
EXPORT_SYMBOL_GPL(device_show_uदीर्घ);

sमाप_प्रकार device_store_पूर्णांक(काष्ठा device *dev,
			 काष्ठा device_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा dev_ext_attribute *ea = to_ext_attr(attr);
	पूर्णांक ret;
	दीर्घ new;

	ret = kम_से_दीर्घ(buf, 0, &new);
	अगर (ret)
		वापस ret;

	अगर (new > पूर्णांक_उच्च || new < पूर्णांक_न्यून)
		वापस -EINVAL;
	*(पूर्णांक *)(ea->var) = new;
	/* Always वापस full ग_लिखो size even अगर we didn't consume all */
	वापस size;
पूर्ण
EXPORT_SYMBOL_GPL(device_store_पूर्णांक);

sमाप_प्रकार device_show_पूर्णांक(काष्ठा device *dev,
			काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	काष्ठा dev_ext_attribute *ea = to_ext_attr(attr);

	वापस sysfs_emit(buf, "%d\n", *(पूर्णांक *)(ea->var));
पूर्ण
EXPORT_SYMBOL_GPL(device_show_पूर्णांक);

sमाप_प्रकार device_store_bool(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा dev_ext_attribute *ea = to_ext_attr(attr);

	अगर (strtobool(buf, ea->var) < 0)
		वापस -EINVAL;

	वापस size;
पूर्ण
EXPORT_SYMBOL_GPL(device_store_bool);

sमाप_प्रकार device_show_bool(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा dev_ext_attribute *ea = to_ext_attr(attr);

	वापस sysfs_emit(buf, "%d\n", *(bool *)(ea->var));
पूर्ण
EXPORT_SYMBOL_GPL(device_show_bool);

/**
 * device_release - मुक्त device काष्ठाure.
 * @kobj: device's kobject.
 *
 * This is called once the reference count क्रम the object
 * reaches 0. We क्रमward the call to the device's release
 * method, which should handle actually मुक्तing the काष्ठाure.
 */
अटल व्योम device_release(काष्ठा kobject *kobj)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा device_निजी *p = dev->p;

	/*
	 * Some platक्रमm devices are driven without driver attached
	 * and managed resources may have been acquired.  Make sure
	 * all resources are released.
	 *
	 * Drivers still can add resources पूर्णांकo device after device
	 * is deleted but alive, so release devres here to aव्योम
	 * possible memory leak.
	 */
	devres_release_all(dev);

	kमुक्त(dev->dma_range_map);

	अगर (dev->release)
		dev->release(dev);
	अन्यथा अगर (dev->type && dev->type->release)
		dev->type->release(dev);
	अन्यथा अगर (dev->class && dev->class->dev_release)
		dev->class->dev_release(dev);
	अन्यथा
		WARN(1, KERN_ERR "Device '%s' does not have a release() function, it is broken and must be fixed. See Documentation/core-api/kobject.rst.\n",
			dev_name(dev));
	kमुक्त(p);
पूर्ण

अटल स्थिर व्योम *device_namespace(काष्ठा kobject *kobj)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	स्थिर व्योम *ns = शून्य;

	अगर (dev->class && dev->class->ns_type)
		ns = dev->class->namespace(dev);

	वापस ns;
पूर्ण

अटल व्योम device_get_ownership(काष्ठा kobject *kobj, kuid_t *uid, kgid_t *gid)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);

	अगर (dev->class && dev->class->get_ownership)
		dev->class->get_ownership(dev, uid, gid);
पूर्ण

अटल काष्ठा kobj_type device_ktype = अणु
	.release	= device_release,
	.sysfs_ops	= &dev_sysfs_ops,
	.namespace	= device_namespace,
	.get_ownership	= device_get_ownership,
पूर्ण;


अटल पूर्णांक dev_uevent_filter(काष्ठा kset *kset, काष्ठा kobject *kobj)
अणु
	काष्ठा kobj_type *ktype = get_ktype(kobj);

	अगर (ktype == &device_ktype) अणु
		काष्ठा device *dev = kobj_to_dev(kobj);
		अगर (dev->bus)
			वापस 1;
		अगर (dev->class)
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर अक्षर *dev_uevent_name(काष्ठा kset *kset, काष्ठा kobject *kobj)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);

	अगर (dev->bus)
		वापस dev->bus->name;
	अगर (dev->class)
		वापस dev->class->name;
	वापस शून्य;
पूर्ण

अटल पूर्णांक dev_uevent(काष्ठा kset *kset, काष्ठा kobject *kobj,
		      काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	पूर्णांक retval = 0;

	/* add device node properties अगर present */
	अगर (MAJOR(dev->devt)) अणु
		स्थिर अक्षर *पंचांगp;
		स्थिर अक्षर *name;
		umode_t mode = 0;
		kuid_t uid = GLOBAL_ROOT_UID;
		kgid_t gid = GLOBAL_ROOT_GID;

		add_uevent_var(env, "MAJOR=%u", MAJOR(dev->devt));
		add_uevent_var(env, "MINOR=%u", MINOR(dev->devt));
		name = device_get_devnode(dev, &mode, &uid, &gid, &पंचांगp);
		अगर (name) अणु
			add_uevent_var(env, "DEVNAME=%s", name);
			अगर (mode)
				add_uevent_var(env, "DEVMODE=%#o", mode & 0777);
			अगर (!uid_eq(uid, GLOBAL_ROOT_UID))
				add_uevent_var(env, "DEVUID=%u", from_kuid(&init_user_ns, uid));
			अगर (!gid_eq(gid, GLOBAL_ROOT_GID))
				add_uevent_var(env, "DEVGID=%u", from_kgid(&init_user_ns, gid));
			kमुक्त(पंचांगp);
		पूर्ण
	पूर्ण

	अगर (dev->type && dev->type->name)
		add_uevent_var(env, "DEVTYPE=%s", dev->type->name);

	अगर (dev->driver)
		add_uevent_var(env, "DRIVER=%s", dev->driver->name);

	/* Add common DT inक्रमmation about the device */
	of_device_uevent(dev, env);

	/* have the bus specअगरic function add its stuff */
	अगर (dev->bus && dev->bus->uevent) अणु
		retval = dev->bus->uevent(dev, env);
		अगर (retval)
			pr_debug("device: '%s': %s: bus uevent() returned %d\n",
				 dev_name(dev), __func__, retval);
	पूर्ण

	/* have the class specअगरic function add its stuff */
	अगर (dev->class && dev->class->dev_uevent) अणु
		retval = dev->class->dev_uevent(dev, env);
		अगर (retval)
			pr_debug("device: '%s': %s: class uevent() "
				 "returned %d\n", dev_name(dev),
				 __func__, retval);
	पूर्ण

	/* have the device type specअगरic function add its stuff */
	अगर (dev->type && dev->type->uevent) अणु
		retval = dev->type->uevent(dev, env);
		अगर (retval)
			pr_debug("device: '%s': %s: dev_type uevent() "
				 "returned %d\n", dev_name(dev),
				 __func__, retval);
	पूर्ण

	वापस retval;
पूर्ण

अटल स्थिर काष्ठा kset_uevent_ops device_uevent_ops = अणु
	.filter =	dev_uevent_filter,
	.name =		dev_uevent_name,
	.uevent =	dev_uevent,
पूर्ण;

अटल sमाप_प्रकार uevent_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा kobject *top_kobj;
	काष्ठा kset *kset;
	काष्ठा kobj_uevent_env *env = शून्य;
	पूर्णांक i;
	पूर्णांक len = 0;
	पूर्णांक retval;

	/* search the kset, the device beदीर्घs to */
	top_kobj = &dev->kobj;
	जबतक (!top_kobj->kset && top_kobj->parent)
		top_kobj = top_kobj->parent;
	अगर (!top_kobj->kset)
		जाओ out;

	kset = top_kobj->kset;
	अगर (!kset->uevent_ops || !kset->uevent_ops->uevent)
		जाओ out;

	/* respect filter */
	अगर (kset->uevent_ops && kset->uevent_ops->filter)
		अगर (!kset->uevent_ops->filter(kset, &dev->kobj))
			जाओ out;

	env = kzalloc(माप(काष्ठा kobj_uevent_env), GFP_KERNEL);
	अगर (!env)
		वापस -ENOMEM;

	/* let the kset specअगरic function add its keys */
	retval = kset->uevent_ops->uevent(kset, &dev->kobj, env);
	अगर (retval)
		जाओ out;

	/* copy keys to file */
	क्रम (i = 0; i < env->envp_idx; i++)
		len += sysfs_emit_at(buf, len, "%s\n", env->envp[i]);
out:
	kमुक्त(env);
	वापस len;
पूर्ण

अटल sमाप_प्रकार uevent_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक rc;

	rc = kobject_synth_uevent(&dev->kobj, buf, count);

	अगर (rc) अणु
		dev_err(dev, "uevent: failed to send synthetic uevent\n");
		वापस rc;
	पूर्ण

	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(uevent);

अटल sमाप_प्रकार online_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	bool val;

	device_lock(dev);
	val = !dev->offline;
	device_unlock(dev);
	वापस sysfs_emit(buf, "%u\n", val);
पूर्ण

अटल sमाप_प्रकार online_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	bool val;
	पूर्णांक ret;

	ret = strtobool(buf, &val);
	अगर (ret < 0)
		वापस ret;

	ret = lock_device_hotplug_sysfs();
	अगर (ret)
		वापस ret;

	ret = val ? device_online(dev) : device_offline(dev);
	unlock_device_hotplug();
	वापस ret < 0 ? ret : count;
पूर्ण
अटल DEVICE_ATTR_RW(online);

पूर्णांक device_add_groups(काष्ठा device *dev, स्थिर काष्ठा attribute_group **groups)
अणु
	वापस sysfs_create_groups(&dev->kobj, groups);
पूर्ण
EXPORT_SYMBOL_GPL(device_add_groups);

व्योम device_हटाओ_groups(काष्ठा device *dev,
			  स्थिर काष्ठा attribute_group **groups)
अणु
	sysfs_हटाओ_groups(&dev->kobj, groups);
पूर्ण
EXPORT_SYMBOL_GPL(device_हटाओ_groups);

जोड़ device_attr_group_devres अणु
	स्थिर काष्ठा attribute_group *group;
	स्थिर काष्ठा attribute_group **groups;
पूर्ण;

अटल पूर्णांक devm_attr_group_match(काष्ठा device *dev, व्योम *res, व्योम *data)
अणु
	वापस ((जोड़ device_attr_group_devres *)res)->group == data;
पूर्ण

अटल व्योम devm_attr_group_हटाओ(काष्ठा device *dev, व्योम *res)
अणु
	जोड़ device_attr_group_devres *devres = res;
	स्थिर काष्ठा attribute_group *group = devres->group;

	dev_dbg(dev, "%s: removing group %p\n", __func__, group);
	sysfs_हटाओ_group(&dev->kobj, group);
पूर्ण

अटल व्योम devm_attr_groups_हटाओ(काष्ठा device *dev, व्योम *res)
अणु
	जोड़ device_attr_group_devres *devres = res;
	स्थिर काष्ठा attribute_group **groups = devres->groups;

	dev_dbg(dev, "%s: removing groups %p\n", __func__, groups);
	sysfs_हटाओ_groups(&dev->kobj, groups);
पूर्ण

/**
 * devm_device_add_group - given a device, create a managed attribute group
 * @dev:	The device to create the group क्रम
 * @grp:	The attribute group to create
 *
 * This function creates a group क्रम the first समय.  It will explicitly
 * warn and error अगर any of the attribute files being created alपढ़ोy exist.
 *
 * Returns 0 on success or error code on failure.
 */
पूर्णांक devm_device_add_group(काष्ठा device *dev, स्थिर काष्ठा attribute_group *grp)
अणु
	जोड़ device_attr_group_devres *devres;
	पूर्णांक error;

	devres = devres_alloc(devm_attr_group_हटाओ,
			      माप(*devres), GFP_KERNEL);
	अगर (!devres)
		वापस -ENOMEM;

	error = sysfs_create_group(&dev->kobj, grp);
	अगर (error) अणु
		devres_मुक्त(devres);
		वापस error;
	पूर्ण

	devres->group = grp;
	devres_add(dev, devres);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(devm_device_add_group);

/**
 * devm_device_हटाओ_group: हटाओ a managed group from a device
 * @dev:	device to हटाओ the group from
 * @grp:	group to हटाओ
 *
 * This function हटाओs a group of attributes from a device. The attributes
 * previously have to have been created क्रम this group, otherwise it will fail.
 */
व्योम devm_device_हटाओ_group(काष्ठा device *dev,
			      स्थिर काष्ठा attribute_group *grp)
अणु
	WARN_ON(devres_release(dev, devm_attr_group_हटाओ,
			       devm_attr_group_match,
			       /* cast away स्थिर */ (व्योम *)grp));
पूर्ण
EXPORT_SYMBOL_GPL(devm_device_हटाओ_group);

/**
 * devm_device_add_groups - create a bunch of managed attribute groups
 * @dev:	The device to create the group क्रम
 * @groups:	The attribute groups to create, शून्य terminated
 *
 * This function creates a bunch of managed attribute groups.  If an error
 * occurs when creating a group, all previously created groups will be
 * हटाओd, unwinding everything back to the original state when this
 * function was called.  It will explicitly warn and error अगर any of the
 * attribute files being created alपढ़ोy exist.
 *
 * Returns 0 on success or error code from sysfs_create_group on failure.
 */
पूर्णांक devm_device_add_groups(काष्ठा device *dev,
			   स्थिर काष्ठा attribute_group **groups)
अणु
	जोड़ device_attr_group_devres *devres;
	पूर्णांक error;

	devres = devres_alloc(devm_attr_groups_हटाओ,
			      माप(*devres), GFP_KERNEL);
	अगर (!devres)
		वापस -ENOMEM;

	error = sysfs_create_groups(&dev->kobj, groups);
	अगर (error) अणु
		devres_मुक्त(devres);
		वापस error;
	पूर्ण

	devres->groups = groups;
	devres_add(dev, devres);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(devm_device_add_groups);

/**
 * devm_device_हटाओ_groups - हटाओ a list of managed groups
 *
 * @dev:	The device क्रम the groups to be हटाओd from
 * @groups:	शून्य terminated list of groups to be हटाओd
 *
 * If groups is not शून्य, हटाओ the specअगरied groups from the device.
 */
व्योम devm_device_हटाओ_groups(काष्ठा device *dev,
			       स्थिर काष्ठा attribute_group **groups)
अणु
	WARN_ON(devres_release(dev, devm_attr_groups_हटाओ,
			       devm_attr_group_match,
			       /* cast away स्थिर */ (व्योम *)groups));
पूर्ण
EXPORT_SYMBOL_GPL(devm_device_हटाओ_groups);

अटल पूर्णांक device_add_attrs(काष्ठा device *dev)
अणु
	काष्ठा class *class = dev->class;
	स्थिर काष्ठा device_type *type = dev->type;
	पूर्णांक error;

	अगर (class) अणु
		error = device_add_groups(dev, class->dev_groups);
		अगर (error)
			वापस error;
	पूर्ण

	अगर (type) अणु
		error = device_add_groups(dev, type->groups);
		अगर (error)
			जाओ err_हटाओ_class_groups;
	पूर्ण

	error = device_add_groups(dev, dev->groups);
	अगर (error)
		जाओ err_हटाओ_type_groups;

	अगर (device_supports_offline(dev) && !dev->offline_disabled) अणु
		error = device_create_file(dev, &dev_attr_online);
		अगर (error)
			जाओ err_हटाओ_dev_groups;
	पूर्ण

	अगर (fw_devlink_flags && !fw_devlink_is_permissive() && dev->fwnode) अणु
		error = device_create_file(dev, &dev_attr_रुकोing_क्रम_supplier);
		अगर (error)
			जाओ err_हटाओ_dev_online;
	पूर्ण

	वापस 0;

 err_हटाओ_dev_online:
	device_हटाओ_file(dev, &dev_attr_online);
 err_हटाओ_dev_groups:
	device_हटाओ_groups(dev, dev->groups);
 err_हटाओ_type_groups:
	अगर (type)
		device_हटाओ_groups(dev, type->groups);
 err_हटाओ_class_groups:
	अगर (class)
		device_हटाओ_groups(dev, class->dev_groups);

	वापस error;
पूर्ण

अटल व्योम device_हटाओ_attrs(काष्ठा device *dev)
अणु
	काष्ठा class *class = dev->class;
	स्थिर काष्ठा device_type *type = dev->type;

	device_हटाओ_file(dev, &dev_attr_रुकोing_क्रम_supplier);
	device_हटाओ_file(dev, &dev_attr_online);
	device_हटाओ_groups(dev, dev->groups);

	अगर (type)
		device_हटाओ_groups(dev, type->groups);

	अगर (class)
		device_हटाओ_groups(dev, class->dev_groups);
पूर्ण

अटल sमाप_प्रकार dev_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	वापस prपूर्णांक_dev_t(buf, dev->devt);
पूर्ण
अटल DEVICE_ATTR_RO(dev);

/* /sys/devices/ */
काष्ठा kset *devices_kset;

/**
 * devices_kset_move_beक्रमe - Move device in the devices_kset's list.
 * @deva: Device to move.
 * @devb: Device @deva should come beक्रमe.
 */
अटल व्योम devices_kset_move_beक्रमe(काष्ठा device *deva, काष्ठा device *devb)
अणु
	अगर (!devices_kset)
		वापस;
	pr_debug("devices_kset: Moving %s before %s\n",
		 dev_name(deva), dev_name(devb));
	spin_lock(&devices_kset->list_lock);
	list_move_tail(&deva->kobj.entry, &devb->kobj.entry);
	spin_unlock(&devices_kset->list_lock);
पूर्ण

/**
 * devices_kset_move_after - Move device in the devices_kset's list.
 * @deva: Device to move
 * @devb: Device @deva should come after.
 */
अटल व्योम devices_kset_move_after(काष्ठा device *deva, काष्ठा device *devb)
अणु
	अगर (!devices_kset)
		वापस;
	pr_debug("devices_kset: Moving %s after %s\n",
		 dev_name(deva), dev_name(devb));
	spin_lock(&devices_kset->list_lock);
	list_move(&deva->kobj.entry, &devb->kobj.entry);
	spin_unlock(&devices_kset->list_lock);
पूर्ण

/**
 * devices_kset_move_last - move the device to the end of devices_kset's list.
 * @dev: device to move
 */
व्योम devices_kset_move_last(काष्ठा device *dev)
अणु
	अगर (!devices_kset)
		वापस;
	pr_debug("devices_kset: Moving %s to end of list\n", dev_name(dev));
	spin_lock(&devices_kset->list_lock);
	list_move_tail(&dev->kobj.entry, &devices_kset->list);
	spin_unlock(&devices_kset->list_lock);
पूर्ण

/**
 * device_create_file - create sysfs attribute file क्रम device.
 * @dev: device.
 * @attr: device attribute descriptor.
 */
पूर्णांक device_create_file(काष्ठा device *dev,
		       स्थिर काष्ठा device_attribute *attr)
अणु
	पूर्णांक error = 0;

	अगर (dev) अणु
		WARN(((attr->attr.mode & S_IWUGO) && !attr->store),
			"Attribute %s: write permission without 'store'\n",
			attr->attr.name);
		WARN(((attr->attr.mode & S_IRUGO) && !attr->show),
			"Attribute %s: read permission without 'show'\n",
			attr->attr.name);
		error = sysfs_create_file(&dev->kobj, &attr->attr);
	पूर्ण

	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(device_create_file);

/**
 * device_हटाओ_file - हटाओ sysfs attribute file.
 * @dev: device.
 * @attr: device attribute descriptor.
 */
व्योम device_हटाओ_file(काष्ठा device *dev,
			स्थिर काष्ठा device_attribute *attr)
अणु
	अगर (dev)
		sysfs_हटाओ_file(&dev->kobj, &attr->attr);
पूर्ण
EXPORT_SYMBOL_GPL(device_हटाओ_file);

/**
 * device_हटाओ_file_self - हटाओ sysfs attribute file from its own method.
 * @dev: device.
 * @attr: device attribute descriptor.
 *
 * See kernfs_हटाओ_self() क्रम details.
 */
bool device_हटाओ_file_self(काष्ठा device *dev,
			     स्थिर काष्ठा device_attribute *attr)
अणु
	अगर (dev)
		वापस sysfs_हटाओ_file_self(&dev->kobj, &attr->attr);
	अन्यथा
		वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(device_हटाओ_file_self);

/**
 * device_create_bin_file - create sysfs binary attribute file क्रम device.
 * @dev: device.
 * @attr: device binary attribute descriptor.
 */
पूर्णांक device_create_bin_file(काष्ठा device *dev,
			   स्थिर काष्ठा bin_attribute *attr)
अणु
	पूर्णांक error = -EINVAL;
	अगर (dev)
		error = sysfs_create_bin_file(&dev->kobj, attr);
	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(device_create_bin_file);

/**
 * device_हटाओ_bin_file - हटाओ sysfs binary attribute file
 * @dev: device.
 * @attr: device binary attribute descriptor.
 */
व्योम device_हटाओ_bin_file(काष्ठा device *dev,
			    स्थिर काष्ठा bin_attribute *attr)
अणु
	अगर (dev)
		sysfs_हटाओ_bin_file(&dev->kobj, attr);
पूर्ण
EXPORT_SYMBOL_GPL(device_हटाओ_bin_file);

अटल व्योम klist_children_get(काष्ठा klist_node *n)
अणु
	काष्ठा device_निजी *p = to_device_निजी_parent(n);
	काष्ठा device *dev = p->device;

	get_device(dev);
पूर्ण

अटल व्योम klist_children_put(काष्ठा klist_node *n)
अणु
	काष्ठा device_निजी *p = to_device_निजी_parent(n);
	काष्ठा device *dev = p->device;

	put_device(dev);
पूर्ण

/**
 * device_initialize - init device काष्ठाure.
 * @dev: device.
 *
 * This prepares the device क्रम use by other layers by initializing
 * its fields.
 * It is the first half of device_रेजिस्टर(), अगर called by
 * that function, though it can also be called separately, so one
 * may use @dev's fields. In particular, get_device()/put_device()
 * may be used क्रम reference counting of @dev after calling this
 * function.
 *
 * All fields in @dev must be initialized by the caller to 0, except
 * क्रम those explicitly set to some other value.  The simplest
 * approach is to use kzalloc() to allocate the काष्ठाure containing
 * @dev.
 *
 * NOTE: Use put_device() to give up your reference instead of मुक्तing
 * @dev directly once you have called this function.
 */
व्योम device_initialize(काष्ठा device *dev)
अणु
	dev->kobj.kset = devices_kset;
	kobject_init(&dev->kobj, &device_ktype);
	INIT_LIST_HEAD(&dev->dma_pools);
	mutex_init(&dev->mutex);
#अगर_घोषित CONFIG_PROVE_LOCKING
	mutex_init(&dev->lockdep_mutex);
#पूर्ण_अगर
	lockdep_set_novalidate_class(&dev->mutex);
	spin_lock_init(&dev->devres_lock);
	INIT_LIST_HEAD(&dev->devres_head);
	device_pm_init(dev);
	set_dev_node(dev, -1);
#अगर_घोषित CONFIG_GENERIC_MSI_IRQ
	INIT_LIST_HEAD(&dev->msi_list);
#पूर्ण_अगर
	INIT_LIST_HEAD(&dev->links.consumers);
	INIT_LIST_HEAD(&dev->links.suppliers);
	INIT_LIST_HEAD(&dev->links.defer_sync);
	dev->links.status = DL_DEV_NO_DRIVER;
#अगर defined(CONFIG_ARCH_HAS_SYNC_DMA_FOR_DEVICE) || \
    defined(CONFIG_ARCH_HAS_SYNC_DMA_FOR_CPU) || \
    defined(CONFIG_ARCH_HAS_SYNC_DMA_FOR_CPU_ALL)
	dev->dma_coherent = dma_शेष_coherent;
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL_GPL(device_initialize);

काष्ठा kobject *भव_device_parent(काष्ठा device *dev)
अणु
	अटल काष्ठा kobject *भव_dir = शून्य;

	अगर (!भव_dir)
		भव_dir = kobject_create_and_add("virtual",
						     &devices_kset->kobj);

	वापस भव_dir;
पूर्ण

काष्ठा class_dir अणु
	काष्ठा kobject kobj;
	काष्ठा class *class;
पूर्ण;

#घोषणा to_class_dir(obj) container_of(obj, काष्ठा class_dir, kobj)

अटल व्योम class_dir_release(काष्ठा kobject *kobj)
अणु
	काष्ठा class_dir *dir = to_class_dir(kobj);
	kमुक्त(dir);
पूर्ण

अटल स्थिर
काष्ठा kobj_ns_type_operations *class_dir_child_ns_type(काष्ठा kobject *kobj)
अणु
	काष्ठा class_dir *dir = to_class_dir(kobj);
	वापस dir->class->ns_type;
पूर्ण

अटल काष्ठा kobj_type class_dir_ktype = अणु
	.release	= class_dir_release,
	.sysfs_ops	= &kobj_sysfs_ops,
	.child_ns_type	= class_dir_child_ns_type
पूर्ण;

अटल काष्ठा kobject *
class_dir_create_and_add(काष्ठा class *class, काष्ठा kobject *parent_kobj)
अणु
	काष्ठा class_dir *dir;
	पूर्णांक retval;

	dir = kzalloc(माप(*dir), GFP_KERNEL);
	अगर (!dir)
		वापस ERR_PTR(-ENOMEM);

	dir->class = class;
	kobject_init(&dir->kobj, &class_dir_ktype);

	dir->kobj.kset = &class->p->glue_dirs;

	retval = kobject_add(&dir->kobj, parent_kobj, "%s", class->name);
	अगर (retval < 0) अणु
		kobject_put(&dir->kobj);
		वापस ERR_PTR(retval);
	पूर्ण
	वापस &dir->kobj;
पूर्ण

अटल DEFINE_MUTEX(gdp_mutex);

अटल काष्ठा kobject *get_device_parent(काष्ठा device *dev,
					 काष्ठा device *parent)
अणु
	अगर (dev->class) अणु
		काष्ठा kobject *kobj = शून्य;
		काष्ठा kobject *parent_kobj;
		काष्ठा kobject *k;

#अगर_घोषित CONFIG_BLOCK
		/* block disks show up in /sys/block */
		अगर (sysfs_deprecated && dev->class == &block_class) अणु
			अगर (parent && parent->class == &block_class)
				वापस &parent->kobj;
			वापस &block_class.p->subsys.kobj;
		पूर्ण
#पूर्ण_अगर

		/*
		 * If we have no parent, we live in "virtual".
		 * Class-devices with a non class-device as parent, live
		 * in a "glue" directory to prevent namespace collisions.
		 */
		अगर (parent == शून्य)
			parent_kobj = भव_device_parent(dev);
		अन्यथा अगर (parent->class && !dev->class->ns_type)
			वापस &parent->kobj;
		अन्यथा
			parent_kobj = &parent->kobj;

		mutex_lock(&gdp_mutex);

		/* find our class-directory at the parent and reference it */
		spin_lock(&dev->class->p->glue_dirs.list_lock);
		list_क्रम_each_entry(k, &dev->class->p->glue_dirs.list, entry)
			अगर (k->parent == parent_kobj) अणु
				kobj = kobject_get(k);
				अवरोध;
			पूर्ण
		spin_unlock(&dev->class->p->glue_dirs.list_lock);
		अगर (kobj) अणु
			mutex_unlock(&gdp_mutex);
			वापस kobj;
		पूर्ण

		/* or create a new class-directory at the parent device */
		k = class_dir_create_and_add(dev->class, parent_kobj);
		/* करो not emit an uevent क्रम this simple "glue" directory */
		mutex_unlock(&gdp_mutex);
		वापस k;
	पूर्ण

	/* subप्रणालीs can specअगरy a शेष root directory क्रम their devices */
	अगर (!parent && dev->bus && dev->bus->dev_root)
		वापस &dev->bus->dev_root->kobj;

	अगर (parent)
		वापस &parent->kobj;
	वापस शून्य;
पूर्ण

अटल अंतरभूत bool live_in_glue_dir(काष्ठा kobject *kobj,
				    काष्ठा device *dev)
अणु
	अगर (!kobj || !dev->class ||
	    kobj->kset != &dev->class->p->glue_dirs)
		वापस false;
	वापस true;
पूर्ण

अटल अंतरभूत काष्ठा kobject *get_glue_dir(काष्ठा device *dev)
अणु
	वापस dev->kobj.parent;
पूर्ण

/*
 * make sure cleaning up dir as the last step, we need to make
 * sure .release handler of kobject is run with holding the
 * global lock
 */
अटल व्योम cleanup_glue_dir(काष्ठा device *dev, काष्ठा kobject *glue_dir)
अणु
	अचिन्हित पूर्णांक ref;

	/* see अगर we live in a "glue" directory */
	अगर (!live_in_glue_dir(glue_dir, dev))
		वापस;

	mutex_lock(&gdp_mutex);
	/**
	 * There is a race condition between removing glue directory
	 * and adding a new device under the glue directory.
	 *
	 * CPU1:                                         CPU2:
	 *
	 * device_add()
	 *   get_device_parent()
	 *     class_dir_create_and_add()
	 *       kobject_add_पूर्णांकernal()
	 *         create_dir()    // create glue_dir
	 *
	 *                                               device_add()
	 *                                                 get_device_parent()
	 *                                                   kobject_get() // get glue_dir
	 *
	 * device_del()
	 *   cleanup_glue_dir()
	 *     kobject_del(glue_dir)
	 *
	 *                                               kobject_add()
	 *                                                 kobject_add_पूर्णांकernal()
	 *                                                   create_dir() // in glue_dir
	 *                                                     sysfs_create_dir_ns()
	 *                                                       kernfs_create_dir_ns(sd)
	 *
	 *       sysfs_हटाओ_dir() // glue_dir->sd=शून्य
	 *       sysfs_put()        // मुक्त glue_dir->sd
	 *
	 *                                                         // sd is मुक्तd
	 *                                                         kernfs_new_node(sd)
	 *                                                           kernfs_get(glue_dir)
	 *                                                           kernfs_add_one()
	 *                                                           kernfs_put()
	 *
	 * Beक्रमe CPU1 हटाओ last child device under glue dir, अगर CPU2 add
	 * a new device under glue dir, the glue_dir kobject reference count
	 * will be increase to 2 in kobject_get(k). And CPU2 has been called
	 * kernfs_create_dir_ns(). Meanजबतक, CPU1 call sysfs_हटाओ_dir()
	 * and sysfs_put(). This result in glue_dir->sd is मुक्तd.
	 *
	 * Then the CPU2 will see a stale "empty" but still potentially used
	 * glue dir around in kernfs_new_node().
	 *
	 * In order to aव्योम this happening, we also should make sure that
	 * kernfs_node क्रम glue_dir is released in CPU1 only when refcount
	 * क्रम glue_dir kobj is 1.
	 */
	ref = kref_पढ़ो(&glue_dir->kref);
	अगर (!kobject_has_children(glue_dir) && !--ref)
		kobject_del(glue_dir);
	kobject_put(glue_dir);
	mutex_unlock(&gdp_mutex);
पूर्ण

अटल पूर्णांक device_add_class_symlinks(काष्ठा device *dev)
अणु
	काष्ठा device_node *of_node = dev_of_node(dev);
	पूर्णांक error;

	अगर (of_node) अणु
		error = sysfs_create_link(&dev->kobj, of_node_kobj(of_node), "of_node");
		अगर (error)
			dev_warn(dev, "Error %d creating of_node link\n",error);
		/* An error here करोesn't warrant bringing करोwn the device */
	पूर्ण

	अगर (!dev->class)
		वापस 0;

	error = sysfs_create_link(&dev->kobj,
				  &dev->class->p->subsys.kobj,
				  "subsystem");
	अगर (error)
		जाओ out_devnode;

	अगर (dev->parent && device_is_not_partition(dev)) अणु
		error = sysfs_create_link(&dev->kobj, &dev->parent->kobj,
					  "device");
		अगर (error)
			जाओ out_subsys;
	पूर्ण

#अगर_घोषित CONFIG_BLOCK
	/* /sys/block has directories and करोes not need symlinks */
	अगर (sysfs_deprecated && dev->class == &block_class)
		वापस 0;
#पूर्ण_अगर

	/* link in the class directory poपूर्णांकing to the device */
	error = sysfs_create_link(&dev->class->p->subsys.kobj,
				  &dev->kobj, dev_name(dev));
	अगर (error)
		जाओ out_device;

	वापस 0;

out_device:
	sysfs_हटाओ_link(&dev->kobj, "device");

out_subsys:
	sysfs_हटाओ_link(&dev->kobj, "subsystem");
out_devnode:
	sysfs_हटाओ_link(&dev->kobj, "of_node");
	वापस error;
पूर्ण

अटल व्योम device_हटाओ_class_symlinks(काष्ठा device *dev)
अणु
	अगर (dev_of_node(dev))
		sysfs_हटाओ_link(&dev->kobj, "of_node");

	अगर (!dev->class)
		वापस;

	अगर (dev->parent && device_is_not_partition(dev))
		sysfs_हटाओ_link(&dev->kobj, "device");
	sysfs_हटाओ_link(&dev->kobj, "subsystem");
#अगर_घोषित CONFIG_BLOCK
	अगर (sysfs_deprecated && dev->class == &block_class)
		वापस;
#पूर्ण_अगर
	sysfs_delete_link(&dev->class->p->subsys.kobj, &dev->kobj, dev_name(dev));
पूर्ण

/**
 * dev_set_name - set a device name
 * @dev: device
 * @fmt: क्रमmat string क्रम the device's name
 */
पूर्णांक dev_set_name(काष्ठा device *dev, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची vargs;
	पूर्णांक err;

	बहु_शुरू(vargs, fmt);
	err = kobject_set_name_vargs(&dev->kobj, fmt, vargs);
	बहु_पूर्ण(vargs);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(dev_set_name);

/**
 * device_to_dev_kobj - select a /sys/dev/ directory क्रम the device
 * @dev: device
 *
 * By शेष we select अक्षर/ क्रम new entries.  Setting class->dev_obj
 * to शून्य prevents an entry from being created.  class->dev_kobj must
 * be set (or cleared) beक्रमe any devices are रेजिस्टरed to the class
 * otherwise device_create_sys_dev_entry() and
 * device_हटाओ_sys_dev_entry() will disagree about the presence of
 * the link.
 */
अटल काष्ठा kobject *device_to_dev_kobj(काष्ठा device *dev)
अणु
	काष्ठा kobject *kobj;

	अगर (dev->class)
		kobj = dev->class->dev_kobj;
	अन्यथा
		kobj = sysfs_dev_अक्षर_kobj;

	वापस kobj;
पूर्ण

अटल पूर्णांक device_create_sys_dev_entry(काष्ठा device *dev)
अणु
	काष्ठा kobject *kobj = device_to_dev_kobj(dev);
	पूर्णांक error = 0;
	अक्षर devt_str[15];

	अगर (kobj) अणु
		क्रमmat_dev_t(devt_str, dev->devt);
		error = sysfs_create_link(kobj, &dev->kobj, devt_str);
	पूर्ण

	वापस error;
पूर्ण

अटल व्योम device_हटाओ_sys_dev_entry(काष्ठा device *dev)
अणु
	काष्ठा kobject *kobj = device_to_dev_kobj(dev);
	अक्षर devt_str[15];

	अगर (kobj) अणु
		क्रमmat_dev_t(devt_str, dev->devt);
		sysfs_हटाओ_link(kobj, devt_str);
	पूर्ण
पूर्ण

अटल पूर्णांक device_निजी_init(काष्ठा device *dev)
अणु
	dev->p = kzalloc(माप(*dev->p), GFP_KERNEL);
	अगर (!dev->p)
		वापस -ENOMEM;
	dev->p->device = dev;
	klist_init(&dev->p->klist_children, klist_children_get,
		   klist_children_put);
	INIT_LIST_HEAD(&dev->p->deferred_probe);
	वापस 0;
पूर्ण

/**
 * device_add - add device to device hierarchy.
 * @dev: device.
 *
 * This is part 2 of device_रेजिस्टर(), though may be called
 * separately _अगरf_ device_initialize() has been called separately.
 *
 * This adds @dev to the kobject hierarchy via kobject_add(), adds it
 * to the global and sibling lists क्रम the device, then
 * adds it to the other relevant subप्रणालीs of the driver model.
 *
 * Do not call this routine or device_रेजिस्टर() more than once क्रम
 * any device काष्ठाure.  The driver model core is not deचिन्हित to work
 * with devices that get unरेजिस्टरed and then spring back to lअगरe.
 * (Among other things, it's very hard to guarantee that all references
 * to the previous incarnation of @dev have been dropped.)  Allocate
 * and रेजिस्टर a fresh new काष्ठा device instead.
 *
 * NOTE: _Never_ directly मुक्त @dev after calling this function, even
 * अगर it वापसed an error! Always use put_device() to give up your
 * reference instead.
 *
 * Rule of thumb is: अगर device_add() succeeds, you should call
 * device_del() when you want to get rid of it. If device_add() has
 * *not* succeeded, use *only* put_device() to drop the reference
 * count.
 */
पूर्णांक device_add(काष्ठा device *dev)
अणु
	काष्ठा device *parent;
	काष्ठा kobject *kobj;
	काष्ठा class_पूर्णांकerface *class_पूर्णांकf;
	पूर्णांक error = -EINVAL;
	काष्ठा kobject *glue_dir = शून्य;

	dev = get_device(dev);
	अगर (!dev)
		जाओ करोne;

	अगर (!dev->p) अणु
		error = device_निजी_init(dev);
		अगर (error)
			जाओ करोne;
	पूर्ण

	/*
	 * क्रम अटलally allocated devices, which should all be converted
	 * some day, we need to initialize the name. We prevent पढ़ोing back
	 * the name, and क्रमce the use of dev_name()
	 */
	अगर (dev->init_name) अणु
		dev_set_name(dev, "%s", dev->init_name);
		dev->init_name = शून्य;
	पूर्ण

	/* subप्रणालीs can specअगरy simple device क्रमागतeration */
	अगर (!dev_name(dev) && dev->bus && dev->bus->dev_name)
		dev_set_name(dev, "%s%u", dev->bus->dev_name, dev->id);

	अगर (!dev_name(dev)) अणु
		error = -EINVAL;
		जाओ name_error;
	पूर्ण

	pr_debug("device: '%s': %s\n", dev_name(dev), __func__);

	parent = get_device(dev->parent);
	kobj = get_device_parent(dev, parent);
	अगर (IS_ERR(kobj)) अणु
		error = PTR_ERR(kobj);
		जाओ parent_error;
	पूर्ण
	अगर (kobj)
		dev->kobj.parent = kobj;

	/* use parent numa_node */
	अगर (parent && (dev_to_node(dev) == NUMA_NO_NODE))
		set_dev_node(dev, dev_to_node(parent));

	/* first, रेजिस्टर with generic layer. */
	/* we require the name to be set beक्रमe, and pass शून्य */
	error = kobject_add(&dev->kobj, dev->kobj.parent, शून्य);
	अगर (error) अणु
		glue_dir = get_glue_dir(dev);
		जाओ Error;
	पूर्ण

	/* notअगरy platक्रमm of device entry */
	error = device_platक्रमm_notअगरy(dev, KOBJ_ADD);
	अगर (error)
		जाओ platक्रमm_error;

	error = device_create_file(dev, &dev_attr_uevent);
	अगर (error)
		जाओ attrError;

	error = device_add_class_symlinks(dev);
	अगर (error)
		जाओ SymlinkError;
	error = device_add_attrs(dev);
	अगर (error)
		जाओ AttrsError;
	error = bus_add_device(dev);
	अगर (error)
		जाओ BusError;
	error = dpm_sysfs_add(dev);
	अगर (error)
		जाओ DPMError;
	device_pm_add(dev);

	अगर (MAJOR(dev->devt)) अणु
		error = device_create_file(dev, &dev_attr_dev);
		अगर (error)
			जाओ DevAttrError;

		error = device_create_sys_dev_entry(dev);
		अगर (error)
			जाओ SysEntryError;

		devपंचांगpfs_create_node(dev);
	पूर्ण

	/* Notअगरy clients of device addition.  This call must come
	 * after dpm_sysfs_add() and beक्रमe kobject_uevent().
	 */
	अगर (dev->bus)
		blocking_notअगरier_call_chain(&dev->bus->p->bus_notअगरier,
					     BUS_NOTIFY_ADD_DEVICE, dev);

	kobject_uevent(&dev->kobj, KOBJ_ADD);

	/*
	 * Check अगर any of the other devices (consumers) have been रुकोing क्रम
	 * this device (supplier) to be added so that they can create a device
	 * link to it.
	 *
	 * This needs to happen after device_pm_add() because device_link_add()
	 * requires the supplier be रेजिस्टरed beक्रमe it's called.
	 *
	 * But this also needs to happen beक्रमe bus_probe_device() to make sure
	 * रुकोing consumers can link to it beक्रमe the driver is bound to the
	 * device and the driver sync_state callback is called क्रम this device.
	 */
	अगर (dev->fwnode && !dev->fwnode->dev) अणु
		dev->fwnode->dev = dev;
		fw_devlink_link_device(dev);
	पूर्ण

	bus_probe_device(dev);

	/*
	 * If all driver registration is करोne and a newly added device करोesn't
	 * match with any driver, करोn't block its consumers from probing in
	 * हाल the consumer device is able to operate without this supplier.
	 */
	अगर (dev->fwnode && fw_devlink_drv_reg_करोne && !dev->can_match)
		fw_devlink_unblock_consumers(dev);

	अगर (parent)
		klist_add_tail(&dev->p->knode_parent,
			       &parent->p->klist_children);

	अगर (dev->class) अणु
		mutex_lock(&dev->class->p->mutex);
		/* tie the class to the device */
		klist_add_tail(&dev->p->knode_class,
			       &dev->class->p->klist_devices);

		/* notअगरy any पूर्णांकerfaces that the device is here */
		list_क्रम_each_entry(class_पूर्णांकf,
				    &dev->class->p->पूर्णांकerfaces, node)
			अगर (class_पूर्णांकf->add_dev)
				class_पूर्णांकf->add_dev(dev, class_पूर्णांकf);
		mutex_unlock(&dev->class->p->mutex);
	पूर्ण
करोne:
	put_device(dev);
	वापस error;
 SysEntryError:
	अगर (MAJOR(dev->devt))
		device_हटाओ_file(dev, &dev_attr_dev);
 DevAttrError:
	device_pm_हटाओ(dev);
	dpm_sysfs_हटाओ(dev);
 DPMError:
	bus_हटाओ_device(dev);
 BusError:
	device_हटाओ_attrs(dev);
 AttrsError:
	device_हटाओ_class_symlinks(dev);
 SymlinkError:
	device_हटाओ_file(dev, &dev_attr_uevent);
 attrError:
	device_platक्रमm_notअगरy(dev, KOBJ_REMOVE);
platक्रमm_error:
	kobject_uevent(&dev->kobj, KOBJ_REMOVE);
	glue_dir = get_glue_dir(dev);
	kobject_del(&dev->kobj);
 Error:
	cleanup_glue_dir(dev, glue_dir);
parent_error:
	put_device(parent);
name_error:
	kमुक्त(dev->p);
	dev->p = शून्य;
	जाओ करोne;
पूर्ण
EXPORT_SYMBOL_GPL(device_add);

/**
 * device_रेजिस्टर - रेजिस्टर a device with the प्रणाली.
 * @dev: poपूर्णांकer to the device काष्ठाure
 *
 * This happens in two clean steps - initialize the device
 * and add it to the प्रणाली. The two steps can be called
 * separately, but this is the easiest and most common.
 * I.e. you should only call the two helpers separately अगर
 * have a clearly defined need to use and refcount the device
 * beक्रमe it is added to the hierarchy.
 *
 * For more inक्रमmation, see the kernelकरोc क्रम device_initialize()
 * and device_add().
 *
 * NOTE: _Never_ directly मुक्त @dev after calling this function, even
 * अगर it वापसed an error! Always use put_device() to give up the
 * reference initialized in this function instead.
 */
पूर्णांक device_रेजिस्टर(काष्ठा device *dev)
अणु
	device_initialize(dev);
	वापस device_add(dev);
पूर्ण
EXPORT_SYMBOL_GPL(device_रेजिस्टर);

/**
 * get_device - increment reference count क्रम device.
 * @dev: device.
 *
 * This simply क्रमwards the call to kobject_get(), though
 * we करो take care to provide क्रम the हाल that we get a शून्य
 * poपूर्णांकer passed in.
 */
काष्ठा device *get_device(काष्ठा device *dev)
अणु
	वापस dev ? kobj_to_dev(kobject_get(&dev->kobj)) : शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(get_device);

/**
 * put_device - decrement reference count.
 * @dev: device in question.
 */
व्योम put_device(काष्ठा device *dev)
अणु
	/* might_sleep(); */
	अगर (dev)
		kobject_put(&dev->kobj);
पूर्ण
EXPORT_SYMBOL_GPL(put_device);

bool समाप्त_device(काष्ठा device *dev)
अणु
	/*
	 * Require the device lock and set the "dead" flag to guarantee that
	 * the update behavior is consistent with the other bitfields near
	 * it and that we cannot have an asynchronous probe routine trying
	 * to run जबतक we are tearing out the bus/class/sysfs from
	 * underneath the device.
	 */
	lockdep_निश्चित_held(&dev->mutex);

	अगर (dev->p->dead)
		वापस false;
	dev->p->dead = true;
	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(समाप्त_device);

/**
 * device_del - delete device from प्रणाली.
 * @dev: device.
 *
 * This is the first part of the device unregistration
 * sequence. This हटाओs the device from the lists we control
 * from here, has it हटाओd from the other driver model
 * subप्रणालीs it was added to in device_add(), and हटाओs it
 * from the kobject hierarchy.
 *
 * NOTE: this should be called manually _अगरf_ device_add() was
 * also called manually.
 */
व्योम device_del(काष्ठा device *dev)
अणु
	काष्ठा device *parent = dev->parent;
	काष्ठा kobject *glue_dir = शून्य;
	काष्ठा class_पूर्णांकerface *class_पूर्णांकf;
	अचिन्हित पूर्णांक noio_flag;

	device_lock(dev);
	समाप्त_device(dev);
	device_unlock(dev);

	अगर (dev->fwnode && dev->fwnode->dev == dev)
		dev->fwnode->dev = शून्य;

	/* Notअगरy clients of device removal.  This call must come
	 * beक्रमe dpm_sysfs_हटाओ().
	 */
	noio_flag = meदो_स्मृति_noio_save();
	अगर (dev->bus)
		blocking_notअगरier_call_chain(&dev->bus->p->bus_notअगरier,
					     BUS_NOTIFY_DEL_DEVICE, dev);

	dpm_sysfs_हटाओ(dev);
	अगर (parent)
		klist_del(&dev->p->knode_parent);
	अगर (MAJOR(dev->devt)) अणु
		devपंचांगpfs_delete_node(dev);
		device_हटाओ_sys_dev_entry(dev);
		device_हटाओ_file(dev, &dev_attr_dev);
	पूर्ण
	अगर (dev->class) अणु
		device_हटाओ_class_symlinks(dev);

		mutex_lock(&dev->class->p->mutex);
		/* notअगरy any पूर्णांकerfaces that the device is now gone */
		list_क्रम_each_entry(class_पूर्णांकf,
				    &dev->class->p->पूर्णांकerfaces, node)
			अगर (class_पूर्णांकf->हटाओ_dev)
				class_पूर्णांकf->हटाओ_dev(dev, class_पूर्णांकf);
		/* हटाओ the device from the class list */
		klist_del(&dev->p->knode_class);
		mutex_unlock(&dev->class->p->mutex);
	पूर्ण
	device_हटाओ_file(dev, &dev_attr_uevent);
	device_हटाओ_attrs(dev);
	bus_हटाओ_device(dev);
	device_pm_हटाओ(dev);
	driver_deferred_probe_del(dev);
	device_platक्रमm_notअगरy(dev, KOBJ_REMOVE);
	device_हटाओ_properties(dev);
	device_links_purge(dev);

	अगर (dev->bus)
		blocking_notअगरier_call_chain(&dev->bus->p->bus_notअगरier,
					     BUS_NOTIFY_REMOVED_DEVICE, dev);
	kobject_uevent(&dev->kobj, KOBJ_REMOVE);
	glue_dir = get_glue_dir(dev);
	kobject_del(&dev->kobj);
	cleanup_glue_dir(dev, glue_dir);
	meदो_स्मृति_noio_restore(noio_flag);
	put_device(parent);
पूर्ण
EXPORT_SYMBOL_GPL(device_del);

/**
 * device_unरेजिस्टर - unरेजिस्टर device from प्रणाली.
 * @dev: device going away.
 *
 * We करो this in two parts, like we करो device_रेजिस्टर(). First,
 * we हटाओ it from all the subप्रणालीs with device_del(), then
 * we decrement the reference count via put_device(). If that
 * is the final reference count, the device will be cleaned up
 * via device_release() above. Otherwise, the काष्ठाure will
 * stick around until the final reference to the device is dropped.
 */
व्योम device_unरेजिस्टर(काष्ठा device *dev)
अणु
	pr_debug("device: '%s': %s\n", dev_name(dev), __func__);
	device_del(dev);
	put_device(dev);
पूर्ण
EXPORT_SYMBOL_GPL(device_unरेजिस्टर);

अटल काष्ठा device *prev_device(काष्ठा klist_iter *i)
अणु
	काष्ठा klist_node *n = klist_prev(i);
	काष्ठा device *dev = शून्य;
	काष्ठा device_निजी *p;

	अगर (n) अणु
		p = to_device_निजी_parent(n);
		dev = p->device;
	पूर्ण
	वापस dev;
पूर्ण

अटल काष्ठा device *next_device(काष्ठा klist_iter *i)
अणु
	काष्ठा klist_node *n = klist_next(i);
	काष्ठा device *dev = शून्य;
	काष्ठा device_निजी *p;

	अगर (n) अणु
		p = to_device_निजी_parent(n);
		dev = p->device;
	पूर्ण
	वापस dev;
पूर्ण

/**
 * device_get_devnode - path of device node file
 * @dev: device
 * @mode: वापसed file access mode
 * @uid: वापसed file owner
 * @gid: वापसed file group
 * @पंचांगp: possibly allocated string
 *
 * Return the relative path of a possible device node.
 * Non-शेष names may need to allocate a memory to compose
 * a name. This memory is वापसed in पंचांगp and needs to be
 * मुक्तd by the caller.
 */
स्थिर अक्षर *device_get_devnode(काष्ठा device *dev,
			       umode_t *mode, kuid_t *uid, kgid_t *gid,
			       स्थिर अक्षर **पंचांगp)
अणु
	अक्षर *s;

	*पंचांगp = शून्य;

	/* the device type may provide a specअगरic name */
	अगर (dev->type && dev->type->devnode)
		*पंचांगp = dev->type->devnode(dev, mode, uid, gid);
	अगर (*पंचांगp)
		वापस *पंचांगp;

	/* the class may provide a specअगरic name */
	अगर (dev->class && dev->class->devnode)
		*पंचांगp = dev->class->devnode(dev, mode);
	अगर (*पंचांगp)
		वापस *पंचांगp;

	/* वापस name without allocation, पंचांगp == शून्य */
	अगर (म_अक्षर(dev_name(dev), '!') == शून्य)
		वापस dev_name(dev);

	/* replace '!' in the name with '/' */
	s = kstrdup(dev_name(dev), GFP_KERNEL);
	अगर (!s)
		वापस शून्य;
	strreplace(s, '!', '/');
	वापस *पंचांगp = s;
पूर्ण

/**
 * device_क्रम_each_child - device child iterator.
 * @parent: parent काष्ठा device.
 * @fn: function to be called क्रम each device.
 * @data: data क्रम the callback.
 *
 * Iterate over @parent's child devices, and call @fn क्रम each,
 * passing it @data.
 *
 * We check the वापस of @fn each समय. If it वापसs anything
 * other than 0, we अवरोध out and वापस that value.
 */
पूर्णांक device_क्रम_each_child(काष्ठा device *parent, व्योम *data,
			  पूर्णांक (*fn)(काष्ठा device *dev, व्योम *data))
अणु
	काष्ठा klist_iter i;
	काष्ठा device *child;
	पूर्णांक error = 0;

	अगर (!parent->p)
		वापस 0;

	klist_iter_init(&parent->p->klist_children, &i);
	जबतक (!error && (child = next_device(&i)))
		error = fn(child, data);
	klist_iter_निकास(&i);
	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(device_क्रम_each_child);

/**
 * device_क्रम_each_child_reverse - device child iterator in reversed order.
 * @parent: parent काष्ठा device.
 * @fn: function to be called क्रम each device.
 * @data: data क्रम the callback.
 *
 * Iterate over @parent's child devices, and call @fn क्रम each,
 * passing it @data.
 *
 * We check the वापस of @fn each समय. If it वापसs anything
 * other than 0, we अवरोध out and वापस that value.
 */
पूर्णांक device_क्रम_each_child_reverse(काष्ठा device *parent, व्योम *data,
				  पूर्णांक (*fn)(काष्ठा device *dev, व्योम *data))
अणु
	काष्ठा klist_iter i;
	काष्ठा device *child;
	पूर्णांक error = 0;

	अगर (!parent->p)
		वापस 0;

	klist_iter_init(&parent->p->klist_children, &i);
	जबतक ((child = prev_device(&i)) && !error)
		error = fn(child, data);
	klist_iter_निकास(&i);
	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(device_क्रम_each_child_reverse);

/**
 * device_find_child - device iterator क्रम locating a particular device.
 * @parent: parent काष्ठा device
 * @match: Callback function to check device
 * @data: Data to pass to match function
 *
 * This is similar to the device_क्रम_each_child() function above, but it
 * वापसs a reference to a device that is 'found' क्रम later use, as
 * determined by the @match callback.
 *
 * The callback should वापस 0 अगर the device करोesn't match and non-zero
 * अगर it करोes.  If the callback वापसs non-zero and a reference to the
 * current device can be obtained, this function will वापस to the caller
 * and not iterate over any more devices.
 *
 * NOTE: you will need to drop the reference with put_device() after use.
 */
काष्ठा device *device_find_child(काष्ठा device *parent, व्योम *data,
				 पूर्णांक (*match)(काष्ठा device *dev, व्योम *data))
अणु
	काष्ठा klist_iter i;
	काष्ठा device *child;

	अगर (!parent)
		वापस शून्य;

	klist_iter_init(&parent->p->klist_children, &i);
	जबतक ((child = next_device(&i)))
		अगर (match(child, data) && get_device(child))
			अवरोध;
	klist_iter_निकास(&i);
	वापस child;
पूर्ण
EXPORT_SYMBOL_GPL(device_find_child);

/**
 * device_find_child_by_name - device iterator क्रम locating a child device.
 * @parent: parent काष्ठा device
 * @name: name of the child device
 *
 * This is similar to the device_find_child() function above, but it
 * वापसs a reference to a device that has the name @name.
 *
 * NOTE: you will need to drop the reference with put_device() after use.
 */
काष्ठा device *device_find_child_by_name(काष्ठा device *parent,
					 स्थिर अक्षर *name)
अणु
	काष्ठा klist_iter i;
	काष्ठा device *child;

	अगर (!parent)
		वापस शून्य;

	klist_iter_init(&parent->p->klist_children, &i);
	जबतक ((child = next_device(&i)))
		अगर (sysfs_streq(dev_name(child), name) && get_device(child))
			अवरोध;
	klist_iter_निकास(&i);
	वापस child;
पूर्ण
EXPORT_SYMBOL_GPL(device_find_child_by_name);

पूर्णांक __init devices_init(व्योम)
अणु
	devices_kset = kset_create_and_add("devices", &device_uevent_ops, शून्य);
	अगर (!devices_kset)
		वापस -ENOMEM;
	dev_kobj = kobject_create_and_add("dev", शून्य);
	अगर (!dev_kobj)
		जाओ dev_kobj_err;
	sysfs_dev_block_kobj = kobject_create_and_add("block", dev_kobj);
	अगर (!sysfs_dev_block_kobj)
		जाओ block_kobj_err;
	sysfs_dev_अक्षर_kobj = kobject_create_and_add("char", dev_kobj);
	अगर (!sysfs_dev_अक्षर_kobj)
		जाओ अक्षर_kobj_err;

	वापस 0;

 अक्षर_kobj_err:
	kobject_put(sysfs_dev_block_kobj);
 block_kobj_err:
	kobject_put(dev_kobj);
 dev_kobj_err:
	kset_unरेजिस्टर(devices_kset);
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक device_check_offline(काष्ठा device *dev, व्योम *not_used)
अणु
	पूर्णांक ret;

	ret = device_क्रम_each_child(dev, शून्य, device_check_offline);
	अगर (ret)
		वापस ret;

	वापस device_supports_offline(dev) && !dev->offline ? -EBUSY : 0;
पूर्ण

/**
 * device_offline - Prepare the device क्रम hot-removal.
 * @dev: Device to be put offline.
 *
 * Execute the device bus type's .offline() callback, अगर present, to prepare
 * the device क्रम a subsequent hot-removal.  If that succeeds, the device must
 * not be used until either it is हटाओd or its bus type's .online() callback
 * is executed.
 *
 * Call under device_hotplug_lock.
 */
पूर्णांक device_offline(काष्ठा device *dev)
अणु
	पूर्णांक ret;

	अगर (dev->offline_disabled)
		वापस -EPERM;

	ret = device_क्रम_each_child(dev, शून्य, device_check_offline);
	अगर (ret)
		वापस ret;

	device_lock(dev);
	अगर (device_supports_offline(dev)) अणु
		अगर (dev->offline) अणु
			ret = 1;
		पूर्ण अन्यथा अणु
			ret = dev->bus->offline(dev);
			अगर (!ret) अणु
				kobject_uevent(&dev->kobj, KOBJ_OFFLINE);
				dev->offline = true;
			पूर्ण
		पूर्ण
	पूर्ण
	device_unlock(dev);

	वापस ret;
पूर्ण

/**
 * device_online - Put the device back online after successful device_offline().
 * @dev: Device to be put back online.
 *
 * If device_offline() has been successfully executed क्रम @dev, but the device
 * has not been हटाओd subsequently, execute its bus type's .online() callback
 * to indicate that the device can be used again.
 *
 * Call under device_hotplug_lock.
 */
पूर्णांक device_online(काष्ठा device *dev)
अणु
	पूर्णांक ret = 0;

	device_lock(dev);
	अगर (device_supports_offline(dev)) अणु
		अगर (dev->offline) अणु
			ret = dev->bus->online(dev);
			अगर (!ret) अणु
				kobject_uevent(&dev->kobj, KOBJ_ONLINE);
				dev->offline = false;
			पूर्ण
		पूर्ण अन्यथा अणु
			ret = 1;
		पूर्ण
	पूर्ण
	device_unlock(dev);

	वापस ret;
पूर्ण

काष्ठा root_device अणु
	काष्ठा device dev;
	काष्ठा module *owner;
पूर्ण;

अटल अंतरभूत काष्ठा root_device *to_root_device(काष्ठा device *d)
अणु
	वापस container_of(d, काष्ठा root_device, dev);
पूर्ण

अटल व्योम root_device_release(काष्ठा device *dev)
अणु
	kमुक्त(to_root_device(dev));
पूर्ण

/**
 * __root_device_रेजिस्टर - allocate and रेजिस्टर a root device
 * @name: root device name
 * @owner: owner module of the root device, usually THIS_MODULE
 *
 * This function allocates a root device and रेजिस्टरs it
 * using device_रेजिस्टर(). In order to मुक्त the वापसed
 * device, use root_device_unरेजिस्टर().
 *
 * Root devices are dummy devices which allow other devices
 * to be grouped under /sys/devices. Use this function to
 * allocate a root device and then use it as the parent of
 * any device which should appear under /sys/devices/अणुnameपूर्ण
 *
 * The /sys/devices/अणुnameपूर्ण directory will also contain a
 * 'module' symlink which poपूर्णांकs to the @owner directory
 * in sysfs.
 *
 * Returns &काष्ठा device poपूर्णांकer on success, or ERR_PTR() on error.
 *
 * Note: You probably want to use root_device_रेजिस्टर().
 */
काष्ठा device *__root_device_रेजिस्टर(स्थिर अक्षर *name, काष्ठा module *owner)
अणु
	काष्ठा root_device *root;
	पूर्णांक err = -ENOMEM;

	root = kzalloc(माप(काष्ठा root_device), GFP_KERNEL);
	अगर (!root)
		वापस ERR_PTR(err);

	err = dev_set_name(&root->dev, "%s", name);
	अगर (err) अणु
		kमुक्त(root);
		वापस ERR_PTR(err);
	पूर्ण

	root->dev.release = root_device_release;

	err = device_रेजिस्टर(&root->dev);
	अगर (err) अणु
		put_device(&root->dev);
		वापस ERR_PTR(err);
	पूर्ण

#अगर_घोषित CONFIG_MODULES	/* gotta find a "cleaner" way to करो this */
	अगर (owner) अणु
		काष्ठा module_kobject *mk = &owner->mkobj;

		err = sysfs_create_link(&root->dev.kobj, &mk->kobj, "module");
		अगर (err) अणु
			device_unरेजिस्टर(&root->dev);
			वापस ERR_PTR(err);
		पूर्ण
		root->owner = owner;
	पूर्ण
#पूर्ण_अगर

	वापस &root->dev;
पूर्ण
EXPORT_SYMBOL_GPL(__root_device_रेजिस्टर);

/**
 * root_device_unरेजिस्टर - unरेजिस्टर and मुक्त a root device
 * @dev: device going away
 *
 * This function unरेजिस्टरs and cleans up a device that was created by
 * root_device_रेजिस्टर().
 */
व्योम root_device_unरेजिस्टर(काष्ठा device *dev)
अणु
	काष्ठा root_device *root = to_root_device(dev);

	अगर (root->owner)
		sysfs_हटाओ_link(&root->dev.kobj, "module");

	device_unरेजिस्टर(dev);
पूर्ण
EXPORT_SYMBOL_GPL(root_device_unरेजिस्टर);


अटल व्योम device_create_release(काष्ठा device *dev)
अणु
	pr_debug("device: '%s': %s\n", dev_name(dev), __func__);
	kमुक्त(dev);
पूर्ण

अटल __म_लिखो(6, 0) काष्ठा device *
device_create_groups_vargs(काष्ठा class *class, काष्ठा device *parent,
			   dev_t devt, व्योम *drvdata,
			   स्थिर काष्ठा attribute_group **groups,
			   स्थिर अक्षर *fmt, बहु_सूची args)
अणु
	काष्ठा device *dev = शून्य;
	पूर्णांक retval = -ENODEV;

	अगर (class == शून्य || IS_ERR(class))
		जाओ error;

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev) अणु
		retval = -ENOMEM;
		जाओ error;
	पूर्ण

	device_initialize(dev);
	dev->devt = devt;
	dev->class = class;
	dev->parent = parent;
	dev->groups = groups;
	dev->release = device_create_release;
	dev_set_drvdata(dev, drvdata);

	retval = kobject_set_name_vargs(&dev->kobj, fmt, args);
	अगर (retval)
		जाओ error;

	retval = device_add(dev);
	अगर (retval)
		जाओ error;

	वापस dev;

error:
	put_device(dev);
	वापस ERR_PTR(retval);
पूर्ण

/**
 * device_create - creates a device and रेजिस्टरs it with sysfs
 * @class: poपूर्णांकer to the काष्ठा class that this device should be रेजिस्टरed to
 * @parent: poपूर्णांकer to the parent काष्ठा device of this new device, अगर any
 * @devt: the dev_t क्रम the अक्षर device to be added
 * @drvdata: the data to be added to the device क्रम callbacks
 * @fmt: string क्रम the device's name
 *
 * This function can be used by अक्षर device classes.  A काष्ठा device
 * will be created in sysfs, रेजिस्टरed to the specअगरied class.
 *
 * A "dev" file will be created, showing the dev_t क्रम the device, अगर
 * the dev_t is not 0,0.
 * If a poपूर्णांकer to a parent काष्ठा device is passed in, the newly created
 * काष्ठा device will be a child of that device in sysfs.
 * The poपूर्णांकer to the काष्ठा device will be वापसed from the call.
 * Any further sysfs files that might be required can be created using this
 * poपूर्णांकer.
 *
 * Returns &काष्ठा device poपूर्णांकer on success, or ERR_PTR() on error.
 *
 * Note: the काष्ठा class passed to this function must have previously
 * been created with a call to class_create().
 */
काष्ठा device *device_create(काष्ठा class *class, काष्ठा device *parent,
			     dev_t devt, व्योम *drvdata, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची vargs;
	काष्ठा device *dev;

	बहु_शुरू(vargs, fmt);
	dev = device_create_groups_vargs(class, parent, devt, drvdata, शून्य,
					  fmt, vargs);
	बहु_पूर्ण(vargs);
	वापस dev;
पूर्ण
EXPORT_SYMBOL_GPL(device_create);

/**
 * device_create_with_groups - creates a device and रेजिस्टरs it with sysfs
 * @class: poपूर्णांकer to the काष्ठा class that this device should be रेजिस्टरed to
 * @parent: poपूर्णांकer to the parent काष्ठा device of this new device, अगर any
 * @devt: the dev_t क्रम the अक्षर device to be added
 * @drvdata: the data to be added to the device क्रम callbacks
 * @groups: शून्य-terminated list of attribute groups to be created
 * @fmt: string क्रम the device's name
 *
 * This function can be used by अक्षर device classes.  A काष्ठा device
 * will be created in sysfs, रेजिस्टरed to the specअगरied class.
 * Additional attributes specअगरied in the groups parameter will also
 * be created स्वतःmatically.
 *
 * A "dev" file will be created, showing the dev_t क्रम the device, अगर
 * the dev_t is not 0,0.
 * If a poपूर्णांकer to a parent काष्ठा device is passed in, the newly created
 * काष्ठा device will be a child of that device in sysfs.
 * The poपूर्णांकer to the काष्ठा device will be वापसed from the call.
 * Any further sysfs files that might be required can be created using this
 * poपूर्णांकer.
 *
 * Returns &काष्ठा device poपूर्णांकer on success, or ERR_PTR() on error.
 *
 * Note: the काष्ठा class passed to this function must have previously
 * been created with a call to class_create().
 */
काष्ठा device *device_create_with_groups(काष्ठा class *class,
					 काष्ठा device *parent, dev_t devt,
					 व्योम *drvdata,
					 स्थिर काष्ठा attribute_group **groups,
					 स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची vargs;
	काष्ठा device *dev;

	बहु_शुरू(vargs, fmt);
	dev = device_create_groups_vargs(class, parent, devt, drvdata, groups,
					 fmt, vargs);
	बहु_पूर्ण(vargs);
	वापस dev;
पूर्ण
EXPORT_SYMBOL_GPL(device_create_with_groups);

/**
 * device_destroy - हटाओs a device that was created with device_create()
 * @class: poपूर्णांकer to the काष्ठा class that this device was रेजिस्टरed with
 * @devt: the dev_t of the device that was previously रेजिस्टरed
 *
 * This call unरेजिस्टरs and cleans up a device that was created with a
 * call to device_create().
 */
व्योम device_destroy(काष्ठा class *class, dev_t devt)
अणु
	काष्ठा device *dev;

	dev = class_find_device_by_devt(class, devt);
	अगर (dev) अणु
		put_device(dev);
		device_unरेजिस्टर(dev);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(device_destroy);

/**
 * device_नाम - नामs a device
 * @dev: the poपूर्णांकer to the काष्ठा device to be नामd
 * @new_name: the new name of the device
 *
 * It is the responsibility of the caller to provide mutual
 * exclusion between two dअगरferent calls of device_नाम
 * on the same device to ensure that new_name is valid and
 * won't conflict with other devices.
 *
 * Note: Don't call this function.  Currently, the networking layer calls this
 * function, but that will change.  The following text from Kay Sievers offers
 * some insight:
 *
 * Renaming devices is racy at many levels, symlinks and other stuff are not
 * replaced atomically, and you get a "move" uevent, but it's not easy to
 * connect the event to the old and new device. Device nodes are not नामd at
 * all, there isn't even support क्रम that in the kernel now.
 *
 * In the meanसमय, during renaming, your target name might be taken by another
 * driver, creating conflicts. Or the old name is taken directly after you
 * नामd it -- then you get events क्रम the same DEVPATH, beक्रमe you even see
 * the "move" event. It's just a mess, and nothing new should ever rely on
 * kernel device renaming. Besides that, it's not even implemented now क्रम
 * other things than (driver-core wise very simple) network devices.
 *
 * We are currently about to change network renaming in udev to completely
 * disallow renaming of devices in the same namespace as the kernel uses,
 * because we can't solve the problems properly, that arise with swapping names
 * of multiple पूर्णांकerfaces without races. Means, renaming of eth[0-9]* will only
 * be allowed to some other name than eth[0-9]*, क्रम the aक्रमementioned
 * reasons.
 *
 * Make up a "real" name in the driver beक्रमe you रेजिस्टर anything, or add
 * some other attributes क्रम userspace to find the device, or use udev to add
 * symlinks -- but never नाम kernel devices later, it's a complete mess. We
 * करोn't even want to get पूर्णांकo that and try to implement the missing pieces in
 * the core. We really have other pieces to fix in the driver core mess. :)
 */
पूर्णांक device_नाम(काष्ठा device *dev, स्थिर अक्षर *new_name)
अणु
	काष्ठा kobject *kobj = &dev->kobj;
	अक्षर *old_device_name = शून्य;
	पूर्णांक error;

	dev = get_device(dev);
	अगर (!dev)
		वापस -EINVAL;

	dev_dbg(dev, "renaming to %s\n", new_name);

	old_device_name = kstrdup(dev_name(dev), GFP_KERNEL);
	अगर (!old_device_name) अणु
		error = -ENOMEM;
		जाओ out;
	पूर्ण

	अगर (dev->class) अणु
		error = sysfs_नाम_link_ns(&dev->class->p->subsys.kobj,
					     kobj, old_device_name,
					     new_name, kobject_namespace(kobj));
		अगर (error)
			जाओ out;
	पूर्ण

	error = kobject_नाम(kobj, new_name);
	अगर (error)
		जाओ out;

out:
	put_device(dev);

	kमुक्त(old_device_name);

	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(device_नाम);

अटल पूर्णांक device_move_class_links(काष्ठा device *dev,
				   काष्ठा device *old_parent,
				   काष्ठा device *new_parent)
अणु
	पूर्णांक error = 0;

	अगर (old_parent)
		sysfs_हटाओ_link(&dev->kobj, "device");
	अगर (new_parent)
		error = sysfs_create_link(&dev->kobj, &new_parent->kobj,
					  "device");
	वापस error;
पूर्ण

/**
 * device_move - moves a device to a new parent
 * @dev: the poपूर्णांकer to the काष्ठा device to be moved
 * @new_parent: the new parent of the device (can be शून्य)
 * @dpm_order: how to reorder the dpm_list
 */
पूर्णांक device_move(काष्ठा device *dev, काष्ठा device *new_parent,
		क्रमागत dpm_order dpm_order)
अणु
	पूर्णांक error;
	काष्ठा device *old_parent;
	काष्ठा kobject *new_parent_kobj;

	dev = get_device(dev);
	अगर (!dev)
		वापस -EINVAL;

	device_pm_lock();
	new_parent = get_device(new_parent);
	new_parent_kobj = get_device_parent(dev, new_parent);
	अगर (IS_ERR(new_parent_kobj)) अणु
		error = PTR_ERR(new_parent_kobj);
		put_device(new_parent);
		जाओ out;
	पूर्ण

	pr_debug("device: '%s': %s: moving to '%s'\n", dev_name(dev),
		 __func__, new_parent ? dev_name(new_parent) : "<NULL>");
	error = kobject_move(&dev->kobj, new_parent_kobj);
	अगर (error) अणु
		cleanup_glue_dir(dev, new_parent_kobj);
		put_device(new_parent);
		जाओ out;
	पूर्ण
	old_parent = dev->parent;
	dev->parent = new_parent;
	अगर (old_parent)
		klist_हटाओ(&dev->p->knode_parent);
	अगर (new_parent) अणु
		klist_add_tail(&dev->p->knode_parent,
			       &new_parent->p->klist_children);
		set_dev_node(dev, dev_to_node(new_parent));
	पूर्ण

	अगर (dev->class) अणु
		error = device_move_class_links(dev, old_parent, new_parent);
		अगर (error) अणु
			/* We ignore errors on cleanup since we're hosed anyway... */
			device_move_class_links(dev, new_parent, old_parent);
			अगर (!kobject_move(&dev->kobj, &old_parent->kobj)) अणु
				अगर (new_parent)
					klist_हटाओ(&dev->p->knode_parent);
				dev->parent = old_parent;
				अगर (old_parent) अणु
					klist_add_tail(&dev->p->knode_parent,
						       &old_parent->p->klist_children);
					set_dev_node(dev, dev_to_node(old_parent));
				पूर्ण
			पूर्ण
			cleanup_glue_dir(dev, new_parent_kobj);
			put_device(new_parent);
			जाओ out;
		पूर्ण
	पूर्ण
	चयन (dpm_order) अणु
	हाल DPM_ORDER_NONE:
		अवरोध;
	हाल DPM_ORDER_DEV_AFTER_PARENT:
		device_pm_move_after(dev, new_parent);
		devices_kset_move_after(dev, new_parent);
		अवरोध;
	हाल DPM_ORDER_PARENT_BEFORE_DEV:
		device_pm_move_beक्रमe(new_parent, dev);
		devices_kset_move_beक्रमe(new_parent, dev);
		अवरोध;
	हाल DPM_ORDER_DEV_LAST:
		device_pm_move_last(dev);
		devices_kset_move_last(dev);
		अवरोध;
	पूर्ण

	put_device(old_parent);
out:
	device_pm_unlock();
	put_device(dev);
	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(device_move);

अटल पूर्णांक device_attrs_change_owner(काष्ठा device *dev, kuid_t kuid,
				     kgid_t kgid)
अणु
	काष्ठा kobject *kobj = &dev->kobj;
	काष्ठा class *class = dev->class;
	स्थिर काष्ठा device_type *type = dev->type;
	पूर्णांक error;

	अगर (class) अणु
		/*
		 * Change the device groups of the device class क्रम @dev to
		 * @kuid/@kgid.
		 */
		error = sysfs_groups_change_owner(kobj, class->dev_groups, kuid,
						  kgid);
		अगर (error)
			वापस error;
	पूर्ण

	अगर (type) अणु
		/*
		 * Change the device groups of the device type क्रम @dev to
		 * @kuid/@kgid.
		 */
		error = sysfs_groups_change_owner(kobj, type->groups, kuid,
						  kgid);
		अगर (error)
			वापस error;
	पूर्ण

	/* Change the device groups of @dev to @kuid/@kgid. */
	error = sysfs_groups_change_owner(kobj, dev->groups, kuid, kgid);
	अगर (error)
		वापस error;

	अगर (device_supports_offline(dev) && !dev->offline_disabled) अणु
		/* Change online device attributes of @dev to @kuid/@kgid. */
		error = sysfs_file_change_owner(kobj, dev_attr_online.attr.name,
						kuid, kgid);
		अगर (error)
			वापस error;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * device_change_owner - change the owner of an existing device.
 * @dev: device.
 * @kuid: new owner's kuid
 * @kgid: new owner's kgid
 *
 * This changes the owner of @dev and its corresponding sysfs entries to
 * @kuid/@kgid. This function बंदly mirrors how @dev was added via driver
 * core.
 *
 * Returns 0 on success or error code on failure.
 */
पूर्णांक device_change_owner(काष्ठा device *dev, kuid_t kuid, kgid_t kgid)
अणु
	पूर्णांक error;
	काष्ठा kobject *kobj = &dev->kobj;

	dev = get_device(dev);
	अगर (!dev)
		वापस -EINVAL;

	/*
	 * Change the kobject and the शेष attributes and groups of the
	 * ktype associated with it to @kuid/@kgid.
	 */
	error = sysfs_change_owner(kobj, kuid, kgid);
	अगर (error)
		जाओ out;

	/*
	 * Change the uevent file क्रम @dev to the new owner. The uevent file
	 * was created in a separate step when @dev got added and we mirror
	 * that step here.
	 */
	error = sysfs_file_change_owner(kobj, dev_attr_uevent.attr.name, kuid,
					kgid);
	अगर (error)
		जाओ out;

	/*
	 * Change the device groups, the device groups associated with the
	 * device class, and the groups associated with the device type of @dev
	 * to @kuid/@kgid.
	 */
	error = device_attrs_change_owner(dev, kuid, kgid);
	अगर (error)
		जाओ out;

	error = dpm_sysfs_change_owner(dev, kuid, kgid);
	अगर (error)
		जाओ out;

#अगर_घोषित CONFIG_BLOCK
	अगर (sysfs_deprecated && dev->class == &block_class)
		जाओ out;
#पूर्ण_अगर

	/*
	 * Change the owner of the symlink located in the class directory of
	 * the device class associated with @dev which poपूर्णांकs to the actual
	 * directory entry क्रम @dev to @kuid/@kgid. This ensures that the
	 * symlink shows the same permissions as its target.
	 */
	error = sysfs_link_change_owner(&dev->class->p->subsys.kobj, &dev->kobj,
					dev_name(dev), kuid, kgid);
	अगर (error)
		जाओ out;

out:
	put_device(dev);
	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(device_change_owner);

/**
 * device_shutकरोwn - call ->shutकरोwn() on each device to shutकरोwn.
 */
व्योम device_shutकरोwn(व्योम)
अणु
	काष्ठा device *dev, *parent;

	रुको_क्रम_device_probe();
	device_block_probing();

	cpufreq_suspend();

	spin_lock(&devices_kset->list_lock);
	/*
	 * Walk the devices list backward, shutting करोwn each in turn.
	 * Beware that device unplug events may also start pulling
	 * devices offline, even as the प्रणाली is shutting करोwn.
	 */
	जबतक (!list_empty(&devices_kset->list)) अणु
		dev = list_entry(devices_kset->list.prev, काष्ठा device,
				kobj.entry);

		/*
		 * hold reference count of device's parent to
		 * prevent it from being मुक्तd because parent's
		 * lock is to be held
		 */
		parent = get_device(dev->parent);
		get_device(dev);
		/*
		 * Make sure the device is off the kset list, in the
		 * event that dev->*->shutकरोwn() करोesn't हटाओ it.
		 */
		list_del_init(&dev->kobj.entry);
		spin_unlock(&devices_kset->list_lock);

		/* hold lock to aव्योम race with probe/release */
		अगर (parent)
			device_lock(parent);
		device_lock(dev);

		/* Don't allow any more runसमय suspends */
		pm_runसमय_get_noresume(dev);
		pm_runसमय_barrier(dev);

		अगर (dev->class && dev->class->shutकरोwn_pre) अणु
			अगर (initcall_debug)
				dev_info(dev, "shutdown_pre\n");
			dev->class->shutकरोwn_pre(dev);
		पूर्ण
		अगर (dev->bus && dev->bus->shutकरोwn) अणु
			अगर (initcall_debug)
				dev_info(dev, "shutdown\n");
			dev->bus->shutकरोwn(dev);
		पूर्ण अन्यथा अगर (dev->driver && dev->driver->shutकरोwn) अणु
			अगर (initcall_debug)
				dev_info(dev, "shutdown\n");
			dev->driver->shutकरोwn(dev);
		पूर्ण

		device_unlock(dev);
		अगर (parent)
			device_unlock(parent);

		put_device(dev);
		put_device(parent);

		spin_lock(&devices_kset->list_lock);
	पूर्ण
	spin_unlock(&devices_kset->list_lock);
पूर्ण

/*
 * Device logging functions
 */

#अगर_घोषित CONFIG_PRINTK
अटल व्योम
set_dev_info(स्थिर काष्ठा device *dev, काष्ठा dev_prपूर्णांकk_info *dev_info)
अणु
	स्थिर अक्षर *subsys;

	स_रखो(dev_info, 0, माप(*dev_info));

	अगर (dev->class)
		subsys = dev->class->name;
	अन्यथा अगर (dev->bus)
		subsys = dev->bus->name;
	अन्यथा
		वापस;

	strscpy(dev_info->subप्रणाली, subsys, माप(dev_info->subप्रणाली));

	/*
	 * Add device identअगरier DEVICE=:
	 *   b12:8         block dev_t
	 *   c127:3        अक्षर dev_t
	 *   n8            netdev अगरindex
	 *   +sound:card0  subप्रणाली:devname
	 */
	अगर (MAJOR(dev->devt)) अणु
		अक्षर c;

		अगर (म_भेद(subsys, "block") == 0)
			c = 'b';
		अन्यथा
			c = 'c';

		snम_लिखो(dev_info->device, माप(dev_info->device),
			 "%c%u:%u", c, MAJOR(dev->devt), MINOR(dev->devt));
	पूर्ण अन्यथा अगर (म_भेद(subsys, "net") == 0) अणु
		काष्ठा net_device *net = to_net_dev(dev);

		snम_लिखो(dev_info->device, माप(dev_info->device),
			 "n%u", net->अगरindex);
	पूर्ण अन्यथा अणु
		snम_लिखो(dev_info->device, माप(dev_info->device),
			 "+%s:%s", subsys, dev_name(dev));
	पूर्ण
पूर्ण

पूर्णांक dev_vprपूर्णांकk_emit(पूर्णांक level, स्थिर काष्ठा device *dev,
		     स्थिर अक्षर *fmt, बहु_सूची args)
अणु
	काष्ठा dev_prपूर्णांकk_info dev_info;

	set_dev_info(dev, &dev_info);

	वापस vprपूर्णांकk_emit(0, level, &dev_info, fmt, args);
पूर्ण
EXPORT_SYMBOL(dev_vprपूर्णांकk_emit);

पूर्णांक dev_prपूर्णांकk_emit(पूर्णांक level, स्थिर काष्ठा device *dev, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	पूर्णांक r;

	बहु_शुरू(args, fmt);

	r = dev_vprपूर्णांकk_emit(level, dev, fmt, args);

	बहु_पूर्ण(args);

	वापस r;
पूर्ण
EXPORT_SYMBOL(dev_prपूर्णांकk_emit);

अटल व्योम __dev_prपूर्णांकk(स्थिर अक्षर *level, स्थिर काष्ठा device *dev,
			काष्ठा va_क्रमmat *vaf)
अणु
	अगर (dev)
		dev_prपूर्णांकk_emit(level[1] - '0', dev, "%s %s: %pV",
				dev_driver_string(dev), dev_name(dev), vaf);
	अन्यथा
		prपूर्णांकk("%s(NULL device *): %pV", level, vaf);
पूर्ण

व्योम dev_prपूर्णांकk(स्थिर अक्षर *level, स्थिर काष्ठा device *dev,
		स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	बहु_शुरू(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	__dev_prपूर्णांकk(level, dev, &vaf);

	बहु_पूर्ण(args);
पूर्ण
EXPORT_SYMBOL(dev_prपूर्णांकk);

#घोषणा define_dev_prपूर्णांकk_level(func, kern_level)		\
व्योम func(स्थिर काष्ठा device *dev, स्थिर अक्षर *fmt, ...)	\
अणु								\
	काष्ठा va_क्रमmat vaf;					\
	बहु_सूची args;						\
								\
	बहु_शुरू(args, fmt);					\
								\
	vaf.fmt = fmt;						\
	vaf.va = &args;						\
								\
	__dev_prपूर्णांकk(kern_level, dev, &vaf);			\
								\
	बहु_पूर्ण(args);						\
पूर्ण								\
EXPORT_SYMBOL(func);

define_dev_prपूर्णांकk_level(_dev_emerg, KERN_EMERG);
define_dev_prपूर्णांकk_level(_dev_alert, KERN_ALERT);
define_dev_prपूर्णांकk_level(_dev_crit, KERN_CRIT);
define_dev_prपूर्णांकk_level(_dev_err, KERN_ERR);
define_dev_prपूर्णांकk_level(_dev_warn, KERN_WARNING);
define_dev_prपूर्णांकk_level(_dev_notice, KERN_NOTICE);
define_dev_prपूर्णांकk_level(_dev_info, KERN_INFO);

#पूर्ण_अगर

/**
 * dev_err_probe - probe error check and log helper
 * @dev: the poपूर्णांकer to the काष्ठा device
 * @err: error value to test
 * @fmt: म_लिखो-style क्रमmat string
 * @...: arguments as specअगरied in the क्रमmat string
 *
 * This helper implements common pattern present in probe functions क्रम error
 * checking: prपूर्णांक debug or error message depending अगर the error value is
 * -EPROBE_DEFER and propagate error upwards.
 * In हाल of -EPROBE_DEFER it sets also defer probe reason, which can be
 * checked later by पढ़ोing devices_deferred debugfs attribute.
 * It replaces code sequence::
 *
 * 	अगर (err != -EPROBE_DEFER)
 * 		dev_err(dev, ...);
 * 	अन्यथा
 * 		dev_dbg(dev, ...);
 * 	वापस err;
 *
 * with::
 *
 * 	वापस dev_err_probe(dev, err, ...);
 *
 * Returns @err.
 *
 */
पूर्णांक dev_err_probe(स्थिर काष्ठा device *dev, पूर्णांक err, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	बहु_शुरू(args, fmt);
	vaf.fmt = fmt;
	vaf.va = &args;

	अगर (err != -EPROBE_DEFER) अणु
		dev_err(dev, "error %pe: %pV", ERR_PTR(err), &vaf);
	पूर्ण अन्यथा अणु
		device_set_deferred_probe_reason(dev, &vaf);
		dev_dbg(dev, "error %pe: %pV", ERR_PTR(err), &vaf);
	पूर्ण

	बहु_पूर्ण(args);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(dev_err_probe);

अटल अंतरभूत bool fwnode_is_primary(काष्ठा fwnode_handle *fwnode)
अणु
	वापस fwnode && !IS_ERR(fwnode->secondary);
पूर्ण

/**
 * set_primary_fwnode - Change the primary firmware node of a given device.
 * @dev: Device to handle.
 * @fwnode: New primary firmware node of the device.
 *
 * Set the device's firmware node poपूर्णांकer to @fwnode, but अगर a secondary
 * firmware node of the device is present, preserve it.
 *
 * Valid fwnode हालs are:
 *  - primary --> secondary --> -ENODEV
 *  - primary --> शून्य
 *  - secondary --> -ENODEV
 *  - शून्य
 */
व्योम set_primary_fwnode(काष्ठा device *dev, काष्ठा fwnode_handle *fwnode)
अणु
	काष्ठा device *parent = dev->parent;
	काष्ठा fwnode_handle *fn = dev->fwnode;

	अगर (fwnode) अणु
		अगर (fwnode_is_primary(fn))
			fn = fn->secondary;

		अगर (fn) अणु
			WARN_ON(fwnode->secondary);
			fwnode->secondary = fn;
		पूर्ण
		dev->fwnode = fwnode;
	पूर्ण अन्यथा अणु
		अगर (fwnode_is_primary(fn)) अणु
			dev->fwnode = fn->secondary;
			/* Set fn->secondary = शून्य, so fn reमुख्यs the primary fwnode */
			अगर (!(parent && fn == parent->fwnode))
				fn->secondary = शून्य;
		पूर्ण अन्यथा अणु
			dev->fwnode = शून्य;
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(set_primary_fwnode);

/**
 * set_secondary_fwnode - Change the secondary firmware node of a given device.
 * @dev: Device to handle.
 * @fwnode: New secondary firmware node of the device.
 *
 * If a primary firmware node of the device is present, set its secondary
 * poपूर्णांकer to @fwnode.  Otherwise, set the device's firmware node poपूर्णांकer to
 * @fwnode.
 */
व्योम set_secondary_fwnode(काष्ठा device *dev, काष्ठा fwnode_handle *fwnode)
अणु
	अगर (fwnode)
		fwnode->secondary = ERR_PTR(-ENODEV);

	अगर (fwnode_is_primary(dev->fwnode))
		dev->fwnode->secondary = fwnode;
	अन्यथा
		dev->fwnode = fwnode;
पूर्ण
EXPORT_SYMBOL_GPL(set_secondary_fwnode);

/**
 * device_set_of_node_from_dev - reuse device-tree node of another device
 * @dev: device whose device-tree node is being set
 * @dev2: device whose device-tree node is being reused
 *
 * Takes another reference to the new device-tree node after first dropping
 * any reference held to the old node.
 */
व्योम device_set_of_node_from_dev(काष्ठा device *dev, स्थिर काष्ठा device *dev2)
अणु
	of_node_put(dev->of_node);
	dev->of_node = of_node_get(dev2->of_node);
	dev->of_node_reused = true;
पूर्ण
EXPORT_SYMBOL_GPL(device_set_of_node_from_dev);

पूर्णांक device_match_name(काष्ठा device *dev, स्थिर व्योम *name)
अणु
	वापस sysfs_streq(dev_name(dev), name);
पूर्ण
EXPORT_SYMBOL_GPL(device_match_name);

पूर्णांक device_match_of_node(काष्ठा device *dev, स्थिर व्योम *np)
अणु
	वापस dev->of_node == np;
पूर्ण
EXPORT_SYMBOL_GPL(device_match_of_node);

पूर्णांक device_match_fwnode(काष्ठा device *dev, स्थिर व्योम *fwnode)
अणु
	वापस dev_fwnode(dev) == fwnode;
पूर्ण
EXPORT_SYMBOL_GPL(device_match_fwnode);

पूर्णांक device_match_devt(काष्ठा device *dev, स्थिर व्योम *pdevt)
अणु
	वापस dev->devt == *(dev_t *)pdevt;
पूर्ण
EXPORT_SYMBOL_GPL(device_match_devt);

पूर्णांक device_match_acpi_dev(काष्ठा device *dev, स्थिर व्योम *adev)
अणु
	वापस ACPI_COMPANION(dev) == adev;
पूर्ण
EXPORT_SYMBOL(device_match_acpi_dev);

पूर्णांक device_match_any(काष्ठा device *dev, स्थिर व्योम *unused)
अणु
	वापस 1;
पूर्ण
EXPORT_SYMBOL_GPL(device_match_any);
