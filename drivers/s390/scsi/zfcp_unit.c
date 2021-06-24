<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * zfcp device driver
 *
 * Tracking of manually configured LUNs and helper functions to
 * रेजिस्टर the LUNs with the SCSI midlayer.
 *
 * Copyright IBM Corp. 2010
 */

#समावेश "zfcp_def.h"
#समावेश "zfcp_ext.h"

/**
 * zfcp_unit_scsi_scan - Register LUN with SCSI midlayer
 * @unit: The zfcp LUN/unit to रेजिस्टर
 *
 * When the SCSI midlayer is not allowed to स्वतःmatically scan and
 * attach SCSI devices, zfcp has to रेजिस्टर the single devices with
 * the SCSI midlayer.
 */
व्योम zfcp_unit_scsi_scan(काष्ठा zfcp_unit *unit)
अणु
	काष्ठा fc_rport *rport = unit->port->rport;
	u64 lun;

	lun = scsilun_to_पूर्णांक((काष्ठा scsi_lun *) &unit->fcp_lun);

	अगर (rport && rport->port_state == FC_PORTSTATE_ONLINE)
		scsi_scan_target(&rport->dev, 0, rport->scsi_target_id, lun,
				 SCSI_SCAN_MANUAL);
पूर्ण

अटल व्योम zfcp_unit_scsi_scan_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा zfcp_unit *unit = container_of(work, काष्ठा zfcp_unit,
					      scsi_work);

	zfcp_unit_scsi_scan(unit);
	put_device(&unit->dev);
पूर्ण

/**
 * zfcp_unit_queue_scsi_scan - Register configured units on port
 * @port: The zfcp_port where to रेजिस्टर units
 *
 * After खोलोing a port, all units configured on this port have to be
 * रेजिस्टरed with the SCSI midlayer. This function should be called
 * after calling fc_remote_port_add, so that the fc_rport is alपढ़ोy
 * ONLINE and the call to scsi_scan_target runs the same way as the
 * call in the FC transport class.
 */
व्योम zfcp_unit_queue_scsi_scan(काष्ठा zfcp_port *port)
अणु
	काष्ठा zfcp_unit *unit;

	पढ़ो_lock_irq(&port->unit_list_lock);
	list_क्रम_each_entry(unit, &port->unit_list, list) अणु
		get_device(&unit->dev);
		अगर (scsi_queue_work(port->adapter->scsi_host,
				    &unit->scsi_work) <= 0)
			put_device(&unit->dev);
	पूर्ण
	पढ़ो_unlock_irq(&port->unit_list_lock);
पूर्ण

अटल काष्ठा zfcp_unit *_zfcp_unit_find(काष्ठा zfcp_port *port, u64 fcp_lun)
अणु
	काष्ठा zfcp_unit *unit;

	list_क्रम_each_entry(unit, &port->unit_list, list)
		अगर (unit->fcp_lun == fcp_lun) अणु
			get_device(&unit->dev);
			वापस unit;
		पूर्ण

	वापस शून्य;
पूर्ण

/**
 * zfcp_unit_find - Find and वापस zfcp_unit with specअगरied FCP LUN
 * @port: zfcp_port where to look क्रम the unit
 * @fcp_lun: 64 Bit FCP LUN used to identअगरy the zfcp_unit
 *
 * If zfcp_unit is found, a reference is acquired that has to be
 * released later.
 *
 * Returns: Poपूर्णांकer to the zfcp_unit, or शून्य अगर there is no zfcp_unit
 *          with the specअगरied FCP LUN.
 */
काष्ठा zfcp_unit *zfcp_unit_find(काष्ठा zfcp_port *port, u64 fcp_lun)
अणु
	काष्ठा zfcp_unit *unit;

	पढ़ो_lock_irq(&port->unit_list_lock);
	unit = _zfcp_unit_find(port, fcp_lun);
	पढ़ो_unlock_irq(&port->unit_list_lock);
	वापस unit;
पूर्ण

/**
 * zfcp_unit_release - Drop reference to zfcp_port and मुक्त memory of zfcp_unit.
 * @dev: poपूर्णांकer to device in zfcp_unit
 */
अटल व्योम zfcp_unit_release(काष्ठा device *dev)
अणु
	काष्ठा zfcp_unit *unit = container_of(dev, काष्ठा zfcp_unit, dev);

	atomic_dec(&unit->port->units);
	kमुक्त(unit);
पूर्ण

/**
 * zfcp_unit_enqueue - enqueue unit to unit list of a port.
 * @port: poपूर्णांकer to port where unit is added
 * @fcp_lun: FCP LUN of unit to be enqueued
 * Returns: 0 success
 *
 * Sets up some unit पूर्णांकernal काष्ठाures and creates sysfs entry.
 */
पूर्णांक zfcp_unit_add(काष्ठा zfcp_port *port, u64 fcp_lun)
अणु
	काष्ठा zfcp_unit *unit;
	पूर्णांक retval = 0;

	mutex_lock(&zfcp_sysfs_port_units_mutex);
	अगर (zfcp_sysfs_port_is_removing(port)) अणु
		/* port is alपढ़ोy gone */
		retval = -ENODEV;
		जाओ out;
	पूर्ण

	unit = zfcp_unit_find(port, fcp_lun);
	अगर (unit) अणु
		put_device(&unit->dev);
		retval = -EEXIST;
		जाओ out;
	पूर्ण

	unit = kzalloc(माप(काष्ठा zfcp_unit), GFP_KERNEL);
	अगर (!unit) अणु
		retval = -ENOMEM;
		जाओ out;
	पूर्ण

	unit->port = port;
	unit->fcp_lun = fcp_lun;
	unit->dev.parent = &port->dev;
	unit->dev.release = zfcp_unit_release;
	unit->dev.groups = zfcp_unit_attr_groups;
	INIT_WORK(&unit->scsi_work, zfcp_unit_scsi_scan_work);

	अगर (dev_set_name(&unit->dev, "0x%016llx",
			 (अचिन्हित दीर्घ दीर्घ) fcp_lun)) अणु
		kमुक्त(unit);
		retval = -ENOMEM;
		जाओ out;
	पूर्ण

	अगर (device_रेजिस्टर(&unit->dev)) अणु
		put_device(&unit->dev);
		retval = -ENOMEM;
		जाओ out;
	पूर्ण

	atomic_inc(&port->units); /* under zfcp_sysfs_port_units_mutex ! */

	ग_लिखो_lock_irq(&port->unit_list_lock);
	list_add_tail(&unit->list, &port->unit_list);
	ग_लिखो_unlock_irq(&port->unit_list_lock);
	/*
	 * lock order: shost->scan_mutex beक्रमe zfcp_sysfs_port_units_mutex
	 * due to      zfcp_unit_scsi_scan() => zfcp_scsi_slave_alloc()
	 */
	mutex_unlock(&zfcp_sysfs_port_units_mutex);

	zfcp_unit_scsi_scan(unit);
	वापस retval;

out:
	mutex_unlock(&zfcp_sysfs_port_units_mutex);
	वापस retval;
पूर्ण

/**
 * zfcp_unit_sdev - Return SCSI device क्रम zfcp_unit
 * @unit: The zfcp_unit where to get the SCSI device क्रम
 *
 * Returns: scsi_device poपूर्णांकer on success, शून्य अगर there is no SCSI
 *          device क्रम this zfcp_unit
 *
 * On success, the caller also holds a reference to the SCSI device
 * that must be released with scsi_device_put.
 */
काष्ठा scsi_device *zfcp_unit_sdev(काष्ठा zfcp_unit *unit)
अणु
	काष्ठा Scsi_Host *shost;
	काष्ठा zfcp_port *port;
	u64 lun;

	lun = scsilun_to_पूर्णांक((काष्ठा scsi_lun *) &unit->fcp_lun);
	port = unit->port;
	shost = port->adapter->scsi_host;
	वापस scsi_device_lookup(shost, 0, port->starget_id, lun);
पूर्ण

/**
 * zfcp_unit_sdev_status - Return zfcp LUN status क्रम SCSI device
 * @unit: The unit to lookup the SCSI device क्रम
 *
 * Returns the zfcp LUN status field of the SCSI device अगर the SCSI device
 * क्रम the zfcp_unit exists, 0 otherwise.
 */
अचिन्हित पूर्णांक zfcp_unit_sdev_status(काष्ठा zfcp_unit *unit)
अणु
	अचिन्हित पूर्णांक status = 0;
	काष्ठा scsi_device *sdev;
	काष्ठा zfcp_scsi_dev *zfcp_sdev;

	sdev = zfcp_unit_sdev(unit);
	अगर (sdev) अणु
		zfcp_sdev = sdev_to_zfcp(sdev);
		status = atomic_पढ़ो(&zfcp_sdev->status);
		scsi_device_put(sdev);
	पूर्ण

	वापस status;
पूर्ण

/**
 * zfcp_unit_हटाओ - Remove entry from list of configured units
 * @port: The port where to हटाओ the unit from the configuration
 * @fcp_lun: The 64 bit LUN of the unit to हटाओ
 *
 * Returns: -EINVAL अगर a unit with the specअगरied LUN करोes not exist,
 *          0 on success.
 */
पूर्णांक zfcp_unit_हटाओ(काष्ठा zfcp_port *port, u64 fcp_lun)
अणु
	काष्ठा zfcp_unit *unit;
	काष्ठा scsi_device *sdev;

	ग_लिखो_lock_irq(&port->unit_list_lock);
	unit = _zfcp_unit_find(port, fcp_lun);
	अगर (unit)
		list_del(&unit->list);
	ग_लिखो_unlock_irq(&port->unit_list_lock);

	अगर (!unit)
		वापस -EINVAL;

	sdev = zfcp_unit_sdev(unit);
	अगर (sdev) अणु
		scsi_हटाओ_device(sdev);
		scsi_device_put(sdev);
	पूर्ण

	device_unरेजिस्टर(&unit->dev);

	put_device(&unit->dev); /* unकरो _zfcp_unit_find() */

	वापस 0;
पूर्ण
