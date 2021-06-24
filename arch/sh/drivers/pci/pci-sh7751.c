<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Low-Level PCI Support क्रम the SH7751
 *
 *  Copyright (C) 2003 - 2009  Paul Mundt
 *  Copyright (C) 2001  Dustin McIntire
 *
 *  With cleanup by Paul van Gool <pvangool@mimotech.com>, 2003.
 */
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पन.स>
#समावेश "pci-sh4.h"
#समावेश <यंत्र/addrspace.h>
#समावेश <linux/sizes.h>

अटल पूर्णांक __init __area_sdram_check(काष्ठा pci_channel *chan,
				     अचिन्हित पूर्णांक area)
अणु
	अचिन्हित दीर्घ word;

	word = __raw_पढ़ोl(SH7751_BCR1);
	/* check BCR क्रम SDRAM in area */
	अगर (((word >> area) & 1) == 0) अणु
		prपूर्णांकk("PCI: Area %d is not configured for SDRAM. BCR1=0x%lx\n",
		       area, word);
		वापस 0;
	पूर्ण
	pci_ग_लिखो_reg(chan, word, SH4_PCIBCR1);

	word = __raw_पढ़ोw(SH7751_BCR2);
	/* check BCR2 क्रम 32bit SDRAM पूर्णांकerface*/
	अगर (((word >> (area << 1)) & 0x3) != 0x3) अणु
		prपूर्णांकk("PCI: Area %d is not 32 bit SDRAM. BCR2=0x%lx\n",
		       area, word);
		वापस 0;
	पूर्ण
	pci_ग_लिखो_reg(chan, word, SH4_PCIBCR2);

	वापस 1;
पूर्ण

अटल काष्ठा resource sh7751_pci_resources[] = अणु
	अणु
		.name	= "SH7751_IO",
		.start	= 0x1000,
		.end	= SZ_4M - 1,
		.flags	= IORESOURCE_IO
	पूर्ण, अणु
		.name	= "SH7751_mem",
		.start	= SH7751_PCI_MEMORY_BASE,
		.end	= SH7751_PCI_MEMORY_BASE + SH7751_PCI_MEM_SIZE - 1,
		.flags	= IORESOURCE_MEM
	पूर्ण,
पूर्ण;

अटल काष्ठा pci_channel sh7751_pci_controller = अणु
	.pci_ops	= &sh4_pci_ops,
	.resources	= sh7751_pci_resources,
	.nr_resources	= ARRAY_SIZE(sh7751_pci_resources),
	.mem_offset	= 0x00000000,
	.io_offset	= 0x00000000,
	.io_map_base	= SH7751_PCI_IO_BASE,
पूर्ण;

अटल काष्ठा sh4_pci_address_map sh7751_pci_map = अणु
	.winकरोw0	= अणु
		.base	= SH7751_CS3_BASE_ADDR,
		.size	= 0x04000000,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init sh7751_pci_init(व्योम)
अणु
	काष्ठा pci_channel *chan = &sh7751_pci_controller;
	अचिन्हित पूर्णांक id;
	u32 word, reg;

	prपूर्णांकk(KERN_NOTICE "PCI: Starting initialization.\n");

	chan->reg_base = 0xfe200000;

	/* check क्रम SH7751/SH7751R hardware */
	id = pci_पढ़ो_reg(chan, SH7751_PCICONF0);
	अगर (id != ((SH7751_DEVICE_ID << 16) | SH7751_VENDOR_ID) &&
	    id != ((SH7751R_DEVICE_ID << 16) | SH7751_VENDOR_ID)) अणु
		pr_debug("PCI: This is not an SH7751(R) (%x)\n", id);
		वापस -ENODEV;
	पूर्ण

	/* Set the BCR's to enable PCI access */
	reg = __raw_पढ़ोl(SH7751_BCR1);
	reg |= 0x80000;
	__raw_ग_लिखोl(reg, SH7751_BCR1);

	/* Turn the घड़ीs back on (not करोne in reset)*/
	pci_ग_लिखो_reg(chan, 0, SH4_PCICLKR);
	/* Clear Powerकरोwn IRQ's (not करोne in reset) */
	word = SH4_PCIPINT_D3 | SH4_PCIPINT_D0;
	pci_ग_लिखो_reg(chan, word, SH4_PCIPINT);

	/* set the command/status bits to:
	 * Wait Cycle Control + Parity Enable + Bus Master +
	 * Mem space enable
	 */
	word = SH7751_PCICONF1_WCC | SH7751_PCICONF1_PER |
	       SH7751_PCICONF1_BUM | SH7751_PCICONF1_MES;
	pci_ग_लिखो_reg(chan, word, SH7751_PCICONF1);

	/* define this host as the host bridge */
	word = PCI_BASE_CLASS_BRIDGE << 24;
	pci_ग_लिखो_reg(chan, word, SH7751_PCICONF2);

	/* Set IO and Mem winकरोws to local address
	 * Make PCI and local address the same क्रम easy 1 to 1 mapping
	 */
	word = sh7751_pci_map.winकरोw0.size - 1;
	pci_ग_लिखो_reg(chan, word, SH4_PCILSR0);
	/* Set the values on winकरोw 0 PCI config रेजिस्टरs */
	word = P2SEGADDR(sh7751_pci_map.winकरोw0.base);
	pci_ग_लिखो_reg(chan, word, SH4_PCILAR0);
	pci_ग_लिखो_reg(chan, word, SH7751_PCICONF5);

	/* Set the local 16MB PCI memory space winकरोw to
	 * the lowest PCI mapped address
	 */
	word = chan->resources[1].start & SH4_PCIMBR_MASK;
	pr_debug("PCI: Setting upper bits of Memory window to 0x%x\n", word);
	pci_ग_लिखो_reg(chan, word , SH4_PCIMBR);

	/* Make sure the MSB's of IO winकरोw are set to access PCI space
	 * correctly */
	word = chan->resources[0].start & SH4_PCIIOBR_MASK;
	pr_debug("PCI: Setting upper bits of IO window to 0x%x\n", word);
	pci_ग_लिखो_reg(chan, word, SH4_PCIIOBR);

	/* Set PCI WCRx, BCRx's, copy from BSC locations */

	/* check BCR क्रम SDRAM in specअगरied area */
	चयन (sh7751_pci_map.winकरोw0.base) अणु
	हाल SH7751_CS0_BASE_ADDR: word = __area_sdram_check(chan, 0); अवरोध;
	हाल SH7751_CS1_BASE_ADDR: word = __area_sdram_check(chan, 1); अवरोध;
	हाल SH7751_CS2_BASE_ADDR: word = __area_sdram_check(chan, 2); अवरोध;
	हाल SH7751_CS3_BASE_ADDR: word = __area_sdram_check(chan, 3); अवरोध;
	हाल SH7751_CS4_BASE_ADDR: word = __area_sdram_check(chan, 4); अवरोध;
	हाल SH7751_CS5_BASE_ADDR: word = __area_sdram_check(chan, 5); अवरोध;
	हाल SH7751_CS6_BASE_ADDR: word = __area_sdram_check(chan, 6); अवरोध;
	पूर्ण

	अगर (!word)
		वापस -1;

	/* configure the रुको control रेजिस्टरs */
	word = __raw_पढ़ोl(SH7751_WCR1);
	pci_ग_लिखो_reg(chan, word, SH4_PCIWCR1);
	word = __raw_पढ़ोl(SH7751_WCR2);
	pci_ग_लिखो_reg(chan, word, SH4_PCIWCR2);
	word = __raw_पढ़ोl(SH7751_WCR3);
	pci_ग_लिखो_reg(chan, word, SH4_PCIWCR3);
	word = __raw_पढ़ोl(SH7751_MCR);
	pci_ग_लिखो_reg(chan, word, SH4_PCIMCR);

	/* NOTE: I'm ignoring the PCI error IRQs क्रम now..
	 * TODO: add support क्रम the पूर्णांकernal error पूर्णांकerrupts and
	 * DMA पूर्णांकerrupts...
	 */

	pci_fixup_pcic(chan);

	/* SH7751 init करोne, set central function init complete */
	/* use round robin mode to stop a device starving/overruning */
	word = SH4_PCICR_PREFIX | SH4_PCICR_CFIN | SH4_PCICR_ARBM;
	pci_ग_लिखो_reg(chan, word, SH4_PCICR);

	वापस रेजिस्टर_pci_controller(chan);
पूर्ण
arch_initcall(sh7751_pci_init);
