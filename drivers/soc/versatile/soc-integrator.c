<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2014 Linaro Ltd.
 *
 * Author: Linus Walleij <linus.walleij@linaro.org>
 */
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/sys_soc.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>
#समावेश <linux/of.h>

#घोषणा INTEGRATOR_HDR_ID_OFFSET	0x00

अटल u32 पूर्णांकegrator_coreid;

अटल स्थिर काष्ठा of_device_id पूर्णांकegrator_cm_match[] = अणु
	अणु .compatible = "arm,core-module-integrator", पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल स्थिर अक्षर *पूर्णांकegrator_arch_str(u32 id)
अणु
	चयन ((id >> 16) & 0xff) अणु
	हाल 0x00:
		वापस "ASB little-endian";
	हाल 0x01:
		वापस "AHB little-endian";
	हाल 0x03:
		वापस "AHB-Lite system bus, bi-endian";
	हाल 0x04:
		वापस "AHB";
	हाल 0x08:
		वापस "AHB system bus, ASB processor bus";
	शेष:
		वापस "Unknown";
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *पूर्णांकegrator_fpga_str(u32 id)
अणु
	चयन ((id >> 12) & 0xf) अणु
	हाल 0x01:
		वापस "XC4062";
	हाल 0x02:
		वापस "XC4085";
	हाल 0x03:
		वापस "XVC600";
	हाल 0x04:
		वापस "EPM7256AE (Altera PLD)";
	शेष:
		वापस "Unknown";
	पूर्ण
पूर्ण

अटल sमाप_प्रकार
manufacturer_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%02x\n", पूर्णांकegrator_coreid >> 24);
पूर्ण

अटल DEVICE_ATTR_RO(manufacturer);

अटल sमाप_प्रकार
arch_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%s\n", पूर्णांकegrator_arch_str(पूर्णांकegrator_coreid));
पूर्ण

अटल DEVICE_ATTR_RO(arch);

अटल sमाप_प्रकार
fpga_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%s\n", पूर्णांकegrator_fpga_str(पूर्णांकegrator_coreid));
पूर्ण

अटल DEVICE_ATTR_RO(fpga);

अटल sमाप_प्रकार
build_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%02x\n", (पूर्णांकegrator_coreid >> 4) & 0xFF);
पूर्ण

अटल DEVICE_ATTR_RO(build);

अटल काष्ठा attribute *पूर्णांकegrator_attrs[] = अणु
	&dev_attr_manufacturer.attr,
	&dev_attr_arch.attr,
	&dev_attr_fpga.attr,
	&dev_attr_build.attr,
	शून्य
पूर्ण;

ATTRIBUTE_GROUPS(पूर्णांकegrator);

अटल पूर्णांक __init पूर्णांकegrator_soc_init(व्योम)
अणु
	काष्ठा regmap *syscon_regmap;
	काष्ठा soc_device *soc_dev;
	काष्ठा soc_device_attribute *soc_dev_attr;
	काष्ठा device_node *np;
	काष्ठा device *dev;
	u32 val;
	पूर्णांक ret;

	np = of_find_matching_node(शून्य, पूर्णांकegrator_cm_match);
	अगर (!np)
		वापस -ENODEV;

	syscon_regmap = syscon_node_to_regmap(np);
	अगर (IS_ERR(syscon_regmap))
		वापस PTR_ERR(syscon_regmap);

	ret = regmap_पढ़ो(syscon_regmap, INTEGRATOR_HDR_ID_OFFSET,
			  &val);
	अगर (ret)
		वापस -ENODEV;
	पूर्णांकegrator_coreid = val;

	soc_dev_attr = kzalloc(माप(*soc_dev_attr), GFP_KERNEL);
	अगर (!soc_dev_attr)
		वापस -ENOMEM;

	soc_dev_attr->soc_id = "Integrator";
	soc_dev_attr->machine = "Integrator";
	soc_dev_attr->family = "Versatile";
	soc_dev_attr->custom_attr_group = पूर्णांकegrator_groups[0];
	soc_dev = soc_device_रेजिस्टर(soc_dev_attr);
	अगर (IS_ERR(soc_dev)) अणु
		kमुक्त(soc_dev_attr);
		वापस -ENODEV;
	पूर्ण
	dev = soc_device_to_device(soc_dev);

	dev_info(dev, "Detected ARM core module:\n");
	dev_info(dev, "    Manufacturer: %02x\n", (val >> 24));
	dev_info(dev, "    Architecture: %s\n", पूर्णांकegrator_arch_str(val));
	dev_info(dev, "    FPGA: %s\n", पूर्णांकegrator_fpga_str(val));
	dev_info(dev, "    Build: %02x\n", (val >> 4) & 0xFF);
	dev_info(dev, "    Rev: %c\n", ('A' + (val & 0x03)));

	वापस 0;
पूर्ण
device_initcall(पूर्णांकegrator_soc_init);
