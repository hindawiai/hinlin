<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2020 BAIKAL ELECTRONICS, JSC
 *
 * Authors:
 *   Serge Semin <Sergey.Semin@baikalelectronics.ru>
 *
 * Baikal-T1 AXI-bus driver
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/device.h>
#समावेश <linux/atomic.h>
#समावेश <linux/regmap.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/nmi.h>
#समावेश <linux/of.h>
#समावेश <linux/clk.h>
#समावेश <linux/reset.h>
#समावेश <linux/sysfs.h>

#घोषणा BT1_AXI_WERRL			0x110
#घोषणा BT1_AXI_WERRH			0x114
#घोषणा BT1_AXI_WERRH_TYPE		BIT(23)
#घोषणा BT1_AXI_WERRH_ADDR_FLD		24
#घोषणा BT1_AXI_WERRH_ADDR_MASK		GENMASK(31, BT1_AXI_WERRH_ADDR_FLD)

/*
 * काष्ठा bt1_axi - Baikal-T1 AXI-bus निजी data
 * @dev: Poपूर्णांकer to the device काष्ठाure.
 * @qos_regs: AXI Interconnect QoS tuning रेजिस्टरs.
 * @sys_regs: Baikal-T1 System Controller रेजिस्टरs map.
 * @irq: Errors IRQ number.
 * @aclk: AXI reference घड़ी.
 * @arst: AXI Interconnect reset line.
 * @count: Number of errors detected.
 */
काष्ठा bt1_axi अणु
	काष्ठा device *dev;

	व्योम __iomem *qos_regs;
	काष्ठा regmap *sys_regs;
	पूर्णांक irq;

	काष्ठा clk *aclk;

	काष्ठा reset_control *arst;

	atomic_t count;
पूर्ण;

अटल irqवापस_t bt1_axi_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा bt1_axi *axi = data;
	u32 low = 0, high = 0;

	regmap_पढ़ो(axi->sys_regs, BT1_AXI_WERRL, &low);
	regmap_पढ़ो(axi->sys_regs, BT1_AXI_WERRH, &high);

	dev_crit_ratelimited(axi->dev,
		"AXI-bus fault %d: %s at 0x%x%08x\n",
		atomic_inc_वापस(&axi->count),
		high & BT1_AXI_WERRH_TYPE ? "no slave" : "slave protocol error",
		high, low);

	/*
	 * Prपूर्णांक backtrace on each CPU. This might be poपूर्णांकless अगर the fault
	 * has happened on the same CPU as the IRQ handler is executed or
	 * the other core proceeded further execution despite the error.
	 * But अगर it's not, by looking at the trace we would get straight to
	 * the cause of the problem.
	 */
	trigger_all_cpu_backtrace();

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम bt1_axi_clear_data(व्योम *data)
अणु
	काष्ठा bt1_axi *axi = data;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(axi->dev);

	platक्रमm_set_drvdata(pdev, शून्य);
पूर्ण

अटल काष्ठा bt1_axi *bt1_axi_create_data(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा bt1_axi *axi;
	पूर्णांक ret;

	axi = devm_kzalloc(dev, माप(*axi), GFP_KERNEL);
	अगर (!axi)
		वापस ERR_PTR(-ENOMEM);

	ret = devm_add_action(dev, bt1_axi_clear_data, axi);
	अगर (ret) अणु
		dev_err(dev, "Can't add AXI EHB data clear action\n");
		वापस ERR_PTR(ret);
	पूर्ण

	axi->dev = dev;
	atomic_set(&axi->count, 0);
	platक्रमm_set_drvdata(pdev, axi);

	वापस axi;
पूर्ण

अटल पूर्णांक bt1_axi_request_regs(काष्ठा bt1_axi *axi)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(axi->dev);
	काष्ठा device *dev = axi->dev;

	axi->sys_regs = syscon_regmap_lookup_by_phandle(dev->of_node, "syscon");
	अगर (IS_ERR(axi->sys_regs)) अणु
		dev_err(dev, "Couldn't find syscon registers\n");
		वापस PTR_ERR(axi->sys_regs);
	पूर्ण

	axi->qos_regs = devm_platक्रमm_ioremap_resource_byname(pdev, "qos");
	अगर (IS_ERR(axi->qos_regs))
		dev_err(dev, "Couldn't map AXI-bus QoS registers\n");

	वापस PTR_ERR_OR_ZERO(axi->qos_regs);
पूर्ण

अटल पूर्णांक bt1_axi_request_rst(काष्ठा bt1_axi *axi)
अणु
	पूर्णांक ret;

	axi->arst = devm_reset_control_get_optional_exclusive(axi->dev, "arst");
	अगर (IS_ERR(axi->arst)) अणु
		dev_warn(axi->dev, "Couldn't get reset control line\n");
		वापस PTR_ERR(axi->arst);
	पूर्ण

	ret = reset_control_deनिश्चित(axi->arst);
	अगर (ret)
		dev_err(axi->dev, "Failed to deassert the reset line\n");

	वापस ret;
पूर्ण

अटल व्योम bt1_axi_disable_clk(व्योम *data)
अणु
	काष्ठा bt1_axi *axi = data;

	clk_disable_unprepare(axi->aclk);
पूर्ण

अटल पूर्णांक bt1_axi_request_clk(काष्ठा bt1_axi *axi)
अणु
	पूर्णांक ret;

	axi->aclk = devm_clk_get(axi->dev, "aclk");
	अगर (IS_ERR(axi->aclk)) अणु
		dev_err(axi->dev, "Couldn't get AXI Interconnect clock\n");
		वापस PTR_ERR(axi->aclk);
	पूर्ण

	ret = clk_prepare_enable(axi->aclk);
	अगर (ret) अणु
		dev_err(axi->dev, "Couldn't enable the AXI clock\n");
		वापस ret;
	पूर्ण

	ret = devm_add_action_or_reset(axi->dev, bt1_axi_disable_clk, axi);
	अगर (ret)
		dev_err(axi->dev, "Can't add AXI clock disable action\n");

	वापस ret;
पूर्ण

अटल पूर्णांक bt1_axi_request_irq(काष्ठा bt1_axi *axi)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(axi->dev);
	पूर्णांक ret;

	axi->irq = platक्रमm_get_irq(pdev, 0);
	अगर (axi->irq < 0)
		वापस axi->irq;

	ret = devm_request_irq(axi->dev, axi->irq, bt1_axi_isr, IRQF_SHARED,
			       "bt1-axi", axi);
	अगर (ret)
		dev_err(axi->dev, "Couldn't request AXI EHB IRQ\n");

	वापस ret;
पूर्ण

अटल sमाप_प्रकार count_show(काष्ठा device *dev,
			  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा bt1_axi *axi = dev_get_drvdata(dev);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", atomic_पढ़ो(&axi->count));
पूर्ण
अटल DEVICE_ATTR_RO(count);

अटल sमाप_प्रकार inject_error_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "Error injection: bus unaligned\n");
पूर्ण

अटल sमाप_प्रकार inject_error_store(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *data, माप_प्रकार count)
अणु
	काष्ठा bt1_axi *axi = dev_get_drvdata(dev);

	/*
	 * Perक्रमming unaligned पढ़ो from the memory will cause the CM2 bus
	 * error जबतक unaligned writing - the AXI bus ग_लिखो error handled
	 * by this driver.
	 */
	अगर (sysfs_streq(data, "bus"))
		पढ़ोb(axi->qos_regs);
	अन्यथा अगर (sysfs_streq(data, "unaligned"))
		ग_लिखोb(0, axi->qos_regs);
	अन्यथा
		वापस -EINVAL;

	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(inject_error);

अटल काष्ठा attribute *bt1_axi_sysfs_attrs[] = अणु
	&dev_attr_count.attr,
	&dev_attr_inject_error.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(bt1_axi_sysfs);

अटल व्योम bt1_axi_हटाओ_sysfs(व्योम *data)
अणु
	काष्ठा bt1_axi *axi = data;

	device_हटाओ_groups(axi->dev, bt1_axi_sysfs_groups);
पूर्ण

अटल पूर्णांक bt1_axi_init_sysfs(काष्ठा bt1_axi *axi)
अणु
	पूर्णांक ret;

	ret = device_add_groups(axi->dev, bt1_axi_sysfs_groups);
	अगर (ret) अणु
		dev_err(axi->dev, "Failed to add sysfs files group\n");
		वापस ret;
	पूर्ण

	ret = devm_add_action_or_reset(axi->dev, bt1_axi_हटाओ_sysfs, axi);
	अगर (ret)
		dev_err(axi->dev, "Can't add AXI EHB sysfs remove action\n");

	वापस ret;
पूर्ण

अटल पूर्णांक bt1_axi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा bt1_axi *axi;
	पूर्णांक ret;

	axi = bt1_axi_create_data(pdev);
	अगर (IS_ERR(axi))
		वापस PTR_ERR(axi);

	ret = bt1_axi_request_regs(axi);
	अगर (ret)
		वापस ret;

	ret = bt1_axi_request_rst(axi);
	अगर (ret)
		वापस ret;

	ret = bt1_axi_request_clk(axi);
	अगर (ret)
		वापस ret;

	ret = bt1_axi_request_irq(axi);
	अगर (ret)
		वापस ret;

	ret = bt1_axi_init_sysfs(axi);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id bt1_axi_of_match[] = अणु
	अणु .compatible = "baikal,bt1-axi" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, bt1_axi_of_match);

अटल काष्ठा platक्रमm_driver bt1_axi_driver = अणु
	.probe = bt1_axi_probe,
	.driver = अणु
		.name = "bt1-axi",
		.of_match_table = bt1_axi_of_match
	पूर्ण
पूर्ण;
module_platक्रमm_driver(bt1_axi_driver);

MODULE_AUTHOR("Serge Semin <Sergey.Semin@baikalelectronics.ru>");
MODULE_DESCRIPTION("Baikal-T1 AXI-bus driver");
MODULE_LICENSE("GPL v2");
