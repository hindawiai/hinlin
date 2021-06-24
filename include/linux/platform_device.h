<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * platक्रमm_device.h - generic, centralized driver model
 *
 * Copyright (c) 2001-2003 Patrick Mochel <mochel@osdl.org>
 *
 * See Documentation/driver-api/driver-model/ क्रम more inक्रमmation.
 */

#अगर_अघोषित _PLATFORM_DEVICE_H_
#घोषणा _PLATFORM_DEVICE_H_

#समावेश <linux/device.h>

#घोषणा PLATFORM_DEVID_NONE	(-1)
#घोषणा PLATFORM_DEVID_AUTO	(-2)

काष्ठा irq_affinity;
काष्ठा mfd_cell;
काष्ठा property_entry;
काष्ठा platक्रमm_device_id;

काष्ठा platक्रमm_device अणु
	स्थिर अक्षर	*name;
	पूर्णांक		id;
	bool		id_स्वतः;
	काष्ठा device	dev;
	u64		platक्रमm_dma_mask;
	काष्ठा device_dma_parameters dma_parms;
	u32		num_resources;
	काष्ठा resource	*resource;

	स्थिर काष्ठा platक्रमm_device_id	*id_entry;
	अक्षर *driver_override; /* Driver name to क्रमce a match */

	/* MFD cell poपूर्णांकer */
	काष्ठा mfd_cell *mfd_cell;

	/* arch specअगरic additions */
	काष्ठा pdev_archdata	archdata;
पूर्ण;

#घोषणा platक्रमm_get_device_id(pdev)	((pdev)->id_entry)

#घोषणा dev_is_platक्रमm(dev) ((dev)->bus == &platक्रमm_bus_type)
#घोषणा to_platक्रमm_device(x) container_of((x), काष्ठा platक्रमm_device, dev)

बाह्य पूर्णांक platक्रमm_device_रेजिस्टर(काष्ठा platक्रमm_device *);
बाह्य व्योम platक्रमm_device_unरेजिस्टर(काष्ठा platक्रमm_device *);

बाह्य काष्ठा bus_type platक्रमm_bus_type;
बाह्य काष्ठा device platक्रमm_bus;

बाह्य काष्ठा resource *platक्रमm_get_resource(काष्ठा platक्रमm_device *,
					      अचिन्हित पूर्णांक, अचिन्हित पूर्णांक);
बाह्य काष्ठा resource *platक्रमm_get_mem_or_io(काष्ठा platक्रमm_device *,
					       अचिन्हित पूर्णांक);

बाह्य काष्ठा device *
platक्रमm_find_device_by_driver(काष्ठा device *start,
			       स्थिर काष्ठा device_driver *drv);
बाह्य व्योम __iomem *
devm_platक्रमm_get_and_ioremap_resource(काष्ठा platक्रमm_device *pdev,
				अचिन्हित पूर्णांक index, काष्ठा resource **res);
बाह्य व्योम __iomem *
devm_platक्रमm_ioremap_resource(काष्ठा platक्रमm_device *pdev,
			       अचिन्हित पूर्णांक index);
बाह्य व्योम __iomem *
devm_platक्रमm_ioremap_resource_wc(काष्ठा platक्रमm_device *pdev,
				  अचिन्हित पूर्णांक index);
बाह्य व्योम __iomem *
devm_platक्रमm_ioremap_resource_byname(काष्ठा platक्रमm_device *pdev,
				      स्थिर अक्षर *name);
बाह्य पूर्णांक platक्रमm_get_irq(काष्ठा platक्रमm_device *, अचिन्हित पूर्णांक);
बाह्य पूर्णांक platक्रमm_get_irq_optional(काष्ठा platक्रमm_device *, अचिन्हित पूर्णांक);
बाह्य पूर्णांक platक्रमm_irq_count(काष्ठा platक्रमm_device *);
बाह्य पूर्णांक devm_platक्रमm_get_irqs_affinity(काष्ठा platक्रमm_device *dev,
					   काष्ठा irq_affinity *affd,
					   अचिन्हित पूर्णांक minvec,
					   अचिन्हित पूर्णांक maxvec,
					   पूर्णांक **irqs);
बाह्य काष्ठा resource *platक्रमm_get_resource_byname(काष्ठा platक्रमm_device *,
						     अचिन्हित पूर्णांक,
						     स्थिर अक्षर *);
बाह्य पूर्णांक platक्रमm_get_irq_byname(काष्ठा platक्रमm_device *, स्थिर अक्षर *);
बाह्य पूर्णांक platक्रमm_get_irq_byname_optional(काष्ठा platक्रमm_device *dev,
					    स्थिर अक्षर *name);
बाह्य पूर्णांक platक्रमm_add_devices(काष्ठा platक्रमm_device **, पूर्णांक);

काष्ठा platक्रमm_device_info अणु
		काष्ठा device *parent;
		काष्ठा fwnode_handle *fwnode;
		bool of_node_reused;

		स्थिर अक्षर *name;
		पूर्णांक id;

		स्थिर काष्ठा resource *res;
		अचिन्हित पूर्णांक num_res;

		स्थिर व्योम *data;
		माप_प्रकार size_data;
		u64 dma_mask;

		स्थिर काष्ठा property_entry *properties;
पूर्ण;
बाह्य काष्ठा platक्रमm_device *platक्रमm_device_रेजिस्टर_full(
		स्थिर काष्ठा platक्रमm_device_info *pdevinfo);

/**
 * platक्रमm_device_रेजिस्टर_resndata - add a platक्रमm-level device with
 * resources and platक्रमm-specअगरic data
 *
 * @parent: parent device क्रम the device we're adding
 * @name: base name of the device we're adding
 * @id: instance id
 * @res: set of resources that needs to be allocated क्रम the device
 * @num: number of resources
 * @data: platक्रमm specअगरic data क्रम this platक्रमm device
 * @size: size of platक्रमm specअगरic data
 *
 * Returns &काष्ठा platक्रमm_device poपूर्णांकer on success, or ERR_PTR() on error.
 */
अटल अंतरभूत काष्ठा platक्रमm_device *platक्रमm_device_रेजिस्टर_resndata(
		काष्ठा device *parent, स्थिर अक्षर *name, पूर्णांक id,
		स्थिर काष्ठा resource *res, अचिन्हित पूर्णांक num,
		स्थिर व्योम *data, माप_प्रकार size) अणु

	काष्ठा platक्रमm_device_info pdevinfo = अणु
		.parent = parent,
		.name = name,
		.id = id,
		.res = res,
		.num_res = num,
		.data = data,
		.size_data = size,
		.dma_mask = 0,
	पूर्ण;

	वापस platक्रमm_device_रेजिस्टर_full(&pdevinfo);
पूर्ण

/**
 * platक्रमm_device_रेजिस्टर_simple - add a platक्रमm-level device and its resources
 * @name: base name of the device we're adding
 * @id: instance id
 * @res: set of resources that needs to be allocated क्रम the device
 * @num: number of resources
 *
 * This function creates a simple platक्रमm device that requires minimal
 * resource and memory management. Canned release function मुक्तing memory
 * allocated क्रम the device allows drivers using such devices to be
 * unloaded without रुकोing क्रम the last reference to the device to be
 * dropped.
 *
 * This पूर्णांकerface is primarily पूर्णांकended क्रम use with legacy drivers which
 * probe hardware directly.  Because such drivers create sysfs device nodes
 * themselves, rather than letting प्रणाली infraकाष्ठाure handle such device
 * क्रमागतeration tasks, they करोn't fully conक्रमm to the Linux driver model.
 * In particular, when such drivers are built as modules, they can't be
 * "hotplugged".
 *
 * Returns &काष्ठा platक्रमm_device poपूर्णांकer on success, or ERR_PTR() on error.
 */
अटल अंतरभूत काष्ठा platक्रमm_device *platक्रमm_device_रेजिस्टर_simple(
		स्थिर अक्षर *name, पूर्णांक id,
		स्थिर काष्ठा resource *res, अचिन्हित पूर्णांक num)
अणु
	वापस platक्रमm_device_रेजिस्टर_resndata(शून्य, name, id,
			res, num, शून्य, 0);
पूर्ण

/**
 * platक्रमm_device_रेजिस्टर_data - add a platक्रमm-level device with platक्रमm-specअगरic data
 * @parent: parent device क्रम the device we're adding
 * @name: base name of the device we're adding
 * @id: instance id
 * @data: platक्रमm specअगरic data क्रम this platक्रमm device
 * @size: size of platक्रमm specअगरic data
 *
 * This function creates a simple platक्रमm device that requires minimal
 * resource and memory management. Canned release function मुक्तing memory
 * allocated क्रम the device allows drivers using such devices to be
 * unloaded without रुकोing क्रम the last reference to the device to be
 * dropped.
 *
 * Returns &काष्ठा platक्रमm_device poपूर्णांकer on success, or ERR_PTR() on error.
 */
अटल अंतरभूत काष्ठा platक्रमm_device *platक्रमm_device_रेजिस्टर_data(
		काष्ठा device *parent, स्थिर अक्षर *name, पूर्णांक id,
		स्थिर व्योम *data, माप_प्रकार size)
अणु
	वापस platक्रमm_device_रेजिस्टर_resndata(parent, name, id,
			शून्य, 0, data, size);
पूर्ण

बाह्य काष्ठा platक्रमm_device *platक्रमm_device_alloc(स्थिर अक्षर *name, पूर्णांक id);
बाह्य पूर्णांक platक्रमm_device_add_resources(काष्ठा platक्रमm_device *pdev,
					 स्थिर काष्ठा resource *res,
					 अचिन्हित पूर्णांक num);
बाह्य पूर्णांक platक्रमm_device_add_data(काष्ठा platक्रमm_device *pdev,
				    स्थिर व्योम *data, माप_प्रकार size);
बाह्य पूर्णांक platक्रमm_device_add_properties(काष्ठा platक्रमm_device *pdev,
				स्थिर काष्ठा property_entry *properties);
बाह्य पूर्णांक platक्रमm_device_add(काष्ठा platक्रमm_device *pdev);
बाह्य व्योम platक्रमm_device_del(काष्ठा platक्रमm_device *pdev);
बाह्य व्योम platक्रमm_device_put(काष्ठा platक्रमm_device *pdev);

काष्ठा platक्रमm_driver अणु
	पूर्णांक (*probe)(काष्ठा platक्रमm_device *);
	पूर्णांक (*हटाओ)(काष्ठा platक्रमm_device *);
	व्योम (*shutकरोwn)(काष्ठा platक्रमm_device *);
	पूर्णांक (*suspend)(काष्ठा platक्रमm_device *, pm_message_t state);
	पूर्णांक (*resume)(काष्ठा platक्रमm_device *);
	काष्ठा device_driver driver;
	स्थिर काष्ठा platक्रमm_device_id *id_table;
	bool prevent_deferred_probe;
पूर्ण;

#घोषणा to_platक्रमm_driver(drv)	(container_of((drv), काष्ठा platक्रमm_driver, \
				 driver))

/*
 * use a macro to aव्योम include chaining to get THIS_MODULE
 */
#घोषणा platक्रमm_driver_रेजिस्टर(drv) \
	__platक्रमm_driver_रेजिस्टर(drv, THIS_MODULE)
बाह्य पूर्णांक __platक्रमm_driver_रेजिस्टर(काष्ठा platक्रमm_driver *,
					काष्ठा module *);
बाह्य व्योम platक्रमm_driver_unरेजिस्टर(काष्ठा platक्रमm_driver *);

/* non-hotpluggable platक्रमm devices may use this so that probe() and
 * its support may live in __init sections, conserving runसमय memory.
 */
#घोषणा platक्रमm_driver_probe(drv, probe) \
	__platक्रमm_driver_probe(drv, probe, THIS_MODULE)
बाह्य पूर्णांक __platक्रमm_driver_probe(काष्ठा platक्रमm_driver *driver,
		पूर्णांक (*probe)(काष्ठा platक्रमm_device *), काष्ठा module *module);

अटल अंतरभूत व्योम *platक्रमm_get_drvdata(स्थिर काष्ठा platक्रमm_device *pdev)
अणु
	वापस dev_get_drvdata(&pdev->dev);
पूर्ण

अटल अंतरभूत व्योम platक्रमm_set_drvdata(काष्ठा platक्रमm_device *pdev,
					व्योम *data)
अणु
	dev_set_drvdata(&pdev->dev, data);
पूर्ण

/* module_platक्रमm_driver() - Helper macro क्रम drivers that करोn't करो
 * anything special in module init/निकास.  This eliminates a lot of
 * boilerplate.  Each module may only use this macro once, and
 * calling it replaces module_init() and module_निकास()
 */
#घोषणा module_platक्रमm_driver(__platक्रमm_driver) \
	module_driver(__platक्रमm_driver, platक्रमm_driver_रेजिस्टर, \
			platक्रमm_driver_unरेजिस्टर)

/* builtin_platक्रमm_driver() - Helper macro क्रम builtin drivers that
 * करोn't करो anything special in driver init.  This eliminates some
 * boilerplate.  Each driver may only use this macro once, and
 * calling it replaces device_initcall().  Note this is meant to be
 * a parallel of module_platक्रमm_driver() above, but w/o _निकास stuff.
 */
#घोषणा builtin_platक्रमm_driver(__platक्रमm_driver) \
	builtin_driver(__platक्रमm_driver, platक्रमm_driver_रेजिस्टर)

/* module_platक्रमm_driver_probe() - Helper macro क्रम drivers that करोn't करो
 * anything special in module init/निकास.  This eliminates a lot of
 * boilerplate.  Each module may only use this macro once, and
 * calling it replaces module_init() and module_निकास()
 */
#घोषणा module_platक्रमm_driver_probe(__platक्रमm_driver, __platक्रमm_probe) \
अटल पूर्णांक __init __platक्रमm_driver##_init(व्योम) \
अणु \
	वापस platक्रमm_driver_probe(&(__platक्रमm_driver), \
				     __platक्रमm_probe);    \
पूर्ण \
module_init(__platक्रमm_driver##_init); \
अटल व्योम __निकास __platक्रमm_driver##_निकास(व्योम) \
अणु \
	platक्रमm_driver_unरेजिस्टर(&(__platक्रमm_driver)); \
पूर्ण \
module_निकास(__platक्रमm_driver##_निकास);

/* builtin_platक्रमm_driver_probe() - Helper macro क्रम drivers that करोn't करो
 * anything special in device init.  This eliminates some boilerplate.  Each
 * driver may only use this macro once, and using it replaces device_initcall.
 * This is meant to be a parallel of module_platक्रमm_driver_probe above, but
 * without the __निकास parts.
 */
#घोषणा builtin_platक्रमm_driver_probe(__platक्रमm_driver, __platक्रमm_probe) \
अटल पूर्णांक __init __platक्रमm_driver##_init(व्योम) \
अणु \
	वापस platक्रमm_driver_probe(&(__platक्रमm_driver), \
				     __platक्रमm_probe);    \
पूर्ण \
device_initcall(__platक्रमm_driver##_init); \

#घोषणा platक्रमm_create_bundle(driver, probe, res, n_res, data, size) \
	__platक्रमm_create_bundle(driver, probe, res, n_res, data, size, THIS_MODULE)
बाह्य काष्ठा platक्रमm_device *__platक्रमm_create_bundle(
	काष्ठा platक्रमm_driver *driver, पूर्णांक (*probe)(काष्ठा platक्रमm_device *),
	काष्ठा resource *res, अचिन्हित पूर्णांक n_res,
	स्थिर व्योम *data, माप_प्रकार size, काष्ठा module *module);

पूर्णांक __platक्रमm_रेजिस्टर_drivers(काष्ठा platक्रमm_driver * स्थिर *drivers,
				अचिन्हित पूर्णांक count, काष्ठा module *owner);
व्योम platक्रमm_unरेजिस्टर_drivers(काष्ठा platक्रमm_driver * स्थिर *drivers,
				 अचिन्हित पूर्णांक count);

#घोषणा platक्रमm_रेजिस्टर_drivers(drivers, count) \
	__platक्रमm_रेजिस्टर_drivers(drivers, count, THIS_MODULE)

#अगर_घोषित CONFIG_SUSPEND
बाह्य पूर्णांक platक्रमm_pm_suspend(काष्ठा device *dev);
बाह्य पूर्णांक platक्रमm_pm_resume(काष्ठा device *dev);
#अन्यथा
#घोषणा platक्रमm_pm_suspend		शून्य
#घोषणा platक्रमm_pm_resume		शून्य
#पूर्ण_अगर

#अगर_घोषित CONFIG_HIBERNATE_CALLBACKS
बाह्य पूर्णांक platक्रमm_pm_मुक्तze(काष्ठा device *dev);
बाह्य पूर्णांक platक्रमm_pm_thaw(काष्ठा device *dev);
बाह्य पूर्णांक platक्रमm_pm_घातeroff(काष्ठा device *dev);
बाह्य पूर्णांक platक्रमm_pm_restore(काष्ठा device *dev);
#अन्यथा
#घोषणा platक्रमm_pm_मुक्तze		शून्य
#घोषणा platक्रमm_pm_thaw		शून्य
#घोषणा platक्रमm_pm_घातeroff		शून्य
#घोषणा platक्रमm_pm_restore		शून्य
#पूर्ण_अगर

बाह्य पूर्णांक platक्रमm_dma_configure(काष्ठा device *dev);

#अगर_घोषित CONFIG_PM_SLEEP
#घोषणा USE_PLATFORM_PM_SLEEP_OPS \
	.suspend = platक्रमm_pm_suspend, \
	.resume = platक्रमm_pm_resume, \
	.मुक्तze = platक्रमm_pm_मुक्तze, \
	.thaw = platक्रमm_pm_thaw, \
	.घातeroff = platक्रमm_pm_घातeroff, \
	.restore = platक्रमm_pm_restore,
#अन्यथा
#घोषणा USE_PLATFORM_PM_SLEEP_OPS
#पूर्ण_अगर

#अगर_अघोषित CONFIG_SUPERH
/*
 * REVISIT: This stub is needed क्रम all non-SuperH users of early platक्रमm
 * drivers. It should go away once we पूर्णांकroduce the new platक्रमm_device-based
 * early driver framework.
 */
अटल अंतरभूत पूर्णांक is_sh_early_platक्रमm_device(काष्ठा platक्रमm_device *pdev)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_SUPERH */

/* For now only SuperH uses it */
व्योम early_platक्रमm_cleanup(व्योम);

#पूर्ण_अगर /* _PLATFORM_DEVICE_H_ */
