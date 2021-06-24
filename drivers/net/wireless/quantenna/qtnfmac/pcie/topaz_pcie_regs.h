<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/* Copyright (c) 2018 Quantenna Communications */

#अगर_अघोषित __TOPAZ_PCIE_H
#घोषणा __TOPAZ_PCIE_H

/* Topaz PCIe DMA रेजिस्टरs */
#घोषणा PCIE_DMA_WR_INTR_STATUS(base)		((base) + 0x9bc)
#घोषणा PCIE_DMA_WR_INTR_MASK(base)		((base) + 0x9c4)
#घोषणा PCIE_DMA_WR_INTR_CLR(base)		((base) + 0x9c8)
#घोषणा PCIE_DMA_WR_ERR_STATUS(base)		((base) + 0x9cc)
#घोषणा PCIE_DMA_WR_DONE_IMWR_ADDR_LOW(base)	((base) + 0x9D0)
#घोषणा PCIE_DMA_WR_DONE_IMWR_ADDR_HIGH(base)	((base) + 0x9d4)

#घोषणा PCIE_DMA_RD_INTR_STATUS(base)		((base) + 0x310)
#घोषणा PCIE_DMA_RD_INTR_MASK(base)		((base) + 0x319)
#घोषणा PCIE_DMA_RD_INTR_CLR(base)		((base) + 0x31c)
#घोषणा PCIE_DMA_RD_ERR_STATUS_LOW(base)	((base) + 0x324)
#घोषणा PCIE_DMA_RD_ERR_STATUS_HIGH(base)	((base) + 0x328)
#घोषणा PCIE_DMA_RD_DONE_IMWR_ADDR_LOW(base)	((base) + 0x33c)
#घोषणा PCIE_DMA_RD_DONE_IMWR_ADDR_HIGH(base)	((base) + 0x340)

/* Topaz LHost IPC4 पूर्णांकerrupt */
#घोषणा TOPAZ_LH_IPC4_INT(base)			((base) + 0x13C)
#घोषणा TOPAZ_LH_IPC4_INT_MASK(base)		((base) + 0x140)

#घोषणा TOPAZ_RC_TX_DONE_IRQ			(0)
#घोषणा TOPAZ_RC_RST_EP_IRQ			(1)
#घोषणा TOPAZ_RC_TX_STOP_IRQ			(2)
#घोषणा TOPAZ_RC_RX_DONE_IRQ			(3)
#घोषणा TOPAZ_RC_PM_EP_IRQ			(4)

/* Topaz LHost M2L पूर्णांकerrupt */
#घोषणा TOPAZ_CTL_M2L_INT(base)			((base) + 0x2C)
#घोषणा TOPAZ_CTL_M2L_INT_MASK(base)		((base) + 0x30)

#घोषणा TOPAZ_RC_CTRL_IRQ			(6)

#घोषणा TOPAZ_IPC_IRQ_WORD(irq)			(BIT(irq) | BIT(irq + 16))

/* PCIe legacy INTx */
#घोषणा TOPAZ_PCIE_CFG0_OFFSET	(0x6C)
#घोषणा TOPAZ_ASSERT_INTX	BIT(9)

#पूर्ण_अगर /* __TOPAZ_PCIE_H */
