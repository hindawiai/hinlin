<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (C) 2021, Intel Corporation. */

#समावेश "ice_virtchnl_allowlist.h"

/* Purpose of this file is to share functionality to allowlist or denylist
 * opcodes used in PF <-> VF communication. Group of opcodes:
 * - शेष -> should be always allowed after creating VF,
 *   शेष_allowlist_opcodes
 * - opcodes needed by VF to work correctly, but not associated with caps ->
 *   should be allowed after successful VF resources allocation,
 *   working_allowlist_opcodes
 * - opcodes needed by VF when caps are activated
 *
 * Caps that करोn't use new opcodes (no opcodes should be allowed):
 * - VIRTCHNL_VF_OFFLOAD_RSS_AQ
 * - VIRTCHNL_VF_OFFLOAD_RSS_REG
 * - VIRTCHNL_VF_OFFLOAD_WB_ON_ITR
 * - VIRTCHNL_VF_OFFLOAD_CRC
 * - VIRTCHNL_VF_OFFLOAD_RX_POLLING
 * - VIRTCHNL_VF_OFFLOAD_RSS_PCTYPE_V2
 * - VIRTCHNL_VF_OFFLOAD_ENCAP
 * - VIRTCHNL_VF_OFFLOAD_ENCAP_CSUM
 * - VIRTCHNL_VF_OFFLOAD_RX_ENCAP_CSUM
 * - VIRTCHNL_VF_OFFLOAD_USO
 */

/* शेष opcodes to communicate with VF */
अटल स्थिर u32 शेष_allowlist_opcodes[] = अणु
	VIRTCHNL_OP_GET_VF_RESOURCES, VIRTCHNL_OP_VERSION, VIRTCHNL_OP_RESET_VF,
पूर्ण;

/* opcodes supported after successful VIRTCHNL_OP_GET_VF_RESOURCES */
अटल स्थिर u32 working_allowlist_opcodes[] = अणु
	VIRTCHNL_OP_CONFIG_TX_QUEUE, VIRTCHNL_OP_CONFIG_RX_QUEUE,
	VIRTCHNL_OP_CONFIG_VSI_QUEUES, VIRTCHNL_OP_CONFIG_IRQ_MAP,
	VIRTCHNL_OP_ENABLE_QUEUES, VIRTCHNL_OP_DISABLE_QUEUES,
	VIRTCHNL_OP_GET_STATS, VIRTCHNL_OP_EVENT,
पूर्ण;

/* VIRTCHNL_VF_OFFLOAD_L2 */
अटल स्थिर u32 l2_allowlist_opcodes[] = अणु
	VIRTCHNL_OP_ADD_ETH_ADDR, VIRTCHNL_OP_DEL_ETH_ADDR,
	VIRTCHNL_OP_CONFIG_PROMISCUOUS_MODE,
पूर्ण;

/* VIRTCHNL_VF_OFFLOAD_REQ_QUEUES */
अटल स्थिर u32 req_queues_allowlist_opcodes[] = अणु
	VIRTCHNL_OP_REQUEST_QUEUES,
पूर्ण;

/* VIRTCHNL_VF_OFFLOAD_VLAN */
अटल स्थिर u32 vlan_allowlist_opcodes[] = अणु
	VIRTCHNL_OP_ADD_VLAN, VIRTCHNL_OP_DEL_VLAN,
	VIRTCHNL_OP_ENABLE_VLAN_STRIPPING, VIRTCHNL_OP_DISABLE_VLAN_STRIPPING,
पूर्ण;

/* VIRTCHNL_VF_OFFLOAD_RSS_PF */
अटल स्थिर u32 rss_pf_allowlist_opcodes[] = अणु
	VIRTCHNL_OP_CONFIG_RSS_KEY, VIRTCHNL_OP_CONFIG_RSS_LUT,
	VIRTCHNL_OP_GET_RSS_HENA_CAPS, VIRTCHNL_OP_SET_RSS_HENA,
पूर्ण;

/* VIRTCHNL_VF_OFFLOAD_ADV_RSS_PF */
अटल स्थिर u32 adv_rss_pf_allowlist_opcodes[] = अणु
	VIRTCHNL_OP_ADD_RSS_CFG, VIRTCHNL_OP_DEL_RSS_CFG,
पूर्ण;

/* VIRTCHNL_VF_OFFLOAD_Fसूची_PF */
अटल स्थिर u32 fdir_pf_allowlist_opcodes[] = अणु
	VIRTCHNL_OP_ADD_Fसूची_FILTER, VIRTCHNL_OP_DEL_Fसूची_FILTER,
पूर्ण;

काष्ठा allowlist_opcode_info अणु
	स्थिर u32 *opcodes;
	माप_प्रकार size;
पूर्ण;

#घोषणा BIT_INDEX(caps) (HWEIGHT((caps) - 1))
#घोषणा ALLOW_ITEM(caps, list) \
	[BIT_INDEX(caps)] = अणु \
		.opcodes = list, \
		.size = ARRAY_SIZE(list) \
	पूर्ण
अटल स्थिर काष्ठा allowlist_opcode_info allowlist_opcodes[] = अणु
	ALLOW_ITEM(VIRTCHNL_VF_OFFLOAD_L2, l2_allowlist_opcodes),
	ALLOW_ITEM(VIRTCHNL_VF_OFFLOAD_REQ_QUEUES, req_queues_allowlist_opcodes),
	ALLOW_ITEM(VIRTCHNL_VF_OFFLOAD_VLAN, vlan_allowlist_opcodes),
	ALLOW_ITEM(VIRTCHNL_VF_OFFLOAD_RSS_PF, rss_pf_allowlist_opcodes),
	ALLOW_ITEM(VIRTCHNL_VF_OFFLOAD_ADV_RSS_PF, adv_rss_pf_allowlist_opcodes),
	ALLOW_ITEM(VIRTCHNL_VF_OFFLOAD_Fसूची_PF, fdir_pf_allowlist_opcodes),
पूर्ण;

/**
 * ice_vc_is_opcode_allowed - check अगर this opcode is allowed on this VF
 * @vf: poपूर्णांकer to VF काष्ठाure
 * @opcode: virtchnl opcode
 *
 * Return true अगर message is allowed on this VF
 */
bool ice_vc_is_opcode_allowed(काष्ठा ice_vf *vf, u32 opcode)
अणु
	अगर (opcode >= VIRTCHNL_OP_MAX)
		वापस false;

	वापस test_bit(opcode, vf->opcodes_allowlist);
पूर्ण

/**
 * ice_vc_allowlist_opcodes - allowlist selected opcodes
 * @vf: poपूर्णांकer to VF काष्ठाure
 * @opcodes: array of opocodes to allowlist
 * @size: size of opcodes array
 *
 * Function should be called to allowlist opcodes on VF.
 */
अटल व्योम
ice_vc_allowlist_opcodes(काष्ठा ice_vf *vf, स्थिर u32 *opcodes, माप_प्रकार size)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < size; i++)
		set_bit(opcodes[i], vf->opcodes_allowlist);
पूर्ण

/**
 * ice_vc_clear_allowlist - clear all allowlist opcodes
 * @vf: poपूर्णांकer to VF काष्ठाure
 */
अटल व्योम ice_vc_clear_allowlist(काष्ठा ice_vf *vf)
अणु
	biपंचांगap_zero(vf->opcodes_allowlist, VIRTCHNL_OP_MAX);
पूर्ण

/**
 * ice_vc_set_शेष_allowlist - allowlist शेष opcodes क्रम VF
 * @vf: poपूर्णांकer to VF काष्ठाure
 */
व्योम ice_vc_set_शेष_allowlist(काष्ठा ice_vf *vf)
अणु
	ice_vc_clear_allowlist(vf);
	ice_vc_allowlist_opcodes(vf, शेष_allowlist_opcodes,
				 ARRAY_SIZE(शेष_allowlist_opcodes));
पूर्ण

/**
 * ice_vc_set_working_allowlist - allowlist opcodes needed to by VF to work
 * @vf: poपूर्णांकer to VF काष्ठाure
 *
 * allowlist opcodes that aren't associated with specअगरic caps, but
 * are needed by VF to work.
 */
व्योम ice_vc_set_working_allowlist(काष्ठा ice_vf *vf)
अणु
	ice_vc_allowlist_opcodes(vf, working_allowlist_opcodes,
				 ARRAY_SIZE(working_allowlist_opcodes));
पूर्ण

/**
 * ice_vc_set_caps_allowlist - allowlist VF opcodes according caps
 * @vf: poपूर्णांकer to VF काष्ठाure
 */
व्योम ice_vc_set_caps_allowlist(काष्ठा ice_vf *vf)
अणु
	अचिन्हित दीर्घ caps = vf->driver_caps;
	अचिन्हित पूर्णांक i;

	क्रम_each_set_bit(i, &caps, ARRAY_SIZE(allowlist_opcodes))
		ice_vc_allowlist_opcodes(vf, allowlist_opcodes[i].opcodes,
					 allowlist_opcodes[i].size);
पूर्ण
