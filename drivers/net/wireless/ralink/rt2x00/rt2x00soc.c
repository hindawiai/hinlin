<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
	Copyright (C) 2004 - 2009 Ivo van Doorn <IvDoorn@gmail.com>
	Copyright (C) 2004 - 2009 Felix Fietkau <nbd@खोलोwrt.org>
	<http://rt2x00.serialmonkey.com>

 */

/*
	Module: rt2x00soc
	Abstract: rt2x00 generic soc device routines.
 */

#समावेश <linux/bug.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश "rt2x00.h"
#समावेश "rt2x00soc.h"

अटल व्योम rt2x00soc_मुक्त_reg(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	kमुक्त(rt2x00dev->rf);
	rt2x00dev->rf = शून्य;

	kमुक्त(rt2x00dev->eeprom);
	rt2x00dev->eeprom = शून्य;

	iounmap(rt2x00dev->csr.base);
पूर्ण

अटल पूर्णांक rt2x00soc_alloc_reg(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(rt2x00dev->dev);
	काष्ठा resource *res;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -ENODEV;

	rt2x00dev->csr.base = ioremap(res->start, resource_size(res));
	अगर (!rt2x00dev->csr.base)
		वापस -ENOMEM;

	rt2x00dev->eeprom = kzalloc(rt2x00dev->ops->eeprom_size, GFP_KERNEL);
	अगर (!rt2x00dev->eeprom)
		जाओ निकास;

	rt2x00dev->rf = kzalloc(rt2x00dev->ops->rf_size, GFP_KERNEL);
	अगर (!rt2x00dev->rf)
		जाओ निकास;

	वापस 0;

निकास:
	rt2x00_probe_err("Failed to allocate registers\n");
	rt2x00soc_मुक्त_reg(rt2x00dev);

	वापस -ENOMEM;
पूर्ण

पूर्णांक rt2x00soc_probe(काष्ठा platक्रमm_device *pdev, स्थिर काष्ठा rt2x00_ops *ops)
अणु
	काष्ठा ieee80211_hw *hw;
	काष्ठा rt2x00_dev *rt2x00dev;
	पूर्णांक retval;

	hw = ieee80211_alloc_hw(माप(काष्ठा rt2x00_dev), ops->hw);
	अगर (!hw) अणु
		rt2x00_probe_err("Failed to allocate hardware\n");
		वापस -ENOMEM;
	पूर्ण

	platक्रमm_set_drvdata(pdev, hw);

	rt2x00dev = hw->priv;
	rt2x00dev->dev = &pdev->dev;
	rt2x00dev->ops = ops;
	rt2x00dev->hw = hw;
	rt2x00dev->irq = platक्रमm_get_irq(pdev, 0);
	rt2x00dev->name = pdev->dev.driver->name;

	rt2x00dev->clk = clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(rt2x00dev->clk))
		rt2x00dev->clk = शून्य;

	rt2x00_set_chip_पूर्णांकf(rt2x00dev, RT2X00_CHIP_INTF_SOC);

	retval = rt2x00soc_alloc_reg(rt2x00dev);
	अगर (retval)
		जाओ निकास_मुक्त_device;

	retval = rt2x00lib_probe_dev(rt2x00dev);
	अगर (retval)
		जाओ निकास_मुक्त_reg;

	वापस 0;

निकास_मुक्त_reg:
	rt2x00soc_मुक्त_reg(rt2x00dev);

निकास_मुक्त_device:
	ieee80211_मुक्त_hw(hw);

	वापस retval;
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00soc_probe);

पूर्णांक rt2x00soc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ieee80211_hw *hw = platक्रमm_get_drvdata(pdev);
	काष्ठा rt2x00_dev *rt2x00dev = hw->priv;

	/*
	 * Free all allocated data.
	 */
	rt2x00lib_हटाओ_dev(rt2x00dev);
	rt2x00soc_मुक्त_reg(rt2x00dev);
	ieee80211_मुक्त_hw(hw);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00soc_हटाओ);

#अगर_घोषित CONFIG_PM
पूर्णांक rt2x00soc_suspend(काष्ठा platक्रमm_device *pdev, pm_message_t state)
अणु
	काष्ठा ieee80211_hw *hw = platक्रमm_get_drvdata(pdev);
	काष्ठा rt2x00_dev *rt2x00dev = hw->priv;

	वापस rt2x00lib_suspend(rt2x00dev);
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00soc_suspend);

पूर्णांक rt2x00soc_resume(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ieee80211_hw *hw = platक्रमm_get_drvdata(pdev);
	काष्ठा rt2x00_dev *rt2x00dev = hw->priv;

	वापस rt2x00lib_resume(rt2x00dev);
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00soc_resume);
#पूर्ण_अगर /* CONFIG_PM */

/*
 * rt2x00soc module inक्रमmation.
 */
MODULE_AUTHOR(DRV_PROJECT);
MODULE_VERSION(DRV_VERSION);
MODULE_DESCRIPTION("rt2x00 soc library");
MODULE_LICENSE("GPL");
