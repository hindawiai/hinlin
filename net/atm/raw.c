<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* net/aपंचांग/raw.c - Raw AAL0 and AAL5 transports */

/* Written 1995-2000 by Werner Almesberger, EPFL LRC/ICA */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ":%s: " fmt, __func__

#समावेश <linux/module.h>
#समावेश <linux/aपंचांगdev.h>
#समावेश <linux/capability.h>
#समावेश <linux/kernel.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>

#समावेश "common.h"
#समावेश "protocols.h"

/*
 * SKB == शून्य indicates that the link is being बंदd
 */

अटल व्योम aपंचांग_push_raw(काष्ठा aपंचांग_vcc *vcc, काष्ठा sk_buff *skb)
अणु
	अगर (skb) अणु
		काष्ठा sock *sk = sk_aपंचांग(vcc);

		skb_queue_tail(&sk->sk_receive_queue, skb);
		sk->sk_data_पढ़ोy(sk);
	पूर्ण
पूर्ण

अटल व्योम aपंचांग_pop_raw(काष्ठा aपंचांग_vcc *vcc, काष्ठा sk_buff *skb)
अणु
	काष्ठा sock *sk = sk_aपंचांग(vcc);

	pr_debug("(%d) %d -= %d\n",
		 vcc->vci, sk_wmem_alloc_get(sk), ATM_SKB(skb)->acct_truesize);
	WARN_ON(refcount_sub_and_test(ATM_SKB(skb)->acct_truesize, &sk->sk_wmem_alloc));
	dev_kमुक्त_skb_any(skb);
	sk->sk_ग_लिखो_space(sk);
पूर्ण

अटल पूर्णांक aपंचांग_send_aal0(काष्ठा aपंचांग_vcc *vcc, काष्ठा sk_buff *skb)
अणु
	/*
	 * Note that अगर vpi/vci are _ANY or _UNSPEC the below will
	 * still work
	 */
	अगर (!capable(CAP_NET_ADMIN) &&
	    (((u32 *)skb->data)[0] & (ATM_HDR_VPI_MASK | ATM_HDR_VCI_MASK)) !=
	    ((vcc->vpi << ATM_HDR_VPI_SHIFT) |
	     (vcc->vci << ATM_HDR_VCI_SHIFT))) अणु
		kमुक्त_skb(skb);
		वापस -EADDRNOTAVAIL;
	पूर्ण
	अगर (vcc->dev->ops->send_bh)
		वापस vcc->dev->ops->send_bh(vcc, skb);
	वापस vcc->dev->ops->send(vcc, skb);
पूर्ण

पूर्णांक aपंचांग_init_aal0(काष्ठा aपंचांग_vcc *vcc)
अणु
	vcc->push = aपंचांग_push_raw;
	vcc->pop = aपंचांग_pop_raw;
	vcc->push_oam = शून्य;
	vcc->send = aपंचांग_send_aal0;
	वापस 0;
पूर्ण

पूर्णांक aपंचांग_init_aal34(काष्ठा aपंचांग_vcc *vcc)
अणु
	vcc->push = aपंचांग_push_raw;
	vcc->pop = aपंचांग_pop_raw;
	vcc->push_oam = शून्य;
	अगर (vcc->dev->ops->send_bh)
		vcc->send = vcc->dev->ops->send_bh;
	अन्यथा
		vcc->send = vcc->dev->ops->send;
	वापस 0;
पूर्ण

पूर्णांक aपंचांग_init_aal5(काष्ठा aपंचांग_vcc *vcc)
अणु
	vcc->push = aपंचांग_push_raw;
	vcc->pop = aपंचांग_pop_raw;
	vcc->push_oam = शून्य;
	अगर (vcc->dev->ops->send_bh)
		vcc->send = vcc->dev->ops->send_bh;
	अन्यथा
		vcc->send = vcc->dev->ops->send;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(aपंचांग_init_aal5);
