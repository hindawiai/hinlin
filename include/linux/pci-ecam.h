<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright 2016 Broadcom
 */
#अगर_अघोषित DRIVERS_PCI_ECAM_H
#घोषणा DRIVERS_PCI_ECAM_H

#समावेश <linux/pci.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>

/*
 * Memory address shअगरt values क्रम the byte-level address that
 * can be used when accessing the PCI Express Configuration Space.
 */

/*
 * Enhanced Configuration Access Mechanism (ECAM)
 *
 * See PCI Express Base Specअगरication, Revision 5.0, Version 1.0,
 * Section 7.2.2, Table 7-1, p. 677.
 */
#घोषणा PCIE_ECAM_BUS_SHIFT	20 /* Bus number */
#घोषणा PCIE_ECAM_DEVFN_SHIFT	12 /* Device and Function number */

#घोषणा PCIE_ECAM_BUS_MASK	0xff
#घोषणा PCIE_ECAM_DEVFN_MASK	0xff
#घोषणा PCIE_ECAM_REG_MASK	0xfff /* Limit offset to a maximum of 4K */

#घोषणा PCIE_ECAM_BUS(x)	(((x) & PCIE_ECAM_BUS_MASK) << PCIE_ECAM_BUS_SHIFT)
#घोषणा PCIE_ECAM_DEVFN(x)	(((x) & PCIE_ECAM_DEVFN_MASK) << PCIE_ECAM_DEVFN_SHIFT)
#घोषणा PCIE_ECAM_REG(x)	((x) & PCIE_ECAM_REG_MASK)

#घोषणा PCIE_ECAM_OFFSET(bus, devfn, where) \
	(PCIE_ECAM_BUS(bus) | \
	 PCIE_ECAM_DEVFN(devfn) | \
	 PCIE_ECAM_REG(where))

/*
 * काष्ठा to hold pci ops and bus shअगरt of the config winकरोw
 * क्रम a PCI controller.
 */
काष्ठा pci_config_winकरोw;
काष्ठा pci_ecam_ops अणु
	अचिन्हित पूर्णांक			bus_shअगरt;
	काष्ठा pci_ops			pci_ops;
	पूर्णांक				(*init)(काष्ठा pci_config_winकरोw *);
पूर्ण;

/*
 * काष्ठा to hold the mappings of a config space winकरोw. This
 * is expected to be used as sysdata क्रम PCI controllers that
 * use ECAM.
 */
काष्ठा pci_config_winकरोw अणु
	काष्ठा resource			res;
	काष्ठा resource			busr;
	व्योम				*priv;
	स्थिर काष्ठा pci_ecam_ops	*ops;
	जोड़ अणु
		व्योम __iomem		*win;	/* 64-bit single mapping */
		व्योम __iomem		**winp; /* 32-bit per-bus mapping */
	पूर्ण;
	काष्ठा device			*parent;/* ECAM res was from this dev */
पूर्ण;

/* create and मुक्त pci_config_winकरोw */
काष्ठा pci_config_winकरोw *pci_ecam_create(काष्ठा device *dev,
		काष्ठा resource *cfgres, काष्ठा resource *busr,
		स्थिर काष्ठा pci_ecam_ops *ops);
व्योम pci_ecam_मुक्त(काष्ठा pci_config_winकरोw *cfg);

/* map_bus when ->sysdata is an instance of pci_config_winकरोw */
व्योम __iomem *pci_ecam_map_bus(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
			       पूर्णांक where);
/* शेष ECAM ops */
बाह्य स्थिर काष्ठा pci_ecam_ops pci_generic_ecam_ops;

#अगर defined(CONFIG_ACPI) && defined(CONFIG_PCI_QUIRKS)
बाह्य स्थिर काष्ठा pci_ecam_ops pci_32b_ops;	/* 32-bit accesses only */
बाह्य स्थिर काष्ठा pci_ecam_ops pci_32b_पढ़ो_ops; /* 32-bit पढ़ो only */
बाह्य स्थिर काष्ठा pci_ecam_ops hisi_pcie_ops;	/* HiSilicon */
बाह्य स्थिर काष्ठा pci_ecam_ops thunder_pem_ecam_ops; /* Cavium ThunderX 1.x & 2.x */
बाह्य स्थिर काष्ठा pci_ecam_ops pci_thunder_ecam_ops; /* Cavium ThunderX 1.x */
बाह्य स्थिर काष्ठा pci_ecam_ops xgene_v1_pcie_ecam_ops; /* APM X-Gene PCIe v1 */
बाह्य स्थिर काष्ठा pci_ecam_ops xgene_v2_pcie_ecam_ops; /* APM X-Gene PCIe v2.x */
बाह्य स्थिर काष्ठा pci_ecam_ops al_pcie_ops;	/* Amazon Annapurna Lअसल PCIe */
बाह्य स्थिर काष्ठा pci_ecam_ops tegra194_pcie_ops; /* Tegra194 PCIe */
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_PCI_HOST_COMMON)
/* क्रम DT-based PCI controllers that support ECAM */
पूर्णांक pci_host_common_probe(काष्ठा platक्रमm_device *pdev);
पूर्णांक pci_host_common_हटाओ(काष्ठा platक्रमm_device *pdev);
#पूर्ण_अगर
#पूर्ण_अगर
