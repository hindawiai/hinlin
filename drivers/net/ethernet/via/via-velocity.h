<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (c) 1996, 2003 VIA Networking Technologies, Inc.
 * All rights reserved.
 *
 * File: via-velocity.h
 *
 * Purpose: Header file to define driver's निजी काष्ठाures.
 *
 * Author: Chuang Liang-Shing, AJ Jiang
 *
 * Date: Jan 24, 2003
 */


#अगर_अघोषित VELOCITY_H
#घोषणा VELOCITY_H

#घोषणा VELOCITY_TX_CSUM_SUPPORT

#घोषणा VELOCITY_NAME          "via-velocity"
#घोषणा VELOCITY_FULL_DRV_NAM  "VIA Networking Velocity Family Gigabit Ethernet Adapter Driver"
#घोषणा VELOCITY_VERSION       "1.15"

#घोषणा VELOCITY_IO_SIZE	256
#घोषणा VELOCITY_NAPI_WEIGHT	64

#घोषणा PKT_BUF_SZ          1540

#घोषणा MAX_UNITS           8
#घोषणा OPTION_DEFAULT      अणु [0 ... MAX_UNITS-1] = -1पूर्ण

#घोषणा REV_ID_VT6110       (0)

#घोषणा BYTE_REG_BITS_ON(x,p)       करो अणु ग_लिखोb(पढ़ोb((p))|(x),(p));पूर्ण जबतक (0)
#घोषणा WORD_REG_BITS_ON(x,p)       करो अणु ग_लिखोw(पढ़ोw((p))|(x),(p));पूर्ण जबतक (0)
#घोषणा DWORD_REG_BITS_ON(x,p)      करो अणु ग_लिखोl(पढ़ोl((p))|(x),(p));पूर्ण जबतक (0)

#घोषणा BYTE_REG_BITS_IS_ON(x,p)    (पढ़ोb((p)) & (x))
#घोषणा WORD_REG_BITS_IS_ON(x,p)    (पढ़ोw((p)) & (x))
#घोषणा DWORD_REG_BITS_IS_ON(x,p)   (पढ़ोl((p)) & (x))

#घोषणा BYTE_REG_BITS_OFF(x,p)      करो अणु ग_लिखोb(पढ़ोb((p)) & (~(x)),(p));पूर्ण जबतक (0)
#घोषणा WORD_REG_BITS_OFF(x,p)      करो अणु ग_लिखोw(पढ़ोw((p)) & (~(x)),(p));पूर्ण जबतक (0)
#घोषणा DWORD_REG_BITS_OFF(x,p)     करो अणु ग_लिखोl(पढ़ोl((p)) & (~(x)),(p));पूर्ण जबतक (0)

#घोषणा BYTE_REG_BITS_SET(x,m,p)    करो अणु ग_लिखोb( (पढ़ोb((p)) & (~(m))) |(x),(p));पूर्ण जबतक (0)
#घोषणा WORD_REG_BITS_SET(x,m,p)    करो अणु ग_लिखोw( (पढ़ोw((p)) & (~(m))) |(x),(p));पूर्ण जबतक (0)
#घोषणा DWORD_REG_BITS_SET(x,m,p)   करो अणु ग_लिखोl( (पढ़ोl((p)) & (~(m)))|(x),(p));पूर्ण  जबतक (0)

#घोषणा VAR_USED(p)     करो अणु(p)=(p);पूर्ण जबतक (0)

/*
 * Purpose: Structures क्रम MAX RX/TX descriptors.
 */


#घोषणा B_OWNED_BY_CHIP     1
#घोषणा B_OWNED_BY_HOST     0

/*
 * Bits in the RSR0 रेजिस्टर
 */

#घोषणा RSR_DETAG	cpu_to_le16(0x0080)
#घोषणा RSR_SNTAG	cpu_to_le16(0x0040)
#घोषणा RSR_RXER	cpu_to_le16(0x0020)
#घोषणा RSR_RL		cpu_to_le16(0x0010)
#घोषणा RSR_CE		cpu_to_le16(0x0008)
#घोषणा RSR_FAE		cpu_to_le16(0x0004)
#घोषणा RSR_CRC		cpu_to_le16(0x0002)
#घोषणा RSR_VIDM	cpu_to_le16(0x0001)

/*
 * Bits in the RSR1 रेजिस्टर
 */

#घोषणा RSR_RXOK	cpu_to_le16(0x8000) // rx OK
#घोषणा RSR_PFT		cpu_to_le16(0x4000) // Perfect filtering address match
#घोषणा RSR_MAR		cpu_to_le16(0x2000) // MAC accept multicast address packet
#घोषणा RSR_BAR		cpu_to_le16(0x1000) // MAC accept broadcast address packet
#घोषणा RSR_PHY		cpu_to_le16(0x0800) // MAC accept physical address packet
#घोषणा RSR_VTAG	cpu_to_le16(0x0400) // 802.1p/1q tagging packet indicator
#घोषणा RSR_STP		cpu_to_le16(0x0200) // start of packet
#घोषणा RSR_EDP		cpu_to_le16(0x0100) // end of packet

/*
 * Bits in the CSM रेजिस्टर
 */

#घोषणा CSM_IPOK            0x40	//IP Checksum validation ok
#घोषणा CSM_TUPOK           0x20	//TCP/UDP Checksum validation ok
#घोषणा CSM_FRAG            0x10	//Fragment IP datagram
#घोषणा CSM_IPKT            0x04	//Received an IP packet
#घोषणा CSM_TCPKT           0x02	//Received a TCP packet
#घोषणा CSM_UDPKT           0x01	//Received a UDP packet

/*
 * Bits in the TSR0 रेजिस्टर
 */

#घोषणा TSR0_ABT	cpu_to_le16(0x0080) // Tx पात because of excessive collision
#घोषणा TSR0_OWT	cpu_to_le16(0x0040) // Jumbo frame Tx पात
#घोषणा TSR0_OWC	cpu_to_le16(0x0020) // Out of winकरोw collision
#घोषणा TSR0_COLS	cpu_to_le16(0x0010) // experience collision in this transmit event
#घोषणा TSR0_NCR3	cpu_to_le16(0x0008) // collision retry counter[3]
#घोषणा TSR0_NCR2	cpu_to_le16(0x0004) // collision retry counter[2]
#घोषणा TSR0_NCR1	cpu_to_le16(0x0002) // collision retry counter[1]
#घोषणा TSR0_NCR0	cpu_to_le16(0x0001) // collision retry counter[0]
#घोषणा TSR0_TERR	cpu_to_le16(0x8000) //
#घोषणा TSR0_FDX	cpu_to_le16(0x4000) // current transaction is serviced by full duplex mode
#घोषणा TSR0_GMII	cpu_to_le16(0x2000) // current transaction is serviced by GMII mode
#घोषणा TSR0_LNKFL	cpu_to_le16(0x1000) // packet serviced during link करोwn
#घोषणा TSR0_SHDN	cpu_to_le16(0x0400) // shutकरोwn हाल
#घोषणा TSR0_CRS	cpu_to_le16(0x0200) // carrier sense lost
#घोषणा TSR0_CDH	cpu_to_le16(0x0100) // AQE test fail (CD heartbeat)

//
// Bits in the TCR0 रेजिस्टर
//
#घोषणा TCR0_TIC            0x80	// निश्चित पूर्णांकerrupt immediately जबतक descriptor has been send complete
#घोषणा TCR0_PIC            0x40	// priority पूर्णांकerrupt request, INA# is issued over adaptive पूर्णांकerrupt scheme
#घोषणा TCR0_VETAG          0x20	// enable VLAN tag
#घोषणा TCR0_IPCK           0x10	// request IP  checksum calculation.
#घोषणा TCR0_UDPCK          0x08	// request UDP checksum calculation.
#घोषणा TCR0_TCPCK          0x04	// request TCP checksum calculation.
#घोषणा TCR0_JMBO           0x02	// indicate a jumbo packet in GMAC side
#घोषणा TCR0_CRC            0x01	// disable CRC generation

#घोषणा TCPLS_NORMAL        3
#घोषणा TCPLS_START         2
#घोषणा TCPLS_END           1
#घोषणा TCPLS_MED           0


// max transmit or receive buffer size
#घोषणा CB_RX_BUF_SIZE     2048UL	// max buffer size
					// NOTE: must be multiple of 4

#घोषणा CB_MAX_RD_NUM       512	// MAX # of RD
#घोषणा CB_MAX_TD_NUM       256	// MAX # of TD

#घोषणा CB_INIT_RD_NUM_3119 128	// init # of RD, क्रम setup VT3119
#घोषणा CB_INIT_TD_NUM_3119 64	// init # of TD, क्रम setup VT3119

#घोषणा CB_INIT_RD_NUM      128	// init # of RD, क्रम setup शेष
#घोषणा CB_INIT_TD_NUM      64	// init # of TD, क्रम setup शेष

// क्रम 3119
#घोषणा CB_TD_RING_NUM      4	// # of TD rings.
#घोषणा CB_MAX_SEG_PER_PKT  7	// max data seg per packet (Tx)


/*
 *	If collisions excess 15 बार , tx will पात, and
 *	अगर tx fअगरo underflow, tx will fail
 *	we should try to resend it
 */

#घोषणा CB_MAX_TX_ABORT_RETRY   3

/*
 *	Receive descriptor
 */

काष्ठा rdesc0 अणु
	__le16 RSR;		/* Receive status */
	__le16 len;		/* bits 0--13; bit 15 - owner */
पूर्ण;

काष्ठा rdesc1 अणु
	__le16 PQTAG;
	u8 CSM;
	u8 IPKT;
पूर्ण;

क्रमागत अणु
	RX_INTEN = cpu_to_le16(0x8000)
पूर्ण;

काष्ठा rx_desc अणु
	काष्ठा rdesc0 rdesc0;
	काष्ठा rdesc1 rdesc1;
	__le32 pa_low;		/* Low 32 bit PCI address */
	__le16 pa_high;		/* Next 16 bit PCI address (48 total) */
	__le16 size;		/* bits 0--14 - frame size, bit 15 - enable पूर्णांक. */
पूर्ण __packed;

/*
 *	Transmit descriptor
 */

काष्ठा tdesc0 अणु
	__le16 TSR;		/* Transmit status रेजिस्टर */
	__le16 len;		/* bits 0--13 - size of frame, bit 15 - owner */
पूर्ण;

काष्ठा tdesc1 अणु
	__le16 vlan;
	u8 TCR;
	u8 cmd;			/* bits 0--1 - TCPLS, bits 4--7 - CMDZ */
पूर्ण __packed;

क्रमागत अणु
	TD_QUEUE = cpu_to_le16(0x8000)
पूर्ण;

काष्ठा td_buf अणु
	__le32 pa_low;
	__le16 pa_high;
	__le16 size;		/* bits 0--13 - size, bit 15 - queue */
पूर्ण __packed;

काष्ठा tx_desc अणु
	काष्ठा tdesc0 tdesc0;
	काष्ठा tdesc1 tdesc1;
	काष्ठा td_buf td_buf[7];
पूर्ण;

काष्ठा velocity_rd_info अणु
	काष्ठा sk_buff *skb;
	dma_addr_t skb_dma;
पूर्ण;

/*
 *	Used to track transmit side buffers.
 */

काष्ठा velocity_td_info अणु
	काष्ठा sk_buff *skb;
	पूर्णांक nskb_dma;
	dma_addr_t skb_dma[7];
पूर्ण;

क्रमागत  velocity_owner अणु
	OWNED_BY_HOST = 0,
	OWNED_BY_NIC = cpu_to_le16(0x8000)
पूर्ण;


/*
 *	MAC रेजिस्टरs and macros.
 */


#घोषणा MCAM_SIZE           64
#घोषणा VCAM_SIZE           64
#घोषणा TX_QUEUE_NO         4

#घोषणा MAX_HW_MIB_COUNTER  32
#घोषणा VELOCITY_MIN_MTU    (64)
#घोषणा VELOCITY_MAX_MTU    (9000)

/*
 *	Registers in the MAC
 */

#घोषणा MAC_REG_PAR         0x00	// physical address
#घोषणा MAC_REG_RCR         0x06
#घोषणा MAC_REG_TCR         0x07
#घोषणा MAC_REG_CR0_SET     0x08
#घोषणा MAC_REG_CR1_SET     0x09
#घोषणा MAC_REG_CR2_SET     0x0A
#घोषणा MAC_REG_CR3_SET     0x0B
#घोषणा MAC_REG_CR0_CLR     0x0C
#घोषणा MAC_REG_CR1_CLR     0x0D
#घोषणा MAC_REG_CR2_CLR     0x0E
#घोषणा MAC_REG_CR3_CLR     0x0F
#घोषणा MAC_REG_MAR         0x10
#घोषणा MAC_REG_CAM         0x10
#घोषणा MAC_REG_DEC_BASE_HI 0x18
#घोषणा MAC_REG_DBF_BASE_HI 0x1C
#घोषणा MAC_REG_ISR_CTL     0x20
#घोषणा MAC_REG_ISR_HOTMR   0x20
#घोषणा MAC_REG_ISR_TSUPTHR 0x20
#घोषणा MAC_REG_ISR_RSUPTHR 0x20
#घोषणा MAC_REG_ISR_CTL1    0x21
#घोषणा MAC_REG_TXE_SR      0x22
#घोषणा MAC_REG_RXE_SR      0x23
#घोषणा MAC_REG_ISR         0x24
#घोषणा MAC_REG_ISR0        0x24
#घोषणा MAC_REG_ISR1        0x25
#घोषणा MAC_REG_ISR2        0x26
#घोषणा MAC_REG_ISR3        0x27
#घोषणा MAC_REG_IMR         0x28
#घोषणा MAC_REG_IMR0        0x28
#घोषणा MAC_REG_IMR1        0x29
#घोषणा MAC_REG_IMR2        0x2A
#घोषणा MAC_REG_IMR3        0x2B
#घोषणा MAC_REG_TDCSR_SET   0x30
#घोषणा MAC_REG_RDCSR_SET   0x32
#घोषणा MAC_REG_TDCSR_CLR   0x34
#घोषणा MAC_REG_RDCSR_CLR   0x36
#घोषणा MAC_REG_RDBASE_LO   0x38
#घोषणा MAC_REG_RDINDX      0x3C
#घोषणा MAC_REG_TDBASE_LO   0x40
#घोषणा MAC_REG_RDCSIZE     0x50
#घोषणा MAC_REG_TDCSIZE     0x52
#घोषणा MAC_REG_TDINDX      0x54
#घोषणा MAC_REG_TDIDX0      0x54
#घोषणा MAC_REG_TDIDX1      0x56
#घोषणा MAC_REG_TDIDX2      0x58
#घोषणा MAC_REG_TDIDX3      0x5A
#घोषणा MAC_REG_PAUSE_TIMER 0x5C
#घोषणा MAC_REG_RBRDU       0x5E
#घोषणा MAC_REG_FIFO_TEST0  0x60
#घोषणा MAC_REG_FIFO_TEST1  0x64
#घोषणा MAC_REG_CAMADDR     0x68
#घोषणा MAC_REG_CAMCR       0x69
#घोषणा MAC_REG_GFTEST      0x6A
#घोषणा MAC_REG_FTSTCMD     0x6B
#घोषणा MAC_REG_MIICFG      0x6C
#घोषणा MAC_REG_MIISR       0x6D
#घोषणा MAC_REG_PHYSR0      0x6E
#घोषणा MAC_REG_PHYSR1      0x6F
#घोषणा MAC_REG_MIICR       0x70
#घोषणा MAC_REG_MIIADR      0x71
#घोषणा MAC_REG_MIIDATA     0x72
#घोषणा MAC_REG_SOFT_TIMER0 0x74
#घोषणा MAC_REG_SOFT_TIMER1 0x76
#घोषणा MAC_REG_CFGA        0x78
#घोषणा MAC_REG_CFGB        0x79
#घोषणा MAC_REG_CFGC        0x7A
#घोषणा MAC_REG_CFGD        0x7B
#घोषणा MAC_REG_DCFG0       0x7C
#घोषणा MAC_REG_DCFG1       0x7D
#घोषणा MAC_REG_MCFG0       0x7E
#घोषणा MAC_REG_MCFG1       0x7F

#घोषणा MAC_REG_TBIST       0x80
#घोषणा MAC_REG_RBIST       0x81
#घोषणा MAC_REG_PMCC        0x82
#घोषणा MAC_REG_STICKHW     0x83
#घोषणा MAC_REG_MIBCR       0x84
#घोषणा MAC_REG_EERSV       0x85
#घोषणा MAC_REG_REVID       0x86
#घोषणा MAC_REG_MIBREAD     0x88
#घोषणा MAC_REG_BPMA        0x8C
#घोषणा MAC_REG_EEWR_DATA   0x8C
#घोषणा MAC_REG_BPMD_WR     0x8F
#घोषणा MAC_REG_BPCMD       0x90
#घोषणा MAC_REG_BPMD_RD     0x91
#घोषणा MAC_REG_EECHKSUM    0x92
#घोषणा MAC_REG_EECSR       0x93
#घोषणा MAC_REG_EERD_DATA   0x94
#घोषणा MAC_REG_EADDR       0x96
#घोषणा MAC_REG_EMBCMD      0x97
#घोषणा MAC_REG_JMPSR0      0x98
#घोषणा MAC_REG_JMPSR1      0x99
#घोषणा MAC_REG_JMPSR2      0x9A
#घोषणा MAC_REG_JMPSR3      0x9B
#घोषणा MAC_REG_CHIPGSR     0x9C
#घोषणा MAC_REG_TESTCFG     0x9D
#घोषणा MAC_REG_DEBUG       0x9E
#घोषणा MAC_REG_CHIPGCR     0x9F	/* Chip Operation and Diagnostic Control */
#घोषणा MAC_REG_WOLCR0_SET  0xA0
#घोषणा MAC_REG_WOLCR1_SET  0xA1
#घोषणा MAC_REG_PWCFG_SET   0xA2
#घोषणा MAC_REG_WOLCFG_SET  0xA3
#घोषणा MAC_REG_WOLCR0_CLR  0xA4
#घोषणा MAC_REG_WOLCR1_CLR  0xA5
#घोषणा MAC_REG_PWCFG_CLR   0xA6
#घोषणा MAC_REG_WOLCFG_CLR  0xA7
#घोषणा MAC_REG_WOLSR0_SET  0xA8
#घोषणा MAC_REG_WOLSR1_SET  0xA9
#घोषणा MAC_REG_WOLSR0_CLR  0xAC
#घोषणा MAC_REG_WOLSR1_CLR  0xAD
#घोषणा MAC_REG_PATRN_CRC0  0xB0
#घोषणा MAC_REG_PATRN_CRC1  0xB2
#घोषणा MAC_REG_PATRN_CRC2  0xB4
#घोषणा MAC_REG_PATRN_CRC3  0xB6
#घोषणा MAC_REG_PATRN_CRC4  0xB8
#घोषणा MAC_REG_PATRN_CRC5  0xBA
#घोषणा MAC_REG_PATRN_CRC6  0xBC
#घोषणा MAC_REG_PATRN_CRC7  0xBE
#घोषणा MAC_REG_BYTEMSK0_0  0xC0
#घोषणा MAC_REG_BYTEMSK0_1  0xC4
#घोषणा MAC_REG_BYTEMSK0_2  0xC8
#घोषणा MAC_REG_BYTEMSK0_3  0xCC
#घोषणा MAC_REG_BYTEMSK1_0  0xD0
#घोषणा MAC_REG_BYTEMSK1_1  0xD4
#घोषणा MAC_REG_BYTEMSK1_2  0xD8
#घोषणा MAC_REG_BYTEMSK1_3  0xDC
#घोषणा MAC_REG_BYTEMSK2_0  0xE0
#घोषणा MAC_REG_BYTEMSK2_1  0xE4
#घोषणा MAC_REG_BYTEMSK2_2  0xE8
#घोषणा MAC_REG_BYTEMSK2_3  0xEC
#घोषणा MAC_REG_BYTEMSK3_0  0xF0
#घोषणा MAC_REG_BYTEMSK3_1  0xF4
#घोषणा MAC_REG_BYTEMSK3_2  0xF8
#घोषणा MAC_REG_BYTEMSK3_3  0xFC

/*
 *	Bits in the RCR रेजिस्टर
 */

#घोषणा RCR_AS              0x80
#घोषणा RCR_AP              0x40
#घोषणा RCR_AL              0x20
#घोषणा RCR_PROM            0x10
#घोषणा RCR_AB              0x08
#घोषणा RCR_AM              0x04
#घोषणा RCR_AR              0x02
#घोषणा RCR_SEP             0x01

/*
 *	Bits in the TCR रेजिस्टर
 */

#घोषणा TCR_TB2BDIS         0x80
#घोषणा TCR_COLTMC1         0x08
#घोषणा TCR_COLTMC0         0x04
#घोषणा TCR_LB1             0x02	/* loopback[1] */
#घोषणा TCR_LB0             0x01	/* loopback[0] */

/*
 *	Bits in the CR0 रेजिस्टर
 */

#घोषणा CR0_TXON            0x00000008UL
#घोषणा CR0_RXON            0x00000004UL
#घोषणा CR0_STOP            0x00000002UL	/* stop MAC, शेष = 1 */
#घोषणा CR0_STRT            0x00000001UL	/* start MAC */
#घोषणा CR0_SFRST           0x00008000UL	/* software reset */
#घोषणा CR0_TM1EN           0x00004000UL
#घोषणा CR0_TM0EN           0x00002000UL
#घोषणा CR0_DPOLL           0x00000800UL	/* disable rx/tx स्वतः polling */
#घोषणा CR0_DISAU           0x00000100UL
#घोषणा CR0_XONEN           0x00800000UL
#घोषणा CR0_FDXTFCEN        0x00400000UL	/* full-duplex TX flow control enable */
#घोषणा CR0_FDXRFCEN        0x00200000UL	/* full-duplex RX flow control enable */
#घोषणा CR0_HDXFCEN         0x00100000UL	/* half-duplex flow control enable */
#घोषणा CR0_XHITH1          0x00080000UL	/* TX XON high threshold 1 */
#घोषणा CR0_XHITH0          0x00040000UL	/* TX XON high threshold 0 */
#घोषणा CR0_XLTH1           0x00020000UL	/* TX छोड़ो frame low threshold 1 */
#घोषणा CR0_XLTH0           0x00010000UL	/* TX छोड़ो frame low threshold 0 */
#घोषणा CR0_GSPRST          0x80000000UL
#घोषणा CR0_FORSRST         0x40000000UL
#घोषणा CR0_FPHYRST         0x20000000UL
#घोषणा CR0_DIAG            0x10000000UL
#घोषणा CR0_INTPCTL         0x04000000UL
#घोषणा CR0_GINTMSK1        0x02000000UL
#घोषणा CR0_GINTMSK0        0x01000000UL

/*
 *	Bits in the CR1 रेजिस्टर
 */

#घोषणा CR1_SFRST           0x80	/* software reset */
#घोषणा CR1_TM1EN           0x40
#घोषणा CR1_TM0EN           0x20
#घोषणा CR1_DPOLL           0x08	/* disable rx/tx स्वतः polling */
#घोषणा CR1_DISAU           0x01

/*
 *	Bits in the CR2 रेजिस्टर
 */

#घोषणा CR2_XONEN           0x80
#घोषणा CR2_FDXTFCEN        0x40	/* full-duplex TX flow control enable */
#घोषणा CR2_FDXRFCEN        0x20	/* full-duplex RX flow control enable */
#घोषणा CR2_HDXFCEN         0x10	/* half-duplex flow control enable */
#घोषणा CR2_XHITH1          0x08	/* TX XON high threshold 1 */
#घोषणा CR2_XHITH0          0x04	/* TX XON high threshold 0 */
#घोषणा CR2_XLTH1           0x02	/* TX छोड़ो frame low threshold 1 */
#घोषणा CR2_XLTH0           0x01	/* TX छोड़ो frame low threshold 0 */

/*
 *	Bits in the CR3 रेजिस्टर
 */

#घोषणा CR3_GSPRST          0x80
#घोषणा CR3_FORSRST         0x40
#घोषणा CR3_FPHYRST         0x20
#घोषणा CR3_DIAG            0x10
#घोषणा CR3_INTPCTL         0x04
#घोषणा CR3_GINTMSK1        0x02
#घोषणा CR3_GINTMSK0        0x01

#घोषणा ISRCTL_UDPINT       0x8000
#घोषणा ISRCTL_TSUPDIS      0x4000
#घोषणा ISRCTL_RSUPDIS      0x2000
#घोषणा ISRCTL_PMSK1        0x1000
#घोषणा ISRCTL_PMSK0        0x0800
#घोषणा ISRCTL_INTPD        0x0400
#घोषणा ISRCTL_HCRLD        0x0200
#घोषणा ISRCTL_SCRLD        0x0100

/*
 *	Bits in the ISR_CTL1 रेजिस्टर
 */

#घोषणा ISRCTL1_UDPINT      0x80
#घोषणा ISRCTL1_TSUPDIS     0x40
#घोषणा ISRCTL1_RSUPDIS     0x20
#घोषणा ISRCTL1_PMSK1       0x10
#घोषणा ISRCTL1_PMSK0       0x08
#घोषणा ISRCTL1_INTPD       0x04
#घोषणा ISRCTL1_HCRLD       0x02
#घोषणा ISRCTL1_SCRLD       0x01

/*
 *	Bits in the TXE_SR रेजिस्टर
 */

#घोषणा TXESR_TFDBS         0x08
#घोषणा TXESR_TDWBS         0x04
#घोषणा TXESR_TDRBS         0x02
#घोषणा TXESR_TDSTR         0x01

/*
 *	Bits in the RXE_SR रेजिस्टर
 */

#घोषणा RXESR_RFDBS         0x08
#घोषणा RXESR_RDWBS         0x04
#घोषणा RXESR_RDRBS         0x02
#घोषणा RXESR_RDSTR         0x01

/*
 *	Bits in the ISR रेजिस्टर
 */

#घोषणा ISR_ISR3            0x80000000UL
#घोषणा ISR_ISR2            0x40000000UL
#घोषणा ISR_ISR1            0x20000000UL
#घोषणा ISR_ISR0            0x10000000UL
#घोषणा ISR_TXSTLI          0x02000000UL
#घोषणा ISR_RXSTLI          0x01000000UL
#घोषणा ISR_HFLD            0x00800000UL
#घोषणा ISR_UDPI            0x00400000UL
#घोषणा ISR_MIBFI           0x00200000UL
#घोषणा ISR_SHDNI           0x00100000UL
#घोषणा ISR_PHYI            0x00080000UL
#घोषणा ISR_PWEI            0x00040000UL
#घोषणा ISR_TMR1I           0x00020000UL
#घोषणा ISR_TMR0I           0x00010000UL
#घोषणा ISR_SRCI            0x00008000UL
#घोषणा ISR_LSTPEI          0x00004000UL
#घोषणा ISR_LSTEI           0x00002000UL
#घोषणा ISR_OVFI            0x00001000UL
#घोषणा ISR_FLONI           0x00000800UL
#घोषणा ISR_RACEI           0x00000400UL
#घोषणा ISR_TXWB1I          0x00000200UL
#घोषणा ISR_TXWB0I          0x00000100UL
#घोषणा ISR_PTX3I           0x00000080UL
#घोषणा ISR_PTX2I           0x00000040UL
#घोषणा ISR_PTX1I           0x00000020UL
#घोषणा ISR_PTX0I           0x00000010UL
#घोषणा ISR_PTXI            0x00000008UL
#घोषणा ISR_PRXI            0x00000004UL
#घोषणा ISR_PPTXI           0x00000002UL
#घोषणा ISR_PPRXI           0x00000001UL

/*
 *	Bits in the IMR रेजिस्टर
 */

#घोषणा IMR_TXSTLM          0x02000000UL
#घोषणा IMR_UDPIM           0x00400000UL
#घोषणा IMR_MIBFIM          0x00200000UL
#घोषणा IMR_SHDNIM          0x00100000UL
#घोषणा IMR_PHYIM           0x00080000UL
#घोषणा IMR_PWEIM           0x00040000UL
#घोषणा IMR_TMR1IM          0x00020000UL
#घोषणा IMR_TMR0IM          0x00010000UL

#घोषणा IMR_SRCIM           0x00008000UL
#घोषणा IMR_LSTPEIM         0x00004000UL
#घोषणा IMR_LSTEIM          0x00002000UL
#घोषणा IMR_OVFIM           0x00001000UL
#घोषणा IMR_FLONIM          0x00000800UL
#घोषणा IMR_RACEIM          0x00000400UL
#घोषणा IMR_TXWB1IM         0x00000200UL
#घोषणा IMR_TXWB0IM         0x00000100UL

#घोषणा IMR_PTX3IM          0x00000080UL
#घोषणा IMR_PTX2IM          0x00000040UL
#घोषणा IMR_PTX1IM          0x00000020UL
#घोषणा IMR_PTX0IM          0x00000010UL
#घोषणा IMR_PTXIM           0x00000008UL
#घोषणा IMR_PRXIM           0x00000004UL
#घोषणा IMR_PPTXIM          0x00000002UL
#घोषणा IMR_PPRXIM          0x00000001UL

/* 0x0013FB0FUL  =  initial value of IMR */

#घोषणा INT_MASK_DEF        (IMR_PPTXIM|IMR_PPRXIM|IMR_PTXIM|IMR_PRXIM|\
                            IMR_PWEIM|IMR_TXWB0IM|IMR_TXWB1IM|IMR_FLONIM|\
                            IMR_OVFIM|IMR_LSTEIM|IMR_LSTPEIM|IMR_SRCIM|IMR_MIBFIM|\
                            IMR_SHDNIM|IMR_TMR1IM|IMR_TMR0IM|IMR_TXSTLM)

/*
 *	Bits in the TDCSR0/1, RDCSR0 रेजिस्टर
 */

#घोषणा TRDCSR_DEAD         0x0008
#घोषणा TRDCSR_WAK          0x0004
#घोषणा TRDCSR_ACT          0x0002
#घोषणा TRDCSR_RUN	    0x0001

/*
 *	Bits in the CAMADDR रेजिस्टर
 */

#घोषणा CAMADDR_CAMEN       0x80
#घोषणा CAMADDR_VCAMSL      0x40

/*
 *	Bits in the CAMCR रेजिस्टर
 */

#घोषणा CAMCR_PS1           0x80
#घोषणा CAMCR_PS0           0x40
#घोषणा CAMCR_AITRPKT       0x20
#घोषणा CAMCR_AITR16        0x10
#घोषणा CAMCR_CAMRD         0x08
#घोषणा CAMCR_CAMWR         0x04
#घोषणा CAMCR_PS_CAM_MASK   0x40
#घोषणा CAMCR_PS_CAM_DATA   0x80
#घोषणा CAMCR_PS_MAR        0x00

/*
 *	Bits in the MIICFG रेजिस्टर
 */

#घोषणा MIICFG_MPO1         0x80
#घोषणा MIICFG_MPO0         0x40
#घोषणा MIICFG_MFDC         0x20

/*
 *	Bits in the MIISR रेजिस्टर
 */

#घोषणा MIISR_MIDLE         0x80

/*
 *	 Bits in the PHYSR0 रेजिस्टर
 */

#घोषणा PHYSR0_PHYRST       0x80
#घोषणा PHYSR0_LINKGD       0x40
#घोषणा PHYSR0_FDPX         0x10
#घोषणा PHYSR0_SPDG         0x08
#घोषणा PHYSR0_SPD10        0x04
#घोषणा PHYSR0_RXFLC        0x02
#घोषणा PHYSR0_TXFLC        0x01

/*
 *	Bits in the PHYSR1 रेजिस्टर
 */

#घोषणा PHYSR1_PHYTBI       0x01

/*
 *	Bits in the MIICR रेजिस्टर
 */

#घोषणा MIICR_MAUTO         0x80
#घोषणा MIICR_RCMD          0x40
#घोषणा MIICR_WCMD          0x20
#घोषणा MIICR_MDPM          0x10
#घोषणा MIICR_MOUT          0x08
#घोषणा MIICR_MDO           0x04
#घोषणा MIICR_MDI           0x02
#घोषणा MIICR_MDC           0x01

/*
 *	Bits in the MIIADR रेजिस्टर
 */

#घोषणा MIIADR_SWMPL        0x80

/*
 *	Bits in the CFGA रेजिस्टर
 */

#घोषणा CFGA_PMHCTG         0x08
#घोषणा CFGA_GPIO1PD        0x04
#घोषणा CFGA_ABSHDN         0x02
#घोषणा CFGA_PACPI          0x01

/*
 *	Bits in the CFGB रेजिस्टर
 */

#घोषणा CFGB_GTCKOPT        0x80
#घोषणा CFGB_MIIOPT         0x40
#घोषणा CFGB_CRSEOPT        0x20
#घोषणा CFGB_OFSET          0x10
#घोषणा CFGB_CRANDOM        0x08
#घोषणा CFGB_CAP            0x04
#घोषणा CFGB_MBA            0x02
#घोषणा CFGB_BAKOPT         0x01

/*
 *	Bits in the CFGC रेजिस्टर
 */

#घोषणा CFGC_EELOAD         0x80
#घोषणा CFGC_BROPT          0x40
#घोषणा CFGC_DLYEN          0x20
#घोषणा CFGC_DTSEL          0x10
#घोषणा CFGC_BTSEL          0x08
#घोषणा CFGC_BPS2           0x04	/* bootrom select[2] */
#घोषणा CFGC_BPS1           0x02	/* bootrom select[1] */
#घोषणा CFGC_BPS0           0x01	/* bootrom select[0] */

/*
 * Bits in the CFGD रेजिस्टर
 */

#घोषणा CFGD_IODIS          0x80
#घोषणा CFGD_MSLVDACEN      0x40
#घोषणा CFGD_CFGDACEN       0x20
#घोषणा CFGD_PCI64EN        0x10
#घोषणा CFGD_HTMRL4         0x08

/*
 *	Bits in the DCFG1 रेजिस्टर
 */

#घोषणा DCFG_XMWI           0x8000
#घोषणा DCFG_XMRM           0x4000
#घोषणा DCFG_XMRL           0x2000
#घोषणा DCFG_PERDIS         0x1000
#घोषणा DCFG_MRWAIT         0x0400
#घोषणा DCFG_MWWAIT         0x0200
#घोषणा DCFG_LATMEN         0x0100

/*
 *	Bits in the MCFG0 रेजिस्टर
 */

#घोषणा MCFG_RXARB          0x0080
#घोषणा MCFG_RFT1           0x0020
#घोषणा MCFG_RFT0           0x0010
#घोषणा MCFG_LOWTHOPT       0x0008
#घोषणा MCFG_PQEN           0x0004
#घोषणा MCFG_RTGOPT         0x0002
#घोषणा MCFG_VIDFR          0x0001

/*
 *	Bits in the MCFG1 रेजिस्टर
 */

#घोषणा MCFG_TXARB          0x8000
#घोषणा MCFG_TXQBK1         0x0800
#घोषणा MCFG_TXQBK0         0x0400
#घोषणा MCFG_TXQNOBK        0x0200
#घोषणा MCFG_SNAPOPT        0x0100

/*
 *	Bits in the PMCC  रेजिस्टर
 */

#घोषणा PMCC_DSI            0x80
#घोषणा PMCC_D2_DIS         0x40
#घोषणा PMCC_D1_DIS         0x20
#घोषणा PMCC_D3C_EN         0x10
#घोषणा PMCC_D3H_EN         0x08
#घोषणा PMCC_D2_EN          0x04
#घोषणा PMCC_D1_EN          0x02
#घोषणा PMCC_D0_EN          0x01

/*
 *	Bits in STICKHW
 */

#घोषणा STICKHW_SWPTAG      0x10
#घोषणा STICKHW_WOLSR       0x08
#घोषणा STICKHW_WOLEN       0x04
#घोषणा STICKHW_DS1         0x02	/* R/W by software/cfg cycle */
#घोषणा STICKHW_DS0         0x01	/* suspend well DS ग_लिखो port */

/*
 *	Bits in the MIBCR रेजिस्टर
 */

#घोषणा MIBCR_MIBISTOK      0x80
#घोषणा MIBCR_MIBISTGO      0x40
#घोषणा MIBCR_MIBINC        0x20
#घोषणा MIBCR_MIBHI         0x10
#घोषणा MIBCR_MIBFRZ        0x08
#घोषणा MIBCR_MIBFLSH       0x04
#घोषणा MIBCR_MPTRINI       0x02
#घोषणा MIBCR_MIBCLR        0x01

/*
 *	Bits in the EERSV रेजिस्टर
 */

#घोषणा EERSV_BOOT_RPL      ((u8) 0x01)	 /* Boot method selection क्रम VT6110 */

#घोषणा EERSV_BOOT_MASK     ((u8) 0x06)
#घोषणा EERSV_BOOT_INT19    ((u8) 0x00)
#घोषणा EERSV_BOOT_INT18    ((u8) 0x02)
#घोषणा EERSV_BOOT_LOCAL    ((u8) 0x04)
#घोषणा EERSV_BOOT_BEV      ((u8) 0x06)


/*
 *	Bits in BPCMD
 */

#घोषणा BPCMD_BPDNE         0x80
#घोषणा BPCMD_EBPWR         0x02
#घोषणा BPCMD_EBPRD         0x01

/*
 *	Bits in the EECSR रेजिस्टर
 */

#घोषणा EECSR_EMBP          0x40	/* eeprom embedded programming */
#घोषणा EECSR_RELOAD        0x20	/* eeprom content reload */
#घोषणा EECSR_DPM           0x10	/* eeprom direct programming */
#घोषणा EECSR_ECS           0x08	/* eeprom CS pin */
#घोषणा EECSR_ECK           0x04	/* eeprom CK pin */
#घोषणा EECSR_EDI           0x02	/* eeprom DI pin */
#घोषणा EECSR_EDO           0x01	/* eeprom DO pin */

/*
 *	Bits in the EMBCMD रेजिस्टर
 */

#घोषणा EMBCMD_EDONE        0x80
#घोषणा EMBCMD_EWDIS        0x08
#घोषणा EMBCMD_EWEN         0x04
#घोषणा EMBCMD_EWR          0x02
#घोषणा EMBCMD_ERD          0x01

/*
 *	Bits in TESTCFG रेजिस्टर
 */

#घोषणा TESTCFG_HBDIS       0x80

/*
 *	Bits in CHIPGCR रेजिस्टर
 */

#घोषणा CHIPGCR_FCGMII      0x80	/* क्रमce GMII (अन्यथा MII only) */
#घोषणा CHIPGCR_FCFDX       0x40	/* क्रमce full duplex */
#घोषणा CHIPGCR_FCRESV      0x20
#घोषणा CHIPGCR_FCMODE      0x10	/* enable MAC क्रमced mode */
#घोषणा CHIPGCR_LPSOPT      0x08
#घोषणा CHIPGCR_TM1US       0x04
#घोषणा CHIPGCR_TM0US       0x02
#घोषणा CHIPGCR_PHYINTEN    0x01

/*
 *	Bits in WOLCR0
 */

#घोषणा WOLCR_MSWOLEN7      0x0080	/* enable pattern match filtering */
#घोषणा WOLCR_MSWOLEN6      0x0040
#घोषणा WOLCR_MSWOLEN5      0x0020
#घोषणा WOLCR_MSWOLEN4      0x0010
#घोषणा WOLCR_MSWOLEN3      0x0008
#घोषणा WOLCR_MSWOLEN2      0x0004
#घोषणा WOLCR_MSWOLEN1      0x0002
#घोषणा WOLCR_MSWOLEN0      0x0001
#घोषणा WOLCR_ARP_EN        0x0001

/*
 *	Bits in WOLCR1
 */

#घोषणा WOLCR_LINKOFF_EN      0x0800	/* link off detected enable */
#घोषणा WOLCR_LINKON_EN       0x0400	/* link on detected enable */
#घोषणा WOLCR_MAGIC_EN        0x0200	/* magic packet filter enable */
#घोषणा WOLCR_UNICAST_EN      0x0100	/* unicast filter enable */


/*
 *	Bits in PWCFG
 */

#घोषणा PWCFG_PHYPWOPT          0x80	/* पूर्णांकernal MII I/F timing */
#घोषणा PWCFG_PCISTICK          0x40	/* PCI sticky R/W enable */
#घोषणा PWCFG_WOLTYPE           0x20	/* pulse(1) or button (0) */
#घोषणा PWCFG_LEGCY_WOL         0x10
#घोषणा PWCFG_PMCSR_PME_SR      0x08
#घोषणा PWCFG_PMCSR_PME_EN      0x04	/* control by PCISTICK */
#घोषणा PWCFG_LEGACY_WOLSR      0x02	/* Legacy WOL_SR shaकरोw */
#घोषणा PWCFG_LEGACY_WOLEN      0x01	/* Legacy WOL_EN shaकरोw */

/*
 *	Bits in WOLCFG
 */

#घोषणा WOLCFG_PMEOVR           0x80	/* क्रम legacy use, क्रमce PMEEN always */
#घोषणा WOLCFG_SAM              0x20	/* accept multicast हाल reset, शेष=0 */
#घोषणा WOLCFG_SAB              0x10	/* accept broadcast हाल reset, शेष=0 */
#घोषणा WOLCFG_SMIIACC          0x08	/* ?? */
#घोषणा WOLCFG_SGENWH           0x02
#घोषणा WOLCFG_PHYINTEN         0x01	/* 0:PHYINT trigger enable, 1:use पूर्णांकernal MII
					  to report status change */
/*
 *	Bits in WOLSR1
 */

#घोषणा WOLSR_LINKOFF_INT      0x0800
#घोषणा WOLSR_LINKON_INT       0x0400
#घोषणा WOLSR_MAGIC_INT        0x0200
#घोषणा WOLSR_UNICAST_INT      0x0100

/*
 *	Ethernet address filter type
 */

#घोषणा PKT_TYPE_NONE               0x0000	/* Turn off receiver */
#घोषणा PKT_TYPE_सूचीECTED           0x0001	/* obselete, directed address is always accepted */
#घोषणा PKT_TYPE_MULTICAST          0x0002
#घोषणा PKT_TYPE_ALL_MULTICAST      0x0004
#घोषणा PKT_TYPE_BROADCAST          0x0008
#घोषणा PKT_TYPE_PROMISCUOUS        0x0020
#घोषणा PKT_TYPE_LONG               0x2000	/* NOTE.... the definition of LONG is >2048 bytes in our chip */
#घोषणा PKT_TYPE_RUNT               0x4000
#घोषणा PKT_TYPE_ERROR              0x8000	/* Accept error packets, e.g. CRC error */

/*
 *	Loopback mode
 */

#घोषणा MAC_LB_NONE         0x00
#घोषणा MAC_LB_INTERNAL     0x01
#घोषणा MAC_LB_EXTERNAL     0x02

/*
 *	Enabled mask value of irq
 */

#अगर defined(_SIM)
#घोषणा IMR_MASK_VALUE      0x0033FF0FUL	/* initial value of IMR
						   set IMR0 to 0x0F according to spec */

#अन्यथा
#घोषणा IMR_MASK_VALUE      0x0013FB0FUL	/* initial value of IMR
						   ignore MIBFI,RACEI to
						   reduce पूर्णांकr. frequency
						   NOTE.... करो not enable NoBuf पूर्णांक mask at driver driver
						      when (1) NoBuf -> RxThreshold = SF
							   (2) OK    -> RxThreshold = original value
						 */
#पूर्ण_अगर

/*
 *	Revision id
 */

#घोषणा REV_ID_VT3119_A0	0x00
#घोषणा REV_ID_VT3119_A1	0x01
#घोषणा REV_ID_VT3216_A0	0x10

/*
 *	Max समय out delay समय
 */

#घोषणा W_MAX_TIMEOUT       0x0FFFU


/*
 *	MAC रेजिस्टरs as a काष्ठाure. Cannot be directly accessed this
 *	way but generates offsets क्रम पढ़ोl/ग_लिखोl() calls
 */

काष्ठा mac_regs अणु
	अस्थिर u8 PAR[6];		/* 0x00 */
	अस्थिर u8 RCR;
	अस्थिर u8 TCR;

	अस्थिर __le32 CR0Set;		/* 0x08 */
	अस्थिर __le32 CR0Clr;		/* 0x0C */

	अस्थिर u8 MARCAM[8];		/* 0x10 */

	अस्थिर __le32 DecBaseHi;	/* 0x18 */
	अस्थिर __le16 DbfBaseHi;	/* 0x1C */
	अस्थिर __le16 reserved_1E;

	अस्थिर __le16 ISRCTL;		/* 0x20 */
	अस्थिर u8 TXESR;
	अस्थिर u8 RXESR;

	अस्थिर __le32 ISR;		/* 0x24 */
	अस्थिर __le32 IMR;

	अस्थिर __le32 TDStatusPort;	/* 0x2C */

	अस्थिर __le16 TDCSRSet;	/* 0x30 */
	अस्थिर u8 RDCSRSet;
	अस्थिर u8 reserved_33;
	अस्थिर __le16 TDCSRClr;
	अस्थिर u8 RDCSRClr;
	अस्थिर u8 reserved_37;

	अस्थिर __le32 RDBaseLo;	/* 0x38 */
	अस्थिर __le16 RDIdx;		/* 0x3C */
	अस्थिर u8 TQETMR;		/* 0x3E, VT3216 and above only */
	अस्थिर u8 RQETMR;		/* 0x3F, VT3216 and above only */

	अस्थिर __le32 TDBaseLo[4];	/* 0x40 */

	अस्थिर __le16 RDCSize;	/* 0x50 */
	अस्थिर __le16 TDCSize;	/* 0x52 */
	अस्थिर __le16 TDIdx[4];	/* 0x54 */
	अस्थिर __le16 tx_छोड़ो_समयr;	/* 0x5C */
	अस्थिर __le16 RBRDU;		/* 0x5E */

	अस्थिर __le32 FIFOTest0;	/* 0x60 */
	अस्थिर __le32 FIFOTest1;	/* 0x64 */

	अस्थिर u8 CAMADDR;		/* 0x68 */
	अस्थिर u8 CAMCR;		/* 0x69 */
	अस्थिर u8 GFTEST;		/* 0x6A */
	अस्थिर u8 FTSTCMD;		/* 0x6B */

	अस्थिर u8 MIICFG;		/* 0x6C */
	अस्थिर u8 MIISR;
	अस्थिर u8 PHYSR0;
	अस्थिर u8 PHYSR1;
	अस्थिर u8 MIICR;
	अस्थिर u8 MIIADR;
	अस्थिर __le16 MIIDATA;

	अस्थिर __le16 SoftTimer0;	/* 0x74 */
	अस्थिर __le16 SoftTimer1;

	अस्थिर u8 CFGA;		/* 0x78 */
	अस्थिर u8 CFGB;
	अस्थिर u8 CFGC;
	अस्थिर u8 CFGD;

	अस्थिर __le16 DCFG;		/* 0x7C */
	अस्थिर __le16 MCFG;

	अस्थिर u8 TBIST;		/* 0x80 */
	अस्थिर u8 RBIST;
	अस्थिर u8 PMCPORT;
	अस्थिर u8 STICKHW;

	अस्थिर u8 MIBCR;		/* 0x84 */
	अस्थिर u8 reserved_85;
	अस्थिर u8 rev_id;
	अस्थिर u8 PORSTS;

	अस्थिर __le32 MIBData;	/* 0x88 */

	अस्थिर __le16 EEWrData;

	अस्थिर u8 reserved_8E;
	अस्थिर u8 BPMDWr;
	अस्थिर u8 BPCMD;
	अस्थिर u8 BPMDRd;

	अस्थिर u8 EECHKSUM;		/* 0x92 */
	अस्थिर u8 EECSR;

	अस्थिर __le16 EERdData;	/* 0x94 */
	अस्थिर u8 EADDR;
	अस्थिर u8 EMBCMD;


	अस्थिर u8 JMPSR0;		/* 0x98 */
	अस्थिर u8 JMPSR1;
	अस्थिर u8 JMPSR2;
	अस्थिर u8 JMPSR3;
	अस्थिर u8 CHIPGSR;		/* 0x9C */
	अस्थिर u8 TESTCFG;
	अस्थिर u8 DEBUG;
	अस्थिर u8 CHIPGCR;

	अस्थिर __le16 WOLCRSet;	/* 0xA0 */
	अस्थिर u8 PWCFGSet;
	अस्थिर u8 WOLCFGSet;

	अस्थिर __le16 WOLCRClr;	/* 0xA4 */
	अस्थिर u8 PWCFGCLR;
	अस्थिर u8 WOLCFGClr;

	अस्थिर __le16 WOLSRSet;	/* 0xA8 */
	अस्थिर __le16 reserved_AA;

	अस्थिर __le16 WOLSRClr;	/* 0xAC */
	अस्थिर __le16 reserved_AE;

	अस्थिर __le16 PatternCRC[8];	/* 0xB0 */
	अस्थिर __le32 ByteMask[4][4];	/* 0xC0 */
पूर्ण;


क्रमागत hw_mib अणु
	HW_MIB_अगरRxAllPkts = 0,
	HW_MIB_अगरRxOkPkts,
	HW_MIB_अगरTxOkPkts,
	HW_MIB_अगरRxErrorPkts,
	HW_MIB_अगरRxRuntOkPkt,
	HW_MIB_अगरRxRuntErrPkt,
	HW_MIB_अगरRx64Pkts,
	HW_MIB_अगरTx64Pkts,
	HW_MIB_अगरRx65To127Pkts,
	HW_MIB_अगरTx65To127Pkts,
	HW_MIB_अगरRx128To255Pkts,
	HW_MIB_अगरTx128To255Pkts,
	HW_MIB_अगरRx256To511Pkts,
	HW_MIB_अगरTx256To511Pkts,
	HW_MIB_अगरRx512To1023Pkts,
	HW_MIB_अगरTx512To1023Pkts,
	HW_MIB_अगरRx1024To1518Pkts,
	HW_MIB_अगरTx1024To1518Pkts,
	HW_MIB_अगरTxEtherCollisions,
	HW_MIB_अगरRxPktCRCE,
	HW_MIB_अगरRxJumboPkts,
	HW_MIB_अगरTxJumboPkts,
	HW_MIB_अगरRxMacControlFrames,
	HW_MIB_अगरTxMacControlFrames,
	HW_MIB_अगरRxPktFAE,
	HW_MIB_अगरRxLongOkPkt,
	HW_MIB_अगरRxLongPktErrPkt,
	HW_MIB_अगरTXSQEErrors,
	HW_MIB_अगरRxNobuf,
	HW_MIB_अगरRxSymbolErrors,
	HW_MIB_अगरInRangeLengthErrors,
	HW_MIB_अगरLateCollisions,
	HW_MIB_SIZE
पूर्ण;

क्रमागत chip_type अणु
	CHIP_TYPE_VT6110 = 1,
पूर्ण;

काष्ठा velocity_info_tbl अणु
	क्रमागत chip_type chip_id;
	स्थिर अक्षर *name;
	पूर्णांक txqueue;
	u32 flags;
पूर्ण;

#घोषणा mac_hw_mibs_init(regs) अणु\
	BYTE_REG_BITS_ON(MIBCR_MIBFRZ,&((regs)->MIBCR));\
	BYTE_REG_BITS_ON(MIBCR_MIBCLR,&((regs)->MIBCR));\
	करो अणुपूर्ण\
		जबतक (BYTE_REG_BITS_IS_ON(MIBCR_MIBCLR,&((regs)->MIBCR)));\
	BYTE_REG_BITS_OFF(MIBCR_MIBFRZ,&((regs)->MIBCR));\
पूर्ण

#घोषणा mac_पढ़ो_isr(regs)  		पढ़ोl(&((regs)->ISR))
#घोषणा mac_ग_लिखो_isr(regs, x)  	ग_लिखोl((x),&((regs)->ISR))
#घोषणा mac_clear_isr(regs) 		ग_लिखोl(0xffffffffL,&((regs)->ISR))

#घोषणा mac_ग_लिखो_पूर्णांक_mask(mask, regs) 	ग_लिखोl((mask),&((regs)->IMR));
#घोषणा mac_disable_पूर्णांक(regs)       	ग_लिखोl(CR0_GINTMSK1,&((regs)->CR0Clr))
#घोषणा mac_enable_पूर्णांक(regs)    	ग_लिखोl(CR0_GINTMSK1,&((regs)->CR0Set))

#घोषणा mac_set_dma_length(regs, n) अणु\
	BYTE_REG_BITS_SET((n),0x07,&((regs)->DCFG));\
पूर्ण

#घोषणा mac_set_rx_thresh(regs, n) अणु\
	BYTE_REG_BITS_SET((n),(MCFG_RFT0|MCFG_RFT1),&((regs)->MCFG));\
पूर्ण

#घोषणा mac_rx_queue_run(regs) अणु\
	ग_लिखोb(TRDCSR_RUN, &((regs)->RDCSRSet));\
पूर्ण

#घोषणा mac_rx_queue_wake(regs) अणु\
	ग_लिखोb(TRDCSR_WAK, &((regs)->RDCSRSet));\
पूर्ण

#घोषणा mac_tx_queue_run(regs, n) अणु\
	ग_लिखोw(TRDCSR_RUN<<((n)*4),&((regs)->TDCSRSet));\
पूर्ण

#घोषणा mac_tx_queue_wake(regs, n) अणु\
	ग_लिखोw(TRDCSR_WAK<<(n*4),&((regs)->TDCSRSet));\
पूर्ण

अटल अंतरभूत व्योम mac_eeprom_reload(काष्ठा mac_regs __iomem * regs) अणु
	पूर्णांक i=0;

	BYTE_REG_BITS_ON(EECSR_RELOAD,&(regs->EECSR));
	करो अणु
		udelay(10);
		अगर (i++>0x1000)
			अवरोध;
	पूर्ण जबतक (BYTE_REG_BITS_IS_ON(EECSR_RELOAD,&(regs->EECSR)));
पूर्ण

/*
 * Header क्रम WOL definitions. Used to compute hashes
 */

प्रकार u8 MCAM_ADDR[ETH_ALEN];

काष्ठा arp_packet अणु
	u8 dest_mac[ETH_ALEN];
	u8 src_mac[ETH_ALEN];
	__be16 type;
	__be16 ar_hrd;
	__be16 ar_pro;
	u8 ar_hln;
	u8 ar_pln;
	__be16 ar_op;
	u8 ar_sha[ETH_ALEN];
	u8 ar_sip[4];
	u8 ar_tha[ETH_ALEN];
	u8 ar_tip[4];
पूर्ण __packed;

काष्ठा _magic_packet अणु
	u8 dest_mac[6];
	u8 src_mac[6];
	__be16 type;
	u8 MAC[16][6];
	u8 password[6];
पूर्ण __packed;

/*
 *	Store क्रम chip context when saving and restoring status. Not
 *	all fields are saved/restored currently.
 */

काष्ठा velocity_context अणु
	u8 mac_reg[256];
	MCAM_ADDR cam_addr[MCAM_SIZE];
	u16 vcam[VCAM_SIZE];
	u32 cammask[2];
	u32 patcrc[2];
	u32 pattern[8];
पूर्ण;

/*
 *	Registers in the MII (offset unit is WORD)
 */

// Marvell 88E1000/88E1000S
#घोषणा MII_REG_PSCR        0x10	// PHY specअगरic control रेजिस्टर

//
// Bits in the Silicon revision रेजिस्टर
//

#घोषणा TCSR_ECHODIS        0x2000	//
#घोषणा AUXCR_MDPPS         0x0004	//

// Bits in the PLED रेजिस्टर
#घोषणा PLED_LALBE			0x0004	//

// Marvell 88E1000/88E1000S Bits in the PHY specअगरic control रेजिस्टर (10h)
#घोषणा PSCR_ACRSTX         0x0800	// Assert CRS on Transmit

#घोषणा PHYID_CICADA_CS8201 0x000FC410UL
#घोषणा PHYID_VT3216_32BIT  0x000FC610UL
#घोषणा PHYID_VT3216_64BIT  0x000FC600UL
#घोषणा PHYID_MARVELL_1000  0x01410C50UL
#घोषणा PHYID_MARVELL_1000S 0x01410C40UL
#घोषणा PHYID_ICPLUS_IP101A 0x02430C54UL
#घोषणा PHYID_REV_ID_MASK   0x0000000FUL

#घोषणा PHYID_GET_PHY_ID(i)         ((i) & ~PHYID_REV_ID_MASK)

#घोषणा MII_REG_BITS_ON(x,i,p) करो अणु\
    u16 w;\
    velocity_mii_पढ़ो((p),(i),&(w));\
    (w)|=(x);\
    velocity_mii_ग_लिखो((p),(i),(w));\
पूर्ण जबतक (0)

#घोषणा MII_REG_BITS_OFF(x,i,p) करो अणु\
    u16 w;\
    velocity_mii_पढ़ो((p),(i),&(w));\
    (w)&=(~(x));\
    velocity_mii_ग_लिखो((p),(i),(w));\
पूर्ण जबतक (0)

#घोषणा MII_REG_BITS_IS_ON(x,i,p) (अणु\
    u16 w;\
    velocity_mii_पढ़ो((p),(i),&(w));\
    ((पूर्णांक) ((w) & (x)));पूर्ण)

#घोषणा MII_GET_PHY_ID(p) (अणु\
    u32 id;\
    velocity_mii_पढ़ो((p),MII_PHYSID2,(u16 *) &id);\
    velocity_mii_पढ़ो((p),MII_PHYSID1,((u16 *) &id)+1);\
    (id);पूर्ण)

#घोषणा     VELOCITY_WOL_MAGIC             0x00000000UL
#घोषणा     VELOCITY_WOL_PHY               0x00000001UL
#घोषणा     VELOCITY_WOL_ARP               0x00000002UL
#घोषणा     VELOCITY_WOL_UCAST             0x00000004UL
#घोषणा     VELOCITY_WOL_BCAST             0x00000010UL
#घोषणा     VELOCITY_WOL_MCAST             0x00000020UL
#घोषणा     VELOCITY_WOL_MAGIC_SEC         0x00000040UL

/*
 *	Flags क्रम options
 */

#घोषणा     VELOCITY_FLAGS_TAGGING         0x00000001UL
#घोषणा     VELOCITY_FLAGS_RX_CSUM         0x00000004UL
#घोषणा     VELOCITY_FLAGS_IP_ALIGN        0x00000008UL
#घोषणा     VELOCITY_FLAGS_VAL_PKT_LEN     0x00000010UL

#घोषणा     VELOCITY_FLAGS_FLOW_CTRL       0x01000000UL

/*
 *	Flags क्रम driver status
 */

#घोषणा     VELOCITY_FLAGS_OPENED          0x00010000UL
#घोषणा     VELOCITY_FLAGS_VMNS_CONNECTED  0x00020000UL
#घोषणा     VELOCITY_FLAGS_VMNS_COMMITTED  0x00040000UL
#घोषणा     VELOCITY_FLAGS_WOL_ENABLED     0x00080000UL

/*
 *	Flags क्रम MII status
 */

#घोषणा     VELOCITY_LINK_FAIL             0x00000001UL
#घोषणा     VELOCITY_SPEED_10              0x00000002UL
#घोषणा     VELOCITY_SPEED_100             0x00000004UL
#घोषणा     VELOCITY_SPEED_1000            0x00000008UL
#घोषणा     VELOCITY_DUPLEX_FULL           0x00000010UL
#घोषणा     VELOCITY_AUTONEG_ENABLE        0x00000020UL
#घोषणा     VELOCITY_FORCED_BY_EEPROM      0x00000040UL

/*
 *	For velocity_set_media_duplex
 */

#घोषणा     VELOCITY_LINK_CHANGE           0x00000001UL

क्रमागत speed_opt अणु
	SPD_DPX_AUTO = 0,
	SPD_DPX_100_HALF = 1,
	SPD_DPX_100_FULL = 2,
	SPD_DPX_10_HALF = 3,
	SPD_DPX_10_FULL = 4,
	SPD_DPX_1000_FULL = 5
पूर्ण;

क्रमागत velocity_init_type अणु
	VELOCITY_INIT_COLD = 0,
	VELOCITY_INIT_RESET,
	VELOCITY_INIT_WOL
पूर्ण;

क्रमागत velocity_flow_cntl_type अणु
	FLOW_CNTL_DEFAULT = 1,
	FLOW_CNTL_TX,
	FLOW_CNTL_RX,
	FLOW_CNTL_TX_RX,
	FLOW_CNTL_DISABLE,
पूर्ण;

काष्ठा velocity_opt अणु
	पूर्णांक numrx;			/* Number of RX descriptors */
	पूर्णांक numtx;			/* Number of TX descriptors */
	क्रमागत speed_opt spd_dpx;		/* Media link mode */

	पूर्णांक DMA_length;			/* DMA length */
	पूर्णांक rx_thresh;			/* RX_THRESH */
	पूर्णांक flow_cntl;
	पूर्णांक wol_opts;			/* Wake on lan options */
	पूर्णांक td_पूर्णांक_count;
	पूर्णांक पूर्णांक_works;
	पूर्णांक rx_bandwidth_hi;
	पूर्णांक rx_bandwidth_lo;
	पूर्णांक rx_bandwidth_en;
	पूर्णांक rxqueue_समयr;
	पूर्णांक txqueue_समयr;
	पूर्णांक tx_पूर्णांकsup;
	पूर्णांक rx_पूर्णांकsup;
	u32 flags;
पूर्ण;

#घोषणा AVAIL_TD(p,q)   ((p)->options.numtx-((p)->tx.used[(q)]))

#घोषणा GET_RD_BY_IDX(vptr, idx)   (vptr->rd_ring[idx])

काष्ठा velocity_info अणु
	काष्ठा device *dev;
	काष्ठा pci_dev *pdev;
	काष्ठा net_device *netdev;
	पूर्णांक no_eeprom;

	अचिन्हित दीर्घ active_vlans[BITS_TO_LONGS(VLAN_N_VID)];
	u8 ip_addr[4];
	क्रमागत chip_type chip_id;

	काष्ठा mac_regs __iomem * mac_regs;
	अचिन्हित दीर्घ memaddr;
	अचिन्हित दीर्घ ioaddr;

	काष्ठा tx_info अणु
		पूर्णांक numq;

		/* FIXME: the locality of the data seems rather poor. */
		पूर्णांक used[TX_QUEUE_NO];
		पूर्णांक curr[TX_QUEUE_NO];
		पूर्णांक tail[TX_QUEUE_NO];
		काष्ठा tx_desc *rings[TX_QUEUE_NO];
		काष्ठा velocity_td_info *infos[TX_QUEUE_NO];
		dma_addr_t pool_dma[TX_QUEUE_NO];
	पूर्ण tx;

	काष्ठा rx_info अणु
		पूर्णांक buf_sz;

		पूर्णांक dirty;
		पूर्णांक curr;
		u32 filled;
		काष्ठा rx_desc *ring;
		काष्ठा velocity_rd_info *info;	/* It's an array */
		dma_addr_t pool_dma;
	पूर्ण rx;

	u32 mib_counter[MAX_HW_MIB_COUNTER];
	काष्ठा velocity_opt options;

	u32 पूर्णांक_mask;

	u32 flags;

	u32 mii_status;
	u32 phy_id;
	पूर्णांक multicast_limit;

	u8 vCAMmask[(VCAM_SIZE / 8)];
	u8 mCAMmask[(MCAM_SIZE / 8)];

	spinlock_t lock;

	पूर्णांक wol_opts;
	u8 wol_passwd[6];

	काष्ठा velocity_context context;

	u32 ticks;
	u32 ethtool_ops_nesting;

	u8 rev_id;

	काष्ठा napi_काष्ठा napi;
पूर्ण;

/**
 *	velocity_get_ip		-	find an IP address क्रम the device
 *	@vptr: Velocity to query
 *
 *	Dig out an IP address क्रम this पूर्णांकerface so that we can
 *	configure wakeup with WOL क्रम ARP. If there are multiple IP
 *	addresses on this chain then we use the first - multi-IP WOL is not
 *	supported.
 *
 */

अटल अंतरभूत पूर्णांक velocity_get_ip(काष्ठा velocity_info *vptr)
अणु
	काष्ठा in_device *in_dev;
	काष्ठा in_अगरaddr *अगरa;
	पूर्णांक res = -ENOENT;

	rcu_पढ़ो_lock();
	in_dev = __in_dev_get_rcu(vptr->netdev);
	अगर (in_dev != शून्य) अणु
		अगरa = rcu_dereference(in_dev->अगरa_list);
		अगर (अगरa != शून्य) अणु
			स_नकल(vptr->ip_addr, &अगरa->अगरa_address, 4);
			res = 0;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस res;
पूर्ण

/**
 *	velocity_update_hw_mibs	-	fetch MIB counters from chip
 *	@vptr: velocity to update
 *
 *	The velocity hardware keeps certain counters in the hardware
 * 	side. We need to पढ़ो these when the user asks क्रम statistics
 *	or when they overflow (causing an पूर्णांकerrupt). The पढ़ो of the
 *	statistic clears it, so we keep running master counters in user
 *	space.
 */

अटल अंतरभूत व्योम velocity_update_hw_mibs(काष्ठा velocity_info *vptr)
अणु
	u32 पंचांगp;
	पूर्णांक i;
	BYTE_REG_BITS_ON(MIBCR_MIBFLSH, &(vptr->mac_regs->MIBCR));

	जबतक (BYTE_REG_BITS_IS_ON(MIBCR_MIBFLSH, &(vptr->mac_regs->MIBCR)));

	BYTE_REG_BITS_ON(MIBCR_MPTRINI, &(vptr->mac_regs->MIBCR));
	क्रम (i = 0; i < HW_MIB_SIZE; i++) अणु
		पंचांगp = पढ़ोl(&(vptr->mac_regs->MIBData)) & 0x00FFFFFFUL;
		vptr->mib_counter[i] += पंचांगp;
	पूर्ण
पूर्ण

/**
 *	init_flow_control_रेजिस्टर 	-	set up flow control
 *	@vptr: velocity to configure
 *
 *	Configure the flow control रेजिस्टरs क्रम this velocity device.
 */

अटल अंतरभूत व्योम init_flow_control_रेजिस्टर(काष्ठा velocity_info *vptr)
अणु
	काष्ठा mac_regs __iomem * regs = vptr->mac_regs;

	/* Set अणुXHITH1, XHITH0, XLTH1, XLTH0पूर्ण in FlowCR1 to अणु1, 0, 1, 1पूर्ण
	   depend on RD=64, and Turn on XNOEN in FlowCR1 */
	ग_लिखोl((CR0_XONEN | CR0_XHITH1 | CR0_XLTH1 | CR0_XLTH0), &regs->CR0Set);
	ग_लिखोl((CR0_FDXTFCEN | CR0_FDXRFCEN | CR0_HDXFCEN | CR0_XHITH0), &regs->CR0Clr);

	/* Set TxPauseTimer to 0xFFFF */
	ग_लिखोw(0xFFFF, &regs->tx_छोड़ो_समयr);

	/* Initialize RBRDU to Rx buffer count. */
	ग_लिखोw(vptr->options.numrx, &regs->RBRDU);
पूर्ण


#पूर्ण_अगर
