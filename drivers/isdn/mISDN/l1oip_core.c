<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*

 * l1oip.c  low level driver क्रम tunneling layer 1 over IP
 *
 * NOTE: It is not compatible with TDMoIP nor "ISDN over IP".
 *
 * Author	Andreas Eversberg (jolly@eversberg.eu)
 */

/* module parameters:
 * type:
 Value 1	= BRI
 Value 2	= PRI
 Value 3 = BRI (multi channel frame, not supported yet)
 Value 4 = PRI (multi channel frame, not supported yet)
 A multi channel frame reduces overhead to a single frame क्रम all
 b-channels, but increases delay.
 (NOTE: Multi channel frames are not implemented yet.)

 * codec:
 Value 0 = transparent (शेष)
 Value 1 = transfer ALAW
 Value 2 = transfer ULAW
 Value 3 = transfer generic 4 bit compression.

 * ulaw:
 0 = we use a-Law (शेष)
 1 = we use u-Law

 * limit:
 limitation of B-channels to control bandwidth (1...126)
 BRI: 1 or 2
 PRI: 1-30, 31-126 (126, because dchannel ist not counted here)
 Also limited ressources are used क्रम stack, resulting in less channels.
 It is possible to have more channels than 30 in PRI mode, this must
 be supported by the application.

 * ip:
 byte representation of remote ip address (127.0.0.1 -> 127,0,0,1)
 If not given or four 0, no remote address is set.
 For multiple पूर्णांकerfaces, concat ip addresses. (127,0,0,1,127,0,0,1)

 * port:
 port number (local पूर्णांकerface)
 If not given or 0, port 931 is used क्रम fist instance, 932 क्रम next...
 For multiple पूर्णांकerfaces, dअगरferent ports must be given.

 * remoteport:
 port number (remote पूर्णांकerface)
 If not given or 0, remote port equals local port
 For multiple पूर्णांकerfaces on equal sites, dअगरferent ports must be given.

 * ondemand:
 0 = fixed (always transmit packets, even when remote side समयd out)
 1 = on demand (only transmit packets, when remote side is detected)
 the शेष is 0
 NOTE: ID must also be set क्रम on demand.

 * id:
 optional value to identअगरy frames. This value must be equal on both
 peers and should be अक्रमom. If omitted or 0, no ID is transmitted.

 * debug:
 NOTE: only one debug value must be given क्रम all cards
 enable debugging (see l1oip.h क्रम debug options)


 Special mISDN controls:

 op = MISDN_CTRL_SETPEER*
 p1 = bytes 0-3 : remote IP address in network order (left element first)
 p2 = bytes 1-2 : remote port in network order (high byte first)
 optional:
 p2 = bytes 3-4 : local port in network order (high byte first)

 op = MISDN_CTRL_UNSETPEER*

 * Use l1oipctrl क्रम comक्रमtable setting or removing ip address.
 (Layer 1 Over IP CTRL)


 L1oIP-Protocol
 --------------

 Frame Header:

 7 6 5 4 3 2 1 0
 +---------------+
 |Ver|T|I|Coding |
 +---------------+
 |  ID byte 3 *  |
 +---------------+
 |  ID byte 2 *  |
 +---------------+
 |  ID byte 1 *  |
 +---------------+
 |  ID byte 0 *  |
 +---------------+
 |M|   Channel   |
 +---------------+
 |    Length *   |
 +---------------+
 | Time Base MSB |
 +---------------+
 | Time Base LSB |
 +---------------+
 | Data....	|

 ...

 |               |
 +---------------+
 |M|   Channel   |
 +---------------+
 |    Length *   |
 +---------------+
 | Time Base MSB |
 +---------------+
 | Time Base LSB |
 +---------------+
 | Data....	|

 ...


 * Only included in some हालs.

 - Ver = Version
 If version is missmatch, the frame must be ignored.

 - T = Type of पूर्णांकerface
 Must be 0 क्रम S0 or 1 क्रम E1.

 - I = Id present
 If bit is set, four ID bytes are included in frame.

 - ID = Connection ID
 Additional ID to prevent Denial of Service attacs. Also it prevents hijacking
 connections with dynamic IP. The ID should be अक्रमom and must not be 0.

 - Coding = Type of codec
 Must be 0 क्रम no transcoding. Also क्रम D-channel and other HDLC frames.
 1 and 2 are reserved क्रम explicitly use of a-LAW or u-LAW codec.
 3 is used क्रम generic table compressor.

 - M = More channels to come. If this flag is 1, the following byte contains
 the length of the channel data. After the data block, the next channel will
 be defined. The flag क्रम the last channel block (or अगर only one channel is
 transmitted), must be 0 and no length is given.

 - Channel = Channel number
 0 reserved
 1-3 channel data क्रम S0 (3 is D-channel)
 1-31 channel data क्रम E1 (16 is D-channel)
 32-127 channel data क्रम extended E1 (16 is D-channel)

 - The length is used अगर the M-flag is 1. It is used to find the next channel
 inside frame.
 NOTE: A value of 0 equals 256 bytes of data.
 -> For larger data blocks, a single frame must be used.
 -> For larger streams, a single frame or multiple blocks with same channel ID
 must be used.

 - Time Base = Timestamp of first sample in frame
 The "Time Base" is used to rearange packets and to detect packet loss.
 The 16 bits are sent in network order (MSB first) and count 1/8000 th of a
 second. This causes a wrap around each 8,192 seconds. There is no requirement
 क्रम the initial "Time Base", but 0 should be used क्रम the first packet.
 In हाल of HDLC data, this बारtamp counts the packet or byte number.


 Two Timers:

 After initialisation, a समयr of 15 seconds is started. Whenever a packet is
 transmitted, the समयr is reset to 15 seconds again. If the समयr expires, an
 empty packet is transmitted. This keep the connection alive.

 When a valid packet is received, a समयr 65 seconds is started. The पूर्णांकerface
 become ACTIVE. If the समयr expires, the पूर्णांकerface becomes INACTIVE.


 Dynamic IP handling:

 To allow dynamic IP, the ID must be non 0. In this हाल, any packet with the
 correct port number and ID will be accepted. If the remote side changes its IP
 the new IP is used क्रम all transmitted packets until it changes again.


 On Demand:

 If the ondemand parameter is given, the remote IP is set to 0 on समयout.
 This will stop keepalive traffic to remote. If the remote is online again,
 traffic will जारी to the remote address. This is useful क्रम road warriors.
 This feature only works with ID set, otherwhise it is highly unsecure.


 Socket and Thपढ़ो
 -----------------

 The complete socket खोलोing and closing is करोne by a thपढ़ो.
 When the thपढ़ो खोलोed a socket, the hc->socket descriptor is set. Whenever a
 packet shall be sent to the socket, the hc->socket must be checked whether not
 शून्य. To prevent change in socket descriptor, the hc->socket_lock must be used.
 To change the socket, a recall of l1oip_socket_खोलो() will safely समाप्त the
 socket process and create a new one.

*/

#घोषणा L1OIP_VERSION	0	/* 0...3 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/mISDNअगर.h>
#समावेश <linux/mISDNhw.h>
#समावेश <linux/mISDNdsp.h>
#समावेश <linux/init.h>
#समावेश <linux/in.h>
#समावेश <linux/inet.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched/संकेत.स>

#समावेश <net/sock.h>
#समावेश "core.h"
#समावेश "l1oip.h"

अटल स्थिर अक्षर *l1oip_revision = "2.00";

अटल पूर्णांक l1oip_cnt;
अटल DEFINE_SPINLOCK(l1oip_lock);
अटल LIST_HEAD(l1oip_ilist);

#घोषणा MAX_CARDS	16
अटल u_पूर्णांक type[MAX_CARDS];
अटल u_पूर्णांक codec[MAX_CARDS];
अटल u_पूर्णांक ip[MAX_CARDS * 4];
अटल u_पूर्णांक port[MAX_CARDS];
अटल u_पूर्णांक remoteport[MAX_CARDS];
अटल u_पूर्णांक ondemand[MAX_CARDS];
अटल u_पूर्णांक limit[MAX_CARDS];
अटल u_पूर्णांक id[MAX_CARDS];
अटल पूर्णांक debug;
अटल पूर्णांक ulaw;

MODULE_AUTHOR("Andreas Eversberg");
MODULE_LICENSE("GPL");
module_param_array(type, uपूर्णांक, शून्य, S_IRUGO | S_IWUSR);
module_param_array(codec, uपूर्णांक, शून्य, S_IRUGO | S_IWUSR);
module_param_array(ip, uपूर्णांक, शून्य, S_IRUGO | S_IWUSR);
module_param_array(port, uपूर्णांक, शून्य, S_IRUGO | S_IWUSR);
module_param_array(remoteport, uपूर्णांक, शून्य, S_IRUGO | S_IWUSR);
module_param_array(ondemand, uपूर्णांक, शून्य, S_IRUGO | S_IWUSR);
module_param_array(limit, uपूर्णांक, शून्य, S_IRUGO | S_IWUSR);
module_param_array(id, uपूर्णांक, शून्य, S_IRUGO | S_IWUSR);
module_param(ulaw, uपूर्णांक, S_IRUGO | S_IWUSR);
module_param(debug, uपूर्णांक, S_IRUGO | S_IWUSR);

/*
 * send a frame via socket, अगर खोलो and restart समयr
 */
अटल पूर्णांक
l1oip_socket_send(काष्ठा l1oip *hc, u8 localcodec, u8 channel, u32 chanmask,
		  u16 समयbase, u8 *buf, पूर्णांक len)
अणु
	u8 *p;
	u8 frame[MAX_DFRAME_LEN_L1 + 32];
	काष्ठा socket *socket = शून्य;

	अगर (debug & DEBUG_L1OIP_MSG)
		prपूर्णांकk(KERN_DEBUG "%s: sending data to socket (len = %d)\n",
		       __func__, len);

	p = frame;

	/* restart समयr */
	अगर (समय_beक्रमe(hc->keep_tl.expires, jअगरfies + 5 * HZ))
		mod_समयr(&hc->keep_tl, jअगरfies + L1OIP_KEEPALIVE * HZ);
	अन्यथा
		hc->keep_tl.expires = jअगरfies + L1OIP_KEEPALIVE * HZ;

	अगर (debug & DEBUG_L1OIP_MSG)
		prपूर्णांकk(KERN_DEBUG "%s: resetting timer\n", __func__);

	/* drop अगर we have no remote ip or port */
	अगर (!hc->sin_remote.sin_addr.s_addr || !hc->sin_remote.sin_port) अणु
		अगर (debug & DEBUG_L1OIP_MSG)
			prपूर्णांकk(KERN_DEBUG "%s: dropping frame, because remote "
			       "IP is not set.\n", __func__);
		वापस len;
	पूर्ण

	/* assemble frame */
	*p++ = (L1OIP_VERSION << 6) /* version and coding */
		| (hc->pri ? 0x20 : 0x00) /* type */
		| (hc->id ? 0x10 : 0x00) /* id */
		| localcodec;
	अगर (hc->id) अणु
		*p++ = hc->id >> 24; /* id */
		*p++ = hc->id >> 16;
		*p++ = hc->id >> 8;
		*p++ = hc->id;
	पूर्ण
	*p++ =  0x00 + channel; /* m-flag, channel */
	*p++ = समयbase >> 8; /* समय base */
	*p++ = समयbase;

	अगर (buf && len) अणु /* add data to frame */
		अगर (localcodec == 1 && ulaw)
			l1oip_ulaw_to_alaw(buf, len, p);
		अन्यथा अगर (localcodec == 2 && !ulaw)
			l1oip_alaw_to_ulaw(buf, len, p);
		अन्यथा अगर (localcodec == 3)
			len = l1oip_law_to_4bit(buf, len, p,
						&hc->chan[channel].codecstate);
		अन्यथा
			स_नकल(p, buf, len);
	पूर्ण
	len += p - frame;

	/* check क्रम socket in safe condition */
	spin_lock(&hc->socket_lock);
	अगर (!hc->socket) अणु
		spin_unlock(&hc->socket_lock);
		वापस 0;
	पूर्ण
	/* seize socket */
	socket = hc->socket;
	hc->socket = शून्य;
	spin_unlock(&hc->socket_lock);
	/* send packet */
	अगर (debug & DEBUG_L1OIP_MSG)
		prपूर्णांकk(KERN_DEBUG "%s: sending packet to socket (len "
		       "= %d)\n", __func__, len);
	hc->sendiov.iov_base = frame;
	hc->sendiov.iov_len  = len;
	len = kernel_sendmsg(socket, &hc->sendmsg, &hc->sendiov, 1, len);
	/* give socket back */
	hc->socket = socket; /* no locking required */

	वापस len;
पूर्ण


/*
 * receive channel data from socket
 */
अटल व्योम
l1oip_socket_recv(काष्ठा l1oip *hc, u8 remotecodec, u8 channel, u16 समयbase,
		  u8 *buf, पूर्णांक len)
अणु
	काष्ठा sk_buff *nskb;
	काष्ठा bchannel *bch;
	काष्ठा dchannel *dch;
	u8 *p;
	u32 rx_counter;

	अगर (len == 0) अणु
		अगर (debug & DEBUG_L1OIP_MSG)
			prपूर्णांकk(KERN_DEBUG "%s: received empty keepalive data, "
			       "ignoring\n", __func__);
		वापस;
	पूर्ण

	अगर (debug & DEBUG_L1OIP_MSG)
		prपूर्णांकk(KERN_DEBUG "%s: received data, sending to mISDN (%d)\n",
		       __func__, len);

	अगर (channel < 1 || channel > 127) अणु
		prपूर्णांकk(KERN_WARNING "%s: packet error - channel %d out of "
		       "range\n", __func__, channel);
		वापस;
	पूर्ण
	dch = hc->chan[channel].dch;
	bch = hc->chan[channel].bch;
	अगर (!dch && !bch) अणु
		prपूर्णांकk(KERN_WARNING "%s: packet error - channel %d not in "
		       "stack\n", __func__, channel);
		वापस;
	पूर्ण

	/* prepare message */
	nskb = mI_alloc_skb((remotecodec == 3) ? (len << 1) : len, GFP_ATOMIC);
	अगर (!nskb) अणु
		prपूर्णांकk(KERN_ERR "%s: No mem for skb.\n", __func__);
		वापस;
	पूर्ण
	p = skb_put(nskb, (remotecodec == 3) ? (len << 1) : len);

	अगर (remotecodec == 1 && ulaw)
		l1oip_alaw_to_ulaw(buf, len, p);
	अन्यथा अगर (remotecodec == 2 && !ulaw)
		l1oip_ulaw_to_alaw(buf, len, p);
	अन्यथा अगर (remotecodec == 3)
		len = l1oip_4bit_to_law(buf, len, p);
	अन्यथा
		स_नकल(p, buf, len);

	/* send message up */
	अगर (dch && len >= 2) अणु
		dch->rx_skb = nskb;
		recv_Dchannel(dch);
	पूर्ण
	अगर (bch) अणु
		/* expand 16 bit sequence number to 32 bit sequence number */
		rx_counter = hc->chan[channel].rx_counter;
		अगर (((s16)(समयbase - rx_counter)) >= 0) अणु
			/* समय has changed क्रमward */
			अगर (समयbase >= (rx_counter & 0xffff))
				rx_counter =
					(rx_counter & 0xffff0000) | समयbase;
			अन्यथा
				rx_counter = ((rx_counter & 0xffff0000) + 0x10000)
					| समयbase;
		पूर्ण अन्यथा अणु
			/* समय has changed backwards */
			अगर (समयbase < (rx_counter & 0xffff))
				rx_counter =
					(rx_counter & 0xffff0000) | समयbase;
			अन्यथा
				rx_counter = ((rx_counter & 0xffff0000) - 0x10000)
					| समयbase;
		पूर्ण
		hc->chan[channel].rx_counter = rx_counter;

#अगर_घोषित REORDER_DEBUG
		अगर (hc->chan[channel].disorder_flag) अणु
			swap(hc->chan[channel].disorder_skb, nskb);
			swap(hc->chan[channel].disorder_cnt, rx_counter);
		पूर्ण
		hc->chan[channel].disorder_flag ^= 1;
		अगर (nskb)
#पूर्ण_अगर
			queue_ch_frame(&bch->ch, PH_DATA_IND, rx_counter, nskb);
	पूर्ण
पूर्ण


/*
 * parse frame and extract channel data
 */
अटल व्योम
l1oip_socket_parse(काष्ठा l1oip *hc, काष्ठा sockaddr_in *sin, u8 *buf, पूर्णांक len)
अणु
	u32			packet_id;
	u8			channel;
	u8			remotecodec;
	u16			समयbase;
	पूर्णांक			m, mlen;
	पूर्णांक			len_start = len; /* initial frame length */
	काष्ठा dchannel		*dch = hc->chan[hc->d_idx].dch;

	अगर (debug & DEBUG_L1OIP_MSG)
		prपूर्णांकk(KERN_DEBUG "%s: received frame, parsing... (%d)\n",
		       __func__, len);

	/* check length */
	अगर (len < 1 + 1 + 2) अणु
		prपूर्णांकk(KERN_WARNING "%s: packet error - length %d below "
		       "4 bytes\n", __func__, len);
		वापस;
	पूर्ण

	/* check version */
	अगर (((*buf) >> 6) != L1OIP_VERSION) अणु
		prपूर्णांकk(KERN_WARNING "%s: packet error - unknown version %d\n",
		       __func__, buf[0]>>6);
		वापस;
	पूर्ण

	/* check type */
	अगर (((*buf) & 0x20) && !hc->pri) अणु
		prपूर्णांकk(KERN_WARNING "%s: packet error - received E1 packet "
		       "on S0 interface\n", __func__);
		वापस;
	पूर्ण
	अगर (!((*buf) & 0x20) && hc->pri) अणु
		prपूर्णांकk(KERN_WARNING "%s: packet error - received S0 packet "
		       "on E1 interface\n", __func__);
		वापस;
	पूर्ण

	/* get id flag */
	packet_id = (*buf >> 4) & 1;

	/* check coding */
	remotecodec = (*buf) & 0x0f;
	अगर (remotecodec > 3) अणु
		prपूर्णांकk(KERN_WARNING "%s: packet error - remotecodec %d "
		       "unsupported\n", __func__, remotecodec);
		वापस;
	पूर्ण
	buf++;
	len--;

	/* check packet_id */
	अगर (packet_id) अणु
		अगर (!hc->id) अणु
			prपूर्णांकk(KERN_WARNING "%s: packet error - packet has id "
			       "0x%x, but we have not\n", __func__, packet_id);
			वापस;
		पूर्ण
		अगर (len < 4) अणु
			prपूर्णांकk(KERN_WARNING "%s: packet error - packet too "
			       "short for ID value\n", __func__);
			वापस;
		पूर्ण
		packet_id = (*buf++) << 24;
		packet_id += (*buf++) << 16;
		packet_id += (*buf++) << 8;
		packet_id += (*buf++);
		len -= 4;

		अगर (packet_id != hc->id) अणु
			prपूर्णांकk(KERN_WARNING "%s: packet error - ID mismatch, "
			       "got 0x%x, we 0x%x\n",
			       __func__, packet_id, hc->id);
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (hc->id) अणु
			prपूर्णांकk(KERN_WARNING "%s: packet error - packet has no "
			       "ID, but we have\n", __func__);
			वापस;
		पूर्ण
	पूर्ण

multअगरrame:
	अगर (len < 1) अणु
		prपूर्णांकk(KERN_WARNING "%s: packet error - packet too short, "
		       "channel expected at position %d.\n",
		       __func__, len-len_start + 1);
		वापस;
	पूर्ण

	/* get channel and multअगरrame flag */
	channel = *buf & 0x7f;
	m = *buf >> 7;
	buf++;
	len--;

	/* check length on multअगरrame */
	अगर (m) अणु
		अगर (len < 1) अणु
			prपूर्णांकk(KERN_WARNING "%s: packet error - packet too "
			       "short, length expected at position %d.\n",
			       __func__, len_start - len - 1);
			वापस;
		पूर्ण

		mlen = *buf++;
		len--;
		अगर (mlen == 0)
			mlen = 256;
		अगर (len < mlen + 3) अणु
			prपूर्णांकk(KERN_WARNING "%s: packet error - length %d at "
			       "position %d exceeds total length %d.\n",
			       __func__, mlen, len_start-len - 1, len_start);
			वापस;
		पूर्ण
		अगर (len == mlen + 3) अणु
			prपूर्णांकk(KERN_WARNING "%s: packet error - length %d at "
			       "position %d will not allow additional "
			       "packet.\n",
			       __func__, mlen, len_start-len + 1);
			वापस;
		पूर्ण
	पूर्ण अन्यथा
		mlen = len - 2; /* single frame, subtract समयbase */

	अगर (len < 2) अणु
		prपूर्णांकk(KERN_WARNING "%s: packet error - packet too short, time "
		       "base expected at position %d.\n",
		       __func__, len-len_start + 1);
		वापस;
	पूर्ण

	/* get समय base */
	समयbase = (*buf++) << 8;
	समयbase |= (*buf++);
	len -= 2;

	/* अगर inactive, we send up a PH_ACTIVATE and activate */
	अगर (!test_bit(FLG_ACTIVE, &dch->Flags)) अणु
		अगर (debug & (DEBUG_L1OIP_MSG | DEBUG_L1OIP_SOCKET))
			prपूर्णांकk(KERN_DEBUG "%s: interface become active due to "
			       "received packet\n", __func__);
		test_and_set_bit(FLG_ACTIVE, &dch->Flags);
		_queue_data(&dch->dev.D, PH_ACTIVATE_IND, MISDN_ID_ANY, 0,
			    शून्य, GFP_ATOMIC);
	पूर्ण

	/* distribute packet */
	l1oip_socket_recv(hc, remotecodec, channel, समयbase, buf, mlen);
	buf += mlen;
	len -= mlen;

	/* multअगरrame */
	अगर (m)
		जाओ multअगरrame;

	/* restart समयr */
	अगर (समय_beक्रमe(hc->समयout_tl.expires, jअगरfies + 5 * HZ) || !hc->समयout_on) अणु
		hc->समयout_on = 1;
		mod_समयr(&hc->समयout_tl, jअगरfies + L1OIP_TIMEOUT * HZ);
	पूर्ण अन्यथा /* only adjust समयr */
		hc->समयout_tl.expires = jअगरfies + L1OIP_TIMEOUT * HZ;

	/* अगर ip or source port changes */
	अगर ((hc->sin_remote.sin_addr.s_addr != sin->sin_addr.s_addr)
	    || (hc->sin_remote.sin_port != sin->sin_port)) अणु
		अगर (debug & DEBUG_L1OIP_SOCKET)
			prपूर्णांकk(KERN_DEBUG "%s: remote address changes from "
			       "0x%08x to 0x%08x (port %d to %d)\n", __func__,
			       ntohl(hc->sin_remote.sin_addr.s_addr),
			       ntohl(sin->sin_addr.s_addr),
			       ntohs(hc->sin_remote.sin_port),
			       ntohs(sin->sin_port));
		hc->sin_remote.sin_addr.s_addr = sin->sin_addr.s_addr;
		hc->sin_remote.sin_port = sin->sin_port;
	पूर्ण
पूर्ण


/*
 * socket stuff
 */
अटल पूर्णांक
l1oip_socket_thपढ़ो(व्योम *data)
अणु
	काष्ठा l1oip *hc = (काष्ठा l1oip *)data;
	पूर्णांक ret = 0;
	काष्ठा sockaddr_in sin_rx;
	काष्ठा kvec iov;
	काष्ठा msghdr msg = अणु.msg_name = &sin_rx,
			     .msg_namelen = माप(sin_rx)पूर्ण;
	अचिन्हित अक्षर *recvbuf;
	माप_प्रकार recvbuf_size = 1500;
	पूर्णांक recvlen;
	काष्ठा socket *socket = शून्य;
	DECLARE_COMPLETION_ONSTACK(रुको);

	/* allocate buffer memory */
	recvbuf = kदो_स्मृति(recvbuf_size, GFP_KERNEL);
	अगर (!recvbuf) अणु
		prपूर्णांकk(KERN_ERR "%s: Failed to alloc recvbuf.\n", __func__);
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	iov.iov_base = recvbuf;
	iov.iov_len = recvbuf_size;

	/* make daemon */
	allow_संकेत(संक_इति);

	/* create socket */
	अगर (sock_create(PF_INET, SOCK_DGRAM, IPPROTO_UDP, &socket)) अणु
		prपूर्णांकk(KERN_ERR "%s: Failed to create socket.\n", __func__);
		ret = -EIO;
		जाओ fail;
	पूर्ण

	/* set incoming address */
	hc->sin_local.sin_family = AF_INET;
	hc->sin_local.sin_addr.s_addr = INADDR_ANY;
	hc->sin_local.sin_port = htons((अचिन्हित लघु)hc->localport);

	/* set outgoing address */
	hc->sin_remote.sin_family = AF_INET;
	hc->sin_remote.sin_addr.s_addr = htonl(hc->remoteip);
	hc->sin_remote.sin_port = htons((अचिन्हित लघु)hc->remoteport);

	/* bind to incoming port */
	अगर (socket->ops->bind(socket, (काष्ठा sockaddr *)&hc->sin_local,
			      माप(hc->sin_local))) अणु
		prपूर्णांकk(KERN_ERR "%s: Failed to bind socket to port %d.\n",
		       __func__, hc->localport);
		ret = -EINVAL;
		जाओ fail;
	पूर्ण

	/* check sk */
	अगर (socket->sk == शून्य) अणु
		prपूर्णांकk(KERN_ERR "%s: socket->sk == NULL\n", __func__);
		ret = -EIO;
		जाओ fail;
	पूर्ण

	/* build send message */
	hc->sendmsg.msg_name = &hc->sin_remote;
	hc->sendmsg.msg_namelen = माप(hc->sin_remote);
	hc->sendmsg.msg_control = शून्य;
	hc->sendmsg.msg_controllen = 0;

	/* give away socket */
	spin_lock(&hc->socket_lock);
	hc->socket = socket;
	spin_unlock(&hc->socket_lock);

	/* पढ़ो loop */
	अगर (debug & DEBUG_L1OIP_SOCKET)
		prपूर्णांकk(KERN_DEBUG "%s: socket created and open\n",
		       __func__);
	जबतक (!संकेत_pending(current)) अणु
		iov_iter_kvec(&msg.msg_iter, READ, &iov, 1, recvbuf_size);
		recvlen = sock_recvmsg(socket, &msg, 0);
		अगर (recvlen > 0) अणु
			l1oip_socket_parse(hc, &sin_rx, recvbuf, recvlen);
		पूर्ण अन्यथा अणु
			अगर (debug & DEBUG_L1OIP_SOCKET)
				prपूर्णांकk(KERN_WARNING
				       "%s: broken pipe on socket\n", __func__);
		पूर्ण
	पूर्ण

	/* get socket back, check first अगर in use, maybe by send function */
	spin_lock(&hc->socket_lock);
	/* अगर hc->socket is शून्य, it is in use until it is given back */
	जबतक (!hc->socket) अणु
		spin_unlock(&hc->socket_lock);
		schedule_समयout(HZ / 10);
		spin_lock(&hc->socket_lock);
	पूर्ण
	hc->socket = शून्य;
	spin_unlock(&hc->socket_lock);

	अगर (debug & DEBUG_L1OIP_SOCKET)
		prपूर्णांकk(KERN_DEBUG "%s: socket thread terminating\n",
		       __func__);

fail:
	/* मुक्त recvbuf */
	kमुक्त(recvbuf);

	/* बंद socket */
	अगर (socket)
		sock_release(socket);

	/* अगर we got समाप्तed, संकेत completion */
	complete(&hc->socket_complete);
	hc->socket_thपढ़ो = शून्य; /* show termination of thपढ़ो */

	अगर (debug & DEBUG_L1OIP_SOCKET)
		prपूर्णांकk(KERN_DEBUG "%s: socket thread terminated\n",
		       __func__);
	वापस ret;
पूर्ण

अटल व्योम
l1oip_socket_बंद(काष्ठा l1oip *hc)
अणु
	काष्ठा dchannel *dch = hc->chan[hc->d_idx].dch;

	/* समाप्त thपढ़ो */
	अगर (hc->socket_thपढ़ो) अणु
		अगर (debug & DEBUG_L1OIP_SOCKET)
			prपूर्णांकk(KERN_DEBUG "%s: socket thread exists, "
			       "killing...\n", __func__);
		send_sig(संक_इति, hc->socket_thपढ़ो, 0);
		रुको_क्रम_completion(&hc->socket_complete);
	पूर्ण

	/* अगर active, we send up a PH_DEACTIVATE and deactivate */
	अगर (test_bit(FLG_ACTIVE, &dch->Flags)) अणु
		अगर (debug & (DEBUG_L1OIP_MSG | DEBUG_L1OIP_SOCKET))
			prपूर्णांकk(KERN_DEBUG "%s: interface become deactivated "
			       "due to timeout\n", __func__);
		test_and_clear_bit(FLG_ACTIVE, &dch->Flags);
		_queue_data(&dch->dev.D, PH_DEACTIVATE_IND, MISDN_ID_ANY, 0,
			    शून्य, GFP_ATOMIC);
	पूर्ण
पूर्ण

अटल पूर्णांक
l1oip_socket_खोलो(काष्ठा l1oip *hc)
अणु
	/* in हाल of reखोलो, we need to बंद first */
	l1oip_socket_बंद(hc);

	init_completion(&hc->socket_complete);

	/* create receive process */
	hc->socket_thपढ़ो = kthपढ़ो_run(l1oip_socket_thपढ़ो, hc, "l1oip_%s",
					hc->name);
	अगर (IS_ERR(hc->socket_thपढ़ो)) अणु
		पूर्णांक err = PTR_ERR(hc->socket_thपढ़ो);
		prपूर्णांकk(KERN_ERR "%s: Failed (%d) to create socket process.\n",
		       __func__, err);
		hc->socket_thपढ़ो = शून्य;
		sock_release(hc->socket);
		वापस err;
	पूर्ण
	अगर (debug & DEBUG_L1OIP_SOCKET)
		prपूर्णांकk(KERN_DEBUG "%s: socket thread created\n", __func__);

	वापस 0;
पूर्ण


अटल व्योम
l1oip_send_bh(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा l1oip *hc = container_of(work, काष्ठा l1oip, workq);

	अगर (debug & (DEBUG_L1OIP_MSG | DEBUG_L1OIP_SOCKET))
		prपूर्णांकk(KERN_DEBUG "%s: keepalive timer expired, sending empty "
		       "frame on dchannel\n", __func__);

	/* send an empty l1oip frame at D-channel */
	l1oip_socket_send(hc, 0, hc->d_idx, 0, 0, शून्य, 0);
पूर्ण


/*
 * समयr stuff
 */
अटल व्योम
l1oip_keepalive(काष्ठा समयr_list *t)
अणु
	काष्ठा l1oip *hc = from_समयr(hc, t, keep_tl);

	schedule_work(&hc->workq);
पूर्ण

अटल व्योम
l1oip_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा l1oip			*hc = from_समयr(hc, t,
								  समयout_tl);
	काष्ठा dchannel		*dch = hc->chan[hc->d_idx].dch;

	अगर (debug & DEBUG_L1OIP_MSG)
		prपूर्णांकk(KERN_DEBUG "%s: timeout timer expired, turn layer one "
		       "down.\n", __func__);

	hc->समयout_on = 0; /* state that समयr must be initialized next समय */

	/* अगर समयout, we send up a PH_DEACTIVATE and deactivate */
	अगर (test_bit(FLG_ACTIVE, &dch->Flags)) अणु
		अगर (debug & (DEBUG_L1OIP_MSG | DEBUG_L1OIP_SOCKET))
			prपूर्णांकk(KERN_DEBUG "%s: interface become deactivated "
			       "due to timeout\n", __func__);
		test_and_clear_bit(FLG_ACTIVE, &dch->Flags);
		_queue_data(&dch->dev.D, PH_DEACTIVATE_IND, MISDN_ID_ANY, 0,
			    शून्य, GFP_ATOMIC);
	पूर्ण

	/* अगर we have ondemand set, we हटाओ ip address */
	अगर (hc->ondemand) अणु
		अगर (debug & DEBUG_L1OIP_MSG)
			prपूर्णांकk(KERN_DEBUG "%s: on demand causes ip address to "
			       "be removed\n", __func__);
		hc->sin_remote.sin_addr.s_addr = 0;
	पूर्ण
पूर्ण


/*
 * message handling
 */
अटल पूर्णांक
handle_dmsg(काष्ठा mISDNchannel *ch, काष्ठा sk_buff *skb)
अणु
	काष्ठा mISDNdevice	*dev = container_of(ch, काष्ठा mISDNdevice, D);
	काष्ठा dchannel		*dch = container_of(dev, काष्ठा dchannel, dev);
	काष्ठा l1oip			*hc = dch->hw;
	काष्ठा mISDNhead	*hh = mISDN_HEAD_P(skb);
	पूर्णांक			ret = -EINVAL;
	पूर्णांक			l, ll;
	अचिन्हित अक्षर		*p;

	चयन (hh->prim) अणु
	हाल PH_DATA_REQ:
		अगर (skb->len < 1) अणु
			prपूर्णांकk(KERN_WARNING "%s: skb too small\n",
			       __func__);
			अवरोध;
		पूर्ण
		अगर (skb->len > MAX_DFRAME_LEN_L1 || skb->len > L1OIP_MAX_LEN) अणु
			prपूर्णांकk(KERN_WARNING "%s: skb too large\n",
			       __func__);
			अवरोध;
		पूर्ण
		/* send frame */
		p = skb->data;
		l = skb->len;
		जबतक (l) अणु
			/*
			 * This is technically bounded by L1OIP_MAX_PERFRAME but
			 * MAX_DFRAME_LEN_L1 < L1OIP_MAX_PERFRAME
			 */
			ll = (l < MAX_DFRAME_LEN_L1) ? l : MAX_DFRAME_LEN_L1;
			l1oip_socket_send(hc, 0, dch->slot, 0,
					  hc->chan[dch->slot].tx_counter++, p, ll);
			p += ll;
			l -= ll;
		पूर्ण
		skb_trim(skb, 0);
		queue_ch_frame(ch, PH_DATA_CNF, hh->id, skb);
		वापस 0;
	हाल PH_ACTIVATE_REQ:
		अगर (debug & (DEBUG_L1OIP_MSG | DEBUG_L1OIP_SOCKET))
			prपूर्णांकk(KERN_DEBUG "%s: PH_ACTIVATE channel %d (1..%d)\n"
			       , __func__, dch->slot, hc->b_num + 1);
		skb_trim(skb, 0);
		अगर (test_bit(FLG_ACTIVE, &dch->Flags))
			queue_ch_frame(ch, PH_ACTIVATE_IND, hh->id, skb);
		अन्यथा
			queue_ch_frame(ch, PH_DEACTIVATE_IND, hh->id, skb);
		वापस 0;
	हाल PH_DEACTIVATE_REQ:
		अगर (debug & (DEBUG_L1OIP_MSG | DEBUG_L1OIP_SOCKET))
			prपूर्णांकk(KERN_DEBUG "%s: PH_DEACTIVATE channel %d "
			       "(1..%d)\n", __func__, dch->slot,
			       hc->b_num + 1);
		skb_trim(skb, 0);
		अगर (test_bit(FLG_ACTIVE, &dch->Flags))
			queue_ch_frame(ch, PH_ACTIVATE_IND, hh->id, skb);
		अन्यथा
			queue_ch_frame(ch, PH_DEACTIVATE_IND, hh->id, skb);
		वापस 0;
	पूर्ण
	अगर (!ret)
		dev_kमुक्त_skb(skb);
	वापस ret;
पूर्ण

अटल पूर्णांक
channel_dctrl(काष्ठा dchannel *dch, काष्ठा mISDN_ctrl_req *cq)
अणु
	पूर्णांक	ret = 0;
	काष्ठा l1oip	*hc = dch->hw;

	चयन (cq->op) अणु
	हाल MISDN_CTRL_GETOP:
		cq->op = MISDN_CTRL_SETPEER | MISDN_CTRL_UNSETPEER
			| MISDN_CTRL_GETPEER;
		अवरोध;
	हाल MISDN_CTRL_SETPEER:
		hc->remoteip = (u32)cq->p1;
		hc->remoteport = cq->p2 & 0xffff;
		hc->localport = cq->p2 >> 16;
		अगर (!hc->remoteport)
			hc->remoteport = hc->localport;
		अगर (debug & DEBUG_L1OIP_SOCKET)
			prपूर्णांकk(KERN_DEBUG "%s: got new ip address from user "
			       "space.\n", __func__);
		l1oip_socket_खोलो(hc);
		अवरोध;
	हाल MISDN_CTRL_UNSETPEER:
		अगर (debug & DEBUG_L1OIP_SOCKET)
			prपूर्णांकk(KERN_DEBUG "%s: removing ip address.\n",
			       __func__);
		hc->remoteip = 0;
		l1oip_socket_खोलो(hc);
		अवरोध;
	हाल MISDN_CTRL_GETPEER:
		अगर (debug & DEBUG_L1OIP_SOCKET)
			prपूर्णांकk(KERN_DEBUG "%s: getting ip address.\n",
			       __func__);
		cq->p1 = hc->remoteip;
		cq->p2 = hc->remoteport | (hc->localport << 16);
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_WARNING "%s: unknown Op %x\n",
		       __func__, cq->op);
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक
खोलो_dchannel(काष्ठा l1oip *hc, काष्ठा dchannel *dch, काष्ठा channel_req *rq)
अणु
	अगर (debug & DEBUG_HW_OPEN)
		prपूर्णांकk(KERN_DEBUG "%s: dev(%d) open from %p\n", __func__,
		       dch->dev.id, __builtin_वापस_address(0));
	अगर (rq->protocol == ISDN_P_NONE)
		वापस -EINVAL;
	अगर ((dch->dev.D.protocol != ISDN_P_NONE) &&
	    (dch->dev.D.protocol != rq->protocol)) अणु
		अगर (debug & DEBUG_HW_OPEN)
			prपूर्णांकk(KERN_WARNING "%s: change protocol %x to %x\n",
			       __func__, dch->dev.D.protocol, rq->protocol);
	पूर्ण
	अगर (dch->dev.D.protocol != rq->protocol)
		dch->dev.D.protocol = rq->protocol;

	अगर (test_bit(FLG_ACTIVE, &dch->Flags)) अणु
		_queue_data(&dch->dev.D, PH_ACTIVATE_IND, MISDN_ID_ANY,
			    0, शून्य, GFP_KERNEL);
	पूर्ण
	rq->ch = &dch->dev.D;
	अगर (!try_module_get(THIS_MODULE))
		prपूर्णांकk(KERN_WARNING "%s:cannot get module\n", __func__);
	वापस 0;
पूर्ण

अटल पूर्णांक
खोलो_bchannel(काष्ठा l1oip *hc, काष्ठा dchannel *dch, काष्ठा channel_req *rq)
अणु
	काष्ठा bchannel	*bch;
	पूर्णांक		ch;

	अगर (!test_channelmap(rq->adr.channel, dch->dev.channelmap))
		वापस -EINVAL;
	अगर (rq->protocol == ISDN_P_NONE)
		वापस -EINVAL;
	ch = rq->adr.channel; /* BRI: 1=B1 2=B2  PRI: 1..15,17.. */
	bch = hc->chan[ch].bch;
	अगर (!bch) अणु
		prपूर्णांकk(KERN_ERR "%s:internal error ch %d has no bch\n",
		       __func__, ch);
		वापस -EINVAL;
	पूर्ण
	अगर (test_and_set_bit(FLG_OPEN, &bch->Flags))
		वापस -EBUSY; /* b-channel can be only खोलो once */
	bch->ch.protocol = rq->protocol;
	rq->ch = &bch->ch;
	अगर (!try_module_get(THIS_MODULE))
		prपूर्णांकk(KERN_WARNING "%s:cannot get module\n", __func__);
	वापस 0;
पूर्ण

अटल पूर्णांक
l1oip_dctrl(काष्ठा mISDNchannel *ch, u_पूर्णांक cmd, व्योम *arg)
अणु
	काष्ठा mISDNdevice	*dev = container_of(ch, काष्ठा mISDNdevice, D);
	काष्ठा dchannel		*dch = container_of(dev, काष्ठा dchannel, dev);
	काष्ठा l1oip			*hc = dch->hw;
	काष्ठा channel_req	*rq;
	पूर्णांक			err = 0;

	अगर (dch->debug & DEBUG_HW)
		prपूर्णांकk(KERN_DEBUG "%s: cmd:%x %p\n",
		       __func__, cmd, arg);
	चयन (cmd) अणु
	हाल OPEN_CHANNEL:
		rq = arg;
		चयन (rq->protocol) अणु
		हाल ISDN_P_TE_S0:
		हाल ISDN_P_NT_S0:
			अगर (hc->pri) अणु
				err = -EINVAL;
				अवरोध;
			पूर्ण
			err = खोलो_dchannel(hc, dch, rq);
			अवरोध;
		हाल ISDN_P_TE_E1:
		हाल ISDN_P_NT_E1:
			अगर (!hc->pri) अणु
				err = -EINVAL;
				अवरोध;
			पूर्ण
			err = खोलो_dchannel(hc, dch, rq);
			अवरोध;
		शेष:
			err = खोलो_bchannel(hc, dch, rq);
		पूर्ण
		अवरोध;
	हाल CLOSE_CHANNEL:
		अगर (debug & DEBUG_HW_OPEN)
			prपूर्णांकk(KERN_DEBUG "%s: dev(%d) close from %p\n",
			       __func__, dch->dev.id,
			       __builtin_वापस_address(0));
		module_put(THIS_MODULE);
		अवरोध;
	हाल CONTROL_CHANNEL:
		err = channel_dctrl(dch, arg);
		अवरोध;
	शेष:
		अगर (dch->debug & DEBUG_HW)
			prपूर्णांकk(KERN_DEBUG "%s: unknown command %x\n",
			       __func__, cmd);
		err = -EINVAL;
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक
handle_bmsg(काष्ठा mISDNchannel *ch, काष्ठा sk_buff *skb)
अणु
	काष्ठा bchannel		*bch = container_of(ch, काष्ठा bchannel, ch);
	काष्ठा l1oip			*hc = bch->hw;
	पूर्णांक			ret = -EINVAL;
	काष्ठा mISDNhead	*hh = mISDN_HEAD_P(skb);
	पूर्णांक			l, ll;
	अचिन्हित अक्षर		*p;

	चयन (hh->prim) अणु
	हाल PH_DATA_REQ:
		अगर (skb->len <= 0) अणु
			prपूर्णांकk(KERN_WARNING "%s: skb too small\n",
			       __func__);
			अवरोध;
		पूर्ण
		अगर (skb->len > MAX_DFRAME_LEN_L1 || skb->len > L1OIP_MAX_LEN) अणु
			prपूर्णांकk(KERN_WARNING "%s: skb too large\n",
			       __func__);
			अवरोध;
		पूर्ण
		/* check क्रम AIS / ulaw-silence */
		l = skb->len;
		अगर (!स_प्रथम_inv(skb->data, 0xff, l)) अणु
			अगर (debug & DEBUG_L1OIP_MSG)
				prपूर्णांकk(KERN_DEBUG "%s: got AIS, not sending, "
				       "but counting\n", __func__);
			hc->chan[bch->slot].tx_counter += l;
			skb_trim(skb, 0);
			queue_ch_frame(ch, PH_DATA_CNF, hh->id, skb);
			वापस 0;
		पूर्ण
		/* check क्रम silence */
		l = skb->len;
		अगर (!स_प्रथम_inv(skb->data, 0x2a, l)) अणु
			अगर (debug & DEBUG_L1OIP_MSG)
				prपूर्णांकk(KERN_DEBUG "%s: got silence, not sending"
				       ", but counting\n", __func__);
			hc->chan[bch->slot].tx_counter += l;
			skb_trim(skb, 0);
			queue_ch_frame(ch, PH_DATA_CNF, hh->id, skb);
			वापस 0;
		पूर्ण

		/* send frame */
		p = skb->data;
		l = skb->len;
		जबतक (l) अणु
			/*
			 * This is technically bounded by L1OIP_MAX_PERFRAME but
			 * MAX_DFRAME_LEN_L1 < L1OIP_MAX_PERFRAME
			 */
			ll = (l < MAX_DFRAME_LEN_L1) ? l : MAX_DFRAME_LEN_L1;
			l1oip_socket_send(hc, hc->codec, bch->slot, 0,
					  hc->chan[bch->slot].tx_counter, p, ll);
			hc->chan[bch->slot].tx_counter += ll;
			p += ll;
			l -= ll;
		पूर्ण
		skb_trim(skb, 0);
		queue_ch_frame(ch, PH_DATA_CNF, hh->id, skb);
		वापस 0;
	हाल PH_ACTIVATE_REQ:
		अगर (debug & (DEBUG_L1OIP_MSG | DEBUG_L1OIP_SOCKET))
			prपूर्णांकk(KERN_DEBUG "%s: PH_ACTIVATE channel %d (1..%d)\n"
			       , __func__, bch->slot, hc->b_num + 1);
		hc->chan[bch->slot].codecstate = 0;
		test_and_set_bit(FLG_ACTIVE, &bch->Flags);
		skb_trim(skb, 0);
		queue_ch_frame(ch, PH_ACTIVATE_IND, hh->id, skb);
		वापस 0;
	हाल PH_DEACTIVATE_REQ:
		अगर (debug & (DEBUG_L1OIP_MSG | DEBUG_L1OIP_SOCKET))
			prपूर्णांकk(KERN_DEBUG "%s: PH_DEACTIVATE channel %d "
			       "(1..%d)\n", __func__, bch->slot,
			       hc->b_num + 1);
		test_and_clear_bit(FLG_ACTIVE, &bch->Flags);
		skb_trim(skb, 0);
		queue_ch_frame(ch, PH_DEACTIVATE_IND, hh->id, skb);
		वापस 0;
	पूर्ण
	अगर (!ret)
		dev_kमुक्त_skb(skb);
	वापस ret;
पूर्ण

अटल पूर्णांक
channel_bctrl(काष्ठा bchannel *bch, काष्ठा mISDN_ctrl_req *cq)
अणु
	पूर्णांक			ret = 0;
	काष्ठा dsp_features	*features =
		(काष्ठा dsp_features *)(*((u_दीर्घ *)&cq->p1));

	चयन (cq->op) अणु
	हाल MISDN_CTRL_GETOP:
		cq->op = MISDN_CTRL_HW_FEATURES_OP;
		अवरोध;
	हाल MISDN_CTRL_HW_FEATURES: /* fill features काष्ठाure */
		अगर (debug & DEBUG_L1OIP_MSG)
			prपूर्णांकk(KERN_DEBUG "%s: HW_FEATURE request\n",
			       __func__);
		/* create confirm */
		features->unघड़ीed = 1;
		features->unordered = 1;
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_WARNING "%s: unknown Op %x\n",
		       __func__, cq->op);
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक
l1oip_bctrl(काष्ठा mISDNchannel *ch, u_पूर्णांक cmd, व्योम *arg)
अणु
	काष्ठा bchannel	*bch = container_of(ch, काष्ठा bchannel, ch);
	पूर्णांक		err = -EINVAL;

	अगर (bch->debug & DEBUG_HW)
		prपूर्णांकk(KERN_DEBUG "%s: cmd:%x %p\n",
		       __func__, cmd, arg);
	चयन (cmd) अणु
	हाल CLOSE_CHANNEL:
		test_and_clear_bit(FLG_OPEN, &bch->Flags);
		test_and_clear_bit(FLG_ACTIVE, &bch->Flags);
		ch->protocol = ISDN_P_NONE;
		ch->peer = शून्य;
		module_put(THIS_MODULE);
		err = 0;
		अवरोध;
	हाल CONTROL_CHANNEL:
		err = channel_bctrl(bch, arg);
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_WARNING "%s: unknown prim(%x)\n",
		       __func__, cmd);
	पूर्ण
	वापस err;
पूर्ण


/*
 * cleanup module and stack
 */
अटल व्योम
release_card(काष्ठा l1oip *hc)
अणु
	पूर्णांक	ch;

	अगर (समयr_pending(&hc->keep_tl))
		del_समयr(&hc->keep_tl);

	अगर (समयr_pending(&hc->समयout_tl))
		del_समयr(&hc->समयout_tl);

	cancel_work_sync(&hc->workq);

	अगर (hc->socket_thपढ़ो)
		l1oip_socket_बंद(hc);

	अगर (hc->रेजिस्टरed && hc->chan[hc->d_idx].dch)
		mISDN_unरेजिस्टर_device(&hc->chan[hc->d_idx].dch->dev);
	क्रम (ch = 0; ch < 128; ch++) अणु
		अगर (hc->chan[ch].dch) अणु
			mISDN_मुक्तdchannel(hc->chan[ch].dch);
			kमुक्त(hc->chan[ch].dch);
		पूर्ण
		अगर (hc->chan[ch].bch) अणु
			mISDN_मुक्तbchannel(hc->chan[ch].bch);
			kमुक्त(hc->chan[ch].bch);
#अगर_घोषित REORDER_DEBUG
			dev_kमुक्त_skb(hc->chan[ch].disorder_skb);
#पूर्ण_अगर
		पूर्ण
	पूर्ण

	spin_lock(&l1oip_lock);
	list_del(&hc->list);
	spin_unlock(&l1oip_lock);

	kमुक्त(hc);
पूर्ण

अटल व्योम
l1oip_cleanup(व्योम)
अणु
	काष्ठा l1oip *hc, *next;

	list_क्रम_each_entry_safe(hc, next, &l1oip_ilist, list)
		release_card(hc);

	l1oip_4bit_मुक्त();
पूर्ण


/*
 * module and stack init
 */
अटल पूर्णांक
init_card(काष्ठा l1oip *hc, पूर्णांक pri, पूर्णांक bundle)
अणु
	काष्ठा dchannel	*dch;
	काष्ठा bchannel	*bch;
	पूर्णांक		ret;
	पूर्णांक		i, ch;

	spin_lock_init(&hc->socket_lock);
	hc->idx = l1oip_cnt;
	hc->pri = pri;
	hc->d_idx = pri ? 16 : 3;
	hc->b_num = pri ? 30 : 2;
	hc->bundle = bundle;
	अगर (hc->pri)
		प्र_लिखो(hc->name, "l1oip-e1.%d", l1oip_cnt + 1);
	अन्यथा
		प्र_लिखो(hc->name, "l1oip-s0.%d", l1oip_cnt + 1);

	चयन (codec[l1oip_cnt]) अणु
	हाल 0: /* as is */
	हाल 1: /* alaw */
	हाल 2: /* ulaw */
	हाल 3: /* 4bit */
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "Codec(%d) not supported.\n",
		       codec[l1oip_cnt]);
		वापस -EINVAL;
	पूर्ण
	hc->codec = codec[l1oip_cnt];
	अगर (debug & DEBUG_L1OIP_INIT)
		prपूर्णांकk(KERN_DEBUG "%s: using codec %d\n",
		       __func__, hc->codec);

	अगर (id[l1oip_cnt] == 0) अणु
		prपूर्णांकk(KERN_WARNING "Warning: No 'id' value given or "
		       "0, this is highly unsecure. Please use 32 "
		       "bit random number 0x...\n");
	पूर्ण
	hc->id = id[l1oip_cnt];
	अगर (debug & DEBUG_L1OIP_INIT)
		prपूर्णांकk(KERN_DEBUG "%s: using id 0x%x\n", __func__, hc->id);

	hc->ondemand = ondemand[l1oip_cnt];
	अगर (hc->ondemand && !hc->id) अणु
		prपूर्णांकk(KERN_ERR "%s: ondemand option only allowed in "
		       "conjunction with non 0 ID\n", __func__);
		वापस -EINVAL;
	पूर्ण

	अगर (limit[l1oip_cnt])
		hc->b_num = limit[l1oip_cnt];
	अगर (!pri && hc->b_num > 2) अणु
		prपूर्णांकk(KERN_ERR "Maximum limit for BRI interface is 2 "
		       "channels.\n");
		वापस -EINVAL;
	पूर्ण
	अगर (pri && hc->b_num > 126) अणु
		prपूर्णांकk(KERN_ERR "Maximum limit for PRI interface is 126 "
		       "channels.\n");
		वापस -EINVAL;
	पूर्ण
	अगर (pri && hc->b_num > 30) अणु
		prपूर्णांकk(KERN_WARNING "Maximum limit for BRI interface is 30 "
		       "channels.\n");
		prपूर्णांकk(KERN_WARNING "Your selection of %d channels must be "
		       "supported by application.\n", hc->limit);
	पूर्ण

	hc->remoteip = ip[l1oip_cnt << 2] << 24
		| ip[(l1oip_cnt << 2) + 1] << 16
		| ip[(l1oip_cnt << 2) + 2] << 8
		| ip[(l1oip_cnt << 2) + 3];
	hc->localport = port[l1oip_cnt]?:(L1OIP_DEFAULTPORT + l1oip_cnt);
	अगर (remoteport[l1oip_cnt])
		hc->remoteport = remoteport[l1oip_cnt];
	अन्यथा
		hc->remoteport = hc->localport;
	अगर (debug & DEBUG_L1OIP_INIT)
		prपूर्णांकk(KERN_DEBUG "%s: using local port %d remote ip "
		       "%d.%d.%d.%d port %d ondemand %d\n", __func__,
		       hc->localport, hc->remoteip >> 24,
		       (hc->remoteip >> 16) & 0xff,
		       (hc->remoteip >> 8) & 0xff, hc->remoteip & 0xff,
		       hc->remoteport, hc->ondemand);

	dch = kzalloc(माप(काष्ठा dchannel), GFP_KERNEL);
	अगर (!dch)
		वापस -ENOMEM;
	dch->debug = debug;
	mISDN_initdchannel(dch, MAX_DFRAME_LEN_L1, शून्य);
	dch->hw = hc;
	अगर (pri)
		dch->dev.Dprotocols = (1 << ISDN_P_TE_E1) | (1 << ISDN_P_NT_E1);
	अन्यथा
		dch->dev.Dprotocols = (1 << ISDN_P_TE_S0) | (1 << ISDN_P_NT_S0);
	dch->dev.Bprotocols = (1 << (ISDN_P_B_RAW & ISDN_P_B_MASK)) |
		(1 << (ISDN_P_B_HDLC & ISDN_P_B_MASK));
	dch->dev.D.send = handle_dmsg;
	dch->dev.D.ctrl = l1oip_dctrl;
	dch->dev.nrbchan = hc->b_num;
	dch->slot = hc->d_idx;
	hc->chan[hc->d_idx].dch = dch;
	i = 1;
	क्रम (ch = 0; ch < dch->dev.nrbchan; ch++) अणु
		अगर (ch == 15)
			i++;
		bch = kzalloc(माप(काष्ठा bchannel), GFP_KERNEL);
		अगर (!bch) अणु
			prपूर्णांकk(KERN_ERR "%s: no memory for bchannel\n",
			       __func__);
			वापस -ENOMEM;
		पूर्ण
		bch->nr = i + ch;
		bch->slot = i + ch;
		bch->debug = debug;
		mISDN_initbchannel(bch, MAX_DATA_MEM, 0);
		bch->hw = hc;
		bch->ch.send = handle_bmsg;
		bch->ch.ctrl = l1oip_bctrl;
		bch->ch.nr = i + ch;
		list_add(&bch->ch.list, &dch->dev.bchannels);
		hc->chan[i + ch].bch = bch;
		set_channelmap(bch->nr, dch->dev.channelmap);
	पूर्ण
	/* TODO: create a parent device क्रम this driver */
	ret = mISDN_रेजिस्टर_device(&dch->dev, शून्य, hc->name);
	अगर (ret)
		वापस ret;
	hc->रेजिस्टरed = 1;

	अगर (debug & DEBUG_L1OIP_INIT)
		prपूर्णांकk(KERN_DEBUG "%s: Setting up network card(%d)\n",
		       __func__, l1oip_cnt + 1);
	ret = l1oip_socket_खोलो(hc);
	अगर (ret)
		वापस ret;

	समयr_setup(&hc->keep_tl, l1oip_keepalive, 0);
	hc->keep_tl.expires = jअगरfies + 2 * HZ; /* two seconds first समय */
	add_समयr(&hc->keep_tl);

	समयr_setup(&hc->समयout_tl, l1oip_समयout, 0);
	hc->समयout_on = 0; /* state that we have समयr off */

	वापस 0;
पूर्ण

अटल पूर्णांक __init
l1oip_init(व्योम)
अणु
	पूर्णांक		pri, bundle;
	काष्ठा l1oip		*hc;
	पूर्णांक		ret;

	prपूर्णांकk(KERN_INFO "mISDN: Layer-1-over-IP driver Rev. %s\n",
	       l1oip_revision);

	अगर (l1oip_4bit_alloc(ulaw))
		वापस -ENOMEM;

	l1oip_cnt = 0;
	जबतक (l1oip_cnt < MAX_CARDS && type[l1oip_cnt]) अणु
		चयन (type[l1oip_cnt] & 0xff) अणु
		हाल 1:
			pri = 0;
			bundle = 0;
			अवरोध;
		हाल 2:
			pri = 1;
			bundle = 0;
			अवरोध;
		हाल 3:
			pri = 0;
			bundle = 1;
			अवरोध;
		हाल 4:
			pri = 1;
			bundle = 1;
			अवरोध;
		शेष:
			prपूर्णांकk(KERN_ERR "Card type(%d) not supported.\n",
			       type[l1oip_cnt] & 0xff);
			l1oip_cleanup();
			वापस -EINVAL;
		पूर्ण

		अगर (debug & DEBUG_L1OIP_INIT)
			prपूर्णांकk(KERN_DEBUG "%s: interface %d is %s with %s.\n",
			       __func__, l1oip_cnt, pri ? "PRI" : "BRI",
			       bundle ? "bundled IP packet for all B-channels" :
			       "separate IP packets for every B-channel");

		hc = kzalloc(माप(काष्ठा l1oip), GFP_ATOMIC);
		अगर (!hc) अणु
			prपूर्णांकk(KERN_ERR "No kmem for L1-over-IP driver.\n");
			l1oip_cleanup();
			वापस -ENOMEM;
		पूर्ण
		INIT_WORK(&hc->workq, (व्योम *)l1oip_send_bh);

		spin_lock(&l1oip_lock);
		list_add_tail(&hc->list, &l1oip_ilist);
		spin_unlock(&l1oip_lock);

		ret = init_card(hc, pri, bundle);
		अगर (ret) अणु
			l1oip_cleanup();
			वापस ret;
		पूर्ण

		l1oip_cnt++;
	पूर्ण
	prपूर्णांकk(KERN_INFO "%d virtual devices registered\n", l1oip_cnt);
	वापस 0;
पूर्ण

module_init(l1oip_init);
module_निकास(l1oip_cleanup);
