<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Greybus driver and device API
 *
 * Copyright 2014-2015 Google Inc.
 * Copyright 2014-2015 Linaro Ltd.
 */

#अगर_अघोषित __LINUX_GREYBUS_H
#घोषणा __LINUX_GREYBUS_H

#अगर_घोषित __KERNEL__

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/idr.h>

#समावेश <linux/greybus/greybus_id.h>
#समावेश <linux/greybus/greybus_manअगरest.h>
#समावेश <linux/greybus/greybus_protocols.h>
#समावेश <linux/greybus/manअगरest.h>
#समावेश <linux/greybus/hd.h>
#समावेश <linux/greybus/svc.h>
#समावेश <linux/greybus/control.h>
#समावेश <linux/greybus/module.h>
#समावेश <linux/greybus/पूर्णांकerface.h>
#समावेश <linux/greybus/bundle.h>
#समावेश <linux/greybus/connection.h>
#समावेश <linux/greybus/operation.h>

/* Matches up with the Greybus Protocol specअगरication करोcument */
#घोषणा GREYBUS_VERSION_MAJOR	0x00
#घोषणा GREYBUS_VERSION_MINOR	0x01

#घोषणा GREYBUS_ID_MATCH_DEVICE \
	(GREYBUS_ID_MATCH_VENDOR | GREYBUS_ID_MATCH_PRODUCT)

#घोषणा GREYBUS_DEVICE(v, p)					\
	.match_flags	= GREYBUS_ID_MATCH_DEVICE,		\
	.venकरोr		= (v),					\
	.product	= (p),

#घोषणा GREYBUS_DEVICE_CLASS(c)					\
	.match_flags	= GREYBUS_ID_MATCH_CLASS,		\
	.class		= (c),

/* Maximum number of CPorts */
#घोषणा CPORT_ID_MAX	4095		/* UniPro max id is 4095 */
#घोषणा CPORT_ID_BAD	U16_MAX

काष्ठा greybus_driver अणु
	स्थिर अक्षर *name;

	पूर्णांक (*probe)(काष्ठा gb_bundle *bundle,
		     स्थिर काष्ठा greybus_bundle_id *id);
	व्योम (*disconnect)(काष्ठा gb_bundle *bundle);

	स्थिर काष्ठा greybus_bundle_id *id_table;

	काष्ठा device_driver driver;
पूर्ण;
#घोषणा to_greybus_driver(d) container_of(d, काष्ठा greybus_driver, driver)

अटल अंतरभूत व्योम greybus_set_drvdata(काष्ठा gb_bundle *bundle, व्योम *data)
अणु
	dev_set_drvdata(&bundle->dev, data);
पूर्ण

अटल अंतरभूत व्योम *greybus_get_drvdata(काष्ठा gb_bundle *bundle)
अणु
	वापस dev_get_drvdata(&bundle->dev);
पूर्ण

/* Don't call these directly, use the module_greybus_driver() macro instead */
पूर्णांक greybus_रेजिस्टर_driver(काष्ठा greybus_driver *driver,
			    काष्ठा module *module, स्थिर अक्षर *mod_name);
व्योम greybus_deरेजिस्टर_driver(काष्ठा greybus_driver *driver);

/* define to get proper THIS_MODULE and KBUILD_MODNAME values */
#घोषणा greybus_रेजिस्टर(driver) \
	greybus_रेजिस्टर_driver(driver, THIS_MODULE, KBUILD_MODNAME)
#घोषणा greybus_deरेजिस्टर(driver) \
	greybus_deरेजिस्टर_driver(driver)

/**
 * module_greybus_driver() - Helper macro क्रम रेजिस्टरing a Greybus driver
 * @__greybus_driver: greybus_driver काष्ठाure
 *
 * Helper macro क्रम Greybus drivers to set up proper module init / निकास
 * functions.  Replaces module_init() and module_निकास() and keeps people from
 * prपूर्णांकing poपूर्णांकless things to the kernel log when their driver is loaded.
 */
#घोषणा module_greybus_driver(__greybus_driver)	\
	module_driver(__greybus_driver, greybus_रेजिस्टर, greybus_deरेजिस्टर)

पूर्णांक greybus_disabled(व्योम);

व्योम gb_debugfs_init(व्योम);
व्योम gb_debugfs_cleanup(व्योम);
काष्ठा dentry *gb_debugfs_get(व्योम);

बाह्य काष्ठा bus_type greybus_bus_type;

बाह्य काष्ठा device_type greybus_hd_type;
बाह्य काष्ठा device_type greybus_module_type;
बाह्य काष्ठा device_type greybus_पूर्णांकerface_type;
बाह्य काष्ठा device_type greybus_control_type;
बाह्य काष्ठा device_type greybus_bundle_type;
बाह्य काष्ठा device_type greybus_svc_type;

अटल अंतरभूत पूर्णांक is_gb_host_device(स्थिर काष्ठा device *dev)
अणु
	वापस dev->type == &greybus_hd_type;
पूर्ण

अटल अंतरभूत पूर्णांक is_gb_module(स्थिर काष्ठा device *dev)
अणु
	वापस dev->type == &greybus_module_type;
पूर्ण

अटल अंतरभूत पूर्णांक is_gb_पूर्णांकerface(स्थिर काष्ठा device *dev)
अणु
	वापस dev->type == &greybus_पूर्णांकerface_type;
पूर्ण

अटल अंतरभूत पूर्णांक is_gb_control(स्थिर काष्ठा device *dev)
अणु
	वापस dev->type == &greybus_control_type;
पूर्ण

अटल अंतरभूत पूर्णांक is_gb_bundle(स्थिर काष्ठा device *dev)
अणु
	वापस dev->type == &greybus_bundle_type;
पूर्ण

अटल अंतरभूत पूर्णांक is_gb_svc(स्थिर काष्ठा device *dev)
अणु
	वापस dev->type == &greybus_svc_type;
पूर्ण

अटल अंतरभूत bool cport_id_valid(काष्ठा gb_host_device *hd, u16 cport_id)
अणु
	वापस cport_id != CPORT_ID_BAD && cport_id < hd->num_cports;
पूर्ण

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* __LINUX_GREYBUS_H */
