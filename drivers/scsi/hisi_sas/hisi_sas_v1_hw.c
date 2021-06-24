<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2015 Linaro Ltd.
 * Copyright (c) 2015 Hisilicon Limited.
 */

#समावेश "hisi_sas.h"
#घोषणा DRV_NAME "hisi_sas_v1_hw"

/* global रेजिस्टरs need init*/
#घोषणा DLVRY_QUEUE_ENABLE		0x0
#घोषणा IOST_BASE_ADDR_LO		0x8
#घोषणा IOST_BASE_ADDR_HI		0xc
#घोषणा ITCT_BASE_ADDR_LO		0x10
#घोषणा ITCT_BASE_ADDR_HI		0x14
#घोषणा BROKEN_MSG_ADDR_LO		0x18
#घोषणा BROKEN_MSG_ADDR_HI		0x1c
#घोषणा PHY_CONTEXT			0x20
#घोषणा PHY_STATE			0x24
#घोषणा PHY_PORT_NUM_MA			0x28
#घोषणा PORT_STATE			0x2c
#घोषणा PHY_CONN_RATE			0x30
#घोषणा HGC_TRANS_TASK_CNT_LIMIT	0x38
#घोषणा AXI_AHB_CLK_CFG			0x3c
#घोषणा HGC_SAS_TXFAIL_RETRY_CTRL	0x84
#घोषणा HGC_GET_ITV_TIME		0x90
#घोषणा DEVICE_MSG_WORK_MODE		0x94
#घोषणा I_T_NEXUS_LOSS_TIME		0xa0
#घोषणा BUS_INACTIVE_LIMIT_TIME		0xa8
#घोषणा REJECT_TO_OPEN_LIMIT_TIME	0xac
#घोषणा CFG_AGING_TIME			0xbc
#घोषणा CFG_AGING_TIME_ITCT_REL_OFF	0
#घोषणा CFG_AGING_TIME_ITCT_REL_MSK	(0x1 << CFG_AGING_TIME_ITCT_REL_OFF)
#घोषणा HGC_DFX_CFG2			0xc0
#घोषणा FIS_LIST_BADDR_L		0xc4
#घोषणा CFG_1US_TIMER_TRSH		0xcc
#घोषणा CFG_SAS_CONFIG			0xd4
#घोषणा HGC_IOST_ECC_ADDR		0x140
#घोषणा HGC_IOST_ECC_ADDR_BAD_OFF	16
#घोषणा HGC_IOST_ECC_ADDR_BAD_MSK	(0x3ff << HGC_IOST_ECC_ADDR_BAD_OFF)
#घोषणा HGC_DQ_ECC_ADDR			0x144
#घोषणा HGC_DQ_ECC_ADDR_BAD_OFF		16
#घोषणा HGC_DQ_ECC_ADDR_BAD_MSK		(0xfff << HGC_DQ_ECC_ADDR_BAD_OFF)
#घोषणा HGC_INVLD_DQE_INFO		0x148
#घोषणा HGC_INVLD_DQE_INFO_DQ_OFF	0
#घोषणा HGC_INVLD_DQE_INFO_DQ_MSK	(0xffff << HGC_INVLD_DQE_INFO_DQ_OFF)
#घोषणा HGC_INVLD_DQE_INFO_TYPE_OFF	16
#घोषणा HGC_INVLD_DQE_INFO_TYPE_MSK	(0x1 << HGC_INVLD_DQE_INFO_TYPE_OFF)
#घोषणा HGC_INVLD_DQE_INFO_FORCE_OFF	17
#घोषणा HGC_INVLD_DQE_INFO_FORCE_MSK	(0x1 << HGC_INVLD_DQE_INFO_FORCE_OFF)
#घोषणा HGC_INVLD_DQE_INFO_PHY_OFF	18
#घोषणा HGC_INVLD_DQE_INFO_PHY_MSK	(0x1 << HGC_INVLD_DQE_INFO_PHY_OFF)
#घोषणा HGC_INVLD_DQE_INFO_ABORT_OFF	19
#घोषणा HGC_INVLD_DQE_INFO_ABORT_MSK	(0x1 << HGC_INVLD_DQE_INFO_ABORT_OFF)
#घोषणा HGC_INVLD_DQE_INFO_IPTT_OF_OFF	20
#घोषणा HGC_INVLD_DQE_INFO_IPTT_OF_MSK	(0x1 << HGC_INVLD_DQE_INFO_IPTT_OF_OFF)
#घोषणा HGC_INVLD_DQE_INFO_SSP_ERR_OFF	21
#घोषणा HGC_INVLD_DQE_INFO_SSP_ERR_MSK	(0x1 << HGC_INVLD_DQE_INFO_SSP_ERR_OFF)
#घोषणा HGC_INVLD_DQE_INFO_OFL_OFF	22
#घोषणा HGC_INVLD_DQE_INFO_OFL_MSK	(0x1 << HGC_INVLD_DQE_INFO_OFL_OFF)
#घोषणा HGC_ITCT_ECC_ADDR		0x150
#घोषणा HGC_ITCT_ECC_ADDR_BAD_OFF	16
#घोषणा HGC_ITCT_ECC_ADDR_BAD_MSK	(0x3ff << HGC_ITCT_ECC_ADDR_BAD_OFF)
#घोषणा HGC_AXI_FIFO_ERR_INFO		0x154
#घोषणा INT_COAL_EN			0x1bc
#घोषणा OQ_INT_COAL_TIME		0x1c0
#घोषणा OQ_INT_COAL_CNT			0x1c4
#घोषणा ENT_INT_COAL_TIME		0x1c8
#घोषणा ENT_INT_COAL_CNT		0x1cc
#घोषणा OQ_INT_SRC			0x1d0
#घोषणा OQ_INT_SRC_MSK			0x1d4
#घोषणा ENT_INT_SRC1			0x1d8
#घोषणा ENT_INT_SRC2			0x1dc
#घोषणा ENT_INT_SRC2_DQ_CFG_ERR_OFF	25
#घोषणा ENT_INT_SRC2_DQ_CFG_ERR_MSK	(0x1 << ENT_INT_SRC2_DQ_CFG_ERR_OFF)
#घोषणा ENT_INT_SRC2_CQ_CFG_ERR_OFF	27
#घोषणा ENT_INT_SRC2_CQ_CFG_ERR_MSK	(0x1 << ENT_INT_SRC2_CQ_CFG_ERR_OFF)
#घोषणा ENT_INT_SRC2_AXI_WRONG_INT_OFF	28
#घोषणा ENT_INT_SRC2_AXI_WRONG_INT_MSK	(0x1 << ENT_INT_SRC2_AXI_WRONG_INT_OFF)
#घोषणा ENT_INT_SRC2_AXI_OVERLF_INT_OFF	29
#घोषणा ENT_INT_SRC2_AXI_OVERLF_INT_MSK	(0x1 << ENT_INT_SRC2_AXI_OVERLF_INT_OFF)
#घोषणा ENT_INT_SRC_MSK1		0x1e0
#घोषणा ENT_INT_SRC_MSK2		0x1e4
#घोषणा SAS_ECC_INTR			0x1e8
#घोषणा SAS_ECC_INTR_DQ_ECC1B_OFF	0
#घोषणा SAS_ECC_INTR_DQ_ECC1B_MSK	(0x1 << SAS_ECC_INTR_DQ_ECC1B_OFF)
#घोषणा SAS_ECC_INTR_DQ_ECCBAD_OFF	1
#घोषणा SAS_ECC_INTR_DQ_ECCBAD_MSK	(0x1 << SAS_ECC_INTR_DQ_ECCBAD_OFF)
#घोषणा SAS_ECC_INTR_IOST_ECC1B_OFF	2
#घोषणा SAS_ECC_INTR_IOST_ECC1B_MSK	(0x1 << SAS_ECC_INTR_IOST_ECC1B_OFF)
#घोषणा SAS_ECC_INTR_IOST_ECCBAD_OFF	3
#घोषणा SAS_ECC_INTR_IOST_ECCBAD_MSK	(0x1 << SAS_ECC_INTR_IOST_ECCBAD_OFF)
#घोषणा SAS_ECC_INTR_ITCT_ECC1B_OFF	4
#घोषणा SAS_ECC_INTR_ITCT_ECC1B_MSK	(0x1 << SAS_ECC_INTR_ITCT_ECC1B_OFF)
#घोषणा SAS_ECC_INTR_ITCT_ECCBAD_OFF	5
#घोषणा SAS_ECC_INTR_ITCT_ECCBAD_MSK	(0x1 << SAS_ECC_INTR_ITCT_ECCBAD_OFF)
#घोषणा SAS_ECC_INTR_MSK		0x1ec
#घोषणा HGC_ERR_STAT_EN			0x238
#घोषणा DLVRY_Q_0_BASE_ADDR_LO		0x260
#घोषणा DLVRY_Q_0_BASE_ADDR_HI		0x264
#घोषणा DLVRY_Q_0_DEPTH			0x268
#घोषणा DLVRY_Q_0_WR_PTR		0x26c
#घोषणा DLVRY_Q_0_RD_PTR		0x270
#घोषणा COMPL_Q_0_BASE_ADDR_LO		0x4e0
#घोषणा COMPL_Q_0_BASE_ADDR_HI		0x4e4
#घोषणा COMPL_Q_0_DEPTH			0x4e8
#घोषणा COMPL_Q_0_WR_PTR		0x4ec
#घोषणा COMPL_Q_0_RD_PTR		0x4f0
#घोषणा HGC_ECC_ERR			0x7d0

/* phy रेजिस्टरs need init */
#घोषणा PORT_BASE			(0x800)

#घोषणा PHY_CFG				(PORT_BASE + 0x0)
#घोषणा PHY_CFG_ENA_OFF			0
#घोषणा PHY_CFG_ENA_MSK			(0x1 << PHY_CFG_ENA_OFF)
#घोषणा PHY_CFG_DC_OPT_OFF		2
#घोषणा PHY_CFG_DC_OPT_MSK		(0x1 << PHY_CFG_DC_OPT_OFF)
#घोषणा PROG_PHY_LINK_RATE		(PORT_BASE + 0xc)
#घोषणा PROG_PHY_LINK_RATE_MAX_OFF	0
#घोषणा PROG_PHY_LINK_RATE_MAX_MSK	(0xf << PROG_PHY_LINK_RATE_MAX_OFF)
#घोषणा PROG_PHY_LINK_RATE_MIN_OFF	4
#घोषणा PROG_PHY_LINK_RATE_MIN_MSK	(0xf << PROG_PHY_LINK_RATE_MIN_OFF)
#घोषणा PROG_PHY_LINK_RATE_OOB_OFF	8
#घोषणा PROG_PHY_LINK_RATE_OOB_MSK	(0xf << PROG_PHY_LINK_RATE_OOB_OFF)
#घोषणा PHY_CTRL			(PORT_BASE + 0x14)
#घोषणा PHY_CTRL_RESET_OFF		0
#घोषणा PHY_CTRL_RESET_MSK		(0x1 << PHY_CTRL_RESET_OFF)
#घोषणा PHY_RATE_NEGO			(PORT_BASE + 0x30)
#घोषणा PHY_PCN				(PORT_BASE + 0x44)
#घोषणा SL_TOUT_CFG			(PORT_BASE + 0x8c)
#घोषणा SL_CONTROL			(PORT_BASE + 0x94)
#घोषणा SL_CONTROL_NOTIFY_EN_OFF	0
#घोषणा SL_CONTROL_NOTIFY_EN_MSK	(0x1 << SL_CONTROL_NOTIFY_EN_OFF)
#घोषणा TX_ID_DWORD0			(PORT_BASE + 0x9c)
#घोषणा TX_ID_DWORD1			(PORT_BASE + 0xa0)
#घोषणा TX_ID_DWORD2			(PORT_BASE + 0xa4)
#घोषणा TX_ID_DWORD3			(PORT_BASE + 0xa8)
#घोषणा TX_ID_DWORD4			(PORT_BASE + 0xaC)
#घोषणा TX_ID_DWORD5			(PORT_BASE + 0xb0)
#घोषणा TX_ID_DWORD6			(PORT_BASE + 0xb4)
#घोषणा RX_IDAF_DWORD0			(PORT_BASE + 0xc4)
#घोषणा RX_IDAF_DWORD1			(PORT_BASE + 0xc8)
#घोषणा RX_IDAF_DWORD2			(PORT_BASE + 0xcc)
#घोषणा RX_IDAF_DWORD3			(PORT_BASE + 0xd0)
#घोषणा RX_IDAF_DWORD4			(PORT_BASE + 0xd4)
#घोषणा RX_IDAF_DWORD5			(PORT_BASE + 0xd8)
#घोषणा RX_IDAF_DWORD6			(PORT_BASE + 0xdc)
#घोषणा RXOP_CHECK_CFG_H		(PORT_BASE + 0xfc)
#घोषणा DONE_RECEIVED_TIME		(PORT_BASE + 0x12c)
#घोषणा CON_CFG_DRIVER			(PORT_BASE + 0x130)
#घोषणा PHY_CONFIG2			(PORT_BASE + 0x1a8)
#घोषणा PHY_CONFIG2_FORCE_TXDEEMPH_OFF	3
#घोषणा PHY_CONFIG2_FORCE_TXDEEMPH_MSK	(0x1 << PHY_CONFIG2_FORCE_TXDEEMPH_OFF)
#घोषणा PHY_CONFIG2_TX_TRAIN_COMP_OFF	24
#घोषणा PHY_CONFIG2_TX_TRAIN_COMP_MSK	(0x1 << PHY_CONFIG2_TX_TRAIN_COMP_OFF)
#घोषणा CHL_INT0			(PORT_BASE + 0x1b0)
#घोषणा CHL_INT0_PHYCTRL_NOTRDY_OFF	0
#घोषणा CHL_INT0_PHYCTRL_NOTRDY_MSK	(0x1 << CHL_INT0_PHYCTRL_NOTRDY_OFF)
#घोषणा CHL_INT0_SN_FAIL_NGR_OFF	2
#घोषणा CHL_INT0_SN_FAIL_NGR_MSK	(0x1 << CHL_INT0_SN_FAIL_NGR_OFF)
#घोषणा CHL_INT0_DWS_LOST_OFF		4
#घोषणा CHL_INT0_DWS_LOST_MSK		(0x1 << CHL_INT0_DWS_LOST_OFF)
#घोषणा CHL_INT0_SL_IDAF_FAIL_OFF	10
#घोषणा CHL_INT0_SL_IDAF_FAIL_MSK	(0x1 << CHL_INT0_SL_IDAF_FAIL_OFF)
#घोषणा CHL_INT0_ID_TIMEOUT_OFF		11
#घोषणा CHL_INT0_ID_TIMEOUT_MSK		(0x1 << CHL_INT0_ID_TIMEOUT_OFF)
#घोषणा CHL_INT0_SL_OPAF_FAIL_OFF	12
#घोषणा CHL_INT0_SL_OPAF_FAIL_MSK	(0x1 << CHL_INT0_SL_OPAF_FAIL_OFF)
#घोषणा CHL_INT0_SL_PS_FAIL_OFF		21
#घोषणा CHL_INT0_SL_PS_FAIL_MSK		(0x1 << CHL_INT0_SL_PS_FAIL_OFF)
#घोषणा CHL_INT1			(PORT_BASE + 0x1b4)
#घोषणा CHL_INT2			(PORT_BASE + 0x1b8)
#घोषणा CHL_INT2_SL_RX_BC_ACK_OFF	2
#घोषणा CHL_INT2_SL_RX_BC_ACK_MSK	(0x1 << CHL_INT2_SL_RX_BC_ACK_OFF)
#घोषणा CHL_INT2_SL_PHY_ENA_OFF		6
#घोषणा CHL_INT2_SL_PHY_ENA_MSK		(0x1 << CHL_INT2_SL_PHY_ENA_OFF)
#घोषणा CHL_INT0_MSK			(PORT_BASE + 0x1bc)
#घोषणा CHL_INT0_MSK_PHYCTRL_NOTRDY_OFF	0
#घोषणा CHL_INT0_MSK_PHYCTRL_NOTRDY_MSK	(0x1 << CHL_INT0_MSK_PHYCTRL_NOTRDY_OFF)
#घोषणा CHL_INT1_MSK			(PORT_BASE + 0x1c0)
#घोषणा CHL_INT2_MSK			(PORT_BASE + 0x1c4)
#घोषणा CHL_INT_COAL_EN			(PORT_BASE + 0x1d0)
#घोषणा DMA_TX_STATUS			(PORT_BASE + 0x2d0)
#घोषणा DMA_TX_STATUS_BUSY_OFF		0
#घोषणा DMA_TX_STATUS_BUSY_MSK		(0x1 << DMA_TX_STATUS_BUSY_OFF)
#घोषणा DMA_RX_STATUS			(PORT_BASE + 0x2e8)
#घोषणा DMA_RX_STATUS_BUSY_OFF		0
#घोषणा DMA_RX_STATUS_BUSY_MSK		(0x1 << DMA_RX_STATUS_BUSY_OFF)

#घोषणा AXI_CFG				0x5100
#घोषणा RESET_VALUE			0x7ffff

/* HW dma काष्ठाures */
/* Delivery queue header */
/* dw0 */
#घोषणा CMD_HDR_RESP_REPORT_OFF		5
#घोषणा CMD_HDR_RESP_REPORT_MSK		0x20
#घोषणा CMD_HDR_TLR_CTRL_OFF		6
#घोषणा CMD_HDR_TLR_CTRL_MSK		0xc0
#घोषणा CMD_HDR_PORT_OFF		17
#घोषणा CMD_HDR_PORT_MSK		0xe0000
#घोषणा CMD_HDR_PRIORITY_OFF		27
#घोषणा CMD_HDR_PRIORITY_MSK		0x8000000
#घोषणा CMD_HDR_MODE_OFF		28
#घोषणा CMD_HDR_MODE_MSK		0x10000000
#घोषणा CMD_HDR_CMD_OFF			29
#घोषणा CMD_HDR_CMD_MSK			0xe0000000
/* dw1 */
#घोषणा CMD_HDR_VERIFY_DTL_OFF		10
#घोषणा CMD_HDR_VERIFY_DTL_MSK		0x400
#घोषणा CMD_HDR_SSP_FRAME_TYPE_OFF	13
#घोषणा CMD_HDR_SSP_FRAME_TYPE_MSK	0xe000
#घोषणा CMD_HDR_DEVICE_ID_OFF		16
#घोषणा CMD_HDR_DEVICE_ID_MSK		0xffff0000
/* dw2 */
#घोषणा CMD_HDR_CFL_OFF			0
#घोषणा CMD_HDR_CFL_MSK			0x1ff
#घोषणा CMD_HDR_MRFL_OFF		15
#घोषणा CMD_HDR_MRFL_MSK		0xff8000
#घोषणा CMD_HDR_FIRST_BURST_OFF		25
#घोषणा CMD_HDR_FIRST_BURST_MSK		0x2000000
/* dw3 */
#घोषणा CMD_HDR_IPTT_OFF		0
#घोषणा CMD_HDR_IPTT_MSK		0xffff
/* dw6 */
#घोषणा CMD_HDR_DATA_SGL_LEN_OFF	16
#घोषणा CMD_HDR_DATA_SGL_LEN_MSK	0xffff0000

/* Completion header */
#घोषणा CMPLT_HDR_IPTT_OFF		0
#घोषणा CMPLT_HDR_IPTT_MSK		(0xffff << CMPLT_HDR_IPTT_OFF)
#घोषणा CMPLT_HDR_CMD_CMPLT_OFF		17
#घोषणा CMPLT_HDR_CMD_CMPLT_MSK		(0x1 << CMPLT_HDR_CMD_CMPLT_OFF)
#घोषणा CMPLT_HDR_ERR_RCRD_XFRD_OFF	18
#घोषणा CMPLT_HDR_ERR_RCRD_XFRD_MSK	(0x1 << CMPLT_HDR_ERR_RCRD_XFRD_OFF)
#घोषणा CMPLT_HDR_RSPNS_XFRD_OFF	19
#घोषणा CMPLT_HDR_RSPNS_XFRD_MSK	(0x1 << CMPLT_HDR_RSPNS_XFRD_OFF)
#घोषणा CMPLT_HDR_IO_CFG_ERR_OFF	27
#घोषणा CMPLT_HDR_IO_CFG_ERR_MSK	(0x1 << CMPLT_HDR_IO_CFG_ERR_OFF)

/* ITCT header */
/* qw0 */
#घोषणा ITCT_HDR_DEV_TYPE_OFF		0
#घोषणा ITCT_HDR_DEV_TYPE_MSK		(0x3ULL << ITCT_HDR_DEV_TYPE_OFF)
#घोषणा ITCT_HDR_VALID_OFF		2
#घोषणा ITCT_HDR_VALID_MSK		(0x1ULL << ITCT_HDR_VALID_OFF)
#घोषणा ITCT_HDR_AWT_CONTROL_OFF	4
#घोषणा ITCT_HDR_AWT_CONTROL_MSK	(0x1ULL << ITCT_HDR_AWT_CONTROL_OFF)
#घोषणा ITCT_HDR_MAX_CONN_RATE_OFF	5
#घोषणा ITCT_HDR_MAX_CONN_RATE_MSK	(0xfULL << ITCT_HDR_MAX_CONN_RATE_OFF)
#घोषणा ITCT_HDR_VALID_LINK_NUM_OFF	9
#घोषणा ITCT_HDR_VALID_LINK_NUM_MSK	(0xfULL << ITCT_HDR_VALID_LINK_NUM_OFF)
#घोषणा ITCT_HDR_PORT_ID_OFF		13
#घोषणा ITCT_HDR_PORT_ID_MSK		(0x7ULL << ITCT_HDR_PORT_ID_OFF)
#घोषणा ITCT_HDR_SMP_TIMEOUT_OFF	16
#घोषणा ITCT_HDR_SMP_TIMEOUT_MSK	(0xffffULL << ITCT_HDR_SMP_TIMEOUT_OFF)
/* qw1 */
#घोषणा ITCT_HDR_MAX_SAS_ADDR_OFF	0
#घोषणा ITCT_HDR_MAX_SAS_ADDR_MSK	(0xffffffffffffffff << \
					ITCT_HDR_MAX_SAS_ADDR_OFF)
/* qw2 */
#घोषणा ITCT_HDR_IT_NEXUS_LOSS_TL_OFF	0
#घोषणा ITCT_HDR_IT_NEXUS_LOSS_TL_MSK	(0xffffULL << \
					ITCT_HDR_IT_NEXUS_LOSS_TL_OFF)
#घोषणा ITCT_HDR_BUS_INACTIVE_TL_OFF	16
#घोषणा ITCT_HDR_BUS_INACTIVE_TL_MSK	(0xffffULL << \
					ITCT_HDR_BUS_INACTIVE_TL_OFF)
#घोषणा ITCT_HDR_MAX_CONN_TL_OFF	32
#घोषणा ITCT_HDR_MAX_CONN_TL_MSK	(0xffffULL << \
					ITCT_HDR_MAX_CONN_TL_OFF)
#घोषणा ITCT_HDR_REJ_OPEN_TL_OFF	48
#घोषणा ITCT_HDR_REJ_OPEN_TL_MSK	(0xffffULL << \
					ITCT_HDR_REJ_OPEN_TL_OFF)

/* Err record header */
#घोषणा ERR_HDR_DMA_TX_ERR_TYPE_OFF	0
#घोषणा ERR_HDR_DMA_TX_ERR_TYPE_MSK	(0xffff << ERR_HDR_DMA_TX_ERR_TYPE_OFF)
#घोषणा ERR_HDR_DMA_RX_ERR_TYPE_OFF	16
#घोषणा ERR_HDR_DMA_RX_ERR_TYPE_MSK	(0xffff << ERR_HDR_DMA_RX_ERR_TYPE_OFF)

काष्ठा hisi_sas_complete_v1_hdr अणु
	__le32 data;
पूर्ण;

काष्ठा hisi_sas_err_record_v1 अणु
	/* dw0 */
	__le32 dma_err_type;

	/* dw1 */
	__le32 trans_tx_fail_type;

	/* dw2 */
	__le32 trans_rx_fail_type;

	/* dw3 */
	u32 rsvd;
पूर्ण;

क्रमागत अणु
	HISI_SAS_PHY_BCAST_ACK = 0,
	HISI_SAS_PHY_SL_PHY_ENABLED,
	HISI_SAS_PHY_INT_ABNORMAL,
	HISI_SAS_PHY_INT_NR
पूर्ण;

क्रमागत अणु
	DMA_TX_ERR_BASE = 0x0,
	DMA_RX_ERR_BASE = 0x100,
	TRANS_TX_FAIL_BASE = 0x200,
	TRANS_RX_FAIL_BASE = 0x300,

	/* dma tx */
	DMA_TX_DIF_CRC_ERR = DMA_TX_ERR_BASE, /* 0x0 */
	DMA_TX_DIF_APP_ERR, /* 0x1 */
	DMA_TX_DIF_RPP_ERR, /* 0x2 */
	DMA_TX_AXI_BUS_ERR, /* 0x3 */
	DMA_TX_DATA_SGL_OVERFLOW_ERR, /* 0x4 */
	DMA_TX_DIF_SGL_OVERFLOW_ERR, /* 0x5 */
	DMA_TX_UNEXP_XFER_RDY_ERR, /* 0x6 */
	DMA_TX_XFER_RDY_OFFSET_ERR, /* 0x7 */
	DMA_TX_DATA_UNDERFLOW_ERR, /* 0x8 */
	DMA_TX_XFER_RDY_LENGTH_OVERFLOW_ERR, /* 0x9 */

	/* dma rx */
	DMA_RX_BUFFER_ECC_ERR = DMA_RX_ERR_BASE, /* 0x100 */
	DMA_RX_DIF_CRC_ERR, /* 0x101 */
	DMA_RX_DIF_APP_ERR, /* 0x102 */
	DMA_RX_DIF_RPP_ERR, /* 0x103 */
	DMA_RX_RESP_BUFFER_OVERFLOW_ERR, /* 0x104 */
	DMA_RX_AXI_BUS_ERR, /* 0x105 */
	DMA_RX_DATA_SGL_OVERFLOW_ERR, /* 0x106 */
	DMA_RX_DIF_SGL_OVERFLOW_ERR, /* 0x107 */
	DMA_RX_DATA_OFFSET_ERR, /* 0x108 */
	DMA_RX_UNEXP_RX_DATA_ERR, /* 0x109 */
	DMA_RX_DATA_OVERFLOW_ERR, /* 0x10a */
	DMA_RX_DATA_UNDERFLOW_ERR, /* 0x10b */
	DMA_RX_UNEXP_RETRANS_RESP_ERR, /* 0x10c */

	/* trans tx */
	TRANS_TX_RSVD0_ERR = TRANS_TX_FAIL_BASE, /* 0x200 */
	TRANS_TX_PHY_NOT_ENABLE_ERR, /* 0x201 */
	TRANS_TX_OPEN_REJCT_WRONG_DEST_ERR, /* 0x202 */
	TRANS_TX_OPEN_REJCT_ZONE_VIOLATION_ERR, /* 0x203 */
	TRANS_TX_OPEN_REJCT_BY_OTHER_ERR, /* 0x204 */
	TRANS_TX_RSVD1_ERR, /* 0x205 */
	TRANS_TX_OPEN_REJCT_AIP_TIMEOUT_ERR, /* 0x206 */
	TRANS_TX_OPEN_REJCT_STP_BUSY_ERR, /* 0x207 */
	TRANS_TX_OPEN_REJCT_PROTOCOL_NOT_SUPPORT_ERR, /* 0x208 */
	TRANS_TX_OPEN_REJCT_RATE_NOT_SUPPORT_ERR, /* 0x209 */
	TRANS_TX_OPEN_REJCT_BAD_DEST_ERR, /* 0x20a */
	TRANS_TX_OPEN_BREAK_RECEIVE_ERR, /* 0x20b */
	TRANS_TX_LOW_PHY_POWER_ERR, /* 0x20c */
	TRANS_TX_OPEN_REJCT_PATHWAY_BLOCKED_ERR, /* 0x20d */
	TRANS_TX_OPEN_TIMEOUT_ERR, /* 0x20e */
	TRANS_TX_OPEN_REJCT_NO_DEST_ERR, /* 0x20f */
	TRANS_TX_OPEN_RETRY_ERR, /* 0x210 */
	TRANS_TX_RSVD2_ERR, /* 0x211 */
	TRANS_TX_BREAK_TIMEOUT_ERR, /* 0x212 */
	TRANS_TX_BREAK_REQUEST_ERR, /* 0x213 */
	TRANS_TX_BREAK_RECEIVE_ERR, /* 0x214 */
	TRANS_TX_CLOSE_TIMEOUT_ERR, /* 0x215 */
	TRANS_TX_CLOSE_NORMAL_ERR, /* 0x216 */
	TRANS_TX_CLOSE_PHYRESET_ERR, /* 0x217 */
	TRANS_TX_WITH_CLOSE_DWS_TIMEOUT_ERR, /* 0x218 */
	TRANS_TX_WITH_CLOSE_COMINIT_ERR, /* 0x219 */
	TRANS_TX_NAK_RECEIVE_ERR, /* 0x21a */
	TRANS_TX_ACK_NAK_TIMEOUT_ERR, /* 0x21b */
	TRANS_TX_CREDIT_TIMEOUT_ERR, /* 0x21c */
	TRANS_TX_IPTT_CONFLICT_ERR, /* 0x21d */
	TRANS_TX_TXFRM_TYPE_ERR, /* 0x21e */
	TRANS_TX_TXSMP_LENGTH_ERR, /* 0x21f */

	/* trans rx */
	TRANS_RX_FRAME_CRC_ERR = TRANS_RX_FAIL_BASE, /* 0x300 */
	TRANS_RX_FRAME_DONE_ERR, /* 0x301 */
	TRANS_RX_FRAME_ERRPRM_ERR, /* 0x302 */
	TRANS_RX_FRAME_NO_CREDIT_ERR, /* 0x303 */
	TRANS_RX_RSVD0_ERR, /* 0x304 */
	TRANS_RX_FRAME_OVERRUN_ERR, /* 0x305 */
	TRANS_RX_FRAME_NO_खातापूर्ण_ERR, /* 0x306 */
	TRANS_RX_LINK_BUF_OVERRUN_ERR, /* 0x307 */
	TRANS_RX_BREAK_TIMEOUT_ERR, /* 0x308 */
	TRANS_RX_BREAK_REQUEST_ERR, /* 0x309 */
	TRANS_RX_BREAK_RECEIVE_ERR, /* 0x30a */
	TRANS_RX_CLOSE_TIMEOUT_ERR, /* 0x30b */
	TRANS_RX_CLOSE_NORMAL_ERR, /* 0x30c */
	TRANS_RX_CLOSE_PHYRESET_ERR, /* 0x30d */
	TRANS_RX_WITH_CLOSE_DWS_TIMEOUT_ERR, /* 0x30e */
	TRANS_RX_WITH_CLOSE_COMINIT_ERR, /* 0x30f */
	TRANS_RX_DATA_LENGTH0_ERR, /* 0x310 */
	TRANS_RX_BAD_HASH_ERR, /* 0x311 */
	TRANS_RX_XRDY_ZERO_ERR, /* 0x312 */
	TRANS_RX_SSP_FRAME_LEN_ERR, /* 0x313 */
	TRANS_RX_TRANS_RX_RSVD1_ERR, /* 0x314 */
	TRANS_RX_NO_BALANCE_ERR, /* 0x315 */
	TRANS_RX_TRANS_RX_RSVD2_ERR, /* 0x316 */
	TRANS_RX_TRANS_RX_RSVD3_ERR, /* 0x317 */
	TRANS_RX_BAD_FRAME_TYPE_ERR, /* 0x318 */
	TRANS_RX_SMP_FRAME_LEN_ERR, /* 0x319 */
	TRANS_RX_SMP_RESP_TIMEOUT_ERR, /* 0x31a */
पूर्ण;

#घोषणा HISI_SAS_PHY_MAX_INT_NR (HISI_SAS_PHY_INT_NR * HISI_SAS_MAX_PHYS)
#घोषणा HISI_SAS_CQ_MAX_INT_NR (HISI_SAS_MAX_QUEUES)
#घोषणा HISI_SAS_FATAL_INT_NR (2)

#घोषणा HISI_SAS_MAX_INT_NR \
	(HISI_SAS_PHY_MAX_INT_NR + HISI_SAS_CQ_MAX_INT_NR +\
	HISI_SAS_FATAL_INT_NR)

अटल u32 hisi_sas_पढ़ो32(काष्ठा hisi_hba *hisi_hba, u32 off)
अणु
	व्योम __iomem *regs = hisi_hba->regs + off;

	वापस पढ़ोl(regs);
पूर्ण

अटल व्योम hisi_sas_ग_लिखो32(काष्ठा hisi_hba *hisi_hba,
				    u32 off, u32 val)
अणु
	व्योम __iomem *regs = hisi_hba->regs + off;

	ग_लिखोl(val, regs);
पूर्ण

अटल व्योम hisi_sas_phy_ग_लिखो32(काष्ठा hisi_hba *hisi_hba,
					पूर्णांक phy_no, u32 off, u32 val)
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

अटल व्योम config_phy_opt_mode_v1_hw(काष्ठा hisi_hba *hisi_hba, पूर्णांक phy_no)
अणु
	u32 cfg = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no, PHY_CFG);

	cfg &= ~PHY_CFG_DC_OPT_MSK;
	cfg |= 1 << PHY_CFG_DC_OPT_OFF;
	hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, PHY_CFG, cfg);
पूर्ण

अटल व्योम config_tx_tfe_स्वतःneg_v1_hw(काष्ठा hisi_hba *hisi_hba, पूर्णांक phy_no)
अणु
	u32 cfg = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no, PHY_CONFIG2);

	cfg &= ~PHY_CONFIG2_FORCE_TXDEEMPH_MSK;
	hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, PHY_CONFIG2, cfg);
पूर्ण

अटल व्योम config_id_frame_v1_hw(काष्ठा hisi_hba *hisi_hba, पूर्णांक phy_no)
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

अटल व्योम setup_itct_v1_hw(काष्ठा hisi_hba *hisi_hba,
			     काष्ठा hisi_sas_device *sas_dev)
अणु
	काष्ठा करोमुख्य_device *device = sas_dev->sas_device;
	काष्ठा device *dev = hisi_hba->dev;
	u64 qw0, device_id = sas_dev->device_id;
	काष्ठा hisi_sas_itct *itct = &hisi_hba->itct[device_id];
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
	शेष:
		dev_warn(dev, "setup itct: unsupported dev type (%d)\n",
			 sas_dev->dev_type);
	पूर्ण

	qw0 |= ((1 << ITCT_HDR_VALID_OFF) |
		(1 << ITCT_HDR_AWT_CONTROL_OFF) |
		(device->max_linkrate << ITCT_HDR_MAX_CONN_RATE_OFF) |
		(1 << ITCT_HDR_VALID_LINK_NUM_OFF) |
		(port->id << ITCT_HDR_PORT_ID_OFF));
	itct->qw0 = cpu_to_le64(qw0);

	/* qw1 */
	स_नकल(&sas_addr, device->sas_addr, SAS_ADDR_SIZE);
	itct->sas_addr = cpu_to_le64(__swab64(sas_addr));

	/* qw2 */
	itct->qw2 = cpu_to_le64((500ULL << ITCT_HDR_IT_NEXUS_LOSS_TL_OFF) |
				(0xff00ULL << ITCT_HDR_BUS_INACTIVE_TL_OFF) |
				(0xff00ULL << ITCT_HDR_MAX_CONN_TL_OFF) |
				(0xff00ULL << ITCT_HDR_REJ_OPEN_TL_OFF));
पूर्ण

अटल पूर्णांक clear_itct_v1_hw(काष्ठा hisi_hba *hisi_hba,
			    काष्ठा hisi_sas_device *sas_dev)
अणु
	u64 dev_id = sas_dev->device_id;
	काष्ठा hisi_sas_itct *itct = &hisi_hba->itct[dev_id];
	u64 qw0;
	u32 reg_val = hisi_sas_पढ़ो32(hisi_hba, CFG_AGING_TIME);

	reg_val |= CFG_AGING_TIME_ITCT_REL_MSK;
	hisi_sas_ग_लिखो32(hisi_hba, CFG_AGING_TIME, reg_val);

	/* मुक्त itct */
	udelay(1);
	reg_val = hisi_sas_पढ़ो32(hisi_hba, CFG_AGING_TIME);
	reg_val &= ~CFG_AGING_TIME_ITCT_REL_MSK;
	hisi_sas_ग_लिखो32(hisi_hba, CFG_AGING_TIME, reg_val);

	qw0 = le64_to_cpu(itct->qw0);
	qw0 &= ~ITCT_HDR_VALID_MSK;
	itct->qw0 = cpu_to_le64(qw0);

	वापस 0;
पूर्ण

अटल पूर्णांक reset_hw_v1_hw(काष्ठा hisi_hba *hisi_hba)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ end_समय;
	u32 val;
	काष्ठा device *dev = hisi_hba->dev;

	क्रम (i = 0; i < hisi_hba->n_phy; i++) अणु
		u32 phy_ctrl = hisi_sas_phy_पढ़ो32(hisi_hba, i, PHY_CTRL);

		phy_ctrl |= PHY_CTRL_RESET_MSK;
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, PHY_CTRL, phy_ctrl);
	पूर्ण
	msleep(1); /* It is safe to रुको क्रम 50us */

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
		/* Apply reset and disable घड़ी */
		/* clk disable reg is offset by +4 bytes from clk enable reg */
		regmap_ग_लिखो(hisi_hba->ctrl, hisi_hba->ctrl_reset_reg,
			     RESET_VALUE);
		regmap_ग_लिखो(hisi_hba->ctrl, hisi_hba->ctrl_घड़ी_ena_reg + 4,
			     RESET_VALUE);
		msleep(1);
		regmap_पढ़ो(hisi_hba->ctrl, hisi_hba->ctrl_reset_sts_reg, &val);
		अगर (RESET_VALUE != (val & RESET_VALUE)) अणु
			dev_err(dev, "Reset failed\n");
			वापस -EIO;
		पूर्ण

		/* De-reset and enable घड़ी */
		/* deनिश्चित rst reg is offset by +4 bytes from निश्चित reg */
		regmap_ग_लिखो(hisi_hba->ctrl, hisi_hba->ctrl_reset_reg + 4,
			     RESET_VALUE);
		regmap_ग_लिखो(hisi_hba->ctrl, hisi_hba->ctrl_घड़ी_ena_reg,
			     RESET_VALUE);
		msleep(1);
		regmap_पढ़ो(hisi_hba->ctrl, hisi_hba->ctrl_reset_sts_reg, &val);
		अगर (val & RESET_VALUE) अणु
			dev_err(dev, "De-reset failed\n");
			वापस -EIO;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_warn(dev, "no reset method\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम init_reg_v1_hw(काष्ठा hisi_hba *hisi_hba)
अणु
	पूर्णांक i;

	/* Global रेजिस्टरs init*/
	hisi_sas_ग_लिखो32(hisi_hba, DLVRY_QUEUE_ENABLE,
			 (u32)((1ULL << hisi_hba->queue_count) - 1));
	hisi_sas_ग_लिखो32(hisi_hba, HGC_TRANS_TASK_CNT_LIMIT, 0x11);
	hisi_sas_ग_लिखो32(hisi_hba, DEVICE_MSG_WORK_MODE, 0x1);
	hisi_sas_ग_लिखो32(hisi_hba, HGC_SAS_TXFAIL_RETRY_CTRL, 0x1ff);
	hisi_sas_ग_लिखो32(hisi_hba, HGC_ERR_STAT_EN, 0x401);
	hisi_sas_ग_लिखो32(hisi_hba, CFG_1US_TIMER_TRSH, 0x64);
	hisi_sas_ग_लिखो32(hisi_hba, HGC_GET_ITV_TIME, 0x1);
	hisi_sas_ग_लिखो32(hisi_hba, I_T_NEXUS_LOSS_TIME, 0x64);
	hisi_sas_ग_लिखो32(hisi_hba, BUS_INACTIVE_LIMIT_TIME, 0x2710);
	hisi_sas_ग_लिखो32(hisi_hba, REJECT_TO_OPEN_LIMIT_TIME, 0x1);
	hisi_sas_ग_लिखो32(hisi_hba, CFG_AGING_TIME, 0x7a12);
	hisi_sas_ग_लिखो32(hisi_hba, HGC_DFX_CFG2, 0x9c40);
	hisi_sas_ग_लिखो32(hisi_hba, FIS_LIST_BADDR_L, 0x2);
	hisi_sas_ग_लिखो32(hisi_hba, INT_COAL_EN, 0xc);
	hisi_sas_ग_लिखो32(hisi_hba, OQ_INT_COAL_TIME, 0x186a0);
	hisi_sas_ग_लिखो32(hisi_hba, OQ_INT_COAL_CNT, 1);
	hisi_sas_ग_लिखो32(hisi_hba, ENT_INT_COAL_TIME, 0x1);
	hisi_sas_ग_लिखो32(hisi_hba, ENT_INT_COAL_CNT, 0x1);
	hisi_sas_ग_लिखो32(hisi_hba, OQ_INT_SRC, 0xffffffff);
	hisi_sas_ग_लिखो32(hisi_hba, OQ_INT_SRC_MSK, 0);
	hisi_sas_ग_लिखो32(hisi_hba, ENT_INT_SRC1, 0xffffffff);
	hisi_sas_ग_लिखो32(hisi_hba, ENT_INT_SRC_MSK1, 0);
	hisi_sas_ग_लिखो32(hisi_hba, ENT_INT_SRC2, 0xffffffff);
	hisi_sas_ग_लिखो32(hisi_hba, ENT_INT_SRC_MSK2, 0);
	hisi_sas_ग_लिखो32(hisi_hba, SAS_ECC_INTR_MSK, 0);
	hisi_sas_ग_लिखो32(hisi_hba, AXI_AHB_CLK_CFG, 0x2);
	hisi_sas_ग_लिखो32(hisi_hba, CFG_SAS_CONFIG, 0x22000000);

	क्रम (i = 0; i < hisi_hba->n_phy; i++) अणु
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, PROG_PHY_LINK_RATE, 0x88a);
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, PHY_CONFIG2, 0x7c080);
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, PHY_RATE_NEGO, 0x415ee00);
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, PHY_PCN, 0x80a80000);
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, SL_TOUT_CFG, 0x7d7d7d7d);
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, DONE_RECEIVED_TIME, 0x0);
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, RXOP_CHECK_CFG_H, 0x1000);
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, DONE_RECEIVED_TIME, 0);
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, CON_CFG_DRIVER, 0x13f0a);
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, CHL_INT_COAL_EN, 3);
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, DONE_RECEIVED_TIME, 8);
	पूर्ण

	क्रम (i = 0; i < hisi_hba->queue_count; i++) अणु
		/* Delivery queue */
		hisi_sas_ग_लिखो32(hisi_hba,
				 DLVRY_Q_0_BASE_ADDR_HI + (i * 0x14),
				 upper_32_bits(hisi_hba->cmd_hdr_dma[i]));

		hisi_sas_ग_लिखो32(hisi_hba,
				 DLVRY_Q_0_BASE_ADDR_LO + (i * 0x14),
				 lower_32_bits(hisi_hba->cmd_hdr_dma[i]));

		hisi_sas_ग_लिखो32(hisi_hba,
				 DLVRY_Q_0_DEPTH + (i * 0x14),
				 HISI_SAS_QUEUE_SLOTS);

		/* Completion queue */
		hisi_sas_ग_लिखो32(hisi_hba,
				 COMPL_Q_0_BASE_ADDR_HI + (i * 0x14),
				 upper_32_bits(hisi_hba->complete_hdr_dma[i]));

		hisi_sas_ग_लिखो32(hisi_hba,
				 COMPL_Q_0_BASE_ADDR_LO + (i * 0x14),
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
	hisi_sas_ग_लिखो32(hisi_hba, BROKEN_MSG_ADDR_LO,
			 lower_32_bits(hisi_hba->अवरोधpoपूर्णांक_dma));

	hisi_sas_ग_लिखो32(hisi_hba, BROKEN_MSG_ADDR_HI,
			 upper_32_bits(hisi_hba->अवरोधpoपूर्णांक_dma));
पूर्ण

अटल पूर्णांक hw_init_v1_hw(काष्ठा hisi_hba *hisi_hba)
अणु
	काष्ठा device *dev = hisi_hba->dev;
	पूर्णांक rc;

	rc = reset_hw_v1_hw(hisi_hba);
	अगर (rc) अणु
		dev_err(dev, "hisi_sas_reset_hw failed, rc=%d\n", rc);
		वापस rc;
	पूर्ण

	msleep(100);
	init_reg_v1_hw(hisi_hba);

	वापस 0;
पूर्ण

अटल व्योम enable_phy_v1_hw(काष्ठा hisi_hba *hisi_hba, पूर्णांक phy_no)
अणु
	u32 cfg = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no, PHY_CFG);

	cfg |= PHY_CFG_ENA_MSK;
	hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, PHY_CFG, cfg);
पूर्ण

अटल व्योम disable_phy_v1_hw(काष्ठा hisi_hba *hisi_hba, पूर्णांक phy_no)
अणु
	u32 cfg = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no, PHY_CFG);

	cfg &= ~PHY_CFG_ENA_MSK;
	hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, PHY_CFG, cfg);
पूर्ण

अटल व्योम start_phy_v1_hw(काष्ठा hisi_hba *hisi_hba, पूर्णांक phy_no)
अणु
	config_id_frame_v1_hw(hisi_hba, phy_no);
	config_phy_opt_mode_v1_hw(hisi_hba, phy_no);
	config_tx_tfe_स्वतःneg_v1_hw(hisi_hba, phy_no);
	enable_phy_v1_hw(hisi_hba, phy_no);
पूर्ण

अटल व्योम phy_hard_reset_v1_hw(काष्ठा hisi_hba *hisi_hba, पूर्णांक phy_no)
अणु
	hisi_sas_phy_enable(hisi_hba, phy_no, 0);
	msleep(100);
	hisi_sas_phy_enable(hisi_hba, phy_no, 1);
पूर्ण

अटल व्योम start_phys_v1_hw(काष्ठा समयr_list *t)
अणु
	काष्ठा hisi_hba *hisi_hba = from_समयr(hisi_hba, t, समयr);
	पूर्णांक i;

	क्रम (i = 0; i < hisi_hba->n_phy; i++) अणु
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, CHL_INT2_MSK, 0x12a);
		hisi_sas_phy_enable(hisi_hba, i, 1);
	पूर्ण
पूर्ण

अटल व्योम phys_init_v1_hw(काष्ठा hisi_hba *hisi_hba)
अणु
	पूर्णांक i;
	काष्ठा समयr_list *समयr = &hisi_hba->समयr;

	क्रम (i = 0; i < hisi_hba->n_phy; i++) अणु
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, CHL_INT2_MSK, 0x6a);
		hisi_sas_phy_पढ़ो32(hisi_hba, i, CHL_INT2_MSK);
	पूर्ण

	समयr_setup(समयr, start_phys_v1_hw, 0);
	mod_समयr(समयr, jअगरfies + HZ);
पूर्ण

अटल व्योम sl_notअगरy_ssp_v1_hw(काष्ठा hisi_hba *hisi_hba, पूर्णांक phy_no)
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

अटल क्रमागत sas_linkrate phy_get_max_linkrate_v1_hw(व्योम)
अणु
	वापस SAS_LINK_RATE_6_0_GBPS;
पूर्ण

अटल व्योम phy_set_linkrate_v1_hw(काष्ठा hisi_hba *hisi_hba, पूर्णांक phy_no,
		काष्ठा sas_phy_linkrates *r)
अणु
	क्रमागत sas_linkrate max = r->maximum_linkrate;
	u32 prog_phy_link_rate = 0x800;

	prog_phy_link_rate |= hisi_sas_get_prog_phy_linkrate_mask(max);
	hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, PROG_PHY_LINK_RATE,
			     prog_phy_link_rate);
पूर्ण

अटल पूर्णांक get_wideport_biपंचांगap_v1_hw(काष्ठा hisi_hba *hisi_hba, पूर्णांक port_id)
अणु
	पूर्णांक i, biपंचांगap = 0;
	u32 phy_port_num_ma = hisi_sas_पढ़ो32(hisi_hba, PHY_PORT_NUM_MA);

	क्रम (i = 0; i < hisi_hba->n_phy; i++)
		अगर (((phy_port_num_ma >> (i * 4)) & 0xf) == port_id)
			biपंचांगap |= 1 << i;

	वापस biपंचांगap;
पूर्ण

/* DQ lock must be taken here */
अटल व्योम start_delivery_v1_hw(काष्ठा hisi_sas_dq *dq)
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

अटल व्योम prep_prd_sge_v1_hw(काष्ठा hisi_hba *hisi_hba,
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

अटल व्योम prep_smp_v1_hw(काष्ठा hisi_hba *hisi_hba,
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
			       (1 << CMD_HDR_MODE_OFF) | /* ini mode */
			       (2 << CMD_HDR_CMD_OFF)); /* smp */

	/* map itct entry */
	hdr->dw1 = cpu_to_le32(sas_dev->device_id << CMD_HDR_DEVICE_ID_OFF);

	/* dw2 */
	hdr->dw2 = cpu_to_le32((((req_len-4)/4) << CMD_HDR_CFL_OFF) |
			       (HISI_SAS_MAX_SMP_RESP_SZ/4 <<
			       CMD_HDR_MRFL_OFF));

	hdr->transfer_tags = cpu_to_le32(slot->idx << CMD_HDR_IPTT_OFF);

	hdr->cmd_table_addr = cpu_to_le64(req_dma_addr);
	hdr->sts_buffer_addr = cpu_to_le64(hisi_sas_status_buf_addr_dma(slot));
पूर्ण

अटल व्योम prep_ssp_v1_hw(काष्ठा hisi_hba *hisi_hba,
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
	u8 *buf_cmd, fburst = 0;
	u32 dw1, dw2;

	/* create header */
	hdr->dw0 = cpu_to_le32((1 << CMD_HDR_RESP_REPORT_OFF) |
			       (0x2 << CMD_HDR_TLR_CTRL_OFF) |
			       (port->id << CMD_HDR_PORT_OFF) |
			       (priority << CMD_HDR_PRIORITY_OFF) |
			       (1 << CMD_HDR_MODE_OFF) | /* ini mode */
			       (1 << CMD_HDR_CMD_OFF)); /* ssp */

	dw1 = 1 << CMD_HDR_VERIFY_DTL_OFF;

	अगर (पंचांगf) अणु
		dw1 |= 3 << CMD_HDR_SSP_FRAME_TYPE_OFF;
	पूर्ण अन्यथा अणु
		चयन (scsi_cmnd->sc_data_direction) अणु
		हाल DMA_TO_DEVICE:
			dw1 |= 2 << CMD_HDR_SSP_FRAME_TYPE_OFF;
			has_data = 1;
			अवरोध;
		हाल DMA_FROM_DEVICE:
			dw1 |= 1 << CMD_HDR_SSP_FRAME_TYPE_OFF;
			has_data = 1;
			अवरोध;
		शेष:
			dw1 |= 0 << CMD_HDR_SSP_FRAME_TYPE_OFF;
		पूर्ण
	पूर्ण

	/* map itct entry */
	dw1 |= sas_dev->device_id << CMD_HDR_DEVICE_ID_OFF;
	hdr->dw1 = cpu_to_le32(dw1);

	अगर (पंचांगf) अणु
		dw2 = ((माप(काष्ठा ssp_पंचांगf_iu) +
			माप(काष्ठा ssp_frame_hdr)+3)/4) <<
			CMD_HDR_CFL_OFF;
	पूर्ण अन्यथा अणु
		dw2 = ((माप(काष्ठा ssp_command_iu) +
			माप(काष्ठा ssp_frame_hdr)+3)/4) <<
			CMD_HDR_CFL_OFF;
	पूर्ण

	dw2 |= (HISI_SAS_MAX_SSP_RESP_SZ/4) << CMD_HDR_MRFL_OFF;

	hdr->transfer_tags = cpu_to_le32(slot->idx << CMD_HDR_IPTT_OFF);

	अगर (has_data)
		prep_prd_sge_v1_hw(hisi_hba, slot, hdr, task->scatter,
					slot->n_elem);

	hdr->data_transfer_len = cpu_to_le32(task->total_xfer_len);
	hdr->cmd_table_addr = cpu_to_le64(hisi_sas_cmd_hdr_addr_dma(slot));
	hdr->sts_buffer_addr = cpu_to_le64(hisi_sas_status_buf_addr_dma(slot));

	buf_cmd = hisi_sas_cmd_hdr_addr_mem(slot) +
		माप(काष्ठा ssp_frame_hdr);
	अगर (task->ssp_task.enable_first_burst) अणु
		fburst = (1 << 7);
		dw2 |= 1 << CMD_HDR_FIRST_BURST_OFF;
	पूर्ण
	hdr->dw2 = cpu_to_le32(dw2);

	स_नकल(buf_cmd, &task->ssp_task.LUN, 8);
	अगर (!पंचांगf) अणु
		buf_cmd[9] = fburst | task->ssp_task.task_attr |
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

/* by शेष, task resp is complete */
अटल व्योम slot_err_v1_hw(काष्ठा hisi_hba *hisi_hba,
			   काष्ठा sas_task *task,
			   काष्ठा hisi_sas_slot *slot)
अणु
	काष्ठा task_status_काष्ठा *ts = &task->task_status;
	काष्ठा hisi_sas_err_record_v1 *err_record =
			hisi_sas_status_buf_addr_mem(slot);
	काष्ठा device *dev = hisi_hba->dev;

	चयन (task->task_proto) अणु
	हाल SAS_PROTOCOL_SSP:
	अणु
		पूर्णांक error = -1;
		u32 dma_err_type = le32_to_cpu(err_record->dma_err_type);
		u32 dma_tx_err_type = ((dma_err_type &
					ERR_HDR_DMA_TX_ERR_TYPE_MSK)) >>
					ERR_HDR_DMA_TX_ERR_TYPE_OFF;
		u32 dma_rx_err_type = ((dma_err_type &
					ERR_HDR_DMA_RX_ERR_TYPE_MSK)) >>
					ERR_HDR_DMA_RX_ERR_TYPE_OFF;
		u32 trans_tx_fail_type =
				le32_to_cpu(err_record->trans_tx_fail_type);
		u32 trans_rx_fail_type =
				le32_to_cpu(err_record->trans_rx_fail_type);

		अगर (dma_tx_err_type) अणु
			/* dma tx err */
			error = ffs(dma_tx_err_type)
				- 1 + DMA_TX_ERR_BASE;
		पूर्ण अन्यथा अगर (dma_rx_err_type) अणु
			/* dma rx err */
			error = ffs(dma_rx_err_type)
				- 1 + DMA_RX_ERR_BASE;
		पूर्ण अन्यथा अगर (trans_tx_fail_type) अणु
			/* trans tx err */
			error = ffs(trans_tx_fail_type)
				- 1 + TRANS_TX_FAIL_BASE;
		पूर्ण अन्यथा अगर (trans_rx_fail_type) अणु
			/* trans rx err */
			error = ffs(trans_rx_fail_type)
				- 1 + TRANS_RX_FAIL_BASE;
		पूर्ण

		चयन (error) अणु
		हाल DMA_TX_DATA_UNDERFLOW_ERR:
		हाल DMA_RX_DATA_UNDERFLOW_ERR:
		अणु
			ts->residual = 0;
			ts->stat = SAS_DATA_UNDERRUN;
			अवरोध;
		पूर्ण
		हाल DMA_TX_DATA_SGL_OVERFLOW_ERR:
		हाल DMA_TX_DIF_SGL_OVERFLOW_ERR:
		हाल DMA_TX_XFER_RDY_LENGTH_OVERFLOW_ERR:
		हाल DMA_RX_DATA_OVERFLOW_ERR:
		हाल TRANS_RX_FRAME_OVERRUN_ERR:
		हाल TRANS_RX_LINK_BUF_OVERRUN_ERR:
		अणु
			ts->stat = SAS_DATA_OVERRUN;
			ts->residual = 0;
			अवरोध;
		पूर्ण
		हाल TRANS_TX_PHY_NOT_ENABLE_ERR:
		अणु
			ts->stat = SAS_PHY_DOWN;
			अवरोध;
		पूर्ण
		हाल TRANS_TX_OPEN_REJCT_WRONG_DEST_ERR:
		हाल TRANS_TX_OPEN_REJCT_ZONE_VIOLATION_ERR:
		हाल TRANS_TX_OPEN_REJCT_BY_OTHER_ERR:
		हाल TRANS_TX_OPEN_REJCT_AIP_TIMEOUT_ERR:
		हाल TRANS_TX_OPEN_REJCT_STP_BUSY_ERR:
		हाल TRANS_TX_OPEN_REJCT_PROTOCOL_NOT_SUPPORT_ERR:
		हाल TRANS_TX_OPEN_REJCT_RATE_NOT_SUPPORT_ERR:
		हाल TRANS_TX_OPEN_REJCT_BAD_DEST_ERR:
		हाल TRANS_TX_OPEN_BREAK_RECEIVE_ERR:
		हाल TRANS_TX_OPEN_REJCT_PATHWAY_BLOCKED_ERR:
		हाल TRANS_TX_OPEN_REJCT_NO_DEST_ERR:
		हाल TRANS_TX_OPEN_RETRY_ERR:
		अणु
			ts->stat = SAS_OPEN_REJECT;
			ts->खोलो_rej_reason = SAS_OREJ_UNKNOWN;
			अवरोध;
		पूर्ण
		हाल TRANS_TX_OPEN_TIMEOUT_ERR:
		अणु
			ts->stat = SAS_OPEN_TO;
			अवरोध;
		पूर्ण
		हाल TRANS_TX_NAK_RECEIVE_ERR:
		हाल TRANS_TX_ACK_NAK_TIMEOUT_ERR:
		अणु
			ts->stat = SAS_NAK_R_ERR;
			अवरोध;
		पूर्ण
		हाल TRANS_TX_CREDIT_TIMEOUT_ERR:
		हाल TRANS_TX_CLOSE_NORMAL_ERR:
		अणु
			/* This will request a retry */
			ts->stat = SAS_QUEUE_FULL;
			slot->पात = 1;
			अवरोध;
		पूर्ण
		शेष:
		अणु
			ts->stat = SAM_STAT_CHECK_CONDITION;
			अवरोध;
		पूर्ण
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
		dev_err(dev, "slot err: SATA/STP not supported\n");
	पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

पूर्ण

अटल व्योम slot_complete_v1_hw(काष्ठा hisi_hba *hisi_hba,
				काष्ठा hisi_sas_slot *slot)
अणु
	काष्ठा sas_task *task = slot->task;
	काष्ठा hisi_sas_device *sas_dev;
	काष्ठा device *dev = hisi_hba->dev;
	काष्ठा task_status_काष्ठा *ts;
	काष्ठा करोमुख्य_device *device;
	काष्ठा hisi_sas_complete_v1_hdr *complete_queue =
			hisi_hba->complete_hdr[slot->cmplt_queue];
	काष्ठा hisi_sas_complete_v1_hdr *complete_hdr;
	अचिन्हित दीर्घ flags;
	u32 cmplt_hdr_data;

	complete_hdr = &complete_queue[slot->cmplt_queue_slot];
	cmplt_hdr_data = le32_to_cpu(complete_hdr->data);

	अगर (unlikely(!task || !task->lldd_task || !task->dev))
		वापस;

	ts = &task->task_status;
	device = task->dev;
	sas_dev = device->lldd_dev;

	spin_lock_irqsave(&task->task_state_lock, flags);
	task->task_state_flags &=
		~(SAS_TASK_STATE_PENDING | SAS_TASK_AT_INITIATOR);
	task->task_state_flags |= SAS_TASK_STATE_DONE;
	spin_unlock_irqrestore(&task->task_state_lock, flags);

	स_रखो(ts, 0, माप(*ts));
	ts->resp = SAS_TASK_COMPLETE;

	अगर (unlikely(!sas_dev)) अणु
		dev_dbg(dev, "slot complete: port has no device\n");
		ts->stat = SAS_PHY_DOWN;
		जाओ out;
	पूर्ण

	अगर (cmplt_hdr_data & CMPLT_HDR_IO_CFG_ERR_MSK) अणु
		u32 info_reg = hisi_sas_पढ़ो32(hisi_hba, HGC_INVLD_DQE_INFO);

		अगर (info_reg & HGC_INVLD_DQE_INFO_DQ_MSK)
			dev_err(dev, "slot complete: [%d:%d] has dq IPTT err\n",
				slot->cmplt_queue, slot->cmplt_queue_slot);

		अगर (info_reg & HGC_INVLD_DQE_INFO_TYPE_MSK)
			dev_err(dev, "slot complete: [%d:%d] has dq type err\n",
				slot->cmplt_queue, slot->cmplt_queue_slot);

		अगर (info_reg & HGC_INVLD_DQE_INFO_FORCE_MSK)
			dev_err(dev, "slot complete: [%d:%d] has dq force phy err\n",
				slot->cmplt_queue, slot->cmplt_queue_slot);

		अगर (info_reg & HGC_INVLD_DQE_INFO_PHY_MSK)
			dev_err(dev, "slot complete: [%d:%d] has dq phy id err\n",
				slot->cmplt_queue, slot->cmplt_queue_slot);

		अगर (info_reg & HGC_INVLD_DQE_INFO_ABORT_MSK)
			dev_err(dev, "slot complete: [%d:%d] has dq abort flag err\n",
				slot->cmplt_queue, slot->cmplt_queue_slot);

		अगर (info_reg & HGC_INVLD_DQE_INFO_IPTT_OF_MSK)
			dev_err(dev, "slot complete: [%d:%d] has dq IPTT or ICT err\n",
				slot->cmplt_queue, slot->cmplt_queue_slot);

		अगर (info_reg & HGC_INVLD_DQE_INFO_SSP_ERR_MSK)
			dev_err(dev, "slot complete: [%d:%d] has dq SSP frame type err\n",
				slot->cmplt_queue, slot->cmplt_queue_slot);

		अगर (info_reg & HGC_INVLD_DQE_INFO_OFL_MSK)
			dev_err(dev, "slot complete: [%d:%d] has dq order frame len err\n",
				slot->cmplt_queue, slot->cmplt_queue_slot);

		ts->stat = SAS_OPEN_REJECT;
		ts->खोलो_rej_reason = SAS_OREJ_UNKNOWN;
		जाओ out;
	पूर्ण

	अगर (cmplt_hdr_data & CMPLT_HDR_ERR_RCRD_XFRD_MSK &&
		!(cmplt_hdr_data & CMPLT_HDR_RSPNS_XFRD_MSK)) अणु

		slot_err_v1_hw(hisi_hba, task, slot);
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
		dev_err(dev, "slot complete: SATA/STP not supported\n");
		अवरोध;

	शेष:
		ts->stat = SAM_STAT_CHECK_CONDITION;
		अवरोध;
	पूर्ण

	अगर (!slot->port->port_attached) अणु
		dev_err(dev, "slot complete: port %d has removed\n",
			slot->port->sas_port.id);
		ts->stat = SAS_PHY_DOWN;
	पूर्ण

out:
	hisi_sas_slot_task_मुक्त(hisi_hba, task, slot);

	अगर (task->task_करोne)
		task->task_करोne(task);
पूर्ण

/* Interrupts */
अटल irqवापस_t पूर्णांक_phyup_v1_hw(पूर्णांक irq_no, व्योम *p)
अणु
	काष्ठा hisi_sas_phy *phy = p;
	काष्ठा hisi_hba *hisi_hba = phy->hisi_hba;
	काष्ठा device *dev = hisi_hba->dev;
	काष्ठा asd_sas_phy *sas_phy = &phy->sas_phy;
	पूर्णांक i, phy_no = sas_phy->id;
	u32 irq_value, context, port_id, link_rate;
	u32 *frame_rcvd = (u32 *)sas_phy->frame_rcvd;
	काष्ठा sas_identअगरy_frame *id = (काष्ठा sas_identअगरy_frame *)frame_rcvd;
	irqवापस_t res = IRQ_HANDLED;
	अचिन्हित दीर्घ flags;

	irq_value = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no, CHL_INT2);
	अगर (!(irq_value & CHL_INT2_SL_PHY_ENA_MSK)) अणु
		dev_dbg(dev, "phyup: irq_value = %x not set enable bit\n",
			irq_value);
		res = IRQ_NONE;
		जाओ end;
	पूर्ण

	context = hisi_sas_पढ़ो32(hisi_hba, PHY_CONTEXT);
	अगर (context & 1 << phy_no) अणु
		dev_err(dev, "phyup: phy%d SATA attached equipment\n",
			phy_no);
		जाओ end;
	पूर्ण

	port_id = (hisi_sas_पढ़ो32(hisi_hba, PHY_PORT_NUM_MA) >> (4 * phy_no))
		  & 0xf;
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

	/* Get the linkrate */
	link_rate = hisi_sas_पढ़ो32(hisi_hba, PHY_CONN_RATE);
	link_rate = (link_rate >> (phy_no * 4)) & 0xf;
	sas_phy->linkrate = link_rate;
	sas_phy->oob_mode = SAS_OOB_MODE;
	स_नकल(sas_phy->attached_sas_addr,
		&id->sas_addr, SAS_ADDR_SIZE);
	dev_info(dev, "phyup: phy%d link_rate=%d\n",
		 phy_no, link_rate);
	phy->port_id = port_id;
	phy->phy_type &= ~(PORT_TYPE_SAS | PORT_TYPE_SATA);
	phy->phy_type |= PORT_TYPE_SAS;
	phy->phy_attached = 1;
	phy->identअगरy.device_type = id->dev_type;
	phy->frame_rcvd_size =	माप(काष्ठा sas_identअगरy_frame);
	अगर (phy->identअगरy.device_type == SAS_END_DEVICE)
		phy->identअगरy.target_port_protocols =
			SAS_PROTOCOL_SSP;
	अन्यथा अगर (phy->identअगरy.device_type != SAS_PHY_UNUSED)
		phy->identअगरy.target_port_protocols =
			SAS_PROTOCOL_SMP;
	hisi_sas_notअगरy_phy_event(phy, HISI_PHYE_PHY_UP);

	spin_lock_irqsave(&phy->lock, flags);
	अगर (phy->reset_completion) अणु
		phy->in_reset = 0;
		complete(phy->reset_completion);
	पूर्ण
	spin_unlock_irqrestore(&phy->lock, flags);

end:
	hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, CHL_INT2,
			     CHL_INT2_SL_PHY_ENA_MSK);

	अगर (irq_value & CHL_INT2_SL_PHY_ENA_MSK) अणु
		u32 chl_पूर्णांक0 = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no, CHL_INT0);

		chl_पूर्णांक0 &= ~CHL_INT0_PHYCTRL_NOTRDY_MSK;
		hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, CHL_INT0, chl_पूर्णांक0);
		hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, CHL_INT0_MSK, 0x3ce3ee);
	पूर्ण

	वापस res;
पूर्ण

अटल irqवापस_t पूर्णांक_bcast_v1_hw(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा hisi_sas_phy *phy = p;
	काष्ठा hisi_hba *hisi_hba = phy->hisi_hba;
	काष्ठा asd_sas_phy *sas_phy = &phy->sas_phy;
	काष्ठा device *dev = hisi_hba->dev;
	पूर्णांक phy_no = sas_phy->id;
	u32 irq_value;
	irqवापस_t res = IRQ_HANDLED;

	irq_value = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no, CHL_INT2);

	अगर (!(irq_value & CHL_INT2_SL_RX_BC_ACK_MSK)) अणु
		dev_err(dev, "bcast: irq_value = %x not set enable bit\n",
			irq_value);
		res = IRQ_NONE;
		जाओ end;
	पूर्ण

	अगर (!test_bit(HISI_SAS_RESET_BIT, &hisi_hba->flags))
		sas_notअगरy_port_event(sas_phy, PORTE_BROADCAST_RCVD,
				      GFP_ATOMIC);

end:
	hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, CHL_INT2,
			     CHL_INT2_SL_RX_BC_ACK_MSK);

	वापस res;
पूर्ण

अटल irqवापस_t पूर्णांक_abnormal_v1_hw(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा hisi_sas_phy *phy = p;
	काष्ठा hisi_hba *hisi_hba = phy->hisi_hba;
	काष्ठा device *dev = hisi_hba->dev;
	काष्ठा asd_sas_phy *sas_phy = &phy->sas_phy;
	u32 irq_value, irq_mask_old;
	पूर्णांक phy_no = sas_phy->id;

	/* mask_पूर्णांक0 */
	irq_mask_old = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no, CHL_INT0_MSK);
	hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, CHL_INT0_MSK, 0x3fffff);

	/* पढ़ो पूर्णांक0 */
	irq_value = hisi_sas_phy_पढ़ो32(hisi_hba, phy_no, CHL_INT0);

	अगर (irq_value & CHL_INT0_PHYCTRL_NOTRDY_MSK) अणु
		u32 phy_state = hisi_sas_पढ़ो32(hisi_hba, PHY_STATE);

		hisi_sas_phy_करोwn(hisi_hba, phy_no,
				  (phy_state & 1 << phy_no) ? 1 : 0,
				  GFP_ATOMIC);
	पूर्ण

	अगर (irq_value & CHL_INT0_ID_TIMEOUT_MSK)
		dev_dbg(dev, "abnormal: ID_TIMEOUT phy%d identify timeout\n",
			phy_no);

	अगर (irq_value & CHL_INT0_DWS_LOST_MSK)
		dev_dbg(dev, "abnormal: DWS_LOST phy%d dws lost\n", phy_no);

	अगर (irq_value & CHL_INT0_SN_FAIL_NGR_MSK)
		dev_dbg(dev, "abnormal: SN_FAIL_NGR phy%d sn fail ngr\n",
			phy_no);

	अगर (irq_value & CHL_INT0_SL_IDAF_FAIL_MSK ||
		irq_value & CHL_INT0_SL_OPAF_FAIL_MSK)
		dev_dbg(dev, "abnormal: SL_ID/OPAF_FAIL phy%d check adr frm err\n",
			phy_no);

	अगर (irq_value & CHL_INT0_SL_PS_FAIL_OFF)
		dev_dbg(dev, "abnormal: SL_PS_FAIL phy%d fail\n", phy_no);

	/* ग_लिखो to zero */
	hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, CHL_INT0, irq_value);

	अगर (irq_value & CHL_INT0_PHYCTRL_NOTRDY_MSK)
		hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, CHL_INT0_MSK,
				0x3fffff & ~CHL_INT0_MSK_PHYCTRL_NOTRDY_MSK);
	अन्यथा
		hisi_sas_phy_ग_लिखो32(hisi_hba, phy_no, CHL_INT0_MSK,
				irq_mask_old);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t cq_पूर्णांकerrupt_v1_hw(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा hisi_sas_cq *cq = p;
	काष्ठा hisi_hba *hisi_hba = cq->hisi_hba;
	काष्ठा hisi_sas_slot *slot;
	पूर्णांक queue = cq->id;
	काष्ठा hisi_sas_complete_v1_hdr *complete_queue =
			(काष्ठा hisi_sas_complete_v1_hdr *)
			hisi_hba->complete_hdr[queue];
	u32 rd_poपूर्णांक = cq->rd_poपूर्णांक, wr_poपूर्णांक;

	spin_lock(&hisi_hba->lock);
	hisi_sas_ग_लिखो32(hisi_hba, OQ_INT_SRC, 1 << queue);
	wr_poपूर्णांक = hisi_sas_पढ़ो32(hisi_hba,
			COMPL_Q_0_WR_PTR + (0x14 * queue));

	जबतक (rd_poपूर्णांक != wr_poपूर्णांक) अणु
		काष्ठा hisi_sas_complete_v1_hdr *complete_hdr;
		पूर्णांक idx;
		u32 cmplt_hdr_data;

		complete_hdr = &complete_queue[rd_poपूर्णांक];
		cmplt_hdr_data = le32_to_cpu(complete_hdr->data);
		idx = (cmplt_hdr_data & CMPLT_HDR_IPTT_MSK) >>
		      CMPLT_HDR_IPTT_OFF;
		slot = &hisi_hba->slot_info[idx];

		/* The completion queue and queue slot index are not
		 * necessarily the same as the delivery queue and
		 * queue slot index.
		 */
		slot->cmplt_queue_slot = rd_poपूर्णांक;
		slot->cmplt_queue = queue;
		slot_complete_v1_hw(hisi_hba, slot);

		अगर (++rd_poपूर्णांक >= HISI_SAS_QUEUE_SLOTS)
			rd_poपूर्णांक = 0;
	पूर्ण

	/* update rd_poपूर्णांक */
	cq->rd_poपूर्णांक = rd_poपूर्णांक;
	hisi_sas_ग_लिखो32(hisi_hba, COMPL_Q_0_RD_PTR + (0x14 * queue), rd_poपूर्णांक);
	spin_unlock(&hisi_hba->lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t fatal_ecc_पूर्णांक_v1_hw(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा hisi_hba *hisi_hba = p;
	काष्ठा device *dev = hisi_hba->dev;
	u32 ecc_पूर्णांक = hisi_sas_पढ़ो32(hisi_hba, SAS_ECC_INTR);

	अगर (ecc_पूर्णांक & SAS_ECC_INTR_DQ_ECC1B_MSK) अणु
		u32 ecc_err = hisi_sas_पढ़ो32(hisi_hba, HGC_ECC_ERR);

		panic("%s: Fatal DQ 1b ECC interrupt (0x%x)\n",
		      dev_name(dev), ecc_err);
	पूर्ण

	अगर (ecc_पूर्णांक & SAS_ECC_INTR_DQ_ECCBAD_MSK) अणु
		u32 addr = (hisi_sas_पढ़ो32(hisi_hba, HGC_DQ_ECC_ADDR) &
				HGC_DQ_ECC_ADDR_BAD_MSK) >>
				HGC_DQ_ECC_ADDR_BAD_OFF;

		panic("%s: Fatal DQ RAM ECC interrupt @ 0x%08x\n",
		      dev_name(dev), addr);
	पूर्ण

	अगर (ecc_पूर्णांक & SAS_ECC_INTR_IOST_ECC1B_MSK) अणु
		u32 ecc_err = hisi_sas_पढ़ो32(hisi_hba, HGC_ECC_ERR);

		panic("%s: Fatal IOST 1b ECC interrupt (0x%x)\n",
		      dev_name(dev), ecc_err);
	पूर्ण

	अगर (ecc_पूर्णांक & SAS_ECC_INTR_IOST_ECCBAD_MSK) अणु
		u32 addr = (hisi_sas_पढ़ो32(hisi_hba, HGC_IOST_ECC_ADDR) &
				HGC_IOST_ECC_ADDR_BAD_MSK) >>
				HGC_IOST_ECC_ADDR_BAD_OFF;

		panic("%s: Fatal IOST RAM ECC interrupt @ 0x%08x\n",
		      dev_name(dev), addr);
	पूर्ण

	अगर (ecc_पूर्णांक & SAS_ECC_INTR_ITCT_ECCBAD_MSK) अणु
		u32 addr = (hisi_sas_पढ़ो32(hisi_hba, HGC_ITCT_ECC_ADDR) &
				HGC_ITCT_ECC_ADDR_BAD_MSK) >>
				HGC_ITCT_ECC_ADDR_BAD_OFF;

		panic("%s: Fatal TCT RAM ECC interrupt @ 0x%08x\n",
		      dev_name(dev), addr);
	पूर्ण

	अगर (ecc_पूर्णांक & SAS_ECC_INTR_ITCT_ECC1B_MSK) अणु
		u32 ecc_err = hisi_sas_पढ़ो32(hisi_hba, HGC_ECC_ERR);

		panic("%s: Fatal ITCT 1b ECC interrupt (0x%x)\n",
		      dev_name(dev), ecc_err);
	पूर्ण

	hisi_sas_ग_लिखो32(hisi_hba, SAS_ECC_INTR, ecc_पूर्णांक | 0x3f);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t fatal_axi_पूर्णांक_v1_hw(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा hisi_hba *hisi_hba = p;
	काष्ठा device *dev = hisi_hba->dev;
	u32 axi_पूर्णांक = hisi_sas_पढ़ो32(hisi_hba, ENT_INT_SRC2);
	u32 axi_info = hisi_sas_पढ़ो32(hisi_hba, HGC_AXI_FIFO_ERR_INFO);

	अगर (axi_पूर्णांक & ENT_INT_SRC2_DQ_CFG_ERR_MSK)
		panic("%s: Fatal DQ_CFG_ERR interrupt (0x%x)\n",
		      dev_name(dev), axi_info);

	अगर (axi_पूर्णांक & ENT_INT_SRC2_CQ_CFG_ERR_MSK)
		panic("%s: Fatal CQ_CFG_ERR interrupt (0x%x)\n",
		      dev_name(dev), axi_info);

	अगर (axi_पूर्णांक & ENT_INT_SRC2_AXI_WRONG_INT_MSK)
		panic("%s: Fatal AXI_WRONG_INT interrupt (0x%x)\n",
		      dev_name(dev), axi_info);

	अगर (axi_पूर्णांक & ENT_INT_SRC2_AXI_OVERLF_INT_MSK)
		panic("%s: Fatal AXI_OVERLF_INT incorrect interrupt (0x%x)\n",
		      dev_name(dev), axi_info);

	hisi_sas_ग_लिखो32(hisi_hba, ENT_INT_SRC2, axi_पूर्णांक | 0x30000000);

	वापस IRQ_HANDLED;
पूर्ण

अटल irq_handler_t phy_पूर्णांकerrupts[HISI_SAS_PHY_INT_NR] = अणु
	पूर्णांक_bcast_v1_hw,
	पूर्णांक_phyup_v1_hw,
	पूर्णांक_abnormal_v1_hw
पूर्ण;

अटल irq_handler_t fatal_पूर्णांकerrupts[HISI_SAS_MAX_QUEUES] = अणु
	fatal_ecc_पूर्णांक_v1_hw,
	fatal_axi_पूर्णांक_v1_hw
पूर्ण;

अटल पूर्णांक पूर्णांकerrupt_init_v1_hw(काष्ठा hisi_hba *hisi_hba)
अणु
	काष्ठा platक्रमm_device *pdev = hisi_hba->platक्रमm_dev;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक i, j, irq, rc, idx;

	क्रम (i = 0; i < hisi_hba->n_phy; i++) अणु
		काष्ठा hisi_sas_phy *phy = &hisi_hba->phy[i];

		idx = i * HISI_SAS_PHY_INT_NR;
		क्रम (j = 0; j < HISI_SAS_PHY_INT_NR; j++, idx++) अणु
			irq = platक्रमm_get_irq(pdev, idx);
			अगर (irq < 0) अणु
				dev_err(dev, "irq init: fail map phy interrupt %d\n",
					idx);
				वापस -ENOENT;
			पूर्ण

			rc = devm_request_irq(dev, irq, phy_पूर्णांकerrupts[j], 0,
					      DRV_NAME " phy", phy);
			अगर (rc) अणु
				dev_err(dev, "irq init: could not request phy interrupt %d, rc=%d\n",
					irq, rc);
				वापस -ENOENT;
			पूर्ण
		पूर्ण
	पूर्ण

	idx = hisi_hba->n_phy * HISI_SAS_PHY_INT_NR;
	क्रम (i = 0; i < hisi_hba->queue_count; i++, idx++) अणु
		irq = platक्रमm_get_irq(pdev, idx);
		अगर (irq < 0) अणु
			dev_err(dev, "irq init: could not map cq interrupt %d\n",
				idx);
			वापस -ENOENT;
		पूर्ण

		rc = devm_request_irq(dev, irq, cq_पूर्णांकerrupt_v1_hw, 0,
				      DRV_NAME " cq", &hisi_hba->cq[i]);
		अगर (rc) अणु
			dev_err(dev, "irq init: could not request cq interrupt %d, rc=%d\n",
				irq, rc);
			वापस -ENOENT;
		पूर्ण
	पूर्ण

	idx = (hisi_hba->n_phy * HISI_SAS_PHY_INT_NR) + hisi_hba->queue_count;
	क्रम (i = 0; i < HISI_SAS_FATAL_INT_NR; i++, idx++) अणु
		irq = platक्रमm_get_irq(pdev, idx);
		अगर (irq < 0) अणु
			dev_err(dev, "irq init: could not map fatal interrupt %d\n",
				idx);
			वापस -ENOENT;
		पूर्ण

		rc = devm_request_irq(dev, irq, fatal_पूर्णांकerrupts[i], 0,
				      DRV_NAME " fatal", hisi_hba);
		अगर (rc) अणु
			dev_err(dev, "irq init: could not request fatal interrupt %d, rc=%d\n",
				irq, rc);
			वापस -ENOENT;
		पूर्ण
	पूर्ण

	hisi_hba->cq_nvecs = hisi_hba->queue_count;

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकerrupt_खोलोall_v1_hw(काष्ठा hisi_hba *hisi_hba)
अणु
	पूर्णांक i;
	u32 val;

	क्रम (i = 0; i < hisi_hba->n_phy; i++) अणु
		/* Clear पूर्णांकerrupt status */
		val = hisi_sas_phy_पढ़ो32(hisi_hba, i, CHL_INT0);
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, CHL_INT0, val);
		val = hisi_sas_phy_पढ़ो32(hisi_hba, i, CHL_INT1);
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, CHL_INT1, val);
		val = hisi_sas_phy_पढ़ो32(hisi_hba, i, CHL_INT2);
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, CHL_INT2, val);

		/* Unmask पूर्णांकerrupt */
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, CHL_INT0_MSK, 0x3ce3ee);
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, CHL_INT1_MSK, 0x17fff);
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, CHL_INT2_MSK, 0x8000012a);

		/* bypass chip bug mask abnormal पूर्णांकr */
		hisi_sas_phy_ग_लिखो32(hisi_hba, i, CHL_INT0_MSK,
				0x3fffff & ~CHL_INT0_MSK_PHYCTRL_NOTRDY_MSK);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hisi_sas_v1_init(काष्ठा hisi_hba *hisi_hba)
अणु
	पूर्णांक rc;

	rc = hw_init_v1_hw(hisi_hba);
	अगर (rc)
		वापस rc;

	rc = पूर्णांकerrupt_init_v1_hw(hisi_hba);
	अगर (rc)
		वापस rc;

	rc = पूर्णांकerrupt_खोलोall_v1_hw(hisi_hba);
	अगर (rc)
		वापस rc;

	वापस 0;
पूर्ण

अटल काष्ठा device_attribute *host_attrs_v1_hw[] = अणु
	&dev_attr_phy_event_threshold,
	शून्य
पूर्ण;

अटल काष्ठा scsi_host_ढाँचा sht_v1_hw = अणु
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
	.shost_attrs		= host_attrs_v1_hw,
	.host_reset             = hisi_sas_host_reset,
पूर्ण;

अटल स्थिर काष्ठा hisi_sas_hw hisi_sas_v1_hw = अणु
	.hw_init = hisi_sas_v1_init,
	.setup_itct = setup_itct_v1_hw,
	.sl_notअगरy_ssp = sl_notअगरy_ssp_v1_hw,
	.clear_itct = clear_itct_v1_hw,
	.prep_smp = prep_smp_v1_hw,
	.prep_ssp = prep_ssp_v1_hw,
	.start_delivery = start_delivery_v1_hw,
	.phys_init = phys_init_v1_hw,
	.phy_start = start_phy_v1_hw,
	.phy_disable = disable_phy_v1_hw,
	.phy_hard_reset = phy_hard_reset_v1_hw,
	.phy_set_linkrate = phy_set_linkrate_v1_hw,
	.phy_get_max_linkrate = phy_get_max_linkrate_v1_hw,
	.get_wideport_biपंचांगap = get_wideport_biपंचांगap_v1_hw,
	.complete_hdr_size = माप(काष्ठा hisi_sas_complete_v1_hdr),
	.sht = &sht_v1_hw,
पूर्ण;

अटल पूर्णांक hisi_sas_v1_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस hisi_sas_probe(pdev, &hisi_sas_v1_hw);
पूर्ण

अटल पूर्णांक hisi_sas_v1_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	वापस hisi_sas_हटाओ(pdev);
पूर्ण

अटल स्थिर काष्ठा of_device_id sas_v1_of_match[] = अणु
	अणु .compatible = "hisilicon,hip05-sas-v1",पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sas_v1_of_match);

अटल स्थिर काष्ठा acpi_device_id sas_v1_acpi_match[] = अणु
	अणु "HISI0161", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(acpi, sas_v1_acpi_match);

अटल काष्ठा platक्रमm_driver hisi_sas_v1_driver = अणु
	.probe = hisi_sas_v1_probe,
	.हटाओ = hisi_sas_v1_हटाओ,
	.driver = अणु
		.name = DRV_NAME,
		.of_match_table = sas_v1_of_match,
		.acpi_match_table = ACPI_PTR(sas_v1_acpi_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(hisi_sas_v1_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("John Garry <john.garry@huawei.com>");
MODULE_DESCRIPTION("HISILICON SAS controller v1 hw driver");
MODULE_ALIAS("platform:" DRV_NAME);
