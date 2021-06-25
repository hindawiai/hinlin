<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * 7990.c -- LANCE ethernet IC generic routines.
 * This is an attempt to separate out the bits of various ethernet
 * drivers that are common because they all use the AMD 7990 LANCE
 * (Local Area Network Controller क्रम Ethernet) chip.
 *
 * Copyright (C) 05/1998 Peter Maydell <pmaydell@chiark.greenend.org.uk>
 *
 * Most of this stuff was obtained by looking at other LANCE drivers,
 * in particular a2065.[ch]. The AMD C-LANCE datasheet was also helpful.
 * NB: this was made easy by the fact that Jes Sorensen had cleaned up
 * most of a2025 and sunlance with the aim of merging them, so the
 * common code was pretty obvious.
 */
#समावेश <linux/crc32.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/in.h>
#समावेश <linux/route.h>
#समावेश <linux/माला.स>
#समावेश <linux/skbuff.h>
#समावेश <linux/pgtable.h>
#समावेश <यंत्र/irq.h>
/* Used क्रम the temporal inet entries and routing */
#समावेश <linux/socket.h>
#समावेश <linux/bitops.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/dma.h>
#अगर_घोषित CONFIG_HP300
#समावेश <यंत्र/blinken.h>
#पूर्ण_अगर

#समावेश "7990.h"

#घोषणा WRITERAP(lp, x)	out_be16(lp->base + LANCE_RAP, (x))
#घोषणा WRITERDP(lp, x)	out_be16(lp->base + LANCE_RDP, (x))
#घोषणा READRDP(lp)	in_be16(lp->base + LANCE_RDP)

#अगर IS_ENABLED(CONFIG_HPLANCE)
#समावेश "hplance.h"

#अघोषित WRITERAP
#अघोषित WRITERDP
#अघोषित READRDP

#अगर IS_ENABLED(CONFIG_MVME147_NET)

/* Lossage Factor Nine, Mr Sulu. */
#घोषणा WRITERAP(lp, x)	(lp->ग_लिखोrap(lp, x))
#घोषणा WRITERDP(lp, x)	(lp->ग_लिखोrdp(lp, x))
#घोषणा READRDP(lp)	(lp->पढ़ोrdp(lp))

#अन्यथा

/* These अंतरभूतs can be used अगर only CONFIG_HPLANCE is defined */
अटल अंतरभूत व्योम WRITERAP(काष्ठा lance_निजी *lp, __u16 value)
अणु
	करो अणु
		out_be16(lp->base + HPLANCE_REGOFF + LANCE_RAP, value);
	पूर्ण जबतक ((in_8(lp->base + HPLANCE_STATUS) & LE_ACK) == 0);
पूर्ण

अटल अंतरभूत व्योम WRITERDP(काष्ठा lance_निजी *lp, __u16 value)
अणु
	करो अणु
		out_be16(lp->base + HPLANCE_REGOFF + LANCE_RDP, value);
	पूर्ण जबतक ((in_8(lp->base + HPLANCE_STATUS) & LE_ACK) == 0);
पूर्ण

अटल अंतरभूत __u16 READRDP(काष्ठा lance_निजी *lp)
अणु
	__u16 value;
	करो अणु
		value = in_be16(lp->base + HPLANCE_REGOFF + LANCE_RDP);
	पूर्ण जबतक ((in_8(lp->base + HPLANCE_STATUS) & LE_ACK) == 0);
	वापस value;
पूर्ण

#पूर्ण_अगर
#पूर्ण_अगर /* IS_ENABLED(CONFIG_HPLANCE) */

/* debugging output macros, various flavours */
/* #घोषणा TEST_HITS */
#अगर_घोषित UNDEF
#घोषणा PRINT_RINGS() \
करो अणु \
	पूर्णांक t; \
	क्रम (t = 0; t < RX_RING_SIZE; t++) अणु \
		prपूर्णांकk("R%d: @(%02X %04X) len %04X, mblen %04X, bits %02X\n", \
		       t, ib->brx_ring[t].rmd1_hadr, ib->brx_ring[t].rmd0, \
		       ib->brx_ring[t].length, \
		       ib->brx_ring[t].mblength, ib->brx_ring[t].rmd1_bits); \
	पूर्ण \
	क्रम (t = 0; t < TX_RING_SIZE; t++) अणु \
		prपूर्णांकk("T%d: @(%02X %04X) len %04X, misc %04X, bits %02X\n", \
		       t, ib->btx_ring[t].पंचांगd1_hadr, ib->btx_ring[t].पंचांगd0, \
		       ib->btx_ring[t].length, \
		       ib->btx_ring[t].misc, ib->btx_ring[t].पंचांगd1_bits); \
	पूर्ण \
पूर्ण जबतक (0)
#अन्यथा
#घोषणा PRINT_RINGS()
#पूर्ण_अगर

/* Load the CSR रेजिस्टरs. The LANCE has to be STOPped when we करो this! */
अटल व्योम load_csrs(काष्ठा lance_निजी *lp)
अणु
	अस्थिर काष्ठा lance_init_block *aib = lp->lance_init_block;
	पूर्णांक leptr;

	leptr = LANCE_ADDR(aib);

	WRITERAP(lp, LE_CSR1);                    /* load address of init block */
	WRITERDP(lp, leptr & 0xFFFF);
	WRITERAP(lp, LE_CSR2);
	WRITERDP(lp, leptr >> 16);
	WRITERAP(lp, LE_CSR3);
	WRITERDP(lp, lp->busmaster_regval);       /* set byteswap/ALEctrl/byte ctrl */

	/* Poपूर्णांक back to csr0 */
	WRITERAP(lp, LE_CSR0);
पूर्ण

/* #घोषणा to 0 or 1 appropriately */
#घोषणा DEBUG_IRING 0
/* Set up the Lance Rx and Tx rings and the init block */
अटल व्योम lance_init_ring(काष्ठा net_device *dev)
अणु
	काष्ठा lance_निजी *lp = netdev_priv(dev);
	अस्थिर काष्ठा lance_init_block *ib = lp->init_block;
	अस्थिर काष्ठा lance_init_block *aib; /* क्रम LANCE_ADDR computations */
	पूर्णांक leptr;
	पूर्णांक i;

	aib = lp->lance_init_block;

	lp->rx_new = lp->tx_new = 0;
	lp->rx_old = lp->tx_old = 0;

	ib->mode = LE_MO_PROM;                             /* normal, enable Tx & Rx */

	/* Copy the ethernet address to the lance init block
	 * Notice that we करो a byteswap अगर we're big endian.
	 * [I think this is the right criterion; at least, sunlance,
	 * a2065 and atarilance करो the byteswap and lance.c (PC) करोesn't.
	 * However, the datasheet says that the BSWAP bit करोesn't affect
	 * the init block, so surely it should be low byte first क्रम
	 * everybody? Um.]
	 * We could define the ib->physaddr as three 16bit values and
	 * use (addr[1] << 8) | addr[0] & co, but this is more efficient.
	 */
#अगर_घोषित __BIG_ENDIAN
	ib->phys_addr[0] = dev->dev_addr[1];
	ib->phys_addr[1] = dev->dev_addr[0];
	ib->phys_addr[2] = dev->dev_addr[3];
	ib->phys_addr[3] = dev->dev_addr[2];
	ib->phys_addr[4] = dev->dev_addr[5];
	ib->phys_addr[5] = dev->dev_addr[4];
#अन्यथा
	क्रम (i = 0; i < 6; i++)
	       ib->phys_addr[i] = dev->dev_addr[i];
#पूर्ण_अगर

	अगर (DEBUG_IRING)
		prपूर्णांकk("TX rings:\n");

	lp->tx_full = 0;
	/* Setup the Tx ring entries */
	क्रम (i = 0; i < (1 << lp->lance_log_tx_bufs); i++) अणु
		leptr = LANCE_ADDR(&aib->tx_buf[i][0]);
		ib->btx_ring[i].पंचांगd0      = leptr;
		ib->btx_ring[i].पंचांगd1_hadr = leptr >> 16;
		ib->btx_ring[i].पंचांगd1_bits = 0;
		ib->btx_ring[i].length    = 0xf000; /* The ones required by पंचांगd2 */
		ib->btx_ring[i].misc      = 0;
		अगर (DEBUG_IRING)
			prपूर्णांकk("%d: 0x%8.8x\n", i, leptr);
	पूर्ण

	/* Setup the Rx ring entries */
	अगर (DEBUG_IRING)
		prपूर्णांकk("RX rings:\n");
	क्रम (i = 0; i < (1 << lp->lance_log_rx_bufs); i++) अणु
		leptr = LANCE_ADDR(&aib->rx_buf[i][0]);

		ib->brx_ring[i].rmd0      = leptr;
		ib->brx_ring[i].rmd1_hadr = leptr >> 16;
		ib->brx_ring[i].rmd1_bits = LE_R1_OWN;
		/* 0xf000 == bits that must be one (reserved, presumably) */
		ib->brx_ring[i].length    = -RX_BUFF_SIZE | 0xf000;
		ib->brx_ring[i].mblength  = 0;
		अगर (DEBUG_IRING)
			prपूर्णांकk("%d: 0x%8.8x\n", i, leptr);
	पूर्ण

	/* Setup the initialization block */

	/* Setup rx descriptor poपूर्णांकer */
	leptr = LANCE_ADDR(&aib->brx_ring);
	ib->rx_len = (lp->lance_log_rx_bufs << 13) | (leptr >> 16);
	ib->rx_ptr = leptr;
	अगर (DEBUG_IRING)
		prपूर्णांकk("RX ptr: %8.8x\n", leptr);

	/* Setup tx descriptor poपूर्णांकer */
	leptr = LANCE_ADDR(&aib->btx_ring);
	ib->tx_len = (lp->lance_log_tx_bufs << 13) | (leptr >> 16);
	ib->tx_ptr = leptr;
	अगर (DEBUG_IRING)
		prपूर्णांकk("TX ptr: %8.8x\n", leptr);

	/* Clear the multicast filter */
	ib->filter[0] = 0;
	ib->filter[1] = 0;
	PRINT_RINGS();
पूर्ण

/* LANCE must be STOPped beक्रमe we करो this, too... */
अटल पूर्णांक init_restart_lance(काष्ठा lance_निजी *lp)
अणु
	पूर्णांक i;

	WRITERAP(lp, LE_CSR0);
	WRITERDP(lp, LE_C0_INIT);

	/* Need a hook here क्रम sunlance ledma stuff */

	/* Wait क्रम the lance to complete initialization */
	क्रम (i = 0; (i < 100) && !(READRDP(lp) & (LE_C0_ERR | LE_C0_IDON)); i++)
		barrier();
	अगर ((i == 100) || (READRDP(lp) & LE_C0_ERR)) अणु
		prपूर्णांकk("LANCE unopened after %d ticks, csr0=%4.4x.\n", i, READRDP(lp));
		वापस -1;
	पूर्ण

	/* Clear IDON by writing a "1", enable पूर्णांकerrupts and start lance */
	WRITERDP(lp, LE_C0_IDON);
	WRITERDP(lp, LE_C0_INEA | LE_C0_STRT);

	वापस 0;
पूर्ण

अटल पूर्णांक lance_reset(काष्ठा net_device *dev)
अणु
	काष्ठा lance_निजी *lp = netdev_priv(dev);
	पूर्णांक status;

	/* Stop the lance */
	WRITERAP(lp, LE_CSR0);
	WRITERDP(lp, LE_C0_STOP);

	load_csrs(lp);
	lance_init_ring(dev);
	netअगर_trans_update(dev); /* prevent tx समयout */
	status = init_restart_lance(lp);
#अगर_घोषित DEBUG_DRIVER
	prपूर्णांकk("Lance restart=%d\n", status);
#पूर्ण_अगर
	वापस status;
पूर्ण

अटल पूर्णांक lance_rx(काष्ठा net_device *dev)
अणु
	काष्ठा lance_निजी *lp = netdev_priv(dev);
	अस्थिर काष्ठा lance_init_block *ib = lp->init_block;
	अस्थिर काष्ठा lance_rx_desc *rd;
	अचिन्हित अक्षर bits;
#अगर_घोषित TEST_HITS
	पूर्णांक i;
#पूर्ण_अगर

#अगर_घोषित TEST_HITS
	prपूर्णांकk("[");
	क्रम (i = 0; i < RX_RING_SIZE; i++) अणु
		अगर (i == lp->rx_new)
			prपूर्णांकk("%s",
			       ib->brx_ring[i].rmd1_bits & LE_R1_OWN ? "_" : "X");
		अन्यथा
			prपूर्णांकk("%s",
			      ib->brx_ring[i].rmd1_bits & LE_R1_OWN ? "." : "1");
	पूर्ण
	prपूर्णांकk("]");
#पूर्ण_अगर
#अगर_घोषित CONFIG_HP300
	blinken_leds(0x40, 0);
#पूर्ण_अगर
	WRITERDP(lp, LE_C0_RINT | LE_C0_INEA);     /* ack Rx पूर्णांक, reenable पूर्णांकs */
	क्रम (rd = &ib->brx_ring[lp->rx_new];     /* For each Rx ring we own... */
	     !((bits = rd->rmd1_bits) & LE_R1_OWN);
	     rd = &ib->brx_ring[lp->rx_new]) अणु

		/* We got an incomplete frame? */
		अगर ((bits & LE_R1_POK) != LE_R1_POK) अणु
			dev->stats.rx_over_errors++;
			dev->stats.rx_errors++;
			जारी;
		पूर्ण अन्यथा अगर (bits & LE_R1_ERR) अणु
			/* Count only the end frame as a rx error,
			 * not the beginning
			 */
			अगर (bits & LE_R1_BUF)
				dev->stats.rx_fअगरo_errors++;
			अगर (bits & LE_R1_CRC)
				dev->stats.rx_crc_errors++;
			अगर (bits & LE_R1_OFL)
				dev->stats.rx_over_errors++;
			अगर (bits & LE_R1_FRA)
				dev->stats.rx_frame_errors++;
			अगर (bits & LE_R1_EOP)
				dev->stats.rx_errors++;
		पूर्ण अन्यथा अणु
			पूर्णांक len = (rd->mblength & 0xfff) - 4;
			काष्ठा sk_buff *skb = netdev_alloc_skb(dev, len + 2);

			अगर (!skb) अणु
				dev->stats.rx_dropped++;
				rd->mblength = 0;
				rd->rmd1_bits = LE_R1_OWN;
				lp->rx_new = (lp->rx_new + 1) & lp->rx_ring_mod_mask;
				वापस 0;
			पूर्ण

			skb_reserve(skb, 2);           /* 16 byte align */
			skb_put(skb, len);             /* make room */
			skb_copy_to_linear_data(skb,
					 (अचिन्हित अक्षर *)&(ib->rx_buf[lp->rx_new][0]),
					 len);
			skb->protocol = eth_type_trans(skb, dev);
			netअगर_rx(skb);
			dev->stats.rx_packets++;
			dev->stats.rx_bytes += len;
		पूर्ण

		/* Return the packet to the pool */
		rd->mblength = 0;
		rd->rmd1_bits = LE_R1_OWN;
		lp->rx_new = (lp->rx_new + 1) & lp->rx_ring_mod_mask;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक lance_tx(काष्ठा net_device *dev)
अणु
	काष्ठा lance_निजी *lp = netdev_priv(dev);
	अस्थिर काष्ठा lance_init_block *ib = lp->init_block;
	अस्थिर काष्ठा lance_tx_desc *td;
	पूर्णांक i, j;
	पूर्णांक status;

#अगर_घोषित CONFIG_HP300
	blinken_leds(0x80, 0);
#पूर्ण_अगर
	/* csr0 is 2f3 */
	WRITERDP(lp, LE_C0_TINT | LE_C0_INEA);
	/* csr0 is 73 */

	j = lp->tx_old;
	क्रम (i = j; i != lp->tx_new; i = j) अणु
		td = &ib->btx_ring[i];

		/* If we hit a packet not owned by us, stop */
		अगर (td->पंचांगd1_bits & LE_T1_OWN)
			अवरोध;

		अगर (td->पंचांगd1_bits & LE_T1_ERR) अणु
			status = td->misc;

			dev->stats.tx_errors++;
			अगर (status & LE_T3_RTY)
				dev->stats.tx_पातed_errors++;
			अगर (status & LE_T3_LCOL)
				dev->stats.tx_winकरोw_errors++;

			अगर (status & LE_T3_CLOS) अणु
				dev->stats.tx_carrier_errors++;
				अगर (lp->स्वतः_select) अणु
					lp->tpe = 1 - lp->tpe;
					prपूर्णांकk("%s: Carrier Lost, trying %s\n",
					       dev->name,
					       lp->tpe ? "TPE" : "AUI");
					/* Stop the lance */
					WRITERAP(lp, LE_CSR0);
					WRITERDP(lp, LE_C0_STOP);
					lance_init_ring(dev);
					load_csrs(lp);
					init_restart_lance(lp);
					वापस 0;
				पूर्ण
			पूर्ण

			/* buffer errors and underflows turn off the transmitter */
			/* Restart the adapter */
			अगर (status & (LE_T3_BUF|LE_T3_UFL)) अणु
				dev->stats.tx_fअगरo_errors++;

				prपूर्णांकk("%s: Tx: ERR_BUF|ERR_UFL, restarting\n",
				       dev->name);
				/* Stop the lance */
				WRITERAP(lp, LE_CSR0);
				WRITERDP(lp, LE_C0_STOP);
				lance_init_ring(dev);
				load_csrs(lp);
				init_restart_lance(lp);
				वापस 0;
			पूर्ण
		पूर्ण अन्यथा अगर ((td->पंचांगd1_bits & LE_T1_POK) == LE_T1_POK) अणु
			/*
			 * So we करोn't count the packet more than once.
			 */
			td->पंचांगd1_bits &= ~(LE_T1_POK);

			/* One collision beक्रमe packet was sent. */
			अगर (td->पंचांगd1_bits & LE_T1_EONE)
				dev->stats.collisions++;

			/* More than one collision, be optimistic. */
			अगर (td->पंचांगd1_bits & LE_T1_EMORE)
				dev->stats.collisions += 2;

			dev->stats.tx_packets++;
		पूर्ण

		j = (j + 1) & lp->tx_ring_mod_mask;
	पूर्ण
	lp->tx_old = j;
	WRITERDP(lp, LE_C0_TINT | LE_C0_INEA);
	वापस 0;
पूर्ण

अटल irqवापस_t
lance_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = (काष्ठा net_device *)dev_id;
	काष्ठा lance_निजी *lp = netdev_priv(dev);
	पूर्णांक csr0;

	spin_lock(&lp->devlock);

	WRITERAP(lp, LE_CSR0);              /* LANCE Controller Status */
	csr0 = READRDP(lp);

	PRINT_RINGS();

	अगर (!(csr0 & LE_C0_INTR)) अणु     /* Check अगर any पूर्णांकerrupt has */
		spin_unlock(&lp->devlock);
		वापस IRQ_NONE;        /* been generated by the Lance. */
	पूर्ण

	/* Acknowledge all the पूर्णांकerrupt sources ASAP */
	WRITERDP(lp, csr0 & ~(LE_C0_INEA|LE_C0_TDMD|LE_C0_STOP|LE_C0_STRT|LE_C0_INIT));

	अगर ((csr0 & LE_C0_ERR)) अणु
		/* Clear the error condition */
		WRITERDP(lp, LE_C0_BABL|LE_C0_ERR|LE_C0_MISS|LE_C0_INEA);
	पूर्ण

	अगर (csr0 & LE_C0_RINT)
		lance_rx(dev);

	अगर (csr0 & LE_C0_TINT)
		lance_tx(dev);

	/* Log misc errors. */
	अगर (csr0 & LE_C0_BABL)
		dev->stats.tx_errors++;       /* Tx babble. */
	अगर (csr0 & LE_C0_MISS)
		dev->stats.rx_errors++;       /* Missed a Rx frame. */
	अगर (csr0 & LE_C0_MERR) अणु
		prपूर्णांकk("%s: Bus master arbitration failure, status %4.4x.\n",
		       dev->name, csr0);
		/* Restart the chip. */
		WRITERDP(lp, LE_C0_STRT);
	पूर्ण

	अगर (lp->tx_full && netअगर_queue_stopped(dev) && (TX_BUFFS_AVAIL >= 0)) अणु
		lp->tx_full = 0;
		netअगर_wake_queue(dev);
	पूर्ण

	WRITERAP(lp, LE_CSR0);
	WRITERDP(lp, LE_C0_BABL|LE_C0_CERR|LE_C0_MISS|LE_C0_MERR|LE_C0_IDON|LE_C0_INEA);

	spin_unlock(&lp->devlock);
	वापस IRQ_HANDLED;
पूर्ण

पूर्णांक lance_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा lance_निजी *lp = netdev_priv(dev);
	पूर्णांक res;

	/* Install the Interrupt handler. Or we could shunt this out to specअगरic drivers? */
	अगर (request_irq(lp->irq, lance_पूर्णांकerrupt, IRQF_SHARED, lp->name, dev))
		वापस -EAGAIN;

	res = lance_reset(dev);
	spin_lock_init(&lp->devlock);
	netअगर_start_queue(dev);

	वापस res;
पूर्ण
EXPORT_SYMBOL_GPL(lance_खोलो);

पूर्णांक lance_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा lance_निजी *lp = netdev_priv(dev);

	netअगर_stop_queue(dev);

	/* Stop the LANCE */
	WRITERAP(lp, LE_CSR0);
	WRITERDP(lp, LE_C0_STOP);

	मुक्त_irq(lp->irq, dev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(lance_बंद);

व्योम lance_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	prपूर्णांकk("lance_tx_timeout\n");
	lance_reset(dev);
	netअगर_trans_update(dev); /* prevent tx समयout */
	netअगर_wake_queue(dev);
पूर्ण
EXPORT_SYMBOL_GPL(lance_tx_समयout);

netdev_tx_t lance_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा lance_निजी *lp = netdev_priv(dev);
	अस्थिर काष्ठा lance_init_block *ib = lp->init_block;
	पूर्णांक entry, skblen, len;
	अटल पूर्णांक outs;
	अचिन्हित दीर्घ flags;

	netअगर_stop_queue(dev);

	अगर (!TX_BUFFS_AVAIL) अणु
		dev_consume_skb_any(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	skblen = skb->len;

#अगर_घोषित DEBUG_DRIVER
	/* dump the packet */
	अणु
		पूर्णांक i;

		क्रम (i = 0; i < 64; i++) अणु
			अगर ((i % 16) == 0)
				prपूर्णांकk("\n");
			prपूर्णांकk("%2.2x ", skb->data[i]);
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	len = (skblen <= ETH_ZLEN) ? ETH_ZLEN : skblen;
	entry = lp->tx_new & lp->tx_ring_mod_mask;
	ib->btx_ring[entry].length = (-len) | 0xf000;
	ib->btx_ring[entry].misc = 0;

	अगर (skb->len < ETH_ZLEN)
		स_रखो((व्योम *)&ib->tx_buf[entry][0], 0, ETH_ZLEN);
	skb_copy_from_linear_data(skb, (व्योम *)&ib->tx_buf[entry][0], skblen);

	/* Now, give the packet to the lance */
	ib->btx_ring[entry].पंचांगd1_bits = (LE_T1_POK|LE_T1_OWN);
	lp->tx_new = (lp->tx_new + 1) & lp->tx_ring_mod_mask;

	outs++;
	/* Kick the lance: transmit now */
	WRITERDP(lp, LE_C0_INEA | LE_C0_TDMD);
	dev_consume_skb_any(skb);

	spin_lock_irqsave(&lp->devlock, flags);
	अगर (TX_BUFFS_AVAIL)
		netअगर_start_queue(dev);
	अन्यथा
		lp->tx_full = 1;
	spin_unlock_irqrestore(&lp->devlock, flags);

	वापस NETDEV_TX_OK;
पूर्ण
EXPORT_SYMBOL_GPL(lance_start_xmit);

/* taken from the depca driver via a2065.c */
अटल व्योम lance_load_multicast(काष्ठा net_device *dev)
अणु
	काष्ठा lance_निजी *lp = netdev_priv(dev);
	अस्थिर काष्ठा lance_init_block *ib = lp->init_block;
	अस्थिर u16 *mcast_table = (u16 *)&ib->filter;
	काष्ठा netdev_hw_addr *ha;
	u32 crc;

	/* set all multicast bits */
	अगर (dev->flags & IFF_ALLMULTI) अणु
		ib->filter[0] = 0xffffffff;
		ib->filter[1] = 0xffffffff;
		वापस;
	पूर्ण
	/* clear the multicast filter */
	ib->filter[0] = 0;
	ib->filter[1] = 0;

	/* Add addresses */
	netdev_क्रम_each_mc_addr(ha, dev) अणु
		crc = ether_crc_le(6, ha->addr);
		crc = crc >> 26;
		mcast_table[crc >> 4] |= 1 << (crc & 0xf);
	पूर्ण
पूर्ण


व्योम lance_set_multicast(काष्ठा net_device *dev)
अणु
	काष्ठा lance_निजी *lp = netdev_priv(dev);
	अस्थिर काष्ठा lance_init_block *ib = lp->init_block;
	पूर्णांक stopped;

	stopped = netअगर_queue_stopped(dev);
	अगर (!stopped)
		netअगर_stop_queue(dev);

	जबतक (lp->tx_old != lp->tx_new)
		schedule();

	WRITERAP(lp, LE_CSR0);
	WRITERDP(lp, LE_C0_STOP);
	lance_init_ring(dev);

	अगर (dev->flags & IFF_PROMISC) अणु
		ib->mode |= LE_MO_PROM;
	पूर्ण अन्यथा अणु
		ib->mode &= ~LE_MO_PROM;
		lance_load_multicast(dev);
	पूर्ण
	load_csrs(lp);
	init_restart_lance(lp);

	अगर (!stopped)
		netअगर_start_queue(dev);
पूर्ण
EXPORT_SYMBOL_GPL(lance_set_multicast);

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
व्योम lance_poll(काष्ठा net_device *dev)
अणु
	काष्ठा lance_निजी *lp = netdev_priv(dev);

	spin_lock(&lp->devlock);
	WRITERAP(lp, LE_CSR0);
	WRITERDP(lp, LE_C0_STRT);
	spin_unlock(&lp->devlock);
	lance_पूर्णांकerrupt(dev->irq, dev);
पूर्ण
EXPORT_SYMBOL_GPL(lance_poll);
#पूर्ण_अगर

MODULE_LICENSE("GPL");
