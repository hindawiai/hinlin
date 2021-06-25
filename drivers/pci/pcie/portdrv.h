<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Purpose:	PCI Express Port Bus Driver's Internal Data Structures
 *
 * Copyright (C) 2004 Intel
 * Copyright (C) Tom Long Nguyen (tom.l.nguyen@पूर्णांकel.com)
 */

#अगर_अघोषित _PORTDRV_H_
#घोषणा _PORTDRV_H_

#समावेश <linux/compiler.h>

/* Service Type */
#घोषणा PCIE_PORT_SERVICE_PME_SHIFT	0	/* Power Management Event */
#घोषणा PCIE_PORT_SERVICE_PME		(1 << PCIE_PORT_SERVICE_PME_SHIFT)
#घोषणा PCIE_PORT_SERVICE_AER_SHIFT	1	/* Advanced Error Reporting */
#घोषणा PCIE_PORT_SERVICE_AER		(1 << PCIE_PORT_SERVICE_AER_SHIFT)
#घोषणा PCIE_PORT_SERVICE_HP_SHIFT	2	/* Native Hotplug */
#घोषणा PCIE_PORT_SERVICE_HP		(1 << PCIE_PORT_SERVICE_HP_SHIFT)
#घोषणा PCIE_PORT_SERVICE_DPC_SHIFT	3	/* Downstream Port Containment */
#घोषणा PCIE_PORT_SERVICE_DPC		(1 << PCIE_PORT_SERVICE_DPC_SHIFT)
#घोषणा PCIE_PORT_SERVICE_BWNOTIF_SHIFT	4	/* Bandwidth notअगरication */
#घोषणा PCIE_PORT_SERVICE_BWNOTIF	(1 << PCIE_PORT_SERVICE_BWNOTIF_SHIFT)

#घोषणा PCIE_PORT_DEVICE_MAXSERVICES   5

बाह्य bool pcie_ports_dpc_native;

#अगर_घोषित CONFIG_PCIEAER
पूर्णांक pcie_aer_init(व्योम);
पूर्णांक pcie_aer_is_native(काष्ठा pci_dev *dev);
#अन्यथा
अटल अंतरभूत पूर्णांक pcie_aer_init(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक pcie_aer_is_native(काष्ठा pci_dev *dev) अणु वापस 0; पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_HOTPLUG_PCI_PCIE
पूर्णांक pcie_hp_init(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक pcie_hp_init(व्योम) अणु वापस 0; पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PCIE_PME
पूर्णांक pcie_pme_init(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक pcie_pme_init(व्योम) अणु वापस 0; पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PCIE_DPC
पूर्णांक pcie_dpc_init(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक pcie_dpc_init(व्योम) अणु वापस 0; पूर्ण
#पूर्ण_अगर

/* Port Type */
#घोषणा PCIE_ANY_PORT			(~0)

काष्ठा pcie_device अणु
	पूर्णांक		irq;	    /* Service IRQ/MSI/MSI-X Vector */
	काष्ठा pci_dev *port;	    /* Root/Upstream/Downstream Port */
	u32		service;    /* Port service this device represents */
	व्योम		*priv_data; /* Service Private Data */
	काष्ठा device	device;     /* Generic Device Interface */
पूर्ण;
#घोषणा to_pcie_device(d) container_of(d, काष्ठा pcie_device, device)

अटल अंतरभूत व्योम set_service_data(काष्ठा pcie_device *dev, व्योम *data)
अणु
	dev->priv_data = data;
पूर्ण

अटल अंतरभूत व्योम *get_service_data(काष्ठा pcie_device *dev)
अणु
	वापस dev->priv_data;
पूर्ण

काष्ठा pcie_port_service_driver अणु
	स्थिर अक्षर *name;
	पूर्णांक (*probe)(काष्ठा pcie_device *dev);
	व्योम (*हटाओ)(काष्ठा pcie_device *dev);
	पूर्णांक (*suspend)(काष्ठा pcie_device *dev);
	पूर्णांक (*resume_noirq)(काष्ठा pcie_device *dev);
	पूर्णांक (*resume)(काष्ठा pcie_device *dev);
	पूर्णांक (*runसमय_suspend)(काष्ठा pcie_device *dev);
	पूर्णांक (*runसमय_resume)(काष्ठा pcie_device *dev);

	/* Device driver may resume normal operations */
	व्योम (*error_resume)(काष्ठा pci_dev *dev);

	पूर्णांक port_type;  /* Type of the port this driver can handle */
	u32 service;    /* Port service this device represents */

	काष्ठा device_driver driver;
पूर्ण;
#घोषणा to_service_driver(d) \
	container_of(d, काष्ठा pcie_port_service_driver, driver)

पूर्णांक pcie_port_service_रेजिस्टर(काष्ठा pcie_port_service_driver *new);
व्योम pcie_port_service_unरेजिस्टर(काष्ठा pcie_port_service_driver *new);

/*
 * The PCIe Capability Interrupt Message Number (PCIe r3.1, sec 7.8.2) must
 * be one of the first 32 MSI-X entries.  Per PCI r3.0, sec 6.8.3.1, MSI
 * supports a maximum of 32 vectors per function.
 */
#घोषणा PCIE_PORT_MAX_MSI_ENTRIES	32

#घोषणा get_descriptor_id(type, service) (((type - 4) << 8) | service)

बाह्य काष्ठा bus_type pcie_port_bus_type;
पूर्णांक pcie_port_device_रेजिस्टर(काष्ठा pci_dev *dev);
#अगर_घोषित CONFIG_PM
पूर्णांक pcie_port_device_suspend(काष्ठा device *dev);
पूर्णांक pcie_port_device_resume_noirq(काष्ठा device *dev);
पूर्णांक pcie_port_device_resume(काष्ठा device *dev);
पूर्णांक pcie_port_device_runसमय_suspend(काष्ठा device *dev);
पूर्णांक pcie_port_device_runसमय_resume(काष्ठा device *dev);
#पूर्ण_अगर
व्योम pcie_port_device_हटाओ(काष्ठा pci_dev *dev);
पूर्णांक __must_check pcie_port_bus_रेजिस्टर(व्योम);
व्योम pcie_port_bus_unरेजिस्टर(व्योम);

काष्ठा pci_dev;

#अगर_घोषित CONFIG_PCIE_PME
बाह्य bool pcie_pme_msi_disabled;

अटल अंतरभूत व्योम pcie_pme_disable_msi(व्योम)
अणु
	pcie_pme_msi_disabled = true;
पूर्ण

अटल अंतरभूत bool pcie_pme_no_msi(व्योम)
अणु
	वापस pcie_pme_msi_disabled;
पूर्ण

व्योम pcie_pme_पूर्णांकerrupt_enable(काष्ठा pci_dev *dev, bool enable);
#अन्यथा /* !CONFIG_PCIE_PME */
अटल अंतरभूत व्योम pcie_pme_disable_msi(व्योम) अणुपूर्ण
अटल अंतरभूत bool pcie_pme_no_msi(व्योम) अणु वापस false; पूर्ण
अटल अंतरभूत व्योम pcie_pme_पूर्णांकerrupt_enable(काष्ठा pci_dev *dev, bool en) अणुपूर्ण
#पूर्ण_अगर /* !CONFIG_PCIE_PME */

काष्ठा device *pcie_port_find_device(काष्ठा pci_dev *dev, u32 service);
#पूर्ण_अगर /* _PORTDRV_H_ */
