<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/* Copyright (C) 2018 Microchip Technology Inc. */

#अगर_अघोषित _LAN743X_H
#घोषणा _LAN743X_H

#समावेश <linux/phy.h>
#समावेश "lan743x_ptp.h"

#घोषणा DRIVER_AUTHOR   "Bryan Whitehead <Bryan.Whitehead@microchip.com>"
#घोषणा DRIVER_DESC "LAN743x PCIe Gigabit Ethernet Driver"
#घोषणा DRIVER_NAME "lan743x"

/* Register Definitions */
#घोषणा ID_REV				(0x00)
#घोषणा ID_REV_ID_MASK_			(0xFFFF0000)
#घोषणा ID_REV_ID_LAN7430_		(0x74300000)
#घोषणा ID_REV_ID_LAN7431_		(0x74310000)
#घोषणा ID_REV_IS_VALID_CHIP_ID_(id_rev)	\
	(((id_rev) & 0xFFF00000) == 0x74300000)
#घोषणा ID_REV_CHIP_REV_MASK_		(0x0000FFFF)
#घोषणा ID_REV_CHIP_REV_A0_		(0x00000000)
#घोषणा ID_REV_CHIP_REV_B0_		(0x00000010)

#घोषणा FPGA_REV			(0x04)
#घोषणा FPGA_REV_GET_MINOR_(fpga_rev)	(((fpga_rev) >> 8) & 0x000000FF)
#घोषणा FPGA_REV_GET_MAJOR_(fpga_rev)	((fpga_rev) & 0x000000FF)

#घोषणा HW_CFG					(0x010)
#घोषणा HW_CFG_RELOAD_TYPE_ALL_			(0x00000FC0)
#घोषणा HW_CFG_EE_OTP_RELOAD_			BIT(4)
#घोषणा HW_CFG_LRST_				BIT(1)

#घोषणा PMT_CTL					(0x014)
#घोषणा PMT_CTL_ETH_PHY_D3_COLD_OVR_		BIT(27)
#घोषणा PMT_CTL_MAC_D3_RX_CLK_OVR_		BIT(25)
#घोषणा PMT_CTL_ETH_PHY_EDPD_PLL_CTL_		BIT(24)
#घोषणा PMT_CTL_ETH_PHY_D3_OVR_			BIT(23)
#घोषणा PMT_CTL_RX_FCT_RFE_D3_CLK_OVR_		BIT(18)
#घोषणा PMT_CTL_GPIO_WAKEUP_EN_			BIT(15)
#घोषणा PMT_CTL_EEE_WAKEUP_EN_			BIT(13)
#घोषणा PMT_CTL_READY_				BIT(7)
#घोषणा PMT_CTL_ETH_PHY_RST_			BIT(4)
#घोषणा PMT_CTL_WOL_EN_				BIT(3)
#घोषणा PMT_CTL_ETH_PHY_WAKE_EN_		BIT(2)
#घोषणा PMT_CTL_WUPS_MASK_			(0x00000003)

#घोषणा DP_SEL				(0x024)
#घोषणा DP_SEL_DPRDY_			BIT(31)
#घोषणा DP_SEL_MASK_			(0x0000001F)
#घोषणा DP_SEL_RFE_RAM			(0x00000001)

#घोषणा DP_SEL_VHF_HASH_LEN		(16)
#घोषणा DP_SEL_VHF_VLAN_LEN		(128)

#घोषणा DP_CMD				(0x028)
#घोषणा DP_CMD_WRITE_			(0x00000001)

#घोषणा DP_ADDR				(0x02C)

#घोषणा DP_DATA_0			(0x030)

#घोषणा E2P_CMD				(0x040)
#घोषणा E2P_CMD_EPC_BUSY_		BIT(31)
#घोषणा E2P_CMD_EPC_CMD_WRITE_		(0x30000000)
#घोषणा E2P_CMD_EPC_CMD_EWEN_		(0x20000000)
#घोषणा E2P_CMD_EPC_CMD_READ_		(0x00000000)
#घोषणा E2P_CMD_EPC_TIMEOUT_		BIT(10)
#घोषणा E2P_CMD_EPC_ADDR_MASK_		(0x000001FF)

#घोषणा E2P_DATA			(0x044)

#घोषणा GPIO_CFG0			(0x050)
#घोषणा GPIO_CFG0_GPIO_सूची_BIT_(bit)	BIT(16 + (bit))
#घोषणा GPIO_CFG0_GPIO_DATA_BIT_(bit)	BIT(0 + (bit))

#घोषणा GPIO_CFG1			(0x054)
#घोषणा GPIO_CFG1_GPIOEN_BIT_(bit)	BIT(16 + (bit))
#घोषणा GPIO_CFG1_GPIOBUF_BIT_(bit)	BIT(0 + (bit))

#घोषणा GPIO_CFG2			(0x058)
#घोषणा GPIO_CFG2_1588_POL_BIT_(bit)	BIT(0 + (bit))

#घोषणा GPIO_CFG3			(0x05C)
#घोषणा GPIO_CFG3_1588_CH_SEL_BIT_(bit)	BIT(16 + (bit))
#घोषणा GPIO_CFG3_1588_OE_BIT_(bit)	BIT(0 + (bit))

#घोषणा FCT_RX_CTL			(0xAC)
#घोषणा FCT_RX_CTL_EN_(channel)		BIT(28 + (channel))
#घोषणा FCT_RX_CTL_DIS_(channel)	BIT(24 + (channel))
#घोषणा FCT_RX_CTL_RESET_(channel)	BIT(20 + (channel))

#घोषणा FCT_TX_CTL			(0xC4)
#घोषणा FCT_TX_CTL_EN_(channel)		BIT(28 + (channel))
#घोषणा FCT_TX_CTL_DIS_(channel)	BIT(24 + (channel))
#घोषणा FCT_TX_CTL_RESET_(channel)	BIT(20 + (channel))

#घोषणा FCT_FLOW(rx_channel)			(0xE0 + ((rx_channel) << 2))
#घोषणा FCT_FLOW_CTL_OFF_THRESHOLD_		(0x00007F00)
#घोषणा FCT_FLOW_CTL_OFF_THRESHOLD_SET_(value)	\
	((value << 8) & FCT_FLOW_CTL_OFF_THRESHOLD_)
#घोषणा FCT_FLOW_CTL_REQ_EN_			BIT(7)
#घोषणा FCT_FLOW_CTL_ON_THRESHOLD_		(0x0000007F)
#घोषणा FCT_FLOW_CTL_ON_THRESHOLD_SET_(value)	\
	((value << 0) & FCT_FLOW_CTL_ON_THRESHOLD_)

#घोषणा MAC_CR				(0x100)
#घोषणा MAC_CR_MII_EN_			BIT(19)
#घोषणा MAC_CR_EEE_EN_			BIT(17)
#घोषणा MAC_CR_ADD_			BIT(12)
#घोषणा MAC_CR_ASD_			BIT(11)
#घोषणा MAC_CR_CNTR_RST_		BIT(5)
#घोषणा MAC_CR_DPX_			BIT(3)
#घोषणा MAC_CR_CFG_H_			BIT(2)
#घोषणा MAC_CR_CFG_L_			BIT(1)
#घोषणा MAC_CR_RST_			BIT(0)

#घोषणा MAC_RX				(0x104)
#घोषणा MAC_RX_MAX_SIZE_SHIFT_		(16)
#घोषणा MAC_RX_MAX_SIZE_MASK_		(0x3FFF0000)
#घोषणा MAC_RX_RXD_			BIT(1)
#घोषणा MAC_RX_RXEN_			BIT(0)

#घोषणा MAC_TX				(0x108)
#घोषणा MAC_TX_TXD_			BIT(1)
#घोषणा MAC_TX_TXEN_			BIT(0)

#घोषणा MAC_FLOW			(0x10C)
#घोषणा MAC_FLOW_CR_TX_FCEN_		BIT(30)
#घोषणा MAC_FLOW_CR_RX_FCEN_		BIT(29)
#घोषणा MAC_FLOW_CR_FCPT_MASK_		(0x0000FFFF)

#घोषणा MAC_RX_ADDRH			(0x118)

#घोषणा MAC_RX_ADDRL			(0x11C)

#घोषणा MAC_MII_ACC			(0x120)
#घोषणा MAC_MII_ACC_PHY_ADDR_SHIFT_	(11)
#घोषणा MAC_MII_ACC_PHY_ADDR_MASK_	(0x0000F800)
#घोषणा MAC_MII_ACC_MIIRINDA_SHIFT_	(6)
#घोषणा MAC_MII_ACC_MIIRINDA_MASK_	(0x000007C0)
#घोषणा MAC_MII_ACC_MII_READ_		(0x00000000)
#घोषणा MAC_MII_ACC_MII_WRITE_		(0x00000002)
#घोषणा MAC_MII_ACC_MII_BUSY_		BIT(0)

#घोषणा MAC_MII_DATA			(0x124)

#घोषणा MAC_EEE_TX_LPI_REQ_DLY_CNT		(0x130)

#घोषणा MAC_WUCSR				(0x140)
#घोषणा MAC_WUCSR_RFE_WAKE_EN_			BIT(14)
#घोषणा MAC_WUCSR_PFDA_EN_			BIT(3)
#घोषणा MAC_WUCSR_WAKE_EN_			BIT(2)
#घोषणा MAC_WUCSR_MPEN_				BIT(1)
#घोषणा MAC_WUCSR_BCST_EN_			BIT(0)

#घोषणा MAC_WK_SRC				(0x144)

#घोषणा MAC_WUF_CFG0			(0x150)
#घोषणा MAC_NUM_OF_WUF_CFG		(32)
#घोषणा MAC_WUF_CFG_BEGIN		(MAC_WUF_CFG0)
#घोषणा MAC_WUF_CFG(index)		(MAC_WUF_CFG_BEGIN + (4 * (index)))
#घोषणा MAC_WUF_CFG_EN_			BIT(31)
#घोषणा MAC_WUF_CFG_TYPE_MCAST_		(0x02000000)
#घोषणा MAC_WUF_CFG_TYPE_ALL_		(0x01000000)
#घोषणा MAC_WUF_CFG_OFFSET_SHIFT_	(16)
#घोषणा MAC_WUF_CFG_CRC16_MASK_		(0x0000FFFF)

#घोषणा MAC_WUF_MASK0_0			(0x200)
#घोषणा MAC_WUF_MASK0_1			(0x204)
#घोषणा MAC_WUF_MASK0_2			(0x208)
#घोषणा MAC_WUF_MASK0_3			(0x20C)
#घोषणा MAC_WUF_MASK0_BEGIN		(MAC_WUF_MASK0_0)
#घोषणा MAC_WUF_MASK1_BEGIN		(MAC_WUF_MASK0_1)
#घोषणा MAC_WUF_MASK2_BEGIN		(MAC_WUF_MASK0_2)
#घोषणा MAC_WUF_MASK3_BEGIN		(MAC_WUF_MASK0_3)
#घोषणा MAC_WUF_MASK0(index)		(MAC_WUF_MASK0_BEGIN + (0x10 * (index)))
#घोषणा MAC_WUF_MASK1(index)		(MAC_WUF_MASK1_BEGIN + (0x10 * (index)))
#घोषणा MAC_WUF_MASK2(index)		(MAC_WUF_MASK2_BEGIN + (0x10 * (index)))
#घोषणा MAC_WUF_MASK3(index)		(MAC_WUF_MASK3_BEGIN + (0x10 * (index)))

/* offset 0x400 - 0x500, x may range from 0 to 32, क्रम a total of 33 entries */
#घोषणा RFE_ADDR_FILT_HI(x)		(0x400 + (8 * (x)))
#घोषणा RFE_ADDR_FILT_HI_VALID_		BIT(31)

/* offset 0x404 - 0x504, x may range from 0 to 32, क्रम a total of 33 entries */
#घोषणा RFE_ADDR_FILT_LO(x)		(0x404 + (8 * (x)))

#घोषणा RFE_CTL				(0x508)
#घोषणा RFE_CTL_AB_			BIT(10)
#घोषणा RFE_CTL_AM_			BIT(9)
#घोषणा RFE_CTL_AU_			BIT(8)
#घोषणा RFE_CTL_MCAST_HASH_		BIT(3)
#घोषणा RFE_CTL_DA_PERFECT_		BIT(1)

#घोषणा RFE_RSS_CFG			(0x554)
#घोषणा RFE_RSS_CFG_UDP_IPV6_EX_	BIT(16)
#घोषणा RFE_RSS_CFG_TCP_IPV6_EX_	BIT(15)
#घोषणा RFE_RSS_CFG_IPV6_EX_		BIT(14)
#घोषणा RFE_RSS_CFG_UDP_IPV6_		BIT(13)
#घोषणा RFE_RSS_CFG_TCP_IPV6_		BIT(12)
#घोषणा RFE_RSS_CFG_IPV6_		BIT(11)
#घोषणा RFE_RSS_CFG_UDP_IPV4_		BIT(10)
#घोषणा RFE_RSS_CFG_TCP_IPV4_		BIT(9)
#घोषणा RFE_RSS_CFG_IPV4_		BIT(8)
#घोषणा RFE_RSS_CFG_VALID_HASH_BITS_	(0x000000E0)
#घोषणा RFE_RSS_CFG_RSS_QUEUE_ENABLE_	BIT(2)
#घोषणा RFE_RSS_CFG_RSS_HASH_STORE_	BIT(1)
#घोषणा RFE_RSS_CFG_RSS_ENABLE_		BIT(0)

#घोषणा RFE_HASH_KEY(index)		(0x558 + (index << 2))

#घोषणा RFE_INDX(index)			(0x580 + (index << 2))

#घोषणा MAC_WUCSR2			(0x600)

#घोषणा INT_STS				(0x780)
#घोषणा INT_BIT_DMA_RX_(channel)	BIT(24 + (channel))
#घोषणा INT_BIT_ALL_RX_			(0x0F000000)
#घोषणा INT_BIT_DMA_TX_(channel)	BIT(16 + (channel))
#घोषणा INT_BIT_ALL_TX_			(0x000F0000)
#घोषणा INT_BIT_SW_GP_			BIT(9)
#घोषणा INT_BIT_1588_			BIT(7)
#घोषणा INT_BIT_ALL_OTHER_		(INT_BIT_SW_GP_ | INT_BIT_1588_)
#घोषणा INT_BIT_MAS_			BIT(0)

#घोषणा INT_SET				(0x784)

#घोषणा INT_EN_SET			(0x788)

#घोषणा INT_EN_CLR			(0x78C)

#घोषणा INT_STS_R2C			(0x790)

#घोषणा INT_VEC_EN_SET			(0x794)
#घोषणा INT_VEC_EN_CLR			(0x798)
#घोषणा INT_VEC_EN_AUTO_CLR		(0x79C)
#घोषणा INT_VEC_EN_(vector_index)	BIT(0 + vector_index)

#घोषणा INT_VEC_MAP0			(0x7A0)
#घोषणा INT_VEC_MAP0_RX_VEC_(channel, vector)	\
	(((u32)(vector)) << ((channel) << 2))

#घोषणा INT_VEC_MAP1			(0x7A4)
#घोषणा INT_VEC_MAP1_TX_VEC_(channel, vector)	\
	(((u32)(vector)) << ((channel) << 2))

#घोषणा INT_VEC_MAP2			(0x7A8)

#घोषणा INT_MOD_MAP0			(0x7B0)

#घोषणा INT_MOD_MAP1			(0x7B4)

#घोषणा INT_MOD_MAP2			(0x7B8)

#घोषणा INT_MOD_CFG0			(0x7C0)
#घोषणा INT_MOD_CFG1			(0x7C4)
#घोषणा INT_MOD_CFG2			(0x7C8)
#घोषणा INT_MOD_CFG3			(0x7CC)
#घोषणा INT_MOD_CFG4			(0x7D0)
#घोषणा INT_MOD_CFG5			(0x7D4)
#घोषणा INT_MOD_CFG6			(0x7D8)
#घोषणा INT_MOD_CFG7			(0x7DC)

#घोषणा PTP_CMD_CTL					(0x0A00)
#घोषणा PTP_CMD_CTL_PTP_CLK_STP_NSEC_			BIT(6)
#घोषणा PTP_CMD_CTL_PTP_CLOCK_STEP_SEC_			BIT(5)
#घोषणा PTP_CMD_CTL_PTP_CLOCK_LOAD_			BIT(4)
#घोषणा PTP_CMD_CTL_PTP_CLOCK_READ_			BIT(3)
#घोषणा PTP_CMD_CTL_PTP_ENABLE_				BIT(2)
#घोषणा PTP_CMD_CTL_PTP_DISABLE_			BIT(1)
#घोषणा PTP_CMD_CTL_PTP_RESET_				BIT(0)
#घोषणा PTP_GENERAL_CONFIG				(0x0A04)
#घोषणा PTP_GENERAL_CONFIG_CLOCK_EVENT_X_MASK_(channel) \
	(0x7 << (1 + ((channel) << 2)))
#घोषणा PTP_GENERAL_CONFIG_CLOCK_EVENT_100NS_	(0)
#घोषणा PTP_GENERAL_CONFIG_CLOCK_EVENT_10US_	(1)
#घोषणा PTP_GENERAL_CONFIG_CLOCK_EVENT_100US_	(2)
#घोषणा PTP_GENERAL_CONFIG_CLOCK_EVENT_1MS_	(3)
#घोषणा PTP_GENERAL_CONFIG_CLOCK_EVENT_10MS_	(4)
#घोषणा PTP_GENERAL_CONFIG_CLOCK_EVENT_200MS_	(5)
#घोषणा PTP_GENERAL_CONFIG_CLOCK_EVENT_X_SET_(channel, value) \
	(((value) & 0x7) << (1 + ((channel) << 2)))
#घोषणा PTP_GENERAL_CONFIG_RELOAD_ADD_X_(channel)	(BIT((channel) << 2))

#घोषणा PTP_INT_STS				(0x0A08)
#घोषणा PTP_INT_EN_SET				(0x0A0C)
#घोषणा PTP_INT_EN_CLR				(0x0A10)
#घोषणा PTP_INT_BIT_TX_SWTS_ERR_		BIT(13)
#घोषणा PTP_INT_BIT_TX_TS_			BIT(12)
#घोषणा PTP_INT_BIT_TIMER_B_			BIT(1)
#घोषणा PTP_INT_BIT_TIMER_A_			BIT(0)

#घोषणा PTP_CLOCK_SEC				(0x0A14)
#घोषणा PTP_CLOCK_NS				(0x0A18)
#घोषणा PTP_CLOCK_SUBNS				(0x0A1C)
#घोषणा PTP_CLOCK_RATE_ADJ			(0x0A20)
#घोषणा PTP_CLOCK_RATE_ADJ_सूची_			BIT(31)
#घोषणा PTP_CLOCK_STEP_ADJ			(0x0A2C)
#घोषणा PTP_CLOCK_STEP_ADJ_सूची_			BIT(31)
#घोषणा PTP_CLOCK_STEP_ADJ_VALUE_MASK_		(0x3FFFFFFF)
#घोषणा PTP_CLOCK_TARGET_SEC_X(channel)		(0x0A30 + ((channel) << 4))
#घोषणा PTP_CLOCK_TARGET_NS_X(channel)		(0x0A34 + ((channel) << 4))
#घोषणा PTP_CLOCK_TARGET_RELOAD_SEC_X(channel)	(0x0A38 + ((channel) << 4))
#घोषणा PTP_CLOCK_TARGET_RELOAD_NS_X(channel)	(0x0A3C + ((channel) << 4))
#घोषणा PTP_LATENCY				(0x0A5C)
#घोषणा PTP_LATENCY_TX_SET_(tx_latency)		(((u32)(tx_latency)) << 16)
#घोषणा PTP_LATENCY_RX_SET_(rx_latency)		\
	(((u32)(rx_latency)) & 0x0000FFFF)
#घोषणा PTP_CAP_INFO				(0x0A60)
#घोषणा PTP_CAP_INFO_TX_TS_CNT_GET_(reg_val)	(((reg_val) & 0x00000070) >> 4)

#घोषणा PTP_TX_MOD				(0x0AA4)
#घोषणा PTP_TX_MOD_TX_PTP_SYNC_TS_INSERT_	(0x10000000)

#घोषणा PTP_TX_MOD2				(0x0AA8)
#घोषणा PTP_TX_MOD2_TX_PTP_CLR_UDPV4_CHKSUM_	(0x00000001)

#घोषणा PTP_TX_EGRESS_SEC			(0x0AAC)
#घोषणा PTP_TX_EGRESS_NS			(0x0AB0)
#घोषणा PTP_TX_EGRESS_NS_CAPTURE_CAUSE_MASK_	(0xC0000000)
#घोषणा PTP_TX_EGRESS_NS_CAPTURE_CAUSE_AUTO_	(0x00000000)
#घोषणा PTP_TX_EGRESS_NS_CAPTURE_CAUSE_SW_	(0x40000000)
#घोषणा PTP_TX_EGRESS_NS_TS_NS_MASK_		(0x3FFFFFFF)

#घोषणा PTP_TX_MSG_HEADER			(0x0AB4)
#घोषणा PTP_TX_MSG_HEADER_MSG_TYPE_		(0x000F0000)
#घोषणा PTP_TX_MSG_HEADER_MSG_TYPE_SYNC_	(0x00000000)

#घोषणा DMAC_CFG				(0xC00)
#घोषणा DMAC_CFG_COAL_EN_			BIT(16)
#घोषणा DMAC_CFG_CH_ARB_SEL_RX_HIGH_		(0x00000000)
#घोषणा DMAC_CFG_MAX_READ_REQ_MASK_		(0x00000070)
#घोषणा DMAC_CFG_MAX_READ_REQ_SET_(val)	\
	((((u32)(val)) << 4) & DMAC_CFG_MAX_READ_REQ_MASK_)
#घोषणा DMAC_CFG_MAX_DSPACE_16_			(0x00000000)
#घोषणा DMAC_CFG_MAX_DSPACE_32_			(0x00000001)
#घोषणा DMAC_CFG_MAX_DSPACE_64_			BIT(1)
#घोषणा DMAC_CFG_MAX_DSPACE_128_		(0x00000003)

#घोषणा DMAC_COAL_CFG				(0xC04)
#घोषणा DMAC_COAL_CFG_TIMER_LIMIT_MASK_		(0xFFF00000)
#घोषणा DMAC_COAL_CFG_TIMER_LIMIT_SET_(val)	\
	((((u32)(val)) << 20) & DMAC_COAL_CFG_TIMER_LIMIT_MASK_)
#घोषणा DMAC_COAL_CFG_TIMER_TX_START_		BIT(19)
#घोषणा DMAC_COAL_CFG_FLUSH_INTS_		BIT(18)
#घोषणा DMAC_COAL_CFG_INT_EXIT_COAL_		BIT(17)
#घोषणा DMAC_COAL_CFG_CSR_EXIT_COAL_		BIT(16)
#घोषणा DMAC_COAL_CFG_TX_THRES_MASK_		(0x0000FF00)
#घोषणा DMAC_COAL_CFG_TX_THRES_SET_(val)	\
	((((u32)(val)) << 8) & DMAC_COAL_CFG_TX_THRES_MASK_)
#घोषणा DMAC_COAL_CFG_RX_THRES_MASK_		(0x000000FF)
#घोषणा DMAC_COAL_CFG_RX_THRES_SET_(val)	\
	(((u32)(val)) & DMAC_COAL_CFG_RX_THRES_MASK_)

#घोषणा DMAC_OBFF_CFG				(0xC08)
#घोषणा DMAC_OBFF_TX_THRES_MASK_		(0x0000FF00)
#घोषणा DMAC_OBFF_TX_THRES_SET_(val)	\
	((((u32)(val)) << 8) & DMAC_OBFF_TX_THRES_MASK_)
#घोषणा DMAC_OBFF_RX_THRES_MASK_		(0x000000FF)
#घोषणा DMAC_OBFF_RX_THRES_SET_(val)	\
	(((u32)(val)) & DMAC_OBFF_RX_THRES_MASK_)

#घोषणा DMAC_CMD				(0xC0C)
#घोषणा DMAC_CMD_SWR_				BIT(31)
#घोषणा DMAC_CMD_TX_SWR_(channel)		BIT(24 + (channel))
#घोषणा DMAC_CMD_START_T_(channel)		BIT(20 + (channel))
#घोषणा DMAC_CMD_STOP_T_(channel)		BIT(16 + (channel))
#घोषणा DMAC_CMD_RX_SWR_(channel)		BIT(8 + (channel))
#घोषणा DMAC_CMD_START_R_(channel)		BIT(4 + (channel))
#घोषणा DMAC_CMD_STOP_R_(channel)		BIT(0 + (channel))

#घोषणा DMAC_INT_STS				(0xC10)
#घोषणा DMAC_INT_EN_SET				(0xC14)
#घोषणा DMAC_INT_EN_CLR				(0xC18)
#घोषणा DMAC_INT_BIT_RXFRM_(channel)		BIT(16 + (channel))
#घोषणा DMAC_INT_BIT_TX_IOC_(channel)		BIT(0 + (channel))

#घोषणा RX_CFG_A(channel)			(0xC40 + ((channel) << 6))
#घोषणा RX_CFG_A_RX_WB_ON_INT_TMR_		BIT(30)
#घोषणा RX_CFG_A_RX_WB_THRES_MASK_		(0x1F000000)
#घोषणा RX_CFG_A_RX_WB_THRES_SET_(val)	\
	((((u32)(val)) << 24) & RX_CFG_A_RX_WB_THRES_MASK_)
#घोषणा RX_CFG_A_RX_PF_THRES_MASK_		(0x001F0000)
#घोषणा RX_CFG_A_RX_PF_THRES_SET_(val)	\
	((((u32)(val)) << 16) & RX_CFG_A_RX_PF_THRES_MASK_)
#घोषणा RX_CFG_A_RX_PF_PRI_THRES_MASK_		(0x00001F00)
#घोषणा RX_CFG_A_RX_PF_PRI_THRES_SET_(val)	\
	((((u32)(val)) << 8) & RX_CFG_A_RX_PF_PRI_THRES_MASK_)
#घोषणा RX_CFG_A_RX_HP_WB_EN_			BIT(5)

#घोषणा RX_CFG_B(channel)			(0xC44 + ((channel) << 6))
#घोषणा RX_CFG_B_TS_ALL_RX_			BIT(29)
#घोषणा RX_CFG_B_RX_PAD_MASK_			(0x03000000)
#घोषणा RX_CFG_B_RX_PAD_0_			(0x00000000)
#घोषणा RX_CFG_B_RX_PAD_2_			(0x02000000)
#घोषणा RX_CFG_B_RDMABL_512_			(0x00040000)
#घोषणा RX_CFG_B_RX_RING_LEN_MASK_		(0x0000FFFF)

#घोषणा RX_BASE_ADDRH(channel)			(0xC48 + ((channel) << 6))

#घोषणा RX_BASE_ADDRL(channel)			(0xC4C + ((channel) << 6))

#घोषणा RX_HEAD_WRITEBACK_ADDRH(channel)	(0xC50 + ((channel) << 6))

#घोषणा RX_HEAD_WRITEBACK_ADDRL(channel)	(0xC54 + ((channel) << 6))

#घोषणा RX_HEAD(channel)			(0xC58 + ((channel) << 6))

#घोषणा RX_TAIL(channel)			(0xC5C + ((channel) << 6))
#घोषणा RX_TAIL_SET_TOP_INT_EN_			BIT(30)
#घोषणा RX_TAIL_SET_TOP_INT_VEC_EN_		BIT(29)

#घोषणा RX_CFG_C(channel)			(0xC64 + ((channel) << 6))
#घोषणा RX_CFG_C_RX_TOP_INT_EN_AUTO_CLR_	BIT(6)
#घोषणा RX_CFG_C_RX_INT_EN_R2C_			BIT(4)
#घोषणा RX_CFG_C_RX_DMA_INT_STS_AUTO_CLR_	BIT(3)
#घोषणा RX_CFG_C_RX_INT_STS_R2C_MODE_MASK_	(0x00000007)

#घोषणा TX_CFG_A(channel)			(0xD40 + ((channel) << 6))
#घोषणा TX_CFG_A_TX_HP_WB_ON_INT_TMR_		BIT(30)
#घोषणा TX_CFG_A_TX_TMR_HPWB_SEL_IOC_		(0x10000000)
#घोषणा TX_CFG_A_TX_PF_THRES_MASK_		(0x001F0000)
#घोषणा TX_CFG_A_TX_PF_THRES_SET_(value)	\
	((((u32)(value)) << 16) & TX_CFG_A_TX_PF_THRES_MASK_)
#घोषणा TX_CFG_A_TX_PF_PRI_THRES_MASK_		(0x00001F00)
#घोषणा TX_CFG_A_TX_PF_PRI_THRES_SET_(value)	\
	((((u32)(value)) << 8) & TX_CFG_A_TX_PF_PRI_THRES_MASK_)
#घोषणा TX_CFG_A_TX_HP_WB_EN_			BIT(5)
#घोषणा TX_CFG_A_TX_HP_WB_THRES_MASK_		(0x0000000F)
#घोषणा TX_CFG_A_TX_HP_WB_THRES_SET_(value)	\
	(((u32)(value)) & TX_CFG_A_TX_HP_WB_THRES_MASK_)

#घोषणा TX_CFG_B(channel)			(0xD44 + ((channel) << 6))
#घोषणा TX_CFG_B_TDMABL_512_			(0x00040000)
#घोषणा TX_CFG_B_TX_RING_LEN_MASK_		(0x0000FFFF)

#घोषणा TX_BASE_ADDRH(channel)			(0xD48 + ((channel) << 6))

#घोषणा TX_BASE_ADDRL(channel)			(0xD4C + ((channel) << 6))

#घोषणा TX_HEAD_WRITEBACK_ADDRH(channel)	(0xD50 + ((channel) << 6))

#घोषणा TX_HEAD_WRITEBACK_ADDRL(channel)	(0xD54 + ((channel) << 6))

#घोषणा TX_HEAD(channel)			(0xD58 + ((channel) << 6))

#घोषणा TX_TAIL(channel)			(0xD5C + ((channel) << 6))
#घोषणा TX_TAIL_SET_DMAC_INT_EN_		BIT(31)
#घोषणा TX_TAIL_SET_TOP_INT_EN_			BIT(30)
#घोषणा TX_TAIL_SET_TOP_INT_VEC_EN_		BIT(29)

#घोषणा TX_CFG_C(channel)			(0xD64 + ((channel) << 6))
#घोषणा TX_CFG_C_TX_TOP_INT_EN_AUTO_CLR_	BIT(6)
#घोषणा TX_CFG_C_TX_DMA_INT_EN_AUTO_CLR_	BIT(5)
#घोषणा TX_CFG_C_TX_INT_EN_R2C_			BIT(4)
#घोषणा TX_CFG_C_TX_DMA_INT_STS_AUTO_CLR_	BIT(3)
#घोषणा TX_CFG_C_TX_INT_STS_R2C_MODE_MASK_	(0x00000007)

#घोषणा OTP_PWR_DN				(0x1000)
#घोषणा OTP_PWR_DN_PWRDN_N_			BIT(0)

#घोषणा OTP_ADDR_HIGH				(0x1004)
#घोषणा OTP_ADDR_LOW				(0x1008)

#घोषणा OTP_PRGM_DATA				(0x1010)

#घोषणा OTP_PRGM_MODE				(0x1014)
#घोषणा OTP_PRGM_MODE_BYTE_			BIT(0)

#घोषणा OTP_READ_DATA				(0x1018)

#घोषणा OTP_FUNC_CMD				(0x1020)
#घोषणा OTP_FUNC_CMD_READ_			BIT(0)

#घोषणा OTP_TST_CMD				(0x1024)
#घोषणा OTP_TST_CMD_PRGVRFY_			BIT(3)

#घोषणा OTP_CMD_GO				(0x1028)
#घोषणा OTP_CMD_GO_GO_				BIT(0)

#घोषणा OTP_STATUS				(0x1030)
#घोषणा OTP_STATUS_BUSY_			BIT(0)

/* MAC statistics रेजिस्टरs */
#घोषणा STAT_RX_FCS_ERRORS			(0x1200)
#घोषणा STAT_RX_ALIGNMENT_ERRORS		(0x1204)
#घोषणा STAT_RX_FRAGMENT_ERRORS			(0x1208)
#घोषणा STAT_RX_JABBER_ERRORS			(0x120C)
#घोषणा STAT_RX_UNDERSIZE_FRAME_ERRORS		(0x1210)
#घोषणा STAT_RX_OVERSIZE_FRAME_ERRORS		(0x1214)
#घोषणा STAT_RX_DROPPED_FRAMES			(0x1218)
#घोषणा STAT_RX_UNICAST_BYTE_COUNT		(0x121C)
#घोषणा STAT_RX_BROADCAST_BYTE_COUNT		(0x1220)
#घोषणा STAT_RX_MULTICAST_BYTE_COUNT		(0x1224)
#घोषणा STAT_RX_UNICAST_FRAMES			(0x1228)
#घोषणा STAT_RX_BROADCAST_FRAMES		(0x122C)
#घोषणा STAT_RX_MULTICAST_FRAMES		(0x1230)
#घोषणा STAT_RX_PAUSE_FRAMES			(0x1234)
#घोषणा STAT_RX_64_BYTE_FRAMES			(0x1238)
#घोषणा STAT_RX_65_127_BYTE_FRAMES		(0x123C)
#घोषणा STAT_RX_128_255_BYTE_FRAMES		(0x1240)
#घोषणा STAT_RX_256_511_BYTES_FRAMES		(0x1244)
#घोषणा STAT_RX_512_1023_BYTE_FRAMES		(0x1248)
#घोषणा STAT_RX_1024_1518_BYTE_FRAMES		(0x124C)
#घोषणा STAT_RX_GREATER_1518_BYTE_FRAMES	(0x1250)
#घोषणा STAT_RX_TOTAL_FRAMES			(0x1254)
#घोषणा STAT_EEE_RX_LPI_TRANSITIONS		(0x1258)
#घोषणा STAT_EEE_RX_LPI_TIME			(0x125C)
#घोषणा STAT_RX_COUNTER_ROLLOVER_STATUS		(0x127C)

#घोषणा STAT_TX_FCS_ERRORS			(0x1280)
#घोषणा STAT_TX_EXCESS_DEFERRAL_ERRORS		(0x1284)
#घोषणा STAT_TX_CARRIER_ERRORS			(0x1288)
#घोषणा STAT_TX_BAD_BYTE_COUNT			(0x128C)
#घोषणा STAT_TX_SINGLE_COLLISIONS		(0x1290)
#घोषणा STAT_TX_MULTIPLE_COLLISIONS		(0x1294)
#घोषणा STAT_TX_EXCESSIVE_COLLISION		(0x1298)
#घोषणा STAT_TX_LATE_COLLISIONS			(0x129C)
#घोषणा STAT_TX_UNICAST_BYTE_COUNT		(0x12A0)
#घोषणा STAT_TX_BROADCAST_BYTE_COUNT		(0x12A4)
#घोषणा STAT_TX_MULTICAST_BYTE_COUNT		(0x12A8)
#घोषणा STAT_TX_UNICAST_FRAMES			(0x12AC)
#घोषणा STAT_TX_BROADCAST_FRAMES		(0x12B0)
#घोषणा STAT_TX_MULTICAST_FRAMES		(0x12B4)
#घोषणा STAT_TX_PAUSE_FRAMES			(0x12B8)
#घोषणा STAT_TX_64_BYTE_FRAMES			(0x12BC)
#घोषणा STAT_TX_65_127_BYTE_FRAMES		(0x12C0)
#घोषणा STAT_TX_128_255_BYTE_FRAMES		(0x12C4)
#घोषणा STAT_TX_256_511_BYTES_FRAMES		(0x12C8)
#घोषणा STAT_TX_512_1023_BYTE_FRAMES		(0x12CC)
#घोषणा STAT_TX_1024_1518_BYTE_FRAMES		(0x12D0)
#घोषणा STAT_TX_GREATER_1518_BYTE_FRAMES	(0x12D4)
#घोषणा STAT_TX_TOTAL_FRAMES			(0x12D8)
#घोषणा STAT_EEE_TX_LPI_TRANSITIONS		(0x12DC)
#घोषणा STAT_EEE_TX_LPI_TIME			(0x12E0)
#घोषणा STAT_TX_COUNTER_ROLLOVER_STATUS		(0x12FC)

/* End of Register definitions */

#घोषणा LAN743X_MAX_RX_CHANNELS		(4)
#घोषणा LAN743X_MAX_TX_CHANNELS		(1)
काष्ठा lan743x_adapter;

#घोषणा LAN743X_USED_RX_CHANNELS	(4)
#घोषणा LAN743X_USED_TX_CHANNELS	(1)
#घोषणा LAN743X_INT_MOD	(400)

#अगर (LAN743X_USED_RX_CHANNELS > LAN743X_MAX_RX_CHANNELS)
#त्रुटि Invalid LAN743X_USED_RX_CHANNELS
#पूर्ण_अगर
#अगर (LAN743X_USED_TX_CHANNELS > LAN743X_MAX_TX_CHANNELS)
#त्रुटि Invalid LAN743X_USED_TX_CHANNELS
#पूर्ण_अगर

/* PCI */
/* SMSC acquired EFAR late 1990's, MCHP acquired SMSC 2012 */
#घोषणा PCI_VENDOR_ID_SMSC		PCI_VENDOR_ID_EFAR
#घोषणा PCI_DEVICE_ID_SMSC_LAN7430	(0x7430)
#घोषणा PCI_DEVICE_ID_SMSC_LAN7431	(0x7431)

#घोषणा PCI_CONFIG_LENGTH		(0x1000)

/* CSR */
#घोषणा CSR_LENGTH					(0x2000)

#घोषणा LAN743X_CSR_FLAG_IS_A0				BIT(0)
#घोषणा LAN743X_CSR_FLAG_IS_B0				BIT(1)
#घोषणा LAN743X_CSR_FLAG_SUPPORTS_INTR_AUTO_SET_CLR	BIT(8)

काष्ठा lan743x_csr अणु
	u32 flags;
	u8 __iomem *csr_address;
	u32 id_rev;
	u32 fpga_rev;
पूर्ण;

/* INTERRUPTS */
प्रकार व्योम(*lan743x_vector_handler)(व्योम *context, u32 पूर्णांक_sts, u32 flags);

#घोषणा LAN743X_VECTOR_FLAG_IRQ_SHARED			BIT(0)
#घोषणा LAN743X_VECTOR_FLAG_SOURCE_STATUS_READ		BIT(1)
#घोषणा LAN743X_VECTOR_FLAG_SOURCE_STATUS_R2C		BIT(2)
#घोषणा LAN743X_VECTOR_FLAG_SOURCE_STATUS_W2C		BIT(3)
#घोषणा LAN743X_VECTOR_FLAG_SOURCE_ENABLE_CHECK		BIT(4)
#घोषणा LAN743X_VECTOR_FLAG_SOURCE_ENABLE_CLEAR		BIT(5)
#घोषणा LAN743X_VECTOR_FLAG_SOURCE_ENABLE_R2C		BIT(6)
#घोषणा LAN743X_VECTOR_FLAG_MASTER_ENABLE_CLEAR		BIT(7)
#घोषणा LAN743X_VECTOR_FLAG_MASTER_ENABLE_SET		BIT(8)
#घोषणा LAN743X_VECTOR_FLAG_VECTOR_ENABLE_ISR_CLEAR	BIT(9)
#घोषणा LAN743X_VECTOR_FLAG_VECTOR_ENABLE_ISR_SET	BIT(10)
#घोषणा LAN743X_VECTOR_FLAG_VECTOR_ENABLE_AUTO_CLEAR	BIT(11)
#घोषणा LAN743X_VECTOR_FLAG_VECTOR_ENABLE_AUTO_SET	BIT(12)
#घोषणा LAN743X_VECTOR_FLAG_SOURCE_ENABLE_AUTO_CLEAR	BIT(13)
#घोषणा LAN743X_VECTOR_FLAG_SOURCE_ENABLE_AUTO_SET	BIT(14)
#घोषणा LAN743X_VECTOR_FLAG_SOURCE_STATUS_AUTO_CLEAR	BIT(15)

काष्ठा lan743x_vector अणु
	पूर्णांक			irq;
	u32			flags;
	काष्ठा lan743x_adapter	*adapter;
	पूर्णांक			vector_index;
	u32			पूर्णांक_mask;
	lan743x_vector_handler	handler;
	व्योम			*context;
पूर्ण;

#घोषणा LAN743X_MAX_VECTOR_COUNT	(8)

काष्ठा lan743x_पूर्णांकr अणु
	पूर्णांक			flags;

	अचिन्हित पूर्णांक		irq;

	काष्ठा lan743x_vector	vector_list[LAN743X_MAX_VECTOR_COUNT];
	पूर्णांक			number_of_vectors;
	bool			using_vectors;

	bool			software_isr_flag;
	रुको_queue_head_t	software_isr_wq;
पूर्ण;

#घोषणा LAN743X_MAX_FRAME_SIZE			(9 * 1024)

/* PHY */
काष्ठा lan743x_phy अणु
	bool	fc_स्वतःneg;
	u8	fc_request_control;
पूर्ण;

/* TX */
काष्ठा lan743x_tx_descriptor;
काष्ठा lan743x_tx_buffer_info;

#घोषणा GPIO_QUEUE_STARTED		(0)
#घोषणा GPIO_TX_FUNCTION		(1)
#घोषणा GPIO_TX_COMPLETION		(2)
#घोषणा GPIO_TX_FRAGMENT		(3)

#घोषणा TX_FRAME_FLAG_IN_PROGRESS	BIT(0)

#घोषणा TX_TS_FLAG_TIMESTAMPING_ENABLED	BIT(0)
#घोषणा TX_TS_FLAG_ONE_STEP_SYNC	BIT(1)

काष्ठा lan743x_tx अणु
	काष्ठा lan743x_adapter *adapter;
	u32	ts_flags;
	u32	vector_flags;
	पूर्णांक	channel_number;

	पूर्णांक	ring_size;
	माप_प्रकार	ring_allocation_size;
	काष्ठा lan743x_tx_descriptor *ring_cpu_ptr;
	dma_addr_t ring_dma_ptr;
	/* ring_lock: used to prevent concurrent access to tx ring */
	spinlock_t ring_lock;
	u32		frame_flags;
	u32		frame_first;
	u32		frame_data0;
	u32		frame_tail;

	काष्ठा lan743x_tx_buffer_info *buffer_info;

	__le32		*head_cpu_ptr;
	dma_addr_t	head_dma_ptr;
	पूर्णांक		last_head;
	पूर्णांक		last_tail;

	काष्ठा napi_काष्ठा napi;

	काष्ठा sk_buff *overflow_skb;
पूर्ण;

व्योम lan743x_tx_set_बारtamping_mode(काष्ठा lan743x_tx *tx,
				      bool enable_बारtamping,
				      bool enable_onestep_sync);

/* RX */
काष्ठा lan743x_rx_descriptor;
काष्ठा lan743x_rx_buffer_info;

काष्ठा lan743x_rx अणु
	काष्ठा lan743x_adapter *adapter;
	u32	vector_flags;
	पूर्णांक	channel_number;

	पूर्णांक	ring_size;
	माप_प्रकार	ring_allocation_size;
	काष्ठा lan743x_rx_descriptor *ring_cpu_ptr;
	dma_addr_t ring_dma_ptr;

	काष्ठा lan743x_rx_buffer_info *buffer_info;

	__le32		*head_cpu_ptr;
	dma_addr_t	head_dma_ptr;
	u32		last_head;
	u32		last_tail;

	काष्ठा napi_काष्ठा napi;

	u32		frame_count;

	काष्ठा sk_buff *skb_head, *skb_tail;
पूर्ण;

काष्ठा lan743x_adapter अणु
	काष्ठा net_device       *netdev;
	काष्ठा mii_bus		*mdiobus;
	पूर्णांक                     msg_enable;
#अगर_घोषित CONFIG_PM
	u32			wolopts;
#पूर्ण_अगर
	काष्ठा pci_dev		*pdev;
	काष्ठा lan743x_csr      csr;
	काष्ठा lan743x_पूर्णांकr     पूर्णांकr;

	काष्ठा lan743x_gpio	gpio;
	काष्ठा lan743x_ptp	ptp;

	u8			mac_address[ETH_ALEN];

	काष्ठा lan743x_phy      phy;
	काष्ठा lan743x_tx       tx[LAN743X_MAX_TX_CHANNELS];
	काष्ठा lan743x_rx       rx[LAN743X_MAX_RX_CHANNELS];

#घोषणा LAN743X_ADAPTER_FLAG_OTP		BIT(0)
	u32			flags;
पूर्ण;

#घोषणा LAN743X_COMPONENT_FLAG_RX(channel)  BIT(20 + (channel))

#घोषणा INTR_FLAG_IRQ_REQUESTED(vector_index)	BIT(0 + vector_index)
#घोषणा INTR_FLAG_MSI_ENABLED			BIT(8)
#घोषणा INTR_FLAG_MSIX_ENABLED			BIT(9)

#घोषणा MAC_MII_READ            1
#घोषणा MAC_MII_WRITE           0

#घोषणा PHY_FLAG_OPENED     BIT(0)
#घोषणा PHY_FLAG_ATTACHED   BIT(1)

#अगर_घोषित CONFIG_ARCH_DMA_ADDR_T_64BIT
#घोषणा DMA_ADDR_HIGH32(dma_addr)   ((u32)(((dma_addr) >> 32) & 0xFFFFFFFF))
#अन्यथा
#घोषणा DMA_ADDR_HIGH32(dma_addr)   ((u32)(0))
#पूर्ण_अगर
#घोषणा DMA_ADDR_LOW32(dma_addr) ((u32)((dma_addr) & 0xFFFFFFFF))
#घोषणा DMA_DESCRIPTOR_SPACING_16       (16)
#घोषणा DMA_DESCRIPTOR_SPACING_32       (32)
#घोषणा DMA_DESCRIPTOR_SPACING_64       (64)
#घोषणा DMA_DESCRIPTOR_SPACING_128      (128)
#घोषणा DEFAULT_DMA_DESCRIPTOR_SPACING  (L1_CACHE_BYTES)

#घोषणा DMAC_CHANNEL_STATE_SET(start_bit, stop_bit) \
	(((start_bit) ? 2 : 0) | ((stop_bit) ? 1 : 0))
#घोषणा DMAC_CHANNEL_STATE_INITIAL      DMAC_CHANNEL_STATE_SET(0, 0)
#घोषणा DMAC_CHANNEL_STATE_STARTED      DMAC_CHANNEL_STATE_SET(1, 0)
#घोषणा DMAC_CHANNEL_STATE_STOP_PENDING DMAC_CHANNEL_STATE_SET(1, 1)
#घोषणा DMAC_CHANNEL_STATE_STOPPED      DMAC_CHANNEL_STATE_SET(0, 1)

/* TX Descriptor bits */
#घोषणा TX_DESC_DATA0_DTYPE_MASK_		(0xC0000000)
#घोषणा TX_DESC_DATA0_DTYPE_DATA_		(0x00000000)
#घोषणा TX_DESC_DATA0_DTYPE_EXT_		(0x40000000)
#घोषणा TX_DESC_DATA0_FS_			(0x20000000)
#घोषणा TX_DESC_DATA0_LS_			(0x10000000)
#घोषणा TX_DESC_DATA0_EXT_			(0x08000000)
#घोषणा TX_DESC_DATA0_IOC_			(0x04000000)
#घोषणा TX_DESC_DATA0_ICE_			(0x00400000)
#घोषणा TX_DESC_DATA0_IPE_			(0x00200000)
#घोषणा TX_DESC_DATA0_TPE_			(0x00100000)
#घोषणा TX_DESC_DATA0_FCS_			(0x00020000)
#घोषणा TX_DESC_DATA0_TSE_			(0x00010000)
#घोषणा TX_DESC_DATA0_BUF_LENGTH_MASK_		(0x0000FFFF)
#घोषणा TX_DESC_DATA0_EXT_LSO_			(0x00200000)
#घोषणा TX_DESC_DATA0_EXT_PAY_LENGTH_MASK_	(0x000FFFFF)
#घोषणा TX_DESC_DATA3_FRAME_LENGTH_MSS_MASK_	(0x3FFF0000)

काष्ठा lan743x_tx_descriptor अणु
	__le32     data0;
	__le32     data1;
	__le32     data2;
	__le32     data3;
पूर्ण __aligned(DEFAULT_DMA_DESCRIPTOR_SPACING);

#घोषणा TX_BUFFER_INFO_FLAG_ACTIVE		BIT(0)
#घोषणा TX_BUFFER_INFO_FLAG_TIMESTAMP_REQUESTED	BIT(1)
#घोषणा TX_BUFFER_INFO_FLAG_IGNORE_SYNC		BIT(2)
#घोषणा TX_BUFFER_INFO_FLAG_SKB_FRAGMENT	BIT(3)
काष्ठा lan743x_tx_buffer_info अणु
	पूर्णांक flags;
	काष्ठा sk_buff *skb;
	dma_addr_t      dma_ptr;
	अचिन्हित पूर्णांक    buffer_length;
पूर्ण;

#घोषणा LAN743X_TX_RING_SIZE    (50)

/* OWN bit is set. ie, Descs are owned by RX DMAC */
#घोषणा RX_DESC_DATA0_OWN_                (0x00008000)
/* OWN bit is clear. ie, Descs are owned by host */
#घोषणा RX_DESC_DATA0_FS_                 (0x80000000)
#घोषणा RX_DESC_DATA0_LS_                 (0x40000000)
#घोषणा RX_DESC_DATA0_FRAME_LENGTH_MASK_  (0x3FFF0000)
#घोषणा RX_DESC_DATA0_FRAME_LENGTH_GET_(data0)	\
	(((data0) & RX_DESC_DATA0_FRAME_LENGTH_MASK_) >> 16)
#घोषणा RX_DESC_DATA0_EXT_                (0x00004000)
#घोषणा RX_DESC_DATA0_BUF_LENGTH_MASK_    (0x00003FFF)
#घोषणा RX_DESC_DATA2_TS_NS_MASK_         (0x3FFFFFFF)

#अगर ((NET_IP_ALIGN != 0) && (NET_IP_ALIGN != 2))
#त्रुटि NET_IP_ALIGN must be 0 or 2
#पूर्ण_अगर

#घोषणा RX_HEAD_PADDING		NET_IP_ALIGN

काष्ठा lan743x_rx_descriptor अणु
	__le32     data0;
	__le32     data1;
	__le32     data2;
	__le32     data3;
पूर्ण __aligned(DEFAULT_DMA_DESCRIPTOR_SPACING);

#घोषणा RX_BUFFER_INFO_FLAG_ACTIVE      BIT(0)
काष्ठा lan743x_rx_buffer_info अणु
	पूर्णांक flags;
	काष्ठा sk_buff *skb;

	dma_addr_t      dma_ptr;
	अचिन्हित पूर्णांक    buffer_length;
पूर्ण;

#घोषणा LAN743X_RX_RING_SIZE        (65)

#घोषणा RX_PROCESS_RESULT_NOTHING_TO_DO     (0)
#घोषणा RX_PROCESS_RESULT_BUFFER_RECEIVED   (1)

u32 lan743x_csr_पढ़ो(काष्ठा lan743x_adapter *adapter, पूर्णांक offset);
व्योम lan743x_csr_ग_लिखो(काष्ठा lan743x_adapter *adapter, पूर्णांक offset, u32 data);

#पूर्ण_अगर /* _LAN743X_H */
