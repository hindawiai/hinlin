<शैली गुरु>
/*
 * PCI Tower specअगरic code
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2006 Thomas Bogenकरोerfer (tsbogend@alpha.franken.de)
 */

#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/pci.h>
#समावेश <linux/serial_8250.h>

#समावेश <यंत्र/sni.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/irq_cpu.h>


#घोषणा PORT(_base,_irq)				\
	अणु						\
		.iobase		= _base,		\
		.irq		= _irq,			\
		.uartclk	= 1843200,		\
		.iotype		= UPIO_PORT,		\
		.flags		= UPF_BOOT_AUTOCONF,	\
	पूर्ण

अटल काष्ठा plat_serial8250_port pcit_data[] = अणु
	PORT(0x3f8, 0),
	PORT(0x2f8, 3),
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device pcit_serial8250_device = अणु
	.name			= "serial8250",
	.id			= PLAT8250_DEV_PLATFORM,
	.dev			= अणु
		.platक्रमm_data	= pcit_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा plat_serial8250_port pcit_cplus_data[] = अणु
	PORT(0x3f8, 0),
	PORT(0x2f8, 3),
	PORT(0x3e8, 4),
	PORT(0x2e8, 3),
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device pcit_cplus_serial8250_device = अणु
	.name			= "serial8250",
	.id			= PLAT8250_DEV_PLATFORM,
	.dev			= अणु
		.platक्रमm_data	= pcit_cplus_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource pcit_cmos_rsrc[] = अणु
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

अटल काष्ठा platक्रमm_device pcit_cmos_device = अणु
	.name		= "rtc_cmos",
	.num_resources	= ARRAY_SIZE(pcit_cmos_rsrc),
	.resource	= pcit_cmos_rsrc
पूर्ण;

अटल काष्ठा platक्रमm_device pcit_pcspeaker_pdev = अणु
	.name		= "pcspkr",
	.id		= -1,
पूर्ण;

अटल काष्ठा resource sni_io_resource = अणु
	.start	= 0x00000000UL,
	.end	= 0x03bfffffUL,
	.name	= "PCIT IO",
	.flags	= IORESOURCE_IO,
पूर्ण;

अटल काष्ठा resource pcit_io_resources[] = अणु
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
		.start	=  0xcf8,
		.end	= 0xcfb,
		.name	= "PCI config addr",
		.flags	= IORESOURCE_BUSY
	पूर्ण, अणु
		.start	=  0xcfc,
		.end	= 0xcff,
		.name	= "PCI config data",
		.flags	= IORESOURCE_BUSY
	पूर्ण
पूर्ण;

अटल व्योम __init sni_pcit_resource_init(व्योम)
अणु
	पूर्णांक i;

	/* request I/O space क्रम devices used on all i[345]86 PCs */
	क्रम (i = 0; i < ARRAY_SIZE(pcit_io_resources); i++)
		request_resource(&sni_io_resource, pcit_io_resources + i);
पूर्ण


बाह्य काष्ठा pci_ops sni_pcit_ops;

#अगर_घोषित CONFIG_PCI
अटल काष्ठा resource sni_mem_resource = अणु
	.start	= 0x18000000UL,
	.end	= 0x1fbfffffUL,
	.name	= "PCIT PCI MEM",
	.flags	= IORESOURCE_MEM
पूर्ण;

अटल काष्ठा pci_controller sni_pcit_controller = अणु
	.pci_ops	= &sni_pcit_ops,
	.mem_resource	= &sni_mem_resource,
	.mem_offset	= 0x00000000UL,
	.io_resource	= &sni_io_resource,
	.io_offset	= 0x00000000UL,
	.io_map_base	= SNI_PORT_BASE
पूर्ण;
#पूर्ण_अगर /* CONFIG_PCI */

अटल व्योम enable_pcit_irq(काष्ठा irq_data *d)
अणु
	u32 mask = 1 << (d->irq - SNI_PCIT_INT_START + 24);

	*(अस्थिर u32 *)SNI_PCIT_INT_REG |= mask;
पूर्ण

व्योम disable_pcit_irq(काष्ठा irq_data *d)
अणु
	u32 mask = 1 << (d->irq - SNI_PCIT_INT_START + 24);

	*(अस्थिर u32 *)SNI_PCIT_INT_REG &= ~mask;
पूर्ण

अटल काष्ठा irq_chip pcit_irq_type = अणु
	.name = "PCIT",
	.irq_mask = disable_pcit_irq,
	.irq_unmask = enable_pcit_irq,
पूर्ण;

अटल व्योम pcit_hwपूर्णांक1(व्योम)
अणु
	u32 pending = *(अस्थिर u32 *)SNI_PCIT_INT_REG;
	पूर्णांक irq;

	clear_c0_status(IE_IRQ1);
	irq = ffs((pending >> 16) & 0x7f);

	अगर (likely(irq > 0))
		करो_IRQ(irq + SNI_PCIT_INT_START - 1);
	set_c0_status(IE_IRQ1);
पूर्ण

अटल व्योम pcit_hwपूर्णांक0(व्योम)
अणु
	u32 pending = *(अस्थिर u32 *)SNI_PCIT_INT_REG;
	पूर्णांक irq;

	clear_c0_status(IE_IRQ0);
	irq = ffs((pending >> 16) & 0x3f);

	अगर (likely(irq > 0))
		करो_IRQ(irq + SNI_PCIT_INT_START - 1);
	set_c0_status(IE_IRQ0);
पूर्ण

अटल व्योम sni_pcit_hwपूर्णांक(व्योम)
अणु
	u32 pending = पढ़ो_c0_cause() & पढ़ो_c0_status();

	अगर (pending & C_IRQ1)
		pcit_hwपूर्णांक1();
	अन्यथा अगर (pending & C_IRQ2)
		करो_IRQ(MIPS_CPU_IRQ_BASE + 4);
	अन्यथा अगर (pending & C_IRQ3)
		करो_IRQ(MIPS_CPU_IRQ_BASE + 5);
	अन्यथा अगर (pending & C_IRQ5)
		करो_IRQ(MIPS_CPU_IRQ_BASE + 7);
पूर्ण

अटल व्योम sni_pcit_hwपूर्णांक_cplus(व्योम)
अणु
	u32 pending = पढ़ो_c0_cause() & पढ़ो_c0_status();

	अगर (pending & C_IRQ0)
		pcit_hwपूर्णांक0();
	अन्यथा अगर (pending & C_IRQ1)
		करो_IRQ(MIPS_CPU_IRQ_BASE + 3);
	अन्यथा अगर (pending & C_IRQ2)
		करो_IRQ(MIPS_CPU_IRQ_BASE + 4);
	अन्यथा अगर (pending & C_IRQ3)
		करो_IRQ(MIPS_CPU_IRQ_BASE + 5);
	अन्यथा अगर (pending & C_IRQ5)
		करो_IRQ(MIPS_CPU_IRQ_BASE + 7);
पूर्ण

व्योम __init sni_pcit_irq_init(व्योम)
अणु
	पूर्णांक i;

	mips_cpu_irq_init();
	क्रम (i = SNI_PCIT_INT_START; i <= SNI_PCIT_INT_END; i++)
		irq_set_chip_and_handler(i, &pcit_irq_type, handle_level_irq);
	*(अस्थिर u32 *)SNI_PCIT_INT_REG = 0;
	sni_hwपूर्णांक = sni_pcit_hwपूर्णांक;
	change_c0_status(ST0_IM, IE_IRQ1);
	अगर (request_irq(SNI_PCIT_INT_START + 6, sni_isa_irq_handler, 0, "ISA",
			शून्य))
		pr_err("Failed to register ISA interrupt\n");
पूर्ण

व्योम __init sni_pcit_cplus_irq_init(व्योम)
अणु
	पूर्णांक i;

	mips_cpu_irq_init();
	क्रम (i = SNI_PCIT_INT_START; i <= SNI_PCIT_INT_END; i++)
		irq_set_chip_and_handler(i, &pcit_irq_type, handle_level_irq);
	*(अस्थिर u32 *)SNI_PCIT_INT_REG = 0x40000000;
	sni_hwपूर्णांक = sni_pcit_hwपूर्णांक_cplus;
	change_c0_status(ST0_IM, IE_IRQ0);
	अगर (request_irq(MIPS_CPU_IRQ_BASE + 3, sni_isa_irq_handler, 0, "ISA",
			शून्य))
		pr_err("Failed to register ISA interrupt\n");
पूर्ण

व्योम __init sni_pcit_init(व्योम)
अणु
	ioport_resource.end = sni_io_resource.end;
#अगर_घोषित CONFIG_PCI
	PCIBIOS_MIN_IO = 0x9000;
	रेजिस्टर_pci_controller(&sni_pcit_controller);
#पूर्ण_अगर
	sni_pcit_resource_init();
पूर्ण

अटल पूर्णांक __init snirm_pcit_setup_devinit(व्योम)
अणु
	चयन (sni_brd_type) अणु
	हाल SNI_BRD_PCI_TOWER:
		platक्रमm_device_रेजिस्टर(&pcit_serial8250_device);
		platक्रमm_device_रेजिस्टर(&pcit_cmos_device);
		platक्रमm_device_रेजिस्टर(&pcit_pcspeaker_pdev);
		अवरोध;

	हाल SNI_BRD_PCI_TOWER_CPLUS:
		platक्रमm_device_रेजिस्टर(&pcit_cplus_serial8250_device);
		platक्रमm_device_रेजिस्टर(&pcit_cmos_device);
		platक्रमm_device_रेजिस्टर(&pcit_pcspeaker_pdev);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

device_initcall(snirm_pcit_setup_devinit);
