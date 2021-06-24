<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* sercos3: UIO driver क्रम the Automata Sercos III PCI card

   Copyright (C) 2008 Linutronix GmbH
     Author: John Ogness <john.ogness@linutronix.de>

   This is a straight-क्रमward UIO driver, where पूर्णांकerrupts are disabled
   by the पूर्णांकerrupt handler and re-enabled via a ग_लिखो to the UIO device
   by the userspace-part.

   The only part that may seem odd is the use of a logical OR when
   storing and restoring enabled पूर्णांकerrupts. This is करोne because the
   userspace-part could directly modअगरy the Interrupt Enable Register
   at any समय. To reduce possible conflicts, the kernel driver uses
   a logical OR to make more controlled changes (rather than blindly
   overwriting previous values).

   Race conditions exist अगर the userspace-part directly modअगरies the
   Interrupt Enable Register जबतक in operation. The consequences are
   that certain पूर्णांकerrupts would fail to be enabled or disabled. For
   this reason, the userspace-part should only directly modअगरy the
   Interrupt Enable Register at the beginning (to get things going).
   The userspace-part can safely disable पूर्णांकerrupts at any समय using
   a ग_लिखो to the UIO device.
*/

#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/uio_driver.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>

/* ID's क्रम SERCOS III PCI card (PLX 9030) */
#घोषणा SERCOS_SUB_VENDOR_ID  0x1971
#घोषणा SERCOS_SUB_SYSID_3530 0x3530
#घोषणा SERCOS_SUB_SYSID_3535 0x3535
#घोषणा SERCOS_SUB_SYSID_3780 0x3780

/* Interrupt Enable Register */
#घोषणा IER0_OFFSET 0x08

/* Interrupt Status Register */
#घोषणा ISR0_OFFSET 0x18

काष्ठा sercos3_priv अणु
	u32 ier0_cache;
	spinlock_t ier0_cache_lock;
पूर्ण;

/* this function assumes ier0_cache_lock is locked! */
अटल व्योम sercos3_disable_पूर्णांकerrupts(काष्ठा uio_info *info,
				       काष्ठा sercos3_priv *priv)
अणु
	व्योम __iomem *ier0 = info->mem[3].पूर्णांकernal_addr + IER0_OFFSET;

	/* add enabled पूर्णांकerrupts to cache */
	priv->ier0_cache |= ioपढ़ो32(ier0);

	/* disable पूर्णांकerrupts */
	ioग_लिखो32(0, ier0);
पूर्ण

/* this function assumes ier0_cache_lock is locked! */
अटल व्योम sercos3_enable_पूर्णांकerrupts(काष्ठा uio_info *info,
				      काष्ठा sercos3_priv *priv)
अणु
	व्योम __iomem *ier0 = info->mem[3].पूर्णांकernal_addr + IER0_OFFSET;

	/* restore previously enabled पूर्णांकerrupts */
	ioग_लिखो32(ioपढ़ो32(ier0) | priv->ier0_cache, ier0);
	priv->ier0_cache = 0;
पूर्ण

अटल irqवापस_t sercos3_handler(पूर्णांक irq, काष्ठा uio_info *info)
अणु
	काष्ठा sercos3_priv *priv = info->priv;
	व्योम __iomem *isr0 = info->mem[3].पूर्णांकernal_addr + ISR0_OFFSET;
	व्योम __iomem *ier0 = info->mem[3].पूर्णांकernal_addr + IER0_OFFSET;

	अगर (!(ioपढ़ो32(isr0) & ioपढ़ो32(ier0)))
		वापस IRQ_NONE;

	spin_lock(&priv->ier0_cache_lock);
	sercos3_disable_पूर्णांकerrupts(info, priv);
	spin_unlock(&priv->ier0_cache_lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक sercos3_irqcontrol(काष्ठा uio_info *info, s32 irq_on)
अणु
	काष्ठा sercos3_priv *priv = info->priv;

	spin_lock_irq(&priv->ier0_cache_lock);
	अगर (irq_on)
		sercos3_enable_पूर्णांकerrupts(info, priv);
	अन्यथा
		sercos3_disable_पूर्णांकerrupts(info, priv);
	spin_unlock_irq(&priv->ier0_cache_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक sercos3_setup_iomem(काष्ठा pci_dev *dev, काष्ठा uio_info *info,
			       पूर्णांक n, पूर्णांक pci_bar)
अणु
	info->mem[n].addr = pci_resource_start(dev, pci_bar);
	अगर (!info->mem[n].addr)
		वापस -1;
	info->mem[n].पूर्णांकernal_addr = ioremap(pci_resource_start(dev, pci_bar),
					     pci_resource_len(dev, pci_bar));
	अगर (!info->mem[n].पूर्णांकernal_addr)
		वापस -1;
	info->mem[n].size = pci_resource_len(dev, pci_bar);
	info->mem[n].memtype = UIO_MEM_PHYS;
	वापस 0;
पूर्ण

अटल पूर्णांक sercos3_pci_probe(काष्ठा pci_dev *dev,
				       स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा uio_info *info;
	काष्ठा sercos3_priv *priv;
	पूर्णांक i;

	info = devm_kzalloc(&dev->dev, माप(काष्ठा uio_info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	priv = devm_kzalloc(&dev->dev, माप(काष्ठा sercos3_priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	अगर (pci_enable_device(dev))
		वापस -ENODEV;

	अगर (pci_request_regions(dev, "sercos3"))
		जाओ out_disable;

	/* we only need PCI BAR's 0, 2, 3, 4, 5 */
	अगर (sercos3_setup_iomem(dev, info, 0, 0))
		जाओ out_unmap;
	अगर (sercos3_setup_iomem(dev, info, 1, 2))
		जाओ out_unmap;
	अगर (sercos3_setup_iomem(dev, info, 2, 3))
		जाओ out_unmap;
	अगर (sercos3_setup_iomem(dev, info, 3, 4))
		जाओ out_unmap;
	अगर (sercos3_setup_iomem(dev, info, 4, 5))
		जाओ out_unmap;

	spin_lock_init(&priv->ier0_cache_lock);
	info->priv = priv;
	info->name = "Sercos_III_PCI";
	info->version = "0.0.1";
	info->irq = dev->irq;
	info->irq_flags = IRQF_SHARED;
	info->handler = sercos3_handler;
	info->irqcontrol = sercos3_irqcontrol;

	pci_set_drvdata(dev, info);

	अगर (uio_रेजिस्टर_device(&dev->dev, info))
		जाओ out_unmap;

	वापस 0;

out_unmap:
	क्रम (i = 0; i < 5; i++) अणु
		अगर (info->mem[i].पूर्णांकernal_addr)
			iounmap(info->mem[i].पूर्णांकernal_addr);
	पूर्ण
	pci_release_regions(dev);
out_disable:
	pci_disable_device(dev);
	वापस -ENODEV;
पूर्ण

अटल व्योम sercos3_pci_हटाओ(काष्ठा pci_dev *dev)
अणु
	काष्ठा uio_info *info = pci_get_drvdata(dev);
	पूर्णांक i;

	uio_unरेजिस्टर_device(info);
	pci_release_regions(dev);
	pci_disable_device(dev);
	क्रम (i = 0; i < 5; i++) अणु
		अगर (info->mem[i].पूर्णांकernal_addr)
			iounmap(info->mem[i].पूर्णांकernal_addr);
	पूर्ण
पूर्ण

अटल काष्ठा pci_device_id sercos3_pci_ids[] = अणु
	अणु
		.venकरोr =       PCI_VENDOR_ID_PLX,
		.device =       PCI_DEVICE_ID_PLX_9030,
		.subvenकरोr =    SERCOS_SUB_VENDOR_ID,
		.subdevice =    SERCOS_SUB_SYSID_3530,
	पूर्ण,
	अणु
		.venकरोr =       PCI_VENDOR_ID_PLX,
		.device =       PCI_DEVICE_ID_PLX_9030,
		.subvenकरोr =    SERCOS_SUB_VENDOR_ID,
		.subdevice =    SERCOS_SUB_SYSID_3535,
	पूर्ण,
	अणु
		.venकरोr =       PCI_VENDOR_ID_PLX,
		.device =       PCI_DEVICE_ID_PLX_9030,
		.subvenकरोr =    SERCOS_SUB_VENDOR_ID,
		.subdevice =    SERCOS_SUB_SYSID_3780,
	पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

अटल काष्ठा pci_driver sercos3_pci_driver = अणु
	.name = "sercos3",
	.id_table = sercos3_pci_ids,
	.probe = sercos3_pci_probe,
	.हटाओ = sercos3_pci_हटाओ,
पूर्ण;

module_pci_driver(sercos3_pci_driver);
MODULE_DESCRIPTION("UIO driver for the Automata Sercos III PCI card");
MODULE_AUTHOR("John Ogness <john.ogness@linutronix.de>");
MODULE_LICENSE("GPL v2");
