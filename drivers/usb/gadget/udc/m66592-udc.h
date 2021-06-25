<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * M66592 UDC (USB gadget)
 *
 * Copyright (C) 2006-2007 Renesas Solutions Corp.
 *
 * Author : Yoshihiro Shimoda <yoshihiro.shimoda.uh@renesas.com>
 */

#अगर_अघोषित __M66592_UDC_H__
#घोषणा __M66592_UDC_H__

#समावेश <linux/clk.h>
#समावेश <linux/usb/m66592.h>

#घोषणा M66592_SYSCFG		0x00
#घोषणा M66592_XTAL		0xC000	/* b15-14: Crystal selection */
#घोषणा   M66592_XTAL48		 0x8000		/* 48MHz */
#घोषणा   M66592_XTAL24		 0x4000		/* 24MHz */
#घोषणा   M66592_XTAL12		 0x0000		/* 12MHz */
#घोषणा M66592_XCKE		0x2000	/* b13: External घड़ी enable */
#घोषणा M66592_RCKE		0x1000	/* b12: Register घड़ी enable */
#घोषणा M66592_PLLC		0x0800	/* b11: PLL control */
#घोषणा M66592_SCKE		0x0400	/* b10: USB घड़ी enable */
#घोषणा M66592_ATCKM		0x0100	/* b8: Automatic घड़ी supply */
#घोषणा M66592_HSE		0x0080	/* b7: Hi-speed enable */
#घोषणा M66592_DCFM		0x0040	/* b6: Controller function select  */
#घोषणा M66592_DMRPD		0x0020	/* b5: D- pull करोwn control */
#घोषणा M66592_DPRPU		0x0010	/* b4: D+ pull up control */
#घोषणा M66592_FSRPC		0x0004	/* b2: Full-speed receiver enable */
#घोषणा M66592_PCUT		0x0002	/* b1: Low घातer sleep enable */
#घोषणा M66592_USBE		0x0001	/* b0: USB module operation enable */

#घोषणा M66592_SYSSTS		0x02
#घोषणा M66592_LNST		0x0003	/* b1-0: D+, D- line status */
#घोषणा   M66592_SE1		 0x0003		/* SE1 */
#घोषणा   M66592_KSTS		 0x0002		/* K State */
#घोषणा   M66592_JSTS		 0x0001		/* J State */
#घोषणा   M66592_SE0		 0x0000		/* SE0 */

#घोषणा M66592_DVSTCTR		0x04
#घोषणा M66592_WKUP		0x0100	/* b8: Remote wakeup */
#घोषणा M66592_RWUPE		0x0080	/* b7: Remote wakeup sense */
#घोषणा M66592_USBRST		0x0040	/* b6: USB reset enable */
#घोषणा M66592_RESUME		0x0020	/* b5: Resume enable */
#घोषणा M66592_UACT		0x0010	/* b4: USB bus enable */
#घोषणा M66592_RHST		0x0003	/* b1-0: Reset handshake status */
#घोषणा   M66592_HSMODE		 0x0003		/* Hi-Speed mode */
#घोषणा   M66592_FSMODE		 0x0002		/* Full-Speed mode */
#घोषणा   M66592_HSPROC		 0x0001		/* HS handshake is processing */

#घोषणा M66592_TESTMODE		0x06
#घोषणा M66592_UTST		0x000F	/* b4-0: Test select */
#घोषणा   M66592_H_TST_PACKET	 0x000C		/* HOST TEST Packet */
#घोषणा   M66592_H_TST_SE0_NAK	 0x000B		/* HOST TEST SE0 NAK */
#घोषणा   M66592_H_TST_K	 0x000A		/* HOST TEST K */
#घोषणा   M66592_H_TST_J	 0x0009		/* HOST TEST J */
#घोषणा   M66592_H_TST_NORMAL	 0x0000		/* HOST Normal Mode */
#घोषणा   M66592_P_TST_PACKET	 0x0004		/* PERI TEST Packet */
#घोषणा   M66592_P_TST_SE0_NAK	 0x0003		/* PERI TEST SE0 NAK */
#घोषणा   M66592_P_TST_K	 0x0002		/* PERI TEST K */
#घोषणा   M66592_P_TST_J	 0x0001		/* PERI TEST J */
#घोषणा   M66592_P_TST_NORMAL	 0x0000		/* PERI Normal Mode */

/* built-in रेजिस्टरs */
#घोषणा M66592_CFBCFG		0x0A
#घोषणा M66592_D0FBCFG		0x0C
#घोषणा M66592_LITTLE		0x0100	/* b8: Little endian mode */
/* बाह्यal chip हाल */
#घोषणा M66592_PINCFG		0x0A
#घोषणा M66592_LDRV		0x8000	/* b15: Drive Current Adjust */
#घोषणा M66592_BIGEND		0x0100	/* b8: Big endian mode */

#घोषणा M66592_DMA0CFG		0x0C
#घोषणा M66592_DMA1CFG		0x0E
#घोषणा M66592_DREQA		0x4000	/* b14: Dreq active select */
#घोषणा M66592_BURST		0x2000	/* b13: Burst mode */
#घोषणा M66592_DACKA		0x0400	/* b10: Dack active select */
#घोषणा M66592_DFORM		0x0380	/* b9-7: DMA mode select */
#घोषणा   M66592_CPU_ADR_RD_WR	 0x0000   /* Address + RD/WR mode (CPU bus) */
#घोषणा   M66592_CPU_DACK_RD_WR	 0x0100   /* DACK + RD/WR mode (CPU bus) */
#घोषणा   M66592_CPU_DACK_ONLY	 0x0180   /* DACK only mode (CPU bus) */
#घोषणा   M66592_SPLIT_DACK_ONLY 0x0200   /* DACK only mode (SPLIT bus) */
#घोषणा   M66592_SPLIT_DACK_DSTB 0x0300   /* DACK + DSTB0 mode (SPLIT bus) */
#घोषणा M66592_DENDA		0x0040	/* b6: Dend active select */
#घोषणा M66592_PKTM		0x0020	/* b5: Packet mode */
#घोषणा M66592_DENDE		0x0010	/* b4: Dend enable */
#घोषणा M66592_OBUS		0x0004	/* b2: OUTbus mode */

/* common हाल */
#घोषणा M66592_CFIFO		0x10
#घोषणा M66592_D0FIFO		0x14
#घोषणा M66592_D1FIFO		0x18

#घोषणा M66592_CFIFOSEL		0x1E
#घोषणा M66592_D0FIFOSEL	0x24
#घोषणा M66592_D1FIFOSEL	0x2A
#घोषणा M66592_RCNT		0x8000	/* b15: Read count mode */
#घोषणा M66592_REW		0x4000	/* b14: Buffer शुरुआत */
#घोषणा M66592_DCLRM		0x2000	/* b13: DMA buffer clear mode */
#घोषणा M66592_DREQE		0x1000	/* b12: DREQ output enable */
#घोषणा M66592_MBW_8		0x0000   /*  8bit */
#घोषणा M66592_MBW_16		0x0400   /* 16bit */
#घोषणा M66592_MBW_32		0x0800   /* 32bit */
#घोषणा M66592_TRENB		0x0200	/* b9: Transaction counter enable */
#घोषणा M66592_TRCLR		0x0100	/* b8: Transaction counter clear */
#घोषणा M66592_DEZPM		0x0080	/* b7: Zero-length packet mode */
#घोषणा M66592_ISEL		0x0020	/* b5: DCP FIFO port direction select */
#घोषणा M66592_CURPIPE		0x0007	/* b2-0: PIPE select */

#घोषणा M66592_CFIFOCTR		0x20
#घोषणा M66592_D0FIFOCTR	0x26
#घोषणा M66592_D1FIFOCTR	0x2c
#घोषणा M66592_BVAL		0x8000	/* b15: Buffer valid flag */
#घोषणा M66592_BCLR		0x4000	/* b14: Buffer clear */
#घोषणा M66592_FRDY		0x2000	/* b13: FIFO पढ़ोy */
#घोषणा M66592_DTLN		0x0FFF	/* b11-0: FIFO received data length */

#घोषणा M66592_CFIFOSIE		0x22
#घोषणा M66592_TGL		0x8000	/* b15: Buffer toggle */
#घोषणा M66592_SCLR		0x4000	/* b14: Buffer clear */
#घोषणा M66592_SBUSY		0x2000	/* b13: SIE_FIFO busy */

#घोषणा M66592_D0FIFOTRN	0x28
#घोषणा M66592_D1FIFOTRN	0x2E
#घोषणा M66592_TRNCNT		0xFFFF	/* b15-0: Transaction counter */

#घोषणा M66592_INTENB0	0x30
#घोषणा M66592_VBSE	0x8000	/* b15: VBUS पूर्णांकerrupt */
#घोषणा M66592_RSME	0x4000	/* b14: Resume पूर्णांकerrupt */
#घोषणा M66592_SOFE	0x2000	/* b13: Frame update पूर्णांकerrupt */
#घोषणा M66592_DVSE	0x1000	/* b12: Device state transition पूर्णांकerrupt */
#घोषणा M66592_CTRE	0x0800	/* b11: Control transfer stage transition irq */
#घोषणा M66592_BEMPE	0x0400	/* b10: Buffer empty पूर्णांकerrupt */
#घोषणा M66592_NRDYE	0x0200	/* b9: Buffer not पढ़ोy पूर्णांकerrupt */
#घोषणा M66592_BRDYE	0x0100	/* b8: Buffer पढ़ोy पूर्णांकerrupt */
#घोषणा M66592_URST	0x0080	/* b7: USB reset detected पूर्णांकerrupt */
#घोषणा M66592_SADR	0x0040	/* b6: Set address executed पूर्णांकerrupt */
#घोषणा M66592_SCFG	0x0020	/* b5: Set configuration executed पूर्णांकerrupt */
#घोषणा M66592_SUSP	0x0010	/* b4: Suspend detected पूर्णांकerrupt */
#घोषणा M66592_WDST	0x0008	/* b3: Control ग_लिखो data stage completed irq */
#घोषणा M66592_RDST	0x0004	/* b2: Control पढ़ो data stage completed irq */
#घोषणा M66592_CMPL	0x0002	/* b1: Control transfer complete पूर्णांकerrupt */
#घोषणा M66592_SERR	0x0001	/* b0: Sequence error पूर्णांकerrupt */

#घोषणा M66592_INTENB1	0x32
#घोषणा M66592_BCHGE	0x4000	/* b14: USB us chenge पूर्णांकerrupt */
#घोषणा M66592_DTCHE	0x1000	/* b12: Detach sense पूर्णांकerrupt */
#घोषणा M66592_SIGNE	0x0020	/* b5: SETUP IGNORE पूर्णांकerrupt */
#घोषणा M66592_SACKE	0x0010	/* b4: SETUP ACK पूर्णांकerrupt */
#घोषणा M66592_BRDYM	0x0004	/* b2: BRDY clear timing */
#घोषणा M66592_INTL	0x0002	/* b1: Interrupt sense select */
#घोषणा M66592_PCSE	0x0001	/* b0: PCUT enable by CS निश्चित */

#घोषणा M66592_BRDYENB		0x36
#घोषणा M66592_BRDYSTS		0x46
#घोषणा M66592_BRDY7		0x0080	/* b7: PIPE7 */
#घोषणा M66592_BRDY6		0x0040	/* b6: PIPE6 */
#घोषणा M66592_BRDY5		0x0020	/* b5: PIPE5 */
#घोषणा M66592_BRDY4		0x0010	/* b4: PIPE4 */
#घोषणा M66592_BRDY3		0x0008	/* b3: PIPE3 */
#घोषणा M66592_BRDY2		0x0004	/* b2: PIPE2 */
#घोषणा M66592_BRDY1		0x0002	/* b1: PIPE1 */
#घोषणा M66592_BRDY0		0x0001	/* b1: PIPE0 */

#घोषणा M66592_NRDYENB		0x38
#घोषणा M66592_NRDYSTS		0x48
#घोषणा M66592_NRDY7		0x0080	/* b7: PIPE7 */
#घोषणा M66592_NRDY6		0x0040	/* b6: PIPE6 */
#घोषणा M66592_NRDY5		0x0020	/* b5: PIPE5 */
#घोषणा M66592_NRDY4		0x0010	/* b4: PIPE4 */
#घोषणा M66592_NRDY3		0x0008	/* b3: PIPE3 */
#घोषणा M66592_NRDY2		0x0004	/* b2: PIPE2 */
#घोषणा M66592_NRDY1		0x0002	/* b1: PIPE1 */
#घोषणा M66592_NRDY0		0x0001	/* b1: PIPE0 */

#घोषणा M66592_BEMPENB		0x3A
#घोषणा M66592_BEMPSTS		0x4A
#घोषणा M66592_BEMP7		0x0080	/* b7: PIPE7 */
#घोषणा M66592_BEMP6		0x0040	/* b6: PIPE6 */
#घोषणा M66592_BEMP5		0x0020	/* b5: PIPE5 */
#घोषणा M66592_BEMP4		0x0010	/* b4: PIPE4 */
#घोषणा M66592_BEMP3		0x0008	/* b3: PIPE3 */
#घोषणा M66592_BEMP2		0x0004	/* b2: PIPE2 */
#घोषणा M66592_BEMP1		0x0002	/* b1: PIPE1 */
#घोषणा M66592_BEMP0		0x0001	/* b0: PIPE0 */

#घोषणा M66592_SOFCFG		0x3C
#घोषणा M66592_SOFM		0x000C	/* b3-2: SOF palse mode */
#घोषणा   M66592_SOF_125US	 0x0008   /* SOF OUT 125us uFrame Signal */
#घोषणा   M66592_SOF_1MS	 0x0004   /* SOF OUT 1ms Frame Signal */
#घोषणा   M66592_SOF_DISABLE	 0x0000   /* SOF OUT Disable */

#घोषणा M66592_INTSTS0		0x40
#घोषणा M66592_VBINT		0x8000	/* b15: VBUS पूर्णांकerrupt */
#घोषणा M66592_RESM		0x4000	/* b14: Resume पूर्णांकerrupt */
#घोषणा M66592_SOFR		0x2000	/* b13: SOF frame update पूर्णांकerrupt */
#घोषणा M66592_DVST		0x1000	/* b12: Device state transition */
#घोषणा M66592_CTRT		0x0800	/* b11: Control stage transition */
#घोषणा M66592_BEMP		0x0400	/* b10: Buffer empty पूर्णांकerrupt */
#घोषणा M66592_NRDY		0x0200	/* b9: Buffer not पढ़ोy पूर्णांकerrupt */
#घोषणा M66592_BRDY		0x0100	/* b8: Buffer पढ़ोy पूर्णांकerrupt */
#घोषणा M66592_VBSTS		0x0080	/* b7: VBUS input port */
#घोषणा M66592_DVSQ		0x0070	/* b6-4: Device state */
#घोषणा   M66592_DS_SPD_CNFG	 0x0070	   /* Suspend Configured */
#घोषणा   M66592_DS_SPD_ADDR	 0x0060	   /* Suspend Address */
#घोषणा   M66592_DS_SPD_DFLT	 0x0050	   /* Suspend Default */
#घोषणा   M66592_DS_SPD_POWR	 0x0040	   /* Suspend Powered */
#घोषणा   M66592_DS_SUSP	 0x0040	   /* Suspend */
#घोषणा   M66592_DS_CNFG	 0x0030	   /* Configured */
#घोषणा   M66592_DS_ADDS	 0x0020	   /* Address */
#घोषणा   M66592_DS_DFLT	 0x0010	   /* Default */
#घोषणा   M66592_DS_POWR	 0x0000	   /* Powered */
#घोषणा M66592_DVSQS		0x0030	/* b5-4: Device state */
#घोषणा M66592_VALID		0x0008	/* b3: Setup packet detected flag */
#घोषणा M66592_CTSQ		0x0007	/* b2-0: Control transfer stage */
#घोषणा   M66592_CS_SQER	 0x0006	  /* Sequence error */
#घोषणा   M66592_CS_WRND	 0x0005	  /* Control ग_लिखो nodata status */
#घोषणा   M66592_CS_WRSS	 0x0004	  /* Control ग_लिखो status stage */
#घोषणा   M66592_CS_WRDS	 0x0003	  /* Control ग_लिखो data stage */
#घोषणा   M66592_CS_RDSS	 0x0002	  /* Control पढ़ो status stage */
#घोषणा   M66592_CS_RDDS	 0x0001	  /* Control पढ़ो data stage */
#घोषणा   M66592_CS_IDST	 0x0000	  /* Idle or setup stage */

#घोषणा M66592_INTSTS1		0x42
#घोषणा M66592_BCHG		0x4000	/* b14: USB bus chenge पूर्णांकerrupt */
#घोषणा M66592_DTCH		0x1000	/* b12: Detach sense पूर्णांकerrupt */
#घोषणा M66592_SIGN		0x0020	/* b5: SETUP IGNORE पूर्णांकerrupt */
#घोषणा M66592_SACK		0x0010	/* b4: SETUP ACK पूर्णांकerrupt */

#घोषणा M66592_FRMNUM		0x4C
#घोषणा M66592_OVRN		0x8000	/* b15: Overrun error */
#घोषणा M66592_CRCE		0x4000	/* b14: Received data error */
#घोषणा M66592_SOFRM		0x0800	/* b11: SOF output mode */
#घोषणा M66592_FRNM		0x07FF	/* b10-0: Frame number */

#घोषणा M66592_UFRMNUM		0x4E
#घोषणा M66592_UFRNM		0x0007	/* b2-0: Micro frame number */

#घोषणा M66592_RECOVER		0x50
#घोषणा M66592_STSRECOV		0x0700	/* Status recovery */
#घोषणा   M66592_STSR_HI	 0x0400		  /* FULL(0) or HI(1) Speed */
#घोषणा   M66592_STSR_DEFAULT	 0x0100		  /* Default state */
#घोषणा   M66592_STSR_ADDRESS	 0x0200		  /* Address state */
#घोषणा   M66592_STSR_CONFIG	 0x0300		  /* Configured state */
#घोषणा M66592_USBADDR		0x007F	/* b6-0: USB address */

#घोषणा M66592_USBREQ			0x54
#घोषणा M66592_bRequest			0xFF00	/* b15-8: bRequest */
#घोषणा   M66592_GET_STATUS		 0x0000
#घोषणा   M66592_CLEAR_FEATURE		 0x0100
#घोषणा   M66592_ReqRESERVED		 0x0200
#घोषणा   M66592_SET_FEATURE		 0x0300
#घोषणा   M66592_ReqRESERVED1		 0x0400
#घोषणा   M66592_SET_ADDRESS		 0x0500
#घोषणा   M66592_GET_DESCRIPTOR		 0x0600
#घोषणा   M66592_SET_DESCRIPTOR		 0x0700
#घोषणा   M66592_GET_CONFIGURATION	 0x0800
#घोषणा   M66592_SET_CONFIGURATION	 0x0900
#घोषणा   M66592_GET_INTERFACE		 0x0A00
#घोषणा   M66592_SET_INTERFACE		 0x0B00
#घोषणा   M66592_SYNCH_FRAME		 0x0C00
#घोषणा M66592_bmRequestType		0x00FF	/* b7-0: bmRequestType */
#घोषणा M66592_bmRequestTypeDir		0x0080	/* b7  : Data direction */
#घोषणा   M66592_HOST_TO_DEVICE		 0x0000
#घोषणा   M66592_DEVICE_TO_HOST		 0x0080
#घोषणा M66592_bmRequestTypeType	0x0060	/* b6-5: Type */
#घोषणा   M66592_STANDARD		 0x0000
#घोषणा   M66592_CLASS			 0x0020
#घोषणा   M66592_VENDOR			 0x0040
#घोषणा M66592_bmRequestTypeRecip	0x001F	/* b4-0: Recipient */
#घोषणा   M66592_DEVICE			 0x0000
#घोषणा   M66592_INTERFACE		 0x0001
#घोषणा   M66592_ENDPOINT		 0x0002

#घोषणा M66592_USBVAL				0x56
#घोषणा M66592_wValue				0xFFFF	/* b15-0: wValue */
/* Standard Feature Selector */
#घोषणा   M66592_ENDPOINT_HALT			0x0000
#घोषणा   M66592_DEVICE_REMOTE_WAKEUP		0x0001
#घोषणा   M66592_TEST_MODE			0x0002
/* Descriptor Types */
#घोषणा M66592_DT_TYPE				0xFF00
#घोषणा M66592_GET_DT_TYPE(v)			(((v) & DT_TYPE) >> 8)
#घोषणा   M66592_DT_DEVICE			0x01
#घोषणा   M66592_DT_CONFIGURATION		0x02
#घोषणा   M66592_DT_STRING			0x03
#घोषणा   M66592_DT_INTERFACE			0x04
#घोषणा   M66592_DT_ENDPOINT			0x05
#घोषणा   M66592_DT_DEVICE_QUALIFIER		0x06
#घोषणा   M66592_DT_OTHER_SPEED_CONFIGURATION	0x07
#घोषणा   M66592_DT_INTERFACE_POWER		0x08
#घोषणा M66592_DT_INDEX				0x00FF
#घोषणा M66592_CONF_NUM				0x00FF
#घोषणा M66592_ALT_SET				0x00FF

#घोषणा M66592_USBINDEX			0x58
#घोषणा M66592_wIndex			0xFFFF	/* b15-0: wIndex */
#घोषणा M66592_TEST_SELECT		0xFF00	/* b15-b8: Test Mode */
#घोषणा   M66592_TEST_J			 0x0100	  /* Test_J */
#घोषणा   M66592_TEST_K			 0x0200	  /* Test_K */
#घोषणा   M66592_TEST_SE0_NAK		 0x0300	  /* Test_SE0_NAK */
#घोषणा   M66592_TEST_PACKET		 0x0400	  /* Test_Packet */
#घोषणा   M66592_TEST_FORCE_ENABLE	 0x0500	  /* Test_Force_Enable */
#घोषणा   M66592_TEST_STSelectors	 0x0600	  /* Standard test selectors */
#घोषणा   M66592_TEST_Reserved		 0x4000	  /* Reserved */
#घोषणा   M66592_TEST_VSTModes		 0xC000	  /* Venकरोr-specअगरic tests */
#घोषणा M66592_EP_सूची			0x0080	/* b7: Endpoपूर्णांक Direction */
#घोषणा   M66592_EP_सूची_IN		 0x0080
#घोषणा   M66592_EP_सूची_OUT		 0x0000

#घोषणा M66592_USBLENG		0x5A
#घोषणा M66592_wLength		0xFFFF	/* b15-0: wLength */

#घोषणा M66592_DCPCFG		0x5C
#घोषणा M66592_CNTMD		0x0100	/* b8: Continuous transfer mode */
#घोषणा M66592_सूची		0x0010	/* b4: Control transfer सूची select */

#घोषणा M66592_DCPMAXP		0x5E
#घोषणा M66592_DEVSEL		0xC000	/* b15-14: Device address select */
#घोषणा   M66592_DEVICE_0	 0x0000		  /* Device address 0 */
#घोषणा   M66592_DEVICE_1	 0x4000		  /* Device address 1 */
#घोषणा   M66592_DEVICE_2	 0x8000		  /* Device address 2 */
#घोषणा   M66592_DEVICE_3	 0xC000		  /* Device address 3 */
#घोषणा M66592_MAXP		0x007F	/* b6-0: Maxpacket size of ep0 */

#घोषणा M66592_DCPCTR		0x60
#घोषणा M66592_BSTS		0x8000	/* b15: Buffer status */
#घोषणा M66592_SUREQ		0x4000	/* b14: Send USB request  */
#घोषणा M66592_SQCLR		0x0100	/* b8: Sequence toggle bit clear */
#घोषणा M66592_SQSET		0x0080	/* b7: Sequence toggle bit set */
#घोषणा M66592_SQMON		0x0040	/* b6: Sequence toggle bit monitor */
#घोषणा M66592_CCPL		0x0004	/* b2: control transfer complete */
#घोषणा M66592_PID		0x0003	/* b1-0: Response PID */
#घोषणा   M66592_PID_STALL	 0x0002		  /* STALL */
#घोषणा   M66592_PID_BUF	 0x0001		  /* BUF */
#घोषणा   M66592_PID_NAK	 0x0000		  /* NAK */

#घोषणा M66592_PIPESEL		0x64
#घोषणा M66592_PIPENM		0x0007	/* b2-0: Pipe select */
#घोषणा   M66592_PIPE0		 0x0000		  /* PIPE 0 */
#घोषणा   M66592_PIPE1		 0x0001		  /* PIPE 1 */
#घोषणा   M66592_PIPE2		 0x0002		  /* PIPE 2 */
#घोषणा   M66592_PIPE3		 0x0003		  /* PIPE 3 */
#घोषणा   M66592_PIPE4		 0x0004		  /* PIPE 4 */
#घोषणा   M66592_PIPE5		 0x0005		  /* PIPE 5 */
#घोषणा   M66592_PIPE6		 0x0006		  /* PIPE 6 */
#घोषणा   M66592_PIPE7		 0x0007		  /* PIPE 7 */

#घोषणा M66592_PIPECFG		0x66
#घोषणा M66592_TYP		0xC000	/* b15-14: Transfer type */
#घोषणा   M66592_ISO		 0xC000		  /* Isochronous */
#घोषणा   M66592_INT		 0x8000		  /* Interrupt */
#घोषणा   M66592_BULK		 0x4000		  /* Bulk */
#घोषणा M66592_BFRE		0x0400	/* b10: Buffer पढ़ोy पूर्णांकerrupt mode */
#घोषणा M66592_DBLB		0x0200	/* b9: Double buffer mode select */
#घोषणा M66592_CNTMD		0x0100	/* b8: Continuous transfer mode */
#घोषणा M66592_SHTNAK		0x0080	/* b7: Transfer end NAK */
#घोषणा M66592_सूची		0x0010	/* b4: Transfer direction select */
#घोषणा   M66592_सूची_H_OUT	 0x0010		  /* HOST OUT */
#घोषणा   M66592_सूची_P_IN	 0x0010		  /* PERI IN */
#घोषणा   M66592_सूची_H_IN	 0x0000		  /* HOST IN */
#घोषणा   M66592_सूची_P_OUT	 0x0000		  /* PERI OUT */
#घोषणा M66592_EPNUM		0x000F	/* b3-0: Eendpoपूर्णांक number select */
#घोषणा   M66592_EP1		 0x0001
#घोषणा   M66592_EP2		 0x0002
#घोषणा   M66592_EP3		 0x0003
#घोषणा   M66592_EP4		 0x0004
#घोषणा   M66592_EP5		 0x0005
#घोषणा   M66592_EP6		 0x0006
#घोषणा   M66592_EP7		 0x0007
#घोषणा   M66592_EP8		 0x0008
#घोषणा   M66592_EP9		 0x0009
#घोषणा   M66592_EP10		 0x000A
#घोषणा   M66592_EP11		 0x000B
#घोषणा   M66592_EP12		 0x000C
#घोषणा   M66592_EP13		 0x000D
#घोषणा   M66592_EP14		 0x000E
#घोषणा   M66592_EP15		 0x000F

#घोषणा M66592_PIPEBUF		0x68
#घोषणा M66592_बफ_मानE		0x7C00	/* b14-10: Pipe buffer size */
#घोषणा M66592_BUF_SIZE(x)	((((x) / 64) - 1) << 10)
#घोषणा M66592_BUFNMB		0x00FF	/* b7-0: Pipe buffer number */

#घोषणा M66592_PIPEMAXP		0x6A
#घोषणा M66592_MXPS		0x07FF	/* b10-0: Maxpacket size */

#घोषणा M66592_PIPEPERI		0x6C
#घोषणा M66592_IFIS		0x1000	/* b12: ISO in-buffer flush mode */
#घोषणा M66592_IITV		0x0007	/* b2-0: ISO पूर्णांकerval */

#घोषणा M66592_PIPE1CTR		0x70
#घोषणा M66592_PIPE2CTR		0x72
#घोषणा M66592_PIPE3CTR		0x74
#घोषणा M66592_PIPE4CTR		0x76
#घोषणा M66592_PIPE5CTR		0x78
#घोषणा M66592_PIPE6CTR		0x7A
#घोषणा M66592_PIPE7CTR		0x7C
#घोषणा M66592_BSTS		0x8000	/* b15: Buffer status */
#घोषणा M66592_INBUFM		0x4000	/* b14: IN buffer monitor (PIPE 1-5) */
#घोषणा M66592_ACLRM		0x0200	/* b9: Out buffer स्वतः clear mode */
#घोषणा M66592_SQCLR		0x0100	/* b8: Sequence toggle bit clear */
#घोषणा M66592_SQSET		0x0080	/* b7: Sequence toggle bit set */
#घोषणा M66592_SQMON		0x0040	/* b6: Sequence toggle bit monitor */
#घोषणा M66592_PID		0x0003	/* b1-0: Response PID */

#घोषणा M66592_INVALID_REG	0x7E


#घोषणा get_pipectr_addr(pipक्रमागत)	(M66592_PIPE1CTR + (pipक्रमागत - 1) * 2)

#घोषणा M66592_MAX_SAMPLING	10

#घोषणा M66592_MAX_NUM_PIPE	8
#घोषणा M66592_MAX_NUM_BULK	3
#घोषणा M66592_MAX_NUM_ISOC	2
#घोषणा M66592_MAX_NUM_INT	2

#घोषणा M66592_BASE_PIPENUM_BULK	3
#घोषणा M66592_BASE_PIPENUM_ISOC	1
#घोषणा M66592_BASE_PIPENUM_INT		6

#घोषणा M66592_BASE_BUFNUM	6
#घोषणा M66592_MAX_BUFNUM	0x4F

काष्ठा m66592_pipe_info अणु
	u16	pipe;
	u16	epnum;
	u16	maxpacket;
	u16	type;
	u16	पूर्णांकerval;
	u16	dir_in;
पूर्ण;

काष्ठा m66592_request अणु
	काष्ठा usb_request	req;
	काष्ठा list_head	queue;
पूर्ण;

काष्ठा m66592_ep अणु
	काष्ठा usb_ep		ep;
	काष्ठा m66592		*m66592;

	काष्ठा list_head	queue;
	अचिन्हित		busy:1;
	अचिन्हित		पूर्णांकernal_ccpl:1;	/* use only control */

	/* this member can able to after m66592_enable */
	अचिन्हित		use_dma:1;
	u16			pipक्रमागत;
	u16			type;

	/* रेजिस्टर address */
	अचिन्हित दीर्घ		fअगरoaddr;
	अचिन्हित दीर्घ		fअगरosel;
	अचिन्हित दीर्घ		fअगरoctr;
	अचिन्हित दीर्घ		fअगरotrn;
	अचिन्हित दीर्घ		pipectr;
पूर्ण;

काष्ठा m66592 अणु
	spinlock_t		lock;
	व्योम __iomem		*reg;
	काष्ठा clk *clk;
	काष्ठा m66592_platdata	*pdata;
	अचिन्हित दीर्घ		irq_trigger;

	काष्ठा usb_gadget		gadget;
	काष्ठा usb_gadget_driver	*driver;

	काष्ठा m66592_ep	ep[M66592_MAX_NUM_PIPE];
	काष्ठा m66592_ep	*pipक्रमागत2ep[M66592_MAX_NUM_PIPE];
	काष्ठा m66592_ep	*epaddr2ep[16];

	काष्ठा usb_request	*ep0_req;	/* क्रम पूर्णांकernal request */
	__le16			ep0_data;	/* क्रम पूर्णांकernal request */
	u16			old_vbus;

	काष्ठा समयr_list	समयr;

	पूर्णांक			scount;

	पूर्णांक			old_dvsq;

	/* pipe config */
	पूर्णांक bulk;
	पूर्णांक पूर्णांकerrupt;
	पूर्णांक isochronous;
	पूर्णांक num_dma;
पूर्ण;
#घोषणा to_m66592(g)	(container_of((g), काष्ठा m66592, gadget))

#घोषणा gadget_to_m66592(_gadget) container_of(_gadget, काष्ठा m66592, gadget)
#घोषणा m66592_to_gadget(m66592) (&m66592->gadget)

#घोषणा is_bulk_pipe(pipक्रमागत)	\
	((pipक्रमागत >= M66592_BASE_PIPENUM_BULK) && \
	 (pipक्रमागत < (M66592_BASE_PIPENUM_BULK + M66592_MAX_NUM_BULK)))
#घोषणा is_पूर्णांकerrupt_pipe(pipक्रमागत)	\
	((pipक्रमागत >= M66592_BASE_PIPENUM_INT) && \
	 (pipक्रमागत < (M66592_BASE_PIPENUM_INT + M66592_MAX_NUM_INT)))
#घोषणा is_isoc_pipe(pipक्रमागत)	\
	((pipक्रमागत >= M66592_BASE_PIPENUM_ISOC) && \
	 (pipक्रमागत < (M66592_BASE_PIPENUM_ISOC + M66592_MAX_NUM_ISOC)))

#घोषणा enable_irq_पढ़ोy(m66592, pipक्रमागत)	\
	enable_pipe_irq(m66592, pipक्रमागत, M66592_BRDYENB)
#घोषणा disable_irq_पढ़ोy(m66592, pipक्रमागत)	\
	disable_pipe_irq(m66592, pipक्रमागत, M66592_BRDYENB)
#घोषणा enable_irq_empty(m66592, pipक्रमागत)	\
	enable_pipe_irq(m66592, pipक्रमागत, M66592_BEMPENB)
#घोषणा disable_irq_empty(m66592, pipक्रमागत)	\
	disable_pipe_irq(m66592, pipक्रमागत, M66592_BEMPENB)
#घोषणा enable_irq_nrdy(m66592, pipक्रमागत)	\
	enable_pipe_irq(m66592, pipक्रमागत, M66592_NRDYENB)
#घोषणा disable_irq_nrdy(m66592, pipक्रमागत)	\
	disable_pipe_irq(m66592, pipक्रमागत, M66592_NRDYENB)

/*-------------------------------------------------------------------------*/
अटल अंतरभूत u16 m66592_पढ़ो(काष्ठा m66592 *m66592, अचिन्हित दीर्घ offset)
अणु
	वापस ioपढ़ो16(m66592->reg + offset);
पूर्ण

अटल अंतरभूत व्योम m66592_पढ़ो_fअगरo(काष्ठा m66592 *m66592,
		अचिन्हित दीर्घ offset,
		व्योम *buf, अचिन्हित दीर्घ len)
अणु
	व्योम __iomem *fअगरoaddr = m66592->reg + offset;

	अगर (m66592->pdata->on_chip) अणु
		len = (len + 3) / 4;
		ioपढ़ो32_rep(fअगरoaddr, buf, len);
	पूर्ण अन्यथा अणु
		len = (len + 1) / 2;
		ioपढ़ो16_rep(fअगरoaddr, buf, len);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम m66592_ग_लिखो(काष्ठा m66592 *m66592, u16 val,
				अचिन्हित दीर्घ offset)
अणु
	ioग_लिखो16(val, m66592->reg + offset);
पूर्ण

अटल अंतरभूत व्योम m66592_mdfy(काष्ठा m66592 *m66592, u16 val, u16 pat,
		अचिन्हित दीर्घ offset)
अणु
	u16 पंचांगp;
	पंचांगp = m66592_पढ़ो(m66592, offset);
	पंचांगp = पंचांगp & (~pat);
	पंचांगp = पंचांगp | val;
	m66592_ग_लिखो(m66592, पंचांगp, offset);
पूर्ण

#घोषणा m66592_bclr(m66592, val, offset)	\
			m66592_mdfy(m66592, 0, val, offset)
#घोषणा m66592_bset(m66592, val, offset)	\
			m66592_mdfy(m66592, val, 0, offset)

अटल अंतरभूत व्योम m66592_ग_लिखो_fअगरo(काष्ठा m66592 *m66592,
		काष्ठा m66592_ep *ep,
		व्योम *buf, अचिन्हित दीर्घ len)
अणु
	व्योम __iomem *fअगरoaddr = m66592->reg + ep->fअगरoaddr;

	अगर (m66592->pdata->on_chip) अणु
		अचिन्हित दीर्घ count;
		अचिन्हित अक्षर *pb;
		पूर्णांक i;

		count = len / 4;
		ioग_लिखो32_rep(fअगरoaddr, buf, count);

		अगर (len & 0x00000003) अणु
			pb = buf + count * 4;
			क्रम (i = 0; i < (len & 0x00000003); i++) अणु
				अगर (m66592_पढ़ो(m66592, M66592_CFBCFG))	/* le */
					ioग_लिखो8(pb[i], fअगरoaddr + (3 - i));
				अन्यथा
					ioग_लिखो8(pb[i], fअगरoaddr + i);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ odd = len & 0x0001;

		len = len / 2;
		ioग_लिखो16_rep(fअगरoaddr, buf, len);
		अगर (odd) अणु
			अचिन्हित अक्षर *p = buf + len*2;
			अगर (m66592->pdata->wr0_लघुed_to_wr1)
				m66592_bclr(m66592, M66592_MBW_16, ep->fअगरosel);
			ioग_लिखो8(*p, fअगरoaddr);
			अगर (m66592->pdata->wr0_लघुed_to_wr1)
				m66592_bset(m66592, M66592_MBW_16, ep->fअगरosel);
		पूर्ण
	पूर्ण
पूर्ण

#पूर्ण_अगर	/* अगरndef __M66592_UDC_H__ */


