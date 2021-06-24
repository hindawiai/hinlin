<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Author	Karsten Keil <kkeil@novell.com>
 *
 * Copyright 2008  by Karsten Keil <kkeil@novell.com>
 */

#समावेश <linux/gfp.h>
#समावेश <linux/module.h>
#समावेश <linux/mISDNhw.h>

अटल व्योम
dchannel_bh(काष्ठा work_काष्ठा *ws)
अणु
	काष्ठा dchannel	*dch  = container_of(ws, काष्ठा dchannel, workq);
	काष्ठा sk_buff	*skb;
	पूर्णांक		err;

	अगर (test_and_clear_bit(FLG_RECVQUEUE, &dch->Flags)) अणु
		जबतक ((skb = skb_dequeue(&dch->rqueue))) अणु
			अगर (likely(dch->dev.D.peer)) अणु
				err = dch->dev.D.recv(dch->dev.D.peer, skb);
				अगर (err)
					dev_kमुक्त_skb(skb);
			पूर्ण अन्यथा
				dev_kमुक्त_skb(skb);
		पूर्ण
	पूर्ण
	अगर (test_and_clear_bit(FLG_PHCHANGE, &dch->Flags)) अणु
		अगर (dch->phfunc)
			dch->phfunc(dch);
	पूर्ण
पूर्ण

अटल व्योम
bchannel_bh(काष्ठा work_काष्ठा *ws)
अणु
	काष्ठा bchannel	*bch  = container_of(ws, काष्ठा bchannel, workq);
	काष्ठा sk_buff	*skb;
	पूर्णांक		err;

	अगर (test_and_clear_bit(FLG_RECVQUEUE, &bch->Flags)) अणु
		जबतक ((skb = skb_dequeue(&bch->rqueue))) अणु
			bch->rcount--;
			अगर (likely(bch->ch.peer)) अणु
				err = bch->ch.recv(bch->ch.peer, skb);
				अगर (err)
					dev_kमुक्त_skb(skb);
			पूर्ण अन्यथा
				dev_kमुक्त_skb(skb);
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक
mISDN_initdchannel(काष्ठा dchannel *ch, पूर्णांक maxlen, व्योम *phf)
अणु
	test_and_set_bit(FLG_HDLC, &ch->Flags);
	ch->maxlen = maxlen;
	ch->hw = शून्य;
	ch->rx_skb = शून्य;
	ch->tx_skb = शून्य;
	ch->tx_idx = 0;
	ch->phfunc = phf;
	skb_queue_head_init(&ch->squeue);
	skb_queue_head_init(&ch->rqueue);
	INIT_LIST_HEAD(&ch->dev.bchannels);
	INIT_WORK(&ch->workq, dchannel_bh);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(mISDN_initdchannel);

पूर्णांक
mISDN_initbchannel(काष्ठा bchannel *ch, अचिन्हित लघु maxlen,
		   अचिन्हित लघु minlen)
अणु
	ch->Flags = 0;
	ch->minlen = minlen;
	ch->next_minlen = minlen;
	ch->init_minlen = minlen;
	ch->maxlen = maxlen;
	ch->next_maxlen = maxlen;
	ch->init_maxlen = maxlen;
	ch->hw = शून्य;
	ch->rx_skb = शून्य;
	ch->tx_skb = शून्य;
	ch->tx_idx = 0;
	skb_queue_head_init(&ch->rqueue);
	ch->rcount = 0;
	ch->next_skb = शून्य;
	INIT_WORK(&ch->workq, bchannel_bh);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(mISDN_initbchannel);

पूर्णांक
mISDN_मुक्तdchannel(काष्ठा dchannel *ch)
अणु
	अगर (ch->tx_skb) अणु
		dev_kमुक्त_skb(ch->tx_skb);
		ch->tx_skb = शून्य;
	पूर्ण
	अगर (ch->rx_skb) अणु
		dev_kमुक्त_skb(ch->rx_skb);
		ch->rx_skb = शून्य;
	पूर्ण
	skb_queue_purge(&ch->squeue);
	skb_queue_purge(&ch->rqueue);
	flush_work(&ch->workq);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(mISDN_मुक्तdchannel);

व्योम
mISDN_clear_bchannel(काष्ठा bchannel *ch)
अणु
	अगर (ch->tx_skb) अणु
		dev_kमुक्त_skb(ch->tx_skb);
		ch->tx_skb = शून्य;
	पूर्ण
	ch->tx_idx = 0;
	अगर (ch->rx_skb) अणु
		dev_kमुक्त_skb(ch->rx_skb);
		ch->rx_skb = शून्य;
	पूर्ण
	अगर (ch->next_skb) अणु
		dev_kमुक्त_skb(ch->next_skb);
		ch->next_skb = शून्य;
	पूर्ण
	test_and_clear_bit(FLG_TX_BUSY, &ch->Flags);
	test_and_clear_bit(FLG_TX_NEXT, &ch->Flags);
	test_and_clear_bit(FLG_ACTIVE, &ch->Flags);
	test_and_clear_bit(FLG_FILLEMPTY, &ch->Flags);
	test_and_clear_bit(FLG_TX_EMPTY, &ch->Flags);
	test_and_clear_bit(FLG_RX_OFF, &ch->Flags);
	ch->dropcnt = 0;
	ch->minlen = ch->init_minlen;
	ch->next_minlen = ch->init_minlen;
	ch->maxlen = ch->init_maxlen;
	ch->next_maxlen = ch->init_maxlen;
	skb_queue_purge(&ch->rqueue);
	ch->rcount = 0;
पूर्ण
EXPORT_SYMBOL(mISDN_clear_bchannel);

व्योम
mISDN_मुक्तbchannel(काष्ठा bchannel *ch)
अणु
	cancel_work_sync(&ch->workq);
	mISDN_clear_bchannel(ch);
पूर्ण
EXPORT_SYMBOL(mISDN_मुक्तbchannel);

पूर्णांक
mISDN_ctrl_bchannel(काष्ठा bchannel *bch, काष्ठा mISDN_ctrl_req *cq)
अणु
	पूर्णांक ret = 0;

	चयन (cq->op) अणु
	हाल MISDN_CTRL_GETOP:
		cq->op = MISDN_CTRL_RX_BUFFER | MISDN_CTRL_FILL_EMPTY |
			 MISDN_CTRL_RX_OFF;
		अवरोध;
	हाल MISDN_CTRL_FILL_EMPTY:
		अगर (cq->p1) अणु
			स_रखो(bch->fill, cq->p2 & 0xff, MISDN_BCH_FILL_SIZE);
			test_and_set_bit(FLG_FILLEMPTY, &bch->Flags);
		पूर्ण अन्यथा अणु
			test_and_clear_bit(FLG_FILLEMPTY, &bch->Flags);
		पूर्ण
		अवरोध;
	हाल MISDN_CTRL_RX_OFF:
		/* पढ़ो back dropped byte count */
		cq->p2 = bch->dropcnt;
		अगर (cq->p1)
			test_and_set_bit(FLG_RX_OFF, &bch->Flags);
		अन्यथा
			test_and_clear_bit(FLG_RX_OFF, &bch->Flags);
		bch->dropcnt = 0;
		अवरोध;
	हाल MISDN_CTRL_RX_BUFFER:
		अगर (cq->p2 > MISDN_CTRL_RX_SIZE_IGNORE)
			bch->next_maxlen = cq->p2;
		अगर (cq->p1 > MISDN_CTRL_RX_SIZE_IGNORE)
			bch->next_minlen = cq->p1;
		/* we वापस the old values */
		cq->p1 = bch->minlen;
		cq->p2 = bch->maxlen;
		अवरोध;
	शेष:
		pr_info("mISDN unhandled control %x operation\n", cq->op);
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL(mISDN_ctrl_bchannel);

अटल अंतरभूत u_पूर्णांक
get_sapi_tei(u_अक्षर *p)
अणु
	u_पूर्णांक	sapi, tei;

	sapi = *p >> 2;
	tei = p[1] >> 1;
	वापस sapi | (tei << 8);
पूर्ण

व्योम
recv_Dchannel(काष्ठा dchannel *dch)
अणु
	काष्ठा mISDNhead *hh;

	अगर (dch->rx_skb->len < 2) अणु /* at least 2 क्रम sapi / tei */
		dev_kमुक्त_skb(dch->rx_skb);
		dch->rx_skb = शून्य;
		वापस;
	पूर्ण
	hh = mISDN_HEAD_P(dch->rx_skb);
	hh->prim = PH_DATA_IND;
	hh->id = get_sapi_tei(dch->rx_skb->data);
	skb_queue_tail(&dch->rqueue, dch->rx_skb);
	dch->rx_skb = शून्य;
	schedule_event(dch, FLG_RECVQUEUE);
पूर्ण
EXPORT_SYMBOL(recv_Dchannel);

व्योम
recv_Echannel(काष्ठा dchannel *ech, काष्ठा dchannel *dch)
अणु
	काष्ठा mISDNhead *hh;

	अगर (ech->rx_skb->len < 2) अणु /* at least 2 क्रम sapi / tei */
		dev_kमुक्त_skb(ech->rx_skb);
		ech->rx_skb = शून्य;
		वापस;
	पूर्ण
	hh = mISDN_HEAD_P(ech->rx_skb);
	hh->prim = PH_DATA_E_IND;
	hh->id = get_sapi_tei(ech->rx_skb->data);
	skb_queue_tail(&dch->rqueue, ech->rx_skb);
	ech->rx_skb = शून्य;
	schedule_event(dch, FLG_RECVQUEUE);
पूर्ण
EXPORT_SYMBOL(recv_Echannel);

व्योम
recv_Bchannel(काष्ठा bchannel *bch, अचिन्हित पूर्णांक id, bool क्रमce)
अणु
	काष्ठा mISDNhead *hh;

	/* अगर allocation did fail upper functions still may call us */
	अगर (unlikely(!bch->rx_skb))
		वापस;
	अगर (unlikely(!bch->rx_skb->len)) अणु
		/* we have no data to send - this may happen after recovery
		 * from overflow or too small allocation.
		 * We need to मुक्त the buffer here */
		dev_kमुक्त_skb(bch->rx_skb);
		bch->rx_skb = शून्य;
	पूर्ण अन्यथा अणु
		अगर (test_bit(FLG_TRANSPARENT, &bch->Flags) &&
		    (bch->rx_skb->len < bch->minlen) && !क्रमce)
				वापस;
		hh = mISDN_HEAD_P(bch->rx_skb);
		hh->prim = PH_DATA_IND;
		hh->id = id;
		अगर (bch->rcount >= 64) अणु
			prपूर्णांकk(KERN_WARNING
			       "B%d receive queue overflow - flushing!\n",
			       bch->nr);
			skb_queue_purge(&bch->rqueue);
		पूर्ण
		bch->rcount++;
		skb_queue_tail(&bch->rqueue, bch->rx_skb);
		bch->rx_skb = शून्य;
		schedule_event(bch, FLG_RECVQUEUE);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(recv_Bchannel);

व्योम
recv_Dchannel_skb(काष्ठा dchannel *dch, काष्ठा sk_buff *skb)
अणु
	skb_queue_tail(&dch->rqueue, skb);
	schedule_event(dch, FLG_RECVQUEUE);
पूर्ण
EXPORT_SYMBOL(recv_Dchannel_skb);

व्योम
recv_Bchannel_skb(काष्ठा bchannel *bch, काष्ठा sk_buff *skb)
अणु
	अगर (bch->rcount >= 64) अणु
		prपूर्णांकk(KERN_WARNING "B-channel %p receive queue overflow, "
		       "flushing!\n", bch);
		skb_queue_purge(&bch->rqueue);
		bch->rcount = 0;
	पूर्ण
	bch->rcount++;
	skb_queue_tail(&bch->rqueue, skb);
	schedule_event(bch, FLG_RECVQUEUE);
पूर्ण
EXPORT_SYMBOL(recv_Bchannel_skb);

अटल व्योम
confirm_Dsend(काष्ठा dchannel *dch)
अणु
	काष्ठा sk_buff	*skb;

	skb = _alloc_mISDN_skb(PH_DATA_CNF, mISDN_HEAD_ID(dch->tx_skb),
			       0, शून्य, GFP_ATOMIC);
	अगर (!skb) अणु
		prपूर्णांकk(KERN_ERR "%s: no skb id %x\n", __func__,
		       mISDN_HEAD_ID(dch->tx_skb));
		वापस;
	पूर्ण
	skb_queue_tail(&dch->rqueue, skb);
	schedule_event(dch, FLG_RECVQUEUE);
पूर्ण

पूर्णांक
get_next_dframe(काष्ठा dchannel *dch)
अणु
	dch->tx_idx = 0;
	dch->tx_skb = skb_dequeue(&dch->squeue);
	अगर (dch->tx_skb) अणु
		confirm_Dsend(dch);
		वापस 1;
	पूर्ण
	dch->tx_skb = शून्य;
	test_and_clear_bit(FLG_TX_BUSY, &dch->Flags);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(get_next_dframe);

अटल व्योम
confirm_Bsend(काष्ठा bchannel *bch)
अणु
	काष्ठा sk_buff	*skb;

	अगर (bch->rcount >= 64) अणु
		prपूर्णांकk(KERN_WARNING "B-channel %p receive queue overflow, "
		       "flushing!\n", bch);
		skb_queue_purge(&bch->rqueue);
		bch->rcount = 0;
	पूर्ण
	skb = _alloc_mISDN_skb(PH_DATA_CNF, mISDN_HEAD_ID(bch->tx_skb),
			       0, शून्य, GFP_ATOMIC);
	अगर (!skb) अणु
		prपूर्णांकk(KERN_ERR "%s: no skb id %x\n", __func__,
		       mISDN_HEAD_ID(bch->tx_skb));
		वापस;
	पूर्ण
	bch->rcount++;
	skb_queue_tail(&bch->rqueue, skb);
	schedule_event(bch, FLG_RECVQUEUE);
पूर्ण

पूर्णांक
get_next_bframe(काष्ठा bchannel *bch)
अणु
	bch->tx_idx = 0;
	अगर (test_bit(FLG_TX_NEXT, &bch->Flags)) अणु
		bch->tx_skb = bch->next_skb;
		अगर (bch->tx_skb) अणु
			bch->next_skb = शून्य;
			test_and_clear_bit(FLG_TX_NEXT, &bch->Flags);
			/* confirm imediately to allow next data */
			confirm_Bsend(bch);
			वापस 1;
		पूर्ण अन्यथा अणु
			test_and_clear_bit(FLG_TX_NEXT, &bch->Flags);
			prपूर्णांकk(KERN_WARNING "B TX_NEXT without skb\n");
		पूर्ण
	पूर्ण
	bch->tx_skb = शून्य;
	test_and_clear_bit(FLG_TX_BUSY, &bch->Flags);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(get_next_bframe);

व्योम
queue_ch_frame(काष्ठा mISDNchannel *ch, u_पूर्णांक pr, पूर्णांक id, काष्ठा sk_buff *skb)
अणु
	काष्ठा mISDNhead *hh;

	अगर (!skb) अणु
		_queue_data(ch, pr, id, 0, शून्य, GFP_ATOMIC);
	पूर्ण अन्यथा अणु
		अगर (ch->peer) अणु
			hh = mISDN_HEAD_P(skb);
			hh->prim = pr;
			hh->id = id;
			अगर (!ch->recv(ch->peer, skb))
				वापस;
		पूर्ण
		dev_kमुक्त_skb(skb);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(queue_ch_frame);

पूर्णांक
dchannel_senddata(काष्ठा dchannel *ch, काष्ठा sk_buff *skb)
अणु
	/* check oversize */
	अगर (skb->len <= 0) अणु
		prपूर्णांकk(KERN_WARNING "%s: skb too small\n", __func__);
		वापस -EINVAL;
	पूर्ण
	अगर (skb->len > ch->maxlen) अणु
		prपूर्णांकk(KERN_WARNING "%s: skb too large(%d/%d)\n",
		       __func__, skb->len, ch->maxlen);
		वापस -EINVAL;
	पूर्ण
	/* HW lock must be obtained */
	अगर (test_and_set_bit(FLG_TX_BUSY, &ch->Flags)) अणु
		skb_queue_tail(&ch->squeue, skb);
		वापस 0;
	पूर्ण अन्यथा अणु
		/* ग_लिखो to fअगरo */
		ch->tx_skb = skb;
		ch->tx_idx = 0;
		वापस 1;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(dchannel_senddata);

पूर्णांक
bchannel_senddata(काष्ठा bchannel *ch, काष्ठा sk_buff *skb)
अणु

	/* check oversize */
	अगर (skb->len <= 0) अणु
		prपूर्णांकk(KERN_WARNING "%s: skb too small\n", __func__);
		वापस -EINVAL;
	पूर्ण
	अगर (skb->len > ch->maxlen) अणु
		prपूर्णांकk(KERN_WARNING "%s: skb too large(%d/%d)\n",
		       __func__, skb->len, ch->maxlen);
		वापस -EINVAL;
	पूर्ण
	/* HW lock must be obtained */
	/* check क्रम pending next_skb */
	अगर (ch->next_skb) अणु
		prपूर्णांकk(KERN_WARNING
		       "%s: next_skb exist ERROR (skb->len=%d next_skb->len=%d)\n",
		       __func__, skb->len, ch->next_skb->len);
		वापस -EBUSY;
	पूर्ण
	अगर (test_and_set_bit(FLG_TX_BUSY, &ch->Flags)) अणु
		test_and_set_bit(FLG_TX_NEXT, &ch->Flags);
		ch->next_skb = skb;
		वापस 0;
	पूर्ण अन्यथा अणु
		/* ग_लिखो to fअगरo */
		ch->tx_skb = skb;
		ch->tx_idx = 0;
		confirm_Bsend(ch);
		वापस 1;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(bchannel_senddata);

/* The function allocates a new receive skb on demand with a size क्रम the
 * requirements of the current protocol. It वापसs the tailroom of the
 * receive skb or an error.
 */
पूर्णांक
bchannel_get_rxbuf(काष्ठा bchannel *bch, पूर्णांक reqlen)
अणु
	पूर्णांक len;

	अगर (bch->rx_skb) अणु
		len = skb_tailroom(bch->rx_skb);
		अगर (len < reqlen) अणु
			pr_warn("B%d no space for %d (only %d) bytes\n",
				bch->nr, reqlen, len);
			अगर (test_bit(FLG_TRANSPARENT, &bch->Flags)) अणु
				/* send what we have now and try a new buffer */
				recv_Bchannel(bch, 0, true);
			पूर्ण अन्यथा अणु
				/* on HDLC we have to drop too big frames */
				वापस -EMSGSIZE;
			पूर्ण
		पूर्ण अन्यथा अणु
			वापस len;
		पूर्ण
	पूर्ण
	/* update current min/max length first */
	अगर (unlikely(bch->maxlen != bch->next_maxlen))
		bch->maxlen = bch->next_maxlen;
	अगर (unlikely(bch->minlen != bch->next_minlen))
		bch->minlen = bch->next_minlen;
	अगर (unlikely(reqlen > bch->maxlen))
		वापस -EMSGSIZE;
	अगर (test_bit(FLG_TRANSPARENT, &bch->Flags)) अणु
		अगर (reqlen >= bch->minlen) अणु
			len = reqlen;
		पूर्ण अन्यथा अणु
			len = 2 * bch->minlen;
			अगर (len > bch->maxlen)
				len = bch->maxlen;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* with HDLC we करो not know the length yet */
		len = bch->maxlen;
	पूर्ण
	bch->rx_skb = mI_alloc_skb(len, GFP_ATOMIC);
	अगर (!bch->rx_skb) अणु
		pr_warn("B%d receive no memory for %d bytes\n", bch->nr, len);
		len = -ENOMEM;
	पूर्ण
	वापस len;
पूर्ण
EXPORT_SYMBOL(bchannel_get_rxbuf);
