<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2020 BAIKAL ELECTRONICS, JSC
 *
 * Authors:
 *   Serge Semin <Sergey.Semin@baikalelectronics.ru>
 *
 * Baikal-T1 APB-bus driver
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/device.h>
#समावेश <linux/atomic.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/nmi.h>
#समावेश <linux/of.h>
#समावेश <linux/regmap.h>
#समावेश <linux/clk.h>
#समावेश <linux/reset.h>
#समावेश <linux/समय64.h>
#समावेश <linux/clk.h>
#समावेश <linux/sysfs.h>

#घोषणा APB_EHB_ISR			0x00
#घोषणा APB_EHB_ISR_PENDING		BIT(0)
#घोषणा APB_EHB_ISR_MASK		BIT(1)
#घोषणा APB_EHB_ADDR			0x04
#घोषणा APB_EHB_TIMEOUT			0x08

#घोषणा APB_EHB_TIMEOUT_MIN		0x000003FFU
#घोषणा APB_EHB_TIMEOUT_MAX		0xFFFFFFFFU

/*
 * काष्ठा bt1_apb - Baikal-T1 APB EHB निजी data
 * @dev: Poपूर्णांकer to the device काष्ठाure.
 * @regs: APB EHB रेजिस्टरs map.
 * @res: No-device error injection memory region.
 * @irq: Errors IRQ number.
 * @rate: APB-bus reference घड़ी rate.
 * @pclk: APB-reference घड़ी.
 * @prst: APB करोमुख्य reset line.
 * @count: Number of errors detected.
 */
काष्ठा bt1_apb अणु
	काष्ठा device *dev;

	काष्ठा regmap *regs;
	व्योम __iomem *res;
	पूर्णांक irq;

	अचिन्हित दीर्घ rate;
	काष्ठा clk *pclk;

	काष्ठा reset_control *prst;

	atomic_t count;
पूर्ण;

अटल स्थिर काष्ठा regmap_config bt1_apb_regmap_cfg = अणु
	.reg_bits = 32,
	.val_bits = 32,
	.reg_stride = 4,
	.max_रेजिस्टर = APB_EHB_TIMEOUT,
	.fast_io = true
पूर्ण;

अटल अंतरभूत अचिन्हित दीर्घ bt1_apb_n_to_समयout_us(काष्ठा bt1_apb *apb, u32 n)
अणु
	u64 समयout = (u64)n * USEC_PER_SEC;

	करो_भाग(समयout, apb->rate);

	वापस समयout;

पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ bt1_apb_समयout_to_n_us(काष्ठा bt1_apb *apb,
						    अचिन्हित दीर्घ समयout)
अणु
	u64 n = (u64)समयout * apb->rate;

	करो_भाग(n, USEC_PER_SEC);

	वापस n;

पूर्ण

अटल irqवापस_t bt1_apb_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा bt1_apb *apb = data;
	u32 addr = 0;

	regmap_पढ़ो(apb->regs, APB_EHB_ADDR, &addr);

	dev_crit_ratelimited(apb->dev,
		"APB-bus fault %d: Slave access timeout at 0x%08x\n",
		atomic_inc_वापस(&apb->count),
		addr);

	/*
	 * Prपूर्णांक backtrace on each CPU. This might be poपूर्णांकless अगर the fault
	 * has happened on the same CPU as the IRQ handler is executed or
	 * the other core proceeded further execution despite the error.
	 * But अगर it's not, by looking at the trace we would get straight to
	 * the cause of the problem.
	 */
	trigger_all_cpu_backtrace();

	regmap_update_bits(apb->regs, APB_EHB_ISR, APB_EHB_ISR_PENDING, 0);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम bt1_apb_clear_data(व्योम *data)
अणु
	काष्ठा bt1_apb *apb = data;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(apb->dev);

	platक्रमm_set_drvdata(pdev, शून्य);
पूर्ण

अटल काष्ठा bt1_apb *bt1_apb_create_data(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा bt1_apb *apb;
	पूर्णांक ret;

	apb = devm_kzalloc(dev, माप(*apb), GFP_KERNEL);
	अगर (!apb)
		वापस ERR_PTR(-ENOMEM);

	ret = devm_add_action(dev, bt1_apb_clear_data, apb);
	अगर (ret) अणु
		dev_err(dev, "Can't add APB EHB data clear action\n");
		वापस ERR_PTR(ret);
	पूर्ण

	apb->dev = dev;
	atomic_set(&apb->count, 0);
	platक्रमm_set_drvdata(pdev, apb);

	वापस apb;
पूर्ण

अटल पूर्णांक bt1_apb_request_regs(काष्ठा bt1_apb *apb)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(apb->dev);
	व्योम __iomem *regs;

	regs = devm_platक्रमm_ioremap_resource_byname(pdev, "ehb");
	अगर (IS_ERR(regs)) अणु
		dev_err(apb->dev, "Couldn't map APB EHB registers\n");
		वापस PTR_ERR(regs);
	पूर्ण

	apb->regs = devm_regmap_init_mmio(apb->dev, regs, &bt1_apb_regmap_cfg);
	अगर (IS_ERR(apb->regs)) अणु
		dev_err(apb->dev, "Couldn't create APB EHB regmap\n");
		वापस PTR_ERR(apb->regs);
	पूर्ण

	apb->res = devm_platक्रमm_ioremap_resource_byname(pdev, "nodev");
	अगर (IS_ERR(apb->res))
		dev_err(apb->dev, "Couldn't map reserved region\n");

	वापस PTR_ERR_OR_ZERO(apb->res);
पूर्ण

अटल पूर्णांक bt1_apb_request_rst(काष्ठा bt1_apb *apb)
अणु
	पूर्णांक ret;

	apb->prst = devm_reset_control_get_optional_exclusive(apb->dev, "prst");
	अगर (IS_ERR(apb->prst)) अणु
		dev_warn(apb->dev, "Couldn't get reset control line\n");
		वापस PTR_ERR(apb->prst);
	पूर्ण

	ret = reset_control_deनिश्चित(apb->prst);
	अगर (ret)
		dev_err(apb->dev, "Failed to deassert the reset line\n");

	वापस ret;
पूर्ण

अटल व्योम bt1_apb_disable_clk(व्योम *data)
अणु
	काष्ठा bt1_apb *apb = data;

	clk_disable_unprepare(apb->pclk);
पूर्ण

अटल पूर्णांक bt1_apb_request_clk(काष्ठा bt1_apb *apb)
अणु
	पूर्णांक ret;

	apb->pclk = devm_clk_get(apb->dev, "pclk");
	अगर (IS_ERR(apb->pclk)) अणु
		dev_err(apb->dev, "Couldn't get APB clock descriptor\n");
		वापस PTR_ERR(apb->pclk);
	पूर्ण

	ret = clk_prepare_enable(apb->pclk);
	अगर (ret) अणु
		dev_err(apb->dev, "Couldn't enable the APB clock\n");
		वापस ret;
	पूर्ण

	ret = devm_add_action_or_reset(apb->dev, bt1_apb_disable_clk, apb);
	अगर (ret) अणु
		dev_err(apb->dev, "Can't add APB EHB clocks disable action\n");
		वापस ret;
	पूर्ण

	apb->rate = clk_get_rate(apb->pclk);
	अगर (!apb->rate) अणु
		dev_err(apb->dev, "Invalid clock rate\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम bt1_apb_clear_irq(व्योम *data)
अणु
	काष्ठा bt1_apb *apb = data;

	regmap_update_bits(apb->regs, APB_EHB_ISR, APB_EHB_ISR_MASK, 0);
पूर्ण

अटल पूर्णांक bt1_apb_request_irq(काष्ठा bt1_apb *apb)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(apb->dev);
	पूर्णांक ret;

	apb->irq = platक्रमm_get_irq(pdev, 0);
	अगर (apb->irq < 0)
		वापस apb->irq;

	ret = devm_request_irq(apb->dev, apb->irq, bt1_apb_isr, IRQF_SHARED,
			       "bt1-apb", apb);
	अगर (ret) अणु
		dev_err(apb->dev, "Couldn't request APB EHB IRQ\n");
		वापस ret;
	पूर्ण

	ret = devm_add_action(apb->dev, bt1_apb_clear_irq, apb);
	अगर (ret) अणु
		dev_err(apb->dev, "Can't add APB EHB IRQs clear action\n");
		वापस ret;
	पूर्ण

	/* Unmask IRQ and clear it' pending flag. */
	regmap_update_bits(apb->regs, APB_EHB_ISR,
			   APB_EHB_ISR_PENDING | APB_EHB_ISR_MASK,
			   APB_EHB_ISR_MASK);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार count_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	काष्ठा bt1_apb *apb = dev_get_drvdata(dev);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", atomic_पढ़ो(&apb->count));
पूर्ण
अटल DEVICE_ATTR_RO(count);

अटल sमाप_प्रकार समयout_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	काष्ठा bt1_apb *apb = dev_get_drvdata(dev);
	अचिन्हित दीर्घ समयout;
	पूर्णांक ret;
	u32 n;

	ret = regmap_पढ़ो(apb->regs, APB_EHB_TIMEOUT, &n);
	अगर (ret)
		वापस ret;

	समयout = bt1_apb_n_to_समयout_us(apb, n);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%lu\n", समयout);
पूर्ण

अटल sमाप_प्रकार समयout_store(काष्ठा device *dev,
			     काष्ठा device_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा bt1_apb *apb = dev_get_drvdata(dev);
	अचिन्हित दीर्घ समयout;
	पूर्णांक ret;
	u32 n;

	अगर (kम_से_अदीर्घ(buf, 0, &समयout) < 0)
		वापस -EINVAL;

	n = bt1_apb_समयout_to_n_us(apb, समयout);
	n = clamp(n, APB_EHB_TIMEOUT_MIN, APB_EHB_TIMEOUT_MAX);

	ret = regmap_ग_लिखो(apb->regs, APB_EHB_TIMEOUT, n);

	वापस ret ?: count;
पूर्ण
अटल DEVICE_ATTR_RW(समयout);

अटल sमाप_प्रकार inject_error_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "Error injection: nodev irq\n");
पूर्ण

अटल sमाप_प्रकार inject_error_store(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *data, माप_प्रकार count)
अणु
	काष्ठा bt1_apb *apb = dev_get_drvdata(dev);

	/*
	 * Either dummy पढ़ो from the unmapped address in the APB IO area
	 * or manually set the IRQ status.
	 */
	अगर (sysfs_streq(data, "nodev"))
		पढ़ोl(apb->res);
	अन्यथा अगर (sysfs_streq(data, "irq"))
		regmap_update_bits(apb->regs, APB_EHB_ISR, APB_EHB_ISR_PENDING,
				   APB_EHB_ISR_PENDING);
	अन्यथा
		वापस -EINVAL;

	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(inject_error);

अटल काष्ठा attribute *bt1_apb_sysfs_attrs[] = अणु
	&dev_attr_count.attr,
	&dev_attr_समयout.attr,
	&dev_attr_inject_error.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(bt1_apb_sysfs);

अटल व्योम bt1_apb_हटाओ_sysfs(व्योम *data)
अणु
	काष्ठा bt1_apb *apb = data;

	device_हटाओ_groups(apb->dev, bt1_apb_sysfs_groups);
पूर्ण

अटल पूर्णांक bt1_apb_init_sysfs(काष्ठा bt1_apb *apb)
अणु
	पूर्णांक ret;

	ret = device_add_groups(apb->dev, bt1_apb_sysfs_groups);
	अगर (ret) अणु
		dev_err(apb->dev, "Failed to create EHB APB sysfs nodes\n");
		वापस ret;
	पूर्ण

	ret = devm_add_action_or_reset(apb->dev, bt1_apb_हटाओ_sysfs, apb);
	अगर (ret)
		dev_err(apb->dev, "Can't add APB EHB sysfs remove action\n");

	वापस ret;
पूर्ण

अटल पूर्णांक bt1_apb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा bt1_apb *apb;
	पूर्णांक ret;

	apb = bt1_apb_create_data(pdev);
	अगर (IS_ERR(apb))
		वापस PTR_ERR(apb);

	ret = bt1_apb_request_regs(apb);
	अगर (ret)
		वापस ret;

	ret = bt1_apb_request_rst(apb);
	अगर (ret)
		वापस ret;

	ret = bt1_apb_request_clk(apb);
	अगर (ret)
		वापस ret;

	ret = bt1_apb_request_irq(apb);
	अगर (ret)
		वापस ret;

	ret = bt1_apb_init_sysfs(apb);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id bt1_apb_of_match[] = अणु
	अणु .compatible = "baikal,bt1-apb" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, bt1_apb_of_match);

अटल काष्ठा platक्रमm_driver bt1_apb_driver = अणु
	.probe = bt1_apb_probe,
	.driver = अणु
		.name = "bt1-apb",
		.of_match_table = bt1_apb_of_match
	पूर्ण
पूर्ण;
module_platक्रमm_driver(bt1_apb_driver);

MODULE_AUTHOR("Serge Semin <Sergey.Semin@baikalelectronics.ru>");
MODULE_DESCRIPTION("Baikal-T1 APB-bus driver");
MODULE_LICENSE("GPL v2");
