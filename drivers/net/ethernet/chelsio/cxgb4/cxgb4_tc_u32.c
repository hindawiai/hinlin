<शैली गुरु>
/*
 * This file is part of the Chelsio T4 Ethernet driver क्रम Linux.
 *
 * Copyright (c) 2016 Chelsio Communications, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश <net/tc_act/tc_gact.h>
#समावेश <net/tc_act/tc_mirred.h>

#समावेश "cxgb4.h"
#समावेश "cxgb4_filter.h"
#समावेश "cxgb4_tc_u32_parse.h"
#समावेश "cxgb4_tc_u32.h"

/* Fill ch_filter_specअगरication with parsed match value/mask pair. */
अटल पूर्णांक fill_match_fields(काष्ठा adapter *adap,
			     काष्ठा ch_filter_specअगरication *fs,
			     काष्ठा tc_cls_u32_offload *cls,
			     स्थिर काष्ठा cxgb4_match_field *entry,
			     bool next_header)
अणु
	अचिन्हित पूर्णांक i, j;
	__be32 val, mask;
	पूर्णांक off, err;
	bool found;

	क्रम (i = 0; i < cls->knode.sel->nkeys; i++) अणु
		off = cls->knode.sel->keys[i].off;
		val = cls->knode.sel->keys[i].val;
		mask = cls->knode.sel->keys[i].mask;

		अगर (next_header) अणु
			/* For next headers, parse only keys with offmask */
			अगर (!cls->knode.sel->keys[i].offmask)
				जारी;
		पूर्ण अन्यथा अणु
			/* For the reमुख्यing, parse only keys without offmask */
			अगर (cls->knode.sel->keys[i].offmask)
				जारी;
		पूर्ण

		found = false;

		क्रम (j = 0; entry[j].val; j++) अणु
			अगर (off == entry[j].off) अणु
				found = true;
				err = entry[j].val(fs, val, mask);
				अगर (err)
					वापस err;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!found)
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* Fill ch_filter_specअगरication with parsed action. */
अटल पूर्णांक fill_action_fields(काष्ठा adapter *adap,
			      काष्ठा ch_filter_specअगरication *fs,
			      काष्ठा tc_cls_u32_offload *cls)
अणु
	अचिन्हित पूर्णांक num_actions = 0;
	स्थिर काष्ठा tc_action *a;
	काष्ठा tcf_exts *exts;
	पूर्णांक i;

	exts = cls->knode.exts;
	अगर (!tcf_exts_has_actions(exts))
		वापस -EINVAL;

	tcf_exts_क्रम_each_action(i, a, exts) अणु
		/* Don't allow more than one action per rule. */
		अगर (num_actions)
			वापस -EINVAL;

		/* Drop in hardware. */
		अगर (is_tcf_gact_shot(a)) अणु
			fs->action = FILTER_DROP;
			num_actions++;
			जारी;
		पूर्ण

		/* Re-direct to specअगरied port in hardware. */
		अगर (is_tcf_mirred_egress_redirect(a)) अणु
			काष्ठा net_device *n_dev, *target_dev;
			bool found = false;
			अचिन्हित पूर्णांक i;

			target_dev = tcf_mirred_dev(a);
			क्रम_each_port(adap, i) अणु
				n_dev = adap->port[i];
				अगर (target_dev == n_dev) अणु
					fs->action = FILTER_SWITCH;
					fs->eport = i;
					found = true;
					अवरोध;
				पूर्ण
			पूर्ण

			/* Interface करोesn't beदीर्घ to any port of
			 * the underlying hardware.
			 */
			अगर (!found)
				वापस -EINVAL;

			num_actions++;
			जारी;
		पूर्ण

		/* Un-supported action. */
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक cxgb4_config_knode(काष्ठा net_device *dev, काष्ठा tc_cls_u32_offload *cls)
अणु
	स्थिर काष्ठा cxgb4_match_field *start, *link_start = शून्य;
	काष्ठा netlink_ext_ack *extack = cls->common.extack;
	काष्ठा adapter *adapter = netdev2adap(dev);
	__be16 protocol = cls->common.protocol;
	काष्ठा ch_filter_specअगरication fs;
	काष्ठा cxgb4_tc_u32_table *t;
	काष्ठा cxgb4_link *link;
	u32 uhtid, link_uhtid;
	bool is_ipv6 = false;
	u8 inet_family;
	पूर्णांक filter_id;
	पूर्णांक ret;

	अगर (!can_tc_u32_offload(dev))
		वापस -EOPNOTSUPP;

	अगर (protocol != htons(ETH_P_IP) && protocol != htons(ETH_P_IPV6))
		वापस -EOPNOTSUPP;

	inet_family = (protocol == htons(ETH_P_IPV6)) ? PF_INET6 : PF_INET;

	/* Get a मुक्त filter entry TID, where we can insert this new
	 * rule. Only insert rule अगर its prio करोesn't conflict with
	 * existing rules.
	 */
	filter_id = cxgb4_get_मुक्त_ftid(dev, inet_family, false,
					TC_U32_NODE(cls->knode.handle));
	अगर (filter_id < 0) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "No free LETCAM index available");
		वापस -ENOMEM;
	पूर्ण

	t = adapter->tc_u32;
	uhtid = TC_U32_USERHTID(cls->knode.handle);
	link_uhtid = TC_U32_USERHTID(cls->knode.link_handle);

	/* Ensure that uhtid is either root u32 (i.e. 0x800)
	 * or a a valid linked bucket.
	 */
	अगर (uhtid != 0x800 && uhtid >= t->size)
		वापस -EINVAL;

	/* Ensure link handle uhtid is sane, अगर specअगरied. */
	अगर (link_uhtid >= t->size)
		वापस -EINVAL;

	स_रखो(&fs, 0, माप(fs));

	अगर (filter_id < adapter->tids.nhpftids)
		fs.prio = 1;
	fs.tc_prio = cls->common.prio;
	fs.tc_cookie = cls->knode.handle;

	अगर (protocol == htons(ETH_P_IPV6)) अणु
		start = cxgb4_ipv6_fields;
		is_ipv6 = true;
	पूर्ण अन्यथा अणु
		start = cxgb4_ipv4_fields;
		is_ipv6 = false;
	पूर्ण

	अगर (uhtid != 0x800) अणु
		/* Link must exist from root node beक्रमe insertion. */
		अगर (!t->table[uhtid - 1].link_handle)
			वापस -EINVAL;

		/* Link must have a valid supported next header. */
		link_start = t->table[uhtid - 1].match_field;
		अगर (!link_start)
			वापस -EINVAL;
	पूर्ण

	/* Parse links and record them क्रम subsequent jumps to valid
	 * next headers.
	 */
	अगर (link_uhtid) अणु
		स्थिर काष्ठा cxgb4_next_header *next;
		bool found = false;
		अचिन्हित पूर्णांक i, j;
		__be32 val, mask;
		पूर्णांक off;

		अगर (t->table[link_uhtid - 1].link_handle) अणु
			dev_err(adapter->pdev_dev,
				"Link handle exists for: 0x%x\n",
				link_uhtid);
			वापस -EINVAL;
		पूर्ण

		next = is_ipv6 ? cxgb4_ipv6_jumps : cxgb4_ipv4_jumps;

		/* Try to find matches that allow jumps to next header. */
		क्रम (i = 0; next[i].jump; i++) अणु
			अगर (next[i].sel.offoff != cls->knode.sel->offoff ||
			    next[i].sel.offshअगरt != cls->knode.sel->offshअगरt ||
			    next[i].sel.offmask != cls->knode.sel->offmask ||
			    next[i].sel.off != cls->knode.sel->off)
				जारी;

			/* Found a possible candidate.  Find a key that
			 * matches the corresponding offset, value, and
			 * mask to jump to next header.
			 */
			क्रम (j = 0; j < cls->knode.sel->nkeys; j++) अणु
				off = cls->knode.sel->keys[j].off;
				val = cls->knode.sel->keys[j].val;
				mask = cls->knode.sel->keys[j].mask;

				अगर (next[i].key.off == off &&
				    next[i].key.val == val &&
				    next[i].key.mask == mask) अणु
					found = true;
					अवरोध;
				पूर्ण
			पूर्ण

			अगर (!found)
				जारी; /* Try next candidate. */

			/* Candidate to jump to next header found.
			 * Translate all keys to पूर्णांकernal specअगरication
			 * and store them in jump table. This spec is copied
			 * later to set the actual filters.
			 */
			ret = fill_match_fields(adapter, &fs, cls,
						start, false);
			अगर (ret)
				जाओ out;

			link = &t->table[link_uhtid - 1];
			link->match_field = next[i].jump;
			link->link_handle = cls->knode.handle;
			स_नकल(&link->fs, &fs, माप(fs));
			अवरोध;
		पूर्ण

		/* No candidate found to jump to next header. */
		अगर (!found)
			वापस -EINVAL;

		वापस 0;
	पूर्ण

	/* Fill ch_filter_specअगरication match fields to be shipped to hardware.
	 * Copy the linked spec (अगर any) first.  And then update the spec as
	 * needed.
	 */
	अगर (uhtid != 0x800 && t->table[uhtid - 1].link_handle) अणु
		/* Copy linked ch_filter_specअगरication */
		स_नकल(&fs, &t->table[uhtid - 1].fs, माप(fs));
		ret = fill_match_fields(adapter, &fs, cls,
					link_start, true);
		अगर (ret)
			जाओ out;
	पूर्ण

	ret = fill_match_fields(adapter, &fs, cls, start, false);
	अगर (ret)
		जाओ out;

	/* Fill ch_filter_specअगरication action fields to be shipped to
	 * hardware.
	 */
	ret = fill_action_fields(adapter, &fs, cls);
	अगर (ret)
		जाओ out;

	/* The filter spec has been completely built from the info
	 * provided from u32.  We now set some शेष fields in the
	 * spec क्रम sanity.
	 */

	/* Match only packets coming from the ingress port where this
	 * filter will be created.
	 */
	fs.val.iport = netdev2pinfo(dev)->port_id;
	fs.mask.iport = ~0;

	/* Enable filter hit counts. */
	fs.hitcnts = 1;

	/* Set type of filter - IPv6 or IPv4 */
	fs.type = is_ipv6 ? 1 : 0;

	/* Set the filter */
	ret = cxgb4_set_filter(dev, filter_id, &fs);
	अगर (ret)
		जाओ out;

	/* If this is a linked bucket, then set the corresponding
	 * entry in the biपंचांगap to mark it as beदीर्घing to this linked
	 * bucket.
	 */
	अगर (uhtid != 0x800 && t->table[uhtid - 1].link_handle)
		set_bit(filter_id, t->table[uhtid - 1].tid_map);

out:
	वापस ret;
पूर्ण

पूर्णांक cxgb4_delete_knode(काष्ठा net_device *dev, काष्ठा tc_cls_u32_offload *cls)
अणु
	काष्ठा adapter *adapter = netdev2adap(dev);
	अचिन्हित पूर्णांक filter_id, max_tids, i, j;
	काष्ठा cxgb4_link *link = शून्य;
	काष्ठा cxgb4_tc_u32_table *t;
	काष्ठा filter_entry *f;
	bool found = false;
	u32 handle, uhtid;
	u8 nslots;
	पूर्णांक ret;

	अगर (!can_tc_u32_offload(dev))
		वापस -EOPNOTSUPP;

	/* Fetch the location to delete the filter. */
	max_tids = adapter->tids.nhpftids + adapter->tids.nftids;

	spin_lock_bh(&adapter->tids.ftid_lock);
	filter_id = 0;
	जबतक (filter_id < max_tids) अणु
		अगर (filter_id < adapter->tids.nhpftids) अणु
			i = filter_id;
			f = &adapter->tids.hpftid_tab[i];
			अगर (f->valid && f->fs.tc_cookie == cls->knode.handle) अणु
				found = true;
				अवरोध;
			पूर्ण

			i = find_next_bit(adapter->tids.hpftid_bmap,
					  adapter->tids.nhpftids, i + 1);
			अगर (i >= adapter->tids.nhpftids) अणु
				filter_id = adapter->tids.nhpftids;
				जारी;
			पूर्ण

			filter_id = i;
		पूर्ण अन्यथा अणु
			i = filter_id - adapter->tids.nhpftids;
			f = &adapter->tids.ftid_tab[i];
			अगर (f->valid && f->fs.tc_cookie == cls->knode.handle) अणु
				found = true;
				अवरोध;
			पूर्ण

			i = find_next_bit(adapter->tids.ftid_bmap,
					  adapter->tids.nftids, i + 1);
			अगर (i >= adapter->tids.nftids)
				अवरोध;

			filter_id = i + adapter->tids.nhpftids;
		पूर्ण

		nslots = 0;
		अगर (f->fs.type) अणु
			nslots++;
			अगर (CHELSIO_CHIP_VERSION(adapter->params.chip) <
			    CHELSIO_T6)
				nslots += 2;
		पूर्ण

		filter_id += nslots;
	पूर्ण
	spin_unlock_bh(&adapter->tids.ftid_lock);

	अगर (!found)
		वापस -दुस्फल;

	t = adapter->tc_u32;
	handle = cls->knode.handle;
	uhtid = TC_U32_USERHTID(cls->knode.handle);

	/* Ensure that uhtid is either root u32 (i.e. 0x800)
	 * or a a valid linked bucket.
	 */
	अगर (uhtid != 0x800 && uhtid >= t->size)
		वापस -EINVAL;

	/* Delete the specअगरied filter */
	अगर (uhtid != 0x800) अणु
		link = &t->table[uhtid - 1];
		अगर (!link->link_handle)
			वापस -EINVAL;

		अगर (!test_bit(filter_id, link->tid_map))
			वापस -EINVAL;
	पूर्ण

	ret = cxgb4_del_filter(dev, filter_id, शून्य);
	अगर (ret)
		जाओ out;

	अगर (link)
		clear_bit(filter_id, link->tid_map);

	/* If a link is being deleted, then delete all filters
	 * associated with the link.
	 */
	क्रम (i = 0; i < t->size; i++) अणु
		link = &t->table[i];

		अगर (link->link_handle == handle) अणु
			क्रम (j = 0; j < max_tids; j++) अणु
				अगर (!test_bit(j, link->tid_map))
					जारी;

				ret = __cxgb4_del_filter(dev, j, शून्य, शून्य);
				अगर (ret)
					जाओ out;

				clear_bit(j, link->tid_map);
			पूर्ण

			/* Clear the link state */
			link->match_field = शून्य;
			link->link_handle = 0;
			स_रखो(&link->fs, 0, माप(link->fs));
			अवरोध;
		पूर्ण
	पूर्ण

out:
	वापस ret;
पूर्ण

व्योम cxgb4_cleanup_tc_u32(काष्ठा adapter *adap)
अणु
	काष्ठा cxgb4_tc_u32_table *t;
	अचिन्हित पूर्णांक i;

	अगर (!adap->tc_u32)
		वापस;

	/* Free up all allocated memory. */
	t = adap->tc_u32;
	क्रम (i = 0; i < t->size; i++) अणु
		काष्ठा cxgb4_link *link = &t->table[i];

		kvमुक्त(link->tid_map);
	पूर्ण
	kvमुक्त(adap->tc_u32);
पूर्ण

काष्ठा cxgb4_tc_u32_table *cxgb4_init_tc_u32(काष्ठा adapter *adap)
अणु
	अचिन्हित पूर्णांक max_tids = adap->tids.nftids + adap->tids.nhpftids;
	काष्ठा cxgb4_tc_u32_table *t;
	अचिन्हित पूर्णांक i;

	अगर (!max_tids)
		वापस शून्य;

	t = kvzalloc(काष्ठा_size(t, table, max_tids), GFP_KERNEL);
	अगर (!t)
		वापस शून्य;

	t->size = max_tids;

	क्रम (i = 0; i < t->size; i++) अणु
		काष्ठा cxgb4_link *link = &t->table[i];
		अचिन्हित पूर्णांक bmap_size;

		bmap_size = BITS_TO_LONGS(max_tids);
		link->tid_map = kvसुस्मृति(bmap_size, माप(अचिन्हित दीर्घ),
					 GFP_KERNEL);
		अगर (!link->tid_map)
			जाओ out_no_mem;
		biपंचांगap_zero(link->tid_map, max_tids);
	पूर्ण

	वापस t;

out_no_mem:
	क्रम (i = 0; i < t->size; i++) अणु
		काष्ठा cxgb4_link *link = &t->table[i];
		kvमुक्त(link->tid_map);
	पूर्ण
	kvमुक्त(t);

	वापस शून्य;
पूर्ण
