<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * Copyright (C) Alan Cox GW4PTS (alan@lxorguk.ukuu.org.uk)
 * Copyright (C) Jonathan Naylor G4KLX (g4klx@g4klx.demon.co.uk)
 * Copyright (C) Joerg Reuter DL1BKE (jreuter@yaina.de)
 */
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/socket.h>
#समावेश <linux/in.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/समयr.h>
#समावेश <linux/माला.स>
#समावेश <linux/sockios.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/net.h>
#समावेश <linux/slab.h>
#समावेश <net/ax25.h>
#समावेश <linux/inet.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <net/sock.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>

अटल DEFINE_SPINLOCK(ax25_frag_lock);

ax25_cb *ax25_send_frame(काष्ठा sk_buff *skb, पूर्णांक paclen, ax25_address *src, ax25_address *dest, ax25_digi *digi, काष्ठा net_device *dev)
अणु
	ax25_dev *ax25_dev;
	ax25_cb *ax25;

	/*
	 * Take the शेष packet length क्रम the device अगर zero is
	 * specअगरied.
	 */
	अगर (paclen == 0) अणु
		अगर ((ax25_dev = ax25_dev_ax25dev(dev)) == शून्य)
			वापस शून्य;

		paclen = ax25_dev->values[AX25_VALUES_PACLEN];
	पूर्ण

	/*
	 * Look क्रम an existing connection.
	 */
	अगर ((ax25 = ax25_find_cb(src, dest, digi, dev)) != शून्य) अणु
		ax25_output(ax25, paclen, skb);
		वापस ax25;		/* It alपढ़ोy existed */
	पूर्ण

	अगर ((ax25_dev = ax25_dev_ax25dev(dev)) == शून्य)
		वापस शून्य;

	अगर ((ax25 = ax25_create_cb()) == शून्य)
		वापस शून्य;

	ax25_fillin_cb(ax25, ax25_dev);

	ax25->source_addr = *src;
	ax25->dest_addr   = *dest;

	अगर (digi != शून्य) अणु
		ax25->digipeat = kmemdup(digi, माप(*digi), GFP_ATOMIC);
		अगर (ax25->digipeat == शून्य) अणु
			ax25_cb_put(ax25);
			वापस शून्य;
		पूर्ण
	पूर्ण

	चयन (ax25->ax25_dev->values[AX25_VALUES_PROTOCOL]) अणु
	हाल AX25_PROTO_STD_SIMPLEX:
	हाल AX25_PROTO_STD_DUPLEX:
		ax25_std_establish_data_link(ax25);
		अवरोध;

#अगर_घोषित CONFIG_AX25_DAMA_SLAVE
	हाल AX25_PROTO_DAMA_SLAVE:
		अगर (ax25_dev->dama.slave)
			ax25_ds_establish_data_link(ax25);
		अन्यथा
			ax25_std_establish_data_link(ax25);
		अवरोध;
#पूर्ण_अगर
	पूर्ण

	/*
	 * There is one ref क्रम the state machine; a caller needs
	 * one more to put it back, just like with the existing one.
	 */
	ax25_cb_hold(ax25);

	ax25_cb_add(ax25);

	ax25->state = AX25_STATE_1;

	ax25_start_heartbeat(ax25);

	ax25_output(ax25, paclen, skb);

	वापस ax25;			/* We had to create it */
पूर्ण

EXPORT_SYMBOL(ax25_send_frame);

/*
 *	All outgoing AX.25 I frames pass via this routine. Thereक्रमe this is
 *	where the fragmentation of frames takes place. If fragment is set to
 *	zero then we are not allowed to करो fragmentation, even अगर the frame
 *	is too large.
 */
व्योम ax25_output(ax25_cb *ax25, पूर्णांक paclen, काष्ठा sk_buff *skb)
अणु
	काष्ठा sk_buff *skbn;
	अचिन्हित अक्षर *p;
	पूर्णांक frontlen, len, fragno, ka9qfrag, first = 1;

	अगर (paclen < 16) अणु
		WARN_ON_ONCE(1);
		kमुक्त_skb(skb);
		वापस;
	पूर्ण

	अगर ((skb->len - 1) > paclen) अणु
		अगर (*skb->data == AX25_P_TEXT) अणु
			skb_pull(skb, 1); /* skip PID */
			ka9qfrag = 0;
		पूर्ण अन्यथा अणु
			paclen -= 2;	/* Allow क्रम fragment control info */
			ka9qfrag = 1;
		पूर्ण

		fragno = skb->len / paclen;
		अगर (skb->len % paclen == 0) fragno--;

		frontlen = skb_headroom(skb);	/* Address space + CTRL */

		जबतक (skb->len > 0) अणु
			spin_lock_bh(&ax25_frag_lock);
			अगर ((skbn = alloc_skb(paclen + 2 + frontlen, GFP_ATOMIC)) == शून्य) अणु
				spin_unlock_bh(&ax25_frag_lock);
				prपूर्णांकk(KERN_CRIT "AX.25: ax25_output - out of memory\n");
				वापस;
			पूर्ण

			अगर (skb->sk != शून्य)
				skb_set_owner_w(skbn, skb->sk);

			spin_unlock_bh(&ax25_frag_lock);

			len = (paclen > skb->len) ? skb->len : paclen;

			अगर (ka9qfrag == 1) अणु
				skb_reserve(skbn, frontlen + 2);
				skb_set_network_header(skbn,
						      skb_network_offset(skb));
				skb_copy_from_linear_data(skb, skb_put(skbn, len), len);
				p = skb_push(skbn, 2);

				*p++ = AX25_P_SEGMENT;

				*p = fragno--;
				अगर (first) अणु
					*p |= AX25_SEG_FIRST;
					first = 0;
				पूर्ण
			पूर्ण अन्यथा अणु
				skb_reserve(skbn, frontlen + 1);
				skb_set_network_header(skbn,
						      skb_network_offset(skb));
				skb_copy_from_linear_data(skb, skb_put(skbn, len), len);
				p = skb_push(skbn, 1);
				*p = AX25_P_TEXT;
			पूर्ण

			skb_pull(skb, len);
			skb_queue_tail(&ax25->ग_लिखो_queue, skbn); /* Throw it on the queue */
		पूर्ण

		kमुक्त_skb(skb);
	पूर्ण अन्यथा अणु
		skb_queue_tail(&ax25->ग_लिखो_queue, skb);	  /* Throw it on the queue */
	पूर्ण

	चयन (ax25->ax25_dev->values[AX25_VALUES_PROTOCOL]) अणु
	हाल AX25_PROTO_STD_SIMPLEX:
	हाल AX25_PROTO_STD_DUPLEX:
		ax25_kick(ax25);
		अवरोध;

#अगर_घोषित CONFIG_AX25_DAMA_SLAVE
	/*
	 * A DAMA slave is _required_ to work as normal AX.25L2V2
	 * अगर no DAMA master is available.
	 */
	हाल AX25_PROTO_DAMA_SLAVE:
		अगर (!ax25->ax25_dev->dama.slave) ax25_kick(ax25);
		अवरोध;
#पूर्ण_अगर
	पूर्ण
पूर्ण

/*
 *  This procedure is passed a buffer descriptor क्रम an अगरrame. It builds
 *  the rest of the control part of the frame and then ग_लिखोs it out.
 */
अटल व्योम ax25_send_अगरrame(ax25_cb *ax25, काष्ठा sk_buff *skb, पूर्णांक poll_bit)
अणु
	अचिन्हित अक्षर *frame;

	अगर (skb == शून्य)
		वापस;

	skb_reset_network_header(skb);

	अगर (ax25->modulus == AX25_MODULUS) अणु
		frame = skb_push(skb, 1);

		*frame = AX25_I;
		*frame |= (poll_bit) ? AX25_PF : 0;
		*frame |= (ax25->vr << 5);
		*frame |= (ax25->vs << 1);
	पूर्ण अन्यथा अणु
		frame = skb_push(skb, 2);

		frame[0] = AX25_I;
		frame[0] |= (ax25->vs << 1);
		frame[1] = (poll_bit) ? AX25_EPF : 0;
		frame[1] |= (ax25->vr << 1);
	पूर्ण

	ax25_start_idleसमयr(ax25);

	ax25_transmit_buffer(ax25, skb, AX25_COMMAND);
पूर्ण

व्योम ax25_kick(ax25_cb *ax25)
अणु
	काष्ठा sk_buff *skb, *skbn;
	पूर्णांक last = 1;
	अचिन्हित लघु start, end, next;

	अगर (ax25->state != AX25_STATE_3 && ax25->state != AX25_STATE_4)
		वापस;

	अगर (ax25->condition & AX25_COND_PEER_RX_BUSY)
		वापस;

	अगर (skb_peek(&ax25->ग_लिखो_queue) == शून्य)
		वापस;

	start = (skb_peek(&ax25->ack_queue) == शून्य) ? ax25->va : ax25->vs;
	end   = (ax25->va + ax25->winकरोw) % ax25->modulus;

	अगर (start == end)
		वापस;

	/*
	 * Transmit data until either we're out of data to send or
	 * the winकरोw is full. Send a poll on the final I frame अगर
	 * the winकरोw is filled.
	 */

	/*
	 * Dequeue the frame and copy it.
	 * Check क्रम race with ax25_clear_queues().
	 */
	skb  = skb_dequeue(&ax25->ग_लिखो_queue);
	अगर (!skb)
		वापस;

	ax25->vs = start;

	करो अणु
		अगर ((skbn = skb_clone(skb, GFP_ATOMIC)) == शून्य) अणु
			skb_queue_head(&ax25->ग_लिखो_queue, skb);
			अवरोध;
		पूर्ण

		अगर (skb->sk != शून्य)
			skb_set_owner_w(skbn, skb->sk);

		next = (ax25->vs + 1) % ax25->modulus;
		last = (next == end);

		/*
		 * Transmit the frame copy.
		 * bke 960114: करो not set the Poll bit on the last frame
		 * in DAMA mode.
		 */
		चयन (ax25->ax25_dev->values[AX25_VALUES_PROTOCOL]) अणु
		हाल AX25_PROTO_STD_SIMPLEX:
		हाल AX25_PROTO_STD_DUPLEX:
			ax25_send_अगरrame(ax25, skbn, (last) ? AX25_POLLON : AX25_POLLOFF);
			अवरोध;

#अगर_घोषित CONFIG_AX25_DAMA_SLAVE
		हाल AX25_PROTO_DAMA_SLAVE:
			ax25_send_अगरrame(ax25, skbn, AX25_POLLOFF);
			अवरोध;
#पूर्ण_अगर
		पूर्ण

		ax25->vs = next;

		/*
		 * Requeue the original data frame.
		 */
		skb_queue_tail(&ax25->ack_queue, skb);

	पूर्ण जबतक (!last && (skb = skb_dequeue(&ax25->ग_लिखो_queue)) != शून्य);

	ax25->condition &= ~AX25_COND_ACK_PENDING;

	अगर (!ax25_t1समयr_running(ax25)) अणु
		ax25_stop_t3समयr(ax25);
		ax25_calculate_t1(ax25);
		ax25_start_t1समयr(ax25);
	पूर्ण
पूर्ण

व्योम ax25_transmit_buffer(ax25_cb *ax25, काष्ठा sk_buff *skb, पूर्णांक type)
अणु
	काष्ठा sk_buff *skbn;
	अचिन्हित अक्षर *ptr;
	पूर्णांक headroom;

	अगर (ax25->ax25_dev == शून्य) अणु
		ax25_disconnect(ax25, ENETUNREACH);
		वापस;
	पूर्ण

	headroom = ax25_addr_size(ax25->digipeat);

	अगर (skb_headroom(skb) < headroom) अणु
		अगर ((skbn = skb_पुनः_स्मृति_headroom(skb, headroom)) == शून्य) अणु
			prपूर्णांकk(KERN_CRIT "AX.25: ax25_transmit_buffer - out of memory\n");
			kमुक्त_skb(skb);
			वापस;
		पूर्ण

		अगर (skb->sk != शून्य)
			skb_set_owner_w(skbn, skb->sk);

		consume_skb(skb);
		skb = skbn;
	पूर्ण

	ptr = skb_push(skb, headroom);

	ax25_addr_build(ptr, &ax25->source_addr, &ax25->dest_addr, ax25->digipeat, type, ax25->modulus);

	ax25_queue_xmit(skb, ax25->ax25_dev->dev);
पूर्ण

/*
 *	A small shim to dev_queue_xmit to add the KISS control byte, and करो
 *	any packet क्रमwarding in operation.
 */
व्योम ax25_queue_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	अचिन्हित अक्षर *ptr;

	skb->protocol = ax25_type_trans(skb, ax25_fwd_dev(dev));

	ptr  = skb_push(skb, 1);
	*ptr = 0x00;			/* KISS */

	dev_queue_xmit(skb);
पूर्ण

पूर्णांक ax25_check_अगरrames_acked(ax25_cb *ax25, अचिन्हित लघु nr)
अणु
	अगर (ax25->vs == nr) अणु
		ax25_frames_acked(ax25, nr);
		ax25_calculate_rtt(ax25);
		ax25_stop_t1समयr(ax25);
		ax25_start_t3समयr(ax25);
		वापस 1;
	पूर्ण अन्यथा अणु
		अगर (ax25->va != nr) अणु
			ax25_frames_acked(ax25, nr);
			ax25_calculate_t1(ax25);
			ax25_start_t1समयr(ax25);
			वापस 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
