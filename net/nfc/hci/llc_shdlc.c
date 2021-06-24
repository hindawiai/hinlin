<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * shdlc Link Layer Control
 *
 * Copyright (C) 2012  Intel Corporation. All rights reserved.
 */

#घोषणा pr_fmt(fmt) "shdlc: %s: " fmt, __func__

#समावेश <linux/types.h>
#समावेश <linux/sched.h>
#समावेश <linux/रुको.h>
#समावेश <linux/slab.h>
#समावेश <linux/skbuff.h>

#समावेश "llc.h"

क्रमागत shdlc_state अणु
	SHDLC_DISCONNECTED = 0,
	SHDLC_CONNECTING = 1,
	SHDLC_NEGOTIATING = 2,
	SHDLC_HALF_CONNECTED = 3,
	SHDLC_CONNECTED = 4
पूर्ण;

काष्ठा llc_shdlc अणु
	काष्ठा nfc_hci_dev *hdev;
	xmit_to_drv_t xmit_to_drv;
	rcv_to_hci_t rcv_to_hci;

	काष्ठा mutex state_mutex;
	क्रमागत shdlc_state state;
	पूर्णांक hard_fault;

	रुको_queue_head_t *connect_wq;
	पूर्णांक connect_tries;
	पूर्णांक connect_result;
	काष्ठा समयr_list connect_समयr;/* aka T3 in spec 10.6.1 */

	u8 w;				/* winकरोw size */
	bool srej_support;

	काष्ठा समयr_list t1_समयr;	/* send ack समयout */
	bool t1_active;

	काष्ठा समयr_list t2_समयr;	/* guard/retransmit समयout */
	bool t2_active;

	पूर्णांक ns;				/* next seq num क्रम send */
	पूर्णांक nr;				/* next expected seq num क्रम receive */
	पूर्णांक dnr;			/* oldest sent unacked seq num */

	काष्ठा sk_buff_head rcv_q;

	काष्ठा sk_buff_head send_q;
	bool rnr;			/* other side is not पढ़ोy to receive */

	काष्ठा sk_buff_head ack_pending_q;

	काष्ठा work_काष्ठा sm_work;

	पूर्णांक tx_headroom;
	पूर्णांक tx_tailroom;

	llc_failure_t llc_failure;
पूर्ण;

#घोषणा SHDLC_LLC_HEAD_ROOM	2

#घोषणा SHDLC_MAX_WINDOW	4
#घोषणा SHDLC_SREJ_SUPPORT	false

#घोषणा SHDLC_CONTROL_HEAD_MASK	0xe0
#घोषणा SHDLC_CONTROL_HEAD_I	0x80
#घोषणा SHDLC_CONTROL_HEAD_I2	0xa0
#घोषणा SHDLC_CONTROL_HEAD_S	0xc0
#घोषणा SHDLC_CONTROL_HEAD_U	0xe0

#घोषणा SHDLC_CONTROL_NS_MASK	0x38
#घोषणा SHDLC_CONTROL_NR_MASK	0x07
#घोषणा SHDLC_CONTROL_TYPE_MASK	0x18

#घोषणा SHDLC_CONTROL_M_MASK	0x1f

क्रमागत sframe_type अणु
	S_FRAME_RR = 0x00,
	S_FRAME_REJ = 0x01,
	S_FRAME_RNR = 0x02,
	S_FRAME_SREJ = 0x03
पूर्ण;

क्रमागत uframe_modअगरier अणु
	U_FRAME_UA = 0x06,
	U_FRAME_RSET = 0x19
पूर्ण;

#घोषणा SHDLC_CONNECT_VALUE_MS	5
#घोषणा SHDLC_T1_VALUE_MS(w)	((5 * w) / 4)
#घोषणा SHDLC_T2_VALUE_MS	300

#घोषणा SHDLC_DUMP_SKB(info, skb)				  \
करो अणु								  \
	pr_debug("%s:\n", info);				  \
	prपूर्णांक_hex_dump(KERN_DEBUG, "shdlc: ", DUMP_PREFIX_OFFSET, \
		       16, 1, skb->data, skb->len, 0);		  \
पूर्ण जबतक (0)

/* checks x < y <= z modulo 8 */
अटल bool llc_shdlc_x_lt_y_lteq_z(पूर्णांक x, पूर्णांक y, पूर्णांक z)
अणु
	अगर (x < z)
		वापस ((x < y) && (y <= z)) ? true : false;
	अन्यथा
		वापस ((y > x) || (y <= z)) ? true : false;
पूर्ण

/* checks x <= y < z modulo 8 */
अटल bool llc_shdlc_x_lteq_y_lt_z(पूर्णांक x, पूर्णांक y, पूर्णांक z)
अणु
	अगर (x <= z)
		वापस ((x <= y) && (y < z)) ? true : false;
	अन्यथा			/* x > z -> z+8 > x */
		वापस ((y >= x) || (y < z)) ? true : false;
पूर्ण

अटल काष्ठा sk_buff *llc_shdlc_alloc_skb(काष्ठा llc_shdlc *shdlc,
					   पूर्णांक payload_len)
अणु
	काष्ठा sk_buff *skb;

	skb = alloc_skb(shdlc->tx_headroom + SHDLC_LLC_HEAD_ROOM +
			shdlc->tx_tailroom + payload_len, GFP_KERNEL);
	अगर (skb)
		skb_reserve(skb, shdlc->tx_headroom + SHDLC_LLC_HEAD_ROOM);

	वापस skb;
पूर्ण

/* immediately sends an S frame. */
अटल पूर्णांक llc_shdlc_send_s_frame(काष्ठा llc_shdlc *shdlc,
				  क्रमागत sframe_type sframe_type, पूर्णांक nr)
अणु
	पूर्णांक r;
	काष्ठा sk_buff *skb;

	pr_debug("sframe_type=%d nr=%d\n", sframe_type, nr);

	skb = llc_shdlc_alloc_skb(shdlc, 0);
	अगर (skb == शून्य)
		वापस -ENOMEM;

	*(u8 *)skb_push(skb, 1) = SHDLC_CONTROL_HEAD_S | (sframe_type << 3) | nr;

	r = shdlc->xmit_to_drv(shdlc->hdev, skb);

	kमुक्त_skb(skb);

	वापस r;
पूर्ण

/* immediately sends an U frame. skb may contain optional payload */
अटल पूर्णांक llc_shdlc_send_u_frame(काष्ठा llc_shdlc *shdlc,
				  काष्ठा sk_buff *skb,
				  क्रमागत uframe_modअगरier uframe_modअगरier)
अणु
	पूर्णांक r;

	pr_debug("uframe_modifier=%d\n", uframe_modअगरier);

	*(u8 *)skb_push(skb, 1) = SHDLC_CONTROL_HEAD_U | uframe_modअगरier;

	r = shdlc->xmit_to_drv(shdlc->hdev, skb);

	kमुक्त_skb(skb);

	वापस r;
पूर्ण

/*
 * Free ack_pending frames until y_nr - 1, and reset t2 according to
 * the reमुख्यing oldest ack_pending frame sent समय
 */
अटल व्योम llc_shdlc_reset_t2(काष्ठा llc_shdlc *shdlc, पूर्णांक y_nr)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक dnr = shdlc->dnr;	/* MUST initially be < y_nr */

	pr_debug("release ack pending up to frame %d excluded\n", y_nr);

	जबतक (dnr != y_nr) अणु
		pr_debug("release ack pending frame %d\n", dnr);

		skb = skb_dequeue(&shdlc->ack_pending_q);
		kमुक्त_skb(skb);

		dnr = (dnr + 1) % 8;
	पूर्ण

	अगर (skb_queue_empty(&shdlc->ack_pending_q)) अणु
		अगर (shdlc->t2_active) अणु
			del_समयr_sync(&shdlc->t2_समयr);
			shdlc->t2_active = false;

			pr_debug
			    ("All sent frames acked. Stopped T2(retransmit)\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		skb = skb_peek(&shdlc->ack_pending_q);

		mod_समयr(&shdlc->t2_समयr, *(अचिन्हित दीर्घ *)skb->cb +
			  msecs_to_jअगरfies(SHDLC_T2_VALUE_MS));
		shdlc->t2_active = true;

		pr_debug
		    ("Start T2(retransmit) for remaining unacked sent frames\n");
	पूर्ण
पूर्ण

/*
 * Receive validated frames from lower layer. skb contains HCI payload only.
 * Handle according to algorithm at spec:10.8.2
 */
अटल व्योम llc_shdlc_rcv_i_frame(काष्ठा llc_shdlc *shdlc,
				  काष्ठा sk_buff *skb, पूर्णांक ns, पूर्णांक nr)
अणु
	पूर्णांक x_ns = ns;
	पूर्णांक y_nr = nr;

	pr_debug("recvd I-frame %d, remote waiting frame %d\n", ns, nr);

	अगर (shdlc->state != SHDLC_CONNECTED)
		जाओ निकास;

	अगर (x_ns != shdlc->nr) अणु
		llc_shdlc_send_s_frame(shdlc, S_FRAME_REJ, shdlc->nr);
		जाओ निकास;
	पूर्ण

	अगर (!shdlc->t1_active) अणु
		shdlc->t1_active = true;
		mod_समयr(&shdlc->t1_समयr, jअगरfies +
			  msecs_to_jअगरfies(SHDLC_T1_VALUE_MS(shdlc->w)));
		pr_debug("(re)Start T1(send ack)\n");
	पूर्ण

	अगर (skb->len) अणु
		shdlc->rcv_to_hci(shdlc->hdev, skb);
		skb = शून्य;
	पूर्ण

	shdlc->nr = (shdlc->nr + 1) % 8;

	अगर (llc_shdlc_x_lt_y_lteq_z(shdlc->dnr, y_nr, shdlc->ns)) अणु
		llc_shdlc_reset_t2(shdlc, y_nr);

		shdlc->dnr = y_nr;
	पूर्ण

निकास:
	kमुक्त_skb(skb);
पूर्ण

अटल व्योम llc_shdlc_rcv_ack(काष्ठा llc_shdlc *shdlc, पूर्णांक y_nr)
अणु
	pr_debug("remote acked up to frame %d excluded\n", y_nr);

	अगर (llc_shdlc_x_lt_y_lteq_z(shdlc->dnr, y_nr, shdlc->ns)) अणु
		llc_shdlc_reset_t2(shdlc, y_nr);
		shdlc->dnr = y_nr;
	पूर्ण
पूर्ण

अटल व्योम llc_shdlc_requeue_ack_pending(काष्ठा llc_shdlc *shdlc)
अणु
	काष्ठा sk_buff *skb;

	pr_debug("ns reset to %d\n", shdlc->dnr);

	जबतक ((skb = skb_dequeue_tail(&shdlc->ack_pending_q))) अणु
		skb_pull(skb, 1);	/* हटाओ control field */
		skb_queue_head(&shdlc->send_q, skb);
	पूर्ण
	shdlc->ns = shdlc->dnr;
पूर्ण

अटल व्योम llc_shdlc_rcv_rej(काष्ठा llc_shdlc *shdlc, पूर्णांक y_nr)
अणु
	काष्ठा sk_buff *skb;

	pr_debug("remote asks retransmission from frame %d\n", y_nr);

	अगर (llc_shdlc_x_lteq_y_lt_z(shdlc->dnr, y_nr, shdlc->ns)) अणु
		अगर (shdlc->t2_active) अणु
			del_समयr_sync(&shdlc->t2_समयr);
			shdlc->t2_active = false;
			pr_debug("Stopped T2(retransmit)\n");
		पूर्ण

		अगर (shdlc->dnr != y_nr) अणु
			जबतक ((shdlc->dnr = ((shdlc->dnr + 1) % 8)) != y_nr) अणु
				skb = skb_dequeue(&shdlc->ack_pending_q);
				kमुक्त_skb(skb);
			पूर्ण
		पूर्ण

		llc_shdlc_requeue_ack_pending(shdlc);
	पूर्ण
पूर्ण

/* See spec RR:10.8.3 REJ:10.8.4 */
अटल व्योम llc_shdlc_rcv_s_frame(काष्ठा llc_shdlc *shdlc,
				  क्रमागत sframe_type s_frame_type, पूर्णांक nr)
अणु
	काष्ठा sk_buff *skb;

	अगर (shdlc->state != SHDLC_CONNECTED)
		वापस;

	चयन (s_frame_type) अणु
	हाल S_FRAME_RR:
		llc_shdlc_rcv_ack(shdlc, nr);
		अगर (shdlc->rnr == true) अणु	/* see SHDLC 10.7.7 */
			shdlc->rnr = false;
			अगर (shdlc->send_q.qlen == 0) अणु
				skb = llc_shdlc_alloc_skb(shdlc, 0);
				अगर (skb)
					skb_queue_tail(&shdlc->send_q, skb);
			पूर्ण
		पूर्ण
		अवरोध;
	हाल S_FRAME_REJ:
		llc_shdlc_rcv_rej(shdlc, nr);
		अवरोध;
	हाल S_FRAME_RNR:
		llc_shdlc_rcv_ack(shdlc, nr);
		shdlc->rnr = true;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम llc_shdlc_connect_complete(काष्ठा llc_shdlc *shdlc, पूर्णांक r)
अणु
	pr_debug("result=%d\n", r);

	del_समयr_sync(&shdlc->connect_समयr);

	अगर (r == 0) अणु
		shdlc->ns = 0;
		shdlc->nr = 0;
		shdlc->dnr = 0;

		shdlc->state = SHDLC_HALF_CONNECTED;
	पूर्ण अन्यथा अणु
		shdlc->state = SHDLC_DISCONNECTED;
	पूर्ण

	shdlc->connect_result = r;

	wake_up(shdlc->connect_wq);
पूर्ण

अटल पूर्णांक llc_shdlc_connect_initiate(काष्ठा llc_shdlc *shdlc)
अणु
	काष्ठा sk_buff *skb;

	pr_debug("\n");

	skb = llc_shdlc_alloc_skb(shdlc, 2);
	अगर (skb == शून्य)
		वापस -ENOMEM;

	skb_put_u8(skb, SHDLC_MAX_WINDOW);
	skb_put_u8(skb, SHDLC_SREJ_SUPPORT ? 1 : 0);

	वापस llc_shdlc_send_u_frame(shdlc, skb, U_FRAME_RSET);
पूर्ण

अटल पूर्णांक llc_shdlc_connect_send_ua(काष्ठा llc_shdlc *shdlc)
अणु
	काष्ठा sk_buff *skb;

	pr_debug("\n");

	skb = llc_shdlc_alloc_skb(shdlc, 0);
	अगर (skb == शून्य)
		वापस -ENOMEM;

	वापस llc_shdlc_send_u_frame(shdlc, skb, U_FRAME_UA);
पूर्ण

अटल व्योम llc_shdlc_rcv_u_frame(काष्ठा llc_shdlc *shdlc,
				  काष्ठा sk_buff *skb,
				  क्रमागत uframe_modअगरier u_frame_modअगरier)
अणु
	u8 w = SHDLC_MAX_WINDOW;
	bool srej_support = SHDLC_SREJ_SUPPORT;
	पूर्णांक r;

	pr_debug("u_frame_modifier=%d\n", u_frame_modअगरier);

	चयन (u_frame_modअगरier) अणु
	हाल U_FRAME_RSET:
		चयन (shdlc->state) अणु
		हाल SHDLC_NEGOTIATING:
		हाल SHDLC_CONNECTING:
			/*
			 * We sent RSET, but chip wants to negociate or we
			 * got RSET beक्रमe we managed to send out our.
			 */
			अगर (skb->len > 0)
				w = skb->data[0];

			अगर (skb->len > 1)
				srej_support = skb->data[1] & 0x01 ? true :
					       false;

			अगर ((w <= SHDLC_MAX_WINDOW) &&
			    (SHDLC_SREJ_SUPPORT || (srej_support == false))) अणु
				shdlc->w = w;
				shdlc->srej_support = srej_support;
				r = llc_shdlc_connect_send_ua(shdlc);
				llc_shdlc_connect_complete(shdlc, r);
			पूर्ण
			अवरोध;
		हाल SHDLC_HALF_CONNECTED:
			/*
			 * Chip resent RSET due to its समयout - Ignote it
			 * as we alपढ़ोy sent UA.
			 */
			अवरोध;
		हाल SHDLC_CONNECTED:
			/*
			 * Chip wants to reset link. This is unexpected and
			 * unsupported.
			 */
			shdlc->hard_fault = -ECONNRESET;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल U_FRAME_UA:
		अगर ((shdlc->state == SHDLC_CONNECTING &&
		     shdlc->connect_tries > 0) ||
		    (shdlc->state == SHDLC_NEGOTIATING)) अणु
			llc_shdlc_connect_complete(shdlc, 0);
			shdlc->state = SHDLC_CONNECTED;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	kमुक्त_skb(skb);
पूर्ण

अटल व्योम llc_shdlc_handle_rcv_queue(काष्ठा llc_shdlc *shdlc)
अणु
	काष्ठा sk_buff *skb;
	u8 control;
	पूर्णांक nr;
	पूर्णांक ns;
	क्रमागत sframe_type s_frame_type;
	क्रमागत uframe_modअगरier u_frame_modअगरier;

	अगर (shdlc->rcv_q.qlen)
		pr_debug("rcvQlen=%d\n", shdlc->rcv_q.qlen);

	जबतक ((skb = skb_dequeue(&shdlc->rcv_q)) != शून्य) अणु
		control = skb->data[0];
		skb_pull(skb, 1);
		चयन (control & SHDLC_CONTROL_HEAD_MASK) अणु
		हाल SHDLC_CONTROL_HEAD_I:
		हाल SHDLC_CONTROL_HEAD_I2:
			अगर (shdlc->state == SHDLC_HALF_CONNECTED)
				shdlc->state = SHDLC_CONNECTED;

			ns = (control & SHDLC_CONTROL_NS_MASK) >> 3;
			nr = control & SHDLC_CONTROL_NR_MASK;
			llc_shdlc_rcv_i_frame(shdlc, skb, ns, nr);
			अवरोध;
		हाल SHDLC_CONTROL_HEAD_S:
			अगर (shdlc->state == SHDLC_HALF_CONNECTED)
				shdlc->state = SHDLC_CONNECTED;

			s_frame_type = (control & SHDLC_CONTROL_TYPE_MASK) >> 3;
			nr = control & SHDLC_CONTROL_NR_MASK;
			llc_shdlc_rcv_s_frame(shdlc, s_frame_type, nr);
			kमुक्त_skb(skb);
			अवरोध;
		हाल SHDLC_CONTROL_HEAD_U:
			u_frame_modअगरier = control & SHDLC_CONTROL_M_MASK;
			llc_shdlc_rcv_u_frame(shdlc, skb, u_frame_modअगरier);
			अवरोध;
		शेष:
			pr_err("UNKNOWN Control=%d\n", control);
			kमुक्त_skb(skb);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक llc_shdlc_w_used(पूर्णांक ns, पूर्णांक dnr)
अणु
	पूर्णांक unack_count;

	अगर (dnr <= ns)
		unack_count = ns - dnr;
	अन्यथा
		unack_count = 8 - dnr + ns;

	वापस unack_count;
पूर्ण

/* Send frames according to algorithm at spec:10.8.1 */
अटल व्योम llc_shdlc_handle_send_queue(काष्ठा llc_shdlc *shdlc)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक r;
	अचिन्हित दीर्घ समय_sent;

	अगर (shdlc->send_q.qlen)
		pr_debug
		    ("sendQlen=%d ns=%d dnr=%d rnr=%s w_room=%d unackQlen=%d\n",
		     shdlc->send_q.qlen, shdlc->ns, shdlc->dnr,
		     shdlc->rnr == false ? "false" : "true",
		     shdlc->w - llc_shdlc_w_used(shdlc->ns, shdlc->dnr),
		     shdlc->ack_pending_q.qlen);

	जबतक (shdlc->send_q.qlen && shdlc->ack_pending_q.qlen < shdlc->w &&
	       (shdlc->rnr == false)) अणु

		अगर (shdlc->t1_active) अणु
			del_समयr_sync(&shdlc->t1_समयr);
			shdlc->t1_active = false;
			pr_debug("Stopped T1(send ack)\n");
		पूर्ण

		skb = skb_dequeue(&shdlc->send_q);

		*(u8 *)skb_push(skb, 1) = SHDLC_CONTROL_HEAD_I | (shdlc->ns << 3) |
					shdlc->nr;

		pr_debug("Sending I-Frame %d, waiting to rcv %d\n", shdlc->ns,
			 shdlc->nr);
		SHDLC_DUMP_SKB("shdlc frame written", skb);

		r = shdlc->xmit_to_drv(shdlc->hdev, skb);
		अगर (r < 0) अणु
			shdlc->hard_fault = r;
			अवरोध;
		पूर्ण

		shdlc->ns = (shdlc->ns + 1) % 8;

		समय_sent = jअगरfies;
		*(अचिन्हित दीर्घ *)skb->cb = समय_sent;

		skb_queue_tail(&shdlc->ack_pending_q, skb);

		अगर (shdlc->t2_active == false) अणु
			shdlc->t2_active = true;
			mod_समयr(&shdlc->t2_समयr, समय_sent +
				  msecs_to_jअगरfies(SHDLC_T2_VALUE_MS));
			pr_debug("Started T2 (retransmit)\n");
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम llc_shdlc_connect_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा llc_shdlc *shdlc = from_समयr(shdlc, t, connect_समयr);

	pr_debug("\n");

	schedule_work(&shdlc->sm_work);
पूर्ण

अटल व्योम llc_shdlc_t1_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा llc_shdlc *shdlc = from_समयr(shdlc, t, t1_समयr);

	pr_debug("SoftIRQ: need to send ack\n");

	schedule_work(&shdlc->sm_work);
पूर्ण

अटल व्योम llc_shdlc_t2_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा llc_shdlc *shdlc = from_समयr(shdlc, t, t2_समयr);

	pr_debug("SoftIRQ: need to retransmit\n");

	schedule_work(&shdlc->sm_work);
पूर्ण

अटल व्योम llc_shdlc_sm_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा llc_shdlc *shdlc = container_of(work, काष्ठा llc_shdlc, sm_work);
	पूर्णांक r;

	pr_debug("\n");

	mutex_lock(&shdlc->state_mutex);

	चयन (shdlc->state) अणु
	हाल SHDLC_DISCONNECTED:
		skb_queue_purge(&shdlc->rcv_q);
		skb_queue_purge(&shdlc->send_q);
		skb_queue_purge(&shdlc->ack_pending_q);
		अवरोध;
	हाल SHDLC_CONNECTING:
		अगर (shdlc->hard_fault) अणु
			llc_shdlc_connect_complete(shdlc, shdlc->hard_fault);
			अवरोध;
		पूर्ण

		अगर (shdlc->connect_tries++ < 5)
			r = llc_shdlc_connect_initiate(shdlc);
		अन्यथा
			r = -ETIME;
		अगर (r < 0) अणु
			llc_shdlc_connect_complete(shdlc, r);
		पूर्ण अन्यथा अणु
			mod_समयr(&shdlc->connect_समयr, jअगरfies +
				  msecs_to_jअगरfies(SHDLC_CONNECT_VALUE_MS));

			shdlc->state = SHDLC_NEGOTIATING;
		पूर्ण
		अवरोध;
	हाल SHDLC_NEGOTIATING:
		अगर (समयr_pending(&shdlc->connect_समयr) == 0) अणु
			shdlc->state = SHDLC_CONNECTING;
			schedule_work(&shdlc->sm_work);
		पूर्ण

		llc_shdlc_handle_rcv_queue(shdlc);

		अगर (shdlc->hard_fault) अणु
			llc_shdlc_connect_complete(shdlc, shdlc->hard_fault);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल SHDLC_HALF_CONNECTED:
	हाल SHDLC_CONNECTED:
		llc_shdlc_handle_rcv_queue(shdlc);
		llc_shdlc_handle_send_queue(shdlc);

		अगर (shdlc->t1_active && समयr_pending(&shdlc->t1_समयr) == 0) अणु
			pr_debug
			    ("Handle T1(send ack) elapsed (T1 now inactive)\n");

			shdlc->t1_active = false;
			r = llc_shdlc_send_s_frame(shdlc, S_FRAME_RR,
						   shdlc->nr);
			अगर (r < 0)
				shdlc->hard_fault = r;
		पूर्ण

		अगर (shdlc->t2_active && समयr_pending(&shdlc->t2_समयr) == 0) अणु
			pr_debug
			    ("Handle T2(retransmit) elapsed (T2 inactive)\n");

			shdlc->t2_active = false;

			llc_shdlc_requeue_ack_pending(shdlc);
			llc_shdlc_handle_send_queue(shdlc);
		पूर्ण

		अगर (shdlc->hard_fault)
			shdlc->llc_failure(shdlc->hdev, shdlc->hard_fault);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	mutex_unlock(&shdlc->state_mutex);
पूर्ण

/*
 * Called from syscall context to establish shdlc link. Sleeps until
 * link is पढ़ोy or failure.
 */
अटल पूर्णांक llc_shdlc_connect(काष्ठा llc_shdlc *shdlc)
अणु
	DECLARE_WAIT_QUEUE_HEAD_ONSTACK(connect_wq);

	pr_debug("\n");

	mutex_lock(&shdlc->state_mutex);

	shdlc->state = SHDLC_CONNECTING;
	shdlc->connect_wq = &connect_wq;
	shdlc->connect_tries = 0;
	shdlc->connect_result = 1;

	mutex_unlock(&shdlc->state_mutex);

	schedule_work(&shdlc->sm_work);

	रुको_event(connect_wq, shdlc->connect_result != 1);

	वापस shdlc->connect_result;
पूर्ण

अटल व्योम llc_shdlc_disconnect(काष्ठा llc_shdlc *shdlc)
अणु
	pr_debug("\n");

	mutex_lock(&shdlc->state_mutex);

	shdlc->state = SHDLC_DISCONNECTED;

	mutex_unlock(&shdlc->state_mutex);

	schedule_work(&shdlc->sm_work);
पूर्ण

/*
 * Receive an incoming shdlc frame. Frame has alपढ़ोy been crc-validated.
 * skb contains only LLC header and payload.
 * If skb == शून्य, it is a notअगरication that the link below is dead.
 */
अटल व्योम llc_shdlc_recv_frame(काष्ठा llc_shdlc *shdlc, काष्ठा sk_buff *skb)
अणु
	अगर (skb == शून्य) अणु
		pr_err("NULL Frame -> link is dead\n");
		shdlc->hard_fault = -EREMOTEIO;
	पूर्ण अन्यथा अणु
		SHDLC_DUMP_SKB("incoming frame", skb);
		skb_queue_tail(&shdlc->rcv_q, skb);
	पूर्ण

	schedule_work(&shdlc->sm_work);
पूर्ण

अटल व्योम *llc_shdlc_init(काष्ठा nfc_hci_dev *hdev, xmit_to_drv_t xmit_to_drv,
			    rcv_to_hci_t rcv_to_hci, पूर्णांक tx_headroom,
			    पूर्णांक tx_tailroom, पूर्णांक *rx_headroom, पूर्णांक *rx_tailroom,
			    llc_failure_t llc_failure)
अणु
	काष्ठा llc_shdlc *shdlc;

	*rx_headroom = SHDLC_LLC_HEAD_ROOM;
	*rx_tailroom = 0;

	shdlc = kzalloc(माप(काष्ठा llc_shdlc), GFP_KERNEL);
	अगर (shdlc == शून्य)
		वापस शून्य;

	mutex_init(&shdlc->state_mutex);
	shdlc->state = SHDLC_DISCONNECTED;

	समयr_setup(&shdlc->connect_समयr, llc_shdlc_connect_समयout, 0);
	समयr_setup(&shdlc->t1_समयr, llc_shdlc_t1_समयout, 0);
	समयr_setup(&shdlc->t2_समयr, llc_shdlc_t2_समयout, 0);

	shdlc->w = SHDLC_MAX_WINDOW;
	shdlc->srej_support = SHDLC_SREJ_SUPPORT;

	skb_queue_head_init(&shdlc->rcv_q);
	skb_queue_head_init(&shdlc->send_q);
	skb_queue_head_init(&shdlc->ack_pending_q);

	INIT_WORK(&shdlc->sm_work, llc_shdlc_sm_work);

	shdlc->hdev = hdev;
	shdlc->xmit_to_drv = xmit_to_drv;
	shdlc->rcv_to_hci = rcv_to_hci;
	shdlc->tx_headroom = tx_headroom;
	shdlc->tx_tailroom = tx_tailroom;
	shdlc->llc_failure = llc_failure;

	वापस shdlc;
पूर्ण

अटल व्योम llc_shdlc_deinit(काष्ठा nfc_llc *llc)
अणु
	काष्ठा llc_shdlc *shdlc = nfc_llc_get_data(llc);

	skb_queue_purge(&shdlc->rcv_q);
	skb_queue_purge(&shdlc->send_q);
	skb_queue_purge(&shdlc->ack_pending_q);

	kमुक्त(shdlc);
पूर्ण

अटल पूर्णांक llc_shdlc_start(काष्ठा nfc_llc *llc)
अणु
	काष्ठा llc_shdlc *shdlc = nfc_llc_get_data(llc);

	वापस llc_shdlc_connect(shdlc);
पूर्ण

अटल पूर्णांक llc_shdlc_stop(काष्ठा nfc_llc *llc)
अणु
	काष्ठा llc_shdlc *shdlc = nfc_llc_get_data(llc);

	llc_shdlc_disconnect(shdlc);

	वापस 0;
पूर्ण

अटल व्योम llc_shdlc_rcv_from_drv(काष्ठा nfc_llc *llc, काष्ठा sk_buff *skb)
अणु
	काष्ठा llc_shdlc *shdlc = nfc_llc_get_data(llc);

	llc_shdlc_recv_frame(shdlc, skb);
पूर्ण

अटल पूर्णांक llc_shdlc_xmit_from_hci(काष्ठा nfc_llc *llc, काष्ठा sk_buff *skb)
अणु
	काष्ठा llc_shdlc *shdlc = nfc_llc_get_data(llc);

	skb_queue_tail(&shdlc->send_q, skb);

	schedule_work(&shdlc->sm_work);

	वापस 0;
पूर्ण

अटल काष्ठा nfc_llc_ops llc_shdlc_ops = अणु
	.init = llc_shdlc_init,
	.deinit = llc_shdlc_deinit,
	.start = llc_shdlc_start,
	.stop = llc_shdlc_stop,
	.rcv_from_drv = llc_shdlc_rcv_from_drv,
	.xmit_from_hci = llc_shdlc_xmit_from_hci,
पूर्ण;

पूर्णांक nfc_llc_shdlc_रेजिस्टर(व्योम)
अणु
	वापस nfc_llc_रेजिस्टर(LLC_SHDLC_NAME, &llc_shdlc_ops);
पूर्ण
