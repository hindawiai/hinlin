<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

/*
 * drm_sysfs.c - Modअगरications to drm_sysfs_class.c to support
 *               extra sysfs attribute from DRM. Normal drm_sysfs_class
 *               करोes not allow adding attributes.
 *
 * Copyright (c) 2004 Jon Smirl <jonsmirl@gmail.com>
 * Copyright (c) 2003-2004 Greg Kroah-Harपंचांगan <greg@kroah.com>
 * Copyright (c) 2003-2004 IBM Corp.
 */

#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/export.h>
#समावेश <linux/gfp.h>
#समावेश <linux/i2c.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/slab.h>

#समावेश <drm/drm_connector.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_modes.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_property.h>
#समावेश <drm/drm_sysfs.h>

#समावेश "drm_internal.h"
#समावेश "drm_crtc_internal.h"

#घोषणा to_drm_minor(d) dev_get_drvdata(d)
#घोषणा to_drm_connector(d) dev_get_drvdata(d)

/**
 * DOC: overview
 *
 * DRM provides very little additional support to drivers क्रम sysfs
 * पूर्णांकeractions, beyond just all the standard stuff. Drivers who want to expose
 * additional sysfs properties and property groups can attach them at either
 * &drm_device.dev or &drm_connector.kdev.
 *
 * Registration is स्वतःmatically handled when calling drm_dev_रेजिस्टर(), or
 * drm_connector_रेजिस्टर() in हाल of hot-plugged connectors. Unregistration is
 * also स्वतःmatically handled by drm_dev_unरेजिस्टर() and
 * drm_connector_unरेजिस्टर().
 */

अटल काष्ठा device_type drm_sysfs_device_minor = अणु
	.name = "drm_minor"
पूर्ण;

काष्ठा class *drm_class;

अटल अक्षर *drm_devnode(काष्ठा device *dev, umode_t *mode)
अणु
	वापस kaप्र_लिखो(GFP_KERNEL, "dri/%s", dev_name(dev));
पूर्ण

अटल CLASS_ATTR_STRING(version, S_IRUGO, "drm 1.1.0 20060810");

/**
 * drm_sysfs_init - initialize sysfs helpers
 *
 * This is used to create the DRM class, which is the implicit parent of any
 * other top-level DRM sysfs objects.
 *
 * You must call drm_sysfs_destroy() to release the allocated resources.
 *
 * Return: 0 on success, negative error code on failure.
 */
पूर्णांक drm_sysfs_init(व्योम)
अणु
	पूर्णांक err;

	drm_class = class_create(THIS_MODULE, "drm");
	अगर (IS_ERR(drm_class))
		वापस PTR_ERR(drm_class);

	err = class_create_file(drm_class, &class_attr_version.attr);
	अगर (err) अणु
		class_destroy(drm_class);
		drm_class = शून्य;
		वापस err;
	पूर्ण

	drm_class->devnode = drm_devnode;
	वापस 0;
पूर्ण

/**
 * drm_sysfs_destroy - destroys DRM class
 *
 * Destroy the DRM device class.
 */
व्योम drm_sysfs_destroy(व्योम)
अणु
	अगर (IS_ERR_OR_शून्य(drm_class))
		वापस;
	class_हटाओ_file(drm_class, &class_attr_version.attr);
	class_destroy(drm_class);
	drm_class = शून्य;
पूर्ण

/*
 * Connector properties
 */
अटल sमाप_प्रकार status_store(काष्ठा device *device,
			   काष्ठा device_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा drm_connector *connector = to_drm_connector(device);
	काष्ठा drm_device *dev = connector->dev;
	क्रमागत drm_connector_क्रमce old_क्रमce;
	पूर्णांक ret;

	ret = mutex_lock_पूर्णांकerruptible(&dev->mode_config.mutex);
	अगर (ret)
		वापस ret;

	old_क्रमce = connector->क्रमce;

	अगर (sysfs_streq(buf, "detect"))
		connector->क्रमce = 0;
	अन्यथा अगर (sysfs_streq(buf, "on"))
		connector->क्रमce = DRM_FORCE_ON;
	अन्यथा अगर (sysfs_streq(buf, "on-digital"))
		connector->क्रमce = DRM_FORCE_ON_DIGITAL;
	अन्यथा अगर (sysfs_streq(buf, "off"))
		connector->क्रमce = DRM_FORCE_OFF;
	अन्यथा
		ret = -EINVAL;

	अगर (old_क्रमce != connector->क्रमce || !connector->क्रमce) अणु
		DRM_DEBUG_KMS("[CONNECTOR:%d:%s] force updated from %d to %d or reprobing\n",
			      connector->base.id,
			      connector->name,
			      old_क्रमce, connector->क्रमce);

		connector->funcs->fill_modes(connector,
					     dev->mode_config.max_width,
					     dev->mode_config.max_height);
	पूर्ण

	mutex_unlock(&dev->mode_config.mutex);

	वापस ret ? ret : count;
पूर्ण

अटल sमाप_प्रकार status_show(काष्ठा device *device,
			   काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा drm_connector *connector = to_drm_connector(device);
	क्रमागत drm_connector_status status;

	status = READ_ONCE(connector->status);

	वापस sysfs_emit(buf, "%s\n",
			  drm_get_connector_status_name(status));
पूर्ण

अटल sमाप_प्रकार dpms_show(काष्ठा device *device,
			   काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा drm_connector *connector = to_drm_connector(device);
	पूर्णांक dpms;

	dpms = READ_ONCE(connector->dpms);

	वापस sysfs_emit(buf, "%s\n", drm_get_dpms_name(dpms));
पूर्ण

अटल sमाप_प्रकार enabled_show(काष्ठा device *device,
			    काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा drm_connector *connector = to_drm_connector(device);
	bool enabled;

	enabled = READ_ONCE(connector->encoder);

	वापस sysfs_emit(buf, enabled ? "enabled\n" : "disabled\n");
पूर्ण

अटल sमाप_प्रकार edid_show(काष्ठा file *filp, काष्ठा kobject *kobj,
			 काष्ठा bin_attribute *attr, अक्षर *buf, loff_t off,
			 माप_प्रकार count)
अणु
	काष्ठा device *connector_dev = kobj_to_dev(kobj);
	काष्ठा drm_connector *connector = to_drm_connector(connector_dev);
	अचिन्हित अक्षर *edid;
	माप_प्रकार size;
	sमाप_प्रकार ret = 0;

	mutex_lock(&connector->dev->mode_config.mutex);
	अगर (!connector->edid_blob_ptr)
		जाओ unlock;

	edid = connector->edid_blob_ptr->data;
	size = connector->edid_blob_ptr->length;
	अगर (!edid)
		जाओ unlock;

	अगर (off >= size)
		जाओ unlock;

	अगर (off + count > size)
		count = size - off;
	स_नकल(buf, edid + off, count);

	ret = count;
unlock:
	mutex_unlock(&connector->dev->mode_config.mutex);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार modes_show(काष्ठा device *device,
			   काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा drm_connector *connector = to_drm_connector(device);
	काष्ठा drm_display_mode *mode;
	पूर्णांक written = 0;

	mutex_lock(&connector->dev->mode_config.mutex);
	list_क्रम_each_entry(mode, &connector->modes, head) अणु
		written += scnम_लिखो(buf + written, PAGE_SIZE - written, "%s\n",
				    mode->name);
	पूर्ण
	mutex_unlock(&connector->dev->mode_config.mutex);

	वापस written;
पूर्ण

अटल DEVICE_ATTR_RW(status);
अटल DEVICE_ATTR_RO(enabled);
अटल DEVICE_ATTR_RO(dpms);
अटल DEVICE_ATTR_RO(modes);

अटल काष्ठा attribute *connector_dev_attrs[] = अणु
	&dev_attr_status.attr,
	&dev_attr_enabled.attr,
	&dev_attr_dpms.attr,
	&dev_attr_modes.attr,
	शून्य
पूर्ण;

अटल काष्ठा bin_attribute edid_attr = अणु
	.attr.name = "edid",
	.attr.mode = 0444,
	.size = 0,
	.पढ़ो = edid_show,
पूर्ण;

अटल काष्ठा bin_attribute *connector_bin_attrs[] = अणु
	&edid_attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group connector_dev_group = अणु
	.attrs = connector_dev_attrs,
	.bin_attrs = connector_bin_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *connector_dev_groups[] = अणु
	&connector_dev_group,
	शून्य
पूर्ण;

पूर्णांक drm_sysfs_connector_add(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_device *dev = connector->dev;

	अगर (connector->kdev)
		वापस 0;

	connector->kdev =
		device_create_with_groups(drm_class, dev->primary->kdev, 0,
					  connector, connector_dev_groups,
					  "card%d-%s", dev->primary->index,
					  connector->name);
	DRM_DEBUG("adding \"%s\" to sysfs\n",
		  connector->name);

	अगर (IS_ERR(connector->kdev)) अणु
		DRM_ERROR("failed to register connector device: %ld\n", PTR_ERR(connector->kdev));
		वापस PTR_ERR(connector->kdev);
	पूर्ण

	अगर (connector->ddc)
		वापस sysfs_create_link(&connector->kdev->kobj,
				 &connector->ddc->dev.kobj, "ddc");
	वापस 0;
पूर्ण

व्योम drm_sysfs_connector_हटाओ(काष्ठा drm_connector *connector)
अणु
	अगर (!connector->kdev)
		वापस;

	अगर (connector->ddc)
		sysfs_हटाओ_link(&connector->kdev->kobj, "ddc");

	DRM_DEBUG("removing \"%s\" from sysfs\n",
		  connector->name);

	device_unरेजिस्टर(connector->kdev);
	connector->kdev = शून्य;
पूर्ण

व्योम drm_sysfs_lease_event(काष्ठा drm_device *dev)
अणु
	अक्षर *event_string = "LEASE=1";
	अक्षर *envp[] = अणु event_string, शून्य पूर्ण;

	DRM_DEBUG("generating lease event\n");

	kobject_uevent_env(&dev->primary->kdev->kobj, KOBJ_CHANGE, envp);
पूर्ण

/**
 * drm_sysfs_hotplug_event - generate a DRM uevent
 * @dev: DRM device
 *
 * Send a uevent क्रम the DRM device specअगरied by @dev.  Currently we only
 * set HOTPLUG=1 in the uevent environment, but this could be expanded to
 * deal with other types of events.
 *
 * Any new uapi should be using the drm_sysfs_connector_status_event()
 * क्रम uevents on connector status change.
 */
व्योम drm_sysfs_hotplug_event(काष्ठा drm_device *dev)
अणु
	अक्षर *event_string = "HOTPLUG=1";
	अक्षर *envp[] = अणु event_string, शून्य पूर्ण;

	DRM_DEBUG("generating hotplug event\n");

	kobject_uevent_env(&dev->primary->kdev->kobj, KOBJ_CHANGE, envp);
पूर्ण
EXPORT_SYMBOL(drm_sysfs_hotplug_event);

/**
 * drm_sysfs_connector_status_event - generate a DRM uevent क्रम connector
 * property status change
 * @connector: connector on which property status changed
 * @property: connector property whose status changed.
 *
 * Send a uevent क्रम the DRM device specअगरied by @dev.  Currently we
 * set HOTPLUG=1 and connector id aदीर्घ with the attached property id
 * related to the status change.
 */
व्योम drm_sysfs_connector_status_event(काष्ठा drm_connector *connector,
				      काष्ठा drm_property *property)
अणु
	काष्ठा drm_device *dev = connector->dev;
	अक्षर hotplug_str[] = "HOTPLUG=1", conn_id[21], prop_id[21];
	अक्षर *envp[4] = अणु hotplug_str, conn_id, prop_id, शून्य पूर्ण;

	WARN_ON(!drm_mode_obj_find_prop_id(&connector->base,
					   property->base.id));

	snम_लिखो(conn_id, ARRAY_SIZE(conn_id),
		 "CONNECTOR=%u", connector->base.id);
	snम_लिखो(prop_id, ARRAY_SIZE(prop_id),
		 "PROPERTY=%u", property->base.id);

	DRM_DEBUG("generating connector status event\n");

	kobject_uevent_env(&dev->primary->kdev->kobj, KOBJ_CHANGE, envp);
पूर्ण
EXPORT_SYMBOL(drm_sysfs_connector_status_event);

अटल व्योम drm_sysfs_release(काष्ठा device *dev)
अणु
	kमुक्त(dev);
पूर्ण

काष्ठा device *drm_sysfs_minor_alloc(काष्ठा drm_minor *minor)
अणु
	स्थिर अक्षर *minor_str;
	काष्ठा device *kdev;
	पूर्णांक r;

	अगर (minor->type == DRM_MINOR_RENDER)
		minor_str = "renderD%d";
	अन्यथा
		minor_str = "card%d";

	kdev = kzalloc(माप(*kdev), GFP_KERNEL);
	अगर (!kdev)
		वापस ERR_PTR(-ENOMEM);

	device_initialize(kdev);
	kdev->devt = MKDEV(DRM_MAJOR, minor->index);
	kdev->class = drm_class;
	kdev->type = &drm_sysfs_device_minor;
	kdev->parent = minor->dev->dev;
	kdev->release = drm_sysfs_release;
	dev_set_drvdata(kdev, minor);

	r = dev_set_name(kdev, minor_str, minor->index);
	अगर (r < 0)
		जाओ err_मुक्त;

	वापस kdev;

err_मुक्त:
	put_device(kdev);
	वापस ERR_PTR(r);
पूर्ण

/**
 * drm_class_device_रेजिस्टर - रेजिस्टर new device with the DRM sysfs class
 * @dev: device to रेजिस्टर
 *
 * Registers a new &काष्ठा device within the DRM sysfs class. Essentially only
 * used by tपंचांग to have a place क्रम its global settings. Drivers should never use
 * this.
 */
पूर्णांक drm_class_device_रेजिस्टर(काष्ठा device *dev)
अणु
	अगर (!drm_class || IS_ERR(drm_class))
		वापस -ENOENT;

	dev->class = drm_class;
	वापस device_रेजिस्टर(dev);
पूर्ण
EXPORT_SYMBOL_GPL(drm_class_device_रेजिस्टर);

/**
 * drm_class_device_unरेजिस्टर - unरेजिस्टर device with the DRM sysfs class
 * @dev: device to unरेजिस्टर
 *
 * Unरेजिस्टरs a &काष्ठा device from the DRM sysfs class. Essentially only used
 * by tपंचांग to have a place क्रम its global settings. Drivers should never use
 * this.
 */
व्योम drm_class_device_unरेजिस्टर(काष्ठा device *dev)
अणु
	वापस device_unरेजिस्टर(dev);
पूर्ण
EXPORT_SYMBOL_GPL(drm_class_device_unरेजिस्टर);
