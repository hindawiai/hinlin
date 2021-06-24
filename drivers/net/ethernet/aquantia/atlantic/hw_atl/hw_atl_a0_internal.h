<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * aQuantia Corporation Network Driver
 * Copyright (C) 2014-2017 aQuantia Corporation. All rights reserved
 */

/* File hw_atl_a0_पूर्णांकernal.h: Definition of Atlantic A0 chip specअगरic
 * स्थिरants.
 */

#अगर_अघोषित HW_ATL_A0_INTERNAL_H
#घोषणा HW_ATL_A0_INTERNAL_H

#समावेश "../aq_common.h"

#घोषणा HW_ATL_A0_MTU_JUMBO 9014U

#घोषणा HW_ATL_A0_TX_RINGS 4U
#घोषणा HW_ATL_A0_RX_RINGS 4U

#घोषणा HW_ATL_A0_RINGS_MAX 32U
#घोषणा HW_ATL_A0_TXD_SIZE  16U
#घोषणा HW_ATL_A0_RXD_SIZE  16U

#घोषणा HW_ATL_A0_MAC      0U
#घोषणा HW_ATL_A0_MAC_MIN  1U
#घोषणा HW_ATL_A0_MAC_MAX  33U

/* पूर्णांकerrupts */
#घोषणा HW_ATL_A0_ERR_INT 8U
#घोषणा HW_ATL_A0_INT_MASK  0xFFFFFFFFU

#घोषणा HW_ATL_A0_TXD_CTL2_LEN        0xFFFFC000U
#घोषणा HW_ATL_A0_TXD_CTL2_CTX_EN     0x00002000U
#घोषणा HW_ATL_A0_TXD_CTL2_CTX_IDX    0x00001000U

#घोषणा HW_ATL_A0_TXD_CTL_DESC_TYPE_TXD   0x00000001U
#घोषणा HW_ATL_A0_TXD_CTL_DESC_TYPE_TXC   0x00000002U
#घोषणा HW_ATL_A0_TXD_CTL_BLEN        0x000FFFF0U
#घोषणा HW_ATL_A0_TXD_CTL_DD          0x00100000U
#घोषणा HW_ATL_A0_TXD_CTL_EOP         0x00200000U

#घोषणा HW_ATL_A0_TXD_CTL_CMD_X       0x3FC00000U

#घोषणा HW_ATL_A0_TXD_CTL_CMD_VLAN    BIT(22)
#घोषणा HW_ATL_A0_TXD_CTL_CMD_FCS     BIT(23)
#घोषणा HW_ATL_A0_TXD_CTL_CMD_IPCSO   BIT(24)
#घोषणा HW_ATL_A0_TXD_CTL_CMD_TUCSO   BIT(25)
#घोषणा HW_ATL_A0_TXD_CTL_CMD_LSO     BIT(26)
#घोषणा HW_ATL_A0_TXD_CTL_CMD_WB      BIT(27)
#घोषणा HW_ATL_A0_TXD_CTL_CMD_VXLAN   BIT(28)

#घोषणा HW_ATL_A0_TXD_CTL_CMD_IPV6    BIT(21)
#घोषणा HW_ATL_A0_TXD_CTL_CMD_TCP     BIT(22)

#घोषणा HW_ATL_A0_MPI_CONTROL_ADR     0x0368U
#घोषणा HW_ATL_A0_MPI_STATE_ADR       0x036CU

#घोषणा HW_ATL_A0_MPI_SPEED_MSK       0xFFFFU
#घोषणा HW_ATL_A0_MPI_SPEED_SHIFT     16U

#घोषणा HW_ATL_A0_TXBUF_MAX 160U
#घोषणा HW_ATL_A0_RXBUF_MAX 320U

#घोषणा HW_ATL_A0_RSS_REसूचीECTION_MAX 64U
#घोषणा HW_ATL_A0_RSS_REसूचीECTION_BITS 3U

#घोषणा HW_ATL_A0_TC_MAX 1U
#घोषणा HW_ATL_A0_RSS_MAX 8U

#घोषणा HW_ATL_A0_FW_SEMA_RAM           0x2U

#घोषणा HW_ATL_A0_RXD_DD    0x1U
#घोषणा HW_ATL_A0_RXD_NCEA0 0x1U

#घोषणा HW_ATL_A0_RXD_WB_STAT2_EOP     0x0002U

#घोषणा HW_ATL_A0_UCP_0X370_REG  0x370U

#घोषणा HW_ATL_A0_FW_VER_EXPECTED 0x01050006U

#घोषणा HW_ATL_A0_MIN_RXD \
	(ALIGN(AQ_CFG_SKB_FRAGS_MAX + 1U, AQ_HW_RXD_MULTIPLE))
#घोषणा HW_ATL_A0_MIN_TXD \
	(ALIGN(AQ_CFG_SKB_FRAGS_MAX + 1U, AQ_HW_TXD_MULTIPLE))

#घोषणा HW_ATL_A0_MAX_RXD 8184U
#घोषणा HW_ATL_A0_MAX_TXD 8184U

#पूर्ण_अगर /* HW_ATL_A0_INTERNAL_H */
