<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// IOMapped CAN bus driver क्रम Bosch M_CAN controller
// Copyright (C) 2014 Freescale Semiconductor, Inc.
//	Dong Aisheng <b29396@मुक्तscale.com>
//
// Copyright (C) 2018-19 Texas Instruments Incorporated - http://www.ti.com/

#समावेश <linux/platक्रमm_device.h>

#समावेश "m_can.h"

काष्ठा m_can_plat_priv अणु
	काष्ठा m_can_classdev cdev;

	व्योम __iomem *base;
	व्योम __iomem *mram_base;
पूर्ण;

अटल अंतरभूत काष्ठा m_can_plat_priv *cdev_to_priv(काष्ठा m_can_classdev *cdev)
अणु
	वापस container_of(cdev, काष्ठा m_can_plat_priv, cdev);
पूर्ण

अटल u32 iomap_पढ़ो_reg(काष्ठा m_can_classdev *cdev, पूर्णांक reg)
अणु
	काष्ठा m_can_plat_priv *priv = cdev_to_priv(cdev);

	वापस पढ़ोl(priv->base + reg);
पूर्ण

अटल u32 iomap_पढ़ो_fअगरo(काष्ठा m_can_classdev *cdev, पूर्णांक offset)
अणु
	काष्ठा m_can_plat_priv *priv = cdev_to_priv(cdev);

	वापस पढ़ोl(priv->mram_base + offset);
पूर्ण

अटल पूर्णांक iomap_ग_लिखो_reg(काष्ठा m_can_classdev *cdev, पूर्णांक reg, पूर्णांक val)
अणु
	काष्ठा m_can_plat_priv *priv = cdev_to_priv(cdev);

	ग_लिखोl(val, priv->base + reg);

	वापस 0;
पूर्ण

अटल पूर्णांक iomap_ग_लिखो_fअगरo(काष्ठा m_can_classdev *cdev, पूर्णांक offset, पूर्णांक val)
अणु
	काष्ठा m_can_plat_priv *priv = cdev_to_priv(cdev);

	ग_लिखोl(val, priv->mram_base + offset);

	वापस 0;
पूर्ण

अटल काष्ठा m_can_ops m_can_plat_ops = अणु
	.पढ़ो_reg = iomap_पढ़ो_reg,
	.ग_लिखो_reg = iomap_ग_लिखो_reg,
	.ग_लिखो_fअगरo = iomap_ग_लिखो_fअगरo,
	.पढ़ो_fअगरo = iomap_पढ़ो_fअगरo,
पूर्ण;

अटल पूर्णांक m_can_plat_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा m_can_classdev *mcan_class;
	काष्ठा m_can_plat_priv *priv;
	काष्ठा resource *res;
	व्योम __iomem *addr;
	व्योम __iomem *mram_addr;
	पूर्णांक irq, ret = 0;

	mcan_class = m_can_class_allocate_dev(&pdev->dev,
					      माप(काष्ठा m_can_plat_priv));
	अगर (!mcan_class)
		वापस -ENOMEM;

	priv = cdev_to_priv(mcan_class);

	ret = m_can_class_get_घड़ीs(mcan_class);
	अगर (ret)
		जाओ probe_fail;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "m_can");
	addr = devm_ioremap_resource(&pdev->dev, res);
	irq = platक्रमm_get_irq_byname(pdev, "int0");
	अगर (IS_ERR(addr) || irq < 0) अणु
		ret = -EINVAL;
		जाओ probe_fail;
	पूर्ण

	/* message ram could be shared */
	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "message_ram");
	अगर (!res) अणु
		ret = -ENODEV;
		जाओ probe_fail;
	पूर्ण

	mram_addr = devm_ioremap(&pdev->dev, res->start, resource_size(res));
	अगर (!mram_addr) अणु
		ret = -ENOMEM;
		जाओ probe_fail;
	पूर्ण

	priv->base = addr;
	priv->mram_base = mram_addr;

	mcan_class->net->irq = irq;
	mcan_class->pm_घड़ी_support = 1;
	mcan_class->can.घड़ी.freq = clk_get_rate(mcan_class->cclk);
	mcan_class->dev = &pdev->dev;

	mcan_class->ops = &m_can_plat_ops;

	mcan_class->is_peripheral = false;

	platक्रमm_set_drvdata(pdev, mcan_class);

	m_can_init_ram(mcan_class);

	pm_runसमय_enable(mcan_class->dev);
	ret = m_can_class_रेजिस्टर(mcan_class);
	अगर (ret)
		जाओ out_runसमय_disable;

	वापस ret;

out_runसमय_disable:
	pm_runसमय_disable(mcan_class->dev);
probe_fail:
	m_can_class_मुक्त_dev(mcan_class->net);
	वापस ret;
पूर्ण

अटल __maybe_unused पूर्णांक m_can_suspend(काष्ठा device *dev)
अणु
	वापस m_can_class_suspend(dev);
पूर्ण

अटल __maybe_unused पूर्णांक m_can_resume(काष्ठा device *dev)
अणु
	वापस m_can_class_resume(dev);
पूर्ण

अटल पूर्णांक m_can_plat_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा m_can_plat_priv *priv = platक्रमm_get_drvdata(pdev);
	काष्ठा m_can_classdev *mcan_class = &priv->cdev;

	m_can_class_unरेजिस्टर(mcan_class);

	m_can_class_मुक्त_dev(mcan_class->net);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused m_can_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा m_can_plat_priv *priv = dev_get_drvdata(dev);
	काष्ठा m_can_classdev *mcan_class = &priv->cdev;

	clk_disable_unprepare(mcan_class->cclk);
	clk_disable_unprepare(mcan_class->hclk);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused m_can_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा m_can_plat_priv *priv = dev_get_drvdata(dev);
	काष्ठा m_can_classdev *mcan_class = &priv->cdev;
	पूर्णांक err;

	err = clk_prepare_enable(mcan_class->hclk);
	अगर (err)
		वापस err;

	err = clk_prepare_enable(mcan_class->cclk);
	अगर (err)
		clk_disable_unprepare(mcan_class->hclk);

	वापस err;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops m_can_pmops = अणु
	SET_RUNTIME_PM_OPS(m_can_runसमय_suspend,
			   m_can_runसमय_resume, शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(m_can_suspend, m_can_resume)
पूर्ण;

अटल स्थिर काष्ठा of_device_id m_can_of_table[] = अणु
	अणु .compatible = "bosch,m_can", .data = शून्य पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, m_can_of_table);

अटल काष्ठा platक्रमm_driver m_can_plat_driver = अणु
	.driver = अणु
		.name = KBUILD_MODNAME,
		.of_match_table = m_can_of_table,
		.pm     = &m_can_pmops,
	पूर्ण,
	.probe = m_can_plat_probe,
	.हटाओ = m_can_plat_हटाओ,
पूर्ण;

module_platक्रमm_driver(m_can_plat_driver);

MODULE_AUTHOR("Dong Aisheng <b29396@freescale.com>");
MODULE_AUTHOR("Dan Murphy <dmurphy@ti.com>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("M_CAN driver for IO Mapped Bosch controllers");
