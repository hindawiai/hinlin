<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * File		pci-acpi.h
 *
 * Copyright (C) 2004 Intel
 * Copyright (C) Tom Long Nguyen (tom.l.nguyen@पूर्णांकel.com)
 */

#अगर_अघोषित _PCI_ACPI_H_
#घोषणा _PCI_ACPI_H_

#समावेश <linux/acpi.h>

#अगर_घोषित CONFIG_ACPI
बाह्य acpi_status pci_acpi_add_bus_pm_notअगरier(काष्ठा acpi_device *dev);
अटल अंतरभूत acpi_status pci_acpi_हटाओ_bus_pm_notअगरier(काष्ठा acpi_device *dev)
अणु
	वापस acpi_हटाओ_pm_notअगरier(dev);
पूर्ण
बाह्य acpi_status pci_acpi_add_pm_notअगरier(काष्ठा acpi_device *dev,
					     काष्ठा pci_dev *pci_dev);
अटल अंतरभूत acpi_status pci_acpi_हटाओ_pm_notअगरier(काष्ठा acpi_device *dev)
अणु
	वापस acpi_हटाओ_pm_notअगरier(dev);
पूर्ण
बाह्य phys_addr_t acpi_pci_root_get_mcfg_addr(acpi_handle handle);

काष्ठा pci_ecam_ops;
बाह्य पूर्णांक pci_mcfg_lookup(काष्ठा acpi_pci_root *root, काष्ठा resource *cfgres,
			   स्थिर काष्ठा pci_ecam_ops **ecam_ops);

अटल अंतरभूत acpi_handle acpi_find_root_bridge_handle(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pci_bus *pbus = pdev->bus;

	/* Find a PCI root bus */
	जबतक (!pci_is_root_bus(pbus))
		pbus = pbus->parent;

	वापस ACPI_HANDLE(pbus->bridge);
पूर्ण

अटल अंतरभूत acpi_handle acpi_pci_get_bridge_handle(काष्ठा pci_bus *pbus)
अणु
	काष्ठा device *dev;

	अगर (pci_is_root_bus(pbus))
		dev = pbus->bridge;
	अन्यथा अणु
		/* If pbus is a भव bus, there is no bridge to it */
		अगर (!pbus->self)
			वापस शून्य;

		dev = &pbus->self->dev;
	पूर्ण

	वापस ACPI_HANDLE(dev);
पूर्ण

काष्ठा acpi_pci_root;
काष्ठा acpi_pci_root_ops;

काष्ठा acpi_pci_root_info अणु
	काष्ठा acpi_pci_root		*root;
	काष्ठा acpi_device		*bridge;
	काष्ठा acpi_pci_root_ops	*ops;
	काष्ठा list_head		resources;
	अक्षर				name[16];
पूर्ण;

काष्ठा acpi_pci_root_ops अणु
	काष्ठा pci_ops *pci_ops;
	पूर्णांक (*init_info)(काष्ठा acpi_pci_root_info *info);
	व्योम (*release_info)(काष्ठा acpi_pci_root_info *info);
	पूर्णांक (*prepare_resources)(काष्ठा acpi_pci_root_info *info);
पूर्ण;

बाह्य पूर्णांक acpi_pci_probe_root_resources(काष्ठा acpi_pci_root_info *info);
बाह्य काष्ठा pci_bus *acpi_pci_root_create(काष्ठा acpi_pci_root *root,
					    काष्ठा acpi_pci_root_ops *ops,
					    काष्ठा acpi_pci_root_info *info,
					    व्योम *sd);

व्योम acpi_pci_add_bus(काष्ठा pci_bus *bus);
व्योम acpi_pci_हटाओ_bus(काष्ठा pci_bus *bus);

#अगर_घोषित	CONFIG_ACPI_PCI_SLOT
व्योम acpi_pci_slot_init(व्योम);
व्योम acpi_pci_slot_क्रमागतerate(काष्ठा pci_bus *bus);
व्योम acpi_pci_slot_हटाओ(काष्ठा pci_bus *bus);
#अन्यथा
अटल अंतरभूत व्योम acpi_pci_slot_init(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम acpi_pci_slot_क्रमागतerate(काष्ठा pci_bus *bus) अणु पूर्ण
अटल अंतरभूत व्योम acpi_pci_slot_हटाओ(काष्ठा pci_bus *bus) अणु पूर्ण
#पूर्ण_अगर

#अगर_घोषित	CONFIG_HOTPLUG_PCI_ACPI
व्योम acpiphp_init(व्योम);
व्योम acpiphp_क्रमागतerate_slots(काष्ठा pci_bus *bus);
व्योम acpiphp_हटाओ_slots(काष्ठा pci_bus *bus);
व्योम acpiphp_check_host_bridge(काष्ठा acpi_device *adev);
#अन्यथा
अटल अंतरभूत व्योम acpiphp_init(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम acpiphp_क्रमागतerate_slots(काष्ठा pci_bus *bus) अणु पूर्ण
अटल अंतरभूत व्योम acpiphp_हटाओ_slots(काष्ठा pci_bus *bus) अणु पूर्ण
अटल अंतरभूत व्योम acpiphp_check_host_bridge(काष्ठा acpi_device *adev) अणु पूर्ण
#पूर्ण_अगर

बाह्य स्थिर guid_t pci_acpi_dsm_guid;

/* _DSM Definitions क्रम PCI */
#घोषणा DSM_PCI_PRESERVE_BOOT_CONFIG		0x05
#घोषणा DSM_PCI_DEVICE_NAME			0x07
#घोषणा DSM_PCI_POWER_ON_RESET_DELAY		0x08
#घोषणा DSM_PCI_DEVICE_READINESS_DURATIONS	0x09

#अगर_घोषित CONFIG_PCIE_EDR
व्योम pci_acpi_add_edr_notअगरier(काष्ठा pci_dev *pdev);
व्योम pci_acpi_हटाओ_edr_notअगरier(काष्ठा pci_dev *pdev);
#अन्यथा
अटल अंतरभूत व्योम pci_acpi_add_edr_notअगरier(काष्ठा pci_dev *pdev) अणु पूर्ण
अटल अंतरभूत व्योम pci_acpi_हटाओ_edr_notअगरier(काष्ठा pci_dev *pdev) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_PCIE_EDR */

#अन्यथा	/* CONFIG_ACPI */
अटल अंतरभूत व्योम acpi_pci_add_bus(काष्ठा pci_bus *bus) अणु पूर्ण
अटल अंतरभूत व्योम acpi_pci_हटाओ_bus(काष्ठा pci_bus *bus) अणु पूर्ण
#पूर्ण_अगर	/* CONFIG_ACPI */

#पूर्ण_अगर	/* _PCI_ACPI_H_ */
