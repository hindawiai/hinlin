<शैली गुरु>
/*  Copyright, 1988-1992, Russell Nelson, Crynwr Software

   This program is मुक्त software; you can redistribute it and/or modअगरy
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, version 1.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License क्रम more details.

   You should have received a copy of the GNU General Public License
   aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
   */


#घोषणा PP_ChipID 0x0000	/* offset   0h -> Corp -ID              */
				/* offset   2h -> Model/Product Number  */
				/* offset   3h -> Chip Revision Number  */

#घोषणा PP_ISAIOB 0x0020	/*  IO base address */
#घोषणा PP_CS8900_ISAINT 0x0022	/*  ISA पूर्णांकerrupt select */
#घोषणा PP_CS8920_ISAINT 0x0370	/*  ISA पूर्णांकerrupt select */
#घोषणा PP_CS8900_ISADMA 0x0024	/*  ISA Rec DMA channel */
#घोषणा PP_CS8920_ISADMA 0x0374	/*  ISA Rec DMA channel */
#घोषणा PP_ISASOF 0x0026	/*  ISA DMA offset */
#घोषणा PP_DmaFrameCnt 0x0028	/*  ISA DMA Frame count */
#घोषणा PP_DmaByteCnt 0x002A	/*  ISA DMA Byte count */
#घोषणा PP_CS8900_ISAMemB 0x002C	/*  Memory base */
#घोषणा PP_CS8920_ISAMemB 0x0348 /*  */

#घोषणा PP_ISABootBase 0x0030	/*  Boot Prom base  */
#घोषणा PP_ISABootMask 0x0034	/*  Boot Prom Mask */

/* EEPROM data and command रेजिस्टरs */
#घोषणा PP_EECMD 0x0040		/*  NVR Interface Command रेजिस्टर */
#घोषणा PP_EEData 0x0042	/*  NVR Interface Data Register */
#घोषणा PP_DebugReg 0x0044	/*  Debug Register */

#घोषणा PP_RxCFG 0x0102		/*  Rx Bus config */
#घोषणा PP_RxCTL 0x0104		/*  Receive Control Register */
#घोषणा PP_TxCFG 0x0106		/*  Transmit Config Register */
#घोषणा PP_TxCMD 0x0108		/*  Transmit Command Register */
#घोषणा PP_BufCFG 0x010A	/*  Bus configuration Register */
#घोषणा PP_LineCTL 0x0112	/*  Line Config Register */
#घोषणा PP_SelfCTL 0x0114	/*  Self Command Register */
#घोषणा PP_BusCTL 0x0116	/*  ISA bus control Register */
#घोषणा PP_TestCTL 0x0118	/*  Test Register */
#घोषणा PP_AutoNegCTL 0x011C	/*  Auto Negotiation Ctrl */

#घोषणा PP_ISQ 0x0120		/*  Interrupt Status */
#घोषणा PP_RxEvent 0x0124	/*  Rx Event Register */
#घोषणा PP_TxEvent 0x0128	/*  Tx Event Register */
#घोषणा PP_BufEvent 0x012C	/*  Bus Event Register */
#घोषणा PP_RxMiss 0x0130	/*  Receive Miss Count */
#घोषणा PP_TxCol 0x0132		/*  Transmit Collision Count */
#घोषणा PP_LineST 0x0134	/*  Line State Register */
#घोषणा PP_SelfST 0x0136	/*  Self State रेजिस्टर */
#घोषणा PP_BusST 0x0138		/*  Bus Status */
#घोषणा PP_TDR 0x013C		/*  Time Doमुख्य Reflectometry */
#घोषणा PP_AutoNegST 0x013E	/*  Auto Neg Status */
#घोषणा PP_TxCommand 0x0144	/*  Tx Command */
#घोषणा PP_TxLength 0x0146	/*  Tx Length */
#घोषणा PP_LAF 0x0150		/*  Hash Table */
#घोषणा PP_IA 0x0158		/*  Physical Address Register */

#घोषणा PP_RxStatus 0x0400	/*  Receive start of frame */
#घोषणा PP_RxLength 0x0402	/*  Receive Length of frame */
#घोषणा PP_RxFrame 0x0404	/*  Receive frame poपूर्णांकer */
#घोषणा PP_TxFrame 0x0A00	/*  Transmit frame poपूर्णांकer */

/*  Primary I/O Base Address. If no I/O base is supplied by the user, then this */
/*  can be used as the शेष I/O base to access the PacketPage Area. */
#घोषणा DEFAULTIOBASE 0x0300
#घोषणा FIRST_IO 0x020C		/*  First I/O port to check */
#घोषणा LAST_IO 0x037C		/*  Last I/O port to check (+10h) */
#घोषणा ADD_MASK 0x3000		/*  Mask it use of the ADD_PORT रेजिस्टर */
#घोषणा ADD_SIG 0x3000		/*  Expected ID signature */

/* On Macs, we only need use the ISA I/O stuff until we करो MEMORY_ON */
#अगर_घोषित CONFIG_MAC
#घोषणा LCSLOTBASE 0xfee00000
#घोषणा MMIOBASE 0x40000
#पूर्ण_अगर

#घोषणा CHIP_EISA_ID_SIG 0x630E   /*  Product ID Code क्रम Crystal Chip (CS8900 spec 4.3) */
#घोषणा CHIP_EISA_ID_SIG_STR "0x630E"

#अगर_घोषित IBMEIPKT
#घोषणा EISA_ID_SIG 0x4D24	/*  IBM */
#घोषणा PART_NO_SIG 0x1010	/*  IBM */
#घोषणा MONGOOSE_BIT 0x0000	/*  IBM */
#अन्यथा
#घोषणा EISA_ID_SIG 0x630E	/*  PnP Venकरोr ID (same as chip id क्रम Crystal board) */
#घोषणा PART_NO_SIG 0x4000	/*  ID code CS8920 board (PnP Venकरोr Product code) */
#घोषणा MONGOOSE_BIT 0x2000	/*  PART_NO_SIG + MONGOOSE_BUT => ID of mongoose */
#पूर्ण_अगर

#घोषणा PRODUCT_ID_ADD 0x0002   /*  Address of product ID */

/*  Mask to find out the types of  रेजिस्टरs */
#घोषणा REG_TYPE_MASK 0x001F

/*  Eeprom Commands */
#घोषणा ERSE_WR_ENBL 0x00F0
#घोषणा ERSE_WR_DISABLE 0x0000

/*  Defines Control/Config रेजिस्टर quपूर्णांकuplet numbers */
#घोषणा RX_BUF_CFG 0x0003
#घोषणा RX_CONTROL 0x0005
#घोषणा TX_CFG 0x0007
#घोषणा TX_COMMAND 0x0009
#घोषणा BUF_CFG 0x000B
#घोषणा LINE_CONTROL 0x0013
#घोषणा SELF_CONTROL 0x0015
#घोषणा BUS_CONTROL 0x0017
#घोषणा TEST_CONTROL 0x0019

/*  Defines Status/Count रेजिस्टरs quपूर्णांकuplet numbers */
#घोषणा RX_EVENT 0x0004
#घोषणा TX_EVENT 0x0008
#घोषणा BUF_EVENT 0x000C
#घोषणा RX_MISS_COUNT 0x0010
#घोषणा TX_COL_COUNT 0x0012
#घोषणा LINE_STATUS 0x0014
#घोषणा SELF_STATUS 0x0016
#घोषणा BUS_STATUS 0x0018
#घोषणा TDR 0x001C

/* PP_RxCFG - Receive  Configuration and Interrupt Mask bit definition -  Read/ग_लिखो */
#घोषणा SKIP_1 0x0040
#घोषणा RX_STREAM_ENBL 0x0080
#घोषणा RX_OK_ENBL 0x0100
#घोषणा RX_DMA_ONLY 0x0200
#घोषणा AUTO_RX_DMA 0x0400
#घोषणा BUFFER_CRC 0x0800
#घोषणा RX_CRC_ERROR_ENBL 0x1000
#घोषणा RX_RUNT_ENBL 0x2000
#घोषणा RX_EXTRA_DATA_ENBL 0x4000

/* PP_RxCTL - Receive Control bit definition - Read/ग_लिखो */
#घोषणा RX_IA_HASH_ACCEPT 0x0040
#घोषणा RX_PROM_ACCEPT 0x0080
#घोषणा RX_OK_ACCEPT 0x0100
#घोषणा RX_MULTCAST_ACCEPT 0x0200
#घोषणा RX_IA_ACCEPT 0x0400
#घोषणा RX_BROADCAST_ACCEPT 0x0800
#घोषणा RX_BAD_CRC_ACCEPT 0x1000
#घोषणा RX_RUNT_ACCEPT 0x2000
#घोषणा RX_EXTRA_DATA_ACCEPT 0x4000
#घोषणा RX_ALL_ACCEPT (RX_PROM_ACCEPT|RX_BAD_CRC_ACCEPT|RX_RUNT_ACCEPT|RX_EXTRA_DATA_ACCEPT)
/*  Default receive mode - inभागidually addressed, broadcast, and error मुक्त */
#घोषणा DEF_RX_ACCEPT (RX_IA_ACCEPT | RX_BROADCAST_ACCEPT | RX_OK_ACCEPT)

/* PP_TxCFG - Transmit Configuration Interrupt Mask bit definition - Read/ग_लिखो */
#घोषणा TX_LOST_CRS_ENBL 0x0040
#घोषणा TX_SQE_ERROR_ENBL 0x0080
#घोषणा TX_OK_ENBL 0x0100
#घोषणा TX_LATE_COL_ENBL 0x0200
#घोषणा TX_JBR_ENBL 0x0400
#घोषणा TX_ANY_COL_ENBL 0x0800
#घोषणा TX_16_COL_ENBL 0x8000

/* PP_TxCMD - Transmit Command bit definition - Read-only */
#घोषणा TX_START_4_BYTES 0x0000
#घोषणा TX_START_64_BYTES 0x0040
#घोषणा TX_START_128_BYTES 0x0080
#घोषणा TX_START_ALL_BYTES 0x00C0
#घोषणा TX_FORCE 0x0100
#घोषणा TX_ONE_COL 0x0200
#घोषणा TX_TWO_PART_DEFF_DISABLE 0x0400
#घोषणा TX_NO_CRC 0x1000
#घोषणा TX_RUNT 0x2000

/* PP_BufCFG - Buffer Configuration Interrupt Mask bit definition - Read/ग_लिखो */
#घोषणा GENERATE_SW_INTERRUPT 0x0040
#घोषणा RX_DMA_ENBL 0x0080
#घोषणा READY_FOR_TX_ENBL 0x0100
#घोषणा TX_UNDERRUN_ENBL 0x0200
#घोषणा RX_MISS_ENBL 0x0400
#घोषणा RX_128_BYTE_ENBL 0x0800
#घोषणा TX_COL_COUNT_OVRFLOW_ENBL 0x1000
#घोषणा RX_MISS_COUNT_OVRFLOW_ENBL 0x2000
#घोषणा RX_DEST_MATCH_ENBL 0x8000

/* PP_LineCTL - Line Control bit definition - Read/ग_लिखो */
#घोषणा SERIAL_RX_ON 0x0040
#घोषणा SERIAL_TX_ON 0x0080
#घोषणा AUI_ONLY 0x0100
#घोषणा AUTO_AUI_10BASET 0x0200
#घोषणा MODIFIED_BACKOFF 0x0800
#घोषणा NO_AUTO_POLARITY 0x1000
#घोषणा TWO_PART_DEFDIS 0x2000
#घोषणा LOW_RX_SQUELCH 0x4000

/* PP_SelfCTL - Software Self Control bit definition - Read/ग_लिखो */
#घोषणा POWER_ON_RESET 0x0040
#घोषणा SW_STOP 0x0100
#घोषणा SLEEP_ON 0x0200
#घोषणा AUTO_WAKEUP 0x0400
#घोषणा HCB0_ENBL 0x1000
#घोषणा HCB1_ENBL 0x2000
#घोषणा HCB0 0x4000
#घोषणा HCB1 0x8000

/* PP_BusCTL - ISA Bus Control bit definition - Read/ग_लिखो */
#घोषणा RESET_RX_DMA 0x0040
#घोषणा MEMORY_ON 0x0400
#घोषणा DMA_BURST_MODE 0x0800
#घोषणा IO_CHANNEL_READY_ON 0x1000
#घोषणा RX_DMA_SIZE_64K 0x2000
#घोषणा ENABLE_IRQ 0x8000

/* PP_TestCTL - Test Control bit definition - Read/ग_लिखो */
#घोषणा LINK_OFF 0x0080
#घोषणा ENDEC_LOOPBACK 0x0200
#घोषणा AUI_LOOPBACK 0x0400
#घोषणा BACKOFF_OFF 0x0800
#घोषणा FDX_8900 0x4000
#घोषणा FAST_TEST 0x8000

/* PP_RxEvent - Receive Event Bit definition - Read-only */
#घोषणा RX_IA_HASHED 0x0040
#घोषणा RX_DRIBBLE 0x0080
#घोषणा RX_OK 0x0100
#घोषणा RX_HASHED 0x0200
#घोषणा RX_IA 0x0400
#घोषणा RX_BROADCAST 0x0800
#घोषणा RX_CRC_ERROR 0x1000
#घोषणा RX_RUNT 0x2000
#घोषणा RX_EXTRA_DATA 0x4000

#घोषणा HASH_INDEX_MASK 0x0FC00

/* PP_TxEvent - Transmit Event Bit definition - Read-only */
#घोषणा TX_LOST_CRS 0x0040
#घोषणा TX_SQE_ERROR 0x0080
#घोषणा TX_OK 0x0100
#घोषणा TX_LATE_COL 0x0200
#घोषणा TX_JBR 0x0400
#घोषणा TX_16_COL 0x8000
#घोषणा TX_SEND_OK_BITS (TX_OK|TX_LOST_CRS)
#घोषणा TX_COL_COUNT_MASK 0x7800

/* PP_BufEvent - Buffer Event Bit definition - Read-only */
#घोषणा SW_INTERRUPT 0x0040
#घोषणा RX_DMA 0x0080
#घोषणा READY_FOR_TX 0x0100
#घोषणा TX_UNDERRUN 0x0200
#घोषणा RX_MISS 0x0400
#घोषणा RX_128_BYTE 0x0800
#घोषणा TX_COL_OVRFLW 0x1000
#घोषणा RX_MISS_OVRFLW 0x2000
#घोषणा RX_DEST_MATCH 0x8000

/* PP_LineST - Ethernet Line Status bit definition - Read-only */
#घोषणा LINK_OK 0x0080
#घोषणा AUI_ON 0x0100
#घोषणा TENBASET_ON 0x0200
#घोषणा POLARITY_OK 0x1000
#घोषणा CRS_OK 0x4000

/* PP_SelfST - Chip Software Status bit definition */
#घोषणा ACTIVE_33V 0x0040
#घोषणा INIT_DONE 0x0080
#घोषणा SI_BUSY 0x0100
#घोषणा EEPROM_PRESENT 0x0200
#घोषणा EEPROM_OK 0x0400
#घोषणा EL_PRESENT 0x0800
#घोषणा EE_SIZE_64 0x1000

/* PP_BusST - ISA Bus Status bit definition */
#घोषणा TX_BID_ERROR 0x0080
#घोषणा READY_FOR_TX_NOW 0x0100

/* PP_AutoNegCTL - Auto Negotiation Control bit definition */
#घोषणा RE_NEG_NOW 0x0040
#घोषणा ALLOW_FDX 0x0080
#घोषणा AUTO_NEG_ENABLE 0x0100
#घोषणा NLP_ENABLE 0x0200
#घोषणा FORCE_FDX 0x8000
#घोषणा AUTO_NEG_BITS (FORCE_FDX|NLP_ENABLE|AUTO_NEG_ENABLE)
#घोषणा AUTO_NEG_MASK (FORCE_FDX|NLP_ENABLE|AUTO_NEG_ENABLE|ALLOW_FDX|RE_NEG_NOW)

/* PP_AutoNegST - Auto Negotiation Status bit definition */
#घोषणा AUTO_NEG_BUSY 0x0080
#घोषणा FLP_LINK 0x0100
#घोषणा FLP_LINK_GOOD 0x0800
#घोषणा LINK_FAULT 0x1000
#घोषणा HDX_ACTIVE 0x4000
#घोषणा FDX_ACTIVE 0x8000

/*  The following block defines the ISQ event types */
#घोषणा ISQ_RECEIVER_EVENT 0x04
#घोषणा ISQ_TRANSMITTER_EVENT 0x08
#घोषणा ISQ_BUFFER_EVENT 0x0c
#घोषणा ISQ_RX_MISS_EVENT 0x10
#घोषणा ISQ_TX_COL_EVENT 0x12

#घोषणा ISQ_EVENT_MASK 0x003F   /*  ISQ mask to find out type of event */
#घोषणा ISQ_HIST 16		/*  small history buffer */
#घोषणा AUTOINCREMENT 0x8000	/*  Bit mask to set bit-15 क्रम स्वतःincrement */

#घोषणा TXRXबफ_मानE 0x0600
#घोषणा RXDMAबफ_मानE 0x8000
#घोषणा RXDMASIZE 0x4000
#घोषणा TXRX_LENGTH_MASK 0x07FF

/*  rx options bits */
#घोषणा RCV_WITH_RXON	1       /*  Set SerRx ON */
#घोषणा RCV_COUNTS	2       /*  Use Framecnt1 */
#घोषणा RCV_PONG	4       /*  Pong respondent */
#घोषणा RCV_DONG	8       /*  Dong operation */
#घोषणा RCV_POLLING	0x10	/*  Poll RxEvent */
#घोषणा RCV_ISQ		0x20	/*  Use ISQ, पूर्णांक */
#घोषणा RCV_AUTO_DMA	0x100	/*  Set AutoRxDMAE */
#घोषणा RCV_DMA		0x200	/*  Set RxDMA only */
#घोषणा RCV_DMA_ALL	0x400	/*  Copy all DMA'ed */
#घोषणा RCV_FIXED_DATA	0x800	/*  Every frame same */
#घोषणा RCV_IO		0x1000	/*  Use ISA IO only */
#घोषणा RCV_MEMORY	0x2000	/*  Use ISA Memory */

#घोषणा RAM_SIZE	0x1000       /*  The card has 4k bytes or RAM */
#घोषणा PKT_START PP_TxFrame  /*  Start of packet RAM */

#घोषणा RX_FRAME_PORT	0x0000
#घोषणा TX_FRAME_PORT RX_FRAME_PORT
#घोषणा TX_CMD_PORT	0x0004
#घोषणा TX_NOW		0x0000       /*  Tx packet after   5 bytes copied */
#घोषणा TX_AFTER_381	0x0040       /*  Tx packet after 381 bytes copied */
#घोषणा TX_AFTER_ALL	0x00c0       /*  Tx packet after all bytes copied */
#घोषणा TX_LEN_PORT	0x0006
#घोषणा ISQ_PORT	0x0008
#घोषणा ADD_PORT	0x000A
#घोषणा DATA_PORT	0x000C

#घोषणा EEPROM_WRITE_EN		0x00F0
#घोषणा EEPROM_WRITE_DIS	0x0000
#घोषणा EEPROM_WRITE_CMD	0x0100
#घोषणा EEPROM_READ_CMD		0x0200

/*  Receive Header */
/*  Description of header of each packet in receive area of memory */
#घोषणा RBUF_EVENT_LOW	0   /*  Low byte of RxEvent - status of received frame */
#घोषणा RBUF_EVENT_HIGH	1   /*  High byte of RxEvent - status of received frame */
#घोषणा RBUF_LEN_LOW	2   /*  Length of received data - low byte */
#घोषणा RBUF_LEN_HI	3   /*  Length of received data - high byte */
#घोषणा RBUF_HEAD_LEN	4   /*  Length of this header */

#घोषणा CHIP_READ 0x1   /*  Used to mark state of the repins code (chip or dma) */
#घोषणा DMA_READ 0x2   /*  Used to mark state of the repins code (chip or dma) */

/*  क्रम bios scan */
/*  */
#अगर_घोषित CSDEBUG
/*  use these values क्रम debugging bios scan */
#घोषणा BIOS_START_SEG 0x00000
#घोषणा BIOS_OFFSET_INC 0x0010
#अन्यथा
#घोषणा BIOS_START_SEG 0x0c000
#घोषणा BIOS_OFFSET_INC 0x0200
#पूर्ण_अगर

#घोषणा BIOS_LAST_OFFSET 0x0fc00

/*  Byte offsets पूर्णांकo the EEPROM configuration buffer */
#घोषणा ISA_CNF_OFFSET 0x6
#घोषणा TX_CTL_OFFSET (ISA_CNF_OFFSET + 8)			/*  8900 eeprom */
#घोषणा AUTO_NEG_CNF_OFFSET (ISA_CNF_OFFSET + 8)		/*  8920 eeprom */

  /*  the assumption here is that the bits in the eeprom are generally  */
  /*  in the same position as those in the स्वतःnegctl रेजिस्टर. */
  /*  Of course the IMM bit is not in that रेजिस्टर so it must be  */
  /*  masked out */
#घोषणा EE_FORCE_FDX  0x8000
#घोषणा EE_NLP_ENABLE 0x0200
#घोषणा EE_AUTO_NEG_ENABLE 0x0100
#घोषणा EE_ALLOW_FDX 0x0080
#घोषणा EE_AUTO_NEG_CNF_MASK (EE_FORCE_FDX|EE_NLP_ENABLE|EE_AUTO_NEG_ENABLE|EE_ALLOW_FDX)

#घोषणा IMM_BIT 0x0040		/*  ignore missing media	 */

#घोषणा ADAPTER_CNF_OFFSET (AUTO_NEG_CNF_OFFSET + 2)
#घोषणा A_CNF_10B_T 0x0001
#घोषणा A_CNF_AUI 0x0002
#घोषणा A_CNF_10B_2 0x0004
#घोषणा A_CNF_MEDIA_TYPE 0x0070
#घोषणा A_CNF_MEDIA_AUTO 0x0070
#घोषणा A_CNF_MEDIA_10B_T 0x0020
#घोषणा A_CNF_MEDIA_AUI 0x0040
#घोषणा A_CNF_MEDIA_10B_2 0x0010
#घोषणा A_CNF_DC_DC_POLARITY 0x0080
#घोषणा A_CNF_NO_AUTO_POLARITY 0x2000
#घोषणा A_CNF_LOW_RX_SQUELCH 0x4000
#घोषणा A_CNF_EXTND_10B_2 0x8000

#घोषणा PACKET_PAGE_OFFSET 0x8

/*  Bit definitions क्रम the ISA configuration word from the EEPROM */
#घोषणा INT_NO_MASK 0x000F
#घोषणा DMA_NO_MASK 0x0070
#घोषणा ISA_DMA_SIZE 0x0200
#घोषणा ISA_AUTO_RxDMA 0x0400
#घोषणा ISA_RxDMA 0x0800
#घोषणा DMA_BURST 0x1000
#घोषणा STREAM_TRANSFER 0x2000
#घोषणा ANY_ISA_DMA (ISA_AUTO_RxDMA | ISA_RxDMA)

/*  DMA controller रेजिस्टरs */
#घोषणा DMA_BASE 0x00     /*  DMA controller base */
#घोषणा DMA_BASE_2 0x0C0    /*  DMA controller base */

#घोषणा DMA_STAT 0x0D0    /*  DMA controller status रेजिस्टर */
#घोषणा DMA_MASK 0x0D4    /*  DMA controller mask रेजिस्टर */
#घोषणा DMA_MODE 0x0D6    /*  DMA controller mode रेजिस्टर */
#घोषणा DMA_RESETFF 0x0D8    /*  DMA controller first/last flip flop */

/*  DMA data */
#घोषणा DMA_DISABLE 0x04     /*  Disable channel n */
#घोषणा DMA_ENABLE 0x00     /*  Enable channel n */
/*  Demand transfers, incr. address, स्वतः init, ग_लिखोs, ch. n */
#घोषणा DMA_RX_MODE 0x14
/*  Demand transfers, incr. address, स्वतः init, पढ़ोs, ch. n */
#घोषणा DMA_TX_MODE 0x18

#घोषणा DMA_SIZE (16*1024) /*  Size of dma buffer - 16k */

#घोषणा CS8900 0x0000
#घोषणा CS8920 0x4000
#घोषणा CS8920M 0x6000
#घोषणा REVISON_BITS 0x1F00
#घोषणा EEVER_NUMBER 0x12
#घोषणा CHKSUM_LEN 0x14
#घोषणा CHKSUM_VAL 0x0000
#घोषणा START_EEPROM_DATA 0x001c /*  Offset पूर्णांकo eeprom क्रम start of data */
#घोषणा IRQ_MAP_EEPROM_DATA 0x0046 /*  Offset पूर्णांकo eeprom क्रम the IRQ map */
#घोषणा IRQ_MAP_LEN 0x0004 /*  No of bytes to पढ़ो क्रम the IRQ map */
#घोषणा PNP_IRQ_FRMT 0x0022 /*  PNP small item IRQ क्रमmat */
#घोषणा CS8900_IRQ_MAP 0x1c20 /*  This IRQ map is fixed */

#घोषणा CS8920_NO_INTS 0x0F   /*  Max CS8920 पूर्णांकerrupt select # */

#घोषणा PNP_ADD_PORT 0x0279
#घोषणा PNP_WRITE_PORT 0x0A79

#घोषणा GET_PNP_ISA_STRUCT 0x40
#घोषणा PNP_ISA_STRUCT_LEN 0x06
#घोषणा PNP_CSN_CNT_OFF 0x01
#घोषणा PNP_RD_PORT_OFF 0x02
#घोषणा PNP_FUNCTION_OK 0x00
#घोषणा PNP_WAKE 0x03
#घोषणा PNP_RSRC_DATA 0x04
#घोषणा PNP_RSRC_READY 0x01
#घोषणा PNP_STATUS 0x05
#घोषणा PNP_ACTIVATE 0x30
#घोषणा PNP_CNF_IO_H 0x60
#घोषणा PNP_CNF_IO_L 0x61
#घोषणा PNP_CNF_INT 0x70
#घोषणा PNP_CNF_DMA 0x74
#घोषणा PNP_CNF_MEM 0x48
