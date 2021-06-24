<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * slip.c	This module implements the SLIP protocol क्रम kernel-based
 *		devices like TTY.  It पूर्णांकerfaces between a raw TTY, and the
 *		kernel's INET protocol layers.
 *
 * Version:	@(#)slip.c	0.8.3	12/24/94
 *
 * Authors:	Laurence Culhane, <loz@holmes.demon.co.uk>
 *		Fred N. van Kempen, <waltje@uwalt.nl.mugnet.org>
 *
 * Fixes:
 *		Alan Cox	: 	Sanity checks and aव्योम tx overruns.
 *					Has a new sl->mtu field.
 *		Alan Cox	: 	Found cause of overrun. अगरconfig sl0
 *					mtu upwards. Driver now spots this
 *					and grows/shrinks its buffers(hack!).
 *					Memory leak अगर you run out of memory
 *					setting up a slip driver fixed.
 *		Matt Dillon	:	Prपूर्णांकable slip (borrowed from NET2E)
 *	Pauline Middelink	:	Slip driver fixes.
 *		Alan Cox	:	Honours the old SL_COMPRESSED flag
 *		Alan Cox	:	KISS AX.25 and AXUI IP support
 *		Michael Riepe	:	Automatic CSLIP recognition added
 *		Charles Hedrick :	CSLIP header length problem fix.
 *		Alan Cox	:	Corrected non-IP हालs of the above.
 *		Alan Cox	:	Now uses hardware type as per FvK.
 *		Alan Cox	:	Default to 192.168.0.0 (RFC 1597)
 *		A.N.Kuznetsov	:	dev_tपूर्णांक() recursion fix.
 *	Dmitry Gorodchanin	:	SLIP memory leaks
 *      Dmitry Gorodchanin      :       Code cleanup. Reduce tty driver
 *                                      buffering from 4096 to 256 bytes.
 *                                      Improving SLIP response समय.
 *                                      CONFIG_SLIP_MODE_SLIP6.
 *                                      अगरconfig sl? up & करोwn now works
 *					correctly.
 *					Modularization.
 *              Alan Cox        :       Oops - fix AX.25 buffer lengths
 *      Dmitry Gorodchanin      :       Even more cleanups. Preserve CSLIP
 *                                      statistics. Include CSLIP code only
 *                                      अगर it really needed.
 *		Alan Cox	:	Free slhc buffers in the right place.
 *		Alan Cox	:	Allow क्रम digipeated IP over AX.25
 *		Matti Aarnio	:	Dynamic SLIP devices, with ideas taken
 *					from Jim Freeman's <jमुक्त@caldera.com>
 *					dynamic PPP devices.  We करो NOT kमुक्त()
 *					device entries, just reg./unreg. them
 *					as they are needed.  We kमुक्त() them
 *					at module cleanup.
 *					With MODULE-loading ``insmod'', user
 *					can issue parameter:  slip_maxdev=1024
 *					(Or how much he/she wants.. Default
 *					is 256)
 *	Stanislav Voronyi	:	Slip line checking, with ideas taken
 *					from multislip BSDI driver which was
 *					written by Igor Chechik, RELCOM Corp.
 *					Only algorithms have been ported to
 *					Linux SLIP driver.
 *	Vitaly E. Lavrov	:	Sane behaviour on tty hangup.
 *	Alexey Kuznetsov	:	Cleanup पूर्णांकerfaces to tty & netdevice
 *					modules.
 */

#घोषणा SL_CHECK_TRANSMIT
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>

#समावेश <linux/uaccess.h>
#समावेश <linux/bitops.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/in.h>
#समावेश <linux/tty.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/अगर_slip.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>
#समावेश "slip.h"
#अगर_घोषित CONFIG_INET
#समावेश <linux/ip.h>
#समावेश <linux/tcp.h>
#समावेश <net/slhc_vj.h>
#पूर्ण_अगर

#घोषणा SLIP_VERSION	"0.8.4-NET3.019-NEWTTY"

अटल काष्ठा net_device **slip_devs;

अटल पूर्णांक slip_maxdev = SL_NRUNIT;
module_param(slip_maxdev, पूर्णांक, 0);
MODULE_PARM_DESC(slip_maxdev, "Maximum number of slip devices");

अटल पूर्णांक slip_esc(अचिन्हित अक्षर *p, अचिन्हित अक्षर *d, पूर्णांक len);
अटल व्योम slip_unesc(काष्ठा slip *sl, अचिन्हित अक्षर c);
#अगर_घोषित CONFIG_SLIP_MODE_SLIP6
अटल पूर्णांक slip_esc6(अचिन्हित अक्षर *p, अचिन्हित अक्षर *d, पूर्णांक len);
अटल व्योम slip_unesc6(काष्ठा slip *sl, अचिन्हित अक्षर c);
#पूर्ण_अगर
#अगर_घोषित CONFIG_SLIP_SMART
अटल व्योम sl_keepalive(काष्ठा समयr_list *t);
अटल व्योम sl_outfill(काष्ठा समयr_list *t);
अटल पूर्णांक sl_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd);
#पूर्ण_अगर

/********************************
*  Buffer administration routines:
*	sl_alloc_bufs()
*	sl_मुक्त_bufs()
*	sl_पुनः_स्मृति_bufs()
*
* NOTE: sl_पुनः_स्मृति_bufs != sl_मुक्त_bufs + sl_alloc_bufs, because
*	sl_पुनः_स्मृति_bufs provides strong atomicity and पुनः_स्मृतिation
*	on actively running device.
*********************************/

/*
   Allocate channel buffers.
 */

अटल पूर्णांक sl_alloc_bufs(काष्ठा slip *sl, पूर्णांक mtu)
अणु
	पूर्णांक err = -ENOBUFS;
	अचिन्हित दीर्घ len;
	अक्षर *rbuff = शून्य;
	अक्षर *xbuff = शून्य;
#अगर_घोषित SL_INCLUDE_CSLIP
	अक्षर *cbuff = शून्य;
	काष्ठा slcompress *slcomp = शून्य;
#पूर्ण_अगर

	/*
	 * Allocate the SLIP frame buffers:
	 *
	 * rbuff	Receive buffer.
	 * xbuff	Transmit buffer.
	 * cbuff        Temporary compression buffer.
	 */
	len = mtu * 2;

	/*
	 * allow क्रम arrival of larger UDP packets, even अगर we say not to
	 * also fixes a bug in which SunOS sends 512-byte packets even with
	 * an MSS of 128
	 */
	अगर (len < 576 * 2)
		len = 576 * 2;
	rbuff = kदो_स्मृति(len + 4, GFP_KERNEL);
	अगर (rbuff == शून्य)
		जाओ err_निकास;
	xbuff = kदो_स्मृति(len + 4, GFP_KERNEL);
	अगर (xbuff == शून्य)
		जाओ err_निकास;
#अगर_घोषित SL_INCLUDE_CSLIP
	cbuff = kदो_स्मृति(len + 4, GFP_KERNEL);
	अगर (cbuff == शून्य)
		जाओ err_निकास;
	slcomp = slhc_init(16, 16);
	अगर (IS_ERR(slcomp))
		जाओ err_निकास;
#पूर्ण_अगर
	spin_lock_bh(&sl->lock);
	अगर (sl->tty == शून्य) अणु
		spin_unlock_bh(&sl->lock);
		err = -ENODEV;
		जाओ err_निकास;
	पूर्ण
	sl->mtu	     = mtu;
	sl->buffsize = len;
	sl->rcount   = 0;
	sl->xleft    = 0;
	rbuff = xchg(&sl->rbuff, rbuff);
	xbuff = xchg(&sl->xbuff, xbuff);
#अगर_घोषित SL_INCLUDE_CSLIP
	cbuff = xchg(&sl->cbuff, cbuff);
	slcomp = xchg(&sl->slcomp, slcomp);
#पूर्ण_अगर
#अगर_घोषित CONFIG_SLIP_MODE_SLIP6
	sl->xdata    = 0;
	sl->xbits    = 0;
#पूर्ण_अगर
	spin_unlock_bh(&sl->lock);
	err = 0;

	/* Cleanup */
err_निकास:
#अगर_घोषित SL_INCLUDE_CSLIP
	kमुक्त(cbuff);
	slhc_मुक्त(slcomp);
#पूर्ण_अगर
	kमुक्त(xbuff);
	kमुक्त(rbuff);
	वापस err;
पूर्ण

/* Free a SLIP channel buffers. */
अटल व्योम sl_मुक्त_bufs(काष्ठा slip *sl)
अणु
	/* Free all SLIP frame buffers. */
	kमुक्त(xchg(&sl->rbuff, शून्य));
	kमुक्त(xchg(&sl->xbuff, शून्य));
#अगर_घोषित SL_INCLUDE_CSLIP
	kमुक्त(xchg(&sl->cbuff, शून्य));
	slhc_मुक्त(xchg(&sl->slcomp, शून्य));
#पूर्ण_अगर
पूर्ण

/*
   Reallocate slip channel buffers.
 */

अटल पूर्णांक sl_पुनः_स्मृति_bufs(काष्ठा slip *sl, पूर्णांक mtu)
अणु
	पूर्णांक err = 0;
	काष्ठा net_device *dev = sl->dev;
	अचिन्हित अक्षर *xbuff, *rbuff;
#अगर_घोषित SL_INCLUDE_CSLIP
	अचिन्हित अक्षर *cbuff;
#पूर्ण_अगर
	पूर्णांक len = mtu * 2;

/*
 * allow क्रम arrival of larger UDP packets, even अगर we say not to
 * also fixes a bug in which SunOS sends 512-byte packets even with
 * an MSS of 128
 */
	अगर (len < 576 * 2)
		len = 576 * 2;

	xbuff = kदो_स्मृति(len + 4, GFP_ATOMIC);
	rbuff = kदो_स्मृति(len + 4, GFP_ATOMIC);
#अगर_घोषित SL_INCLUDE_CSLIP
	cbuff = kदो_स्मृति(len + 4, GFP_ATOMIC);
#पूर्ण_अगर


#अगर_घोषित SL_INCLUDE_CSLIP
	अगर (xbuff == शून्य || rbuff == शून्य || cbuff == शून्य)  अणु
#अन्यथा
	अगर (xbuff == शून्य || rbuff == शून्य)  अणु
#पूर्ण_अगर
		अगर (mtu > sl->mtu) अणु
			prपूर्णांकk(KERN_WARNING "%s: unable to grow slip buffers, MTU change cancelled.\n",
			       dev->name);
			err = -ENOBUFS;
		पूर्ण
		जाओ करोne;
	पूर्ण
	spin_lock_bh(&sl->lock);

	err = -ENODEV;
	अगर (sl->tty == शून्य)
		जाओ करोne_on_bh;

	xbuff    = xchg(&sl->xbuff, xbuff);
	rbuff    = xchg(&sl->rbuff, rbuff);
#अगर_घोषित SL_INCLUDE_CSLIP
	cbuff    = xchg(&sl->cbuff, cbuff);
#पूर्ण_अगर
	अगर (sl->xleft)  अणु
		अगर (sl->xleft <= len)  अणु
			स_नकल(sl->xbuff, sl->xhead, sl->xleft);
		पूर्ण अन्यथा  अणु
			sl->xleft = 0;
			dev->stats.tx_dropped++;
		पूर्ण
	पूर्ण
	sl->xhead = sl->xbuff;

	अगर (sl->rcount)  अणु
		अगर (sl->rcount <= len) अणु
			स_नकल(sl->rbuff, rbuff, sl->rcount);
		पूर्ण अन्यथा  अणु
			sl->rcount = 0;
			dev->stats.rx_over_errors++;
			set_bit(SLF_ERROR, &sl->flags);
		पूर्ण
	पूर्ण
	sl->mtu      = mtu;
	dev->mtu      = mtu;
	sl->buffsize = len;
	err = 0;

करोne_on_bh:
	spin_unlock_bh(&sl->lock);

करोne:
	kमुक्त(xbuff);
	kमुक्त(rbuff);
#अगर_घोषित SL_INCLUDE_CSLIP
	kमुक्त(cbuff);
#पूर्ण_अगर
	वापस err;
पूर्ण


/* Set the "sending" flag.  This must be atomic hence the set_bit. */
अटल अंतरभूत व्योम sl_lock(काष्ठा slip *sl)
अणु
	netअगर_stop_queue(sl->dev);
पूर्ण


/* Clear the "sending" flag.  This must be atomic, hence the ASM. */
अटल अंतरभूत व्योम sl_unlock(काष्ठा slip *sl)
अणु
	netअगर_wake_queue(sl->dev);
पूर्ण

/* Send one completely decapsulated IP datagram to the IP layer. */
अटल व्योम sl_bump(काष्ठा slip *sl)
अणु
	काष्ठा net_device *dev = sl->dev;
	काष्ठा sk_buff *skb;
	पूर्णांक count;

	count = sl->rcount;
#अगर_घोषित SL_INCLUDE_CSLIP
	अगर (sl->mode & (SL_MODE_ADAPTIVE | SL_MODE_CSLIP)) अणु
		अचिन्हित अक्षर c = sl->rbuff[0];
		अगर (c & SL_TYPE_COMPRESSED_TCP) अणु
			/* ignore compressed packets when CSLIP is off */
			अगर (!(sl->mode & SL_MODE_CSLIP)) अणु
				prपूर्णांकk(KERN_WARNING "%s: compressed packet ignored\n", dev->name);
				वापस;
			पूर्ण
			/* make sure we've reserved enough space क्रम uncompress
			   to use */
			अगर (count + 80 > sl->buffsize) अणु
				dev->stats.rx_over_errors++;
				वापस;
			पूर्ण
			count = slhc_uncompress(sl->slcomp, sl->rbuff, count);
			अगर (count <= 0)
				वापस;
		पूर्ण अन्यथा अगर (c >= SL_TYPE_UNCOMPRESSED_TCP) अणु
			अगर (!(sl->mode & SL_MODE_CSLIP)) अणु
				/* turn on header compression */
				sl->mode |= SL_MODE_CSLIP;
				sl->mode &= ~SL_MODE_ADAPTIVE;
				prपूर्णांकk(KERN_INFO "%s: header compression turned on\n", dev->name);
			पूर्ण
			sl->rbuff[0] &= 0x4f;
			अगर (slhc_remember(sl->slcomp, sl->rbuff, count) <= 0)
				वापस;
		पूर्ण
	पूर्ण
#पूर्ण_अगर  /* SL_INCLUDE_CSLIP */

	dev->stats.rx_bytes += count;

	skb = dev_alloc_skb(count);
	अगर (skb == शून्य) अणु
		prपूर्णांकk(KERN_WARNING "%s: memory squeeze, dropping packet.\n", dev->name);
		dev->stats.rx_dropped++;
		वापस;
	पूर्ण
	skb->dev = dev;
	skb_put_data(skb, sl->rbuff, count);
	skb_reset_mac_header(skb);
	skb->protocol = htons(ETH_P_IP);
	netअगर_rx_ni(skb);
	dev->stats.rx_packets++;
पूर्ण

/* Encapsulate one IP datagram and stuff पूर्णांकo a TTY queue. */
अटल व्योम sl_encaps(काष्ठा slip *sl, अचिन्हित अक्षर *icp, पूर्णांक len)
अणु
	अचिन्हित अक्षर *p;
	पूर्णांक actual, count;

	अगर (len > sl->mtu) अणु		/* Sigh, shouldn't occur BUT ... */
		prपूर्णांकk(KERN_WARNING "%s: truncating oversized transmit packet!\n", sl->dev->name);
		sl->dev->stats.tx_dropped++;
		sl_unlock(sl);
		वापस;
	पूर्ण

	p = icp;
#अगर_घोषित SL_INCLUDE_CSLIP
	अगर (sl->mode & SL_MODE_CSLIP)
		len = slhc_compress(sl->slcomp, p, len, sl->cbuff, &p, 1);
#पूर्ण_अगर
#अगर_घोषित CONFIG_SLIP_MODE_SLIP6
	अगर (sl->mode & SL_MODE_SLIP6)
		count = slip_esc6(p, sl->xbuff, len);
	अन्यथा
#पूर्ण_अगर
		count = slip_esc(p, sl->xbuff, len);

	/* Order of next two lines is *very* important.
	 * When we are sending a little amount of data,
	 * the transfer may be completed inside the ops->ग_लिखो()
	 * routine, because it's running with पूर्णांकerrupts enabled.
	 * In this हाल we *never* got WRITE_WAKEUP event,
	 * अगर we did not request it beक्रमe ग_लिखो operation.
	 *       14 Oct 1994  Dmitry Gorodchanin.
	 */
	set_bit(TTY_DO_WRITE_WAKEUP, &sl->tty->flags);
	actual = sl->tty->ops->ग_लिखो(sl->tty, sl->xbuff, count);
#अगर_घोषित SL_CHECK_TRANSMIT
	netअगर_trans_update(sl->dev);
#पूर्ण_अगर
	sl->xleft = count - actual;
	sl->xhead = sl->xbuff + actual;
#अगर_घोषित CONFIG_SLIP_SMART
	/* VSV */
	clear_bit(SLF_OUTWAIT, &sl->flags);	/* reset outfill flag */
#पूर्ण_अगर
पूर्ण

/* Write out any reमुख्यing transmit buffer. Scheduled when tty is writable */
अटल व्योम slip_transmit(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा slip *sl = container_of(work, काष्ठा slip, tx_work);
	पूर्णांक actual;

	spin_lock_bh(&sl->lock);
	/* First make sure we're connected. */
	अगर (!sl->tty || sl->magic != SLIP_MAGIC || !netअगर_running(sl->dev)) अणु
		spin_unlock_bh(&sl->lock);
		वापस;
	पूर्ण

	अगर (sl->xleft <= 0)  अणु
		/* Now serial buffer is almost मुक्त & we can start
		 * transmission of another packet */
		sl->dev->stats.tx_packets++;
		clear_bit(TTY_DO_WRITE_WAKEUP, &sl->tty->flags);
		spin_unlock_bh(&sl->lock);
		sl_unlock(sl);
		वापस;
	पूर्ण

	actual = sl->tty->ops->ग_लिखो(sl->tty, sl->xhead, sl->xleft);
	sl->xleft -= actual;
	sl->xhead += actual;
	spin_unlock_bh(&sl->lock);
पूर्ण

/*
 * Called by the driver when there's room क्रम more data.
 * Schedule the transmit.
 */
अटल व्योम slip_ग_लिखो_wakeup(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा slip *sl;

	rcu_पढ़ो_lock();
	sl = rcu_dereference(tty->disc_data);
	अगर (sl)
		schedule_work(&sl->tx_work);
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम sl_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा slip *sl = netdev_priv(dev);

	spin_lock(&sl->lock);

	अगर (netअगर_queue_stopped(dev)) अणु
		अगर (!netअगर_running(dev))
			जाओ out;

		/* May be we must check transmitter समयout here ?
		 *      14 Oct 1994 Dmitry Gorodchanin.
		 */
#अगर_घोषित SL_CHECK_TRANSMIT
		अगर (समय_beक्रमe(jअगरfies, dev_trans_start(dev) + 20 * HZ))  अणु
			/* 20 sec समयout not reached */
			जाओ out;
		पूर्ण
		prपूर्णांकk(KERN_WARNING "%s: transmit timed out, %s?\n",
			dev->name,
			(tty_अक्षरs_in_buffer(sl->tty) || sl->xleft) ?
				"bad line quality" : "driver error");
		sl->xleft = 0;
		clear_bit(TTY_DO_WRITE_WAKEUP, &sl->tty->flags);
		sl_unlock(sl);
#पूर्ण_अगर
	पूर्ण
out:
	spin_unlock(&sl->lock);
पूर्ण


/* Encapsulate an IP datagram and kick it पूर्णांकo a TTY queue. */
अटल netdev_tx_t
sl_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा slip *sl = netdev_priv(dev);

	spin_lock(&sl->lock);
	अगर (!netअगर_running(dev)) अणु
		spin_unlock(&sl->lock);
		prपूर्णांकk(KERN_WARNING "%s: xmit call when iface is down\n", dev->name);
		dev_kमुक्त_skb(skb);
		वापस NETDEV_TX_OK;
	पूर्ण
	अगर (sl->tty == शून्य) अणु
		spin_unlock(&sl->lock);
		dev_kमुक्त_skb(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	sl_lock(sl);
	dev->stats.tx_bytes += skb->len;
	sl_encaps(sl, skb->data, skb->len);
	spin_unlock(&sl->lock);

	dev_kमुक्त_skb(skb);
	वापस NETDEV_TX_OK;
पूर्ण


/******************************************
 *   Routines looking at netdevice side.
 ******************************************/

/* Netdevice UP -> DOWN routine */

अटल पूर्णांक
sl_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा slip *sl = netdev_priv(dev);

	spin_lock_bh(&sl->lock);
	अगर (sl->tty)
		/* TTY discipline is running. */
		clear_bit(TTY_DO_WRITE_WAKEUP, &sl->tty->flags);
	netअगर_stop_queue(dev);
	sl->rcount   = 0;
	sl->xleft    = 0;
	spin_unlock_bh(&sl->lock);

	वापस 0;
पूर्ण

/* Netdevice DOWN -> UP routine */

अटल पूर्णांक sl_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा slip *sl = netdev_priv(dev);

	अगर (sl->tty == शून्य)
		वापस -ENODEV;

	sl->flags &= (1 << SLF_INUSE);
	netअगर_start_queue(dev);
	वापस 0;
पूर्ण

/* Netdevice change MTU request */

अटल पूर्णांक sl_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	काष्ठा slip *sl = netdev_priv(dev);

	वापस sl_पुनः_स्मृति_bufs(sl, new_mtu);
पूर्ण

/* Netdevice get statistics request */

अटल व्योम
sl_get_stats64(काष्ठा net_device *dev, काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा net_device_stats *devstats = &dev->stats;
#अगर_घोषित SL_INCLUDE_CSLIP
	काष्ठा slip *sl = netdev_priv(dev);
	काष्ठा slcompress *comp = sl->slcomp;
#पूर्ण_अगर
	stats->rx_packets     = devstats->rx_packets;
	stats->tx_packets     = devstats->tx_packets;
	stats->rx_bytes       = devstats->rx_bytes;
	stats->tx_bytes       = devstats->tx_bytes;
	stats->rx_dropped     = devstats->rx_dropped;
	stats->tx_dropped     = devstats->tx_dropped;
	stats->tx_errors      = devstats->tx_errors;
	stats->rx_errors      = devstats->rx_errors;
	stats->rx_over_errors = devstats->rx_over_errors;

#अगर_घोषित SL_INCLUDE_CSLIP
	अगर (comp) अणु
		/* Generic compressed statistics */
		stats->rx_compressed   = comp->sls_i_compressed;
		stats->tx_compressed   = comp->sls_o_compressed;

		/* Are we really still needs this? */
		stats->rx_fअगरo_errors += comp->sls_i_compressed;
		stats->rx_dropped     += comp->sls_i_tossed;
		stats->tx_fअगरo_errors += comp->sls_o_compressed;
		stats->collisions     += comp->sls_o_misses;
	पूर्ण
#पूर्ण_अगर
पूर्ण

/* Netdevice रेजिस्टर callback */

अटल पूर्णांक sl_init(काष्ठा net_device *dev)
अणु
	काष्ठा slip *sl = netdev_priv(dev);

	/*
	 *	Finish setting up the DEVICE info.
	 */

	dev->mtu		= sl->mtu;
	dev->type		= ARPHRD_SLIP + sl->mode;
#अगर_घोषित SL_CHECK_TRANSMIT
	dev->watchकरोg_समयo	= 20*HZ;
#पूर्ण_अगर
	वापस 0;
पूर्ण


अटल व्योम sl_uninit(काष्ठा net_device *dev)
अणु
	काष्ठा slip *sl = netdev_priv(dev);

	sl_मुक्त_bufs(sl);
पूर्ण

/* Hook the deकाष्ठाor so we can मुक्त slip devices at the right poपूर्णांक in समय */
अटल व्योम sl_मुक्त_netdev(काष्ठा net_device *dev)
अणु
	पूर्णांक i = dev->base_addr;

	slip_devs[i] = शून्य;
पूर्ण

अटल स्थिर काष्ठा net_device_ops sl_netdev_ops = अणु
	.nकरो_init		= sl_init,
	.nकरो_uninit	  	= sl_uninit,
	.nकरो_खोलो		= sl_खोलो,
	.nकरो_stop		= sl_बंद,
	.nकरो_start_xmit		= sl_xmit,
	.nकरो_get_stats64        = sl_get_stats64,
	.nकरो_change_mtu		= sl_change_mtu,
	.nकरो_tx_समयout		= sl_tx_समयout,
#अगर_घोषित CONFIG_SLIP_SMART
	.nकरो_करो_ioctl		= sl_ioctl,
#पूर्ण_अगर
पूर्ण;


अटल व्योम sl_setup(काष्ठा net_device *dev)
अणु
	dev->netdev_ops		= &sl_netdev_ops;
	dev->needs_मुक्त_netdev	= true;
	dev->priv_deकाष्ठाor	= sl_मुक्त_netdev;

	dev->hard_header_len	= 0;
	dev->addr_len		= 0;
	dev->tx_queue_len	= 10;

	/* MTU range: 68 - 65534 */
	dev->min_mtu = 68;
	dev->max_mtu = 65534;

	/* New-style flags. */
	dev->flags		= IFF_NOARP|IFF_POINTOPOINT|IFF_MULTICAST;
पूर्ण

/******************************************
  Routines looking at TTY side.
 ******************************************/


/*
 * Handle the 'receiver data ready' पूर्णांकerrupt.
 * This function is called by the 'tty_io' module in the kernel when
 * a block of SLIP data has been received, which can now be decapsulated
 * and sent on to some IP layer क्रम further processing. This will not
 * be re-entered जबतक running but other ldisc functions may be called
 * in parallel
 */

अटल व्योम slip_receive_buf(काष्ठा tty_काष्ठा *tty, स्थिर अचिन्हित अक्षर *cp,
							अक्षर *fp, पूर्णांक count)
अणु
	काष्ठा slip *sl = tty->disc_data;

	अगर (!sl || sl->magic != SLIP_MAGIC || !netअगर_running(sl->dev))
		वापस;

	/* Read the अक्षरacters out of the buffer */
	जबतक (count--) अणु
		अगर (fp && *fp++) अणु
			अगर (!test_and_set_bit(SLF_ERROR, &sl->flags))
				sl->dev->stats.rx_errors++;
			cp++;
			जारी;
		पूर्ण
#अगर_घोषित CONFIG_SLIP_MODE_SLIP6
		अगर (sl->mode & SL_MODE_SLIP6)
			slip_unesc6(sl, *cp++);
		अन्यथा
#पूर्ण_अगर
			slip_unesc(sl, *cp++);
	पूर्ण
पूर्ण

/************************************
 *  slip_खोलो helper routines.
 ************************************/

/* Collect hanged up channels */
अटल व्योम sl_sync(व्योम)
अणु
	पूर्णांक i;
	काष्ठा net_device *dev;
	काष्ठा slip	  *sl;

	क्रम (i = 0; i < slip_maxdev; i++) अणु
		dev = slip_devs[i];
		अगर (dev == शून्य)
			अवरोध;

		sl = netdev_priv(dev);
		अगर (sl->tty || sl->leased)
			जारी;
		अगर (dev->flags & IFF_UP)
			dev_बंद(dev);
	पूर्ण
पूर्ण


/* Find a मुक्त SLIP channel, and link in this `tty' line. */
अटल काष्ठा slip *sl_alloc(व्योम)
अणु
	पूर्णांक i;
	अक्षर name[IFNAMSIZ];
	काष्ठा net_device *dev = शून्य;
	काष्ठा slip       *sl;

	क्रम (i = 0; i < slip_maxdev; i++) अणु
		dev = slip_devs[i];
		अगर (dev == शून्य)
			अवरोध;
	पूर्ण
	/* Sorry, too many, all slots in use */
	अगर (i >= slip_maxdev)
		वापस शून्य;

	प्र_लिखो(name, "sl%d", i);
	dev = alloc_netdev(माप(*sl), name, NET_NAME_UNKNOWN, sl_setup);
	अगर (!dev)
		वापस शून्य;

	dev->base_addr  = i;
	sl = netdev_priv(dev);

	/* Initialize channel control data */
	sl->magic       = SLIP_MAGIC;
	sl->dev	      	= dev;
	spin_lock_init(&sl->lock);
	INIT_WORK(&sl->tx_work, slip_transmit);
	sl->mode        = SL_MODE_DEFAULT;
#अगर_घोषित CONFIG_SLIP_SMART
	/* initialize समयr_list काष्ठा */
	समयr_setup(&sl->keepalive_समयr, sl_keepalive, 0);
	समयr_setup(&sl->outfill_समयr, sl_outfill, 0);
#पूर्ण_अगर
	slip_devs[i] = dev;
	वापस sl;
पूर्ण

/*
 * Open the high-level part of the SLIP channel.
 * This function is called by the TTY module when the
 * SLIP line discipline is called क्रम.  Because we are
 * sure the tty line exists, we only have to link it to
 * a मुक्त SLIP channel...
 *
 * Called in process context serialized from other ldisc calls.
 */

अटल पूर्णांक slip_खोलो(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा slip *sl;
	पूर्णांक err;

	अगर (!capable(CAP_NET_ADMIN))
		वापस -EPERM;

	अगर (tty->ops->ग_लिखो == शून्य)
		वापस -EOPNOTSUPP;

	/* RTnetlink lock is misused here to serialize concurrent
	   खोलोs of slip channels. There are better ways, but it is
	   the simplest one.
	 */
	rtnl_lock();

	/* Collect hanged up channels. */
	sl_sync();

	sl = tty->disc_data;

	err = -EEXIST;
	/* First make sure we're not alपढ़ोy connected. */
	अगर (sl && sl->magic == SLIP_MAGIC)
		जाओ err_निकास;

	/* OK.  Find a मुक्त SLIP channel to use. */
	err = -ENखाता;
	sl = sl_alloc();
	अगर (sl == शून्य)
		जाओ err_निकास;

	sl->tty = tty;
	tty->disc_data = sl;
	sl->pid = current->pid;

	अगर (!test_bit(SLF_INUSE, &sl->flags)) अणु
		/* Perक्रमm the low-level SLIP initialization. */
		err = sl_alloc_bufs(sl, SL_MTU);
		अगर (err)
			जाओ err_मुक्त_chan;

		set_bit(SLF_INUSE, &sl->flags);

		err = रेजिस्टर_netdevice(sl->dev);
		अगर (err)
			जाओ err_मुक्त_bufs;
	पूर्ण

#अगर_घोषित CONFIG_SLIP_SMART
	अगर (sl->keepalive) अणु
		sl->keepalive_समयr.expires = jअगरfies + sl->keepalive * HZ;
		add_समयr(&sl->keepalive_समयr);
	पूर्ण
	अगर (sl->outfill) अणु
		sl->outfill_समयr.expires = jअगरfies + sl->outfill * HZ;
		add_समयr(&sl->outfill_समयr);
	पूर्ण
#पूर्ण_अगर

	/* Done.  We have linked the TTY line to a channel. */
	rtnl_unlock();
	tty->receive_room = 65536;	/* We करोn't flow control */

	/* TTY layer expects 0 on success */
	वापस 0;

err_मुक्त_bufs:
	sl_मुक्त_bufs(sl);

err_मुक्त_chan:
	sl->tty = शून्य;
	tty->disc_data = शून्य;
	clear_bit(SLF_INUSE, &sl->flags);
	sl_मुक्त_netdev(sl->dev);
	/* करो not call मुक्त_netdev beक्रमe rtnl_unlock */
	rtnl_unlock();
	मुक्त_netdev(sl->dev);
	वापस err;

err_निकास:
	rtnl_unlock();

	/* Count references from TTY module */
	वापस err;
पूर्ण

/*
 * Close करोwn a SLIP channel.
 * This means flushing out any pending queues, and then वापसing. This
 * call is serialized against other ldisc functions.
 *
 * We also use this method fo a hangup event
 */

अटल व्योम slip_बंद(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा slip *sl = tty->disc_data;

	/* First make sure we're connected. */
	अगर (!sl || sl->magic != SLIP_MAGIC || sl->tty != tty)
		वापस;

	spin_lock_bh(&sl->lock);
	rcu_assign_poपूर्णांकer(tty->disc_data, शून्य);
	sl->tty = शून्य;
	spin_unlock_bh(&sl->lock);

	synchronize_rcu();
	flush_work(&sl->tx_work);

	/* VSV = very important to हटाओ समयrs */
#अगर_घोषित CONFIG_SLIP_SMART
	del_समयr_sync(&sl->keepalive_समयr);
	del_समयr_sync(&sl->outfill_समयr);
#पूर्ण_अगर
	/* Flush network side */
	unरेजिस्टर_netdev(sl->dev);
	/* This will complete via sl_मुक्त_netdev */
पूर्ण

अटल पूर्णांक slip_hangup(काष्ठा tty_काष्ठा *tty)
अणु
	slip_बंद(tty);
	वापस 0;
पूर्ण
 /************************************************************************
  *			STANDARD SLIP ENCAPSULATION		  	 *
  ************************************************************************/

अटल पूर्णांक slip_esc(अचिन्हित अक्षर *s, अचिन्हित अक्षर *d, पूर्णांक len)
अणु
	अचिन्हित अक्षर *ptr = d;
	अचिन्हित अक्षर c;

	/*
	 * Send an initial END अक्षरacter to flush out any
	 * data that may have accumulated in the receiver
	 * due to line noise.
	 */

	*ptr++ = END;

	/*
	 * For each byte in the packet, send the appropriate
	 * अक्षरacter sequence, according to the SLIP protocol.
	 */

	जबतक (len-- > 0) अणु
		चयन (c = *s++) अणु
		हाल END:
			*ptr++ = ESC;
			*ptr++ = ESC_END;
			अवरोध;
		हाल ESC:
			*ptr++ = ESC;
			*ptr++ = ESC_ESC;
			अवरोध;
		शेष:
			*ptr++ = c;
			अवरोध;
		पूर्ण
	पूर्ण
	*ptr++ = END;
	वापस ptr - d;
पूर्ण

अटल व्योम slip_unesc(काष्ठा slip *sl, अचिन्हित अक्षर s)
अणु

	चयन (s) अणु
	हाल END:
#अगर_घोषित CONFIG_SLIP_SMART
		/* drop keeptest bit = VSV */
		अगर (test_bit(SLF_KEEPTEST, &sl->flags))
			clear_bit(SLF_KEEPTEST, &sl->flags);
#पूर्ण_अगर

		अगर (!test_and_clear_bit(SLF_ERROR, &sl->flags) &&
		    (sl->rcount > 2))
			sl_bump(sl);
		clear_bit(SLF_ESCAPE, &sl->flags);
		sl->rcount = 0;
		वापस;

	हाल ESC:
		set_bit(SLF_ESCAPE, &sl->flags);
		वापस;
	हाल ESC_ESC:
		अगर (test_and_clear_bit(SLF_ESCAPE, &sl->flags))
			s = ESC;
		अवरोध;
	हाल ESC_END:
		अगर (test_and_clear_bit(SLF_ESCAPE, &sl->flags))
			s = END;
		अवरोध;
	पूर्ण
	अगर (!test_bit(SLF_ERROR, &sl->flags))  अणु
		अगर (sl->rcount < sl->buffsize)  अणु
			sl->rbuff[sl->rcount++] = s;
			वापस;
		पूर्ण
		sl->dev->stats.rx_over_errors++;
		set_bit(SLF_ERROR, &sl->flags);
	पूर्ण
पूर्ण


#अगर_घोषित CONFIG_SLIP_MODE_SLIP6
/************************************************************************
 *			 6 BIT SLIP ENCAPSULATION			*
 ************************************************************************/

अटल पूर्णांक slip_esc6(अचिन्हित अक्षर *s, अचिन्हित अक्षर *d, पूर्णांक len)
अणु
	अचिन्हित अक्षर *ptr = d;
	अचिन्हित अक्षर c;
	पूर्णांक i;
	अचिन्हित लघु v = 0;
	लघु bits = 0;

	/*
	 * Send an initial END अक्षरacter to flush out any
	 * data that may have accumulated in the receiver
	 * due to line noise.
	 */

	*ptr++ = 0x70;

	/*
	 * Encode the packet पूर्णांकo prपूर्णांकable ascii अक्षरacters
	 */

	क्रम (i = 0; i < len; ++i) अणु
		v = (v << 8) | s[i];
		bits += 8;
		जबतक (bits >= 6) अणु
			bits -= 6;
			c = 0x30 + ((v >> bits) & 0x3F);
			*ptr++ = c;
		पूर्ण
	पूर्ण
	अगर (bits) अणु
		c = 0x30 + ((v << (6 - bits)) & 0x3F);
		*ptr++ = c;
	पूर्ण
	*ptr++ = 0x70;
	वापस ptr - d;
पूर्ण

अटल व्योम slip_unesc6(काष्ठा slip *sl, अचिन्हित अक्षर s)
अणु
	अचिन्हित अक्षर c;

	अगर (s == 0x70) अणु
#अगर_घोषित CONFIG_SLIP_SMART
		/* drop keeptest bit = VSV */
		अगर (test_bit(SLF_KEEPTEST, &sl->flags))
			clear_bit(SLF_KEEPTEST, &sl->flags);
#पूर्ण_अगर

		अगर (!test_and_clear_bit(SLF_ERROR, &sl->flags) &&
		    (sl->rcount > 2))
			sl_bump(sl);
		sl->rcount = 0;
		sl->xbits = 0;
		sl->xdata = 0;
	पूर्ण अन्यथा अगर (s >= 0x30 && s < 0x70) अणु
		sl->xdata = (sl->xdata << 6) | ((s - 0x30) & 0x3F);
		sl->xbits += 6;
		अगर (sl->xbits >= 8) अणु
			sl->xbits -= 8;
			c = (अचिन्हित अक्षर)(sl->xdata >> sl->xbits);
			अगर (!test_bit(SLF_ERROR, &sl->flags))  अणु
				अगर (sl->rcount < sl->buffsize)  अणु
					sl->rbuff[sl->rcount++] = c;
					वापस;
				पूर्ण
				sl->dev->stats.rx_over_errors++;
				set_bit(SLF_ERROR, &sl->flags);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_SLIP_MODE_SLIP6 */

/* Perक्रमm I/O control on an active SLIP channel. */
अटल पूर्णांक slip_ioctl(काष्ठा tty_काष्ठा *tty, काष्ठा file *file,
					अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा slip *sl = tty->disc_data;
	अचिन्हित पूर्णांक पंचांगp;
	पूर्णांक __user *p = (पूर्णांक __user *)arg;

	/* First make sure we're connected. */
	अगर (!sl || sl->magic != SLIP_MAGIC)
		वापस -EINVAL;

	चयन (cmd) अणु
	हाल SIOCGIFNAME:
		पंचांगp = म_माप(sl->dev->name) + 1;
		अगर (copy_to_user((व्योम __user *)arg, sl->dev->name, पंचांगp))
			वापस -EFAULT;
		वापस 0;

	हाल SIOCGIFENCAP:
		अगर (put_user(sl->mode, p))
			वापस -EFAULT;
		वापस 0;

	हाल SIOCSIFENCAP:
		अगर (get_user(पंचांगp, p))
			वापस -EFAULT;
#अगर_अघोषित SL_INCLUDE_CSLIP
		अगर (पंचांगp & (SL_MODE_CSLIP|SL_MODE_ADAPTIVE))
			वापस -EINVAL;
#अन्यथा
		अगर ((पंचांगp & (SL_MODE_ADAPTIVE | SL_MODE_CSLIP)) ==
		    (SL_MODE_ADAPTIVE | SL_MODE_CSLIP))
			/* वापस -EINVAL; */
			पंचांगp &= ~SL_MODE_ADAPTIVE;
#पूर्ण_अगर
#अगर_अघोषित CONFIG_SLIP_MODE_SLIP6
		अगर (पंचांगp & SL_MODE_SLIP6)
			वापस -EINVAL;
#पूर्ण_अगर
		sl->mode = पंचांगp;
		sl->dev->type = ARPHRD_SLIP + sl->mode;
		वापस 0;

	हाल SIOCSIFHWADDR:
		वापस -EINVAL;

#अगर_घोषित CONFIG_SLIP_SMART
	/* VSV changes start here */
	हाल SIOCSKEEPALIVE:
		अगर (get_user(पंचांगp, p))
			वापस -EFAULT;
		अगर (पंचांगp > 255) /* max क्रम unअक्षर */
			वापस -EINVAL;

		spin_lock_bh(&sl->lock);
		अगर (!sl->tty) अणु
			spin_unlock_bh(&sl->lock);
			वापस -ENODEV;
		पूर्ण
		sl->keepalive = (u8)पंचांगp;
		अगर (sl->keepalive != 0) अणु
			mod_समयr(&sl->keepalive_समयr,
					jअगरfies + sl->keepalive * HZ);
			set_bit(SLF_KEEPTEST, &sl->flags);
		पूर्ण अन्यथा
			del_समयr(&sl->keepalive_समयr);
		spin_unlock_bh(&sl->lock);
		वापस 0;

	हाल SIOCGKEEPALIVE:
		अगर (put_user(sl->keepalive, p))
			वापस -EFAULT;
		वापस 0;

	हाल SIOCSOUTFILL:
		अगर (get_user(पंचांगp, p))
			वापस -EFAULT;
		अगर (पंचांगp > 255) /* max क्रम unअक्षर */
			वापस -EINVAL;
		spin_lock_bh(&sl->lock);
		अगर (!sl->tty) अणु
			spin_unlock_bh(&sl->lock);
			वापस -ENODEV;
		पूर्ण
		sl->outfill = (u8)पंचांगp;
		अगर (sl->outfill != 0) अणु
			mod_समयr(&sl->outfill_समयr,
						jअगरfies + sl->outfill * HZ);
			set_bit(SLF_OUTWAIT, &sl->flags);
		पूर्ण अन्यथा
			del_समयr(&sl->outfill_समयr);
		spin_unlock_bh(&sl->lock);
		वापस 0;

	हाल SIOCGOUTFILL:
		अगर (put_user(sl->outfill, p))
			वापस -EFAULT;
		वापस 0;
	/* VSV changes end */
#पूर्ण_अगर
	शेष:
		वापस tty_mode_ioctl(tty, file, cmd, arg);
	पूर्ण
पूर्ण

/* VSV changes start here */
#अगर_घोषित CONFIG_SLIP_SMART
/* function करो_ioctl called from net/core/dev.c
   to allow get/set outfill/keepalive parameter
   by अगरconfig                                 */

अटल पूर्णांक sl_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	काष्ठा slip *sl = netdev_priv(dev);
	अचिन्हित दीर्घ *p = (अचिन्हित दीर्घ *)&rq->अगरr_अगरru;

	अगर (sl == शून्य)		/* Allocation failed ?? */
		वापस -ENODEV;

	spin_lock_bh(&sl->lock);

	अगर (!sl->tty) अणु
		spin_unlock_bh(&sl->lock);
		वापस -ENODEV;
	पूर्ण

	चयन (cmd) अणु
	हाल SIOCSKEEPALIVE:
		/* max क्रम unअक्षर */
		अगर ((अचिन्हित)*p > 255) अणु
			spin_unlock_bh(&sl->lock);
			वापस -EINVAL;
		पूर्ण
		sl->keepalive = (u8)*p;
		अगर (sl->keepalive != 0) अणु
			sl->keepalive_समयr.expires =
						jअगरfies + sl->keepalive * HZ;
			mod_समयr(&sl->keepalive_समयr,
						jअगरfies + sl->keepalive * HZ);
			set_bit(SLF_KEEPTEST, &sl->flags);
		पूर्ण अन्यथा
			del_समयr(&sl->keepalive_समयr);
		अवरोध;

	हाल SIOCGKEEPALIVE:
		*p = sl->keepalive;
		अवरोध;

	हाल SIOCSOUTFILL:
		अगर ((अचिन्हित)*p > 255) अणु /* max क्रम unअक्षर */
			spin_unlock_bh(&sl->lock);
			वापस -EINVAL;
		पूर्ण
		sl->outfill = (u8)*p;
		अगर (sl->outfill != 0) अणु
			mod_समयr(&sl->outfill_समयr,
						jअगरfies + sl->outfill * HZ);
			set_bit(SLF_OUTWAIT, &sl->flags);
		पूर्ण अन्यथा
			del_समयr(&sl->outfill_समयr);
		अवरोध;

	हाल SIOCGOUTFILL:
		*p = sl->outfill;
		अवरोध;

	हाल SIOCSLEASE:
		/* Resolve race condition, when ioctl'ing hanged up
		   and खोलोed by another process device.
		 */
		अगर (sl->tty != current->संकेत->tty &&
						sl->pid != current->pid) अणु
			spin_unlock_bh(&sl->lock);
			वापस -EPERM;
		पूर्ण
		sl->leased = 0;
		अगर (*p)
			sl->leased = 1;
		अवरोध;

	हाल SIOCGLEASE:
		*p = sl->leased;
	पूर्ण
	spin_unlock_bh(&sl->lock);
	वापस 0;
पूर्ण
#पूर्ण_अगर
/* VSV changes end */

अटल काष्ठा tty_ldisc_ops sl_ldisc = अणु
	.owner 		= THIS_MODULE,
	.name 		= "slip",
	.खोलो 		= slip_खोलो,
	.बंद	 	= slip_बंद,
	.hangup	 	= slip_hangup,
	.ioctl		= slip_ioctl,
	.receive_buf	= slip_receive_buf,
	.ग_लिखो_wakeup	= slip_ग_लिखो_wakeup,
पूर्ण;

अटल पूर्णांक __init slip_init(व्योम)
अणु
	पूर्णांक status;

	अगर (slip_maxdev < 4)
		slip_maxdev = 4; /* Sanity */

	prपूर्णांकk(KERN_INFO "SLIP: version %s (dynamic channels, max=%d)"
#अगर_घोषित CONFIG_SLIP_MODE_SLIP6
	       " (6 bit encapsulation enabled)"
#पूर्ण_अगर
	       ".\n",
	       SLIP_VERSION, slip_maxdev);
#अगर defined(SL_INCLUDE_CSLIP)
	prपूर्णांकk(KERN_INFO "CSLIP: code copyright 1989 Regents of the University of California.\n");
#पूर्ण_अगर
#अगर_घोषित CONFIG_SLIP_SMART
	prपूर्णांकk(KERN_INFO "SLIP linefill/keepalive option.\n");
#पूर्ण_अगर

	slip_devs = kसुस्मृति(slip_maxdev, माप(काष्ठा net_device *),
								GFP_KERNEL);
	अगर (!slip_devs)
		वापस -ENOMEM;

	/* Fill in our line protocol discipline, and रेजिस्टर it */
	status = tty_रेजिस्टर_ldisc(N_SLIP, &sl_ldisc);
	अगर (status != 0) अणु
		prपूर्णांकk(KERN_ERR "SLIP: can't register line discipline (err = %d)\n", status);
		kमुक्त(slip_devs);
	पूर्ण
	वापस status;
पूर्ण

अटल व्योम __निकास slip_निकास(व्योम)
अणु
	पूर्णांक i;
	काष्ठा net_device *dev;
	काष्ठा slip *sl;
	अचिन्हित दीर्घ समयout = jअगरfies + HZ;
	पूर्णांक busy = 0;

	अगर (slip_devs == शून्य)
		वापस;

	/* First of all: check क्रम active disciplines and hangup them.
	 */
	करो अणु
		अगर (busy)
			msleep_पूर्णांकerruptible(100);

		busy = 0;
		क्रम (i = 0; i < slip_maxdev; i++) अणु
			dev = slip_devs[i];
			अगर (!dev)
				जारी;
			sl = netdev_priv(dev);
			spin_lock_bh(&sl->lock);
			अगर (sl->tty) अणु
				busy++;
				tty_hangup(sl->tty);
			पूर्ण
			spin_unlock_bh(&sl->lock);
		पूर्ण
	पूर्ण जबतक (busy && समय_beक्रमe(jअगरfies, समयout));

	/* FIXME: hangup is async so we should रुको when करोing this second
	   phase */

	क्रम (i = 0; i < slip_maxdev; i++) अणु
		dev = slip_devs[i];
		अगर (!dev)
			जारी;
		slip_devs[i] = शून्य;

		sl = netdev_priv(dev);
		अगर (sl->tty) अणु
			prपूर्णांकk(KERN_ERR "%s: tty discipline still running\n",
			       dev->name);
		पूर्ण

		unरेजिस्टर_netdev(dev);
	पूर्ण

	kमुक्त(slip_devs);
	slip_devs = शून्य;

	i = tty_unरेजिस्टर_ldisc(N_SLIP);
	अगर (i != 0)
		prपूर्णांकk(KERN_ERR "SLIP: can't unregister line discipline (err = %d)\n", i);
पूर्ण

module_init(slip_init);
module_निकास(slip_निकास);

#अगर_घोषित CONFIG_SLIP_SMART
/*
 * This is start of the code क्रम multislip style line checking
 * added by Stanislav Voronyi. All changes beक्रमe marked VSV
 */

अटल व्योम sl_outfill(काष्ठा समयr_list *t)
अणु
	काष्ठा slip *sl = from_समयr(sl, t, outfill_समयr);

	spin_lock(&sl->lock);

	अगर (sl->tty == शून्य)
		जाओ out;

	अगर (sl->outfill) अणु
		अगर (test_bit(SLF_OUTWAIT, &sl->flags)) अणु
			/* no packets were transmitted, करो outfill */
#अगर_घोषित CONFIG_SLIP_MODE_SLIP6
			अचिन्हित अक्षर s = (sl->mode & SL_MODE_SLIP6)?0x70:END;
#अन्यथा
			अचिन्हित अक्षर s = END;
#पूर्ण_अगर
			/* put END पूर्णांकo tty queue. Is it right ??? */
			अगर (!netअगर_queue_stopped(sl->dev)) अणु
				/* अगर device busy no outfill */
				sl->tty->ops->ग_लिखो(sl->tty, &s, 1);
			पूर्ण
		पूर्ण अन्यथा
			set_bit(SLF_OUTWAIT, &sl->flags);

		mod_समयr(&sl->outfill_समयr, jअगरfies+sl->outfill*HZ);
	पूर्ण
out:
	spin_unlock(&sl->lock);
पूर्ण

अटल व्योम sl_keepalive(काष्ठा समयr_list *t)
अणु
	काष्ठा slip *sl = from_समयr(sl, t, keepalive_समयr);

	spin_lock(&sl->lock);

	अगर (sl->tty == शून्य)
		जाओ out;

	अगर (sl->keepalive) अणु
		अगर (test_bit(SLF_KEEPTEST, &sl->flags)) अणु
			/* keepalive still high :(, we must hangup */
			अगर (sl->outfill)
				/* outfill समयr must be deleted too */
				(व्योम)del_समयr(&sl->outfill_समयr);
			prपूर्णांकk(KERN_DEBUG "%s: no packets received during keepalive timeout, hangup.\n", sl->dev->name);
			/* this must hangup tty & बंद slip */
			tty_hangup(sl->tty);
			/* I think we need not something अन्यथा */
			जाओ out;
		पूर्ण अन्यथा
			set_bit(SLF_KEEPTEST, &sl->flags);

		mod_समयr(&sl->keepalive_समयr, jअगरfies+sl->keepalive*HZ);
	पूर्ण
out:
	spin_unlock(&sl->lock);
पूर्ण

#पूर्ण_अगर
MODULE_LICENSE("GPL");
MODULE_ALIAS_LDISC(N_SLIP);
