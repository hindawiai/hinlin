<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2013-2016, Intel Corporation. All rights reserved.
 */
#अगर_अघोषित _LINUX_MEI_CL_BUS_H
#घोषणा _LINUX_MEI_CL_BUS_H

#समावेश <linux/device.h>
#समावेश <linux/uuid.h>
#समावेश <linux/mod_devicetable.h>

काष्ठा mei_cl_device;
काष्ठा mei_device;

प्रकार व्योम (*mei_cldev_cb_t)(काष्ठा mei_cl_device *cldev);

/**
 * काष्ठा mei_cl_device - MEI device handle
 * An mei_cl_device poपूर्णांकer is वापसed from mei_add_device()
 * and links MEI bus clients to their actual ME host client poपूर्णांकer.
 * Drivers क्रम MEI devices will get an mei_cl_device poपूर्णांकer
 * when being probed and shall use it क्रम करोing ME bus I/O.
 *
 * @bus_list: device on the bus list
 * @bus: parent mei device
 * @dev: linux driver model device poपूर्णांकer
 * @me_cl: me client
 * @cl: mei client
 * @name: device name
 * @rx_work: async work to execute Rx event callback
 * @rx_cb: Drivers रेजिस्टर this callback to get asynchronous ME
 *	Rx buffer pending notअगरications.
 * @notअगर_work: async work to execute FW notअगर event callback
 * @notअगर_cb: Drivers रेजिस्टर this callback to get asynchronous ME
 *	FW notअगरication pending notअगरications.
 *
 * @करो_match: wheather device can be matched with a driver
 * @is_added: device is alपढ़ोy scanned
 * @priv_data: client निजी data
 */
काष्ठा mei_cl_device अणु
	काष्ठा list_head bus_list;
	काष्ठा mei_device *bus;
	काष्ठा device dev;

	काष्ठा mei_me_client *me_cl;
	काष्ठा mei_cl *cl;
	अक्षर name[MEI_CL_NAME_SIZE];

	काष्ठा work_काष्ठा rx_work;
	mei_cldev_cb_t rx_cb;
	काष्ठा work_काष्ठा notअगर_work;
	mei_cldev_cb_t notअगर_cb;

	अचिन्हित पूर्णांक करो_match:1;
	अचिन्हित पूर्णांक is_added:1;

	व्योम *priv_data;
पूर्ण;

#घोषणा to_mei_cl_device(d) container_of(d, काष्ठा mei_cl_device, dev)

काष्ठा mei_cl_driver अणु
	काष्ठा device_driver driver;
	स्थिर अक्षर *name;

	स्थिर काष्ठा mei_cl_device_id *id_table;

	पूर्णांक (*probe)(काष्ठा mei_cl_device *cldev,
		     स्थिर काष्ठा mei_cl_device_id *id);
	व्योम (*हटाओ)(काष्ठा mei_cl_device *cldev);
पूर्ण;

पूर्णांक __mei_cldev_driver_रेजिस्टर(काष्ठा mei_cl_driver *cldrv,
				काष्ठा module *owner);
#घोषणा mei_cldev_driver_रेजिस्टर(cldrv)             \
	__mei_cldev_driver_रेजिस्टर(cldrv, THIS_MODULE)

व्योम mei_cldev_driver_unरेजिस्टर(काष्ठा mei_cl_driver *cldrv);

/**
 * module_mei_cl_driver - Helper macro क्रम रेजिस्टरing mei cl driver
 *
 * @__mei_cldrv: mei_cl_driver काष्ठाure
 *
 *  Helper macro क्रम mei cl drivers which करो not करो anything special in module
 *  init/निकास, क्रम eliminating a boilerplate code.
 */
#घोषणा module_mei_cl_driver(__mei_cldrv) \
	module_driver(__mei_cldrv, \
		      mei_cldev_driver_रेजिस्टर,\
		      mei_cldev_driver_unरेजिस्टर)

sमाप_प्रकार mei_cldev_send(काष्ठा mei_cl_device *cldev, u8 *buf, माप_प्रकार length);
sमाप_प्रकार mei_cldev_recv(काष्ठा mei_cl_device *cldev, u8 *buf, माप_प्रकार length);
sमाप_प्रकार mei_cldev_recv_nonblock(काष्ठा mei_cl_device *cldev, u8 *buf,
				माप_प्रकार length);
sमाप_प्रकार mei_cldev_send_vtag(काष्ठा mei_cl_device *cldev, u8 *buf, माप_प्रकार length,
			    u8 vtag);
sमाप_प्रकार mei_cldev_recv_vtag(काष्ठा mei_cl_device *cldev, u8 *buf, माप_प्रकार length,
			    u8 *vtag);
sमाप_प्रकार mei_cldev_recv_nonblock_vtag(काष्ठा mei_cl_device *cldev, u8 *buf,
				     माप_प्रकार length, u8 *vtag);

पूर्णांक mei_cldev_रेजिस्टर_rx_cb(काष्ठा mei_cl_device *cldev, mei_cldev_cb_t rx_cb);
पूर्णांक mei_cldev_रेजिस्टर_notअगर_cb(काष्ठा mei_cl_device *cldev,
				mei_cldev_cb_t notअगर_cb);

स्थिर uuid_le *mei_cldev_uuid(स्थिर काष्ठा mei_cl_device *cldev);
u8 mei_cldev_ver(स्थिर काष्ठा mei_cl_device *cldev);

व्योम *mei_cldev_get_drvdata(स्थिर काष्ठा mei_cl_device *cldev);
व्योम mei_cldev_set_drvdata(काष्ठा mei_cl_device *cldev, व्योम *data);

पूर्णांक mei_cldev_enable(काष्ठा mei_cl_device *cldev);
पूर्णांक mei_cldev_disable(काष्ठा mei_cl_device *cldev);
bool mei_cldev_enabled(काष्ठा mei_cl_device *cldev);

#पूर्ण_अगर /* _LINUX_MEI_CL_BUS_H */
