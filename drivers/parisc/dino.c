<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
**	DINO manager
**
**	(c) Copyright 1999 Red Hat Software
**	(c) Copyright 1999 SuSE GmbH
**	(c) Copyright 1999,2000 Hewlett-Packard Company
**	(c) Copyright 2000 Grant Grundler
**	(c) Copyright 2006-2019 Helge Deller
**
**
**	This module provides access to Dino PCI bus (config/IOport spaces)
**	and helps manage Dino IRQ lines.
**
**	Dino पूर्णांकerrupt handling is a bit complicated.
**	Dino always ग_लिखोs to the broadcast EIR via irr0 क्रम now.
**	(BIG WARNING: using broadcast EIR is a really bad thing क्रम SMP!)
**	Only one processor पूर्णांकerrupt is used क्रम the 11 IRQ line 
**	inमाला_दो to dino.
**
**	The dअगरferent between Built-in Dino and Card-Mode
**	dino is in chip initialization and pci device initialization.
**
**	Linux drivers can only use Card-Mode Dino अगर pci devices I/O port
**	BARs are configured and used by the driver. Programming MMIO address 
**	requires substantial knowledge of available Host I/O address ranges
**	is currently not supported.  Port/Config accessor functions are the
**	same. "BIOS" dअगरferences are handled within the existing routines.
*/

/*	Changes :
**	2001-06-14 : Clement Moyroud (moyroudc@esiee.fr)
**		- added support क्रम the पूर्णांकegrated RS232. 	
*/

/*
** TODO: create a भव address क्रम each Dino HPA.
**       GSC code might be able to करो this since IODC data tells us
**       how many pages are used. PCI subप्रणाली could (must?) करो this
**       क्रम PCI drivers devices which implement/use MMIO रेजिस्टरs.
*/

#समावेश <linux/delay.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>	/* क्रम काष्ठा irqaction */
#समावेश <linux/spinlock.h>	/* क्रम spinlock_t and prototypes */

#समावेश <यंत्र/pdc.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/hardware.h>

#समावेश "gsc.h"
#समावेश "iommu.h"

#अघोषित DINO_DEBUG

#अगर_घोषित DINO_DEBUG
#घोषणा DBG(x...) prपूर्णांकk(x)
#अन्यथा
#घोषणा DBG(x...)
#पूर्ण_अगर

/*
** Config accessor functions only pass in the 8-bit bus number
** and not the 8-bit "PCI Segment" number. Each Dino will be
** asचिन्हित a PCI bus number based on "when" it's discovered.
**
** The "secondary" bus number is set to this beक्रमe calling
** pci_scan_bus(). If any PPB's are present, the scan will
** discover them and update the "secondary" and "subordinate"
** fields in Dino's pci_bus काष्ठाure.
**
** Changes in the configuration *will* result in a dअगरferent
** bus number क्रम each dino.
*/

#घोषणा is_card_dino(id)	((id)->hw_type == HPHW_A_DMA)
#घोषणा is_cujo(id)		((id)->hversion == 0x682)

#घोषणा DINO_IAR0		0x004
#घोषणा DINO_IODC_ADDR		0x008
#घोषणा DINO_IODC_DATA_0	0x008
#घोषणा DINO_IODC_DATA_1	0x008
#घोषणा DINO_IRR0		0x00C
#घोषणा DINO_IAR1		0x010
#घोषणा DINO_IRR1		0x014
#घोषणा DINO_IMR		0x018
#घोषणा DINO_IPR		0x01C
#घोषणा DINO_TOC_ADDR		0x020
#घोषणा DINO_ICR		0x024
#घोषणा DINO_ILR		0x028
#घोषणा DINO_IO_COMMAND		0x030
#घोषणा DINO_IO_STATUS		0x034
#घोषणा DINO_IO_CONTROL		0x038
#घोषणा DINO_IO_GSC_ERR_RESP	0x040
#घोषणा DINO_IO_ERR_INFO	0x044
#घोषणा DINO_IO_PCI_ERR_RESP	0x048
#घोषणा DINO_IO_FBB_EN		0x05c
#घोषणा DINO_IO_ADDR_EN		0x060
#घोषणा DINO_PCI_ADDR		0x064
#घोषणा DINO_CONFIG_DATA	0x068
#घोषणा DINO_IO_DATA		0x06c
#घोषणा DINO_MEM_DATA		0x070	/* Dino 3.x only */
#घोषणा DINO_GSC2X_CONFIG	0x7b4
#घोषणा DINO_GMASK		0x800
#घोषणा DINO_PAMR		0x804
#घोषणा DINO_PAPR		0x808
#घोषणा DINO_DAMODE		0x80c
#घोषणा DINO_PCICMD		0x810
#घोषणा DINO_PCISTS		0x814
#घोषणा DINO_MLTIM		0x81c
#घोषणा DINO_BRDG_FEAT		0x820
#घोषणा DINO_PCIROR		0x824
#घोषणा DINO_PCIWOR		0x828
#घोषणा DINO_TLTIM		0x830

#घोषणा DINO_IRQS 11		/* bits 0-10 are architected */
#घोषणा DINO_IRR_MASK	0x5ff	/* only 10 bits are implemented */
#घोषणा DINO_LOCAL_IRQS (DINO_IRQS+1)

#घोषणा DINO_MASK_IRQ(x)	(1<<(x))

#घोषणा PCIINTA   0x001
#घोषणा PCIINTB   0x002
#घोषणा PCIINTC   0x004
#घोषणा PCIINTD   0x008
#घोषणा PCIINTE   0x010
#घोषणा PCIINTF   0x020
#घोषणा GSCEXTINT 0x040
/* #घोषणा xxx       0x080 - bit 7 is "default" */
/* #घोषणा xxx    0x100 - bit 8 not used */
/* #घोषणा xxx    0x200 - bit 9 not used */
#घोषणा RS232INT  0x400

काष्ठा dino_device
अणु
	काष्ठा pci_hba_data	hba;	/* 'C' inheritance - must be first */
	spinlock_t		dinosaur_pen;
	अचिन्हित दीर्घ		txn_addr; /* EIR addr to generate पूर्णांकerrupt */ 
	u32			txn_data; /* EIR data assign to each dino */ 
	u32 			imr;	  /* IRQ's which are enabled */ 
	पूर्णांक			global_irq[DINO_LOCAL_IRQS]; /* map IMR bit to global irq */
#अगर_घोषित DINO_DEBUG
	अचिन्हित पूर्णांक		dino_irr0; /* save most recent IRQ line stat */
#पूर्ण_अगर
पूर्ण;

अटल अंतरभूत काष्ठा dino_device *DINO_DEV(काष्ठा pci_hba_data *hba)
अणु
	वापस container_of(hba, काष्ठा dino_device, hba);
पूर्ण

/* Check अगर PCI device is behind a Card-mode Dino. */
अटल पूर्णांक pci_dev_is_behind_card_dino(काष्ठा pci_dev *dev)
अणु
	काष्ठा dino_device *dino_dev;

	dino_dev = DINO_DEV(parisc_walk_tree(dev->bus->bridge));
	वापस is_card_dino(&dino_dev->hba.dev->id);
पूर्ण

/*
 * Dino Configuration Space Accessor Functions
 */

#घोषणा DINO_CFG_TOK(bus,dfn,pos) ((u32) ((bus)<<16 | (dfn)<<8 | (pos)))

/*
 * keep the current highest bus count to assist in allocating busses.  This
 * tries to keep a global bus count total so that when we discover an 
 * entirely new bus, it can be given a unique bus number.
 */
अटल पूर्णांक dino_current_bus = 0;

अटल पूर्णांक dino_cfg_पढ़ो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक where,
		पूर्णांक size, u32 *val)
अणु
	काष्ठा dino_device *d = DINO_DEV(parisc_walk_tree(bus->bridge));
	u32 local_bus = (bus->parent == शून्य) ? 0 : bus->busn_res.start;
	u32 v = DINO_CFG_TOK(local_bus, devfn, where & ~3);
	व्योम __iomem *base_addr = d->hba.base_addr;
	अचिन्हित दीर्घ flags;

	DBG("%s: %p, %d, %d, %d\n", __func__, base_addr, devfn, where,
									size);
	spin_lock_irqsave(&d->dinosaur_pen, flags);

	/* tell HW which CFG address */
	__raw_ग_लिखोl(v, base_addr + DINO_PCI_ADDR);

	/* generate cfg पढ़ो cycle */
	अगर (size == 1) अणु
		*val = पढ़ोb(base_addr + DINO_CONFIG_DATA + (where & 3));
	पूर्ण अन्यथा अगर (size == 2) अणु
		*val = पढ़ोw(base_addr + DINO_CONFIG_DATA + (where & 2));
	पूर्ण अन्यथा अगर (size == 4) अणु
		*val = पढ़ोl(base_addr + DINO_CONFIG_DATA);
	पूर्ण

	spin_unlock_irqrestore(&d->dinosaur_pen, flags);
	वापस 0;
पूर्ण

/*
 * Dino address stepping "feature":
 * When address stepping, Dino attempts to drive the bus one cycle too soon
 * even though the type of cycle (config vs. MMIO) might be dअगरferent. 
 * The पढ़ो of Ven/Prod ID is harmless and aव्योमs Dino's address stepping.
 */
अटल पूर्णांक dino_cfg_ग_लिखो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक where,
	पूर्णांक size, u32 val)
अणु
	काष्ठा dino_device *d = DINO_DEV(parisc_walk_tree(bus->bridge));
	u32 local_bus = (bus->parent == शून्य) ? 0 : bus->busn_res.start;
	u32 v = DINO_CFG_TOK(local_bus, devfn, where & ~3);
	व्योम __iomem *base_addr = d->hba.base_addr;
	अचिन्हित दीर्घ flags;

	DBG("%s: %p, %d, %d, %d\n", __func__, base_addr, devfn, where,
									size);
	spin_lock_irqsave(&d->dinosaur_pen, flags);

	/* aव्योम address stepping feature */
	__raw_ग_लिखोl(v & 0xffffff00, base_addr + DINO_PCI_ADDR);
	__raw_पढ़ोl(base_addr + DINO_CONFIG_DATA);

	/* tell HW which CFG address */
	__raw_ग_लिखोl(v, base_addr + DINO_PCI_ADDR);
	/* generate cfg पढ़ो cycle */
	अगर (size == 1) अणु
		ग_लिखोb(val, base_addr + DINO_CONFIG_DATA + (where & 3));
	पूर्ण अन्यथा अगर (size == 2) अणु
		ग_लिखोw(val, base_addr + DINO_CONFIG_DATA + (where & 2));
	पूर्ण अन्यथा अगर (size == 4) अणु
		ग_लिखोl(val, base_addr + DINO_CONFIG_DATA);
	पूर्ण

	spin_unlock_irqrestore(&d->dinosaur_pen, flags);
	वापस 0;
पूर्ण

अटल काष्ठा pci_ops dino_cfg_ops = अणु
	.पढ़ो =		dino_cfg_पढ़ो,
	.ग_लिखो =	dino_cfg_ग_लिखो,
पूर्ण;


/*
 * Dino "I/O Port" Space Accessor Functions
 *
 * Many PCI devices करोn't require use of I/O port space (eg Tulip,
 * NCR720) since they export the same रेजिस्टरs to both MMIO and
 * I/O port space.  Perक्रमmance is going to stink अगर drivers use
 * I/O port instead of MMIO.
 */

#घोषणा DINO_PORT_IN(type, size, mask) \
अटल u##size dino_in##size (काष्ठा pci_hba_data *d, u16 addr) \
अणु \
	u##size v; \
	अचिन्हित दीर्घ flags; \
	spin_lock_irqsave(&(DINO_DEV(d)->dinosaur_pen), flags); \
	/* tell HW which IO Port address */ \
	__raw_ग_लिखोl((u32) addr, d->base_addr + DINO_PCI_ADDR); \
	/* generate I/O PORT पढ़ो cycle */ \
	v = पढ़ो##type(d->base_addr+DINO_IO_DATA+(addr&mask)); \
	spin_unlock_irqrestore(&(DINO_DEV(d)->dinosaur_pen), flags); \
	वापस v; \
पूर्ण

DINO_PORT_IN(b,  8, 3)
DINO_PORT_IN(w, 16, 2)
DINO_PORT_IN(l, 32, 0)

#घोषणा DINO_PORT_OUT(type, size, mask) \
अटल व्योम dino_out##size (काष्ठा pci_hba_data *d, u16 addr, u##size val) \
अणु \
	अचिन्हित दीर्घ flags; \
	spin_lock_irqsave(&(DINO_DEV(d)->dinosaur_pen), flags); \
	/* tell HW which IO port address */ \
	__raw_ग_लिखोl((u32) addr, d->base_addr + DINO_PCI_ADDR); \
	/* generate cfg ग_लिखो cycle */ \
	ग_लिखो##type(val, d->base_addr+DINO_IO_DATA+(addr&mask)); \
	spin_unlock_irqrestore(&(DINO_DEV(d)->dinosaur_pen), flags); \
पूर्ण

DINO_PORT_OUT(b,  8, 3)
DINO_PORT_OUT(w, 16, 2)
DINO_PORT_OUT(l, 32, 0)

अटल काष्ठा pci_port_ops dino_port_ops = अणु
	.inb	= dino_in8,
	.inw	= dino_in16,
	.inl	= dino_in32,
	.outb	= dino_out8,
	.outw	= dino_out16,
	.outl	= dino_out32
पूर्ण;

अटल व्योम dino_mask_irq(काष्ठा irq_data *d)
अणु
	काष्ठा dino_device *dino_dev = irq_data_get_irq_chip_data(d);
	पूर्णांक local_irq = gsc_find_local_irq(d->irq, dino_dev->global_irq, DINO_LOCAL_IRQS);

	DBG(KERN_WARNING "%s(0x%px, %d)\n", __func__, dino_dev, d->irq);

	/* Clear the matching bit in the IMR रेजिस्टर */
	dino_dev->imr &= ~(DINO_MASK_IRQ(local_irq));
	__raw_ग_लिखोl(dino_dev->imr, dino_dev->hba.base_addr+DINO_IMR);
पूर्ण

अटल व्योम dino_unmask_irq(काष्ठा irq_data *d)
अणु
	काष्ठा dino_device *dino_dev = irq_data_get_irq_chip_data(d);
	पूर्णांक local_irq = gsc_find_local_irq(d->irq, dino_dev->global_irq, DINO_LOCAL_IRQS);
	u32 पंचांगp;

	DBG(KERN_WARNING "%s(0x%px, %d)\n", __func__, dino_dev, d->irq);

	/*
	** clear pending IRQ bits
	**
	** This करोes NOT change ILR state!
	** See comment below क्रम ILR usage.
	*/
	__raw_पढ़ोl(dino_dev->hba.base_addr+DINO_IPR);

	/* set the matching bit in the IMR रेजिस्टर */
	dino_dev->imr |= DINO_MASK_IRQ(local_irq);	/* used in dino_isr() */
	__raw_ग_लिखोl( dino_dev->imr, dino_dev->hba.base_addr+DINO_IMR);

	/* Emulate "Level Triggered" Interrupt
	** Basically, a driver is blowing it अगर the IRQ line is निश्चितed
	** जबतक the IRQ is disabled.  But tulip.c seems to करो that....
	** Give 'em a kluge award and a nice round of applause!
	**
	** The gsc_ग_लिखो will generate an पूर्णांकerrupt which invokes dino_isr().
	** dino_isr() will पढ़ो IPR and find nothing. But then catch this
	** when it also checks ILR.
	*/
	पंचांगp = __raw_पढ़ोl(dino_dev->hba.base_addr+DINO_ILR);
	अगर (पंचांगp & DINO_MASK_IRQ(local_irq)) अणु
		DBG(KERN_WARNING "%s(): IRQ asserted! (ILR 0x%x)\n",
				__func__, पंचांगp);
		gsc_ग_लिखोl(dino_dev->txn_data, dino_dev->txn_addr);
	पूर्ण
पूर्ण

अटल काष्ठा irq_chip dino_पूर्णांकerrupt_type = अणु
	.name		= "GSC-PCI",
	.irq_unmask	= dino_unmask_irq,
	.irq_mask	= dino_mask_irq,
पूर्ण;


/*
 * Handle a Processor पूर्णांकerrupt generated by Dino.
 *
 * ilr_loop counter is a kluge to prevent a "stuck" IRQ line from
 * wedging the CPU. Could be हटाओd or made optional at some poपूर्णांक.
 */
अटल irqवापस_t dino_isr(पूर्णांक irq, व्योम *पूर्णांकr_dev)
अणु
	काष्ठा dino_device *dino_dev = पूर्णांकr_dev;
	u32 mask;
	पूर्णांक ilr_loop = 100;

	/* पढ़ो and acknowledge pending पूर्णांकerrupts */
#अगर_घोषित DINO_DEBUG
	dino_dev->dino_irr0 =
#पूर्ण_अगर
	mask = __raw_पढ़ोl(dino_dev->hba.base_addr+DINO_IRR0) & DINO_IRR_MASK;

	अगर (mask == 0)
		वापस IRQ_NONE;

ilr_again:
	करो अणु
		पूर्णांक local_irq = __ffs(mask);
		पूर्णांक irq = dino_dev->global_irq[local_irq];
		DBG(KERN_DEBUG "%s(%d, %p) mask 0x%x\n",
			__func__, irq, पूर्णांकr_dev, mask);
		generic_handle_irq(irq);
		mask &= ~DINO_MASK_IRQ(local_irq);
	पूर्ण जबतक (mask);

	/* Support क्रम level triggered IRQ lines.
	** 
	** Dropping this support would make this routine *much* faster.
	** But since PCI requires level triggered IRQ line to share lines...
	** device drivers may assume lines are level triggered (and not
	** edge triggered like EISA/ISA can be).
	*/
	mask = __raw_पढ़ोl(dino_dev->hba.base_addr+DINO_ILR) & dino_dev->imr;
	अगर (mask) अणु
		अगर (--ilr_loop > 0)
			जाओ ilr_again;
		pr_warn_ratelimited("Dino 0x%px: stuck interrupt %d\n",
		       dino_dev->hba.base_addr, mask);
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम dino_assign_irq(काष्ठा dino_device *dino, पूर्णांक local_irq, पूर्णांक *irqp)
अणु
	पूर्णांक irq = gsc_assign_irq(&dino_पूर्णांकerrupt_type, dino);
	अगर (irq == NO_IRQ)
		वापस;

	*irqp = irq;
	dino->global_irq[local_irq] = irq;
पूर्ण

अटल व्योम dino_choose_irq(काष्ठा parisc_device *dev, व्योम *ctrl)
अणु
	पूर्णांक irq;
	काष्ठा dino_device *dino = ctrl;

	चयन (dev->id.sversion) अणु
		हाल 0x00084:	irq =  8; अवरोध; /* PS/2 */
		हाल 0x0008c:	irq = 10; अवरोध; /* RS232 */
		हाल 0x00096:	irq =  8; अवरोध; /* PS/2 */
		शेष:	वापस;		 /* Unknown */
	पूर्ण

	dino_assign_irq(dino, irq, &dev->irq);
पूर्ण


/*
 * Cirrus 6832 Cardbus reports wrong irq on RDI Tadpole PARISC Laptop (deller@gmx.de)
 * (the irqs are off-by-one, not sure yet अगर this is a cirrus, dino-hardware or dino-driver problem...)
 */
अटल व्योम quirk_cirrus_cardbus(काष्ठा pci_dev *dev)
अणु
	u8 new_irq = dev->irq - 1;
	prपूर्णांकk(KERN_INFO "PCI: Cirrus Cardbus IRQ fixup for %s, from %d to %d\n",
			pci_name(dev), dev->irq, new_irq);
	dev->irq = new_irq;
पूर्ण
DECLARE_PCI_FIXUP_ENABLE(PCI_VENDOR_ID_CIRRUS, PCI_DEVICE_ID_CIRRUS_6832, quirk_cirrus_cardbus );

#अगर_घोषित CONFIG_TULIP
अटल व्योम pci_fixup_tulip(काष्ठा pci_dev *dev)
अणु
	अगर (!pci_dev_is_behind_card_dino(dev))
		वापस;
	अगर (!(pci_resource_flags(dev, 1) & IORESOURCE_MEM))
		वापस;
	pr_warn("%s: HP HSC-PCI Cards with card-mode Dino not yet supported.\n",
		pci_name(dev));
	/* Disable this card by zeroing the PCI resources */
	स_रखो(&dev->resource[0], 0, माप(dev->resource[0]));
	स_रखो(&dev->resource[1], 0, माप(dev->resource[1]));
पूर्ण
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_DEC, PCI_ANY_ID, pci_fixup_tulip);
#पूर्ण_अगर /* CONFIG_TULIP */

अटल व्योम __init
dino_bios_init(व्योम)
अणु
	DBG("dino_bios_init\n");
पूर्ण

/*
 * dino_card_setup - Set up the memory space क्रम a Dino in card mode.
 * @bus: the bus under this dino
 *
 * Claim an 8MB chunk of unused IO space and call the generic PCI routines
 * to set up the addresses of the devices on this bus.
 */
#घोषणा _8MB 0x00800000UL
अटल व्योम __init
dino_card_setup(काष्ठा pci_bus *bus, व्योम __iomem *base_addr)
अणु
	पूर्णांक i;
	काष्ठा dino_device *dino_dev = DINO_DEV(parisc_walk_tree(bus->bridge));
	काष्ठा resource *res;
	अक्षर name[128];
	पूर्णांक size;

	res = &dino_dev->hba.lmmio_space;
	res->flags = IORESOURCE_MEM;
	size = scnम_लिखो(name, माप(name), "Dino LMMIO (%s)", 
			 dev_name(bus->bridge));
	res->name = kदो_स्मृति(size+1, GFP_KERNEL);
	अगर(res->name)
		म_नकल((अक्षर *)res->name, name);
	अन्यथा
		res->name = dino_dev->hba.lmmio_space.name;
	

	अगर (ccio_allocate_resource(dino_dev->hba.dev, res, _8MB,
				F_EXTEND(0xf0000000UL) | _8MB,
				F_EXTEND(0xffffffffUL) &~ _8MB, _8MB) < 0) अणु
		काष्ठा pci_dev *dev, *पंचांगp;

		prपूर्णांकk(KERN_ERR "Dino: cannot attach bus %s\n",
		       dev_name(bus->bridge));
		/* समाप्त the bus, we can't करो anything with it */
		list_क्रम_each_entry_safe(dev, पंचांगp, &bus->devices, bus_list) अणु
			list_del(&dev->bus_list);
		पूर्ण
			
		वापस;
	पूर्ण
	bus->resource[1] = res;
	bus->resource[0] = &(dino_dev->hba.io_space);

	/* Now tell dino what range it has */
	क्रम (i = 1; i < 31; i++) अणु
		अगर (res->start == F_EXTEND(0xf0000000UL | (i * _8MB)))
			अवरोध;
	पूर्ण
	DBG("DINO GSC WRITE i=%d, start=%lx, dino addr = %p\n",
	    i, res->start, base_addr + DINO_IO_ADDR_EN);
	__raw_ग_लिखोl(1 << i, base_addr + DINO_IO_ADDR_EN);
पूर्ण

अटल व्योम __init
dino_card_fixup(काष्ठा pci_dev *dev)
अणु
	u32 irq_pin;

	/*
	** REVISIT: card-mode PCI-PCI expansion chassis करो exist.
	**         Not sure they were ever productized.
	**         Die here since we'll die later in dino_inb() anyway.
	*/
	अगर ((dev->class >> 8) == PCI_CLASS_BRIDGE_PCI) अणु
		panic("Card-Mode Dino: PCI-PCI Bridge not supported\n");
	पूर्ण

	/*
	** Set Latency Timer to 0xff (not a shared bus)
	** Set CACHELINE_SIZE.
	*/
	dino_cfg_ग_लिखो(dev->bus, dev->devfn, 
		       PCI_CACHE_LINE_SIZE, 2, 0xff00 | L1_CACHE_BYTES/4); 

	/*
	** Program INT_LINE क्रम card-mode devices.
	** The cards are hardwired according to this algorithm.
	** And it करोesn't matter if PPB's are present or not since
	** the IRQ lines bypass the PPB.
	**
	** "-1" converts INTA-D (1-4) to PCIINTA-D (0-3) range.
	** The additional "-1" adjusts क्रम skewing the IRQ<->slot.
	*/
	dino_cfg_पढ़ो(dev->bus, dev->devfn, PCI_INTERRUPT_PIN, 1, &irq_pin); 
	dev->irq = pci_swizzle_पूर्णांकerrupt_pin(dev, irq_pin) - 1;

	/* Shouldn't really need to do this but it's in हाल someone tries
	** to bypass PCI services and look at the card themselves.
	*/
	dino_cfg_ग_लिखो(dev->bus, dev->devfn, PCI_INTERRUPT_LINE, 1, dev->irq); 
पूर्ण

/* The alignment contraपूर्णांकs क्रम PCI bridges under dino */
#घोषणा DINO_BRIDGE_ALIGN 0x100000


अटल व्योम __init
dino_fixup_bus(काष्ठा pci_bus *bus)
अणु
        काष्ठा pci_dev *dev;
        काष्ठा dino_device *dino_dev = DINO_DEV(parisc_walk_tree(bus->bridge));

	DBG(KERN_WARNING "%s(0x%px) bus %d platform_data 0x%px\n",
	    __func__, bus, bus->busn_res.start,
	    bus->bridge->platक्रमm_data);

	/* Firmware करोesn't set up card-mode dino, so we have to */
	अगर (is_card_dino(&dino_dev->hba.dev->id)) अणु
		dino_card_setup(bus, dino_dev->hba.base_addr);
	पूर्ण अन्यथा अगर (bus->parent) अणु
		पूर्णांक i;

		pci_पढ़ो_bridge_bases(bus);


		क्रम(i = PCI_BRIDGE_RESOURCES; i < PCI_NUM_RESOURCES; i++) अणु
			अगर((bus->self->resource[i].flags & 
			    (IORESOURCE_IO | IORESOURCE_MEM)) == 0)
				जारी;
			
			अगर(bus->self->resource[i].flags & IORESOURCE_MEM) अणु
				/* There's a quirk to alignment of
				 * bridge memory resources: the start
				 * is the alignment and start-end is
				 * the size.  However, firmware will
				 * have asचिन्हित start and end, so we
				 * need to take this पूर्णांकo account */
				bus->self->resource[i].end = bus->self->resource[i].end - bus->self->resource[i].start + DINO_BRIDGE_ALIGN;
				bus->self->resource[i].start = DINO_BRIDGE_ALIGN;
				
			पूर्ण
					
			DBG("DEBUG %s assigning %d [%pR]\n",
			    dev_name(&bus->self->dev), i,
			    &bus->self->resource[i]);
			WARN_ON(pci_assign_resource(bus->self, i));
			DBG("DEBUG %s after assign %d [%pR]\n",
			    dev_name(&bus->self->dev), i,
			    &bus->self->resource[i]);
		पूर्ण
	पूर्ण


	list_क्रम_each_entry(dev, &bus->devices, bus_list) अणु
		अगर (is_card_dino(&dino_dev->hba.dev->id))
			dino_card_fixup(dev);

		/*
		** P2PB's only have 2 BARs, no IRQs.
		** I'd like to just ignore them क्रम now.
		*/
		अगर ((dev->class >> 8) == PCI_CLASS_BRIDGE_PCI)  अणु
			pcibios_init_bridge(dev);
			जारी;
		पूर्ण

		/* null out the ROM resource अगर there is one (we करोn't
		 * care about an expansion rom on parisc, since it
		 * usually contains (x86) bios code) */
		dev->resource[PCI_ROM_RESOURCE].flags = 0;
				
		अगर(dev->irq == 255) अणु

#घोषणा DINO_FIX_UNASSIGNED_INTERRUPTS
#अगर_घोषित DINO_FIX_UNASSIGNED_INTERRUPTS

			/* This code tries to assign an unasचिन्हित
			 * पूर्णांकerrupt.  Leave it disabled unless you
			 * *really* know what you're करोing since the
			 * pin<->पूर्णांकerrupt line mapping varies by bus
			 * and machine */

			u32 irq_pin;
			
			dino_cfg_पढ़ो(dev->bus, dev->devfn, 
				      PCI_INTERRUPT_PIN, 1, &irq_pin);
			irq_pin = pci_swizzle_पूर्णांकerrupt_pin(dev, irq_pin) - 1;
			prपूर्णांकk(KERN_WARNING "Device %s has undefined IRQ, "
					"setting to %d\n", pci_name(dev), irq_pin);
			dino_cfg_ग_लिखो(dev->bus, dev->devfn, 
				       PCI_INTERRUPT_LINE, 1, irq_pin);
			dino_assign_irq(dino_dev, irq_pin, &dev->irq);
#अन्यथा
			dev->irq = 65535;
			prपूर्णांकk(KERN_WARNING "Device %s has unassigned IRQ\n", pci_name(dev));
#पूर्ण_अगर
		पूर्ण अन्यथा अणु
			/* Adjust INT_LINE क्रम that busses region */
			dino_assign_irq(dino_dev, dev->irq, &dev->irq);
		पूर्ण
	पूर्ण
पूर्ण


अटल काष्ठा pci_bios_ops dino_bios_ops = अणु
	.init		= dino_bios_init,
	.fixup_bus	= dino_fixup_bus
पूर्ण;


/*
 *	Initialise a DINO controller chip
 */
अटल व्योम __init
dino_card_init(काष्ठा dino_device *dino_dev)
अणु
	u32 brdg_feat = 0x00784e05;
	अचिन्हित दीर्घ status;

	status = __raw_पढ़ोl(dino_dev->hba.base_addr+DINO_IO_STATUS);
	अगर (status & 0x0000ff80) अणु
		__raw_ग_लिखोl(0x00000005,
				dino_dev->hba.base_addr+DINO_IO_COMMAND);
		udelay(1);
	पूर्ण

	__raw_ग_लिखोl(0x00000000, dino_dev->hba.base_addr+DINO_GMASK);
	__raw_ग_लिखोl(0x00000001, dino_dev->hba.base_addr+DINO_IO_FBB_EN);
	__raw_ग_लिखोl(0x00000000, dino_dev->hba.base_addr+DINO_ICR);

#अगर 1
/* REVISIT - should be a runसमय check (eg अगर (CPU_IS_PCX_L) ...) */
	/*
	** PCX-L processors करोn't support XQL like Dino wants it.
	** PCX-L2 ignore XQL संकेत and it करोesn't matter.
	*/
	brdg_feat &= ~0x4;	/* UXQL */
#पूर्ण_अगर
	__raw_ग_लिखोl( brdg_feat, dino_dev->hba.base_addr+DINO_BRDG_FEAT);

	/*
	** Don't enable address decoding until we know which I/O range
	** currently is available from the host. Only affects MMIO
	** and not I/O port space.
	*/
	__raw_ग_लिखोl(0x00000000, dino_dev->hba.base_addr+DINO_IO_ADDR_EN);

	__raw_ग_लिखोl(0x00000000, dino_dev->hba.base_addr+DINO_DAMODE);
	__raw_ग_लिखोl(0x00222222, dino_dev->hba.base_addr+DINO_PCIROR);
	__raw_ग_लिखोl(0x00222222, dino_dev->hba.base_addr+DINO_PCIWOR);

	__raw_ग_लिखोl(0x00000040, dino_dev->hba.base_addr+DINO_MLTIM);
	__raw_ग_लिखोl(0x00000080, dino_dev->hba.base_addr+DINO_IO_CONTROL);
	__raw_ग_लिखोl(0x0000008c, dino_dev->hba.base_addr+DINO_TLTIM);

	/* Disable PAMR beक्रमe writing PAPR */
	__raw_ग_लिखोl(0x0000007e, dino_dev->hba.base_addr+DINO_PAMR);
	__raw_ग_लिखोl(0x0000007f, dino_dev->hba.base_addr+DINO_PAPR);
	__raw_ग_लिखोl(0x00000000, dino_dev->hba.base_addr+DINO_PAMR);

	/*
	** Dino ERS encourages enabling FBB (0x6f).
	** We can't until we know *all* devices below us can support it.
	** (Something in device configuration header tells us).
	*/
	__raw_ग_लिखोl(0x0000004f, dino_dev->hba.base_addr+DINO_PCICMD);

	/* Somewhere, the PCI spec says give devices 1 second
	** to recover from the #RESET being de-निश्चितed.
	** Experience shows most devices only need 10ms.
	** This लघु-cut speeds up booting signअगरicantly.
	*/
	mdelay(pci_post_reset_delay);
पूर्ण

अटल पूर्णांक __init
dino_bridge_init(काष्ठा dino_device *dino_dev, स्थिर अक्षर *name)
अणु
	अचिन्हित दीर्घ io_addr;
	पूर्णांक result, i, count=0;
	काष्ठा resource *res, *prevres = शून्य;
	/*
	 * Decoding IO_ADDR_EN only works क्रम Built-in Dino
	 * since PDC has alपढ़ोy initialized this.
	 */

	io_addr = __raw_पढ़ोl(dino_dev->hba.base_addr + DINO_IO_ADDR_EN);
	अगर (io_addr == 0) अणु
		prपूर्णांकk(KERN_WARNING "%s: No PCI devices enabled.\n", name);
		वापस -ENODEV;
	पूर्ण

	res = &dino_dev->hba.lmmio_space;
	क्रम (i = 0; i < 32; i++) अणु
		अचिन्हित दीर्घ start, end;

		अगर((io_addr & (1 << i)) == 0)
			जारी;

		start = F_EXTEND(0xf0000000UL) | (i << 23);
		end = start + 8 * 1024 * 1024 - 1;

		DBG("DINO RANGE %d is at 0x%lx-0x%lx\n", count,
		    start, end);

		अगर(prevres && prevres->end + 1 == start) अणु
			prevres->end = end;
		पूर्ण अन्यथा अणु
			अगर(count >= DINO_MAX_LMMIO_RESOURCES) अणु
				prपूर्णांकk(KERN_ERR "%s is out of resource windows for range %d (0x%lx-0x%lx)\n", name, count, start, end);
				अवरोध;
			पूर्ण
			prevres = res;
			res->start = start;
			res->end = end;
			res->flags = IORESOURCE_MEM;
			res->name = kदो_स्मृति(64, GFP_KERNEL);
			अगर(res->name)
				snम_लिखो((अक्षर *)res->name, 64, "%s LMMIO %d",
					 name, count);
			res++;
			count++;
		पूर्ण
	पूर्ण

	res = &dino_dev->hba.lmmio_space;

	क्रम(i = 0; i < DINO_MAX_LMMIO_RESOURCES; i++) अणु
		अगर(res[i].flags == 0)
			अवरोध;

		result = ccio_request_resource(dino_dev->hba.dev, &res[i]);
		अगर (result < 0) अणु
			prपूर्णांकk(KERN_ERR "%s: failed to claim PCI Bus address "
			       "space %d (%pR)!\n", name, i, &res[i]);
			वापस result;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __init dino_common_init(काष्ठा parisc_device *dev,
		काष्ठा dino_device *dino_dev, स्थिर अक्षर *name)
अणु
	पूर्णांक status;
	u32 eim;
	काष्ठा gsc_irq gsc_irq;
	काष्ठा resource *res;

	pcibios_रेजिस्टर_hba(&dino_dev->hba);

	pci_bios = &dino_bios_ops;   /* used by pci_scan_bus() */
	pci_port = &dino_port_ops;

	/*
	** Note: SMP प्रणालीs can make use of IRR1/IAR1 रेजिस्टरs
	**   But it won't buy much perक्रमmance except in very
	**   specअगरic applications/configurations. Note Dino
	**   still only has 11 IRQ input lines - just map some of them
	**   to a dअगरferent processor.
	*/
	dev->irq = gsc_alloc_irq(&gsc_irq);
	dino_dev->txn_addr = gsc_irq.txn_addr;
	dino_dev->txn_data = gsc_irq.txn_data;
	eim = ((u32) gsc_irq.txn_addr) | gsc_irq.txn_data;

	/* 
	** Dino needs a PA "IRQ" to get a processor's attention.
	** arch/parisc/kernel/irq.c वापसs an EIRR bit.
	*/
	अगर (dev->irq < 0) अणु
		prपूर्णांकk(KERN_WARNING "%s: gsc_alloc_irq() failed\n", name);
		वापस 1;
	पूर्ण

	status = request_irq(dev->irq, dino_isr, 0, name, dino_dev);
	अगर (status) अणु
		prपूर्णांकk(KERN_WARNING "%s: request_irq() failed with %d\n", 
			name, status);
		वापस 1;
	पूर्ण

	/* Support the serial port which is someबार attached on built-in
	 * Dino / Cujo chips.
	 */

	gsc_fixup_irqs(dev, dino_dev, dino_choose_irq);

	/*
	** This enables DINO to generate पूर्णांकerrupts when it sees
	** any of its inमाला_दो *change*. Just निश्चितing an IRQ
	** beक्रमe it's enabled (ie unmasked) isn't good enough.
	*/
	__raw_ग_लिखोl(eim, dino_dev->hba.base_addr+DINO_IAR0);

	/*
	** Some platक्रमms करोn't clear Dino's IRR0 रेजिस्टर at boot समय.
	** Reading will clear it now.
	*/
	__raw_पढ़ोl(dino_dev->hba.base_addr+DINO_IRR0);

	/* allocate I/O Port resource region */
	res = &dino_dev->hba.io_space;
	अगर (!is_cujo(&dev->id)) अणु
		res->name = "Dino I/O Port";
	पूर्ण अन्यथा अणु
		res->name = "Cujo I/O Port";
	पूर्ण
	res->start = HBA_PORT_BASE(dino_dev->hba.hba_num);
	res->end = res->start + (HBA_PORT_SPACE_SIZE - 1);
	res->flags = IORESOURCE_IO; /* करो not mark it busy ! */
	अगर (request_resource(&ioport_resource, res) < 0) अणु
		prपूर्णांकk(KERN_ERR "%s: request I/O Port region failed "
		       "0x%lx/%lx (hpa 0x%px)\n",
		       name, (अचिन्हित दीर्घ)res->start, (अचिन्हित दीर्घ)res->end,
		       dino_dev->hba.base_addr);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा CUJO_RAVEN_ADDR		F_EXTEND(0xf1000000UL)
#घोषणा CUJO_FIREHAWK_ADDR	F_EXTEND(0xf1604000UL)
#घोषणा CUJO_RAVEN_BADPAGE	0x01003000UL
#घोषणा CUJO_FIREHAWK_BADPAGE	0x01607000UL

अटल स्थिर अक्षर dino_vers[][4] = अणु
	"2.0",
	"2.1",
	"3.0",
	"3.1"
पूर्ण;

अटल स्थिर अक्षर cujo_vers[][4] = अणु
	"1.0",
	"2.0"
पूर्ण;

व्योम ccio_cujo20_fixup(काष्ठा parisc_device *dev, u32 iovp);

/*
** Determine अगर dino should claim this chip (वापस 0) or not (वापस 1).
** If so, initialize the chip appropriately (card-mode vs bridge mode).
** Much of the initialization is common though.
*/
अटल पूर्णांक __init dino_probe(काष्ठा parisc_device *dev)
अणु
	काष्ठा dino_device *dino_dev;	// Dino specअगरic control काष्ठा
	स्थिर अक्षर *version = "unknown";
	अक्षर *name;
	पूर्णांक is_cujo = 0;
	LIST_HEAD(resources);
	काष्ठा pci_bus *bus;
	अचिन्हित दीर्घ hpa = dev->hpa.start;
	पूर्णांक max;

	name = "Dino";
	अगर (is_card_dino(&dev->id)) अणु
		version = "3.x (card mode)";
	पूर्ण अन्यथा अणु
		अगर (!is_cujo(&dev->id)) अणु
			अगर (dev->id.hversion_rev < 4) अणु
				version = dino_vers[dev->id.hversion_rev];
			पूर्ण
		पूर्ण अन्यथा अणु
			name = "Cujo";
			is_cujo = 1;
			अगर (dev->id.hversion_rev < 2) अणु
				version = cujo_vers[dev->id.hversion_rev];
			पूर्ण
		पूर्ण
	पूर्ण

	prपूर्णांकk("%s version %s found at 0x%lx\n", name, version, hpa);

	अगर (!request_mem_region(hpa, PAGE_SIZE, name)) अणु
		prपूर्णांकk(KERN_ERR "DINO: Hey! Someone took my MMIO space (0x%lx)!\n",
			hpa);
		वापस 1;
	पूर्ण

	/* Check क्रम bugs */
	अगर (is_cujo && dev->id.hversion_rev == 1) अणु
#अगर_घोषित CONFIG_IOMMU_CCIO
		prपूर्णांकk(KERN_WARNING "Enabling Cujo 2.0 bug workaround\n");
		अगर (hpa == (अचिन्हित दीर्घ)CUJO_RAVEN_ADDR) अणु
			ccio_cujo20_fixup(dev, CUJO_RAVEN_BADPAGE);
		पूर्ण अन्यथा अगर (hpa == (अचिन्हित दीर्घ)CUJO_FIREHAWK_ADDR) अणु
			ccio_cujo20_fixup(dev, CUJO_FIREHAWK_BADPAGE);
		पूर्ण अन्यथा अणु
			prपूर्णांकk("Don't recognise Cujo at address 0x%lx, not enabling workaround\n", hpa);
		पूर्ण
#पूर्ण_अगर
	पूर्ण अन्यथा अगर (!is_cujo && !is_card_dino(&dev->id) &&
			dev->id.hversion_rev < 3) अणु
		prपूर्णांकk(KERN_WARNING
"The GSCtoPCI (Dino hrev %d) bus converter found may exhibit\n"
"data corruption.  See Service Note Numbers: A4190A-01, A4191A-01.\n"
"Systems shipped after Aug 20, 1997 will not exhibit this problem.\n"
"Models affected: C180, C160, C160L, B160L, and B132L workstations.\n\n",
			dev->id.hversion_rev);
/* REVISIT: why are C200/C240 listed in the README table but not
**   "Models affected"? Could be an omission in the original literature.
*/
	पूर्ण

	dino_dev = kzalloc(माप(काष्ठा dino_device), GFP_KERNEL);
	अगर (!dino_dev) अणु
		prपूर्णांकk("dino_init_chip - couldn't alloc dino_device\n");
		वापस 1;
	पूर्ण

	dino_dev->hba.dev = dev;
	dino_dev->hba.base_addr = ioremap(hpa, 4096);
	dino_dev->hba.lmmio_space_offset = PCI_F_EXTEND;
	spin_lock_init(&dino_dev->dinosaur_pen);
	dino_dev->hba.iommu = ccio_get_iommu(dev);

	अगर (is_card_dino(&dev->id)) अणु
		dino_card_init(dino_dev);
	पूर्ण अन्यथा अणु
		dino_bridge_init(dino_dev, name);
	पूर्ण

	अगर (dino_common_init(dev, dino_dev, name))
		वापस 1;

	dev->dev.platक्रमm_data = dino_dev;

	pci_add_resource_offset(&resources, &dino_dev->hba.io_space,
				HBA_PORT_BASE(dino_dev->hba.hba_num));
	अगर (dino_dev->hba.lmmio_space.flags)
		pci_add_resource_offset(&resources, &dino_dev->hba.lmmio_space,
					dino_dev->hba.lmmio_space_offset);
	अगर (dino_dev->hba.elmmio_space.flags)
		pci_add_resource_offset(&resources, &dino_dev->hba.elmmio_space,
					dino_dev->hba.lmmio_space_offset);
	अगर (dino_dev->hba.gmmio_space.flags)
		pci_add_resource(&resources, &dino_dev->hba.gmmio_space);

	dino_dev->hba.bus_num.start = dino_current_bus;
	dino_dev->hba.bus_num.end = 255;
	dino_dev->hba.bus_num.flags = IORESOURCE_BUS;
	pci_add_resource(&resources, &dino_dev->hba.bus_num);
	/*
	** It's not used to aव्योम chicken/egg problems
	** with configuration accessor functions.
	*/
	dino_dev->hba.hba_bus = bus = pci_create_root_bus(&dev->dev,
			 dino_current_bus, &dino_cfg_ops, शून्य, &resources);
	अगर (!bus) अणु
		prपूर्णांकk(KERN_ERR "ERROR: failed to scan PCI bus on %s (duplicate bus number %d?)\n",
		       dev_name(&dev->dev), dino_current_bus);
		pci_मुक्त_resource_list(&resources);
		/* increment the bus number in हाल of duplicates */
		dino_current_bus++;
		वापस 0;
	पूर्ण

	max = pci_scan_child_bus(bus);
	pci_bus_update_busn_res_end(bus, max);

	/* This code *depends* on scanning being single thपढ़ोed
	 * अगर it isn't, this global bus number count will fail
	 */
	dino_current_bus = max + 1;
	pci_bus_assign_resources(bus);
	pci_bus_add_devices(bus);
	वापस 0;
पूर्ण

/*
 * Normally, we would just test sversion.  But the Elroy PCI adapter has
 * the same sversion as Dino, so we have to check hversion as well.
 * Unक्रमtunately, the J2240 PDC reports the wrong hversion क्रम the first
 * Dino, so we have to test क्रम Dino, Cujo and Dino-in-a-J2240.
 * For card-mode Dino, most machines report an sversion of 9D.  But 715
 * and 725 firmware misreport it as 0x08080 क्रम no adequately explained
 * reason.
 */
अटल स्थिर काष्ठा parisc_device_id dino_tbl[] __initस्थिर = अणु
	अणु HPHW_A_DMA, HVERSION_REV_ANY_ID, 0x004, 0x0009D पूर्ण,/* Card-mode Dino */
	अणु HPHW_A_DMA, HVERSION_REV_ANY_ID, HVERSION_ANY_ID, 0x08080 पूर्ण, /* XXX */
	अणु HPHW_BRIDGE, HVERSION_REV_ANY_ID, 0x680, 0xa पूर्ण, /* Bridge-mode Dino */
	अणु HPHW_BRIDGE, HVERSION_REV_ANY_ID, 0x682, 0xa पूर्ण, /* Bridge-mode Cujo */
	अणु HPHW_BRIDGE, HVERSION_REV_ANY_ID, 0x05d, 0xa पूर्ण, /* Dino in a J2240 */
	अणु 0, पूर्ण
पूर्ण;

अटल काष्ठा parisc_driver dino_driver __refdata = अणु
	.name =		"dino",
	.id_table =	dino_tbl,
	.probe =	dino_probe,
पूर्ण;

/*
 * One समय initialization to let the world know Dino is here.
 * This is the only routine which is NOT अटल.
 * Must be called exactly once beक्रमe pci_init().
 */
पूर्णांक __init dino_init(व्योम)
अणु
	रेजिस्टर_parisc_driver(&dino_driver);
	वापस 0;
पूर्ण

