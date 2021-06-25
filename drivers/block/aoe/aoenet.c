<शैली गुरु>
/* Copyright (c) 2013 Coraid, Inc.  See COPYING क्रम GPL terms. */
/*
 * aoenet.c
 * Ethernet portion of AoE driver
 */

#समावेश <linux/gfp.h>
#समावेश <linux/hdreg.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/moduleparam.h>
#समावेश <net/net_namespace.h>
#समावेश <यंत्र/unaligned.h>
#समावेश "aoe.h"

#घोषणा NECODES 5

अटल अक्षर *aoe_errlist[] =
अणु
	"no such error",
	"unrecognized command code",
	"bad argument parameter",
	"device unavailable",
	"config string present",
	"unsupported version"
पूर्ण;

क्रमागत अणु
	IFLISTSZ = 1024,
पूर्ण;

अटल अक्षर aoe_अगरlist[IFLISTSZ];
module_param_string(aoe_अगरlist, aoe_अगरlist, IFLISTSZ, 0600);
MODULE_PARM_DESC(aoe_अगरlist, "aoe_iflist=dev1[,dev2...]");

अटल रुको_queue_head_t txwq;
अटल काष्ठा ktstate kts;

#अगर_अघोषित MODULE
अटल पूर्णांक __init aoe_अगरlist_setup(अक्षर *str)
अणु
	म_नकलन(aoe_अगरlist, str, IFLISTSZ);
	aoe_अगरlist[IFLISTSZ - 1] = '\0';
	वापस 1;
पूर्ण

__setup("aoe_iflist=", aoe_अगरlist_setup);
#पूर्ण_अगर

अटल spinlock_t txlock;
अटल काष्ठा sk_buff_head skbtxq;

/* enters with txlock held */
अटल पूर्णांक
tx(पूर्णांक id) __must_hold(&txlock)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा net_device *अगरp;

	जबतक ((skb = skb_dequeue(&skbtxq))) अणु
		spin_unlock_irq(&txlock);
		अगरp = skb->dev;
		अगर (dev_queue_xmit(skb) == NET_XMIT_DROP && net_ratelimit())
			pr_warn("aoe: packet could not be sent on %s.  %s\n",
				अगरp ? अगरp->name : "netif",
				"consider increasing tx_queue_len");
		spin_lock_irq(&txlock);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक
is_aoe_netअगर(काष्ठा net_device *अगरp)
अणु
	रेजिस्टर अक्षर *p, *q;
	रेजिस्टर पूर्णांक len;

	अगर (aoe_अगरlist[0] == '\0')
		वापस 1;

	p = aoe_अगरlist + म_अखोज(aoe_अगरlist, WHITESPACE);
	क्रम (; *p; p = q + म_अखोज(q, WHITESPACE)) अणु
		q = p + म_खोज(p, WHITESPACE);
		अगर (q != p)
			len = q - p;
		अन्यथा
			len = म_माप(p); /* last token in aoe_अगरlist */

		अगर (म_माप(अगरp->name) == len && !म_भेदन(अगरp->name, p, len))
			वापस 1;
		अगर (q == p)
			अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक
set_aoe_अगरlist(स्थिर अक्षर __user *user_str, माप_प्रकार size)
अणु
	अगर (size >= IFLISTSZ)
		वापस -EINVAL;

	अगर (copy_from_user(aoe_अगरlist, user_str, size)) अणु
		prपूर्णांकk(KERN_INFO "aoe: copy from user failed\n");
		वापस -EFAULT;
	पूर्ण
	aoe_अगरlist[size] = 0x00;
	वापस 0;
पूर्ण

व्योम
aoenet_xmit(काष्ठा sk_buff_head *queue)
अणु
	काष्ठा sk_buff *skb, *पंचांगp;
	uदीर्घ flags;

	skb_queue_walk_safe(queue, skb, पंचांगp) अणु
		__skb_unlink(skb, queue);
		spin_lock_irqsave(&txlock, flags);
		skb_queue_tail(&skbtxq, skb);
		spin_unlock_irqrestore(&txlock, flags);
		wake_up(&txwq);
	पूर्ण
पूर्ण

/*
 * (1) len करोesn't include the header by शेष.  I want this.
 */
अटल पूर्णांक
aoenet_rcv(काष्ठा sk_buff *skb, काष्ठा net_device *अगरp, काष्ठा packet_type *pt, काष्ठा net_device *orig_dev)
अणु
	काष्ठा aoe_hdr *h;
	काष्ठा aoe_atahdr *ah;
	u32 n;
	पूर्णांक sn;

	अगर (dev_net(अगरp) != &init_net)
		जाओ निकास;

	skb = skb_share_check(skb, GFP_ATOMIC);
	अगर (skb == शून्य)
		वापस 0;
	अगर (!is_aoe_netअगर(अगरp))
		जाओ निकास;
	skb_push(skb, ETH_HLEN);	/* (1) */
	sn = माप(*h) + माप(*ah);
	अगर (skb->len >= sn) अणु
		sn -= skb_headlen(skb);
		अगर (sn > 0 && !__pskb_pull_tail(skb, sn))
			जाओ निकास;
	पूर्ण
	h = (काष्ठा aoe_hdr *) skb->data;
	n = get_unaligned_be32(&h->tag);
	अगर ((h->verfl & AOEFL_RSP) == 0 || (n & 1<<31))
		जाओ निकास;

	अगर (h->verfl & AOEFL_ERR) अणु
		n = h->err;
		अगर (n > NECODES)
			n = 0;
		अगर (net_ratelimit())
			prपूर्णांकk(KERN_ERR
				"%s%d.%d@%s; ecode=%d '%s'\n",
				"aoe: error packet from ",
				get_unaligned_be16(&h->major),
				h->minor, skb->dev->name,
				h->err, aoe_errlist[n]);
		जाओ निकास;
	पूर्ण

	चयन (h->cmd) अणु
	हाल AOECMD_ATA:
		/* ata_rsp may keep skb क्रम later processing or give it back */
		skb = aoecmd_ata_rsp(skb);
		अवरोध;
	हाल AOECMD_CFG:
		aoecmd_cfg_rsp(skb);
		अवरोध;
	शेष:
		अगर (h->cmd >= AOECMD_VEND_MIN)
			अवरोध;	/* करोn't complain about venकरोr commands */
		pr_info("aoe: unknown AoE command type 0x%02x\n", h->cmd);
		अवरोध;
	पूर्ण

	अगर (!skb)
		वापस 0;
निकास:
	dev_kमुक्त_skb(skb);
	वापस 0;
पूर्ण

अटल काष्ठा packet_type aoe_pt __पढ़ो_mostly = अणु
	.type = __स्थिरant_htons(ETH_P_AOE),
	.func = aoenet_rcv,
पूर्ण;

पूर्णांक __init
aoenet_init(व्योम)
अणु
	skb_queue_head_init(&skbtxq);
	init_रुकोqueue_head(&txwq);
	spin_lock_init(&txlock);
	kts.lock = &txlock;
	kts.fn = tx;
	kts.रुकोq = &txwq;
	kts.id = 0;
	snम_लिखो(kts.name, माप(kts.name), "aoe_tx%d", kts.id);
	अगर (aoe_ktstart(&kts))
		वापस -EAGAIN;
	dev_add_pack(&aoe_pt);
	वापस 0;
पूर्ण

व्योम
aoenet_निकास(व्योम)
अणु
	aoe_ktstop(&kts);
	skb_queue_purge(&skbtxq);
	dev_हटाओ_pack(&aoe_pt);
पूर्ण

