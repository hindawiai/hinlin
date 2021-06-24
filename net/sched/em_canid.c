<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * em_canid.c  Ematch rule to match CAN frames according to their CAN IDs
 *
 * Idea:       Oliver Hartkopp <oliver.hartkopp@volkswagen.de>
 * Copyright:  (c) 2011 Czech Technical University in Prague
 *             (c) 2011 Volkswagen Group Research
 * Authors:    Michal Sojka <sojkam1@fel.cvut.cz>
 *             Pavel Pisa <pisa@cmp.felk.cvut.cz>
 *             Rostislav Lisovy <lisovy@gmail.cz>
 * Funded by:  Volkswagen Group Research
 */

#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/skbuff.h>
#समावेश <net/pkt_cls.h>
#समावेश <linux/can.h>

#घोषणा EM_CAN_RULES_MAX 500

काष्ठा canid_match अणु
	/* For each SFF CAN ID (11 bit) there is one record in this bitfield */
	DECLARE_BITMAP(match_sff, (1 << CAN_SFF_ID_BITS));

	पूर्णांक rules_count;
	पूर्णांक sff_rules_count;
	पूर्णांक eff_rules_count;

	/*
	 * Raw rules copied from netlink message; Used क्रम sending
	 * inक्रमmation to userspace (when 'tc filter show' is invoked)
	 * AND when matching EFF frames
	 */
	काष्ठा can_filter rules_raw[];
पूर्ण;

/**
 * em_canid_get_id() - Extracts Can ID out of the sk_buff काष्ठाure.
 * @skb: buffer to extract Can ID from
 */
अटल canid_t em_canid_get_id(काष्ठा sk_buff *skb)
अणु
	/* CAN ID is stored within the data field */
	काष्ठा can_frame *cf = (काष्ठा can_frame *)skb->data;

	वापस cf->can_id;
पूर्ण

अटल व्योम em_canid_sff_match_add(काष्ठा canid_match *cm, u32 can_id,
					u32 can_mask)
अणु
	पूर्णांक i;

	/*
	 * Limit can_mask and can_id to SFF range to
	 * protect against ग_लिखो after end of array
	 */
	can_mask &= CAN_SFF_MASK;
	can_id &= can_mask;

	/* Single frame */
	अगर (can_mask == CAN_SFF_MASK) अणु
		set_bit(can_id, cm->match_sff);
		वापस;
	पूर्ण

	/* All frames */
	अगर (can_mask == 0) अणु
		biपंचांगap_fill(cm->match_sff, (1 << CAN_SFF_ID_BITS));
		वापस;
	पूर्ण

	/*
	 * Inभागidual frame filter.
	 * Add record (set bit to 1) क्रम each ID that
	 * conक्रमms particular rule
	 */
	क्रम (i = 0; i < (1 << CAN_SFF_ID_BITS); i++) अणु
		अगर ((i & can_mask) == can_id)
			set_bit(i, cm->match_sff);
	पूर्ण
पूर्ण

अटल अंतरभूत काष्ठा canid_match *em_canid_priv(काष्ठा tcf_ematch *m)
अणु
	वापस (काष्ठा canid_match *)m->data;
पूर्ण

अटल पूर्णांक em_canid_match(काष्ठा sk_buff *skb, काष्ठा tcf_ematch *m,
			 काष्ठा tcf_pkt_info *info)
अणु
	काष्ठा canid_match *cm = em_canid_priv(m);
	canid_t can_id;
	पूर्णांक match = 0;
	पूर्णांक i;
	स्थिर काष्ठा can_filter *lp;

	can_id = em_canid_get_id(skb);

	अगर (can_id & CAN_EFF_FLAG) अणु
		क्रम (i = 0, lp = cm->rules_raw;
		     i < cm->eff_rules_count; i++, lp++) अणु
			अगर (!(((lp->can_id ^ can_id) & lp->can_mask))) अणु
				match = 1;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु /* SFF */
		can_id &= CAN_SFF_MASK;
		match = (test_bit(can_id, cm->match_sff) ? 1 : 0);
	पूर्ण

	वापस match;
पूर्ण

अटल पूर्णांक em_canid_change(काष्ठा net *net, व्योम *data, पूर्णांक len,
			  काष्ठा tcf_ematch *m)
अणु
	काष्ठा can_filter *conf = data; /* Array with rules */
	काष्ठा canid_match *cm;
	पूर्णांक i;

	अगर (!len)
		वापस -EINVAL;

	अगर (len % माप(काष्ठा can_filter))
		वापस -EINVAL;

	अगर (len > माप(काष्ठा can_filter) * EM_CAN_RULES_MAX)
		वापस -EINVAL;

	cm = kzalloc(माप(काष्ठा canid_match) + len, GFP_KERNEL);
	अगर (!cm)
		वापस -ENOMEM;

	cm->rules_count = len / माप(काष्ठा can_filter);

	/*
	 * We need two क्रम() loops क्रम copying rules पूर्णांकo two contiguous
	 * areas in rules_raw to process all eff rules with a simple loop.
	 * NB: The configuration पूर्णांकerface supports sff and eff rules.
	 * We करो not support filters here that match क्रम the same can_id
	 * provided in a SFF and EFF frame (e.g. 0x123 / 0x80000123).
	 * For this (unusual हाल) two filters have to be specअगरied. The
	 * SFF/EFF separation is करोne with the CAN_EFF_FLAG in the can_id.
	 */

	/* Fill rules_raw with EFF rules first */
	क्रम (i = 0; i < cm->rules_count; i++) अणु
		अगर (conf[i].can_id & CAN_EFF_FLAG) अणु
			स_नकल(cm->rules_raw + cm->eff_rules_count,
				&conf[i],
				माप(काष्ठा can_filter));

			cm->eff_rules_count++;
		पूर्ण
	पूर्ण

	/* append SFF frame rules */
	क्रम (i = 0; i < cm->rules_count; i++) अणु
		अगर (!(conf[i].can_id & CAN_EFF_FLAG)) अणु
			स_नकल(cm->rules_raw
				+ cm->eff_rules_count
				+ cm->sff_rules_count,
				&conf[i], माप(काष्ठा can_filter));

			cm->sff_rules_count++;

			em_canid_sff_match_add(cm,
				conf[i].can_id, conf[i].can_mask);
		पूर्ण
	पूर्ण

	m->datalen = माप(काष्ठा canid_match) + len;
	m->data = (अचिन्हित दीर्घ)cm;
	वापस 0;
पूर्ण

अटल व्योम em_canid_destroy(काष्ठा tcf_ematch *m)
अणु
	काष्ठा canid_match *cm = em_canid_priv(m);

	kमुक्त(cm);
पूर्ण

अटल पूर्णांक em_canid_dump(काष्ठा sk_buff *skb, काष्ठा tcf_ematch *m)
अणु
	काष्ठा canid_match *cm = em_canid_priv(m);

	/*
	 * When configuring this ematch 'rules_count' is set not to exceed
	 * 'rules_raw' array size
	 */
	अगर (nla_put_nohdr(skb, माप(काष्ठा can_filter) * cm->rules_count,
	    &cm->rules_raw) < 0)
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

अटल काष्ठा tcf_ematch_ops em_canid_ops = अणु
	.kind	  = TCF_EM_CANID,
	.change	  = em_canid_change,
	.match	  = em_canid_match,
	.destroy  = em_canid_destroy,
	.dump	  = em_canid_dump,
	.owner	  = THIS_MODULE,
	.link	  = LIST_HEAD_INIT(em_canid_ops.link)
पूर्ण;

अटल पूर्णांक __init init_em_canid(व्योम)
अणु
	वापस tcf_em_रेजिस्टर(&em_canid_ops);
पूर्ण

अटल व्योम __निकास निकास_em_canid(व्योम)
अणु
	tcf_em_unरेजिस्टर(&em_canid_ops);
पूर्ण

MODULE_LICENSE("GPL");

module_init(init_em_canid);
module_निकास(निकास_em_canid);

MODULE_ALIAS_TCF_EMATCH(TCF_EM_CANID);
