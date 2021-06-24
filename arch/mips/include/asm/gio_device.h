<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <linux/device.h>
#समावेश <linux/mod_devicetable.h>

काष्ठा gio_device_id अणु
	__u8 id;
पूर्ण;

काष्ठा gio_device अणु
	काष्ठा device	dev;
	काष्ठा resource resource;
	अचिन्हित पूर्णांक	irq;
	अचिन्हित पूर्णांक	slotno;

	स्थिर अक्षर	*name;
	काष्ठा gio_device_id id;
	अचिन्हित	id32:1;
	अचिन्हित	gio64:1;
पूर्ण;
#घोषणा to_gio_device(d) container_of(d, काष्ठा gio_device, dev)

काष्ठा gio_driver अणु
	स्थिर अक्षर    *name;
	काष्ठा module *owner;
	स्थिर काष्ठा gio_device_id *id_table;

	पूर्णांक  (*probe)(काष्ठा gio_device *, स्थिर काष्ठा gio_device_id *);
	व्योम (*हटाओ)(काष्ठा gio_device *);
	व्योम (*shutकरोwn)(काष्ठा gio_device *);

	काष्ठा device_driver driver;
पूर्ण;
#घोषणा to_gio_driver(drv) container_of(drv, काष्ठा gio_driver, driver)

बाह्य काष्ठा gio_device *gio_dev_get(काष्ठा gio_device *);
बाह्य व्योम gio_dev_put(काष्ठा gio_device *);

बाह्य पूर्णांक gio_device_रेजिस्टर(काष्ठा gio_device *);
बाह्य व्योम gio_device_unरेजिस्टर(काष्ठा gio_device *);
बाह्य व्योम gio_release_dev(काष्ठा device *);

अटल अंतरभूत व्योम gio_device_मुक्त(काष्ठा gio_device *dev)
अणु
	gio_release_dev(&dev->dev);
पूर्ण

बाह्य पूर्णांक gio_रेजिस्टर_driver(काष्ठा gio_driver *);
बाह्य व्योम gio_unरेजिस्टर_driver(काष्ठा gio_driver *);

#घोषणा gio_get_drvdata(_dev)	     dev_get_drvdata(&(_dev)->dev)
#घोषणा gio_set_drvdata(_dev, data)  dev_set_drvdata(&(_dev)->dev, (data))

बाह्य व्योम gio_set_master(काष्ठा gio_device *);
