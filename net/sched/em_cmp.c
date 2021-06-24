<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * net/sched/em_cmp.c	Simple packet data comparison ematch
 *
 * Authors:	Thomas Graf <tgraf@suug.ch>
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/tc_ematch/tc_em_cmp.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <net/pkt_cls.h>

अटल अंतरभूत पूर्णांक cmp_needs_transक्रमmation(काष्ठा tcf_em_cmp *cmp)
अणु
	वापस unlikely(cmp->flags & TCF_EM_CMP_TRANS);
पूर्ण

अटल पूर्णांक em_cmp_match(काष्ठा sk_buff *skb, काष्ठा tcf_ematch *em,
			काष्ठा tcf_pkt_info *info)
अणु
	काष्ठा tcf_em_cmp *cmp = (काष्ठा tcf_em_cmp *) em->data;
	अचिन्हित अक्षर *ptr = tcf_get_base_ptr(skb, cmp->layer) + cmp->off;
	u32 val = 0;

	अगर (!tcf_valid_offset(skb, ptr, cmp->align))
		वापस 0;

	चयन (cmp->align) अणु
	हाल TCF_EM_ALIGN_U8:
		val = *ptr;
		अवरोध;

	हाल TCF_EM_ALIGN_U16:
		val = get_unaligned_be16(ptr);

		अगर (cmp_needs_transक्रमmation(cmp))
			val = be16_to_cpu(val);
		अवरोध;

	हाल TCF_EM_ALIGN_U32:
		/* Worth checking boundaries? The branching seems
		 * to get worse. Visit again.
		 */
		val = get_unaligned_be32(ptr);

		अगर (cmp_needs_transक्रमmation(cmp))
			val = be32_to_cpu(val);
		अवरोध;

	शेष:
		वापस 0;
	पूर्ण

	अगर (cmp->mask)
		val &= cmp->mask;

	चयन (cmp->opnd) अणु
	हाल TCF_EM_OPND_EQ:
		वापस val == cmp->val;
	हाल TCF_EM_OPND_LT:
		वापस val < cmp->val;
	हाल TCF_EM_OPND_GT:
		वापस val > cmp->val;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा tcf_ematch_ops em_cmp_ops = अणु
	.kind	  = TCF_EM_CMP,
	.datalen  = माप(काष्ठा tcf_em_cmp),
	.match	  = em_cmp_match,
	.owner	  = THIS_MODULE,
	.link	  = LIST_HEAD_INIT(em_cmp_ops.link)
पूर्ण;

अटल पूर्णांक __init init_em_cmp(व्योम)
अणु
	वापस tcf_em_रेजिस्टर(&em_cmp_ops);
पूर्ण

अटल व्योम __निकास निकास_em_cmp(व्योम)
अणु
	tcf_em_unरेजिस्टर(&em_cmp_ops);
पूर्ण

MODULE_LICENSE("GPL");

module_init(init_em_cmp);
module_निकास(निकास_em_cmp);

MODULE_ALIAS_TCF_EMATCH(TCF_EM_CMP);
