<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* net/sched/sch_ingress.c - Ingress and clsact qdisc
 *
 * Authors:     Jamal Hadi Salim 1999
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/list.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/rtnetlink.h>

#समावेश <net/netlink.h>
#समावेश <net/pkt_sched.h>
#समावेश <net/pkt_cls.h>

काष्ठा ingress_sched_data अणु
	काष्ठा tcf_block *block;
	काष्ठा tcf_block_ext_info block_info;
	काष्ठा mini_Qdisc_pair miniqp;
पूर्ण;

अटल काष्ठा Qdisc *ingress_leaf(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg)
अणु
	वापस शून्य;
पूर्ण

अटल अचिन्हित दीर्घ ingress_find(काष्ठा Qdisc *sch, u32 classid)
अणु
	वापस TC_H_MIN(classid) + 1;
पूर्ण

अटल अचिन्हित दीर्घ ingress_bind_filter(काष्ठा Qdisc *sch,
					 अचिन्हित दीर्घ parent, u32 classid)
अणु
	वापस ingress_find(sch, classid);
पूर्ण

अटल व्योम ingress_unbind_filter(काष्ठा Qdisc *sch, अचिन्हित दीर्घ cl)
अणु
पूर्ण

अटल व्योम ingress_walk(काष्ठा Qdisc *sch, काष्ठा qdisc_walker *walker)
अणु
पूर्ण

अटल काष्ठा tcf_block *ingress_tcf_block(काष्ठा Qdisc *sch, अचिन्हित दीर्घ cl,
					   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा ingress_sched_data *q = qdisc_priv(sch);

	वापस q->block;
पूर्ण

अटल व्योम clsact_chain_head_change(काष्ठा tcf_proto *tp_head, व्योम *priv)
अणु
	काष्ठा mini_Qdisc_pair *miniqp = priv;

	mini_qdisc_pair_swap(miniqp, tp_head);
पूर्ण;

अटल व्योम ingress_ingress_block_set(काष्ठा Qdisc *sch, u32 block_index)
अणु
	काष्ठा ingress_sched_data *q = qdisc_priv(sch);

	q->block_info.block_index = block_index;
पूर्ण

अटल u32 ingress_ingress_block_get(काष्ठा Qdisc *sch)
अणु
	काष्ठा ingress_sched_data *q = qdisc_priv(sch);

	वापस q->block_info.block_index;
पूर्ण

अटल पूर्णांक ingress_init(काष्ठा Qdisc *sch, काष्ठा nlattr *opt,
			काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा ingress_sched_data *q = qdisc_priv(sch);
	काष्ठा net_device *dev = qdisc_dev(sch);
	पूर्णांक err;

	net_inc_ingress_queue();

	mini_qdisc_pair_init(&q->miniqp, sch, &dev->miniq_ingress);

	q->block_info.binder_type = FLOW_BLOCK_BINDER_TYPE_CLSACT_INGRESS;
	q->block_info.chain_head_change = clsact_chain_head_change;
	q->block_info.chain_head_change_priv = &q->miniqp;

	err = tcf_block_get_ext(&q->block, sch, &q->block_info, extack);
	अगर (err)
		वापस err;

	mini_qdisc_pair_block_init(&q->miniqp, q->block);

	वापस 0;
पूर्ण

अटल व्योम ingress_destroy(काष्ठा Qdisc *sch)
अणु
	काष्ठा ingress_sched_data *q = qdisc_priv(sch);

	tcf_block_put_ext(q->block, sch, &q->block_info);
	net_dec_ingress_queue();
पूर्ण

अटल पूर्णांक ingress_dump(काष्ठा Qdisc *sch, काष्ठा sk_buff *skb)
अणु
	काष्ठा nlattr *nest;

	nest = nla_nest_start_noflag(skb, TCA_OPTIONS);
	अगर (nest == शून्य)
		जाओ nla_put_failure;

	वापस nla_nest_end(skb, nest);

nla_put_failure:
	nla_nest_cancel(skb, nest);
	वापस -1;
पूर्ण

अटल स्थिर काष्ठा Qdisc_class_ops ingress_class_ops = अणु
	.flags		=	QDISC_CLASS_OPS_DOIT_UNLOCKED,
	.leaf		=	ingress_leaf,
	.find		=	ingress_find,
	.walk		=	ingress_walk,
	.tcf_block	=	ingress_tcf_block,
	.bind_tcf	=	ingress_bind_filter,
	.unbind_tcf	=	ingress_unbind_filter,
पूर्ण;

अटल काष्ठा Qdisc_ops ingress_qdisc_ops __पढ़ो_mostly = अणु
	.cl_ops			=	&ingress_class_ops,
	.id			=	"ingress",
	.priv_size		=	माप(काष्ठा ingress_sched_data),
	.अटल_flags		=	TCQ_F_CPUSTATS,
	.init			=	ingress_init,
	.destroy		=	ingress_destroy,
	.dump			=	ingress_dump,
	.ingress_block_set	=	ingress_ingress_block_set,
	.ingress_block_get	=	ingress_ingress_block_get,
	.owner			=	THIS_MODULE,
पूर्ण;

काष्ठा clsact_sched_data अणु
	काष्ठा tcf_block *ingress_block;
	काष्ठा tcf_block *egress_block;
	काष्ठा tcf_block_ext_info ingress_block_info;
	काष्ठा tcf_block_ext_info egress_block_info;
	काष्ठा mini_Qdisc_pair miniqp_ingress;
	काष्ठा mini_Qdisc_pair miniqp_egress;
पूर्ण;

अटल अचिन्हित दीर्घ clsact_find(काष्ठा Qdisc *sch, u32 classid)
अणु
	चयन (TC_H_MIN(classid)) अणु
	हाल TC_H_MIN(TC_H_MIN_INGRESS):
	हाल TC_H_MIN(TC_H_MIN_EGRESS):
		वापस TC_H_MIN(classid);
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल अचिन्हित दीर्घ clsact_bind_filter(काष्ठा Qdisc *sch,
					अचिन्हित दीर्घ parent, u32 classid)
अणु
	वापस clsact_find(sch, classid);
पूर्ण

अटल काष्ठा tcf_block *clsact_tcf_block(काष्ठा Qdisc *sch, अचिन्हित दीर्घ cl,
					  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा clsact_sched_data *q = qdisc_priv(sch);

	चयन (cl) अणु
	हाल TC_H_MIN(TC_H_MIN_INGRESS):
		वापस q->ingress_block;
	हाल TC_H_MIN(TC_H_MIN_EGRESS):
		वापस q->egress_block;
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

अटल व्योम clsact_ingress_block_set(काष्ठा Qdisc *sch, u32 block_index)
अणु
	काष्ठा clsact_sched_data *q = qdisc_priv(sch);

	q->ingress_block_info.block_index = block_index;
पूर्ण

अटल व्योम clsact_egress_block_set(काष्ठा Qdisc *sch, u32 block_index)
अणु
	काष्ठा clsact_sched_data *q = qdisc_priv(sch);

	q->egress_block_info.block_index = block_index;
पूर्ण

अटल u32 clsact_ingress_block_get(काष्ठा Qdisc *sch)
अणु
	काष्ठा clsact_sched_data *q = qdisc_priv(sch);

	वापस q->ingress_block_info.block_index;
पूर्ण

अटल u32 clsact_egress_block_get(काष्ठा Qdisc *sch)
अणु
	काष्ठा clsact_sched_data *q = qdisc_priv(sch);

	वापस q->egress_block_info.block_index;
पूर्ण

अटल पूर्णांक clsact_init(काष्ठा Qdisc *sch, काष्ठा nlattr *opt,
		       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा clsact_sched_data *q = qdisc_priv(sch);
	काष्ठा net_device *dev = qdisc_dev(sch);
	पूर्णांक err;

	net_inc_ingress_queue();
	net_inc_egress_queue();

	mini_qdisc_pair_init(&q->miniqp_ingress, sch, &dev->miniq_ingress);

	q->ingress_block_info.binder_type = FLOW_BLOCK_BINDER_TYPE_CLSACT_INGRESS;
	q->ingress_block_info.chain_head_change = clsact_chain_head_change;
	q->ingress_block_info.chain_head_change_priv = &q->miniqp_ingress;

	err = tcf_block_get_ext(&q->ingress_block, sch, &q->ingress_block_info,
				extack);
	अगर (err)
		वापस err;

	mini_qdisc_pair_block_init(&q->miniqp_ingress, q->ingress_block);

	mini_qdisc_pair_init(&q->miniqp_egress, sch, &dev->miniq_egress);

	q->egress_block_info.binder_type = FLOW_BLOCK_BINDER_TYPE_CLSACT_EGRESS;
	q->egress_block_info.chain_head_change = clsact_chain_head_change;
	q->egress_block_info.chain_head_change_priv = &q->miniqp_egress;

	वापस tcf_block_get_ext(&q->egress_block, sch, &q->egress_block_info, extack);
पूर्ण

अटल व्योम clsact_destroy(काष्ठा Qdisc *sch)
अणु
	काष्ठा clsact_sched_data *q = qdisc_priv(sch);

	tcf_block_put_ext(q->egress_block, sch, &q->egress_block_info);
	tcf_block_put_ext(q->ingress_block, sch, &q->ingress_block_info);

	net_dec_ingress_queue();
	net_dec_egress_queue();
पूर्ण

अटल स्थिर काष्ठा Qdisc_class_ops clsact_class_ops = अणु
	.flags		=	QDISC_CLASS_OPS_DOIT_UNLOCKED,
	.leaf		=	ingress_leaf,
	.find		=	clsact_find,
	.walk		=	ingress_walk,
	.tcf_block	=	clsact_tcf_block,
	.bind_tcf	=	clsact_bind_filter,
	.unbind_tcf	=	ingress_unbind_filter,
पूर्ण;

अटल काष्ठा Qdisc_ops clsact_qdisc_ops __पढ़ो_mostly = अणु
	.cl_ops			=	&clsact_class_ops,
	.id			=	"clsact",
	.priv_size		=	माप(काष्ठा clsact_sched_data),
	.अटल_flags		=	TCQ_F_CPUSTATS,
	.init			=	clsact_init,
	.destroy		=	clsact_destroy,
	.dump			=	ingress_dump,
	.ingress_block_set	=	clsact_ingress_block_set,
	.egress_block_set	=	clsact_egress_block_set,
	.ingress_block_get	=	clsact_ingress_block_get,
	.egress_block_get	=	clsact_egress_block_get,
	.owner			=	THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init ingress_module_init(व्योम)
अणु
	पूर्णांक ret;

	ret = रेजिस्टर_qdisc(&ingress_qdisc_ops);
	अगर (!ret) अणु
		ret = रेजिस्टर_qdisc(&clsact_qdisc_ops);
		अगर (ret)
			unरेजिस्टर_qdisc(&ingress_qdisc_ops);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम __निकास ingress_module_निकास(व्योम)
अणु
	unरेजिस्टर_qdisc(&ingress_qdisc_ops);
	unरेजिस्टर_qdisc(&clsact_qdisc_ops);
पूर्ण

module_init(ingress_module_init);
module_निकास(ingress_module_निकास);

MODULE_ALIAS("sch_clsact");
MODULE_LICENSE("GPL");
