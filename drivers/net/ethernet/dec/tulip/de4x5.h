<शैली गुरु>
/*
    Copyright 1994 Digital Equipment Corporation.

    This software may be used and distributed according to  the terms of the
    GNU General Public License, incorporated herein by reference.

    The author may    be  reached as davies@wanton.lkg.dec.com  or   Digital
    Equipment Corporation, 550 King Street, Littleton MA 01460.

    =========================================================================
*/

/*
** DC21040 CSR<1..15> Register Address Map
*/
#घोषणा DE4X5_BMR    iobase+(0x000 << lp->bus)  /* Bus Mode Register */
#घोषणा DE4X5_TPD    iobase+(0x008 << lp->bus)  /* Transmit Poll Demand Reg */
#घोषणा DE4X5_RPD    iobase+(0x010 << lp->bus)  /* Receive Poll Demand Reg */
#घोषणा DE4X5_RRBA   iobase+(0x018 << lp->bus)  /* RX Ring Base Address Reg */
#घोषणा DE4X5_TRBA   iobase+(0x020 << lp->bus)  /* TX Ring Base Address Reg */
#घोषणा DE4X5_STS    iobase+(0x028 << lp->bus)  /* Status Register */
#घोषणा DE4X5_OMR    iobase+(0x030 << lp->bus)  /* Operation Mode Register */
#घोषणा DE4X5_IMR    iobase+(0x038 << lp->bus)  /* Interrupt Mask Register */
#घोषणा DE4X5_MFC    iobase+(0x040 << lp->bus)  /* Missed Frame Counter */
#घोषणा DE4X5_APROM  iobase+(0x048 << lp->bus)  /* Ethernet Address PROM */
#घोषणा DE4X5_BROM   iobase+(0x048 << lp->bus)  /* Boot ROM Register */
#घोषणा DE4X5_SROM   iobase+(0x048 << lp->bus)  /* Serial ROM Register */
#घोषणा DE4X5_MII    iobase+(0x048 << lp->bus)  /* MII Interface Register */
#घोषणा DE4X5_DDR    iobase+(0x050 << lp->bus)  /* Data Diagnostic Register */
#घोषणा DE4X5_FDR    iobase+(0x058 << lp->bus)  /* Full Duplex Register */
#घोषणा DE4X5_GPT    iobase+(0x058 << lp->bus)  /* General Purpose Timer Reg.*/
#घोषणा DE4X5_GEP    iobase+(0x060 << lp->bus)  /* General Purpose Register */
#घोषणा DE4X5_SISR   iobase+(0x060 << lp->bus)  /* SIA Status Register */
#घोषणा DE4X5_SICR   iobase+(0x068 << lp->bus)  /* SIA Connectivity Register */
#घोषणा DE4X5_STRR   iobase+(0x070 << lp->bus)  /* SIA TX/RX Register */
#घोषणा DE4X5_SIGR   iobase+(0x078 << lp->bus)  /* SIA General Register */

/*
** EISA Register Address Map
*/
#घोषणा EISA_ID      iobase+0x0c80   /* EISA ID Registers */
#घोषणा EISA_ID0     iobase+0x0c80   /* EISA ID Register 0 */
#घोषणा EISA_ID1     iobase+0x0c81   /* EISA ID Register 1 */
#घोषणा EISA_ID2     iobase+0x0c82   /* EISA ID Register 2 */
#घोषणा EISA_ID3     iobase+0x0c83   /* EISA ID Register 3 */
#घोषणा EISA_CR      iobase+0x0c84   /* EISA Control Register */
#घोषणा EISA_REG0    iobase+0x0c88   /* EISA Configuration Register 0 */
#घोषणा EISA_REG1    iobase+0x0c89   /* EISA Configuration Register 1 */
#घोषणा EISA_REG2    iobase+0x0c8a   /* EISA Configuration Register 2 */
#घोषणा EISA_REG3    iobase+0x0c8f   /* EISA Configuration Register 3 */
#घोषणा EISA_APROM   iobase+0x0c90   /* Ethernet Address PROM */

/*
** PCI/EISA Configuration Registers Address Map
*/
#घोषणा PCI_CFID     iobase+0x0008   /* PCI Configuration ID Register */
#घोषणा PCI_CFCS     iobase+0x000c   /* PCI Command/Status Register */
#घोषणा PCI_CFRV     iobase+0x0018   /* PCI Revision Register */
#घोषणा PCI_CFLT     iobase+0x001c   /* PCI Latency Timer Register */
#घोषणा PCI_CBIO     iobase+0x0028   /* PCI Base I/O Register */
#घोषणा PCI_CBMA     iobase+0x002c   /* PCI Base Memory Address Register */
#घोषणा PCI_CBER     iobase+0x0030   /* PCI Expansion ROM Base Address Reg. */
#घोषणा PCI_CFIT     iobase+0x003c   /* PCI Configuration Interrupt Register */
#घोषणा PCI_CFDA     iobase+0x0040   /* PCI Driver Area Register */
#घोषणा PCI_CFDD     iobase+0x0041   /* PCI Driver Dependent Area Register */
#घोषणा PCI_CFPM     iobase+0x0043   /* PCI Power Management Area Register */

/*
** EISA Configuration Register 0 bit definitions
*/
#घोषणा ER0_BSW       0x80           /* EISA Bus Slave Width, 1: 32 bits */
#घोषणा ER0_BMW       0x40           /* EISA Bus Master Width, 1: 32 bits */
#घोषणा ER0_EPT       0x20           /* EISA PREEMPT Time, 0: 23 BCLKs */
#घोषणा ER0_ISTS      0x10           /* Interrupt Status (X) */
#घोषणा ER0_LI        0x08           /* Latch Interrupts */
#घोषणा ER0_INTL      0x06           /* INTerrupt Level */
#घोषणा ER0_INTT      0x01           /* INTerrupt Type, 0: Level, 1: Edge */

/*
** EISA Configuration Register 1 bit definitions
*/
#घोषणा ER1_IAM       0xe0           /* ISA Address Mode */
#घोषणा ER1_IAE       0x10           /* ISA Addressing Enable */
#घोषणा ER1_UPIN      0x0f           /* User Pins */

/*
** EISA Configuration Register 2 bit definitions
*/
#घोषणा ER2_BRS       0xc0           /* Boot ROM Size */
#घोषणा ER2_BRA       0x3c           /* Boot ROM Address <16:13> */

/*
** EISA Configuration Register 3 bit definitions
*/
#घोषणा ER3_BWE       0x40           /* Burst Write Enable */
#घोषणा ER3_BRE       0x04           /* Burst Read Enable */
#घोषणा ER3_LSR       0x02           /* Local Software Reset */

/*
** PCI Configuration ID Register (PCI_CFID). The Device IDs are left
** shअगरted 8 bits to allow detection of DC21142 and DC21143 variants with
** the configuration revision रेजिस्टर step number.
*/
#घोषणा CFID_DID    0xff00           /* Device ID */
#घोषणा CFID_VID    0x00ff           /* Venकरोr ID */
#घोषणा DC21040_DID 0x0200           /* Unique Device ID # */
#घोषणा DC21040_VID 0x1011           /* DC21040 Manufacturer */
#घोषणा DC21041_DID 0x1400           /* Unique Device ID # */
#घोषणा DC21041_VID 0x1011           /* DC21041 Manufacturer */
#घोषणा DC21140_DID 0x0900           /* Unique Device ID # */
#घोषणा DC21140_VID 0x1011           /* DC21140 Manufacturer */
#घोषणा DC2114x_DID 0x1900           /* Unique Device ID # */
#घोषणा DC2114x_VID 0x1011           /* DC2114[23] Manufacturer */

/*
** Chipset defines
*/
#घोषणा DC21040     DC21040_DID
#घोषणा DC21041     DC21041_DID
#घोषणा DC21140     DC21140_DID
#घोषणा DC2114x     DC2114x_DID
#घोषणा DC21142     (DC2114x_DID | 0x0010)
#घोषणा DC21143     (DC2114x_DID | 0x0030)
#घोषणा DC2114x_BRK 0x0020           /* CFRV अवरोध between DC21142 & DC21143 */

#घोषणा is_DC21040 ((venकरोr == DC21040_VID) && (device == DC21040_DID))
#घोषणा is_DC21041 ((venकरोr == DC21041_VID) && (device == DC21041_DID))
#घोषणा is_DC21140 ((venकरोr == DC21140_VID) && (device == DC21140_DID))
#घोषणा is_DC2114x ((venकरोr == DC2114x_VID) && (device == DC2114x_DID))
#घोषणा is_DC21142 ((venकरोr == DC2114x_VID) && (device == DC21142))
#घोषणा is_DC21143 ((venकरोr == DC2114x_VID) && (device == DC21143))

/*
** PCI Configuration Command/Status Register (PCI_CFCS)
*/
#घोषणा CFCS_DPE    0x80000000       /* Detected Parity Error (S) */
#घोषणा CFCS_SSE    0x40000000       /* Signal System Error   (S) */
#घोषणा CFCS_RMA    0x20000000       /* Receive Master Abort  (S) */
#घोषणा CFCS_RTA    0x10000000       /* Receive Target Abort  (S) */
#घोषणा CFCS_DST    0x06000000       /* DEVSEL Timing         (S) */
#घोषणा CFCS_DPR    0x01000000       /* Data Parity Report    (S) */
#घोषणा CFCS_FBB    0x00800000       /* Fast Back-To-Back     (S) */
#घोषणा CFCS_SEE    0x00000100       /* System Error Enable   (C) */
#घोषणा CFCS_PER    0x00000040       /* Parity Error Response (C) */
#घोषणा CFCS_MO     0x00000004       /* Master Operation      (C) */
#घोषणा CFCS_MSA    0x00000002       /* Memory Space Access   (C) */
#घोषणा CFCS_IOSA   0x00000001       /* I/O Space Access      (C) */

/*
** PCI Configuration Revision Register (PCI_CFRV)
*/
#घोषणा CFRV_BC     0xff000000       /* Base Class */
#घोषणा CFRV_SC     0x00ff0000       /* Subclass */
#घोषणा CFRV_RN     0x000000f0       /* Revision Number */
#घोषणा CFRV_SN     0x0000000f       /* Step Number */
#घोषणा BASE_CLASS  0x02000000       /* Indicates Network Controller */
#घोषणा SUB_CLASS   0x00000000       /* Indicates Ethernet Controller */
#घोषणा STEP_NUMBER 0x00000020       /* Increments क्रम future chips */
#घोषणा REV_NUMBER  0x00000003       /* 0x00, 0x01, 0x02, 0x03: Rev in Step */
#घोषणा CFRV_MASK   0xffff0000       /* Register mask */

/*
** PCI Configuration Latency Timer Register (PCI_CFLT)
*/
#घोषणा CFLT_BC     0x0000ff00       /* Latency Timer bits */

/*
** PCI Configuration Base I/O Address Register (PCI_CBIO)
*/
#घोषणा CBIO_MASK   -128             /* Base I/O Address Mask */
#घोषणा CBIO_IOSI   0x00000001       /* I/O Space Indicator (RO, value is 1) */

/*
** PCI Configuration Card Inक्रमmation Structure Register (PCI_CCIS)
*/
#घोषणा CCIS_ROMI   0xf0000000       /* ROM Image */
#घोषणा CCIS_ASO    0x0ffffff8       /* Address Space Offset */
#घोषणा CCIS_ASI    0x00000007       /* Address Space Indicator */

/*
** PCI Configuration Subप्रणाली ID Register (PCI_SSID)
*/
#घोषणा SSID_SSID   0xffff0000       /* Subप्रणाली ID */
#घोषणा SSID_SVID   0x0000ffff       /* Subप्रणाली Venकरोr ID */

/*
** PCI Configuration Expansion ROM Base Address Register (PCI_CBER)
*/
#घोषणा CBER_MASK   0xfffffc00       /* Expansion ROM Base Address Mask */
#घोषणा CBER_ROME   0x00000001       /* ROM Enable */

/*
** PCI Configuration Interrupt Register (PCI_CFIT)
*/
#घोषणा CFIT_MXLT   0xff000000       /* MAX_LAT Value (0.25us periods) */
#घोषणा CFIT_MNGT   0x00ff0000       /* MIN_GNT Value (0.25us periods) */
#घोषणा CFIT_IRQP   0x0000ff00       /* Interrupt Pin */
#घोषणा CFIT_IRQL   0x000000ff       /* Interrupt Line */

/*
** PCI Configuration Power Management Area Register (PCI_CFPM)
*/
#घोषणा SLEEP       0x80             /* Power Saving Sleep Mode */
#घोषणा SNOOZE      0x40             /* Power Saving Snooze Mode */
#घोषणा WAKEUP      0x00             /* Power Saving Wakeup */

#घोषणा PCI_CFDA_DSU 0x41            /* 8 bit Configuration Space Address */
#घोषणा PCI_CFDA_PSM 0x43            /* 8 bit Configuration Space Address */

/*
** DC21040 Bus Mode Register (DE4X5_BMR)
*/
#घोषणा BMR_RML    0x00200000       /* [Memory] Read Multiple */
#घोषणा BMR_DBO    0x00100000       /* Descriptor Byte Ordering (Endian) */
#घोषणा BMR_TAP    0x000e0000       /* Transmit Automatic Polling */
#घोषणा BMR_DAS    0x00010000       /* Diagnostic Address Space */
#घोषणा BMR_CAL    0x0000c000       /* Cache Alignment */
#घोषणा BMR_PBL    0x00003f00       /* Programmable Burst Length */
#घोषणा BMR_BLE    0x00000080       /* Big/Little Endian */
#घोषणा BMR_DSL    0x0000007c       /* Descriptor Skip Length */
#घोषणा BMR_BAR    0x00000002       /* Bus ARbitration */
#घोषणा BMR_SWR    0x00000001       /* Software Reset */

                                    /* Timings here are क्रम 10BASE-T/AUI only*/
#घोषणा TAP_NOPOLL 0x00000000       /* No स्वतःmatic polling */
#घोषणा TAP_200US  0x00020000       /* TX स्वतःmatic polling every 200us */
#घोषणा TAP_800US  0x00040000       /* TX स्वतःmatic polling every 800us */
#घोषणा TAP_1_6MS  0x00060000       /* TX स्वतःmatic polling every 1.6ms */
#घोषणा TAP_12_8US 0x00080000       /* TX स्वतःmatic polling every 12.8us */
#घोषणा TAP_25_6US 0x000a0000       /* TX स्वतःmatic polling every 25.6us */
#घोषणा TAP_51_2US 0x000c0000       /* TX स्वतःmatic polling every 51.2us */
#घोषणा TAP_102_4US 0x000e0000      /* TX स्वतःmatic polling every 102.4us */

#घोषणा CAL_NOUSE  0x00000000       /* Not used */
#घोषणा CAL_8LONG  0x00004000       /* 8-दीर्घword alignment */
#घोषणा CAL_16LONG 0x00008000       /* 16-दीर्घword alignment */
#घोषणा CAL_32LONG 0x0000c000       /* 32-दीर्घword alignment */

#घोषणा PBL_0      0x00000000       /*  DMA burst length = amount in RX FIFO */
#घोषणा PBL_1      0x00000100       /*  1 दीर्घword  DMA burst length */
#घोषणा PBL_2      0x00000200       /*  2 दीर्घwords DMA burst length */
#घोषणा PBL_4      0x00000400       /*  4 दीर्घwords DMA burst length */
#घोषणा PBL_8      0x00000800       /*  8 दीर्घwords DMA burst length */
#घोषणा PBL_16     0x00001000       /* 16 दीर्घwords DMA burst length */
#घोषणा PBL_32     0x00002000       /* 32 दीर्घwords DMA burst length */

#घोषणा DSL_0      0x00000000       /*  0 दीर्घword  / descriptor */
#घोषणा DSL_1      0x00000004       /*  1 दीर्घword  / descriptor */
#घोषणा DSL_2      0x00000008       /*  2 दीर्घwords / descriptor */
#घोषणा DSL_4      0x00000010       /*  4 दीर्घwords / descriptor */
#घोषणा DSL_8      0x00000020       /*  8 दीर्घwords / descriptor */
#घोषणा DSL_16     0x00000040       /* 16 दीर्घwords / descriptor */
#घोषणा DSL_32     0x00000080       /* 32 दीर्घwords / descriptor */

/*
** DC21040 Transmit Poll Demand Register (DE4X5_TPD)
*/
#घोषणा TPD        0x00000001       /* Transmit Poll Demand */

/*
** DC21040 Receive Poll Demand Register (DE4X5_RPD)
*/
#घोषणा RPD        0x00000001       /* Receive Poll Demand */

/*
** DC21040 Receive Ring Base Address Register (DE4X5_RRBA)
*/
#घोषणा RRBA       0xfffffffc       /* RX Descriptor List Start Address */

/*
** DC21040 Transmit Ring Base Address Register (DE4X5_TRBA)
*/
#घोषणा TRBA       0xfffffffc       /* TX Descriptor List Start Address */

/*
** Status Register (DE4X5_STS)
*/
#घोषणा STS_GPI    0x04000000       /* General Purpose Port Interrupt */
#घोषणा STS_BE     0x03800000       /* Bus Error Bits */
#घोषणा STS_TS     0x00700000       /* Transmit Process State */
#घोषणा STS_RS     0x000e0000       /* Receive Process State */
#घोषणा STS_NIS    0x00010000       /* Normal Interrupt Summary */
#घोषणा STS_AIS    0x00008000       /* Abnormal Interrupt Summary */
#घोषणा STS_ER     0x00004000       /* Early Receive */
#घोषणा STS_FBE    0x00002000       /* Fatal Bus Error */
#घोषणा STS_SE     0x00002000       /* System Error */
#घोषणा STS_LNF    0x00001000       /* Link Fail */
#घोषणा STS_FD     0x00000800       /* Full-Duplex Short Frame Received */
#घोषणा STS_TM     0x00000800       /* Timer Expired (DC21041) */
#घोषणा STS_ETI    0x00000400       /* Early Transmit Interrupt */
#घोषणा STS_AT     0x00000400       /* AUI/TP Pin */
#घोषणा STS_RWT    0x00000200       /* Receive Watchकरोg Time-Out */
#घोषणा STS_RPS    0x00000100       /* Receive Process Stopped */
#घोषणा STS_RU     0x00000080       /* Receive Buffer Unavailable */
#घोषणा STS_RI     0x00000040       /* Receive Interrupt */
#घोषणा STS_UNF    0x00000020       /* Transmit Underflow */
#घोषणा STS_LNP    0x00000010       /* Link Pass */
#घोषणा STS_ANC    0x00000010       /* Autonegotiation Complete */
#घोषणा STS_TJT    0x00000008       /* Transmit Jabber Time-Out */
#घोषणा STS_TU     0x00000004       /* Transmit Buffer Unavailable */
#घोषणा STS_TPS    0x00000002       /* Transmit Process Stopped */
#घोषणा STS_TI     0x00000001       /* Transmit Interrupt */

#घोषणा EB_PAR     0x00000000       /* Parity Error */
#घोषणा EB_MA      0x00800000       /* Master Abort */
#घोषणा EB_TA      0x01000000       /* Target Abort */
#घोषणा EB_RES0    0x01800000       /* Reserved */
#घोषणा EB_RES1    0x02000000       /* Reserved */

#घोषणा TS_STOP    0x00000000       /* Stopped */
#घोषणा TS_FTD     0x00100000       /* Fetch Transmit Descriptor */
#घोषणा TS_WEOT    0x00200000       /* Wait क्रम End Of Transmission */
#घोषणा TS_QDAT    0x00300000       /* Queue skb data पूर्णांकo TX FIFO */
#घोषणा TS_RES     0x00400000       /* Reserved */
#घोषणा TS_SPKT    0x00500000       /* Setup Packet */
#घोषणा TS_SUSP    0x00600000       /* Suspended */
#घोषणा TS_CLTD    0x00700000       /* Close Transmit Descriptor */

#घोषणा RS_STOP    0x00000000       /* Stopped */
#घोषणा RS_FRD     0x00020000       /* Fetch Receive Descriptor */
#घोषणा RS_CEOR    0x00040000       /* Check क्रम End of Receive Packet */
#घोषणा RS_WFRP    0x00060000       /* Wait क्रम Receive Packet */
#घोषणा RS_SUSP    0x00080000       /* Suspended */
#घोषणा RS_CLRD    0x000a0000       /* Close Receive Descriptor */
#घोषणा RS_FLUSH   0x000c0000       /* Flush RX FIFO */
#घोषणा RS_QRFS    0x000e0000       /* Queue RX FIFO पूर्णांकo RX Skb */

#घोषणा INT_CANCEL 0x0001ffff       /* For zeroing all पूर्णांकerrupt sources */

/*
** Operation Mode Register (DE4X5_OMR)
*/
#घोषणा OMR_SC     0x80000000       /* Special Capture Effect Enable */
#घोषणा OMR_RA     0x40000000       /* Receive All */
#घोषणा OMR_SDP    0x02000000       /* SD Polarity - MUST BE ASSERTED */
#घोषणा OMR_SCR    0x01000000       /* Scrambler Mode */
#घोषणा OMR_PCS    0x00800000       /* PCS Function */
#घोषणा OMR_TTM    0x00400000       /* Transmit Threshold Mode */
#घोषणा OMR_SF     0x00200000       /* Store and Forward */
#घोषणा OMR_HBD    0x00080000       /* HeartBeat Disable */
#घोषणा OMR_PS     0x00040000       /* Port Select */
#घोषणा OMR_CA     0x00020000       /* Capture Effect Enable */
#घोषणा OMR_BP     0x00010000       /* Back Pressure */
#घोषणा OMR_TR     0x0000c000       /* Threshold Control Bits */
#घोषणा OMR_ST     0x00002000       /* Start/Stop Transmission Command */
#घोषणा OMR_FC     0x00001000       /* Force Collision Mode */
#घोषणा OMR_OM     0x00000c00       /* Operating Mode */
#घोषणा OMR_FDX    0x00000200       /* Full Duplex Mode */
#घोषणा OMR_FKD    0x00000100       /* Flaky Oscillator Disable */
#घोषणा OMR_PM     0x00000080       /* Pass All Multicast */
#घोषणा OMR_PR     0x00000040       /* Promiscuous Mode */
#घोषणा OMR_SB     0x00000020       /* Start/Stop Backoff Counter */
#घोषणा OMR_IF     0x00000010       /* Inverse Filtering */
#घोषणा OMR_PB     0x00000008       /* Pass Bad Frames */
#घोषणा OMR_HO     0x00000004       /* Hash Only Filtering Mode */
#घोषणा OMR_SR     0x00000002       /* Start/Stop Receive */
#घोषणा OMR_HP     0x00000001       /* Hash/Perfect Receive Filtering Mode */

#घोषणा TR_72      0x00000000       /* Threshold set to 72 (128) bytes */
#घोषणा TR_96      0x00004000       /* Threshold set to 96 (256) bytes */
#घोषणा TR_128     0x00008000       /* Threshold set to 128 (512) bytes */
#घोषणा TR_160     0x0000c000       /* Threshold set to 160 (1024) bytes */

#घोषणा OMR_DEF     (OMR_SDP)
#घोषणा OMR_SIA     (OMR_SDP | OMR_TTM)
#घोषणा OMR_SYM     (OMR_SDP | OMR_SCR | OMR_PCS | OMR_HBD | OMR_PS)
#घोषणा OMR_MII_10  (OMR_SDP | OMR_TTM | OMR_PS)
#घोषणा OMR_MII_100 (OMR_SDP | OMR_HBD | OMR_PS)

/*
** DC21040 Interrupt Mask Register (DE4X5_IMR)
*/
#घोषणा IMR_GPM    0x04000000       /* General Purpose Port Mask */
#घोषणा IMR_NIM    0x00010000       /* Normal Interrupt Summary Mask */
#घोषणा IMR_AIM    0x00008000       /* Abnormal Interrupt Summary Mask */
#घोषणा IMR_ERM    0x00004000       /* Early Receive Mask */
#घोषणा IMR_FBM    0x00002000       /* Fatal Bus Error Mask */
#घोषणा IMR_SEM    0x00002000       /* System Error Mask */
#घोषणा IMR_LFM    0x00001000       /* Link Fail Mask */
#घोषणा IMR_FDM    0x00000800       /* Full-Duplex (Short Frame) Mask */
#घोषणा IMR_TMM    0x00000800       /* Timer Expired Mask (DC21041) */
#घोषणा IMR_ETM    0x00000400       /* Early Transmit Interrupt Mask */
#घोषणा IMR_ATM    0x00000400       /* AUI/TP Switch Mask */
#घोषणा IMR_RWM    0x00000200       /* Receive Watchकरोg Time-Out Mask */
#घोषणा IMR_RSM    0x00000100       /* Receive Stopped Mask */
#घोषणा IMR_RUM    0x00000080       /* Receive Buffer Unavailable Mask */
#घोषणा IMR_RIM    0x00000040       /* Receive Interrupt Mask */
#घोषणा IMR_UNM    0x00000020       /* Underflow Interrupt Mask */
#घोषणा IMR_ANM    0x00000010       /* Autonegotiation Complete Mask */
#घोषणा IMR_LPM    0x00000010       /* Link Pass */
#घोषणा IMR_TJM    0x00000008       /* Transmit Time-Out Jabber Mask */
#घोषणा IMR_TUM    0x00000004       /* Transmit Buffer Unavailable Mask */
#घोषणा IMR_TSM    0x00000002       /* Transmission Stopped Mask */
#घोषणा IMR_TIM    0x00000001       /* Transmit Interrupt Mask */

/*
** Missed Frames and FIFO Overflow Counters (DE4X5_MFC)
*/
#घोषणा MFC_FOCO   0x10000000       /* FIFO Overflow Counter Overflow Bit */
#घोषणा MFC_FOC    0x0ffe0000       /* FIFO Overflow Counter Bits */
#घोषणा MFC_OVFL   0x00010000       /* Missed Frames Counter Overflow Bit */
#घोषणा MFC_CNTR   0x0000ffff       /* Missed Frames Counter Bits */
#घोषणा MFC_FOCM   0x1ffe0000       /* FIFO Overflow Counter Mask */

/*
** DC21040 Ethernet Address PROM (DE4X5_APROM)
*/
#घोषणा APROM_DN   0x80000000       /* Data Not Valid */
#घोषणा APROM_DT   0x000000ff       /* Address Byte */

/*
** DC21041 Boot/Ethernet Address ROM (DE4X5_BROM)
*/
#घोषणा BROM_MODE 0x00008000       /* MODE_1: 0,  MODE_0: 1  (पढ़ो only) */
#घोषणा BROM_RD   0x00004000       /* Read from Boot ROM */
#घोषणा BROM_WR   0x00002000       /* Write to Boot ROM */
#घोषणा BROM_BR   0x00001000       /* Select Boot ROM when set */
#घोषणा BROM_SR   0x00000800       /* Select Serial ROM when set */
#घोषणा BROM_REG  0x00000400       /* External Register Select */
#घोषणा BROM_DT   0x000000ff       /* Data Byte */

/*
** DC21041 Serial/Ethernet Address ROM (DE4X5_SROM, DE4X5_MII)
*/
#घोषणा MII_MDI   0x00080000       /* MII Management Data In */
#घोषणा MII_MDO   0x00060000       /* MII Management Mode/Data Out */
#घोषणा MII_MRD   0x00040000       /* MII Management Define Read Mode */
#घोषणा MII_MWR   0x00000000       /* MII Management Define Write Mode */
#घोषणा MII_MDT   0x00020000       /* MII Management Data Out */
#घोषणा MII_MDC   0x00010000       /* MII Management Clock */
#घोषणा MII_RD    0x00004000       /* Read from MII */
#घोषणा MII_WR    0x00002000       /* Write to MII */
#घोषणा MII_SEL   0x00000800       /* Select MII when RESET */

#घोषणा SROM_MODE 0x00008000       /* MODE_1: 0,  MODE_0: 1  (पढ़ो only) */
#घोषणा SROM_RD   0x00004000       /* Read from Boot ROM */
#घोषणा SROM_WR   0x00002000       /* Write to Boot ROM */
#घोषणा SROM_BR   0x00001000       /* Select Boot ROM when set */
#घोषणा SROM_SR   0x00000800       /* Select Serial ROM when set */
#घोषणा SROM_REG  0x00000400       /* External Register Select */
#घोषणा SROM_DT   0x000000ff       /* Data Byte */

#घोषणा DT_OUT    0x00000008       /* Serial Data Out */
#घोषणा DT_IN     0x00000004       /* Serial Data In */
#घोषणा DT_CLK    0x00000002       /* Serial ROM Clock */
#घोषणा DT_CS     0x00000001       /* Serial ROM Chip Select */

#घोषणा MII_PREAMBLE 0xffffffff    /* MII Management Preamble */
#घोषणा MII_TEST     0xaaaaaaaa    /* MII Test Signal */
#घोषणा MII_STRD     0x06          /* Start of Frame+Op Code: use low nibble */
#घोषणा MII_STWR     0x0a          /* Start of Frame+Op Code: use low nibble */

#घोषणा MII_CR       0x00          /* MII Management Control Register */
#घोषणा MII_SR       0x01          /* MII Management Status Register */
#घोषणा MII_ID0      0x02          /* PHY Identअगरier Register 0 */
#घोषणा MII_ID1      0x03          /* PHY Identअगरier Register 1 */
#घोषणा MII_ANA      0x04          /* Auto Negotiation Advertisement */
#घोषणा MII_ANLPA    0x05          /* Auto Negotiation Link Partner Ability */
#घोषणा MII_ANE      0x06          /* Auto Negotiation Expansion */
#घोषणा MII_ANP      0x07          /* Auto Negotiation Next Page TX */

#घोषणा DE4X5_MAX_MII 32           /* Maximum address of MII PHY devices */

/*
** MII Management Control Register
*/
#घोषणा MII_CR_RST  0x8000         /* RESET the PHY chip */
#घोषणा MII_CR_LPBK 0x4000         /* Loopback enable */
#घोषणा MII_CR_SPD  0x2000         /* 0: 10Mb/s; 1: 100Mb/s */
#घोषणा MII_CR_10   0x0000         /* Set 10Mb/s */
#घोषणा MII_CR_100  0x2000         /* Set 100Mb/s */
#घोषणा MII_CR_ASSE 0x1000         /* Auto Speed Select Enable */
#घोषणा MII_CR_PD   0x0800         /* Power Down */
#घोषणा MII_CR_ISOL 0x0400         /* Isolate Mode */
#घोषणा MII_CR_RAN  0x0200         /* Restart Auto Negotiation */
#घोषणा MII_CR_FDM  0x0100         /* Full Duplex Mode */
#घोषणा MII_CR_CTE  0x0080         /* Collision Test Enable */

/*
** MII Management Status Register
*/
#घोषणा MII_SR_T4C  0x8000         /* 100BASE-T4 capable */
#घोषणा MII_SR_TXFD 0x4000         /* 100BASE-TX Full Duplex capable */
#घोषणा MII_SR_TXHD 0x2000         /* 100BASE-TX Half Duplex capable */
#घोषणा MII_SR_TFD  0x1000         /* 10BASE-T Full Duplex capable */
#घोषणा MII_SR_THD  0x0800         /* 10BASE-T Half Duplex capable */
#घोषणा MII_SR_ASSC 0x0020         /* Auto Speed Selection Complete*/
#घोषणा MII_SR_RFD  0x0010         /* Remote Fault Detected */
#घोषणा MII_SR_ANC  0x0008         /* Auto Negotiation capable */
#घोषणा MII_SR_LKS  0x0004         /* Link Status */
#घोषणा MII_SR_JABD 0x0002         /* Jabber Detect */
#घोषणा MII_SR_XC   0x0001         /* Extended Capabilities */

/*
** MII Management Auto Negotiation Advertisement Register
*/
#घोषणा MII_ANA_TAF  0x03e0        /* Technology Ability Field */
#घोषणा MII_ANA_T4AM 0x0200        /* T4 Technology Ability Mask */
#घोषणा MII_ANA_TXAM 0x0180        /* TX Technology Ability Mask */
#घोषणा MII_ANA_FDAM 0x0140        /* Full Duplex Technology Ability Mask */
#घोषणा MII_ANA_HDAM 0x02a0        /* Half Duplex Technology Ability Mask */
#घोषणा MII_ANA_100M 0x0380        /* 100Mb Technology Ability Mask */
#घोषणा MII_ANA_10M  0x0060        /* 10Mb Technology Ability Mask */
#घोषणा MII_ANA_CSMA 0x0001        /* CSMA-CD Capable */

/*
** MII Management Auto Negotiation Remote End Register
*/
#घोषणा MII_ANLPA_NP   0x8000      /* Next Page (Enable) */
#घोषणा MII_ANLPA_ACK  0x4000      /* Remote Acknowledge */
#घोषणा MII_ANLPA_RF   0x2000      /* Remote Fault */
#घोषणा MII_ANLPA_TAF  0x03e0      /* Technology Ability Field */
#घोषणा MII_ANLPA_T4AM 0x0200      /* T4 Technology Ability Mask */
#घोषणा MII_ANLPA_TXAM 0x0180      /* TX Technology Ability Mask */
#घोषणा MII_ANLPA_FDAM 0x0140      /* Full Duplex Technology Ability Mask */
#घोषणा MII_ANLPA_HDAM 0x02a0      /* Half Duplex Technology Ability Mask */
#घोषणा MII_ANLPA_100M 0x0380      /* 100Mb Technology Ability Mask */
#घोषणा MII_ANLPA_10M  0x0060      /* 10Mb Technology Ability Mask */
#घोषणा MII_ANLPA_CSMA 0x0001      /* CSMA-CD Capable */

/*
** SROM Media Definitions (ABG SROM Section)
*/
#घोषणा MEDIA_NWAY     0x0080      /* Nway (Auto Negotiation) on PHY */
#घोषणा MEDIA_MII      0x0040      /* MII Present on the adapter */
#घोषणा MEDIA_FIBRE    0x0008      /* Fibre Media present */
#घोषणा MEDIA_AUI      0x0004      /* AUI Media present */
#घोषणा MEDIA_TP       0x0002      /* TP Media present */
#घोषणा MEDIA_BNC      0x0001      /* BNC Media present */

/*
** SROM Definitions (Digital Semiconductor Format)
*/
#घोषणा SROM_SSVID     0x0000      /* Sub-प्रणाली Venकरोr ID offset */
#घोषणा SROM_SSID      0x0002      /* Sub-प्रणाली ID offset */
#घोषणा SROM_CISPL     0x0004      /* CardBus CIS Poपूर्णांकer low offset */
#घोषणा SROM_CISPH     0x0006      /* CardBus CIS Poपूर्णांकer high offset */
#घोषणा SROM_IDCRC     0x0010      /* ID Block CRC offset*/
#घोषणा SROM_RSVD2     0x0011      /* ID Reserved 2 offset */
#घोषणा SROM_SFV       0x0012      /* SROM Format Version offset */
#घोषणा SROM_CCNT      0x0013      /* Controller Count offset */
#घोषणा SROM_HWADD     0x0014      /* Hardware Address offset */
#घोषणा SROM_MRSVD     0x007c      /* Manufacturer Reserved offset*/
#घोषणा SROM_CRC       0x007e      /* SROM CRC offset */

/*
** SROM Media Connection Definitions
*/
#घोषणा SROM_10BT      0x0000      /*  10BASE-T half duplex */
#घोषणा SROM_10BTN     0x0100      /*  10BASE-T with Nway */
#घोषणा SROM_10BTF     0x0204      /*  10BASE-T full duplex */
#घोषणा SROM_10BTNLP   0x0400      /*  10BASE-T without Link Pass test */
#घोषणा SROM_10B2      0x0001      /*  10BASE-2 (BNC) */
#घोषणा SROM_10B5      0x0002      /*  10BASE-5 (AUI) */
#घोषणा SROM_100BTH    0x0003      /*  100BASE-T half duplex */
#घोषणा SROM_100BTF    0x0205      /*  100BASE-T full duplex */
#घोषणा SROM_100BT4    0x0006      /*  100BASE-T4 */
#घोषणा SROM_100BFX    0x0007      /*  100BASE-FX half duplex (Fiber) */
#घोषणा SROM_M10BT     0x0009      /*  MII 10BASE-T half duplex */
#घोषणा SROM_M10BTF    0x020a      /*  MII 10BASE-T full duplex */
#घोषणा SROM_M100BT    0x000d      /*  MII 100BASE-T half duplex */
#घोषणा SROM_M100BTF   0x020e      /*  MII 100BASE-T full duplex */
#घोषणा SROM_M100BT4   0x000f      /*  MII 100BASE-T4 */
#घोषणा SROM_M100BF    0x0010      /*  MII 100BASE-FX half duplex */
#घोषणा SROM_M100BFF   0x0211      /*  MII 100BASE-FX full duplex */
#घोषणा SROM_PDA       0x0800      /*  Powerup & Dynamic Autosense */
#घोषणा SROM_PAO       0x8800      /*  Powerup Autosense Only */
#घोषणा SROM_NSMI      0xffff      /*  No Selected Media Inक्रमmation */

/*
** SROM Media Definitions
*/
#घोषणा SROM_10BASET   0x0000      /*  10BASE-T half duplex */
#घोषणा SROM_10BASE2   0x0001      /*  10BASE-2 (BNC) */
#घोषणा SROM_10BASE5   0x0002      /*  10BASE-5 (AUI) */
#घोषणा SROM_100BASET  0x0003      /*  100BASE-T half duplex */
#घोषणा SROM_10BASETF  0x0004      /*  10BASE-T full duplex */
#घोषणा SROM_100BASETF 0x0005      /*  100BASE-T full duplex */
#घोषणा SROM_100BASET4 0x0006      /*  100BASE-T4 */
#घोषणा SROM_100BASEF  0x0007      /*  100BASE-FX half duplex */
#घोषणा SROM_100BASEFF 0x0008      /*  100BASE-FX full duplex */

#घोषणा BLOCK_LEN      0x7f        /* Extended blocks length mask */
#घोषणा EXT_FIELD      0x40        /* Extended blocks extension field bit */
#घोषणा MEDIA_CODE     0x3f        /* Extended blocks media code mask */

/*
** SROM Compact Format Block Masks
*/
#घोषणा COMPACT_FI      0x80       /* Format Indicator */
#घोषणा COMPACT_LEN     0x04       /* Length */
#घोषणा COMPACT_MC      0x3f       /* Media Code */

/*
** SROM Extended Format Block Type 0 Masks
*/
#घोषणा BLOCK0_FI      0x80        /* Format Indicator */
#घोषणा BLOCK0_MCS     0x80        /* Media Code byte Sign */
#घोषणा BLOCK0_MC      0x3f        /* Media Code */

/*
** DC21040 Full Duplex Register (DE4X5_FDR)
*/
#घोषणा FDR_FDACV  0x0000ffff      /* Full Duplex Auto Configuration Value */

/*
** DC21041 General Purpose Timer Register (DE4X5_GPT)
*/
#घोषणा GPT_CON  0x00010000        /* One shot: 0,  Continuous: 1 */
#घोषणा GPT_VAL  0x0000ffff        /* Timer Value */

/*
** DC21140 General Purpose Register (DE4X5_GEP) (hardware dependent bits)
*/
/* Valid ONLY क्रम DE500 hardware */
#घोषणा GEP_LNP  0x00000080        /* Link Pass               (input)        */
#घोषणा GEP_SLNK 0x00000040        /* SYM LINK                (input)        */
#घोषणा GEP_SDET 0x00000020        /* Signal Detect           (input)        */
#घोषणा GEP_HRST 0x00000010        /* Hard RESET (to PHY)     (output)       */
#घोषणा GEP_FDXD 0x00000008        /* Full Duplex Disable     (output)       */
#घोषणा GEP_PHYL 0x00000004        /* PHY Loopback            (output)       */
#घोषणा GEP_FLED 0x00000002        /* Force Activity LED on   (output)       */
#घोषणा GEP_MODE 0x00000001        /* 0: 10Mb/s,  1: 100Mb/s                 */
#घोषणा GEP_INIT 0x0000011f        /* Setup inमाला_दो (0) and outमाला_दो (1)       */
#घोषणा GEP_CTRL 0x00000100        /* GEP control bit                        */

/*
** SIA Register Defaults
*/
#घोषणा CSR13 0x00000001
#घोषणा CSR14 0x0003ff7f           /* Autonegotiation disabled               */
#घोषणा CSR15 0x00000008

/*
** SIA Status Register (DE4X5_SISR)
*/
#घोषणा SISR_LPC   0xffff0000      /* Link Partner's Code Word               */
#घोषणा SISR_LPN   0x00008000      /* Link Partner Negotiable                */
#घोषणा SISR_ANS   0x00007000      /* Auto Negotiation Arbitration State     */
#घोषणा SISR_NSN   0x00000800      /* Non Stable NLPs Detected (DC21041)     */
#घोषणा SISR_TRF   0x00000800      /* Transmit Remote Fault                  */
#घोषणा SISR_NSND  0x00000400      /* Non Stable NLPs Detected (DC21142)     */
#घोषणा SISR_ANR_FDS 0x00000400    /* Auto Negotiate Restart/Full Duplex Sel.*/
#घोषणा SISR_TRA   0x00000200      /* 10BASE-T Receive Port Activity         */
#घोषणा SISR_NRA   0x00000200      /* Non Selected Port Receive Activity     */
#घोषणा SISR_ARA   0x00000100      /* AUI Receive Port Activity              */
#घोषणा SISR_SRA   0x00000100      /* Selected Port Receive Activity         */
#घोषणा SISR_DAO   0x00000080      /* PLL All One                            */
#घोषणा SISR_DAZ   0x00000040      /* PLL All Zero                           */
#घोषणा SISR_DSP   0x00000020      /* PLL Self-Test Pass                     */
#घोषणा SISR_DSD   0x00000010      /* PLL Self-Test Done                     */
#घोषणा SISR_APS   0x00000008      /* Auto Polarity State                    */
#घोषणा SISR_LKF   0x00000004      /* Link Fail Status                       */
#घोषणा SISR_LS10  0x00000004      /* 10Mb/s Link Fail Status                */
#घोषणा SISR_NCR   0x00000002      /* Network Connection Error               */
#घोषणा SISR_LS100 0x00000002      /* 100Mb/s Link Fail Status               */
#घोषणा SISR_PAUI  0x00000001      /* AUI_TP Indication                      */
#घोषणा SISR_MRA   0x00000001      /* MII Receive Port Activity              */

#घोषणा ANS_NDIS   0x00000000      /* Nway disable                           */
#घोषणा ANS_TDIS   0x00001000      /* Transmit Disable                       */
#घोषणा ANS_ADET   0x00002000      /* Ability Detect                         */
#घोषणा ANS_ACK    0x00003000      /* Acknowledge                            */
#घोषणा ANS_CACK   0x00004000      /* Complete Acknowledge                   */
#घोषणा ANS_NWOK   0x00005000      /* Nway OK - FLP Link Good                */
#घोषणा ANS_LCHK   0x00006000      /* Link Check                             */

#घोषणा SISR_RST   0x00000301      /* CSR12 reset                            */
#घोषणा SISR_ANR   0x00001301      /* Autonegotiation restart                */

/*
** SIA Connectivity Register (DE4X5_SICR)
*/
#घोषणा SICR_SDM   0xffff0000       /* SIA Diagnostics Mode */
#घोषणा SICR_OE57  0x00008000       /* Output Enable 5 6 7 */
#घोषणा SICR_OE24  0x00004000       /* Output Enable 2 4 */
#घोषणा SICR_OE13  0x00002000       /* Output Enable 1 3 */
#घोषणा SICR_IE    0x00001000       /* Input Enable */
#घोषणा SICR_EXT   0x00000000       /* SIA MUX Select External SIA Mode */
#घोषणा SICR_D_SIA 0x00000400       /* SIA MUX Select Diagnostics - SIA Sigs */
#घोषणा SICR_DPLL  0x00000800       /* SIA MUX Select Diagnostics - DPLL Sigs*/
#घोषणा SICR_APLL  0x00000a00       /* SIA MUX Select Diagnostics - DPLL Sigs*/
#घोषणा SICR_D_RxM 0x00000c00       /* SIA MUX Select Diagnostics - RxM Sigs */
#घोषणा SICR_M_RxM 0x00000d00       /* SIA MUX Select Diagnostics - RxM Sigs */
#घोषणा SICR_LNKT  0x00000e00       /* SIA MUX Select Diagnostics - Link Test*/
#घोषणा SICR_SEL   0x00000f00       /* SIA MUX Select AUI or TP with LEDs */
#घोषणा SICR_ASE   0x00000080       /* APLL Start Enable*/
#घोषणा SICR_SIM   0x00000040       /* Serial Interface Input Multiplexer */
#घोषणा SICR_ENI   0x00000020       /* Encoder Input Multiplexer */
#घोषणा SICR_EDP   0x00000010       /* SIA PLL External Input Enable */
#घोषणा SICR_AUI   0x00000008       /* 10Base-T (0) or AUI (1) */
#घोषणा SICR_CAC   0x00000004       /* CSR Auto Configuration */
#घोषणा SICR_PS    0x00000002       /* Pin AUI/TP Selection */
#घोषणा SICR_SRL   0x00000001       /* SIA Reset */
#घोषणा SIA_RESET  0x00000000       /* SIA Reset Value */

/*
** SIA Transmit and Receive Register (DE4X5_STRR)
*/
#घोषणा STRR_TAS   0x00008000       /* 10Base-T/AUI Autosensing Enable */
#घोषणा STRR_SPP   0x00004000       /* Set Polarity Plus */
#घोषणा STRR_APE   0x00002000       /* Auto Polarity Enable */
#घोषणा STRR_LTE   0x00001000       /* Link Test Enable */
#घोषणा STRR_SQE   0x00000800       /* Signal Quality Enable */
#घोषणा STRR_CLD   0x00000400       /* Collision Detect Enable */
#घोषणा STRR_CSQ   0x00000200       /* Collision Squelch Enable */
#घोषणा STRR_RSQ   0x00000100       /* Receive Squelch Enable */
#घोषणा STRR_ANE   0x00000080       /* Auto Negotiate Enable */
#घोषणा STRR_HDE   0x00000040       /* Half Duplex Enable */
#घोषणा STRR_CPEN  0x00000030       /* Compensation Enable */
#घोषणा STRR_LSE   0x00000008       /* Link Pulse Send Enable */
#घोषणा STRR_DREN  0x00000004       /* Driver Enable */
#घोषणा STRR_LBK   0x00000002       /* Loopback Enable */
#घोषणा STRR_ECEN  0x00000001       /* Encoder Enable */
#घोषणा STRR_RESET 0xffffffff       /* Reset value क्रम STRR */

/*
** SIA General Register (DE4X5_SIGR)
*/
#घोषणा SIGR_RMI   0x40000000       /* Receive Match Interrupt */
#घोषणा SIGR_GI1   0x20000000       /* General Port Interrupt 1 */
#घोषणा SIGR_GI0   0x10000000       /* General Port Interrupt 0 */
#घोषणा SIGR_CWE   0x08000000       /* Control Write Enable */
#घोषणा SIGR_RME   0x04000000       /* Receive Match Enable */
#घोषणा SIGR_GEI1  0x02000000       /* GEP Interrupt Enable on Port 1 */
#घोषणा SIGR_GEI0  0x01000000       /* GEP Interrupt Enable on Port 0 */
#घोषणा SIGR_LGS3  0x00800000       /* LED/GEP3 Select */
#घोषणा SIGR_LGS2  0x00400000       /* LED/GEP2 Select */
#घोषणा SIGR_LGS1  0x00200000       /* LED/GEP1 Select */
#घोषणा SIGR_LGS0  0x00100000       /* LED/GEP0 Select */
#घोषणा SIGR_MD    0x000f0000       /* General Purpose Mode and Data */
#घोषणा SIGR_LV2   0x00008000       /* General Purpose LED2 value */
#घोषणा SIGR_LE2   0x00004000       /* General Purpose LED2 enable */
#घोषणा SIGR_FRL   0x00002000       /* Force Receiver Low */
#घोषणा SIGR_DPST  0x00001000       /* PLL Self Test Start */
#घोषणा SIGR_LSD   0x00000800       /* LED Stretch Disable */
#घोषणा SIGR_FLF   0x00000400       /* Force Link Fail */
#घोषणा SIGR_FUSQ  0x00000200       /* Force Unsquelch */
#घोषणा SIGR_TSCK  0x00000100       /* Test Clock */
#घोषणा SIGR_LV1   0x00000080       /* General Purpose LED1 value */
#घोषणा SIGR_LE1   0x00000040       /* General Purpose LED1 enable */
#घोषणा SIGR_RWR   0x00000020       /* Receive Watchकरोg Release */
#घोषणा SIGR_RWD   0x00000010       /* Receive Watchकरोg Disable */
#घोषणा SIGR_ABM   0x00000008       /* BNC: 0,  AUI:1 */
#घोषणा SIGR_JCK   0x00000004       /* Jabber Clock */
#घोषणा SIGR_HUJ   0x00000002       /* Host Unjab */
#घोषणा SIGR_JBD   0x00000001       /* Jabber Disable */
#घोषणा SIGR_RESET 0xffff0000       /* Reset value क्रम SIGR */

/*
** Receive Descriptor Bit Summary
*/
#घोषणा R_OWN      0x80000000       /* Own Bit */
#घोषणा RD_FF      0x40000000       /* Filtering Fail */
#घोषणा RD_FL      0x3fff0000       /* Frame Length */
#घोषणा RD_ES      0x00008000       /* Error Summary */
#घोषणा RD_LE      0x00004000       /* Length Error */
#घोषणा RD_DT      0x00003000       /* Data Type */
#घोषणा RD_RF      0x00000800       /* Runt Frame */
#घोषणा RD_MF      0x00000400       /* Multicast Frame */
#घोषणा RD_FS      0x00000200       /* First Descriptor */
#घोषणा RD_LS      0x00000100       /* Last Descriptor */
#घोषणा RD_TL      0x00000080       /* Frame Too Long */
#घोषणा RD_CS      0x00000040       /* Collision Seen */
#घोषणा RD_FT      0x00000020       /* Frame Type */
#घोषणा RD_RJ      0x00000010       /* Receive Watchकरोg */
#घोषणा RD_RE      0x00000008       /* Report on MII Error */
#घोषणा RD_DB      0x00000004       /* Dribbling Bit */
#घोषणा RD_CE      0x00000002       /* CRC Error */
#घोषणा RD_OF      0x00000001       /* Overflow */

#घोषणा RD_RER     0x02000000       /* Receive End Of Ring */
#घोषणा RD_RCH     0x01000000       /* Second Address Chained */
#घोषणा RD_RBS2    0x003ff800       /* Buffer 2 Size */
#घोषणा RD_RBS1    0x000007ff       /* Buffer 1 Size */

/*
** Transmit Descriptor Bit Summary
*/
#घोषणा T_OWN      0x80000000       /* Own Bit */
#घोषणा TD_ES      0x00008000       /* Error Summary */
#घोषणा TD_TO      0x00004000       /* Transmit Jabber Time-Out */
#घोषणा TD_LO      0x00000800       /* Loss Of Carrier */
#घोषणा TD_NC      0x00000400       /* No Carrier */
#घोषणा TD_LC      0x00000200       /* Late Collision */
#घोषणा TD_EC      0x00000100       /* Excessive Collisions */
#घोषणा TD_HF      0x00000080       /* Heartbeat Fail */
#घोषणा TD_CC      0x00000078       /* Collision Counter */
#घोषणा TD_LF      0x00000004       /* Link Fail */
#घोषणा TD_UF      0x00000002       /* Underflow Error */
#घोषणा TD_DE      0x00000001       /* Deferred */

#घोषणा TD_IC      0x80000000       /* Interrupt On Completion */
#घोषणा TD_LS      0x40000000       /* Last Segment */
#घोषणा TD_FS      0x20000000       /* First Segment */
#घोषणा TD_FT1     0x10000000       /* Filtering Type */
#घोषणा TD_SET     0x08000000       /* Setup Packet */
#घोषणा TD_AC      0x04000000       /* Add CRC Disable */
#घोषणा TD_TER     0x02000000       /* Transmit End Of Ring */
#घोषणा TD_TCH     0x01000000       /* Second Address Chained */
#घोषणा TD_DPD     0x00800000       /* Disabled Padding */
#घोषणा TD_FT0     0x00400000       /* Filtering Type */
#घोषणा TD_TBS2    0x003ff800       /* Buffer 2 Size */
#घोषणा TD_TBS1    0x000007ff       /* Buffer 1 Size */

#घोषणा PERFECT_F  0x00000000
#घोषणा HASH_F     TD_FT0
#घोषणा INVERSE_F  TD_FT1
#घोषणा HASH_O_F   (TD_FT1 | TD_F0)

/*
** Media / mode state machine definitions
** User selectable:
*/
#घोषणा TP              0x0040     /* 10Base-T (now equiv to _10Mb)        */
#घोषणा TP_NW           0x0002     /* 10Base-T with Nway                   */
#घोषणा BNC             0x0004     /* Thinwire                             */
#घोषणा AUI             0x0008     /* Thickwire                            */
#घोषणा BNC_AUI         0x0010     /* BNC/AUI on DC21040 indistinguishable */
#घोषणा _10Mb           0x0040     /* 10Mb/s Ethernet                      */
#घोषणा _100Mb          0x0080     /* 100Mb/s Ethernet                     */
#घोषणा AUTO            0x4000     /* Auto sense the media or speed        */

/*
** Internal states
*/
#घोषणा NC              0x0000     /* No Connection                        */
#घोषणा ANS             0x0020     /* Intermediate AutoNegotiation State   */
#घोषणा SPD_DET         0x0100     /* Parallel speed detection             */
#घोषणा INIT            0x0200     /* Initial state                        */
#घोषणा EXT_SIA         0x0400     /* External SIA क्रम motherboard chip    */
#घोषणा ANS_SUSPECT     0x0802     /* Suspect the ANS (TP) port is करोwn    */
#घोषणा TP_SUSPECT      0x0803     /* Suspect the TP port is करोwn          */
#घोषणा BNC_AUI_SUSPECT 0x0804     /* Suspect the BNC or AUI port is करोwn  */
#घोषणा EXT_SIA_SUSPECT 0x0805     /* Suspect the EXT SIA port is करोwn     */
#घोषणा BNC_SUSPECT     0x0806     /* Suspect the BNC port is करोwn         */
#घोषणा AUI_SUSPECT     0x0807     /* Suspect the AUI port is करोwn         */
#घोषणा MII             0x1000     /* MII on the 21143                     */

#घोषणा TIMER_CB        0x80000000 /* Timer callback detection             */

/*
** DE4X5 DEBUG Options
*/
#घोषणा DEBUG_NONE      0x0000     /* No DEBUG messages */
#घोषणा DEBUG_VERSION   0x0001     /* Prपूर्णांक version message */
#घोषणा DEBUG_MEDIA     0x0002     /* Prपूर्णांक media messages */
#घोषणा DEBUG_TX        0x0004     /* Prपूर्णांक TX (queue_pkt) messages */
#घोषणा DEBUG_RX        0x0008     /* Prपूर्णांक RX (de4x5_rx) messages */
#घोषणा DEBUG_SROM      0x0010     /* Prपूर्णांक SROM messages */
#घोषणा DEBUG_MII       0x0020     /* Prपूर्णांक MII messages */
#घोषणा DEBUG_OPEN      0x0040     /* Prपूर्णांक de4x5_खोलो() messages */
#घोषणा DEBUG_CLOSE     0x0080     /* Prपूर्णांक de4x5_बंद() messages */
#घोषणा DEBUG_PCICFG    0x0100
#घोषणा DEBUG_ALL       0x01ff

/*
** Miscellaneous
*/
#घोषणा PCI  0
#घोषणा EISA 1

#घोषणा DE4X5_HASH_TABLE_LEN   512       /* Bits */
#घोषणा DE4X5_HASH_BITS        0x01ff    /* 9 LS bits */

#घोषणा SETUP_FRAME_LEN  192       /* Bytes */
#घोषणा IMPERF_PA_OFFSET 156       /* Bytes */

#घोषणा POLL_DEMAND          1

#घोषणा LOST_MEDIA_THRESHOLD 3

#घोषणा MASK_INTERRUPTS      1
#घोषणा UNMASK_INTERRUPTS    0

#घोषणा DE4X5_STRLEN         8

#घोषणा DE4X5_INIT           0     /* Initialisation समय */
#घोषणा DE4X5_RUN            1     /* Run समय */

#घोषणा DE4X5_SAVE_STATE     0
#घोषणा DE4X5_RESTORE_STATE  1

/*
** Address Filtering Modes
*/
#घोषणा PERFECT              0     /* 16 perfect physical addresses */
#घोषणा HASH_PERF            1     /* 1 perfect, 512 multicast addresses */
#घोषणा PERFECT_REJ          2     /* Reject 16 perfect physical addresses */
#घोषणा ALL_HASH             3     /* Hashes all physical & multicast addrs */

#घोषणा ALL                  0     /* Clear out all the setup frame */
#घोषणा PHYS_ADDR_ONLY       1     /* Update the physical address only */

/*
** Adapter state
*/
#घोषणा INITIALISED          0     /* After h/w initialised and mem alloc'd */
#घोषणा CLOSED               1     /* Ready क्रम खोलोing */
#घोषणा OPEN                 2     /* Running */

/*
** Various रुको बार
*/
#घोषणा PDET_LINK_WAIT    1200    /* msecs to रुको क्रम link detect bits     */
#घोषणा ANS_FINISH_WAIT   1000    /* msecs to रुको क्रम link detect bits     */

/*
** IEEE OUIs क्रम various PHY venकरोr/chip combos - Reg 2 values only. Since
** the venकरोrs seem split 50-50 on how to calculate the OUI रेजिस्टर values
** anyway, just पढ़ोing Reg2 seems reasonable क्रम now [see de4x5_get_oui()].
*/
#घोषणा NATIONAL_TX 0x2000
#घोषणा BROADCOM_T4 0x03e0
#घोषणा SEEQ_T4     0x0016
#घोषणा CYPRESS_T4  0x0014

/*
** Speed Selection stuff
*/
#घोषणा SET_10Mb अणु\
  अगर ((lp->phy[lp->active].id) && (!lp->useSROM || lp->useMII)) अणु\
    omr = inl(DE4X5_OMR) & ~(OMR_TTM | OMR_PCS | OMR_SCR | OMR_FDX);\
    अगर ((lp->पंचांगp != MII_SR_ASSC) || (lp->स्वतःsense != AUTO)) अणु\
      mii_wr(MII_CR_10|(lp->fdx?MII_CR_FDM:0), MII_CR, lp->phy[lp->active].addr, DE4X5_MII);\
    पूर्ण\
    omr |= ((lp->fdx ? OMR_FDX : 0) | OMR_TTM);\
    outl(omr, DE4X5_OMR);\
    अगर (!lp->useSROM) lp->cache.gep = 0;\
  पूर्ण अन्यथा अगर (lp->useSROM && !lp->useMII) अणु\
    omr = (inl(DE4X5_OMR) & ~(OMR_PS | OMR_HBD | OMR_TTM | OMR_PCS | OMR_SCR | OMR_FDX));\
    omr |= (lp->fdx ? OMR_FDX : 0);\
    outl(omr | (lp->infoblock_csr6 & ~(OMR_SCR | OMR_HBD)), DE4X5_OMR);\
  पूर्ण अन्यथा अणु\
    omr = (inl(DE4X5_OMR) & ~(OMR_PS | OMR_HBD | OMR_TTM | OMR_PCS | OMR_SCR | OMR_FDX));\
    omr |= (lp->fdx ? OMR_FDX : 0);\
    outl(omr | OMR_SDP | OMR_TTM, DE4X5_OMR);\
    lp->cache.gep = (lp->fdx ? 0 : GEP_FDXD);\
    gep_wr(lp->cache.gep, dev);\
  पूर्ण\
पूर्ण

#घोषणा SET_100Mb अणु\
  अगर ((lp->phy[lp->active].id) && (!lp->useSROM || lp->useMII)) अणु\
    पूर्णांक fdx=0;\
    अगर (lp->phy[lp->active].id == NATIONAL_TX) अणु\
        mii_wr(mii_rd(0x18, lp->phy[lp->active].addr, DE4X5_MII) & ~0x2000,\
                      0x18, lp->phy[lp->active].addr, DE4X5_MII);\
    पूर्ण\
    omr = inl(DE4X5_OMR) & ~(OMR_TTM | OMR_PCS | OMR_SCR | OMR_FDX);\
    sr = mii_rd(MII_SR, lp->phy[lp->active].addr, DE4X5_MII);\
    अगर (!(sr & MII_ANA_T4AM) && lp->fdx) fdx=1;\
    अगर ((lp->पंचांगp != MII_SR_ASSC) || (lp->स्वतःsense != AUTO)) अणु\
      mii_wr(MII_CR_100|(fdx?MII_CR_FDM:0), MII_CR, lp->phy[lp->active].addr, DE4X5_MII);\
    पूर्ण\
    अगर (fdx) omr |= OMR_FDX;\
    outl(omr, DE4X5_OMR);\
    अगर (!lp->useSROM) lp->cache.gep = 0;\
  पूर्ण अन्यथा अगर (lp->useSROM && !lp->useMII) अणु\
    omr = (inl(DE4X5_OMR) & ~(OMR_PS | OMR_HBD | OMR_TTM | OMR_PCS | OMR_SCR | OMR_FDX));\
    omr |= (lp->fdx ? OMR_FDX : 0);\
    outl(omr | lp->infoblock_csr6, DE4X5_OMR);\
  पूर्ण अन्यथा अणु\
    omr = (inl(DE4X5_OMR) & ~(OMR_PS | OMR_HBD | OMR_TTM | OMR_PCS | OMR_SCR | OMR_FDX));\
    omr |= (lp->fdx ? OMR_FDX : 0);\
    outl(omr | OMR_SDP | OMR_PS | OMR_HBD | OMR_PCS | OMR_SCR, DE4X5_OMR);\
    lp->cache.gep = (lp->fdx ? 0 : GEP_FDXD) | GEP_MODE;\
    gep_wr(lp->cache.gep, dev);\
  पूर्ण\
पूर्ण

/* FIX ME so I करोn't jam 10Mb networks */
#घोषणा SET_100Mb_PDET अणु\
  अगर ((lp->phy[lp->active].id) && (!lp->useSROM || lp->useMII)) अणु\
    mii_wr(MII_CR_100|MII_CR_ASSE, MII_CR, lp->phy[lp->active].addr, DE4X5_MII);\
    omr = (inl(DE4X5_OMR) & ~(OMR_TTM | OMR_PCS | OMR_SCR | OMR_FDX));\
    outl(omr, DE4X5_OMR);\
  पूर्ण अन्यथा अगर (lp->useSROM && !lp->useMII) अणु\
    omr = (inl(DE4X5_OMR) & ~(OMR_TTM | OMR_PCS | OMR_SCR | OMR_FDX));\
    outl(omr, DE4X5_OMR);\
  पूर्ण अन्यथा अणु\
    omr = (inl(DE4X5_OMR) & ~(OMR_PS | OMR_HBD | OMR_TTM | OMR_PCS | OMR_SCR | OMR_FDX));\
    outl(omr | OMR_SDP | OMR_PS | OMR_HBD | OMR_PCS, DE4X5_OMR);\
    lp->cache.gep = (GEP_FDXD | GEP_MODE);\
    gep_wr(lp->cache.gep, dev);\
  पूर्ण\
पूर्ण

/*
** Include the IOCTL stuff
*/
#समावेश <linux/sockios.h>

काष्ठा de4x5_ioctl अणु
	अचिन्हित लघु cmd;                /* Command to run */
	अचिन्हित लघु len;                /* Length of the data buffer */
	अचिन्हित अक्षर  __user *data;       /* Poपूर्णांकer to the data buffer */
पूर्ण;

/*
** Recognised commands क्रम the driver
*/
#घोषणा DE4X5_GET_HWADDR	0x01 /* Get the hardware address */
#घोषणा DE4X5_SET_HWADDR	0x02 /* Set the hardware address */
/* 0x03 and 0x04 were used beक्रमe and are obsoleted now. Don't use them. */
#घोषणा DE4X5_SAY_BOO	        0x05 /* Say "Boo!" to the kernel log file */
#घोषणा DE4X5_GET_MCA   	0x06 /* Get a multicast address */
#घोषणा DE4X5_SET_MCA   	0x07 /* Set a multicast address */
#घोषणा DE4X5_CLR_MCA    	0x08 /* Clear a multicast address */
#घोषणा DE4X5_MCA_EN    	0x09 /* Enable a multicast address group */
#घोषणा DE4X5_GET_STATS  	0x0a /* Get the driver statistics */
#घोषणा DE4X5_CLR_STATS 	0x0b /* Zero out the driver statistics */
#घोषणा DE4X5_GET_OMR           0x0c /* Get the OMR Register contents */
#घोषणा DE4X5_SET_OMR           0x0d /* Set the OMR Register contents */
#घोषणा DE4X5_GET_REG           0x0e /* Get the DE4X5 Registers */

#घोषणा MOTO_SROM_BUG    (lp->active == 8 && (get_unaligned_le32(dev->dev_addr) & 0x00ffffff) == 0x3e0008)
