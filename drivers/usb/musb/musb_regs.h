<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * MUSB OTG driver रेजिस्टर defines
 *
 * Copyright 2005 Mentor Graphics Corporation
 * Copyright (C) 2005-2006 by Texas Instruments
 * Copyright (C) 2006-2007 Nokia Corporation
 */

#अगर_अघोषित __MUSB_REGS_H__
#घोषणा __MUSB_REGS_H__

#घोषणा MUSB_EP0_FIFOSIZE	64	/* This is non-configurable */

/*
 * MUSB Register bits
 */

/* POWER */
#घोषणा MUSB_POWER_ISOUPDATE	0x80
#घोषणा MUSB_POWER_SOFTCONN	0x40
#घोषणा MUSB_POWER_HSENAB	0x20
#घोषणा MUSB_POWER_HSMODE	0x10
#घोषणा MUSB_POWER_RESET	0x08
#घोषणा MUSB_POWER_RESUME	0x04
#घोषणा MUSB_POWER_SUSPENDM	0x02
#घोषणा MUSB_POWER_ENSUSPEND	0x01

/* INTRUSB */
#घोषणा MUSB_INTR_SUSPEND	0x01
#घोषणा MUSB_INTR_RESUME	0x02
#घोषणा MUSB_INTR_RESET		0x04
#घोषणा MUSB_INTR_BABBLE	0x04
#घोषणा MUSB_INTR_SOF		0x08
#घोषणा MUSB_INTR_CONNECT	0x10
#घोषणा MUSB_INTR_DISCONNECT	0x20
#घोषणा MUSB_INTR_SESSREQ	0x40
#घोषणा MUSB_INTR_VBUSERROR	0x80	/* For SESSION end */

/* DEVCTL */
#घोषणा MUSB_DEVCTL_BDEVICE	0x80
#घोषणा MUSB_DEVCTL_FSDEV	0x40
#घोषणा MUSB_DEVCTL_LSDEV	0x20
#घोषणा MUSB_DEVCTL_VBUS	0x18
#घोषणा MUSB_DEVCTL_VBUS_SHIFT	3
#घोषणा MUSB_DEVCTL_HM		0x04
#घोषणा MUSB_DEVCTL_HR		0x02
#घोषणा MUSB_DEVCTL_SESSION	0x01

/* BABBLE_CTL */
#घोषणा MUSB_BABBLE_FORCE_TXIDLE	0x80
#घोषणा MUSB_BABBLE_SW_SESSION_CTRL	0x40
#घोषणा MUSB_BABBLE_STUCK_J		0x20
#घोषणा MUSB_BABBLE_RCV_DISABLE		0x04

/* MUSB ULPI VBUSCONTROL */
#घोषणा MUSB_ULPI_USE_EXTVBUS	0x01
#घोषणा MUSB_ULPI_USE_EXTVBUSIND 0x02
/* ULPI_REG_CONTROL */
#घोषणा MUSB_ULPI_REG_REQ	(1 << 0)
#घोषणा MUSB_ULPI_REG_CMPLT	(1 << 1)
#घोषणा MUSB_ULPI_RDN_WR	(1 << 2)

/* TESTMODE */
#घोषणा MUSB_TEST_FORCE_HOST	0x80
#घोषणा MUSB_TEST_FIFO_ACCESS	0x40
#घोषणा MUSB_TEST_FORCE_FS	0x20
#घोषणा MUSB_TEST_FORCE_HS	0x10
#घोषणा MUSB_TEST_PACKET	0x08
#घोषणा MUSB_TEST_K		0x04
#घोषणा MUSB_TEST_J		0x02
#घोषणा MUSB_TEST_SE0_NAK	0x01

/* Allocate क्रम द्विगुन-packet buffering (effectively द्विगुनs asचिन्हित _SIZE) */
#घोषणा MUSB_FIFOSZ_DPB	0x10
/* Allocation size (8, 16, 32, ... 4096) */
#घोषणा MUSB_FIFOSZ_SIZE	0x0f

/* CSR0 */
#घोषणा MUSB_CSR0_FLUSHFIFO	0x0100
#घोषणा MUSB_CSR0_TXPKTRDY	0x0002
#घोषणा MUSB_CSR0_RXPKTRDY	0x0001

/* CSR0 in Peripheral mode */
#घोषणा MUSB_CSR0_P_SVDSETUPEND	0x0080
#घोषणा MUSB_CSR0_P_SVDRXPKTRDY	0x0040
#घोषणा MUSB_CSR0_P_SENDSTALL	0x0020
#घोषणा MUSB_CSR0_P_SETUPEND	0x0010
#घोषणा MUSB_CSR0_P_DATAEND	0x0008
#घोषणा MUSB_CSR0_P_SENTSTALL	0x0004

/* CSR0 in Host mode */
#घोषणा MUSB_CSR0_H_DIS_PING		0x0800
#घोषणा MUSB_CSR0_H_WR_DATATOGGLE	0x0400	/* Set to allow setting: */
#घोषणा MUSB_CSR0_H_DATATOGGLE		0x0200	/* Data toggle control */
#घोषणा MUSB_CSR0_H_NAKTIMEOUT		0x0080
#घोषणा MUSB_CSR0_H_STATUSPKT		0x0040
#घोषणा MUSB_CSR0_H_REQPKT		0x0020
#घोषणा MUSB_CSR0_H_ERROR		0x0010
#घोषणा MUSB_CSR0_H_SETUPPKT		0x0008
#घोषणा MUSB_CSR0_H_RXSTALL		0x0004

/* CSR0 bits to aव्योम zeroing (ग_लिखो zero clears, ग_लिखो 1 ignored) */
#घोषणा MUSB_CSR0_P_WZC_BITS	\
	(MUSB_CSR0_P_SENTSTALL)
#घोषणा MUSB_CSR0_H_WZC_BITS	\
	(MUSB_CSR0_H_NAKTIMEOUT | MUSB_CSR0_H_RXSTALL \
	| MUSB_CSR0_RXPKTRDY)

/* TxType/RxType */
#घोषणा MUSB_TYPE_SPEED		0xc0
#घोषणा MUSB_TYPE_SPEED_SHIFT	6
#घोषणा MUSB_TYPE_PROTO		0x30	/* Implicitly zero क्रम ep0 */
#घोषणा MUSB_TYPE_PROTO_SHIFT	4
#घोषणा MUSB_TYPE_REMOTE_END	0xf	/* Implicitly zero क्रम ep0 */

/* CONFIGDATA */
#घोषणा MUSB_CONFIGDATA_MPRXE		0x80	/* Auto bulk pkt combining */
#घोषणा MUSB_CONFIGDATA_MPTXE		0x40	/* Auto bulk pkt splitting */
#घोषणा MUSB_CONFIGDATA_BIGENDIAN	0x20
#घोषणा MUSB_CONFIGDATA_HBRXE		0x10	/* HB-ISO क्रम RX */
#घोषणा MUSB_CONFIGDATA_HBTXE		0x08	/* HB-ISO क्रम TX */
#घोषणा MUSB_CONFIGDATA_DYNFIFO		0x04	/* Dynamic FIFO sizing */
#घोषणा MUSB_CONFIGDATA_SOFTCONE	0x02	/* SoftConnect */
#घोषणा MUSB_CONFIGDATA_UTMIDW		0x01	/* Data width 0/1 => 8/16bits */

/* TXCSR in Peripheral and Host mode */
#घोषणा MUSB_TXCSR_AUTOSET		0x8000
#घोषणा MUSB_TXCSR_DMAENAB		0x1000
#घोषणा MUSB_TXCSR_FRCDATATOG		0x0800
#घोषणा MUSB_TXCSR_DMAMODE		0x0400
#घोषणा MUSB_TXCSR_CLRDATATOG		0x0040
#घोषणा MUSB_TXCSR_FLUSHFIFO		0x0008
#घोषणा MUSB_TXCSR_FIFONOTEMPTY		0x0002
#घोषणा MUSB_TXCSR_TXPKTRDY		0x0001

/* TXCSR in Peripheral mode */
#घोषणा MUSB_TXCSR_P_ISO		0x4000
#घोषणा MUSB_TXCSR_P_INCOMPTX		0x0080
#घोषणा MUSB_TXCSR_P_SENTSTALL		0x0020
#घोषणा MUSB_TXCSR_P_SENDSTALL		0x0010
#घोषणा MUSB_TXCSR_P_UNDERRUN		0x0004

/* TXCSR in Host mode */
#घोषणा MUSB_TXCSR_H_WR_DATATOGGLE	0x0200
#घोषणा MUSB_TXCSR_H_DATATOGGLE		0x0100
#घोषणा MUSB_TXCSR_H_NAKTIMEOUT		0x0080
#घोषणा MUSB_TXCSR_H_RXSTALL		0x0020
#घोषणा MUSB_TXCSR_H_ERROR		0x0004

/* TXCSR bits to aव्योम zeroing (ग_लिखो zero clears, ग_लिखो 1 ignored) */
#घोषणा MUSB_TXCSR_P_WZC_BITS	\
	(MUSB_TXCSR_P_INCOMPTX | MUSB_TXCSR_P_SENTSTALL \
	| MUSB_TXCSR_P_UNDERRUN | MUSB_TXCSR_FIFONOTEMPTY)
#घोषणा MUSB_TXCSR_H_WZC_BITS	\
	(MUSB_TXCSR_H_NAKTIMEOUT | MUSB_TXCSR_H_RXSTALL \
	| MUSB_TXCSR_H_ERROR | MUSB_TXCSR_FIFONOTEMPTY)

/* RXCSR in Peripheral and Host mode */
#घोषणा MUSB_RXCSR_AUTOCLEAR		0x8000
#घोषणा MUSB_RXCSR_DMAENAB		0x2000
#घोषणा MUSB_RXCSR_DISNYET		0x1000
#घोषणा MUSB_RXCSR_PID_ERR		0x1000
#घोषणा MUSB_RXCSR_DMAMODE		0x0800
#घोषणा MUSB_RXCSR_INCOMPRX		0x0100
#घोषणा MUSB_RXCSR_CLRDATATOG		0x0080
#घोषणा MUSB_RXCSR_FLUSHFIFO		0x0010
#घोषणा MUSB_RXCSR_DATAERROR		0x0008
#घोषणा MUSB_RXCSR_FIFOFULL		0x0002
#घोषणा MUSB_RXCSR_RXPKTRDY		0x0001

/* RXCSR in Peripheral mode */
#घोषणा MUSB_RXCSR_P_ISO		0x4000
#घोषणा MUSB_RXCSR_P_SENTSTALL		0x0040
#घोषणा MUSB_RXCSR_P_SENDSTALL		0x0020
#घोषणा MUSB_RXCSR_P_OVERRUN		0x0004

/* RXCSR in Host mode */
#घोषणा MUSB_RXCSR_H_AUTOREQ		0x4000
#घोषणा MUSB_RXCSR_H_WR_DATATOGGLE	0x0400
#घोषणा MUSB_RXCSR_H_DATATOGGLE		0x0200
#घोषणा MUSB_RXCSR_H_RXSTALL		0x0040
#घोषणा MUSB_RXCSR_H_REQPKT		0x0020
#घोषणा MUSB_RXCSR_H_ERROR		0x0004

/* RXCSR bits to aव्योम zeroing (ग_लिखो zero clears, ग_लिखो 1 ignored) */
#घोषणा MUSB_RXCSR_P_WZC_BITS	\
	(MUSB_RXCSR_P_SENTSTALL | MUSB_RXCSR_P_OVERRUN \
	| MUSB_RXCSR_RXPKTRDY)
#घोषणा MUSB_RXCSR_H_WZC_BITS	\
	(MUSB_RXCSR_H_RXSTALL | MUSB_RXCSR_H_ERROR \
	| MUSB_RXCSR_DATAERROR | MUSB_RXCSR_RXPKTRDY)

/* HUBADDR */
#घोषणा MUSB_HUBADDR_MULTI_TT		0x80


/*
 * Common USB रेजिस्टरs
 */

#घोषणा MUSB_FADDR		0x00	/* 8-bit */
#घोषणा MUSB_POWER		0x01	/* 8-bit */

#घोषणा MUSB_INTRTX		0x02	/* 16-bit */
#घोषणा MUSB_INTRRX		0x04
#घोषणा MUSB_INTRTXE		0x06
#घोषणा MUSB_INTRRXE		0x08
#घोषणा MUSB_INTRUSB		0x0A	/* 8 bit */
#घोषणा MUSB_INTRUSBE		0x0B	/* 8 bit */
#घोषणा MUSB_FRAME		0x0C
#घोषणा MUSB_INDEX		0x0E	/* 8 bit */
#घोषणा MUSB_TESTMODE		0x0F	/* 8 bit */

/*
 * Additional Control Registers
 */

#घोषणा MUSB_DEVCTL		0x60	/* 8 bit */
#घोषणा MUSB_BABBLE_CTL		0x61	/* 8 bit */

/* These are always controlled through the INDEX रेजिस्टर */
#घोषणा MUSB_TXFIFOSZ		0x62	/* 8-bit (see masks) */
#घोषणा MUSB_RXFIFOSZ		0x63	/* 8-bit (see masks) */
#घोषणा MUSB_TXFIFOADD		0x64	/* 16-bit offset shअगरted right 3 */
#घोषणा MUSB_RXFIFOADD		0x66	/* 16-bit offset shअगरted right 3 */

/* REVISIT: vctrl/vstatus: optional venकरोr uपंचांगi+phy रेजिस्टर at 0x68 */
#घोषणा MUSB_HWVERS		0x6C	/* 8 bit */
#घोषणा MUSB_ULPI_BUSCONTROL	0x70	/* 8 bit */
#घोषणा MUSB_ULPI_INT_MASK	0x72	/* 8 bit */
#घोषणा MUSB_ULPI_INT_SRC	0x73	/* 8 bit */
#घोषणा MUSB_ULPI_REG_DATA	0x74	/* 8 bit */
#घोषणा MUSB_ULPI_REG_ADDR	0x75	/* 8 bit */
#घोषणा MUSB_ULPI_REG_CONTROL	0x76	/* 8 bit */
#घोषणा MUSB_ULPI_RAW_DATA	0x77	/* 8 bit */

#घोषणा MUSB_EPINFO		0x78	/* 8 bit */
#घोषणा MUSB_RAMINFO		0x79	/* 8 bit */
#घोषणा MUSB_LINKINFO		0x7a	/* 8 bit */
#घोषणा MUSB_VPLEN		0x7b	/* 8 bit */
#घोषणा MUSB_HS_खातापूर्ण1		0x7c	/* 8 bit */
#घोषणा MUSB_FS_खातापूर्ण1		0x7d	/* 8 bit */
#घोषणा MUSB_LS_खातापूर्ण1		0x7e	/* 8 bit */

/* Offsets to endpoपूर्णांक रेजिस्टरs */
#घोषणा MUSB_TXMAXP		0x00
#घोषणा MUSB_TXCSR		0x02
#घोषणा MUSB_CSR0		MUSB_TXCSR	/* Re-used क्रम EP0 */
#घोषणा MUSB_RXMAXP		0x04
#घोषणा MUSB_RXCSR		0x06
#घोषणा MUSB_RXCOUNT		0x08
#घोषणा MUSB_COUNT0		MUSB_RXCOUNT	/* Re-used क्रम EP0 */
#घोषणा MUSB_TXTYPE		0x0A
#घोषणा MUSB_TYPE0		MUSB_TXTYPE	/* Re-used क्रम EP0 */
#घोषणा MUSB_TXINTERVAL		0x0B
#घोषणा MUSB_NAKLIMIT0		MUSB_TXINTERVAL	/* Re-used क्रम EP0 */
#घोषणा MUSB_RXTYPE		0x0C
#घोषणा MUSB_RXINTERVAL		0x0D
#घोषणा MUSB_FIFOSIZE		0x0F
#घोषणा MUSB_CONFIGDATA		MUSB_FIFOSIZE	/* Re-used क्रम EP0 */

#समावेश "tusb6010.h"		/* Needed "only" क्रम TUSB_EP0_CONF */

#घोषणा MUSB_TXCSR_MODE			0x2000

/* "bus control"/target रेजिस्टरs, क्रम host side multipoपूर्णांक (बाह्यal hubs) */
#घोषणा MUSB_TXFUNCADDR		0x00
#घोषणा MUSB_TXHUBADDR		0x02
#घोषणा MUSB_TXHUBPORT		0x03

#घोषणा MUSB_RXFUNCADDR		0x04
#घोषणा MUSB_RXHUBADDR		0x06
#घोषणा MUSB_RXHUBPORT		0x07

अटल अंतरभूत u8 musb_पढ़ो_configdata(व्योम __iomem *mbase)
अणु
	musb_ग_लिखोb(mbase, MUSB_INDEX, 0);
	वापस musb_पढ़ोb(mbase, 0x10 + MUSB_CONFIGDATA);
पूर्ण

अटल अंतरभूत व्योम musb_ग_लिखो_rxfunaddr(काष्ठा musb *musb, u8 epnum,
		u8 qh_addr_reg)
अणु
	musb_ग_लिखोb(musb->mregs,
		    musb->io.busctl_offset(epnum, MUSB_RXFUNCADDR),
		    qh_addr_reg);
पूर्ण

अटल अंतरभूत व्योम musb_ग_लिखो_rxhubaddr(काष्ठा musb *musb, u8 epnum,
		u8 qh_h_addr_reg)
अणु
	musb_ग_लिखोb(musb->mregs, musb->io.busctl_offset(epnum, MUSB_RXHUBADDR),
			qh_h_addr_reg);
पूर्ण

अटल अंतरभूत व्योम musb_ग_लिखो_rxhubport(काष्ठा musb *musb, u8 epnum,
		u8 qh_h_port_reg)
अणु
	musb_ग_लिखोb(musb->mregs, musb->io.busctl_offset(epnum, MUSB_RXHUBPORT),
			qh_h_port_reg);
पूर्ण

अटल अंतरभूत व्योम musb_ग_लिखो_txfunaddr(काष्ठा musb *musb, u8 epnum,
		u8 qh_addr_reg)
अणु
	musb_ग_लिखोb(musb->mregs,
		    musb->io.busctl_offset(epnum, MUSB_TXFUNCADDR),
		    qh_addr_reg);
पूर्ण

अटल अंतरभूत व्योम musb_ग_लिखो_txhubaddr(काष्ठा musb *musb, u8 epnum,
		u8 qh_addr_reg)
अणु
	musb_ग_लिखोb(musb->mregs, musb->io.busctl_offset(epnum, MUSB_TXHUBADDR),
			qh_addr_reg);
पूर्ण

अटल अंतरभूत व्योम musb_ग_लिखो_txhubport(काष्ठा musb *musb, u8 epnum,
		u8 qh_h_port_reg)
अणु
	musb_ग_लिखोb(musb->mregs, musb->io.busctl_offset(epnum, MUSB_TXHUBPORT),
			qh_h_port_reg);
पूर्ण

अटल अंतरभूत u8 musb_पढ़ो_rxfunaddr(काष्ठा musb *musb, u8 epnum)
अणु
	वापस musb_पढ़ोb(musb->mregs,
			  musb->io.busctl_offset(epnum, MUSB_RXFUNCADDR));
पूर्ण

अटल अंतरभूत u8 musb_पढ़ो_rxhubaddr(काष्ठा musb *musb, u8 epnum)
अणु
	वापस musb_पढ़ोb(musb->mregs,
			  musb->io.busctl_offset(epnum, MUSB_RXHUBADDR));
पूर्ण

अटल अंतरभूत u8 musb_पढ़ो_rxhubport(काष्ठा musb *musb, u8 epnum)
अणु
	वापस musb_पढ़ोb(musb->mregs,
			  musb->io.busctl_offset(epnum, MUSB_RXHUBPORT));
पूर्ण

अटल अंतरभूत u8 musb_पढ़ो_txfunaddr(काष्ठा musb *musb, u8 epnum)
अणु
	वापस musb_पढ़ोb(musb->mregs,
			  musb->io.busctl_offset(epnum, MUSB_TXFUNCADDR));
पूर्ण

अटल अंतरभूत u8 musb_पढ़ो_txhubaddr(काष्ठा musb *musb, u8 epnum)
अणु
	वापस musb_पढ़ोb(musb->mregs,
			  musb->io.busctl_offset(epnum, MUSB_TXHUBADDR));
पूर्ण

अटल अंतरभूत u8 musb_पढ़ो_txhubport(काष्ठा musb *musb, u8 epnum)
अणु
	वापस musb_पढ़ोb(musb->mregs,
			  musb->io.busctl_offset(epnum, MUSB_TXHUBPORT));
पूर्ण

#पूर्ण_अगर	/* __MUSB_REGS_H__ */
