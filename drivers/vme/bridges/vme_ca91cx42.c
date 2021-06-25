<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Support क्रम the Tundra Universe I/II VME-PCI Bridge Chips
 *
 * Author: Martyn Welch <martyn.welch@ge.com>
 * Copyright 2008 GE Intelligent Platक्रमms Embedded Systems, Inc.
 *
 * Based on work by Tom Armistead and Ajit Prem
 * Copyright 2004 Motorola Inc.
 *
 * Derived from ca91c042.c by Michael Wyrick
 */

#समावेश <linux/module.h>
#समावेश <linux/mm.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/pci.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/poll.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/समय.स>
#समावेश <linux/पन.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/vme.h>

#समावेश "../vme_bridge.h"
#समावेश "vme_ca91cx42.h"

अटल पूर्णांक ca91cx42_probe(काष्ठा pci_dev *, स्थिर काष्ठा pci_device_id *);
अटल व्योम ca91cx42_हटाओ(काष्ठा pci_dev *);

/* Module parameters */
अटल पूर्णांक geoid;

अटल स्थिर अक्षर driver_name[] = "vme_ca91cx42";

अटल स्थिर काष्ठा pci_device_id ca91cx42_ids[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_TUNDRA, PCI_DEVICE_ID_TUNDRA_CA91C142) पूर्ण,
	अणु पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(pci, ca91cx42_ids);

अटल काष्ठा pci_driver ca91cx42_driver = अणु
	.name = driver_name,
	.id_table = ca91cx42_ids,
	.probe = ca91cx42_probe,
	.हटाओ = ca91cx42_हटाओ,
पूर्ण;

अटल u32 ca91cx42_DMA_irqhandler(काष्ठा ca91cx42_driver *bridge)
अणु
	wake_up(&bridge->dma_queue);

	वापस CA91CX42_LINT_DMA;
पूर्ण

अटल u32 ca91cx42_LM_irqhandler(काष्ठा ca91cx42_driver *bridge, u32 stat)
अणु
	पूर्णांक i;
	u32 serviced = 0;

	क्रम (i = 0; i < 4; i++) अणु
		अगर (stat & CA91CX42_LINT_LM[i]) अणु
			/* We only enable पूर्णांकerrupts अगर the callback is set */
			bridge->lm_callback[i](bridge->lm_data[i]);
			serviced |= CA91CX42_LINT_LM[i];
		पूर्ण
	पूर्ण

	वापस serviced;
पूर्ण

/* XXX This needs to be split पूर्णांकo 4 queues */
अटल u32 ca91cx42_MB_irqhandler(काष्ठा ca91cx42_driver *bridge, पूर्णांक mbox_mask)
अणु
	wake_up(&bridge->mbox_queue);

	वापस CA91CX42_LINT_MBOX;
पूर्ण

अटल u32 ca91cx42_IACK_irqhandler(काष्ठा ca91cx42_driver *bridge)
अणु
	wake_up(&bridge->iack_queue);

	वापस CA91CX42_LINT_SW_IACK;
पूर्ण

अटल u32 ca91cx42_VERR_irqhandler(काष्ठा vme_bridge *ca91cx42_bridge)
अणु
	पूर्णांक val;
	काष्ठा ca91cx42_driver *bridge;

	bridge = ca91cx42_bridge->driver_priv;

	val = ioपढ़ो32(bridge->base + DGCS);

	अगर (!(val & 0x00000800)) अणु
		dev_err(ca91cx42_bridge->parent, "ca91cx42_VERR_irqhandler DMA "
			"Read Error DGCS=%08X\n", val);
	पूर्ण

	वापस CA91CX42_LINT_VERR;
पूर्ण

अटल u32 ca91cx42_LERR_irqhandler(काष्ठा vme_bridge *ca91cx42_bridge)
अणु
	पूर्णांक val;
	काष्ठा ca91cx42_driver *bridge;

	bridge = ca91cx42_bridge->driver_priv;

	val = ioपढ़ो32(bridge->base + DGCS);

	अगर (!(val & 0x00000800))
		dev_err(ca91cx42_bridge->parent, "ca91cx42_LERR_irqhandler DMA "
			"Read Error DGCS=%08X\n", val);

	वापस CA91CX42_LINT_LERR;
पूर्ण


अटल u32 ca91cx42_VIRQ_irqhandler(काष्ठा vme_bridge *ca91cx42_bridge,
	पूर्णांक stat)
अणु
	पूर्णांक vec, i, serviced = 0;
	काष्ठा ca91cx42_driver *bridge;

	bridge = ca91cx42_bridge->driver_priv;


	क्रम (i = 7; i > 0; i--) अणु
		अगर (stat & (1 << i)) अणु
			vec = ioपढ़ो32(bridge->base +
				CA91CX42_V_STATID[i]) & 0xff;

			vme_irq_handler(ca91cx42_bridge, i, vec);

			serviced |= (1 << i);
		पूर्ण
	पूर्ण

	वापस serviced;
पूर्ण

अटल irqवापस_t ca91cx42_irqhandler(पूर्णांक irq, व्योम *ptr)
अणु
	u32 stat, enable, serviced = 0;
	काष्ठा vme_bridge *ca91cx42_bridge;
	काष्ठा ca91cx42_driver *bridge;

	ca91cx42_bridge = ptr;

	bridge = ca91cx42_bridge->driver_priv;

	enable = ioपढ़ो32(bridge->base + LINT_EN);
	stat = ioपढ़ो32(bridge->base + LINT_STAT);

	/* Only look at unmasked पूर्णांकerrupts */
	stat &= enable;

	अगर (unlikely(!stat))
		वापस IRQ_NONE;

	अगर (stat & CA91CX42_LINT_DMA)
		serviced |= ca91cx42_DMA_irqhandler(bridge);
	अगर (stat & (CA91CX42_LINT_LM0 | CA91CX42_LINT_LM1 | CA91CX42_LINT_LM2 |
			CA91CX42_LINT_LM3))
		serviced |= ca91cx42_LM_irqhandler(bridge, stat);
	अगर (stat & CA91CX42_LINT_MBOX)
		serviced |= ca91cx42_MB_irqhandler(bridge, stat);
	अगर (stat & CA91CX42_LINT_SW_IACK)
		serviced |= ca91cx42_IACK_irqhandler(bridge);
	अगर (stat & CA91CX42_LINT_VERR)
		serviced |= ca91cx42_VERR_irqhandler(ca91cx42_bridge);
	अगर (stat & CA91CX42_LINT_LERR)
		serviced |= ca91cx42_LERR_irqhandler(ca91cx42_bridge);
	अगर (stat & (CA91CX42_LINT_VIRQ1 | CA91CX42_LINT_VIRQ2 |
			CA91CX42_LINT_VIRQ3 | CA91CX42_LINT_VIRQ4 |
			CA91CX42_LINT_VIRQ5 | CA91CX42_LINT_VIRQ6 |
			CA91CX42_LINT_VIRQ7))
		serviced |= ca91cx42_VIRQ_irqhandler(ca91cx42_bridge, stat);

	/* Clear serviced पूर्णांकerrupts */
	ioग_लिखो32(serviced, bridge->base + LINT_STAT);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ca91cx42_irq_init(काष्ठा vme_bridge *ca91cx42_bridge)
अणु
	पूर्णांक result, पंचांगp;
	काष्ठा pci_dev *pdev;
	काष्ठा ca91cx42_driver *bridge;

	bridge = ca91cx42_bridge->driver_priv;

	/* Need pdev */
	pdev = to_pci_dev(ca91cx42_bridge->parent);

	/* Disable पूर्णांकerrupts from PCI to VME */
	ioग_लिखो32(0, bridge->base + VINT_EN);

	/* Disable PCI पूर्णांकerrupts */
	ioग_लिखो32(0, bridge->base + LINT_EN);
	/* Clear Any Pending PCI Interrupts */
	ioग_लिखो32(0x00FFFFFF, bridge->base + LINT_STAT);

	result = request_irq(pdev->irq, ca91cx42_irqhandler, IRQF_SHARED,
			driver_name, ca91cx42_bridge);
	अगर (result) अणु
		dev_err(&pdev->dev, "Can't get assigned pci irq vector %02X\n",
		       pdev->irq);
		वापस result;
	पूर्ण

	/* Ensure all पूर्णांकerrupts are mapped to PCI Interrupt 0 */
	ioग_लिखो32(0, bridge->base + LINT_MAP0);
	ioग_लिखो32(0, bridge->base + LINT_MAP1);
	ioग_लिखो32(0, bridge->base + LINT_MAP2);

	/* Enable DMA, mailbox & LM Interrupts */
	पंचांगp = CA91CX42_LINT_MBOX3 | CA91CX42_LINT_MBOX2 | CA91CX42_LINT_MBOX1 |
		CA91CX42_LINT_MBOX0 | CA91CX42_LINT_SW_IACK |
		CA91CX42_LINT_VERR | CA91CX42_LINT_LERR | CA91CX42_LINT_DMA;

	ioग_लिखो32(पंचांगp, bridge->base + LINT_EN);

	वापस 0;
पूर्ण

अटल व्योम ca91cx42_irq_निकास(काष्ठा ca91cx42_driver *bridge,
	काष्ठा pci_dev *pdev)
अणु
	काष्ठा vme_bridge *ca91cx42_bridge;

	/* Disable पूर्णांकerrupts from PCI to VME */
	ioग_लिखो32(0, bridge->base + VINT_EN);

	/* Disable PCI पूर्णांकerrupts */
	ioग_लिखो32(0, bridge->base + LINT_EN);
	/* Clear Any Pending PCI Interrupts */
	ioग_लिखो32(0x00FFFFFF, bridge->base + LINT_STAT);

	ca91cx42_bridge = container_of((व्योम *)bridge, काष्ठा vme_bridge,
				       driver_priv);
	मुक्त_irq(pdev->irq, ca91cx42_bridge);
पूर्ण

अटल पूर्णांक ca91cx42_iack_received(काष्ठा ca91cx42_driver *bridge, पूर्णांक level)
अणु
	u32 पंचांगp;

	पंचांगp = ioपढ़ो32(bridge->base + LINT_STAT);

	अगर (पंचांगp & (1 << level))
		वापस 0;
	अन्यथा
		वापस 1;
पूर्ण

/*
 * Set up an VME पूर्णांकerrupt
 */
अटल व्योम ca91cx42_irq_set(काष्ठा vme_bridge *ca91cx42_bridge, पूर्णांक level,
	पूर्णांक state, पूर्णांक sync)

अणु
	काष्ठा pci_dev *pdev;
	u32 पंचांगp;
	काष्ठा ca91cx42_driver *bridge;

	bridge = ca91cx42_bridge->driver_priv;

	/* Enable IRQ level */
	पंचांगp = ioपढ़ो32(bridge->base + LINT_EN);

	अगर (state == 0)
		पंचांगp &= ~CA91CX42_LINT_VIRQ[level];
	अन्यथा
		पंचांगp |= CA91CX42_LINT_VIRQ[level];

	ioग_लिखो32(पंचांगp, bridge->base + LINT_EN);

	अगर ((state == 0) && (sync != 0)) अणु
		pdev = to_pci_dev(ca91cx42_bridge->parent);

		synchronize_irq(pdev->irq);
	पूर्ण
पूर्ण

अटल पूर्णांक ca91cx42_irq_generate(काष्ठा vme_bridge *ca91cx42_bridge, पूर्णांक level,
	पूर्णांक statid)
अणु
	u32 पंचांगp;
	काष्ठा ca91cx42_driver *bridge;

	bridge = ca91cx42_bridge->driver_priv;

	/* Universe can only generate even vectors */
	अगर (statid & 1)
		वापस -EINVAL;

	mutex_lock(&bridge->vme_पूर्णांक);

	पंचांगp = ioपढ़ो32(bridge->base + VINT_EN);

	/* Set Status/ID */
	ioग_लिखो32(statid << 24, bridge->base + STATID);

	/* Assert VMEbus IRQ */
	पंचांगp = पंचांगp | (1 << (level + 24));
	ioग_लिखो32(पंचांगp, bridge->base + VINT_EN);

	/* Wait क्रम IACK */
	रुको_event_पूर्णांकerruptible(bridge->iack_queue,
				 ca91cx42_iack_received(bridge, level));

	/* Return पूर्णांकerrupt to low state */
	पंचांगp = ioपढ़ो32(bridge->base + VINT_EN);
	पंचांगp = पंचांगp & ~(1 << (level + 24));
	ioग_लिखो32(पंचांगp, bridge->base + VINT_EN);

	mutex_unlock(&bridge->vme_पूर्णांक);

	वापस 0;
पूर्ण

अटल पूर्णांक ca91cx42_slave_set(काष्ठा vme_slave_resource *image, पूर्णांक enabled,
	अचिन्हित दीर्घ दीर्घ vme_base, अचिन्हित दीर्घ दीर्घ size,
	dma_addr_t pci_base, u32 aspace, u32 cycle)
अणु
	अचिन्हित पूर्णांक i, addr = 0, granularity;
	अचिन्हित पूर्णांक temp_ctl = 0;
	अचिन्हित पूर्णांक vme_bound, pci_offset;
	काष्ठा vme_bridge *ca91cx42_bridge;
	काष्ठा ca91cx42_driver *bridge;

	ca91cx42_bridge = image->parent;

	bridge = ca91cx42_bridge->driver_priv;

	i = image->number;

	चयन (aspace) अणु
	हाल VME_A16:
		addr |= CA91CX42_VSI_CTL_VAS_A16;
		अवरोध;
	हाल VME_A24:
		addr |= CA91CX42_VSI_CTL_VAS_A24;
		अवरोध;
	हाल VME_A32:
		addr |= CA91CX42_VSI_CTL_VAS_A32;
		अवरोध;
	हाल VME_USER1:
		addr |= CA91CX42_VSI_CTL_VAS_USER1;
		अवरोध;
	हाल VME_USER2:
		addr |= CA91CX42_VSI_CTL_VAS_USER2;
		अवरोध;
	हाल VME_A64:
	हाल VME_CRCSR:
	हाल VME_USER3:
	हाल VME_USER4:
	शेष:
		dev_err(ca91cx42_bridge->parent, "Invalid address space\n");
		वापस -EINVAL;
		अवरोध;
	पूर्ण

	/*
	 * Bound address is a valid address क्रम the winकरोw, adjust
	 * accordingly
	 */
	vme_bound = vme_base + size;
	pci_offset = pci_base - vme_base;

	अगर ((i == 0) || (i == 4))
		granularity = 0x1000;
	अन्यथा
		granularity = 0x10000;

	अगर (vme_base & (granularity - 1)) अणु
		dev_err(ca91cx42_bridge->parent, "Invalid VME base "
			"alignment\n");
		वापस -EINVAL;
	पूर्ण
	अगर (vme_bound & (granularity - 1)) अणु
		dev_err(ca91cx42_bridge->parent, "Invalid VME bound "
			"alignment\n");
		वापस -EINVAL;
	पूर्ण
	अगर (pci_offset & (granularity - 1)) अणु
		dev_err(ca91cx42_bridge->parent, "Invalid PCI Offset "
			"alignment\n");
		वापस -EINVAL;
	पूर्ण

	/* Disable जबतक we are mucking around */
	temp_ctl = ioपढ़ो32(bridge->base + CA91CX42_VSI_CTL[i]);
	temp_ctl &= ~CA91CX42_VSI_CTL_EN;
	ioग_लिखो32(temp_ctl, bridge->base + CA91CX42_VSI_CTL[i]);

	/* Setup mapping */
	ioग_लिखो32(vme_base, bridge->base + CA91CX42_VSI_BS[i]);
	ioग_लिखो32(vme_bound, bridge->base + CA91CX42_VSI_BD[i]);
	ioग_लिखो32(pci_offset, bridge->base + CA91CX42_VSI_TO[i]);

	/* Setup address space */
	temp_ctl &= ~CA91CX42_VSI_CTL_VAS_M;
	temp_ctl |= addr;

	/* Setup cycle types */
	temp_ctl &= ~(CA91CX42_VSI_CTL_PGM_M | CA91CX42_VSI_CTL_SUPER_M);
	अगर (cycle & VME_SUPER)
		temp_ctl |= CA91CX42_VSI_CTL_SUPER_SUPR;
	अगर (cycle & VME_USER)
		temp_ctl |= CA91CX42_VSI_CTL_SUPER_NPRIV;
	अगर (cycle & VME_PROG)
		temp_ctl |= CA91CX42_VSI_CTL_PGM_PGM;
	अगर (cycle & VME_DATA)
		temp_ctl |= CA91CX42_VSI_CTL_PGM_DATA;

	/* Write ctl reg without enable */
	ioग_लिखो32(temp_ctl, bridge->base + CA91CX42_VSI_CTL[i]);

	अगर (enabled)
		temp_ctl |= CA91CX42_VSI_CTL_EN;

	ioग_लिखो32(temp_ctl, bridge->base + CA91CX42_VSI_CTL[i]);

	वापस 0;
पूर्ण

अटल पूर्णांक ca91cx42_slave_get(काष्ठा vme_slave_resource *image, पूर्णांक *enabled,
	अचिन्हित दीर्घ दीर्घ *vme_base, अचिन्हित दीर्घ दीर्घ *size,
	dma_addr_t *pci_base, u32 *aspace, u32 *cycle)
अणु
	अचिन्हित पूर्णांक i, granularity = 0, ctl = 0;
	अचिन्हित दीर्घ दीर्घ vme_bound, pci_offset;
	काष्ठा ca91cx42_driver *bridge;

	bridge = image->parent->driver_priv;

	i = image->number;

	अगर ((i == 0) || (i == 4))
		granularity = 0x1000;
	अन्यथा
		granularity = 0x10000;

	/* Read Registers */
	ctl = ioपढ़ो32(bridge->base + CA91CX42_VSI_CTL[i]);

	*vme_base = ioपढ़ो32(bridge->base + CA91CX42_VSI_BS[i]);
	vme_bound = ioपढ़ो32(bridge->base + CA91CX42_VSI_BD[i]);
	pci_offset = ioपढ़ो32(bridge->base + CA91CX42_VSI_TO[i]);

	*pci_base = (dma_addr_t)*vme_base + pci_offset;
	*size = (अचिन्हित दीर्घ दीर्घ)((vme_bound - *vme_base) + granularity);

	*enabled = 0;
	*aspace = 0;
	*cycle = 0;

	अगर (ctl & CA91CX42_VSI_CTL_EN)
		*enabled = 1;

	अगर ((ctl & CA91CX42_VSI_CTL_VAS_M) == CA91CX42_VSI_CTL_VAS_A16)
		*aspace = VME_A16;
	अगर ((ctl & CA91CX42_VSI_CTL_VAS_M) == CA91CX42_VSI_CTL_VAS_A24)
		*aspace = VME_A24;
	अगर ((ctl & CA91CX42_VSI_CTL_VAS_M) == CA91CX42_VSI_CTL_VAS_A32)
		*aspace = VME_A32;
	अगर ((ctl & CA91CX42_VSI_CTL_VAS_M) == CA91CX42_VSI_CTL_VAS_USER1)
		*aspace = VME_USER1;
	अगर ((ctl & CA91CX42_VSI_CTL_VAS_M) == CA91CX42_VSI_CTL_VAS_USER2)
		*aspace = VME_USER2;

	अगर (ctl & CA91CX42_VSI_CTL_SUPER_SUPR)
		*cycle |= VME_SUPER;
	अगर (ctl & CA91CX42_VSI_CTL_SUPER_NPRIV)
		*cycle |= VME_USER;
	अगर (ctl & CA91CX42_VSI_CTL_PGM_PGM)
		*cycle |= VME_PROG;
	अगर (ctl & CA91CX42_VSI_CTL_PGM_DATA)
		*cycle |= VME_DATA;

	वापस 0;
पूर्ण

/*
 * Allocate and map PCI Resource
 */
अटल पूर्णांक ca91cx42_alloc_resource(काष्ठा vme_master_resource *image,
	अचिन्हित दीर्घ दीर्घ size)
अणु
	अचिन्हित दीर्घ दीर्घ existing_size;
	पूर्णांक retval = 0;
	काष्ठा pci_dev *pdev;
	काष्ठा vme_bridge *ca91cx42_bridge;

	ca91cx42_bridge = image->parent;

	/* Find pci_dev container of dev */
	अगर (!ca91cx42_bridge->parent) अणु
		dev_err(ca91cx42_bridge->parent, "Dev entry NULL\n");
		वापस -EINVAL;
	पूर्ण
	pdev = to_pci_dev(ca91cx42_bridge->parent);

	existing_size = (अचिन्हित दीर्घ दीर्घ)(image->bus_resource.end -
		image->bus_resource.start);

	/* If the existing size is OK, वापस */
	अगर (existing_size == (size - 1))
		वापस 0;

	अगर (existing_size != 0) अणु
		iounmap(image->kern_base);
		image->kern_base = शून्य;
		kमुक्त(image->bus_resource.name);
		release_resource(&image->bus_resource);
		स_रखो(&image->bus_resource, 0, माप(image->bus_resource));
	पूर्ण

	अगर (!image->bus_resource.name) अणु
		image->bus_resource.name = kदो_स्मृति(VMENAMSIZ+3, GFP_ATOMIC);
		अगर (!image->bus_resource.name) अणु
			retval = -ENOMEM;
			जाओ err_name;
		पूर्ण
	पूर्ण

	प्र_लिखो((अक्षर *)image->bus_resource.name, "%s.%d",
		ca91cx42_bridge->name, image->number);

	image->bus_resource.start = 0;
	image->bus_resource.end = (अचिन्हित दीर्घ)size;
	image->bus_resource.flags = IORESOURCE_MEM;

	retval = pci_bus_alloc_resource(pdev->bus,
		&image->bus_resource, size, 0x10000, PCIBIOS_MIN_MEM,
		0, शून्य, शून्य);
	अगर (retval) अणु
		dev_err(ca91cx42_bridge->parent, "Failed to allocate mem "
			"resource for window %d size 0x%lx start 0x%lx\n",
			image->number, (अचिन्हित दीर्घ)size,
			(अचिन्हित दीर्घ)image->bus_resource.start);
		जाओ err_resource;
	पूर्ण

	image->kern_base = ioremap(
		image->bus_resource.start, size);
	अगर (!image->kern_base) अणु
		dev_err(ca91cx42_bridge->parent, "Failed to remap resource\n");
		retval = -ENOMEM;
		जाओ err_remap;
	पूर्ण

	वापस 0;

err_remap:
	release_resource(&image->bus_resource);
err_resource:
	kमुक्त(image->bus_resource.name);
	स_रखो(&image->bus_resource, 0, माप(image->bus_resource));
err_name:
	वापस retval;
पूर्ण

/*
 * Free and unmap PCI Resource
 */
अटल व्योम ca91cx42_मुक्त_resource(काष्ठा vme_master_resource *image)
अणु
	iounmap(image->kern_base);
	image->kern_base = शून्य;
	release_resource(&image->bus_resource);
	kमुक्त(image->bus_resource.name);
	स_रखो(&image->bus_resource, 0, माप(image->bus_resource));
पूर्ण


अटल पूर्णांक ca91cx42_master_set(काष्ठा vme_master_resource *image, पूर्णांक enabled,
	अचिन्हित दीर्घ दीर्घ vme_base, अचिन्हित दीर्घ दीर्घ size, u32 aspace,
	u32 cycle, u32 dwidth)
अणु
	पूर्णांक retval = 0;
	अचिन्हित पूर्णांक i, granularity = 0;
	अचिन्हित पूर्णांक temp_ctl = 0;
	अचिन्हित दीर्घ दीर्घ pci_bound, vme_offset, pci_base;
	काष्ठा vme_bridge *ca91cx42_bridge;
	काष्ठा ca91cx42_driver *bridge;

	ca91cx42_bridge = image->parent;

	bridge = ca91cx42_bridge->driver_priv;

	i = image->number;

	अगर ((i == 0) || (i == 4))
		granularity = 0x1000;
	अन्यथा
		granularity = 0x10000;

	/* Verअगरy input data */
	अगर (vme_base & (granularity - 1)) अणु
		dev_err(ca91cx42_bridge->parent, "Invalid VME Window "
			"alignment\n");
		retval = -EINVAL;
		जाओ err_winकरोw;
	पूर्ण
	अगर (size & (granularity - 1)) अणु
		dev_err(ca91cx42_bridge->parent, "Invalid VME Window "
			"alignment\n");
		retval = -EINVAL;
		जाओ err_winकरोw;
	पूर्ण

	spin_lock(&image->lock);

	/*
	 * Let's allocate the resource here rather than further up the stack as
	 * it aव्योमs pushing loads of bus dependent stuff up the stack
	 */
	retval = ca91cx42_alloc_resource(image, size);
	अगर (retval) अणु
		spin_unlock(&image->lock);
		dev_err(ca91cx42_bridge->parent, "Unable to allocate memory "
			"for resource name\n");
		retval = -ENOMEM;
		जाओ err_res;
	पूर्ण

	pci_base = (अचिन्हित दीर्घ दीर्घ)image->bus_resource.start;

	/*
	 * Bound address is a valid address क्रम the winकरोw, adjust
	 * according to winकरोw granularity.
	 */
	pci_bound = pci_base + size;
	vme_offset = vme_base - pci_base;

	/* Disable जबतक we are mucking around */
	temp_ctl = ioपढ़ो32(bridge->base + CA91CX42_LSI_CTL[i]);
	temp_ctl &= ~CA91CX42_LSI_CTL_EN;
	ioग_लिखो32(temp_ctl, bridge->base + CA91CX42_LSI_CTL[i]);

	/* Setup cycle types */
	temp_ctl &= ~CA91CX42_LSI_CTL_VCT_M;
	अगर (cycle & VME_BLT)
		temp_ctl |= CA91CX42_LSI_CTL_VCT_BLT;
	अगर (cycle & VME_MBLT)
		temp_ctl |= CA91CX42_LSI_CTL_VCT_MBLT;

	/* Setup data width */
	temp_ctl &= ~CA91CX42_LSI_CTL_VDW_M;
	चयन (dwidth) अणु
	हाल VME_D8:
		temp_ctl |= CA91CX42_LSI_CTL_VDW_D8;
		अवरोध;
	हाल VME_D16:
		temp_ctl |= CA91CX42_LSI_CTL_VDW_D16;
		अवरोध;
	हाल VME_D32:
		temp_ctl |= CA91CX42_LSI_CTL_VDW_D32;
		अवरोध;
	हाल VME_D64:
		temp_ctl |= CA91CX42_LSI_CTL_VDW_D64;
		अवरोध;
	शेष:
		spin_unlock(&image->lock);
		dev_err(ca91cx42_bridge->parent, "Invalid data width\n");
		retval = -EINVAL;
		जाओ err_dwidth;
		अवरोध;
	पूर्ण

	/* Setup address space */
	temp_ctl &= ~CA91CX42_LSI_CTL_VAS_M;
	चयन (aspace) अणु
	हाल VME_A16:
		temp_ctl |= CA91CX42_LSI_CTL_VAS_A16;
		अवरोध;
	हाल VME_A24:
		temp_ctl |= CA91CX42_LSI_CTL_VAS_A24;
		अवरोध;
	हाल VME_A32:
		temp_ctl |= CA91CX42_LSI_CTL_VAS_A32;
		अवरोध;
	हाल VME_CRCSR:
		temp_ctl |= CA91CX42_LSI_CTL_VAS_CRCSR;
		अवरोध;
	हाल VME_USER1:
		temp_ctl |= CA91CX42_LSI_CTL_VAS_USER1;
		अवरोध;
	हाल VME_USER2:
		temp_ctl |= CA91CX42_LSI_CTL_VAS_USER2;
		अवरोध;
	हाल VME_A64:
	हाल VME_USER3:
	हाल VME_USER4:
	शेष:
		spin_unlock(&image->lock);
		dev_err(ca91cx42_bridge->parent, "Invalid address space\n");
		retval = -EINVAL;
		जाओ err_aspace;
		अवरोध;
	पूर्ण

	temp_ctl &= ~(CA91CX42_LSI_CTL_PGM_M | CA91CX42_LSI_CTL_SUPER_M);
	अगर (cycle & VME_SUPER)
		temp_ctl |= CA91CX42_LSI_CTL_SUPER_SUPR;
	अगर (cycle & VME_PROG)
		temp_ctl |= CA91CX42_LSI_CTL_PGM_PGM;

	/* Setup mapping */
	ioग_लिखो32(pci_base, bridge->base + CA91CX42_LSI_BS[i]);
	ioग_लिखो32(pci_bound, bridge->base + CA91CX42_LSI_BD[i]);
	ioग_लिखो32(vme_offset, bridge->base + CA91CX42_LSI_TO[i]);

	/* Write ctl reg without enable */
	ioग_लिखो32(temp_ctl, bridge->base + CA91CX42_LSI_CTL[i]);

	अगर (enabled)
		temp_ctl |= CA91CX42_LSI_CTL_EN;

	ioग_लिखो32(temp_ctl, bridge->base + CA91CX42_LSI_CTL[i]);

	spin_unlock(&image->lock);
	वापस 0;

err_aspace:
err_dwidth:
	ca91cx42_मुक्त_resource(image);
err_res:
err_winकरोw:
	वापस retval;
पूर्ण

अटल पूर्णांक __ca91cx42_master_get(काष्ठा vme_master_resource *image,
	पूर्णांक *enabled, अचिन्हित दीर्घ दीर्घ *vme_base, अचिन्हित दीर्घ दीर्घ *size,
	u32 *aspace, u32 *cycle, u32 *dwidth)
अणु
	अचिन्हित पूर्णांक i, ctl;
	अचिन्हित दीर्घ दीर्घ pci_base, pci_bound, vme_offset;
	काष्ठा ca91cx42_driver *bridge;

	bridge = image->parent->driver_priv;

	i = image->number;

	ctl = ioपढ़ो32(bridge->base + CA91CX42_LSI_CTL[i]);

	pci_base = ioपढ़ो32(bridge->base + CA91CX42_LSI_BS[i]);
	vme_offset = ioपढ़ो32(bridge->base + CA91CX42_LSI_TO[i]);
	pci_bound = ioपढ़ो32(bridge->base + CA91CX42_LSI_BD[i]);

	*vme_base = pci_base + vme_offset;
	*size = (अचिन्हित दीर्घ दीर्घ)(pci_bound - pci_base);

	*enabled = 0;
	*aspace = 0;
	*cycle = 0;
	*dwidth = 0;

	अगर (ctl & CA91CX42_LSI_CTL_EN)
		*enabled = 1;

	/* Setup address space */
	चयन (ctl & CA91CX42_LSI_CTL_VAS_M) अणु
	हाल CA91CX42_LSI_CTL_VAS_A16:
		*aspace = VME_A16;
		अवरोध;
	हाल CA91CX42_LSI_CTL_VAS_A24:
		*aspace = VME_A24;
		अवरोध;
	हाल CA91CX42_LSI_CTL_VAS_A32:
		*aspace = VME_A32;
		अवरोध;
	हाल CA91CX42_LSI_CTL_VAS_CRCSR:
		*aspace = VME_CRCSR;
		अवरोध;
	हाल CA91CX42_LSI_CTL_VAS_USER1:
		*aspace = VME_USER1;
		अवरोध;
	हाल CA91CX42_LSI_CTL_VAS_USER2:
		*aspace = VME_USER2;
		अवरोध;
	पूर्ण

	/* XXX Not sure howto check क्रम MBLT */
	/* Setup cycle types */
	अगर (ctl & CA91CX42_LSI_CTL_VCT_BLT)
		*cycle |= VME_BLT;
	अन्यथा
		*cycle |= VME_SCT;

	अगर (ctl & CA91CX42_LSI_CTL_SUPER_SUPR)
		*cycle |= VME_SUPER;
	अन्यथा
		*cycle |= VME_USER;

	अगर (ctl & CA91CX42_LSI_CTL_PGM_PGM)
		*cycle = VME_PROG;
	अन्यथा
		*cycle = VME_DATA;

	/* Setup data width */
	चयन (ctl & CA91CX42_LSI_CTL_VDW_M) अणु
	हाल CA91CX42_LSI_CTL_VDW_D8:
		*dwidth = VME_D8;
		अवरोध;
	हाल CA91CX42_LSI_CTL_VDW_D16:
		*dwidth = VME_D16;
		अवरोध;
	हाल CA91CX42_LSI_CTL_VDW_D32:
		*dwidth = VME_D32;
		अवरोध;
	हाल CA91CX42_LSI_CTL_VDW_D64:
		*dwidth = VME_D64;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ca91cx42_master_get(काष्ठा vme_master_resource *image, पूर्णांक *enabled,
	अचिन्हित दीर्घ दीर्घ *vme_base, अचिन्हित दीर्घ दीर्घ *size, u32 *aspace,
	u32 *cycle, u32 *dwidth)
अणु
	पूर्णांक retval;

	spin_lock(&image->lock);

	retval = __ca91cx42_master_get(image, enabled, vme_base, size, aspace,
		cycle, dwidth);

	spin_unlock(&image->lock);

	वापस retval;
पूर्ण

अटल sमाप_प्रकार ca91cx42_master_पढ़ो(काष्ठा vme_master_resource *image,
	व्योम *buf, माप_प्रकार count, loff_t offset)
अणु
	sमाप_प्रकार retval;
	व्योम __iomem *addr = image->kern_base + offset;
	अचिन्हित पूर्णांक करोne = 0;
	अचिन्हित पूर्णांक count32;

	अगर (count == 0)
		वापस 0;

	spin_lock(&image->lock);

	/* The following code handles VME address alignment. We cannot use
	 * स_नकल_xxx here because it may cut data transfers in to 8-bit
	 * cycles when D16 or D32 cycles are required on the VME bus.
	 * On the other hand, the bridge itself assures that the maximum data
	 * cycle configured क्रम the transfer is used and splits it
	 * स्वतःmatically क्रम non-aligned addresses, so we करोn't want the
	 * overhead of needlessly क्रमcing small transfers क्रम the entire cycle.
	 */
	अगर ((uपूर्णांकptr_t)addr & 0x1) अणु
		*(u8 *)buf = ioपढ़ो8(addr);
		करोne += 1;
		अगर (करोne == count)
			जाओ out;
	पूर्ण
	अगर ((uपूर्णांकptr_t)(addr + करोne) & 0x2) अणु
		अगर ((count - करोne) < 2) अणु
			*(u8 *)(buf + करोne) = ioपढ़ो8(addr + करोne);
			करोne += 1;
			जाओ out;
		पूर्ण अन्यथा अणु
			*(u16 *)(buf + करोne) = ioपढ़ो16(addr + करोne);
			करोne += 2;
		पूर्ण
	पूर्ण

	count32 = (count - करोne) & ~0x3;
	जबतक (करोne < count32) अणु
		*(u32 *)(buf + करोne) = ioपढ़ो32(addr + करोne);
		करोne += 4;
	पूर्ण

	अगर ((count - करोne) & 0x2) अणु
		*(u16 *)(buf + करोne) = ioपढ़ो16(addr + करोne);
		करोne += 2;
	पूर्ण
	अगर ((count - करोne) & 0x1) अणु
		*(u8 *)(buf + करोne) = ioपढ़ो8(addr + करोne);
		करोne += 1;
	पूर्ण
out:
	retval = count;
	spin_unlock(&image->lock);

	वापस retval;
पूर्ण

अटल sमाप_प्रकार ca91cx42_master_ग_लिखो(काष्ठा vme_master_resource *image,
	व्योम *buf, माप_प्रकार count, loff_t offset)
अणु
	sमाप_प्रकार retval;
	व्योम __iomem *addr = image->kern_base + offset;
	अचिन्हित पूर्णांक करोne = 0;
	अचिन्हित पूर्णांक count32;

	अगर (count == 0)
		वापस 0;

	spin_lock(&image->lock);

	/* Here we apply क्रम the same strategy we करो in master_पढ़ो
	 * function in order to assure the correct cycles.
	 */
	अगर ((uपूर्णांकptr_t)addr & 0x1) अणु
		ioग_लिखो8(*(u8 *)buf, addr);
		करोne += 1;
		अगर (करोne == count)
			जाओ out;
	पूर्ण
	अगर ((uपूर्णांकptr_t)(addr + करोne) & 0x2) अणु
		अगर ((count - करोne) < 2) अणु
			ioग_लिखो8(*(u8 *)(buf + करोne), addr + करोne);
			करोne += 1;
			जाओ out;
		पूर्ण अन्यथा अणु
			ioग_लिखो16(*(u16 *)(buf + करोne), addr + करोne);
			करोne += 2;
		पूर्ण
	पूर्ण

	count32 = (count - करोne) & ~0x3;
	जबतक (करोne < count32) अणु
		ioग_लिखो32(*(u32 *)(buf + करोne), addr + करोne);
		करोne += 4;
	पूर्ण

	अगर ((count - करोne) & 0x2) अणु
		ioग_लिखो16(*(u16 *)(buf + करोne), addr + करोne);
		करोne += 2;
	पूर्ण
	अगर ((count - करोne) & 0x1) अणु
		ioग_लिखो8(*(u8 *)(buf + करोne), addr + करोne);
		करोne += 1;
	पूर्ण
out:
	retval = count;

	spin_unlock(&image->lock);

	वापस retval;
पूर्ण

अटल अचिन्हित पूर्णांक ca91cx42_master_rmw(काष्ठा vme_master_resource *image,
	अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक compare, अचिन्हित पूर्णांक swap,
	loff_t offset)
अणु
	u32 result;
	uपूर्णांकptr_t pci_addr;
	काष्ठा ca91cx42_driver *bridge;
	काष्ठा device *dev;

	bridge = image->parent->driver_priv;
	dev = image->parent->parent;

	/* Find the PCI address that maps to the desired VME address */

	/* Locking as we can only करो one of these at a समय */
	mutex_lock(&bridge->vme_rmw);

	/* Lock image */
	spin_lock(&image->lock);

	pci_addr = (uपूर्णांकptr_t)image->kern_base + offset;

	/* Address must be 4-byte aligned */
	अगर (pci_addr & 0x3) अणु
		dev_err(dev, "RMW Address not 4-byte aligned\n");
		result = -EINVAL;
		जाओ out;
	पूर्ण

	/* Ensure RMW Disabled whilst configuring */
	ioग_लिखो32(0, bridge->base + SCYC_CTL);

	/* Configure रेजिस्टरs */
	ioग_लिखो32(mask, bridge->base + SCYC_EN);
	ioग_लिखो32(compare, bridge->base + SCYC_CMP);
	ioग_लिखो32(swap, bridge->base + SCYC_SWP);
	ioग_लिखो32(pci_addr, bridge->base + SCYC_ADDR);

	/* Enable RMW */
	ioग_लिखो32(CA91CX42_SCYC_CTL_CYC_RMW, bridge->base + SCYC_CTL);

	/* Kick process off with a पढ़ो to the required address. */
	result = ioपढ़ो32(image->kern_base + offset);

	/* Disable RMW */
	ioग_लिखो32(0, bridge->base + SCYC_CTL);

out:
	spin_unlock(&image->lock);

	mutex_unlock(&bridge->vme_rmw);

	वापस result;
पूर्ण

अटल पूर्णांक ca91cx42_dma_list_add(काष्ठा vme_dma_list *list,
	काष्ठा vme_dma_attr *src, काष्ठा vme_dma_attr *dest, माप_प्रकार count)
अणु
	काष्ठा ca91cx42_dma_entry *entry, *prev;
	काष्ठा vme_dma_pci *pci_attr;
	काष्ठा vme_dma_vme *vme_attr;
	dma_addr_t desc_ptr;
	पूर्णांक retval = 0;
	काष्ठा device *dev;

	dev = list->parent->parent->parent;

	/* XXX descriptor must be aligned on 64-bit boundaries */
	entry = kदो_स्मृति(माप(*entry), GFP_KERNEL);
	अगर (!entry) अणु
		retval = -ENOMEM;
		जाओ err_mem;
	पूर्ण

	/* Test descriptor alignment */
	अगर ((अचिन्हित दीर्घ)&entry->descriptor & CA91CX42_DCPP_M) अणु
		dev_err(dev, "Descriptor not aligned to 16 byte boundary as "
			"required: %p\n", &entry->descriptor);
		retval = -EINVAL;
		जाओ err_align;
	पूर्ण

	स_रखो(&entry->descriptor, 0, माप(entry->descriptor));

	अगर (dest->type == VME_DMA_VME) अणु
		entry->descriptor.dctl |= CA91CX42_DCTL_L2V;
		vme_attr = dest->निजी;
		pci_attr = src->निजी;
	पूर्ण अन्यथा अणु
		vme_attr = src->निजी;
		pci_attr = dest->निजी;
	पूर्ण

	/* Check we can करो fulfill required attributes */
	अगर ((vme_attr->aspace & ~(VME_A16 | VME_A24 | VME_A32 | VME_USER1 |
		VME_USER2)) != 0) अणु

		dev_err(dev, "Unsupported cycle type\n");
		retval = -EINVAL;
		जाओ err_aspace;
	पूर्ण

	अगर ((vme_attr->cycle & ~(VME_SCT | VME_BLT | VME_SUPER | VME_USER |
		VME_PROG | VME_DATA)) != 0) अणु

		dev_err(dev, "Unsupported cycle type\n");
		retval = -EINVAL;
		जाओ err_cycle;
	पूर्ण

	/* Check to see अगर we can fulfill source and destination */
	अगर (!(((src->type == VME_DMA_PCI) && (dest->type == VME_DMA_VME)) ||
		((src->type == VME_DMA_VME) && (dest->type == VME_DMA_PCI)))) अणु

		dev_err(dev, "Cannot perform transfer with this "
			"source-destination combination\n");
		retval = -EINVAL;
		जाओ err_direct;
	पूर्ण

	/* Setup cycle types */
	अगर (vme_attr->cycle & VME_BLT)
		entry->descriptor.dctl |= CA91CX42_DCTL_VCT_BLT;

	/* Setup data width */
	चयन (vme_attr->dwidth) अणु
	हाल VME_D8:
		entry->descriptor.dctl |= CA91CX42_DCTL_VDW_D8;
		अवरोध;
	हाल VME_D16:
		entry->descriptor.dctl |= CA91CX42_DCTL_VDW_D16;
		अवरोध;
	हाल VME_D32:
		entry->descriptor.dctl |= CA91CX42_DCTL_VDW_D32;
		अवरोध;
	हाल VME_D64:
		entry->descriptor.dctl |= CA91CX42_DCTL_VDW_D64;
		अवरोध;
	शेष:
		dev_err(dev, "Invalid data width\n");
		वापस -EINVAL;
	पूर्ण

	/* Setup address space */
	चयन (vme_attr->aspace) अणु
	हाल VME_A16:
		entry->descriptor.dctl |= CA91CX42_DCTL_VAS_A16;
		अवरोध;
	हाल VME_A24:
		entry->descriptor.dctl |= CA91CX42_DCTL_VAS_A24;
		अवरोध;
	हाल VME_A32:
		entry->descriptor.dctl |= CA91CX42_DCTL_VAS_A32;
		अवरोध;
	हाल VME_USER1:
		entry->descriptor.dctl |= CA91CX42_DCTL_VAS_USER1;
		अवरोध;
	हाल VME_USER2:
		entry->descriptor.dctl |= CA91CX42_DCTL_VAS_USER2;
		अवरोध;
	शेष:
		dev_err(dev, "Invalid address space\n");
		वापस -EINVAL;
		अवरोध;
	पूर्ण

	अगर (vme_attr->cycle & VME_SUPER)
		entry->descriptor.dctl |= CA91CX42_DCTL_SUPER_SUPR;
	अगर (vme_attr->cycle & VME_PROG)
		entry->descriptor.dctl |= CA91CX42_DCTL_PGM_PGM;

	entry->descriptor.dtbc = count;
	entry->descriptor.dla = pci_attr->address;
	entry->descriptor.dva = vme_attr->address;
	entry->descriptor.dcpp = CA91CX42_DCPP_शून्य;

	/* Add to list */
	list_add_tail(&entry->list, &list->entries);

	/* Fill out previous descriptors "Next Address" */
	अगर (entry->list.prev != &list->entries) अणु
		prev = list_entry(entry->list.prev, काष्ठा ca91cx42_dma_entry,
			list);
		/* We need the bus address क्रम the poपूर्णांकer */
		desc_ptr = virt_to_bus(&entry->descriptor);
		prev->descriptor.dcpp = desc_ptr & ~CA91CX42_DCPP_M;
	पूर्ण

	वापस 0;

err_cycle:
err_aspace:
err_direct:
err_align:
	kमुक्त(entry);
err_mem:
	वापस retval;
पूर्ण

अटल पूर्णांक ca91cx42_dma_busy(काष्ठा vme_bridge *ca91cx42_bridge)
अणु
	u32 पंचांगp;
	काष्ठा ca91cx42_driver *bridge;

	bridge = ca91cx42_bridge->driver_priv;

	पंचांगp = ioपढ़ो32(bridge->base + DGCS);

	अगर (पंचांगp & CA91CX42_DGCS_ACT)
		वापस 0;
	अन्यथा
		वापस 1;
पूर्ण

अटल पूर्णांक ca91cx42_dma_list_exec(काष्ठा vme_dma_list *list)
अणु
	काष्ठा vme_dma_resource *ctrlr;
	काष्ठा ca91cx42_dma_entry *entry;
	पूर्णांक retval;
	dma_addr_t bus_addr;
	u32 val;
	काष्ठा device *dev;
	काष्ठा ca91cx42_driver *bridge;

	ctrlr = list->parent;

	bridge = ctrlr->parent->driver_priv;
	dev = ctrlr->parent->parent;

	mutex_lock(&ctrlr->mtx);

	अगर (!(list_empty(&ctrlr->running))) अणु
		/*
		 * XXX We have an active DMA transfer and currently haven't
		 *     sorted out the mechanism क्रम "pending" DMA transfers.
		 *     Return busy.
		 */
		/* Need to add to pending here */
		mutex_unlock(&ctrlr->mtx);
		वापस -EBUSY;
	पूर्ण अन्यथा अणु
		list_add(&list->list, &ctrlr->running);
	पूर्ण

	/* Get first bus address and ग_लिखो पूर्णांकo रेजिस्टरs */
	entry = list_first_entry(&list->entries, काष्ठा ca91cx42_dma_entry,
		list);

	bus_addr = virt_to_bus(&entry->descriptor);

	mutex_unlock(&ctrlr->mtx);

	ioग_लिखो32(0, bridge->base + DTBC);
	ioग_लिखो32(bus_addr & ~CA91CX42_DCPP_M, bridge->base + DCPP);

	/* Start the operation */
	val = ioपढ़ो32(bridge->base + DGCS);

	/* XXX Could set VMEbus On and Off Counters here */
	val &= (CA91CX42_DGCS_VON_M | CA91CX42_DGCS_VOFF_M);

	val |= (CA91CX42_DGCS_CHAIN | CA91CX42_DGCS_STOP | CA91CX42_DGCS_HALT |
		CA91CX42_DGCS_DONE | CA91CX42_DGCS_LERR | CA91CX42_DGCS_VERR |
		CA91CX42_DGCS_PERR);

	ioग_लिखो32(val, bridge->base + DGCS);

	val |= CA91CX42_DGCS_GO;

	ioग_लिखो32(val, bridge->base + DGCS);

	retval = रुको_event_पूर्णांकerruptible(bridge->dma_queue,
					  ca91cx42_dma_busy(ctrlr->parent));

	अगर (retval) अणु
		val = ioपढ़ो32(bridge->base + DGCS);
		ioग_लिखो32(val | CA91CX42_DGCS_STOP_REQ, bridge->base + DGCS);
		/* Wait क्रम the operation to पात */
		रुको_event(bridge->dma_queue,
			   ca91cx42_dma_busy(ctrlr->parent));
		retval = -EINTR;
		जाओ निकास;
	पूर्ण

	/*
	 * Read status रेजिस्टर, this रेजिस्टर is valid until we kick off a
	 * new transfer.
	 */
	val = ioपढ़ो32(bridge->base + DGCS);

	अगर (val & (CA91CX42_DGCS_LERR | CA91CX42_DGCS_VERR |
		CA91CX42_DGCS_PERR)) अणु

		dev_err(dev, "ca91c042: DMA Error. DGCS=%08X\n", val);
		val = ioपढ़ो32(bridge->base + DCTL);
		retval = -EIO;
	पूर्ण

निकास:
	/* Remove list from running list */
	mutex_lock(&ctrlr->mtx);
	list_del(&list->list);
	mutex_unlock(&ctrlr->mtx);

	वापस retval;

पूर्ण

अटल पूर्णांक ca91cx42_dma_list_empty(काष्ठा vme_dma_list *list)
अणु
	काष्ठा list_head *pos, *temp;
	काष्ठा ca91cx42_dma_entry *entry;

	/* detach and मुक्त each entry */
	list_क्रम_each_safe(pos, temp, &list->entries) अणु
		list_del(pos);
		entry = list_entry(pos, काष्ठा ca91cx42_dma_entry, list);
		kमुक्त(entry);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * All 4 location monitors reside at the same base - this is thereक्रमe a
 * प्रणाली wide configuration.
 *
 * This करोes not enable the LM monitor - that should be करोne when the first
 * callback is attached and disabled when the last callback is हटाओd.
 */
अटल पूर्णांक ca91cx42_lm_set(काष्ठा vme_lm_resource *lm,
	अचिन्हित दीर्घ दीर्घ lm_base, u32 aspace, u32 cycle)
अणु
	u32 temp_base, lm_ctl = 0;
	पूर्णांक i;
	काष्ठा ca91cx42_driver *bridge;
	काष्ठा device *dev;

	bridge = lm->parent->driver_priv;
	dev = lm->parent->parent;

	/* Check the alignment of the location monitor */
	temp_base = (u32)lm_base;
	अगर (temp_base & 0xffff) अणु
		dev_err(dev, "Location monitor must be aligned to 64KB "
			"boundary");
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&lm->mtx);

	/* If we alपढ़ोy have a callback attached, we can't move it! */
	क्रम (i = 0; i < lm->monitors; i++) अणु
		अगर (bridge->lm_callback[i]) अणु
			mutex_unlock(&lm->mtx);
			dev_err(dev, "Location monitor callback attached, "
				"can't reset\n");
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	चयन (aspace) अणु
	हाल VME_A16:
		lm_ctl |= CA91CX42_LM_CTL_AS_A16;
		अवरोध;
	हाल VME_A24:
		lm_ctl |= CA91CX42_LM_CTL_AS_A24;
		अवरोध;
	हाल VME_A32:
		lm_ctl |= CA91CX42_LM_CTL_AS_A32;
		अवरोध;
	शेष:
		mutex_unlock(&lm->mtx);
		dev_err(dev, "Invalid address space\n");
		वापस -EINVAL;
		अवरोध;
	पूर्ण

	अगर (cycle & VME_SUPER)
		lm_ctl |= CA91CX42_LM_CTL_SUPR;
	अगर (cycle & VME_USER)
		lm_ctl |= CA91CX42_LM_CTL_NPRIV;
	अगर (cycle & VME_PROG)
		lm_ctl |= CA91CX42_LM_CTL_PGM;
	अगर (cycle & VME_DATA)
		lm_ctl |= CA91CX42_LM_CTL_DATA;

	ioग_लिखो32(lm_base, bridge->base + LM_BS);
	ioग_लिखो32(lm_ctl, bridge->base + LM_CTL);

	mutex_unlock(&lm->mtx);

	वापस 0;
पूर्ण

/* Get configuration of the callback monitor and वापस whether it is enabled
 * or disabled.
 */
अटल पूर्णांक ca91cx42_lm_get(काष्ठा vme_lm_resource *lm,
	अचिन्हित दीर्घ दीर्घ *lm_base, u32 *aspace, u32 *cycle)
अणु
	u32 lm_ctl, enabled = 0;
	काष्ठा ca91cx42_driver *bridge;

	bridge = lm->parent->driver_priv;

	mutex_lock(&lm->mtx);

	*lm_base = (अचिन्हित दीर्घ दीर्घ)ioपढ़ो32(bridge->base + LM_BS);
	lm_ctl = ioपढ़ो32(bridge->base + LM_CTL);

	अगर (lm_ctl & CA91CX42_LM_CTL_EN)
		enabled = 1;

	अगर ((lm_ctl & CA91CX42_LM_CTL_AS_M) == CA91CX42_LM_CTL_AS_A16)
		*aspace = VME_A16;
	अगर ((lm_ctl & CA91CX42_LM_CTL_AS_M) == CA91CX42_LM_CTL_AS_A24)
		*aspace = VME_A24;
	अगर ((lm_ctl & CA91CX42_LM_CTL_AS_M) == CA91CX42_LM_CTL_AS_A32)
		*aspace = VME_A32;

	*cycle = 0;
	अगर (lm_ctl & CA91CX42_LM_CTL_SUPR)
		*cycle |= VME_SUPER;
	अगर (lm_ctl & CA91CX42_LM_CTL_NPRIV)
		*cycle |= VME_USER;
	अगर (lm_ctl & CA91CX42_LM_CTL_PGM)
		*cycle |= VME_PROG;
	अगर (lm_ctl & CA91CX42_LM_CTL_DATA)
		*cycle |= VME_DATA;

	mutex_unlock(&lm->mtx);

	वापस enabled;
पूर्ण

/*
 * Attach a callback to a specअगरic location monitor.
 *
 * Callback will be passed the monitor triggered.
 */
अटल पूर्णांक ca91cx42_lm_attach(काष्ठा vme_lm_resource *lm, पूर्णांक monitor,
	व्योम (*callback)(व्योम *), व्योम *data)
अणु
	u32 lm_ctl, पंचांगp;
	काष्ठा ca91cx42_driver *bridge;
	काष्ठा device *dev;

	bridge = lm->parent->driver_priv;
	dev = lm->parent->parent;

	mutex_lock(&lm->mtx);

	/* Ensure that the location monitor is configured - need PGM or DATA */
	lm_ctl = ioपढ़ो32(bridge->base + LM_CTL);
	अगर ((lm_ctl & (CA91CX42_LM_CTL_PGM | CA91CX42_LM_CTL_DATA)) == 0) अणु
		mutex_unlock(&lm->mtx);
		dev_err(dev, "Location monitor not properly configured\n");
		वापस -EINVAL;
	पूर्ण

	/* Check that a callback isn't alपढ़ोy attached */
	अगर (bridge->lm_callback[monitor]) अणु
		mutex_unlock(&lm->mtx);
		dev_err(dev, "Existing callback attached\n");
		वापस -EBUSY;
	पूर्ण

	/* Attach callback */
	bridge->lm_callback[monitor] = callback;
	bridge->lm_data[monitor] = data;

	/* Enable Location Monitor पूर्णांकerrupt */
	पंचांगp = ioपढ़ो32(bridge->base + LINT_EN);
	पंचांगp |= CA91CX42_LINT_LM[monitor];
	ioग_लिखो32(पंचांगp, bridge->base + LINT_EN);

	/* Ensure that global Location Monitor Enable set */
	अगर ((lm_ctl & CA91CX42_LM_CTL_EN) == 0) अणु
		lm_ctl |= CA91CX42_LM_CTL_EN;
		ioग_लिखो32(lm_ctl, bridge->base + LM_CTL);
	पूर्ण

	mutex_unlock(&lm->mtx);

	वापस 0;
पूर्ण

/*
 * Detach a callback function क्रमn a specअगरic location monitor.
 */
अटल पूर्णांक ca91cx42_lm_detach(काष्ठा vme_lm_resource *lm, पूर्णांक monitor)
अणु
	u32 पंचांगp;
	काष्ठा ca91cx42_driver *bridge;

	bridge = lm->parent->driver_priv;

	mutex_lock(&lm->mtx);

	/* Disable Location Monitor and ensure previous पूर्णांकerrupts are clear */
	पंचांगp = ioपढ़ो32(bridge->base + LINT_EN);
	पंचांगp &= ~CA91CX42_LINT_LM[monitor];
	ioग_लिखो32(पंचांगp, bridge->base + LINT_EN);

	ioग_लिखो32(CA91CX42_LINT_LM[monitor],
		 bridge->base + LINT_STAT);

	/* Detach callback */
	bridge->lm_callback[monitor] = शून्य;
	bridge->lm_data[monitor] = शून्य;

	/* If all location monitors disabled, disable global Location Monitor */
	अगर ((पंचांगp & (CA91CX42_LINT_LM0 | CA91CX42_LINT_LM1 | CA91CX42_LINT_LM2 |
			CA91CX42_LINT_LM3)) == 0) अणु
		पंचांगp = ioपढ़ो32(bridge->base + LM_CTL);
		पंचांगp &= ~CA91CX42_LM_CTL_EN;
		ioग_लिखो32(पंचांगp, bridge->base + LM_CTL);
	पूर्ण

	mutex_unlock(&lm->mtx);

	वापस 0;
पूर्ण

अटल पूर्णांक ca91cx42_slot_get(काष्ठा vme_bridge *ca91cx42_bridge)
अणु
	u32 slot = 0;
	काष्ठा ca91cx42_driver *bridge;

	bridge = ca91cx42_bridge->driver_priv;

	अगर (!geoid) अणु
		slot = ioपढ़ो32(bridge->base + VCSR_BS);
		slot = ((slot & CA91CX42_VCSR_BS_SLOT_M) >> 27);
	पूर्ण अन्यथा
		slot = geoid;

	वापस (पूर्णांक)slot;

पूर्ण

अटल व्योम *ca91cx42_alloc_consistent(काष्ठा device *parent, माप_प्रकार size,
	dma_addr_t *dma)
अणु
	काष्ठा pci_dev *pdev;

	/* Find pci_dev container of dev */
	pdev = to_pci_dev(parent);

	वापस dma_alloc_coherent(&pdev->dev, size, dma, GFP_KERNEL);
पूर्ण

अटल व्योम ca91cx42_मुक्त_consistent(काष्ठा device *parent, माप_प्रकार size,
	व्योम *vaddr, dma_addr_t dma)
अणु
	काष्ठा pci_dev *pdev;

	/* Find pci_dev container of dev */
	pdev = to_pci_dev(parent);

	dma_मुक्त_coherent(&pdev->dev, size, vaddr, dma);
पूर्ण

/*
 * Configure CR/CSR space
 *
 * Access to the CR/CSR can be configured at घातer-up. The location of the
 * CR/CSR रेजिस्टरs in the CR/CSR address space is determined by the boards
 * Auto-ID or Geographic address. This function ensures that the winकरोw is
 * enabled at an offset consistent with the boards geopgraphic address.
 */
अटल पूर्णांक ca91cx42_crcsr_init(काष्ठा vme_bridge *ca91cx42_bridge,
	काष्ठा pci_dev *pdev)
अणु
	अचिन्हित पूर्णांक crcsr_addr;
	पूर्णांक पंचांगp, slot;
	काष्ठा ca91cx42_driver *bridge;

	bridge = ca91cx42_bridge->driver_priv;

	slot = ca91cx42_slot_get(ca91cx42_bridge);

	/* Write CSR Base Address अगर slot ID is supplied as a module param */
	अगर (geoid)
		ioग_लिखो32(geoid << 27, bridge->base + VCSR_BS);

	dev_info(&pdev->dev, "CR/CSR Offset: %d\n", slot);
	अगर (slot == 0) अणु
		dev_err(&pdev->dev, "Slot number is unset, not configuring "
			"CR/CSR space\n");
		वापस -EINVAL;
	पूर्ण

	/* Allocate mem क्रम CR/CSR image */
	bridge->crcsr_kernel = dma_alloc_coherent(&pdev->dev,
						  VME_CRCSR_BUF_SIZE,
						  &bridge->crcsr_bus, GFP_KERNEL);
	अगर (!bridge->crcsr_kernel) अणु
		dev_err(&pdev->dev, "Failed to allocate memory for CR/CSR "
			"image\n");
		वापस -ENOMEM;
	पूर्ण

	crcsr_addr = slot * (512 * 1024);
	ioग_लिखो32(bridge->crcsr_bus - crcsr_addr, bridge->base + VCSR_TO);

	पंचांगp = ioपढ़ो32(bridge->base + VCSR_CTL);
	पंचांगp |= CA91CX42_VCSR_CTL_EN;
	ioग_लिखो32(पंचांगp, bridge->base + VCSR_CTL);

	वापस 0;
पूर्ण

अटल व्योम ca91cx42_crcsr_निकास(काष्ठा vme_bridge *ca91cx42_bridge,
	काष्ठा pci_dev *pdev)
अणु
	u32 पंचांगp;
	काष्ठा ca91cx42_driver *bridge;

	bridge = ca91cx42_bridge->driver_priv;

	/* Turn off CR/CSR space */
	पंचांगp = ioपढ़ो32(bridge->base + VCSR_CTL);
	पंचांगp &= ~CA91CX42_VCSR_CTL_EN;
	ioग_लिखो32(पंचांगp, bridge->base + VCSR_CTL);

	/* Free image */
	ioग_लिखो32(0, bridge->base + VCSR_TO);

	dma_मुक्त_coherent(&pdev->dev, VME_CRCSR_BUF_SIZE,
			  bridge->crcsr_kernel, bridge->crcsr_bus);
पूर्ण

अटल पूर्णांक ca91cx42_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	पूर्णांक retval, i;
	u32 data;
	काष्ठा list_head *pos = शून्य, *n;
	काष्ठा vme_bridge *ca91cx42_bridge;
	काष्ठा ca91cx42_driver *ca91cx42_device;
	काष्ठा vme_master_resource *master_image;
	काष्ठा vme_slave_resource *slave_image;
	काष्ठा vme_dma_resource *dma_ctrlr;
	काष्ठा vme_lm_resource *lm;

	/* We want to support more than one of each bridge so we need to
	 * dynamically allocate the bridge काष्ठाure
	 */
	ca91cx42_bridge = kzalloc(माप(*ca91cx42_bridge), GFP_KERNEL);
	अगर (!ca91cx42_bridge) अणु
		retval = -ENOMEM;
		जाओ err_काष्ठा;
	पूर्ण
	vme_init_bridge(ca91cx42_bridge);

	ca91cx42_device = kzalloc(माप(*ca91cx42_device), GFP_KERNEL);
	अगर (!ca91cx42_device) अणु
		retval = -ENOMEM;
		जाओ err_driver;
	पूर्ण

	ca91cx42_bridge->driver_priv = ca91cx42_device;

	/* Enable the device */
	retval = pci_enable_device(pdev);
	अगर (retval) अणु
		dev_err(&pdev->dev, "Unable to enable device\n");
		जाओ err_enable;
	पूर्ण

	/* Map Registers */
	retval = pci_request_regions(pdev, driver_name);
	अगर (retval) अणु
		dev_err(&pdev->dev, "Unable to reserve resources\n");
		जाओ err_resource;
	पूर्ण

	/* map रेजिस्टरs in BAR 0 */
	ca91cx42_device->base = ioremap(pci_resource_start(pdev, 0),
		4096);
	अगर (!ca91cx42_device->base) अणु
		dev_err(&pdev->dev, "Unable to remap CRG region\n");
		retval = -EIO;
		जाओ err_remap;
	पूर्ण

	/* Check to see अगर the mapping worked out */
	data = ioपढ़ो32(ca91cx42_device->base + CA91CX42_PCI_ID) & 0x0000FFFF;
	अगर (data != PCI_VENDOR_ID_TUNDRA) अणु
		dev_err(&pdev->dev, "PCI_ID check failed\n");
		retval = -EIO;
		जाओ err_test;
	पूर्ण

	/* Initialize रुको queues & mutual exclusion flags */
	init_रुकोqueue_head(&ca91cx42_device->dma_queue);
	init_रुकोqueue_head(&ca91cx42_device->iack_queue);
	mutex_init(&ca91cx42_device->vme_पूर्णांक);
	mutex_init(&ca91cx42_device->vme_rmw);

	ca91cx42_bridge->parent = &pdev->dev;
	म_नकल(ca91cx42_bridge->name, driver_name);

	/* Setup IRQ */
	retval = ca91cx42_irq_init(ca91cx42_bridge);
	अगर (retval != 0) अणु
		dev_err(&pdev->dev, "Chip Initialization failed.\n");
		जाओ err_irq;
	पूर्ण

	/* Add master winकरोws to list */
	क्रम (i = 0; i < CA91C142_MAX_MASTER; i++) अणु
		master_image = kदो_स्मृति(माप(*master_image), GFP_KERNEL);
		अगर (!master_image) अणु
			retval = -ENOMEM;
			जाओ err_master;
		पूर्ण
		master_image->parent = ca91cx42_bridge;
		spin_lock_init(&master_image->lock);
		master_image->locked = 0;
		master_image->number = i;
		master_image->address_attr = VME_A16 | VME_A24 | VME_A32 |
			VME_CRCSR | VME_USER1 | VME_USER2;
		master_image->cycle_attr = VME_SCT | VME_BLT | VME_MBLT |
			VME_SUPER | VME_USER | VME_PROG | VME_DATA;
		master_image->width_attr = VME_D8 | VME_D16 | VME_D32 | VME_D64;
		स_रखो(&master_image->bus_resource, 0,
		       माप(master_image->bus_resource));
		master_image->kern_base  = शून्य;
		list_add_tail(&master_image->list,
			&ca91cx42_bridge->master_resources);
	पूर्ण

	/* Add slave winकरोws to list */
	क्रम (i = 0; i < CA91C142_MAX_SLAVE; i++) अणु
		slave_image = kदो_स्मृति(माप(*slave_image), GFP_KERNEL);
		अगर (!slave_image) अणु
			retval = -ENOMEM;
			जाओ err_slave;
		पूर्ण
		slave_image->parent = ca91cx42_bridge;
		mutex_init(&slave_image->mtx);
		slave_image->locked = 0;
		slave_image->number = i;
		slave_image->address_attr = VME_A24 | VME_A32 | VME_USER1 |
			VME_USER2;

		/* Only winकरोws 0 and 4 support A16 */
		अगर (i == 0 || i == 4)
			slave_image->address_attr |= VME_A16;

		slave_image->cycle_attr = VME_SCT | VME_BLT | VME_MBLT |
			VME_SUPER | VME_USER | VME_PROG | VME_DATA;
		list_add_tail(&slave_image->list,
			&ca91cx42_bridge->slave_resources);
	पूर्ण

	/* Add dma engines to list */
	क्रम (i = 0; i < CA91C142_MAX_DMA; i++) अणु
		dma_ctrlr = kदो_स्मृति(माप(*dma_ctrlr), GFP_KERNEL);
		अगर (!dma_ctrlr) अणु
			retval = -ENOMEM;
			जाओ err_dma;
		पूर्ण
		dma_ctrlr->parent = ca91cx42_bridge;
		mutex_init(&dma_ctrlr->mtx);
		dma_ctrlr->locked = 0;
		dma_ctrlr->number = i;
		dma_ctrlr->route_attr = VME_DMA_VME_TO_MEM |
			VME_DMA_MEM_TO_VME;
		INIT_LIST_HEAD(&dma_ctrlr->pending);
		INIT_LIST_HEAD(&dma_ctrlr->running);
		list_add_tail(&dma_ctrlr->list,
			&ca91cx42_bridge->dma_resources);
	पूर्ण

	/* Add location monitor to list */
	lm = kदो_स्मृति(माप(*lm), GFP_KERNEL);
	अगर (!lm) अणु
		retval = -ENOMEM;
		जाओ err_lm;
	पूर्ण
	lm->parent = ca91cx42_bridge;
	mutex_init(&lm->mtx);
	lm->locked = 0;
	lm->number = 1;
	lm->monitors = 4;
	list_add_tail(&lm->list, &ca91cx42_bridge->lm_resources);

	ca91cx42_bridge->slave_get = ca91cx42_slave_get;
	ca91cx42_bridge->slave_set = ca91cx42_slave_set;
	ca91cx42_bridge->master_get = ca91cx42_master_get;
	ca91cx42_bridge->master_set = ca91cx42_master_set;
	ca91cx42_bridge->master_पढ़ो = ca91cx42_master_पढ़ो;
	ca91cx42_bridge->master_ग_लिखो = ca91cx42_master_ग_लिखो;
	ca91cx42_bridge->master_rmw = ca91cx42_master_rmw;
	ca91cx42_bridge->dma_list_add = ca91cx42_dma_list_add;
	ca91cx42_bridge->dma_list_exec = ca91cx42_dma_list_exec;
	ca91cx42_bridge->dma_list_empty = ca91cx42_dma_list_empty;
	ca91cx42_bridge->irq_set = ca91cx42_irq_set;
	ca91cx42_bridge->irq_generate = ca91cx42_irq_generate;
	ca91cx42_bridge->lm_set = ca91cx42_lm_set;
	ca91cx42_bridge->lm_get = ca91cx42_lm_get;
	ca91cx42_bridge->lm_attach = ca91cx42_lm_attach;
	ca91cx42_bridge->lm_detach = ca91cx42_lm_detach;
	ca91cx42_bridge->slot_get = ca91cx42_slot_get;
	ca91cx42_bridge->alloc_consistent = ca91cx42_alloc_consistent;
	ca91cx42_bridge->मुक्त_consistent = ca91cx42_मुक्त_consistent;

	data = ioपढ़ो32(ca91cx42_device->base + MISC_CTL);
	dev_info(&pdev->dev, "Board is%s the VME system controller\n",
		(data & CA91CX42_MISC_CTL_SYSCON) ? "" : " not");
	dev_info(&pdev->dev, "Slot ID is %d\n",
		ca91cx42_slot_get(ca91cx42_bridge));

	अगर (ca91cx42_crcsr_init(ca91cx42_bridge, pdev))
		dev_err(&pdev->dev, "CR/CSR configuration failed.\n");

	/* Need to save ca91cx42_bridge poपूर्णांकer locally in link list क्रम use in
	 * ca91cx42_हटाओ()
	 */
	retval = vme_रेजिस्टर_bridge(ca91cx42_bridge);
	अगर (retval != 0) अणु
		dev_err(&pdev->dev, "Chip Registration failed.\n");
		जाओ err_reg;
	पूर्ण

	pci_set_drvdata(pdev, ca91cx42_bridge);

	वापस 0;

err_reg:
	ca91cx42_crcsr_निकास(ca91cx42_bridge, pdev);
err_lm:
	/* resources are stored in link list */
	list_क्रम_each_safe(pos, n, &ca91cx42_bridge->lm_resources) अणु
		lm = list_entry(pos, काष्ठा vme_lm_resource, list);
		list_del(pos);
		kमुक्त(lm);
	पूर्ण
err_dma:
	/* resources are stored in link list */
	list_क्रम_each_safe(pos, n, &ca91cx42_bridge->dma_resources) अणु
		dma_ctrlr = list_entry(pos, काष्ठा vme_dma_resource, list);
		list_del(pos);
		kमुक्त(dma_ctrlr);
	पूर्ण
err_slave:
	/* resources are stored in link list */
	list_क्रम_each_safe(pos, n, &ca91cx42_bridge->slave_resources) अणु
		slave_image = list_entry(pos, काष्ठा vme_slave_resource, list);
		list_del(pos);
		kमुक्त(slave_image);
	पूर्ण
err_master:
	/* resources are stored in link list */
	list_क्रम_each_safe(pos, n, &ca91cx42_bridge->master_resources) अणु
		master_image = list_entry(pos, काष्ठा vme_master_resource,
			list);
		list_del(pos);
		kमुक्त(master_image);
	पूर्ण

	ca91cx42_irq_निकास(ca91cx42_device, pdev);
err_irq:
err_test:
	iounmap(ca91cx42_device->base);
err_remap:
	pci_release_regions(pdev);
err_resource:
	pci_disable_device(pdev);
err_enable:
	kमुक्त(ca91cx42_device);
err_driver:
	kमुक्त(ca91cx42_bridge);
err_काष्ठा:
	वापस retval;

पूर्ण

अटल व्योम ca91cx42_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा list_head *pos = शून्य, *n;
	काष्ठा vme_master_resource *master_image;
	काष्ठा vme_slave_resource *slave_image;
	काष्ठा vme_dma_resource *dma_ctrlr;
	काष्ठा vme_lm_resource *lm;
	काष्ठा ca91cx42_driver *bridge;
	काष्ठा vme_bridge *ca91cx42_bridge = pci_get_drvdata(pdev);

	bridge = ca91cx42_bridge->driver_priv;


	/* Turn off Ints */
	ioग_लिखो32(0, bridge->base + LINT_EN);

	/* Turn off the winकरोws */
	ioग_लिखो32(0x00800000, bridge->base + LSI0_CTL);
	ioग_लिखो32(0x00800000, bridge->base + LSI1_CTL);
	ioग_लिखो32(0x00800000, bridge->base + LSI2_CTL);
	ioग_लिखो32(0x00800000, bridge->base + LSI3_CTL);
	ioग_लिखो32(0x00800000, bridge->base + LSI4_CTL);
	ioग_लिखो32(0x00800000, bridge->base + LSI5_CTL);
	ioग_लिखो32(0x00800000, bridge->base + LSI6_CTL);
	ioग_लिखो32(0x00800000, bridge->base + LSI7_CTL);
	ioग_लिखो32(0x00F00000, bridge->base + VSI0_CTL);
	ioग_लिखो32(0x00F00000, bridge->base + VSI1_CTL);
	ioग_लिखो32(0x00F00000, bridge->base + VSI2_CTL);
	ioग_लिखो32(0x00F00000, bridge->base + VSI3_CTL);
	ioग_लिखो32(0x00F00000, bridge->base + VSI4_CTL);
	ioग_लिखो32(0x00F00000, bridge->base + VSI5_CTL);
	ioग_लिखो32(0x00F00000, bridge->base + VSI6_CTL);
	ioग_लिखो32(0x00F00000, bridge->base + VSI7_CTL);

	vme_unरेजिस्टर_bridge(ca91cx42_bridge);

	ca91cx42_crcsr_निकास(ca91cx42_bridge, pdev);

	/* resources are stored in link list */
	list_क्रम_each_safe(pos, n, &ca91cx42_bridge->lm_resources) अणु
		lm = list_entry(pos, काष्ठा vme_lm_resource, list);
		list_del(pos);
		kमुक्त(lm);
	पूर्ण

	/* resources are stored in link list */
	list_क्रम_each_safe(pos, n, &ca91cx42_bridge->dma_resources) अणु
		dma_ctrlr = list_entry(pos, काष्ठा vme_dma_resource, list);
		list_del(pos);
		kमुक्त(dma_ctrlr);
	पूर्ण

	/* resources are stored in link list */
	list_क्रम_each_safe(pos, n, &ca91cx42_bridge->slave_resources) अणु
		slave_image = list_entry(pos, काष्ठा vme_slave_resource, list);
		list_del(pos);
		kमुक्त(slave_image);
	पूर्ण

	/* resources are stored in link list */
	list_क्रम_each_safe(pos, n, &ca91cx42_bridge->master_resources) अणु
		master_image = list_entry(pos, काष्ठा vme_master_resource,
			list);
		list_del(pos);
		kमुक्त(master_image);
	पूर्ण

	ca91cx42_irq_निकास(bridge, pdev);

	iounmap(bridge->base);

	pci_release_regions(pdev);

	pci_disable_device(pdev);

	kमुक्त(ca91cx42_bridge);
पूर्ण

module_pci_driver(ca91cx42_driver);

MODULE_PARM_DESC(geoid, "Override geographical addressing");
module_param(geoid, पूर्णांक, 0);

MODULE_DESCRIPTION("VME driver for the Tundra Universe II VME bridge");
MODULE_LICENSE("GPL");
