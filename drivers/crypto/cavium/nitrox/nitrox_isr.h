<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __NITROX_ISR_H
#घोषणा __NITROX_ISR_H

#समावेश "nitrox_dev.h"

पूर्णांक nitrox_रेजिस्टर_पूर्णांकerrupts(काष्ठा nitrox_device *ndev);
व्योम nitrox_unरेजिस्टर_पूर्णांकerrupts(काष्ठा nitrox_device *ndev);
पूर्णांक nitrox_sriov_रेजिस्टर_पूर्णांकerupts(काष्ठा nitrox_device *ndev);
व्योम nitrox_sriov_unरेजिस्टर_पूर्णांकerrupts(काष्ठा nitrox_device *ndev);

#अगर_घोषित CONFIG_PCI_IOV
पूर्णांक nitrox_sriov_configure(काष्ठा pci_dev *pdev, पूर्णांक num_vfs);
#अन्यथा
अटल अंतरभूत पूर्णांक nitrox_sriov_configure(काष्ठा pci_dev *pdev, पूर्णांक num_vfs)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __NITROX_ISR_H */
