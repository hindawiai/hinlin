<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Hitachi (now Renesas) SCA-II HD64572 driver क्रम Linux
 *
 * Copyright (C) 1998-2008 Krzysztof Halasa <khc@pm.waw.pl>
 *
 * Source of inक्रमmation: HD64572 SCA-II User's Manual
 *
 * We use the following SCA memory map:
 *
 * Packet buffer descriptor rings - starting from card->rambase:
 * rx_ring_buffers * माप(pkt_desc) = logical channel #0 RX ring
 * tx_ring_buffers * माप(pkt_desc) = logical channel #0 TX ring
 * rx_ring_buffers * माप(pkt_desc) = logical channel #1 RX ring (अगर used)
 * tx_ring_buffers * माप(pkt_desc) = logical channel #1 TX ring (अगर used)
 *
 * Packet data buffers - starting from card->rambase + buff_offset:
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
#समावेश "hd64572.h"

#घोषणा NAPI_WEIGHT		16

#घोषणा get_msci(port)	  (port->chan ?   MSCI1_OFFSET :   MSCI0_OFFSET)
#घोषणा get_dmac_rx(port) (port->chan ? DMAC1RX_OFFSET : DMAC0RX_OFFSET)
#घोषणा get_dmac_tx(port) (port->chan ? DMAC1TX_OFFSET : DMAC0TX_OFFSET)

#घोषणा sca_in(reg, card)	     पढ़ोb(card->scabase + (reg))
#घोषणा sca_out(value, reg, card)    ग_लिखोb(value, card->scabase + (reg))
#घोषणा sca_inw(reg, card)	     पढ़ोw(card->scabase + (reg))
#घोषणा sca_outw(value, reg, card)   ग_लिखोw(value, card->scabase + (reg))
#घोषणा sca_inl(reg, card)	     पढ़ोl(card->scabase + (reg))
#घोषणा sca_outl(value, reg, card)   ग_लिखोl(value, card->scabase + (reg))

अटल पूर्णांक sca_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget);

अटल अंतरभूत port_t* dev_to_port(काष्ठा net_device *dev)
अणु
	वापस dev_to_hdlc(dev)->priv;
पूर्ण

अटल अंतरभूत व्योम enable_पूर्णांकr(port_t *port)
अणु
	/* enable DMIB and MSCI RXINTA पूर्णांकerrupts */
	sca_outl(sca_inl(IER0, port->card) |
		 (port->chan ? 0x08002200 : 0x00080022), IER0, port->card);
पूर्ण

अटल अंतरभूत व्योम disable_पूर्णांकr(port_t *port)
अणु
	sca_outl(sca_inl(IER0, port->card) &
		 (port->chan ? 0x00FF00FF : 0xFF00FF00), IER0, port->card);
पूर्ण

अटल अंतरभूत u16 desc_असल_number(port_t *port, u16 desc, पूर्णांक transmit)
अणु
	u16 rx_buffs = port->card->rx_ring_buffers;
	u16 tx_buffs = port->card->tx_ring_buffers;

	desc %= (transmit ? tx_buffs : rx_buffs); // called with "X + 1" etc.
	वापस port->chan * (rx_buffs + tx_buffs) + transmit * rx_buffs + desc;
पूर्ण


अटल अंतरभूत u16 desc_offset(port_t *port, u16 desc, पूर्णांक transmit)
अणु
	/* Descriptor offset always fits in 16 bits */
	वापस desc_असल_number(port, desc, transmit) * माप(pkt_desc);
पूर्ण


अटल अंतरभूत pkt_desc __iomem *desc_address(port_t *port, u16 desc,
					     पूर्णांक transmit)
अणु
	वापस (pkt_desc __iomem *)(port->card->rambase +
				    desc_offset(port, desc, transmit));
पूर्ण


अटल अंतरभूत u32 buffer_offset(port_t *port, u16 desc, पूर्णांक transmit)
अणु
	वापस port->card->buff_offset +
		desc_असल_number(port, desc, transmit) * (u32)HDLC_MAX_MRU;
पूर्ण


अटल अंतरभूत व्योम sca_set_carrier(port_t *port)
अणु
	अगर (!(sca_in(get_msci(port) + ST3, port->card) & ST3_DCD)) अणु
#अगर_घोषित DEBUG_LINK
		prपूर्णांकk(KERN_DEBUG "%s: sca_set_carrier on\n",
		       port->netdev.name);
#पूर्ण_अगर
		netअगर_carrier_on(port->netdev);
	पूर्ण अन्यथा अणु
#अगर_घोषित DEBUG_LINK
		prपूर्णांकk(KERN_DEBUG "%s: sca_set_carrier off\n",
		       port->netdev.name);
#पूर्ण_अगर
		netअगर_carrier_off(port->netdev);
	पूर्ण
पूर्ण


अटल व्योम sca_init_port(port_t *port)
अणु
	card_t *card = port->card;
	u16 dmac_rx = get_dmac_rx(port), dmac_tx = get_dmac_tx(port);
	पूर्णांक transmit, i;

	port->rxin = 0;
	port->txin = 0;
	port->txlast = 0;

	क्रम (transmit = 0; transmit < 2; transmit++) अणु
		u16 buffs = transmit ? card->tx_ring_buffers
			: card->rx_ring_buffers;

		क्रम (i = 0; i < buffs; i++) अणु
			pkt_desc __iomem *desc = desc_address(port, i, transmit);
			u16 chain_off = desc_offset(port, i + 1, transmit);
			u32 buff_off = buffer_offset(port, i, transmit);

			ग_लिखोl(chain_off, &desc->cp);
			ग_लिखोl(buff_off, &desc->bp);
			ग_लिखोw(0, &desc->len);
			ग_लिखोb(0, &desc->stat);
		पूर्ण
	पूर्ण

	/* DMA disable - to halt state */
	sca_out(0, DSR_RX(port->chan), card);
	sca_out(0, DSR_TX(port->chan), card);

	/* software ABORT - to initial state */
	sca_out(DCR_ABORT, DCR_RX(port->chan), card);
	sca_out(DCR_ABORT, DCR_TX(port->chan), card);

	/* current desc addr */
	sca_outl(desc_offset(port, 0, 0), dmac_rx + CDAL, card);
	sca_outl(desc_offset(port, card->tx_ring_buffers - 1, 0),
		 dmac_rx + EDAL, card);
	sca_outl(desc_offset(port, 0, 1), dmac_tx + CDAL, card);
	sca_outl(desc_offset(port, 0, 1), dmac_tx + EDAL, card);

	/* clear frame end पूर्णांकerrupt counter */
	sca_out(DCR_CLEAR_खातापूर्ण, DCR_RX(port->chan), card);
	sca_out(DCR_CLEAR_खातापूर्ण, DCR_TX(port->chan), card);

	/* Receive */
	sca_outw(HDLC_MAX_MRU, dmac_rx + BFLL, card); /* set buffer length */
	sca_out(0x14, DMR_RX(port->chan), card); /* Chain mode, Multi-frame */
	sca_out(सूची_EOME, सूची_RX(port->chan), card); /* enable पूर्णांकerrupts */
	sca_out(DSR_DE, DSR_RX(port->chan), card); /* DMA enable */

	/* Transmit */
	sca_out(0x14, DMR_TX(port->chan), card); /* Chain mode, Multi-frame */
	sca_out(सूची_EOME, सूची_TX(port->chan), card); /* enable पूर्णांकerrupts */

	sca_set_carrier(port);
	netअगर_napi_add(port->netdev, &port->napi, sca_poll, NAPI_WEIGHT);
पूर्ण


/* MSCI पूर्णांकerrupt service */
अटल अंतरभूत व्योम sca_msci_पूर्णांकr(port_t *port)
अणु
	u16 msci = get_msci(port);
	card_t* card = port->card;

	अगर (sca_in(msci + ST1, card) & ST1_CDCD) अणु
		/* Reset MSCI CDCD status bit */
		sca_out(ST1_CDCD, msci + ST1, card);
		sca_set_carrier(port);
	पूर्ण
पूर्ण


अटल अंतरभूत व्योम sca_rx(card_t *card, port_t *port, pkt_desc __iomem *desc,
			  u16 rxin)
अणु
	काष्ठा net_device *dev = port->netdev;
	काष्ठा sk_buff *skb;
	u16 len;
	u32 buff;

	len = पढ़ोw(&desc->len);
	skb = dev_alloc_skb(len);
	अगर (!skb) अणु
		dev->stats.rx_dropped++;
		वापस;
	पूर्ण

	buff = buffer_offset(port, rxin, 0);
	स_नकल_fromio(skb->data, card->rambase + buff, len);

	skb_put(skb, len);
#अगर_घोषित DEBUG_PKT
	prपूर्णांकk(KERN_DEBUG "%s RX(%i):", dev->name, skb->len);
	debug_frame(skb);
#पूर्ण_अगर
	dev->stats.rx_packets++;
	dev->stats.rx_bytes += skb->len;
	skb->protocol = hdlc_type_trans(skb, dev);
	netअगर_receive_skb(skb);
पूर्ण


/* Receive DMA service */
अटल अंतरभूत पूर्णांक sca_rx_करोne(port_t *port, पूर्णांक budget)
अणु
	काष्ठा net_device *dev = port->netdev;
	u16 dmac = get_dmac_rx(port);
	card_t *card = port->card;
	u8 stat = sca_in(DSR_RX(port->chan), card); /* पढ़ो DMA Status */
	पूर्णांक received = 0;

	/* Reset DSR status bits */
	sca_out((stat & (DSR_EOT | DSR_EOM | DSR_BOF | DSR_COF)) | DSR_DWE,
		DSR_RX(port->chan), card);

	अगर (stat & DSR_BOF)
		/* Dropped one or more frames */
		dev->stats.rx_over_errors++;

	जबतक (received < budget) अणु
		u32 desc_off = desc_offset(port, port->rxin, 0);
		pkt_desc __iomem *desc;
		u32 cda = sca_inl(dmac + CDAL, card);

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
		पूर्ण अन्यथा अणु
			sca_rx(card, port, desc, port->rxin);
			received++;
		पूर्ण

		/* Set new error descriptor address */
		sca_outl(desc_off, dmac + EDAL, card);
		port->rxin = (port->rxin + 1) % card->rx_ring_buffers;
	पूर्ण

	/* make sure RX DMA is enabled */
	sca_out(DSR_DE, DSR_RX(port->chan), card);
	वापस received;
पूर्ण


/* Transmit DMA service */
अटल अंतरभूत व्योम sca_tx_करोne(port_t *port)
अणु
	काष्ठा net_device *dev = port->netdev;
	card_t* card = port->card;
	u8 stat;
	अचिन्हित count = 0;

	spin_lock(&port->lock);

	stat = sca_in(DSR_TX(port->chan), card); /* पढ़ो DMA Status */

	/* Reset DSR status bits */
	sca_out((stat & (DSR_EOT | DSR_EOM | DSR_BOF | DSR_COF)) | DSR_DWE,
		DSR_TX(port->chan), card);

	जबतक (1) अणु
		pkt_desc __iomem *desc = desc_address(port, port->txlast, 1);
		u8 stat = पढ़ोb(&desc->stat);

		अगर (!(stat & ST_TX_OWNRSHP))
			अवरोध; /* not yet transmitted */
		अगर (stat & ST_TX_UNDRRUN) अणु
			dev->stats.tx_errors++;
			dev->stats.tx_fअगरo_errors++;
		पूर्ण अन्यथा अणु
			dev->stats.tx_packets++;
			dev->stats.tx_bytes += पढ़ोw(&desc->len);
		पूर्ण
		ग_लिखोb(0, &desc->stat);	/* Free descriptor */
		count++;
		port->txlast = (port->txlast + 1) % card->tx_ring_buffers;
	पूर्ण

	अगर (count)
		netअगर_wake_queue(dev);
	spin_unlock(&port->lock);
पूर्ण


अटल पूर्णांक sca_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	port_t *port = container_of(napi, port_t, napi);
	u32 isr0 = sca_inl(ISR0, port->card);
	पूर्णांक received = 0;

	अगर (isr0 & (port->chan ? 0x08000000 : 0x00080000))
		sca_msci_पूर्णांकr(port);

	अगर (isr0 & (port->chan ? 0x00002000 : 0x00000020))
		sca_tx_करोne(port);

	अगर (isr0 & (port->chan ? 0x00000200 : 0x00000002))
		received = sca_rx_करोne(port, budget);

	अगर (received < budget) अणु
		napi_complete_करोne(napi, received);
		enable_पूर्णांकr(port);
	पूर्ण

	वापस received;
पूर्ण

अटल irqवापस_t sca_पूर्णांकr(पूर्णांक irq, व्योम *dev_id)
अणु
	card_t *card = dev_id;
	u32 isr0 = sca_inl(ISR0, card);
	पूर्णांक i, handled = 0;

	क्रम (i = 0; i < 2; i++) अणु
		port_t *port = get_port(card, i);
		अगर (port && (isr0 & (i ? 0x08002200 : 0x00080022))) अणु
			handled = 1;
			disable_पूर्णांकr(port);
			napi_schedule(&port->napi);
		पूर्ण
	पूर्ण

	वापस IRQ_RETVAL(handled);
पूर्ण


अटल व्योम sca_set_port(port_t *port)
अणु
	card_t* card = port->card;
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
	sca_out(port->पंचांगc, msci + TMCR, card);
	sca_out(port->पंचांगc, msci + TMCT, card);

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
	card_t* card = port->card;
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
	हाल PARITY_CRC32_PR1_CCITT: md0 = MD0_HDLC | MD0_CRC_ITU32; अवरोध;
	हाल PARITY_CRC16_PR1_CCITT: md0 = MD0_HDLC | MD0_CRC_ITU;   अवरोध;
	शेष:		     md0 = MD0_HDLC | MD0_CRC_NONE;
	पूर्ण

	sca_out(CMD_RESET, msci + CMD, card);
	sca_out(md0, msci + MD0, card);
	sca_out(0x00, msci + MD1, card); /* no address field check */
	sca_out(md2, msci + MD2, card);
	sca_out(0x7E, msci + IDL, card); /* flag अक्षरacter 0x7E */
	/* Skip the rest of underrun frame */
	sca_out(CTL_IDLE | CTL_URCT | CTL_URSKP, msci + CTL, card);
	sca_out(0x0F, msci + RNR, card); /* +1=RX DMA activation condition */
	sca_out(0x3C, msci + TFS, card); /* +1 = TX start */
	sca_out(0x38, msci + TCR, card); /* =Critical TX DMA activ condition */
	sca_out(0x38, msci + TNR0, card); /* =TX DMA activation condition */
	sca_out(0x3F, msci + TNR1, card); /* +1=TX DMA deactivation condition*/

/* We're using the following पूर्णांकerrupts:
   - RXINTA (DCD changes only)
   - DMIB (EOM - single frame transfer complete)
*/
	sca_outl(IE0_RXINTA | IE0_CDCD, msci + IE0, card);

	sca_out(port->पंचांगc, msci + TMCR, card);
	sca_out(port->पंचांगc, msci + TMCT, card);
	sca_out(port->rxs, msci + RXS, card);
	sca_out(port->txs, msci + TXS, card);
	sca_out(CMD_TX_ENABLE, msci + CMD, card);
	sca_out(CMD_RX_ENABLE, msci + CMD, card);

	sca_set_carrier(port);
	enable_पूर्णांकr(port);
	napi_enable(&port->napi);
	netअगर_start_queue(dev);
पूर्ण


अटल व्योम sca_बंद(काष्ठा net_device *dev)
अणु
	port_t *port = dev_to_port(dev);

	/* reset channel */
	sca_out(CMD_RESET, get_msci(port) + CMD, port->card);
	disable_पूर्णांकr(port);
	napi_disable(&port->napi);
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
	    parity != PARITY_CRC32_PR1_CCITT &&
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
	card_t *card = port->card;
	u16 cnt;

	prपूर्णांकk(KERN_DEBUG "RX ring: CDA=%u EDA=%u DSR=%02X in=%u %sactive",
	       sca_inl(get_dmac_rx(port) + CDAL, card),
	       sca_inl(get_dmac_rx(port) + EDAL, card),
	       sca_in(DSR_RX(port->chan), card), port->rxin,
	       sca_in(DSR_RX(port->chan), card) & DSR_DE ? "" : "in");
	क्रम (cnt = 0; cnt < port->card->rx_ring_buffers; cnt++)
		pr_cont(" %02X", पढ़ोb(&(desc_address(port, cnt, 0)->stat)));
	pr_cont("\n");

	prपूर्णांकk(KERN_DEBUG "TX ring: CDA=%u EDA=%u DSR=%02X in=%u "
	       "last=%u %sactive",
	       sca_inl(get_dmac_tx(port) + CDAL, card),
	       sca_inl(get_dmac_tx(port) + EDAL, card),
	       sca_in(DSR_TX(port->chan), card), port->txin, port->txlast,
	       sca_in(DSR_TX(port->chan), card) & DSR_DE ? "" : "in");

	क्रम (cnt = 0; cnt < port->card->tx_ring_buffers; cnt++)
		pr_cont(" %02X", पढ़ोb(&(desc_address(port, cnt, 1)->stat)));
	pr_cont("\n");

	prपूर्णांकk(KERN_DEBUG "MSCI: MD: %02x %02x %02x,"
	       " ST: %02x %02x %02x %02x %02x, FST: %02x CST: %02x %02x\n",
	       sca_in(get_msci(port) + MD0, card),
	       sca_in(get_msci(port) + MD1, card),
	       sca_in(get_msci(port) + MD2, card),
	       sca_in(get_msci(port) + ST0, card),
	       sca_in(get_msci(port) + ST1, card),
	       sca_in(get_msci(port) + ST2, card),
	       sca_in(get_msci(port) + ST3, card),
	       sca_in(get_msci(port) + ST4, card),
	       sca_in(get_msci(port) + FST, card),
	       sca_in(get_msci(port) + CST0, card),
	       sca_in(get_msci(port) + CST1, card));

	prपूर्णांकk(KERN_DEBUG "ILAR: %02x ISR: %08x %08x\n", sca_in(ILAR, card),
	       sca_inl(ISR0, card), sca_inl(ISR1, card));
पूर्ण
#पूर्ण_अगर /* DEBUG_RINGS */


अटल netdev_tx_t sca_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	port_t *port = dev_to_port(dev);
	card_t *card = port->card;
	pkt_desc __iomem *desc;
	u32 buff, len;

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
	स_नकल_toio(card->rambase + buff, skb->data, len);

	ग_लिखोw(len, &desc->len);
	ग_लिखोb(ST_TX_EOM, &desc->stat);

	port->txin = (port->txin + 1) % card->tx_ring_buffers;
	sca_outl(desc_offset(port, port->txin, 1),
		 get_dmac_tx(port) + EDAL, card);

	sca_out(DSR_DE, DSR_TX(port->chan), card); /* Enable TX DMA */

	desc = desc_address(port, port->txin + 1, 1);
	अगर (पढ़ोb(&desc->stat)) /* allow 1 packet gap */
		netअगर_stop_queue(dev);

	spin_unlock_irq(&port->lock);

	dev_kमुक्त_skb(skb);
	वापस NETDEV_TX_OK;
पूर्ण


अटल u32 sca_detect_ram(card_t *card, u8 __iomem *rambase, u32 ramsize)
अणु
	/* Round RAM size to 32 bits, fill from end to start */
	u32 i = ramsize &= ~3;

	करो अणु
		i -= 4;
		ग_लिखोl(i ^ 0x12345678, rambase + i);
	पूर्ण जबतक (i > 0);

	क्रम (i = 0; i < ramsize ; i += 4) अणु
		अगर (पढ़ोl(rambase + i) != (i ^ 0x12345678))
			अवरोध;
	पूर्ण

	वापस i;
पूर्ण


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
