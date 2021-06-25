<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/* Copyright (c) 2015 Quantenna Communications */

#अगर_अघोषित __PEARL_PCIE_H
#घोषणा __PEARL_PCIE_H

/* Pearl PCIe HDP रेजिस्टरs */
#घोषणा PCIE_HDP_CTRL(base)			((base) + 0x2c00)
#घोषणा PCIE_HDP_AXI_CTRL(base)			((base) + 0x2c04)
#घोषणा PCIE_HDP_HOST_WR_DESC0(base)		((base) + 0x2c10)
#घोषणा PCIE_HDP_HOST_WR_DESC0_H(base)		((base) + 0x2c14)
#घोषणा PCIE_HDP_HOST_WR_DESC1(base)		((base) + 0x2c18)
#घोषणा PCIE_HDP_HOST_WR_DESC1_H(base)		((base) + 0x2c1c)
#घोषणा PCIE_HDP_HOST_WR_DESC2(base)		((base) + 0x2c20)
#घोषणा PCIE_HDP_HOST_WR_DESC2_H(base)		((base) + 0x2c24)
#घोषणा PCIE_HDP_HOST_WR_DESC3(base)		((base) + 0x2c28)
#घोषणा PCIE_HDP_HOST_WR_DESC4_H(base)		((base) + 0x2c2c)
#घोषणा PCIE_HDP_RX_INT_CTRL(base)		((base) + 0x2c30)
#घोषणा PCIE_HDP_TX_INT_CTRL(base)		((base) + 0x2c34)
#घोषणा PCIE_HDP_INT_STATUS(base)		((base) + 0x2c38)
#घोषणा PCIE_HDP_INT_EN(base)			((base) + 0x2c3c)
#घोषणा PCIE_HDP_RX_DESC0_PTR(base)		((base) + 0x2c40)
#घोषणा PCIE_HDP_RX_DESC0_NOE(base)		((base) + 0x2c44)
#घोषणा PCIE_HDP_RX_DESC1_PTR(base)		((base) + 0x2c48)
#घोषणा PCIE_HDP_RX_DESC1_NOE(base)		((base) + 0x2c4c)
#घोषणा PCIE_HDP_RX_DESC2_PTR(base)		((base) + 0x2c50)
#घोषणा PCIE_HDP_RX_DESC2_NOE(base)		((base) + 0x2c54)
#घोषणा PCIE_HDP_RX_DESC3_PTR(base)		((base) + 0x2c58)
#घोषणा PCIE_HDP_RX_DESC3_NOE(base)		((base) + 0x2c5c)

#घोषणा PCIE_HDP_TX0_BASE_ADDR(base)		((base) + 0x2c60)
#घोषणा PCIE_HDP_TX1_BASE_ADDR(base)		((base) + 0x2c64)
#घोषणा PCIE_HDP_TX0_Q_CTRL(base)		((base) + 0x2c70)
#घोषणा PCIE_HDP_TX1_Q_CTRL(base)		((base) + 0x2c74)
#घोषणा PCIE_HDP_CFG0(base)			((base) + 0x2c80)
#घोषणा PCIE_HDP_CFG1(base)			((base) + 0x2c84)
#घोषणा PCIE_HDP_CFG2(base)			((base) + 0x2c88)
#घोषणा PCIE_HDP_CFG3(base)			((base) + 0x2c8c)
#घोषणा PCIE_HDP_CFG4(base)			((base) + 0x2c90)
#घोषणा PCIE_HDP_CFG5(base)			((base) + 0x2c94)
#घोषणा PCIE_HDP_CFG6(base)			((base) + 0x2c98)
#घोषणा PCIE_HDP_CFG7(base)			((base) + 0x2c9c)
#घोषणा PCIE_HDP_CFG8(base)			((base) + 0x2ca0)
#घोषणा PCIE_HDP_CFG9(base)			((base) + 0x2ca4)
#घोषणा PCIE_HDP_CFG10(base)			((base) + 0x2ca8)
#घोषणा PCIE_HDP_CFG11(base)			((base) + 0x2cac)
#घोषणा PCIE_INT(base)				((base) + 0x2cb0)
#घोषणा PCIE_INT_MASK(base)			((base) + 0x2cb4)
#घोषणा PCIE_MSI_MASK(base)			((base) + 0x2cb8)
#घोषणा PCIE_MSI_PNDG(base)			((base) + 0x2cbc)
#घोषणा PCIE_PRI_CFG(base)			((base) + 0x2cc0)
#घोषणा PCIE_PHY_CR(base)			((base) + 0x2cc4)
#घोषणा PCIE_HDP_CTAG_CTRL(base)		((base) + 0x2cf4)
#घोषणा PCIE_HDP_HHBM_BUF_PTR(base)		((base) + 0x2d00)
#घोषणा PCIE_HDP_HHBM_BUF_PTR_H(base)		((base) + 0x2d04)
#घोषणा PCIE_HDP_HHBM_BUF_FIFO_NOE(base)	((base) + 0x2d04)
#घोषणा PCIE_HDP_RX0DMA_CNT(base)		((base) + 0x2d10)
#घोषणा PCIE_HDP_RX1DMA_CNT(base)		((base) + 0x2d14)
#घोषणा PCIE_HDP_RX2DMA_CNT(base)		((base) + 0x2d18)
#घोषणा PCIE_HDP_RX3DMA_CNT(base)		((base) + 0x2d1c)
#घोषणा PCIE_HDP_TX0DMA_CNT(base)		((base) + 0x2d20)
#घोषणा PCIE_HDP_TX1DMA_CNT(base)		((base) + 0x2d24)
#घोषणा PCIE_HDP_RXDMA_CTRL(base)		((base) + 0x2d28)
#घोषणा PCIE_HDP_TX_HOST_Q_SZ_CTRL(base)	((base) + 0x2d2c)
#घोषणा PCIE_HDP_TX_HOST_Q_BASE_L(base)		((base) + 0x2d30)
#घोषणा PCIE_HDP_TX_HOST_Q_BASE_H(base)		((base) + 0x2d34)
#घोषणा PCIE_HDP_TX_HOST_Q_WR_PTR(base)		((base) + 0x2d38)
#घोषणा PCIE_HDP_TX_HOST_Q_RD_PTR(base)		((base) + 0x2d3c)
#घोषणा PCIE_HDP_TX_HOST_Q_STS(base)		((base) + 0x2d40)

/* Pearl PCIe HBM pool रेजिस्टरs */
#घोषणा PCIE_HHBM_CSR_REG(base)			((base) + 0x2e00)
#घोषणा PCIE_HHBM_Q_BASE_REG(base)		((base) + 0x2e04)
#घोषणा PCIE_HHBM_Q_LIMIT_REG(base)		((base) + 0x2e08)
#घोषणा PCIE_HHBM_Q_WR_REG(base)		((base) + 0x2e0c)
#घोषणा PCIE_HHBM_Q_RD_REG(base)		((base) + 0x2e10)
#घोषणा PCIE_HHBM_POOL_DATA_0_H(base)		((base) + 0x2e90)
#घोषणा PCIE_HHBM_CONFIG(base)			((base) + 0x2f9c)
#घोषणा PCIE_HHBM_POOL_REQ_0(base)		((base) + 0x2f10)
#घोषणा PCIE_HHBM_POOL_DATA_0(base)		((base) + 0x2f40)
#घोषणा PCIE_HHBM_WATERMARK_MASKED_INT(base)	((base) + 0x2f68)
#घोषणा PCIE_HHBM_WATERMARK_INT(base)		((base) + 0x2f6c)
#घोषणा PCIE_HHBM_POOL_WATERMARK(base)		((base) + 0x2f70)
#घोषणा PCIE_HHBM_POOL_OVERFLOW_CNT(base)	((base) + 0x2f90)
#घोषणा PCIE_HHBM_POOL_UNDERFLOW_CNT(base)	((base) + 0x2f94)
#घोषणा HBM_INT_STATUS(base)			((base) + 0x2f9c)
#घोषणा PCIE_HHBM_POOL_CNFIG(base)		((base) + 0x2f9c)

/* Pearl PCIe HBM bit field definitions */
#घोषणा HHBM_CONFIG_SOFT_RESET			(BIT(8))
#घोषणा HHBM_WR_REQ				(BIT(0))
#घोषणा HHBM_RD_REQ				(BIT(1))
#घोषणा HHBM_DONE				(BIT(31))
#घोषणा HHBM_64BIT				(BIT(10))

/* PCIe HDP पूर्णांकerrupt status definition */
#घोषणा PCIE_HDP_INT_EP_RXDMA		(BIT(0))
#घोषणा PCIE_HDP_INT_HBM_UF		(BIT(1))
#घोषणा PCIE_HDP_INT_RX_LEN_ERR		(BIT(2))
#घोषणा PCIE_HDP_INT_RX_HDR_LEN_ERR	(BIT(3))
#घोषणा PCIE_HDP_INT_EP_TXDMA		(BIT(12))
#घोषणा PCIE_HDP_INT_HHBM_UF		(BIT(13))
#घोषणा PCIE_HDP_INT_EP_TXEMPTY		(BIT(15))
#घोषणा PCIE_HDP_INT_IPC		(BIT(29))

/* PCIe पूर्णांकerrupt status definition */
#घोषणा PCIE_INT_MSI			(BIT(24))
#घोषणा PCIE_INT_INTX			(BIT(23))

/* PCIe legacy INTx */
#घोषणा PEARL_PCIE_CFG0_OFFSET		(0x6C)
#घोषणा PEARL_ASSERT_INTX		(BIT(9))

/* SYS CTL regs */
#घोषणा QTN_PEARL_SYSCTL_LHOST_IRQ_OFFSET	(0x001C)

#घोषणा QTN_PEARL_IPC_IRQ_WORD(irq)	(BIT(irq) | BIT(irq + 16))
#घोषणा QTN_PEARL_LHOST_IPC_IRQ		(6)
#घोषणा QTN_PEARL_LHOST_EP_RESET	(7)

#पूर्ण_अगर /* __PEARL_PCIE_H */
