<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * cpcihp_zt5550.h
 *
 * Intel/Ziatech ZT5550 CompactPCI Host Controller driver definitions
 *
 * Copyright 2002 SOMA Networks, Inc.
 * Copyright 2001 Intel San Luis Obispo
 * Copyright 2000,2001 MontaVista Software Inc.
 *
 * Send feedback to <scotपंचांग@somanetworks.com>
 */

#अगर_अघोषित _CPCIHP_ZT5550_H
#घोषणा _CPCIHP_ZT5550_H

/* Direct रेजिस्टरs */
#घोषणा CSR_HCINDEX		0x00
#घोषणा CSR_HCDATA		0x04
#घोषणा CSR_INTSTAT		0x08
#घोषणा CSR_INTMASK		0x09
#घोषणा CSR_CNT0CMD		0x0C
#घोषणा CSR_CNT1CMD		0x0E
#घोषणा CSR_CNT0		0x10
#घोषणा CSR_CNT1		0x14

/* Masks क्रम पूर्णांकerrupt bits in CSR_INTMASK direct रेजिस्टर */
#घोषणा CNT0_INT_MASK		0x01
#घोषणा CNT1_INT_MASK		0x02
#घोषणा ENUM_INT_MASK		0x04
#घोषणा ALL_सूचीECT_INTS_MASK	0x07

/* Indexed रेजिस्टरs (through CSR_INDEX, CSR_DATA) */
#घोषणा HC_INT_MASK_REG		0x04
#घोषणा HC_STATUS_REG		0x08
#घोषणा HC_CMD_REG		0x0C
#घोषणा ARB_CONFIG_GNT_REG	0x10
#घोषणा ARB_CONFIG_CFG_REG	0x12
#घोषणा ARB_CONFIG_REG		0x10
#घोषणा ISOL_CONFIG_REG		0x18
#घोषणा FAULT_STATUS_REG	0x20
#घोषणा FAULT_CONFIG_REG	0x24
#घोषणा WD_CONFIG_REG		0x2C
#घोषणा HC_DIAG_REG		0x30
#घोषणा SERIAL_COMM_REG		0x34
#घोषणा SERIAL_OUT_REG		0x38
#घोषणा SERIAL_IN_REG		0x3C

/* Masks क्रम पूर्णांकerrupt bits in HC_INT_MASK_REG indexed रेजिस्टर */
#घोषणा SERIAL_INT_MASK		0x01
#घोषणा FAULT_INT_MASK		0x02
#घोषणा HCF_INT_MASK		0x04
#घोषणा ALL_INDEXED_INTS_MASK	0x07

/* Digital I/O port storing ENUM# */
#घोषणा ENUM_PORT	0xE1
/* Mask to get to the ENUM# bit on the bus */
#घोषणा ENUM_MASK	0x40

#पूर्ण_अगर				/* _CPCIHP_ZT5550_H */
