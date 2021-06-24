<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/* Copyright (c) 2018 Quantenna Communications */

#अगर_अघोषित _QTN_FMAC_PCIE_IPC_H_
#घोषणा _QTN_FMAC_PCIE_IPC_H_

#समावेश <linux/types.h>

#समावेश "shm_ipc_defs.h"

/* EP/RC status and flags */
#घोषणा QTN_BDA_PCIE_INIT		0x01
#घोषणा QTN_BDA_PCIE_RDY		0x02
#घोषणा QTN_BDA_FW_LOAD_RDY		0x03
#घोषणा QTN_BDA_FW_LOAD_DONE		0x04
#घोषणा QTN_BDA_FW_START		0x05
#घोषणा QTN_BDA_FW_RUN			0x06
#घोषणा QTN_BDA_FW_HOST_RDY		0x07
#घोषणा QTN_BDA_FW_TARGET_RDY		0x11
#घोषणा QTN_BDA_FW_TARGET_BOOT		0x12
#घोषणा QTN_BDA_FW_FLASH_BOOT		0x13
#घोषणा QTN_BDA_FW_QLINK_DONE		0x14
#घोषणा QTN_BDA_FW_HOST_LOAD		0x08
#घोषणा QTN_BDA_FW_BLOCK_DONE		0x09
#घोषणा QTN_BDA_FW_BLOCK_RDY		0x0A
#घोषणा QTN_BDA_FW_EP_RDY		0x0B
#घोषणा QTN_BDA_FW_BLOCK_END		0x0C
#घोषणा QTN_BDA_FW_CONFIG		0x0D
#घोषणा QTN_BDA_FW_RUNNING		0x0E
#घोषणा QTN_BDA_PCIE_FAIL		0x82
#घोषणा QTN_BDA_FW_LOAD_FAIL		0x85

#घोषणा QTN_BDA_RCMODE			BIT(1)
#घोषणा QTN_BDA_MSI			BIT(2)
#घोषणा QTN_BDA_HOST_CALCMD		BIT(3)
#घोषणा QTN_BDA_FLASH_PRESENT		BIT(4)
#घोषणा QTN_BDA_FLASH_BOOT		BIT(5)
#घोषणा QTN_BDA_XMIT_UBOOT		BIT(6)
#घोषणा QTN_BDA_HOST_QLINK_DRV		BIT(7)
#घोषणा QTN_BDA_TARGET_FBOOT_ERR	BIT(8)
#घोषणा QTN_BDA_TARGET_FWLOAD_ERR	BIT(9)
#घोषणा QTN_BDA_HOST_NOFW_ERR		BIT(12)
#घोषणा QTN_BDA_HOST_MEMALLOC_ERR	BIT(13)
#घोषणा QTN_BDA_HOST_MEMMAP_ERR		BIT(14)
#घोषणा QTN_BDA_VER(x)			(((x) >> 4) & 0xFF)
#घोषणा QTN_BDA_ERROR_MASK		0xFF00

/* रेजिस्टरs and shmem address macros */
#अगर BITS_PER_LONG == 64
#घोषणा QTN_HOST_HI32(a)	((u32)(((u64)a) >> 32))
#घोषणा QTN_HOST_LO32(a)	((u32)(((u64)a) & 0xffffffffUL))
#घोषणा QTN_HOST_ADDR(h, l)	((((u64)h) << 32) | ((u64)l))
#या_अगर BITS_PER_LONG == 32
#घोषणा QTN_HOST_HI32(a)	0
#घोषणा QTN_HOST_LO32(a)	((u32)(((u32)a) & 0xffffffffUL))
#घोषणा QTN_HOST_ADDR(h, l)	((u32)l)
#अन्यथा
#त्रुटि Unexpected BITS_PER_LONG value
#पूर्ण_अगर

#घोषणा QTN_PCIE_BDA_VERSION		0x1001

#घोषणा PCIE_BDA_NAMELEN		32

#घोषणा QTN_PCIE_RC_TX_QUEUE_LEN	256
#घोषणा QTN_PCIE_TX_VALID_PKT		0x80000000
#घोषणा QTN_PCIE_PKT_LEN_MASK		0xffff

#घोषणा QTN_BD_EMPTY		((uपूर्णांक32_t)0x00000001)
#घोषणा QTN_BD_WRAP		((uपूर्णांक32_t)0x00000002)
#घोषणा QTN_BD_MASK_LEN		((uपूर्णांक32_t)0xFFFF0000)
#घोषणा QTN_BD_MASK_OFFSET	((uपूर्णांक32_t)0x0000FF00)

#घोषणा QTN_GET_LEN(x)		(((x) >> 16) & 0xFFFF)
#घोषणा QTN_GET_OFFSET(x)	(((x) >> 8) & 0xFF)
#घोषणा QTN_SET_LEN(len)	(((len) & 0xFFFF) << 16)
#घोषणा QTN_SET_OFFSET(of)	(((of) & 0xFF) << 8)

#घोषणा RX_DONE_INTR_MSK	((0x1 << 6) - 1)

#घोषणा PCIE_DMA_OFFSET_ERROR		0xFFFF
#घोषणा PCIE_DMA_OFFSET_ERROR_MASK	0xFFFF

#घोषणा QTN_PCI_ENDIAN_DETECT_DATA	0x12345678
#घोषणा QTN_PCI_ENDIAN_REVERSE_DATA	0x78563412
#घोषणा QTN_PCI_ENDIAN_VALID_STATUS	0x3c3c3c3c
#घोषणा QTN_PCI_ENDIAN_INVALID_STATUS	0
#घोषणा QTN_PCI_LITTLE_ENDIAN		0
#घोषणा QTN_PCI_BIG_ENDIAN		0xffffffff

#घोषणा NBLOCKS(size, blksize)		\
	((size) / (blksize) + (((size) % (blksize) > 0) ? 1 : 0))

#पूर्ण_अगर /* _QTN_FMAC_PCIE_IPC_H_ */
