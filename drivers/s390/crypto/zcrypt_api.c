<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  Copyright IBM Corp. 2001, 2018
 *  Author(s): Robert Burroughs
 *	       Eric Rossman (edrossma@us.ibm.com)
 *	       Cornelia Huck <cornelia.huck@de.ibm.com>
 *
 *  Hotplug & misc device support: Jochen Roehrig (roehrig@de.ibm.com)
 *  Major cleanup & driver split: Martin Schwidefsky <schwidefsky@de.ibm.com>
 *				  Ralph Wuerthner <rwuerthn@de.ibm.com>
 *  MSGTYPE reकाष्ठा:		  Holger Dengler <hd@linux.vnet.ibm.com>
 *  Multiple device nodes: Harald Freudenberger <freude@linux.ibm.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/fs.h>
#समावेश <linux/compat.h>
#समावेश <linux/slab.h>
#समावेश <linux/atomic.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/hw_अक्रमom.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/cdev.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/capability.h>
#समावेश <यंत्र/debug.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश <यंत्र/trace/zcrypt.h>

#समावेश "zcrypt_api.h"
#समावेश "zcrypt_debug.h"

#समावेश "zcrypt_msgtype6.h"
#समावेश "zcrypt_msgtype50.h"
#समावेश "zcrypt_ccamisc.h"
#समावेश "zcrypt_ep11misc.h"

/*
 * Module description.
 */
MODULE_AUTHOR("IBM Corporation");
MODULE_DESCRIPTION("Cryptographic Coprocessor interface, " \
		   "Copyright IBM Corp. 2001, 2012");
MODULE_LICENSE("GPL");

/*
 * zcrypt tracepoपूर्णांक functions
 */
EXPORT_TRACEPOINT_SYMBOL(s390_zcrypt_req);
EXPORT_TRACEPOINT_SYMBOL(s390_zcrypt_rep);

अटल पूर्णांक zcrypt_hwrng_seed = 1;
module_param_named(hwrng_seed, zcrypt_hwrng_seed, पूर्णांक, 0440);
MODULE_PARM_DESC(hwrng_seed, "Turn on/off hwrng auto seed, default is 1 (on).");

DEFINE_SPINLOCK(zcrypt_list_lock);
LIST_HEAD(zcrypt_card_list);
पूर्णांक zcrypt_device_count;

अटल atomic_t zcrypt_खोलो_count = ATOMIC_INIT(0);
अटल atomic_t zcrypt_rescan_count = ATOMIC_INIT(0);

atomic_t zcrypt_rescan_req = ATOMIC_INIT(0);
EXPORT_SYMBOL(zcrypt_rescan_req);

अटल LIST_HEAD(zcrypt_ops_list);

/* Zcrypt related debug feature stuff. */
debug_info_t *zcrypt_dbf_info;

/**
 * Process a rescan of the transport layer.
 *
 * Returns 1, अगर the rescan has been processed, otherwise 0.
 */
अटल अंतरभूत पूर्णांक zcrypt_process_rescan(व्योम)
अणु
	अगर (atomic_पढ़ो(&zcrypt_rescan_req)) अणु
		atomic_set(&zcrypt_rescan_req, 0);
		atomic_inc(&zcrypt_rescan_count);
		ap_bus_क्रमce_rescan();
		ZCRYPT_DBF(DBF_INFO, "rescan count=%07d\n",
			   atomic_inc_वापस(&zcrypt_rescan_count));
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

व्योम zcrypt_msgtype_रेजिस्टर(काष्ठा zcrypt_ops *zops)
अणु
	list_add_tail(&zops->list, &zcrypt_ops_list);
पूर्ण

व्योम zcrypt_msgtype_unरेजिस्टर(काष्ठा zcrypt_ops *zops)
अणु
	list_del_init(&zops->list);
पूर्ण

काष्ठा zcrypt_ops *zcrypt_msgtype(अचिन्हित अक्षर *name, पूर्णांक variant)
अणु
	काष्ठा zcrypt_ops *zops;

	list_क्रम_each_entry(zops, &zcrypt_ops_list, list)
		अगर ((zops->variant == variant) &&
		    (!म_भेदन(zops->name, name, माप(zops->name))))
			वापस zops;
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(zcrypt_msgtype);

/*
 * Multi device nodes extension functions.
 */

#अगर_घोषित CONFIG_ZCRYPT_MULTIDEVNODES

काष्ठा zcdn_device;

अटल काष्ठा class *zcrypt_class;
अटल dev_t zcrypt_devt;
अटल काष्ठा cdev zcrypt_cdev;

काष्ठा zcdn_device अणु
	काष्ठा device device;
	काष्ठा ap_perms perms;
पूर्ण;

#घोषणा to_zcdn_dev(x) container_of((x), काष्ठा zcdn_device, device)

#घोषणा ZCDN_MAX_NAME 32

अटल पूर्णांक zcdn_create(स्थिर अक्षर *name);
अटल पूर्णांक zcdn_destroy(स्थिर अक्षर *name);

/*
 * Find zcdn device by name.
 * Returns reference to the zcdn device which needs to be released
 * with put_device() after use.
 */
अटल अंतरभूत काष्ठा zcdn_device *find_zcdndev_by_name(स्थिर अक्षर *name)
अणु
	काष्ठा device *dev = class_find_device_by_name(zcrypt_class, name);

	वापस dev ? to_zcdn_dev(dev) : शून्य;
पूर्ण

/*
 * Find zcdn device by devt value.
 * Returns reference to the zcdn device which needs to be released
 * with put_device() after use.
 */
अटल अंतरभूत काष्ठा zcdn_device *find_zcdndev_by_devt(dev_t devt)
अणु
	काष्ठा device *dev = class_find_device_by_devt(zcrypt_class, devt);

	वापस dev ? to_zcdn_dev(dev) : शून्य;
पूर्ण

अटल sमाप_प्रकार ioctlmask_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	पूर्णांक i, rc;
	काष्ठा zcdn_device *zcdndev = to_zcdn_dev(dev);

	अगर (mutex_lock_पूर्णांकerruptible(&ap_perms_mutex))
		वापस -ERESTARTSYS;

	buf[0] = '0';
	buf[1] = 'x';
	क्रम (i = 0; i < माप(zcdndev->perms.ioctlm) / माप(दीर्घ); i++)
		snम_लिखो(buf + 2 + 2 * i * माप(दीर्घ),
			 PAGE_SIZE - 2 - 2 * i * माप(दीर्घ),
			 "%016lx", zcdndev->perms.ioctlm[i]);
	buf[2 + 2 * i * माप(दीर्घ)] = '\n';
	buf[2 + 2 * i * माप(दीर्घ) + 1] = '\0';
	rc = 2 + 2 * i * माप(दीर्घ) + 1;

	mutex_unlock(&ap_perms_mutex);

	वापस rc;
पूर्ण

अटल sमाप_प्रकार ioctlmask_store(काष्ठा device *dev,
			       काष्ठा device_attribute *attr,
			       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक rc;
	काष्ठा zcdn_device *zcdndev = to_zcdn_dev(dev);

	rc = ap_parse_mask_str(buf, zcdndev->perms.ioctlm,
			       AP_IOCTLS, &ap_perms_mutex);
	अगर (rc)
		वापस rc;

	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(ioctlmask);

अटल sमाप_प्रकार apmask_show(काष्ठा device *dev,
			   काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	पूर्णांक i, rc;
	काष्ठा zcdn_device *zcdndev = to_zcdn_dev(dev);

	अगर (mutex_lock_पूर्णांकerruptible(&ap_perms_mutex))
		वापस -ERESTARTSYS;

	buf[0] = '0';
	buf[1] = 'x';
	क्रम (i = 0; i < माप(zcdndev->perms.apm) / माप(दीर्घ); i++)
		snम_लिखो(buf + 2 + 2 * i * माप(दीर्घ),
			 PAGE_SIZE - 2 - 2 * i * माप(दीर्घ),
			 "%016lx", zcdndev->perms.apm[i]);
	buf[2 + 2 * i * माप(दीर्घ)] = '\n';
	buf[2 + 2 * i * माप(दीर्घ) + 1] = '\0';
	rc = 2 + 2 * i * माप(दीर्घ) + 1;

	mutex_unlock(&ap_perms_mutex);

	वापस rc;
पूर्ण

अटल sमाप_प्रकार apmask_store(काष्ठा device *dev,
			    काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक rc;
	काष्ठा zcdn_device *zcdndev = to_zcdn_dev(dev);

	rc = ap_parse_mask_str(buf, zcdndev->perms.apm,
			       AP_DEVICES, &ap_perms_mutex);
	अगर (rc)
		वापस rc;

	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(apmask);

अटल sमाप_प्रकार aqmask_show(काष्ठा device *dev,
			   काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	पूर्णांक i, rc;
	काष्ठा zcdn_device *zcdndev = to_zcdn_dev(dev);

	अगर (mutex_lock_पूर्णांकerruptible(&ap_perms_mutex))
		वापस -ERESTARTSYS;

	buf[0] = '0';
	buf[1] = 'x';
	क्रम (i = 0; i < माप(zcdndev->perms.aqm) / माप(दीर्घ); i++)
		snम_लिखो(buf + 2 + 2 * i * माप(दीर्घ),
			 PAGE_SIZE - 2 - 2 * i * माप(दीर्घ),
			 "%016lx", zcdndev->perms.aqm[i]);
	buf[2 + 2 * i * माप(दीर्घ)] = '\n';
	buf[2 + 2 * i * माप(दीर्घ) + 1] = '\0';
	rc = 2 + 2 * i * माप(दीर्घ) + 1;

	mutex_unlock(&ap_perms_mutex);

	वापस rc;
पूर्ण

अटल sमाप_प्रकार aqmask_store(काष्ठा device *dev,
			    काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक rc;
	काष्ठा zcdn_device *zcdndev = to_zcdn_dev(dev);

	rc = ap_parse_mask_str(buf, zcdndev->perms.aqm,
			       AP_DOMAINS, &ap_perms_mutex);
	अगर (rc)
		वापस rc;

	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(aqmask);

अटल काष्ठा attribute *zcdn_dev_attrs[] = अणु
	&dev_attr_ioctlmask.attr,
	&dev_attr_apmask.attr,
	&dev_attr_aqmask.attr,
	शून्य
पूर्ण;

अटल काष्ठा attribute_group zcdn_dev_attr_group = अणु
	.attrs = zcdn_dev_attrs
पूर्ण;

अटल स्थिर काष्ठा attribute_group *zcdn_dev_attr_groups[] = अणु
	&zcdn_dev_attr_group,
	शून्य
पूर्ण;

अटल sमाप_प्रकार zcdn_create_store(काष्ठा class *class,
				 काष्ठा class_attribute *attr,
				 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक rc;
	अक्षर name[ZCDN_MAX_NAME];

	म_नकलन(name, skip_spaces(buf), माप(name));
	name[माप(name) - 1] = '\0';

	rc = zcdn_create(strim(name));

	वापस rc ? rc : count;
पूर्ण

अटल स्थिर काष्ठा class_attribute class_attr_zcdn_create =
	__ATTR(create, 0600, शून्य, zcdn_create_store);

अटल sमाप_प्रकार zcdn_destroy_store(काष्ठा class *class,
				  काष्ठा class_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक rc;
	अक्षर name[ZCDN_MAX_NAME];

	म_नकलन(name, skip_spaces(buf), माप(name));
	name[माप(name) - 1] = '\0';

	rc = zcdn_destroy(strim(name));

	वापस rc ? rc : count;
पूर्ण

अटल स्थिर काष्ठा class_attribute class_attr_zcdn_destroy =
	__ATTR(destroy, 0600, शून्य, zcdn_destroy_store);

अटल व्योम zcdn_device_release(काष्ठा device *dev)
अणु
	काष्ठा zcdn_device *zcdndev = to_zcdn_dev(dev);

	ZCRYPT_DBF(DBF_INFO, "releasing zcdn device %d:%d\n",
		   MAJOR(dev->devt), MINOR(dev->devt));

	kमुक्त(zcdndev);
पूर्ण

अटल पूर्णांक zcdn_create(स्थिर अक्षर *name)
अणु
	dev_t devt;
	पूर्णांक i, rc = 0;
	अक्षर nodename[ZCDN_MAX_NAME];
	काष्ठा zcdn_device *zcdndev;

	अगर (mutex_lock_पूर्णांकerruptible(&ap_perms_mutex))
		वापस -ERESTARTSYS;

	/* check अगर device node with this name alपढ़ोy exists */
	अगर (name[0]) अणु
		zcdndev = find_zcdndev_by_name(name);
		अगर (zcdndev) अणु
			put_device(&zcdndev->device);
			rc = -EEXIST;
			जाओ unlockout;
		पूर्ण
	पूर्ण

	/* find an unused minor number */
	क्रम (i = 0; i < ZCRYPT_MAX_MINOR_NODES; i++) अणु
		devt = MKDEV(MAJOR(zcrypt_devt), MINOR(zcrypt_devt) + i);
		zcdndev = find_zcdndev_by_devt(devt);
		अगर (zcdndev)
			put_device(&zcdndev->device);
		अन्यथा
			अवरोध;
	पूर्ण
	अगर (i == ZCRYPT_MAX_MINOR_NODES) अणु
		rc = -ENOSPC;
		जाओ unlockout;
	पूर्ण

	/* alloc and prepare a new zcdn device */
	zcdndev = kzalloc(माप(*zcdndev), GFP_KERNEL);
	अगर (!zcdndev) अणु
		rc = -ENOMEM;
		जाओ unlockout;
	पूर्ण
	zcdndev->device.release = zcdn_device_release;
	zcdndev->device.class = zcrypt_class;
	zcdndev->device.devt = devt;
	zcdndev->device.groups = zcdn_dev_attr_groups;
	अगर (name[0])
		म_नकलन(nodename, name, माप(nodename));
	अन्यथा
		snम_लिखो(nodename, माप(nodename),
			 ZCRYPT_NAME "_%d", (पूर्णांक) MINOR(devt));
	nodename[माप(nodename)-1] = '\0';
	अगर (dev_set_name(&zcdndev->device, nodename)) अणु
		rc = -EINVAL;
		जाओ unlockout;
	पूर्ण
	rc = device_रेजिस्टर(&zcdndev->device);
	अगर (rc) अणु
		put_device(&zcdndev->device);
		जाओ unlockout;
	पूर्ण

	ZCRYPT_DBF(DBF_INFO, "created zcdn device %d:%d\n",
		   MAJOR(devt), MINOR(devt));

unlockout:
	mutex_unlock(&ap_perms_mutex);
	वापस rc;
पूर्ण

अटल पूर्णांक zcdn_destroy(स्थिर अक्षर *name)
अणु
	पूर्णांक rc = 0;
	काष्ठा zcdn_device *zcdndev;

	अगर (mutex_lock_पूर्णांकerruptible(&ap_perms_mutex))
		वापस -ERESTARTSYS;

	/* try to find this zcdn device */
	zcdndev = find_zcdndev_by_name(name);
	अगर (!zcdndev) अणु
		rc = -ENOENT;
		जाओ unlockout;
	पूर्ण

	/*
	 * The zcdn device is not hard destroyed. It is subject to
	 * reference counting and thus just needs to be unरेजिस्टरed.
	 */
	put_device(&zcdndev->device);
	device_unरेजिस्टर(&zcdndev->device);

unlockout:
	mutex_unlock(&ap_perms_mutex);
	वापस rc;
पूर्ण

अटल व्योम zcdn_destroy_all(व्योम)
अणु
	पूर्णांक i;
	dev_t devt;
	काष्ठा zcdn_device *zcdndev;

	mutex_lock(&ap_perms_mutex);
	क्रम (i = 0; i < ZCRYPT_MAX_MINOR_NODES; i++) अणु
		devt = MKDEV(MAJOR(zcrypt_devt), MINOR(zcrypt_devt) + i);
		zcdndev = find_zcdndev_by_devt(devt);
		अगर (zcdndev) अणु
			put_device(&zcdndev->device);
			device_unरेजिस्टर(&zcdndev->device);
		पूर्ण
	पूर्ण
	mutex_unlock(&ap_perms_mutex);
पूर्ण

#पूर्ण_अगर

/**
 * zcrypt_पढ़ो (): Not supported beyond zcrypt 1.3.1.
 *
 * This function is not supported beyond zcrypt 1.3.1.
 */
अटल sमाप_प्रकार zcrypt_पढ़ो(काष्ठा file *filp, अक्षर __user *buf,
			   माप_प्रकार count, loff_t *f_pos)
अणु
	वापस -EPERM;
पूर्ण

/**
 * zcrypt_ग_लिखो(): Not allowed.
 *
 * Write is is not allowed
 */
अटल sमाप_प्रकार zcrypt_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *buf,
			    माप_प्रकार count, loff_t *f_pos)
अणु
	वापस -EPERM;
पूर्ण

/**
 * zcrypt_खोलो(): Count number of users.
 *
 * Device खोलो function to count number of users.
 */
अटल पूर्णांक zcrypt_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा ap_perms *perms = &ap_perms;

#अगर_घोषित CONFIG_ZCRYPT_MULTIDEVNODES
	अगर (filp->f_inode->i_cdev == &zcrypt_cdev) अणु
		काष्ठा zcdn_device *zcdndev;

		अगर (mutex_lock_पूर्णांकerruptible(&ap_perms_mutex))
			वापस -ERESTARTSYS;
		zcdndev = find_zcdndev_by_devt(filp->f_inode->i_rdev);
		/* find वापसs a reference, no get_device() needed */
		mutex_unlock(&ap_perms_mutex);
		अगर (zcdndev)
			perms = &zcdndev->perms;
	पूर्ण
#पूर्ण_अगर
	filp->निजी_data = (व्योम *) perms;

	atomic_inc(&zcrypt_खोलो_count);
	वापस stream_खोलो(inode, filp);
पूर्ण

/**
 * zcrypt_release(): Count number of users.
 *
 * Device बंद function to count number of users.
 */
अटल पूर्णांक zcrypt_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
#अगर_घोषित CONFIG_ZCRYPT_MULTIDEVNODES
	अगर (filp->f_inode->i_cdev == &zcrypt_cdev) अणु
		काष्ठा zcdn_device *zcdndev;

		mutex_lock(&ap_perms_mutex);
		zcdndev = find_zcdndev_by_devt(filp->f_inode->i_rdev);
		mutex_unlock(&ap_perms_mutex);
		अगर (zcdndev) अणु
			/* 2 माला_दो here: one क्रम find, one क्रम खोलो */
			put_device(&zcdndev->device);
			put_device(&zcdndev->device);
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	atomic_dec(&zcrypt_खोलो_count);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक zcrypt_check_ioctl(काष्ठा ap_perms *perms,
				     अचिन्हित पूर्णांक cmd)
अणु
	पूर्णांक rc = -EPERM;
	पूर्णांक ioctlnr = (cmd & _IOC_NRMASK) >> _IOC_NRSHIFT;

	अगर (ioctlnr > 0 && ioctlnr < AP_IOCTLS) अणु
		अगर (test_bit_inv(ioctlnr, perms->ioctlm))
			rc = 0;
	पूर्ण

	अगर (rc)
		ZCRYPT_DBF(DBF_WARN,
			   "ioctl check failed: ioctlnr=0x%04x rc=%d\n",
			   ioctlnr, rc);

	वापस rc;
पूर्ण

अटल अंतरभूत bool zcrypt_check_card(काष्ठा ap_perms *perms, पूर्णांक card)
अणु
	वापस test_bit_inv(card, perms->apm) ? true : false;
पूर्ण

अटल अंतरभूत bool zcrypt_check_queue(काष्ठा ap_perms *perms, पूर्णांक queue)
अणु
	वापस test_bit_inv(queue, perms->aqm) ? true : false;
पूर्ण

अटल अंतरभूत काष्ठा zcrypt_queue *zcrypt_pick_queue(काष्ठा zcrypt_card *zc,
						     काष्ठा zcrypt_queue *zq,
						     काष्ठा module **pmod,
						     अचिन्हित पूर्णांक weight)
अणु
	अगर (!zq || !try_module_get(zq->queue->ap_dev.drv->driver.owner))
		वापस शून्य;
	zcrypt_queue_get(zq);
	get_device(&zq->queue->ap_dev.device);
	atomic_add(weight, &zc->load);
	atomic_add(weight, &zq->load);
	zq->request_count++;
	*pmod = zq->queue->ap_dev.drv->driver.owner;
	वापस zq;
पूर्ण

अटल अंतरभूत व्योम zcrypt_drop_queue(काष्ठा zcrypt_card *zc,
				     काष्ठा zcrypt_queue *zq,
				     काष्ठा module *mod,
				     अचिन्हित पूर्णांक weight)
अणु
	zq->request_count--;
	atomic_sub(weight, &zc->load);
	atomic_sub(weight, &zq->load);
	put_device(&zq->queue->ap_dev.device);
	zcrypt_queue_put(zq);
	module_put(mod);
पूर्ण

अटल अंतरभूत bool zcrypt_card_compare(काष्ठा zcrypt_card *zc,
				       काष्ठा zcrypt_card *pref_zc,
				       अचिन्हित पूर्णांक weight,
				       अचिन्हित पूर्णांक pref_weight)
अणु
	अगर (!pref_zc)
		वापस true;
	weight += atomic_पढ़ो(&zc->load);
	pref_weight += atomic_पढ़ो(&pref_zc->load);
	अगर (weight == pref_weight)
		वापस atomic64_पढ़ो(&zc->card->total_request_count) <
			atomic64_पढ़ो(&pref_zc->card->total_request_count);
	वापस weight < pref_weight;
पूर्ण

अटल अंतरभूत bool zcrypt_queue_compare(काष्ठा zcrypt_queue *zq,
					काष्ठा zcrypt_queue *pref_zq,
					अचिन्हित पूर्णांक weight,
					अचिन्हित पूर्णांक pref_weight)
अणु
	अगर (!pref_zq)
		वापस true;
	weight += atomic_पढ़ो(&zq->load);
	pref_weight += atomic_पढ़ो(&pref_zq->load);
	अगर (weight == pref_weight)
		वापस zq->queue->total_request_count <
			pref_zq->queue->total_request_count;
	वापस weight < pref_weight;
पूर्ण

/*
 * zcrypt ioctls.
 */
अटल दीर्घ zcrypt_rsa_modexpo(काष्ठा ap_perms *perms,
			       काष्ठा zcrypt_track *tr,
			       काष्ठा ica_rsa_modexpo *mex)
अणु
	काष्ठा zcrypt_card *zc, *pref_zc;
	काष्ठा zcrypt_queue *zq, *pref_zq;
	काष्ठा ap_message ap_msg;
	अचिन्हित पूर्णांक wgt = 0, pref_wgt = 0;
	अचिन्हित पूर्णांक func_code;
	पूर्णांक cpen, qpen, qid = 0, rc = -ENODEV;
	काष्ठा module *mod;

	trace_s390_zcrypt_req(mex, TP_ICARSAMODEXPO);

	ap_init_message(&ap_msg);

#अगर_घोषित CONFIG_ZCRYPT_DEBUG
	अगर (tr && tr->fi.cmd)
		ap_msg.fi.cmd = tr->fi.cmd;
#पूर्ण_अगर

	अगर (mex->outputdatalength < mex->inputdatalength) अणु
		func_code = 0;
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	/*
	 * As दीर्घ as outputdatalength is big enough, we can set the
	 * outputdatalength equal to the inputdatalength, since that is the
	 * number of bytes we will copy in any हाल
	 */
	mex->outputdatalength = mex->inputdatalength;

	rc = get_rsa_modex_fc(mex, &func_code);
	अगर (rc)
		जाओ out;

	pref_zc = शून्य;
	pref_zq = शून्य;
	spin_lock(&zcrypt_list_lock);
	क्रम_each_zcrypt_card(zc) अणु
		/* Check क्रम useable accelarator or CCA card */
		अगर (!zc->online || !zc->card->config ||
		    !(zc->card->functions & 0x18000000))
			जारी;
		/* Check क्रम size limits */
		अगर (zc->min_mod_size > mex->inputdatalength ||
		    zc->max_mod_size < mex->inputdatalength)
			जारी;
		/* check अगर device node has admission क्रम this card */
		अगर (!zcrypt_check_card(perms, zc->card->id))
			जारी;
		/* get weight index of the card device	*/
		wgt = zc->speed_rating[func_code];
		/* penalty अगर this msg was previously sent via this card */
		cpen = (tr && tr->again_counter && tr->last_qid &&
			AP_QID_CARD(tr->last_qid) == zc->card->id) ?
			TRACK_AGAIN_CARD_WEIGHT_PENALTY : 0;
		अगर (!zcrypt_card_compare(zc, pref_zc, wgt + cpen, pref_wgt))
			जारी;
		क्रम_each_zcrypt_queue(zq, zc) अणु
			/* check अगर device is useable and eligible */
			अगर (!zq->online || !zq->ops->rsa_modexpo ||
			    !zq->queue->config)
				जारी;
			/* check अगर device node has admission क्रम this queue */
			अगर (!zcrypt_check_queue(perms,
						AP_QID_QUEUE(zq->queue->qid)))
				जारी;
			/* penalty अगर the msg was previously sent at this qid */
			qpen = (tr && tr->again_counter && tr->last_qid &&
				tr->last_qid == zq->queue->qid) ?
				TRACK_AGAIN_QUEUE_WEIGHT_PENALTY : 0;
			अगर (!zcrypt_queue_compare(zq, pref_zq,
						  wgt + cpen + qpen, pref_wgt))
				जारी;
			pref_zc = zc;
			pref_zq = zq;
			pref_wgt = wgt + cpen + qpen;
		पूर्ण
	पूर्ण
	pref_zq = zcrypt_pick_queue(pref_zc, pref_zq, &mod, wgt);
	spin_unlock(&zcrypt_list_lock);

	अगर (!pref_zq) अणु
		rc = -ENODEV;
		जाओ out;
	पूर्ण

	qid = pref_zq->queue->qid;
	rc = pref_zq->ops->rsa_modexpo(pref_zq, mex, &ap_msg);

	spin_lock(&zcrypt_list_lock);
	zcrypt_drop_queue(pref_zc, pref_zq, mod, wgt);
	spin_unlock(&zcrypt_list_lock);

out:
	ap_release_message(&ap_msg);
	अगर (tr) अणु
		tr->last_rc = rc;
		tr->last_qid = qid;
	पूर्ण
	trace_s390_zcrypt_rep(mex, func_code, rc,
			      AP_QID_CARD(qid), AP_QID_QUEUE(qid));
	वापस rc;
पूर्ण

अटल दीर्घ zcrypt_rsa_crt(काष्ठा ap_perms *perms,
			   काष्ठा zcrypt_track *tr,
			   काष्ठा ica_rsa_modexpo_crt *crt)
अणु
	काष्ठा zcrypt_card *zc, *pref_zc;
	काष्ठा zcrypt_queue *zq, *pref_zq;
	काष्ठा ap_message ap_msg;
	अचिन्हित पूर्णांक wgt = 0, pref_wgt = 0;
	अचिन्हित पूर्णांक func_code;
	पूर्णांक cpen, qpen, qid = 0, rc = -ENODEV;
	काष्ठा module *mod;

	trace_s390_zcrypt_req(crt, TP_ICARSACRT);

	ap_init_message(&ap_msg);

#अगर_घोषित CONFIG_ZCRYPT_DEBUG
	अगर (tr && tr->fi.cmd)
		ap_msg.fi.cmd = tr->fi.cmd;
#पूर्ण_अगर

	अगर (crt->outputdatalength < crt->inputdatalength) अणु
		func_code = 0;
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	/*
	 * As दीर्घ as outputdatalength is big enough, we can set the
	 * outputdatalength equal to the inputdatalength, since that is the
	 * number of bytes we will copy in any हाल
	 */
	crt->outputdatalength = crt->inputdatalength;

	rc = get_rsa_crt_fc(crt, &func_code);
	अगर (rc)
		जाओ out;

	pref_zc = शून्य;
	pref_zq = शून्य;
	spin_lock(&zcrypt_list_lock);
	क्रम_each_zcrypt_card(zc) अणु
		/* Check क्रम useable accelarator or CCA card */
		अगर (!zc->online || !zc->card->config ||
		    !(zc->card->functions & 0x18000000))
			जारी;
		/* Check क्रम size limits */
		अगर (zc->min_mod_size > crt->inputdatalength ||
		    zc->max_mod_size < crt->inputdatalength)
			जारी;
		/* check अगर device node has admission क्रम this card */
		अगर (!zcrypt_check_card(perms, zc->card->id))
			जारी;
		/* get weight index of the card device	*/
		wgt = zc->speed_rating[func_code];
		/* penalty अगर this msg was previously sent via this card */
		cpen = (tr && tr->again_counter && tr->last_qid &&
			AP_QID_CARD(tr->last_qid) == zc->card->id) ?
			TRACK_AGAIN_CARD_WEIGHT_PENALTY : 0;
		अगर (!zcrypt_card_compare(zc, pref_zc, wgt + cpen, pref_wgt))
			जारी;
		क्रम_each_zcrypt_queue(zq, zc) अणु
			/* check अगर device is useable and eligible */
			अगर (!zq->online || !zq->ops->rsa_modexpo_crt ||
			    !zq->queue->config)
				जारी;
			/* check अगर device node has admission क्रम this queue */
			अगर (!zcrypt_check_queue(perms,
						AP_QID_QUEUE(zq->queue->qid)))
				जारी;
			/* penalty अगर the msg was previously sent at this qid */
			qpen = (tr && tr->again_counter && tr->last_qid &&
				tr->last_qid == zq->queue->qid) ?
				TRACK_AGAIN_QUEUE_WEIGHT_PENALTY : 0;
			अगर (!zcrypt_queue_compare(zq, pref_zq,
						  wgt + cpen + qpen, pref_wgt))
				जारी;
			pref_zc = zc;
			pref_zq = zq;
			pref_wgt = wgt + cpen + qpen;
		पूर्ण
	पूर्ण
	pref_zq = zcrypt_pick_queue(pref_zc, pref_zq, &mod, wgt);
	spin_unlock(&zcrypt_list_lock);

	अगर (!pref_zq) अणु
		rc = -ENODEV;
		जाओ out;
	पूर्ण

	qid = pref_zq->queue->qid;
	rc = pref_zq->ops->rsa_modexpo_crt(pref_zq, crt, &ap_msg);

	spin_lock(&zcrypt_list_lock);
	zcrypt_drop_queue(pref_zc, pref_zq, mod, wgt);
	spin_unlock(&zcrypt_list_lock);

out:
	ap_release_message(&ap_msg);
	अगर (tr) अणु
		tr->last_rc = rc;
		tr->last_qid = qid;
	पूर्ण
	trace_s390_zcrypt_rep(crt, func_code, rc,
			      AP_QID_CARD(qid), AP_QID_QUEUE(qid));
	वापस rc;
पूर्ण

अटल दीर्घ _zcrypt_send_cprb(bool userspace, काष्ठा ap_perms *perms,
			      काष्ठा zcrypt_track *tr,
			      काष्ठा ica_xcRB *xcRB)
अणु
	काष्ठा zcrypt_card *zc, *pref_zc;
	काष्ठा zcrypt_queue *zq, *pref_zq;
	काष्ठा ap_message ap_msg;
	अचिन्हित पूर्णांक wgt = 0, pref_wgt = 0;
	अचिन्हित पूर्णांक func_code;
	अचिन्हित लघु *करोमुख्य, tकरोm;
	पूर्णांक cpen, qpen, qid = 0, rc = -ENODEV;
	काष्ठा module *mod;

	trace_s390_zcrypt_req(xcRB, TB_ZSECSENDCPRB);

	xcRB->status = 0;
	ap_init_message(&ap_msg);

#अगर_घोषित CONFIG_ZCRYPT_DEBUG
	अगर (tr && tr->fi.cmd)
		ap_msg.fi.cmd = tr->fi.cmd;
	अगर (tr && tr->fi.action == AP_FI_ACTION_CCA_AGENT_FF) अणु
		ZCRYPT_DBF_WARN("%s fi cmd 0x%04x: forcing invalid agent_ID 'FF'\n",
				__func__, tr->fi.cmd);
		xcRB->agent_ID = 0x4646;
	पूर्ण
#पूर्ण_अगर

	rc = get_cprb_fc(userspace, xcRB, &ap_msg, &func_code, &करोमुख्य);
	अगर (rc)
		जाओ out;

	/*
	 * If a valid target करोमुख्य is set and this करोमुख्य is NOT a usage
	 * करोमुख्य but a control only करोमुख्य, use the शेष करोमुख्य as target.
	 */
	tकरोm = *करोमुख्य;
	अगर (tकरोm < AP_DOMAINS &&
	    !ap_test_config_usage_करोमुख्य(tकरोm) &&
	    ap_test_config_ctrl_करोमुख्य(tकरोm) &&
	    ap_करोमुख्य_index >= 0)
		tकरोm = ap_करोमुख्य_index;

	pref_zc = शून्य;
	pref_zq = शून्य;
	spin_lock(&zcrypt_list_lock);
	क्रम_each_zcrypt_card(zc) अणु
		/* Check क्रम useable CCA card */
		अगर (!zc->online || !zc->card->config ||
		    !(zc->card->functions & 0x10000000))
			जारी;
		/* Check क्रम user selected CCA card */
		अगर (xcRB->user_defined != AUTOSELECT &&
		    xcRB->user_defined != zc->card->id)
			जारी;
		/* check अगर device node has admission क्रम this card */
		अगर (!zcrypt_check_card(perms, zc->card->id))
			जारी;
		/* get weight index of the card device	*/
		wgt = speed_idx_cca(func_code) * zc->speed_rating[SECKEY];
		/* penalty अगर this msg was previously sent via this card */
		cpen = (tr && tr->again_counter && tr->last_qid &&
			AP_QID_CARD(tr->last_qid) == zc->card->id) ?
			TRACK_AGAIN_CARD_WEIGHT_PENALTY : 0;
		अगर (!zcrypt_card_compare(zc, pref_zc, wgt + cpen, pref_wgt))
			जारी;
		क्रम_each_zcrypt_queue(zq, zc) अणु
			/* check क्रम device useable and eligible */
			अगर (!zq->online ||
			    !zq->ops->send_cprb ||
			    !zq->queue->config ||
			    (tकरोm != AUTOSEL_DOM &&
			     tकरोm != AP_QID_QUEUE(zq->queue->qid)))
				जारी;
			/* check अगर device node has admission क्रम this queue */
			अगर (!zcrypt_check_queue(perms,
						AP_QID_QUEUE(zq->queue->qid)))
				जारी;
			/* penalty अगर the msg was previously sent at this qid */
			qpen = (tr && tr->again_counter && tr->last_qid &&
				tr->last_qid == zq->queue->qid) ?
				TRACK_AGAIN_QUEUE_WEIGHT_PENALTY : 0;
			अगर (!zcrypt_queue_compare(zq, pref_zq,
						  wgt + cpen + qpen, pref_wgt))
				जारी;
			pref_zc = zc;
			pref_zq = zq;
			pref_wgt = wgt + cpen + qpen;
		पूर्ण
	पूर्ण
	pref_zq = zcrypt_pick_queue(pref_zc, pref_zq, &mod, wgt);
	spin_unlock(&zcrypt_list_lock);

	अगर (!pref_zq) अणु
		rc = -ENODEV;
		जाओ out;
	पूर्ण

	/* in हाल of स्वतः select, provide the correct करोमुख्य */
	qid = pref_zq->queue->qid;
	अगर (*करोमुख्य == AUTOSEL_DOM)
		*करोमुख्य = AP_QID_QUEUE(qid);

#अगर_घोषित CONFIG_ZCRYPT_DEBUG
	अगर (tr && tr->fi.action == AP_FI_ACTION_CCA_DOM_INVAL) अणु
		ZCRYPT_DBF_WARN("%s fi cmd 0x%04x: forcing invalid domain\n",
				__func__, tr->fi.cmd);
		*करोमुख्य = 99;
	पूर्ण
#पूर्ण_अगर

	rc = pref_zq->ops->send_cprb(userspace, pref_zq, xcRB, &ap_msg);

	spin_lock(&zcrypt_list_lock);
	zcrypt_drop_queue(pref_zc, pref_zq, mod, wgt);
	spin_unlock(&zcrypt_list_lock);

out:
	ap_release_message(&ap_msg);
	अगर (tr) अणु
		tr->last_rc = rc;
		tr->last_qid = qid;
	पूर्ण
	trace_s390_zcrypt_rep(xcRB, func_code, rc,
			      AP_QID_CARD(qid), AP_QID_QUEUE(qid));
	वापस rc;
पूर्ण

दीर्घ zcrypt_send_cprb(काष्ठा ica_xcRB *xcRB)
अणु
	वापस _zcrypt_send_cprb(false, &ap_perms, शून्य, xcRB);
पूर्ण
EXPORT_SYMBOL(zcrypt_send_cprb);

अटल bool is_desired_ep11_card(अचिन्हित पूर्णांक dev_id,
				 अचिन्हित लघु target_num,
				 काष्ठा ep11_target_dev *tarमाला_लो)
अणु
	जबतक (target_num-- > 0) अणु
		अगर (tarमाला_लो->ap_id == dev_id || tarमाला_लो->ap_id == AUTOSEL_AP)
			वापस true;
		tarमाला_लो++;
	पूर्ण
	वापस false;
पूर्ण

अटल bool is_desired_ep11_queue(अचिन्हित पूर्णांक dev_qid,
				  अचिन्हित लघु target_num,
				  काष्ठा ep11_target_dev *tarमाला_लो)
अणु
	पूर्णांक card = AP_QID_CARD(dev_qid), करोm = AP_QID_QUEUE(dev_qid);

	जबतक (target_num-- > 0) अणु
		अगर ((tarमाला_लो->ap_id == card || tarमाला_लो->ap_id == AUTOSEL_AP) &&
		    (tarमाला_लो->करोm_id == करोm || tarमाला_लो->करोm_id == AUTOSEL_DOM))
			वापस true;
		tarमाला_लो++;
	पूर्ण
	वापस false;
पूर्ण

अटल दीर्घ _zcrypt_send_ep11_cprb(bool userspace, काष्ठा ap_perms *perms,
				   काष्ठा zcrypt_track *tr,
				   काष्ठा ep11_urb *xcrb)
अणु
	काष्ठा zcrypt_card *zc, *pref_zc;
	काष्ठा zcrypt_queue *zq, *pref_zq;
	काष्ठा ep11_target_dev *tarमाला_लो;
	अचिन्हित लघु target_num;
	अचिन्हित पूर्णांक wgt = 0, pref_wgt = 0;
	अचिन्हित पूर्णांक func_code;
	काष्ठा ap_message ap_msg;
	पूर्णांक cpen, qpen, qid = 0, rc = -ENODEV;
	काष्ठा module *mod;

	trace_s390_zcrypt_req(xcrb, TP_ZSENDEP11CPRB);

	ap_init_message(&ap_msg);

#अगर_घोषित CONFIG_ZCRYPT_DEBUG
	अगर (tr && tr->fi.cmd)
		ap_msg.fi.cmd = tr->fi.cmd;
#पूर्ण_अगर

	target_num = (अचिन्हित लघु) xcrb->tarमाला_लो_num;

	/* empty list indicates स्वतःselect (all available tarमाला_लो) */
	tarमाला_लो = शून्य;
	अगर (target_num != 0) अणु
		काष्ठा ep11_target_dev __user *uptr;

		tarमाला_लो = kसुस्मृति(target_num, माप(*tarमाला_लो), GFP_KERNEL);
		अगर (!tarमाला_लो) अणु
			func_code = 0;
			rc = -ENOMEM;
			जाओ out;
		पूर्ण

		uptr = (काष्ठा ep11_target_dev __क्रमce __user *) xcrb->tarमाला_लो;
		अगर (z_copy_from_user(userspace, tarमाला_लो, uptr,
				   target_num * माप(*tarमाला_लो))) अणु
			func_code = 0;
			rc = -EFAULT;
			जाओ out_मुक्त;
		पूर्ण
	पूर्ण

	rc = get_ep11cprb_fc(userspace, xcrb, &ap_msg, &func_code);
	अगर (rc)
		जाओ out_मुक्त;

	pref_zc = शून्य;
	pref_zq = शून्य;
	spin_lock(&zcrypt_list_lock);
	क्रम_each_zcrypt_card(zc) अणु
		/* Check क्रम useable EP11 card */
		अगर (!zc->online || !zc->card->config ||
		    !(zc->card->functions & 0x04000000))
			जारी;
		/* Check क्रम user selected EP11 card */
		अगर (tarमाला_लो &&
		    !is_desired_ep11_card(zc->card->id, target_num, tarमाला_लो))
			जारी;
		/* check अगर device node has admission क्रम this card */
		अगर (!zcrypt_check_card(perms, zc->card->id))
			जारी;
		/* get weight index of the card device	*/
		wgt = speed_idx_ep11(func_code) * zc->speed_rating[SECKEY];
		/* penalty अगर this msg was previously sent via this card */
		cpen = (tr && tr->again_counter && tr->last_qid &&
			AP_QID_CARD(tr->last_qid) == zc->card->id) ?
			TRACK_AGAIN_CARD_WEIGHT_PENALTY : 0;
		अगर (!zcrypt_card_compare(zc, pref_zc, wgt + cpen, pref_wgt))
			जारी;
		क्रम_each_zcrypt_queue(zq, zc) अणु
			/* check अगर device is useable and eligible */
			अगर (!zq->online ||
			    !zq->ops->send_ep11_cprb ||
			    !zq->queue->config ||
			    (tarमाला_लो &&
			     !is_desired_ep11_queue(zq->queue->qid,
						    target_num, tarमाला_लो)))
				जारी;
			/* check अगर device node has admission क्रम this queue */
			अगर (!zcrypt_check_queue(perms,
						AP_QID_QUEUE(zq->queue->qid)))
				जारी;
			/* penalty अगर the msg was previously sent at this qid */
			qpen = (tr && tr->again_counter && tr->last_qid &&
				tr->last_qid == zq->queue->qid) ?
				TRACK_AGAIN_QUEUE_WEIGHT_PENALTY : 0;
			अगर (!zcrypt_queue_compare(zq, pref_zq,
						  wgt + cpen + qpen, pref_wgt))
				जारी;
			pref_zc = zc;
			pref_zq = zq;
			pref_wgt = wgt + cpen + qpen;
		पूर्ण
	पूर्ण
	pref_zq = zcrypt_pick_queue(pref_zc, pref_zq, &mod, wgt);
	spin_unlock(&zcrypt_list_lock);

	अगर (!pref_zq) अणु
		rc = -ENODEV;
		जाओ out_मुक्त;
	पूर्ण

	qid = pref_zq->queue->qid;
	rc = pref_zq->ops->send_ep11_cprb(userspace, pref_zq, xcrb, &ap_msg);

	spin_lock(&zcrypt_list_lock);
	zcrypt_drop_queue(pref_zc, pref_zq, mod, wgt);
	spin_unlock(&zcrypt_list_lock);

out_मुक्त:
	kमुक्त(tarमाला_लो);
out:
	ap_release_message(&ap_msg);
	अगर (tr) अणु
		tr->last_rc = rc;
		tr->last_qid = qid;
	पूर्ण
	trace_s390_zcrypt_rep(xcrb, func_code, rc,
			      AP_QID_CARD(qid), AP_QID_QUEUE(qid));
	वापस rc;
पूर्ण

दीर्घ zcrypt_send_ep11_cprb(काष्ठा ep11_urb *xcrb)
अणु
	वापस _zcrypt_send_ep11_cprb(false, &ap_perms, शून्य, xcrb);
पूर्ण
EXPORT_SYMBOL(zcrypt_send_ep11_cprb);

अटल दीर्घ zcrypt_rng(अक्षर *buffer)
अणु
	काष्ठा zcrypt_card *zc, *pref_zc;
	काष्ठा zcrypt_queue *zq, *pref_zq;
	अचिन्हित पूर्णांक wgt = 0, pref_wgt = 0;
	अचिन्हित पूर्णांक func_code;
	काष्ठा ap_message ap_msg;
	अचिन्हित पूर्णांक करोमुख्य;
	पूर्णांक qid = 0, rc = -ENODEV;
	काष्ठा module *mod;

	trace_s390_zcrypt_req(buffer, TP_HWRNGCPRB);

	ap_init_message(&ap_msg);
	rc = get_rng_fc(&ap_msg, &func_code, &करोमुख्य);
	अगर (rc)
		जाओ out;

	pref_zc = शून्य;
	pref_zq = शून्य;
	spin_lock(&zcrypt_list_lock);
	क्रम_each_zcrypt_card(zc) अणु
		/* Check क्रम useable CCA card */
		अगर (!zc->online || !zc->card->config ||
		    !(zc->card->functions & 0x10000000))
			जारी;
		/* get weight index of the card device	*/
		wgt = zc->speed_rating[func_code];
		अगर (!zcrypt_card_compare(zc, pref_zc, wgt, pref_wgt))
			जारी;
		क्रम_each_zcrypt_queue(zq, zc) अणु
			/* check अगर device is useable and eligible */
			अगर (!zq->online || !zq->ops->rng ||
			    !zq->queue->config)
				जारी;
			अगर (!zcrypt_queue_compare(zq, pref_zq, wgt, pref_wgt))
				जारी;
			pref_zc = zc;
			pref_zq = zq;
			pref_wgt = wgt;
		पूर्ण
	पूर्ण
	pref_zq = zcrypt_pick_queue(pref_zc, pref_zq, &mod, wgt);
	spin_unlock(&zcrypt_list_lock);

	अगर (!pref_zq) अणु
		rc = -ENODEV;
		जाओ out;
	पूर्ण

	qid = pref_zq->queue->qid;
	rc = pref_zq->ops->rng(pref_zq, buffer, &ap_msg);

	spin_lock(&zcrypt_list_lock);
	zcrypt_drop_queue(pref_zc, pref_zq, mod, wgt);
	spin_unlock(&zcrypt_list_lock);

out:
	ap_release_message(&ap_msg);
	trace_s390_zcrypt_rep(buffer, func_code, rc,
			      AP_QID_CARD(qid), AP_QID_QUEUE(qid));
	वापस rc;
पूर्ण

अटल व्योम zcrypt_device_status_mask(काष्ठा zcrypt_device_status *devstatus)
अणु
	काष्ठा zcrypt_card *zc;
	काष्ठा zcrypt_queue *zq;
	काष्ठा zcrypt_device_status *stat;
	पूर्णांक card, queue;

	स_रखो(devstatus, 0, MAX_ZDEV_ENTRIES
	       * माप(काष्ठा zcrypt_device_status));

	spin_lock(&zcrypt_list_lock);
	क्रम_each_zcrypt_card(zc) अणु
		क्रम_each_zcrypt_queue(zq, zc) अणु
			card = AP_QID_CARD(zq->queue->qid);
			अगर (card >= MAX_ZDEV_CARDIDS)
				जारी;
			queue = AP_QID_QUEUE(zq->queue->qid);
			stat = &devstatus[card * AP_DOMAINS + queue];
			stat->hwtype = zc->card->ap_dev.device_type;
			stat->functions = zc->card->functions >> 26;
			stat->qid = zq->queue->qid;
			stat->online = zq->online ? 0x01 : 0x00;
		पूर्ण
	पूर्ण
	spin_unlock(&zcrypt_list_lock);
पूर्ण

व्योम zcrypt_device_status_mask_ext(काष्ठा zcrypt_device_status_ext *devstatus)
अणु
	काष्ठा zcrypt_card *zc;
	काष्ठा zcrypt_queue *zq;
	काष्ठा zcrypt_device_status_ext *stat;
	पूर्णांक card, queue;

	स_रखो(devstatus, 0, MAX_ZDEV_ENTRIES_EXT
	       * माप(काष्ठा zcrypt_device_status_ext));

	spin_lock(&zcrypt_list_lock);
	क्रम_each_zcrypt_card(zc) अणु
		क्रम_each_zcrypt_queue(zq, zc) अणु
			card = AP_QID_CARD(zq->queue->qid);
			queue = AP_QID_QUEUE(zq->queue->qid);
			stat = &devstatus[card * AP_DOMAINS + queue];
			stat->hwtype = zc->card->ap_dev.device_type;
			stat->functions = zc->card->functions >> 26;
			stat->qid = zq->queue->qid;
			stat->online = zq->online ? 0x01 : 0x00;
		पूर्ण
	पूर्ण
	spin_unlock(&zcrypt_list_lock);
पूर्ण
EXPORT_SYMBOL(zcrypt_device_status_mask_ext);

पूर्णांक zcrypt_device_status_ext(पूर्णांक card, पूर्णांक queue,
			     काष्ठा zcrypt_device_status_ext *devstat)
अणु
	काष्ठा zcrypt_card *zc;
	काष्ठा zcrypt_queue *zq;

	स_रखो(devstat, 0, माप(*devstat));

	spin_lock(&zcrypt_list_lock);
	क्रम_each_zcrypt_card(zc) अणु
		क्रम_each_zcrypt_queue(zq, zc) अणु
			अगर (card == AP_QID_CARD(zq->queue->qid) &&
			    queue == AP_QID_QUEUE(zq->queue->qid)) अणु
				devstat->hwtype = zc->card->ap_dev.device_type;
				devstat->functions = zc->card->functions >> 26;
				devstat->qid = zq->queue->qid;
				devstat->online = zq->online ? 0x01 : 0x00;
				spin_unlock(&zcrypt_list_lock);
				वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock(&zcrypt_list_lock);

	वापस -ENODEV;
पूर्ण
EXPORT_SYMBOL(zcrypt_device_status_ext);

अटल व्योम zcrypt_status_mask(अक्षर status[], माप_प्रकार max_adapters)
अणु
	काष्ठा zcrypt_card *zc;
	काष्ठा zcrypt_queue *zq;
	पूर्णांक card;

	स_रखो(status, 0, max_adapters);
	spin_lock(&zcrypt_list_lock);
	क्रम_each_zcrypt_card(zc) अणु
		क्रम_each_zcrypt_queue(zq, zc) अणु
			card = AP_QID_CARD(zq->queue->qid);
			अगर (AP_QID_QUEUE(zq->queue->qid) != ap_करोमुख्य_index
			    || card >= max_adapters)
				जारी;
			status[card] = zc->online ? zc->user_space_type : 0x0d;
		पूर्ण
	पूर्ण
	spin_unlock(&zcrypt_list_lock);
पूर्ण

अटल व्योम zcrypt_qdepth_mask(अक्षर qdepth[], माप_प्रकार max_adapters)
अणु
	काष्ठा zcrypt_card *zc;
	काष्ठा zcrypt_queue *zq;
	पूर्णांक card;

	स_रखो(qdepth, 0, max_adapters);
	spin_lock(&zcrypt_list_lock);
	local_bh_disable();
	क्रम_each_zcrypt_card(zc) अणु
		क्रम_each_zcrypt_queue(zq, zc) अणु
			card = AP_QID_CARD(zq->queue->qid);
			अगर (AP_QID_QUEUE(zq->queue->qid) != ap_करोमुख्य_index
			    || card >= max_adapters)
				जारी;
			spin_lock(&zq->queue->lock);
			qdepth[card] =
				zq->queue->pendingq_count +
				zq->queue->requestq_count;
			spin_unlock(&zq->queue->lock);
		पूर्ण
	पूर्ण
	local_bh_enable();
	spin_unlock(&zcrypt_list_lock);
पूर्ण

अटल व्योम zcrypt_perdev_reqcnt(u32 reqcnt[], माप_प्रकार max_adapters)
अणु
	काष्ठा zcrypt_card *zc;
	काष्ठा zcrypt_queue *zq;
	पूर्णांक card;
	u64 cnt;

	स_रखो(reqcnt, 0, माप(पूर्णांक) * max_adapters);
	spin_lock(&zcrypt_list_lock);
	local_bh_disable();
	क्रम_each_zcrypt_card(zc) अणु
		क्रम_each_zcrypt_queue(zq, zc) अणु
			card = AP_QID_CARD(zq->queue->qid);
			अगर (AP_QID_QUEUE(zq->queue->qid) != ap_करोमुख्य_index
			    || card >= max_adapters)
				जारी;
			spin_lock(&zq->queue->lock);
			cnt = zq->queue->total_request_count;
			spin_unlock(&zq->queue->lock);
			reqcnt[card] = (cnt < अच_पूर्णांक_उच्च) ? (u32) cnt : अच_पूर्णांक_उच्च;
		पूर्ण
	पूर्ण
	local_bh_enable();
	spin_unlock(&zcrypt_list_lock);
पूर्ण

अटल पूर्णांक zcrypt_pendingq_count(व्योम)
अणु
	काष्ठा zcrypt_card *zc;
	काष्ठा zcrypt_queue *zq;
	पूर्णांक pendingq_count;

	pendingq_count = 0;
	spin_lock(&zcrypt_list_lock);
	local_bh_disable();
	क्रम_each_zcrypt_card(zc) अणु
		क्रम_each_zcrypt_queue(zq, zc) अणु
			अगर (AP_QID_QUEUE(zq->queue->qid) != ap_करोमुख्य_index)
				जारी;
			spin_lock(&zq->queue->lock);
			pendingq_count += zq->queue->pendingq_count;
			spin_unlock(&zq->queue->lock);
		पूर्ण
	पूर्ण
	local_bh_enable();
	spin_unlock(&zcrypt_list_lock);
	वापस pendingq_count;
पूर्ण

अटल पूर्णांक zcrypt_requestq_count(व्योम)
अणु
	काष्ठा zcrypt_card *zc;
	काष्ठा zcrypt_queue *zq;
	पूर्णांक requestq_count;

	requestq_count = 0;
	spin_lock(&zcrypt_list_lock);
	local_bh_disable();
	क्रम_each_zcrypt_card(zc) अणु
		क्रम_each_zcrypt_queue(zq, zc) अणु
			अगर (AP_QID_QUEUE(zq->queue->qid) != ap_करोमुख्य_index)
				जारी;
			spin_lock(&zq->queue->lock);
			requestq_count += zq->queue->requestq_count;
			spin_unlock(&zq->queue->lock);
		पूर्ण
	पूर्ण
	local_bh_enable();
	spin_unlock(&zcrypt_list_lock);
	वापस requestq_count;
पूर्ण

अटल पूर्णांक icarsamodexpo_ioctl(काष्ठा ap_perms *perms, अचिन्हित दीर्घ arg)
अणु
	पूर्णांक rc;
	काष्ठा zcrypt_track tr;
	काष्ठा ica_rsa_modexpo mex;
	काष्ठा ica_rsa_modexpo __user *umex = (व्योम __user *) arg;

	स_रखो(&tr, 0, माप(tr));
	अगर (copy_from_user(&mex, umex, माप(mex)))
		वापस -EFAULT;

#अगर_घोषित CONFIG_ZCRYPT_DEBUG
	अगर (mex.inputdatalength & (1U << 31)) अणु
		अगर (!capable(CAP_SYS_ADMIN))
			वापस -EPERM;
		tr.fi.cmd = (u16)(mex.inputdatalength >> 16);
	पूर्ण
	mex.inputdatalength &= 0x0000FFFF;
#पूर्ण_अगर

	करो अणु
		rc = zcrypt_rsa_modexpo(perms, &tr, &mex);
		अगर (rc == -EAGAIN)
			tr.again_counter++;
#अगर_घोषित CONFIG_ZCRYPT_DEBUG
		अगर (rc == -EAGAIN && (tr.fi.flags & AP_FI_FLAG_NO_RETRY))
			अवरोध;
#पूर्ण_अगर
	पूर्ण जबतक (rc == -EAGAIN && tr.again_counter < TRACK_AGAIN_MAX);
	/* on failure: retry once again after a requested rescan */
	अगर ((rc == -ENODEV) && (zcrypt_process_rescan()))
		करो अणु
			rc = zcrypt_rsa_modexpo(perms, &tr, &mex);
			अगर (rc == -EAGAIN)
				tr.again_counter++;
		पूर्ण जबतक (rc == -EAGAIN && tr.again_counter < TRACK_AGAIN_MAX);
	अगर (rc == -EAGAIN && tr.again_counter >= TRACK_AGAIN_MAX)
		rc = -EIO;
	अगर (rc) अणु
		ZCRYPT_DBF(DBF_DEBUG, "ioctl ICARSAMODEXPO rc=%d\n", rc);
		वापस rc;
	पूर्ण
	वापस put_user(mex.outputdatalength, &umex->outputdatalength);
पूर्ण

अटल पूर्णांक icarsacrt_ioctl(काष्ठा ap_perms *perms, अचिन्हित दीर्घ arg)
अणु
	पूर्णांक rc;
	काष्ठा zcrypt_track tr;
	काष्ठा ica_rsa_modexpo_crt crt;
	काष्ठा ica_rsa_modexpo_crt __user *ucrt = (व्योम __user *) arg;

	स_रखो(&tr, 0, माप(tr));
	अगर (copy_from_user(&crt, ucrt, माप(crt)))
		वापस -EFAULT;

#अगर_घोषित CONFIG_ZCRYPT_DEBUG
	अगर (crt.inputdatalength & (1U << 31)) अणु
		अगर (!capable(CAP_SYS_ADMIN))
			वापस -EPERM;
		tr.fi.cmd = (u16)(crt.inputdatalength >> 16);
	पूर्ण
	crt.inputdatalength &= 0x0000FFFF;
#पूर्ण_अगर

	करो अणु
		rc = zcrypt_rsa_crt(perms, &tr, &crt);
		अगर (rc == -EAGAIN)
			tr.again_counter++;
#अगर_घोषित CONFIG_ZCRYPT_DEBUG
		अगर (rc == -EAGAIN && (tr.fi.flags & AP_FI_FLAG_NO_RETRY))
			अवरोध;
#पूर्ण_अगर
	पूर्ण जबतक (rc == -EAGAIN && tr.again_counter < TRACK_AGAIN_MAX);
	/* on failure: retry once again after a requested rescan */
	अगर ((rc == -ENODEV) && (zcrypt_process_rescan()))
		करो अणु
			rc = zcrypt_rsa_crt(perms, &tr, &crt);
			अगर (rc == -EAGAIN)
				tr.again_counter++;
		पूर्ण जबतक (rc == -EAGAIN && tr.again_counter < TRACK_AGAIN_MAX);
	अगर (rc == -EAGAIN && tr.again_counter >= TRACK_AGAIN_MAX)
		rc = -EIO;
	अगर (rc) अणु
		ZCRYPT_DBF(DBF_DEBUG, "ioctl ICARSACRT rc=%d\n", rc);
		वापस rc;
	पूर्ण
	वापस put_user(crt.outputdatalength, &ucrt->outputdatalength);
पूर्ण

अटल पूर्णांक zsecsendcprb_ioctl(काष्ठा ap_perms *perms, अचिन्हित दीर्घ arg)
अणु
	पूर्णांक rc;
	काष्ठा ica_xcRB xcRB;
	काष्ठा zcrypt_track tr;
	काष्ठा ica_xcRB __user *uxcRB = (व्योम __user *) arg;

	स_रखो(&tr, 0, माप(tr));
	अगर (copy_from_user(&xcRB, uxcRB, माप(xcRB)))
		वापस -EFAULT;

#अगर_घोषित CONFIG_ZCRYPT_DEBUG
	अगर (xcRB.status & (1U << 31)) अणु
		अगर (!capable(CAP_SYS_ADMIN))
			वापस -EPERM;
		tr.fi.cmd = (u16)(xcRB.status >> 16);
	पूर्ण
	xcRB.status &= 0x0000FFFF;
#पूर्ण_अगर

	करो अणु
		rc = _zcrypt_send_cprb(true, perms, &tr, &xcRB);
		अगर (rc == -EAGAIN)
			tr.again_counter++;
#अगर_घोषित CONFIG_ZCRYPT_DEBUG
		अगर (rc == -EAGAIN && (tr.fi.flags & AP_FI_FLAG_NO_RETRY))
			अवरोध;
#पूर्ण_अगर
	पूर्ण जबतक (rc == -EAGAIN && tr.again_counter < TRACK_AGAIN_MAX);
	/* on failure: retry once again after a requested rescan */
	अगर ((rc == -ENODEV) && (zcrypt_process_rescan()))
		करो अणु
			rc = _zcrypt_send_cprb(true, perms, &tr, &xcRB);
			अगर (rc == -EAGAIN)
				tr.again_counter++;
		पूर्ण जबतक (rc == -EAGAIN && tr.again_counter < TRACK_AGAIN_MAX);
	अगर (rc == -EAGAIN && tr.again_counter >= TRACK_AGAIN_MAX)
		rc = -EIO;
	अगर (rc)
		ZCRYPT_DBF(DBF_DEBUG, "ioctl ZSENDCPRB rc=%d status=0x%x\n",
			   rc, xcRB.status);
	अगर (copy_to_user(uxcRB, &xcRB, माप(xcRB)))
		वापस -EFAULT;
	वापस rc;
पूर्ण

अटल पूर्णांक zsendep11cprb_ioctl(काष्ठा ap_perms *perms, अचिन्हित दीर्घ arg)
अणु
	पूर्णांक rc;
	काष्ठा ep11_urb xcrb;
	काष्ठा zcrypt_track tr;
	काष्ठा ep11_urb __user *uxcrb = (व्योम __user *)arg;

	स_रखो(&tr, 0, माप(tr));
	अगर (copy_from_user(&xcrb, uxcrb, माप(xcrb)))
		वापस -EFAULT;

#अगर_घोषित CONFIG_ZCRYPT_DEBUG
	अगर (xcrb.req_len & (1ULL << 63)) अणु
		अगर (!capable(CAP_SYS_ADMIN))
			वापस -EPERM;
		tr.fi.cmd = (u16)(xcrb.req_len >> 48);
	पूर्ण
	xcrb.req_len &= 0x0000FFFFFFFFFFFFULL;
#पूर्ण_अगर

	करो अणु
		rc = _zcrypt_send_ep11_cprb(true, perms, &tr, &xcrb);
		अगर (rc == -EAGAIN)
			tr.again_counter++;
#अगर_घोषित CONFIG_ZCRYPT_DEBUG
		अगर (rc == -EAGAIN && (tr.fi.flags & AP_FI_FLAG_NO_RETRY))
			अवरोध;
#पूर्ण_अगर
	पूर्ण जबतक (rc == -EAGAIN && tr.again_counter < TRACK_AGAIN_MAX);
	/* on failure: retry once again after a requested rescan */
	अगर ((rc == -ENODEV) && (zcrypt_process_rescan()))
		करो अणु
			rc = _zcrypt_send_ep11_cprb(true, perms, &tr, &xcrb);
			अगर (rc == -EAGAIN)
				tr.again_counter++;
		पूर्ण जबतक (rc == -EAGAIN && tr.again_counter < TRACK_AGAIN_MAX);
	अगर (rc == -EAGAIN && tr.again_counter >= TRACK_AGAIN_MAX)
		rc = -EIO;
	अगर (rc)
		ZCRYPT_DBF(DBF_DEBUG, "ioctl ZSENDEP11CPRB rc=%d\n", rc);
	अगर (copy_to_user(uxcrb, &xcrb, माप(xcrb)))
		वापस -EFAULT;
	वापस rc;
पूर्ण

अटल दीर्घ zcrypt_unlocked_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd,
				  अचिन्हित दीर्घ arg)
अणु
	पूर्णांक rc;
	काष्ठा ap_perms *perms =
		(काष्ठा ap_perms *) filp->निजी_data;

	rc = zcrypt_check_ioctl(perms, cmd);
	अगर (rc)
		वापस rc;

	चयन (cmd) अणु
	हाल ICARSAMODEXPO:
		वापस icarsamodexpo_ioctl(perms, arg);
	हाल ICARSACRT:
		वापस icarsacrt_ioctl(perms, arg);
	हाल ZSECSENDCPRB:
		वापस zsecsendcprb_ioctl(perms, arg);
	हाल ZSENDEP11CPRB:
		वापस zsendep11cprb_ioctl(perms, arg);
	हाल ZCRYPT_DEVICE_STATUS: अणु
		काष्ठा zcrypt_device_status_ext *device_status;
		माप_प्रकार total_size = MAX_ZDEV_ENTRIES_EXT
			* माप(काष्ठा zcrypt_device_status_ext);

		device_status = kzalloc(total_size, GFP_KERNEL);
		अगर (!device_status)
			वापस -ENOMEM;
		zcrypt_device_status_mask_ext(device_status);
		अगर (copy_to_user((अक्षर __user *) arg, device_status,
				 total_size))
			rc = -EFAULT;
		kमुक्त(device_status);
		वापस rc;
	पूर्ण
	हाल ZCRYPT_STATUS_MASK: अणु
		अक्षर status[AP_DEVICES];

		zcrypt_status_mask(status, AP_DEVICES);
		अगर (copy_to_user((अक्षर __user *) arg, status, माप(status)))
			वापस -EFAULT;
		वापस 0;
	पूर्ण
	हाल ZCRYPT_QDEPTH_MASK: अणु
		अक्षर qdepth[AP_DEVICES];

		zcrypt_qdepth_mask(qdepth, AP_DEVICES);
		अगर (copy_to_user((अक्षर __user *) arg, qdepth, माप(qdepth)))
			वापस -EFAULT;
		वापस 0;
	पूर्ण
	हाल ZCRYPT_PERDEV_REQCNT: अणु
		u32 *reqcnt;

		reqcnt = kसुस्मृति(AP_DEVICES, माप(u32), GFP_KERNEL);
		अगर (!reqcnt)
			वापस -ENOMEM;
		zcrypt_perdev_reqcnt(reqcnt, AP_DEVICES);
		अगर (copy_to_user((पूर्णांक __user *) arg, reqcnt,
				 माप(u32) * AP_DEVICES))
			rc = -EFAULT;
		kमुक्त(reqcnt);
		वापस rc;
	पूर्ण
	हाल Z90STAT_REQUESTQ_COUNT:
		वापस put_user(zcrypt_requestq_count(), (पूर्णांक __user *) arg);
	हाल Z90STAT_PENDINGQ_COUNT:
		वापस put_user(zcrypt_pendingq_count(), (पूर्णांक __user *) arg);
	हाल Z90STAT_TOTALOPEN_COUNT:
		वापस put_user(atomic_पढ़ो(&zcrypt_खोलो_count),
				(पूर्णांक __user *) arg);
	हाल Z90STAT_DOMAIN_INDEX:
		वापस put_user(ap_करोमुख्य_index, (पूर्णांक __user *) arg);
	/*
	 * Deprecated ioctls
	 */
	हाल ZDEVICESTATUS: अणु
		/* the old ioctl supports only 64 adapters */
		काष्ठा zcrypt_device_status *device_status;
		माप_प्रकार total_size = MAX_ZDEV_ENTRIES
			* माप(काष्ठा zcrypt_device_status);

		device_status = kzalloc(total_size, GFP_KERNEL);
		अगर (!device_status)
			वापस -ENOMEM;
		zcrypt_device_status_mask(device_status);
		अगर (copy_to_user((अक्षर __user *) arg, device_status,
				 total_size))
			rc = -EFAULT;
		kमुक्त(device_status);
		वापस rc;
	पूर्ण
	हाल Z90STAT_STATUS_MASK: अणु
		/* the old ioctl supports only 64 adapters */
		अक्षर status[MAX_ZDEV_CARDIDS];

		zcrypt_status_mask(status, MAX_ZDEV_CARDIDS);
		अगर (copy_to_user((अक्षर __user *) arg, status, माप(status)))
			वापस -EFAULT;
		वापस 0;
	पूर्ण
	हाल Z90STAT_QDEPTH_MASK: अणु
		/* the old ioctl supports only 64 adapters */
		अक्षर qdepth[MAX_ZDEV_CARDIDS];

		zcrypt_qdepth_mask(qdepth, MAX_ZDEV_CARDIDS);
		अगर (copy_to_user((अक्षर __user *) arg, qdepth, माप(qdepth)))
			वापस -EFAULT;
		वापस 0;
	पूर्ण
	हाल Z90STAT_PERDEV_REQCNT: अणु
		/* the old ioctl supports only 64 adapters */
		u32 reqcnt[MAX_ZDEV_CARDIDS];

		zcrypt_perdev_reqcnt(reqcnt, MAX_ZDEV_CARDIDS);
		अगर (copy_to_user((पूर्णांक __user *) arg, reqcnt, माप(reqcnt)))
			वापस -EFAULT;
		वापस 0;
	पूर्ण
	/* unknown ioctl number */
	शेष:
		ZCRYPT_DBF(DBF_DEBUG, "unknown ioctl 0x%08x\n", cmd);
		वापस -ENOIOCTLCMD;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_COMPAT
/*
 * ioctl32 conversion routines
 */
काष्ठा compat_ica_rsa_modexpo अणु
	compat_uptr_t	inputdata;
	अचिन्हित पूर्णांक	inputdatalength;
	compat_uptr_t	outputdata;
	अचिन्हित पूर्णांक	outputdatalength;
	compat_uptr_t	b_key;
	compat_uptr_t	n_modulus;
पूर्ण;

अटल दीर्घ trans_modexpo32(काष्ठा ap_perms *perms, काष्ठा file *filp,
			    अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा compat_ica_rsa_modexpo __user *umex32 = compat_ptr(arg);
	काष्ठा compat_ica_rsa_modexpo mex32;
	काष्ठा ica_rsa_modexpo mex64;
	काष्ठा zcrypt_track tr;
	दीर्घ rc;

	स_रखो(&tr, 0, माप(tr));
	अगर (copy_from_user(&mex32, umex32, माप(mex32)))
		वापस -EFAULT;
	mex64.inputdata = compat_ptr(mex32.inputdata);
	mex64.inputdatalength = mex32.inputdatalength;
	mex64.outputdata = compat_ptr(mex32.outputdata);
	mex64.outputdatalength = mex32.outputdatalength;
	mex64.b_key = compat_ptr(mex32.b_key);
	mex64.n_modulus = compat_ptr(mex32.n_modulus);
	करो अणु
		rc = zcrypt_rsa_modexpo(perms, &tr, &mex64);
		अगर (rc == -EAGAIN)
			tr.again_counter++;
	पूर्ण जबतक (rc == -EAGAIN && tr.again_counter < TRACK_AGAIN_MAX);
	/* on failure: retry once again after a requested rescan */
	अगर ((rc == -ENODEV) && (zcrypt_process_rescan()))
		करो अणु
			rc = zcrypt_rsa_modexpo(perms, &tr, &mex64);
			अगर (rc == -EAGAIN)
				tr.again_counter++;
		पूर्ण जबतक (rc == -EAGAIN && tr.again_counter < TRACK_AGAIN_MAX);
	अगर (rc == -EAGAIN && tr.again_counter >= TRACK_AGAIN_MAX)
		rc = -EIO;
	अगर (rc)
		वापस rc;
	वापस put_user(mex64.outputdatalength,
			&umex32->outputdatalength);
पूर्ण

काष्ठा compat_ica_rsa_modexpo_crt अणु
	compat_uptr_t	inputdata;
	अचिन्हित पूर्णांक	inputdatalength;
	compat_uptr_t	outputdata;
	अचिन्हित पूर्णांक	outputdatalength;
	compat_uptr_t	bp_key;
	compat_uptr_t	bq_key;
	compat_uptr_t	np_prime;
	compat_uptr_t	nq_prime;
	compat_uptr_t	u_mult_inv;
पूर्ण;

अटल दीर्घ trans_modexpo_crt32(काष्ठा ap_perms *perms, काष्ठा file *filp,
				अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा compat_ica_rsa_modexpo_crt __user *ucrt32 = compat_ptr(arg);
	काष्ठा compat_ica_rsa_modexpo_crt crt32;
	काष्ठा ica_rsa_modexpo_crt crt64;
	काष्ठा zcrypt_track tr;
	दीर्घ rc;

	स_रखो(&tr, 0, माप(tr));
	अगर (copy_from_user(&crt32, ucrt32, माप(crt32)))
		वापस -EFAULT;
	crt64.inputdata = compat_ptr(crt32.inputdata);
	crt64.inputdatalength = crt32.inputdatalength;
	crt64.outputdata = compat_ptr(crt32.outputdata);
	crt64.outputdatalength = crt32.outputdatalength;
	crt64.bp_key = compat_ptr(crt32.bp_key);
	crt64.bq_key = compat_ptr(crt32.bq_key);
	crt64.np_prime = compat_ptr(crt32.np_prime);
	crt64.nq_prime = compat_ptr(crt32.nq_prime);
	crt64.u_mult_inv = compat_ptr(crt32.u_mult_inv);
	करो अणु
		rc = zcrypt_rsa_crt(perms, &tr, &crt64);
		अगर (rc == -EAGAIN)
			tr.again_counter++;
	पूर्ण जबतक (rc == -EAGAIN && tr.again_counter < TRACK_AGAIN_MAX);
	/* on failure: retry once again after a requested rescan */
	अगर ((rc == -ENODEV) && (zcrypt_process_rescan()))
		करो अणु
			rc = zcrypt_rsa_crt(perms, &tr, &crt64);
			अगर (rc == -EAGAIN)
				tr.again_counter++;
		पूर्ण जबतक (rc == -EAGAIN && tr.again_counter < TRACK_AGAIN_MAX);
	अगर (rc == -EAGAIN && tr.again_counter >= TRACK_AGAIN_MAX)
		rc = -EIO;
	अगर (rc)
		वापस rc;
	वापस put_user(crt64.outputdatalength,
			&ucrt32->outputdatalength);
पूर्ण

काष्ठा compat_ica_xcRB अणु
	अचिन्हित लघु	agent_ID;
	अचिन्हित पूर्णांक	user_defined;
	अचिन्हित लघु	request_ID;
	अचिन्हित पूर्णांक	request_control_blk_length;
	अचिन्हित अक्षर	padding1[16 - माप(compat_uptr_t)];
	compat_uptr_t	request_control_blk_addr;
	अचिन्हित पूर्णांक	request_data_length;
	अक्षर		padding2[16 - माप(compat_uptr_t)];
	compat_uptr_t	request_data_address;
	अचिन्हित पूर्णांक	reply_control_blk_length;
	अक्षर		padding3[16 - माप(compat_uptr_t)];
	compat_uptr_t	reply_control_blk_addr;
	अचिन्हित पूर्णांक	reply_data_length;
	अक्षर		padding4[16 - माप(compat_uptr_t)];
	compat_uptr_t	reply_data_addr;
	अचिन्हित लघु	priority_winकरोw;
	अचिन्हित पूर्णांक	status;
पूर्ण __packed;

अटल दीर्घ trans_xcRB32(काष्ठा ap_perms *perms, काष्ठा file *filp,
			 अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा compat_ica_xcRB __user *uxcRB32 = compat_ptr(arg);
	काष्ठा compat_ica_xcRB xcRB32;
	काष्ठा zcrypt_track tr;
	काष्ठा ica_xcRB xcRB64;
	दीर्घ rc;

	स_रखो(&tr, 0, माप(tr));
	अगर (copy_from_user(&xcRB32, uxcRB32, माप(xcRB32)))
		वापस -EFAULT;
	xcRB64.agent_ID = xcRB32.agent_ID;
	xcRB64.user_defined = xcRB32.user_defined;
	xcRB64.request_ID = xcRB32.request_ID;
	xcRB64.request_control_blk_length =
		xcRB32.request_control_blk_length;
	xcRB64.request_control_blk_addr =
		compat_ptr(xcRB32.request_control_blk_addr);
	xcRB64.request_data_length =
		xcRB32.request_data_length;
	xcRB64.request_data_address =
		compat_ptr(xcRB32.request_data_address);
	xcRB64.reply_control_blk_length =
		xcRB32.reply_control_blk_length;
	xcRB64.reply_control_blk_addr =
		compat_ptr(xcRB32.reply_control_blk_addr);
	xcRB64.reply_data_length = xcRB32.reply_data_length;
	xcRB64.reply_data_addr =
		compat_ptr(xcRB32.reply_data_addr);
	xcRB64.priority_winकरोw = xcRB32.priority_winकरोw;
	xcRB64.status = xcRB32.status;
	करो अणु
		rc = _zcrypt_send_cprb(true, perms, &tr, &xcRB64);
		अगर (rc == -EAGAIN)
			tr.again_counter++;
	पूर्ण जबतक (rc == -EAGAIN && tr.again_counter < TRACK_AGAIN_MAX);
	/* on failure: retry once again after a requested rescan */
	अगर ((rc == -ENODEV) && (zcrypt_process_rescan()))
		करो अणु
			rc = _zcrypt_send_cprb(true, perms, &tr, &xcRB64);
			अगर (rc == -EAGAIN)
				tr.again_counter++;
		पूर्ण जबतक (rc == -EAGAIN && tr.again_counter < TRACK_AGAIN_MAX);
	अगर (rc == -EAGAIN && tr.again_counter >= TRACK_AGAIN_MAX)
		rc = -EIO;
	xcRB32.reply_control_blk_length = xcRB64.reply_control_blk_length;
	xcRB32.reply_data_length = xcRB64.reply_data_length;
	xcRB32.status = xcRB64.status;
	अगर (copy_to_user(uxcRB32, &xcRB32, माप(xcRB32)))
		वापस -EFAULT;
	वापस rc;
पूर्ण

अटल दीर्घ zcrypt_compat_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd,
			 अचिन्हित दीर्घ arg)
अणु
	पूर्णांक rc;
	काष्ठा ap_perms *perms =
		(काष्ठा ap_perms *) filp->निजी_data;

	rc = zcrypt_check_ioctl(perms, cmd);
	अगर (rc)
		वापस rc;

	अगर (cmd == ICARSAMODEXPO)
		वापस trans_modexpo32(perms, filp, cmd, arg);
	अगर (cmd == ICARSACRT)
		वापस trans_modexpo_crt32(perms, filp, cmd, arg);
	अगर (cmd == ZSECSENDCPRB)
		वापस trans_xcRB32(perms, filp, cmd, arg);
	वापस zcrypt_unlocked_ioctl(filp, cmd, arg);
पूर्ण
#पूर्ण_अगर

/*
 * Misc device file operations.
 */
अटल स्थिर काष्ठा file_operations zcrypt_fops = अणु
	.owner		= THIS_MODULE,
	.पढ़ो		= zcrypt_पढ़ो,
	.ग_लिखो		= zcrypt_ग_लिखो,
	.unlocked_ioctl	= zcrypt_unlocked_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl	= zcrypt_compat_ioctl,
#पूर्ण_अगर
	.खोलो		= zcrypt_खोलो,
	.release	= zcrypt_release,
	.llseek		= no_llseek,
पूर्ण;

/*
 * Misc device.
 */
अटल काष्ठा miscdevice zcrypt_misc_device = अणु
	.minor	    = MISC_DYNAMIC_MINOR,
	.name	    = "z90crypt",
	.fops	    = &zcrypt_fops,
पूर्ण;

अटल पूर्णांक zcrypt_rng_device_count;
अटल u32 *zcrypt_rng_buffer;
अटल पूर्णांक zcrypt_rng_buffer_index;
अटल DEFINE_MUTEX(zcrypt_rng_mutex);

अटल पूर्णांक zcrypt_rng_data_पढ़ो(काष्ठा hwrng *rng, u32 *data)
अणु
	पूर्णांक rc;

	/*
	 * We करोn't need locking here because the RNG API guarantees serialized
	 * पढ़ो method calls.
	 */
	अगर (zcrypt_rng_buffer_index == 0) अणु
		rc = zcrypt_rng((अक्षर *) zcrypt_rng_buffer);
		/* on failure: retry once again after a requested rescan */
		अगर ((rc == -ENODEV) && (zcrypt_process_rescan()))
			rc = zcrypt_rng((अक्षर *) zcrypt_rng_buffer);
		अगर (rc < 0)
			वापस -EIO;
		zcrypt_rng_buffer_index = rc / माप(*data);
	पूर्ण
	*data = zcrypt_rng_buffer[--zcrypt_rng_buffer_index];
	वापस माप(*data);
पूर्ण

अटल काष्ठा hwrng zcrypt_rng_dev = अणु
	.name		= "zcrypt",
	.data_पढ़ो	= zcrypt_rng_data_पढ़ो,
	.quality	= 990,
पूर्ण;

पूर्णांक zcrypt_rng_device_add(व्योम)
अणु
	पूर्णांक rc = 0;

	mutex_lock(&zcrypt_rng_mutex);
	अगर (zcrypt_rng_device_count == 0) अणु
		zcrypt_rng_buffer = (u32 *) get_zeroed_page(GFP_KERNEL);
		अगर (!zcrypt_rng_buffer) अणु
			rc = -ENOMEM;
			जाओ out;
		पूर्ण
		zcrypt_rng_buffer_index = 0;
		अगर (!zcrypt_hwrng_seed)
			zcrypt_rng_dev.quality = 0;
		rc = hwrng_रेजिस्टर(&zcrypt_rng_dev);
		अगर (rc)
			जाओ out_मुक्त;
		zcrypt_rng_device_count = 1;
	पूर्ण अन्यथा
		zcrypt_rng_device_count++;
	mutex_unlock(&zcrypt_rng_mutex);
	वापस 0;

out_मुक्त:
	मुक्त_page((अचिन्हित दीर्घ) zcrypt_rng_buffer);
out:
	mutex_unlock(&zcrypt_rng_mutex);
	वापस rc;
पूर्ण

व्योम zcrypt_rng_device_हटाओ(व्योम)
अणु
	mutex_lock(&zcrypt_rng_mutex);
	zcrypt_rng_device_count--;
	अगर (zcrypt_rng_device_count == 0) अणु
		hwrng_unरेजिस्टर(&zcrypt_rng_dev);
		मुक्त_page((अचिन्हित दीर्घ) zcrypt_rng_buffer);
	पूर्ण
	mutex_unlock(&zcrypt_rng_mutex);
पूर्ण

/*
 * Wait until the zcrypt api is operational.
 * The AP bus scan and the binding of ap devices to device drivers is
 * an asynchronous job. This function रुकोs until these initial jobs
 * are करोne and so the zcrypt api should be पढ़ोy to serve crypto
 * requests - अगर there are resources available. The function uses an
 * पूर्णांकernal समयout of 60s. The very first caller will either रुको क्रम
 * ap bus bindings complete or the समयout happens. This state will be
 * remembered क्रम further callers which will only be blocked until a
 * decision is made (समयout or bindings complete).
 * On समयout -ETIME is वापसed, on success the वापस value is 0.
 */
पूर्णांक zcrypt_रुको_api_operational(व्योम)
अणु
	अटल DEFINE_MUTEX(zcrypt_रुको_api_lock);
	अटल पूर्णांक zcrypt_रुको_api_state;
	पूर्णांक rc;

	rc = mutex_lock_पूर्णांकerruptible(&zcrypt_रुको_api_lock);
	अगर (rc)
		वापस rc;

	चयन (zcrypt_रुको_api_state) अणु
	हाल 0:
		/* initial state, invoke रुको क्रम the ap bus complete */
		rc = ap_रुको_init_apqn_bindings_complete(
			msecs_to_jअगरfies(60 * 1000));
		चयन (rc) अणु
		हाल 0:
			/* ap bus bindings are complete */
			zcrypt_रुको_api_state = 1;
			अवरोध;
		हाल -EINTR:
			/* पूर्णांकerrupted, go back to caller */
			अवरोध;
		हाल -ETIME:
			/* समयout */
			ZCRYPT_DBF(DBF_WARN,
				   "%s ap_wait_init_apqn_bindings_complete() returned with ETIME\n",
				   __func__);
			zcrypt_रुको_api_state = -ETIME;
			अवरोध;
		शेष:
			/* other failure */
			ZCRYPT_DBF(DBF_DEBUG,
				   "%s ap_wait_init_apqn_bindings_complete() failure rc=%d\n",
				   __func__, rc);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल 1:
		/* a previous caller alपढ़ोy found ap bus bindings complete */
		rc = 0;
		अवरोध;
	शेष:
		/* a previous caller had समयout or other failure */
		rc = zcrypt_रुको_api_state;
		अवरोध;
	पूर्ण

	mutex_unlock(&zcrypt_रुको_api_lock);

	वापस rc;
पूर्ण
EXPORT_SYMBOL(zcrypt_रुको_api_operational);

पूर्णांक __init zcrypt_debug_init(व्योम)
अणु
	zcrypt_dbf_info = debug_रेजिस्टर("zcrypt", 1, 1,
					 DBF_MAX_SPRINTF_ARGS * माप(दीर्घ));
	debug_रेजिस्टर_view(zcrypt_dbf_info, &debug_प्र_लिखो_view);
	debug_set_level(zcrypt_dbf_info, DBF_ERR);

	वापस 0;
पूर्ण

व्योम zcrypt_debug_निकास(व्योम)
अणु
	debug_unरेजिस्टर(zcrypt_dbf_info);
पूर्ण

#अगर_घोषित CONFIG_ZCRYPT_MULTIDEVNODES

अटल पूर्णांक __init zcdn_init(व्योम)
अणु
	पूर्णांक rc;

	/* create a new class 'zcrypt' */
	zcrypt_class = class_create(THIS_MODULE, ZCRYPT_NAME);
	अगर (IS_ERR(zcrypt_class)) अणु
		rc = PTR_ERR(zcrypt_class);
		जाओ out_class_create_failed;
	पूर्ण
	zcrypt_class->dev_release = zcdn_device_release;

	/* alloc device minor range */
	rc = alloc_chrdev_region(&zcrypt_devt,
				 0, ZCRYPT_MAX_MINOR_NODES,
				 ZCRYPT_NAME);
	अगर (rc)
		जाओ out_alloc_chrdev_failed;

	cdev_init(&zcrypt_cdev, &zcrypt_fops);
	zcrypt_cdev.owner = THIS_MODULE;
	rc = cdev_add(&zcrypt_cdev, zcrypt_devt, ZCRYPT_MAX_MINOR_NODES);
	अगर (rc)
		जाओ out_cdev_add_failed;

	/* need some class specअगरic sysfs attributes */
	rc = class_create_file(zcrypt_class, &class_attr_zcdn_create);
	अगर (rc)
		जाओ out_class_create_file_1_failed;
	rc = class_create_file(zcrypt_class, &class_attr_zcdn_destroy);
	अगर (rc)
		जाओ out_class_create_file_2_failed;

	वापस 0;

out_class_create_file_2_failed:
	class_हटाओ_file(zcrypt_class, &class_attr_zcdn_create);
out_class_create_file_1_failed:
	cdev_del(&zcrypt_cdev);
out_cdev_add_failed:
	unरेजिस्टर_chrdev_region(zcrypt_devt, ZCRYPT_MAX_MINOR_NODES);
out_alloc_chrdev_failed:
	class_destroy(zcrypt_class);
out_class_create_failed:
	वापस rc;
पूर्ण

अटल व्योम zcdn_निकास(व्योम)
अणु
	class_हटाओ_file(zcrypt_class, &class_attr_zcdn_create);
	class_हटाओ_file(zcrypt_class, &class_attr_zcdn_destroy);
	zcdn_destroy_all();
	cdev_del(&zcrypt_cdev);
	unरेजिस्टर_chrdev_region(zcrypt_devt, ZCRYPT_MAX_MINOR_NODES);
	class_destroy(zcrypt_class);
पूर्ण

#पूर्ण_अगर

/**
 * zcrypt_api_init(): Module initialization.
 *
 * The module initialization code.
 */
पूर्णांक __init zcrypt_api_init(व्योम)
अणु
	पूर्णांक rc;

	rc = zcrypt_debug_init();
	अगर (rc)
		जाओ out;

#अगर_घोषित CONFIG_ZCRYPT_MULTIDEVNODES
	rc = zcdn_init();
	अगर (rc)
		जाओ out;
#पूर्ण_अगर

	/* Register the request sprayer. */
	rc = misc_रेजिस्टर(&zcrypt_misc_device);
	अगर (rc < 0)
		जाओ out_misc_रेजिस्टर_failed;

	zcrypt_msgtype6_init();
	zcrypt_msgtype50_init();

	वापस 0;

out_misc_रेजिस्टर_failed:
#अगर_घोषित CONFIG_ZCRYPT_MULTIDEVNODES
	zcdn_निकास();
#पूर्ण_अगर
	zcrypt_debug_निकास();
out:
	वापस rc;
पूर्ण

/**
 * zcrypt_api_निकास(): Module termination.
 *
 * The module termination code.
 */
व्योम __निकास zcrypt_api_निकास(व्योम)
अणु
#अगर_घोषित CONFIG_ZCRYPT_MULTIDEVNODES
	zcdn_निकास();
#पूर्ण_अगर
	misc_deरेजिस्टर(&zcrypt_misc_device);
	zcrypt_msgtype6_निकास();
	zcrypt_msgtype50_निकास();
	zcrypt_ccamisc_निकास();
	zcrypt_ep11misc_निकास();
	zcrypt_debug_निकास();
पूर्ण

module_init(zcrypt_api_init);
module_निकास(zcrypt_api_निकास);
