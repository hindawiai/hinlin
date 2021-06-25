<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (C) 2018 Netronome Systems, Inc. */

#समावेश <linux/bitfield.h>
#समावेश <net/pkt_cls.h>

#समावेश "../nfpcore/nfp_cpp.h"
#समावेश "../nfp_app.h"
#समावेश "../nfp_net_repr.h"
#समावेश "main.h"

काष्ठा nfp_abm_u32_match अणु
	u32 handle;
	u32 band;
	u8 mask;
	u8 val;
	काष्ठा list_head list;
पूर्ण;

अटल bool
nfp_abm_u32_check_knode(काष्ठा nfp_abm *abm, काष्ठा tc_cls_u32_knode *knode,
			__be16 proto, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tc_u32_key *k;
	अचिन्हित पूर्णांक tos_off;

	अगर (knode->exts && tcf_exts_has_actions(knode->exts)) अणु
		NL_SET_ERR_MSG_MOD(extack, "action offload not supported");
		वापस false;
	पूर्ण
	अगर (knode->link_handle) अणु
		NL_SET_ERR_MSG_MOD(extack, "linking not supported");
		वापस false;
	पूर्ण
	अगर (knode->sel->flags != TC_U32_TERMINAL) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "flags must be equal to TC_U32_TERMINAL");
		वापस false;
	पूर्ण
	अगर (knode->sel->off || knode->sel->offshअगरt || knode->sel->offmask ||
	    knode->sel->offoff || knode->fshअगरt) अणु
		NL_SET_ERR_MSG_MOD(extack, "variable offsetting not supported");
		वापस false;
	पूर्ण
	अगर (knode->sel->hoff || knode->sel->hmask) अणु
		NL_SET_ERR_MSG_MOD(extack, "hashing not supported");
		वापस false;
	पूर्ण
	अगर (knode->val || knode->mask) अणु
		NL_SET_ERR_MSG_MOD(extack, "matching on mark not supported");
		वापस false;
	पूर्ण
	अगर (knode->res && knode->res->class) अणु
		NL_SET_ERR_MSG_MOD(extack, "setting non-0 class not supported");
		वापस false;
	पूर्ण
	अगर (knode->res && knode->res->classid >= abm->num_bands) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "classid higher than number of bands");
		वापस false;
	पूर्ण
	अगर (knode->sel->nkeys != 1) अणु
		NL_SET_ERR_MSG_MOD(extack, "exactly one key required");
		वापस false;
	पूर्ण

	चयन (proto) अणु
	हाल htons(ETH_P_IP):
		tos_off = 16;
		अवरोध;
	हाल htons(ETH_P_IPV6):
		tos_off = 20;
		अवरोध;
	शेष:
		NL_SET_ERR_MSG_MOD(extack, "only IP and IPv6 supported as filter protocol");
		वापस false;
	पूर्ण

	k = &knode->sel->keys[0];
	अगर (k->offmask) अणु
		NL_SET_ERR_MSG_MOD(extack, "offset mask - variable offsetting not supported");
		वापस false;
	पूर्ण
	अगर (k->off) अणु
		NL_SET_ERR_MSG_MOD(extack, "only DSCP fields can be matched");
		वापस false;
	पूर्ण
	अगर (k->val & ~k->mask) अणु
		NL_SET_ERR_MSG_MOD(extack, "mask does not cover the key");
		वापस false;
	पूर्ण
	अगर (be32_to_cpu(k->mask) >> tos_off & ~abm->dscp_mask) अणु
		NL_SET_ERR_MSG_MOD(extack, "only high DSCP class selector bits can be used");
		nfp_err(abm->app->cpp,
			"u32 offload: requested mask %x FW can support only %x\n",
			be32_to_cpu(k->mask) >> tos_off, abm->dscp_mask);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

/* This filter list -> map conversion is O(n * m), we expect single digit or
 * low द्विगुन digit number of prios and likewise क्रम the filters.  Also u32
 * करोesn't report stats, so it's really only setup समय cost.
 */
अटल अचिन्हित पूर्णांक
nfp_abm_find_band_क्रम_prio(काष्ठा nfp_abm_link *alink, अचिन्हित पूर्णांक prio)
अणु
	काष्ठा nfp_abm_u32_match *iter;

	list_क्रम_each_entry(iter, &alink->dscp_map, list)
		अगर ((prio & iter->mask) == iter->val)
			वापस iter->band;

	वापस alink->def_band;
पूर्ण

अटल पूर्णांक nfp_abm_update_band_map(काष्ठा nfp_abm_link *alink)
अणु
	अचिन्हित पूर्णांक i, bits_per_prio, prios_per_word, base_shअगरt;
	काष्ठा nfp_abm *abm = alink->abm;
	u32 field_mask;

	alink->has_prio = !list_empty(&alink->dscp_map);

	bits_per_prio = roundup_घात_of_two(order_base_2(abm->num_bands));
	field_mask = (1 << bits_per_prio) - 1;
	prios_per_word = माप(u32) * BITS_PER_BYTE / bits_per_prio;

	/* FW mask applies from top bits */
	base_shअगरt = 8 - order_base_2(abm->num_prios);

	क्रम (i = 0; i < abm->num_prios; i++) अणु
		अचिन्हित पूर्णांक offset;
		u32 *word;
		u8 band;

		word = &alink->prio_map[i / prios_per_word];
		offset = (i % prios_per_word) * bits_per_prio;

		band = nfp_abm_find_band_क्रम_prio(alink, i << base_shअगरt);

		*word &= ~(field_mask << offset);
		*word |= band << offset;
	पूर्ण

	/* Qdisc offload status may change अगर has_prio changed */
	nfp_abm_qdisc_offload_update(alink);

	वापस nfp_abm_ctrl_prio_map_update(alink, alink->prio_map);
पूर्ण

अटल व्योम
nfp_abm_u32_knode_delete(काष्ठा nfp_abm_link *alink,
			 काष्ठा tc_cls_u32_knode *knode)
अणु
	काष्ठा nfp_abm_u32_match *iter;

	list_क्रम_each_entry(iter, &alink->dscp_map, list)
		अगर (iter->handle == knode->handle) अणु
			list_del(&iter->list);
			kमुक्त(iter);
			nfp_abm_update_band_map(alink);
			वापस;
		पूर्ण
पूर्ण

अटल पूर्णांक
nfp_abm_u32_knode_replace(काष्ठा nfp_abm_link *alink,
			  काष्ठा tc_cls_u32_knode *knode,
			  __be16 proto, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nfp_abm_u32_match *match = शून्य, *iter;
	अचिन्हित पूर्णांक tos_off;
	u8 mask, val;
	पूर्णांक err;

	अगर (!nfp_abm_u32_check_knode(alink->abm, knode, proto, extack))
		जाओ err_delete;

	tos_off = proto == htons(ETH_P_IP) ? 16 : 20;

	/* Extract the DSCP Class Selector bits */
	val = be32_to_cpu(knode->sel->keys[0].val) >> tos_off & 0xff;
	mask = be32_to_cpu(knode->sel->keys[0].mask) >> tos_off & 0xff;

	/* Check अगर there is no conflicting mapping and find match by handle */
	list_क्रम_each_entry(iter, &alink->dscp_map, list) अणु
		u32 cmask;

		अगर (iter->handle == knode->handle) अणु
			match = iter;
			जारी;
		पूर्ण

		cmask = iter->mask & mask;
		अगर ((iter->val & cmask) == (val & cmask) &&
		    iter->band != knode->res->classid) अणु
			NL_SET_ERR_MSG_MOD(extack, "conflict with already offloaded filter");
			जाओ err_delete;
		पूर्ण
	पूर्ण

	अगर (!match) अणु
		match = kzalloc(माप(*match), GFP_KERNEL);
		अगर (!match)
			वापस -ENOMEM;
		list_add(&match->list, &alink->dscp_map);
	पूर्ण
	match->handle = knode->handle;
	match->band = knode->res->classid;
	match->mask = mask;
	match->val = val;

	err = nfp_abm_update_band_map(alink);
	अगर (err)
		जाओ err_delete;

	वापस 0;

err_delete:
	nfp_abm_u32_knode_delete(alink, knode);
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक nfp_abm_setup_tc_block_cb(क्रमागत tc_setup_type type,
				     व्योम *type_data, व्योम *cb_priv)
अणु
	काष्ठा tc_cls_u32_offload *cls_u32 = type_data;
	काष्ठा nfp_repr *repr = cb_priv;
	काष्ठा nfp_abm_link *alink;

	alink = repr->app_priv;

	अगर (type != TC_SETUP_CLSU32) अणु
		NL_SET_ERR_MSG_MOD(cls_u32->common.extack,
				   "only offload of u32 classifier supported");
		वापस -EOPNOTSUPP;
	पूर्ण
	अगर (!tc_cls_can_offload_and_chain0(repr->netdev, &cls_u32->common))
		वापस -EOPNOTSUPP;

	अगर (cls_u32->common.protocol != htons(ETH_P_IP) &&
	    cls_u32->common.protocol != htons(ETH_P_IPV6)) अणु
		NL_SET_ERR_MSG_MOD(cls_u32->common.extack,
				   "only IP and IPv6 supported as filter protocol");
		वापस -EOPNOTSUPP;
	पूर्ण

	चयन (cls_u32->command) अणु
	हाल TC_CLSU32_NEW_KNODE:
	हाल TC_CLSU32_REPLACE_KNODE:
		वापस nfp_abm_u32_knode_replace(alink, &cls_u32->knode,
						 cls_u32->common.protocol,
						 cls_u32->common.extack);
	हाल TC_CLSU32_DELETE_KNODE:
		nfp_abm_u32_knode_delete(alink, &cls_u32->knode);
		वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल LIST_HEAD(nfp_abm_block_cb_list);

पूर्णांक nfp_abm_setup_cls_block(काष्ठा net_device *netdev, काष्ठा nfp_repr *repr,
			    काष्ठा flow_block_offload *f)
अणु
	वापस flow_block_cb_setup_simple(f, &nfp_abm_block_cb_list,
					  nfp_abm_setup_tc_block_cb,
					  repr, repr, true);
पूर्ण
