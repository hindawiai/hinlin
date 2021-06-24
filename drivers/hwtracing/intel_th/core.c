<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Intel(R) Trace Hub driver core
 *
 * Copyright (C) 2014-2015 Intel Corporation.
 */

#घोषणा pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/idr.h>
#समावेश <linux/pci.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/dma-mapping.h>

#समावेश "intel_th.h"
#समावेश "debug.h"

अटल bool host_mode __पढ़ो_mostly;
module_param(host_mode, bool, 0444);

अटल DEFINE_IDA(पूर्णांकel_th_ida);

अटल पूर्णांक पूर्णांकel_th_match(काष्ठा device *dev, काष्ठा device_driver *driver)
अणु
	काष्ठा पूर्णांकel_th_driver *thdrv = to_पूर्णांकel_th_driver(driver);
	काष्ठा पूर्णांकel_th_device *thdev = to_पूर्णांकel_th_device(dev);

	अगर (thdev->type == INTEL_TH_SWITCH &&
	    (!thdrv->enable || !thdrv->disable))
		वापस 0;

	वापस !म_भेद(thdev->name, driver->name);
पूर्ण

अटल पूर्णांक पूर्णांकel_th_child_हटाओ(काष्ठा device *dev, व्योम *data)
अणु
	device_release_driver(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_th_probe(काष्ठा device *dev)
अणु
	काष्ठा पूर्णांकel_th_driver *thdrv = to_पूर्णांकel_th_driver(dev->driver);
	काष्ठा पूर्णांकel_th_device *thdev = to_पूर्णांकel_th_device(dev);
	काष्ठा पूर्णांकel_th_driver *hubdrv;
	काष्ठा पूर्णांकel_th_device *hub = शून्य;
	पूर्णांक ret;

	अगर (thdev->type == INTEL_TH_SWITCH)
		hub = thdev;
	अन्यथा अगर (dev->parent)
		hub = to_पूर्णांकel_th_device(dev->parent);

	अगर (!hub || !hub->dev.driver)
		वापस -EPROBE_DEFER;

	hubdrv = to_पूर्णांकel_th_driver(hub->dev.driver);

	pm_runसमय_set_active(dev);
	pm_runसमय_no_callbacks(dev);
	pm_runसमय_enable(dev);

	ret = thdrv->probe(to_पूर्णांकel_th_device(dev));
	अगर (ret)
		जाओ out_pm;

	अगर (thdrv->attr_group) अणु
		ret = sysfs_create_group(&thdev->dev.kobj, thdrv->attr_group);
		अगर (ret)
			जाओ out;
	पूर्ण

	अगर (thdev->type == INTEL_TH_OUTPUT &&
	    !पूर्णांकel_th_output_asचिन्हित(thdev))
		/* करोes not talk to hardware */
		ret = hubdrv->assign(hub, thdev);

out:
	अगर (ret)
		thdrv->हटाओ(thdev);

out_pm:
	अगर (ret)
		pm_runसमय_disable(dev);

	वापस ret;
पूर्ण

अटल व्योम पूर्णांकel_th_device_हटाओ(काष्ठा पूर्णांकel_th_device *thdev);

अटल पूर्णांक पूर्णांकel_th_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा पूर्णांकel_th_driver *thdrv = to_पूर्णांकel_th_driver(dev->driver);
	काष्ठा पूर्णांकel_th_device *thdev = to_पूर्णांकel_th_device(dev);
	काष्ठा पूर्णांकel_th_device *hub = to_पूर्णांकel_th_hub(thdev);
	पूर्णांक err;

	अगर (thdev->type == INTEL_TH_SWITCH) अणु
		काष्ठा पूर्णांकel_th *th = to_पूर्णांकel_th(hub);
		पूर्णांक i, lowest;

		/* disconnect outमाला_दो */
		err = device_क्रम_each_child(dev, thdev, पूर्णांकel_th_child_हटाओ);
		अगर (err)
			वापस err;

		/*
		 * Remove outमाला_दो, that is, hub's children: they are created
		 * at hub's probe समय by having the hub call
		 * पूर्णांकel_th_output_enable() क्रम each of them.
		 */
		क्रम (i = 0, lowest = -1; i < th->num_thdevs; i++) अणु
			/*
			 * Move the non-output devices from higher up the
			 * th->thdev[] array to lower positions to मुख्यtain
			 * a contiguous array.
			 */
			अगर (th->thdev[i]->type != INTEL_TH_OUTPUT) अणु
				अगर (lowest >= 0) अणु
					th->thdev[lowest] = th->thdev[i];
					th->thdev[i] = शून्य;
					++lowest;
				पूर्ण

				जारी;
			पूर्ण

			अगर (lowest == -1)
				lowest = i;

			पूर्णांकel_th_device_हटाओ(th->thdev[i]);
			th->thdev[i] = शून्य;
		पूर्ण

		अगर (lowest >= 0)
			th->num_thdevs = lowest;
	पूर्ण

	अगर (thdrv->attr_group)
		sysfs_हटाओ_group(&thdev->dev.kobj, thdrv->attr_group);

	pm_runसमय_get_sync(dev);

	thdrv->हटाओ(thdev);

	अगर (पूर्णांकel_th_output_asचिन्हित(thdev)) अणु
		काष्ठा पूर्णांकel_th_driver *hubdrv =
			to_पूर्णांकel_th_driver(dev->parent->driver);

		अगर (hub->dev.driver)
			/* करोes not talk to hardware */
			hubdrv->unassign(hub, thdev);
	पूर्ण

	pm_runसमय_disable(dev);
	pm_runसमय_set_active(dev);
	pm_runसमय_enable(dev);

	वापस 0;
पूर्ण

अटल काष्ठा bus_type पूर्णांकel_th_bus = अणु
	.name		= "intel_th",
	.match		= पूर्णांकel_th_match,
	.probe		= पूर्णांकel_th_probe,
	.हटाओ		= पूर्णांकel_th_हटाओ,
पूर्ण;

अटल व्योम पूर्णांकel_th_device_मुक्त(काष्ठा पूर्णांकel_th_device *thdev);

अटल व्योम पूर्णांकel_th_device_release(काष्ठा device *dev)
अणु
	पूर्णांकel_th_device_मुक्त(to_पूर्णांकel_th_device(dev));
पूर्ण

अटल काष्ठा device_type पूर्णांकel_th_source_device_type = अणु
	.name		= "intel_th_source_device",
	.release	= पूर्णांकel_th_device_release,
पूर्ण;

अटल अक्षर *पूर्णांकel_th_output_devnode(काष्ठा device *dev, umode_t *mode,
				     kuid_t *uid, kgid_t *gid)
अणु
	काष्ठा पूर्णांकel_th_device *thdev = to_पूर्णांकel_th_device(dev);
	काष्ठा पूर्णांकel_th *th = to_पूर्णांकel_th(thdev);
	अक्षर *node;

	अगर (thdev->id >= 0)
		node = kaप्र_लिखो(GFP_KERNEL, "intel_th%d/%s%d", th->id,
				 thdev->name, thdev->id);
	अन्यथा
		node = kaप्र_लिखो(GFP_KERNEL, "intel_th%d/%s", th->id,
				 thdev->name);

	वापस node;
पूर्ण

अटल sमाप_प्रकार port_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा पूर्णांकel_th_device *thdev = to_पूर्णांकel_th_device(dev);

	अगर (thdev->output.port >= 0)
		वापस scnम_लिखो(buf, PAGE_SIZE, "%u\n", thdev->output.port);

	वापस scnम_लिखो(buf, PAGE_SIZE, "unassigned\n");
पूर्ण

अटल DEVICE_ATTR_RO(port);

अटल पूर्णांक पूर्णांकel_th_output_activate(काष्ठा पूर्णांकel_th_device *thdev)
अणु
	काष्ठा पूर्णांकel_th_driver *thdrv =
		to_पूर्णांकel_th_driver_or_null(thdev->dev.driver);
	काष्ठा पूर्णांकel_th *th = to_पूर्णांकel_th(thdev);
	पूर्णांक ret = 0;

	अगर (!thdrv)
		वापस -ENODEV;

	अगर (!try_module_get(thdrv->driver.owner))
		वापस -ENODEV;

	pm_runसमय_get_sync(&thdev->dev);

	अगर (th->activate)
		ret = th->activate(th);
	अगर (ret)
		जाओ fail_put;

	अगर (thdrv->activate)
		ret = thdrv->activate(thdev);
	अन्यथा
		पूर्णांकel_th_trace_enable(thdev);

	अगर (ret)
		जाओ fail_deactivate;

	वापस 0;

fail_deactivate:
	अगर (th->deactivate)
		th->deactivate(th);

fail_put:
	pm_runसमय_put(&thdev->dev);
	module_put(thdrv->driver.owner);

	वापस ret;
पूर्ण

अटल व्योम पूर्णांकel_th_output_deactivate(काष्ठा पूर्णांकel_th_device *thdev)
अणु
	काष्ठा पूर्णांकel_th_driver *thdrv =
		to_पूर्णांकel_th_driver_or_null(thdev->dev.driver);
	काष्ठा पूर्णांकel_th *th = to_पूर्णांकel_th(thdev);

	अगर (!thdrv)
		वापस;

	अगर (thdrv->deactivate)
		thdrv->deactivate(thdev);
	अन्यथा
		पूर्णांकel_th_trace_disable(thdev);

	अगर (th->deactivate)
		th->deactivate(th);

	pm_runसमय_put(&thdev->dev);
	module_put(thdrv->driver.owner);
पूर्ण

अटल sमाप_प्रकार active_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा पूर्णांकel_th_device *thdev = to_पूर्णांकel_th_device(dev);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", thdev->output.active);
पूर्ण

अटल sमाप_प्रकार active_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा पूर्णांकel_th_device *thdev = to_पूर्णांकel_th_device(dev);
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 10, &val);
	अगर (ret)
		वापस ret;

	अगर (!!val != thdev->output.active) अणु
		अगर (val)
			ret = पूर्णांकel_th_output_activate(thdev);
		अन्यथा
			पूर्णांकel_th_output_deactivate(thdev);
	पूर्ण

	वापस ret ? ret : size;
पूर्ण

अटल DEVICE_ATTR_RW(active);

अटल काष्ठा attribute *पूर्णांकel_th_output_attrs[] = अणु
	&dev_attr_port.attr,
	&dev_attr_active.attr,
	शून्य,
पूर्ण;

ATTRIBUTE_GROUPS(पूर्णांकel_th_output);

अटल काष्ठा device_type पूर्णांकel_th_output_device_type = अणु
	.name		= "intel_th_output_device",
	.groups		= पूर्णांकel_th_output_groups,
	.release	= पूर्णांकel_th_device_release,
	.devnode	= पूर्णांकel_th_output_devnode,
पूर्ण;

अटल काष्ठा device_type पूर्णांकel_th_चयन_device_type = अणु
	.name		= "intel_th_switch_device",
	.release	= पूर्णांकel_th_device_release,
पूर्ण;

अटल काष्ठा device_type *पूर्णांकel_th_device_type[] = अणु
	[INTEL_TH_SOURCE]	= &पूर्णांकel_th_source_device_type,
	[INTEL_TH_OUTPUT]	= &पूर्णांकel_th_output_device_type,
	[INTEL_TH_SWITCH]	= &पूर्णांकel_th_चयन_device_type,
पूर्ण;

पूर्णांक पूर्णांकel_th_driver_रेजिस्टर(काष्ठा पूर्णांकel_th_driver *thdrv)
अणु
	अगर (!thdrv->probe || !thdrv->हटाओ)
		वापस -EINVAL;

	thdrv->driver.bus = &पूर्णांकel_th_bus;

	वापस driver_रेजिस्टर(&thdrv->driver);
पूर्ण
EXPORT_SYMBOL_GPL(पूर्णांकel_th_driver_रेजिस्टर);

व्योम पूर्णांकel_th_driver_unरेजिस्टर(काष्ठा पूर्णांकel_th_driver *thdrv)
अणु
	driver_unरेजिस्टर(&thdrv->driver);
पूर्ण
EXPORT_SYMBOL_GPL(पूर्णांकel_th_driver_unरेजिस्टर);

अटल काष्ठा पूर्णांकel_th_device *
पूर्णांकel_th_device_alloc(काष्ठा पूर्णांकel_th *th, अचिन्हित पूर्णांक type, स्थिर अक्षर *name,
		      पूर्णांक id)
अणु
	काष्ठा device *parent;
	काष्ठा पूर्णांकel_th_device *thdev;

	अगर (type == INTEL_TH_OUTPUT)
		parent = &th->hub->dev;
	अन्यथा
		parent = th->dev;

	thdev = kzalloc(माप(*thdev) + म_माप(name) + 1, GFP_KERNEL);
	अगर (!thdev)
		वापस शून्य;

	thdev->id = id;
	thdev->type = type;

	म_नकल(thdev->name, name);
	device_initialize(&thdev->dev);
	thdev->dev.bus = &पूर्णांकel_th_bus;
	thdev->dev.type = पूर्णांकel_th_device_type[type];
	thdev->dev.parent = parent;
	thdev->dev.dma_mask = parent->dma_mask;
	thdev->dev.dma_parms = parent->dma_parms;
	dma_set_coherent_mask(&thdev->dev, parent->coherent_dma_mask);
	अगर (id >= 0)
		dev_set_name(&thdev->dev, "%d-%s%d", th->id, name, id);
	अन्यथा
		dev_set_name(&thdev->dev, "%d-%s", th->id, name);

	वापस thdev;
पूर्ण

अटल पूर्णांक पूर्णांकel_th_device_add_resources(काष्ठा पूर्णांकel_th_device *thdev,
					 काष्ठा resource *res, पूर्णांक nres)
अणु
	काष्ठा resource *r;

	r = kmemdup(res, माप(*res) * nres, GFP_KERNEL);
	अगर (!r)
		वापस -ENOMEM;

	thdev->resource = r;
	thdev->num_resources = nres;

	वापस 0;
पूर्ण

अटल व्योम पूर्णांकel_th_device_हटाओ(काष्ठा पूर्णांकel_th_device *thdev)
अणु
	device_del(&thdev->dev);
	put_device(&thdev->dev);
पूर्ण

अटल व्योम पूर्णांकel_th_device_मुक्त(काष्ठा पूर्णांकel_th_device *thdev)
अणु
	kमुक्त(thdev->resource);
	kमुक्त(thdev);
पूर्ण

/*
 * Intel(R) Trace Hub subdevices
 */
अटल स्थिर काष्ठा पूर्णांकel_th_subdevice अणु
	स्थिर अक्षर		*name;
	काष्ठा resource		res[3];
	अचिन्हित		nres;
	अचिन्हित		type;
	अचिन्हित		otype;
	bool			mknode;
	अचिन्हित		scrpd;
	पूर्णांक			id;
पूर्ण पूर्णांकel_th_subdevices[] = अणु
	अणु
		.nres	= 1,
		.res	= अणु
			अणु
				/* Handle TSCU and CTS from GTH driver */
				.start	= REG_GTH_OFFSET,
				.end	= REG_CTS_OFFSET + REG_CTS_LENGTH - 1,
				.flags	= IORESOURCE_MEM,
			पूर्ण,
		पूर्ण,
		.name	= "gth",
		.type	= INTEL_TH_SWITCH,
		.id	= -1,
	पूर्ण,
	अणु
		.nres	= 2,
		.res	= अणु
			अणु
				.start	= REG_MSU_OFFSET,
				.end	= REG_MSU_OFFSET + REG_MSU_LENGTH - 1,
				.flags	= IORESOURCE_MEM,
			पूर्ण,
			अणु
				.start	= BUF_MSU_OFFSET,
				.end	= BUF_MSU_OFFSET + BUF_MSU_LENGTH - 1,
				.flags	= IORESOURCE_MEM,
			पूर्ण,
		पूर्ण,
		.name	= "msc",
		.id	= 0,
		.type	= INTEL_TH_OUTPUT,
		.mknode	= true,
		.otype	= GTH_MSU,
		.scrpd	= SCRPD_MEM_IS_PRIM_DEST | SCRPD_MSC0_IS_ENABLED,
	पूर्ण,
	अणु
		.nres	= 2,
		.res	= अणु
			अणु
				.start	= REG_MSU_OFFSET,
				.end	= REG_MSU_OFFSET + REG_MSU_LENGTH - 1,
				.flags	= IORESOURCE_MEM,
			पूर्ण,
			अणु
				.start	= BUF_MSU_OFFSET,
				.end	= BUF_MSU_OFFSET + BUF_MSU_LENGTH - 1,
				.flags	= IORESOURCE_MEM,
			पूर्ण,
		पूर्ण,
		.name	= "msc",
		.id	= 1,
		.type	= INTEL_TH_OUTPUT,
		.mknode	= true,
		.otype	= GTH_MSU,
		.scrpd	= SCRPD_MEM_IS_PRIM_DEST | SCRPD_MSC1_IS_ENABLED,
	पूर्ण,
	अणु
		.nres	= 2,
		.res	= अणु
			अणु
				.start	= REG_STH_OFFSET,
				.end	= REG_STH_OFFSET + REG_STH_LENGTH - 1,
				.flags	= IORESOURCE_MEM,
			पूर्ण,
			अणु
				.start	= TH_MMIO_SW,
				.end	= 0,
				.flags	= IORESOURCE_MEM,
			पूर्ण,
		पूर्ण,
		.id	= -1,
		.name	= "sth",
		.type	= INTEL_TH_SOURCE,
	पूर्ण,
	अणु
		.nres	= 2,
		.res	= अणु
			अणु
				.start	= REG_STH_OFFSET,
				.end	= REG_STH_OFFSET + REG_STH_LENGTH - 1,
				.flags	= IORESOURCE_MEM,
			पूर्ण,
			अणु
				.start	= TH_MMIO_RTIT,
				.end	= 0,
				.flags	= IORESOURCE_MEM,
			पूर्ण,
		पूर्ण,
		.id	= -1,
		.name	= "rtit",
		.type	= INTEL_TH_SOURCE,
	पूर्ण,
	अणु
		.nres	= 1,
		.res	= अणु
			अणु
				.start	= REG_PTI_OFFSET,
				.end	= REG_PTI_OFFSET + REG_PTI_LENGTH - 1,
				.flags	= IORESOURCE_MEM,
			पूर्ण,
		पूर्ण,
		.id	= -1,
		.name	= "pti",
		.type	= INTEL_TH_OUTPUT,
		.otype	= GTH_PTI,
		.scrpd	= SCRPD_PTI_IS_PRIM_DEST,
	पूर्ण,
	अणु
		.nres	= 1,
		.res	= अणु
			अणु
				.start	= REG_PTI_OFFSET,
				.end	= REG_PTI_OFFSET + REG_PTI_LENGTH - 1,
				.flags	= IORESOURCE_MEM,
			पूर्ण,
		पूर्ण,
		.id	= -1,
		.name	= "lpp",
		.type	= INTEL_TH_OUTPUT,
		.otype	= GTH_LPP,
		.scrpd	= SCRPD_PTI_IS_PRIM_DEST,
	पूर्ण,
	अणु
		.nres	= 1,
		.res	= अणु
			अणु
				.start	= REG_DCIH_OFFSET,
				.end	= REG_DCIH_OFFSET + REG_DCIH_LENGTH - 1,
				.flags	= IORESOURCE_MEM,
			पूर्ण,
		पूर्ण,
		.id	= -1,
		.name	= "dcih",
		.type	= INTEL_TH_OUTPUT,
	पूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_MODULES
अटल व्योम __पूर्णांकel_th_request_hub_module(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा पूर्णांकel_th *th = container_of(work, काष्ठा पूर्णांकel_th,
					   request_module_work);

	request_module("intel_th_%s", th->hub->name);
पूर्ण

अटल पूर्णांक पूर्णांकel_th_request_hub_module(काष्ठा पूर्णांकel_th *th)
अणु
	INIT_WORK(&th->request_module_work, __पूर्णांकel_th_request_hub_module);
	schedule_work(&th->request_module_work);

	वापस 0;
पूर्ण

अटल व्योम पूर्णांकel_th_request_hub_module_flush(काष्ठा पूर्णांकel_th *th)
अणु
	flush_work(&th->request_module_work);
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक पूर्णांकel_th_request_hub_module(काष्ठा पूर्णांकel_th *th)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_th_request_hub_module_flush(काष्ठा पूर्णांकel_th *th)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_MODULES */

अटल काष्ठा पूर्णांकel_th_device *
पूर्णांकel_th_subdevice_alloc(काष्ठा पूर्णांकel_th *th,
			 स्थिर काष्ठा पूर्णांकel_th_subdevice *subdev)
अणु
	काष्ठा पूर्णांकel_th_device *thdev;
	काष्ठा resource res[3];
	अचिन्हित पूर्णांक req = 0;
	पूर्णांक r, err;

	thdev = पूर्णांकel_th_device_alloc(th, subdev->type, subdev->name,
				      subdev->id);
	अगर (!thdev)
		वापस ERR_PTR(-ENOMEM);

	thdev->drvdata = th->drvdata;

	स_नकल(res, subdev->res,
	       माप(काष्ठा resource) * subdev->nres);

	क्रम (r = 0; r < subdev->nres; r++) अणु
		काष्ठा resource *devres = th->resource;
		पूर्णांक bar = TH_MMIO_CONFIG;

		/*
		 * Take .end == 0 to mean 'take the whole bar',
		 * .start then tells us which bar it is. Default to
		 * TH_MMIO_CONFIG.
		 */
		अगर (!res[r].end && res[r].flags == IORESOURCE_MEM) अणु
			bar = res[r].start;
			err = -ENODEV;
			अगर (bar >= th->num_resources)
				जाओ fail_put_device;
			res[r].start = 0;
			res[r].end = resource_size(&devres[bar]) - 1;
		पूर्ण

		अगर (res[r].flags & IORESOURCE_MEM) अणु
			res[r].start	+= devres[bar].start;
			res[r].end	+= devres[bar].start;

			dev_dbg(th->dev, "%s:%d @ %pR\n",
				subdev->name, r, &res[r]);
		पूर्ण अन्यथा अगर (res[r].flags & IORESOURCE_IRQ) अणु
			/*
			 * Only pass on the IRQ अगर we have useful पूर्णांकerrupts:
			 * the ones that can be configured via MINTCTL.
			 */
			अगर (INTEL_TH_CAP(th, has_mपूर्णांकctl) && th->irq != -1)
				res[r].start = th->irq;
		पूर्ण
	पूर्ण

	err = पूर्णांकel_th_device_add_resources(thdev, res, subdev->nres);
	अगर (err)
		जाओ fail_put_device;

	अगर (subdev->type == INTEL_TH_OUTPUT) अणु
		अगर (subdev->mknode)
			thdev->dev.devt = MKDEV(th->major, th->num_thdevs);
		thdev->output.type = subdev->otype;
		thdev->output.port = -1;
		thdev->output.scratchpad = subdev->scrpd;
	पूर्ण अन्यथा अगर (subdev->type == INTEL_TH_SWITCH) अणु
		thdev->host_mode =
			INTEL_TH_CAP(th, host_mode_only) ? true : host_mode;
		th->hub = thdev;
	पूर्ण

	err = device_add(&thdev->dev);
	अगर (err)
		जाओ fail_मुक्त_res;

	/* need चयन driver to be loaded to क्रमागतerate the rest */
	अगर (subdev->type == INTEL_TH_SWITCH && !req) अणु
		err = पूर्णांकel_th_request_hub_module(th);
		अगर (!err)
			req++;
	पूर्ण

	वापस thdev;

fail_मुक्त_res:
	kमुक्त(thdev->resource);

fail_put_device:
	put_device(&thdev->dev);

	वापस ERR_PTR(err);
पूर्ण

/**
 * पूर्णांकel_th_output_enable() - find and enable a device क्रम a given output type
 * @th:		Intel TH instance
 * @otype:	output type
 *
 * Go through the unallocated output devices, find the first one whos type
 * matches @otype and instantiate it. These devices are हटाओd when the hub
 * device is हटाओd, see पूर्णांकel_th_हटाओ().
 */
पूर्णांक पूर्णांकel_th_output_enable(काष्ठा पूर्णांकel_th *th, अचिन्हित पूर्णांक otype)
अणु
	काष्ठा पूर्णांकel_th_device *thdev;
	पूर्णांक src = 0, dst = 0;

	क्रम (src = 0, dst = 0; dst <= th->num_thdevs; src++, dst++) अणु
		क्रम (; src < ARRAY_SIZE(पूर्णांकel_th_subdevices); src++) अणु
			अगर (पूर्णांकel_th_subdevices[src].type != INTEL_TH_OUTPUT)
				जारी;

			अगर (पूर्णांकel_th_subdevices[src].otype != otype)
				जारी;

			अवरोध;
		पूर्ण

		/* no unallocated matching subdevices */
		अगर (src == ARRAY_SIZE(पूर्णांकel_th_subdevices))
			वापस -ENODEV;

		क्रम (; dst < th->num_thdevs; dst++) अणु
			अगर (th->thdev[dst]->type != INTEL_TH_OUTPUT)
				जारी;

			अगर (th->thdev[dst]->output.type != otype)
				जारी;

			अवरोध;
		पूर्ण

		/*
		 * पूर्णांकel_th_subdevices[src] matches our requirements and is
		 * not matched in th::thdev[]
		 */
		अगर (dst == th->num_thdevs)
			जाओ found;
	पूर्ण

	वापस -ENODEV;

found:
	thdev = पूर्णांकel_th_subdevice_alloc(th, &पूर्णांकel_th_subdevices[src]);
	अगर (IS_ERR(thdev))
		वापस PTR_ERR(thdev);

	th->thdev[th->num_thdevs++] = thdev;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(पूर्णांकel_th_output_enable);

अटल पूर्णांक पूर्णांकel_th_populate(काष्ठा पूर्णांकel_th *th)
अणु
	पूर्णांक src;

	/* create devices क्रम each पूर्णांकel_th_subdevice */
	क्रम (src = 0; src < ARRAY_SIZE(पूर्णांकel_th_subdevices); src++) अणु
		स्थिर काष्ठा पूर्णांकel_th_subdevice *subdev =
			&पूर्णांकel_th_subdevices[src];
		काष्ठा पूर्णांकel_th_device *thdev;

		/* only allow SOURCE and SWITCH devices in host mode */
		अगर ((INTEL_TH_CAP(th, host_mode_only) || host_mode) &&
		    subdev->type == INTEL_TH_OUTPUT)
			जारी;

		/*
		 * करोn't enable port OUTPUTs in this path; SWITCH enables them
		 * via पूर्णांकel_th_output_enable()
		 */
		अगर (subdev->type == INTEL_TH_OUTPUT &&
		    subdev->otype != GTH_NONE)
			जारी;

		thdev = पूर्णांकel_th_subdevice_alloc(th, subdev);
		/* note: caller should मुक्त subdevices from th::thdev[] */
		अगर (IS_ERR(thdev)) अणु
			/* ENODEV क्रम inभागidual subdevices is allowed */
			अगर (PTR_ERR(thdev) == -ENODEV)
				जारी;

			वापस PTR_ERR(thdev);
		पूर्ण

		th->thdev[th->num_thdevs++] = thdev;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_th_output_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	स्थिर काष्ठा file_operations *fops;
	काष्ठा पूर्णांकel_th_driver *thdrv;
	काष्ठा device *dev;
	पूर्णांक err;

	dev = bus_find_device_by_devt(&पूर्णांकel_th_bus, inode->i_rdev);
	अगर (!dev || !dev->driver)
		वापस -ENODEV;

	thdrv = to_पूर्णांकel_th_driver(dev->driver);
	fops = fops_get(thdrv->fops);
	अगर (!fops)
		वापस -ENODEV;

	replace_fops(file, fops);

	file->निजी_data = to_पूर्णांकel_th_device(dev);

	अगर (file->f_op->खोलो) अणु
		err = file->f_op->खोलो(inode, file);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations पूर्णांकel_th_output_fops = अणु
	.खोलो	= पूर्णांकel_th_output_खोलो,
	.llseek	= noop_llseek,
पूर्ण;

अटल irqवापस_t पूर्णांकel_th_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा पूर्णांकel_th *th = data;
	irqवापस_t ret = IRQ_NONE;
	काष्ठा पूर्णांकel_th_driver *d;
	पूर्णांक i;

	क्रम (i = 0; i < th->num_thdevs; i++) अणु
		अगर (th->thdev[i]->type != INTEL_TH_OUTPUT)
			जारी;

		d = to_पूर्णांकel_th_driver(th->thdev[i]->dev.driver);
		अगर (d && d->irq)
			ret |= d->irq(th->thdev[i]);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * पूर्णांकel_th_alloc() - allocate a new Intel TH device and its subdevices
 * @dev:	parent device
 * @devres:	resources indexed by th_mmio_idx
 * @irq:	irq number
 */
काष्ठा पूर्णांकel_th *
पूर्णांकel_th_alloc(काष्ठा device *dev, स्थिर काष्ठा पूर्णांकel_th_drvdata *drvdata,
	       काष्ठा resource *devres, अचिन्हित पूर्णांक ndevres)
अणु
	पूर्णांक err, r, nr_mmios = 0;
	काष्ठा पूर्णांकel_th *th;

	th = kzalloc(माप(*th), GFP_KERNEL);
	अगर (!th)
		वापस ERR_PTR(-ENOMEM);

	th->id = ida_simple_get(&पूर्णांकel_th_ida, 0, 0, GFP_KERNEL);
	अगर (th->id < 0) अणु
		err = th->id;
		जाओ err_alloc;
	पूर्ण

	th->major = __रेजिस्टर_chrdev(0, 0, TH_POSSIBLE_OUTPUTS,
				      "intel_th/output", &पूर्णांकel_th_output_fops);
	अगर (th->major < 0) अणु
		err = th->major;
		जाओ err_ida;
	पूर्ण
	th->irq = -1;
	th->dev = dev;
	th->drvdata = drvdata;

	क्रम (r = 0; r < ndevres; r++)
		चयन (devres[r].flags & IORESOURCE_TYPE_BITS) अणु
		हाल IORESOURCE_MEM:
			th->resource[nr_mmios++] = devres[r];
			अवरोध;
		हाल IORESOURCE_IRQ:
			err = devm_request_irq(dev, devres[r].start,
					       पूर्णांकel_th_irq, IRQF_SHARED,
					       dev_name(dev), th);
			अगर (err)
				जाओ err_chrdev;

			अगर (th->irq == -1)
				th->irq = devres[r].start;
			th->num_irqs++;
			अवरोध;
		शेष:
			dev_warn(dev, "Unknown resource type %lx\n",
				 devres[r].flags);
			अवरोध;
		पूर्ण

	th->num_resources = nr_mmios;

	dev_set_drvdata(dev, th);

	pm_runसमय_no_callbacks(dev);
	pm_runसमय_put(dev);
	pm_runसमय_allow(dev);

	err = पूर्णांकel_th_populate(th);
	अगर (err) अणु
		/* मुक्त the subdevices and unकरो everything */
		पूर्णांकel_th_मुक्त(th);
		वापस ERR_PTR(err);
	पूर्ण

	वापस th;

err_chrdev:
	__unरेजिस्टर_chrdev(th->major, 0, TH_POSSIBLE_OUTPUTS,
			    "intel_th/output");

err_ida:
	ida_simple_हटाओ(&पूर्णांकel_th_ida, th->id);

err_alloc:
	kमुक्त(th);

	वापस ERR_PTR(err);
पूर्ण
EXPORT_SYMBOL_GPL(पूर्णांकel_th_alloc);

व्योम पूर्णांकel_th_मुक्त(काष्ठा पूर्णांकel_th *th)
अणु
	पूर्णांक i;

	पूर्णांकel_th_request_hub_module_flush(th);

	पूर्णांकel_th_device_हटाओ(th->hub);
	क्रम (i = 0; i < th->num_thdevs; i++) अणु
		अगर (th->thdev[i] != th->hub)
			पूर्णांकel_th_device_हटाओ(th->thdev[i]);
		th->thdev[i] = शून्य;
	पूर्ण

	th->num_thdevs = 0;

	क्रम (i = 0; i < th->num_irqs; i++)
		devm_मुक्त_irq(th->dev, th->irq + i, th);

	pm_runसमय_get_sync(th->dev);
	pm_runसमय_क्रमbid(th->dev);

	__unरेजिस्टर_chrdev(th->major, 0, TH_POSSIBLE_OUTPUTS,
			    "intel_th/output");

	ida_simple_हटाओ(&पूर्णांकel_th_ida, th->id);

	kमुक्त(th);
पूर्ण
EXPORT_SYMBOL_GPL(पूर्णांकel_th_मुक्त);

/**
 * पूर्णांकel_th_trace_enable() - enable tracing क्रम an output device
 * @thdev:	output device that requests tracing be enabled
 */
पूर्णांक पूर्णांकel_th_trace_enable(काष्ठा पूर्णांकel_th_device *thdev)
अणु
	काष्ठा पूर्णांकel_th_device *hub = to_पूर्णांकel_th_device(thdev->dev.parent);
	काष्ठा पूर्णांकel_th_driver *hubdrv = to_पूर्णांकel_th_driver(hub->dev.driver);

	अगर (WARN_ON_ONCE(hub->type != INTEL_TH_SWITCH))
		वापस -EINVAL;

	अगर (WARN_ON_ONCE(thdev->type != INTEL_TH_OUTPUT))
		वापस -EINVAL;

	pm_runसमय_get_sync(&thdev->dev);
	hubdrv->enable(hub, &thdev->output);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(पूर्णांकel_th_trace_enable);

/**
 * पूर्णांकel_th_trace_चयन() - execute a चयन sequence
 * @thdev:	output device that requests tracing चयन
 */
पूर्णांक पूर्णांकel_th_trace_चयन(काष्ठा पूर्णांकel_th_device *thdev)
अणु
	काष्ठा पूर्णांकel_th_device *hub = to_पूर्णांकel_th_device(thdev->dev.parent);
	काष्ठा पूर्णांकel_th_driver *hubdrv = to_पूर्णांकel_th_driver(hub->dev.driver);

	अगर (WARN_ON_ONCE(hub->type != INTEL_TH_SWITCH))
		वापस -EINVAL;

	अगर (WARN_ON_ONCE(thdev->type != INTEL_TH_OUTPUT))
		वापस -EINVAL;

	hubdrv->trig_चयन(hub, &thdev->output);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(पूर्णांकel_th_trace_चयन);

/**
 * पूर्णांकel_th_trace_disable() - disable tracing क्रम an output device
 * @thdev:	output device that requests tracing be disabled
 */
पूर्णांक पूर्णांकel_th_trace_disable(काष्ठा पूर्णांकel_th_device *thdev)
अणु
	काष्ठा पूर्णांकel_th_device *hub = to_पूर्णांकel_th_device(thdev->dev.parent);
	काष्ठा पूर्णांकel_th_driver *hubdrv = to_पूर्णांकel_th_driver(hub->dev.driver);

	WARN_ON_ONCE(hub->type != INTEL_TH_SWITCH);
	अगर (WARN_ON_ONCE(thdev->type != INTEL_TH_OUTPUT))
		वापस -EINVAL;

	hubdrv->disable(hub, &thdev->output);
	pm_runसमय_put(&thdev->dev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(पूर्णांकel_th_trace_disable);

पूर्णांक पूर्णांकel_th_set_output(काष्ठा पूर्णांकel_th_device *thdev,
			अचिन्हित पूर्णांक master)
अणु
	काष्ठा पूर्णांकel_th_device *hub = to_पूर्णांकel_th_hub(thdev);
	काष्ठा पूर्णांकel_th_driver *hubdrv = to_पूर्णांकel_th_driver(hub->dev.driver);
	पूर्णांक ret;

	/* In host mode, this is up to the बाह्यal debugger, करो nothing. */
	अगर (hub->host_mode)
		वापस 0;

	/*
	 * hub is instantiated together with the source device that
	 * calls here, so guaranteed to be present.
	 */
	hubdrv = to_पूर्णांकel_th_driver(hub->dev.driver);
	अगर (!hubdrv || !try_module_get(hubdrv->driver.owner))
		वापस -EINVAL;

	अगर (!hubdrv->set_output) अणु
		ret = -ENOTSUPP;
		जाओ out;
	पूर्ण

	ret = hubdrv->set_output(hub, master);

out:
	module_put(hubdrv->driver.owner);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(पूर्णांकel_th_set_output);

अटल पूर्णांक __init पूर्णांकel_th_init(व्योम)
अणु
	पूर्णांकel_th_debug_init();

	वापस bus_रेजिस्टर(&पूर्णांकel_th_bus);
पूर्ण
subsys_initcall(पूर्णांकel_th_init);

अटल व्योम __निकास पूर्णांकel_th_निकास(व्योम)
अणु
	पूर्णांकel_th_debug_करोne();

	bus_unरेजिस्टर(&पूर्णांकel_th_bus);
पूर्ण
module_निकास(पूर्णांकel_th_निकास);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Intel(R) Trace Hub controller driver");
MODULE_AUTHOR("Alexander Shishkin <alexander.shishkin@linux.intel.com>");
