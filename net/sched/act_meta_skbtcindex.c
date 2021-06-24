<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * net/sched/act_meta_tc_index.c IFE skb->tc_index metadata module
 *
 * copyright Jamal Hadi Salim (2016)
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

अटल पूर्णांक skbtcindex_encode(काष्ठा sk_buff *skb, व्योम *skbdata,
			     काष्ठा tcf_meta_info *e)
अणु
	u32 अगरetc_index = skb->tc_index;

	वापस अगरe_encode_meta_u16(अगरetc_index, skbdata, e);
पूर्ण

अटल पूर्णांक skbtcindex_decode(काष्ठा sk_buff *skb, व्योम *data, u16 len)
अणु
	u16 अगरetc_index = *(u16 *)data;

	skb->tc_index = ntohs(अगरetc_index);
	वापस 0;
पूर्ण

अटल पूर्णांक skbtcindex_check(काष्ठा sk_buff *skb, काष्ठा tcf_meta_info *e)
अणु
	वापस अगरe_check_meta_u16(skb->tc_index, e);
पूर्ण

अटल काष्ठा tcf_meta_ops अगरe_skbtcindex_ops = अणु
	.metaid = IFE_META_TCINDEX,
	.metatype = NLA_U16,
	.name = "tc_index",
	.synopsis = "skb tc_index 16 bit metadata",
	.check_presence = skbtcindex_check,
	.encode = skbtcindex_encode,
	.decode = skbtcindex_decode,
	.get = अगरe_get_meta_u16,
	.alloc = अगरe_alloc_meta_u16,
	.release = अगरe_release_meta_gen,
	.validate = अगरe_validate_meta_u16,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init अगरetc_index_init_module(व्योम)
अणु
	वापस रेजिस्टर_अगरe_op(&अगरe_skbtcindex_ops);
पूर्ण

अटल व्योम __निकास अगरetc_index_cleanup_module(व्योम)
अणु
	unरेजिस्टर_अगरe_op(&अगरe_skbtcindex_ops);
पूर्ण

module_init(अगरetc_index_init_module);
module_निकास(अगरetc_index_cleanup_module);

MODULE_AUTHOR("Jamal Hadi Salim(2016)");
MODULE_DESCRIPTION("Inter-FE skb tc_index metadata module");
MODULE_LICENSE("GPL");
MODULE_ALIAS_IFE_META("tcindex");
