<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2020 BAIKAL ELECTRONICS, JSC
 *
 * Authors:
 *   Serge Semin <Sergey.Semin@baikalelectronics.ru>
 *
 * Baikal-T1 CM2 L2-cache Control Block driver.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/types.h>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/of.h>

#घोषणा L2_CTL_REG			0x028
#घोषणा L2_CTL_DATA_STALL_FLD		0
#घोषणा L2_CTL_DATA_STALL_MASK		GENMASK(1, L2_CTL_DATA_STALL_FLD)
#घोषणा L2_CTL_TAG_STALL_FLD		2
#घोषणा L2_CTL_TAG_STALL_MASK		GENMASK(3, L2_CTL_TAG_STALL_FLD)
#घोषणा L2_CTL_WS_STALL_FLD		4
#घोषणा L2_CTL_WS_STALL_MASK		GENMASK(5, L2_CTL_WS_STALL_FLD)
#घोषणा L2_CTL_SET_CLKRATIO		BIT(13)
#घोषणा L2_CTL_CLKRATIO_LOCK		BIT(31)

#घोषणा L2_CTL_STALL_MIN		0
#घोषणा L2_CTL_STALL_MAX		3
#घोषणा L2_CTL_STALL_SET_DELAY_US	1
#घोषणा L2_CTL_STALL_SET_TOUT_US	1000

/*
 * काष्ठा l2_ctl - Baikal-T1 L2 Control block निजी data.
 * @dev: Poपूर्णांकer to the device काष्ठाure.
 * @sys_regs: Baikal-T1 System Controller रेजिस्टरs map.
 */
काष्ठा l2_ctl अणु
	काष्ठा device *dev;

	काष्ठा regmap *sys_regs;
पूर्ण;

/*
 * क्रमागत l2_ctl_stall - Baikal-T1 L2-cache-RAM stall identअगरier.
 * @L2_WSSTALL: Way-select latency.
 * @L2_TAGSTALL: Tag latency.
 * @L2_DATASTALL: Data latency.
 */
क्रमागत l2_ctl_stall अणु
	L2_WS_STALL,
	L2_TAG_STALL,
	L2_DATA_STALL
पूर्ण;

/*
 * काष्ठा l2_ctl_device_attribute - Baikal-T1 L2-cache device attribute.
 * @dev_attr: Actual sysfs device attribute.
 * @id: L2-cache stall field identअगरier.
 */
काष्ठा l2_ctl_device_attribute अणु
	काष्ठा device_attribute dev_attr;
	क्रमागत l2_ctl_stall id;
पूर्ण;

#घोषणा to_l2_ctl_dev_attr(_dev_attr) \
	container_of(_dev_attr, काष्ठा l2_ctl_device_attribute, dev_attr)

#घोषणा L2_CTL_ATTR_RW(_name, _prefix, _id) \
	काष्ठा l2_ctl_device_attribute l2_ctl_attr_##_name = \
		अणु __ATTR(_name, 0644, _prefix##_show, _prefix##_store),	_id पूर्ण

अटल पूर्णांक l2_ctl_get_latency(काष्ठा l2_ctl *l2, क्रमागत l2_ctl_stall id, u32 *val)
अणु
	u32 data = 0;
	पूर्णांक ret;

	ret = regmap_पढ़ो(l2->sys_regs, L2_CTL_REG, &data);
	अगर (ret)
		वापस ret;

	चयन (id) अणु
	हाल L2_WS_STALL:
		*val = FIELD_GET(L2_CTL_WS_STALL_MASK, data);
		अवरोध;
	हाल L2_TAG_STALL:
		*val = FIELD_GET(L2_CTL_TAG_STALL_MASK, data);
		अवरोध;
	हाल L2_DATA_STALL:
		*val = FIELD_GET(L2_CTL_DATA_STALL_MASK, data);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक l2_ctl_set_latency(काष्ठा l2_ctl *l2, क्रमागत l2_ctl_stall id, u32 val)
अणु
	u32 mask = 0, data = 0;
	पूर्णांक ret;

	val = clamp_val(val, L2_CTL_STALL_MIN, L2_CTL_STALL_MAX);

	चयन (id) अणु
	हाल L2_WS_STALL:
		data = FIELD_PREP(L2_CTL_WS_STALL_MASK, val);
		mask = L2_CTL_WS_STALL_MASK;
		अवरोध;
	हाल L2_TAG_STALL:
		data = FIELD_PREP(L2_CTL_TAG_STALL_MASK, val);
		mask = L2_CTL_TAG_STALL_MASK;
		अवरोध;
	हाल L2_DATA_STALL:
		data = FIELD_PREP(L2_CTL_DATA_STALL_MASK, val);
		mask = L2_CTL_DATA_STALL_MASK;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	data |= L2_CTL_SET_CLKRATIO;
	mask |= L2_CTL_SET_CLKRATIO;

	ret = regmap_update_bits(l2->sys_regs, L2_CTL_REG, mask, data);
	अगर (ret)
		वापस ret;

	वापस regmap_पढ़ो_poll_समयout(l2->sys_regs, L2_CTL_REG, data,
					data & L2_CTL_CLKRATIO_LOCK,
					L2_CTL_STALL_SET_DELAY_US,
					L2_CTL_STALL_SET_TOUT_US);
पूर्ण

अटल व्योम l2_ctl_clear_data(व्योम *data)
अणु
	काष्ठा l2_ctl *l2 = data;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(l2->dev);

	platक्रमm_set_drvdata(pdev, शून्य);
पूर्ण

अटल काष्ठा l2_ctl *l2_ctl_create_data(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा l2_ctl *l2;
	पूर्णांक ret;

	l2 = devm_kzalloc(dev, माप(*l2), GFP_KERNEL);
	अगर (!l2)
		वापस ERR_PTR(-ENOMEM);

	ret = devm_add_action(dev, l2_ctl_clear_data, l2);
	अगर (ret) अणु
		dev_err(dev, "Can't add L2 CTL data clear action\n");
		वापस ERR_PTR(ret);
	पूर्ण

	l2->dev = dev;
	platक्रमm_set_drvdata(pdev, l2);

	वापस l2;
पूर्ण

अटल पूर्णांक l2_ctl_find_sys_regs(काष्ठा l2_ctl *l2)
अणु
	l2->sys_regs = syscon_node_to_regmap(l2->dev->of_node->parent);
	अगर (IS_ERR(l2->sys_regs)) अणु
		dev_err(l2->dev, "Couldn't get L2 CTL register map\n");
		वापस PTR_ERR(l2->sys_regs);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक l2_ctl_of_parse_property(काष्ठा l2_ctl *l2, क्रमागत l2_ctl_stall id,
				    स्थिर अक्षर *propname)
अणु
	पूर्णांक ret = 0;
	u32 data;

	अगर (!of_property_पढ़ो_u32(l2->dev->of_node, propname, &data)) अणु
		ret = l2_ctl_set_latency(l2, id, data);
		अगर (ret)
			dev_err(l2->dev, "Invalid value of '%s'\n", propname);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक l2_ctl_of_parse(काष्ठा l2_ctl *l2)
अणु
	पूर्णांक ret;

	ret = l2_ctl_of_parse_property(l2, L2_WS_STALL, "baikal,l2-ws-latency");
	अगर (ret)
		वापस ret;

	ret = l2_ctl_of_parse_property(l2, L2_TAG_STALL, "baikal,l2-tag-latency");
	अगर (ret)
		वापस ret;

	वापस l2_ctl_of_parse_property(l2, L2_DATA_STALL,
					"baikal,l2-data-latency");
पूर्ण

अटल sमाप_प्रकार l2_ctl_latency_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   अक्षर *buf)
अणु
	काष्ठा l2_ctl_device_attribute *devattr = to_l2_ctl_dev_attr(attr);
	काष्ठा l2_ctl *l2 = dev_get_drvdata(dev);
	u32 data;
	पूर्णांक ret;

	ret = l2_ctl_get_latency(l2, devattr->id, &data);
	अगर (ret)
		वापस ret;

	वापस scnम_लिखो(buf, PAGE_SIZE, "%u\n", data);
पूर्ण

अटल sमाप_प्रकार l2_ctl_latency_store(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा l2_ctl_device_attribute *devattr = to_l2_ctl_dev_attr(attr);
	काष्ठा l2_ctl *l2 = dev_get_drvdata(dev);
	u32 data;
	पूर्णांक ret;

	अगर (kstrtouपूर्णांक(buf, 0, &data) < 0)
		वापस -EINVAL;

	ret = l2_ctl_set_latency(l2, devattr->id, data);
	अगर (ret)
		वापस ret;

	वापस count;
पूर्ण

अटल L2_CTL_ATTR_RW(l2_ws_latency, l2_ctl_latency, L2_WS_STALL);
अटल L2_CTL_ATTR_RW(l2_tag_latency, l2_ctl_latency, L2_TAG_STALL);
अटल L2_CTL_ATTR_RW(l2_data_latency, l2_ctl_latency, L2_DATA_STALL);

अटल काष्ठा attribute *l2_ctl_sysfs_attrs[] = अणु
	&l2_ctl_attr_l2_ws_latency.dev_attr.attr,
	&l2_ctl_attr_l2_tag_latency.dev_attr.attr,
	&l2_ctl_attr_l2_data_latency.dev_attr.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(l2_ctl_sysfs);

अटल व्योम l2_ctl_हटाओ_sysfs(व्योम *data)
अणु
	काष्ठा l2_ctl *l2 = data;

	device_हटाओ_groups(l2->dev, l2_ctl_sysfs_groups);
पूर्ण

अटल पूर्णांक l2_ctl_init_sysfs(काष्ठा l2_ctl *l2)
अणु
	पूर्णांक ret;

	ret = device_add_groups(l2->dev, l2_ctl_sysfs_groups);
	अगर (ret) अणु
		dev_err(l2->dev, "Failed to create L2 CTL sysfs nodes\n");
		वापस ret;
	पूर्ण

	ret = devm_add_action_or_reset(l2->dev, l2_ctl_हटाओ_sysfs, l2);
	अगर (ret)
		dev_err(l2->dev, "Can't add L2 CTL sysfs remove action\n");

	वापस ret;
पूर्ण

अटल पूर्णांक l2_ctl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा l2_ctl *l2;
	पूर्णांक ret;

	l2 = l2_ctl_create_data(pdev);
	अगर (IS_ERR(l2))
		वापस PTR_ERR(l2);

	ret = l2_ctl_find_sys_regs(l2);
	अगर (ret)
		वापस ret;

	ret = l2_ctl_of_parse(l2);
	अगर (ret)
		वापस ret;

	ret = l2_ctl_init_sysfs(l2);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id l2_ctl_of_match[] = अणु
	अणु .compatible = "baikal,bt1-l2-ctl" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, l2_ctl_of_match);

अटल काष्ठा platक्रमm_driver l2_ctl_driver = अणु
	.probe = l2_ctl_probe,
	.driver = अणु
		.name = "bt1-l2-ctl",
		.of_match_table = l2_ctl_of_match
	पूर्ण
पूर्ण;
module_platक्रमm_driver(l2_ctl_driver);

MODULE_AUTHOR("Serge Semin <Sergey.Semin@baikalelectronics.ru>");
MODULE_DESCRIPTION("Baikal-T1 L2-cache driver");
MODULE_LICENSE("GPL v2");
