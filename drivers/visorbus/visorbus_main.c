<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright oडट 2010 - 2015 UNISYS CORPORATION
 * All rights reserved.
 */

#समावेश <linux/प्रकार.स>
#समावेश <linux/debugfs.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/visorbus.h>
#समावेश <linux/uuid.h>

#समावेश "visorbus_private.h"

अटल स्थिर guid_t visor_vbus_channel_guid = VISOR_VBUS_CHANNEL_GUID;

/* Display string that is guaranteed to be no दीर्घer the 99 अक्षरacters */
#घोषणा LINESIZE 99
#घोषणा POLLJIFFIES_NORMALCHANNEL 10

/* stores whether bus_registration was successful */
अटल bool initialized;
अटल काष्ठा dentry *visorbus_debugfs_dir;

/*
 * DEVICE type attributes
 *
 * The modalias file will contain the guid of the device.
 */
अटल sमाप_प्रकार modalias_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा visor_device *vdev;
	स्थिर guid_t *guid;

	vdev = to_visor_device(dev);
	guid = visorchannel_get_guid(vdev->visorchannel);
	वापस प्र_लिखो(buf, "visorbus:%pUl\n", guid);
पूर्ण
अटल DEVICE_ATTR_RO(modalias);

अटल काष्ठा attribute *visorbus_dev_attrs[] = अणु
	&dev_attr_modalias.attr,
	शून्य,
पूर्ण;

ATTRIBUTE_GROUPS(visorbus_dev);

/* filled in with info about parent chipset driver when we रेजिस्टर with it */
अटल काष्ठा visor_vbus_deviceinfo chipset_driverinfo;
/* filled in with info about this driver, wrt it servicing client busses */
अटल काष्ठा visor_vbus_deviceinfo clientbus_driverinfo;

/* list of visor_device काष्ठाs, linked via .list_all */
अटल LIST_HEAD(list_all_bus_instances);
/* list of visor_device काष्ठाs, linked via .list_all */
अटल LIST_HEAD(list_all_device_instances);

/*
 * Generic function useful क्रम validating any type of channel when it is
 * received by the client that will be accessing the channel.
 * Note that <logCtx> is only needed क्रम callers in the EFI environment, and
 * is used to pass the EFI_DIAG_CAPTURE_PROTOCOL needed to log messages.
 */
पूर्णांक visor_check_channel(काष्ठा channel_header *ch, काष्ठा device *dev,
			स्थिर guid_t *expected_guid, अक्षर *chname,
			u64 expected_min_bytes, u32 expected_version,
			u64 expected_signature)
अणु
	अगर (!guid_is_null(expected_guid)) अणु
		/* caller wants us to verअगरy type GUID */
		अगर (!guid_equal(&ch->chtype, expected_guid)) अणु
			dev_err(dev, "Channel mismatch on channel=%s(%pUL) field=type expected=%pUL actual=%pUL\n",
				chname, expected_guid, expected_guid,
				&ch->chtype);
			वापस 0;
		पूर्ण
	पूर्ण
	/* verअगरy channel size */
	अगर (expected_min_bytes > 0) अणु
		अगर (ch->size < expected_min_bytes) अणु
			dev_err(dev, "Channel mismatch on channel=%s(%pUL) field=size expected=0x%-8.8Lx actual=0x%-8.8Lx\n",
				chname, expected_guid,
				(अचिन्हित दीर्घ दीर्घ)expected_min_bytes,
				ch->size);
			वापस 0;
		पूर्ण
	पूर्ण
	/* verअगरy channel version */
	अगर (expected_version > 0) अणु
		अगर (ch->version_id != expected_version) अणु
			dev_err(dev, "Channel mismatch on channel=%s(%pUL) field=version expected=0x%-8.8lx actual=0x%-8.8x\n",
				chname, expected_guid,
				(अचिन्हित दीर्घ)expected_version,
				ch->version_id);
			वापस 0;
		पूर्ण
	पूर्ण
	/* verअगरy channel signature */
	अगर (expected_signature > 0) अणु
		अगर (ch->signature != expected_signature) अणु
			dev_err(dev, "Channel mismatch on channel=%s(%pUL) field=signature expected=0x%-8.8Lx actual=0x%-8.8Lx\n",
				chname, expected_guid,	expected_signature,
				ch->signature);
			वापस 0;
		पूर्ण
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक visorbus_uevent(काष्ठा device *xdev, काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा visor_device *dev;
	स्थिर guid_t *guid;

	dev = to_visor_device(xdev);
	guid = visorchannel_get_guid(dev->visorchannel);
	वापस add_uevent_var(env, "MODALIAS=visorbus:%pUl", guid);
पूर्ण

/*
 * visorbus_match() - called स्वतःmatically upon adding a visor_device
 *                    (device_add), or adding a visor_driver
 *                    (visorbus_रेजिस्टर_visor_driver)
 * @xdev: काष्ठा device क्रम the device being matched
 * @xdrv: काष्ठा device_driver क्रम driver to match device against
 *
 * Return: 1 अगरf the provided driver can control the specअगरied device
 */
अटल पूर्णांक visorbus_match(काष्ठा device *xdev, काष्ठा device_driver *xdrv)
अणु
	स्थिर guid_t *channel_type;
	पूर्णांक i;
	काष्ठा visor_device *dev;
	काष्ठा visor_driver *drv;
	काष्ठा visorchannel *chan;

	dev = to_visor_device(xdev);
	channel_type = visorchannel_get_guid(dev->visorchannel);
	drv = to_visor_driver(xdrv);
	chan = dev->visorchannel;
	अगर (!drv->channel_types)
		वापस 0;
	क्रम (i = 0; !guid_is_null(&drv->channel_types[i].guid); i++)
		अगर (guid_equal(&drv->channel_types[i].guid, channel_type) &&
		    visor_check_channel(visorchannel_get_header(chan),
					xdev,
					&drv->channel_types[i].guid,
					(अक्षर *)drv->channel_types[i].name,
					drv->channel_types[i].min_bytes,
					drv->channel_types[i].version,
					VISOR_CHANNEL_SIGNATURE))
			वापस i + 1;
	वापस 0;
पूर्ण

/*
 * This describes the TYPE of bus.
 * (Don't confuse this with an INSTANCE of the bus.)
 */
अटल काष्ठा bus_type visorbus_type = अणु
	.name = "visorbus",
	.match = visorbus_match,
	.uevent = visorbus_uevent,
	.dev_groups = visorbus_dev_groups,
पूर्ण;

काष्ठा visor_busdev अणु
	u32 bus_no;
	u32 dev_no;
पूर्ण;

अटल पूर्णांक match_visorbus_dev_by_id(काष्ठा device *dev, स्थिर व्योम *data)
अणु
	काष्ठा visor_device *vdev = to_visor_device(dev);
	स्थिर काष्ठा visor_busdev *id = data;

	अगर (vdev->chipset_bus_no == id->bus_no &&
	    vdev->chipset_dev_no == id->dev_no)
		वापस 1;
	वापस 0;
पूर्ण

काष्ठा visor_device *visorbus_get_device_by_id(u32 bus_no, u32 dev_no,
					       काष्ठा visor_device *from)
अणु
	काष्ठा device *dev;
	काष्ठा device *dev_start = शून्य;
	काष्ठा visor_busdev id = अणु
		.bus_no = bus_no,
		.dev_no = dev_no
	पूर्ण;

	अगर (from)
		dev_start = &from->device;
	dev = bus_find_device(&visorbus_type, dev_start, (व्योम *)&id,
			      match_visorbus_dev_by_id);
	अगर (!dev)
		वापस शून्य;
	वापस to_visor_device(dev);
पूर्ण

/*
 * visorbus_release_busdevice() - called when device_unरेजिस्टर() is called क्रम
 *                                the bus device instance, after all other tasks
 *                                involved with destroying the dev are complete
 * @xdev: काष्ठा device क्रम the bus being released
 */
अटल व्योम visorbus_release_busdevice(काष्ठा device *xdev)
अणु
	काष्ठा visor_device *dev = dev_get_drvdata(xdev);

	debugfs_हटाओ(dev->debugfs_bus_info);
	debugfs_हटाओ_recursive(dev->debugfs_dir);
	visorchannel_destroy(dev->visorchannel);
	kमुक्त(dev);
पूर्ण

/*
 * visorbus_release_device() - called when device_unरेजिस्टर() is called क्रम
 *                             each child device instance
 * @xdev: काष्ठा device क्रम the visor device being released
 */
अटल व्योम visorbus_release_device(काष्ठा device *xdev)
अणु
	काष्ठा visor_device *dev = to_visor_device(xdev);

	visorchannel_destroy(dev->visorchannel);
	kमुक्त(dev);
पूर्ण

/*
 * BUS specअगरic channel attributes to appear under
 * /sys/bus/visorbus<x>/dev<y>/channel
 */

अटल sमाप_प्रकार physaddr_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा visor_device *vdev = to_visor_device(dev);

	वापस प्र_लिखो(buf, "0x%llx\n",
		       visorchannel_get_physaddr(vdev->visorchannel));
पूर्ण
अटल DEVICE_ATTR_RO(physaddr);

अटल sमाप_प्रकार nbytes_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा visor_device *vdev = to_visor_device(dev);

	वापस प्र_लिखो(buf, "0x%lx\n",
		       visorchannel_get_nbytes(vdev->visorchannel));
पूर्ण
अटल DEVICE_ATTR_RO(nbytes);

अटल sमाप_प्रकार clientpartition_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा visor_device *vdev = to_visor_device(dev);

	वापस प्र_लिखो(buf, "0x%llx\n",
		       visorchannel_get_clientpartition(vdev->visorchannel));
पूर्ण
अटल DEVICE_ATTR_RO(clientpartition);

अटल sमाप_प्रकार typeguid_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा visor_device *vdev = to_visor_device(dev);
	अक्षर typeid[LINESIZE];

	वापस प्र_लिखो(buf, "%s\n",
		       visorchannel_id(vdev->visorchannel, typeid));
पूर्ण
अटल DEVICE_ATTR_RO(typeguid);

अटल sमाप_प्रकार zoneguid_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा visor_device *vdev = to_visor_device(dev);
	अक्षर zoneid[LINESIZE];

	वापस प्र_लिखो(buf, "%s\n",
		       visorchannel_zoneid(vdev->visorchannel, zoneid));
पूर्ण
अटल DEVICE_ATTR_RO(zoneguid);

अटल sमाप_प्रकार typename_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	पूर्णांक i = 0;
	काष्ठा bus_type *xbus = dev->bus;
	काष्ठा device_driver *xdrv = dev->driver;
	काष्ठा visor_driver *drv = शून्य;

	अगर (!xdrv)
		वापस 0;
	i = xbus->match(dev, xdrv);
	अगर (!i)
		वापस 0;
	drv = to_visor_driver(xdrv);
	वापस प्र_लिखो(buf, "%s\n", drv->channel_types[i - 1].name);
पूर्ण
अटल DEVICE_ATTR_RO(typename);

अटल काष्ठा attribute *channel_attrs[] = अणु
	&dev_attr_physaddr.attr,
	&dev_attr_nbytes.attr,
	&dev_attr_clientpartition.attr,
	&dev_attr_typeguid.attr,
	&dev_attr_zoneguid.attr,
	&dev_attr_typename.attr,
	शून्य
पूर्ण;

ATTRIBUTE_GROUPS(channel);

/*
 *  BUS instance attributes
 *
 *  define & implement display of bus attributes under
 *  /sys/bus/visorbus/devices/visorbus<n>.
 */
अटल sमाप_प्रकार partition_handle_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा visor_device *vdev = to_visor_device(dev);
	u64 handle = visorchannel_get_clientpartition(vdev->visorchannel);

	वापस प्र_लिखो(buf, "0x%llx\n", handle);
पूर्ण
अटल DEVICE_ATTR_RO(partition_handle);

अटल sमाप_प्रकार partition_guid_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा visor_device *vdev = to_visor_device(dev);

	वापस प्र_लिखो(buf, "{%pUb}\n", &vdev->partition_guid);
पूर्ण
अटल DEVICE_ATTR_RO(partition_guid);

अटल sमाप_प्रकार partition_name_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा visor_device *vdev = to_visor_device(dev);

	वापस प्र_लिखो(buf, "%s\n", vdev->name);
पूर्ण
अटल DEVICE_ATTR_RO(partition_name);

अटल sमाप_प्रकार channel_addr_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा visor_device *vdev = to_visor_device(dev);
	u64 addr = visorchannel_get_physaddr(vdev->visorchannel);

	वापस प्र_लिखो(buf, "0x%llx\n", addr);
पूर्ण
अटल DEVICE_ATTR_RO(channel_addr);

अटल sमाप_प्रकार channel_bytes_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा visor_device *vdev = to_visor_device(dev);
	u64 nbytes = visorchannel_get_nbytes(vdev->visorchannel);

	वापस प्र_लिखो(buf, "0x%llx\n", nbytes);
पूर्ण
अटल DEVICE_ATTR_RO(channel_bytes);

अटल sमाप_प्रकार channel_id_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा visor_device *vdev = to_visor_device(dev);
	पूर्णांक len = 0;

	visorchannel_id(vdev->visorchannel, buf);
	len = म_माप(buf);
	buf[len++] = '\n';
	वापस len;
पूर्ण
अटल DEVICE_ATTR_RO(channel_id);

अटल काष्ठा attribute *visorbus_attrs[] = अणु
	&dev_attr_partition_handle.attr,
	&dev_attr_partition_guid.attr,
	&dev_attr_partition_name.attr,
	&dev_attr_channel_addr.attr,
	&dev_attr_channel_bytes.attr,
	&dev_attr_channel_id.attr,
	शून्य
पूर्ण;

ATTRIBUTE_GROUPS(visorbus);

/*
 *  BUS debugfs entries
 *
 *  define & implement display of debugfs attributes under
 *  /sys/kernel/debug/visorbus/visorbus<n>.
 */

/*
 * vbuschannel_prपूर्णांक_devinfo() - क्रमmat a काष्ठा visor_vbus_deviceinfo
 *                               and ग_लिखो it to a seq_file
 * @devinfo: the काष्ठा visor_vbus_deviceinfo to क्रमmat
 * @seq: seq_file to ग_लिखो to
 * @devix: the device index to be included in the output data, or -1 अगर no
 *         device index is to be included
 *
 * Reads @devInfo, and ग_लिखोs it in human-पढ़ोable notation to @seq.
 */
अटल व्योम vbuschannel_prपूर्णांक_devinfo(काष्ठा visor_vbus_deviceinfo *devinfo,
				      काष्ठा seq_file *seq, पूर्णांक devix)
अणु
	/* uninitialized vbus device entry */
	अगर (!है_छाप(devinfo->devtype[0]))
		वापस;
	अगर (devix >= 0)
		seq_म_लिखो(seq, "[%d]", devix);
	अन्यथा
		/* vbus device entry is क्रम bus or chipset */
		seq_माला_दो(seq, "   ");
	/*
	 * Note: because the s-Par back-end is मुक्त to scribble in this area,
	 * we never assume '\0'-termination.
	 */
	seq_म_लिखो(seq, "%-*.*s ", (पूर्णांक)माप(devinfo->devtype),
		   (पूर्णांक)माप(devinfo->devtype), devinfo->devtype);
	seq_म_लिखो(seq, "%-*.*s ", (पूर्णांक)माप(devinfo->drvname),
		   (पूर्णांक)माप(devinfo->drvname), devinfo->drvname);
	seq_म_लिखो(seq, "%.*s\n", (पूर्णांक)माप(devinfo->infostrs),
		   devinfo->infostrs);
पूर्ण

अटल पूर्णांक bus_info_debugfs_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	पूर्णांक i = 0;
	अचिन्हित दीर्घ off;
	काष्ठा visor_vbus_deviceinfo dev_info;
	काष्ठा visor_device *vdev = seq->निजी;
	काष्ठा visorchannel *channel = vdev->visorchannel;

	अगर (!channel)
		वापस 0;

	seq_म_लिखो(seq,
		   "Client device/driver info for %s partition (vbus #%u):\n",
		   ((vdev->name) ? (अक्षर *)(vdev->name) : ""),
		   vdev->chipset_bus_no);
	अगर (visorchannel_पढ़ो(channel,
			      दुरत्व(काष्ठा visor_vbus_channel, chp_info),
			      &dev_info, माप(dev_info)) >= 0)
		vbuschannel_prपूर्णांक_devinfo(&dev_info, seq, -1);
	अगर (visorchannel_पढ़ो(channel,
			      दुरत्व(काष्ठा visor_vbus_channel, bus_info),
			      &dev_info, माप(dev_info)) >= 0)
		vbuschannel_prपूर्णांक_devinfo(&dev_info, seq, -1);

	off = दुरत्व(काष्ठा visor_vbus_channel, dev_info);
	जबतक (off + माप(dev_info) <= visorchannel_get_nbytes(channel)) अणु
		अगर (visorchannel_पढ़ो(channel, off, &dev_info,
				      माप(dev_info)) >= 0)
			vbuschannel_prपूर्णांक_devinfo(&dev_info, seq, i);
		off += माप(dev_info);
		i++;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक bus_info_debugfs_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, bus_info_debugfs_show, inode->i_निजी);
पूर्ण

अटल स्थिर काष्ठा file_operations bus_info_debugfs_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = bus_info_debugfs_खोलो,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.release = single_release,
पूर्ण;

अटल व्योम dev_periodic_work(काष्ठा समयr_list *t)
अणु
	काष्ठा visor_device *dev = from_समयr(dev, t, समयr);
	काष्ठा visor_driver *drv = to_visor_driver(dev->device.driver);

	drv->channel_पूर्णांकerrupt(dev);
	mod_समयr(&dev->समयr, jअगरfies + POLLJIFFIES_NORMALCHANNEL);
पूर्ण

अटल पूर्णांक dev_start_periodic_work(काष्ठा visor_device *dev)
अणु
	अगर (dev->being_हटाओd || dev->समयr_active)
		वापस -EINVAL;

	/* now up by at least 2 */
	get_device(&dev->device);
	dev->समयr.expires = jअगरfies + POLLJIFFIES_NORMALCHANNEL;
	add_समयr(&dev->समयr);
	dev->समयr_active = true;
	वापस 0;
पूर्ण

अटल व्योम dev_stop_periodic_work(काष्ठा visor_device *dev)
अणु
	अगर (!dev->समयr_active)
		वापस;

	del_समयr_sync(&dev->समयr);
	dev->समयr_active = false;
	put_device(&dev->device);
पूर्ण

/*
 * visordriver_हटाओ_device() - handle visor device going away
 * @xdev: काष्ठा device क्रम the visor device being हटाओd
 *
 * This is called when device_unरेजिस्टर() is called क्रम each child device
 * instance, to notअगरy the appropriate visorbus function driver that the device
 * is going away, and to decrease the reference count of the device.
 *
 * Return: 0 अगरf successful
 */
अटल पूर्णांक visordriver_हटाओ_device(काष्ठा device *xdev)
अणु
	काष्ठा visor_device *dev = to_visor_device(xdev);
	काष्ठा visor_driver *drv = to_visor_driver(xdev->driver);

	mutex_lock(&dev->visordriver_callback_lock);
	dev->being_हटाओd = true;
	drv->हटाओ(dev);
	mutex_unlock(&dev->visordriver_callback_lock);
	dev_stop_periodic_work(dev);
	put_device(&dev->device);
	वापस 0;
पूर्ण

/*
 * visorbus_unरेजिस्टर_visor_driver() - unरेजिस्टरs the provided driver
 * @drv: the driver to unरेजिस्टर
 *
 * A visor function driver calls this function to unरेजिस्टर the driver,
 * i.e., within its module_निकास function.
 */
व्योम visorbus_unरेजिस्टर_visor_driver(काष्ठा visor_driver *drv)
अणु
	driver_unरेजिस्टर(&drv->driver);
पूर्ण
EXPORT_SYMBOL_GPL(visorbus_unरेजिस्टर_visor_driver);

/*
 * visorbus_पढ़ो_channel() - पढ़ोs from the designated channel पूर्णांकo
 *                           the provided buffer
 * @dev:    the device whose channel is पढ़ो from
 * @offset: the offset पूर्णांकo the channel at which पढ़ोing starts
 * @dest:   the destination buffer that is written पूर्णांकo from the channel
 * @nbytes: the number of bytes to पढ़ो from the channel
 *
 * If receiving a message, use the visorchannel_संकेतहटाओ() function instead.
 *
 * Return: पूर्णांकeger indicating success (zero) or failure (non-zero)
 */
पूर्णांक visorbus_पढ़ो_channel(काष्ठा visor_device *dev, अचिन्हित दीर्घ offset,
			  व्योम *dest, अचिन्हित दीर्घ nbytes)
अणु
	वापस visorchannel_पढ़ो(dev->visorchannel, offset, dest, nbytes);
पूर्ण
EXPORT_SYMBOL_GPL(visorbus_पढ़ो_channel);

/*
 * visorbus_ग_लिखो_channel() - ग_लिखोs the provided buffer पूर्णांकo the designated
 *                            channel
 * @dev:    the device whose channel is written to
 * @offset: the offset पूर्णांकo the channel at which writing starts
 * @src:    the source buffer that is written पूर्णांकo the channel
 * @nbytes: the number of bytes to ग_लिखो पूर्णांकo the channel
 *
 * If sending a message, use the visorchannel_संकेतinsert() function instead.
 *
 * Return: पूर्णांकeger indicating success (zero) or failure (non-zero)
 */
पूर्णांक visorbus_ग_लिखो_channel(काष्ठा visor_device *dev, अचिन्हित दीर्घ offset,
			   व्योम *src, अचिन्हित दीर्घ nbytes)
अणु
	वापस visorchannel_ग_लिखो(dev->visorchannel, offset, src, nbytes);
पूर्ण
EXPORT_SYMBOL_GPL(visorbus_ग_लिखो_channel);

/*
 * visorbus_enable_channel_पूर्णांकerrupts() - enables पूर्णांकerrupts on the
 *                                        designated device
 * @dev: the device on which to enable पूर्णांकerrupts
 *
 * Currently we करोn't yet have a real पूर्णांकerrupt, so क्रम now we just call the
 * पूर्णांकerrupt function periodically via a समयr.
 */
पूर्णांक visorbus_enable_channel_पूर्णांकerrupts(काष्ठा visor_device *dev)
अणु
	काष्ठा visor_driver *drv = to_visor_driver(dev->device.driver);

	अगर (!drv->channel_पूर्णांकerrupt) अणु
		dev_err(&dev->device, "%s no interrupt function!\n", __func__);
		वापस -ENOENT;
	पूर्ण

	वापस dev_start_periodic_work(dev);
पूर्ण
EXPORT_SYMBOL_GPL(visorbus_enable_channel_पूर्णांकerrupts);

/*
 * visorbus_disable_channel_पूर्णांकerrupts() - disables पूर्णांकerrupts on the
 *                                         designated device
 * @dev: the device on which to disable पूर्णांकerrupts
 */
व्योम visorbus_disable_channel_पूर्णांकerrupts(काष्ठा visor_device *dev)
अणु
	dev_stop_periodic_work(dev);
पूर्ण
EXPORT_SYMBOL_GPL(visorbus_disable_channel_पूर्णांकerrupts);

/*
 * create_visor_device() - create visor device as a result of receiving the
 *                         controlvm device_create message क्रम a new device
 * @dev: a freshly-zeroed काष्ठा visor_device, containing only filled-in values
 *       क्रम chipset_bus_no and chipset_dev_no, that will be initialized
 *
 * This is how everything starts from the device end.
 * This function is called when a channel first appears via a ControlVM
 * message.  In response, this function allocates a visor_device to correspond
 * to the new channel, and attempts to connect it the appropriate * driver. If
 * the appropriate driver is found, the visor_driver.probe() function क्रम that
 * driver will be called, and will be passed the new * visor_device that we
 * just created.
 *
 * It's ok अगर the appropriate driver is not yet loaded, because in that हाल
 * the new device काष्ठा will just stick around in the bus' list of devices.
 * When the appropriate driver calls visorbus_रेजिस्टर_visor_driver(), the
 * visor_driver.probe() क्रम the new driver will be called with the new device.
 *
 * Return: 0 अगर successful, otherwise the negative value वापसed by
 *         device_add() indicating the reason क्रम failure
 */
पूर्णांक create_visor_device(काष्ठा visor_device *dev)
अणु
	पूर्णांक err;
	u32 chipset_bus_no = dev->chipset_bus_no;
	u32 chipset_dev_no = dev->chipset_dev_no;

	mutex_init(&dev->visordriver_callback_lock);
	dev->device.bus = &visorbus_type;
	dev->device.groups = channel_groups;
	device_initialize(&dev->device);
	dev->device.release = visorbus_release_device;
	/* keep a reference just क्रम us (now 2) */
	get_device(&dev->device);
	समयr_setup(&dev->समयr, dev_periodic_work, 0);
	/*
	 * bus_id must be a unique name with respect to this bus TYPE (NOT bus
	 * instance).  That's why we need to include the bus number within the
	 * name.
	 */
	err = dev_set_name(&dev->device, "vbus%u:dev%u",
			   chipset_bus_no, chipset_dev_no);
	अगर (err)
		जाओ err_put;
	/*
	 * device_add करोes this:
	 *    bus_add_device(dev)
	 *    ->device_attach(dev)
	 *      ->क्रम each driver drv रेजिस्टरed on the bus that dev is on
	 *          अगर (dev.drv)  **  device alपढ़ोy has a driver **
	 *            ** not sure we could ever get here... **
	 *          अन्यथा
	 *            अगर (bus.match(dev,drv)) [visorbus_match]
	 *              dev.drv = drv
	 *              अगर (!drv.probe(dev))  [visordriver_probe_device]
	 *                dev.drv = शून्य
	 *
	 * Note that device_add करोes NOT fail अगर no driver failed to claim the
	 * device.  The device will be linked onto bus_type.klist_devices
	 * regardless (use bus_क्रम_each_dev).
	 */
	err = device_add(&dev->device);
	अगर (err < 0)
		जाओ err_put;
	list_add_tail(&dev->list_all, &list_all_device_instances);
	dev->state.created = 1;
	visorbus_response(dev, err, CONTROLVM_DEVICE_CREATE);
	/* success: reference kept via unmatched get_device() */
	वापस 0;

err_put:
	put_device(&dev->device);
	dev_err(&dev->device, "Creating visor device failed. %d\n", err);
	वापस err;
पूर्ण

व्योम हटाओ_visor_device(काष्ठा visor_device *dev)
अणु
	list_del(&dev->list_all);
	put_device(&dev->device);
	अगर (dev->pending_msg_hdr)
		visorbus_response(dev, 0, CONTROLVM_DEVICE_DESTROY);
	device_unरेजिस्टर(&dev->device);
पूर्ण

अटल पूर्णांक get_vbus_header_info(काष्ठा visorchannel *chan,
				काष्ठा device *dev,
				काष्ठा visor_vbus_headerinfo *hdr_info)
अणु
	पूर्णांक err;

	अगर (!visor_check_channel(visorchannel_get_header(chan),
				 dev,
				 &visor_vbus_channel_guid,
				 "vbus",
				 माप(काष्ठा visor_vbus_channel),
				 VISOR_VBUS_CHANNEL_VERSIONID,
				 VISOR_CHANNEL_SIGNATURE))
		वापस -EINVAL;

	err = visorchannel_पढ़ो(chan, माप(काष्ठा channel_header), hdr_info,
				माप(*hdr_info));
	अगर (err < 0)
		वापस err;
	अगर (hdr_info->काष्ठा_bytes < माप(काष्ठा visor_vbus_headerinfo))
		वापस -EINVAL;
	अगर (hdr_info->device_info_काष्ठा_bytes <
	    माप(काष्ठा visor_vbus_deviceinfo))
		वापस -EINVAL;
	वापस 0;
पूर्ण

/*
 * ग_लिखो_vbus_chp_info() - ग_लिखो the contents of <info> to the काष्ठा
 *                         visor_vbus_channel.chp_info
 * @chan:     indentअगरies the s-Par channel that will be updated
 * @hdr_info: used to find appropriate channel offset to ग_लिखो data
 * @info:     contains the inक्रमmation to ग_लिखो
 *
 * Writes chipset info पूर्णांकo the channel memory to be used क्रम diagnostic
 * purposes.
 *
 * Returns no value since this is debug inक्रमmation and not needed क्रम
 * device functionality.
 */
अटल व्योम ग_लिखो_vbus_chp_info(काष्ठा visorchannel *chan,
				काष्ठा visor_vbus_headerinfo *hdr_info,
				काष्ठा visor_vbus_deviceinfo *info)
अणु
	पूर्णांक off;

	अगर (hdr_info->chp_info_offset == 0)
		वापस;

	off = माप(काष्ठा channel_header) + hdr_info->chp_info_offset;
	visorchannel_ग_लिखो(chan, off, info, माप(*info));
पूर्ण

/*
 * ग_लिखो_vbus_bus_info() - ग_लिखो the contents of <info> to the काष्ठा
 *                         visor_vbus_channel.bus_info
 * @chan:     indentअगरies the s-Par channel that will be updated
 * @hdr_info: used to find appropriate channel offset to ग_लिखो data
 * @info:     contains the inक्रमmation to ग_लिखो
 *
 * Writes bus info पूर्णांकo the channel memory to be used क्रम diagnostic
 * purposes.
 *
 * Returns no value since this is debug inक्रमmation and not needed क्रम
 * device functionality.
 */
अटल व्योम ग_लिखो_vbus_bus_info(काष्ठा visorchannel *chan,
				काष्ठा visor_vbus_headerinfo *hdr_info,
				काष्ठा visor_vbus_deviceinfo *info)
अणु
	पूर्णांक off;

	अगर (hdr_info->bus_info_offset == 0)
		वापस;

	off = माप(काष्ठा channel_header) + hdr_info->bus_info_offset;
	visorchannel_ग_लिखो(chan, off, info, माप(*info));
पूर्ण

/*
 * ग_लिखो_vbus_dev_info() - ग_लिखो the contents of <info> to the काष्ठा
 *                         visor_vbus_channel.dev_info[<devix>]
 * @chan:     indentअगरies the s-Par channel that will be updated
 * @hdr_info: used to find appropriate channel offset to ग_लिखो data
 * @info:     contains the inक्रमmation to ग_लिखो
 * @devix:    the relative device number (0..n-1) of the device on the bus
 *
 * Writes device info पूर्णांकo the channel memory to be used क्रम diagnostic
 * purposes.
 *
 * Returns no value since this is debug inक्रमmation and not needed क्रम
 * device functionality.
 */
अटल व्योम ग_लिखो_vbus_dev_info(काष्ठा visorchannel *chan,
				काष्ठा visor_vbus_headerinfo *hdr_info,
				काष्ठा visor_vbus_deviceinfo *info,
				अचिन्हित पूर्णांक devix)
अणु
	पूर्णांक off;

	अगर (hdr_info->dev_info_offset == 0)
		वापस;
	off = (माप(काष्ठा channel_header) + hdr_info->dev_info_offset) +
	      (hdr_info->device_info_काष्ठा_bytes * devix);
	visorchannel_ग_लिखो(chan, off, info, माप(*info));
पूर्ण

अटल व्योम bus_device_info_init(
		काष्ठा visor_vbus_deviceinfo *bus_device_info_ptr,
		स्थिर अक्षर *dev_type, स्थिर अक्षर *drv_name)
अणु
	स_रखो(bus_device_info_ptr, 0, माप(काष्ठा visor_vbus_deviceinfo));
	snम_लिखो(bus_device_info_ptr->devtype,
		 माप(bus_device_info_ptr->devtype),
		 "%s", (dev_type) ? dev_type : "unknownType");
	snम_लिखो(bus_device_info_ptr->drvname,
		 माप(bus_device_info_ptr->drvname),
		 "%s", (drv_name) ? drv_name : "unknownDriver");
	snम_लिखो(bus_device_info_ptr->infostrs,
		 माप(bus_device_info_ptr->infostrs), "kernel ver. %s",
		 utsname()->release);
पूर्ण

/*
 * publish_vbus_dev_info() - क्रम a child device just created on a client bus,
 *			     fill in inक्रमmation about the driver that is
 *			     controlling this device पूर्णांकo the appropriate slot
 *			     within the vbus channel of the bus instance
 * @visordev: काष्ठा visor_device क्रम the desired device
 */
अटल व्योम publish_vbus_dev_info(काष्ठा visor_device *visordev)
अणु
	पूर्णांक i;
	काष्ठा visor_device *bdev;
	काष्ठा visor_driver *visordrv;
	u32 bus_no = visordev->chipset_bus_no;
	u32 dev_no = visordev->chipset_dev_no;
	काष्ठा visor_vbus_deviceinfo dev_info;
	स्थिर अक्षर *chan_type_name = शून्य;
	काष्ठा visor_vbus_headerinfo *hdr_info;

	अगर (!visordev->device.driver)
		वापस;
	bdev = visorbus_get_device_by_id(bus_no, BUS_ROOT_DEVICE, शून्य);
	अगर (!bdev)
		वापस;
	hdr_info = (काष्ठा visor_vbus_headerinfo *)bdev->vbus_hdr_info;
	अगर (!hdr_info)
		वापस;
	visordrv = to_visor_driver(visordev->device.driver);

	/*
	 * Within the list of device types (by GUID) that the driver
	 * says it supports, find out which one of those types matches
	 * the type of this device, so that we can include the device
	 * type name
	 */
	क्रम (i = 0; visordrv->channel_types[i].name; i++) अणु
		अगर (guid_equal(&visordrv->channel_types[i].guid,
			       &visordev->channel_type_guid)) अणु
			chan_type_name = visordrv->channel_types[i].name;
			अवरोध;
		पूर्ण
	पूर्ण
	bus_device_info_init(&dev_info, chan_type_name, visordrv->name);
	ग_लिखो_vbus_dev_info(bdev->visorchannel, hdr_info, &dev_info, dev_no);
	ग_लिखो_vbus_chp_info(bdev->visorchannel, hdr_info, &chipset_driverinfo);
	ग_लिखो_vbus_bus_info(bdev->visorchannel, hdr_info,
			    &clientbus_driverinfo);
पूर्ण

/*
 * visordriver_probe_device() - handle new visor device coming online
 * @xdev: काष्ठा device क्रम the visor device being probed
 *
 * This is called स्वतःmatically upon adding a visor_device (device_add), or
 * adding a visor_driver (visorbus_रेजिस्टर_visor_driver), but only after
 * visorbus_match() has वापसed 1 to indicate a successful match between
 * driver and device.
 *
 * If successful, a reference to the device will be held onto via get_device().
 *
 * Return: 0 अगर successful, meaning the function driver's probe() function
 *         was successful with this device, otherwise a negative त्रुटि_सं
 *         value indicating failure reason
 */
अटल पूर्णांक visordriver_probe_device(काष्ठा device *xdev)
अणु
	पूर्णांक err;
	काष्ठा visor_driver *drv = to_visor_driver(xdev->driver);
	काष्ठा visor_device *dev = to_visor_device(xdev);

	mutex_lock(&dev->visordriver_callback_lock);
	dev->being_हटाओd = false;
	err = drv->probe(dev);
	अगर (err) अणु
		mutex_unlock(&dev->visordriver_callback_lock);
		वापस err;
	पूर्ण
	/* success: reference kept via unmatched get_device() */
	get_device(&dev->device);
	publish_vbus_dev_info(dev);
	mutex_unlock(&dev->visordriver_callback_lock);
	वापस 0;
पूर्ण

/*
 * visorbus_रेजिस्टर_visor_driver() - रेजिस्टरs the provided visor driver क्रम
 *				      handling one or more visor device
 *                                    types (channel_types)
 * @drv: the driver to रेजिस्टर
 *
 * A visor function driver calls this function to रेजिस्टर the driver. The
 * caller MUST fill in the following fields within the #drv काष्ठाure:
 *     name, version, owner, channel_types, probe, हटाओ
 *
 * Here's how the whole Linux bus / driver / device model works.
 *
 * At प्रणाली start-up, the visorbus kernel module is loaded, which रेजिस्टरs
 * visorbus_type as a bus type, using bus_रेजिस्टर().
 *
 * All kernel modules that support particular device types on a
 * visorbus bus are loaded.  Each of these kernel modules calls
 * visorbus_रेजिस्टर_visor_driver() in their init functions, passing a
 * visor_driver काष्ठा.  visorbus_रेजिस्टर_visor_driver() in turn calls
 * रेजिस्टर_driver(&visor_driver.driver).  This .driver member is
 * initialized with generic methods (like probe), whose sole responsibility
 * is to act as a broker क्रम the real methods, which are within the
 * visor_driver काष्ठा.  (This is the way the subclass behavior is
 * implemented, since visor_driver is essentially a subclass of the
 * generic driver.)  Whenever a driver_रेजिस्टर() happens, core bus code in
 * the kernel करोes (see device_attach() in drivers/base/dd.c):
 *
 *     क्रम each dev associated with the bus (the bus that driver is on) that
 *     करोes not yet have a driver
 *         अगर bus.match(dev,newdriver) == yes_matched  ** .match specअगरied
 *                                                ** during bus_रेजिस्टर().
 *             newdriver.probe(dev)  ** क्रम visor drivers, this will call
 *                   ** the generic driver.probe implemented in visorbus.c,
 *                   ** which in turn calls the probe specअगरied within the
 *                   ** काष्ठा visor_driver (which was specअगरied by the
 *                   ** actual device driver as part of
 *                   ** visorbus_रेजिस्टर_visor_driver()).
 *
 * The above dance also happens when a new device appears.
 * So the question is, how are devices created within the प्रणाली?
 * Basically, just call device_add(dev).  See pci_bus_add_devices().
 * pci_scan_device() shows an example of how to build a device काष्ठा.  It
 * वापसs the newly-created काष्ठा to pci_scan_single_device(), who adds it
 * to the list of devices at PCIBUS.devices.  That list of devices is what
 * is traversed by pci_bus_add_devices().
 *
 * Return: पूर्णांकeger indicating success (zero) or failure (non-zero)
 */
पूर्णांक visorbus_रेजिस्टर_visor_driver(काष्ठा visor_driver *drv)
अणु
	/* can't रेजिस्टर on a nonexistent bus */
	अगर (!initialized)
		वापस -ENODEV;
	अगर (!drv->probe)
		वापस -EINVAL;
	अगर (!drv->हटाओ)
		वापस -EINVAL;
	अगर (!drv->छोड़ो)
		वापस -EINVAL;
	अगर (!drv->resume)
		वापस -EINVAL;

	drv->driver.name = drv->name;
	drv->driver.bus = &visorbus_type;
	drv->driver.probe = visordriver_probe_device;
	drv->driver.हटाओ = visordriver_हटाओ_device;
	drv->driver.owner = drv->owner;
	/*
	 * driver_रेजिस्टर करोes this:
	 *   bus_add_driver(drv)
	 *   ->अगर (drv.bus)  ** (bus_type) **
	 *       driver_attach(drv)
	 *         क्रम each dev with bus type of drv.bus
	 *           अगर (!dev.drv)  ** no driver asचिन्हित yet **
	 *             अगर (bus.match(dev,drv))  [visorbus_match]
	 *               dev.drv = drv
	 *               अगर (!drv.probe(dev))   [visordriver_probe_device]
	 *                 dev.drv = शून्य
	 */
	वापस driver_रेजिस्टर(&drv->driver);
पूर्ण
EXPORT_SYMBOL_GPL(visorbus_रेजिस्टर_visor_driver);

/*
 * visorbus_create_instance() - create a device instance क्रम the visorbus itself
 * @dev: काष्ठा visor_device indicating the bus instance
 *
 * Return: 0 क्रम success, otherwise negative त्रुटि_सं value indicating reason क्रम
 *         failure
 */
पूर्णांक visorbus_create_instance(काष्ठा visor_device *dev)
अणु
	पूर्णांक id = dev->chipset_bus_no;
	पूर्णांक err;
	काष्ठा visor_vbus_headerinfo *hdr_info;

	hdr_info = kzalloc(माप(*hdr_info), GFP_KERNEL);
	अगर (!hdr_info)
		वापस -ENOMEM;
	dev_set_name(&dev->device, "visorbus%d", id);
	dev->device.bus = &visorbus_type;
	dev->device.groups = visorbus_groups;
	dev->device.release = visorbus_release_busdevice;
	dev->debugfs_dir = debugfs_create_dir(dev_name(&dev->device),
					      visorbus_debugfs_dir);
	dev->debugfs_bus_info = debugfs_create_file("client_bus_info", 0440,
						    dev->debugfs_dir, dev,
						    &bus_info_debugfs_fops);
	dev_set_drvdata(&dev->device, dev);
	err = get_vbus_header_info(dev->visorchannel, &dev->device, hdr_info);
	अगर (err < 0)
		जाओ err_debugfs_dir;
	err = device_रेजिस्टर(&dev->device);
	अगर (err < 0)
		जाओ err_debugfs_dir;
	list_add_tail(&dev->list_all, &list_all_bus_instances);
	dev->state.created = 1;
	dev->vbus_hdr_info = (व्योम *)hdr_info;
	ग_लिखो_vbus_chp_info(dev->visorchannel, hdr_info, &chipset_driverinfo);
	ग_लिखो_vbus_bus_info(dev->visorchannel, hdr_info, &clientbus_driverinfo);
	visorbus_response(dev, err, CONTROLVM_BUS_CREATE);
	वापस 0;

err_debugfs_dir:
	debugfs_हटाओ_recursive(dev->debugfs_dir);
	kमुक्त(hdr_info);
	dev_err(&dev->device, "%s failed: %d\n", __func__, err);
	वापस err;
पूर्ण

/*
 * visorbus_हटाओ_instance() - हटाओ a device instance क्रम the visorbus itself
 * @dev: काष्ठा visor_device indentअगरying the bus to हटाओ
 */
व्योम visorbus_हटाओ_instance(काष्ठा visor_device *dev)
अणु
	/*
	 * Note that this will result in the release method क्रम
	 * dev->dev being called, which will call
	 * visorbus_release_busdevice().  This has something to करो with
	 * the put_device() करोne in device_unरेजिस्टर(), but I have never
	 * successfully been able to trace thru the code to see where/how
	 * release() माला_लो called.  But I know it करोes.
	 */
	kमुक्त(dev->vbus_hdr_info);
	list_del(&dev->list_all);
	अगर (dev->pending_msg_hdr)
		visorbus_response(dev, 0, CONTROLVM_BUS_DESTROY);
	device_unरेजिस्टर(&dev->device);
पूर्ण

/*
 * हटाओ_all_visor_devices() - हटाओ all child visorbus device instances
 */
अटल व्योम हटाओ_all_visor_devices(व्योम)
अणु
	काष्ठा list_head *listentry, *listपंचांगp;

	list_क्रम_each_safe(listentry, listपंचांगp, &list_all_device_instances) अणु
		काष्ठा visor_device *dev;

		dev = list_entry(listentry, काष्ठा visor_device, list_all);
		हटाओ_visor_device(dev);
	पूर्ण
पूर्ण

/*
 * छोड़ो_state_change_complete() - the callback function to be called by a
 *                                 visorbus function driver when a
 *                                 pending "pause device" operation has
 *                                 completed
 * @dev: काष्ठा visor_device identअगरying the छोड़ोd device
 * @status: 0 अगरf the छोड़ो state change completed successfully, otherwise
 *          a negative त्रुटि_सं value indicating the reason क्रम failure
 */
अटल व्योम छोड़ो_state_change_complete(काष्ठा visor_device *dev, पूर्णांक status)
अणु
	अगर (!dev->pausing)
		वापस;

	dev->pausing = false;
	visorbus_device_changestate_response(dev, status,
					     segment_state_standby);
पूर्ण

/*
 * resume_state_change_complete() - the callback function to be called by a
 *                                  visorbus function driver when a
 *                                  pending "resume device" operation has
 *                                  completed
 * @dev: काष्ठा visor_device identअगरying the resumed device
 * @status: 0 अगरf the resume state change completed successfully, otherwise
 *          a negative त्रुटि_सं value indicating the reason क्रम failure
 */
अटल व्योम resume_state_change_complete(काष्ठा visor_device *dev, पूर्णांक status)
अणु
	अगर (!dev->resuming)
		वापस;

	dev->resuming = false;
	/*
	 * Notअगरy the chipset driver that the resume is complete,
	 * which will presumably want to send some sort of response to
	 * the initiator.
	 */
	visorbus_device_changestate_response(dev, status,
					     segment_state_running);
पूर्ण

/*
 * visorchipset_initiate_device_छोड़ो_resume() - start a छोड़ो or resume
 *                                               operation क्रम a visor device
 * @dev: काष्ठा visor_device identअगरying the device being छोड़ोd or resumed
 * @is_छोड़ो: true to indicate छोड़ो operation, false to indicate resume
 *
 * Tell the subordinate function driver क्रम a specअगरic device to छोड़ो
 * or resume that device.  Success/failure result is वापसed asynchronously
 * via a callback function; see छोड़ो_state_change_complete() and
 * resume_state_change_complete().
 */
अटल पूर्णांक visorchipset_initiate_device_छोड़ो_resume(काष्ठा visor_device *dev,
						     bool is_छोड़ो)
अणु
	पूर्णांक err;
	काष्ठा visor_driver *drv;

	/* If no driver associated with the device nothing to छोड़ो/resume */
	अगर (!dev->device.driver)
		वापस 0;
	अगर (dev->pausing || dev->resuming)
		वापस -EBUSY;

	drv = to_visor_driver(dev->device.driver);
	अगर (is_छोड़ो) अणु
		dev->pausing = true;
		err = drv->छोड़ो(dev, छोड़ो_state_change_complete);
	पूर्ण अन्यथा अणु
		/*
		 * The vbus_dev_info काष्ठाure in the channel was been cleared,
		 * make sure it is valid.
		 */
		publish_vbus_dev_info(dev);
		dev->resuming = true;
		err = drv->resume(dev, resume_state_change_complete);
	पूर्ण
	वापस err;
पूर्ण

/*
 * visorchipset_device_छोड़ो() - start a छोड़ो operation क्रम a visor device
 * @dev_info: काष्ठा visor_device identअगरying the device being छोड़ोd
 *
 * Tell the subordinate function driver क्रम a specअगरic device to छोड़ो
 * that device.  Success/failure result is वापसed asynchronously
 * via a callback function; see छोड़ो_state_change_complete().
 */
पूर्णांक visorchipset_device_छोड़ो(काष्ठा visor_device *dev_info)
अणु
	पूर्णांक err;

	err = visorchipset_initiate_device_छोड़ो_resume(dev_info, true);
	अगर (err < 0) अणु
		dev_info->pausing = false;
		वापस err;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * visorchipset_device_resume() - start a resume operation क्रम a visor device
 * @dev_info: काष्ठा visor_device identअगरying the device being resumed
 *
 * Tell the subordinate function driver क्रम a specअगरic device to resume
 * that device.  Success/failure result is वापसed asynchronously
 * via a callback function; see resume_state_change_complete().
 */
पूर्णांक visorchipset_device_resume(काष्ठा visor_device *dev_info)
अणु
	पूर्णांक err;

	err = visorchipset_initiate_device_छोड़ो_resume(dev_info, false);
	अगर (err < 0) अणु
		dev_info->resuming = false;
		वापस err;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक visorbus_init(व्योम)
अणु
	पूर्णांक err;

	visorbus_debugfs_dir = debugfs_create_dir("visorbus", शून्य);
	bus_device_info_init(&clientbus_driverinfo, "clientbus", "visorbus");
	err = bus_रेजिस्टर(&visorbus_type);
	अगर (err < 0)
		वापस err;
	initialized = true;
	bus_device_info_init(&chipset_driverinfo, "chipset", "visorchipset");
	वापस 0;
पूर्ण

व्योम visorbus_निकास(व्योम)
अणु
	काष्ठा list_head *listentry, *listपंचांगp;

	हटाओ_all_visor_devices();
	list_क्रम_each_safe(listentry, listपंचांगp, &list_all_bus_instances) अणु
		काष्ठा visor_device *dev;

		dev = list_entry(listentry, काष्ठा visor_device, list_all);
		visorbus_हटाओ_instance(dev);
	पूर्ण
	bus_unरेजिस्टर(&visorbus_type);
	initialized = false;
	debugfs_हटाओ_recursive(visorbus_debugfs_dir);
पूर्ण
