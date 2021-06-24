<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2003 Christoph Hellwig (hch@lst.de)
 * Copyright (C) 1999, 2000, 04 Ralf Baechle (ralf@linux-mips.org)
 * Copyright (C) 1999, 2000 Silicon Graphics, Inc.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/pci.h>
#समावेश <linux/smp.h>
#समावेश <linux/dma-direct.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/platक्रमm_data/xtalk-bridge.h>
#समावेश <linux/nvmem-consumer.h>
#समावेश <linux/crc16.h>

#समावेश <यंत्र/pci/bridge.h>
#समावेश <यंत्र/paccess.h>
#समावेश <यंत्र/sn/irq_भाग.स>
#समावेश <यंत्र/sn/ioc3.h>

#घोषणा CRC16_INIT	0
#घोषणा CRC16_VALID	0xb001

/*
 * Common phys<->dma mapping क्रम platक्रमms using pci xtalk bridge
 */
dma_addr_t phys_to_dma(काष्ठा device *dev, phys_addr_t paddr)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा bridge_controller *bc = BRIDGE_CONTROLLER(pdev->bus);

	वापस bc->baddr + paddr;
पूर्ण

phys_addr_t dma_to_phys(काष्ठा device *dev, dma_addr_t dma_addr)
अणु
	वापस dma_addr & ~(0xffUL << 56);
पूर्ण

/*
 * Most of the IOC3 PCI config रेजिस्टर aren't present
 * we emulate what is needed क्रम a normal PCI क्रमागतeration
 */
अटल पूर्णांक ioc3_cfg_rd(व्योम *addr, पूर्णांक where, पूर्णांक size, u32 *value, u32 sid)
अणु
	u32 cf, shअगरt, mask;

	चयन (where & ~3) अणु
	हाल 0x00 ... 0x10:
	हाल 0x40 ... 0x44:
		अगर (get_dbe(cf, (u32 *)addr))
			वापस PCIBIOS_DEVICE_NOT_FOUND;
		अवरोध;
	हाल 0x2c:
		cf = sid;
		अवरोध;
	हाल 0x3c:
		/* emulate sane पूर्णांकerrupt pin value */
		cf = 0x00000100;
		अवरोध;
	शेष:
		cf = 0;
		अवरोध;
	पूर्ण
	shअगरt = (where & 3) << 3;
	mask = 0xffffffffU >> ((4 - size) << 3);
	*value = (cf >> shअगरt) & mask;

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक ioc3_cfg_wr(व्योम *addr, पूर्णांक where, पूर्णांक size, u32 value)
अणु
	u32 cf, shअगरt, mask, smask;

	अगर ((where >= 0x14 && where < 0x40) || (where >= 0x48))
		वापस PCIBIOS_SUCCESSFUL;

	अगर (get_dbe(cf, (u32 *)addr))
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	shअगरt = ((where & 3) << 3);
	mask = (0xffffffffU >> ((4 - size) << 3));
	smask = mask << shअगरt;

	cf = (cf & ~smask) | ((value & mask) << shअगरt);
	अगर (put_dbe(cf, (u32 *)addr))
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल व्योम bridge_disable_swapping(काष्ठा pci_dev *dev)
अणु
	काष्ठा bridge_controller *bc = BRIDGE_CONTROLLER(dev->bus);
	पूर्णांक slot = PCI_SLOT(dev->devfn);

	/* Turn off byte swapping */
	bridge_clr(bc, b_device[slot].reg, BRIDGE_DEV_SWAP_सूची);
	bridge_पढ़ो(bc, b_widget.w_tflush);	/* Flush */
पूर्ण

DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_SGI, PCI_DEVICE_ID_SGI_IOC3,
	bridge_disable_swapping);


/*
 * The Bridge ASIC supports both type 0 and type 1 access.  Type 1 is
 * not really करोcumented, so right now I can't ग_लिखो code which uses it.
 * Thereक्रमe we use type 0 accesses क्रम now even though they won't work
 * correctly क्रम PCI-to-PCI bridges.
 *
 * The function is complicated by the ultimate brokenness of the IOC3 chip
 * which is used in SGI प्रणालीs.  The IOC3 can only handle 32-bit PCI
 * accesses and करोes only decode parts of it's address space.
 */
अटल पूर्णांक pci_conf0_पढ़ो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				 पूर्णांक where, पूर्णांक size, u32 *value)
अणु
	काष्ठा bridge_controller *bc = BRIDGE_CONTROLLER(bus);
	काष्ठा bridge_regs *bridge = bc->base;
	पूर्णांक slot = PCI_SLOT(devfn);
	पूर्णांक fn = PCI_FUNC(devfn);
	व्योम *addr;
	u32 cf;
	पूर्णांक res;

	addr = &bridge->b_type0_cfg_dev[slot].f[fn].c[PCI_VENDOR_ID];
	अगर (get_dbe(cf, (u32 *)addr))
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	/*
	 * IOC3 is broken beyond belief ...  Don't even give the
	 * generic PCI code a chance to look at it क्रम real ...
	 */
	अगर (cf == (PCI_VENDOR_ID_SGI | (PCI_DEVICE_ID_SGI_IOC3 << 16))) अणु
		addr = &bridge->b_type0_cfg_dev[slot].f[fn].l[where >> 2];
		वापस ioc3_cfg_rd(addr, where, size, value,
				   bc->ioc3_sid[slot]);
	पूर्ण

	addr = &bridge->b_type0_cfg_dev[slot].f[fn].c[where ^ (4 - size)];

	अगर (size == 1)
		res = get_dbe(*value, (u8 *)addr);
	अन्यथा अगर (size == 2)
		res = get_dbe(*value, (u16 *)addr);
	अन्यथा
		res = get_dbe(*value, (u32 *)addr);

	वापस res ? PCIBIOS_DEVICE_NOT_FOUND : PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक pci_conf1_पढ़ो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				 पूर्णांक where, पूर्णांक size, u32 *value)
अणु
	काष्ठा bridge_controller *bc = BRIDGE_CONTROLLER(bus);
	काष्ठा bridge_regs *bridge = bc->base;
	पूर्णांक busno = bus->number;
	पूर्णांक slot = PCI_SLOT(devfn);
	पूर्णांक fn = PCI_FUNC(devfn);
	व्योम *addr;
	u32 cf;
	पूर्णांक res;

	bridge_ग_लिखो(bc, b_pci_cfg, (busno << 16) | (slot << 11));
	addr = &bridge->b_type1_cfg.c[(fn << 8) | PCI_VENDOR_ID];
	अगर (get_dbe(cf, (u32 *)addr))
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	/*
	 * IOC3 is broken beyond belief ...  Don't even give the
	 * generic PCI code a chance to look at it क्रम real ...
	 */
	अगर (cf == (PCI_VENDOR_ID_SGI | (PCI_DEVICE_ID_SGI_IOC3 << 16))) अणु
		addr = &bridge->b_type1_cfg.c[(fn << 8) | (where & ~3)];
		वापस ioc3_cfg_rd(addr, where, size, value,
				   bc->ioc3_sid[slot]);
	पूर्ण

	addr = &bridge->b_type1_cfg.c[(fn << 8) | (where ^ (4 - size))];

	अगर (size == 1)
		res = get_dbe(*value, (u8 *)addr);
	अन्यथा अगर (size == 2)
		res = get_dbe(*value, (u16 *)addr);
	अन्यथा
		res = get_dbe(*value, (u32 *)addr);

	वापस res ? PCIBIOS_DEVICE_NOT_FOUND : PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक pci_पढ़ो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
			   पूर्णांक where, पूर्णांक size, u32 *value)
अणु
	अगर (!pci_is_root_bus(bus))
		वापस pci_conf1_पढ़ो_config(bus, devfn, where, size, value);

	वापस pci_conf0_पढ़ो_config(bus, devfn, where, size, value);
पूर्ण

अटल पूर्णांक pci_conf0_ग_लिखो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				  पूर्णांक where, पूर्णांक size, u32 value)
अणु
	काष्ठा bridge_controller *bc = BRIDGE_CONTROLLER(bus);
	काष्ठा bridge_regs *bridge = bc->base;
	पूर्णांक slot = PCI_SLOT(devfn);
	पूर्णांक fn = PCI_FUNC(devfn);
	व्योम *addr;
	u32 cf;
	पूर्णांक res;

	addr = &bridge->b_type0_cfg_dev[slot].f[fn].c[PCI_VENDOR_ID];
	अगर (get_dbe(cf, (u32 *)addr))
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	/*
	 * IOC3 is broken beyond belief ...  Don't even give the
	 * generic PCI code a chance to look at it क्रम real ...
	 */
	अगर (cf == (PCI_VENDOR_ID_SGI | (PCI_DEVICE_ID_SGI_IOC3 << 16))) अणु
		addr = &bridge->b_type0_cfg_dev[slot].f[fn].l[where >> 2];
		वापस ioc3_cfg_wr(addr, where, size, value);
	पूर्ण

	addr = &bridge->b_type0_cfg_dev[slot].f[fn].c[where ^ (4 - size)];

	अगर (size == 1)
		res = put_dbe(value, (u8 *)addr);
	अन्यथा अगर (size == 2)
		res = put_dbe(value, (u16 *)addr);
	अन्यथा
		res = put_dbe(value, (u32 *)addr);

	अगर (res)
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक pci_conf1_ग_लिखो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				  पूर्णांक where, पूर्णांक size, u32 value)
अणु
	काष्ठा bridge_controller *bc = BRIDGE_CONTROLLER(bus);
	काष्ठा bridge_regs *bridge = bc->base;
	पूर्णांक slot = PCI_SLOT(devfn);
	पूर्णांक fn = PCI_FUNC(devfn);
	पूर्णांक busno = bus->number;
	व्योम *addr;
	u32 cf;
	पूर्णांक res;

	bridge_ग_लिखो(bc, b_pci_cfg, (busno << 16) | (slot << 11));
	addr = &bridge->b_type1_cfg.c[(fn << 8) | PCI_VENDOR_ID];
	अगर (get_dbe(cf, (u32 *)addr))
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	/*
	 * IOC3 is broken beyond belief ...  Don't even give the
	 * generic PCI code a chance to look at it क्रम real ...
	 */
	अगर (cf == (PCI_VENDOR_ID_SGI | (PCI_DEVICE_ID_SGI_IOC3 << 16))) अणु
		addr = &bridge->b_type0_cfg_dev[slot].f[fn].l[where >> 2];
		वापस ioc3_cfg_wr(addr, where, size, value);
	पूर्ण

	addr = &bridge->b_type1_cfg.c[(fn << 8) | (where ^ (4 - size))];

	अगर (size == 1)
		res = put_dbe(value, (u8 *)addr);
	अन्यथा अगर (size == 2)
		res = put_dbe(value, (u16 *)addr);
	अन्यथा
		res = put_dbe(value, (u32 *)addr);

	अगर (res)
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक pci_ग_लिखो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
	पूर्णांक where, पूर्णांक size, u32 value)
अणु
	अगर (!pci_is_root_bus(bus))
		वापस pci_conf1_ग_लिखो_config(bus, devfn, where, size, value);

	वापस pci_conf0_ग_लिखो_config(bus, devfn, where, size, value);
पूर्ण

अटल काष्ठा pci_ops bridge_pci_ops = अणु
	.पढ़ो	 = pci_पढ़ो_config,
	.ग_लिखो	 = pci_ग_लिखो_config,
पूर्ण;

काष्ठा bridge_irq_chip_data अणु
	काष्ठा bridge_controller *bc;
	nasid_t nasid;
पूर्ण;

अटल पूर्णांक bridge_set_affinity(काष्ठा irq_data *d, स्थिर काष्ठा cpumask *mask,
			       bool क्रमce)
अणु
#अगर_घोषित CONFIG_NUMA
	काष्ठा bridge_irq_chip_data *data = d->chip_data;
	पूर्णांक bit = d->parent_data->hwirq;
	पूर्णांक pin = d->hwirq;
	पूर्णांक ret, cpu;

	ret = irq_chip_set_affinity_parent(d, mask, क्रमce);
	अगर (ret >= 0) अणु
		cpu = cpumask_first_and(mask, cpu_online_mask);
		data->nasid = cpu_to_node(cpu);
		bridge_ग_लिखो(data->bc, b_पूर्णांक_addr[pin].addr,
			     (((data->bc->पूर्णांकr_addr >> 30) & 0x30000) |
			      bit | (data->nasid << 8)));
		bridge_पढ़ो(data->bc, b_wid_tflush);
	पूर्ण
	वापस ret;
#अन्यथा
	वापस irq_chip_set_affinity_parent(d, mask, क्रमce);
#पूर्ण_अगर
पूर्ण

काष्ठा irq_chip bridge_irq_chip = अणु
	.name             = "BRIDGE",
	.irq_mask         = irq_chip_mask_parent,
	.irq_unmask       = irq_chip_unmask_parent,
	.irq_set_affinity = bridge_set_affinity
पूर्ण;

अटल पूर्णांक bridge_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
			       अचिन्हित पूर्णांक nr_irqs, व्योम *arg)
अणु
	काष्ठा bridge_irq_chip_data *data;
	काष्ठा irq_alloc_info *info = arg;
	पूर्णांक ret;

	अगर (nr_irqs > 1 || !info)
		वापस -EINVAL;

	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	ret = irq_करोमुख्य_alloc_irqs_parent(करोमुख्य, virq, nr_irqs, arg);
	अगर (ret >= 0) अणु
		data->bc = info->ctrl;
		data->nasid = info->nasid;
		irq_करोमुख्य_set_info(करोमुख्य, virq, info->pin, &bridge_irq_chip,
				    data, handle_level_irq, शून्य, शून्य);
	पूर्ण अन्यथा अणु
		kमुक्त(data);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम bridge_करोमुख्य_मुक्त(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
			       अचिन्हित पूर्णांक nr_irqs)
अणु
	काष्ठा irq_data *irqd = irq_करोमुख्य_get_irq_data(करोमुख्य, virq);

	अगर (nr_irqs)
		वापस;

	kमुक्त(irqd->chip_data);
	irq_करोमुख्य_मुक्त_irqs_top(करोमुख्य, virq, nr_irqs);
पूर्ण

अटल पूर्णांक bridge_करोमुख्य_activate(काष्ठा irq_करोमुख्य *करोमुख्य,
				  काष्ठा irq_data *irqd, bool reserve)
अणु
	काष्ठा bridge_irq_chip_data *data = irqd->chip_data;
	काष्ठा bridge_controller *bc = data->bc;
	पूर्णांक bit = irqd->parent_data->hwirq;
	पूर्णांक pin = irqd->hwirq;
	u32 device;

	bridge_ग_लिखो(bc, b_पूर्णांक_addr[pin].addr,
		     (((bc->पूर्णांकr_addr >> 30) & 0x30000) |
		      bit | (data->nasid << 8)));
	bridge_set(bc, b_पूर्णांक_enable, (1 << pin));
	bridge_set(bc, b_पूर्णांक_enable, 0x7ffffe00); /* more stuff in पूर्णांक_enable */

	/*
	 * Enable sending of an पूर्णांकerrupt clear packet to the hub on a high to
	 * low transition of the पूर्णांकerrupt pin.
	 *
	 * IRIX sets additional bits in the address which are करोcumented as
	 * reserved in the bridge करोcs.
	 */
	bridge_set(bc, b_पूर्णांक_mode, (1UL << pin));

	/*
	 * We assume the bridge to have a 1:1 mapping between devices
	 * (slots) and पूर्णांकr pins.
	 */
	device = bridge_पढ़ो(bc, b_पूर्णांक_device);
	device &= ~(7 << (pin*3));
	device |= (pin << (pin*3));
	bridge_ग_लिखो(bc, b_पूर्णांक_device, device);

	bridge_पढ़ो(bc, b_wid_tflush);
	वापस 0;
पूर्ण

अटल व्योम bridge_करोमुख्य_deactivate(काष्ठा irq_करोमुख्य *करोमुख्य,
				     काष्ठा irq_data *irqd)
अणु
	काष्ठा bridge_irq_chip_data *data = irqd->chip_data;

	bridge_clr(data->bc, b_पूर्णांक_enable, (1 << irqd->hwirq));
	bridge_पढ़ो(data->bc, b_wid_tflush);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops bridge_करोमुख्य_ops = अणु
	.alloc      = bridge_करोमुख्य_alloc,
	.मुक्त       = bridge_करोमुख्य_मुक्त,
	.activate   = bridge_करोमुख्य_activate,
	.deactivate = bridge_करोमुख्य_deactivate
पूर्ण;

/*
 * All observed requests have pin == 1. We could have a global here, that
 * माला_लो incremented and वापसed every समय - unक्रमtunately, pci_map_irq
 * may be called on the same device over and over, and need to वापस the
 * same value. On O2000, pin can be 0 or 1, and PCI slots can be [0..7].
 *
 * A given PCI device, in general, should be able to पूर्णांकr any of the cpus
 * on any one of the hubs connected to its xbow.
 */
अटल पूर्णांक bridge_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	काष्ठा bridge_controller *bc = BRIDGE_CONTROLLER(dev->bus);
	काष्ठा irq_alloc_info info;
	पूर्णांक irq;

	चयन (pin) अणु
	हाल PCI_INTERRUPT_UNKNOWN:
	हाल PCI_INTERRUPT_INTA:
	हाल PCI_INTERRUPT_INTC:
		pin = 0;
		अवरोध;
	हाल PCI_INTERRUPT_INTB:
	हाल PCI_INTERRUPT_INTD:
		pin = 1;
	पूर्ण

	irq = bc->pci_पूर्णांक[slot][pin];
	अगर (irq == -1) अणु
		info.ctrl = bc;
		info.nasid = bc->nasid;
		info.pin = bc->पूर्णांक_mapping[slot][pin];

		irq = irq_करोमुख्य_alloc_irqs(bc->करोमुख्य, 1, bc->nasid, &info);
		अगर (irq < 0)
			वापस irq;

		bc->pci_पूर्णांक[slot][pin] = irq;
	पूर्ण
	वापस irq;
पूर्ण

#घोषणा IOC3_SID(sid)	(PCI_VENDOR_ID_SGI | ((sid) << 16))

अटल व्योम bridge_setup_ip27_baseio6g(काष्ठा bridge_controller *bc)
अणु
	bc->ioc3_sid[2] = IOC3_SID(IOC3_SUBSYS_IP27_BASEIO6G);
	bc->ioc3_sid[6] = IOC3_SID(IOC3_SUBSYS_IP27_MIO);
	bc->पूर्णांक_mapping[2][1] = 4;
	bc->पूर्णांक_mapping[6][1] = 6;
पूर्ण

अटल व्योम bridge_setup_ip27_baseio(काष्ठा bridge_controller *bc)
अणु
	bc->ioc3_sid[2] = IOC3_SID(IOC3_SUBSYS_IP27_BASEIO);
	bc->पूर्णांक_mapping[2][1] = 4;
पूर्ण

अटल व्योम bridge_setup_ip29_baseio(काष्ठा bridge_controller *bc)
अणु
	bc->ioc3_sid[2] = IOC3_SID(IOC3_SUBSYS_IP29_SYSBOARD);
	bc->पूर्णांक_mapping[2][1] = 3;
पूर्ण

अटल व्योम bridge_setup_ip30_sysboard(काष्ठा bridge_controller *bc)
अणु
	bc->ioc3_sid[2] = IOC3_SID(IOC3_SUBSYS_IP30_SYSBOARD);
	bc->पूर्णांक_mapping[2][1] = 4;
पूर्ण

अटल व्योम bridge_setup_menet(काष्ठा bridge_controller *bc)
अणु
	bc->ioc3_sid[0] = IOC3_SID(IOC3_SUBSYS_MENET);
	bc->ioc3_sid[1] = IOC3_SID(IOC3_SUBSYS_MENET);
	bc->ioc3_sid[2] = IOC3_SID(IOC3_SUBSYS_MENET);
	bc->ioc3_sid[3] = IOC3_SID(IOC3_SUBSYS_MENET4);
पूर्ण

अटल व्योम bridge_setup_io7(काष्ठा bridge_controller *bc)
अणु
	bc->ioc3_sid[4] = IOC3_SID(IOC3_SUBSYS_IO7);
पूर्ण

अटल व्योम bridge_setup_io8(काष्ठा bridge_controller *bc)
अणु
	bc->ioc3_sid[4] = IOC3_SID(IOC3_SUBSYS_IO8);
पूर्ण

अटल व्योम bridge_setup_io9(काष्ठा bridge_controller *bc)
अणु
	bc->ioc3_sid[1] = IOC3_SID(IOC3_SUBSYS_IO9);
पूर्ण

अटल व्योम bridge_setup_ip34_fuel_sysboard(काष्ठा bridge_controller *bc)
अणु
	bc->ioc3_sid[4] = IOC3_SID(IOC3_SUBSYS_IP34_SYSBOARD);
पूर्ण

#घोषणा BRIDGE_BOARD_SETUP(_partno, _setup)	\
	अणु .match = _partno, .setup = _setup पूर्ण

अटल स्थिर काष्ठा अणु
	अक्षर *match;
	व्योम (*setup)(काष्ठा bridge_controller *bc);
पूर्ण bridge_ioc3_devid[] = अणु
	BRIDGE_BOARD_SETUP("030-0734-", bridge_setup_ip27_baseio6g),
	BRIDGE_BOARD_SETUP("030-0880-", bridge_setup_ip27_baseio6g),
	BRIDGE_BOARD_SETUP("030-1023-", bridge_setup_ip27_baseio),
	BRIDGE_BOARD_SETUP("030-1124-", bridge_setup_ip27_baseio),
	BRIDGE_BOARD_SETUP("030-1025-", bridge_setup_ip29_baseio),
	BRIDGE_BOARD_SETUP("030-1244-", bridge_setup_ip29_baseio),
	BRIDGE_BOARD_SETUP("030-1389-", bridge_setup_ip29_baseio),
	BRIDGE_BOARD_SETUP("030-0887-", bridge_setup_ip30_sysboard),
	BRIDGE_BOARD_SETUP("030-1467-", bridge_setup_ip30_sysboard),
	BRIDGE_BOARD_SETUP("030-0873-", bridge_setup_menet),
	BRIDGE_BOARD_SETUP("030-1557-", bridge_setup_io7),
	BRIDGE_BOARD_SETUP("030-1673-", bridge_setup_io8),
	BRIDGE_BOARD_SETUP("030-1771-", bridge_setup_io9),
	BRIDGE_BOARD_SETUP("030-1707-", bridge_setup_ip34_fuel_sysboard),
पूर्ण;

अटल व्योम bridge_setup_board(काष्ठा bridge_controller *bc, अक्षर *partnum)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(bridge_ioc3_devid); i++)
		अगर (!म_भेदन(partnum, bridge_ioc3_devid[i].match,
			     म_माप(bridge_ioc3_devid[i].match))) अणु
			bridge_ioc3_devid[i].setup(bc);
		पूर्ण
पूर्ण

अटल पूर्णांक bridge_nvmem_match(काष्ठा device *dev, स्थिर व्योम *data)
अणु
	स्थिर अक्षर *name = dev_name(dev);
	स्थिर अक्षर *prefix = data;

	अगर (म_माप(name) < म_माप(prefix))
		वापस 0;

	वापस स_भेद(prefix, dev_name(dev), म_माप(prefix)) == 0;
पूर्ण

अटल पूर्णांक bridge_get_partnum(u64 baddr, अक्षर *partnum)
अणु
	काष्ठा nvmem_device *nvmem;
	अक्षर prefix[24];
	u8 prom[64];
	पूर्णांक i, j;
	पूर्णांक ret;

	snम_लिखो(prefix, माप(prefix), "bridge-%012llx-0b-", baddr);

	nvmem = nvmem_device_find(prefix, bridge_nvmem_match);
	अगर (IS_ERR(nvmem))
		वापस PTR_ERR(nvmem);

	ret = nvmem_device_पढ़ो(nvmem, 0, 64, prom);
	nvmem_device_put(nvmem);

	अगर (ret != 64)
		वापस ret;

	अगर (crc16(CRC16_INIT, prom, 32) != CRC16_VALID ||
	    crc16(CRC16_INIT, prom + 32, 32) != CRC16_VALID)
		वापस -EINVAL;

	/* Assemble part number */
	j = 0;
	क्रम (i = 0; i < 19; i++)
		अगर (prom[i + 11] != ' ')
			partnum[j++] = prom[i + 11];

	क्रम (i = 0; i < 6; i++)
		अगर (prom[i + 32] != ' ')
			partnum[j++] = prom[i + 32];

	partnum[j] = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक bridge_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा xtalk_bridge_platक्रमm_data *bd = dev_get_platdata(&pdev->dev);
	काष्ठा device *dev = &pdev->dev;
	काष्ठा bridge_controller *bc;
	काष्ठा pci_host_bridge *host;
	काष्ठा irq_करोमुख्य *करोमुख्य, *parent;
	काष्ठा fwnode_handle *fn;
	अक्षर partnum[26];
	पूर्णांक slot;
	पूर्णांक err;

	/* get part number from one wire prom */
	अगर (bridge_get_partnum(virt_to_phys((व्योम *)bd->bridge_addr), partnum))
		वापस -EPROBE_DEFER; /* not available yet */

	parent = irq_get_शेष_host();
	अगर (!parent)
		वापस -ENODEV;
	fn = irq_करोमुख्य_alloc_named_fwnode("BRIDGE");
	अगर (!fn)
		वापस -ENOMEM;
	करोमुख्य = irq_करोमुख्य_create_hierarchy(parent, 0, 8, fn,
					     &bridge_करोमुख्य_ops, शून्य);
	अगर (!करोमुख्य) अणु
		irq_करोमुख्य_मुक्त_fwnode(fn);
		वापस -ENOMEM;
	पूर्ण

	pci_set_flags(PCI_PROBE_ONLY);

	host = devm_pci_alloc_host_bridge(dev, माप(*bc));
	अगर (!host) अणु
		err = -ENOMEM;
		जाओ err_हटाओ_करोमुख्य;
	पूर्ण

	bc = pci_host_bridge_priv(host);

	bc->busn.name		= "Bridge PCI busn";
	bc->busn.start		= 0;
	bc->busn.end		= 0xff;
	bc->busn.flags		= IORESOURCE_BUS;

	bc->करोमुख्य		= करोमुख्य;

	pci_add_resource_offset(&host->winकरोws, &bd->mem, bd->mem_offset);
	pci_add_resource_offset(&host->winकरोws, &bd->io, bd->io_offset);
	pci_add_resource(&host->winकरोws, &bc->busn);

	err = devm_request_pci_bus_resources(dev, &host->winकरोws);
	अगर (err < 0)
		जाओ err_मुक्त_resource;

	bc->nasid = bd->nasid;

	bc->baddr = (u64)bd->masterwid << 60 | PCI64_ATTR_BAR;
	bc->base = (काष्ठा bridge_regs *)bd->bridge_addr;
	bc->पूर्णांकr_addr = bd->पूर्णांकr_addr;

	/*
	 * Clear all pending पूर्णांकerrupts.
	 */
	bridge_ग_लिखो(bc, b_पूर्णांक_rst_stat, BRIDGE_IRR_ALL_CLR);

	/*
	 * Until otherwise set up, assume all पूर्णांकerrupts are from slot 0
	 */
	bridge_ग_लिखो(bc, b_पूर्णांक_device, 0x0);

	/*
	 * disable swapping क्रम big winकरोws
	 */
	bridge_clr(bc, b_wid_control,
		   BRIDGE_CTRL_IO_SWAP | BRIDGE_CTRL_MEM_SWAP);
#अगर_घोषित CONFIG_PAGE_SIZE_4KB
	bridge_clr(bc, b_wid_control, BRIDGE_CTRL_PAGE_SIZE);
#अन्यथा /* 16kB or larger */
	bridge_set(bc, b_wid_control, BRIDGE_CTRL_PAGE_SIZE);
#पूर्ण_अगर

	/*
	 * Hmm...  IRIX sets additional bits in the address which
	 * are करोcumented as reserved in the bridge करोcs.
	 */
	bridge_ग_लिखो(bc, b_wid_पूर्णांक_upper,
		     ((bc->पूर्णांकr_addr >> 32) & 0xffff) | (bd->masterwid << 16));
	bridge_ग_लिखो(bc, b_wid_पूर्णांक_lower, bc->पूर्णांकr_addr & 0xffffffff);
	bridge_ग_लिखो(bc, b_dir_map, (bd->masterwid << 20));	/* DMA */
	bridge_ग_लिखो(bc, b_पूर्णांक_enable, 0);

	क्रम (slot = 0; slot < 8; slot++) अणु
		bridge_set(bc, b_device[slot].reg, BRIDGE_DEV_SWAP_सूची);
		bc->pci_पूर्णांक[slot][0] = -1;
		bc->pci_पूर्णांक[slot][1] = -1;
		/* शेष पूर्णांकerrupt pin mapping */
		bc->पूर्णांक_mapping[slot][0] = slot;
		bc->पूर्णांक_mapping[slot][1] = slot ^ 4;
	पूर्ण
	bridge_पढ़ो(bc, b_wid_tflush);	  /* रुको until Bridge PIO complete */

	bridge_setup_board(bc, partnum);

	host->dev.parent = dev;
	host->sysdata = bc;
	host->busnr = 0;
	host->ops = &bridge_pci_ops;
	host->map_irq = bridge_map_irq;
	host->swizzle_irq = pci_common_swizzle;

	err = pci_scan_root_bus_bridge(host);
	अगर (err < 0)
		जाओ err_मुक्त_resource;

	pci_bus_claim_resources(host->bus);
	pci_bus_add_devices(host->bus);

	platक्रमm_set_drvdata(pdev, host->bus);

	वापस 0;

err_मुक्त_resource:
	pci_मुक्त_resource_list(&host->winकरोws);
err_हटाओ_करोमुख्य:
	irq_करोमुख्य_हटाओ(करोमुख्य);
	irq_करोमुख्य_मुक्त_fwnode(fn);
	वापस err;
पूर्ण

अटल पूर्णांक bridge_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pci_bus *bus = platक्रमm_get_drvdata(pdev);
	काष्ठा bridge_controller *bc = BRIDGE_CONTROLLER(bus);
	काष्ठा fwnode_handle *fn = bc->करोमुख्य->fwnode;

	irq_करोमुख्य_हटाओ(bc->करोमुख्य);
	irq_करोमुख्य_मुक्त_fwnode(fn);
	pci_lock_rescan_हटाओ();
	pci_stop_root_bus(bus);
	pci_हटाओ_root_bus(bus);
	pci_unlock_rescan_हटाओ();

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver bridge_driver = अणु
	.probe  = bridge_probe,
	.हटाओ = bridge_हटाओ,
	.driver = अणु
		.name = "xtalk-bridge",
	पूर्ण
पूर्ण;

builtin_platक्रमm_driver(bridge_driver);
