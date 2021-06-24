<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2015 - 2016 Cavium, Inc.
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_pci.h>
#समावेश <linux/pci-acpi.h>
#समावेश <linux/pci-ecam.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/io-64-nonatomic-lo-hi.h>
#समावेश "../pci.h"

#अगर defined(CONFIG_PCI_HOST_THUNDER_PEM) || (defined(CONFIG_ACPI) && defined(CONFIG_PCI_QUIRKS))

#घोषणा PEM_CFG_WR 0x28
#घोषणा PEM_CFG_RD 0x30

/*
 * Enhanced Configuration Access Mechanism (ECAM)
 *
 * N.B. This is a non-standard platक्रमm-specअगरic ECAM bus shअगरt value.  For
 * standard values defined in the PCI Express Base Specअगरication see
 * include/linux/pci-ecam.h.
 */
#घोषणा THUNDER_PCIE_ECAM_BUS_SHIFT	24

काष्ठा thunder_pem_pci अणु
	u32		ea_entry[3];
	व्योम __iomem	*pem_reg_base;
पूर्ण;

अटल पूर्णांक thunder_pem_bridge_पढ़ो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				   पूर्णांक where, पूर्णांक size, u32 *val)
अणु
	u64 पढ़ो_val, पंचांगp_val;
	काष्ठा pci_config_winकरोw *cfg = bus->sysdata;
	काष्ठा thunder_pem_pci *pem_pci = (काष्ठा thunder_pem_pci *)cfg->priv;

	अगर (devfn != 0 || where >= 2048) अणु
		*val = ~0;
		वापस PCIBIOS_DEVICE_NOT_FOUND;
	पूर्ण

	/*
	 * 32-bit accesses only.  Write the address to the low order
	 * bits of PEM_CFG_RD, then trigger the पढ़ो by पढ़ोing back.
	 * The config data lands in the upper 32-bits of PEM_CFG_RD.
	 */
	पढ़ो_val = where & ~3ull;
	ग_लिखोq(पढ़ो_val, pem_pci->pem_reg_base + PEM_CFG_RD);
	पढ़ो_val = पढ़ोq(pem_pci->pem_reg_base + PEM_CFG_RD);
	पढ़ो_val >>= 32;

	/*
	 * The config space contains some garbage, fix it up.  Also
	 * synthesize an EA capability क्रम the BAR used by MSI-X.
	 */
	चयन (where & ~3) अणु
	हाल 0x40:
		पढ़ो_val &= 0xffff00ff;
		पढ़ो_val |= 0x00007000; /* Skip MSI CAP */
		अवरोध;
	हाल 0x70: /* Express Cap */
		/*
		 * Change PME पूर्णांकerrupt to vector 2 on T88 where it
		 * पढ़ोs as 0, अन्यथा leave it alone.
		 */
		अगर (!(पढ़ो_val & (0x1f << 25)))
			पढ़ो_val |= (2u << 25);
		अवरोध;
	हाल 0xb0: /* MSI-X Cap */
		/* TableSize=2 or 4, Next Cap is EA */
		पढ़ो_val &= 0xc00000ff;
		/*
		 * If Express Cap(0x70) raw PME vector पढ़ोs as 0 we are on
		 * T88 and TableSize is reported as 4, अन्यथा TableSize
		 * is 2.
		 */
		ग_लिखोq(0x70, pem_pci->pem_reg_base + PEM_CFG_RD);
		पंचांगp_val = पढ़ोq(pem_pci->pem_reg_base + PEM_CFG_RD);
		पंचांगp_val >>= 32;
		अगर (!(पंचांगp_val & (0x1f << 25)))
			पढ़ो_val |= 0x0003bc00;
		अन्यथा
			पढ़ो_val |= 0x0001bc00;
		अवरोध;
	हाल 0xb4:
		/* Table offset=0, BIR=0 */
		पढ़ो_val = 0x00000000;
		अवरोध;
	हाल 0xb8:
		/* BPA offset=0xf0000, BIR=0 */
		पढ़ो_val = 0x000f0000;
		अवरोध;
	हाल 0xbc:
		/* EA, 1 entry, no next Cap */
		पढ़ो_val = 0x00010014;
		अवरोध;
	हाल 0xc0:
		/* DW2 क्रम type-1 */
		पढ़ो_val = 0x00000000;
		अवरोध;
	हाल 0xc4:
		/* Entry BEI=0, PP=0x00, SP=0xff, ES=3 */
		पढ़ो_val = 0x80ff0003;
		अवरोध;
	हाल 0xc8:
		पढ़ो_val = pem_pci->ea_entry[0];
		अवरोध;
	हाल 0xcc:
		पढ़ो_val = pem_pci->ea_entry[1];
		अवरोध;
	हाल 0xd0:
		पढ़ो_val = pem_pci->ea_entry[2];
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	पढ़ो_val >>= (8 * (where & 3));
	चयन (size) अणु
	हाल 1:
		पढ़ो_val &= 0xff;
		अवरोध;
	हाल 2:
		पढ़ो_val &= 0xffff;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	*val = पढ़ो_val;
	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक thunder_pem_config_पढ़ो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				   पूर्णांक where, पूर्णांक size, u32 *val)
अणु
	काष्ठा pci_config_winकरोw *cfg = bus->sysdata;

	अगर (bus->number < cfg->busr.start ||
	    bus->number > cfg->busr.end)
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	/*
	 * The first device on the bus is the PEM PCIe bridge.
	 * Special हाल its config access.
	 */
	अगर (bus->number == cfg->busr.start)
		वापस thunder_pem_bridge_पढ़ो(bus, devfn, where, size, val);

	वापस pci_generic_config_पढ़ो(bus, devfn, where, size, val);
पूर्ण

/*
 * Some of the w1c_bits below also include पढ़ो-only or non-writable
 * reserved bits, this makes the code simpler and is OK as the bits
 * are not affected by writing zeros to them.
 */
अटल u32 thunder_pem_bridge_w1c_bits(u64 where_aligned)
अणु
	u32 w1c_bits = 0;

	चयन (where_aligned) अणु
	हाल 0x04: /* Command/Status */
	हाल 0x1c: /* Base and I/O Limit/Secondary Status */
		w1c_bits = 0xff000000;
		अवरोध;
	हाल 0x44: /* Power Management Control and Status */
		w1c_bits = 0xfffffe00;
		अवरोध;
	हाल 0x78: /* Device Control/Device Status */
	हाल 0x80: /* Link Control/Link Status */
	हाल 0x88: /* Slot Control/Slot Status */
	हाल 0x90: /* Root Status */
	हाल 0xa0: /* Link Control 2 Registers/Link Status 2 */
		w1c_bits = 0xffff0000;
		अवरोध;
	हाल 0x104: /* Uncorrectable Error Status */
	हाल 0x110: /* Correctable Error Status */
	हाल 0x130: /* Error Status */
	हाल 0x160: /* Link Control 4 */
		w1c_bits = 0xffffffff;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस w1c_bits;
पूर्ण

/* Some bits must be written to one so they appear to be पढ़ो-only. */
अटल u32 thunder_pem_bridge_w1_bits(u64 where_aligned)
अणु
	u32 w1_bits;

	चयन (where_aligned) अणु
	हाल 0x1c: /* I/O Base / I/O Limit, Secondary Status */
		/* Force 32-bit I/O addressing. */
		w1_bits = 0x0101;
		अवरोध;
	हाल 0x24: /* Prefetchable Memory Base / Prefetchable Memory Limit */
		/* Force 64-bit addressing */
		w1_bits = 0x00010001;
		अवरोध;
	शेष:
		w1_bits = 0;
		अवरोध;
	पूर्ण
	वापस w1_bits;
पूर्ण

अटल पूर्णांक thunder_pem_bridge_ग_लिखो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				    पूर्णांक where, पूर्णांक size, u32 val)
अणु
	काष्ठा pci_config_winकरोw *cfg = bus->sysdata;
	काष्ठा thunder_pem_pci *pem_pci = (काष्ठा thunder_pem_pci *)cfg->priv;
	u64 ग_लिखो_val, पढ़ो_val;
	u64 where_aligned = where & ~3ull;
	u32 mask = 0;


	अगर (devfn != 0 || where >= 2048)
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	/*
	 * 32-bit accesses only.  If the ग_लिखो is क्रम a size smaller
	 * than 32-bits, we must first पढ़ो the 32-bit value and merge
	 * in the desired bits and then ग_लिखो the whole 32-bits back
	 * out.
	 */
	चयन (size) अणु
	हाल 1:
		ग_लिखोq(where_aligned, pem_pci->pem_reg_base + PEM_CFG_RD);
		पढ़ो_val = पढ़ोq(pem_pci->pem_reg_base + PEM_CFG_RD);
		पढ़ो_val >>= 32;
		mask = ~(0xff << (8 * (where & 3)));
		पढ़ो_val &= mask;
		val = (val & 0xff) << (8 * (where & 3));
		val |= (u32)पढ़ो_val;
		अवरोध;
	हाल 2:
		ग_लिखोq(where_aligned, pem_pci->pem_reg_base + PEM_CFG_RD);
		पढ़ो_val = पढ़ोq(pem_pci->pem_reg_base + PEM_CFG_RD);
		पढ़ो_val >>= 32;
		mask = ~(0xffff << (8 * (where & 3)));
		पढ़ो_val &= mask;
		val = (val & 0xffff) << (8 * (where & 3));
		val |= (u32)पढ़ो_val;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/*
	 * By expanding the ग_लिखो width to 32 bits, we may
	 * inadvertently hit some W1C bits that were not पूर्णांकended to
	 * be written.  Calculate the mask that must be applied to the
	 * data to be written to aव्योम these हालs.
	 */
	अगर (mask) अणु
		u32 w1c_bits = thunder_pem_bridge_w1c_bits(where);

		अगर (w1c_bits) अणु
			mask &= w1c_bits;
			val &= ~mask;
		पूर्ण
	पूर्ण

	/*
	 * Some bits must be पढ़ो-only with value of one.  Since the
	 * access method allows these to be cleared अगर a zero is
	 * written, क्रमce them to one beक्रमe writing.
	 */
	val |= thunder_pem_bridge_w1_bits(where_aligned);

	/*
	 * Low order bits are the config address, the high order 32
	 * bits are the data to be written.
	 */
	ग_लिखो_val = (((u64)val) << 32) | where_aligned;
	ग_लिखोq(ग_लिखो_val, pem_pci->pem_reg_base + PEM_CFG_WR);
	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक thunder_pem_config_ग_लिखो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				    पूर्णांक where, पूर्णांक size, u32 val)
अणु
	काष्ठा pci_config_winकरोw *cfg = bus->sysdata;

	अगर (bus->number < cfg->busr.start ||
	    bus->number > cfg->busr.end)
		वापस PCIBIOS_DEVICE_NOT_FOUND;
	/*
	 * The first device on the bus is the PEM PCIe bridge.
	 * Special हाल its config access.
	 */
	अगर (bus->number == cfg->busr.start)
		वापस thunder_pem_bridge_ग_लिखो(bus, devfn, where, size, val);


	वापस pci_generic_config_ग_लिखो(bus, devfn, where, size, val);
पूर्ण

अटल पूर्णांक thunder_pem_init(काष्ठा device *dev, काष्ठा pci_config_winकरोw *cfg,
			    काष्ठा resource *res_pem)
अणु
	काष्ठा thunder_pem_pci *pem_pci;
	resource_माप_प्रकार bar4_start;

	pem_pci = devm_kzalloc(dev, माप(*pem_pci), GFP_KERNEL);
	अगर (!pem_pci)
		वापस -ENOMEM;

	pem_pci->pem_reg_base = devm_ioremap(dev, res_pem->start, 0x10000);
	अगर (!pem_pci->pem_reg_base)
		वापस -ENOMEM;

	/*
	 * The MSI-X BAR क्रम the PEM and AER पूर्णांकerrupts is located at
	 * a fixed offset from the PEM रेजिस्टर base.  Generate a
	 * fragment of the synthesized Enhanced Allocation capability
	 * काष्ठाure here क्रम the BAR.
	 */
	bar4_start = res_pem->start + 0xf00000;
	pem_pci->ea_entry[0] = lower_32_bits(bar4_start) | 2;
	pem_pci->ea_entry[1] = lower_32_bits(res_pem->end - bar4_start) & ~3u;
	pem_pci->ea_entry[2] = upper_32_bits(bar4_start);

	cfg->priv = pem_pci;
	वापस 0;
पूर्ण

#अगर defined(CONFIG_ACPI) && defined(CONFIG_PCI_QUIRKS)

#घोषणा PEM_RES_BASE		0x87e0c0000000ULL
#घोषणा PEM_NODE_MASK		GENMASK_ULL(45, 44)
#घोषणा PEM_INDX_MASK		GENMASK_ULL(26, 24)
#घोषणा PEM_MIN_DOM_IN_NODE	4
#घोषणा PEM_MAX_DOM_IN_NODE	10

अटल व्योम thunder_pem_reserve_range(काष्ठा device *dev, पूर्णांक seg,
				      काष्ठा resource *r)
अणु
	resource_माप_प्रकार start = r->start, end = r->end;
	काष्ठा resource *res;
	स्थिर अक्षर *regionid;

	regionid = kaप्र_लिखो(GFP_KERNEL, "PEM RC:%d", seg);
	अगर (!regionid)
		वापस;

	res = request_mem_region(start, end - start + 1, regionid);
	अगर (res)
		res->flags &= ~IORESOURCE_BUSY;
	अन्यथा
		kमुक्त(regionid);

	dev_info(dev, "%pR %s reserved\n", r,
		 res ? "has been" : "could not be");
पूर्ण

अटल व्योम thunder_pem_legacy_fw(काष्ठा acpi_pci_root *root,
				 काष्ठा resource *res_pem)
अणु
	पूर्णांक node = acpi_get_node(root->device->handle);
	पूर्णांक index;

	अगर (node == NUMA_NO_NODE)
		node = 0;

	index = root->segment - PEM_MIN_DOM_IN_NODE;
	index -= node * PEM_MAX_DOM_IN_NODE;
	res_pem->start = PEM_RES_BASE | FIELD_PREP(PEM_NODE_MASK, node) |
					FIELD_PREP(PEM_INDX_MASK, index);
	res_pem->flags = IORESOURCE_MEM;
पूर्ण

अटल पूर्णांक thunder_pem_acpi_init(काष्ठा pci_config_winकरोw *cfg)
अणु
	काष्ठा device *dev = cfg->parent;
	काष्ठा acpi_device *adev = to_acpi_device(dev);
	काष्ठा acpi_pci_root *root = acpi_driver_data(adev);
	काष्ठा resource *res_pem;
	पूर्णांक ret;

	res_pem = devm_kzalloc(&adev->dev, माप(*res_pem), GFP_KERNEL);
	अगर (!res_pem)
		वापस -ENOMEM;

	ret = acpi_get_rc_resources(dev, "CAVA02B", root->segment, res_pem);

	/*
	 * If we fail to gather resources it means that we run with old
	 * FW where we need to calculate PEM-specअगरic resources manually.
	 */
	अगर (ret) अणु
		thunder_pem_legacy_fw(root, res_pem);
		/*
		 * Reserve 64K size PEM specअगरic resources. The full 16M range
		 * size is required क्रम thunder_pem_init() call.
		 */
		res_pem->end = res_pem->start + SZ_64K - 1;
		thunder_pem_reserve_range(dev, root->segment, res_pem);
		res_pem->end = res_pem->start + SZ_16M - 1;

		/* Reserve PCI configuration space as well. */
		thunder_pem_reserve_range(dev, root->segment, &cfg->res);
	पूर्ण

	वापस thunder_pem_init(dev, cfg, res_pem);
पूर्ण

स्थिर काष्ठा pci_ecam_ops thunder_pem_ecam_ops = अणु
	.bus_shअगरt	= THUNDER_PCIE_ECAM_BUS_SHIFT,
	.init		= thunder_pem_acpi_init,
	.pci_ops	= अणु
		.map_bus	= pci_ecam_map_bus,
		.पढ़ो		= thunder_pem_config_पढ़ो,
		.ग_लिखो		= thunder_pem_config_ग_लिखो,
	पूर्ण
पूर्ण;

#पूर्ण_अगर

#अगर_घोषित CONFIG_PCI_HOST_THUNDER_PEM

अटल पूर्णांक thunder_pem_platक्रमm_init(काष्ठा pci_config_winकरोw *cfg)
अणु
	काष्ठा device *dev = cfg->parent;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा resource *res_pem;

	अगर (!dev->of_node)
		वापस -EINVAL;

	/*
	 * The second रेजिस्टर range is the PEM bridge to the PCIe
	 * bus.  It has a dअगरferent config access method than those
	 * devices behind the bridge.
	 */
	res_pem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	अगर (!res_pem) अणु
		dev_err(dev, "missing \"reg[1]\"property\n");
		वापस -EINVAL;
	पूर्ण

	वापस thunder_pem_init(dev, cfg, res_pem);
पूर्ण

अटल स्थिर काष्ठा pci_ecam_ops pci_thunder_pem_ops = अणु
	.bus_shअगरt	= THUNDER_PCIE_ECAM_BUS_SHIFT,
	.init		= thunder_pem_platक्रमm_init,
	.pci_ops	= अणु
		.map_bus	= pci_ecam_map_bus,
		.पढ़ो		= thunder_pem_config_पढ़ो,
		.ग_लिखो		= thunder_pem_config_ग_लिखो,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा of_device_id thunder_pem_of_match[] = अणु
	अणु
		.compatible = "cavium,pci-host-thunder-pem",
		.data = &pci_thunder_pem_ops,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver thunder_pem_driver = अणु
	.driver = अणु
		.name = KBUILD_MODNAME,
		.of_match_table = thunder_pem_of_match,
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe = pci_host_common_probe,
पूर्ण;
builtin_platक्रमm_driver(thunder_pem_driver);

#पूर्ण_अगर
#पूर्ण_अगर
