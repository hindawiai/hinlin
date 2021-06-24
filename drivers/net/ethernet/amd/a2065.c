<शैली गुरु>
/*
 * Amiga Linux/68k A2065 Ethernet Driver
 *
 * (C) Copyright 1995-2003 by Geert Uytterhoeven <geert@linux-m68k.org>
 *
 * Fixes and tips by:
 *	- Janos Farkas (CHEXUM@sparta.banki.hu)
 *	- Jes Degn Soerensen (jds@kom.auc.dk)
 *	- Matt Domsch (Matt_Domsch@dell.com)
 *
 * ----------------------------------------------------------------------------
 *
 * This program is based on
 *
 *	ariadne.?:	Amiga Linux/68k Ariadne Ethernet Driver
 *			(C) Copyright 1995 by Geert Uytterhoeven,
 *                                            Peter De Schrijver
 *
 *	lance.c:	An AMD LANCE ethernet driver क्रम linux.
 *			Written 1993-94 by Donald Becker.
 *
 *	Am79C960:	PCnet(पंचांग)-ISA Single-Chip Ethernet Controller
 *			Advanced Micro Devices
 *			Publication #16907, Rev. B, Amendment/0, May 1994
 *
 * ----------------------------------------------------------------------------
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of the Linux
 * distribution क्रम more details.
 *
 * ----------------------------------------------------------------------------
 *
 * The A2065 is a Zorro-II board made by Commoकरोre/Ameristar. It contains:
 *
 *	- an Am7990 Local Area Network Controller क्रम Ethernet (LANCE) with
 *	  both 10BASE-2 (thin coax) and AUI (DB-15) connectors
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

/*#घोषणा DEBUG*/
/*#घोषणा TEST_HITS*/

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/module.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/माला.स>
#समावेश <linux/init.h>
#समावेश <linux/crc32.h>
#समावेश <linux/zorro.h>
#समावेश <linux/bitops.h>

#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/amigaपूर्णांकs.h>
#समावेश <यंत्र/amigahw.h>

#समावेश "a2065.h"

/* Transmit/Receive Ring Definitions */

#घोषणा LANCE_LOG_TX_BUFFERS	(2)
#घोषणा LANCE_LOG_RX_BUFFERS	(4)

#घोषणा TX_RING_SIZE		(1 << LANCE_LOG_TX_BUFFERS)
#घोषणा RX_RING_SIZE		(1 << LANCE_LOG_RX_BUFFERS)

#घोषणा TX_RING_MOD_MASK	(TX_RING_SIZE - 1)
#घोषणा RX_RING_MOD_MASK	(RX_RING_SIZE - 1)

#घोषणा PKT_BUF_SIZE		(1544)
#घोषणा RX_BUFF_SIZE            PKT_BUF_SIZE
#घोषणा TX_BUFF_SIZE            PKT_BUF_SIZE

/* Layout of the Lance's RAM Buffer */

काष्ठा lance_init_block अणु
	अचिन्हित लघु mode;		/* Pre-set mode (reg. 15) */
	अचिन्हित अक्षर phys_addr[6];     /* Physical ethernet address */
	अचिन्हित filter[2];		/* Multicast filter. */

	/* Receive and transmit ring base, aदीर्घ with extra bits. */
	अचिन्हित लघु rx_ptr;		/* receive descriptor addr */
	अचिन्हित लघु rx_len;		/* receive len and high addr */
	अचिन्हित लघु tx_ptr;		/* transmit descriptor addr */
	अचिन्हित लघु tx_len;		/* transmit len and high addr */

	/* The Tx and Rx ring entries must aligned on 8-byte boundaries. */
	काष्ठा lance_rx_desc brx_ring[RX_RING_SIZE];
	काष्ठा lance_tx_desc btx_ring[TX_RING_SIZE];

	अक्षर rx_buf[RX_RING_SIZE][RX_BUFF_SIZE];
	अक्षर tx_buf[TX_RING_SIZE][TX_BUFF_SIZE];
पूर्ण;

/* Private Device Data */

काष्ठा lance_निजी अणु
	अक्षर *name;
	अस्थिर काष्ठा lance_regs *ll;
	अस्थिर काष्ठा lance_init_block *init_block;	    /* Hosts view */
	अस्थिर काष्ठा lance_init_block *lance_init_block; /* Lance view */

	पूर्णांक rx_new, tx_new;
	पूर्णांक rx_old, tx_old;

	पूर्णांक lance_log_rx_bufs, lance_log_tx_bufs;
	पूर्णांक rx_ring_mod_mask, tx_ring_mod_mask;

	पूर्णांक tpe;		      /* cable-selection is TPE */
	पूर्णांक स्वतः_select;	      /* cable-selection by carrier */
	अचिन्हित लघु busmaster_regval;

	काष्ठा समयr_list         multicast_समयr;
	काष्ठा net_device	  *dev;
पूर्ण;

#घोषणा LANCE_ADDR(x) ((पूर्णांक)(x) & ~0xff000000)

/* Load the CSR रेजिस्टरs */
अटल व्योम load_csrs(काष्ठा lance_निजी *lp)
अणु
	अस्थिर काष्ठा lance_regs *ll = lp->ll;
	अस्थिर काष्ठा lance_init_block *aib = lp->lance_init_block;
	पूर्णांक leptr = LANCE_ADDR(aib);

	ll->rap = LE_CSR1;
	ll->rdp = (leptr & 0xFFFF);
	ll->rap = LE_CSR2;
	ll->rdp = leptr >> 16;
	ll->rap = LE_CSR3;
	ll->rdp = lp->busmaster_regval;

	/* Poपूर्णांक back to csr0 */
	ll->rap = LE_CSR0;
पूर्ण

/* Setup the Lance Rx and Tx rings */
अटल व्योम lance_init_ring(काष्ठा net_device *dev)
अणु
	काष्ठा lance_निजी *lp = netdev_priv(dev);
	अस्थिर काष्ठा lance_init_block *ib = lp->init_block;
	अस्थिर काष्ठा lance_init_block *aib = lp->lance_init_block;
					/* क्रम LANCE_ADDR computations */
	पूर्णांक leptr;
	पूर्णांक i;

	/* Lock out other processes जबतक setting up hardware */
	netअगर_stop_queue(dev);
	lp->rx_new = lp->tx_new = 0;
	lp->rx_old = lp->tx_old = 0;

	ib->mode = 0;

	/* Copy the ethernet address to the lance init block
	 * Note that on the sparc you need to swap the ethernet address.
	 */
	ib->phys_addr[0] = dev->dev_addr[1];
	ib->phys_addr[1] = dev->dev_addr[0];
	ib->phys_addr[2] = dev->dev_addr[3];
	ib->phys_addr[3] = dev->dev_addr[2];
	ib->phys_addr[4] = dev->dev_addr[5];
	ib->phys_addr[5] = dev->dev_addr[4];

	/* Setup the Tx ring entries */
	netdev_dbg(dev, "TX rings:\n");
	क्रम (i = 0; i <= 1 << lp->lance_log_tx_bufs; i++) अणु
		leptr = LANCE_ADDR(&aib->tx_buf[i][0]);
		ib->btx_ring[i].पंचांगd0      = leptr;
		ib->btx_ring[i].पंचांगd1_hadr = leptr >> 16;
		ib->btx_ring[i].पंचांगd1_bits = 0;
		ib->btx_ring[i].length    = 0xf000; /* The ones required by पंचांगd2 */
		ib->btx_ring[i].misc      = 0;
		अगर (i < 3)
			netdev_dbg(dev, "%d: 0x%08x\n", i, leptr);
	पूर्ण

	/* Setup the Rx ring entries */
	netdev_dbg(dev, "RX rings:\n");
	क्रम (i = 0; i < 1 << lp->lance_log_rx_bufs; i++) अणु
		leptr = LANCE_ADDR(&aib->rx_buf[i][0]);

		ib->brx_ring[i].rmd0      = leptr;
		ib->brx_ring[i].rmd1_hadr = leptr >> 16;
		ib->brx_ring[i].rmd1_bits = LE_R1_OWN;
		ib->brx_ring[i].length    = -RX_BUFF_SIZE | 0xf000;
		ib->brx_ring[i].mblength  = 0;
		अगर (i < 3)
			netdev_dbg(dev, "%d: 0x%08x\n", i, leptr);
	पूर्ण

	/* Setup the initialization block */

	/* Setup rx descriptor poपूर्णांकer */
	leptr = LANCE_ADDR(&aib->brx_ring);
	ib->rx_len = (lp->lance_log_rx_bufs << 13) | (leptr >> 16);
	ib->rx_ptr = leptr;
	netdev_dbg(dev, "RX ptr: %08x\n", leptr);

	/* Setup tx descriptor poपूर्णांकer */
	leptr = LANCE_ADDR(&aib->btx_ring);
	ib->tx_len = (lp->lance_log_tx_bufs << 13) | (leptr >> 16);
	ib->tx_ptr = leptr;
	netdev_dbg(dev, "TX ptr: %08x\n", leptr);

	/* Clear the multicast filter */
	ib->filter[0] = 0;
	ib->filter[1] = 0;
पूर्ण

अटल पूर्णांक init_restart_lance(काष्ठा lance_निजी *lp)
अणु
	अस्थिर काष्ठा lance_regs *ll = lp->ll;
	पूर्णांक i;

	ll->rap = LE_CSR0;
	ll->rdp = LE_C0_INIT;

	/* Wait क्रम the lance to complete initialization */
	क्रम (i = 0; (i < 100) && !(ll->rdp & (LE_C0_ERR | LE_C0_IDON)); i++)
		barrier();
	अगर ((i == 100) || (ll->rdp & LE_C0_ERR)) अणु
		pr_err("unopened after %d ticks, csr0=%04x\n", i, ll->rdp);
		वापस -EIO;
	पूर्ण

	/* Clear IDON by writing a "1", enable पूर्णांकerrupts and start lance */
	ll->rdp = LE_C0_IDON;
	ll->rdp = LE_C0_INEA | LE_C0_STRT;

	वापस 0;
पूर्ण

अटल पूर्णांक lance_rx(काष्ठा net_device *dev)
अणु
	काष्ठा lance_निजी *lp = netdev_priv(dev);
	अस्थिर काष्ठा lance_init_block *ib = lp->init_block;
	अस्थिर काष्ठा lance_regs *ll = lp->ll;
	अस्थिर काष्ठा lance_rx_desc *rd;
	अचिन्हित अक्षर bits;

#अगर_घोषित TEST_HITS
	पूर्णांक i;
	अक्षर buf[RX_RING_SIZE + 1];

	क्रम (i = 0; i < RX_RING_SIZE; i++) अणु
		अक्षर r1_own = ib->brx_ring[i].rmd1_bits & LE_R1_OWN;
		अगर (i == lp->rx_new)
			buf[i] = r1_own ? '_' : 'X';
		अन्यथा
			buf[i] = r1_own ? '.' : '1';
	पूर्ण
	buf[RX_RING_SIZE] = 0;

	pr_debug("RxRing TestHits: [%s]\n", buf);
#पूर्ण_अगर

	ll->rdp = LE_C0_RINT | LE_C0_INEA;
	क्रम (rd = &ib->brx_ring[lp->rx_new];
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

			skb_reserve(skb, 2);		/* 16 byte align */
			skb_put(skb, len);		/* make room */
			skb_copy_to_linear_data(skb,
				 (अचिन्हित अक्षर *)&ib->rx_buf[lp->rx_new][0],
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
	अस्थिर काष्ठा lance_regs *ll = lp->ll;
	अस्थिर काष्ठा lance_tx_desc *td;
	पूर्णांक i, j;
	पूर्णांक status;

	/* csr0 is 2f3 */
	ll->rdp = LE_C0_TINT | LE_C0_INEA;
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
					netdev_err(dev, "Carrier Lost, trying %s\n",
						   lp->tpe ? "TPE" : "AUI");
					/* Stop the lance */
					ll->rap = LE_CSR0;
					ll->rdp = LE_C0_STOP;
					lance_init_ring(dev);
					load_csrs(lp);
					init_restart_lance(lp);
					वापस 0;
				पूर्ण
			पूर्ण

			/* buffer errors and underflows turn off
			 * the transmitter, so restart the adapter
			 */
			अगर (status & (LE_T3_BUF | LE_T3_UFL)) अणु
				dev->stats.tx_fअगरo_errors++;

				netdev_err(dev, "Tx: ERR_BUF|ERR_UFL, restarting\n");
				/* Stop the lance */
				ll->rap = LE_CSR0;
				ll->rdp = LE_C0_STOP;
				lance_init_ring(dev);
				load_csrs(lp);
				init_restart_lance(lp);
				वापस 0;
			पूर्ण
		पूर्ण अन्यथा अगर ((td->पंचांगd1_bits & LE_T1_POK) == LE_T1_POK) अणु
			/* So we करोn't count the packet more than once. */
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
	ll->rdp = LE_C0_TINT | LE_C0_INEA;
	वापस 0;
पूर्ण

अटल पूर्णांक lance_tx_buffs_avail(काष्ठा lance_निजी *lp)
अणु
	अगर (lp->tx_old <= lp->tx_new)
		वापस lp->tx_old + lp->tx_ring_mod_mask - lp->tx_new;
	वापस lp->tx_old - lp->tx_new - 1;
पूर्ण

अटल irqवापस_t lance_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = dev_id;
	काष्ठा lance_निजी *lp = netdev_priv(dev);
	अस्थिर काष्ठा lance_regs *ll = lp->ll;
	पूर्णांक csr0;

	ll->rap = LE_CSR0;		/* LANCE Controller Status */
	csr0 = ll->rdp;

	अगर (!(csr0 & LE_C0_INTR))	/* Check अगर any पूर्णांकerrupt has */
		वापस IRQ_NONE;	/* been generated by the Lance. */

	/* Acknowledge all the पूर्णांकerrupt sources ASAP */
	ll->rdp = csr0 & ~(LE_C0_INEA | LE_C0_TDMD | LE_C0_STOP | LE_C0_STRT |
			   LE_C0_INIT);

	अगर (csr0 & LE_C0_ERR) अणु
		/* Clear the error condition */
		ll->rdp = LE_C0_BABL | LE_C0_ERR | LE_C0_MISS | LE_C0_INEA;
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
		netdev_err(dev, "Bus master arbitration failure, status %04x\n",
			   csr0);
		/* Restart the chip. */
		ll->rdp = LE_C0_STRT;
	पूर्ण

	अगर (netअगर_queue_stopped(dev) && lance_tx_buffs_avail(lp) > 0)
		netअगर_wake_queue(dev);

	ll->rap = LE_CSR0;
	ll->rdp = (LE_C0_BABL | LE_C0_CERR | LE_C0_MISS | LE_C0_MERR |
		   LE_C0_IDON | LE_C0_INEA);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक lance_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा lance_निजी *lp = netdev_priv(dev);
	अस्थिर काष्ठा lance_regs *ll = lp->ll;
	पूर्णांक ret;

	/* Stop the Lance */
	ll->rap = LE_CSR0;
	ll->rdp = LE_C0_STOP;

	/* Install the Interrupt handler */
	ret = request_irq(IRQ_AMIGA_PORTS, lance_पूर्णांकerrupt, IRQF_SHARED,
			  dev->name, dev);
	अगर (ret)
		वापस ret;

	load_csrs(lp);
	lance_init_ring(dev);

	netअगर_start_queue(dev);

	वापस init_restart_lance(lp);
पूर्ण

अटल पूर्णांक lance_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा lance_निजी *lp = netdev_priv(dev);
	अस्थिर काष्ठा lance_regs *ll = lp->ll;

	netअगर_stop_queue(dev);
	del_समयr_sync(&lp->multicast_समयr);

	/* Stop the card */
	ll->rap = LE_CSR0;
	ll->rdp = LE_C0_STOP;

	मुक्त_irq(IRQ_AMIGA_PORTS, dev);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक lance_reset(काष्ठा net_device *dev)
अणु
	काष्ठा lance_निजी *lp = netdev_priv(dev);
	अस्थिर काष्ठा lance_regs *ll = lp->ll;
	पूर्णांक status;

	/* Stop the lance */
	ll->rap = LE_CSR0;
	ll->rdp = LE_C0_STOP;

	load_csrs(lp);

	lance_init_ring(dev);
	netअगर_trans_update(dev); /* prevent tx समयout */
	netअगर_start_queue(dev);

	status = init_restart_lance(lp);
	netdev_dbg(dev, "Lance restart=%d\n", status);

	वापस status;
पूर्ण

अटल व्योम lance_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा lance_निजी *lp = netdev_priv(dev);
	अस्थिर काष्ठा lance_regs *ll = lp->ll;

	netdev_err(dev, "transmit timed out, status %04x, reset\n", ll->rdp);
	lance_reset(dev);
	netअगर_wake_queue(dev);
पूर्ण

अटल netdev_tx_t lance_start_xmit(काष्ठा sk_buff *skb,
				    काष्ठा net_device *dev)
अणु
	काष्ठा lance_निजी *lp = netdev_priv(dev);
	अस्थिर काष्ठा lance_regs *ll = lp->ll;
	अस्थिर काष्ठा lance_init_block *ib = lp->init_block;
	पूर्णांक entry, skblen;
	पूर्णांक status = NETDEV_TX_OK;
	अचिन्हित दीर्घ flags;

	अगर (skb_padto(skb, ETH_ZLEN))
		वापस NETDEV_TX_OK;
	skblen = max_t(अचिन्हित, skb->len, ETH_ZLEN);

	local_irq_save(flags);

	अगर (!lance_tx_buffs_avail(lp))
		जाओ out_मुक्त;

	/* dump the packet */
	prपूर्णांक_hex_dump_debug("skb->data: ", DUMP_PREFIX_NONE, 16, 1, skb->data,
			     64, true);

	entry = lp->tx_new & lp->tx_ring_mod_mask;
	ib->btx_ring[entry].length = (-skblen) | 0xf000;
	ib->btx_ring[entry].misc = 0;

	skb_copy_from_linear_data(skb, (व्योम *)&ib->tx_buf[entry][0], skblen);

	/* Now, give the packet to the lance */
	ib->btx_ring[entry].पंचांगd1_bits = (LE_T1_POK | LE_T1_OWN);
	lp->tx_new = (lp->tx_new+1) & lp->tx_ring_mod_mask;
	dev->stats.tx_bytes += skblen;

	अगर (lance_tx_buffs_avail(lp) <= 0)
		netअगर_stop_queue(dev);

	/* Kick the lance: transmit now */
	ll->rdp = LE_C0_INEA | LE_C0_TDMD;
 out_मुक्त:
	dev_kमुक्त_skb(skb);

	local_irq_restore(flags);

	वापस status;
पूर्ण

/* taken from the depca driver */
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

अटल व्योम lance_set_multicast(काष्ठा net_device *dev)
अणु
	काष्ठा lance_निजी *lp = netdev_priv(dev);
	अस्थिर काष्ठा lance_init_block *ib = lp->init_block;
	अस्थिर काष्ठा lance_regs *ll = lp->ll;

	अगर (!netअगर_running(dev))
		वापस;

	अगर (lp->tx_old != lp->tx_new) अणु
		mod_समयr(&lp->multicast_समयr, jअगरfies + 4);
		netअगर_wake_queue(dev);
		वापस;
	पूर्ण

	netअगर_stop_queue(dev);

	ll->rap = LE_CSR0;
	ll->rdp = LE_C0_STOP;
	lance_init_ring(dev);

	अगर (dev->flags & IFF_PROMISC) अणु
		ib->mode |= LE_MO_PROM;
	पूर्ण अन्यथा अणु
		ib->mode &= ~LE_MO_PROM;
		lance_load_multicast(dev);
	पूर्ण
	load_csrs(lp);
	init_restart_lance(lp);
	netअगर_wake_queue(dev);
पूर्ण

अटल व्योम lance_set_multicast_retry(काष्ठा समयr_list *t)
अणु
	काष्ठा lance_निजी *lp = from_समयr(lp, t, multicast_समयr);

	lance_set_multicast(lp->dev);
पूर्ण

अटल पूर्णांक a2065_init_one(काष्ठा zorro_dev *z,
			  स्थिर काष्ठा zorro_device_id *ent);
अटल व्योम a2065_हटाओ_one(काष्ठा zorro_dev *z);


अटल स्थिर काष्ठा zorro_device_id a2065_zorro_tbl[] = अणु
	अणु ZORRO_PROD_CBM_A2065_1 पूर्ण,
	अणु ZORRO_PROD_CBM_A2065_2 पूर्ण,
	अणु ZORRO_PROD_AMERISTAR_A2065 पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(zorro, a2065_zorro_tbl);

अटल काष्ठा zorro_driver a2065_driver = अणु
	.name		= "a2065",
	.id_table	= a2065_zorro_tbl,
	.probe		= a2065_init_one,
	.हटाओ		= a2065_हटाओ_one,
पूर्ण;

अटल स्थिर काष्ठा net_device_ops lance_netdev_ops = अणु
	.nकरो_खोलो		= lance_खोलो,
	.nकरो_stop		= lance_बंद,
	.nकरो_start_xmit		= lance_start_xmit,
	.nकरो_tx_समयout		= lance_tx_समयout,
	.nकरो_set_rx_mode	= lance_set_multicast,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address	= eth_mac_addr,
पूर्ण;

अटल पूर्णांक a2065_init_one(काष्ठा zorro_dev *z,
			  स्थिर काष्ठा zorro_device_id *ent)
अणु
	काष्ठा net_device *dev;
	काष्ठा lance_निजी *priv;
	अचिन्हित दीर्घ board = z->resource.start;
	अचिन्हित दीर्घ base_addr = board + A2065_LANCE;
	अचिन्हित दीर्घ mem_start = board + A2065_RAM;
	काष्ठा resource *r1, *r2;
	u32 serial;
	पूर्णांक err;

	r1 = request_mem_region(base_addr, माप(काष्ठा lance_regs),
				"Am7990");
	अगर (!r1)
		वापस -EBUSY;
	r2 = request_mem_region(mem_start, A2065_RAM_SIZE, "RAM");
	अगर (!r2) अणु
		release_mem_region(base_addr, माप(काष्ठा lance_regs));
		वापस -EBUSY;
	पूर्ण

	dev = alloc_etherdev(माप(काष्ठा lance_निजी));
	अगर (dev == शून्य) अणु
		release_mem_region(base_addr, माप(काष्ठा lance_regs));
		release_mem_region(mem_start, A2065_RAM_SIZE);
		वापस -ENOMEM;
	पूर्ण

	priv = netdev_priv(dev);

	r1->name = dev->name;
	r2->name = dev->name;

	serial = be32_to_cpu(z->rom.er_SerialNumber);
	dev->dev_addr[0] = 0x00;
	अगर (z->id != ZORRO_PROD_AMERISTAR_A2065) अणु	/* Commoकरोre */
		dev->dev_addr[1] = 0x80;
		dev->dev_addr[2] = 0x10;
	पूर्ण अन्यथा अणु					/* Ameristar */
		dev->dev_addr[1] = 0x00;
		dev->dev_addr[2] = 0x9f;
	पूर्ण
	dev->dev_addr[3] = (serial >> 16) & 0xff;
	dev->dev_addr[4] = (serial >> 8) & 0xff;
	dev->dev_addr[5] = serial & 0xff;
	dev->base_addr = (अचिन्हित दीर्घ)ZTWO_VADDR(base_addr);
	dev->mem_start = (अचिन्हित दीर्घ)ZTWO_VADDR(mem_start);
	dev->mem_end = dev->mem_start + A2065_RAM_SIZE;

	priv->ll = (अस्थिर काष्ठा lance_regs *)dev->base_addr;
	priv->init_block = (काष्ठा lance_init_block *)dev->mem_start;
	priv->lance_init_block = (काष्ठा lance_init_block *)A2065_RAM;
	priv->स्वतः_select = 0;
	priv->busmaster_regval = LE_C3_BSWP;

	priv->lance_log_rx_bufs = LANCE_LOG_RX_BUFFERS;
	priv->lance_log_tx_bufs = LANCE_LOG_TX_BUFFERS;
	priv->rx_ring_mod_mask = RX_RING_MOD_MASK;
	priv->tx_ring_mod_mask = TX_RING_MOD_MASK;
	priv->dev = dev;

	dev->netdev_ops = &lance_netdev_ops;
	dev->watchकरोg_समयo = 5*HZ;
	dev->dma = 0;

	समयr_setup(&priv->multicast_समयr, lance_set_multicast_retry, 0);

	err = रेजिस्टर_netdev(dev);
	अगर (err) अणु
		release_mem_region(base_addr, माप(काष्ठा lance_regs));
		release_mem_region(mem_start, A2065_RAM_SIZE);
		मुक्त_netdev(dev);
		वापस err;
	पूर्ण
	zorro_set_drvdata(z, dev);

	netdev_info(dev, "A2065 at 0x%08lx, Ethernet Address %pM\n",
		    board, dev->dev_addr);

	वापस 0;
पूर्ण


अटल व्योम a2065_हटाओ_one(काष्ठा zorro_dev *z)
अणु
	काष्ठा net_device *dev = zorro_get_drvdata(z);

	unरेजिस्टर_netdev(dev);
	release_mem_region(ZTWO_PADDR(dev->base_addr),
			   माप(काष्ठा lance_regs));
	release_mem_region(ZTWO_PADDR(dev->mem_start), A2065_RAM_SIZE);
	मुक्त_netdev(dev);
पूर्ण

अटल पूर्णांक __init a2065_init_module(व्योम)
अणु
	वापस zorro_रेजिस्टर_driver(&a2065_driver);
पूर्ण

अटल व्योम __निकास a2065_cleanup_module(व्योम)
अणु
	zorro_unरेजिस्टर_driver(&a2065_driver);
पूर्ण

module_init(a2065_init_module);
module_निकास(a2065_cleanup_module);

MODULE_LICENSE("GPL");
