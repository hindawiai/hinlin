<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * Copyright (C) Alan Cox GW4PTS (alan@lxorguk.ukuu.org.uk)
 * Copyright (C) Jonathan Naylor G4KLX (g4klx@g4klx.demon.co.uk)
 * Copyright (C) Joerg Reuter DL1BKE (jreuter@yaina.de)
 * Copyright (C) Hans-Joachim Hetscher DD8NE (dd8ne@bnv-bamberg.de)
 */
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/socket.h>
#समावेश <linux/in.h>
#समावेश <linux/kernel.h>
#समावेश <linux/समयr.h>
#समावेश <linux/माला.स>
#समावेश <linux/sockios.h>
#समावेश <linux/net.h>
#समावेश <linux/slab.h>
#समावेश <net/ax25.h>
#समावेश <linux/inet.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <net/sock.h>
#समावेश <net/tcp_states.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>

/*
 *	Given a fragment, queue it on the fragment queue and अगर the fragment
 *	is complete, send it back to ax25_rx_अगरrame.
 */
अटल पूर्णांक ax25_rx_fragment(ax25_cb *ax25, काष्ठा sk_buff *skb)
अणु
	काष्ठा sk_buff *skbn, *skbo;

	अगर (ax25->fragno != 0) अणु
		अगर (!(*skb->data & AX25_SEG_FIRST)) अणु
			अगर ((ax25->fragno - 1) == (*skb->data & AX25_SEG_REM)) अणु
				/* Enqueue fragment */
				ax25->fragno = *skb->data & AX25_SEG_REM;
				skb_pull(skb, 1);	/* skip fragno */
				ax25->fraglen += skb->len;
				skb_queue_tail(&ax25->frag_queue, skb);

				/* Last fragment received ? */
				अगर (ax25->fragno == 0) अणु
					skbn = alloc_skb(AX25_MAX_HEADER_LEN +
							 ax25->fraglen,
							 GFP_ATOMIC);
					अगर (!skbn) अणु
						skb_queue_purge(&ax25->frag_queue);
						वापस 1;
					पूर्ण

					skb_reserve(skbn, AX25_MAX_HEADER_LEN);

					skbn->dev   = ax25->ax25_dev->dev;
					skb_reset_network_header(skbn);
					skb_reset_transport_header(skbn);

					/* Copy data from the fragments */
					जबतक ((skbo = skb_dequeue(&ax25->frag_queue)) != शून्य) अणु
						skb_copy_from_linear_data(skbo,
							  skb_put(skbn, skbo->len),
									  skbo->len);
						kमुक्त_skb(skbo);
					पूर्ण

					ax25->fraglen = 0;

					अगर (ax25_rx_अगरrame(ax25, skbn) == 0)
						kमुक्त_skb(skbn);
				पूर्ण

				वापस 1;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* First fragment received */
		अगर (*skb->data & AX25_SEG_FIRST) अणु
			skb_queue_purge(&ax25->frag_queue);
			ax25->fragno = *skb->data & AX25_SEG_REM;
			skb_pull(skb, 1);		/* skip fragno */
			ax25->fraglen = skb->len;
			skb_queue_tail(&ax25->frag_queue, skb);
			वापस 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 *	This is where all valid I frames are sent to, to be dispatched to
 *	whichever protocol requires them.
 */
पूर्णांक ax25_rx_अगरrame(ax25_cb *ax25, काष्ठा sk_buff *skb)
अणु
	पूर्णांक (*func)(काष्ठा sk_buff *, ax25_cb *);
	अचिन्हित अक्षर pid;
	पूर्णांक queued = 0;

	अगर (skb == शून्य) वापस 0;

	ax25_start_idleसमयr(ax25);

	pid = *skb->data;

	अगर (pid == AX25_P_IP) अणु
		/* working around a TCP bug to keep additional listeners
		 * happy. TCP re-uses the buffer and destroys the original
		 * content.
		 */
		काष्ठा sk_buff *skbn = skb_copy(skb, GFP_ATOMIC);
		अगर (skbn != शून्य) अणु
			kमुक्त_skb(skb);
			skb = skbn;
		पूर्ण

		skb_pull(skb, 1);	/* Remove PID */
		skb->mac_header = skb->network_header;
		skb_reset_network_header(skb);
		skb->dev      = ax25->ax25_dev->dev;
		skb->pkt_type = PACKET_HOST;
		skb->protocol = htons(ETH_P_IP);
		netअगर_rx(skb);
		वापस 1;
	पूर्ण
	अगर (pid == AX25_P_SEGMENT) अणु
		skb_pull(skb, 1);	/* Remove PID */
		वापस ax25_rx_fragment(ax25, skb);
	पूर्ण

	अगर ((func = ax25_protocol_function(pid)) != शून्य) अणु
		skb_pull(skb, 1);	/* Remove PID */
		वापस (*func)(skb, ax25);
	पूर्ण

	अगर (ax25->sk != शून्य && ax25->ax25_dev->values[AX25_VALUES_CONMODE] == 2) अणु
		अगर ((!ax25->pidincl && ax25->sk->sk_protocol == pid) ||
		    ax25->pidincl) अणु
			अगर (sock_queue_rcv_skb(ax25->sk, skb) == 0)
				queued = 1;
			अन्यथा
				ax25->condition |= AX25_COND_OWN_RX_BUSY;
		पूर्ण
	पूर्ण

	वापस queued;
पूर्ण

/*
 *	Higher level upcall क्रम a LAPB frame
 */
अटल पूर्णांक ax25_process_rx_frame(ax25_cb *ax25, काष्ठा sk_buff *skb, पूर्णांक type, पूर्णांक dama)
अणु
	पूर्णांक queued = 0;

	अगर (ax25->state == AX25_STATE_0)
		वापस 0;

	चयन (ax25->ax25_dev->values[AX25_VALUES_PROTOCOL]) अणु
	हाल AX25_PROTO_STD_SIMPLEX:
	हाल AX25_PROTO_STD_DUPLEX:
		queued = ax25_std_frame_in(ax25, skb, type);
		अवरोध;

#अगर_घोषित CONFIG_AX25_DAMA_SLAVE
	हाल AX25_PROTO_DAMA_SLAVE:
		अगर (dama || ax25->ax25_dev->dama.slave)
			queued = ax25_ds_frame_in(ax25, skb, type);
		अन्यथा
			queued = ax25_std_frame_in(ax25, skb, type);
		अवरोध;
#पूर्ण_अगर
	पूर्ण

	वापस queued;
पूर्ण

अटल पूर्णांक ax25_rcv(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
	ax25_address *dev_addr, काष्ठा packet_type *ptype)
अणु
	ax25_address src, dest, *next_digi = शून्य;
	पूर्णांक type = 0, mine = 0, dama;
	काष्ठा sock *make, *sk;
	ax25_digi dp, reverse_dp;
	ax25_cb *ax25;
	ax25_dev *ax25_dev;

	/*
	 *	Process the AX.25/LAPB frame.
	 */

	skb_reset_transport_header(skb);

	अगर ((ax25_dev = ax25_dev_ax25dev(dev)) == शून्य)
		जाओ मुक्त;

	/*
	 *	Parse the address header.
	 */

	अगर (ax25_addr_parse(skb->data, skb->len, &src, &dest, &dp, &type, &dama) == शून्य)
		जाओ मुक्त;

	/*
	 *	Ours perhaps ?
	 */
	अगर (dp.lastrepeat + 1 < dp.ndigi)		/* Not yet digipeated completely */
		next_digi = &dp.calls[dp.lastrepeat + 1];

	/*
	 *	Pull of the AX.25 headers leaving the CTRL/PID bytes
	 */
	skb_pull(skb, ax25_addr_size(&dp));

	/* For our port addresses ? */
	अगर (ax25cmp(&dest, dev_addr) == 0 && dp.lastrepeat + 1 == dp.ndigi)
		mine = 1;

	/* Also match on any रेजिस्टरed callsign from L3/4 */
	अगर (!mine && ax25_listen_mine(&dest, dev) && dp.lastrepeat + 1 == dp.ndigi)
		mine = 1;

	/* UI frame - bypass LAPB processing */
	अगर ((*skb->data & ~0x10) == AX25_UI && dp.lastrepeat + 1 == dp.ndigi) अणु
		skb_set_transport_header(skb, 2); /* skip control and pid */

		ax25_send_to_raw(&dest, skb, skb->data[1]);

		अगर (!mine && ax25cmp(&dest, (ax25_address *)dev->broadcast) != 0)
			जाओ मुक्त;

		/* Now we are poपूर्णांकing at the pid byte */
		चयन (skb->data[1]) अणु
		हाल AX25_P_IP:
			skb_pull(skb,2);		/* drop PID/CTRL */
			skb_reset_transport_header(skb);
			skb_reset_network_header(skb);
			skb->dev      = dev;
			skb->pkt_type = PACKET_HOST;
			skb->protocol = htons(ETH_P_IP);
			netअगर_rx(skb);
			अवरोध;

		हाल AX25_P_ARP:
			skb_pull(skb,2);
			skb_reset_transport_header(skb);
			skb_reset_network_header(skb);
			skb->dev      = dev;
			skb->pkt_type = PACKET_HOST;
			skb->protocol = htons(ETH_P_ARP);
			netअगर_rx(skb);
			अवरोध;
		हाल AX25_P_TEXT:
			/* Now find a suitable dgram socket */
			sk = ax25_get_socket(&dest, &src, SOCK_DGRAM);
			अगर (sk != शून्य) अणु
				bh_lock_sock(sk);
				अगर (atomic_पढ़ो(&sk->sk_rmem_alloc) >=
				    sk->sk_rcvbuf) अणु
					kमुक्त_skb(skb);
				पूर्ण अन्यथा अणु
					/*
					 *	Remove the control and PID.
					 */
					skb_pull(skb, 2);
					अगर (sock_queue_rcv_skb(sk, skb) != 0)
						kमुक्त_skb(skb);
				पूर्ण
				bh_unlock_sock(sk);
				sock_put(sk);
			पूर्ण अन्यथा अणु
				kमुक्त_skb(skb);
			पूर्ण
			अवरोध;

		शेष:
			kमुक्त_skb(skb);	/* Will scan SOCK_AX25 RAW sockets */
			अवरोध;
		पूर्ण

		वापस 0;
	पूर्ण

	/*
	 *	Is connected mode supported on this device ?
	 *	If not, should we DM the incoming frame (except DMs) or
	 *	silently ignore them. For now we stay quiet.
	 */
	अगर (ax25_dev->values[AX25_VALUES_CONMODE] == 0)
		जाओ मुक्त;

	/* LAPB */

	/* AX.25 state 1-4 */

	ax25_digi_invert(&dp, &reverse_dp);

	अगर ((ax25 = ax25_find_cb(&dest, &src, &reverse_dp, dev)) != शून्य) अणु
		/*
		 *	Process the frame. If it is queued up पूर्णांकernally it
		 *	वापसs one otherwise we मुक्त it immediately. This
		 *	routine itself wakes the user context layers so we करो
		 *	no further work
		 */
		अगर (ax25_process_rx_frame(ax25, skb, type, dama) == 0)
			kमुक्त_skb(skb);

		ax25_cb_put(ax25);
		वापस 0;
	पूर्ण

	/* AX.25 state 0 (disconnected) */

	/* a) received not a SABM(E) */

	अगर ((*skb->data & ~AX25_PF) != AX25_SABM &&
	    (*skb->data & ~AX25_PF) != AX25_SABME) अणु
		/*
		 *	Never reply to a DM. Also ignore any connects क्रम
		 *	addresses that are not our पूर्णांकerfaces and not a socket.
		 */
		अगर ((*skb->data & ~AX25_PF) != AX25_DM && mine)
			ax25_वापस_dm(dev, &src, &dest, &dp);

		जाओ मुक्त;
	पूर्ण

	/* b) received SABM(E) */

	अगर (dp.lastrepeat + 1 == dp.ndigi)
		sk = ax25_find_listener(&dest, 0, dev, SOCK_SEQPACKET);
	अन्यथा
		sk = ax25_find_listener(next_digi, 1, dev, SOCK_SEQPACKET);

	अगर (sk != शून्य) अणु
		bh_lock_sock(sk);
		अगर (sk_acceptq_is_full(sk) ||
		    (make = ax25_make_new(sk, ax25_dev)) == शून्य) अणु
			अगर (mine)
				ax25_वापस_dm(dev, &src, &dest, &dp);
			kमुक्त_skb(skb);
			bh_unlock_sock(sk);
			sock_put(sk);

			वापस 0;
		पूर्ण

		ax25 = sk_to_ax25(make);
		skb_set_owner_r(skb, make);
		skb_queue_head(&sk->sk_receive_queue, skb);

		make->sk_state = TCP_ESTABLISHED;

		sk_acceptq_added(sk);
		bh_unlock_sock(sk);
	पूर्ण अन्यथा अणु
		अगर (!mine)
			जाओ मुक्त;

		अगर ((ax25 = ax25_create_cb()) == शून्य) अणु
			ax25_वापस_dm(dev, &src, &dest, &dp);
			जाओ मुक्त;
		पूर्ण

		ax25_fillin_cb(ax25, ax25_dev);
	पूर्ण

	ax25->source_addr = dest;
	ax25->dest_addr   = src;

	/*
	 *	Sort out any digipeated paths.
	 */
	अगर (dp.ndigi && !ax25->digipeat &&
	    (ax25->digipeat = kदो_स्मृति(माप(ax25_digi), GFP_ATOMIC)) == शून्य) अणु
		kमुक्त_skb(skb);
		ax25_destroy_socket(ax25);
		अगर (sk)
			sock_put(sk);
		वापस 0;
	पूर्ण

	अगर (dp.ndigi == 0) अणु
		kमुक्त(ax25->digipeat);
		ax25->digipeat = शून्य;
	पूर्ण अन्यथा अणु
		/* Reverse the source SABM's path */
		स_नकल(ax25->digipeat, &reverse_dp, माप(ax25_digi));
	पूर्ण

	अगर ((*skb->data & ~AX25_PF) == AX25_SABME) अणु
		ax25->modulus = AX25_EMODULUS;
		ax25->winकरोw  = ax25_dev->values[AX25_VALUES_EWINDOW];
	पूर्ण अन्यथा अणु
		ax25->modulus = AX25_MODULUS;
		ax25->winकरोw  = ax25_dev->values[AX25_VALUES_WINDOW];
	पूर्ण

	ax25_send_control(ax25, AX25_UA, AX25_POLLON, AX25_RESPONSE);

#अगर_घोषित CONFIG_AX25_DAMA_SLAVE
	अगर (dama && ax25->ax25_dev->values[AX25_VALUES_PROTOCOL] == AX25_PROTO_DAMA_SLAVE)
		ax25_dama_on(ax25);
#पूर्ण_अगर

	ax25->state = AX25_STATE_3;

	ax25_cb_add(ax25);

	ax25_start_heartbeat(ax25);
	ax25_start_t3समयr(ax25);
	ax25_start_idleसमयr(ax25);

	अगर (sk) अणु
		अगर (!sock_flag(sk, SOCK_DEAD))
			sk->sk_data_पढ़ोy(sk);
		sock_put(sk);
	पूर्ण अन्यथा अणु
मुक्त:
		kमुक्त_skb(skb);
	पूर्ण
	वापस 0;
पूर्ण

/*
 *	Receive an AX.25 frame via a SLIP पूर्णांकerface.
 */
पूर्णांक ax25_kiss_rcv(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
		  काष्ठा packet_type *ptype, काष्ठा net_device *orig_dev)
अणु
	skb_orphan(skb);

	अगर (!net_eq(dev_net(dev), &init_net)) अणु
		kमुक्त_skb(skb);
		वापस 0;
	पूर्ण

	अगर ((*skb->data & 0x0F) != 0) अणु
		kमुक्त_skb(skb);	/* Not a KISS data frame */
		वापस 0;
	पूर्ण

	skb_pull(skb, AX25_KISS_HEADER_LEN);	/* Remove the KISS byte */

	वापस ax25_rcv(skb, dev, (ax25_address *)dev->dev_addr, ptype);
पूर्ण
