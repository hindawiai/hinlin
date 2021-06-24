<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (C) 2018-2020, Intel Corporation. */

/* flow director ethtool support क्रम ice */

#समावेश "ice.h"
#समावेश "ice_lib.h"
#समावेश "ice_flow.h"

अटल काष्ठा in6_addr full_ipv6_addr_mask = अणु
	.in6_u = अणु
		.u6_addr8 = अणु
			0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
			0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		पूर्ण
	पूर्ण
पूर्ण;

अटल काष्ठा in6_addr zero_ipv6_addr_mask = अणु
	.in6_u = अणु
		.u6_addr8 = अणु
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		पूर्ण
	पूर्ण
पूर्ण;

/* calls to ice_flow_add_prof require the number of segments in the array
 * क्रम segs_cnt. In this code that is one more than the index.
 */
#घोषणा TNL_SEG_CNT(_TNL_) ((_TNL_) + 1)

/**
 * ice_fltr_to_ethtool_flow - convert filter type values to ethtool
 * flow type values
 * @flow: filter type to be converted
 *
 * Returns the corresponding ethtool flow type.
 */
अटल पूर्णांक ice_fltr_to_ethtool_flow(क्रमागत ice_fltr_ptype flow)
अणु
	चयन (flow) अणु
	हाल ICE_FLTR_PTYPE_NONF_IPV4_TCP:
		वापस TCP_V4_FLOW;
	हाल ICE_FLTR_PTYPE_NONF_IPV4_UDP:
		वापस UDP_V4_FLOW;
	हाल ICE_FLTR_PTYPE_NONF_IPV4_SCTP:
		वापस SCTP_V4_FLOW;
	हाल ICE_FLTR_PTYPE_NONF_IPV4_OTHER:
		वापस IPV4_USER_FLOW;
	हाल ICE_FLTR_PTYPE_NONF_IPV6_TCP:
		वापस TCP_V6_FLOW;
	हाल ICE_FLTR_PTYPE_NONF_IPV6_UDP:
		वापस UDP_V6_FLOW;
	हाल ICE_FLTR_PTYPE_NONF_IPV6_SCTP:
		वापस SCTP_V6_FLOW;
	हाल ICE_FLTR_PTYPE_NONF_IPV6_OTHER:
		वापस IPV6_USER_FLOW;
	शेष:
		/* 0 is undefined ethtool flow */
		वापस 0;
	पूर्ण
पूर्ण

/**
 * ice_ethtool_flow_to_fltr - convert ethtool flow type to filter क्रमागत
 * @eth: Ethtool flow type to be converted
 *
 * Returns flow क्रमागत
 */
अटल क्रमागत ice_fltr_ptype ice_ethtool_flow_to_fltr(पूर्णांक eth)
अणु
	चयन (eth) अणु
	हाल TCP_V4_FLOW:
		वापस ICE_FLTR_PTYPE_NONF_IPV4_TCP;
	हाल UDP_V4_FLOW:
		वापस ICE_FLTR_PTYPE_NONF_IPV4_UDP;
	हाल SCTP_V4_FLOW:
		वापस ICE_FLTR_PTYPE_NONF_IPV4_SCTP;
	हाल IPV4_USER_FLOW:
		वापस ICE_FLTR_PTYPE_NONF_IPV4_OTHER;
	हाल TCP_V6_FLOW:
		वापस ICE_FLTR_PTYPE_NONF_IPV6_TCP;
	हाल UDP_V6_FLOW:
		वापस ICE_FLTR_PTYPE_NONF_IPV6_UDP;
	हाल SCTP_V6_FLOW:
		वापस ICE_FLTR_PTYPE_NONF_IPV6_SCTP;
	हाल IPV6_USER_FLOW:
		वापस ICE_FLTR_PTYPE_NONF_IPV6_OTHER;
	शेष:
		वापस ICE_FLTR_PTYPE_NONF_NONE;
	पूर्ण
पूर्ण

/**
 * ice_is_mask_valid - check mask field set
 * @mask: full mask to check
 * @field: field क्रम which mask should be valid
 *
 * If the mask is fully set वापस true. If it is not valid क्रम field वापस
 * false.
 */
अटल bool ice_is_mask_valid(u64 mask, u64 field)
अणु
	वापस (mask & field) == field;
पूर्ण

/**
 * ice_get_ethtool_fdir_entry - fill ethtool काष्ठाure with fdir filter data
 * @hw: hardware काष्ठाure that contains filter list
 * @cmd: ethtool command data काष्ठाure to receive the filter data
 *
 * Returns 0 on success and -EINVAL on failure
 */
पूर्णांक ice_get_ethtool_fdir_entry(काष्ठा ice_hw *hw, काष्ठा ethtool_rxnfc *cmd)
अणु
	काष्ठा ethtool_rx_flow_spec *fsp;
	काष्ठा ice_fdir_fltr *rule;
	पूर्णांक ret = 0;
	u16 idx;

	fsp = (काष्ठा ethtool_rx_flow_spec *)&cmd->fs;

	mutex_lock(&hw->fdir_fltr_lock);

	rule = ice_fdir_find_fltr_by_idx(hw, fsp->location);

	अगर (!rule || fsp->location != rule->fltr_id) अणु
		ret = -EINVAL;
		जाओ release_lock;
	पूर्ण

	fsp->flow_type = ice_fltr_to_ethtool_flow(rule->flow_type);

	स_रखो(&fsp->m_u, 0, माप(fsp->m_u));
	स_रखो(&fsp->m_ext, 0, माप(fsp->m_ext));

	चयन (fsp->flow_type) अणु
	हाल IPV4_USER_FLOW:
		fsp->h_u.usr_ip4_spec.ip_ver = ETH_RX_NFC_IP4;
		fsp->h_u.usr_ip4_spec.proto = 0;
		fsp->h_u.usr_ip4_spec.l4_4_bytes = rule->ip.v4.l4_header;
		fsp->h_u.usr_ip4_spec.tos = rule->ip.v4.tos;
		fsp->h_u.usr_ip4_spec.ip4src = rule->ip.v4.src_ip;
		fsp->h_u.usr_ip4_spec.ip4dst = rule->ip.v4.dst_ip;
		fsp->m_u.usr_ip4_spec.ip4src = rule->mask.v4.src_ip;
		fsp->m_u.usr_ip4_spec.ip4dst = rule->mask.v4.dst_ip;
		fsp->m_u.usr_ip4_spec.ip_ver = 0xFF;
		fsp->m_u.usr_ip4_spec.proto = 0;
		fsp->m_u.usr_ip4_spec.l4_4_bytes = rule->mask.v4.l4_header;
		fsp->m_u.usr_ip4_spec.tos = rule->mask.v4.tos;
		अवरोध;
	हाल TCP_V4_FLOW:
	हाल UDP_V4_FLOW:
	हाल SCTP_V4_FLOW:
		fsp->h_u.tcp_ip4_spec.psrc = rule->ip.v4.src_port;
		fsp->h_u.tcp_ip4_spec.pdst = rule->ip.v4.dst_port;
		fsp->h_u.tcp_ip4_spec.ip4src = rule->ip.v4.src_ip;
		fsp->h_u.tcp_ip4_spec.ip4dst = rule->ip.v4.dst_ip;
		fsp->m_u.tcp_ip4_spec.psrc = rule->mask.v4.src_port;
		fsp->m_u.tcp_ip4_spec.pdst = rule->mask.v4.dst_port;
		fsp->m_u.tcp_ip4_spec.ip4src = rule->mask.v4.src_ip;
		fsp->m_u.tcp_ip4_spec.ip4dst = rule->mask.v4.dst_ip;
		अवरोध;
	हाल IPV6_USER_FLOW:
		fsp->h_u.usr_ip6_spec.l4_4_bytes = rule->ip.v6.l4_header;
		fsp->h_u.usr_ip6_spec.tclass = rule->ip.v6.tc;
		fsp->h_u.usr_ip6_spec.l4_proto = rule->ip.v6.proto;
		स_नकल(fsp->h_u.tcp_ip6_spec.ip6src, rule->ip.v6.src_ip,
		       माप(काष्ठा in6_addr));
		स_नकल(fsp->h_u.tcp_ip6_spec.ip6dst, rule->ip.v6.dst_ip,
		       माप(काष्ठा in6_addr));
		स_नकल(fsp->m_u.tcp_ip6_spec.ip6src, rule->mask.v6.src_ip,
		       माप(काष्ठा in6_addr));
		स_नकल(fsp->m_u.tcp_ip6_spec.ip6dst, rule->mask.v6.dst_ip,
		       माप(काष्ठा in6_addr));
		fsp->m_u.usr_ip6_spec.l4_4_bytes = rule->mask.v6.l4_header;
		fsp->m_u.usr_ip6_spec.tclass = rule->mask.v6.tc;
		fsp->m_u.usr_ip6_spec.l4_proto = rule->mask.v6.proto;
		अवरोध;
	हाल TCP_V6_FLOW:
	हाल UDP_V6_FLOW:
	हाल SCTP_V6_FLOW:
		स_नकल(fsp->h_u.tcp_ip6_spec.ip6src, rule->ip.v6.src_ip,
		       माप(काष्ठा in6_addr));
		स_नकल(fsp->h_u.tcp_ip6_spec.ip6dst, rule->ip.v6.dst_ip,
		       माप(काष्ठा in6_addr));
		fsp->h_u.tcp_ip6_spec.psrc = rule->ip.v6.src_port;
		fsp->h_u.tcp_ip6_spec.pdst = rule->ip.v6.dst_port;
		स_नकल(fsp->m_u.tcp_ip6_spec.ip6src,
		       rule->mask.v6.src_ip,
		       माप(काष्ठा in6_addr));
		स_नकल(fsp->m_u.tcp_ip6_spec.ip6dst,
		       rule->mask.v6.dst_ip,
		       माप(काष्ठा in6_addr));
		fsp->m_u.tcp_ip6_spec.psrc = rule->mask.v6.src_port;
		fsp->m_u.tcp_ip6_spec.pdst = rule->mask.v6.dst_port;
		fsp->h_u.tcp_ip6_spec.tclass = rule->ip.v6.tc;
		fsp->m_u.tcp_ip6_spec.tclass = rule->mask.v6.tc;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (rule->dest_ctl == ICE_FLTR_PRGM_DESC_DEST_DROP_PKT)
		fsp->ring_cookie = RX_CLS_FLOW_DISC;
	अन्यथा
		fsp->ring_cookie = rule->q_index;

	idx = ice_ethtool_flow_to_fltr(fsp->flow_type);
	अगर (idx == ICE_FLTR_PTYPE_NONF_NONE) अणु
		dev_err(ice_hw_to_dev(hw), "Missing input index for flow_type %d\n",
			rule->flow_type);
		ret = -EINVAL;
	पूर्ण

release_lock:
	mutex_unlock(&hw->fdir_fltr_lock);
	वापस ret;
पूर्ण

/**
 * ice_get_fdir_fltr_ids - fill buffer with filter IDs of active filters
 * @hw: hardware काष्ठाure containing the filter list
 * @cmd: ethtool command data काष्ठाure
 * @rule_locs: ethtool array passed in from OS to receive filter IDs
 *
 * Returns 0 as expected क्रम success by ethtool
 */
पूर्णांक
ice_get_fdir_fltr_ids(काष्ठा ice_hw *hw, काष्ठा ethtool_rxnfc *cmd,
		      u32 *rule_locs)
अणु
	काष्ठा ice_fdir_fltr *f_rule;
	अचिन्हित पूर्णांक cnt = 0;
	पूर्णांक val = 0;

	/* report total rule count */
	cmd->data = ice_get_fdir_cnt_all(hw);

	mutex_lock(&hw->fdir_fltr_lock);

	list_क्रम_each_entry(f_rule, &hw->fdir_list_head, fltr_node) अणु
		अगर (cnt == cmd->rule_cnt) अणु
			val = -EMSGSIZE;
			जाओ release_lock;
		पूर्ण
		rule_locs[cnt] = f_rule->fltr_id;
		cnt++;
	पूर्ण

release_lock:
	mutex_unlock(&hw->fdir_fltr_lock);
	अगर (!val)
		cmd->rule_cnt = cnt;
	वापस val;
पूर्ण

/**
 * ice_fdir_get_hw_prof - वापस the ice_fd_hw_proc associated with a flow
 * @hw: hardware काष्ठाure containing the filter list
 * @blk: hardware block
 * @flow: FDir flow type to release
 */
अटल काष्ठा ice_fd_hw_prof *
ice_fdir_get_hw_prof(काष्ठा ice_hw *hw, क्रमागत ice_block blk, पूर्णांक flow)
अणु
	अगर (blk == ICE_BLK_FD && hw->fdir_prof)
		वापस hw->fdir_prof[flow];

	वापस शून्य;
पूर्ण

/**
 * ice_fdir_erase_flow_from_hw - हटाओ a flow from the HW profile tables
 * @hw: hardware काष्ठाure containing the filter list
 * @blk: hardware block
 * @flow: FDir flow type to release
 */
अटल व्योम
ice_fdir_erase_flow_from_hw(काष्ठा ice_hw *hw, क्रमागत ice_block blk, पूर्णांक flow)
अणु
	काष्ठा ice_fd_hw_prof *prof = ice_fdir_get_hw_prof(hw, blk, flow);
	पूर्णांक tun;

	अगर (!prof)
		वापस;

	क्रम (tun = 0; tun < ICE_FD_HW_SEG_MAX; tun++) अणु
		u64 prof_id;
		पूर्णांक j;

		prof_id = flow + tun * ICE_FLTR_PTYPE_MAX;
		क्रम (j = 0; j < prof->cnt; j++) अणु
			u16 vsi_num;

			अगर (!prof->entry_h[j][tun] || !prof->vsi_h[j])
				जारी;
			vsi_num = ice_get_hw_vsi_num(hw, prof->vsi_h[j]);
			ice_rem_prof_id_flow(hw, blk, vsi_num, prof_id);
			ice_flow_rem_entry(hw, blk, prof->entry_h[j][tun]);
			prof->entry_h[j][tun] = 0;
		पूर्ण
		ice_flow_rem_prof(hw, blk, prof_id);
	पूर्ण
पूर्ण

/**
 * ice_fdir_rem_flow - release the ice_flow काष्ठाures क्रम a filter type
 * @hw: hardware काष्ठाure containing the filter list
 * @blk: hardware block
 * @flow_type: FDir flow type to release
 */
अटल व्योम
ice_fdir_rem_flow(काष्ठा ice_hw *hw, क्रमागत ice_block blk,
		  क्रमागत ice_fltr_ptype flow_type)
अणु
	पूर्णांक flow = (पूर्णांक)flow_type & ~FLOW_EXT;
	काष्ठा ice_fd_hw_prof *prof;
	पूर्णांक tun, i;

	prof = ice_fdir_get_hw_prof(hw, blk, flow);
	अगर (!prof)
		वापस;

	ice_fdir_erase_flow_from_hw(hw, blk, flow);
	क्रम (i = 0; i < prof->cnt; i++)
		prof->vsi_h[i] = 0;
	क्रम (tun = 0; tun < ICE_FD_HW_SEG_MAX; tun++) अणु
		अगर (!prof->fdir_seg[tun])
			जारी;
		devm_kमुक्त(ice_hw_to_dev(hw), prof->fdir_seg[tun]);
		prof->fdir_seg[tun] = शून्य;
	पूर्ण
	prof->cnt = 0;
पूर्ण

/**
 * ice_fdir_release_flows - release all flows in use क्रम later replay
 * @hw: poपूर्णांकer to HW instance
 */
व्योम ice_fdir_release_flows(काष्ठा ice_hw *hw)
अणु
	पूर्णांक flow;

	/* release Flow Director HW table entries */
	क्रम (flow = 0; flow < ICE_FLTR_PTYPE_MAX; flow++)
		ice_fdir_erase_flow_from_hw(hw, ICE_BLK_FD, flow);
पूर्ण

/**
 * ice_fdir_replay_flows - replay HW Flow Director filter info
 * @hw: poपूर्णांकer to HW instance
 */
व्योम ice_fdir_replay_flows(काष्ठा ice_hw *hw)
अणु
	पूर्णांक flow;

	क्रम (flow = 0; flow < ICE_FLTR_PTYPE_MAX; flow++) अणु
		पूर्णांक tun;

		अगर (!hw->fdir_prof[flow] || !hw->fdir_prof[flow]->cnt)
			जारी;
		क्रम (tun = 0; tun < ICE_FD_HW_SEG_MAX; tun++) अणु
			काष्ठा ice_flow_prof *hw_prof;
			काष्ठा ice_fd_hw_prof *prof;
			u64 prof_id;
			पूर्णांक j;

			prof = hw->fdir_prof[flow];
			prof_id = flow + tun * ICE_FLTR_PTYPE_MAX;
			ice_flow_add_prof(hw, ICE_BLK_FD, ICE_FLOW_RX, prof_id,
					  prof->fdir_seg[tun], TNL_SEG_CNT(tun),
					  &hw_prof);
			क्रम (j = 0; j < prof->cnt; j++) अणु
				क्रमागत ice_flow_priority prio;
				u64 entry_h = 0;
				पूर्णांक err;

				prio = ICE_FLOW_PRIO_NORMAL;
				err = ice_flow_add_entry(hw, ICE_BLK_FD,
							 prof_id,
							 prof->vsi_h[0],
							 prof->vsi_h[j],
							 prio, prof->fdir_seg,
							 &entry_h);
				अगर (err) अणु
					dev_err(ice_hw_to_dev(hw), "Could not replay Flow Director, flow type %d\n",
						flow);
					जारी;
				पूर्ण
				prof->entry_h[j][tun] = entry_h;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/**
 * ice_parse_rx_flow_user_data - deस्थिरruct user-defined data
 * @fsp: poपूर्णांकer to ethtool Rx flow specअगरication
 * @data: poपूर्णांकer to userdef data काष्ठाure क्रम storage
 *
 * Returns 0 on success, negative error value on failure
 */
अटल पूर्णांक
ice_parse_rx_flow_user_data(काष्ठा ethtool_rx_flow_spec *fsp,
			    काष्ठा ice_rx_flow_userdef *data)
अणु
	u64 value, mask;

	स_रखो(data, 0, माप(*data));
	अगर (!(fsp->flow_type & FLOW_EXT))
		वापस 0;

	value = be64_to_cpu(*((__क्रमce __be64 *)fsp->h_ext.data));
	mask = be64_to_cpu(*((__क्रमce __be64 *)fsp->m_ext.data));
	अगर (!mask)
		वापस 0;

#घोषणा ICE_USERDEF_FLEX_WORD_M	GENMASK_ULL(15, 0)
#घोषणा ICE_USERDEF_FLEX_OFFS_S	16
#घोषणा ICE_USERDEF_FLEX_OFFS_M	GENMASK_ULL(31, ICE_USERDEF_FLEX_OFFS_S)
#घोषणा ICE_USERDEF_FLEX_FLTR_M	GENMASK_ULL(31, 0)

	/* 0x1fe is the maximum value क्रम offsets stored in the पूर्णांकernal
	 * filtering tables.
	 */
#घोषणा ICE_USERDEF_FLEX_MAX_OFFS_VAL 0x1fe

	अगर (!ice_is_mask_valid(mask, ICE_USERDEF_FLEX_FLTR_M) ||
	    value > ICE_USERDEF_FLEX_FLTR_M)
		वापस -EINVAL;

	data->flex_word = value & ICE_USERDEF_FLEX_WORD_M;
	data->flex_offset = (value & ICE_USERDEF_FLEX_OFFS_M) >>
			     ICE_USERDEF_FLEX_OFFS_S;
	अगर (data->flex_offset > ICE_USERDEF_FLEX_MAX_OFFS_VAL)
		वापस -EINVAL;

	data->flex_fltr = true;

	वापस 0;
पूर्ण

/**
 * ice_fdir_num_avail_fltr - वापस the number of unused flow director filters
 * @hw: poपूर्णांकer to hardware काष्ठाure
 * @vsi: software VSI काष्ठाure
 *
 * There are 2 filter pools: guaranteed and best efक्रमt(shared). Each VSI can
 * use filters from either pool. The guaranteed pool is भागided between VSIs.
 * The best efक्रमt filter pool is common to all VSIs and is a device shared
 * resource pool. The number of filters available to this VSI is the sum of
 * the VSIs guaranteed filter pool and the global available best efक्रमt
 * filter pool.
 *
 * Returns the number of available flow director filters to this VSI
 */
अटल पूर्णांक ice_fdir_num_avail_fltr(काष्ठा ice_hw *hw, काष्ठा ice_vsi *vsi)
अणु
	u16 vsi_num = ice_get_hw_vsi_num(hw, vsi->idx);
	u16 num_guar;
	u16 num_be;

	/* total guaranteed filters asचिन्हित to this VSI */
	num_guar = vsi->num_gfltr;

	/* minus the guaranteed filters programed by this VSI */
	num_guar -= (rd32(hw, VSIQF_FD_CNT(vsi_num)) &
		     VSIQF_FD_CNT_FD_GCNT_M) >> VSIQF_FD_CNT_FD_GCNT_S;

	/* total global best efक्रमt filters */
	num_be = hw->func_caps.fd_fltr_best_efक्रमt;

	/* minus the global best efक्रमt filters programmed */
	num_be -= (rd32(hw, GLQF_FD_CNT) & GLQF_FD_CNT_FD_BCNT_M) >>
		   GLQF_FD_CNT_FD_BCNT_S;

	वापस num_guar + num_be;
पूर्ण

/**
 * ice_fdir_alloc_flow_prof - allocate FDir flow profile काष्ठाure(s)
 * @hw: HW काष्ठाure containing the FDir flow profile काष्ठाure(s)
 * @flow: flow type to allocate the flow profile क्रम
 *
 * Allocate the fdir_prof and fdir_prof[flow] अगर not alपढ़ोy created. Return 0
 * on success and negative on error.
 */
अटल पूर्णांक
ice_fdir_alloc_flow_prof(काष्ठा ice_hw *hw, क्रमागत ice_fltr_ptype flow)
अणु
	अगर (!hw)
		वापस -EINVAL;

	अगर (!hw->fdir_prof) अणु
		hw->fdir_prof = devm_kसुस्मृति(ice_hw_to_dev(hw),
					     ICE_FLTR_PTYPE_MAX,
					     माप(*hw->fdir_prof),
					     GFP_KERNEL);
		अगर (!hw->fdir_prof)
			वापस -ENOMEM;
	पूर्ण

	अगर (!hw->fdir_prof[flow]) अणु
		hw->fdir_prof[flow] = devm_kzalloc(ice_hw_to_dev(hw),
						   माप(**hw->fdir_prof),
						   GFP_KERNEL);
		अगर (!hw->fdir_prof[flow])
			वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ice_fdir_set_hw_fltr_rule - Configure HW tables to generate a FDir rule
 * @pf: poपूर्णांकer to the PF काष्ठाure
 * @seg: protocol header description poपूर्णांकer
 * @flow: filter क्रमागत
 * @tun: FDir segment to program
 */
अटल पूर्णांक
ice_fdir_set_hw_fltr_rule(काष्ठा ice_pf *pf, काष्ठा ice_flow_seg_info *seg,
			  क्रमागत ice_fltr_ptype flow, क्रमागत ice_fd_hw_seg tun)
अणु
	काष्ठा device *dev = ice_pf_to_dev(pf);
	काष्ठा ice_vsi *मुख्य_vsi, *ctrl_vsi;
	काष्ठा ice_flow_seg_info *old_seg;
	काष्ठा ice_flow_prof *prof = शून्य;
	काष्ठा ice_fd_hw_prof *hw_prof;
	काष्ठा ice_hw *hw = &pf->hw;
	क्रमागत ice_status status;
	u64 entry1_h = 0;
	u64 entry2_h = 0;
	u64 prof_id;
	पूर्णांक err;

	मुख्य_vsi = ice_get_मुख्य_vsi(pf);
	अगर (!मुख्य_vsi)
		वापस -EINVAL;

	ctrl_vsi = ice_get_ctrl_vsi(pf);
	अगर (!ctrl_vsi)
		वापस -EINVAL;

	err = ice_fdir_alloc_flow_prof(hw, flow);
	अगर (err)
		वापस err;

	hw_prof = hw->fdir_prof[flow];
	old_seg = hw_prof->fdir_seg[tun];
	अगर (old_seg) अणु
		/* This flow_type alपढ़ोy has a changed input set.
		 * If it matches the requested input set then we are
		 * करोne. Or, अगर it's different then it's an error.
		 */
		अगर (!स_भेद(old_seg, seg, माप(*seg)))
			वापस -EEXIST;

		/* अगर there are FDir filters using this flow,
		 * then वापस error.
		 */
		अगर (hw->fdir_fltr_cnt[flow]) अणु
			dev_err(dev, "Failed to add filter.  Flow director filters on each port must have the same input set.\n");
			वापस -EINVAL;
		पूर्ण

		अगर (ice_is_arfs_using_perfect_flow(hw, flow)) अणु
			dev_err(dev, "aRFS using perfect flow type %d, cannot change input set\n",
				flow);
			वापस -EINVAL;
		पूर्ण

		/* हटाओ HW filter definition */
		ice_fdir_rem_flow(hw, ICE_BLK_FD, flow);
	पूर्ण

	/* Adding a profile, but there is only one header supported.
	 * That is the final parameters are 1 header (segment), no
	 * actions (शून्य) and zero actions 0.
	 */
	prof_id = flow + tun * ICE_FLTR_PTYPE_MAX;
	status = ice_flow_add_prof(hw, ICE_BLK_FD, ICE_FLOW_RX, prof_id, seg,
				   TNL_SEG_CNT(tun), &prof);
	अगर (status)
		वापस ice_status_to_त्रुटि_सं(status);
	status = ice_flow_add_entry(hw, ICE_BLK_FD, prof_id, मुख्य_vsi->idx,
				    मुख्य_vsi->idx, ICE_FLOW_PRIO_NORMAL,
				    seg, &entry1_h);
	अगर (status) अणु
		err = ice_status_to_त्रुटि_सं(status);
		जाओ err_prof;
	पूर्ण
	status = ice_flow_add_entry(hw, ICE_BLK_FD, prof_id, मुख्य_vsi->idx,
				    ctrl_vsi->idx, ICE_FLOW_PRIO_NORMAL,
				    seg, &entry2_h);
	अगर (status) अणु
		err = ice_status_to_त्रुटि_सं(status);
		जाओ err_entry;
	पूर्ण

	hw_prof->fdir_seg[tun] = seg;
	hw_prof->entry_h[0][tun] = entry1_h;
	hw_prof->entry_h[1][tun] = entry2_h;
	hw_prof->vsi_h[0] = मुख्य_vsi->idx;
	hw_prof->vsi_h[1] = ctrl_vsi->idx;
	अगर (!hw_prof->cnt)
		hw_prof->cnt = 2;

	वापस 0;

err_entry:
	ice_rem_prof_id_flow(hw, ICE_BLK_FD,
			     ice_get_hw_vsi_num(hw, मुख्य_vsi->idx), prof_id);
	ice_flow_rem_entry(hw, ICE_BLK_FD, entry1_h);
err_prof:
	ice_flow_rem_prof(hw, ICE_BLK_FD, prof_id);
	dev_err(dev, "Failed to add filter.  Flow director filters on each port must have the same input set.\n");

	वापस err;
पूर्ण

/**
 * ice_set_init_fdir_seg
 * @seg: flow segment क्रम programming
 * @l3_proto: ICE_FLOW_SEG_HDR_IPV4 or ICE_FLOW_SEG_HDR_IPV6
 * @l4_proto: ICE_FLOW_SEG_HDR_TCP or ICE_FLOW_SEG_HDR_UDP
 *
 * Set the configuration क्रम perfect filters to the provided flow segment क्रम
 * programming the HW filter. This is to be called only when initializing
 * filters as this function it assumes no filters exist.
 */
अटल पूर्णांक
ice_set_init_fdir_seg(काष्ठा ice_flow_seg_info *seg,
		      क्रमागत ice_flow_seg_hdr l3_proto,
		      क्रमागत ice_flow_seg_hdr l4_proto)
अणु
	क्रमागत ice_flow_field src_addr, dst_addr, src_port, dst_port;

	अगर (!seg)
		वापस -EINVAL;

	अगर (l3_proto == ICE_FLOW_SEG_HDR_IPV4) अणु
		src_addr = ICE_FLOW_FIELD_IDX_IPV4_SA;
		dst_addr = ICE_FLOW_FIELD_IDX_IPV4_DA;
	पूर्ण अन्यथा अगर (l3_proto == ICE_FLOW_SEG_HDR_IPV6) अणु
		src_addr = ICE_FLOW_FIELD_IDX_IPV6_SA;
		dst_addr = ICE_FLOW_FIELD_IDX_IPV6_DA;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	अगर (l4_proto == ICE_FLOW_SEG_HDR_TCP) अणु
		src_port = ICE_FLOW_FIELD_IDX_TCP_SRC_PORT;
		dst_port = ICE_FLOW_FIELD_IDX_TCP_DST_PORT;
	पूर्ण अन्यथा अगर (l4_proto == ICE_FLOW_SEG_HDR_UDP) अणु
		src_port = ICE_FLOW_FIELD_IDX_UDP_SRC_PORT;
		dst_port = ICE_FLOW_FIELD_IDX_UDP_DST_PORT;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	ICE_FLOW_SET_HDRS(seg, l3_proto | l4_proto);

	/* IP source address */
	ice_flow_set_fld(seg, src_addr, ICE_FLOW_FLD_OFF_INVAL,
			 ICE_FLOW_FLD_OFF_INVAL, ICE_FLOW_FLD_OFF_INVAL, false);

	/* IP destination address */
	ice_flow_set_fld(seg, dst_addr, ICE_FLOW_FLD_OFF_INVAL,
			 ICE_FLOW_FLD_OFF_INVAL, ICE_FLOW_FLD_OFF_INVAL, false);

	/* Layer 4 source port */
	ice_flow_set_fld(seg, src_port, ICE_FLOW_FLD_OFF_INVAL,
			 ICE_FLOW_FLD_OFF_INVAL, ICE_FLOW_FLD_OFF_INVAL, false);

	/* Layer 4 destination port */
	ice_flow_set_fld(seg, dst_port, ICE_FLOW_FLD_OFF_INVAL,
			 ICE_FLOW_FLD_OFF_INVAL, ICE_FLOW_FLD_OFF_INVAL, false);

	वापस 0;
पूर्ण

/**
 * ice_create_init_fdir_rule
 * @pf: PF काष्ठाure
 * @flow: filter क्रमागत
 *
 * Return error value or 0 on success.
 */
अटल पूर्णांक
ice_create_init_fdir_rule(काष्ठा ice_pf *pf, क्रमागत ice_fltr_ptype flow)
अणु
	काष्ठा ice_flow_seg_info *seg, *tun_seg;
	काष्ठा device *dev = ice_pf_to_dev(pf);
	काष्ठा ice_hw *hw = &pf->hw;
	पूर्णांक ret;

	/* अगर there is alपढ़ोy a filter rule क्रम kind वापस -EINVAL */
	अगर (hw->fdir_prof && hw->fdir_prof[flow] &&
	    hw->fdir_prof[flow]->fdir_seg[0])
		वापस -EINVAL;

	seg = devm_kzalloc(dev, माप(*seg), GFP_KERNEL);
	अगर (!seg)
		वापस -ENOMEM;

	tun_seg = devm_kzalloc(dev, माप(*seg) * ICE_FD_HW_SEG_MAX,
			       GFP_KERNEL);
	अगर (!tun_seg) अणु
		devm_kमुक्त(dev, seg);
		वापस -ENOMEM;
	पूर्ण

	अगर (flow == ICE_FLTR_PTYPE_NONF_IPV4_TCP)
		ret = ice_set_init_fdir_seg(seg, ICE_FLOW_SEG_HDR_IPV4,
					    ICE_FLOW_SEG_HDR_TCP);
	अन्यथा अगर (flow == ICE_FLTR_PTYPE_NONF_IPV4_UDP)
		ret = ice_set_init_fdir_seg(seg, ICE_FLOW_SEG_HDR_IPV4,
					    ICE_FLOW_SEG_HDR_UDP);
	अन्यथा अगर (flow == ICE_FLTR_PTYPE_NONF_IPV6_TCP)
		ret = ice_set_init_fdir_seg(seg, ICE_FLOW_SEG_HDR_IPV6,
					    ICE_FLOW_SEG_HDR_TCP);
	अन्यथा अगर (flow == ICE_FLTR_PTYPE_NONF_IPV6_UDP)
		ret = ice_set_init_fdir_seg(seg, ICE_FLOW_SEG_HDR_IPV6,
					    ICE_FLOW_SEG_HDR_UDP);
	अन्यथा
		ret = -EINVAL;
	अगर (ret)
		जाओ err_निकास;

	/* add filter क्रम outer headers */
	ret = ice_fdir_set_hw_fltr_rule(pf, seg, flow, ICE_FD_HW_SEG_NON_TUN);
	अगर (ret)
		/* could not ग_लिखो filter, मुक्त memory */
		जाओ err_निकास;

	/* make tunneled filter HW entries अगर possible */
	स_नकल(&tun_seg[1], seg, माप(*seg));
	ret = ice_fdir_set_hw_fltr_rule(pf, tun_seg, flow, ICE_FD_HW_SEG_TUN);
	अगर (ret)
		/* could not ग_लिखो tunnel filter, but outer header filter
		 * exists
		 */
		devm_kमुक्त(dev, tun_seg);

	set_bit(flow, hw->fdir_perfect_fltr);
	वापस ret;
err_निकास:
	devm_kमुक्त(dev, tun_seg);
	devm_kमुक्त(dev, seg);

	वापस -EOPNOTSUPP;
पूर्ण

/**
 * ice_set_fdir_ip4_seg
 * @seg: flow segment क्रम programming
 * @tcp_ip4_spec: mask data from ethtool
 * @l4_proto: Layer 4 protocol to program
 * @perfect_fltr: only valid on success; वापसs true अगर perfect filter,
 *		  false अगर not
 *
 * Set the mask data पूर्णांकo the flow segment to be used to program HW
 * table based on provided L4 protocol क्रम IPv4
 */
अटल पूर्णांक
ice_set_fdir_ip4_seg(काष्ठा ice_flow_seg_info *seg,
		     काष्ठा ethtool_tcpip4_spec *tcp_ip4_spec,
		     क्रमागत ice_flow_seg_hdr l4_proto, bool *perfect_fltr)
अणु
	क्रमागत ice_flow_field src_port, dst_port;

	/* make sure we करोn't have any empty rule */
	अगर (!tcp_ip4_spec->psrc && !tcp_ip4_spec->ip4src &&
	    !tcp_ip4_spec->pdst && !tcp_ip4_spec->ip4dst)
		वापस -EINVAL;

	/* filtering on TOS not supported */
	अगर (tcp_ip4_spec->tos)
		वापस -EOPNOTSUPP;

	अगर (l4_proto == ICE_FLOW_SEG_HDR_TCP) अणु
		src_port = ICE_FLOW_FIELD_IDX_TCP_SRC_PORT;
		dst_port = ICE_FLOW_FIELD_IDX_TCP_DST_PORT;
	पूर्ण अन्यथा अगर (l4_proto == ICE_FLOW_SEG_HDR_UDP) अणु
		src_port = ICE_FLOW_FIELD_IDX_UDP_SRC_PORT;
		dst_port = ICE_FLOW_FIELD_IDX_UDP_DST_PORT;
	पूर्ण अन्यथा अगर (l4_proto == ICE_FLOW_SEG_HDR_SCTP) अणु
		src_port = ICE_FLOW_FIELD_IDX_SCTP_SRC_PORT;
		dst_port = ICE_FLOW_FIELD_IDX_SCTP_DST_PORT;
	पूर्ण अन्यथा अणु
		वापस -EOPNOTSUPP;
	पूर्ण

	*perfect_fltr = true;
	ICE_FLOW_SET_HDRS(seg, ICE_FLOW_SEG_HDR_IPV4 | l4_proto);

	/* IP source address */
	अगर (tcp_ip4_spec->ip4src == htonl(0xFFFFFFFF))
		ice_flow_set_fld(seg, ICE_FLOW_FIELD_IDX_IPV4_SA,
				 ICE_FLOW_FLD_OFF_INVAL, ICE_FLOW_FLD_OFF_INVAL,
				 ICE_FLOW_FLD_OFF_INVAL, false);
	अन्यथा अगर (!tcp_ip4_spec->ip4src)
		*perfect_fltr = false;
	अन्यथा
		वापस -EOPNOTSUPP;

	/* IP destination address */
	अगर (tcp_ip4_spec->ip4dst == htonl(0xFFFFFFFF))
		ice_flow_set_fld(seg, ICE_FLOW_FIELD_IDX_IPV4_DA,
				 ICE_FLOW_FLD_OFF_INVAL, ICE_FLOW_FLD_OFF_INVAL,
				 ICE_FLOW_FLD_OFF_INVAL, false);
	अन्यथा अगर (!tcp_ip4_spec->ip4dst)
		*perfect_fltr = false;
	अन्यथा
		वापस -EOPNOTSUPP;

	/* Layer 4 source port */
	अगर (tcp_ip4_spec->psrc == htons(0xFFFF))
		ice_flow_set_fld(seg, src_port, ICE_FLOW_FLD_OFF_INVAL,
				 ICE_FLOW_FLD_OFF_INVAL, ICE_FLOW_FLD_OFF_INVAL,
				 false);
	अन्यथा अगर (!tcp_ip4_spec->psrc)
		*perfect_fltr = false;
	अन्यथा
		वापस -EOPNOTSUPP;

	/* Layer 4 destination port */
	अगर (tcp_ip4_spec->pdst == htons(0xFFFF))
		ice_flow_set_fld(seg, dst_port, ICE_FLOW_FLD_OFF_INVAL,
				 ICE_FLOW_FLD_OFF_INVAL, ICE_FLOW_FLD_OFF_INVAL,
				 false);
	अन्यथा अगर (!tcp_ip4_spec->pdst)
		*perfect_fltr = false;
	अन्यथा
		वापस -EOPNOTSUPP;

	वापस 0;
पूर्ण

/**
 * ice_set_fdir_ip4_usr_seg
 * @seg: flow segment क्रम programming
 * @usr_ip4_spec: ethtool userdef packet offset
 * @perfect_fltr: only valid on success; वापसs true अगर perfect filter,
 *		  false अगर not
 *
 * Set the offset data पूर्णांकo the flow segment to be used to program HW
 * table क्रम IPv4
 */
अटल पूर्णांक
ice_set_fdir_ip4_usr_seg(काष्ठा ice_flow_seg_info *seg,
			 काष्ठा ethtool_usrip4_spec *usr_ip4_spec,
			 bool *perfect_fltr)
अणु
	/* first 4 bytes of Layer 4 header */
	अगर (usr_ip4_spec->l4_4_bytes)
		वापस -EINVAL;
	अगर (usr_ip4_spec->tos)
		वापस -EINVAL;
	अगर (usr_ip4_spec->ip_ver)
		वापस -EINVAL;
	/* Filtering on Layer 4 protocol not supported */
	अगर (usr_ip4_spec->proto)
		वापस -EOPNOTSUPP;
	/* empty rules are not valid */
	अगर (!usr_ip4_spec->ip4src && !usr_ip4_spec->ip4dst)
		वापस -EINVAL;

	*perfect_fltr = true;
	ICE_FLOW_SET_HDRS(seg, ICE_FLOW_SEG_HDR_IPV4);

	/* IP source address */
	अगर (usr_ip4_spec->ip4src == htonl(0xFFFFFFFF))
		ice_flow_set_fld(seg, ICE_FLOW_FIELD_IDX_IPV4_SA,
				 ICE_FLOW_FLD_OFF_INVAL, ICE_FLOW_FLD_OFF_INVAL,
				 ICE_FLOW_FLD_OFF_INVAL, false);
	अन्यथा अगर (!usr_ip4_spec->ip4src)
		*perfect_fltr = false;
	अन्यथा
		वापस -EOPNOTSUPP;

	/* IP destination address */
	अगर (usr_ip4_spec->ip4dst == htonl(0xFFFFFFFF))
		ice_flow_set_fld(seg, ICE_FLOW_FIELD_IDX_IPV4_DA,
				 ICE_FLOW_FLD_OFF_INVAL, ICE_FLOW_FLD_OFF_INVAL,
				 ICE_FLOW_FLD_OFF_INVAL, false);
	अन्यथा अगर (!usr_ip4_spec->ip4dst)
		*perfect_fltr = false;
	अन्यथा
		वापस -EOPNOTSUPP;

	वापस 0;
पूर्ण

/**
 * ice_set_fdir_ip6_seg
 * @seg: flow segment क्रम programming
 * @tcp_ip6_spec: mask data from ethtool
 * @l4_proto: Layer 4 protocol to program
 * @perfect_fltr: only valid on success; वापसs true अगर perfect filter,
 *		  false अगर not
 *
 * Set the mask data पूर्णांकo the flow segment to be used to program HW
 * table based on provided L4 protocol क्रम IPv6
 */
अटल पूर्णांक
ice_set_fdir_ip6_seg(काष्ठा ice_flow_seg_info *seg,
		     काष्ठा ethtool_tcpip6_spec *tcp_ip6_spec,
		     क्रमागत ice_flow_seg_hdr l4_proto, bool *perfect_fltr)
अणु
	क्रमागत ice_flow_field src_port, dst_port;

	/* make sure we करोn't have any empty rule */
	अगर (!स_भेद(tcp_ip6_spec->ip6src, &zero_ipv6_addr_mask,
		    माप(काष्ठा in6_addr)) &&
	    !स_भेद(tcp_ip6_spec->ip6dst, &zero_ipv6_addr_mask,
		    माप(काष्ठा in6_addr)) &&
	    !tcp_ip6_spec->psrc && !tcp_ip6_spec->pdst)
		वापस -EINVAL;

	/* filtering on TC not supported */
	अगर (tcp_ip6_spec->tclass)
		वापस -EOPNOTSUPP;

	अगर (l4_proto == ICE_FLOW_SEG_HDR_TCP) अणु
		src_port = ICE_FLOW_FIELD_IDX_TCP_SRC_PORT;
		dst_port = ICE_FLOW_FIELD_IDX_TCP_DST_PORT;
	पूर्ण अन्यथा अगर (l4_proto == ICE_FLOW_SEG_HDR_UDP) अणु
		src_port = ICE_FLOW_FIELD_IDX_UDP_SRC_PORT;
		dst_port = ICE_FLOW_FIELD_IDX_UDP_DST_PORT;
	पूर्ण अन्यथा अगर (l4_proto == ICE_FLOW_SEG_HDR_SCTP) अणु
		src_port = ICE_FLOW_FIELD_IDX_SCTP_SRC_PORT;
		dst_port = ICE_FLOW_FIELD_IDX_SCTP_DST_PORT;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	*perfect_fltr = true;
	ICE_FLOW_SET_HDRS(seg, ICE_FLOW_SEG_HDR_IPV6 | l4_proto);

	अगर (!स_भेद(tcp_ip6_spec->ip6src, &full_ipv6_addr_mask,
		    माप(काष्ठा in6_addr)))
		ice_flow_set_fld(seg, ICE_FLOW_FIELD_IDX_IPV6_SA,
				 ICE_FLOW_FLD_OFF_INVAL, ICE_FLOW_FLD_OFF_INVAL,
				 ICE_FLOW_FLD_OFF_INVAL, false);
	अन्यथा अगर (!स_भेद(tcp_ip6_spec->ip6src, &zero_ipv6_addr_mask,
			 माप(काष्ठा in6_addr)))
		*perfect_fltr = false;
	अन्यथा
		वापस -EOPNOTSUPP;

	अगर (!स_भेद(tcp_ip6_spec->ip6dst, &full_ipv6_addr_mask,
		    माप(काष्ठा in6_addr)))
		ice_flow_set_fld(seg, ICE_FLOW_FIELD_IDX_IPV6_DA,
				 ICE_FLOW_FLD_OFF_INVAL, ICE_FLOW_FLD_OFF_INVAL,
				 ICE_FLOW_FLD_OFF_INVAL, false);
	अन्यथा अगर (!स_भेद(tcp_ip6_spec->ip6dst, &zero_ipv6_addr_mask,
			 माप(काष्ठा in6_addr)))
		*perfect_fltr = false;
	अन्यथा
		वापस -EOPNOTSUPP;

	/* Layer 4 source port */
	अगर (tcp_ip6_spec->psrc == htons(0xFFFF))
		ice_flow_set_fld(seg, src_port, ICE_FLOW_FLD_OFF_INVAL,
				 ICE_FLOW_FLD_OFF_INVAL, ICE_FLOW_FLD_OFF_INVAL,
				 false);
	अन्यथा अगर (!tcp_ip6_spec->psrc)
		*perfect_fltr = false;
	अन्यथा
		वापस -EOPNOTSUPP;

	/* Layer 4 destination port */
	अगर (tcp_ip6_spec->pdst == htons(0xFFFF))
		ice_flow_set_fld(seg, dst_port, ICE_FLOW_FLD_OFF_INVAL,
				 ICE_FLOW_FLD_OFF_INVAL, ICE_FLOW_FLD_OFF_INVAL,
				 false);
	अन्यथा अगर (!tcp_ip6_spec->pdst)
		*perfect_fltr = false;
	अन्यथा
		वापस -EOPNOTSUPP;

	वापस 0;
पूर्ण

/**
 * ice_set_fdir_ip6_usr_seg
 * @seg: flow segment क्रम programming
 * @usr_ip6_spec: ethtool userdef packet offset
 * @perfect_fltr: only valid on success; वापसs true अगर perfect filter,
 *		  false अगर not
 *
 * Set the offset data पूर्णांकo the flow segment to be used to program HW
 * table क्रम IPv6
 */
अटल पूर्णांक
ice_set_fdir_ip6_usr_seg(काष्ठा ice_flow_seg_info *seg,
			 काष्ठा ethtool_usrip6_spec *usr_ip6_spec,
			 bool *perfect_fltr)
अणु
	/* filtering on Layer 4 bytes not supported */
	अगर (usr_ip6_spec->l4_4_bytes)
		वापस -EOPNOTSUPP;
	/* filtering on TC not supported */
	अगर (usr_ip6_spec->tclass)
		वापस -EOPNOTSUPP;
	/* filtering on Layer 4 protocol not supported */
	अगर (usr_ip6_spec->l4_proto)
		वापस -EOPNOTSUPP;
	/* empty rules are not valid */
	अगर (!स_भेद(usr_ip6_spec->ip6src, &zero_ipv6_addr_mask,
		    माप(काष्ठा in6_addr)) &&
	    !स_भेद(usr_ip6_spec->ip6dst, &zero_ipv6_addr_mask,
		    माप(काष्ठा in6_addr)))
		वापस -EINVAL;

	*perfect_fltr = true;
	ICE_FLOW_SET_HDRS(seg, ICE_FLOW_SEG_HDR_IPV6);

	अगर (!स_भेद(usr_ip6_spec->ip6src, &full_ipv6_addr_mask,
		    माप(काष्ठा in6_addr)))
		ice_flow_set_fld(seg, ICE_FLOW_FIELD_IDX_IPV6_SA,
				 ICE_FLOW_FLD_OFF_INVAL, ICE_FLOW_FLD_OFF_INVAL,
				 ICE_FLOW_FLD_OFF_INVAL, false);
	अन्यथा अगर (!स_भेद(usr_ip6_spec->ip6src, &zero_ipv6_addr_mask,
			 माप(काष्ठा in6_addr)))
		*perfect_fltr = false;
	अन्यथा
		वापस -EOPNOTSUPP;

	अगर (!स_भेद(usr_ip6_spec->ip6dst, &full_ipv6_addr_mask,
		    माप(काष्ठा in6_addr)))
		ice_flow_set_fld(seg, ICE_FLOW_FIELD_IDX_IPV6_DA,
				 ICE_FLOW_FLD_OFF_INVAL, ICE_FLOW_FLD_OFF_INVAL,
				 ICE_FLOW_FLD_OFF_INVAL, false);
	अन्यथा अगर (!स_भेद(usr_ip6_spec->ip6dst, &zero_ipv6_addr_mask,
			 माप(काष्ठा in6_addr)))
		*perfect_fltr = false;
	अन्यथा
		वापस -EOPNOTSUPP;

	वापस 0;
पूर्ण

/**
 * ice_cfg_fdir_xtrct_seq - Configure extraction sequence क्रम the given filter
 * @pf: PF काष्ठाure
 * @fsp: poपूर्णांकer to ethtool Rx flow specअगरication
 * @user: user defined data from flow specअगरication
 *
 * Returns 0 on success.
 */
अटल पूर्णांक
ice_cfg_fdir_xtrct_seq(काष्ठा ice_pf *pf, काष्ठा ethtool_rx_flow_spec *fsp,
		       काष्ठा ice_rx_flow_userdef *user)
अणु
	काष्ठा ice_flow_seg_info *seg, *tun_seg;
	काष्ठा device *dev = ice_pf_to_dev(pf);
	क्रमागत ice_fltr_ptype fltr_idx;
	काष्ठा ice_hw *hw = &pf->hw;
	bool perfect_filter;
	पूर्णांक ret;

	seg = devm_kzalloc(dev, माप(*seg), GFP_KERNEL);
	अगर (!seg)
		वापस -ENOMEM;

	tun_seg = devm_kzalloc(dev, माप(*seg) * ICE_FD_HW_SEG_MAX,
			       GFP_KERNEL);
	अगर (!tun_seg) अणु
		devm_kमुक्त(dev, seg);
		वापस -ENOMEM;
	पूर्ण

	चयन (fsp->flow_type & ~FLOW_EXT) अणु
	हाल TCP_V4_FLOW:
		ret = ice_set_fdir_ip4_seg(seg, &fsp->m_u.tcp_ip4_spec,
					   ICE_FLOW_SEG_HDR_TCP,
					   &perfect_filter);
		अवरोध;
	हाल UDP_V4_FLOW:
		ret = ice_set_fdir_ip4_seg(seg, &fsp->m_u.tcp_ip4_spec,
					   ICE_FLOW_SEG_HDR_UDP,
					   &perfect_filter);
		अवरोध;
	हाल SCTP_V4_FLOW:
		ret = ice_set_fdir_ip4_seg(seg, &fsp->m_u.tcp_ip4_spec,
					   ICE_FLOW_SEG_HDR_SCTP,
					   &perfect_filter);
		अवरोध;
	हाल IPV4_USER_FLOW:
		ret = ice_set_fdir_ip4_usr_seg(seg, &fsp->m_u.usr_ip4_spec,
					       &perfect_filter);
		अवरोध;
	हाल TCP_V6_FLOW:
		ret = ice_set_fdir_ip6_seg(seg, &fsp->m_u.tcp_ip6_spec,
					   ICE_FLOW_SEG_HDR_TCP,
					   &perfect_filter);
		अवरोध;
	हाल UDP_V6_FLOW:
		ret = ice_set_fdir_ip6_seg(seg, &fsp->m_u.tcp_ip6_spec,
					   ICE_FLOW_SEG_HDR_UDP,
					   &perfect_filter);
		अवरोध;
	हाल SCTP_V6_FLOW:
		ret = ice_set_fdir_ip6_seg(seg, &fsp->m_u.tcp_ip6_spec,
					   ICE_FLOW_SEG_HDR_SCTP,
					   &perfect_filter);
		अवरोध;
	हाल IPV6_USER_FLOW:
		ret = ice_set_fdir_ip6_usr_seg(seg, &fsp->m_u.usr_ip6_spec,
					       &perfect_filter);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण
	अगर (ret)
		जाओ err_निकास;

	/* tunnel segments are shअगरted up one. */
	स_नकल(&tun_seg[1], seg, माप(*seg));

	अगर (user && user->flex_fltr) अणु
		perfect_filter = false;
		ice_flow_add_fld_raw(seg, user->flex_offset,
				     ICE_FLTR_PRGM_FLEX_WORD_SIZE,
				     ICE_FLOW_FLD_OFF_INVAL,
				     ICE_FLOW_FLD_OFF_INVAL);
		ice_flow_add_fld_raw(&tun_seg[1], user->flex_offset,
				     ICE_FLTR_PRGM_FLEX_WORD_SIZE,
				     ICE_FLOW_FLD_OFF_INVAL,
				     ICE_FLOW_FLD_OFF_INVAL);
	पूर्ण

	/* add filter क्रम outer headers */
	fltr_idx = ice_ethtool_flow_to_fltr(fsp->flow_type & ~FLOW_EXT);
	ret = ice_fdir_set_hw_fltr_rule(pf, seg, fltr_idx,
					ICE_FD_HW_SEG_NON_TUN);
	अगर (ret == -EEXIST)
		/* Rule alपढ़ोy exists, मुक्त memory and जारी */
		devm_kमुक्त(dev, seg);
	अन्यथा अगर (ret)
		/* could not ग_लिखो filter, मुक्त memory */
		जाओ err_निकास;

	/* make tunneled filter HW entries अगर possible */
	स_नकल(&tun_seg[1], seg, माप(*seg));
	ret = ice_fdir_set_hw_fltr_rule(pf, tun_seg, fltr_idx,
					ICE_FD_HW_SEG_TUN);
	अगर (ret == -EEXIST) अणु
		/* Rule alपढ़ोy exists, मुक्त memory and count as success */
		devm_kमुक्त(dev, tun_seg);
		ret = 0;
	पूर्ण अन्यथा अगर (ret) अणु
		/* could not ग_लिखो tunnel filter, but outer filter exists */
		devm_kमुक्त(dev, tun_seg);
	पूर्ण

	अगर (perfect_filter)
		set_bit(fltr_idx, hw->fdir_perfect_fltr);
	अन्यथा
		clear_bit(fltr_idx, hw->fdir_perfect_fltr);

	वापस ret;

err_निकास:
	devm_kमुक्त(dev, tun_seg);
	devm_kमुक्त(dev, seg);

	वापस -EOPNOTSUPP;
पूर्ण

/**
 * ice_fdir_ग_लिखो_fltr - send a flow director filter to the hardware
 * @pf: PF data काष्ठाure
 * @input: filter काष्ठाure
 * @add: true adds filter and false हटाओd filter
 * @is_tun: true adds inner filter on tunnel and false outer headers
 *
 * वापसs 0 on success and negative value on error
 */
पूर्णांक
ice_fdir_ग_लिखो_fltr(काष्ठा ice_pf *pf, काष्ठा ice_fdir_fltr *input, bool add,
		    bool is_tun)
अणु
	काष्ठा device *dev = ice_pf_to_dev(pf);
	काष्ठा ice_hw *hw = &pf->hw;
	काष्ठा ice_fltr_desc desc;
	काष्ठा ice_vsi *ctrl_vsi;
	क्रमागत ice_status status;
	u8 *pkt, *frag_pkt;
	bool has_frag;
	पूर्णांक err;

	ctrl_vsi = ice_get_ctrl_vsi(pf);
	अगर (!ctrl_vsi)
		वापस -EINVAL;

	pkt = devm_kzalloc(dev, ICE_Fसूची_MAX_RAW_PKT_SIZE, GFP_KERNEL);
	अगर (!pkt)
		वापस -ENOMEM;
	frag_pkt = devm_kzalloc(dev, ICE_Fसूची_MAX_RAW_PKT_SIZE, GFP_KERNEL);
	अगर (!frag_pkt) अणु
		err = -ENOMEM;
		जाओ err_मुक्त;
	पूर्ण

	ice_fdir_get_prgm_desc(hw, input, &desc, add);
	status = ice_fdir_get_gen_prgm_pkt(hw, input, pkt, false, is_tun);
	अगर (status) अणु
		err = ice_status_to_त्रुटि_सं(status);
		जाओ err_मुक्त_all;
	पूर्ण
	err = ice_prgm_fdir_fltr(ctrl_vsi, &desc, pkt);
	अगर (err)
		जाओ err_मुक्त_all;

	/* repeat क्रम fragment packet */
	has_frag = ice_fdir_has_frag(input->flow_type);
	अगर (has_frag) अणु
		/* करोes not वापस error */
		ice_fdir_get_prgm_desc(hw, input, &desc, add);
		status = ice_fdir_get_gen_prgm_pkt(hw, input, frag_pkt, true,
						   is_tun);
		अगर (status) अणु
			err = ice_status_to_त्रुटि_सं(status);
			जाओ err_frag;
		पूर्ण
		err = ice_prgm_fdir_fltr(ctrl_vsi, &desc, frag_pkt);
		अगर (err)
			जाओ err_frag;
	पूर्ण अन्यथा अणु
		devm_kमुक्त(dev, frag_pkt);
	पूर्ण

	वापस 0;

err_मुक्त_all:
	devm_kमुक्त(dev, frag_pkt);
err_मुक्त:
	devm_kमुक्त(dev, pkt);
	वापस err;

err_frag:
	devm_kमुक्त(dev, frag_pkt);
	वापस err;
पूर्ण

/**
 * ice_fdir_ग_लिखो_all_fltr - send a flow director filter to the hardware
 * @pf: PF data काष्ठाure
 * @input: filter काष्ठाure
 * @add: true adds filter and false हटाओd filter
 *
 * वापसs 0 on success and negative value on error
 */
अटल पूर्णांक
ice_fdir_ग_लिखो_all_fltr(काष्ठा ice_pf *pf, काष्ठा ice_fdir_fltr *input,
			bool add)
अणु
	u16 port_num;
	पूर्णांक tun;

	क्रम (tun = 0; tun < ICE_FD_HW_SEG_MAX; tun++) अणु
		bool is_tun = tun == ICE_FD_HW_SEG_TUN;
		पूर्णांक err;

		अगर (is_tun && !ice_get_खोलो_tunnel_port(&pf->hw, &port_num))
			जारी;
		err = ice_fdir_ग_लिखो_fltr(pf, input, add, is_tun);
		अगर (err)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * ice_fdir_replay_fltrs - replay filters from the HW filter list
 * @pf: board निजी काष्ठाure
 */
व्योम ice_fdir_replay_fltrs(काष्ठा ice_pf *pf)
अणु
	काष्ठा ice_fdir_fltr *f_rule;
	काष्ठा ice_hw *hw = &pf->hw;

	list_क्रम_each_entry(f_rule, &hw->fdir_list_head, fltr_node) अणु
		पूर्णांक err = ice_fdir_ग_लिखो_all_fltr(pf, f_rule, true);

		अगर (err)
			dev_dbg(ice_pf_to_dev(pf), "Flow Director error %d, could not reprogram filter %d\n",
				err, f_rule->fltr_id);
	पूर्ण
पूर्ण

/**
 * ice_fdir_create_dflt_rules - create शेष perfect filters
 * @pf: PF data काष्ठाure
 *
 * Returns 0 क्रम success or error.
 */
पूर्णांक ice_fdir_create_dflt_rules(काष्ठा ice_pf *pf)
अणु
	पूर्णांक err;

	/* Create perfect TCP and UDP rules in hardware. */
	err = ice_create_init_fdir_rule(pf, ICE_FLTR_PTYPE_NONF_IPV4_TCP);
	अगर (err)
		वापस err;

	err = ice_create_init_fdir_rule(pf, ICE_FLTR_PTYPE_NONF_IPV4_UDP);
	अगर (err)
		वापस err;

	err = ice_create_init_fdir_rule(pf, ICE_FLTR_PTYPE_NONF_IPV6_TCP);
	अगर (err)
		वापस err;

	err = ice_create_init_fdir_rule(pf, ICE_FLTR_PTYPE_NONF_IPV6_UDP);

	वापस err;
पूर्ण

/**
 * ice_vsi_manage_fdir - turn on/off flow director
 * @vsi: the VSI being changed
 * @ena: boolean value indicating अगर this is an enable or disable request
 */
व्योम ice_vsi_manage_fdir(काष्ठा ice_vsi *vsi, bool ena)
अणु
	काष्ठा ice_fdir_fltr *f_rule, *पंचांगp;
	काष्ठा ice_pf *pf = vsi->back;
	काष्ठा ice_hw *hw = &pf->hw;
	क्रमागत ice_fltr_ptype flow;

	अगर (ena) अणु
		set_bit(ICE_FLAG_FD_ENA, pf->flags);
		ice_fdir_create_dflt_rules(pf);
		वापस;
	पूर्ण

	mutex_lock(&hw->fdir_fltr_lock);
	अगर (!test_and_clear_bit(ICE_FLAG_FD_ENA, pf->flags))
		जाओ release_lock;
	list_क्रम_each_entry_safe(f_rule, पंचांगp, &hw->fdir_list_head, fltr_node) अणु
		/* ignore वापस value */
		ice_fdir_ग_लिखो_all_fltr(pf, f_rule, false);
		ice_fdir_update_cntrs(hw, f_rule->flow_type, false);
		list_del(&f_rule->fltr_node);
		devm_kमुक्त(ice_hw_to_dev(hw), f_rule);
	पूर्ण

	अगर (hw->fdir_prof)
		क्रम (flow = ICE_FLTR_PTYPE_NONF_NONE; flow < ICE_FLTR_PTYPE_MAX;
		     flow++)
			अगर (hw->fdir_prof[flow])
				ice_fdir_rem_flow(hw, ICE_BLK_FD, flow);

release_lock:
	mutex_unlock(&hw->fdir_fltr_lock);
पूर्ण

/**
 * ice_fdir_करो_rem_flow - delete flow and possibly add perfect flow
 * @pf: PF काष्ठाure
 * @flow_type: FDir flow type to release
 */
अटल व्योम
ice_fdir_करो_rem_flow(काष्ठा ice_pf *pf, क्रमागत ice_fltr_ptype flow_type)
अणु
	काष्ठा ice_hw *hw = &pf->hw;
	bool need_perfect = false;

	अगर (flow_type == ICE_FLTR_PTYPE_NONF_IPV4_TCP ||
	    flow_type == ICE_FLTR_PTYPE_NONF_IPV4_UDP ||
	    flow_type == ICE_FLTR_PTYPE_NONF_IPV6_TCP ||
	    flow_type == ICE_FLTR_PTYPE_NONF_IPV6_UDP)
		need_perfect = true;

	अगर (need_perfect && test_bit(flow_type, hw->fdir_perfect_fltr))
		वापस;

	ice_fdir_rem_flow(hw, ICE_BLK_FD, flow_type);
	अगर (need_perfect)
		ice_create_init_fdir_rule(pf, flow_type);
पूर्ण

/**
 * ice_fdir_update_list_entry - add or delete a filter from the filter list
 * @pf: PF काष्ठाure
 * @input: filter काष्ठाure
 * @fltr_idx: ethtool index of filter to modअगरy
 *
 * वापसs 0 on success and negative on errors
 */
अटल पूर्णांक
ice_fdir_update_list_entry(काष्ठा ice_pf *pf, काष्ठा ice_fdir_fltr *input,
			   पूर्णांक fltr_idx)
अणु
	काष्ठा ice_fdir_fltr *old_fltr;
	काष्ठा ice_hw *hw = &pf->hw;
	पूर्णांक err = -ENOENT;

	/* Do not update filters during reset */
	अगर (ice_is_reset_in_progress(pf->state))
		वापस -EBUSY;

	old_fltr = ice_fdir_find_fltr_by_idx(hw, fltr_idx);
	अगर (old_fltr) अणु
		err = ice_fdir_ग_लिखो_all_fltr(pf, old_fltr, false);
		अगर (err)
			वापस err;
		ice_fdir_update_cntrs(hw, old_fltr->flow_type, false);
		अगर (!input && !hw->fdir_fltr_cnt[old_fltr->flow_type])
			/* we just deleted the last filter of flow_type so we
			 * should also delete the HW filter info.
			 */
			ice_fdir_करो_rem_flow(pf, old_fltr->flow_type);
		list_del(&old_fltr->fltr_node);
		devm_kमुक्त(ice_hw_to_dev(hw), old_fltr);
	पूर्ण
	अगर (!input)
		वापस err;
	ice_fdir_list_add_fltr(hw, input);
	ice_fdir_update_cntrs(hw, input->flow_type, true);
	वापस 0;
पूर्ण

/**
 * ice_del_fdir_ethtool - delete Flow Director filter
 * @vsi: poपूर्णांकer to target VSI
 * @cmd: command to add or delete Flow Director filter
 *
 * Returns 0 on success and negative values क्रम failure
 */
पूर्णांक ice_del_fdir_ethtool(काष्ठा ice_vsi *vsi, काष्ठा ethtool_rxnfc *cmd)
अणु
	काष्ठा ethtool_rx_flow_spec *fsp =
		(काष्ठा ethtool_rx_flow_spec *)&cmd->fs;
	काष्ठा ice_pf *pf = vsi->back;
	काष्ठा ice_hw *hw = &pf->hw;
	पूर्णांक val;

	अगर (!test_bit(ICE_FLAG_FD_ENA, pf->flags))
		वापस -EOPNOTSUPP;

	/* Do not delete filters during reset */
	अगर (ice_is_reset_in_progress(pf->state)) अणु
		dev_err(ice_pf_to_dev(pf), "Device is resetting - deleting Flow Director filters not supported during reset\n");
		वापस -EBUSY;
	पूर्ण

	अगर (test_bit(ICE_FD_FLUSH_REQ, pf->state))
		वापस -EBUSY;

	mutex_lock(&hw->fdir_fltr_lock);
	val = ice_fdir_update_list_entry(pf, शून्य, fsp->location);
	mutex_unlock(&hw->fdir_fltr_lock);

	वापस val;
पूर्ण

/**
 * ice_set_fdir_input_set - Set the input set क्रम Flow Director
 * @vsi: poपूर्णांकer to target VSI
 * @fsp: poपूर्णांकer to ethtool Rx flow specअगरication
 * @input: filter काष्ठाure
 */
अटल पूर्णांक
ice_set_fdir_input_set(काष्ठा ice_vsi *vsi, काष्ठा ethtool_rx_flow_spec *fsp,
		       काष्ठा ice_fdir_fltr *input)
अणु
	u16 dest_vsi, q_index = 0;
	काष्ठा ice_pf *pf;
	काष्ठा ice_hw *hw;
	पूर्णांक flow_type;
	u8 dest_ctl;

	अगर (!vsi || !fsp || !input)
		वापस -EINVAL;

	pf = vsi->back;
	hw = &pf->hw;

	dest_vsi = vsi->idx;
	अगर (fsp->ring_cookie == RX_CLS_FLOW_DISC) अणु
		dest_ctl = ICE_FLTR_PRGM_DESC_DEST_DROP_PKT;
	पूर्ण अन्यथा अणु
		u32 ring = ethtool_get_flow_spec_ring(fsp->ring_cookie);
		u8 vf = ethtool_get_flow_spec_ring_vf(fsp->ring_cookie);

		अगर (vf) अणु
			dev_err(ice_pf_to_dev(pf), "Failed to add filter. Flow director filters are not supported on VF queues.\n");
			वापस -EINVAL;
		पूर्ण

		अगर (ring >= vsi->num_rxq)
			वापस -EINVAL;

		dest_ctl = ICE_FLTR_PRGM_DESC_DEST_सूचीECT_PKT_QINDEX;
		q_index = ring;
	पूर्ण

	input->fltr_id = fsp->location;
	input->q_index = q_index;
	flow_type = fsp->flow_type & ~FLOW_EXT;

	input->dest_vsi = dest_vsi;
	input->dest_ctl = dest_ctl;
	input->fltr_status = ICE_FLTR_PRGM_DESC_FD_STATUS_FD_ID;
	input->cnt_index = ICE_FD_SB_STAT_IDX(hw->fd_ctr_base);
	input->flow_type = ice_ethtool_flow_to_fltr(flow_type);

	अगर (fsp->flow_type & FLOW_EXT) अणु
		स_नकल(input->ext_data.usr_def, fsp->h_ext.data,
		       माप(input->ext_data.usr_def));
		input->ext_data.vlan_type = fsp->h_ext.vlan_etype;
		input->ext_data.vlan_tag = fsp->h_ext.vlan_tci;
		स_नकल(input->ext_mask.usr_def, fsp->m_ext.data,
		       माप(input->ext_mask.usr_def));
		input->ext_mask.vlan_type = fsp->m_ext.vlan_etype;
		input->ext_mask.vlan_tag = fsp->m_ext.vlan_tci;
	पूर्ण

	चयन (flow_type) अणु
	हाल TCP_V4_FLOW:
	हाल UDP_V4_FLOW:
	हाल SCTP_V4_FLOW:
		input->ip.v4.dst_port = fsp->h_u.tcp_ip4_spec.pdst;
		input->ip.v4.src_port = fsp->h_u.tcp_ip4_spec.psrc;
		input->ip.v4.dst_ip = fsp->h_u.tcp_ip4_spec.ip4dst;
		input->ip.v4.src_ip = fsp->h_u.tcp_ip4_spec.ip4src;
		input->mask.v4.dst_port = fsp->m_u.tcp_ip4_spec.pdst;
		input->mask.v4.src_port = fsp->m_u.tcp_ip4_spec.psrc;
		input->mask.v4.dst_ip = fsp->m_u.tcp_ip4_spec.ip4dst;
		input->mask.v4.src_ip = fsp->m_u.tcp_ip4_spec.ip4src;
		अवरोध;
	हाल IPV4_USER_FLOW:
		input->ip.v4.dst_ip = fsp->h_u.usr_ip4_spec.ip4dst;
		input->ip.v4.src_ip = fsp->h_u.usr_ip4_spec.ip4src;
		input->ip.v4.l4_header = fsp->h_u.usr_ip4_spec.l4_4_bytes;
		input->ip.v4.proto = fsp->h_u.usr_ip4_spec.proto;
		input->ip.v4.ip_ver = fsp->h_u.usr_ip4_spec.ip_ver;
		input->ip.v4.tos = fsp->h_u.usr_ip4_spec.tos;
		input->mask.v4.dst_ip = fsp->m_u.usr_ip4_spec.ip4dst;
		input->mask.v4.src_ip = fsp->m_u.usr_ip4_spec.ip4src;
		input->mask.v4.l4_header = fsp->m_u.usr_ip4_spec.l4_4_bytes;
		input->mask.v4.proto = fsp->m_u.usr_ip4_spec.proto;
		input->mask.v4.ip_ver = fsp->m_u.usr_ip4_spec.ip_ver;
		input->mask.v4.tos = fsp->m_u.usr_ip4_spec.tos;
		अवरोध;
	हाल TCP_V6_FLOW:
	हाल UDP_V6_FLOW:
	हाल SCTP_V6_FLOW:
		स_नकल(input->ip.v6.dst_ip, fsp->h_u.usr_ip6_spec.ip6dst,
		       माप(काष्ठा in6_addr));
		स_नकल(input->ip.v6.src_ip, fsp->h_u.usr_ip6_spec.ip6src,
		       माप(काष्ठा in6_addr));
		input->ip.v6.dst_port = fsp->h_u.tcp_ip6_spec.pdst;
		input->ip.v6.src_port = fsp->h_u.tcp_ip6_spec.psrc;
		input->ip.v6.tc = fsp->h_u.tcp_ip6_spec.tclass;
		स_नकल(input->mask.v6.dst_ip, fsp->m_u.tcp_ip6_spec.ip6dst,
		       माप(काष्ठा in6_addr));
		स_नकल(input->mask.v6.src_ip, fsp->m_u.tcp_ip6_spec.ip6src,
		       माप(काष्ठा in6_addr));
		input->mask.v6.dst_port = fsp->m_u.tcp_ip6_spec.pdst;
		input->mask.v6.src_port = fsp->m_u.tcp_ip6_spec.psrc;
		input->mask.v6.tc = fsp->m_u.tcp_ip6_spec.tclass;
		अवरोध;
	हाल IPV6_USER_FLOW:
		स_नकल(input->ip.v6.dst_ip, fsp->h_u.usr_ip6_spec.ip6dst,
		       माप(काष्ठा in6_addr));
		स_नकल(input->ip.v6.src_ip, fsp->h_u.usr_ip6_spec.ip6src,
		       माप(काष्ठा in6_addr));
		input->ip.v6.l4_header = fsp->h_u.usr_ip6_spec.l4_4_bytes;
		input->ip.v6.tc = fsp->h_u.usr_ip6_spec.tclass;

		/* अगर no protocol requested, use IPPROTO_NONE */
		अगर (!fsp->m_u.usr_ip6_spec.l4_proto)
			input->ip.v6.proto = IPPROTO_NONE;
		अन्यथा
			input->ip.v6.proto = fsp->h_u.usr_ip6_spec.l4_proto;

		स_नकल(input->mask.v6.dst_ip, fsp->m_u.usr_ip6_spec.ip6dst,
		       माप(काष्ठा in6_addr));
		स_नकल(input->mask.v6.src_ip, fsp->m_u.usr_ip6_spec.ip6src,
		       माप(काष्ठा in6_addr));
		input->mask.v6.l4_header = fsp->m_u.usr_ip6_spec.l4_4_bytes;
		input->mask.v6.tc = fsp->m_u.usr_ip6_spec.tclass;
		input->mask.v6.proto = fsp->m_u.usr_ip6_spec.l4_proto;
		अवरोध;
	शेष:
		/* not करोing un-parsed flow types */
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ice_add_fdir_ethtool - Add/Remove Flow Director filter
 * @vsi: poपूर्णांकer to target VSI
 * @cmd: command to add or delete Flow Director filter
 *
 * Returns 0 on success and negative values क्रम failure
 */
पूर्णांक ice_add_fdir_ethtool(काष्ठा ice_vsi *vsi, काष्ठा ethtool_rxnfc *cmd)
अणु
	काष्ठा ice_rx_flow_userdef userdata;
	काष्ठा ethtool_rx_flow_spec *fsp;
	काष्ठा ice_fdir_fltr *input;
	काष्ठा device *dev;
	काष्ठा ice_pf *pf;
	काष्ठा ice_hw *hw;
	पूर्णांक fltrs_needed;
	u16 tunnel_port;
	पूर्णांक ret;

	अगर (!vsi)
		वापस -EINVAL;

	pf = vsi->back;
	hw = &pf->hw;
	dev = ice_pf_to_dev(pf);

	अगर (!test_bit(ICE_FLAG_FD_ENA, pf->flags))
		वापस -EOPNOTSUPP;

	/* Do not program filters during reset */
	अगर (ice_is_reset_in_progress(pf->state)) अणु
		dev_err(dev, "Device is resetting - adding Flow Director filters not supported during reset\n");
		वापस -EBUSY;
	पूर्ण

	fsp = (काष्ठा ethtool_rx_flow_spec *)&cmd->fs;

	अगर (ice_parse_rx_flow_user_data(fsp, &userdata))
		वापस -EINVAL;

	अगर (fsp->flow_type & FLOW_MAC_EXT)
		वापस -EINVAL;

	ret = ice_cfg_fdir_xtrct_seq(pf, fsp, &userdata);
	अगर (ret)
		वापस ret;

	अगर (fsp->location >= ice_get_fdir_cnt_all(hw)) अणु
		dev_err(dev, "Failed to add filter.  The maximum number of flow director filters has been reached.\n");
		वापस -ENOSPC;
	पूर्ण

	/* वापस error अगर not an update and no available filters */
	fltrs_needed = ice_get_खोलो_tunnel_port(hw, &tunnel_port) ? 2 : 1;
	अगर (!ice_fdir_find_fltr_by_idx(hw, fsp->location) &&
	    ice_fdir_num_avail_fltr(hw, pf->vsi[vsi->idx]) < fltrs_needed) अणु
		dev_err(dev, "Failed to add filter.  The maximum number of flow director filters has been reached.\n");
		वापस -ENOSPC;
	पूर्ण

	input = devm_kzalloc(dev, माप(*input), GFP_KERNEL);
	अगर (!input)
		वापस -ENOMEM;

	ret = ice_set_fdir_input_set(vsi, fsp, input);
	अगर (ret)
		जाओ मुक्त_input;

	mutex_lock(&hw->fdir_fltr_lock);
	अगर (ice_fdir_is_dup_fltr(hw, input)) अणु
		ret = -EINVAL;
		जाओ release_lock;
	पूर्ण

	अगर (userdata.flex_fltr) अणु
		input->flex_fltr = true;
		input->flex_word = cpu_to_be16(userdata.flex_word);
		input->flex_offset = userdata.flex_offset;
	पूर्ण

	input->cnt_ena = ICE_FXD_FLTR_QW0_STAT_ENA_PKTS;
	input->fdid_prio = ICE_FXD_FLTR_QW1_FDID_PRI_THREE;
	input->comp_report = ICE_FXD_FLTR_QW0_COMP_REPORT_SW_FAIL;

	/* input काष्ठा is added to the HW filter list */
	ice_fdir_update_list_entry(pf, input, fsp->location);

	ret = ice_fdir_ग_लिखो_all_fltr(pf, input, true);
	अगर (ret)
		जाओ हटाओ_sw_rule;

	जाओ release_lock;

हटाओ_sw_rule:
	ice_fdir_update_cntrs(hw, input->flow_type, false);
	list_del(&input->fltr_node);
release_lock:
	mutex_unlock(&hw->fdir_fltr_lock);
मुक्त_input:
	अगर (ret)
		devm_kमुक्त(dev, input);

	वापस ret;
पूर्ण
