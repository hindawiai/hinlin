<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2016 Linaro Ltd.
 * Copyright (c) 2016 Hisilicon Limited.
 */

#समावेश "hisi_sas.h"
#घोषणा DRV_NAME "hisi_sas_v2_hw"

/* global रेजिस्टरs need init*/
#घोषणा DLVRY_QUEUE_ENABLE		0x0
#घोषणा IOST_BASE_ADDR_LO		0x8
#घोषणा IOST_BASE_ADDR_HI		0xc
#घोषणा ITCT_BASE_ADDR_LO		0x10
#घोषणा ITCT_BASE_ADDR_HI		0x14
#घोषणा IO_BROKEN_MSG_ADDR_LO		0x18
#घोषणा IO_BROKEN_MSG_ADDR_HI		0x1c
#घोषणा PHY_CONTEXT			0x20
#घोषणा PHY_STATE			0x24
#घोषणा PHY_PORT_NUM_MA			0x28
#घोषणा PORT_STATE			0x2c
#घोषणा PORT_STATE_PHY8_PORT_NUM_OFF	16
#घोषणा PORT_STATE_PHY8_PORT_NUM_MSK	(0xf << PORT_STATE_PHY8_PORT_NUM_OFF)
#घोषणा PORT_STATE_PHY8_CONN_RATE_OFF	20
#घोषणा PORT_STATE_PHY8_CONN_RATE_MSK	(0xf << PORT_STATE_PHY8_CONN_RATE_OFF)
#घोषणा PHY_CONN_RATE			0x30
#घोषणा HGC_TRANS_TASK_CNT_LIMIT	0x38
#घोषणा AXI_AHB_CLK_CFG			0x3c
#घोषणा ITCT_CLR			0x44
#घोषणा ITCT_CLR_EN_OFF			16
#घोषणा ITCT_CLR_EN_MSK			(0x1 << ITCT_CLR_EN_OFF)
#घोषणा ITCT_DEV_OFF			0
#घोषणा ITCT_DEV_MSK			(0x7ff << ITCT_DEV_OFF)
#घोषणा AXI_USER1			0x48
#घोषणा AXI_USER2			0x4c
#घोषणा IO_SATA_BROKEN_MSG_ADDR_LO	0x58
#घोषणा IO_SATA_BROKEN_MSG_ADDR_HI	0x5c
#घोषणा SATA_INITI_D2H_STORE_ADDR_LO	0x60
#घोषणा SATA_INITI_D2H_STORE_ADDR_HI	0x64
#घोषणा HGC_SAS_TX_OPEN_FAIL_RETRY_CTRL	0x84
#घोषणा HGC_SAS_TXFAIL_RETRY_CTRL	0x88
#घोषणा HGC_GET_ITV_TIME		0x90
#घोषणा DEVICE_MSG_WORK_MODE		0x94
#घोषणा OPENA_WT_CONTI_TIME		0x9c
#घोषणा I_T_NEXUS_LOSS_TIME		0xa0
#घोषणा MAX_CON_TIME_LIMIT_TIME		0xa4
#घोषणा BUS_INACTIVE_LIMIT_TIME		0xa8
#घोषणा REJECT_TO_OPEN_LIMIT_TIME	0xac
#घोषणा CFG_AGING_TIME			0xbc
#घोषणा HGC_DFX_CFG2			0xc0
#घोषणा HGC_IOMB_PROC1_STATUS	0x104
#घोषणा CFG_1US_TIMER_TRSH		0xcc
#घोषणा HGC_LM_DFX_STATUS2		0x128
#घोषणा HGC_LM_DFX_STATUS2_IOSTLIST_OFF		0
#घोषणा HGC_LM_DFX_STATUS2_IOSTLIST_MSK	(0xfff << \
					 HGC_LM_DFX_STATUS2_IOSTLIST_OFF)
#घोषणा HGC_LM_DFX_STATUS2_ITCTLIST_OFF		12
#घोषणा HGC_LM_DFX_STATUS2_ITCTLIST_MSK	(0x7ff << \
					 HGC_LM_DFX_STATUS2_ITCTLIST_OFF)
#घोषणा HGC_CQE_ECC_ADDR		0x13c
#घोषणा HGC_CQE_ECC_1B_ADDR_OFF	0
#घोषणा HGC_CQE_ECC_1B_ADDR_MSK	(0x3f << HGC_CQE_ECC_1B_ADDR_OFF)
#घोषणा HGC_CQE_ECC_MB_ADDR_OFF	8
#घोषणा HGC_CQE_ECC_MB_ADDR_MSK (0x3f << HGC_CQE_ECC_MB_ADDR_OFF)
#घोषणा HGC_IOST_ECC_ADDR		0x140
#घोषणा HGC_IOST_ECC_1B_ADDR_OFF	0
#घोषणा HGC_IOST_ECC_1B_ADDR_MSK	(0x3ff << HGC_IOST_ECC_1B_ADDR_OFF)
#घोषणा HGC_IOST_ECC_MB_ADDR_OFF	16
#घोषणा HGC_IOST_ECC_MB_ADDR_MSK	(0x3ff << HGC_IOST_ECC_MB_ADDR_OFF)
#घोषणा HGC_DQE_ECC_ADDR		0x144
#घोषणा HGC_DQE_ECC_1B_ADDR_OFF	0
#घोषणा HGC_DQE_ECC_1B_ADDR_MSK	(0xfff << HGC_DQE_ECC_1B_ADDR_OFF)
#घोषणा HGC_DQE_ECC_MB_ADDR_OFF	16
#घोषणा HGC_DQE_ECC_MB_ADDR_MSK (0xfff << HGC_DQE_ECC_MB_ADDR_OFF)
#घोषणा HGC_INVLD_DQE_INFO		0x148
#घोषणा HGC_INVLD_DQE_INFO_FB_CH0_OFF	9
#घोषणा HGC_INVLD_DQE_INFO_FB_CH0_MSK	(0x1 << HGC_INVLD_DQE_INFO_FB_CH0_OFF)
#घोषणा HGC_INVLD_DQE_INFO_FB_CH3_OFF	18
#घोषणा HGC_ITCT_ECC_ADDR		0x150
#घोषणा HGC_ITCT_ECC_1B_ADDR_OFF		0
#घोषणा HGC_ITCT_ECC_1B_ADDR_MSK		(0x3ff << \
						 HGC_ITCT_ECC_1B_ADDR_OFF)
#घोषणा HGC_ITCT_ECC_MB_ADDR_OFF		16
#घोषणा HGC_ITCT_ECC_MB_ADDR_MSK		(0x3ff << \
						 HGC_ITCT_ECC_MB_ADDR_OFF)
#घोषणा HGC_AXI_FIFO_ERR_INFO	0x154
#घोषणा AXI_ERR_INFO_OFF		0
#घोषणा AXI_ERR_INFO_MSK		(0xff << AXI_ERR_INFO_OFF)
#घोषणा FIFO_ERR_INFO_OFF		8
#घोषणा FIFO_ERR_INFO_MSK		(0xff << FIFO_ERR_INFO_OFF)
#घोषणा INT_COAL_EN			0x19c
#घोषणा OQ_INT_COAL_TIME		0x1a0
#घोषणा OQ_INT_COAL_CNT			0x1a4
#घोषणा ENT_INT_COAL_TIME		0x1a8
#घोषणा ENT_INT_COAL_CNT		0x1ac
#घोषणा OQ_INT_SRC			0x1b0
#घोषणा OQ_INT_SRC_MSK			0x1b4
#घोषणा ENT_INT_SRC1			0x1b8
#घोषणा ENT_INT_SRC1_D2H_FIS_CH0_OFF	0
#घोषणा ENT_INT_SRC1_D2H_FIS_CH0_MSK	(0x1 << ENT_INT_SRC1_D2H_FIS_CH0_OFF)
#घोषणा ENT_INT_SRC1_D2H_FIS_CH1_OFF	8
#घोषणा ENT_INT_SRC1_D2H_FIS_CH1_MSK	(0x1 << ENT_INT_SRC1_D2H_FIS_CH1_OFF)
#घोषणा ENT_INT_SRC2			0x1bc
#घोषणा ENT_INT_SRC3			0x1c0
#घोषणा ENT_INT_SRC3_WP_DEPTH_OFF		8
#घोषणा ENT_INT_SRC3_IPTT_SLOT_NOMATCH_OFF	9
#घोषणा ENT_INT_SRC3_RP_DEPTH_OFF		10
#घोषणा ENT_INT_SRC3_AXI_OFF			11
#घोषणा ENT_INT_SRC3_FIFO_OFF			12
#घोषणा ENT_INT_SRC3_LM_OFF				14
#घोषणा ENT_INT_SRC3_ITC_INT_OFF	15
#घोषणा ENT_INT_SRC3_ITC_INT_MSK	(0x1 << ENT_INT_SRC3_ITC_INT_OFF)
#घोषणा ENT_INT_SRC3_ABT_OFF		16
#घोषणा ENT_INT_SRC_MSK1		0x1c4
#घोषणा ENT_INT_SRC_MSK2		0x1c8
#घोषणा ENT_INT_SRC_MSK3		0x1cc
#घोषणा ENT_INT_SRC_MSK3_ENT95_MSK_OFF	31
#घोषणा ENT_INT_SRC_MSK3_ENT95_MSK_MSK	(0x1 << ENT_INT_SRC_MSK3_ENT95_MSK_OFF)
#घोषणा SAS_ECC_INTR			0x1e8
#घोषणा SAS_ECC_INTR_DQE_ECC_1B_OFF		0
#घोषणा SAS_ECC_INTR_DQE_ECC_MB_OFF		1
#घोषणा SAS_ECC_INTR_IOST_ECC_1B_OFF	2
#घोषणा SAS_ECC_INTR_IOST_ECC_MB_OFF	3
#घोषणा SAS_ECC_INTR_ITCT_ECC_MB_OFF	4
#घोषणा SAS_ECC_INTR_ITCT_ECC_1B_OFF	5
#घोषणा SAS_ECC_INTR_IOSTLIST_ECC_MB_OFF	6
#घोषणा SAS_ECC_INTR_IOSTLIST_ECC_1B_OFF	7
#घोषणा SAS_ECC_INTR_ITCTLIST_ECC_1B_OFF	8
#घोषणा SAS_ECC_INTR_ITCTLIST_ECC_MB_OFF	9
#घोषणा SAS_ECC_INTR_CQE_ECC_1B_OFF		10
#घोषणा SAS_ECC_INTR_CQE_ECC_MB_OFF		11
#घोषणा SAS_ECC_INTR_NCQ_MEM0_ECC_MB_OFF	12
#घोषणा SAS_ECC_INTR_NCQ_MEM0_ECC_1B_OFF	13
#घोषणा SAS_ECC_INTR_NCQ_MEM1_ECC_MB_OFF	14
#घोषणा SAS_ECC_INTR_NCQ_MEM1_ECC_1B_OFF	15
#घोषणा SAS_ECC_INTR_NCQ_MEM2_ECC_MB_OFF	16
#घोषणा SAS_ECC_INTR_NCQ_MEM2_ECC_1B_OFF	17
#घोषणा SAS_ECC_INTR_NCQ_MEM3_ECC_MB_OFF	18
#घोषणा SAS_ECC_INTR_NCQ_MEM3_ECC_1B_OFF	19
#घोषणा SAS_ECC_INTR_MSK		0x1ec
#घोषणा HGC_ERR_STAT_EN			0x238
#घोषणा CQE_SEND_CNT			0x248
#घोषणा DLVRY_Q_0_BASE_ADDR_LO		0x260
#घोषणा DLVRY_Q_0_BASE_ADDR_HI		0x264
#घोषणा DLVRY_Q_0_DEPTH			0x268
#घोषणा DLVRY_Q_0_WR_PTR		0x26c
#घोषणा DLVRY_Q_0_RD_PTR		0x270
#घोषणा HYPER_STREAM_ID_EN_CFG		0xc80
#घोषणा OQ0_INT_SRC_MSK			0xc90
#घोषणा COMPL_Q_0_BASE_ADDR_LO		0x4e0
#घोषणा COMPL_Q_0_BASE_ADDR_HI		0x4e4
#घोषणा COMPL_Q_0_DEPTH			0x4e8
#घोषणा COMPL_Q_0_WR_PTR		0x4ec
#घोषणा COMPL_Q_0_RD_PTR		0x4f0
#घोषणा HGC_RXM_DFX_STATUS14	0xae8
#घोषणा HGC_RXM_DFX_STATUS14_MEM0_OFF		0
#घोषणा HGC_RXM_DFX_STATUS14_MEM0_MSK		(0x1ff << \
						 HGC_RXM_DFX_STATUS14_MEM0_OFF)
#घोषणा HGC_RXM_DFX_STATUS14_MEM1_OFF		9
#घोषणा HGC_RXM_DFX_STATUS14_MEM1_MSK		(0x1ff << \
						 HGC_RXM_DFX_STATUS14_MEM1_OFF)
#घोषणा HGC_RXM_DFX_STATUS14_MEM2_OFF		18
#घोषणा HGC_RXM_DFX_STATUS14_MEM2_MSK		(0x1ff << \
						 HGC_RXM_DFX_STATUS14_MEM2_OFF)
#घोषणा HGC_RXM_DFX_STATUS15	0xaec
#घोषणा HGC_RXM_DFX_STATUS15_MEM3_OFF		0
#घोषणा HGC_RXM_DFX_STATUS15_MEM3_MSK		(0x1ff << \
						 HGC_RXM_DFX_STATUS15_MEM3_OFF)
/* phy रेजिस्टरs need init */
#घोषणा PORT_BASE			(0x2000)

#घोषणा PHY_CFG				(PORT_BASE + 0x0)
#घोषणा HARD_PHY_LINKRATE		(PORT_BASE + 0x4)
#घोषणा PHY_CFG_ENA_OFF			0
#घोषणा PHY_CFG_ENA_MSK			(0x1 << PHY_CFG_ENA_OFF)
#घोषणा PHY_CFG_DC_OPT_OFF		2
#घोषणा PHY_CFG_DC_OPT_MSK		(0x1 << PHY_CFG_DC_OPT_OFF)
#घोषणा PROG_PHY_LINK_RATE		(PORT_BASE + 0x8)
#घोषणा PROG_PHY_LINK_RATE_MAX_OFF	0
#घोषणा PROG_PHY_LINK_RATE_MAX_MSK	(0xff << PROG_PHY_LINK_RATE_MAX_OFF)
#घोषणा PHY_CTRL			(PORT_BASE + 0x14)
#घोषणा PHY_CTRL_RESET_OFF		0
#घोषणा PHY_CTRL_RESET_MSK		(0x1 << PHY_CTRL_RESET_OFF)
#घोषणा SAS_PHY_CTRL			(PORT_BASE + 0x20)
#घोषणा SL_CFG				(PORT_BASE + 0x84)
#घोषणा PHY_PCN				(PORT_BASE + 0x44)
#घोषणा SL_TOUT_CFG			(PORT_BASE + 0x8c)
#घोषणा SL_CONTROL			(PORT_BASE + 0x94)
#घोषणा SL_CONTROL_NOTIFY_EN_OFF	0
#घोषणा SL_CONTROL_NOTIFY_EN_MSK	(0x1 << SL_CONTROL_NOTIFY_EN_OFF)
#घोषणा SL_CONTROL_CTA_OFF		17
#घोषणा SL_CONTROL_CTA_MSK		(0x1 << SL_CONTROL_CTA_OFF)
#घोषणा RX_PRIMS_STATUS			(PORT_BASE + 0x98)
#घोषणा RX_BCAST_CHG_OFF		1
#घोषणा RX_BCAST_CHG_MSK		(0x1 << RX_BCAST_CHG_OFF)
#घोषणा TX_ID_DWORD0			(PORT_BASE + 0x9c)
#घोषणा TX_ID_DWORD1			(PORT_BASE + 0xa0)
#घोषणा TX_ID_DWORD2			(PORT_BASE + 0xa4)
#घोषणा TX_ID_DWORD3			(PORT_BASE + 0xa8)
#घोषणा TX_ID_DWORD4			(PORT_BASE + 0xaC)
#घोषणा TX_ID_DWORD5			(PORT_BASE + 0xb0)
#घोषणा TX_ID_DWORD6			(PORT_BASE + 0xb4)
#घोषणा TXID_AUTO			(PORT_BASE + 0xb8)
#घोषणा TXID_AUTO_CT3_OFF		1
#घोषणा TXID_AUTO_CT3_MSK		(0x1 << TXID_AUTO_CT3_OFF)
#घोषणा TXID_AUTO_CTB_OFF		11
#घोषणा TXID_AUTO_CTB_MSK		(0x1 << TXID_AUTO_CTB_OFF)
#घोषणा TX_HARDRST_OFF			2
#घोषणा TX_HARDRST_MSK			(0x1 << TX_HARDRST_OFF)
#घोषणा RX_IDAF_DWORD0			(PORT_BASE + 0xc4)
#घोषणा RX_IDAF_DWORD1			(PORT_BASE + 0xc8)
#घोषणा RX_IDAF_DWORD2			(PORT_BASE + 0xcc)
#घोषणा RX_IDAF_DWORD3			(PORT_BASE + 0xd0)
#घोषणा RX_IDAF_DWORD4			(PORT_BASE + 0xd4)
#घोषणा RX_IDAF_DWORD5			(PORT_BASE + 0xd8)
#घोषणा RX_IDAF_DWORD6			(PORT_BASE + 0xdc)
#घोषणा RXOP_CHECK_CFG_H		(PORT_BASE + 0xfc)
#घोषणा CON_CONTROL			(PORT_BASE + 0x118)
#घोषणा CON_CONTROL_CFG_OPEN_ACC_STP_OFF	0
#घोषणा CON_CONTROL_CFG_OPEN_ACC_STP_MSK	\
		(0x01 << CON_CONTROL_CFG_OPEN_ACC_STP_OFF)
#घोषणा DONE_RECEIVED_TIME		(PORT_BASE + 0x11c)
#घोषणा CHL_INT0			(PORT_BASE + 0x1b4)
#घोषणा CHL_INT0_HOTPLUG_TOUT_OFF	0
#घोषणा CHL_INT0_HOTPLUG_TOUT_MSK	(0x1 << CHL_INT0_HOTPLUG_TOUT_OFF)
#घोषणा CHL_INT0_SL_RX_BCST_ACK_OFF	1
#घोषणा CHL_INT0_SL_RX_BCST_ACK_MSK	(0x1 << CHL_INT0_SL_RX_BCST_ACK_OFF)
#घोषणा CHL_INT0_SL_PHY_ENABLE_OFF	2
#घोषणा CHL_INT0_SL_PHY_ENABLE_MSK	(0x1 << CHL_INT0_SL_PHY_ENABLE_OFF)
#घोषणा CHL_INT0_NOT_RDY_OFF		4
#घोषणा CHL_INT0_NOT_RDY_MSK		(0x1 << CHL_INT0_NOT_RDY_OFF)
#घोषणा CHL_INT0_PHY_RDY_OFF		5
#घोषणा CHL_INT0_PHY_RDY_MSK		(0x1 << CHL_INT0_PHY_RDY_OFF)
#घोषणा CHL_INT1			(PORT_BASE + 0x1b8)
#घोषणा CHL_INT1_DMAC_TX_ECC_ERR_OFF	15
#घोषणा CHL_INT1_DMAC_TX_ECC_ERR_MSK	(0x1 << CHL_INT1_DMAC_TX_ECC_ERR_OFF)
#घोषणा CHL_INT1_DMAC_RX_ECC_ERR_OFF	17
#घोषणा CHL_INT1_DMAC_RX_ECC_ERR_MSK	(0x1 << CHL_INT1_DMAC_RX_ECC_ERR_OFF)
#घोषणा CHL_INT1_DMAC_TX_AXI_WR_ERR_OFF	19
#घोषणा CHL_INT1_DMAC_TX_AXI_RD_ERR_OFF	20
#घोषणा CHL_INT1_DMAC_RX_AXI_WR_ERR_OFF	21
#घोषणा CHL_INT1_DMAC_RX_AXI_RD_ERR_OFF	22
#घोषणा CHL_INT2			(PORT_BASE + 0x1bc)
#घोषणा CHL_INT2_SL_IDAF_TOUT_CONF_OFF	0
#घोषणा CHL_INT0_MSK			(PORT_BASE + 0x1c0)
#घोषणा CHL_INT1_MSK			(PORT_BASE + 0x1c4)
#घोषणा CHL_INT2_MSK			(PORT_BASE + 0x1c8)
#घोषणा CHL_INT_COAL_EN			(PORT_BASE + 0x1d0)
#घोषणा DMA_TX_DFX0				(PORT_BASE + 0x200)
#घोषणा DMA_TX_DFX1				(PORT_BASE + 0x204)
#घोषणा DMA_TX_DFX1_IPTT_OFF		0
#घोषणा DMA_TX_DFX1_IPTT_MSK		(0xffff << DMA_TX_DFX1_IPTT_OFF)
#घोषणा DMA_TX_FIFO_DFX0		(PORT_BASE + 0x240)
#घोषणा PORT_DFX0				(PORT_BASE + 0x258)
#घोषणा LINK_DFX2					(PORT_BASE + 0X264)
#घोषणा LINK_DFX2_RCVR_HOLD_STS_OFF	9
#घोषणा LINK_DFX2_RCVR_HOLD_STS_MSK	(0x1 << LINK_DFX2_RCVR_HOLD_STS_OFF)
#घोषणा LINK_DFX2_SEND_HOLD_STS_OFF	10
#घोषणा LINK_DFX2_SEND_HOLD_STS_MSK	(0x1 << LINK_DFX2_SEND_HOLD_STS_OFF)
#घोषणा SAS_ERR_CNT4_REG		(PORT_BASE + 0x290)
#घोषणा SAS_ERR_CNT6_REG		(PORT_BASE + 0x298)
#घोषणा PHY_CTRL_RDY_MSK		(PORT_BASE + 0x2b0)
#घोषणा PHYCTRL_NOT_RDY_MSK		(PORT_BASE + 0x2b4)
#घोषणा PHYCTRL_DWS_RESET_MSK		(PORT_BASE + 0x2b8)
#घोषणा PHYCTRL_PHY_ENA_MSK		(PORT_BASE + 0x2bc)
#घोषणा SL_RX_BCAST_CHK_MSK		(PORT_BASE + 0x2c0)
#घोषणा PHYCTRL_OOB_RESTART_MSK		(PORT_BASE + 0x2c4)
#घोषणा DMA_TX_STATUS			(PORT_BASE + 0x2d0)
#घोषणा DMA_TX_STATUS_BUSY_OFF		0
#घोषणा DMA_TX_STATUS_BUSY_MSK		(0x1 << DMA_TX_STATUS_BUSY_OFF)
#घोषणा DMA_RX_STATUS			(PORT_BASE + 0x2e8)
#घोषणा DMA_RX_STATUS_BUSY_OFF		0
#घोषणा DMA_RX_STATUS_BUSY_MSK		(0x1 << DMA_RX_STATUS_BUSY_OFF)

#घोषणा AXI_CFG				(0x5100)
#घोषणा AM_CFG_MAX_TRANS		(0x5010)
#घोषणा AM_CFG_SINGLE_PORT_MAX_TRANS	(0x5014)

#घोषणा AXI_MASTER_CFG_BASE		(0x5000)
#घोषणा AM_CTRL_GLOBAL			(0x0)
#घोषणा AM_CURR_TRANS_RETURN	(0x150)

/* HW dma काष्ठाures */
/* Delivery queue header */
/* dw0 */
#घोषणा CMD_HDR_ABORT_FLAG_OFF		0
#घोषणा CMD_HDR_ABORT_FLAG_MSK		(0x3 << CMD_HDR_ABORT_FLAG_OFF)
#घोषणा CMD_HDR_ABORT_DEVICE_TYPE_OFF	2
#घोषणा CMD_HDR_ABORT_DEVICE_TYPE_MSK	(0x1 << CMD_HDR_ABORT_DEVICE_TYPE_OFF)
#घोषणा CMD_HDR_RESP_REPORT_OFF		5
#घोषणा CMD_HDR_RESP_REPORT_MSK		(0x1 << CMD_HDR_RESP_REPORT_OFF)
#घोषणा CMD_HDR_TLR_CTRL_OFF		6
#घोषणा CMD_HDR_TLR_CTRL_MSK		(0x3 << CMD_HDR_TLR_CTRL_OFF)
#घोषणा CMD_HDR_PHY_ID_OFF		8
#घोषणा CMD_HDR_PHY_ID_MSK		(0x1ff << CMD_HDR_PHY_ID_OFF)
#घोषणा CMD_HDR_FORCE_PHY_OFF		17
#घोषणा CMD_HDR_FORCE_PHY_MSK		(0x1 << CMD_HDR_FORCE_PHY_OFF)
#घोषणा CMD_HDR_PORT_OFF		18
#घोषणा CMD_HDR_PORT_MSK		(0xf << CMD_HDR_PORT_OFF)
#घोषणा CMD_HDR_PRIORITY_OFF		27
#घोषणा CMD_HDR_PRIORITY_MSK		(0x1 << CMD_HDR_PRIORITY_OFF)
#घोषणा CMD_HDR_CMD_OFF			29
#घोषणा CMD_HDR_CMD_MSK			(0x7 << CMD_HDR_CMD_OFF)
/* dw1 */
#घोषणा CMD_HDR_सूची_OFF			5
#घोषणा CMD_HDR_सूची_MSK			(0x3 << CMD_HDR_सूची_OFF)
#घोषणा CMD_HDR_RESET_OFF		7
#घोषणा CMD_HDR_RESET_MSK		(0x1 << CMD_HDR_RESET_OFF)
#घोषणा CMD_HDR_VDTL_OFF		10
#घोषणा CMD_HDR_VDTL_MSK		(0x1 << CMD_HDR_VDTL_OFF)
#घोषणा CMD_HDR_FRAME_TYPE_OFF		11
#घोषणा CMD_HDR_FRAME_TYPE_MSK		(0x1f << CMD_HDR_FRAME_TYPE_OFF)
#घोषणा CMD_HDR_DEV_ID_OFF		16
#घोषणा CMD_HDR_DEV_ID_MSK		(0xffff << CMD_HDR_DEV_ID_OFF)
/* dw2 */
#घोषणा CMD_HDR_CFL_OFF			0
#घोषणा CMD_HDR_CFL_MSK			(0x1ff << CMD_HDR_CFL_OFF)
#घोषणा CMD_HDR_NCQ_TAG_OFF		10
#घोषणा CMD_HDR_NCQ_TAG_MSK		(0x1f << CMD_HDR_NCQ_TAG_OFF)
#घोषणा CMD_HDR_MRFL_OFF		15
#घोषणा CMD_HDR_MRFL_MSK		(0x1ff << CMD_HDR_MRFL_OFF)
#घोषणा CMD_HDR_SG_MOD_OFF		24
#घोषणा CMD_HDR_SG_MOD_MSK		(0x3 << CMD_HDR_SG_MOD_OFF)
#घोषणा CMD_HDR_FIRST_BURST_OFF		26
#घोषणा CMD_HDR_FIRST_BURST_MSK		(0x1 << CMD_HDR_SG_MOD_OFF)
/* dw3 */
#घोषणा CMD_HDR_IPTT_OFF		0
#घोषणा CMD_HDR_IPTT_MSK		(0xffff << CMD_HDR_IPTT_OFF)
/* dw6 */
#घोषणा CMD_HDR_DIF_SGL_LEN_OFF		0
#घोषणा CMD_HDR_DIF_SGL_LEN_MSK		(0xffff << CMD_HDR_DIF_SGL_LEN_OFF)
#घोषणा CMD_HDR_DATA_SGL_LEN_OFF	16
#घोषणा CMD_HDR_DATA_SGL_LEN_MSK	(0xffff << CMD_HDR_DATA_SGL_LEN_OFF)
#घोषणा CMD_HDR_ABORT_IPTT_OFF		16
#घोषणा CMD_HDR_ABORT_IPTT_MSK		(0xffff << CMD_HDR_ABORT_IPTT_OFF)

/* Completion header */
/* dw0 */
#घोषणा CMPLT_HDR_ERR_PHASE_OFF	2
#घोषणा CMPLT_HDR_ERR_PHASE_MSK	(0xff << CMPLT_HDR_ERR_PHASE_OFF)
#घोषणा CMPLT_HDR_RSPNS_XFRD_OFF	10
#घोषणा CMPLT_HDR_RSPNS_XFRD_MSK	(0x1 << CMPLT_HDR_RSPNS_XFRD_OFF)
#घोषणा CMPLT_HDR_ERX_OFF		12
#घोषणा CMPLT_HDR_ERX_MSK		(0x1 << CMPLT_HDR_ERX_OFF)
#घोषणा CMPLT_HDR_ABORT_STAT_OFF	13
#घोषणा CMPLT_HDR_ABORT_STAT_MSK	(0x7 << CMPLT_HDR_ABORT_STAT_OFF)
/* पात_stat */
#घोषणा STAT_IO_NOT_VALID		0x1
#घोषणा STAT_IO_NO_DEVICE		0x2
#घोषणा STAT_IO_COMPLETE		0x3
#घोषणा STAT_IO_ABORTED			0x4
/* dw1 */
#घोषणा CMPLT_HDR_IPTT_OFF		0
#घोषणा CMPLT_HDR_IPTT_MSK		(0xffff << CMPLT_HDR_IPTT_OFF)
#घोषणा CMPLT_HDR_DEV_ID_OFF		16
#घोषणा CMPLT_HDR_DEV_ID_MSK		(0xffff << CMPLT_HDR_DEV_ID_OFF)

/* ITCT header */
/* qw0 */
#घोषणा ITCT_HDR_DEV_TYPE_OFF		0
#घोषणा ITCT_HDR_DEV_TYPE_MSK		(0x3 << ITCT_HDR_DEV_TYPE_OFF)
#घोषणा ITCT_HDR_VALID_OFF		2
#घोषणा ITCT_HDR_VALID_MSK		(0x1 << ITCT_HDR_VALID_OFF)
#घोषणा ITCT_HDR_MCR_OFF		5
#घोषणा ITCT_HDR_MCR_MSK		(0xf << ITCT_HDR_MCR_OFF)
#घोषणा ITCT_HDR_VLN_OFF		9
#घोषणा ITCT_HDR_VLN_MSK		(0xf << ITCT_HDR_VLN_OFF)
#घोषणा ITCT_HDR_SMP_TIMEOUT_OFF	16
#घोषणा ITCT_HDR_SMP_TIMEOUT_8US	1
#घोषणा ITCT_HDR_SMP_TIMEOUT		(ITCT_HDR_SMP_TIMEOUT_8US * \
					 250) /* 2ms */
#घोषणा ITCT_HDR_AWT_CONTINUE_OFF	25
#घोषणा ITCT_HDR_PORT_ID_OFF		28
#घोषणा ITCT_HDR_PORT_ID_MSK		(0xf << ITCT_HDR_PORT_ID_OFF)
/* qw2 */
#घोषणा ITCT_HDR_INLT_OFF		0
#घोषणा ITCT_HDR_INLT_MSK		(0xffffULL << ITCT_HDR_INLT_OFF)
#घोषणा ITCT_HDR_BITLT_OFF		16
#घोषणा ITCT_HDR_BITLT_MSK		(0xffffULL << ITCT_HDR_BITLT_OFF)
#घोषणा ITCT_HDR_MCTLT_OFF		32
#घोषणा ITCT_HDR_MCTLT_MSK		(0xffffULL << ITCT_HDR_MCTLT_OFF)
#घोषणा ITCT_HDR_RTOLT_OFF		48
#घोषणा ITCT_HDR_RTOLT_MSK		(0xffffULL << ITCT_HDR_RTOLT_OFF)

#घोषणा HISI_SAS_FATAL_INT_NR	2

काष्ठा hisi_sas_complete_v2_hdr अणु
	__le32 dw0;
	__le32 dw1;
	__le32 act;
	__le32 dw3;
पूर्ण;

काष्ठा hisi_sas_err_record_v2 अणु
	/* dw0 */
	__le32 trans_tx_fail_type;

	/* dw1 */
	__le32 trans_rx_fail_type;

	/* dw2 */
	__le16 dma_tx_err_type;
	__le16 sipc_rx_err_type;

	/* dw3 */
	__le32 dma_rx_err_type;
पूर्ण;

काष्ठा संकेत_attenuation_s अणु
	u32 de_emphasis;
	u32 preshoot;
	u32 boost;
पूर्ण;

काष्ठा sig_atten_lu_s अणु
	स्थिर काष्ठा संकेत_attenuation_s *att;
	u32 sas_phy_ctrl;
पूर्ण;

अटल स्थिर काष्ठा hisi_sas_hw_error one_bit_ecc_errors[] = अणु
	अणु
		.irq_msk = BIT(SAS_ECC_INTR_DQE_ECC_1B_OFF),
		.msk = HGC_DQE_ECC_1B_ADDR_MSK,
		.shअगरt = HGC_DQE_ECC_1B_ADDR_OFF,
		.msg = "hgc_dqe_ecc1b_intr",
		.reg = HGC_DQE_ECC_ADDR,
	पूर्ण,
	अणु
		.irq_msk = BIT(SAS_ECC_INTR_IOST_ECC_1B_OFF),
		.msk = HGC_IOST_ECC_1B_ADDR_MSK,
		.shअगरt = HGC_IOST_ECC_1B_ADDR_OFF,
		.msg = "hgc_iost_ecc1b_intr",
		.reg = HGC_IOST_ECC_ADDR,
	पूर्ण,
	अणु
		.irq_msk = BIT(SAS_ECC_INTR_ITCT_ECC_1B_OFF),
		.msk = HGC_ITCT_ECC_1B_ADDR_MSK,
		.shअगरt = HGC_ITCT_ECC_1B_ADDR_OFF,
		.msg = "hgc_itct_ecc1b_intr",
		.reg = HGC_ITCT_ECC_ADDR,
	पूर्ण,
	अणु
		.irq_msk = BIT(SAS_ECC_INTR_IOSTLIST_ECC_1B_OFF),
		.msk = HGC_LM_DFX_STATUS2_IOSTLIST_MSK,
		.shअगरt = HGC_LM_DFX_STATUS2_IOSTLIST_OFF,
		.msg = "hgc_iostl_ecc1b_intr",
		.reg = HGC_LM_DFX_STATUS2,
	पूर्ण,
	अणु
		.irq_msk = BIT(SAS_ECC_INTR_ITCTLIST_ECC_1B_OFF),
		.msk = HGC_LM_DFX_STATUS2_ITCTLIST_MSK,
		.shअगरt = HGC_LM_DFX_STATUS2_ITCTLIST_OFF,
		.msg = "hgc_itctl_ecc1b_intr",
		.reg = HGC_LM_DFX_STATUS2,
	पूर्ण,
	अणु
		.irq_msk = BIT(SAS_ECC_INTR_CQE_ECC_1B_OFF),
		.msk = HGC_CQE_ECC_1B_ADDR_MSK,
		.shअगरt = HGC_CQE_ECC_1B_ADDR_OFF,
		.msg = "hgc_cqe_ecc1b_intr",
		.reg = HGC_CQE_ECC_ADDR,
	पूर्ण,
	अणु
		.irq_msk = BIT(SAS_ECC_INTR_NCQ_MEM0_ECC_1B_OFF),
		.msk = HGC_RXM_DFX_STATUS14_MEM0_MSK,
		.shअगरt = HGC_RXM_DFX_STATUS14_MEM0_OFF,
		.msg = "rxm_mem0_ecc1b_intr",
		.reg = HGC_RXM_DFX_STATUS14,
	पूर्ण,
	अणु
		.irq_msk = BIT(SAS_ECC_INTR_NCQ_MEM1_ECC_1B_OFF),
		.msk = HGC_RXM_DFX_STATUS14_MEM1_MSK,
		.shअगरt = HGC_RXM_DFX_STATUS14_MEM1_OFF,
		.msg = "rxm_mem1_ecc1b_intr",
		.reg = HGC_RXM_DFX_STATUS14,
	पूर्ण,
	अणु
		.irq_msk = BIT(SAS_ECC_INTR_NCQ_MEM2_ECC_1B_OFF),
		.msk = HGC_RXM_DFX_STATUS14_MEM2_MSK,
		.shअगरt = HGC_RXM_DFX_STATUS14_MEM2_OFF,
		.msg = "rxm_mem2_ecc1b_intr",
		.reg = HGC_RXM_DFX_STATUS14,
	पूर्ण,
	अणु
		.irq_msk = BIT(SAS_ECC_INTR_NCQ_MEM3_ECC_1B_OFF),
		.msk = HGC_RXM_DFX_STATUS15_MEM3_MSK,
		.shअगरt = HGC_RXM_DFX_STATUS15_MEM3_OFF,
		.msg = "rxm_mem3_ecc1b_intr",
		.reg = HGC_RXM_DFX_STATUS15,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा hisi_sas_hw_error multi_bit_ecc_errors[] = अणु
	अणु
		.irq_msk = BIT(SAS_ECC_INTR_DQE_ECC_MB_OFF),
		.msk = HGC_DQE_ECC_MB_ADDR_MSK,
		.shअगरt = HGC_DQE_ECC_MB_ADDR_OFF,
		.msg = "hgc_dqe_eccbad_intr",
		.reg = HGC_DQE_ECC_ADDR,
	पूर्ण,
	अणु
		.irq_msk = BIT(SAS_ECC_INTR_IOST_ECC_MB_OFF),
		.msk = HGC_IOST_ECC_MB_ADDR_MSK,
		.shअगरt = HGC_IOST_ECC_MB_ADDR_OFF,
		.msg = "hgc_iost_eccbad_intr",
		.reg = HGC_IOST_ECC_ADDR,
	पूर्ण,
	अणु
		.irq_msk = BIT(SAS_ECC_INTR_ITCT_ECC_MB_OFF),
		.msk = HGC_ITCT_ECC_MB_ADDR_MSK,
		.shअगरt = HGC_ITCT_ECC_MB_ADDR_OFF,
		.msg = "hgc_itct_eccbad_intr",
		.reg = HGC_ITCT_ECC_ADDR,
	पूर्ण,
	अणु
		.irq_msk = BIT(SAS_ECC_INTR_IOSTLIST_ECC_MB_OFF),
		.msk = HGC_LM_DFX_STATUS2_IOSTLIST_MSK,
		.shअगरt = HGC_LM_DFX_STATUS2_IOSTLIST_OFF,
		.msg = "hgc_iostl_eccbad_intr",
		.reg = HGC_LM_DFX_STATUS2,
	पूर्ण,
	अणु
		.irq_msk = BIT(SAS_ECC_INTR_ITCTLIST_ECC_MB_OFF),
		.msk = HGC_LM_DFX_STATUS2_ITCTLIST_MSK,
		.shअगरt = HGC_LM_DFX_STATUS2_ITCTLIST_OFF,
		.msg = "hgc_itctl_eccbad_intr",
		.reg = HGC_LM_DFX_STATUS2,
	पूर्ण,
	अणु
		.irq_msk = BIT(SAS_ECC_INTR_CQE_ECC_MB_OFF),
		.msk = HGC_CQE_ECC_MB_ADDR_MSK,
		.shअगरt = HGC_CQE_ECC_MB_ADDR_OFF,
		.msg = "hgc_cqe_eccbad_intr",
		.reg = HGC_CQE_ECC_ADDR,
	पूर्ण,
	अणु
		.irq_msk = BIT(SAS_ECC_INTR_NCQ_MEM0_ECC_MB_OFF),
		.msk = HGC_RXM_DFX_STATUS14_MEM0_MSK,
		.shअगरt = HGC_RXM_DFX_STATUS14_MEM0_OFF,
		.msg = "rxm_mem0_eccbad_intr",
		.reg = HGC_RXM_DFX_STATUS14,
	पूर्ण,
	अणु
		.irq_msk = BIT(SAS_ECC_INTR_NCQ_MEM1_ECC_MB_OFF),
		.msk = HGC_RXM_DFX_STATUS14_MEM1_MSK,
		.shअगरt = HGC_RXM_DFX_STATUS14_MEM1_OFF,
		.msg = "rxm_mem1_eccbad_intr",
		.reg = HGC_RXM_DFX_STATUS14,
	पूर्ण,
	अणु
		.irq_msk = BIT(SAS_ECC_INTR_NCQ_MEM2_ECC_MB_OFF),
		.msk = HGC_RXM_DFX_STATUS14_MEM2_MSK,
		.shअगरt = HGC_RXM_DFX_STATUS14_MEM2_OFF,
		.msg = "rxm_mem2_eccbad_intr",
		.reg = HGC_RXM_DFX_STATUS14,
	पूर्ण,
	अणु
		.irq_msk = BIT(SAS_ECC_INTR_NCQ_MEM3_ECC_MB_OFF),
		.msk = HGC_RXM_DFX_STATUS15_MEM3_MSK,
		.shअगरt = HGC_RXM_DFX_STATUS15_MEM3_OFF,
		.msg = "rxm_mem3_eccbad_intr",
		.reg = HGC_RXM_DFX_STATUS15,
	पूर्ण,
पूर्ण;

क्रमागत अणु
	HISI_SAS_PHY_PHY_UPDOWN,
	HISI_SAS_PHY_CHNL_INT,
	HISI_SAS_PHY_INT_NR
पूर्ण;

क्रमागत अणु
	TRANS_TX_FAIL_BASE = 0x0, /* dw0 */
	TRANS_RX_FAIL_BASE = 0x20, /* dw1 */
	DMA_TX_ERR_BASE = 0x40, /* dw2 bit 15-0 */
	SIPC_RX_ERR_BASE = 0x50, /* dw2 bit 31-16*/
	DMA_RX_ERR_BASE = 0x60, /* dw3 */

	/* trans tx*/
	TRANS_TX_OPEN_FAIL_WITH_IT_NEXUS_LOSS = TRANS_TX_FAIL_BASE, /* 0x0 */
	TRANS_TX_ERR_PHY_NOT_ENABLE, /* 0x1 */
	TRANS_TX_OPEN_CNX_ERR_WRONG_DESTINATION, /* 0x2 */
	TRANS_TX_OPEN_CNX_ERR_ZONE_VIOLATION, /* 0x3 */
	TRANS_TX_OPEN_CNX_ERR_BY_OTHER, /* 0x4 */
	RESERVED0, /* 0x5 */
	TRANS_TX_OPEN_CNX_ERR_AIP_TIMEOUT, /* 0x6 */
	TRANS_TX_OPEN_CNX_ERR_STP_RESOURCES_BUSY, /* 0x7 */
	TRANS_TX_OPEN_CNX_ERR_PROTOCOL_NOT_SUPPORTED, /* 0x8 */
	TRANS_TX_OPEN_CNX_ERR_CONNECTION_RATE_NOT_SUPPORTED, /* 0x9 */
	TRANS_TX_OPEN_CNX_ERR_BAD_DESTINATION, /* 0xa */
	TRANS_TX_OPEN_CNX_ERR_BREAK_RCVD, /* 0xb */
	TRANS_TX_OPEN_CNX_ERR_LOW_PHY_POWER, /* 0xc */
	TRANS_TX_OPEN_CNX_ERR_PATHWAY_BLOCKED, /* 0xd */
	TRANS_TX_OPEN_CNX_ERR_OPEN_TIMEOUT, /* 0xe */
	TRANS_TX_OPEN_CNX_ERR_NO_DESTINATION, /* 0xf */
	TRANS_TX_OPEN_RETRY_ERR_THRESHOLD_REACHED, /* 0x10 */
	TRANS_TX_ERR_FRAME_TXED, /* 0x11 */
	TRANS_TX_ERR_WITH_BREAK_TIMEOUT, /* 0x12 */
	TRANS_TX_ERR_WITH_BREAK_REQUEST, /* 0x13 */
	TRANS_TX_ERR_WITH_BREAK_RECEVIED, /* 0x14 */
	TRANS_TX_ERR_WITH_CLOSE_TIMEOUT, /* 0x15 */
	TRANS_TX_ERR_WITH_CLOSE_NORMAL, /* 0x16 क्रम ssp*/
	TRANS_TX_ERR_WITH_CLOSE_PHYDISALE, /* 0x17 */
	TRANS_TX_ERR_WITH_CLOSE_DWS_TIMEOUT, /* 0x18 */
	TRANS_TX_ERR_WITH_CLOSE_COMINIT, /* 0x19 */
	TRANS_TX_ERR_WITH_NAK_RECEVIED, /* 0x1a क्रम ssp*/
	TRANS_TX_ERR_WITH_ACK_NAK_TIMEOUT, /* 0x1b क्रम ssp*/
	/*IO_TX_ERR_WITH_R_ERR_RECEVIED, [> 0x1b क्रम sata/stp<] */
	TRANS_TX_ERR_WITH_CREDIT_TIMEOUT, /* 0x1c क्रम ssp */
	/*IO_RX_ERR_WITH_SATA_DEVICE_LOST 0x1c क्रम sata/stp */
	TRANS_TX_ERR_WITH_IPTT_CONFLICT, /* 0x1d क्रम ssp/smp */
	TRANS_TX_ERR_WITH_OPEN_BY_DES_OR_OTHERS, /* 0x1e */
	/*IO_TX_ERR_WITH_SYNC_RXD, [> 0x1e <] क्रम sata/stp */
	TRANS_TX_ERR_WITH_WAIT_RECV_TIMEOUT, /* 0x1f क्रम sata/stp */

	/* trans rx */
	TRANS_RX_ERR_WITH_RXFRAME_CRC_ERR = TRANS_RX_FAIL_BASE, /* 0x20 */
	TRANS_RX_ERR_WITH_RXFIS_8B10B_DISP_ERR, /* 0x21 क्रम sata/stp */
	TRANS_RX_ERR_WITH_RXFRAME_HAVE_ERRPRM, /* 0x22 क्रम ssp/smp */
	/*IO_ERR_WITH_RXFIS_8B10B_CODE_ERR, [> 0x22 <] क्रम sata/stp */
	TRANS_RX_ERR_WITH_RXFIS_DECODE_ERROR, /* 0x23 क्रम sata/stp */
	TRANS_RX_ERR_WITH_RXFIS_CRC_ERR, /* 0x24 क्रम sata/stp */
	TRANS_RX_ERR_WITH_RXFRAME_LENGTH_OVERRUN, /* 0x25 क्रम smp */
	/*IO_ERR_WITH_RXFIS_TX SYNCP, [> 0x25 <] क्रम sata/stp */
	TRANS_RX_ERR_WITH_RXFIS_RX_SYNCP, /* 0x26 क्रम sata/stp*/
	TRANS_RX_ERR_WITH_LINK_BUF_OVERRUN, /* 0x27 */
	TRANS_RX_ERR_WITH_BREAK_TIMEOUT, /* 0x28 */
	TRANS_RX_ERR_WITH_BREAK_REQUEST, /* 0x29 */
	TRANS_RX_ERR_WITH_BREAK_RECEVIED, /* 0x2a */
	RESERVED1, /* 0x2b */
	TRANS_RX_ERR_WITH_CLOSE_NORMAL, /* 0x2c */
	TRANS_RX_ERR_WITH_CLOSE_PHY_DISABLE, /* 0x2d */
	TRANS_RX_ERR_WITH_CLOSE_DWS_TIMEOUT, /* 0x2e */
	TRANS_RX_ERR_WITH_CLOSE_COMINIT, /* 0x2f */
	TRANS_RX_ERR_WITH_DATA_LEN0, /* 0x30 क्रम ssp/smp */
	TRANS_RX_ERR_WITH_BAD_HASH, /* 0x31 क्रम ssp */
	/*IO_RX_ERR_WITH_FIS_TOO_SHORT, [> 0x31 <] क्रम sata/stp */
	TRANS_RX_XRDY_WLEN_ZERO_ERR, /* 0x32 क्रम ssp*/
	/*IO_RX_ERR_WITH_FIS_TOO_LONG, [> 0x32 <] क्रम sata/stp */
	TRANS_RX_SSP_FRM_LEN_ERR, /* 0x33 क्रम ssp */
	/*IO_RX_ERR_WITH_SATA_DEVICE_LOST, [> 0x33 <] क्रम sata */
	RESERVED2, /* 0x34 */
	RESERVED3, /* 0x35 */
	RESERVED4, /* 0x36 */
	RESERVED5, /* 0x37 */
	TRANS_RX_ERR_WITH_BAD_FRM_TYPE, /* 0x38 */
	TRANS_RX_SMP_FRM_LEN_ERR, /* 0x39 */
	TRANS_RX_SMP_RESP_TIMEOUT_ERR, /* 0x3a */
	RESERVED6, /* 0x3b */
	RESERVED7, /* 0x3c */
	RESERVED8, /* 0x3d */
	RESERVED9, /* 0x3e */
	TRANS_RX_R_ERR, /* 0x3f */

	/* dma tx */
	DMA_TX_DIF_CRC_ERR = DMA_TX_ERR_BASE, /* 0x40 */
	DMA_TX_DIF_APP_ERR, /* 0x41 */
	DMA_TX_DIF_RPP_ERR, /* 0x42 */
	DMA_TX_DATA_SGL_OVERFLOW, /* 0x43 */
	DMA_TX_DIF_SGL_OVERFLOW, /* 0x44 */
	DMA_TX_UNEXP_XFER_ERR, /* 0x45 */
	DMA_TX_UNEXP_RETRANS_ERR, /* 0x46 */
	DMA_TX_XFER_LEN_OVERFLOW, /* 0x47 */
	DMA_TX_XFER_OFFSET_ERR, /* 0x48 */
	DMA_TX_RAM_ECC_ERR, /* 0x49 */
	DMA_TX_DIF_LEN_ALIGN_ERR, /* 0x4a */
	DMA_TX_MAX_ERR_CODE,

	/* sipc rx */
	SIPC_RX_FIS_STATUS_ERR_BIT_VLD = SIPC_RX_ERR_BASE, /* 0x50 */
	SIPC_RX_PIO_WRSETUP_STATUS_DRQ_ERR, /* 0x51 */
	SIPC_RX_FIS_STATUS_BSY_BIT_ERR, /* 0x52 */
	SIPC_RX_WRSETUP_LEN_ODD_ERR, /* 0x53 */
	SIPC_RX_WRSETUP_LEN_ZERO_ERR, /* 0x54 */
	SIPC_RX_WRDATA_LEN_NOT_MATCH_ERR, /* 0x55 */
	SIPC_RX_NCQ_WRSETUP_OFFSET_ERR, /* 0x56 */
	SIPC_RX_NCQ_WRSETUP_AUTO_ACTIVE_ERR, /* 0x57 */
	SIPC_RX_SATA_UNEXP_FIS_ERR, /* 0x58 */
	SIPC_RX_WRSETUP_ESTATUS_ERR, /* 0x59 */
	SIPC_RX_DATA_UNDERFLOW_ERR, /* 0x5a */
	SIPC_RX_MAX_ERR_CODE,

	/* dma rx */
	DMA_RX_DIF_CRC_ERR = DMA_RX_ERR_BASE, /* 0x60 */
	DMA_RX_DIF_APP_ERR, /* 0x61 */
	DMA_RX_DIF_RPP_ERR, /* 0x62 */
	DMA_RX_DATA_SGL_OVERFLOW, /* 0x63 */
	DMA_RX_DIF_SGL_OVERFLOW, /* 0x64 */
	DMA_RX_DATA_LEN_OVERFLOW, /* 0x65 */
	DMA_RX_DATA_LEN_UNDERFLOW, /* 0x66 */
	DMA_RX_DATA_OFFSET_ERR, /* 0x67 */
	RESERVED10, /* 0x68 */
	DMA_RX_SATA_FRAME_TYPE_ERR, /* 0x69 */
	DMA_RX_RESP_BUF_OVERFLOW, /* 0x6a */
	DMA_RX_UNEXP_RETRANS_RESP_ERR, /* 0x6b */
	DMA_RX_UNEXP_NORM_RESP_ERR, /* 0x6c */
	DMA_RX_UNEXP_RDFRAME_ERR, /* 0x6d */
	DMA_RX_PIO_DATA_LEN_ERR, /* 0x6e */
	DMA_RX_RDSETUP_STATUS_ERR, /* 0x6f */
	DMA_RX_RDSETUP_STATUS_DRQ_ERR, /* 0x70 */
	DMA_RX_RDSETUP_STATUS_BSY_ERR, /* 0x71 */
	DMA_RX_RDSETUP_LEN_ODD_ERR, /* 0x72 */
	DMA_RX_RDSETUP_LEN_ZERO_ERR, /* 0x73 */
	DMA_RX_RDSETUP_LEN_OVER_ERR, /* 0x74 */
	DMA_RX_RDSETUP_OFFSET_ERR, /* 0x75 */
	DMA_RX_RDSETUP_ACTIVE_ERR, /* 0x76 */
	DMA_RX_RDSETUP_ESTATUS_ERR, /* 0x77 */
	DMA_RX_RAM_ECC_ERR, /* 0x78 */
	DMA_RX_UNKNOWN_FRM_ERR, /* 0x79 */
	DMA_RX_MAX_ERR_CODE,
पूर्ण;

#घोषणा HISI_SAS_COMMAND_ENTRIES_V2_HW 4096
#घोषणा HISI_MAX_SATA_SUPPORT_V2_HW	(HISI_SAS_COMMAND_ENTRIES_V2_HW/64 - 1)

#घोषणा सूची_NO_DATA 0
#घोषणा सूची_TO_INI 1
#घोषणा सूची_TO_DEVICE 2
#घोषणा सूची_RESERVED 3

#घोषणा ERR_ON_TX_PHASE(err_phase) (err_phase == 0x2 || \
		err_phase == 0x4 || err_phase == 0x8 ||\
		err_phase == 0x6 || err_phase == 0xa)
#घोषणा ERR_ON_RX_PHASE(err_phase) (err_phase == 0x10 || \
		err_phase == 0x20 || err_phase == 0x40)

अटल व्योम link_समयout_disable_link(काष्ठा समयr_list *t);

अटल u32 hisi_sas_पढ़ो32(काष्ठा hisi_hba *hisi_hba, u32 off)
अणु
	व्योम __iomem *regs = hisi_hba->regs + off;

	वापस पढ़ोl(regs);
पूर्ण

अटल u32 hisi_sas_पढ़ो32_relaxed(काष्ठा hisi_hba *hisi_hba, u32 off)
अणु
	व्योम __iomem *regs = hisi_hba->regs + off;

	वापस पढ़ोl_relaxed(regs);
पूर्ण

अटल व्योम hisi_sas_ग_लिखो32(काष्ठा hisi_hba *hisi_hba, u32 off, u32 val)
अणु
	व्योम __iomem *regs = hisi_hba->regs + off;

	ग_लिखोl(val, regs);
पूर्ण

अटल व्योम hisi_sas_phy_ग_लिखो32(काष्ठा hisi_hba *hisi_hba, पूर्णांक phy_no,
				 u32 off, u32 val)
अणु
	व्योम __iomem *regs = hisi_hba->regs + (0x400 * phy_no) + off;

	ग_लिखोl(val, regs);
पूर्ण

अटल u32 hisi_sas_phy_पढ़ो32(काष्ठा hisi_hba *hisi_hba,
				      पूर्णांक phy_no, u32 off)
अणु
	व्योम __iomem *regs = hisi_hba->regs + (0x400 * phy_no) + off;

	वापस पढ़ोl(regs);
पूर्ण

/* This function needs to be रक्षित from pre-emption. */
अटल पूर्णांक
slot_index_alloc_quirk_v2_hw(काष्ठा hisi_hba *hisi_hba,
			     काष्ठा करोमुख्य_device *device)
अणु
	पूर्णांक sata_dev = dev_is_sata(device);
	व्योम *biपंचांगap = hisi_hba->slot_index_tags;
	काष्ठा hisi_sas_device *sas_dev = device->lldd_dev;
	पूर्णांक sata_idx = sas_dev->sata_idx;
	पूर्णांक start, end;

	अगर (!sata_dev) अणु
		/*
		 * STP link SoC bug workaround: index starts from 1.
		 * additionally, we can only allocate odd IPTT(1~4095)
		 * क्रम SAS/SMP device.
		 */
		start = 1;
		end = hisi_hba->slot_index_count;
	पूर्ण अन्यथा अणु
		अगर (sata_idx >= HISI_MAX_SATA_SUPPORT_V2_HW)
			वापस -EINVAL;

		/*
		 * For SATA device: allocate even IPTT in this पूर्णांकerval
		 * [64*(sata_idx+1), 64*(sata_idx+2)], then each SATA device
		 * own 32 IPTTs. IPTT 0 shall not be used duing to STP link
		 * SoC bug workaround. So we ignore the first 32 even IPTTs.
		 */
		start = 64 * (sata_idx + 1);
		end = 64 * (sata_idx + 2);
	पूर्ण

	spin_lock(&hisi_hba->lock);
	जबतक (1) अणु
		start = find_next_zero_bit(biपंचांगap,
					hisi_hba->slot_index_count, start);
		अगर (start >= end) अणु
			spin_unlock(&hisi_hba->lock);
			वापस -SAS_QUEUE_FULL;
		पूर्ण
		/*
		  * SAS IPTT bit0 should be 1, and SATA IPTT bit0 should be 0.
		  */
		अगर (sata_dev ^ (start & 1))
			अवरोध;
		start++;
	पूर्ण

	set_bit(start, biपंचांगap);
	spin_unlock(&hisi_hba->lock);
	वापस start;
पूर्ण

अटल bool sata_index_alloc_v2_hw(काष्ठा hisi_hba *hisi_hba, पूर्णांक *idx)
अणु
	अचिन्हित पूर्णांक index;
	काष्ठा device *dev = hisi_hba->dev;
	व्योम *biपंचांगap = hisi_hba->sata_dev_biपंचांगap;

	index = find_first_zero_bit(biपंचांगap, HISI_MAX_SATA_SUPPORT_V2_HW);
	अगर (index >= HISI_MAX_SATA_SUPPORT_V2_HW) अणु
		dev_warn(dev, "alloc sata index failed, index=%d\n", index);
		वापस false;
	पूर्ण

	set_bit(index, biपंचांगap);
	*idx = index;
	वापस true;
पूर्ण


अटल काष्ठा
hisi_sas_device *alloc_dev_quirk_v2_hw(काष्ठा करोमुख्य_device *device)
अणु
	काष्ठा hisi_hba *hisi_hba = device->port->ha->lldd_ha;
	काष्ठा hisi_sas_device *sas_dev = शून्य;
	पूर्णांक i, sata_dev = dev_is_sata(device);
	पूर्णांक sata_idx = -1;

	spin_lock(&hisi_hba->lock);

	अगर (sata_dev)
		अगर (!sata_index_alloc_v2_hw(hisi_hba, &sata_idx))
			जाओ out;

	क्रम (i = 0; i < HISI_SAS_MAX_DEVICES; i++) अणु
		/*
		 * SATA device id bit0 should be 0
		 */
		अगर (sata_dev && (i & 1))
			जारी;
		अगर (hisi_hba->devices[i].dev_type == SAS_PHY_UNUSED) अणु
			पूर्णांक queue = i % hisi_hba->queue_count;
			काष्ठा hisi_sas_dq *dq = &hisi_hba->dq[queue];

			hisi_hba->devices[i].device_id = i;
			sas_dev = &hisi_hba->devices[i];
			sas_dev->dev_status = HISI_SAS_DEV_INIT;
			sas_dev->dev_type = device->dev_type;
			sas_dev->hisi_hba = hisi_hba;
			sas_dev->sas_device = device;
			sas_dev->sata_idx = sata_idx;
			sas_dev->dq = dq;
			spin_lock_init(&sas_dev->lock);
			INIT_LIST_HEAD(&hisi_hba->devices[i].list);
			अवरोध;
		पूर्ण
	पूर्ण

out:
	spin_unlock(&hisi_hba->lock);

	वापस sas_dev;
पूर्ण

अटल व्योम config_phy_opt_mode_v2_hw(काष्ठा hisi_hba *hisi_hba, पूर्णांक phy_no)
अणु
	u32 cfg = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no, PHY_CFG);

	cfg &= ~PHY_CFG_DC_OPT_MSK;
	cfg |= 1 << PHY_CFG_DC_OPT_OFF;
	hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, PHY_CFG, cfg);
पूर्ण

अटल व्योम config_id_frame_v2_hw(काष्ठा hisi_hba *hisi_hba, पूर्णांक phy_no)
अणु
	काष्ठा sas_identअगरy_frame identअगरy_frame;
	u32 *identअगरy_buffer;

	स_रखो(&identअगरy_frame, 0, माप(identअगरy_frame));
	identअगरy_frame.dev_type = SAS_END_DEVICE;
	identअगरy_frame.frame_type = 0;
	identअगरy_frame._un1 = 1;
	identअगरy_frame.initiator_bits = SAS_PROTOCOL_ALL;
	identअगरy_frame.target_bits = SAS_PROTOCOL_NONE;
	स_नकल(&identअगरy_frame._un4_11[0], hisi_hba->sas_addr, SAS_ADDR_SIZE);
	स_नकल(&identअगरy_frame.sas_addr[0], hisi_hba->sas_addr,	SAS_ADDR_SIZE);
	identअगरy_frame.phy_id = phy_no;
	identअगरy_buffer = (u32 *)(&identअगरy_frame);

	hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, TX_ID_DWORD0,
			__swab32(identअगरy_buffer[0]));
	hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, TX_ID_DWORD1,
			__swab32(identअगरy_buffer[1]));
	hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, TX_ID_DWORD2,
			__swab32(identअगरy_buffer[2]));
	hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, TX_ID_DWORD3,
			__swab32(identअगरy_buffer[3]));
	hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, TX_ID_DWORD4,
			__swab32(identअगरy_buffer[4]));
	hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, TX_ID_DWORD5,
			__swab32(identअगरy_buffer[5]));
पूर्ण

अटल व्योम setup_itct_v2_hw(काष्ठा hisi_hba *hisi_hba,
			     काष्ठा hisi_sas_device *sas_dev)
अणु
	काष्ठा करोमुख्य_device *device = sas_dev->sas_device;
	काष्ठा device *dev = hisi_hba->dev;
	u64 qw0, device_id = sas_dev->device_id;
	काष्ठा hisi_sas_itct *itct = &hisi_hba->itct[device_id];
	काष्ठा करोमुख्य_device *parent_dev = device->parent;
	काष्ठा asd_sas_port *sas_port = device->port;
	काष्ठा hisi_sas_port *port = to_hisi_sas_port(sas_port);
	u64 sas_addr;

	स_रखो(itct, 0, माप(*itct));

	/* qw0 */
	qw0 = 0;
	चयन (sas_dev->dev_type) अणु
	हाल SAS_END_DEVICE:
	हाल SAS_EDGE_EXPANDER_DEVICE:
	हाल SAS_FANOUT_EXPANDER_DEVICE:
		qw0 = HISI_SAS_DEV_TYPE_SSP << ITCT_HDR_DEV_TYPE_OFF;
		अवरोध;
	हाल SAS_SATA_DEV:
	हाल SAS_SATA_PENDING:
		अगर (parent_dev && dev_is_expander(parent_dev->dev_type))
			qw0 = HISI_SAS_DEV_TYPE_STP << ITCT_HDR_DEV_TYPE_OFF;
		अन्यथा
			qw0 = HISI_SAS_DEV_TYPE_SATA << ITCT_HDR_DEV_TYPE_OFF;
		अवरोध;
	शेष:
		dev_warn(dev, "setup itct: unsupported dev type (%d)\n",
			 sas_dev->dev_type);
	पूर्ण

	qw0 |= ((1 << ITCT_HDR_VALID_OFF) |
		(device->linkrate << ITCT_HDR_MCR_OFF) |
		(1 << ITCT_HDR_VLN_OFF) |
		(ITCT_HDR_SMP_TIMEOUT << ITCT_HDR_SMP_TIMEOUT_OFF) |
		(1 << ITCT_HDR_AWT_CONTINUE_OFF) |
		(port->id << ITCT_HDR_PORT_ID_OFF));
	itct->qw0 = cpu_to_le64(qw0);

	/* qw1 */
	स_नकल(&sas_addr, device->sas_addr, SAS_ADDR_SIZE);
	itct->sas_addr = cpu_to_le64(__swab64(sas_addr));

	/* qw2 */
	अगर (!dev_is_sata(device))
		itct->qw2 = cpu_to_le64((5000ULL << ITCT_HDR_INLT_OFF) |
					(0x1ULL << ITCT_HDR_BITLT_OFF) |
					(0x32ULL << ITCT_HDR_MCTLT_OFF) |
					(0x1ULL << ITCT_HDR_RTOLT_OFF));
पूर्ण

अटल पूर्णांक clear_itct_v2_hw(काष्ठा hisi_hba *hisi_hba,
			    काष्ठा hisi_sas_device *sas_dev)
अणु
	DECLARE_COMPLETION_ONSTACK(completion);
	u64 dev_id = sas_dev->device_id;
	काष्ठा hisi_sas_itct *itct = &hisi_hba->itct[dev_id];
	u32 reg_val = hisi_sas_पढ़ो32(hisi_hba, ENT_INT_SRC3);
	काष्ठा device *dev = hisi_hba->dev;
	पूर्णांक i;

	sas_dev->completion = &completion;

	/* clear the itct पूर्णांकerrupt state */
	अगर (ENT_INT_SRC3_ITC_INT_MSK & reg_val)
		hisi_sas_ग_लिखो32(hisi_hba, ENT_INT_SRC3,
				 ENT_INT_SRC3_ITC_INT_MSK);

	/* need to set रेजिस्टर twice to clear ITCT क्रम v2 hw */
	क्रम (i = 0; i < 2; i++) अणु
		reg_val = ITCT_CLR_EN_MSK | (dev_id & ITCT_DEV_MSK);
		hisi_sas_ग_लिखो32(hisi_hba, ITCT_CLR, reg_val);
		अगर (!रुको_क्रम_completion_समयout(sas_dev->completion,
						 CLEAR_ITCT_TIMEOUT * HZ)) अणु
			dev_warn(dev, "failed to clear ITCT\n");
			वापस -ETIMEDOUT;
		पूर्ण

		स_रखो(itct, 0, माप(काष्ठा hisi_sas_itct));
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम मुक्त_device_v2_hw(काष्ठा hisi_sas_device *sas_dev)
अणु
	काष्ठा hisi_hba *hisi_hba = sas_dev->hisi_hba;

	/* SoC bug workaround */
	अगर (dev_is_sata(sas_dev->sas_device))
		clear_bit(sas_dev->sata_idx, hisi_hba->sata_dev_biपंचांगap);
पूर्ण

अटल पूर्णांक reset_hw_v2_hw(काष्ठा hisi_hba *hisi_hba)
अणु
	पूर्णांक i, reset_val;
	u32 val;
	अचिन्हित दीर्घ end_समय;
	काष्ठा device *dev = hisi_hba->dev;

	/* The mask needs to be set depending on the number of phys */
	अगर (hisi_hba->n_phy == 9)
		reset_val = 0x1fffff;
	अन्यथा
		reset_val = 0x7ffff;

	hisi_sas_ग_लिखो32(hisi_hba, DLVRY_QUEUE_ENABLE, 0);

	/* Disable all of the PHYs */
	क्रम (i = 0; i < hisi_hba->n_phy; i++) अणु
		u32 phy_cfg = hisi_sas_phy_पढ़ो32(hisi_hba, i, PHY_CFG);

		phy_cfg &= ~PHY_CTRL_RESET_MSK;
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, PHY_CFG, phy_cfg);
	पूर्ण
	udelay(50);

	/* Ensure DMA tx & rx idle */
	क्रम (i = 0; i < hisi_hba->n_phy; i++) अणु
		u32 dma_tx_status, dma_rx_status;

		end_समय = jअगरfies + msecs_to_jअगरfies(1000);

		जबतक (1) अणु
			dma_tx_status = hisi_sas_phy_पढ़ो32(hisi_hba, i,
							    DMA_TX_STATUS);
			dma_rx_status = hisi_sas_phy_पढ़ो32(hisi_hba, i,
							    DMA_RX_STATUS);

			अगर (!(dma_tx_status & DMA_TX_STATUS_BUSY_MSK) &&
				!(dma_rx_status & DMA_RX_STATUS_BUSY_MSK))
				अवरोध;

			msleep(20);
			अगर (समय_after(jअगरfies, end_समय))
				वापस -EIO;
		पूर्ण
	पूर्ण

	/* Ensure axi bus idle */
	end_समय = jअगरfies + msecs_to_jअगरfies(1000);
	जबतक (1) अणु
		u32 axi_status =
			hisi_sas_पढ़ो32(hisi_hba, AXI_CFG);

		अगर (axi_status == 0)
			अवरोध;

		msleep(20);
		अगर (समय_after(jअगरfies, end_समय))
			वापस -EIO;
	पूर्ण

	अगर (ACPI_HANDLE(dev)) अणु
		acpi_status s;

		s = acpi_evaluate_object(ACPI_HANDLE(dev), "_RST", शून्य, शून्य);
		अगर (ACPI_FAILURE(s)) अणु
			dev_err(dev, "Reset failed\n");
			वापस -EIO;
		पूर्ण
	पूर्ण अन्यथा अगर (hisi_hba->ctrl) अणु
		/* reset and disable घड़ी*/
		regmap_ग_लिखो(hisi_hba->ctrl, hisi_hba->ctrl_reset_reg,
				reset_val);
		regmap_ग_लिखो(hisi_hba->ctrl, hisi_hba->ctrl_घड़ी_ena_reg + 4,
				reset_val);
		msleep(1);
		regmap_पढ़ो(hisi_hba->ctrl, hisi_hba->ctrl_reset_sts_reg, &val);
		अगर (reset_val != (val & reset_val)) अणु
			dev_err(dev, "SAS reset fail.\n");
			वापस -EIO;
		पूर्ण

		/* De-reset and enable घड़ी*/
		regmap_ग_लिखो(hisi_hba->ctrl, hisi_hba->ctrl_reset_reg + 4,
				reset_val);
		regmap_ग_लिखो(hisi_hba->ctrl, hisi_hba->ctrl_घड़ी_ena_reg,
				reset_val);
		msleep(1);
		regmap_पढ़ो(hisi_hba->ctrl, hisi_hba->ctrl_reset_sts_reg,
				&val);
		अगर (val & reset_val) अणु
			dev_err(dev, "SAS de-reset fail.\n");
			वापस -EIO;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_err(dev, "no reset method\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* This function needs to be called after resetting SAS controller. */
अटल व्योम phys_reject_stp_links_v2_hw(काष्ठा hisi_hba *hisi_hba)
अणु
	u32 cfg;
	पूर्णांक phy_no;

	hisi_hba->reject_stp_links_msk = (1 << hisi_hba->n_phy) - 1;
	क्रम (phy_no = 0; phy_no < hisi_hba->n_phy; phy_no++) अणु
		cfg = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no, CON_CONTROL);
		अगर (!(cfg & CON_CONTROL_CFG_OPEN_ACC_STP_MSK))
			जारी;

		cfg &= ~CON_CONTROL_CFG_OPEN_ACC_STP_MSK;
		hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, CON_CONTROL, cfg);
	पूर्ण
पूर्ण

अटल व्योम phys_try_accept_stp_links_v2_hw(काष्ठा hisi_hba *hisi_hba)
अणु
	पूर्णांक phy_no;
	u32 dma_tx_dfx1;

	क्रम (phy_no = 0; phy_no < hisi_hba->n_phy; phy_no++) अणु
		अगर (!(hisi_hba->reject_stp_links_msk & BIT(phy_no)))
			जारी;

		dma_tx_dfx1 = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no,
						DMA_TX_DFX1);
		अगर (dma_tx_dfx1 & DMA_TX_DFX1_IPTT_MSK) अणु
			u32 cfg = hisi_sas_phy_पढ़ो32(hisi_hba,
				phy_no, CON_CONTROL);

			cfg |= CON_CONTROL_CFG_OPEN_ACC_STP_MSK;
			hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no,
				CON_CONTROL, cfg);
			clear_bit(phy_no, &hisi_hba->reject_stp_links_msk);
		पूर्ण
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा संकेत_attenuation_s x6000 = अणु9200, 0, 10476पूर्ण;
अटल स्थिर काष्ठा sig_atten_lu_s sig_atten_lu[] = अणु
	अणु &x6000, 0x3016a68 पूर्ण,
पूर्ण;

अटल व्योम init_reg_v2_hw(काष्ठा hisi_hba *hisi_hba)
अणु
	काष्ठा device *dev = hisi_hba->dev;
	u32 sas_phy_ctrl = 0x30b9908;
	u32 संकेत[3];
	पूर्णांक i;

	/* Global रेजिस्टरs init */

	/* Deal with am-max-transmissions quirk */
	अगर (device_property_present(dev, "hip06-sas-v2-quirk-amt")) अणु
		hisi_sas_ग_लिखो32(hisi_hba, AM_CFG_MAX_TRANS, 0x2020);
		hisi_sas_ग_लिखो32(hisi_hba, AM_CFG_SINGLE_PORT_MAX_TRANS,
				 0x2020);
	पूर्ण /* Else, use शेषs -> करो nothing */

	hisi_sas_ग_लिखो32(hisi_hba, DLVRY_QUEUE_ENABLE,
			 (u32)((1ULL << hisi_hba->queue_count) - 1));
	hisi_sas_ग_लिखो32(hisi_hba, AXI_USER1, 0xc0000000);
	hisi_sas_ग_लिखो32(hisi_hba, AXI_USER2, 0x10000);
	hisi_sas_ग_लिखो32(hisi_hba, HGC_SAS_TXFAIL_RETRY_CTRL, 0x0);
	hisi_sas_ग_लिखो32(hisi_hba, HGC_SAS_TX_OPEN_FAIL_RETRY_CTRL, 0x7FF);
	hisi_sas_ग_लिखो32(hisi_hba, OPENA_WT_CONTI_TIME, 0x1);
	hisi_sas_ग_लिखो32(hisi_hba, I_T_NEXUS_LOSS_TIME, 0x1F4);
	hisi_sas_ग_लिखो32(hisi_hba, MAX_CON_TIME_LIMIT_TIME, 0x32);
	hisi_sas_ग_लिखो32(hisi_hba, BUS_INACTIVE_LIMIT_TIME, 0x1);
	hisi_sas_ग_लिखो32(hisi_hba, CFG_AGING_TIME, 0x1);
	hisi_sas_ग_लिखो32(hisi_hba, HGC_ERR_STAT_EN, 0x1);
	hisi_sas_ग_लिखो32(hisi_hba, HGC_GET_ITV_TIME, 0x1);
	hisi_sas_ग_लिखो32(hisi_hba, INT_COAL_EN, 0xc);
	hisi_sas_ग_लिखो32(hisi_hba, OQ_INT_COAL_TIME, 0x60);
	hisi_sas_ग_लिखो32(hisi_hba, OQ_INT_COAL_CNT, 0x3);
	hisi_sas_ग_लिखो32(hisi_hba, ENT_INT_COAL_TIME, 0x1);
	hisi_sas_ग_लिखो32(hisi_hba, ENT_INT_COAL_CNT, 0x1);
	hisi_sas_ग_लिखो32(hisi_hba, OQ_INT_SRC, 0x0);
	hisi_sas_ग_लिखो32(hisi_hba, ENT_INT_SRC1, 0xffffffff);
	hisi_sas_ग_लिखो32(hisi_hba, ENT_INT_SRC2, 0xffffffff);
	hisi_sas_ग_लिखो32(hisi_hba, ENT_INT_SRC3, 0xffffffff);
	hisi_sas_ग_लिखो32(hisi_hba, ENT_INT_SRC_MSK1, 0x7efefefe);
	hisi_sas_ग_लिखो32(hisi_hba, ENT_INT_SRC_MSK2, 0x7efefefe);
	hisi_sas_ग_लिखो32(hisi_hba, ENT_INT_SRC_MSK3, 0x7ffe20fe);
	hisi_sas_ग_लिखो32(hisi_hba, SAS_ECC_INTR_MSK, 0xfff00c30);
	क्रम (i = 0; i < hisi_hba->queue_count; i++)
		hisi_sas_ग_लिखो32(hisi_hba, OQ0_INT_SRC_MSK + 0x4 * i, 0);

	hisi_sas_ग_लिखो32(hisi_hba, AXI_AHB_CLK_CFG, 1);
	hisi_sas_ग_लिखो32(hisi_hba, HYPER_STREAM_ID_EN_CFG, 1);

	/* Get sas_phy_ctrl value to deal with TX FFE issue. */
	अगर (!device_property_पढ़ो_u32_array(dev, "hisilicon,signal-attenuation",
					    संकेत, ARRAY_SIZE(संकेत))) अणु
		क्रम (i = 0; i < ARRAY_SIZE(sig_atten_lu); i++) अणु
			स्थिर काष्ठा sig_atten_lu_s *lookup = &sig_atten_lu[i];
			स्थिर काष्ठा संकेत_attenuation_s *att = lookup->att;

			अगर ((संकेत[0] == att->de_emphasis) &&
			    (संकेत[1] == att->preshoot) &&
			    (संकेत[2] == att->boost)) अणु
				sas_phy_ctrl = lookup->sas_phy_ctrl;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (i == ARRAY_SIZE(sig_atten_lu))
			dev_warn(dev, "unknown signal attenuation values, using default PHY ctrl config\n");
	पूर्ण

	क्रम (i = 0; i < hisi_hba->n_phy; i++) अणु
		काष्ठा hisi_sas_phy *phy = &hisi_hba->phy[i];
		काष्ठा asd_sas_phy *sas_phy = &phy->sas_phy;
		u32 prog_phy_link_rate = 0x800;

		अगर (!sas_phy->phy || (sas_phy->phy->maximum_linkrate <
				SAS_LINK_RATE_1_5_GBPS)) अणु
			prog_phy_link_rate = 0x855;
		पूर्ण अन्यथा अणु
			क्रमागत sas_linkrate max = sas_phy->phy->maximum_linkrate;

			prog_phy_link_rate =
				hisi_sas_get_prog_phy_linkrate_mask(max) |
				0x800;
		पूर्ण
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, PROG_PHY_LINK_RATE,
			prog_phy_link_rate);
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, SAS_PHY_CTRL, sas_phy_ctrl);
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, SL_TOUT_CFG, 0x7d7d7d7d);
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, SL_CONTROL, 0x0);
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, TXID_AUTO, 0x2);
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, DONE_RECEIVED_TIME, 0x8);
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, CHL_INT0, 0xffffffff);
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, CHL_INT1, 0xffffffff);
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, CHL_INT2, 0xfff87fff);
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, RXOP_CHECK_CFG_H, 0x1000);
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, CHL_INT1_MSK, 0xff857fff);
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, CHL_INT2_MSK, 0x8ffffbfe);
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, SL_CFG, 0x13f801fc);
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, PHY_CTRL_RDY_MSK, 0x0);
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, PHYCTRL_NOT_RDY_MSK, 0x0);
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, PHYCTRL_DWS_RESET_MSK, 0x0);
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, PHYCTRL_PHY_ENA_MSK, 0x0);
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, SL_RX_BCAST_CHK_MSK, 0x0);
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, CHL_INT_COAL_EN, 0x0);
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, PHYCTRL_OOB_RESTART_MSK, 0x0);
		अगर (hisi_hba->refclk_frequency_mhz == 66)
			hisi_sas_phy_ग_लिखो32(hisi_hba, i, PHY_CTRL, 0x199B694);
		/* अन्यथा, करो nothing -> leave it how you found it */
	पूर्ण

	क्रम (i = 0; i < hisi_hba->queue_count; i++) अणु
		/* Delivery queue */
		hisi_sas_ग_लिखो32(hisi_hba,
				 DLVRY_Q_0_BASE_ADDR_HI + (i * 0x14),
				 upper_32_bits(hisi_hba->cmd_hdr_dma[i]));

		hisi_sas_ग_लिखो32(hisi_hba, DLVRY_Q_0_BASE_ADDR_LO + (i * 0x14),
				 lower_32_bits(hisi_hba->cmd_hdr_dma[i]));

		hisi_sas_ग_लिखो32(hisi_hba, DLVRY_Q_0_DEPTH + (i * 0x14),
				 HISI_SAS_QUEUE_SLOTS);

		/* Completion queue */
		hisi_sas_ग_लिखो32(hisi_hba, COMPL_Q_0_BASE_ADDR_HI + (i * 0x14),
				 upper_32_bits(hisi_hba->complete_hdr_dma[i]));

		hisi_sas_ग_लिखो32(hisi_hba, COMPL_Q_0_BASE_ADDR_LO + (i * 0x14),
				 lower_32_bits(hisi_hba->complete_hdr_dma[i]));

		hisi_sas_ग_लिखो32(hisi_hba, COMPL_Q_0_DEPTH + (i * 0x14),
				 HISI_SAS_QUEUE_SLOTS);
	पूर्ण

	/* itct */
	hisi_sas_ग_लिखो32(hisi_hba, ITCT_BASE_ADDR_LO,
			 lower_32_bits(hisi_hba->itct_dma));

	hisi_sas_ग_लिखो32(hisi_hba, ITCT_BASE_ADDR_HI,
			 upper_32_bits(hisi_hba->itct_dma));

	/* iost */
	hisi_sas_ग_लिखो32(hisi_hba, IOST_BASE_ADDR_LO,
			 lower_32_bits(hisi_hba->iost_dma));

	hisi_sas_ग_लिखो32(hisi_hba, IOST_BASE_ADDR_HI,
			 upper_32_bits(hisi_hba->iost_dma));

	/* अवरोधpoपूर्णांक */
	hisi_sas_ग_लिखो32(hisi_hba, IO_BROKEN_MSG_ADDR_LO,
			 lower_32_bits(hisi_hba->अवरोधpoपूर्णांक_dma));

	hisi_sas_ग_लिखो32(hisi_hba, IO_BROKEN_MSG_ADDR_HI,
			 upper_32_bits(hisi_hba->अवरोधpoपूर्णांक_dma));

	/* SATA broken msg */
	hisi_sas_ग_लिखो32(hisi_hba, IO_SATA_BROKEN_MSG_ADDR_LO,
			 lower_32_bits(hisi_hba->sata_अवरोधpoपूर्णांक_dma));

	hisi_sas_ग_लिखो32(hisi_hba, IO_SATA_BROKEN_MSG_ADDR_HI,
			 upper_32_bits(hisi_hba->sata_अवरोधpoपूर्णांक_dma));

	/* SATA initial fis */
	hisi_sas_ग_लिखो32(hisi_hba, SATA_INITI_D2H_STORE_ADDR_LO,
			 lower_32_bits(hisi_hba->initial_fis_dma));

	hisi_sas_ग_लिखो32(hisi_hba, SATA_INITI_D2H_STORE_ADDR_HI,
			 upper_32_bits(hisi_hba->initial_fis_dma));
पूर्ण

अटल व्योम link_समयout_enable_link(काष्ठा समयr_list *t)
अणु
	काष्ठा hisi_hba *hisi_hba = from_समयr(hisi_hba, t, समयr);
	पूर्णांक i, reg_val;

	क्रम (i = 0; i < hisi_hba->n_phy; i++) अणु
		अगर (hisi_hba->reject_stp_links_msk & BIT(i))
			जारी;

		reg_val = hisi_sas_phy_पढ़ो32(hisi_hba, i, CON_CONTROL);
		अगर (!(reg_val & BIT(0))) अणु
			hisi_sas_phy_ग_लिखो32(hisi_hba, i,
					CON_CONTROL, 0x7);
			अवरोध;
		पूर्ण
	पूर्ण

	hisi_hba->समयr.function = link_समयout_disable_link;
	mod_समयr(&hisi_hba->समयr, jअगरfies + msecs_to_jअगरfies(900));
पूर्ण

अटल व्योम link_समयout_disable_link(काष्ठा समयr_list *t)
अणु
	काष्ठा hisi_hba *hisi_hba = from_समयr(hisi_hba, t, समयr);
	पूर्णांक i, reg_val;

	reg_val = hisi_sas_पढ़ो32(hisi_hba, PHY_STATE);
	क्रम (i = 0; i < hisi_hba->n_phy && reg_val; i++) अणु
		अगर (hisi_hba->reject_stp_links_msk & BIT(i))
			जारी;

		अगर (reg_val & BIT(i)) अणु
			hisi_sas_phy_ग_लिखो32(hisi_hba, i,
					CON_CONTROL, 0x6);
			अवरोध;
		पूर्ण
	पूर्ण

	hisi_hba->समयr.function = link_समयout_enable_link;
	mod_समयr(&hisi_hba->समयr, jअगरfies + msecs_to_jअगरfies(100));
पूर्ण

अटल व्योम set_link_समयr_quirk(काष्ठा hisi_hba *hisi_hba)
अणु
	hisi_hba->समयr.function = link_समयout_disable_link;
	hisi_hba->समयr.expires = jअगरfies + msecs_to_jअगरfies(1000);
	add_समयr(&hisi_hba->समयr);
पूर्ण

अटल पूर्णांक hw_init_v2_hw(काष्ठा hisi_hba *hisi_hba)
अणु
	काष्ठा device *dev = hisi_hba->dev;
	पूर्णांक rc;

	rc = reset_hw_v2_hw(hisi_hba);
	अगर (rc) अणु
		dev_err(dev, "hisi_sas_reset_hw failed, rc=%d\n", rc);
		वापस rc;
	पूर्ण

	msleep(100);
	init_reg_v2_hw(hisi_hba);

	वापस 0;
पूर्ण

अटल व्योम enable_phy_v2_hw(काष्ठा hisi_hba *hisi_hba, पूर्णांक phy_no)
अणु
	u32 cfg = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no, PHY_CFG);

	cfg |= PHY_CFG_ENA_MSK;
	hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, PHY_CFG, cfg);
पूर्ण

अटल bool is_sata_phy_v2_hw(काष्ठा hisi_hba *hisi_hba, पूर्णांक phy_no)
अणु
	u32 context;

	context = hisi_sas_पढ़ो32(hisi_hba, PHY_CONTEXT);
	अगर (context & (1 << phy_no))
		वापस true;

	वापस false;
पूर्ण

अटल bool tx_fअगरo_is_empty_v2_hw(काष्ठा hisi_hba *hisi_hba, पूर्णांक phy_no)
अणु
	u32 dfx_val;

	dfx_val = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no, DMA_TX_DFX1);

	अगर (dfx_val & BIT(16))
		वापस false;

	वापस true;
पूर्ण

अटल bool axi_bus_is_idle_v2_hw(काष्ठा hisi_hba *hisi_hba, पूर्णांक phy_no)
अणु
	पूर्णांक i, max_loop = 1000;
	काष्ठा device *dev = hisi_hba->dev;
	u32 status, axi_status, dfx_val, dfx_tx_val;

	क्रम (i = 0; i < max_loop; i++) अणु
		status = hisi_sas_पढ़ो32_relaxed(hisi_hba,
			AXI_MASTER_CFG_BASE + AM_CURR_TRANS_RETURN);

		axi_status = hisi_sas_पढ़ो32(hisi_hba, AXI_CFG);
		dfx_val = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no, DMA_TX_DFX1);
		dfx_tx_val = hisi_sas_phy_पढ़ो32(hisi_hba,
			phy_no, DMA_TX_FIFO_DFX0);

		अगर ((status == 0x3) && (axi_status == 0x0) &&
		    (dfx_val & BIT(20)) && (dfx_tx_val & BIT(10)))
			वापस true;
		udelay(10);
	पूर्ण
	dev_err(dev, "bus is not idle phy%d, axi150:0x%x axi100:0x%x port204:0x%x port240:0x%x\n",
			phy_no, status, axi_status,
			dfx_val, dfx_tx_val);
	वापस false;
पूर्ण

अटल bool रुको_io_करोne_v2_hw(काष्ठा hisi_hba *hisi_hba, पूर्णांक phy_no)
अणु
	पूर्णांक i, max_loop = 1000;
	काष्ठा device *dev = hisi_hba->dev;
	u32 status, tx_dfx0;

	क्रम (i = 0; i < max_loop; i++) अणु
		status = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no, LINK_DFX2);
		status = (status & 0x3fc0) >> 6;

		अगर (status != 0x1)
			वापस true;

		tx_dfx0 = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no, DMA_TX_DFX0);
		अगर ((tx_dfx0 & 0x1ff) == 0x2)
			वापस true;
		udelay(10);
	पूर्ण
	dev_err(dev, "IO not done phy%d, port264:0x%x port200:0x%x\n",
			phy_no, status, tx_dfx0);
	वापस false;
पूर्ण

अटल bool allowed_disable_phy_v2_hw(काष्ठा hisi_hba *hisi_hba, पूर्णांक phy_no)
अणु
	अगर (tx_fअगरo_is_empty_v2_hw(hisi_hba, phy_no))
		वापस true;

	अगर (!axi_bus_is_idle_v2_hw(hisi_hba, phy_no))
		वापस false;

	अगर (!रुको_io_करोne_v2_hw(hisi_hba, phy_no))
		वापस false;

	वापस true;
पूर्ण


अटल व्योम disable_phy_v2_hw(काष्ठा hisi_hba *hisi_hba, पूर्णांक phy_no)
अणु
	u32 cfg, axi_val, dfx0_val, txid_स्वतः;
	काष्ठा device *dev = hisi_hba->dev;

	/* Close axi bus. */
	axi_val = hisi_sas_पढ़ो32(hisi_hba, AXI_MASTER_CFG_BASE +
				AM_CTRL_GLOBAL);
	axi_val |= 0x1;
	hisi_sas_ग_लिखो32(hisi_hba, AXI_MASTER_CFG_BASE +
		AM_CTRL_GLOBAL, axi_val);

	अगर (is_sata_phy_v2_hw(hisi_hba, phy_no)) अणु
		अगर (allowed_disable_phy_v2_hw(hisi_hba, phy_no))
			जाओ करो_disable;

		/* Reset host controller. */
		queue_work(hisi_hba->wq, &hisi_hba->rst_work);
		वापस;
	पूर्ण

	dfx0_val = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no, PORT_DFX0);
	dfx0_val = (dfx0_val & 0x1fc0) >> 6;
	अगर (dfx0_val != 0x4)
		जाओ करो_disable;

	अगर (!tx_fअगरo_is_empty_v2_hw(hisi_hba, phy_no)) अणु
		dev_warn(dev, "phy%d, wait tx fifo need send break\n",
			phy_no);
		txid_स्वतः = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no,
					TXID_AUTO);
		txid_स्वतः |= TXID_AUTO_CTB_MSK;
		hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, TXID_AUTO,
					txid_स्वतः);
	पूर्ण

करो_disable:
	cfg = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no, PHY_CFG);
	cfg &= ~PHY_CFG_ENA_MSK;
	hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, PHY_CFG, cfg);

	/* Open axi bus. */
	axi_val &= ~0x1;
	hisi_sas_ग_लिखो32(hisi_hba, AXI_MASTER_CFG_BASE +
		AM_CTRL_GLOBAL, axi_val);
पूर्ण

अटल व्योम start_phy_v2_hw(काष्ठा hisi_hba *hisi_hba, पूर्णांक phy_no)
अणु
	config_id_frame_v2_hw(hisi_hba, phy_no);
	config_phy_opt_mode_v2_hw(hisi_hba, phy_no);
	enable_phy_v2_hw(hisi_hba, phy_no);
पूर्ण

अटल व्योम phy_hard_reset_v2_hw(काष्ठा hisi_hba *hisi_hba, पूर्णांक phy_no)
अणु
	काष्ठा hisi_sas_phy *phy = &hisi_hba->phy[phy_no];
	u32 txid_स्वतः;

	hisi_sas_phy_enable(hisi_hba, phy_no, 0);
	अगर (phy->identअगरy.device_type == SAS_END_DEVICE) अणु
		txid_स्वतः = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no, TXID_AUTO);
		hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, TXID_AUTO,
					txid_स्वतः | TX_HARDRST_MSK);
	पूर्ण
	msleep(100);
	hisi_sas_phy_enable(hisi_hba, phy_no, 1);
पूर्ण

अटल व्योम phy_get_events_v2_hw(काष्ठा hisi_hba *hisi_hba, पूर्णांक phy_no)
अणु
	काष्ठा hisi_sas_phy *phy = &hisi_hba->phy[phy_no];
	काष्ठा asd_sas_phy *sas_phy = &phy->sas_phy;
	काष्ठा sas_phy *sphy = sas_phy->phy;
	u32 err4_reg_val, err6_reg_val;

	/* loss dword syn, phy reset problem */
	err4_reg_val = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no, SAS_ERR_CNT4_REG);

	/* disparity err, invalid dword */
	err6_reg_val = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no, SAS_ERR_CNT6_REG);

	sphy->loss_of_dword_sync_count += (err4_reg_val >> 16) & 0xFFFF;
	sphy->phy_reset_problem_count += err4_reg_val & 0xFFFF;
	sphy->invalid_dword_count += (err6_reg_val & 0xFF0000) >> 16;
	sphy->running_disparity_error_count += err6_reg_val & 0xFF;
पूर्ण

अटल व्योम phys_init_v2_hw(काष्ठा hisi_hba *hisi_hba)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < hisi_hba->n_phy; i++) अणु
		काष्ठा hisi_sas_phy *phy = &hisi_hba->phy[i];
		काष्ठा asd_sas_phy *sas_phy = &phy->sas_phy;

		अगर (!sas_phy->phy->enabled)
			जारी;

		hisi_sas_phy_enable(hisi_hba, i, 1);
	पूर्ण
पूर्ण

अटल व्योम sl_notअगरy_ssp_v2_hw(काष्ठा hisi_hba *hisi_hba, पूर्णांक phy_no)
अणु
	u32 sl_control;

	sl_control = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no, SL_CONTROL);
	sl_control |= SL_CONTROL_NOTIFY_EN_MSK;
	hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, SL_CONTROL, sl_control);
	msleep(1);
	sl_control = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no, SL_CONTROL);
	sl_control &= ~SL_CONTROL_NOTIFY_EN_MSK;
	hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, SL_CONTROL, sl_control);
पूर्ण

अटल क्रमागत sas_linkrate phy_get_max_linkrate_v2_hw(व्योम)
अणु
	वापस SAS_LINK_RATE_12_0_GBPS;
पूर्ण

अटल व्योम phy_set_linkrate_v2_hw(काष्ठा hisi_hba *hisi_hba, पूर्णांक phy_no,
		काष्ठा sas_phy_linkrates *r)
अणु
	क्रमागत sas_linkrate max = r->maximum_linkrate;
	u32 prog_phy_link_rate = 0x800;

	prog_phy_link_rate |= hisi_sas_get_prog_phy_linkrate_mask(max);
	hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, PROG_PHY_LINK_RATE,
			     prog_phy_link_rate);
पूर्ण

अटल पूर्णांक get_wideport_biपंचांगap_v2_hw(काष्ठा hisi_hba *hisi_hba, पूर्णांक port_id)
अणु
	पूर्णांक i, biपंचांगap = 0;
	u32 phy_port_num_ma = hisi_sas_पढ़ो32(hisi_hba, PHY_PORT_NUM_MA);
	u32 phy_state = hisi_sas_पढ़ो32(hisi_hba, PHY_STATE);

	क्रम (i = 0; i < (hisi_hba->n_phy < 9 ? hisi_hba->n_phy : 8); i++)
		अगर (phy_state & 1 << i)
			अगर (((phy_port_num_ma >> (i * 4)) & 0xf) == port_id)
				biपंचांगap |= 1 << i;

	अगर (hisi_hba->n_phy == 9) अणु
		u32 port_state = hisi_sas_पढ़ो32(hisi_hba, PORT_STATE);

		अगर (phy_state & 1 << 8)
			अगर (((port_state & PORT_STATE_PHY8_PORT_NUM_MSK) >>
			     PORT_STATE_PHY8_PORT_NUM_OFF) == port_id)
				biपंचांगap |= 1 << 9;
	पूर्ण

	वापस biपंचांगap;
पूर्ण

/* DQ lock must be taken here */
अटल व्योम start_delivery_v2_hw(काष्ठा hisi_sas_dq *dq)
अणु
	काष्ठा hisi_hba *hisi_hba = dq->hisi_hba;
	काष्ठा hisi_sas_slot *s, *s1, *s2 = शून्य;
	पूर्णांक dlvry_queue = dq->id;
	पूर्णांक wp;

	list_क्रम_each_entry_safe(s, s1, &dq->list, delivery) अणु
		अगर (!s->पढ़ोy)
			अवरोध;
		s2 = s;
		list_del(&s->delivery);
	पूर्ण

	अगर (!s2)
		वापस;

	/*
	 * Ensure that memories क्रम slots built on other CPUs is observed.
	 */
	smp_rmb();
	wp = (s2->dlvry_queue_slot + 1) % HISI_SAS_QUEUE_SLOTS;

	hisi_sas_ग_लिखो32(hisi_hba, DLVRY_Q_0_WR_PTR + (dlvry_queue * 0x14), wp);
पूर्ण

अटल व्योम prep_prd_sge_v2_hw(काष्ठा hisi_hba *hisi_hba,
			      काष्ठा hisi_sas_slot *slot,
			      काष्ठा hisi_sas_cmd_hdr *hdr,
			      काष्ठा scatterlist *scatter,
			      पूर्णांक n_elem)
अणु
	काष्ठा hisi_sas_sge_page *sge_page = hisi_sas_sge_addr_mem(slot);
	काष्ठा scatterlist *sg;
	पूर्णांक i;

	क्रम_each_sg(scatter, sg, n_elem, i) अणु
		काष्ठा hisi_sas_sge *entry = &sge_page->sge[i];

		entry->addr = cpu_to_le64(sg_dma_address(sg));
		entry->page_ctrl_0 = entry->page_ctrl_1 = 0;
		entry->data_len = cpu_to_le32(sg_dma_len(sg));
		entry->data_off = 0;
	पूर्ण

	hdr->prd_table_addr = cpu_to_le64(hisi_sas_sge_addr_dma(slot));

	hdr->sg_len = cpu_to_le32(n_elem << CMD_HDR_DATA_SGL_LEN_OFF);
पूर्ण

अटल व्योम prep_smp_v2_hw(काष्ठा hisi_hba *hisi_hba,
			  काष्ठा hisi_sas_slot *slot)
अणु
	काष्ठा sas_task *task = slot->task;
	काष्ठा hisi_sas_cmd_hdr *hdr = slot->cmd_hdr;
	काष्ठा करोमुख्य_device *device = task->dev;
	काष्ठा hisi_sas_port *port = slot->port;
	काष्ठा scatterlist *sg_req;
	काष्ठा hisi_sas_device *sas_dev = device->lldd_dev;
	dma_addr_t req_dma_addr;
	अचिन्हित पूर्णांक req_len;

	/* req */
	sg_req = &task->smp_task.smp_req;
	req_dma_addr = sg_dma_address(sg_req);
	req_len = sg_dma_len(&task->smp_task.smp_req);

	/* create header */
	/* dw0 */
	hdr->dw0 = cpu_to_le32((port->id << CMD_HDR_PORT_OFF) |
			       (1 << CMD_HDR_PRIORITY_OFF) | /* high pri */
			       (2 << CMD_HDR_CMD_OFF)); /* smp */

	/* map itct entry */
	hdr->dw1 = cpu_to_le32((sas_dev->device_id << CMD_HDR_DEV_ID_OFF) |
			       (1 << CMD_HDR_FRAME_TYPE_OFF) |
			       (सूची_NO_DATA << CMD_HDR_सूची_OFF));

	/* dw2 */
	hdr->dw2 = cpu_to_le32((((req_len - 4) / 4) << CMD_HDR_CFL_OFF) |
			       (HISI_SAS_MAX_SMP_RESP_SZ / 4 <<
			       CMD_HDR_MRFL_OFF));

	hdr->transfer_tags = cpu_to_le32(slot->idx << CMD_HDR_IPTT_OFF);

	hdr->cmd_table_addr = cpu_to_le64(req_dma_addr);
	hdr->sts_buffer_addr = cpu_to_le64(hisi_sas_status_buf_addr_dma(slot));
पूर्ण

अटल व्योम prep_ssp_v2_hw(काष्ठा hisi_hba *hisi_hba,
			  काष्ठा hisi_sas_slot *slot)
अणु
	काष्ठा sas_task *task = slot->task;
	काष्ठा hisi_sas_cmd_hdr *hdr = slot->cmd_hdr;
	काष्ठा करोमुख्य_device *device = task->dev;
	काष्ठा hisi_sas_device *sas_dev = device->lldd_dev;
	काष्ठा hisi_sas_port *port = slot->port;
	काष्ठा sas_ssp_task *ssp_task = &task->ssp_task;
	काष्ठा scsi_cmnd *scsi_cmnd = ssp_task->cmd;
	काष्ठा hisi_sas_पंचांगf_task *पंचांगf = slot->पंचांगf;
	पूर्णांक has_data = 0, priority = !!पंचांगf;
	u8 *buf_cmd;
	u32 dw1 = 0, dw2 = 0;

	hdr->dw0 = cpu_to_le32((1 << CMD_HDR_RESP_REPORT_OFF) |
			       (2 << CMD_HDR_TLR_CTRL_OFF) |
			       (port->id << CMD_HDR_PORT_OFF) |
			       (priority << CMD_HDR_PRIORITY_OFF) |
			       (1 << CMD_HDR_CMD_OFF)); /* ssp */

	dw1 = 1 << CMD_HDR_VDTL_OFF;
	अगर (पंचांगf) अणु
		dw1 |= 2 << CMD_HDR_FRAME_TYPE_OFF;
		dw1 |= सूची_NO_DATA << CMD_HDR_सूची_OFF;
	पूर्ण अन्यथा अणु
		dw1 |= 1 << CMD_HDR_FRAME_TYPE_OFF;
		चयन (scsi_cmnd->sc_data_direction) अणु
		हाल DMA_TO_DEVICE:
			has_data = 1;
			dw1 |= सूची_TO_DEVICE << CMD_HDR_सूची_OFF;
			अवरोध;
		हाल DMA_FROM_DEVICE:
			has_data = 1;
			dw1 |= सूची_TO_INI << CMD_HDR_सूची_OFF;
			अवरोध;
		शेष:
			dw1 &= ~CMD_HDR_सूची_MSK;
		पूर्ण
	पूर्ण

	/* map itct entry */
	dw1 |= sas_dev->device_id << CMD_HDR_DEV_ID_OFF;
	hdr->dw1 = cpu_to_le32(dw1);

	dw2 = (((माप(काष्ठा ssp_command_iu) + माप(काष्ठा ssp_frame_hdr)
	      + 3) / 4) << CMD_HDR_CFL_OFF) |
	      ((HISI_SAS_MAX_SSP_RESP_SZ / 4) << CMD_HDR_MRFL_OFF) |
	      (2 << CMD_HDR_SG_MOD_OFF);
	hdr->dw2 = cpu_to_le32(dw2);

	hdr->transfer_tags = cpu_to_le32(slot->idx);

	अगर (has_data)
		prep_prd_sge_v2_hw(hisi_hba, slot, hdr, task->scatter,
					slot->n_elem);

	hdr->data_transfer_len = cpu_to_le32(task->total_xfer_len);
	hdr->cmd_table_addr = cpu_to_le64(hisi_sas_cmd_hdr_addr_dma(slot));
	hdr->sts_buffer_addr = cpu_to_le64(hisi_sas_status_buf_addr_dma(slot));

	buf_cmd = hisi_sas_cmd_hdr_addr_mem(slot) +
		माप(काष्ठा ssp_frame_hdr);

	स_नकल(buf_cmd, &task->ssp_task.LUN, 8);
	अगर (!पंचांगf) अणु
		buf_cmd[9] = task->ssp_task.task_attr |
				(task->ssp_task.task_prio << 3);
		स_नकल(buf_cmd + 12, task->ssp_task.cmd->cmnd,
				task->ssp_task.cmd->cmd_len);
	पूर्ण अन्यथा अणु
		buf_cmd[10] = पंचांगf->पंचांगf;
		चयन (पंचांगf->पंचांगf) अणु
		हाल TMF_ABORT_TASK:
		हाल TMF_QUERY_TASK:
			buf_cmd[12] =
				(पंचांगf->tag_of_task_to_be_managed >> 8) & 0xff;
			buf_cmd[13] =
				पंचांगf->tag_of_task_to_be_managed & 0xff;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

#घोषणा TRANS_TX_ERR	0
#घोषणा TRANS_RX_ERR	1
#घोषणा DMA_TX_ERR		2
#घोषणा SIPC_RX_ERR		3
#घोषणा DMA_RX_ERR		4

#घोषणा DMA_TX_ERR_OFF	0
#घोषणा DMA_TX_ERR_MSK	(0xffff << DMA_TX_ERR_OFF)
#घोषणा SIPC_RX_ERR_OFF	16
#घोषणा SIPC_RX_ERR_MSK (0xffff << SIPC_RX_ERR_OFF)

अटल पूर्णांक parse_trans_tx_err_code_v2_hw(u32 err_msk)
अणु
	अटल स्थिर u8 trans_tx_err_code_prio[] = अणु
		TRANS_TX_OPEN_FAIL_WITH_IT_NEXUS_LOSS,
		TRANS_TX_ERR_PHY_NOT_ENABLE,
		TRANS_TX_OPEN_CNX_ERR_WRONG_DESTINATION,
		TRANS_TX_OPEN_CNX_ERR_ZONE_VIOLATION,
		TRANS_TX_OPEN_CNX_ERR_BY_OTHER,
		RESERVED0,
		TRANS_TX_OPEN_CNX_ERR_AIP_TIMEOUT,
		TRANS_TX_OPEN_CNX_ERR_STP_RESOURCES_BUSY,
		TRANS_TX_OPEN_CNX_ERR_PROTOCOL_NOT_SUPPORTED,
		TRANS_TX_OPEN_CNX_ERR_CONNECTION_RATE_NOT_SUPPORTED,
		TRANS_TX_OPEN_CNX_ERR_BAD_DESTINATION,
		TRANS_TX_OPEN_CNX_ERR_BREAK_RCVD,
		TRANS_TX_OPEN_CNX_ERR_LOW_PHY_POWER,
		TRANS_TX_OPEN_CNX_ERR_PATHWAY_BLOCKED,
		TRANS_TX_OPEN_CNX_ERR_OPEN_TIMEOUT,
		TRANS_TX_OPEN_CNX_ERR_NO_DESTINATION,
		TRANS_TX_OPEN_RETRY_ERR_THRESHOLD_REACHED,
		TRANS_TX_ERR_WITH_CLOSE_PHYDISALE,
		TRANS_TX_ERR_WITH_CLOSE_DWS_TIMEOUT,
		TRANS_TX_ERR_WITH_CLOSE_COMINIT,
		TRANS_TX_ERR_WITH_BREAK_TIMEOUT,
		TRANS_TX_ERR_WITH_BREAK_REQUEST,
		TRANS_TX_ERR_WITH_BREAK_RECEVIED,
		TRANS_TX_ERR_WITH_CLOSE_TIMEOUT,
		TRANS_TX_ERR_WITH_CLOSE_NORMAL,
		TRANS_TX_ERR_WITH_NAK_RECEVIED,
		TRANS_TX_ERR_WITH_ACK_NAK_TIMEOUT,
		TRANS_TX_ERR_WITH_CREDIT_TIMEOUT,
		TRANS_TX_ERR_WITH_IPTT_CONFLICT,
		TRANS_TX_ERR_WITH_OPEN_BY_DES_OR_OTHERS,
		TRANS_TX_ERR_WITH_WAIT_RECV_TIMEOUT,
	पूर्ण;
	पूर्णांक index, i;

	क्रम (i = 0; i < ARRAY_SIZE(trans_tx_err_code_prio); i++) अणु
		index = trans_tx_err_code_prio[i] - TRANS_TX_FAIL_BASE;
		अगर (err_msk & (1 << index))
			वापस trans_tx_err_code_prio[i];
	पूर्ण
	वापस -1;
पूर्ण

अटल पूर्णांक parse_trans_rx_err_code_v2_hw(u32 err_msk)
अणु
	अटल स्थिर u8 trans_rx_err_code_prio[] = अणु
		TRANS_RX_ERR_WITH_RXFRAME_CRC_ERR,
		TRANS_RX_ERR_WITH_RXFIS_8B10B_DISP_ERR,
		TRANS_RX_ERR_WITH_RXFRAME_HAVE_ERRPRM,
		TRANS_RX_ERR_WITH_RXFIS_DECODE_ERROR,
		TRANS_RX_ERR_WITH_RXFIS_CRC_ERR,
		TRANS_RX_ERR_WITH_RXFRAME_LENGTH_OVERRUN,
		TRANS_RX_ERR_WITH_RXFIS_RX_SYNCP,
		TRANS_RX_ERR_WITH_LINK_BUF_OVERRUN,
		TRANS_RX_ERR_WITH_CLOSE_PHY_DISABLE,
		TRANS_RX_ERR_WITH_CLOSE_DWS_TIMEOUT,
		TRANS_RX_ERR_WITH_CLOSE_COMINIT,
		TRANS_RX_ERR_WITH_BREAK_TIMEOUT,
		TRANS_RX_ERR_WITH_BREAK_REQUEST,
		TRANS_RX_ERR_WITH_BREAK_RECEVIED,
		RESERVED1,
		TRANS_RX_ERR_WITH_CLOSE_NORMAL,
		TRANS_RX_ERR_WITH_DATA_LEN0,
		TRANS_RX_ERR_WITH_BAD_HASH,
		TRANS_RX_XRDY_WLEN_ZERO_ERR,
		TRANS_RX_SSP_FRM_LEN_ERR,
		RESERVED2,
		RESERVED3,
		RESERVED4,
		RESERVED5,
		TRANS_RX_ERR_WITH_BAD_FRM_TYPE,
		TRANS_RX_SMP_FRM_LEN_ERR,
		TRANS_RX_SMP_RESP_TIMEOUT_ERR,
		RESERVED6,
		RESERVED7,
		RESERVED8,
		RESERVED9,
		TRANS_RX_R_ERR,
	पूर्ण;
	पूर्णांक index, i;

	क्रम (i = 0; i < ARRAY_SIZE(trans_rx_err_code_prio); i++) अणु
		index = trans_rx_err_code_prio[i] - TRANS_RX_FAIL_BASE;
		अगर (err_msk & (1 << index))
			वापस trans_rx_err_code_prio[i];
	पूर्ण
	वापस -1;
पूर्ण

अटल पूर्णांक parse_dma_tx_err_code_v2_hw(u32 err_msk)
अणु
	अटल स्थिर u8 dma_tx_err_code_prio[] = अणु
		DMA_TX_UNEXP_XFER_ERR,
		DMA_TX_UNEXP_RETRANS_ERR,
		DMA_TX_XFER_LEN_OVERFLOW,
		DMA_TX_XFER_OFFSET_ERR,
		DMA_TX_RAM_ECC_ERR,
		DMA_TX_DIF_LEN_ALIGN_ERR,
		DMA_TX_DIF_CRC_ERR,
		DMA_TX_DIF_APP_ERR,
		DMA_TX_DIF_RPP_ERR,
		DMA_TX_DATA_SGL_OVERFLOW,
		DMA_TX_DIF_SGL_OVERFLOW,
	पूर्ण;
	पूर्णांक index, i;

	क्रम (i = 0; i < ARRAY_SIZE(dma_tx_err_code_prio); i++) अणु
		index = dma_tx_err_code_prio[i] - DMA_TX_ERR_BASE;
		err_msk = err_msk & DMA_TX_ERR_MSK;
		अगर (err_msk & (1 << index))
			वापस dma_tx_err_code_prio[i];
	पूर्ण
	वापस -1;
पूर्ण

अटल पूर्णांक parse_sipc_rx_err_code_v2_hw(u32 err_msk)
अणु
	अटल स्थिर u8 sipc_rx_err_code_prio[] = अणु
		SIPC_RX_FIS_STATUS_ERR_BIT_VLD,
		SIPC_RX_PIO_WRSETUP_STATUS_DRQ_ERR,
		SIPC_RX_FIS_STATUS_BSY_BIT_ERR,
		SIPC_RX_WRSETUP_LEN_ODD_ERR,
		SIPC_RX_WRSETUP_LEN_ZERO_ERR,
		SIPC_RX_WRDATA_LEN_NOT_MATCH_ERR,
		SIPC_RX_NCQ_WRSETUP_OFFSET_ERR,
		SIPC_RX_NCQ_WRSETUP_AUTO_ACTIVE_ERR,
		SIPC_RX_SATA_UNEXP_FIS_ERR,
		SIPC_RX_WRSETUP_ESTATUS_ERR,
		SIPC_RX_DATA_UNDERFLOW_ERR,
	पूर्ण;
	पूर्णांक index, i;

	क्रम (i = 0; i < ARRAY_SIZE(sipc_rx_err_code_prio); i++) अणु
		index = sipc_rx_err_code_prio[i] - SIPC_RX_ERR_BASE;
		err_msk = err_msk & SIPC_RX_ERR_MSK;
		अगर (err_msk & (1 << (index + 0x10)))
			वापस sipc_rx_err_code_prio[i];
	पूर्ण
	वापस -1;
पूर्ण

अटल पूर्णांक parse_dma_rx_err_code_v2_hw(u32 err_msk)
अणु
	अटल स्थिर u8 dma_rx_err_code_prio[] = अणु
		DMA_RX_UNKNOWN_FRM_ERR,
		DMA_RX_DATA_LEN_OVERFLOW,
		DMA_RX_DATA_LEN_UNDERFLOW,
		DMA_RX_DATA_OFFSET_ERR,
		RESERVED10,
		DMA_RX_SATA_FRAME_TYPE_ERR,
		DMA_RX_RESP_BUF_OVERFLOW,
		DMA_RX_UNEXP_RETRANS_RESP_ERR,
		DMA_RX_UNEXP_NORM_RESP_ERR,
		DMA_RX_UNEXP_RDFRAME_ERR,
		DMA_RX_PIO_DATA_LEN_ERR,
		DMA_RX_RDSETUP_STATUS_ERR,
		DMA_RX_RDSETUP_STATUS_DRQ_ERR,
		DMA_RX_RDSETUP_STATUS_BSY_ERR,
		DMA_RX_RDSETUP_LEN_ODD_ERR,
		DMA_RX_RDSETUP_LEN_ZERO_ERR,
		DMA_RX_RDSETUP_LEN_OVER_ERR,
		DMA_RX_RDSETUP_OFFSET_ERR,
		DMA_RX_RDSETUP_ACTIVE_ERR,
		DMA_RX_RDSETUP_ESTATUS_ERR,
		DMA_RX_RAM_ECC_ERR,
		DMA_RX_DIF_CRC_ERR,
		DMA_RX_DIF_APP_ERR,
		DMA_RX_DIF_RPP_ERR,
		DMA_RX_DATA_SGL_OVERFLOW,
		DMA_RX_DIF_SGL_OVERFLOW,
	पूर्ण;
	पूर्णांक index, i;

	क्रम (i = 0; i < ARRAY_SIZE(dma_rx_err_code_prio); i++) अणु
		index = dma_rx_err_code_prio[i] - DMA_RX_ERR_BASE;
		अगर (err_msk & (1 << index))
			वापस dma_rx_err_code_prio[i];
	पूर्ण
	वापस -1;
पूर्ण

/* by शेष, task resp is complete */
अटल व्योम slot_err_v2_hw(काष्ठा hisi_hba *hisi_hba,
			   काष्ठा sas_task *task,
			   काष्ठा hisi_sas_slot *slot,
			   पूर्णांक err_phase)
अणु
	काष्ठा task_status_काष्ठा *ts = &task->task_status;
	काष्ठा hisi_sas_err_record_v2 *err_record =
			hisi_sas_status_buf_addr_mem(slot);
	u32 trans_tx_fail_type = le32_to_cpu(err_record->trans_tx_fail_type);
	u32 trans_rx_fail_type = le32_to_cpu(err_record->trans_rx_fail_type);
	u16 dma_tx_err_type = le16_to_cpu(err_record->dma_tx_err_type);
	u16 sipc_rx_err_type = le16_to_cpu(err_record->sipc_rx_err_type);
	u32 dma_rx_err_type = le32_to_cpu(err_record->dma_rx_err_type);
	पूर्णांक error = -1;

	अगर (err_phase == 1) अणु
		/* error in TX phase, the priority of error is: DW2 > DW0 */
		error = parse_dma_tx_err_code_v2_hw(dma_tx_err_type);
		अगर (error == -1)
			error = parse_trans_tx_err_code_v2_hw(
					trans_tx_fail_type);
	पूर्ण अन्यथा अगर (err_phase == 2) अणु
		/* error in RX phase, the priority is: DW1 > DW3 > DW2 */
		error = parse_trans_rx_err_code_v2_hw(trans_rx_fail_type);
		अगर (error == -1) अणु
			error = parse_dma_rx_err_code_v2_hw(
					dma_rx_err_type);
			अगर (error == -1)
				error = parse_sipc_rx_err_code_v2_hw(
						sipc_rx_err_type);
		पूर्ण
	पूर्ण

	चयन (task->task_proto) अणु
	हाल SAS_PROTOCOL_SSP:
	अणु
		चयन (error) अणु
		हाल TRANS_TX_OPEN_CNX_ERR_NO_DESTINATION:
		अणु
			ts->stat = SAS_OPEN_REJECT;
			ts->खोलो_rej_reason = SAS_OREJ_NO_DEST;
			अवरोध;
		पूर्ण
		हाल TRANS_TX_OPEN_CNX_ERR_PROTOCOL_NOT_SUPPORTED:
		अणु
			ts->stat = SAS_OPEN_REJECT;
			ts->खोलो_rej_reason = SAS_OREJ_EPROTO;
			अवरोध;
		पूर्ण
		हाल TRANS_TX_OPEN_CNX_ERR_CONNECTION_RATE_NOT_SUPPORTED:
		अणु
			ts->stat = SAS_OPEN_REJECT;
			ts->खोलो_rej_reason = SAS_OREJ_CONN_RATE;
			अवरोध;
		पूर्ण
		हाल TRANS_TX_OPEN_CNX_ERR_BAD_DESTINATION:
		अणु
			ts->stat = SAS_OPEN_REJECT;
			ts->खोलो_rej_reason = SAS_OREJ_BAD_DEST;
			अवरोध;
		पूर्ण
		हाल TRANS_TX_OPEN_CNX_ERR_WRONG_DESTINATION:
		अणु
			ts->stat = SAS_OPEN_REJECT;
			ts->खोलो_rej_reason = SAS_OREJ_WRONG_DEST;
			अवरोध;
		पूर्ण
		हाल DMA_RX_UNEXP_NORM_RESP_ERR:
		हाल TRANS_TX_OPEN_CNX_ERR_ZONE_VIOLATION:
		हाल DMA_RX_RESP_BUF_OVERFLOW:
		अणु
			ts->stat = SAS_OPEN_REJECT;
			ts->खोलो_rej_reason = SAS_OREJ_UNKNOWN;
			अवरोध;
		पूर्ण
		हाल TRANS_TX_OPEN_CNX_ERR_LOW_PHY_POWER:
		अणु
			/* not sure */
			ts->stat = SAS_DEV_NO_RESPONSE;
			अवरोध;
		पूर्ण
		हाल DMA_RX_DATA_LEN_OVERFLOW:
		अणु
			ts->stat = SAS_DATA_OVERRUN;
			ts->residual = 0;
			अवरोध;
		पूर्ण
		हाल DMA_RX_DATA_LEN_UNDERFLOW:
		अणु
			ts->residual = trans_tx_fail_type;
			ts->stat = SAS_DATA_UNDERRUN;
			अवरोध;
		पूर्ण
		हाल TRANS_TX_OPEN_FAIL_WITH_IT_NEXUS_LOSS:
		हाल TRANS_TX_ERR_PHY_NOT_ENABLE:
		हाल TRANS_TX_OPEN_CNX_ERR_BY_OTHER:
		हाल TRANS_TX_OPEN_CNX_ERR_AIP_TIMEOUT:
		हाल TRANS_TX_OPEN_CNX_ERR_BREAK_RCVD:
		हाल TRANS_TX_OPEN_CNX_ERR_PATHWAY_BLOCKED:
		हाल TRANS_TX_OPEN_CNX_ERR_OPEN_TIMEOUT:
		हाल TRANS_TX_OPEN_RETRY_ERR_THRESHOLD_REACHED:
		हाल TRANS_TX_ERR_WITH_BREAK_TIMEOUT:
		हाल TRANS_TX_ERR_WITH_BREAK_REQUEST:
		हाल TRANS_TX_ERR_WITH_BREAK_RECEVIED:
		हाल TRANS_TX_ERR_WITH_CLOSE_TIMEOUT:
		हाल TRANS_TX_ERR_WITH_CLOSE_NORMAL:
		हाल TRANS_TX_ERR_WITH_CLOSE_PHYDISALE:
		हाल TRANS_TX_ERR_WITH_CLOSE_DWS_TIMEOUT:
		हाल TRANS_TX_ERR_WITH_CLOSE_COMINIT:
		हाल TRANS_TX_ERR_WITH_NAK_RECEVIED:
		हाल TRANS_TX_ERR_WITH_ACK_NAK_TIMEOUT:
		हाल TRANS_TX_ERR_WITH_CREDIT_TIMEOUT:
		हाल TRANS_TX_ERR_WITH_IPTT_CONFLICT:
		हाल TRANS_RX_ERR_WITH_RXFRAME_CRC_ERR:
		हाल TRANS_RX_ERR_WITH_RXFIS_8B10B_DISP_ERR:
		हाल TRANS_RX_ERR_WITH_RXFRAME_HAVE_ERRPRM:
		हाल TRANS_RX_ERR_WITH_LINK_BUF_OVERRUN:
		हाल TRANS_RX_ERR_WITH_BREAK_TIMEOUT:
		हाल TRANS_RX_ERR_WITH_BREAK_REQUEST:
		हाल TRANS_RX_ERR_WITH_BREAK_RECEVIED:
		हाल TRANS_RX_ERR_WITH_CLOSE_NORMAL:
		हाल TRANS_RX_ERR_WITH_CLOSE_DWS_TIMEOUT:
		हाल TRANS_RX_ERR_WITH_CLOSE_COMINIT:
		हाल TRANS_TX_ERR_FRAME_TXED:
		हाल TRANS_RX_ERR_WITH_CLOSE_PHY_DISABLE:
		हाल TRANS_RX_ERR_WITH_DATA_LEN0:
		हाल TRANS_RX_ERR_WITH_BAD_HASH:
		हाल TRANS_RX_XRDY_WLEN_ZERO_ERR:
		हाल TRANS_RX_SSP_FRM_LEN_ERR:
		हाल TRANS_RX_ERR_WITH_BAD_FRM_TYPE:
		हाल DMA_TX_DATA_SGL_OVERFLOW:
		हाल DMA_TX_UNEXP_XFER_ERR:
		हाल DMA_TX_UNEXP_RETRANS_ERR:
		हाल DMA_TX_XFER_LEN_OVERFLOW:
		हाल DMA_TX_XFER_OFFSET_ERR:
		हाल SIPC_RX_DATA_UNDERFLOW_ERR:
		हाल DMA_RX_DATA_SGL_OVERFLOW:
		हाल DMA_RX_DATA_OFFSET_ERR:
		हाल DMA_RX_RDSETUP_LEN_ODD_ERR:
		हाल DMA_RX_RDSETUP_LEN_ZERO_ERR:
		हाल DMA_RX_RDSETUP_LEN_OVER_ERR:
		हाल DMA_RX_SATA_FRAME_TYPE_ERR:
		हाल DMA_RX_UNKNOWN_FRM_ERR:
		अणु
			/* This will request a retry */
			ts->stat = SAS_QUEUE_FULL;
			slot->पात = 1;
			अवरोध;
		पूर्ण
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
		अवरोध;
	हाल SAS_PROTOCOL_SMP:
		ts->stat = SAM_STAT_CHECK_CONDITION;
		अवरोध;

	हाल SAS_PROTOCOL_SATA:
	हाल SAS_PROTOCOL_STP:
	हाल SAS_PROTOCOL_SATA | SAS_PROTOCOL_STP:
	अणु
		चयन (error) अणु
		हाल TRANS_TX_OPEN_CNX_ERR_NO_DESTINATION:
		अणु
			ts->stat = SAS_OPEN_REJECT;
			ts->खोलो_rej_reason = SAS_OREJ_NO_DEST;
			अवरोध;
		पूर्ण
		हाल TRANS_TX_OPEN_CNX_ERR_LOW_PHY_POWER:
		अणु
			ts->resp = SAS_TASK_UNDELIVERED;
			ts->stat = SAS_DEV_NO_RESPONSE;
			अवरोध;
		पूर्ण
		हाल TRANS_TX_OPEN_CNX_ERR_PROTOCOL_NOT_SUPPORTED:
		अणु
			ts->stat = SAS_OPEN_REJECT;
			ts->खोलो_rej_reason = SAS_OREJ_EPROTO;
			अवरोध;
		पूर्ण
		हाल TRANS_TX_OPEN_CNX_ERR_CONNECTION_RATE_NOT_SUPPORTED:
		अणु
			ts->stat = SAS_OPEN_REJECT;
			ts->खोलो_rej_reason = SAS_OREJ_CONN_RATE;
			अवरोध;
		पूर्ण
		हाल TRANS_TX_OPEN_CNX_ERR_BAD_DESTINATION:
		अणु
			ts->stat = SAS_OPEN_REJECT;
			ts->खोलो_rej_reason = SAS_OREJ_CONN_RATE;
			अवरोध;
		पूर्ण
		हाल TRANS_TX_OPEN_CNX_ERR_WRONG_DESTINATION:
		अणु
			ts->stat = SAS_OPEN_REJECT;
			ts->खोलो_rej_reason = SAS_OREJ_WRONG_DEST;
			अवरोध;
		पूर्ण
		हाल DMA_RX_RESP_BUF_OVERFLOW:
		हाल DMA_RX_UNEXP_NORM_RESP_ERR:
		हाल TRANS_TX_OPEN_CNX_ERR_ZONE_VIOLATION:
		अणु
			ts->stat = SAS_OPEN_REJECT;
			ts->खोलो_rej_reason = SAS_OREJ_UNKNOWN;
			अवरोध;
		पूर्ण
		हाल DMA_RX_DATA_LEN_OVERFLOW:
		अणु
			ts->stat = SAS_DATA_OVERRUN;
			ts->residual = 0;
			अवरोध;
		पूर्ण
		हाल DMA_RX_DATA_LEN_UNDERFLOW:
		अणु
			ts->residual = trans_tx_fail_type;
			ts->stat = SAS_DATA_UNDERRUN;
			अवरोध;
		पूर्ण
		हाल TRANS_TX_OPEN_FAIL_WITH_IT_NEXUS_LOSS:
		हाल TRANS_TX_ERR_PHY_NOT_ENABLE:
		हाल TRANS_TX_OPEN_CNX_ERR_BY_OTHER:
		हाल TRANS_TX_OPEN_CNX_ERR_AIP_TIMEOUT:
		हाल TRANS_TX_OPEN_CNX_ERR_BREAK_RCVD:
		हाल TRANS_TX_OPEN_CNX_ERR_PATHWAY_BLOCKED:
		हाल TRANS_TX_OPEN_CNX_ERR_OPEN_TIMEOUT:
		हाल TRANS_TX_OPEN_RETRY_ERR_THRESHOLD_REACHED:
		हाल TRANS_TX_ERR_WITH_BREAK_TIMEOUT:
		हाल TRANS_TX_ERR_WITH_BREAK_REQUEST:
		हाल TRANS_TX_ERR_WITH_BREAK_RECEVIED:
		हाल TRANS_TX_ERR_WITH_CLOSE_TIMEOUT:
		हाल TRANS_TX_ERR_WITH_CLOSE_NORMAL:
		हाल TRANS_TX_ERR_WITH_CLOSE_PHYDISALE:
		हाल TRANS_TX_ERR_WITH_CLOSE_DWS_TIMEOUT:
		हाल TRANS_TX_ERR_WITH_CLOSE_COMINIT:
		हाल TRANS_TX_ERR_WITH_ACK_NAK_TIMEOUT:
		हाल TRANS_TX_ERR_WITH_CREDIT_TIMEOUT:
		हाल TRANS_TX_ERR_WITH_OPEN_BY_DES_OR_OTHERS:
		हाल TRANS_TX_ERR_WITH_WAIT_RECV_TIMEOUT:
		हाल TRANS_RX_ERR_WITH_RXFRAME_HAVE_ERRPRM:
		हाल TRANS_RX_ERR_WITH_RXFIS_8B10B_DISP_ERR:
		हाल TRANS_RX_ERR_WITH_RXFIS_DECODE_ERROR:
		हाल TRANS_RX_ERR_WITH_RXFIS_CRC_ERR:
		हाल TRANS_RX_ERR_WITH_RXFRAME_LENGTH_OVERRUN:
		हाल TRANS_RX_ERR_WITH_RXFIS_RX_SYNCP:
		हाल TRANS_RX_ERR_WITH_LINK_BUF_OVERRUN:
		हाल TRANS_RX_ERR_WITH_BREAK_TIMEOUT:
		हाल TRANS_RX_ERR_WITH_BREAK_REQUEST:
		हाल TRANS_RX_ERR_WITH_BREAK_RECEVIED:
		हाल TRANS_RX_ERR_WITH_CLOSE_NORMAL:
		हाल TRANS_RX_ERR_WITH_CLOSE_PHY_DISABLE:
		हाल TRANS_RX_ERR_WITH_CLOSE_DWS_TIMEOUT:
		हाल TRANS_RX_ERR_WITH_CLOSE_COMINIT:
		हाल TRANS_RX_ERR_WITH_DATA_LEN0:
		हाल TRANS_RX_ERR_WITH_BAD_HASH:
		हाल TRANS_RX_XRDY_WLEN_ZERO_ERR:
		हाल TRANS_RX_ERR_WITH_BAD_FRM_TYPE:
		हाल DMA_TX_DATA_SGL_OVERFLOW:
		हाल DMA_TX_UNEXP_XFER_ERR:
		हाल DMA_TX_UNEXP_RETRANS_ERR:
		हाल DMA_TX_XFER_LEN_OVERFLOW:
		हाल DMA_TX_XFER_OFFSET_ERR:
		हाल SIPC_RX_FIS_STATUS_ERR_BIT_VLD:
		हाल SIPC_RX_PIO_WRSETUP_STATUS_DRQ_ERR:
		हाल SIPC_RX_FIS_STATUS_BSY_BIT_ERR:
		हाल SIPC_RX_WRSETUP_LEN_ODD_ERR:
		हाल SIPC_RX_WRSETUP_LEN_ZERO_ERR:
		हाल SIPC_RX_WRDATA_LEN_NOT_MATCH_ERR:
		हाल SIPC_RX_SATA_UNEXP_FIS_ERR:
		हाल DMA_RX_DATA_SGL_OVERFLOW:
		हाल DMA_RX_DATA_OFFSET_ERR:
		हाल DMA_RX_SATA_FRAME_TYPE_ERR:
		हाल DMA_RX_UNEXP_RDFRAME_ERR:
		हाल DMA_RX_PIO_DATA_LEN_ERR:
		हाल DMA_RX_RDSETUP_STATUS_ERR:
		हाल DMA_RX_RDSETUP_STATUS_DRQ_ERR:
		हाल DMA_RX_RDSETUP_STATUS_BSY_ERR:
		हाल DMA_RX_RDSETUP_LEN_ODD_ERR:
		हाल DMA_RX_RDSETUP_LEN_ZERO_ERR:
		हाल DMA_RX_RDSETUP_LEN_OVER_ERR:
		हाल DMA_RX_RDSETUP_OFFSET_ERR:
		हाल DMA_RX_RDSETUP_ACTIVE_ERR:
		हाल DMA_RX_RDSETUP_ESTATUS_ERR:
		हाल DMA_RX_UNKNOWN_FRM_ERR:
		हाल TRANS_RX_SSP_FRM_LEN_ERR:
		हाल TRANS_TX_OPEN_CNX_ERR_STP_RESOURCES_BUSY:
		अणु
			slot->पात = 1;
			ts->stat = SAS_PHY_DOWN;
			अवरोध;
		पूर्ण
		शेष:
		अणु
			ts->stat = SAS_PROTO_RESPONSE;
			अवरोध;
		पूर्ण
		पूर्ण
		hisi_sas_sata_करोne(task, slot);
	पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम slot_complete_v2_hw(काष्ठा hisi_hba *hisi_hba,
				काष्ठा hisi_sas_slot *slot)
अणु
	काष्ठा sas_task *task = slot->task;
	काष्ठा hisi_sas_device *sas_dev;
	काष्ठा device *dev = hisi_hba->dev;
	काष्ठा task_status_काष्ठा *ts;
	काष्ठा करोमुख्य_device *device;
	काष्ठा sas_ha_काष्ठा *ha;
	काष्ठा hisi_sas_complete_v2_hdr *complete_queue =
			hisi_hba->complete_hdr[slot->cmplt_queue];
	काष्ठा hisi_sas_complete_v2_hdr *complete_hdr =
			&complete_queue[slot->cmplt_queue_slot];
	अचिन्हित दीर्घ flags;
	bool is_पूर्णांकernal = slot->is_पूर्णांकernal;
	u32 dw0;

	अगर (unlikely(!task || !task->lldd_task || !task->dev))
		वापस;

	ts = &task->task_status;
	device = task->dev;
	ha = device->port->ha;
	sas_dev = device->lldd_dev;

	spin_lock_irqsave(&task->task_state_lock, flags);
	task->task_state_flags &=
		~(SAS_TASK_STATE_PENDING | SAS_TASK_AT_INITIATOR);
	spin_unlock_irqrestore(&task->task_state_lock, flags);

	स_रखो(ts, 0, माप(*ts));
	ts->resp = SAS_TASK_COMPLETE;

	अगर (unlikely(!sas_dev)) अणु
		dev_dbg(dev, "slot complete: port has no device\n");
		ts->stat = SAS_PHY_DOWN;
		जाओ out;
	पूर्ण

	/* Use SAS+TMF status codes */
	dw0 = le32_to_cpu(complete_hdr->dw0);
	चयन ((dw0 & CMPLT_HDR_ABORT_STAT_MSK) >>
		CMPLT_HDR_ABORT_STAT_OFF) अणु
	हाल STAT_IO_ABORTED:
		/* this io has been पातed by पात command */
		ts->stat = SAS_ABORTED_TASK;
		जाओ out;
	हाल STAT_IO_COMPLETE:
		/* पूर्णांकernal पात command complete */
		ts->stat = TMF_RESP_FUNC_SUCC;
		del_समयr(&slot->पूर्णांकernal_पात_समयr);
		जाओ out;
	हाल STAT_IO_NO_DEVICE:
		ts->stat = TMF_RESP_FUNC_COMPLETE;
		del_समयr(&slot->पूर्णांकernal_पात_समयr);
		जाओ out;
	हाल STAT_IO_NOT_VALID:
		/* पात single io, controller करोn't find
		 * the io need to पात
		 */
		ts->stat = TMF_RESP_FUNC_FAILED;
		del_समयr(&slot->पूर्णांकernal_पात_समयr);
		जाओ out;
	शेष:
		अवरोध;
	पूर्ण

	अगर ((dw0 & CMPLT_HDR_ERX_MSK) && (!(dw0 & CMPLT_HDR_RSPNS_XFRD_MSK))) अणु
		u32 err_phase = (dw0 & CMPLT_HDR_ERR_PHASE_MSK)
				>> CMPLT_HDR_ERR_PHASE_OFF;
		u32 *error_info = hisi_sas_status_buf_addr_mem(slot);

		/* Analyse error happens on which phase TX or RX */
		अगर (ERR_ON_TX_PHASE(err_phase))
			slot_err_v2_hw(hisi_hba, task, slot, 1);
		अन्यथा अगर (ERR_ON_RX_PHASE(err_phase))
			slot_err_v2_hw(hisi_hba, task, slot, 2);

		अगर (ts->stat != SAS_DATA_UNDERRUN)
			dev_info(dev, "erroneous completion iptt=%d task=%pK dev id=%d CQ hdr: 0x%x 0x%x 0x%x 0x%x Error info: 0x%x 0x%x 0x%x 0x%x\n",
				 slot->idx, task, sas_dev->device_id,
				 complete_hdr->dw0, complete_hdr->dw1,
				 complete_hdr->act, complete_hdr->dw3,
				 error_info[0], error_info[1],
				 error_info[2], error_info[3]);

		अगर (unlikely(slot->पात)) अणु
			sas_task_पात(task);
			वापस;
		पूर्ण
		जाओ out;
	पूर्ण

	चयन (task->task_proto) अणु
	हाल SAS_PROTOCOL_SSP:
	अणु
		काष्ठा hisi_sas_status_buffer *status_buffer =
				hisi_sas_status_buf_addr_mem(slot);
		काष्ठा ssp_response_iu *iu = (काष्ठा ssp_response_iu *)
				&status_buffer->iu[0];

		sas_ssp_task_response(dev, task, iu);
		अवरोध;
	पूर्ण
	हाल SAS_PROTOCOL_SMP:
	अणु
		काष्ठा scatterlist *sg_resp = &task->smp_task.smp_resp;
		व्योम *to = page_address(sg_page(sg_resp));

		ts->stat = SAM_STAT_GOOD;

		dma_unmap_sg(dev, &task->smp_task.smp_req, 1,
			     DMA_TO_DEVICE);
		स_नकल(to + sg_resp->offset,
		       hisi_sas_status_buf_addr_mem(slot) +
		       माप(काष्ठा hisi_sas_err_record),
		       sg_resp->length);
		अवरोध;
	पूर्ण
	हाल SAS_PROTOCOL_SATA:
	हाल SAS_PROTOCOL_STP:
	हाल SAS_PROTOCOL_SATA | SAS_PROTOCOL_STP:
	अणु
		ts->stat = SAM_STAT_GOOD;
		hisi_sas_sata_करोne(task, slot);
		अवरोध;
	पूर्ण
	शेष:
		ts->stat = SAM_STAT_CHECK_CONDITION;
		अवरोध;
	पूर्ण

	अगर (!slot->port->port_attached) अणु
		dev_warn(dev, "slot complete: port %d has removed\n",
			slot->port->sas_port.id);
		ts->stat = SAS_PHY_DOWN;
	पूर्ण

out:
	spin_lock_irqsave(&task->task_state_lock, flags);
	अगर (task->task_state_flags & SAS_TASK_STATE_ABORTED) अणु
		spin_unlock_irqrestore(&task->task_state_lock, flags);
		dev_info(dev, "slot complete: task(%pK) aborted\n", task);
		वापस;
	पूर्ण
	task->task_state_flags |= SAS_TASK_STATE_DONE;
	spin_unlock_irqrestore(&task->task_state_lock, flags);
	hisi_sas_slot_task_मुक्त(hisi_hba, task, slot);

	अगर (!is_पूर्णांकernal && (task->task_proto != SAS_PROTOCOL_SMP)) अणु
		spin_lock_irqsave(&device->करोne_lock, flags);
		अगर (test_bit(SAS_HA_FROZEN, &ha->state)) अणु
			spin_unlock_irqrestore(&device->करोne_lock, flags);
			dev_info(dev, "slot complete: task(%pK) ignored\n",
				 task);
			वापस;
		पूर्ण
		spin_unlock_irqrestore(&device->करोne_lock, flags);
	पूर्ण

	अगर (task->task_करोne)
		task->task_करोne(task);
पूर्ण

अटल व्योम prep_ata_v2_hw(काष्ठा hisi_hba *hisi_hba,
			  काष्ठा hisi_sas_slot *slot)
अणु
	काष्ठा sas_task *task = slot->task;
	काष्ठा करोमुख्य_device *device = task->dev;
	काष्ठा करोमुख्य_device *parent_dev = device->parent;
	काष्ठा hisi_sas_device *sas_dev = device->lldd_dev;
	काष्ठा hisi_sas_cmd_hdr *hdr = slot->cmd_hdr;
	काष्ठा asd_sas_port *sas_port = device->port;
	काष्ठा hisi_sas_port *port = to_hisi_sas_port(sas_port);
	काष्ठा hisi_sas_पंचांगf_task *पंचांगf = slot->पंचांगf;
	u8 *buf_cmd;
	पूर्णांक has_data = 0, hdr_tag = 0;
	u32 dw0, dw1 = 0, dw2 = 0;

	/* create header */
	/* dw0 */
	dw0 = port->id << CMD_HDR_PORT_OFF;
	अगर (parent_dev && dev_is_expander(parent_dev->dev_type))
		dw0 |= 3 << CMD_HDR_CMD_OFF;
	अन्यथा
		dw0 |= 4 << CMD_HDR_CMD_OFF;

	अगर (पंचांगf && पंचांगf->क्रमce_phy) अणु
		dw0 |= CMD_HDR_FORCE_PHY_MSK;
		dw0 |= (1 << पंचांगf->phy_id) << CMD_HDR_PHY_ID_OFF;
	पूर्ण

	hdr->dw0 = cpu_to_le32(dw0);

	/* dw1 */
	चयन (task->data_dir) अणु
	हाल DMA_TO_DEVICE:
		has_data = 1;
		dw1 |= सूची_TO_DEVICE << CMD_HDR_सूची_OFF;
		अवरोध;
	हाल DMA_FROM_DEVICE:
		has_data = 1;
		dw1 |= सूची_TO_INI << CMD_HDR_सूची_OFF;
		अवरोध;
	शेष:
		dw1 &= ~CMD_HDR_सूची_MSK;
	पूर्ण

	अगर ((task->ata_task.fis.command == ATA_CMD_DEV_RESET) &&
			(task->ata_task.fis.control & ATA_SRST))
		dw1 |= 1 << CMD_HDR_RESET_OFF;

	dw1 |= (hisi_sas_get_ata_protocol(
		&task->ata_task.fis, task->data_dir))
		<< CMD_HDR_FRAME_TYPE_OFF;
	dw1 |= sas_dev->device_id << CMD_HDR_DEV_ID_OFF;
	hdr->dw1 = cpu_to_le32(dw1);

	/* dw2 */
	अगर (task->ata_task.use_ncq) अणु
		काष्ठा ata_queued_cmd *qc = task->uldd_task;

		hdr_tag = qc->tag;
		task->ata_task.fis.sector_count |= (u8) (hdr_tag << 3);
		dw2 |= hdr_tag << CMD_HDR_NCQ_TAG_OFF;
	पूर्ण

	dw2 |= (HISI_SAS_MAX_STP_RESP_SZ / 4) << CMD_HDR_CFL_OFF |
			2 << CMD_HDR_SG_MOD_OFF;
	hdr->dw2 = cpu_to_le32(dw2);

	/* dw3 */
	hdr->transfer_tags = cpu_to_le32(slot->idx);

	अगर (has_data)
		prep_prd_sge_v2_hw(hisi_hba, slot, hdr, task->scatter,
					slot->n_elem);

	hdr->data_transfer_len = cpu_to_le32(task->total_xfer_len);
	hdr->cmd_table_addr = cpu_to_le64(hisi_sas_cmd_hdr_addr_dma(slot));
	hdr->sts_buffer_addr = cpu_to_le64(hisi_sas_status_buf_addr_dma(slot));

	buf_cmd = hisi_sas_cmd_hdr_addr_mem(slot);

	अगर (likely(!task->ata_task.device_control_reg_update))
		task->ata_task.fis.flags |= 0x80; /* C=1: update ATA cmd reg */
	/* fill in command FIS */
	स_नकल(buf_cmd, &task->ata_task.fis, माप(काष्ठा host_to_dev_fis));
पूर्ण

अटल व्योम hisi_sas_पूर्णांकernal_पात_quirk_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा hisi_sas_slot *slot = from_समयr(slot, t, पूर्णांकernal_पात_समयr);
	काष्ठा hisi_sas_port *port = slot->port;
	काष्ठा asd_sas_port *asd_sas_port;
	काष्ठा asd_sas_phy *sas_phy;

	अगर (!port)
		वापस;

	asd_sas_port = &port->sas_port;

	/* Kick the hardware - send अवरोध command */
	list_क्रम_each_entry(sas_phy, &asd_sas_port->phy_list, port_phy_el) अणु
		काष्ठा hisi_sas_phy *phy = sas_phy->lldd_phy;
		काष्ठा hisi_hba *hisi_hba = phy->hisi_hba;
		पूर्णांक phy_no = sas_phy->id;
		u32 link_dfx2;

		link_dfx2 = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no, LINK_DFX2);
		अगर ((link_dfx2 == LINK_DFX2_RCVR_HOLD_STS_MSK) ||
		    (link_dfx2 & LINK_DFX2_SEND_HOLD_STS_MSK)) अणु
			u32 txid_स्वतः;

			txid_स्वतः = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no,
							TXID_AUTO);
			txid_स्वतः |= TXID_AUTO_CTB_MSK;
			hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, TXID_AUTO,
					     txid_स्वतः);
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम prep_पात_v2_hw(काष्ठा hisi_hba *hisi_hba,
		काष्ठा hisi_sas_slot *slot,
		पूर्णांक device_id, पूर्णांक पात_flag, पूर्णांक tag_to_पात)
अणु
	काष्ठा sas_task *task = slot->task;
	काष्ठा करोमुख्य_device *dev = task->dev;
	काष्ठा hisi_sas_cmd_hdr *hdr = slot->cmd_hdr;
	काष्ठा hisi_sas_port *port = slot->port;
	काष्ठा समयr_list *समयr = &slot->पूर्णांकernal_पात_समयr;

	/* setup the quirk समयr */
	समयr_setup(समयr, hisi_sas_पूर्णांकernal_पात_quirk_समयout, 0);
	/* Set the समयout to 10ms less than पूर्णांकernal पात समयout */
	mod_समयr(समयr, jअगरfies + msecs_to_jअगरfies(100));

	/* dw0 */
	hdr->dw0 = cpu_to_le32((5 << CMD_HDR_CMD_OFF) | /*पात*/
			       (port->id << CMD_HDR_PORT_OFF) |
			       (dev_is_sata(dev) <<
				CMD_HDR_ABORT_DEVICE_TYPE_OFF) |
			       (पात_flag << CMD_HDR_ABORT_FLAG_OFF));

	/* dw1 */
	hdr->dw1 = cpu_to_le32(device_id << CMD_HDR_DEV_ID_OFF);

	/* dw7 */
	hdr->dw7 = cpu_to_le32(tag_to_पात << CMD_HDR_ABORT_IPTT_OFF);
	hdr->transfer_tags = cpu_to_le32(slot->idx);
पूर्ण

अटल पूर्णांक phy_up_v2_hw(पूर्णांक phy_no, काष्ठा hisi_hba *hisi_hba)
अणु
	पूर्णांक i, res = IRQ_HANDLED;
	u32 port_id, link_rate;
	काष्ठा hisi_sas_phy *phy = &hisi_hba->phy[phy_no];
	काष्ठा asd_sas_phy *sas_phy = &phy->sas_phy;
	काष्ठा device *dev = hisi_hba->dev;
	u32 *frame_rcvd = (u32 *)sas_phy->frame_rcvd;
	काष्ठा sas_identअगरy_frame *id = (काष्ठा sas_identअगरy_frame *)frame_rcvd;
	अचिन्हित दीर्घ flags;

	hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, PHYCTRL_PHY_ENA_MSK, 1);

	अगर (is_sata_phy_v2_hw(hisi_hba, phy_no))
		जाओ end;

	del_समयr(&phy->समयr);

	अगर (phy_no == 8) अणु
		u32 port_state = hisi_sas_पढ़ो32(hisi_hba, PORT_STATE);

		port_id = (port_state & PORT_STATE_PHY8_PORT_NUM_MSK) >>
			  PORT_STATE_PHY8_PORT_NUM_OFF;
		link_rate = (port_state & PORT_STATE_PHY8_CONN_RATE_MSK) >>
			    PORT_STATE_PHY8_CONN_RATE_OFF;
	पूर्ण अन्यथा अणु
		port_id = hisi_sas_पढ़ो32(hisi_hba, PHY_PORT_NUM_MA);
		port_id = (port_id >> (4 * phy_no)) & 0xf;
		link_rate = hisi_sas_पढ़ो32(hisi_hba, PHY_CONN_RATE);
		link_rate = (link_rate >> (phy_no * 4)) & 0xf;
	पूर्ण

	अगर (port_id == 0xf) अणु
		dev_err(dev, "phyup: phy%d invalid portid\n", phy_no);
		res = IRQ_NONE;
		जाओ end;
	पूर्ण

	क्रम (i = 0; i < 6; i++) अणु
		u32 idaf = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no,
					       RX_IDAF_DWORD0 + (i * 4));
		frame_rcvd[i] = __swab32(idaf);
	पूर्ण

	sas_phy->linkrate = link_rate;
	sas_phy->oob_mode = SAS_OOB_MODE;
	स_नकल(sas_phy->attached_sas_addr, &id->sas_addr, SAS_ADDR_SIZE);
	dev_info(dev, "phyup: phy%d link_rate=%d\n", phy_no, link_rate);
	phy->port_id = port_id;
	phy->phy_type &= ~(PORT_TYPE_SAS | PORT_TYPE_SATA);
	phy->phy_type |= PORT_TYPE_SAS;
	phy->phy_attached = 1;
	phy->identअगरy.device_type = id->dev_type;
	phy->frame_rcvd_size =	माप(काष्ठा sas_identअगरy_frame);
	अगर (phy->identअगरy.device_type == SAS_END_DEVICE)
		phy->identअगरy.target_port_protocols =
			SAS_PROTOCOL_SSP;
	अन्यथा अगर (phy->identअगरy.device_type != SAS_PHY_UNUSED) अणु
		phy->identअगरy.target_port_protocols =
			SAS_PROTOCOL_SMP;
		अगर (!समयr_pending(&hisi_hba->समयr))
			set_link_समयr_quirk(hisi_hba);
	पूर्ण
	hisi_sas_notअगरy_phy_event(phy, HISI_PHYE_PHY_UP);
	spin_lock_irqsave(&phy->lock, flags);
	अगर (phy->reset_completion) अणु
		phy->in_reset = 0;
		complete(phy->reset_completion);
	पूर्ण
	spin_unlock_irqrestore(&phy->lock, flags);

end:
	hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, CHL_INT0,
			     CHL_INT0_SL_PHY_ENABLE_MSK);
	hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, PHYCTRL_PHY_ENA_MSK, 0);

	वापस res;
पूर्ण

अटल bool check_any_wideports_v2_hw(काष्ठा hisi_hba *hisi_hba)
अणु
	u32 port_state;

	port_state = hisi_sas_पढ़ो32(hisi_hba, PORT_STATE);
	अगर (port_state & 0x1ff)
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक phy_करोwn_v2_hw(पूर्णांक phy_no, काष्ठा hisi_hba *hisi_hba)
अणु
	u32 phy_state, sl_ctrl, txid_स्वतः;
	काष्ठा hisi_sas_phy *phy = &hisi_hba->phy[phy_no];
	काष्ठा hisi_sas_port *port = phy->port;
	काष्ठा device *dev = hisi_hba->dev;

	del_समयr(&phy->समयr);
	hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, PHYCTRL_NOT_RDY_MSK, 1);

	phy_state = hisi_sas_पढ़ो32(hisi_hba, PHY_STATE);
	dev_info(dev, "phydown: phy%d phy_state=0x%x\n", phy_no, phy_state);
	hisi_sas_phy_करोwn(hisi_hba, phy_no, (phy_state & 1 << phy_no) ? 1 : 0,
			  GFP_ATOMIC);

	sl_ctrl = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no, SL_CONTROL);
	hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, SL_CONTROL,
			     sl_ctrl & ~SL_CONTROL_CTA_MSK);
	अगर (port && !get_wideport_biपंचांगap_v2_hw(hisi_hba, port->id))
		अगर (!check_any_wideports_v2_hw(hisi_hba) &&
				समयr_pending(&hisi_hba->समयr))
			del_समयr(&hisi_hba->समयr);

	txid_स्वतः = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no, TXID_AUTO);
	hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, TXID_AUTO,
			     txid_स्वतः | TXID_AUTO_CT3_MSK);

	hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, CHL_INT0, CHL_INT0_NOT_RDY_MSK);
	hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, PHYCTRL_NOT_RDY_MSK, 0);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t पूर्णांक_phy_upकरोwn_v2_hw(पूर्णांक irq_no, व्योम *p)
अणु
	काष्ठा hisi_hba *hisi_hba = p;
	u32 irq_msk;
	पूर्णांक phy_no = 0;
	irqवापस_t res = IRQ_NONE;

	irq_msk = (hisi_sas_पढ़ो32(hisi_hba, HGC_INVLD_DQE_INFO)
		   >> HGC_INVLD_DQE_INFO_FB_CH0_OFF) & 0x1ff;
	जबतक (irq_msk) अणु
		अगर (irq_msk  & 1) अणु
			u32 reg_value = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no,
					    CHL_INT0);

			चयन (reg_value & (CHL_INT0_NOT_RDY_MSK |
					CHL_INT0_SL_PHY_ENABLE_MSK)) अणु

			हाल CHL_INT0_SL_PHY_ENABLE_MSK:
				/* phy up */
				अगर (phy_up_v2_hw(phy_no, hisi_hba) ==
				    IRQ_HANDLED)
					res = IRQ_HANDLED;
				अवरोध;

			हाल CHL_INT0_NOT_RDY_MSK:
				/* phy करोwn */
				अगर (phy_करोwn_v2_hw(phy_no, hisi_hba) ==
				    IRQ_HANDLED)
					res = IRQ_HANDLED;
				अवरोध;

			हाल (CHL_INT0_NOT_RDY_MSK |
					CHL_INT0_SL_PHY_ENABLE_MSK):
				reg_value = hisi_sas_पढ़ो32(hisi_hba,
						PHY_STATE);
				अगर (reg_value & BIT(phy_no)) अणु
					/* phy up */
					अगर (phy_up_v2_hw(phy_no, hisi_hba) ==
					    IRQ_HANDLED)
						res = IRQ_HANDLED;
				पूर्ण अन्यथा अणु
					/* phy करोwn */
					अगर (phy_करोwn_v2_hw(phy_no, hisi_hba) ==
					    IRQ_HANDLED)
						res = IRQ_HANDLED;
				पूर्ण
				अवरोध;

			शेष:
				अवरोध;
			पूर्ण

		पूर्ण
		irq_msk >>= 1;
		phy_no++;
	पूर्ण

	वापस res;
पूर्ण

अटल व्योम phy_bcast_v2_hw(पूर्णांक phy_no, काष्ठा hisi_hba *hisi_hba)
अणु
	काष्ठा hisi_sas_phy *phy = &hisi_hba->phy[phy_no];
	काष्ठा asd_sas_phy *sas_phy = &phy->sas_phy;
	u32 bcast_status;

	hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, SL_RX_BCAST_CHK_MSK, 1);
	bcast_status = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no, RX_PRIMS_STATUS);
	अगर ((bcast_status & RX_BCAST_CHG_MSK) &&
	    !test_bit(HISI_SAS_RESET_BIT, &hisi_hba->flags))
		sas_notअगरy_port_event(sas_phy, PORTE_BROADCAST_RCVD,
				      GFP_ATOMIC);
	hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, CHL_INT0,
			     CHL_INT0_SL_RX_BCST_ACK_MSK);
	hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, SL_RX_BCAST_CHK_MSK, 0);
पूर्ण

अटल स्थिर काष्ठा hisi_sas_hw_error port_ecc_axi_error[] = अणु
	अणु
		.irq_msk = BIT(CHL_INT1_DMAC_TX_ECC_ERR_OFF),
		.msg = "dmac_tx_ecc_bad_err",
	पूर्ण,
	अणु
		.irq_msk = BIT(CHL_INT1_DMAC_RX_ECC_ERR_OFF),
		.msg = "dmac_rx_ecc_bad_err",
	पूर्ण,
	अणु
		.irq_msk = BIT(CHL_INT1_DMAC_TX_AXI_WR_ERR_OFF),
		.msg = "dma_tx_axi_wr_err",
	पूर्ण,
	अणु
		.irq_msk = BIT(CHL_INT1_DMAC_TX_AXI_RD_ERR_OFF),
		.msg = "dma_tx_axi_rd_err",
	पूर्ण,
	अणु
		.irq_msk = BIT(CHL_INT1_DMAC_RX_AXI_WR_ERR_OFF),
		.msg = "dma_rx_axi_wr_err",
	पूर्ण,
	अणु
		.irq_msk = BIT(CHL_INT1_DMAC_RX_AXI_RD_ERR_OFF),
		.msg = "dma_rx_axi_rd_err",
	पूर्ण,
पूर्ण;

अटल irqवापस_t पूर्णांक_chnl_पूर्णांक_v2_hw(पूर्णांक irq_no, व्योम *p)
अणु
	काष्ठा hisi_hba *hisi_hba = p;
	काष्ठा device *dev = hisi_hba->dev;
	u32 ent_msk, ent_पंचांगp, irq_msk;
	पूर्णांक phy_no = 0;

	ent_msk = hisi_sas_पढ़ो32(hisi_hba, ENT_INT_SRC_MSK3);
	ent_पंचांगp = ent_msk;
	ent_msk |= ENT_INT_SRC_MSK3_ENT95_MSK_MSK;
	hisi_sas_ग_लिखो32(hisi_hba, ENT_INT_SRC_MSK3, ent_msk);

	irq_msk = (hisi_sas_पढ़ो32(hisi_hba, HGC_INVLD_DQE_INFO) >>
			HGC_INVLD_DQE_INFO_FB_CH3_OFF) & 0x1ff;

	जबतक (irq_msk) अणु
		u32 irq_value0 = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no,
						     CHL_INT0);
		u32 irq_value1 = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no,
						     CHL_INT1);
		u32 irq_value2 = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no,
						     CHL_INT2);

		अगर ((irq_msk & (1 << phy_no)) && irq_value1) अणु
			पूर्णांक i;

			क्रम (i = 0; i < ARRAY_SIZE(port_ecc_axi_error); i++) अणु
				स्थिर काष्ठा hisi_sas_hw_error *error =
						&port_ecc_axi_error[i];

				अगर (!(irq_value1 & error->irq_msk))
					जारी;

				dev_warn(dev, "%s error (phy%d 0x%x) found!\n",
					error->msg, phy_no, irq_value1);
				queue_work(hisi_hba->wq, &hisi_hba->rst_work);
			पूर्ण

			hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no,
					     CHL_INT1, irq_value1);
		पूर्ण

		अगर ((irq_msk & (1 << phy_no)) && irq_value2) अणु
			काष्ठा hisi_sas_phy *phy = &hisi_hba->phy[phy_no];

			अगर (irq_value2 & BIT(CHL_INT2_SL_IDAF_TOUT_CONF_OFF)) अणु
				dev_warn(dev, "phy%d identify timeout\n",
					 phy_no);
				hisi_sas_notअगरy_phy_event(phy,
						HISI_PHYE_LINK_RESET);
			पूर्ण

			hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no,
						 CHL_INT2, irq_value2);
		पूर्ण

		अगर ((irq_msk & (1 << phy_no)) && irq_value0) अणु
			अगर (irq_value0 & CHL_INT0_SL_RX_BCST_ACK_MSK)
				phy_bcast_v2_hw(phy_no, hisi_hba);

			अगर (irq_value0 & CHL_INT0_PHY_RDY_MSK)
				hisi_sas_phy_oob_पढ़ोy(hisi_hba, phy_no);

			hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no,
					CHL_INT0, irq_value0
					& (~CHL_INT0_HOTPLUG_TOUT_MSK)
					& (~CHL_INT0_SL_PHY_ENABLE_MSK)
					& (~CHL_INT0_NOT_RDY_MSK));
		पूर्ण
		irq_msk &= ~(1 << phy_no);
		phy_no++;
	पूर्ण

	hisi_sas_ग_लिखो32(hisi_hba, ENT_INT_SRC_MSK3, ent_पंचांगp);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम
one_bit_ecc_error_process_v2_hw(काष्ठा hisi_hba *hisi_hba, u32 irq_value)
अणु
	काष्ठा device *dev = hisi_hba->dev;
	स्थिर काष्ठा hisi_sas_hw_error *ecc_error;
	u32 val;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(one_bit_ecc_errors); i++) अणु
		ecc_error = &one_bit_ecc_errors[i];
		अगर (irq_value & ecc_error->irq_msk) अणु
			val = hisi_sas_पढ़ो32(hisi_hba, ecc_error->reg);
			val &= ecc_error->msk;
			val >>= ecc_error->shअगरt;
			dev_warn(dev, "%s found: mem addr is 0x%08X\n",
				 ecc_error->msg, val);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम multi_bit_ecc_error_process_v2_hw(काष्ठा hisi_hba *hisi_hba,
		u32 irq_value)
अणु
	काष्ठा device *dev = hisi_hba->dev;
	स्थिर काष्ठा hisi_sas_hw_error *ecc_error;
	u32 val;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(multi_bit_ecc_errors); i++) अणु
		ecc_error = &multi_bit_ecc_errors[i];
		अगर (irq_value & ecc_error->irq_msk) अणु
			val = hisi_sas_पढ़ो32(hisi_hba, ecc_error->reg);
			val &= ecc_error->msk;
			val >>= ecc_error->shअगरt;
			dev_err(dev, "%s (0x%x) found: mem addr is 0x%08X\n",
				ecc_error->msg, irq_value, val);
			queue_work(hisi_hba->wq, &hisi_hba->rst_work);
		पूर्ण
	पूर्ण

	वापस;
पूर्ण

अटल irqवापस_t fatal_ecc_पूर्णांक_v2_hw(पूर्णांक irq_no, व्योम *p)
अणु
	काष्ठा hisi_hba *hisi_hba = p;
	u32 irq_value, irq_msk;

	irq_msk = hisi_sas_पढ़ो32(hisi_hba, SAS_ECC_INTR_MSK);
	hisi_sas_ग_लिखो32(hisi_hba, SAS_ECC_INTR_MSK, irq_msk | 0xffffffff);

	irq_value = hisi_sas_पढ़ो32(hisi_hba, SAS_ECC_INTR);
	अगर (irq_value) अणु
		one_bit_ecc_error_process_v2_hw(hisi_hba, irq_value);
		multi_bit_ecc_error_process_v2_hw(hisi_hba, irq_value);
	पूर्ण

	hisi_sas_ग_लिखो32(hisi_hba, SAS_ECC_INTR, irq_value);
	hisi_sas_ग_लिखो32(hisi_hba, SAS_ECC_INTR_MSK, irq_msk);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा hisi_sas_hw_error axi_error[] = अणु
	अणु .msk = BIT(0), .msg = "IOST_AXI_W_ERR" पूर्ण,
	अणु .msk = BIT(1), .msg = "IOST_AXI_R_ERR" पूर्ण,
	अणु .msk = BIT(2), .msg = "ITCT_AXI_W_ERR" पूर्ण,
	अणु .msk = BIT(3), .msg = "ITCT_AXI_R_ERR" पूर्ण,
	अणु .msk = BIT(4), .msg = "SATA_AXI_W_ERR" पूर्ण,
	अणु .msk = BIT(5), .msg = "SATA_AXI_R_ERR" पूर्ण,
	अणु .msk = BIT(6), .msg = "DQE_AXI_R_ERR" पूर्ण,
	अणु .msk = BIT(7), .msg = "CQE_AXI_W_ERR" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hisi_sas_hw_error fअगरo_error[] = अणु
	अणु .msk = BIT(8),  .msg = "CQE_WINFO_FIFO" पूर्ण,
	अणु .msk = BIT(9),  .msg = "CQE_MSG_FIFIO" पूर्ण,
	अणु .msk = BIT(10), .msg = "GETDQE_FIFO" पूर्ण,
	अणु .msk = BIT(11), .msg = "CMDP_FIFO" पूर्ण,
	अणु .msk = BIT(12), .msg = "AWTCTRL_FIFO" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hisi_sas_hw_error fatal_axi_errors[] = अणु
	अणु
		.irq_msk = BIT(ENT_INT_SRC3_WP_DEPTH_OFF),
		.msg = "write pointer and depth",
	पूर्ण,
	अणु
		.irq_msk = BIT(ENT_INT_SRC3_IPTT_SLOT_NOMATCH_OFF),
		.msg = "iptt no match slot",
	पूर्ण,
	अणु
		.irq_msk = BIT(ENT_INT_SRC3_RP_DEPTH_OFF),
		.msg = "read pointer and depth",
	पूर्ण,
	अणु
		.irq_msk = BIT(ENT_INT_SRC3_AXI_OFF),
		.reg = HGC_AXI_FIFO_ERR_INFO,
		.sub = axi_error,
	पूर्ण,
	अणु
		.irq_msk = BIT(ENT_INT_SRC3_FIFO_OFF),
		.reg = HGC_AXI_FIFO_ERR_INFO,
		.sub = fअगरo_error,
	पूर्ण,
	अणु
		.irq_msk = BIT(ENT_INT_SRC3_LM_OFF),
		.msg = "LM add/fetch list",
	पूर्ण,
	अणु
		.irq_msk = BIT(ENT_INT_SRC3_ABT_OFF),
		.msg = "SAS_HGC_ABT fetch LM list",
	पूर्ण,
पूर्ण;

अटल irqवापस_t fatal_axi_पूर्णांक_v2_hw(पूर्णांक irq_no, व्योम *p)
अणु
	काष्ठा hisi_hba *hisi_hba = p;
	u32 irq_value, irq_msk, err_value;
	काष्ठा device *dev = hisi_hba->dev;
	स्थिर काष्ठा hisi_sas_hw_error *axi_error;
	पूर्णांक i;

	irq_msk = hisi_sas_पढ़ो32(hisi_hba, ENT_INT_SRC_MSK3);
	hisi_sas_ग_लिखो32(hisi_hba, ENT_INT_SRC_MSK3, irq_msk | 0xfffffffe);

	irq_value = hisi_sas_पढ़ो32(hisi_hba, ENT_INT_SRC3);

	क्रम (i = 0; i < ARRAY_SIZE(fatal_axi_errors); i++) अणु
		axi_error = &fatal_axi_errors[i];
		अगर (!(irq_value & axi_error->irq_msk))
			जारी;

		hisi_sas_ग_लिखो32(hisi_hba, ENT_INT_SRC3,
				 1 << axi_error->shअगरt);
		अगर (axi_error->sub) अणु
			स्थिर काष्ठा hisi_sas_hw_error *sub = axi_error->sub;

			err_value = hisi_sas_पढ़ो32(hisi_hba, axi_error->reg);
			क्रम (; sub->msk || sub->msg; sub++) अणु
				अगर (!(err_value & sub->msk))
					जारी;
				dev_err(dev, "%s (0x%x) found!\n",
					sub->msg, irq_value);
				queue_work(hisi_hba->wq, &hisi_hba->rst_work);
			पूर्ण
		पूर्ण अन्यथा अणु
			dev_err(dev, "%s (0x%x) found!\n",
				axi_error->msg, irq_value);
			queue_work(hisi_hba->wq, &hisi_hba->rst_work);
		पूर्ण
	पूर्ण

	अगर (irq_value & BIT(ENT_INT_SRC3_ITC_INT_OFF)) अणु
		u32 reg_val = hisi_sas_पढ़ो32(hisi_hba, ITCT_CLR);
		u32 dev_id = reg_val & ITCT_DEV_MSK;
		काष्ठा hisi_sas_device *sas_dev = &hisi_hba->devices[dev_id];

		hisi_sas_ग_लिखो32(hisi_hba, ITCT_CLR, 0);
		dev_dbg(dev, "clear ITCT ok\n");
		complete(sas_dev->completion);
	पूर्ण

	hisi_sas_ग_लिखो32(hisi_hba, ENT_INT_SRC3, irq_value);
	hisi_sas_ग_लिखो32(hisi_hba, ENT_INT_SRC_MSK3, irq_msk);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t  cq_thपढ़ो_v2_hw(पूर्णांक irq_no, व्योम *p)
अणु
	काष्ठा hisi_sas_cq *cq = p;
	काष्ठा hisi_hba *hisi_hba = cq->hisi_hba;
	काष्ठा hisi_sas_slot *slot;
	काष्ठा hisi_sas_itct *itct;
	काष्ठा hisi_sas_complete_v2_hdr *complete_queue;
	u32 rd_poपूर्णांक = cq->rd_poपूर्णांक, wr_poपूर्णांक, dev_id;
	पूर्णांक queue = cq->id;

	अगर (unlikely(hisi_hba->reject_stp_links_msk))
		phys_try_accept_stp_links_v2_hw(hisi_hba);

	complete_queue = hisi_hba->complete_hdr[queue];

	wr_poपूर्णांक = hisi_sas_पढ़ो32(hisi_hba, COMPL_Q_0_WR_PTR +
				   (0x14 * queue));

	जबतक (rd_poपूर्णांक != wr_poपूर्णांक) अणु
		काष्ठा hisi_sas_complete_v2_hdr *complete_hdr;
		पूर्णांक iptt;

		complete_hdr = &complete_queue[rd_poपूर्णांक];

		/* Check क्रम NCQ completion */
		अगर (complete_hdr->act) अणु
			u32 act_पंचांगp = le32_to_cpu(complete_hdr->act);
			पूर्णांक ncq_tag_count = ffs(act_पंचांगp);
			u32 dw1 = le32_to_cpu(complete_hdr->dw1);

			dev_id = (dw1 & CMPLT_HDR_DEV_ID_MSK) >>
				 CMPLT_HDR_DEV_ID_OFF;
			itct = &hisi_hba->itct[dev_id];

			/* The NCQ tags are held in the itct header */
			जबतक (ncq_tag_count) अणु
				__le64 *_ncq_tag = &itct->qw4_15[0], __ncq_tag;
				u64 ncq_tag;

				ncq_tag_count--;
				__ncq_tag = _ncq_tag[ncq_tag_count / 5];
				ncq_tag = le64_to_cpu(__ncq_tag);
				iptt = (ncq_tag >> (ncq_tag_count % 5) * 12) &
				       0xfff;

				slot = &hisi_hba->slot_info[iptt];
				slot->cmplt_queue_slot = rd_poपूर्णांक;
				slot->cmplt_queue = queue;
				slot_complete_v2_hw(hisi_hba, slot);

				act_पंचांगp &= ~(1 << ncq_tag_count);
				ncq_tag_count = ffs(act_पंचांगp);
			पूर्ण
		पूर्ण अन्यथा अणु
			u32 dw1 = le32_to_cpu(complete_hdr->dw1);

			iptt = dw1 & CMPLT_HDR_IPTT_MSK;
			slot = &hisi_hba->slot_info[iptt];
			slot->cmplt_queue_slot = rd_poपूर्णांक;
			slot->cmplt_queue = queue;
			slot_complete_v2_hw(hisi_hba, slot);
		पूर्ण

		अगर (++rd_poपूर्णांक >= HISI_SAS_QUEUE_SLOTS)
			rd_poपूर्णांक = 0;
	पूर्ण

	/* update rd_poपूर्णांक */
	cq->rd_poपूर्णांक = rd_poपूर्णांक;
	hisi_sas_ग_लिखो32(hisi_hba, COMPL_Q_0_RD_PTR + (0x14 * queue), rd_poपूर्णांक);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t cq_पूर्णांकerrupt_v2_hw(पूर्णांक irq_no, व्योम *p)
अणु
	काष्ठा hisi_sas_cq *cq = p;
	काष्ठा hisi_hba *hisi_hba = cq->hisi_hba;
	पूर्णांक queue = cq->id;

	hisi_sas_ग_लिखो32(hisi_hba, OQ_INT_SRC, 1 << queue);

	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल irqवापस_t sata_पूर्णांक_v2_hw(पूर्णांक irq_no, व्योम *p)
अणु
	काष्ठा hisi_sas_phy *phy = p;
	काष्ठा hisi_hba *hisi_hba = phy->hisi_hba;
	काष्ठा asd_sas_phy *sas_phy = &phy->sas_phy;
	काष्ठा device *dev = hisi_hba->dev;
	काष्ठा	hisi_sas_initial_fis *initial_fis;
	काष्ठा dev_to_host_fis *fis;
	u32 ent_पंचांगp, ent_msk, ent_पूर्णांक, port_id, link_rate, hard_phy_linkrate;
	irqवापस_t res = IRQ_HANDLED;
	u8 attached_sas_addr[SAS_ADDR_SIZE] = अणु0पूर्ण;
	अचिन्हित दीर्घ flags;
	पूर्णांक phy_no, offset;

	del_समयr(&phy->समयr);

	phy_no = sas_phy->id;
	initial_fis = &hisi_hba->initial_fis[phy_no];
	fis = &initial_fis->fis;

	offset = 4 * (phy_no / 4);
	ent_msk = hisi_sas_पढ़ो32(hisi_hba, ENT_INT_SRC_MSK1 + offset);
	hisi_sas_ग_लिखो32(hisi_hba, ENT_INT_SRC_MSK1 + offset,
			 ent_msk | 1 << ((phy_no % 4) * 8));

	ent_पूर्णांक = hisi_sas_पढ़ो32(hisi_hba, ENT_INT_SRC1 + offset);
	ent_पंचांगp = ent_पूर्णांक & (1 << (ENT_INT_SRC1_D2H_FIS_CH1_OFF *
			     (phy_no % 4)));
	ent_पूर्णांक >>= ENT_INT_SRC1_D2H_FIS_CH1_OFF * (phy_no % 4);
	अगर ((ent_पूर्णांक & ENT_INT_SRC1_D2H_FIS_CH0_MSK) == 0) अणु
		dev_warn(dev, "sata int: phy%d did not receive FIS\n", phy_no);
		res = IRQ_NONE;
		जाओ end;
	पूर्ण

	/* check ERR bit of Status Register */
	अगर (fis->status & ATA_ERR) अणु
		dev_warn(dev, "sata int: phy%d FIS status: 0x%x\n", phy_no,
			 fis->status);
		hisi_sas_notअगरy_phy_event(phy, HISI_PHYE_LINK_RESET);
		res = IRQ_NONE;
		जाओ end;
	पूर्ण

	अगर (unlikely(phy_no == 8)) अणु
		u32 port_state = hisi_sas_पढ़ो32(hisi_hba, PORT_STATE);

		port_id = (port_state & PORT_STATE_PHY8_PORT_NUM_MSK) >>
			  PORT_STATE_PHY8_PORT_NUM_OFF;
		link_rate = (port_state & PORT_STATE_PHY8_CONN_RATE_MSK) >>
			    PORT_STATE_PHY8_CONN_RATE_OFF;
	पूर्ण अन्यथा अणु
		port_id = hisi_sas_पढ़ो32(hisi_hba, PHY_PORT_NUM_MA);
		port_id = (port_id >> (4 * phy_no)) & 0xf;
		link_rate = hisi_sas_पढ़ो32(hisi_hba, PHY_CONN_RATE);
		link_rate = (link_rate >> (phy_no * 4)) & 0xf;
	पूर्ण

	अगर (port_id == 0xf) अणु
		dev_err(dev, "sata int: phy%d invalid portid\n", phy_no);
		res = IRQ_NONE;
		जाओ end;
	पूर्ण

	sas_phy->linkrate = link_rate;
	hard_phy_linkrate = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no,
						HARD_PHY_LINKRATE);
	phy->maximum_linkrate = hard_phy_linkrate & 0xf;
	phy->minimum_linkrate = (hard_phy_linkrate >> 4) & 0xf;

	sas_phy->oob_mode = SATA_OOB_MODE;
	/* Make up some unique SAS address */
	attached_sas_addr[0] = 0x50;
	attached_sas_addr[6] = hisi_hba->shost->host_no;
	attached_sas_addr[7] = phy_no;
	स_नकल(sas_phy->attached_sas_addr, attached_sas_addr, SAS_ADDR_SIZE);
	स_नकल(sas_phy->frame_rcvd, fis, माप(काष्ठा dev_to_host_fis));
	dev_info(dev, "sata int phyup: phy%d link_rate=%d\n", phy_no, link_rate);
	phy->phy_type &= ~(PORT_TYPE_SAS | PORT_TYPE_SATA);
	phy->port_id = port_id;
	phy->phy_type |= PORT_TYPE_SATA;
	phy->phy_attached = 1;
	phy->identअगरy.device_type = SAS_SATA_DEV;
	phy->frame_rcvd_size = माप(काष्ठा dev_to_host_fis);
	phy->identअगरy.target_port_protocols = SAS_PROTOCOL_SATA;
	hisi_sas_notअगरy_phy_event(phy, HISI_PHYE_PHY_UP);

	spin_lock_irqsave(&phy->lock, flags);
	अगर (phy->reset_completion) अणु
		phy->in_reset = 0;
		complete(phy->reset_completion);
	पूर्ण
	spin_unlock_irqrestore(&phy->lock, flags);
end:
	hisi_sas_ग_लिखो32(hisi_hba, ENT_INT_SRC1 + offset, ent_पंचांगp);
	hisi_sas_ग_लिखो32(hisi_hba, ENT_INT_SRC_MSK1 + offset, ent_msk);

	वापस res;
पूर्ण

अटल irq_handler_t phy_पूर्णांकerrupts[HISI_SAS_PHY_INT_NR] = अणु
	पूर्णांक_phy_upकरोwn_v2_hw,
	पूर्णांक_chnl_पूर्णांक_v2_hw,
पूर्ण;

अटल irq_handler_t fatal_पूर्णांकerrupts[HISI_SAS_FATAL_INT_NR] = अणु
	fatal_ecc_पूर्णांक_v2_hw,
	fatal_axi_पूर्णांक_v2_hw
पूर्ण;

#घोषणा CQ0_IRQ_INDEX (96)

अटल पूर्णांक hisi_sas_v2_पूर्णांकerrupt_preinit(काष्ठा hisi_hba *hisi_hba)
अणु
	काष्ठा platक्रमm_device *pdev = hisi_hba->platक्रमm_dev;
	काष्ठा Scsi_Host *shost = hisi_hba->shost;
	काष्ठा irq_affinity desc = अणु
		.pre_vectors = CQ0_IRQ_INDEX,
		.post_vectors = 16,
	पूर्ण;
	पूर्णांक resv = desc.pre_vectors + desc.post_vectors, minvec = resv + 1, nvec;

	nvec = devm_platक्रमm_get_irqs_affinity(pdev, &desc, minvec, 128,
					       &hisi_hba->irq_map);
	अगर (nvec < 0)
		वापस nvec;

	shost->nr_hw_queues = hisi_hba->cq_nvecs = nvec - resv;

	वापस 0;
पूर्ण

/*
 * There is a limitation in the hip06 chipset that we need
 * to map in all mbigen पूर्णांकerrupts, even अगर they are not used.
 */
अटल पूर्णांक पूर्णांकerrupt_init_v2_hw(काष्ठा hisi_hba *hisi_hba)
अणु
	काष्ठा platक्रमm_device *pdev = hisi_hba->platक्रमm_dev;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक irq, rc = 0;
	पूर्णांक i, phy_no, fatal_no, queue_no;

	क्रम (i = 0; i < HISI_SAS_PHY_INT_NR; i++) अणु
		irq = hisi_hba->irq_map[i + 1]; /* Phy up/करोwn is irq1 */
		rc = devm_request_irq(dev, irq, phy_पूर्णांकerrupts[i], 0,
				      DRV_NAME " phy", hisi_hba);
		अगर (rc) अणु
			dev_err(dev, "irq init: could not request phy interrupt %d, rc=%d\n",
				irq, rc);
			rc = -ENOENT;
			जाओ err_out;
		पूर्ण
	पूर्ण

	क्रम (phy_no = 0; phy_no < hisi_hba->n_phy; phy_no++) अणु
		काष्ठा hisi_sas_phy *phy = &hisi_hba->phy[phy_no];

		irq = hisi_hba->irq_map[phy_no + 72];
		rc = devm_request_irq(dev, irq, sata_पूर्णांक_v2_hw, 0,
				      DRV_NAME " sata", phy);
		अगर (rc) अणु
			dev_err(dev, "irq init: could not request sata interrupt %d, rc=%d\n",
				irq, rc);
			rc = -ENOENT;
			जाओ err_out;
		पूर्ण
	पूर्ण

	क्रम (fatal_no = 0; fatal_no < HISI_SAS_FATAL_INT_NR; fatal_no++) अणु
		irq = hisi_hba->irq_map[fatal_no + 81];
		rc = devm_request_irq(dev, irq, fatal_पूर्णांकerrupts[fatal_no], 0,
				      DRV_NAME " fatal", hisi_hba);
		अगर (rc) अणु
			dev_err(dev, "irq init: could not request fatal interrupt %d, rc=%d\n",
				irq, rc);
			rc = -ENOENT;
			जाओ err_out;
		पूर्ण
	पूर्ण

	क्रम (queue_no = 0; queue_no < hisi_hba->cq_nvecs; queue_no++) अणु
		काष्ठा hisi_sas_cq *cq = &hisi_hba->cq[queue_no];

		cq->irq_no = hisi_hba->irq_map[queue_no + 96];
		rc = devm_request_thपढ़ोed_irq(dev, cq->irq_no,
					       cq_पूर्णांकerrupt_v2_hw,
					       cq_thपढ़ो_v2_hw, IRQF_ONESHOT,
					       DRV_NAME " cq", cq);
		अगर (rc) अणु
			dev_err(dev, "irq init: could not request cq interrupt %d, rc=%d\n",
					cq->irq_no, rc);
			rc = -ENOENT;
			जाओ err_out;
		पूर्ण
		cq->irq_mask = irq_get_affinity_mask(cq->irq_no);
	पूर्ण
err_out:
	वापस rc;
पूर्ण

अटल पूर्णांक hisi_sas_v2_init(काष्ठा hisi_hba *hisi_hba)
अणु
	पूर्णांक rc;

	स_रखो(hisi_hba->sata_dev_biपंचांगap, 0, माप(hisi_hba->sata_dev_biपंचांगap));

	rc = hw_init_v2_hw(hisi_hba);
	अगर (rc)
		वापस rc;

	rc = पूर्णांकerrupt_init_v2_hw(hisi_hba);
	अगर (rc)
		वापस rc;

	वापस 0;
पूर्ण

अटल व्योम पूर्णांकerrupt_disable_v2_hw(काष्ठा hisi_hba *hisi_hba)
अणु
	काष्ठा platक्रमm_device *pdev = hisi_hba->platक्रमm_dev;
	पूर्णांक i;

	क्रम (i = 0; i < hisi_hba->queue_count; i++)
		hisi_sas_ग_लिखो32(hisi_hba, OQ0_INT_SRC_MSK + 0x4 * i, 0x1);

	hisi_sas_ग_लिखो32(hisi_hba, ENT_INT_SRC_MSK1, 0xffffffff);
	hisi_sas_ग_लिखो32(hisi_hba, ENT_INT_SRC_MSK2, 0xffffffff);
	hisi_sas_ग_लिखो32(hisi_hba, ENT_INT_SRC_MSK3, 0xffffffff);
	hisi_sas_ग_लिखो32(hisi_hba, SAS_ECC_INTR_MSK, 0xffffffff);

	क्रम (i = 0; i < hisi_hba->n_phy; i++) अणु
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, CHL_INT1_MSK, 0xffffffff);
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, CHL_INT2_MSK, 0xffffffff);
	पूर्ण

	क्रम (i = 0; i < 128; i++)
		synchronize_irq(platक्रमm_get_irq(pdev, i));
पूर्ण


अटल u32 get_phys_state_v2_hw(काष्ठा hisi_hba *hisi_hba)
अणु
	वापस hisi_sas_पढ़ो32(hisi_hba, PHY_STATE);
पूर्ण

अटल पूर्णांक soft_reset_v2_hw(काष्ठा hisi_hba *hisi_hba)
अणु
	काष्ठा device *dev = hisi_hba->dev;
	पूर्णांक rc, cnt;

	पूर्णांकerrupt_disable_v2_hw(hisi_hba);
	hisi_sas_ग_लिखो32(hisi_hba, DLVRY_QUEUE_ENABLE, 0x0);

	hisi_sas_stop_phys(hisi_hba);

	mdelay(10);

	hisi_sas_ग_लिखो32(hisi_hba, AXI_MASTER_CFG_BASE + AM_CTRL_GLOBAL, 0x1);

	/* रुको until bus idle */
	cnt = 0;
	जबतक (1) अणु
		u32 status = hisi_sas_पढ़ो32_relaxed(hisi_hba,
				AXI_MASTER_CFG_BASE + AM_CURR_TRANS_RETURN);

		अगर (status == 0x3)
			अवरोध;

		udelay(10);
		अगर (cnt++ > 10) अणु
			dev_err(dev, "wait axi bus state to idle timeout!\n");
			वापस -1;
		पूर्ण
	पूर्ण

	hisi_sas_init_mem(hisi_hba);

	rc = hw_init_v2_hw(hisi_hba);
	अगर (rc)
		वापस rc;

	phys_reject_stp_links_v2_hw(hisi_hba);

	वापस 0;
पूर्ण

अटल पूर्णांक ग_लिखो_gpio_v2_hw(काष्ठा hisi_hba *hisi_hba, u8 reg_type,
			u8 reg_index, u8 reg_count, u8 *ग_लिखो_data)
अणु
	काष्ठा device *dev = hisi_hba->dev;
	पूर्णांक phy_no, count;

	अगर (!hisi_hba->sgpio_regs)
		वापस -EOPNOTSUPP;

	चयन (reg_type) अणु
	हाल SAS_GPIO_REG_TX:
		count = reg_count * 4;
		count = min(count, hisi_hba->n_phy);

		क्रम (phy_no = 0; phy_no < count; phy_no++) अणु
			/*
			 * GPIO_TX[n] रेजिस्टर has the highest numbered drive
			 * of the four in the first byte and the lowest
			 * numbered drive in the fourth byte.
			 * See SFF-8485 Rev. 0.7 Table 24.
			 */
			व्योम __iomem  *reg_addr = hisi_hba->sgpio_regs +
					reg_index * 4 + phy_no;
			पूर्णांक data_idx = phy_no + 3 - (phy_no % 4) * 2;

			ग_लिखोb(ग_लिखो_data[data_idx], reg_addr);
		पूर्ण

		अवरोध;
	शेष:
		dev_err(dev, "write gpio: unsupported or bad reg type %d\n",
			reg_type);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम रुको_cmds_complete_समयout_v2_hw(काष्ठा hisi_hba *hisi_hba,
					     पूर्णांक delay_ms, पूर्णांक समयout_ms)
अणु
	काष्ठा device *dev = hisi_hba->dev;
	पूर्णांक entries, entries_old = 0, समय;

	क्रम (समय = 0; समय < समयout_ms; समय += delay_ms) अणु
		entries = hisi_sas_पढ़ो32(hisi_hba, CQE_SEND_CNT);
		अगर (entries == entries_old)
			अवरोध;

		entries_old = entries;
		msleep(delay_ms);
	पूर्ण

	अगर (समय >= समयout_ms) अणु
		dev_dbg(dev, "Wait commands complete timeout!\n");
		वापस;
	पूर्ण

	dev_dbg(dev, "wait commands complete %dms\n", समय);

पूर्ण

अटल काष्ठा device_attribute *host_attrs_v2_hw[] = अणु
	&dev_attr_phy_event_threshold,
	शून्य
पूर्ण;

अटल पूर्णांक map_queues_v2_hw(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा hisi_hba *hisi_hba = shost_priv(shost);
	काष्ठा blk_mq_queue_map *qmap = &shost->tag_set.map[HCTX_TYPE_DEFAULT];
	स्थिर काष्ठा cpumask *mask;
	अचिन्हित पूर्णांक queue, cpu;

	क्रम (queue = 0; queue < qmap->nr_queues; queue++) अणु
		mask = irq_get_affinity_mask(hisi_hba->irq_map[96 + queue]);
		अगर (!mask)
			जारी;

		क्रम_each_cpu(cpu, mask)
			qmap->mq_map[cpu] = qmap->queue_offset + queue;
	पूर्ण

	वापस 0;

पूर्ण

अटल काष्ठा scsi_host_ढाँचा sht_v2_hw = अणु
	.name			= DRV_NAME,
	.proc_name		= DRV_NAME,
	.module			= THIS_MODULE,
	.queuecommand		= sas_queuecommand,
	.dma_need_drain		= ata_scsi_dma_need_drain,
	.target_alloc		= sas_target_alloc,
	.slave_configure	= hisi_sas_slave_configure,
	.scan_finished		= hisi_sas_scan_finished,
	.scan_start		= hisi_sas_scan_start,
	.change_queue_depth	= sas_change_queue_depth,
	.bios_param		= sas_bios_param,
	.this_id		= -1,
	.sg_tablesize		= HISI_SAS_SGE_PAGE_CNT,
	.max_sectors		= SCSI_DEFAULT_MAX_SECTORS,
	.eh_device_reset_handler = sas_eh_device_reset_handler,
	.eh_target_reset_handler = sas_eh_target_reset_handler,
	.target_destroy		= sas_target_destroy,
	.ioctl			= sas_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl		= sas_ioctl,
#पूर्ण_अगर
	.shost_attrs		= host_attrs_v2_hw,
	.host_reset		= hisi_sas_host_reset,
	.map_queues		= map_queues_v2_hw,
	.host_tagset		= 1,
पूर्ण;

अटल स्थिर काष्ठा hisi_sas_hw hisi_sas_v2_hw = अणु
	.hw_init = hisi_sas_v2_init,
	.पूर्णांकerrupt_preinit = hisi_sas_v2_पूर्णांकerrupt_preinit,
	.setup_itct = setup_itct_v2_hw,
	.slot_index_alloc = slot_index_alloc_quirk_v2_hw,
	.alloc_dev = alloc_dev_quirk_v2_hw,
	.sl_notअगरy_ssp = sl_notअगरy_ssp_v2_hw,
	.get_wideport_biपंचांगap = get_wideport_biपंचांगap_v2_hw,
	.clear_itct = clear_itct_v2_hw,
	.मुक्त_device = मुक्त_device_v2_hw,
	.prep_smp = prep_smp_v2_hw,
	.prep_ssp = prep_ssp_v2_hw,
	.prep_stp = prep_ata_v2_hw,
	.prep_पात = prep_पात_v2_hw,
	.start_delivery = start_delivery_v2_hw,
	.phys_init = phys_init_v2_hw,
	.phy_start = start_phy_v2_hw,
	.phy_disable = disable_phy_v2_hw,
	.phy_hard_reset = phy_hard_reset_v2_hw,
	.get_events = phy_get_events_v2_hw,
	.phy_set_linkrate = phy_set_linkrate_v2_hw,
	.phy_get_max_linkrate = phy_get_max_linkrate_v2_hw,
	.complete_hdr_size = माप(काष्ठा hisi_sas_complete_v2_hdr),
	.soft_reset = soft_reset_v2_hw,
	.get_phys_state = get_phys_state_v2_hw,
	.ग_लिखो_gpio = ग_लिखो_gpio_v2_hw,
	.रुको_cmds_complete_समयout = रुको_cmds_complete_समयout_v2_hw,
	.sht = &sht_v2_hw,
पूर्ण;

अटल पूर्णांक hisi_sas_v2_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस hisi_sas_probe(pdev, &hisi_sas_v2_hw);
पूर्ण

अटल पूर्णांक hisi_sas_v2_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	वापस hisi_sas_हटाओ(pdev);
पूर्ण

अटल स्थिर काष्ठा of_device_id sas_v2_of_match[] = अणु
	अणु .compatible = "hisilicon,hip06-sas-v2",पूर्ण,
	अणु .compatible = "hisilicon,hip07-sas-v2",पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sas_v2_of_match);

अटल स्थिर काष्ठा acpi_device_id sas_v2_acpi_match[] = अणु
	अणु "HISI0162", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(acpi, sas_v2_acpi_match);

अटल काष्ठा platक्रमm_driver hisi_sas_v2_driver = अणु
	.probe = hisi_sas_v2_probe,
	.हटाओ = hisi_sas_v2_हटाओ,
	.driver = अणु
		.name = DRV_NAME,
		.of_match_table = sas_v2_of_match,
		.acpi_match_table = ACPI_PTR(sas_v2_acpi_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(hisi_sas_v2_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("John Garry <john.garry@huawei.com>");
MODULE_DESCRIPTION("HISILICON SAS controller v2 hw driver");
MODULE_ALIAS("platform:" DRV_NAME);
