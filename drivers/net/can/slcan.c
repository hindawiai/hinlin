<शैली गुरु>
/*
 * slcan.c - serial line CAN पूर्णांकerface driver (using tty line discipline)
 *
 * This file is derived from linux/drivers/net/slip/slip.c
 *
 * slip.c Authors  : Laurence Culhane <loz@holmes.demon.co.uk>
 *                   Fred N. van Kempen <waltje@uwalt.nl.mugnet.org>
 * slcan.c Author  : Oliver Hartkopp <socketcan@hartkopp.net>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License aदीर्घ
 * with this program; अगर not, see http://www.gnu.org/licenses/gpl.hपंचांगl
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>

#समावेश <linux/uaccess.h>
#समावेश <linux/bitops.h>
#समावेश <linux/माला.स>
#समावेश <linux/tty.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/sched.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/can.h>
#समावेश <linux/can/skb.h>
#समावेश <linux/can/can-ml.h>

MODULE_ALIAS_LDISC(N_SLCAN);
MODULE_DESCRIPTION("serial line CAN interface");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Oliver Hartkopp <socketcan@hartkopp.net>");

#घोषणा SLCAN_MAGIC 0x53CA

अटल पूर्णांक maxdev = 10;		/* MAX number of SLCAN channels;
				   This can be overridden with
				   insmod slcan.ko maxdev=nnn	*/
module_param(maxdev, पूर्णांक, 0);
MODULE_PARM_DESC(maxdev, "Maximum number of slcan interfaces");

/* maximum rx buffer len: extended CAN frame with बारtamp */
#घोषणा SLC_MTU (माप("T1111222281122334455667788EA5F\r")+1)

#घोषणा SLC_CMD_LEN 1
#घोषणा SLC_SFF_ID_LEN 3
#घोषणा SLC_EFF_ID_LEN 8

काष्ठा slcan अणु
	पूर्णांक			magic;

	/* Various fields. */
	काष्ठा tty_काष्ठा	*tty;		/* ptr to TTY काष्ठाure	     */
	काष्ठा net_device	*dev;		/* easy क्रम पूर्णांकr handling    */
	spinlock_t		lock;
	काष्ठा work_काष्ठा	tx_work;	/* Flushes transmit buffer   */

	/* These are poपूर्णांकers to the दो_स्मृति()ed frame buffers. */
	अचिन्हित अक्षर		rbuff[SLC_MTU];	/* receiver buffer	     */
	पूर्णांक			rcount;         /* received अक्षरs counter    */
	अचिन्हित अक्षर		xbuff[SLC_MTU];	/* transmitter buffer	     */
	अचिन्हित अक्षर		*xhead;         /* poपूर्णांकer to next XMIT byte */
	पूर्णांक			xleft;          /* bytes left in XMIT queue  */

	अचिन्हित दीर्घ		flags;		/* Flag values/ mode etc     */
#घोषणा SLF_INUSE		0		/* Channel in use            */
#घोषणा SLF_ERROR		1               /* Parity, etc. error        */
पूर्ण;

अटल काष्ठा net_device **slcan_devs;

 /************************************************************************
  *			SLCAN ENCAPSULATION FORMAT			 *
  ************************************************************************/

/*
 * A CAN frame has a can_id (11 bit standard frame क्रमmat OR 29 bit extended
 * frame क्रमmat) a data length code (len) which can be from 0 to 8
 * and up to <len> data bytes as payload.
 * Additionally a CAN frame may become a remote transmission frame अगर the
 * RTR-bit is set. This causes another ECU to send a CAN frame with the
 * given can_id.
 *
 * The SLCAN ASCII representation of these dअगरferent frame types is:
 * <type> <id> <dlc> <data>*
 *
 * Extended frames (29 bit) are defined by capital अक्षरacters in the type.
 * RTR frames are defined as 'r' types - normal frames have 't' type:
 * t => 11 bit data frame
 * r => 11 bit RTR frame
 * T => 29 bit data frame
 * R => 29 bit RTR frame
 *
 * The <id> is 3 (standard) or 8 (extended) bytes in ASCII Hex (base64).
 * The <dlc> is a one byte ASCII number ('0' - '8')
 * The <data> section has at much ASCII Hex bytes as defined by the <dlc>
 *
 * Examples:
 *
 * t1230 : can_id 0x123, len 0, no data
 * t4563112233 : can_id 0x456, len 3, data 0x11 0x22 0x33
 * T12ABCDEF2AA55 : extended can_id 0x12ABCDEF, len 2, data 0xAA 0x55
 * r1230 : can_id 0x123, len 0, no data, remote transmission request
 *
 */

 /************************************************************************
  *			STANDARD SLCAN DECAPSULATION			 *
  ************************************************************************/

/* Send one completely decapsulated can_frame to the network layer */
अटल व्योम slc_bump(काष्ठा slcan *sl)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा can_frame cf;
	पूर्णांक i, पंचांगp;
	u32 पंचांगpid;
	अक्षर *cmd = sl->rbuff;

	स_रखो(&cf, 0, माप(cf));

	चयन (*cmd) अणु
	हाल 'r':
		cf.can_id = CAN_RTR_FLAG;
		fallthrough;
	हाल 't':
		/* store dlc ASCII value and terminate SFF CAN ID string */
		cf.len = sl->rbuff[SLC_CMD_LEN + SLC_SFF_ID_LEN];
		sl->rbuff[SLC_CMD_LEN + SLC_SFF_ID_LEN] = 0;
		/* poपूर्णांक to payload data behind the dlc */
		cmd += SLC_CMD_LEN + SLC_SFF_ID_LEN + 1;
		अवरोध;
	हाल 'R':
		cf.can_id = CAN_RTR_FLAG;
		fallthrough;
	हाल 'T':
		cf.can_id |= CAN_EFF_FLAG;
		/* store dlc ASCII value and terminate EFF CAN ID string */
		cf.len = sl->rbuff[SLC_CMD_LEN + SLC_EFF_ID_LEN];
		sl->rbuff[SLC_CMD_LEN + SLC_EFF_ID_LEN] = 0;
		/* poपूर्णांक to payload data behind the dlc */
		cmd += SLC_CMD_LEN + SLC_EFF_ID_LEN + 1;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	अगर (kstrtou32(sl->rbuff + SLC_CMD_LEN, 16, &पंचांगpid))
		वापस;

	cf.can_id |= पंचांगpid;

	/* get len from sanitized ASCII value */
	अगर (cf.len >= '0' && cf.len < '9')
		cf.len -= '0';
	अन्यथा
		वापस;

	/* RTR frames may have a dlc > 0 but they never have any data bytes */
	अगर (!(cf.can_id & CAN_RTR_FLAG)) अणु
		क्रम (i = 0; i < cf.len; i++) अणु
			पंचांगp = hex_to_bin(*cmd++);
			अगर (पंचांगp < 0)
				वापस;
			cf.data[i] = (पंचांगp << 4);
			पंचांगp = hex_to_bin(*cmd++);
			अगर (पंचांगp < 0)
				वापस;
			cf.data[i] |= पंचांगp;
		पूर्ण
	पूर्ण

	skb = dev_alloc_skb(माप(काष्ठा can_frame) +
			    माप(काष्ठा can_skb_priv));
	अगर (!skb)
		वापस;

	skb->dev = sl->dev;
	skb->protocol = htons(ETH_P_CAN);
	skb->pkt_type = PACKET_BROADCAST;
	skb->ip_summed = CHECKSUM_UNNECESSARY;

	can_skb_reserve(skb);
	can_skb_prv(skb)->अगरindex = sl->dev->अगरindex;
	can_skb_prv(skb)->skbcnt = 0;

	skb_put_data(skb, &cf, माप(काष्ठा can_frame));

	sl->dev->stats.rx_packets++;
	sl->dev->stats.rx_bytes += cf.len;
	netअगर_rx_ni(skb);
पूर्ण

/* parse tty input stream */
अटल व्योम slcan_unesc(काष्ठा slcan *sl, अचिन्हित अक्षर s)
अणु
	अगर ((s == '\r') || (s == '\a')) अणु /* CR or BEL ends the pdu */
		अगर (!test_and_clear_bit(SLF_ERROR, &sl->flags) &&
		    (sl->rcount > 4))  अणु
			slc_bump(sl);
		पूर्ण
		sl->rcount = 0;
	पूर्ण अन्यथा अणु
		अगर (!test_bit(SLF_ERROR, &sl->flags))  अणु
			अगर (sl->rcount < SLC_MTU)  अणु
				sl->rbuff[sl->rcount++] = s;
				वापस;
			पूर्ण अन्यथा अणु
				sl->dev->stats.rx_over_errors++;
				set_bit(SLF_ERROR, &sl->flags);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

 /************************************************************************
  *			STANDARD SLCAN ENCAPSULATION			 *
  ************************************************************************/

/* Encapsulate one can_frame and stuff पूर्णांकo a TTY queue. */
अटल व्योम slc_encaps(काष्ठा slcan *sl, काष्ठा can_frame *cf)
अणु
	पूर्णांक actual, i;
	अचिन्हित अक्षर *pos;
	अचिन्हित अक्षर *endpos;
	canid_t id = cf->can_id;

	pos = sl->xbuff;

	अगर (cf->can_id & CAN_RTR_FLAG)
		*pos = 'R'; /* becomes 'r' in standard frame क्रमmat (SFF) */
	अन्यथा
		*pos = 'T'; /* becomes 't' in standard frame क्रमmat (SSF) */

	/* determine number of अक्षरs क्रम the CAN-identअगरier */
	अगर (cf->can_id & CAN_EFF_FLAG) अणु
		id &= CAN_EFF_MASK;
		endpos = pos + SLC_EFF_ID_LEN;
	पूर्ण अन्यथा अणु
		*pos |= 0x20; /* convert R/T to lower हाल क्रम SFF */
		id &= CAN_SFF_MASK;
		endpos = pos + SLC_SFF_ID_LEN;
	पूर्ण

	/* build 3 (SFF) or 8 (EFF) digit CAN identअगरier */
	pos++;
	जबतक (endpos >= pos) अणु
		*endpos-- = hex_asc_upper[id & 0xf];
		id >>= 4;
	पूर्ण

	pos += (cf->can_id & CAN_EFF_FLAG) ? SLC_EFF_ID_LEN : SLC_SFF_ID_LEN;

	*pos++ = cf->len + '0';

	/* RTR frames may have a dlc > 0 but they never have any data bytes */
	अगर (!(cf->can_id & CAN_RTR_FLAG)) अणु
		क्रम (i = 0; i < cf->len; i++)
			pos = hex_byte_pack_upper(pos, cf->data[i]);
	पूर्ण

	*pos++ = '\r';

	/* Order of next two lines is *very* important.
	 * When we are sending a little amount of data,
	 * the transfer may be completed inside the ops->ग_लिखो()
	 * routine, because it's running with पूर्णांकerrupts enabled.
	 * In this हाल we *never* got WRITE_WAKEUP event,
	 * अगर we did not request it beक्रमe ग_लिखो operation.
	 *       14 Oct 1994  Dmitry Gorodchanin.
	 */
	set_bit(TTY_DO_WRITE_WAKEUP, &sl->tty->flags);
	actual = sl->tty->ops->ग_लिखो(sl->tty, sl->xbuff, pos - sl->xbuff);
	sl->xleft = (pos - sl->xbuff) - actual;
	sl->xhead = sl->xbuff + actual;
	sl->dev->stats.tx_bytes += cf->len;
पूर्ण

/* Write out any reमुख्यing transmit buffer. Scheduled when tty is writable */
अटल व्योम slcan_transmit(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा slcan *sl = container_of(work, काष्ठा slcan, tx_work);
	पूर्णांक actual;

	spin_lock_bh(&sl->lock);
	/* First make sure we're connected. */
	अगर (!sl->tty || sl->magic != SLCAN_MAGIC || !netअगर_running(sl->dev)) अणु
		spin_unlock_bh(&sl->lock);
		वापस;
	पूर्ण

	अगर (sl->xleft <= 0)  अणु
		/* Now serial buffer is almost मुक्त & we can start
		 * transmission of another packet */
		sl->dev->stats.tx_packets++;
		clear_bit(TTY_DO_WRITE_WAKEUP, &sl->tty->flags);
		spin_unlock_bh(&sl->lock);
		netअगर_wake_queue(sl->dev);
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
अटल व्योम slcan_ग_लिखो_wakeup(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा slcan *sl;

	rcu_पढ़ो_lock();
	sl = rcu_dereference(tty->disc_data);
	अगर (sl)
		schedule_work(&sl->tx_work);
	rcu_पढ़ो_unlock();
पूर्ण

/* Send a can_frame to a TTY queue. */
अटल netdev_tx_t slc_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा slcan *sl = netdev_priv(dev);

	अगर (skb->len != CAN_MTU)
		जाओ out;

	spin_lock(&sl->lock);
	अगर (!netअगर_running(dev))  अणु
		spin_unlock(&sl->lock);
		prपूर्णांकk(KERN_WARNING "%s: xmit: iface is down\n", dev->name);
		जाओ out;
	पूर्ण
	अगर (sl->tty == शून्य) अणु
		spin_unlock(&sl->lock);
		जाओ out;
	पूर्ण

	netअगर_stop_queue(sl->dev);
	slc_encaps(sl, (काष्ठा can_frame *) skb->data); /* encaps & send */
	spin_unlock(&sl->lock);

out:
	kमुक्त_skb(skb);
	वापस NETDEV_TX_OK;
पूर्ण


/******************************************
 *   Routines looking at netdevice side.
 ******************************************/

/* Netdevice UP -> DOWN routine */
अटल पूर्णांक slc_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा slcan *sl = netdev_priv(dev);

	spin_lock_bh(&sl->lock);
	अगर (sl->tty) अणु
		/* TTY discipline is running. */
		clear_bit(TTY_DO_WRITE_WAKEUP, &sl->tty->flags);
	पूर्ण
	netअगर_stop_queue(dev);
	sl->rcount   = 0;
	sl->xleft    = 0;
	spin_unlock_bh(&sl->lock);

	वापस 0;
पूर्ण

/* Netdevice DOWN -> UP routine */
अटल पूर्णांक slc_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा slcan *sl = netdev_priv(dev);

	अगर (sl->tty == शून्य)
		वापस -ENODEV;

	sl->flags &= (1 << SLF_INUSE);
	netअगर_start_queue(dev);
	वापस 0;
पूर्ण

/* Hook the deकाष्ठाor so we can मुक्त slcan devs at the right poपूर्णांक in समय */
अटल व्योम slc_मुक्त_netdev(काष्ठा net_device *dev)
अणु
	पूर्णांक i = dev->base_addr;

	slcan_devs[i] = शून्य;
पूर्ण

अटल पूर्णांक slcan_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा net_device_ops slc_netdev_ops = अणु
	.nकरो_खोलो               = slc_खोलो,
	.nकरो_stop               = slc_बंद,
	.nकरो_start_xmit         = slc_xmit,
	.nकरो_change_mtu         = slcan_change_mtu,
पूर्ण;

अटल व्योम slc_setup(काष्ठा net_device *dev)
अणु
	dev->netdev_ops		= &slc_netdev_ops;
	dev->needs_मुक्त_netdev	= true;
	dev->priv_deकाष्ठाor	= slc_मुक्त_netdev;

	dev->hard_header_len	= 0;
	dev->addr_len		= 0;
	dev->tx_queue_len	= 10;

	dev->mtu		= CAN_MTU;
	dev->type		= ARPHRD_CAN;

	/* New-style flags. */
	dev->flags		= IFF_NOARP;
	dev->features           = NETIF_F_HW_CSUM;
पूर्ण

/******************************************
  Routines looking at TTY side.
 ******************************************/

/*
 * Handle the 'receiver data ready' पूर्णांकerrupt.
 * This function is called by the 'tty_io' module in the kernel when
 * a block of SLCAN data has been received, which can now be decapsulated
 * and sent on to some IP layer क्रम further processing. This will not
 * be re-entered जबतक running but other ldisc functions may be called
 * in parallel
 */

अटल व्योम slcan_receive_buf(काष्ठा tty_काष्ठा *tty,
			      स्थिर अचिन्हित अक्षर *cp, अक्षर *fp, पूर्णांक count)
अणु
	काष्ठा slcan *sl = (काष्ठा slcan *) tty->disc_data;

	अगर (!sl || sl->magic != SLCAN_MAGIC || !netअगर_running(sl->dev))
		वापस;

	/* Read the अक्षरacters out of the buffer */
	जबतक (count--) अणु
		अगर (fp && *fp++) अणु
			अगर (!test_and_set_bit(SLF_ERROR, &sl->flags))
				sl->dev->stats.rx_errors++;
			cp++;
			जारी;
		पूर्ण
		slcan_unesc(sl, *cp++);
	पूर्ण
पूर्ण

/************************************
 *  slcan_खोलो helper routines.
 ************************************/

/* Collect hanged up channels */
अटल व्योम slc_sync(व्योम)
अणु
	पूर्णांक i;
	काष्ठा net_device *dev;
	काष्ठा slcan	  *sl;

	क्रम (i = 0; i < maxdev; i++) अणु
		dev = slcan_devs[i];
		अगर (dev == शून्य)
			अवरोध;

		sl = netdev_priv(dev);
		अगर (sl->tty)
			जारी;
		अगर (dev->flags & IFF_UP)
			dev_बंद(dev);
	पूर्ण
पूर्ण

/* Find a मुक्त SLCAN channel, and link in this `tty' line. */
अटल काष्ठा slcan *slc_alloc(व्योम)
अणु
	पूर्णांक i;
	अक्षर name[IFNAMSIZ];
	काष्ठा net_device *dev = शून्य;
	काष्ठा can_ml_priv *can_ml;
	काष्ठा slcan       *sl;
	पूर्णांक size;

	क्रम (i = 0; i < maxdev; i++) अणु
		dev = slcan_devs[i];
		अगर (dev == शून्य)
			अवरोध;

	पूर्ण

	/* Sorry, too many, all slots in use */
	अगर (i >= maxdev)
		वापस शून्य;

	प्र_लिखो(name, "slcan%d", i);
	size = ALIGN(माप(*sl), NETDEV_ALIGN) + माप(काष्ठा can_ml_priv);
	dev = alloc_netdev(size, name, NET_NAME_UNKNOWN, slc_setup);
	अगर (!dev)
		वापस शून्य;

	dev->base_addr  = i;
	sl = netdev_priv(dev);
	can_ml = (व्योम *)sl + ALIGN(माप(*sl), NETDEV_ALIGN);
	can_set_ml_priv(dev, can_ml);

	/* Initialize channel control data */
	sl->magic = SLCAN_MAGIC;
	sl->dev	= dev;
	spin_lock_init(&sl->lock);
	INIT_WORK(&sl->tx_work, slcan_transmit);
	slcan_devs[i] = dev;

	वापस sl;
पूर्ण

/*
 * Open the high-level part of the SLCAN channel.
 * This function is called by the TTY module when the
 * SLCAN line discipline is called क्रम.  Because we are
 * sure the tty line exists, we only have to link it to
 * a मुक्त SLCAN channel...
 *
 * Called in process context serialized from other ldisc calls.
 */

अटल पूर्णांक slcan_खोलो(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा slcan *sl;
	पूर्णांक err;

	अगर (!capable(CAP_NET_ADMIN))
		वापस -EPERM;

	अगर (tty->ops->ग_लिखो == शून्य)
		वापस -EOPNOTSUPP;

	/* RTnetlink lock is misused here to serialize concurrent
	   खोलोs of slcan channels. There are better ways, but it is
	   the simplest one.
	 */
	rtnl_lock();

	/* Collect hanged up channels. */
	slc_sync();

	sl = tty->disc_data;

	err = -EEXIST;
	/* First make sure we're not alपढ़ोy connected. */
	अगर (sl && sl->magic == SLCAN_MAGIC)
		जाओ err_निकास;

	/* OK.  Find a मुक्त SLCAN channel to use. */
	err = -ENखाता;
	sl = slc_alloc();
	अगर (sl == शून्य)
		जाओ err_निकास;

	sl->tty = tty;
	tty->disc_data = sl;

	अगर (!test_bit(SLF_INUSE, &sl->flags)) अणु
		/* Perक्रमm the low-level SLCAN initialization. */
		sl->rcount   = 0;
		sl->xleft    = 0;

		set_bit(SLF_INUSE, &sl->flags);

		err = रेजिस्टर_netdevice(sl->dev);
		अगर (err)
			जाओ err_मुक्त_chan;
	पूर्ण

	/* Done.  We have linked the TTY line to a channel. */
	rtnl_unlock();
	tty->receive_room = 65536;	/* We करोn't flow control */

	/* TTY layer expects 0 on success */
	वापस 0;

err_मुक्त_chan:
	sl->tty = शून्य;
	tty->disc_data = शून्य;
	clear_bit(SLF_INUSE, &sl->flags);
	slc_मुक्त_netdev(sl->dev);
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
 * Close करोwn a SLCAN channel.
 * This means flushing out any pending queues, and then वापसing. This
 * call is serialized against other ldisc functions.
 *
 * We also use this method क्रम a hangup event.
 */

अटल व्योम slcan_बंद(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा slcan *sl = (काष्ठा slcan *) tty->disc_data;

	/* First make sure we're connected. */
	अगर (!sl || sl->magic != SLCAN_MAGIC || sl->tty != tty)
		वापस;

	spin_lock_bh(&sl->lock);
	rcu_assign_poपूर्णांकer(tty->disc_data, शून्य);
	sl->tty = शून्य;
	spin_unlock_bh(&sl->lock);

	synchronize_rcu();
	flush_work(&sl->tx_work);

	/* Flush network side */
	unरेजिस्टर_netdev(sl->dev);
	/* This will complete via sl_मुक्त_netdev */
पूर्ण

अटल पूर्णांक slcan_hangup(काष्ठा tty_काष्ठा *tty)
अणु
	slcan_बंद(tty);
	वापस 0;
पूर्ण

/* Perक्रमm I/O control on an active SLCAN channel. */
अटल पूर्णांक slcan_ioctl(काष्ठा tty_काष्ठा *tty, काष्ठा file *file,
		       अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा slcan *sl = (काष्ठा slcan *) tty->disc_data;
	अचिन्हित पूर्णांक पंचांगp;

	/* First make sure we're connected. */
	अगर (!sl || sl->magic != SLCAN_MAGIC)
		वापस -EINVAL;

	चयन (cmd) अणु
	हाल SIOCGIFNAME:
		पंचांगp = म_माप(sl->dev->name) + 1;
		अगर (copy_to_user((व्योम __user *)arg, sl->dev->name, पंचांगp))
			वापस -EFAULT;
		वापस 0;

	हाल SIOCSIFHWADDR:
		वापस -EINVAL;

	शेष:
		वापस tty_mode_ioctl(tty, file, cmd, arg);
	पूर्ण
पूर्ण

अटल काष्ठा tty_ldisc_ops slc_ldisc = अणु
	.owner		= THIS_MODULE,
	.name		= "slcan",
	.खोलो		= slcan_खोलो,
	.बंद		= slcan_बंद,
	.hangup		= slcan_hangup,
	.ioctl		= slcan_ioctl,
	.receive_buf	= slcan_receive_buf,
	.ग_लिखो_wakeup	= slcan_ग_लिखो_wakeup,
पूर्ण;

अटल पूर्णांक __init slcan_init(व्योम)
अणु
	पूर्णांक status;

	अगर (maxdev < 4)
		maxdev = 4; /* Sanity */

	pr_info("slcan: serial line CAN interface driver\n");
	pr_info("slcan: %d dynamic interface channels.\n", maxdev);

	slcan_devs = kसुस्मृति(maxdev, माप(काष्ठा net_device *), GFP_KERNEL);
	अगर (!slcan_devs)
		वापस -ENOMEM;

	/* Fill in our line protocol discipline, and रेजिस्टर it */
	status = tty_रेजिस्टर_ldisc(N_SLCAN, &slc_ldisc);
	अगर (status)  अणु
		prपूर्णांकk(KERN_ERR "slcan: can't register line discipline\n");
		kमुक्त(slcan_devs);
	पूर्ण
	वापस status;
पूर्ण

अटल व्योम __निकास slcan_निकास(व्योम)
अणु
	पूर्णांक i;
	काष्ठा net_device *dev;
	काष्ठा slcan *sl;
	अचिन्हित दीर्घ समयout = jअगरfies + HZ;
	पूर्णांक busy = 0;

	अगर (slcan_devs == शून्य)
		वापस;

	/* First of all: check क्रम active disciplines and hangup them.
	 */
	करो अणु
		अगर (busy)
			msleep_पूर्णांकerruptible(100);

		busy = 0;
		क्रम (i = 0; i < maxdev; i++) अणु
			dev = slcan_devs[i];
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

	क्रम (i = 0; i < maxdev; i++) अणु
		dev = slcan_devs[i];
		अगर (!dev)
			जारी;
		slcan_devs[i] = शून्य;

		sl = netdev_priv(dev);
		अगर (sl->tty) अणु
			prपूर्णांकk(KERN_ERR "%s: tty discipline still running\n",
			       dev->name);
		पूर्ण

		unरेजिस्टर_netdev(dev);
	पूर्ण

	kमुक्त(slcan_devs);
	slcan_devs = शून्य;

	i = tty_unरेजिस्टर_ldisc(N_SLCAN);
	अगर (i)
		prपूर्णांकk(KERN_ERR "slcan: can't unregister ldisc (err %d)\n", i);
पूर्ण

module_init(slcan_init);
module_निकास(slcan_निकास);
