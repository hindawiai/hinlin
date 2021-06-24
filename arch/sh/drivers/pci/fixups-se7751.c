<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pci.h>
#समावेश <linux/पन.स>
#समावेश <linux/sh_पूर्णांकc.h>
#समावेश "pci-sh4.h"

पूर्णांक pcibios_map_platक्रमm_irq(स्थिर काष्ठा pci_dev *, u8 slot, u8 pin)
अणु
        चयन (slot) अणु
        हाल 0: वापस evt2irq(0x3a0);
        हाल 1: वापस evt2irq(0x3a0);	/* AMD Ethernet controller */
        हाल 2: वापस -1;
        हाल 3: वापस -1;
        हाल 4: वापस -1;
        शेष:
                prपूर्णांकk("PCI: Bad IRQ mapping request for slot %d\n", slot);
                वापस -1;
        पूर्ण
पूर्ण

#घोषणा PCIMCR_MRSET_OFF	0xBFFFFFFF
#घोषणा PCIMCR_RFSH_OFF		0xFFFFFFFB

/*
 * Only दीर्घ word accesses of the PCIC's पूर्णांकernal local रेजिस्टरs and the
 * configuration रेजिस्टरs from the CPU is supported.
 */
#घोषणा PCIC_WRITE(x,v) ग_लिखोl((v), PCI_REG(x))
#घोषणा PCIC_READ(x) पढ़ोl(PCI_REG(x))

/*
 * Description:  This function sets up and initializes the pcic, sets
 * up the BARS, maps the DRAM पूर्णांकo the address space etc, etc.
 */
पूर्णांक pci_fixup_pcic(काष्ठा pci_channel *chan)
अणु
	अचिन्हित दीर्घ bcr1, wcr1, wcr2, wcr3, mcr;
	अचिन्हित लघु bcr2;

	/*
	* Initialize the slave bus controller on the pcic.  The values used
	* here should not be hardcoded, but they should be taken from the bsc
	* on the processor, to make this function as generic as possible.
	* (i.e. Another sbc may usr dअगरferent SDRAM timing settings -- in order
	* क्रम the pcic to work, its settings need to be exactly the same.)
	*/
	bcr1 = (*(अस्थिर अचिन्हित दीर्घ*)(SH7751_BCR1));
	bcr2 = (*(अस्थिर अचिन्हित लघु*)(SH7751_BCR2));
	wcr1 = (*(अस्थिर अचिन्हित दीर्घ*)(SH7751_WCR1));
	wcr2 = (*(अस्थिर अचिन्हित दीर्घ*)(SH7751_WCR2));
	wcr3 = (*(अस्थिर अचिन्हित दीर्घ*)(SH7751_WCR3));
	mcr = (*(अस्थिर अचिन्हित दीर्घ*)(SH7751_MCR));

	bcr1 = bcr1 | 0x00080000;  /* Enable Bit 19, BREQEN */
	(*(अस्थिर अचिन्हित दीर्घ*)(SH7751_BCR1)) = bcr1;

	bcr1 = bcr1 | 0x40080000;  /* Enable Bit 19 BREQEN, set PCIC to slave */
	PCIC_WRITE(SH7751_PCIBCR1, bcr1);	 /* PCIC BCR1 */
	PCIC_WRITE(SH7751_PCIBCR2, bcr2);     /* PCIC BCR2 */
	PCIC_WRITE(SH7751_PCIWCR1, wcr1);     /* PCIC WCR1 */
	PCIC_WRITE(SH7751_PCIWCR2, wcr2);     /* PCIC WCR2 */
	PCIC_WRITE(SH7751_PCIWCR3, wcr3);     /* PCIC WCR3 */
	mcr = (mcr & PCIMCR_MRSET_OFF) & PCIMCR_RFSH_OFF;
	PCIC_WRITE(SH7751_PCIMCR, mcr);      /* PCIC MCR */


	/* Enable all पूर्णांकerrupts, so we know what to fix */
	PCIC_WRITE(SH7751_PCIINTM, 0x0000c3ff);
	PCIC_WRITE(SH7751_PCIAINTM, 0x0000380f);

	/* Set up standard PCI config रेजिस्टरs */
	PCIC_WRITE(SH7751_PCICONF1,	0xF39000C7); /* Bus Master, Mem & I/O access */
	PCIC_WRITE(SH7751_PCICONF2,	0x00000000); /* PCI Class code & Revision ID */
	PCIC_WRITE(SH7751_PCICONF4,	0xab000001); /* PCI I/O address (local regs) */
	PCIC_WRITE(SH7751_PCICONF5,	0x0c000000); /* PCI MEM address (local RAM)  */
	PCIC_WRITE(SH7751_PCICONF6,	0xd0000000); /* PCI MEM address (unused)     */
	PCIC_WRITE(SH7751_PCICONF11, 0x35051054); /* PCI Subप्रणाली ID & Venकरोr ID */
	PCIC_WRITE(SH7751_PCILSR0, 0x03f00000);   /* MEM (full 64M exposed)       */
	PCIC_WRITE(SH7751_PCILSR1, 0x00000000);   /* MEM (unused)                 */
	PCIC_WRITE(SH7751_PCILAR0, 0x0c000000);   /* MEM (direct map from PCI)    */
	PCIC_WRITE(SH7751_PCILAR1, 0x00000000);   /* MEM (unused)                 */

	/* Now turn it on... */
	PCIC_WRITE(SH7751_PCICR, 0xa5000001);

	/*
	* Set PCIMBR and PCIIOBR here, assuming a single winकरोw
	* (16M MEM, 256K IO) is enough.  If a larger space is
	* needed, the पढ़ोx/ग_लिखोx and inx/outx functions will
	* have to करो more (e.g. setting रेजिस्टरs क्रम each call).
	*/

	/*
	* Set the MBR so PCI address is one-to-one with winकरोw,
	* meaning all calls go straight through... use BUG_ON to
	* catch erroneous assumption.
	*/
	BUG_ON(chan->resources[1].start != SH7751_PCI_MEMORY_BASE);

	PCIC_WRITE(SH7751_PCIMBR, chan->resources[1].start);

	/* Set IOBR क्रम winकरोw containing area specअगरied in pci.h */
	PCIC_WRITE(SH7751_PCIIOBR, (chan->resources[0].start & SH7751_PCIIOBR_MASK));

	/* All करोne, may as well say so... */
	prपूर्णांकk("SH7751 PCI: Finished initialization of the PCI controller\n");

	वापस 1;
पूर्ण
