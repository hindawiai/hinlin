<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * amd8111_edac.h, EDAC defs क्रम AMD8111 hypertransport chip
 *
 * Copyright (c) 2008 Wind River Systems, Inc.
 *
 * Authors:	Cao Qingtao <qingtao.cao@windriver.com>
 * 		Benjamin Walsh <benjamin.walsh@windriver.com>
 * 		Hu Yongqi <yongqi.hu@windriver.com>
 */

#अगर_अघोषित _AMD8111_EDAC_H_
#घोषणा _AMD8111_EDAC_H_

/************************************************************
 *	PCI Bridge Status and Command Register, DevA:0x04
 ************************************************************/
#घोषणा REG_PCI_STSCMD	0x04
क्रमागत pci_stscmd_bits अणु
	PCI_STSCMD_SSE		= BIT(30),
	PCI_STSCMD_RMA		= BIT(29),
	PCI_STSCMD_RTA		= BIT(28),
	PCI_STSCMD_SERREN	= BIT(8),
	PCI_STSCMD_CLEAR_MASK	= (PCI_STSCMD_SSE |
				   PCI_STSCMD_RMA |
				   PCI_STSCMD_RTA)
पूर्ण;

/************************************************************
 *	PCI Bridge Memory Base-Limit Register, DevA:0x1c
 ************************************************************/
#घोषणा REG_MEM_LIM     0x1c
क्रमागत mem_limit_bits अणु
	MEM_LIMIT_DPE   = BIT(31),
	MEM_LIMIT_RSE   = BIT(30),
	MEM_LIMIT_RMA   = BIT(29),
	MEM_LIMIT_RTA   = BIT(28),
	MEM_LIMIT_STA   = BIT(27),
	MEM_LIMIT_MDPE  = BIT(24),
	MEM_LIMIT_CLEAR_MASK  = (MEM_LIMIT_DPE |
				 MEM_LIMIT_RSE |
				 MEM_LIMIT_RMA |
				 MEM_LIMIT_RTA |
				 MEM_LIMIT_STA |
				 MEM_LIMIT_MDPE)
पूर्ण;

/************************************************************
 *	HyperTransport Link Control Register, DevA:0xc4
 ************************************************************/
#घोषणा REG_HT_LINK	0xc4
क्रमागत ht_link_bits अणु
	HT_LINK_LKFAIL	= BIT(4),
	HT_LINK_CRCFEN	= BIT(1),
	HT_LINK_CLEAR_MASK = (HT_LINK_LKFAIL)
पूर्ण;

/************************************************************
 *	PCI Bridge Interrupt and Bridge Control, DevA:0x3c
 ************************************************************/
#घोषणा REG_PCI_INTBRG_CTRL	0x3c
क्रमागत pci_पूर्णांकbrg_ctrl_bits अणु
	PCI_INTBRG_CTRL_DTSERREN	= BIT(27),
	PCI_INTBRG_CTRL_DTSTAT		= BIT(26),
	PCI_INTBRG_CTRL_MARSP		= BIT(21),
	PCI_INTBRG_CTRL_SERREN		= BIT(17),
	PCI_INTBRG_CTRL_PEREN		= BIT(16),
	PCI_INTBRG_CTRL_CLEAR_MASK	= (PCI_INTBRG_CTRL_DTSTAT),
	PCI_INTBRG_CTRL_POLL_MASK	= (PCI_INTBRG_CTRL_DTSERREN |
					   PCI_INTBRG_CTRL_MARSP |
					   PCI_INTBRG_CTRL_SERREN)
पूर्ण;

/************************************************************
 *		I/O Control 1 Register, DevB:0x40
 ************************************************************/
#घोषणा REG_IO_CTRL_1 0x40
क्रमागत io_ctrl_1_bits अणु
	IO_CTRL_1_NMIONERR	= BIT(7),
	IO_CTRL_1_LPC_ERR	= BIT(6),
	IO_CTRL_1_PW2LPC	= BIT(1),
	IO_CTRL_1_CLEAR_MASK	= (IO_CTRL_1_LPC_ERR | IO_CTRL_1_PW2LPC)
पूर्ण;

/************************************************************
 *		Legacy I/O Space Registers
 ************************************************************/
#घोषणा REG_AT_COMPAT 0x61
क्रमागत at_compat_bits अणु
	AT_COMPAT_SERR		= BIT(7),
	AT_COMPAT_IOCHK		= BIT(6),
	AT_COMPAT_CLRIOCHK	= BIT(3),
	AT_COMPAT_CLRSERR	= BIT(2),
पूर्ण;

काष्ठा amd8111_dev_info अणु
	u16 err_dev;	/* PCI Device ID */
	काष्ठा pci_dev *dev;
	पूर्णांक edac_idx;	/* device index */
	अक्षर *ctl_name;
	काष्ठा edac_device_ctl_info *edac_dev;
	व्योम (*init)(काष्ठा amd8111_dev_info *dev_info);
	व्योम (*निकास)(काष्ठा amd8111_dev_info *dev_info);
	व्योम (*check)(काष्ठा edac_device_ctl_info *edac_dev);
पूर्ण;

काष्ठा amd8111_pci_info अणु
	u16 err_dev;	/* PCI Device ID */
	काष्ठा pci_dev *dev;
	पूर्णांक edac_idx;	/* pci index */
	स्थिर अक्षर *ctl_name;
	काष्ठा edac_pci_ctl_info *edac_dev;
	व्योम (*init)(काष्ठा amd8111_pci_info *dev_info);
	व्योम (*निकास)(काष्ठा amd8111_pci_info *dev_info);
	व्योम (*check)(काष्ठा edac_pci_ctl_info *edac_dev);
पूर्ण;

#पूर्ण_अगर /* _AMD8111_EDAC_H_ */
