<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/*
 * Copyright 2015-2020 Amazon.com, Inc. or its affiliates. All rights reserved.
 */

#अगर_अघोषित ENA_PCI_ID_TBL_H_
#घोषणा ENA_PCI_ID_TBL_H_

#अगर_अघोषित PCI_VENDOR_ID_AMAZON
#घोषणा PCI_VENDOR_ID_AMAZON 0x1d0f
#पूर्ण_अगर

#अगर_अघोषित PCI_DEV_ID_ENA_PF
#घोषणा PCI_DEV_ID_ENA_PF	0x0ec2
#पूर्ण_अगर

#अगर_अघोषित PCI_DEV_ID_ENA_LLQ_PF
#घोषणा PCI_DEV_ID_ENA_LLQ_PF	0x1ec2
#पूर्ण_अगर

#अगर_अघोषित PCI_DEV_ID_ENA_VF
#घोषणा PCI_DEV_ID_ENA_VF	0xec20
#पूर्ण_अगर

#अगर_अघोषित PCI_DEV_ID_ENA_LLQ_VF
#घोषणा PCI_DEV_ID_ENA_LLQ_VF	0xec21
#पूर्ण_अगर

#अगर_अघोषित PCI_DEV_ID_ENA_RESRV0
#घोषणा PCI_DEV_ID_ENA_RESRV0	0x0051
#पूर्ण_अगर

#घोषणा ENA_PCI_ID_TABLE_ENTRY(devid) \
	अणुPCI_DEVICE(PCI_VENDOR_ID_AMAZON, devid)पूर्ण,

अटल स्थिर काष्ठा pci_device_id ena_pci_tbl[] = अणु
	ENA_PCI_ID_TABLE_ENTRY(PCI_DEV_ID_ENA_RESRV0)
	ENA_PCI_ID_TABLE_ENTRY(PCI_DEV_ID_ENA_PF)
	ENA_PCI_ID_TABLE_ENTRY(PCI_DEV_ID_ENA_LLQ_PF)
	ENA_PCI_ID_TABLE_ENTRY(PCI_DEV_ID_ENA_VF)
	ENA_PCI_ID_TABLE_ENTRY(PCI_DEV_ID_ENA_LLQ_VF)
	अणु पूर्ण
पूर्ण;

#पूर्ण_अगर /* ENA_PCI_ID_TBL_H_ */
