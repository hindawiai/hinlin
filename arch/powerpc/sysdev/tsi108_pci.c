<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Common routines क्रम Tundra Semiconductor TSI108 host bridge.
 *
 * 2004-2005 (c) Tundra Semiconductor Corp.
 * Author: Alex Bounine (alexandreb@tundra.com)
 * Author: Roy Zang (tie-fei.zang@मुक्तscale.com)
 * 	   Add pci पूर्णांकerrupt router host
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/pci-bridge.h>
#समावेश <यंत्र/tsi108.h>
#समावेश <यंत्र/tsi108_pci.h>
#समावेश <यंत्र/tsi108_irq.h>
#समावेश <यंत्र/prom.h>

#अघोषित DEBUG
#अगर_घोषित DEBUG
#घोषणा DBG(x...) prपूर्णांकk(x)
#अन्यथा
#घोषणा DBG(x...)
#पूर्ण_अगर

#घोषणा tsi_mk_config_addr(bus, devfunc, offset) \
	((((bus)<<16) | ((devfunc)<<8) | (offset & 0xfc)) + tsi108_pci_cfg_base)

u32 tsi108_pci_cfg_base;
अटल u32 tsi108_pci_cfg_phys;
u32 tsi108_csr_vir_base;
अटल काष्ठा irq_करोमुख्य *pci_irq_host;

बाह्य u32 get_vir_csrbase(व्योम);
बाह्य u32 tsi108_पढ़ो_reg(u32 reg_offset);
बाह्य व्योम tsi108_ग_लिखो_reg(u32 reg_offset, u32 val);

पूर्णांक
tsi108_direct_ग_लिखो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfunc,
			   पूर्णांक offset, पूर्णांक len, u32 val)
अणु
	अस्थिर अचिन्हित अक्षर *cfg_addr;
	काष्ठा pci_controller *hose = pci_bus_to_host(bus);

	अगर (ppc_md.pci_exclude_device)
		अगर (ppc_md.pci_exclude_device(hose, bus->number, devfunc))
			वापस PCIBIOS_DEVICE_NOT_FOUND;

	cfg_addr = (अचिन्हित अक्षर *)(tsi_mk_config_addr(bus->number,
							devfunc, offset) |
							(offset & 0x03));

#अगर_घोषित DEBUG
	prपूर्णांकk("PCI CFG write : ");
	prपूर्णांकk("%d:0x%x:0x%x ", bus->number, devfunc, offset);
	prपूर्णांकk("%d ADDR=0x%08x ", len, (uपूर्णांक) cfg_addr);
	prपूर्णांकk("data = 0x%08x\n", val);
#पूर्ण_अगर

	चयन (len) अणु
	हाल 1:
		out_8((u8 *) cfg_addr, val);
		अवरोध;
	हाल 2:
		out_le16((u16 *) cfg_addr, val);
		अवरोध;
	शेष:
		out_le32((u32 *) cfg_addr, val);
		अवरोध;
	पूर्ण

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

व्योम tsi108_clear_pci_error(u32 pci_cfg_base)
अणु
	u32 err_stat, err_addr, pci_stat;

	/*
	 * Quietly clear PB and PCI error flags set as result
	 * of PCI/X configuration पढ़ो requests.
	 */

	/* Read PB Error Log Registers */

	err_stat = tsi108_पढ़ो_reg(TSI108_PB_OFFSET + TSI108_PB_ERRCS);
	err_addr = tsi108_पढ़ो_reg(TSI108_PB_OFFSET + TSI108_PB_AERR);

	अगर (err_stat & TSI108_PB_ERRCS_ES) अणु
		/* Clear error flag */
		tsi108_ग_लिखो_reg(TSI108_PB_OFFSET + TSI108_PB_ERRCS,
				 TSI108_PB_ERRCS_ES);

		/* Clear पढ़ो error reported in PB_ISR */
		tsi108_ग_लिखो_reg(TSI108_PB_OFFSET + TSI108_PB_ISR,
				 TSI108_PB_ISR_PBS_RD_ERR);

		/* Clear PCI/X bus cfg errors अगर applicable */
		अगर ((err_addr & 0xFF000000) == pci_cfg_base) अणु
			pci_stat =
			    tsi108_पढ़ो_reg(TSI108_PCI_OFFSET + TSI108_PCI_CSR);
			tsi108_ग_लिखो_reg(TSI108_PCI_OFFSET + TSI108_PCI_CSR,
					 pci_stat);
		पूर्ण
	पूर्ण

	वापस;
पूर्ण

#घोषणा __tsi108_पढ़ो_pci_config(x, addr, op)		\
	__यंत्र__ __अस्थिर__(				\
		"	"op" %0,0,%1\n"		\
		"1:	eieio\n"			\
		"2:\n"					\
		".section .fixup,\"ax\"\n"		\
		"3:	li %0,-1\n"			\
		"	b 2b\n"				\
		".previous\n"				\
		EX_TABLE(1b, 3b)			\
		: "=r"(x) : "r"(addr))

पूर्णांक
tsi108_direct_पढ़ो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक offset,
			  पूर्णांक len, u32 * val)
अणु
	अस्थिर अचिन्हित अक्षर *cfg_addr;
	काष्ठा pci_controller *hose = pci_bus_to_host(bus);
	u32 temp;

	अगर (ppc_md.pci_exclude_device)
		अगर (ppc_md.pci_exclude_device(hose, bus->number, devfn))
			वापस PCIBIOS_DEVICE_NOT_FOUND;

	cfg_addr = (अचिन्हित अक्षर *)(tsi_mk_config_addr(bus->number,
							devfn,
							offset) | (offset &
								   0x03));

	चयन (len) अणु
	हाल 1:
		__tsi108_पढ़ो_pci_config(temp, cfg_addr, "lbzx");
		अवरोध;
	हाल 2:
		__tsi108_पढ़ो_pci_config(temp, cfg_addr, "lhbrx");
		अवरोध;
	शेष:
		__tsi108_पढ़ो_pci_config(temp, cfg_addr, "lwbrx");
		अवरोध;
	पूर्ण

	*val = temp;

#अगर_घोषित DEBUG
	अगर ((0xFFFFFFFF != temp) && (0xFFFF != temp) && (0xFF != temp)) अणु
		prपूर्णांकk("PCI CFG read : ");
		prपूर्णांकk("%d:0x%x:0x%x ", bus->number, devfn, offset);
		prपूर्णांकk("%d ADDR=0x%08x ", len, (uपूर्णांक) cfg_addr);
		prपूर्णांकk("data = 0x%x\n", *val);
	पूर्ण
#पूर्ण_अगर
	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

व्योम tsi108_clear_pci_cfg_error(व्योम)
अणु
	tsi108_clear_pci_error(tsi108_pci_cfg_phys);
पूर्ण

अटल काष्ठा pci_ops tsi108_direct_pci_ops = अणु
	.पढ़ो = tsi108_direct_पढ़ो_config,
	.ग_लिखो = tsi108_direct_ग_लिखो_config,
पूर्ण;

पूर्णांक __init tsi108_setup_pci(काष्ठा device_node *dev, u32 cfg_phys, पूर्णांक primary)
अणु
	पूर्णांक len;
	काष्ठा pci_controller *hose;
	काष्ठा resource rsrc;
	स्थिर पूर्णांक *bus_range;
	पूर्णांक has_address = 0;

	/* PCI Config mapping */
	tsi108_pci_cfg_base = (u32)ioremap(cfg_phys, TSI108_PCI_CFG_SIZE);
	tsi108_pci_cfg_phys = cfg_phys;
	DBG("TSI_PCI: %s tsi108_pci_cfg_base=0x%x\n", __func__,
	    tsi108_pci_cfg_base);

	/* Fetch host bridge रेजिस्टरs address */
	has_address = (of_address_to_resource(dev, 0, &rsrc) == 0);

	/* Get bus range अगर any */
	bus_range = of_get_property(dev, "bus-range", &len);
	अगर (bus_range == शून्य || len < 2 * माप(पूर्णांक)) अणु
		prपूर्णांकk(KERN_WARNING "Can't get bus-range for %pOF, assume"
		       " bus 0\n", dev);
	पूर्ण

	hose = pcibios_alloc_controller(dev);

	अगर (!hose) अणु
		prपूर्णांकk("PCI Host bridge init failed\n");
		वापस -ENOMEM;
	पूर्ण

	hose->first_busno = bus_range ? bus_range[0] : 0;
	hose->last_busno = bus_range ? bus_range[1] : 0xff;

	(hose)->ops = &tsi108_direct_pci_ops;

	prपूर्णांकk(KERN_INFO "Found tsi108 PCI host bridge at 0x%08x. "
	       "Firmware bus number: %d->%d\n",
	       rsrc.start, hose->first_busno, hose->last_busno);

	/* Interpret the "ranges" property */
	/* This also maps the I/O region and sets isa_io/mem_base */
	pci_process_bridge_OF_ranges(hose, dev, primary);
	वापस 0;
पूर्ण

/*
 * Low level utility functions
 */

अटल व्योम tsi108_pci_पूर्णांक_mask(u_पूर्णांक irq)
अणु
	u_पूर्णांक irp_cfg;
	पूर्णांक पूर्णांक_line = (irq - IRQ_PCI_INTAD_BASE);

	irp_cfg = tsi108_पढ़ो_reg(TSI108_PCI_OFFSET + TSI108_PCI_IRP_CFG_CTL);
	mb();
	irp_cfg |= (1 << पूर्णांक_line);	/* INTx_सूची = output */
	irp_cfg &= ~(3 << (8 + (पूर्णांक_line * 2)));	/* INTx_TYPE = unused */
	tsi108_ग_लिखो_reg(TSI108_PCI_OFFSET + TSI108_PCI_IRP_CFG_CTL, irp_cfg);
	mb();
	irp_cfg = tsi108_पढ़ो_reg(TSI108_PCI_OFFSET + TSI108_PCI_IRP_CFG_CTL);
पूर्ण

अटल व्योम tsi108_pci_पूर्णांक_unmask(u_पूर्णांक irq)
अणु
	u_पूर्णांक irp_cfg;
	पूर्णांक पूर्णांक_line = (irq - IRQ_PCI_INTAD_BASE);

	irp_cfg = tsi108_पढ़ो_reg(TSI108_PCI_OFFSET + TSI108_PCI_IRP_CFG_CTL);
	mb();
	irp_cfg &= ~(1 << पूर्णांक_line);
	irp_cfg |= (3 << (8 + (पूर्णांक_line * 2)));
	tsi108_ग_लिखो_reg(TSI108_PCI_OFFSET + TSI108_PCI_IRP_CFG_CTL, irp_cfg);
	mb();
पूर्ण

अटल व्योम init_pci_source(व्योम)
अणु
	tsi108_ग_लिखो_reg(TSI108_PCI_OFFSET + TSI108_PCI_IRP_CFG_CTL,
			0x0000ff00);
	tsi108_ग_लिखो_reg(TSI108_PCI_OFFSET + TSI108_PCI_IRP_ENABLE,
			TSI108_PCI_IRP_ENABLE_P_INT);
	mb();
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक get_pci_source(व्योम)
अणु
	u_पूर्णांक temp = 0;
	पूर्णांक irq = -1;
	पूर्णांक i;
	u_पूर्णांक pci_irp_stat;
	अटल पूर्णांक mask = 0;

	/* Read PCI/X block पूर्णांकerrupt status रेजिस्टर */
	pci_irp_stat = tsi108_पढ़ो_reg(TSI108_PCI_OFFSET + TSI108_PCI_IRP_STAT);
	mb();

	अगर (pci_irp_stat & TSI108_PCI_IRP_STAT_P_INT) अणु
		/* Process Interrupt from PCI bus INTA# - INTD# lines */
		temp =
		    tsi108_पढ़ो_reg(TSI108_PCI_OFFSET +
				    TSI108_PCI_IRP_INTAD) & 0xf;
		mb();
		क्रम (i = 0; i < 4; i++, mask++) अणु
			अगर (temp & (1 << mask % 4)) अणु
				irq = IRQ_PCI_INTA + mask % 4;
				mask++;
				अवरोध;
			पूर्ण
		पूर्ण

		/* Disable पूर्णांकerrupts from PCI block */
		temp = tsi108_पढ़ो_reg(TSI108_PCI_OFFSET + TSI108_PCI_IRP_ENABLE);
		tsi108_ग_लिखो_reg(TSI108_PCI_OFFSET + TSI108_PCI_IRP_ENABLE,
				temp & ~TSI108_PCI_IRP_ENABLE_P_INT);
		mb();
		(व्योम)tsi108_पढ़ो_reg(TSI108_PCI_OFFSET + TSI108_PCI_IRP_ENABLE);
		mb();
	पूर्ण
#अगर_घोषित DEBUG
	अन्यथा अणु
		prपूर्णांकk("TSI108_PIC: error in TSI108_PCI_IRP_STAT\n");
		pci_irp_stat =
		    tsi108_पढ़ो_reg(TSI108_PCI_OFFSET + TSI108_PCI_IRP_STAT);
		temp =
		    tsi108_पढ़ो_reg(TSI108_PCI_OFFSET + TSI108_PCI_IRP_INTAD);
		mb();
		prपूर्णांकk(">> stat=0x%08x intad=0x%08x ", pci_irp_stat, temp);
		temp =
		    tsi108_पढ़ो_reg(TSI108_PCI_OFFSET + TSI108_PCI_IRP_CFG_CTL);
		mb();
		prपूर्णांकk("cfg_ctl=0x%08x ", temp);
		temp =
		    tsi108_पढ़ो_reg(TSI108_PCI_OFFSET + TSI108_PCI_IRP_ENABLE);
		mb();
		prपूर्णांकk("irp_enable=0x%08x\n", temp);
	पूर्ण
#पूर्ण_अगर	/* end of DEBUG */

	वापस irq;
पूर्ण


/*
 * Linux descriptor level callbacks
 */

अटल व्योम tsi108_pci_irq_unmask(काष्ठा irq_data *d)
अणु
	tsi108_pci_पूर्णांक_unmask(d->irq);

	/* Enable पूर्णांकerrupts from PCI block */
	tsi108_ग_लिखो_reg(TSI108_PCI_OFFSET + TSI108_PCI_IRP_ENABLE,
			 tsi108_पढ़ो_reg(TSI108_PCI_OFFSET +
					 TSI108_PCI_IRP_ENABLE) |
			 TSI108_PCI_IRP_ENABLE_P_INT);
	mb();
पूर्ण

अटल व्योम tsi108_pci_irq_mask(काष्ठा irq_data *d)
अणु
	tsi108_pci_पूर्णांक_mask(d->irq);
पूर्ण

अटल व्योम tsi108_pci_irq_ack(काष्ठा irq_data *d)
अणु
	tsi108_pci_पूर्णांक_mask(d->irq);
पूर्ण

/*
 * Interrupt controller descriptor क्रम cascaded PCI पूर्णांकerrupt controller.
 */

अटल काष्ठा irq_chip tsi108_pci_irq = अणु
	.name = "tsi108_PCI_int",
	.irq_mask = tsi108_pci_irq_mask,
	.irq_ack = tsi108_pci_irq_ack,
	.irq_unmask = tsi108_pci_irq_unmask,
पूर्ण;

अटल पूर्णांक pci_irq_host_xlate(काष्ठा irq_करोमुख्य *h, काष्ठा device_node *ct,
			    स्थिर u32 *पूर्णांकspec, अचिन्हित पूर्णांक पूर्णांकsize,
			    irq_hw_number_t *out_hwirq, अचिन्हित पूर्णांक *out_flags)
अणु
	*out_hwirq = पूर्णांकspec[0];
	*out_flags = IRQ_TYPE_LEVEL_HIGH;
	वापस 0;
पूर्ण

अटल पूर्णांक pci_irq_host_map(काष्ठा irq_करोमुख्य *h, अचिन्हित पूर्णांक virq,
			  irq_hw_number_t hw)
अणु	अचिन्हित पूर्णांक irq;
	DBG("%s(%d, 0x%lx)\n", __func__, virq, hw);
	अगर ((virq >= 1) && (virq <= 4))अणु
		irq = virq + IRQ_PCI_INTAD_BASE - 1;
		irq_set_status_flags(irq, IRQ_LEVEL);
		irq_set_chip(irq, &tsi108_pci_irq);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops pci_irq_करोमुख्य_ops = अणु
	.map = pci_irq_host_map,
	.xlate = pci_irq_host_xlate,
पूर्ण;

/*
 * Exported functions
 */

/*
 * The Tsi108 PCI पूर्णांकerrupts initialization routine.
 *
 * The INTA# - INTD# पूर्णांकerrupts on the PCI bus are reported by the PCI block
 * to the MPIC using single पूर्णांकerrupt source (IRQ_TSI108_PCI). Thereक्रमe the
 * PCI block has to be treated as a cascaded पूर्णांकerrupt controller connected
 * to the MPIC.
 */

व्योम __init tsi108_pci_पूर्णांक_init(काष्ठा device_node *node)
अणु
	DBG("Tsi108_pci_int_init: initializing PCI interrupts\n");

	pci_irq_host = irq_करोमुख्य_add_legacy_isa(node, &pci_irq_करोमुख्य_ops, शून्य);
	अगर (pci_irq_host == शून्य) अणु
		prपूर्णांकk(KERN_ERR "pci_irq_host: failed to allocate irq domain!\n");
		वापस;
	पूर्ण

	init_pci_source();
पूर्ण

व्योम tsi108_irq_cascade(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	अचिन्हित पूर्णांक cascade_irq = get_pci_source();

	अगर (cascade_irq)
		generic_handle_irq(cascade_irq);

	chip->irq_eoi(&desc->irq_data);
पूर्ण
