<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2020 MediaTek Inc.
 *
 * Author: ChiYuan Huang <cy_huang@richtek.com>
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/usb/tcpm.h>

#समावेश "tcpci.h"

#घोषणा MT6360_REG_VCONNCTRL1	0x8C
#घोषणा MT6360_REG_MODECTRL2	0x8F
#घोषणा MT6360_REG_SWRESET	0xA0
#घोषणा MT6360_REG_DEBCTRL1	0xA1
#घोषणा MT6360_REG_DRPCTRL1	0xA2
#घोषणा MT6360_REG_DRPCTRL2	0xA3
#घोषणा MT6360_REG_I2CTORST	0xBF
#घोषणा MT6360_REG_RXCTRL2	0xCF
#घोषणा MT6360_REG_CTDCTRL2	0xEC

/* MT6360_REG_VCONNCTRL1 */
#घोषणा MT6360_VCONNCL_ENABLE	BIT(0)
/* MT6360_REG_RXCTRL2 */
#घोषणा MT6360_OPEN40M_ENABLE	BIT(7)
/* MT6360_REG_CTDCTRL2 */
#घोषणा MT6360_RPONESHOT_ENABLE	BIT(6)

काष्ठा mt6360_tcpc_info अणु
	काष्ठा tcpci_data tdata;
	काष्ठा tcpci *tcpci;
	काष्ठा device *dev;
	पूर्णांक irq;
पूर्ण;

अटल अंतरभूत पूर्णांक mt6360_tcpc_पढ़ो16(काष्ठा regmap *regmap,
				     अचिन्हित पूर्णांक reg, u16 *val)
अणु
	वापस regmap_raw_पढ़ो(regmap, reg, val, माप(u16));
पूर्ण

अटल अंतरभूत पूर्णांक mt6360_tcpc_ग_लिखो16(काष्ठा regmap *regmap,
				      अचिन्हित पूर्णांक reg, u16 val)
अणु
	वापस regmap_raw_ग_लिखो(regmap, reg, &val, माप(u16));
पूर्ण

अटल पूर्णांक mt6360_tcpc_init(काष्ठा tcpci *tcpci, काष्ठा tcpci_data *tdata)
अणु
	काष्ठा regmap *regmap = tdata->regmap;
	पूर्णांक ret;

	ret = regmap_ग_लिखो(regmap, MT6360_REG_SWRESET, 0x01);
	अगर (ret)
		वापस ret;

	/* after reset command, रुको 1~2ms to रुको IC action */
	usleep_range(1000, 2000);

	/* ग_लिखो all alert to masked */
	ret = mt6360_tcpc_ग_लिखो16(regmap, TCPC_ALERT_MASK, 0);
	अगर (ret)
		वापस ret;

	/* config I2C समयout reset enable , and समयout to 200ms */
	ret = regmap_ग_लिखो(regmap, MT6360_REG_I2CTORST, 0x8F);
	अगर (ret)
		वापस ret;

	/* config CC Detect Debounce : 26.7*val us */
	ret = regmap_ग_लिखो(regmap, MT6360_REG_DEBCTRL1, 0x10);
	अगर (ret)
		वापस ret;

	/* DRP Toggle Cycle : 51.2 + 6.4*val ms */
	ret = regmap_ग_लिखो(regmap, MT6360_REG_DRPCTRL1, 4);
	अगर (ret)
		वापस ret;

	/* DRP Duyt Ctrl : dcSRC: /1024 */
	ret = mt6360_tcpc_ग_लिखो16(regmap, MT6360_REG_DRPCTRL2, 330);
	अगर (ret)
		वापस ret;

	/* Enable VCONN Current Limit function */
	ret = regmap_update_bits(regmap, MT6360_REG_VCONNCTRL1, MT6360_VCONNCL_ENABLE,
				 MT6360_VCONNCL_ENABLE);
	अगर (ret)
		वापस ret;

	/* Enable cc खोलो 40ms when pmic send vsysuv संकेत */
	ret = regmap_update_bits(regmap, MT6360_REG_RXCTRL2, MT6360_OPEN40M_ENABLE,
				 MT6360_OPEN40M_ENABLE);
	अगर (ret)
		वापस ret;

	/* Enable Rpdet oneshot detection */
	ret = regmap_update_bits(regmap, MT6360_REG_CTDCTRL2, MT6360_RPONESHOT_ENABLE,
				 MT6360_RPONESHOT_ENABLE);
	अगर (ret)
		वापस ret;

	/* Set shipping mode off, AUTOIDLE on */
	वापस regmap_ग_लिखो(regmap, MT6360_REG_MODECTRL2, 0x7A);
पूर्ण

अटल irqवापस_t mt6360_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mt6360_tcpc_info *mti = dev_id;

	वापस tcpci_irq(mti->tcpci);
पूर्ण

अटल पूर्णांक mt6360_tcpc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mt6360_tcpc_info *mti;
	पूर्णांक ret;

	mti = devm_kzalloc(&pdev->dev, माप(*mti), GFP_KERNEL);
	अगर (!mti)
		वापस -ENOMEM;

	mti->dev = &pdev->dev;

	mti->tdata.regmap = dev_get_regmap(pdev->dev.parent, शून्य);
	अगर (!mti->tdata.regmap) अणु
		dev_err(&pdev->dev, "Failed to get parent regmap\n");
		वापस -ENODEV;
	पूर्ण

	mti->irq = platक्रमm_get_irq_byname(pdev, "PD_IRQB");
	अगर (mti->irq < 0)
		वापस mti->irq;

	mti->tdata.init = mt6360_tcpc_init;
	mti->tcpci = tcpci_रेजिस्टर_port(&pdev->dev, &mti->tdata);
	अगर (IS_ERR(mti->tcpci)) अणु
		dev_err(&pdev->dev, "Failed to register tcpci port\n");
		वापस PTR_ERR(mti->tcpci);
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(mti->dev, mti->irq, शून्य, mt6360_irq, IRQF_ONESHOT,
					dev_name(&pdev->dev), mti);
	अगर (ret) अणु
		dev_err(mti->dev, "Failed to register irq\n");
		tcpci_unरेजिस्टर_port(mti->tcpci);
		वापस ret;
	पूर्ण

	device_init_wakeup(&pdev->dev, true);
	platक्रमm_set_drvdata(pdev, mti);

	वापस 0;
पूर्ण

अटल पूर्णांक mt6360_tcpc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mt6360_tcpc_info *mti = platक्रमm_get_drvdata(pdev);

	disable_irq(mti->irq);
	tcpci_unरेजिस्टर_port(mti->tcpci);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused mt6360_tcpc_suspend(काष्ठा device *dev)
अणु
	काष्ठा mt6360_tcpc_info *mti = dev_get_drvdata(dev);

	अगर (device_may_wakeup(dev))
		enable_irq_wake(mti->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused mt6360_tcpc_resume(काष्ठा device *dev)
अणु
	काष्ठा mt6360_tcpc_info *mti = dev_get_drvdata(dev);

	अगर (device_may_wakeup(dev))
		disable_irq_wake(mti->irq);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(mt6360_tcpc_pm_ops, mt6360_tcpc_suspend, mt6360_tcpc_resume);

अटल स्थिर काष्ठा of_device_id __maybe_unused mt6360_tcpc_of_id[] = अणु
	अणु .compatible = "mediatek,mt6360-tcpc", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mt6360_tcpc_of_id);

अटल काष्ठा platक्रमm_driver mt6360_tcpc_driver = अणु
	.driver = अणु
		.name = "mt6360-tcpc",
		.pm = &mt6360_tcpc_pm_ops,
		.of_match_table = mt6360_tcpc_of_id,
	पूर्ण,
	.probe = mt6360_tcpc_probe,
	.हटाओ = mt6360_tcpc_हटाओ,
पूर्ण;
module_platक्रमm_driver(mt6360_tcpc_driver);

MODULE_AUTHOR("ChiYuan Huang <cy_huang@richtek.com>");
MODULE_DESCRIPTION("MT6360 USB Type-C Port Controller Interface Driver");
MODULE_LICENSE("GPL v2");
