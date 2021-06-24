<शैली गुरु>
/*
 * linux/arch/mips/txx9/pci.c
 *
 * Based on linux/arch/mips/txx9/rbtx4927/setup.c,
 *	    linux/arch/mips/txx9/rbtx4938/setup.c,
 *	    and RBTX49xx patch from CELF patch archive.
 *
 * Copyright 2001-2005 MontaVista Software Inc.
 * Copyright (C) 1996, 97, 2001, 04  Ralf Baechle (ralf@linux-mips.org)
 * (C) Copyright TOSHIBA CORPORATION 2000-2001, 2004-2007
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */
#समावेश <linux/delay.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/txx9/generic.h>
#समावेश <यंत्र/txx9/pci.h>
#अगर_घोषित CONFIG_TOSHIBA_FPCIB0
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/i8259.h>
#समावेश <यंत्र/txx9/smsc_fdc37m81x.h>
#पूर्ण_अगर

अटल पूर्णांक __init
early_पढ़ो_config_word(काष्ठा pci_controller *hose,
		       पूर्णांक top_bus, पूर्णांक bus, पूर्णांक devfn, पूर्णांक offset, u16 *value)
अणु
	काष्ठा pci_bus fake_bus;

	fake_bus.number = bus;
	fake_bus.sysdata = hose;
	fake_bus.ops = hose->pci_ops;

	अगर (bus != top_bus)
		/* Fake a parent bus काष्ठाure. */
		fake_bus.parent = &fake_bus;
	अन्यथा
		fake_bus.parent = शून्य;

	वापस pci_bus_पढ़ो_config_word(&fake_bus, devfn, offset, value);
पूर्ण

पूर्णांक __init txx9_pci66_check(काष्ठा pci_controller *hose, पूर्णांक top_bus,
			    पूर्णांक current_bus)
अणु
	u32 pci_devfn;
	अचिन्हित लघु vid;
	पूर्णांक cap66 = -1;
	u16 stat;

	/* It seems SLC90E66 needs some समय after PCI reset... */
	mdelay(80);

	pr_info("PCI: Checking 66MHz capabilities...\n");

	क्रम (pci_devfn = 0; pci_devfn < 0xff; pci_devfn++) अणु
		अगर (PCI_FUNC(pci_devfn))
			जारी;
		अगर (early_पढ़ो_config_word(hose, top_bus, current_bus,
					   pci_devfn, PCI_VENDOR_ID, &vid) !=
		    PCIBIOS_SUCCESSFUL)
			जारी;
		अगर (vid == 0xffff)
			जारी;

		/* check 66MHz capability */
		अगर (cap66 < 0)
			cap66 = 1;
		अगर (cap66) अणु
			early_पढ़ो_config_word(hose, top_bus, current_bus,
					       pci_devfn, PCI_STATUS, &stat);
			अगर (!(stat & PCI_STATUS_66MHZ)) अणु
				pr_debug("PCI: %02x:%02x not 66MHz capable.\n",
					 current_bus, pci_devfn);
				cap66 = 0;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस cap66 > 0;
पूर्ण

अटल काष्ठा resource primary_pci_mem_res[2] = अणु
	अणु .name = "PCI MEM" पूर्ण,
	अणु .name = "PCI MMIO" पूर्ण,
पूर्ण;
अटल काष्ठा resource primary_pci_io_res = अणु .name = "PCI IO" पूर्ण;
काष्ठा pci_controller txx9_primary_pcic = अणु
	.mem_resource = &primary_pci_mem_res[0],
	.io_resource = &primary_pci_io_res,
पूर्ण;

#अगर_घोषित CONFIG_64BIT
पूर्णांक txx9_pci_mem_high __initdata = 1;
#अन्यथा
पूर्णांक txx9_pci_mem_high __initdata;
#पूर्ण_अगर

/*
 * allocate pci_controller and resources.
 * mem_base, io_base: physical address.	 0 क्रम स्वतः assignment.
 * mem_size and io_size means max size on स्वतः assignment.
 * pcic must be &txx9_primary_pcic or शून्य.
 */
काष्ठा pci_controller *__init
txx9_alloc_pci_controller(काष्ठा pci_controller *pcic,
			  अचिन्हित दीर्घ mem_base, अचिन्हित दीर्घ mem_size,
			  अचिन्हित दीर्घ io_base, अचिन्हित दीर्घ io_size)
अणु
	काष्ठा pcic अणु
		काष्ठा pci_controller c;
		काष्ठा resource r_mem[2];
		काष्ठा resource r_io;
	पूर्ण *new = शून्य;
	पूर्णांक min_size = 0x10000;

	अगर (!pcic) अणु
		new = kzalloc(माप(*new), GFP_KERNEL);
		अगर (!new)
			वापस शून्य;
		new->r_mem[0].name = "PCI mem";
		new->r_mem[1].name = "PCI mmio";
		new->r_io.name = "PCI io";
		new->c.mem_resource = new->r_mem;
		new->c.io_resource = &new->r_io;
		pcic = &new->c;
	पूर्ण अन्यथा
		BUG_ON(pcic != &txx9_primary_pcic);
	pcic->io_resource->flags = IORESOURCE_IO;

	/*
	 * क्रम स्वतः assignment, first search a (big) region क्रम PCI
	 * MEM, then search a region क्रम PCI IO.
	 */
	अगर (mem_base) अणु
		pcic->mem_resource[0].start = mem_base;
		pcic->mem_resource[0].end = mem_base + mem_size - 1;
		अगर (request_resource(&iomem_resource, &pcic->mem_resource[0]))
			जाओ मुक्त_and_निकास;
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ min = 0, max = 0x20000000; /* low 512MB */
		अगर (!mem_size) अणु
			/* शेष size क्रम स्वतः assignment */
			अगर (txx9_pci_mem_high)
				mem_size = 0x20000000;	/* mem:512M(max) */
			अन्यथा
				mem_size = 0x08000000;	/* mem:128M(max) */
		पूर्ण
		अगर (txx9_pci_mem_high) अणु
			min = 0x20000000;
			max = 0xe0000000;
		पूर्ण
		/* search मुक्त region क्रम PCI MEM */
		क्रम (; mem_size >= min_size; mem_size /= 2) अणु
			अगर (allocate_resource(&iomem_resource,
					      &pcic->mem_resource[0],
					      mem_size, min, max,
					      mem_size, शून्य, शून्य) == 0)
				अवरोध;
		पूर्ण
		अगर (mem_size < min_size)
			जाओ मुक्त_and_निकास;
	पूर्ण

	pcic->mem_resource[1].flags = IORESOURCE_MEM | IORESOURCE_BUSY;
	अगर (io_base) अणु
		pcic->mem_resource[1].start = io_base;
		pcic->mem_resource[1].end = io_base + io_size - 1;
		अगर (request_resource(&iomem_resource, &pcic->mem_resource[1]))
			जाओ release_and_निकास;
	पूर्ण अन्यथा अणु
		अगर (!io_size)
			/* शेष size क्रम स्वतः assignment */
			io_size = 0x01000000;	/* io:16M(max) */
		/* search मुक्त region क्रम PCI IO in low 512MB */
		क्रम (; io_size >= min_size; io_size /= 2) अणु
			अगर (allocate_resource(&iomem_resource,
					      &pcic->mem_resource[1],
					      io_size, 0, 0x20000000,
					      io_size, शून्य, शून्य) == 0)
				अवरोध;
		पूर्ण
		अगर (io_size < min_size)
			जाओ release_and_निकास;
		io_base = pcic->mem_resource[1].start;
	पूर्ण

	pcic->mem_resource[0].flags = IORESOURCE_MEM;
	अगर (pcic == &txx9_primary_pcic &&
	    mips_io_port_base == (अचिन्हित दीर्घ)-1) अणु
		/* map ioport 0 to PCI I/O space address 0 */
		set_io_port_base(IO_BASE + pcic->mem_resource[1].start);
		pcic->io_resource->start = 0;
		pcic->io_offset = 0;	/* busaddr == ioaddr */
		pcic->io_map_base = IO_BASE + pcic->mem_resource[1].start;
	पूर्ण अन्यथा अणु
		/* physaddr to ioaddr */
		pcic->io_resource->start =
			io_base - (mips_io_port_base - IO_BASE);
		pcic->io_offset = io_base - (mips_io_port_base - IO_BASE);
		pcic->io_map_base = mips_io_port_base;
	पूर्ण
	pcic->io_resource->end = pcic->io_resource->start + io_size - 1;

	pcic->mem_offset = 0;	/* busaddr == physaddr */

	pr_info("PCI: IO %pR MEM %pR\n", &pcic->mem_resource[1],
		&pcic->mem_resource[0]);

	/* रेजिस्टर_pci_controller() will request MEM resource */
	release_resource(&pcic->mem_resource[0]);
	वापस pcic;
 release_and_निकास:
	release_resource(&pcic->mem_resource[0]);
 मुक्त_and_निकास:
	kमुक्त(new);
	pr_err("PCI: Failed to allocate resources.\n");
	वापस शून्य;
पूर्ण

अटल पूर्णांक __init
txx9_arch_pci_init(व्योम)
अणु
	PCIBIOS_MIN_IO = 0x8000;	/* reseve legacy I/O space */
	वापस 0;
पूर्ण
arch_initcall(txx9_arch_pci_init);

/* IRQ/IDSEL mapping */
पूर्णांक txx9_pci_option =
#अगर_घोषित CONFIG_PICMG_PCI_BACKPLANE_DEFAULT
	TXX9_PCI_OPT_PICMG |
#पूर्ण_अगर
	TXX9_PCI_OPT_CLK_AUTO;

क्रमागत txx9_pci_err_action txx9_pci_err_action = TXX9_PCI_ERR_REPORT;

#अगर_घोषित CONFIG_TOSHIBA_FPCIB0
अटल irqवापस_t i8259_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	पूर्णांक isairq;

	isairq = i8259_irq();
	अगर (unlikely(isairq <= I8259A_IRQ_BASE))
		वापस IRQ_NONE;
	generic_handle_irq(isairq);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक txx9_i8259_irq_setup(पूर्णांक irq)
अणु
	पूर्णांक err;

	init_i8259_irqs();
	err = request_irq(irq, &i8259_पूर्णांकerrupt, IRQF_SHARED,
			  "cascade(i8259)", (व्योम *)(दीर्घ)irq);
	अगर (!err)
		pr_info("PCI-ISA bridge PIC (irq %d)\n", irq);
	वापस err;
पूर्ण

अटल व्योम __ref quirk_slc90e66_bridge(काष्ठा pci_dev *dev)
अणु
	पूर्णांक irq;	/* PCI/ISA Bridge पूर्णांकerrupt */
	u8 reg_64;
	u32 reg_b0;
	u8 reg_e1;
	irq = pcibios_map_irq(dev, PCI_SLOT(dev->devfn), 1); /* INTA */
	अगर (!irq)
		वापस;
	txx9_i8259_irq_setup(irq);
	pci_पढ़ो_config_byte(dev, 0x64, &reg_64);
	pci_पढ़ो_config_dword(dev, 0xb0, &reg_b0);
	pci_पढ़ो_config_byte(dev, 0xe1, &reg_e1);
	/* serial irq control */
	reg_64 = 0xd0;
	/* serial irq pin */
	reg_b0 |= 0x00010000;
	/* ide irq on isa14 */
	reg_e1 &= 0xf0;
	reg_e1 |= 0x0d;
	pci_ग_लिखो_config_byte(dev, 0x64, reg_64);
	pci_ग_लिखो_config_dword(dev, 0xb0, reg_b0);
	pci_ग_लिखो_config_byte(dev, 0xe1, reg_e1);

	smsc_fdc37m81x_init(0x3f0);
	smsc_fdc37m81x_config_beg();
	smsc_fdc37m81x_config_set(SMSC_FDC37M81X_DNUM,
				  SMSC_FDC37M81X_KBD);
	smsc_fdc37m81x_config_set(SMSC_FDC37M81X_INT, 1);
	smsc_fdc37m81x_config_set(SMSC_FDC37M81X_INT2, 12);
	smsc_fdc37m81x_config_set(SMSC_FDC37M81X_ACTIVE,
				  1);
	smsc_fdc37m81x_config_end();
पूर्ण

अटल व्योम quirk_slc90e66_ide(काष्ठा pci_dev *dev)
अणु
	अचिन्हित अक्षर dat;
	पूर्णांक regs[2] = अणु0x41, 0x43पूर्ण;
	पूर्णांक i;

	/* SMSC SLC90E66 IDE uses irq 14, 15 (शेष) */
	pci_ग_लिखो_config_byte(dev, PCI_INTERRUPT_LINE, 14);
	pci_पढ़ो_config_byte(dev, PCI_INTERRUPT_LINE, &dat);
	pr_info("PCI: %s: IRQ %02x", pci_name(dev), dat);
	/* enable SMSC SLC90E66 IDE */
	क्रम (i = 0; i < ARRAY_SIZE(regs); i++) अणु
		pci_पढ़ो_config_byte(dev, regs[i], &dat);
		pci_ग_लिखो_config_byte(dev, regs[i], dat | 0x80);
		pci_पढ़ो_config_byte(dev, regs[i], &dat);
		pr_cont(" IDETIM%d %02x", i, dat);
	पूर्ण
	pci_पढ़ो_config_byte(dev, 0x5c, &dat);
	/*
	 * !!! DO NOT REMOVE THIS COMMENT IT IS REQUIRED BY SMSC !!!
	 *
	 * This line of code is पूर्णांकended to provide the user with a work
	 * around solution to the anomalies cited in SMSC's anomaly sheet
	 * entitled, "SLC90E66 Functional Rev.J_0.1 Anomalies"".
	 *
	 * !!! DO NOT REMOVE THIS COMMENT IT IS REQUIRED BY SMSC !!!
	 */
	dat |= 0x01;
	pci_ग_लिखो_config_byte(dev, 0x5c, dat);
	pci_पढ़ो_config_byte(dev, 0x5c, &dat);
	pr_cont(" REG5C %02x\n", dat);
पूर्ण
#पूर्ण_अगर /* CONFIG_TOSHIBA_FPCIB0 */

अटल व्योम tc35815_fixup(काष्ठा pci_dev *dev)
अणु
	/* This device may have PM रेजिस्टरs but not they are not supported. */
	अगर (dev->pm_cap) अणु
		dev_info(&dev->dev, "PM disabled\n");
		dev->pm_cap = 0;
	पूर्ण
पूर्ण

अटल व्योम final_fixup(काष्ठा pci_dev *dev)
अणु
	अचिन्हित अक्षर bist;

	/* Do build-in self test */
	अगर (pci_पढ़ो_config_byte(dev, PCI_BIST, &bist) == PCIBIOS_SUCCESSFUL &&
	    (bist & PCI_BIST_CAPABLE)) अणु
		अचिन्हित दीर्घ समयout;
		pci_set_घातer_state(dev, PCI_D0);
		pr_info("PCI: %s BIST...", pci_name(dev));
		pci_ग_लिखो_config_byte(dev, PCI_BIST, PCI_BIST_START);
		समयout = jअगरfies + HZ * 2;	/* समयout after 2 sec */
		करो अणु
			pci_पढ़ो_config_byte(dev, PCI_BIST, &bist);
			अगर (समय_after(jअगरfies, समयout))
				अवरोध;
		पूर्ण जबतक (bist & PCI_BIST_START);
		अगर (bist & (PCI_BIST_CODE_MASK | PCI_BIST_START))
			pr_cont("failed. (0x%x)\n", bist);
		अन्यथा
			pr_cont("OK.\n");
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_TOSHIBA_FPCIB0
#घोषणा PCI_DEVICE_ID_EFAR_SLC90E66_0 0x9460
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_EFAR, PCI_DEVICE_ID_EFAR_SLC90E66_0,
	quirk_slc90e66_bridge);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_EFAR, PCI_DEVICE_ID_EFAR_SLC90E66_1,
	quirk_slc90e66_ide);
DECLARE_PCI_FIXUP_RESUME(PCI_VENDOR_ID_EFAR, PCI_DEVICE_ID_EFAR_SLC90E66_1,
	quirk_slc90e66_ide);
#पूर्ण_अगर
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_TOSHIBA_2,
			PCI_DEVICE_ID_TOSHIBA_TC35815_NWU, tc35815_fixup);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_TOSHIBA_2,
			PCI_DEVICE_ID_TOSHIBA_TC35815_TX4939, tc35815_fixup);
DECLARE_PCI_FIXUP_FINAL(PCI_ANY_ID, PCI_ANY_ID, final_fixup);
DECLARE_PCI_FIXUP_RESUME(PCI_ANY_ID, PCI_ANY_ID, final_fixup);

पूर्णांक pcibios_plat_dev_init(काष्ठा pci_dev *dev)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक (*txx9_pci_map_irq)(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin);
पूर्णांक pcibios_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	वापस txx9_pci_map_irq(dev, slot, pin);
पूर्ण

अक्षर * (*txx9_board_pcibios_setup)(अक्षर *str) __initdata;

अक्षर *__init txx9_pcibios_setup(अक्षर *str)
अणु
	अगर (txx9_board_pcibios_setup && !txx9_board_pcibios_setup(str))
		वापस शून्य;
	अगर (!म_भेद(str, "picmg")) अणु
		/* PICMG compliant backplane (TOSHIBA JMB-PICMG-ATX
		   (5V or 3.3V), JMB-PICMG-L2 (5V only), etc.) */
		txx9_pci_option |= TXX9_PCI_OPT_PICMG;
		वापस शून्य;
	पूर्ण अन्यथा अगर (!म_भेद(str, "nopicmg")) अणु
		/* non-PICMG compliant backplane (TOSHIBA
		   RBHBK4100,RBHBK4200, Interface PCM-PCM05, etc.) */
		txx9_pci_option &= ~TXX9_PCI_OPT_PICMG;
		वापस शून्य;
	पूर्ण अन्यथा अगर (!म_भेदन(str, "clk=", 4)) अणु
		अक्षर *val = str + 4;
		txx9_pci_option &= ~TXX9_PCI_OPT_CLK_MASK;
		अगर (म_भेद(val, "33") == 0)
			txx9_pci_option |= TXX9_PCI_OPT_CLK_33;
		अन्यथा अगर (म_भेद(val, "66") == 0)
			txx9_pci_option |= TXX9_PCI_OPT_CLK_66;
		अन्यथा /* "auto" */
			txx9_pci_option |= TXX9_PCI_OPT_CLK_AUTO;
		वापस शून्य;
	पूर्ण अन्यथा अगर (!म_भेदन(str, "err=", 4)) अणु
		अगर (!म_भेद(str + 4, "panic"))
			txx9_pci_err_action = TXX9_PCI_ERR_PANIC;
		अन्यथा अगर (!म_भेद(str + 4, "ignore"))
			txx9_pci_err_action = TXX9_PCI_ERR_IGNORE;
		वापस शून्य;
	पूर्ण

	txx9_pci_map_irq = txx9_board_vec->pci_map_irq;

	वापस str;
पूर्ण
