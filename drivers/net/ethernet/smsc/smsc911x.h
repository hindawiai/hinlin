<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/***************************************************************************
 *
 * Copyright (C) 2004-2008 SMSC
 * Copyright (C) 2005-2008 ARM
 *
 ***************************************************************************/
#अगर_अघोषित __SMSC911X_H__
#घोषणा __SMSC911X_H__

/*Chip ID*/
#घोषणा LAN9115	0x01150000
#घोषणा LAN9116	0x01160000
#घोषणा LAN9117	0x01170000
#घोषणा LAN9118	0x01180000
#घोषणा LAN9215	0x115A0000
#घोषणा LAN9216	0x116A0000
#घोषणा LAN9217	0x117A0000
#घोषणा LAN9218	0x118A0000
#घोषणा LAN9210	0x92100000
#घोषणा LAN9211	0x92110000
#घोषणा LAN9220	0x92200000
#घोषणा LAN9221	0x92210000
#घोषणा LAN9250	0x92500000
#घोषणा LAN89218	0x218A0000

#घोषणा TX_FIFO_LOW_THRESHOLD	((u32)1600)
#घोषणा SMSC911X_EEPROM_SIZE	((u32)128)
#घोषणा USE_DEBUG		0

/* This is the maximum number of packets to be received every
 * NAPI poll */
#घोषणा SMSC_NAPI_WEIGHT	16

/* implements a PHY loopback test at initialisation समय, to ensure a packet
 * can be successfully looped back */
#घोषणा USE_PHY_WORK_AROUND

#अगर USE_DEBUG >= 1
#घोषणा SMSC_WARN(pdata, nlevel, fmt, args...)			\
	netअगर_warn(pdata, nlevel, (pdata)->dev,			\
		   "%s: " fmt "\n", __func__, ##args)
#अन्यथा
#घोषणा SMSC_WARN(pdata, nlevel, fmt, args...)			\
	no_prपूर्णांकk(fmt "\n", ##args)
#पूर्ण_अगर

#अगर USE_DEBUG >= 2
#घोषणा SMSC_TRACE(pdata, nlevel, fmt, args...)			\
	netअगर_info(pdata, nlevel, pdata->dev, fmt "\n", ##args)
#अन्यथा
#घोषणा SMSC_TRACE(pdata, nlevel, fmt, args...)			\
	no_prपूर्णांकk(fmt "\n", ##args)
#पूर्ण_अगर

#अगर_घोषित CONFIG_DEBUG_SPINLOCK
#घोषणा SMSC_ASSERT_MAC_LOCK(pdata) \
		lockdep_निश्चित_held(&pdata->mac_lock)
#अन्यथा
#घोषणा SMSC_ASSERT_MAC_LOCK(pdata) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर				/* CONFIG_DEBUG_SPINLOCK */

/* SMSC911x रेजिस्टरs and bitfields */
#घोषणा RX_DATA_FIFO			0x00

#घोषणा TX_DATA_FIFO			0x20
#घोषणा TX_CMD_A_ON_COMP_		0x80000000
#घोषणा TX_CMD_A_BUF_END_ALGN_		0x03000000
#घोषणा TX_CMD_A_4_BYTE_ALGN_		0x00000000
#घोषणा TX_CMD_A_16_BYTE_ALGN_		0x01000000
#घोषणा TX_CMD_A_32_BYTE_ALGN_		0x02000000
#घोषणा TX_CMD_A_DATA_OFFSET_		0x001F0000
#घोषणा TX_CMD_A_FIRST_SEG_		0x00002000
#घोषणा TX_CMD_A_LAST_SEG_		0x00001000
#घोषणा TX_CMD_A_BUF_SIZE_		0x000007FF
#घोषणा TX_CMD_B_PKT_TAG_		0xFFFF0000
#घोषणा TX_CMD_B_ADD_CRC_DISABLE_	0x00002000
#घोषणा TX_CMD_B_DISABLE_PADDING_	0x00001000
#घोषणा TX_CMD_B_PKT_BYTE_LENGTH_	0x000007FF

#घोषणा RX_STATUS_FIFO			0x40
#घोषणा RX_STS_ES_			0x00008000
#घोषणा RX_STS_LENGTH_ERR_		0x00001000
#घोषणा RX_STS_MCAST_			0x00000400
#घोषणा RX_STS_FRAME_TYPE_		0x00000020
#घोषणा RX_STS_CRC_ERR_			0x00000002

#घोषणा RX_STATUS_FIFO_PEEK		0x44

#घोषणा TX_STATUS_FIFO			0x48
#घोषणा TX_STS_ES_			0x00008000
#घोषणा TX_STS_LOST_CARRIER_		0x00000800
#घोषणा TX_STS_NO_CARRIER_		0x00000400
#घोषणा TX_STS_LATE_COL_		0x00000200
#घोषणा TX_STS_EXCESS_COL_		0x00000100

#घोषणा TX_STATUS_FIFO_PEEK		0x4C

#घोषणा ID_REV				0x50
#घोषणा ID_REV_CHIP_ID_			0xFFFF0000
#घोषणा ID_REV_REV_ID_			0x0000FFFF

#घोषणा INT_CFG				0x54
#घोषणा INT_CFG_INT_DEAS_		0xFF000000
#घोषणा INT_CFG_INT_DEAS_CLR_		0x00004000
#घोषणा INT_CFG_INT_DEAS_STS_		0x00002000
#घोषणा INT_CFG_IRQ_INT_		0x00001000
#घोषणा INT_CFG_IRQ_EN_			0x00000100
#घोषणा INT_CFG_IRQ_POL_		0x00000010
#घोषणा INT_CFG_IRQ_TYPE_		0x00000001

#घोषणा INT_STS				0x58
#घोषणा INT_STS_SW_INT_			0x80000000
#घोषणा INT_STS_TXSTOP_INT_		0x02000000
#घोषणा INT_STS_RXSTOP_INT_		0x01000000
#घोषणा INT_STS_RXDFH_INT_		0x00800000
#घोषणा INT_STS_RXDF_INT_		0x00400000
#घोषणा INT_STS_TX_IOC_			0x00200000
#घोषणा INT_STS_RXD_INT_		0x00100000
#घोषणा INT_STS_GPT_INT_		0x00080000
#घोषणा INT_STS_PHY_INT_		0x00040000
#घोषणा INT_STS_PME_INT_		0x00020000
#घोषणा INT_STS_TXSO_			0x00010000
#घोषणा INT_STS_RWT_			0x00008000
#घोषणा INT_STS_RXE_			0x00004000
#घोषणा INT_STS_TXE_			0x00002000
#घोषणा INT_STS_TDFU_			0x00000800
#घोषणा INT_STS_TDFO_			0x00000400
#घोषणा INT_STS_TDFA_			0x00000200
#घोषणा INT_STS_TSFF_			0x00000100
#घोषणा INT_STS_TSFL_			0x00000080
#घोषणा INT_STS_RXDF_			0x00000040
#घोषणा INT_STS_RDFL_			0x00000020
#घोषणा INT_STS_RSFF_			0x00000010
#घोषणा INT_STS_RSFL_			0x00000008
#घोषणा INT_STS_GPIO2_INT_		0x00000004
#घोषणा INT_STS_GPIO1_INT_		0x00000002
#घोषणा INT_STS_GPIO0_INT_		0x00000001

#घोषणा INT_EN				0x5C
#घोषणा INT_EN_SW_INT_EN_		0x80000000
#घोषणा INT_EN_TXSTOP_INT_EN_		0x02000000
#घोषणा INT_EN_RXSTOP_INT_EN_		0x01000000
#घोषणा INT_EN_RXDFH_INT_EN_		0x00800000
#घोषणा INT_EN_TIOC_INT_EN_		0x00200000
#घोषणा INT_EN_RXD_INT_EN_		0x00100000
#घोषणा INT_EN_GPT_INT_EN_		0x00080000
#घोषणा INT_EN_PHY_INT_EN_		0x00040000
#घोषणा INT_EN_PME_INT_EN_		0x00020000
#घोषणा INT_EN_TXSO_EN_			0x00010000
#घोषणा INT_EN_RWT_EN_			0x00008000
#घोषणा INT_EN_RXE_EN_			0x00004000
#घोषणा INT_EN_TXE_EN_			0x00002000
#घोषणा INT_EN_TDFU_EN_			0x00000800
#घोषणा INT_EN_TDFO_EN_			0x00000400
#घोषणा INT_EN_TDFA_EN_			0x00000200
#घोषणा INT_EN_TSFF_EN_			0x00000100
#घोषणा INT_EN_TSFL_EN_			0x00000080
#घोषणा INT_EN_RXDF_EN_			0x00000040
#घोषणा INT_EN_RDFL_EN_			0x00000020
#घोषणा INT_EN_RSFF_EN_			0x00000010
#घोषणा INT_EN_RSFL_EN_			0x00000008
#घोषणा INT_EN_GPIO2_INT_		0x00000004
#घोषणा INT_EN_GPIO1_INT_		0x00000002
#घोषणा INT_EN_GPIO0_INT_		0x00000001

#घोषणा BYTE_TEST			0x64

#घोषणा FIFO_INT			0x68
#घोषणा FIFO_INT_TX_AVAIL_LEVEL_	0xFF000000
#घोषणा FIFO_INT_TX_STS_LEVEL_		0x00FF0000
#घोषणा FIFO_INT_RX_AVAIL_LEVEL_	0x0000FF00
#घोषणा FIFO_INT_RX_STS_LEVEL_		0x000000FF

#घोषणा RX_CFG				0x6C
#घोषणा RX_CFG_RX_END_ALGN_		0xC0000000
#घोषणा RX_CFG_RX_END_ALGN4_		0x00000000
#घोषणा RX_CFG_RX_END_ALGN16_		0x40000000
#घोषणा RX_CFG_RX_END_ALGN32_		0x80000000
#घोषणा RX_CFG_RX_DMA_CNT_		0x0FFF0000
#घोषणा RX_CFG_RX_DUMP_			0x00008000
#घोषणा RX_CFG_RXDOFF_			0x00001F00

#घोषणा TX_CFG				0x70
#घोषणा TX_CFG_TXS_DUMP_		0x00008000
#घोषणा TX_CFG_TXD_DUMP_		0x00004000
#घोषणा TX_CFG_TXSAO_			0x00000004
#घोषणा TX_CFG_TX_ON_			0x00000002
#घोषणा TX_CFG_STOP_TX_			0x00000001

#घोषणा HW_CFG				0x74
#घोषणा HW_CFG_TTM_			0x00200000
#घोषणा HW_CFG_SF_			0x00100000
#घोषणा HW_CFG_TX_FIF_SZ_		0x000F0000
#घोषणा HW_CFG_TR_			0x00003000
#घोषणा HW_CFG_SRST_			0x00000001

/* only available on 115/117 */
#घोषणा HW_CFG_PHY_CLK_SEL_		0x00000060
#घोषणा HW_CFG_PHY_CLK_SEL_INT_PHY_	0x00000000
#घोषणा HW_CFG_PHY_CLK_SEL_EXT_PHY_	0x00000020
#घोषणा HW_CFG_PHY_CLK_SEL_CLK_DIS_	0x00000040
#घोषणा HW_CFG_SMI_SEL_		 	0x00000010
#घोषणा HW_CFG_EXT_PHY_DET_		0x00000008
#घोषणा HW_CFG_EXT_PHY_EN_		0x00000004
#घोषणा HW_CFG_SRST_TO_			0x00000002

/* only available  on 116/118 */
#घोषणा HW_CFG_32_16_BIT_MODE_		0x00000004

#घोषणा RX_DP_CTRL			0x78
#घोषणा RX_DP_CTRL_RX_FFWD_		0x80000000

#घोषणा RX_FIFO_INF			0x7C
#घोषणा RX_FIFO_INF_RXSUSED_		0x00FF0000
#घोषणा RX_FIFO_INF_RXDUSED_		0x0000FFFF

#घोषणा TX_FIFO_INF			0x80
#घोषणा TX_FIFO_INF_TSUSED_		0x00FF0000
#घोषणा TX_FIFO_INF_TDFREE_		0x0000FFFF

#घोषणा PMT_CTRL			0x84
#घोषणा PMT_CTRL_PM_MODE_		0x00003000
#घोषणा PMT_CTRL_PM_MODE_D0_		0x00000000
#घोषणा PMT_CTRL_PM_MODE_D1_		0x00001000
#घोषणा PMT_CTRL_PM_MODE_D2_		0x00002000
#घोषणा PMT_CTRL_PM_MODE_D3_		0x00003000
#घोषणा PMT_CTRL_PHY_RST_		0x00000400
#घोषणा PMT_CTRL_WOL_EN_		0x00000200
#घोषणा PMT_CTRL_ED_EN_			0x00000100
#घोषणा PMT_CTRL_PME_TYPE_		0x00000040
#घोषणा PMT_CTRL_WUPS_			0x00000030
#घोषणा PMT_CTRL_WUPS_NOWAKE_		0x00000000
#घोषणा PMT_CTRL_WUPS_ED_		0x00000010
#घोषणा PMT_CTRL_WUPS_WOL_		0x00000020
#घोषणा PMT_CTRL_WUPS_MULTI_		0x00000030
#घोषणा PMT_CTRL_PME_IND_		0x00000008
#घोषणा PMT_CTRL_PME_POL_		0x00000004
#घोषणा PMT_CTRL_PME_EN_		0x00000002
#घोषणा PMT_CTRL_READY_			0x00000001

#घोषणा GPIO_CFG			0x88
#घोषणा GPIO_CFG_LED3_EN_		0x40000000
#घोषणा GPIO_CFG_LED2_EN_		0x20000000
#घोषणा GPIO_CFG_LED1_EN_		0x10000000
#घोषणा GPIO_CFG_GPIO2_INT_POL_		0x04000000
#घोषणा GPIO_CFG_GPIO1_INT_POL_		0x02000000
#घोषणा GPIO_CFG_GPIO0_INT_POL_		0x01000000
#घोषणा GPIO_CFG_EEPR_EN_		0x00700000
#घोषणा GPIO_CFG_GPIOBUF2_		0x00040000
#घोषणा GPIO_CFG_GPIOBUF1_		0x00020000
#घोषणा GPIO_CFG_GPIOBUF0_		0x00010000
#घोषणा GPIO_CFG_GPIOसूची2_		0x00000400
#घोषणा GPIO_CFG_GPIOसूची1_		0x00000200
#घोषणा GPIO_CFG_GPIOसूची0_		0x00000100
#घोषणा GPIO_CFG_GPIOD4_		0x00000020
#घोषणा GPIO_CFG_GPIOD3_		0x00000010
#घोषणा GPIO_CFG_GPIOD2_		0x00000004
#घोषणा GPIO_CFG_GPIOD1_		0x00000002
#घोषणा GPIO_CFG_GPIOD0_		0x00000001

#घोषणा GPT_CFG				0x8C
#घोषणा GPT_CFG_TIMER_EN_		0x20000000
#घोषणा GPT_CFG_GPT_LOAD_		0x0000FFFF

#घोषणा GPT_CNT				0x90
#घोषणा GPT_CNT_GPT_CNT_		0x0000FFFF

#घोषणा WORD_SWAP			0x98

#घोषणा FREE_RUN			0x9C

#घोषणा RX_DROP				0xA0

#घोषणा MAC_CSR_CMD			0xA4
#घोषणा MAC_CSR_CMD_CSR_BUSY_		0x80000000
#घोषणा MAC_CSR_CMD_R_NOT_W_		0x40000000
#घोषणा MAC_CSR_CMD_CSR_ADDR_		0x000000FF

#घोषणा MAC_CSR_DATA			0xA8

#घोषणा AFC_CFG				0xAC
#घोषणा AFC_CFG_AFC_HI_			0x00FF0000
#घोषणा AFC_CFG_AFC_LO_			0x0000FF00
#घोषणा AFC_CFG_BACK_DUR_		0x000000F0
#घोषणा AFC_CFG_FCMULT_			0x00000008
#घोषणा AFC_CFG_FCBRD_			0x00000004
#घोषणा AFC_CFG_FCADD_			0x00000002
#घोषणा AFC_CFG_FCANY_			0x00000001

#घोषणा E2P_CMD				0xB0
#घोषणा E2P_CMD_EPC_BUSY_		0x80000000
#घोषणा E2P_CMD_EPC_CMD_		0x70000000
#घोषणा E2P_CMD_EPC_CMD_READ_		0x00000000
#घोषणा E2P_CMD_EPC_CMD_EWDS_		0x10000000
#घोषणा E2P_CMD_EPC_CMD_EWEN_		0x20000000
#घोषणा E2P_CMD_EPC_CMD_WRITE_		0x30000000
#घोषणा E2P_CMD_EPC_CMD_WRAL_		0x40000000
#घोषणा E2P_CMD_EPC_CMD_ERASE_		0x50000000
#घोषणा E2P_CMD_EPC_CMD_ERAL_		0x60000000
#घोषणा E2P_CMD_EPC_CMD_RELOAD_		0x70000000
#घोषणा E2P_CMD_EPC_TIMEOUT_		0x00000200
#घोषणा E2P_CMD_MAC_ADDR_LOADED_	0x00000100
#घोषणा E2P_CMD_EPC_ADDR_		0x000000FF

#घोषणा E2P_DATA			0xB4
#घोषणा E2P_DATA_EEPROM_DATA_		0x000000FF
#घोषणा LAN_REGISTER_EXTENT		0x00000100

#घोषणा RESET_CTL			0x1F8
#घोषणा RESET_CTL_DIGITAL_RST_		0x00000001

/*
 * MAC Control and Status Register (Indirect Address)
 * Offset (through the MAC_CSR CMD and DATA port)
 */
#घोषणा MAC_CR				0x01
#घोषणा MAC_CR_RXALL_			0x80000000
#घोषणा MAC_CR_HBDIS_			0x10000000
#घोषणा MAC_CR_RCVOWN_			0x00800000
#घोषणा MAC_CR_LOOPBK_			0x00200000
#घोषणा MAC_CR_FDPX_			0x00100000
#घोषणा MAC_CR_MCPAS_			0x00080000
#घोषणा MAC_CR_PRMS_			0x00040000
#घोषणा MAC_CR_INVFILT_			0x00020000
#घोषणा MAC_CR_PASSBAD_			0x00010000
#घोषणा MAC_CR_HFILT_			0x00008000
#घोषणा MAC_CR_HPFILT_			0x00002000
#घोषणा MAC_CR_LCOLL_			0x00001000
#घोषणा MAC_CR_BCAST_			0x00000800
#घोषणा MAC_CR_DISRTY_			0x00000400
#घोषणा MAC_CR_PADSTR_			0x00000100
#घोषणा MAC_CR_BOLMT_MASK_		0x000000C0
#घोषणा MAC_CR_DFCHK_			0x00000020
#घोषणा MAC_CR_TXEN_			0x00000008
#घोषणा MAC_CR_RXEN_			0x00000004

#घोषणा ADDRH				0x02

#घोषणा ADDRL				0x03

#घोषणा HASHH				0x04

#घोषणा HASHL				0x05

#घोषणा MII_ACC				0x06
#घोषणा MII_ACC_PHY_ADDR_		0x0000F800
#घोषणा MII_ACC_MIIRINDA_		0x000007C0
#घोषणा MII_ACC_MII_WRITE_		0x00000002
#घोषणा MII_ACC_MII_BUSY_		0x00000001

#घोषणा MII_DATA			0x07

#घोषणा FLOW				0x08
#घोषणा FLOW_FCPT_			0xFFFF0000
#घोषणा FLOW_FCPASS_			0x00000004
#घोषणा FLOW_FCEN_			0x00000002
#घोषणा FLOW_FCBSY_			0x00000001

#घोषणा VLAN1				0x09

#घोषणा VLAN2				0x0A

#घोषणा WUFF				0x0B

#घोषणा WUCSR				0x0C
#घोषणा WUCSR_GUE_			0x00000200
#घोषणा WUCSR_WUFR_			0x00000040
#घोषणा WUCSR_MPR_			0x00000020
#घोषणा WUCSR_WAKE_EN_			0x00000004
#घोषणा WUCSR_MPEN_			0x00000002

/*
 * Phy definitions (venकरोr-specअगरic)
 */
#घोषणा LAN9118_PHY_ID			0x00C0001C

#घोषणा MII_INTSTS			0x1D

#घोषणा MII_INTMSK			0x1E
#घोषणा PHY_INTMSK_AN_RCV_		(1 << 1)
#घोषणा PHY_INTMSK_PDFAULT_		(1 << 2)
#घोषणा PHY_INTMSK_AN_ACK_		(1 << 3)
#घोषणा PHY_INTMSK_LNKDOWN_		(1 << 4)
#घोषणा PHY_INTMSK_RFAULT_		(1 << 5)
#घोषणा PHY_INTMSK_AN_COMP_		(1 << 6)
#घोषणा PHY_INTMSK_ENERGYON_		(1 << 7)
#घोषणा PHY_INTMSK_DEFAULT_		(PHY_INTMSK_ENERGYON_ | \
					 PHY_INTMSK_AN_COMP_ | \
					 PHY_INTMSK_RFAULT_ | \
					 PHY_INTMSK_LNKDOWN_)

#घोषणा ADVERTISE_PAUSE_ALL		(ADVERTISE_PAUSE_CAP | \
					 ADVERTISE_PAUSE_ASYM)

#घोषणा LPA_PAUSE_ALL			(LPA_PAUSE_CAP | \
					 LPA_PAUSE_ASYM)

/*
 * Provide hooks to let the arch add to the initialisation procedure
 * and to override the source of the MAC address.
 */
#घोषणा SMSC_INITIALIZE()		करो अणुपूर्ण जबतक (0)
#घोषणा smsc_get_mac(dev)		smsc911x_पढ़ो_mac_address((dev))

#अगर_घोषित CONFIG_SMSC911X_ARCH_HOOKS
#समावेश <यंत्र/smsc911x.h>
#पूर्ण_अगर

#समावेश <linux/smscphy.h>

#पूर्ण_अगर				/* __SMSC911X_H__ */
