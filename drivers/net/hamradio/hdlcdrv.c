<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*****************************************************************************/

/*
 *	hdlcdrv.c  -- HDLC packet radio network driver.
 *
 *	Copyright (C) 1996-2000  Thomas Sailer (sailer@अगरe.ee.ethz.ch)
 *
 *  Please note that the GPL allows you to use the driver, NOT the radio.
 *  In order to use the radio, you need a license from the communications
 *  authority of your country.
 *
 *  The driver was derived from Donald Beckers skeleton.c
 *	Written 1993-94 by Donald Becker.
 *
 *  History:
 *   0.1  21.09.1996  Started
 *        18.10.1996  Changed to new user space access routines 
 *                    (copy_अणुto,fromपूर्ण_user)
 *   0.2  21.11.1996  various small changes
 *   0.3  03.03.1997  fixed (hopefully) IP not working with ax.25 as a module
 *   0.4  16.04.1997  init code/data tagged
 *   0.5  30.07.1997  made HDLC buffers bigger (solves a problem with the
 *                    soundmodem driver)
 *   0.6  05.04.1998  add spinlocks
 *   0.7  03.08.1999  हटाओd some old compatibility cruft
 *   0.8  12.02.2000  adapted to softnet driver पूर्णांकerface
 */

/*****************************************************************************/

#समावेश <linux/capability.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/net.h>
#समावेश <linux/in.h>
#समावेश <linux/अगर.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/bitops.h>

#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/hdlcdrv.h>
#समावेश <linux/अक्रमom.h>
#समावेश <net/ax25.h> 
#समावेश <linux/uaccess.h>

#समावेश <linux/crc-ccitt.h>

/* --------------------------------------------------------------------- */

#घोषणा KISS_VERBOSE

/* --------------------------------------------------------------------- */

#घोषणा PARAM_TXDELAY   1
#घोषणा PARAM_PERSIST   2
#घोषणा PARAM_SLOTTIME  3
#घोषणा PARAM_TXTAIL    4
#घोषणा PARAM_FULLDUP   5
#घोषणा PARAM_HARDWARE  6
#घोषणा PARAM_RETURN    255

/* --------------------------------------------------------------------- */
/*
 * the CRC routines are stolen from WAMPES
 * by Dieter Deyke
 */


/*---------------------------------------------------------------------------*/

अटल अंतरभूत व्योम append_crc_ccitt(अचिन्हित अक्षर *buffer, पूर्णांक len)
अणु
 	अचिन्हित पूर्णांक crc = crc_ccitt(0xffff, buffer, len) ^ 0xffff;
	buffer += len;
	*buffer++ = crc;
	*buffer++ = crc >> 8;
पूर्ण

/*---------------------------------------------------------------------------*/

अटल अंतरभूत पूर्णांक check_crc_ccitt(स्थिर अचिन्हित अक्षर *buf, पूर्णांक cnt)
अणु
	वापस (crc_ccitt(0xffff, buf, cnt) & 0xffff) == 0xf0b8;
पूर्ण

/*---------------------------------------------------------------------------*/

#अगर 0
अटल पूर्णांक calc_crc_ccitt(स्थिर अचिन्हित अक्षर *buf, पूर्णांक cnt)
अणु
	अचिन्हित पूर्णांक crc = 0xffff;

	क्रम (; cnt > 0; cnt--)
		crc = (crc >> 8) ^ crc_ccitt_table[(crc ^ *buf++) & 0xff];
	crc ^= 0xffff;
	वापस crc & 0xffff;
पूर्ण
#पूर्ण_अगर

/* ---------------------------------------------------------------------- */

#घोषणा tenms_to_2flags(s,tenms) ((tenms * s->par.bitrate) / 100 / 16)

/* ---------------------------------------------------------------------- */
/*
 * The HDLC routines
 */

अटल पूर्णांक hdlc_rx_add_bytes(काष्ठा hdlcdrv_state *s, अचिन्हित पूर्णांक bits, 
			     पूर्णांक num)
अणु
	पूर्णांक added = 0;
	
	जबतक (s->hdlcrx.rx_state && num >= 8) अणु
		अगर (s->hdlcrx.len >= माप(s->hdlcrx.buffer)) अणु
			s->hdlcrx.rx_state = 0;
			वापस 0;
		पूर्ण
		*s->hdlcrx.bp++ = bits >> (32-num);
		s->hdlcrx.len++;
		num -= 8;
		added += 8;
	पूर्ण
	वापस added;
पूर्ण

अटल व्योम hdlc_rx_flag(काष्ठा net_device *dev, काष्ठा hdlcdrv_state *s)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक pkt_len;
	अचिन्हित अक्षर *cp;

	अगर (s->hdlcrx.len < 4) 
		वापस;
	अगर (!check_crc_ccitt(s->hdlcrx.buffer, s->hdlcrx.len)) 
		वापस;
	pkt_len = s->hdlcrx.len - 2 + 1; /* KISS kludge */
	अगर (!(skb = dev_alloc_skb(pkt_len))) अणु
		prपूर्णांकk("%s: memory squeeze, dropping packet\n", dev->name);
		dev->stats.rx_dropped++;
		वापस;
	पूर्ण
	cp = skb_put(skb, pkt_len);
	*cp++ = 0; /* KISS kludge */
	स_नकल(cp, s->hdlcrx.buffer, pkt_len - 1);
	skb->protocol = ax25_type_trans(skb, dev);
	netअगर_rx(skb);
	dev->stats.rx_packets++;
पूर्ण

व्योम hdlcdrv_receiver(काष्ठा net_device *dev, काष्ठा hdlcdrv_state *s)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक mask1, mask2, mask3, mask4, mask5, mask6, word;
	
	अगर (!s || s->magic != HDLCDRV_MAGIC) 
		वापस;
	अगर (test_and_set_bit(0, &s->hdlcrx.in_hdlc_rx))
		वापस;

	जबतक (!hdlcdrv_hbuf_empty(&s->hdlcrx.hbuf)) अणु
		word = hdlcdrv_hbuf_get(&s->hdlcrx.hbuf);	

#अगर_घोषित HDLCDRV_DEBUG
		hdlcdrv_add_bitbuffer_word(&s->bitbuf_hdlc, word);
#पूर्ण_अगर /* HDLCDRV_DEBUG */
	       	s->hdlcrx.bitstream >>= 16;
		s->hdlcrx.bitstream |= word << 16;
		s->hdlcrx.bitbuf >>= 16;
		s->hdlcrx.bitbuf |= word << 16;
		s->hdlcrx.numbits += 16;
		क्रम(i = 15, mask1 = 0x1fc00, mask2 = 0x1fe00, mask3 = 0x0fc00,
		    mask4 = 0x1f800, mask5 = 0xf800, mask6 = 0xffff; 
		    i >= 0; 
		    i--, mask1 <<= 1, mask2 <<= 1, mask3 <<= 1, mask4 <<= 1, 
		    mask5 <<= 1, mask6 = (mask6 << 1) | 1) अणु
			अगर ((s->hdlcrx.bitstream & mask1) == mask1)
				s->hdlcrx.rx_state = 0; /* पात received */
			अन्यथा अगर ((s->hdlcrx.bitstream & mask2) == mask3) अणु
				/* flag received */
				अगर (s->hdlcrx.rx_state) अणु
					hdlc_rx_add_bytes(s, s->hdlcrx.bitbuf 
							  << (8+i),
							  s->hdlcrx.numbits
							  -8-i);
					hdlc_rx_flag(dev, s);
				पूर्ण
				s->hdlcrx.len = 0;
				s->hdlcrx.bp = s->hdlcrx.buffer;
				s->hdlcrx.rx_state = 1;
				s->hdlcrx.numbits = i;
			पूर्ण अन्यथा अगर ((s->hdlcrx.bitstream & mask4) == mask5) अणु
				/* stuffed bit */
				s->hdlcrx.numbits--;
				s->hdlcrx.bitbuf = (s->hdlcrx.bitbuf & (~mask6)) |
					((s->hdlcrx.bitbuf & mask6) << 1);
			पूर्ण
		पूर्ण
		s->hdlcrx.numbits -= hdlc_rx_add_bytes(s, s->hdlcrx.bitbuf,
						       s->hdlcrx.numbits);
	पूर्ण
	clear_bit(0, &s->hdlcrx.in_hdlc_rx);
पूर्ण

/* ---------------------------------------------------------------------- */

अटल अंतरभूत व्योम करो_kiss_params(काष्ठा hdlcdrv_state *s,
				  अचिन्हित अक्षर *data, अचिन्हित दीर्घ len)
अणु

#अगर_घोषित KISS_VERBOSE
#घोषणा PKP(a,b) prपूर्णांकk(KERN_INFO "hdlcdrv.c: channel params: " a "\n", b)
#अन्यथा /* KISS_VERBOSE */	      
#घोषणा PKP(a,b) 
#पूर्ण_अगर /* KISS_VERBOSE */	      

	अगर (len < 2)
		वापस;
	चयन(data[0]) अणु
	हाल PARAM_TXDELAY:
		s->ch_params.tx_delay = data[1];
		PKP("TX delay = %ums", 10 * s->ch_params.tx_delay);
		अवरोध;
	हाल PARAM_PERSIST:   
		s->ch_params.ppersist = data[1];
		PKP("p persistence = %u", s->ch_params.ppersist);
		अवरोध;
	हाल PARAM_SLOTTIME:  
		s->ch_params.slotसमय = data[1];
		PKP("slot time = %ums", s->ch_params.slotसमय);
		अवरोध;
	हाल PARAM_TXTAIL:    
		s->ch_params.tx_tail = data[1];
		PKP("TX tail = %ums", s->ch_params.tx_tail);
		अवरोध;
	हाल PARAM_FULLDUP:   
		s->ch_params.fulldup = !!data[1];
		PKP("%s duplex", s->ch_params.fulldup ? "full" : "half");
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
#अघोषित PKP
पूर्ण

/* ---------------------------------------------------------------------- */

व्योम hdlcdrv_transmitter(काष्ठा net_device *dev, काष्ठा hdlcdrv_state *s)
अणु
	अचिन्हित पूर्णांक mask1, mask2, mask3;
	पूर्णांक i;
	काष्ठा sk_buff *skb;
	पूर्णांक pkt_len;

	अगर (!s || s->magic != HDLCDRV_MAGIC) 
		वापस;
	अगर (test_and_set_bit(0, &s->hdlctx.in_hdlc_tx))
		वापस;
	क्रम (;;) अणु
		अगर (s->hdlctx.numbits >= 16) अणु
			अगर (hdlcdrv_hbuf_full(&s->hdlctx.hbuf)) अणु
				clear_bit(0, &s->hdlctx.in_hdlc_tx);
				वापस;
			पूर्ण
			hdlcdrv_hbuf_put(&s->hdlctx.hbuf, s->hdlctx.bitbuf);
			s->hdlctx.bitbuf >>= 16;
			s->hdlctx.numbits -= 16;
		पूर्ण
		चयन (s->hdlctx.tx_state) अणु
		शेष:
			clear_bit(0, &s->hdlctx.in_hdlc_tx);
			वापस;
		हाल 0:
		हाल 1:
			अगर (s->hdlctx.numflags) अणु
				s->hdlctx.numflags--;
				s->hdlctx.bitbuf |= 
					0x7e7e << s->hdlctx.numbits;
				s->hdlctx.numbits += 16;
				अवरोध;
			पूर्ण
			अगर (s->hdlctx.tx_state == 1) अणु
				clear_bit(0, &s->hdlctx.in_hdlc_tx);
				वापस;
			पूर्ण
			अगर (!(skb = s->skb)) अणु
				पूर्णांक flgs = tenms_to_2flags(s, s->ch_params.tx_tail);
				अगर (flgs < 2)
					flgs = 2;
				s->hdlctx.tx_state = 1;
				s->hdlctx.numflags = flgs;
				अवरोध;
			पूर्ण
			s->skb = शून्य;
			netअगर_wake_queue(dev);
			pkt_len = skb->len-1; /* strip KISS byte */
			अगर (pkt_len >= HDLCDRV_MAXFLEN || pkt_len < 2) अणु
				s->hdlctx.tx_state = 0;
				s->hdlctx.numflags = 1;
				dev_kमुक्त_skb_irq(skb);
				अवरोध;
			पूर्ण
			skb_copy_from_linear_data_offset(skb, 1,
							 s->hdlctx.buffer,
							 pkt_len);
			dev_kमुक्त_skb_irq(skb);
			s->hdlctx.bp = s->hdlctx.buffer;
			append_crc_ccitt(s->hdlctx.buffer, pkt_len);
			s->hdlctx.len = pkt_len+2; /* the appended CRC */
			s->hdlctx.tx_state = 2;
			s->hdlctx.bitstream = 0;
			dev->stats.tx_packets++;
			अवरोध;
		हाल 2:
			अगर (!s->hdlctx.len) अणु
				s->hdlctx.tx_state = 0;
				s->hdlctx.numflags = 1;
				अवरोध;
			पूर्ण
			s->hdlctx.len--;
			s->hdlctx.bitbuf |= *s->hdlctx.bp <<
				s->hdlctx.numbits;
			s->hdlctx.bitstream >>= 8;
			s->hdlctx.bitstream |= (*s->hdlctx.bp++) << 16;
			mask1 = 0x1f000;
			mask2 = 0x10000;
			mask3 = 0xffffffff >> (31-s->hdlctx.numbits);
			s->hdlctx.numbits += 8;
			क्रम(i = 0; i < 8; i++, mask1 <<= 1, mask2 <<= 1, 
			    mask3 = (mask3 << 1) | 1) अणु
				अगर ((s->hdlctx.bitstream & mask1) != mask1) 
					जारी;
				s->hdlctx.bitstream &= ~mask2;
				s->hdlctx.bitbuf = 
					(s->hdlctx.bitbuf & mask3) |
						((s->hdlctx.bitbuf & 
						 (~mask3)) << 1);
				s->hdlctx.numbits++;
				mask3 = (mask3 << 1) | 1;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/* ---------------------------------------------------------------------- */

अटल व्योम start_tx(काष्ठा net_device *dev, काष्ठा hdlcdrv_state *s)
अणु
	s->hdlctx.tx_state = 0;
	s->hdlctx.numflags = tenms_to_2flags(s, s->ch_params.tx_delay);
	s->hdlctx.bitbuf = s->hdlctx.bitstream = s->hdlctx.numbits = 0;
	hdlcdrv_transmitter(dev, s);
	s->hdlctx.ptt = 1;
	s->ptt_keyed++;
पूर्ण

/* ---------------------------------------------------------------------- */

व्योम hdlcdrv_arbitrate(काष्ठा net_device *dev, काष्ठा hdlcdrv_state *s)
अणु
	अगर (!s || s->magic != HDLCDRV_MAGIC || s->hdlctx.ptt || !s->skb) 
		वापस;
	अगर (s->ch_params.fulldup) अणु
		start_tx(dev, s);
		वापस;
	पूर्ण
	अगर (s->hdlcrx.dcd) अणु
		s->hdlctx.slotcnt = s->ch_params.slotसमय;
		वापस;
	पूर्ण
	अगर ((--s->hdlctx.slotcnt) > 0)
		वापस;
	s->hdlctx.slotcnt = s->ch_params.slotसमय;
	अगर ((pअक्रमom_u32() % 256) > s->ch_params.ppersist)
		वापस;
	start_tx(dev, s);
पूर्ण

/* --------------------------------------------------------------------- */
/*
 * ===================== network driver पूर्णांकerface =========================
 */

अटल netdev_tx_t hdlcdrv_send_packet(काष्ठा sk_buff *skb,
				       काष्ठा net_device *dev)
अणु
	काष्ठा hdlcdrv_state *sm = netdev_priv(dev);

	अगर (skb->protocol == htons(ETH_P_IP))
		वापस ax25_ip_xmit(skb);

	अगर (skb->data[0] != 0) अणु
		करो_kiss_params(sm, skb->data, skb->len);
		dev_kमुक्त_skb(skb);
		वापस NETDEV_TX_OK;
	पूर्ण
	अगर (sm->skb) अणु
		dev_kमुक्त_skb(skb);
		वापस NETDEV_TX_OK;
	पूर्ण
	netअगर_stop_queue(dev);
	sm->skb = skb;
	वापस NETDEV_TX_OK;
पूर्ण

/* --------------------------------------------------------------------- */

अटल पूर्णांक hdlcdrv_set_mac_address(काष्ठा net_device *dev, व्योम *addr)
अणु
	काष्ठा sockaddr *sa = (काष्ठा sockaddr *)addr;

	/* addr is an AX.25 shअगरted ASCII mac address */
	स_नकल(dev->dev_addr, sa->sa_data, dev->addr_len); 
	वापस 0;                                         
पूर्ण

/* --------------------------------------------------------------------- */
/*
 * Open/initialize the board. This is called (in the current kernel)
 * someसमय after booting when the 'ifconfig' program is run.
 *
 * This routine should set everything up anew at each खोलो, even
 * रेजिस्टरs that "should" only need to be set once at boot, so that
 * there is non-reboot way to recover अगर something goes wrong.
 */

अटल पूर्णांक hdlcdrv_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा hdlcdrv_state *s = netdev_priv(dev);
	पूर्णांक i;

	अगर (!s->ops || !s->ops->खोलो)
		वापस -ENODEV;

	/*
	 * initialise some variables
	 */
	s->खोलोed = 1;
	s->hdlcrx.hbuf.rd = s->hdlcrx.hbuf.wr = 0;
	s->hdlcrx.in_hdlc_rx = 0;
	s->hdlcrx.rx_state = 0;
	
	s->hdlctx.hbuf.rd = s->hdlctx.hbuf.wr = 0;
	s->hdlctx.in_hdlc_tx = 0;
	s->hdlctx.tx_state = 1;
	s->hdlctx.numflags = 0;
	s->hdlctx.bitstream = s->hdlctx.bitbuf = s->hdlctx.numbits = 0;
	s->hdlctx.ptt = 0;
	s->hdlctx.slotcnt = s->ch_params.slotसमय;
	s->hdlctx.calibrate = 0;

	i = s->ops->खोलो(dev);
	अगर (i)
		वापस i;
	netअगर_start_queue(dev);
	वापस 0;
पूर्ण

/* --------------------------------------------------------------------- */
/* 
 * The inverse routine to hdlcdrv_खोलो(). 
 */

अटल पूर्णांक hdlcdrv_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा hdlcdrv_state *s = netdev_priv(dev);
	पूर्णांक i = 0;

	netअगर_stop_queue(dev);

	अगर (s->ops && s->ops->बंद)
		i = s->ops->बंद(dev);
	dev_kमुक्त_skb(s->skb);
	s->skb = शून्य;
	s->खोलोed = 0;
	वापस i;
पूर्ण

/* --------------------------------------------------------------------- */

अटल पूर्णांक hdlcdrv_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	काष्ठा hdlcdrv_state *s = netdev_priv(dev);
	काष्ठा hdlcdrv_ioctl bi;

	अगर (cmd != SIOCDEVPRIVATE) अणु
		अगर (s->ops && s->ops->ioctl)
			वापस s->ops->ioctl(dev, अगरr, &bi, cmd);
		वापस -ENOIOCTLCMD;
	पूर्ण
	अगर (copy_from_user(&bi, अगरr->अगरr_data, माप(bi)))
		वापस -EFAULT;

	चयन (bi.cmd) अणु
	शेष:
		अगर (s->ops && s->ops->ioctl)
			वापस s->ops->ioctl(dev, अगरr, &bi, cmd);
		वापस -ENOIOCTLCMD;

	हाल HDLCDRVCTL_GETCHANNELPAR:
		bi.data.cp.tx_delay = s->ch_params.tx_delay;
		bi.data.cp.tx_tail = s->ch_params.tx_tail;
		bi.data.cp.slotसमय = s->ch_params.slotसमय;
		bi.data.cp.ppersist = s->ch_params.ppersist;
		bi.data.cp.fulldup = s->ch_params.fulldup;
		अवरोध;

	हाल HDLCDRVCTL_SETCHANNELPAR:
		अगर (!capable(CAP_NET_ADMIN))
			वापस -EACCES;
		s->ch_params.tx_delay = bi.data.cp.tx_delay;
		s->ch_params.tx_tail = bi.data.cp.tx_tail;
		s->ch_params.slotसमय = bi.data.cp.slotसमय;
		s->ch_params.ppersist = bi.data.cp.ppersist;
		s->ch_params.fulldup = bi.data.cp.fulldup;
		s->hdlctx.slotcnt = 1;
		वापस 0;
		
	हाल HDLCDRVCTL_GETMODEMPAR:
		bi.data.mp.iobase = dev->base_addr;
		bi.data.mp.irq = dev->irq;
		bi.data.mp.dma = dev->dma;
		bi.data.mp.dma2 = s->ptt_out.dma2;
		bi.data.mp.seriobase = s->ptt_out.seriobase;
		bi.data.mp.pariobase = s->ptt_out.pariobase;
		bi.data.mp.midiiobase = s->ptt_out.midiiobase;
		अवरोध;

	हाल HDLCDRVCTL_SETMODEMPAR:
		अगर ((!capable(CAP_SYS_RAWIO)) || netअगर_running(dev))
			वापस -EACCES;
		dev->base_addr = bi.data.mp.iobase;
		dev->irq = bi.data.mp.irq;
		dev->dma = bi.data.mp.dma;
		s->ptt_out.dma2 = bi.data.mp.dma2;
		s->ptt_out.seriobase = bi.data.mp.seriobase;
		s->ptt_out.pariobase = bi.data.mp.pariobase;
		s->ptt_out.midiiobase = bi.data.mp.midiiobase;
		वापस 0;	
	
	हाल HDLCDRVCTL_GETSTAT:
		bi.data.cs.ptt = hdlcdrv_ptt(s);
		bi.data.cs.dcd = s->hdlcrx.dcd;
		bi.data.cs.ptt_keyed = s->ptt_keyed;
		bi.data.cs.tx_packets = dev->stats.tx_packets;
		bi.data.cs.tx_errors = dev->stats.tx_errors;
		bi.data.cs.rx_packets = dev->stats.rx_packets;
		bi.data.cs.rx_errors = dev->stats.rx_errors;
		अवरोध;		

	हाल HDLCDRVCTL_OLDGETSTAT:
		bi.data.ocs.ptt = hdlcdrv_ptt(s);
		bi.data.ocs.dcd = s->hdlcrx.dcd;
		bi.data.ocs.ptt_keyed = s->ptt_keyed;
		अवरोध;		

	हाल HDLCDRVCTL_CALIBRATE:
		अगर(!capable(CAP_SYS_RAWIO))
			वापस -EPERM;
		अगर (s->par.bitrate <= 0)
			वापस -EINVAL;
		अगर (bi.data.calibrate > पूर्णांक_उच्च / s->par.bitrate)
			वापस -EINVAL;
		s->hdlctx.calibrate = bi.data.calibrate * s->par.bitrate / 16;
		वापस 0;

	हाल HDLCDRVCTL_GETSAMPLES:
#अगर_अघोषित HDLCDRV_DEBUG
		वापस -EPERM;
#अन्यथा /* HDLCDRV_DEBUG */
		अगर (s->bitbuf_channel.rd == s->bitbuf_channel.wr) 
			वापस -EAGAIN;
		bi.data.bits = 
			s->bitbuf_channel.buffer[s->bitbuf_channel.rd];
		s->bitbuf_channel.rd = (s->bitbuf_channel.rd+1) %
			माप(s->bitbuf_channel.buffer);
		अवरोध;
#पूर्ण_अगर /* HDLCDRV_DEBUG */
				
	हाल HDLCDRVCTL_GETBITS:
#अगर_अघोषित HDLCDRV_DEBUG
		वापस -EPERM;
#अन्यथा /* HDLCDRV_DEBUG */
		अगर (s->bitbuf_hdlc.rd == s->bitbuf_hdlc.wr) 
			वापस -EAGAIN;
		bi.data.bits = 
			s->bitbuf_hdlc.buffer[s->bitbuf_hdlc.rd];
		s->bitbuf_hdlc.rd = (s->bitbuf_hdlc.rd+1) %
			माप(s->bitbuf_hdlc.buffer);
		अवरोध;		
#पूर्ण_अगर /* HDLCDRV_DEBUG */

	हाल HDLCDRVCTL_DRIVERNAME:
		अगर (s->ops && s->ops->drvname) अणु
			strlcpy(bi.data.drivername, s->ops->drvname,
				माप(bi.data.drivername));
			अवरोध;
		पूर्ण
		bi.data.drivername[0] = '\0';
		अवरोध;
		
	पूर्ण
	अगर (copy_to_user(अगरr->अगरr_data, &bi, माप(bi)))
		वापस -EFAULT;
	वापस 0;

पूर्ण

/* --------------------------------------------------------------------- */

अटल स्थिर काष्ठा net_device_ops hdlcdrv_netdev = अणु
	.nकरो_खोलो	= hdlcdrv_खोलो,
	.nकरो_stop	= hdlcdrv_बंद,
	.nकरो_start_xmit = hdlcdrv_send_packet,
	.nकरो_करो_ioctl	= hdlcdrv_ioctl,
	.nकरो_set_mac_address = hdlcdrv_set_mac_address,
पूर्ण;

/*
 * Initialize fields in hdlcdrv
 */
अटल व्योम hdlcdrv_setup(काष्ठा net_device *dev)
अणु
	अटल स्थिर काष्ठा hdlcdrv_channel_params dflt_ch_params = अणु 
		20, 2, 10, 40, 0 
	पूर्ण;
	काष्ठा hdlcdrv_state *s = netdev_priv(dev);

	/*
	 * initialize the hdlcdrv_state काष्ठा
	 */
	s->ch_params = dflt_ch_params;
	s->ptt_keyed = 0;

	spin_lock_init(&s->hdlcrx.hbuf.lock);
	s->hdlcrx.hbuf.rd = s->hdlcrx.hbuf.wr = 0;
	s->hdlcrx.in_hdlc_rx = 0;
	s->hdlcrx.rx_state = 0;
	
	spin_lock_init(&s->hdlctx.hbuf.lock);
	s->hdlctx.hbuf.rd = s->hdlctx.hbuf.wr = 0;
	s->hdlctx.in_hdlc_tx = 0;
	s->hdlctx.tx_state = 1;
	s->hdlctx.numflags = 0;
	s->hdlctx.bitstream = s->hdlctx.bitbuf = s->hdlctx.numbits = 0;
	s->hdlctx.ptt = 0;
	s->hdlctx.slotcnt = s->ch_params.slotसमय;
	s->hdlctx.calibrate = 0;

#अगर_घोषित HDLCDRV_DEBUG
	s->bitbuf_channel.rd = s->bitbuf_channel.wr = 0;
	s->bitbuf_channel.shreg = 0x80;

	s->bitbuf_hdlc.rd = s->bitbuf_hdlc.wr = 0;
	s->bitbuf_hdlc.shreg = 0x80;
#पूर्ण_अगर /* HDLCDRV_DEBUG */


	/* Fill in the fields of the device काष्ठाure */

	s->skb = शून्य;
	
	dev->netdev_ops = &hdlcdrv_netdev;
	dev->header_ops = &ax25_header_ops;
	
	dev->type = ARPHRD_AX25;           /* AF_AX25 device */
	dev->hard_header_len = AX25_MAX_HEADER_LEN + AX25_BPQ_HEADER_LEN;
	dev->mtu = AX25_DEF_PACLEN;        /* eth_mtu is the शेष */
	dev->addr_len = AX25_ADDR_LEN;     /* माप an ax.25 address */
	स_नकल(dev->broadcast, &ax25_bcast, AX25_ADDR_LEN);
	स_नकल(dev->dev_addr, &ax25_defaddr, AX25_ADDR_LEN);
	dev->tx_queue_len = 16;
पूर्ण

/* --------------------------------------------------------------------- */
काष्ठा net_device *hdlcdrv_रेजिस्टर(स्थिर काष्ठा hdlcdrv_ops *ops,
				    अचिन्हित पूर्णांक privsize, स्थिर अक्षर *अगरname,
				    अचिन्हित पूर्णांक baseaddr, अचिन्हित पूर्णांक irq, 
				    अचिन्हित पूर्णांक dma) 
अणु
	काष्ठा net_device *dev;
	काष्ठा hdlcdrv_state *s;
	पूर्णांक err;

	अगर (privsize < माप(काष्ठा hdlcdrv_state))
		privsize = माप(काष्ठा hdlcdrv_state);

	dev = alloc_netdev(privsize, अगरname, NET_NAME_UNKNOWN, hdlcdrv_setup);
	अगर (!dev)
		वापस ERR_PTR(-ENOMEM);

	/*
	 * initialize part of the hdlcdrv_state काष्ठा
	 */
	s = netdev_priv(dev);
	s->magic = HDLCDRV_MAGIC;
	s->ops = ops;
	dev->base_addr = baseaddr;
	dev->irq = irq;
	dev->dma = dma;

	err = रेजिस्टर_netdev(dev);
	अगर (err < 0) अणु
		prपूर्णांकk(KERN_WARNING "hdlcdrv: cannot register net "
		       "device %s\n", dev->name);
		मुक्त_netdev(dev);
		dev = ERR_PTR(err);
	पूर्ण
	वापस dev;
पूर्ण

/* --------------------------------------------------------------------- */

व्योम hdlcdrv_unरेजिस्टर(काष्ठा net_device *dev) 
अणु
	काष्ठा hdlcdrv_state *s = netdev_priv(dev);

	BUG_ON(s->magic != HDLCDRV_MAGIC);

	अगर (s->खोलोed && s->ops->बंद)
		s->ops->बंद(dev);
	unरेजिस्टर_netdev(dev);
	
	मुक्त_netdev(dev);
पूर्ण

/* --------------------------------------------------------------------- */

EXPORT_SYMBOL(hdlcdrv_receiver);
EXPORT_SYMBOL(hdlcdrv_transmitter);
EXPORT_SYMBOL(hdlcdrv_arbitrate);
EXPORT_SYMBOL(hdlcdrv_रेजिस्टर);
EXPORT_SYMBOL(hdlcdrv_unरेजिस्टर);

/* --------------------------------------------------------------------- */

अटल पूर्णांक __init hdlcdrv_init_driver(व्योम)
अणु
	prपूर्णांकk(KERN_INFO "hdlcdrv: (C) 1996-2000 Thomas Sailer HB9JNX/AE4WA\n");
	prपूर्णांकk(KERN_INFO "hdlcdrv: version 0.8\n");
	वापस 0;
पूर्ण

/* --------------------------------------------------------------------- */

अटल व्योम __निकास hdlcdrv_cleanup_driver(व्योम)
अणु
	prपूर्णांकk(KERN_INFO "hdlcdrv: cleanup\n");
पूर्ण

/* --------------------------------------------------------------------- */

MODULE_AUTHOR("Thomas M. Sailer, sailer@ife.ee.ethz.ch, hb9jnx@hb9w.che.eu");
MODULE_DESCRIPTION("Packet Radio network interface HDLC encoder/decoder");
MODULE_LICENSE("GPL");
module_init(hdlcdrv_init_driver);
module_निकास(hdlcdrv_cleanup_driver);

/* --------------------------------------------------------------------- */
