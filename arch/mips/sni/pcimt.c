<शैली गुरु>
/*
 * PCIMT specअगरic code
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1996, 97, 98, 2000, 03, 04, 06 Ralf Baechle (ralf@linux-mips.org)
 * Copyright (C) 2006,2007 Thomas Bogenकरोerfer (tsbogend@alpha.franken.de)
 */

#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/pci.h>
#समावेश <linux/serial_8250.h>

#समावेश <यंत्र/sni.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/i8259.h>
#समावेश <यंत्र/irq_cpu.h>

#घोषणा cacheconf (*(अस्थिर अचिन्हित पूर्णांक *)PCIMT_CACHECONF)
#घोषणा invspace (*(अस्थिर अचिन्हित पूर्णांक *)PCIMT_INVSPACE)

अटल व्योम __init sni_pcimt_sc_init(व्योम)
अणु
	अचिन्हित पूर्णांक scsiz, sc_size;

	scsiz = cacheconf & 7;
	अगर (scsiz == 0) अणु
		prपूर्णांकk("Second level cache is deactivated.\n");
		वापस;
	पूर्ण
	अगर (scsiz >= 6) अणु
		prपूर्णांकk("Invalid second level cache size configured, "
		       "deactivating second level cache.\n");
		cacheconf = 0;
		वापस;
	पूर्ण

	sc_size = 128 << scsiz;
	prपूर्णांकk("%dkb second level cache detected, deactivating.\n", sc_size);
	cacheconf = 0;
पूर्ण


/*
 * A bit more gossip about the iron we're running on ...
 */
अटल अंतरभूत व्योम sni_pcimt_detect(व्योम)
अणु
	अक्षर boardtype[80];
	अचिन्हित अक्षर csmsr;
	अक्षर *p = boardtype;
	अचिन्हित पूर्णांक asic;

	csmsr = *(अस्थिर अचिन्हित अक्षर *)PCIMT_CSMSR;

	p += प्र_लिखो(p, "%s PCI", (csmsr & 0x80) ? "RM200" : "RM300");
	अगर ((csmsr & 0x80) == 0)
		p += प्र_लिखो(p, ", board revision %s",
			     (csmsr & 0x20) ? "D" : "C");
	asic = csmsr & 0x80;
	asic = (csmsr & 0x08) ? asic : !asic;
	p += प्र_लिखो(p, ", ASIC PCI Rev %s", asic ? "1.0" : "1.1");
	prपूर्णांकk("%s.\n", boardtype);
पूर्ण

#घोषणा PORT(_base,_irq)				\
	अणु						\
		.iobase		= _base,		\
		.irq		= _irq,			\
		.uartclk	= 1843200,		\
		.iotype		= UPIO_PORT,		\
		.flags		= UPF_BOOT_AUTOCONF,	\
	पूर्ण

अटल काष्ठा plat_serial8250_port pcimt_data[] = अणु
	PORT(0x3f8, 4),
	PORT(0x2f8, 3),
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device pcimt_serial8250_device = अणु
	.name			= "serial8250",
	.id			= PLAT8250_DEV_PLATFORM,
	.dev			= अणु
		.platक्रमm_data	= pcimt_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource pcimt_cmos_rsrc[] = अणु
	अणु
		.start = 0x70,
		.end   = 0x71,
		.flags = IORESOURCE_IO
	पूर्ण,
	अणु
		.start = 8,
		.end   = 8,
		.flags = IORESOURCE_IRQ
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device pcimt_cmos_device = अणु
	.name		= "rtc_cmos",
	.num_resources	= ARRAY_SIZE(pcimt_cmos_rsrc),
	.resource	= pcimt_cmos_rsrc
पूर्ण;


अटल काष्ठा resource sni_io_resource = अणु
	.start	= 0x00000000UL,
	.end	= 0x03bfffffUL,
	.name	= "PCIMT IO MEM",
	.flags	= IORESOURCE_IO,
पूर्ण;

अटल काष्ठा resource pcimt_io_resources[] = अणु
	अणु
		.start	= 0x00,
		.end	= 0x1f,
		.name	= "dma1",
		.flags	= IORESOURCE_BUSY
	पूर्ण, अणु
		.start	=  0x40,
		.end	= 0x5f,
		.name	= "timer",
		.flags	= IORESOURCE_BUSY
	पूर्ण, अणु
		.start	=  0x60,
		.end	= 0x6f,
		.name	= "keyboard",
		.flags	= IORESOURCE_BUSY
	पूर्ण, अणु
		.start	=  0x80,
		.end	= 0x8f,
		.name	= "dma page reg",
		.flags	= IORESOURCE_BUSY
	पूर्ण, अणु
		.start	=  0xc0,
		.end	= 0xdf,
		.name	= "dma2",
		.flags	= IORESOURCE_BUSY
	पूर्ण, अणु
		.start	=  0xcfc,
		.end	= 0xcff,
		.name	= "PCI config data",
		.flags	= IORESOURCE_BUSY
	पूर्ण
पूर्ण;

अटल काष्ठा resource pcimt_mem_resources[] = अणु
	अणु
		/*
		 * this region should only be 4 bytes दीर्घ,
		 * but it's 16MB on all RM300C I've checked
		 */
		.start	= 0x1a000000,
		.end	= 0x1affffff,
		.name	= "PCI INT ACK",
		.flags	= IORESOURCE_BUSY
	पूर्ण
पूर्ण;

अटल काष्ठा resource sni_mem_resource = अणु
	.start	= 0x18000000UL,
	.end	= 0x1fbfffffUL,
	.name	= "PCIMT PCI MEM",
	.flags	= IORESOURCE_MEM
पूर्ण;

अटल व्योम __init sni_pcimt_resource_init(व्योम)
अणु
	पूर्णांक i;

	/* request I/O space क्रम devices used on all i[345]86 PCs */
	क्रम (i = 0; i < ARRAY_SIZE(pcimt_io_resources); i++)
		request_resource(&sni_io_resource, pcimt_io_resources + i);
	/* request MEM space क्रम devices used on all i[345]86 PCs */
	क्रम (i = 0; i < ARRAY_SIZE(pcimt_mem_resources); i++)
		request_resource(&sni_mem_resource, pcimt_mem_resources + i);
पूर्ण

बाह्य काष्ठा pci_ops sni_pcimt_ops;

#अगर_घोषित CONFIG_PCI
अटल काष्ठा pci_controller sni_controller = अणु
	.pci_ops	= &sni_pcimt_ops,
	.mem_resource	= &sni_mem_resource,
	.mem_offset	= 0x00000000UL,
	.io_resource	= &sni_io_resource,
	.io_offset	= 0x00000000UL,
	.io_map_base	= SNI_PORT_BASE
पूर्ण;
#पूर्ण_अगर

अटल व्योम enable_pcimt_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक mask = 1 << (d->irq - PCIMT_IRQ_INT2);

	*(अस्थिर u8 *) PCIMT_IRQSEL |= mask;
पूर्ण

व्योम disable_pcimt_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक mask = ~(1 << (d->irq - PCIMT_IRQ_INT2));

	*(अस्थिर u8 *) PCIMT_IRQSEL &= mask;
पूर्ण

अटल काष्ठा irq_chip pcimt_irq_type = अणु
	.name = "PCIMT",
	.irq_mask = disable_pcimt_irq,
	.irq_unmask = enable_pcimt_irq,
पूर्ण;

/*
 * hwपूर्णांक0 should deal with MP agent, ASIC PCI, EISA NMI and debug
 * button पूर्णांकerrupts.  Later ...
 */
अटल व्योम pcimt_hwपूर्णांक0(व्योम)
अणु
	panic("Received int0 but no handler yet ...");
पूर्ण

/*
 * hwपूर्णांक 1 deals with EISA and SCSI पूर्णांकerrupts,
 *
 * The EISA_INT bit in CSITPEND is high active, all others are low active.
 */
अटल व्योम pcimt_hwपूर्णांक1(व्योम)
अणु
	u8 pend = *(अस्थिर अक्षर *)PCIMT_CSITPEND;
	अचिन्हित दीर्घ flags;

	अगर (pend & IT_EISA) अणु
		पूर्णांक irq;
		/*
		 * Note: ASIC PCI's builtin पूर्णांकerrupt acknowledge feature is
		 * broken.  Using it may result in loss of some or all i8259
		 * पूर्णांकerrupts, so करोn't use PCIMT_INT_ACKNOWLEDGE ...
		 */
		irq = i8259_irq();
		अगर (unlikely(irq < 0))
			वापस;

		करो_IRQ(irq);
	पूर्ण

	अगर (!(pend & IT_SCSI)) अणु
		flags = पढ़ो_c0_status();
		clear_c0_status(ST0_IM);
		करो_IRQ(PCIMT_IRQ_SCSI);
		ग_लिखो_c0_status(flags);
	पूर्ण
पूर्ण

/*
 * hwपूर्णांक 3 should deal with the PCI A - D पूर्णांकerrupts,
 */
अटल व्योम pcimt_hwपूर्णांक3(व्योम)
अणु
	u8 pend = *(अस्थिर अक्षर *)PCIMT_CSITPEND;
	पूर्णांक irq;

	pend &= (IT_INTA | IT_INTB | IT_INTC | IT_INTD);
	pend ^= (IT_INTA | IT_INTB | IT_INTC | IT_INTD);
	clear_c0_status(IE_IRQ3);
	irq = PCIMT_IRQ_INT2 + ffs(pend) - 1;
	करो_IRQ(irq);
	set_c0_status(IE_IRQ3);
पूर्ण

अटल व्योम sni_pcimt_hwपूर्णांक(व्योम)
अणु
	u32 pending = पढ़ो_c0_cause() & पढ़ो_c0_status();

	अगर (pending & C_IRQ5)
		करो_IRQ(MIPS_CPU_IRQ_BASE + 7);
	अन्यथा अगर (pending & C_IRQ4)
		करो_IRQ(MIPS_CPU_IRQ_BASE + 6);
	अन्यथा अगर (pending & C_IRQ3)
		pcimt_hwपूर्णांक3();
	अन्यथा अगर (pending & C_IRQ1)
		pcimt_hwपूर्णांक1();
	अन्यथा अगर (pending & C_IRQ0) अणु
		pcimt_hwपूर्णांक0();
	पूर्ण
पूर्ण

व्योम __init sni_pcimt_irq_init(व्योम)
अणु
	पूर्णांक i;

	*(अस्थिर u8 *) PCIMT_IRQSEL = IT_ETH | IT_EISA;
	mips_cpu_irq_init();
	/* Actually we've got more पूर्णांकerrupts to handle ...  */
	क्रम (i = PCIMT_IRQ_INT2; i <= PCIMT_IRQ_SCSI; i++)
		irq_set_chip_and_handler(i, &pcimt_irq_type, handle_level_irq);
	sni_hwपूर्णांक = sni_pcimt_hwपूर्णांक;
	change_c0_status(ST0_IM, IE_IRQ1|IE_IRQ3);
पूर्ण

व्योम __init sni_pcimt_init(व्योम)
अणु
	sni_pcimt_detect();
	sni_pcimt_sc_init();
	ioport_resource.end = sni_io_resource.end;
#अगर_घोषित CONFIG_PCI
	PCIBIOS_MIN_IO = 0x9000;
	रेजिस्टर_pci_controller(&sni_controller);
#पूर्ण_अगर
	sni_pcimt_resource_init();
पूर्ण

अटल पूर्णांक __init snirm_pcimt_setup_devinit(व्योम)
अणु
	चयन (sni_brd_type) अणु
	हाल SNI_BRD_PCI_MTOWER:
	हाल SNI_BRD_PCI_DESKTOP:
	हाल SNI_BRD_PCI_MTOWER_CPLUS:
		platक्रमm_device_रेजिस्टर(&pcimt_serial8250_device);
		platक्रमm_device_रेजिस्टर(&pcimt_cmos_device);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

device_initcall(snirm_pcimt_setup_devinit);
