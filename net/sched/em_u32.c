<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * net/sched/em_u32.c	U32 Ematch
 *
 * Authors:	Thomas Graf <tgraf@suug.ch>
 *		Alexey Kuznetsov, <kuznet@ms2.inr.ac.ru>
 *
 * Based on net/sched/cls_u32.c
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/skbuff.h>
#समावेश <net/pkt_cls.h>

अटल पूर्णांक em_u32_match(काष्ठा sk_buff *skb, काष्ठा tcf_ematch *em,
			काष्ठा tcf_pkt_info *info)
अणु
	काष्ठा tc_u32_key *key = (काष्ठा tc_u32_key *) em->data;
	स्थिर अचिन्हित अक्षर *ptr = skb_network_header(skb);

	अगर (info) अणु
		अगर (info->ptr)
			ptr = info->ptr;
		ptr += (info->nexthdr & key->offmask);
	पूर्ण

	ptr += key->off;

	अगर (!tcf_valid_offset(skb, ptr, माप(u32)))
		वापस 0;

	वापस !(((*(__be32 *) ptr)  ^ key->val) & key->mask);
पूर्ण

अटल काष्ठा tcf_ematch_ops em_u32_ops = अणु
	.kind	  = TCF_EM_U32,
	.datalen  = माप(काष्ठा tc_u32_key),
	.match	  = em_u32_match,
	.owner	  = THIS_MODULE,
	.link	  = LIST_HEAD_INIT(em_u32_ops.link)
पूर्ण;

अटल पूर्णांक __init init_em_u32(व्योम)
अणु
	वापस tcf_em_रेजिस्टर(&em_u32_ops);
पूर्ण

अटल व्योम __निकास निकास_em_u32(व्योम)
अणु
	tcf_em_unरेजिस्टर(&em_u32_ops);
पूर्ण

MODULE_LICENSE("GPL");

module_init(init_em_u32);
module_निकास(निकास_em_u32);

MODULE_ALIAS_TCF_EMATCH(TCF_EM_U32);
