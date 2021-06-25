<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/****************************************************************************
 * Driver क्रम Solarflare network controllers and boards
 * Copyright 2005-2018 Solarflare Communications Inc.
 * Copyright 2019-2020 Xilinx Inc.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation, incorporated herein by reference.
 */

#समावेश "mcdi_filters.h"
#समावेश "mcdi.h"
#समावेश "nic.h"
#समावेश "rx_common.h"

/* The maximum size of a shared RSS context */
/* TODO: this should really be from the mcdi protocol export */
#घोषणा EFX_EF10_MAX_SHARED_RSS_CONTEXT_SIZE 64UL

#घोषणा EFX_EF10_FILTER_ID_INVALID 0xffff

/* An arbitrary search limit क्रम the software hash table */
#घोषणा EFX_EF10_FILTER_SEARCH_LIMIT 200

अटल काष्ठा efx_filter_spec *
efx_mcdi_filter_entry_spec(स्थिर काष्ठा efx_mcdi_filter_table *table,
			   अचिन्हित पूर्णांक filter_idx)
अणु
	वापस (काष्ठा efx_filter_spec *)(table->entry[filter_idx].spec &
					  ~EFX_EF10_FILTER_FLAGS);
पूर्ण

अटल अचिन्हित पूर्णांक
efx_mcdi_filter_entry_flags(स्थिर काष्ठा efx_mcdi_filter_table *table,
			   अचिन्हित पूर्णांक filter_idx)
अणु
	वापस table->entry[filter_idx].spec & EFX_EF10_FILTER_FLAGS;
पूर्ण

अटल u32 efx_mcdi_filter_get_unsafe_id(u32 filter_id)
अणु
	WARN_ON_ONCE(filter_id == EFX_EF10_FILTER_ID_INVALID);
	वापस filter_id & (EFX_MCDI_FILTER_TBL_ROWS - 1);
पूर्ण

अटल अचिन्हित पूर्णांक efx_mcdi_filter_get_unsafe_pri(u32 filter_id)
अणु
	वापस filter_id / (EFX_MCDI_FILTER_TBL_ROWS * 2);
पूर्ण

अटल u32 efx_mcdi_filter_make_filter_id(अचिन्हित पूर्णांक pri, u16 idx)
अणु
	वापस pri * EFX_MCDI_FILTER_TBL_ROWS * 2 + idx;
पूर्ण

/*
 * Decide whether a filter should be exclusive or अन्यथा should allow
 * delivery to additional recipients.  Currently we decide that
 * filters क्रम specअगरic local unicast MAC and IP addresses are
 * exclusive.
 */
अटल bool efx_mcdi_filter_is_exclusive(स्थिर काष्ठा efx_filter_spec *spec)
अणु
	अगर (spec->match_flags & EFX_FILTER_MATCH_LOC_MAC &&
	    !is_multicast_ether_addr(spec->loc_mac))
		वापस true;

	अगर ((spec->match_flags &
	     (EFX_FILTER_MATCH_ETHER_TYPE | EFX_FILTER_MATCH_LOC_HOST)) ==
	    (EFX_FILTER_MATCH_ETHER_TYPE | EFX_FILTER_MATCH_LOC_HOST)) अणु
		अगर (spec->ether_type == htons(ETH_P_IP) &&
		    !ipv4_is_multicast(spec->loc_host[0]))
			वापस true;
		अगर (spec->ether_type == htons(ETH_P_IPV6) &&
		    ((स्थिर u8 *)spec->loc_host)[0] != 0xff)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम
efx_mcdi_filter_set_entry(काष्ठा efx_mcdi_filter_table *table,
			  अचिन्हित पूर्णांक filter_idx,
			  स्थिर काष्ठा efx_filter_spec *spec,
			  अचिन्हित पूर्णांक flags)
अणु
	table->entry[filter_idx].spec =	(अचिन्हित दीर्घ)spec | flags;
पूर्ण

अटल व्योम
efx_mcdi_filter_push_prep_set_match_fields(काष्ठा efx_nic *efx,
					   स्थिर काष्ठा efx_filter_spec *spec,
					   efx_dword_t *inbuf)
अणु
	क्रमागत efx_encap_type encap_type = efx_filter_get_encap_type(spec);
	u32 match_fields = 0, uc_match, mc_match;

	MCDI_SET_DWORD(inbuf, FILTER_OP_IN_OP,
		       efx_mcdi_filter_is_exclusive(spec) ?
		       MC_CMD_FILTER_OP_IN_OP_INSERT :
		       MC_CMD_FILTER_OP_IN_OP_SUBSCRIBE);

	/*
	 * Convert match flags and values.  Unlike almost
	 * everything अन्यथा in MCDI, these fields are in
	 * network byte order.
	 */
#घोषणा COPY_VALUE(value, mcdi_field)					     \
	करो अणु							     \
		match_fields |=					     \
			1 << MC_CMD_FILTER_OP_IN_MATCH_ ##	     \
			mcdi_field ## _LBN;			     \
		BUILD_BUG_ON(					     \
			MC_CMD_FILTER_OP_IN_ ## mcdi_field ## _LEN < \
			माप(value));				     \
		स_नकल(MCDI_PTR(inbuf, FILTER_OP_IN_ ##	mcdi_field), \
		       &value, माप(value));			     \
	पूर्ण जबतक (0)
#घोषणा COPY_FIELD(gen_flag, gen_field, mcdi_field)			     \
	अगर (spec->match_flags & EFX_FILTER_MATCH_ ## gen_flag) अणु     \
		COPY_VALUE(spec->gen_field, mcdi_field);	     \
	पूर्ण
	/*
	 * Handle encap filters first.  They will always be mismatch
	 * (unknown UC or MC) filters
	 */
	अगर (encap_type) अणु
		/*
		 * ether_type and outer_ip_proto need to be variables
		 * because COPY_VALUE wants to स_नकल them
		 */
		__be16 ether_type =
			htons(encap_type & EFX_ENCAP_FLAG_IPV6 ?
			      ETH_P_IPV6 : ETH_P_IP);
		u8 vni_type = MC_CMD_FILTER_OP_EXT_IN_VNI_TYPE_GENEVE;
		u8 outer_ip_proto;

		चयन (encap_type & EFX_ENCAP_TYPES_MASK) अणु
		हाल EFX_ENCAP_TYPE_VXLAN:
			vni_type = MC_CMD_FILTER_OP_EXT_IN_VNI_TYPE_VXLAN;
			fallthrough;
		हाल EFX_ENCAP_TYPE_GENEVE:
			COPY_VALUE(ether_type, ETHER_TYPE);
			outer_ip_proto = IPPROTO_UDP;
			COPY_VALUE(outer_ip_proto, IP_PROTO);
			/*
			 * We always need to set the type field, even
			 * though we're not matching on the TNI.
			 */
			MCDI_POPULATE_DWORD_1(inbuf,
				FILTER_OP_EXT_IN_VNI_OR_VSID,
				FILTER_OP_EXT_IN_VNI_TYPE,
				vni_type);
			अवरोध;
		हाल EFX_ENCAP_TYPE_NVGRE:
			COPY_VALUE(ether_type, ETHER_TYPE);
			outer_ip_proto = IPPROTO_GRE;
			COPY_VALUE(outer_ip_proto, IP_PROTO);
			अवरोध;
		शेष:
			WARN_ON(1);
		पूर्ण

		uc_match = MC_CMD_FILTER_OP_EXT_IN_MATCH_IFRM_UNKNOWN_UCAST_DST_LBN;
		mc_match = MC_CMD_FILTER_OP_EXT_IN_MATCH_IFRM_UNKNOWN_MCAST_DST_LBN;
	पूर्ण अन्यथा अणु
		uc_match = MC_CMD_FILTER_OP_EXT_IN_MATCH_UNKNOWN_UCAST_DST_LBN;
		mc_match = MC_CMD_FILTER_OP_EXT_IN_MATCH_UNKNOWN_MCAST_DST_LBN;
	पूर्ण

	अगर (spec->match_flags & EFX_FILTER_MATCH_LOC_MAC_IG)
		match_fields |=
			is_multicast_ether_addr(spec->loc_mac) ?
			1 << mc_match :
			1 << uc_match;
	COPY_FIELD(REM_HOST, rem_host, SRC_IP);
	COPY_FIELD(LOC_HOST, loc_host, DST_IP);
	COPY_FIELD(REM_MAC, rem_mac, SRC_MAC);
	COPY_FIELD(REM_PORT, rem_port, SRC_PORT);
	COPY_FIELD(LOC_MAC, loc_mac, DST_MAC);
	COPY_FIELD(LOC_PORT, loc_port, DST_PORT);
	COPY_FIELD(ETHER_TYPE, ether_type, ETHER_TYPE);
	COPY_FIELD(INNER_VID, inner_vid, INNER_VLAN);
	COPY_FIELD(OUTER_VID, outer_vid, OUTER_VLAN);
	COPY_FIELD(IP_PROTO, ip_proto, IP_PROTO);
#अघोषित COPY_FIELD
#अघोषित COPY_VALUE
	MCDI_SET_DWORD(inbuf, FILTER_OP_IN_MATCH_FIELDS,
		       match_fields);
पूर्ण

अटल व्योम efx_mcdi_filter_push_prep(काष्ठा efx_nic *efx,
				      स्थिर काष्ठा efx_filter_spec *spec,
				      efx_dword_t *inbuf, u64 handle,
				      काष्ठा efx_rss_context *ctx,
				      bool replacing)
अणु
	u32 flags = spec->flags;

	स_रखो(inbuf, 0, MC_CMD_FILTER_OP_EXT_IN_LEN);

	/* If RSS filter, caller better have given us an RSS context */
	अगर (flags & EFX_FILTER_FLAG_RX_RSS) अणु
		/*
		 * We करोn't have the ability to return an error, so we'll just
		 * log a warning and disable RSS क्रम the filter.
		 */
		अगर (WARN_ON_ONCE(!ctx))
			flags &= ~EFX_FILTER_FLAG_RX_RSS;
		अन्यथा अगर (WARN_ON_ONCE(ctx->context_id == EFX_MCDI_RSS_CONTEXT_INVALID))
			flags &= ~EFX_FILTER_FLAG_RX_RSS;
	पूर्ण

	अगर (replacing) अणु
		MCDI_SET_DWORD(inbuf, FILTER_OP_IN_OP,
			       MC_CMD_FILTER_OP_IN_OP_REPLACE);
		MCDI_SET_QWORD(inbuf, FILTER_OP_IN_HANDLE, handle);
	पूर्ण अन्यथा अणु
		efx_mcdi_filter_push_prep_set_match_fields(efx, spec, inbuf);
	पूर्ण

	MCDI_SET_DWORD(inbuf, FILTER_OP_IN_PORT_ID, efx->vport_id);
	MCDI_SET_DWORD(inbuf, FILTER_OP_IN_RX_DEST,
		       spec->dmaq_id == EFX_FILTER_RX_DMAQ_ID_DROP ?
		       MC_CMD_FILTER_OP_IN_RX_DEST_DROP :
		       MC_CMD_FILTER_OP_IN_RX_DEST_HOST);
	MCDI_SET_DWORD(inbuf, FILTER_OP_IN_TX_DOMAIN, 0);
	MCDI_SET_DWORD(inbuf, FILTER_OP_IN_TX_DEST,
		       MC_CMD_FILTER_OP_IN_TX_DEST_DEFAULT);
	MCDI_SET_DWORD(inbuf, FILTER_OP_IN_RX_QUEUE,
		       spec->dmaq_id == EFX_FILTER_RX_DMAQ_ID_DROP ?
		       0 : spec->dmaq_id);
	MCDI_SET_DWORD(inbuf, FILTER_OP_IN_RX_MODE,
		       (flags & EFX_FILTER_FLAG_RX_RSS) ?
		       MC_CMD_FILTER_OP_IN_RX_MODE_RSS :
		       MC_CMD_FILTER_OP_IN_RX_MODE_SIMPLE);
	अगर (flags & EFX_FILTER_FLAG_RX_RSS)
		MCDI_SET_DWORD(inbuf, FILTER_OP_IN_RX_CONTEXT, ctx->context_id);
पूर्ण

अटल पूर्णांक efx_mcdi_filter_push(काष्ठा efx_nic *efx,
				स्थिर काष्ठा efx_filter_spec *spec, u64 *handle,
				काष्ठा efx_rss_context *ctx, bool replacing)
अणु
	MCDI_DECLARE_BUF(inbuf, MC_CMD_FILTER_OP_EXT_IN_LEN);
	MCDI_DECLARE_BUF(outbuf, MC_CMD_FILTER_OP_EXT_OUT_LEN);
	माप_प्रकार outlen;
	पूर्णांक rc;

	efx_mcdi_filter_push_prep(efx, spec, inbuf, *handle, ctx, replacing);
	rc = efx_mcdi_rpc_quiet(efx, MC_CMD_FILTER_OP, inbuf, माप(inbuf),
				outbuf, माप(outbuf), &outlen);
	अगर (rc && spec->priority != EFX_FILTER_PRI_HINT)
		efx_mcdi_display_error(efx, MC_CMD_FILTER_OP, माप(inbuf),
				       outbuf, outlen, rc);
	अगर (rc == 0)
		*handle = MCDI_QWORD(outbuf, FILTER_OP_OUT_HANDLE);
	अगर (rc == -ENOSPC)
		rc = -EBUSY; /* to match efx_farch_filter_insert() */
	वापस rc;
पूर्ण

अटल u32 efx_mcdi_filter_mcdi_flags_from_spec(स्थिर काष्ठा efx_filter_spec *spec)
अणु
	क्रमागत efx_encap_type encap_type = efx_filter_get_encap_type(spec);
	अचिन्हित पूर्णांक match_flags = spec->match_flags;
	अचिन्हित पूर्णांक uc_match, mc_match;
	u32 mcdi_flags = 0;

#घोषणा MAP_FILTER_TO_MCDI_FLAG(gen_flag, mcdi_field, encap) अणु		\
		अचिन्हित पूर्णांक  old_match_flags = match_flags;		\
		match_flags &= ~EFX_FILTER_MATCH_ ## gen_flag;		\
		अगर (match_flags != old_match_flags)			\
			mcdi_flags |=					\
				(1 << ((encap) ?			\
				       MC_CMD_FILTER_OP_EXT_IN_MATCH_IFRM_ ## \
				       mcdi_field ## _LBN :		\
				       MC_CMD_FILTER_OP_EXT_IN_MATCH_ ##\
				       mcdi_field ## _LBN));		\
	पूर्ण
	/* inner or outer based on encap type */
	MAP_FILTER_TO_MCDI_FLAG(REM_HOST, SRC_IP, encap_type);
	MAP_FILTER_TO_MCDI_FLAG(LOC_HOST, DST_IP, encap_type);
	MAP_FILTER_TO_MCDI_FLAG(REM_MAC, SRC_MAC, encap_type);
	MAP_FILTER_TO_MCDI_FLAG(REM_PORT, SRC_PORT, encap_type);
	MAP_FILTER_TO_MCDI_FLAG(LOC_MAC, DST_MAC, encap_type);
	MAP_FILTER_TO_MCDI_FLAG(LOC_PORT, DST_PORT, encap_type);
	MAP_FILTER_TO_MCDI_FLAG(ETHER_TYPE, ETHER_TYPE, encap_type);
	MAP_FILTER_TO_MCDI_FLAG(IP_PROTO, IP_PROTO, encap_type);
	/* always outer */
	MAP_FILTER_TO_MCDI_FLAG(INNER_VID, INNER_VLAN, false);
	MAP_FILTER_TO_MCDI_FLAG(OUTER_VID, OUTER_VLAN, false);
#अघोषित MAP_FILTER_TO_MCDI_FLAG

	/* special handling क्रम encap type, and mismatch */
	अगर (encap_type) अणु
		match_flags &= ~EFX_FILTER_MATCH_ENCAP_TYPE;
		mcdi_flags |=
			(1 << MC_CMD_FILTER_OP_EXT_IN_MATCH_ETHER_TYPE_LBN);
		mcdi_flags |= (1 << MC_CMD_FILTER_OP_EXT_IN_MATCH_IP_PROTO_LBN);

		uc_match = MC_CMD_FILTER_OP_EXT_IN_MATCH_IFRM_UNKNOWN_UCAST_DST_LBN;
		mc_match = MC_CMD_FILTER_OP_EXT_IN_MATCH_IFRM_UNKNOWN_MCAST_DST_LBN;
	पूर्ण अन्यथा अणु
		uc_match = MC_CMD_FILTER_OP_EXT_IN_MATCH_UNKNOWN_UCAST_DST_LBN;
		mc_match = MC_CMD_FILTER_OP_EXT_IN_MATCH_UNKNOWN_MCAST_DST_LBN;
	पूर्ण

	अगर (match_flags & EFX_FILTER_MATCH_LOC_MAC_IG) अणु
		match_flags &= ~EFX_FILTER_MATCH_LOC_MAC_IG;
		mcdi_flags |=
			is_multicast_ether_addr(spec->loc_mac) ?
			1 << mc_match :
			1 << uc_match;
	पूर्ण

	/* Did we map them all? */
	WARN_ON_ONCE(match_flags);

	वापस mcdi_flags;
पूर्ण

अटल पूर्णांक efx_mcdi_filter_pri(काष्ठा efx_mcdi_filter_table *table,
			       स्थिर काष्ठा efx_filter_spec *spec)
अणु
	u32 mcdi_flags = efx_mcdi_filter_mcdi_flags_from_spec(spec);
	अचिन्हित पूर्णांक match_pri;

	क्रम (match_pri = 0;
	     match_pri < table->rx_match_count;
	     match_pri++)
		अगर (table->rx_match_mcdi_flags[match_pri] == mcdi_flags)
			वापस match_pri;

	वापस -EPROTONOSUPPORT;
पूर्ण

अटल s32 efx_mcdi_filter_insert_locked(काष्ठा efx_nic *efx,
					 काष्ठा efx_filter_spec *spec,
					 bool replace_equal)
अणु
	DECLARE_BITMAP(mc_rem_map, EFX_EF10_FILTER_SEARCH_LIMIT);
	काष्ठा efx_mcdi_filter_table *table;
	काष्ठा efx_filter_spec *saved_spec;
	काष्ठा efx_rss_context *ctx = शून्य;
	अचिन्हित पूर्णांक match_pri, hash;
	अचिन्हित पूर्णांक priv_flags;
	bool rss_locked = false;
	bool replacing = false;
	अचिन्हित पूर्णांक depth, i;
	पूर्णांक ins_index = -1;
	DEFINE_WAIT(रुको);
	bool is_mc_recip;
	s32 rc;

	WARN_ON(!rwsem_is_locked(&efx->filter_sem));
	table = efx->filter_state;
	करोwn_ग_लिखो(&table->lock);

	/* For now, only support RX filters */
	अगर ((spec->flags & (EFX_FILTER_FLAG_RX | EFX_FILTER_FLAG_TX)) !=
	    EFX_FILTER_FLAG_RX) अणु
		rc = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	rc = efx_mcdi_filter_pri(table, spec);
	अगर (rc < 0)
		जाओ out_unlock;
	match_pri = rc;

	hash = efx_filter_spec_hash(spec);
	is_mc_recip = efx_filter_is_mc_recipient(spec);
	अगर (is_mc_recip)
		biपंचांगap_zero(mc_rem_map, EFX_EF10_FILTER_SEARCH_LIMIT);

	अगर (spec->flags & EFX_FILTER_FLAG_RX_RSS) अणु
		mutex_lock(&efx->rss_lock);
		rss_locked = true;
		अगर (spec->rss_context)
			ctx = efx_find_rss_context_entry(efx, spec->rss_context);
		अन्यथा
			ctx = &efx->rss_context;
		अगर (!ctx) अणु
			rc = -ENOENT;
			जाओ out_unlock;
		पूर्ण
		अगर (ctx->context_id == EFX_MCDI_RSS_CONTEXT_INVALID) अणु
			rc = -EOPNOTSUPP;
			जाओ out_unlock;
		पूर्ण
	पूर्ण

	/* Find any existing filters with the same match tuple or
	 * अन्यथा a मुक्त slot to insert at.
	 */
	क्रम (depth = 1; depth < EFX_EF10_FILTER_SEARCH_LIMIT; depth++) अणु
		i = (hash + depth) & (EFX_MCDI_FILTER_TBL_ROWS - 1);
		saved_spec = efx_mcdi_filter_entry_spec(table, i);

		अगर (!saved_spec) अणु
			अगर (ins_index < 0)
				ins_index = i;
		पूर्ण अन्यथा अगर (efx_filter_spec_equal(spec, saved_spec)) अणु
			अगर (spec->priority < saved_spec->priority &&
			    spec->priority != EFX_FILTER_PRI_AUTO) अणु
				rc = -EPERM;
				जाओ out_unlock;
			पूर्ण
			अगर (!is_mc_recip) अणु
				/* This is the only one */
				अगर (spec->priority ==
				    saved_spec->priority &&
				    !replace_equal) अणु
					rc = -EEXIST;
					जाओ out_unlock;
				पूर्ण
				ins_index = i;
				अवरोध;
			पूर्ण अन्यथा अगर (spec->priority >
				   saved_spec->priority ||
				   (spec->priority ==
				    saved_spec->priority &&
				    replace_equal)) अणु
				अगर (ins_index < 0)
					ins_index = i;
				अन्यथा
					__set_bit(depth, mc_rem_map);
			पूर्ण
		पूर्ण
	पूर्ण

	/* Once we reach the maximum search depth, use the first suitable
	 * slot, or वापस -EBUSY अगर there was none
	 */
	अगर (ins_index < 0) अणु
		rc = -EBUSY;
		जाओ out_unlock;
	पूर्ण

	/* Create a software table entry अगर necessary. */
	saved_spec = efx_mcdi_filter_entry_spec(table, ins_index);
	अगर (saved_spec) अणु
		अगर (spec->priority == EFX_FILTER_PRI_AUTO &&
		    saved_spec->priority >= EFX_FILTER_PRI_AUTO) अणु
			/* Just make sure it won't be हटाओd */
			अगर (saved_spec->priority > EFX_FILTER_PRI_AUTO)
				saved_spec->flags |= EFX_FILTER_FLAG_RX_OVER_AUTO;
			table->entry[ins_index].spec &=
				~EFX_EF10_FILTER_FLAG_AUTO_OLD;
			rc = ins_index;
			जाओ out_unlock;
		पूर्ण
		replacing = true;
		priv_flags = efx_mcdi_filter_entry_flags(table, ins_index);
	पूर्ण अन्यथा अणु
		saved_spec = kदो_स्मृति(माप(*spec), GFP_ATOMIC);
		अगर (!saved_spec) अणु
			rc = -ENOMEM;
			जाओ out_unlock;
		पूर्ण
		*saved_spec = *spec;
		priv_flags = 0;
	पूर्ण
	efx_mcdi_filter_set_entry(table, ins_index, saved_spec, priv_flags);

	/* Actually insert the filter on the HW */
	rc = efx_mcdi_filter_push(efx, spec, &table->entry[ins_index].handle,
				  ctx, replacing);

	अगर (rc == -EINVAL && efx->must_पुनः_स्मृति_vis)
		/* The MC rebooted under us, causing it to reject our filter
		 * insertion as poपूर्णांकing to an invalid VI (spec->dmaq_id).
		 */
		rc = -EAGAIN;

	/* Finalise the software table entry */
	अगर (rc == 0) अणु
		अगर (replacing) अणु
			/* Update the fields that may dअगरfer */
			अगर (saved_spec->priority == EFX_FILTER_PRI_AUTO)
				saved_spec->flags |=
					EFX_FILTER_FLAG_RX_OVER_AUTO;
			saved_spec->priority = spec->priority;
			saved_spec->flags &= EFX_FILTER_FLAG_RX_OVER_AUTO;
			saved_spec->flags |= spec->flags;
			saved_spec->rss_context = spec->rss_context;
			saved_spec->dmaq_id = spec->dmaq_id;
		पूर्ण
	पूर्ण अन्यथा अगर (!replacing) अणु
		kमुक्त(saved_spec);
		saved_spec = शून्य;
	पूर्ण अन्यथा अणु
		/* We failed to replace, so the old filter is still present.
		 * Roll back the software table to reflect this.  In fact the
		 * efx_mcdi_filter_set_entry() call below will करो the right
		 * thing, so nothing extra is needed here.
		 */
	पूर्ण
	efx_mcdi_filter_set_entry(table, ins_index, saved_spec, priv_flags);

	/* Remove and finalise entries क्रम lower-priority multicast
	 * recipients
	 */
	अगर (is_mc_recip) अणु
		MCDI_DECLARE_BUF(inbuf, MC_CMD_FILTER_OP_EXT_IN_LEN);
		अचिन्हित पूर्णांक depth, i;

		स_रखो(inbuf, 0, माप(inbuf));

		क्रम (depth = 0; depth < EFX_EF10_FILTER_SEARCH_LIMIT; depth++) अणु
			अगर (!test_bit(depth, mc_rem_map))
				जारी;

			i = (hash + depth) & (EFX_MCDI_FILTER_TBL_ROWS - 1);
			saved_spec = efx_mcdi_filter_entry_spec(table, i);
			priv_flags = efx_mcdi_filter_entry_flags(table, i);

			अगर (rc == 0) अणु
				MCDI_SET_DWORD(inbuf, FILTER_OP_IN_OP,
					       MC_CMD_FILTER_OP_IN_OP_UNSUBSCRIBE);
				MCDI_SET_QWORD(inbuf, FILTER_OP_IN_HANDLE,
					       table->entry[i].handle);
				rc = efx_mcdi_rpc(efx, MC_CMD_FILTER_OP,
						  inbuf, माप(inbuf),
						  शून्य, 0, शून्य);
			पूर्ण

			अगर (rc == 0) अणु
				kमुक्त(saved_spec);
				saved_spec = शून्य;
				priv_flags = 0;
			पूर्ण
			efx_mcdi_filter_set_entry(table, i, saved_spec,
						  priv_flags);
		पूर्ण
	पूर्ण

	/* If successful, वापस the inserted filter ID */
	अगर (rc == 0)
		rc = efx_mcdi_filter_make_filter_id(match_pri, ins_index);

out_unlock:
	अगर (rss_locked)
		mutex_unlock(&efx->rss_lock);
	up_ग_लिखो(&table->lock);
	वापस rc;
पूर्ण

s32 efx_mcdi_filter_insert(काष्ठा efx_nic *efx, काष्ठा efx_filter_spec *spec,
			   bool replace_equal)
अणु
	s32 ret;

	करोwn_पढ़ो(&efx->filter_sem);
	ret = efx_mcdi_filter_insert_locked(efx, spec, replace_equal);
	up_पढ़ो(&efx->filter_sem);

	वापस ret;
पूर्ण

/*
 * Remove a filter.
 * If !by_index, हटाओ by ID
 * If by_index, हटाओ by index
 * Filter ID may come from userland and must be range-checked.
 * Caller must hold efx->filter_sem क्रम पढ़ो, and efx->filter_state->lock
 * क्रम ग_लिखो.
 */
अटल पूर्णांक efx_mcdi_filter_हटाओ_पूर्णांकernal(काष्ठा efx_nic *efx,
					   अचिन्हित पूर्णांक priority_mask,
					   u32 filter_id, bool by_index)
अणु
	अचिन्हित पूर्णांक filter_idx = efx_mcdi_filter_get_unsafe_id(filter_id);
	काष्ठा efx_mcdi_filter_table *table = efx->filter_state;
	MCDI_DECLARE_BUF(inbuf,
			 MC_CMD_FILTER_OP_IN_HANDLE_OFST +
			 MC_CMD_FILTER_OP_IN_HANDLE_LEN);
	काष्ठा efx_filter_spec *spec;
	DEFINE_WAIT(रुको);
	पूर्णांक rc;

	spec = efx_mcdi_filter_entry_spec(table, filter_idx);
	अगर (!spec ||
	    (!by_index &&
	     efx_mcdi_filter_pri(table, spec) !=
	     efx_mcdi_filter_get_unsafe_pri(filter_id)))
		वापस -ENOENT;

	अगर (spec->flags & EFX_FILTER_FLAG_RX_OVER_AUTO &&
	    priority_mask == (1U << EFX_FILTER_PRI_AUTO)) अणु
		/* Just हटाओ flags */
		spec->flags &= ~EFX_FILTER_FLAG_RX_OVER_AUTO;
		table->entry[filter_idx].spec &= ~EFX_EF10_FILTER_FLAG_AUTO_OLD;
		वापस 0;
	पूर्ण

	अगर (!(priority_mask & (1U << spec->priority)))
		वापस -ENOENT;

	अगर (spec->flags & EFX_FILTER_FLAG_RX_OVER_AUTO) अणु
		/* Reset to an स्वतःmatic filter */

		काष्ठा efx_filter_spec new_spec = *spec;

		new_spec.priority = EFX_FILTER_PRI_AUTO;
		new_spec.flags = (EFX_FILTER_FLAG_RX |
				  (efx_rss_active(&efx->rss_context) ?
				   EFX_FILTER_FLAG_RX_RSS : 0));
		new_spec.dmaq_id = 0;
		new_spec.rss_context = 0;
		rc = efx_mcdi_filter_push(efx, &new_spec,
					  &table->entry[filter_idx].handle,
					  &efx->rss_context,
					  true);

		अगर (rc == 0)
			*spec = new_spec;
	पूर्ण अन्यथा अणु
		/* Really हटाओ the filter */

		MCDI_SET_DWORD(inbuf, FILTER_OP_IN_OP,
			       efx_mcdi_filter_is_exclusive(spec) ?
			       MC_CMD_FILTER_OP_IN_OP_REMOVE :
			       MC_CMD_FILTER_OP_IN_OP_UNSUBSCRIBE);
		MCDI_SET_QWORD(inbuf, FILTER_OP_IN_HANDLE,
			       table->entry[filter_idx].handle);
		rc = efx_mcdi_rpc_quiet(efx, MC_CMD_FILTER_OP,
					inbuf, माप(inbuf), शून्य, 0, शून्य);

		अगर ((rc == 0) || (rc == -ENOENT)) अणु
			/* Filter हटाओd OK or didn't actually exist */
			kमुक्त(spec);
			efx_mcdi_filter_set_entry(table, filter_idx, शून्य, 0);
		पूर्ण अन्यथा अणु
			efx_mcdi_display_error(efx, MC_CMD_FILTER_OP,
					       MC_CMD_FILTER_OP_EXT_IN_LEN,
					       शून्य, 0, rc);
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण

/* Remove filters that weren't renewed. */
अटल व्योम efx_mcdi_filter_हटाओ_old(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_mcdi_filter_table *table = efx->filter_state;
	पूर्णांक हटाओ_failed = 0;
	पूर्णांक हटाओ_noent = 0;
	पूर्णांक rc;
	पूर्णांक i;

	करोwn_ग_लिखो(&table->lock);
	क्रम (i = 0; i < EFX_MCDI_FILTER_TBL_ROWS; i++) अणु
		अगर (READ_ONCE(table->entry[i].spec) &
		    EFX_EF10_FILTER_FLAG_AUTO_OLD) अणु
			rc = efx_mcdi_filter_हटाओ_पूर्णांकernal(efx,
					1U << EFX_FILTER_PRI_AUTO, i, true);
			अगर (rc == -ENOENT)
				हटाओ_noent++;
			अन्यथा अगर (rc)
				हटाओ_failed++;
		पूर्ण
	पूर्ण
	up_ग_लिखो(&table->lock);

	अगर (हटाओ_failed)
		netअगर_info(efx, drv, efx->net_dev,
			   "%s: failed to remove %d filters\n",
			   __func__, हटाओ_failed);
	अगर (हटाओ_noent)
		netअगर_info(efx, drv, efx->net_dev,
			   "%s: failed to remove %d non-existent filters\n",
			   __func__, हटाओ_noent);
पूर्ण

पूर्णांक efx_mcdi_filter_हटाओ_safe(काष्ठा efx_nic *efx,
				क्रमागत efx_filter_priority priority,
				u32 filter_id)
अणु
	काष्ठा efx_mcdi_filter_table *table;
	पूर्णांक rc;

	करोwn_पढ़ो(&efx->filter_sem);
	table = efx->filter_state;
	करोwn_ग_लिखो(&table->lock);
	rc = efx_mcdi_filter_हटाओ_पूर्णांकernal(efx, 1U << priority, filter_id,
					     false);
	up_ग_लिखो(&table->lock);
	up_पढ़ो(&efx->filter_sem);
	वापस rc;
पूर्ण

/* Caller must hold efx->filter_sem क्रम पढ़ो */
अटल व्योम efx_mcdi_filter_हटाओ_unsafe(काष्ठा efx_nic *efx,
					  क्रमागत efx_filter_priority priority,
					  u32 filter_id)
अणु
	काष्ठा efx_mcdi_filter_table *table = efx->filter_state;

	अगर (filter_id == EFX_EF10_FILTER_ID_INVALID)
		वापस;

	करोwn_ग_लिखो(&table->lock);
	efx_mcdi_filter_हटाओ_पूर्णांकernal(efx, 1U << priority, filter_id,
					true);
	up_ग_लिखो(&table->lock);
पूर्ण

पूर्णांक efx_mcdi_filter_get_safe(काष्ठा efx_nic *efx,
			     क्रमागत efx_filter_priority priority,
			     u32 filter_id, काष्ठा efx_filter_spec *spec)
अणु
	अचिन्हित पूर्णांक filter_idx = efx_mcdi_filter_get_unsafe_id(filter_id);
	स्थिर काष्ठा efx_filter_spec *saved_spec;
	काष्ठा efx_mcdi_filter_table *table;
	पूर्णांक rc;

	करोwn_पढ़ो(&efx->filter_sem);
	table = efx->filter_state;
	करोwn_पढ़ो(&table->lock);
	saved_spec = efx_mcdi_filter_entry_spec(table, filter_idx);
	अगर (saved_spec && saved_spec->priority == priority &&
	    efx_mcdi_filter_pri(table, saved_spec) ==
	    efx_mcdi_filter_get_unsafe_pri(filter_id)) अणु
		*spec = *saved_spec;
		rc = 0;
	पूर्ण अन्यथा अणु
		rc = -ENOENT;
	पूर्ण
	up_पढ़ो(&table->lock);
	up_पढ़ो(&efx->filter_sem);
	वापस rc;
पूर्ण

अटल पूर्णांक efx_mcdi_filter_insert_addr_list(काष्ठा efx_nic *efx,
					    काष्ठा efx_mcdi_filter_vlan *vlan,
					    bool multicast, bool rollback)
अणु
	काष्ठा efx_mcdi_filter_table *table = efx->filter_state;
	काष्ठा efx_mcdi_dev_addr *addr_list;
	क्रमागत efx_filter_flags filter_flags;
	काष्ठा efx_filter_spec spec;
	u8 baddr[ETH_ALEN];
	अचिन्हित पूर्णांक i, j;
	पूर्णांक addr_count;
	u16 *ids;
	पूर्णांक rc;

	अगर (multicast) अणु
		addr_list = table->dev_mc_list;
		addr_count = table->dev_mc_count;
		ids = vlan->mc;
	पूर्ण अन्यथा अणु
		addr_list = table->dev_uc_list;
		addr_count = table->dev_uc_count;
		ids = vlan->uc;
	पूर्ण

	filter_flags = efx_rss_active(&efx->rss_context) ? EFX_FILTER_FLAG_RX_RSS : 0;

	/* Insert/renew filters */
	क्रम (i = 0; i < addr_count; i++) अणु
		EFX_WARN_ON_PARANOID(ids[i] != EFX_EF10_FILTER_ID_INVALID);
		efx_filter_init_rx(&spec, EFX_FILTER_PRI_AUTO, filter_flags, 0);
		efx_filter_set_eth_local(&spec, vlan->vid, addr_list[i].addr);
		rc = efx_mcdi_filter_insert_locked(efx, &spec, true);
		अगर (rc < 0) अणु
			अगर (rollback) अणु
				netअगर_info(efx, drv, efx->net_dev,
					   "efx_mcdi_filter_insert failed rc=%d\n",
					   rc);
				/* Fall back to promiscuous */
				क्रम (j = 0; j < i; j++) अणु
					efx_mcdi_filter_हटाओ_unsafe(
						efx, EFX_FILTER_PRI_AUTO,
						ids[j]);
					ids[j] = EFX_EF10_FILTER_ID_INVALID;
				पूर्ण
				वापस rc;
			पूर्ण अन्यथा अणु
				/* keep invalid ID, and carry on */
			पूर्ण
		पूर्ण अन्यथा अणु
			ids[i] = efx_mcdi_filter_get_unsafe_id(rc);
		पूर्ण
	पूर्ण

	अगर (multicast && rollback) अणु
		/* Also need an Ethernet broadcast filter */
		EFX_WARN_ON_PARANOID(vlan->शेष_filters[EFX_EF10_BCAST] !=
				     EFX_EF10_FILTER_ID_INVALID);
		efx_filter_init_rx(&spec, EFX_FILTER_PRI_AUTO, filter_flags, 0);
		eth_broadcast_addr(baddr);
		efx_filter_set_eth_local(&spec, vlan->vid, baddr);
		rc = efx_mcdi_filter_insert_locked(efx, &spec, true);
		अगर (rc < 0) अणु
			netअगर_warn(efx, drv, efx->net_dev,
				   "Broadcast filter insert failed rc=%d\n", rc);
			/* Fall back to promiscuous */
			क्रम (j = 0; j < i; j++) अणु
				efx_mcdi_filter_हटाओ_unsafe(
					efx, EFX_FILTER_PRI_AUTO,
					ids[j]);
				ids[j] = EFX_EF10_FILTER_ID_INVALID;
			पूर्ण
			वापस rc;
		पूर्ण अन्यथा अणु
			vlan->शेष_filters[EFX_EF10_BCAST] =
				efx_mcdi_filter_get_unsafe_id(rc);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक efx_mcdi_filter_insert_def(काष्ठा efx_nic *efx,
				      काष्ठा efx_mcdi_filter_vlan *vlan,
				      क्रमागत efx_encap_type encap_type,
				      bool multicast, bool rollback)
अणु
	काष्ठा efx_mcdi_filter_table *table = efx->filter_state;
	क्रमागत efx_filter_flags filter_flags;
	काष्ठा efx_filter_spec spec;
	u8 baddr[ETH_ALEN];
	पूर्णांक rc;
	u16 *id;

	filter_flags = efx_rss_active(&efx->rss_context) ? EFX_FILTER_FLAG_RX_RSS : 0;

	efx_filter_init_rx(&spec, EFX_FILTER_PRI_AUTO, filter_flags, 0);

	अगर (multicast)
		efx_filter_set_mc_def(&spec);
	अन्यथा
		efx_filter_set_uc_def(&spec);

	अगर (encap_type) अणु
		अगर (efx_has_cap(efx, VXLAN_NVGRE))
			efx_filter_set_encap_type(&spec, encap_type);
		अन्यथा
			/*
			 * करोn't insert encap filters on non-supporting
			 * platक्रमms. ID will be left as INVALID.
			 */
			वापस 0;
	पूर्ण

	अगर (vlan->vid != EFX_FILTER_VID_UNSPEC)
		efx_filter_set_eth_local(&spec, vlan->vid, शून्य);

	rc = efx_mcdi_filter_insert_locked(efx, &spec, true);
	अगर (rc < 0) अणु
		स्थिर अक्षर *um = multicast ? "Multicast" : "Unicast";
		स्थिर अक्षर *encap_name = "";
		स्थिर अक्षर *encap_ipv = "";

		अगर ((encap_type & EFX_ENCAP_TYPES_MASK) ==
		    EFX_ENCAP_TYPE_VXLAN)
			encap_name = "VXLAN ";
		अन्यथा अगर ((encap_type & EFX_ENCAP_TYPES_MASK) ==
			 EFX_ENCAP_TYPE_NVGRE)
			encap_name = "NVGRE ";
		अन्यथा अगर ((encap_type & EFX_ENCAP_TYPES_MASK) ==
			 EFX_ENCAP_TYPE_GENEVE)
			encap_name = "GENEVE ";
		अगर (encap_type & EFX_ENCAP_FLAG_IPV6)
			encap_ipv = "IPv6 ";
		अन्यथा अगर (encap_type)
			encap_ipv = "IPv4 ";

		/*
		 * unprivileged functions can't insert mismatch filters
		 * क्रम encapsulated or unicast traffic, so करोwngrade
		 * those warnings to debug.
		 */
		netअगर_cond_dbg(efx, drv, efx->net_dev,
			       rc == -EPERM && (encap_type || !multicast), warn,
			       "%s%s%s mismatch filter insert failed rc=%d\n",
			       encap_name, encap_ipv, um, rc);
	पूर्ण अन्यथा अगर (multicast) अणु
		/* mapping from encap types to शेष filter IDs (multicast) */
		अटल क्रमागत efx_mcdi_filter_शेष_filters map[] = अणु
			[EFX_ENCAP_TYPE_NONE] = EFX_EF10_MCDEF,
			[EFX_ENCAP_TYPE_VXLAN] = EFX_EF10_VXLAN4_MCDEF,
			[EFX_ENCAP_TYPE_NVGRE] = EFX_EF10_NVGRE4_MCDEF,
			[EFX_ENCAP_TYPE_GENEVE] = EFX_EF10_GENEVE4_MCDEF,
			[EFX_ENCAP_TYPE_VXLAN | EFX_ENCAP_FLAG_IPV6] =
				EFX_EF10_VXLAN6_MCDEF,
			[EFX_ENCAP_TYPE_NVGRE | EFX_ENCAP_FLAG_IPV6] =
				EFX_EF10_NVGRE6_MCDEF,
			[EFX_ENCAP_TYPE_GENEVE | EFX_ENCAP_FLAG_IPV6] =
				EFX_EF10_GENEVE6_MCDEF,
		पूर्ण;

		/* quick bounds check (BCAST result impossible) */
		BUILD_BUG_ON(EFX_EF10_BCAST != 0);
		अगर (encap_type >= ARRAY_SIZE(map) || map[encap_type] == 0) अणु
			WARN_ON(1);
			वापस -EINVAL;
		पूर्ण
		/* then follow map */
		id = &vlan->शेष_filters[map[encap_type]];

		EFX_WARN_ON_PARANOID(*id != EFX_EF10_FILTER_ID_INVALID);
		*id = efx_mcdi_filter_get_unsafe_id(rc);
		अगर (!table->mc_chaining && !encap_type) अणु
			/* Also need an Ethernet broadcast filter */
			efx_filter_init_rx(&spec, EFX_FILTER_PRI_AUTO,
					   filter_flags, 0);
			eth_broadcast_addr(baddr);
			efx_filter_set_eth_local(&spec, vlan->vid, baddr);
			rc = efx_mcdi_filter_insert_locked(efx, &spec, true);
			अगर (rc < 0) अणु
				netअगर_warn(efx, drv, efx->net_dev,
					   "Broadcast filter insert failed rc=%d\n",
					   rc);
				अगर (rollback) अणु
					/* Roll back the mc_def filter */
					efx_mcdi_filter_हटाओ_unsafe(
							efx, EFX_FILTER_PRI_AUTO,
							*id);
					*id = EFX_EF10_FILTER_ID_INVALID;
					वापस rc;
				पूर्ण
			पूर्ण अन्यथा अणु
				EFX_WARN_ON_PARANOID(
					vlan->शेष_filters[EFX_EF10_BCAST] !=
					EFX_EF10_FILTER_ID_INVALID);
				vlan->शेष_filters[EFX_EF10_BCAST] =
					efx_mcdi_filter_get_unsafe_id(rc);
			पूर्ण
		पूर्ण
		rc = 0;
	पूर्ण अन्यथा अणु
		/* mapping from encap types to शेष filter IDs (unicast) */
		अटल क्रमागत efx_mcdi_filter_शेष_filters map[] = अणु
			[EFX_ENCAP_TYPE_NONE] = EFX_EF10_UCDEF,
			[EFX_ENCAP_TYPE_VXLAN] = EFX_EF10_VXLAN4_UCDEF,
			[EFX_ENCAP_TYPE_NVGRE] = EFX_EF10_NVGRE4_UCDEF,
			[EFX_ENCAP_TYPE_GENEVE] = EFX_EF10_GENEVE4_UCDEF,
			[EFX_ENCAP_TYPE_VXLAN | EFX_ENCAP_FLAG_IPV6] =
				EFX_EF10_VXLAN6_UCDEF,
			[EFX_ENCAP_TYPE_NVGRE | EFX_ENCAP_FLAG_IPV6] =
				EFX_EF10_NVGRE6_UCDEF,
			[EFX_ENCAP_TYPE_GENEVE | EFX_ENCAP_FLAG_IPV6] =
				EFX_EF10_GENEVE6_UCDEF,
		पूर्ण;

		/* quick bounds check (BCAST result impossible) */
		BUILD_BUG_ON(EFX_EF10_BCAST != 0);
		अगर (encap_type >= ARRAY_SIZE(map) || map[encap_type] == 0) अणु
			WARN_ON(1);
			वापस -EINVAL;
		पूर्ण
		/* then follow map */
		id = &vlan->शेष_filters[map[encap_type]];
		EFX_WARN_ON_PARANOID(*id != EFX_EF10_FILTER_ID_INVALID);
		*id = rc;
		rc = 0;
	पूर्ण
	वापस rc;
पूर्ण

/*
 * Caller must hold efx->filter_sem क्रम पढ़ो अगर race against
 * efx_mcdi_filter_table_हटाओ() is possible
 */
अटल व्योम efx_mcdi_filter_vlan_sync_rx_mode(काष्ठा efx_nic *efx,
					      काष्ठा efx_mcdi_filter_vlan *vlan)
अणु
	काष्ठा efx_mcdi_filter_table *table = efx->filter_state;

	/*
	 * Do not install unspecअगरied VID अगर VLAN filtering is enabled.
	 * Do not install all specअगरied VIDs अगर VLAN filtering is disabled.
	 */
	अगर ((vlan->vid == EFX_FILTER_VID_UNSPEC) == table->vlan_filter)
		वापस;

	/* Insert/renew unicast filters */
	अगर (table->uc_promisc) अणु
		efx_mcdi_filter_insert_def(efx, vlan, EFX_ENCAP_TYPE_NONE,
					   false, false);
		efx_mcdi_filter_insert_addr_list(efx, vlan, false, false);
	पूर्ण अन्यथा अणु
		/*
		 * If any of the filters failed to insert, fall back to
		 * promiscuous mode - add in the uc_def filter.  But keep
		 * our inभागidual unicast filters.
		 */
		अगर (efx_mcdi_filter_insert_addr_list(efx, vlan, false, false))
			efx_mcdi_filter_insert_def(efx, vlan,
						   EFX_ENCAP_TYPE_NONE,
						   false, false);
	पूर्ण
	efx_mcdi_filter_insert_def(efx, vlan, EFX_ENCAP_TYPE_VXLAN,
				   false, false);
	efx_mcdi_filter_insert_def(efx, vlan, EFX_ENCAP_TYPE_VXLAN |
					      EFX_ENCAP_FLAG_IPV6,
				   false, false);
	efx_mcdi_filter_insert_def(efx, vlan, EFX_ENCAP_TYPE_NVGRE,
				   false, false);
	efx_mcdi_filter_insert_def(efx, vlan, EFX_ENCAP_TYPE_NVGRE |
					      EFX_ENCAP_FLAG_IPV6,
				   false, false);
	efx_mcdi_filter_insert_def(efx, vlan, EFX_ENCAP_TYPE_GENEVE,
				   false, false);
	efx_mcdi_filter_insert_def(efx, vlan, EFX_ENCAP_TYPE_GENEVE |
					      EFX_ENCAP_FLAG_IPV6,
				   false, false);

	/*
	 * Insert/renew multicast filters
	 *
	 * If changing promiscuous state with cascaded multicast filters, हटाओ
	 * old filters first, so that packets are dropped rather than duplicated
	 */
	अगर (table->mc_chaining && table->mc_promisc_last != table->mc_promisc)
		efx_mcdi_filter_हटाओ_old(efx);
	अगर (table->mc_promisc) अणु
		अगर (table->mc_chaining) अणु
			/*
			 * If we failed to insert promiscuous filters, rollback
			 * and fall back to inभागidual multicast filters
			 */
			अगर (efx_mcdi_filter_insert_def(efx, vlan,
						       EFX_ENCAP_TYPE_NONE,
						       true, true)) अणु
				/* Changing promisc state, so हटाओ old filters */
				efx_mcdi_filter_हटाओ_old(efx);
				efx_mcdi_filter_insert_addr_list(efx, vlan,
								 true, false);
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			 * If we failed to insert promiscuous filters, करोn't
			 * rollback.  Regardless, also insert the mc_list,
			 * unless it's incomplete due to overflow
			 */
			efx_mcdi_filter_insert_def(efx, vlan,
						   EFX_ENCAP_TYPE_NONE,
						   true, false);
			अगर (!table->mc_overflow)
				efx_mcdi_filter_insert_addr_list(efx, vlan,
								 true, false);
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * If any filters failed to insert, rollback and fall back to
		 * promiscuous mode - mc_def filter and maybe broadcast.  If
		 * that fails, roll back again and insert as many of our
		 * inभागidual multicast filters as we can.
		 */
		अगर (efx_mcdi_filter_insert_addr_list(efx, vlan, true, true)) अणु
			/* Changing promisc state, so हटाओ old filters */
			अगर (table->mc_chaining)
				efx_mcdi_filter_हटाओ_old(efx);
			अगर (efx_mcdi_filter_insert_def(efx, vlan,
						       EFX_ENCAP_TYPE_NONE,
						       true, true))
				efx_mcdi_filter_insert_addr_list(efx, vlan,
								 true, false);
		पूर्ण
	पूर्ण
	efx_mcdi_filter_insert_def(efx, vlan, EFX_ENCAP_TYPE_VXLAN,
				   true, false);
	efx_mcdi_filter_insert_def(efx, vlan, EFX_ENCAP_TYPE_VXLAN |
					      EFX_ENCAP_FLAG_IPV6,
				   true, false);
	efx_mcdi_filter_insert_def(efx, vlan, EFX_ENCAP_TYPE_NVGRE,
				   true, false);
	efx_mcdi_filter_insert_def(efx, vlan, EFX_ENCAP_TYPE_NVGRE |
					      EFX_ENCAP_FLAG_IPV6,
				   true, false);
	efx_mcdi_filter_insert_def(efx, vlan, EFX_ENCAP_TYPE_GENEVE,
				   true, false);
	efx_mcdi_filter_insert_def(efx, vlan, EFX_ENCAP_TYPE_GENEVE |
					      EFX_ENCAP_FLAG_IPV6,
				   true, false);
पूर्ण

पूर्णांक efx_mcdi_filter_clear_rx(काष्ठा efx_nic *efx,
			     क्रमागत efx_filter_priority priority)
अणु
	काष्ठा efx_mcdi_filter_table *table;
	अचिन्हित पूर्णांक priority_mask;
	अचिन्हित पूर्णांक i;
	पूर्णांक rc;

	priority_mask = (((1U << (priority + 1)) - 1) &
			 ~(1U << EFX_FILTER_PRI_AUTO));

	करोwn_पढ़ो(&efx->filter_sem);
	table = efx->filter_state;
	करोwn_ग_लिखो(&table->lock);
	क्रम (i = 0; i < EFX_MCDI_FILTER_TBL_ROWS; i++) अणु
		rc = efx_mcdi_filter_हटाओ_पूर्णांकernal(efx, priority_mask,
						     i, true);
		अगर (rc && rc != -ENOENT)
			अवरोध;
		rc = 0;
	पूर्ण

	up_ग_लिखो(&table->lock);
	up_पढ़ो(&efx->filter_sem);
	वापस rc;
पूर्ण

u32 efx_mcdi_filter_count_rx_used(काष्ठा efx_nic *efx,
				 क्रमागत efx_filter_priority priority)
अणु
	काष्ठा efx_mcdi_filter_table *table;
	अचिन्हित पूर्णांक filter_idx;
	s32 count = 0;

	करोwn_पढ़ो(&efx->filter_sem);
	table = efx->filter_state;
	करोwn_पढ़ो(&table->lock);
	क्रम (filter_idx = 0; filter_idx < EFX_MCDI_FILTER_TBL_ROWS; filter_idx++) अणु
		अगर (table->entry[filter_idx].spec &&
		    efx_mcdi_filter_entry_spec(table, filter_idx)->priority ==
		    priority)
			++count;
	पूर्ण
	up_पढ़ो(&table->lock);
	up_पढ़ो(&efx->filter_sem);
	वापस count;
पूर्ण

u32 efx_mcdi_filter_get_rx_id_limit(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_mcdi_filter_table *table = efx->filter_state;

	वापस table->rx_match_count * EFX_MCDI_FILTER_TBL_ROWS * 2;
पूर्ण

s32 efx_mcdi_filter_get_rx_ids(काष्ठा efx_nic *efx,
			       क्रमागत efx_filter_priority priority,
			       u32 *buf, u32 size)
अणु
	काष्ठा efx_mcdi_filter_table *table;
	काष्ठा efx_filter_spec *spec;
	अचिन्हित पूर्णांक filter_idx;
	s32 count = 0;

	करोwn_पढ़ो(&efx->filter_sem);
	table = efx->filter_state;
	करोwn_पढ़ो(&table->lock);

	क्रम (filter_idx = 0; filter_idx < EFX_MCDI_FILTER_TBL_ROWS; filter_idx++) अणु
		spec = efx_mcdi_filter_entry_spec(table, filter_idx);
		अगर (spec && spec->priority == priority) अणु
			अगर (count == size) अणु
				count = -EMSGSIZE;
				अवरोध;
			पूर्ण
			buf[count++] =
				efx_mcdi_filter_make_filter_id(
					efx_mcdi_filter_pri(table, spec),
					filter_idx);
		पूर्ण
	पूर्ण
	up_पढ़ो(&table->lock);
	up_पढ़ो(&efx->filter_sem);
	वापस count;
पूर्ण

अटल पूर्णांक efx_mcdi_filter_match_flags_from_mcdi(bool encap, u32 mcdi_flags)
अणु
	पूर्णांक match_flags = 0;

#घोषणा MAP_FLAG(gen_flag, mcdi_field) करो अणु				\
		u32 old_mcdi_flags = mcdi_flags;			\
		mcdi_flags &= ~(1 << MC_CMD_FILTER_OP_EXT_IN_MATCH_ ##	\
				     mcdi_field ## _LBN);		\
		अगर (mcdi_flags != old_mcdi_flags)			\
			match_flags |= EFX_FILTER_MATCH_ ## gen_flag;	\
	पूर्ण जबतक (0)

	अगर (encap) अणु
		/* encap filters must specअगरy encap type */
		match_flags |= EFX_FILTER_MATCH_ENCAP_TYPE;
		/* and imply ethertype and ip proto */
		mcdi_flags &=
			~(1 << MC_CMD_FILTER_OP_EXT_IN_MATCH_IP_PROTO_LBN);
		mcdi_flags &=
			~(1 << MC_CMD_FILTER_OP_EXT_IN_MATCH_ETHER_TYPE_LBN);
		/* VLAN tags refer to the outer packet */
		MAP_FLAG(INNER_VID, INNER_VLAN);
		MAP_FLAG(OUTER_VID, OUTER_VLAN);
		/* everything अन्यथा refers to the inner packet */
		MAP_FLAG(LOC_MAC_IG, IFRM_UNKNOWN_UCAST_DST);
		MAP_FLAG(LOC_MAC_IG, IFRM_UNKNOWN_MCAST_DST);
		MAP_FLAG(REM_HOST, IFRM_SRC_IP);
		MAP_FLAG(LOC_HOST, IFRM_DST_IP);
		MAP_FLAG(REM_MAC, IFRM_SRC_MAC);
		MAP_FLAG(REM_PORT, IFRM_SRC_PORT);
		MAP_FLAG(LOC_MAC, IFRM_DST_MAC);
		MAP_FLAG(LOC_PORT, IFRM_DST_PORT);
		MAP_FLAG(ETHER_TYPE, IFRM_ETHER_TYPE);
		MAP_FLAG(IP_PROTO, IFRM_IP_PROTO);
	पूर्ण अन्यथा अणु
		MAP_FLAG(LOC_MAC_IG, UNKNOWN_UCAST_DST);
		MAP_FLAG(LOC_MAC_IG, UNKNOWN_MCAST_DST);
		MAP_FLAG(REM_HOST, SRC_IP);
		MAP_FLAG(LOC_HOST, DST_IP);
		MAP_FLAG(REM_MAC, SRC_MAC);
		MAP_FLAG(REM_PORT, SRC_PORT);
		MAP_FLAG(LOC_MAC, DST_MAC);
		MAP_FLAG(LOC_PORT, DST_PORT);
		MAP_FLAG(ETHER_TYPE, ETHER_TYPE);
		MAP_FLAG(INNER_VID, INNER_VLAN);
		MAP_FLAG(OUTER_VID, OUTER_VLAN);
		MAP_FLAG(IP_PROTO, IP_PROTO);
	पूर्ण
#अघोषित MAP_FLAG

	/* Did we map them all? */
	अगर (mcdi_flags)
		वापस -EINVAL;

	वापस match_flags;
पूर्ण

bool efx_mcdi_filter_match_supported(काष्ठा efx_mcdi_filter_table *table,
				     bool encap,
				     क्रमागत efx_filter_match_flags match_flags)
अणु
	अचिन्हित पूर्णांक match_pri;
	पूर्णांक mf;

	क्रम (match_pri = 0;
	     match_pri < table->rx_match_count;
	     match_pri++) अणु
		mf = efx_mcdi_filter_match_flags_from_mcdi(encap,
				table->rx_match_mcdi_flags[match_pri]);
		अगर (mf == match_flags)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक
efx_mcdi_filter_table_probe_matches(काष्ठा efx_nic *efx,
				    काष्ठा efx_mcdi_filter_table *table,
				    bool encap)
अणु
	MCDI_DECLARE_BUF(inbuf, MC_CMD_GET_PARSER_DISP_INFO_IN_LEN);
	MCDI_DECLARE_BUF(outbuf, MC_CMD_GET_PARSER_DISP_INFO_OUT_LENMAX);
	अचिन्हित पूर्णांक pd_match_pri, pd_match_count;
	माप_प्रकार outlen;
	पूर्णांक rc;

	/* Find out which RX filter types are supported, and their priorities */
	MCDI_SET_DWORD(inbuf, GET_PARSER_DISP_INFO_IN_OP,
		       encap ?
		       MC_CMD_GET_PARSER_DISP_INFO_IN_OP_GET_SUPPORTED_ENCAP_RX_MATCHES :
		       MC_CMD_GET_PARSER_DISP_INFO_IN_OP_GET_SUPPORTED_RX_MATCHES);
	rc = efx_mcdi_rpc(efx, MC_CMD_GET_PARSER_DISP_INFO,
			  inbuf, माप(inbuf), outbuf, माप(outbuf),
			  &outlen);
	अगर (rc)
		वापस rc;

	pd_match_count = MCDI_VAR_ARRAY_LEN(
		outlen, GET_PARSER_DISP_INFO_OUT_SUPPORTED_MATCHES);

	क्रम (pd_match_pri = 0; pd_match_pri < pd_match_count; pd_match_pri++) अणु
		u32 mcdi_flags =
			MCDI_ARRAY_DWORD(
				outbuf,
				GET_PARSER_DISP_INFO_OUT_SUPPORTED_MATCHES,
				pd_match_pri);
		rc = efx_mcdi_filter_match_flags_from_mcdi(encap, mcdi_flags);
		अगर (rc < 0) अणु
			netअगर_dbg(efx, probe, efx->net_dev,
				  "%s: fw flags %#x pri %u not supported in driver\n",
				  __func__, mcdi_flags, pd_match_pri);
		पूर्ण अन्यथा अणु
			netअगर_dbg(efx, probe, efx->net_dev,
				  "%s: fw flags %#x pri %u supported as driver flags %#x pri %u\n",
				  __func__, mcdi_flags, pd_match_pri,
				  rc, table->rx_match_count);
			table->rx_match_mcdi_flags[table->rx_match_count] = mcdi_flags;
			table->rx_match_count++;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक efx_mcdi_filter_table_probe(काष्ठा efx_nic *efx, bool multicast_chaining)
अणु
	काष्ठा net_device *net_dev = efx->net_dev;
	काष्ठा efx_mcdi_filter_table *table;
	पूर्णांक rc;

	अगर (!efx_rwsem_निश्चित_ग_लिखो_locked(&efx->filter_sem))
		वापस -EINVAL;

	अगर (efx->filter_state) /* alपढ़ोy probed */
		वापस 0;

	table = kzalloc(माप(*table), GFP_KERNEL);
	अगर (!table)
		वापस -ENOMEM;

	table->mc_chaining = multicast_chaining;
	table->rx_match_count = 0;
	rc = efx_mcdi_filter_table_probe_matches(efx, table, false);
	अगर (rc)
		जाओ fail;
	अगर (efx_has_cap(efx, VXLAN_NVGRE))
		rc = efx_mcdi_filter_table_probe_matches(efx, table, true);
	अगर (rc)
		जाओ fail;
	अगर ((efx_supported_features(efx) & NETIF_F_HW_VLAN_CTAG_FILTER) &&
	    !(efx_mcdi_filter_match_supported(table, false,
		(EFX_FILTER_MATCH_OUTER_VID | EFX_FILTER_MATCH_LOC_MAC)) &&
	      efx_mcdi_filter_match_supported(table, false,
		(EFX_FILTER_MATCH_OUTER_VID | EFX_FILTER_MATCH_LOC_MAC_IG)))) अणु
		netअगर_info(efx, probe, net_dev,
			   "VLAN filters are not supported in this firmware variant\n");
		net_dev->features &= ~NETIF_F_HW_VLAN_CTAG_FILTER;
		efx->fixed_features &= ~NETIF_F_HW_VLAN_CTAG_FILTER;
		net_dev->hw_features &= ~NETIF_F_HW_VLAN_CTAG_FILTER;
	पूर्ण

	table->entry = vzalloc(array_size(EFX_MCDI_FILTER_TBL_ROWS,
					  माप(*table->entry)));
	अगर (!table->entry) अणु
		rc = -ENOMEM;
		जाओ fail;
	पूर्ण

	table->mc_promisc_last = false;
	table->vlan_filter =
		!!(efx->net_dev->features & NETIF_F_HW_VLAN_CTAG_FILTER);
	INIT_LIST_HEAD(&table->vlan_list);
	init_rwsem(&table->lock);

	efx->filter_state = table;

	वापस 0;
fail:
	kमुक्त(table);
	वापस rc;
पूर्ण

व्योम efx_mcdi_filter_table_reset_mc_allocations(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_mcdi_filter_table *table = efx->filter_state;

	अगर (table) अणु
		table->must_restore_filters = true;
		table->must_restore_rss_contexts = true;
	पूर्ण
पूर्ण

/*
 * Caller must hold efx->filter_sem क्रम पढ़ो अगर race against
 * efx_mcdi_filter_table_हटाओ() is possible
 */
व्योम efx_mcdi_filter_table_restore(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_mcdi_filter_table *table = efx->filter_state;
	अचिन्हित पूर्णांक invalid_filters = 0, failed = 0;
	काष्ठा efx_mcdi_filter_vlan *vlan;
	काष्ठा efx_filter_spec *spec;
	काष्ठा efx_rss_context *ctx;
	अचिन्हित पूर्णांक filter_idx;
	u32 mcdi_flags;
	पूर्णांक match_pri;
	पूर्णांक rc, i;

	WARN_ON(!rwsem_is_locked(&efx->filter_sem));

	अगर (!table || !table->must_restore_filters)
		वापस;

	करोwn_ग_लिखो(&table->lock);
	mutex_lock(&efx->rss_lock);

	क्रम (filter_idx = 0; filter_idx < EFX_MCDI_FILTER_TBL_ROWS; filter_idx++) अणु
		spec = efx_mcdi_filter_entry_spec(table, filter_idx);
		अगर (!spec)
			जारी;

		mcdi_flags = efx_mcdi_filter_mcdi_flags_from_spec(spec);
		match_pri = 0;
		जबतक (match_pri < table->rx_match_count &&
		       table->rx_match_mcdi_flags[match_pri] != mcdi_flags)
			++match_pri;
		अगर (match_pri >= table->rx_match_count) अणु
			invalid_filters++;
			जाओ not_restored;
		पूर्ण
		अगर (spec->rss_context)
			ctx = efx_find_rss_context_entry(efx, spec->rss_context);
		अन्यथा
			ctx = &efx->rss_context;
		अगर (spec->flags & EFX_FILTER_FLAG_RX_RSS) अणु
			अगर (!ctx) अणु
				netअगर_warn(efx, drv, efx->net_dev,
					   "Warning: unable to restore a filter with nonexistent RSS context %u.\n",
					   spec->rss_context);
				invalid_filters++;
				जाओ not_restored;
			पूर्ण
			अगर (ctx->context_id == EFX_MCDI_RSS_CONTEXT_INVALID) अणु
				netअगर_warn(efx, drv, efx->net_dev,
					   "Warning: unable to restore a filter with RSS context %u as it was not created.\n",
					   spec->rss_context);
				invalid_filters++;
				जाओ not_restored;
			पूर्ण
		पूर्ण

		rc = efx_mcdi_filter_push(efx, spec,
					  &table->entry[filter_idx].handle,
					  ctx, false);
		अगर (rc)
			failed++;

		अगर (rc) अणु
not_restored:
			list_क्रम_each_entry(vlan, &table->vlan_list, list)
				क्रम (i = 0; i < EFX_EF10_NUM_DEFAULT_FILTERS; ++i)
					अगर (vlan->शेष_filters[i] == filter_idx)
						vlan->शेष_filters[i] =
							EFX_EF10_FILTER_ID_INVALID;

			kमुक्त(spec);
			efx_mcdi_filter_set_entry(table, filter_idx, शून्य, 0);
		पूर्ण
	पूर्ण

	mutex_unlock(&efx->rss_lock);
	up_ग_लिखो(&table->lock);

	/*
	 * This can happen validly अगर the MC's capabilities have changed, so
	 * is not an error.
	 */
	अगर (invalid_filters)
		netअगर_dbg(efx, drv, efx->net_dev,
			  "Did not restore %u filters that are now unsupported.\n",
			  invalid_filters);

	अगर (failed)
		netअगर_err(efx, hw, efx->net_dev,
			  "unable to restore %u filters\n", failed);
	अन्यथा
		table->must_restore_filters = false;
पूर्ण

व्योम efx_mcdi_filter_table_करोwn(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_mcdi_filter_table *table = efx->filter_state;
	MCDI_DECLARE_BUF(inbuf, MC_CMD_FILTER_OP_EXT_IN_LEN);
	काष्ठा efx_filter_spec *spec;
	अचिन्हित पूर्णांक filter_idx;
	पूर्णांक rc;

	अगर (!table)
		वापस;

	efx_mcdi_filter_cleanup_vlans(efx);

	क्रम (filter_idx = 0; filter_idx < EFX_MCDI_FILTER_TBL_ROWS; filter_idx++) अणु
		spec = efx_mcdi_filter_entry_spec(table, filter_idx);
		अगर (!spec)
			जारी;

		MCDI_SET_DWORD(inbuf, FILTER_OP_IN_OP,
			       efx_mcdi_filter_is_exclusive(spec) ?
			       MC_CMD_FILTER_OP_IN_OP_REMOVE :
			       MC_CMD_FILTER_OP_IN_OP_UNSUBSCRIBE);
		MCDI_SET_QWORD(inbuf, FILTER_OP_IN_HANDLE,
			       table->entry[filter_idx].handle);
		rc = efx_mcdi_rpc_quiet(efx, MC_CMD_FILTER_OP, inbuf,
					माप(inbuf), शून्य, 0, शून्य);
		अगर (rc)
			netअगर_info(efx, drv, efx->net_dev,
				   "%s: filter %04x remove failed\n",
				   __func__, filter_idx);
		kमुक्त(spec);
	पूर्ण
पूर्ण

व्योम efx_mcdi_filter_table_हटाओ(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_mcdi_filter_table *table = efx->filter_state;

	efx_mcdi_filter_table_करोwn(efx);

	efx->filter_state = शून्य;
	/*
	 * If we were called without locking, then it's not safe to मुक्त
	 * the table as others might be using it.  So we just WARN, leak
	 * the memory, and potentially get an inconsistent filter table
	 * state.
	 * This should never actually happen.
	 */
	अगर (!efx_rwsem_निश्चित_ग_लिखो_locked(&efx->filter_sem))
		वापस;

	अगर (!table)
		वापस;

	vमुक्त(table->entry);
	kमुक्त(table);
पूर्ण

अटल व्योम efx_mcdi_filter_mark_one_old(काष्ठा efx_nic *efx, uपूर्णांक16_t *id)
अणु
	काष्ठा efx_mcdi_filter_table *table = efx->filter_state;
	अचिन्हित पूर्णांक filter_idx;

	efx_rwsem_निश्चित_ग_लिखो_locked(&table->lock);

	अगर (*id != EFX_EF10_FILTER_ID_INVALID) अणु
		filter_idx = efx_mcdi_filter_get_unsafe_id(*id);
		अगर (!table->entry[filter_idx].spec)
			netअगर_dbg(efx, drv, efx->net_dev,
				  "marked null spec old %04x:%04x\n", *id,
				  filter_idx);
		table->entry[filter_idx].spec |= EFX_EF10_FILTER_FLAG_AUTO_OLD;
		*id = EFX_EF10_FILTER_ID_INVALID;
	पूर्ण
पूर्ण

/* Mark old per-VLAN filters that may need to be हटाओd */
अटल व्योम _efx_mcdi_filter_vlan_mark_old(काष्ठा efx_nic *efx,
					   काष्ठा efx_mcdi_filter_vlan *vlan)
अणु
	काष्ठा efx_mcdi_filter_table *table = efx->filter_state;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < table->dev_uc_count; i++)
		efx_mcdi_filter_mark_one_old(efx, &vlan->uc[i]);
	क्रम (i = 0; i < table->dev_mc_count; i++)
		efx_mcdi_filter_mark_one_old(efx, &vlan->mc[i]);
	क्रम (i = 0; i < EFX_EF10_NUM_DEFAULT_FILTERS; i++)
		efx_mcdi_filter_mark_one_old(efx, &vlan->शेष_filters[i]);
पूर्ण

/*
 * Mark old filters that may need to be हटाओd.
 * Caller must hold efx->filter_sem क्रम पढ़ो अगर race against
 * efx_mcdi_filter_table_हटाओ() is possible
 */
अटल व्योम efx_mcdi_filter_mark_old(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_mcdi_filter_table *table = efx->filter_state;
	काष्ठा efx_mcdi_filter_vlan *vlan;

	करोwn_ग_लिखो(&table->lock);
	list_क्रम_each_entry(vlan, &table->vlan_list, list)
		_efx_mcdi_filter_vlan_mark_old(efx, vlan);
	up_ग_लिखो(&table->lock);
पूर्ण

पूर्णांक efx_mcdi_filter_add_vlan(काष्ठा efx_nic *efx, u16 vid)
अणु
	काष्ठा efx_mcdi_filter_table *table = efx->filter_state;
	काष्ठा efx_mcdi_filter_vlan *vlan;
	अचिन्हित पूर्णांक i;

	अगर (!efx_rwsem_निश्चित_ग_लिखो_locked(&efx->filter_sem))
		वापस -EINVAL;

	vlan = efx_mcdi_filter_find_vlan(efx, vid);
	अगर (WARN_ON(vlan)) अणु
		netअगर_err(efx, drv, efx->net_dev,
			  "VLAN %u already added\n", vid);
		वापस -EALREADY;
	पूर्ण

	vlan = kzalloc(माप(*vlan), GFP_KERNEL);
	अगर (!vlan)
		वापस -ENOMEM;

	vlan->vid = vid;

	क्रम (i = 0; i < ARRAY_SIZE(vlan->uc); i++)
		vlan->uc[i] = EFX_EF10_FILTER_ID_INVALID;
	क्रम (i = 0; i < ARRAY_SIZE(vlan->mc); i++)
		vlan->mc[i] = EFX_EF10_FILTER_ID_INVALID;
	क्रम (i = 0; i < EFX_EF10_NUM_DEFAULT_FILTERS; i++)
		vlan->शेष_filters[i] = EFX_EF10_FILTER_ID_INVALID;

	list_add_tail(&vlan->list, &table->vlan_list);

	अगर (efx_dev_रेजिस्टरed(efx))
		efx_mcdi_filter_vlan_sync_rx_mode(efx, vlan);

	वापस 0;
पूर्ण

अटल व्योम efx_mcdi_filter_del_vlan_पूर्णांकernal(काष्ठा efx_nic *efx,
					      काष्ठा efx_mcdi_filter_vlan *vlan)
अणु
	अचिन्हित पूर्णांक i;

	/* See comment in efx_mcdi_filter_table_हटाओ() */
	अगर (!efx_rwsem_निश्चित_ग_लिखो_locked(&efx->filter_sem))
		वापस;

	list_del(&vlan->list);

	क्रम (i = 0; i < ARRAY_SIZE(vlan->uc); i++)
		efx_mcdi_filter_हटाओ_unsafe(efx, EFX_FILTER_PRI_AUTO,
					      vlan->uc[i]);
	क्रम (i = 0; i < ARRAY_SIZE(vlan->mc); i++)
		efx_mcdi_filter_हटाओ_unsafe(efx, EFX_FILTER_PRI_AUTO,
					      vlan->mc[i]);
	क्रम (i = 0; i < EFX_EF10_NUM_DEFAULT_FILTERS; i++)
		अगर (vlan->शेष_filters[i] != EFX_EF10_FILTER_ID_INVALID)
			efx_mcdi_filter_हटाओ_unsafe(efx, EFX_FILTER_PRI_AUTO,
						      vlan->शेष_filters[i]);

	kमुक्त(vlan);
पूर्ण

व्योम efx_mcdi_filter_del_vlan(काष्ठा efx_nic *efx, u16 vid)
अणु
	काष्ठा efx_mcdi_filter_vlan *vlan;

	/* See comment in efx_mcdi_filter_table_हटाओ() */
	अगर (!efx_rwsem_निश्चित_ग_लिखो_locked(&efx->filter_sem))
		वापस;

	vlan = efx_mcdi_filter_find_vlan(efx, vid);
	अगर (!vlan) अणु
		netअगर_err(efx, drv, efx->net_dev,
			  "VLAN %u not found in filter state\n", vid);
		वापस;
	पूर्ण

	efx_mcdi_filter_del_vlan_पूर्णांकernal(efx, vlan);
पूर्ण

काष्ठा efx_mcdi_filter_vlan *efx_mcdi_filter_find_vlan(काष्ठा efx_nic *efx,
						       u16 vid)
अणु
	काष्ठा efx_mcdi_filter_table *table = efx->filter_state;
	काष्ठा efx_mcdi_filter_vlan *vlan;

	WARN_ON(!rwsem_is_locked(&efx->filter_sem));

	list_क्रम_each_entry(vlan, &table->vlan_list, list) अणु
		अगर (vlan->vid == vid)
			वापस vlan;
	पूर्ण

	वापस शून्य;
पूर्ण

व्योम efx_mcdi_filter_cleanup_vlans(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_mcdi_filter_table *table = efx->filter_state;
	काष्ठा efx_mcdi_filter_vlan *vlan, *next_vlan;

	/* See comment in efx_mcdi_filter_table_हटाओ() */
	अगर (!efx_rwsem_निश्चित_ग_लिखो_locked(&efx->filter_sem))
		वापस;

	अगर (!table)
		वापस;

	list_क्रम_each_entry_safe(vlan, next_vlan, &table->vlan_list, list)
		efx_mcdi_filter_del_vlan_पूर्णांकernal(efx, vlan);
पूर्ण

अटल व्योम efx_mcdi_filter_uc_addr_list(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_mcdi_filter_table *table = efx->filter_state;
	काष्ठा net_device *net_dev = efx->net_dev;
	काष्ठा netdev_hw_addr *uc;
	अचिन्हित पूर्णांक i;

	table->uc_promisc = !!(net_dev->flags & IFF_PROMISC);
	ether_addr_copy(table->dev_uc_list[0].addr, net_dev->dev_addr);
	i = 1;
	netdev_क्रम_each_uc_addr(uc, net_dev) अणु
		अगर (i >= EFX_EF10_FILTER_DEV_UC_MAX) अणु
			table->uc_promisc = true;
			अवरोध;
		पूर्ण
		ether_addr_copy(table->dev_uc_list[i].addr, uc->addr);
		i++;
	पूर्ण

	table->dev_uc_count = i;
पूर्ण

अटल व्योम efx_mcdi_filter_mc_addr_list(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_mcdi_filter_table *table = efx->filter_state;
	काष्ठा net_device *net_dev = efx->net_dev;
	काष्ठा netdev_hw_addr *mc;
	अचिन्हित पूर्णांक i;

	table->mc_overflow = false;
	table->mc_promisc = !!(net_dev->flags & (IFF_PROMISC | IFF_ALLMULTI));

	i = 0;
	netdev_क्रम_each_mc_addr(mc, net_dev) अणु
		अगर (i >= EFX_EF10_FILTER_DEV_MC_MAX) अणु
			table->mc_promisc = true;
			table->mc_overflow = true;
			अवरोध;
		पूर्ण
		ether_addr_copy(table->dev_mc_list[i].addr, mc->addr);
		i++;
	पूर्ण

	table->dev_mc_count = i;
पूर्ण

/*
 * Caller must hold efx->filter_sem क्रम पढ़ो अगर race against
 * efx_mcdi_filter_table_हटाओ() is possible
 */
व्योम efx_mcdi_filter_sync_rx_mode(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_mcdi_filter_table *table = efx->filter_state;
	काष्ठा net_device *net_dev = efx->net_dev;
	काष्ठा efx_mcdi_filter_vlan *vlan;
	bool vlan_filter;

	अगर (!efx_dev_रेजिस्टरed(efx))
		वापस;

	अगर (!table)
		वापस;

	efx_mcdi_filter_mark_old(efx);

	/*
	 * Copy/convert the address lists; add the primary station
	 * address and broadcast address
	 */
	netअगर_addr_lock_bh(net_dev);
	efx_mcdi_filter_uc_addr_list(efx);
	efx_mcdi_filter_mc_addr_list(efx);
	netअगर_addr_unlock_bh(net_dev);

	/*
	 * If VLAN filtering changes, all old filters are finally हटाओd.
	 * Do it in advance to aव्योम conflicts क्रम unicast untagged and
	 * VLAN 0 tagged filters.
	 */
	vlan_filter = !!(net_dev->features & NETIF_F_HW_VLAN_CTAG_FILTER);
	अगर (table->vlan_filter != vlan_filter) अणु
		table->vlan_filter = vlan_filter;
		efx_mcdi_filter_हटाओ_old(efx);
	पूर्ण

	list_क्रम_each_entry(vlan, &table->vlan_list, list)
		efx_mcdi_filter_vlan_sync_rx_mode(efx, vlan);

	efx_mcdi_filter_हटाओ_old(efx);
	table->mc_promisc_last = table->mc_promisc;
पूर्ण

#अगर_घोषित CONFIG_RFS_ACCEL

bool efx_mcdi_filter_rfs_expire_one(काष्ठा efx_nic *efx, u32 flow_id,
				    अचिन्हित पूर्णांक filter_idx)
अणु
	काष्ठा efx_filter_spec *spec, saved_spec;
	काष्ठा efx_mcdi_filter_table *table;
	काष्ठा efx_arfs_rule *rule = शून्य;
	bool ret = true, क्रमce = false;
	u16 arfs_id;

	करोwn_पढ़ो(&efx->filter_sem);
	table = efx->filter_state;
	करोwn_ग_लिखो(&table->lock);
	spec = efx_mcdi_filter_entry_spec(table, filter_idx);

	अगर (!spec || spec->priority != EFX_FILTER_PRI_HINT)
		जाओ out_unlock;

	spin_lock_bh(&efx->rps_hash_lock);
	अगर (!efx->rps_hash_table) अणु
		/* In the असलence of the table, we always वापस 0 to ARFS. */
		arfs_id = 0;
	पूर्ण अन्यथा अणु
		rule = efx_rps_hash_find(efx, spec);
		अगर (!rule)
			/* ARFS table करोesn't know of this filter, so हटाओ it */
			जाओ expire;
		arfs_id = rule->arfs_id;
		ret = efx_rps_check_rule(rule, filter_idx, &क्रमce);
		अगर (क्रमce)
			जाओ expire;
		अगर (!ret) अणु
			spin_unlock_bh(&efx->rps_hash_lock);
			जाओ out_unlock;
		पूर्ण
	पूर्ण
	अगर (!rps_may_expire_flow(efx->net_dev, spec->dmaq_id, flow_id, arfs_id))
		ret = false;
	अन्यथा अगर (rule)
		rule->filter_id = EFX_ARFS_FILTER_ID_REMOVING;
expire:
	saved_spec = *spec; /* हटाओ operation will kमुक्त spec */
	spin_unlock_bh(&efx->rps_hash_lock);
	/*
	 * At this poपूर्णांक (since we dropped the lock), another thपढ़ो might queue
	 * up a fresh insertion request (but the actual insertion will be held
	 * up by our possession of the filter table lock).  In that हाल, it
	 * will set rule->filter_id to EFX_ARFS_FILTER_ID_PENDING, meaning that
	 * the rule is not हटाओd by efx_rps_hash_del() below.
	 */
	अगर (ret)
		ret = efx_mcdi_filter_हटाओ_पूर्णांकernal(efx, 1U << spec->priority,
						      filter_idx, true) == 0;
	/*
	 * While we can't safely dereference rule (we dropped the lock), we can
	 * still test it क्रम शून्य.
	 */
	अगर (ret && rule) अणु
		/* Expiring, so हटाओ entry from ARFS table */
		spin_lock_bh(&efx->rps_hash_lock);
		efx_rps_hash_del(efx, &saved_spec);
		spin_unlock_bh(&efx->rps_hash_lock);
	पूर्ण
out_unlock:
	up_ग_लिखो(&table->lock);
	up_पढ़ो(&efx->filter_sem);
	वापस ret;
पूर्ण

#पूर्ण_अगर /* CONFIG_RFS_ACCEL */

#घोषणा RSS_MODE_HASH_ADDRS	(1 << RSS_MODE_HASH_SRC_ADDR_LBN |\
				 1 << RSS_MODE_HASH_DST_ADDR_LBN)
#घोषणा RSS_MODE_HASH_PORTS	(1 << RSS_MODE_HASH_SRC_PORT_LBN |\
				 1 << RSS_MODE_HASH_DST_PORT_LBN)
#घोषणा RSS_CONTEXT_FLAGS_DEFAULT	(1 << MC_CMD_RSS_CONTEXT_GET_FLAGS_OUT_TOEPLITZ_IPV4_EN_LBN |\
					 1 << MC_CMD_RSS_CONTEXT_GET_FLAGS_OUT_TOEPLITZ_TCPV4_EN_LBN |\
					 1 << MC_CMD_RSS_CONTEXT_GET_FLAGS_OUT_TOEPLITZ_IPV6_EN_LBN |\
					 1 << MC_CMD_RSS_CONTEXT_GET_FLAGS_OUT_TOEPLITZ_TCPV6_EN_LBN |\
					 (RSS_MODE_HASH_ADDRS | RSS_MODE_HASH_PORTS) << MC_CMD_RSS_CONTEXT_GET_FLAGS_OUT_TCP_IPV4_RSS_MODE_LBN |\
					 RSS_MODE_HASH_ADDRS << MC_CMD_RSS_CONTEXT_GET_FLAGS_OUT_UDP_IPV4_RSS_MODE_LBN |\
					 RSS_MODE_HASH_ADDRS << MC_CMD_RSS_CONTEXT_GET_FLAGS_OUT_OTHER_IPV4_RSS_MODE_LBN |\
					 (RSS_MODE_HASH_ADDRS | RSS_MODE_HASH_PORTS) << MC_CMD_RSS_CONTEXT_GET_FLAGS_OUT_TCP_IPV6_RSS_MODE_LBN |\
					 RSS_MODE_HASH_ADDRS << MC_CMD_RSS_CONTEXT_GET_FLAGS_OUT_UDP_IPV6_RSS_MODE_LBN |\
					 RSS_MODE_HASH_ADDRS << MC_CMD_RSS_CONTEXT_GET_FLAGS_OUT_OTHER_IPV6_RSS_MODE_LBN)

पूर्णांक efx_mcdi_get_rss_context_flags(काष्ठा efx_nic *efx, u32 context, u32 *flags)
अणु
	/*
	 * Firmware had a bug (sfc bug 61952) where it would not actually
	 * fill in the flags field in the response to MC_CMD_RSS_CONTEXT_GET_FLAGS.
	 * This meant that it would always contain whatever was previously
	 * in the MCDI buffer.  Fortunately, all firmware versions with
	 * this bug have the same शेष flags value क्रम a newly-allocated
	 * RSS context, and the only समय we want to get the flags is just
	 * after allocating.  Moreover, the response has a 32-bit hole
	 * where the context ID would be in the request, so we can use an
	 * overlength buffer in the request and pre-fill the flags field
	 * with what we believe the शेष to be.  Thus अगर the firmware
	 * has the bug, it will leave our pre-filled value in the flags
	 * field of the response, and we will get the right answer.
	 *
	 * However, this करोes mean that this function should NOT be used अगर
	 * the RSS context flags might not be their शेषs - it is ONLY
	 * reliably correct क्रम a newly-allocated RSS context.
	 */
	MCDI_DECLARE_BUF(inbuf, MC_CMD_RSS_CONTEXT_GET_FLAGS_OUT_LEN);
	MCDI_DECLARE_BUF(outbuf, MC_CMD_RSS_CONTEXT_GET_FLAGS_OUT_LEN);
	माप_प्रकार outlen;
	पूर्णांक rc;

	/* Check we have a hole क्रम the context ID */
	BUILD_BUG_ON(MC_CMD_RSS_CONTEXT_GET_FLAGS_IN_LEN != MC_CMD_RSS_CONTEXT_GET_FLAGS_OUT_FLAGS_OFST);
	MCDI_SET_DWORD(inbuf, RSS_CONTEXT_GET_FLAGS_IN_RSS_CONTEXT_ID, context);
	MCDI_SET_DWORD(inbuf, RSS_CONTEXT_GET_FLAGS_OUT_FLAGS,
		       RSS_CONTEXT_FLAGS_DEFAULT);
	rc = efx_mcdi_rpc(efx, MC_CMD_RSS_CONTEXT_GET_FLAGS, inbuf,
			  माप(inbuf), outbuf, माप(outbuf), &outlen);
	अगर (rc == 0) अणु
		अगर (outlen < MC_CMD_RSS_CONTEXT_GET_FLAGS_OUT_LEN)
			rc = -EIO;
		अन्यथा
			*flags = MCDI_DWORD(outbuf, RSS_CONTEXT_GET_FLAGS_OUT_FLAGS);
	पूर्ण
	वापस rc;
पूर्ण

/*
 * Attempt to enable 4-tuple UDP hashing on the specअगरied RSS context.
 * If we fail, we just leave the RSS context at its शेष hash settings,
 * which is safe but may slightly reduce perक्रमmance.
 * Defaults are 4-tuple क्रम TCP and 2-tuple क्रम UDP and other-IP, so we
 * just need to set the UDP ports flags (क्रम both IP versions).
 */
व्योम efx_mcdi_set_rss_context_flags(काष्ठा efx_nic *efx,
				    काष्ठा efx_rss_context *ctx)
अणु
	MCDI_DECLARE_BUF(inbuf, MC_CMD_RSS_CONTEXT_SET_FLAGS_IN_LEN);
	u32 flags;

	BUILD_BUG_ON(MC_CMD_RSS_CONTEXT_SET_FLAGS_OUT_LEN != 0);

	अगर (efx_mcdi_get_rss_context_flags(efx, ctx->context_id, &flags) != 0)
		वापस;
	MCDI_SET_DWORD(inbuf, RSS_CONTEXT_SET_FLAGS_IN_RSS_CONTEXT_ID,
		       ctx->context_id);
	flags |= RSS_MODE_HASH_PORTS << MC_CMD_RSS_CONTEXT_GET_FLAGS_OUT_UDP_IPV4_RSS_MODE_LBN;
	flags |= RSS_MODE_HASH_PORTS << MC_CMD_RSS_CONTEXT_GET_FLAGS_OUT_UDP_IPV6_RSS_MODE_LBN;
	MCDI_SET_DWORD(inbuf, RSS_CONTEXT_SET_FLAGS_IN_FLAGS, flags);
	अगर (!efx_mcdi_rpc(efx, MC_CMD_RSS_CONTEXT_SET_FLAGS, inbuf, माप(inbuf),
			  शून्य, 0, शून्य))
		/* Succeeded, so UDP 4-tuple is now enabled */
		ctx->rx_hash_udp_4tuple = true;
पूर्ण

अटल पूर्णांक efx_mcdi_filter_alloc_rss_context(काष्ठा efx_nic *efx, bool exclusive,
					     काष्ठा efx_rss_context *ctx,
					     अचिन्हित *context_size)
अणु
	MCDI_DECLARE_BUF(inbuf, MC_CMD_RSS_CONTEXT_ALLOC_IN_LEN);
	MCDI_DECLARE_BUF(outbuf, MC_CMD_RSS_CONTEXT_ALLOC_OUT_LEN);
	माप_प्रकार outlen;
	पूर्णांक rc;
	u32 alloc_type = exclusive ?
				MC_CMD_RSS_CONTEXT_ALLOC_IN_TYPE_EXCLUSIVE :
				MC_CMD_RSS_CONTEXT_ALLOC_IN_TYPE_SHARED;
	अचिन्हित rss_spपढ़ो = exclusive ?
				efx->rss_spपढ़ो :
				min(roundकरोwn_घात_of_two(efx->rss_spपढ़ो),
				    EFX_EF10_MAX_SHARED_RSS_CONTEXT_SIZE);

	अगर (!exclusive && rss_spपढ़ो == 1) अणु
		ctx->context_id = EFX_MCDI_RSS_CONTEXT_INVALID;
		अगर (context_size)
			*context_size = 1;
		वापस 0;
	पूर्ण

	अगर (efx_has_cap(efx, RX_RSS_LIMITED))
		वापस -EOPNOTSUPP;

	MCDI_SET_DWORD(inbuf, RSS_CONTEXT_ALLOC_IN_UPSTREAM_PORT_ID,
		       efx->vport_id);
	MCDI_SET_DWORD(inbuf, RSS_CONTEXT_ALLOC_IN_TYPE, alloc_type);
	MCDI_SET_DWORD(inbuf, RSS_CONTEXT_ALLOC_IN_NUM_QUEUES, rss_spपढ़ो);

	rc = efx_mcdi_rpc(efx, MC_CMD_RSS_CONTEXT_ALLOC, inbuf, माप(inbuf),
		outbuf, माप(outbuf), &outlen);
	अगर (rc != 0)
		वापस rc;

	अगर (outlen < MC_CMD_RSS_CONTEXT_ALLOC_OUT_LEN)
		वापस -EIO;

	ctx->context_id = MCDI_DWORD(outbuf, RSS_CONTEXT_ALLOC_OUT_RSS_CONTEXT_ID);

	अगर (context_size)
		*context_size = rss_spपढ़ो;

	अगर (efx_has_cap(efx, ADDITIONAL_RSS_MODES))
		efx_mcdi_set_rss_context_flags(efx, ctx);

	वापस 0;
पूर्ण

अटल पूर्णांक efx_mcdi_filter_मुक्त_rss_context(काष्ठा efx_nic *efx, u32 context)
अणु
	MCDI_DECLARE_BUF(inbuf, MC_CMD_RSS_CONTEXT_FREE_IN_LEN);

	MCDI_SET_DWORD(inbuf, RSS_CONTEXT_FREE_IN_RSS_CONTEXT_ID,
		       context);
	वापस efx_mcdi_rpc(efx, MC_CMD_RSS_CONTEXT_FREE, inbuf, माप(inbuf),
			    शून्य, 0, शून्य);
पूर्ण

अटल पूर्णांक efx_mcdi_filter_populate_rss_table(काष्ठा efx_nic *efx, u32 context,
				       स्थिर u32 *rx_indir_table, स्थिर u8 *key)
अणु
	MCDI_DECLARE_BUF(tablebuf, MC_CMD_RSS_CONTEXT_SET_TABLE_IN_LEN);
	MCDI_DECLARE_BUF(keybuf, MC_CMD_RSS_CONTEXT_SET_KEY_IN_LEN);
	पूर्णांक i, rc;

	MCDI_SET_DWORD(tablebuf, RSS_CONTEXT_SET_TABLE_IN_RSS_CONTEXT_ID,
		       context);
	BUILD_BUG_ON(ARRAY_SIZE(efx->rss_context.rx_indir_table) !=
		     MC_CMD_RSS_CONTEXT_SET_TABLE_IN_INसूचीECTION_TABLE_LEN);

	/* This iterates over the length of efx->rss_context.rx_indir_table, but
	 * copies bytes from rx_indir_table.  That's because the latter is a
	 * poपूर्णांकer rather than an array, but should have the same length.
	 * The efx->rss_context.rx_hash_key loop below is similar.
	 */
	क्रम (i = 0; i < ARRAY_SIZE(efx->rss_context.rx_indir_table); ++i)
		MCDI_PTR(tablebuf,
			 RSS_CONTEXT_SET_TABLE_IN_INसूचीECTION_TABLE)[i] =
				(u8) rx_indir_table[i];

	rc = efx_mcdi_rpc(efx, MC_CMD_RSS_CONTEXT_SET_TABLE, tablebuf,
			  माप(tablebuf), शून्य, 0, शून्य);
	अगर (rc != 0)
		वापस rc;

	MCDI_SET_DWORD(keybuf, RSS_CONTEXT_SET_KEY_IN_RSS_CONTEXT_ID,
		       context);
	BUILD_BUG_ON(ARRAY_SIZE(efx->rss_context.rx_hash_key) !=
		     MC_CMD_RSS_CONTEXT_SET_KEY_IN_TOEPLITZ_KEY_LEN);
	क्रम (i = 0; i < ARRAY_SIZE(efx->rss_context.rx_hash_key); ++i)
		MCDI_PTR(keybuf, RSS_CONTEXT_SET_KEY_IN_TOEPLITZ_KEY)[i] = key[i];

	वापस efx_mcdi_rpc(efx, MC_CMD_RSS_CONTEXT_SET_KEY, keybuf,
			    माप(keybuf), शून्य, 0, शून्य);
पूर्ण

व्योम efx_mcdi_rx_मुक्त_indir_table(काष्ठा efx_nic *efx)
अणु
	पूर्णांक rc;

	अगर (efx->rss_context.context_id != EFX_MCDI_RSS_CONTEXT_INVALID) अणु
		rc = efx_mcdi_filter_मुक्त_rss_context(efx, efx->rss_context.context_id);
		WARN_ON(rc != 0);
	पूर्ण
	efx->rss_context.context_id = EFX_MCDI_RSS_CONTEXT_INVALID;
पूर्ण

अटल पूर्णांक efx_mcdi_filter_rx_push_shared_rss_config(काष्ठा efx_nic *efx,
					      अचिन्हित *context_size)
अणु
	काष्ठा efx_mcdi_filter_table *table = efx->filter_state;
	पूर्णांक rc = efx_mcdi_filter_alloc_rss_context(efx, false, &efx->rss_context,
					    context_size);

	अगर (rc != 0)
		वापस rc;

	table->rx_rss_context_exclusive = false;
	efx_set_शेष_rx_indir_table(efx, &efx->rss_context);
	वापस 0;
पूर्ण

अटल पूर्णांक efx_mcdi_filter_rx_push_exclusive_rss_config(काष्ठा efx_nic *efx,
						 स्थिर u32 *rx_indir_table,
						 स्थिर u8 *key)
अणु
	काष्ठा efx_mcdi_filter_table *table = efx->filter_state;
	u32 old_rx_rss_context = efx->rss_context.context_id;
	पूर्णांक rc;

	अगर (efx->rss_context.context_id == EFX_MCDI_RSS_CONTEXT_INVALID ||
	    !table->rx_rss_context_exclusive) अणु
		rc = efx_mcdi_filter_alloc_rss_context(efx, true, &efx->rss_context,
						शून्य);
		अगर (rc == -EOPNOTSUPP)
			वापस rc;
		अन्यथा अगर (rc != 0)
			जाओ fail1;
	पूर्ण

	rc = efx_mcdi_filter_populate_rss_table(efx, efx->rss_context.context_id,
					 rx_indir_table, key);
	अगर (rc != 0)
		जाओ fail2;

	अगर (efx->rss_context.context_id != old_rx_rss_context &&
	    old_rx_rss_context != EFX_MCDI_RSS_CONTEXT_INVALID)
		WARN_ON(efx_mcdi_filter_मुक्त_rss_context(efx, old_rx_rss_context) != 0);
	table->rx_rss_context_exclusive = true;
	अगर (rx_indir_table != efx->rss_context.rx_indir_table)
		स_नकल(efx->rss_context.rx_indir_table, rx_indir_table,
		       माप(efx->rss_context.rx_indir_table));
	अगर (key != efx->rss_context.rx_hash_key)
		स_नकल(efx->rss_context.rx_hash_key, key,
		       efx->type->rx_hash_key_size);

	वापस 0;

fail2:
	अगर (old_rx_rss_context != efx->rss_context.context_id) अणु
		WARN_ON(efx_mcdi_filter_मुक्त_rss_context(efx, efx->rss_context.context_id) != 0);
		efx->rss_context.context_id = old_rx_rss_context;
	पूर्ण
fail1:
	netअगर_err(efx, hw, efx->net_dev, "%s: failed rc=%d\n", __func__, rc);
	वापस rc;
पूर्ण

पूर्णांक efx_mcdi_rx_push_rss_context_config(काष्ठा efx_nic *efx,
					काष्ठा efx_rss_context *ctx,
					स्थिर u32 *rx_indir_table,
					स्थिर u8 *key)
अणु
	पूर्णांक rc;

	WARN_ON(!mutex_is_locked(&efx->rss_lock));

	अगर (ctx->context_id == EFX_MCDI_RSS_CONTEXT_INVALID) अणु
		rc = efx_mcdi_filter_alloc_rss_context(efx, true, ctx, शून्य);
		अगर (rc)
			वापस rc;
	पूर्ण

	अगर (!rx_indir_table) /* Delete this context */
		वापस efx_mcdi_filter_मुक्त_rss_context(efx, ctx->context_id);

	rc = efx_mcdi_filter_populate_rss_table(efx, ctx->context_id,
					 rx_indir_table, key);
	अगर (rc)
		वापस rc;

	स_नकल(ctx->rx_indir_table, rx_indir_table,
	       माप(efx->rss_context.rx_indir_table));
	स_नकल(ctx->rx_hash_key, key, efx->type->rx_hash_key_size);

	वापस 0;
पूर्ण

पूर्णांक efx_mcdi_rx_pull_rss_context_config(काष्ठा efx_nic *efx,
					काष्ठा efx_rss_context *ctx)
अणु
	MCDI_DECLARE_BUF(inbuf, MC_CMD_RSS_CONTEXT_GET_TABLE_IN_LEN);
	MCDI_DECLARE_BUF(tablebuf, MC_CMD_RSS_CONTEXT_GET_TABLE_OUT_LEN);
	MCDI_DECLARE_BUF(keybuf, MC_CMD_RSS_CONTEXT_GET_KEY_OUT_LEN);
	माप_प्रकार outlen;
	पूर्णांक rc, i;

	WARN_ON(!mutex_is_locked(&efx->rss_lock));

	BUILD_BUG_ON(MC_CMD_RSS_CONTEXT_GET_TABLE_IN_LEN !=
		     MC_CMD_RSS_CONTEXT_GET_KEY_IN_LEN);

	अगर (ctx->context_id == EFX_MCDI_RSS_CONTEXT_INVALID)
		वापस -ENOENT;

	MCDI_SET_DWORD(inbuf, RSS_CONTEXT_GET_TABLE_IN_RSS_CONTEXT_ID,
		       ctx->context_id);
	BUILD_BUG_ON(ARRAY_SIZE(ctx->rx_indir_table) !=
		     MC_CMD_RSS_CONTEXT_GET_TABLE_OUT_INसूचीECTION_TABLE_LEN);
	rc = efx_mcdi_rpc(efx, MC_CMD_RSS_CONTEXT_GET_TABLE, inbuf, माप(inbuf),
			  tablebuf, माप(tablebuf), &outlen);
	अगर (rc != 0)
		वापस rc;

	अगर (WARN_ON(outlen != MC_CMD_RSS_CONTEXT_GET_TABLE_OUT_LEN))
		वापस -EIO;

	क्रम (i = 0; i < ARRAY_SIZE(ctx->rx_indir_table); i++)
		ctx->rx_indir_table[i] = MCDI_PTR(tablebuf,
				RSS_CONTEXT_GET_TABLE_OUT_INसूचीECTION_TABLE)[i];

	MCDI_SET_DWORD(inbuf, RSS_CONTEXT_GET_KEY_IN_RSS_CONTEXT_ID,
		       ctx->context_id);
	BUILD_BUG_ON(ARRAY_SIZE(ctx->rx_hash_key) !=
		     MC_CMD_RSS_CONTEXT_SET_KEY_IN_TOEPLITZ_KEY_LEN);
	rc = efx_mcdi_rpc(efx, MC_CMD_RSS_CONTEXT_GET_KEY, inbuf, माप(inbuf),
			  keybuf, माप(keybuf), &outlen);
	अगर (rc != 0)
		वापस rc;

	अगर (WARN_ON(outlen != MC_CMD_RSS_CONTEXT_GET_KEY_OUT_LEN))
		वापस -EIO;

	क्रम (i = 0; i < ARRAY_SIZE(ctx->rx_hash_key); ++i)
		ctx->rx_hash_key[i] = MCDI_PTR(
				keybuf, RSS_CONTEXT_GET_KEY_OUT_TOEPLITZ_KEY)[i];

	वापस 0;
पूर्ण

पूर्णांक efx_mcdi_rx_pull_rss_config(काष्ठा efx_nic *efx)
अणु
	पूर्णांक rc;

	mutex_lock(&efx->rss_lock);
	rc = efx_mcdi_rx_pull_rss_context_config(efx, &efx->rss_context);
	mutex_unlock(&efx->rss_lock);
	वापस rc;
पूर्ण

व्योम efx_mcdi_rx_restore_rss_contexts(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_mcdi_filter_table *table = efx->filter_state;
	काष्ठा efx_rss_context *ctx;
	पूर्णांक rc;

	WARN_ON(!mutex_is_locked(&efx->rss_lock));

	अगर (!table->must_restore_rss_contexts)
		वापस;

	list_क्रम_each_entry(ctx, &efx->rss_context.list, list) अणु
		/* previous NIC RSS context is gone */
		ctx->context_id = EFX_MCDI_RSS_CONTEXT_INVALID;
		/* so try to allocate a new one */
		rc = efx_mcdi_rx_push_rss_context_config(efx, ctx,
							 ctx->rx_indir_table,
							 ctx->rx_hash_key);
		अगर (rc)
			netअगर_warn(efx, probe, efx->net_dev,
				   "failed to restore RSS context %u, rc=%d"
				   "; RSS filters may fail to be applied\n",
				   ctx->user_id, rc);
	पूर्ण
	table->must_restore_rss_contexts = false;
पूर्ण

पूर्णांक efx_mcdi_pf_rx_push_rss_config(काष्ठा efx_nic *efx, bool user,
				   स्थिर u32 *rx_indir_table,
				   स्थिर u8 *key)
अणु
	पूर्णांक rc;

	अगर (efx->rss_spपढ़ो == 1)
		वापस 0;

	अगर (!key)
		key = efx->rss_context.rx_hash_key;

	rc = efx_mcdi_filter_rx_push_exclusive_rss_config(efx, rx_indir_table, key);

	अगर (rc == -ENOBUFS && !user) अणु
		अचिन्हित context_size;
		bool mismatch = false;
		माप_प्रकार i;

		क्रम (i = 0;
		     i < ARRAY_SIZE(efx->rss_context.rx_indir_table) && !mismatch;
		     i++)
			mismatch = rx_indir_table[i] !=
				ethtool_rxfh_indir_शेष(i, efx->rss_spपढ़ो);

		rc = efx_mcdi_filter_rx_push_shared_rss_config(efx, &context_size);
		अगर (rc == 0) अणु
			अगर (context_size != efx->rss_spपढ़ो)
				netअगर_warn(efx, probe, efx->net_dev,
					   "Could not allocate an exclusive RSS"
					   " context; allocated a shared one of"
					   " different size."
					   " Wanted %u, got %u.\n",
					   efx->rss_spपढ़ो, context_size);
			अन्यथा अगर (mismatch)
				netअगर_warn(efx, probe, efx->net_dev,
					   "Could not allocate an exclusive RSS"
					   " context; allocated a shared one but"
					   " could not apply custom"
					   " indirection.\n");
			अन्यथा
				netअगर_info(efx, probe, efx->net_dev,
					   "Could not allocate an exclusive RSS"
					   " context; allocated a shared one.\n");
		पूर्ण
	पूर्ण
	वापस rc;
पूर्ण

पूर्णांक efx_mcdi_vf_rx_push_rss_config(काष्ठा efx_nic *efx, bool user,
				   स्थिर u32 *rx_indir_table
				   __attribute__ ((unused)),
				   स्थिर u8 *key
				   __attribute__ ((unused)))
अणु
	अगर (user)
		वापस -EOPNOTSUPP;
	अगर (efx->rss_context.context_id != EFX_MCDI_RSS_CONTEXT_INVALID)
		वापस 0;
	वापस efx_mcdi_filter_rx_push_shared_rss_config(efx, शून्य);
पूर्ण

पूर्णांक efx_mcdi_push_शेष_indir_table(काष्ठा efx_nic *efx,
				      अचिन्हित पूर्णांक rss_spपढ़ो)
अणु
	पूर्णांक rc = 0;

	अगर (efx->rss_spपढ़ो == rss_spपढ़ो)
		वापस 0;

	efx->rss_spपढ़ो = rss_spपढ़ो;
	अगर (!efx->filter_state)
		वापस 0;

	efx_mcdi_rx_मुक्त_indir_table(efx);
	अगर (rss_spपढ़ो > 1) अणु
		efx_set_शेष_rx_indir_table(efx, &efx->rss_context);
		rc = efx->type->rx_push_rss_config(efx, false,
				   efx->rss_context.rx_indir_table, शून्य);
	पूर्ण
	वापस rc;
पूर्ण
