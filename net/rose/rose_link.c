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
#समावेश <linux/jअगरfies.h>
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
#समावेश <linux/fcntl.h>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <net/rose.h>

अटल व्योम rose_fसमयr_expiry(काष्ठा समयr_list *);
अटल व्योम rose_t0समयr_expiry(काष्ठा समयr_list *);

अटल व्योम rose_transmit_restart_confirmation(काष्ठा rose_neigh *neigh);
अटल व्योम rose_transmit_restart_request(काष्ठा rose_neigh *neigh);

व्योम rose_start_fसमयr(काष्ठा rose_neigh *neigh)
अणु
	del_समयr(&neigh->fसमयr);

	neigh->fसमयr.function = rose_fसमयr_expiry;
	neigh->fसमयr.expires  =
		jअगरfies + msecs_to_jअगरfies(sysctl_rose_link_fail_समयout);

	add_समयr(&neigh->fसमयr);
पूर्ण

अटल व्योम rose_start_t0समयr(काष्ठा rose_neigh *neigh)
अणु
	del_समयr(&neigh->t0समयr);

	neigh->t0समयr.function = rose_t0समयr_expiry;
	neigh->t0समयr.expires  =
		jअगरfies + msecs_to_jअगरfies(sysctl_rose_restart_request_समयout);

	add_समयr(&neigh->t0समयr);
पूर्ण

व्योम rose_stop_fसमयr(काष्ठा rose_neigh *neigh)
अणु
	del_समयr(&neigh->fसमयr);
पूर्ण

व्योम rose_stop_t0समयr(काष्ठा rose_neigh *neigh)
अणु
	del_समयr(&neigh->t0समयr);
पूर्ण

पूर्णांक rose_fसमयr_running(काष्ठा rose_neigh *neigh)
अणु
	वापस समयr_pending(&neigh->fसमयr);
पूर्ण

अटल पूर्णांक rose_t0समयr_running(काष्ठा rose_neigh *neigh)
अणु
	वापस समयr_pending(&neigh->t0समयr);
पूर्ण

अटल व्योम rose_fसमयr_expiry(काष्ठा समयr_list *t)
अणु
पूर्ण

अटल व्योम rose_t0समयr_expiry(काष्ठा समयr_list *t)
अणु
	काष्ठा rose_neigh *neigh = from_समयr(neigh, t, t0समयr);

	rose_transmit_restart_request(neigh);

	neigh->dce_mode = 0;

	rose_start_t0समयr(neigh);
पूर्ण

/*
 *	Interface to ax25_send_frame. Changes my level 2 callsign depending
 *	on whether we have a global ROSE callsign or use the शेष port
 *	callsign.
 */
अटल पूर्णांक rose_send_frame(काष्ठा sk_buff *skb, काष्ठा rose_neigh *neigh)
अणु
	ax25_address *rose_call;
	ax25_cb *ax25s;

	अगर (ax25cmp(&rose_callsign, &null_ax25_address) == 0)
		rose_call = (ax25_address *)neigh->dev->dev_addr;
	अन्यथा
		rose_call = &rose_callsign;

	ax25s = neigh->ax25;
	neigh->ax25 = ax25_send_frame(skb, 260, rose_call, &neigh->callsign, neigh->digipeat, neigh->dev);
	अगर (ax25s)
		ax25_cb_put(ax25s);

	वापस neigh->ax25 != शून्य;
पूर्ण

/*
 *	Interface to ax25_link_up. Changes my level 2 callsign depending
 *	on whether we have a global ROSE callsign or use the शेष port
 *	callsign.
 */
अटल पूर्णांक rose_link_up(काष्ठा rose_neigh *neigh)
अणु
	ax25_address *rose_call;
	ax25_cb *ax25s;

	अगर (ax25cmp(&rose_callsign, &null_ax25_address) == 0)
		rose_call = (ax25_address *)neigh->dev->dev_addr;
	अन्यथा
		rose_call = &rose_callsign;

	ax25s = neigh->ax25;
	neigh->ax25 = ax25_find_cb(rose_call, &neigh->callsign, neigh->digipeat, neigh->dev);
	अगर (ax25s)
		ax25_cb_put(ax25s);

	वापस neigh->ax25 != शून्य;
पूर्ण

/*
 *	This handles all restart and diagnostic frames.
 */
व्योम rose_link_rx_restart(काष्ठा sk_buff *skb, काष्ठा rose_neigh *neigh, अचिन्हित लघु frametype)
अणु
	काष्ठा sk_buff *skbn;

	चयन (frametype) अणु
	हाल ROSE_RESTART_REQUEST:
		rose_stop_t0समयr(neigh);
		neigh->restarted = 1;
		neigh->dce_mode  = (skb->data[3] == ROSE_DTE_ORIGINATED);
		rose_transmit_restart_confirmation(neigh);
		अवरोध;

	हाल ROSE_RESTART_CONFIRMATION:
		rose_stop_t0समयr(neigh);
		neigh->restarted = 1;
		अवरोध;

	हाल ROSE_DIAGNOSTIC:
		pr_warn("ROSE: received diagnostic #%d - %3ph\n", skb->data[3],
			skb->data + 4);
		अवरोध;

	शेष:
		prपूर्णांकk(KERN_WARNING "ROSE: received unknown %02X with LCI 000\n", frametype);
		अवरोध;
	पूर्ण

	अगर (neigh->restarted) अणु
		जबतक ((skbn = skb_dequeue(&neigh->queue)) != शून्य)
			अगर (!rose_send_frame(skbn, neigh))
				kमुक्त_skb(skbn);
	पूर्ण
पूर्ण

/*
 *	This routine is called when a Restart Request is needed
 */
अटल व्योम rose_transmit_restart_request(काष्ठा rose_neigh *neigh)
अणु
	काष्ठा sk_buff *skb;
	अचिन्हित अक्षर *dptr;
	पूर्णांक len;

	len = AX25_BPQ_HEADER_LEN + AX25_MAX_HEADER_LEN + ROSE_MIN_LEN + 3;

	अगर ((skb = alloc_skb(len, GFP_ATOMIC)) == शून्य)
		वापस;

	skb_reserve(skb, AX25_BPQ_HEADER_LEN + AX25_MAX_HEADER_LEN);

	dptr = skb_put(skb, ROSE_MIN_LEN + 3);

	*dptr++ = AX25_P_ROSE;
	*dptr++ = ROSE_GFI;
	*dptr++ = 0x00;
	*dptr++ = ROSE_RESTART_REQUEST;
	*dptr++ = ROSE_DTE_ORIGINATED;
	*dptr++ = 0;

	अगर (!rose_send_frame(skb, neigh))
		kमुक्त_skb(skb);
पूर्ण

/*
 * This routine is called when a Restart Confirmation is needed
 */
अटल व्योम rose_transmit_restart_confirmation(काष्ठा rose_neigh *neigh)
अणु
	काष्ठा sk_buff *skb;
	अचिन्हित अक्षर *dptr;
	पूर्णांक len;

	len = AX25_BPQ_HEADER_LEN + AX25_MAX_HEADER_LEN + ROSE_MIN_LEN + 1;

	अगर ((skb = alloc_skb(len, GFP_ATOMIC)) == शून्य)
		वापस;

	skb_reserve(skb, AX25_BPQ_HEADER_LEN + AX25_MAX_HEADER_LEN);

	dptr = skb_put(skb, ROSE_MIN_LEN + 1);

	*dptr++ = AX25_P_ROSE;
	*dptr++ = ROSE_GFI;
	*dptr++ = 0x00;
	*dptr++ = ROSE_RESTART_CONFIRMATION;

	अगर (!rose_send_frame(skb, neigh))
		kमुक्त_skb(skb);
पूर्ण

/*
 * This routine is called when a Clear Request is needed outside of the context
 * of a connected socket.
 */
व्योम rose_transmit_clear_request(काष्ठा rose_neigh *neigh, अचिन्हित पूर्णांक lci, अचिन्हित अक्षर cause, अचिन्हित अक्षर diagnostic)
अणु
	काष्ठा sk_buff *skb;
	अचिन्हित अक्षर *dptr;
	पूर्णांक len;

	len = AX25_BPQ_HEADER_LEN + AX25_MAX_HEADER_LEN + ROSE_MIN_LEN + 3;

	अगर ((skb = alloc_skb(len, GFP_ATOMIC)) == शून्य)
		वापस;

	skb_reserve(skb, AX25_BPQ_HEADER_LEN + AX25_MAX_HEADER_LEN);

	dptr = skb_put(skb, ROSE_MIN_LEN + 3);

	*dptr++ = AX25_P_ROSE;
	*dptr++ = ((lci >> 8) & 0x0F) | ROSE_GFI;
	*dptr++ = ((lci >> 0) & 0xFF);
	*dptr++ = ROSE_CLEAR_REQUEST;
	*dptr++ = cause;
	*dptr++ = diagnostic;

	अगर (!rose_send_frame(skb, neigh))
		kमुक्त_skb(skb);
पूर्ण

व्योम rose_transmit_link(काष्ठा sk_buff *skb, काष्ठा rose_neigh *neigh)
अणु
	अचिन्हित अक्षर *dptr;

	अगर (neigh->loopback) अणु
		rose_loopback_queue(skb, neigh);
		वापस;
	पूर्ण

	अगर (!rose_link_up(neigh))
		neigh->restarted = 0;

	dptr = skb_push(skb, 1);
	*dptr++ = AX25_P_ROSE;

	अगर (neigh->restarted) अणु
		अगर (!rose_send_frame(skb, neigh))
			kमुक्त_skb(skb);
	पूर्ण अन्यथा अणु
		skb_queue_tail(&neigh->queue, skb);

		अगर (!rose_t0समयr_running(neigh)) अणु
			rose_transmit_restart_request(neigh);
			neigh->dce_mode = 0;
			rose_start_t0समयr(neigh);
		पूर्ण
	पूर्ण
पूर्ण
