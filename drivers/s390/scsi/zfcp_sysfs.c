<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * zfcp device driver
 *
 * sysfs attributes.
 *
 * Copyright IBM Corp. 2008, 2020
 */

#घोषणा KMSG_COMPONENT "zfcp"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/slab.h>
#समावेश "zfcp_diag.h"
#समावेश "zfcp_ext.h"

#घोषणा ZFCP_DEV_ATTR(_feat, _name, _mode, _show, _store) \
काष्ठा device_attribute dev_attr_##_feat##_##_name = __ATTR(_name, _mode,\
							    _show, _store)
#घोषणा ZFCP_DEFINE_ATTR(_feat_def, _feat, _name, _क्रमmat, _value)	       \
अटल sमाप_प्रकार zfcp_sysfs_##_feat##_##_name##_show(काष्ठा device *dev,	       \
						   काष्ठा device_attribute *at,\
						   अक्षर *buf)		       \
अणु									       \
	काष्ठा _feat_def *_feat = container_of(dev, काष्ठा _feat_def, dev);    \
									       \
	वापस प्र_लिखो(buf, _क्रमmat, _value);				       \
पूर्ण									       \
अटल ZFCP_DEV_ATTR(_feat, _name, S_IRUGO,				       \
		     zfcp_sysfs_##_feat##_##_name##_show, शून्य);

#घोषणा ZFCP_DEFINE_ATTR_CONST(_feat, _name, _क्रमmat, _value)		       \
अटल sमाप_प्रकार zfcp_sysfs_##_feat##_##_name##_show(काष्ठा device *dev,	       \
						   काष्ठा device_attribute *at,\
						   अक्षर *buf)		       \
अणु									       \
	वापस प्र_लिखो(buf, _क्रमmat, _value);				       \
पूर्ण									       \
अटल ZFCP_DEV_ATTR(_feat, _name, S_IRUGO,				       \
		     zfcp_sysfs_##_feat##_##_name##_show, शून्य);

#घोषणा ZFCP_DEFINE_A_ATTR(_name, _क्रमmat, _value)			     \
अटल sमाप_प्रकार zfcp_sysfs_adapter_##_name##_show(काष्ठा device *dev,	     \
						 काष्ठा device_attribute *at,\
						 अक्षर *buf)		     \
अणु									     \
	काष्ठा ccw_device *cdev = to_ccwdev(dev);			     \
	काष्ठा zfcp_adapter *adapter = zfcp_ccw_adapter_by_cdev(cdev);	     \
	पूर्णांक i;								     \
									     \
	अगर (!adapter)							     \
		वापस -ENODEV;						     \
									     \
	i = प्र_लिखो(buf, _क्रमmat, _value);				     \
	zfcp_ccw_adapter_put(adapter);					     \
	वापस i;							     \
पूर्ण									     \
अटल ZFCP_DEV_ATTR(adapter, _name, S_IRUGO,				     \
		     zfcp_sysfs_adapter_##_name##_show, शून्य);

ZFCP_DEFINE_A_ATTR(status, "0x%08x\n", atomic_पढ़ो(&adapter->status));
ZFCP_DEFINE_A_ATTR(peer_wwnn, "0x%016llx\n",
		   (अचिन्हित दीर्घ दीर्घ) adapter->peer_wwnn);
ZFCP_DEFINE_A_ATTR(peer_wwpn, "0x%016llx\n",
		   (अचिन्हित दीर्घ दीर्घ) adapter->peer_wwpn);
ZFCP_DEFINE_A_ATTR(peer_d_id, "0x%06x\n", adapter->peer_d_id);
ZFCP_DEFINE_A_ATTR(card_version, "0x%04x\n", adapter->hydra_version);
ZFCP_DEFINE_A_ATTR(lic_version, "0x%08x\n", adapter->fsf_lic_version);
ZFCP_DEFINE_A_ATTR(hardware_version, "0x%08x\n", adapter->hardware_version);
ZFCP_DEFINE_A_ATTR(in_recovery, "%d\n", (atomic_पढ़ो(&adapter->status) &
					 ZFCP_STATUS_COMMON_ERP_INUSE) != 0);

ZFCP_DEFINE_ATTR(zfcp_port, port, status, "0x%08x\n",
		 atomic_पढ़ो(&port->status));
ZFCP_DEFINE_ATTR(zfcp_port, port, in_recovery, "%d\n",
		 (atomic_पढ़ो(&port->status) &
		  ZFCP_STATUS_COMMON_ERP_INUSE) != 0);
ZFCP_DEFINE_ATTR_CONST(port, access_denied, "%d\n", 0);

ZFCP_DEFINE_ATTR(zfcp_unit, unit, status, "0x%08x\n",
		 zfcp_unit_sdev_status(unit));
ZFCP_DEFINE_ATTR(zfcp_unit, unit, in_recovery, "%d\n",
		 (zfcp_unit_sdev_status(unit) &
		  ZFCP_STATUS_COMMON_ERP_INUSE) != 0);
ZFCP_DEFINE_ATTR(zfcp_unit, unit, access_denied, "%d\n",
		 (zfcp_unit_sdev_status(unit) &
		  ZFCP_STATUS_COMMON_ACCESS_DENIED) != 0);
ZFCP_DEFINE_ATTR_CONST(unit, access_shared, "%d\n", 0);
ZFCP_DEFINE_ATTR_CONST(unit, access_पढ़ोonly, "%d\n", 0);

अटल sमाप_प्रकार zfcp_sysfs_port_failed_show(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   अक्षर *buf)
अणु
	काष्ठा zfcp_port *port = container_of(dev, काष्ठा zfcp_port, dev);

	अगर (atomic_पढ़ो(&port->status) & ZFCP_STATUS_COMMON_ERP_FAILED)
		वापस प्र_लिखो(buf, "1\n");

	वापस प्र_लिखो(buf, "0\n");
पूर्ण

अटल sमाप_प्रकार zfcp_sysfs_port_failed_store(काष्ठा device *dev,
					    काष्ठा device_attribute *attr,
					    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा zfcp_port *port = container_of(dev, काष्ठा zfcp_port, dev);
	अचिन्हित दीर्घ val;

	अगर (kम_से_अदीर्घ(buf, 0, &val) || val != 0)
		वापस -EINVAL;

	zfcp_erp_set_port_status(port, ZFCP_STATUS_COMMON_RUNNING);
	zfcp_erp_port_reखोलो(port, ZFCP_STATUS_COMMON_ERP_FAILED, "sypfai2");
	zfcp_erp_रुको(port->adapter);

	वापस count;
पूर्ण
अटल ZFCP_DEV_ATTR(port, failed, S_IWUSR | S_IRUGO,
		     zfcp_sysfs_port_failed_show,
		     zfcp_sysfs_port_failed_store);

अटल sमाप_प्रकार zfcp_sysfs_unit_failed_show(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   अक्षर *buf)
अणु
	काष्ठा zfcp_unit *unit = container_of(dev, काष्ठा zfcp_unit, dev);
	काष्ठा scsi_device *sdev;
	अचिन्हित पूर्णांक status, failed = 1;

	sdev = zfcp_unit_sdev(unit);
	अगर (sdev) अणु
		status = atomic_पढ़ो(&sdev_to_zfcp(sdev)->status);
		failed = status & ZFCP_STATUS_COMMON_ERP_FAILED ? 1 : 0;
		scsi_device_put(sdev);
	पूर्ण

	वापस प्र_लिखो(buf, "%d\n", failed);
पूर्ण

अटल sमाप_प्रकार zfcp_sysfs_unit_failed_store(काष्ठा device *dev,
					    काष्ठा device_attribute *attr,
					    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा zfcp_unit *unit = container_of(dev, काष्ठा zfcp_unit, dev);
	अचिन्हित दीर्घ val;
	काष्ठा scsi_device *sdev;

	अगर (kम_से_अदीर्घ(buf, 0, &val) || val != 0)
		वापस -EINVAL;

	sdev = zfcp_unit_sdev(unit);
	अगर (sdev) अणु
		zfcp_erp_set_lun_status(sdev, ZFCP_STATUS_COMMON_RUNNING);
		zfcp_erp_lun_reखोलो(sdev, ZFCP_STATUS_COMMON_ERP_FAILED,
				    "syufai2");
		zfcp_erp_रुको(unit->port->adapter);
	पूर्ण अन्यथा
		zfcp_unit_scsi_scan(unit);

	वापस count;
पूर्ण
अटल ZFCP_DEV_ATTR(unit, failed, S_IWUSR | S_IRUGO,
		     zfcp_sysfs_unit_failed_show,
		     zfcp_sysfs_unit_failed_store);

अटल sमाप_प्रकार zfcp_sysfs_adapter_failed_show(काष्ठा device *dev,
					      काष्ठा device_attribute *attr,
					      अक्षर *buf)
अणु
	काष्ठा ccw_device *cdev = to_ccwdev(dev);
	काष्ठा zfcp_adapter *adapter = zfcp_ccw_adapter_by_cdev(cdev);
	पूर्णांक i;

	अगर (!adapter)
		वापस -ENODEV;

	अगर (atomic_पढ़ो(&adapter->status) & ZFCP_STATUS_COMMON_ERP_FAILED)
		i = प्र_लिखो(buf, "1\n");
	अन्यथा
		i = प्र_लिखो(buf, "0\n");

	zfcp_ccw_adapter_put(adapter);
	वापस i;
पूर्ण

अटल sमाप_प्रकार zfcp_sysfs_adapter_failed_store(काष्ठा device *dev,
					       काष्ठा device_attribute *attr,
					       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ccw_device *cdev = to_ccwdev(dev);
	काष्ठा zfcp_adapter *adapter = zfcp_ccw_adapter_by_cdev(cdev);
	अचिन्हित दीर्घ val;
	पूर्णांक retval = 0;

	अगर (!adapter)
		वापस -ENODEV;

	अगर (kम_से_अदीर्घ(buf, 0, &val) || val != 0) अणु
		retval = -EINVAL;
		जाओ out;
	पूर्ण

	zfcp_erp_adapter_reset_sync(adapter, "syafai2");
out:
	zfcp_ccw_adapter_put(adapter);
	वापस retval ? retval : (sमाप_प्रकार) count;
पूर्ण
अटल ZFCP_DEV_ATTR(adapter, failed, S_IWUSR | S_IRUGO,
		     zfcp_sysfs_adapter_failed_show,
		     zfcp_sysfs_adapter_failed_store);

अटल sमाप_प्रकार zfcp_sysfs_port_rescan_store(काष्ठा device *dev,
					    काष्ठा device_attribute *attr,
					    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ccw_device *cdev = to_ccwdev(dev);
	काष्ठा zfcp_adapter *adapter = zfcp_ccw_adapter_by_cdev(cdev);
	पूर्णांक retval = 0;

	अगर (!adapter)
		वापस -ENODEV;

	/*
	 * If `scsi_host` is missing, we can't schedule `scan_work`, as it
	 * makes use of the corresponding fc_host object. But this state is
	 * only possible अगर xconfig/xport data has never completed yet,
	 * and we couldn't successfully scan क्रम ports anyway.
	 */
	अगर (adapter->scsi_host == शून्य) अणु
		retval = -ENODEV;
		जाओ out;
	पूर्ण

	/*
	 * Users wish is our command: immediately schedule and flush a
	 * worker to conduct a synchronous port scan, that is, neither
	 * a अक्रमom delay nor a rate limit is applied here.
	 */
	queue_delayed_work(adapter->work_queue, &adapter->scan_work, 0);
	flush_delayed_work(&adapter->scan_work);
out:
	zfcp_ccw_adapter_put(adapter);
	वापस retval ? retval : (sमाप_प्रकार) count;
पूर्ण
अटल ZFCP_DEV_ATTR(adapter, port_rescan, S_IWUSR, शून्य,
		     zfcp_sysfs_port_rescan_store);

DEFINE_MUTEX(zfcp_sysfs_port_units_mutex);

अटल व्योम zfcp_sysfs_port_set_removing(काष्ठा zfcp_port *स्थिर port)
अणु
	lockdep_निश्चित_held(&zfcp_sysfs_port_units_mutex);
	atomic_set(&port->units, -1);
पूर्ण

bool zfcp_sysfs_port_is_removing(स्थिर काष्ठा zfcp_port *स्थिर port)
अणु
	lockdep_निश्चित_held(&zfcp_sysfs_port_units_mutex);
	वापस atomic_पढ़ो(&port->units) == -1;
पूर्ण

अटल bool zfcp_sysfs_port_in_use(काष्ठा zfcp_port *स्थिर port)
अणु
	काष्ठा zfcp_adapter *स्थिर adapter = port->adapter;
	अचिन्हित दीर्घ flags;
	काष्ठा scsi_device *sdev;
	bool in_use = true;

	mutex_lock(&zfcp_sysfs_port_units_mutex);
	अगर (atomic_पढ़ो(&port->units) > 0)
		जाओ unlock_port_units_mutex; /* zfcp_unit(s) under port */

	spin_lock_irqsave(adapter->scsi_host->host_lock, flags);
	__shost_क्रम_each_device(sdev, adapter->scsi_host) अणु
		स्थिर काष्ठा zfcp_scsi_dev *zsdev = sdev_to_zfcp(sdev);

		अगर (sdev->sdev_state == SDEV_DEL ||
		    sdev->sdev_state == SDEV_CANCEL)
			जारी;
		अगर (zsdev->port != port)
			जारी;
		/* alive scsi_device under port of पूर्णांकerest */
		जाओ unlock_host_lock;
	पूर्ण

	/* port is about to be हटाओd, so no more unit_add or slave_alloc */
	zfcp_sysfs_port_set_removing(port);
	in_use = false;

unlock_host_lock:
	spin_unlock_irqrestore(adapter->scsi_host->host_lock, flags);
unlock_port_units_mutex:
	mutex_unlock(&zfcp_sysfs_port_units_mutex);
	वापस in_use;
पूर्ण

अटल sमाप_प्रकार zfcp_sysfs_port_हटाओ_store(काष्ठा device *dev,
					    काष्ठा device_attribute *attr,
					    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ccw_device *cdev = to_ccwdev(dev);
	काष्ठा zfcp_adapter *adapter = zfcp_ccw_adapter_by_cdev(cdev);
	काष्ठा zfcp_port *port;
	u64 wwpn;
	पूर्णांक retval = -EINVAL;

	अगर (!adapter)
		वापस -ENODEV;

	अगर (kम_से_अदीर्घl(buf, 0, (अचिन्हित दीर्घ दीर्घ *) &wwpn))
		जाओ out;

	port = zfcp_get_port_by_wwpn(adapter, wwpn);
	अगर (!port)
		जाओ out;
	अन्यथा
		retval = 0;

	अगर (zfcp_sysfs_port_in_use(port)) अणु
		retval = -EBUSY;
		put_device(&port->dev); /* unकरो zfcp_get_port_by_wwpn() */
		जाओ out;
	पूर्ण

	ग_लिखो_lock_irq(&adapter->port_list_lock);
	list_del(&port->list);
	ग_लिखो_unlock_irq(&adapter->port_list_lock);

	zfcp_erp_port_shutकरोwn(port, 0, "syprs_1");
	device_unरेजिस्टर(&port->dev);

	put_device(&port->dev); /* unकरो zfcp_get_port_by_wwpn() */
 out:
	zfcp_ccw_adapter_put(adapter);
	वापस retval ? retval : (sमाप_प्रकार) count;
पूर्ण
अटल ZFCP_DEV_ATTR(adapter, port_हटाओ, S_IWUSR, शून्य,
		     zfcp_sysfs_port_हटाओ_store);

अटल sमाप_प्रकार
zfcp_sysfs_adapter_diag_max_age_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा zfcp_adapter *adapter = zfcp_ccw_adapter_by_cdev(to_ccwdev(dev));
	sमाप_प्रकार rc;

	अगर (!adapter)
		वापस -ENODEV;

	/* उच्चमान(log(2^64 - 1) / log(10)) = 20 */
	rc = scnम_लिखो(buf, 20 + 2, "%lu\n", adapter->diagnostics->max_age);

	zfcp_ccw_adapter_put(adapter);
	वापस rc;
पूर्ण

अटल sमाप_प्रकार
zfcp_sysfs_adapter_diag_max_age_store(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा zfcp_adapter *adapter = zfcp_ccw_adapter_by_cdev(to_ccwdev(dev));
	अचिन्हित दीर्घ max_age;
	sमाप_प्रकार rc;

	अगर (!adapter)
		वापस -ENODEV;

	rc = kम_से_अदीर्घ(buf, 10, &max_age);
	अगर (rc != 0)
		जाओ out;

	adapter->diagnostics->max_age = max_age;

	rc = count;
out:
	zfcp_ccw_adapter_put(adapter);
	वापस rc;
पूर्ण
अटल ZFCP_DEV_ATTR(adapter, diag_max_age, 0644,
		     zfcp_sysfs_adapter_diag_max_age_show,
		     zfcp_sysfs_adapter_diag_max_age_store);

अटल sमाप_प्रकार zfcp_sysfs_adapter_fc_security_show(
	काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ccw_device *cdev = to_ccwdev(dev);
	काष्ठा zfcp_adapter *adapter = zfcp_ccw_adapter_by_cdev(cdev);
	अचिन्हित पूर्णांक status;
	पूर्णांक i;

	अगर (!adapter)
		वापस -ENODEV;

	/*
	 * Adapter status COMMON_OPEN implies xconf data and xport data
	 * was करोne. Adapter FC Endpoपूर्णांक Security capability reमुख्यs
	 * unchanged in हाल of COMMON_ERP_FAILED (e.g. due to local link
	 * करोwn).
	 */
	status = atomic_पढ़ो(&adapter->status);
	अगर (0 == (status & ZFCP_STATUS_COMMON_OPEN))
		i = प्र_लिखो(buf, "unknown\n");
	अन्यथा अगर (!(adapter->adapter_features & FSF_FEATURE_FC_SECURITY))
		i = प्र_लिखो(buf, "unsupported\n");
	अन्यथा अणु
		i = zfcp_fsf_scnprपूर्णांक_fc_security(
			buf, PAGE_SIZE - 1, adapter->fc_security_algorithms,
			ZFCP_FSF_PRINT_FMT_LIST);
		i += scnम_लिखो(buf + i, PAGE_SIZE - i, "\n");
	पूर्ण

	zfcp_ccw_adapter_put(adapter);
	वापस i;
पूर्ण
अटल ZFCP_DEV_ATTR(adapter, fc_security, S_IRUGO,
		     zfcp_sysfs_adapter_fc_security_show,
		     शून्य);

अटल काष्ठा attribute *zfcp_adapter_attrs[] = अणु
	&dev_attr_adapter_failed.attr,
	&dev_attr_adapter_in_recovery.attr,
	&dev_attr_adapter_port_हटाओ.attr,
	&dev_attr_adapter_port_rescan.attr,
	&dev_attr_adapter_peer_wwnn.attr,
	&dev_attr_adapter_peer_wwpn.attr,
	&dev_attr_adapter_peer_d_id.attr,
	&dev_attr_adapter_card_version.attr,
	&dev_attr_adapter_lic_version.attr,
	&dev_attr_adapter_status.attr,
	&dev_attr_adapter_hardware_version.attr,
	&dev_attr_adapter_diag_max_age.attr,
	&dev_attr_adapter_fc_security.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group zfcp_sysfs_adapter_attr_group = अणु
	.attrs = zfcp_adapter_attrs,
पूर्ण;

अटल sमाप_प्रकार zfcp_sysfs_unit_add_store(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा zfcp_port *port = container_of(dev, काष्ठा zfcp_port, dev);
	u64 fcp_lun;
	पूर्णांक retval;

	अगर (kम_से_अदीर्घl(buf, 0, (अचिन्हित दीर्घ दीर्घ *) &fcp_lun))
		वापस -EINVAL;

	retval = zfcp_unit_add(port, fcp_lun);
	अगर (retval)
		वापस retval;

	वापस count;
पूर्ण
अटल DEVICE_ATTR(unit_add, S_IWUSR, शून्य, zfcp_sysfs_unit_add_store);

अटल sमाप_प्रकार zfcp_sysfs_unit_हटाओ_store(काष्ठा device *dev,
					    काष्ठा device_attribute *attr,
					    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा zfcp_port *port = container_of(dev, काष्ठा zfcp_port, dev);
	u64 fcp_lun;

	अगर (kम_से_अदीर्घl(buf, 0, (अचिन्हित दीर्घ दीर्घ *) &fcp_lun))
		वापस -EINVAL;

	अगर (zfcp_unit_हटाओ(port, fcp_lun))
		वापस -EINVAL;

	वापस count;
पूर्ण
अटल DEVICE_ATTR(unit_हटाओ, S_IWUSR, शून्य, zfcp_sysfs_unit_हटाओ_store);

अटल sमाप_प्रकार zfcp_sysfs_port_fc_security_show(काष्ठा device *dev,
						काष्ठा device_attribute *attr,
						अक्षर *buf)
अणु
	काष्ठा zfcp_port *port = container_of(dev, काष्ठा zfcp_port, dev);
	काष्ठा zfcp_adapter *adapter = port->adapter;
	अचिन्हित पूर्णांक status = atomic_पढ़ो(&port->status);
	पूर्णांक i;

	अगर (0 == (status & ZFCP_STATUS_COMMON_OPEN) ||
	    0 == (status & ZFCP_STATUS_COMMON_UNBLOCKED) ||
	    0 == (status & ZFCP_STATUS_PORT_PHYS_OPEN) ||
	    0 != (status & ZFCP_STATUS_COMMON_ERP_FAILED) ||
	    0 != (status & ZFCP_STATUS_COMMON_ACCESS_BOXED))
		i = प्र_लिखो(buf, "unknown\n");
	अन्यथा अगर (!(adapter->adapter_features & FSF_FEATURE_FC_SECURITY))
		i = प्र_लिखो(buf, "unsupported\n");
	अन्यथा अणु
		i = zfcp_fsf_scnprपूर्णांक_fc_security(
			buf, PAGE_SIZE - 1, port->connection_info,
			ZFCP_FSF_PRINT_FMT_SINGLEITEM);
		i += scnम_लिखो(buf + i, PAGE_SIZE - i, "\n");
	पूर्ण

	वापस i;
पूर्ण
अटल ZFCP_DEV_ATTR(port, fc_security, S_IRUGO,
		     zfcp_sysfs_port_fc_security_show,
		     शून्य);

अटल काष्ठा attribute *zfcp_port_attrs[] = अणु
	&dev_attr_unit_add.attr,
	&dev_attr_unit_हटाओ.attr,
	&dev_attr_port_failed.attr,
	&dev_attr_port_in_recovery.attr,
	&dev_attr_port_status.attr,
	&dev_attr_port_access_denied.attr,
	&dev_attr_port_fc_security.attr,
	शून्य
पूर्ण;
अटल काष्ठा attribute_group zfcp_port_attr_group = अणु
	.attrs = zfcp_port_attrs,
पूर्ण;
स्थिर काष्ठा attribute_group *zfcp_port_attr_groups[] = अणु
	&zfcp_port_attr_group,
	शून्य,
पूर्ण;

अटल काष्ठा attribute *zfcp_unit_attrs[] = अणु
	&dev_attr_unit_failed.attr,
	&dev_attr_unit_in_recovery.attr,
	&dev_attr_unit_status.attr,
	&dev_attr_unit_access_denied.attr,
	&dev_attr_unit_access_shared.attr,
	&dev_attr_unit_access_पढ़ोonly.attr,
	शून्य
पूर्ण;
अटल काष्ठा attribute_group zfcp_unit_attr_group = अणु
	.attrs = zfcp_unit_attrs,
पूर्ण;
स्थिर काष्ठा attribute_group *zfcp_unit_attr_groups[] = अणु
	&zfcp_unit_attr_group,
	शून्य,
पूर्ण;

#घोषणा ZFCP_DEFINE_LATENCY_ATTR(_name) 				\
अटल sमाप_प्रकार								\
zfcp_sysfs_unit_##_name##_latency_show(काष्ठा device *dev,		\
				       काष्ठा device_attribute *attr,	\
				       अक्षर *buf) अणु			\
	काष्ठा scsi_device *sdev = to_scsi_device(dev);			\
	काष्ठा zfcp_scsi_dev *zfcp_sdev = sdev_to_zfcp(sdev);		\
	काष्ठा zfcp_latencies *lat = &zfcp_sdev->latencies;		\
	काष्ठा zfcp_adapter *adapter = zfcp_sdev->port->adapter;	\
	अचिन्हित दीर्घ दीर्घ fsum, fmin, fmax, csum, cmin, cmax, cc;	\
									\
	spin_lock_bh(&lat->lock);					\
	fsum = lat->_name.fabric.sum * adapter->समयr_ticks;		\
	fmin = lat->_name.fabric.min * adapter->समयr_ticks;		\
	fmax = lat->_name.fabric.max * adapter->समयr_ticks;		\
	csum = lat->_name.channel.sum * adapter->समयr_ticks;		\
	cmin = lat->_name.channel.min * adapter->समयr_ticks;		\
	cmax = lat->_name.channel.max * adapter->समयr_ticks;		\
	cc  = lat->_name.counter;					\
	spin_unlock_bh(&lat->lock);					\
									\
	करो_भाग(fsum, 1000);						\
	करो_भाग(fmin, 1000);						\
	करो_भाग(fmax, 1000);						\
	करो_भाग(csum, 1000);						\
	करो_भाग(cmin, 1000);						\
	करो_भाग(cmax, 1000);						\
									\
	वापस प्र_लिखो(buf, "%llu %llu %llu %llu %llu %llu %llu\n",	\
		       fmin, fmax, fsum, cmin, cmax, csum, cc); 	\
पूर्ण									\
अटल sमाप_प्रकार								\
zfcp_sysfs_unit_##_name##_latency_store(काष्ठा device *dev,		\
					काष्ठा device_attribute *attr,	\
					स्थिर अक्षर *buf, माप_प्रकार count)	\
अणु									\
	काष्ठा scsi_device *sdev = to_scsi_device(dev);			\
	काष्ठा zfcp_scsi_dev *zfcp_sdev = sdev_to_zfcp(sdev);		\
	काष्ठा zfcp_latencies *lat = &zfcp_sdev->latencies;		\
	अचिन्हित दीर्घ flags;						\
									\
	spin_lock_irqsave(&lat->lock, flags);				\
	lat->_name.fabric.sum = 0;					\
	lat->_name.fabric.min = 0xFFFFFFFF;				\
	lat->_name.fabric.max = 0;					\
	lat->_name.channel.sum = 0;					\
	lat->_name.channel.min = 0xFFFFFFFF;				\
	lat->_name.channel.max = 0;					\
	lat->_name.counter = 0;						\
	spin_unlock_irqrestore(&lat->lock, flags);			\
									\
	वापस (sमाप_प्रकार) count;						\
पूर्ण									\
अटल DEVICE_ATTR(_name##_latency, S_IWUSR | S_IRUGO,			\
		   zfcp_sysfs_unit_##_name##_latency_show,		\
		   zfcp_sysfs_unit_##_name##_latency_store);

ZFCP_DEFINE_LATENCY_ATTR(पढ़ो);
ZFCP_DEFINE_LATENCY_ATTR(ग_लिखो);
ZFCP_DEFINE_LATENCY_ATTR(cmd);

#घोषणा ZFCP_DEFINE_SCSI_ATTR(_name, _क्रमmat, _value)			\
अटल sमाप_प्रकार zfcp_sysfs_scsi_##_name##_show(काष्ठा device *dev,	\
					      काष्ठा device_attribute *attr,\
					      अक्षर *buf)                 \
अणु                                                                        \
	काष्ठा scsi_device *sdev = to_scsi_device(dev);			 \
	काष्ठा zfcp_scsi_dev *zfcp_sdev = sdev_to_zfcp(sdev);		 \
									 \
	वापस प्र_लिखो(buf, _क्रमmat, _value);                            \
पूर्ण                                                                        \
अटल DEVICE_ATTR(_name, S_IRUGO, zfcp_sysfs_scsi_##_name##_show, शून्य);

ZFCP_DEFINE_SCSI_ATTR(hba_id, "%s\n",
		      dev_name(&zfcp_sdev->port->adapter->ccw_device->dev));
ZFCP_DEFINE_SCSI_ATTR(wwpn, "0x%016llx\n",
		      (अचिन्हित दीर्घ दीर्घ) zfcp_sdev->port->wwpn);

अटल sमाप_प्रकार zfcp_sysfs_scsi_fcp_lun_show(काष्ठा device *dev,
					    काष्ठा device_attribute *attr,
					    अक्षर *buf)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(dev);

	वापस प्र_लिखो(buf, "0x%016llx\n", zfcp_scsi_dev_lun(sdev));
पूर्ण
अटल DEVICE_ATTR(fcp_lun, S_IRUGO, zfcp_sysfs_scsi_fcp_lun_show, शून्य);

ZFCP_DEFINE_SCSI_ATTR(zfcp_access_denied, "%d\n",
		      (atomic_पढ़ो(&zfcp_sdev->status) &
		       ZFCP_STATUS_COMMON_ACCESS_DENIED) != 0);

अटल sमाप_प्रकार zfcp_sysfs_scsi_zfcp_failed_show(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   अक्षर *buf)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(dev);
	अचिन्हित पूर्णांक status = atomic_पढ़ो(&sdev_to_zfcp(sdev)->status);
	अचिन्हित पूर्णांक failed = status & ZFCP_STATUS_COMMON_ERP_FAILED ? 1 : 0;

	वापस प्र_लिखो(buf, "%d\n", failed);
पूर्ण

अटल sमाप_प्रकार zfcp_sysfs_scsi_zfcp_failed_store(काष्ठा device *dev,
					    काष्ठा device_attribute *attr,
					    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(dev);
	अचिन्हित दीर्घ val;

	अगर (kम_से_अदीर्घ(buf, 0, &val) || val != 0)
		वापस -EINVAL;

	zfcp_erp_set_lun_status(sdev, ZFCP_STATUS_COMMON_RUNNING);
	zfcp_erp_lun_reखोलो(sdev, ZFCP_STATUS_COMMON_ERP_FAILED,
			    "syufai3");
	zfcp_erp_रुको(sdev_to_zfcp(sdev)->port->adapter);

	वापस count;
पूर्ण
अटल DEVICE_ATTR(zfcp_failed, S_IWUSR | S_IRUGO,
		   zfcp_sysfs_scsi_zfcp_failed_show,
		   zfcp_sysfs_scsi_zfcp_failed_store);

ZFCP_DEFINE_SCSI_ATTR(zfcp_in_recovery, "%d\n",
		      (atomic_पढ़ो(&zfcp_sdev->status) &
		       ZFCP_STATUS_COMMON_ERP_INUSE) != 0);

ZFCP_DEFINE_SCSI_ATTR(zfcp_status, "0x%08x\n",
		      atomic_पढ़ो(&zfcp_sdev->status));

काष्ठा device_attribute *zfcp_sysfs_sdev_attrs[] = अणु
	&dev_attr_fcp_lun,
	&dev_attr_wwpn,
	&dev_attr_hba_id,
	&dev_attr_पढ़ो_latency,
	&dev_attr_ग_लिखो_latency,
	&dev_attr_cmd_latency,
	&dev_attr_zfcp_access_denied,
	&dev_attr_zfcp_failed,
	&dev_attr_zfcp_in_recovery,
	&dev_attr_zfcp_status,
	शून्य
पूर्ण;

अटल sमाप_प्रकार zfcp_sysfs_adapter_util_show(काष्ठा device *dev,
					    काष्ठा device_attribute *attr,
					    अक्षर *buf)
अणु
	काष्ठा Scsi_Host *scsi_host = dev_to_shost(dev);
	काष्ठा fsf_qtcb_bottom_port *qtcb_port;
	काष्ठा zfcp_adapter *adapter;
	पूर्णांक retval;

	adapter = (काष्ठा zfcp_adapter *) scsi_host->hostdata[0];
	अगर (!(adapter->adapter_features & FSF_FEATURE_MEASUREMENT_DATA))
		वापस -EOPNOTSUPP;

	qtcb_port = kzalloc(माप(काष्ठा fsf_qtcb_bottom_port), GFP_KERNEL);
	अगर (!qtcb_port)
		वापस -ENOMEM;

	retval = zfcp_fsf_exchange_port_data_sync(adapter->qdio, qtcb_port);
	अगर (retval == 0 || retval == -EAGAIN)
		retval = प्र_लिखो(buf, "%u %u %u\n", qtcb_port->cp_util,
				 qtcb_port->cb_util, qtcb_port->a_util);
	kमुक्त(qtcb_port);
	वापस retval;
पूर्ण
अटल DEVICE_ATTR(utilization, S_IRUGO, zfcp_sysfs_adapter_util_show, शून्य);

अटल पूर्णांक zfcp_sysfs_adapter_ex_config(काष्ठा device *dev,
					काष्ठा fsf_statistics_info *stat_inf)
अणु
	काष्ठा Scsi_Host *scsi_host = dev_to_shost(dev);
	काष्ठा fsf_qtcb_bottom_config *qtcb_config;
	काष्ठा zfcp_adapter *adapter;
	पूर्णांक retval;

	adapter = (काष्ठा zfcp_adapter *) scsi_host->hostdata[0];
	अगर (!(adapter->adapter_features & FSF_FEATURE_MEASUREMENT_DATA))
		वापस -EOPNOTSUPP;

	qtcb_config = kzalloc(माप(काष्ठा fsf_qtcb_bottom_config),
			      GFP_KERNEL);
	अगर (!qtcb_config)
		वापस -ENOMEM;

	retval = zfcp_fsf_exchange_config_data_sync(adapter->qdio, qtcb_config);
	अगर (retval == 0 || retval == -EAGAIN)
		*stat_inf = qtcb_config->stat_info;

	kमुक्त(qtcb_config);
	वापस retval;
पूर्ण

#घोषणा ZFCP_SHOST_ATTR(_name, _क्रमmat, _arg...)			\
अटल sमाप_प्रकार zfcp_sysfs_adapter_##_name##_show(काष्ठा device *dev,	\
						 काष्ठा device_attribute *attr,\
						 अक्षर *buf)		\
अणु									\
	काष्ठा fsf_statistics_info stat_info;				\
	पूर्णांक retval;							\
									\
	retval = zfcp_sysfs_adapter_ex_config(dev, &stat_info);		\
	अगर (retval)							\
		वापस retval;						\
									\
	वापस प्र_लिखो(buf, _क्रमmat, ## _arg);				\
पूर्ण									\
अटल DEVICE_ATTR(_name, S_IRUGO, zfcp_sysfs_adapter_##_name##_show, शून्य);

ZFCP_SHOST_ATTR(requests, "%llu %llu %llu\n",
		(अचिन्हित दीर्घ दीर्घ) stat_info.input_req,
		(अचिन्हित दीर्घ दीर्घ) stat_info.output_req,
		(अचिन्हित दीर्घ दीर्घ) stat_info.control_req);

ZFCP_SHOST_ATTR(megabytes, "%llu %llu\n",
		(अचिन्हित दीर्घ दीर्घ) stat_info.input_mb,
		(अचिन्हित दीर्घ दीर्घ) stat_info.output_mb);

ZFCP_SHOST_ATTR(seconds_active, "%llu\n",
		(अचिन्हित दीर्घ दीर्घ) stat_info.seconds_act);

अटल sमाप_प्रकार zfcp_sysfs_adapter_q_full_show(काष्ठा device *dev,
					      काष्ठा device_attribute *attr,
					      अक्षर *buf)
अणु
	काष्ठा Scsi_Host *scsi_host = class_to_shost(dev);
	काष्ठा zfcp_qdio *qdio =
		((काष्ठा zfcp_adapter *) scsi_host->hostdata[0])->qdio;
	u64 util;

	spin_lock_bh(&qdio->stat_lock);
	util = qdio->req_q_util;
	spin_unlock_bh(&qdio->stat_lock);

	वापस प्र_लिखो(buf, "%d %llu\n", atomic_पढ़ो(&qdio->req_q_full),
		       (अचिन्हित दीर्घ दीर्घ)util);
पूर्ण
अटल DEVICE_ATTR(queue_full, S_IRUGO, zfcp_sysfs_adapter_q_full_show, शून्य);

काष्ठा device_attribute *zfcp_sysfs_shost_attrs[] = अणु
	&dev_attr_utilization,
	&dev_attr_requests,
	&dev_attr_megabytes,
	&dev_attr_seconds_active,
	&dev_attr_queue_full,
	शून्य
पूर्ण;

अटल sमाप_प्रकार zfcp_sysfs_adapter_diag_b2b_credit_show(
	काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा zfcp_adapter *adapter = zfcp_ccw_adapter_by_cdev(to_ccwdev(dev));
	काष्ठा zfcp_diag_header *diag_hdr;
	काष्ठा fc_els_flogi *nsp;
	sमाप_प्रकार rc = -ENOLINK;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक status;

	अगर (!adapter)
		वापस -ENODEV;

	status = atomic_पढ़ो(&adapter->status);
	अगर (0 == (status & ZFCP_STATUS_COMMON_OPEN) ||
	    0 == (status & ZFCP_STATUS_COMMON_UNBLOCKED) ||
	    0 != (status & ZFCP_STATUS_COMMON_ERP_FAILED))
		जाओ out;

	diag_hdr = &adapter->diagnostics->config_data.header;

	rc = zfcp_diag_update_buffer_limited(
		adapter, diag_hdr, zfcp_diag_update_config_data_buffer);
	अगर (rc != 0)
		जाओ out;

	spin_lock_irqsave(&diag_hdr->access_lock, flags);
	/* nport_serv_param करोesn't contain the ELS_Command code */
	nsp = (काष्ठा fc_els_flogi *)((अचिन्हित दीर्घ)
					      adapter->diagnostics->config_data
						      .data.nport_serv_param -
				      माप(u32));

	rc = scnम_लिखो(buf, 5 + 2, "%hu\n",
		       be16_to_cpu(nsp->fl_csp.sp_bb_cred));
	spin_unlock_irqrestore(&diag_hdr->access_lock, flags);

out:
	zfcp_ccw_adapter_put(adapter);
	वापस rc;
पूर्ण
अटल ZFCP_DEV_ATTR(adapter_diag, b2b_credit, 0400,
		     zfcp_sysfs_adapter_diag_b2b_credit_show, शून्य);

#घोषणा ZFCP_DEFINE_DIAG_SFP_ATTR(_name, _qtcb_member, _prtsize, _prtfmt)      \
	अटल sमाप_प्रकार zfcp_sysfs_adapter_diag_sfp_##_name##_show(	       \
		काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)  \
	अणु								       \
		काष्ठा zfcp_adapter *स्थिर adapter =			       \
			zfcp_ccw_adapter_by_cdev(to_ccwdev(dev));	       \
		काष्ठा zfcp_diag_header *diag_hdr;			       \
		sमाप_प्रकार rc = -ENOLINK;					       \
		अचिन्हित दीर्घ flags;					       \
		अचिन्हित पूर्णांक status;					       \
									       \
		अगर (!adapter)						       \
			वापस -ENODEV;					       \
									       \
		status = atomic_पढ़ो(&adapter->status);			       \
		अगर (0 == (status & ZFCP_STATUS_COMMON_OPEN) ||		       \
		    0 == (status & ZFCP_STATUS_COMMON_UNBLOCKED) ||	       \
		    0 != (status & ZFCP_STATUS_COMMON_ERP_FAILED))	       \
			जाओ out;					       \
									       \
		अगर (!zfcp_diag_support_sfp(adapter)) अणु			       \
			rc = -EOPNOTSUPP;				       \
			जाओ out;					       \
		पूर्ण							       \
									       \
		diag_hdr = &adapter->diagnostics->port_data.header;	       \
									       \
		rc = zfcp_diag_update_buffer_limited(			       \
			adapter, diag_hdr, zfcp_diag_update_port_data_buffer); \
		अगर (rc != 0)						       \
			जाओ out;					       \
									       \
		spin_lock_irqsave(&diag_hdr->access_lock, flags);	       \
		rc = scnम_लिखो(						       \
			buf, (_prtsize) + 2, _prtfmt "\n",		       \
			adapter->diagnostics->port_data.data._qtcb_member);    \
		spin_unlock_irqrestore(&diag_hdr->access_lock, flags);	       \
									       \
	out:								       \
		zfcp_ccw_adapter_put(adapter);				       \
		वापस rc;						       \
	पूर्ण								       \
	अटल ZFCP_DEV_ATTR(adapter_diag_sfp, _name, 0400,		       \
			     zfcp_sysfs_adapter_diag_sfp_##_name##_show, शून्य)

ZFCP_DEFINE_DIAG_SFP_ATTR(temperature, temperature, 6, "%hd");
ZFCP_DEFINE_DIAG_SFP_ATTR(vcc, vcc, 5, "%hu");
ZFCP_DEFINE_DIAG_SFP_ATTR(tx_bias, tx_bias, 5, "%hu");
ZFCP_DEFINE_DIAG_SFP_ATTR(tx_घातer, tx_घातer, 5, "%hu");
ZFCP_DEFINE_DIAG_SFP_ATTR(rx_घातer, rx_घातer, 5, "%hu");
ZFCP_DEFINE_DIAG_SFP_ATTR(port_tx_type, sfp_flags.port_tx_type, 2, "%hu");
ZFCP_DEFINE_DIAG_SFP_ATTR(optical_port, sfp_flags.optical_port, 1, "%hu");
ZFCP_DEFINE_DIAG_SFP_ATTR(sfp_invalid, sfp_flags.sfp_invalid, 1, "%hu");
ZFCP_DEFINE_DIAG_SFP_ATTR(connector_type, sfp_flags.connector_type, 1, "%hu");
ZFCP_DEFINE_DIAG_SFP_ATTR(fec_active, sfp_flags.fec_active, 1, "%hu");

अटल काष्ठा attribute *zfcp_sysfs_diag_attrs[] = अणु
	&dev_attr_adapter_diag_sfp_temperature.attr,
	&dev_attr_adapter_diag_sfp_vcc.attr,
	&dev_attr_adapter_diag_sfp_tx_bias.attr,
	&dev_attr_adapter_diag_sfp_tx_घातer.attr,
	&dev_attr_adapter_diag_sfp_rx_घातer.attr,
	&dev_attr_adapter_diag_sfp_port_tx_type.attr,
	&dev_attr_adapter_diag_sfp_optical_port.attr,
	&dev_attr_adapter_diag_sfp_sfp_invalid.attr,
	&dev_attr_adapter_diag_sfp_connector_type.attr,
	&dev_attr_adapter_diag_sfp_fec_active.attr,
	&dev_attr_adapter_diag_b2b_credit.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group zfcp_sysfs_diag_attr_group = अणु
	.name = "diagnostics",
	.attrs = zfcp_sysfs_diag_attrs,
पूर्ण;

स्थिर काष्ठा attribute_group *zfcp_sysfs_adapter_attr_groups[] = अणु
	&zfcp_sysfs_adapter_attr_group,
	&zfcp_sysfs_diag_attr_group,
	शून्य,
पूर्ण;
