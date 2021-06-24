<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Copyright (C) Hans Alblas PE1AYX <hans@esrac.ele.tue.nl>
 * Copyright (C) 2004, 05 Ralf Baechle DL5RB <ralf@linux-mips.org>
 * Copyright (C) 2004, 05 Thomas Osterried DL9SAU <thomas@x-berg.in-berlin.de>
 */
#समावेश <linux/module.h>
#समावेश <linux/bitops.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/crc16.h>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/in.h>
#समावेश <linux/inet.h>
#समावेश <linux/slab.h>
#समावेश <linux/tty.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/netdevice.h>
#समावेश <linux/major.h>
#समावेश <linux/init.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/refcount.h>

#समावेश <net/ax25.h>

#घोषणा AX_MTU		236

/* SLIP/KISS protocol अक्षरacters. */
#घोषणा END             0300		/* indicates end of frame	*/
#घोषणा ESC             0333		/* indicates byte stuffing	*/
#घोषणा ESC_END         0334		/* ESC ESC_END means END 'data'	*/
#घोषणा ESC_ESC         0335		/* ESC ESC_ESC means ESC 'data'	*/

काष्ठा mkiss अणु
	काष्ठा tty_काष्ठा	*tty;	/* ptr to TTY काष्ठाure		*/
	काष्ठा net_device	*dev;	/* easy क्रम पूर्णांकr handling	*/

	/* These are poपूर्णांकers to the दो_स्मृति()ed frame buffers. */
	spinlock_t		buflock;/* lock क्रम rbuf and xbuf */
	अचिन्हित अक्षर		*rbuff;	/* receiver buffer		*/
	पूर्णांक			rcount;	/* received अक्षरs counter       */
	अचिन्हित अक्षर		*xbuff;	/* transmitter buffer		*/
	अचिन्हित अक्षर		*xhead;	/* poपूर्णांकer to next byte to XMIT */
	पूर्णांक			xleft;	/* bytes left in XMIT queue     */

	/* Detailed SLIP statistics. */
	पूर्णांक		mtu;		/* Our mtu (to spot changes!)   */
	पूर्णांक		buffsize;	/* Max buffers sizes            */

	अचिन्हित दीर्घ	flags;		/* Flag values/ mode etc	*/
					/* दीर्घ req'd: used by set_bit --RR */
#घोषणा AXF_INUSE	0		/* Channel in use               */
#घोषणा AXF_ESCAPE	1               /* ESC received                 */
#घोषणा AXF_ERROR	2               /* Parity, etc. error           */
#घोषणा AXF_KEEPTEST	3		/* Keepalive test flag		*/
#घोषणा AXF_OUTWAIT	4		/* is outpacket was flag	*/

	पूर्णांक		mode;
        पूर्णांक		crcmode;	/* MW: क्रम FlexNet, SMACK etc.  */
	पूर्णांक		crcस्वतः;	/* CRC स्वतः mode */

#घोषणा CRC_MODE_NONE		0
#घोषणा CRC_MODE_FLEX		1
#घोषणा CRC_MODE_SMACK		2
#घोषणा CRC_MODE_FLEX_TEST	3
#घोषणा CRC_MODE_SMACK_TEST	4

	refcount_t		refcnt;
	काष्ठा completion	dead;
पूर्ण;

/*---------------------------------------------------------------------------*/

अटल स्थिर अचिन्हित लघु crc_flex_table[] = अणु
	0x0f87, 0x1e0e, 0x2c95, 0x3d1c, 0x49a3, 0x582a, 0x6ab1, 0x7b38,
	0x83cf, 0x9246, 0xa0dd, 0xb154, 0xc5eb, 0xd462, 0xe6f9, 0xf770,
	0x1f06, 0x0e8f, 0x3c14, 0x2d9d, 0x5922, 0x48ab, 0x7a30, 0x6bb9,
	0x934e, 0x82c7, 0xb05c, 0xa1d5, 0xd56a, 0xc4e3, 0xf678, 0xe7f1,
	0x2e85, 0x3f0c, 0x0d97, 0x1c1e, 0x68a1, 0x7928, 0x4bb3, 0x5a3a,
	0xa2cd, 0xb344, 0x81df, 0x9056, 0xe4e9, 0xf560, 0xc7fb, 0xd672,
	0x3e04, 0x2f8d, 0x1d16, 0x0c9f, 0x7820, 0x69a9, 0x5b32, 0x4abb,
	0xb24c, 0xa3c5, 0x915e, 0x80d7, 0xf468, 0xe5e1, 0xd77a, 0xc6f3,
	0x4d83, 0x5c0a, 0x6e91, 0x7f18, 0x0ba7, 0x1a2e, 0x28b5, 0x393c,
	0xc1cb, 0xd042, 0xe2d9, 0xf350, 0x87ef, 0x9666, 0xa4fd, 0xb574,
	0x5d02, 0x4c8b, 0x7e10, 0x6f99, 0x1b26, 0x0aaf, 0x3834, 0x29bd,
	0xd14a, 0xc0c3, 0xf258, 0xe3d1, 0x976e, 0x86e7, 0xb47c, 0xa5f5,
	0x6c81, 0x7d08, 0x4f93, 0x5e1a, 0x2aa5, 0x3b2c, 0x09b7, 0x183e,
	0xe0c9, 0xf140, 0xc3db, 0xd252, 0xa6ed, 0xb764, 0x85ff, 0x9476,
	0x7c00, 0x6d89, 0x5f12, 0x4e9b, 0x3a24, 0x2bad, 0x1936, 0x08bf,
	0xf048, 0xe1c1, 0xd35a, 0xc2d3, 0xb66c, 0xa7e5, 0x957e, 0x84f7,
	0x8b8f, 0x9a06, 0xa89d, 0xb914, 0xcdab, 0xdc22, 0xeeb9, 0xff30,
	0x07c7, 0x164e, 0x24d5, 0x355c, 0x41e3, 0x506a, 0x62f1, 0x7378,
	0x9b0e, 0x8a87, 0xb81c, 0xa995, 0xdd2a, 0xcca3, 0xfe38, 0xefb1,
	0x1746, 0x06cf, 0x3454, 0x25dd, 0x5162, 0x40eb, 0x7270, 0x63f9,
	0xaa8d, 0xbb04, 0x899f, 0x9816, 0xeca9, 0xfd20, 0xcfbb, 0xde32,
	0x26c5, 0x374c, 0x05d7, 0x145e, 0x60e1, 0x7168, 0x43f3, 0x527a,
	0xba0c, 0xab85, 0x991e, 0x8897, 0xfc28, 0xeda1, 0xdf3a, 0xceb3,
	0x3644, 0x27cd, 0x1556, 0x04df, 0x7060, 0x61e9, 0x5372, 0x42fb,
	0xc98b, 0xd802, 0xea99, 0xfb10, 0x8faf, 0x9e26, 0xacbd, 0xbd34,
	0x45c3, 0x544a, 0x66d1, 0x7758, 0x03e7, 0x126e, 0x20f5, 0x317c,
	0xd90a, 0xc883, 0xfa18, 0xeb91, 0x9f2e, 0x8ea7, 0xbc3c, 0xadb5,
	0x5542, 0x44cb, 0x7650, 0x67d9, 0x1366, 0x02ef, 0x3074, 0x21fd,
	0xe889, 0xf900, 0xcb9b, 0xda12, 0xaead, 0xbf24, 0x8dbf, 0x9c36,
	0x64c1, 0x7548, 0x47d3, 0x565a, 0x22e5, 0x336c, 0x01f7, 0x107e,
	0xf808, 0xe981, 0xdb1a, 0xca93, 0xbe2c, 0xafa5, 0x9d3e, 0x8cb7,
	0x7440, 0x65c9, 0x5752, 0x46db, 0x3264, 0x23ed, 0x1176, 0x00ff
पूर्ण;

अटल अचिन्हित लघु calc_crc_flex(अचिन्हित अक्षर *cp, पूर्णांक size)
अणु
	अचिन्हित लघु crc = 0xffff;

	जबतक (size--)
		crc = (crc << 8) ^ crc_flex_table[((crc >> 8) ^ *cp++) & 0xff];

	वापस crc;
पूर्ण

अटल पूर्णांक check_crc_flex(अचिन्हित अक्षर *cp, पूर्णांक size)
अणु
	अचिन्हित लघु crc = 0xffff;

	अगर (size < 3)
		वापस -1;

	जबतक (size--)
		crc = (crc << 8) ^ crc_flex_table[((crc >> 8) ^ *cp++) & 0xff];

	अगर ((crc & 0xffff) != 0x7070)
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक check_crc_16(अचिन्हित अक्षर *cp, पूर्णांक size)
अणु
	अचिन्हित लघु crc = 0x0000;

	अगर (size < 3)
		वापस -1;

	crc = crc16(0, cp, size);

	अगर (crc != 0x0000)
		वापस -1;

	वापस 0;
पूर्ण

/*
 * Standard encapsulation
 */

अटल पूर्णांक kiss_esc(अचिन्हित अक्षर *s, अचिन्हित अक्षर *d, पूर्णांक len)
अणु
	अचिन्हित अक्षर *ptr = d;
	अचिन्हित अक्षर c;

	/*
	 * Send an initial END अक्षरacter to flush out any data that may have
	 * accumulated in the receiver due to line noise.
	 */

	*ptr++ = END;

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

/*
 * MW:
 * OK its ugly, but tell me a better solution without copying the
 * packet to a temporary buffer :-)
 */
अटल पूर्णांक kiss_esc_crc(अचिन्हित अक्षर *s, अचिन्हित अक्षर *d, अचिन्हित लघु crc,
	पूर्णांक len)
अणु
	अचिन्हित अक्षर *ptr = d;
	अचिन्हित अक्षर c=0;

	*ptr++ = END;
	जबतक (len > 0) अणु
		अगर (len > 2)
			c = *s++;
		अन्यथा अगर (len > 1)
			c = crc >> 8;
		अन्यथा
			c = crc & 0xff;

		len--;

		चयन (c) अणु
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

/* Send one completely decapsulated AX.25 packet to the AX.25 layer. */
अटल व्योम ax_bump(काष्ठा mkiss *ax)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक count;

	spin_lock_bh(&ax->buflock);
	अगर (ax->rbuff[0] > 0x0f) अणु
		अगर (ax->rbuff[0] & 0x80) अणु
			अगर (check_crc_16(ax->rbuff, ax->rcount) < 0) अणु
				ax->dev->stats.rx_errors++;
				spin_unlock_bh(&ax->buflock);

				वापस;
			पूर्ण
			अगर (ax->crcmode != CRC_MODE_SMACK && ax->crcस्वतः) अणु
				prपूर्णांकk(KERN_INFO
				       "mkiss: %s: Switching to crc-smack\n",
				       ax->dev->name);
				ax->crcmode = CRC_MODE_SMACK;
			पूर्ण
			ax->rcount -= 2;
			*ax->rbuff &= ~0x80;
		पूर्ण अन्यथा अगर (ax->rbuff[0] & 0x20)  अणु
			अगर (check_crc_flex(ax->rbuff, ax->rcount) < 0) अणु
				ax->dev->stats.rx_errors++;
				spin_unlock_bh(&ax->buflock);
				वापस;
			पूर्ण
			अगर (ax->crcmode != CRC_MODE_FLEX && ax->crcस्वतः) अणु
				prपूर्णांकk(KERN_INFO
				       "mkiss: %s: Switching to crc-flexnet\n",
				       ax->dev->name);
				ax->crcmode = CRC_MODE_FLEX;
			पूर्ण
			ax->rcount -= 2;

			/*
			 * dl9sau bugfix: the trailling two bytes flexnet crc
			 * will not be passed to the kernel. thus we have to
			 * correct the kissparm signature, because it indicates
			 * a crc but there's none
			 */
			*ax->rbuff &= ~0x20;
		पूर्ण
 	पूर्ण

	count = ax->rcount;

	अगर ((skb = dev_alloc_skb(count)) == शून्य) अणु
		prपूर्णांकk(KERN_ERR "mkiss: %s: memory squeeze, dropping packet.\n",
		       ax->dev->name);
		ax->dev->stats.rx_dropped++;
		spin_unlock_bh(&ax->buflock);
		वापस;
	पूर्ण

	skb_put_data(skb, ax->rbuff, count);
	skb->protocol = ax25_type_trans(skb, ax->dev);
	netअगर_rx(skb);
	ax->dev->stats.rx_packets++;
	ax->dev->stats.rx_bytes += count;
	spin_unlock_bh(&ax->buflock);
पूर्ण

अटल व्योम kiss_unesc(काष्ठा mkiss *ax, अचिन्हित अक्षर s)
अणु
	चयन (s) अणु
	हाल END:
		/* drop keeptest bit = VSV */
		अगर (test_bit(AXF_KEEPTEST, &ax->flags))
			clear_bit(AXF_KEEPTEST, &ax->flags);

		अगर (!test_and_clear_bit(AXF_ERROR, &ax->flags) && (ax->rcount > 2))
			ax_bump(ax);

		clear_bit(AXF_ESCAPE, &ax->flags);
		ax->rcount = 0;
		वापस;

	हाल ESC:
		set_bit(AXF_ESCAPE, &ax->flags);
		वापस;
	हाल ESC_ESC:
		अगर (test_and_clear_bit(AXF_ESCAPE, &ax->flags))
			s = ESC;
		अवरोध;
	हाल ESC_END:
		अगर (test_and_clear_bit(AXF_ESCAPE, &ax->flags))
			s = END;
		अवरोध;
	पूर्ण

	spin_lock_bh(&ax->buflock);
	अगर (!test_bit(AXF_ERROR, &ax->flags)) अणु
		अगर (ax->rcount < ax->buffsize) अणु
			ax->rbuff[ax->rcount++] = s;
			spin_unlock_bh(&ax->buflock);
			वापस;
		पूर्ण

		ax->dev->stats.rx_over_errors++;
		set_bit(AXF_ERROR, &ax->flags);
	पूर्ण
	spin_unlock_bh(&ax->buflock);
पूर्ण

अटल पूर्णांक ax_set_mac_address(काष्ठा net_device *dev, व्योम *addr)
अणु
	काष्ठा sockaddr_ax25 *sa = addr;

	netअगर_tx_lock_bh(dev);
	netअगर_addr_lock(dev);
	स_नकल(dev->dev_addr, &sa->sax25_call, AX25_ADDR_LEN);
	netअगर_addr_unlock(dev);
	netअगर_tx_unlock_bh(dev);

	वापस 0;
पूर्ण

/*---------------------------------------------------------------------------*/

अटल व्योम ax_changedmtu(काष्ठा mkiss *ax)
अणु
	काष्ठा net_device *dev = ax->dev;
	अचिन्हित अक्षर *xbuff, *rbuff, *oxbuff, *orbuff;
	पूर्णांक len;

	len = dev->mtu * 2;

	/*
	 * allow क्रम arrival of larger UDP packets, even अगर we say not to
	 * also fixes a bug in which SunOS sends 512-byte packets even with
	 * an MSS of 128
	 */
	अगर (len < 576 * 2)
		len = 576 * 2;

	xbuff = kदो_स्मृति(len + 4, GFP_ATOMIC);
	rbuff = kदो_स्मृति(len + 4, GFP_ATOMIC);

	अगर (xbuff == शून्य || rbuff == शून्य)  अणु
		prपूर्णांकk(KERN_ERR "mkiss: %s: unable to grow ax25 buffers, "
		       "MTU change cancelled.\n",
		       ax->dev->name);
		dev->mtu = ax->mtu;
		kमुक्त(xbuff);
		kमुक्त(rbuff);
		वापस;
	पूर्ण

	spin_lock_bh(&ax->buflock);

	oxbuff    = ax->xbuff;
	ax->xbuff = xbuff;
	orbuff    = ax->rbuff;
	ax->rbuff = rbuff;

	अगर (ax->xleft) अणु
		अगर (ax->xleft <= len) अणु
			स_नकल(ax->xbuff, ax->xhead, ax->xleft);
		पूर्ण अन्यथा  अणु
			ax->xleft = 0;
			dev->stats.tx_dropped++;
		पूर्ण
	पूर्ण

	ax->xhead = ax->xbuff;

	अगर (ax->rcount) अणु
		अगर (ax->rcount <= len) अणु
			स_नकल(ax->rbuff, orbuff, ax->rcount);
		पूर्ण अन्यथा  अणु
			ax->rcount = 0;
			dev->stats.rx_over_errors++;
			set_bit(AXF_ERROR, &ax->flags);
		पूर्ण
	पूर्ण

	ax->mtu      = dev->mtu + 73;
	ax->buffsize = len;

	spin_unlock_bh(&ax->buflock);

	kमुक्त(oxbuff);
	kमुक्त(orbuff);
पूर्ण

/* Encapsulate one AX.25 packet and stuff पूर्णांकo a TTY queue. */
अटल व्योम ax_encaps(काष्ठा net_device *dev, अचिन्हित अक्षर *icp, पूर्णांक len)
अणु
	काष्ठा mkiss *ax = netdev_priv(dev);
	अचिन्हित अक्षर *p;
	पूर्णांक actual, count;

	अगर (ax->mtu != ax->dev->mtu + 73)	/* Someone has been अगरconfigging */
		ax_changedmtu(ax);

	अगर (len > ax->mtu) अणु		/* Sigh, shouldn't occur BUT ... */
		prपूर्णांकk(KERN_ERR "mkiss: %s: truncating oversized transmit packet!\n", ax->dev->name);
		dev->stats.tx_dropped++;
		netअगर_start_queue(dev);
		वापस;
	पूर्ण

	p = icp;

	spin_lock_bh(&ax->buflock);
	अगर ((*p & 0x0f) != 0) अणु
		/* Configuration Command (kissparms(1).
		 * Protocol spec says: never append CRC.
		 * This fixes a very old bug in the linux
		 * kiss driver. -- dl9sau */
		चयन (*p & 0xff) अणु
		हाल 0x85:
			/* command from userspace especially क्रम us,
			 * not क्रम delivery to the tnc */
			अगर (len > 1) अणु
				पूर्णांक cmd = (p[1] & 0xff);
				चयन(cmd) अणु
				हाल 3:
				  ax->crcmode = CRC_MODE_SMACK;
				  अवरोध;
				हाल 2:
				  ax->crcmode = CRC_MODE_FLEX;
				  अवरोध;
				हाल 1:
				  ax->crcmode = CRC_MODE_NONE;
				  अवरोध;
				हाल 0:
				शेष:
				  ax->crcmode = CRC_MODE_SMACK_TEST;
				  cmd = 0;
				पूर्ण
				ax->crcस्वतः = (cmd ? 0 : 1);
				prपूर्णांकk(KERN_INFO "mkiss: %s: crc mode set to %d\n",
				       ax->dev->name, cmd);
			पूर्ण
			spin_unlock_bh(&ax->buflock);
			netअगर_start_queue(dev);

			वापस;
		शेष:
			count = kiss_esc(p, ax->xbuff, len);
		पूर्ण
	पूर्ण अन्यथा अणु
		अचिन्हित लघु crc;
		चयन (ax->crcmode) अणु
		हाल CRC_MODE_SMACK_TEST:
			ax->crcmode  = CRC_MODE_FLEX_TEST;
			prपूर्णांकk(KERN_INFO "mkiss: %s: Trying crc-smack\n", ax->dev->name);
			fallthrough;
		हाल CRC_MODE_SMACK:
			*p |= 0x80;
			crc = swab16(crc16(0, p, len));
			count = kiss_esc_crc(p, ax->xbuff, crc, len+2);
			अवरोध;
		हाल CRC_MODE_FLEX_TEST:
			ax->crcmode = CRC_MODE_NONE;
			prपूर्णांकk(KERN_INFO "mkiss: %s: Trying crc-flexnet\n", ax->dev->name);
			fallthrough;
		हाल CRC_MODE_FLEX:
			*p |= 0x20;
			crc = calc_crc_flex(p, len);
			count = kiss_esc_crc(p, ax->xbuff, crc, len+2);
			अवरोध;

		शेष:
			count = kiss_esc(p, ax->xbuff, len);
		पूर्ण
  	पूर्ण
	spin_unlock_bh(&ax->buflock);

	set_bit(TTY_DO_WRITE_WAKEUP, &ax->tty->flags);
	actual = ax->tty->ops->ग_लिखो(ax->tty, ax->xbuff, count);
	dev->stats.tx_packets++;
	dev->stats.tx_bytes += actual;

	netअगर_trans_update(ax->dev);
	ax->xleft = count - actual;
	ax->xhead = ax->xbuff + actual;
पूर्ण

/* Encapsulate an AX.25 packet and kick it पूर्णांकo a TTY queue. */
अटल netdev_tx_t ax_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा mkiss *ax = netdev_priv(dev);

	अगर (skb->protocol == htons(ETH_P_IP))
		वापस ax25_ip_xmit(skb);

	अगर (!netअगर_running(dev))  अणु
		prपूर्णांकk(KERN_ERR "mkiss: %s: xmit call when iface is down\n", dev->name);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	अगर (netअगर_queue_stopped(dev)) अणु
		/*
		 * May be we must check transmitter समयout here ?
		 *      14 Oct 1994 Dmitry Gorodchanin.
		 */
		अगर (समय_beक्रमe(jअगरfies, dev_trans_start(dev) + 20 * HZ)) अणु
			/* 20 sec समयout not reached */
			वापस NETDEV_TX_BUSY;
		पूर्ण

		prपूर्णांकk(KERN_ERR "mkiss: %s: transmit timed out, %s?\n", dev->name,
		       (tty_अक्षरs_in_buffer(ax->tty) || ax->xleft) ?
		       "bad line quality" : "driver error");

		ax->xleft = 0;
		clear_bit(TTY_DO_WRITE_WAKEUP, &ax->tty->flags);
		netअगर_start_queue(dev);
	पूर्ण

	/* We were not busy, so we are now... :-) */
	netअगर_stop_queue(dev);
	ax_encaps(dev, skb->data, skb->len);
	kमुक्त_skb(skb);

	वापस NETDEV_TX_OK;
पूर्ण

अटल पूर्णांक ax_खोलो_dev(काष्ठा net_device *dev)
अणु
	काष्ठा mkiss *ax = netdev_priv(dev);

	अगर (ax->tty == शून्य)
		वापस -ENODEV;

	वापस 0;
पूर्ण

/* Open the low-level part of the AX25 channel. Easy! */
अटल पूर्णांक ax_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा mkiss *ax = netdev_priv(dev);
	अचिन्हित दीर्घ len;

	अगर (ax->tty == शून्य)
		वापस -ENODEV;

	/*
	 * Allocate the frame buffers:
	 *
	 * rbuff	Receive buffer.
	 * xbuff	Transmit buffer.
	 */
	len = dev->mtu * 2;

	/*
	 * allow क्रम arrival of larger UDP packets, even अगर we say not to
	 * also fixes a bug in which SunOS sends 512-byte packets even with
	 * an MSS of 128
	 */
	अगर (len < 576 * 2)
		len = 576 * 2;

	अगर ((ax->rbuff = kदो_स्मृति(len + 4, GFP_KERNEL)) == शून्य)
		जाओ norbuff;

	अगर ((ax->xbuff = kदो_स्मृति(len + 4, GFP_KERNEL)) == शून्य)
		जाओ noxbuff;

	ax->mtu	     = dev->mtu + 73;
	ax->buffsize = len;
	ax->rcount   = 0;
	ax->xleft    = 0;

	ax->flags   &= (1 << AXF_INUSE);      /* Clear ESCAPE & ERROR flags */

	spin_lock_init(&ax->buflock);

	वापस 0;

noxbuff:
	kमुक्त(ax->rbuff);

norbuff:
	वापस -ENOMEM;
पूर्ण


/* Close the low-level part of the AX25 channel. Easy! */
अटल पूर्णांक ax_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा mkiss *ax = netdev_priv(dev);

	अगर (ax->tty)
		clear_bit(TTY_DO_WRITE_WAKEUP, &ax->tty->flags);

	netअगर_stop_queue(dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops ax_netdev_ops = अणु
	.nकरो_खोलो            = ax_खोलो_dev,
	.nकरो_stop            = ax_बंद,
	.nकरो_start_xmit	     = ax_xmit,
	.nकरो_set_mac_address = ax_set_mac_address,
पूर्ण;

अटल व्योम ax_setup(काष्ठा net_device *dev)
अणु
	/* Finish setting up the DEVICE info. */
	dev->mtu             = AX_MTU;
	dev->hard_header_len = AX25_MAX_HEADER_LEN;
	dev->addr_len        = AX25_ADDR_LEN;
	dev->type            = ARPHRD_AX25;
	dev->tx_queue_len    = 10;
	dev->header_ops      = &ax25_header_ops;
	dev->netdev_ops	     = &ax_netdev_ops;


	स_नकल(dev->broadcast, &ax25_bcast, AX25_ADDR_LEN);
	स_नकल(dev->dev_addr,  &ax25_defaddr,  AX25_ADDR_LEN);

	dev->flags      = IFF_BROADCAST | IFF_MULTICAST;
पूर्ण

/*
 * We have a potential race on dereferencing tty->disc_data, because the tty
 * layer provides no locking at all - thus one cpu could be running
 * sixpack_receive_buf जबतक another calls sixpack_बंद, which zeroes
 * tty->disc_data and मुक्तs the memory that sixpack_receive_buf is using.  The
 * best way to fix this is to use a rwlock in the tty काष्ठा, but क्रम now we
 * use a single global rwlock क्रम all ttys in ppp line discipline.
 */
अटल DEFINE_RWLOCK(disc_data_lock);

अटल काष्ठा mkiss *mkiss_get(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा mkiss *ax;

	पढ़ो_lock(&disc_data_lock);
	ax = tty->disc_data;
	अगर (ax)
		refcount_inc(&ax->refcnt);
	पढ़ो_unlock(&disc_data_lock);

	वापस ax;
पूर्ण

अटल व्योम mkiss_put(काष्ठा mkiss *ax)
अणु
	अगर (refcount_dec_and_test(&ax->refcnt))
		complete(&ax->dead);
पूर्ण

अटल पूर्णांक crc_क्रमce = 0;	/* Can be overridden with insmod */

अटल पूर्णांक mkiss_खोलो(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा net_device *dev;
	काष्ठा mkiss *ax;
	पूर्णांक err;

	अगर (!capable(CAP_NET_ADMIN))
		वापस -EPERM;
	अगर (tty->ops->ग_लिखो == शून्य)
		वापस -EOPNOTSUPP;

	dev = alloc_netdev(माप(काष्ठा mkiss), "ax%d", NET_NAME_UNKNOWN,
			   ax_setup);
	अगर (!dev) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	ax = netdev_priv(dev);
	ax->dev = dev;

	spin_lock_init(&ax->buflock);
	refcount_set(&ax->refcnt, 1);
	init_completion(&ax->dead);

	ax->tty = tty;
	tty->disc_data = ax;
	tty->receive_room = 65535;

	tty_driver_flush_buffer(tty);

	/* Restore शेष settings */
	dev->type = ARPHRD_AX25;

	/* Perक्रमm the low-level AX25 initialization. */
	err = ax_खोलो(ax->dev);
	अगर (err)
		जाओ out_मुक्त_netdev;

	err = रेजिस्टर_netdev(dev);
	अगर (err)
		जाओ out_मुक्त_buffers;

	/* after रेजिस्टर_netdev() - because अन्यथा prपूर्णांकk smashes the kernel */
	चयन (crc_क्रमce) अणु
	हाल 3:
		ax->crcmode  = CRC_MODE_SMACK;
		prपूर्णांकk(KERN_INFO "mkiss: %s: crc mode smack forced.\n",
		       ax->dev->name);
		अवरोध;
	हाल 2:
		ax->crcmode  = CRC_MODE_FLEX;
		prपूर्णांकk(KERN_INFO "mkiss: %s: crc mode flexnet forced.\n",
		       ax->dev->name);
		अवरोध;
	हाल 1:
		ax->crcmode  = CRC_MODE_NONE;
		prपूर्णांकk(KERN_INFO "mkiss: %s: crc mode disabled.\n",
		       ax->dev->name);
		अवरोध;
	हाल 0:
	शेष:
		crc_क्रमce = 0;
		prपूर्णांकk(KERN_INFO "mkiss: %s: crc mode is auto.\n",
		       ax->dev->name);
		ax->crcmode  = CRC_MODE_SMACK_TEST;
	पूर्ण
	ax->crcस्वतः = (crc_क्रमce ? 0 : 1);

	netअगर_start_queue(dev);

	/* Done.  We have linked the TTY line to a channel. */
	वापस 0;

out_मुक्त_buffers:
	kमुक्त(ax->rbuff);
	kमुक्त(ax->xbuff);

out_मुक्त_netdev:
	मुक्त_netdev(dev);

out:
	वापस err;
पूर्ण

अटल व्योम mkiss_बंद(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा mkiss *ax;

	ग_लिखो_lock_irq(&disc_data_lock);
	ax = tty->disc_data;
	tty->disc_data = शून्य;
	ग_लिखो_unlock_irq(&disc_data_lock);

	अगर (!ax)
		वापस;

	/*
	 * We have now ensured that nobody can start using ap from now on, but
	 * we have to रुको क्रम all existing users to finish.
	 */
	अगर (!refcount_dec_and_test(&ax->refcnt))
		रुको_क्रम_completion(&ax->dead);
	/*
	 * Halt the transmit queue so that a new transmit cannot scribble
	 * on our buffers
	 */
	netअगर_stop_queue(ax->dev);

	/* Free all AX25 frame buffers. */
	kमुक्त(ax->rbuff);
	kमुक्त(ax->xbuff);

	ax->tty = शून्य;

	unरेजिस्टर_netdev(ax->dev);
	मुक्त_netdev(ax->dev);
पूर्ण

/* Perक्रमm I/O control on an active ax25 channel. */
अटल पूर्णांक mkiss_ioctl(काष्ठा tty_काष्ठा *tty, काष्ठा file *file,
	अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा mkiss *ax = mkiss_get(tty);
	काष्ठा net_device *dev;
	अचिन्हित पूर्णांक पंचांगp, err;

	/* First make sure we're connected. */
	अगर (ax == शून्य)
		वापस -ENXIO;
	dev = ax->dev;

	चयन (cmd) अणु
 	हाल SIOCGIFNAME:
		err = copy_to_user((व्योम __user *) arg, ax->dev->name,
		                   म_माप(ax->dev->name) + 1) ? -EFAULT : 0;
		अवरोध;

	हाल SIOCGIFENCAP:
		err = put_user(4, (पूर्णांक __user *) arg);
		अवरोध;

	हाल SIOCSIFENCAP:
		अगर (get_user(पंचांगp, (पूर्णांक __user *) arg)) अणु
			err = -EFAULT;
			अवरोध;
		पूर्ण

		ax->mode = पंचांगp;
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
		स_नकल(dev->dev_addr, addr, AX25_ADDR_LEN);
		netअगर_tx_unlock_bh(dev);

		err = 0;
		अवरोध;
	पूर्ण
	शेष:
		err = -ENOIOCTLCMD;
	पूर्ण

	mkiss_put(ax);

	वापस err;
पूर्ण

/*
 * Handle the 'receiver data ready' पूर्णांकerrupt.
 * This function is called by the 'tty_io' module in the kernel when
 * a block of data has been received, which can now be decapsulated
 * and sent on to the AX.25 layer क्रम further processing.
 */
अटल व्योम mkiss_receive_buf(काष्ठा tty_काष्ठा *tty, स्थिर अचिन्हित अक्षर *cp,
	अक्षर *fp, पूर्णांक count)
अणु
	काष्ठा mkiss *ax = mkiss_get(tty);

	अगर (!ax)
		वापस;

	/*
	 * Argh! mtu change समय! - costs us the packet part received
	 * at the change
	 */
	अगर (ax->mtu != ax->dev->mtu + 73)
		ax_changedmtu(ax);

	/* Read the अक्षरacters out of the buffer */
	जबतक (count--) अणु
		अगर (fp != शून्य && *fp++) अणु
			अगर (!test_and_set_bit(AXF_ERROR, &ax->flags))
				ax->dev->stats.rx_errors++;
			cp++;
			जारी;
		पूर्ण

		kiss_unesc(ax, *cp++);
	पूर्ण

	mkiss_put(ax);
	tty_unthrottle(tty);
पूर्ण

/*
 * Called by the driver when there's room क्रम more data.  If we have
 * more packets to send, we send them here.
 */
अटल व्योम mkiss_ग_लिखो_wakeup(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा mkiss *ax = mkiss_get(tty);
	पूर्णांक actual;

	अगर (!ax)
		वापस;

	अगर (ax->xleft <= 0)  अणु
		/* Now serial buffer is almost मुक्त & we can start
		 * transmission of another packet
		 */
		clear_bit(TTY_DO_WRITE_WAKEUP, &tty->flags);

		netअगर_wake_queue(ax->dev);
		जाओ out;
	पूर्ण

	actual = tty->ops->ग_लिखो(tty, ax->xhead, ax->xleft);
	ax->xleft -= actual;
	ax->xhead += actual;

out:
	mkiss_put(ax);
पूर्ण

अटल काष्ठा tty_ldisc_ops ax_ldisc = अणु
	.owner		= THIS_MODULE,
	.name		= "mkiss",
	.खोलो		= mkiss_खोलो,
	.बंद		= mkiss_बंद,
	.ioctl		= mkiss_ioctl,
	.receive_buf	= mkiss_receive_buf,
	.ग_लिखो_wakeup	= mkiss_ग_लिखो_wakeup
पूर्ण;

अटल स्थिर अक्षर banner[] __initस्थिर = KERN_INFO \
	"mkiss: AX.25 Multikiss, Hans Albas PE1AYX\n";
अटल स्थिर अक्षर msg_regfail[] __initस्थिर = KERN_ERR \
	"mkiss: can't register line discipline (err = %d)\n";

अटल पूर्णांक __init mkiss_init_driver(व्योम)
अणु
	पूर्णांक status;

	prपूर्णांकk(banner);

	status = tty_रेजिस्टर_ldisc(N_AX25, &ax_ldisc);
	अगर (status != 0)
		prपूर्णांकk(msg_regfail, status);

	वापस status;
पूर्ण

अटल स्थिर अक्षर msg_unregfail[] = KERN_ERR \
	"mkiss: can't unregister line discipline (err = %d)\n";

अटल व्योम __निकास mkiss_निकास_driver(व्योम)
अणु
	पूर्णांक ret;

	अगर ((ret = tty_unरेजिस्टर_ldisc(N_AX25)))
		prपूर्णांकk(msg_unregfail, ret);
पूर्ण

MODULE_AUTHOR("Ralf Baechle DL5RB <ralf@linux-mips.org>");
MODULE_DESCRIPTION("KISS driver for AX.25 over TTYs");
module_param(crc_क्रमce, पूर्णांक, 0);
MODULE_PARM_DESC(crc_क्रमce, "crc [0 = auto | 1 = none | 2 = flexnet | 3 = smack]");
MODULE_LICENSE("GPL");
MODULE_ALIAS_LDISC(N_AX25);

module_init(mkiss_init_driver);
module_निकास(mkiss_निकास_driver);
