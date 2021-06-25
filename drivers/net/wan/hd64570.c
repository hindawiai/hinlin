<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Hitachi SCA HD64570 driver क्रम Linux
 *
 * Copyright (C) 1998-2003 Krzysztof Halasa <khc@pm.waw.pl>
 *
 * Source of inक्रमmation: Hitachi HD64570 SCA User's Manual
 *
 * We use the following SCA memory map:
 *
 * Packet buffer descriptor rings - starting from winbase or win0base:
 * rx_ring_buffers * माप(pkt_desc) = logical channel #0 RX ring
 * tx_ring_buffers * माप(pkt_desc) = logical channel #0 TX ring
 * rx_ring_buffers * माप(pkt_desc) = logical channel #1 RX ring (अगर used)
 * tx_ring_buffers * माप(pkt_desc) = logical channel #1 TX ring (अगर used)
 *
 * Packet data buffers - starting from winbase + buff_offset:
 * rx_ring_buffers * HDLC_MAX_MRU     = logical channel #0 RX buffers
 * tx_ring_buffers * HDLC_MAX_MRU     = logical channel #0 TX buffers
 * rx_ring_buffers * HDLC_MAX_MRU     = logical channel #0 RX buffers (अगर used)
 * tx_ring_buffers * HDLC_MAX_MRU     = logical channel #0 TX buffers (अगर used)
 */

#समावेश <linux/bitops.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fcntl.h>
#समावेश <linux/hdlc.h>
#समावेश <linux/in.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <यंत्र/पन.स>
#समावेश <linux/uaccess.h>
#समावेश "hd64570.h"

#घोषणा get_msci(port)	  (phy_node(port) ?   MSCI1_OFFSET :   MSCI0_OFFSET)
#घोषणा get_dmac_rx(port) (phy_node(port) ? DMAC1RX_OFFSET : DMAC0RX_OFFSET)
#घोषणा get_dmac_tx(port) (phy_node(port) ? DMAC1TX_OFFSET : DMAC0TX_OFFSET)

#घोषणा SCA_INTR_MSCI(node)    (node ? 0x10 : 0x01)
#घोषणा SCA_INTR_DMAC_RX(node) (node ? 0x20 : 0x02)
#घोषणा SCA_INTR_DMAC_TX(node) (node ? 0x40 : 0x04)


अटल अंतरभूत काष्ठा net_device *port_to_dev(port_t *port)
अणु
	वापस port->dev;
पूर्ण

अटल अंतरभूत पूर्णांक sca_पूर्णांकr_status(card_t *card)
अणु
	u8 result = 0;
	u8 isr0 = sca_in(ISR0, card);
	u8 isr1 = sca_in(ISR1, card);

	अगर (isr1 & 0x03) result |= SCA_INTR_DMAC_RX(0);
	अगर (isr1 & 0x0C) result |= SCA_INTR_DMAC_TX(0);
	अगर (isr1 & 0x30) result |= SCA_INTR_DMAC_RX(1);
	अगर (isr1 & 0xC0) result |= SCA_INTR_DMAC_TX(1);
	अगर (isr0 & 0x0F) result |= SCA_INTR_MSCI(0);
	अगर (isr0 & 0xF0) result |= SCA_INTR_MSCI(1);

	अगर (!(result & SCA_INTR_DMAC_TX(0)))
		अगर (sca_in(DSR_TX(0), card) & DSR_EOM)
			result |= SCA_INTR_DMAC_TX(0);
	अगर (!(result & SCA_INTR_DMAC_TX(1)))
		अगर (sca_in(DSR_TX(1), card) & DSR_EOM)
			result |= SCA_INTR_DMAC_TX(1);

	वापस result;
पूर्ण

अटल अंतरभूत port_t* dev_to_port(काष्ठा net_device *dev)
अणु
	वापस dev_to_hdlc(dev)->priv;
पूर्ण

अटल अंतरभूत u16 next_desc(port_t *port, u16 desc, पूर्णांक transmit)
अणु
	वापस (desc + 1) % (transmit ? port_to_card(port)->tx_ring_buffers
			     : port_to_card(port)->rx_ring_buffers);
पूर्ण


अटल अंतरभूत u16 desc_असल_number(port_t *port, u16 desc, पूर्णांक transmit)
अणु
	u16 rx_buffs = port_to_card(port)->rx_ring_buffers;
	u16 tx_buffs = port_to_card(port)->tx_ring_buffers;

	desc %= (transmit ? tx_buffs : rx_buffs); // called with "X + 1" etc.
	वापस log_node(port) * (rx_buffs + tx_buffs) +
		transmit * rx_buffs + desc;
पूर्ण


अटल अंतरभूत u16 desc_offset(port_t *port, u16 desc, पूर्णांक transmit)
अणु
	/* Descriptor offset always fits in 16 bits */
	वापस desc_असल_number(port, desc, transmit) * माप(pkt_desc);
पूर्ण


अटल अंतरभूत pkt_desc __iomem *desc_address(port_t *port, u16 desc,
					     पूर्णांक transmit)
अणु
#अगर_घोषित PAGE0_ALWAYS_MAPPED
	वापस (pkt_desc __iomem *)(win0base(port_to_card(port))
				    + desc_offset(port, desc, transmit));
#अन्यथा
	वापस (pkt_desc __iomem *)(winbase(port_to_card(port))
				    + desc_offset(port, desc, transmit));
#पूर्ण_अगर
पूर्ण


अटल अंतरभूत u32 buffer_offset(port_t *port, u16 desc, पूर्णांक transmit)
अणु
	वापस port_to_card(port)->buff_offset +
		desc_असल_number(port, desc, transmit) * (u32)HDLC_MAX_MRU;
पूर्ण


अटल अंतरभूत व्योम sca_set_carrier(port_t *port)
अणु
	अगर (!(sca_in(get_msci(port) + ST3, port_to_card(port)) & ST3_DCD)) अणु
#अगर_घोषित DEBUG_LINK
		prपूर्णांकk(KERN_DEBUG "%s: sca_set_carrier on\n",
		       port_to_dev(port)->name);
#पूर्ण_अगर
		netअगर_carrier_on(port_to_dev(port));
	पूर्ण अन्यथा अणु
#अगर_घोषित DEBUG_LINK
		prपूर्णांकk(KERN_DEBUG "%s: sca_set_carrier off\n",
		       port_to_dev(port)->name);
#पूर्ण_अगर
		netअगर_carrier_off(port_to_dev(port));
	पूर्ण
पूर्ण


अटल व्योम sca_init_port(port_t *port)
अणु
	card_t *card = port_to_card(port);
	पूर्णांक transmit, i;

	port->rxin = 0;
	port->txin = 0;
	port->txlast = 0;

#अगर_अघोषित PAGE0_ALWAYS_MAPPED
	खोलोwin(card, 0);
#पूर्ण_अगर

	क्रम (transmit = 0; transmit < 2; transmit++) अणु
		u16 dmac = transmit ? get_dmac_tx(port) : get_dmac_rx(port);
		u16 buffs = transmit ? card->tx_ring_buffers
			: card->rx_ring_buffers;

		क्रम (i = 0; i < buffs; i++) अणु
			pkt_desc __iomem *desc = desc_address(port, i, transmit);
			u16 chain_off = desc_offset(port, i + 1, transmit);
			u32 buff_off = buffer_offset(port, i, transmit);

			ग_लिखोw(chain_off, &desc->cp);
			ग_लिखोl(buff_off, &desc->bp);
			ग_लिखोw(0, &desc->len);
			ग_लिखोb(0, &desc->stat);
		पूर्ण

		/* DMA disable - to halt state */
		sca_out(0, transmit ? DSR_TX(phy_node(port)) :
			DSR_RX(phy_node(port)), card);
		/* software ABORT - to initial state */
		sca_out(DCR_ABORT, transmit ? DCR_TX(phy_node(port)) :
			DCR_RX(phy_node(port)), card);

		/* current desc addr */
		sca_out(0, dmac + CPB, card); /* poपूर्णांकer base */
		sca_outw(desc_offset(port, 0, transmit), dmac + CDAL, card);
		अगर (!transmit)
			sca_outw(desc_offset(port, buffs - 1, transmit),
				 dmac + EDAL, card);
		अन्यथा
			sca_outw(desc_offset(port, 0, transmit), dmac + EDAL,
				 card);

		/* clear frame end पूर्णांकerrupt counter */
		sca_out(DCR_CLEAR_खातापूर्ण, transmit ? DCR_TX(phy_node(port)) :
			DCR_RX(phy_node(port)), card);

		अगर (!transmit) अणु /* Receive */
			/* set buffer length */
			sca_outw(HDLC_MAX_MRU, dmac + BFLL, card);
			/* Chain mode, Multi-frame */
			sca_out(0x14, DMR_RX(phy_node(port)), card);
			sca_out(सूची_EOME | सूची_BOFE, सूची_RX(phy_node(port)),
				card);
			/* DMA enable */
			sca_out(DSR_DE, DSR_RX(phy_node(port)), card);
		पूर्ण अन्यथा अणु	/* Transmit */
			/* Chain mode, Multi-frame */
			sca_out(0x14, DMR_TX(phy_node(port)), card);
			/* enable underflow पूर्णांकerrupts */
			sca_out(सूची_BOFE, सूची_TX(phy_node(port)), card);
		पूर्ण
	पूर्ण
	sca_set_carrier(port);
पूर्ण


#अगर_घोषित NEED_SCA_MSCI_INTR
/* MSCI पूर्णांकerrupt service */
अटल अंतरभूत व्योम sca_msci_पूर्णांकr(port_t *port)
अणु
	u16 msci = get_msci(port);
	card_t* card = port_to_card(port);
	u8 stat = sca_in(msci + ST1, card); /* पढ़ो MSCI ST1 status */

	/* Reset MSCI TX underrun and CDCD status bit */
	sca_out(stat & (ST1_UDRN | ST1_CDCD), msci + ST1, card);

	अगर (stat & ST1_UDRN) अणु
		/* TX Underrun error detected */
		port_to_dev(port)->stats.tx_errors++;
		port_to_dev(port)->stats.tx_fअगरo_errors++;
	पूर्ण

	अगर (stat & ST1_CDCD)
		sca_set_carrier(port);
पूर्ण
#पूर्ण_अगर


अटल अंतरभूत व्योम sca_rx(card_t *card, port_t *port, pkt_desc __iomem *desc,
			  u16 rxin)
अणु
	काष्ठा net_device *dev = port_to_dev(port);
	काष्ठा sk_buff *skb;
	u16 len;
	u32 buff;
	u32 maxlen;
	u8 page;

	len = पढ़ोw(&desc->len);
	skb = dev_alloc_skb(len);
	अगर (!skb) अणु
		dev->stats.rx_dropped++;
		वापस;
	पूर्ण

	buff = buffer_offset(port, rxin, 0);
	page = buff / winsize(card);
	buff = buff % winsize(card);
	maxlen = winsize(card) - buff;

	खोलोwin(card, page);

	अगर (len > maxlen) अणु
		स_नकल_fromio(skb->data, winbase(card) + buff, maxlen);
		खोलोwin(card, page + 1);
		स_नकल_fromio(skb->data + maxlen, winbase(card), len - maxlen);
	पूर्ण अन्यथा
		स_नकल_fromio(skb->data, winbase(card) + buff, len);

#अगर_अघोषित PAGE0_ALWAYS_MAPPED
	खोलोwin(card, 0);	/* select pkt_desc table page back */
#पूर्ण_अगर
	skb_put(skb, len);
#अगर_घोषित DEBUG_PKT
	prपूर्णांकk(KERN_DEBUG "%s RX(%i):", dev->name, skb->len);
	debug_frame(skb);
#पूर्ण_अगर
	dev->stats.rx_packets++;
	dev->stats.rx_bytes += skb->len;
	skb->protocol = hdlc_type_trans(skb, dev);
	netअगर_rx(skb);
पूर्ण


/* Receive DMA पूर्णांकerrupt service */
अटल अंतरभूत व्योम sca_rx_पूर्णांकr(port_t *port)
अणु
	काष्ठा net_device *dev = port_to_dev(port);
	u16 dmac = get_dmac_rx(port);
	card_t *card = port_to_card(port);
	u8 stat = sca_in(DSR_RX(phy_node(port)), card); /* पढ़ो DMA Status */

	/* Reset DSR status bits */
	sca_out((stat & (DSR_EOT | DSR_EOM | DSR_BOF | DSR_COF)) | DSR_DWE,
		DSR_RX(phy_node(port)), card);

	अगर (stat & DSR_BOF)
		/* Dropped one or more frames */
		dev->stats.rx_over_errors++;

	जबतक (1) अणु
		u32 desc_off = desc_offset(port, port->rxin, 0);
		pkt_desc __iomem *desc;
		u32 cda = sca_inw(dmac + CDAL, card);

		अगर ((cda >= desc_off) && (cda < desc_off + माप(pkt_desc)))
			अवरोध;	/* No frame received */

		desc = desc_address(port, port->rxin, 0);
		stat = पढ़ोb(&desc->stat);
		अगर (!(stat & ST_RX_EOM))
			port->rxpart = 1; /* partial frame received */
		अन्यथा अगर ((stat & ST_ERROR_MASK) || port->rxpart) अणु
			dev->stats.rx_errors++;
			अगर (stat & ST_RX_OVERRUN)
				dev->stats.rx_fअगरo_errors++;
			अन्यथा अगर ((stat & (ST_RX_SHORT | ST_RX_ABORT |
					  ST_RX_RESBIT)) || port->rxpart)
				dev->stats.rx_frame_errors++;
			अन्यथा अगर (stat & ST_RX_CRC)
				dev->stats.rx_crc_errors++;
			अगर (stat & ST_RX_EOM)
				port->rxpart = 0; /* received last fragment */
		पूर्ण अन्यथा
			sca_rx(card, port, desc, port->rxin);

		/* Set new error descriptor address */
		sca_outw(desc_off, dmac + EDAL, card);
		port->rxin = next_desc(port, port->rxin, 0);
	पूर्ण

	/* make sure RX DMA is enabled */
	sca_out(DSR_DE, DSR_RX(phy_node(port)), card);
पूर्ण


/* Transmit DMA पूर्णांकerrupt service */
अटल अंतरभूत व्योम sca_tx_पूर्णांकr(port_t *port)
अणु
	काष्ठा net_device *dev = port_to_dev(port);
	u16 dmac = get_dmac_tx(port);
	card_t* card = port_to_card(port);
	u8 stat;

	spin_lock(&port->lock);

	stat = sca_in(DSR_TX(phy_node(port)), card); /* पढ़ो DMA Status */

	/* Reset DSR status bits */
	sca_out((stat & (DSR_EOT | DSR_EOM | DSR_BOF | DSR_COF)) | DSR_DWE,
		DSR_TX(phy_node(port)), card);

	जबतक (1) अणु
		pkt_desc __iomem *desc;

		u32 desc_off = desc_offset(port, port->txlast, 1);
		u32 cda = sca_inw(dmac + CDAL, card);
		अगर ((cda >= desc_off) && (cda < desc_off + माप(pkt_desc)))
			अवरोध;	/* Transmitter is/will_be sending this frame */

		desc = desc_address(port, port->txlast, 1);
		dev->stats.tx_packets++;
		dev->stats.tx_bytes += पढ़ोw(&desc->len);
		ग_लिखोb(0, &desc->stat);	/* Free descriptor */
		port->txlast = next_desc(port, port->txlast, 1);
	पूर्ण

	netअगर_wake_queue(dev);
	spin_unlock(&port->lock);
पूर्ण


अटल irqवापस_t sca_पूर्णांकr(पूर्णांक irq, व्योम* dev_id)
अणु
	card_t *card = dev_id;
	पूर्णांक i;
	u8 stat;
	पूर्णांक handled = 0;
	u8 page = sca_get_page(card);

	जबतक((stat = sca_पूर्णांकr_status(card)) != 0) अणु
		handled = 1;
		क्रम (i = 0; i < 2; i++) अणु
			port_t *port = get_port(card, i);
			अगर (port) अणु
				अगर (stat & SCA_INTR_MSCI(i))
					sca_msci_पूर्णांकr(port);

				अगर (stat & SCA_INTR_DMAC_RX(i))
					sca_rx_पूर्णांकr(port);

				अगर (stat & SCA_INTR_DMAC_TX(i))
					sca_tx_पूर्णांकr(port);
			पूर्ण
		पूर्ण
	पूर्ण

	खोलोwin(card, page);		/* Restore original page */
	वापस IRQ_RETVAL(handled);
पूर्ण


अटल व्योम sca_set_port(port_t *port)
अणु
	card_t* card = port_to_card(port);
	u16 msci = get_msci(port);
	u8 md2 = sca_in(msci + MD2, card);
	अचिन्हित पूर्णांक पंचांगc, br = 10, brv = 1024;


	अगर (port->settings.घड़ी_rate > 0) अणु
		/* Try lower br क्रम better accuracy*/
		करो अणु
			br--;
			brv >>= 1; /* brv = 2^9 = 512 max in specs */

			/* Baud Rate = CLOCK_BASE / TMC / 2^BR */
			पंचांगc = CLOCK_BASE / brv / port->settings.घड़ी_rate;
		पूर्णजबतक (br > 1 && पंचांगc <= 128);

		अगर (पंचांगc < 1) अणु
			पंचांगc = 1;
			br = 0;	/* For baud=CLOCK_BASE we use पंचांगc=1 br=0 */
			brv = 1;
		पूर्ण अन्यथा अगर (पंचांगc > 255)
			पंचांगc = 256; /* पंचांगc=0 means 256 - low baud rates */

		port->settings.घड़ी_rate = CLOCK_BASE / brv / पंचांगc;
	पूर्ण अन्यथा अणु
		br = 9; /* Minimum घड़ी rate */
		पंचांगc = 256;	/* 8bit = 0 */
		port->settings.घड़ी_rate = CLOCK_BASE / (256 * 512);
	पूर्ण

	port->rxs = (port->rxs & ~CLK_BRG_MASK) | br;
	port->txs = (port->txs & ~CLK_BRG_MASK) | br;
	port->पंचांगc = पंचांगc;

	/* baud भागisor - समय स्थिरant*/
	sca_out(port->पंचांगc, msci + TMC, card);

	/* Set BRG bits */
	sca_out(port->rxs, msci + RXS, card);
	sca_out(port->txs, msci + TXS, card);

	अगर (port->settings.loopback)
		md2 |= MD2_LOOPBACK;
	अन्यथा
		md2 &= ~MD2_LOOPBACK;

	sca_out(md2, msci + MD2, card);

पूर्ण


अटल व्योम sca_खोलो(काष्ठा net_device *dev)
अणु
	port_t *port = dev_to_port(dev);
	card_t* card = port_to_card(port);
	u16 msci = get_msci(port);
	u8 md0, md2;

	चयन(port->encoding) अणु
	हाल ENCODING_NRZ:	md2 = MD2_NRZ;		अवरोध;
	हाल ENCODING_NRZI:	md2 = MD2_NRZI;		अवरोध;
	हाल ENCODING_FM_MARK:	md2 = MD2_FM_MARK;	अवरोध;
	हाल ENCODING_FM_SPACE:	md2 = MD2_FM_SPACE;	अवरोध;
	शेष:		md2 = MD2_MANCHESTER;
	पूर्ण

	अगर (port->settings.loopback)
		md2 |= MD2_LOOPBACK;

	चयन(port->parity) अणु
	हाल PARITY_CRC16_PR0:	     md0 = MD0_HDLC | MD0_CRC_16_0;  अवरोध;
	हाल PARITY_CRC16_PR1:	     md0 = MD0_HDLC | MD0_CRC_16;    अवरोध;
	हाल PARITY_CRC16_PR0_CCITT: md0 = MD0_HDLC | MD0_CRC_ITU_0; अवरोध;
	हाल PARITY_CRC16_PR1_CCITT: md0 = MD0_HDLC | MD0_CRC_ITU;   अवरोध;
	शेष:		     md0 = MD0_HDLC | MD0_CRC_NONE;
	पूर्ण

	sca_out(CMD_RESET, msci + CMD, card);
	sca_out(md0, msci + MD0, card);
	sca_out(0x00, msci + MD1, card); /* no address field check */
	sca_out(md2, msci + MD2, card);
	sca_out(0x7E, msci + IDL, card); /* flag अक्षरacter 0x7E */
	sca_out(CTL_IDLE, msci + CTL, card);

	/* Allow at least 8 bytes beक्रमe requesting RX DMA operation */
	/* TX with higher priority and possibly with लघुer transfers */
	sca_out(0x07, msci + RRC, card); /* +1=RXRDY/DMA activation condition*/
	sca_out(0x10, msci + TRC0, card); /* = TXRDY/DMA activation condition*/
	sca_out(0x14, msci + TRC1, card); /* +1=TXRDY/DMA deactiv condition */

/* We're using the following पूर्णांकerrupts:
   - TXINT (DMAC completed all transmisions, underrun or DCD change)
   - all DMA पूर्णांकerrupts
*/
	sca_set_carrier(port);

	/* MSCI TX INT and RX INT A IRQ enable */
	sca_out(IE0_TXINT | IE0_RXINTA, msci + IE0, card);
	sca_out(IE1_UDRN | IE1_CDCD, msci + IE1, card);
	sca_out(sca_in(IER0, card) | (phy_node(port) ? 0xC0 : 0x0C),
		IER0, card); /* TXINT and RXINT */
	/* enable DMA IRQ */
	sca_out(sca_in(IER1, card) | (phy_node(port) ? 0xF0 : 0x0F),
		IER1, card);

	sca_out(port->पंचांगc, msci + TMC, card); /* Restore रेजिस्टरs */
	sca_out(port->rxs, msci + RXS, card);
	sca_out(port->txs, msci + TXS, card);
	sca_out(CMD_TX_ENABLE, msci + CMD, card);
	sca_out(CMD_RX_ENABLE, msci + CMD, card);

	netअगर_start_queue(dev);
पूर्ण


अटल व्योम sca_बंद(काष्ठा net_device *dev)
अणु
	port_t *port = dev_to_port(dev);
	card_t* card = port_to_card(port);

	/* reset channel */
	sca_out(CMD_RESET, get_msci(port) + CMD, port_to_card(port));
	/* disable MSCI पूर्णांकerrupts */
	sca_out(sca_in(IER0, card) & (phy_node(port) ? 0x0F : 0xF0),
		IER0, card);
	/* disable DMA पूर्णांकerrupts */
	sca_out(sca_in(IER1, card) & (phy_node(port) ? 0x0F : 0xF0),
		IER1, card);

	netअगर_stop_queue(dev);
पूर्ण


अटल पूर्णांक sca_attach(काष्ठा net_device *dev, अचिन्हित लघु encoding,
		      अचिन्हित लघु parity)
अणु
	अगर (encoding != ENCODING_NRZ &&
	    encoding != ENCODING_NRZI &&
	    encoding != ENCODING_FM_MARK &&
	    encoding != ENCODING_FM_SPACE &&
	    encoding != ENCODING_MANCHESTER)
		वापस -EINVAL;

	अगर (parity != PARITY_NONE &&
	    parity != PARITY_CRC16_PR0 &&
	    parity != PARITY_CRC16_PR1 &&
	    parity != PARITY_CRC16_PR0_CCITT &&
	    parity != PARITY_CRC16_PR1_CCITT)
		वापस -EINVAL;

	dev_to_port(dev)->encoding = encoding;
	dev_to_port(dev)->parity = parity;
	वापस 0;
पूर्ण


#अगर_घोषित DEBUG_RINGS
अटल व्योम sca_dump_rings(काष्ठा net_device *dev)
अणु
	port_t *port = dev_to_port(dev);
	card_t *card = port_to_card(port);
	u16 cnt;
#अगर_अघोषित PAGE0_ALWAYS_MAPPED
	u8 page = sca_get_page(card);

	खोलोwin(card, 0);
#पूर्ण_अगर

	prपूर्णांकk(KERN_DEBUG "RX ring: CDA=%u EDA=%u DSR=%02X in=%u %sactive",
	       sca_inw(get_dmac_rx(port) + CDAL, card),
	       sca_inw(get_dmac_rx(port) + EDAL, card),
	       sca_in(DSR_RX(phy_node(port)), card), port->rxin,
	       sca_in(DSR_RX(phy_node(port)), card) & DSR_DE ? "" : "in");
	क्रम (cnt = 0; cnt < port_to_card(port)->rx_ring_buffers; cnt++)
		pr_cont(" %02X", पढ़ोb(&(desc_address(port, cnt, 0)->stat)));
	pr_cont("\n");

	prपूर्णांकk(KERN_DEBUG "TX ring: CDA=%u EDA=%u DSR=%02X in=%u "
	       "last=%u %sactive",
	       sca_inw(get_dmac_tx(port) + CDAL, card),
	       sca_inw(get_dmac_tx(port) + EDAL, card),
	       sca_in(DSR_TX(phy_node(port)), card), port->txin, port->txlast,
	       sca_in(DSR_TX(phy_node(port)), card) & DSR_DE ? "" : "in");

	क्रम (cnt = 0; cnt < port_to_card(port)->tx_ring_buffers; cnt++)
		pr_cont(" %02X", पढ़ोb(&(desc_address(port, cnt, 1)->stat)));
	pr_cont("\n");

	prपूर्णांकk(KERN_DEBUG "MSCI: MD: %02x %02x %02x, ST: %02x %02x %02x %02x,"
	       " FST: %02x CST: %02x %02x\n",
	       sca_in(get_msci(port) + MD0, card),
	       sca_in(get_msci(port) + MD1, card),
	       sca_in(get_msci(port) + MD2, card),
	       sca_in(get_msci(port) + ST0, card),
	       sca_in(get_msci(port) + ST1, card),
	       sca_in(get_msci(port) + ST2, card),
	       sca_in(get_msci(port) + ST3, card),
	       sca_in(get_msci(port) + FST, card),
	       sca_in(get_msci(port) + CST0, card),
	       sca_in(get_msci(port) + CST1, card));

	prपूर्णांकk(KERN_DEBUG "ISR: %02x %02x %02x\n", sca_in(ISR0, card),
	       sca_in(ISR1, card), sca_in(ISR2, card));

#अगर_अघोषित PAGE0_ALWAYS_MAPPED
	खोलोwin(card, page); /* Restore original page */
#पूर्ण_अगर
पूर्ण
#पूर्ण_अगर /* DEBUG_RINGS */


अटल netdev_tx_t sca_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	port_t *port = dev_to_port(dev);
	card_t *card = port_to_card(port);
	pkt_desc __iomem *desc;
	u32 buff, len;
	u8 page;
	u32 maxlen;

	spin_lock_irq(&port->lock);

	desc = desc_address(port, port->txin + 1, 1);
	BUG_ON(पढ़ोb(&desc->stat)); /* previous xmit should stop queue */

#अगर_घोषित DEBUG_PKT
	prपूर्णांकk(KERN_DEBUG "%s TX(%i):", dev->name, skb->len);
	debug_frame(skb);
#पूर्ण_अगर

	desc = desc_address(port, port->txin, 1);
	buff = buffer_offset(port, port->txin, 1);
	len = skb->len;
	page = buff / winsize(card);
	buff = buff % winsize(card);
	maxlen = winsize(card) - buff;

	खोलोwin(card, page);
	अगर (len > maxlen) अणु
		स_नकल_toio(winbase(card) + buff, skb->data, maxlen);
		खोलोwin(card, page + 1);
		स_नकल_toio(winbase(card), skb->data + maxlen, len - maxlen);
	पूर्ण अन्यथा
		स_नकल_toio(winbase(card) + buff, skb->data, len);

#अगर_अघोषित PAGE0_ALWAYS_MAPPED
	खोलोwin(card, 0);	/* select pkt_desc table page back */
#पूर्ण_अगर
	ग_लिखोw(len, &desc->len);
	ग_लिखोb(ST_TX_EOM, &desc->stat);

	port->txin = next_desc(port, port->txin, 1);
	sca_outw(desc_offset(port, port->txin, 1),
		 get_dmac_tx(port) + EDAL, card);

	sca_out(DSR_DE, DSR_TX(phy_node(port)), card); /* Enable TX DMA */

	desc = desc_address(port, port->txin + 1, 1);
	अगर (पढ़ोb(&desc->stat)) /* allow 1 packet gap */
		netअगर_stop_queue(dev);

	spin_unlock_irq(&port->lock);

	dev_kमुक्त_skb(skb);
	वापस NETDEV_TX_OK;
पूर्ण


#अगर_घोषित NEED_DETECT_RAM
अटल u32 sca_detect_ram(card_t *card, u8 __iomem *rambase, u32 ramsize)
अणु
	/* Round RAM size to 32 bits, fill from end to start */
	u32 i = ramsize &= ~3;
	u32 size = winsize(card);

	खोलोwin(card, (i - 4) / size); /* select last winकरोw */

	करो अणु
		i -= 4;
		अगर ((i + 4) % size == 0)
			खोलोwin(card, i / size);
		ग_लिखोl(i ^ 0x12345678, rambase + i % size);
	पूर्ण जबतक (i > 0);

	क्रम (i = 0; i < ramsize ; i += 4) अणु
		अगर (i % size == 0)
			खोलोwin(card, i / size);

		अगर (पढ़ोl(rambase + i % size) != (i ^ 0x12345678))
			अवरोध;
	पूर्ण

	वापस i;
पूर्ण
#पूर्ण_अगर /* NEED_DETECT_RAM */


अटल व्योम sca_init(card_t *card, पूर्णांक रुको_states)
अणु
	sca_out(रुको_states, WCRL, card); /* Wait Control */
	sca_out(रुको_states, WCRM, card);
	sca_out(रुको_states, WCRH, card);

	sca_out(0, DMER, card);	/* DMA Master disable */
	sca_out(0x03, PCR, card); /* DMA priority */
	sca_out(0, DSR_RX(0), card); /* DMA disable - to halt state */
	sca_out(0, DSR_TX(0), card);
	sca_out(0, DSR_RX(1), card);
	sca_out(0, DSR_TX(1), card);
	sca_out(DMER_DME, DMER, card); /* DMA Master enable */
पूर्ण
