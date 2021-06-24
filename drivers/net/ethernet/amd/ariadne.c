<शैली गुरु>
/*
 *  Amiga Linux/m68k Ariadne Ethernet Driver
 *
 *  तऊ Copyright 1995-2003 by Geert Uytterhoeven (geert@linux-m68k.org)
 *			     Peter De Schrijver (p2@mind.be)
 *
 *  ---------------------------------------------------------------------------
 *
 *  This program is based on
 *
 *	lance.c:	An AMD LANCE ethernet driver क्रम linux.
 *			Written 1993-94 by Donald Becker.
 *
 *	Am79C960:	PCnet(पंचांग)-ISA Single-Chip Ethernet Controller
 *			Advanced Micro Devices
 *			Publication #16907, Rev. B, Amendment/0, May 1994
 *
 *	MC68230:	Parallel Interface/Timer (PI/T)
 *			Motorola Semiconductors, December, 1983
 *
 *  ---------------------------------------------------------------------------
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License.  See the file COPYING in the मुख्य directory of the Linux
 *  distribution क्रम more details.
 *
 *  ---------------------------------------------------------------------------
 *
 *  The Ariadne is a Zorro-II board made by Village Tronic. It contains:
 *
 *	- an Am79C960 PCnet-ISA Single-Chip Ethernet Controller with both
 *	  10BASE-2 (thin coax) and 10BASE-T (UTP) connectors
 *
 *	- an MC68230 Parallel Interface/Timer configured as 2 parallel ports
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
/*#घोषणा DEBUG*/

#समावेश <linux/module.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ioport.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/init.h>
#समावेश <linux/zorro.h>
#समावेश <linux/bitops.h>

#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/amigaपूर्णांकs.h>
#समावेश <यंत्र/amigahw.h>
#समावेश <यंत्र/irq.h>

#समावेश "ariadne.h"

#अगर_घोषित ARIADNE_DEBUG
पूर्णांक ariadne_debug = ARIADNE_DEBUG;
#अन्यथा
पूर्णांक ariadne_debug = 1;
#पूर्ण_अगर

/* Macros to Fix Endianness problems */

/* Swap the Bytes in a WORD */
#घोषणा swapw(x)	(((x >> 8) & 0x00ff) | ((x << 8) & 0xff00))
/* Get the Low BYTE in a WORD */
#घोषणा lowb(x)		(x & 0xff)
/* Get the Swapped High WORD in a LONG */
#घोषणा swhighw(x)	((((x) >> 8) & 0xff00) | (((x) >> 24) & 0x00ff))
/* Get the Swapped Low WORD in a LONG */
#घोषणा swloww(x)	((((x) << 8) & 0xff00) | (((x) >> 8) & 0x00ff))

/* Transmit/Receive Ring Definitions */

#घोषणा TX_RING_SIZE	5
#घोषणा RX_RING_SIZE	16

#घोषणा PKT_BUF_SIZE	1520

/* Private Device Data */

काष्ठा ariadne_निजी अणु
	अस्थिर काष्ठा TDRE *tx_ring[TX_RING_SIZE];
	अस्थिर काष्ठा RDRE *rx_ring[RX_RING_SIZE];
	अस्थिर u_लघु *tx_buff[TX_RING_SIZE];
	अस्थिर u_लघु *rx_buff[RX_RING_SIZE];
	पूर्णांक cur_tx, cur_rx;		/* The next मुक्त ring entry */
	पूर्णांक dirty_tx;			/* The ring entries to be मुक्त()ed */
	अक्षर tx_full;
पूर्ण;

/* Structure Created in the Ariadne's RAM Buffer */

काष्ठा lancedata अणु
	काष्ठा TDRE tx_ring[TX_RING_SIZE];
	काष्ठा RDRE rx_ring[RX_RING_SIZE];
	u_लघु tx_buff[TX_RING_SIZE][PKT_BUF_SIZE / माप(u_लघु)];
	u_लघु rx_buff[RX_RING_SIZE][PKT_BUF_SIZE / माप(u_लघु)];
पूर्ण;

अटल व्योम स_नकलw(अस्थिर u_लघु *dest, u_लघु *src, पूर्णांक len)
अणु
	जबतक (len >= 2) अणु
		*(dest++) = *(src++);
		len -= 2;
	पूर्ण
	अगर (len == 1)
		*dest = (*(u_अक्षर *)src) << 8;
पूर्ण

अटल व्योम ariadne_init_ring(काष्ठा net_device *dev)
अणु
	काष्ठा ariadne_निजी *priv = netdev_priv(dev);
	अस्थिर काष्ठा lancedata *lancedata = (काष्ठा lancedata *)dev->mem_start;
	पूर्णांक i;

	netअगर_stop_queue(dev);

	priv->tx_full = 0;
	priv->cur_rx = priv->cur_tx = 0;
	priv->dirty_tx = 0;

	/* Set up TX Ring */
	क्रम (i = 0; i < TX_RING_SIZE; i++) अणु
		अस्थिर काष्ठा TDRE *t = &lancedata->tx_ring[i];
		t->TMD0 = swloww(ARIADNE_RAM +
				 दुरत्व(काष्ठा lancedata, tx_buff[i]));
		t->TMD1 = swhighw(ARIADNE_RAM +
				  दुरत्व(काष्ठा lancedata, tx_buff[i])) |
			TF_STP | TF_ENP;
		t->TMD2 = swapw((u_लघु)-PKT_BUF_SIZE);
		t->TMD3 = 0;
		priv->tx_ring[i] = &lancedata->tx_ring[i];
		priv->tx_buff[i] = lancedata->tx_buff[i];
		netdev_dbg(dev, "TX Entry %2d at %p, Buf at %p\n",
			   i, &lancedata->tx_ring[i], lancedata->tx_buff[i]);
	पूर्ण

	/* Set up RX Ring */
	क्रम (i = 0; i < RX_RING_SIZE; i++) अणु
		अस्थिर काष्ठा RDRE *r = &lancedata->rx_ring[i];
		r->RMD0 = swloww(ARIADNE_RAM +
				 दुरत्व(काष्ठा lancedata, rx_buff[i]));
		r->RMD1 = swhighw(ARIADNE_RAM +
				  दुरत्व(काष्ठा lancedata, rx_buff[i])) |
			RF_OWN;
		r->RMD2 = swapw((u_लघु)-PKT_BUF_SIZE);
		r->RMD3 = 0x0000;
		priv->rx_ring[i] = &lancedata->rx_ring[i];
		priv->rx_buff[i] = lancedata->rx_buff[i];
		netdev_dbg(dev, "RX Entry %2d at %p, Buf at %p\n",
			   i, &lancedata->rx_ring[i], lancedata->rx_buff[i]);
	पूर्ण
पूर्ण

अटल पूर्णांक ariadne_rx(काष्ठा net_device *dev)
अणु
	काष्ठा ariadne_निजी *priv = netdev_priv(dev);
	पूर्णांक entry = priv->cur_rx % RX_RING_SIZE;
	पूर्णांक i;

	/* If we own the next entry, it's a new packet. Send it up */
	जबतक (!(lowb(priv->rx_ring[entry]->RMD1) & RF_OWN)) अणु
		पूर्णांक status = lowb(priv->rx_ring[entry]->RMD1);

		अगर (status != (RF_STP | RF_ENP)) अणु	/* There was an error */
			/* There is a tricky error noted by
			 * John Murphy <murf@perftech.com> to Russ Nelson:
			 * Even with full-sized buffers it's possible क्रम a
			 * jabber packet to use two buffers, with only the
			 * last correctly noting the error
			 */
			/* Only count a general error at the end of a packet */
			अगर (status & RF_ENP)
				dev->stats.rx_errors++;
			अगर (status & RF_FRAM)
				dev->stats.rx_frame_errors++;
			अगर (status & RF_OFLO)
				dev->stats.rx_over_errors++;
			अगर (status & RF_CRC)
				dev->stats.rx_crc_errors++;
			अगर (status & RF_BUFF)
				dev->stats.rx_fअगरo_errors++;
			priv->rx_ring[entry]->RMD1 &= 0xff00 | RF_STP | RF_ENP;
		पूर्ण अन्यथा अणु
			/* Malloc up new buffer, compatible with net-3 */
			लघु pkt_len = swapw(priv->rx_ring[entry]->RMD3);
			काष्ठा sk_buff *skb;

			skb = netdev_alloc_skb(dev, pkt_len + 2);
			अगर (skb == शून्य) अणु
				क्रम (i = 0; i < RX_RING_SIZE; i++)
					अगर (lowb(priv->rx_ring[(entry + i) % RX_RING_SIZE]->RMD1) & RF_OWN)
						अवरोध;

				अगर (i > RX_RING_SIZE - 2) अणु
					dev->stats.rx_dropped++;
					priv->rx_ring[entry]->RMD1 |= RF_OWN;
					priv->cur_rx++;
				पूर्ण
				अवरोध;
			पूर्ण


			skb_reserve(skb, 2);	/* 16 byte align */
			skb_put(skb, pkt_len);	/* Make room */
			skb_copy_to_linear_data(skb,
						(स्थिर व्योम *)priv->rx_buff[entry],
						pkt_len);
			skb->protocol = eth_type_trans(skb, dev);
			netdev_dbg(dev, "RX pkt type 0x%04x from %pM to %pM data %p len %u\n",
				   ((u_लघु *)skb->data)[6],
				   skb->data + 6, skb->data,
				   skb->data, skb->len);

			netअगर_rx(skb);
			dev->stats.rx_packets++;
			dev->stats.rx_bytes += pkt_len;
		पूर्ण

		priv->rx_ring[entry]->RMD1 |= RF_OWN;
		entry = (++priv->cur_rx) % RX_RING_SIZE;
	पूर्ण

	priv->cur_rx = priv->cur_rx % RX_RING_SIZE;

	/* We should check that at least two ring entries are मुक्त.
	 * If not, we should मुक्त one and mark stats->rx_dropped++
	 */

	वापस 0;
पूर्ण

अटल irqवापस_t ariadne_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा net_device *dev = (काष्ठा net_device *)data;
	अस्थिर काष्ठा Am79C960 *lance = (काष्ठा Am79C960 *)dev->base_addr;
	काष्ठा ariadne_निजी *priv;
	पूर्णांक csr0, boguscnt;
	पूर्णांक handled = 0;

	lance->RAP = CSR0;		/* PCnet-ISA Controller Status */

	अगर (!(lance->RDP & INTR))	/* Check अगर any पूर्णांकerrupt has been */
		वापस IRQ_NONE;	/* generated by the board */

	priv = netdev_priv(dev);

	boguscnt = 10;
	जबतक ((csr0 = lance->RDP) & (ERR | RINT | TINT) && --boguscnt >= 0) अणु
		/* Acknowledge all of the current पूर्णांकerrupt sources ASAP */
		lance->RDP = csr0 & ~(INEA | TDMD | STOP | STRT | INIT);

#अगर_घोषित DEBUG
		अगर (ariadne_debug > 5) अणु
			netdev_dbg(dev, "interrupt  csr0=%#02x new csr=%#02x [",
				   csr0, lance->RDP);
			अगर (csr0 & INTR)
				pr_cont(" INTR");
			अगर (csr0 & INEA)
				pr_cont(" INEA");
			अगर (csr0 & RXON)
				pr_cont(" RXON");
			अगर (csr0 & TXON)
				pr_cont(" TXON");
			अगर (csr0 & TDMD)
				pr_cont(" TDMD");
			अगर (csr0 & STOP)
				pr_cont(" STOP");
			अगर (csr0 & STRT)
				pr_cont(" STRT");
			अगर (csr0 & INIT)
				pr_cont(" INIT");
			अगर (csr0 & ERR)
				pr_cont(" ERR");
			अगर (csr0 & BABL)
				pr_cont(" BABL");
			अगर (csr0 & CERR)
				pr_cont(" CERR");
			अगर (csr0 & MISS)
				pr_cont(" MISS");
			अगर (csr0 & MERR)
				pr_cont(" MERR");
			अगर (csr0 & RINT)
				pr_cont(" RINT");
			अगर (csr0 & TINT)
				pr_cont(" TINT");
			अगर (csr0 & IDON)
				pr_cont(" IDON");
			pr_cont(" ]\n");
		पूर्ण
#पूर्ण_अगर

		अगर (csr0 & RINT) अणु	/* Rx पूर्णांकerrupt */
			handled = 1;
			ariadne_rx(dev);
		पूर्ण

		अगर (csr0 & TINT) अणु	/* Tx-करोne पूर्णांकerrupt */
			पूर्णांक dirty_tx = priv->dirty_tx;

			handled = 1;
			जबतक (dirty_tx < priv->cur_tx) अणु
				पूर्णांक entry = dirty_tx % TX_RING_SIZE;
				पूर्णांक status = lowb(priv->tx_ring[entry]->TMD1);

				अगर (status & TF_OWN)
					अवरोध;	/* It still hasn't been Txed */

				priv->tx_ring[entry]->TMD1 &= 0xff00;

				अगर (status & TF_ERR) अणु
					/* There was an major error, log it */
					पूर्णांक err_status = priv->tx_ring[entry]->TMD3;
					dev->stats.tx_errors++;
					अगर (err_status & EF_RTRY)
						dev->stats.tx_पातed_errors++;
					अगर (err_status & EF_LCAR)
						dev->stats.tx_carrier_errors++;
					अगर (err_status & EF_LCOL)
						dev->stats.tx_winकरोw_errors++;
					अगर (err_status & EF_UFLO) अणु
						/* Ackk!  On FIFO errors the Tx unit is turned off! */
						dev->stats.tx_fअगरo_errors++;
						/* Remove this verbosity later! */
						netdev_err(dev, "Tx FIFO error! Status %04x\n",
							   csr0);
						/* Restart the chip */
						lance->RDP = STRT;
					पूर्ण
				पूर्ण अन्यथा अणु
					अगर (status & (TF_MORE | TF_ONE))
						dev->stats.collisions++;
					dev->stats.tx_packets++;
				पूर्ण
				dirty_tx++;
			पूर्ण

#अगर_अघोषित final_version
			अगर (priv->cur_tx - dirty_tx >= TX_RING_SIZE) अणु
				netdev_err(dev, "out-of-sync dirty pointer, %d vs. %d, full=%d\n",
					   dirty_tx, priv->cur_tx,
					   priv->tx_full);
				dirty_tx += TX_RING_SIZE;
			पूर्ण
#पूर्ण_अगर

			अगर (priv->tx_full && netअगर_queue_stopped(dev) &&
			    dirty_tx > priv->cur_tx - TX_RING_SIZE + 2) अणु
				/* The ring is no दीर्घer full */
				priv->tx_full = 0;
				netअगर_wake_queue(dev);
			पूर्ण

			priv->dirty_tx = dirty_tx;
		पूर्ण

		/* Log misc errors */
		अगर (csr0 & BABL) अणु
			handled = 1;
			dev->stats.tx_errors++;	/* Tx babble */
		पूर्ण
		अगर (csr0 & MISS) अणु
			handled = 1;
			dev->stats.rx_errors++;	/* Missed a Rx frame */
		पूर्ण
		अगर (csr0 & MERR) अणु
			handled = 1;
			netdev_err(dev, "Bus master arbitration failure, status %04x\n",
				   csr0);
			/* Restart the chip */
			lance->RDP = STRT;
		पूर्ण
	पूर्ण

	/* Clear any other पूर्णांकerrupt, and set पूर्णांकerrupt enable */
	lance->RAP = CSR0;		/* PCnet-ISA Controller Status */
	lance->RDP = INEA | BABL | CERR | MISS | MERR | IDON;

	अगर (ariadne_debug > 4)
		netdev_dbg(dev, "exiting interrupt, csr%d=%#04x\n",
			   lance->RAP, lance->RDP);

	वापस IRQ_RETVAL(handled);
पूर्ण

अटल पूर्णांक ariadne_खोलो(काष्ठा net_device *dev)
अणु
	अस्थिर काष्ठा Am79C960 *lance = (काष्ठा Am79C960 *)dev->base_addr;
	u_लघु in;
	u_दीर्घ version;
	पूर्णांक i;

	/* Reset the LANCE */
	in = lance->Reset;

	/* Stop the LANCE */
	lance->RAP = CSR0;		/* PCnet-ISA Controller Status */
	lance->RDP = STOP;

	/* Check the LANCE version */
	lance->RAP = CSR88;		/* Chip ID */
	version = swapw(lance->RDP);
	lance->RAP = CSR89;		/* Chip ID */
	version |= swapw(lance->RDP) << 16;
	अगर ((version & 0x00000fff) != 0x00000003) अणु
		pr_warn("Couldn't find AMD Ethernet Chip\n");
		वापस -EAGAIN;
	पूर्ण
	अगर ((version & 0x0ffff000) != 0x00003000) अणु
		pr_warn("Couldn't find Am79C960 (Wrong part number = %ld)\n",
		       (version & 0x0ffff000) >> 12);
		वापस -EAGAIN;
	पूर्ण

	netdev_dbg(dev, "Am79C960 (PCnet-ISA) Revision %ld\n",
		   (version & 0xf0000000) >> 28);

	ariadne_init_ring(dev);

	/* Miscellaneous Stuff */
	lance->RAP = CSR3;		/* Interrupt Masks and Deferral Control */
	lance->RDP = 0x0000;
	lance->RAP = CSR4;		/* Test and Features Control */
	lance->RDP = DPOLL | APAD_XMT | MFCOM | RCVCCOM | TXSTRTM | JABM;

	/* Set the Multicast Table */
	lance->RAP = CSR8;		/* Logical Address Filter, LADRF[15:0] */
	lance->RDP = 0x0000;
	lance->RAP = CSR9;		/* Logical Address Filter, LADRF[31:16] */
	lance->RDP = 0x0000;
	lance->RAP = CSR10;		/* Logical Address Filter, LADRF[47:32] */
	lance->RDP = 0x0000;
	lance->RAP = CSR11;		/* Logical Address Filter, LADRF[63:48] */
	lance->RDP = 0x0000;

	/* Set the Ethernet Hardware Address */
	lance->RAP = CSR12;		/* Physical Address Register, PADR[15:0] */
	lance->RDP = ((u_लघु *)&dev->dev_addr[0])[0];
	lance->RAP = CSR13;		/* Physical Address Register, PADR[31:16] */
	lance->RDP = ((u_लघु *)&dev->dev_addr[0])[1];
	lance->RAP = CSR14;		/* Physical Address Register, PADR[47:32] */
	lance->RDP = ((u_लघु *)&dev->dev_addr[0])[2];

	/* Set the Init Block Mode */
	lance->RAP = CSR15;		/* Mode Register */
	lance->RDP = 0x0000;

	/* Set the Transmit Descriptor Ring Poपूर्णांकer */
	lance->RAP = CSR30;		/* Base Address of Transmit Ring */
	lance->RDP = swloww(ARIADNE_RAM + दुरत्व(काष्ठा lancedata, tx_ring));
	lance->RAP = CSR31;		/* Base Address of transmit Ring */
	lance->RDP = swhighw(ARIADNE_RAM + दुरत्व(काष्ठा lancedata, tx_ring));

	/* Set the Receive Descriptor Ring Poपूर्णांकer */
	lance->RAP = CSR24;		/* Base Address of Receive Ring */
	lance->RDP = swloww(ARIADNE_RAM + दुरत्व(काष्ठा lancedata, rx_ring));
	lance->RAP = CSR25;		/* Base Address of Receive Ring */
	lance->RDP = swhighw(ARIADNE_RAM + दुरत्व(काष्ठा lancedata, rx_ring));

	/* Set the Number of RX and TX Ring Entries */
	lance->RAP = CSR76;		/* Receive Ring Length */
	lance->RDP = swapw(((u_लघु)-RX_RING_SIZE));
	lance->RAP = CSR78;		/* Transmit Ring Length */
	lance->RDP = swapw(((u_लघु)-TX_RING_SIZE));

	/* Enable Media Interface Port Auto Select (10BASE-2/10BASE-T) */
	lance->RAP = ISACSR2;		/* Miscellaneous Configuration */
	lance->IDP = ASEL;

	/* LED Control */
	lance->RAP = ISACSR5;		/* LED1 Status */
	lance->IDP = PSE|XMTE;
	lance->RAP = ISACSR6;	/* LED2 Status */
	lance->IDP = PSE|COLE;
	lance->RAP = ISACSR7;	/* LED3 Status */
	lance->IDP = PSE|RCVE;

	netअगर_start_queue(dev);

	i = request_irq(IRQ_AMIGA_PORTS, ariadne_पूर्णांकerrupt, IRQF_SHARED,
			dev->name, dev);
	अगर (i)
		वापस i;

	lance->RAP = CSR0;		/* PCnet-ISA Controller Status */
	lance->RDP = INEA | STRT;

	वापस 0;
पूर्ण

अटल पूर्णांक ariadne_बंद(काष्ठा net_device *dev)
अणु
	अस्थिर काष्ठा Am79C960 *lance = (काष्ठा Am79C960 *)dev->base_addr;

	netअगर_stop_queue(dev);

	lance->RAP = CSR112;		/* Missed Frame Count */
	dev->stats.rx_missed_errors = swapw(lance->RDP);
	lance->RAP = CSR0;		/* PCnet-ISA Controller Status */

	अगर (ariadne_debug > 1) अणु
		netdev_dbg(dev, "Shutting down ethercard, status was %02x\n",
			   lance->RDP);
		netdev_dbg(dev, "%lu packets missed\n",
			   dev->stats.rx_missed_errors);
	पूर्ण

	/* We stop the LANCE here -- it occasionally polls memory अगर we करोn't */
	lance->RDP = STOP;

	मुक्त_irq(IRQ_AMIGA_PORTS, dev);

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ariadne_reset(काष्ठा net_device *dev)
अणु
	अस्थिर काष्ठा Am79C960 *lance = (काष्ठा Am79C960 *)dev->base_addr;

	lance->RAP = CSR0;	/* PCnet-ISA Controller Status */
	lance->RDP = STOP;
	ariadne_init_ring(dev);
	lance->RDP = INEA | STRT;
	netअगर_start_queue(dev);
पूर्ण

अटल व्योम ariadne_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	अस्थिर काष्ठा Am79C960 *lance = (काष्ठा Am79C960 *)dev->base_addr;

	netdev_err(dev, "transmit timed out, status %04x, resetting\n",
		   lance->RDP);
	ariadne_reset(dev);
	netअगर_wake_queue(dev);
पूर्ण

अटल netdev_tx_t ariadne_start_xmit(काष्ठा sk_buff *skb,
				      काष्ठा net_device *dev)
अणु
	काष्ठा ariadne_निजी *priv = netdev_priv(dev);
	अस्थिर काष्ठा Am79C960 *lance = (काष्ठा Am79C960 *)dev->base_addr;
	पूर्णांक entry;
	अचिन्हित दीर्घ flags;
	पूर्णांक len = skb->len;

#अगर 0
	अगर (ariadne_debug > 3) अणु
		lance->RAP = CSR0;	/* PCnet-ISA Controller Status */
		netdev_dbg(dev, "%s: csr0 %04x\n", __func__, lance->RDP);
		lance->RDP = 0x0000;
	पूर्ण
#पूर्ण_अगर

	/* FIXME: is the 79C960 new enough to करो its own padding right ? */
	अगर (skb->len < ETH_ZLEN) अणु
		अगर (skb_padto(skb, ETH_ZLEN))
			वापस NETDEV_TX_OK;
		len = ETH_ZLEN;
	पूर्ण

	/* Fill in a Tx ring entry */

	netdev_dbg(dev, "TX pkt type 0x%04x from %pM to %pM data %p len %u\n",
		   ((u_लघु *)skb->data)[6],
		   skb->data + 6, skb->data,
		   skb->data, skb->len);

	local_irq_save(flags);

	entry = priv->cur_tx % TX_RING_SIZE;

	/* Caution: the ग_लिखो order is important here, set the base address with
	   the "ownership" bits last */

	priv->tx_ring[entry]->TMD2 = swapw((u_लघु)-skb->len);
	priv->tx_ring[entry]->TMD3 = 0x0000;
	स_नकलw(priv->tx_buff[entry], (u_लघु *)skb->data, len);

#अगर_घोषित DEBUG
	prपूर्णांक_hex_dump(KERN_DEBUG, "tx_buff: ", DUMP_PREFIX_OFFSET, 16, 1,
		       (व्योम *)priv->tx_buff[entry],
		       skb->len > 64 ? 64 : skb->len, true);
#पूर्ण_अगर

	priv->tx_ring[entry]->TMD1 = (priv->tx_ring[entry]->TMD1 & 0xff00)
		| TF_OWN | TF_STP | TF_ENP;

	dev_kमुक्त_skb(skb);

	priv->cur_tx++;
	अगर ((priv->cur_tx >= TX_RING_SIZE) &&
	    (priv->dirty_tx >= TX_RING_SIZE)) अणु

		netdev_dbg(dev, "*** Subtracting TX_RING_SIZE from cur_tx (%d) and dirty_tx (%d)\n",
			   priv->cur_tx, priv->dirty_tx);

		priv->cur_tx -= TX_RING_SIZE;
		priv->dirty_tx -= TX_RING_SIZE;
	पूर्ण
	dev->stats.tx_bytes += len;

	/* Trigger an immediate send poll */
	lance->RAP = CSR0;		/* PCnet-ISA Controller Status */
	lance->RDP = INEA | TDMD;

	अगर (lowb(priv->tx_ring[(entry + 1) % TX_RING_SIZE]->TMD1) != 0) अणु
		netअगर_stop_queue(dev);
		priv->tx_full = 1;
	पूर्ण
	local_irq_restore(flags);

	वापस NETDEV_TX_OK;
पूर्ण

अटल काष्ठा net_device_stats *ariadne_get_stats(काष्ठा net_device *dev)
अणु
	अस्थिर काष्ठा Am79C960 *lance = (काष्ठा Am79C960 *)dev->base_addr;
	लघु saved_addr;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	saved_addr = lance->RAP;
	lance->RAP = CSR112;		/* Missed Frame Count */
	dev->stats.rx_missed_errors = swapw(lance->RDP);
	lance->RAP = saved_addr;
	local_irq_restore(flags);

	वापस &dev->stats;
पूर्ण

/* Set or clear the multicast filter क्रम this adaptor.
 * num_addrs == -1	Promiscuous mode, receive all packets
 * num_addrs == 0	Normal mode, clear multicast list
 * num_addrs > 0	Multicast mode, receive normal and MC packets,
 * 			and करो best-efक्रमt filtering.
 */
अटल व्योम set_multicast_list(काष्ठा net_device *dev)
अणु
	अस्थिर काष्ठा Am79C960 *lance = (काष्ठा Am79C960 *)dev->base_addr;

	अगर (!netअगर_running(dev))
		वापस;

	netअगर_stop_queue(dev);

	/* We take the simple way out and always enable promiscuous mode */
	lance->RAP = CSR0;		/* PCnet-ISA Controller Status */
	lance->RDP = STOP;		/* Temporarily stop the lance */
	ariadne_init_ring(dev);

	अगर (dev->flags & IFF_PROMISC) अणु
		lance->RAP = CSR15;	/* Mode Register */
		lance->RDP = PROM;	/* Set promiscuous mode */
	पूर्ण अन्यथा अणु
		लघु multicast_table[4];
		पूर्णांक num_addrs = netdev_mc_count(dev);
		पूर्णांक i;
		/* We करोn't use the multicast table,
		 * but rely on upper-layer filtering
		 */
		स_रखो(multicast_table, (num_addrs == 0) ? 0 : -1,
		       माप(multicast_table));
		क्रम (i = 0; i < 4; i++) अणु
			lance->RAP = CSR8 + (i << 8);
					/* Logical Address Filter */
			lance->RDP = swapw(multicast_table[i]);
		पूर्ण
		lance->RAP = CSR15;	/* Mode Register */
		lance->RDP = 0x0000;	/* Unset promiscuous mode */
	पूर्ण

	lance->RAP = CSR0;		/* PCnet-ISA Controller Status */
	lance->RDP = INEA | STRT | IDON;/* Resume normal operation */

	netअगर_wake_queue(dev);
पूर्ण


अटल व्योम ariadne_हटाओ_one(काष्ठा zorro_dev *z)
अणु
	काष्ठा net_device *dev = zorro_get_drvdata(z);

	unरेजिस्टर_netdev(dev);
	release_mem_region(ZTWO_PADDR(dev->base_addr), माप(काष्ठा Am79C960));
	release_mem_region(ZTWO_PADDR(dev->mem_start), ARIADNE_RAM_SIZE);
	मुक्त_netdev(dev);
पूर्ण

अटल स्थिर काष्ठा zorro_device_id ariadne_zorro_tbl[] = अणु
	अणु ZORRO_PROD_VILLAGE_TRONIC_ARIADNE पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(zorro, ariadne_zorro_tbl);

अटल स्थिर काष्ठा net_device_ops ariadne_netdev_ops = अणु
	.nकरो_खोलो		= ariadne_खोलो,
	.nकरो_stop		= ariadne_बंद,
	.nकरो_start_xmit		= ariadne_start_xmit,
	.nकरो_tx_समयout		= ariadne_tx_समयout,
	.nकरो_get_stats		= ariadne_get_stats,
	.nकरो_set_rx_mode	= set_multicast_list,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address	= eth_mac_addr,
पूर्ण;

अटल पूर्णांक ariadne_init_one(काष्ठा zorro_dev *z,
			    स्थिर काष्ठा zorro_device_id *ent)
अणु
	अचिन्हित दीर्घ board = z->resource.start;
	अचिन्हित दीर्घ base_addr = board + ARIADNE_LANCE;
	अचिन्हित दीर्घ mem_start = board + ARIADNE_RAM;
	काष्ठा resource *r1, *r2;
	काष्ठा net_device *dev;
	u32 serial;
	पूर्णांक err;

	r1 = request_mem_region(base_addr, माप(काष्ठा Am79C960), "Am79C960");
	अगर (!r1)
		वापस -EBUSY;
	r2 = request_mem_region(mem_start, ARIADNE_RAM_SIZE, "RAM");
	अगर (!r2) अणु
		release_mem_region(base_addr, माप(काष्ठा Am79C960));
		वापस -EBUSY;
	पूर्ण

	dev = alloc_etherdev(माप(काष्ठा ariadne_निजी));
	अगर (dev == शून्य) अणु
		release_mem_region(base_addr, माप(काष्ठा Am79C960));
		release_mem_region(mem_start, ARIADNE_RAM_SIZE);
		वापस -ENOMEM;
	पूर्ण

	r1->name = dev->name;
	r2->name = dev->name;

	serial = be32_to_cpu(z->rom.er_SerialNumber);
	dev->dev_addr[0] = 0x00;
	dev->dev_addr[1] = 0x60;
	dev->dev_addr[2] = 0x30;
	dev->dev_addr[3] = (serial >> 16) & 0xff;
	dev->dev_addr[4] = (serial >> 8) & 0xff;
	dev->dev_addr[5] = serial & 0xff;
	dev->base_addr = (अचिन्हित दीर्घ)ZTWO_VADDR(base_addr);
	dev->mem_start = (अचिन्हित दीर्घ)ZTWO_VADDR(mem_start);
	dev->mem_end = dev->mem_start + ARIADNE_RAM_SIZE;

	dev->netdev_ops = &ariadne_netdev_ops;
	dev->watchकरोg_समयo = 5 * HZ;

	err = रेजिस्टर_netdev(dev);
	अगर (err) अणु
		release_mem_region(base_addr, माप(काष्ठा Am79C960));
		release_mem_region(mem_start, ARIADNE_RAM_SIZE);
		मुक्त_netdev(dev);
		वापस err;
	पूर्ण
	zorro_set_drvdata(z, dev);

	netdev_info(dev, "Ariadne at 0x%08lx, Ethernet Address %pM\n",
		    board, dev->dev_addr);

	वापस 0;
पूर्ण

अटल काष्ठा zorro_driver ariadne_driver = अणु
	.name		= "ariadne",
	.id_table	= ariadne_zorro_tbl,
	.probe		= ariadne_init_one,
	.हटाओ		= ariadne_हटाओ_one,
पूर्ण;

अटल पूर्णांक __init ariadne_init_module(व्योम)
अणु
	वापस zorro_रेजिस्टर_driver(&ariadne_driver);
पूर्ण

अटल व्योम __निकास ariadne_cleanup_module(व्योम)
अणु
	zorro_unरेजिस्टर_driver(&ariadne_driver);
पूर्ण

module_init(ariadne_init_module);
module_निकास(ariadne_cleanup_module);

MODULE_LICENSE("GPL");
