<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * leon_pci_grpci2.c: GRPCI2 Host PCI driver
 *
 * Copyright (C) 2011 Aeroflex Gaisler AB, Daniel Hellstrom
 *
 */

#समावेश <linux/of_device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/export.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/leon.h>
#समावेश <यंत्र/vaddrs.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/leon_pci.h>

#समावेश "irq.h"

काष्ठा grpci2_barcfg अणु
	अचिन्हित दीर्घ pciadr;	/* PCI Space Address */
	अचिन्हित दीर्घ ahbadr;	/* PCI Base address mapped to this AHB addr */
पूर्ण;

/* Device Node Configuration options:
 *  - barcfgs    : Custom Configuration of Host's 6 target BARs
 *  - irq_mask   : Limit which PCI पूर्णांकerrupts are enabled
 *  - करो_reset   : Force PCI Reset on startup
 *
 * barcfgs
 * =======
 *
 * Optional custom Target BAR configuration (see काष्ठा grpci2_barcfg). All
 * addresses are physical. Array always contains 6 elements (len=2*4*6 bytes)
 *
 * -1 means not configured (let host driver करो शेष setup).
 *
 * [i*2+0] = PCI Address of BAR[i] on target पूर्णांकerface
 * [i*2+1] = Accessing PCI address of BAR[i] result in this AMBA address
 *
 *
 * irq_mask
 * ========
 *
 * Limit which PCI पूर्णांकerrupts are enabled. 0=Disable, 1=Enable. By शेष
 * all are enabled. Use this when PCI पूर्णांकerrupt pins are भग्नing on PCB.
 * पूर्णांक, len=4.
 *  bit0 = PCI INTA#
 *  bit1 = PCI INTB#
 *  bit2 = PCI INTC#
 *  bit3 = PCI INTD#
 *
 *
 * reset
 * =====
 *
 * Force PCI reset on startup. पूर्णांक, len=4
 */

/* Enable Debugging Configuration Space Access */
#अघोषित GRPCI2_DEBUG_CFGACCESS

/*
 * GRPCI2 APB Register MAP
 */
काष्ठा grpci2_regs अणु
	अचिन्हित पूर्णांक ctrl;		/* 0x00 Control */
	अचिन्हित पूर्णांक sts_cap;		/* 0x04 Status / Capabilities */
	पूर्णांक res1;			/* 0x08 */
	अचिन्हित पूर्णांक io_map;		/* 0x0C I/O Map address */
	अचिन्हित पूर्णांक dma_ctrl;		/* 0x10 DMA */
	अचिन्हित पूर्णांक dma_bdbase;	/* 0x14 DMA */
	पूर्णांक res2[2];			/* 0x18 */
	अचिन्हित पूर्णांक bars[6];		/* 0x20 पढ़ो-only PCI BARs */
	पूर्णांक res3[2];			/* 0x38 */
	अचिन्हित पूर्णांक ahbmst_map[16];	/* 0x40 AHB->PCI Map per AHB Master */

	/* PCI Trace Buffer Registers (OPTIONAL) */
	अचिन्हित पूर्णांक t_ctrl;		/* 0x80 */
	अचिन्हित पूर्णांक t_cnt;		/* 0x84 */
	अचिन्हित पूर्णांक t_adpat;		/* 0x88 */
	अचिन्हित पूर्णांक t_admask;		/* 0x8C */
	अचिन्हित पूर्णांक t_sigpat;		/* 0x90 */
	अचिन्हित पूर्णांक t_sigmask;		/* 0x94 */
	अचिन्हित पूर्णांक t_adstate;		/* 0x98 */
	अचिन्हित पूर्णांक t_sigstate;	/* 0x9C */
पूर्ण;

#घोषणा REGLOAD(a)	(be32_to_cpu(__raw_पढ़ोl(&(a))))
#घोषणा REGSTORE(a, v)	(__raw_ग_लिखोl(cpu_to_be32(v), &(a)))

#घोषणा CTRL_BUS_BIT 16

#घोषणा CTRL_RESET (1<<31)
#घोषणा CTRL_SI (1<<27)
#घोषणा CTRL_PE (1<<26)
#घोषणा CTRL_EI (1<<25)
#घोषणा CTRL_ER (1<<24)
#घोषणा CTRL_BUS (0xff<<CTRL_BUS_BIT)
#घोषणा CTRL_HOSTINT 0xf

#घोषणा STS_HOST_BIT	31
#घोषणा STS_MST_BIT	30
#घोषणा STS_TAR_BIT	29
#घोषणा STS_DMA_BIT	28
#घोषणा STS_DI_BIT	27
#घोषणा STS_HI_BIT	26
#घोषणा STS_IRQMODE_BIT	24
#घोषणा STS_TRACE_BIT	23
#घोषणा STS_CFGERRVALID_BIT 20
#घोषणा STS_CFGERR_BIT	19
#घोषणा STS_INTTYPE_BIT	12
#घोषणा STS_INTSTS_BIT	8
#घोषणा STS_FDEPTH_BIT	2
#घोषणा STS_FNUM_BIT	0

#घोषणा STS_HOST	(1<<STS_HOST_BIT)
#घोषणा STS_MST		(1<<STS_MST_BIT)
#घोषणा STS_TAR		(1<<STS_TAR_BIT)
#घोषणा STS_DMA		(1<<STS_DMA_BIT)
#घोषणा STS_DI		(1<<STS_DI_BIT)
#घोषणा STS_HI		(1<<STS_HI_BIT)
#घोषणा STS_IRQMODE	(0x3<<STS_IRQMODE_BIT)
#घोषणा STS_TRACE	(1<<STS_TRACE_BIT)
#घोषणा STS_CFGERRVALID	(1<<STS_CFGERRVALID_BIT)
#घोषणा STS_CFGERR	(1<<STS_CFGERR_BIT)
#घोषणा STS_INTTYPE	(0x3f<<STS_INTTYPE_BIT)
#घोषणा STS_INTSTS	(0xf<<STS_INTSTS_BIT)
#घोषणा STS_FDEPTH	(0x7<<STS_FDEPTH_BIT)
#घोषणा STS_FNUM	(0x3<<STS_FNUM_BIT)

#घोषणा STS_ISYSERR	(1<<17)
#घोषणा STS_IDMA	(1<<16)
#घोषणा STS_IDMAERR	(1<<15)
#घोषणा STS_IMSTABRT	(1<<14)
#घोषणा STS_ITGTABRT	(1<<13)
#घोषणा STS_IPARERR	(1<<12)

#घोषणा STS_ERR_IRQ (STS_ISYSERR | STS_IMSTABRT | STS_ITGTABRT | STS_IPARERR)

काष्ठा grpci2_bd_chan अणु
	अचिन्हित पूर्णांक ctrl;	/* 0x00 DMA Control */
	अचिन्हित पूर्णांक nchan;	/* 0x04 Next DMA Channel Address */
	अचिन्हित पूर्णांक nbd;	/* 0x08 Next Data Descriptor in chan */
	अचिन्हित पूर्णांक res;	/* 0x0C Reserved */
पूर्ण;

#घोषणा BD_CHAN_EN		0x80000000
#घोषणा BD_CHAN_TYPE		0x00300000
#घोषणा BD_CHAN_BDCNT		0x0000ffff
#घोषणा BD_CHAN_EN_BIT		31
#घोषणा BD_CHAN_TYPE_BIT	20
#घोषणा BD_CHAN_BDCNT_BIT	0

काष्ठा grpci2_bd_data अणु
	अचिन्हित पूर्णांक ctrl;	/* 0x00 DMA Data Control */
	अचिन्हित पूर्णांक pci_adr;	/* 0x04 PCI Start Address */
	अचिन्हित पूर्णांक ahb_adr;	/* 0x08 AHB Start address */
	अचिन्हित पूर्णांक next;	/* 0x0C Next Data Descriptor in chan */
पूर्ण;

#घोषणा BD_DATA_EN		0x80000000
#घोषणा BD_DATA_IE		0x40000000
#घोषणा BD_DATA_DR		0x20000000
#घोषणा BD_DATA_TYPE		0x00300000
#घोषणा BD_DATA_ER		0x00080000
#घोषणा BD_DATA_LEN		0x0000ffff
#घोषणा BD_DATA_EN_BIT		31
#घोषणा BD_DATA_IE_BIT		30
#घोषणा BD_DATA_DR_BIT		29
#घोषणा BD_DATA_TYPE_BIT	20
#घोषणा BD_DATA_ER_BIT		19
#घोषणा BD_DATA_LEN_BIT		0

/* GRPCI2 Capability */
काष्ठा grpci2_cap_first अणु
	अचिन्हित पूर्णांक ctrl;
	अचिन्हित पूर्णांक pci2ahb_map[6];
	अचिन्हित पूर्णांक ext2ahb_map;
	अचिन्हित पूर्णांक io_map;
	अचिन्हित पूर्णांक pcibar_size[6];
पूर्ण;
#घोषणा CAP9_CTRL_OFS 0
#घोषणा CAP9_BAR_OFS 0x4
#घोषणा CAP9_IOMAP_OFS 0x20
#घोषणा CAP9_BARSIZE_OFS 0x24

#घोषणा TGT 256

काष्ठा grpci2_priv अणु
	काष्ठा leon_pci_info	info; /* must be on top of this काष्ठाure */
	काष्ठा grpci2_regs __iomem *regs;
	अक्षर			irq;
	अक्षर			irq_mode; /* IRQ Mode from CAPSTS REG */
	अक्षर			bt_enabled;
	अक्षर			करो_reset;
	अक्षर			irq_mask;
	u32			pciid; /* PCI ID of Host */
	अचिन्हित अक्षर		irq_map[4];

	/* Virtual IRQ numbers */
	अचिन्हित पूर्णांक		virq_err;
	अचिन्हित पूर्णांक		virq_dma;

	/* AHB PCI Winकरोws */
	अचिन्हित दीर्घ		pci_area;	/* MEMORY */
	अचिन्हित दीर्घ		pci_area_end;
	अचिन्हित दीर्घ		pci_io;		/* I/O */
	अचिन्हित दीर्घ		pci_conf;	/* CONFIGURATION */
	अचिन्हित दीर्घ		pci_conf_end;
	अचिन्हित दीर्घ		pci_io_va;

	काष्ठा grpci2_barcfg	tgtbars[6];
पूर्ण;

अटल DEFINE_SPINLOCK(grpci2_dev_lock);
अटल काष्ठा grpci2_priv *grpci2priv;

अटल पूर्णांक grpci2_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	काष्ठा grpci2_priv *priv = dev->bus->sysdata;
	पूर्णांक irq_group;

	/* Use शेष IRQ decoding on PCI BUS0 according slot numbering */
	irq_group = slot & 0x3;
	pin = ((pin - 1) + irq_group) & 0x3;

	वापस priv->irq_map[pin];
पूर्ण

अटल पूर्णांक grpci2_cfg_r32(काष्ठा grpci2_priv *priv, अचिन्हित पूर्णांक bus,
				अचिन्हित पूर्णांक devfn, पूर्णांक where, u32 *val)
अणु
	अचिन्हित पूर्णांक *pci_conf;
	अचिन्हित दीर्घ flags;
	u32 पंचांगp;

	अगर (where & 0x3)
		वापस -EINVAL;

	अगर (bus == 0) अणु
		devfn += (0x8 * 6); /* start at AD16=Device0 */
	पूर्ण अन्यथा अगर (bus == TGT) अणु
		bus = 0;
		devfn = 0; /* special हाल: bridge controller itself */
	पूर्ण

	/* Select bus */
	spin_lock_irqsave(&grpci2_dev_lock, flags);
	REGSTORE(priv->regs->ctrl, (REGLOAD(priv->regs->ctrl) & ~(0xff << 16)) |
				   (bus << 16));
	spin_unlock_irqrestore(&grpci2_dev_lock, flags);

	/* clear old status */
	REGSTORE(priv->regs->sts_cap, (STS_CFGERR | STS_CFGERRVALID));

	pci_conf = (अचिन्हित पूर्णांक *) (priv->pci_conf |
						(devfn << 8) | (where & 0xfc));
	पंचांगp = LEON3_BYPASS_LOAD_PA(pci_conf);

	/* Wait until GRPCI2 संकेतs that CFG access is करोne, it should be
	 * करोne instantaneously unless a DMA operation is ongoing...
	 */
	जबतक ((REGLOAD(priv->regs->sts_cap) & STS_CFGERRVALID) == 0)
		;

	अगर (REGLOAD(priv->regs->sts_cap) & STS_CFGERR) अणु
		*val = 0xffffffff;
	पूर्ण अन्यथा अणु
		/* Bus always little endian (unaffected by byte-swapping) */
		*val = swab32(पंचांगp);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक grpci2_cfg_r16(काष्ठा grpci2_priv *priv, अचिन्हित पूर्णांक bus,
				अचिन्हित पूर्णांक devfn, पूर्णांक where, u32 *val)
अणु
	u32 v;
	पूर्णांक ret;

	अगर (where & 0x1)
		वापस -EINVAL;
	ret = grpci2_cfg_r32(priv, bus, devfn, where & ~0x3, &v);
	*val = 0xffff & (v >> (8 * (where & 0x3)));
	वापस ret;
पूर्ण

अटल पूर्णांक grpci2_cfg_r8(काष्ठा grpci2_priv *priv, अचिन्हित पूर्णांक bus,
				अचिन्हित पूर्णांक devfn, पूर्णांक where, u32 *val)
अणु
	u32 v;
	पूर्णांक ret;

	ret = grpci2_cfg_r32(priv, bus, devfn, where & ~0x3, &v);
	*val = 0xff & (v >> (8 * (where & 3)));

	वापस ret;
पूर्ण

अटल पूर्णांक grpci2_cfg_w32(काष्ठा grpci2_priv *priv, अचिन्हित पूर्णांक bus,
				अचिन्हित पूर्णांक devfn, पूर्णांक where, u32 val)
अणु
	अचिन्हित पूर्णांक *pci_conf;
	अचिन्हित दीर्घ flags;

	अगर (where & 0x3)
		वापस -EINVAL;

	अगर (bus == 0) अणु
		devfn += (0x8 * 6); /* start at AD16=Device0 */
	पूर्ण अन्यथा अगर (bus == TGT) अणु
		bus = 0;
		devfn = 0; /* special हाल: bridge controller itself */
	पूर्ण

	/* Select bus */
	spin_lock_irqsave(&grpci2_dev_lock, flags);
	REGSTORE(priv->regs->ctrl, (REGLOAD(priv->regs->ctrl) & ~(0xff << 16)) |
				   (bus << 16));
	spin_unlock_irqrestore(&grpci2_dev_lock, flags);

	/* clear old status */
	REGSTORE(priv->regs->sts_cap, (STS_CFGERR | STS_CFGERRVALID));

	pci_conf = (अचिन्हित पूर्णांक *) (priv->pci_conf |
						(devfn << 8) | (where & 0xfc));
	LEON3_BYPASS_STORE_PA(pci_conf, swab32(val));

	/* Wait until GRPCI2 संकेतs that CFG access is करोne, it should be
	 * करोne instantaneously unless a DMA operation is ongoing...
	 */
	जबतक ((REGLOAD(priv->regs->sts_cap) & STS_CFGERRVALID) == 0)
		;

	वापस 0;
पूर्ण

अटल पूर्णांक grpci2_cfg_w16(काष्ठा grpci2_priv *priv, अचिन्हित पूर्णांक bus,
				अचिन्हित पूर्णांक devfn, पूर्णांक where, u32 val)
अणु
	पूर्णांक ret;
	u32 v;

	अगर (where & 0x1)
		वापस -EINVAL;
	ret = grpci2_cfg_r32(priv, bus, devfn, where&~3, &v);
	अगर (ret)
		वापस ret;
	v = (v & ~(0xffff << (8 * (where & 0x3)))) |
	    ((0xffff & val) << (8 * (where & 0x3)));
	वापस grpci2_cfg_w32(priv, bus, devfn, where & ~0x3, v);
पूर्ण

अटल पूर्णांक grpci2_cfg_w8(काष्ठा grpci2_priv *priv, अचिन्हित पूर्णांक bus,
				अचिन्हित पूर्णांक devfn, पूर्णांक where, u32 val)
अणु
	पूर्णांक ret;
	u32 v;

	ret = grpci2_cfg_r32(priv, bus, devfn, where & ~0x3, &v);
	अगर (ret != 0)
		वापस ret;
	v = (v & ~(0xff << (8 * (where & 0x3)))) |
	    ((0xff & val) << (8 * (where & 0x3)));
	वापस grpci2_cfg_w32(priv, bus, devfn, where & ~0x3, v);
पूर्ण

/* Read from Configuration Space. When entering here the PCI layer has taken
 * the pci_lock spinlock and IRQ is off.
 */
अटल पूर्णांक grpci2_पढ़ो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
			      पूर्णांक where, पूर्णांक size, u32 *val)
अणु
	काष्ठा grpci2_priv *priv = grpci2priv;
	अचिन्हित पूर्णांक busno = bus->number;
	पूर्णांक ret;

	अगर (PCI_SLOT(devfn) > 15 || busno > 255) अणु
		*val = ~0;
		वापस 0;
	पूर्ण

	चयन (size) अणु
	हाल 1:
		ret = grpci2_cfg_r8(priv, busno, devfn, where, val);
		अवरोध;
	हाल 2:
		ret = grpci2_cfg_r16(priv, busno, devfn, where, val);
		अवरोध;
	हाल 4:
		ret = grpci2_cfg_r32(priv, busno, devfn, where, val);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

#अगर_घोषित GRPCI2_DEBUG_CFGACCESS
	prपूर्णांकk(KERN_INFO "grpci2_read_config: [%02x:%02x:%x] ofs=%d val=%x "
		"size=%d\n", busno, PCI_SLOT(devfn), PCI_FUNC(devfn), where,
		*val, size);
#पूर्ण_अगर

	वापस ret;
पूर्ण

/* Write to Configuration Space. When entering here the PCI layer has taken
 * the pci_lock spinlock and IRQ is off.
 */
अटल पूर्णांक grpci2_ग_लिखो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
			       पूर्णांक where, पूर्णांक size, u32 val)
अणु
	काष्ठा grpci2_priv *priv = grpci2priv;
	अचिन्हित पूर्णांक busno = bus->number;

	अगर (PCI_SLOT(devfn) > 15 || busno > 255)
		वापस 0;

#अगर_घोषित GRPCI2_DEBUG_CFGACCESS
	prपूर्णांकk(KERN_INFO "grpci2_write_config: [%02x:%02x:%x] ofs=%d size=%d "
		"val=%x\n", busno, PCI_SLOT(devfn), PCI_FUNC(devfn),
		where, size, val);
#पूर्ण_अगर

	चयन (size) अणु
	शेष:
		वापस -EINVAL;
	हाल 1:
		वापस grpci2_cfg_w8(priv, busno, devfn, where, val);
	हाल 2:
		वापस grpci2_cfg_w16(priv, busno, devfn, where, val);
	हाल 4:
		वापस grpci2_cfg_w32(priv, busno, devfn, where, val);
	पूर्ण
पूर्ण

अटल काष्ठा pci_ops grpci2_ops = अणु
	.पढ़ो =		grpci2_पढ़ो_config,
	.ग_लिखो =	grpci2_ग_लिखो_config,
पूर्ण;

/* GENIRQ IRQ chip implementation क्रम GRPCI2 irqmode=0..2. In configuration
 * 3 where all PCI Interrupts has a separate IRQ on the प्रणाली IRQ controller
 * this is not needed and the standard IRQ controller can be used.
 */

अटल व्योम grpci2_mask_irq(काष्ठा irq_data *data)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक irqidx;
	काष्ठा grpci2_priv *priv = grpci2priv;

	irqidx = (अचिन्हित पूर्णांक)data->chip_data - 1;
	अगर (irqidx > 3) /* only mask PCI पूर्णांकerrupts here */
		वापस;

	spin_lock_irqsave(&grpci2_dev_lock, flags);
	REGSTORE(priv->regs->ctrl, REGLOAD(priv->regs->ctrl) & ~(1 << irqidx));
	spin_unlock_irqrestore(&grpci2_dev_lock, flags);
पूर्ण

अटल व्योम grpci2_unmask_irq(काष्ठा irq_data *data)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक irqidx;
	काष्ठा grpci2_priv *priv = grpci2priv;

	irqidx = (अचिन्हित पूर्णांक)data->chip_data - 1;
	अगर (irqidx > 3) /* only unmask PCI पूर्णांकerrupts here */
		वापस;

	spin_lock_irqsave(&grpci2_dev_lock, flags);
	REGSTORE(priv->regs->ctrl, REGLOAD(priv->regs->ctrl) | (1 << irqidx));
	spin_unlock_irqrestore(&grpci2_dev_lock, flags);
पूर्ण

अटल अचिन्हित पूर्णांक grpci2_startup_irq(काष्ठा irq_data *data)
अणु
	grpci2_unmask_irq(data);
	वापस 0;
पूर्ण

अटल व्योम grpci2_shutकरोwn_irq(काष्ठा irq_data *data)
अणु
	grpci2_mask_irq(data);
पूर्ण

अटल काष्ठा irq_chip grpci2_irq = अणु
	.name		= "grpci2",
	.irq_startup	= grpci2_startup_irq,
	.irq_shutकरोwn	= grpci2_shutकरोwn_irq,
	.irq_mask	= grpci2_mask_irq,
	.irq_unmask	= grpci2_unmask_irq,
पूर्ण;

/* Handle one or multiple IRQs from the PCI core */
अटल व्योम grpci2_pci_flow_irq(काष्ठा irq_desc *desc)
अणु
	काष्ठा grpci2_priv *priv = grpci2priv;
	पूर्णांक i, ack = 0;
	अचिन्हित पूर्णांक ctrl, sts_cap, pci_पूर्णांकs;

	ctrl = REGLOAD(priv->regs->ctrl);
	sts_cap = REGLOAD(priv->regs->sts_cap);

	/* Error Interrupt? */
	अगर (sts_cap & STS_ERR_IRQ) अणु
		generic_handle_irq(priv->virq_err);
		ack = 1;
	पूर्ण

	/* PCI Interrupt? */
	pci_पूर्णांकs = ((~sts_cap) >> STS_INTSTS_BIT) & ctrl & CTRL_HOSTINT;
	अगर (pci_पूर्णांकs) अणु
		/* Call respective PCI Interrupt handler */
		क्रम (i = 0; i < 4; i++) अणु
			अगर (pci_पूर्णांकs & (1 << i))
				generic_handle_irq(priv->irq_map[i]);
		पूर्ण
		ack = 1;
	पूर्ण

	/*
	 * Decode DMA Interrupt only when shared with Err and PCI INTX#, when
	 * the DMA is a unique IRQ the DMA पूर्णांकerrupts करोesn't end up here, they
	 * goes directly to DMA ISR.
	 */
	अगर ((priv->irq_mode == 0) && (sts_cap & (STS_IDMA | STS_IDMAERR))) अणु
		generic_handle_irq(priv->virq_dma);
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
अटल अचिन्हित पूर्णांक grpci2_build_device_irq(अचिन्हित पूर्णांक irq)
अणु
	अचिन्हित पूर्णांक virq = 0, pil;

	pil = 1 << 8;
	virq = irq_alloc(irq, pil);
	अगर (virq == 0)
		जाओ out;

	irq_set_chip_and_handler_name(virq, &grpci2_irq, handle_simple_irq,
				      "pcilvl");
	irq_set_chip_data(virq, (व्योम *)irq);

out:
	वापस virq;
पूर्ण

अटल व्योम grpci2_hw_init(काष्ठा grpci2_priv *priv)
अणु
	u32 ahbadr, pciadr, bar_sz, capptr, io_map, data;
	काष्ठा grpci2_regs __iomem *regs = priv->regs;
	पूर्णांक i;
	काष्ठा grpci2_barcfg *barcfg = priv->tgtbars;

	/* Reset any earlier setup */
	अगर (priv->करो_reset) अणु
		prपूर्णांकk(KERN_INFO "GRPCI2: Resetting PCI bus\n");
		REGSTORE(regs->ctrl, CTRL_RESET);
		ssleep(1); /* Wait क्रम boards to settle */
	पूर्ण
	REGSTORE(regs->ctrl, 0);
	REGSTORE(regs->sts_cap, ~0); /* Clear Status */
	REGSTORE(regs->dma_ctrl, 0);
	REGSTORE(regs->dma_bdbase, 0);

	/* Translate I/O accesses to 0, I/O Space always @ PCI low 64Kbytes */
	REGSTORE(regs->io_map, REGLOAD(regs->io_map) & 0x0000ffff);

	/* set 1:1 mapping between AHB -> PCI memory space, क्रम all Masters
	 * Each AHB master has it's own mapping रेजिस्टरs. Max 16 AHB masters.
	 */
	क्रम (i = 0; i < 16; i++)
		REGSTORE(regs->ahbmst_map[i], priv->pci_area);

	/* Get the GRPCI2 Host PCI ID */
	grpci2_cfg_r32(priv, TGT, 0, PCI_VENDOR_ID, &priv->pciid);

	/* Get address to first (always defined) capability काष्ठाure */
	grpci2_cfg_r8(priv, TGT, 0, PCI_CAPABILITY_LIST, &capptr);

	/* Enable/Disable Byte twisting */
	grpci2_cfg_r32(priv, TGT, 0, capptr+CAP9_IOMAP_OFS, &io_map);
	io_map = (io_map & ~0x1) | (priv->bt_enabled ? 1 : 0);
	grpci2_cfg_w32(priv, TGT, 0, capptr+CAP9_IOMAP_OFS, io_map);

	/* Setup the Host's PCI Target BARs क्रम other peripherals to access,
	 * and करो DMA to the host's memory. The target BARs can be sized and
	 * enabled inभागidually.
	 *
	 * User may set custom target BARs, but शेष is:
	 * The first BARs is used to map kernel low (DMA is part of normal
	 * region on sparc which is SRMMU_MAXMEM big) मुख्य memory 1:1 to the
	 * PCI bus, the other BARs are disabled. We assume that the first BAR
	 * is always available.
	 */
	क्रम (i = 0; i < 6; i++) अणु
		अगर (barcfg[i].pciadr != ~0 && barcfg[i].ahbadr != ~0) अणु
			/* Target BARs must have the proper alignment */
			ahbadr = barcfg[i].ahbadr;
			pciadr = barcfg[i].pciadr;
			bar_sz = ((pciadr - 1) & ~pciadr) + 1;
		पूर्ण अन्यथा अणु
			अगर (i == 0) अणु
				/* Map मुख्य memory */
				bar_sz = 0xf0000008; /* 256MB prefetchable */
				ahbadr = 0xf0000000 & (u32)__pa(PAGE_ALIGN(
					(अचिन्हित दीर्घ) &_end));
				pciadr = ahbadr;
			पूर्ण अन्यथा अणु
				bar_sz = 0;
				ahbadr = 0;
				pciadr = 0;
			पूर्ण
		पूर्ण
		grpci2_cfg_w32(priv, TGT, 0, capptr+CAP9_BARSIZE_OFS+i*4,
				bar_sz);
		grpci2_cfg_w32(priv, TGT, 0, PCI_BASE_ADDRESS_0+i*4, pciadr);
		grpci2_cfg_w32(priv, TGT, 0, capptr+CAP9_BAR_OFS+i*4, ahbadr);
		prपूर्णांकk(KERN_INFO "        TGT BAR[%d]: 0x%08x (PCI)-> 0x%08x\n",
			i, pciadr, ahbadr);
	पूर्ण

	/* set as bus master and enable pci memory responses */
	grpci2_cfg_r32(priv, TGT, 0, PCI_COMMAND, &data);
	data |= (PCI_COMMAND_MEMORY | PCI_COMMAND_MASTER);
	grpci2_cfg_w32(priv, TGT, 0, PCI_COMMAND, data);

	/* Enable Error respone (CPU-TRAP) on illegal memory access. */
	REGSTORE(regs->ctrl, CTRL_ER | CTRL_PE);
पूर्ण

अटल irqवापस_t grpci2_jump_पूर्णांकerrupt(पूर्णांक irq, व्योम *arg)
अणु
	prपूर्णांकk(KERN_ERR "GRPCI2: Jump IRQ happened\n");
	वापस IRQ_NONE;
पूर्ण

/* Handle GRPCI2 Error Interrupt */
अटल irqवापस_t grpci2_err_पूर्णांकerrupt(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा grpci2_priv *priv = arg;
	काष्ठा grpci2_regs __iomem *regs = priv->regs;
	अचिन्हित पूर्णांक status;

	status = REGLOAD(regs->sts_cap);
	अगर ((status & STS_ERR_IRQ) == 0)
		वापस IRQ_NONE;

	अगर (status & STS_IPARERR)
		prपूर्णांकk(KERN_ERR "GRPCI2: Parity Error\n");

	अगर (status & STS_ITGTABRT)
		prपूर्णांकk(KERN_ERR "GRPCI2: Target Abort\n");

	अगर (status & STS_IMSTABRT)
		prपूर्णांकk(KERN_ERR "GRPCI2: Master Abort\n");

	अगर (status & STS_ISYSERR)
		prपूर्णांकk(KERN_ERR "GRPCI2: System Error\n");

	/* Clear handled INT TYPE IRQs */
	REGSTORE(regs->sts_cap, status & STS_ERR_IRQ);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक grpci2_of_probe(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा grpci2_regs __iomem *regs;
	काष्ठा grpci2_priv *priv;
	पूर्णांक err, i, len;
	स्थिर पूर्णांक *पंचांगp;
	अचिन्हित पूर्णांक capability;

	अगर (grpci2priv) अणु
		prपूर्णांकk(KERN_ERR "GRPCI2: only one GRPCI2 core supported\n");
		वापस -ENODEV;
	पूर्ण

	अगर (ofdev->num_resources < 3) अणु
		prपूर्णांकk(KERN_ERR "GRPCI2: not enough APB/AHB resources\n");
		वापस -EIO;
	पूर्ण

	/* Find Device Address */
	regs = of_ioremap(&ofdev->resource[0], 0,
			  resource_size(&ofdev->resource[0]),
			  "grlib-grpci2 regs");
	अगर (regs == शून्य) अणु
		prपूर्णांकk(KERN_ERR "GRPCI2: ioremap failed\n");
		वापस -EIO;
	पूर्ण

	/*
	 * Check that we're in Host Slot and that we can act as a Host Bridge
	 * and not only as target.
	 */
	capability = REGLOAD(regs->sts_cap);
	अगर ((capability & STS_HOST) || !(capability & STS_MST)) अणु
		prपूर्णांकk(KERN_INFO "GRPCI2: not in host system slot\n");
		err = -EIO;
		जाओ err1;
	पूर्ण

	priv = grpci2priv = kzalloc(माप(काष्ठा grpci2_priv), GFP_KERNEL);
	अगर (grpci2priv == शून्य) अणु
		err = -ENOMEM;
		जाओ err1;
	पूर्ण
	priv->regs = regs;
	priv->irq = ofdev->archdata.irqs[0]; /* BASE IRQ */
	priv->irq_mode = (capability & STS_IRQMODE) >> STS_IRQMODE_BIT;

	prपूर्णांकk(KERN_INFO "GRPCI2: host found at %p, irq%d\n", regs, priv->irq);

	/* Byte twisting should be made configurable from kernel command line */
	priv->bt_enabled = 1;

	/* Let user करो custom Target BAR assignment */
	पंचांगp = of_get_property(ofdev->dev.of_node, "barcfg", &len);
	अगर (पंचांगp && (len == 2*4*6))
		स_नकल(priv->tgtbars, पंचांगp, 2*4*6);
	अन्यथा
		स_रखो(priv->tgtbars, -1, 2*4*6);

	/* Limit IRQ unmasking in irq_mode 2 and 3 */
	पंचांगp = of_get_property(ofdev->dev.of_node, "irq_mask", &len);
	अगर (पंचांगp && (len == 4))
		priv->करो_reset = *पंचांगp;
	अन्यथा
		priv->irq_mask = 0xf;

	/* Optional PCI reset. Force PCI reset on startup */
	पंचांगp = of_get_property(ofdev->dev.of_node, "reset", &len);
	अगर (पंचांगp && (len == 4))
		priv->करो_reset = *पंचांगp;
	अन्यथा
		priv->करो_reset = 0;

	/* Find PCI Memory, I/O and Configuration Space Winकरोws */
	priv->pci_area = ofdev->resource[1].start;
	priv->pci_area_end = ofdev->resource[1].end+1;
	priv->pci_io = ofdev->resource[2].start;
	priv->pci_conf = ofdev->resource[2].start + 0x10000;
	priv->pci_conf_end = priv->pci_conf + 0x10000;
	priv->pci_io_va = (अचिन्हित दीर्घ)ioremap(priv->pci_io, 0x10000);
	अगर (!priv->pci_io_va) अणु
		err = -EIO;
		जाओ err2;
	पूर्ण

	prपूर्णांकk(KERN_INFO
		"GRPCI2: MEMORY SPACE [0x%08lx - 0x%08lx]\n"
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
	स_रखो(&priv->info.io_space, 0, माप(काष्ठा resource));
	priv->info.io_space.name = "GRPCI2 PCI I/O Space";
	priv->info.io_space.start = priv->pci_io_va + 0x1000;
	priv->info.io_space.end = priv->pci_io_va + 0x10000 - 1;
	priv->info.io_space.flags = IORESOURCE_IO;

	/*
	 * GRPCI2 has no prefetchable memory, map everything as
	 * non-prefetchable memory
	 */
	स_रखो(&priv->info.mem_space, 0, माप(काष्ठा resource));
	priv->info.mem_space.name = "GRPCI2 PCI MEM Space";
	priv->info.mem_space.start = priv->pci_area;
	priv->info.mem_space.end = priv->pci_area_end - 1;
	priv->info.mem_space.flags = IORESOURCE_MEM;

	अगर (request_resource(&iomem_resource, &priv->info.mem_space) < 0)
		जाओ err3;
	अगर (request_resource(&ioport_resource, &priv->info.io_space) < 0)
		जाओ err4;

	/* setup maximum supported PCI buses */
	priv->info.busn.name = "GRPCI2 busn";
	priv->info.busn.start = 0;
	priv->info.busn.end = 255;

	grpci2_hw_init(priv);

	/*
	 * Get PCI Interrupt to System IRQ mapping and setup IRQ handling
	 * Error IRQ always on PCI INTA.
	 */
	अगर (priv->irq_mode < 2) अणु
		/* All PCI पूर्णांकerrupts are shared using the same प्रणाली IRQ */
		leon_update_virq_handling(priv->irq, grpci2_pci_flow_irq,
					 "pcilvl", 0);

		priv->irq_map[0] = grpci2_build_device_irq(1);
		priv->irq_map[1] = grpci2_build_device_irq(2);
		priv->irq_map[2] = grpci2_build_device_irq(3);
		priv->irq_map[3] = grpci2_build_device_irq(4);

		priv->virq_err = grpci2_build_device_irq(5);
		अगर (priv->irq_mode & 1)
			priv->virq_dma = ofdev->archdata.irqs[1];
		अन्यथा
			priv->virq_dma = grpci2_build_device_irq(6);

		/* Enable IRQs on LEON IRQ controller */
		err = request_irq(priv->irq, grpci2_jump_पूर्णांकerrupt, 0,
					"GRPCI2_JUMP", priv);
		अगर (err)
			prपूर्णांकk(KERN_ERR "GRPCI2: ERR IRQ request failed\n");
	पूर्ण अन्यथा अणु
		/* All PCI पूर्णांकerrupts have an unique IRQ पूर्णांकerrupt */
		क्रम (i = 0; i < 4; i++) अणु
			/* Make LEON IRQ layer handle level IRQ by acking */
			leon_update_virq_handling(ofdev->archdata.irqs[i],
						 handle_fasteoi_irq, "pcilvl",
						 1);
			priv->irq_map[i] = ofdev->archdata.irqs[i];
		पूर्ण
		priv->virq_err = priv->irq_map[0];
		अगर (priv->irq_mode & 1)
			priv->virq_dma = ofdev->archdata.irqs[4];
		अन्यथा
			priv->virq_dma = priv->irq_map[0];

		/* Unmask all PCI पूर्णांकerrupts, request_irq will not करो that */
		REGSTORE(regs->ctrl, REGLOAD(regs->ctrl)|(priv->irq_mask&0xf));
	पूर्ण

	/* Setup IRQ handler क्रम non-configuration space access errors */
	err = request_irq(priv->virq_err, grpci2_err_पूर्णांकerrupt, IRQF_SHARED,
				"GRPCI2_ERR", priv);
	अगर (err) अणु
		prपूर्णांकk(KERN_DEBUG "GRPCI2: ERR VIRQ request failed: %d\n", err);
		जाओ err5;
	पूर्ण

	/*
	 * Enable Error Interrupts. PCI पूर्णांकerrupts are unmasked once request_irq
	 * is called by the PCI Device drivers
	 */
	REGSTORE(regs->ctrl, REGLOAD(regs->ctrl) | CTRL_EI | CTRL_SI);

	/* Init common layer and scan buses */
	priv->info.ops = &grpci2_ops;
	priv->info.map_irq = grpci2_map_irq;
	leon_pci_init(ofdev, &priv->info);

	वापस 0;

err5:
	release_resource(&priv->info.io_space);
err4:
	release_resource(&priv->info.mem_space);
err3:
	err = -ENOMEM;
	iounmap((व्योम __iomem *)priv->pci_io_va);
err2:
	kमुक्त(priv);
err1:
	of_iounmap(&ofdev->resource[0], regs,
		resource_size(&ofdev->resource[0]));
	वापस err;
पूर्ण

अटल स्थिर काष्ठा of_device_id grpci2_of_match[] __initस्थिर = अणु
	अणु
	 .name = "GAISLER_GRPCI2",
	 पूर्ण,
	अणु
	 .name = "01_07c",
	 पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver grpci2_of_driver = अणु
	.driver = अणु
		.name = "grpci2",
		.of_match_table = grpci2_of_match,
	पूर्ण,
	.probe = grpci2_of_probe,
पूर्ण;

अटल पूर्णांक __init grpci2_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&grpci2_of_driver);
पूर्ण

subsys_initcall(grpci2_init);
