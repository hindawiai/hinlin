<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/* Copyright (c) 2015-2016 Quantenna Communications */

#अगर_अघोषित _QTN_FMAC_PCIE_IPC_H_
#घोषणा _QTN_FMAC_PCIE_IPC_H_

#समावेश <linux/types.h>

#समावेश "shm_ipc_defs.h"

/* biपंचांगap क्रम EP status and flags: updated by EP, पढ़ो by RC */
#घोषणा QTN_EP_HAS_UBOOT	BIT(0)
#घोषणा QTN_EP_HAS_FIRMWARE	BIT(1)
#घोषणा QTN_EP_REQ_UBOOT	BIT(2)
#घोषणा QTN_EP_REQ_FIRMWARE	BIT(3)
#घोषणा QTN_EP_ERROR_UBOOT	BIT(4)
#घोषणा QTN_EP_ERROR_FIRMWARE	BIT(5)

#घोषणा QTN_EP_FW_LOADRDY	BIT(8)
#घोषणा QTN_EP_FW_SYNC		BIT(9)
#घोषणा QTN_EP_FW_RETRY		BIT(10)
#घोषणा QTN_EP_FW_QLINK_DONE	BIT(15)
#घोषणा QTN_EP_FW_DONE		BIT(16)

/* biपंचांगap क्रम RC status and flags: updated by RC, पढ़ो by EP */
#घोषणा QTN_RC_PCIE_LINK	BIT(0)
#घोषणा QTN_RC_NET_LINK		BIT(1)
#घोषणा QTN_RC_FW_FLASHBOOT	BIT(5)
#घोषणा QTN_RC_FW_QLINK		BIT(7)
#घोषणा QTN_RC_FW_LOADRDY	BIT(8)
#घोषणा QTN_RC_FW_SYNC		BIT(9)

#घोषणा PCIE_HDP_INT_RX_BITS (0		\
	| PCIE_HDP_INT_EP_TXDMA		\
	| PCIE_HDP_INT_EP_TXEMPTY	\
	| PCIE_HDP_INT_HHBM_UF		\
	)

#घोषणा PCIE_HDP_INT_TX_BITS (0		\
	| PCIE_HDP_INT_EP_RXDMA		\
	)

#अगर_घोषित CONFIG_ARCH_DMA_ADDR_T_64BIT
#घोषणा QTN_HOST_HI32(a)	((u32)(((u64)a) >> 32))
#घोषणा QTN_HOST_LO32(a)	((u32)(((u64)a) & 0xffffffffUL))
#घोषणा QTN_HOST_ADDR(h, l)	((((u64)h) << 32) | ((u64)l))
#अन्यथा
#घोषणा QTN_HOST_HI32(a)	0
#घोषणा QTN_HOST_LO32(a)	((u32)(((u32)a) & 0xffffffffUL))
#घोषणा QTN_HOST_ADDR(h, l)	((u32)l)
#पूर्ण_अगर

#घोषणा QTN_PCIE_BDA_VERSION		0x1002

#घोषणा PCIE_BDA_NAMELEN		32
#घोषणा PCIE_HHBM_MAX_SIZE		2048

#घोषणा QTN_PCIE_BOARDFLG	"PCIEQTN"
#घोषणा QTN_PCIE_FW_DLMASK	0xF
#घोषणा QTN_PCIE_FW_BUFSZ	2048

#घोषणा QTN_ENET_ADDR_LENGTH	6

#घोषणा QTN_TXDONE_MASK		((u32)0x80000000)
#घोषणा QTN_GET_LEN(x)		((x) & 0xFFFF)

#घोषणा QTN_PCIE_TX_DESC_LEN_MASK	0xFFFF
#घोषणा QTN_PCIE_TX_DESC_LEN_SHIFT	0
#घोषणा QTN_PCIE_TX_DESC_PORT_MASK	0xF
#घोषणा QTN_PCIE_TX_DESC_PORT_SHIFT	16
#घोषणा QTN_PCIE_TX_DESC_TQE_BIT	BIT(24)

#घोषणा QTN_EP_LHOST_TQE_PORT	4

क्रमागत qtnf_fw_loadtype अणु
	QTN_FW_DBEGIN,
	QTN_FW_DSUB,
	QTN_FW_DEND,
	QTN_FW_CTRL
पूर्ण;

#पूर्ण_अगर /* _QTN_FMAC_PCIE_IPC_H_ */
