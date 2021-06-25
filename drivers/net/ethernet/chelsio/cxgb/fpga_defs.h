<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* $Date: 2005/03/07 23:59:05 $ $RCSfile: fpga_defs.h,v $ $Revision: 1.4 $ */

/*
 * FPGA specअगरic definitions
 */

#अगर_अघोषित __CHELSIO_FPGA_DEFS_H__
#घोषणा __CHELSIO_FPGA_DEFS_H__

#घोषणा FPGA_PCIX_ADDR_VERSION               0xA08
#घोषणा FPGA_PCIX_ADDR_STAT                  0xA0C

/* FPGA master पूर्णांकerrupt Cause/Enable bits */
#घोषणा FPGA_PCIX_INTERRUPT_SGE_ERROR        0x1
#घोषणा FPGA_PCIX_INTERRUPT_SGE_DATA         0x2
#घोषणा FPGA_PCIX_INTERRUPT_TP               0x4
#घोषणा FPGA_PCIX_INTERRUPT_MC3              0x8
#घोषणा FPGA_PCIX_INTERRUPT_GMAC             0x10
#घोषणा FPGA_PCIX_INTERRUPT_PCIX             0x20

/* TP पूर्णांकerrupt रेजिस्टर addresses */
#घोषणा FPGA_TP_ADDR_INTERRUPT_ENABLE        0xA10
#घोषणा FPGA_TP_ADDR_INTERRUPT_CAUSE         0xA14
#घोषणा FPGA_TP_ADDR_VERSION                 0xA18

/* TP पूर्णांकerrupt Cause/Enable bits */
#घोषणा FPGA_TP_INTERRUPT_MC4                0x1
#घोषणा FPGA_TP_INTERRUPT_MC5                0x2

/*
 * PM पूर्णांकerrupt रेजिस्टर addresses
 */
#घोषणा FPGA_MC3_REG_INTRENABLE              0xA20
#घोषणा FPGA_MC3_REG_INTRCAUSE               0xA24
#घोषणा FPGA_MC3_REG_VERSION                 0xA28

/*
 * GMAC पूर्णांकerrupt रेजिस्टर addresses
 */
#घोषणा FPGA_GMAC_ADDR_INTERRUPT_ENABLE      0xA30
#घोषणा FPGA_GMAC_ADDR_INTERRUPT_CAUSE       0xA34
#घोषणा FPGA_GMAC_ADDR_VERSION               0xA38

/* GMAC Cause/Enable bits */
#घोषणा FPGA_GMAC_INTERRUPT_PORT0            0x1
#घोषणा FPGA_GMAC_INTERRUPT_PORT1            0x2
#घोषणा FPGA_GMAC_INTERRUPT_PORT2            0x4
#घोषणा FPGA_GMAC_INTERRUPT_PORT3            0x8

/* MI0 रेजिस्टरs */
#घोषणा A_MI0_CLK 0xb00

#घोषणा S_MI0_CLK_DIV    0
#घोषणा M_MI0_CLK_DIV    0xff
#घोषणा V_MI0_CLK_DIV(x) ((x) << S_MI0_CLK_DIV)
#घोषणा G_MI0_CLK_DIV(x) (((x) >> S_MI0_CLK_DIV) & M_MI0_CLK_DIV)

#घोषणा S_MI0_CLK_CNT    8
#घोषणा M_MI0_CLK_CNT    0xff
#घोषणा V_MI0_CLK_CNT(x) ((x) << S_MI0_CLK_CNT)
#घोषणा G_MI0_CLK_CNT(x) (((x) >> S_MI0_CLK_CNT) & M_MI0_CLK_CNT)

#घोषणा A_MI0_CSR 0xb04

#घोषणा S_MI0_CSR_POLL    0
#घोषणा V_MI0_CSR_POLL(x) ((x) << S_MI0_CSR_POLL)
#घोषणा F_MI0_CSR_POLL    V_MI0_CSR_POLL(1U)

#घोषणा S_MI0_PREAMBLE    1
#घोषणा V_MI0_PREAMBLE(x) ((x) << S_MI0_PREAMBLE)
#घोषणा F_MI0_PREAMBLE    V_MI0_PREAMBLE(1U)

#घोषणा S_MI0_INTR_ENABLE    2
#घोषणा V_MI0_INTR_ENABLE(x) ((x) << S_MI0_INTR_ENABLE)
#घोषणा F_MI0_INTR_ENABLE    V_MI0_INTR_ENABLE(1U)

#घोषणा S_MI0_BUSY    3
#घोषणा V_MI0_BUSY(x) ((x) << S_MI0_BUSY)
#घोषणा F_MI0_BUSY    V_MI0_BUSY(1U)

#घोषणा S_MI0_MDIO    4
#घोषणा V_MI0_MDIO(x) ((x) << S_MI0_MDIO)
#घोषणा F_MI0_MDIO    V_MI0_MDIO(1U)

#घोषणा A_MI0_ADDR 0xb08

#घोषणा S_MI0_PHY_REG_ADDR    0
#घोषणा M_MI0_PHY_REG_ADDR    0x1f
#घोषणा V_MI0_PHY_REG_ADDR(x) ((x) << S_MI0_PHY_REG_ADDR)
#घोषणा G_MI0_PHY_REG_ADDR(x) (((x) >> S_MI0_PHY_REG_ADDR) & M_MI0_PHY_REG_ADDR)

#घोषणा S_MI0_PHY_ADDR    5
#घोषणा M_MI0_PHY_ADDR    0x1f
#घोषणा V_MI0_PHY_ADDR(x) ((x) << S_MI0_PHY_ADDR)
#घोषणा G_MI0_PHY_ADDR(x) (((x) >> S_MI0_PHY_ADDR) & M_MI0_PHY_ADDR)

#घोषणा A_MI0_DATA_EXT 0xb0c
#घोषणा A_MI0_DATA_INT 0xb10

/* GMAC रेजिस्टरs */
#घोषणा A_GMAC_MACID_LO	0x28
#घोषणा A_GMAC_MACID_HI	0x2c
#घोषणा A_GMAC_CSR	0x30

#घोषणा S_INTERFACE    0
#घोषणा M_INTERFACE    0x3
#घोषणा V_INTERFACE(x) ((x) << S_INTERFACE)
#घोषणा G_INTERFACE(x) (((x) >> S_INTERFACE) & M_INTERFACE)

#घोषणा S_MAC_TX_ENABLE    2
#घोषणा V_MAC_TX_ENABLE(x) ((x) << S_MAC_TX_ENABLE)
#घोषणा F_MAC_TX_ENABLE    V_MAC_TX_ENABLE(1U)

#घोषणा S_MAC_RX_ENABLE    3
#घोषणा V_MAC_RX_ENABLE(x) ((x) << S_MAC_RX_ENABLE)
#घोषणा F_MAC_RX_ENABLE    V_MAC_RX_ENABLE(1U)

#घोषणा S_MAC_LB_ENABLE    4
#घोषणा V_MAC_LB_ENABLE(x) ((x) << S_MAC_LB_ENABLE)
#घोषणा F_MAC_LB_ENABLE    V_MAC_LB_ENABLE(1U)

#घोषणा S_MAC_SPEED    5
#घोषणा M_MAC_SPEED    0x3
#घोषणा V_MAC_SPEED(x) ((x) << S_MAC_SPEED)
#घोषणा G_MAC_SPEED(x) (((x) >> S_MAC_SPEED) & M_MAC_SPEED)

#घोषणा S_MAC_HD_FC_ENABLE    7
#घोषणा V_MAC_HD_FC_ENABLE(x) ((x) << S_MAC_HD_FC_ENABLE)
#घोषणा F_MAC_HD_FC_ENABLE    V_MAC_HD_FC_ENABLE(1U)

#घोषणा S_MAC_HALF_DUPLEX    8
#घोषणा V_MAC_HALF_DUPLEX(x) ((x) << S_MAC_HALF_DUPLEX)
#घोषणा F_MAC_HALF_DUPLEX    V_MAC_HALF_DUPLEX(1U)

#घोषणा S_MAC_PROMISC    9
#घोषणा V_MAC_PROMISC(x) ((x) << S_MAC_PROMISC)
#घोषणा F_MAC_PROMISC    V_MAC_PROMISC(1U)

#घोषणा S_MAC_MC_ENABLE    10
#घोषणा V_MAC_MC_ENABLE(x) ((x) << S_MAC_MC_ENABLE)
#घोषणा F_MAC_MC_ENABLE    V_MAC_MC_ENABLE(1U)

#घोषणा S_MAC_RESET    11
#घोषणा V_MAC_RESET(x) ((x) << S_MAC_RESET)
#घोषणा F_MAC_RESET    V_MAC_RESET(1U)

#घोषणा S_MAC_RX_PAUSE_ENABLE    12
#घोषणा V_MAC_RX_PAUSE_ENABLE(x) ((x) << S_MAC_RX_PAUSE_ENABLE)
#घोषणा F_MAC_RX_PAUSE_ENABLE    V_MAC_RX_PAUSE_ENABLE(1U)

#घोषणा S_MAC_TX_PAUSE_ENABLE    13
#घोषणा V_MAC_TX_PAUSE_ENABLE(x) ((x) << S_MAC_TX_PAUSE_ENABLE)
#घोषणा F_MAC_TX_PAUSE_ENABLE    V_MAC_TX_PAUSE_ENABLE(1U)

#घोषणा S_MAC_LWM_ENABLE    14
#घोषणा V_MAC_LWM_ENABLE(x) ((x) << S_MAC_LWM_ENABLE)
#घोषणा F_MAC_LWM_ENABLE    V_MAC_LWM_ENABLE(1U)

#घोषणा S_MAC_MAGIC_PKT_ENABLE    15
#घोषणा V_MAC_MAGIC_PKT_ENABLE(x) ((x) << S_MAC_MAGIC_PKT_ENABLE)
#घोषणा F_MAC_MAGIC_PKT_ENABLE    V_MAC_MAGIC_PKT_ENABLE(1U)

#घोषणा S_MAC_ISL_ENABLE    16
#घोषणा V_MAC_ISL_ENABLE(x) ((x) << S_MAC_ISL_ENABLE)
#घोषणा F_MAC_ISL_ENABLE    V_MAC_ISL_ENABLE(1U)

#घोषणा S_MAC_JUMBO_ENABLE    17
#घोषणा V_MAC_JUMBO_ENABLE(x) ((x) << S_MAC_JUMBO_ENABLE)
#घोषणा F_MAC_JUMBO_ENABLE    V_MAC_JUMBO_ENABLE(1U)

#घोषणा S_MAC_RX_PAD_ENABLE    18
#घोषणा V_MAC_RX_PAD_ENABLE(x) ((x) << S_MAC_RX_PAD_ENABLE)
#घोषणा F_MAC_RX_PAD_ENABLE    V_MAC_RX_PAD_ENABLE(1U)

#घोषणा S_MAC_RX_CRC_ENABLE    19
#घोषणा V_MAC_RX_CRC_ENABLE(x) ((x) << S_MAC_RX_CRC_ENABLE)
#घोषणा F_MAC_RX_CRC_ENABLE    V_MAC_RX_CRC_ENABLE(1U)

#घोषणा A_GMAC_IFS 0x34

#घोषणा S_MAC_IFS2    0
#घोषणा M_MAC_IFS2    0x3f
#घोषणा V_MAC_IFS2(x) ((x) << S_MAC_IFS2)
#घोषणा G_MAC_IFS2(x) (((x) >> S_MAC_IFS2) & M_MAC_IFS2)

#घोषणा S_MAC_IFS1    8
#घोषणा M_MAC_IFS1    0x7f
#घोषणा V_MAC_IFS1(x) ((x) << S_MAC_IFS1)
#घोषणा G_MAC_IFS1(x) (((x) >> S_MAC_IFS1) & M_MAC_IFS1)

#घोषणा A_GMAC_JUMBO_FRAME_LEN 0x38
#घोषणा A_GMAC_LNK_DLY 0x3c
#घोषणा A_GMAC_PAUSETIME 0x40
#घोषणा A_GMAC_MCAST_LO 0x44
#घोषणा A_GMAC_MCAST_HI 0x48
#घोषणा A_GMAC_MCAST_MASK_LO 0x4c
#घोषणा A_GMAC_MCAST_MASK_HI 0x50
#घोषणा A_GMAC_RMT_CNT 0x54
#घोषणा A_GMAC_RMT_DATA 0x58
#घोषणा A_GMAC_BACKOFF_SEED 0x5c
#घोषणा A_GMAC_TXF_THRES 0x60

#घोषणा S_TXF_READ_THRESHOLD    0
#घोषणा M_TXF_READ_THRESHOLD    0xff
#घोषणा V_TXF_READ_THRESHOLD(x) ((x) << S_TXF_READ_THRESHOLD)
#घोषणा G_TXF_READ_THRESHOLD(x) (((x) >> S_TXF_READ_THRESHOLD) & M_TXF_READ_THRESHOLD)

#घोषणा S_TXF_WRITE_THRESHOLD    16
#घोषणा M_TXF_WRITE_THRESHOLD    0xff
#घोषणा V_TXF_WRITE_THRESHOLD(x) ((x) << S_TXF_WRITE_THRESHOLD)
#घोषणा G_TXF_WRITE_THRESHOLD(x) (((x) >> S_TXF_WRITE_THRESHOLD) & M_TXF_WRITE_THRESHOLD)

#घोषणा MAC_REG_BASE 0x600
#घोषणा MAC_REG_ADDR(idx, reg) (MAC_REG_BASE + (idx) * 128 + (reg))

#घोषणा MAC_REG_IDLO(idx)              MAC_REG_ADDR(idx, A_GMAC_MACID_LO)
#घोषणा MAC_REG_IDHI(idx)              MAC_REG_ADDR(idx, A_GMAC_MACID_HI)
#घोषणा MAC_REG_CSR(idx)               MAC_REG_ADDR(idx, A_GMAC_CSR)
#घोषणा MAC_REG_IFS(idx)               MAC_REG_ADDR(idx, A_GMAC_IFS)
#घोषणा MAC_REG_LARGEFRAMELENGTH(idx) MAC_REG_ADDR(idx, A_GMAC_JUMBO_FRAME_LEN)
#घोषणा MAC_REG_LINKDLY(idx)           MAC_REG_ADDR(idx, A_GMAC_LNK_DLY)
#घोषणा MAC_REG_PAUSETIME(idx)         MAC_REG_ADDR(idx, A_GMAC_PAUSETIME)
#घोषणा MAC_REG_CASTLO(idx)            MAC_REG_ADDR(idx, A_GMAC_MCAST_LO)
#घोषणा MAC_REG_MCASTHI(idx)           MAC_REG_ADDR(idx, A_GMAC_MCAST_HI)
#घोषणा MAC_REG_CASTMASKLO(idx)        MAC_REG_ADDR(idx, A_GMAC_MCAST_MASK_LO)
#घोषणा MAC_REG_MCASTMASKHI(idx)       MAC_REG_ADDR(idx, A_GMAC_MCAST_MASK_HI)
#घोषणा MAC_REG_RMCNT(idx)             MAC_REG_ADDR(idx, A_GMAC_RMT_CNT)
#घोषणा MAC_REG_RMDATA(idx)            MAC_REG_ADDR(idx, A_GMAC_RMT_DATA)
#घोषणा MAC_REG_GMRANDBACKOFFSEED(idx) MAC_REG_ADDR(idx, A_GMAC_BACKOFF_SEED)
#घोषणा MAC_REG_TXFTHRESHOLDS(idx)     MAC_REG_ADDR(idx, A_GMAC_TXF_THRES)

#पूर्ण_अगर
