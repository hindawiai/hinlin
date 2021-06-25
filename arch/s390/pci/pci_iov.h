<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright IBM Corp. 2020
 *
 * Author(s):
 *   Niklas Schnelle <schnelle@linux.ibm.com>
 *
 */

#अगर_अघोषित __S390_PCI_IOV_H
#घोषणा __S390_PCI_IOV_H

#अगर_घोषित CONFIG_PCI_IOV
व्योम zpci_iov_हटाओ_virtfn(काष्ठा pci_dev *pdev, पूर्णांक vfn);

व्योम zpci_iov_map_resources(काष्ठा pci_dev *pdev);

पूर्णांक zpci_iov_setup_virtfn(काष्ठा zpci_bus *zbus, काष्ठा pci_dev *virtfn, पूर्णांक vfn);

#अन्यथा /* CONFIG_PCI_IOV */
अटल अंतरभूत व्योम zpci_iov_हटाओ_virtfn(काष्ठा pci_dev *pdev, पूर्णांक vfn) अणुपूर्ण

अटल अंतरभूत व्योम zpci_iov_map_resources(काष्ठा pci_dev *pdev) अणुपूर्ण

अटल अंतरभूत पूर्णांक zpci_iov_setup_virtfn(काष्ठा zpci_bus *zbus, काष्ठा pci_dev *virtfn, पूर्णांक vfn)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PCI_IOV */
#पूर्ण_अगर /* __S390_PCI_IOV_h */
