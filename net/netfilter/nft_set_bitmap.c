<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2017 Pablo Neira Ayuso <pablo@netfilter.org>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/list.h>
#समावेश <linux/netlink.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_tables_core.h>

काष्ठा nft_biपंचांगap_elem अणु
	काष्ठा list_head	head;
	काष्ठा nft_set_ext	ext;
पूर्ण;

/* This biपंचांगap uses two bits to represent one element. These two bits determine
 * the element state in the current and the future generation.
 *
 * An element can be in three states. The generation cursor is represented using
 * the ^ अक्षरacter, note that this cursor shअगरts on every succesful transaction.
 * If no transaction is going on, we observe all elements are in the following
 * state:
 *
 * 11 = this element is active in the current generation. In हाल of no updates,
 * ^    it stays active in the next generation.
 * 00 = this element is inactive in the current generation. In हाल of no
 * ^    updates, it stays inactive in the next generation.
 *
 * On transaction handling, we observe these two temporary states:
 *
 * 01 = this element is inactive in the current generation and it becomes active
 * ^    in the next one. This happens when the element is inserted but commit
 *      path has not yet been executed yet, so activation is still pending. On
 *      transaction पातion, the element is हटाओd.
 * 10 = this element is active in the current generation and it becomes inactive
 * ^    in the next one. This happens when the element is deactivated but commit
 *      path has not yet been executed yet, so removal is still pending. On
 *      transation पातion, the next generation bit is reset to go back to
 *      restore its previous state.
 */
काष्ठा nft_biपंचांगap अणु
	काष्ठा	list_head	list;
	u16			biपंचांगap_size;
	u8			biपंचांगap[];
पूर्ण;

अटल अंतरभूत व्योम nft_biपंचांगap_location(स्थिर काष्ठा nft_set *set,
				       स्थिर व्योम *key,
				       u32 *idx, u32 *off)
अणु
	u32 k;

	अगर (set->klen == 2)
		k = *(u16 *)key;
	अन्यथा
		k = *(u8 *)key;
	k <<= 1;

	*idx = k / BITS_PER_BYTE;
	*off = k % BITS_PER_BYTE;
पूर्ण

/* Fetch the two bits that represent the element and check अगर it is active based
 * on the generation mask.
 */
अटल अंतरभूत bool
nft_biपंचांगap_active(स्थिर u8 *biपंचांगap, u32 idx, u32 off, u8 genmask)
अणु
	वापस (biपंचांगap[idx] & (0x3 << off)) & (genmask << off);
पूर्ण

अटल bool nft_biपंचांगap_lookup(स्थिर काष्ठा net *net, स्थिर काष्ठा nft_set *set,
			      स्थिर u32 *key, स्थिर काष्ठा nft_set_ext **ext)
अणु
	स्थिर काष्ठा nft_biपंचांगap *priv = nft_set_priv(set);
	u8 genmask = nft_genmask_cur(net);
	u32 idx, off;

	nft_biपंचांगap_location(set, key, &idx, &off);

	वापस nft_biपंचांगap_active(priv->biपंचांगap, idx, off, genmask);
पूर्ण

अटल काष्ठा nft_biपंचांगap_elem *
nft_biपंचांगap_elem_find(स्थिर काष्ठा nft_set *set, काष्ठा nft_biपंचांगap_elem *this,
		     u8 genmask)
अणु
	स्थिर काष्ठा nft_biपंचांगap *priv = nft_set_priv(set);
	काष्ठा nft_biपंचांगap_elem *be;

	list_क्रम_each_entry_rcu(be, &priv->list, head) अणु
		अगर (स_भेद(nft_set_ext_key(&be->ext),
			   nft_set_ext_key(&this->ext), set->klen) ||
		    !nft_set_elem_active(&be->ext, genmask))
			जारी;

		वापस be;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम *nft_biपंचांगap_get(स्थिर काष्ठा net *net, स्थिर काष्ठा nft_set *set,
			    स्थिर काष्ठा nft_set_elem *elem, अचिन्हित पूर्णांक flags)
अणु
	स्थिर काष्ठा nft_biपंचांगap *priv = nft_set_priv(set);
	u8 genmask = nft_genmask_cur(net);
	काष्ठा nft_biपंचांगap_elem *be;

	list_क्रम_each_entry_rcu(be, &priv->list, head) अणु
		अगर (स_भेद(nft_set_ext_key(&be->ext), elem->key.val.data, set->klen) ||
		    !nft_set_elem_active(&be->ext, genmask))
			जारी;

		वापस be;
	पूर्ण
	वापस ERR_PTR(-ENOENT);
पूर्ण

अटल पूर्णांक nft_biपंचांगap_insert(स्थिर काष्ठा net *net, स्थिर काष्ठा nft_set *set,
			     स्थिर काष्ठा nft_set_elem *elem,
			     काष्ठा nft_set_ext **ext)
अणु
	काष्ठा nft_biपंचांगap *priv = nft_set_priv(set);
	काष्ठा nft_biपंचांगap_elem *new = elem->priv, *be;
	u8 genmask = nft_genmask_next(net);
	u32 idx, off;

	be = nft_biपंचांगap_elem_find(set, new, genmask);
	अगर (be) अणु
		*ext = &be->ext;
		वापस -EEXIST;
	पूर्ण

	nft_biपंचांगap_location(set, nft_set_ext_key(&new->ext), &idx, &off);
	/* Enter 01 state. */
	priv->biपंचांगap[idx] |= (genmask << off);
	list_add_tail_rcu(&new->head, &priv->list);

	वापस 0;
पूर्ण

अटल व्योम nft_biपंचांगap_हटाओ(स्थिर काष्ठा net *net,
			      स्थिर काष्ठा nft_set *set,
			      स्थिर काष्ठा nft_set_elem *elem)
अणु
	काष्ठा nft_biपंचांगap *priv = nft_set_priv(set);
	काष्ठा nft_biपंचांगap_elem *be = elem->priv;
	u8 genmask = nft_genmask_next(net);
	u32 idx, off;

	nft_biपंचांगap_location(set, nft_set_ext_key(&be->ext), &idx, &off);
	/* Enter 00 state. */
	priv->biपंचांगap[idx] &= ~(genmask << off);
	list_del_rcu(&be->head);
पूर्ण

अटल व्योम nft_biपंचांगap_activate(स्थिर काष्ठा net *net,
				स्थिर काष्ठा nft_set *set,
				स्थिर काष्ठा nft_set_elem *elem)
अणु
	काष्ठा nft_biपंचांगap *priv = nft_set_priv(set);
	काष्ठा nft_biपंचांगap_elem *be = elem->priv;
	u8 genmask = nft_genmask_next(net);
	u32 idx, off;

	nft_biपंचांगap_location(set, nft_set_ext_key(&be->ext), &idx, &off);
	/* Enter 11 state. */
	priv->biपंचांगap[idx] |= (genmask << off);
	nft_set_elem_change_active(net, set, &be->ext);
पूर्ण

अटल bool nft_biपंचांगap_flush(स्थिर काष्ठा net *net,
			     स्थिर काष्ठा nft_set *set, व्योम *_be)
अणु
	काष्ठा nft_biपंचांगap *priv = nft_set_priv(set);
	u8 genmask = nft_genmask_next(net);
	काष्ठा nft_biपंचांगap_elem *be = _be;
	u32 idx, off;

	nft_biपंचांगap_location(set, nft_set_ext_key(&be->ext), &idx, &off);
	/* Enter 10 state, similar to deactivation. */
	priv->biपंचांगap[idx] &= ~(genmask << off);
	nft_set_elem_change_active(net, set, &be->ext);

	वापस true;
पूर्ण

अटल व्योम *nft_biपंचांगap_deactivate(स्थिर काष्ठा net *net,
				   स्थिर काष्ठा nft_set *set,
				   स्थिर काष्ठा nft_set_elem *elem)
अणु
	काष्ठा nft_biपंचांगap *priv = nft_set_priv(set);
	काष्ठा nft_biपंचांगap_elem *this = elem->priv, *be;
	u8 genmask = nft_genmask_next(net);
	u32 idx, off;

	nft_biपंचांगap_location(set, elem->key.val.data, &idx, &off);

	be = nft_biपंचांगap_elem_find(set, this, genmask);
	अगर (!be)
		वापस शून्य;

	/* Enter 10 state. */
	priv->biपंचांगap[idx] &= ~(genmask << off);
	nft_set_elem_change_active(net, set, &be->ext);

	वापस be;
पूर्ण

अटल व्योम nft_biपंचांगap_walk(स्थिर काष्ठा nft_ctx *ctx,
			    काष्ठा nft_set *set,
			    काष्ठा nft_set_iter *iter)
अणु
	स्थिर काष्ठा nft_biपंचांगap *priv = nft_set_priv(set);
	काष्ठा nft_biपंचांगap_elem *be;
	काष्ठा nft_set_elem elem;

	list_क्रम_each_entry_rcu(be, &priv->list, head) अणु
		अगर (iter->count < iter->skip)
			जाओ cont;
		अगर (!nft_set_elem_active(&be->ext, iter->genmask))
			जाओ cont;

		elem.priv = be;

		iter->err = iter->fn(ctx, set, iter, &elem);

		अगर (iter->err < 0)
			वापस;
cont:
		iter->count++;
	पूर्ण
पूर्ण

/* The biपंचांगap size is घात(2, key length in bits) / bits per byte. This is
 * multiplied by two since each element takes two bits. For 8 bit keys, the
 * biपंचांगap consumes 66 bytes. For 16 bit keys, 16388 bytes.
 */
अटल अंतरभूत u32 nft_biपंचांगap_size(u32 klen)
अणु
	वापस ((2 << ((klen * BITS_PER_BYTE) - 1)) / BITS_PER_BYTE) << 1;
पूर्ण

अटल अंतरभूत u64 nft_biपंचांगap_total_size(u32 klen)
अणु
	वापस माप(काष्ठा nft_biपंचांगap) + nft_biपंचांगap_size(klen);
पूर्ण

अटल u64 nft_biपंचांगap_privsize(स्थिर काष्ठा nlattr * स्थिर nla[],
			       स्थिर काष्ठा nft_set_desc *desc)
अणु
	u32 klen = ntohl(nla_get_be32(nla[NFTA_SET_KEY_LEN]));

	वापस nft_biपंचांगap_total_size(klen);
पूर्ण

अटल पूर्णांक nft_biपंचांगap_init(स्थिर काष्ठा nft_set *set,
			   स्थिर काष्ठा nft_set_desc *desc,
			   स्थिर काष्ठा nlattr * स्थिर nla[])
अणु
	काष्ठा nft_biपंचांगap *priv = nft_set_priv(set);

	INIT_LIST_HEAD(&priv->list);
	priv->biपंचांगap_size = nft_biपंचांगap_size(set->klen);

	वापस 0;
पूर्ण

अटल व्योम nft_biपंचांगap_destroy(स्थिर काष्ठा nft_set *set)
अणु
	काष्ठा nft_biपंचांगap *priv = nft_set_priv(set);
	काष्ठा nft_biपंचांगap_elem *be, *n;

	list_क्रम_each_entry_safe(be, n, &priv->list, head)
		nft_set_elem_destroy(set, be, true);
पूर्ण

अटल bool nft_biपंचांगap_estimate(स्थिर काष्ठा nft_set_desc *desc, u32 features,
				काष्ठा nft_set_estimate *est)
अणु
	/* Make sure biपंचांगaps we करोn't get biपंचांगaps larger than 16 Kbytes. */
	अगर (desc->klen > 2)
		वापस false;
	अन्यथा अगर (desc->expr)
		वापस false;

	est->size   = nft_biपंचांगap_total_size(desc->klen);
	est->lookup = NFT_SET_CLASS_O_1;
	est->space  = NFT_SET_CLASS_O_1;

	वापस true;
पूर्ण

स्थिर काष्ठा nft_set_type nft_set_biपंचांगap_type = अणु
	.ops		= अणु
		.privsize	= nft_biपंचांगap_privsize,
		.elemsize	= दुरत्व(काष्ठा nft_biपंचांगap_elem, ext),
		.estimate	= nft_biपंचांगap_estimate,
		.init		= nft_biपंचांगap_init,
		.destroy	= nft_biपंचांगap_destroy,
		.insert		= nft_biपंचांगap_insert,
		.हटाओ		= nft_biपंचांगap_हटाओ,
		.deactivate	= nft_biपंचांगap_deactivate,
		.flush		= nft_biपंचांगap_flush,
		.activate	= nft_biपंचांगap_activate,
		.lookup		= nft_biपंचांगap_lookup,
		.walk		= nft_biपंचांगap_walk,
		.get		= nft_biपंचांगap_get,
	पूर्ण,
पूर्ण;
