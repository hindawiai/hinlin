<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* sis900.h Definitions क्रम SiS ethernet controllers including 7014/7016 and 900
 * Copyright 1999 Silicon Integrated System Corporation
 * References:
 *   SiS 7016 Fast Ethernet PCI Bus 10/100 Mbps LAN Controller with OnNow Support,
 *	preliminary Rev. 1.0 Jan. 14, 1998
 *   SiS 900 Fast Ethernet PCI Bus 10/100 Mbps LAN Single Chip with OnNow Support,
 *	preliminary Rev. 1.0 Nov. 10, 1998
 *   SiS 7014 Single Chip 100BASE-TX/10BASE-T Physical Layer Solution,
 *	preliminary Rev. 1.0 Jan. 18, 1998
 *   http://www.sis.com.tw/support/databook.hपंचांग
 */

/*
 * SiS 7016 and SiS 900 ethernet controller रेजिस्टरs
 */

/* The I/O extent, SiS 900 needs 256 bytes of io address */
#घोषणा SIS900_TOTAL_SIZE 0x100

/* Symbolic offsets to रेजिस्टरs. */
क्रमागत sis900_रेजिस्टरs अणु
	cr=0x0,                 //Command Register
	cfg=0x4,                //Configuration Register
	mear=0x8,               //EEPROM Access Register
	ptscr=0xc,              //PCI Test Control Register
	isr=0x10,               //Interrupt Status Register
	imr=0x14,               //Interrupt Mask Register
	ier=0x18,               //Interrupt Enable Register
	epar=0x18,              //Enhanced PHY Access Register
	txdp=0x20,              //Transmit Descriptor Poपूर्णांकer Register
        txcfg=0x24,             //Transmit Configuration Register
        rxdp=0x30,              //Receive Descriptor Poपूर्णांकer Register
        rxcfg=0x34,             //Receive Configuration Register
        flctrl=0x38,            //Flow Control Register
        rxlen=0x3c,             //Receive Packet Length Register
        rfcr=0x48,              //Receive Filter Control Register
        rfdr=0x4C,              //Receive Filter Data Register
        pmctrl=0xB0,            //Power Management Control Register
        pmer=0xB4               //Power Management Wake-up Event Register
पूर्ण;

/* Symbolic names क्रम bits in various रेजिस्टरs */
क्रमागत sis900_command_रेजिस्टर_bits अणु
	RELOAD  = 0x00000400, ACCESSMODE = 0x00000200,/* ET */
	RESET   = 0x00000100, SWI = 0x00000080, RxRESET = 0x00000020,
	TxRESET = 0x00000010, RxDIS = 0x00000008, RxENA = 0x00000004,
	TxDIS   = 0x00000002, TxENA = 0x00000001
पूर्ण;

क्रमागत sis900_configuration_रेजिस्टर_bits अणु
	DESCRFMT = 0x00000100 /* 7016 specअगरic */, REQALG = 0x00000080,
	SB    = 0x00000040, POW = 0x00000020, EXD = 0x00000010,
	PESEL = 0x00000008, LPM = 0x00000004, BEM = 0x00000001,
	/* 635 & 900B Specअगरic */
	RND_CNT = 0x00000400, FAIR_BACKOFF = 0x00000200,
	EDB_MASTER_EN = 0x00002000
पूर्ण;

क्रमागत sis900_eeprom_access_रेजिस्टर_bits अणु
	MDC  = 0x00000040, MDसूची = 0x00000020, MDIO = 0x00000010, /* 7016 specअगरic */
	EECS = 0x00000008, EECLK = 0x00000004, EEDO = 0x00000002,
	EEDI = 0x00000001
पूर्ण;

क्रमागत sis900_पूर्णांकerrupt_रेजिस्टर_bits अणु
	WKEVT  = 0x10000000, TxPAUSEEND = 0x08000000, TxPAUSE = 0x04000000,
	TxRCMP = 0x02000000, RxRCMP = 0x01000000, DPERR = 0x00800000,
	SSERR  = 0x00400000, RMABT  = 0x00200000, RTABT = 0x00100000,
	RxSOVR = 0x00010000, HIBERR = 0x00008000, SWINT = 0x00001000,
	MIBINT = 0x00000800, TxURN  = 0x00000400, TxIDLE  = 0x00000200,
	TxERR  = 0x00000100, TxDESC = 0x00000080, TxOK  = 0x00000040,
	RxORN  = 0x00000020, RxIDLE = 0x00000010, RxEARLY = 0x00000008,
	RxERR  = 0x00000004, RxDESC = 0x00000002, RxOK  = 0x00000001
पूर्ण;

क्रमागत sis900_पूर्णांकerrupt_enable_रेजिस्टर_bits अणु
	IE = 0x00000001
पूर्ण;

/* maximum dma burst क्रम transmission and receive */
#घोषणा MAX_DMA_RANGE	7	/* actually 0 means MAXIMUM !! */
#घोषणा TxMXDMA_shअगरt   	20
#घोषणा RxMXDMA_shअगरt    20

क्रमागत sis900_tx_rx_dmaअणु
	DMA_BURST_512 = 0,	DMA_BURST_64 = 5
पूर्ण;

/* transmit FIFO thresholds */
#घोषणा TX_FILL_THRESH   16	/* 1/4 FIFO size */
#घोषणा TxFILLT_shअगरt   	8
#घोषणा TxDRNT_shअगरt    	0
#घोषणा TxDRNT_100      	48	/* 3/4 FIFO size */
#घोषणा TxDRNT_10		16 	/* 1/2 FIFO size */

क्रमागत sis900_transmit_config_रेजिस्टर_bits अणु
	TxCSI = 0x80000000, TxHBI = 0x40000000, TxMLB = 0x20000000,
	TxATP = 0x10000000, TxIFG = 0x0C000000, TxFILLT = 0x00003F00,
	TxDRNT = 0x0000003F
पूर्ण;

/* recevie FIFO thresholds */
#घोषणा RxDRNT_shअगरt     1
#घोषणा RxDRNT_100	16	/* 1/2 FIFO size */
#घोषणा RxDRNT_10		24 	/* 3/4 FIFO size */

क्रमागत sis900_reveive_config_रेजिस्टर_bits अणु
	RxAEP  = 0x80000000, RxARP = 0x40000000, RxATX = 0x10000000,
	RxAJAB = 0x08000000, RxDRNT = 0x0000007F
पूर्ण;

#घोषणा RFAA_shअगरt      28
#घोषणा RFADDR_shअगरt    16

क्रमागत sis900_receive_filter_control_रेजिस्टर_bits अणु
	RFEN  = 0x80000000, RFAAB = 0x40000000, RFAAM = 0x20000000,
	RFAAP = 0x10000000, RFPromiscuous = (RFAAB|RFAAM|RFAAP)
पूर्ण;

क्रमागत sis900_reveive_filter_data_mask अणु
	RFDAT =  0x0000FFFF
पूर्ण;

/* EEPROM Addresses */
क्रमागत sis900_eeprom_address अणु
	EEPROMSignature = 0x00, EEPROMVenकरोrID = 0x02, EEPROMDeviceID = 0x03,
	EEPROMMACAddr   = 0x08, EEPROMChecksum = 0x0b
पूर्ण;

/* The EEPROM commands include the alway-set leading bit. Refer to NM93Cxx datasheet */
क्रमागत sis900_eeprom_command अणु
	EEपढ़ो     = 0x0180, EEग_लिखो    = 0x0140, EEerase = 0x01C0,
	EEग_लिखोEnable = 0x0130, EEग_लिखोDisable = 0x0100,
	EEeraseAll = 0x0120, EEग_लिखोAll = 0x0110,
	EEaddrMask = 0x013F, EEcmdShअगरt = 16
पूर्ण;

/* For SiS962 or SiS963, request the eeprom software access */
क्रमागत sis96x_eeprom_command अणु
	EEREQ = 0x00000400, EEDONE = 0x00000200, EEGNT = 0x00000100
पूर्ण;

/* PCI Registers */
क्रमागत sis900_pci_रेजिस्टरs अणु
	CFGPMC 	 = 0x40,
	CFGPMCSR = 0x44
पूर्ण;

/* Power management capabilities bits */
क्रमागत sis900_cfgpmc_रेजिस्टर_bits अणु
	PMVER	= 0x00070000,
	DSI	= 0x00100000,
	PMESP	= 0xf8000000
पूर्ण;

क्रमागत sis900_pmesp_bits अणु
	PME_D0 = 0x1,
	PME_D1 = 0x2,
	PME_D2 = 0x4,
	PME_D3H = 0x8,
	PME_D3C = 0x10
पूर्ण;

/* Power management control/status bits */
क्रमागत sis900_cfgpmcsr_रेजिस्टर_bits अणु
	PMESTS = 0x00004000,
	PME_EN = 0x00000100, // Power management enable
	PWR_STA = 0x00000003 // Current घातer state
पूर्ण;

/* Wake-on-LAN support. */
क्रमागत sis900_घातer_management_control_रेजिस्टर_bits अणु
	LINKLOSS  = 0x00000001,
	LINKON    = 0x00000002,
	MAGICPKT  = 0x00000400,
	ALGORITHM = 0x00000800,
	FRM1EN    = 0x00100000,
	FRM2EN    = 0x00200000,
	FRM3EN    = 0x00400000,
	FRM1ACS   = 0x01000000,
	FRM2ACS   = 0x02000000,
	FRM3ACS   = 0x04000000,
	WAKEALL   = 0x40000000,
	GATECLK   = 0x80000000
पूर्ण;

/* Management Data I/O (mdio) frame */
#घोषणा MIIपढ़ो         0x6000
#घोषणा MIIग_लिखो        0x5002
#घोषणा MIIpmdShअगरt     7
#घोषणा MIIregShअगरt     2
#घोषणा MIIcmdLen       16
#घोषणा MIIcmdShअगरt     16

/* Buffer Descriptor Status*/
क्रमागत sis900_buffer_status अणु
	OWN    = 0x80000000, MORE   = 0x40000000, INTR = 0x20000000,
	SUPCRC = 0x10000000, INCCRC = 0x10000000,
	OK     = 0x08000000, DSIZE  = 0x00000FFF
पूर्ण;
/* Status क्रम TX Buffers */
क्रमागत sis900_tx_buffer_status अणु
	ABORT   = 0x04000000, UNDERRUN = 0x02000000, NOCARRIER = 0x01000000,
	DEFERD  = 0x00800000, EXCDEFER = 0x00400000, OWCOLL    = 0x00200000,
	EXCCOLL = 0x00100000, COLCNT   = 0x000F0000
पूर्ण;

क्रमागत sis900_rx_buffer_status अणु
	OVERRUN = 0x02000000, DEST = 0x00800000,     BCAST = 0x01800000,
	MCAST   = 0x01000000, UNIMATCH = 0x00800000, TOOLONG = 0x00400000,
	RUNT    = 0x00200000, RXISERR  = 0x00100000, CRCERR  = 0x00080000,
	FAERR   = 0x00040000, LOOPBK   = 0x00020000, RXCOL   = 0x00010000
पूर्ण;

/* MII रेजिस्टर offsets */
क्रमागत mii_रेजिस्टरs अणु
	MII_CONTROL = 0x0000, MII_STATUS = 0x0001, MII_PHY_ID0 = 0x0002,
	MII_PHY_ID1 = 0x0003, MII_ANADV  = 0x0004, MII_ANLPAR  = 0x0005,
	MII_ANEXT   = 0x0006
पूर्ण;

/* mii रेजिस्टरs specअगरic to SiS 900 */
क्रमागत sis_mii_रेजिस्टरs अणु
	MII_CONFIG1 = 0x0010, MII_CONFIG2 = 0x0011, MII_STSOUT = 0x0012,
	MII_MASK    = 0x0013, MII_RESV    = 0x0014
पूर्ण;

/* mii रेजिस्टरs specअगरic to ICS 1893 */
क्रमागत ics_mii_रेजिस्टरs अणु
	MII_EXTCTRL  = 0x0010, MII_QPDSTS = 0x0011, MII_10BTOP = 0x0012,
	MII_EXTCTRL2 = 0x0013
पूर्ण;

/* mii रेजिस्टरs specअगरic to AMD 79C901 */
क्रमागत amd_mii_रेजिस्टरs अणु
	MII_STATUS_SUMMARY = 0x0018
पूर्ण;

/* MII Control रेजिस्टर bit definitions. */
क्रमागत mii_control_रेजिस्टर_bits अणु
	MII_CNTL_FDX     = 0x0100, MII_CNTL_RST_AUTO = 0x0200,
	MII_CNTL_ISOLATE = 0x0400, MII_CNTL_PWRDWN   = 0x0800,
	MII_CNTL_AUTO    = 0x1000, MII_CNTL_SPEED    = 0x2000,
	MII_CNTL_LPBK    = 0x4000, MII_CNTL_RESET    = 0x8000
पूर्ण;

/* MII Status रेजिस्टर bit  */
क्रमागत mii_status_रेजिस्टर_bits अणु
	MII_STAT_EXT    = 0x0001, MII_STAT_JAB        = 0x0002,
	MII_STAT_LINK   = 0x0004, MII_STAT_CAN_AUTO   = 0x0008,
	MII_STAT_FAULT  = 0x0010, MII_STAT_AUTO_DONE  = 0x0020,
	MII_STAT_CAN_T  = 0x0800, MII_STAT_CAN_T_FDX  = 0x1000,
	MII_STAT_CAN_TX = 0x2000, MII_STAT_CAN_TX_FDX = 0x4000,
	MII_STAT_CAN_T4 = 0x8000
पूर्ण;

#घोषणा		MII_ID1_OUI_LO		0xFC00	/* low bits of OUI mask */
#घोषणा		MII_ID1_MODEL		0x03F0	/* model number */
#घोषणा		MII_ID1_REV		0x000F	/* model number */

/* MII NWAY Register Bits ...
   valid क्रम the ANAR (Auto-Negotiation Advertisement) and
   ANLPAR (Auto-Negotiation Link Partner) रेजिस्टरs */
क्रमागत mii_nway_रेजिस्टर_bits अणु
	MII_NWAY_NODE_SEL = 0x001f, MII_NWAY_CSMA_CD = 0x0001,
	MII_NWAY_T	  = 0x0020, MII_NWAY_T_FDX   = 0x0040,
	MII_NWAY_TX       = 0x0080, MII_NWAY_TX_FDX  = 0x0100,
	MII_NWAY_T4       = 0x0200, MII_NWAY_PAUSE   = 0x0400,
	MII_NWAY_RF       = 0x2000, MII_NWAY_ACK     = 0x4000,
	MII_NWAY_NP       = 0x8000
पूर्ण;

क्रमागत mii_stsout_रेजिस्टर_bits अणु
	MII_STSOUT_LINK_FAIL = 0x4000,
	MII_STSOUT_SPD       = 0x0080, MII_STSOUT_DPLX = 0x0040
पूर्ण;

क्रमागत mii_stsics_रेजिस्टर_bits अणु
	MII_STSICS_SPD  = 0x8000, MII_STSICS_DPLX = 0x4000,
	MII_STSICS_LINKSTS = 0x0001
पूर्ण;

क्रमागत mii_stssum_रेजिस्टर_bits अणु
	MII_STSSUM_LINK = 0x0008, MII_STSSUM_DPLX = 0x0004,
	MII_STSSUM_AUTO = 0x0002, MII_STSSUM_SPD  = 0x0001
पूर्ण;

क्रमागत sis900_revision_id अणु
	SIS630A_900_REV = 0x80,		SIS630E_900_REV = 0x81,
	SIS630S_900_REV = 0x82,		SIS630EA1_900_REV = 0x83,
	SIS630ET_900_REV = 0x84,	SIS635A_900_REV = 0x90,
	SIS96x_900_REV = 0X91,		SIS900B_900_REV = 0x03
पूर्ण;

क्रमागत sis630_revision_id अणु
	SIS630A0    = 0x00, SIS630A1      = 0x01,
	SIS630B0    = 0x10, SIS630B1      = 0x11
पूर्ण;

#घोषणा FDX_CAPABLE_DUPLEX_UNKNOWN      0
#घोषणा FDX_CAPABLE_HALF_SELECTED       1
#घोषणा FDX_CAPABLE_FULL_SELECTED       2

#घोषणा HW_SPEED_UNCONFIG		0
#घोषणा HW_SPEED_HOME		1
#घोषणा HW_SPEED_10_MBPS        	10
#घोषणा HW_SPEED_100_MBPS       	100
#घोषणा HW_SPEED_DEFAULT        	(HW_SPEED_100_MBPS)

#घोषणा CRC_SIZE                4
#घोषणा MAC_HEADER_SIZE         14

#अगर IS_ENABLED(CONFIG_VLAN_8021Q)
#घोषणा MAX_FRAME_SIZE  (1518 + 4)
#अन्यथा
#घोषणा MAX_FRAME_SIZE  1518
#पूर्ण_अगर /* CONFIG_VLAN_802_1Q */

#घोषणा TX_BUF_SIZE     (MAX_FRAME_SIZE+18)
#घोषणा RX_BUF_SIZE     (MAX_FRAME_SIZE+18)

#घोषणा NUM_TX_DESC     16      	/* Number of Tx descriptor रेजिस्टरs. */
#घोषणा NUM_RX_DESC     16       	/* Number of Rx descriptor रेजिस्टरs. */
#घोषणा TX_TOTAL_SIZE	NUM_TX_DESC*माप(BufferDesc)
#घोषणा RX_TOTAL_SIZE	NUM_RX_DESC*माप(BufferDesc)

/* PCI stuff, should be move to pci.h */
#घोषणा SIS630_VENDOR_ID        0x1039
#घोषणा SIS630_DEVICE_ID        0x0630
