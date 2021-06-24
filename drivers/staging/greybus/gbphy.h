<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Greybus Bridged-Phy Bus driver
 *
 * Copyright 2016 Google Inc.
 */

#अगर_अघोषित __GBPHY_H
#घोषणा __GBPHY_H

काष्ठा gbphy_device अणु
	u32 id;
	काष्ठा greybus_descriptor_cport *cport_desc;
	काष्ठा gb_bundle *bundle;
	काष्ठा list_head list;
	काष्ठा device dev;
पूर्ण;
#घोषणा to_gbphy_dev(d) container_of(d, काष्ठा gbphy_device, dev)

अटल अंतरभूत व्योम *gb_gbphy_get_data(काष्ठा gbphy_device *gdev)
अणु
	वापस dev_get_drvdata(&gdev->dev);
पूर्ण

अटल अंतरभूत व्योम gb_gbphy_set_data(काष्ठा gbphy_device *gdev, व्योम *data)
अणु
	dev_set_drvdata(&gdev->dev, data);
पूर्ण

काष्ठा gbphy_device_id अणु
	__u8 protocol_id;
पूर्ण;

#घोषणा GBPHY_PROTOCOL(p)		\
	.protocol_id	= (p),

काष्ठा gbphy_driver अणु
	स्थिर अक्षर *name;
	पूर्णांक (*probe)(काष्ठा gbphy_device *device,
		     स्थिर काष्ठा gbphy_device_id *id);
	व्योम (*हटाओ)(काष्ठा gbphy_device *device);
	स्थिर काष्ठा gbphy_device_id *id_table;

	काष्ठा device_driver driver;
पूर्ण;
#घोषणा to_gbphy_driver(d) container_of(d, काष्ठा gbphy_driver, driver)

पूर्णांक gb_gbphy_रेजिस्टर_driver(काष्ठा gbphy_driver *driver,
			     काष्ठा module *owner, स्थिर अक्षर *mod_name);
व्योम gb_gbphy_deरेजिस्टर_driver(काष्ठा gbphy_driver *driver);

#घोषणा gb_gbphy_रेजिस्टर(driver) \
	gb_gbphy_रेजिस्टर_driver(driver, THIS_MODULE, KBUILD_MODNAME)
#घोषणा gb_gbphy_deरेजिस्टर(driver) \
	gb_gbphy_deरेजिस्टर_driver(driver)

/**
 * module_gbphy_driver() - Helper macro क्रम रेजिस्टरing a gbphy driver
 * @__gbphy_driver: gbphy_driver काष्ठाure
 *
 * Helper macro क्रम gbphy drivers to set up proper module init / निकास
 * functions.  Replaces module_init() and module_निकास() and keeps people from
 * prपूर्णांकing poपूर्णांकless things to the kernel log when their driver is loaded.
 */
#घोषणा module_gbphy_driver(__gbphy_driver)	\
	module_driver(__gbphy_driver, gb_gbphy_रेजिस्टर, gb_gbphy_deरेजिस्टर)

#अगर_घोषित CONFIG_PM
अटल अंतरभूत पूर्णांक gbphy_runसमय_get_sync(काष्ठा gbphy_device *gbphy_dev)
अणु
	काष्ठा device *dev = &gbphy_dev->dev;
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(dev);
	अगर (ret < 0) अणु
		dev_err(dev, "pm_runtime_get_sync failed: %d\n", ret);
		pm_runसमय_put_noidle(dev);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम gbphy_runसमय_put_स्वतःsuspend(काष्ठा gbphy_device *gbphy_dev)
अणु
	काष्ठा device *dev = &gbphy_dev->dev;

	pm_runसमय_mark_last_busy(dev);
	pm_runसमय_put_स्वतःsuspend(dev);
पूर्ण

अटल अंतरभूत व्योम gbphy_runसमय_get_noresume(काष्ठा gbphy_device *gbphy_dev)
अणु
	pm_runसमय_get_noresume(&gbphy_dev->dev);
पूर्ण

अटल अंतरभूत व्योम gbphy_runसमय_put_noidle(काष्ठा gbphy_device *gbphy_dev)
अणु
	pm_runसमय_put_noidle(&gbphy_dev->dev);
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक gbphy_runसमय_get_sync(काष्ठा gbphy_device *gbphy_dev) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम gbphy_runसमय_put_स्वतःsuspend(काष्ठा gbphy_device *gbphy_dev) अणुपूर्ण
अटल अंतरभूत व्योम gbphy_runसमय_get_noresume(काष्ठा gbphy_device *gbphy_dev) अणुपूर्ण
अटल अंतरभूत व्योम gbphy_runसमय_put_noidle(काष्ठा gbphy_device *gbphy_dev) अणुपूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __GBPHY_H */

