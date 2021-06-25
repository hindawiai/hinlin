<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/**
 * APM X-Gene PCIe Driver
 *
 * Copyright (c) 2014 Applied Micro Circuits Corporation.
 *
 * Author: Tanmay Inamdar <tinamdar@apm.com>.
 */
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/memblock.h>
#समावेश <linux/init.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_pci.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci-acpi.h>
#समावेश <linux/pci-ecam.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश "../pci.h"

#घोषणा PCIECORE_CTLANDSTATUS		0x50
#घोषणा PIM1_1L				0x80
#घोषणा IBAR2				0x98
#घोषणा IR2MSK				0x9c
#घोषणा PIM2_1L				0xa0
#घोषणा IBAR3L				0xb4
#घोषणा IR3MSKL				0xbc
#घोषणा PIM3_1L				0xc4
#घोषणा OMR1BARL			0x100
#घोषणा OMR2BARL			0x118
#घोषणा OMR3BARL			0x130
#घोषणा CFGBARL				0x154
#घोषणा CFGBARH				0x158
#घोषणा CFGCTL				0x15c
#घोषणा RTDID				0x160
#घोषणा BRIDGE_CFG_0			0x2000
#घोषणा BRIDGE_CFG_4			0x2010
#घोषणा BRIDGE_STATUS_0			0x2600

#घोषणा LINK_UP_MASK			0x00000100
#घोषणा AXI_EP_CFG_ACCESS		0x10000
#घोषणा EN_COHERENCY			0xF0000000
#घोषणा EN_REG				0x00000001
#घोषणा OB_LO_IO			0x00000002
#घोषणा XGENE_PCIE_VENDORID		0x10E8
#घोषणा XGENE_PCIE_DEVICEID		0xE004
#घोषणा SZ_1T				(SZ_1G*1024ULL)
#घोषणा PIPE_PHY_RATE_RD(src)		((0xc000 & (u32)(src)) >> 0xe)

#घोषणा XGENE_V1_PCI_EXP_CAP		0x40

/* PCIe IP version */
#घोषणा XGENE_PCIE_IP_VER_UNKN		0
#घोषणा XGENE_PCIE_IP_VER_1		1
#घोषणा XGENE_PCIE_IP_VER_2		2

#अगर defined(CONFIG_PCI_XGENE) || (defined(CONFIG_ACPI) && defined(CONFIG_PCI_QUIRKS))
काष्ठा xgene_pcie_port अणु
	काष्ठा device_node	*node;
	काष्ठा device		*dev;
	काष्ठा clk		*clk;
	व्योम __iomem		*csr_base;
	व्योम __iomem		*cfg_base;
	अचिन्हित दीर्घ		cfg_addr;
	bool			link_up;
	u32			version;
पूर्ण;

अटल u32 xgene_pcie_पढ़ोl(काष्ठा xgene_pcie_port *port, u32 reg)
अणु
	वापस पढ़ोl(port->csr_base + reg);
पूर्ण

अटल व्योम xgene_pcie_ग_लिखोl(काष्ठा xgene_pcie_port *port, u32 reg, u32 val)
अणु
	ग_लिखोl(val, port->csr_base + reg);
पूर्ण

अटल अंतरभूत u32 pcie_bar_low_val(u32 addr, u32 flags)
अणु
	वापस (addr & PCI_BASE_ADDRESS_MEM_MASK) | flags;
पूर्ण

अटल अंतरभूत काष्ठा xgene_pcie_port *pcie_bus_to_port(काष्ठा pci_bus *bus)
अणु
	काष्ठा pci_config_winकरोw *cfg;

	अगर (acpi_disabled)
		वापस (काष्ठा xgene_pcie_port *)(bus->sysdata);

	cfg = bus->sysdata;
	वापस (काष्ठा xgene_pcie_port *)(cfg->priv);
पूर्ण

/*
 * When the address bit [17:16] is 2'b01, the Configuration access will be
 * treated as Type 1 and it will be क्रमwarded to बाह्यal PCIe device.
 */
अटल व्योम __iomem *xgene_pcie_get_cfg_base(काष्ठा pci_bus *bus)
अणु
	काष्ठा xgene_pcie_port *port = pcie_bus_to_port(bus);

	अगर (bus->number >= (bus->primary + 1))
		वापस port->cfg_base + AXI_EP_CFG_ACCESS;

	वापस port->cfg_base;
पूर्ण

/*
 * For Configuration request, RTDID रेजिस्टर is used as Bus Number,
 * Device Number and Function number of the header fields.
 */
अटल व्योम xgene_pcie_set_rtdid_reg(काष्ठा pci_bus *bus, uपूर्णांक devfn)
अणु
	काष्ठा xgene_pcie_port *port = pcie_bus_to_port(bus);
	अचिन्हित पूर्णांक b, d, f;
	u32 rtdid_val = 0;

	b = bus->number;
	d = PCI_SLOT(devfn);
	f = PCI_FUNC(devfn);

	अगर (!pci_is_root_bus(bus))
		rtdid_val = (b << 8) | (d << 3) | f;

	xgene_pcie_ग_लिखोl(port, RTDID, rtdid_val);
	/* पढ़ो the रेजिस्टर back to ensure flush */
	xgene_pcie_पढ़ोl(port, RTDID);
पूर्ण

/*
 * X-Gene PCIe port uses BAR0-BAR1 of RC's configuration space as
 * the translation from PCI bus to native BUS.  Entire DDR region
 * is mapped पूर्णांकo PCIe space using these रेजिस्टरs, so it can be
 * reached by DMA from EP devices.  The BAR0/1 of bridge should be
 * hidden during क्रमागतeration to aव्योम the sizing and resource allocation
 * by PCIe core.
 */
अटल bool xgene_pcie_hide_rc_bars(काष्ठा pci_bus *bus, पूर्णांक offset)
अणु
	अगर (pci_is_root_bus(bus) && ((offset == PCI_BASE_ADDRESS_0) ||
				     (offset == PCI_BASE_ADDRESS_1)))
		वापस true;

	वापस false;
पूर्ण

अटल व्योम __iomem *xgene_pcie_map_bus(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
					पूर्णांक offset)
अणु
	अगर ((pci_is_root_bus(bus) && devfn != 0) ||
	    xgene_pcie_hide_rc_bars(bus, offset))
		वापस शून्य;

	xgene_pcie_set_rtdid_reg(bus, devfn);
	वापस xgene_pcie_get_cfg_base(bus) + offset;
पूर्ण

अटल पूर्णांक xgene_pcie_config_पढ़ो32(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				    पूर्णांक where, पूर्णांक size, u32 *val)
अणु
	काष्ठा xgene_pcie_port *port = pcie_bus_to_port(bus);

	अगर (pci_generic_config_पढ़ो32(bus, devfn, where & ~0x3, 4, val) !=
	    PCIBIOS_SUCCESSFUL)
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	/*
	 * The v1 controller has a bug in its Configuration Request
	 * Retry Status (CRS) logic: when CRS Software Visibility is
	 * enabled and we पढ़ो the Venकरोr and Device ID of a non-existent
	 * device, the controller fabricates वापस data of 0xFFFF0001
	 * ("device exists but is not ready") instead of 0xFFFFFFFF
	 * ("device does not exist").  This causes the PCI core to retry
	 * the पढ़ो until it बार out.  Aव्योम this by not claiming to
	 * support CRS SV.
	 */
	अगर (pci_is_root_bus(bus) && (port->version == XGENE_PCIE_IP_VER_1) &&
	    ((where & ~0x3) == XGENE_V1_PCI_EXP_CAP + PCI_EXP_RTCTL))
		*val &= ~(PCI_EXP_RTCAP_CRSVIS << 16);

	अगर (size <= 2)
		*val = (*val >> (8 * (where & 3))) & ((1 << (size * 8)) - 1);

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_ACPI) && defined(CONFIG_PCI_QUIRKS)
अटल पूर्णांक xgene_get_csr_resource(काष्ठा acpi_device *adev,
				  काष्ठा resource *res)
अणु
	काष्ठा device *dev = &adev->dev;
	काष्ठा resource_entry *entry;
	काष्ठा list_head list;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	INIT_LIST_HEAD(&list);
	flags = IORESOURCE_MEM;
	ret = acpi_dev_get_resources(adev, &list,
				     acpi_dev_filter_resource_type_cb,
				     (व्योम *) flags);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to parse _CRS method, error code %d\n",
			ret);
		वापस ret;
	पूर्ण

	अगर (ret == 0) अणु
		dev_err(dev, "no IO and memory resources present in _CRS\n");
		वापस -EINVAL;
	पूर्ण

	entry = list_first_entry(&list, काष्ठा resource_entry, node);
	*res = *entry->res;
	acpi_dev_मुक्त_resource_list(&list);
	वापस 0;
पूर्ण

अटल पूर्णांक xgene_pcie_ecam_init(काष्ठा pci_config_winकरोw *cfg, u32 ipversion)
अणु
	काष्ठा device *dev = cfg->parent;
	काष्ठा acpi_device *adev = to_acpi_device(dev);
	काष्ठा xgene_pcie_port *port;
	काष्ठा resource csr;
	पूर्णांक ret;

	port = devm_kzalloc(dev, माप(*port), GFP_KERNEL);
	अगर (!port)
		वापस -ENOMEM;

	ret = xgene_get_csr_resource(adev, &csr);
	अगर (ret) अणु
		dev_err(dev, "can't get CSR resource\n");
		वापस ret;
	पूर्ण
	port->csr_base = devm_pci_remap_cfg_resource(dev, &csr);
	अगर (IS_ERR(port->csr_base))
		वापस PTR_ERR(port->csr_base);

	port->cfg_base = cfg->win;
	port->version = ipversion;

	cfg->priv = port;
	वापस 0;
पूर्ण

अटल पूर्णांक xgene_v1_pcie_ecam_init(काष्ठा pci_config_winकरोw *cfg)
अणु
	वापस xgene_pcie_ecam_init(cfg, XGENE_PCIE_IP_VER_1);
पूर्ण

स्थिर काष्ठा pci_ecam_ops xgene_v1_pcie_ecam_ops = अणु
	.init		= xgene_v1_pcie_ecam_init,
	.pci_ops	= अणु
		.map_bus	= xgene_pcie_map_bus,
		.पढ़ो		= xgene_pcie_config_पढ़ो32,
		.ग_लिखो		= pci_generic_config_ग_लिखो,
	पूर्ण
पूर्ण;

अटल पूर्णांक xgene_v2_pcie_ecam_init(काष्ठा pci_config_winकरोw *cfg)
अणु
	वापस xgene_pcie_ecam_init(cfg, XGENE_PCIE_IP_VER_2);
पूर्ण

स्थिर काष्ठा pci_ecam_ops xgene_v2_pcie_ecam_ops = अणु
	.init		= xgene_v2_pcie_ecam_init,
	.pci_ops	= अणु
		.map_bus	= xgene_pcie_map_bus,
		.पढ़ो		= xgene_pcie_config_पढ़ो32,
		.ग_लिखो		= pci_generic_config_ग_लिखो,
	पूर्ण
पूर्ण;
#पूर्ण_अगर

#अगर defined(CONFIG_PCI_XGENE)
अटल u64 xgene_pcie_set_ib_mask(काष्ठा xgene_pcie_port *port, u32 addr,
				  u32 flags, u64 size)
अणु
	u64 mask = (~(size - 1) & PCI_BASE_ADDRESS_MEM_MASK) | flags;
	u32 val32 = 0;
	u32 val;

	val32 = xgene_pcie_पढ़ोl(port, addr);
	val = (val32 & 0x0000ffff) | (lower_32_bits(mask) << 16);
	xgene_pcie_ग_लिखोl(port, addr, val);

	val32 = xgene_pcie_पढ़ोl(port, addr + 0x04);
	val = (val32 & 0xffff0000) | (lower_32_bits(mask) >> 16);
	xgene_pcie_ग_लिखोl(port, addr + 0x04, val);

	val32 = xgene_pcie_पढ़ोl(port, addr + 0x04);
	val = (val32 & 0x0000ffff) | (upper_32_bits(mask) << 16);
	xgene_pcie_ग_लिखोl(port, addr + 0x04, val);

	val32 = xgene_pcie_पढ़ोl(port, addr + 0x08);
	val = (val32 & 0xffff0000) | (upper_32_bits(mask) >> 16);
	xgene_pcie_ग_लिखोl(port, addr + 0x08, val);

	वापस mask;
पूर्ण

अटल व्योम xgene_pcie_linkup(काष्ठा xgene_pcie_port *port,
			      u32 *lanes, u32 *speed)
अणु
	u32 val32;

	port->link_up = false;
	val32 = xgene_pcie_पढ़ोl(port, PCIECORE_CTLANDSTATUS);
	अगर (val32 & LINK_UP_MASK) अणु
		port->link_up = true;
		*speed = PIPE_PHY_RATE_RD(val32);
		val32 = xgene_pcie_पढ़ोl(port, BRIDGE_STATUS_0);
		*lanes = val32 >> 26;
	पूर्ण
पूर्ण

अटल पूर्णांक xgene_pcie_init_port(काष्ठा xgene_pcie_port *port)
अणु
	काष्ठा device *dev = port->dev;
	पूर्णांक rc;

	port->clk = clk_get(dev, शून्य);
	अगर (IS_ERR(port->clk)) अणु
		dev_err(dev, "clock not available\n");
		वापस -ENODEV;
	पूर्ण

	rc = clk_prepare_enable(port->clk);
	अगर (rc) अणु
		dev_err(dev, "clock enable failed\n");
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xgene_pcie_map_reg(काष्ठा xgene_pcie_port *port,
			      काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = port->dev;
	काष्ठा resource *res;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "csr");
	port->csr_base = devm_pci_remap_cfg_resource(dev, res);
	अगर (IS_ERR(port->csr_base))
		वापस PTR_ERR(port->csr_base);

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "cfg");
	port->cfg_base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(port->cfg_base))
		वापस PTR_ERR(port->cfg_base);
	port->cfg_addr = res->start;

	वापस 0;
पूर्ण

अटल व्योम xgene_pcie_setup_ob_reg(काष्ठा xgene_pcie_port *port,
				    काष्ठा resource *res, u32 offset,
				    u64 cpu_addr, u64 pci_addr)
अणु
	काष्ठा device *dev = port->dev;
	resource_माप_प्रकार size = resource_size(res);
	u64 restype = resource_type(res);
	u64 mask = 0;
	u32 min_size;
	u32 flag = EN_REG;

	अगर (restype == IORESOURCE_MEM) अणु
		min_size = SZ_128M;
	पूर्ण अन्यथा अणु
		min_size = 128;
		flag |= OB_LO_IO;
	पूर्ण

	अगर (size >= min_size)
		mask = ~(size - 1) | flag;
	अन्यथा
		dev_warn(dev, "res size 0x%llx less than minimum 0x%x\n",
			 (u64)size, min_size);

	xgene_pcie_ग_लिखोl(port, offset, lower_32_bits(cpu_addr));
	xgene_pcie_ग_लिखोl(port, offset + 0x04, upper_32_bits(cpu_addr));
	xgene_pcie_ग_लिखोl(port, offset + 0x08, lower_32_bits(mask));
	xgene_pcie_ग_लिखोl(port, offset + 0x0c, upper_32_bits(mask));
	xgene_pcie_ग_लिखोl(port, offset + 0x10, lower_32_bits(pci_addr));
	xgene_pcie_ग_लिखोl(port, offset + 0x14, upper_32_bits(pci_addr));
पूर्ण

अटल व्योम xgene_pcie_setup_cfg_reg(काष्ठा xgene_pcie_port *port)
अणु
	u64 addr = port->cfg_addr;

	xgene_pcie_ग_लिखोl(port, CFGBARL, lower_32_bits(addr));
	xgene_pcie_ग_लिखोl(port, CFGBARH, upper_32_bits(addr));
	xgene_pcie_ग_लिखोl(port, CFGCTL, EN_REG);
पूर्ण

अटल पूर्णांक xgene_pcie_map_ranges(काष्ठा xgene_pcie_port *port)
अणु
	काष्ठा pci_host_bridge *bridge = pci_host_bridge_from_priv(port);
	काष्ठा resource_entry *winकरोw;
	काष्ठा device *dev = port->dev;

	resource_list_क्रम_each_entry(winकरोw, &bridge->winकरोws) अणु
		काष्ठा resource *res = winकरोw->res;
		u64 restype = resource_type(res);

		dev_dbg(dev, "%pR\n", res);

		चयन (restype) अणु
		हाल IORESOURCE_IO:
			xgene_pcie_setup_ob_reg(port, res, OMR3BARL,
						pci_pio_to_address(res->start),
						res->start - winकरोw->offset);
			अवरोध;
		हाल IORESOURCE_MEM:
			अगर (res->flags & IORESOURCE_PREFETCH)
				xgene_pcie_setup_ob_reg(port, res, OMR2BARL,
							res->start,
							res->start -
							winकरोw->offset);
			अन्यथा
				xgene_pcie_setup_ob_reg(port, res, OMR1BARL,
							res->start,
							res->start -
							winकरोw->offset);
			अवरोध;
		हाल IORESOURCE_BUS:
			अवरोध;
		शेष:
			dev_err(dev, "invalid resource %pR\n", res);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	xgene_pcie_setup_cfg_reg(port);
	वापस 0;
पूर्ण

अटल व्योम xgene_pcie_setup_pims(काष्ठा xgene_pcie_port *port, u32 pim_reg,
				  u64 pim, u64 size)
अणु
	xgene_pcie_ग_लिखोl(port, pim_reg, lower_32_bits(pim));
	xgene_pcie_ग_लिखोl(port, pim_reg + 0x04,
			  upper_32_bits(pim) | EN_COHERENCY);
	xgene_pcie_ग_लिखोl(port, pim_reg + 0x10, lower_32_bits(size));
	xgene_pcie_ग_लिखोl(port, pim_reg + 0x14, upper_32_bits(size));
पूर्ण

/*
 * X-Gene PCIe support maximum 3 inbound memory regions
 * This function helps to select a region based on size of region
 */
अटल पूर्णांक xgene_pcie_select_ib_reg(u8 *ib_reg_mask, u64 size)
अणु
	अगर ((size > 4) && (size < SZ_16M) && !(*ib_reg_mask & (1 << 1))) अणु
		*ib_reg_mask |= (1 << 1);
		वापस 1;
	पूर्ण

	अगर ((size > SZ_1K) && (size < SZ_1T) && !(*ib_reg_mask & (1 << 0))) अणु
		*ib_reg_mask |= (1 << 0);
		वापस 0;
	पूर्ण

	अगर ((size > SZ_1M) && (size < SZ_1T) && !(*ib_reg_mask & (1 << 2))) अणु
		*ib_reg_mask |= (1 << 2);
		वापस 2;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल व्योम xgene_pcie_setup_ib_reg(काष्ठा xgene_pcie_port *port,
				    काष्ठा resource_entry *entry,
				    u8 *ib_reg_mask)
अणु
	व्योम __iomem *cfg_base = port->cfg_base;
	काष्ठा device *dev = port->dev;
	व्योम *bar_addr;
	u32 pim_reg;
	u64 cpu_addr = entry->res->start;
	u64 pci_addr = cpu_addr - entry->offset;
	u64 size = resource_size(entry->res);
	u64 mask = ~(size - 1) | EN_REG;
	u32 flags = PCI_BASE_ADDRESS_MEM_TYPE_64;
	u32 bar_low;
	पूर्णांक region;

	region = xgene_pcie_select_ib_reg(ib_reg_mask, size);
	अगर (region < 0) अणु
		dev_warn(dev, "invalid pcie dma-range config\n");
		वापस;
	पूर्ण

	अगर (entry->res->flags & IORESOURCE_PREFETCH)
		flags |= PCI_BASE_ADDRESS_MEM_PREFETCH;

	bar_low = pcie_bar_low_val((u32)cpu_addr, flags);
	चयन (region) अणु
	हाल 0:
		xgene_pcie_set_ib_mask(port, BRIDGE_CFG_4, flags, size);
		bar_addr = cfg_base + PCI_BASE_ADDRESS_0;
		ग_लिखोl(bar_low, bar_addr);
		ग_लिखोl(upper_32_bits(cpu_addr), bar_addr + 0x4);
		pim_reg = PIM1_1L;
		अवरोध;
	हाल 1:
		xgene_pcie_ग_लिखोl(port, IBAR2, bar_low);
		xgene_pcie_ग_लिखोl(port, IR2MSK, lower_32_bits(mask));
		pim_reg = PIM2_1L;
		अवरोध;
	हाल 2:
		xgene_pcie_ग_लिखोl(port, IBAR3L, bar_low);
		xgene_pcie_ग_लिखोl(port, IBAR3L + 0x4, upper_32_bits(cpu_addr));
		xgene_pcie_ग_लिखोl(port, IR3MSKL, lower_32_bits(mask));
		xgene_pcie_ग_लिखोl(port, IR3MSKL + 0x4, upper_32_bits(mask));
		pim_reg = PIM3_1L;
		अवरोध;
	पूर्ण

	xgene_pcie_setup_pims(port, pim_reg, pci_addr, ~(size - 1));
पूर्ण

अटल पूर्णांक xgene_pcie_parse_map_dma_ranges(काष्ठा xgene_pcie_port *port)
अणु
	काष्ठा pci_host_bridge *bridge = pci_host_bridge_from_priv(port);
	काष्ठा resource_entry *entry;
	u8 ib_reg_mask = 0;

	resource_list_क्रम_each_entry(entry, &bridge->dma_ranges)
		xgene_pcie_setup_ib_reg(port, entry, &ib_reg_mask);

	वापस 0;
पूर्ण

/* clear BAR configuration which was करोne by firmware */
अटल व्योम xgene_pcie_clear_config(काष्ठा xgene_pcie_port *port)
अणु
	पूर्णांक i;

	क्रम (i = PIM1_1L; i <= CFGCTL; i += 4)
		xgene_pcie_ग_लिखोl(port, i, 0);
पूर्ण

अटल पूर्णांक xgene_pcie_setup(काष्ठा xgene_pcie_port *port)
अणु
	काष्ठा device *dev = port->dev;
	u32 val, lanes = 0, speed = 0;
	पूर्णांक ret;

	xgene_pcie_clear_config(port);

	/* setup the venकरोr and device IDs correctly */
	val = (XGENE_PCIE_DEVICEID << 16) | XGENE_PCIE_VENDORID;
	xgene_pcie_ग_लिखोl(port, BRIDGE_CFG_0, val);

	ret = xgene_pcie_map_ranges(port);
	अगर (ret)
		वापस ret;

	ret = xgene_pcie_parse_map_dma_ranges(port);
	अगर (ret)
		वापस ret;

	xgene_pcie_linkup(port, &lanes, &speed);
	अगर (!port->link_up)
		dev_info(dev, "(rc) link down\n");
	अन्यथा
		dev_info(dev, "(rc) x%d gen-%d link up\n", lanes, speed + 1);
	वापस 0;
पूर्ण

अटल काष्ठा pci_ops xgene_pcie_ops = अणु
	.map_bus = xgene_pcie_map_bus,
	.पढ़ो = xgene_pcie_config_पढ़ो32,
	.ग_लिखो = pci_generic_config_ग_लिखो32,
पूर्ण;

अटल पूर्णांक xgene_pcie_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *dn = dev->of_node;
	काष्ठा xgene_pcie_port *port;
	काष्ठा pci_host_bridge *bridge;
	पूर्णांक ret;

	bridge = devm_pci_alloc_host_bridge(dev, माप(*port));
	अगर (!bridge)
		वापस -ENOMEM;

	port = pci_host_bridge_priv(bridge);

	port->node = of_node_get(dn);
	port->dev = dev;

	port->version = XGENE_PCIE_IP_VER_UNKN;
	अगर (of_device_is_compatible(port->node, "apm,xgene-pcie"))
		port->version = XGENE_PCIE_IP_VER_1;

	ret = xgene_pcie_map_reg(port, pdev);
	अगर (ret)
		वापस ret;

	ret = xgene_pcie_init_port(port);
	अगर (ret)
		वापस ret;

	ret = xgene_pcie_setup(port);
	अगर (ret)
		वापस ret;

	bridge->sysdata = port;
	bridge->ops = &xgene_pcie_ops;

	वापस pci_host_probe(bridge);
पूर्ण

अटल स्थिर काष्ठा of_device_id xgene_pcie_match_table[] = अणु
	अणु.compatible = "apm,xgene-pcie",पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver xgene_pcie_driver = अणु
	.driver = अणु
		.name = "xgene-pcie",
		.of_match_table = of_match_ptr(xgene_pcie_match_table),
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe = xgene_pcie_probe,
पूर्ण;
builtin_platक्रमm_driver(xgene_pcie_driver);
#पूर्ण_अगर
