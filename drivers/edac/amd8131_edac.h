<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * amd8131_edac.h, EDAC defs क्रम AMD8131 hypertransport chip
 *
 * Copyright (c) 2008 Wind River Systems, Inc.
 *
 * Authors:	Cao Qingtao <qingtao.cao@windriver.com>
 * 		Benjamin Walsh <benjamin.walsh@windriver.com>
 * 		Hu Yongqi <yongqi.hu@windriver.com>
 */

#अगर_अघोषित _AMD8131_EDAC_H_
#घोषणा _AMD8131_EDAC_H_

#घोषणा DEVFN_PCIX_BRIDGE_NORTH_A	8
#घोषणा DEVFN_PCIX_BRIDGE_NORTH_B	16
#घोषणा DEVFN_PCIX_BRIDGE_SOUTH_A	24
#घोषणा DEVFN_PCIX_BRIDGE_SOUTH_B	32

/************************************************************
 *	PCI-X Bridge Status and Command Register, DevA:0x04
 ************************************************************/
#घोषणा REG_STS_CMD	0x04
क्रमागत sts_cmd_bits अणु
	STS_CMD_SSE	= BIT(30),
	STS_CMD_SERREN	= BIT(8)
पूर्ण;

/************************************************************
 *	PCI-X Bridge Interrupt and Bridge Control Register,
 ************************************************************/
#घोषणा REG_INT_CTLR	0x3c
क्रमागत पूर्णांक_ctlr_bits अणु
	INT_CTLR_DTSE	= BIT(27),
	INT_CTLR_DTS	= BIT(26),
	INT_CTLR_SERR	= BIT(17),
	INT_CTLR_PERR	= BIT(16)
पूर्ण;

/************************************************************
 *	PCI-X Bridge Memory Base-Limit Register, DevA:0x1C
 ************************************************************/
#घोषणा REG_MEM_LIM	0x1c
क्रमागत mem_limit_bits अणु
	MEM_LIMIT_DPE 	= BIT(31),
	MEM_LIMIT_RSE 	= BIT(30),
	MEM_LIMIT_RMA 	= BIT(29),
	MEM_LIMIT_RTA 	= BIT(28),
	MEM_LIMIT_STA	= BIT(27),
	MEM_LIMIT_MDPE	= BIT(24),
	MEM_LIMIT_MASK	= MEM_LIMIT_DPE|MEM_LIMIT_RSE|MEM_LIMIT_RMA|
				MEM_LIMIT_RTA|MEM_LIMIT_STA|MEM_LIMIT_MDPE
पूर्ण;

/************************************************************
 *	Link Configuration And Control Register, side A
 ************************************************************/
#घोषणा REG_LNK_CTRL_A	0xc4

/************************************************************
 *	Link Configuration And Control Register, side B
 ************************************************************/
#घोषणा REG_LNK_CTRL_B  0xc8

क्रमागत lnk_ctrl_bits अणु
	LNK_CTRL_CRCERR_A	= BIT(9),
	LNK_CTRL_CRCERR_B	= BIT(8),
	LNK_CTRL_CRCFEN		= BIT(1)
पूर्ण;

क्रमागत pcix_bridge_inst अणु
	NORTH_A = 0,
	NORTH_B = 1,
	SOUTH_A = 2,
	SOUTH_B = 3,
	NO_BRIDGE = 4
पूर्ण;

काष्ठा amd8131_dev_info अणु
	पूर्णांक devfn;
	क्रमागत pcix_bridge_inst inst;
	काष्ठा pci_dev *dev;
	पूर्णांक edac_idx;	/* pci device index */
	अक्षर *ctl_name;
	काष्ठा edac_pci_ctl_info *edac_dev;
पूर्ण;

/*
 * AMD8131 chipset has two pairs of PCIX Bridge and related IOAPIC
 * Controller, and ATCA-6101 has two AMD8131 chipsets, so there are
 * four PCIX Bridges on ATCA-6101 altogether.
 *
 * These PCIX Bridges share the same PCI Device ID and are all of
 * Function Zero, they could be discrimated by their pci_dev->devfn.
 * They share the same set of init/check/निकास methods, and their
 * निजी काष्ठाures are collected in the devices[] array.
 */
काष्ठा amd8131_info अणु
	u16 err_dev;	/* PCI Device ID क्रम AMD8131 APIC*/
	काष्ठा amd8131_dev_info *devices;
	व्योम (*init)(काष्ठा amd8131_dev_info *dev_info);
	व्योम (*निकास)(काष्ठा amd8131_dev_info *dev_info);
	व्योम (*check)(काष्ठा edac_pci_ctl_info *edac_dev);
पूर्ण;

#पूर्ण_अगर /* _AMD8131_EDAC_H_ */

