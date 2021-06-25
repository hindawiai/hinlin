<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* net/aपंचांग/संकेतing.c - ATM संकेतing */

/* Written 1995-2000 by Werner Almesberger, EPFL LRC/ICA */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ":%s: " fmt, __func__

#समावेश <linux/त्रुटिसं.स>	/* error codes */
#समावेश <linux/kernel.h>	/* prपूर्णांकk */
#समावेश <linux/skbuff.h>
#समावेश <linux/रुको.h>
#समावेश <linux/sched.h>	/* jअगरfies and HZ */
#समावेश <linux/aपंचांग.h>		/* ATM stuff */
#समावेश <linux/aपंचांगsap.h>
#समावेश <linux/aपंचांगsvc.h>
#समावेश <linux/aपंचांगdev.h>
#समावेश <linux/bitops.h>
#समावेश <linux/slab.h>

#समावेश "resources.h"
#समावेश "signaling.h"

काष्ठा aपंचांग_vcc *sigd = शून्य;

अटल व्योम sigd_put_skb(काष्ठा sk_buff *skb)
अणु
	अगर (!sigd) अणु
		pr_debug("atmsvc: no signaling daemon\n");
		kमुक्त_skb(skb);
		वापस;
	पूर्ण
	aपंचांग_क्रमce_अक्षरge(sigd, skb->truesize);
	skb_queue_tail(&sk_aपंचांग(sigd)->sk_receive_queue, skb);
	sk_aपंचांग(sigd)->sk_data_पढ़ोy(sk_aपंचांग(sigd));
पूर्ण

अटल व्योम modअगरy_qos(काष्ठा aपंचांग_vcc *vcc, काष्ठा aपंचांगsvc_msg *msg)
अणु
	काष्ठा sk_buff *skb;

	अगर (test_bit(ATM_VF_RELEASED, &vcc->flags) ||
	    !test_bit(ATM_VF_READY, &vcc->flags))
		वापस;
	msg->type = as_error;
	अगर (!vcc->dev->ops->change_qos)
		msg->reply = -EOPNOTSUPP;
	अन्यथा अणु
		/* should lock VCC */
		msg->reply = vcc->dev->ops->change_qos(vcc, &msg->qos,
						       msg->reply);
		अगर (!msg->reply)
			msg->type = as_okay;
	पूर्ण
	/*
	 * Should probably just turn around the old skb. But then, the buffer
	 * space accounting needs to follow the change too. Maybe later.
	 */
	जबतक (!(skb = alloc_skb(माप(काष्ठा aपंचांगsvc_msg), GFP_KERNEL)))
		schedule();
	*(काष्ठा aपंचांगsvc_msg *)skb_put(skb, माप(काष्ठा aपंचांगsvc_msg)) = *msg;
	sigd_put_skb(skb);
पूर्ण

अटल पूर्णांक sigd_send(काष्ठा aपंचांग_vcc *vcc, काष्ठा sk_buff *skb)
अणु
	काष्ठा aपंचांगsvc_msg *msg;
	काष्ठा aपंचांग_vcc *session_vcc;
	काष्ठा sock *sk;

	msg = (काष्ठा aपंचांगsvc_msg *) skb->data;
	WARN_ON(refcount_sub_and_test(skb->truesize, &sk_aपंचांग(vcc)->sk_wmem_alloc));
	vcc = *(काष्ठा aपंचांग_vcc **) &msg->vcc;
	pr_debug("%d (0x%lx)\n", (पूर्णांक)msg->type, (अचिन्हित दीर्घ)vcc);
	sk = sk_aपंचांग(vcc);

	चयन (msg->type) अणु
	हाल as_okay:
		sk->sk_err = -msg->reply;
		clear_bit(ATM_VF_WAITING, &vcc->flags);
		अगर (!*vcc->local.sas_addr.prv && !*vcc->local.sas_addr.pub) अणु
			vcc->local.sas_family = AF_ATMSVC;
			स_नकल(vcc->local.sas_addr.prv,
			       msg->local.sas_addr.prv, ATM_ESA_LEN);
			स_नकल(vcc->local.sas_addr.pub,
			       msg->local.sas_addr.pub, ATM_E164_LEN + 1);
		पूर्ण
		session_vcc = vcc->session ? vcc->session : vcc;
		अगर (session_vcc->vpi || session_vcc->vci)
			अवरोध;
		session_vcc->itf = msg->pvc.sap_addr.itf;
		session_vcc->vpi = msg->pvc.sap_addr.vpi;
		session_vcc->vci = msg->pvc.sap_addr.vci;
		अगर (session_vcc->vpi || session_vcc->vci)
			session_vcc->qos = msg->qos;
		अवरोध;
	हाल as_error:
		clear_bit(ATM_VF_REGIS, &vcc->flags);
		clear_bit(ATM_VF_READY, &vcc->flags);
		sk->sk_err = -msg->reply;
		clear_bit(ATM_VF_WAITING, &vcc->flags);
		अवरोध;
	हाल as_indicate:
		vcc = *(काष्ठा aपंचांग_vcc **)&msg->listen_vcc;
		sk = sk_aपंचांग(vcc);
		pr_debug("as_indicate!!!\n");
		lock_sock(sk);
		अगर (sk_acceptq_is_full(sk)) अणु
			sigd_enq(शून्य, as_reject, vcc, शून्य, शून्य);
			dev_kमुक्त_skb(skb);
			जाओ as_indicate_complete;
		पूर्ण
		sk_acceptq_added(sk);
		skb_queue_tail(&sk->sk_receive_queue, skb);
		pr_debug("waking sk_sleep(sk) 0x%p\n", sk_sleep(sk));
		sk->sk_state_change(sk);
as_indicate_complete:
		release_sock(sk);
		वापस 0;
	हाल as_बंद:
		set_bit(ATM_VF_RELEASED, &vcc->flags);
		vcc_release_async(vcc, msg->reply);
		जाओ out;
	हाल as_modअगरy:
		modअगरy_qos(vcc, msg);
		अवरोध;
	हाल as_addparty:
	हाल as_dropparty:
		sk->sk_err_soft = -msg->reply;
					/* < 0 failure, otherwise ep_ref */
		clear_bit(ATM_VF_WAITING, &vcc->flags);
		अवरोध;
	शेष:
		pr_alert("bad message type %d\n", (पूर्णांक)msg->type);
		वापस -EINVAL;
	पूर्ण
	sk->sk_state_change(sk);
out:
	dev_kमुक्त_skb(skb);
	वापस 0;
पूर्ण

व्योम sigd_enq2(काष्ठा aपंचांग_vcc *vcc, क्रमागत aपंचांगsvc_msg_type type,
	       काष्ठा aपंचांग_vcc *listen_vcc, स्थिर काष्ठा sockaddr_aपंचांगpvc *pvc,
	       स्थिर काष्ठा sockaddr_aपंचांगsvc *svc, स्थिर काष्ठा aपंचांग_qos *qos,
	       पूर्णांक reply)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा aपंचांगsvc_msg *msg;
	अटल अचिन्हित पूर्णांक session = 0;

	pr_debug("%d (0x%p)\n", (पूर्णांक)type, vcc);
	जबतक (!(skb = alloc_skb(माप(काष्ठा aपंचांगsvc_msg), GFP_KERNEL)))
		schedule();
	msg = skb_put_zero(skb, माप(काष्ठा aपंचांगsvc_msg));
	msg->type = type;
	*(काष्ठा aपंचांग_vcc **) &msg->vcc = vcc;
	*(काष्ठा aपंचांग_vcc **) &msg->listen_vcc = listen_vcc;
	msg->reply = reply;
	अगर (qos)
		msg->qos = *qos;
	अगर (vcc)
		msg->sap = vcc->sap;
	अगर (svc)
		msg->svc = *svc;
	अगर (vcc)
		msg->local = vcc->local;
	अगर (pvc)
		msg->pvc = *pvc;
	अगर (vcc) अणु
		अगर (type == as_connect && test_bit(ATM_VF_SESSION, &vcc->flags))
			msg->session = ++session;
			/* every new pmp connect माला_लो the next session number */
	पूर्ण
	sigd_put_skb(skb);
	अगर (vcc)
		set_bit(ATM_VF_REGIS, &vcc->flags);
पूर्ण

व्योम sigd_enq(काष्ठा aपंचांग_vcc *vcc, क्रमागत aपंचांगsvc_msg_type type,
	      काष्ठा aपंचांग_vcc *listen_vcc, स्थिर काष्ठा sockaddr_aपंचांगpvc *pvc,
	      स्थिर काष्ठा sockaddr_aपंचांगsvc *svc)
अणु
	sigd_enq2(vcc, type, listen_vcc, pvc, svc, vcc ? &vcc->qos : शून्य, 0);
	/* other ISP applications may use "reply" */
पूर्ण

अटल व्योम purge_vcc(काष्ठा aपंचांग_vcc *vcc)
अणु
	अगर (sk_aपंचांग(vcc)->sk_family == PF_ATMSVC &&
	    !test_bit(ATM_VF_META, &vcc->flags)) अणु
		set_bit(ATM_VF_RELEASED, &vcc->flags);
		clear_bit(ATM_VF_REGIS, &vcc->flags);
		vcc_release_async(vcc, -EUNATCH);
	पूर्ण
पूर्ण

अटल व्योम sigd_बंद(काष्ठा aपंचांग_vcc *vcc)
अणु
	काष्ठा sock *s;
	पूर्णांक i;

	pr_debug("\n");
	sigd = शून्य;
	अगर (skb_peek(&sk_aपंचांग(vcc)->sk_receive_queue))
		pr_err("closing with requests pending\n");
	skb_queue_purge(&sk_aपंचांग(vcc)->sk_receive_queue);

	पढ़ो_lock(&vcc_sklist_lock);
	क्रम (i = 0; i < VCC_HTABLE_SIZE; ++i) अणु
		काष्ठा hlist_head *head = &vcc_hash[i];

		sk_क्रम_each(s, head) अणु
			vcc = aपंचांग_sk(s);

			purge_vcc(vcc);
		पूर्ण
	पूर्ण
	पढ़ो_unlock(&vcc_sklist_lock);
पूर्ण

अटल स्थिर काष्ठा aपंचांगdev_ops sigd_dev_ops = अणु
	.बंद = sigd_बंद,
	.send =	sigd_send
पूर्ण;

अटल काष्ठा aपंचांग_dev sigd_dev = अणु
	.ops =		&sigd_dev_ops,
	.type =		"sig",
	.number =	999,
	.lock =		__SPIN_LOCK_UNLOCKED(sigd_dev.lock)
पूर्ण;

पूर्णांक sigd_attach(काष्ठा aपंचांग_vcc *vcc)
अणु
	अगर (sigd)
		वापस -EADDRINUSE;
	pr_debug("\n");
	sigd = vcc;
	vcc->dev = &sigd_dev;
	vcc_insert_socket(sk_aपंचांग(vcc));
	set_bit(ATM_VF_META, &vcc->flags);
	set_bit(ATM_VF_READY, &vcc->flags);
	वापस 0;
पूर्ण
