<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2004 Benjamin Herrenschmuidt (benh@kernel.crashing.org),
 *		      IBM Corp.
 */

#अघोषित DEBUG

#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/माला.स>
#समावेश <linux/init.h>
#समावेश <linux/irq.h>

#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/pci-bridge.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/iommu.h>
#समावेश <यंत्र/ppc-pci.h>
#समावेश <यंत्र/isa-bridge.h>

#समावेश "maple.h"

#अगर_घोषित DEBUG
#घोषणा DBG(x...) prपूर्णांकk(x)
#अन्यथा
#घोषणा DBG(x...)
#पूर्ण_अगर

अटल काष्ठा pci_controller *u3_agp, *u3_ht, *u4_pcie;

अटल पूर्णांक __init fixup_one_level_bus_range(काष्ठा device_node *node, पूर्णांक higher)
अणु
	क्रम (; node; node = node->sibling) अणु
		स्थिर पूर्णांक *bus_range;
		स्थिर अचिन्हित पूर्णांक *class_code;
		पूर्णांक len;

		/* For PCI<->PCI bridges or CardBus bridges, we go करोwn */
		class_code = of_get_property(node, "class-code", शून्य);
		अगर (!class_code || ((*class_code >> 8) != PCI_CLASS_BRIDGE_PCI &&
			(*class_code >> 8) != PCI_CLASS_BRIDGE_CARDBUS))
			जारी;
		bus_range = of_get_property(node, "bus-range", &len);
		अगर (bus_range != शून्य && len > 2 * माप(पूर्णांक)) अणु
			अगर (bus_range[1] > higher)
				higher = bus_range[1];
		पूर्ण
		higher = fixup_one_level_bus_range(node->child, higher);
	पूर्ण
	वापस higher;
पूर्ण

/* This routine fixes the "bus-range" property of all bridges in the
 * प्रणाली since they tend to have their "last" member wrong on macs
 *
 * Note that the bus numbers manipulated here are OF bus numbers, they
 * are not Linux bus numbers.
 */
अटल व्योम __init fixup_bus_range(काष्ठा device_node *bridge)
अणु
	पूर्णांक *bus_range;
	काष्ठा property *prop;
	पूर्णांक len;

	/* Lookup the "bus-range" property क्रम the hose */
	prop = of_find_property(bridge, "bus-range", &len);
	अगर (prop == शून्य  || prop->value == शून्य || len < 2 * माप(पूर्णांक)) अणु
		prपूर्णांकk(KERN_WARNING "Can't get bus-range for %pOF\n",
			       bridge);
		वापस;
	पूर्ण
	bus_range = prop->value;
	bus_range[1] = fixup_one_level_bus_range(bridge->child, bus_range[1]);
पूर्ण


अटल अचिन्हित दीर्घ u3_agp_cfa0(u8 devfn, u8 off)
अणु
	वापस (1 << (अचिन्हित दीर्घ)PCI_SLOT(devfn)) |
		((अचिन्हित दीर्घ)PCI_FUNC(devfn) << 8) |
		((अचिन्हित दीर्घ)off & 0xFCUL);
पूर्ण

अटल अचिन्हित दीर्घ u3_agp_cfa1(u8 bus, u8 devfn, u8 off)
अणु
	वापस ((अचिन्हित दीर्घ)bus << 16) |
		((अचिन्हित दीर्घ)devfn << 8) |
		((अचिन्हित दीर्घ)off & 0xFCUL) |
		1UL;
पूर्ण

अटल अस्थिर व्योम __iomem *u3_agp_cfg_access(काष्ठा pci_controller* hose,
				       u8 bus, u8 dev_fn, u8 offset)
अणु
	अचिन्हित पूर्णांक caddr;

	अगर (bus == hose->first_busno) अणु
		अगर (dev_fn < (11 << 3))
			वापस शून्य;
		caddr = u3_agp_cfa0(dev_fn, offset);
	पूर्ण अन्यथा
		caddr = u3_agp_cfa1(bus, dev_fn, offset);

	/* Uninorth will वापस garbage अगर we करोn't पढ़ो back the value ! */
	करो अणु
		out_le32(hose->cfg_addr, caddr);
	पूर्ण जबतक (in_le32(hose->cfg_addr) != caddr);

	offset &= 0x07;
	वापस hose->cfg_data + offset;
पूर्ण

अटल पूर्णांक u3_agp_पढ़ो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
			      पूर्णांक offset, पूर्णांक len, u32 *val)
अणु
	काष्ठा pci_controller *hose;
	अस्थिर व्योम __iomem *addr;

	hose = pci_bus_to_host(bus);
	अगर (hose == शून्य)
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	addr = u3_agp_cfg_access(hose, bus->number, devfn, offset);
	अगर (!addr)
		वापस PCIBIOS_DEVICE_NOT_FOUND;
	/*
	 * Note: the caller has alपढ़ोy checked that offset is
	 * suitably aligned and that len is 1, 2 or 4.
	 */
	चयन (len) अणु
	हाल 1:
		*val = in_8(addr);
		अवरोध;
	हाल 2:
		*val = in_le16(addr);
		अवरोध;
	शेष:
		*val = in_le32(addr);
		अवरोध;
	पूर्ण
	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक u3_agp_ग_लिखो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
			       पूर्णांक offset, पूर्णांक len, u32 val)
अणु
	काष्ठा pci_controller *hose;
	अस्थिर व्योम __iomem *addr;

	hose = pci_bus_to_host(bus);
	अगर (hose == शून्य)
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	addr = u3_agp_cfg_access(hose, bus->number, devfn, offset);
	अगर (!addr)
		वापस PCIBIOS_DEVICE_NOT_FOUND;
	/*
	 * Note: the caller has alपढ़ोy checked that offset is
	 * suitably aligned and that len is 1, 2 or 4.
	 */
	चयन (len) अणु
	हाल 1:
		out_8(addr, val);
		अवरोध;
	हाल 2:
		out_le16(addr, val);
		अवरोध;
	शेष:
		out_le32(addr, val);
		अवरोध;
	पूर्ण
	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल काष्ठा pci_ops u3_agp_pci_ops =
अणु
	.पढ़ो = u3_agp_पढ़ो_config,
	.ग_लिखो = u3_agp_ग_लिखो_config,
पूर्ण;

अटल अचिन्हित दीर्घ u3_ht_cfa0(u8 devfn, u8 off)
अणु
	वापस (devfn << 8) | off;
पूर्ण

अटल अचिन्हित दीर्घ u3_ht_cfa1(u8 bus, u8 devfn, u8 off)
अणु
	वापस u3_ht_cfa0(devfn, off) + (bus << 16) + 0x01000000UL;
पूर्ण

अटल अस्थिर व्योम __iomem *u3_ht_cfg_access(काष्ठा pci_controller* hose,
				      u8 bus, u8 devfn, u8 offset)
अणु
	अगर (bus == hose->first_busno) अणु
		अगर (PCI_SLOT(devfn) == 0)
			वापस शून्य;
		वापस hose->cfg_data + u3_ht_cfa0(devfn, offset);
	पूर्ण अन्यथा
		वापस hose->cfg_data + u3_ht_cfa1(bus, devfn, offset);
पूर्ण

अटल पूर्णांक u3_ht_root_पढ़ो_config(काष्ठा pci_controller *hose, u8 offset,
				  पूर्णांक len, u32 *val)
अणु
	अस्थिर व्योम __iomem *addr;

	addr = hose->cfg_addr;
	addr += ((offset & ~3) << 2) + (4 - len - (offset & 3));

	चयन (len) अणु
	हाल 1:
		*val = in_8(addr);
		अवरोध;
	हाल 2:
		*val = in_be16(addr);
		अवरोध;
	शेष:
		*val = in_be32(addr);
		अवरोध;
	पूर्ण

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक u3_ht_root_ग_लिखो_config(काष्ठा pci_controller *hose, u8 offset,
				  पूर्णांक len, u32 val)
अणु
	अस्थिर व्योम __iomem *addr;

	addr = hose->cfg_addr + ((offset & ~3) << 2) + (4 - len - (offset & 3));

	अगर (offset >= PCI_BASE_ADDRESS_0 && offset < PCI_CAPABILITY_LIST)
		वापस PCIBIOS_SUCCESSFUL;

	चयन (len) अणु
	हाल 1:
		out_8(addr, val);
		अवरोध;
	हाल 2:
		out_be16(addr, val);
		अवरोध;
	शेष:
		out_be32(addr, val);
		अवरोध;
	पूर्ण

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक u3_ht_पढ़ो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
			     पूर्णांक offset, पूर्णांक len, u32 *val)
अणु
	काष्ठा pci_controller *hose;
	अस्थिर व्योम __iomem *addr;

	hose = pci_bus_to_host(bus);
	अगर (hose == शून्य)
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	अगर (bus->number == hose->first_busno && devfn == PCI_DEVFN(0, 0))
		वापस u3_ht_root_पढ़ो_config(hose, offset, len, val);

	अगर (offset > 0xff)
		वापस PCIBIOS_BAD_REGISTER_NUMBER;

	addr = u3_ht_cfg_access(hose, bus->number, devfn, offset);
	अगर (!addr)
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	/*
	 * Note: the caller has alपढ़ोy checked that offset is
	 * suitably aligned and that len is 1, 2 or 4.
	 */
	चयन (len) अणु
	हाल 1:
		*val = in_8(addr);
		अवरोध;
	हाल 2:
		*val = in_le16(addr);
		अवरोध;
	शेष:
		*val = in_le32(addr);
		अवरोध;
	पूर्ण
	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक u3_ht_ग_लिखो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
			      पूर्णांक offset, पूर्णांक len, u32 val)
अणु
	काष्ठा pci_controller *hose;
	अस्थिर व्योम __iomem *addr;

	hose = pci_bus_to_host(bus);
	अगर (hose == शून्य)
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	अगर (bus->number == hose->first_busno && devfn == PCI_DEVFN(0, 0))
		वापस u3_ht_root_ग_लिखो_config(hose, offset, len, val);

	अगर (offset > 0xff)
		वापस PCIBIOS_BAD_REGISTER_NUMBER;

	addr = u3_ht_cfg_access(hose, bus->number, devfn, offset);
	अगर (!addr)
		वापस PCIBIOS_DEVICE_NOT_FOUND;
	/*
	 * Note: the caller has alपढ़ोy checked that offset is
	 * suitably aligned and that len is 1, 2 or 4.
	 */
	चयन (len) अणु
	हाल 1:
		out_8(addr, val);
		अवरोध;
	हाल 2:
		out_le16(addr, val);
		अवरोध;
	शेष:
		out_le32(addr, val);
		अवरोध;
	पूर्ण
	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल काष्ठा pci_ops u3_ht_pci_ops =
अणु
	.पढ़ो = u3_ht_पढ़ो_config,
	.ग_लिखो = u3_ht_ग_लिखो_config,
पूर्ण;

अटल अचिन्हित पूर्णांक u4_pcie_cfa0(अचिन्हित पूर्णांक devfn, अचिन्हित पूर्णांक off)
अणु
	वापस (1 << PCI_SLOT(devfn))	|
	       (PCI_FUNC(devfn) << 8)	|
	       ((off >> 8) << 28) 	|
	       (off & 0xfcu);
पूर्ण

अटल अचिन्हित पूर्णांक u4_pcie_cfa1(अचिन्हित पूर्णांक bus, अचिन्हित पूर्णांक devfn,
				 अचिन्हित पूर्णांक off)
अणु
        वापस (bus << 16)		|
	       (devfn << 8)		|
	       ((off >> 8) << 28)	|
	       (off & 0xfcu)		| 1u;
पूर्ण

अटल अस्थिर व्योम __iomem *u4_pcie_cfg_access(काष्ठा pci_controller* hose,
                                        u8 bus, u8 dev_fn, पूर्णांक offset)
अणु
        अचिन्हित पूर्णांक caddr;

        अगर (bus == hose->first_busno)
                caddr = u4_pcie_cfa0(dev_fn, offset);
        अन्यथा
                caddr = u4_pcie_cfa1(bus, dev_fn, offset);

        /* Uninorth will वापस garbage अगर we करोn't पढ़ो back the value ! */
        करो अणु
                out_le32(hose->cfg_addr, caddr);
        पूर्ण जबतक (in_le32(hose->cfg_addr) != caddr);

        offset &= 0x03;
        वापस hose->cfg_data + offset;
पूर्ण

अटल पूर्णांक u4_pcie_पढ़ो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
                               पूर्णांक offset, पूर्णांक len, u32 *val)
अणु
        काष्ठा pci_controller *hose;
        अस्थिर व्योम __iomem *addr;

        hose = pci_bus_to_host(bus);
        अगर (hose == शून्य)
                वापस PCIBIOS_DEVICE_NOT_FOUND;
        अगर (offset >= 0x1000)
                वापस  PCIBIOS_BAD_REGISTER_NUMBER;
        addr = u4_pcie_cfg_access(hose, bus->number, devfn, offset);
        अगर (!addr)
                वापस PCIBIOS_DEVICE_NOT_FOUND;
        /*
         * Note: the caller has alपढ़ोy checked that offset is
         * suitably aligned and that len is 1, 2 or 4.
         */
        चयन (len) अणु
        हाल 1:
                *val = in_8(addr);
                अवरोध;
        हाल 2:
                *val = in_le16(addr);
                अवरोध;
        शेष:
                *val = in_le32(addr);
                अवरोध;
        पूर्ण
        वापस PCIBIOS_SUCCESSFUL;
पूर्ण
अटल पूर्णांक u4_pcie_ग_लिखो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
                                पूर्णांक offset, पूर्णांक len, u32 val)
अणु
        काष्ठा pci_controller *hose;
        अस्थिर व्योम __iomem *addr;

        hose = pci_bus_to_host(bus);
        अगर (hose == शून्य)
                वापस PCIBIOS_DEVICE_NOT_FOUND;
        अगर (offset >= 0x1000)
                वापस  PCIBIOS_BAD_REGISTER_NUMBER;
        addr = u4_pcie_cfg_access(hose, bus->number, devfn, offset);
        अगर (!addr)
                वापस PCIBIOS_DEVICE_NOT_FOUND;
        /*
         * Note: the caller has alपढ़ोy checked that offset is
         * suitably aligned and that len is 1, 2 or 4.
         */
        चयन (len) अणु
        हाल 1:
                out_8(addr, val);
                अवरोध;
        हाल 2:
                out_le16(addr, val);
                अवरोध;
        शेष:
                out_le32(addr, val);
                अवरोध;
        पूर्ण
        वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल काष्ठा pci_ops u4_pcie_pci_ops =
अणु
	.पढ़ो = u4_pcie_पढ़ो_config,
	.ग_लिखो = u4_pcie_ग_लिखो_config,
पूर्ण;

अटल व्योम __init setup_u3_agp(काष्ठा pci_controller* hose)
अणु
	/* On G5, we move AGP up to high bus number so we करोn't need
	 * to reassign bus numbers क्रम HT. If we ever have P2P bridges
	 * on AGP, we'll have to move pci_assign_all_buses to the
	 * pci_controller काष्ठाure so we enable it क्रम AGP and not क्रम
	 * HT childs.
	 * We hard code the address because of the dअगरferent size of
	 * the reg address cell, we shall fix that by समाप्तing काष्ठा
	 * reg_property and using some accessor functions instead
	 */
	hose->first_busno = 0xf0;
	hose->last_busno = 0xff;
	hose->ops = &u3_agp_pci_ops;
	hose->cfg_addr = ioremap(0xf0000000 + 0x800000, 0x1000);
	hose->cfg_data = ioremap(0xf0000000 + 0xc00000, 0x1000);

	u3_agp = hose;
पूर्ण

अटल व्योम __init setup_u4_pcie(काष्ठा pci_controller* hose)
अणु
        /* We currently only implement the "non-atomic" config space, to
         * be optimised later.
         */
        hose->ops = &u4_pcie_pci_ops;
        hose->cfg_addr = ioremap(0xf0000000 + 0x800000, 0x1000);
        hose->cfg_data = ioremap(0xf0000000 + 0xc00000, 0x1000);

        u4_pcie = hose;
पूर्ण

अटल व्योम __init setup_u3_ht(काष्ठा pci_controller* hose)
अणु
	hose->ops = &u3_ht_pci_ops;

	/* We hard code the address because of the dअगरferent size of
	 * the reg address cell, we shall fix that by समाप्तing काष्ठा
	 * reg_property and using some accessor functions instead
	 */
	hose->cfg_data = ioremap(0xf2000000, 0x02000000);
	hose->cfg_addr = ioremap(0xf8070000, 0x1000);

	hose->first_busno = 0;
	hose->last_busno = 0xef;

	u3_ht = hose;
पूर्ण

अटल पूर्णांक __init maple_add_bridge(काष्ठा device_node *dev)
अणु
	पूर्णांक len;
	काष्ठा pci_controller *hose;
	अक्षर* disp_name;
	स्थिर पूर्णांक *bus_range;
	पूर्णांक primary = 1;

	DBG("Adding PCI host bridge %pOF\n", dev);

	bus_range = of_get_property(dev, "bus-range", &len);
	अगर (bus_range == शून्य || len < 2 * माप(पूर्णांक)) अणु
		prपूर्णांकk(KERN_WARNING "Can't get bus-range for %pOF, assume bus 0\n",
		dev);
	पूर्ण

	hose = pcibios_alloc_controller(dev);
	अगर (hose == शून्य)
		वापस -ENOMEM;
	hose->first_busno = bus_range ? bus_range[0] : 0;
	hose->last_busno = bus_range ? bus_range[1] : 0xff;
	hose->controller_ops = maple_pci_controller_ops;

	disp_name = शून्य;
	अगर (of_device_is_compatible(dev, "u3-agp")) अणु
		setup_u3_agp(hose);
		disp_name = "U3-AGP";
		primary = 0;
	पूर्ण अन्यथा अगर (of_device_is_compatible(dev, "u3-ht")) अणु
		setup_u3_ht(hose);
		disp_name = "U3-HT";
		primary = 1;
        पूर्ण अन्यथा अगर (of_device_is_compatible(dev, "u4-pcie")) अणु
                setup_u4_pcie(hose);
                disp_name = "U4-PCIE";
                primary = 0;
	पूर्ण
	prपूर्णांकk(KERN_INFO "Found %s PCI host bridge. Firmware bus number: %d->%d\n",
		disp_name, hose->first_busno, hose->last_busno);

	/* Interpret the "ranges" property */
	/* This also maps the I/O region and sets isa_io/mem_base */
	pci_process_bridge_OF_ranges(hose, dev, primary);

	/* Fixup "bus-range" OF property */
	fixup_bus_range(dev);

	/* Check क्रम legacy IOs */
	isa_bridge_find_early(hose);

	/* create pci_dn's क्रम DT nodes under this PHB */
	pci_devs_phb_init_dynamic(hose);

	वापस 0;
पूर्ण


व्योम maple_pci_irq_fixup(काष्ठा pci_dev *dev)
अणु
	DBG(" -> maple_pci_irq_fixup\n");

	/* Fixup IRQ क्रम PCIe host */
	अगर (u4_pcie != शून्य && dev->bus->number == 0 &&
	    pci_bus_to_host(dev->bus) == u4_pcie) अणु
		prपूर्णांकk(KERN_DEBUG "Fixup U4 PCIe IRQ\n");
		dev->irq = irq_create_mapping(शून्य, 1);
		अगर (dev->irq)
			irq_set_irq_type(dev->irq, IRQ_TYPE_LEVEL_LOW);
	पूर्ण

	/* Hide AMD8111 IDE पूर्णांकerrupt when in legacy mode so
	 * the driver calls pci_get_legacy_ide_irq()
	 */
	अगर (dev->venकरोr == PCI_VENDOR_ID_AMD &&
	    dev->device == PCI_DEVICE_ID_AMD_8111_IDE &&
	    (dev->class & 5) != 5) अणु
		dev->irq = 0;
	पूर्ण

	DBG(" <- maple_pci_irq_fixup\n");
पूर्ण

अटल पूर्णांक maple_pci_root_bridge_prepare(काष्ठा pci_host_bridge *bridge)
अणु
	काष्ठा pci_controller *hose = pci_bus_to_host(bridge->bus);
	काष्ठा device_node *np, *child;

	अगर (hose != u3_agp)
		वापस 0;

	/* Fixup the PCI<->OF mapping क्रम U3 AGP due to bus rक्रमागतbering. We
	 * assume there is no P2P bridge on the AGP bus, which should be a
	 * safe assumptions hopefully.
	 */
	np = hose->dn;
	PCI_DN(np)->busno = 0xf0;
	क्रम_each_child_of_node(np, child)
		PCI_DN(child)->busno = 0xf0;

	वापस 0;
पूर्ण

व्योम __init maple_pci_init(व्योम)
अणु
	काष्ठा device_node *np, *root;
	काष्ठा device_node *ht = शून्य;

	/* Probe root PCI hosts, that is on U3 the AGP host and the
	 * HyperTransport host. That one is actually "kept" around
	 * and actually added last as it's resource management relies
	 * on the AGP resources to have been setup first
	 */
	root = of_find_node_by_path("/");
	अगर (root == शून्य) अणु
		prपूर्णांकk(KERN_CRIT "maple_find_bridges: can't find root of device tree\n");
		वापस;
	पूर्ण
	क्रम_each_child_of_node(root, np) अणु
		अगर (!of_node_is_type(np, "pci") && !of_node_is_type(np, "ht"))
			जारी;
		अगर ((of_device_is_compatible(np, "u4-pcie") ||
		     of_device_is_compatible(np, "u3-agp")) &&
		    maple_add_bridge(np) == 0)
			of_node_get(np);

		अगर (of_device_is_compatible(np, "u3-ht")) अणु
			of_node_get(np);
			ht = np;
		पूर्ण
	पूर्ण
	of_node_put(root);

	/* Now setup the HyperTransport host अगर we found any
	 */
	अगर (ht && maple_add_bridge(ht) != 0)
		of_node_put(ht);

	ppc_md.pcibios_root_bridge_prepare = maple_pci_root_bridge_prepare;

	/* Tell pci.c to not change any resource allocations.  */
	pci_add_flags(PCI_PROBE_ONLY);
पूर्ण

पूर्णांक maple_pci_get_legacy_ide_irq(काष्ठा pci_dev *pdev, पूर्णांक channel)
अणु
	काष्ठा device_node *np;
	अचिन्हित पूर्णांक defirq = channel ? 15 : 14;
	अचिन्हित पूर्णांक irq;

	अगर (pdev->venकरोr != PCI_VENDOR_ID_AMD ||
	    pdev->device != PCI_DEVICE_ID_AMD_8111_IDE)
		वापस defirq;

	np = pci_device_to_OF_node(pdev);
	अगर (np == शून्य) अणु
		prपूर्णांकk("Failed to locate OF node for IDE %s\n",
		       pci_name(pdev));
		वापस defirq;
	पूर्ण
	irq = irq_of_parse_and_map(np, channel & 0x1);
	अगर (!irq) अणु
		prपूर्णांकk("Failed to map onboard IDE interrupt for channel %d\n",
		       channel);
		वापस defirq;
	पूर्ण
	वापस irq;
पूर्ण

अटल व्योम quirk_ipr_msi(काष्ठा pci_dev *dev)
अणु
	/* Something prevents MSIs from the IPR from working on Bimini,
	 * and the driver has no smarts to recover. So disable MSI
	 * on it क्रम now. */

	अगर (machine_is(maple)) अणु
		dev->no_msi = 1;
		dev_info(&dev->dev, "Quirk disabled MSI\n");
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_IBM, PCI_DEVICE_ID_IBM_OBSIDIAN,
			quirk_ipr_msi);

काष्ठा pci_controller_ops maple_pci_controller_ops = अणु
पूर्ण;
