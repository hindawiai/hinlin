<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * 6pack.c	This module implements the 6pack protocol क्रम kernel-based
 *		devices like TTY. It पूर्णांकerfaces between a raw TTY and the
 *		kernel's AX.25 protocol layers.
 *
 * Authors:	Andreas Kथघnsgen <ajk@comnets.uni-bremen.de>
 *              Ralf Baechle DL5RB <ralf@linux-mips.org>
 *
 * Quite a lot of stuff "stolen" by Joerg Reuter from slip.c, written by
 *
 *		Laurence Culhane, <loz@holmes.demon.co.uk>
 *		Fred N. van Kempen, <waltje@uwalt.nl.mugnet.org>
 */

#समावेश <linux/module.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/bitops.h>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/in.h>
#समावेश <linux/tty.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/netdevice.h>
#समावेश <linux/समयr.h>
#समावेश <linux/slab.h>
#समावेश <net/ax25.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/init.h>
#समावेश <linux/ip.h>
#समावेश <linux/tcp.h>
#समावेश <linux/semaphore.h>
#समावेश <linux/refcount.h>

#घोषणा SIXPACK_VERSION    "Revision: 0.3.0"

/* sixpack priority commands */
#घोषणा SIXP_Sखातापूर्ण		0x40	/* start and end of a 6pack frame */
#घोषणा SIXP_TX_URUN		0x48	/* transmit overrun */
#घोषणा SIXP_RX_ORUN		0x50	/* receive overrun */
#घोषणा SIXP_RX_BUF_OVL		0x58	/* receive buffer overflow */

#घोषणा SIXP_CHKSUM		0xFF	/* valid checksum of a 6pack frame */

/* masks to get certain bits out of the status bytes sent by the TNC */

#घोषणा SIXP_CMD_MASK		0xC0
#घोषणा SIXP_CHN_MASK		0x07
#घोषणा SIXP_PRIO_CMD_MASK	0x80
#घोषणा SIXP_STD_CMD_MASK	0x40
#घोषणा SIXP_PRIO_DATA_MASK	0x38
#घोषणा SIXP_TX_MASK		0x20
#घोषणा SIXP_RX_MASK		0x10
#घोषणा SIXP_RX_DCD_MASK	0x18
#घोषणा SIXP_LEDS_ON		0x78
#घोषणा SIXP_LEDS_OFF		0x60
#घोषणा SIXP_CON		0x08
#घोषणा SIXP_STA		0x10

#घोषणा SIXP_FOUND_TNC		0xe9
#घोषणा SIXP_CON_ON		0x68
#घोषणा SIXP_DCD_MASK		0x08
#घोषणा SIXP_DAMA_OFF		0

/* शेष level 2 parameters */
#घोषणा SIXP_TXDELAY			(HZ/4)	/* in 1 s */
#घोषणा SIXP_PERSIST			50	/* in 256ths */
#घोषणा SIXP_SLOTTIME			(HZ/10)	/* in 1 s */
#घोषणा SIXP_INIT_RESYNC_TIMEOUT	(3*HZ/2) /* in 1 s */
#घोषणा SIXP_RESYNC_TIMEOUT		5*HZ	/* in 1 s */

/* 6pack configuration. */
#घोषणा SIXP_NRUNIT			31      /* MAX number of 6pack channels */
#घोषणा SIXP_MTU			256	/* Default MTU */

क्रमागत sixpack_flags अणु
	SIXPF_ERROR,	/* Parity, etc. error	*/
पूर्ण;

काष्ठा sixpack अणु
	/* Various fields. */
	काष्ठा tty_काष्ठा	*tty;		/* ptr to TTY काष्ठाure	*/
	काष्ठा net_device	*dev;		/* easy क्रम पूर्णांकr handling  */

	/* These are poपूर्णांकers to the दो_स्मृति()ed frame buffers. */
	अचिन्हित अक्षर		*rbuff;		/* receiver buffer	*/
	पूर्णांक			rcount;         /* received अक्षरs counter  */
	अचिन्हित अक्षर		*xbuff;		/* transmitter buffer	*/
	अचिन्हित अक्षर		*xhead;         /* next byte to XMIT */
	पूर्णांक			xleft;          /* bytes left in XMIT queue  */

	अचिन्हित अक्षर		raw_buf[4];
	अचिन्हित अक्षर		cooked_buf[400];

	अचिन्हित पूर्णांक		rx_count;
	अचिन्हित पूर्णांक		rx_count_cooked;

	पूर्णांक			mtu;		/* Our mtu (to spot changes!) */
	पूर्णांक			buffsize;       /* Max buffers sizes */

	अचिन्हित दीर्घ		flags;		/* Flag values/ mode etc */
	अचिन्हित अक्षर		mode;		/* 6pack mode */

	/* 6pack stuff */
	अचिन्हित अक्षर		tx_delay;
	अचिन्हित अक्षर		persistence;
	अचिन्हित अक्षर		slotसमय;
	अचिन्हित अक्षर		duplex;
	अचिन्हित अक्षर		led_state;
	अचिन्हित अक्षर		status;
	अचिन्हित अक्षर		status1;
	अचिन्हित अक्षर		status2;
	अचिन्हित अक्षर		tx_enable;
	अचिन्हित अक्षर		tnc_state;

	काष्ठा समयr_list	tx_t;
	काष्ठा समयr_list	resync_t;
	refcount_t		refcnt;
	काष्ठा completion	dead;
	spinlock_t		lock;
पूर्ण;

#घोषणा AX25_6PACK_HEADER_LEN 0

अटल व्योम sixpack_decode(काष्ठा sixpack *, स्थिर अचिन्हित अक्षर[], पूर्णांक);
अटल पूर्णांक encode_sixpack(अचिन्हित अक्षर *, अचिन्हित अक्षर *, पूर्णांक, अचिन्हित अक्षर);

/*
 * Perक्रमm the persistence/slotसमय algorithm क्रम CSMA access. If the
 * persistence check was successful, ग_लिखो the data to the serial driver.
 * Note that in हाल of DAMA operation, the data is not sent here.
 */

अटल व्योम sp_xmit_on_air(काष्ठा समयr_list *t)
अणु
	काष्ठा sixpack *sp = from_समयr(sp, t, tx_t);
	पूर्णांक actual, when = sp->slotसमय;
	अटल अचिन्हित अक्षर अक्रमom;

	अक्रमom = अक्रमom * 17 + 41;

	अगर (((sp->status1 & SIXP_DCD_MASK) == 0) && (अक्रमom < sp->persistence)) अणु
		sp->led_state = 0x70;
		sp->tty->ops->ग_लिखो(sp->tty, &sp->led_state, 1);
		sp->tx_enable = 1;
		actual = sp->tty->ops->ग_लिखो(sp->tty, sp->xbuff, sp->status2);
		sp->xleft -= actual;
		sp->xhead += actual;
		sp->led_state = 0x60;
		sp->tty->ops->ग_लिखो(sp->tty, &sp->led_state, 1);
		sp->status2 = 0;
	पूर्ण अन्यथा
		mod_समयr(&sp->tx_t, jअगरfies + ((when + 1) * HZ) / 100);
पूर्ण

/* ----> 6pack समयr पूर्णांकerrupt handler and मित्रs. <---- */

/* Encapsulate one AX.25 frame and stuff पूर्णांकo a TTY queue. */
अटल व्योम sp_encaps(काष्ठा sixpack *sp, अचिन्हित अक्षर *icp, पूर्णांक len)
अणु
	अचिन्हित अक्षर *msg, *p = icp;
	पूर्णांक actual, count;

	अगर (len > sp->mtu) अणु	/* sp->mtu = AX25_MTU = max. PACLEN = 256 */
		msg = "oversized transmit packet!";
		जाओ out_drop;
	पूर्ण

	अगर (p[0] > 5) अणु
		msg = "invalid KISS command";
		जाओ out_drop;
	पूर्ण

	अगर ((p[0] != 0) && (len > 2)) अणु
		msg = "KISS control packet too long";
		जाओ out_drop;
	पूर्ण

	अगर ((p[0] == 0) && (len < 15)) अणु
		msg = "bad AX.25 packet to transmit";
		जाओ out_drop;
	पूर्ण

	count = encode_sixpack(p, sp->xbuff, len, sp->tx_delay);
	set_bit(TTY_DO_WRITE_WAKEUP, &sp->tty->flags);

	चयन (p[0]) अणु
	हाल 1:	sp->tx_delay = p[1];
		वापस;
	हाल 2:	sp->persistence = p[1];
		वापस;
	हाल 3:	sp->slotसमय = p[1];
		वापस;
	हाल 4:	/* ignored */
		वापस;
	हाल 5:	sp->duplex = p[1];
		वापस;
	पूर्ण

	अगर (p[0] != 0)
		वापस;

	/*
	 * In हाल of fullduplex or DAMA operation, we करोn't take care about the
	 * state of the DCD or of any समयrs, as the determination of the
	 * correct समय to send is the job of the AX.25 layer. We send
	 * immediately after data has arrived.
	 */
	अगर (sp->duplex == 1) अणु
		sp->led_state = 0x70;
		sp->tty->ops->ग_लिखो(sp->tty, &sp->led_state, 1);
		sp->tx_enable = 1;
		actual = sp->tty->ops->ग_लिखो(sp->tty, sp->xbuff, count);
		sp->xleft = count - actual;
		sp->xhead = sp->xbuff + actual;
		sp->led_state = 0x60;
		sp->tty->ops->ग_लिखो(sp->tty, &sp->led_state, 1);
	पूर्ण अन्यथा अणु
		sp->xleft = count;
		sp->xhead = sp->xbuff;
		sp->status2 = count;
		sp_xmit_on_air(&sp->tx_t);
	पूर्ण

	वापस;

out_drop:
	sp->dev->stats.tx_dropped++;
	netअगर_start_queue(sp->dev);
	अगर (net_ratelimit())
		prपूर्णांकk(KERN_DEBUG "%s: %s - dropped.\n", sp->dev->name, msg);
पूर्ण

/* Encapsulate an IP datagram and kick it पूर्णांकo a TTY queue. */

अटल netdev_tx_t sp_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा sixpack *sp = netdev_priv(dev);

	अगर (skb->protocol == htons(ETH_P_IP))
		वापस ax25_ip_xmit(skb);

	spin_lock_bh(&sp->lock);
	/* We were not busy, so we are now... :-) */
	netअगर_stop_queue(dev);
	dev->stats.tx_bytes += skb->len;
	sp_encaps(sp, skb->data, skb->len);
	spin_unlock_bh(&sp->lock);

	dev_kमुक्त_skb(skb);

	वापस NETDEV_TX_OK;
पूर्ण

अटल पूर्णांक sp_खोलो_dev(काष्ठा net_device *dev)
अणु
	काष्ठा sixpack *sp = netdev_priv(dev);

	अगर (sp->tty == शून्य)
		वापस -ENODEV;
	वापस 0;
पूर्ण

/* Close the low-level part of the 6pack channel. */
अटल पूर्णांक sp_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा sixpack *sp = netdev_priv(dev);

	spin_lock_bh(&sp->lock);
	अगर (sp->tty) अणु
		/* TTY discipline is running. */
		clear_bit(TTY_DO_WRITE_WAKEUP, &sp->tty->flags);
	पूर्ण
	netअगर_stop_queue(dev);
	spin_unlock_bh(&sp->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक sp_set_mac_address(काष्ठा net_device *dev, व्योम *addr)
अणु
	काष्ठा sockaddr_ax25 *sa = addr;

	netअगर_tx_lock_bh(dev);
	netअगर_addr_lock(dev);
	स_नकल(dev->dev_addr, &sa->sax25_call, AX25_ADDR_LEN);
	netअगर_addr_unlock(dev);
	netअगर_tx_unlock_bh(dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops sp_netdev_ops = अणु
	.nकरो_खोलो		= sp_खोलो_dev,
	.nकरो_stop		= sp_बंद,
	.nकरो_start_xmit		= sp_xmit,
	.nकरो_set_mac_address    = sp_set_mac_address,
पूर्ण;

अटल व्योम sp_setup(काष्ठा net_device *dev)
अणु
	/* Finish setting up the DEVICE info. */
	dev->netdev_ops		= &sp_netdev_ops;
	dev->needs_मुक्त_netdev	= true;
	dev->mtu		= SIXP_MTU;
	dev->hard_header_len	= AX25_MAX_HEADER_LEN;
	dev->header_ops 	= &ax25_header_ops;

	dev->addr_len		= AX25_ADDR_LEN;
	dev->type		= ARPHRD_AX25;
	dev->tx_queue_len	= 10;

	/* Only activated in AX.25 mode */
	स_नकल(dev->broadcast, &ax25_bcast, AX25_ADDR_LEN);
	स_नकल(dev->dev_addr, &ax25_defaddr, AX25_ADDR_LEN);

	dev->flags		= 0;
पूर्ण

/* Send one completely decapsulated IP datagram to the IP layer. */

/*
 * This is the routine that sends the received data to the kernel AX.25.
 * 'cmd' is the KISS command. For AX.25 data, it is zero.
 */

अटल व्योम sp_bump(काष्ठा sixpack *sp, अक्षर cmd)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक count;
	अचिन्हित अक्षर *ptr;

	count = sp->rcount + 1;

	sp->dev->stats.rx_bytes += count;

	अगर ((skb = dev_alloc_skb(count + 1)) == शून्य)
		जाओ out_mem;

	ptr = skb_put(skb, count + 1);
	*ptr++ = cmd;	/* KISS command */

	स_नकल(ptr, sp->cooked_buf + 1, count);
	skb->protocol = ax25_type_trans(skb, sp->dev);
	netअगर_rx(skb);
	sp->dev->stats.rx_packets++;

	वापस;

out_mem:
	sp->dev->stats.rx_dropped++;
पूर्ण


/* ----------------------------------------------------------------------- */

/*
 * We have a potential race on dereferencing tty->disc_data, because the tty
 * layer provides no locking at all - thus one cpu could be running
 * sixpack_receive_buf जबतक another calls sixpack_बंद, which zeroes
 * tty->disc_data and मुक्तs the memory that sixpack_receive_buf is using.  The
 * best way to fix this is to use a rwlock in the tty काष्ठा, but क्रम now we
 * use a single global rwlock क्रम all ttys in ppp line discipline.
 */
अटल DEFINE_RWLOCK(disc_data_lock);
                                                                                
अटल काष्ठा sixpack *sp_get(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा sixpack *sp;

	पढ़ो_lock(&disc_data_lock);
	sp = tty->disc_data;
	अगर (sp)
		refcount_inc(&sp->refcnt);
	पढ़ो_unlock(&disc_data_lock);

	वापस sp;
पूर्ण

अटल व्योम sp_put(काष्ठा sixpack *sp)
अणु
	अगर (refcount_dec_and_test(&sp->refcnt))
		complete(&sp->dead);
पूर्ण

/*
 * Called by the TTY driver when there's room क्रम more data.  If we have
 * more packets to send, we send them here.
 */
अटल व्योम sixpack_ग_लिखो_wakeup(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा sixpack *sp = sp_get(tty);
	पूर्णांक actual;

	अगर (!sp)
		वापस;
	अगर (sp->xleft <= 0)  अणु
		/* Now serial buffer is almost मुक्त & we can start
		 * transmission of another packet */
		sp->dev->stats.tx_packets++;
		clear_bit(TTY_DO_WRITE_WAKEUP, &tty->flags);
		sp->tx_enable = 0;
		netअगर_wake_queue(sp->dev);
		जाओ out;
	पूर्ण

	अगर (sp->tx_enable) अणु
		actual = tty->ops->ग_लिखो(tty, sp->xhead, sp->xleft);
		sp->xleft -= actual;
		sp->xhead += actual;
	पूर्ण

out:
	sp_put(sp);
पूर्ण

/* ----------------------------------------------------------------------- */

/*
 * Handle the 'receiver data ready' पूर्णांकerrupt.
 * This function is called by the tty module in the kernel when
 * a block of 6pack data has been received, which can now be decapsulated
 * and sent on to some IP layer क्रम further processing.
 */
अटल व्योम sixpack_receive_buf(काष्ठा tty_काष्ठा *tty,
	स्थिर अचिन्हित अक्षर *cp, अक्षर *fp, पूर्णांक count)
अणु
	काष्ठा sixpack *sp;
	पूर्णांक count1;

	अगर (!count)
		वापस;

	sp = sp_get(tty);
	अगर (!sp)
		वापस;

	/* Read the अक्षरacters out of the buffer */
	count1 = count;
	जबतक (count) अणु
		count--;
		अगर (fp && *fp++) अणु
			अगर (!test_and_set_bit(SIXPF_ERROR, &sp->flags))
				sp->dev->stats.rx_errors++;
			जारी;
		पूर्ण
	पूर्ण
	sixpack_decode(sp, cp, count1);

	sp_put(sp);
	tty_unthrottle(tty);
पूर्ण

/*
 * Try to resync the TNC. Called by the resync समयr defined in
 * decode_prio_command
 */

#घोषणा TNC_UNINITIALIZED	0
#घोषणा TNC_UNSYNC_STARTUP	1
#घोषणा TNC_UNSYNCED		2
#घोषणा TNC_IN_SYNC		3

अटल व्योम __tnc_set_sync_state(काष्ठा sixpack *sp, पूर्णांक new_tnc_state)
अणु
	अक्षर *msg;

	चयन (new_tnc_state) अणु
	शेष:			/* gcc oh piece-o-crap ... */
	हाल TNC_UNSYNC_STARTUP:
		msg = "Synchronizing with TNC";
		अवरोध;
	हाल TNC_UNSYNCED:
		msg = "Lost synchronization with TNC\n";
		अवरोध;
	हाल TNC_IN_SYNC:
		msg = "Found TNC";
		अवरोध;
	पूर्ण

	sp->tnc_state = new_tnc_state;
	prपूर्णांकk(KERN_INFO "%s: %s\n", sp->dev->name, msg);
पूर्ण

अटल अंतरभूत व्योम tnc_set_sync_state(काष्ठा sixpack *sp, पूर्णांक new_tnc_state)
अणु
	पूर्णांक old_tnc_state = sp->tnc_state;

	अगर (old_tnc_state != new_tnc_state)
		__tnc_set_sync_state(sp, new_tnc_state);
पूर्ण

अटल व्योम resync_tnc(काष्ठा समयr_list *t)
अणु
	काष्ठा sixpack *sp = from_समयr(sp, t, resync_t);
	अटल अक्षर resync_cmd = 0xe8;

	/* clear any data that might have been received */

	sp->rx_count = 0;
	sp->rx_count_cooked = 0;

	/* reset state machine */

	sp->status = 1;
	sp->status1 = 1;
	sp->status2 = 0;

	/* resync the TNC */

	sp->led_state = 0x60;
	sp->tty->ops->ग_लिखो(sp->tty, &sp->led_state, 1);
	sp->tty->ops->ग_लिखो(sp->tty, &resync_cmd, 1);


	/* Start resync समयr again -- the TNC might be still असलent */
	mod_समयr(&sp->resync_t, jअगरfies + SIXP_RESYNC_TIMEOUT);
पूर्ण

अटल अंतरभूत पूर्णांक tnc_init(काष्ठा sixpack *sp)
अणु
	अचिन्हित अक्षर inbyte = 0xe8;

	tnc_set_sync_state(sp, TNC_UNSYNC_STARTUP);

	sp->tty->ops->ग_लिखो(sp->tty, &inbyte, 1);

	mod_समयr(&sp->resync_t, jअगरfies + SIXP_RESYNC_TIMEOUT);

	वापस 0;
पूर्ण

/*
 * Open the high-level part of the 6pack channel.
 * This function is called by the TTY module when the
 * 6pack line discipline is called क्रम.  Because we are
 * sure the tty line exists, we only have to link it to
 * a मुक्त 6pcack channel...
 */
अटल पूर्णांक sixpack_खोलो(काष्ठा tty_काष्ठा *tty)
अणु
	अक्षर *rbuff = शून्य, *xbuff = शून्य;
	काष्ठा net_device *dev;
	काष्ठा sixpack *sp;
	अचिन्हित दीर्घ len;
	पूर्णांक err = 0;

	अगर (!capable(CAP_NET_ADMIN))
		वापस -EPERM;
	अगर (tty->ops->ग_लिखो == शून्य)
		वापस -EOPNOTSUPP;

	dev = alloc_netdev(माप(काष्ठा sixpack), "sp%d", NET_NAME_UNKNOWN,
			   sp_setup);
	अगर (!dev) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	sp = netdev_priv(dev);
	sp->dev = dev;

	spin_lock_init(&sp->lock);
	refcount_set(&sp->refcnt, 1);
	init_completion(&sp->dead);

	/* !!! length of the buffers. MTU is IP MTU, not PACLEN!  */

	len = dev->mtu * 2;

	rbuff = kदो_स्मृति(len + 4, GFP_KERNEL);
	xbuff = kदो_स्मृति(len + 4, GFP_KERNEL);

	अगर (rbuff == शून्य || xbuff == शून्य) अणु
		err = -ENOBUFS;
		जाओ out_मुक्त;
	पूर्ण

	spin_lock_bh(&sp->lock);

	sp->tty = tty;

	sp->rbuff	= rbuff;
	sp->xbuff	= xbuff;

	sp->mtu		= AX25_MTU + 73;
	sp->buffsize	= len;
	sp->rcount	= 0;
	sp->rx_count	= 0;
	sp->rx_count_cooked = 0;
	sp->xleft	= 0;

	sp->flags	= 0;		/* Clear ESCAPE & ERROR flags */

	sp->duplex	= 0;
	sp->tx_delay    = SIXP_TXDELAY;
	sp->persistence = SIXP_PERSIST;
	sp->slotसमय    = SIXP_SLOTTIME;
	sp->led_state   = 0x60;
	sp->status      = 1;
	sp->status1     = 1;
	sp->status2     = 0;
	sp->tx_enable   = 0;

	netअगर_start_queue(dev);

	समयr_setup(&sp->tx_t, sp_xmit_on_air, 0);

	समयr_setup(&sp->resync_t, resync_tnc, 0);

	spin_unlock_bh(&sp->lock);

	/* Done.  We have linked the TTY line to a channel. */
	tty->disc_data = sp;
	tty->receive_room = 65536;

	/* Now we're पढ़ोy to रेजिस्टर. */
	err = रेजिस्टर_netdev(dev);
	अगर (err)
		जाओ out_मुक्त;

	tnc_init(sp);

	वापस 0;

out_मुक्त:
	kमुक्त(xbuff);
	kमुक्त(rbuff);

	मुक्त_netdev(dev);

out:
	वापस err;
पूर्ण


/*
 * Close करोwn a 6pack channel.
 * This means flushing out any pending queues, and then restoring the
 * TTY line discipline to what it was beक्रमe it got hooked to 6pack
 * (which usually is TTY again).
 */
अटल व्योम sixpack_बंद(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा sixpack *sp;

	ग_लिखो_lock_irq(&disc_data_lock);
	sp = tty->disc_data;
	tty->disc_data = शून्य;
	ग_लिखो_unlock_irq(&disc_data_lock);
	अगर (!sp)
		वापस;

	/*
	 * We have now ensured that nobody can start using ap from now on, but
	 * we have to रुको क्रम all existing users to finish.
	 */
	अगर (!refcount_dec_and_test(&sp->refcnt))
		रुको_क्रम_completion(&sp->dead);

	/* We must stop the queue to aव्योम potentially scribbling
	 * on the मुक्त buffers. The sp->dead completion is not sufficient
	 * to protect us from sp->xbuff access.
	 */
	netअगर_stop_queue(sp->dev);

	del_समयr_sync(&sp->tx_t);
	del_समयr_sync(&sp->resync_t);

	/* Free all 6pack frame buffers. */
	kमुक्त(sp->rbuff);
	kमुक्त(sp->xbuff);

	unरेजिस्टर_netdev(sp->dev);
पूर्ण

/* Perक्रमm I/O control on an active 6pack channel. */
अटल पूर्णांक sixpack_ioctl(काष्ठा tty_काष्ठा *tty, काष्ठा file *file,
	अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा sixpack *sp = sp_get(tty);
	काष्ठा net_device *dev;
	अचिन्हित पूर्णांक पंचांगp, err;

	अगर (!sp)
		वापस -ENXIO;
	dev = sp->dev;

	चयन(cmd) अणु
	हाल SIOCGIFNAME:
		err = copy_to_user((व्योम __user *) arg, dev->name,
		                   म_माप(dev->name) + 1) ? -EFAULT : 0;
		अवरोध;

	हाल SIOCGIFENCAP:
		err = put_user(0, (पूर्णांक __user *) arg);
		अवरोध;

	हाल SIOCSIFENCAP:
		अगर (get_user(पंचांगp, (पूर्णांक __user *) arg)) अणु
			err = -EFAULT;
			अवरोध;
		पूर्ण

		sp->mode = पंचांगp;
		dev->addr_len        = AX25_ADDR_LEN;
		dev->hard_header_len = AX25_KISS_HEADER_LEN +
		                       AX25_MAX_HEADER_LEN + 3;
		dev->type            = ARPHRD_AX25;

		err = 0;
		अवरोध;

	 हाल SIOCSIFHWADDR: अणु
		अक्षर addr[AX25_ADDR_LEN];

		अगर (copy_from_user(&addr,
		                   (व्योम __user *) arg, AX25_ADDR_LEN)) अणु
				err = -EFAULT;
				अवरोध;
			पूर्ण

			netअगर_tx_lock_bh(dev);
			स_नकल(dev->dev_addr, &addr, AX25_ADDR_LEN);
			netअगर_tx_unlock_bh(dev);

			err = 0;
			अवरोध;
		पूर्ण

	शेष:
		err = tty_mode_ioctl(tty, file, cmd, arg);
	पूर्ण

	sp_put(sp);

	वापस err;
पूर्ण

अटल काष्ठा tty_ldisc_ops sp_ldisc = अणु
	.owner		= THIS_MODULE,
	.name		= "6pack",
	.खोलो		= sixpack_खोलो,
	.बंद		= sixpack_बंद,
	.ioctl		= sixpack_ioctl,
	.receive_buf	= sixpack_receive_buf,
	.ग_लिखो_wakeup	= sixpack_ग_लिखो_wakeup,
पूर्ण;

/* Initialize 6pack control device -- रेजिस्टर 6pack line discipline */

अटल स्थिर अक्षर msg_banner[]  __initस्थिर = KERN_INFO \
	"AX.25: 6pack driver, " SIXPACK_VERSION "\n";
अटल स्थिर अक्षर msg_regfail[] __initस्थिर = KERN_ERR  \
	"6pack: can't register line discipline (err = %d)\n";

अटल पूर्णांक __init sixpack_init_driver(व्योम)
अणु
	पूर्णांक status;

	prपूर्णांकk(msg_banner);

	/* Register the provided line protocol discipline */
	अगर ((status = tty_रेजिस्टर_ldisc(N_6PACK, &sp_ldisc)) != 0)
		prपूर्णांकk(msg_regfail, status);

	वापस status;
पूर्ण

अटल स्थिर अक्षर msg_unregfail[] = KERN_ERR \
	"6pack: can't unregister line discipline (err = %d)\n";

अटल व्योम __निकास sixpack_निकास_driver(व्योम)
अणु
	पूर्णांक ret;

	अगर ((ret = tty_unरेजिस्टर_ldisc(N_6PACK)))
		prपूर्णांकk(msg_unregfail, ret);
पूर्ण

/* encode an AX.25 packet पूर्णांकo 6pack */

अटल पूर्णांक encode_sixpack(अचिन्हित अक्षर *tx_buf, अचिन्हित अक्षर *tx_buf_raw,
	पूर्णांक length, अचिन्हित अक्षर tx_delay)
अणु
	पूर्णांक count = 0;
	अचिन्हित अक्षर checksum = 0, buf[400];
	पूर्णांक raw_count = 0;

	tx_buf_raw[raw_count++] = SIXP_PRIO_CMD_MASK | SIXP_TX_MASK;
	tx_buf_raw[raw_count++] = SIXP_Sखातापूर्ण;

	buf[0] = tx_delay;
	क्रम (count = 1; count < length; count++)
		buf[count] = tx_buf[count];

	क्रम (count = 0; count < length; count++)
		checksum += buf[count];
	buf[length] = (अचिन्हित अक्षर) 0xff - checksum;

	क्रम (count = 0; count <= length; count++) अणु
		अगर ((count % 3) == 0) अणु
			tx_buf_raw[raw_count++] = (buf[count] & 0x3f);
			tx_buf_raw[raw_count] = ((buf[count] >> 2) & 0x30);
		पूर्ण अन्यथा अगर ((count % 3) == 1) अणु
			tx_buf_raw[raw_count++] |= (buf[count] & 0x0f);
			tx_buf_raw[raw_count] =	((buf[count] >> 2) & 0x3c);
		पूर्ण अन्यथा अणु
			tx_buf_raw[raw_count++] |= (buf[count] & 0x03);
			tx_buf_raw[raw_count++] = (buf[count] >> 2);
		पूर्ण
	पूर्ण
	अगर ((length % 3) != 2)
		raw_count++;
	tx_buf_raw[raw_count++] = SIXP_Sखातापूर्ण;
	वापस raw_count;
पूर्ण

/* decode 4 sixpack-encoded bytes पूर्णांकo 3 data bytes */

अटल व्योम decode_data(काष्ठा sixpack *sp, अचिन्हित अक्षर inbyte)
अणु
	अचिन्हित अक्षर *buf;

	अगर (sp->rx_count != 3) अणु
		sp->raw_buf[sp->rx_count++] = inbyte;

		वापस;
	पूर्ण

	buf = sp->raw_buf;
	sp->cooked_buf[sp->rx_count_cooked++] =
		buf[0] | ((buf[1] << 2) & 0xc0);
	sp->cooked_buf[sp->rx_count_cooked++] =
		(buf[1] & 0x0f) | ((buf[2] << 2) & 0xf0);
	sp->cooked_buf[sp->rx_count_cooked++] =
		(buf[2] & 0x03) | (inbyte << 2);
	sp->rx_count = 0;
पूर्ण

/* identअगरy and execute a 6pack priority command byte */

अटल व्योम decode_prio_command(काष्ठा sixpack *sp, अचिन्हित अक्षर cmd)
अणु
	पूर्णांक actual;

	अगर ((cmd & SIXP_PRIO_DATA_MASK) != 0) अणु     /* idle ? */

	/* RX and DCD flags can only be set in the same prio command,
	   अगर the DCD flag has been set without the RX flag in the previous
	   prio command. If DCD has not been set beक्रमe, something in the
	   transmission has gone wrong. In this हाल, RX and DCD are
	   cleared in order to prevent the decode_data routine from
	   पढ़ोing further data that might be corrupt. */

		अगर (((sp->status & SIXP_DCD_MASK) == 0) &&
			((cmd & SIXP_RX_DCD_MASK) == SIXP_RX_DCD_MASK)) अणु
				अगर (sp->status != 1)
					prपूर्णांकk(KERN_DEBUG "6pack: protocol violation\n");
				अन्यथा
					sp->status = 0;
				cmd &= ~SIXP_RX_DCD_MASK;
		पूर्ण
		sp->status = cmd & SIXP_PRIO_DATA_MASK;
	पूर्ण अन्यथा अणु /* output watchकरोg अक्षर अगर idle */
		अगर ((sp->status2 != 0) && (sp->duplex == 1)) अणु
			sp->led_state = 0x70;
			sp->tty->ops->ग_लिखो(sp->tty, &sp->led_state, 1);
			sp->tx_enable = 1;
			actual = sp->tty->ops->ग_लिखो(sp->tty, sp->xbuff, sp->status2);
			sp->xleft -= actual;
			sp->xhead += actual;
			sp->led_state = 0x60;
			sp->status2 = 0;

		पूर्ण
	पूर्ण

	/* needed to trigger the TNC watchकरोg */
	sp->tty->ops->ग_लिखो(sp->tty, &sp->led_state, 1);

        /* अगर the state byte has been received, the TNC is present,
           so the resync समयr can be reset. */

	अगर (sp->tnc_state == TNC_IN_SYNC)
		mod_समयr(&sp->resync_t, jअगरfies + SIXP_INIT_RESYNC_TIMEOUT);

	sp->status1 = cmd & SIXP_PRIO_DATA_MASK;
पूर्ण

/* identअगरy and execute a standard 6pack command byte */

अटल व्योम decode_std_command(काष्ठा sixpack *sp, अचिन्हित अक्षर cmd)
अणु
	अचिन्हित अक्षर checksum = 0, rest = 0;
	लघु i;

	चयन (cmd & SIXP_CMD_MASK) अणु     /* normal command */
	हाल SIXP_Sखातापूर्ण:
		अगर ((sp->rx_count == 0) && (sp->rx_count_cooked == 0)) अणु
			अगर ((sp->status & SIXP_RX_DCD_MASK) ==
				SIXP_RX_DCD_MASK) अणु
				sp->led_state = 0x68;
				sp->tty->ops->ग_लिखो(sp->tty, &sp->led_state, 1);
			पूर्ण
		पूर्ण अन्यथा अणु
			sp->led_state = 0x60;
			/* fill trailing bytes with zeroes */
			sp->tty->ops->ग_लिखो(sp->tty, &sp->led_state, 1);
			rest = sp->rx_count;
			अगर (rest != 0)
				 क्रम (i = rest; i <= 3; i++)
					decode_data(sp, 0);
			अगर (rest == 2)
				sp->rx_count_cooked -= 2;
			अन्यथा अगर (rest == 3)
				sp->rx_count_cooked -= 1;
			क्रम (i = 0; i < sp->rx_count_cooked; i++)
				checksum += sp->cooked_buf[i];
			अगर (checksum != SIXP_CHKSUM) अणु
				prपूर्णांकk(KERN_DEBUG "6pack: bad checksum %2.2x\n", checksum);
			पूर्ण अन्यथा अणु
				sp->rcount = sp->rx_count_cooked-2;
				sp_bump(sp, 0);
			पूर्ण
			sp->rx_count_cooked = 0;
		पूर्ण
		अवरोध;
	हाल SIXP_TX_URUN: prपूर्णांकk(KERN_DEBUG "6pack: TX underrun\n");
		अवरोध;
	हाल SIXP_RX_ORUN: prपूर्णांकk(KERN_DEBUG "6pack: RX overrun\n");
		अवरोध;
	हाल SIXP_RX_BUF_OVL:
		prपूर्णांकk(KERN_DEBUG "6pack: RX buffer overflow\n");
	पूर्ण
पूर्ण

/* decode a 6pack packet */

अटल व्योम
sixpack_decode(काष्ठा sixpack *sp, स्थिर अचिन्हित अक्षर *pre_rbuff, पूर्णांक count)
अणु
	अचिन्हित अक्षर inbyte;
	पूर्णांक count1;

	क्रम (count1 = 0; count1 < count; count1++) अणु
		inbyte = pre_rbuff[count1];
		अगर (inbyte == SIXP_FOUND_TNC) अणु
			tnc_set_sync_state(sp, TNC_IN_SYNC);
			del_समयr(&sp->resync_t);
		पूर्ण
		अगर ((inbyte & SIXP_PRIO_CMD_MASK) != 0)
			decode_prio_command(sp, inbyte);
		अन्यथा अगर ((inbyte & SIXP_STD_CMD_MASK) != 0)
			decode_std_command(sp, inbyte);
		अन्यथा अगर ((sp->status & SIXP_RX_DCD_MASK) == SIXP_RX_DCD_MASK)
			decode_data(sp, inbyte);
	पूर्ण
पूर्ण

MODULE_AUTHOR("Ralf Baechle DO1GRB <ralf@linux-mips.org>");
MODULE_DESCRIPTION("6pack driver for AX.25");
MODULE_LICENSE("GPL");
MODULE_ALIAS_LDISC(N_6PACK);

module_init(sixpack_init_driver);
module_निकास(sixpack_निकास_driver);
