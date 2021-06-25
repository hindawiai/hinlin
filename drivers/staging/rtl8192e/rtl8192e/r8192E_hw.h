<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright(c) 2008 - 2010 Realtek Corporation. All rights reserved.
 *
 * Contact Inक्रमmation: wlanfae <wlanfae@realtek.com>
 */
#अगर_अघोषित R8180_HW
#घोषणा R8180_HW

क्रमागत baseband_config अणु
	BaseBand_Config_PHY_REG = 0,
	BaseBand_Config_AGC_TAB = 1,
पूर्ण;

#घोषणा	RTL8187_REQT_READ	0xc0
#घोषणा	RTL8187_REQT_WRITE	0x40
#घोषणा	RTL8187_REQ_GET_REGS	0x05
#घोषणा	RTL8187_REQ_SET_REGS	0x05

#घोषणा MAX_TX_URB 5
#घोषणा MAX_RX_URB 16
#घोषणा RX_URB_SIZE 9100

#घोषणा BB_ANTATTEN_CHAN14	0x0c
#घोषणा BB_ANTENNA_B 0x40

#घोषणा BB_HOST_BANG (1<<30)
#घोषणा BB_HOST_BANG_EN (1<<2)
#घोषणा BB_HOST_BANG_CLK (1<<1)
#घोषणा BB_HOST_BANG_RW (1<<3)
#घोषणा BB_HOST_BANG_DATA	 1

#घोषणा RTL8190_EEPROM_ID	0x8129
#घोषणा EEPROM_VID		0x02
#घोषणा EEPROM_DID		0x04
#घोषणा EEPROM_NODE_ADDRESS_BYTE_0	0x0C

#घोषणा EEPROM_TxPowerDअगरf	0x1F


#घोषणा EEPROM_PwDअगरf		0x21
#घोषणा EEPROM_CrystalCap	0x22



#घोषणा EEPROM_TxPwIndex_CCK_V1		0x29
#घोषणा EEPROM_TxPwIndex_OFDM_24G_V1	0x2C
#घोषणा EEPROM_TxPwIndex_Ver		0x27

#घोषणा EEPROM_Default_TxPowerDअगरf		0x0
#घोषणा EEPROM_Default_ThermalMeter		0x77
#घोषणा EEPROM_Default_AntTxPowerDअगरf		0x0
#घोषणा EEPROM_Default_TxPwDअगरf_CrystalCap	0x5
#घोषणा EEPROM_Default_PwDअगरf			0x4
#घोषणा EEPROM_Default_CrystalCap		0x5
#घोषणा EEPROM_Default_TxPower			0x1010
#घोषणा EEPROM_ICVersion_ChannelPlan	0x7C
#घोषणा EEPROM_Customer_ID			0x7B
#घोषणा EEPROM_RFInd_PowerDअगरf			0x28
#घोषणा EEPROM_ThermalMeter			0x29
#घोषणा EEPROM_TxPwDअगरf_CrystalCap		0x2A
#घोषणा EEPROM_TxPwIndex_CCK			0x2C
#घोषणा EEPROM_TxPwIndex_OFDM_24G	0x3A
#घोषणा EEPROM_Default_TxPowerLevel		0x10
#घोषणा EEPROM_IC_VER				0x7d
#घोषणा EEPROM_CRC				0x7e

#घोषणा EEPROM_CID_DEFAULT			0x0
#घोषणा EEPROM_CID_CAMEO				0x1
#घोषणा EEPROM_CID_RUNTOP				0x2
#घोषणा EEPROM_CID_Senao				0x3
#घोषणा EEPROM_CID_TOSHIBA				0x4
#घोषणा EEPROM_CID_NetCore				0x5
#घोषणा EEPROM_CID_Nettronix			0x6
#घोषणा EEPROM_CID_Pronet				0x7
#घोषणा EEPROM_CID_DLINK				0x8
#घोषणा EEPROM_CID_WHQL					0xFE
क्रमागत _RTL8192Pci_HW अणु
	MAC0			= 0x000,
	MAC1			= 0x001,
	MAC2			= 0x002,
	MAC3			= 0x003,
	MAC4			= 0x004,
	MAC5			= 0x005,
	PCIF			= 0x009,
#घोषणा MXDMA2_16bytes		0x000
#घोषणा MXDMA2_32bytes		0x001
#घोषणा MXDMA2_64bytes		0x010
#घोषणा MXDMA2_128bytes		0x011
#घोषणा MXDMA2_256bytes		0x100
#घोषणा MXDMA2_512bytes		0x101
#घोषणा MXDMA2_1024bytes	0x110
#घोषणा MXDMA2_NoLimit		0x7

#घोषणा	MULRW_SHIFT		3
#घोषणा	MXDMA2_RX_SHIFT		4
#घोषणा	MXDMA2_TX_SHIFT		0
	PMR			= 0x00c,
	EPROM_CMD		= 0x00e,
#घोषणा EPROM_CMD_RESERVED_MASK BIT5
#घोषणा EPROM_CMD_9356SEL	BIT4
#घोषणा EPROM_CMD_OPERATING_MODE_SHIFT 6
#घोषणा EPROM_CMD_OPERATING_MODE_MASK ((1<<7)|(1<<6))
#घोषणा EPROM_CMD_CONFIG 0x3
#घोषणा EPROM_CMD_NORMAL 0
#घोषणा EPROM_CMD_LOAD 1
#घोषणा EPROM_CMD_PROGRAM 2
#घोषणा EPROM_CS_BIT 3
#घोषणा EPROM_CK_BIT 2
#घोषणा EPROM_W_BIT 1
#घोषणा EPROM_R_BIT 0

	AFR			 = 0x010,
#घोषणा AFR_CardBEn		(1<<0)
#घोषणा AFR_CLKRUN_SEL		(1<<1)
#घोषणा AFR_FuncRegEn		(1<<2)

	ANAPAR			= 0x17,
#घोषणा	BB_GLOBAL_RESET_BIT	0x1
	BB_GLOBAL_RESET		= 0x020,
	BSSIDR			= 0x02E,
	CMDR			= 0x037,
#घोषणा		CR_RST					0x10
#घोषणा		CR_RE					0x08
#घोषणा		CR_TE					0x04
#घोषणा		CR_MulRW				0x01
	SIFS		= 0x03E,
	TCR			= 0x040,
	RCR			= 0x044,
#घोषणा RCR_FILTER_MASK (BIT0 | BIT1 | BIT2 | BIT3 | BIT5 | BIT12 |	\
			BIT18 | BIT19 | BIT20 | BIT21 | BIT22 | BIT23)
#घोषणा RCR_ONLYERLPKT		BIT31
#घोषणा RCR_ENCS2		BIT30
#घोषणा RCR_ENCS1		BIT29
#घोषणा RCR_ENMBID		BIT27
#घोषणा RCR_ACKTXBW		(BIT24|BIT25)
#घोषणा RCR_CBSSID		BIT23
#घोषणा RCR_APWRMGT		BIT22
#घोषणा	RCR_ADD3		BIT21
#घोषणा RCR_AMF			BIT20
#घोषणा RCR_ACF			BIT19
#घोषणा RCR_ADF			BIT18
#घोषणा RCR_RXFTH		BIT13
#घोषणा RCR_AICV		BIT12
#घोषणा	RCR_ACRC32		BIT5
#घोषणा	RCR_AB			BIT3
#घोषणा	RCR_AM			BIT2
#घोषणा	RCR_APM			BIT1
#घोषणा	RCR_AAP			BIT0
#घोषणा RCR_MXDMA_OFFSET	8
#घोषणा RCR_FIFO_OFFSET		13
	SLOT_TIME		= 0x049,
	ACK_TIMEOUT		= 0x04c,
	PIFS_TIME		= 0x04d,
	USTIME			= 0x04e,
	EDCAPARA_BE		= 0x050,
	EDCAPARA_BK		= 0x054,
	EDCAPARA_VO		= 0x058,
	EDCAPARA_VI		= 0x05C,
#घोषणा	AC_PARAM_TXOP_LIMIT_OFFSET		16
#घोषणा	AC_PARAM_ECW_MAX_OFFSET		12
#घोषणा	AC_PARAM_ECW_MIN_OFFSET			8
#घोषणा	AC_PARAM_AIFS_OFFSET				0
	RFPC			= 0x05F,
	CWRR			= 0x060,
	BCN_TCFG		= 0x062,
#घोषणा BCN_TCFG_CW_SHIFT		8
#घोषणा BCN_TCFG_IFS			0
	BCN_INTERVAL		= 0x070,
	ATIMWND			= 0x072,
	BCN_DRV_EARLY_INT	= 0x074,
#घोषणा	BCN_DRV_EARLY_INT_SWBCN_SHIFT	8
#घोषणा	BCN_DRV_EARLY_INT_TIME_SHIFT	0
	BCN_DMATIME		= 0x076,
	BCN_ERR_THRESH		= 0x078,
	RWCAM			= 0x0A0,
#घोषणा   CAM_CM_SecCAMPolling		BIT31
#घोषणा   CAM_CM_SecCAMClr			BIT30
#घोषणा   CAM_CM_SecCAMWE			BIT16
#घोषणा   CAM_VALID			       BIT15
#घोषणा   CAM_NOTVALID			0x0000
#घोषणा   CAM_USEDK				BIT5

#घोषणा   CAM_NONE				0x0
#घोषणा   CAM_WEP40				0x01
#घोषणा   CAM_TKIP				0x02
#घोषणा   CAM_AES				0x04
#घोषणा   CAM_WEP104			0x05

#घोषणा   TOTAL_CAM_ENTRY				32

#घोषणा   CAM_CONFIG_USEDK	true
#घोषणा   CAM_CONFIG_NO_USEDK	false
#घोषणा   CAM_WRITE		BIT16
#घोषणा   CAM_READ		0x00000000
#घोषणा   CAM_POLLINIG		BIT31
#घोषणा   SCR_UseDK		0x01
	WCAMI			= 0x0A4,
	RCAMO			= 0x0A8,
	SECR			= 0x0B0,
#घोषणा	SCR_TxUseDK			BIT0
#घोषणा   SCR_RxUseDK			BIT1
#घोषणा   SCR_TxEncEnable		BIT2
#घोषणा   SCR_RxDecEnable		BIT3
#घोषणा   SCR_SKByA2				BIT4
#घोषणा   SCR_NoSKMC				BIT5
	SWREGULATOR	= 0x0BD,
	INTA_MASK		= 0x0f4,
#घोषणा IMR8190_DISABLED		0x0
#घोषणा IMR_ATIMEND			BIT28
#घोषणा IMR_TBDOK			BIT27
#घोषणा IMR_TBDER			BIT26
#घोषणा IMR_TXFOVW			BIT15
#घोषणा IMR_TIMEOUT0			BIT14
#घोषणा IMR_BcnInt			BIT13
#घोषणा	IMR_RXFOVW			BIT12
#घोषणा IMR_RDU				BIT11
#घोषणा IMR_RXCMDOK			BIT10
#घोषणा IMR_BDOK			BIT9
#घोषणा IMR_HIGHDOK			BIT8
#घोषणा	IMR_COMDOK			BIT7
#घोषणा IMR_MGNTDOK			BIT6
#घोषणा IMR_HCCADOK			BIT5
#घोषणा	IMR_BKDOK			BIT4
#घोषणा	IMR_BEDOK			BIT3
#घोषणा	IMR_VIDOK			BIT2
#घोषणा	IMR_VODOK			BIT1
#घोषणा	IMR_ROK				BIT0
	ISR			= 0x0f8,
	TPPoll			= 0x0fd,
#घोषणा TPPoll_BKQ		BIT0
#घोषणा TPPoll_BEQ		BIT1
#घोषणा TPPoll_VIQ		BIT2
#घोषणा TPPoll_VOQ		BIT3
#घोषणा TPPoll_BQ		BIT4
#घोषणा TPPoll_CQ		BIT5
#घोषणा TPPoll_MQ		BIT6
#घोषणा TPPoll_HQ		BIT7
#घोषणा TPPoll_HCCAQ		BIT8
#घोषणा TPPoll_StopBK	BIT9
#घोषणा TPPoll_StopBE	BIT10
#घोषणा TPPoll_StopVI		BIT11
#घोषणा TPPoll_StopVO	BIT12
#घोषणा TPPoll_StopMgt	BIT13
#घोषणा TPPoll_StopHigh	BIT14
#घोषणा TPPoll_StopHCCA	BIT15
#घोषणा TPPoll_SHIFT		8

	PSR			= 0x0ff,
#घोषणा PSR_GEN			0x0
#घोषणा PSR_CPU			0x1
	CPU_GEN			= 0x100,
	BB_RESET			= 0x101,
#घोषणा	CPU_CCK_LOOPBACK	0x00030000
#घोषणा	CPU_GEN_SYSTEM_RESET	0x00000001
#घोषणा	CPU_GEN_FIRMWARE_RESET	0x00000008
#घोषणा	CPU_GEN_BOOT_RDY	0x00000010
#घोषणा	CPU_GEN_FIRM_RDY	0x00000020
#घोषणा	CPU_GEN_PUT_CODE_OK	0x00000080
#घोषणा	CPU_GEN_BB_RST		0x00000100
#घोषणा	CPU_GEN_PWR_STB_CPU	0x00000004
#घोषणा CPU_GEN_NO_LOOPBACK_MSK	0xFFF8FFFF
#घोषणा CPU_GEN_NO_LOOPBACK_SET	0x00080000
#घोषणा	CPU_GEN_GPIO_UART		0x00007000

	LED1Cfg			= 0x154,
	LED0Cfg			= 0x155,

	AcmAvg			= 0x170,
	AcmHwCtrl		= 0x171,
#घोषणा	AcmHw_HwEn		BIT0
#घोषणा	AcmHw_BeqEn		BIT1
#घोषणा	AcmHw_ViqEn		BIT2
#घोषणा	AcmHw_VoqEn		BIT3
#घोषणा	AcmHw_BeqStatus		BIT4
#घोषणा	AcmHw_ViqStatus		BIT5
#घोषणा	AcmHw_VoqStatus		BIT6
	AcmFwCtrl		= 0x172,
#घोषणा	AcmFw_BeqStatus		BIT0
#घोषणा	AcmFw_ViqStatus		BIT1
#घोषणा	AcmFw_VoqStatus		BIT2
	VOAdmTime		= 0x174,
	VIAdmTime		= 0x178,
	BEAdmTime		= 0x17C,
	RQPN1			= 0x180,
	RQPN2			= 0x184,
	RQPN3			= 0x188,
	QPRR			= 0x1E0,
	QPNR			= 0x1F0,
	BQDA			= 0x200,
	HQDA			= 0x204,
	CQDA			= 0x208,
	MQDA			= 0x20C,
	HCCAQDA			= 0x210,
	VOQDA			= 0x214,
	VIQDA			= 0x218,
	BEQDA			= 0x21C,
	BKQDA			= 0x220,
	RCQDA			= 0x224,
	RDQDA			= 0x228,

	MAR0			= 0x240,
	MAR4			= 0x244,

	CCX_PERIOD		= 0x250,
	CLM_RESULT		= 0x251,
	NHM_PERIOD		= 0x252,

	NHM_THRESHOLD0		= 0x253,
	NHM_THRESHOLD1		= 0x254,
	NHM_THRESHOLD2		= 0x255,
	NHM_THRESHOLD3		= 0x256,
	NHM_THRESHOLD4		= 0x257,
	NHM_THRESHOLD5		= 0x258,
	NHM_THRESHOLD6		= 0x259,

	MCTRL			= 0x25A,

	NHM_RPI_COUNTER0	= 0x264,
	NHM_RPI_COUNTER1	= 0x265,
	NHM_RPI_COUNTER2	= 0x266,
	NHM_RPI_COUNTER3	= 0x267,
	NHM_RPI_COUNTER4	= 0x268,
	NHM_RPI_COUNTER5	= 0x269,
	NHM_RPI_COUNTER6	= 0x26A,
	NHM_RPI_COUNTER7	= 0x26B,
	WFCRC0		  = 0x2f0,
	WFCRC1		  = 0x2f4,
	WFCRC2		  = 0x2f8,

	BW_OPMODE		= 0x300,
#घोषणा	BW_OPMODE_11J			BIT0
#घोषणा	BW_OPMODE_5G			BIT1
#घोषणा	BW_OPMODE_20MHZ			BIT2
	IC_VERRSION		= 0x301,
	MSR			= 0x303,
#घोषणा MSR_LINK_MASK      ((1<<0)|(1<<1))
#घोषणा MSR_LINK_MANAGED   2
#घोषणा MSR_LINK_NONE      0
#घोषणा MSR_LINK_SHIFT     0
#घोषणा MSR_LINK_ADHOC     1
#घोषणा MSR_LINK_MASTER    3
#घोषणा MSR_LINK_ENEDCA	   (1<<4)

#घोषणा	MSR_NOLINK					0x00
#घोषणा	MSR_ADHOC					0x01
#घोषणा	MSR_INFRA					0x02
#घोषणा	MSR_AP						0x03

	RETRY_LIMIT		= 0x304,
#घोषणा RETRY_LIMIT_SHORT_SHIFT 8
#घोषणा RETRY_LIMIT_LONG_SHIFT 0
	TSFR			= 0x308,
	RRSR			= 0x310,
#घोषणा RRSR_RSC_OFFSET				21
#घोषणा RRSR_SHORT_OFFSET			23
#घोषणा RRSR_RSC_DUPLICATE			0x600000
#घोषणा RRSR_RSC_UPSUBCHNL			0x400000
#घोषणा RRSR_RSC_LOWSUBCHNL			0x200000
#घोषणा RRSR_SHORT				0x800000
#घोषणा RRSR_1M					BIT0
#घोषणा RRSR_2M					BIT1
#घोषणा RRSR_5_5M				BIT2
#घोषणा RRSR_11M				BIT3
#घोषणा RRSR_6M					BIT4
#घोषणा RRSR_9M					BIT5
#घोषणा RRSR_12M				BIT6
#घोषणा RRSR_18M				BIT7
#घोषणा RRSR_24M				BIT8
#घोषणा RRSR_36M				BIT9
#घोषणा RRSR_48M				BIT10
#घोषणा RRSR_54M				BIT11
#घोषणा RRSR_MCS0				BIT12
#घोषणा RRSR_MCS1				BIT13
#घोषणा RRSR_MCS2				BIT14
#घोषणा RRSR_MCS3				BIT15
#घोषणा RRSR_MCS4				BIT16
#घोषणा RRSR_MCS5				BIT17
#घोषणा RRSR_MCS6				BIT18
#घोषणा RRSR_MCS7				BIT19
#घोषणा BRSR_AckShortPmb			BIT23
	UFWP			= 0x318,
	RATR0			= 0x320,
#घोषणा	RATR_1M			0x00000001
#घोषणा	RATR_2M			0x00000002
#घोषणा	RATR_55M		0x00000004
#घोषणा	RATR_11M		0x00000008
#घोषणा	RATR_6M			0x00000010
#घोषणा	RATR_9M			0x00000020
#घोषणा	RATR_12M		0x00000040
#घोषणा	RATR_18M		0x00000080
#घोषणा	RATR_24M		0x00000100
#घोषणा	RATR_36M		0x00000200
#घोषणा	RATR_48M		0x00000400
#घोषणा	RATR_54M		0x00000800
#घोषणा	RATR_MCS0		0x00001000
#घोषणा	RATR_MCS1		0x00002000
#घोषणा	RATR_MCS2		0x00004000
#घोषणा	RATR_MCS3		0x00008000
#घोषणा	RATR_MCS4		0x00010000
#घोषणा	RATR_MCS5		0x00020000
#घोषणा	RATR_MCS6		0x00040000
#घोषणा	RATR_MCS7		0x00080000
#घोषणा	RATR_MCS8		0x00100000
#घोषणा	RATR_MCS9		0x00200000
#घोषणा	RATR_MCS10		0x00400000
#घोषणा	RATR_MCS11		0x00800000
#घोषणा	RATR_MCS12		0x01000000
#घोषणा	RATR_MCS13		0x02000000
#घोषणा	RATR_MCS14		0x04000000
#घोषणा	RATR_MCS15		0x08000000
#घोषणा RATE_ALL_CCK		(RATR_1M | RATR_2M | RATR_55M | RATR_11M)
#घोषणा RATE_ALL_OFDM_AG	(RATR_6M | RATR_9M | RATR_12M | RATR_18M | \
				RATR_24M | RATR_36M | RATR_48M | RATR_54M)
#घोषणा RATE_ALL_OFDM_1SS	(RATR_MCS0 | RATR_MCS1 | RATR_MCS2 |	\
				RATR_MCS3 | RATR_MCS4 | RATR_MCS5 |	\
				RATR_MCS6 | RATR_MCS7)
#घोषणा RATE_ALL_OFDM_2SS	(RATR_MCS8 | RATR_MCS9 | RATR_MCS10 |	\
				RATR_MCS11 | RATR_MCS12 | RATR_MCS13 |	\
				RATR_MCS14|RATR_MCS15)


	DRIVER_RSSI		= 0x32c,
	MCS_TXAGC		= 0x340,
	CCK_TXAGC		= 0x348,
	MacBlkCtrl		= 0x403,

पूर्ण
;

#घोषणा GPI 0x108
#घोषणा GPO 0x109
#घोषणा GPE 0x10a

#घोषणा	 HWSET_MAX_SIZE_92S				128

#घोषणा	ANAPAR_FOR_8192PciE				0x17

#पूर्ण_अगर
