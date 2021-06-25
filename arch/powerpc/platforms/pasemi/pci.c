<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2006 PA Semi, Inc
 *
 * Authors: Kip Walker, PA Semi
 *	    Olof Johansson, PA Semi
 *
 * Maपूर्णांकained by: Olof Johansson <olof@lixom.net>
 *
 * Based on arch/घातerpc/platक्रमms/maple/pci.c
 */


#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>

#समावेश <यंत्र/pci-bridge.h>
#समावेश <यंत्र/isa-bridge.h>
#समावेश <यंत्र/machdep.h>

#समावेश <यंत्र/ppc-pci.h>

#समावेश "pasemi.h"

#घोषणा PA_PXP_CFA(bus, devfn, off) (((bus) << 20) | ((devfn) << 12) | (off))

अटल अंतरभूत पूर्णांक pa_pxp_offset_valid(u8 bus, u8 devfn, पूर्णांक offset)
अणु
	/* Device 0 Function 0 is special: It's config space spans function 1 as
	 * well, so allow larger offset. It's really a two-function device but the
	 * second function करोes not probe.
	 */
	अगर (bus == 0 && devfn == 0)
		वापस offset < 8192;
	अन्यथा
		वापस offset < 4096;
पूर्ण

अटल व्योम अस्थिर __iomem *pa_pxp_cfg_addr(काष्ठा pci_controller *hose,
				       u8 bus, u8 devfn, पूर्णांक offset)
अणु
	वापस hose->cfg_data + PA_PXP_CFA(bus, devfn, offset);
पूर्ण

अटल अंतरभूत पूर्णांक is_root_port(पूर्णांक busno, पूर्णांक devfn)
अणु
	वापस ((busno == 0) && (PCI_FUNC(devfn) < 4) &&
		 ((PCI_SLOT(devfn) == 16) || (PCI_SLOT(devfn) == 17)));
पूर्ण

अटल अंतरभूत पूर्णांक is_5945_reg(पूर्णांक reg)
अणु
	वापस (((reg >= 0x18) && (reg < 0x34)) ||
		((reg >= 0x158) && (reg < 0x178)));
पूर्ण

अटल पूर्णांक workaround_5945(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
			   पूर्णांक offset, पूर्णांक len, u32 *val)
अणु
	काष्ठा pci_controller *hose;
	व्योम अस्थिर __iomem *addr, *dummy;
	पूर्णांक byte;
	u32 पंचांगp;

	अगर (!is_root_port(bus->number, devfn) || !is_5945_reg(offset))
		वापस 0;

	hose = pci_bus_to_host(bus);

	addr = pa_pxp_cfg_addr(hose, bus->number, devfn, offset & ~0x3);
	byte = offset & 0x3;

	/* Workaround bug 5945: ग_लिखो 0 to a dummy रेजिस्टर beक्रमe पढ़ोing,
	 * and ग_लिखो back what we पढ़ो. We must पढ़ो/ग_लिखो the full 32-bit
	 * contents so we need to shअगरt and mask by hand.
	 */
	dummy = pa_pxp_cfg_addr(hose, bus->number, devfn, 0x10);
	out_le32(dummy, 0);
	पंचांगp = in_le32(addr);
	out_le32(addr, पंचांगp);

	चयन (len) अणु
	हाल 1:
		*val = (पंचांगp >> (8*byte)) & 0xff;
		अवरोध;
	हाल 2:
		अगर (byte == 0)
			*val = पंचांगp & 0xffff;
		अन्यथा
			*val = (पंचांगp >> 16) & 0xffff;
		अवरोध;
	शेष:
		*val = पंचांगp;
		अवरोध;
	पूर्ण

	वापस 1;
पूर्ण

#अगर_घोषित CONFIG_PPC_PASEMI_NEMO
#घोषणा PXP_ERR_CFG_REG	0x4
#घोषणा PXP_IGNORE_PCIE_ERRORS	0x800
#घोषणा SB600_BUS 5

अटल व्योम sb600_set_flag(पूर्णांक bus)
अणु
	अटल व्योम __iomem *iob_mapbase = शून्य;
	काष्ठा resource res;
	काष्ठा device_node *dn;
	पूर्णांक err;

	अगर (iob_mapbase == शून्य) अणु
		dn = of_find_compatible_node(शून्य, "isa", "pasemi,1682m-iob");
		अगर (!dn) अणु
			pr_crit("NEMO SB600 missing iob node\n");
			वापस;
		पूर्ण

		err = of_address_to_resource(dn, 0, &res);
		of_node_put(dn);

		अगर (err) अणु
			pr_crit("NEMO SB600 missing resource\n");
			वापस;
		पूर्ण

		pr_info("NEMO SB600 IOB base %08llx\n",res.start);

		iob_mapbase = ioremap(res.start + 0x100, 0x94);
	पूर्ण

	अगर (iob_mapbase != शून्य) अणु
		अगर (bus == SB600_BUS) अणु
			/*
			 * This is the SB600's bus, tell the PCI-e root port
			 * to allow non-zero devices to क्रमागतerate.
			 */
			out_le32(iob_mapbase + PXP_ERR_CFG_REG, in_le32(iob_mapbase + PXP_ERR_CFG_REG) | PXP_IGNORE_PCIE_ERRORS);
		पूर्ण अन्यथा अणु
			/*
			 * Only scan device 0 on other busses
			 */
			out_le32(iob_mapbase + PXP_ERR_CFG_REG, in_le32(iob_mapbase + PXP_ERR_CFG_REG) & ~PXP_IGNORE_PCIE_ERRORS);
		पूर्ण
	पूर्ण
पूर्ण

#अन्यथा

अटल व्योम sb600_set_flag(पूर्णांक bus)
अणु
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक pa_pxp_पढ़ो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
			      पूर्णांक offset, पूर्णांक len, u32 *val)
अणु
	काष्ठा pci_controller *hose;
	व्योम अस्थिर __iomem *addr;

	hose = pci_bus_to_host(bus);
	अगर (!hose)
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	अगर (!pa_pxp_offset_valid(bus->number, devfn, offset))
		वापस PCIBIOS_BAD_REGISTER_NUMBER;

	अगर (workaround_5945(bus, devfn, offset, len, val))
		वापस PCIBIOS_SUCCESSFUL;

	addr = pa_pxp_cfg_addr(hose, bus->number, devfn, offset);

	sb600_set_flag(bus->number);

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

अटल पूर्णांक pa_pxp_ग_लिखो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
			       पूर्णांक offset, पूर्णांक len, u32 val)
अणु
	काष्ठा pci_controller *hose;
	व्योम अस्थिर __iomem *addr;

	hose = pci_bus_to_host(bus);
	अगर (!hose)
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	अगर (!pa_pxp_offset_valid(bus->number, devfn, offset))
		वापस PCIBIOS_BAD_REGISTER_NUMBER;

	addr = pa_pxp_cfg_addr(hose, bus->number, devfn, offset);

	sb600_set_flag(bus->number);

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

अटल काष्ठा pci_ops pa_pxp_ops = अणु
	.पढ़ो = pa_pxp_पढ़ो_config,
	.ग_लिखो = pa_pxp_ग_लिखो_config,
पूर्ण;

अटल व्योम __init setup_pa_pxp(काष्ठा pci_controller *hose)
अणु
	hose->ops = &pa_pxp_ops;
	hose->cfg_data = ioremap(0xe0000000, 0x10000000);
पूर्ण

अटल पूर्णांक __init pas_add_bridge(काष्ठा device_node *dev)
अणु
	काष्ठा pci_controller *hose;

	pr_debug("Adding PCI host bridge %pOF\n", dev);

	hose = pcibios_alloc_controller(dev);
	अगर (!hose)
		वापस -ENOMEM;

	hose->first_busno = 0;
	hose->last_busno = 0xff;
	hose->controller_ops = pasemi_pci_controller_ops;

	setup_pa_pxp(hose);

	pr_info("Found PA-PXP PCI host bridge.\n");

	/* Interpret the "ranges" property */
	pci_process_bridge_OF_ranges(hose, dev, 1);

	/*
	 * Scan क्रम an isa bridge. This is needed to find the SB600 on the nemo
	 * and करोes nothing on machines without one.
	 */
	isa_bridge_find_early(hose);

	वापस 0;
पूर्ण

व्योम __init pas_pci_init(व्योम)
अणु
	काष्ठा device_node *np, *root;
	पूर्णांक res;

	root = of_find_node_by_path("/");
	अगर (!root) अणु
		pr_crit("pas_pci_init: can't find root of device tree\n");
		वापस;
	पूर्ण

	pci_set_flags(PCI_SCAN_ALL_PCIE_DEVS);

	np = of_find_compatible_node(root, शून्य, "pasemi,rootbus");
	अगर (np) अणु
		res = pas_add_bridge(np);
		of_node_put(np);
	पूर्ण
पूर्ण

व्योम __iomem *pasemi_pci_अ_लोfgaddr(काष्ठा pci_dev *dev, पूर्णांक offset)
अणु
	काष्ठा pci_controller *hose;

	hose = pci_bus_to_host(dev->bus);

	वापस (व्योम __iomem *)pa_pxp_cfg_addr(hose, dev->bus->number, dev->devfn, offset);
पूर्ण

काष्ठा pci_controller_ops pasemi_pci_controller_ops;
