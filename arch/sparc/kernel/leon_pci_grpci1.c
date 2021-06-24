<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * leon_pci_grpci1.c: GRPCI1 Host PCI driver
 *
 * Copyright (C) 2013 Aeroflex Gaisler AB
 *
 * This GRPCI1 driver करोes not support PCI पूर्णांकerrupts taken from
 * GPIO pins. Interrupt generation at PCI parity and प्रणाली error
 * detection is by शेष turned off since some GRPCI1 cores करोes
 * not support detection. It can be turned on from the bootloader
 * using the all_pci_errors property.
 *
 * Contributors: Daniel Hellstrom <daniel@gaisler.com>
 */

#समावेश <linux/of_device.h>
#समावेश <linux/export.h>
#समावेश <linux/kernel.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/delay.h>
#समावेश <linux/pci.h>

#समावेश <यंत्र/leon_pci.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/vaddrs.h>
#समावेश <यंत्र/leon.h>
#समावेश <यंत्र/पन.स>

#समावेश "irq.h"

/* Enable/Disable Debugging Configuration Space Access */
#अघोषित GRPCI1_DEBUG_CFGACCESS

/*
 * GRPCI1 APB Register MAP
 */
काष्ठा grpci1_regs अणु
	अचिन्हित पूर्णांक cfg_stat;		/* 0x00 Configuration / Status */
	अचिन्हित पूर्णांक bar0;		/* 0x04 BAR0 (RO) */
	अचिन्हित पूर्णांक page0;		/* 0x08 PAGE0 (RO) */
	अचिन्हित पूर्णांक bar1;		/* 0x0C BAR1 (RO) */
	अचिन्हित पूर्णांक page1;		/* 0x10 PAGE1 */
	अचिन्हित पूर्णांक iomap;		/* 0x14 IO Map */
	अचिन्हित पूर्णांक stat_cmd;		/* 0x18 PCI Status & Command (RO) */
	अचिन्हित पूर्णांक irq;		/* 0x1C Interrupt रेजिस्टर */
पूर्ण;

#घोषणा REGLOAD(a)	(be32_to_cpu(__raw_पढ़ोl(&(a))))
#घोषणा REGSTORE(a, v)	(__raw_ग_लिखोl(cpu_to_be32(v), &(a)))

#घोषणा PAGE0_BTEN_BIT    0
#घोषणा PAGE0_BTEN        (1 << PAGE0_BTEN_BIT)

#घोषणा CFGSTAT_HOST_BIT  13
#घोषणा CFGSTAT_CTO_BIT   8
#घोषणा CFGSTAT_HOST      (1 << CFGSTAT_HOST_BIT)
#घोषणा CFGSTAT_CTO       (1 << CFGSTAT_CTO_BIT)

#घोषणा IRQ_DPE (1 << 9)
#घोषणा IRQ_SSE (1 << 8)
#घोषणा IRQ_RMA (1 << 7)
#घोषणा IRQ_RTA (1 << 6)
#घोषणा IRQ_STA (1 << 5)
#घोषणा IRQ_DPED (1 << 4)
#घोषणा IRQ_INTD (1 << 3)
#घोषणा IRQ_INTC (1 << 2)
#घोषणा IRQ_INTB (1 << 1)
#घोषणा IRQ_INTA (1 << 0)
#घोषणा IRQ_DEF_ERRORS (IRQ_RMA | IRQ_RTA | IRQ_STA)
#घोषणा IRQ_ALL_ERRORS (IRQ_DPED | IRQ_DEF_ERRORS | IRQ_SSE | IRQ_DPE)
#घोषणा IRQ_INTX (IRQ_INTA | IRQ_INTB | IRQ_INTC | IRQ_INTD)
#घोषणा IRQ_MASK_BIT 16

#घोषणा DEF_PCI_ERRORS (PCI_STATUS_SIG_TARGET_ABORT | \
			PCI_STATUS_REC_TARGET_ABORT | \
			PCI_STATUS_REC_MASTER_ABORT)
#घोषणा ALL_PCI_ERRORS (PCI_STATUS_PARITY | PCI_STATUS_DETECTED_PARITY | \
			PCI_STATUS_SIG_SYSTEM_ERROR | DEF_PCI_ERRORS)

#घोषणा TGT 256

काष्ठा grpci1_priv अणु
	काष्ठा leon_pci_info	info; /* must be on top of this काष्ठाure */
	काष्ठा grpci1_regs __iomem *regs;		/* GRPCI रेजिस्टर map */
	काष्ठा device		*dev;
	पूर्णांक			pci_err_mask;	/* STATUS रेजिस्टर error mask */
	पूर्णांक			irq;		/* LEON irqctrl GRPCI IRQ */
	अचिन्हित अक्षर		irq_map[4];	/* GRPCI nexus PCI INTX# IRQs */
	अचिन्हित पूर्णांक		irq_err;	/* GRPCI nexus Virt Error IRQ */

	/* AHB PCI Winकरोws */
	अचिन्हित दीर्घ		pci_area;	/* MEMORY */
	अचिन्हित दीर्घ		pci_area_end;
	अचिन्हित दीर्घ		pci_io;		/* I/O */
	अचिन्हित दीर्घ		pci_conf;	/* CONFIGURATION */
	अचिन्हित दीर्घ		pci_conf_end;
	अचिन्हित दीर्घ		pci_io_va;
पूर्ण;

अटल काष्ठा grpci1_priv *grpci1priv;

अटल पूर्णांक grpci1_cfg_w32(काष्ठा grpci1_priv *priv, अचिन्हित पूर्णांक bus,
				अचिन्हित पूर्णांक devfn, पूर्णांक where, u32 val);

अटल पूर्णांक grpci1_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	काष्ठा grpci1_priv *priv = dev->bus->sysdata;
	पूर्णांक irq_group;

	/* Use शेष IRQ decoding on PCI BUS0 according slot numbering */
	irq_group = slot & 0x3;
	pin = ((pin - 1) + irq_group) & 0x3;

	वापस priv->irq_map[pin];
पूर्ण

अटल पूर्णांक grpci1_cfg_r32(काष्ठा grpci1_priv *priv, अचिन्हित पूर्णांक bus,
				अचिन्हित पूर्णांक devfn, पूर्णांक where, u32 *val)
अणु
	u32 *pci_conf, पंचांगp, cfg;

	अगर (where & 0x3)
		वापस -EINVAL;

	अगर (bus == 0) अणु
		devfn += (0x8 * 6); /* start at AD16=Device0 */
	पूर्ण अन्यथा अगर (bus == TGT) अणु
		bus = 0;
		devfn = 0; /* special हाल: bridge controller itself */
	पूर्ण

	/* Select bus */
	cfg = REGLOAD(priv->regs->cfg_stat);
	REGSTORE(priv->regs->cfg_stat, (cfg & ~(0xf << 23)) | (bus << 23));

	/* करो पढ़ो access */
	pci_conf = (u32 *) (priv->pci_conf | (devfn << 8) | (where & 0xfc));
	पंचांगp = LEON3_BYPASS_LOAD_PA(pci_conf);

	/* check अगर master पात was received */
	अगर (REGLOAD(priv->regs->cfg_stat) & CFGSTAT_CTO) अणु
		*val = 0xffffffff;
		/* Clear Master पात bit in PCI cfg space (is set) */
		पंचांगp = REGLOAD(priv->regs->stat_cmd);
		grpci1_cfg_w32(priv, TGT, 0, PCI_COMMAND, पंचांगp);
	पूर्ण अन्यथा अणु
		/* Bus always little endian (unaffected by byte-swapping) */
		*val = swab32(पंचांगp);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक grpci1_cfg_r16(काष्ठा grpci1_priv *priv, अचिन्हित पूर्णांक bus,
				अचिन्हित पूर्णांक devfn, पूर्णांक where, u32 *val)
अणु
	u32 v;
	पूर्णांक ret;

	अगर (where & 0x1)
		वापस -EINVAL;
	ret = grpci1_cfg_r32(priv, bus, devfn, where & ~0x3, &v);
	*val = 0xffff & (v >> (8 * (where & 0x3)));
	वापस ret;
पूर्ण

अटल पूर्णांक grpci1_cfg_r8(काष्ठा grpci1_priv *priv, अचिन्हित पूर्णांक bus,
				अचिन्हित पूर्णांक devfn, पूर्णांक where, u32 *val)
अणु
	u32 v;
	पूर्णांक ret;

	ret = grpci1_cfg_r32(priv, bus, devfn, where & ~0x3, &v);
	*val = 0xff & (v >> (8 * (where & 3)));

	वापस ret;
पूर्ण

अटल पूर्णांक grpci1_cfg_w32(काष्ठा grpci1_priv *priv, अचिन्हित पूर्णांक bus,
				अचिन्हित पूर्णांक devfn, पूर्णांक where, u32 val)
अणु
	अचिन्हित पूर्णांक *pci_conf;
	u32 cfg;

	अगर (where & 0x3)
		वापस -EINVAL;

	अगर (bus == 0) अणु
		devfn += (0x8 * 6); /* start at AD16=Device0 */
	पूर्ण अन्यथा अगर (bus == TGT) अणु
		bus = 0;
		devfn = 0; /* special हाल: bridge controller itself */
	पूर्ण

	/* Select bus */
	cfg = REGLOAD(priv->regs->cfg_stat);
	REGSTORE(priv->regs->cfg_stat, (cfg & ~(0xf << 23)) | (bus << 23));

	pci_conf = (अचिन्हित पूर्णांक *) (priv->pci_conf |
						(devfn << 8) | (where & 0xfc));
	LEON3_BYPASS_STORE_PA(pci_conf, swab32(val));

	वापस 0;
पूर्ण

अटल पूर्णांक grpci1_cfg_w16(काष्ठा grpci1_priv *priv, अचिन्हित पूर्णांक bus,
				अचिन्हित पूर्णांक devfn, पूर्णांक where, u32 val)
अणु
	पूर्णांक ret;
	u32 v;

	अगर (where & 0x1)
		वापस -EINVAL;
	ret = grpci1_cfg_r32(priv, bus, devfn, where&~3, &v);
	अगर (ret)
		वापस ret;
	v = (v & ~(0xffff << (8 * (where & 0x3)))) |
	    ((0xffff & val) << (8 * (where & 0x3)));
	वापस grpci1_cfg_w32(priv, bus, devfn, where & ~0x3, v);
पूर्ण

अटल पूर्णांक grpci1_cfg_w8(काष्ठा grpci1_priv *priv, अचिन्हित पूर्णांक bus,
				अचिन्हित पूर्णांक devfn, पूर्णांक where, u32 val)
अणु
	पूर्णांक ret;
	u32 v;

	ret = grpci1_cfg_r32(priv, bus, devfn, where & ~0x3, &v);
	अगर (ret != 0)
		वापस ret;
	v = (v & ~(0xff << (8 * (where & 0x3)))) |
	    ((0xff & val) << (8 * (where & 0x3)));
	वापस grpci1_cfg_w32(priv, bus, devfn, where & ~0x3, v);
पूर्ण

/* Read from Configuration Space. When entering here the PCI layer has taken
 * the pci_lock spinlock and IRQ is off.
 */
अटल पूर्णांक grpci1_पढ़ो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
			      पूर्णांक where, पूर्णांक size, u32 *val)
अणु
	काष्ठा grpci1_priv *priv = grpci1priv;
	अचिन्हित पूर्णांक busno = bus->number;
	पूर्णांक ret;

	अगर (PCI_SLOT(devfn) > 15 || busno > 15) अणु
		*val = ~0;
		वापस 0;
	पूर्ण

	चयन (size) अणु
	हाल 1:
		ret = grpci1_cfg_r8(priv, busno, devfn, where, val);
		अवरोध;
	हाल 2:
		ret = grpci1_cfg_r16(priv, busno, devfn, where, val);
		अवरोध;
	हाल 4:
		ret = grpci1_cfg_r32(priv, busno, devfn, where, val);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

#अगर_घोषित GRPCI1_DEBUG_CFGACCESS
	prपूर्णांकk(KERN_INFO
		"grpci1_read_config: [%02x:%02x:%x] ofs=%d val=%x size=%d\n",
		busno, PCI_SLOT(devfn), PCI_FUNC(devfn), where, *val, size);
#पूर्ण_अगर

	वापस ret;
पूर्ण

/* Write to Configuration Space. When entering here the PCI layer has taken
 * the pci_lock spinlock and IRQ is off.
 */
अटल पूर्णांक grpci1_ग_लिखो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
			       पूर्णांक where, पूर्णांक size, u32 val)
अणु
	काष्ठा grpci1_priv *priv = grpci1priv;
	अचिन्हित पूर्णांक busno = bus->number;

	अगर (PCI_SLOT(devfn) > 15 || busno > 15)
		वापस 0;

#अगर_घोषित GRPCI1_DEBUG_CFGACCESS
	prपूर्णांकk(KERN_INFO
		"grpci1_write_config: [%02x:%02x:%x] ofs=%d size=%d val=%x\n",
		busno, PCI_SLOT(devfn), PCI_FUNC(devfn), where, size, val);
#पूर्ण_अगर

	चयन (size) अणु
	शेष:
		वापस -EINVAL;
	हाल 1:
		वापस grpci1_cfg_w8(priv, busno, devfn, where, val);
	हाल 2:
		वापस grpci1_cfg_w16(priv, busno, devfn, where, val);
	हाल 4:
		वापस grpci1_cfg_w32(priv, busno, devfn, where, val);
	पूर्ण
पूर्ण

अटल काष्ठा pci_ops grpci1_ops = अणु
	.पढ़ो =		grpci1_पढ़ो_config,
	.ग_लिखो =	grpci1_ग_लिखो_config,
पूर्ण;

/* GENIRQ IRQ chip implementation क्रम grpci1 irqmode=0..2. In configuration
 * 3 where all PCI Interrupts has a separate IRQ on the प्रणाली IRQ controller
 * this is not needed and the standard IRQ controller can be used.
 */

अटल व्योम grpci1_mask_irq(काष्ठा irq_data *data)
अणु
	u32 irqidx;
	काष्ठा grpci1_priv *priv = grpci1priv;

	irqidx = (u32)data->chip_data - 1;
	अगर (irqidx > 3) /* only mask PCI पूर्णांकerrupts here */
		वापस;
	irqidx += IRQ_MASK_BIT;

	REGSTORE(priv->regs->irq, REGLOAD(priv->regs->irq) & ~(1 << irqidx));
पूर्ण

अटल व्योम grpci1_unmask_irq(काष्ठा irq_data *data)
अणु
	u32 irqidx;
	काष्ठा grpci1_priv *priv = grpci1priv;

	irqidx = (u32)data->chip_data - 1;
	अगर (irqidx > 3) /* only unmask PCI पूर्णांकerrupts here */
		वापस;
	irqidx += IRQ_MASK_BIT;

	REGSTORE(priv->regs->irq, REGLOAD(priv->regs->irq) | (1 << irqidx));
पूर्ण

अटल अचिन्हित पूर्णांक grpci1_startup_irq(काष्ठा irq_data *data)
अणु
	grpci1_unmask_irq(data);
	वापस 0;
पूर्ण

अटल व्योम grpci1_shutकरोwn_irq(काष्ठा irq_data *data)
अणु
	grpci1_mask_irq(data);
पूर्ण

अटल काष्ठा irq_chip grpci1_irq = अणु
	.name		= "grpci1",
	.irq_startup	= grpci1_startup_irq,
	.irq_shutकरोwn	= grpci1_shutकरोwn_irq,
	.irq_mask	= grpci1_mask_irq,
	.irq_unmask	= grpci1_unmask_irq,
पूर्ण;

/* Handle one or multiple IRQs from the PCI core */
अटल व्योम grpci1_pci_flow_irq(काष्ठा irq_desc *desc)
अणु
	काष्ठा grpci1_priv *priv = grpci1priv;
	पूर्णांक i, ack = 0;
	अचिन्हित पूर्णांक irqreg;

	irqreg = REGLOAD(priv->regs->irq);
	irqreg = (irqreg >> IRQ_MASK_BIT) & irqreg;

	/* Error Interrupt? */
	अगर (irqreg & IRQ_ALL_ERRORS) अणु
		generic_handle_irq(priv->irq_err);
		ack = 1;
	पूर्ण

	/* PCI Interrupt? */
	अगर (irqreg & IRQ_INTX) अणु
		/* Call respective PCI Interrupt handler */
		क्रम (i = 0; i < 4; i++) अणु
			अगर (irqreg & (1 << i))
				generic_handle_irq(priv->irq_map[i]);
		पूर्ण
		ack = 1;
	पूर्ण

	/*
	 * Call "first level" IRQ chip end-of-irq handler. It will ACK LEON IRQ
	 * Controller, this must be करोne after IRQ sources have been handled to
	 * aव्योम द्विगुन IRQ generation
	 */
	अगर (ack)
		desc->irq_data.chip->irq_eoi(&desc->irq_data);
पूर्ण

/* Create a भव IRQ */
अटल अचिन्हित पूर्णांक grpci1_build_device_irq(अचिन्हित पूर्णांक irq)
अणु
	अचिन्हित पूर्णांक virq = 0, pil;

	pil = 1 << 8;
	virq = irq_alloc(irq, pil);
	अगर (virq == 0)
		जाओ out;

	irq_set_chip_and_handler_name(virq, &grpci1_irq, handle_simple_irq,
				      "pcilvl");
	irq_set_chip_data(virq, (व्योम *)irq);

out:
	वापस virq;
पूर्ण

/*
 * Initialize mappings AMBA<->PCI, clear IRQ state, setup PCI पूर्णांकerface
 *
 * Target BARs:
 *  BAR0: unused in this implementation
 *  BAR1: peripheral DMA to host's memory (size at least 256MByte)
 *  BAR2..BAR5: not implemented in hardware
 */
अटल व्योम grpci1_hw_init(काष्ठा grpci1_priv *priv)
अणु
	u32 ahbadr, bar_sz, data, pciadr;
	काष्ठा grpci1_regs __iomem *regs = priv->regs;

	/* set 1:1 mapping between AHB -> PCI memory space */
	REGSTORE(regs->cfg_stat, priv->pci_area & 0xf0000000);

	/* map PCI accesses to target BAR1 to Linux kernel memory 1:1 */
	ahbadr = 0xf0000000 & (u32)__pa(PAGE_ALIGN((अचिन्हित दीर्घ) &_end));
	REGSTORE(regs->page1, ahbadr);

	/* translate I/O accesses to 0, I/O Space always @ PCI low 64Kbytes */
	REGSTORE(regs->iomap, REGLOAD(regs->iomap) & 0x0000ffff);

	/* disable and clear pending पूर्णांकerrupts */
	REGSTORE(regs->irq, 0);

	/* Setup BAR0 outside access range so that it करोes not conflict with
	 * peripheral DMA. There is no need to set up the PAGE0 रेजिस्टर.
	 */
	grpci1_cfg_w32(priv, TGT, 0, PCI_BASE_ADDRESS_0, 0xffffffff);
	grpci1_cfg_r32(priv, TGT, 0, PCI_BASE_ADDRESS_0, &bar_sz);
	bar_sz = ~bar_sz + 1;
	pciadr = priv->pci_area - bar_sz;
	grpci1_cfg_w32(priv, TGT, 0, PCI_BASE_ADDRESS_0, pciadr);

	/*
	 * Setup the Host's PCI Target BAR1 क्रम other peripherals to access,
	 * and करो DMA to the host's memory.
	 */
	grpci1_cfg_w32(priv, TGT, 0, PCI_BASE_ADDRESS_1, ahbadr);

	/*
	 * Setup Latency Timer and cache line size. Default cache line
	 * size will result in poor perक्रमmance (256 word fetches), 0xff
	 * will set it according to the max size of the PCI FIFO.
	 */
	grpci1_cfg_w8(priv, TGT, 0, PCI_CACHE_LINE_SIZE, 0xff);
	grpci1_cfg_w8(priv, TGT, 0, PCI_LATENCY_TIMER, 0x40);

	/* set as bus master, enable pci memory responses, clear status bits */
	grpci1_cfg_r32(priv, TGT, 0, PCI_COMMAND, &data);
	data |= (PCI_COMMAND_MEMORY | PCI_COMMAND_MASTER);
	grpci1_cfg_w32(priv, TGT, 0, PCI_COMMAND, data);
पूर्ण

अटल irqवापस_t grpci1_jump_पूर्णांकerrupt(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा grpci1_priv *priv = arg;
	dev_err(priv->dev, "Jump IRQ happened\n");
	वापस IRQ_NONE;
पूर्ण

/* Handle GRPCI1 Error Interrupt */
अटल irqवापस_t grpci1_err_पूर्णांकerrupt(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा grpci1_priv *priv = arg;
	u32 status;

	grpci1_cfg_r16(priv, TGT, 0, PCI_STATUS, &status);
	status &= priv->pci_err_mask;

	अगर (status == 0)
		वापस IRQ_NONE;

	अगर (status & PCI_STATUS_PARITY)
		dev_err(priv->dev, "Data Parity Error\n");

	अगर (status & PCI_STATUS_SIG_TARGET_ABORT)
		dev_err(priv->dev, "Signalled Target Abort\n");

	अगर (status & PCI_STATUS_REC_TARGET_ABORT)
		dev_err(priv->dev, "Received Target Abort\n");

	अगर (status & PCI_STATUS_REC_MASTER_ABORT)
		dev_err(priv->dev, "Received Master Abort\n");

	अगर (status & PCI_STATUS_SIG_SYSTEM_ERROR)
		dev_err(priv->dev, "Signalled System Error\n");

	अगर (status & PCI_STATUS_DETECTED_PARITY)
		dev_err(priv->dev, "Parity Error\n");

	/* Clear handled INT TYPE IRQs */
	grpci1_cfg_w16(priv, TGT, 0, PCI_STATUS, status);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक grpci1_of_probe(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा grpci1_regs __iomem *regs;
	काष्ठा grpci1_priv *priv;
	पूर्णांक err, len;
	स्थिर पूर्णांक *पंचांगp;
	u32 cfg, size, err_mask;
	काष्ठा resource *res;

	अगर (grpci1priv) अणु
		dev_err(&ofdev->dev, "only one GRPCI1 supported\n");
		वापस -ENODEV;
	पूर्ण

	अगर (ofdev->num_resources < 3) अणु
		dev_err(&ofdev->dev, "not enough APB/AHB resources\n");
		वापस -EIO;
	पूर्ण

	priv = devm_kzalloc(&ofdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv) अणु
		dev_err(&ofdev->dev, "memory allocation failed\n");
		वापस -ENOMEM;
	पूर्ण
	platक्रमm_set_drvdata(ofdev, priv);
	priv->dev = &ofdev->dev;

	/* find device रेजिस्टर base address */
	res = platक्रमm_get_resource(ofdev, IORESOURCE_MEM, 0);
	regs = devm_ioremap_resource(&ofdev->dev, res);
	अगर (IS_ERR(regs))
		वापस PTR_ERR(regs);

	/*
	 * check that we're in Host Slot and that we can act as a Host Bridge
	 * and not only as target/peripheral.
	 */
	cfg = REGLOAD(regs->cfg_stat);
	अगर ((cfg & CFGSTAT_HOST) == 0) अणु
		dev_err(&ofdev->dev, "not in host system slot\n");
		वापस -EIO;
	पूर्ण

	/* check that BAR1 support 256 MByte so that we can map kernel space */
	REGSTORE(regs->page1, 0xffffffff);
	size = ~REGLOAD(regs->page1) + 1;
	अगर (size < 0x10000000) अणु
		dev_err(&ofdev->dev, "BAR1 must be at least 256MByte\n");
		वापस -EIO;
	पूर्ण

	/* hardware must support little-endian PCI (byte-twisting) */
	अगर ((REGLOAD(regs->page0) & PAGE0_BTEN) == 0) अणु
		dev_err(&ofdev->dev, "byte-twisting is required\n");
		वापस -EIO;
	पूर्ण

	priv->regs = regs;
	priv->irq = irq_of_parse_and_map(ofdev->dev.of_node, 0);
	dev_info(&ofdev->dev, "host found at 0x%p, irq%d\n", regs, priv->irq);

	/* Find PCI Memory, I/O and Configuration Space Winकरोws */
	priv->pci_area = ofdev->resource[1].start;
	priv->pci_area_end = ofdev->resource[1].end+1;
	priv->pci_io = ofdev->resource[2].start;
	priv->pci_conf = ofdev->resource[2].start + 0x10000;
	priv->pci_conf_end = priv->pci_conf + 0x10000;
	priv->pci_io_va = (अचिन्हित दीर्घ)ioremap(priv->pci_io, 0x10000);
	अगर (!priv->pci_io_va) अणु
		dev_err(&ofdev->dev, "unable to map PCI I/O area\n");
		वापस -EIO;
	पूर्ण

	prपूर्णांकk(KERN_INFO
		"GRPCI1: MEMORY SPACE [0x%08lx - 0x%08lx]\n"
		"        I/O    SPACE [0x%08lx - 0x%08lx]\n"
		"        CONFIG SPACE [0x%08lx - 0x%08lx]\n",
		priv->pci_area, priv->pci_area_end-1,
		priv->pci_io, priv->pci_conf-1,
		priv->pci_conf, priv->pci_conf_end-1);

	/*
	 * I/O Space resources in I/O Winकरोw mapped पूर्णांकo Virtual Adr Space
	 * We never use low 4KB because some devices seem have problems using
	 * address 0.
	 */
	priv->info.io_space.name = "GRPCI1 PCI I/O Space";
	priv->info.io_space.start = priv->pci_io_va + 0x1000;
	priv->info.io_space.end = priv->pci_io_va + 0x10000 - 1;
	priv->info.io_space.flags = IORESOURCE_IO;

	/*
	 * grpci1 has no prefetchable memory, map everything as
	 * non-prefetchable memory
	 */
	priv->info.mem_space.name = "GRPCI1 PCI MEM Space";
	priv->info.mem_space.start = priv->pci_area;
	priv->info.mem_space.end = priv->pci_area_end - 1;
	priv->info.mem_space.flags = IORESOURCE_MEM;

	अगर (request_resource(&iomem_resource, &priv->info.mem_space) < 0) अणु
		dev_err(&ofdev->dev, "unable to request PCI memory area\n");
		err = -ENOMEM;
		जाओ err1;
	पूर्ण

	अगर (request_resource(&ioport_resource, &priv->info.io_space) < 0) अणु
		dev_err(&ofdev->dev, "unable to request PCI I/O area\n");
		err = -ENOMEM;
		जाओ err2;
	पूर्ण

	/* setup maximum supported PCI buses */
	priv->info.busn.name = "GRPCI1 busn";
	priv->info.busn.start = 0;
	priv->info.busn.end = 15;

	grpci1priv = priv;

	/* Initialize hardware */
	grpci1_hw_init(priv);

	/*
	 * Get PCI Interrupt to System IRQ mapping and setup IRQ handling
	 * Error IRQ. All PCI and PCI-Error पूर्णांकerrupts are shared using the
	 * same प्रणाली IRQ.
	 */
	leon_update_virq_handling(priv->irq, grpci1_pci_flow_irq, "pcilvl", 0);

	priv->irq_map[0] = grpci1_build_device_irq(1);
	priv->irq_map[1] = grpci1_build_device_irq(2);
	priv->irq_map[2] = grpci1_build_device_irq(3);
	priv->irq_map[3] = grpci1_build_device_irq(4);
	priv->irq_err = grpci1_build_device_irq(5);

	prपूर्णांकk(KERN_INFO "        PCI INTA..D#: IRQ%d, IRQ%d, IRQ%d, IRQ%d\n",
		priv->irq_map[0], priv->irq_map[1], priv->irq_map[2],
		priv->irq_map[3]);

	/* Enable IRQs on LEON IRQ controller */
	err = devm_request_irq(&ofdev->dev, priv->irq, grpci1_jump_पूर्णांकerrupt, 0,
				"GRPCI1_JUMP", priv);
	अगर (err) अणु
		dev_err(&ofdev->dev, "ERR IRQ request failed: %d\n", err);
		जाओ err3;
	पूर्ण

	/* Setup IRQ handler क्रम access errors */
	err = devm_request_irq(&ofdev->dev, priv->irq_err,
				grpci1_err_पूर्णांकerrupt, IRQF_SHARED, "GRPCI1_ERR",
				priv);
	अगर (err) अणु
		dev_err(&ofdev->dev, "ERR VIRQ request failed: %d\n", err);
		जाओ err3;
	पूर्ण

	पंचांगp = of_get_property(ofdev->dev.of_node, "all_pci_errors", &len);
	अगर (पंचांगp && (len == 4)) अणु
		priv->pci_err_mask = ALL_PCI_ERRORS;
		err_mask = IRQ_ALL_ERRORS << IRQ_MASK_BIT;
	पूर्ण अन्यथा अणु
		priv->pci_err_mask = DEF_PCI_ERRORS;
		err_mask = IRQ_DEF_ERRORS << IRQ_MASK_BIT;
	पूर्ण

	/*
	 * Enable Error Interrupts. PCI पूर्णांकerrupts are unmasked once request_irq
	 * is called by the PCI Device drivers
	 */
	REGSTORE(regs->irq, err_mask);

	/* Init common layer and scan buses */
	priv->info.ops = &grpci1_ops;
	priv->info.map_irq = grpci1_map_irq;
	leon_pci_init(ofdev, &priv->info);

	वापस 0;

err3:
	release_resource(&priv->info.io_space);
err2:
	release_resource(&priv->info.mem_space);
err1:
	iounmap((व्योम __iomem *)priv->pci_io_va);
	grpci1priv = शून्य;
	वापस err;
पूर्ण

अटल स्थिर काष्ठा of_device_id grpci1_of_match[] __initस्थिर = अणु
	अणु
	 .name = "GAISLER_PCIFBRG",
	 पूर्ण,
	अणु
	 .name = "01_014",
	 पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver grpci1_of_driver = अणु
	.driver = अणु
		.name = "grpci1",
		.of_match_table = grpci1_of_match,
	पूर्ण,
	.probe = grpci1_of_probe,
पूर्ण;

अटल पूर्णांक __init grpci1_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&grpci1_of_driver);
पूर्ण

subsys_initcall(grpci1_init);
