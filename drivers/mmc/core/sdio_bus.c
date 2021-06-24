<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  linux/drivers/mmc/core/sdio_bus.c
 *
 *  Copyright 2007 Pierre Ossman
 *
 * SDIO function driver model
 */

#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/acpi.h>

#समावेश <linux/mmc/card.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/sdio_func.h>
#समावेश <linux/of.h>

#समावेश "core.h"
#समावेश "card.h"
#समावेश "sdio_cis.h"
#समावेश "sdio_bus.h"

#घोषणा to_sdio_driver(d)	container_of(d, काष्ठा sdio_driver, drv)

/* show configuration fields */
#घोषणा sdio_config_attr(field, क्रमmat_string, args...)			\
अटल sमाप_प्रकार								\
field##_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)				\
अणु									\
	काष्ठा sdio_func *func;						\
									\
	func = dev_to_sdio_func (dev);					\
	वापस प्र_लिखो(buf, क्रमmat_string, args);			\
पूर्ण									\
अटल DEVICE_ATTR_RO(field)

sdio_config_attr(class, "0x%02x\n", func->class);
sdio_config_attr(venकरोr, "0x%04x\n", func->venकरोr);
sdio_config_attr(device, "0x%04x\n", func->device);
sdio_config_attr(revision, "%u.%u\n", func->major_rev, func->minor_rev);
sdio_config_attr(modalias, "sdio:c%02Xv%04Xd%04X\n", func->class, func->venकरोr, func->device);

#घोषणा sdio_info_attr(num)									\
अटल sमाप_प्रकार info##num##_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)	\
अणु												\
	काष्ठा sdio_func *func = dev_to_sdio_func(dev);						\
												\
	अगर (num > func->num_info)								\
		वापस -ENODATA;								\
	अगर (!func->info[num-1][0])								\
		वापस 0;									\
	वापस प्र_लिखो(buf, "%s\n", func->info[num-1]);						\
पूर्ण												\
अटल DEVICE_ATTR_RO(info##num)

sdio_info_attr(1);
sdio_info_attr(2);
sdio_info_attr(3);
sdio_info_attr(4);

अटल काष्ठा attribute *sdio_dev_attrs[] = अणु
	&dev_attr_class.attr,
	&dev_attr_venकरोr.attr,
	&dev_attr_device.attr,
	&dev_attr_revision.attr,
	&dev_attr_info1.attr,
	&dev_attr_info2.attr,
	&dev_attr_info3.attr,
	&dev_attr_info4.attr,
	&dev_attr_modalias.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(sdio_dev);

अटल स्थिर काष्ठा sdio_device_id *sdio_match_one(काष्ठा sdio_func *func,
	स्थिर काष्ठा sdio_device_id *id)
अणु
	अगर (id->class != (__u8)SDIO_ANY_ID && id->class != func->class)
		वापस शून्य;
	अगर (id->venकरोr != (__u16)SDIO_ANY_ID && id->venकरोr != func->venकरोr)
		वापस शून्य;
	अगर (id->device != (__u16)SDIO_ANY_ID && id->device != func->device)
		वापस शून्य;
	वापस id;
पूर्ण

अटल स्थिर काष्ठा sdio_device_id *sdio_match_device(काष्ठा sdio_func *func,
	काष्ठा sdio_driver *sdrv)
अणु
	स्थिर काष्ठा sdio_device_id *ids;

	ids = sdrv->id_table;

	अगर (ids) अणु
		जबतक (ids->class || ids->venकरोr || ids->device) अणु
			अगर (sdio_match_one(func, ids))
				वापस ids;
			ids++;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक sdio_bus_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	काष्ठा sdio_func *func = dev_to_sdio_func(dev);
	काष्ठा sdio_driver *sdrv = to_sdio_driver(drv);

	अगर (sdio_match_device(func, sdrv))
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक
sdio_bus_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा sdio_func *func = dev_to_sdio_func(dev);
	अचिन्हित पूर्णांक i;

	अगर (add_uevent_var(env,
			"SDIO_CLASS=%02X", func->class))
		वापस -ENOMEM;

	अगर (add_uevent_var(env, 
			"SDIO_ID=%04X:%04X", func->venकरोr, func->device))
		वापस -ENOMEM;

	अगर (add_uevent_var(env,
			"SDIO_REVISION=%u.%u", func->major_rev, func->minor_rev))
		वापस -ENOMEM;

	क्रम (i = 0; i < func->num_info; i++) अणु
		अगर (add_uevent_var(env, "SDIO_INFO%u=%s", i+1, func->info[i]))
			वापस -ENOMEM;
	पूर्ण

	अगर (add_uevent_var(env,
			"MODALIAS=sdio:c%02Xv%04Xd%04X",
			func->class, func->venकरोr, func->device))
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल पूर्णांक sdio_bus_probe(काष्ठा device *dev)
अणु
	काष्ठा sdio_driver *drv = to_sdio_driver(dev->driver);
	काष्ठा sdio_func *func = dev_to_sdio_func(dev);
	स्थिर काष्ठा sdio_device_id *id;
	पूर्णांक ret;

	id = sdio_match_device(func, drv);
	अगर (!id)
		वापस -ENODEV;

	ret = dev_pm_करोमुख्य_attach(dev, false);
	अगर (ret)
		वापस ret;

	atomic_inc(&func->card->sdio_funcs_probed);

	/* Unbound SDIO functions are always suspended.
	 * During probe, the function is set active and the usage count
	 * is incremented.  If the driver supports runसमय PM,
	 * it should call pm_runसमय_put_noidle() in its probe routine and
	 * pm_runसमय_get_noresume() in its हटाओ routine.
	 */
	अगर (func->card->host->caps & MMC_CAP_POWER_OFF_CARD) अणु
		ret = pm_runसमय_get_sync(dev);
		अगर (ret < 0)
			जाओ disable_runसमयpm;
	पूर्ण

	/* Set the शेष block size so the driver is sure it's something
	 * sensible. */
	sdio_claim_host(func);
	अगर (mmc_card_हटाओd(func->card))
		ret = -ENOMEDIUM;
	अन्यथा
		ret = sdio_set_block_size(func, 0);
	sdio_release_host(func);
	अगर (ret)
		जाओ disable_runसमयpm;

	ret = drv->probe(func, id);
	अगर (ret)
		जाओ disable_runसमयpm;

	वापस 0;

disable_runसमयpm:
	atomic_dec(&func->card->sdio_funcs_probed);
	अगर (func->card->host->caps & MMC_CAP_POWER_OFF_CARD)
		pm_runसमय_put_noidle(dev);
	dev_pm_करोमुख्य_detach(dev, false);
	वापस ret;
पूर्ण

अटल पूर्णांक sdio_bus_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा sdio_driver *drv = to_sdio_driver(dev->driver);
	काष्ठा sdio_func *func = dev_to_sdio_func(dev);

	/* Make sure card is घातered beक्रमe invoking ->हटाओ() */
	अगर (func->card->host->caps & MMC_CAP_POWER_OFF_CARD)
		pm_runसमय_get_sync(dev);

	drv->हटाओ(func);
	atomic_dec(&func->card->sdio_funcs_probed);

	अगर (func->irq_handler) अणु
		pr_warn("WARNING: driver %s did not remove its interrupt handler!\n",
			drv->name);
		sdio_claim_host(func);
		sdio_release_irq(func);
		sdio_release_host(func);
	पूर्ण

	/* First, unकरो the increment made directly above */
	अगर (func->card->host->caps & MMC_CAP_POWER_OFF_CARD)
		pm_runसमय_put_noidle(dev);

	/* Then unकरो the runसमय PM settings in sdio_bus_probe() */
	अगर (func->card->host->caps & MMC_CAP_POWER_OFF_CARD)
		pm_runसमय_put_sync(dev);

	dev_pm_करोमुख्य_detach(dev, false);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops sdio_bus_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(pm_generic_suspend, pm_generic_resume)
	SET_RUNTIME_PM_OPS(
		pm_generic_runसमय_suspend,
		pm_generic_runसमय_resume,
		शून्य
	)
पूर्ण;

अटल काष्ठा bus_type sdio_bus_type = अणु
	.name		= "sdio",
	.dev_groups	= sdio_dev_groups,
	.match		= sdio_bus_match,
	.uevent		= sdio_bus_uevent,
	.probe		= sdio_bus_probe,
	.हटाओ		= sdio_bus_हटाओ,
	.pm		= &sdio_bus_pm_ops,
पूर्ण;

पूर्णांक sdio_रेजिस्टर_bus(व्योम)
अणु
	वापस bus_रेजिस्टर(&sdio_bus_type);
पूर्ण

व्योम sdio_unरेजिस्टर_bus(व्योम)
अणु
	bus_unरेजिस्टर(&sdio_bus_type);
पूर्ण

/**
 *	sdio_रेजिस्टर_driver - रेजिस्टर a function driver
 *	@drv: SDIO function driver
 */
पूर्णांक sdio_रेजिस्टर_driver(काष्ठा sdio_driver *drv)
अणु
	drv->drv.name = drv->name;
	drv->drv.bus = &sdio_bus_type;
	वापस driver_रेजिस्टर(&drv->drv);
पूर्ण
EXPORT_SYMBOL_GPL(sdio_रेजिस्टर_driver);

/**
 *	sdio_unरेजिस्टर_driver - unरेजिस्टर a function driver
 *	@drv: SDIO function driver
 */
व्योम sdio_unरेजिस्टर_driver(काष्ठा sdio_driver *drv)
अणु
	drv->drv.bus = &sdio_bus_type;
	driver_unरेजिस्टर(&drv->drv);
पूर्ण
EXPORT_SYMBOL_GPL(sdio_unरेजिस्टर_driver);

अटल व्योम sdio_release_func(काष्ठा device *dev)
अणु
	काष्ठा sdio_func *func = dev_to_sdio_func(dev);

	sdio_मुक्त_func_cis(func);

	kमुक्त(func->info);
	kमुक्त(func->पंचांगpbuf);
	kमुक्त(func);
पूर्ण

/*
 * Allocate and initialise a new SDIO function काष्ठाure.
 */
काष्ठा sdio_func *sdio_alloc_func(काष्ठा mmc_card *card)
अणु
	काष्ठा sdio_func *func;

	func = kzalloc(माप(काष्ठा sdio_func), GFP_KERNEL);
	अगर (!func)
		वापस ERR_PTR(-ENOMEM);

	/*
	 * allocate buffer separately to make sure it's properly aligned क्रम
	 * DMA usage (incl. 64 bit DMA)
	 */
	func->पंचांगpbuf = kदो_स्मृति(4, GFP_KERNEL);
	अगर (!func->पंचांगpbuf) अणु
		kमुक्त(func);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	func->card = card;

	device_initialize(&func->dev);

	func->dev.parent = &card->dev;
	func->dev.bus = &sdio_bus_type;
	func->dev.release = sdio_release_func;

	वापस func;
पूर्ण

#अगर_घोषित CONFIG_ACPI
अटल व्योम sdio_acpi_set_handle(काष्ठा sdio_func *func)
अणु
	काष्ठा mmc_host *host = func->card->host;
	u64 addr = ((u64)host->slotno << 16) | func->num;

	acpi_preset_companion(&func->dev, ACPI_COMPANION(host->parent), addr);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम sdio_acpi_set_handle(काष्ठा sdio_func *func) अणुपूर्ण
#पूर्ण_अगर

अटल व्योम sdio_set_of_node(काष्ठा sdio_func *func)
अणु
	काष्ठा mmc_host *host = func->card->host;

	func->dev.of_node = mmc_of_find_child_device(host, func->num);
पूर्ण

/*
 * Register a new SDIO function with the driver model.
 */
पूर्णांक sdio_add_func(काष्ठा sdio_func *func)
अणु
	पूर्णांक ret;

	dev_set_name(&func->dev, "%s:%d", mmc_card_id(func->card), func->num);

	sdio_set_of_node(func);
	sdio_acpi_set_handle(func);
	device_enable_async_suspend(&func->dev);
	ret = device_add(&func->dev);
	अगर (ret == 0)
		sdio_func_set_present(func);

	वापस ret;
पूर्ण

/*
 * Unरेजिस्टर a SDIO function with the driver model, and
 * (eventually) मुक्त it.
 * This function can be called through error paths where sdio_add_func() was
 * never executed (because a failure occurred at an earlier poपूर्णांक).
 */
व्योम sdio_हटाओ_func(काष्ठा sdio_func *func)
अणु
	अगर (!sdio_func_present(func))
		वापस;

	device_del(&func->dev);
	of_node_put(func->dev.of_node);
	put_device(&func->dev);
पूर्ण

