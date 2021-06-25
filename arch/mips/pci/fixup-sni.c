<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * SNI specअगरic PCI support क्रम RM200/RM300.
 *
 * Copyright (C) 1997 - 2000, 2003, 04 Ralf Baechle (ralf@linux-mips.org)
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>

#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/sni.h>

#समावेश <irq.h>

/*
 * PCIMT Shortcuts ...
 */
#घोषणा SCSI	PCIMT_IRQ_SCSI
#घोषणा ETH	PCIMT_IRQ_ETHERNET
#घोषणा INTA	PCIMT_IRQ_INTA
#घोषणा INTB	PCIMT_IRQ_INTB
#घोषणा INTC	PCIMT_IRQ_INTC
#घोषणा INTD	PCIMT_IRQ_INTD

/*
 * Device 0: PCI EISA Bridge	(directly routed)
 * Device 1: NCR53c810 SCSI	(directly routed)
 * Device 2: PCnet32 Ethernet	(directly routed)
 * Device 3: VGA		(routed to INTB)
 * Device 4: Unused
 * Device 5: Slot 2
 * Device 6: Slot 3
 * Device 7: Slot 4
 *
 * Documentation says the VGA is device 5 and device 3 is unused but that
 * seem to be a करोcumentation error.  At least on my RM200C the Cirrus
 * Logic CL-GD5434 VGA is device 3.
 */
अटल अक्षर irq_tab_rm200[8][5] = अणु
	/*	 INTA  INTB  INTC  INTD */
	अणु     0,    0,	  0,	0,    0 पूर्ण,	/* EISA bridge */
	अणु  SCSI, SCSI, SCSI, SCSI, SCSI पूर्ण,	/* SCSI */
	अणु   ETH,  ETH,	ETH,  ETH,  ETH पूर्ण,	/* Ethernet */
	अणु  INTB, INTB, INTB, INTB, INTB पूर्ण,	/* VGA */
	अणु     0,    0,	  0,	0,    0 पूर्ण,	/* Unused */
	अणु     0, INTB, INTC, INTD, INTA पूर्ण,	/* Slot 2 */
	अणु     0, INTC, INTD, INTA, INTB पूर्ण,	/* Slot 3 */
	अणु     0, INTD, INTA, INTB, INTC पूर्ण,	/* Slot 4 */
पूर्ण;

/*
 * In Revision D of the RM300 Device 2 has become a normal purpose Slot 1
 *
 * The VGA card is optional क्रम RM300 प्रणालीs.
 */
अटल अक्षर irq_tab_rm300d[8][5] = अणु
	/*	 INTA  INTB  INTC  INTD */
	अणु     0,    0,	  0,	0,    0 पूर्ण,	/* EISA bridge */
	अणु  SCSI, SCSI, SCSI, SCSI, SCSI पूर्ण,	/* SCSI */
	अणु     0, INTC, INTD, INTA, INTB पूर्ण,	/* Slot 1 */
	अणु  INTB, INTB, INTB, INTB, INTB पूर्ण,	/* VGA */
	अणु     0,    0,	  0,	0,    0 पूर्ण,	/* Unused */
	अणु     0, INTB, INTC, INTD, INTA पूर्ण,	/* Slot 2 */
	अणु     0, INTC, INTD, INTA, INTB पूर्ण,	/* Slot 3 */
	अणु     0, INTD, INTA, INTB, INTC पूर्ण,	/* Slot 4 */
पूर्ण;

अटल अक्षर irq_tab_rm300e[5][5] = अणु
	/*	 INTA  INTB  INTC  INTD */
	अणु     0,    0,	  0,	0,    0 पूर्ण,	/* HOST bridge */
	अणु  SCSI, SCSI, SCSI, SCSI, SCSI पूर्ण,	/* SCSI */
	अणु     0, INTC, INTD, INTA, INTB पूर्ण,	/* Bridge/i960 */
	अणु     0, INTD, INTA, INTB, INTC पूर्ण,	/* Slot 1 */
	अणु     0, INTA, INTB, INTC, INTD पूर्ण,	/* Slot 2 */
पूर्ण;
#अघोषित SCSI
#अघोषित ETH
#अघोषित INTA
#अघोषित INTB
#अघोषित INTC
#अघोषित INTD


/*
 * PCIT Shortcuts ...
 */
#घोषणा SCSI0	PCIT_IRQ_SCSI0
#घोषणा SCSI1	PCIT_IRQ_SCSI1
#घोषणा ETH	PCIT_IRQ_ETHERNET
#घोषणा INTA	PCIT_IRQ_INTA
#घोषणा INTB	PCIT_IRQ_INTB
#घोषणा INTC	PCIT_IRQ_INTC
#घोषणा INTD	PCIT_IRQ_INTD

अटल अक्षर irq_tab_pcit[13][5] = अणु
	/*	 INTA  INTB  INTC  INTD */
	अणु     0,     0,	    0,	   0,	  0 पूर्ण,	/* HOST bridge */
	अणु SCSI0, SCSI0, SCSI0, SCSI0, SCSI0 पूर्ण,	/* SCSI */
	अणु SCSI1, SCSI1, SCSI1, SCSI1, SCSI1 पूर्ण,	/* SCSI */
	अणु   ETH,   ETH,	  ETH,	 ETH,	ETH पूर्ण,	/* Ethernet */
	अणु     0,  INTA,	 INTB,	INTC,  INTD पूर्ण,	/* PCI-PCI bridge */
	अणु     0,     0,	    0,	   0,	  0 पूर्ण,	/* Unused */
	अणु     0,     0,	    0,	   0,	  0 पूर्ण,	/* Unused */
	अणु     0,     0,	    0,	   0,	  0 पूर्ण,	/* Unused */
	अणु     0,  INTA,	 INTB,	INTC,  INTD पूर्ण,	/* Slot 1 */
	अणु     0,  INTB,	 INTC,	INTD,  INTA पूर्ण,	/* Slot 2 */
	अणु     0,  INTC,	 INTD,	INTA,  INTB पूर्ण,	/* Slot 3 */
	अणु     0,  INTD,	 INTA,	INTB,  INTC पूर्ण,	/* Slot 4 */
	अणु     0,  INTA,	 INTB,	INTC,  INTD पूर्ण,	/* Slot 5 */
पूर्ण;

अटल अक्षर irq_tab_pcit_cplus[13][5] = अणु
	/*	 INTA  INTB  INTC  INTD */
	अणु     0,     0,	    0,	   0,	  0 पूर्ण,	/* HOST bridge */
	अणु     0,  INTB,	 INTC,	INTD,  INTA पूर्ण,	/* PCI Slot 9 */
	अणु     0,     0,	    0,	   0,	  0 पूर्ण,	/* PCI-EISA */
	अणु     0,     0,	    0,	   0,	  0 पूर्ण,	/* Unused */
	अणु     0,  INTA,	 INTB,	INTC,  INTD पूर्ण,	/* PCI-PCI bridge */
	अणु     0,  INTB,	 INTC,	INTD,  INTA पूर्ण,	/* fixup */
पूर्ण;

अटल अंतरभूत पूर्णांक is_rm300_revd(व्योम)
अणु
	अचिन्हित अक्षर csmsr = *(अस्थिर अचिन्हित अक्षर *)PCIMT_CSMSR;

	वापस (csmsr & 0xa0) == 0x20;
पूर्ण

पूर्णांक pcibios_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	चयन (sni_brd_type) अणु
	हाल SNI_BRD_PCI_TOWER_CPLUS:
		अगर (slot == 4) अणु
			/*
			 * SNI messed up पूर्णांकerrupt wiring क्रम onboard
			 * PCI bus 1; we need to fix this up here
			 */
			जबतक (dev && dev->bus->number != 1)
				dev = dev->bus->self;
			अगर (dev && dev->devfn >= PCI_DEVFN(4, 0))
				slot = 5;
		पूर्ण
		वापस irq_tab_pcit_cplus[slot][pin];
	हाल SNI_BRD_PCI_TOWER:
		वापस irq_tab_pcit[slot][pin];

	हाल SNI_BRD_PCI_MTOWER:
		अगर (is_rm300_revd())
			वापस irq_tab_rm300d[slot][pin];
		fallthrough;
	हाल SNI_BRD_PCI_DESKTOP:
		वापस irq_tab_rm200[slot][pin];

	हाल SNI_BRD_PCI_MTOWER_CPLUS:
		वापस irq_tab_rm300e[slot][pin];
	पूर्ण

	वापस 0;
पूर्ण

/* Do platक्रमm specअगरic device initialization at pci_enable_device() समय */
पूर्णांक pcibios_plat_dev_init(काष्ठा pci_dev *dev)
अणु
	वापस 0;
पूर्ण
