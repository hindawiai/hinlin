<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Support क्रम the Tundra TSI148 VME-PCI Bridge Chip
 *
 * Author: Martyn Welch <martyn.welch@ge.com>
 * Copyright 2008 GE Intelligent Platक्रमms Embedded Systems, Inc.
 *
 * Based on work by Tom Armistead and Ajit Prem
 * Copyright 2004 Motorola Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/mm.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/proc_fs.h>
#समावेश <linux/pci.h>
#समावेश <linux/poll.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/समय.स>
#समावेश <linux/पन.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/byteorder/generic.h>
#समावेश <linux/vme.h>

#समावेश "../vme_bridge.h"
#समावेश "vme_tsi148.h"

अटल पूर्णांक tsi148_probe(काष्ठा pci_dev *, स्थिर काष्ठा pci_device_id *);
अटल व्योम tsi148_हटाओ(काष्ठा pci_dev *);


/* Module parameter */
अटल bool err_chk;
अटल पूर्णांक geoid;

अटल स्थिर अक्षर driver_name[] = "vme_tsi148";

अटल स्थिर काष्ठा pci_device_id tsi148_ids[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_TUNDRA, PCI_DEVICE_ID_TUNDRA_TSI148) पूर्ण,
	अणु पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(pci, tsi148_ids);

अटल काष्ठा pci_driver tsi148_driver = अणु
	.name = driver_name,
	.id_table = tsi148_ids,
	.probe = tsi148_probe,
	.हटाओ = tsi148_हटाओ,
पूर्ण;

अटल व्योम reg_join(अचिन्हित पूर्णांक high, अचिन्हित पूर्णांक low,
	अचिन्हित दीर्घ दीर्घ *variable)
अणु
	*variable = (अचिन्हित दीर्घ दीर्घ)high << 32;
	*variable |= (अचिन्हित दीर्घ दीर्घ)low;
पूर्ण

अटल व्योम reg_split(अचिन्हित दीर्घ दीर्घ variable, अचिन्हित पूर्णांक *high,
	अचिन्हित पूर्णांक *low)
अणु
	*low = (अचिन्हित पूर्णांक)variable & 0xFFFFFFFF;
	*high = (अचिन्हित पूर्णांक)(variable >> 32);
पूर्ण

/*
 * Wakes up DMA queue.
 */
अटल u32 tsi148_DMA_irqhandler(काष्ठा tsi148_driver *bridge,
	पूर्णांक channel_mask)
अणु
	u32 serviced = 0;

	अगर (channel_mask & TSI148_LCSR_INTS_DMA0S) अणु
		wake_up(&bridge->dma_queue[0]);
		serviced |= TSI148_LCSR_INTC_DMA0C;
	पूर्ण
	अगर (channel_mask & TSI148_LCSR_INTS_DMA1S) अणु
		wake_up(&bridge->dma_queue[1]);
		serviced |= TSI148_LCSR_INTC_DMA1C;
	पूर्ण

	वापस serviced;
पूर्ण

/*
 * Wake up location monitor queue
 */
अटल u32 tsi148_LM_irqhandler(काष्ठा tsi148_driver *bridge, u32 stat)
अणु
	पूर्णांक i;
	u32 serviced = 0;

	क्रम (i = 0; i < 4; i++) अणु
		अगर (stat & TSI148_LCSR_INTS_LMS[i]) अणु
			/* We only enable पूर्णांकerrupts अगर the callback is set */
			bridge->lm_callback[i](bridge->lm_data[i]);
			serviced |= TSI148_LCSR_INTC_LMC[i];
		पूर्ण
	पूर्ण

	वापस serviced;
पूर्ण

/*
 * Wake up mail box queue.
 *
 * XXX This functionality is not exposed up though API.
 */
अटल u32 tsi148_MB_irqhandler(काष्ठा vme_bridge *tsi148_bridge, u32 stat)
अणु
	पूर्णांक i;
	u32 val;
	u32 serviced = 0;
	काष्ठा tsi148_driver *bridge;

	bridge = tsi148_bridge->driver_priv;

	क्रम (i = 0; i < 4; i++) अणु
		अगर (stat & TSI148_LCSR_INTS_MBS[i]) अणु
			val = ioपढ़ो32be(bridge->base +	TSI148_GCSR_MBOX[i]);
			dev_err(tsi148_bridge->parent, "VME Mailbox %d received"
				": 0x%x\n", i, val);
			serviced |= TSI148_LCSR_INTC_MBC[i];
		पूर्ण
	पूर्ण

	वापस serviced;
पूर्ण

/*
 * Display error & status message when PERR (PCI) exception पूर्णांकerrupt occurs.
 */
अटल u32 tsi148_PERR_irqhandler(काष्ठा vme_bridge *tsi148_bridge)
अणु
	काष्ठा tsi148_driver *bridge;

	bridge = tsi148_bridge->driver_priv;

	dev_err(tsi148_bridge->parent, "PCI Exception at address: 0x%08x:%08x, "
		"attributes: %08x\n",
		ioपढ़ो32be(bridge->base + TSI148_LCSR_EDPAU),
		ioपढ़ो32be(bridge->base + TSI148_LCSR_EDPAL),
		ioपढ़ो32be(bridge->base + TSI148_LCSR_EDPAT));

	dev_err(tsi148_bridge->parent, "PCI-X attribute reg: %08x, PCI-X split "
		"completion reg: %08x\n",
		ioपढ़ो32be(bridge->base + TSI148_LCSR_EDPXA),
		ioपढ़ो32be(bridge->base + TSI148_LCSR_EDPXS));

	ioग_लिखो32be(TSI148_LCSR_EDPAT_EDPCL, bridge->base + TSI148_LCSR_EDPAT);

	वापस TSI148_LCSR_INTC_PERRC;
पूर्ण

/*
 * Save address and status when VME error पूर्णांकerrupt occurs.
 */
अटल u32 tsi148_VERR_irqhandler(काष्ठा vme_bridge *tsi148_bridge)
अणु
	अचिन्हित पूर्णांक error_addr_high, error_addr_low;
	अचिन्हित दीर्घ दीर्घ error_addr;
	u32 error_attrib;
	पूर्णांक error_am;
	काष्ठा tsi148_driver *bridge;

	bridge = tsi148_bridge->driver_priv;

	error_addr_high = ioपढ़ो32be(bridge->base + TSI148_LCSR_VEAU);
	error_addr_low = ioपढ़ो32be(bridge->base + TSI148_LCSR_VEAL);
	error_attrib = ioपढ़ो32be(bridge->base + TSI148_LCSR_VEAT);
	error_am = (error_attrib & TSI148_LCSR_VEAT_AM_M) >> 8;

	reg_join(error_addr_high, error_addr_low, &error_addr);

	/* Check क्रम exception रेजिस्टर overflow (we have lost error data) */
	अगर (error_attrib & TSI148_LCSR_VEAT_Vखातापूर्ण) अणु
		dev_err(tsi148_bridge->parent, "VME Bus Exception Overflow "
			"Occurred\n");
	पूर्ण

	अगर (err_chk)
		vme_bus_error_handler(tsi148_bridge, error_addr, error_am);
	अन्यथा
		dev_err(tsi148_bridge->parent,
			"VME Bus Error at address: 0x%llx, attributes: %08x\n",
			error_addr, error_attrib);

	/* Clear Status */
	ioग_लिखो32be(TSI148_LCSR_VEAT_VESCL, bridge->base + TSI148_LCSR_VEAT);

	वापस TSI148_LCSR_INTC_VERRC;
पूर्ण

/*
 * Wake up IACK queue.
 */
अटल u32 tsi148_IACK_irqhandler(काष्ठा tsi148_driver *bridge)
अणु
	wake_up(&bridge->iack_queue);

	वापस TSI148_LCSR_INTC_IACKC;
पूर्ण

/*
 * Calling VME bus पूर्णांकerrupt callback अगर provided.
 */
अटल u32 tsi148_VIRQ_irqhandler(काष्ठा vme_bridge *tsi148_bridge,
	u32 stat)
अणु
	पूर्णांक vec, i, serviced = 0;
	काष्ठा tsi148_driver *bridge;

	bridge = tsi148_bridge->driver_priv;

	क्रम (i = 7; i > 0; i--) अणु
		अगर (stat & (1 << i)) अणु
			/*
			 * Note: Even though the रेजिस्टरs are defined as
			 * 32-bits in the spec, we only want to issue 8-bit
			 * IACK cycles on the bus, पढ़ो from offset 3.
			 */
			vec = ioपढ़ो8(bridge->base + TSI148_LCSR_VIACK[i] + 3);

			vme_irq_handler(tsi148_bridge, i, vec);

			serviced |= (1 << i);
		पूर्ण
	पूर्ण

	वापस serviced;
पूर्ण

/*
 * Top level पूर्णांकerrupt handler.  Clears appropriate पूर्णांकerrupt status bits and
 * then calls appropriate sub handler(s).
 */
अटल irqवापस_t tsi148_irqhandler(पूर्णांक irq, व्योम *ptr)
अणु
	u32 stat, enable, serviced = 0;
	काष्ठा vme_bridge *tsi148_bridge;
	काष्ठा tsi148_driver *bridge;

	tsi148_bridge = ptr;

	bridge = tsi148_bridge->driver_priv;

	/* Determine which पूर्णांकerrupts are unmasked and set */
	enable = ioपढ़ो32be(bridge->base + TSI148_LCSR_INTEO);
	stat = ioपढ़ो32be(bridge->base + TSI148_LCSR_INTS);

	/* Only look at unmasked पूर्णांकerrupts */
	stat &= enable;

	अगर (unlikely(!stat))
		वापस IRQ_NONE;

	/* Call subhandlers as appropriate */
	/* DMA irqs */
	अगर (stat & (TSI148_LCSR_INTS_DMA1S | TSI148_LCSR_INTS_DMA0S))
		serviced |= tsi148_DMA_irqhandler(bridge, stat);

	/* Location monitor irqs */
	अगर (stat & (TSI148_LCSR_INTS_LM3S | TSI148_LCSR_INTS_LM2S |
			TSI148_LCSR_INTS_LM1S | TSI148_LCSR_INTS_LM0S))
		serviced |= tsi148_LM_irqhandler(bridge, stat);

	/* Mail box irqs */
	अगर (stat & (TSI148_LCSR_INTS_MB3S | TSI148_LCSR_INTS_MB2S |
			TSI148_LCSR_INTS_MB1S | TSI148_LCSR_INTS_MB0S))
		serviced |= tsi148_MB_irqhandler(tsi148_bridge, stat);

	/* PCI bus error */
	अगर (stat & TSI148_LCSR_INTS_PERRS)
		serviced |= tsi148_PERR_irqhandler(tsi148_bridge);

	/* VME bus error */
	अगर (stat & TSI148_LCSR_INTS_VERRS)
		serviced |= tsi148_VERR_irqhandler(tsi148_bridge);

	/* IACK irq */
	अगर (stat & TSI148_LCSR_INTS_IACKS)
		serviced |= tsi148_IACK_irqhandler(bridge);

	/* VME bus irqs */
	अगर (stat & (TSI148_LCSR_INTS_IRQ7S | TSI148_LCSR_INTS_IRQ6S |
			TSI148_LCSR_INTS_IRQ5S | TSI148_LCSR_INTS_IRQ4S |
			TSI148_LCSR_INTS_IRQ3S | TSI148_LCSR_INTS_IRQ2S |
			TSI148_LCSR_INTS_IRQ1S))
		serviced |= tsi148_VIRQ_irqhandler(tsi148_bridge, stat);

	/* Clear serviced पूर्णांकerrupts */
	ioग_लिखो32be(serviced, bridge->base + TSI148_LCSR_INTC);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक tsi148_irq_init(काष्ठा vme_bridge *tsi148_bridge)
अणु
	पूर्णांक result;
	अचिन्हित पूर्णांक पंचांगp;
	काष्ठा pci_dev *pdev;
	काष्ठा tsi148_driver *bridge;

	pdev = to_pci_dev(tsi148_bridge->parent);

	bridge = tsi148_bridge->driver_priv;

	result = request_irq(pdev->irq,
			     tsi148_irqhandler,
			     IRQF_SHARED,
			     driver_name, tsi148_bridge);
	अगर (result) अणु
		dev_err(tsi148_bridge->parent, "Can't get assigned pci irq "
			"vector %02X\n", pdev->irq);
		वापस result;
	पूर्ण

	/* Enable and unmask पूर्णांकerrupts */
	पंचांगp = TSI148_LCSR_INTEO_DMA1EO | TSI148_LCSR_INTEO_DMA0EO |
		TSI148_LCSR_INTEO_MB3EO | TSI148_LCSR_INTEO_MB2EO |
		TSI148_LCSR_INTEO_MB1EO | TSI148_LCSR_INTEO_MB0EO |
		TSI148_LCSR_INTEO_PERREO | TSI148_LCSR_INTEO_VERREO |
		TSI148_LCSR_INTEO_IACKEO;

	/* This leaves the following पूर्णांकerrupts masked.
	 * TSI148_LCSR_INTEO_VIEEO
	 * TSI148_LCSR_INTEO_SYSFLEO
	 * TSI148_LCSR_INTEO_ACFLEO
	 */

	/* Don't enable Location Monitor पूर्णांकerrupts here - they will be
	 * enabled when the location monitors are properly configured and
	 * a callback has been attached.
	 * TSI148_LCSR_INTEO_LM0EO
	 * TSI148_LCSR_INTEO_LM1EO
	 * TSI148_LCSR_INTEO_LM2EO
	 * TSI148_LCSR_INTEO_LM3EO
	 */

	/* Don't enable VME पूर्णांकerrupts until we add a handler, अन्यथा the board
	 * will respond to it and we करोn't want that unless it knows how to
	 * properly deal with it.
	 * TSI148_LCSR_INTEO_IRQ7EO
	 * TSI148_LCSR_INTEO_IRQ6EO
	 * TSI148_LCSR_INTEO_IRQ5EO
	 * TSI148_LCSR_INTEO_IRQ4EO
	 * TSI148_LCSR_INTEO_IRQ3EO
	 * TSI148_LCSR_INTEO_IRQ2EO
	 * TSI148_LCSR_INTEO_IRQ1EO
	 */

	ioग_लिखो32be(पंचांगp, bridge->base + TSI148_LCSR_INTEO);
	ioग_लिखो32be(पंचांगp, bridge->base + TSI148_LCSR_INTEN);

	वापस 0;
पूर्ण

अटल व्योम tsi148_irq_निकास(काष्ठा vme_bridge *tsi148_bridge,
	काष्ठा pci_dev *pdev)
अणु
	काष्ठा tsi148_driver *bridge = tsi148_bridge->driver_priv;

	/* Turn off पूर्णांकerrupts */
	ioग_लिखो32be(0x0, bridge->base + TSI148_LCSR_INTEO);
	ioग_लिखो32be(0x0, bridge->base + TSI148_LCSR_INTEN);

	/* Clear all पूर्णांकerrupts */
	ioग_लिखो32be(0xFFFFFFFF, bridge->base + TSI148_LCSR_INTC);

	/* Detach पूर्णांकerrupt handler */
	मुक्त_irq(pdev->irq, tsi148_bridge);
पूर्ण

/*
 * Check to see अगर an IACk has been received, वापस true (1) or false (0).
 */
अटल पूर्णांक tsi148_iack_received(काष्ठा tsi148_driver *bridge)
अणु
	u32 पंचांगp;

	पंचांगp = ioपढ़ो32be(bridge->base + TSI148_LCSR_VICR);

	अगर (पंचांगp & TSI148_LCSR_VICR_IRQS)
		वापस 0;
	अन्यथा
		वापस 1;
पूर्ण

/*
 * Configure VME पूर्णांकerrupt
 */
अटल व्योम tsi148_irq_set(काष्ठा vme_bridge *tsi148_bridge, पूर्णांक level,
	पूर्णांक state, पूर्णांक sync)
अणु
	काष्ठा pci_dev *pdev;
	u32 पंचांगp;
	काष्ठा tsi148_driver *bridge;

	bridge = tsi148_bridge->driver_priv;

	/* We need to करो the ordering dअगरferently क्रम enabling and disabling */
	अगर (state == 0) अणु
		पंचांगp = ioपढ़ो32be(bridge->base + TSI148_LCSR_INTEN);
		पंचांगp &= ~TSI148_LCSR_INTEN_IRQEN[level - 1];
		ioग_लिखो32be(पंचांगp, bridge->base + TSI148_LCSR_INTEN);

		पंचांगp = ioपढ़ो32be(bridge->base + TSI148_LCSR_INTEO);
		पंचांगp &= ~TSI148_LCSR_INTEO_IRQEO[level - 1];
		ioग_लिखो32be(पंचांगp, bridge->base + TSI148_LCSR_INTEO);

		अगर (sync != 0) अणु
			pdev = to_pci_dev(tsi148_bridge->parent);
			synchronize_irq(pdev->irq);
		पूर्ण
	पूर्ण अन्यथा अणु
		पंचांगp = ioपढ़ो32be(bridge->base + TSI148_LCSR_INTEO);
		पंचांगp |= TSI148_LCSR_INTEO_IRQEO[level - 1];
		ioग_लिखो32be(पंचांगp, bridge->base + TSI148_LCSR_INTEO);

		पंचांगp = ioपढ़ो32be(bridge->base + TSI148_LCSR_INTEN);
		पंचांगp |= TSI148_LCSR_INTEN_IRQEN[level - 1];
		ioग_लिखो32be(पंचांगp, bridge->base + TSI148_LCSR_INTEN);
	पूर्ण
पूर्ण

/*
 * Generate a VME bus पूर्णांकerrupt at the requested level & vector. Wait क्रम
 * पूर्णांकerrupt to be acked.
 */
अटल पूर्णांक tsi148_irq_generate(काष्ठा vme_bridge *tsi148_bridge, पूर्णांक level,
	पूर्णांक statid)
अणु
	u32 पंचांगp;
	काष्ठा tsi148_driver *bridge;

	bridge = tsi148_bridge->driver_priv;

	mutex_lock(&bridge->vme_पूर्णांक);

	/* Read VICR रेजिस्टर */
	पंचांगp = ioपढ़ो32be(bridge->base + TSI148_LCSR_VICR);

	/* Set Status/ID */
	पंचांगp = (पंचांगp & ~TSI148_LCSR_VICR_STID_M) |
		(statid & TSI148_LCSR_VICR_STID_M);
	ioग_लिखो32be(पंचांगp, bridge->base + TSI148_LCSR_VICR);

	/* Assert VMEbus IRQ */
	पंचांगp = पंचांगp | TSI148_LCSR_VICR_IRQL[level];
	ioग_लिखो32be(पंचांगp, bridge->base + TSI148_LCSR_VICR);

	/* XXX Consider implementing a समयout? */
	रुको_event_पूर्णांकerruptible(bridge->iack_queue,
		tsi148_iack_received(bridge));

	mutex_unlock(&bridge->vme_पूर्णांक);

	वापस 0;
पूर्ण

/*
 * Initialize a slave winकरोw with the requested attributes.
 */
अटल पूर्णांक tsi148_slave_set(काष्ठा vme_slave_resource *image, पूर्णांक enabled,
	अचिन्हित दीर्घ दीर्घ vme_base, अचिन्हित दीर्घ दीर्घ size,
	dma_addr_t pci_base, u32 aspace, u32 cycle)
अणु
	अचिन्हित पूर्णांक i, addr = 0, granularity = 0;
	अचिन्हित पूर्णांक temp_ctl = 0;
	अचिन्हित पूर्णांक vme_base_low, vme_base_high;
	अचिन्हित पूर्णांक vme_bound_low, vme_bound_high;
	अचिन्हित पूर्णांक pci_offset_low, pci_offset_high;
	अचिन्हित दीर्घ दीर्घ vme_bound, pci_offset;
	काष्ठा vme_bridge *tsi148_bridge;
	काष्ठा tsi148_driver *bridge;

	tsi148_bridge = image->parent;
	bridge = tsi148_bridge->driver_priv;

	i = image->number;

	चयन (aspace) अणु
	हाल VME_A16:
		granularity = 0x10;
		addr |= TSI148_LCSR_ITAT_AS_A16;
		अवरोध;
	हाल VME_A24:
		granularity = 0x1000;
		addr |= TSI148_LCSR_ITAT_AS_A24;
		अवरोध;
	हाल VME_A32:
		granularity = 0x10000;
		addr |= TSI148_LCSR_ITAT_AS_A32;
		अवरोध;
	हाल VME_A64:
		granularity = 0x10000;
		addr |= TSI148_LCSR_ITAT_AS_A64;
		अवरोध;
	शेष:
		dev_err(tsi148_bridge->parent, "Invalid address space\n");
		वापस -EINVAL;
	पूर्ण

	/* Convert 64-bit variables to 2x 32-bit variables */
	reg_split(vme_base, &vme_base_high, &vme_base_low);

	/*
	 * Bound address is a valid address क्रम the winकरोw, adjust
	 * accordingly
	 */
	vme_bound = vme_base + size - granularity;
	reg_split(vme_bound, &vme_bound_high, &vme_bound_low);
	pci_offset = (अचिन्हित दीर्घ दीर्घ)pci_base - vme_base;
	reg_split(pci_offset, &pci_offset_high, &pci_offset_low);

	अगर (vme_base_low & (granularity - 1)) अणु
		dev_err(tsi148_bridge->parent, "Invalid VME base alignment\n");
		वापस -EINVAL;
	पूर्ण
	अगर (vme_bound_low & (granularity - 1)) अणु
		dev_err(tsi148_bridge->parent, "Invalid VME bound alignment\n");
		वापस -EINVAL;
	पूर्ण
	अगर (pci_offset_low & (granularity - 1)) अणु
		dev_err(tsi148_bridge->parent, "Invalid PCI Offset "
			"alignment\n");
		वापस -EINVAL;
	पूर्ण

	/*  Disable जबतक we are mucking around */
	temp_ctl = ioपढ़ो32be(bridge->base + TSI148_LCSR_IT[i] +
		TSI148_LCSR_OFFSET_ITAT);
	temp_ctl &= ~TSI148_LCSR_ITAT_EN;
	ioग_लिखो32be(temp_ctl, bridge->base + TSI148_LCSR_IT[i] +
		TSI148_LCSR_OFFSET_ITAT);

	/* Setup mapping */
	ioग_लिखो32be(vme_base_high, bridge->base + TSI148_LCSR_IT[i] +
		TSI148_LCSR_OFFSET_ITSAU);
	ioग_लिखो32be(vme_base_low, bridge->base + TSI148_LCSR_IT[i] +
		TSI148_LCSR_OFFSET_ITSAL);
	ioग_लिखो32be(vme_bound_high, bridge->base + TSI148_LCSR_IT[i] +
		TSI148_LCSR_OFFSET_ITEAU);
	ioग_लिखो32be(vme_bound_low, bridge->base + TSI148_LCSR_IT[i] +
		TSI148_LCSR_OFFSET_ITEAL);
	ioग_लिखो32be(pci_offset_high, bridge->base + TSI148_LCSR_IT[i] +
		TSI148_LCSR_OFFSET_ITOFU);
	ioग_लिखो32be(pci_offset_low, bridge->base + TSI148_LCSR_IT[i] +
		TSI148_LCSR_OFFSET_ITOFL);

	/* Setup 2eSST speeds */
	temp_ctl &= ~TSI148_LCSR_ITAT_2eSSTM_M;
	चयन (cycle & (VME_2eSST160 | VME_2eSST267 | VME_2eSST320)) अणु
	हाल VME_2eSST160:
		temp_ctl |= TSI148_LCSR_ITAT_2eSSTM_160;
		अवरोध;
	हाल VME_2eSST267:
		temp_ctl |= TSI148_LCSR_ITAT_2eSSTM_267;
		अवरोध;
	हाल VME_2eSST320:
		temp_ctl |= TSI148_LCSR_ITAT_2eSSTM_320;
		अवरोध;
	पूर्ण

	/* Setup cycle types */
	temp_ctl &= ~(0x1F << 7);
	अगर (cycle & VME_BLT)
		temp_ctl |= TSI148_LCSR_ITAT_BLT;
	अगर (cycle & VME_MBLT)
		temp_ctl |= TSI148_LCSR_ITAT_MBLT;
	अगर (cycle & VME_2eVME)
		temp_ctl |= TSI148_LCSR_ITAT_2eVME;
	अगर (cycle & VME_2eSST)
		temp_ctl |= TSI148_LCSR_ITAT_2eSST;
	अगर (cycle & VME_2eSSTB)
		temp_ctl |= TSI148_LCSR_ITAT_2eSSTB;

	/* Setup address space */
	temp_ctl &= ~TSI148_LCSR_ITAT_AS_M;
	temp_ctl |= addr;

	temp_ctl &= ~0xF;
	अगर (cycle & VME_SUPER)
		temp_ctl |= TSI148_LCSR_ITAT_SUPR ;
	अगर (cycle & VME_USER)
		temp_ctl |= TSI148_LCSR_ITAT_NPRIV;
	अगर (cycle & VME_PROG)
		temp_ctl |= TSI148_LCSR_ITAT_PGM;
	अगर (cycle & VME_DATA)
		temp_ctl |= TSI148_LCSR_ITAT_DATA;

	/* Write ctl reg without enable */
	ioग_लिखो32be(temp_ctl, bridge->base + TSI148_LCSR_IT[i] +
		TSI148_LCSR_OFFSET_ITAT);

	अगर (enabled)
		temp_ctl |= TSI148_LCSR_ITAT_EN;

	ioग_लिखो32be(temp_ctl, bridge->base + TSI148_LCSR_IT[i] +
		TSI148_LCSR_OFFSET_ITAT);

	वापस 0;
पूर्ण

/*
 * Get slave winकरोw configuration.
 */
अटल पूर्णांक tsi148_slave_get(काष्ठा vme_slave_resource *image, पूर्णांक *enabled,
	अचिन्हित दीर्घ दीर्घ *vme_base, अचिन्हित दीर्घ दीर्घ *size,
	dma_addr_t *pci_base, u32 *aspace, u32 *cycle)
अणु
	अचिन्हित पूर्णांक i, granularity = 0, ctl = 0;
	अचिन्हित पूर्णांक vme_base_low, vme_base_high;
	अचिन्हित पूर्णांक vme_bound_low, vme_bound_high;
	अचिन्हित पूर्णांक pci_offset_low, pci_offset_high;
	अचिन्हित दीर्घ दीर्घ vme_bound, pci_offset;
	काष्ठा tsi148_driver *bridge;

	bridge = image->parent->driver_priv;

	i = image->number;

	/* Read रेजिस्टरs */
	ctl = ioपढ़ो32be(bridge->base + TSI148_LCSR_IT[i] +
		TSI148_LCSR_OFFSET_ITAT);

	vme_base_high = ioपढ़ो32be(bridge->base + TSI148_LCSR_IT[i] +
		TSI148_LCSR_OFFSET_ITSAU);
	vme_base_low = ioपढ़ो32be(bridge->base + TSI148_LCSR_IT[i] +
		TSI148_LCSR_OFFSET_ITSAL);
	vme_bound_high = ioपढ़ो32be(bridge->base + TSI148_LCSR_IT[i] +
		TSI148_LCSR_OFFSET_ITEAU);
	vme_bound_low = ioपढ़ो32be(bridge->base + TSI148_LCSR_IT[i] +
		TSI148_LCSR_OFFSET_ITEAL);
	pci_offset_high = ioपढ़ो32be(bridge->base + TSI148_LCSR_IT[i] +
		TSI148_LCSR_OFFSET_ITOFU);
	pci_offset_low = ioपढ़ो32be(bridge->base + TSI148_LCSR_IT[i] +
		TSI148_LCSR_OFFSET_ITOFL);

	/* Convert 64-bit variables to 2x 32-bit variables */
	reg_join(vme_base_high, vme_base_low, vme_base);
	reg_join(vme_bound_high, vme_bound_low, &vme_bound);
	reg_join(pci_offset_high, pci_offset_low, &pci_offset);

	*pci_base = (dma_addr_t)(*vme_base + pci_offset);

	*enabled = 0;
	*aspace = 0;
	*cycle = 0;

	अगर (ctl & TSI148_LCSR_ITAT_EN)
		*enabled = 1;

	अगर ((ctl & TSI148_LCSR_ITAT_AS_M) == TSI148_LCSR_ITAT_AS_A16) अणु
		granularity = 0x10;
		*aspace |= VME_A16;
	पूर्ण
	अगर ((ctl & TSI148_LCSR_ITAT_AS_M) == TSI148_LCSR_ITAT_AS_A24) अणु
		granularity = 0x1000;
		*aspace |= VME_A24;
	पूर्ण
	अगर ((ctl & TSI148_LCSR_ITAT_AS_M) == TSI148_LCSR_ITAT_AS_A32) अणु
		granularity = 0x10000;
		*aspace |= VME_A32;
	पूर्ण
	अगर ((ctl & TSI148_LCSR_ITAT_AS_M) == TSI148_LCSR_ITAT_AS_A64) अणु
		granularity = 0x10000;
		*aspace |= VME_A64;
	पूर्ण

	/* Need granularity beक्रमe we set the size */
	*size = (अचिन्हित दीर्घ दीर्घ)((vme_bound - *vme_base) + granularity);


	अगर ((ctl & TSI148_LCSR_ITAT_2eSSTM_M) == TSI148_LCSR_ITAT_2eSSTM_160)
		*cycle |= VME_2eSST160;
	अगर ((ctl & TSI148_LCSR_ITAT_2eSSTM_M) == TSI148_LCSR_ITAT_2eSSTM_267)
		*cycle |= VME_2eSST267;
	अगर ((ctl & TSI148_LCSR_ITAT_2eSSTM_M) == TSI148_LCSR_ITAT_2eSSTM_320)
		*cycle |= VME_2eSST320;

	अगर (ctl & TSI148_LCSR_ITAT_BLT)
		*cycle |= VME_BLT;
	अगर (ctl & TSI148_LCSR_ITAT_MBLT)
		*cycle |= VME_MBLT;
	अगर (ctl & TSI148_LCSR_ITAT_2eVME)
		*cycle |= VME_2eVME;
	अगर (ctl & TSI148_LCSR_ITAT_2eSST)
		*cycle |= VME_2eSST;
	अगर (ctl & TSI148_LCSR_ITAT_2eSSTB)
		*cycle |= VME_2eSSTB;

	अगर (ctl & TSI148_LCSR_ITAT_SUPR)
		*cycle |= VME_SUPER;
	अगर (ctl & TSI148_LCSR_ITAT_NPRIV)
		*cycle |= VME_USER;
	अगर (ctl & TSI148_LCSR_ITAT_PGM)
		*cycle |= VME_PROG;
	अगर (ctl & TSI148_LCSR_ITAT_DATA)
		*cycle |= VME_DATA;

	वापस 0;
पूर्ण

/*
 * Allocate and map PCI Resource
 */
अटल पूर्णांक tsi148_alloc_resource(काष्ठा vme_master_resource *image,
	अचिन्हित दीर्घ दीर्घ size)
अणु
	अचिन्हित दीर्घ दीर्घ existing_size;
	पूर्णांक retval = 0;
	काष्ठा pci_dev *pdev;
	काष्ठा vme_bridge *tsi148_bridge;

	tsi148_bridge = image->parent;

	pdev = to_pci_dev(tsi148_bridge->parent);

	existing_size = (अचिन्हित दीर्घ दीर्घ)(image->bus_resource.end -
		image->bus_resource.start);

	/* If the existing size is OK, वापस */
	अगर ((size != 0) && (existing_size == (size - 1)))
		वापस 0;

	अगर (existing_size != 0) अणु
		iounmap(image->kern_base);
		image->kern_base = शून्य;
		kमुक्त(image->bus_resource.name);
		release_resource(&image->bus_resource);
		स_रखो(&image->bus_resource, 0, माप(image->bus_resource));
	पूर्ण

	/* Exit here अगर size is zero */
	अगर (size == 0)
		वापस 0;

	अगर (!image->bus_resource.name) अणु
		image->bus_resource.name = kदो_स्मृति(VMENAMSIZ+3, GFP_ATOMIC);
		अगर (!image->bus_resource.name) अणु
			retval = -ENOMEM;
			जाओ err_name;
		पूर्ण
	पूर्ण

	प्र_लिखो((अक्षर *)image->bus_resource.name, "%s.%d", tsi148_bridge->name,
		image->number);

	image->bus_resource.start = 0;
	image->bus_resource.end = (अचिन्हित दीर्घ)size;
	image->bus_resource.flags = IORESOURCE_MEM;

	retval = pci_bus_alloc_resource(pdev->bus,
		&image->bus_resource, size, 0x10000, PCIBIOS_MIN_MEM,
		0, शून्य, शून्य);
	अगर (retval) अणु
		dev_err(tsi148_bridge->parent, "Failed to allocate mem "
			"resource for window %d size 0x%lx start 0x%lx\n",
			image->number, (अचिन्हित दीर्घ)size,
			(अचिन्हित दीर्घ)image->bus_resource.start);
		जाओ err_resource;
	पूर्ण

	image->kern_base = ioremap(
		image->bus_resource.start, size);
	अगर (!image->kern_base) अणु
		dev_err(tsi148_bridge->parent, "Failed to remap resource\n");
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
अटल व्योम tsi148_मुक्त_resource(काष्ठा vme_master_resource *image)
अणु
	iounmap(image->kern_base);
	image->kern_base = शून्य;
	release_resource(&image->bus_resource);
	kमुक्त(image->bus_resource.name);
	स_रखो(&image->bus_resource, 0, माप(image->bus_resource));
पूर्ण

/*
 * Set the attributes of an outbound winकरोw.
 */
अटल पूर्णांक tsi148_master_set(काष्ठा vme_master_resource *image, पूर्णांक enabled,
	अचिन्हित दीर्घ दीर्घ vme_base, अचिन्हित दीर्घ दीर्घ size, u32 aspace,
	u32 cycle, u32 dwidth)
अणु
	पूर्णांक retval = 0;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक temp_ctl = 0;
	अचिन्हित पूर्णांक pci_base_low, pci_base_high;
	अचिन्हित पूर्णांक pci_bound_low, pci_bound_high;
	अचिन्हित पूर्णांक vme_offset_low, vme_offset_high;
	अचिन्हित दीर्घ दीर्घ pci_bound, vme_offset, pci_base;
	काष्ठा vme_bridge *tsi148_bridge;
	काष्ठा tsi148_driver *bridge;
	काष्ठा pci_bus_region region;
	काष्ठा pci_dev *pdev;

	tsi148_bridge = image->parent;

	bridge = tsi148_bridge->driver_priv;

	pdev = to_pci_dev(tsi148_bridge->parent);

	/* Verअगरy input data */
	अगर (vme_base & 0xFFFF) अणु
		dev_err(tsi148_bridge->parent, "Invalid VME Window "
			"alignment\n");
		retval = -EINVAL;
		जाओ err_winकरोw;
	पूर्ण

	अगर ((size == 0) && (enabled != 0)) अणु
		dev_err(tsi148_bridge->parent, "Size must be non-zero for "
			"enabled windows\n");
		retval = -EINVAL;
		जाओ err_winकरोw;
	पूर्ण

	spin_lock(&image->lock);

	/* Let's allocate the resource here rather than further up the stack as
	 * it aव्योमs pushing loads of bus dependent stuff up the stack. If size
	 * is zero, any existing resource will be मुक्तd.
	 */
	retval = tsi148_alloc_resource(image, size);
	अगर (retval) अणु
		spin_unlock(&image->lock);
		dev_err(tsi148_bridge->parent, "Unable to allocate memory for "
			"resource\n");
		जाओ err_res;
	पूर्ण

	अगर (size == 0) अणु
		pci_base = 0;
		pci_bound = 0;
		vme_offset = 0;
	पूर्ण अन्यथा अणु
		pcibios_resource_to_bus(pdev->bus, &region,
					&image->bus_resource);
		pci_base = region.start;

		/*
		 * Bound address is a valid address क्रम the winकरोw, adjust
		 * according to winकरोw granularity.
		 */
		pci_bound = pci_base + (size - 0x10000);
		vme_offset = vme_base - pci_base;
	पूर्ण

	/* Convert 64-bit variables to 2x 32-bit variables */
	reg_split(pci_base, &pci_base_high, &pci_base_low);
	reg_split(pci_bound, &pci_bound_high, &pci_bound_low);
	reg_split(vme_offset, &vme_offset_high, &vme_offset_low);

	अगर (pci_base_low & 0xFFFF) अणु
		spin_unlock(&image->lock);
		dev_err(tsi148_bridge->parent, "Invalid PCI base alignment\n");
		retval = -EINVAL;
		जाओ err_gran;
	पूर्ण
	अगर (pci_bound_low & 0xFFFF) अणु
		spin_unlock(&image->lock);
		dev_err(tsi148_bridge->parent, "Invalid PCI bound alignment\n");
		retval = -EINVAL;
		जाओ err_gran;
	पूर्ण
	अगर (vme_offset_low & 0xFFFF) अणु
		spin_unlock(&image->lock);
		dev_err(tsi148_bridge->parent, "Invalid VME Offset "
			"alignment\n");
		retval = -EINVAL;
		जाओ err_gran;
	पूर्ण

	i = image->number;

	/* Disable जबतक we are mucking around */
	temp_ctl = ioपढ़ो32be(bridge->base + TSI148_LCSR_OT[i] +
		TSI148_LCSR_OFFSET_OTAT);
	temp_ctl &= ~TSI148_LCSR_OTAT_EN;
	ioग_लिखो32be(temp_ctl, bridge->base + TSI148_LCSR_OT[i] +
		TSI148_LCSR_OFFSET_OTAT);

	/* Setup 2eSST speeds */
	temp_ctl &= ~TSI148_LCSR_OTAT_2eSSTM_M;
	चयन (cycle & (VME_2eSST160 | VME_2eSST267 | VME_2eSST320)) अणु
	हाल VME_2eSST160:
		temp_ctl |= TSI148_LCSR_OTAT_2eSSTM_160;
		अवरोध;
	हाल VME_2eSST267:
		temp_ctl |= TSI148_LCSR_OTAT_2eSSTM_267;
		अवरोध;
	हाल VME_2eSST320:
		temp_ctl |= TSI148_LCSR_OTAT_2eSSTM_320;
		अवरोध;
	पूर्ण

	/* Setup cycle types */
	अगर (cycle & VME_BLT) अणु
		temp_ctl &= ~TSI148_LCSR_OTAT_TM_M;
		temp_ctl |= TSI148_LCSR_OTAT_TM_BLT;
	पूर्ण
	अगर (cycle & VME_MBLT) अणु
		temp_ctl &= ~TSI148_LCSR_OTAT_TM_M;
		temp_ctl |= TSI148_LCSR_OTAT_TM_MBLT;
	पूर्ण
	अगर (cycle & VME_2eVME) अणु
		temp_ctl &= ~TSI148_LCSR_OTAT_TM_M;
		temp_ctl |= TSI148_LCSR_OTAT_TM_2eVME;
	पूर्ण
	अगर (cycle & VME_2eSST) अणु
		temp_ctl &= ~TSI148_LCSR_OTAT_TM_M;
		temp_ctl |= TSI148_LCSR_OTAT_TM_2eSST;
	पूर्ण
	अगर (cycle & VME_2eSSTB) अणु
		dev_warn(tsi148_bridge->parent, "Currently not setting "
			"Broadcast Select Registers\n");
		temp_ctl &= ~TSI148_LCSR_OTAT_TM_M;
		temp_ctl |= TSI148_LCSR_OTAT_TM_2eSSTB;
	पूर्ण

	/* Setup data width */
	temp_ctl &= ~TSI148_LCSR_OTAT_DBW_M;
	चयन (dwidth) अणु
	हाल VME_D16:
		temp_ctl |= TSI148_LCSR_OTAT_DBW_16;
		अवरोध;
	हाल VME_D32:
		temp_ctl |= TSI148_LCSR_OTAT_DBW_32;
		अवरोध;
	शेष:
		spin_unlock(&image->lock);
		dev_err(tsi148_bridge->parent, "Invalid data width\n");
		retval = -EINVAL;
		जाओ err_dwidth;
	पूर्ण

	/* Setup address space */
	temp_ctl &= ~TSI148_LCSR_OTAT_AMODE_M;
	चयन (aspace) अणु
	हाल VME_A16:
		temp_ctl |= TSI148_LCSR_OTAT_AMODE_A16;
		अवरोध;
	हाल VME_A24:
		temp_ctl |= TSI148_LCSR_OTAT_AMODE_A24;
		अवरोध;
	हाल VME_A32:
		temp_ctl |= TSI148_LCSR_OTAT_AMODE_A32;
		अवरोध;
	हाल VME_A64:
		temp_ctl |= TSI148_LCSR_OTAT_AMODE_A64;
		अवरोध;
	हाल VME_CRCSR:
		temp_ctl |= TSI148_LCSR_OTAT_AMODE_CRCSR;
		अवरोध;
	हाल VME_USER1:
		temp_ctl |= TSI148_LCSR_OTAT_AMODE_USER1;
		अवरोध;
	हाल VME_USER2:
		temp_ctl |= TSI148_LCSR_OTAT_AMODE_USER2;
		अवरोध;
	हाल VME_USER3:
		temp_ctl |= TSI148_LCSR_OTAT_AMODE_USER3;
		अवरोध;
	हाल VME_USER4:
		temp_ctl |= TSI148_LCSR_OTAT_AMODE_USER4;
		अवरोध;
	शेष:
		spin_unlock(&image->lock);
		dev_err(tsi148_bridge->parent, "Invalid address space\n");
		retval = -EINVAL;
		जाओ err_aspace;
	पूर्ण

	temp_ctl &= ~(3<<4);
	अगर (cycle & VME_SUPER)
		temp_ctl |= TSI148_LCSR_OTAT_SUP;
	अगर (cycle & VME_PROG)
		temp_ctl |= TSI148_LCSR_OTAT_PGM;

	/* Setup mapping */
	ioग_लिखो32be(pci_base_high, bridge->base + TSI148_LCSR_OT[i] +
		TSI148_LCSR_OFFSET_OTSAU);
	ioग_लिखो32be(pci_base_low, bridge->base + TSI148_LCSR_OT[i] +
		TSI148_LCSR_OFFSET_OTSAL);
	ioग_लिखो32be(pci_bound_high, bridge->base + TSI148_LCSR_OT[i] +
		TSI148_LCSR_OFFSET_OTEAU);
	ioग_लिखो32be(pci_bound_low, bridge->base + TSI148_LCSR_OT[i] +
		TSI148_LCSR_OFFSET_OTEAL);
	ioग_लिखो32be(vme_offset_high, bridge->base + TSI148_LCSR_OT[i] +
		TSI148_LCSR_OFFSET_OTOFU);
	ioग_लिखो32be(vme_offset_low, bridge->base + TSI148_LCSR_OT[i] +
		TSI148_LCSR_OFFSET_OTOFL);

	/* Write ctl reg without enable */
	ioग_लिखो32be(temp_ctl, bridge->base + TSI148_LCSR_OT[i] +
		TSI148_LCSR_OFFSET_OTAT);

	अगर (enabled)
		temp_ctl |= TSI148_LCSR_OTAT_EN;

	ioग_लिखो32be(temp_ctl, bridge->base + TSI148_LCSR_OT[i] +
		TSI148_LCSR_OFFSET_OTAT);

	spin_unlock(&image->lock);
	वापस 0;

err_aspace:
err_dwidth:
err_gran:
	tsi148_मुक्त_resource(image);
err_res:
err_winकरोw:
	वापस retval;

पूर्ण

/*
 * Set the attributes of an outbound winकरोw.
 *
 * XXX Not parsing prefetch inक्रमmation.
 */
अटल पूर्णांक __tsi148_master_get(काष्ठा vme_master_resource *image, पूर्णांक *enabled,
	अचिन्हित दीर्घ दीर्घ *vme_base, अचिन्हित दीर्घ दीर्घ *size, u32 *aspace,
	u32 *cycle, u32 *dwidth)
अणु
	अचिन्हित पूर्णांक i, ctl;
	अचिन्हित पूर्णांक pci_base_low, pci_base_high;
	अचिन्हित पूर्णांक pci_bound_low, pci_bound_high;
	अचिन्हित पूर्णांक vme_offset_low, vme_offset_high;

	अचिन्हित दीर्घ दीर्घ pci_base, pci_bound, vme_offset;
	काष्ठा tsi148_driver *bridge;

	bridge = image->parent->driver_priv;

	i = image->number;

	ctl = ioपढ़ो32be(bridge->base + TSI148_LCSR_OT[i] +
		TSI148_LCSR_OFFSET_OTAT);

	pci_base_high = ioपढ़ो32be(bridge->base + TSI148_LCSR_OT[i] +
		TSI148_LCSR_OFFSET_OTSAU);
	pci_base_low = ioपढ़ो32be(bridge->base + TSI148_LCSR_OT[i] +
		TSI148_LCSR_OFFSET_OTSAL);
	pci_bound_high = ioपढ़ो32be(bridge->base + TSI148_LCSR_OT[i] +
		TSI148_LCSR_OFFSET_OTEAU);
	pci_bound_low = ioपढ़ो32be(bridge->base + TSI148_LCSR_OT[i] +
		TSI148_LCSR_OFFSET_OTEAL);
	vme_offset_high = ioपढ़ो32be(bridge->base + TSI148_LCSR_OT[i] +
		TSI148_LCSR_OFFSET_OTOFU);
	vme_offset_low = ioपढ़ो32be(bridge->base + TSI148_LCSR_OT[i] +
		TSI148_LCSR_OFFSET_OTOFL);

	/* Convert 64-bit variables to 2x 32-bit variables */
	reg_join(pci_base_high, pci_base_low, &pci_base);
	reg_join(pci_bound_high, pci_bound_low, &pci_bound);
	reg_join(vme_offset_high, vme_offset_low, &vme_offset);

	*vme_base = pci_base + vme_offset;
	*size = (अचिन्हित दीर्घ दीर्घ)(pci_bound - pci_base) + 0x10000;

	*enabled = 0;
	*aspace = 0;
	*cycle = 0;
	*dwidth = 0;

	अगर (ctl & TSI148_LCSR_OTAT_EN)
		*enabled = 1;

	/* Setup address space */
	अगर ((ctl & TSI148_LCSR_OTAT_AMODE_M) == TSI148_LCSR_OTAT_AMODE_A16)
		*aspace |= VME_A16;
	अगर ((ctl & TSI148_LCSR_OTAT_AMODE_M) == TSI148_LCSR_OTAT_AMODE_A24)
		*aspace |= VME_A24;
	अगर ((ctl & TSI148_LCSR_OTAT_AMODE_M) == TSI148_LCSR_OTAT_AMODE_A32)
		*aspace |= VME_A32;
	अगर ((ctl & TSI148_LCSR_OTAT_AMODE_M) == TSI148_LCSR_OTAT_AMODE_A64)
		*aspace |= VME_A64;
	अगर ((ctl & TSI148_LCSR_OTAT_AMODE_M) == TSI148_LCSR_OTAT_AMODE_CRCSR)
		*aspace |= VME_CRCSR;
	अगर ((ctl & TSI148_LCSR_OTAT_AMODE_M) == TSI148_LCSR_OTAT_AMODE_USER1)
		*aspace |= VME_USER1;
	अगर ((ctl & TSI148_LCSR_OTAT_AMODE_M) == TSI148_LCSR_OTAT_AMODE_USER2)
		*aspace |= VME_USER2;
	अगर ((ctl & TSI148_LCSR_OTAT_AMODE_M) == TSI148_LCSR_OTAT_AMODE_USER3)
		*aspace |= VME_USER3;
	अगर ((ctl & TSI148_LCSR_OTAT_AMODE_M) == TSI148_LCSR_OTAT_AMODE_USER4)
		*aspace |= VME_USER4;

	/* Setup 2eSST speeds */
	अगर ((ctl & TSI148_LCSR_OTAT_2eSSTM_M) == TSI148_LCSR_OTAT_2eSSTM_160)
		*cycle |= VME_2eSST160;
	अगर ((ctl & TSI148_LCSR_OTAT_2eSSTM_M) == TSI148_LCSR_OTAT_2eSSTM_267)
		*cycle |= VME_2eSST267;
	अगर ((ctl & TSI148_LCSR_OTAT_2eSSTM_M) == TSI148_LCSR_OTAT_2eSSTM_320)
		*cycle |= VME_2eSST320;

	/* Setup cycle types */
	अगर ((ctl & TSI148_LCSR_OTAT_TM_M) == TSI148_LCSR_OTAT_TM_SCT)
		*cycle |= VME_SCT;
	अगर ((ctl & TSI148_LCSR_OTAT_TM_M) == TSI148_LCSR_OTAT_TM_BLT)
		*cycle |= VME_BLT;
	अगर ((ctl & TSI148_LCSR_OTAT_TM_M) == TSI148_LCSR_OTAT_TM_MBLT)
		*cycle |= VME_MBLT;
	अगर ((ctl & TSI148_LCSR_OTAT_TM_M) == TSI148_LCSR_OTAT_TM_2eVME)
		*cycle |= VME_2eVME;
	अगर ((ctl & TSI148_LCSR_OTAT_TM_M) == TSI148_LCSR_OTAT_TM_2eSST)
		*cycle |= VME_2eSST;
	अगर ((ctl & TSI148_LCSR_OTAT_TM_M) == TSI148_LCSR_OTAT_TM_2eSSTB)
		*cycle |= VME_2eSSTB;

	अगर (ctl & TSI148_LCSR_OTAT_SUP)
		*cycle |= VME_SUPER;
	अन्यथा
		*cycle |= VME_USER;

	अगर (ctl & TSI148_LCSR_OTAT_PGM)
		*cycle |= VME_PROG;
	अन्यथा
		*cycle |= VME_DATA;

	/* Setup data width */
	अगर ((ctl & TSI148_LCSR_OTAT_DBW_M) == TSI148_LCSR_OTAT_DBW_16)
		*dwidth = VME_D16;
	अगर ((ctl & TSI148_LCSR_OTAT_DBW_M) == TSI148_LCSR_OTAT_DBW_32)
		*dwidth = VME_D32;

	वापस 0;
पूर्ण


अटल पूर्णांक tsi148_master_get(काष्ठा vme_master_resource *image, पूर्णांक *enabled,
	अचिन्हित दीर्घ दीर्घ *vme_base, अचिन्हित दीर्घ दीर्घ *size, u32 *aspace,
	u32 *cycle, u32 *dwidth)
अणु
	पूर्णांक retval;

	spin_lock(&image->lock);

	retval = __tsi148_master_get(image, enabled, vme_base, size, aspace,
		cycle, dwidth);

	spin_unlock(&image->lock);

	वापस retval;
पूर्ण

अटल sमाप_प्रकार tsi148_master_पढ़ो(काष्ठा vme_master_resource *image, व्योम *buf,
	माप_प्रकार count, loff_t offset)
अणु
	पूर्णांक retval, enabled;
	अचिन्हित दीर्घ दीर्घ vme_base, size;
	u32 aspace, cycle, dwidth;
	काष्ठा vme_error_handler *handler = शून्य;
	काष्ठा vme_bridge *tsi148_bridge;
	व्योम __iomem *addr = image->kern_base + offset;
	अचिन्हित पूर्णांक करोne = 0;
	अचिन्हित पूर्णांक count32;

	tsi148_bridge = image->parent;

	spin_lock(&image->lock);

	अगर (err_chk) अणु
		__tsi148_master_get(image, &enabled, &vme_base, &size, &aspace,
				    &cycle, &dwidth);
		handler = vme_रेजिस्टर_error_handler(tsi148_bridge, aspace,
						     vme_base + offset, count);
		अगर (!handler) अणु
			spin_unlock(&image->lock);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

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

	अगर (err_chk) अणु
		अगर (handler->num_errors) अणु
			dev_err(image->parent->parent,
				"First VME read error detected an at address 0x%llx\n",
				handler->first_error);
			retval = handler->first_error - (vme_base + offset);
		पूर्ण
		vme_unरेजिस्टर_error_handler(handler);
	पूर्ण

	spin_unlock(&image->lock);

	वापस retval;
पूर्ण


अटल sमाप_प्रकार tsi148_master_ग_लिखो(काष्ठा vme_master_resource *image, व्योम *buf,
	माप_प्रकार count, loff_t offset)
अणु
	पूर्णांक retval = 0, enabled;
	अचिन्हित दीर्घ दीर्घ vme_base, size;
	u32 aspace, cycle, dwidth;
	व्योम __iomem *addr = image->kern_base + offset;
	अचिन्हित पूर्णांक करोne = 0;
	अचिन्हित पूर्णांक count32;

	काष्ठा vme_error_handler *handler = शून्य;
	काष्ठा vme_bridge *tsi148_bridge;
	काष्ठा tsi148_driver *bridge;

	tsi148_bridge = image->parent;

	bridge = tsi148_bridge->driver_priv;

	spin_lock(&image->lock);

	अगर (err_chk) अणु
		__tsi148_master_get(image, &enabled, &vme_base, &size, &aspace,
				    &cycle, &dwidth);
		handler = vme_रेजिस्टर_error_handler(tsi148_bridge, aspace,
						     vme_base + offset, count);
		अगर (!handler) अणु
			spin_unlock(&image->lock);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

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

	/*
	 * Writes are posted. We need to करो a पढ़ो on the VME bus to flush out
	 * all of the ग_लिखोs beक्रमe we check क्रम errors. We can't guarantee
	 * that पढ़ोing the data we have just written is safe. It is believed
	 * that there isn't any पढ़ो, ग_लिखो re-ordering, so we can पढ़ो any
	 * location in VME space, so lets पढ़ो the Device ID from the tsi148's
	 * own रेजिस्टरs as mapped पूर्णांकo CR/CSR space.
	 *
	 * We check क्रम saved errors in the written address range/space.
	 */

	अगर (err_chk) अणु
		ioपढ़ो16(bridge->flush_image->kern_base + 0x7F000);

		अगर (handler->num_errors) अणु
			dev_warn(tsi148_bridge->parent,
				 "First VME write error detected an at address 0x%llx\n",
				 handler->first_error);
			retval = handler->first_error - (vme_base + offset);
		पूर्ण
		vme_unरेजिस्टर_error_handler(handler);
	पूर्ण

	spin_unlock(&image->lock);

	वापस retval;
पूर्ण

/*
 * Perक्रमm an RMW cycle on the VME bus.
 *
 * Requires a previously configured master winकरोw, वापसs final value.
 */
अटल अचिन्हित पूर्णांक tsi148_master_rmw(काष्ठा vme_master_resource *image,
	अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक compare, अचिन्हित पूर्णांक swap,
	loff_t offset)
अणु
	अचिन्हित दीर्घ दीर्घ pci_addr;
	अचिन्हित पूर्णांक pci_addr_high, pci_addr_low;
	u32 पंचांगp, result;
	पूर्णांक i;
	काष्ठा tsi148_driver *bridge;

	bridge = image->parent->driver_priv;

	/* Find the PCI address that maps to the desired VME address */
	i = image->number;

	/* Locking as we can only करो one of these at a समय */
	mutex_lock(&bridge->vme_rmw);

	/* Lock image */
	spin_lock(&image->lock);

	pci_addr_high = ioपढ़ो32be(bridge->base + TSI148_LCSR_OT[i] +
		TSI148_LCSR_OFFSET_OTSAU);
	pci_addr_low = ioपढ़ो32be(bridge->base + TSI148_LCSR_OT[i] +
		TSI148_LCSR_OFFSET_OTSAL);

	reg_join(pci_addr_high, pci_addr_low, &pci_addr);
	reg_split(pci_addr + offset, &pci_addr_high, &pci_addr_low);

	/* Configure रेजिस्टरs */
	ioग_लिखो32be(mask, bridge->base + TSI148_LCSR_RMWEN);
	ioग_लिखो32be(compare, bridge->base + TSI148_LCSR_RMWC);
	ioग_लिखो32be(swap, bridge->base + TSI148_LCSR_RMWS);
	ioग_लिखो32be(pci_addr_high, bridge->base + TSI148_LCSR_RMWAU);
	ioग_लिखो32be(pci_addr_low, bridge->base + TSI148_LCSR_RMWAL);

	/* Enable RMW */
	पंचांगp = ioपढ़ो32be(bridge->base + TSI148_LCSR_VMCTRL);
	पंचांगp |= TSI148_LCSR_VMCTRL_RMWEN;
	ioग_लिखो32be(पंचांगp, bridge->base + TSI148_LCSR_VMCTRL);

	/* Kick process off with a पढ़ो to the required address. */
	result = ioपढ़ो32be(image->kern_base + offset);

	/* Disable RMW */
	पंचांगp = ioपढ़ो32be(bridge->base + TSI148_LCSR_VMCTRL);
	पंचांगp &= ~TSI148_LCSR_VMCTRL_RMWEN;
	ioग_लिखो32be(पंचांगp, bridge->base + TSI148_LCSR_VMCTRL);

	spin_unlock(&image->lock);

	mutex_unlock(&bridge->vme_rmw);

	वापस result;
पूर्ण

अटल पूर्णांक tsi148_dma_set_vme_src_attributes(काष्ठा device *dev, __be32 *attr,
	u32 aspace, u32 cycle, u32 dwidth)
अणु
	u32 val;

	val = be32_to_cpu(*attr);

	/* Setup 2eSST speeds */
	चयन (cycle & (VME_2eSST160 | VME_2eSST267 | VME_2eSST320)) अणु
	हाल VME_2eSST160:
		val |= TSI148_LCSR_DSAT_2eSSTM_160;
		अवरोध;
	हाल VME_2eSST267:
		val |= TSI148_LCSR_DSAT_2eSSTM_267;
		अवरोध;
	हाल VME_2eSST320:
		val |= TSI148_LCSR_DSAT_2eSSTM_320;
		अवरोध;
	पूर्ण

	/* Setup cycle types */
	अगर (cycle & VME_SCT)
		val |= TSI148_LCSR_DSAT_TM_SCT;

	अगर (cycle & VME_BLT)
		val |= TSI148_LCSR_DSAT_TM_BLT;

	अगर (cycle & VME_MBLT)
		val |= TSI148_LCSR_DSAT_TM_MBLT;

	अगर (cycle & VME_2eVME)
		val |= TSI148_LCSR_DSAT_TM_2eVME;

	अगर (cycle & VME_2eSST)
		val |= TSI148_LCSR_DSAT_TM_2eSST;

	अगर (cycle & VME_2eSSTB) अणु
		dev_err(dev, "Currently not setting Broadcast Select "
			"Registers\n");
		val |= TSI148_LCSR_DSAT_TM_2eSSTB;
	पूर्ण

	/* Setup data width */
	चयन (dwidth) अणु
	हाल VME_D16:
		val |= TSI148_LCSR_DSAT_DBW_16;
		अवरोध;
	हाल VME_D32:
		val |= TSI148_LCSR_DSAT_DBW_32;
		अवरोध;
	शेष:
		dev_err(dev, "Invalid data width\n");
		वापस -EINVAL;
	पूर्ण

	/* Setup address space */
	चयन (aspace) अणु
	हाल VME_A16:
		val |= TSI148_LCSR_DSAT_AMODE_A16;
		अवरोध;
	हाल VME_A24:
		val |= TSI148_LCSR_DSAT_AMODE_A24;
		अवरोध;
	हाल VME_A32:
		val |= TSI148_LCSR_DSAT_AMODE_A32;
		अवरोध;
	हाल VME_A64:
		val |= TSI148_LCSR_DSAT_AMODE_A64;
		अवरोध;
	हाल VME_CRCSR:
		val |= TSI148_LCSR_DSAT_AMODE_CRCSR;
		अवरोध;
	हाल VME_USER1:
		val |= TSI148_LCSR_DSAT_AMODE_USER1;
		अवरोध;
	हाल VME_USER2:
		val |= TSI148_LCSR_DSAT_AMODE_USER2;
		अवरोध;
	हाल VME_USER3:
		val |= TSI148_LCSR_DSAT_AMODE_USER3;
		अवरोध;
	हाल VME_USER4:
		val |= TSI148_LCSR_DSAT_AMODE_USER4;
		अवरोध;
	शेष:
		dev_err(dev, "Invalid address space\n");
		वापस -EINVAL;
	पूर्ण

	अगर (cycle & VME_SUPER)
		val |= TSI148_LCSR_DSAT_SUP;
	अगर (cycle & VME_PROG)
		val |= TSI148_LCSR_DSAT_PGM;

	*attr = cpu_to_be32(val);

	वापस 0;
पूर्ण

अटल पूर्णांक tsi148_dma_set_vme_dest_attributes(काष्ठा device *dev, __be32 *attr,
	u32 aspace, u32 cycle, u32 dwidth)
अणु
	u32 val;

	val = be32_to_cpu(*attr);

	/* Setup 2eSST speeds */
	चयन (cycle & (VME_2eSST160 | VME_2eSST267 | VME_2eSST320)) अणु
	हाल VME_2eSST160:
		val |= TSI148_LCSR_DDAT_2eSSTM_160;
		अवरोध;
	हाल VME_2eSST267:
		val |= TSI148_LCSR_DDAT_2eSSTM_267;
		अवरोध;
	हाल VME_2eSST320:
		val |= TSI148_LCSR_DDAT_2eSSTM_320;
		अवरोध;
	पूर्ण

	/* Setup cycle types */
	अगर (cycle & VME_SCT)
		val |= TSI148_LCSR_DDAT_TM_SCT;

	अगर (cycle & VME_BLT)
		val |= TSI148_LCSR_DDAT_TM_BLT;

	अगर (cycle & VME_MBLT)
		val |= TSI148_LCSR_DDAT_TM_MBLT;

	अगर (cycle & VME_2eVME)
		val |= TSI148_LCSR_DDAT_TM_2eVME;

	अगर (cycle & VME_2eSST)
		val |= TSI148_LCSR_DDAT_TM_2eSST;

	अगर (cycle & VME_2eSSTB) अणु
		dev_err(dev, "Currently not setting Broadcast Select "
			"Registers\n");
		val |= TSI148_LCSR_DDAT_TM_2eSSTB;
	पूर्ण

	/* Setup data width */
	चयन (dwidth) अणु
	हाल VME_D16:
		val |= TSI148_LCSR_DDAT_DBW_16;
		अवरोध;
	हाल VME_D32:
		val |= TSI148_LCSR_DDAT_DBW_32;
		अवरोध;
	शेष:
		dev_err(dev, "Invalid data width\n");
		वापस -EINVAL;
	पूर्ण

	/* Setup address space */
	चयन (aspace) अणु
	हाल VME_A16:
		val |= TSI148_LCSR_DDAT_AMODE_A16;
		अवरोध;
	हाल VME_A24:
		val |= TSI148_LCSR_DDAT_AMODE_A24;
		अवरोध;
	हाल VME_A32:
		val |= TSI148_LCSR_DDAT_AMODE_A32;
		अवरोध;
	हाल VME_A64:
		val |= TSI148_LCSR_DDAT_AMODE_A64;
		अवरोध;
	हाल VME_CRCSR:
		val |= TSI148_LCSR_DDAT_AMODE_CRCSR;
		अवरोध;
	हाल VME_USER1:
		val |= TSI148_LCSR_DDAT_AMODE_USER1;
		अवरोध;
	हाल VME_USER2:
		val |= TSI148_LCSR_DDAT_AMODE_USER2;
		अवरोध;
	हाल VME_USER3:
		val |= TSI148_LCSR_DDAT_AMODE_USER3;
		अवरोध;
	हाल VME_USER4:
		val |= TSI148_LCSR_DDAT_AMODE_USER4;
		अवरोध;
	शेष:
		dev_err(dev, "Invalid address space\n");
		वापस -EINVAL;
	पूर्ण

	अगर (cycle & VME_SUPER)
		val |= TSI148_LCSR_DDAT_SUP;
	अगर (cycle & VME_PROG)
		val |= TSI148_LCSR_DDAT_PGM;

	*attr = cpu_to_be32(val);

	वापस 0;
पूर्ण

/*
 * Add a link list descriptor to the list
 *
 * Note: DMA engine expects the DMA descriptor to be big endian.
 */
अटल पूर्णांक tsi148_dma_list_add(काष्ठा vme_dma_list *list,
	काष्ठा vme_dma_attr *src, काष्ठा vme_dma_attr *dest, माप_प्रकार count)
अणु
	काष्ठा tsi148_dma_entry *entry, *prev;
	u32 address_high, address_low, val;
	काष्ठा vme_dma_pattern *pattern_attr;
	काष्ठा vme_dma_pci *pci_attr;
	काष्ठा vme_dma_vme *vme_attr;
	पूर्णांक retval = 0;
	काष्ठा vme_bridge *tsi148_bridge;

	tsi148_bridge = list->parent->parent;

	/* Descriptor must be aligned on 64-bit boundaries */
	entry = kदो_स्मृति(माप(*entry), GFP_KERNEL);
	अगर (!entry) अणु
		retval = -ENOMEM;
		जाओ err_mem;
	पूर्ण

	/* Test descriptor alignment */
	अगर ((अचिन्हित दीर्घ)&entry->descriptor & 0x7) अणु
		dev_err(tsi148_bridge->parent, "Descriptor not aligned to 8 "
			"byte boundary as required: %p\n",
			&entry->descriptor);
		retval = -EINVAL;
		जाओ err_align;
	पूर्ण

	/* Given we are going to fill out the काष्ठाure, we probably करोn't
	 * need to zero it, but better safe than sorry क्रम now.
	 */
	स_रखो(&entry->descriptor, 0, माप(entry->descriptor));

	/* Fill out source part */
	चयन (src->type) अणु
	हाल VME_DMA_PATTERN:
		pattern_attr = src->निजी;

		entry->descriptor.dsal = cpu_to_be32(pattern_attr->pattern);

		val = TSI148_LCSR_DSAT_TYP_PAT;

		/* Default behaviour is 32 bit pattern */
		अगर (pattern_attr->type & VME_DMA_PATTERN_BYTE)
			val |= TSI148_LCSR_DSAT_PSZ;

		/* It seems that the शेष behaviour is to increment */
		अगर ((pattern_attr->type & VME_DMA_PATTERN_INCREMENT) == 0)
			val |= TSI148_LCSR_DSAT_NIN;
		entry->descriptor.dsat = cpu_to_be32(val);
		अवरोध;
	हाल VME_DMA_PCI:
		pci_attr = src->निजी;

		reg_split((अचिन्हित दीर्घ दीर्घ)pci_attr->address, &address_high,
			&address_low);
		entry->descriptor.dsau = cpu_to_be32(address_high);
		entry->descriptor.dsal = cpu_to_be32(address_low);
		entry->descriptor.dsat = cpu_to_be32(TSI148_LCSR_DSAT_TYP_PCI);
		अवरोध;
	हाल VME_DMA_VME:
		vme_attr = src->निजी;

		reg_split((अचिन्हित दीर्घ दीर्घ)vme_attr->address, &address_high,
			&address_low);
		entry->descriptor.dsau = cpu_to_be32(address_high);
		entry->descriptor.dsal = cpu_to_be32(address_low);
		entry->descriptor.dsat = cpu_to_be32(TSI148_LCSR_DSAT_TYP_VME);

		retval = tsi148_dma_set_vme_src_attributes(
			tsi148_bridge->parent, &entry->descriptor.dsat,
			vme_attr->aspace, vme_attr->cycle, vme_attr->dwidth);
		अगर (retval < 0)
			जाओ err_source;
		अवरोध;
	शेष:
		dev_err(tsi148_bridge->parent, "Invalid source type\n");
		retval = -EINVAL;
		जाओ err_source;
	पूर्ण

	/* Assume last link - this will be over-written by adding another */
	entry->descriptor.dnlau = cpu_to_be32(0);
	entry->descriptor.dnlal = cpu_to_be32(TSI148_LCSR_DNLAL_LLA);

	/* Fill out destination part */
	चयन (dest->type) अणु
	हाल VME_DMA_PCI:
		pci_attr = dest->निजी;

		reg_split((अचिन्हित दीर्घ दीर्घ)pci_attr->address, &address_high,
			&address_low);
		entry->descriptor.ddau = cpu_to_be32(address_high);
		entry->descriptor.ddal = cpu_to_be32(address_low);
		entry->descriptor.ddat = cpu_to_be32(TSI148_LCSR_DDAT_TYP_PCI);
		अवरोध;
	हाल VME_DMA_VME:
		vme_attr = dest->निजी;

		reg_split((अचिन्हित दीर्घ दीर्घ)vme_attr->address, &address_high,
			&address_low);
		entry->descriptor.ddau = cpu_to_be32(address_high);
		entry->descriptor.ddal = cpu_to_be32(address_low);
		entry->descriptor.ddat = cpu_to_be32(TSI148_LCSR_DDAT_TYP_VME);

		retval = tsi148_dma_set_vme_dest_attributes(
			tsi148_bridge->parent, &entry->descriptor.ddat,
			vme_attr->aspace, vme_attr->cycle, vme_attr->dwidth);
		अगर (retval < 0)
			जाओ err_dest;
		अवरोध;
	शेष:
		dev_err(tsi148_bridge->parent, "Invalid destination type\n");
		retval = -EINVAL;
		जाओ err_dest;
	पूर्ण

	/* Fill out count */
	entry->descriptor.dcnt = cpu_to_be32((u32)count);

	/* Add to list */
	list_add_tail(&entry->list, &list->entries);

	entry->dma_handle = dma_map_single(tsi148_bridge->parent,
					   &entry->descriptor,
					   माप(entry->descriptor),
					   DMA_TO_DEVICE);
	अगर (dma_mapping_error(tsi148_bridge->parent, entry->dma_handle)) अणु
		dev_err(tsi148_bridge->parent, "DMA mapping error\n");
		retval = -EINVAL;
		जाओ err_dma;
	पूर्ण

	/* Fill out previous descriptors "Next Address" */
	अगर (entry->list.prev != &list->entries) अणु
		reg_split((अचिन्हित दीर्घ दीर्घ)entry->dma_handle, &address_high,
			&address_low);
		prev = list_entry(entry->list.prev, काष्ठा tsi148_dma_entry,
				  list);
		prev->descriptor.dnlau = cpu_to_be32(address_high);
		prev->descriptor.dnlal = cpu_to_be32(address_low);

	पूर्ण

	वापस 0;

err_dma:
err_dest:
err_source:
err_align:
		kमुक्त(entry);
err_mem:
	वापस retval;
पूर्ण

/*
 * Check to see अगर the provided DMA channel is busy.
 */
अटल पूर्णांक tsi148_dma_busy(काष्ठा vme_bridge *tsi148_bridge, पूर्णांक channel)
अणु
	u32 पंचांगp;
	काष्ठा tsi148_driver *bridge;

	bridge = tsi148_bridge->driver_priv;

	पंचांगp = ioपढ़ो32be(bridge->base + TSI148_LCSR_DMA[channel] +
		TSI148_LCSR_OFFSET_DSTA);

	अगर (पंचांगp & TSI148_LCSR_DSTA_BSY)
		वापस 0;
	अन्यथा
		वापस 1;

पूर्ण

/*
 * Execute a previously generated link list
 *
 * XXX Need to provide control रेजिस्टर configuration.
 */
अटल पूर्णांक tsi148_dma_list_exec(काष्ठा vme_dma_list *list)
अणु
	काष्ठा vme_dma_resource *ctrlr;
	पूर्णांक channel, retval;
	काष्ठा tsi148_dma_entry *entry;
	u32 bus_addr_high, bus_addr_low;
	u32 val, dctlreg = 0;
	काष्ठा vme_bridge *tsi148_bridge;
	काष्ठा tsi148_driver *bridge;

	ctrlr = list->parent;

	tsi148_bridge = ctrlr->parent;

	bridge = tsi148_bridge->driver_priv;

	mutex_lock(&ctrlr->mtx);

	channel = ctrlr->number;

	अगर (!list_empty(&ctrlr->running)) अणु
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
	entry = list_first_entry(&list->entries, काष्ठा tsi148_dma_entry,
		list);

	mutex_unlock(&ctrlr->mtx);

	reg_split(entry->dma_handle, &bus_addr_high, &bus_addr_low);

	ioग_लिखो32be(bus_addr_high, bridge->base +
		TSI148_LCSR_DMA[channel] + TSI148_LCSR_OFFSET_DNLAU);
	ioग_लिखो32be(bus_addr_low, bridge->base +
		TSI148_LCSR_DMA[channel] + TSI148_LCSR_OFFSET_DNLAL);

	dctlreg = ioपढ़ो32be(bridge->base + TSI148_LCSR_DMA[channel] +
		TSI148_LCSR_OFFSET_DCTL);

	/* Start the operation */
	ioग_लिखो32be(dctlreg | TSI148_LCSR_DCTL_DGO, bridge->base +
		TSI148_LCSR_DMA[channel] + TSI148_LCSR_OFFSET_DCTL);

	retval = रुको_event_पूर्णांकerruptible(bridge->dma_queue[channel],
		tsi148_dma_busy(ctrlr->parent, channel));

	अगर (retval) अणु
		ioग_लिखो32be(dctlreg | TSI148_LCSR_DCTL_ABT, bridge->base +
			TSI148_LCSR_DMA[channel] + TSI148_LCSR_OFFSET_DCTL);
		/* Wait क्रम the operation to पात */
		रुको_event(bridge->dma_queue[channel],
			   tsi148_dma_busy(ctrlr->parent, channel));
		retval = -EINTR;
		जाओ निकास;
	पूर्ण

	/*
	 * Read status रेजिस्टर, this रेजिस्टर is valid until we kick off a
	 * new transfer.
	 */
	val = ioपढ़ो32be(bridge->base + TSI148_LCSR_DMA[channel] +
		TSI148_LCSR_OFFSET_DSTA);

	अगर (val & TSI148_LCSR_DSTA_VBE) अणु
		dev_err(tsi148_bridge->parent, "DMA Error. DSTA=%08X\n", val);
		retval = -EIO;
	पूर्ण

निकास:
	/* Remove list from running list */
	mutex_lock(&ctrlr->mtx);
	list_del(&list->list);
	mutex_unlock(&ctrlr->mtx);

	वापस retval;
पूर्ण

/*
 * Clean up a previously generated link list
 *
 * We have a separate function, करोn't assume that the chain can't be reused.
 */
अटल पूर्णांक tsi148_dma_list_empty(काष्ठा vme_dma_list *list)
अणु
	काष्ठा list_head *pos, *temp;
	काष्ठा tsi148_dma_entry *entry;

	काष्ठा vme_bridge *tsi148_bridge = list->parent->parent;

	/* detach and मुक्त each entry */
	list_क्रम_each_safe(pos, temp, &list->entries) अणु
		list_del(pos);
		entry = list_entry(pos, काष्ठा tsi148_dma_entry, list);

		dma_unmap_single(tsi148_bridge->parent, entry->dma_handle,
			माप(काष्ठा tsi148_dma_descriptor), DMA_TO_DEVICE);
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
अटल पूर्णांक tsi148_lm_set(काष्ठा vme_lm_resource *lm, अचिन्हित दीर्घ दीर्घ lm_base,
	u32 aspace, u32 cycle)
अणु
	u32 lm_base_high, lm_base_low, lm_ctl = 0;
	पूर्णांक i;
	काष्ठा vme_bridge *tsi148_bridge;
	काष्ठा tsi148_driver *bridge;

	tsi148_bridge = lm->parent;

	bridge = tsi148_bridge->driver_priv;

	mutex_lock(&lm->mtx);

	/* If we alपढ़ोy have a callback attached, we can't move it! */
	क्रम (i = 0; i < lm->monitors; i++) अणु
		अगर (bridge->lm_callback[i]) अणु
			mutex_unlock(&lm->mtx);
			dev_err(tsi148_bridge->parent, "Location monitor "
				"callback attached, can't reset\n");
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	चयन (aspace) अणु
	हाल VME_A16:
		lm_ctl |= TSI148_LCSR_LMAT_AS_A16;
		अवरोध;
	हाल VME_A24:
		lm_ctl |= TSI148_LCSR_LMAT_AS_A24;
		अवरोध;
	हाल VME_A32:
		lm_ctl |= TSI148_LCSR_LMAT_AS_A32;
		अवरोध;
	हाल VME_A64:
		lm_ctl |= TSI148_LCSR_LMAT_AS_A64;
		अवरोध;
	शेष:
		mutex_unlock(&lm->mtx);
		dev_err(tsi148_bridge->parent, "Invalid address space\n");
		वापस -EINVAL;
	पूर्ण

	अगर (cycle & VME_SUPER)
		lm_ctl |= TSI148_LCSR_LMAT_SUPR ;
	अगर (cycle & VME_USER)
		lm_ctl |= TSI148_LCSR_LMAT_NPRIV;
	अगर (cycle & VME_PROG)
		lm_ctl |= TSI148_LCSR_LMAT_PGM;
	अगर (cycle & VME_DATA)
		lm_ctl |= TSI148_LCSR_LMAT_DATA;

	reg_split(lm_base, &lm_base_high, &lm_base_low);

	ioग_लिखो32be(lm_base_high, bridge->base + TSI148_LCSR_LMBAU);
	ioग_लिखो32be(lm_base_low, bridge->base + TSI148_LCSR_LMBAL);
	ioग_लिखो32be(lm_ctl, bridge->base + TSI148_LCSR_LMAT);

	mutex_unlock(&lm->mtx);

	वापस 0;
पूर्ण

/* Get configuration of the callback monitor and वापस whether it is enabled
 * or disabled.
 */
अटल पूर्णांक tsi148_lm_get(काष्ठा vme_lm_resource *lm,
	अचिन्हित दीर्घ दीर्घ *lm_base, u32 *aspace, u32 *cycle)
अणु
	u32 lm_base_high, lm_base_low, lm_ctl, enabled = 0;
	काष्ठा tsi148_driver *bridge;

	bridge = lm->parent->driver_priv;

	mutex_lock(&lm->mtx);

	lm_base_high = ioपढ़ो32be(bridge->base + TSI148_LCSR_LMBAU);
	lm_base_low = ioपढ़ो32be(bridge->base + TSI148_LCSR_LMBAL);
	lm_ctl = ioपढ़ो32be(bridge->base + TSI148_LCSR_LMAT);

	reg_join(lm_base_high, lm_base_low, lm_base);

	अगर (lm_ctl & TSI148_LCSR_LMAT_EN)
		enabled = 1;

	अगर ((lm_ctl & TSI148_LCSR_LMAT_AS_M) == TSI148_LCSR_LMAT_AS_A16)
		*aspace |= VME_A16;

	अगर ((lm_ctl & TSI148_LCSR_LMAT_AS_M) == TSI148_LCSR_LMAT_AS_A24)
		*aspace |= VME_A24;

	अगर ((lm_ctl & TSI148_LCSR_LMAT_AS_M) == TSI148_LCSR_LMAT_AS_A32)
		*aspace |= VME_A32;

	अगर ((lm_ctl & TSI148_LCSR_LMAT_AS_M) == TSI148_LCSR_LMAT_AS_A64)
		*aspace |= VME_A64;


	अगर (lm_ctl & TSI148_LCSR_LMAT_SUPR)
		*cycle |= VME_SUPER;
	अगर (lm_ctl & TSI148_LCSR_LMAT_NPRIV)
		*cycle |= VME_USER;
	अगर (lm_ctl & TSI148_LCSR_LMAT_PGM)
		*cycle |= VME_PROG;
	अगर (lm_ctl & TSI148_LCSR_LMAT_DATA)
		*cycle |= VME_DATA;

	mutex_unlock(&lm->mtx);

	वापस enabled;
पूर्ण

/*
 * Attach a callback to a specअगरic location monitor.
 *
 * Callback will be passed the monitor triggered.
 */
अटल पूर्णांक tsi148_lm_attach(काष्ठा vme_lm_resource *lm, पूर्णांक monitor,
	व्योम (*callback)(व्योम *), व्योम *data)
अणु
	u32 lm_ctl, पंचांगp;
	काष्ठा vme_bridge *tsi148_bridge;
	काष्ठा tsi148_driver *bridge;

	tsi148_bridge = lm->parent;

	bridge = tsi148_bridge->driver_priv;

	mutex_lock(&lm->mtx);

	/* Ensure that the location monitor is configured - need PGM or DATA */
	lm_ctl = ioपढ़ो32be(bridge->base + TSI148_LCSR_LMAT);
	अगर ((lm_ctl & (TSI148_LCSR_LMAT_PGM | TSI148_LCSR_LMAT_DATA)) == 0) अणु
		mutex_unlock(&lm->mtx);
		dev_err(tsi148_bridge->parent, "Location monitor not properly "
			"configured\n");
		वापस -EINVAL;
	पूर्ण

	/* Check that a callback isn't alपढ़ोy attached */
	अगर (bridge->lm_callback[monitor]) अणु
		mutex_unlock(&lm->mtx);
		dev_err(tsi148_bridge->parent, "Existing callback attached\n");
		वापस -EBUSY;
	पूर्ण

	/* Attach callback */
	bridge->lm_callback[monitor] = callback;
	bridge->lm_data[monitor] = data;

	/* Enable Location Monitor पूर्णांकerrupt */
	पंचांगp = ioपढ़ो32be(bridge->base + TSI148_LCSR_INTEN);
	पंचांगp |= TSI148_LCSR_INTEN_LMEN[monitor];
	ioग_लिखो32be(पंचांगp, bridge->base + TSI148_LCSR_INTEN);

	पंचांगp = ioपढ़ो32be(bridge->base + TSI148_LCSR_INTEO);
	पंचांगp |= TSI148_LCSR_INTEO_LMEO[monitor];
	ioग_लिखो32be(पंचांगp, bridge->base + TSI148_LCSR_INTEO);

	/* Ensure that global Location Monitor Enable set */
	अगर ((lm_ctl & TSI148_LCSR_LMAT_EN) == 0) अणु
		lm_ctl |= TSI148_LCSR_LMAT_EN;
		ioग_लिखो32be(lm_ctl, bridge->base + TSI148_LCSR_LMAT);
	पूर्ण

	mutex_unlock(&lm->mtx);

	वापस 0;
पूर्ण

/*
 * Detach a callback function क्रमn a specअगरic location monitor.
 */
अटल पूर्णांक tsi148_lm_detach(काष्ठा vme_lm_resource *lm, पूर्णांक monitor)
अणु
	u32 lm_en, पंचांगp;
	काष्ठा tsi148_driver *bridge;

	bridge = lm->parent->driver_priv;

	mutex_lock(&lm->mtx);

	/* Disable Location Monitor and ensure previous पूर्णांकerrupts are clear */
	lm_en = ioपढ़ो32be(bridge->base + TSI148_LCSR_INTEN);
	lm_en &= ~TSI148_LCSR_INTEN_LMEN[monitor];
	ioग_लिखो32be(lm_en, bridge->base + TSI148_LCSR_INTEN);

	पंचांगp = ioपढ़ो32be(bridge->base + TSI148_LCSR_INTEO);
	पंचांगp &= ~TSI148_LCSR_INTEO_LMEO[monitor];
	ioग_लिखो32be(पंचांगp, bridge->base + TSI148_LCSR_INTEO);

	ioग_लिखो32be(TSI148_LCSR_INTC_LMC[monitor],
		 bridge->base + TSI148_LCSR_INTC);

	/* Detach callback */
	bridge->lm_callback[monitor] = शून्य;
	bridge->lm_data[monitor] = शून्य;

	/* If all location monitors disabled, disable global Location Monitor */
	अगर ((lm_en & (TSI148_LCSR_INTS_LM0S | TSI148_LCSR_INTS_LM1S |
			TSI148_LCSR_INTS_LM2S | TSI148_LCSR_INTS_LM3S)) == 0) अणु
		पंचांगp = ioपढ़ो32be(bridge->base + TSI148_LCSR_LMAT);
		पंचांगp &= ~TSI148_LCSR_LMAT_EN;
		ioग_लिखो32be(पंचांगp, bridge->base + TSI148_LCSR_LMAT);
	पूर्ण

	mutex_unlock(&lm->mtx);

	वापस 0;
पूर्ण

/*
 * Determine Geographical Addressing
 */
अटल पूर्णांक tsi148_slot_get(काष्ठा vme_bridge *tsi148_bridge)
अणु
	u32 slot = 0;
	काष्ठा tsi148_driver *bridge;

	bridge = tsi148_bridge->driver_priv;

	अगर (!geoid) अणु
		slot = ioपढ़ो32be(bridge->base + TSI148_LCSR_VSTAT);
		slot = slot & TSI148_LCSR_VSTAT_GA_M;
	पूर्ण अन्यथा
		slot = geoid;

	वापस (पूर्णांक)slot;
पूर्ण

अटल व्योम *tsi148_alloc_consistent(काष्ठा device *parent, माप_प्रकार size,
	dma_addr_t *dma)
अणु
	काष्ठा pci_dev *pdev;

	/* Find pci_dev container of dev */
	pdev = to_pci_dev(parent);

	वापस dma_alloc_coherent(&pdev->dev, size, dma, GFP_KERNEL);
पूर्ण

अटल व्योम tsi148_मुक्त_consistent(काष्ठा device *parent, माप_प्रकार size,
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
 *
 * Each board has a 512kB winकरोw, with the highest 4kB being used क्रम the
 * boards रेजिस्टरs, this means there is a fix length 508kB winकरोw which must
 * be mapped onto PCI memory.
 */
अटल पूर्णांक tsi148_crcsr_init(काष्ठा vme_bridge *tsi148_bridge,
	काष्ठा pci_dev *pdev)
अणु
	u32 cbar, crat, vstat;
	u32 crcsr_bus_high, crcsr_bus_low;
	पूर्णांक retval;
	काष्ठा tsi148_driver *bridge;

	bridge = tsi148_bridge->driver_priv;

	/* Allocate mem क्रम CR/CSR image */
	bridge->crcsr_kernel = dma_alloc_coherent(&pdev->dev,
						  VME_CRCSR_BUF_SIZE,
						  &bridge->crcsr_bus, GFP_KERNEL);
	अगर (!bridge->crcsr_kernel) अणु
		dev_err(tsi148_bridge->parent, "Failed to allocate memory for "
			"CR/CSR image\n");
		वापस -ENOMEM;
	पूर्ण

	reg_split(bridge->crcsr_bus, &crcsr_bus_high, &crcsr_bus_low);

	ioग_लिखो32be(crcsr_bus_high, bridge->base + TSI148_LCSR_CROU);
	ioग_लिखो32be(crcsr_bus_low, bridge->base + TSI148_LCSR_CROL);

	/* Ensure that the CR/CSR is configured at the correct offset */
	cbar = ioपढ़ो32be(bridge->base + TSI148_CBAR);
	cbar = (cbar & TSI148_CRCSR_CBAR_M)>>3;

	vstat = tsi148_slot_get(tsi148_bridge);

	अगर (cbar != vstat) अणु
		cbar = vstat;
		dev_info(tsi148_bridge->parent, "Setting CR/CSR offset\n");
		ioग_लिखो32be(cbar<<3, bridge->base + TSI148_CBAR);
	पूर्ण
	dev_info(tsi148_bridge->parent, "CR/CSR Offset: %d\n", cbar);

	crat = ioपढ़ो32be(bridge->base + TSI148_LCSR_CRAT);
	अगर (crat & TSI148_LCSR_CRAT_EN)
		dev_info(tsi148_bridge->parent, "CR/CSR already enabled\n");
	अन्यथा अणु
		dev_info(tsi148_bridge->parent, "Enabling CR/CSR space\n");
		ioग_लिखो32be(crat | TSI148_LCSR_CRAT_EN,
			bridge->base + TSI148_LCSR_CRAT);
	पूर्ण

	/* If we want flushed, error-checked ग_लिखोs, set up a winकरोw
	 * over the CR/CSR रेजिस्टरs. We पढ़ो from here to safely flush
	 * through VME ग_लिखोs.
	 */
	अगर (err_chk) अणु
		retval = tsi148_master_set(bridge->flush_image, 1,
			(vstat * 0x80000), 0x80000, VME_CRCSR, VME_SCT,
			VME_D16);
		अगर (retval)
			dev_err(tsi148_bridge->parent, "Configuring flush image"
				" failed\n");
	पूर्ण

	वापस 0;

पूर्ण

अटल व्योम tsi148_crcsr_निकास(काष्ठा vme_bridge *tsi148_bridge,
	काष्ठा pci_dev *pdev)
अणु
	u32 crat;
	काष्ठा tsi148_driver *bridge;

	bridge = tsi148_bridge->driver_priv;

	/* Turn off CR/CSR space */
	crat = ioपढ़ो32be(bridge->base + TSI148_LCSR_CRAT);
	ioग_लिखो32be(crat & ~TSI148_LCSR_CRAT_EN,
		bridge->base + TSI148_LCSR_CRAT);

	/* Free image */
	ioग_लिखो32be(0, bridge->base + TSI148_LCSR_CROU);
	ioग_लिखो32be(0, bridge->base + TSI148_LCSR_CROL);

	dma_मुक्त_coherent(&pdev->dev, VME_CRCSR_BUF_SIZE,
			  bridge->crcsr_kernel, bridge->crcsr_bus);
पूर्ण

अटल पूर्णांक tsi148_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	पूर्णांक retval, i, master_num;
	u32 data;
	काष्ठा list_head *pos = शून्य, *n;
	काष्ठा vme_bridge *tsi148_bridge;
	काष्ठा tsi148_driver *tsi148_device;
	काष्ठा vme_master_resource *master_image;
	काष्ठा vme_slave_resource *slave_image;
	काष्ठा vme_dma_resource *dma_ctrlr;
	काष्ठा vme_lm_resource *lm;

	/* If we want to support more than one of each bridge, we need to
	 * dynamically generate this so we get one per device
	 */
	tsi148_bridge = kzalloc(माप(*tsi148_bridge), GFP_KERNEL);
	अगर (!tsi148_bridge) अणु
		retval = -ENOMEM;
		जाओ err_काष्ठा;
	पूर्ण
	vme_init_bridge(tsi148_bridge);

	tsi148_device = kzalloc(माप(*tsi148_device), GFP_KERNEL);
	अगर (!tsi148_device) अणु
		retval = -ENOMEM;
		जाओ err_driver;
	पूर्ण

	tsi148_bridge->driver_priv = tsi148_device;

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
	tsi148_device->base = ioremap(pci_resource_start(pdev, 0),
		4096);
	अगर (!tsi148_device->base) अणु
		dev_err(&pdev->dev, "Unable to remap CRG region\n");
		retval = -EIO;
		जाओ err_remap;
	पूर्ण

	/* Check to see अगर the mapping worked out */
	data = ioपढ़ो32(tsi148_device->base + TSI148_PCFS_ID) & 0x0000FFFF;
	अगर (data != PCI_VENDOR_ID_TUNDRA) अणु
		dev_err(&pdev->dev, "CRG region check failed\n");
		retval = -EIO;
		जाओ err_test;
	पूर्ण

	/* Initialize रुको queues & mutual exclusion flags */
	init_रुकोqueue_head(&tsi148_device->dma_queue[0]);
	init_रुकोqueue_head(&tsi148_device->dma_queue[1]);
	init_रुकोqueue_head(&tsi148_device->iack_queue);
	mutex_init(&tsi148_device->vme_पूर्णांक);
	mutex_init(&tsi148_device->vme_rmw);

	tsi148_bridge->parent = &pdev->dev;
	म_नकल(tsi148_bridge->name, driver_name);

	/* Setup IRQ */
	retval = tsi148_irq_init(tsi148_bridge);
	अगर (retval != 0) अणु
		dev_err(&pdev->dev, "Chip Initialization failed.\n");
		जाओ err_irq;
	पूर्ण

	/* If we are going to flush ग_लिखोs, we need to पढ़ो from the VME bus.
	 * We need to करो this safely, thus we पढ़ो the devices own CR/CSR
	 * रेजिस्टर. To करो this we must set up a winकरोw in CR/CSR space and
	 * hence have one less master winकरोw resource available.
	 */
	master_num = TSI148_MAX_MASTER;
	अगर (err_chk) अणु
		master_num--;

		tsi148_device->flush_image =
			kदो_स्मृति(माप(*tsi148_device->flush_image),
				GFP_KERNEL);
		अगर (!tsi148_device->flush_image) अणु
			retval = -ENOMEM;
			जाओ err_master;
		पूर्ण
		tsi148_device->flush_image->parent = tsi148_bridge;
		spin_lock_init(&tsi148_device->flush_image->lock);
		tsi148_device->flush_image->locked = 1;
		tsi148_device->flush_image->number = master_num;
		स_रखो(&tsi148_device->flush_image->bus_resource, 0,
		       माप(tsi148_device->flush_image->bus_resource));
		tsi148_device->flush_image->kern_base  = शून्य;
	पूर्ण

	/* Add master winकरोws to list */
	क्रम (i = 0; i < master_num; i++) अणु
		master_image = kदो_स्मृति(माप(*master_image), GFP_KERNEL);
		अगर (!master_image) अणु
			retval = -ENOMEM;
			जाओ err_master;
		पूर्ण
		master_image->parent = tsi148_bridge;
		spin_lock_init(&master_image->lock);
		master_image->locked = 0;
		master_image->number = i;
		master_image->address_attr = VME_A16 | VME_A24 | VME_A32 |
			VME_A64 | VME_CRCSR | VME_USER1 | VME_USER2 |
			VME_USER3 | VME_USER4;
		master_image->cycle_attr = VME_SCT | VME_BLT | VME_MBLT |
			VME_2eVME | VME_2eSST | VME_2eSSTB | VME_2eSST160 |
			VME_2eSST267 | VME_2eSST320 | VME_SUPER | VME_USER |
			VME_PROG | VME_DATA;
		master_image->width_attr = VME_D16 | VME_D32;
		स_रखो(&master_image->bus_resource, 0,
		       माप(master_image->bus_resource));
		master_image->kern_base  = शून्य;
		list_add_tail(&master_image->list,
			&tsi148_bridge->master_resources);
	पूर्ण

	/* Add slave winकरोws to list */
	क्रम (i = 0; i < TSI148_MAX_SLAVE; i++) अणु
		slave_image = kदो_स्मृति(माप(*slave_image), GFP_KERNEL);
		अगर (!slave_image) अणु
			retval = -ENOMEM;
			जाओ err_slave;
		पूर्ण
		slave_image->parent = tsi148_bridge;
		mutex_init(&slave_image->mtx);
		slave_image->locked = 0;
		slave_image->number = i;
		slave_image->address_attr = VME_A16 | VME_A24 | VME_A32 |
			VME_A64;
		slave_image->cycle_attr = VME_SCT | VME_BLT | VME_MBLT |
			VME_2eVME | VME_2eSST | VME_2eSSTB | VME_2eSST160 |
			VME_2eSST267 | VME_2eSST320 | VME_SUPER | VME_USER |
			VME_PROG | VME_DATA;
		list_add_tail(&slave_image->list,
			&tsi148_bridge->slave_resources);
	पूर्ण

	/* Add dma engines to list */
	क्रम (i = 0; i < TSI148_MAX_DMA; i++) अणु
		dma_ctrlr = kदो_स्मृति(माप(*dma_ctrlr), GFP_KERNEL);
		अगर (!dma_ctrlr) अणु
			retval = -ENOMEM;
			जाओ err_dma;
		पूर्ण
		dma_ctrlr->parent = tsi148_bridge;
		mutex_init(&dma_ctrlr->mtx);
		dma_ctrlr->locked = 0;
		dma_ctrlr->number = i;
		dma_ctrlr->route_attr = VME_DMA_VME_TO_MEM |
			VME_DMA_MEM_TO_VME | VME_DMA_VME_TO_VME |
			VME_DMA_MEM_TO_MEM | VME_DMA_PATTERN_TO_VME |
			VME_DMA_PATTERN_TO_MEM;
		INIT_LIST_HEAD(&dma_ctrlr->pending);
		INIT_LIST_HEAD(&dma_ctrlr->running);
		list_add_tail(&dma_ctrlr->list,
			&tsi148_bridge->dma_resources);
	पूर्ण

	/* Add location monitor to list */
	lm = kदो_स्मृति(माप(*lm), GFP_KERNEL);
	अगर (!lm) अणु
		retval = -ENOMEM;
		जाओ err_lm;
	पूर्ण
	lm->parent = tsi148_bridge;
	mutex_init(&lm->mtx);
	lm->locked = 0;
	lm->number = 1;
	lm->monitors = 4;
	list_add_tail(&lm->list, &tsi148_bridge->lm_resources);

	tsi148_bridge->slave_get = tsi148_slave_get;
	tsi148_bridge->slave_set = tsi148_slave_set;
	tsi148_bridge->master_get = tsi148_master_get;
	tsi148_bridge->master_set = tsi148_master_set;
	tsi148_bridge->master_पढ़ो = tsi148_master_पढ़ो;
	tsi148_bridge->master_ग_लिखो = tsi148_master_ग_लिखो;
	tsi148_bridge->master_rmw = tsi148_master_rmw;
	tsi148_bridge->dma_list_add = tsi148_dma_list_add;
	tsi148_bridge->dma_list_exec = tsi148_dma_list_exec;
	tsi148_bridge->dma_list_empty = tsi148_dma_list_empty;
	tsi148_bridge->irq_set = tsi148_irq_set;
	tsi148_bridge->irq_generate = tsi148_irq_generate;
	tsi148_bridge->lm_set = tsi148_lm_set;
	tsi148_bridge->lm_get = tsi148_lm_get;
	tsi148_bridge->lm_attach = tsi148_lm_attach;
	tsi148_bridge->lm_detach = tsi148_lm_detach;
	tsi148_bridge->slot_get = tsi148_slot_get;
	tsi148_bridge->alloc_consistent = tsi148_alloc_consistent;
	tsi148_bridge->मुक्त_consistent = tsi148_मुक्त_consistent;

	data = ioपढ़ो32be(tsi148_device->base + TSI148_LCSR_VSTAT);
	dev_info(&pdev->dev, "Board is%s the VME system controller\n",
		(data & TSI148_LCSR_VSTAT_SCONS) ? "" : " not");
	अगर (!geoid)
		dev_info(&pdev->dev, "VME geographical address is %d\n",
			data & TSI148_LCSR_VSTAT_GA_M);
	अन्यथा
		dev_info(&pdev->dev, "VME geographical address is set to %d\n",
			geoid);

	dev_info(&pdev->dev, "VME Write and flush and error check is %s\n",
		err_chk ? "enabled" : "disabled");

	retval = tsi148_crcsr_init(tsi148_bridge, pdev);
	अगर (retval) अणु
		dev_err(&pdev->dev, "CR/CSR configuration failed.\n");
		जाओ err_crcsr;
	पूर्ण

	retval = vme_रेजिस्टर_bridge(tsi148_bridge);
	अगर (retval != 0) अणु
		dev_err(&pdev->dev, "Chip Registration failed.\n");
		जाओ err_reg;
	पूर्ण

	pci_set_drvdata(pdev, tsi148_bridge);

	/* Clear VME bus "board fail", and "power-up reset" lines */
	data = ioपढ़ो32be(tsi148_device->base + TSI148_LCSR_VSTAT);
	data &= ~TSI148_LCSR_VSTAT_BRDFL;
	data |= TSI148_LCSR_VSTAT_CPURST;
	ioग_लिखो32be(data, tsi148_device->base + TSI148_LCSR_VSTAT);

	वापस 0;

err_reg:
	tsi148_crcsr_निकास(tsi148_bridge, pdev);
err_crcsr:
err_lm:
	/* resources are stored in link list */
	list_क्रम_each_safe(pos, n, &tsi148_bridge->lm_resources) अणु
		lm = list_entry(pos, काष्ठा vme_lm_resource, list);
		list_del(pos);
		kमुक्त(lm);
	पूर्ण
err_dma:
	/* resources are stored in link list */
	list_क्रम_each_safe(pos, n, &tsi148_bridge->dma_resources) अणु
		dma_ctrlr = list_entry(pos, काष्ठा vme_dma_resource, list);
		list_del(pos);
		kमुक्त(dma_ctrlr);
	पूर्ण
err_slave:
	/* resources are stored in link list */
	list_क्रम_each_safe(pos, n, &tsi148_bridge->slave_resources) अणु
		slave_image = list_entry(pos, काष्ठा vme_slave_resource, list);
		list_del(pos);
		kमुक्त(slave_image);
	पूर्ण
err_master:
	/* resources are stored in link list */
	list_क्रम_each_safe(pos, n, &tsi148_bridge->master_resources) अणु
		master_image = list_entry(pos, काष्ठा vme_master_resource,
			list);
		list_del(pos);
		kमुक्त(master_image);
	पूर्ण

	tsi148_irq_निकास(tsi148_bridge, pdev);
err_irq:
err_test:
	iounmap(tsi148_device->base);
err_remap:
	pci_release_regions(pdev);
err_resource:
	pci_disable_device(pdev);
err_enable:
	kमुक्त(tsi148_device);
err_driver:
	kमुक्त(tsi148_bridge);
err_काष्ठा:
	वापस retval;

पूर्ण

अटल व्योम tsi148_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा list_head *pos = शून्य;
	काष्ठा list_head *पंचांगplist;
	काष्ठा vme_master_resource *master_image;
	काष्ठा vme_slave_resource *slave_image;
	काष्ठा vme_dma_resource *dma_ctrlr;
	पूर्णांक i;
	काष्ठा tsi148_driver *bridge;
	काष्ठा vme_bridge *tsi148_bridge = pci_get_drvdata(pdev);

	bridge = tsi148_bridge->driver_priv;


	dev_dbg(&pdev->dev, "Driver is being unloaded.\n");

	/*
	 *  Shutकरोwn all inbound and outbound winकरोws.
	 */
	क्रम (i = 0; i < 8; i++) अणु
		ioग_लिखो32be(0, bridge->base + TSI148_LCSR_IT[i] +
			TSI148_LCSR_OFFSET_ITAT);
		ioग_लिखो32be(0, bridge->base + TSI148_LCSR_OT[i] +
			TSI148_LCSR_OFFSET_OTAT);
	पूर्ण

	/*
	 *  Shutकरोwn Location monitor.
	 */
	ioग_लिखो32be(0, bridge->base + TSI148_LCSR_LMAT);

	/*
	 *  Shutकरोwn CRG map.
	 */
	ioग_लिखो32be(0, bridge->base + TSI148_LCSR_CSRAT);

	/*
	 *  Clear error status.
	 */
	ioग_लिखो32be(0xFFFFFFFF, bridge->base + TSI148_LCSR_EDPAT);
	ioग_लिखो32be(0xFFFFFFFF, bridge->base + TSI148_LCSR_VEAT);
	ioग_लिखो32be(0x07000700, bridge->base + TSI148_LCSR_PSTAT);

	/*
	 *  Remove VIRQ पूर्णांकerrupt (अगर any)
	 */
	अगर (ioपढ़ो32be(bridge->base + TSI148_LCSR_VICR) & 0x800)
		ioग_लिखो32be(0x8000, bridge->base + TSI148_LCSR_VICR);

	/*
	 *  Map all Interrupts to PCI INTA
	 */
	ioग_लिखो32be(0x0, bridge->base + TSI148_LCSR_INTM1);
	ioग_लिखो32be(0x0, bridge->base + TSI148_LCSR_INTM2);

	tsi148_irq_निकास(tsi148_bridge, pdev);

	vme_unरेजिस्टर_bridge(tsi148_bridge);

	tsi148_crcsr_निकास(tsi148_bridge, pdev);

	/* resources are stored in link list */
	list_क्रम_each_safe(pos, पंचांगplist, &tsi148_bridge->dma_resources) अणु
		dma_ctrlr = list_entry(pos, काष्ठा vme_dma_resource, list);
		list_del(pos);
		kमुक्त(dma_ctrlr);
	पूर्ण

	/* resources are stored in link list */
	list_क्रम_each_safe(pos, पंचांगplist, &tsi148_bridge->slave_resources) अणु
		slave_image = list_entry(pos, काष्ठा vme_slave_resource, list);
		list_del(pos);
		kमुक्त(slave_image);
	पूर्ण

	/* resources are stored in link list */
	list_क्रम_each_safe(pos, पंचांगplist, &tsi148_bridge->master_resources) अणु
		master_image = list_entry(pos, काष्ठा vme_master_resource,
			list);
		list_del(pos);
		kमुक्त(master_image);
	पूर्ण

	iounmap(bridge->base);

	pci_release_regions(pdev);

	pci_disable_device(pdev);

	kमुक्त(tsi148_bridge->driver_priv);

	kमुक्त(tsi148_bridge);
पूर्ण

module_pci_driver(tsi148_driver);

MODULE_PARM_DESC(err_chk, "Check for VME errors on reads and writes");
module_param(err_chk, bool, 0);

MODULE_PARM_DESC(geoid, "Override geographical addressing");
module_param(geoid, पूर्णांक, 0);

MODULE_DESCRIPTION("VME driver for the Tundra Tempe VME bridge");
MODULE_LICENSE("GPL");
