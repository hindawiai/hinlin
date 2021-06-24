<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/common/amba.c
 *
 *  Copyright (C) 2003 Deep Blue Solutions Ltd, All Rights Reserved.
 */
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/pm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/amba/bus.h>
#समावेश <linux/sizes.h>
#समावेश <linux/सीमा.स>
#समावेश <linux/clk/clk-conf.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset.h>

#समावेश <यंत्र/irq.h>

#घोषणा to_amba_driver(d)	container_of(d, काष्ठा amba_driver, drv)

/* called on periphid match and class 0x9 coresight device. */
अटल पूर्णांक
amba_cs_uci_id_match(स्थिर काष्ठा amba_id *table, काष्ठा amba_device *dev)
अणु
	पूर्णांक ret = 0;
	काष्ठा amba_cs_uci_id *uci;

	uci = table->data;

	/* no table data or zero mask - वापस match on periphid */
	अगर (!uci || (uci->devarch_mask == 0))
		वापस 1;

	/* test against पढ़ो devtype and masked devarch value */
	ret = (dev->uci.devtype == uci->devtype) &&
		((dev->uci.devarch & uci->devarch_mask) == uci->devarch);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा amba_id *
amba_lookup(स्थिर काष्ठा amba_id *table, काष्ठा amba_device *dev)
अणु
	जबतक (table->mask) अणु
		अगर (((dev->periphid & table->mask) == table->id) &&
			((dev->cid != CORESIGHT_CID) ||
			 (amba_cs_uci_id_match(table, dev))))
			वापस table;
		table++;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक amba_get_enable_pclk(काष्ठा amba_device *pcdev)
अणु
	पूर्णांक ret;

	pcdev->pclk = clk_get(&pcdev->dev, "apb_pclk");
	अगर (IS_ERR(pcdev->pclk))
		वापस PTR_ERR(pcdev->pclk);

	ret = clk_prepare_enable(pcdev->pclk);
	अगर (ret)
		clk_put(pcdev->pclk);

	वापस ret;
पूर्ण

अटल व्योम amba_put_disable_pclk(काष्ठा amba_device *pcdev)
अणु
	clk_disable_unprepare(pcdev->pclk);
	clk_put(pcdev->pclk);
पूर्ण


अटल sमाप_प्रकार driver_override_show(काष्ठा device *_dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा amba_device *dev = to_amba_device(_dev);
	sमाप_प्रकार len;

	device_lock(_dev);
	len = प्र_लिखो(buf, "%s\n", dev->driver_override);
	device_unlock(_dev);
	वापस len;
पूर्ण

अटल sमाप_प्रकार driver_override_store(काष्ठा device *_dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा amba_device *dev = to_amba_device(_dev);
	अक्षर *driver_override, *old, *cp;

	/* We need to keep extra room क्रम a newline */
	अगर (count >= (PAGE_SIZE - 1))
		वापस -EINVAL;

	driver_override = kstrndup(buf, count, GFP_KERNEL);
	अगर (!driver_override)
		वापस -ENOMEM;

	cp = म_अक्षर(driver_override, '\n');
	अगर (cp)
		*cp = '\0';

	device_lock(_dev);
	old = dev->driver_override;
	अगर (म_माप(driver_override)) अणु
		dev->driver_override = driver_override;
	पूर्ण अन्यथा अणु
		kमुक्त(driver_override);
		dev->driver_override = शून्य;
	पूर्ण
	device_unlock(_dev);

	kमुक्त(old);

	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(driver_override);

#घोषणा amba_attr_func(name,fmt,arg...)					\
अटल sमाप_प्रकार name##_show(काष्ठा device *_dev,				\
			   काष्ठा device_attribute *attr, अक्षर *buf)	\
अणु									\
	काष्ठा amba_device *dev = to_amba_device(_dev);			\
	वापस प्र_लिखो(buf, fmt, arg);					\
पूर्ण									\
अटल DEVICE_ATTR_RO(name)

amba_attr_func(id, "%08x\n", dev->periphid);
amba_attr_func(irq0, "%u\n", dev->irq[0]);
amba_attr_func(irq1, "%u\n", dev->irq[1]);
amba_attr_func(resource, "\t%016llx\t%016llx\t%016lx\n",
	 (अचिन्हित दीर्घ दीर्घ)dev->res.start, (अचिन्हित दीर्घ दीर्घ)dev->res.end,
	 dev->res.flags);

अटल काष्ठा attribute *amba_dev_attrs[] = अणु
	&dev_attr_id.attr,
	&dev_attr_resource.attr,
	&dev_attr_driver_override.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(amba_dev);

अटल पूर्णांक amba_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	काष्ठा amba_device *pcdev = to_amba_device(dev);
	काष्ठा amba_driver *pcdrv = to_amba_driver(drv);

	/* When driver_override is set, only bind to the matching driver */
	अगर (pcdev->driver_override)
		वापस !म_भेद(pcdev->driver_override, drv->name);

	वापस amba_lookup(pcdrv->id_table, pcdev) != शून्य;
पूर्ण

अटल पूर्णांक amba_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा amba_device *pcdev = to_amba_device(dev);
	पूर्णांक retval = 0;

	retval = add_uevent_var(env, "AMBA_ID=%08x", pcdev->periphid);
	अगर (retval)
		वापस retval;

	retval = add_uevent_var(env, "MODALIAS=amba:d%08X", pcdev->periphid);
	वापस retval;
पूर्ण

/*
 * These are the device model conversion veneers; they convert the
 * device model काष्ठाures to our more specअगरic काष्ठाures.
 */
अटल पूर्णांक amba_probe(काष्ठा device *dev)
अणु
	काष्ठा amba_device *pcdev = to_amba_device(dev);
	काष्ठा amba_driver *pcdrv = to_amba_driver(dev->driver);
	स्थिर काष्ठा amba_id *id = amba_lookup(pcdrv->id_table, pcdev);
	पूर्णांक ret;

	करो अणु
		ret = of_clk_set_शेषs(dev->of_node, false);
		अगर (ret < 0)
			अवरोध;

		ret = dev_pm_करोमुख्य_attach(dev, true);
		अगर (ret)
			अवरोध;

		ret = amba_get_enable_pclk(pcdev);
		अगर (ret) अणु
			dev_pm_करोमुख्य_detach(dev, true);
			अवरोध;
		पूर्ण

		pm_runसमय_get_noresume(dev);
		pm_runसमय_set_active(dev);
		pm_runसमय_enable(dev);

		ret = pcdrv->probe(pcdev, id);
		अगर (ret == 0)
			अवरोध;

		pm_runसमय_disable(dev);
		pm_runसमय_set_suspended(dev);
		pm_runसमय_put_noidle(dev);

		amba_put_disable_pclk(pcdev);
		dev_pm_करोमुख्य_detach(dev, true);
	पूर्ण जबतक (0);

	वापस ret;
पूर्ण

अटल पूर्णांक amba_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा amba_device *pcdev = to_amba_device(dev);
	काष्ठा amba_driver *drv = to_amba_driver(dev->driver);

	pm_runसमय_get_sync(dev);
	अगर (drv->हटाओ)
		drv->हटाओ(pcdev);
	pm_runसमय_put_noidle(dev);

	/* Unकरो the runसमय PM settings in amba_probe() */
	pm_runसमय_disable(dev);
	pm_runसमय_set_suspended(dev);
	pm_runसमय_put_noidle(dev);

	amba_put_disable_pclk(pcdev);
	dev_pm_करोमुख्य_detach(dev, true);

	वापस 0;
पूर्ण

अटल व्योम amba_shutकरोwn(काष्ठा device *dev)
अणु
	काष्ठा amba_driver *drv;

	अगर (!dev->driver)
		वापस;

	drv = to_amba_driver(dev->driver);
	अगर (drv->shutकरोwn)
		drv->shutकरोwn(to_amba_device(dev));
पूर्ण

#अगर_घोषित CONFIG_PM
/*
 * Hooks to provide runसमय PM of the pclk (bus घड़ी).  It is safe to
 * enable/disable the bus घड़ी at runसमय PM suspend/resume as this
 * करोes not result in loss of context.
 */
अटल पूर्णांक amba_pm_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा amba_device *pcdev = to_amba_device(dev);
	पूर्णांक ret = pm_generic_runसमय_suspend(dev);

	अगर (ret == 0 && dev->driver) अणु
		अगर (pm_runसमय_is_irq_safe(dev))
			clk_disable(pcdev->pclk);
		अन्यथा
			clk_disable_unprepare(pcdev->pclk);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक amba_pm_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा amba_device *pcdev = to_amba_device(dev);
	पूर्णांक ret;

	अगर (dev->driver) अणु
		अगर (pm_runसमय_is_irq_safe(dev))
			ret = clk_enable(pcdev->pclk);
		अन्यथा
			ret = clk_prepare_enable(pcdev->pclk);
		/* Failure is probably fatal to the प्रणाली, but... */
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस pm_generic_runसमय_resume(dev);
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

अटल स्थिर काष्ठा dev_pm_ops amba_pm = अणु
	.suspend	= pm_generic_suspend,
	.resume		= pm_generic_resume,
	.मुक्तze		= pm_generic_मुक्तze,
	.thaw		= pm_generic_thaw,
	.घातeroff	= pm_generic_घातeroff,
	.restore	= pm_generic_restore,
	SET_RUNTIME_PM_OPS(
		amba_pm_runसमय_suspend,
		amba_pm_runसमय_resume,
		शून्य
	)
पूर्ण;

/*
 * Primecells are part of the Advanced Microcontroller Bus Architecture,
 * so we call the bus "amba".
 * DMA configuration क्रम platक्रमm and AMBA bus is same. So here we reuse
 * platक्रमm's DMA config routine.
 */
काष्ठा bus_type amba_bustype = अणु
	.name		= "amba",
	.dev_groups	= amba_dev_groups,
	.match		= amba_match,
	.uevent		= amba_uevent,
	.probe		= amba_probe,
	.हटाओ		= amba_हटाओ,
	.shutकरोwn	= amba_shutकरोwn,
	.dma_configure	= platक्रमm_dma_configure,
	.pm		= &amba_pm,
पूर्ण;
EXPORT_SYMBOL_GPL(amba_bustype);

अटल पूर्णांक __init amba_init(व्योम)
अणु
	वापस bus_रेजिस्टर(&amba_bustype);
पूर्ण

postcore_initcall(amba_init);

/**
 *	amba_driver_रेजिस्टर - रेजिस्टर an AMBA device driver
 *	@drv: amba device driver काष्ठाure
 *
 *	Register an AMBA device driver with the Linux device model
 *	core.  If devices pre-exist, the drivers probe function will
 *	be called.
 */
पूर्णांक amba_driver_रेजिस्टर(काष्ठा amba_driver *drv)
अणु
	अगर (!drv->probe)
		वापस -EINVAL;

	drv->drv.bus = &amba_bustype;

	वापस driver_रेजिस्टर(&drv->drv);
पूर्ण

/**
 *	amba_driver_unरेजिस्टर - हटाओ an AMBA device driver
 *	@drv: AMBA device driver काष्ठाure to हटाओ
 *
 *	Unरेजिस्टर an AMBA device driver from the Linux device
 *	model.  The device model will call the drivers हटाओ function
 *	क्रम each device the device driver is currently handling.
 */
व्योम amba_driver_unरेजिस्टर(काष्ठा amba_driver *drv)
अणु
	driver_unरेजिस्टर(&drv->drv);
पूर्ण


अटल व्योम amba_device_release(काष्ठा device *dev)
अणु
	काष्ठा amba_device *d = to_amba_device(dev);

	अगर (d->res.parent)
		release_resource(&d->res);
	kमुक्त(d);
पूर्ण

अटल पूर्णांक amba_device_try_add(काष्ठा amba_device *dev, काष्ठा resource *parent)
अणु
	u32 size;
	व्योम __iomem *पंचांगp;
	पूर्णांक i, ret;

	WARN_ON(dev->irq[0] == (अचिन्हित पूर्णांक)-1);
	WARN_ON(dev->irq[1] == (अचिन्हित पूर्णांक)-1);

	ret = request_resource(parent, &dev->res);
	अगर (ret)
		जाओ err_out;

	/* Hard-coded primecell ID instead of plug-n-play */
	अगर (dev->periphid != 0)
		जाओ skip_probe;

	/*
	 * Dynamically calculate the size of the resource
	 * and use this क्रम iomap
	 */
	size = resource_size(&dev->res);
	पंचांगp = ioremap(dev->res.start, size);
	अगर (!पंचांगp) अणु
		ret = -ENOMEM;
		जाओ err_release;
	पूर्ण

	ret = dev_pm_करोमुख्य_attach(&dev->dev, true);
	अगर (ret) अणु
		iounmap(पंचांगp);
		जाओ err_release;
	पूर्ण

	ret = amba_get_enable_pclk(dev);
	अगर (ret == 0) अणु
		u32 pid, cid;
		काष्ठा reset_control *rstc;

		/*
		 * Find reset control(s) of the amba bus and de-निश्चित them.
		 */
		rstc = of_reset_control_array_get_optional_shared(dev->dev.of_node);
		अगर (IS_ERR(rstc)) अणु
			ret = PTR_ERR(rstc);
			अगर (ret != -EPROBE_DEFER)
				dev_err(&dev->dev, "can't get reset: %d\n",
					ret);
			जाओ err_reset;
		पूर्ण
		reset_control_deनिश्चित(rstc);
		reset_control_put(rstc);

		/*
		 * Read pid and cid based on size of resource
		 * they are located at end of region
		 */
		क्रम (pid = 0, i = 0; i < 4; i++)
			pid |= (पढ़ोl(पंचांगp + size - 0x20 + 4 * i) & 255) <<
				(i * 8);
		क्रम (cid = 0, i = 0; i < 4; i++)
			cid |= (पढ़ोl(पंचांगp + size - 0x10 + 4 * i) & 255) <<
				(i * 8);

		अगर (cid == CORESIGHT_CID) अणु
			/* set the base to the start of the last 4k block */
			व्योम __iomem *csbase = पंचांगp + size - 4096;

			dev->uci.devarch =
				पढ़ोl(csbase + UCI_REG_DEVARCH_OFFSET);
			dev->uci.devtype =
				पढ़ोl(csbase + UCI_REG_DEVTYPE_OFFSET) & 0xff;
		पूर्ण

		amba_put_disable_pclk(dev);

		अगर (cid == AMBA_CID || cid == CORESIGHT_CID) अणु
			dev->periphid = pid;
			dev->cid = cid;
		पूर्ण

		अगर (!dev->periphid)
			ret = -ENODEV;
	पूर्ण

	iounmap(पंचांगp);
	dev_pm_करोमुख्य_detach(&dev->dev, true);

	अगर (ret)
		जाओ err_release;

 skip_probe:
	ret = device_add(&dev->dev);
	अगर (ret)
		जाओ err_release;

	अगर (dev->irq[0])
		ret = device_create_file(&dev->dev, &dev_attr_irq0);
	अगर (ret == 0 && dev->irq[1])
		ret = device_create_file(&dev->dev, &dev_attr_irq1);
	अगर (ret == 0)
		वापस ret;

	device_unरेजिस्टर(&dev->dev);

 err_release:
	release_resource(&dev->res);
 err_out:
	वापस ret;

 err_reset:
	amba_put_disable_pclk(dev);
	iounmap(पंचांगp);
	dev_pm_करोमुख्य_detach(&dev->dev, true);
	जाओ err_release;
पूर्ण

/*
 * Registration of AMBA device require पढ़ोing its pid and cid रेजिस्टरs.
 * To करो this, the device must be turned on (अगर it is a part of घातer करोमुख्य)
 * and have घड़ीs enabled. However in some हालs those resources might not be
 * yet available. Returning EPROBE_DEFER is not a solution in such हाल,
 * because callers करोn't handle this special error code. Instead such devices
 * are added to the special list and their registration is retried from
 * periodic worker, until all resources are available and registration succeeds.
 */
काष्ठा deferred_device अणु
	काष्ठा amba_device *dev;
	काष्ठा resource *parent;
	काष्ठा list_head node;
पूर्ण;

अटल LIST_HEAD(deferred_devices);
अटल DEFINE_MUTEX(deferred_devices_lock);

अटल व्योम amba_deferred_retry_func(काष्ठा work_काष्ठा *dummy);
अटल DECLARE_DELAYED_WORK(deferred_retry_work, amba_deferred_retry_func);

#घोषणा DEFERRED_DEVICE_TIMEOUT (msecs_to_jअगरfies(5 * 1000))

अटल पूर्णांक amba_deferred_retry(व्योम)
अणु
	काष्ठा deferred_device *ddev, *पंचांगp;

	mutex_lock(&deferred_devices_lock);

	list_क्रम_each_entry_safe(ddev, पंचांगp, &deferred_devices, node) अणु
		पूर्णांक ret = amba_device_try_add(ddev->dev, ddev->parent);

		अगर (ret == -EPROBE_DEFER)
			जारी;

		list_del_init(&ddev->node);
		kमुक्त(ddev);
	पूर्ण

	mutex_unlock(&deferred_devices_lock);

	वापस 0;
पूर्ण
late_initcall(amba_deferred_retry);

अटल व्योम amba_deferred_retry_func(काष्ठा work_काष्ठा *dummy)
अणु
	amba_deferred_retry();

	अगर (!list_empty(&deferred_devices))
		schedule_delayed_work(&deferred_retry_work,
				      DEFERRED_DEVICE_TIMEOUT);
पूर्ण

/**
 *	amba_device_add - add a previously allocated AMBA device काष्ठाure
 *	@dev: AMBA device allocated by amba_device_alloc
 *	@parent: resource parent क्रम this devices resources
 *
 *	Claim the resource, and पढ़ो the device cell ID अगर not alपढ़ोy
 *	initialized.  Register the AMBA device with the Linux device
 *	manager.
 */
पूर्णांक amba_device_add(काष्ठा amba_device *dev, काष्ठा resource *parent)
अणु
	पूर्णांक ret = amba_device_try_add(dev, parent);

	अगर (ret == -EPROBE_DEFER) अणु
		काष्ठा deferred_device *ddev;

		ddev = kदो_स्मृति(माप(*ddev), GFP_KERNEL);
		अगर (!ddev)
			वापस -ENOMEM;

		ddev->dev = dev;
		ddev->parent = parent;
		ret = 0;

		mutex_lock(&deferred_devices_lock);

		अगर (list_empty(&deferred_devices))
			schedule_delayed_work(&deferred_retry_work,
					      DEFERRED_DEVICE_TIMEOUT);
		list_add_tail(&ddev->node, &deferred_devices);

		mutex_unlock(&deferred_devices_lock);
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(amba_device_add);

अटल काष्ठा amba_device *
amba_aphb_device_add(काष्ठा device *parent, स्थिर अक्षर *name,
		     resource_माप_प्रकार base, माप_प्रकार size, पूर्णांक irq1, पूर्णांक irq2,
		     व्योम *pdata, अचिन्हित पूर्णांक periphid, u64 dma_mask,
		     काष्ठा resource *resbase)
अणु
	काष्ठा amba_device *dev;
	पूर्णांक ret;

	dev = amba_device_alloc(name, base, size);
	अगर (!dev)
		वापस ERR_PTR(-ENOMEM);

	dev->dev.coherent_dma_mask = dma_mask;
	dev->irq[0] = irq1;
	dev->irq[1] = irq2;
	dev->periphid = periphid;
	dev->dev.platक्रमm_data = pdata;
	dev->dev.parent = parent;

	ret = amba_device_add(dev, resbase);
	अगर (ret) अणु
		amba_device_put(dev);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस dev;
पूर्ण

काष्ठा amba_device *
amba_apb_device_add(काष्ठा device *parent, स्थिर अक्षर *name,
		    resource_माप_प्रकार base, माप_प्रकार size, पूर्णांक irq1, पूर्णांक irq2,
		    व्योम *pdata, अचिन्हित पूर्णांक periphid)
अणु
	वापस amba_aphb_device_add(parent, name, base, size, irq1, irq2, pdata,
				    periphid, 0, &iomem_resource);
पूर्ण
EXPORT_SYMBOL_GPL(amba_apb_device_add);

काष्ठा amba_device *
amba_ahb_device_add(काष्ठा device *parent, स्थिर अक्षर *name,
		    resource_माप_प्रकार base, माप_प्रकार size, पूर्णांक irq1, पूर्णांक irq2,
		    व्योम *pdata, अचिन्हित पूर्णांक periphid)
अणु
	वापस amba_aphb_device_add(parent, name, base, size, irq1, irq2, pdata,
				    periphid, ~0ULL, &iomem_resource);
पूर्ण
EXPORT_SYMBOL_GPL(amba_ahb_device_add);

काष्ठा amba_device *
amba_apb_device_add_res(काष्ठा device *parent, स्थिर अक्षर *name,
			resource_माप_प्रकार base, माप_प्रकार size, पूर्णांक irq1,
			पूर्णांक irq2, व्योम *pdata, अचिन्हित पूर्णांक periphid,
			काष्ठा resource *resbase)
अणु
	वापस amba_aphb_device_add(parent, name, base, size, irq1, irq2, pdata,
				    periphid, 0, resbase);
पूर्ण
EXPORT_SYMBOL_GPL(amba_apb_device_add_res);

काष्ठा amba_device *
amba_ahb_device_add_res(काष्ठा device *parent, स्थिर अक्षर *name,
			resource_माप_प्रकार base, माप_प्रकार size, पूर्णांक irq1,
			पूर्णांक irq2, व्योम *pdata, अचिन्हित पूर्णांक periphid,
			काष्ठा resource *resbase)
अणु
	वापस amba_aphb_device_add(parent, name, base, size, irq1, irq2, pdata,
				    periphid, ~0ULL, resbase);
पूर्ण
EXPORT_SYMBOL_GPL(amba_ahb_device_add_res);


अटल व्योम amba_device_initialize(काष्ठा amba_device *dev, स्थिर अक्षर *name)
अणु
	device_initialize(&dev->dev);
	अगर (name)
		dev_set_name(&dev->dev, "%s", name);
	dev->dev.release = amba_device_release;
	dev->dev.bus = &amba_bustype;
	dev->dev.dma_mask = &dev->dev.coherent_dma_mask;
	dev->dev.dma_parms = &dev->dma_parms;
	dev->res.name = dev_name(&dev->dev);
पूर्ण

/**
 *	amba_device_alloc - allocate an AMBA device
 *	@name: sysfs name of the AMBA device
 *	@base: base of AMBA device
 *	@size: size of AMBA device
 *
 *	Allocate and initialize an AMBA device काष्ठाure.  Returns %शून्य
 *	on failure.
 */
काष्ठा amba_device *amba_device_alloc(स्थिर अक्षर *name, resource_माप_प्रकार base,
	माप_प्रकार size)
अणु
	काष्ठा amba_device *dev;

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (dev) अणु
		amba_device_initialize(dev, name);
		dev->res.start = base;
		dev->res.end = base + size - 1;
		dev->res.flags = IORESOURCE_MEM;
	पूर्ण

	वापस dev;
पूर्ण
EXPORT_SYMBOL_GPL(amba_device_alloc);

/**
 *	amba_device_रेजिस्टर - रेजिस्टर an AMBA device
 *	@dev: AMBA device to रेजिस्टर
 *	@parent: parent memory resource
 *
 *	Setup the AMBA device, पढ़ोing the cell ID अगर present.
 *	Claim the resource, and रेजिस्टर the AMBA device with
 *	the Linux device manager.
 */
पूर्णांक amba_device_रेजिस्टर(काष्ठा amba_device *dev, काष्ठा resource *parent)
अणु
	amba_device_initialize(dev, dev->dev.init_name);
	dev->dev.init_name = शून्य;

	वापस amba_device_add(dev, parent);
पूर्ण

/**
 *	amba_device_put - put an AMBA device
 *	@dev: AMBA device to put
 */
व्योम amba_device_put(काष्ठा amba_device *dev)
अणु
	put_device(&dev->dev);
पूर्ण
EXPORT_SYMBOL_GPL(amba_device_put);

/**
 *	amba_device_unरेजिस्टर - unरेजिस्टर an AMBA device
 *	@dev: AMBA device to हटाओ
 *
 *	Remove the specअगरied AMBA device from the Linux device
 *	manager.  All files associated with this object will be
 *	destroyed, and device drivers notअगरied that the device has
 *	been हटाओd.  The AMBA device's resources including
 *	the amba_device काष्ठाure will be मुक्तd once all
 *	references to it have been dropped.
 */
व्योम amba_device_unरेजिस्टर(काष्ठा amba_device *dev)
अणु
	device_unरेजिस्टर(&dev->dev);
पूर्ण


काष्ठा find_data अणु
	काष्ठा amba_device *dev;
	काष्ठा device *parent;
	स्थिर अक्षर *busid;
	अचिन्हित पूर्णांक id;
	अचिन्हित पूर्णांक mask;
पूर्ण;

अटल पूर्णांक amba_find_match(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा find_data *d = data;
	काष्ठा amba_device *pcdev = to_amba_device(dev);
	पूर्णांक r;

	r = (pcdev->periphid & d->mask) == d->id;
	अगर (d->parent)
		r &= d->parent == dev->parent;
	अगर (d->busid)
		r &= म_भेद(dev_name(dev), d->busid) == 0;

	अगर (r) अणु
		get_device(dev);
		d->dev = pcdev;
	पूर्ण

	वापस r;
पूर्ण

/**
 *	amba_find_device - locate an AMBA device given a bus id
 *	@busid: bus id क्रम device (or शून्य)
 *	@parent: parent device (or शून्य)
 *	@id: peripheral ID (or 0)
 *	@mask: peripheral ID mask (or 0)
 *
 *	Return the AMBA device corresponding to the supplied parameters.
 *	If no device matches, वापसs शून्य.
 *
 *	NOTE: When a valid device is found, its refcount is
 *	incremented, and must be decremented beक्रमe the वापसed
 *	reference.
 */
काष्ठा amba_device *
amba_find_device(स्थिर अक्षर *busid, काष्ठा device *parent, अचिन्हित पूर्णांक id,
		 अचिन्हित पूर्णांक mask)
अणु
	काष्ठा find_data data;

	data.dev = शून्य;
	data.parent = parent;
	data.busid = busid;
	data.id = id;
	data.mask = mask;

	bus_क्रम_each_dev(&amba_bustype, शून्य, &data, amba_find_match);

	वापस data.dev;
पूर्ण

/**
 *	amba_request_regions - request all mem regions associated with device
 *	@dev: amba_device काष्ठाure क्रम device
 *	@name: name, or शून्य to use driver name
 */
पूर्णांक amba_request_regions(काष्ठा amba_device *dev, स्थिर अक्षर *name)
अणु
	पूर्णांक ret = 0;
	u32 size;

	अगर (!name)
		name = dev->dev.driver->name;

	size = resource_size(&dev->res);

	अगर (!request_mem_region(dev->res.start, size, name))
		ret = -EBUSY;

	वापस ret;
पूर्ण

/**
 *	amba_release_regions - release mem regions associated with device
 *	@dev: amba_device काष्ठाure क्रम device
 *
 *	Release regions claimed by a successful call to amba_request_regions.
 */
व्योम amba_release_regions(काष्ठा amba_device *dev)
अणु
	u32 size;

	size = resource_size(&dev->res);
	release_mem_region(dev->res.start, size);
पूर्ण

EXPORT_SYMBOL(amba_driver_रेजिस्टर);
EXPORT_SYMBOL(amba_driver_unरेजिस्टर);
EXPORT_SYMBOL(amba_device_रेजिस्टर);
EXPORT_SYMBOL(amba_device_unरेजिस्टर);
EXPORT_SYMBOL(amba_find_device);
EXPORT_SYMBOL(amba_request_regions);
EXPORT_SYMBOL(amba_release_regions);
