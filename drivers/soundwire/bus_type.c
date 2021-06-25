<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright(c) 2015-17 Intel Corporation.

#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/soundwire/sdw.h>
#समावेश <linux/soundwire/sdw_type.h>
#समावेश "bus.h"
#समावेश "sysfs_local.h"

/**
 * sdw_get_device_id - find the matching SoundWire device id
 * @slave: SoundWire Slave Device
 * @drv: SoundWire Slave Driver
 *
 * The match is करोne by comparing the mfg_id and part_id from the
 * काष्ठा sdw_device_id.
 */
अटल स्थिर काष्ठा sdw_device_id *
sdw_get_device_id(काष्ठा sdw_slave *slave, काष्ठा sdw_driver *drv)
अणु
	स्थिर काष्ठा sdw_device_id *id;

	क्रम (id = drv->id_table; id && id->mfg_id; id++)
		अगर (slave->id.mfg_id == id->mfg_id &&
		    slave->id.part_id == id->part_id  &&
		    (!id->sdw_version ||
		     slave->id.sdw_version == id->sdw_version) &&
		    (!id->class_id ||
		     slave->id.class_id == id->class_id))
			वापस id;

	वापस शून्य;
पूर्ण

अटल पूर्णांक sdw_bus_match(काष्ठा device *dev, काष्ठा device_driver *ddrv)
अणु
	काष्ठा sdw_slave *slave;
	काष्ठा sdw_driver *drv;
	पूर्णांक ret = 0;

	अगर (is_sdw_slave(dev)) अणु
		slave = dev_to_sdw_dev(dev);
		drv = drv_to_sdw_driver(ddrv);

		ret = !!sdw_get_device_id(slave, drv);
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक sdw_slave_modalias(स्थिर काष्ठा sdw_slave *slave, अक्षर *buf, माप_प्रकार size)
अणु
	/* modalias is sdw:m<mfg_id>p<part_id>v<version>c<class_id> */

	वापस snम_लिखो(buf, size, "sdw:m%04Xp%04Xv%02Xc%02X\n",
			slave->id.mfg_id, slave->id.part_id,
			slave->id.sdw_version, slave->id.class_id);
पूर्ण

पूर्णांक sdw_slave_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा sdw_slave *slave = dev_to_sdw_dev(dev);
	अक्षर modalias[32];

	sdw_slave_modalias(slave, modalias, माप(modalias));

	अगर (add_uevent_var(env, "MODALIAS=%s", modalias))
		वापस -ENOMEM;

	वापस 0;
पूर्ण

काष्ठा bus_type sdw_bus_type = अणु
	.name = "soundwire",
	.match = sdw_bus_match,
पूर्ण;
EXPORT_SYMBOL_GPL(sdw_bus_type);

अटल पूर्णांक sdw_drv_probe(काष्ठा device *dev)
अणु
	काष्ठा sdw_slave *slave = dev_to_sdw_dev(dev);
	काष्ठा sdw_driver *drv = drv_to_sdw_driver(dev->driver);
	स्थिर काष्ठा sdw_device_id *id;
	स्थिर अक्षर *name;
	पूर्णांक ret;

	/*
	 * fw description is mandatory to bind
	 */
	अगर (!dev->fwnode)
		वापस -ENODEV;

	अगर (!IS_ENABLED(CONFIG_ACPI) && !dev->of_node)
		वापस -ENODEV;

	id = sdw_get_device_id(slave, drv);
	अगर (!id)
		वापस -ENODEV;

	slave->ops = drv->ops;

	/*
	 * attach to घातer करोमुख्य but करोn't turn on (last arg)
	 */
	ret = dev_pm_करोमुख्य_attach(dev, false);
	अगर (ret)
		वापस ret;

	ret = drv->probe(slave, id);
	अगर (ret) अणु
		name = drv->name;
		अगर (!name)
			name = drv->driver.name;
		dev_err(dev, "Probe of %s failed: %d\n", name, ret);
		dev_pm_करोमुख्य_detach(dev, false);
		वापस ret;
	पूर्ण

	/* device is probed so let's पढ़ो the properties now */
	अगर (slave->ops && slave->ops->पढ़ो_prop)
		slave->ops->पढ़ो_prop(slave);

	/* init the sysfs as we have properties now */
	ret = sdw_slave_sysfs_init(slave);
	अगर (ret < 0)
		dev_warn(dev, "Slave sysfs init failed:%d\n", ret);

	/*
	 * Check क्रम valid clk_stop_समयout, use DisCo worst हाल value of
	 * 300ms
	 *
	 * TODO: check the समयouts and driver removal हाल
	 */
	अगर (slave->prop.clk_stop_समयout == 0)
		slave->prop.clk_stop_समयout = 300;

	slave->bus->clk_stop_समयout = max_t(u32, slave->bus->clk_stop_समयout,
					     slave->prop.clk_stop_समयout);

	slave->probed = true;
	complete(&slave->probe_complete);

	dev_dbg(dev, "probe complete\n");

	वापस 0;
पूर्ण

अटल पूर्णांक sdw_drv_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा sdw_slave *slave = dev_to_sdw_dev(dev);
	काष्ठा sdw_driver *drv = drv_to_sdw_driver(dev->driver);
	पूर्णांक ret = 0;

	अगर (drv->हटाओ)
		ret = drv->हटाओ(slave);

	dev_pm_करोमुख्य_detach(dev, false);

	वापस ret;
पूर्ण

अटल व्योम sdw_drv_shutकरोwn(काष्ठा device *dev)
अणु
	काष्ठा sdw_slave *slave = dev_to_sdw_dev(dev);
	काष्ठा sdw_driver *drv = drv_to_sdw_driver(dev->driver);

	अगर (drv->shutकरोwn)
		drv->shutकरोwn(slave);
पूर्ण

/**
 * __sdw_रेजिस्टर_driver() - रेजिस्टर a SoundWire Slave driver
 * @drv: driver to रेजिस्टर
 * @owner: owning module/driver
 *
 * Return: zero on success, अन्यथा a negative error code.
 */
पूर्णांक __sdw_रेजिस्टर_driver(काष्ठा sdw_driver *drv, काष्ठा module *owner)
अणु
	स्थिर अक्षर *name;

	drv->driver.bus = &sdw_bus_type;

	अगर (!drv->probe) अणु
		name = drv->name;
		अगर (!name)
			name = drv->driver.name;

		pr_err("driver %s didn't provide SDW probe routine\n", name);
		वापस -EINVAL;
	पूर्ण

	drv->driver.owner = owner;
	drv->driver.probe = sdw_drv_probe;

	अगर (drv->हटाओ)
		drv->driver.हटाओ = sdw_drv_हटाओ;

	अगर (drv->shutकरोwn)
		drv->driver.shutकरोwn = sdw_drv_shutकरोwn;

	वापस driver_रेजिस्टर(&drv->driver);
पूर्ण
EXPORT_SYMBOL_GPL(__sdw_रेजिस्टर_driver);

/**
 * sdw_unरेजिस्टर_driver() - unरेजिस्टरs the SoundWire Slave driver
 * @drv: driver to unरेजिस्टर
 */
व्योम sdw_unरेजिस्टर_driver(काष्ठा sdw_driver *drv)
अणु
	driver_unरेजिस्टर(&drv->driver);
पूर्ण
EXPORT_SYMBOL_GPL(sdw_unरेजिस्टर_driver);

अटल पूर्णांक __init sdw_bus_init(व्योम)
अणु
	sdw_debugfs_init();
	वापस bus_रेजिस्टर(&sdw_bus_type);
पूर्ण

अटल व्योम __निकास sdw_bus_निकास(व्योम)
अणु
	sdw_debugfs_निकास();
	bus_unरेजिस्टर(&sdw_bus_type);
पूर्ण

postcore_initcall(sdw_bus_init);
module_निकास(sdw_bus_निकास);

MODULE_DESCRIPTION("SoundWire bus");
MODULE_LICENSE("GPL v2");
