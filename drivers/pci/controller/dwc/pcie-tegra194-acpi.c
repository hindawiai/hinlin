<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * ACPI quirks क्रम Tegra194 PCIe host controller
 *
 * Copyright (C) 2021 NVIDIA Corporation.
 *
 * Author: Vidya Sagar <vidyas@nvidia.com>
 */

#समावेश <linux/pci.h>
#समावेश <linux/pci-acpi.h>
#समावेश <linux/pci-ecam.h>

#समावेश "pcie-designware.h"

काष्ठा tegra194_pcie_ecam  अणु
	व्योम __iomem *config_base;
	व्योम __iomem *iatu_base;
	व्योम __iomem *dbi_base;
पूर्ण;

अटल पूर्णांक tegra194_acpi_init(काष्ठा pci_config_winकरोw *cfg)
अणु
	काष्ठा device *dev = cfg->parent;
	काष्ठा tegra194_pcie_ecam *pcie_ecam;

	pcie_ecam = devm_kzalloc(dev, माप(*pcie_ecam), GFP_KERNEL);
	अगर (!pcie_ecam)
		वापस -ENOMEM;

	pcie_ecam->config_base = cfg->win;
	pcie_ecam->iatu_base = cfg->win + SZ_256K;
	pcie_ecam->dbi_base = cfg->win + SZ_512K;
	cfg->priv = pcie_ecam;

	वापस 0;
पूर्ण

अटल व्योम atu_reg_ग_लिखो(काष्ठा tegra194_pcie_ecam *pcie_ecam, पूर्णांक index,
			  u32 val, u32 reg)
अणु
	u32 offset = PCIE_GET_ATU_OUTB_UNR_REG_OFFSET(index);

	ग_लिखोl(val, pcie_ecam->iatu_base + offset + reg);
पूर्ण

अटल व्योम program_outbound_atu(काष्ठा tegra194_pcie_ecam *pcie_ecam,
				 पूर्णांक index, पूर्णांक type, u64 cpu_addr,
				 u64 pci_addr, u64 size)
अणु
	atu_reg_ग_लिखो(pcie_ecam, index, lower_32_bits(cpu_addr),
		      PCIE_ATU_LOWER_BASE);
	atu_reg_ग_लिखो(pcie_ecam, index, upper_32_bits(cpu_addr),
		      PCIE_ATU_UPPER_BASE);
	atu_reg_ग_लिखो(pcie_ecam, index, lower_32_bits(pci_addr),
		      PCIE_ATU_LOWER_TARGET);
	atu_reg_ग_लिखो(pcie_ecam, index, lower_32_bits(cpu_addr + size - 1),
		      PCIE_ATU_LIMIT);
	atu_reg_ग_लिखो(pcie_ecam, index, upper_32_bits(pci_addr),
		      PCIE_ATU_UPPER_TARGET);
	atu_reg_ग_लिखो(pcie_ecam, index, type, PCIE_ATU_CR1);
	atu_reg_ग_लिखो(pcie_ecam, index, PCIE_ATU_ENABLE, PCIE_ATU_CR2);
पूर्ण

अटल व्योम __iomem *tegra194_map_bus(काष्ठा pci_bus *bus,
				      अचिन्हित पूर्णांक devfn, पूर्णांक where)
अणु
	काष्ठा pci_config_winकरोw *cfg = bus->sysdata;
	काष्ठा tegra194_pcie_ecam *pcie_ecam = cfg->priv;
	u32 busdev;
	पूर्णांक type;

	अगर (bus->number < cfg->busr.start || bus->number > cfg->busr.end)
		वापस शून्य;

	अगर (bus->number == cfg->busr.start) अणु
		अगर (PCI_SLOT(devfn) == 0)
			वापस pcie_ecam->dbi_base + where;
		अन्यथा
			वापस शून्य;
	पूर्ण

	busdev = PCIE_ATU_BUS(bus->number) | PCIE_ATU_DEV(PCI_SLOT(devfn)) |
		 PCIE_ATU_FUNC(PCI_FUNC(devfn));

	अगर (bus->parent->number == cfg->busr.start) अणु
		अगर (PCI_SLOT(devfn) == 0)
			type = PCIE_ATU_TYPE_CFG0;
		अन्यथा
			वापस शून्य;
	पूर्ण अन्यथा अणु
		type = PCIE_ATU_TYPE_CFG1;
	पूर्ण

	program_outbound_atu(pcie_ecam, 0, type, cfg->res.start, busdev,
			     SZ_256K);

	वापस pcie_ecam->config_base + where;
पूर्ण

स्थिर काष्ठा pci_ecam_ops tegra194_pcie_ops = अणु
	.init		= tegra194_acpi_init,
	.pci_ops	= अणु
		.map_bus	= tegra194_map_bus,
		.पढ़ो		= pci_generic_config_पढ़ो,
		.ग_लिखो		= pci_generic_config_ग_लिखो,
	पूर्ण
पूर्ण;
