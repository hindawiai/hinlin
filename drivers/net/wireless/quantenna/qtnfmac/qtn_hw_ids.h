<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/* Copyright (c) 2015-2016 Quantenna Communications. All rights reserved. */

#अगर_अघोषित	_QTN_HW_IDS_H_
#घोषणा	_QTN_HW_IDS_H_

#समावेश <linux/pci_ids.h>

#घोषणा PCIE_VENDOR_ID_QUANTENNA	(0x1bb5)

/* PCIE Device IDs */

#घोषणा	PCIE_DEVICE_ID_QSR		(0x0008)

#घोषणा QTN_REG_SYS_CTRL_CSR		0x14
#घोषणा QTN_CHIP_ID_MASK		0xF0
#घोषणा QTN_CHIP_ID_TOPAZ		0x40
#घोषणा QTN_CHIP_ID_PEARL		0x50
#घोषणा QTN_CHIP_ID_PEARL_B		0x60
#घोषणा QTN_CHIP_ID_PEARL_C		0x70

/* FW names */

#घोषणा QTN_PCI_PEARL_FW_NAME		"qtn/fmac_qsr10g.img"
#घोषणा QTN_PCI_TOPAZ_FW_NAME		"qtn/fmac_qsr1000.img"
#घोषणा QTN_PCI_TOPAZ_BOOTLD_NAME	"qtn/uboot_qsr1000.img"

अटल अंतरभूत अचिन्हित पूर्णांक qtnf_chip_id_get(स्थिर व्योम __iomem *regs_base)
अणु
	u32 board_rev = पढ़ोl(regs_base + QTN_REG_SYS_CTRL_CSR);

	वापस board_rev & QTN_CHIP_ID_MASK;
पूर्ण

#पूर्ण_अगर	/* _QTN_HW_IDS_H_ */
