<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * net/sched/act_meta_prio.c IFE skb->priority metadata module
 *
 * copyright Jamal Hadi Salim (2015)
*/

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/skbuff.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <net/netlink.h>
#समावेश <net/pkt_sched.h>
#समावेश <uapi/linux/tc_act/tc_अगरe.h>
#समावेश <net/tc_act/tc_अगरe.h>

अटल पूर्णांक skbprio_check(काष्ठा sk_buff *skb, काष्ठा tcf_meta_info *e)
अणु
	वापस अगरe_check_meta_u32(skb->priority, e);
पूर्ण

अटल पूर्णांक skbprio_encode(काष्ठा sk_buff *skb, व्योम *skbdata,
			  काष्ठा tcf_meta_info *e)
अणु
	u32 अगरeprio = skb->priority; /* aव्योम having to cast skb->priority*/

	वापस अगरe_encode_meta_u32(अगरeprio, skbdata, e);
पूर्ण

अटल पूर्णांक skbprio_decode(काष्ठा sk_buff *skb, व्योम *data, u16 len)
अणु
	u32 अगरeprio = *(u32 *)data;

	skb->priority = ntohl(अगरeprio);
	वापस 0;
पूर्ण

अटल काष्ठा tcf_meta_ops अगरe_prio_ops = अणु
	.metaid = IFE_META_PRIO,
	.metatype = NLA_U32,
	.name = "skbprio",
	.synopsis = "skb prio metadata",
	.check_presence = skbprio_check,
	.encode = skbprio_encode,
	.decode = skbprio_decode,
	.get = अगरe_get_meta_u32,
	.alloc = अगरe_alloc_meta_u32,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init अगरeprio_init_module(व्योम)
अणु
	वापस रेजिस्टर_अगरe_op(&अगरe_prio_ops);
पूर्ण

अटल व्योम __निकास अगरeprio_cleanup_module(व्योम)
अणु
	unरेजिस्टर_अगरe_op(&अगरe_prio_ops);
पूर्ण

module_init(अगरeprio_init_module);
module_निकास(अगरeprio_cleanup_module);

MODULE_AUTHOR("Jamal Hadi Salim(2015)");
MODULE_DESCRIPTION("Inter-FE skb prio metadata action");
MODULE_LICENSE("GPL");
MODULE_ALIAS_IFE_META("skbprio");
