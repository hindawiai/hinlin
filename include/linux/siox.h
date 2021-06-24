<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2015 Pengutronix, Uwe Kleine-Kथघnig <kernel@pengutronix.de>
 */

#समावेश <linux/device.h>

#घोषणा to_siox_device(_dev)	container_of((_dev), काष्ठा siox_device, dev)
काष्ठा siox_device अणु
	काष्ठा list_head node; /* node in smaster->devices */
	काष्ठा siox_master *smaster;
	काष्ठा device dev;

	स्थिर अक्षर *type;
	माप_प्रकार inbytes;
	माप_प्रकार outbytes;
	u8 statustype;

	u8 status_पढ़ो_clean;
	u8 status_written;
	u8 status_written_lastcycle;
	bool connected;

	/* statistics */
	अचिन्हित पूर्णांक watchकरोg_errors;
	अचिन्हित पूर्णांक status_errors;

	काष्ठा kernfs_node *status_errors_kn;
	काष्ठा kernfs_node *watchकरोg_kn;
	काष्ठा kernfs_node *watchकरोg_errors_kn;
	काष्ठा kernfs_node *connected_kn;
पूर्ण;

bool siox_device_synced(काष्ठा siox_device *sdevice);
bool siox_device_connected(काष्ठा siox_device *sdevice);

काष्ठा siox_driver अणु
	पूर्णांक (*probe)(काष्ठा siox_device *sdevice);
	व्योम (*हटाओ)(काष्ठा siox_device *sdevice);
	व्योम (*shutकरोwn)(काष्ठा siox_device *sdevice);

	/*
	 * buf is big enough to hold sdev->inbytes - 1 bytes, the status byte
	 * is in the scope of the framework.
	 */
	पूर्णांक (*set_data)(काष्ठा siox_device *sdevice, u8 status, u8 buf[]);
	/*
	 * buf is big enough to hold sdev->outbytes - 1 bytes, the status byte
	 * is in the scope of the framework
	 */
	पूर्णांक (*get_data)(काष्ठा siox_device *sdevice, स्थिर u8 buf[]);

	काष्ठा device_driver driver;
पूर्ण;

अटल अंतरभूत काष्ठा siox_driver *to_siox_driver(काष्ठा device_driver *driver)
अणु
	अगर (driver)
		वापस container_of(driver, काष्ठा siox_driver, driver);
	अन्यथा
		वापस शून्य;
पूर्ण

पूर्णांक __siox_driver_रेजिस्टर(काष्ठा siox_driver *sdriver, काष्ठा module *owner);

अटल अंतरभूत पूर्णांक siox_driver_रेजिस्टर(काष्ठा siox_driver *sdriver)
अणु
	वापस __siox_driver_रेजिस्टर(sdriver, THIS_MODULE);
पूर्ण

अटल अंतरभूत व्योम siox_driver_unरेजिस्टर(काष्ठा siox_driver *sdriver)
अणु
	वापस driver_unरेजिस्टर(&sdriver->driver);
पूर्ण

/*
 * module_siox_driver() - Helper macro क्रम drivers that करोn't करो
 * anything special in module init/निकास.  This eliminates a lot of
 * boilerplate.  Each module may only use this macro once, and
 * calling it replaces module_init() and module_निकास()
 */
#घोषणा module_siox_driver(__siox_driver) \
	module_driver(__siox_driver, siox_driver_रेजिस्टर, \
			siox_driver_unरेजिस्टर)
