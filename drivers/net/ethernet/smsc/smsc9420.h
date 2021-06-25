<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
 /***************************************************************************
 *
 * Copyright (C) 2007,2008  SMSC
 *
 ***************************************************************************
 */

#अगर_अघोषित _SMSC9420_H
#घोषणा _SMSC9420_H

#घोषणा TX_RING_SIZE			(32)
#घोषणा RX_RING_SIZE			(128)

/* पूर्णांकerrupt deनिश्चितion in multiples of 10us */
#घोषणा INT_DEAS_TIME			(50)

#घोषणा NAPI_WEIGHT			(64)
#घोषणा SMSC_BAR			(3)

#अगर_घोषित __BIG_ENDIAN
/* Register set is duplicated क्रम BE at an offset of 0x200 */
#घोषणा LAN9420_CPSR_ENDIAN_OFFSET	(0x200)
#अन्यथा
#घोषणा LAN9420_CPSR_ENDIAN_OFFSET	(0)
#पूर्ण_अगर

#घोषणा PCI_VENDOR_ID_9420		(0x1055)
#घोषणा PCI_DEVICE_ID_9420		(0xE420)

#घोषणा LAN_REGISTER_EXTENT		(0x400)

#घोषणा SMSC9420_EEPROM_SIZE		((u32)11)
#घोषणा SMSC9420_EEPROM_MAGIC		(0x9420)

#घोषणा PKT_BUF_SZ			(VLAN_ETH_FRAME_LEN + NET_IP_ALIGN + 4)

/***********************************************/
/* DMA Controller Control and Status Registers */
/***********************************************/
#घोषणा BUS_MODE			(0x00)
#घोषणा BUS_MODE_SWR_			(BIT(0))
#घोषणा BUS_MODE_DMA_BURST_LENGTH_1	(BIT(8))
#घोषणा BUS_MODE_DMA_BURST_LENGTH_2	(BIT(9))
#घोषणा BUS_MODE_DMA_BURST_LENGTH_4	(BIT(10))
#घोषणा BUS_MODE_DMA_BURST_LENGTH_8	(BIT(11))
#घोषणा BUS_MODE_DMA_BURST_LENGTH_16	(BIT(12))
#घोषणा BUS_MODE_DMA_BURST_LENGTH_32	(BIT(13))
#घोषणा BUS_MODE_DBO_			(BIT(20))

#घोषणा TX_POLL_DEMAND			(0x04)

#घोषणा RX_POLL_DEMAND			(0x08)

#घोषणा RX_BASE_ADDR			(0x0C)

#घोषणा TX_BASE_ADDR			(0x10)

#घोषणा DMAC_STATUS			(0x14)
#घोषणा DMAC_STS_TS_			(7 << 20)
#घोषणा DMAC_STS_RS_ 			(7 << 17)
#घोषणा DMAC_STS_NIS_			(BIT(16))
#घोषणा DMAC_STS_AIS_			(BIT(15))
#घोषणा DMAC_STS_RWT_			(BIT(9))
#घोषणा DMAC_STS_RXPS_			(BIT(8))
#घोषणा DMAC_STS_RXBU_			(BIT(7))
#घोषणा DMAC_STS_RX_			(BIT(6))
#घोषणा DMAC_STS_TXUNF_			(BIT(5))
#घोषणा DMAC_STS_TXBU_			(BIT(2))
#घोषणा DMAC_STS_TXPS_			(BIT(1))
#घोषणा DMAC_STS_TX_			(BIT(0))

#घोषणा DMAC_CONTROL			(0x18)
#घोषणा DMAC_CONTROL_TTM_		(BIT(22))
#घोषणा DMAC_CONTROL_SF_		(BIT(21))
#घोषणा DMAC_CONTROL_ST_		(BIT(13))
#घोषणा DMAC_CONTROL_OSF_		(BIT(2))
#घोषणा DMAC_CONTROL_SR_		(BIT(1))

#घोषणा DMAC_INTR_ENA			(0x1C)
#घोषणा DMAC_INTR_ENA_NIS_		(BIT(16))
#घोषणा DMAC_INTR_ENA_AIS_		(BIT(15))
#घोषणा DMAC_INTR_ENA_RWT_		(BIT(9))
#घोषणा DMAC_INTR_ENA_RXPS_		(BIT(8))
#घोषणा DMAC_INTR_ENA_RXBU_		(BIT(7))
#घोषणा DMAC_INTR_ENA_RX_		(BIT(6))
#घोषणा DMAC_INTR_ENA_TXBU_		(BIT(2))
#घोषणा DMAC_INTR_ENA_TXPS_		(BIT(1))
#घोषणा DMAC_INTR_ENA_TX_		(BIT(0))

#घोषणा MISS_FRAME_CNTR			(0x20)

#घोषणा TX_BUFF_ADDR			(0x50)

#घोषणा RX_BUFF_ADDR			(0x54)

/* Transmit Descriptor Bit Defs */
#घोषणा TDES0_OWN_			(0x80000000)
#घोषणा TDES0_ERROR_SUMMARY_		(0x00008000)
#घोषणा TDES0_LOSS_OF_CARRIER_		(0x00000800)
#घोषणा TDES0_NO_CARRIER_		(0x00000400)
#घोषणा TDES0_LATE_COLLISION_		(0x00000200)
#घोषणा TDES0_EXCESSIVE_COLLISIONS_	(0x00000100)
#घोषणा TDES0_HEARTBEAT_FAIL_		(0x00000080)
#घोषणा TDES0_COLLISION_COUNT_MASK_	(0x00000078)
#घोषणा TDES0_COLLISION_COUNT_SHFT_	(3)
#घोषणा TDES0_EXCESSIVE_DEFERRAL_	(0x00000004)
#घोषणा TDES0_DEFERRED_			(0x00000001)

#घोषणा TDES1_IC_			0x80000000
#घोषणा TDES1_LS_			0x40000000
#घोषणा TDES1_FS_			0x20000000
#घोषणा TDES1_TXCSEN_			0x08000000
#घोषणा TDES1_TER_			(BIT(25))
#घोषणा TDES1_TCH_			0x01000000

/* Receive Descriptor 0 Bit Defs */
#घोषणा RDES0_OWN_			(0x80000000)
#घोषणा RDES0_FRAME_LENGTH_MASK_	(0x07FF0000)
#घोषणा RDES0_FRAME_LENGTH_SHFT_	(16)
#घोषणा RDES0_ERROR_SUMMARY_		(0x00008000)
#घोषणा RDES0_DESCRIPTOR_ERROR_		(0x00004000)
#घोषणा RDES0_LENGTH_ERROR_		(0x00001000)
#घोषणा RDES0_RUNT_FRAME_		(0x00000800)
#घोषणा RDES0_MULTICAST_FRAME_		(0x00000400)
#घोषणा RDES0_FIRST_DESCRIPTOR_		(0x00000200)
#घोषणा RDES0_LAST_DESCRIPTOR_		(0x00000100)
#घोषणा RDES0_FRAME_TOO_LONG_		(0x00000080)
#घोषणा RDES0_COLLISION_SEEN_		(0x00000040)
#घोषणा RDES0_FRAME_TYPE_		(0x00000020)
#घोषणा RDES0_WATCHDOG_TIMEOUT_		(0x00000010)
#घोषणा RDES0_MII_ERROR_		(0x00000008)
#घोषणा RDES0_DRIBBLING_BIT_		(0x00000004)
#घोषणा RDES0_CRC_ERROR_		(0x00000002)

/* Receive Descriptor 1 Bit Defs */
#घोषणा RDES1_RER_			(0x02000000)

/***********************************************/
/*       MAC Control and Status Registers      */
/***********************************************/
#घोषणा MAC_CR				(0x80)
#घोषणा MAC_CR_RXALL_			(0x80000000)
#घोषणा MAC_CR_DIS_RXOWN_		(0x00800000)
#घोषणा MAC_CR_LOOPBK_			(0x00200000)
#घोषणा MAC_CR_FDPX_			(0x00100000)
#घोषणा MAC_CR_MCPAS_			(0x00080000)
#घोषणा MAC_CR_PRMS_			(0x00040000)
#घोषणा MAC_CR_INVFILT_			(0x00020000)
#घोषणा MAC_CR_PASSBAD_			(0x00010000)
#घोषणा MAC_CR_HFILT_			(0x00008000)
#घोषणा MAC_CR_HPFILT_			(0x00002000)
#घोषणा MAC_CR_LCOLL_			(0x00001000)
#घोषणा MAC_CR_DIS_BCAST_		(0x00000800)
#घोषणा MAC_CR_DIS_RTRY_		(0x00000400)
#घोषणा MAC_CR_PADSTR_			(0x00000100)
#घोषणा MAC_CR_BOLMT_MSK		(0x000000C0)
#घोषणा MAC_CR_MFCHK_			(0x00000020)
#घोषणा MAC_CR_TXEN_			(0x00000008)
#घोषणा MAC_CR_RXEN_			(0x00000004)

#घोषणा ADDRH				(0x84)

#घोषणा ADDRL				(0x88)

#घोषणा HASHH				(0x8C)

#घोषणा HASHL				(0x90)

#घोषणा MII_ACCESS			(0x94)
#घोषणा MII_ACCESS_MII_BUSY_		(0x00000001)
#घोषणा MII_ACCESS_MII_WRITE_		(0x00000002)
#घोषणा MII_ACCESS_MII_READ_		(0x00000000)
#घोषणा MII_ACCESS_INDX_MSK_		(0x000007C0)
#घोषणा MII_ACCESS_PHYADDR_MSK_		(0x0000F8C0)
#घोषणा MII_ACCESS_INDX_SHFT_CNT	(6)
#घोषणा MII_ACCESS_PHYADDR_SHFT_CNT	(11)

#घोषणा MII_DATA			(0x98)

#घोषणा FLOW				(0x9C)

#घोषणा VLAN1				(0xA0)

#घोषणा VLAN2				(0xA4)

#घोषणा WUFF				(0xA8)

#घोषणा WUCSR				(0xAC)

#घोषणा COE_CR				(0xB0)
#घोषणा TX_COE_EN			(0x00010000)
#घोषणा RX_COE_MODE			(0x00000002)
#घोषणा RX_COE_EN			(0x00000001)

/***********************************************/
/*     System Control and Status Registers     */
/***********************************************/
#घोषणा ID_REV				(0xC0)

#घोषणा INT_CTL				(0xC4)
#घोषणा INT_CTL_SW_INT_EN_		(0x00008000)
#घोषणा INT_CTL_SBERR_INT_EN_		(1 << 12)
#घोषणा INT_CTL_MBERR_INT_EN_		(1 << 13)
#घोषणा INT_CTL_GPT_INT_EN_		(0x00000008)
#घोषणा INT_CTL_PHY_INT_EN_		(0x00000004)
#घोषणा INT_CTL_WAKE_INT_EN_		(0x00000002)

#घोषणा INT_STAT			(0xC8)
#घोषणा INT_STAT_SW_INT_		(1 << 15)
#घोषणा INT_STAT_MBERR_INT_		(1 << 13)
#घोषणा INT_STAT_SBERR_INT_		(1 << 12)
#घोषणा INT_STAT_GPT_INT_		(1 << 3)
#घोषणा INT_STAT_PHY_INT_		(0x00000004)
#घोषणा INT_STAT_WAKE_INT_		(0x00000002)
#घोषणा INT_STAT_DMAC_INT_		(0x00000001)

#घोषणा INT_CFG				(0xCC)
#घोषणा INT_CFG_IRQ_INT_		(0x00080000)
#घोषणा INT_CFG_IRQ_EN_			(0x00040000)
#घोषणा INT_CFG_INT_DEAS_CLR_		(0x00000200)
#घोषणा INT_CFG_INT_DEAS_MASK		(0x000000FF)

#घोषणा GPIO_CFG			(0xD0)
#घोषणा GPIO_CFG_LED_3_			(0x40000000)
#घोषणा GPIO_CFG_LED_2_			(0x20000000)
#घोषणा GPIO_CFG_LED_1_			(0x10000000)
#घोषणा GPIO_CFG_EEPR_EN_		(0x00700000)

#घोषणा GPT_CFG				(0xD4)
#घोषणा GPT_CFG_TIMER_EN_		(0x20000000)

#घोषणा GPT_CNT				(0xD8)

#घोषणा BUS_CFG				(0xDC)
#घोषणा BUS_CFG_RXTXWEIGHT_1_1		(0 << 25)
#घोषणा BUS_CFG_RXTXWEIGHT_2_1		(1 << 25)
#घोषणा BUS_CFG_RXTXWEIGHT_3_1		(2 << 25)
#घोषणा BUS_CFG_RXTXWEIGHT_4_1		(3 << 25)

#घोषणा PMT_CTRL			(0xE0)

#घोषणा FREE_RUN			(0xF4)

#घोषणा E2P_CMD				(0xF8)
#घोषणा E2P_CMD_EPC_BUSY_		(0x80000000)
#घोषणा E2P_CMD_EPC_CMD_		(0x70000000)
#घोषणा E2P_CMD_EPC_CMD_READ_		(0x00000000)
#घोषणा E2P_CMD_EPC_CMD_EWDS_		(0x10000000)
#घोषणा E2P_CMD_EPC_CMD_EWEN_		(0x20000000)
#घोषणा E2P_CMD_EPC_CMD_WRITE_		(0x30000000)
#घोषणा E2P_CMD_EPC_CMD_WRAL_		(0x40000000)
#घोषणा E2P_CMD_EPC_CMD_ERASE_		(0x50000000)
#घोषणा E2P_CMD_EPC_CMD_ERAL_		(0x60000000)
#घोषणा E2P_CMD_EPC_CMD_RELOAD_		(0x70000000)
#घोषणा E2P_CMD_EPC_TIMEOUT_		(0x00000200)
#घोषणा E2P_CMD_MAC_ADDR_LOADED_	(0x00000100)
#घोषणा E2P_CMD_EPC_ADDR_		(0x000000FF)

#घोषणा E2P_DATA			(0xFC)
#घोषणा E2P_DATA_EEPROM_DATA_		(0x000000FF)

#पूर्ण_अगर /* _SMSC9420_H */
