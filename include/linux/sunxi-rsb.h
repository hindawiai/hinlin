<शैली गुरु>
/*
 * Allwinner Reduced Serial Bus Driver
 *
 * Copyright (c) 2015 Chen-Yu Tsai
 *
 * Author: Chen-Yu Tsai <wens@csie.org>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */
#अगर_अघोषित _SUNXI_RSB_H
#घोषणा _SUNXI_RSB_H

#समावेश <linux/device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/types.h>

काष्ठा sunxi_rsb;

/**
 * काष्ठा sunxi_rsb_device - Basic representation of an RSB device
 * @dev:	Driver model representation of the device.
 * @ctrl:	RSB controller managing the bus hosting this device.
 * @rtaddr:	This device's runसमय address
 * @hwaddr:	This device's hardware address
 */
काष्ठा sunxi_rsb_device अणु
	काष्ठा device		dev;
	काष्ठा sunxi_rsb	*rsb;
	पूर्णांक			irq;
	u8			rtaddr;
	u16			hwaddr;
पूर्ण;

अटल अंतरभूत काष्ठा sunxi_rsb_device *to_sunxi_rsb_device(काष्ठा device *d)
अणु
	वापस container_of(d, काष्ठा sunxi_rsb_device, dev);
पूर्ण

अटल अंतरभूत व्योम *sunxi_rsb_device_get_drvdata(स्थिर काष्ठा sunxi_rsb_device *rdev)
अणु
	वापस dev_get_drvdata(&rdev->dev);
पूर्ण

अटल अंतरभूत व्योम sunxi_rsb_device_set_drvdata(काष्ठा sunxi_rsb_device *rdev,
						व्योम *data)
अणु
	dev_set_drvdata(&rdev->dev, data);
पूर्ण

/**
 * काष्ठा sunxi_rsb_driver - RSB slave device driver
 * @driver:	RSB device drivers should initialize name and owner field of
 *		this काष्ठाure.
 * @probe:	binds this driver to a RSB device.
 * @हटाओ:	unbinds this driver from the RSB device.
 */
काष्ठा sunxi_rsb_driver अणु
	काष्ठा device_driver driver;
	पूर्णांक (*probe)(काष्ठा sunxi_rsb_device *rdev);
	व्योम (*हटाओ)(काष्ठा sunxi_rsb_device *rdev);
पूर्ण;

अटल अंतरभूत काष्ठा sunxi_rsb_driver *to_sunxi_rsb_driver(काष्ठा device_driver *d)
अणु
	वापस container_of(d, काष्ठा sunxi_rsb_driver, driver);
पूर्ण

पूर्णांक sunxi_rsb_driver_रेजिस्टर(काष्ठा sunxi_rsb_driver *rdrv);

/**
 * sunxi_rsb_driver_unरेजिस्टर() - unरेजिस्टर an RSB client driver
 * @rdrv:	the driver to unरेजिस्टर
 */
अटल अंतरभूत व्योम sunxi_rsb_driver_unरेजिस्टर(काष्ठा sunxi_rsb_driver *rdrv)
अणु
	अगर (rdrv)
		driver_unरेजिस्टर(&rdrv->driver);
पूर्ण

#घोषणा module_sunxi_rsb_driver(__sunxi_rsb_driver) \
	module_driver(__sunxi_rsb_driver, sunxi_rsb_driver_रेजिस्टर, \
			sunxi_rsb_driver_unरेजिस्टर)

काष्ठा regmap *__devm_regmap_init_sunxi_rsb(काष्ठा sunxi_rsb_device *rdev,
					    स्थिर काष्ठा regmap_config *config,
					    काष्ठा lock_class_key *lock_key,
					    स्थिर अक्षर *lock_name);

/**
 * devm_regmap_init_sunxi_rsb(): Initialise managed रेजिस्टर map
 *
 * @rdev: Device that will be पूर्णांकeracted with
 * @config: Configuration क्रम रेजिस्टर map
 *
 * The वापस value will be an ERR_PTR() on error or a valid poपूर्णांकer
 * to a काष्ठा regmap.  The regmap will be स्वतःmatically मुक्तd by the
 * device management code.
 */
#घोषणा devm_regmap_init_sunxi_rsb(rdev, config)			\
	__regmap_lockdep_wrapper(__devm_regmap_init_sunxi_rsb, #config,	\
				 rdev, config)

#पूर्ण_अगर /* _SUNXI_RSB_H */
