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

/* System ID in syscon */
#घोषणा REALVIEW_SYS_ID_OFFSET 0x00

अटल स्थिर काष्ठा of_device_id realview_soc_of_match[] = अणु
	अणु .compatible = "arm,realview-eb-soc",	पूर्ण,
	अणु .compatible = "arm,realview-pb1176-soc", पूर्ण,
	अणु .compatible = "arm,realview-pb11mp-soc", पूर्ण,
	अणु .compatible = "arm,realview-pba8-soc", पूर्ण,
	अणु .compatible = "arm,realview-pbx-soc", पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल u32 realview_coreid;

अटल स्थिर अक्षर *realview_arch_str(u32 id)
अणु
	चयन ((id >> 8) & 0xf) अणु
	हाल 0x04:
		वापस "AHB";
	हाल 0x05:
		वापस "Multi-layer AXI";
	शेष:
		वापस "Unknown";
	पूर्ण
पूर्ण

अटल sमाप_प्रकार
manufacturer_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%02x\n", realview_coreid >> 24);
पूर्ण

अटल DEVICE_ATTR_RO(manufacturer);

अटल sमाप_प्रकार
board_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "HBI-%03x\n", ((realview_coreid >> 16) & 0xfff));
पूर्ण

अटल DEVICE_ATTR_RO(board);

अटल sमाप_प्रकार
fpga_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%s\n", realview_arch_str(realview_coreid));
पूर्ण

अटल DEVICE_ATTR_RO(fpga);

अटल sमाप_प्रकार
build_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%02x\n", (realview_coreid & 0xFF));
पूर्ण

अटल DEVICE_ATTR_RO(build);

अटल काष्ठा attribute *realview_attrs[] = अणु
	&dev_attr_manufacturer.attr,
	&dev_attr_board.attr,
	&dev_attr_fpga.attr,
	&dev_attr_build.attr,
	शून्य
पूर्ण;

ATTRIBUTE_GROUPS(realview);

अटल पूर्णांक realview_soc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा regmap *syscon_regmap;
	काष्ठा soc_device *soc_dev;
	काष्ठा soc_device_attribute *soc_dev_attr;
	काष्ठा device_node *np = pdev->dev.of_node;
	पूर्णांक ret;

	syscon_regmap = syscon_regmap_lookup_by_phandle(np, "regmap");
	अगर (IS_ERR(syscon_regmap))
		वापस PTR_ERR(syscon_regmap);

	soc_dev_attr = kzalloc(माप(*soc_dev_attr), GFP_KERNEL);
	अगर (!soc_dev_attr)
		वापस -ENOMEM;

	ret = of_property_पढ़ो_string(np, "compatible",
				      &soc_dev_attr->soc_id);
	अगर (ret)
		वापस -EINVAL;

	soc_dev_attr->machine = "RealView";
	soc_dev_attr->family = "Versatile";
	soc_dev_attr->custom_attr_group = realview_groups[0];
	soc_dev = soc_device_रेजिस्टर(soc_dev_attr);
	अगर (IS_ERR(soc_dev)) अणु
		kमुक्त(soc_dev_attr);
		वापस -ENODEV;
	पूर्ण
	ret = regmap_पढ़ो(syscon_regmap, REALVIEW_SYS_ID_OFFSET,
			  &realview_coreid);
	अगर (ret)
		वापस -ENODEV;

	dev_info(&pdev->dev, "RealView Syscon Core ID: 0x%08x, HBI-%03x\n",
		 realview_coreid,
		 ((realview_coreid >> 16) & 0xfff));
	/* FIXME: add attributes क्रम SoC to sysfs */
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver realview_soc_driver = अणु
	.probe = realview_soc_probe,
	.driver = अणु
		.name = "realview-soc",
		.of_match_table = realview_soc_of_match,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(realview_soc_driver);
