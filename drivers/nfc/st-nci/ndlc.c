<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Low Level Transport (NDLC) Driver क्रम STMicroelectronics NFC Chip
 *
 * Copyright (C) 2014-2015  STMicroelectronics SAS. All rights reserved.
 */

#समावेश <linux/sched.h>
#समावेश <net/nfc/nci_core.h>

#समावेश "st-nci.h"

#घोषणा NDLC_TIMER_T1		100
#घोषणा NDLC_TIMER_T1_WAIT	400
#घोषणा NDLC_TIMER_T2		1200

#घोषणा PCB_TYPE_DATAFRAME		0x80
#घोषणा PCB_TYPE_SUPERVISOR		0xc0
#घोषणा PCB_TYPE_MASK			PCB_TYPE_SUPERVISOR

#घोषणा PCB_SYNC_ACK			0x20
#घोषणा PCB_SYNC_NACK			0x10
#घोषणा PCB_SYNC_WAIT			0x30
#घोषणा PCB_SYNC_NOINFO			0x00
#घोषणा PCB_SYNC_MASK			PCB_SYNC_WAIT

#घोषणा PCB_DATAFRAME_RETRANSMIT_YES	0x00
#घोषणा PCB_DATAFRAME_RETRANSMIT_NO	0x04
#घोषणा PCB_DATAFRAME_RETRANSMIT_MASK	PCB_DATAFRAME_RETRANSMIT_NO

#घोषणा PCB_SUPERVISOR_RETRANSMIT_YES	0x00
#घोषणा PCB_SUPERVISOR_RETRANSMIT_NO	0x02
#घोषणा PCB_SUPERVISOR_RETRANSMIT_MASK	PCB_SUPERVISOR_RETRANSMIT_NO

#घोषणा PCB_FRAME_CRC_INFO_PRESENT	0x08
#घोषणा PCB_FRAME_CRC_INFO_NOTPRESENT	0x00
#घोषणा PCB_FRAME_CRC_INFO_MASK		PCB_FRAME_CRC_INFO_PRESENT

#घोषणा NDLC_DUMP_SKB(info, skb)                                 \
करो अणु                                                             \
	pr_debug("%s:\n", info);                                 \
	prपूर्णांक_hex_dump(KERN_DEBUG, "ndlc: ", DUMP_PREFIX_OFFSET, \
			16, 1, skb->data, skb->len, 0);          \
पूर्ण जबतक (0)

पूर्णांक ndlc_खोलो(काष्ठा llt_ndlc *ndlc)
अणु
	/* toggle reset pin */
	ndlc->ops->enable(ndlc->phy_id);
	ndlc->घातered = 1;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(ndlc_खोलो);

व्योम ndlc_बंद(काष्ठा llt_ndlc *ndlc)
अणु
	काष्ठा nci_mode_set_cmd cmd;

	cmd.cmd_type = ST_NCI_SET_NFC_MODE;
	cmd.mode = 0;

	/* toggle reset pin */
	ndlc->ops->enable(ndlc->phy_id);

	nci_prop_cmd(ndlc->ndev, ST_NCI_CORE_PROP,
		     माप(काष्ठा nci_mode_set_cmd), (__u8 *)&cmd);

	ndlc->घातered = 0;
	ndlc->ops->disable(ndlc->phy_id);
पूर्ण
EXPORT_SYMBOL(ndlc_बंद);

पूर्णांक ndlc_send(काष्ठा llt_ndlc *ndlc, काष्ठा sk_buff *skb)
अणु
	/* add ndlc header */
	u8 pcb = PCB_TYPE_DATAFRAME | PCB_DATAFRAME_RETRANSMIT_NO |
		PCB_FRAME_CRC_INFO_NOTPRESENT;

	*(u8 *)skb_push(skb, 1) = pcb;
	skb_queue_tail(&ndlc->send_q, skb);

	schedule_work(&ndlc->sm_work);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ndlc_send);

अटल व्योम llt_ndlc_send_queue(काष्ठा llt_ndlc *ndlc)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक r;
	अचिन्हित दीर्घ समय_sent;

	अगर (ndlc->send_q.qlen)
		pr_debug("sendQlen=%d unackQlen=%d\n",
			 ndlc->send_q.qlen, ndlc->ack_pending_q.qlen);

	जबतक (ndlc->send_q.qlen) अणु
		skb = skb_dequeue(&ndlc->send_q);
		NDLC_DUMP_SKB("ndlc frame written", skb);
		r = ndlc->ops->ग_लिखो(ndlc->phy_id, skb);
		अगर (r < 0) अणु
			ndlc->hard_fault = r;
			अवरोध;
		पूर्ण
		समय_sent = jअगरfies;
		*(अचिन्हित दीर्घ *)skb->cb = समय_sent;

		skb_queue_tail(&ndlc->ack_pending_q, skb);

		/* start समयr t1 क्रम ndlc aknowledge */
		ndlc->t1_active = true;
		mod_समयr(&ndlc->t1_समयr, समय_sent +
			msecs_to_jअगरfies(NDLC_TIMER_T1));
		/* start समयr t2 क्रम chip availability */
		ndlc->t2_active = true;
		mod_समयr(&ndlc->t2_समयr, समय_sent +
			msecs_to_jअगरfies(NDLC_TIMER_T2));
	पूर्ण
पूर्ण

अटल व्योम llt_ndlc_requeue_data_pending(काष्ठा llt_ndlc *ndlc)
अणु
	काष्ठा sk_buff *skb;
	u8 pcb;

	जबतक ((skb = skb_dequeue_tail(&ndlc->ack_pending_q))) अणु
		pcb = skb->data[0];
		चयन (pcb & PCB_TYPE_MASK) अणु
		हाल PCB_TYPE_SUPERVISOR:
			skb->data[0] = (pcb & ~PCB_SUPERVISOR_RETRANSMIT_MASK) |
				PCB_SUPERVISOR_RETRANSMIT_YES;
			अवरोध;
		हाल PCB_TYPE_DATAFRAME:
			skb->data[0] = (pcb & ~PCB_DATAFRAME_RETRANSMIT_MASK) |
				PCB_DATAFRAME_RETRANSMIT_YES;
			अवरोध;
		शेष:
			pr_err("UNKNOWN Packet Control Byte=%d\n", pcb);
			kमुक्त_skb(skb);
			जारी;
		पूर्ण
		skb_queue_head(&ndlc->send_q, skb);
	पूर्ण
पूर्ण

अटल व्योम llt_ndlc_rcv_queue(काष्ठा llt_ndlc *ndlc)
अणु
	काष्ठा sk_buff *skb;
	u8 pcb;
	अचिन्हित दीर्घ समय_sent;

	अगर (ndlc->rcv_q.qlen)
		pr_debug("rcvQlen=%d\n", ndlc->rcv_q.qlen);

	जबतक ((skb = skb_dequeue(&ndlc->rcv_q)) != शून्य) अणु
		pcb = skb->data[0];
		skb_pull(skb, 1);
		अगर ((pcb & PCB_TYPE_MASK) == PCB_TYPE_SUPERVISOR) अणु
			चयन (pcb & PCB_SYNC_MASK) अणु
			हाल PCB_SYNC_ACK:
				skb = skb_dequeue(&ndlc->ack_pending_q);
				kमुक्त_skb(skb);
				del_समयr_sync(&ndlc->t1_समयr);
				del_समयr_sync(&ndlc->t2_समयr);
				ndlc->t2_active = false;
				ndlc->t1_active = false;
				अवरोध;
			हाल PCB_SYNC_NACK:
				llt_ndlc_requeue_data_pending(ndlc);
				llt_ndlc_send_queue(ndlc);
				/* start समयr t1 क्रम ndlc aknowledge */
				समय_sent = jअगरfies;
				ndlc->t1_active = true;
				mod_समयr(&ndlc->t1_समयr, समय_sent +
					msecs_to_jअगरfies(NDLC_TIMER_T1));
				अवरोध;
			हाल PCB_SYNC_WAIT:
				समय_sent = jअगरfies;
				ndlc->t1_active = true;
				mod_समयr(&ndlc->t1_समयr, समय_sent +
					  msecs_to_jअगरfies(NDLC_TIMER_T1_WAIT));
				अवरोध;
			शेष:
				kमुक्त_skb(skb);
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अगर ((pcb & PCB_TYPE_MASK) == PCB_TYPE_DATAFRAME) अणु
			nci_recv_frame(ndlc->ndev, skb);
		पूर्ण अन्यथा अणु
			kमुक्त_skb(skb);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम llt_ndlc_sm_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा llt_ndlc *ndlc = container_of(work, काष्ठा llt_ndlc, sm_work);

	llt_ndlc_send_queue(ndlc);
	llt_ndlc_rcv_queue(ndlc);

	अगर (ndlc->t1_active && समयr_pending(&ndlc->t1_समयr) == 0) अणु
		pr_debug
		    ("Handle T1(recv SUPERVISOR) elapsed (T1 now inactive)\n");
		ndlc->t1_active = false;

		llt_ndlc_requeue_data_pending(ndlc);
		llt_ndlc_send_queue(ndlc);
	पूर्ण

	अगर (ndlc->t2_active && समयr_pending(&ndlc->t2_समयr) == 0) अणु
		pr_debug("Handle T2(recv DATA) elapsed (T2 now inactive)\n");
		ndlc->t2_active = false;
		ndlc->t1_active = false;
		del_समयr_sync(&ndlc->t1_समयr);
		del_समयr_sync(&ndlc->t2_समयr);
		ndlc_बंद(ndlc);
		ndlc->hard_fault = -EREMOTEIO;
	पूर्ण
पूर्ण

व्योम ndlc_recv(काष्ठा llt_ndlc *ndlc, काष्ठा sk_buff *skb)
अणु
	अगर (skb == शून्य) अणु
		pr_err("NULL Frame -> link is dead\n");
		ndlc->hard_fault = -EREMOTEIO;
		ndlc_बंद(ndlc);
	पूर्ण अन्यथा अणु
		NDLC_DUMP_SKB("incoming frame", skb);
		skb_queue_tail(&ndlc->rcv_q, skb);
	पूर्ण

	schedule_work(&ndlc->sm_work);
पूर्ण
EXPORT_SYMBOL(ndlc_recv);

अटल व्योम ndlc_t1_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा llt_ndlc *ndlc = from_समयr(ndlc, t, t1_समयr);

	pr_debug("\n");

	schedule_work(&ndlc->sm_work);
पूर्ण

अटल व्योम ndlc_t2_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा llt_ndlc *ndlc = from_समयr(ndlc, t, t2_समयr);

	pr_debug("\n");

	schedule_work(&ndlc->sm_work);
पूर्ण

पूर्णांक ndlc_probe(व्योम *phy_id, काष्ठा nfc_phy_ops *phy_ops, काष्ठा device *dev,
	       पूर्णांक phy_headroom, पूर्णांक phy_tailroom, काष्ठा llt_ndlc **ndlc_id,
	       काष्ठा st_nci_se_status *se_status)
अणु
	काष्ठा llt_ndlc *ndlc;

	ndlc = devm_kzalloc(dev, माप(काष्ठा llt_ndlc), GFP_KERNEL);
	अगर (!ndlc)
		वापस -ENOMEM;

	ndlc->ops = phy_ops;
	ndlc->phy_id = phy_id;
	ndlc->dev = dev;
	ndlc->घातered = 0;

	*ndlc_id = ndlc;

	/* initialize समयrs */
	समयr_setup(&ndlc->t1_समयr, ndlc_t1_समयout, 0);
	समयr_setup(&ndlc->t2_समयr, ndlc_t2_समयout, 0);

	skb_queue_head_init(&ndlc->rcv_q);
	skb_queue_head_init(&ndlc->send_q);
	skb_queue_head_init(&ndlc->ack_pending_q);

	INIT_WORK(&ndlc->sm_work, llt_ndlc_sm_work);

	वापस st_nci_probe(ndlc, phy_headroom, phy_tailroom, se_status);
पूर्ण
EXPORT_SYMBOL(ndlc_probe);

व्योम ndlc_हटाओ(काष्ठा llt_ndlc *ndlc)
अणु
	st_nci_हटाओ(ndlc->ndev);

	/* cancel समयrs */
	del_समयr_sync(&ndlc->t1_समयr);
	del_समयr_sync(&ndlc->t2_समयr);
	ndlc->t2_active = false;
	ndlc->t1_active = false;

	skb_queue_purge(&ndlc->rcv_q);
	skb_queue_purge(&ndlc->send_q);
पूर्ण
EXPORT_SYMBOL(ndlc_हटाओ);
