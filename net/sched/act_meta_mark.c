<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * net/sched/act_meta_mark.c IFE skb->mark metadata module
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

अटल पूर्णांक skbmark_encode(काष्ठा sk_buff *skb, व्योम *skbdata,
			  काष्ठा tcf_meta_info *e)
अणु
	u32 अगरemark = skb->mark;

	वापस अगरe_encode_meta_u32(अगरemark, skbdata, e);
पूर्ण

अटल पूर्णांक skbmark_decode(काष्ठा sk_buff *skb, व्योम *data, u16 len)
अणु
	u32 अगरemark = *(u32 *)data;

	skb->mark = ntohl(अगरemark);
	वापस 0;
पूर्ण

अटल पूर्णांक skbmark_check(काष्ठा sk_buff *skb, काष्ठा tcf_meta_info *e)
अणु
	वापस अगरe_check_meta_u32(skb->mark, e);
पूर्ण

अटल काष्ठा tcf_meta_ops अगरe_skbmark_ops = अणु
	.metaid = IFE_META_SKBMARK,
	.metatype = NLA_U32,
	.name = "skbmark",
	.synopsis = "skb mark 32 bit metadata",
	.check_presence = skbmark_check,
	.encode = skbmark_encode,
	.decode = skbmark_decode,
	.get = अगरe_get_meta_u32,
	.alloc = अगरe_alloc_meta_u32,
	.release = अगरe_release_meta_gen,
	.validate = अगरe_validate_meta_u32,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init अगरemark_init_module(व्योम)
अणु
	वापस रेजिस्टर_अगरe_op(&अगरe_skbmark_ops);
पूर्ण

अटल व्योम __निकास अगरemark_cleanup_module(व्योम)
अणु
	unरेजिस्टर_अगरe_op(&अगरe_skbmark_ops);
पूर्ण

module_init(अगरemark_init_module);
module_निकास(अगरemark_cleanup_module);

MODULE_AUTHOR("Jamal Hadi Salim(2015)");
MODULE_DESCRIPTION("Inter-FE skb mark metadata module");
MODULE_LICENSE("GPL");
MODULE_ALIAS_IFE_META("skbmark");
