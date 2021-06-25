<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2017 Hisilicon Limited.
 */

#समावेश "hisi_sas.h"
#घोषणा DRV_NAME "hisi_sas_v3_hw"

/* global रेजिस्टरs need init */
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
#घोषणा PHY_CONN_RATE			0x30
#घोषणा ITCT_CLR			0x44
#घोषणा ITCT_CLR_EN_OFF			16
#घोषणा ITCT_CLR_EN_MSK			(0x1 << ITCT_CLR_EN_OFF)
#घोषणा ITCT_DEV_OFF			0
#घोषणा ITCT_DEV_MSK			(0x7ff << ITCT_DEV_OFF)
#घोषणा SAS_AXI_USER3			0x50
#घोषणा IO_SATA_BROKEN_MSG_ADDR_LO	0x58
#घोषणा IO_SATA_BROKEN_MSG_ADDR_HI	0x5c
#घोषणा SATA_INITI_D2H_STORE_ADDR_LO	0x60
#घोषणा SATA_INITI_D2H_STORE_ADDR_HI	0x64
#घोषणा CFG_MAX_TAG			0x68
#घोषणा HGC_SAS_TX_OPEN_FAIL_RETRY_CTRL	0x84
#घोषणा HGC_SAS_TXFAIL_RETRY_CTRL	0x88
#घोषणा HGC_GET_ITV_TIME		0x90
#घोषणा DEVICE_MSG_WORK_MODE		0x94
#घोषणा OPENA_WT_CONTI_TIME		0x9c
#घोषणा I_T_NEXUS_LOSS_TIME		0xa0
#घोषणा MAX_CON_TIME_LIMIT_TIME		0xa4
#घोषणा BUS_INACTIVE_LIMIT_TIME		0xa8
#घोषणा REJECT_TO_OPEN_LIMIT_TIME	0xac
#घोषणा CQ_INT_CONVERGE_EN		0xb0
#घोषणा CFG_AGING_TIME			0xbc
#घोषणा HGC_DFX_CFG2			0xc0
#घोषणा CFG_ABT_SET_QUERY_IPTT	0xd4
#घोषणा CFG_SET_ABORTED_IPTT_OFF	0
#घोषणा CFG_SET_ABORTED_IPTT_MSK	(0xfff << CFG_SET_ABORTED_IPTT_OFF)
#घोषणा CFG_SET_ABORTED_EN_OFF	12
#घोषणा CFG_ABT_SET_IPTT_DONE	0xd8
#घोषणा CFG_ABT_SET_IPTT_DONE_OFF	0
#घोषणा HGC_IOMB_PROC1_STATUS	0x104
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
#घोषणा CHNL_INT_STATUS			0x148
#घोषणा TAB_DFX				0x14c
#घोषणा HGC_ITCT_ECC_ADDR		0x150
#घोषणा HGC_ITCT_ECC_1B_ADDR_OFF		0
#घोषणा HGC_ITCT_ECC_1B_ADDR_MSK		(0x3ff << \
						 HGC_ITCT_ECC_1B_ADDR_OFF)
#घोषणा HGC_ITCT_ECC_MB_ADDR_OFF		16
#घोषणा HGC_ITCT_ECC_MB_ADDR_MSK		(0x3ff << \
						 HGC_ITCT_ECC_MB_ADDR_OFF)
#घोषणा HGC_AXI_FIFO_ERR_INFO  0x154
#घोषणा AXI_ERR_INFO_OFF               0
#घोषणा AXI_ERR_INFO_MSK               (0xff << AXI_ERR_INFO_OFF)
#घोषणा FIFO_ERR_INFO_OFF              8
#घोषणा FIFO_ERR_INFO_MSK              (0xff << FIFO_ERR_INFO_OFF)
#घोषणा TAB_RD_TYPE			0x15c
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
#घोषणा ENT_INT_SRC3_DQE_POISON_OFF	18
#घोषणा ENT_INT_SRC3_IOST_POISON_OFF	19
#घोषणा ENT_INT_SRC3_ITCT_POISON_OFF	20
#घोषणा ENT_INT_SRC3_ITCT_NCQ_POISON_OFF	21
#घोषणा ENT_INT_SRC_MSK1		0x1c4
#घोषणा ENT_INT_SRC_MSK2		0x1c8
#घोषणा ENT_INT_SRC_MSK3		0x1cc
#घोषणा ENT_INT_SRC_MSK3_ENT95_MSK_OFF	31
#घोषणा CHNL_PHYUPDOWN_INT_MSK		0x1d0
#घोषणा CHNL_ENT_INT_MSK			0x1d4
#घोषणा HGC_COM_INT_MSK				0x1d8
#घोषणा ENT_INT_SRC_MSK3_ENT95_MSK_MSK	(0x1 << ENT_INT_SRC_MSK3_ENT95_MSK_OFF)
#घोषणा SAS_ECC_INTR			0x1e8
#घोषणा SAS_ECC_INTR_DQE_ECC_1B_OFF		0
#घोषणा SAS_ECC_INTR_DQE_ECC_MB_OFF		1
#घोषणा SAS_ECC_INTR_IOST_ECC_1B_OFF	2
#घोषणा SAS_ECC_INTR_IOST_ECC_MB_OFF	3
#घोषणा SAS_ECC_INTR_ITCT_ECC_1B_OFF	4
#घोषणा SAS_ECC_INTR_ITCT_ECC_MB_OFF	5
#घोषणा SAS_ECC_INTR_ITCTLIST_ECC_1B_OFF	6
#घोषणा SAS_ECC_INTR_ITCTLIST_ECC_MB_OFF	7
#घोषणा SAS_ECC_INTR_IOSTLIST_ECC_1B_OFF	8
#घोषणा SAS_ECC_INTR_IOSTLIST_ECC_MB_OFF	9
#घोषणा SAS_ECC_INTR_CQE_ECC_1B_OFF		10
#घोषणा SAS_ECC_INTR_CQE_ECC_MB_OFF		11
#घोषणा SAS_ECC_INTR_NCQ_MEM0_ECC_1B_OFF	12
#घोषणा SAS_ECC_INTR_NCQ_MEM0_ECC_MB_OFF	13
#घोषणा SAS_ECC_INTR_NCQ_MEM1_ECC_1B_OFF	14
#घोषणा SAS_ECC_INTR_NCQ_MEM1_ECC_MB_OFF	15
#घोषणा SAS_ECC_INTR_NCQ_MEM2_ECC_1B_OFF	16
#घोषणा SAS_ECC_INTR_NCQ_MEM2_ECC_MB_OFF	17
#घोषणा SAS_ECC_INTR_NCQ_MEM3_ECC_1B_OFF	18
#घोषणा SAS_ECC_INTR_NCQ_MEM3_ECC_MB_OFF	19
#घोषणा SAS_ECC_INTR_OOO_RAM_ECC_1B_OFF		20
#घोषणा SAS_ECC_INTR_OOO_RAM_ECC_MB_OFF		21
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
#घोषणा HGC_RXM_DFX_STATUS14		0xae8
#घोषणा HGC_RXM_DFX_STATUS14_MEM0_OFF	0
#घोषणा HGC_RXM_DFX_STATUS14_MEM0_MSK	(0x1ff << \
					 HGC_RXM_DFX_STATUS14_MEM0_OFF)
#घोषणा HGC_RXM_DFX_STATUS14_MEM1_OFF	9
#घोषणा HGC_RXM_DFX_STATUS14_MEM1_MSK	(0x1ff << \
					 HGC_RXM_DFX_STATUS14_MEM1_OFF)
#घोषणा HGC_RXM_DFX_STATUS14_MEM2_OFF	18
#घोषणा HGC_RXM_DFX_STATUS14_MEM2_MSK	(0x1ff << \
					 HGC_RXM_DFX_STATUS14_MEM2_OFF)
#घोषणा HGC_RXM_DFX_STATUS15		0xaec
#घोषणा HGC_RXM_DFX_STATUS15_MEM3_OFF	0
#घोषणा HGC_RXM_DFX_STATUS15_MEM3_MSK	(0x1ff << \
					 HGC_RXM_DFX_STATUS15_MEM3_OFF)
#घोषणा AWQOS_AWCACHE_CFG	0xc84
#घोषणा ARQOS_ARCACHE_CFG	0xc88
#घोषणा HILINK_ERR_DFX		0xe04
#घोषणा SAS_GPIO_CFG_0		0x1000
#घोषणा SAS_GPIO_CFG_1		0x1004
#घोषणा SAS_GPIO_TX_0_1	0x1040
#घोषणा SAS_CFG_DRIVE_VLD	0x1070

/* phy रेजिस्टरs requiring init */
#घोषणा PORT_BASE			(0x2000)
#घोषणा PHY_CFG				(PORT_BASE + 0x0)
#घोषणा HARD_PHY_LINKRATE		(PORT_BASE + 0x4)
#घोषणा PHY_CFG_ENA_OFF			0
#घोषणा PHY_CFG_ENA_MSK			(0x1 << PHY_CFG_ENA_OFF)
#घोषणा PHY_CFG_DC_OPT_OFF		2
#घोषणा PHY_CFG_DC_OPT_MSK		(0x1 << PHY_CFG_DC_OPT_OFF)
#घोषणा PHY_CFG_PHY_RST_OFF		3
#घोषणा PHY_CFG_PHY_RST_MSK		(0x1 << PHY_CFG_PHY_RST_OFF)
#घोषणा PROG_PHY_LINK_RATE		(PORT_BASE + 0x8)
#घोषणा CFG_PROG_PHY_LINK_RATE_OFF	0
#घोषणा CFG_PROG_PHY_LINK_RATE_MSK	(0xff << CFG_PROG_PHY_LINK_RATE_OFF)
#घोषणा CFG_PROG_OOB_PHY_LINK_RATE_OFF	8
#घोषणा CFG_PROG_OOB_PHY_LINK_RATE_MSK	(0xf << CFG_PROG_OOB_PHY_LINK_RATE_OFF)
#घोषणा PHY_CTRL			(PORT_BASE + 0x14)
#घोषणा PHY_CTRL_RESET_OFF		0
#घोषणा PHY_CTRL_RESET_MSK		(0x1 << PHY_CTRL_RESET_OFF)
#घोषणा CMD_HDR_PIR_OFF			8
#घोषणा CMD_HDR_PIR_MSK			(0x1 << CMD_HDR_PIR_OFF)
#घोषणा SERDES_CFG			(PORT_BASE + 0x1c)
#घोषणा CFG_ALOS_CHK_DISABLE_OFF	9
#घोषणा CFG_ALOS_CHK_DISABLE_MSK	(0x1 << CFG_ALOS_CHK_DISABLE_OFF)
#घोषणा SAS_PHY_BIST_CTRL		(PORT_BASE + 0x2c)
#घोषणा CFG_BIST_MODE_SEL_OFF		0
#घोषणा CFG_BIST_MODE_SEL_MSK		(0xf << CFG_BIST_MODE_SEL_OFF)
#घोषणा CFG_LOOP_TEST_MODE_OFF		14
#घोषणा CFG_LOOP_TEST_MODE_MSK		(0x3 << CFG_LOOP_TEST_MODE_OFF)
#घोषणा CFG_RX_BIST_EN_OFF		16
#घोषणा CFG_RX_BIST_EN_MSK		(0x1 << CFG_RX_BIST_EN_OFF)
#घोषणा CFG_TX_BIST_EN_OFF		17
#घोषणा CFG_TX_BIST_EN_MSK		(0x1 << CFG_TX_BIST_EN_OFF)
#घोषणा CFG_BIST_TEST_OFF		18
#घोषणा CFG_BIST_TEST_MSK		(0x1 << CFG_BIST_TEST_OFF)
#घोषणा SAS_PHY_BIST_CODE		(PORT_BASE + 0x30)
#घोषणा SAS_PHY_BIST_CODE1		(PORT_BASE + 0x34)
#घोषणा SAS_BIST_ERR_CNT		(PORT_BASE + 0x38)
#घोषणा SL_CFG				(PORT_BASE + 0x84)
#घोषणा AIP_LIMIT			(PORT_BASE + 0x90)
#घोषणा SL_CONTROL			(PORT_BASE + 0x94)
#घोषणा SL_CONTROL_NOTIFY_EN_OFF	0
#घोषणा SL_CONTROL_NOTIFY_EN_MSK	(0x1 << SL_CONTROL_NOTIFY_EN_OFF)
#घोषणा SL_CTA_OFF		17
#घोषणा SL_CTA_MSK		(0x1 << SL_CTA_OFF)
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
#घोषणा TXID_AUTO				(PORT_BASE + 0xb8)
#घोषणा CT3_OFF		1
#घोषणा CT3_MSK		(0x1 << CT3_OFF)
#घोषणा TX_HARDRST_OFF          2
#घोषणा TX_HARDRST_MSK          (0x1 << TX_HARDRST_OFF)
#घोषणा RX_IDAF_DWORD0			(PORT_BASE + 0xc4)
#घोषणा RXOP_CHECK_CFG_H		(PORT_BASE + 0xfc)
#घोषणा STP_LINK_TIMER			(PORT_BASE + 0x120)
#घोषणा STP_LINK_TIMEOUT_STATE		(PORT_BASE + 0x124)
#घोषणा CON_CFG_DRIVER			(PORT_BASE + 0x130)
#घोषणा SAS_SSP_CON_TIMER_CFG		(PORT_BASE + 0x134)
#घोषणा SAS_SMP_CON_TIMER_CFG		(PORT_BASE + 0x138)
#घोषणा SAS_STP_CON_TIMER_CFG		(PORT_BASE + 0x13c)
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
#घोषणा CHL_INT1_DMAC_TX_ECC_MB_ERR_OFF	15
#घोषणा CHL_INT1_DMAC_TX_ECC_1B_ERR_OFF	16
#घोषणा CHL_INT1_DMAC_RX_ECC_MB_ERR_OFF	17
#घोषणा CHL_INT1_DMAC_RX_ECC_1B_ERR_OFF	18
#घोषणा CHL_INT1_DMAC_TX_AXI_WR_ERR_OFF	19
#घोषणा CHL_INT1_DMAC_TX_AXI_RD_ERR_OFF	20
#घोषणा CHL_INT1_DMAC_RX_AXI_WR_ERR_OFF	21
#घोषणा CHL_INT1_DMAC_RX_AXI_RD_ERR_OFF	22
#घोषणा CHL_INT1_DMAC_TX_FIFO_ERR_OFF	23
#घोषणा CHL_INT1_DMAC_RX_FIFO_ERR_OFF	24
#घोषणा CHL_INT1_DMAC_TX_AXI_RUSER_ERR_OFF	26
#घोषणा CHL_INT1_DMAC_RX_AXI_RUSER_ERR_OFF	27
#घोषणा CHL_INT2			(PORT_BASE + 0x1bc)
#घोषणा CHL_INT2_SL_IDAF_TOUT_CONF_OFF	0
#घोषणा CHL_INT2_RX_DISP_ERR_OFF	28
#घोषणा CHL_INT2_RX_CODE_ERR_OFF	29
#घोषणा CHL_INT2_RX_INVLD_DW_OFF	30
#घोषणा CHL_INT2_STP_LINK_TIMEOUT_OFF	31
#घोषणा CHL_INT0_MSK			(PORT_BASE + 0x1c0)
#घोषणा CHL_INT1_MSK			(PORT_BASE + 0x1c4)
#घोषणा CHL_INT2_MSK			(PORT_BASE + 0x1c8)
#घोषणा SAS_EC_INT_COAL_TIME		(PORT_BASE + 0x1cc)
#घोषणा CHL_INT_COAL_EN			(PORT_BASE + 0x1d0)
#घोषणा SAS_RX_TRAIN_TIMER		(PORT_BASE + 0x2a4)
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

#घोषणा COARSETUNE_TIME			(PORT_BASE + 0x304)
#घोषणा TXDEEMPH_G1			(PORT_BASE + 0x350)
#घोषणा ERR_CNT_DWS_LOST		(PORT_BASE + 0x380)
#घोषणा ERR_CNT_RESET_PROB		(PORT_BASE + 0x384)
#घोषणा ERR_CNT_INVLD_DW		(PORT_BASE + 0x390)
#घोषणा ERR_CNT_CODE_ERR		(PORT_BASE + 0x394)
#घोषणा ERR_CNT_DISP_ERR		(PORT_BASE + 0x398)
#घोषणा DFX_FIFO_CTRL			(PORT_BASE + 0x3a0)
#घोषणा DFX_FIFO_CTRL_TRIGGER_MODE_OFF	0
#घोषणा DFX_FIFO_CTRL_TRIGGER_MODE_MSK	(0x7 << DFX_FIFO_CTRL_TRIGGER_MODE_OFF)
#घोषणा DFX_FIFO_CTRL_DUMP_MODE_OFF	3
#घोषणा DFX_FIFO_CTRL_DUMP_MODE_MSK	(0x7 << DFX_FIFO_CTRL_DUMP_MODE_OFF)
#घोषणा DFX_FIFO_CTRL_SIGNAL_SEL_OFF	6
#घोषणा DFX_FIFO_CTRL_SIGNAL_SEL_MSK	(0xF << DFX_FIFO_CTRL_SIGNAL_SEL_OFF)
#घोषणा DFX_FIFO_CTRL_DUMP_DISABLE_OFF	10
#घोषणा DFX_FIFO_CTRL_DUMP_DISABLE_MSK	(0x1 << DFX_FIFO_CTRL_DUMP_DISABLE_OFF)
#घोषणा DFX_FIFO_TRIGGER		(PORT_BASE + 0x3a4)
#घोषणा DFX_FIFO_TRIGGER_MSK		(PORT_BASE + 0x3a8)
#घोषणा DFX_FIFO_DUMP_MSK		(PORT_BASE + 0x3aC)
#घोषणा DFX_FIFO_RD_DATA		(PORT_BASE + 0x3b0)

#घोषणा DEFAULT_ITCT_HW		2048 /* reset value, not reprogrammed */
#अगर (HISI_SAS_MAX_DEVICES > DEFAULT_ITCT_HW)
#त्रुटि Max ITCT exceeded
#पूर्ण_अगर

#घोषणा AXI_MASTER_CFG_BASE		(0x5000)
#घोषणा AM_CTRL_GLOBAL			(0x0)
#घोषणा AM_CTRL_SHUTDOWN_REQ_OFF	0
#घोषणा AM_CTRL_SHUTDOWN_REQ_MSK	(0x1 << AM_CTRL_SHUTDOWN_REQ_OFF)
#घोषणा AM_CURR_TRANS_RETURN	(0x150)

#घोषणा AM_CFG_MAX_TRANS		(0x5010)
#घोषणा AM_CFG_SINGLE_PORT_MAX_TRANS	(0x5014)
#घोषणा AXI_CFG					(0x5100)
#घोषणा AM_ROB_ECC_ERR_ADDR		(0x510c)
#घोषणा AM_ROB_ECC_ERR_ADDR_OFF	0
#घोषणा AM_ROB_ECC_ERR_ADDR_MSK	0xffffffff

/* RAS रेजिस्टरs need init */
#घोषणा RAS_BASE		(0x6000)
#घोषणा SAS_RAS_INTR0			(RAS_BASE)
#घोषणा SAS_RAS_INTR1			(RAS_BASE + 0x04)
#घोषणा SAS_RAS_INTR0_MASK		(RAS_BASE + 0x08)
#घोषणा SAS_RAS_INTR1_MASK		(RAS_BASE + 0x0c)
#घोषणा CFG_SAS_RAS_INTR_MASK		(RAS_BASE + 0x1c)
#घोषणा SAS_RAS_INTR2			(RAS_BASE + 0x20)
#घोषणा SAS_RAS_INTR2_MASK		(RAS_BASE + 0x24)

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
#घोषणा CMD_HDR_PORT_OFF		18
#घोषणा CMD_HDR_PORT_MSK		(0xf << CMD_HDR_PORT_OFF)
#घोषणा CMD_HDR_PRIORITY_OFF		27
#घोषणा CMD_HDR_PRIORITY_MSK		(0x1 << CMD_HDR_PRIORITY_OFF)
#घोषणा CMD_HDR_CMD_OFF			29
#घोषणा CMD_HDR_CMD_MSK			(0x7 << CMD_HDR_CMD_OFF)
/* dw1 */
#घोषणा CMD_HDR_UNCON_CMD_OFF	3
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
/* dw3 */
#घोषणा CMD_HDR_IPTT_OFF		0
#घोषणा CMD_HDR_IPTT_MSK		(0xffff << CMD_HDR_IPTT_OFF)
/* dw6 */
#घोषणा CMD_HDR_DIF_SGL_LEN_OFF		0
#घोषणा CMD_HDR_DIF_SGL_LEN_MSK		(0xffff << CMD_HDR_DIF_SGL_LEN_OFF)
#घोषणा CMD_HDR_DATA_SGL_LEN_OFF	16
#घोषणा CMD_HDR_DATA_SGL_LEN_MSK	(0xffff << CMD_HDR_DATA_SGL_LEN_OFF)
/* dw7 */
#घोषणा CMD_HDR_ADDR_MODE_SEL_OFF		15
#घोषणा CMD_HDR_ADDR_MODE_SEL_MSK		(1 << CMD_HDR_ADDR_MODE_SEL_OFF)
#घोषणा CMD_HDR_ABORT_IPTT_OFF		16
#घोषणा CMD_HDR_ABORT_IPTT_MSK		(0xffff << CMD_HDR_ABORT_IPTT_OFF)

/* Completion header */
/* dw0 */
#घोषणा CMPLT_HDR_CMPLT_OFF		0
#घोषणा CMPLT_HDR_CMPLT_MSK		(0x3 << CMPLT_HDR_CMPLT_OFF)
#घोषणा CMPLT_HDR_ERROR_PHASE_OFF   2
#घोषणा CMPLT_HDR_ERROR_PHASE_MSK   (0xff << CMPLT_HDR_ERROR_PHASE_OFF)
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
/* dw3 */
#घोषणा CMPLT_HDR_IO_IN_TARGET_OFF	17
#घोषणा CMPLT_HDR_IO_IN_TARGET_MSK	(0x1 << CMPLT_HDR_IO_IN_TARGET_OFF)

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
#घोषणा ITCT_HDR_AWT_CONTINUE_OFF	25
#घोषणा ITCT_HDR_PORT_ID_OFF		28
#घोषणा ITCT_HDR_PORT_ID_MSK		(0xf << ITCT_HDR_PORT_ID_OFF)
/* qw2 */
#घोषणा ITCT_HDR_INLT_OFF		0
#घोषणा ITCT_HDR_INLT_MSK		(0xffffULL << ITCT_HDR_INLT_OFF)
#घोषणा ITCT_HDR_RTOLT_OFF		48
#घोषणा ITCT_HDR_RTOLT_MSK		(0xffffULL << ITCT_HDR_RTOLT_OFF)

काष्ठा hisi_sas_protect_iu_v3_hw अणु
	u32 dw0;
	u32 lbrtcv;
	u32 lbrtgv;
	u32 dw3;
	u32 dw4;
	u32 dw5;
	u32 rsv;
पूर्ण;

काष्ठा hisi_sas_complete_v3_hdr अणु
	__le32 dw0;
	__le32 dw1;
	__le32 act;
	__le32 dw3;
पूर्ण;

काष्ठा hisi_sas_err_record_v3 अणु
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

#घोषणा RX_DATA_LEN_UNDERFLOW_OFF	6
#घोषणा RX_DATA_LEN_UNDERFLOW_MSK	(1 << RX_DATA_LEN_UNDERFLOW_OFF)

#घोषणा HISI_SAS_COMMAND_ENTRIES_V3_HW 4096
#घोषणा HISI_SAS_MSI_COUNT_V3_HW 32

#घोषणा सूची_NO_DATA 0
#घोषणा सूची_TO_INI 1
#घोषणा सूची_TO_DEVICE 2
#घोषणा सूची_RESERVED 3

#घोषणा FIS_CMD_IS_UNCONSTRAINED(fis) \
	((fis.command == ATA_CMD_READ_LOG_EXT) || \
	(fis.command == ATA_CMD_READ_LOG_DMA_EXT) || \
	((fis.command == ATA_CMD_DEV_RESET) && \
	((fis.control & ATA_SRST) != 0)))

#घोषणा T10_INSRT_EN_OFF    0
#घोषणा T10_INSRT_EN_MSK    (1 << T10_INSRT_EN_OFF)
#घोषणा T10_RMV_EN_OFF	    1
#घोषणा T10_RMV_EN_MSK	    (1 << T10_RMV_EN_OFF)
#घोषणा T10_RPLC_EN_OFF	    2
#घोषणा T10_RPLC_EN_MSK	    (1 << T10_RPLC_EN_OFF)
#घोषणा T10_CHK_EN_OFF	    3
#घोषणा T10_CHK_EN_MSK	    (1 << T10_CHK_EN_OFF)
#घोषणा INCR_LBRT_OFF	    5
#घोषणा INCR_LBRT_MSK	    (1 << INCR_LBRT_OFF)
#घोषणा USR_DATA_BLOCK_SZ_OFF	20
#घोषणा USR_DATA_BLOCK_SZ_MSK	(0x3 << USR_DATA_BLOCK_SZ_OFF)
#घोषणा T10_CHK_MSK_OFF	    16
#घोषणा T10_CHK_REF_TAG_MSK (0xf0 << T10_CHK_MSK_OFF)
#घोषणा T10_CHK_APP_TAG_MSK (0xc << T10_CHK_MSK_OFF)

#घोषणा BASE_VECTORS_V3_HW  16
#घोषणा MIN_AFFINE_VECTORS_V3_HW  (BASE_VECTORS_V3_HW + 1)

#घोषणा CHNL_INT_STS_MSK	0xeeeeeeee
#घोषणा CHNL_INT_STS_PHY_MSK	0xe
#घोषणा CHNL_INT_STS_INT0_MSK BIT(1)
#घोषणा CHNL_INT_STS_INT1_MSK BIT(2)
#घोषणा CHNL_INT_STS_INT2_MSK BIT(3)
#घोषणा CHNL_WIDTH 4

क्रमागत अणु
	DSM_FUNC_ERR_HANDLE_MSI = 0,
पूर्ण;

अटल bool hisi_sas_पूर्णांकr_conv;
MODULE_PARM_DESC(पूर्णांकr_conv, "interrupt converge enable (0-1)");

/* permit overriding the host protection capabilities mask (EEDP/T10 PI) */
अटल पूर्णांक prot_mask;
module_param(prot_mask, पूर्णांक, 0);
MODULE_PARM_DESC(prot_mask, " host protection capabilities mask, def=0x0 ");

अटल व्योम debugfs_work_handler_v3_hw(काष्ठा work_काष्ठा *work);
अटल व्योम debugfs_snapshot_regs_v3_hw(काष्ठा hisi_hba *hisi_hba);

अटल u32 hisi_sas_पढ़ो32(काष्ठा hisi_hba *hisi_hba, u32 off)
अणु
	व्योम __iomem *regs = hisi_hba->regs + off;

	वापस पढ़ोl(regs);
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

#घोषणा hisi_sas_पढ़ो32_poll_समयout(off, val, cond, delay_us,		\
				     समयout_us)			\
(अणु									\
	व्योम __iomem *regs = hisi_hba->regs + off;			\
	पढ़ोl_poll_समयout(regs, val, cond, delay_us, समयout_us);	\
पूर्ण)

#घोषणा hisi_sas_पढ़ो32_poll_समयout_atomic(off, val, cond, delay_us,	\
					    समयout_us)			\
(अणु									\
	व्योम __iomem *regs = hisi_hba->regs + off;			\
	पढ़ोl_poll_समयout_atomic(regs, val, cond, delay_us, समयout_us);\
पूर्ण)

अटल व्योम init_reg_v3_hw(काष्ठा hisi_hba *hisi_hba)
अणु
	पूर्णांक i, j;

	/* Global रेजिस्टरs init */
	hisi_sas_ग_लिखो32(hisi_hba, DLVRY_QUEUE_ENABLE,
			 (u32)((1ULL << hisi_hba->queue_count) - 1));
	hisi_sas_ग_लिखो32(hisi_hba, SAS_AXI_USER3, 0);
	hisi_sas_ग_लिखो32(hisi_hba, CFG_MAX_TAG, 0xfff0400);
	hisi_sas_ग_लिखो32(hisi_hba, HGC_SAS_TXFAIL_RETRY_CTRL, 0x108);
	hisi_sas_ग_लिखो32(hisi_hba, CFG_AGING_TIME, 0x1);
	hisi_sas_ग_लिखो32(hisi_hba, INT_COAL_EN, 0x1);
	hisi_sas_ग_लिखो32(hisi_hba, OQ_INT_COAL_TIME, 0x1);
	hisi_sas_ग_लिखो32(hisi_hba, OQ_INT_COAL_CNT, 0x1);
	hisi_sas_ग_लिखो32(hisi_hba, CQ_INT_CONVERGE_EN,
			 hisi_sas_पूर्णांकr_conv);
	hisi_sas_ग_लिखो32(hisi_hba, OQ_INT_SRC, 0xffff);
	hisi_sas_ग_लिखो32(hisi_hba, ENT_INT_SRC1, 0xffffffff);
	hisi_sas_ग_लिखो32(hisi_hba, ENT_INT_SRC2, 0xffffffff);
	hisi_sas_ग_लिखो32(hisi_hba, ENT_INT_SRC3, 0xffffffff);
	hisi_sas_ग_लिखो32(hisi_hba, ENT_INT_SRC_MSK1, 0xfefefefe);
	hisi_sas_ग_लिखो32(hisi_hba, ENT_INT_SRC_MSK2, 0xfefefefe);
	hisi_sas_ग_लिखो32(hisi_hba, ENT_INT_SRC_MSK3, 0xffc220ff);
	hisi_sas_ग_लिखो32(hisi_hba, CHNL_PHYUPDOWN_INT_MSK, 0x0);
	hisi_sas_ग_लिखो32(hisi_hba, CHNL_ENT_INT_MSK, 0x0);
	hisi_sas_ग_लिखो32(hisi_hba, HGC_COM_INT_MSK, 0x0);
	hisi_sas_ग_लिखो32(hisi_hba, SAS_ECC_INTR_MSK, 0x155555);
	hisi_sas_ग_लिखो32(hisi_hba, AWQOS_AWCACHE_CFG, 0xf0f0);
	hisi_sas_ग_लिखो32(hisi_hba, ARQOS_ARCACHE_CFG, 0xf0f0);
	क्रम (i = 0; i < hisi_hba->queue_count; i++)
		hisi_sas_ग_लिखो32(hisi_hba, OQ0_INT_SRC_MSK + 0x4 * i, 0);

	hisi_sas_ग_लिखो32(hisi_hba, HYPER_STREAM_ID_EN_CFG, 1);

	क्रम (i = 0; i < hisi_hba->n_phy; i++) अणु
		क्रमागत sas_linkrate max;
		काष्ठा hisi_sas_phy *phy = &hisi_hba->phy[i];
		काष्ठा asd_sas_phy *sas_phy = &phy->sas_phy;
		u32 prog_phy_link_rate = hisi_sas_phy_पढ़ो32(hisi_hba, i,
							   PROG_PHY_LINK_RATE);

		prog_phy_link_rate &= ~CFG_PROG_PHY_LINK_RATE_MSK;
		अगर (!sas_phy->phy || (sas_phy->phy->maximum_linkrate <
				SAS_LINK_RATE_1_5_GBPS))
			max = SAS_LINK_RATE_12_0_GBPS;
		अन्यथा
			max = sas_phy->phy->maximum_linkrate;
		prog_phy_link_rate |= hisi_sas_get_prog_phy_linkrate_mask(max);
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, PROG_PHY_LINK_RATE,
			prog_phy_link_rate);
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, SERDES_CFG, 0xffc00);
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, SAS_RX_TRAIN_TIMER, 0x13e80);
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, CHL_INT0, 0xffffffff);
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, CHL_INT1, 0xffffffff);
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, CHL_INT2, 0xffffffff);
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, RXOP_CHECK_CFG_H, 0x1000);
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, CHL_INT1_MSK, 0xf2057fff);
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, CHL_INT2_MSK, 0xffffbfe);
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, PHY_CTRL_RDY_MSK, 0x0);
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, PHYCTRL_NOT_RDY_MSK, 0x0);
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, PHYCTRL_DWS_RESET_MSK, 0x0);
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, PHYCTRL_PHY_ENA_MSK, 0x0);
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, SL_RX_BCAST_CHK_MSK, 0x0);
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, PHYCTRL_OOB_RESTART_MSK, 0x1);
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, STP_LINK_TIMER, 0x7f7a120);
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, CON_CFG_DRIVER, 0x2a0a01);
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, SAS_SSP_CON_TIMER_CFG, 0x32);
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, SAS_EC_INT_COAL_TIME,
				     0x30f4240);
		/* used क्रम 12G negotiate */
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, COARSETUNE_TIME, 0x1e);
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, AIP_LIMIT, 0x2ffff);

		/* get शेष FFE configuration क्रम BIST */
		क्रम (j = 0; j < FFE_CFG_MAX; j++) अणु
			u32 val = hisi_sas_phy_पढ़ो32(hisi_hba, i,
						      TXDEEMPH_G1 + (j * 0x4));
			hisi_hba->debugfs_bist_ffe[i][j] = val;
		पूर्ण
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

	/* RAS रेजिस्टरs init */
	hisi_sas_ग_लिखो32(hisi_hba, SAS_RAS_INTR0_MASK, 0x0);
	hisi_sas_ग_लिखो32(hisi_hba, SAS_RAS_INTR1_MASK, 0x0);
	hisi_sas_ग_लिखो32(hisi_hba, SAS_RAS_INTR2_MASK, 0x0);
	hisi_sas_ग_लिखो32(hisi_hba, CFG_SAS_RAS_INTR_MASK, 0x0);

	/* LED रेजिस्टरs init */
	hisi_sas_ग_लिखो32(hisi_hba, SAS_CFG_DRIVE_VLD, 0x80000ff);
	hisi_sas_ग_लिखो32(hisi_hba, SAS_GPIO_TX_0_1, 0x80808080);
	hisi_sas_ग_लिखो32(hisi_hba, SAS_GPIO_TX_0_1 + 0x4, 0x80808080);
	/* Configure blink generator rate A to 1Hz and B to 4Hz */
	hisi_sas_ग_लिखो32(hisi_hba, SAS_GPIO_CFG_1, 0x121700);
	hisi_sas_ग_लिखो32(hisi_hba, SAS_GPIO_CFG_0, 0x800000);
पूर्ण

अटल व्योम config_phy_opt_mode_v3_hw(काष्ठा hisi_hba *hisi_hba, पूर्णांक phy_no)
अणु
	u32 cfg = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no, PHY_CFG);

	cfg &= ~PHY_CFG_DC_OPT_MSK;
	cfg |= 1 << PHY_CFG_DC_OPT_OFF;
	hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, PHY_CFG, cfg);
पूर्ण

अटल व्योम config_id_frame_v3_hw(काष्ठा hisi_hba *hisi_hba, पूर्णांक phy_no)
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

अटल व्योम setup_itct_v3_hw(काष्ठा hisi_hba *hisi_hba,
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
		(0xfa << ITCT_HDR_SMP_TIMEOUT_OFF) |
		(1 << ITCT_HDR_AWT_CONTINUE_OFF) |
		(port->id << ITCT_HDR_PORT_ID_OFF));
	itct->qw0 = cpu_to_le64(qw0);

	/* qw1 */
	स_नकल(&sas_addr, device->sas_addr, SAS_ADDR_SIZE);
	itct->sas_addr = cpu_to_le64(__swab64(sas_addr));

	/* qw2 */
	अगर (!dev_is_sata(device))
		itct->qw2 = cpu_to_le64((5000ULL << ITCT_HDR_INLT_OFF) |
					(0x1ULL << ITCT_HDR_RTOLT_OFF));
पूर्ण

अटल पूर्णांक clear_itct_v3_hw(काष्ठा hisi_hba *hisi_hba,
			    काष्ठा hisi_sas_device *sas_dev)
अणु
	DECLARE_COMPLETION_ONSTACK(completion);
	u64 dev_id = sas_dev->device_id;
	काष्ठा hisi_sas_itct *itct = &hisi_hba->itct[dev_id];
	u32 reg_val = hisi_sas_पढ़ो32(hisi_hba, ENT_INT_SRC3);
	काष्ठा device *dev = hisi_hba->dev;

	sas_dev->completion = &completion;

	/* clear the itct पूर्णांकerrupt state */
	अगर (ENT_INT_SRC3_ITC_INT_MSK & reg_val)
		hisi_sas_ग_लिखो32(hisi_hba, ENT_INT_SRC3,
				 ENT_INT_SRC3_ITC_INT_MSK);

	/* clear the itct table */
	reg_val = ITCT_CLR_EN_MSK | (dev_id & ITCT_DEV_MSK);
	hisi_sas_ग_लिखो32(hisi_hba, ITCT_CLR, reg_val);

	अगर (!रुको_क्रम_completion_समयout(sas_dev->completion,
					 CLEAR_ITCT_TIMEOUT * HZ)) अणु
		dev_warn(dev, "failed to clear ITCT\n");
		वापस -ETIMEDOUT;
	पूर्ण

	स_रखो(itct, 0, माप(काष्ठा hisi_sas_itct));
	वापस 0;
पूर्ण

अटल व्योम dereg_device_v3_hw(काष्ठा hisi_hba *hisi_hba,
				काष्ठा करोमुख्य_device *device)
अणु
	काष्ठा hisi_sas_slot *slot, *slot2;
	काष्ठा hisi_sas_device *sas_dev = device->lldd_dev;
	u32 cfg_abt_set_query_iptt;

	cfg_abt_set_query_iptt = hisi_sas_पढ़ो32(hisi_hba,
		CFG_ABT_SET_QUERY_IPTT);
	list_क्रम_each_entry_safe(slot, slot2, &sas_dev->list, entry) अणु
		cfg_abt_set_query_iptt &= ~CFG_SET_ABORTED_IPTT_MSK;
		cfg_abt_set_query_iptt |= (1 << CFG_SET_ABORTED_EN_OFF) |
			(slot->idx << CFG_SET_ABORTED_IPTT_OFF);
		hisi_sas_ग_लिखो32(hisi_hba, CFG_ABT_SET_QUERY_IPTT,
			cfg_abt_set_query_iptt);
	पूर्ण
	cfg_abt_set_query_iptt &= ~(1 << CFG_SET_ABORTED_EN_OFF);
	hisi_sas_ग_लिखो32(hisi_hba, CFG_ABT_SET_QUERY_IPTT,
		cfg_abt_set_query_iptt);
	hisi_sas_ग_लिखो32(hisi_hba, CFG_ABT_SET_IPTT_DONE,
					1 << CFG_ABT_SET_IPTT_DONE_OFF);
पूर्ण

अटल पूर्णांक reset_hw_v3_hw(काष्ठा hisi_hba *hisi_hba)
अणु
	काष्ठा device *dev = hisi_hba->dev;
	पूर्णांक ret;
	u32 val;

	hisi_sas_ग_लिखो32(hisi_hba, DLVRY_QUEUE_ENABLE, 0);

	/* Disable all of the PHYs */
	hisi_sas_stop_phys(hisi_hba);
	udelay(50);

	/* Ensure axi bus idle */
	ret = hisi_sas_पढ़ो32_poll_समयout(AXI_CFG, val, !val,
					   20000, 1000000);
	अगर (ret) अणु
		dev_err(dev, "axi bus is not idle, ret = %d!\n", ret);
		वापस -EIO;
	पूर्ण

	अगर (ACPI_HANDLE(dev)) अणु
		acpi_status s;

		s = acpi_evaluate_object(ACPI_HANDLE(dev), "_RST", शून्य, शून्य);
		अगर (ACPI_FAILURE(s)) अणु
			dev_err(dev, "Reset failed\n");
			वापस -EIO;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_err(dev, "no reset method!\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hw_init_v3_hw(काष्ठा hisi_hba *hisi_hba)
अणु
	काष्ठा device *dev = hisi_hba->dev;
	काष्ठा acpi_device *acpi_dev;
	जोड़ acpi_object *obj;
	guid_t guid;
	पूर्णांक rc;

	rc = reset_hw_v3_hw(hisi_hba);
	अगर (rc) अणु
		dev_err(dev, "hisi_sas_reset_hw failed, rc=%d\n", rc);
		वापस rc;
	पूर्ण

	msleep(100);
	init_reg_v3_hw(hisi_hba);

	अगर (guid_parse("D5918B4B-37AE-4E10-A99F-E5E8A6EF4C1F", &guid)) अणु
		dev_err(dev, "Parse GUID failed\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * This DSM handles some hardware-related configurations:
	 * 1. Switch over to MSI error handling in kernel
	 * 2. BIOS *may* reset some रेजिस्टर values through this method
	 */
	obj = acpi_evaluate_dsm(ACPI_HANDLE(dev), &guid, 0,
				DSM_FUNC_ERR_HANDLE_MSI, शून्य);
	अगर (!obj)
		dev_warn(dev, "can not find DSM method, ignore\n");
	अन्यथा
		ACPI_FREE(obj);

	acpi_dev = ACPI_COMPANION(dev);
	अगर (!acpi_device_घातer_manageable(acpi_dev))
		dev_notice(dev, "neither _PS0 nor _PR0 is defined\n");
	वापस 0;
पूर्ण

अटल व्योम enable_phy_v3_hw(काष्ठा hisi_hba *hisi_hba, पूर्णांक phy_no)
अणु
	u32 cfg = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no, PHY_CFG);

	cfg |= PHY_CFG_ENA_MSK;
	cfg &= ~PHY_CFG_PHY_RST_MSK;
	hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, PHY_CFG, cfg);
पूर्ण

अटल व्योम disable_phy_v3_hw(काष्ठा hisi_hba *hisi_hba, पूर्णांक phy_no)
अणु
	u32 cfg = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no, PHY_CFG);
	u32 irq_msk = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no, CHL_INT2_MSK);
	अटल स्थिर u32 msk = BIT(CHL_INT2_RX_DISP_ERR_OFF) |
			       BIT(CHL_INT2_RX_CODE_ERR_OFF) |
			       BIT(CHL_INT2_RX_INVLD_DW_OFF);
	u32 state;

	hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, CHL_INT2_MSK, msk | irq_msk);

	cfg &= ~PHY_CFG_ENA_MSK;
	hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, PHY_CFG, cfg);

	mdelay(50);

	state = hisi_sas_पढ़ो32(hisi_hba, PHY_STATE);
	अगर (state & BIT(phy_no)) अणु
		cfg |= PHY_CFG_PHY_RST_MSK;
		hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, PHY_CFG, cfg);
	पूर्ण

	udelay(1);

	hisi_sas_phy_पढ़ो32(hisi_hba, phy_no, ERR_CNT_INVLD_DW);
	hisi_sas_phy_पढ़ो32(hisi_hba, phy_no, ERR_CNT_DISP_ERR);
	hisi_sas_phy_पढ़ो32(hisi_hba, phy_no, ERR_CNT_CODE_ERR);

	hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, CHL_INT2, msk);
	hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, CHL_INT2_MSK, irq_msk);
पूर्ण

अटल व्योम start_phy_v3_hw(काष्ठा hisi_hba *hisi_hba, पूर्णांक phy_no)
अणु
	config_id_frame_v3_hw(hisi_hba, phy_no);
	config_phy_opt_mode_v3_hw(hisi_hba, phy_no);
	enable_phy_v3_hw(hisi_hba, phy_no);
पूर्ण

अटल व्योम phy_hard_reset_v3_hw(काष्ठा hisi_hba *hisi_hba, पूर्णांक phy_no)
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

अटल क्रमागत sas_linkrate phy_get_max_linkrate_v3_hw(व्योम)
अणु
	वापस SAS_LINK_RATE_12_0_GBPS;
पूर्ण

अटल व्योम phys_init_v3_hw(काष्ठा hisi_hba *hisi_hba)
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

अटल व्योम sl_notअगरy_ssp_v3_hw(काष्ठा hisi_hba *hisi_hba, पूर्णांक phy_no)
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

अटल पूर्णांक get_wideport_biपंचांगap_v3_hw(काष्ठा hisi_hba *hisi_hba, पूर्णांक port_id)
अणु
	पूर्णांक i, biपंचांगap = 0;
	u32 phy_port_num_ma = hisi_sas_पढ़ो32(hisi_hba, PHY_PORT_NUM_MA);
	u32 phy_state = hisi_sas_पढ़ो32(hisi_hba, PHY_STATE);

	क्रम (i = 0; i < hisi_hba->n_phy; i++)
		अगर (phy_state & BIT(i))
			अगर (((phy_port_num_ma >> (i * 4)) & 0xf) == port_id)
				biपंचांगap |= BIT(i);

	वापस biपंचांगap;
पूर्ण

अटल व्योम start_delivery_v3_hw(काष्ठा hisi_sas_dq *dq)
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

अटल व्योम prep_prd_sge_v3_hw(काष्ठा hisi_hba *hisi_hba,
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

	hdr->sg_len |= cpu_to_le32(n_elem << CMD_HDR_DATA_SGL_LEN_OFF);
पूर्ण

अटल व्योम prep_prd_sge_dअगर_v3_hw(काष्ठा hisi_hba *hisi_hba,
				   काष्ठा hisi_sas_slot *slot,
				   काष्ठा hisi_sas_cmd_hdr *hdr,
				   काष्ठा scatterlist *scatter,
				   पूर्णांक n_elem)
अणु
	काष्ठा hisi_sas_sge_dअगर_page *sge_dअगर_page;
	काष्ठा scatterlist *sg;
	पूर्णांक i;

	sge_dअगर_page = hisi_sas_sge_dअगर_addr_mem(slot);

	क्रम_each_sg(scatter, sg, n_elem, i) अणु
		काष्ठा hisi_sas_sge *entry = &sge_dअगर_page->sge[i];

		entry->addr = cpu_to_le64(sg_dma_address(sg));
		entry->page_ctrl_0 = 0;
		entry->page_ctrl_1 = 0;
		entry->data_len = cpu_to_le32(sg_dma_len(sg));
		entry->data_off = 0;
	पूर्ण

	hdr->dअगर_prd_table_addr =
		cpu_to_le64(hisi_sas_sge_dअगर_addr_dma(slot));

	hdr->sg_len |= cpu_to_le32(n_elem << CMD_HDR_DIF_SGL_LEN_OFF);
पूर्ण

अटल u32 get_prot_chk_msk_v3_hw(काष्ठा scsi_cmnd *scsi_cmnd)
अणु
	अचिन्हित अक्षर prot_flags = scsi_cmnd->prot_flags;

	अगर (prot_flags & SCSI_PROT_REF_CHECK)
		वापस T10_CHK_APP_TAG_MSK;
	वापस T10_CHK_REF_TAG_MSK | T10_CHK_APP_TAG_MSK;
पूर्ण

अटल व्योम fill_prot_v3_hw(काष्ठा scsi_cmnd *scsi_cmnd,
			    काष्ठा hisi_sas_protect_iu_v3_hw *prot)
अणु
	अचिन्हित अक्षर prot_op = scsi_get_prot_op(scsi_cmnd);
	अचिन्हित पूर्णांक पूर्णांकerval = scsi_prot_पूर्णांकerval(scsi_cmnd);
	u32 lbrt_chk_val = t10_pi_ref_tag(scsi_cmnd->request);

	चयन (prot_op) अणु
	हाल SCSI_PROT_READ_INSERT:
		prot->dw0 |= T10_INSRT_EN_MSK;
		prot->lbrtgv = lbrt_chk_val;
		अवरोध;
	हाल SCSI_PROT_READ_STRIP:
		prot->dw0 |= (T10_RMV_EN_MSK | T10_CHK_EN_MSK);
		prot->lbrtcv = lbrt_chk_val;
		prot->dw4 |= get_prot_chk_msk_v3_hw(scsi_cmnd);
		अवरोध;
	हाल SCSI_PROT_READ_PASS:
		prot->dw0 |= T10_CHK_EN_MSK;
		prot->lbrtcv = lbrt_chk_val;
		prot->dw4 |= get_prot_chk_msk_v3_hw(scsi_cmnd);
		अवरोध;
	हाल SCSI_PROT_WRITE_INSERT:
		prot->dw0 |= T10_INSRT_EN_MSK;
		prot->lbrtgv = lbrt_chk_val;
		अवरोध;
	हाल SCSI_PROT_WRITE_STRIP:
		prot->dw0 |= (T10_RMV_EN_MSK | T10_CHK_EN_MSK);
		prot->lbrtcv = lbrt_chk_val;
		अवरोध;
	हाल SCSI_PROT_WRITE_PASS:
		prot->dw0 |= T10_CHK_EN_MSK;
		prot->lbrtcv = lbrt_chk_val;
		prot->dw4 |= get_prot_chk_msk_v3_hw(scsi_cmnd);
		अवरोध;
	शेष:
		WARN(1, "prot_op(0x%x) is not valid\n", prot_op);
		अवरोध;
	पूर्ण

	चयन (पूर्णांकerval) अणु
	हाल 512:
		अवरोध;
	हाल 4096:
		prot->dw0 |= (0x1 << USR_DATA_BLOCK_SZ_OFF);
		अवरोध;
	हाल 520:
		prot->dw0 |= (0x2 << USR_DATA_BLOCK_SZ_OFF);
		अवरोध;
	शेष:
		WARN(1, "protection interval (0x%x) invalid\n",
		     पूर्णांकerval);
		अवरोध;
	पूर्ण

	prot->dw0 |= INCR_LBRT_MSK;
पूर्ण

अटल व्योम prep_ssp_v3_hw(काष्ठा hisi_hba *hisi_hba,
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
	अचिन्हित अक्षर prot_op;
	u8 *buf_cmd;
	u32 dw1 = 0, dw2 = 0, len = 0;

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
		prot_op = scsi_get_prot_op(scsi_cmnd);
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

	dw2 = (((माप(काष्ठा ssp_command_iu) + माप(काष्ठा ssp_frame_hdr)
	      + 3) / 4) << CMD_HDR_CFL_OFF) |
	      ((HISI_SAS_MAX_SSP_RESP_SZ / 4) << CMD_HDR_MRFL_OFF) |
	      (2 << CMD_HDR_SG_MOD_OFF);
	hdr->dw2 = cpu_to_le32(dw2);
	hdr->transfer_tags = cpu_to_le32(slot->idx);

	अगर (has_data) अणु
		prep_prd_sge_v3_hw(hisi_hba, slot, hdr, task->scatter,
				   slot->n_elem);

		अगर (scsi_prot_sg_count(scsi_cmnd))
			prep_prd_sge_dअगर_v3_hw(hisi_hba, slot, hdr,
					       scsi_prot_sglist(scsi_cmnd),
					       slot->n_elem_dअगर);
	पूर्ण

	hdr->cmd_table_addr = cpu_to_le64(hisi_sas_cmd_hdr_addr_dma(slot));
	hdr->sts_buffer_addr = cpu_to_le64(hisi_sas_status_buf_addr_dma(slot));

	buf_cmd = hisi_sas_cmd_hdr_addr_mem(slot) +
		माप(काष्ठा ssp_frame_hdr);

	स_नकल(buf_cmd, &task->ssp_task.LUN, 8);
	अगर (!पंचांगf) अणु
		buf_cmd[9] = ssp_task->task_attr | (ssp_task->task_prio << 3);
		स_नकल(buf_cmd + 12, scsi_cmnd->cmnd, scsi_cmnd->cmd_len);
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

	अगर (has_data && (prot_op != SCSI_PROT_NORMAL)) अणु
		काष्ठा hisi_sas_protect_iu_v3_hw prot;
		u8 *buf_cmd_prot;

		hdr->dw7 |= cpu_to_le32(1 << CMD_HDR_ADDR_MODE_SEL_OFF);
		dw1 |= CMD_HDR_PIR_MSK;
		buf_cmd_prot = hisi_sas_cmd_hdr_addr_mem(slot) +
			       माप(काष्ठा ssp_frame_hdr) +
			       माप(काष्ठा ssp_command_iu);

		स_रखो(&prot, 0, माप(काष्ठा hisi_sas_protect_iu_v3_hw));
		fill_prot_v3_hw(scsi_cmnd, &prot);
		स_नकल(buf_cmd_prot, &prot,
		       माप(काष्ठा hisi_sas_protect_iu_v3_hw));
		/*
		 * For READ, we need length of info पढ़ो to memory, जबतक क्रम
		 * WRITE we need length of data written to the disk.
		 */
		अगर (prot_op == SCSI_PROT_WRITE_INSERT ||
		    prot_op == SCSI_PROT_READ_INSERT ||
		    prot_op == SCSI_PROT_WRITE_PASS ||
		    prot_op == SCSI_PROT_READ_PASS) अणु
			अचिन्हित पूर्णांक पूर्णांकerval = scsi_prot_पूर्णांकerval(scsi_cmnd);
			अचिन्हित पूर्णांक ilog2_पूर्णांकerval = ilog2(पूर्णांकerval);

			len = (task->total_xfer_len >> ilog2_पूर्णांकerval) * 8;
		पूर्ण
	पूर्ण

	hdr->dw1 = cpu_to_le32(dw1);

	hdr->data_transfer_len = cpu_to_le32(task->total_xfer_len + len);
पूर्ण

अटल व्योम prep_smp_v3_hw(काष्ठा hisi_hba *hisi_hba,
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
	req_len = sg_dma_len(sg_req);
	req_dma_addr = sg_dma_address(sg_req);

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

अटल व्योम prep_ata_v3_hw(काष्ठा hisi_hba *hisi_hba,
			  काष्ठा hisi_sas_slot *slot)
अणु
	काष्ठा sas_task *task = slot->task;
	काष्ठा करोमुख्य_device *device = task->dev;
	काष्ठा करोमुख्य_device *parent_dev = device->parent;
	काष्ठा hisi_sas_device *sas_dev = device->lldd_dev;
	काष्ठा hisi_sas_cmd_hdr *hdr = slot->cmd_hdr;
	काष्ठा asd_sas_port *sas_port = device->port;
	काष्ठा hisi_sas_port *port = to_hisi_sas_port(sas_port);
	u8 *buf_cmd;
	पूर्णांक has_data = 0, hdr_tag = 0;
	u32 dw1 = 0, dw2 = 0;

	hdr->dw0 = cpu_to_le32(port->id << CMD_HDR_PORT_OFF);
	अगर (parent_dev && dev_is_expander(parent_dev->dev_type))
		hdr->dw0 |= cpu_to_le32(3 << CMD_HDR_CMD_OFF);
	अन्यथा
		hdr->dw0 |= cpu_to_le32(4U << CMD_HDR_CMD_OFF);

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

	अगर (FIS_CMD_IS_UNCONSTRAINED(task->ata_task.fis))
		dw1 |= 1 << CMD_HDR_UNCON_CMD_OFF;

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
		prep_prd_sge_v3_hw(hisi_hba, slot, hdr, task->scatter,
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

अटल व्योम prep_पात_v3_hw(काष्ठा hisi_hba *hisi_hba,
		काष्ठा hisi_sas_slot *slot,
		पूर्णांक device_id, पूर्णांक पात_flag, पूर्णांक tag_to_पात)
अणु
	काष्ठा sas_task *task = slot->task;
	काष्ठा करोमुख्य_device *dev = task->dev;
	काष्ठा hisi_sas_cmd_hdr *hdr = slot->cmd_hdr;
	काष्ठा hisi_sas_port *port = slot->port;

	/* dw0 */
	hdr->dw0 = cpu_to_le32((5U << CMD_HDR_CMD_OFF) | /*पात*/
			       (port->id << CMD_HDR_PORT_OFF) |
				   (dev_is_sata(dev)
					<< CMD_HDR_ABORT_DEVICE_TYPE_OFF) |
					(पात_flag
					 << CMD_HDR_ABORT_FLAG_OFF));

	/* dw1 */
	hdr->dw1 = cpu_to_le32(device_id
			<< CMD_HDR_DEV_ID_OFF);

	/* dw7 */
	hdr->dw7 = cpu_to_le32(tag_to_पात << CMD_HDR_ABORT_IPTT_OFF);
	hdr->transfer_tags = cpu_to_le32(slot->idx);
पूर्ण

अटल irqवापस_t phy_up_v3_hw(पूर्णांक phy_no, काष्ठा hisi_hba *hisi_hba)
अणु
	पूर्णांक i;
	irqवापस_t res;
	u32 context, port_id, link_rate;
	काष्ठा hisi_sas_phy *phy = &hisi_hba->phy[phy_no];
	काष्ठा asd_sas_phy *sas_phy = &phy->sas_phy;
	काष्ठा device *dev = hisi_hba->dev;
	अचिन्हित दीर्घ flags;

	del_समयr(&phy->समयr);
	hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, PHYCTRL_PHY_ENA_MSK, 1);

	port_id = hisi_sas_पढ़ो32(hisi_hba, PHY_PORT_NUM_MA);
	port_id = (port_id >> (4 * phy_no)) & 0xf;
	link_rate = hisi_sas_पढ़ो32(hisi_hba, PHY_CONN_RATE);
	link_rate = (link_rate >> (phy_no * 4)) & 0xf;

	अगर (port_id == 0xf) अणु
		dev_err(dev, "phyup: phy%d invalid portid\n", phy_no);
		res = IRQ_NONE;
		जाओ end;
	पूर्ण
	sas_phy->linkrate = link_rate;
	phy->phy_type &= ~(PORT_TYPE_SAS | PORT_TYPE_SATA);

	/* Check क्रम SATA dev */
	context = hisi_sas_पढ़ो32(hisi_hba, PHY_CONTEXT);
	अगर (context & (1 << phy_no)) अणु
		काष्ठा hisi_sas_initial_fis *initial_fis;
		काष्ठा dev_to_host_fis *fis;
		u8 attached_sas_addr[SAS_ADDR_SIZE] = अणु0पूर्ण;
		काष्ठा Scsi_Host *shost = hisi_hba->shost;

		dev_info(dev, "phyup: phy%d link_rate=%d(sata)\n", phy_no, link_rate);
		initial_fis = &hisi_hba->initial_fis[phy_no];
		fis = &initial_fis->fis;

		/* check ERR bit of Status Register */
		अगर (fis->status & ATA_ERR) अणु
			dev_warn(dev, "sata int: phy%d FIS status: 0x%x\n",
				 phy_no, fis->status);
			hisi_sas_notअगरy_phy_event(phy, HISI_PHYE_LINK_RESET);
			res = IRQ_NONE;
			जाओ end;
		पूर्ण

		sas_phy->oob_mode = SATA_OOB_MODE;
		attached_sas_addr[0] = 0x50;
		attached_sas_addr[6] = shost->host_no;
		attached_sas_addr[7] = phy_no;
		स_नकल(sas_phy->attached_sas_addr,
		       attached_sas_addr,
		       SAS_ADDR_SIZE);
		स_नकल(sas_phy->frame_rcvd, fis,
		       माप(काष्ठा dev_to_host_fis));
		phy->phy_type |= PORT_TYPE_SATA;
		phy->identअगरy.device_type = SAS_SATA_DEV;
		phy->frame_rcvd_size = माप(काष्ठा dev_to_host_fis);
		phy->identअगरy.target_port_protocols = SAS_PROTOCOL_SATA;
	पूर्ण अन्यथा अणु
		u32 *frame_rcvd = (u32 *)sas_phy->frame_rcvd;
		काष्ठा sas_identअगरy_frame *id =
			(काष्ठा sas_identअगरy_frame *)frame_rcvd;

		dev_info(dev, "phyup: phy%d link_rate=%d\n", phy_no, link_rate);
		क्रम (i = 0; i < 6; i++) अणु
			u32 idaf = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no,
					       RX_IDAF_DWORD0 + (i * 4));
			frame_rcvd[i] = __swab32(idaf);
		पूर्ण
		sas_phy->oob_mode = SAS_OOB_MODE;
		स_नकल(sas_phy->attached_sas_addr,
		       &id->sas_addr,
		       SAS_ADDR_SIZE);
		phy->phy_type |= PORT_TYPE_SAS;
		phy->identअगरy.device_type = id->dev_type;
		phy->frame_rcvd_size = माप(काष्ठा sas_identअगरy_frame);
		अगर (phy->identअगरy.device_type == SAS_END_DEVICE)
			phy->identअगरy.target_port_protocols =
				SAS_PROTOCOL_SSP;
		अन्यथा अगर (phy->identअगरy.device_type != SAS_PHY_UNUSED)
			phy->identअगरy.target_port_protocols =
				SAS_PROTOCOL_SMP;
	पूर्ण

	phy->port_id = port_id;
	phy->phy_attached = 1;
	hisi_sas_notअगरy_phy_event(phy, HISI_PHYE_PHY_UP);
	res = IRQ_HANDLED;
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

अटल irqवापस_t phy_करोwn_v3_hw(पूर्णांक phy_no, काष्ठा hisi_hba *hisi_hba)
अणु
	काष्ठा hisi_sas_phy *phy = &hisi_hba->phy[phy_no];
	u32 phy_state, sl_ctrl, txid_स्वतः;
	काष्ठा device *dev = hisi_hba->dev;

	atomic_inc(&phy->करोwn_cnt);

	del_समयr(&phy->समयr);
	hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, PHYCTRL_NOT_RDY_MSK, 1);

	phy_state = hisi_sas_पढ़ो32(hisi_hba, PHY_STATE);
	dev_info(dev, "phydown: phy%d phy_state=0x%x\n", phy_no, phy_state);
	hisi_sas_phy_करोwn(hisi_hba, phy_no, (phy_state & 1 << phy_no) ? 1 : 0,
			  GFP_ATOMIC);

	sl_ctrl = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no, SL_CONTROL);
	hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, SL_CONTROL,
						sl_ctrl&(~SL_CTA_MSK));

	txid_स्वतः = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no, TXID_AUTO);
	hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, TXID_AUTO,
						txid_स्वतः | CT3_MSK);

	hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, CHL_INT0, CHL_INT0_NOT_RDY_MSK);
	hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, PHYCTRL_NOT_RDY_MSK, 0);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t phy_bcast_v3_hw(पूर्णांक phy_no, काष्ठा hisi_hba *hisi_hba)
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

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t पूर्णांक_phy_up_करोwn_bcast_v3_hw(पूर्णांक irq_no, व्योम *p)
अणु
	काष्ठा hisi_hba *hisi_hba = p;
	u32 irq_msk;
	पूर्णांक phy_no = 0;
	irqवापस_t res = IRQ_NONE;

	irq_msk = hisi_sas_पढ़ो32(hisi_hba, CHNL_INT_STATUS)
				& 0x11111111;
	जबतक (irq_msk) अणु
		अगर (irq_msk  & 1) अणु
			u32 irq_value = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no,
							    CHL_INT0);
			u32 phy_state = hisi_sas_पढ़ो32(hisi_hba, PHY_STATE);
			पूर्णांक rdy = phy_state & (1 << phy_no);

			अगर (rdy) अणु
				अगर (irq_value & CHL_INT0_SL_PHY_ENABLE_MSK)
					/* phy up */
					अगर (phy_up_v3_hw(phy_no, hisi_hba)
							== IRQ_HANDLED)
						res = IRQ_HANDLED;
				अगर (irq_value & CHL_INT0_SL_RX_BCST_ACK_MSK)
					/* phy bcast */
					अगर (phy_bcast_v3_hw(phy_no, hisi_hba)
							== IRQ_HANDLED)
						res = IRQ_HANDLED;
			पूर्ण अन्यथा अणु
				अगर (irq_value & CHL_INT0_NOT_RDY_MSK)
					/* phy करोwn */
					अगर (phy_करोwn_v3_hw(phy_no, hisi_hba)
							== IRQ_HANDLED)
						res = IRQ_HANDLED;
			पूर्ण
		पूर्ण
		irq_msk >>= 4;
		phy_no++;
	पूर्ण

	वापस res;
पूर्ण

अटल स्थिर काष्ठा hisi_sas_hw_error port_axi_error[] = अणु
	अणु
		.irq_msk = BIT(CHL_INT1_DMAC_TX_ECC_MB_ERR_OFF),
		.msg = "dmac_tx_ecc_bad_err",
	पूर्ण,
	अणु
		.irq_msk = BIT(CHL_INT1_DMAC_RX_ECC_MB_ERR_OFF),
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
	अणु
		.irq_msk = BIT(CHL_INT1_DMAC_TX_FIFO_ERR_OFF),
		.msg = "dma_tx_fifo_err",
	पूर्ण,
	अणु
		.irq_msk = BIT(CHL_INT1_DMAC_RX_FIFO_ERR_OFF),
		.msg = "dma_rx_fifo_err",
	पूर्ण,
	अणु
		.irq_msk = BIT(CHL_INT1_DMAC_TX_AXI_RUSER_ERR_OFF),
		.msg = "dma_tx_axi_ruser_err",
	पूर्ण,
	अणु
		.irq_msk = BIT(CHL_INT1_DMAC_RX_AXI_RUSER_ERR_OFF),
		.msg = "dma_rx_axi_ruser_err",
	पूर्ण,
पूर्ण;

अटल व्योम handle_chl_पूर्णांक1_v3_hw(काष्ठा hisi_hba *hisi_hba, पूर्णांक phy_no)
अणु
	u32 irq_value = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no, CHL_INT1);
	u32 irq_msk = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no, CHL_INT1_MSK);
	काष्ठा device *dev = hisi_hba->dev;
	पूर्णांक i;

	irq_value &= ~irq_msk;
	अगर (!irq_value) अणु
		dev_warn(dev, "phy%d channel int 1 received with status bits cleared\n",
			 phy_no);
		वापस;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(port_axi_error); i++) अणु
		स्थिर काष्ठा hisi_sas_hw_error *error = &port_axi_error[i];

		अगर (!(irq_value & error->irq_msk))
			जारी;

		dev_err(dev, "%s error (phy%d 0x%x) found!\n",
			error->msg, phy_no, irq_value);
		queue_work(hisi_hba->wq, &hisi_hba->rst_work);
	पूर्ण

	hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, CHL_INT1, irq_value);
पूर्ण

अटल व्योम phy_get_events_v3_hw(काष्ठा hisi_hba *hisi_hba, पूर्णांक phy_no)
अणु
	काष्ठा hisi_sas_phy *phy = &hisi_hba->phy[phy_no];
	काष्ठा asd_sas_phy *sas_phy = &phy->sas_phy;
	काष्ठा sas_phy *sphy = sas_phy->phy;
	अचिन्हित दीर्घ flags;
	u32 reg_value;

	spin_lock_irqsave(&phy->lock, flags);

	/* loss dword sync */
	reg_value = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no, ERR_CNT_DWS_LOST);
	sphy->loss_of_dword_sync_count += reg_value;

	/* phy reset problem */
	reg_value = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no, ERR_CNT_RESET_PROB);
	sphy->phy_reset_problem_count += reg_value;

	/* invalid dword */
	reg_value = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no, ERR_CNT_INVLD_DW);
	sphy->invalid_dword_count += reg_value;

	/* disparity err */
	reg_value = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no, ERR_CNT_DISP_ERR);
	sphy->running_disparity_error_count += reg_value;

	/* code violation error */
	reg_value = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no, ERR_CNT_CODE_ERR);
	phy->code_violation_err_count += reg_value;

	spin_unlock_irqrestore(&phy->lock, flags);
पूर्ण

अटल व्योम handle_chl_पूर्णांक2_v3_hw(काष्ठा hisi_hba *hisi_hba, पूर्णांक phy_no)
अणु
	u32 irq_msk = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no, CHL_INT2_MSK);
	u32 irq_value = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no, CHL_INT2);
	काष्ठा hisi_sas_phy *phy = &hisi_hba->phy[phy_no];
	काष्ठा pci_dev *pci_dev = hisi_hba->pci_dev;
	काष्ठा device *dev = hisi_hba->dev;
	अटल स्थिर u32 msk = BIT(CHL_INT2_RX_DISP_ERR_OFF) |
			BIT(CHL_INT2_RX_CODE_ERR_OFF) |
			BIT(CHL_INT2_RX_INVLD_DW_OFF);

	irq_value &= ~irq_msk;
	अगर (!irq_value) अणु
		dev_warn(dev, "phy%d channel int 2 received with status bits cleared\n",
			 phy_no);
		वापस;
	पूर्ण

	अगर (irq_value & BIT(CHL_INT2_SL_IDAF_TOUT_CONF_OFF)) अणु
		dev_warn(dev, "phy%d identify timeout\n", phy_no);
		hisi_sas_notअगरy_phy_event(phy, HISI_PHYE_LINK_RESET);
	पूर्ण

	अगर (irq_value & BIT(CHL_INT2_STP_LINK_TIMEOUT_OFF)) अणु
		u32 reg_value = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no,
				STP_LINK_TIMEOUT_STATE);

		dev_warn(dev, "phy%d stp link timeout (0x%x)\n",
			 phy_no, reg_value);
		अगर (reg_value & BIT(4))
			hisi_sas_notअगरy_phy_event(phy, HISI_PHYE_LINK_RESET);
	पूर्ण

	अगर (pci_dev->revision > 0x20 && (irq_value & msk)) अणु
		काष्ठा asd_sas_phy *sas_phy = &phy->sas_phy;
		काष्ठा sas_phy *sphy = sas_phy->phy;

		phy_get_events_v3_hw(hisi_hba, phy_no);

		अगर (irq_value & BIT(CHL_INT2_RX_INVLD_DW_OFF))
			dev_info(dev, "phy%d invalid dword cnt:   %u\n", phy_no,
				 sphy->invalid_dword_count);

		अगर (irq_value & BIT(CHL_INT2_RX_CODE_ERR_OFF))
			dev_info(dev, "phy%d code violation cnt:  %u\n", phy_no,
				 phy->code_violation_err_count);

		अगर (irq_value & BIT(CHL_INT2_RX_DISP_ERR_OFF))
			dev_info(dev, "phy%d disparity error cnt: %u\n", phy_no,
				 sphy->running_disparity_error_count);
	पूर्ण

	अगर ((irq_value & BIT(CHL_INT2_RX_INVLD_DW_OFF)) &&
	    (pci_dev->revision == 0x20)) अणु
		u32 reg_value;
		पूर्णांक rc;

		rc = hisi_sas_पढ़ो32_poll_समयout_atomic(
				HILINK_ERR_DFX, reg_value,
				!((reg_value >> 8) & BIT(phy_no)),
				1000, 10000);
		अगर (rc)
			hisi_sas_notअगरy_phy_event(phy, HISI_PHYE_LINK_RESET);
	पूर्ण

	hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, CHL_INT2, irq_value);
पूर्ण

अटल व्योम handle_chl_पूर्णांक0_v3_hw(काष्ठा hisi_hba *hisi_hba, पूर्णांक phy_no)
अणु
	u32 irq_value0 = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no, CHL_INT0);

	अगर (irq_value0 & CHL_INT0_PHY_RDY_MSK)
		hisi_sas_phy_oob_पढ़ोy(hisi_hba, phy_no);

	hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, CHL_INT0,
			     irq_value0 & (~CHL_INT0_SL_RX_BCST_ACK_MSK)
			     & (~CHL_INT0_SL_PHY_ENABLE_MSK)
			     & (~CHL_INT0_NOT_RDY_MSK));
पूर्ण

अटल irqवापस_t पूर्णांक_chnl_पूर्णांक_v3_hw(पूर्णांक irq_no, व्योम *p)
अणु
	काष्ठा hisi_hba *hisi_hba = p;
	u32 irq_msk;
	पूर्णांक phy_no = 0;

	irq_msk = hisi_sas_पढ़ो32(hisi_hba, CHNL_INT_STATUS)
		  & CHNL_INT_STS_MSK;

	जबतक (irq_msk) अणु
		अगर (irq_msk & (CHNL_INT_STS_INT0_MSK << (phy_no * CHNL_WIDTH)))
			handle_chl_पूर्णांक0_v3_hw(hisi_hba, phy_no);

		अगर (irq_msk & (CHNL_INT_STS_INT1_MSK << (phy_no * CHNL_WIDTH)))
			handle_chl_पूर्णांक1_v3_hw(hisi_hba, phy_no);

		अगर (irq_msk & (CHNL_INT_STS_INT2_MSK << (phy_no * CHNL_WIDTH)))
			handle_chl_पूर्णांक2_v3_hw(hisi_hba, phy_no);

		irq_msk &= ~(CHNL_INT_STS_PHY_MSK << (phy_no * CHNL_WIDTH));
		phy_no++;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

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
	अणु
		.irq_msk = BIT(SAS_ECC_INTR_OOO_RAM_ECC_MB_OFF),
		.msk = AM_ROB_ECC_ERR_ADDR_MSK,
		.shअगरt = AM_ROB_ECC_ERR_ADDR_OFF,
		.msg = "ooo_ram_eccbad_intr",
		.reg = AM_ROB_ECC_ERR_ADDR,
	पूर्ण,
पूर्ण;

अटल व्योम multi_bit_ecc_error_process_v3_hw(काष्ठा hisi_hba *hisi_hba,
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
पूर्ण

अटल व्योम fatal_ecc_पूर्णांक_v3_hw(काष्ठा hisi_hba *hisi_hba)
अणु
	u32 irq_value, irq_msk;

	irq_msk = hisi_sas_पढ़ो32(hisi_hba, SAS_ECC_INTR_MSK);
	hisi_sas_ग_लिखो32(hisi_hba, SAS_ECC_INTR_MSK, 0xffffffff);

	irq_value = hisi_sas_पढ़ो32(hisi_hba, SAS_ECC_INTR);
	अगर (irq_value)
		multi_bit_ecc_error_process_v3_hw(hisi_hba, irq_value);

	hisi_sas_ग_लिखो32(hisi_hba, SAS_ECC_INTR, irq_value);
	hisi_sas_ग_लिखो32(hisi_hba, SAS_ECC_INTR_MSK, irq_msk);
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

अटल स्थिर काष्ठा hisi_sas_hw_error fatal_axi_error[] = अणु
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
	अणु
		.irq_msk = BIT(ENT_INT_SRC3_DQE_POISON_OFF),
		.msg = "read dqe poison",
	पूर्ण,
	अणु
		.irq_msk = BIT(ENT_INT_SRC3_IOST_POISON_OFF),
		.msg = "read iost poison",
	पूर्ण,
	अणु
		.irq_msk = BIT(ENT_INT_SRC3_ITCT_POISON_OFF),
		.msg = "read itct poison",
	पूर्ण,
	अणु
		.irq_msk = BIT(ENT_INT_SRC3_ITCT_NCQ_POISON_OFF),
		.msg = "read itct ncq poison",
	पूर्ण,

पूर्ण;

अटल irqवापस_t fatal_axi_पूर्णांक_v3_hw(पूर्णांक irq_no, व्योम *p)
अणु
	u32 irq_value, irq_msk;
	काष्ठा hisi_hba *hisi_hba = p;
	काष्ठा device *dev = hisi_hba->dev;
	काष्ठा pci_dev *pdev = hisi_hba->pci_dev;
	पूर्णांक i;

	irq_msk = hisi_sas_पढ़ो32(hisi_hba, ENT_INT_SRC_MSK3);
	hisi_sas_ग_लिखो32(hisi_hba, ENT_INT_SRC_MSK3, irq_msk | 0x1df00);

	irq_value = hisi_sas_पढ़ो32(hisi_hba, ENT_INT_SRC3);
	irq_value &= ~irq_msk;

	क्रम (i = 0; i < ARRAY_SIZE(fatal_axi_error); i++) अणु
		स्थिर काष्ठा hisi_sas_hw_error *error = &fatal_axi_error[i];

		अगर (!(irq_value & error->irq_msk))
			जारी;

		अगर (error->sub) अणु
			स्थिर काष्ठा hisi_sas_hw_error *sub = error->sub;
			u32 err_value = hisi_sas_पढ़ो32(hisi_hba, error->reg);

			क्रम (; sub->msk || sub->msg; sub++) अणु
				अगर (!(err_value & sub->msk))
					जारी;

				dev_err(dev, "%s error (0x%x) found!\n",
					sub->msg, irq_value);
				queue_work(hisi_hba->wq, &hisi_hba->rst_work);
			पूर्ण
		पूर्ण अन्यथा अणु
			dev_err(dev, "%s error (0x%x) found!\n",
				error->msg, irq_value);
			queue_work(hisi_hba->wq, &hisi_hba->rst_work);
		पूर्ण

		अगर (pdev->revision < 0x21) अणु
			u32 reg_val;

			reg_val = hisi_sas_पढ़ो32(hisi_hba,
						  AXI_MASTER_CFG_BASE +
						  AM_CTRL_GLOBAL);
			reg_val |= AM_CTRL_SHUTDOWN_REQ_MSK;
			hisi_sas_ग_लिखो32(hisi_hba, AXI_MASTER_CFG_BASE +
					 AM_CTRL_GLOBAL, reg_val);
		पूर्ण
	पूर्ण

	fatal_ecc_पूर्णांक_v3_hw(hisi_hba);

	अगर (irq_value & BIT(ENT_INT_SRC3_ITC_INT_OFF)) अणु
		u32 reg_val = hisi_sas_पढ़ो32(hisi_hba, ITCT_CLR);
		u32 dev_id = reg_val & ITCT_DEV_MSK;
		काष्ठा hisi_sas_device *sas_dev =
				&hisi_hba->devices[dev_id];

		hisi_sas_ग_लिखो32(hisi_hba, ITCT_CLR, 0);
		dev_dbg(dev, "clear ITCT ok\n");
		complete(sas_dev->completion);
	पूर्ण

	hisi_sas_ग_लिखो32(hisi_hba, ENT_INT_SRC3, irq_value & 0x1df00);
	hisi_sas_ग_लिखो32(hisi_hba, ENT_INT_SRC_MSK3, irq_msk);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम
slot_err_v3_hw(काष्ठा hisi_hba *hisi_hba, काष्ठा sas_task *task,
	       काष्ठा hisi_sas_slot *slot)
अणु
	काष्ठा task_status_काष्ठा *ts = &task->task_status;
	काष्ठा hisi_sas_complete_v3_hdr *complete_queue =
			hisi_hba->complete_hdr[slot->cmplt_queue];
	काष्ठा hisi_sas_complete_v3_hdr *complete_hdr =
			&complete_queue[slot->cmplt_queue_slot];
	काष्ठा hisi_sas_err_record_v3 *record =
			hisi_sas_status_buf_addr_mem(slot);
	u32 dma_rx_err_type = le32_to_cpu(record->dma_rx_err_type);
	u32 trans_tx_fail_type = le32_to_cpu(record->trans_tx_fail_type);
	u32 dw3 = le32_to_cpu(complete_hdr->dw3);

	चयन (task->task_proto) अणु
	हाल SAS_PROTOCOL_SSP:
		अगर (dma_rx_err_type & RX_DATA_LEN_UNDERFLOW_MSK) अणु
			ts->residual = trans_tx_fail_type;
			ts->stat = SAS_DATA_UNDERRUN;
		पूर्ण अन्यथा अगर (dw3 & CMPLT_HDR_IO_IN_TARGET_MSK) अणु
			ts->stat = SAS_QUEUE_FULL;
			slot->पात = 1;
		पूर्ण अन्यथा अणु
			ts->stat = SAS_OPEN_REJECT;
			ts->खोलो_rej_reason = SAS_OREJ_RSVD_RETRY;
		पूर्ण
		अवरोध;
	हाल SAS_PROTOCOL_SATA:
	हाल SAS_PROTOCOL_STP:
	हाल SAS_PROTOCOL_SATA | SAS_PROTOCOL_STP:
		अगर (dma_rx_err_type & RX_DATA_LEN_UNDERFLOW_MSK) अणु
			ts->residual = trans_tx_fail_type;
			ts->stat = SAS_DATA_UNDERRUN;
		पूर्ण अन्यथा अगर (dw3 & CMPLT_HDR_IO_IN_TARGET_MSK) अणु
			ts->stat = SAS_PHY_DOWN;
			slot->पात = 1;
		पूर्ण अन्यथा अणु
			ts->stat = SAS_OPEN_REJECT;
			ts->खोलो_rej_reason = SAS_OREJ_RSVD_RETRY;
		पूर्ण
		hisi_sas_sata_करोne(task, slot);
		अवरोध;
	हाल SAS_PROTOCOL_SMP:
		ts->stat = SAM_STAT_CHECK_CONDITION;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम slot_complete_v3_hw(काष्ठा hisi_hba *hisi_hba,
				काष्ठा hisi_sas_slot *slot)
अणु
	काष्ठा sas_task *task = slot->task;
	काष्ठा hisi_sas_device *sas_dev;
	काष्ठा device *dev = hisi_hba->dev;
	काष्ठा task_status_काष्ठा *ts;
	काष्ठा करोमुख्य_device *device;
	काष्ठा sas_ha_काष्ठा *ha;
	काष्ठा hisi_sas_complete_v3_hdr *complete_queue =
			hisi_hba->complete_hdr[slot->cmplt_queue];
	काष्ठा hisi_sas_complete_v3_hdr *complete_hdr =
			&complete_queue[slot->cmplt_queue_slot];
	अचिन्हित दीर्घ flags;
	bool is_पूर्णांकernal = slot->is_पूर्णांकernal;
	u32 dw0, dw1, dw3;

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
		dev_dbg(dev, "slot complete: port has not device\n");
		ts->stat = SAS_PHY_DOWN;
		जाओ out;
	पूर्ण

	dw0 = le32_to_cpu(complete_hdr->dw0);
	dw1 = le32_to_cpu(complete_hdr->dw1);
	dw3 = le32_to_cpu(complete_hdr->dw3);

	/*
	 * Use SAS+TMF status codes
	 */
	चयन ((dw0 & CMPLT_HDR_ABORT_STAT_MSK) >> CMPLT_HDR_ABORT_STAT_OFF) अणु
	हाल STAT_IO_ABORTED:
		/* this IO has been पातed by पात command */
		ts->stat = SAS_ABORTED_TASK;
		जाओ out;
	हाल STAT_IO_COMPLETE:
		/* पूर्णांकernal पात command complete */
		ts->stat = TMF_RESP_FUNC_SUCC;
		जाओ out;
	हाल STAT_IO_NO_DEVICE:
		ts->stat = TMF_RESP_FUNC_COMPLETE;
		जाओ out;
	हाल STAT_IO_NOT_VALID:
		/*
		 * पात single IO, the controller can't find the IO
		 */
		ts->stat = TMF_RESP_FUNC_FAILED;
		जाओ out;
	शेष:
		अवरोध;
	पूर्ण

	/* check क्रम erroneous completion */
	अगर ((dw0 & CMPLT_HDR_CMPLT_MSK) == 0x3) अणु
		u32 *error_info = hisi_sas_status_buf_addr_mem(slot);

		slot_err_v3_hw(hisi_hba, task, slot);
		अगर (ts->stat != SAS_DATA_UNDERRUN)
			dev_info(dev, "erroneous completion iptt=%d task=%pK dev id=%d addr=%016llx CQ hdr: 0x%x 0x%x 0x%x 0x%x Error info: 0x%x 0x%x 0x%x 0x%x\n",
				 slot->idx, task, sas_dev->device_id,
				 SAS_ADDR(device->sas_addr),
				 dw0, dw1, complete_hdr->act, dw3,
				 error_info[0], error_info[1],
				 error_info[2], error_info[3]);
		अगर (unlikely(slot->पात)) अणु
			sas_task_पात(task);
			वापस;
		पूर्ण
		जाओ out;
	पूर्ण

	चयन (task->task_proto) अणु
	हाल SAS_PROTOCOL_SSP: अणु
		काष्ठा ssp_response_iu *iu =
			hisi_sas_status_buf_addr_mem(slot) +
			माप(काष्ठा hisi_sas_err_record);

		sas_ssp_task_response(dev, task, iu);
		अवरोध;
	पूर्ण
	हाल SAS_PROTOCOL_SMP: अणु
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
		ts->stat = SAM_STAT_GOOD;
		hisi_sas_sata_करोne(task, slot);
		अवरोध;
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
			dev_info(dev, "slot complete: task(%pK) ignored\n ",
				 task);
			वापस;
		पूर्ण
		spin_unlock_irqrestore(&device->करोne_lock, flags);
	पूर्ण

	अगर (task->task_करोne)
		task->task_करोne(task);
पूर्ण

अटल irqवापस_t  cq_thपढ़ो_v3_hw(पूर्णांक irq_no, व्योम *p)
अणु
	काष्ठा hisi_sas_cq *cq = p;
	काष्ठा hisi_hba *hisi_hba = cq->hisi_hba;
	काष्ठा hisi_sas_slot *slot;
	काष्ठा hisi_sas_complete_v3_hdr *complete_queue;
	u32 rd_poपूर्णांक = cq->rd_poपूर्णांक, wr_poपूर्णांक;
	पूर्णांक queue = cq->id;

	complete_queue = hisi_hba->complete_hdr[queue];

	wr_poपूर्णांक = hisi_sas_पढ़ो32(hisi_hba, COMPL_Q_0_WR_PTR +
				   (0x14 * queue));

	जबतक (rd_poपूर्णांक != wr_poपूर्णांक) अणु
		काष्ठा hisi_sas_complete_v3_hdr *complete_hdr;
		काष्ठा device *dev = hisi_hba->dev;
		u32 dw1;
		पूर्णांक iptt;

		complete_hdr = &complete_queue[rd_poपूर्णांक];
		dw1 = le32_to_cpu(complete_hdr->dw1);

		iptt = dw1 & CMPLT_HDR_IPTT_MSK;
		अगर (likely(iptt < HISI_SAS_COMMAND_ENTRIES_V3_HW)) अणु
			slot = &hisi_hba->slot_info[iptt];
			slot->cmplt_queue_slot = rd_poपूर्णांक;
			slot->cmplt_queue = queue;
			slot_complete_v3_hw(hisi_hba, slot);
		पूर्ण अन्यथा
			dev_err(dev, "IPTT %d is invalid, discard it.\n", iptt);

		अगर (++rd_poपूर्णांक >= HISI_SAS_QUEUE_SLOTS)
			rd_poपूर्णांक = 0;
	पूर्ण

	/* update rd_poपूर्णांक */
	cq->rd_poपूर्णांक = rd_poपूर्णांक;
	hisi_sas_ग_लिखो32(hisi_hba, COMPL_Q_0_RD_PTR + (0x14 * queue), rd_poपूर्णांक);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t cq_पूर्णांकerrupt_v3_hw(पूर्णांक irq_no, व्योम *p)
अणु
	काष्ठा hisi_sas_cq *cq = p;
	काष्ठा hisi_hba *hisi_hba = cq->hisi_hba;
	पूर्णांक queue = cq->id;

	hisi_sas_ग_लिखो32(hisi_hba, OQ_INT_SRC, 1 << queue);

	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल पूर्णांक पूर्णांकerrupt_preinit_v3_hw(काष्ठा hisi_hba *hisi_hba)
अणु
	पूर्णांक vectors;
	पूर्णांक max_msi = HISI_SAS_MSI_COUNT_V3_HW, min_msi;
	काष्ठा Scsi_Host *shost = hisi_hba->shost;
	काष्ठा irq_affinity desc = अणु
		.pre_vectors = BASE_VECTORS_V3_HW,
	पूर्ण;

	min_msi = MIN_AFFINE_VECTORS_V3_HW;
	vectors = pci_alloc_irq_vectors_affinity(hisi_hba->pci_dev,
						 min_msi, max_msi,
						 PCI_IRQ_MSI |
						 PCI_IRQ_AFFINITY,
						 &desc);
	अगर (vectors < 0)
		वापस -ENOENT;


	hisi_hba->cq_nvecs = vectors - BASE_VECTORS_V3_HW;
	shost->nr_hw_queues = hisi_hba->cq_nvecs;

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकerrupt_init_v3_hw(काष्ठा hisi_hba *hisi_hba)
अणु
	काष्ठा device *dev = hisi_hba->dev;
	काष्ठा pci_dev *pdev = hisi_hba->pci_dev;
	पूर्णांक rc, i;

	rc = devm_request_irq(dev, pci_irq_vector(pdev, 1),
			      पूर्णांक_phy_up_करोwn_bcast_v3_hw, 0,
			      DRV_NAME " phy", hisi_hba);
	अगर (rc) अणु
		dev_err(dev, "could not request phy interrupt, rc=%d\n", rc);
		वापस -ENOENT;
	पूर्ण

	rc = devm_request_irq(dev, pci_irq_vector(pdev, 2),
			      पूर्णांक_chnl_पूर्णांक_v3_hw, 0,
			      DRV_NAME " channel", hisi_hba);
	अगर (rc) अणु
		dev_err(dev, "could not request chnl interrupt, rc=%d\n", rc);
		वापस -ENOENT;
	पूर्ण

	rc = devm_request_irq(dev, pci_irq_vector(pdev, 11),
			      fatal_axi_पूर्णांक_v3_hw, 0,
			      DRV_NAME " fatal", hisi_hba);
	अगर (rc) अणु
		dev_err(dev, "could not request fatal interrupt, rc=%d\n", rc);
		वापस -ENOENT;
	पूर्ण

	अगर (hisi_sas_पूर्णांकr_conv)
		dev_info(dev, "Enable interrupt converge\n");

	क्रम (i = 0; i < hisi_hba->cq_nvecs; i++) अणु
		काष्ठा hisi_sas_cq *cq = &hisi_hba->cq[i];
		पूर्णांक nr = hisi_sas_पूर्णांकr_conv ? 16 : 16 + i;
		अचिन्हित दीर्घ irqflags = hisi_sas_पूर्णांकr_conv ? IRQF_SHARED :
							      IRQF_ONESHOT;

		cq->irq_no = pci_irq_vector(pdev, nr);
		rc = devm_request_thपढ़ोed_irq(dev, cq->irq_no,
				      cq_पूर्णांकerrupt_v3_hw,
				      cq_thपढ़ो_v3_hw,
				      irqflags,
				      DRV_NAME " cq", cq);
		अगर (rc) अणु
			dev_err(dev, "could not request cq%d interrupt, rc=%d\n",
				i, rc);
			वापस -ENOENT;
		पूर्ण
		cq->irq_mask = pci_irq_get_affinity(pdev, i + BASE_VECTORS_V3_HW);
		अगर (!cq->irq_mask) अणु
			dev_err(dev, "could not get cq%d irq affinity!\n", i);
			वापस -ENOENT;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hisi_sas_v3_init(काष्ठा hisi_hba *hisi_hba)
अणु
	पूर्णांक rc;

	rc = hw_init_v3_hw(hisi_hba);
	अगर (rc)
		वापस rc;

	rc = पूर्णांकerrupt_init_v3_hw(hisi_hba);
	अगर (rc)
		वापस rc;

	वापस 0;
पूर्ण

अटल व्योम phy_set_linkrate_v3_hw(काष्ठा hisi_hba *hisi_hba, पूर्णांक phy_no,
		काष्ठा sas_phy_linkrates *r)
अणु
	क्रमागत sas_linkrate max = r->maximum_linkrate;
	u32 prog_phy_link_rate = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no,
						     PROG_PHY_LINK_RATE);

	prog_phy_link_rate &= ~CFG_PROG_PHY_LINK_RATE_MSK;
	prog_phy_link_rate |= hisi_sas_get_prog_phy_linkrate_mask(max);
	hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, PROG_PHY_LINK_RATE,
			     prog_phy_link_rate);
पूर्ण

अटल व्योम पूर्णांकerrupt_disable_v3_hw(काष्ठा hisi_hba *hisi_hba)
अणु
	काष्ठा pci_dev *pdev = hisi_hba->pci_dev;
	पूर्णांक i;

	synchronize_irq(pci_irq_vector(pdev, 1));
	synchronize_irq(pci_irq_vector(pdev, 2));
	synchronize_irq(pci_irq_vector(pdev, 11));
	क्रम (i = 0; i < hisi_hba->queue_count; i++)
		hisi_sas_ग_लिखो32(hisi_hba, OQ0_INT_SRC_MSK + 0x4 * i, 0x1);

	क्रम (i = 0; i < hisi_hba->cq_nvecs; i++)
		synchronize_irq(pci_irq_vector(pdev, i + 16));

	hisi_sas_ग_लिखो32(hisi_hba, ENT_INT_SRC_MSK1, 0xffffffff);
	hisi_sas_ग_लिखो32(hisi_hba, ENT_INT_SRC_MSK2, 0xffffffff);
	hisi_sas_ग_लिखो32(hisi_hba, ENT_INT_SRC_MSK3, 0xffffffff);
	hisi_sas_ग_लिखो32(hisi_hba, SAS_ECC_INTR_MSK, 0xffffffff);

	क्रम (i = 0; i < hisi_hba->n_phy; i++) अणु
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, CHL_INT1_MSK, 0xffffffff);
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, CHL_INT2_MSK, 0xffffffff);
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, PHYCTRL_NOT_RDY_MSK, 0x1);
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, PHYCTRL_PHY_ENA_MSK, 0x1);
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, SL_RX_BCAST_CHK_MSK, 0x1);
	पूर्ण
पूर्ण

अटल u32 get_phys_state_v3_hw(काष्ठा hisi_hba *hisi_hba)
अणु
	वापस hisi_sas_पढ़ो32(hisi_hba, PHY_STATE);
पूर्ण

अटल पूर्णांक disable_host_v3_hw(काष्ठा hisi_hba *hisi_hba)
अणु
	काष्ठा device *dev = hisi_hba->dev;
	u32 status, reg_val;
	पूर्णांक rc;

	पूर्णांकerrupt_disable_v3_hw(hisi_hba);
	hisi_sas_ग_लिखो32(hisi_hba, DLVRY_QUEUE_ENABLE, 0x0);

	hisi_sas_stop_phys(hisi_hba);

	mdelay(10);

	reg_val = hisi_sas_पढ़ो32(hisi_hba, AXI_MASTER_CFG_BASE +
				  AM_CTRL_GLOBAL);
	reg_val |= AM_CTRL_SHUTDOWN_REQ_MSK;
	hisi_sas_ग_लिखो32(hisi_hba, AXI_MASTER_CFG_BASE +
			 AM_CTRL_GLOBAL, reg_val);

	/* रुको until bus idle */
	rc = hisi_sas_पढ़ो32_poll_समयout(AXI_MASTER_CFG_BASE +
					  AM_CURR_TRANS_RETURN, status,
					  status == 0x3, 10, 100);
	अगर (rc) अणु
		dev_err(dev, "axi bus is not idle, rc=%d\n", rc);
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक soft_reset_v3_hw(काष्ठा hisi_hba *hisi_hba)
अणु
	काष्ठा device *dev = hisi_hba->dev;
	पूर्णांक rc;

	rc = disable_host_v3_hw(hisi_hba);
	अगर (rc) अणु
		dev_err(dev, "soft reset: disable host failed rc=%d\n", rc);
		वापस rc;
	पूर्ण

	hisi_sas_init_mem(hisi_hba);

	वापस hw_init_v3_hw(hisi_hba);
पूर्ण

अटल पूर्णांक ग_लिखो_gpio_v3_hw(काष्ठा hisi_hba *hisi_hba, u8 reg_type,
			u8 reg_index, u8 reg_count, u8 *ग_लिखो_data)
अणु
	काष्ठा device *dev = hisi_hba->dev;
	u32 *data = (u32 *)ग_लिखो_data;
	पूर्णांक i;

	चयन (reg_type) अणु
	हाल SAS_GPIO_REG_TX:
		अगर ((reg_index + reg_count) > ((hisi_hba->n_phy + 3) / 4)) अणु
			dev_err(dev, "write gpio: invalid reg range[%d, %d]\n",
				reg_index, reg_index + reg_count - 1);
			वापस -EINVAL;
		पूर्ण

		क्रम (i = 0; i < reg_count; i++)
			hisi_sas_ग_लिखो32(hisi_hba,
					 SAS_GPIO_TX_0_1 + (reg_index + i) * 4,
					 data[i]);
		अवरोध;
	शेष:
		dev_err(dev, "write gpio: unsupported or bad reg type %d\n",
			reg_type);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम रुको_cmds_complete_समयout_v3_hw(काष्ठा hisi_hba *hisi_hba,
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

अटल sमाप_प्रकार पूर्णांकr_conv_v3_hw_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "%u\n", hisi_sas_पूर्णांकr_conv);
पूर्ण
अटल DEVICE_ATTR_RO(पूर्णांकr_conv_v3_hw);

अटल व्योम config_पूर्णांकr_coal_v3_hw(काष्ठा hisi_hba *hisi_hba)
अणु
	/* config those रेजिस्टरs between enable and disable PHYs */
	hisi_sas_stop_phys(hisi_hba);

	अगर (hisi_hba->पूर्णांकr_coal_ticks == 0 ||
	    hisi_hba->पूर्णांकr_coal_count == 0) अणु
		hisi_sas_ग_लिखो32(hisi_hba, INT_COAL_EN, 0x1);
		hisi_sas_ग_लिखो32(hisi_hba, OQ_INT_COAL_TIME, 0x1);
		hisi_sas_ग_लिखो32(hisi_hba, OQ_INT_COAL_CNT, 0x1);
	पूर्ण अन्यथा अणु
		hisi_sas_ग_लिखो32(hisi_hba, INT_COAL_EN, 0x3);
		hisi_sas_ग_लिखो32(hisi_hba, OQ_INT_COAL_TIME,
				 hisi_hba->पूर्णांकr_coal_ticks);
		hisi_sas_ग_लिखो32(hisi_hba, OQ_INT_COAL_CNT,
				 hisi_hba->पूर्णांकr_coal_count);
	पूर्ण
	phys_init_v3_hw(hisi_hba);
पूर्ण

अटल sमाप_प्रकार पूर्णांकr_coal_ticks_v3_hw_show(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा hisi_hba *hisi_hba = shost_priv(shost);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%u\n",
			 hisi_hba->पूर्णांकr_coal_ticks);
पूर्ण

अटल sमाप_प्रकार पूर्णांकr_coal_ticks_v3_hw_store(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा hisi_hba *hisi_hba = shost_priv(shost);
	u32 पूर्णांकr_coal_ticks;
	पूर्णांक ret;

	ret = kstrtou32(buf, 10, &पूर्णांकr_coal_ticks);
	अगर (ret) अणु
		dev_err(dev, "Input data of interrupt coalesce unmatch\n");
		वापस -EINVAL;
	पूर्ण

	अगर (पूर्णांकr_coal_ticks >= BIT(24)) अणु
		dev_err(dev, "पूर्णांकr_coal_ticks must be less than 2^24!\न");
		वापस -EINVAL;
	पूर्ण

	hisi_hba->पूर्णांकr_coal_ticks = पूर्णांकr_coal_ticks;

	config_पूर्णांकr_coal_v3_hw(hisi_hba);

	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(पूर्णांकr_coal_ticks_v3_hw);

अटल sमाप_प्रकार पूर्णांकr_coal_count_v3_hw_show(काष्ठा device *dev,
					  काष्ठा device_attribute
					  *attr, अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा hisi_hba *hisi_hba = shost_priv(shost);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%u\n",
			 hisi_hba->पूर्णांकr_coal_count);
पूर्ण

अटल sमाप_प्रकार पूर्णांकr_coal_count_v3_hw_store(काष्ठा device *dev,
		काष्ठा device_attribute
		*attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा hisi_hba *hisi_hba = shost_priv(shost);
	u32 पूर्णांकr_coal_count;
	पूर्णांक ret;

	ret = kstrtou32(buf, 10, &पूर्णांकr_coal_count);
	अगर (ret) अणु
		dev_err(dev, "Input data of interrupt coalesce unmatch\n");
		वापस -EINVAL;
	पूर्ण

	अगर (पूर्णांकr_coal_count >= BIT(8)) अणु
		dev_err(dev, "पूर्णांकr_coal_count must be less than 2^8!\न");
		वापस -EINVAL;
	पूर्ण

	hisi_hba->पूर्णांकr_coal_count = पूर्णांकr_coal_count;

	config_पूर्णांकr_coal_v3_hw(hisi_hba);

	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(पूर्णांकr_coal_count_v3_hw);

अटल पूर्णांक slave_configure_v3_hw(काष्ठा scsi_device *sdev)
अणु
	काष्ठा Scsi_Host *shost = dev_to_shost(&sdev->sdev_gendev);
	काष्ठा करोमुख्य_device *ddev = sdev_to_करोमुख्य_dev(sdev);
	काष्ठा hisi_hba *hisi_hba = shost_priv(shost);
	काष्ठा device *dev = hisi_hba->dev;
	पूर्णांक ret = sas_slave_configure(sdev);

	अगर (ret)
		वापस ret;
	अगर (!dev_is_sata(ddev))
		sas_change_queue_depth(sdev, 64);

	अगर (sdev->type == TYPE_ENCLOSURE)
		वापस 0;

	अगर (!device_link_add(&sdev->sdev_gendev, dev,
			     DL_FLAG_PM_RUNTIME | DL_FLAG_RPM_ACTIVE)) अणु
		अगर (pm_runसमय_enabled(dev)) अणु
			dev_info(dev, "add device link failed, disable runtime PM for the host\n");
			pm_runसमय_disable(dev);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा device_attribute *host_attrs_v3_hw[] = अणु
	&dev_attr_phy_event_threshold,
	&dev_attr_पूर्णांकr_conv_v3_hw,
	&dev_attr_पूर्णांकr_coal_ticks_v3_hw,
	&dev_attr_पूर्णांकr_coal_count_v3_hw,
	शून्य
पूर्ण;

#घोषणा HISI_SAS_DEBUGFS_REG(x) अणु#x, xपूर्ण

काष्ठा hisi_sas_debugfs_reg_lu अणु
	अक्षर *name;
	पूर्णांक off;
पूर्ण;

काष्ठा hisi_sas_debugfs_reg अणु
	स्थिर काष्ठा hisi_sas_debugfs_reg_lu *lu;
	पूर्णांक count;
	पूर्णांक base_off;
पूर्ण;

अटल स्थिर काष्ठा hisi_sas_debugfs_reg_lu debugfs_port_reg_lu[] = अणु
	HISI_SAS_DEBUGFS_REG(PHY_CFG),
	HISI_SAS_DEBUGFS_REG(HARD_PHY_LINKRATE),
	HISI_SAS_DEBUGFS_REG(PROG_PHY_LINK_RATE),
	HISI_SAS_DEBUGFS_REG(PHY_CTRL),
	HISI_SAS_DEBUGFS_REG(SL_CFG),
	HISI_SAS_DEBUGFS_REG(AIP_LIMIT),
	HISI_SAS_DEBUGFS_REG(SL_CONTROL),
	HISI_SAS_DEBUGFS_REG(RX_PRIMS_STATUS),
	HISI_SAS_DEBUGFS_REG(TX_ID_DWORD0),
	HISI_SAS_DEBUGFS_REG(TX_ID_DWORD1),
	HISI_SAS_DEBUGFS_REG(TX_ID_DWORD2),
	HISI_SAS_DEBUGFS_REG(TX_ID_DWORD3),
	HISI_SAS_DEBUGFS_REG(TX_ID_DWORD4),
	HISI_SAS_DEBUGFS_REG(TX_ID_DWORD5),
	HISI_SAS_DEBUGFS_REG(TX_ID_DWORD6),
	HISI_SAS_DEBUGFS_REG(TXID_AUTO),
	HISI_SAS_DEBUGFS_REG(RX_IDAF_DWORD0),
	HISI_SAS_DEBUGFS_REG(RXOP_CHECK_CFG_H),
	HISI_SAS_DEBUGFS_REG(STP_LINK_TIMER),
	HISI_SAS_DEBUGFS_REG(STP_LINK_TIMEOUT_STATE),
	HISI_SAS_DEBUGFS_REG(CON_CFG_DRIVER),
	HISI_SAS_DEBUGFS_REG(SAS_SSP_CON_TIMER_CFG),
	HISI_SAS_DEBUGFS_REG(SAS_SMP_CON_TIMER_CFG),
	HISI_SAS_DEBUGFS_REG(SAS_STP_CON_TIMER_CFG),
	HISI_SAS_DEBUGFS_REG(CHL_INT0),
	HISI_SAS_DEBUGFS_REG(CHL_INT1),
	HISI_SAS_DEBUGFS_REG(CHL_INT2),
	HISI_SAS_DEBUGFS_REG(CHL_INT0_MSK),
	HISI_SAS_DEBUGFS_REG(CHL_INT1_MSK),
	HISI_SAS_DEBUGFS_REG(CHL_INT2_MSK),
	HISI_SAS_DEBUGFS_REG(SAS_EC_INT_COAL_TIME),
	HISI_SAS_DEBUGFS_REG(CHL_INT_COAL_EN),
	HISI_SAS_DEBUGFS_REG(SAS_RX_TRAIN_TIMER),
	HISI_SAS_DEBUGFS_REG(PHY_CTRL_RDY_MSK),
	HISI_SAS_DEBUGFS_REG(PHYCTRL_NOT_RDY_MSK),
	HISI_SAS_DEBUGFS_REG(PHYCTRL_DWS_RESET_MSK),
	HISI_SAS_DEBUGFS_REG(PHYCTRL_PHY_ENA_MSK),
	HISI_SAS_DEBUGFS_REG(SL_RX_BCAST_CHK_MSK),
	HISI_SAS_DEBUGFS_REG(PHYCTRL_OOB_RESTART_MSK),
	HISI_SAS_DEBUGFS_REG(DMA_TX_STATUS),
	HISI_SAS_DEBUGFS_REG(DMA_RX_STATUS),
	HISI_SAS_DEBUGFS_REG(COARSETUNE_TIME),
	HISI_SAS_DEBUGFS_REG(ERR_CNT_DWS_LOST),
	HISI_SAS_DEBUGFS_REG(ERR_CNT_RESET_PROB),
	HISI_SAS_DEBUGFS_REG(ERR_CNT_INVLD_DW),
	HISI_SAS_DEBUGFS_REG(ERR_CNT_CODE_ERR),
	HISI_SAS_DEBUGFS_REG(ERR_CNT_DISP_ERR),
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hisi_sas_debugfs_reg debugfs_port_reg = अणु
	.lu = debugfs_port_reg_lu,
	.count = 0x100,
	.base_off = PORT_BASE,
पूर्ण;

अटल स्थिर काष्ठा hisi_sas_debugfs_reg_lu debugfs_global_reg_lu[] = अणु
	HISI_SAS_DEBUGFS_REG(DLVRY_QUEUE_ENABLE),
	HISI_SAS_DEBUGFS_REG(PHY_CONTEXT),
	HISI_SAS_DEBUGFS_REG(PHY_STATE),
	HISI_SAS_DEBUGFS_REG(PHY_PORT_NUM_MA),
	HISI_SAS_DEBUGFS_REG(PHY_CONN_RATE),
	HISI_SAS_DEBUGFS_REG(ITCT_CLR),
	HISI_SAS_DEBUGFS_REG(IO_SATA_BROKEN_MSG_ADDR_LO),
	HISI_SAS_DEBUGFS_REG(IO_SATA_BROKEN_MSG_ADDR_HI),
	HISI_SAS_DEBUGFS_REG(SATA_INITI_D2H_STORE_ADDR_LO),
	HISI_SAS_DEBUGFS_REG(SATA_INITI_D2H_STORE_ADDR_HI),
	HISI_SAS_DEBUGFS_REG(CFG_MAX_TAG),
	HISI_SAS_DEBUGFS_REG(HGC_SAS_TX_OPEN_FAIL_RETRY_CTRL),
	HISI_SAS_DEBUGFS_REG(HGC_SAS_TXFAIL_RETRY_CTRL),
	HISI_SAS_DEBUGFS_REG(HGC_GET_ITV_TIME),
	HISI_SAS_DEBUGFS_REG(DEVICE_MSG_WORK_MODE),
	HISI_SAS_DEBUGFS_REG(OPENA_WT_CONTI_TIME),
	HISI_SAS_DEBUGFS_REG(I_T_NEXUS_LOSS_TIME),
	HISI_SAS_DEBUGFS_REG(MAX_CON_TIME_LIMIT_TIME),
	HISI_SAS_DEBUGFS_REG(BUS_INACTIVE_LIMIT_TIME),
	HISI_SAS_DEBUGFS_REG(REJECT_TO_OPEN_LIMIT_TIME),
	HISI_SAS_DEBUGFS_REG(CQ_INT_CONVERGE_EN),
	HISI_SAS_DEBUGFS_REG(CFG_AGING_TIME),
	HISI_SAS_DEBUGFS_REG(HGC_DFX_CFG2),
	HISI_SAS_DEBUGFS_REG(CFG_ABT_SET_QUERY_IPTT),
	HISI_SAS_DEBUGFS_REG(CFG_ABT_SET_IPTT_DONE),
	HISI_SAS_DEBUGFS_REG(HGC_IOMB_PROC1_STATUS),
	HISI_SAS_DEBUGFS_REG(CHNL_INT_STATUS),
	HISI_SAS_DEBUGFS_REG(HGC_AXI_FIFO_ERR_INFO),
	HISI_SAS_DEBUGFS_REG(INT_COAL_EN),
	HISI_SAS_DEBUGFS_REG(OQ_INT_COAL_TIME),
	HISI_SAS_DEBUGFS_REG(OQ_INT_COAL_CNT),
	HISI_SAS_DEBUGFS_REG(ENT_INT_COAL_TIME),
	HISI_SAS_DEBUGFS_REG(ENT_INT_COAL_CNT),
	HISI_SAS_DEBUGFS_REG(OQ_INT_SRC),
	HISI_SAS_DEBUGFS_REG(OQ_INT_SRC_MSK),
	HISI_SAS_DEBUGFS_REG(ENT_INT_SRC1),
	HISI_SAS_DEBUGFS_REG(ENT_INT_SRC2),
	HISI_SAS_DEBUGFS_REG(ENT_INT_SRC3),
	HISI_SAS_DEBUGFS_REG(ENT_INT_SRC_MSK1),
	HISI_SAS_DEBUGFS_REG(ENT_INT_SRC_MSK2),
	HISI_SAS_DEBUGFS_REG(ENT_INT_SRC_MSK3),
	HISI_SAS_DEBUGFS_REG(CHNL_PHYUPDOWN_INT_MSK),
	HISI_SAS_DEBUGFS_REG(CHNL_ENT_INT_MSK),
	HISI_SAS_DEBUGFS_REG(HGC_COM_INT_MSK),
	HISI_SAS_DEBUGFS_REG(SAS_ECC_INTR),
	HISI_SAS_DEBUGFS_REG(SAS_ECC_INTR_MSK),
	HISI_SAS_DEBUGFS_REG(HGC_ERR_STAT_EN),
	HISI_SAS_DEBUGFS_REG(CQE_SEND_CNT),
	HISI_SAS_DEBUGFS_REG(DLVRY_Q_0_DEPTH),
	HISI_SAS_DEBUGFS_REG(DLVRY_Q_0_WR_PTR),
	HISI_SAS_DEBUGFS_REG(DLVRY_Q_0_RD_PTR),
	HISI_SAS_DEBUGFS_REG(HYPER_STREAM_ID_EN_CFG),
	HISI_SAS_DEBUGFS_REG(OQ0_INT_SRC_MSK),
	HISI_SAS_DEBUGFS_REG(COMPL_Q_0_DEPTH),
	HISI_SAS_DEBUGFS_REG(COMPL_Q_0_WR_PTR),
	HISI_SAS_DEBUGFS_REG(COMPL_Q_0_RD_PTR),
	HISI_SAS_DEBUGFS_REG(AWQOS_AWCACHE_CFG),
	HISI_SAS_DEBUGFS_REG(ARQOS_ARCACHE_CFG),
	HISI_SAS_DEBUGFS_REG(HILINK_ERR_DFX),
	HISI_SAS_DEBUGFS_REG(SAS_GPIO_CFG_0),
	HISI_SAS_DEBUGFS_REG(SAS_GPIO_CFG_1),
	HISI_SAS_DEBUGFS_REG(SAS_GPIO_TX_0_1),
	HISI_SAS_DEBUGFS_REG(SAS_CFG_DRIVE_VLD),
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hisi_sas_debugfs_reg debugfs_global_reg = अणु
	.lu = debugfs_global_reg_lu,
	.count = 0x800,
पूर्ण;

अटल स्थिर काष्ठा hisi_sas_debugfs_reg_lu debugfs_axi_reg_lu[] = अणु
	HISI_SAS_DEBUGFS_REG(AM_CFG_MAX_TRANS),
	HISI_SAS_DEBUGFS_REG(AM_CFG_SINGLE_PORT_MAX_TRANS),
	HISI_SAS_DEBUGFS_REG(AXI_CFG),
	HISI_SAS_DEBUGFS_REG(AM_ROB_ECC_ERR_ADDR),
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hisi_sas_debugfs_reg debugfs_axi_reg = अणु
	.lu = debugfs_axi_reg_lu,
	.count = 0x61,
	.base_off = AXI_MASTER_CFG_BASE,
पूर्ण;

अटल स्थिर काष्ठा hisi_sas_debugfs_reg_lu debugfs_ras_reg_lu[] = अणु
	HISI_SAS_DEBUGFS_REG(SAS_RAS_INTR0),
	HISI_SAS_DEBUGFS_REG(SAS_RAS_INTR1),
	HISI_SAS_DEBUGFS_REG(SAS_RAS_INTR0_MASK),
	HISI_SAS_DEBUGFS_REG(SAS_RAS_INTR1_MASK),
	HISI_SAS_DEBUGFS_REG(CFG_SAS_RAS_INTR_MASK),
	HISI_SAS_DEBUGFS_REG(SAS_RAS_INTR2),
	HISI_SAS_DEBUGFS_REG(SAS_RAS_INTR2_MASK),
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hisi_sas_debugfs_reg debugfs_ras_reg = अणु
	.lu = debugfs_ras_reg_lu,
	.count = 0x10,
	.base_off = RAS_BASE,
पूर्ण;

अटल व्योम debugfs_snapshot_prepare_v3_hw(काष्ठा hisi_hba *hisi_hba)
अणु
	set_bit(HISI_SAS_REJECT_CMD_BIT, &hisi_hba->flags);

	hisi_sas_ग_लिखो32(hisi_hba, DLVRY_QUEUE_ENABLE, 0);

	रुको_cmds_complete_समयout_v3_hw(hisi_hba, 100, 5000);

	hisi_sas_sync_irqs(hisi_hba);
पूर्ण

अटल व्योम debugfs_snapshot_restore_v3_hw(काष्ठा hisi_hba *hisi_hba)
अणु
	hisi_sas_ग_लिखो32(hisi_hba, DLVRY_QUEUE_ENABLE,
			 (u32)((1ULL << hisi_hba->queue_count) - 1));

	clear_bit(HISI_SAS_REJECT_CMD_BIT, &hisi_hba->flags);
पूर्ण

अटल व्योम पढ़ो_iost_itct_cache_v3_hw(काष्ठा hisi_hba *hisi_hba,
				       क्रमागत hisi_sas_debugfs_cache_type type,
				       u32 *cache)
अणु
	u32 cache_dw_size = HISI_SAS_IOST_ITCT_CACHE_DW_SZ *
			    HISI_SAS_IOST_ITCT_CACHE_NUM;
	काष्ठा device *dev = hisi_hba->dev;
	u32 *buf = cache;
	u32 i, val;

	hisi_sas_ग_लिखो32(hisi_hba, TAB_RD_TYPE, type);

	क्रम (i = 0; i < HISI_SAS_IOST_ITCT_CACHE_DW_SZ; i++) अणु
		val = hisi_sas_पढ़ो32(hisi_hba, TAB_DFX);
		अगर (val == 0xffffffff)
			अवरोध;
	पूर्ण

	अगर (val != 0xffffffff) अणु
		dev_err(dev, "Issue occurred in reading IOST/ITCT cache!\n");
		वापस;
	पूर्ण

	स_रखो(buf, 0, cache_dw_size * 4);
	buf[0] = val;

	क्रम (i = 1; i < cache_dw_size; i++)
		buf[i] = hisi_sas_पढ़ो32(hisi_hba, TAB_DFX);
पूर्ण

अटल व्योम hisi_sas_bist_test_prep_v3_hw(काष्ठा hisi_hba *hisi_hba)
अणु
	u32 reg_val;
	पूर्णांक phy_no = hisi_hba->debugfs_bist_phy_no;
	पूर्णांक i;

	/* disable PHY */
	hisi_sas_phy_enable(hisi_hba, phy_no, 0);

	/* update FFE */
	क्रम (i = 0; i < FFE_CFG_MAX; i++)
		hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, TXDEEMPH_G1 + (i * 0x4),
				     hisi_hba->debugfs_bist_ffe[phy_no][i]);

	/* disable ALOS */
	reg_val = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no, SERDES_CFG);
	reg_val |= CFG_ALOS_CHK_DISABLE_MSK;
	hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, SERDES_CFG, reg_val);
पूर्ण

अटल व्योम hisi_sas_bist_test_restore_v3_hw(काष्ठा hisi_hba *hisi_hba)
अणु
	u32 reg_val;
	पूर्णांक phy_no = hisi_hba->debugfs_bist_phy_no;

	/* disable loopback */
	reg_val = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no, SAS_PHY_BIST_CTRL);
	reg_val &= ~(CFG_RX_BIST_EN_MSK | CFG_TX_BIST_EN_MSK |
		     CFG_BIST_TEST_MSK);
	hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, SAS_PHY_BIST_CTRL, reg_val);

	/* enable ALOS */
	reg_val = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no, SERDES_CFG);
	reg_val &= ~CFG_ALOS_CHK_DISABLE_MSK;
	hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, SERDES_CFG, reg_val);

	/* restore the linkrate */
	reg_val = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no, PROG_PHY_LINK_RATE);
	/* init OOB link rate as 1.5 Gbits */
	reg_val &= ~CFG_PROG_OOB_PHY_LINK_RATE_MSK;
	reg_val |= (0x8 << CFG_PROG_OOB_PHY_LINK_RATE_OFF);
	hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, PROG_PHY_LINK_RATE, reg_val);

	/* enable PHY */
	hisi_sas_phy_enable(hisi_hba, phy_no, 1);
पूर्ण

#घोषणा SAS_PHY_BIST_CODE_INIT	0x1
#घोषणा SAS_PHY_BIST_CODE1_INIT	0X80
अटल पूर्णांक debugfs_set_bist_v3_hw(काष्ठा hisi_hba *hisi_hba, bool enable)
अणु
	u32 reg_val, mode_पंचांगp;
	u32 linkrate = hisi_hba->debugfs_bist_linkrate;
	u32 phy_no = hisi_hba->debugfs_bist_phy_no;
	u32 *ffe = hisi_hba->debugfs_bist_ffe[phy_no];
	u32 code_mode = hisi_hba->debugfs_bist_code_mode;
	u32 path_mode = hisi_hba->debugfs_bist_mode;
	u32 *fix_code = &hisi_hba->debugfs_bist_fixed_code[0];
	काष्ठा device *dev = hisi_hba->dev;

	dev_info(dev, "BIST info:phy%d link_rate=%d code_mode=%d path_mode=%d ffe={0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x} fixed_code={0x%x, 0x%x}\n",
		 phy_no, linkrate, code_mode, path_mode,
		 ffe[FFE_SAS_1_5_GBPS], ffe[FFE_SAS_3_0_GBPS],
		 ffe[FFE_SAS_6_0_GBPS], ffe[FFE_SAS_12_0_GBPS],
		 ffe[FFE_SATA_1_5_GBPS], ffe[FFE_SATA_3_0_GBPS],
		 ffe[FFE_SATA_6_0_GBPS], fix_code[FIXED_CODE],
		 fix_code[FIXED_CODE_1]);
	mode_पंचांगp = path_mode ? 2 : 1;
	अगर (enable) अणु
		/* some preparations beक्रमe bist test */
		hisi_sas_bist_test_prep_v3_hw(hisi_hba);

		/* set linkrate of bit test*/
		reg_val = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no,
					      PROG_PHY_LINK_RATE);
		reg_val &= ~CFG_PROG_OOB_PHY_LINK_RATE_MSK;
		reg_val |= (linkrate << CFG_PROG_OOB_PHY_LINK_RATE_OFF);
		hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, PROG_PHY_LINK_RATE,
				     reg_val);

		/* set code mode of bit test */
		reg_val = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no,
					      SAS_PHY_BIST_CTRL);
		reg_val &= ~(CFG_BIST_MODE_SEL_MSK | CFG_LOOP_TEST_MODE_MSK |
			     CFG_RX_BIST_EN_MSK | CFG_TX_BIST_EN_MSK |
			     CFG_BIST_TEST_MSK);
		reg_val |= ((code_mode << CFG_BIST_MODE_SEL_OFF) |
			    (mode_पंचांगp << CFG_LOOP_TEST_MODE_OFF) |
			    CFG_BIST_TEST_MSK);
		hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, SAS_PHY_BIST_CTRL,
				     reg_val);

		/* set the bist init value */
		अगर (code_mode == HISI_SAS_BIST_CODE_MODE_FIXED_DATA) अणु
			reg_val = hisi_hba->debugfs_bist_fixed_code[0];
			hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no,
					     SAS_PHY_BIST_CODE, reg_val);

			reg_val = hisi_hba->debugfs_bist_fixed_code[1];
			hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no,
					     SAS_PHY_BIST_CODE1, reg_val);
		पूर्ण अन्यथा अणु
			hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no,
					     SAS_PHY_BIST_CODE,
					     SAS_PHY_BIST_CODE_INIT);
			hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no,
					     SAS_PHY_BIST_CODE1,
					     SAS_PHY_BIST_CODE1_INIT);
		पूर्ण

		mdelay(100);
		reg_val |= (CFG_RX_BIST_EN_MSK | CFG_TX_BIST_EN_MSK);
		hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, SAS_PHY_BIST_CTRL,
				     reg_val);

		/* clear error bit */
		mdelay(100);
		hisi_sas_phy_पढ़ो32(hisi_hba, phy_no, SAS_BIST_ERR_CNT);
	पूर्ण अन्यथा अणु
		/* disable bist test and recover it */
		hisi_hba->debugfs_bist_cnt += hisi_sas_phy_पढ़ो32(hisi_hba,
				phy_no, SAS_BIST_ERR_CNT);
		hisi_sas_bist_test_restore_v3_hw(hisi_hba);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hisi_sas_map_queues(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा hisi_hba *hisi_hba = shost_priv(shost);
	काष्ठा blk_mq_queue_map *qmap = &shost->tag_set.map[HCTX_TYPE_DEFAULT];

	वापस blk_mq_pci_map_queues(qmap, hisi_hba->pci_dev,
				     BASE_VECTORS_V3_HW);
पूर्ण

अटल काष्ठा scsi_host_ढाँचा sht_v3_hw = अणु
	.name			= DRV_NAME,
	.proc_name		= DRV_NAME,
	.module			= THIS_MODULE,
	.queuecommand		= sas_queuecommand,
	.dma_need_drain		= ata_scsi_dma_need_drain,
	.target_alloc		= sas_target_alloc,
	.slave_configure	= slave_configure_v3_hw,
	.scan_finished		= hisi_sas_scan_finished,
	.scan_start		= hisi_sas_scan_start,
	.map_queues		= hisi_sas_map_queues,
	.change_queue_depth	= sas_change_queue_depth,
	.bios_param		= sas_bios_param,
	.this_id		= -1,
	.sg_tablesize		= HISI_SAS_SGE_PAGE_CNT,
	.sg_prot_tablesize	= HISI_SAS_SGE_PAGE_CNT,
	.max_sectors		= SCSI_DEFAULT_MAX_SECTORS,
	.eh_device_reset_handler = sas_eh_device_reset_handler,
	.eh_target_reset_handler = sas_eh_target_reset_handler,
	.target_destroy		= sas_target_destroy,
	.ioctl			= sas_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl		= sas_ioctl,
#पूर्ण_अगर
	.shost_attrs		= host_attrs_v3_hw,
	.tag_alloc_policy	= BLK_TAG_ALLOC_RR,
	.host_reset             = hisi_sas_host_reset,
	.host_tagset		= 1,
पूर्ण;

अटल स्थिर काष्ठा hisi_sas_hw hisi_sas_v3_hw = अणु
	.setup_itct = setup_itct_v3_hw,
	.get_wideport_biपंचांगap = get_wideport_biपंचांगap_v3_hw,
	.complete_hdr_size = माप(काष्ठा hisi_sas_complete_v3_hdr),
	.clear_itct = clear_itct_v3_hw,
	.sl_notअगरy_ssp = sl_notअगरy_ssp_v3_hw,
	.prep_ssp = prep_ssp_v3_hw,
	.prep_smp = prep_smp_v3_hw,
	.prep_stp = prep_ata_v3_hw,
	.prep_पात = prep_पात_v3_hw,
	.start_delivery = start_delivery_v3_hw,
	.phys_init = phys_init_v3_hw,
	.phy_start = start_phy_v3_hw,
	.phy_disable = disable_phy_v3_hw,
	.phy_hard_reset = phy_hard_reset_v3_hw,
	.phy_get_max_linkrate = phy_get_max_linkrate_v3_hw,
	.phy_set_linkrate = phy_set_linkrate_v3_hw,
	.dereg_device = dereg_device_v3_hw,
	.soft_reset = soft_reset_v3_hw,
	.get_phys_state = get_phys_state_v3_hw,
	.get_events = phy_get_events_v3_hw,
	.ग_लिखो_gpio = ग_लिखो_gpio_v3_hw,
	.रुको_cmds_complete_समयout = रुको_cmds_complete_समयout_v3_hw,
	.debugfs_snapshot_regs = debugfs_snapshot_regs_v3_hw,
पूर्ण;

अटल काष्ठा Scsi_Host *
hisi_sas_shost_alloc_pci(काष्ठा pci_dev *pdev)
अणु
	काष्ठा Scsi_Host *shost;
	काष्ठा hisi_hba *hisi_hba;
	काष्ठा device *dev = &pdev->dev;

	shost = scsi_host_alloc(&sht_v3_hw, माप(*hisi_hba));
	अगर (!shost) अणु
		dev_err(dev, "shost alloc failed\n");
		वापस शून्य;
	पूर्ण
	hisi_hba = shost_priv(shost);

	INIT_WORK(&hisi_hba->rst_work, hisi_sas_rst_work_handler);
	INIT_WORK(&hisi_hba->debugfs_work, debugfs_work_handler_v3_hw);
	hisi_hba->hw = &hisi_sas_v3_hw;
	hisi_hba->pci_dev = pdev;
	hisi_hba->dev = dev;
	hisi_hba->shost = shost;
	SHOST_TO_SAS_HA(shost) = &hisi_hba->sha;

	अगर (prot_mask & ~HISI_SAS_PROT_MASK)
		dev_err(dev, "unsupported protection mask 0x%x, using default (0x0)\n",
			prot_mask);
	अन्यथा
		hisi_hba->prot_mask = prot_mask;

	अगर (hisi_sas_get_fw_info(hisi_hba) < 0)
		जाओ err_out;

	अगर (hisi_sas_alloc(hisi_hba)) अणु
		hisi_sas_मुक्त(hisi_hba);
		जाओ err_out;
	पूर्ण

	वापस shost;
err_out:
	scsi_host_put(shost);
	dev_err(dev, "shost alloc failed\n");
	वापस शून्य;
पूर्ण

अटल व्योम debugfs_snapshot_cq_reg_v3_hw(काष्ठा hisi_hba *hisi_hba)
अणु
	पूर्णांक queue_entry_size = hisi_hba->hw->complete_hdr_size;
	पूर्णांक dump_index = hisi_hba->debugfs_dump_index;
	पूर्णांक i;

	क्रम (i = 0; i < hisi_hba->queue_count; i++)
		स_नकल(hisi_hba->debugfs_cq[dump_index][i].complete_hdr,
		       hisi_hba->complete_hdr[i],
		       HISI_SAS_QUEUE_SLOTS * queue_entry_size);
पूर्ण

अटल व्योम debugfs_snapshot_dq_reg_v3_hw(काष्ठा hisi_hba *hisi_hba)
अणु
	पूर्णांक queue_entry_size = माप(काष्ठा hisi_sas_cmd_hdr);
	पूर्णांक dump_index = hisi_hba->debugfs_dump_index;
	पूर्णांक i;

	क्रम (i = 0; i < hisi_hba->queue_count; i++) अणु
		काष्ठा hisi_sas_cmd_hdr *debugfs_cmd_hdr, *cmd_hdr;
		पूर्णांक j;

		debugfs_cmd_hdr = hisi_hba->debugfs_dq[dump_index][i].hdr;
		cmd_hdr = hisi_hba->cmd_hdr[i];

		क्रम (j = 0; j < HISI_SAS_QUEUE_SLOTS; j++)
			स_नकल(&debugfs_cmd_hdr[j], &cmd_hdr[j],
			       queue_entry_size);
	पूर्ण
पूर्ण

अटल व्योम debugfs_snapshot_port_reg_v3_hw(काष्ठा hisi_hba *hisi_hba)
अणु
	पूर्णांक dump_index = hisi_hba->debugfs_dump_index;
	स्थिर काष्ठा hisi_sas_debugfs_reg *port = &debugfs_port_reg;
	पूर्णांक i, phy_cnt;
	u32 offset;
	u32 *databuf;

	क्रम (phy_cnt = 0; phy_cnt < hisi_hba->n_phy; phy_cnt++) अणु
		databuf = hisi_hba->debugfs_port_reg[dump_index][phy_cnt].data;
		क्रम (i = 0; i < port->count; i++, databuf++) अणु
			offset = port->base_off + 4 * i;
			*databuf = hisi_sas_phy_पढ़ो32(hisi_hba, phy_cnt,
						       offset);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम debugfs_snapshot_global_reg_v3_hw(काष्ठा hisi_hba *hisi_hba)
अणु
	पूर्णांक dump_index = hisi_hba->debugfs_dump_index;
	u32 *databuf = hisi_hba->debugfs_regs[dump_index][DEBUGFS_GLOBAL].data;
	पूर्णांक i;

	क्रम (i = 0; i < debugfs_axi_reg.count; i++, databuf++)
		*databuf = hisi_sas_पढ़ो32(hisi_hba, 4 * i);
पूर्ण

अटल व्योम debugfs_snapshot_axi_reg_v3_hw(काष्ठा hisi_hba *hisi_hba)
अणु
	पूर्णांक dump_index = hisi_hba->debugfs_dump_index;
	u32 *databuf = hisi_hba->debugfs_regs[dump_index][DEBUGFS_AXI].data;
	स्थिर काष्ठा hisi_sas_debugfs_reg *axi = &debugfs_axi_reg;
	पूर्णांक i;

	क्रम (i = 0; i < axi->count; i++, databuf++)
		*databuf = hisi_sas_पढ़ो32(hisi_hba, 4 * i + axi->base_off);
पूर्ण

अटल व्योम debugfs_snapshot_ras_reg_v3_hw(काष्ठा hisi_hba *hisi_hba)
अणु
	पूर्णांक dump_index = hisi_hba->debugfs_dump_index;
	u32 *databuf = hisi_hba->debugfs_regs[dump_index][DEBUGFS_RAS].data;
	स्थिर काष्ठा hisi_sas_debugfs_reg *ras = &debugfs_ras_reg;
	पूर्णांक i;

	क्रम (i = 0; i < ras->count; i++, databuf++)
		*databuf = hisi_sas_पढ़ो32(hisi_hba, 4 * i + ras->base_off);
पूर्ण

अटल व्योम debugfs_snapshot_itct_reg_v3_hw(काष्ठा hisi_hba *hisi_hba)
अणु
	पूर्णांक dump_index = hisi_hba->debugfs_dump_index;
	व्योम *cachebuf = hisi_hba->debugfs_itct_cache[dump_index].cache;
	व्योम *databuf = hisi_hba->debugfs_itct[dump_index].itct;
	काष्ठा hisi_sas_itct *itct;
	पूर्णांक i;

	पढ़ो_iost_itct_cache_v3_hw(hisi_hba, HISI_SAS_ITCT_CACHE, cachebuf);

	itct = hisi_hba->itct;

	क्रम (i = 0; i < HISI_SAS_MAX_ITCT_ENTRIES; i++, itct++) अणु
		स_नकल(databuf, itct, माप(काष्ठा hisi_sas_itct));
		databuf += माप(काष्ठा hisi_sas_itct);
	पूर्ण
पूर्ण

अटल व्योम debugfs_snapshot_iost_reg_v3_hw(काष्ठा hisi_hba *hisi_hba)
अणु
	पूर्णांक dump_index = hisi_hba->debugfs_dump_index;
	पूर्णांक max_command_entries = HISI_SAS_MAX_COMMANDS;
	व्योम *cachebuf = hisi_hba->debugfs_iost_cache[dump_index].cache;
	व्योम *databuf = hisi_hba->debugfs_iost[dump_index].iost;
	काष्ठा hisi_sas_iost *iost;
	पूर्णांक i;

	पढ़ो_iost_itct_cache_v3_hw(hisi_hba, HISI_SAS_IOST_CACHE, cachebuf);

	iost = hisi_hba->iost;

	क्रम (i = 0; i < max_command_entries; i++, iost++) अणु
		स_नकल(databuf, iost, माप(काष्ठा hisi_sas_iost));
		databuf += माप(काष्ठा hisi_sas_iost);
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *
debugfs_to_reg_name_v3_hw(पूर्णांक off, पूर्णांक base_off,
			  स्थिर काष्ठा hisi_sas_debugfs_reg_lu *lu)
अणु
	क्रम (; lu->name; lu++) अणु
		अगर (off == lu->off - base_off)
			वापस lu->name;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम debugfs_prपूर्णांक_reg_v3_hw(u32 *regs_val, काष्ठा seq_file *s,
				    स्थिर काष्ठा hisi_sas_debugfs_reg *reg)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < reg->count; i++) अणु
		पूर्णांक off = i * 4;
		स्थिर अक्षर *name;

		name = debugfs_to_reg_name_v3_hw(off, reg->base_off,
						 reg->lu);

		अगर (name)
			seq_म_लिखो(s, "0x%08x 0x%08x %s\n", off,
				   regs_val[i], name);
		अन्यथा
			seq_म_लिखो(s, "0x%08x 0x%08x\n", off,
				   regs_val[i]);
	पूर्ण
पूर्ण

अटल पूर्णांक debugfs_global_v3_hw_show(काष्ठा seq_file *s, व्योम *p)
अणु
	काष्ठा hisi_sas_debugfs_regs *global = s->निजी;

	debugfs_prपूर्णांक_reg_v3_hw(global->data, s,
				&debugfs_global_reg);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(debugfs_global_v3_hw);

अटल पूर्णांक debugfs_axi_v3_hw_show(काष्ठा seq_file *s, व्योम *p)
अणु
	काष्ठा hisi_sas_debugfs_regs *axi = s->निजी;

	debugfs_prपूर्णांक_reg_v3_hw(axi->data, s,
				&debugfs_axi_reg);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(debugfs_axi_v3_hw);

अटल पूर्णांक debugfs_ras_v3_hw_show(काष्ठा seq_file *s, व्योम *p)
अणु
	काष्ठा hisi_sas_debugfs_regs *ras = s->निजी;

	debugfs_prपूर्णांक_reg_v3_hw(ras->data, s,
				&debugfs_ras_reg);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(debugfs_ras_v3_hw);

अटल पूर्णांक debugfs_port_v3_hw_show(काष्ठा seq_file *s, व्योम *p)
अणु
	काष्ठा hisi_sas_debugfs_port *port = s->निजी;
	स्थिर काष्ठा hisi_sas_debugfs_reg *reg_port = &debugfs_port_reg;

	debugfs_prपूर्णांक_reg_v3_hw(port->data, s, reg_port);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(debugfs_port_v3_hw);

अटल व्योम debugfs_show_row_64_v3_hw(काष्ठा seq_file *s, पूर्णांक index,
				      पूर्णांक sz, __le64 *ptr)
अणु
	पूर्णांक i;

	/* completion header size not fixed per HW version */
	seq_म_लिखो(s, "index %04d:\n\t", index);
	क्रम (i = 1; i <= sz / 8; i++, ptr++) अणु
		seq_म_लिखो(s, " 0x%016llx", le64_to_cpu(*ptr));
		अगर (!(i % 2))
			seq_माला_दो(s, "\n\t");
	पूर्ण

	seq_माला_दो(s, "\n");
पूर्ण

अटल व्योम debugfs_show_row_32_v3_hw(काष्ठा seq_file *s, पूर्णांक index,
				      पूर्णांक sz, __le32 *ptr)
अणु
	पूर्णांक i;

	/* completion header size not fixed per HW version */
	seq_म_लिखो(s, "index %04d:\n\t", index);
	क्रम (i = 1; i <= sz / 4; i++, ptr++) अणु
		seq_म_लिखो(s, " 0x%08x", le32_to_cpu(*ptr));
		अगर (!(i % 4))
			seq_माला_दो(s, "\n\t");
	पूर्ण
	seq_माला_दो(s, "\n");
पूर्ण

अटल व्योम debugfs_cq_show_slot_v3_hw(काष्ठा seq_file *s, पूर्णांक slot,
				       काष्ठा hisi_sas_debugfs_cq *debugfs_cq)
अणु
	काष्ठा hisi_sas_cq *cq = debugfs_cq->cq;
	काष्ठा hisi_hba *hisi_hba = cq->hisi_hba;
	__le32 *complete_hdr = debugfs_cq->complete_hdr +
			       (hisi_hba->hw->complete_hdr_size * slot);

	debugfs_show_row_32_v3_hw(s, slot,
				  hisi_hba->hw->complete_hdr_size,
				  complete_hdr);
पूर्ण

अटल पूर्णांक debugfs_cq_v3_hw_show(काष्ठा seq_file *s, व्योम *p)
अणु
	काष्ठा hisi_sas_debugfs_cq *debugfs_cq = s->निजी;
	पूर्णांक slot;

	क्रम (slot = 0; slot < HISI_SAS_QUEUE_SLOTS; slot++)
		debugfs_cq_show_slot_v3_hw(s, slot, debugfs_cq);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(debugfs_cq_v3_hw);

अटल व्योम debugfs_dq_show_slot_v3_hw(काष्ठा seq_file *s, पूर्णांक slot,
				       व्योम *dq_ptr)
अणु
	काष्ठा hisi_sas_debugfs_dq *debugfs_dq = dq_ptr;
	व्योम *cmd_queue = debugfs_dq->hdr;
	__le32 *cmd_hdr = cmd_queue +
		माप(काष्ठा hisi_sas_cmd_hdr) * slot;

	debugfs_show_row_32_v3_hw(s, slot, माप(काष्ठा hisi_sas_cmd_hdr),
				  cmd_hdr);
पूर्ण

अटल पूर्णांक debugfs_dq_v3_hw_show(काष्ठा seq_file *s, व्योम *p)
अणु
	पूर्णांक slot;

	क्रम (slot = 0; slot < HISI_SAS_QUEUE_SLOTS; slot++)
		debugfs_dq_show_slot_v3_hw(s, slot, s->निजी);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(debugfs_dq_v3_hw);

अटल पूर्णांक debugfs_iost_v3_hw_show(काष्ठा seq_file *s, व्योम *p)
अणु
	काष्ठा hisi_sas_debugfs_iost *debugfs_iost = s->निजी;
	काष्ठा hisi_sas_iost *iost = debugfs_iost->iost;
	पूर्णांक i, max_command_entries = HISI_SAS_MAX_COMMANDS;

	क्रम (i = 0; i < max_command_entries; i++, iost++) अणु
		__le64 *data = &iost->qw0;

		debugfs_show_row_64_v3_hw(s, i, माप(*iost), data);
	पूर्ण

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(debugfs_iost_v3_hw);

अटल पूर्णांक debugfs_iost_cache_v3_hw_show(काष्ठा seq_file *s, व्योम *p)
अणु
	काष्ठा hisi_sas_debugfs_iost_cache *debugfs_iost_cache = s->निजी;
	काष्ठा hisi_sas_iost_itct_cache *iost_cache =
						debugfs_iost_cache->cache;
	u32 cache_size = HISI_SAS_IOST_ITCT_CACHE_DW_SZ * 4;
	पूर्णांक i, tab_idx;
	__le64 *iost;

	क्रम (i = 0; i < HISI_SAS_IOST_ITCT_CACHE_NUM; i++, iost_cache++) अणु
		/*
		 * Data काष्ठा of IOST cache:
		 * Data[1]: BIT0~15: Table index
		 *	    Bit16:   Valid mask
		 * Data[2]~[9]: IOST table
		 */
		tab_idx = (iost_cache->data[1] & 0xffff);
		iost = (__le64 *)iost_cache;

		debugfs_show_row_64_v3_hw(s, tab_idx, cache_size, iost);
	पूर्ण

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(debugfs_iost_cache_v3_hw);

अटल पूर्णांक debugfs_itct_v3_hw_show(काष्ठा seq_file *s, व्योम *p)
अणु
	पूर्णांक i;
	काष्ठा hisi_sas_debugfs_itct *debugfs_itct = s->निजी;
	काष्ठा hisi_sas_itct *itct = debugfs_itct->itct;

	क्रम (i = 0; i < HISI_SAS_MAX_ITCT_ENTRIES; i++, itct++) अणु
		__le64 *data = &itct->qw0;

		debugfs_show_row_64_v3_hw(s, i, माप(*itct), data);
	पूर्ण

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(debugfs_itct_v3_hw);

अटल पूर्णांक debugfs_itct_cache_v3_hw_show(काष्ठा seq_file *s, व्योम *p)
अणु
	काष्ठा hisi_sas_debugfs_itct_cache *debugfs_itct_cache = s->निजी;
	काष्ठा hisi_sas_iost_itct_cache *itct_cache =
						debugfs_itct_cache->cache;
	u32 cache_size = HISI_SAS_IOST_ITCT_CACHE_DW_SZ * 4;
	पूर्णांक i, tab_idx;
	__le64 *itct;

	क्रम (i = 0; i < HISI_SAS_IOST_ITCT_CACHE_NUM; i++, itct_cache++) अणु
		/*
		 * Data काष्ठा of ITCT cache:
		 * Data[1]: BIT0~15: Table index
		 *	    Bit16:   Valid mask
		 * Data[2]~[9]: ITCT table
		 */
		tab_idx = itct_cache->data[1] & 0xffff;
		itct = (__le64 *)itct_cache;

		debugfs_show_row_64_v3_hw(s, tab_idx, cache_size, itct);
	पूर्ण

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(debugfs_itct_cache_v3_hw);

अटल व्योम debugfs_create_files_v3_hw(काष्ठा hisi_hba *hisi_hba)
अणु
	u64 *debugfs_बारtamp;
	पूर्णांक dump_index = hisi_hba->debugfs_dump_index;
	काष्ठा dentry *dump_dentry;
	काष्ठा dentry *dentry;
	अक्षर name[256];
	पूर्णांक p;
	पूर्णांक c;
	पूर्णांक d;

	snम_लिखो(name, 256, "%d", dump_index);

	dump_dentry = debugfs_create_dir(name, hisi_hba->debugfs_dump_dentry);

	debugfs_बारtamp = &hisi_hba->debugfs_बारtamp[dump_index];

	debugfs_create_u64("timestamp", 0400, dump_dentry,
			   debugfs_बारtamp);

	debugfs_create_file("global", 0400, dump_dentry,
			    &hisi_hba->debugfs_regs[dump_index][DEBUGFS_GLOBAL],
			    &debugfs_global_v3_hw_fops);

	/* Create port dir and files */
	dentry = debugfs_create_dir("port", dump_dentry);
	क्रम (p = 0; p < hisi_hba->n_phy; p++) अणु
		snम_लिखो(name, 256, "%d", p);

		debugfs_create_file(name, 0400, dentry,
				    &hisi_hba->debugfs_port_reg[dump_index][p],
				    &debugfs_port_v3_hw_fops);
	पूर्ण

	/* Create CQ dir and files */
	dentry = debugfs_create_dir("cq", dump_dentry);
	क्रम (c = 0; c < hisi_hba->queue_count; c++) अणु
		snम_लिखो(name, 256, "%d", c);

		debugfs_create_file(name, 0400, dentry,
				    &hisi_hba->debugfs_cq[dump_index][c],
				    &debugfs_cq_v3_hw_fops);
	पूर्ण

	/* Create DQ dir and files */
	dentry = debugfs_create_dir("dq", dump_dentry);
	क्रम (d = 0; d < hisi_hba->queue_count; d++) अणु
		snम_लिखो(name, 256, "%d", d);

		debugfs_create_file(name, 0400, dentry,
				    &hisi_hba->debugfs_dq[dump_index][d],
				    &debugfs_dq_v3_hw_fops);
	पूर्ण

	debugfs_create_file("iost", 0400, dump_dentry,
			    &hisi_hba->debugfs_iost[dump_index],
			    &debugfs_iost_v3_hw_fops);

	debugfs_create_file("iost_cache", 0400, dump_dentry,
			    &hisi_hba->debugfs_iost_cache[dump_index],
			    &debugfs_iost_cache_v3_hw_fops);

	debugfs_create_file("itct", 0400, dump_dentry,
			    &hisi_hba->debugfs_itct[dump_index],
			    &debugfs_itct_v3_hw_fops);

	debugfs_create_file("itct_cache", 0400, dump_dentry,
			    &hisi_hba->debugfs_itct_cache[dump_index],
			    &debugfs_itct_cache_v3_hw_fops);

	debugfs_create_file("axi", 0400, dump_dentry,
			    &hisi_hba->debugfs_regs[dump_index][DEBUGFS_AXI],
			    &debugfs_axi_v3_hw_fops);

	debugfs_create_file("ras", 0400, dump_dentry,
			    &hisi_hba->debugfs_regs[dump_index][DEBUGFS_RAS],
			    &debugfs_ras_v3_hw_fops);
पूर्ण

अटल व्योम debugfs_snapshot_regs_v3_hw(काष्ठा hisi_hba *hisi_hba)
अणु
	पूर्णांक debugfs_dump_index = hisi_hba->debugfs_dump_index;
	काष्ठा device *dev = hisi_hba->dev;
	u64 बारtamp = local_घड़ी();

	अगर (debugfs_dump_index >= hisi_sas_debugfs_dump_count) अणु
		dev_warn(dev, "dump count exceeded!\n");
		वापस;
	पूर्ण

	करो_भाग(बारtamp, NSEC_PER_MSEC);
	hisi_hba->debugfs_बारtamp[debugfs_dump_index] = बारtamp;
	hisi_hba->debugfs_dump_index++;

	debugfs_snapshot_prepare_v3_hw(hisi_hba);

	debugfs_snapshot_global_reg_v3_hw(hisi_hba);
	debugfs_snapshot_port_reg_v3_hw(hisi_hba);
	debugfs_snapshot_axi_reg_v3_hw(hisi_hba);
	debugfs_snapshot_ras_reg_v3_hw(hisi_hba);
	debugfs_snapshot_cq_reg_v3_hw(hisi_hba);
	debugfs_snapshot_dq_reg_v3_hw(hisi_hba);
	debugfs_snapshot_itct_reg_v3_hw(hisi_hba);
	debugfs_snapshot_iost_reg_v3_hw(hisi_hba);

	debugfs_create_files_v3_hw(hisi_hba);

	debugfs_snapshot_restore_v3_hw(hisi_hba);
पूर्ण

अटल sमाप_प्रकार debugfs_trigger_dump_v3_hw_ग_लिखो(काष्ठा file *file,
						स्थिर अक्षर __user *user_buf,
						माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा hisi_hba *hisi_hba = file->f_inode->i_निजी;
	अक्षर buf[8];

	अगर (hisi_hba->debugfs_dump_index >= hisi_sas_debugfs_dump_count)
		वापस -EFAULT;

	अगर (count > 8)
		वापस -EFAULT;

	अगर (copy_from_user(buf, user_buf, count))
		वापस -EFAULT;

	अगर (buf[0] != '1')
		वापस -EFAULT;

	queue_work(hisi_hba->wq, &hisi_hba->debugfs_work);

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations debugfs_trigger_dump_v3_hw_fops = अणु
	.ग_लिखो = &debugfs_trigger_dump_v3_hw_ग_लिखो,
	.owner = THIS_MODULE,
पूर्ण;

क्रमागत अणु
	HISI_SAS_BIST_LOOPBACK_MODE_DIGITAL = 0,
	HISI_SAS_BIST_LOOPBACK_MODE_SERDES,
	HISI_SAS_BIST_LOOPBACK_MODE_REMOTE,
पूर्ण;

अटल स्थिर काष्ठा अणु
	पूर्णांक		value;
	अक्षर		*name;
पूर्ण debugfs_loop_linkrate_v3_hw[] = अणु
	अणु SAS_LINK_RATE_1_5_GBPS, "1.5 Gbit" पूर्ण,
	अणु SAS_LINK_RATE_3_0_GBPS, "3.0 Gbit" पूर्ण,
	अणु SAS_LINK_RATE_6_0_GBPS, "6.0 Gbit" पूर्ण,
	अणु SAS_LINK_RATE_12_0_GBPS, "12.0 Gbit" पूर्ण,
पूर्ण;

अटल पूर्णांक debugfs_bist_linkrate_v3_hw_show(काष्ठा seq_file *s, व्योम *p)
अणु
	काष्ठा hisi_hba *hisi_hba = s->निजी;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(debugfs_loop_linkrate_v3_hw); i++) अणु
		पूर्णांक match = (hisi_hba->debugfs_bist_linkrate ==
			     debugfs_loop_linkrate_v3_hw[i].value);

		seq_म_लिखो(s, "%s%s%s ", match ? "[" : "",
			   debugfs_loop_linkrate_v3_hw[i].name,
			   match ? "]" : "");
	पूर्ण
	seq_माला_दो(s, "\n");

	वापस 0;
पूर्ण

अटल sमाप_प्रकार debugfs_bist_linkrate_v3_hw_ग_लिखो(काष्ठा file *filp,
						 स्थिर अक्षर __user *buf,
						 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा seq_file *m = filp->निजी_data;
	काष्ठा hisi_hba *hisi_hba = m->निजी;
	अक्षर kbuf[16] = अणुपूर्ण, *pkbuf;
	bool found = false;
	पूर्णांक i;

	अगर (hisi_hba->debugfs_bist_enable)
		वापस -EPERM;

	अगर (count >= माप(kbuf))
		वापस -EOVERFLOW;

	अगर (copy_from_user(kbuf, buf, count))
		वापस -EINVAL;

	pkbuf = म_मालाip(kbuf);

	क्रम (i = 0; i < ARRAY_SIZE(debugfs_loop_linkrate_v3_hw); i++) अणु
		अगर (!म_भेदन(debugfs_loop_linkrate_v3_hw[i].name,
			     pkbuf, 16)) अणु
			hisi_hba->debugfs_bist_linkrate =
				debugfs_loop_linkrate_v3_hw[i].value;
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found)
		वापस -EINVAL;

	वापस count;
पूर्ण

अटल पूर्णांक debugfs_bist_linkrate_v3_hw_खोलो(काष्ठा inode *inode,
					    काष्ठा file *filp)
अणु
	वापस single_खोलो(filp, debugfs_bist_linkrate_v3_hw_show,
			   inode->i_निजी);
पूर्ण

अटल स्थिर काष्ठा file_operations debugfs_bist_linkrate_v3_hw_fops = अणु
	.खोलो = debugfs_bist_linkrate_v3_hw_खोलो,
	.पढ़ो = seq_पढ़ो,
	.ग_लिखो = debugfs_bist_linkrate_v3_hw_ग_लिखो,
	.llseek = seq_lseek,
	.release = single_release,
	.owner = THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा अणु
	पूर्णांक		value;
	अक्षर		*name;
पूर्ण debugfs_loop_code_mode_v3_hw[] = अणु
	अणु HISI_SAS_BIST_CODE_MODE_PRBS7, "PRBS7" पूर्ण,
	अणु HISI_SAS_BIST_CODE_MODE_PRBS23, "PRBS23" पूर्ण,
	अणु HISI_SAS_BIST_CODE_MODE_PRBS31, "PRBS31" पूर्ण,
	अणु HISI_SAS_BIST_CODE_MODE_JTPAT, "JTPAT" पूर्ण,
	अणु HISI_SAS_BIST_CODE_MODE_CJTPAT, "CJTPAT" पूर्ण,
	अणु HISI_SAS_BIST_CODE_MODE_SCRAMBED_0, "SCRAMBED_0" पूर्ण,
	अणु HISI_SAS_BIST_CODE_MODE_TRAIN, "TRAIN" पूर्ण,
	अणु HISI_SAS_BIST_CODE_MODE_TRAIN_DONE, "TRAIN_DONE" पूर्ण,
	अणु HISI_SAS_BIST_CODE_MODE_HFTP, "HFTP" पूर्ण,
	अणु HISI_SAS_BIST_CODE_MODE_MFTP, "MFTP" पूर्ण,
	अणु HISI_SAS_BIST_CODE_MODE_LFTP, "LFTP" पूर्ण,
	अणु HISI_SAS_BIST_CODE_MODE_FIXED_DATA, "FIXED_DATA" पूर्ण,
पूर्ण;

अटल पूर्णांक debugfs_bist_code_mode_v3_hw_show(काष्ठा seq_file *s, व्योम *p)
अणु
	काष्ठा hisi_hba *hisi_hba = s->निजी;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(debugfs_loop_code_mode_v3_hw); i++) अणु
		पूर्णांक match = (hisi_hba->debugfs_bist_code_mode ==
			     debugfs_loop_code_mode_v3_hw[i].value);

		seq_म_लिखो(s, "%s%s%s ", match ? "[" : "",
			   debugfs_loop_code_mode_v3_hw[i].name,
			   match ? "]" : "");
	पूर्ण
	seq_माला_दो(s, "\n");

	वापस 0;
पूर्ण

अटल sमाप_प्रकार debugfs_bist_code_mode_v3_hw_ग_लिखो(काष्ठा file *filp,
						  स्थिर अक्षर __user *buf,
						  माप_प्रकार count,
						  loff_t *ppos)
अणु
	काष्ठा seq_file *m = filp->निजी_data;
	काष्ठा hisi_hba *hisi_hba = m->निजी;
	अक्षर kbuf[16] = अणुपूर्ण, *pkbuf;
	bool found = false;
	पूर्णांक i;

	अगर (hisi_hba->debugfs_bist_enable)
		वापस -EPERM;

	अगर (count >= माप(kbuf))
		वापस -EINVAL;

	अगर (copy_from_user(kbuf, buf, count))
		वापस -EOVERFLOW;

	pkbuf = म_मालाip(kbuf);

	क्रम (i = 0; i < ARRAY_SIZE(debugfs_loop_code_mode_v3_hw); i++) अणु
		अगर (!म_भेदन(debugfs_loop_code_mode_v3_hw[i].name,
			     pkbuf, 16)) अणु
			hisi_hba->debugfs_bist_code_mode =
				debugfs_loop_code_mode_v3_hw[i].value;
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found)
		वापस -EINVAL;

	वापस count;
पूर्ण

अटल पूर्णांक debugfs_bist_code_mode_v3_hw_खोलो(काष्ठा inode *inode,
					     काष्ठा file *filp)
अणु
	वापस single_खोलो(filp, debugfs_bist_code_mode_v3_hw_show,
			   inode->i_निजी);
पूर्ण

अटल स्थिर काष्ठा file_operations debugfs_bist_code_mode_v3_hw_fops = अणु
	.खोलो = debugfs_bist_code_mode_v3_hw_खोलो,
	.पढ़ो = seq_पढ़ो,
	.ग_लिखो = debugfs_bist_code_mode_v3_hw_ग_लिखो,
	.llseek = seq_lseek,
	.release = single_release,
	.owner = THIS_MODULE,
पूर्ण;

अटल sमाप_प्रकार debugfs_bist_phy_v3_hw_ग_लिखो(काष्ठा file *filp,
					    स्थिर अक्षर __user *buf,
					    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा seq_file *m = filp->निजी_data;
	काष्ठा hisi_hba *hisi_hba = m->निजी;
	अचिन्हित पूर्णांक phy_no;
	पूर्णांक val;

	अगर (hisi_hba->debugfs_bist_enable)
		वापस -EPERM;

	val = kstrtouपूर्णांक_from_user(buf, count, 0, &phy_no);
	अगर (val)
		वापस val;

	अगर (phy_no >= hisi_hba->n_phy)
		वापस -EINVAL;

	hisi_hba->debugfs_bist_phy_no = phy_no;

	वापस count;
पूर्ण

अटल पूर्णांक debugfs_bist_phy_v3_hw_show(काष्ठा seq_file *s, व्योम *p)
अणु
	काष्ठा hisi_hba *hisi_hba = s->निजी;

	seq_म_लिखो(s, "%d\n", hisi_hba->debugfs_bist_phy_no);

	वापस 0;
पूर्ण

अटल पूर्णांक debugfs_bist_phy_v3_hw_खोलो(काष्ठा inode *inode,
				       काष्ठा file *filp)
अणु
	वापस single_खोलो(filp, debugfs_bist_phy_v3_hw_show,
			   inode->i_निजी);
पूर्ण

अटल स्थिर काष्ठा file_operations debugfs_bist_phy_v3_hw_fops = अणु
	.खोलो = debugfs_bist_phy_v3_hw_खोलो,
	.पढ़ो = seq_पढ़ो,
	.ग_लिखो = debugfs_bist_phy_v3_hw_ग_लिखो,
	.llseek = seq_lseek,
	.release = single_release,
	.owner = THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा अणु
	पूर्णांक		value;
	अक्षर		*name;
पूर्ण debugfs_loop_modes_v3_hw[] = अणु
	अणु HISI_SAS_BIST_LOOPBACK_MODE_DIGITAL, "digital" पूर्ण,
	अणु HISI_SAS_BIST_LOOPBACK_MODE_SERDES, "serdes" पूर्ण,
	अणु HISI_SAS_BIST_LOOPBACK_MODE_REMOTE, "remote" पूर्ण,
पूर्ण;

अटल पूर्णांक debugfs_bist_mode_v3_hw_show(काष्ठा seq_file *s, व्योम *p)
अणु
	काष्ठा hisi_hba *hisi_hba = s->निजी;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(debugfs_loop_modes_v3_hw); i++) अणु
		पूर्णांक match = (hisi_hba->debugfs_bist_mode ==
			     debugfs_loop_modes_v3_hw[i].value);

		seq_म_लिखो(s, "%s%s%s ", match ? "[" : "",
			   debugfs_loop_modes_v3_hw[i].name,
			   match ? "]" : "");
	पूर्ण
	seq_माला_दो(s, "\n");

	वापस 0;
पूर्ण

अटल sमाप_प्रकार debugfs_bist_mode_v3_hw_ग_लिखो(काष्ठा file *filp,
					     स्थिर अक्षर __user *buf,
					     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा seq_file *m = filp->निजी_data;
	काष्ठा hisi_hba *hisi_hba = m->निजी;
	अक्षर kbuf[16] = अणुपूर्ण, *pkbuf;
	bool found = false;
	पूर्णांक i;

	अगर (hisi_hba->debugfs_bist_enable)
		वापस -EPERM;

	अगर (count >= माप(kbuf))
		वापस -EINVAL;

	अगर (copy_from_user(kbuf, buf, count))
		वापस -EOVERFLOW;

	pkbuf = म_मालाip(kbuf);

	क्रम (i = 0; i < ARRAY_SIZE(debugfs_loop_modes_v3_hw); i++) अणु
		अगर (!म_भेदन(debugfs_loop_modes_v3_hw[i].name, pkbuf, 16)) अणु
			hisi_hba->debugfs_bist_mode =
				debugfs_loop_modes_v3_hw[i].value;
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found)
		वापस -EINVAL;

	वापस count;
पूर्ण

अटल पूर्णांक debugfs_bist_mode_v3_hw_खोलो(काष्ठा inode *inode,
					काष्ठा file *filp)
अणु
	वापस single_खोलो(filp, debugfs_bist_mode_v3_hw_show,
			   inode->i_निजी);
पूर्ण

अटल स्थिर काष्ठा file_operations debugfs_bist_mode_v3_hw_fops = अणु
	.खोलो = debugfs_bist_mode_v3_hw_खोलो,
	.पढ़ो = seq_पढ़ो,
	.ग_लिखो = debugfs_bist_mode_v3_hw_ग_लिखो,
	.llseek = seq_lseek,
	.release = single_release,
	.owner = THIS_MODULE,
पूर्ण;

अटल sमाप_प्रकार debugfs_bist_enable_v3_hw_ग_लिखो(काष्ठा file *filp,
					       स्थिर अक्षर __user *buf,
					       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा seq_file *m = filp->निजी_data;
	काष्ठा hisi_hba *hisi_hba = m->निजी;
	अचिन्हित पूर्णांक enable;
	पूर्णांक val;

	val = kstrtouपूर्णांक_from_user(buf, count, 0, &enable);
	अगर (val)
		वापस val;

	अगर (enable > 1)
		वापस -EINVAL;

	अगर (enable == hisi_hba->debugfs_bist_enable)
		वापस count;

	val = debugfs_set_bist_v3_hw(hisi_hba, enable);
	अगर (val < 0)
		वापस val;

	hisi_hba->debugfs_bist_enable = enable;

	वापस count;
पूर्ण

अटल पूर्णांक debugfs_bist_enable_v3_hw_show(काष्ठा seq_file *s, व्योम *p)
अणु
	काष्ठा hisi_hba *hisi_hba = s->निजी;

	seq_म_लिखो(s, "%d\n", hisi_hba->debugfs_bist_enable);

	वापस 0;
पूर्ण

अटल पूर्णांक debugfs_bist_enable_v3_hw_खोलो(काष्ठा inode *inode,
					  काष्ठा file *filp)
अणु
	वापस single_खोलो(filp, debugfs_bist_enable_v3_hw_show,
			   inode->i_निजी);
पूर्ण

अटल स्थिर काष्ठा file_operations debugfs_bist_enable_v3_hw_fops = अणु
	.खोलो = debugfs_bist_enable_v3_hw_खोलो,
	.पढ़ो = seq_पढ़ो,
	.ग_लिखो = debugfs_bist_enable_v3_hw_ग_लिखो,
	.llseek = seq_lseek,
	.release = single_release,
	.owner = THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा अणु
	अक्षर *name;
पूर्ण debugfs_ffe_name_v3_hw[FFE_CFG_MAX] = अणु
	अणु "SAS_1_5_GBPS" पूर्ण,
	अणु "SAS_3_0_GBPS" पूर्ण,
	अणु "SAS_6_0_GBPS" पूर्ण,
	अणु "SAS_12_0_GBPS" पूर्ण,
	अणु "FFE_RESV" पूर्ण,
	अणु "SATA_1_5_GBPS" पूर्ण,
	अणु "SATA_3_0_GBPS" पूर्ण,
	अणु "SATA_6_0_GBPS" पूर्ण,
पूर्ण;

अटल sमाप_प्रकार debugfs_v3_hw_ग_लिखो(काष्ठा file *filp,
				   स्थिर अक्षर __user *buf,
				   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा seq_file *m = filp->निजी_data;
	u32 *val = m->निजी;
	पूर्णांक res;

	res = kstrtouपूर्णांक_from_user(buf, count, 0, val);
	अगर (res)
		वापस res;

	वापस count;
पूर्ण

अटल पूर्णांक debugfs_v3_hw_show(काष्ठा seq_file *s, व्योम *p)
अणु
	u32 *val = s->निजी;

	seq_म_लिखो(s, "0x%x\n", *val);

	वापस 0;
पूर्ण

अटल पूर्णांक debugfs_v3_hw_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	वापस single_खोलो(filp, debugfs_v3_hw_show,
			   inode->i_निजी);
पूर्ण

अटल स्थिर काष्ठा file_operations debugfs_v3_hw_fops = अणु
	.खोलो = debugfs_v3_hw_खोलो,
	.पढ़ो = seq_पढ़ो,
	.ग_लिखो = debugfs_v3_hw_ग_लिखो,
	.llseek = seq_lseek,
	.release = single_release,
	.owner = THIS_MODULE,
पूर्ण;

अटल sमाप_प्रकार debugfs_phy_करोwn_cnt_v3_hw_ग_लिखो(काष्ठा file *filp,
						स्थिर अक्षर __user *buf,
						माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा seq_file *s = filp->निजी_data;
	काष्ठा hisi_sas_phy *phy = s->निजी;
	अचिन्हित पूर्णांक set_val;
	पूर्णांक res;

	res = kstrtouपूर्णांक_from_user(buf, count, 0, &set_val);
	अगर (res)
		वापस res;

	अगर (set_val > 0)
		वापस -EINVAL;

	atomic_set(&phy->करोwn_cnt, 0);

	वापस count;
पूर्ण

अटल पूर्णांक debugfs_phy_करोwn_cnt_v3_hw_show(काष्ठा seq_file *s, व्योम *p)
अणु
	काष्ठा hisi_sas_phy *phy = s->निजी;

	seq_म_लिखो(s, "%d\n", atomic_पढ़ो(&phy->करोwn_cnt));

	वापस 0;
पूर्ण

अटल पूर्णांक debugfs_phy_करोwn_cnt_v3_hw_खोलो(काष्ठा inode *inode,
					   काष्ठा file *filp)
अणु
	वापस single_खोलो(filp, debugfs_phy_करोwn_cnt_v3_hw_show,
			   inode->i_निजी);
पूर्ण

अटल स्थिर काष्ठा file_operations debugfs_phy_करोwn_cnt_v3_hw_fops = अणु
	.खोलो = debugfs_phy_करोwn_cnt_v3_hw_खोलो,
	.पढ़ो = seq_पढ़ो,
	.ग_लिखो = debugfs_phy_करोwn_cnt_v3_hw_ग_लिखो,
	.llseek = seq_lseek,
	.release = single_release,
	.owner = THIS_MODULE,
पूर्ण;

क्रमागत fअगरo_dump_mode_v3_hw अणु
	FIFO_DUMP_FORVER =		(1U << 0),
	FIFO_DUMP_AFTER_TRIGGER =	(1U << 1),
	FIFO_DUMP_UNTILL_TRIGGER =	(1U << 2),
पूर्ण;

क्रमागत fअगरo_trigger_mode_v3_hw अणु
	FIFO_TRIGGER_EDGE =		(1U << 0),
	FIFO_TRIGGER_SAME_LEVEL =	(1U << 1),
	FIFO_TRIGGER_DIFF_LEVEL =	(1U << 2),
पूर्ण;

अटल पूर्णांक debugfs_is_fअगरo_config_valid_v3_hw(काष्ठा hisi_sas_phy *phy)
अणु
	काष्ठा hisi_hba *hisi_hba = phy->hisi_hba;

	अगर (phy->fअगरo.संकेत_sel > 0xf) अणु
		dev_info(hisi_hba->dev, "Invalid signal select: %u\n",
			 phy->fअगरo.संकेत_sel);
		वापस -EINVAL;
	पूर्ण

	चयन (phy->fअगरo.dump_mode) अणु
	हाल FIFO_DUMP_FORVER:
	हाल FIFO_DUMP_AFTER_TRIGGER:
	हाल FIFO_DUMP_UNTILL_TRIGGER:
		अवरोध;
	शेष:
		dev_info(hisi_hba->dev, "Invalid dump mode: %u\n",
			 phy->fअगरo.dump_mode);
		वापस -EINVAL;
	पूर्ण

	/* when FIFO_DUMP_FORVER, no need to check trigger_mode */
	अगर (phy->fअगरo.dump_mode == FIFO_DUMP_FORVER)
		वापस 0;

	चयन (phy->fअगरo.trigger_mode) अणु
	हाल FIFO_TRIGGER_EDGE:
	हाल FIFO_TRIGGER_SAME_LEVEL:
	हाल FIFO_TRIGGER_DIFF_LEVEL:
		अवरोध;
	शेष:
		dev_info(hisi_hba->dev, "Invalid trigger mode: %u\n",
			 phy->fअगरo.trigger_mode);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक debugfs_update_fअगरo_config_v3_hw(काष्ठा hisi_sas_phy *phy)
अणु
	u32 trigger_mode = phy->fअगरo.trigger_mode;
	u32 संकेत_sel = phy->fअगरo.संकेत_sel;
	u32 dump_mode = phy->fअगरo.dump_mode;
	काष्ठा hisi_hba *hisi_hba = phy->hisi_hba;
	पूर्णांक phy_no = phy->sas_phy.id;
	u32 reg_val;
	पूर्णांक res;

	/* Check the validity of trace FIFO configuration */
	res = debugfs_is_fअगरo_config_valid_v3_hw(phy);
	अगर (res)
		वापस res;

	reg_val = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no, DFX_FIFO_CTRL);
	/* Disable trace FIFO beक्रमe update configuration */
	reg_val |= DFX_FIFO_CTRL_DUMP_DISABLE_MSK;

	/* Update trace FIFO configuration */
	reg_val &= ~(DFX_FIFO_CTRL_DUMP_MODE_MSK |
		     DFX_FIFO_CTRL_SIGNAL_SEL_MSK |
		     DFX_FIFO_CTRL_TRIGGER_MODE_MSK);

	reg_val |= ((trigger_mode << DFX_FIFO_CTRL_TRIGGER_MODE_OFF) |
		    (dump_mode << DFX_FIFO_CTRL_DUMP_MODE_OFF) |
		    (संकेत_sel << DFX_FIFO_CTRL_SIGNAL_SEL_OFF));
	hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, DFX_FIFO_CTRL, reg_val);

	hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, DFX_FIFO_DUMP_MSK,
			     phy->fअगरo.dump_msk);

	hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, DFX_FIFO_TRIGGER,
			     phy->fअगरo.trigger);

	hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, DFX_FIFO_TRIGGER_MSK,
			     phy->fअगरo.trigger_msk);

	/* Enable trace FIFO after updated configuration */
	reg_val = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no, DFX_FIFO_CTRL);
	reg_val &= ~DFX_FIFO_CTRL_DUMP_DISABLE_MSK;
	hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, DFX_FIFO_CTRL, reg_val);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार debugfs_fअगरo_update_cfg_v3_hw_ग_लिखो(काष्ठा file *filp,
						   स्थिर अक्षर __user *buf,
						   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा hisi_sas_phy *phy = filp->निजी_data;
	bool update;
	पूर्णांक val;

	val = kstrtobool_from_user(buf, count, &update);
	अगर (val)
		वापस val;

	अगर (update != 1)
		वापस -EINVAL;

	val = debugfs_update_fअगरo_config_v3_hw(phy);
	अगर (val)
		वापस val;

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations debugfs_fअगरo_update_cfg_v3_hw_fops = अणु
	.खोलो = simple_खोलो,
	.ग_लिखो = debugfs_fअगरo_update_cfg_v3_hw_ग_लिखो,
	.owner = THIS_MODULE,
पूर्ण;

अटल व्योम debugfs_पढ़ो_fअगरo_data_v3_hw(काष्ठा hisi_sas_phy *phy)
अणु
	काष्ठा hisi_hba *hisi_hba = phy->hisi_hba;
	u32 *buf = phy->fअगरo.rd_data;
	पूर्णांक phy_no = phy->sas_phy.id;
	u32 val;
	पूर्णांक i;

	स_रखो(buf, 0, माप(phy->fअगरo.rd_data));

	/* Disable trace FIFO beक्रमe पढ़ो data */
	val = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no, DFX_FIFO_CTRL);
	val |= DFX_FIFO_CTRL_DUMP_DISABLE_MSK;
	hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, DFX_FIFO_CTRL, val);

	क्रम (i = 0; i < HISI_SAS_FIFO_DATA_DW_SIZE; i++) अणु
		val = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no,
					  DFX_FIFO_RD_DATA);
		buf[i] = val;
	पूर्ण

	/* Enable trace FIFO after पढ़ो data */
	val = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no, DFX_FIFO_CTRL);
	val &= ~DFX_FIFO_CTRL_DUMP_DISABLE_MSK;
	hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, DFX_FIFO_CTRL, val);
पूर्ण

अटल पूर्णांक debugfs_fअगरo_data_v3_hw_show(काष्ठा seq_file *s, व्योम *p)
अणु
	काष्ठा hisi_sas_phy *phy = s->निजी;

	debugfs_पढ़ो_fअगरo_data_v3_hw(phy);

	debugfs_show_row_32_v3_hw(s, 0, HISI_SAS_FIFO_DATA_DW_SIZE * 4,
				  phy->fअगरo.rd_data);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(debugfs_fअगरo_data_v3_hw);

अटल व्योम debugfs_fअगरo_init_v3_hw(काष्ठा hisi_hba *hisi_hba)
अणु
	पूर्णांक phy_no;

	hisi_hba->debugfs_fअगरo_dentry =
			debugfs_create_dir("fifo", hisi_hba->debugfs_dir);

	क्रम (phy_no = 0; phy_no < hisi_hba->n_phy; phy_no++) अणु
		काष्ठा hisi_sas_phy *phy = &hisi_hba->phy[phy_no];
		काष्ठा dentry *port_dentry;
		अक्षर name[256];
		u32 val;

		/* get शेष configuration क्रम trace FIFO */
		val = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no, DFX_FIFO_CTRL);
		val &= DFX_FIFO_CTRL_DUMP_MODE_MSK;
		val >>= DFX_FIFO_CTRL_DUMP_MODE_OFF;
		phy->fअगरo.dump_mode = val;

		val = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no, DFX_FIFO_CTRL);
		val &= DFX_FIFO_CTRL_TRIGGER_MODE_MSK;
		val >>= DFX_FIFO_CTRL_TRIGGER_MODE_OFF;
		phy->fअगरo.trigger_mode = val;

		val = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no, DFX_FIFO_CTRL);
		val &= DFX_FIFO_CTRL_SIGNAL_SEL_MSK;
		val >>= DFX_FIFO_CTRL_SIGNAL_SEL_OFF;
		phy->fअगरo.संकेत_sel = val;

		val = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no, DFX_FIFO_DUMP_MSK);
		phy->fअगरo.dump_msk = val;

		val = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no, DFX_FIFO_TRIGGER);
		phy->fअगरo.trigger = val;
		val = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no, DFX_FIFO_TRIGGER_MSK);
		phy->fअगरo.trigger_msk = val;

		snम_लिखो(name, 256, "%d", phy_no);
		port_dentry = debugfs_create_dir(name,
						 hisi_hba->debugfs_fअगरo_dentry);

		debugfs_create_file("update_config", 0200, port_dentry, phy,
				    &debugfs_fअगरo_update_cfg_v3_hw_fops);

		debugfs_create_file("signal_sel", 0600, port_dentry,
				    &phy->fअगरo.संकेत_sel,
				    &debugfs_v3_hw_fops);

		debugfs_create_file("dump_msk", 0600, port_dentry,
				    &phy->fअगरo.dump_msk,
				    &debugfs_v3_hw_fops);

		debugfs_create_file("dump_mode", 0600, port_dentry,
				    &phy->fअगरo.dump_mode,
				    &debugfs_v3_hw_fops);

		debugfs_create_file("trigger_mode", 0600, port_dentry,
				    &phy->fअगरo.trigger_mode,
				    &debugfs_v3_hw_fops);

		debugfs_create_file("trigger", 0600, port_dentry,
				    &phy->fअगरo.trigger,
				    &debugfs_v3_hw_fops);

		debugfs_create_file("trigger_msk", 0600, port_dentry,
				    &phy->fअगरo.trigger_msk,
				    &debugfs_v3_hw_fops);

		debugfs_create_file("fifo_data", 0400, port_dentry, phy,
				    &debugfs_fअगरo_data_v3_hw_fops);
	पूर्ण
पूर्ण

अटल व्योम debugfs_work_handler_v3_hw(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hisi_hba *hisi_hba =
		container_of(work, काष्ठा hisi_hba, debugfs_work);

	debugfs_snapshot_regs_v3_hw(hisi_hba);
पूर्ण

अटल व्योम debugfs_release_v3_hw(काष्ठा hisi_hba *hisi_hba, पूर्णांक dump_index)
अणु
	काष्ठा device *dev = hisi_hba->dev;
	पूर्णांक i;

	devm_kमुक्त(dev, hisi_hba->debugfs_iost_cache[dump_index].cache);
	devm_kमुक्त(dev, hisi_hba->debugfs_itct_cache[dump_index].cache);
	devm_kमुक्त(dev, hisi_hba->debugfs_iost[dump_index].iost);
	devm_kमुक्त(dev, hisi_hba->debugfs_itct[dump_index].itct);

	क्रम (i = 0; i < hisi_hba->queue_count; i++)
		devm_kमुक्त(dev, hisi_hba->debugfs_dq[dump_index][i].hdr);

	क्रम (i = 0; i < hisi_hba->queue_count; i++)
		devm_kमुक्त(dev,
			   hisi_hba->debugfs_cq[dump_index][i].complete_hdr);

	क्रम (i = 0; i < DEBUGFS_REGS_NUM; i++)
		devm_kमुक्त(dev, hisi_hba->debugfs_regs[dump_index][i].data);

	क्रम (i = 0; i < hisi_hba->n_phy; i++)
		devm_kमुक्त(dev, hisi_hba->debugfs_port_reg[dump_index][i].data);
पूर्ण

अटल स्थिर काष्ठा hisi_sas_debugfs_reg *debugfs_reg_array_v3_hw[DEBUGFS_REGS_NUM] = अणु
	[DEBUGFS_GLOBAL] = &debugfs_global_reg,
	[DEBUGFS_AXI] = &debugfs_axi_reg,
	[DEBUGFS_RAS] = &debugfs_ras_reg,
पूर्ण;

अटल पूर्णांक debugfs_alloc_v3_hw(काष्ठा hisi_hba *hisi_hba, पूर्णांक dump_index)
अणु
	स्थिर काष्ठा hisi_sas_hw *hw = hisi_hba->hw;
	काष्ठा device *dev = hisi_hba->dev;
	पूर्णांक p, c, d, r, i;
	माप_प्रकार sz;

	क्रम (r = 0; r < DEBUGFS_REGS_NUM; r++) अणु
		काष्ठा hisi_sas_debugfs_regs *regs =
				&hisi_hba->debugfs_regs[dump_index][r];

		sz = debugfs_reg_array_v3_hw[r]->count * 4;
		regs->data = devm_kदो_स्मृति(dev, sz, GFP_KERNEL);
		अगर (!regs->data)
			जाओ fail;
		regs->hisi_hba = hisi_hba;
	पूर्ण

	sz = debugfs_port_reg.count * 4;
	क्रम (p = 0; p < hisi_hba->n_phy; p++) अणु
		काष्ठा hisi_sas_debugfs_port *port =
				&hisi_hba->debugfs_port_reg[dump_index][p];

		port->data = devm_kदो_स्मृति(dev, sz, GFP_KERNEL);
		अगर (!port->data)
			जाओ fail;
		port->phy = &hisi_hba->phy[p];
	पूर्ण

	sz = hw->complete_hdr_size * HISI_SAS_QUEUE_SLOTS;
	क्रम (c = 0; c < hisi_hba->queue_count; c++) अणु
		काष्ठा hisi_sas_debugfs_cq *cq =
				&hisi_hba->debugfs_cq[dump_index][c];

		cq->complete_hdr = devm_kदो_स्मृति(dev, sz, GFP_KERNEL);
		अगर (!cq->complete_hdr)
			जाओ fail;
		cq->cq = &hisi_hba->cq[c];
	पूर्ण

	sz = माप(काष्ठा hisi_sas_cmd_hdr) * HISI_SAS_QUEUE_SLOTS;
	क्रम (d = 0; d < hisi_hba->queue_count; d++) अणु
		काष्ठा hisi_sas_debugfs_dq *dq =
				&hisi_hba->debugfs_dq[dump_index][d];

		dq->hdr = devm_kदो_स्मृति(dev, sz, GFP_KERNEL);
		अगर (!dq->hdr)
			जाओ fail;
		dq->dq = &hisi_hba->dq[d];
	पूर्ण

	sz = HISI_SAS_MAX_COMMANDS * माप(काष्ठा hisi_sas_iost);

	hisi_hba->debugfs_iost[dump_index].iost =
				devm_kदो_स्मृति(dev, sz, GFP_KERNEL);
	अगर (!hisi_hba->debugfs_iost[dump_index].iost)
		जाओ fail;

	sz = HISI_SAS_IOST_ITCT_CACHE_NUM *
	     माप(काष्ठा hisi_sas_iost_itct_cache);

	hisi_hba->debugfs_iost_cache[dump_index].cache =
				devm_kदो_स्मृति(dev, sz, GFP_KERNEL);
	अगर (!hisi_hba->debugfs_iost_cache[dump_index].cache)
		जाओ fail;

	sz = HISI_SAS_IOST_ITCT_CACHE_NUM *
	     माप(काष्ठा hisi_sas_iost_itct_cache);

	hisi_hba->debugfs_itct_cache[dump_index].cache =
				devm_kदो_स्मृति(dev, sz, GFP_KERNEL);
	अगर (!hisi_hba->debugfs_itct_cache[dump_index].cache)
		जाओ fail;

	/* New memory allocation must be locate beक्रमe itct */
	sz = HISI_SAS_MAX_ITCT_ENTRIES * माप(काष्ठा hisi_sas_itct);

	hisi_hba->debugfs_itct[dump_index].itct =
				devm_kदो_स्मृति(dev, sz, GFP_KERNEL);
	अगर (!hisi_hba->debugfs_itct[dump_index].itct)
		जाओ fail;

	वापस 0;
fail:
	क्रम (i = 0; i < hisi_sas_debugfs_dump_count; i++)
		debugfs_release_v3_hw(hisi_hba, i);
	वापस -ENOMEM;
पूर्ण

अटल व्योम debugfs_phy_करोwn_cnt_init_v3_hw(काष्ठा hisi_hba *hisi_hba)
अणु
	काष्ठा dentry *dir = debugfs_create_dir("phy_down_cnt",
						hisi_hba->debugfs_dir);
	अक्षर name[16];
	पूर्णांक phy_no;

	क्रम (phy_no = 0; phy_no < hisi_hba->n_phy; phy_no++) अणु
		snम_लिखो(name, 16, "%d", phy_no);
		debugfs_create_file(name, 0600, dir,
				    &hisi_hba->phy[phy_no],
				    &debugfs_phy_करोwn_cnt_v3_hw_fops);
	पूर्ण
पूर्ण

अटल व्योम debugfs_bist_init_v3_hw(काष्ठा hisi_hba *hisi_hba)
अणु
	काष्ठा dentry *ports_dentry;
	पूर्णांक phy_no;

	hisi_hba->debugfs_bist_dentry =
			debugfs_create_dir("bist", hisi_hba->debugfs_dir);
	debugfs_create_file("link_rate", 0600,
			    hisi_hba->debugfs_bist_dentry, hisi_hba,
			    &debugfs_bist_linkrate_v3_hw_fops);

	debugfs_create_file("code_mode", 0600,
			    hisi_hba->debugfs_bist_dentry, hisi_hba,
			    &debugfs_bist_code_mode_v3_hw_fops);

	debugfs_create_file("fixed_code", 0600,
			    hisi_hba->debugfs_bist_dentry,
			    &hisi_hba->debugfs_bist_fixed_code[0],
			    &debugfs_v3_hw_fops);

	debugfs_create_file("fixed_code_1", 0600,
			    hisi_hba->debugfs_bist_dentry,
			    &hisi_hba->debugfs_bist_fixed_code[1],
			    &debugfs_v3_hw_fops);

	debugfs_create_file("phy_id", 0600, hisi_hba->debugfs_bist_dentry,
			    hisi_hba, &debugfs_bist_phy_v3_hw_fops);

	debugfs_create_u32("cnt", 0600, hisi_hba->debugfs_bist_dentry,
			   &hisi_hba->debugfs_bist_cnt);

	debugfs_create_file("loopback_mode", 0600,
			    hisi_hba->debugfs_bist_dentry,
			    hisi_hba, &debugfs_bist_mode_v3_hw_fops);

	debugfs_create_file("enable", 0600, hisi_hba->debugfs_bist_dentry,
			    hisi_hba, &debugfs_bist_enable_v3_hw_fops);

	ports_dentry = debugfs_create_dir("port", hisi_hba->debugfs_bist_dentry);

	क्रम (phy_no = 0; phy_no < hisi_hba->n_phy; phy_no++) अणु
		काष्ठा dentry *port_dentry;
		काष्ठा dentry *ffe_dentry;
		अक्षर name[256];
		पूर्णांक i;

		snम_लिखो(name, 256, "%d", phy_no);
		port_dentry = debugfs_create_dir(name, ports_dentry);
		ffe_dentry = debugfs_create_dir("ffe", port_dentry);
		क्रम (i = 0; i < FFE_CFG_MAX; i++) अणु
			अगर (i == FFE_RESV)
				जारी;
			debugfs_create_file(debugfs_ffe_name_v3_hw[i].name,
					    0600, ffe_dentry,
					    &hisi_hba->debugfs_bist_ffe[phy_no][i],
					    &debugfs_v3_hw_fops);
		पूर्ण
	पूर्ण

	hisi_hba->debugfs_bist_linkrate = SAS_LINK_RATE_1_5_GBPS;
पूर्ण

अटल व्योम debugfs_init_v3_hw(काष्ठा hisi_hba *hisi_hba)
अणु
	काष्ठा device *dev = hisi_hba->dev;
	पूर्णांक i;

	hisi_hba->debugfs_dir = debugfs_create_dir(dev_name(dev),
						   hisi_sas_debugfs_dir);
	debugfs_create_file("trigger_dump", 0200,
			    hisi_hba->debugfs_dir,
			    hisi_hba,
			    &debugfs_trigger_dump_v3_hw_fops);

	/* create bist काष्ठाures */
	debugfs_bist_init_v3_hw(hisi_hba);

	hisi_hba->debugfs_dump_dentry =
			debugfs_create_dir("dump", hisi_hba->debugfs_dir);

	debugfs_phy_करोwn_cnt_init_v3_hw(hisi_hba);
	debugfs_fअगरo_init_v3_hw(hisi_hba);

	क्रम (i = 0; i < hisi_sas_debugfs_dump_count; i++) अणु
		अगर (debugfs_alloc_v3_hw(hisi_hba, i)) अणु
			debugfs_हटाओ_recursive(hisi_hba->debugfs_dir);
			dev_dbg(dev, "failed to init debugfs!\n");
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम debugfs_निकास_v3_hw(काष्ठा hisi_hba *hisi_hba)
अणु
	debugfs_हटाओ_recursive(hisi_hba->debugfs_dir);
पूर्ण

अटल पूर्णांक
hisi_sas_v3_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा Scsi_Host *shost;
	काष्ठा hisi_hba *hisi_hba;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा asd_sas_phy **arr_phy;
	काष्ठा asd_sas_port **arr_port;
	काष्ठा sas_ha_काष्ठा *sha;
	पूर्णांक rc, phy_nr, port_nr, i;

	rc = pci_enable_device(pdev);
	अगर (rc)
		जाओ err_out;

	pci_set_master(pdev);

	rc = pci_request_regions(pdev, DRV_NAME);
	अगर (rc)
		जाओ err_out_disable_device;

	rc = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64));
	अगर (rc)
		rc = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
	अगर (rc) अणु
		dev_err(dev, "No usable DMA addressing method\n");
		rc = -ENODEV;
		जाओ err_out_regions;
	पूर्ण

	shost = hisi_sas_shost_alloc_pci(pdev);
	अगर (!shost) अणु
		rc = -ENOMEM;
		जाओ err_out_regions;
	पूर्ण

	sha = SHOST_TO_SAS_HA(shost);
	hisi_hba = shost_priv(shost);
	dev_set_drvdata(dev, sha);

	hisi_hba->regs = pcim_iomap(pdev, 5, 0);
	अगर (!hisi_hba->regs) अणु
		dev_err(dev, "cannot map register\n");
		rc = -ENOMEM;
		जाओ err_out_ha;
	पूर्ण

	phy_nr = port_nr = hisi_hba->n_phy;

	arr_phy = devm_kसुस्मृति(dev, phy_nr, माप(व्योम *), GFP_KERNEL);
	arr_port = devm_kसुस्मृति(dev, port_nr, माप(व्योम *), GFP_KERNEL);
	अगर (!arr_phy || !arr_port) अणु
		rc = -ENOMEM;
		जाओ err_out_ha;
	पूर्ण

	sha->sas_phy = arr_phy;
	sha->sas_port = arr_port;
	sha->core.shost = shost;
	sha->lldd_ha = hisi_hba;

	shost->transportt = hisi_sas_stt;
	shost->max_id = HISI_SAS_MAX_DEVICES;
	shost->max_lun = ~0;
	shost->max_channel = 1;
	shost->max_cmd_len = 16;
	shost->can_queue = HISI_SAS_UNRESERVED_IPTT;
	shost->cmd_per_lun = HISI_SAS_UNRESERVED_IPTT;

	sha->sas_ha_name = DRV_NAME;
	sha->dev = dev;
	sha->lldd_module = THIS_MODULE;
	sha->sas_addr = &hisi_hba->sas_addr[0];
	sha->num_phys = hisi_hba->n_phy;

	क्रम (i = 0; i < hisi_hba->n_phy; i++) अणु
		sha->sas_phy[i] = &hisi_hba->phy[i].sas_phy;
		sha->sas_port[i] = &hisi_hba->port[i].sas_port;
	पूर्ण

	अगर (hisi_hba->prot_mask) अणु
		dev_info(dev, "Registering for DIF/DIX prot_mask=0x%x\n",
			 prot_mask);
		scsi_host_set_prot(hisi_hba->shost, prot_mask);
		अगर (hisi_hba->prot_mask & HISI_SAS_DIX_PROT_MASK)
			scsi_host_set_guard(hisi_hba->shost,
					    SHOST_DIX_GUARD_CRC);
	पूर्ण

	अगर (hisi_sas_debugfs_enable)
		debugfs_init_v3_hw(hisi_hba);

	rc = पूर्णांकerrupt_preinit_v3_hw(hisi_hba);
	अगर (rc)
		जाओ err_out_debugfs;
	dev_err(dev, "%d hw queues\n", shost->nr_hw_queues);
	rc = scsi_add_host(shost, dev);
	अगर (rc)
		जाओ err_out_मुक्त_irq_vectors;

	rc = sas_रेजिस्टर_ha(sha);
	अगर (rc)
		जाओ err_out_रेजिस्टर_ha;

	rc = hisi_sas_v3_init(hisi_hba);
	अगर (rc)
		जाओ err_out_hw_init;

	scsi_scan_host(shost);

	/*
	 * For the situation that there are ATA disks connected with SAS
	 * controller, it additionally creates ata_port which will affect the
	 * child_count of hisi_hba->dev. Even अगर suspended all the disks,
	 * ata_port is still and the child_count of hisi_hba->dev is not 0.
	 * So use pm_suspend_ignore_children() to ignore the effect to
	 * hisi_hba->dev.
	 */
	pm_suspend_ignore_children(dev, true);
	pm_runसमय_put_noidle(&pdev->dev);

	वापस 0;

err_out_hw_init:
	sas_unरेजिस्टर_ha(sha);
err_out_रेजिस्टर_ha:
	scsi_हटाओ_host(shost);
err_out_मुक्त_irq_vectors:
	pci_मुक्त_irq_vectors(pdev);
err_out_debugfs:
	debugfs_निकास_v3_hw(hisi_hba);
err_out_ha:
	hisi_sas_मुक्त(hisi_hba);
	scsi_host_put(shost);
err_out_regions:
	pci_release_regions(pdev);
err_out_disable_device:
	pci_disable_device(pdev);
err_out:
	वापस rc;
पूर्ण

अटल व्योम
hisi_sas_v3_destroy_irqs(काष्ठा pci_dev *pdev, काष्ठा hisi_hba *hisi_hba)
अणु
	पूर्णांक i;

	devm_मुक्त_irq(&pdev->dev, pci_irq_vector(pdev, 1), hisi_hba);
	devm_मुक्त_irq(&pdev->dev, pci_irq_vector(pdev, 2), hisi_hba);
	devm_मुक्त_irq(&pdev->dev, pci_irq_vector(pdev, 11), hisi_hba);
	क्रम (i = 0; i < hisi_hba->cq_nvecs; i++) अणु
		काष्ठा hisi_sas_cq *cq = &hisi_hba->cq[i];
		पूर्णांक nr = hisi_sas_पूर्णांकr_conv ? 16 : 16 + i;

		devm_मुक्त_irq(&pdev->dev, pci_irq_vector(pdev, nr), cq);
	पूर्ण
	pci_मुक्त_irq_vectors(pdev);
पूर्ण

अटल व्योम hisi_sas_v3_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा sas_ha_काष्ठा *sha = dev_get_drvdata(dev);
	काष्ठा hisi_hba *hisi_hba = sha->lldd_ha;
	काष्ठा Scsi_Host *shost = sha->core.shost;

	pm_runसमय_get_noresume(dev);
	अगर (समयr_pending(&hisi_hba->समयr))
		del_समयr(&hisi_hba->समयr);

	sas_unरेजिस्टर_ha(sha);
	flush_workqueue(hisi_hba->wq);
	sas_हटाओ_host(sha->core.shost);

	hisi_sas_v3_destroy_irqs(pdev, hisi_hba);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
	hisi_sas_मुक्त(hisi_hba);
	debugfs_निकास_v3_hw(hisi_hba);
	scsi_host_put(shost);
पूर्ण

अटल व्योम hisi_sas_reset_prepare_v3_hw(काष्ठा pci_dev *pdev)
अणु
	काष्ठा sas_ha_काष्ठा *sha = pci_get_drvdata(pdev);
	काष्ठा hisi_hba *hisi_hba = sha->lldd_ha;
	काष्ठा device *dev = hisi_hba->dev;
	पूर्णांक rc;

	dev_info(dev, "FLR prepare\n");
	set_bit(HISI_SAS_RESET_BIT, &hisi_hba->flags);
	hisi_sas_controller_reset_prepare(hisi_hba);

	rc = disable_host_v3_hw(hisi_hba);
	अगर (rc)
		dev_err(dev, "FLR: disable host failed rc=%d\n", rc);
पूर्ण

अटल व्योम hisi_sas_reset_करोne_v3_hw(काष्ठा pci_dev *pdev)
अणु
	काष्ठा sas_ha_काष्ठा *sha = pci_get_drvdata(pdev);
	काष्ठा hisi_hba *hisi_hba = sha->lldd_ha;
	काष्ठा device *dev = hisi_hba->dev;
	पूर्णांक rc;

	hisi_sas_init_mem(hisi_hba);

	rc = hw_init_v3_hw(hisi_hba);
	अगर (rc) अणु
		dev_err(dev, "FLR: hw init failed rc=%d\n", rc);
		वापस;
	पूर्ण

	hisi_sas_controller_reset_करोne(hisi_hba);
	dev_info(dev, "FLR done\n");
पूर्ण

क्रमागत अणु
	/* instances of the controller */
	hip08,
पूर्ण;

अटल पूर्णांक _suspend_v3_hw(काष्ठा device *device)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(device);
	काष्ठा sas_ha_काष्ठा *sha = pci_get_drvdata(pdev);
	काष्ठा hisi_hba *hisi_hba = sha->lldd_ha;
	काष्ठा device *dev = hisi_hba->dev;
	काष्ठा Scsi_Host *shost = hisi_hba->shost;
	पूर्णांक rc;

	अगर (!pdev->pm_cap) अणु
		dev_err(dev, "PCI PM not supported\n");
		वापस -ENODEV;
	पूर्ण

	अगर (test_and_set_bit(HISI_SAS_RESET_BIT, &hisi_hba->flags))
		वापस -1;

	scsi_block_requests(shost);
	set_bit(HISI_SAS_REJECT_CMD_BIT, &hisi_hba->flags);
	flush_workqueue(hisi_hba->wq);

	rc = disable_host_v3_hw(hisi_hba);
	अगर (rc) अणु
		dev_err(dev, "PM suspend: disable host failed rc=%d\n", rc);
		clear_bit(HISI_SAS_REJECT_CMD_BIT, &hisi_hba->flags);
		clear_bit(HISI_SAS_RESET_BIT, &hisi_hba->flags);
		scsi_unblock_requests(shost);
		वापस rc;
	पूर्ण

	hisi_sas_init_mem(hisi_hba);

	dev_warn(dev, "entering suspend state\n");

	hisi_sas_release_tasks(hisi_hba);

	sas_suspend_ha(sha);
	वापस 0;
पूर्ण

अटल पूर्णांक _resume_v3_hw(काष्ठा device *device)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(device);
	काष्ठा sas_ha_काष्ठा *sha = pci_get_drvdata(pdev);
	काष्ठा hisi_hba *hisi_hba = sha->lldd_ha;
	काष्ठा Scsi_Host *shost = hisi_hba->shost;
	काष्ठा device *dev = hisi_hba->dev;
	अचिन्हित पूर्णांक rc;
	pci_घातer_t device_state = pdev->current_state;

	dev_warn(dev, "resuming from operating state [D%d]\n",
		 device_state);

	scsi_unblock_requests(shost);
	clear_bit(HISI_SAS_REJECT_CMD_BIT, &hisi_hba->flags);

	sas_prep_resume_ha(sha);
	rc = hw_init_v3_hw(hisi_hba);
	अगर (rc) अणु
		scsi_हटाओ_host(shost);
		वापस rc;
	पूर्ण
	phys_init_v3_hw(hisi_hba);
	sas_resume_ha(sha);
	clear_bit(HISI_SAS_RESET_BIT, &hisi_hba->flags);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused suspend_v3_hw(काष्ठा device *device)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(device);
	काष्ठा sas_ha_काष्ठा *sha = pci_get_drvdata(pdev);
	काष्ठा hisi_hba *hisi_hba = sha->lldd_ha;
	पूर्णांक rc;

	set_bit(HISI_SAS_PM_BIT, &hisi_hba->flags);

	rc = _suspend_v3_hw(device);
	अगर (rc)
		clear_bit(HISI_SAS_PM_BIT, &hisi_hba->flags);

	वापस rc;
पूर्ण

अटल पूर्णांक __maybe_unused resume_v3_hw(काष्ठा device *device)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(device);
	काष्ठा sas_ha_काष्ठा *sha = pci_get_drvdata(pdev);
	काष्ठा hisi_hba *hisi_hba = sha->lldd_ha;
	पूर्णांक rc = _resume_v3_hw(device);

	clear_bit(HISI_SAS_PM_BIT, &hisi_hba->flags);

	वापस rc;
पूर्ण

अटल स्थिर काष्ठा pci_device_id sas_v3_pci_table[] = अणु
	अणु PCI_VDEVICE(HUAWEI, 0xa230), hip08 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, sas_v3_pci_table);

अटल स्थिर काष्ठा pci_error_handlers hisi_sas_err_handler = अणु
	.reset_prepare	= hisi_sas_reset_prepare_v3_hw,
	.reset_करोne	= hisi_sas_reset_करोne_v3_hw,
पूर्ण;

अटल UNIVERSAL_DEV_PM_OPS(hisi_sas_v3_pm_ops,
			    suspend_v3_hw,
			    resume_v3_hw,
			    शून्य);

अटल काष्ठा pci_driver sas_v3_pci_driver = अणु
	.name		= DRV_NAME,
	.id_table	= sas_v3_pci_table,
	.probe		= hisi_sas_v3_probe,
	.हटाओ		= hisi_sas_v3_हटाओ,
	.err_handler	= &hisi_sas_err_handler,
	.driver.pm	= &hisi_sas_v3_pm_ops,
पूर्ण;

module_pci_driver(sas_v3_pci_driver);
module_param_named(पूर्णांकr_conv, hisi_sas_पूर्णांकr_conv, bool, 0444);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("John Garry <john.garry@huawei.com>");
MODULE_DESCRIPTION("HISILICON SAS controller v3 hw driver based on pci device");
MODULE_ALIAS("pci:" DRV_NAME);
