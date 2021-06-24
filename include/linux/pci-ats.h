<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित LINUX_PCI_ATS_H
#घोषणा LINUX_PCI_ATS_H

#समावेश <linux/pci.h>

#अगर_घोषित CONFIG_PCI_ATS
/* Address Translation Service */
bool pci_ats_supported(काष्ठा pci_dev *dev);
पूर्णांक pci_enable_ats(काष्ठा pci_dev *dev, पूर्णांक ps);
व्योम pci_disable_ats(काष्ठा pci_dev *dev);
पूर्णांक pci_ats_queue_depth(काष्ठा pci_dev *dev);
पूर्णांक pci_ats_page_aligned(काष्ठा pci_dev *dev);
#अन्यथा /* CONFIG_PCI_ATS */
अटल अंतरभूत bool pci_ats_supported(काष्ठा pci_dev *d)
अणु वापस false; पूर्ण
अटल अंतरभूत पूर्णांक pci_enable_ats(काष्ठा pci_dev *d, पूर्णांक ps)
अणु वापस -ENODEV; पूर्ण
अटल अंतरभूत व्योम pci_disable_ats(काष्ठा pci_dev *d) अणु पूर्ण
अटल अंतरभूत पूर्णांक pci_ats_queue_depth(काष्ठा pci_dev *d)
अणु वापस -ENODEV; पूर्ण
अटल अंतरभूत पूर्णांक pci_ats_page_aligned(काष्ठा pci_dev *dev)
अणु वापस 0; पूर्ण
#पूर्ण_अगर /* CONFIG_PCI_ATS */

#अगर_घोषित CONFIG_PCI_PRI
पूर्णांक pci_enable_pri(काष्ठा pci_dev *pdev, u32 reqs);
व्योम pci_disable_pri(काष्ठा pci_dev *pdev);
पूर्णांक pci_reset_pri(काष्ठा pci_dev *pdev);
पूर्णांक pci_prg_resp_pasid_required(काष्ठा pci_dev *pdev);
bool pci_pri_supported(काष्ठा pci_dev *pdev);
#अन्यथा
अटल अंतरभूत bool pci_pri_supported(काष्ठा pci_dev *pdev)
अणु वापस false; पूर्ण
#पूर्ण_अगर /* CONFIG_PCI_PRI */

#अगर_घोषित CONFIG_PCI_PASID
पूर्णांक pci_enable_pasid(काष्ठा pci_dev *pdev, पूर्णांक features);
व्योम pci_disable_pasid(काष्ठा pci_dev *pdev);
पूर्णांक pci_pasid_features(काष्ठा pci_dev *pdev);
पूर्णांक pci_max_pasids(काष्ठा pci_dev *pdev);
#अन्यथा /* CONFIG_PCI_PASID */
अटल अंतरभूत पूर्णांक pci_enable_pasid(काष्ठा pci_dev *pdev, पूर्णांक features)
अणु वापस -EINVAL; पूर्ण
अटल अंतरभूत व्योम pci_disable_pasid(काष्ठा pci_dev *pdev) अणु पूर्ण
अटल अंतरभूत पूर्णांक pci_pasid_features(काष्ठा pci_dev *pdev)
अणु वापस -EINVAL; पूर्ण
अटल अंतरभूत पूर्णांक pci_max_pasids(काष्ठा pci_dev *pdev)
अणु वापस -EINVAL; पूर्ण
#पूर्ण_अगर /* CONFIG_PCI_PASID */

#पूर्ण_अगर /* LINUX_PCI_ATS_H */
