<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  Pvpanic MMIO Device Support
 *
 *  Copyright (C) 2013 Fujitsu.
 *  Copyright (C) 2018 ZTE.
 *  Copyright (C) 2021 Oracle.
 */

#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/kexec.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>

#समावेश <uapi/misc/pvpanic.h>

#समावेश "pvpanic.h"

MODULE_AUTHOR("Hu Tao <hutao@cn.fujitsu.com>");
MODULE_DESCRIPTION("pvpanic-mmio device driver");
MODULE_LICENSE("GPL");

अटल sमाप_प्रकार capability_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा pvpanic_instance *pi = dev_get_drvdata(dev);

	वापस sysfs_emit(buf, "%x\n", pi->capability);
पूर्ण
अटल DEVICE_ATTR_RO(capability);

अटल sमाप_प्रकार events_show(काष्ठा device *dev,  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा pvpanic_instance *pi = dev_get_drvdata(dev);

	वापस sysfs_emit(buf, "%x\n", pi->events);
पूर्ण

अटल sमाप_प्रकार events_store(काष्ठा device *dev,  काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा pvpanic_instance *pi = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक पंचांगp;
	पूर्णांक err;

	err = kstrtouपूर्णांक(buf, 16, &पंचांगp);
	अगर (err)
		वापस err;

	अगर ((पंचांगp & pi->capability) != पंचांगp)
		वापस -EINVAL;

	pi->events = पंचांगp;

	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(events);

अटल काष्ठा attribute *pvpanic_mmio_dev_attrs[] = अणु
	&dev_attr_capability.attr,
	&dev_attr_events.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(pvpanic_mmio_dev);

अटल पूर्णांक pvpanic_mmio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा pvpanic_instance *pi;
	काष्ठा resource *res;
	व्योम __iomem *base;

	res = platक्रमm_get_mem_or_io(pdev, 0);
	अगर (!res)
		वापस -EINVAL;

	चयन (resource_type(res)) अणु
	हाल IORESOURCE_IO:
		base = devm_ioport_map(dev, res->start, resource_size(res));
		अगर (!base)
			वापस -ENOMEM;
		अवरोध;
	हाल IORESOURCE_MEM:
		base = devm_ioremap_resource(dev, res);
		अगर (IS_ERR(base))
			वापस PTR_ERR(base);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	pi = kदो_स्मृति(माप(*pi), GFP_ATOMIC);
	अगर (!pi)
		वापस -ENOMEM;

	pi->base = base;
	pi->capability = PVPANIC_PANICKED | PVPANIC_CRASH_LOADED;

	/* initlize capability by RDPT */
	pi->capability &= ioपढ़ो8(base);
	pi->events = pi->capability;

	dev_set_drvdata(dev, pi);

	वापस pvpanic_probe(pi);
पूर्ण

अटल पूर्णांक pvpanic_mmio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pvpanic_instance *pi = dev_get_drvdata(&pdev->dev);

	pvpanic_हटाओ(pi);
	kमुक्त(pi);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id pvpanic_mmio_match[] = अणु
	अणु .compatible = "qemu,pvpanic-mmio", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, pvpanic_mmio_match);

अटल स्थिर काष्ठा acpi_device_id pvpanic_device_ids[] = अणु
	अणु "QEMU0001", 0 पूर्ण,
	अणु "", 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, pvpanic_device_ids);

अटल काष्ठा platक्रमm_driver pvpanic_mmio_driver = अणु
	.driver = अणु
		.name = "pvpanic-mmio",
		.of_match_table = pvpanic_mmio_match,
		.acpi_match_table = pvpanic_device_ids,
		.dev_groups = pvpanic_mmio_dev_groups,
	पूर्ण,
	.probe = pvpanic_mmio_probe,
	.हटाओ = pvpanic_mmio_हटाओ,
पूर्ण;
module_platक्रमm_driver(pvpanic_mmio_driver);
