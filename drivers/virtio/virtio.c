<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/virtपन.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/virtio_config.h>
#समावेश <linux/module.h>
#समावेश <linux/idr.h>
#समावेश <uapi/linux/virtio_ids.h>

/* Unique numbering क्रम virtio devices. */
अटल DEFINE_IDA(virtio_index_ida);

अटल sमाप_प्रकार device_show(काष्ठा device *_d,
			   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा virtio_device *dev = dev_to_virtio(_d);
	वापस प्र_लिखो(buf, "0x%04x\n", dev->id.device);
पूर्ण
अटल DEVICE_ATTR_RO(device);

अटल sमाप_प्रकार venकरोr_show(काष्ठा device *_d,
			   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा virtio_device *dev = dev_to_virtio(_d);
	वापस प्र_लिखो(buf, "0x%04x\n", dev->id.venकरोr);
पूर्ण
अटल DEVICE_ATTR_RO(venकरोr);

अटल sमाप_प्रकार status_show(काष्ठा device *_d,
			   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा virtio_device *dev = dev_to_virtio(_d);
	वापस प्र_लिखो(buf, "0x%08x\n", dev->config->get_status(dev));
पूर्ण
अटल DEVICE_ATTR_RO(status);

अटल sमाप_प्रकार modalias_show(काष्ठा device *_d,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा virtio_device *dev = dev_to_virtio(_d);
	वापस प्र_लिखो(buf, "virtio:d%08Xv%08X\n",
		       dev->id.device, dev->id.venकरोr);
पूर्ण
अटल DEVICE_ATTR_RO(modalias);

अटल sमाप_प्रकार features_show(काष्ठा device *_d,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा virtio_device *dev = dev_to_virtio(_d);
	अचिन्हित पूर्णांक i;
	sमाप_प्रकार len = 0;

	/* We actually represent this as a bitstring, as it could be
	 * arbitrary length in future. */
	क्रम (i = 0; i < माप(dev->features)*8; i++)
		len += प्र_लिखो(buf+len, "%c",
			       __virtio_test_bit(dev, i) ? '1' : '0');
	len += प्र_लिखो(buf+len, "\n");
	वापस len;
पूर्ण
अटल DEVICE_ATTR_RO(features);

अटल काष्ठा attribute *virtio_dev_attrs[] = अणु
	&dev_attr_device.attr,
	&dev_attr_venकरोr.attr,
	&dev_attr_status.attr,
	&dev_attr_modalias.attr,
	&dev_attr_features.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(virtio_dev);

अटल अंतरभूत पूर्णांक virtio_id_match(स्थिर काष्ठा virtio_device *dev,
				  स्थिर काष्ठा virtio_device_id *id)
अणु
	अगर (id->device != dev->id.device && id->device != VIRTIO_DEV_ANY_ID)
		वापस 0;

	वापस id->venकरोr == VIRTIO_DEV_ANY_ID || id->venकरोr == dev->id.venकरोr;
पूर्ण

/* This looks through all the IDs a driver claims to support.  If any of them
 * match, we वापस 1 and the kernel will call virtio_dev_probe(). */
अटल पूर्णांक virtio_dev_match(काष्ठा device *_dv, काष्ठा device_driver *_dr)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा virtio_device *dev = dev_to_virtio(_dv);
	स्थिर काष्ठा virtio_device_id *ids;

	ids = drv_to_virtio(_dr)->id_table;
	क्रम (i = 0; ids[i].device; i++)
		अगर (virtio_id_match(dev, &ids[i]))
			वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक virtio_uevent(काष्ठा device *_dv, काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा virtio_device *dev = dev_to_virtio(_dv);

	वापस add_uevent_var(env, "MODALIAS=virtio:d%08Xv%08X",
			      dev->id.device, dev->id.venकरोr);
पूर्ण

व्योम virtio_check_driver_offered_feature(स्थिर काष्ठा virtio_device *vdev,
					 अचिन्हित पूर्णांक fbit)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा virtio_driver *drv = drv_to_virtio(vdev->dev.driver);

	क्रम (i = 0; i < drv->feature_table_size; i++)
		अगर (drv->feature_table[i] == fbit)
			वापस;

	अगर (drv->feature_table_legacy) अणु
		क्रम (i = 0; i < drv->feature_table_size_legacy; i++)
			अगर (drv->feature_table_legacy[i] == fbit)
				वापस;
	पूर्ण

	BUG();
पूर्ण
EXPORT_SYMBOL_GPL(virtio_check_driver_offered_feature);

अटल व्योम __virtio_config_changed(काष्ठा virtio_device *dev)
अणु
	काष्ठा virtio_driver *drv = drv_to_virtio(dev->dev.driver);

	अगर (!dev->config_enabled)
		dev->config_change_pending = true;
	अन्यथा अगर (drv && drv->config_changed)
		drv->config_changed(dev);
पूर्ण

व्योम virtio_config_changed(काष्ठा virtio_device *dev)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->config_lock, flags);
	__virtio_config_changed(dev);
	spin_unlock_irqrestore(&dev->config_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(virtio_config_changed);

अटल व्योम virtio_config_disable(काष्ठा virtio_device *dev)
अणु
	spin_lock_irq(&dev->config_lock);
	dev->config_enabled = false;
	spin_unlock_irq(&dev->config_lock);
पूर्ण

अटल व्योम virtio_config_enable(काष्ठा virtio_device *dev)
अणु
	spin_lock_irq(&dev->config_lock);
	dev->config_enabled = true;
	अगर (dev->config_change_pending)
		__virtio_config_changed(dev);
	dev->config_change_pending = false;
	spin_unlock_irq(&dev->config_lock);
पूर्ण

व्योम virtio_add_status(काष्ठा virtio_device *dev, अचिन्हित पूर्णांक status)
अणु
	might_sleep();
	dev->config->set_status(dev, dev->config->get_status(dev) | status);
पूर्ण
EXPORT_SYMBOL_GPL(virtio_add_status);

पूर्णांक virtio_finalize_features(काष्ठा virtio_device *dev)
अणु
	पूर्णांक ret = dev->config->finalize_features(dev);
	अचिन्हित status;

	might_sleep();
	अगर (ret)
		वापस ret;

	ret = arch_has_restricted_virtio_memory_access();
	अगर (ret) अणु
		अगर (!virtio_has_feature(dev, VIRTIO_F_VERSION_1)) अणु
			dev_warn(&dev->dev,
				 "device must provide VIRTIO_F_VERSION_1\n");
			वापस -ENODEV;
		पूर्ण

		अगर (!virtio_has_feature(dev, VIRTIO_F_ACCESS_PLATFORM)) अणु
			dev_warn(&dev->dev,
				 "device must provide VIRTIO_F_ACCESS_PLATFORM\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	अगर (!virtio_has_feature(dev, VIRTIO_F_VERSION_1))
		वापस 0;

	virtio_add_status(dev, VIRTIO_CONFIG_S_FEATURES_OK);
	status = dev->config->get_status(dev);
	अगर (!(status & VIRTIO_CONFIG_S_FEATURES_OK)) अणु
		dev_err(&dev->dev, "virtio: device refuses features: %x\n",
			status);
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(virtio_finalize_features);

अटल पूर्णांक virtio_dev_probe(काष्ठा device *_d)
अणु
	पूर्णांक err, i;
	काष्ठा virtio_device *dev = dev_to_virtio(_d);
	काष्ठा virtio_driver *drv = drv_to_virtio(dev->dev.driver);
	u64 device_features;
	u64 driver_features;
	u64 driver_features_legacy;

	/* We have a driver! */
	virtio_add_status(dev, VIRTIO_CONFIG_S_DRIVER);

	/* Figure out what features the device supports. */
	device_features = dev->config->get_features(dev);

	/* Figure out what features the driver supports. */
	driver_features = 0;
	क्रम (i = 0; i < drv->feature_table_size; i++) अणु
		अचिन्हित पूर्णांक f = drv->feature_table[i];
		BUG_ON(f >= 64);
		driver_features |= (1ULL << f);
	पूर्ण

	/* Some drivers have a separate feature table क्रम virtio v1.0 */
	अगर (drv->feature_table_legacy) अणु
		driver_features_legacy = 0;
		क्रम (i = 0; i < drv->feature_table_size_legacy; i++) अणु
			अचिन्हित पूर्णांक f = drv->feature_table_legacy[i];
			BUG_ON(f >= 64);
			driver_features_legacy |= (1ULL << f);
		पूर्ण
	पूर्ण अन्यथा अणु
		driver_features_legacy = driver_features;
	पूर्ण

	अगर (device_features & (1ULL << VIRTIO_F_VERSION_1))
		dev->features = driver_features & device_features;
	अन्यथा
		dev->features = driver_features_legacy & device_features;

	/* Transport features always preserved to pass to finalize_features. */
	क्रम (i = VIRTIO_TRANSPORT_F_START; i < VIRTIO_TRANSPORT_F_END; i++)
		अगर (device_features & (1ULL << i))
			__virtio_set_bit(dev, i);

	अगर (drv->validate) अणु
		err = drv->validate(dev);
		अगर (err)
			जाओ err;
	पूर्ण

	err = virtio_finalize_features(dev);
	अगर (err)
		जाओ err;

	err = drv->probe(dev);
	अगर (err)
		जाओ err;

	/* If probe didn't करो it, mark device DRIVER_OK ourselves. */
	अगर (!(dev->config->get_status(dev) & VIRTIO_CONFIG_S_DRIVER_OK))
		virtio_device_पढ़ोy(dev);

	अगर (drv->scan)
		drv->scan(dev);

	virtio_config_enable(dev);

	वापस 0;
err:
	virtio_add_status(dev, VIRTIO_CONFIG_S_FAILED);
	वापस err;

पूर्ण

अटल पूर्णांक virtio_dev_हटाओ(काष्ठा device *_d)
अणु
	काष्ठा virtio_device *dev = dev_to_virtio(_d);
	काष्ठा virtio_driver *drv = drv_to_virtio(dev->dev.driver);

	virtio_config_disable(dev);

	drv->हटाओ(dev);

	/* Driver should have reset device. */
	WARN_ON_ONCE(dev->config->get_status(dev));

	/* Acknowledge the device's existence again. */
	virtio_add_status(dev, VIRTIO_CONFIG_S_ACKNOWLEDGE);
	वापस 0;
पूर्ण

अटल काष्ठा bus_type virtio_bus = अणु
	.name  = "virtio",
	.match = virtio_dev_match,
	.dev_groups = virtio_dev_groups,
	.uevent = virtio_uevent,
	.probe = virtio_dev_probe,
	.हटाओ = virtio_dev_हटाओ,
पूर्ण;

पूर्णांक रेजिस्टर_virtio_driver(काष्ठा virtio_driver *driver)
अणु
	/* Catch this early. */
	BUG_ON(driver->feature_table_size && !driver->feature_table);
	driver->driver.bus = &virtio_bus;
	वापस driver_रेजिस्टर(&driver->driver);
पूर्ण
EXPORT_SYMBOL_GPL(रेजिस्टर_virtio_driver);

व्योम unरेजिस्टर_virtio_driver(काष्ठा virtio_driver *driver)
अणु
	driver_unरेजिस्टर(&driver->driver);
पूर्ण
EXPORT_SYMBOL_GPL(unरेजिस्टर_virtio_driver);

/**
 * रेजिस्टर_virtio_device - रेजिस्टर virtio device
 * @dev        : virtio device to be रेजिस्टरed
 *
 * On error, the caller must call put_device on &@dev->dev (and not kमुक्त),
 * as another code path may have obtained a reference to @dev.
 *
 * Returns: 0 on suceess, -error on failure
 */
पूर्णांक रेजिस्टर_virtio_device(काष्ठा virtio_device *dev)
अणु
	पूर्णांक err;

	dev->dev.bus = &virtio_bus;
	device_initialize(&dev->dev);

	/* Assign a unique device index and hence name. */
	err = ida_simple_get(&virtio_index_ida, 0, 0, GFP_KERNEL);
	अगर (err < 0)
		जाओ out;

	dev->index = err;
	dev_set_name(&dev->dev, "virtio%u", dev->index);

	spin_lock_init(&dev->config_lock);
	dev->config_enabled = false;
	dev->config_change_pending = false;

	/* We always start by resetting the device, in हाल a previous
	 * driver messed it up.  This also tests that code path a little. */
	dev->config->reset(dev);

	/* Acknowledge that we've seen the device. */
	virtio_add_status(dev, VIRTIO_CONFIG_S_ACKNOWLEDGE);

	INIT_LIST_HEAD(&dev->vqs);

	/*
	 * device_add() causes the bus infraकाष्ठाure to look क्रम a matching
	 * driver.
	 */
	err = device_add(&dev->dev);
	अगर (err)
		ida_simple_हटाओ(&virtio_index_ida, dev->index);
out:
	अगर (err)
		virtio_add_status(dev, VIRTIO_CONFIG_S_FAILED);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(रेजिस्टर_virtio_device);

bool is_virtio_device(काष्ठा device *dev)
अणु
	वापस dev->bus == &virtio_bus;
पूर्ण
EXPORT_SYMBOL_GPL(is_virtio_device);

व्योम unरेजिस्टर_virtio_device(काष्ठा virtio_device *dev)
अणु
	पूर्णांक index = dev->index; /* save क्रम after device release */

	device_unरेजिस्टर(&dev->dev);
	ida_simple_हटाओ(&virtio_index_ida, index);
पूर्ण
EXPORT_SYMBOL_GPL(unरेजिस्टर_virtio_device);

#अगर_घोषित CONFIG_PM_SLEEP
पूर्णांक virtio_device_मुक्तze(काष्ठा virtio_device *dev)
अणु
	काष्ठा virtio_driver *drv = drv_to_virtio(dev->dev.driver);

	virtio_config_disable(dev);

	dev->failed = dev->config->get_status(dev) & VIRTIO_CONFIG_S_FAILED;

	अगर (drv && drv->मुक्तze)
		वापस drv->मुक्तze(dev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(virtio_device_मुक्तze);

पूर्णांक virtio_device_restore(काष्ठा virtio_device *dev)
अणु
	काष्ठा virtio_driver *drv = drv_to_virtio(dev->dev.driver);
	पूर्णांक ret;

	/* We always start by resetting the device, in हाल a previous
	 * driver messed it up. */
	dev->config->reset(dev);

	/* Acknowledge that we've seen the device. */
	virtio_add_status(dev, VIRTIO_CONFIG_S_ACKNOWLEDGE);

	/* Maybe driver failed beक्रमe मुक्तze.
	 * Restore the failed status, क्रम debugging. */
	अगर (dev->failed)
		virtio_add_status(dev, VIRTIO_CONFIG_S_FAILED);

	अगर (!drv)
		वापस 0;

	/* We have a driver! */
	virtio_add_status(dev, VIRTIO_CONFIG_S_DRIVER);

	ret = virtio_finalize_features(dev);
	अगर (ret)
		जाओ err;

	अगर (drv->restore) अणु
		ret = drv->restore(dev);
		अगर (ret)
			जाओ err;
	पूर्ण

	/* Finally, tell the device we're all set */
	virtio_add_status(dev, VIRTIO_CONFIG_S_DRIVER_OK);

	virtio_config_enable(dev);

	वापस 0;

err:
	virtio_add_status(dev, VIRTIO_CONFIG_S_FAILED);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(virtio_device_restore);
#पूर्ण_अगर

अटल पूर्णांक virtio_init(व्योम)
अणु
	अगर (bus_रेजिस्टर(&virtio_bus) != 0)
		panic("virtio bus registration failed");
	वापस 0;
पूर्ण

अटल व्योम __निकास virtio_निकास(व्योम)
अणु
	bus_unरेजिस्टर(&virtio_bus);
	ida_destroy(&virtio_index_ida);
पूर्ण
core_initcall(virtio_init);
module_निकास(virtio_निकास);

MODULE_LICENSE("GPL");
