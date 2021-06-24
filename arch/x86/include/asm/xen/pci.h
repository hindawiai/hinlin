<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_XEN_PCI_H
#घोषणा _ASM_X86_XEN_PCI_H

#अगर defined(CONFIG_PCI_XEN)
बाह्य पूर्णांक __init pci_xen_init(व्योम);
बाह्य पूर्णांक __init pci_xen_hvm_init(व्योम);
#घोषणा pci_xen 1
#अन्यथा
#घोषणा pci_xen 0
#घोषणा pci_xen_init (0)
अटल अंतरभूत पूर्णांक pci_xen_hvm_init(व्योम)
अणु
	वापस -1;
पूर्ण
#पूर्ण_अगर
#अगर defined(CONFIG_XEN_DOM0)
पूर्णांक __init pci_xen_initial_करोमुख्य(व्योम);
पूर्णांक xen_find_device_करोमुख्य_owner(काष्ठा pci_dev *dev);
पूर्णांक xen_रेजिस्टर_device_करोमुख्य_owner(काष्ठा pci_dev *dev, uपूर्णांक16_t करोमुख्य);
पूर्णांक xen_unरेजिस्टर_device_करोमुख्य_owner(काष्ठा pci_dev *dev);
#अन्यथा
अटल अंतरभूत पूर्णांक __init pci_xen_initial_करोमुख्य(व्योम)
अणु
	वापस -1;
पूर्ण
अटल अंतरभूत पूर्णांक xen_find_device_करोमुख्य_owner(काष्ठा pci_dev *dev)
अणु
	वापस -1;
पूर्ण
अटल अंतरभूत पूर्णांक xen_रेजिस्टर_device_करोमुख्य_owner(काष्ठा pci_dev *dev,
						   uपूर्णांक16_t करोमुख्य)
अणु
	वापस -1;
पूर्ण
अटल अंतरभूत पूर्णांक xen_unरेजिस्टर_device_करोमुख्य_owner(काष्ठा pci_dev *dev)
अणु
	वापस -1;
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_PCI_MSI)
#अगर defined(CONFIG_PCI_XEN)
/* The drivers/pci/xen-pcअगरront.c sets this काष्ठाure to
 * its own functions.
 */
काष्ठा xen_pci_frontend_ops अणु
	पूर्णांक (*enable_msi)(काष्ठा pci_dev *dev, पूर्णांक vectors[]);
	व्योम (*disable_msi)(काष्ठा pci_dev *dev);
	पूर्णांक (*enable_msix)(काष्ठा pci_dev *dev, पूर्णांक vectors[], पूर्णांक nvec);
	व्योम (*disable_msix)(काष्ठा pci_dev *dev);
पूर्ण;

बाह्य काष्ठा xen_pci_frontend_ops *xen_pci_frontend;

अटल अंतरभूत पूर्णांक xen_pci_frontend_enable_msi(काष्ठा pci_dev *dev,
					      पूर्णांक vectors[])
अणु
	अगर (xen_pci_frontend && xen_pci_frontend->enable_msi)
		वापस xen_pci_frontend->enable_msi(dev, vectors);
	वापस -ENOSYS;
पूर्ण
अटल अंतरभूत व्योम xen_pci_frontend_disable_msi(काष्ठा pci_dev *dev)
अणु
	अगर (xen_pci_frontend && xen_pci_frontend->disable_msi)
			xen_pci_frontend->disable_msi(dev);
पूर्ण
अटल अंतरभूत पूर्णांक xen_pci_frontend_enable_msix(काष्ठा pci_dev *dev,
					       पूर्णांक vectors[], पूर्णांक nvec)
अणु
	अगर (xen_pci_frontend && xen_pci_frontend->enable_msix)
		वापस xen_pci_frontend->enable_msix(dev, vectors, nvec);
	वापस -ENOSYS;
पूर्ण
अटल अंतरभूत व्योम xen_pci_frontend_disable_msix(काष्ठा pci_dev *dev)
अणु
	अगर (xen_pci_frontend && xen_pci_frontend->disable_msix)
			xen_pci_frontend->disable_msix(dev);
पूर्ण
#पूर्ण_अगर /* CONFIG_PCI_XEN */
#पूर्ण_अगर /* CONFIG_PCI_MSI */

#पूर्ण_अगर	/* _ASM_X86_XEN_PCI_H */
