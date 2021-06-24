<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * net/sched/em_nbyte.c	N-Byte ematch
 *
 * Authors:	Thomas Graf <tgraf@suug.ch>
 */

#समावेश <linux/gfp.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/skbuff.h>
#समावेश <linux/tc_ematch/tc_em_nbyte.h>
#समावेश <net/pkt_cls.h>

काष्ठा nbyte_data अणु
	काष्ठा tcf_em_nbyte	hdr;
	अक्षर			pattern[];
पूर्ण;

अटल पूर्णांक em_nbyte_change(काष्ठा net *net, व्योम *data, पूर्णांक data_len,
			   काष्ठा tcf_ematch *em)
अणु
	काष्ठा tcf_em_nbyte *nbyte = data;

	अगर (data_len < माप(*nbyte) ||
	    data_len < (माप(*nbyte) + nbyte->len))
		वापस -EINVAL;

	em->datalen = माप(*nbyte) + nbyte->len;
	em->data = (अचिन्हित दीर्घ)kmemdup(data, em->datalen, GFP_KERNEL);
	अगर (em->data == 0UL)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल पूर्णांक em_nbyte_match(काष्ठा sk_buff *skb, काष्ठा tcf_ematch *em,
			  काष्ठा tcf_pkt_info *info)
अणु
	काष्ठा nbyte_data *nbyte = (काष्ठा nbyte_data *) em->data;
	अचिन्हित अक्षर *ptr = tcf_get_base_ptr(skb, nbyte->hdr.layer);

	ptr += nbyte->hdr.off;

	अगर (!tcf_valid_offset(skb, ptr, nbyte->hdr.len))
		वापस 0;

	वापस !स_भेद(ptr, nbyte->pattern, nbyte->hdr.len);
पूर्ण

अटल काष्ठा tcf_ematch_ops em_nbyte_ops = अणु
	.kind	  = TCF_EM_NBYTE,
	.change	  = em_nbyte_change,
	.match	  = em_nbyte_match,
	.owner	  = THIS_MODULE,
	.link	  = LIST_HEAD_INIT(em_nbyte_ops.link)
पूर्ण;

अटल पूर्णांक __init init_em_nbyte(व्योम)
अणु
	वापस tcf_em_रेजिस्टर(&em_nbyte_ops);
पूर्ण

अटल व्योम __निकास निकास_em_nbyte(व्योम)
अणु
	tcf_em_unरेजिस्टर(&em_nbyte_ops);
पूर्ण

MODULE_LICENSE("GPL");

module_init(init_em_nbyte);
module_निकास(निकास_em_nbyte);

MODULE_ALIAS_TCF_EMATCH(TCF_EM_NBYTE);
