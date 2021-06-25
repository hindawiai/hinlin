<शैली गुरु>
/*
 * Linux ARCnet driver - device-independent routines
 *
 * Written 1997 by David Woodhouse.
 * Written 1994-1999 by Avery Pennarun.
 * Written 1999-2000 by Martin Mares <mj@ucw.cz>.
 * Derived from skeleton.c by Donald Becker.
 *
 * Special thanks to Contemporary Controls, Inc. (www.ccontrols.com)
 *  क्रम sponsoring the further development of this driver.
 *
 * **********************
 *
 * The original copyright was as follows:
 *
 * skeleton.c Written 1993 by Donald Becker.
 * Copyright 1993 United States Government as represented by the
 * Director, National Security Agency.  This software may only be used
 * and distributed according to the terms of the GNU General Public License as
 * modअगरied by SRC, incorporated herein by reference.
 *
 * **********************
 *
 * The change log is now in a file called ChangeLog in this directory.
 *
 * Sources:
 *  - Crynwr arcnet.com/arcether.com packet drivers.
 *  - arcnet.c v0.00 dated 1/1/94 and apparently by
 *     Donald Becker - it didn't work :)
 *  - skeleton.c v0.05 dated 11/16/93 by Donald Becker
 *     (from Linux Kernel 1.1.45)
 *  - RFC's 1201 and 1051 - re: TCP/IP over ARCnet
 *  - The official ARCnet COM9026 data sheets (!) thanks to
 *     Ken Cornetet <kcornete@nyx10.cs.du.edu>
 *  - The official ARCnet COM20020 data sheets.
 *  - Inक्रमmation on some more obscure ARCnet controller chips, thanks
 *     to the nice people at SMSC.
 *  - net/inet/eth.c (from kernel 1.1.50) क्रम header-building info.
 *  - Alternate Linux ARCnet source by V.Shergin <vsher@sao.stavropol.su>
 *  - Textual inक्रमmation and more alternate source from Joachim Koenig
 *     <jojo@repas.de>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/delay.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_arp.h>
#समावेश <net/arp.h>
#समावेश <linux/init.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/errqueue.h>

#समावेश <linux/leds.h>

#समावेश "arcdevice.h"
#समावेश "com9026.h"

/* "do nothing" functions क्रम protocol drivers */
अटल व्योम null_rx(काष्ठा net_device *dev, पूर्णांक bufnum,
		    काष्ठा archdr *pkthdr, पूर्णांक length);
अटल पूर्णांक null_build_header(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
			     अचिन्हित लघु type, uपूर्णांक8_t daddr);
अटल पूर्णांक null_prepare_tx(काष्ठा net_device *dev, काष्ठा archdr *pkt,
			   पूर्णांक length, पूर्णांक bufnum);

अटल व्योम arcnet_rx(काष्ठा net_device *dev, पूर्णांक bufnum);

/* one ArcProto per possible proto ID.  None of the elements of
 * arc_proto_map are allowed to be शून्य; they will get set to
 * arc_proto_शेष instead.  It also must not be शून्य; अगर you would like
 * to set it to शून्य, set it to &arc_proto_null instead.
 */
काष्ठा ArcProto *arc_proto_map[256];
EXPORT_SYMBOL(arc_proto_map);

काष्ठा ArcProto *arc_proto_शेष;
EXPORT_SYMBOL(arc_proto_शेष);

काष्ठा ArcProto *arc_bcast_proto;
EXPORT_SYMBOL(arc_bcast_proto);

काष्ठा ArcProto *arc_raw_proto;
EXPORT_SYMBOL(arc_raw_proto);

अटल काष्ठा ArcProto arc_proto_null = अणु
	.suffix		= '?',
	.mtu		= XMTU,
	.is_ip          = 0,
	.rx		= null_rx,
	.build_header	= null_build_header,
	.prepare_tx	= null_prepare_tx,
	.जारी_tx    = शून्य,
	.ack_tx         = शून्य
पूर्ण;

/* Exported function prototypes */
पूर्णांक arcnet_debug = ARCNET_DEBUG;
EXPORT_SYMBOL(arcnet_debug);

/* Internal function prototypes */
अटल पूर्णांक arcnet_header(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
			 अचिन्हित लघु type, स्थिर व्योम *daddr,
			 स्थिर व्योम *saddr, अचिन्हित len);
अटल पूर्णांक go_tx(काष्ठा net_device *dev);

अटल पूर्णांक debug = ARCNET_DEBUG;
module_param(debug, पूर्णांक, 0);
MODULE_LICENSE("GPL");

अटल पूर्णांक __init arcnet_init(व्योम)
अणु
	पूर्णांक count;

	arcnet_debug = debug;

	pr_info("arcnet loaded\n");

	/* initialize the protocol map */
	arc_raw_proto = arc_proto_शेष = arc_bcast_proto = &arc_proto_null;
	क्रम (count = 0; count < 256; count++)
		arc_proto_map[count] = arc_proto_शेष;

	अगर (BUGLVL(D_DURING))
		pr_info("struct sizes: %zd %zd %zd %zd %zd\n",
			माप(काष्ठा arc_hardware),
			माप(काष्ठा arc_rfc1201),
			माप(काष्ठा arc_rfc1051),
			माप(काष्ठा arc_eth_encap),
			माप(काष्ठा archdr));

	वापस 0;
पूर्ण

अटल व्योम __निकास arcnet_निकास(व्योम)
अणु
पूर्ण

module_init(arcnet_init);
module_निकास(arcnet_निकास);

/* Dump the contents of an sk_buff */
#अगर ARCNET_DEBUG_MAX & D_SKB
व्योम arcnet_dump_skb(काष्ठा net_device *dev,
		     काष्ठा sk_buff *skb, अक्षर *desc)
अणु
	अक्षर hdr[32];

	/* dump the packet */
	snम_लिखो(hdr, माप(hdr), "%6s:%s skb->data:", dev->name, desc);
	prपूर्णांक_hex_dump(KERN_DEBUG, hdr, DUMP_PREFIX_OFFSET,
		       16, 1, skb->data, skb->len, true);
पूर्ण
EXPORT_SYMBOL(arcnet_dump_skb);
#पूर्ण_अगर

/* Dump the contents of an ARCnet buffer */
#अगर (ARCNET_DEBUG_MAX & (D_RX | D_TX))
अटल व्योम arcnet_dump_packet(काष्ठा net_device *dev, पूर्णांक bufnum,
			       अक्षर *desc, पूर्णांक take_arcnet_lock)
अणु
	काष्ठा arcnet_local *lp = netdev_priv(dev);
	पूर्णांक i, length;
	अचिन्हित दीर्घ flags = 0;
	अटल uपूर्णांक8_t buf[512];
	अक्षर hdr[32];

	/* hw.copy_from_card expects IRQ context so take the IRQ lock
	 * to keep it single thपढ़ोed
	 */
	अगर (take_arcnet_lock)
		spin_lock_irqsave(&lp->lock, flags);

	lp->hw.copy_from_card(dev, bufnum, 0, buf, 512);
	अगर (take_arcnet_lock)
		spin_unlock_irqrestore(&lp->lock, flags);

	/* अगर the offset[0] byte is nonzero, this is a 256-byte packet */
	length = (buf[2] ? 256 : 512);

	/* dump the packet */
	snम_लिखो(hdr, माप(hdr), "%6s:%s packet dump:", dev->name, desc);
	prपूर्णांक_hex_dump(KERN_DEBUG, hdr, DUMP_PREFIX_OFFSET,
		       16, 1, buf, length, true);
पूर्ण

#अन्यथा

#घोषणा arcnet_dump_packet(dev, bufnum, desc, take_arcnet_lock) करो अणु पूर्ण जबतक (0)

#पूर्ण_अगर

/* Trigger a LED event in response to a ARCNET device event */
व्योम arcnet_led_event(काष्ठा net_device *dev, क्रमागत arcnet_led_event event)
अणु
	काष्ठा arcnet_local *lp = netdev_priv(dev);
	अचिन्हित दीर्घ led_delay = 350;
	अचिन्हित दीर्घ tx_delay = 50;

	चयन (event) अणु
	हाल ARCNET_LED_EVENT_RECON:
		led_trigger_blink_oneshot(lp->recon_led_trig,
					  &led_delay, &led_delay, 0);
		अवरोध;
	हाल ARCNET_LED_EVENT_OPEN:
		led_trigger_event(lp->tx_led_trig, LED_OFF);
		led_trigger_event(lp->recon_led_trig, LED_OFF);
		अवरोध;
	हाल ARCNET_LED_EVENT_STOP:
		led_trigger_event(lp->tx_led_trig, LED_OFF);
		led_trigger_event(lp->recon_led_trig, LED_OFF);
		अवरोध;
	हाल ARCNET_LED_EVENT_TX:
		led_trigger_blink_oneshot(lp->tx_led_trig,
					  &tx_delay, &tx_delay, 0);
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(arcnet_led_event);

अटल व्योम arcnet_led_release(काष्ठा device *gendev, व्योम *res)
अणु
	काष्ठा arcnet_local *lp = netdev_priv(to_net_dev(gendev));

	led_trigger_unरेजिस्टर_simple(lp->tx_led_trig);
	led_trigger_unरेजिस्टर_simple(lp->recon_led_trig);
पूर्ण

/* Register ARCNET LED triggers क्रम a arcnet device
 *
 * This is normally called from a driver's probe function
 */
व्योम devm_arcnet_led_init(काष्ठा net_device *netdev, पूर्णांक index, पूर्णांक subid)
अणु
	काष्ठा arcnet_local *lp = netdev_priv(netdev);
	व्योम *res;

	res = devres_alloc(arcnet_led_release, 0, GFP_KERNEL);
	अगर (!res) अणु
		netdev_err(netdev, "cannot register LED triggers\n");
		वापस;
	पूर्ण

	snम_लिखो(lp->tx_led_trig_name, माप(lp->tx_led_trig_name),
		 "arc%d-%d-tx", index, subid);
	snम_लिखो(lp->recon_led_trig_name, माप(lp->recon_led_trig_name),
		 "arc%d-%d-recon", index, subid);

	led_trigger_रेजिस्टर_simple(lp->tx_led_trig_name,
				    &lp->tx_led_trig);
	led_trigger_रेजिस्टर_simple(lp->recon_led_trig_name,
				    &lp->recon_led_trig);

	devres_add(&netdev->dev, res);
पूर्ण
EXPORT_SYMBOL_GPL(devm_arcnet_led_init);

/* Unरेजिस्टर a protocol driver from the arc_proto_map.  Protocol drivers
 * are responsible क्रम रेजिस्टरing themselves, but the unरेजिस्टर routine
 * is pretty generic so we'll करो it here.
 */
व्योम arcnet_unरेजिस्टर_proto(काष्ठा ArcProto *proto)
अणु
	पूर्णांक count;

	अगर (arc_proto_शेष == proto)
		arc_proto_शेष = &arc_proto_null;
	अगर (arc_bcast_proto == proto)
		arc_bcast_proto = arc_proto_शेष;
	अगर (arc_raw_proto == proto)
		arc_raw_proto = arc_proto_शेष;

	क्रम (count = 0; count < 256; count++) अणु
		अगर (arc_proto_map[count] == proto)
			arc_proto_map[count] = arc_proto_शेष;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(arcnet_unरेजिस्टर_proto);

/* Add a buffer to the queue.  Only the पूर्णांकerrupt handler is allowed to करो
 * this, unless पूर्णांकerrupts are disabled.
 *
 * Note: we करोn't check for a full queue, since there aren't enough buffers
 * to more than fill it.
 */
अटल व्योम release_arcbuf(काष्ठा net_device *dev, पूर्णांक bufnum)
अणु
	काष्ठा arcnet_local *lp = netdev_priv(dev);
	पूर्णांक i;

	lp->buf_queue[lp->first_मुक्त_buf++] = bufnum;
	lp->first_मुक्त_buf %= 5;

	अगर (BUGLVL(D_DURING)) अणु
		arc_prपूर्णांकk(D_DURING, dev, "release_arcbuf: freed #%d; buffer queue is now: ",
			   bufnum);
		क्रम (i = lp->next_buf; i != lp->first_मुक्त_buf; i = (i + 1) % 5)
			arc_cont(D_DURING, "#%d ", lp->buf_queue[i]);
		arc_cont(D_DURING, "\n");
	पूर्ण
पूर्ण

/* Get a buffer from the queue.
 * If this वापसs -1, there are no buffers available.
 */
अटल पूर्णांक get_arcbuf(काष्ठा net_device *dev)
अणु
	काष्ठा arcnet_local *lp = netdev_priv(dev);
	पूर्णांक buf = -1, i;

	अगर (!atomic_dec_and_test(&lp->buf_lock)) अणु
		/* alपढ़ोy in this function */
		arc_prपूर्णांकk(D_NORMAL, dev, "get_arcbuf: overlap (%d)!\n",
			   lp->buf_lock.counter);
	पूर्ण अन्यथा अणु			/* we can जारी */
		अगर (lp->next_buf >= 5)
			lp->next_buf -= 5;

		अगर (lp->next_buf == lp->first_मुक्त_buf) अणु
			arc_prपूर्णांकk(D_NORMAL, dev, "get_arcbuf: BUG: no buffers are available??\n");
		पूर्ण अन्यथा अणु
			buf = lp->buf_queue[lp->next_buf++];
			lp->next_buf %= 5;
		पूर्ण
	पूर्ण

	अगर (BUGLVL(D_DURING)) अणु
		arc_prपूर्णांकk(D_DURING, dev, "get_arcbuf: got #%d; buffer queue is now: ",
			   buf);
		क्रम (i = lp->next_buf; i != lp->first_मुक्त_buf; i = (i + 1) % 5)
			arc_cont(D_DURING, "#%d ", lp->buf_queue[i]);
		arc_cont(D_DURING, "\n");
	पूर्ण

	atomic_inc(&lp->buf_lock);
	वापस buf;
पूर्ण

अटल पूर्णांक choose_mtu(व्योम)
अणु
	पूर्णांक count, mtu = 65535;

	/* choose the smallest MTU of all available encaps */
	क्रम (count = 0; count < 256; count++) अणु
		अगर (arc_proto_map[count] != &arc_proto_null &&
		    arc_proto_map[count]->mtu < mtu) अणु
			mtu = arc_proto_map[count]->mtu;
		पूर्ण
	पूर्ण

	वापस mtu == 65535 ? XMTU : mtu;
पूर्ण

अटल स्थिर काष्ठा header_ops arcnet_header_ops = अणु
	.create = arcnet_header,
पूर्ण;

अटल स्थिर काष्ठा net_device_ops arcnet_netdev_ops = अणु
	.nकरो_खोलो	= arcnet_खोलो,
	.nकरो_stop	= arcnet_बंद,
	.nकरो_start_xmit = arcnet_send_packet,
	.nकरो_tx_समयout = arcnet_समयout,
पूर्ण;

/* Setup a काष्ठा device क्रम ARCnet. */
अटल व्योम arcdev_setup(काष्ठा net_device *dev)
अणु
	dev->type = ARPHRD_ARCNET;
	dev->netdev_ops = &arcnet_netdev_ops;
	dev->header_ops = &arcnet_header_ops;
	dev->hard_header_len = माप(काष्ठा arc_hardware);
	dev->mtu = choose_mtu();

	dev->addr_len = ARCNET_ALEN;
	dev->tx_queue_len = 100;
	dev->broadcast[0] = 0x00;	/* क्रम us, broadcasts are address 0 */
	dev->watchकरोg_समयo = TX_TIMEOUT;

	/* New-style flags. */
	dev->flags = IFF_BROADCAST;
पूर्ण

अटल व्योम arcnet_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा arcnet_local *lp = from_समयr(lp, t, समयr);
	काष्ठा net_device *dev = lp->dev;

	spin_lock_irq(&lp->lock);

	अगर (!lp->reset_in_progress && !netअगर_carrier_ok(dev)) अणु
		netअगर_carrier_on(dev);
		netdev_info(dev, "link up\n");
	पूर्ण

	spin_unlock_irq(&lp->lock);
पूर्ण

अटल व्योम reset_device_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा arcnet_local *lp;
	काष्ठा net_device *dev;

	lp = container_of(work, काष्ठा arcnet_local, reset_work);
	dev = lp->dev;

	/* Do not bring the network पूर्णांकerface back up अगर an अगरकरोwn
	 * was alपढ़ोy करोne.
	 */
	अगर (!netअगर_running(dev) || !lp->reset_in_progress)
		वापस;

	rtnl_lock();

	/* Do another check, in हाल of an अगरकरोwn that was triggered in
	 * the small race winकरोw between the निकास condition above and
	 * acquiring RTNL.
	 */
	अगर (!netअगर_running(dev) || !lp->reset_in_progress)
		जाओ out;

	dev_बंद(dev);
	dev_खोलो(dev, शून्य);

out:
	rtnl_unlock();
पूर्ण

अटल व्योम arcnet_reply_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा arcnet_local *lp = from_tasklet(lp, t, reply_tasklet);

	काष्ठा sk_buff *ackskb, *skb;
	काष्ठा sock_exterr_skb *serr;
	काष्ठा sock *sk;
	पूर्णांक ret;

	local_irq_disable();
	skb = lp->outgoing.skb;
	अगर (!skb || !skb->sk) अणु
		local_irq_enable();
		वापस;
	पूर्ण

	sock_hold(skb->sk);
	sk = skb->sk;
	ackskb = skb_clone_sk(skb);
	sock_put(skb->sk);

	अगर (!ackskb) अणु
		local_irq_enable();
		वापस;
	पूर्ण

	serr = SKB_EXT_ERR(ackskb);
	स_रखो(serr, 0, माप(*serr));
	serr->ee.ee_त्रुटि_सं = ENOMSG;
	serr->ee.ee_origin = SO_EE_ORIGIN_TXSTATUS;
	serr->ee.ee_data = skb_shinfo(skb)->tskey;
	serr->ee.ee_info = lp->reply_status;

	/* finally erasing outgoing skb */
	dev_kमुक्त_skb(lp->outgoing.skb);
	lp->outgoing.skb = शून्य;

	ackskb->dev = lp->dev;

	ret = sock_queue_err_skb(sk, ackskb);
	अगर (ret)
		kमुक्त_skb(ackskb);

	local_irq_enable();
पूर्ण;

काष्ठा net_device *alloc_arcdev(स्थिर अक्षर *name)
अणु
	काष्ठा net_device *dev;

	dev = alloc_netdev(माप(काष्ठा arcnet_local),
			   name && *name ? name : "arc%d", NET_NAME_UNKNOWN,
			   arcdev_setup);
	अगर (dev) अणु
		काष्ठा arcnet_local *lp = netdev_priv(dev);

		lp->dev = dev;
		spin_lock_init(&lp->lock);
		समयr_setup(&lp->समयr, arcnet_समयr, 0);
		INIT_WORK(&lp->reset_work, reset_device_work);
	पूर्ण

	वापस dev;
पूर्ण
EXPORT_SYMBOL(alloc_arcdev);

व्योम मुक्त_arcdev(काष्ठा net_device *dev)
अणु
	काष्ठा arcnet_local *lp = netdev_priv(dev);

	/* Do not cancel this at ->nकरो_बंद(), as the workqueue itself
	 * indirectly calls the अगरकरोwn path through dev_बंद().
	 */
	cancel_work_sync(&lp->reset_work);
	मुक्त_netdev(dev);
पूर्ण
EXPORT_SYMBOL(मुक्त_arcdev);

/* Open/initialize the board.  This is called someसमय after booting when
 * the 'ifconfig' program is run.
 *
 * This routine should set everything up anew at each खोलो, even रेजिस्टरs
 * that "should" only need to be set once at boot, so that there is
 * non-reboot way to recover अगर something goes wrong.
 */
पूर्णांक arcnet_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा arcnet_local *lp = netdev_priv(dev);
	पूर्णांक count, newmtu, error;

	arc_prपूर्णांकk(D_INIT, dev, "opened.");

	अगर (!try_module_get(lp->hw.owner))
		वापस -ENODEV;

	अगर (BUGLVL(D_PROTO)) अणु
		arc_prपूर्णांकk(D_PROTO, dev, "protocol map (default is '%c'): ",
			   arc_proto_शेष->suffix);
		क्रम (count = 0; count < 256; count++)
			arc_cont(D_PROTO, "%c", arc_proto_map[count]->suffix);
		arc_cont(D_PROTO, "\n");
	पूर्ण

	tasklet_setup(&lp->reply_tasklet, arcnet_reply_tasklet);

	arc_prपूर्णांकk(D_INIT, dev, "arcnet_open: resetting card.\n");

	/* try to put the card in a defined state - अगर it fails the first
	 * समय, actually reset it.
	 */
	error = -ENODEV;
	अगर (lp->hw.reset(dev, 0) && lp->hw.reset(dev, 1))
		जाओ out_module_put;

	newmtu = choose_mtu();
	अगर (newmtu < dev->mtu)
		dev->mtu = newmtu;

	arc_prपूर्णांकk(D_INIT, dev, "arcnet_open: mtu: %d.\n", dev->mtu);

	/* स्वतःdetect the encapsulation क्रम each host. */
	स_रखो(lp->शेष_proto, 0, माप(lp->शेष_proto));

	/* the broadcast address is special - use the 'bcast' protocol */
	क्रम (count = 0; count < 256; count++) अणु
		अगर (arc_proto_map[count] == arc_bcast_proto) अणु
			lp->शेष_proto[0] = count;
			अवरोध;
		पूर्ण
	पूर्ण

	/* initialize buffers */
	atomic_set(&lp->buf_lock, 1);

	lp->next_buf = lp->first_मुक्त_buf = 0;
	release_arcbuf(dev, 0);
	release_arcbuf(dev, 1);
	release_arcbuf(dev, 2);
	release_arcbuf(dev, 3);
	lp->cur_tx = lp->next_tx = -1;
	lp->cur_rx = -1;

	lp->rfc1201.sequence = 1;

	/* bring up the hardware driver */
	अगर (lp->hw.खोलो)
		lp->hw.खोलो(dev);

	अगर (dev->dev_addr[0] == 0)
		arc_prपूर्णांकk(D_NORMAL, dev, "WARNING!  Station address 00 is reserved for broadcasts!\n");
	अन्यथा अगर (dev->dev_addr[0] == 255)
		arc_prपूर्णांकk(D_NORMAL, dev, "WARNING!  Station address FF may confuse DOS networking programs!\n");

	arc_prपूर्णांकk(D_DEBUG, dev, "%s: %d: %s\n", __खाता__, __LINE__, __func__);
	अगर (lp->hw.status(dev) & RESETflag) अणु
		arc_prपूर्णांकk(D_DEBUG, dev, "%s: %d: %s\n",
			   __खाता__, __LINE__, __func__);
		lp->hw.command(dev, CFLAGScmd | RESETclear);
	पूर्ण

	arc_prपूर्णांकk(D_DEBUG, dev, "%s: %d: %s\n", __खाता__, __LINE__, __func__);
	/* make sure we're ready to receive IRQ's. */
	lp->hw.पूर्णांकmask(dev, 0);
	udelay(1);		/* give it समय to set the mask beक्रमe
				 * we reset it again. (may not even be
				 * necessary)
				 */
	arc_prपूर्णांकk(D_DEBUG, dev, "%s: %d: %s\n", __खाता__, __LINE__, __func__);
	lp->पूर्णांकmask = NORXflag | RECONflag;
	lp->hw.पूर्णांकmask(dev, lp->पूर्णांकmask);
	arc_prपूर्णांकk(D_DEBUG, dev, "%s: %d: %s\n", __खाता__, __LINE__, __func__);

	netअगर_carrier_off(dev);
	netअगर_start_queue(dev);
	mod_समयr(&lp->समयr, jअगरfies + msecs_to_jअगरfies(1000));

	arcnet_led_event(dev, ARCNET_LED_EVENT_OPEN);
	वापस 0;

 out_module_put:
	module_put(lp->hw.owner);
	वापस error;
पूर्ण
EXPORT_SYMBOL(arcnet_खोलो);

/* The inverse routine to arcnet_खोलो - shuts करोwn the card. */
पूर्णांक arcnet_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा arcnet_local *lp = netdev_priv(dev);

	arcnet_led_event(dev, ARCNET_LED_EVENT_STOP);
	del_समयr_sync(&lp->समयr);

	netअगर_stop_queue(dev);
	netअगर_carrier_off(dev);

	tasklet_समाप्त(&lp->reply_tasklet);

	/* flush TX and disable RX */
	lp->hw.पूर्णांकmask(dev, 0);
	lp->hw.command(dev, NOTXcmd);	/* stop transmit */
	lp->hw.command(dev, NORXcmd);	/* disable receive */
	mdelay(1);

	/* shut करोwn the card */
	lp->hw.बंद(dev);

	/* reset counters */
	lp->reset_in_progress = 0;

	module_put(lp->hw.owner);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(arcnet_बंद);

अटल पूर्णांक arcnet_header(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
			 अचिन्हित लघु type, स्थिर व्योम *daddr,
			 स्थिर व्योम *saddr, अचिन्हित len)
अणु
	स्थिर काष्ठा arcnet_local *lp = netdev_priv(dev);
	uपूर्णांक8_t _daddr, proto_num;
	काष्ठा ArcProto *proto;

	arc_prपूर्णांकk(D_DURING, dev,
		   "create header from %d to %d; protocol %d (%Xh); size %u.\n",
		   saddr ? *(uपूर्णांक8_t *)saddr : -1,
		   daddr ? *(uपूर्णांक8_t *)daddr : -1,
		   type, type, len);

	अगर (skb->len != 0 && len != skb->len)
		arc_prपूर्णांकk(D_NORMAL, dev, "arcnet_header: Yikes!  skb->len(%d) != len(%d)!\n",
			   skb->len, len);

	/* Type is host order - ? */
	अगर (type == ETH_P_ARCNET) अणु
		proto = arc_raw_proto;
		arc_prपूर्णांकk(D_DEBUG, dev, "arc_raw_proto used. proto='%c'\n",
			   proto->suffix);
		_daddr = daddr ? *(uपूर्णांक8_t *)daddr : 0;
	पूर्ण अन्यथा अगर (!daddr) अणु
		/* अगर the dest addr isn't provided, we can't choose an
		 * encapsulation!  Store the packet type (eg. ETH_P_IP)
		 * क्रम now, and we'll push on a real header when we करो
		 * rebuild_header.
		 */
		*(uपूर्णांक16_t *)skb_push(skb, 2) = type;
		/* XXX: Why not use skb->mac_len? */
		अगर (skb->network_header - skb->mac_header != 2)
			arc_prपूर्णांकk(D_NORMAL, dev, "arcnet_header: Yikes!  diff (%u) is not 2!\n",
				   skb->network_header - skb->mac_header);
		वापस -2;	/* वापस error -- can't transmit yet! */
	पूर्ण अन्यथा अणु
		/* otherwise, we can just add the header as usual. */
		_daddr = *(uपूर्णांक8_t *)daddr;
		proto_num = lp->शेष_proto[_daddr];
		proto = arc_proto_map[proto_num];
		arc_prपूर्णांकk(D_DURING, dev, "building header for %02Xh using protocol '%c'\n",
			   proto_num, proto->suffix);
		अगर (proto == &arc_proto_null && arc_bcast_proto != proto) अणु
			arc_prपूर्णांकk(D_DURING, dev, "actually, let's use '%c' instead.\n",
				   arc_bcast_proto->suffix);
			proto = arc_bcast_proto;
		पूर्ण
	पूर्ण
	वापस proto->build_header(skb, dev, type, _daddr);
पूर्ण

/* Called by the kernel in order to transmit a packet. */
netdev_tx_t arcnet_send_packet(काष्ठा sk_buff *skb,
			       काष्ठा net_device *dev)
अणु
	काष्ठा arcnet_local *lp = netdev_priv(dev);
	काष्ठा archdr *pkt;
	काष्ठा arc_rfc1201 *soft;
	काष्ठा ArcProto *proto;
	पूर्णांक txbuf;
	अचिन्हित दीर्घ flags;
	पूर्णांक retval;

	arc_prपूर्णांकk(D_DURING, dev,
		   "transmit requested (status=%Xh, txbufs=%d/%d, len=%d, protocol %x)\n",
		   lp->hw.status(dev), lp->cur_tx, lp->next_tx, skb->len, skb->protocol);

	pkt = (काष्ठा archdr *)skb->data;
	soft = &pkt->soft.rfc1201;
	proto = arc_proto_map[soft->proto];

	arc_prपूर्णांकk(D_SKB_SIZE, dev, "skb: transmitting %d bytes to %02X\n",
		   skb->len, pkt->hard.dest);
	अगर (BUGLVL(D_SKB))
		arcnet_dump_skb(dev, skb, "tx");

	/* fits in one packet? */
	अगर (skb->len - ARC_HDR_SIZE > XMTU && !proto->जारी_tx) अणु
		arc_prपूर्णांकk(D_NORMAL, dev, "fixme: packet too large: compensating badly!\n");
		dev_kमुक्त_skb(skb);
		वापस NETDEV_TX_OK;	/* करोn't try again */
	पूर्ण

	/* We're busy transmitting a packet... */
	netअगर_stop_queue(dev);

	spin_lock_irqsave(&lp->lock, flags);
	lp->hw.पूर्णांकmask(dev, 0);
	अगर (lp->next_tx == -1)
		txbuf = get_arcbuf(dev);
	अन्यथा
		txbuf = -1;

	अगर (txbuf != -1) अणु
		lp->outgoing.skb = skb;
		अगर (proto->prepare_tx(dev, pkt, skb->len, txbuf) &&
		    !proto->ack_tx) अणु
			/* करोne right away and we करोn't want to acknowledge
			 *  the package later - क्रमget about it now
			 */
			dev->stats.tx_bytes += skb->len;
		पूर्ण अन्यथा अणु
			/* करो it the 'split' way */
			lp->outgoing.proto = proto;
			lp->outgoing.skb = skb;
			lp->outgoing.pkt = pkt;

			अगर (proto->जारी_tx &&
			    proto->जारी_tx(dev, txbuf)) अणु
				arc_prपूर्णांकk(D_NORMAL, dev,
					   "bug! continue_tx finished the first time! (proto='%c')\n",
					   proto->suffix);
			पूर्ण
		पूर्ण
		retval = NETDEV_TX_OK;
		lp->next_tx = txbuf;
	पूर्ण अन्यथा अणु
		retval = NETDEV_TX_BUSY;
	पूर्ण

	arc_prपूर्णांकk(D_DEBUG, dev, "%s: %d: %s, status: %x\n",
		   __खाता__, __LINE__, __func__, lp->hw.status(dev));
	/* make sure we didn't ignore a TX IRQ जबतक we were in here */
	lp->hw.पूर्णांकmask(dev, 0);

	arc_prपूर्णांकk(D_DEBUG, dev, "%s: %d: %s\n", __खाता__, __LINE__, __func__);
	lp->पूर्णांकmask |= TXFREEflag | EXCNAKflag;
	lp->hw.पूर्णांकmask(dev, lp->पूर्णांकmask);
	arc_prपूर्णांकk(D_DEBUG, dev, "%s: %d: %s, status: %x\n",
		   __खाता__, __LINE__, __func__, lp->hw.status(dev));

	arcnet_led_event(dev, ARCNET_LED_EVENT_TX);

	spin_unlock_irqrestore(&lp->lock, flags);
	वापस retval;		/* no need to try again */
पूर्ण
EXPORT_SYMBOL(arcnet_send_packet);

/* Actually start transmitting a packet that was loaded पूर्णांकo a buffer
 * by prepare_tx.  This should _only_ be called by the पूर्णांकerrupt handler.
 */
अटल पूर्णांक go_tx(काष्ठा net_device *dev)
अणु
	काष्ठा arcnet_local *lp = netdev_priv(dev);

	arc_prपूर्णांकk(D_DURING, dev, "go_tx: status=%Xh, intmask=%Xh, next_tx=%d, cur_tx=%d\n",
		   lp->hw.status(dev), lp->पूर्णांकmask, lp->next_tx, lp->cur_tx);

	अगर (lp->cur_tx != -1 || lp->next_tx == -1)
		वापस 0;

	अगर (BUGLVL(D_TX))
		arcnet_dump_packet(dev, lp->next_tx, "go_tx", 0);

	lp->cur_tx = lp->next_tx;
	lp->next_tx = -1;

	/* start sending */
	lp->hw.command(dev, TXcmd | (lp->cur_tx << 3));

	dev->stats.tx_packets++;
	lp->lasttrans_dest = lp->lastload_dest;
	lp->lastload_dest = 0;
	lp->excnak_pending = 0;
	lp->पूर्णांकmask |= TXFREEflag | EXCNAKflag;

	वापस 1;
पूर्ण

/* Called by the kernel when transmit बार out */
व्योम arcnet_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा arcnet_local *lp = netdev_priv(dev);
	पूर्णांक status = lp->hw.status(dev);
	अक्षर *msg;

	spin_lock_irqsave(&lp->lock, flags);
	अगर (status & TXFREEflag) अणु	/* transmit _DID_ finish */
		msg = " - missed IRQ?";
	पूर्ण अन्यथा अणु
		msg = "";
		dev->stats.tx_पातed_errors++;
		lp->समयd_out = 1;
		lp->hw.command(dev, NOTXcmd | (lp->cur_tx << 3));
	पूर्ण
	dev->stats.tx_errors++;

	/* make sure we didn't miss a TX or a EXC NAK IRQ */
	lp->hw.पूर्णांकmask(dev, 0);
	lp->पूर्णांकmask |= TXFREEflag | EXCNAKflag;
	lp->hw.पूर्णांकmask(dev, lp->पूर्णांकmask);

	spin_unlock_irqrestore(&lp->lock, flags);

	अगर (समय_after(jअगरfies, lp->last_समयout + 10 * HZ)) अणु
		arc_prपूर्णांकk(D_EXTRA, dev, "tx timed out%s (status=%Xh, intmask=%Xh, dest=%02Xh)\n",
			   msg, status, lp->पूर्णांकmask, lp->lasttrans_dest);
		lp->last_समयout = jअगरfies;
	पूर्ण

	अगर (lp->cur_tx == -1)
		netअगर_wake_queue(dev);
पूर्ण
EXPORT_SYMBOL(arcnet_समयout);

/* The typical workload of the driver: Handle the network पूर्णांकerface
 * पूर्णांकerrupts. Establish which device needs attention, and call the correct
 * chipset पूर्णांकerrupt handler.
 */
irqवापस_t arcnet_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = dev_id;
	काष्ठा arcnet_local *lp;
	पूर्णांक recbuf, status, diagstatus, didsomething, boguscount;
	अचिन्हित दीर्घ flags;
	पूर्णांक retval = IRQ_NONE;

	arc_prपूर्णांकk(D_DURING, dev, "\n");

	arc_prपूर्णांकk(D_DURING, dev, "in arcnet_interrupt\n");

	lp = netdev_priv(dev);
	BUG_ON(!lp);

	spin_lock_irqsave(&lp->lock, flags);

	अगर (lp->reset_in_progress)
		जाओ out;

	/* RESET flag was enabled - अगर device is not running, we must
	 * clear it right away (but nothing अन्यथा).
	 */
	अगर (!netअगर_running(dev)) अणु
		अगर (lp->hw.status(dev) & RESETflag)
			lp->hw.command(dev, CFLAGScmd | RESETclear);
		lp->hw.पूर्णांकmask(dev, 0);
		spin_unlock_irqrestore(&lp->lock, flags);
		वापस retval;
	पूर्ण

	arc_prपूर्णांकk(D_DURING, dev, "in arcnet_inthandler (status=%Xh, intmask=%Xh)\n",
		   lp->hw.status(dev), lp->पूर्णांकmask);

	boguscount = 5;
	करो अणु
		status = lp->hw.status(dev);
		diagstatus = (status >> 8) & 0xFF;

		arc_prपूर्णांकk(D_DEBUG, dev, "%s: %d: %s: status=%x\n",
			   __खाता__, __LINE__, __func__, status);
		didsomething = 0;

		/* RESET flag was enabled - card is resetting and अगर RX is
		 * disabled, it's NOT because we just got a packet.
		 *
		 * The card is in an undefined state.
		 * Clear it out and start over.
		 */
		अगर (status & RESETflag) अणु
			arc_prपूर्णांकk(D_NORMAL, dev, "spurious reset (status=%Xh)\n",
				   status);

			lp->reset_in_progress = 1;
			netअगर_stop_queue(dev);
			netअगर_carrier_off(dev);
			schedule_work(&lp->reset_work);

			/* get out of the पूर्णांकerrupt handler! */
			जाओ out;
		पूर्ण
		/* RX is inhibited - we must have received something.
		 * Prepare to receive पूर्णांकo the next buffer.
		 *
		 * We करोn't actually copy the received packet from the card
		 * until after the transmit handler runs (and possibly
		 * launches the next tx); this should improve latency slightly
		 * अगर we get both types of पूर्णांकerrupts at once.
		 */
		recbuf = -1;
		अगर (status & lp->पूर्णांकmask & NORXflag) अणु
			recbuf = lp->cur_rx;
			arc_prपूर्णांकk(D_DURING, dev, "Buffer #%d: receive irq (status=%Xh)\n",
				   recbuf, status);

			lp->cur_rx = get_arcbuf(dev);
			अगर (lp->cur_rx != -1) अणु
				arc_prपूर्णांकk(D_DURING, dev, "enabling receive to buffer #%d\n",
					   lp->cur_rx);
				lp->hw.command(dev, RXcmd | (lp->cur_rx << 3) | RXbcasts);
			पूर्ण
			didsomething++;
		पूर्ण

		अगर ((diagstatus & EXCNAKflag)) अणु
			arc_prपूर्णांकk(D_DURING, dev, "EXCNAK IRQ (diagstat=%Xh)\n",
				   diagstatus);

			lp->hw.command(dev, NOTXcmd);      /* disable transmit */
			lp->excnak_pending = 1;

			lp->hw.command(dev, EXCNAKclear);
			lp->पूर्णांकmask &= ~(EXCNAKflag);
			didsomething++;
		पूर्ण

		/* a transmit finished, and we're पूर्णांकerested in it. */
		अगर ((status & lp->पूर्णांकmask & TXFREEflag) || lp->समयd_out) अणु
			पूर्णांक ackstatus;
			lp->पूर्णांकmask &= ~(TXFREEflag | EXCNAKflag);

			अगर (status & TXACKflag)
				ackstatus = 2;
			अन्यथा अगर (lp->excnak_pending)
				ackstatus = 1;
			अन्यथा
				ackstatus = 0;

			arc_prपूर्णांकk(D_DURING, dev, "TX IRQ (stat=%Xh)\n",
				   status);

			अगर (lp->cur_tx != -1 && !lp->समयd_out) अणु
				अगर (!(status & TXACKflag)) अणु
					अगर (lp->lasttrans_dest != 0) अणु
						arc_prपूर्णांकk(D_EXTRA, dev,
							   "transmit was not acknowledged! (status=%Xh, dest=%02Xh)\n",
							   status,
							   lp->lasttrans_dest);
						dev->stats.tx_errors++;
						dev->stats.tx_carrier_errors++;
					पूर्ण अन्यथा अणु
						arc_prपूर्णांकk(D_DURING, dev,
							   "broadcast was not acknowledged; that's normal (status=%Xh, dest=%02Xh)\n",
							   status,
							   lp->lasttrans_dest);
					पूर्ण
				पूर्ण

				अगर (lp->outgoing.proto &&
				    lp->outgoing.proto->ack_tx) अणु
					lp->outgoing.proto
						->ack_tx(dev, ackstatus);
				पूर्ण
				lp->reply_status = ackstatus;
				tasklet_hi_schedule(&lp->reply_tasklet);
			पूर्ण
			अगर (lp->cur_tx != -1)
				release_arcbuf(dev, lp->cur_tx);

			lp->cur_tx = -1;
			lp->समयd_out = 0;
			didsomething++;

			/* send another packet अगर there is one */
			go_tx(dev);

			/* जारी a split packet, अगर any */
			अगर (lp->outgoing.proto &&
			    lp->outgoing.proto->जारी_tx) अणु
				पूर्णांक txbuf = get_arcbuf(dev);

				अगर (txbuf != -1) अणु
					अगर (lp->outgoing.proto->जारी_tx(dev, txbuf)) अणु
						/* that was the last segment */
						dev->stats.tx_bytes += lp->outgoing.skb->len;
						अगर (!lp->outgoing.proto->ack_tx) अणु
							dev_kमुक्त_skb_irq(lp->outgoing.skb);
							lp->outgoing.proto = शून्य;
						पूर्ण
					पूर्ण
					lp->next_tx = txbuf;
				पूर्ण
			पूर्ण
			/* inक्रमm upper layers of idleness, अगर necessary */
			अगर (lp->cur_tx == -1)
				netअगर_wake_queue(dev);
		पूर्ण
		/* now process the received packet, अगर any */
		अगर (recbuf != -1) अणु
			अगर (BUGLVL(D_RX))
				arcnet_dump_packet(dev, recbuf, "rx irq", 0);

			arcnet_rx(dev, recbuf);
			release_arcbuf(dev, recbuf);

			didsomething++;
		पूर्ण
		अगर (status & lp->पूर्णांकmask & RECONflag) अणु
			lp->hw.command(dev, CFLAGScmd | CONFIGclear);
			dev->stats.tx_carrier_errors++;

			arc_prपूर्णांकk(D_RECON, dev, "Network reconfiguration detected (status=%Xh)\n",
				   status);
			अगर (netअगर_carrier_ok(dev)) अणु
				netअगर_carrier_off(dev);
				netdev_info(dev, "link down\n");
			पूर्ण
			mod_समयr(&lp->समयr, jअगरfies + msecs_to_jअगरfies(1000));

			arcnet_led_event(dev, ARCNET_LED_EVENT_RECON);
			/* MYRECON bit is at bit 7 of diagstatus */
			अगर (diagstatus & 0x80)
				arc_prपूर्णांकk(D_RECON, dev, "Put out that recon myself\n");

			/* is the RECON info empty or old? */
			अगर (!lp->first_recon || !lp->last_recon ||
			    समय_after(jअगरfies, lp->last_recon + HZ * 10)) अणु
				अगर (lp->network_करोwn)
					arc_prपूर्णांकk(D_NORMAL, dev, "reconfiguration detected: cabling restored?\n");
				lp->first_recon = lp->last_recon = jअगरfies;
				lp->num_recons = lp->network_करोwn = 0;

				arc_prपूर्णांकk(D_DURING, dev, "recon: clearing counters.\n");
			पूर्ण अन्यथा अणु	/* add to current RECON counter */
				lp->last_recon = jअगरfies;
				lp->num_recons++;

				arc_prपूर्णांकk(D_DURING, dev, "recon: counter=%d, time=%lds, net=%d\n",
					   lp->num_recons,
					   (lp->last_recon - lp->first_recon) / HZ,
					   lp->network_करोwn);

				/* अगर network is marked up;
				 * and first_recon and last_recon are 60+ apart;
				 * and the average no. of recons counted is
				 *    > RECON_THRESHOLD/min;
				 * then prपूर्णांक a warning message.
				 */
				अगर (!lp->network_करोwn &&
				    (lp->last_recon - lp->first_recon) <= HZ * 60 &&
				    lp->num_recons >= RECON_THRESHOLD) अणु
					lp->network_करोwn = 1;
					arc_prपूर्णांकk(D_NORMAL, dev, "many reconfigurations detected: cabling problem?\n");
				पूर्ण अन्यथा अगर (!lp->network_करोwn &&
					   lp->last_recon - lp->first_recon > HZ * 60) अणु
					/* reset counters अगर we've gone क्रम
					 *  over a minute.
					 */
					lp->first_recon = lp->last_recon;
					lp->num_recons = 1;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अगर (lp->network_करोwn &&
			   समय_after(jअगरfies, lp->last_recon + HZ * 10)) अणु
			अगर (lp->network_करोwn)
				arc_prपूर्णांकk(D_NORMAL, dev, "cabling restored?\n");
			lp->first_recon = lp->last_recon = 0;
			lp->num_recons = lp->network_करोwn = 0;

			arc_prपूर्णांकk(D_DURING, dev, "not recon: clearing counters anyway.\n");
			netअगर_carrier_on(dev);
		पूर्ण

		अगर (didsomething)
			retval |= IRQ_HANDLED;
	पूर्ण जबतक (--boguscount && didsomething);

	arc_prपूर्णांकk(D_DURING, dev, "arcnet_interrupt complete (status=%Xh, count=%d)\n",
		   lp->hw.status(dev), boguscount);
	arc_prपूर्णांकk(D_DURING, dev, "\n");

	lp->hw.पूर्णांकmask(dev, 0);
	udelay(1);
	lp->hw.पूर्णांकmask(dev, lp->पूर्णांकmask);

out:
	spin_unlock_irqrestore(&lp->lock, flags);
	वापस retval;
पूर्ण
EXPORT_SYMBOL(arcnet_पूर्णांकerrupt);

/* This is a generic packet receiver that calls arcnet??_rx depending on the
 * protocol ID found.
 */
अटल व्योम arcnet_rx(काष्ठा net_device *dev, पूर्णांक bufnum)
अणु
	काष्ठा arcnet_local *lp = netdev_priv(dev);
	जोड़ अणु
		काष्ठा archdr pkt;
		अक्षर buf[512];
	पूर्ण rxdata;
	काष्ठा arc_rfc1201 *soft;
	पूर्णांक length, ofs;

	soft = &rxdata.pkt.soft.rfc1201;

	lp->hw.copy_from_card(dev, bufnum, 0, &rxdata.pkt, ARC_HDR_SIZE);
	अगर (rxdata.pkt.hard.offset[0]) अणु
		ofs = rxdata.pkt.hard.offset[0];
		length = 256 - ofs;
	पूर्ण अन्यथा अणु
		ofs = rxdata.pkt.hard.offset[1];
		length = 512 - ofs;
	पूर्ण

	/* get the full header, अगर possible */
	अगर (माप(rxdata.pkt.soft) <= length) अणु
		lp->hw.copy_from_card(dev, bufnum, ofs, soft, माप(rxdata.pkt.soft));
	पूर्ण अन्यथा अणु
		स_रखो(&rxdata.pkt.soft, 0, माप(rxdata.pkt.soft));
		lp->hw.copy_from_card(dev, bufnum, ofs, soft, length);
	पूर्ण

	arc_prपूर्णांकk(D_DURING, dev, "Buffer #%d: received packet from %02Xh to %02Xh (%d+4 bytes)\n",
		   bufnum, rxdata.pkt.hard.source, rxdata.pkt.hard.dest, length);

	dev->stats.rx_packets++;
	dev->stats.rx_bytes += length + ARC_HDR_SIZE;

	/* call the right receiver क्रम the protocol */
	अगर (arc_proto_map[soft->proto]->is_ip) अणु
		अगर (BUGLVL(D_PROTO)) अणु
			काष्ठा ArcProto
			*oldp = arc_proto_map[lp->शेष_proto[rxdata.pkt.hard.source]],
			*newp = arc_proto_map[soft->proto];

			अगर (oldp != newp) अणु
				arc_prपूर्णांकk(D_PROTO, dev,
					   "got protocol %02Xh; encap for host %02Xh is now '%c' (was '%c')\n",
					   soft->proto, rxdata.pkt.hard.source,
					   newp->suffix, oldp->suffix);
			पूर्ण
		पूर्ण

		/* broadcasts will always be करोne with the last-used encap. */
		lp->शेष_proto[0] = soft->proto;

		/* in striking contrast, the following isn't a hack. */
		lp->शेष_proto[rxdata.pkt.hard.source] = soft->proto;
	पूर्ण
	/* call the protocol-specअगरic receiver. */
	arc_proto_map[soft->proto]->rx(dev, bufnum, &rxdata.pkt, length);
पूर्ण

अटल व्योम null_rx(काष्ठा net_device *dev, पूर्णांक bufnum,
		    काष्ठा archdr *pkthdr, पूर्णांक length)
अणु
	arc_prपूर्णांकk(D_PROTO, dev,
		   "rx: don't know how to deal with proto %02Xh from host %02Xh.\n",
		   pkthdr->soft.rfc1201.proto, pkthdr->hard.source);
पूर्ण

अटल पूर्णांक null_build_header(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
			     अचिन्हित लघु type, uपूर्णांक8_t daddr)
अणु
	काष्ठा arcnet_local *lp = netdev_priv(dev);

	arc_prपूर्णांकk(D_PROTO, dev,
		   "tx: can't build header for encap %02Xh; load a protocol driver.\n",
		   lp->शेष_proto[daddr]);

	/* always fails */
	वापस 0;
पूर्ण

/* the "do nothing" prepare_tx function warns that there's nothing to करो. */
अटल पूर्णांक null_prepare_tx(काष्ठा net_device *dev, काष्ठा archdr *pkt,
			   पूर्णांक length, पूर्णांक bufnum)
अणु
	काष्ठा arcnet_local *lp = netdev_priv(dev);
	काष्ठा arc_hardware newpkt;

	arc_prपूर्णांकk(D_PROTO, dev, "tx: no encap for this host; load a protocol driver.\n");

	/* send a packet to myself -- will never get received, of course */
	newpkt.source = newpkt.dest = dev->dev_addr[0];

	/* only one byte of actual data (and it's अक्रमom) */
	newpkt.offset[0] = 0xFF;

	lp->hw.copy_to_card(dev, bufnum, 0, &newpkt, ARC_HDR_SIZE);

	वापस 1;		/* करोne */
पूर्ण
