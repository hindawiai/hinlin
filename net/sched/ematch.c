<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * net/sched/ematch.c		Extended Match API
 *
 * Authors:	Thomas Graf <tgraf@suug.ch>
 *
 * ==========================================================================
 *
 * An extended match (ematch) is a small classअगरication tool not worth
 * writing a full classअगरier क्रम. Ematches can be पूर्णांकerconnected to क्रमm
 * a logic expression and get attached to classअगरiers to extend their
 * functionatlity.
 *
 * The userspace part transक्रमms the logic expressions पूर्णांकo an array
 * consisting of multiple sequences of पूर्णांकerconnected ematches separated
 * by markers. Precedence is implemented by a special ematch kind
 * referencing a sequence beyond the marker of the current sequence
 * causing the current position in the sequence to be pushed onto a stack
 * to allow the current position to be overwritten by the position referenced
 * in the special ematch. Matching जारीs in the new sequence until a
 * marker is reached causing the position to be restored from the stack.
 *
 * Example:
 *          A AND (B1 OR B2) AND C AND D
 *
 *              ------->-PUSH-------
 *    -->--    /         -->--      \   -->--
 *   /     \  /         /     \      \ /     \
 * +-------+-------+-------+-------+-------+--------+
 * | A AND | B AND | C AND | D END | B1 OR | B2 END |
 * +-------+-------+-------+-------+-------+--------+
 *                    \                      /
 *                     --------<-POP---------
 *
 * where B is a भव ematch referencing to sequence starting with B1.
 *
 * ==========================================================================
 *
 * How to ग_लिखो an ematch in 60 seconds
 * ------------------------------------
 *
 *   1) Provide a matcher function:
 *      अटल पूर्णांक my_match(काष्ठा sk_buff *skb, काष्ठा tcf_ematch *m,
 *                          काष्ठा tcf_pkt_info *info)
 *      अणु
 *      	काष्ठा mydata *d = (काष्ठा mydata *) m->data;
 *
 *      	अगर (...matching goes here...)
 *      		वापस 1;
 *      	अन्यथा
 *      		वापस 0;
 *      पूर्ण
 *
 *   2) Fill out a काष्ठा tcf_ematch_ops:
 *      अटल काष्ठा tcf_ematch_ops my_ops = अणु
 *      	.kind = unique id,
 *      	.datalen = माप(काष्ठा mydata),
 *      	.match = my_match,
 *      	.owner = THIS_MODULE,
 *      पूर्ण;
 *
 *   3) Register/Unरेजिस्टर your ematch:
 *      अटल पूर्णांक __init init_my_ematch(व्योम)
 *      अणु
 *      	वापस tcf_em_रेजिस्टर(&my_ops);
 *      पूर्ण
 *
 *      अटल व्योम __निकास निकास_my_ematch(व्योम)
 *      अणु
 *      	tcf_em_unरेजिस्टर(&my_ops);
 *      पूर्ण
 *
 *      module_init(init_my_ematch);
 *      module_निकास(निकास_my_ematch);
 *
 *   4) By now you should have two more seconds left, barely enough to
 *      खोलो up a beer to watch the compilation going.
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/skbuff.h>
#समावेश <net/pkt_cls.h>

अटल LIST_HEAD(ematch_ops);
अटल DEFINE_RWLOCK(ematch_mod_lock);

अटल काष्ठा tcf_ematch_ops *tcf_em_lookup(u16 kind)
अणु
	काष्ठा tcf_ematch_ops *e = शून्य;

	पढ़ो_lock(&ematch_mod_lock);
	list_क्रम_each_entry(e, &ematch_ops, link) अणु
		अगर (kind == e->kind) अणु
			अगर (!try_module_get(e->owner))
				e = शून्य;
			पढ़ो_unlock(&ematch_mod_lock);
			वापस e;
		पूर्ण
	पूर्ण
	पढ़ो_unlock(&ematch_mod_lock);

	वापस शून्य;
पूर्ण

/**
 * tcf_em_रेजिस्टर - रेजिस्टर an extended match
 *
 * @ops: ematch operations lookup table
 *
 * This function must be called by ematches to announce their presence.
 * The given @ops must have kind set to a unique identअगरier and the
 * callback match() must be implemented. All other callbacks are optional
 * and a fallback implementation is used instead.
 *
 * Returns -EEXISTS अगर an ematch of the same kind has alपढ़ोy रेजिस्टरed.
 */
पूर्णांक tcf_em_रेजिस्टर(काष्ठा tcf_ematch_ops *ops)
अणु
	पूर्णांक err = -EEXIST;
	काष्ठा tcf_ematch_ops *e;

	अगर (ops->match == शून्य)
		वापस -EINVAL;

	ग_लिखो_lock(&ematch_mod_lock);
	list_क्रम_each_entry(e, &ematch_ops, link)
		अगर (ops->kind == e->kind)
			जाओ errout;

	list_add_tail(&ops->link, &ematch_ops);
	err = 0;
errout:
	ग_लिखो_unlock(&ematch_mod_lock);
	वापस err;
पूर्ण
EXPORT_SYMBOL(tcf_em_रेजिस्टर);

/**
 * tcf_em_unरेजिस्टर - unregster and extended match
 *
 * @ops: ematch operations lookup table
 *
 * This function must be called by ematches to announce their disappearance
 * क्रम examples when the module माला_लो unloaded. The @ops parameter must be
 * the same as the one used क्रम registration.
 *
 * Returns -ENOENT अगर no matching ematch was found.
 */
व्योम tcf_em_unरेजिस्टर(काष्ठा tcf_ematch_ops *ops)
अणु
	ग_लिखो_lock(&ematch_mod_lock);
	list_del(&ops->link);
	ग_लिखो_unlock(&ematch_mod_lock);
पूर्ण
EXPORT_SYMBOL(tcf_em_unरेजिस्टर);

अटल अंतरभूत काष्ठा tcf_ematch *tcf_em_get_match(काष्ठा tcf_ematch_tree *tree,
						  पूर्णांक index)
अणु
	वापस &tree->matches[index];
पूर्ण


अटल पूर्णांक tcf_em_validate(काष्ठा tcf_proto *tp,
			   काष्ठा tcf_ematch_tree_hdr *tree_hdr,
			   काष्ठा tcf_ematch *em, काष्ठा nlattr *nla, पूर्णांक idx)
अणु
	पूर्णांक err = -EINVAL;
	काष्ठा tcf_ematch_hdr *em_hdr = nla_data(nla);
	पूर्णांक data_len = nla_len(nla) - माप(*em_hdr);
	व्योम *data = (व्योम *) em_hdr + माप(*em_hdr);
	काष्ठा net *net = tp->chain->block->net;

	अगर (!TCF_EM_REL_VALID(em_hdr->flags))
		जाओ errout;

	अगर (em_hdr->kind == TCF_EM_CONTAINER) अणु
		/* Special ematch called "container", carries an index
		 * referencing an बाह्यal ematch sequence.
		 */
		u32 ref;

		अगर (data_len < माप(ref))
			जाओ errout;
		ref = *(u32 *) data;

		अगर (ref >= tree_hdr->nmatches)
			जाओ errout;

		/* We करो not allow backward jumps to aव्योम loops and jumps
		 * to our own position are of course illegal.
		 */
		अगर (ref <= idx)
			जाओ errout;


		em->data = ref;
	पूर्ण अन्यथा अणु
		/* Note: This lookup will increase the module refcnt
		 * of the ematch module referenced. In हाल of a failure,
		 * a destroy function is called by the underlying layer
		 * which स्वतःmatically releases the reference again, thereक्रमe
		 * the module MUST not be given back under any circumstances
		 * here. Be aware, the destroy function assumes that the
		 * module is held अगर the ops field is non zero.
		 */
		em->ops = tcf_em_lookup(em_hdr->kind);

		अगर (em->ops == शून्य) अणु
			err = -ENOENT;
#अगर_घोषित CONFIG_MODULES
			__rtnl_unlock();
			request_module("ematch-kind-%u", em_hdr->kind);
			rtnl_lock();
			em->ops = tcf_em_lookup(em_hdr->kind);
			अगर (em->ops) अणु
				/* We dropped the RTNL mutex in order to
				 * perक्रमm the module load. Tell the caller
				 * to replay the request.
				 */
				module_put(em->ops->owner);
				em->ops = शून्य;
				err = -EAGAIN;
			पूर्ण
#पूर्ण_अगर
			जाओ errout;
		पूर्ण

		/* ematch module provides expected length of data, so we
		 * can करो a basic sanity check.
		 */
		अगर (em->ops->datalen && data_len < em->ops->datalen)
			जाओ errout;

		अगर (em->ops->change) अणु
			err = -EINVAL;
			अगर (em_hdr->flags & TCF_EM_SIMPLE)
				जाओ errout;
			err = em->ops->change(net, data, data_len, em);
			अगर (err < 0)
				जाओ errout;
		पूर्ण अन्यथा अगर (data_len > 0) अणु
			/* ematch module करोesn't provide an own change
			 * procedure and expects us to allocate and copy
			 * the ematch data.
			 *
			 * TCF_EM_SIMPLE may be specअगरied stating that the
			 * data only consists of a u32 पूर्णांकeger and the module
			 * करोes not expected a memory reference but rather
			 * the value carried.
			 */
			अगर (em_hdr->flags & TCF_EM_SIMPLE) अणु
				अगर (data_len < माप(u32))
					जाओ errout;
				em->data = *(u32 *) data;
			पूर्ण अन्यथा अणु
				व्योम *v = kmemdup(data, data_len, GFP_KERNEL);
				अगर (v == शून्य) अणु
					err = -ENOBUFS;
					जाओ errout;
				पूर्ण
				em->data = (अचिन्हित दीर्घ) v;
			पूर्ण
			em->datalen = data_len;
		पूर्ण
	पूर्ण

	em->matchid = em_hdr->matchid;
	em->flags = em_hdr->flags;
	em->net = net;

	err = 0;
errout:
	वापस err;
पूर्ण

अटल स्थिर काष्ठा nla_policy em_policy[TCA_EMATCH_TREE_MAX + 1] = अणु
	[TCA_EMATCH_TREE_HDR]	= अणु .len = माप(काष्ठा tcf_ematch_tree_hdr) पूर्ण,
	[TCA_EMATCH_TREE_LIST]	= अणु .type = NLA_NESTED पूर्ण,
पूर्ण;

/**
 * tcf_em_tree_validate - validate ematch config TLV and build ematch tree
 *
 * @tp: classअगरier kind handle
 * @nla: ematch tree configuration TLV
 * @tree: destination ematch tree variable to store the resulting
 *        ematch tree.
 *
 * This function validates the given configuration TLV @nla and builds an
 * ematch tree in @tree. The resulting tree must later be copied पूर्णांकo
 * the निजी classअगरier data using tcf_em_tree_change(). You MUST NOT
 * provide the ematch tree variable of the निजी classअगरier data directly,
 * the changes would not be locked properly.
 *
 * Returns a negative error code अगर the configuration TLV contains errors.
 */
पूर्णांक tcf_em_tree_validate(काष्ठा tcf_proto *tp, काष्ठा nlattr *nla,
			 काष्ठा tcf_ematch_tree *tree)
अणु
	पूर्णांक idx, list_len, matches_len, err;
	काष्ठा nlattr *tb[TCA_EMATCH_TREE_MAX + 1];
	काष्ठा nlattr *rt_match, *rt_hdr, *rt_list;
	काष्ठा tcf_ematch_tree_hdr *tree_hdr;
	काष्ठा tcf_ematch *em;

	स_रखो(tree, 0, माप(*tree));
	अगर (!nla)
		वापस 0;

	err = nla_parse_nested_deprecated(tb, TCA_EMATCH_TREE_MAX, nla,
					  em_policy, शून्य);
	अगर (err < 0)
		जाओ errout;

	err = -EINVAL;
	rt_hdr = tb[TCA_EMATCH_TREE_HDR];
	rt_list = tb[TCA_EMATCH_TREE_LIST];

	अगर (rt_hdr == शून्य || rt_list == शून्य)
		जाओ errout;

	tree_hdr = nla_data(rt_hdr);
	स_नकल(&tree->hdr, tree_hdr, माप(*tree_hdr));

	rt_match = nla_data(rt_list);
	list_len = nla_len(rt_list);
	matches_len = tree_hdr->nmatches * माप(*em);

	tree->matches = kzalloc(matches_len, GFP_KERNEL);
	अगर (tree->matches == शून्य)
		जाओ errout;

	/* We करो not use nla_parse_nested here because the maximum
	 * number of attributes is unknown. This saves us the allocation
	 * क्रम a tb buffer which would serve no purpose at all.
	 *
	 * The array of rt attributes is parsed in the order as they are
	 * provided, their type must be incremental from 1 to n. Even
	 * अगर it करोes not serve any real purpose, a failure of sticking
	 * to this policy will result in parsing failure.
	 */
	क्रम (idx = 0; nla_ok(rt_match, list_len); idx++) अणु
		err = -EINVAL;

		अगर (rt_match->nla_type != (idx + 1))
			जाओ errout_पात;

		अगर (idx >= tree_hdr->nmatches)
			जाओ errout_पात;

		अगर (nla_len(rt_match) < माप(काष्ठा tcf_ematch_hdr))
			जाओ errout_पात;

		em = tcf_em_get_match(tree, idx);

		err = tcf_em_validate(tp, tree_hdr, em, rt_match, idx);
		अगर (err < 0)
			जाओ errout_पात;

		rt_match = nla_next(rt_match, &list_len);
	पूर्ण

	/* Check अगर the number of matches provided by userspace actually
	 * complies with the array of matches. The number was used क्रम
	 * the validation of references and a mismatch could lead to
	 * undefined references during the matching process.
	 */
	अगर (idx != tree_hdr->nmatches) अणु
		err = -EINVAL;
		जाओ errout_पात;
	पूर्ण

	err = 0;
errout:
	वापस err;

errout_पात:
	tcf_em_tree_destroy(tree);
	वापस err;
पूर्ण
EXPORT_SYMBOL(tcf_em_tree_validate);

/**
 * tcf_em_tree_destroy - destroy an ematch tree
 *
 * @tree: ematch tree to be deleted
 *
 * This functions destroys an ematch tree previously created by
 * tcf_em_tree_validate()/tcf_em_tree_change(). You must ensure that
 * the ematch tree is not in use beक्रमe calling this function.
 */
व्योम tcf_em_tree_destroy(काष्ठा tcf_ematch_tree *tree)
अणु
	पूर्णांक i;

	अगर (tree->matches == शून्य)
		वापस;

	क्रम (i = 0; i < tree->hdr.nmatches; i++) अणु
		काष्ठा tcf_ematch *em = tcf_em_get_match(tree, i);

		अगर (em->ops) अणु
			अगर (em->ops->destroy)
				em->ops->destroy(em);
			अन्यथा अगर (!tcf_em_is_simple(em))
				kमुक्त((व्योम *) em->data);
			module_put(em->ops->owner);
		पूर्ण
	पूर्ण

	tree->hdr.nmatches = 0;
	kमुक्त(tree->matches);
	tree->matches = शून्य;
पूर्ण
EXPORT_SYMBOL(tcf_em_tree_destroy);

/**
 * tcf_em_tree_dump - dump ematch tree पूर्णांकo a rtnl message
 *
 * @skb: skb holding the rtnl message
 * @tree: ematch tree to be dumped
 * @tlv: TLV type to be used to encapsulate the tree
 *
 * This function dumps a ematch tree पूर्णांकo a rtnl message. It is valid to
 * call this function जबतक the ematch tree is in use.
 *
 * Returns -1 अगर the skb tailroom is insufficient.
 */
पूर्णांक tcf_em_tree_dump(काष्ठा sk_buff *skb, काष्ठा tcf_ematch_tree *tree, पूर्णांक tlv)
अणु
	पूर्णांक i;
	u8 *tail;
	काष्ठा nlattr *top_start;
	काष्ठा nlattr *list_start;

	top_start = nla_nest_start_noflag(skb, tlv);
	अगर (top_start == शून्य)
		जाओ nla_put_failure;

	अगर (nla_put(skb, TCA_EMATCH_TREE_HDR, माप(tree->hdr), &tree->hdr))
		जाओ nla_put_failure;

	list_start = nla_nest_start_noflag(skb, TCA_EMATCH_TREE_LIST);
	अगर (list_start == शून्य)
		जाओ nla_put_failure;

	tail = skb_tail_poपूर्णांकer(skb);
	क्रम (i = 0; i < tree->hdr.nmatches; i++) अणु
		काष्ठा nlattr *match_start = (काष्ठा nlattr *)tail;
		काष्ठा tcf_ematch *em = tcf_em_get_match(tree, i);
		काष्ठा tcf_ematch_hdr em_hdr = अणु
			.kind = em->ops ? em->ops->kind : TCF_EM_CONTAINER,
			.matchid = em->matchid,
			.flags = em->flags
		पूर्ण;

		अगर (nla_put(skb, i + 1, माप(em_hdr), &em_hdr))
			जाओ nla_put_failure;

		अगर (em->ops && em->ops->dump) अणु
			अगर (em->ops->dump(skb, em) < 0)
				जाओ nla_put_failure;
		पूर्ण अन्यथा अगर (tcf_em_is_container(em) || tcf_em_is_simple(em)) अणु
			u32 u = em->data;
			nla_put_nohdr(skb, माप(u), &u);
		पूर्ण अन्यथा अगर (em->datalen > 0)
			nla_put_nohdr(skb, em->datalen, (व्योम *) em->data);

		tail = skb_tail_poपूर्णांकer(skb);
		match_start->nla_len = tail - (u8 *)match_start;
	पूर्ण

	nla_nest_end(skb, list_start);
	nla_nest_end(skb, top_start);

	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण
EXPORT_SYMBOL(tcf_em_tree_dump);

अटल अंतरभूत पूर्णांक tcf_em_match(काष्ठा sk_buff *skb, काष्ठा tcf_ematch *em,
			       काष्ठा tcf_pkt_info *info)
अणु
	पूर्णांक r = em->ops->match(skb, em, info);

	वापस tcf_em_is_inverted(em) ? !r : r;
पूर्ण

/* Do not use this function directly, use tcf_em_tree_match instead */
पूर्णांक __tcf_em_tree_match(काष्ठा sk_buff *skb, काष्ठा tcf_ematch_tree *tree,
			काष्ठा tcf_pkt_info *info)
अणु
	पूर्णांक stackp = 0, match_idx = 0, res = 0;
	काष्ठा tcf_ematch *cur_match;
	पूर्णांक stack[CONFIG_NET_EMATCH_STACK];

proceed:
	जबतक (match_idx < tree->hdr.nmatches) अणु
		cur_match = tcf_em_get_match(tree, match_idx);

		अगर (tcf_em_is_container(cur_match)) अणु
			अगर (unlikely(stackp >= CONFIG_NET_EMATCH_STACK))
				जाओ stack_overflow;

			stack[stackp++] = match_idx;
			match_idx = cur_match->data;
			जाओ proceed;
		पूर्ण

		res = tcf_em_match(skb, cur_match, info);

		अगर (tcf_em_early_end(cur_match, res))
			अवरोध;

		match_idx++;
	पूर्ण

pop_stack:
	अगर (stackp > 0) अणु
		match_idx = stack[--stackp];
		cur_match = tcf_em_get_match(tree, match_idx);

		अगर (tcf_em_is_inverted(cur_match))
			res = !res;

		अगर (tcf_em_early_end(cur_match, res)) अणु
			जाओ pop_stack;
		पूर्ण अन्यथा अणु
			match_idx++;
			जाओ proceed;
		पूर्ण
	पूर्ण

	वापस res;

stack_overflow:
	net_warn_ratelimited("tc ematch: local stack overflow, increase NET_EMATCH_STACK\n");
	वापस -1;
पूर्ण
EXPORT_SYMBOL(__tcf_em_tree_match);
