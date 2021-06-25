<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* iptables module क्रम using new netfilter netlink queue
 *
 * (C) 2005 by Harald Welte <laक्रमge@netfilter.org>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>

#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter_arp.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter/xt_NFQUEUE.h>

#समावेश <net/netfilter/nf_queue.h>

MODULE_AUTHOR("Harald Welte <laforge@netfilter.org>");
MODULE_DESCRIPTION("Xtables: packet forwarding to netlink");
MODULE_LICENSE("GPL");
MODULE_ALIAS("ipt_NFQUEUE");
MODULE_ALIAS("ip6t_NFQUEUE");
MODULE_ALIAS("arpt_NFQUEUE");

अटल u32 jhash_initval __पढ़ो_mostly;

अटल अचिन्हित पूर्णांक
nfqueue_tg(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_NFQ_info *tinfo = par->targinfo;

	वापस NF_QUEUE_NR(tinfo->queuक्रमागत);
पूर्ण

अटल अचिन्हित पूर्णांक
nfqueue_tg_v1(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_NFQ_info_v1 *info = par->targinfo;
	u32 queue = info->queuक्रमागत;

	अगर (info->queues_total > 1) अणु
		queue = nfqueue_hash(skb, queue, info->queues_total,
				     xt_family(par), jhash_initval);
	पूर्ण
	वापस NF_QUEUE_NR(queue);
पूर्ण

अटल अचिन्हित पूर्णांक
nfqueue_tg_v2(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_NFQ_info_v2 *info = par->targinfo;
	अचिन्हित पूर्णांक ret = nfqueue_tg_v1(skb, par);

	अगर (info->bypass)
		ret |= NF_VERDICT_FLAG_QUEUE_BYPASS;
	वापस ret;
पूर्ण

अटल पूर्णांक nfqueue_tg_check(स्थिर काष्ठा xt_tgchk_param *par)
अणु
	स्थिर काष्ठा xt_NFQ_info_v3 *info = par->targinfo;
	u32 maxid;

	init_hashअक्रमom(&jhash_initval);

	अगर (info->queues_total == 0) अणु
		pr_info_ratelimited("number of total queues is 0\n");
		वापस -EINVAL;
	पूर्ण
	maxid = info->queues_total - 1 + info->queuक्रमागत;
	अगर (maxid > 0xffff) अणु
		pr_info_ratelimited("number of queues (%u) out of range (got %u)\n",
				    info->queues_total, maxid);
		वापस -दुस्फल;
	पूर्ण
	अगर (par->target->revision == 2 && info->flags > 1)
		वापस -EINVAL;
	अगर (par->target->revision == 3 && info->flags & ~NFQ_FLAG_MASK)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक
nfqueue_tg_v3(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_NFQ_info_v3 *info = par->targinfo;
	u32 queue = info->queuक्रमागत;
	पूर्णांक ret;

	अगर (info->queues_total > 1) अणु
		अगर (info->flags & NFQ_FLAG_CPU_FANOUT) अणु
			पूर्णांक cpu = smp_processor_id();

			queue = info->queuक्रमागत + cpu % info->queues_total;
		पूर्ण अन्यथा अणु
			queue = nfqueue_hash(skb, queue, info->queues_total,
					     xt_family(par), jhash_initval);
		पूर्ण
	पूर्ण

	ret = NF_QUEUE_NR(queue);
	अगर (info->flags & NFQ_FLAG_BYPASS)
		ret |= NF_VERDICT_FLAG_QUEUE_BYPASS;

	वापस ret;
पूर्ण

अटल काष्ठा xt_target nfqueue_tg_reg[] __पढ़ो_mostly = अणु
	अणु
		.name		= "NFQUEUE",
		.family		= NFPROTO_UNSPEC,
		.target		= nfqueue_tg,
		.tarमाला_लोize	= माप(काष्ठा xt_NFQ_info),
		.me		= THIS_MODULE,
	पूर्ण,
	अणु
		.name		= "NFQUEUE",
		.revision	= 1,
		.family		= NFPROTO_UNSPEC,
		.checkentry	= nfqueue_tg_check,
		.target		= nfqueue_tg_v1,
		.tarमाला_लोize	= माप(काष्ठा xt_NFQ_info_v1),
		.me		= THIS_MODULE,
	पूर्ण,
	अणु
		.name		= "NFQUEUE",
		.revision	= 2,
		.family		= NFPROTO_UNSPEC,
		.checkentry	= nfqueue_tg_check,
		.target		= nfqueue_tg_v2,
		.tarमाला_लोize	= माप(काष्ठा xt_NFQ_info_v2),
		.me		= THIS_MODULE,
	पूर्ण,
	अणु
		.name		= "NFQUEUE",
		.revision	= 3,
		.family		= NFPROTO_UNSPEC,
		.checkentry	= nfqueue_tg_check,
		.target		= nfqueue_tg_v3,
		.tarमाला_लोize	= माप(काष्ठा xt_NFQ_info_v3),
		.me		= THIS_MODULE,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init nfqueue_tg_init(व्योम)
अणु
	वापस xt_रेजिस्टर_tarमाला_लो(nfqueue_tg_reg, ARRAY_SIZE(nfqueue_tg_reg));
पूर्ण

अटल व्योम __निकास nfqueue_tg_निकास(व्योम)
अणु
	xt_unरेजिस्टर_tarमाला_लो(nfqueue_tg_reg, ARRAY_SIZE(nfqueue_tg_reg));
पूर्ण

module_init(nfqueue_tg_init);
module_निकास(nfqueue_tg_निकास);
