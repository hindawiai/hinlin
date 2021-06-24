<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  hdac-ext-bus.c - HD-audio extended core bus functions.
 *
 *  Copyright (C) 2014-2015 Intel Corp
 *  Author: Jeeja KP <jeeja.kp@पूर्णांकel.com>
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <sound/hdaudio_ext.h>

MODULE_DESCRIPTION("HDA extended core");
MODULE_LICENSE("GPL v2");

/**
 * snd_hdac_ext_bus_init - initialize a HD-audio extended bus
 * @bus: the poपूर्णांकer to HDAC bus object
 * @dev: device poपूर्णांकer
 * @ops: bus verb चालकs
 * @ext_ops: चालकs used क्रम ASoC HDA codec drivers
 *
 * Returns 0 अगर successful, or a negative error code.
 */
पूर्णांक snd_hdac_ext_bus_init(काष्ठा hdac_bus *bus, काष्ठा device *dev,
			स्थिर काष्ठा hdac_bus_ops *ops,
			स्थिर काष्ठा hdac_ext_bus_ops *ext_ops)
अणु
	पूर्णांक ret;

	ret = snd_hdac_bus_init(bus, dev, ops);
	अगर (ret < 0)
		वापस ret;

	bus->ext_ops = ext_ops;
	/* FIXME:
	 * Currently only one bus is supported, अगर there is device with more
	 * buses, bus->idx should be greater than 0, but there needs to be a
	 * reliable way to always assign same number.
	 */
	bus->idx = 0;
	bus->cmd_dma_state = true;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_ext_bus_init);

/**
 * snd_hdac_ext_bus_निकास - clean up a HD-audio extended bus
 * @bus: the poपूर्णांकer to HDAC bus object
 */
व्योम snd_hdac_ext_bus_निकास(काष्ठा hdac_bus *bus)
अणु
	snd_hdac_bus_निकास(bus);
	WARN_ON(!list_empty(&bus->hlink_list));
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_ext_bus_निकास);

अटल व्योम शेष_release(काष्ठा device *dev)
अणु
	snd_hdac_ext_bus_device_निकास(dev_to_hdac_dev(dev));
पूर्ण

/**
 * snd_hdac_ext_bus_device_init - initialize the HDA extended codec base device
 * @bus: hdac bus to attach to
 * @addr: codec address
 * @hdev: hdac device to init
 * @type: codec type (HDAC_DEV_*) to use क्रम this device
 *
 * Returns zero क्रम success or a negative error code.
 */
पूर्णांक snd_hdac_ext_bus_device_init(काष्ठा hdac_bus *bus, पूर्णांक addr,
				 काष्ठा hdac_device *hdev, पूर्णांक type)
अणु
	अक्षर name[15];
	पूर्णांक ret;

	hdev->bus = bus;

	snम_लिखो(name, माप(name), "ehdaudio%dD%d", bus->idx, addr);

	ret  = snd_hdac_device_init(hdev, bus, name, addr);
	अगर (ret < 0) अणु
		dev_err(bus->dev, "device init failed for hdac device\n");
		वापस ret;
	पूर्ण
	hdev->type = type;
	hdev->dev.release = शेष_release;

	ret = snd_hdac_device_रेजिस्टर(hdev);
	अगर (ret) अणु
		dev_err(bus->dev, "failed to register hdac device\n");
		snd_hdac_ext_bus_device_निकास(hdev);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_ext_bus_device_init);

/**
 * snd_hdac_ext_bus_device_निकास - clean up a HD-audio extended codec base device
 * @hdev: hdac device to clean up
 */
व्योम snd_hdac_ext_bus_device_निकास(काष्ठा hdac_device *hdev)
अणु
	snd_hdac_device_निकास(hdev);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_ext_bus_device_निकास);

/**
 * snd_hdac_ext_bus_device_हटाओ - हटाओ HD-audio extended codec base devices
 *
 * @bus: the poपूर्णांकer to HDAC bus object
 */
व्योम snd_hdac_ext_bus_device_हटाओ(काष्ठा hdac_bus *bus)
अणु
	काष्ठा hdac_device *codec, *__codec;
	/*
	 * we need to हटाओ all the codec devices objects created in the
	 * snd_hdac_ext_bus_device_init
	 */
	list_क्रम_each_entry_safe(codec, __codec, &bus->codec_list, list) अणु
		snd_hdac_device_unरेजिस्टर(codec);
		put_device(&codec->dev);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_ext_bus_device_हटाओ);
#घोषणा dev_to_hdac(dev) (container_of((dev), \
			काष्ठा hdac_device, dev))

अटल अंतरभूत काष्ठा hdac_driver *get_hdrv(काष्ठा device *dev)
अणु
	काष्ठा hdac_driver *hdrv = drv_to_hdac_driver(dev->driver);
	वापस hdrv;
पूर्ण

अटल अंतरभूत काष्ठा hdac_device *get_hdev(काष्ठा device *dev)
अणु
	काष्ठा hdac_device *hdev = dev_to_hdac_dev(dev);
	वापस hdev;
पूर्ण

अटल पूर्णांक hda_ext_drv_probe(काष्ठा device *dev)
अणु
	वापस (get_hdrv(dev))->probe(get_hdev(dev));
पूर्ण

अटल पूर्णांक hdac_ext_drv_हटाओ(काष्ठा device *dev)
अणु
	वापस (get_hdrv(dev))->हटाओ(get_hdev(dev));
पूर्ण

अटल व्योम hdac_ext_drv_shutकरोwn(काष्ठा device *dev)
अणु
	वापस (get_hdrv(dev))->shutकरोwn(get_hdev(dev));
पूर्ण

/**
 * snd_hda_ext_driver_रेजिस्टर - रेजिस्टर a driver क्रम ext hda devices
 *
 * @drv: ext hda driver काष्ठाure
 */
पूर्णांक snd_hda_ext_driver_रेजिस्टर(काष्ठा hdac_driver *drv)
अणु
	drv->type = HDA_DEV_ASOC;
	drv->driver.bus = &snd_hda_bus_type;
	/* we use शेष match */

	अगर (drv->probe)
		drv->driver.probe = hda_ext_drv_probe;
	अगर (drv->हटाओ)
		drv->driver.हटाओ = hdac_ext_drv_हटाओ;
	अगर (drv->shutकरोwn)
		drv->driver.shutकरोwn = hdac_ext_drv_shutकरोwn;

	वापस driver_रेजिस्टर(&drv->driver);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_ext_driver_रेजिस्टर);

/**
 * snd_hda_ext_driver_unरेजिस्टर - unरेजिस्टर a driver क्रम ext hda devices
 *
 * @drv: ext hda driver काष्ठाure
 */
व्योम snd_hda_ext_driver_unरेजिस्टर(काष्ठा hdac_driver *drv)
अणु
	driver_unरेजिस्टर(&drv->driver);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_ext_driver_unरेजिस्टर);
