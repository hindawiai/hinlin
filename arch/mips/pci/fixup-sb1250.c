<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	Copyright (C) 2004, 2006  MIPS Technologies, Inc.  All rights reserved.
 *	    Author:	Maciej W. Rozycki <macro@mips.com>
 *	Copyright (C) 2018  Maciej W. Rozycki
 */

#समावेश <linux/dma-mapping.h>
#समावेश <linux/pci.h>

/*
 * Set the BCM1250, etc. PCI host bridge's TRDY समयout
 * to the finite max.
 */
अटल व्योम quirk_sb1250_pci(काष्ठा pci_dev *dev)
अणु
	pci_ग_लिखो_config_byte(dev, 0x40, 0xff);
पूर्ण
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_SIBYTE, PCI_DEVICE_ID_BCM1250_PCI,
			quirk_sb1250_pci);

/*
 * The BCM1250, etc. PCI host bridge करोes not support DAC on its 32-bit
 * bus, so we set the bus's DMA limit accordingly.  However the HT link
 * करोwn the artअगरicial PCI-HT bridge supports 40-bit addressing and the
 * SP1011 HT-PCI bridge करोwnstream supports both DAC and a 64-bit bus
 * width, so we record the PCI-HT bridge's secondary and subordinate bus
 * numbers and करो not set the limit क्रम devices present in the inclusive
 * range of those.
 */
काष्ठा sb1250_bus_dma_limit_exclude अणु
	bool set;
	अचिन्हित अक्षर start;
	अचिन्हित अक्षर end;
पूर्ण;

अटल पूर्णांक sb1250_bus_dma_limit(काष्ठा pci_dev *dev, व्योम *data)
अणु
	काष्ठा sb1250_bus_dma_limit_exclude *exclude = data;
	bool exclude_this;
	bool ht_bridge;

	exclude_this = exclude->set && (dev->bus->number >= exclude->start &&
					dev->bus->number <= exclude->end);
	ht_bridge = !exclude->set && (dev->venकरोr == PCI_VENDOR_ID_SIBYTE &&
				      dev->device == PCI_DEVICE_ID_BCM1250_HT);

	अगर (exclude_this) अणु
		dev_dbg(&dev->dev, "not disabling DAC for device");
	पूर्ण अन्यथा अगर (ht_bridge) अणु
		exclude->start = dev->subordinate->number;
		exclude->end = pci_bus_max_busnr(dev->subordinate);
		exclude->set = true;
		dev_dbg(&dev->dev, "not disabling DAC for [bus %02x-%02x]",
			exclude->start, exclude->end);
	पूर्ण अन्यथा अणु
		dev_dbg(&dev->dev, "disabling DAC for device");
		dev->dev.bus_dma_limit = DMA_BIT_MASK(32);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम quirk_sb1250_pci_dac(काष्ठा pci_dev *dev)
अणु
	काष्ठा sb1250_bus_dma_limit_exclude exclude = अणु .set = false पूर्ण;

	pci_walk_bus(dev->bus, sb1250_bus_dma_limit, &exclude);
पूर्ण
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_SIBYTE, PCI_DEVICE_ID_BCM1250_PCI,
			quirk_sb1250_pci_dac);

/*
 * The BCM1250, etc. PCI/HT bridge reports as a host bridge.
 */
अटल व्योम quirk_sb1250_ht(काष्ठा pci_dev *dev)
अणु
	dev->class = PCI_CLASS_BRIDGE_PCI << 8;
पूर्ण
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_SIBYTE, PCI_DEVICE_ID_BCM1250_HT,
			quirk_sb1250_ht);

/*
 * Set the SP1011 HT/PCI bridge's TRDY समयout to the finite max.
 */
अटल व्योम quirk_sp1011(काष्ठा pci_dev *dev)
अणु
	pci_ग_लिखो_config_byte(dev, 0x64, 0xff);
पूर्ण
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_SIPACKETS, PCI_DEVICE_ID_SP1011,
			quirk_sp1011);
