<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *	This is part of rtl8187 OpenSource driver.
 *	Copyright (C) Andrea Merello 2004-2005  <andrea.merello@gmail.com>
 *
 *	Parts of this driver are based on the GPL part of the
 *	official Realtek driver.
 *	Parts of this driver are based on the rtl8180 driver skeleton
 *	from Patric Schenke & Andres Salomon.
 *	Parts of this driver are based on the Intel Pro Wireless
 *	2100 GPL driver.
 *
 *	We want to thank the Authors of those projects
 *	and the Ndiswrapper project Authors.
 */

/* Mariusz Matuszek added full रेजिस्टरs definition with Realtek's name */

/* this file contains रेजिस्टर definitions क्रम the rtl8187 MAC controller */
#अगर_अघोषित R8192_HW
#घोषणा R8192_HW

#घोषणा	RTL8187_REQT_READ	0xc0
#घोषणा	RTL8187_REQT_WRITE	0x40
#घोषणा	RTL8187_REQ_GET_REGS	0x05
#घोषणा	RTL8187_REQ_SET_REGS	0x05

#घोषणा MAX_TX_URB 5
#घोषणा MAX_RX_URB 16

#घोषणा R8180_MAX_RETRY 255

#घोषणा RX_URB_SIZE 9100

#घोषणा RTL8190_EEPROM_ID	0x8129
#घोषणा EEPROM_VID		0x02
#घोषणा EEPROM_PID		0x04
#घोषणा EEPROM_NODE_ADDRESS_BYTE_0	0x0C

#घोषणा EEPROM_TX_POWER_DIFF	0x1F
#घोषणा EEPROM_THERMAL_METER	0x20
#घोषणा EEPROM_PW_DIFF		0x21	//0x21
#घोषणा EEPROM_CRYSTAL_CAP	0x22	//0x22

#घोषणा EEPROM_TX_PW_INDEX_CCK	0x23	//0x23
#घोषणा EEPROM_TX_PW_INDEX_OFDM_24G	0x24	//0x24~0x26
#घोषणा EEPROM_TX_PW_INDEX_CCK_V1	0x29	//0x29~0x2B
#घोषणा EEPROM_TX_PW_INDEX_OFDM_24G_V1	0x2C	//0x2C~0x2E
#घोषणा EEPROM_TX_PW_INDEX_VER		0x27	//0x27

#घोषणा EEPROM_DEFAULT_THERNAL_METER		0x7
#घोषणा EEPROM_DEFAULT_PW_DIFF			0x4
#घोषणा EEPROM_DEFAULT_CRYSTAL_CAP		0x5
#घोषणा EEPROM_DEFAULT_TX_POWER		0x1010
#घोषणा EEPROM_CUSTOMER_ID			0x7B	//0x7B:CustomerID
#घोषणा EEPROM_CHANNEL_PLAN			0x16	//0x7C

#घोषणा EEPROM_CID_RUNTOP				0x2
#घोषणा EEPROM_CID_DLINK				0x8

#घोषणा AC_PARAM_TXOP_LIMIT_OFFSET	16
#घोषणा AC_PARAM_ECW_MAX_OFFSET		12
#घोषणा AC_PARAM_ECW_MIN_OFFSET		8
#घोषणा AC_PARAM_AIFS_OFFSET		0

//#पूर्ण_अगर
क्रमागत _RTL8192Usb_HW अणु
	MAC0			= 0x000,
	MAC4			= 0x004,

#घोषणा	BB_GLOBAL_RESET_BIT	0x1
	BB_GLOBAL_RESET		= 0x020, // BasebandGlobal Reset Register
	BSSIDR			= 0x02E, // BSSID Register
	CMDR			= 0x037, // Command रेजिस्टर
#घोषणा CR_RE			0x08
#घोषणा CR_TE			0x04
	SIFS			= 0x03E, // SIFS रेजिस्टर

#घोषणा TCR_MXDMA_2048		7
#घोषणा TCR_LRL_OFFSET		0
#घोषणा TCR_SRL_OFFSET		8
#घोषणा TCR_MXDMA_OFFSET	21
#घोषणा TCR_SAT			BIT(24)	// Enable Rate depedent ack समयout समयr
	RCR			= 0x044, // Receive Configuration Register
#घोषणा MAC_FILTER_MASK (BIT(0) | BIT(1) | BIT(2) | BIT(3) | BIT(5) | \
			 BIT(12) | BIT(18) | BIT(19) | BIT(20) | BIT(21) | \
			 BIT(22) | BIT(23))
#घोषणा RX_FIFO_THRESHOLD_MASK (BIT(13) | BIT(14) | BIT(15))
#घोषणा RX_FIFO_THRESHOLD_SHIFT 13
#घोषणा RX_FIFO_THRESHOLD_NONE 7
#घोषणा MAX_RX_DMA_MASK 	(BIT(8) | BIT(9) | BIT(10))
#घोषणा RCR_MXDMA_OFFSET	8
#घोषणा RCR_FIFO_OFFSET		13
#घोषणा RCR_ONLYERLPKT		BIT(31)			// Early Receiving based on Packet Size.
#घोषणा RCR_CBSSID		BIT(23)			// Accept BSSID match packet
#घोषणा RCR_APWRMGT		BIT(22)			// Accept घातer management packet
#घोषणा RCR_AMF			BIT(20)			// Accept management type frame
#घोषणा RCR_ACF			BIT(19)			// Accept control type frame
#घोषणा RCR_ADF			BIT(18)			// Accept data type frame
#घोषणा RCR_AICV		BIT(12)			// Accept ICV error packet
#घोषणा	RCR_ACRC32		BIT(5)			// Accept CRC32 error packet
#घोषणा	RCR_AB			BIT(3)			// Accept broadcast packet
#घोषणा	RCR_AM			BIT(2)			// Accept multicast packet
#घोषणा	RCR_APM			BIT(1)			// Accept physical match packet
#घोषणा	RCR_AAP			BIT(0)			// Accept all unicast packet
	SLOT_TIME		= 0x049, // Slot Time Register
	ACK_TIMEOUT		= 0x04c, // Ack Timeout Register
	EDCAPARA_BE		= 0x050, // EDCA Parameter of AC BE
	EDCAPARA_BK		= 0x054, // EDCA Parameter of AC BK
	EDCAPARA_VO		= 0x058, // EDCA Parameter of AC VO
	EDCAPARA_VI		= 0x05C, // EDCA Parameter of AC VI
	BCN_TCFG		= 0x062, // Beacon Time Configuration
#घोषणा BCN_TCFG_CW_SHIFT		8
#घोषणा BCN_TCFG_IFS			0
	BCN_INTERVAL		= 0x070, // Beacon Interval (TU)
	ATIMWND			= 0x072, // ATIM Winकरोw Size (TU)
	BCN_DRV_EARLY_INT	= 0x074, // Driver Early Interrupt Time (TU). Time to send पूर्णांकerrupt to notअगरy to change beacon content beक्रमe TBTT
	BCN_DMATIME		= 0x076, // Beacon DMA and ATIM पूर्णांकerrupt समय (US). Indicates the समय beक्रमe TBTT to perक्रमm beacon queue DMA
	BCN_ERR_THRESH		= 0x078, // Beacon Error Threshold
	RWCAM			= 0x0A0, //IN 8190 Data Sheet is called CAMcmd
	WCAMI			= 0x0A4, // Software ग_लिखो CAM input content
	SECR			= 0x0B0, //Security Configuration Register
#घोषणा	SCR_TxUseDK		BIT(0)			//Force Tx Use Default Key
#घोषणा SCR_RxUseDK		BIT(1)			//Force Rx Use Default Key
#घोषणा SCR_TxEncEnable		BIT(2)			//Enable Tx Encryption
#घोषणा SCR_RxDecEnable		BIT(3)			//Enable Rx Decryption
#घोषणा SCR_SKByA2		BIT(4)			//Search kEY BY A2
#घोषणा SCR_NoSKMC		BIT(5)			//No Key Search क्रम Multicast

//----------------------------------------------------------------------------
//       8190 CPU General Register		(offset 0x100, 4 byte)
//----------------------------------------------------------------------------
#घोषणा	CPU_CCK_LOOPBACK	0x00030000
#घोषणा	CPU_GEN_SYSTEM_RESET	0x00000001
#घोषणा	CPU_GEN_FIRMWARE_RESET	0x00000008
#घोषणा	CPU_GEN_BOOT_RDY	0x00000010
#घोषणा	CPU_GEN_FIRM_RDY	0x00000020
#घोषणा	CPU_GEN_PUT_CODE_OK	0x00000080
#घोषणा	CPU_GEN_BB_RST		0x00000100
#घोषणा	CPU_GEN_PWR_STB_CPU	0x00000004
#घोषणा CPU_GEN_NO_LOOPBACK_MSK	0xFFF8FFFF // Set bit18,17,16 to 0. Set bit19
#घोषणा CPU_GEN_NO_LOOPBACK_SET	0x00080000 // Set BIT19 to 1
	CPU_GEN			= 0x100, // CPU Reset Register

	AcmHwCtrl		= 0x171, // ACM Hardware Control Register
//----------------------------------------------------------------------------
////
////       8190 AcmHwCtrl bits                                    (offset 0x171, 1 byte)
////----------------------------------------------------------------------------
//
#घोषणा AcmHw_BeqEn             BIT(1)

	RQPN1			= 0x180, // Reserved Queue Page Number , Vo Vi, Be, Bk
	RQPN2			= 0x184, // Reserved Queue Page Number, HCCA, Cmd, Mgnt, High
	RQPN3			= 0x188, // Reserved Queue Page Number, Bcn, Public,
	QPNR			= 0x1D0, //0x1F0, // Queue Packet Number report per TID

#घोषणा	BW_OPMODE_5G			BIT(1)
#घोषणा	BW_OPMODE_20MHZ			BIT(2)
	BW_OPMODE		= 0x300, // Bandwidth operation mode
	MSR			= 0x303, // Media Status रेजिस्टर
#घोषणा MSR_LINK_MASK      (BIT(0)|BIT(1))
#घोषणा MSR_LINK_MANAGED   2
#घोषणा MSR_LINK_NONE      0
#घोषणा MSR_LINK_SHIFT     0
#घोषणा MSR_LINK_ADHOC     1
#घोषणा MSR_LINK_MASTER    3
	RETRY_LIMIT		= 0x304, // Retry Limit [15:8]-लघु, [7:0]-दीर्घ
#घोषणा RETRY_LIMIT_SHORT_SHIFT 8
#घोषणा RETRY_LIMIT_LONG_SHIFT 0
	RRSR			= 0x310, // Response Rate Set
#घोषणा RRSR_1M						BIT(0)
#घोषणा RRSR_2M						BIT(1)
#घोषणा RRSR_5_5M					BIT(2)
#घोषणा RRSR_11M					BIT(3)
#घोषणा RRSR_6M						BIT(4)
#घोषणा RRSR_9M						BIT(5)
#घोषणा RRSR_12M					BIT(6)
#घोषणा RRSR_18M					BIT(7)
#घोषणा RRSR_24M					BIT(8)
#घोषणा RRSR_36M					BIT(9)
#घोषणा RRSR_48M					BIT(10)
#घोषणा RRSR_54M					BIT(11)
#घोषणा BRSR_AckShortPmb			BIT(23)		// CCK ACK: use Short Preamble or not.
	UFWP			= 0x318,
	RATR0			= 0x320, // Rate Adaptive Table रेजिस्टर1
	DRIVER_RSSI		= 0x32c,					// Driver tell Firmware current RSSI
//----------------------------------------------------------------------------
//       8190 Rate Adaptive Table Register	(offset 0x320, 4 byte)
//----------------------------------------------------------------------------
//CCK
#घोषणा	RATR_1M			0x00000001
#घोषणा	RATR_2M			0x00000002
#घोषणा	RATR_55M		0x00000004
#घोषणा	RATR_11M		0x00000008
//OFDM
#घोषणा	RATR_6M			0x00000010
#घोषणा	RATR_9M			0x00000020
#घोषणा	RATR_12M		0x00000040
#घोषणा	RATR_18M		0x00000080
#घोषणा	RATR_24M		0x00000100
#घोषणा	RATR_36M		0x00000200
#घोषणा	RATR_48M		0x00000400
#घोषणा	RATR_54M		0x00000800
//MCS 1 Spatial Stream
#घोषणा	RATR_MCS0		0x00001000
#घोषणा	RATR_MCS1		0x00002000
#घोषणा	RATR_MCS2		0x00004000
#घोषणा	RATR_MCS3		0x00008000
#घोषणा	RATR_MCS4		0x00010000
#घोषणा	RATR_MCS5		0x00020000
#घोषणा	RATR_MCS6		0x00040000
#घोषणा	RATR_MCS7		0x00080000
//MCS 2 Spatial Stream
#घोषणा	RATR_MCS8		0x00100000
#घोषणा	RATR_MCS9		0x00200000
#घोषणा	RATR_MCS10		0x00400000
#घोषणा	RATR_MCS11		0x00800000
#घोषणा	RATR_MCS12		0x01000000
#घोषणा	RATR_MCS13		0x02000000
#घोषणा	RATR_MCS14		0x04000000
#घोषणा	RATR_MCS15		0x08000000
// ALL CCK Rate
#घोषणा RATE_ALL_CCK		RATR_1M|RATR_2M|RATR_55M|RATR_11M
#घोषणा RATE_ALL_OFDM_AG	RATR_6M|RATR_9M|RATR_12M|RATR_18M|RATR_24M\
							|RATR_36M|RATR_48M|RATR_54M
#घोषणा RATE_ALL_OFDM_1SS	RATR_MCS0|RATR_MCS1|RATR_MCS2|RATR_MCS3 | \
							RATR_MCS4|RATR_MCS5|RATR_MCS6|RATR_MCS7
#घोषणा RATE_ALL_OFDM_2SS	RATR_MCS8|RATR_MCS9	|RATR_MCS10|RATR_MCS11| \
							RATR_MCS12|RATR_MCS13|RATR_MCS14|RATR_MCS15

	EPROM_CMD		= 0xfe58,
#घोषणा Cmd9346CR_9356SEL	BIT(4)
#घोषणा EPROM_CMD_OPERATING_MODE_SHIFT 6
#घोषणा EPROM_CMD_NORMAL 0
#घोषणा EPROM_CMD_PROGRAM 2
#घोषणा EPROM_CS_BIT BIT(3)
#घोषणा EPROM_CK_BIT BIT(2)
#घोषणा EPROM_W_BIT  BIT(1)
#घोषणा EPROM_R_BIT  BIT(0)
पूर्ण;

//----------------------------------------------------------------------------
//       818xB AnaParm & AnaParm2 Register
//----------------------------------------------------------------------------
#घोषणा GPI 0x108
#पूर्ण_अगर
