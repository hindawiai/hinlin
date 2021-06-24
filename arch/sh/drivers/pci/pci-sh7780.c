<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Low-Level PCI Support क्रम the SH7780
 *
 *  Copyright (C) 2005 - 2010  Paul Mundt
 */
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/समयr.h>
#समावेश <linux/irq.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/delay.h>
#समावेश <linux/log2.h>
#समावेश "pci-sh4.h"
#समावेश <यंत्र/mmu.h>
#समावेश <linux/sizes.h>

#अगर defined(CONFIG_CPU_BIG_ENDIAN)
# define PCICR_ENDIANNESS SH4_PCICR_BSWP
#अन्यथा
# define PCICR_ENDIANNESS 0
#पूर्ण_अगर


अटल काष्ठा resource sh7785_pci_resources[] = अणु
	अणु
		.name	= "PCI IO",
		.start	= 0x1000,
		.end	= SZ_4M - 1,
		.flags	= IORESOURCE_IO,
	पूर्ण, अणु
		.name	= "PCI MEM 0",
		.start	= 0xfd000000,
		.end	= 0xfd000000 + SZ_16M - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण, अणु
		.name	= "PCI MEM 1",
		.start	= 0x10000000,
		.end	= 0x10000000 + SZ_64M - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण, अणु
		/*
		 * 32-bit only resources must be last.
		 */
		.name	= "PCI MEM 2",
		.start	= 0xc0000000,
		.end	= 0xc0000000 + SZ_512M - 1,
		.flags	= IORESOURCE_MEM | IORESOURCE_MEM_32BIT,
	पूर्ण,
पूर्ण;

अटल काष्ठा pci_channel sh7780_pci_controller = अणु
	.pci_ops	= &sh4_pci_ops,
	.resources	= sh7785_pci_resources,
	.nr_resources	= ARRAY_SIZE(sh7785_pci_resources),
	.io_offset	= 0,
	.mem_offset	= 0,
	.io_map_base	= 0xfe200000,
	.serr_irq	= evt2irq(0xa00),
	.err_irq	= evt2irq(0xaa0),
पूर्ण;

काष्ठा pci_errors अणु
	अचिन्हित पूर्णांक	mask;
	स्थिर अक्षर	*str;
पूर्ण pci_arbiter_errors[] = अणु
	अणु SH4_PCIAINT_MBKN,	"master broken" पूर्ण,
	अणु SH4_PCIAINT_TBTO,	"target bus time out" पूर्ण,
	अणु SH4_PCIAINT_MBTO,	"master bus time out" पूर्ण,
	अणु SH4_PCIAINT_TABT,	"target abort" पूर्ण,
	अणु SH4_PCIAINT_MABT,	"master abort" पूर्ण,
	अणु SH4_PCIAINT_RDPE,	"read data parity error" पूर्ण,
	अणु SH4_PCIAINT_WDPE,	"write data parity error" पूर्ण,
पूर्ण, pci_पूर्णांकerrupt_errors[] = अणु
	अणु SH4_PCIINT_MLCK,	"master lock error" पूर्ण,
	अणु SH4_PCIINT_TABT,	"target-target abort" पूर्ण,
	अणु SH4_PCIINT_TRET,	"target retry time out" पूर्ण,
	अणु SH4_PCIINT_MFDE,	"master function disable error" पूर्ण,
	अणु SH4_PCIINT_PRTY,	"address parity error" पूर्ण,
	अणु SH4_PCIINT_SERR,	"SERR" पूर्ण,
	अणु SH4_PCIINT_TWDP,	"data parity error for target write" पूर्ण,
	अणु SH4_PCIINT_TRDP,	"PERR detected for target read" पूर्ण,
	अणु SH4_PCIINT_MTABT,	"target abort for master" पूर्ण,
	अणु SH4_PCIINT_MMABT,	"master abort for master" पूर्ण,
	अणु SH4_PCIINT_MWPD,	"master write data parity error" पूर्ण,
	अणु SH4_PCIINT_MRPD,	"master read data parity error" पूर्ण,
पूर्ण;

अटल irqवापस_t sh7780_pci_err_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा pci_channel *hose = dev_id;
	अचिन्हित दीर्घ addr;
	अचिन्हित पूर्णांक status;
	अचिन्हित पूर्णांक cmd;
	पूर्णांक i;

	addr = __raw_पढ़ोl(hose->reg_base + SH4_PCIALR);

	/*
	 * Handle status errors.
	 */
	status = __raw_पढ़ोw(hose->reg_base + PCI_STATUS);
	अगर (status & (PCI_STATUS_PARITY |
		      PCI_STATUS_DETECTED_PARITY |
		      PCI_STATUS_SIG_TARGET_ABORT |
		      PCI_STATUS_REC_TARGET_ABORT |
		      PCI_STATUS_REC_MASTER_ABORT)) अणु
		cmd = pcibios_handle_status_errors(addr, status, hose);
		अगर (likely(cmd))
			__raw_ग_लिखोw(cmd, hose->reg_base + PCI_STATUS);
	पूर्ण

	/*
	 * Handle arbiter errors.
	 */
	status = __raw_पढ़ोl(hose->reg_base + SH4_PCIAINT);
	क्रम (i = cmd = 0; i < ARRAY_SIZE(pci_arbiter_errors); i++) अणु
		अगर (status & pci_arbiter_errors[i].mask) अणु
			prपूर्णांकk(KERN_DEBUG "PCI: %s, addr=%08lx\n",
			       pci_arbiter_errors[i].str, addr);
			cmd |= pci_arbiter_errors[i].mask;
		पूर्ण
	पूर्ण
	__raw_ग_लिखोl(cmd, hose->reg_base + SH4_PCIAINT);

	/*
	 * Handle the reमुख्यing PCI errors.
	 */
	status = __raw_पढ़ोl(hose->reg_base + SH4_PCIINT);
	क्रम (i = cmd = 0; i < ARRAY_SIZE(pci_पूर्णांकerrupt_errors); i++) अणु
		अगर (status & pci_पूर्णांकerrupt_errors[i].mask) अणु
			prपूर्णांकk(KERN_DEBUG "PCI: %s, addr=%08lx\n",
			       pci_पूर्णांकerrupt_errors[i].str, addr);
			cmd |= pci_पूर्णांकerrupt_errors[i].mask;
		पूर्ण
	पूर्ण
	__raw_ग_लिखोl(cmd, hose->reg_base + SH4_PCIINT);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t sh7780_pci_serr_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा pci_channel *hose = dev_id;

	prपूर्णांकk(KERN_DEBUG "PCI: system error received: ");
	pcibios_report_status(PCI_STATUS_SIG_SYSTEM_ERROR, 1);
	pr_cont("\n");

	/* Deनिश्चित SERR */
	__raw_ग_लिखोl(SH4_PCIINTM_SDIM, hose->reg_base + SH4_PCIINTM);

	/* Back off the IRQ क्रम aजबतक */
	disable_irq_nosync(irq);
	hose->serr_समयr.expires = jअगरfies + HZ;
	add_समयr(&hose->serr_समयr);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक __init sh7780_pci_setup_irqs(काष्ठा pci_channel *hose)
अणु
	पूर्णांक ret;

	/* Clear out PCI arbiter IRQs */
	__raw_ग_लिखोl(0, hose->reg_base + SH4_PCIAINT);

	/* Clear all error conditions */
	__raw_ग_लिखोw(PCI_STATUS_DETECTED_PARITY  | \
		     PCI_STATUS_SIG_SYSTEM_ERROR | \
		     PCI_STATUS_REC_MASTER_ABORT | \
		     PCI_STATUS_REC_TARGET_ABORT | \
		     PCI_STATUS_SIG_TARGET_ABORT | \
		     PCI_STATUS_PARITY, hose->reg_base + PCI_STATUS);

	ret = request_irq(hose->serr_irq, sh7780_pci_serr_irq, 0,
			  "PCI SERR interrupt", hose);
	अगर (unlikely(ret)) अणु
		pr_err("PCI: Failed hooking SERR IRQ\n");
		वापस ret;
	पूर्ण

	/*
	 * The PCI ERR IRQ needs to be IRQF_SHARED since all of the घातer
	 * करोwn IRQ vectors are routed through the ERR IRQ vector. We
	 * only request_irq() once as there is only a single masking
	 * source क्रम multiple events.
	 */
	ret = request_irq(hose->err_irq, sh7780_pci_err_irq, IRQF_SHARED,
			  "PCI ERR interrupt", hose);
	अगर (unlikely(ret)) अणु
		मुक्त_irq(hose->serr_irq, hose);
		वापस ret;
	पूर्ण

	/* Unmask all of the arbiter IRQs. */
	__raw_ग_लिखोl(SH4_PCIAINT_MBKN | SH4_PCIAINT_TBTO | SH4_PCIAINT_MBTO | \
		     SH4_PCIAINT_TABT | SH4_PCIAINT_MABT | SH4_PCIAINT_RDPE | \
		     SH4_PCIAINT_WDPE, hose->reg_base + SH4_PCIAINTM);

	/* Unmask all of the PCI IRQs */
	__raw_ग_लिखोl(SH4_PCIINTM_TTADIM  | SH4_PCIINTM_TMTOIM  | \
		     SH4_PCIINTM_MDEIM   | SH4_PCIINTM_APEDIM  | \
		     SH4_PCIINTM_SDIM    | SH4_PCIINTM_DPEITWM | \
		     SH4_PCIINTM_PEDITRM | SH4_PCIINTM_TADIMM  | \
		     SH4_PCIINTM_MADIMM  | SH4_PCIINTM_MWPDIM  | \
		     SH4_PCIINTM_MRDPEIM, hose->reg_base + SH4_PCIINTM);

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम __init sh7780_pci_tearकरोwn_irqs(काष्ठा pci_channel *hose)
अणु
	मुक्त_irq(hose->err_irq, hose);
	मुक्त_irq(hose->serr_irq, hose);
पूर्ण

अटल व्योम __init sh7780_pci66_init(काष्ठा pci_channel *hose)
अणु
	अचिन्हित पूर्णांक पंचांगp;

	अगर (!pci_is_66mhz_capable(hose, 0, 0))
		वापस;

	/* Enable रेजिस्टर access */
	पंचांगp = __raw_पढ़ोl(hose->reg_base + SH4_PCICR);
	पंचांगp |= SH4_PCICR_PREFIX;
	__raw_ग_लिखोl(पंचांगp, hose->reg_base + SH4_PCICR);

	/* Enable 66MHz operation */
	पंचांगp = __raw_पढ़ोw(hose->reg_base + PCI_STATUS);
	पंचांगp |= PCI_STATUS_66MHZ;
	__raw_ग_लिखोw(पंचांगp, hose->reg_base + PCI_STATUS);

	/* Done */
	पंचांगp = __raw_पढ़ोl(hose->reg_base + SH4_PCICR);
	पंचांगp |= SH4_PCICR_PREFIX | SH4_PCICR_CFIN;
	__raw_ग_लिखोl(पंचांगp, hose->reg_base + SH4_PCICR);
पूर्ण

अटल पूर्णांक __init sh7780_pci_init(व्योम)
अणु
	काष्ठा pci_channel *chan = &sh7780_pci_controller;
	phys_addr_t memphys;
	माप_प्रकार memsize;
	अचिन्हित पूर्णांक id;
	स्थिर अक्षर *type;
	पूर्णांक ret, i;

	pr_notice("PCI: Starting initialization.\n");

	chan->reg_base = 0xfe040000;

	/* Enable CPU access to the PCIC रेजिस्टरs. */
	__raw_ग_लिखोl(PCIECR_ENBL, PCIECR);

	/* Reset */
	__raw_ग_लिखोl(SH4_PCICR_PREFIX | SH4_PCICR_PRST | PCICR_ENDIANNESS,
		     chan->reg_base + SH4_PCICR);

	/*
	 * Wait क्रम it to come back up. The spec says to allow क्रम up to
	 * 1 second after toggling the reset pin, but in practice 100ms
	 * is more than enough.
	 */
	mdelay(100);

	id = __raw_पढ़ोw(chan->reg_base + PCI_VENDOR_ID);
	अगर (id != PCI_VENDOR_ID_RENESAS) अणु
		pr_err("PCI: Unknown vendor ID 0x%04x.\n", id);
		वापस -ENODEV;
	पूर्ण

	id = __raw_पढ़ोw(chan->reg_base + PCI_DEVICE_ID);
	type = (id == PCI_DEVICE_ID_RENESAS_SH7763) ? "SH7763" :
	       (id == PCI_DEVICE_ID_RENESAS_SH7780) ? "SH7780" :
	       (id == PCI_DEVICE_ID_RENESAS_SH7781) ? "SH7781" :
	       (id == PCI_DEVICE_ID_RENESAS_SH7785) ? "SH7785" :
					  शून्य;
	अगर (unlikely(!type)) अणु
		pr_err("PCI: Found an unsupported Renesas host controller, device id 0x%04x.\n",
		       id);
		वापस -EINVAL;
	पूर्ण

	pr_notice("PCI: Found a Renesas %s host controller, revision %d.\n",
		  type, __raw_पढ़ोb(chan->reg_base + PCI_REVISION_ID));

	/*
	 * Now throw it in to रेजिस्टर initialization mode and
	 * start the real work.
	 */
	__raw_ग_लिखोl(SH4_PCICR_PREFIX | PCICR_ENDIANNESS,
		     chan->reg_base + SH4_PCICR);

	memphys = __pa(memory_start);
	memsize = roundup_घात_of_two(memory_end - memory_start);

	/*
	 * If there's more than 512MB of memory, we need to roll over to
	 * LAR1/LSR1.
	 */
	अगर (memsize > SZ_512M) अणु
		__raw_ग_लिखोl(memphys + SZ_512M, chan->reg_base + SH4_PCILAR1);
		__raw_ग_लिखोl((((memsize - SZ_512M) - SZ_1M) & 0x1ff00000) | 1,
			     chan->reg_base + SH4_PCILSR1);
		memsize = SZ_512M;
	पूर्ण अन्यथा अणु
		/*
		 * Otherwise just zero it out and disable it.
		 */
		__raw_ग_लिखोl(0, chan->reg_base + SH4_PCILAR1);
		__raw_ग_लिखोl(0, chan->reg_base + SH4_PCILSR1);
	पूर्ण

	/*
	 * LAR0/LSR0 covers up to the first 512MB, which is enough to
	 * cover all of lowmem on most platक्रमms.
	 */
	__raw_ग_लिखोl(memphys, chan->reg_base + SH4_PCILAR0);
	__raw_ग_लिखोl(((memsize - SZ_1M) & 0x1ff00000) | 1,
		     chan->reg_base + SH4_PCILSR0);

	/*
	 * Hook up the ERR and SERR IRQs.
	 */
	ret = sh7780_pci_setup_irqs(chan);
	अगर (unlikely(ret))
		वापस ret;

	/*
	 * Disable the cache snoop controller क्रम non-coherent DMA.
	 */
	__raw_ग_लिखोl(0, chan->reg_base + SH7780_PCICSCR0);
	__raw_ग_लिखोl(0, chan->reg_base + SH7780_PCICSAR0);
	__raw_ग_लिखोl(0, chan->reg_base + SH7780_PCICSCR1);
	__raw_ग_लिखोl(0, chan->reg_base + SH7780_PCICSAR1);

	/*
	 * Setup the memory BARs
	 */
	क्रम (i = 1; i < chan->nr_resources; i++) अणु
		काष्ठा resource *res = chan->resources + i;
		resource_माप_प्रकार size;

		अगर (unlikely(res->flags & IORESOURCE_IO))
			जारी;

		/*
		 * Make sure we're in the right physical addressing mode
		 * क्रम dealing with the resource.
		 */
		अगर ((res->flags & IORESOURCE_MEM_32BIT) && __in_29bit_mode()) अणु
			chan->nr_resources--;
			जारी;
		पूर्ण

		size = resource_size(res);

		/*
		 * The MBMR mask is calculated in units of 256kB, which
		 * keeps things pretty simple.
		 */
		__raw_ग_लिखोl(((roundup_घात_of_two(size) / SZ_256K) - 1) << 18,
			     chan->reg_base + SH7780_PCIMBMR(i - 1));
		__raw_ग_लिखोl(res->start, chan->reg_base + SH7780_PCIMBR(i - 1));
	पूर्ण

	/*
	 * And I/O.
	 */
	__raw_ग_लिखोl(0, chan->reg_base + PCI_BASE_ADDRESS_0);
	__raw_ग_लिखोl(0, chan->reg_base + SH7780_PCIIOBR);
	__raw_ग_लिखोl(0, chan->reg_base + SH7780_PCIIOBMR);

	__raw_ग_लिखोw(PCI_COMMAND_SERR   | PCI_COMMAND_WAIT   | \
		     PCI_COMMAND_PARITY | PCI_COMMAND_MASTER | \
		     PCI_COMMAND_MEMORY, chan->reg_base + PCI_COMMAND);

	/*
	 * Initialization mode complete, release the control रेजिस्टर and
	 * enable round robin mode to stop device overruns/starvation.
	 */
	__raw_ग_लिखोl(SH4_PCICR_PREFIX | SH4_PCICR_CFIN | SH4_PCICR_FTO |
		     PCICR_ENDIANNESS,
		     chan->reg_base + SH4_PCICR);

	ret = रेजिस्टर_pci_controller(chan);
	अगर (unlikely(ret))
		जाओ err;

	sh7780_pci66_init(chan);

	pr_notice("PCI: Running at %dMHz.\n",
		  (__raw_पढ़ोw(chan->reg_base + PCI_STATUS) & PCI_STATUS_66MHZ)
		  ? 66 : 33);

	वापस 0;

err:
	sh7780_pci_tearकरोwn_irqs(chan);
	वापस ret;
पूर्ण
arch_initcall(sh7780_pci_init);
