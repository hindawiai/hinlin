<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Author	Karsten Keil <kkeil@novell.com>
 *
 * Copyright 2008  by Karsten Keil <kkeil@novell.com>
 */

#समावेश <linux/slab.h>
#समावेश <linux/mISDNअगर.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/cpuसमय.स>
#समावेश <linux/संकेत.स>

#समावेश "core.h"

अटल u_पूर्णांक	*debug;

अटल अंतरभूत व्योम
_queue_message(काष्ठा mISDNstack *st, काष्ठा sk_buff *skb)
अणु
	काष्ठा mISDNhead	*hh = mISDN_HEAD_P(skb);

	अगर (*debug & DEBUG_QUEUE_FUNC)
		prपूर्णांकk(KERN_DEBUG "%s prim(%x) id(%x) %p\n",
		       __func__, hh->prim, hh->id, skb);
	skb_queue_tail(&st->msgq, skb);
	अगर (likely(!test_bit(mISDN_STACK_STOPPED, &st->status))) अणु
		test_and_set_bit(mISDN_STACK_WORK, &st->status);
		wake_up_पूर्णांकerruptible(&st->workq);
	पूर्ण
पूर्ण

अटल पूर्णांक
mISDN_queue_message(काष्ठा mISDNchannel *ch, काष्ठा sk_buff *skb)
अणु
	_queue_message(ch->st, skb);
	वापस 0;
पूर्ण

अटल काष्ठा mISDNchannel *
get_channel4id(काष्ठा mISDNstack *st, u_पूर्णांक id)
अणु
	काष्ठा mISDNchannel	*ch;

	mutex_lock(&st->lmutex);
	list_क्रम_each_entry(ch, &st->layer2, list) अणु
		अगर (id == ch->nr)
			जाओ unlock;
	पूर्ण
	ch = शून्य;
unlock:
	mutex_unlock(&st->lmutex);
	वापस ch;
पूर्ण

अटल व्योम
send_socklist(काष्ठा mISDN_sock_list *sl, काष्ठा sk_buff *skb)
अणु
	काष्ठा sock		*sk;
	काष्ठा sk_buff		*cskb = शून्य;

	पढ़ो_lock(&sl->lock);
	sk_क्रम_each(sk, &sl->head) अणु
		अगर (sk->sk_state != MISDN_BOUND)
			जारी;
		अगर (!cskb)
			cskb = skb_copy(skb, GFP_ATOMIC);
		अगर (!cskb) अणु
			prपूर्णांकk(KERN_WARNING "%s no skb\n", __func__);
			अवरोध;
		पूर्ण
		अगर (!sock_queue_rcv_skb(sk, cskb))
			cskb = शून्य;
	पूर्ण
	पढ़ो_unlock(&sl->lock);
	dev_kमुक्त_skb(cskb);
पूर्ण

अटल व्योम
send_layer2(काष्ठा mISDNstack *st, काष्ठा sk_buff *skb)
अणु
	काष्ठा sk_buff		*cskb;
	काष्ठा mISDNhead	*hh = mISDN_HEAD_P(skb);
	काष्ठा mISDNchannel	*ch;
	पूर्णांक			ret;

	अगर (!st)
		वापस;
	mutex_lock(&st->lmutex);
	अगर ((hh->id & MISDN_ID_ADDR_MASK) == MISDN_ID_ANY) अणु /* L2 क्रम all */
		list_क्रम_each_entry(ch, &st->layer2, list) अणु
			अगर (list_is_last(&ch->list, &st->layer2)) अणु
				cskb = skb;
				skb = शून्य;
			पूर्ण अन्यथा अणु
				cskb = skb_copy(skb, GFP_KERNEL);
			पूर्ण
			अगर (cskb) अणु
				ret = ch->send(ch, cskb);
				अगर (ret) अणु
					अगर (*debug & DEBUG_SEND_ERR)
						prपूर्णांकk(KERN_DEBUG
						       "%s ch%d prim(%x) addr(%x)"
						       " err %d\n",
						       __func__, ch->nr,
						       hh->prim, ch->addr, ret);
					dev_kमुक्त_skb(cskb);
				पूर्ण
			पूर्ण अन्यथा अणु
				prपूर्णांकk(KERN_WARNING "%s ch%d addr %x no mem\n",
				       __func__, ch->nr, ch->addr);
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		list_क्रम_each_entry(ch, &st->layer2, list) अणु
			अगर ((hh->id & MISDN_ID_ADDR_MASK) == ch->addr) अणु
				ret = ch->send(ch, skb);
				अगर (!ret)
					skb = शून्य;
				जाओ out;
			पूर्ण
		पूर्ण
		ret = st->dev->teimgr->ctrl(st->dev->teimgr, CHECK_DATA, skb);
		अगर (!ret)
			skb = शून्य;
		अन्यथा अगर (*debug & DEBUG_SEND_ERR)
			prपूर्णांकk(KERN_DEBUG
			       "%s mgr prim(%x) err %d\n",
			       __func__, hh->prim, ret);
	पूर्ण
out:
	mutex_unlock(&st->lmutex);
	dev_kमुक्त_skb(skb);
पूर्ण

अटल अंतरभूत पूर्णांक
send_msg_to_layer(काष्ठा mISDNstack *st, काष्ठा sk_buff *skb)
अणु
	काष्ठा mISDNhead	*hh = mISDN_HEAD_P(skb);
	काष्ठा mISDNchannel	*ch;
	पूर्णांक	lm;

	lm = hh->prim & MISDN_LAYERMASK;
	अगर (*debug & DEBUG_QUEUE_FUNC)
		prपूर्णांकk(KERN_DEBUG "%s prim(%x) id(%x) %p\n",
		       __func__, hh->prim, hh->id, skb);
	अगर (lm == 0x1) अणु
		अगर (!hlist_empty(&st->l1sock.head)) अणु
			__net_बारtamp(skb);
			send_socklist(&st->l1sock, skb);
		पूर्ण
		वापस st->layer1->send(st->layer1, skb);
	पूर्ण अन्यथा अगर (lm == 0x2) अणु
		अगर (!hlist_empty(&st->l1sock.head))
			send_socklist(&st->l1sock, skb);
		send_layer2(st, skb);
		वापस 0;
	पूर्ण अन्यथा अगर (lm == 0x4) अणु
		ch = get_channel4id(st, hh->id);
		अगर (ch)
			वापस ch->send(ch, skb);
		अन्यथा
			prपूर्णांकk(KERN_WARNING
			       "%s: dev(%s) prim(%x) id(%x) no channel\n",
			       __func__, dev_name(&st->dev->dev), hh->prim,
			       hh->id);
	पूर्ण अन्यथा अगर (lm == 0x8) अणु
		WARN_ON(lm == 0x8);
		ch = get_channel4id(st, hh->id);
		अगर (ch)
			वापस ch->send(ch, skb);
		अन्यथा
			prपूर्णांकk(KERN_WARNING
			       "%s: dev(%s) prim(%x) id(%x) no channel\n",
			       __func__, dev_name(&st->dev->dev), hh->prim,
			       hh->id);
	पूर्ण अन्यथा अणु
		/* broadcast not handled yet */
		prपूर्णांकk(KERN_WARNING "%s: dev(%s) prim %x not delivered\n",
		       __func__, dev_name(&st->dev->dev), hh->prim);
	पूर्ण
	वापस -ESRCH;
पूर्ण

अटल व्योम
करो_clear_stack(काष्ठा mISDNstack *st)
अणु
पूर्ण

अटल पूर्णांक
mISDNStackd(व्योम *data)
अणु
	काष्ठा mISDNstack *st = data;
#अगर_घोषित MISDN_MSG_STATS
	u64 uसमय, sसमय;
#पूर्ण_अगर
	पूर्णांक err = 0;

	sigfillset(&current->blocked);
	अगर (*debug & DEBUG_MSG_THREAD)
		prपूर्णांकk(KERN_DEBUG "mISDNStackd %s started\n",
		       dev_name(&st->dev->dev));

	अगर (st->notअगरy != शून्य) अणु
		complete(st->notअगरy);
		st->notअगरy = शून्य;
	पूर्ण

	क्रम (;;) अणु
		काष्ठा sk_buff	*skb;

		अगर (unlikely(test_bit(mISDN_STACK_STOPPED, &st->status))) अणु
			test_and_clear_bit(mISDN_STACK_WORK, &st->status);
			test_and_clear_bit(mISDN_STACK_RUNNING, &st->status);
		पूर्ण अन्यथा
			test_and_set_bit(mISDN_STACK_RUNNING, &st->status);
		जबतक (test_bit(mISDN_STACK_WORK, &st->status)) अणु
			skb = skb_dequeue(&st->msgq);
			अगर (!skb) अणु
				test_and_clear_bit(mISDN_STACK_WORK,
						   &st->status);
				/* test अगर a race happens */
				skb = skb_dequeue(&st->msgq);
				अगर (!skb)
					जारी;
				test_and_set_bit(mISDN_STACK_WORK,
						 &st->status);
			पूर्ण
#अगर_घोषित MISDN_MSG_STATS
			st->msg_cnt++;
#पूर्ण_अगर
			err = send_msg_to_layer(st, skb);
			अगर (unlikely(err)) अणु
				अगर (*debug & DEBUG_SEND_ERR)
					prपूर्णांकk(KERN_DEBUG
					       "%s: %s prim(%x) id(%x) "
					       "send call(%d)\n",
					       __func__, dev_name(&st->dev->dev),
					       mISDN_HEAD_PRIM(skb),
					       mISDN_HEAD_ID(skb), err);
				dev_kमुक्त_skb(skb);
				जारी;
			पूर्ण
			अगर (unlikely(test_bit(mISDN_STACK_STOPPED,
					      &st->status))) अणु
				test_and_clear_bit(mISDN_STACK_WORK,
						   &st->status);
				test_and_clear_bit(mISDN_STACK_RUNNING,
						   &st->status);
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (test_bit(mISDN_STACK_CLEARING, &st->status)) अणु
			test_and_set_bit(mISDN_STACK_STOPPED, &st->status);
			test_and_clear_bit(mISDN_STACK_RUNNING, &st->status);
			करो_clear_stack(st);
			test_and_clear_bit(mISDN_STACK_CLEARING, &st->status);
			test_and_set_bit(mISDN_STACK_RESTART, &st->status);
		पूर्ण
		अगर (test_and_clear_bit(mISDN_STACK_RESTART, &st->status)) अणु
			test_and_clear_bit(mISDN_STACK_STOPPED, &st->status);
			test_and_set_bit(mISDN_STACK_RUNNING, &st->status);
			अगर (!skb_queue_empty(&st->msgq))
				test_and_set_bit(mISDN_STACK_WORK,
						 &st->status);
		पूर्ण
		अगर (test_bit(mISDN_STACK_ABORT, &st->status))
			अवरोध;
		अगर (st->notअगरy != शून्य) अणु
			complete(st->notअगरy);
			st->notअगरy = शून्य;
		पूर्ण
#अगर_घोषित MISDN_MSG_STATS
		st->sleep_cnt++;
#पूर्ण_अगर
		test_and_clear_bit(mISDN_STACK_ACTIVE, &st->status);
		रुको_event_पूर्णांकerruptible(st->workq, (st->status &
						     mISDN_STACK_ACTION_MASK));
		अगर (*debug & DEBUG_MSG_THREAD)
			prपूर्णांकk(KERN_DEBUG "%s: %s wake status %08lx\n",
			       __func__, dev_name(&st->dev->dev), st->status);
		test_and_set_bit(mISDN_STACK_ACTIVE, &st->status);

		test_and_clear_bit(mISDN_STACK_WAKEUP, &st->status);

		अगर (test_bit(mISDN_STACK_STOPPED, &st->status)) अणु
			test_and_clear_bit(mISDN_STACK_RUNNING, &st->status);
#अगर_घोषित MISDN_MSG_STATS
			st->stopped_cnt++;
#पूर्ण_अगर
		पूर्ण
	पूर्ण
#अगर_घोषित MISDN_MSG_STATS
	prपूर्णांकk(KERN_DEBUG "mISDNStackd daemon for %s proceed %d "
	       "msg %d sleep %d stopped\n",
	       dev_name(&st->dev->dev), st->msg_cnt, st->sleep_cnt,
	       st->stopped_cnt);
	task_cpuसमय(st->thपढ़ो, &uसमय, &sसमय);
	prपूर्णांकk(KERN_DEBUG
	       "mISDNStackd daemon for %s utime(%llu) stime(%llu)\n",
	       dev_name(&st->dev->dev), uसमय, sसमय);
	prपूर्णांकk(KERN_DEBUG
	       "mISDNStackd daemon for %s nvcsw(%ld) nivcsw(%ld)\n",
	       dev_name(&st->dev->dev), st->thपढ़ो->nvcsw, st->thपढ़ो->nivcsw);
	prपूर्णांकk(KERN_DEBUG "mISDNStackd daemon for %s killed now\n",
	       dev_name(&st->dev->dev));
#पूर्ण_अगर
	test_and_set_bit(mISDN_STACK_KILLED, &st->status);
	test_and_clear_bit(mISDN_STACK_RUNNING, &st->status);
	test_and_clear_bit(mISDN_STACK_ACTIVE, &st->status);
	test_and_clear_bit(mISDN_STACK_ABORT, &st->status);
	skb_queue_purge(&st->msgq);
	st->thपढ़ो = शून्य;
	अगर (st->notअगरy != शून्य) अणु
		complete(st->notअगरy);
		st->notअगरy = शून्य;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
l1_receive(काष्ठा mISDNchannel *ch, काष्ठा sk_buff *skb)
अणु
	अगर (!ch->st)
		वापस -ENODEV;
	__net_बारtamp(skb);
	_queue_message(ch->st, skb);
	वापस 0;
पूर्ण

व्योम
set_channel_address(काष्ठा mISDNchannel *ch, u_पूर्णांक sapi, u_पूर्णांक tei)
अणु
	ch->addr = sapi | (tei << 8);
पूर्ण

व्योम
__add_layer2(काष्ठा mISDNchannel *ch, काष्ठा mISDNstack *st)
अणु
	list_add_tail(&ch->list, &st->layer2);
पूर्ण

व्योम
add_layer2(काष्ठा mISDNchannel *ch, काष्ठा mISDNstack *st)
अणु
	mutex_lock(&st->lmutex);
	__add_layer2(ch, st);
	mutex_unlock(&st->lmutex);
पूर्ण

अटल पूर्णांक
st_own_ctrl(काष्ठा mISDNchannel *ch, u_पूर्णांक cmd, व्योम *arg)
अणु
	अगर (!ch->st || !ch->st->layer1)
		वापस -EINVAL;
	वापस ch->st->layer1->ctrl(ch->st->layer1, cmd, arg);
पूर्ण

पूर्णांक
create_stack(काष्ठा mISDNdevice *dev)
अणु
	काष्ठा mISDNstack	*newst;
	पूर्णांक			err;
	DECLARE_COMPLETION_ONSTACK(करोne);

	newst = kzalloc(माप(काष्ठा mISDNstack), GFP_KERNEL);
	अगर (!newst) अणु
		prपूर्णांकk(KERN_ERR "kmalloc mISDN_stack failed\n");
		वापस -ENOMEM;
	पूर्ण
	newst->dev = dev;
	INIT_LIST_HEAD(&newst->layer2);
	INIT_HLIST_HEAD(&newst->l1sock.head);
	rwlock_init(&newst->l1sock.lock);
	init_रुकोqueue_head(&newst->workq);
	skb_queue_head_init(&newst->msgq);
	mutex_init(&newst->lmutex);
	dev->D.st = newst;
	err = create_teimanager(dev);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "kmalloc teimanager failed\n");
		kमुक्त(newst);
		वापस err;
	पूर्ण
	dev->teimgr->peer = &newst->own;
	dev->teimgr->recv = mISDN_queue_message;
	dev->teimgr->st = newst;
	newst->layer1 = &dev->D;
	dev->D.recv = l1_receive;
	dev->D.peer = &newst->own;
	newst->own.st = newst;
	newst->own.ctrl = st_own_ctrl;
	newst->own.send = mISDN_queue_message;
	newst->own.recv = mISDN_queue_message;
	अगर (*debug & DEBUG_CORE_FUNC)
		prपूर्णांकk(KERN_DEBUG "%s: st(%s)\n", __func__,
		       dev_name(&newst->dev->dev));
	newst->notअगरy = &करोne;
	newst->thपढ़ो = kthपढ़ो_run(mISDNStackd, (व्योम *)newst, "mISDN_%s",
				    dev_name(&newst->dev->dev));
	अगर (IS_ERR(newst->thपढ़ो)) अणु
		err = PTR_ERR(newst->thपढ़ो);
		prपूर्णांकk(KERN_ERR
		       "mISDN:cannot create kernel thread for %s (%d)\n",
		       dev_name(&newst->dev->dev), err);
		delete_teimanager(dev->teimgr);
		kमुक्त(newst);
	पूर्ण अन्यथा
		रुको_क्रम_completion(&करोne);
	वापस err;
पूर्ण

पूर्णांक
connect_layer1(काष्ठा mISDNdevice *dev, काष्ठा mISDNchannel *ch,
	       u_पूर्णांक protocol, काष्ठा sockaddr_mISDN *adr)
अणु
	काष्ठा mISDN_sock	*msk = container_of(ch, काष्ठा mISDN_sock, ch);
	काष्ठा channel_req	rq;
	पूर्णांक			err;


	अगर (*debug &  DEBUG_CORE_FUNC)
		prपूर्णांकk(KERN_DEBUG "%s: %s proto(%x) adr(%d %d %d %d)\n",
		       __func__, dev_name(&dev->dev), protocol, adr->dev,
		       adr->channel, adr->sapi, adr->tei);
	चयन (protocol) अणु
	हाल ISDN_P_NT_S0:
	हाल ISDN_P_NT_E1:
	हाल ISDN_P_TE_S0:
	हाल ISDN_P_TE_E1:
		ch->recv = mISDN_queue_message;
		ch->peer = &dev->D.st->own;
		ch->st = dev->D.st;
		rq.protocol = protocol;
		rq.adr.channel = adr->channel;
		err = dev->D.ctrl(&dev->D, OPEN_CHANNEL, &rq);
		prपूर्णांकk(KERN_DEBUG "%s: ret %d (dev %d)\n", __func__, err,
		       dev->id);
		अगर (err)
			वापस err;
		ग_लिखो_lock_bh(&dev->D.st->l1sock.lock);
		sk_add_node(&msk->sk, &dev->D.st->l1sock.head);
		ग_लिखो_unlock_bh(&dev->D.st->l1sock.lock);
		अवरोध;
	शेष:
		वापस -ENOPROTOOPT;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक
connect_Bstack(काष्ठा mISDNdevice *dev, काष्ठा mISDNchannel *ch,
	       u_पूर्णांक protocol, काष्ठा sockaddr_mISDN *adr)
अणु
	काष्ठा channel_req	rq, rq2;
	पूर्णांक			pmask, err;
	काष्ठा Bprotocol	*bp;

	अगर (*debug &  DEBUG_CORE_FUNC)
		prपूर्णांकk(KERN_DEBUG "%s: %s proto(%x) adr(%d %d %d %d)\n",
		       __func__, dev_name(&dev->dev), protocol,
		       adr->dev, adr->channel, adr->sapi,
		       adr->tei);
	ch->st = dev->D.st;
	pmask = 1 << (protocol & ISDN_P_B_MASK);
	अगर (pmask & dev->Bprotocols) अणु
		rq.protocol = protocol;
		rq.adr = *adr;
		err = dev->D.ctrl(&dev->D, OPEN_CHANNEL, &rq);
		अगर (err)
			वापस err;
		ch->recv = rq.ch->send;
		ch->peer = rq.ch;
		rq.ch->recv = ch->send;
		rq.ch->peer = ch;
		rq.ch->st = dev->D.st;
	पूर्ण अन्यथा अणु
		bp = get_Bprotocol4mask(pmask);
		अगर (!bp)
			वापस -ENOPROTOOPT;
		rq2.protocol = protocol;
		rq2.adr = *adr;
		rq2.ch = ch;
		err = bp->create(&rq2);
		अगर (err)
			वापस err;
		ch->recv = rq2.ch->send;
		ch->peer = rq2.ch;
		rq2.ch->st = dev->D.st;
		rq.protocol = rq2.protocol;
		rq.adr = *adr;
		err = dev->D.ctrl(&dev->D, OPEN_CHANNEL, &rq);
		अगर (err) अणु
			rq2.ch->ctrl(rq2.ch, CLOSE_CHANNEL, शून्य);
			वापस err;
		पूर्ण
		rq2.ch->recv = rq.ch->send;
		rq2.ch->peer = rq.ch;
		rq.ch->recv = rq2.ch->send;
		rq.ch->peer = rq2.ch;
		rq.ch->st = dev->D.st;
	पूर्ण
	ch->protocol = protocol;
	ch->nr = rq.ch->nr;
	वापस 0;
पूर्ण

पूर्णांक
create_l2entity(काष्ठा mISDNdevice *dev, काष्ठा mISDNchannel *ch,
		u_पूर्णांक protocol, काष्ठा sockaddr_mISDN *adr)
अणु
	काष्ठा channel_req	rq;
	पूर्णांक			err;

	अगर (*debug &  DEBUG_CORE_FUNC)
		prपूर्णांकk(KERN_DEBUG "%s: %s proto(%x) adr(%d %d %d %d)\n",
		       __func__, dev_name(&dev->dev), protocol,
		       adr->dev, adr->channel, adr->sapi,
		       adr->tei);
	rq.protocol = ISDN_P_TE_S0;
	अगर (dev->Dprotocols & (1 << ISDN_P_TE_E1))
		rq.protocol = ISDN_P_TE_E1;
	चयन (protocol) अणु
	हाल ISDN_P_LAPD_NT:
		rq.protocol = ISDN_P_NT_S0;
		अगर (dev->Dprotocols & (1 << ISDN_P_NT_E1))
			rq.protocol = ISDN_P_NT_E1;
		fallthrough;
	हाल ISDN_P_LAPD_TE:
		ch->recv = mISDN_queue_message;
		ch->peer = &dev->D.st->own;
		ch->st = dev->D.st;
		rq.adr.channel = 0;
		err = dev->D.ctrl(&dev->D, OPEN_CHANNEL, &rq);
		prपूर्णांकk(KERN_DEBUG "%s: ret 1 %d\n", __func__, err);
		अगर (err)
			अवरोध;
		rq.protocol = protocol;
		rq.adr = *adr;
		rq.ch = ch;
		err = dev->teimgr->ctrl(dev->teimgr, OPEN_CHANNEL, &rq);
		prपूर्णांकk(KERN_DEBUG "%s: ret 2 %d\n", __func__, err);
		अगर (!err) अणु
			अगर ((protocol == ISDN_P_LAPD_NT) && !rq.ch)
				अवरोध;
			add_layer2(rq.ch, dev->D.st);
			rq.ch->recv = mISDN_queue_message;
			rq.ch->peer = &dev->D.st->own;
			rq.ch->ctrl(rq.ch, OPEN_CHANNEL, शून्य); /* can't fail */
		पूर्ण
		अवरोध;
	शेष:
		err = -EPROTONOSUPPORT;
	पूर्ण
	वापस err;
पूर्ण

व्योम
delete_channel(काष्ठा mISDNchannel *ch)
अणु
	काष्ठा mISDN_sock	*msk = container_of(ch, काष्ठा mISDN_sock, ch);
	काष्ठा mISDNchannel	*pch;

	अगर (!ch->st) अणु
		prपूर्णांकk(KERN_WARNING "%s: no stack\n", __func__);
		वापस;
	पूर्ण
	अगर (*debug & DEBUG_CORE_FUNC)
		prपूर्णांकk(KERN_DEBUG "%s: st(%s) protocol(%x)\n", __func__,
		       dev_name(&ch->st->dev->dev), ch->protocol);
	अगर (ch->protocol >= ISDN_P_B_START) अणु
		अगर (ch->peer) अणु
			ch->peer->ctrl(ch->peer, CLOSE_CHANNEL, शून्य);
			ch->peer = शून्य;
		पूर्ण
		वापस;
	पूर्ण
	चयन (ch->protocol) अणु
	हाल ISDN_P_NT_S0:
	हाल ISDN_P_TE_S0:
	हाल ISDN_P_NT_E1:
	हाल ISDN_P_TE_E1:
		ग_लिखो_lock_bh(&ch->st->l1sock.lock);
		sk_del_node_init(&msk->sk);
		ग_लिखो_unlock_bh(&ch->st->l1sock.lock);
		ch->st->dev->D.ctrl(&ch->st->dev->D, CLOSE_CHANNEL, शून्य);
		अवरोध;
	हाल ISDN_P_LAPD_TE:
		pch = get_channel4id(ch->st, ch->nr);
		अगर (pch) अणु
			mutex_lock(&ch->st->lmutex);
			list_del(&pch->list);
			mutex_unlock(&ch->st->lmutex);
			pch->ctrl(pch, CLOSE_CHANNEL, शून्य);
			pch = ch->st->dev->teimgr;
			pch->ctrl(pch, CLOSE_CHANNEL, शून्य);
		पूर्ण अन्यथा
			prपूर्णांकk(KERN_WARNING "%s: no l2 channel\n",
			       __func__);
		अवरोध;
	हाल ISDN_P_LAPD_NT:
		pch = ch->st->dev->teimgr;
		अगर (pch) अणु
			pch->ctrl(pch, CLOSE_CHANNEL, शून्य);
		पूर्ण अन्यथा
			prपूर्णांकk(KERN_WARNING "%s: no l2 channel\n",
			       __func__);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस;
पूर्ण

व्योम
delete_stack(काष्ठा mISDNdevice *dev)
अणु
	काष्ठा mISDNstack	*st = dev->D.st;
	DECLARE_COMPLETION_ONSTACK(करोne);

	अगर (*debug & DEBUG_CORE_FUNC)
		prपूर्णांकk(KERN_DEBUG "%s: st(%s)\n", __func__,
		       dev_name(&st->dev->dev));
	अगर (dev->teimgr)
		delete_teimanager(dev->teimgr);
	अगर (st->thपढ़ो) अणु
		अगर (st->notअगरy) अणु
			prपूर्णांकk(KERN_WARNING "%s: notifier in use\n",
			       __func__);
			complete(st->notअगरy);
		पूर्ण
		st->notअगरy = &करोne;
		test_and_set_bit(mISDN_STACK_ABORT, &st->status);
		test_and_set_bit(mISDN_STACK_WAKEUP, &st->status);
		wake_up_पूर्णांकerruptible(&st->workq);
		रुको_क्रम_completion(&करोne);
	पूर्ण
	अगर (!list_empty(&st->layer2))
		prपूर्णांकk(KERN_WARNING "%s: layer2 list not empty\n",
		       __func__);
	अगर (!hlist_empty(&st->l1sock.head))
		prपूर्णांकk(KERN_WARNING "%s: layer1 list not empty\n",
		       __func__);
	kमुक्त(st);
पूर्ण

व्योम
mISDN_initstack(u_पूर्णांक *dp)
अणु
	debug = dp;
पूर्ण
