<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/* Copyright (c) 2016-2018 Mellanox Technologies. All rights reserved */

#अगर_अघोषित _MLXSW_PCI_H
#घोषणा _MLXSW_PCI_H

#समावेश <linux/pci.h>

#घोषणा PCI_DEVICE_ID_MELLANOX_SWITCHX2		0xc738
#घोषणा PCI_DEVICE_ID_MELLANOX_SPECTRUM		0xcb84
#घोषणा PCI_DEVICE_ID_MELLANOX_SPECTRUM2	0xcf6c
#घोषणा PCI_DEVICE_ID_MELLANOX_SPECTRUM3	0xcf70
#घोषणा PCI_DEVICE_ID_MELLANOX_SWITCHIB		0xcb20
#घोषणा PCI_DEVICE_ID_MELLANOX_SWITCHIB2	0xcf08

#अगर IS_ENABLED(CONFIG_MLXSW_PCI)

पूर्णांक mlxsw_pci_driver_रेजिस्टर(काष्ठा pci_driver *pci_driver);
व्योम mlxsw_pci_driver_unरेजिस्टर(काष्ठा pci_driver *pci_driver);

#अन्यथा

अटल अंतरभूत पूर्णांक
mlxsw_pci_driver_रेजिस्टर(काष्ठा pci_driver *pci_driver)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम
mlxsw_pci_driver_unरेजिस्टर(काष्ठा pci_driver *pci_driver)
अणु
पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर
