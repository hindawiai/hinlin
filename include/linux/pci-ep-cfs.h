<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/**
 * PCI Endpoपूर्णांक ConfigFS header file
 *
 * Copyright (C) 2017 Texas Instruments
 * Author: Kishon Vijay Abraham I <kishon@ti.com>
 */

#अगर_अघोषित __LINUX_PCI_EP_CFS_H
#घोषणा __LINUX_PCI_EP_CFS_H

#समावेश <linux/configfs.h>

#अगर_घोषित CONFIG_PCI_ENDPOINT_CONFIGFS
काष्ठा config_group *pci_ep_cfs_add_epc_group(स्थिर अक्षर *name);
व्योम pci_ep_cfs_हटाओ_epc_group(काष्ठा config_group *group);
काष्ठा config_group *pci_ep_cfs_add_epf_group(स्थिर अक्षर *name);
व्योम pci_ep_cfs_हटाओ_epf_group(काष्ठा config_group *group);
#अन्यथा
अटल अंतरभूत काष्ठा config_group *pci_ep_cfs_add_epc_group(स्थिर अक्षर *name)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम pci_ep_cfs_हटाओ_epc_group(काष्ठा config_group *group)
अणु
पूर्ण

अटल अंतरभूत काष्ठा config_group *pci_ep_cfs_add_epf_group(स्थिर अक्षर *name)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम pci_ep_cfs_हटाओ_epf_group(काष्ठा config_group *group)
अणु
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* __LINUX_PCI_EP_CFS_H */
