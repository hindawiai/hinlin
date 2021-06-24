<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Support क्रम indirect PCI bridges.
 *
 * Copyright (C) 1998 Gabriel Paubert.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/माला.स>
#समावेश <linux/init.h>

#समावेश <linux/पन.स>
#समावेश <यंत्र/pci-bridge.h>

अटल पूर्णांक
indirect_पढ़ो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक offset,
		     पूर्णांक len, u32 *val)
अणु
	काष्ठा pci_controller *hose = pci_bus_to_host(bus);
	अस्थिर व्योम __iomem *cfg_data;
	u8 cfg_type = 0;
	u32 bus_no, reg;

	अगर (hose->indirect_type & INसूचीECT_TYPE_NO_PCIE_LINK) अणु
		अगर (bus->number != hose->first_busno)
			वापस PCIBIOS_DEVICE_NOT_FOUND;
		अगर (devfn != 0)
			वापस PCIBIOS_DEVICE_NOT_FOUND;
	पूर्ण

	अगर (hose->indirect_type & INसूचीECT_TYPE_SET_CFG_TYPE)
		अगर (bus->number != hose->first_busno)
			cfg_type = 1;

	bus_no = (bus->number == hose->first_busno) ?
			hose->self_busno : bus->number;

	अगर (hose->indirect_type & INसूचीECT_TYPE_EXT_REG)
		reg = ((offset & 0xf00) << 16) | (offset & 0xfc);
	अन्यथा
		reg = offset & 0xfc; /* Only 3 bits क्रम function */

	अगर (hose->indirect_type & INसूचीECT_TYPE_BIG_ENDIAN)
		out_be32(hose->cfg_addr, (0x80000000 | (bus_no << 16) |
			 (devfn << 8) | reg | cfg_type));
	अन्यथा
		out_le32(hose->cfg_addr, (0x80000000 | (bus_no << 16) |
			 (devfn << 8) | reg | cfg_type));

	/*
	 * Note: the caller has alपढ़ोy checked that offset is
	 * suitably aligned and that len is 1, 2 or 4.
	 */
	cfg_data = hose->cfg_data + (offset & 3); /* Only 3 bits क्रम function */
	चयन (len) अणु
	हाल 1:
		*val = in_8(cfg_data);
		अवरोध;
	हाल 2:
		*val = in_le16(cfg_data);
		अवरोध;
	शेष:
		*val = in_le32(cfg_data);
		अवरोध;
	पूर्ण
	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक
indirect_ग_लिखो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक offset,
		      पूर्णांक len, u32 val)
अणु
	काष्ठा pci_controller *hose = pci_bus_to_host(bus);
	अस्थिर व्योम __iomem *cfg_data;
	u8 cfg_type = 0;
	u32 bus_no, reg;

	अगर (hose->indirect_type & INसूचीECT_TYPE_NO_PCIE_LINK) अणु
		अगर (bus->number != hose->first_busno)
			वापस PCIBIOS_DEVICE_NOT_FOUND;
		अगर (devfn != 0)
			वापस PCIBIOS_DEVICE_NOT_FOUND;
	पूर्ण

	अगर (hose->indirect_type & INसूचीECT_TYPE_SET_CFG_TYPE)
		अगर (bus->number != hose->first_busno)
			cfg_type = 1;

	bus_no = (bus->number == hose->first_busno) ?
			hose->self_busno : bus->number;

	अगर (hose->indirect_type & INसूचीECT_TYPE_EXT_REG)
		reg = ((offset & 0xf00) << 16) | (offset & 0xfc);
	अन्यथा
		reg = offset & 0xfc;

	अगर (hose->indirect_type & INसूचीECT_TYPE_BIG_ENDIAN)
		out_be32(hose->cfg_addr, (0x80000000 | (bus_no << 16) |
			 (devfn << 8) | reg | cfg_type));
	अन्यथा
		out_le32(hose->cfg_addr, (0x80000000 | (bus_no << 16) |
			 (devfn << 8) | reg | cfg_type));

	/* suppress setting of PCI_PRIMARY_BUS */
	अगर (hose->indirect_type & INसूचीECT_TYPE_SURPRESS_PRIMARY_BUS)
		अगर ((offset == PCI_PRIMARY_BUS) &&
			(bus->number == hose->first_busno))
			val &= 0xffffff00;

	/* Workaround क्रम PCI_28 Errata in 440EPx/GRx */
	अगर ((hose->indirect_type & INसूचीECT_TYPE_BROKEN_MRM) &&
			offset == PCI_CACHE_LINE_SIZE) अणु
		val = 0;
	पूर्ण

	/*
	 * Note: the caller has alपढ़ोy checked that offset is
	 * suitably aligned and that len is 1, 2 or 4.
	 */
	cfg_data = hose->cfg_data + (offset & 3);
	चयन (len) अणु
	हाल 1:
		out_8(cfg_data, val);
		अवरोध;
	हाल 2:
		out_le16(cfg_data, val);
		अवरोध;
	शेष:
		out_le32(cfg_data, val);
		अवरोध;
	पूर्ण

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल काष्ठा pci_ops indirect_pci_ops = अणु
	.पढ़ो = indirect_पढ़ो_config,
	.ग_लिखो = indirect_ग_लिखो_config,
पूर्ण;

व्योम __init
setup_indirect_pci(काष्ठा pci_controller *hose,
		   resource_माप_प्रकार cfg_addr,
		   resource_माप_प्रकार cfg_data, u32 flags)
अणु
	resource_माप_प्रकार base = cfg_addr & PAGE_MASK;
	व्योम __iomem *mbase;

	mbase = ioremap(base, PAGE_SIZE);
	hose->cfg_addr = mbase + (cfg_addr & ~PAGE_MASK);
	अगर ((cfg_data & PAGE_MASK) != base)
		mbase = ioremap(cfg_data & PAGE_MASK, PAGE_SIZE);
	hose->cfg_data = mbase + (cfg_data & ~PAGE_MASK);
	hose->ops = &indirect_pci_ops;
	hose->indirect_type = flags;
पूर्ण
