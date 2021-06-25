<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *	xt_u32 - kernel module to match u32 packet content
 *
 *	Original author: Don Cohen <करोn@isis.cs3-inc.com>
 *	(C) CC Computer Consultants GmbH, 2007
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/types.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter/xt_u32.h>

अटल bool u32_match_it(स्थिर काष्ठा xt_u32 *data,
			 स्थिर काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा xt_u32_test *ct;
	अचिन्हित पूर्णांक testind;
	अचिन्हित पूर्णांक nnums;
	अचिन्हित पूर्णांक nvals;
	अचिन्हित पूर्णांक i;
	__be32 n;
	u_पूर्णांक32_t pos;
	u_पूर्णांक32_t val;
	u_पूर्णांक32_t at;

	/*
	 * Small example: "0 >> 28 == 4 && 8 & 0xFF0000 >> 16 = 6, 17"
	 * (=IPv4 and (TCP or UDP)). Outer loop runs over the "&&" opeअक्रमs.
	 */
	क्रम (testind = 0; testind < data->ntests; ++testind) अणु
		ct  = &data->tests[testind];
		at  = 0;
		pos = ct->location[0].number;

		अगर (skb->len < 4 || pos > skb->len - 4)
			वापस false;

		अगर (skb_copy_bits(skb, pos, &n, माप(n)) < 0)
			BUG();
		val   = ntohl(n);
		nnums = ct->nnums;

		/* Inner loop runs over "&", "<<", ">>" and "@" opeअक्रमs */
		क्रम (i = 1; i < nnums; ++i) अणु
			u_पूर्णांक32_t number = ct->location[i].number;
			चयन (ct->location[i].nextop) अणु
			हाल XT_U32_AND:
				val &= number;
				अवरोध;
			हाल XT_U32_LEFTSH:
				val <<= number;
				अवरोध;
			हाल XT_U32_RIGHTSH:
				val >>= number;
				अवरोध;
			हाल XT_U32_AT:
				अगर (at + val < at)
					वापस false;
				at += val;
				pos = number;
				अगर (at + 4 < at || skb->len < at + 4 ||
				    pos > skb->len - at - 4)
					वापस false;

				अगर (skb_copy_bits(skb, at + pos, &n,
						    माप(n)) < 0)
					BUG();
				val = ntohl(n);
				अवरोध;
			पूर्ण
		पूर्ण

		/* Run over the "," and ":" opeअक्रमs */
		nvals = ct->nvalues;
		क्रम (i = 0; i < nvals; ++i)
			अगर (ct->value[i].min <= val && val <= ct->value[i].max)
				अवरोध;

		अगर (i >= ct->nvalues)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool u32_mt(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_u32 *data = par->matchinfo;
	bool ret;

	ret = u32_match_it(data, skb);
	वापस ret ^ data->invert;
पूर्ण

अटल काष्ठा xt_match xt_u32_mt_reg __पढ़ो_mostly = अणु
	.name       = "u32",
	.revision   = 0,
	.family     = NFPROTO_UNSPEC,
	.match      = u32_mt,
	.matchsize  = माप(काष्ठा xt_u32),
	.me         = THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init u32_mt_init(व्योम)
अणु
	वापस xt_रेजिस्टर_match(&xt_u32_mt_reg);
पूर्ण

अटल व्योम __निकास u32_mt_निकास(व्योम)
अणु
	xt_unरेजिस्टर_match(&xt_u32_mt_reg);
पूर्ण

module_init(u32_mt_init);
module_निकास(u32_mt_निकास);
MODULE_AUTHOR("Jan Engelhardt <jengelh@medozas.de>");
MODULE_DESCRIPTION("Xtables: arbitrary byte matching");
MODULE_LICENSE("GPL");
MODULE_ALIAS("ipt_u32");
MODULE_ALIAS("ip6t_u32");
