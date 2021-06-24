<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_ULPI_DRIVER_H
#घोषणा __LINUX_ULPI_DRIVER_H

#समावेश <linux/mod_devicetable.h>

#समावेश <linux/device.h>

काष्ठा ulpi_ops;

/**
 * काष्ठा ulpi - describes ULPI PHY device
 * @id: venकरोr and product ids क्रम ULPI device
 * @ops: I/O access
 * @dev: device पूर्णांकerface
 */
काष्ठा ulpi अणु
	काष्ठा ulpi_device_id id;
	स्थिर काष्ठा ulpi_ops *ops;
	काष्ठा device dev;
पूर्ण;

#घोषणा to_ulpi_dev(d) container_of(d, काष्ठा ulpi, dev)

अटल अंतरभूत व्योम ulpi_set_drvdata(काष्ठा ulpi *ulpi, व्योम *data)
अणु
	dev_set_drvdata(&ulpi->dev, data);
पूर्ण

अटल अंतरभूत व्योम *ulpi_get_drvdata(काष्ठा ulpi *ulpi)
अणु
	वापस dev_get_drvdata(&ulpi->dev);
पूर्ण

/**
 * काष्ठा ulpi_driver - describes a ULPI PHY driver
 * @id_table: array of device identअगरiers supported by this driver
 * @probe: binds this driver to ULPI device
 * @हटाओ: unbinds this driver from ULPI device
 * @driver: the name and owner members must be initialized by the drivers
 */
काष्ठा ulpi_driver अणु
	स्थिर काष्ठा ulpi_device_id *id_table;
	पूर्णांक (*probe)(काष्ठा ulpi *ulpi);
	व्योम (*हटाओ)(काष्ठा ulpi *ulpi);
	काष्ठा device_driver driver;
पूर्ण;

#घोषणा to_ulpi_driver(d) container_of(d, काष्ठा ulpi_driver, driver)

/*
 * use a macro to aव्योम include chaining to get THIS_MODULE
 */
#घोषणा ulpi_रेजिस्टर_driver(drv) __ulpi_रेजिस्टर_driver(drv, THIS_MODULE)
पूर्णांक __ulpi_रेजिस्टर_driver(काष्ठा ulpi_driver *drv, काष्ठा module *module);
व्योम ulpi_unरेजिस्टर_driver(काष्ठा ulpi_driver *drv);

#घोषणा module_ulpi_driver(__ulpi_driver) \
	module_driver(__ulpi_driver, ulpi_रेजिस्टर_driver, \
		      ulpi_unरेजिस्टर_driver)

पूर्णांक ulpi_पढ़ो(काष्ठा ulpi *ulpi, u8 addr);
पूर्णांक ulpi_ग_लिखो(काष्ठा ulpi *ulpi, u8 addr, u8 val);

#पूर्ण_अगर /* __LINUX_ULPI_DRIVER_H */
