<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * UIO driver fo Humusoft MF624 DAQ card.
 * Copyright (C) 2011 Rostislav Lisovy <lisovy@gmail.com>,
 *                    Czech Technical University in Prague
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/uio_driver.h>

#घोषणा PCI_VENDOR_ID_HUMUSOFT		0x186c
#घोषणा PCI_DEVICE_ID_MF624		0x0624
#घोषणा PCI_SUBVENDOR_ID_HUMUSOFT	0x186c
#घोषणा PCI_SUBDEVICE_DEVICE		0x0624

/* BAR0 Interrupt control/status रेजिस्टर */
#घोषणा INTCSR				0x4C
#घोषणा INTCSR_ADINT_ENABLE		(1 << 0)
#घोषणा INTCSR_CTR4INT_ENABLE		(1 << 3)
#घोषणा INTCSR_PCIINT_ENABLE		(1 << 6)
#घोषणा INTCSR_ADINT_STATUS		(1 << 2)
#घोषणा INTCSR_CTR4INT_STATUS		(1 << 5)

क्रमागत mf624_पूर्णांकerrupt_source अणुADC, CTR4, ALLपूर्ण;

अटल व्योम mf624_disable_पूर्णांकerrupt(क्रमागत mf624_पूर्णांकerrupt_source source,
			     काष्ठा uio_info *info)
अणु
	व्योम __iomem *INTCSR_reg = info->mem[0].पूर्णांकernal_addr + INTCSR;

	चयन (source) अणु
	हाल ADC:
		ioग_लिखो32(ioपढ़ो32(INTCSR_reg)
			& ~(INTCSR_ADINT_ENABLE | INTCSR_PCIINT_ENABLE),
			INTCSR_reg);
		अवरोध;

	हाल CTR4:
		ioग_लिखो32(ioपढ़ो32(INTCSR_reg)
			& ~(INTCSR_CTR4INT_ENABLE | INTCSR_PCIINT_ENABLE),
			INTCSR_reg);
		अवरोध;

	हाल ALL:
	शेष:
		ioग_लिखो32(ioपढ़ो32(INTCSR_reg)
			& ~(INTCSR_ADINT_ENABLE | INTCSR_CTR4INT_ENABLE
			    | INTCSR_PCIINT_ENABLE),
			INTCSR_reg);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम mf624_enable_पूर्णांकerrupt(क्रमागत mf624_पूर्णांकerrupt_source source,
			    काष्ठा uio_info *info)
अणु
	व्योम __iomem *INTCSR_reg = info->mem[0].पूर्णांकernal_addr + INTCSR;

	चयन (source) अणु
	हाल ADC:
		ioग_लिखो32(ioपढ़ो32(INTCSR_reg)
			| INTCSR_ADINT_ENABLE | INTCSR_PCIINT_ENABLE,
			INTCSR_reg);
		अवरोध;

	हाल CTR4:
		ioग_लिखो32(ioपढ़ो32(INTCSR_reg)
			| INTCSR_CTR4INT_ENABLE | INTCSR_PCIINT_ENABLE,
			INTCSR_reg);
		अवरोध;

	हाल ALL:
	शेष:
		ioग_लिखो32(ioपढ़ो32(INTCSR_reg)
			| INTCSR_ADINT_ENABLE | INTCSR_CTR4INT_ENABLE
			| INTCSR_PCIINT_ENABLE,
			INTCSR_reg);
		अवरोध;
	पूर्ण
पूर्ण

अटल irqवापस_t mf624_irq_handler(पूर्णांक irq, काष्ठा uio_info *info)
अणु
	व्योम __iomem *INTCSR_reg = info->mem[0].पूर्णांकernal_addr + INTCSR;

	अगर ((ioपढ़ो32(INTCSR_reg) & INTCSR_ADINT_ENABLE)
	    && (ioपढ़ो32(INTCSR_reg) & INTCSR_ADINT_STATUS)) अणु
		mf624_disable_पूर्णांकerrupt(ADC, info);
		वापस IRQ_HANDLED;
	पूर्ण

	अगर ((ioपढ़ो32(INTCSR_reg) & INTCSR_CTR4INT_ENABLE)
	    && (ioपढ़ो32(INTCSR_reg) & INTCSR_CTR4INT_STATUS)) अणु
		mf624_disable_पूर्णांकerrupt(CTR4, info);
		वापस IRQ_HANDLED;
	पूर्ण

	वापस IRQ_NONE;
पूर्ण

अटल पूर्णांक mf624_irqcontrol(काष्ठा uio_info *info, s32 irq_on)
अणु
	अगर (irq_on == 0)
		mf624_disable_पूर्णांकerrupt(ALL, info);
	अन्यथा अगर (irq_on == 1)
		mf624_enable_पूर्णांकerrupt(ALL, info);

	वापस 0;
पूर्ण

अटल पूर्णांक mf624_setup_mem(काष्ठा pci_dev *dev, पूर्णांक bar, काष्ठा uio_mem *mem, स्थिर अक्षर *name)
अणु
	resource_माप_प्रकार start = pci_resource_start(dev, bar);
	resource_माप_प्रकार len = pci_resource_len(dev, bar);

	mem->name = name;
	mem->addr = start & PAGE_MASK;
	mem->offs = start & ~PAGE_MASK;
	अगर (!mem->addr)
		वापस -ENODEV;
	mem->size = ((start & ~PAGE_MASK) + len + PAGE_SIZE - 1) & PAGE_MASK;
	mem->memtype = UIO_MEM_PHYS;
	mem->पूर्णांकernal_addr = pci_ioremap_bar(dev, bar);
	अगर (!mem->पूर्णांकernal_addr)
		वापस -ENODEV;
	वापस 0;
पूर्ण

अटल पूर्णांक mf624_pci_probe(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा uio_info *info;

	info = devm_kzalloc(&dev->dev, माप(काष्ठा uio_info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	अगर (pci_enable_device(dev))
		वापस -ENODEV;

	अगर (pci_request_regions(dev, "mf624"))
		जाओ out_disable;

	info->name = "mf624";
	info->version = "0.0.1";

	/* Note: Datasheet says device uses BAR0, BAR1, BAR2 -- करो not trust it */

	/* BAR0 */
	अगर (mf624_setup_mem(dev, 0, &info->mem[0], "PCI chipset, interrupts, status "
			    "bits, special functions"))
		जाओ out_release;
	/* BAR2 */
	अगर (mf624_setup_mem(dev, 2, &info->mem[1], "ADC, DAC, DIO"))
		जाओ out_unmap0;

	/* BAR4 */
	अगर (mf624_setup_mem(dev, 4, &info->mem[2], "Counter/timer chip"))
		जाओ out_unmap1;

	info->irq = dev->irq;
	info->irq_flags = IRQF_SHARED;
	info->handler = mf624_irq_handler;

	info->irqcontrol = mf624_irqcontrol;

	अगर (uio_रेजिस्टर_device(&dev->dev, info))
		जाओ out_unmap2;

	pci_set_drvdata(dev, info);

	वापस 0;

out_unmap2:
	iounmap(info->mem[2].पूर्णांकernal_addr);
out_unmap1:
	iounmap(info->mem[1].पूर्णांकernal_addr);
out_unmap0:
	iounmap(info->mem[0].पूर्णांकernal_addr);

out_release:
	pci_release_regions(dev);

out_disable:
	pci_disable_device(dev);

	वापस -ENODEV;
पूर्ण

अटल व्योम mf624_pci_हटाओ(काष्ठा pci_dev *dev)
अणु
	काष्ठा uio_info *info = pci_get_drvdata(dev);

	mf624_disable_पूर्णांकerrupt(ALL, info);

	uio_unरेजिस्टर_device(info);
	pci_release_regions(dev);
	pci_disable_device(dev);

	iounmap(info->mem[0].पूर्णांकernal_addr);
	iounmap(info->mem[1].पूर्णांकernal_addr);
	iounmap(info->mem[2].पूर्णांकernal_addr);
पूर्ण

अटल स्थिर काष्ठा pci_device_id mf624_pci_id[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_HUMUSOFT, PCI_DEVICE_ID_MF624) पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

अटल काष्ठा pci_driver mf624_pci_driver = अणु
	.name = "mf624",
	.id_table = mf624_pci_id,
	.probe = mf624_pci_probe,
	.हटाओ = mf624_pci_हटाओ,
पूर्ण;
MODULE_DEVICE_TABLE(pci, mf624_pci_id);

module_pci_driver(mf624_pci_driver);
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Rostislav Lisovy <lisovy@gmail.com>");
