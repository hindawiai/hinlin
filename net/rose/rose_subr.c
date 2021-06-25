<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * Copyright (C) Jonathan Naylor G4KLX (g4klx@g4klx.demon.co.uk)
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
#समावेश <linux/fcntl.h>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <net/rose.h>

अटल पूर्णांक rose_create_facilities(अचिन्हित अक्षर *buffer, काष्ठा rose_sock *rose);

/*
 *	This routine purges all of the queues of frames.
 */
व्योम rose_clear_queues(काष्ठा sock *sk)
अणु
	skb_queue_purge(&sk->sk_ग_लिखो_queue);
	skb_queue_purge(&rose_sk(sk)->ack_queue);
पूर्ण

/*
 * This routine purges the input queue of those frames that have been
 * acknowledged. This replaces the boxes labelled "V(a) <- N(r)" on the
 * SDL diagram.
 */
व्योम rose_frames_acked(काष्ठा sock *sk, अचिन्हित लघु nr)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा rose_sock *rose = rose_sk(sk);

	/*
	 * Remove all the ack-ed frames from the ack queue.
	 */
	अगर (rose->va != nr) अणु
		जबतक (skb_peek(&rose->ack_queue) != शून्य && rose->va != nr) अणु
			skb = skb_dequeue(&rose->ack_queue);
			kमुक्त_skb(skb);
			rose->va = (rose->va + 1) % ROSE_MODULUS;
		पूर्ण
	पूर्ण
पूर्ण

व्योम rose_requeue_frames(काष्ठा sock *sk)
अणु
	काष्ठा sk_buff *skb, *skb_prev = शून्य;

	/*
	 * Requeue all the un-ack-ed frames on the output queue to be picked
	 * up by rose_kick. This arrangement handles the possibility of an
	 * empty output queue.
	 */
	जबतक ((skb = skb_dequeue(&rose_sk(sk)->ack_queue)) != शून्य) अणु
		अगर (skb_prev == शून्य)
			skb_queue_head(&sk->sk_ग_लिखो_queue, skb);
		अन्यथा
			skb_append(skb_prev, skb, &sk->sk_ग_लिखो_queue);
		skb_prev = skb;
	पूर्ण
पूर्ण

/*
 *	Validate that the value of nr is between va and vs. Return true or
 *	false क्रम testing.
 */
पूर्णांक rose_validate_nr(काष्ठा sock *sk, अचिन्हित लघु nr)
अणु
	काष्ठा rose_sock *rose = rose_sk(sk);
	अचिन्हित लघु vc = rose->va;

	जबतक (vc != rose->vs) अणु
		अगर (nr == vc) वापस 1;
		vc = (vc + 1) % ROSE_MODULUS;
	पूर्ण

	वापस nr == rose->vs;
पूर्ण

/*
 *  This routine is called when the packet layer पूर्णांकernally generates a
 *  control frame.
 */
व्योम rose_ग_लिखो_पूर्णांकernal(काष्ठा sock *sk, पूर्णांक frametype)
अणु
	काष्ठा rose_sock *rose = rose_sk(sk);
	काष्ठा sk_buff *skb;
	अचिन्हित अक्षर  *dptr;
	अचिन्हित अक्षर  lci1, lci2;
	पूर्णांक maxfaclen = 0;
	पूर्णांक len, faclen;
	पूर्णांक reserve;

	reserve = AX25_BPQ_HEADER_LEN + AX25_MAX_HEADER_LEN + 1;
	len = ROSE_MIN_LEN;

	चयन (frametype) अणु
	हाल ROSE_CALL_REQUEST:
		len   += 1 + ROSE_ADDR_LEN + ROSE_ADDR_LEN;
		maxfaclen = 256;
		अवरोध;
	हाल ROSE_CALL_ACCEPTED:
	हाल ROSE_CLEAR_REQUEST:
	हाल ROSE_RESET_REQUEST:
		len   += 2;
		अवरोध;
	पूर्ण

	skb = alloc_skb(reserve + len + maxfaclen, GFP_ATOMIC);
	अगर (!skb)
		वापस;

	/*
	 *	Space क्रम AX.25 header and PID.
	 */
	skb_reserve(skb, reserve);

	dptr = skb_put(skb, len);

	lci1 = (rose->lci >> 8) & 0x0F;
	lci2 = (rose->lci >> 0) & 0xFF;

	चयन (frametype) अणु
	हाल ROSE_CALL_REQUEST:
		*dptr++ = ROSE_GFI | lci1;
		*dptr++ = lci2;
		*dptr++ = frametype;
		*dptr++ = ROSE_CALL_REQ_ADDR_LEN_VAL;
		स_नकल(dptr, &rose->dest_addr,  ROSE_ADDR_LEN);
		dptr   += ROSE_ADDR_LEN;
		स_नकल(dptr, &rose->source_addr, ROSE_ADDR_LEN);
		dptr   += ROSE_ADDR_LEN;
		faclen = rose_create_facilities(dptr, rose);
		skb_put(skb, faclen);
		dptr   += faclen;
		अवरोध;

	हाल ROSE_CALL_ACCEPTED:
		*dptr++ = ROSE_GFI | lci1;
		*dptr++ = lci2;
		*dptr++ = frametype;
		*dptr++ = 0x00;		/* Address length */
		*dptr++ = 0;		/* Facilities length */
		अवरोध;

	हाल ROSE_CLEAR_REQUEST:
		*dptr++ = ROSE_GFI | lci1;
		*dptr++ = lci2;
		*dptr++ = frametype;
		*dptr++ = rose->cause;
		*dptr++ = rose->diagnostic;
		अवरोध;

	हाल ROSE_RESET_REQUEST:
		*dptr++ = ROSE_GFI | lci1;
		*dptr++ = lci2;
		*dptr++ = frametype;
		*dptr++ = ROSE_DTE_ORIGINATED;
		*dptr++ = 0;
		अवरोध;

	हाल ROSE_RR:
	हाल ROSE_RNR:
		*dptr++ = ROSE_GFI | lci1;
		*dptr++ = lci2;
		*dptr   = frametype;
		*dptr++ |= (rose->vr << 5) & 0xE0;
		अवरोध;

	हाल ROSE_CLEAR_CONFIRMATION:
	हाल ROSE_RESET_CONFIRMATION:
		*dptr++ = ROSE_GFI | lci1;
		*dptr++ = lci2;
		*dptr++  = frametype;
		अवरोध;

	शेष:
		prपूर्णांकk(KERN_ERR "ROSE: rose_write_internal - invalid frametype %02X\n", frametype);
		kमुक्त_skb(skb);
		वापस;
	पूर्ण

	rose_transmit_link(skb, rose->neighbour);
पूर्ण

पूर्णांक rose_decode(काष्ठा sk_buff *skb, पूर्णांक *ns, पूर्णांक *nr, पूर्णांक *q, पूर्णांक *d, पूर्णांक *m)
अणु
	अचिन्हित अक्षर *frame;

	frame = skb->data;

	*ns = *nr = *q = *d = *m = 0;

	चयन (frame[2]) अणु
	हाल ROSE_CALL_REQUEST:
	हाल ROSE_CALL_ACCEPTED:
	हाल ROSE_CLEAR_REQUEST:
	हाल ROSE_CLEAR_CONFIRMATION:
	हाल ROSE_RESET_REQUEST:
	हाल ROSE_RESET_CONFIRMATION:
		वापस frame[2];
	शेष:
		अवरोध;
	पूर्ण

	अगर ((frame[2] & 0x1F) == ROSE_RR  ||
	    (frame[2] & 0x1F) == ROSE_RNR) अणु
		*nr = (frame[2] >> 5) & 0x07;
		वापस frame[2] & 0x1F;
	पूर्ण

	अगर ((frame[2] & 0x01) == ROSE_DATA) अणु
		*q  = (frame[0] & ROSE_Q_BIT) == ROSE_Q_BIT;
		*d  = (frame[0] & ROSE_D_BIT) == ROSE_D_BIT;
		*m  = (frame[2] & ROSE_M_BIT) == ROSE_M_BIT;
		*nr = (frame[2] >> 5) & 0x07;
		*ns = (frame[2] >> 1) & 0x07;
		वापस ROSE_DATA;
	पूर्ण

	वापस ROSE_ILLEGAL;
पूर्ण

अटल पूर्णांक rose_parse_national(अचिन्हित अक्षर *p, काष्ठा rose_facilities_काष्ठा *facilities, पूर्णांक len)
अणु
	अचिन्हित अक्षर *pt;
	अचिन्हित अक्षर l, lg, n = 0;
	पूर्णांक fac_national_digis_received = 0;

	करो अणु
		चयन (*p & 0xC0) अणु
		हाल 0x00:
			अगर (len < 2)
				वापस -1;
			p   += 2;
			n   += 2;
			len -= 2;
			अवरोध;

		हाल 0x40:
			अगर (len < 3)
				वापस -1;
			अगर (*p == FAC_NATIONAL_RAND)
				facilities->अक्रम = ((p[1] << 8) & 0xFF00) + ((p[2] << 0) & 0x00FF);
			p   += 3;
			n   += 3;
			len -= 3;
			अवरोध;

		हाल 0x80:
			अगर (len < 4)
				वापस -1;
			p   += 4;
			n   += 4;
			len -= 4;
			अवरोध;

		हाल 0xC0:
			अगर (len < 2)
				वापस -1;
			l = p[1];
			अगर (len < 2 + l)
				वापस -1;
			अगर (*p == FAC_NATIONAL_DEST_DIGI) अणु
				अगर (!fac_national_digis_received) अणु
					अगर (l < AX25_ADDR_LEN)
						वापस -1;
					स_नकल(&facilities->source_digis[0], p + 2, AX25_ADDR_LEN);
					facilities->source_ndigis = 1;
				पूर्ण
			पूर्ण
			अन्यथा अगर (*p == FAC_NATIONAL_SRC_DIGI) अणु
				अगर (!fac_national_digis_received) अणु
					अगर (l < AX25_ADDR_LEN)
						वापस -1;
					स_नकल(&facilities->dest_digis[0], p + 2, AX25_ADDR_LEN);
					facilities->dest_ndigis = 1;
				पूर्ण
			पूर्ण
			अन्यथा अगर (*p == FAC_NATIONAL_FAIL_CALL) अणु
				अगर (l < AX25_ADDR_LEN)
					वापस -1;
				स_नकल(&facilities->fail_call, p + 2, AX25_ADDR_LEN);
			पूर्ण
			अन्यथा अगर (*p == FAC_NATIONAL_FAIL_ADD) अणु
				अगर (l < 1 + ROSE_ADDR_LEN)
					वापस -1;
				स_नकल(&facilities->fail_addr, p + 3, ROSE_ADDR_LEN);
			पूर्ण
			अन्यथा अगर (*p == FAC_NATIONAL_DIGIS) अणु
				अगर (l % AX25_ADDR_LEN)
					वापस -1;
				fac_national_digis_received = 1;
				facilities->source_ndigis = 0;
				facilities->dest_ndigis   = 0;
				क्रम (pt = p + 2, lg = 0 ; lg < l ; pt += AX25_ADDR_LEN, lg += AX25_ADDR_LEN) अणु
					अगर (pt[6] & AX25_HBIT) अणु
						अगर (facilities->dest_ndigis >= ROSE_MAX_DIGIS)
							वापस -1;
						स_नकल(&facilities->dest_digis[facilities->dest_ndigis++], pt, AX25_ADDR_LEN);
					पूर्ण अन्यथा अणु
						अगर (facilities->source_ndigis >= ROSE_MAX_DIGIS)
							वापस -1;
						स_नकल(&facilities->source_digis[facilities->source_ndigis++], pt, AX25_ADDR_LEN);
					पूर्ण
				पूर्ण
			पूर्ण
			p   += l + 2;
			n   += l + 2;
			len -= l + 2;
			अवरोध;
		पूर्ण
	पूर्ण जबतक (*p != 0x00 && len > 0);

	वापस n;
पूर्ण

अटल पूर्णांक rose_parse_ccitt(अचिन्हित अक्षर *p, काष्ठा rose_facilities_काष्ठा *facilities, पूर्णांक len)
अणु
	अचिन्हित अक्षर l, n = 0;
	अक्षर callsign[11];

	करो अणु
		चयन (*p & 0xC0) अणु
		हाल 0x00:
			अगर (len < 2)
				वापस -1;
			p   += 2;
			n   += 2;
			len -= 2;
			अवरोध;

		हाल 0x40:
			अगर (len < 3)
				वापस -1;
			p   += 3;
			n   += 3;
			len -= 3;
			अवरोध;

		हाल 0x80:
			अगर (len < 4)
				वापस -1;
			p   += 4;
			n   += 4;
			len -= 4;
			अवरोध;

		हाल 0xC0:
			अगर (len < 2)
				वापस -1;
			l = p[1];

			/* Prevent overflows*/
			अगर (l < 10 || l > 20)
				वापस -1;

			अगर (*p == FAC_CCITT_DEST_NSAP) अणु
				स_नकल(&facilities->source_addr, p + 7, ROSE_ADDR_LEN);
				स_नकल(callsign, p + 12,   l - 10);
				callsign[l - 10] = '\0';
				asc2ax(&facilities->source_call, callsign);
			पूर्ण
			अगर (*p == FAC_CCITT_SRC_NSAP) अणु
				स_नकल(&facilities->dest_addr, p + 7, ROSE_ADDR_LEN);
				स_नकल(callsign, p + 12, l - 10);
				callsign[l - 10] = '\0';
				asc2ax(&facilities->dest_call, callsign);
			पूर्ण
			p   += l + 2;
			n   += l + 2;
			len -= l + 2;
			अवरोध;
		पूर्ण
	पूर्ण जबतक (*p != 0x00 && len > 0);

	वापस n;
पूर्ण

पूर्णांक rose_parse_facilities(अचिन्हित अक्षर *p, अचिन्हित packet_len,
	काष्ठा rose_facilities_काष्ठा *facilities)
अणु
	पूर्णांक facilities_len, len;

	facilities_len = *p++;

	अगर (facilities_len == 0 || (अचिन्हित पूर्णांक)facilities_len > packet_len)
		वापस 0;

	जबतक (facilities_len >= 3 && *p == 0x00) अणु
		facilities_len--;
		p++;

		चयन (*p) अणु
		हाल FAC_NATIONAL:		/* National */
			len = rose_parse_national(p + 1, facilities, facilities_len - 1);
			अवरोध;

		हाल FAC_CCITT:		/* CCITT */
			len = rose_parse_ccitt(p + 1, facilities, facilities_len - 1);
			अवरोध;

		शेष:
			prपूर्णांकk(KERN_DEBUG "ROSE: rose_parse_facilities - unknown facilities family %02X\n", *p);
			len = 1;
			अवरोध;
		पूर्ण

		अगर (len < 0)
			वापस 0;
		अगर (WARN_ON(len >= facilities_len))
			वापस 0;
		facilities_len -= len + 1;
		p += len + 1;
	पूर्ण

	वापस facilities_len == 0;
पूर्ण

अटल पूर्णांक rose_create_facilities(अचिन्हित अक्षर *buffer, काष्ठा rose_sock *rose)
अणु
	अचिन्हित अक्षर *p = buffer + 1;
	अक्षर *callsign;
	अक्षर buf[11];
	पूर्णांक len, nb;

	/* National Facilities */
	अगर (rose->अक्रम != 0 || rose->source_ndigis == 1 || rose->dest_ndigis == 1) अणु
		*p++ = 0x00;
		*p++ = FAC_NATIONAL;

		अगर (rose->अक्रम != 0) अणु
			*p++ = FAC_NATIONAL_RAND;
			*p++ = (rose->अक्रम >> 8) & 0xFF;
			*p++ = (rose->अक्रम >> 0) & 0xFF;
		पूर्ण

		/* Sent beक्रमe older facilities */
		अगर ((rose->source_ndigis > 0) || (rose->dest_ndigis > 0)) अणु
			पूर्णांक maxdigi = 0;
			*p++ = FAC_NATIONAL_DIGIS;
			*p++ = AX25_ADDR_LEN * (rose->source_ndigis + rose->dest_ndigis);
			क्रम (nb = 0 ; nb < rose->source_ndigis ; nb++) अणु
				अगर (++maxdigi >= ROSE_MAX_DIGIS)
					अवरोध;
				स_नकल(p, &rose->source_digis[nb], AX25_ADDR_LEN);
				p[6] |= AX25_HBIT;
				p += AX25_ADDR_LEN;
			पूर्ण
			क्रम (nb = 0 ; nb < rose->dest_ndigis ; nb++) अणु
				अगर (++maxdigi >= ROSE_MAX_DIGIS)
					अवरोध;
				स_नकल(p, &rose->dest_digis[nb], AX25_ADDR_LEN);
				p[6] &= ~AX25_HBIT;
				p += AX25_ADDR_LEN;
			पूर्ण
		पूर्ण

		/* For compatibility */
		अगर (rose->source_ndigis > 0) अणु
			*p++ = FAC_NATIONAL_SRC_DIGI;
			*p++ = AX25_ADDR_LEN;
			स_नकल(p, &rose->source_digis[0], AX25_ADDR_LEN);
			p   += AX25_ADDR_LEN;
		पूर्ण

		/* For compatibility */
		अगर (rose->dest_ndigis > 0) अणु
			*p++ = FAC_NATIONAL_DEST_DIGI;
			*p++ = AX25_ADDR_LEN;
			स_नकल(p, &rose->dest_digis[0], AX25_ADDR_LEN);
			p   += AX25_ADDR_LEN;
		पूर्ण
	पूर्ण

	*p++ = 0x00;
	*p++ = FAC_CCITT;

	*p++ = FAC_CCITT_DEST_NSAP;

	callsign = ax2asc(buf, &rose->dest_call);

	*p++ = म_माप(callsign) + 10;
	*p++ = (म_माप(callsign) + 9) * 2;		/* ??? */

	*p++ = 0x47; *p++ = 0x00; *p++ = 0x11;
	*p++ = ROSE_ADDR_LEN * 2;
	स_नकल(p, &rose->dest_addr, ROSE_ADDR_LEN);
	p   += ROSE_ADDR_LEN;

	स_नकल(p, callsign, म_माप(callsign));
	p   += म_माप(callsign);

	*p++ = FAC_CCITT_SRC_NSAP;

	callsign = ax2asc(buf, &rose->source_call);

	*p++ = म_माप(callsign) + 10;
	*p++ = (म_माप(callsign) + 9) * 2;		/* ??? */

	*p++ = 0x47; *p++ = 0x00; *p++ = 0x11;
	*p++ = ROSE_ADDR_LEN * 2;
	स_नकल(p, &rose->source_addr, ROSE_ADDR_LEN);
	p   += ROSE_ADDR_LEN;

	स_नकल(p, callsign, म_माप(callsign));
	p   += म_माप(callsign);

	len       = p - buffer;
	buffer[0] = len - 1;

	वापस len;
पूर्ण

व्योम rose_disconnect(काष्ठा sock *sk, पूर्णांक reason, पूर्णांक cause, पूर्णांक diagnostic)
अणु
	काष्ठा rose_sock *rose = rose_sk(sk);

	rose_stop_समयr(sk);
	rose_stop_idleसमयr(sk);

	rose_clear_queues(sk);

	rose->lci   = 0;
	rose->state = ROSE_STATE_0;

	अगर (cause != -1)
		rose->cause = cause;

	अगर (diagnostic != -1)
		rose->diagnostic = diagnostic;

	sk->sk_state     = TCP_CLOSE;
	sk->sk_err       = reason;
	sk->sk_shutकरोwn |= SEND_SHUTDOWN;

	अगर (!sock_flag(sk, SOCK_DEAD)) अणु
		sk->sk_state_change(sk);
		sock_set_flag(sk, SOCK_DEAD);
	पूर्ण
पूर्ण
