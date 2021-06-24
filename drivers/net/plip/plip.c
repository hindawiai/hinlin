<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* $Id: plip.c,v 1.3.6.2 1997/04/16 15:07:56 phil Exp $ */
/* PLIP: A parallel port "network" driver क्रम Linux. */
/* This driver is क्रम parallel port with 5-bit cable (LapLink (R) cable). */
/*
 * Authors:	Donald Becker <becker@scyld.com>
 *		Tommy Thorn <thorn@daimi.aau.dk>
 *		Tanabe Hiroyasu <hiro@sanpo.t.u-tokyo.ac.jp>
 *		Alan Cox <gw4pts@gw4pts.ampr.org>
 *		Peter Bauer <100136.3530@compuserve.com>
 *		Niibe Yutaka <gniibe@mri.co.jp>
 *		Nimrod Zimerman <zimerman@mailandnews.com>
 *
 * Enhancements:
 *		Modularization and अगरreq/अगरmap support by Alan Cox.
 *		Rewritten by Niibe Yutaka.
 *		parport-sharing awareness code by Philip Blundell.
 *		SMP locking by Niibe Yutaka.
 *		Support क्रम parallel ports with no IRQ (poll mode),
 *		Modअगरications to use the parallel port API
 *		by Nimrod Zimerman.
 *
 * Fixes:
 *		Niibe Yutaka
 *		  - Module initialization.
 *		  - MTU fix.
 *		  - Make sure other end is OK, beक्रमe sending a packet.
 *		  - Fix immediate समयr problem.
 *
 *		Al Viro
 *		  - Changed अणुenable,disableपूर्ण_irq handling to make it work
 *		    with new ("stack") semantics.
 */

/*
 * Original version and the name 'PLIP' from Donald Becker <becker@scyld.com>
 * inspired by Russ Nelson's parallel port packet driver.
 *
 * NOTE:
 *     Tanabe Hiroyasu had changed the protocol, and it was in Linux v1.0.
 *     Because of the necessity to communicate to DOS machines with the
 *     Crynwr packet driver, Peter Bauer changed the protocol again
 *     back to original protocol.
 *
 *     This version follows original PLIP protocol.
 *     So, this PLIP can't communicate the PLIP of Linux v1.0.
 */

/*
 *     To use with DOS box, please करो (Turn on ARP चयन):
 *	# अगरconfig plip[0-2] arp
 */
अटल स्थिर अक्षर version[] = "NET3 PLIP version 2.4-parport gniibe@mri.co.jp\n";

/*
  Sources:
	Ideas and protocols came from Russ Nelson's <nelson@crynwr.com>
	"parallel.asm" parallel port packet driver.

  The "Crynwr" parallel port standard specअगरies the following protocol:
    Trigger by sending nibble '0x8' (this causes पूर्णांकerrupt on other end)
    count-low octet
    count-high octet
    ... data octets
    checksum octet
  Each octet is sent as <रुको क्रम rx. '0x1?'> <send 0x10+(octet&0x0F)>
			<रुको क्रम rx. '0x0?'> <send 0x00+((octet>>4)&0x0F)>

  The packet is encapsulated as अगर it were ethernet.

  The cable used is a de facto standard parallel null cable -- sold as
  a "LapLink" cable by various places.  You'll need a 12-conductor cable to
  make one yourself.  The wiring is:
    SLCTIN	17 - 17
    GROUND	25 - 25
    D0->ERROR	2 - 15		15 - 2
    D1->SLCT	3 - 13		13 - 3
    D2->PAPOUT	4 - 12		12 - 4
    D3->ACK	5 - 10		10 - 5
    D4->BUSY	6 - 11		11 - 6
  Do not connect the other pins.  They are
    D5,D6,D7 are 7,8,9
    STROBE is 1, FEED is 14, INIT is 16
    extra grounds are 18,19,20,21,22,23,24
*/

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/in.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/अगर_plip.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/completion.h>
#समावेश <linux/parport.h>
#समावेश <linux/bitops.h>

#समावेश <net/neighbour.h>

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/byteorder.h>

/* Maximum number of devices to support. */
#घोषणा PLIP_MAX  8

/* Use 0 क्रम production, 1 क्रम verअगरication, >2 क्रम debug */
#अगर_अघोषित NET_DEBUG
#घोषणा NET_DEBUG 1
#पूर्ण_अगर
अटल स्थिर अचिन्हित पूर्णांक net_debug = NET_DEBUG;

#घोषणा ENABLE(irq)  अगर (irq != -1) enable_irq(irq)
#घोषणा DISABLE(irq) अगर (irq != -1) disable_irq(irq)

/* In micro second */
#घोषणा PLIP_DELAY_UNIT		   1

/* Connection समय out = PLIP_TRIGGER_WAIT * PLIP_DELAY_UNIT usec */
#घोषणा PLIP_TRIGGER_WAIT	 500

/* Nibble समय out = PLIP_NIBBLE_WAIT * PLIP_DELAY_UNIT usec */
#घोषणा PLIP_NIBBLE_WAIT        3000

/* Bottom halves */
अटल व्योम plip_kick_bh(काष्ठा work_काष्ठा *work);
अटल व्योम plip_bh(काष्ठा work_काष्ठा *work);
अटल व्योम plip_समयr_bh(काष्ठा work_काष्ठा *work);

/* Interrupt handler */
अटल व्योम plip_पूर्णांकerrupt(व्योम *dev_id);

/* Functions क्रम DEV methods */
अटल netdev_tx_t plip_tx_packet(काष्ठा sk_buff *skb, काष्ठा net_device *dev);
अटल पूर्णांक plip_hard_header(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
                            अचिन्हित लघु type, स्थिर व्योम *daddr,
			    स्थिर व्योम *saddr, अचिन्हित len);
अटल पूर्णांक plip_hard_header_cache(स्थिर काष्ठा neighbour *neigh,
                                  काष्ठा hh_cache *hh, __be16 type);
अटल पूर्णांक plip_खोलो(काष्ठा net_device *dev);
अटल पूर्णांक plip_बंद(काष्ठा net_device *dev);
अटल पूर्णांक plip_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd);
अटल पूर्णांक plip_preempt(व्योम *handle);
अटल व्योम plip_wakeup(व्योम *handle);

क्रमागत plip_connection_state अणु
	PLIP_CN_NONE=0,
	PLIP_CN_RECEIVE,
	PLIP_CN_SEND,
	PLIP_CN_CLOSING,
	PLIP_CN_ERROR
पूर्ण;

क्रमागत plip_packet_state अणु
	PLIP_PK_DONE=0,
	PLIP_PK_TRIGGER,
	PLIP_PK_LENGTH_LSB,
	PLIP_PK_LENGTH_MSB,
	PLIP_PK_DATA,
	PLIP_PK_CHECKSUM
पूर्ण;

क्रमागत plip_nibble_state अणु
	PLIP_NB_BEGIN,
	PLIP_NB_1,
	PLIP_NB_2,
पूर्ण;

काष्ठा plip_local अणु
	क्रमागत plip_packet_state state;
	क्रमागत plip_nibble_state nibble;
	जोड़ अणु
		काष्ठा अणु
#अगर defined(__LITTLE_ENDIAN)
			अचिन्हित अक्षर lsb;
			अचिन्हित अक्षर msb;
#या_अगर defined(__BIG_ENDIAN)
			अचिन्हित अक्षर msb;
			अचिन्हित अक्षर lsb;
#अन्यथा
#त्रुटि	"Please fix the endianness defines in <asm/byteorder.h>"
#पूर्ण_अगर
		पूर्ण b;
		अचिन्हित लघु h;
	पूर्ण length;
	अचिन्हित लघु byte;
	अचिन्हित अक्षर  checksum;
	अचिन्हित अक्षर  data;
	काष्ठा sk_buff *skb;
पूर्ण;

काष्ठा net_local अणु
	काष्ठा net_device *dev;
	काष्ठा work_काष्ठा immediate;
	काष्ठा delayed_work deferred;
	काष्ठा delayed_work समयr;
	काष्ठा plip_local snd_data;
	काष्ठा plip_local rcv_data;
	काष्ठा pardevice *pardev;
	अचिन्हित दीर्घ  trigger;
	अचिन्हित दीर्घ  nibble;
	क्रमागत plip_connection_state connection;
	अचिन्हित लघु समयout_count;
	पूर्णांक is_deferred;
	पूर्णांक port_owner;
	पूर्णांक should_relinquish;
	spinlock_t lock;
	atomic_t समाप्त_समयr;
	काष्ठा completion समाप्तed_समयr_cmp;
पूर्ण;

अटल अंतरभूत व्योम enable_parport_पूर्णांकerrupts (काष्ठा net_device *dev)
अणु
	अगर (dev->irq != -1)
	अणु
		काष्ठा parport *port =
		   ((काष्ठा net_local *)netdev_priv(dev))->pardev->port;
		port->ops->enable_irq (port);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम disable_parport_पूर्णांकerrupts (काष्ठा net_device *dev)
अणु
	अगर (dev->irq != -1)
	अणु
		काष्ठा parport *port =
		   ((काष्ठा net_local *)netdev_priv(dev))->pardev->port;
		port->ops->disable_irq (port);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_data (काष्ठा net_device *dev, अचिन्हित अक्षर data)
अणु
	काष्ठा parport *port =
	   ((काष्ठा net_local *)netdev_priv(dev))->pardev->port;

	port->ops->ग_लिखो_data (port, data);
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर पढ़ो_status (काष्ठा net_device *dev)
अणु
	काष्ठा parport *port =
	   ((काष्ठा net_local *)netdev_priv(dev))->pardev->port;

	वापस port->ops->पढ़ो_status (port);
पूर्ण

अटल स्थिर काष्ठा header_ops plip_header_ops = अणु
	.create	= plip_hard_header,
	.cache  = plip_hard_header_cache,
पूर्ण;

अटल स्थिर काष्ठा net_device_ops plip_netdev_ops = अणु
	.nकरो_खोलो		 = plip_खोलो,
	.nकरो_stop		 = plip_बंद,
	.nकरो_start_xmit		 = plip_tx_packet,
	.nकरो_करो_ioctl		 = plip_ioctl,
	.nकरो_set_mac_address	 = eth_mac_addr,
	.nकरो_validate_addr	 = eth_validate_addr,
पूर्ण;

/* Entry poपूर्णांक of PLIP driver.
   Probe the hardware, and रेजिस्टर/initialize the driver.

   PLIP is rather weird, because of the way it पूर्णांकeracts with the parport
   प्रणाली.  It is _not_ initialised from Space.c.  Instead, plip_init()
   is called, and that function makes up a "struct net_device" क्रम each port, and
   then calls us here.

   */
अटल व्योम
plip_init_netdev(काष्ठा net_device *dev)
अणु
	काष्ठा net_local *nl = netdev_priv(dev);

	/* Then, override parts of it */
	dev->tx_queue_len 	 = 10;
	dev->flags	         = IFF_POINTOPOINT|IFF_NOARP;
	स_रखो(dev->dev_addr, 0xfc, ETH_ALEN);

	dev->netdev_ops		 = &plip_netdev_ops;
	dev->header_ops          = &plip_header_ops;


	nl->port_owner = 0;

	/* Initialize स्थिरants */
	nl->trigger	= PLIP_TRIGGER_WAIT;
	nl->nibble	= PLIP_NIBBLE_WAIT;

	/* Initialize task queue काष्ठाures */
	INIT_WORK(&nl->immediate, plip_bh);
	INIT_DELAYED_WORK(&nl->deferred, plip_kick_bh);

	अगर (dev->irq == -1)
		INIT_DELAYED_WORK(&nl->समयr, plip_समयr_bh);

	spin_lock_init(&nl->lock);
पूर्ण

/* Bottom half handler क्रम the delayed request.
   This routine is kicked by करो_समयr().
   Request `plip_bh' to be invoked. */
अटल व्योम
plip_kick_bh(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा net_local *nl =
		container_of(work, काष्ठा net_local, deferred.work);

	अगर (nl->is_deferred)
		schedule_work(&nl->immediate);
पूर्ण

/* Forward declarations of पूर्णांकernal routines */
अटल पूर्णांक plip_none(काष्ठा net_device *, काष्ठा net_local *,
		     काष्ठा plip_local *, काष्ठा plip_local *);
अटल पूर्णांक plip_receive_packet(काष्ठा net_device *, काष्ठा net_local *,
			       काष्ठा plip_local *, काष्ठा plip_local *);
अटल पूर्णांक plip_send_packet(काष्ठा net_device *, काष्ठा net_local *,
			    काष्ठा plip_local *, काष्ठा plip_local *);
अटल पूर्णांक plip_connection_बंद(काष्ठा net_device *, काष्ठा net_local *,
				 काष्ठा plip_local *, काष्ठा plip_local *);
अटल पूर्णांक plip_error(काष्ठा net_device *, काष्ठा net_local *,
		      काष्ठा plip_local *, काष्ठा plip_local *);
अटल पूर्णांक plip_bh_समयout_error(काष्ठा net_device *dev, काष्ठा net_local *nl,
				 काष्ठा plip_local *snd,
				 काष्ठा plip_local *rcv,
				 पूर्णांक error);

#घोषणा OK        0
#घोषणा TIMEOUT   1
#घोषणा ERROR     2
#घोषणा HS_TIMEOUT	3

प्रकार पूर्णांक (*plip_func)(काष्ठा net_device *dev, काष्ठा net_local *nl,
			 काष्ठा plip_local *snd, काष्ठा plip_local *rcv);

अटल स्थिर plip_func connection_state_table[] =
अणु
	plip_none,
	plip_receive_packet,
	plip_send_packet,
	plip_connection_बंद,
	plip_error
पूर्ण;

/* Bottom half handler of PLIP. */
अटल व्योम
plip_bh(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा net_local *nl = container_of(work, काष्ठा net_local, immediate);
	काष्ठा plip_local *snd = &nl->snd_data;
	काष्ठा plip_local *rcv = &nl->rcv_data;
	plip_func f;
	पूर्णांक r;

	nl->is_deferred = 0;
	f = connection_state_table[nl->connection];
	अगर ((r = (*f)(nl->dev, nl, snd, rcv)) != OK &&
	    (r = plip_bh_समयout_error(nl->dev, nl, snd, rcv, r)) != OK) अणु
		nl->is_deferred = 1;
		schedule_delayed_work(&nl->deferred, 1);
	पूर्ण
पूर्ण

अटल व्योम
plip_समयr_bh(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा net_local *nl =
		container_of(work, काष्ठा net_local, समयr.work);

	अगर (!(atomic_पढ़ो (&nl->समाप्त_समयr))) अणु
		plip_पूर्णांकerrupt (nl->dev);

		schedule_delayed_work(&nl->समयr, 1);
	पूर्ण
	अन्यथा अणु
		complete(&nl->समाप्तed_समयr_cmp);
	पूर्ण
पूर्ण

अटल पूर्णांक
plip_bh_समयout_error(काष्ठा net_device *dev, काष्ठा net_local *nl,
		      काष्ठा plip_local *snd, काष्ठा plip_local *rcv,
		      पूर्णांक error)
अणु
	अचिन्हित अक्षर c0;
	/*
	 * This is tricky. If we got here from the beginning of send (either
	 * with ERROR or HS_TIMEOUT) we have IRQ enabled. Otherwise it's
	 * alपढ़ोy disabled. With the old variant of अणुenable,disableपूर्ण_irq()
	 * extra disable_irq() was a no-op. Now it became mortal - it's
	 * unbalanced and thus we'll never re-enable IRQ (until rmmod plip,
	 * that is). So we have to treat HS_TIMEOUT and ERROR from send
	 * in a special way.
	 */

	spin_lock_irq(&nl->lock);
	अगर (nl->connection == PLIP_CN_SEND) अणु

		अगर (error != ERROR) अणु /* Timeout */
			nl->समयout_count++;
			अगर ((error == HS_TIMEOUT && nl->समयout_count <= 10) ||
			    nl->समयout_count <= 3) अणु
				spin_unlock_irq(&nl->lock);
				/* Try again later */
				वापस TIMEOUT;
			पूर्ण
			c0 = पढ़ो_status(dev);
			prपूर्णांकk(KERN_WARNING "%s: transmit timeout(%d,%02x)\n",
			       dev->name, snd->state, c0);
		पूर्ण अन्यथा
			error = HS_TIMEOUT;
		dev->stats.tx_errors++;
		dev->stats.tx_पातed_errors++;
	पूर्ण अन्यथा अगर (nl->connection == PLIP_CN_RECEIVE) अणु
		अगर (rcv->state == PLIP_PK_TRIGGER) अणु
			/* Transmission was पूर्णांकerrupted. */
			spin_unlock_irq(&nl->lock);
			वापस OK;
		पूर्ण
		अगर (error != ERROR) अणु /* Timeout */
			अगर (++nl->समयout_count <= 3) अणु
				spin_unlock_irq(&nl->lock);
				/* Try again later */
				वापस TIMEOUT;
			पूर्ण
			c0 = पढ़ो_status(dev);
			prपूर्णांकk(KERN_WARNING "%s: receive timeout(%d,%02x)\n",
			       dev->name, rcv->state, c0);
		पूर्ण
		dev->stats.rx_dropped++;
	पूर्ण
	rcv->state = PLIP_PK_DONE;
	अगर (rcv->skb) अणु
		kमुक्त_skb(rcv->skb);
		rcv->skb = शून्य;
	पूर्ण
	snd->state = PLIP_PK_DONE;
	अगर (snd->skb) अणु
		dev_kमुक्त_skb(snd->skb);
		snd->skb = शून्य;
	पूर्ण
	spin_unlock_irq(&nl->lock);
	अगर (error == HS_TIMEOUT) अणु
		DISABLE(dev->irq);
		synchronize_irq(dev->irq);
	पूर्ण
	disable_parport_पूर्णांकerrupts (dev);
	netअगर_stop_queue (dev);
	nl->connection = PLIP_CN_ERROR;
	ग_लिखो_data (dev, 0x00);

	वापस TIMEOUT;
पूर्ण

अटल पूर्णांक
plip_none(काष्ठा net_device *dev, काष्ठा net_local *nl,
	  काष्ठा plip_local *snd, काष्ठा plip_local *rcv)
अणु
	वापस OK;
पूर्ण

/* PLIP_RECEIVE --- receive a byte(two nibbles)
   Returns OK on success, TIMEOUT on समयout */
अटल अंतरभूत पूर्णांक
plip_receive(अचिन्हित लघु nibble_समयout, काष्ठा net_device *dev,
	     क्रमागत plip_nibble_state *ns_p, अचिन्हित अक्षर *data_p)
अणु
	अचिन्हित अक्षर c0, c1;
	अचिन्हित पूर्णांक cx;

	चयन (*ns_p) अणु
	हाल PLIP_NB_BEGIN:
		cx = nibble_समयout;
		जबतक (1) अणु
			c0 = पढ़ो_status(dev);
			udelay(PLIP_DELAY_UNIT);
			अगर ((c0 & 0x80) == 0) अणु
				c1 = पढ़ो_status(dev);
				अगर (c0 == c1)
					अवरोध;
			पूर्ण
			अगर (--cx == 0)
				वापस TIMEOUT;
		पूर्ण
		*data_p = (c0 >> 3) & 0x0f;
		ग_लिखो_data (dev, 0x10); /* send ACK */
		*ns_p = PLIP_NB_1;
		fallthrough;

	हाल PLIP_NB_1:
		cx = nibble_समयout;
		जबतक (1) अणु
			c0 = पढ़ो_status(dev);
			udelay(PLIP_DELAY_UNIT);
			अगर (c0 & 0x80) अणु
				c1 = पढ़ो_status(dev);
				अगर (c0 == c1)
					अवरोध;
			पूर्ण
			अगर (--cx == 0)
				वापस TIMEOUT;
		पूर्ण
		*data_p |= (c0 << 1) & 0xf0;
		ग_लिखो_data (dev, 0x00); /* send ACK */
		*ns_p = PLIP_NB_BEGIN;
		अवरोध;
	हाल PLIP_NB_2:
		अवरोध;
	पूर्ण
	वापस OK;
पूर्ण

/*
 *	Determine the packet's protocol ID. The rule here is that we
 *	assume 802.3 अगर the type field is लघु enough to be a length.
 *	This is normal practice and works क्रम any 'now in use' protocol.
 *
 *	PLIP is ethernet ish but the daddr might not be valid अगर unicast.
 *	PLIP क्रमtunately has no bus architecture (its Poपूर्णांक-to-poपूर्णांक).
 *
 *	We can't fix the daddr thing as that quirk (more bug) is embedded
 *	in far too many old प्रणालीs not all even running Linux.
 */

अटल __be16 plip_type_trans(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा ethhdr *eth;
	अचिन्हित अक्षर *rawp;

	skb_reset_mac_header(skb);
	skb_pull(skb,dev->hard_header_len);
	eth = eth_hdr(skb);

	अगर(is_multicast_ether_addr(eth->h_dest))
	अणु
		अगर(ether_addr_equal_64bits(eth->h_dest, dev->broadcast))
			skb->pkt_type=PACKET_BROADCAST;
		अन्यथा
			skb->pkt_type=PACKET_MULTICAST;
	पूर्ण

	/*
	 *	This ALLMULTI check should be redundant by 1.4
	 *	so करोn't क्रमget to हटाओ it.
	 */

	अगर (ntohs(eth->h_proto) >= ETH_P_802_3_MIN)
		वापस eth->h_proto;

	rawp = skb->data;

	/*
	 *	This is a magic hack to spot IPX packets. Older Novell अवरोधs
	 *	the protocol design and runs IPX over 802.3 without an 802.2 LLC
	 *	layer. We look क्रम FFFF which isn't a used 802.2 SSAP/DSAP. This
	 *	won't work क्रम fault tolerant netware but करोes क्रम the rest.
	 */
	अगर (*(अचिन्हित लघु *)rawp == 0xFFFF)
		वापस htons(ETH_P_802_3);

	/*
	 *	Real 802.2 LLC
	 */
	वापस htons(ETH_P_802_2);
पूर्ण

/* PLIP_RECEIVE_PACKET --- receive a packet */
अटल पूर्णांक
plip_receive_packet(काष्ठा net_device *dev, काष्ठा net_local *nl,
		    काष्ठा plip_local *snd, काष्ठा plip_local *rcv)
अणु
	अचिन्हित लघु nibble_समयout = nl->nibble;
	अचिन्हित अक्षर *lbuf;

	चयन (rcv->state) अणु
	हाल PLIP_PK_TRIGGER:
		DISABLE(dev->irq);
		/* Don't need to synchronize irq, as we can safely ignore it */
		disable_parport_पूर्णांकerrupts (dev);
		ग_लिखो_data (dev, 0x01); /* send ACK */
		अगर (net_debug > 2)
			prपूर्णांकk(KERN_DEBUG "%s: receive start\n", dev->name);
		rcv->state = PLIP_PK_LENGTH_LSB;
		rcv->nibble = PLIP_NB_BEGIN;
		fallthrough;

	हाल PLIP_PK_LENGTH_LSB:
		अगर (snd->state != PLIP_PK_DONE) अणु
			अगर (plip_receive(nl->trigger, dev,
					 &rcv->nibble, &rcv->length.b.lsb)) अणु
				/* collision, here dev->tbusy == 1 */
				rcv->state = PLIP_PK_DONE;
				nl->is_deferred = 1;
				nl->connection = PLIP_CN_SEND;
				schedule_delayed_work(&nl->deferred, 1);
				enable_parport_पूर्णांकerrupts (dev);
				ENABLE(dev->irq);
				वापस OK;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (plip_receive(nibble_समयout, dev,
					 &rcv->nibble, &rcv->length.b.lsb))
				वापस TIMEOUT;
		पूर्ण
		rcv->state = PLIP_PK_LENGTH_MSB;
		fallthrough;

	हाल PLIP_PK_LENGTH_MSB:
		अगर (plip_receive(nibble_समयout, dev,
				 &rcv->nibble, &rcv->length.b.msb))
			वापस TIMEOUT;
		अगर (rcv->length.h > dev->mtu + dev->hard_header_len ||
		    rcv->length.h < 8) अणु
			prपूर्णांकk(KERN_WARNING "%s: bogus packet size %d.\n", dev->name, rcv->length.h);
			वापस ERROR;
		पूर्ण
		/* Malloc up new buffer. */
		rcv->skb = dev_alloc_skb(rcv->length.h + 2);
		अगर (rcv->skb == शून्य) अणु
			prपूर्णांकk(KERN_ERR "%s: Memory squeeze.\n", dev->name);
			वापस ERROR;
		पूर्ण
		skb_reserve(rcv->skb, 2);	/* Align IP on 16 byte boundaries */
		skb_put(rcv->skb,rcv->length.h);
		rcv->skb->dev = dev;
		rcv->state = PLIP_PK_DATA;
		rcv->byte = 0;
		rcv->checksum = 0;
		fallthrough;

	हाल PLIP_PK_DATA:
		lbuf = rcv->skb->data;
		करो अणु
			अगर (plip_receive(nibble_समयout, dev,
					 &rcv->nibble, &lbuf[rcv->byte]))
				वापस TIMEOUT;
		पूर्ण जबतक (++rcv->byte < rcv->length.h);
		करो अणु
			rcv->checksum += lbuf[--rcv->byte];
		पूर्ण जबतक (rcv->byte);
		rcv->state = PLIP_PK_CHECKSUM;
		fallthrough;

	हाल PLIP_PK_CHECKSUM:
		अगर (plip_receive(nibble_समयout, dev,
				 &rcv->nibble, &rcv->data))
			वापस TIMEOUT;
		अगर (rcv->data != rcv->checksum) अणु
			dev->stats.rx_crc_errors++;
			अगर (net_debug)
				prपूर्णांकk(KERN_DEBUG "%s: checksum error\n", dev->name);
			वापस ERROR;
		पूर्ण
		rcv->state = PLIP_PK_DONE;
		fallthrough;

	हाल PLIP_PK_DONE:
		/* Inक्रमm the upper layer क्रम the arrival of a packet. */
		rcv->skb->protocol=plip_type_trans(rcv->skb, dev);
		netअगर_rx_ni(rcv->skb);
		dev->stats.rx_bytes += rcv->length.h;
		dev->stats.rx_packets++;
		rcv->skb = शून्य;
		अगर (net_debug > 2)
			prपूर्णांकk(KERN_DEBUG "%s: receive end\n", dev->name);

		/* Close the connection. */
		ग_लिखो_data (dev, 0x00);
		spin_lock_irq(&nl->lock);
		अगर (snd->state != PLIP_PK_DONE) अणु
			nl->connection = PLIP_CN_SEND;
			spin_unlock_irq(&nl->lock);
			schedule_work(&nl->immediate);
			enable_parport_पूर्णांकerrupts (dev);
			ENABLE(dev->irq);
			वापस OK;
		पूर्ण अन्यथा अणु
			nl->connection = PLIP_CN_NONE;
			spin_unlock_irq(&nl->lock);
			enable_parport_पूर्णांकerrupts (dev);
			ENABLE(dev->irq);
			वापस OK;
		पूर्ण
	पूर्ण
	वापस OK;
पूर्ण

/* PLIP_SEND --- send a byte (two nibbles)
   Returns OK on success, TIMEOUT when समयout    */
अटल अंतरभूत पूर्णांक
plip_send(अचिन्हित लघु nibble_समयout, काष्ठा net_device *dev,
	  क्रमागत plip_nibble_state *ns_p, अचिन्हित अक्षर data)
अणु
	अचिन्हित अक्षर c0;
	अचिन्हित पूर्णांक cx;

	चयन (*ns_p) अणु
	हाल PLIP_NB_BEGIN:
		ग_लिखो_data (dev, data & 0x0f);
		*ns_p = PLIP_NB_1;
		fallthrough;

	हाल PLIP_NB_1:
		ग_लिखो_data (dev, 0x10 | (data & 0x0f));
		cx = nibble_समयout;
		जबतक (1) अणु
			c0 = पढ़ो_status(dev);
			अगर ((c0 & 0x80) == 0)
				अवरोध;
			अगर (--cx == 0)
				वापस TIMEOUT;
			udelay(PLIP_DELAY_UNIT);
		पूर्ण
		ग_लिखो_data (dev, 0x10 | (data >> 4));
		*ns_p = PLIP_NB_2;
		fallthrough;

	हाल PLIP_NB_2:
		ग_लिखो_data (dev, (data >> 4));
		cx = nibble_समयout;
		जबतक (1) अणु
			c0 = पढ़ो_status(dev);
			अगर (c0 & 0x80)
				अवरोध;
			अगर (--cx == 0)
				वापस TIMEOUT;
			udelay(PLIP_DELAY_UNIT);
		पूर्ण
		*ns_p = PLIP_NB_BEGIN;
		वापस OK;
	पूर्ण
	वापस OK;
पूर्ण

/* PLIP_SEND_PACKET --- send a packet */
अटल पूर्णांक
plip_send_packet(काष्ठा net_device *dev, काष्ठा net_local *nl,
		 काष्ठा plip_local *snd, काष्ठा plip_local *rcv)
अणु
	अचिन्हित लघु nibble_समयout = nl->nibble;
	अचिन्हित अक्षर *lbuf;
	अचिन्हित अक्षर c0;
	अचिन्हित पूर्णांक cx;

	अगर (snd->skb == शून्य || (lbuf = snd->skb->data) == शून्य) अणु
		prपूर्णांकk(KERN_DEBUG "%s: send skb lost\n", dev->name);
		snd->state = PLIP_PK_DONE;
		snd->skb = शून्य;
		वापस ERROR;
	पूर्ण

	चयन (snd->state) अणु
	हाल PLIP_PK_TRIGGER:
		अगर ((पढ़ो_status(dev) & 0xf8) != 0x80)
			वापस HS_TIMEOUT;

		/* Trigger remote rx पूर्णांकerrupt. */
		ग_लिखो_data (dev, 0x08);
		cx = nl->trigger;
		जबतक (1) अणु
			udelay(PLIP_DELAY_UNIT);
			spin_lock_irq(&nl->lock);
			अगर (nl->connection == PLIP_CN_RECEIVE) अणु
				spin_unlock_irq(&nl->lock);
				/* Interrupted. */
				dev->stats.collisions++;
				वापस OK;
			पूर्ण
			c0 = पढ़ो_status(dev);
			अगर (c0 & 0x08) अणु
				spin_unlock_irq(&nl->lock);
				DISABLE(dev->irq);
				synchronize_irq(dev->irq);
				अगर (nl->connection == PLIP_CN_RECEIVE) अणु
					/* Interrupted.
					   We करोn't need to enable irq,
					   as it is soon disabled.    */
					/* Yes, we करो. New variant of
					   अणुenable,disableपूर्ण_irq *counts*
					   them.  -- AV  */
					ENABLE(dev->irq);
					dev->stats.collisions++;
					वापस OK;
				पूर्ण
				disable_parport_पूर्णांकerrupts (dev);
				अगर (net_debug > 2)
					prपूर्णांकk(KERN_DEBUG "%s: send start\n", dev->name);
				snd->state = PLIP_PK_LENGTH_LSB;
				snd->nibble = PLIP_NB_BEGIN;
				nl->समयout_count = 0;
				अवरोध;
			पूर्ण
			spin_unlock_irq(&nl->lock);
			अगर (--cx == 0) अणु
				ग_लिखो_data (dev, 0x00);
				वापस HS_TIMEOUT;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल PLIP_PK_LENGTH_LSB:
		अगर (plip_send(nibble_समयout, dev,
			      &snd->nibble, snd->length.b.lsb))
			वापस TIMEOUT;
		snd->state = PLIP_PK_LENGTH_MSB;
		fallthrough;

	हाल PLIP_PK_LENGTH_MSB:
		अगर (plip_send(nibble_समयout, dev,
			      &snd->nibble, snd->length.b.msb))
			वापस TIMEOUT;
		snd->state = PLIP_PK_DATA;
		snd->byte = 0;
		snd->checksum = 0;
		fallthrough;

	हाल PLIP_PK_DATA:
		करो अणु
			अगर (plip_send(nibble_समयout, dev,
				      &snd->nibble, lbuf[snd->byte]))
				वापस TIMEOUT;
		पूर्ण जबतक (++snd->byte < snd->length.h);
		करो अणु
			snd->checksum += lbuf[--snd->byte];
		पूर्ण जबतक (snd->byte);
		snd->state = PLIP_PK_CHECKSUM;
		fallthrough;

	हाल PLIP_PK_CHECKSUM:
		अगर (plip_send(nibble_समयout, dev,
			      &snd->nibble, snd->checksum))
			वापस TIMEOUT;

		dev->stats.tx_bytes += snd->skb->len;
		dev_kमुक्त_skb(snd->skb);
		dev->stats.tx_packets++;
		snd->state = PLIP_PK_DONE;
		fallthrough;

	हाल PLIP_PK_DONE:
		/* Close the connection */
		ग_लिखो_data (dev, 0x00);
		snd->skb = शून्य;
		अगर (net_debug > 2)
			prपूर्णांकk(KERN_DEBUG "%s: send end\n", dev->name);
		nl->connection = PLIP_CN_CLOSING;
		nl->is_deferred = 1;
		schedule_delayed_work(&nl->deferred, 1);
		enable_parport_पूर्णांकerrupts (dev);
		ENABLE(dev->irq);
		वापस OK;
	पूर्ण
	वापस OK;
पूर्ण

अटल पूर्णांक
plip_connection_बंद(काष्ठा net_device *dev, काष्ठा net_local *nl,
		      काष्ठा plip_local *snd, काष्ठा plip_local *rcv)
अणु
	spin_lock_irq(&nl->lock);
	अगर (nl->connection == PLIP_CN_CLOSING) अणु
		nl->connection = PLIP_CN_NONE;
		netअगर_wake_queue (dev);
	पूर्ण
	spin_unlock_irq(&nl->lock);
	अगर (nl->should_relinquish) अणु
		nl->should_relinquish = nl->port_owner = 0;
		parport_release(nl->pardev);
	पूर्ण
	वापस OK;
पूर्ण

/* PLIP_ERROR --- रुको till other end settled */
अटल पूर्णांक
plip_error(काष्ठा net_device *dev, काष्ठा net_local *nl,
	   काष्ठा plip_local *snd, काष्ठा plip_local *rcv)
अणु
	अचिन्हित अक्षर status;

	status = पढ़ो_status(dev);
	अगर ((status & 0xf8) == 0x80) अणु
		अगर (net_debug > 2)
			prपूर्णांकk(KERN_DEBUG "%s: reset interface.\n", dev->name);
		nl->connection = PLIP_CN_NONE;
		nl->should_relinquish = 0;
		netअगर_start_queue (dev);
		enable_parport_पूर्णांकerrupts (dev);
		ENABLE(dev->irq);
		netअगर_wake_queue (dev);
	पूर्ण अन्यथा अणु
		nl->is_deferred = 1;
		schedule_delayed_work(&nl->deferred, 1);
	पूर्ण

	वापस OK;
पूर्ण

/* Handle the parallel port पूर्णांकerrupts. */
अटल व्योम
plip_पूर्णांकerrupt(व्योम *dev_id)
अणु
	काष्ठा net_device *dev = dev_id;
	काष्ठा net_local *nl;
	काष्ठा plip_local *rcv;
	अचिन्हित अक्षर c0;
	अचिन्हित दीर्घ flags;

	nl = netdev_priv(dev);
	rcv = &nl->rcv_data;

	spin_lock_irqsave (&nl->lock, flags);

	c0 = पढ़ो_status(dev);
	अगर ((c0 & 0xf8) != 0xc0) अणु
		अगर ((dev->irq != -1) && (net_debug > 1))
			prपूर्णांकk(KERN_DEBUG "%s: spurious interrupt\n", dev->name);
		spin_unlock_irqrestore (&nl->lock, flags);
		वापस;
	पूर्ण

	अगर (net_debug > 3)
		prपूर्णांकk(KERN_DEBUG "%s: interrupt.\n", dev->name);

	चयन (nl->connection) अणु
	हाल PLIP_CN_CLOSING:
		netअगर_wake_queue (dev);
		fallthrough;
	हाल PLIP_CN_NONE:
	हाल PLIP_CN_SEND:
		rcv->state = PLIP_PK_TRIGGER;
		nl->connection = PLIP_CN_RECEIVE;
		nl->समयout_count = 0;
		schedule_work(&nl->immediate);
		अवरोध;

	हाल PLIP_CN_RECEIVE:
		/* May occur because there is race condition
		   around test and set of dev->पूर्णांकerrupt.
		   Ignore this पूर्णांकerrupt. */
		अवरोध;

	हाल PLIP_CN_ERROR:
		prपूर्णांकk(KERN_ERR "%s: receive interrupt in error state\n", dev->name);
		अवरोध;
	पूर्ण

	spin_unlock_irqrestore(&nl->lock, flags);
पूर्ण

अटल netdev_tx_t
plip_tx_packet(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा net_local *nl = netdev_priv(dev);
	काष्ठा plip_local *snd = &nl->snd_data;

	अगर (netअगर_queue_stopped(dev))
		वापस NETDEV_TX_BUSY;

	/* We may need to grab the bus */
	अगर (!nl->port_owner) अणु
		अगर (parport_claim(nl->pardev))
			वापस NETDEV_TX_BUSY;
		nl->port_owner = 1;
	पूर्ण

	netअगर_stop_queue (dev);

	अगर (skb->len > dev->mtu + dev->hard_header_len) अणु
		prपूर्णांकk(KERN_WARNING "%s: packet too big, %d.\n", dev->name, (पूर्णांक)skb->len);
		netअगर_start_queue (dev);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	अगर (net_debug > 2)
		prपूर्णांकk(KERN_DEBUG "%s: send request\n", dev->name);

	spin_lock_irq(&nl->lock);
	snd->skb = skb;
	snd->length.h = skb->len;
	snd->state = PLIP_PK_TRIGGER;
	अगर (nl->connection == PLIP_CN_NONE) अणु
		nl->connection = PLIP_CN_SEND;
		nl->समयout_count = 0;
	पूर्ण
	schedule_work(&nl->immediate);
	spin_unlock_irq(&nl->lock);

	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम
plip_reग_लिखो_address(स्थिर काष्ठा net_device *dev, काष्ठा ethhdr *eth)
अणु
	स्थिर काष्ठा in_device *in_dev;

	rcu_पढ़ो_lock();
	in_dev = __in_dev_get_rcu(dev);
	अगर (in_dev) अणु
		/* Any address will करो - we take the first */
		स्थिर काष्ठा in_अगरaddr *अगरa = rcu_dereference(in_dev->अगरa_list);
		अगर (अगरa) अणु
			स_नकल(eth->h_source, dev->dev_addr, ETH_ALEN);
			स_रखो(eth->h_dest, 0xfc, 2);
			स_नकल(eth->h_dest+2, &अगरa->अगरa_address, 4);
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

अटल पूर्णांक
plip_hard_header(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
		 अचिन्हित लघु type, स्थिर व्योम *daddr,
		 स्थिर व्योम *saddr, अचिन्हित len)
अणु
	पूर्णांक ret;

	ret = eth_header(skb, dev, type, daddr, saddr, len);
	अगर (ret >= 0)
		plip_reग_लिखो_address (dev, (काष्ठा ethhdr *)skb->data);

	वापस ret;
पूर्ण

अटल पूर्णांक plip_hard_header_cache(स्थिर काष्ठा neighbour *neigh,
				  काष्ठा hh_cache *hh, __be16 type)
अणु
	पूर्णांक ret;

	ret = eth_header_cache(neigh, hh, type);
	अगर (ret == 0) अणु
		काष्ठा ethhdr *eth;

		eth = (काष्ठा ethhdr*)(((u8*)hh->hh_data) +
				       HH_DATA_OFF(माप(*eth)));
		plip_reग_लिखो_address (neigh->dev, eth);
	पूर्ण

	वापस ret;
पूर्ण

/* Open/initialize the board.  This is called (in the current kernel)
   someसमय after booting when the 'ifconfig' program is run.

   This routine माला_लो exclusive access to the parallel port by allocating
   its IRQ line.
 */
अटल पूर्णांक
plip_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा net_local *nl = netdev_priv(dev);
	काष्ठा in_device *in_dev;

	/* Grab the port */
	अगर (!nl->port_owner) अणु
		अगर (parport_claim(nl->pardev)) वापस -EAGAIN;
		nl->port_owner = 1;
	पूर्ण

	nl->should_relinquish = 0;

	/* Clear the data port. */
	ग_लिखो_data (dev, 0x00);

	/* Enable rx पूर्णांकerrupt. */
	enable_parport_पूर्णांकerrupts (dev);
	अगर (dev->irq == -1)
	अणु
		atomic_set (&nl->समाप्त_समयr, 0);
		schedule_delayed_work(&nl->समयr, 1);
	पूर्ण

	/* Initialize the state machine. */
	nl->rcv_data.state = nl->snd_data.state = PLIP_PK_DONE;
	nl->rcv_data.skb = nl->snd_data.skb = शून्य;
	nl->connection = PLIP_CN_NONE;
	nl->is_deferred = 0;

	/* Fill in the MAC-level header.
	   We used to abuse dev->broadcast to store the poपूर्णांक-to-poपूर्णांक
	   MAC address, but we no दीर्घer करो it. Instead, we fetch the
	   पूर्णांकerface address whenever it is needed, which is cheap enough
	   because we use the hh_cache. Actually, abusing dev->broadcast
	   didn't work, because when using plip_खोलो the poपूर्णांक-to-poपूर्णांक
	   address isn't yet known.
	   PLIP करोesn't have a real MAC address, but we need it to be
	   DOS compatible, and to properly support taps (otherwise,
	   when the device address isn't identical to the address of a
	   received frame, the kernel incorrectly drops it).             */

	in_dev=__in_dev_get_rtnl(dev);
	अगर (in_dev) अणु
		/* Any address will करो - we take the first. We alपढ़ोy
		   have the first two bytes filled with 0xfc, from
		   plip_init_dev(). */
		स्थिर काष्ठा in_अगरaddr *अगरa = rcu_dereference(in_dev->अगरa_list);
		अगर (अगरa != शून्य) अणु
			स_नकल(dev->dev_addr+2, &अगरa->अगरa_local, 4);
		पूर्ण
	पूर्ण

	netअगर_start_queue (dev);

	वापस 0;
पूर्ण

/* The inverse routine to plip_खोलो (). */
अटल पूर्णांक
plip_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा net_local *nl = netdev_priv(dev);
	काष्ठा plip_local *snd = &nl->snd_data;
	काष्ठा plip_local *rcv = &nl->rcv_data;

	netअगर_stop_queue (dev);
	DISABLE(dev->irq);
	synchronize_irq(dev->irq);

	अगर (dev->irq == -1)
	अणु
		init_completion(&nl->समाप्तed_समयr_cmp);
		atomic_set (&nl->समाप्त_समयr, 1);
		रुको_क्रम_completion(&nl->समाप्तed_समयr_cmp);
	पूर्ण

#अगर_घोषित NOTDEF
	outb(0x00, PAR_DATA(dev));
#पूर्ण_अगर
	nl->is_deferred = 0;
	nl->connection = PLIP_CN_NONE;
	अगर (nl->port_owner) अणु
		parport_release(nl->pardev);
		nl->port_owner = 0;
	पूर्ण

	snd->state = PLIP_PK_DONE;
	अगर (snd->skb) अणु
		dev_kमुक्त_skb(snd->skb);
		snd->skb = शून्य;
	पूर्ण
	rcv->state = PLIP_PK_DONE;
	अगर (rcv->skb) अणु
		kमुक्त_skb(rcv->skb);
		rcv->skb = शून्य;
	पूर्ण

#अगर_घोषित NOTDEF
	/* Reset. */
	outb(0x00, PAR_CONTROL(dev));
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक
plip_preempt(व्योम *handle)
अणु
	काष्ठा net_device *dev = (काष्ठा net_device *)handle;
	काष्ठा net_local *nl = netdev_priv(dev);

	/* Stand our ground अगर a datagram is on the wire */
	अगर (nl->connection != PLIP_CN_NONE) अणु
		nl->should_relinquish = 1;
		वापस 1;
	पूर्ण

	nl->port_owner = 0;	/* Remember that we released the bus */
	वापस 0;
पूर्ण

अटल व्योम
plip_wakeup(व्योम *handle)
अणु
	काष्ठा net_device *dev = (काष्ठा net_device *)handle;
	काष्ठा net_local *nl = netdev_priv(dev);

	अगर (nl->port_owner) अणु
		/* Why are we being woken up? */
		prपूर्णांकk(KERN_DEBUG "%s: why am I being woken up?\n", dev->name);
		अगर (!parport_claim(nl->pardev))
			/* bus_owner is alपढ़ोy set (but why?) */
			prपूर्णांकk(KERN_DEBUG "%s: I'm broken.\n", dev->name);
		अन्यथा
			वापस;
	पूर्ण

	अगर (!(dev->flags & IFF_UP))
		/* Don't need the port when the पूर्णांकerface is करोwn */
		वापस;

	अगर (!parport_claim(nl->pardev)) अणु
		nl->port_owner = 1;
		/* Clear the data port. */
		ग_लिखो_data (dev, 0x00);
	पूर्ण
पूर्ण

अटल पूर्णांक
plip_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	काष्ठा net_local *nl = netdev_priv(dev);
	काष्ठा plipconf *pc = (काष्ठा plipconf *) &rq->अगरr_अगरru;

	अगर (cmd != SIOCDEVPLIP)
		वापस -EOPNOTSUPP;

	चयन(pc->pcmd) अणु
	हाल PLIP_GET_TIMEOUT:
		pc->trigger = nl->trigger;
		pc->nibble  = nl->nibble;
		अवरोध;
	हाल PLIP_SET_TIMEOUT:
		अगर(!capable(CAP_NET_ADMIN))
			वापस -EPERM;
		nl->trigger = pc->trigger;
		nl->nibble  = pc->nibble;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक parport[PLIP_MAX] = अणु [0 ... PLIP_MAX-1] = -1 पूर्ण;
अटल पूर्णांक timid;

module_param_array(parport, पूर्णांक, शून्य, 0);
module_param(timid, पूर्णांक, 0);
MODULE_PARM_DESC(parport, "List of parport device numbers to use by plip");

अटल काष्ठा net_device *dev_plip[PLIP_MAX] = अणु शून्य, पूर्ण;

अटल अंतरभूत पूर्णांक
plip_searchक्रम(पूर्णांक list[], पूर्णांक a)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < PLIP_MAX && list[i] != -1; i++) अणु
		अगर (list[i] == a) वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/* plip_attach() is called (by the parport code) when a port is
 * available to use. */
अटल व्योम plip_attach (काष्ठा parport *port)
अणु
	अटल पूर्णांक unit;
	काष्ठा net_device *dev;
	काष्ठा net_local *nl;
	अक्षर name[IFNAMSIZ];
	काष्ठा pardev_cb plip_cb;

	अगर ((parport[0] == -1 && (!timid || !port->devices)) ||
	    plip_searchक्रम(parport, port->number)) अणु
		अगर (unit == PLIP_MAX) अणु
			prपूर्णांकk(KERN_ERR "plip: too many devices\n");
			वापस;
		पूर्ण

		प्र_लिखो(name, "plip%d", unit);
		dev = alloc_etherdev(माप(काष्ठा net_local));
		अगर (!dev)
			वापस;

		म_नकल(dev->name, name);

		dev->irq = port->irq;
		dev->base_addr = port->base;
		अगर (port->irq == -1) अणु
			prपूर्णांकk(KERN_INFO "plip: %s has no IRQ. Using IRQ-less mode,"
		                 "which is fairly inefficient!\n", port->name);
		पूर्ण

		nl = netdev_priv(dev);
		nl->dev = dev;

		स_रखो(&plip_cb, 0, माप(plip_cb));
		plip_cb.निजी = dev;
		plip_cb.preempt = plip_preempt;
		plip_cb.wakeup = plip_wakeup;
		plip_cb.irq_func = plip_पूर्णांकerrupt;

		nl->pardev = parport_रेजिस्टर_dev_model(port, dev->name,
							&plip_cb, unit);

		अगर (!nl->pardev) अणु
			prपूर्णांकk(KERN_ERR "%s: parport_register failed\n", name);
			जाओ err_मुक्त_dev;
		पूर्ण

		plip_init_netdev(dev);

		अगर (रेजिस्टर_netdev(dev)) अणु
			prपूर्णांकk(KERN_ERR "%s: network register failed\n", name);
			जाओ err_parport_unरेजिस्टर;
		पूर्ण

		prपूर्णांकk(KERN_INFO "%s", version);
		अगर (dev->irq != -1)
			prपूर्णांकk(KERN_INFO "%s: Parallel port at %#3lx, "
					 "using IRQ %d.\n",
				         dev->name, dev->base_addr, dev->irq);
		अन्यथा
			prपूर्णांकk(KERN_INFO "%s: Parallel port at %#3lx, "
					 "not using IRQ.\n",
					 dev->name, dev->base_addr);
		dev_plip[unit++] = dev;
	पूर्ण
	वापस;

err_parport_unरेजिस्टर:
	parport_unरेजिस्टर_device(nl->pardev);
err_मुक्त_dev:
	मुक्त_netdev(dev);
पूर्ण

/* plip_detach() is called (by the parport code) when a port is
 * no दीर्घer available to use. */
अटल व्योम plip_detach (काष्ठा parport *port)
अणु
	/* Nothing to करो */
पूर्ण

अटल पूर्णांक plip_probe(काष्ठा pardevice *par_dev)
अणु
	काष्ठा device_driver *drv = par_dev->dev.driver;
	पूर्णांक len = म_माप(drv->name);

	अगर (म_भेदन(par_dev->name, drv->name, len))
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल काष्ठा parport_driver plip_driver = अणु
	.name		= "plip",
	.probe		= plip_probe,
	.match_port	= plip_attach,
	.detach		= plip_detach,
	.devmodel	= true,
पूर्ण;

अटल व्योम __निकास plip_cleanup_module (व्योम)
अणु
	काष्ठा net_device *dev;
	पूर्णांक i;

	क्रम (i=0; i < PLIP_MAX; i++) अणु
		अगर ((dev = dev_plip[i])) अणु
			काष्ठा net_local *nl = netdev_priv(dev);
			unरेजिस्टर_netdev(dev);
			अगर (nl->port_owner)
				parport_release(nl->pardev);
			parport_unरेजिस्टर_device(nl->pardev);
			मुक्त_netdev(dev);
			dev_plip[i] = शून्य;
		पूर्ण
	पूर्ण

	parport_unरेजिस्टर_driver(&plip_driver);
पूर्ण

#अगर_अघोषित MODULE

अटल पूर्णांक parport_ptr;

अटल पूर्णांक __init plip_setup(अक्षर *str)
अणु
	पूर्णांक पूर्णांकs[4];

	str = get_options(str, ARRAY_SIZE(पूर्णांकs), पूर्णांकs);

	/* Ugh. */
	अगर (!म_भेदन(str, "parport", 7)) अणु
		पूर्णांक n = simple_म_से_अदीर्घ(str+7, शून्य, 10);
		अगर (parport_ptr < PLIP_MAX)
			parport[parport_ptr++] = n;
		अन्यथा
			prपूर्णांकk(KERN_INFO "plip: too many ports, %s ignored.\n",
			       str);
	पूर्ण अन्यथा अगर (!म_भेद(str, "timid")) अणु
		timid = 1;
	पूर्ण अन्यथा अणु
		अगर (पूर्णांकs[0] == 0 || पूर्णांकs[1] == 0) अणु
			/* disable driver on "plip=" or "plip=0" */
			parport[0] = -2;
		पूर्ण अन्यथा अणु
			prपूर्णांकk(KERN_WARNING "warning: 'plip=0x%x' ignored\n",
			       पूर्णांकs[1]);
		पूर्ण
	पूर्ण
	वापस 1;
पूर्ण

__setup("plip=", plip_setup);

#पूर्ण_अगर /* !MODULE */

अटल पूर्णांक __init plip_init (व्योम)
अणु
	अगर (parport[0] == -2)
		वापस 0;

	अगर (parport[0] != -1 && timid) अणु
		prपूर्णांकk(KERN_WARNING "plip: warning, ignoring `timid' since specific ports given.\n");
		timid = 0;
	पूर्ण

	अगर (parport_रेजिस्टर_driver (&plip_driver)) अणु
		prपूर्णांकk (KERN_WARNING "plip: couldn't register driver\n");
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

module_init(plip_init);
module_निकास(plip_cleanup_module);
MODULE_LICENSE("GPL");
