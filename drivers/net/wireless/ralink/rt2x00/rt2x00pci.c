<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
	Copyright (C) 2004 - 2009 Ivo van Doorn <IvDoorn@gmail.com>
	<http://rt2x00.serialmonkey.com>

 */

/*
	Module: rt2x00pci
	Abstract: rt2x00 generic pci device routines.
 */

#समावेश <linux/dma-mapping.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>

#समावेश "rt2x00.h"
#समावेश "rt2x00pci.h"

/*
 * PCI driver handlers.
 */
अटल व्योम rt2x00pci_मुक्त_reg(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	kमुक्त(rt2x00dev->rf);
	rt2x00dev->rf = शून्य;

	kमुक्त(rt2x00dev->eeprom);
	rt2x00dev->eeprom = शून्य;

	अगर (rt2x00dev->csr.base) अणु
		iounmap(rt2x00dev->csr.base);
		rt2x00dev->csr.base = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक rt2x00pci_alloc_reg(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	काष्ठा pci_dev *pci_dev = to_pci_dev(rt2x00dev->dev);

	rt2x00dev->csr.base = pci_ioremap_bar(pci_dev, 0);
	अगर (!rt2x00dev->csr.base)
		जाओ निकास;

	rt2x00dev->eeprom = kzalloc(rt2x00dev->ops->eeprom_size, GFP_KERNEL);
	अगर (!rt2x00dev->eeprom)
		जाओ निकास;

	rt2x00dev->rf = kzalloc(rt2x00dev->ops->rf_size, GFP_KERNEL);
	अगर (!rt2x00dev->rf)
		जाओ निकास;

	वापस 0;

निकास:
	rt2x00_probe_err("Failed to allocate registers\n");

	rt2x00pci_मुक्त_reg(rt2x00dev);

	वापस -ENOMEM;
पूर्ण

पूर्णांक rt2x00pci_probe(काष्ठा pci_dev *pci_dev, स्थिर काष्ठा rt2x00_ops *ops)
अणु
	काष्ठा ieee80211_hw *hw;
	काष्ठा rt2x00_dev *rt2x00dev;
	पूर्णांक retval;
	u16 chip;

	retval = pci_enable_device(pci_dev);
	अगर (retval) अणु
		rt2x00_probe_err("Enable device failed\n");
		वापस retval;
	पूर्ण

	retval = pci_request_regions(pci_dev, pci_name(pci_dev));
	अगर (retval) अणु
		rt2x00_probe_err("PCI request regions failed\n");
		जाओ निकास_disable_device;
	पूर्ण

	pci_set_master(pci_dev);

	अगर (pci_set_mwi(pci_dev))
		rt2x00_probe_err("MWI not available\n");

	अगर (dma_set_mask(&pci_dev->dev, DMA_BIT_MASK(32))) अणु
		rt2x00_probe_err("PCI DMA not supported\n");
		retval = -EIO;
		जाओ निकास_release_regions;
	पूर्ण

	hw = ieee80211_alloc_hw(माप(काष्ठा rt2x00_dev), ops->hw);
	अगर (!hw) अणु
		rt2x00_probe_err("Failed to allocate hardware\n");
		retval = -ENOMEM;
		जाओ निकास_release_regions;
	पूर्ण

	pci_set_drvdata(pci_dev, hw);

	rt2x00dev = hw->priv;
	rt2x00dev->dev = &pci_dev->dev;
	rt2x00dev->ops = ops;
	rt2x00dev->hw = hw;
	rt2x00dev->irq = pci_dev->irq;
	rt2x00dev->name = ops->name;

	अगर (pci_is_pcie(pci_dev))
		rt2x00_set_chip_पूर्णांकf(rt2x00dev, RT2X00_CHIP_INTF_PCIE);
	अन्यथा
		rt2x00_set_chip_पूर्णांकf(rt2x00dev, RT2X00_CHIP_INTF_PCI);

	retval = rt2x00pci_alloc_reg(rt2x00dev);
	अगर (retval)
		जाओ निकास_मुक्त_device;

	/*
	 * Because rt3290 chip use dअगरferent efuse offset to पढ़ो efuse data.
	 * So beक्रमe पढ़ो efuse it need to indicate it is the
	 * rt3290 or not.
	 */
	pci_पढ़ो_config_word(pci_dev, PCI_DEVICE_ID, &chip);
	rt2x00dev->chip.rt = chip;

	retval = rt2x00lib_probe_dev(rt2x00dev);
	अगर (retval)
		जाओ निकास_मुक्त_reg;

	वापस 0;

निकास_मुक्त_reg:
	rt2x00pci_मुक्त_reg(rt2x00dev);

निकास_मुक्त_device:
	ieee80211_मुक्त_hw(hw);

निकास_release_regions:
	pci_clear_mwi(pci_dev);
	pci_release_regions(pci_dev);

निकास_disable_device:
	pci_disable_device(pci_dev);

	वापस retval;
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00pci_probe);

व्योम rt2x00pci_हटाओ(काष्ठा pci_dev *pci_dev)
अणु
	काष्ठा ieee80211_hw *hw = pci_get_drvdata(pci_dev);
	काष्ठा rt2x00_dev *rt2x00dev = hw->priv;

	/*
	 * Free all allocated data.
	 */
	rt2x00lib_हटाओ_dev(rt2x00dev);
	rt2x00pci_मुक्त_reg(rt2x00dev);
	ieee80211_मुक्त_hw(hw);

	/*
	 * Free the PCI device data.
	 */
	pci_clear_mwi(pci_dev);
	pci_disable_device(pci_dev);
	pci_release_regions(pci_dev);
पूर्ण
EXPORT_SYMBOL_GPL(rt2x00pci_हटाओ);

अटल पूर्णांक __maybe_unused rt2x00pci_suspend(काष्ठा device *dev)
अणु
	काष्ठा ieee80211_hw *hw = dev_get_drvdata(dev);
	काष्ठा rt2x00_dev *rt2x00dev = hw->priv;

	वापस rt2x00lib_suspend(rt2x00dev);
पूर्ण

अटल पूर्णांक __maybe_unused rt2x00pci_resume(काष्ठा device *dev)
अणु
	काष्ठा ieee80211_hw *hw = dev_get_drvdata(dev);
	काष्ठा rt2x00_dev *rt2x00dev = hw->priv;

	वापस rt2x00lib_resume(rt2x00dev);
पूर्ण

SIMPLE_DEV_PM_OPS(rt2x00pci_pm_ops, rt2x00pci_suspend, rt2x00pci_resume);
EXPORT_SYMBOL_GPL(rt2x00pci_pm_ops);

/*
 * rt2x00pci module inक्रमmation.
 */
MODULE_AUTHOR(DRV_PROJECT);
MODULE_VERSION(DRV_VERSION);
MODULE_DESCRIPTION("rt2x00 pci library");
MODULE_LICENSE("GPL");
