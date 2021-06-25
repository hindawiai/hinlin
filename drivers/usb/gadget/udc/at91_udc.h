<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2004 by Thomas Rathbone, HP Lअसल
 * Copyright (C) 2005 by Ivan Kokshaysky
 * Copyright (C) 2006 by SAN People
 */

#अगर_अघोषित AT91_UDC_H
#घोषणा AT91_UDC_H

/*
 * USB Device Port (UDP) रेजिस्टरs.
 * Based on AT91RM9200 datasheet revision E.
 */

#घोषणा AT91_UDP_FRM_NUM	0x00		/* Frame Number Register */
#घोषणा     AT91_UDP_NUM	(0x7ff <<  0)	/* Frame Number */
#घोषणा     AT91_UDP_FRM_ERR	(1     << 16)	/* Frame Error */
#घोषणा     AT91_UDP_FRM_OK	(1     << 17)	/* Frame OK */

#घोषणा AT91_UDP_GLB_STAT	0x04		/* Global State Register */
#घोषणा     AT91_UDP_FADDEN	(1 <<  0)	/* Function Address Enable */
#घोषणा     AT91_UDP_CONFG	(1 <<  1)	/* Configured */
#घोषणा     AT91_UDP_ESR	(1 <<  2)	/* Enable Send Resume */
#घोषणा     AT91_UDP_RSMINPR	(1 <<  3)	/* Resume has been sent */
#घोषणा     AT91_UDP_RMWUPE	(1 <<  4)	/* Remote Wake Up Enable */

#घोषणा AT91_UDP_FADDR		0x08		/* Function Address Register */
#घोषणा     AT91_UDP_FADD	(0x7f << 0)	/* Function Address Value */
#घोषणा     AT91_UDP_FEN	(1    << 8)	/* Function Enable */

#घोषणा AT91_UDP_IER		0x10		/* Interrupt Enable Register */
#घोषणा AT91_UDP_IDR		0x14		/* Interrupt Disable Register */
#घोषणा AT91_UDP_IMR		0x18		/* Interrupt Mask Register */

#घोषणा AT91_UDP_ISR		0x1c		/* Interrupt Status Register */
#घोषणा     AT91_UDP_EP(n)	(1 << (n))	/* Endpoपूर्णांक Interrupt Status */
#घोषणा     AT91_UDP_RXSUSP	(1 <<  8) 	/* USB Suspend Interrupt Status */
#घोषणा     AT91_UDP_RXRSM	(1 <<  9)	/* USB Resume Interrupt Status */
#घोषणा     AT91_UDP_EXTRSM	(1 << 10)	/* External Resume Interrupt Status [AT91RM9200 only] */
#घोषणा     AT91_UDP_SOFINT	(1 << 11)	/* Start of Frame Interrupt Status */
#घोषणा     AT91_UDP_ENDBUSRES	(1 << 12)	/* End of Bus Reset Interrupt Status */
#घोषणा     AT91_UDP_WAKEUP	(1 << 13)	/* USB Wakeup Interrupt Status [AT91RM9200 only] */

#घोषणा AT91_UDP_ICR		0x20		/* Interrupt Clear Register */
#घोषणा AT91_UDP_RST_EP		0x28		/* Reset Endpoपूर्णांक Register */

#घोषणा AT91_UDP_CSR(n)		(0x30+((n)*4))	/* Endpoपूर्णांक Control/Status Registers 0-7 */
#घोषणा     AT91_UDP_TXCOMP	(1 <<  0)	/* Generates IN packet with data previously written in DPR */
#घोषणा     AT91_UDP_RX_DATA_BK0 (1 <<  1)	/* Receive Data Bank 0 */
#घोषणा     AT91_UDP_RXSETUP	(1 <<  2)	/* Send STALL to the host */
#घोषणा     AT91_UDP_STALLSENT	(1 <<  3)	/* Stall Sent / Isochronous error (Isochronous endpoपूर्णांकs) */
#घोषणा     AT91_UDP_TXPKTRDY	(1 <<  4)	/* Transmit Packet Ready */
#घोषणा     AT91_UDP_FORCESTALL	(1 <<  5)	/* Force Stall */
#घोषणा     AT91_UDP_RX_DATA_BK1 (1 <<  6)	/* Receive Data Bank 1 */
#घोषणा     AT91_UDP_सूची	(1 <<  7)	/* Transfer Direction */
#घोषणा     AT91_UDP_EPTYPE	(7 <<  8)	/* Endpoपूर्णांक Type */
#घोषणा		AT91_UDP_EPTYPE_CTRL		(0 <<  8)
#घोषणा		AT91_UDP_EPTYPE_ISO_OUT		(1 <<  8)
#घोषणा		AT91_UDP_EPTYPE_BULK_OUT	(2 <<  8)
#घोषणा		AT91_UDP_EPTYPE_INT_OUT		(3 <<  8)
#घोषणा		AT91_UDP_EPTYPE_ISO_IN		(5 <<  8)
#घोषणा		AT91_UDP_EPTYPE_BULK_IN		(6 <<  8)
#घोषणा		AT91_UDP_EPTYPE_INT_IN		(7 <<  8)
#घोषणा     AT91_UDP_DTGLE	(1 << 11)	/* Data Toggle */
#घोषणा     AT91_UDP_EPEDS	(1 << 15)	/* Endpoपूर्णांक Enable/Disable */
#घोषणा     AT91_UDP_RXBYTECNT	(0x7ff << 16)	/* Number of bytes in FIFO */

#घोषणा AT91_UDP_FDR(n)		(0x50+((n)*4))	/* Endpoपूर्णांक FIFO Data Registers 0-7 */

#घोषणा AT91_UDP_TXVC		0x74		/* Transceiver Control Register */
#घोषणा     AT91_UDP_TXVC_TXVDIS (1 << 8)	/* Transceiver Disable */
#घोषणा     AT91_UDP_TXVC_PUON   (1 << 9)	/* PullUp On [AT91SAM9260 only] */

/*-------------------------------------------------------------------------*/

/*
 * controller driver data काष्ठाures
 */

#घोषणा	NUM_ENDPOINTS	6

/*
 * hardware won't disable bus reset, or resume जबतक the controller
 * is suspended ... watching suspend helps keep the logic symmetric.
 */
#घोषणा	MINIMUS_INTERRUPTUS \
	(AT91_UDP_ENDBUSRES | AT91_UDP_RXRSM | AT91_UDP_RXSUSP)

काष्ठा at91_ep अणु
	काष्ठा usb_ep			ep;
	काष्ठा list_head		queue;
	काष्ठा at91_udc			*udc;
	व्योम __iomem			*creg;

	अचिन्हित			maxpacket:16;
	u8				पूर्णांक_mask;
	अचिन्हित			is_pingpong:1;

	अचिन्हित			stopped:1;
	अचिन्हित			is_in:1;
	अचिन्हित			is_iso:1;
	अचिन्हित			fअगरo_bank:1;
पूर्ण;

काष्ठा at91_udc_caps अणु
	पूर्णांक (*init)(काष्ठा at91_udc *udc);
	व्योम (*pullup)(काष्ठा at91_udc *udc, पूर्णांक is_on);
पूर्ण;

काष्ठा at91_udc_data अणु
	पूर्णांक	vbus_pin;		/* high == host घातering us */
	u8	vbus_active_low;	/* vbus polarity */
	u8	vbus_polled;		/* Use polling, not पूर्णांकerrupt */
	पूर्णांक	pullup_pin;		/* active == D+ pulled up */
	u8	pullup_active_low;	/* true == pullup_pin is active low */
पूर्ण;

/*
 * driver is non-SMP, and just blocks IRQs whenever it needs
 * access protection क्रम chip रेजिस्टरs or driver state
 */
काष्ठा at91_udc अणु
	काष्ठा usb_gadget		gadget;
	काष्ठा at91_ep			ep[NUM_ENDPOINTS];
	काष्ठा usb_gadget_driver	*driver;
	स्थिर काष्ठा at91_udc_caps	*caps;
	अचिन्हित			vbus:1;
	अचिन्हित			enabled:1;
	अचिन्हित			घड़ीed:1;
	अचिन्हित			suspended:1;
	अचिन्हित			req_pending:1;
	अचिन्हित			रुको_क्रम_addr_ack:1;
	अचिन्हित			रुको_क्रम_config_ack:1;
	अचिन्हित			active_suspend:1;
	u8				addr;
	काष्ठा at91_udc_data		board;
	काष्ठा clk			*iclk, *fclk;
	काष्ठा platक्रमm_device		*pdev;
	काष्ठा proc_dir_entry		*pde;
	व्योम __iomem			*udp_baseaddr;
	पूर्णांक				udp_irq;
	spinlock_t			lock;
	काष्ठा समयr_list		vbus_समयr;
	काष्ठा work_काष्ठा		vbus_समयr_work;
	काष्ठा regmap			*matrix;
पूर्ण;

अटल अंतरभूत काष्ठा at91_udc *to_udc(काष्ठा usb_gadget *g)
अणु
	वापस container_of(g, काष्ठा at91_udc, gadget);
पूर्ण

काष्ठा at91_request अणु
	काष्ठा usb_request		req;
	काष्ठा list_head		queue;
पूर्ण;

/*-------------------------------------------------------------------------*/

#अगर_घोषित VERBOSE_DEBUG
#    define VDBG		DBG
#अन्यथा
#    define VDBG(stuff...)	करोअणुपूर्णजबतक(0)
#पूर्ण_अगर

#अगर_घोषित PACKET_TRACE
#    define PACKET		VDBG
#अन्यथा
#    define PACKET(stuff...)	करोअणुपूर्णजबतक(0)
#पूर्ण_अगर

#घोषणा ERR(stuff...)		pr_err("udc: " stuff)
#घोषणा WARNING(stuff...)	pr_warn("udc: " stuff)
#घोषणा INFO(stuff...)		pr_info("udc: " stuff)
#घोषणा DBG(stuff...)		pr_debug("udc: " stuff)

#पूर्ण_अगर

