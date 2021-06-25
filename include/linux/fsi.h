<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* FSI device & driver पूर्णांकerfaces
 *
 * Copyright (C) IBM Corporation 2016
 */

#अगर_अघोषित LINUX_FSI_H
#घोषणा LINUX_FSI_H

#समावेश <linux/device.h>

काष्ठा fsi_device अणु
	काष्ठा device		dev;
	u8			engine_type;
	u8			version;
	u8			unit;
	काष्ठा fsi_slave	*slave;
	uपूर्णांक32_t		addr;
	uपूर्णांक32_t		size;
पूर्ण;

बाह्य पूर्णांक fsi_device_पढ़ो(काष्ठा fsi_device *dev, uपूर्णांक32_t addr,
		व्योम *val, माप_प्रकार size);
बाह्य पूर्णांक fsi_device_ग_लिखो(काष्ठा fsi_device *dev, uपूर्णांक32_t addr,
		स्थिर व्योम *val, माप_प्रकार size);
बाह्य पूर्णांक fsi_device_peek(काष्ठा fsi_device *dev, व्योम *val);

काष्ठा fsi_device_id अणु
	u8	engine_type;
	u8	version;
पूर्ण;

#घोषणा FSI_VERSION_ANY		0

#घोषणा FSI_DEVICE(t) \
	.engine_type = (t), .version = FSI_VERSION_ANY,

#घोषणा FSI_DEVICE_VERSIONED(t, v) \
	.engine_type = (t), .version = (v),

काष्ठा fsi_driver अणु
	काष्ठा device_driver		drv;
	स्थिर काष्ठा fsi_device_id	*id_table;
पूर्ण;

#घोषणा to_fsi_dev(devp) container_of(devp, काष्ठा fsi_device, dev)
#घोषणा to_fsi_drv(drvp) container_of(drvp, काष्ठा fsi_driver, drv)

बाह्य पूर्णांक fsi_driver_रेजिस्टर(काष्ठा fsi_driver *fsi_drv);
बाह्य व्योम fsi_driver_unरेजिस्टर(काष्ठा fsi_driver *fsi_drv);

/* module_fsi_driver() - Helper macro क्रम drivers that करोn't करो
 * anything special in module init/निकास.  This eliminates a lot of
 * boilerplate.  Each module may only use this macro once, and
 * calling it replaces module_init() and module_निकास()
 */
#घोषणा module_fsi_driver(__fsi_driver) \
		module_driver(__fsi_driver, fsi_driver_रेजिस्टर, \
				fsi_driver_unरेजिस्टर)

/* direct slave API */
बाह्य पूर्णांक fsi_slave_claim_range(काष्ठा fsi_slave *slave,
		uपूर्णांक32_t addr, uपूर्णांक32_t size);
बाह्य व्योम fsi_slave_release_range(काष्ठा fsi_slave *slave,
		uपूर्णांक32_t addr, uपूर्णांक32_t size);
बाह्य पूर्णांक fsi_slave_पढ़ो(काष्ठा fsi_slave *slave, uपूर्णांक32_t addr,
		व्योम *val, माप_प्रकार size);
बाह्य पूर्णांक fsi_slave_ग_लिखो(काष्ठा fsi_slave *slave, uपूर्णांक32_t addr,
		स्थिर व्योम *val, माप_प्रकार size);

बाह्य काष्ठा bus_type fsi_bus_type;
बाह्य स्थिर काष्ठा device_type fsi_cdev_type;

क्रमागत fsi_dev_type अणु
	fsi_dev_cfam,
	fsi_dev_sbefअगरo,
	fsi_dev_scom,
	fsi_dev_occ
पूर्ण;

बाह्य पूर्णांक fsi_get_new_minor(काष्ठा fsi_device *fdev, क्रमागत fsi_dev_type type,
			     dev_t *out_dev, पूर्णांक *out_index);
बाह्य व्योम fsi_मुक्त_minor(dev_t dev);

#पूर्ण_अगर /* LINUX_FSI_H */
