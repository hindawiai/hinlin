<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * R8A66597 driver platक्रमm data
 *
 * Copyright (C) 2009  Renesas Solutions Corp.
 *
 * Author : Yoshihiro Shimoda <yoshihiro.shimoda.uh@renesas.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 51 Franklin St, Fअगरth Floor, Boston, MA  02110-1301  USA
 *
 */

#अगर_अघोषित __LINUX_USB_R8A66597_H
#घोषणा __LINUX_USB_R8A66597_H

#घोषणा R8A66597_PLATDATA_XTAL_12MHZ	0x01
#घोषणा R8A66597_PLATDATA_XTAL_24MHZ	0x02
#घोषणा R8A66597_PLATDATA_XTAL_48MHZ	0x03

काष्ठा r8a66597_platdata अणु
	/* This callback can control port घातer instead of DVSTCTR रेजिस्टर. */
	व्योम (*port_घातer)(पूर्णांक port, पूर्णांक घातer);

	/* This parameter is क्रम BUSWAIT */
	u16		busरुको;

	/* set one = on chip controller, set zero = बाह्यal controller */
	अचिन्हित	on_chip:1;

	/* (बाह्यal controller only) set R8A66597_PLATDATA_XTAL_nnMHZ */
	अचिन्हित	xtal:2;

	/* set one = 3.3V, set zero = 1.5V */
	अचिन्हित	vअगर:1;

	/* set one = big endian, set zero = little endian */
	अचिन्हित	endian:1;

	/* (बाह्यal controller only) set one = WR0_N लघुed to WR1_N */
	अचिन्हित	wr0_लघुed_to_wr1:1;

	/* set one = using SUDMAC */
	अचिन्हित	sudmac:1;
पूर्ण;

/* Register definitions */
#घोषणा SYSCFG0		0x00
#घोषणा SYSCFG1		0x02
#घोषणा SYSSTS0		0x04
#घोषणा SYSSTS1		0x06
#घोषणा DVSTCTR0	0x08
#घोषणा DVSTCTR1	0x0A
#घोषणा TESTMODE	0x0C
#घोषणा PINCFG		0x0E
#घोषणा DMA0CFG		0x10
#घोषणा DMA1CFG		0x12
#घोषणा CFIFO		0x14
#घोषणा D0FIFO		0x18
#घोषणा D1FIFO		0x1C
#घोषणा CFIFOSEL	0x20
#घोषणा CFIFOCTR	0x22
#घोषणा CFIFOSIE	0x24
#घोषणा D0FIFOSEL	0x28
#घोषणा D0FIFOCTR	0x2A
#घोषणा D1FIFOSEL	0x2C
#घोषणा D1FIFOCTR	0x2E
#घोषणा INTENB0		0x30
#घोषणा INTENB1		0x32
#घोषणा INTENB2		0x34
#घोषणा BRDYENB		0x36
#घोषणा NRDYENB		0x38
#घोषणा BEMPENB		0x3A
#घोषणा SOFCFG		0x3C
#घोषणा INTSTS0		0x40
#घोषणा INTSTS1		0x42
#घोषणा INTSTS2		0x44
#घोषणा BRDYSTS		0x46
#घोषणा NRDYSTS		0x48
#घोषणा BEMPSTS		0x4A
#घोषणा FRMNUM		0x4C
#घोषणा UFRMNUM		0x4E
#घोषणा USBADDR		0x50
#घोषणा USBREQ		0x54
#घोषणा USBVAL		0x56
#घोषणा USBINDX		0x58
#घोषणा USBLENG		0x5A
#घोषणा DCPCFG		0x5C
#घोषणा DCPMAXP		0x5E
#घोषणा DCPCTR		0x60
#घोषणा PIPESEL		0x64
#घोषणा PIPECFG		0x68
#घोषणा PIPEBUF		0x6A
#घोषणा PIPEMAXP	0x6C
#घोषणा PIPEPERI	0x6E
#घोषणा PIPE1CTR	0x70
#घोषणा PIPE2CTR	0x72
#घोषणा PIPE3CTR	0x74
#घोषणा PIPE4CTR	0x76
#घोषणा PIPE5CTR	0x78
#घोषणा PIPE6CTR	0x7A
#घोषणा PIPE7CTR	0x7C
#घोषणा PIPE8CTR	0x7E
#घोषणा PIPE9CTR	0x80
#घोषणा PIPE1TRE	0x90
#घोषणा PIPE1TRN	0x92
#घोषणा PIPE2TRE	0x94
#घोषणा PIPE2TRN	0x96
#घोषणा PIPE3TRE	0x98
#घोषणा PIPE3TRN	0x9A
#घोषणा PIPE4TRE	0x9C
#घोषणा	PIPE4TRN	0x9E
#घोषणा	PIPE5TRE	0xA0
#घोषणा	PIPE5TRN	0xA2
#घोषणा DEVADD0		0xD0
#घोषणा DEVADD1		0xD2
#घोषणा DEVADD2		0xD4
#घोषणा DEVADD3		0xD6
#घोषणा DEVADD4		0xD8
#घोषणा DEVADD5		0xDA
#घोषणा DEVADD6		0xDC
#घोषणा DEVADD7		0xDE
#घोषणा DEVADD8		0xE0
#घोषणा DEVADD9		0xE2
#घोषणा DEVADDA		0xE4

/* System Configuration Control Register */
#घोषणा	XTAL		0xC000	/* b15-14: Crystal selection */
#घोषणा	  XTAL48	 0x8000	  /* 48MHz */
#घोषणा	  XTAL24	 0x4000	  /* 24MHz */
#घोषणा	  XTAL12	 0x0000	  /* 12MHz */
#घोषणा	XCKE		0x2000	/* b13: External घड़ी enable */
#घोषणा	PLLC		0x0800	/* b11: PLL control */
#घोषणा	SCKE		0x0400	/* b10: USB घड़ी enable */
#घोषणा	PCSDIS		0x0200	/* b9: not CS wakeup */
#घोषणा	LPSME		0x0100	/* b8: Low घातer sleep mode */
#घोषणा	HSE		0x0080	/* b7: Hi-speed enable */
#घोषणा	DCFM		0x0040	/* b6: Controller function select  */
#घोषणा	DRPD		0x0020	/* b5: D+/- pull करोwn control */
#घोषणा	DPRPU		0x0010	/* b4: D+ pull up control */
#घोषणा	USBE		0x0001	/* b0: USB module operation enable */

/* System Configuration Status Register */
#घोषणा	OVCBIT		0x8000	/* b15-14: Over-current bit */
#घोषणा	OVCMON		0xC000	/* b15-14: Over-current monitor */
#घोषणा	SOFEA		0x0020	/* b5: SOF monitor */
#घोषणा	IDMON		0x0004	/* b3: ID-pin monitor */
#घोषणा	LNST		0x0003	/* b1-0: D+, D- line status */
#घोषणा	  SE1		 0x0003	  /* SE1 */
#घोषणा	  FS_KSTS	 0x0002	  /* Full-Speed K State */
#घोषणा	  FS_JSTS	 0x0001	  /* Full-Speed J State */
#घोषणा	  LS_JSTS	 0x0002	  /* Low-Speed J State */
#घोषणा	  LS_KSTS	 0x0001	  /* Low-Speed K State */
#घोषणा	  SE0		 0x0000	  /* SE0 */

/* Device State Control Register */
#घोषणा	EXTLP0		0x0400	/* b10: External port */
#घोषणा	VBOUT		0x0200	/* b9: VBUS output */
#घोषणा	WKUP		0x0100	/* b8: Remote wakeup */
#घोषणा	RWUPE		0x0080	/* b7: Remote wakeup sense */
#घोषणा	USBRST		0x0040	/* b6: USB reset enable */
#घोषणा	RESUME		0x0020	/* b5: Resume enable */
#घोषणा	UACT		0x0010	/* b4: USB bus enable */
#घोषणा	RHST		0x0007	/* b1-0: Reset handshake status */
#घोषणा	  HSPROC	 0x0004	  /* HS handshake is processing */
#घोषणा	  HSMODE	 0x0003	  /* Hi-Speed mode */
#घोषणा	  FSMODE	 0x0002	  /* Full-Speed mode */
#घोषणा	  LSMODE	 0x0001	  /* Low-Speed mode */
#घोषणा	  UNDECID	 0x0000	  /* Undecided */

/* Test Mode Register */
#घोषणा	UTST			0x000F	/* b3-0: Test select */
#घोषणा	  H_TST_PACKET		 0x000C	  /* HOST TEST Packet */
#घोषणा	  H_TST_SE0_NAK		 0x000B	  /* HOST TEST SE0 NAK */
#घोषणा	  H_TST_K		 0x000A	  /* HOST TEST K */
#घोषणा	  H_TST_J		 0x0009	  /* HOST TEST J */
#घोषणा	  H_TST_NORMAL		 0x0000	  /* HOST Normal Mode */
#घोषणा	  P_TST_PACKET		 0x0004	  /* PERI TEST Packet */
#घोषणा	  P_TST_SE0_NAK		 0x0003	  /* PERI TEST SE0 NAK */
#घोषणा	  P_TST_K		 0x0002	  /* PERI TEST K */
#घोषणा	  P_TST_J		 0x0001	  /* PERI TEST J */
#घोषणा	  P_TST_NORMAL		 0x0000	  /* PERI Normal Mode */

/* Data Pin Configuration Register */
#घोषणा	LDRV			0x8000	/* b15: Drive Current Adjust */
#घोषणा	  VIF1			  0x0000		/* VIF = 1.8V */
#घोषणा	  VIF3			  0x8000		/* VIF = 3.3V */
#घोषणा	INTA			0x0001	/* b1: USB INT-pin active */

/* DMAx Pin Configuration Register */
#घोषणा	DREQA			0x4000	/* b14: Dreq active select */
#घोषणा	BURST			0x2000	/* b13: Burst mode */
#घोषणा	DACKA			0x0400	/* b10: Dack active select */
#घोषणा	DFORM			0x0380	/* b9-7: DMA mode select */
#घोषणा	  CPU_ADR_RD_WR		 0x0000	  /* Address + RD/WR mode (CPU bus) */
#घोषणा	  CPU_DACK_RD_WR	 0x0100	  /* DACK + RD/WR mode (CPU bus) */
#घोषणा	  CPU_DACK_ONLY		 0x0180	  /* DACK only mode (CPU bus) */
#घोषणा	  SPLIT_DACK_ONLY	 0x0200	  /* DACK only mode (SPLIT bus) */
#घोषणा	DENDA			0x0040	/* b6: Dend active select */
#घोषणा	PKTM			0x0020	/* b5: Packet mode */
#घोषणा	DENDE			0x0010	/* b4: Dend enable */
#घोषणा	OBUS			0x0004	/* b2: OUTbus mode */

/* CFIFO/DxFIFO Port Select Register */
#घोषणा	RCNT		0x8000	/* b15: Read count mode */
#घोषणा	REW		0x4000	/* b14: Buffer शुरुआत */
#घोषणा	DCLRM		0x2000	/* b13: DMA buffer clear mode */
#घोषणा	DREQE		0x1000	/* b12: DREQ output enable */
#घोषणा	  MBW_8		 0x0000	  /*  8bit */
#घोषणा	  MBW_16	 0x0400	  /* 16bit */
#घोषणा	  MBW_32	 0x0800   /* 32bit */
#घोषणा	BIGEND		0x0100	/* b8: Big endian mode */
#घोषणा	  BYTE_LITTLE	 0x0000		/* little dendian */
#घोषणा	  BYTE_BIG	 0x0100		/* big endअगरan */
#घोषणा	ISEL		0x0020	/* b5: DCP FIFO port direction select */
#घोषणा	CURPIPE		0x000F	/* b2-0: PIPE select */

/* CFIFO/DxFIFO Port Control Register */
#घोषणा	BVAL		0x8000	/* b15: Buffer valid flag */
#घोषणा	BCLR		0x4000	/* b14: Buffer clear */
#घोषणा	FRDY		0x2000	/* b13: FIFO पढ़ोy */
#घोषणा	DTLN		0x0FFF	/* b11-0: FIFO received data length */

/* Interrupt Enable Register 0 */
#घोषणा	VBSE	0x8000	/* b15: VBUS पूर्णांकerrupt */
#घोषणा	RSME	0x4000	/* b14: Resume पूर्णांकerrupt */
#घोषणा	SOFE	0x2000	/* b13: Frame update पूर्णांकerrupt */
#घोषणा	DVSE	0x1000	/* b12: Device state transition पूर्णांकerrupt */
#घोषणा	CTRE	0x0800	/* b11: Control transfer stage transition पूर्णांकerrupt */
#घोषणा	BEMPE	0x0400	/* b10: Buffer empty पूर्णांकerrupt */
#घोषणा	NRDYE	0x0200	/* b9: Buffer not पढ़ोy पूर्णांकerrupt */
#घोषणा	BRDYE	0x0100	/* b8: Buffer पढ़ोy पूर्णांकerrupt */

/* Interrupt Enable Register 1 */
#घोषणा	OVRCRE		0x8000	/* b15: Over-current पूर्णांकerrupt */
#घोषणा	BCHGE		0x4000	/* b14: USB us chenge पूर्णांकerrupt */
#घोषणा	DTCHE		0x1000	/* b12: Detach sense पूर्णांकerrupt */
#घोषणा	ATTCHE		0x0800	/* b11: Attach sense पूर्णांकerrupt */
#घोषणा	खातापूर्णERRE		0x0040	/* b6: खातापूर्ण error पूर्णांकerrupt */
#घोषणा	SIGNE		0x0020	/* b5: SETUP IGNORE पूर्णांकerrupt */
#घोषणा	SACKE		0x0010	/* b4: SETUP ACK पूर्णांकerrupt */

/* BRDY Interrupt Enable/Status Register */
#घोषणा	BRDY9		0x0200	/* b9: PIPE9 */
#घोषणा	BRDY8		0x0100	/* b8: PIPE8 */
#घोषणा	BRDY7		0x0080	/* b7: PIPE7 */
#घोषणा	BRDY6		0x0040	/* b6: PIPE6 */
#घोषणा	BRDY5		0x0020	/* b5: PIPE5 */
#घोषणा	BRDY4		0x0010	/* b4: PIPE4 */
#घोषणा	BRDY3		0x0008	/* b3: PIPE3 */
#घोषणा	BRDY2		0x0004	/* b2: PIPE2 */
#घोषणा	BRDY1		0x0002	/* b1: PIPE1 */
#घोषणा	BRDY0		0x0001	/* b1: PIPE0 */

/* NRDY Interrupt Enable/Status Register */
#घोषणा	NRDY9		0x0200	/* b9: PIPE9 */
#घोषणा	NRDY8		0x0100	/* b8: PIPE8 */
#घोषणा	NRDY7		0x0080	/* b7: PIPE7 */
#घोषणा	NRDY6		0x0040	/* b6: PIPE6 */
#घोषणा	NRDY5		0x0020	/* b5: PIPE5 */
#घोषणा	NRDY4		0x0010	/* b4: PIPE4 */
#घोषणा	NRDY3		0x0008	/* b3: PIPE3 */
#घोषणा	NRDY2		0x0004	/* b2: PIPE2 */
#घोषणा	NRDY1		0x0002	/* b1: PIPE1 */
#घोषणा	NRDY0		0x0001	/* b1: PIPE0 */

/* BEMP Interrupt Enable/Status Register */
#घोषणा	BEMP9		0x0200	/* b9: PIPE9 */
#घोषणा	BEMP8		0x0100	/* b8: PIPE8 */
#घोषणा	BEMP7		0x0080	/* b7: PIPE7 */
#घोषणा	BEMP6		0x0040	/* b6: PIPE6 */
#घोषणा	BEMP5		0x0020	/* b5: PIPE5 */
#घोषणा	BEMP4		0x0010	/* b4: PIPE4 */
#घोषणा	BEMP3		0x0008	/* b3: PIPE3 */
#घोषणा	BEMP2		0x0004	/* b2: PIPE2 */
#घोषणा	BEMP1		0x0002	/* b1: PIPE1 */
#घोषणा	BEMP0		0x0001	/* b0: PIPE0 */

/* SOF Pin Configuration Register */
#घोषणा	TRNENSEL	0x0100	/* b8: Select transaction enable period */
#घोषणा	BRDYM		0x0040	/* b6: BRDY clear timing */
#घोषणा	INTL		0x0020	/* b5: Interrupt sense select */
#घोषणा	EDGESTS		0x0010	/* b4:  */
#घोषणा	SOFMODE		0x000C	/* b3-2: SOF pin select */
#घोषणा	  SOF_125US	 0x0008	  /* SOF OUT 125us Frame Signal */
#घोषणा	  SOF_1MS	 0x0004	  /* SOF OUT 1ms Frame Signal */
#घोषणा	  SOF_DISABLE	 0x0000	  /* SOF OUT Disable */

/* Interrupt Status Register 0 */
#घोषणा	VBINT	0x8000	/* b15: VBUS पूर्णांकerrupt */
#घोषणा	RESM	0x4000	/* b14: Resume पूर्णांकerrupt */
#घोषणा	SOFR	0x2000	/* b13: SOF frame update पूर्णांकerrupt */
#घोषणा	DVST	0x1000	/* b12: Device state transition पूर्णांकerrupt */
#घोषणा	CTRT	0x0800	/* b11: Control transfer stage transition पूर्णांकerrupt */
#घोषणा	BEMP	0x0400	/* b10: Buffer empty पूर्णांकerrupt */
#घोषणा	NRDY	0x0200	/* b9: Buffer not पढ़ोy पूर्णांकerrupt */
#घोषणा	BRDY	0x0100	/* b8: Buffer पढ़ोy पूर्णांकerrupt */
#घोषणा	VBSTS	0x0080	/* b7: VBUS input port */
#घोषणा	DVSQ	0x0070	/* b6-4: Device state */
#घोषणा	  DS_SPD_CNFG	 0x0070	  /* Suspend Configured */
#घोषणा	  DS_SPD_ADDR	 0x0060	  /* Suspend Address */
#घोषणा	  DS_SPD_DFLT	 0x0050	  /* Suspend Default */
#घोषणा	  DS_SPD_POWR	 0x0040	  /* Suspend Powered */
#घोषणा	  DS_SUSP	 0x0040	  /* Suspend */
#घोषणा	  DS_CNFG	 0x0030	  /* Configured */
#घोषणा	  DS_ADDS	 0x0020	  /* Address */
#घोषणा	  DS_DFLT	 0x0010	  /* Default */
#घोषणा	  DS_POWR	 0x0000	  /* Powered */
#घोषणा	DVSQS		0x0030	/* b5-4: Device state */
#घोषणा	VALID		0x0008	/* b3: Setup packet detected flag */
#घोषणा	CTSQ		0x0007	/* b2-0: Control transfer stage */
#घोषणा	  CS_SQER	 0x0006	  /* Sequence error */
#घोषणा	  CS_WRND	 0x0005	  /* Control ग_लिखो nodata status stage */
#घोषणा	  CS_WRSS	 0x0004	  /* Control ग_लिखो status stage */
#घोषणा	  CS_WRDS	 0x0003	  /* Control ग_लिखो data stage */
#घोषणा	  CS_RDSS	 0x0002	  /* Control पढ़ो status stage */
#घोषणा	  CS_RDDS	 0x0001	  /* Control पढ़ो data stage */
#घोषणा	  CS_IDST	 0x0000	  /* Idle or setup stage */

/* Interrupt Status Register 1 */
#घोषणा	OVRCR		0x8000	/* b15: Over-current पूर्णांकerrupt */
#घोषणा	BCHG		0x4000	/* b14: USB bus chenge पूर्णांकerrupt */
#घोषणा	DTCH		0x1000	/* b12: Detach sense पूर्णांकerrupt */
#घोषणा	ATTCH		0x0800	/* b11: Attach sense पूर्णांकerrupt */
#घोषणा	खातापूर्णERR		0x0040	/* b6: खातापूर्ण-error पूर्णांकerrupt */
#घोषणा	SIGN		0x0020	/* b5: Setup ignore पूर्णांकerrupt */
#घोषणा	SACK		0x0010	/* b4: Setup acknowledge पूर्णांकerrupt */

/* Frame Number Register */
#घोषणा	OVRN		0x8000	/* b15: Overrun error */
#घोषणा	CRCE		0x4000	/* b14: Received data error */
#घोषणा	FRNM		0x07FF	/* b10-0: Frame number */

/* Micro Frame Number Register */
#घोषणा	UFRNM		0x0007	/* b2-0: Micro frame number */

/* Default Control Pipe Maxpacket Size Register */
/* Pipe Maxpacket Size Register */
#घोषणा	DEVSEL	0xF000	/* b15-14: Device address select */
#घोषणा	MAXP	0x007F	/* b6-0: Maxpacket size of शेष control pipe */

/* Default Control Pipe Control Register */
#घोषणा	BSTS		0x8000	/* b15: Buffer status */
#घोषणा	SUREQ		0x4000	/* b14: Send USB request  */
#घोषणा	CSCLR		0x2000	/* b13: complete-split status clear */
#घोषणा	CSSTS		0x1000	/* b12: complete-split status */
#घोषणा	SUREQCLR	0x0800	/* b11: stop setup request */
#घोषणा	SQCLR		0x0100	/* b8: Sequence toggle bit clear */
#घोषणा	SQSET		0x0080	/* b7: Sequence toggle bit set */
#घोषणा	SQMON		0x0040	/* b6: Sequence toggle bit monitor */
#घोषणा	PBUSY		0x0020	/* b5: pipe busy */
#घोषणा	PINGE		0x0010	/* b4: ping enable */
#घोषणा	CCPL		0x0004	/* b2: Enable control transfer complete */
#घोषणा	PID		0x0003	/* b1-0: Response PID */
#घोषणा	  PID_STALL11	 0x0003	  /* STALL */
#घोषणा	  PID_STALL	 0x0002	  /* STALL */
#घोषणा	  PID_BUF	 0x0001	  /* BUF */
#घोषणा	  PID_NAK	 0x0000	  /* NAK */

/* Pipe Winकरोw Select Register */
#घोषणा	PIPENM		0x0007	/* b2-0: Pipe select */

/* Pipe Configuration Register */
#घोषणा	R8A66597_TYP	0xC000	/* b15-14: Transfer type */
#घोषणा	  R8A66597_ISO	 0xC000		  /* Isochronous */
#घोषणा	  R8A66597_INT	 0x8000		  /* Interrupt */
#घोषणा	  R8A66597_BULK	 0x4000		  /* Bulk */
#घोषणा	R8A66597_BFRE	0x0400	/* b10: Buffer पढ़ोy पूर्णांकerrupt mode select */
#घोषणा	R8A66597_DBLB	0x0200	/* b9: Double buffer mode select */
#घोषणा	R8A66597_CNTMD	0x0100	/* b8: Continuous transfer mode select */
#घोषणा	R8A66597_SHTNAK	0x0080	/* b7: Transfer end NAK */
#घोषणा	R8A66597_सूची	0x0010	/* b4: Transfer direction select */
#घोषणा	R8A66597_EPNUM	0x000F	/* b3-0: Eendpoपूर्णांक number select */

/* Pipe Buffer Configuration Register */
#घोषणा	बफ_मानE		0x7C00	/* b14-10: Pipe buffer size */
#घोषणा	BUFNMB		0x007F	/* b6-0: Pipe buffer number */
#घोषणा	PIPE0BUF	256
#घोषणा	PIPExBUF	64

/* Pipe Maxpacket Size Register */
#घोषणा	MXPS		0x07FF	/* b10-0: Maxpacket size */

/* Pipe Cycle Configuration Register */
#घोषणा	IFIS	0x1000	/* b12: Isochronous in-buffer flush mode select */
#घोषणा	IITV	0x0007	/* b2-0: Isochronous पूर्णांकerval */

/* Pipex Control Register */
#घोषणा	BSTS	0x8000	/* b15: Buffer status */
#घोषणा	INBUFM	0x4000	/* b14: IN buffer monitor (Only क्रम PIPE1 to 5) */
#घोषणा	CSCLR	0x2000	/* b13: complete-split status clear */
#घोषणा	CSSTS	0x1000	/* b12: complete-split status */
#घोषणा	ATREPM	0x0400	/* b10: Auto repeat mode */
#घोषणा	ACLRM	0x0200	/* b9: Out buffer स्वतः clear mode */
#घोषणा	SQCLR	0x0100	/* b8: Sequence toggle bit clear */
#घोषणा	SQSET	0x0080	/* b7: Sequence toggle bit set */
#घोषणा	SQMON	0x0040	/* b6: Sequence toggle bit monitor */
#घोषणा	PBUSY	0x0020	/* b5: pipe busy */
#घोषणा	PID	0x0003	/* b1-0: Response PID */

/* PIPExTRE */
#घोषणा	TRENB		0x0200	/* b9: Transaction counter enable */
#घोषणा	TRCLR		0x0100	/* b8: Transaction counter clear */

/* PIPExTRN */
#घोषणा	TRNCNT		0xFFFF	/* b15-0: Transaction counter */

/* DEVADDx */
#घोषणा	UPPHUB		0x7800
#घोषणा	HUBPORT		0x0700
#घोषणा	USBSPD		0x00C0
#घोषणा	RTPORT		0x0001

/* SUDMAC रेजिस्टरs */
#घोषणा CH0CFG		0x00
#घोषणा CH1CFG		0x04
#घोषणा CH0BA		0x10
#घोषणा CH1BA		0x14
#घोषणा CH0BBC		0x18
#घोषणा CH1BBC		0x1C
#घोषणा CH0CA		0x20
#घोषणा CH1CA		0x24
#घोषणा CH0CBC		0x28
#घोषणा CH1CBC		0x2C
#घोषणा CH0DEN		0x30
#घोषणा CH1DEN		0x34
#घोषणा DSTSCLR		0x38
#घोषणा DBUFCTRL	0x3C
#घोषणा DINTCTRL	0x40
#घोषणा DINTSTS		0x44
#घोषणा DINTSTSCLR	0x48
#घोषणा CH0SHCTRL	0x50
#घोषणा CH1SHCTRL	0x54

/* SUDMAC Configuration Registers */
#घोषणा SENDBUFM	0x1000 /* b12: Transmit Buffer Mode */
#घोषणा RCVENDM		0x0100 /* b8: Receive Data Transfer End Mode */
#घोषणा LBA_WAIT	0x0030 /* b5-4: Local Bus Access Wait */

/* DMA Enable Registers */
#घोषणा DEN		0x0001 /* b1: DMA Transfer Enable */

/* DMA Status Clear Register */
#घोषणा CH1STCLR	0x0002 /* b2: Ch1 DMA Status Clear */
#घोषणा CH0STCLR	0x0001 /* b1: Ch0 DMA Status Clear */

/* DMA Buffer Control Register */
#घोषणा CH1BUFW		0x0200 /* b9: Ch1 DMA Buffer Data Transfer Enable */
#घोषणा CH0BUFW		0x0100 /* b8: Ch0 DMA Buffer Data Transfer Enable */
#घोषणा CH1BUFS		0x0002 /* b2: Ch1 DMA Buffer Data Status */
#घोषणा CH0BUFS		0x0001 /* b1: Ch0 DMA Buffer Data Status */

/* DMA Interrupt Control Register */
#घोषणा CH1ERRE		0x0200 /* b9: Ch1 SHwy Res Err Detect Int Enable */
#घोषणा CH0ERRE		0x0100 /* b8: Ch0 SHwy Res Err Detect Int Enable */
#घोषणा CH1ENDE		0x0002 /* b2: Ch1 DMA Transfer End Int Enable */
#घोषणा CH0ENDE		0x0001 /* b1: Ch0 DMA Transfer End Int Enable */

/* DMA Interrupt Status Register */
#घोषणा CH1ERRS		0x0200 /* b9: Ch1 SHwy Res Err Detect Int Status */
#घोषणा CH0ERRS		0x0100 /* b8: Ch0 SHwy Res Err Detect Int Status */
#घोषणा CH1ENDS		0x0002 /* b2: Ch1 DMA Transfer End Int Status */
#घोषणा CH0ENDS		0x0001 /* b1: Ch0 DMA Transfer End Int Status */

/* DMA Interrupt Status Clear Register */
#घोषणा CH1ERRC		0x0200 /* b9: Ch1 SHwy Res Err Detect Int Stat Clear */
#घोषणा CH0ERRC		0x0100 /* b8: Ch0 SHwy Res Err Detect Int Stat Clear */
#घोषणा CH1ENDC		0x0002 /* b2: Ch1 DMA Transfer End Int Stat Clear */
#घोषणा CH0ENDC		0x0001 /* b1: Ch0 DMA Transfer End Int Stat Clear */

#पूर्ण_अगर /* __LINUX_USB_R8A66597_H */

