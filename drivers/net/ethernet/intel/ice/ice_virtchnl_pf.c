<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2018, Intel Corporation. */

#समावेश "ice.h"
#समावेश "ice_base.h"
#समावेश "ice_lib.h"
#समावेश "ice_fltr.h"
#समावेश "ice_flow.h"
#समावेश "ice_virtchnl_allowlist.h"

#घोषणा FIELD_SELECTOR(proto_hdr_field) \
		BIT((proto_hdr_field) & PROTO_HDR_FIELD_MASK)

काष्ठा ice_vc_hdr_match_type अणु
	u32 vc_hdr;	/* virtchnl headers (VIRTCHNL_PROTO_HDR_XXX) */
	u32 ice_hdr;	/* ice headers (ICE_FLOW_SEG_HDR_XXX) */
पूर्ण;

अटल स्थिर काष्ठा ice_vc_hdr_match_type ice_vc_hdr_list_os[] = अणु
	अणुVIRTCHNL_PROTO_HDR_NONE,	ICE_FLOW_SEG_HDR_NONEपूर्ण,
	अणुVIRTCHNL_PROTO_HDR_IPV4,	ICE_FLOW_SEG_HDR_IPV4 |
					ICE_FLOW_SEG_HDR_IPV_OTHERपूर्ण,
	अणुVIRTCHNL_PROTO_HDR_IPV6,	ICE_FLOW_SEG_HDR_IPV6 |
					ICE_FLOW_SEG_HDR_IPV_OTHERपूर्ण,
	अणुVIRTCHNL_PROTO_HDR_TCP,	ICE_FLOW_SEG_HDR_TCPपूर्ण,
	अणुVIRTCHNL_PROTO_HDR_UDP,	ICE_FLOW_SEG_HDR_UDPपूर्ण,
	अणुVIRTCHNL_PROTO_HDR_SCTP,	ICE_FLOW_SEG_HDR_SCTPपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ice_vc_hdr_match_type ice_vc_hdr_list_comms[] = अणु
	अणुVIRTCHNL_PROTO_HDR_NONE,	ICE_FLOW_SEG_HDR_NONEपूर्ण,
	अणुVIRTCHNL_PROTO_HDR_ETH,	ICE_FLOW_SEG_HDR_ETHपूर्ण,
	अणुVIRTCHNL_PROTO_HDR_S_VLAN,	ICE_FLOW_SEG_HDR_VLANपूर्ण,
	अणुVIRTCHNL_PROTO_HDR_C_VLAN,	ICE_FLOW_SEG_HDR_VLANपूर्ण,
	अणुVIRTCHNL_PROTO_HDR_IPV4,	ICE_FLOW_SEG_HDR_IPV4 |
					ICE_FLOW_SEG_HDR_IPV_OTHERपूर्ण,
	अणुVIRTCHNL_PROTO_HDR_IPV6,	ICE_FLOW_SEG_HDR_IPV6 |
					ICE_FLOW_SEG_HDR_IPV_OTHERपूर्ण,
	अणुVIRTCHNL_PROTO_HDR_TCP,	ICE_FLOW_SEG_HDR_TCPपूर्ण,
	अणुVIRTCHNL_PROTO_HDR_UDP,	ICE_FLOW_SEG_HDR_UDPपूर्ण,
	अणुVIRTCHNL_PROTO_HDR_SCTP,	ICE_FLOW_SEG_HDR_SCTPपूर्ण,
	अणुVIRTCHNL_PROTO_HDR_PPPOE,	ICE_FLOW_SEG_HDR_PPPOEपूर्ण,
	अणुVIRTCHNL_PROTO_HDR_GTPU_IP,	ICE_FLOW_SEG_HDR_GTPU_IPपूर्ण,
	अणुVIRTCHNL_PROTO_HDR_GTPU_EH,	ICE_FLOW_SEG_HDR_GTPU_EHपूर्ण,
	अणुVIRTCHNL_PROTO_HDR_GTPU_EH_PDU_DWN,
					ICE_FLOW_SEG_HDR_GTPU_DWNपूर्ण,
	अणुVIRTCHNL_PROTO_HDR_GTPU_EH_PDU_UP,
					ICE_FLOW_SEG_HDR_GTPU_UPपूर्ण,
	अणुVIRTCHNL_PROTO_HDR_L2TPV3,	ICE_FLOW_SEG_HDR_L2TPV3पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_ESP,	ICE_FLOW_SEG_HDR_ESPपूर्ण,
	अणुVIRTCHNL_PROTO_HDR_AH,		ICE_FLOW_SEG_HDR_AHपूर्ण,
	अणुVIRTCHNL_PROTO_HDR_PFCP,	ICE_FLOW_SEG_HDR_PFCP_SESSIONपूर्ण,
पूर्ण;

काष्ठा ice_vc_hash_field_match_type अणु
	u32 vc_hdr;		/* virtchnl headers
				 * (VIRTCHNL_PROTO_HDR_XXX)
				 */
	u32 vc_hash_field;	/* virtchnl hash fields selector
				 * FIELD_SELECTOR((VIRTCHNL_PROTO_HDR_ETH_XXX))
				 */
	u64 ice_hash_field;	/* ice hash fields
				 * (BIT_ULL(ICE_FLOW_FIELD_IDX_XXX))
				 */
पूर्ण;

अटल स्थिर काष्ठा
ice_vc_hash_field_match_type ice_vc_hash_field_list_os[] = अणु
	अणुVIRTCHNL_PROTO_HDR_IPV4, FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_IPV4_SRC),
		BIT_ULL(ICE_FLOW_FIELD_IDX_IPV4_SA)पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_IPV4, FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_IPV4_DST),
		BIT_ULL(ICE_FLOW_FIELD_IDX_IPV4_DA)पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_IPV4, FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_IPV4_SRC) |
		FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_IPV4_DST),
		ICE_FLOW_HASH_IPV4पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_IPV4, FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_IPV4_SRC) |
		FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_IPV4_PROT),
		BIT_ULL(ICE_FLOW_FIELD_IDX_IPV4_SA) |
		BIT_ULL(ICE_FLOW_FIELD_IDX_IPV4_PROT)पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_IPV4, FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_IPV4_DST) |
		FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_IPV4_PROT),
		BIT_ULL(ICE_FLOW_FIELD_IDX_IPV4_DA) |
		BIT_ULL(ICE_FLOW_FIELD_IDX_IPV4_PROT)पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_IPV4, FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_IPV4_SRC) |
		FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_IPV4_DST) |
		FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_IPV4_PROT),
		ICE_FLOW_HASH_IPV4 | BIT_ULL(ICE_FLOW_FIELD_IDX_IPV4_PROT)पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_IPV4, FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_IPV4_PROT),
		BIT_ULL(ICE_FLOW_FIELD_IDX_IPV4_PROT)पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_IPV6, FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_IPV6_SRC),
		BIT_ULL(ICE_FLOW_FIELD_IDX_IPV6_SA)पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_IPV6, FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_IPV6_DST),
		BIT_ULL(ICE_FLOW_FIELD_IDX_IPV6_DA)पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_IPV6, FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_IPV6_SRC) |
		FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_IPV6_DST),
		ICE_FLOW_HASH_IPV6पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_IPV6, FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_IPV6_SRC) |
		FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_IPV6_PROT),
		BIT_ULL(ICE_FLOW_FIELD_IDX_IPV6_SA) |
		BIT_ULL(ICE_FLOW_FIELD_IDX_IPV6_PROT)पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_IPV6, FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_IPV6_DST) |
		FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_IPV6_PROT),
		BIT_ULL(ICE_FLOW_FIELD_IDX_IPV6_DA) |
		BIT_ULL(ICE_FLOW_FIELD_IDX_IPV6_PROT)पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_IPV6, FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_IPV6_SRC) |
		FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_IPV6_DST) |
		FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_IPV6_PROT),
		ICE_FLOW_HASH_IPV6 | BIT_ULL(ICE_FLOW_FIELD_IDX_IPV6_PROT)पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_IPV6, FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_IPV6_PROT),
		BIT_ULL(ICE_FLOW_FIELD_IDX_IPV6_PROT)पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_TCP,
		FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_TCP_SRC_PORT),
		BIT_ULL(ICE_FLOW_FIELD_IDX_TCP_SRC_PORT)पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_TCP,
		FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_TCP_DST_PORT),
		BIT_ULL(ICE_FLOW_FIELD_IDX_TCP_DST_PORT)पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_TCP,
		FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_TCP_SRC_PORT) |
		FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_TCP_DST_PORT),
		ICE_FLOW_HASH_TCP_PORTपूर्ण,
	अणुVIRTCHNL_PROTO_HDR_UDP,
		FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_UDP_SRC_PORT),
		BIT_ULL(ICE_FLOW_FIELD_IDX_UDP_SRC_PORT)पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_UDP,
		FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_UDP_DST_PORT),
		BIT_ULL(ICE_FLOW_FIELD_IDX_UDP_DST_PORT)पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_UDP,
		FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_UDP_SRC_PORT) |
		FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_UDP_DST_PORT),
		ICE_FLOW_HASH_UDP_PORTपूर्ण,
	अणुVIRTCHNL_PROTO_HDR_SCTP,
		FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_SCTP_SRC_PORT),
		BIT_ULL(ICE_FLOW_FIELD_IDX_SCTP_SRC_PORT)पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_SCTP,
		FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_SCTP_DST_PORT),
		BIT_ULL(ICE_FLOW_FIELD_IDX_SCTP_DST_PORT)पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_SCTP,
		FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_SCTP_SRC_PORT) |
		FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_SCTP_DST_PORT),
		ICE_FLOW_HASH_SCTP_PORTपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा
ice_vc_hash_field_match_type ice_vc_hash_field_list_comms[] = अणु
	अणुVIRTCHNL_PROTO_HDR_ETH, FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_ETH_SRC),
		BIT_ULL(ICE_FLOW_FIELD_IDX_ETH_SA)पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_ETH, FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_ETH_DST),
		BIT_ULL(ICE_FLOW_FIELD_IDX_ETH_DA)पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_ETH, FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_ETH_SRC) |
		FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_ETH_DST),
		ICE_FLOW_HASH_ETHपूर्ण,
	अणुVIRTCHNL_PROTO_HDR_ETH,
		FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_ETH_ETHERTYPE),
		BIT_ULL(ICE_FLOW_FIELD_IDX_ETH_TYPE)पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_S_VLAN,
		FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_S_VLAN_ID),
		BIT_ULL(ICE_FLOW_FIELD_IDX_S_VLAN)पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_C_VLAN,
		FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_C_VLAN_ID),
		BIT_ULL(ICE_FLOW_FIELD_IDX_C_VLAN)पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_IPV4, FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_IPV4_SRC),
		BIT_ULL(ICE_FLOW_FIELD_IDX_IPV4_SA)पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_IPV4, FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_IPV4_DST),
		BIT_ULL(ICE_FLOW_FIELD_IDX_IPV4_DA)पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_IPV4, FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_IPV4_SRC) |
		FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_IPV4_DST),
		ICE_FLOW_HASH_IPV4पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_IPV4, FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_IPV4_SRC) |
		FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_IPV4_PROT),
		BIT_ULL(ICE_FLOW_FIELD_IDX_IPV4_SA) |
		BIT_ULL(ICE_FLOW_FIELD_IDX_IPV4_PROT)पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_IPV4, FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_IPV4_DST) |
		FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_IPV4_PROT),
		BIT_ULL(ICE_FLOW_FIELD_IDX_IPV4_DA) |
		BIT_ULL(ICE_FLOW_FIELD_IDX_IPV4_PROT)पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_IPV4, FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_IPV4_SRC) |
		FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_IPV4_DST) |
		FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_IPV4_PROT),
		ICE_FLOW_HASH_IPV4 | BIT_ULL(ICE_FLOW_FIELD_IDX_IPV4_PROT)पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_IPV4, FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_IPV4_PROT),
		BIT_ULL(ICE_FLOW_FIELD_IDX_IPV4_PROT)पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_IPV6, FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_IPV6_SRC),
		BIT_ULL(ICE_FLOW_FIELD_IDX_IPV6_SA)पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_IPV6, FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_IPV6_DST),
		BIT_ULL(ICE_FLOW_FIELD_IDX_IPV6_DA)पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_IPV6, FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_IPV6_SRC) |
		FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_IPV6_DST),
		ICE_FLOW_HASH_IPV6पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_IPV6, FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_IPV6_SRC) |
		FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_IPV6_PROT),
		BIT_ULL(ICE_FLOW_FIELD_IDX_IPV6_SA) |
		BIT_ULL(ICE_FLOW_FIELD_IDX_IPV6_PROT)पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_IPV6, FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_IPV6_DST) |
		FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_IPV6_PROT),
		BIT_ULL(ICE_FLOW_FIELD_IDX_IPV6_DA) |
		BIT_ULL(ICE_FLOW_FIELD_IDX_IPV6_PROT)पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_IPV6, FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_IPV6_SRC) |
		FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_IPV6_DST) |
		FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_IPV6_PROT),
		ICE_FLOW_HASH_IPV6 | BIT_ULL(ICE_FLOW_FIELD_IDX_IPV6_PROT)पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_IPV6, FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_IPV6_PROT),
		BIT_ULL(ICE_FLOW_FIELD_IDX_IPV6_PROT)पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_TCP,
		FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_TCP_SRC_PORT),
		BIT_ULL(ICE_FLOW_FIELD_IDX_TCP_SRC_PORT)पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_TCP,
		FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_TCP_DST_PORT),
		BIT_ULL(ICE_FLOW_FIELD_IDX_TCP_DST_PORT)पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_TCP,
		FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_TCP_SRC_PORT) |
		FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_TCP_DST_PORT),
		ICE_FLOW_HASH_TCP_PORTपूर्ण,
	अणुVIRTCHNL_PROTO_HDR_UDP,
		FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_UDP_SRC_PORT),
		BIT_ULL(ICE_FLOW_FIELD_IDX_UDP_SRC_PORT)पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_UDP,
		FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_UDP_DST_PORT),
		BIT_ULL(ICE_FLOW_FIELD_IDX_UDP_DST_PORT)पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_UDP,
		FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_UDP_SRC_PORT) |
		FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_UDP_DST_PORT),
		ICE_FLOW_HASH_UDP_PORTपूर्ण,
	अणुVIRTCHNL_PROTO_HDR_SCTP,
		FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_SCTP_SRC_PORT),
		BIT_ULL(ICE_FLOW_FIELD_IDX_SCTP_SRC_PORT)पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_SCTP,
		FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_SCTP_DST_PORT),
		BIT_ULL(ICE_FLOW_FIELD_IDX_SCTP_DST_PORT)पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_SCTP,
		FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_SCTP_SRC_PORT) |
		FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_SCTP_DST_PORT),
		ICE_FLOW_HASH_SCTP_PORTपूर्ण,
	अणुVIRTCHNL_PROTO_HDR_PPPOE,
		FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_PPPOE_SESS_ID),
		BIT_ULL(ICE_FLOW_FIELD_IDX_PPPOE_SESS_ID)पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_GTPU_IP,
		FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_GTPU_IP_TEID),
		BIT_ULL(ICE_FLOW_FIELD_IDX_GTPU_IP_TEID)पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_L2TPV3,
		FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_L2TPV3_SESS_ID),
		BIT_ULL(ICE_FLOW_FIELD_IDX_L2TPV3_SESS_ID)पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_ESP, FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_ESP_SPI),
		BIT_ULL(ICE_FLOW_FIELD_IDX_ESP_SPI)पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_AH, FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_AH_SPI),
		BIT_ULL(ICE_FLOW_FIELD_IDX_AH_SPI)पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_PFCP, FIELD_SELECTOR(VIRTCHNL_PROTO_HDR_PFCP_SEID),
		BIT_ULL(ICE_FLOW_FIELD_IDX_PFCP_SEID)पूर्ण,
पूर्ण;

/**
 * ice_get_vf_vsi - get VF's VSI based on the stored index
 * @vf: VF used to get VSI
 */
अटल काष्ठा ice_vsi *ice_get_vf_vsi(काष्ठा ice_vf *vf)
अणु
	वापस vf->pf->vsi[vf->lan_vsi_idx];
पूर्ण

/**
 * ice_validate_vf_id - helper to check अगर VF ID is valid
 * @pf: poपूर्णांकer to the PF काष्ठाure
 * @vf_id: the ID of the VF to check
 */
अटल पूर्णांक ice_validate_vf_id(काष्ठा ice_pf *pf, u16 vf_id)
अणु
	/* vf_id range is only valid क्रम 0-255, and should always be अचिन्हित */
	अगर (vf_id >= pf->num_alloc_vfs) अणु
		dev_err(ice_pf_to_dev(pf), "Invalid VF ID: %u\n", vf_id);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * ice_check_vf_init - helper to check अगर VF init complete
 * @pf: poपूर्णांकer to the PF काष्ठाure
 * @vf: the poपूर्णांकer to the VF to check
 */
अटल पूर्णांक ice_check_vf_init(काष्ठा ice_pf *pf, काष्ठा ice_vf *vf)
अणु
	अगर (!test_bit(ICE_VF_STATE_INIT, vf->vf_states)) अणु
		dev_err(ice_pf_to_dev(pf), "VF ID: %u in reset. Try again.\n",
			vf->vf_id);
		वापस -EBUSY;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * ice_err_to_virt_err - translate errors क्रम VF वापस code
 * @ice_err: error वापस code
 */
अटल क्रमागत virtchnl_status_code ice_err_to_virt_err(क्रमागत ice_status ice_err)
अणु
	चयन (ice_err) अणु
	हाल ICE_SUCCESS:
		वापस VIRTCHNL_STATUS_SUCCESS;
	हाल ICE_ERR_BAD_PTR:
	हाल ICE_ERR_INVAL_SIZE:
	हाल ICE_ERR_DEVICE_NOT_SUPPORTED:
	हाल ICE_ERR_PARAM:
	हाल ICE_ERR_CFG:
		वापस VIRTCHNL_STATUS_ERR_PARAM;
	हाल ICE_ERR_NO_MEMORY:
		वापस VIRTCHNL_STATUS_ERR_NO_MEMORY;
	हाल ICE_ERR_NOT_READY:
	हाल ICE_ERR_RESET_FAILED:
	हाल ICE_ERR_FW_API_VER:
	हाल ICE_ERR_AQ_ERROR:
	हाल ICE_ERR_AQ_TIMEOUT:
	हाल ICE_ERR_AQ_FULL:
	हाल ICE_ERR_AQ_NO_WORK:
	हाल ICE_ERR_AQ_EMPTY:
		वापस VIRTCHNL_STATUS_ERR_ADMIN_QUEUE_ERROR;
	शेष:
		वापस VIRTCHNL_STATUS_ERR_NOT_SUPPORTED;
	पूर्ण
पूर्ण

/**
 * ice_vc_vf_broadcast - Broadcast a message to all VFs on PF
 * @pf: poपूर्णांकer to the PF काष्ठाure
 * @v_opcode: operation code
 * @v_retval: वापस value
 * @msg: poपूर्णांकer to the msg buffer
 * @msglen: msg length
 */
अटल व्योम
ice_vc_vf_broadcast(काष्ठा ice_pf *pf, क्रमागत virtchnl_ops v_opcode,
		    क्रमागत virtchnl_status_code v_retval, u8 *msg, u16 msglen)
अणु
	काष्ठा ice_hw *hw = &pf->hw;
	अचिन्हित पूर्णांक i;

	ice_क्रम_each_vf(pf, i) अणु
		काष्ठा ice_vf *vf = &pf->vf[i];

		/* Not all vfs are enabled so skip the ones that are not */
		अगर (!test_bit(ICE_VF_STATE_INIT, vf->vf_states) &&
		    !test_bit(ICE_VF_STATE_ACTIVE, vf->vf_states))
			जारी;

		/* Ignore वापस value on purpose - a given VF may fail, but
		 * we need to keep going and send to all of them
		 */
		ice_aq_send_msg_to_vf(hw, vf->vf_id, v_opcode, v_retval, msg,
				      msglen, शून्य);
	पूर्ण
पूर्ण

/**
 * ice_set_pfe_link - Set the link speed/status of the virtchnl_pf_event
 * @vf: poपूर्णांकer to the VF काष्ठाure
 * @pfe: poपूर्णांकer to the virtchnl_pf_event to set link speed/status क्रम
 * @ice_link_speed: link speed specअगरied by ICE_AQ_LINK_SPEED_*
 * @link_up: whether or not to set the link up/करोwn
 */
अटल व्योम
ice_set_pfe_link(काष्ठा ice_vf *vf, काष्ठा virtchnl_pf_event *pfe,
		 पूर्णांक ice_link_speed, bool link_up)
अणु
	अगर (vf->driver_caps & VIRTCHNL_VF_CAP_ADV_LINK_SPEED) अणु
		pfe->event_data.link_event_adv.link_status = link_up;
		/* Speed in Mbps */
		pfe->event_data.link_event_adv.link_speed =
			ice_conv_link_speed_to_virtchnl(true, ice_link_speed);
	पूर्ण अन्यथा अणु
		pfe->event_data.link_event.link_status = link_up;
		/* Legacy method क्रम virtchnl link speeds */
		pfe->event_data.link_event.link_speed =
			(क्रमागत virtchnl_link_speed)
			ice_conv_link_speed_to_virtchnl(false, ice_link_speed);
	पूर्ण
पूर्ण

/**
 * ice_vf_has_no_qs_ena - check अगर the VF has any Rx or Tx queues enabled
 * @vf: the VF to check
 *
 * Returns true अगर the VF has no Rx and no Tx queues enabled and वापसs false
 * otherwise
 */
अटल bool ice_vf_has_no_qs_ena(काष्ठा ice_vf *vf)
अणु
	वापस (!biपंचांगap_weight(vf->rxq_ena, ICE_MAX_RSS_QS_PER_VF) &&
		!biपंचांगap_weight(vf->txq_ena, ICE_MAX_RSS_QS_PER_VF));
पूर्ण

/**
 * ice_is_vf_link_up - check अगर the VF's link is up
 * @vf: VF to check अगर link is up
 */
अटल bool ice_is_vf_link_up(काष्ठा ice_vf *vf)
अणु
	काष्ठा ice_pf *pf = vf->pf;

	अगर (ice_check_vf_init(pf, vf))
		वापस false;

	अगर (ice_vf_has_no_qs_ena(vf))
		वापस false;
	अन्यथा अगर (vf->link_क्रमced)
		वापस vf->link_up;
	अन्यथा
		वापस pf->hw.port_info->phy.link_info.link_info &
			ICE_AQ_LINK_UP;
पूर्ण

/**
 * ice_vc_notअगरy_vf_link_state - Inक्रमm a VF of link status
 * @vf: poपूर्णांकer to the VF काष्ठाure
 *
 * send a link status message to a single VF
 */
अटल व्योम ice_vc_notअगरy_vf_link_state(काष्ठा ice_vf *vf)
अणु
	काष्ठा virtchnl_pf_event pfe = अणु 0 पूर्ण;
	काष्ठा ice_hw *hw = &vf->pf->hw;

	pfe.event = VIRTCHNL_EVENT_LINK_CHANGE;
	pfe.severity = PF_EVENT_SEVERITY_INFO;

	अगर (ice_is_vf_link_up(vf))
		ice_set_pfe_link(vf, &pfe,
				 hw->port_info->phy.link_info.link_speed, true);
	अन्यथा
		ice_set_pfe_link(vf, &pfe, ICE_AQ_LINK_SPEED_UNKNOWN, false);

	ice_aq_send_msg_to_vf(hw, vf->vf_id, VIRTCHNL_OP_EVENT,
			      VIRTCHNL_STATUS_SUCCESS, (u8 *)&pfe,
			      माप(pfe), शून्य);
पूर्ण

/**
 * ice_vf_invalidate_vsi - invalidate vsi_idx/vsi_num to हटाओ VSI access
 * @vf: VF to हटाओ access to VSI क्रम
 */
अटल व्योम ice_vf_invalidate_vsi(काष्ठा ice_vf *vf)
अणु
	vf->lan_vsi_idx = ICE_NO_VSI;
	vf->lan_vsi_num = ICE_NO_VSI;
पूर्ण

/**
 * ice_vf_vsi_release - invalidate the VF's VSI after मुक्तing it
 * @vf: invalidate this VF's VSI after मुक्तing it
 */
अटल व्योम ice_vf_vsi_release(काष्ठा ice_vf *vf)
अणु
	ice_vsi_release(ice_get_vf_vsi(vf));
	ice_vf_invalidate_vsi(vf);
पूर्ण

/**
 * ice_vf_ctrl_invalidate_vsi - invalidate ctrl_vsi_idx to हटाओ VSI access
 * @vf: VF that control VSI is being invalidated on
 */
अटल व्योम ice_vf_ctrl_invalidate_vsi(काष्ठा ice_vf *vf)
अणु
	vf->ctrl_vsi_idx = ICE_NO_VSI;
पूर्ण

/**
 * ice_vf_ctrl_vsi_release - invalidate the VF's control VSI after मुक्तing it
 * @vf: VF that control VSI is being released on
 */
अटल व्योम ice_vf_ctrl_vsi_release(काष्ठा ice_vf *vf)
अणु
	ice_vsi_release(vf->pf->vsi[vf->ctrl_vsi_idx]);
	ice_vf_ctrl_invalidate_vsi(vf);
पूर्ण

/**
 * ice_मुक्त_vf_res - Free a VF's resources
 * @vf: poपूर्णांकer to the VF info
 */
अटल व्योम ice_मुक्त_vf_res(काष्ठा ice_vf *vf)
अणु
	काष्ठा ice_pf *pf = vf->pf;
	पूर्णांक i, last_vector_idx;

	/* First, disable VF's configuration API to prevent OS from
	 * accessing the VF's VSI after it's मुक्तd or invalidated.
	 */
	clear_bit(ICE_VF_STATE_INIT, vf->vf_states);
	ice_vf_fdir_निकास(vf);
	/* मुक्त VF control VSI */
	अगर (vf->ctrl_vsi_idx != ICE_NO_VSI)
		ice_vf_ctrl_vsi_release(vf);

	/* मुक्त VSI and disconnect it from the parent uplink */
	अगर (vf->lan_vsi_idx != ICE_NO_VSI) अणु
		ice_vf_vsi_release(vf);
		vf->num_mac = 0;
	पूर्ण

	last_vector_idx = vf->first_vector_idx + pf->num_msix_per_vf - 1;

	/* clear VF MDD event inक्रमmation */
	स_रखो(&vf->mdd_tx_events, 0, माप(vf->mdd_tx_events));
	स_रखो(&vf->mdd_rx_events, 0, माप(vf->mdd_rx_events));

	/* Disable पूर्णांकerrupts so that VF starts in a known state */
	क्रम (i = vf->first_vector_idx; i <= last_vector_idx; i++) अणु
		wr32(&pf->hw, GLINT_DYN_CTL(i), GLINT_DYN_CTL_CLEARPBA_M);
		ice_flush(&pf->hw);
	पूर्ण
	/* reset some of the state variables keeping track of the resources */
	clear_bit(ICE_VF_STATE_MC_PROMISC, vf->vf_states);
	clear_bit(ICE_VF_STATE_UC_PROMISC, vf->vf_states);
पूर्ण

/**
 * ice_dis_vf_mappings
 * @vf: poपूर्णांकer to the VF काष्ठाure
 */
अटल व्योम ice_dis_vf_mappings(काष्ठा ice_vf *vf)
अणु
	काष्ठा ice_pf *pf = vf->pf;
	काष्ठा ice_vsi *vsi;
	काष्ठा device *dev;
	पूर्णांक first, last, v;
	काष्ठा ice_hw *hw;

	hw = &pf->hw;
	vsi = ice_get_vf_vsi(vf);

	dev = ice_pf_to_dev(pf);
	wr32(hw, VPINT_ALLOC(vf->vf_id), 0);
	wr32(hw, VPINT_ALLOC_PCI(vf->vf_id), 0);

	first = vf->first_vector_idx;
	last = first + pf->num_msix_per_vf - 1;
	क्रम (v = first; v <= last; v++) अणु
		u32 reg;

		reg = (((1 << GLINT_VECT2FUNC_IS_PF_S) &
			GLINT_VECT2FUNC_IS_PF_M) |
		       ((hw->pf_id << GLINT_VECT2FUNC_PF_NUM_S) &
			GLINT_VECT2FUNC_PF_NUM_M));
		wr32(hw, GLINT_VECT2FUNC(v), reg);
	पूर्ण

	अगर (vsi->tx_mapping_mode == ICE_VSI_MAP_CONTIG)
		wr32(hw, VPLAN_TX_QBASE(vf->vf_id), 0);
	अन्यथा
		dev_err(dev, "Scattered mode for VF Tx queues is not yet implemented\n");

	अगर (vsi->rx_mapping_mode == ICE_VSI_MAP_CONTIG)
		wr32(hw, VPLAN_RX_QBASE(vf->vf_id), 0);
	अन्यथा
		dev_err(dev, "Scattered mode for VF Rx queues is not yet implemented\n");
पूर्ण

/**
 * ice_sriov_मुक्त_msix_res - Reset/मुक्त any used MSIX resources
 * @pf: poपूर्णांकer to the PF काष्ठाure
 *
 * Since no MSIX entries are taken from the pf->irq_tracker then just clear
 * the pf->sriov_base_vector.
 *
 * Returns 0 on success, and -EINVAL on error.
 */
अटल पूर्णांक ice_sriov_मुक्त_msix_res(काष्ठा ice_pf *pf)
अणु
	काष्ठा ice_res_tracker *res;

	अगर (!pf)
		वापस -EINVAL;

	res = pf->irq_tracker;
	अगर (!res)
		वापस -EINVAL;

	/* give back irq_tracker resources used */
	WARN_ON(pf->sriov_base_vector < res->num_entries);

	pf->sriov_base_vector = 0;

	वापस 0;
पूर्ण

/**
 * ice_set_vf_state_qs_dis - Set VF queues state to disabled
 * @vf: poपूर्णांकer to the VF काष्ठाure
 */
व्योम ice_set_vf_state_qs_dis(काष्ठा ice_vf *vf)
अणु
	/* Clear Rx/Tx enabled queues flag */
	biपंचांगap_zero(vf->txq_ena, ICE_MAX_RSS_QS_PER_VF);
	biपंचांगap_zero(vf->rxq_ena, ICE_MAX_RSS_QS_PER_VF);
	clear_bit(ICE_VF_STATE_QS_ENA, vf->vf_states);
पूर्ण

/**
 * ice_dis_vf_qs - Disable the VF queues
 * @vf: poपूर्णांकer to the VF काष्ठाure
 */
अटल व्योम ice_dis_vf_qs(काष्ठा ice_vf *vf)
अणु
	काष्ठा ice_vsi *vsi = ice_get_vf_vsi(vf);

	ice_vsi_stop_lan_tx_rings(vsi, ICE_NO_RESET, vf->vf_id);
	ice_vsi_stop_all_rx_rings(vsi);
	ice_set_vf_state_qs_dis(vf);
पूर्ण

/**
 * ice_मुक्त_vfs - Free all VFs
 * @pf: poपूर्णांकer to the PF काष्ठाure
 */
व्योम ice_मुक्त_vfs(काष्ठा ice_pf *pf)
अणु
	काष्ठा device *dev = ice_pf_to_dev(pf);
	काष्ठा ice_hw *hw = &pf->hw;
	अचिन्हित पूर्णांक पंचांगp, i;

	अगर (!pf->vf)
		वापस;

	जबतक (test_and_set_bit(ICE_VF_DIS, pf->state))
		usleep_range(1000, 2000);

	/* Disable IOV beक्रमe मुक्तing resources. This lets any VF drivers
	 * running in the host get themselves cleaned up beक्रमe we yank
	 * the carpet out from underneath their feet.
	 */
	अगर (!pci_vfs_asचिन्हित(pf->pdev))
		pci_disable_sriov(pf->pdev);
	अन्यथा
		dev_warn(dev, "VFs are assigned - not disabling SR-IOV\n");

	/* Aव्योम रुको समय by stopping all VFs at the same समय */
	ice_क्रम_each_vf(pf, i)
		अगर (test_bit(ICE_VF_STATE_QS_ENA, pf->vf[i].vf_states))
			ice_dis_vf_qs(&pf->vf[i]);

	पंचांगp = pf->num_alloc_vfs;
	pf->num_qps_per_vf = 0;
	pf->num_alloc_vfs = 0;
	क्रम (i = 0; i < पंचांगp; i++) अणु
		अगर (test_bit(ICE_VF_STATE_INIT, pf->vf[i].vf_states)) अणु
			/* disable VF qp mappings and set VF disable state */
			ice_dis_vf_mappings(&pf->vf[i]);
			set_bit(ICE_VF_STATE_DIS, pf->vf[i].vf_states);
			ice_मुक्त_vf_res(&pf->vf[i]);
		पूर्ण
	पूर्ण

	अगर (ice_sriov_मुक्त_msix_res(pf))
		dev_err(dev, "Failed to free MSIX resources used by SR-IOV\n");

	devm_kमुक्त(dev, pf->vf);
	pf->vf = शून्य;

	/* This check is क्रम when the driver is unloaded जबतक VFs are
	 * asचिन्हित. Setting the number of VFs to 0 through sysfs is caught
	 * beक्रमe this function ever माला_लो called.
	 */
	अगर (!pci_vfs_asचिन्हित(pf->pdev)) अणु
		अचिन्हित पूर्णांक vf_id;

		/* Acknowledge VFLR क्रम all VFs. Without this, VFs will fail to
		 * work correctly when SR-IOV माला_लो re-enabled.
		 */
		क्रम (vf_id = 0; vf_id < पंचांगp; vf_id++) अणु
			u32 reg_idx, bit_idx;

			reg_idx = (hw->func_caps.vf_base_id + vf_id) / 32;
			bit_idx = (hw->func_caps.vf_base_id + vf_id) % 32;
			wr32(hw, GLGEN_VFLRSTAT(reg_idx), BIT(bit_idx));
		पूर्ण
	पूर्ण

	/* clear malicious info अगर the VFs are getting released */
	क्रम (i = 0; i < पंचांगp; i++)
		अगर (ice_mbx_clear_malvf(&hw->mbx_snapshot, pf->malvfs,
					ICE_MAX_VF_COUNT, i))
			dev_dbg(dev, "failed to clear malicious VF state for VF %u\n",
				i);

	clear_bit(ICE_VF_DIS, pf->state);
	clear_bit(ICE_FLAG_SRIOV_ENA, pf->flags);
पूर्ण

/**
 * ice_trigger_vf_reset - Reset a VF on HW
 * @vf: poपूर्णांकer to the VF काष्ठाure
 * @is_vflr: true अगर VFLR was issued, false अगर not
 * @is_pfr: true अगर the reset was triggered due to a previous PFR
 *
 * Trigger hardware to start a reset क्रम a particular VF. Expects the caller
 * to रुको the proper amount of समय to allow hardware to reset the VF beक्रमe
 * it cleans up and restores VF functionality.
 */
अटल व्योम ice_trigger_vf_reset(काष्ठा ice_vf *vf, bool is_vflr, bool is_pfr)
अणु
	काष्ठा ice_pf *pf = vf->pf;
	u32 reg, reg_idx, bit_idx;
	अचिन्हित पूर्णांक vf_असल_id, i;
	काष्ठा device *dev;
	काष्ठा ice_hw *hw;

	dev = ice_pf_to_dev(pf);
	hw = &pf->hw;
	vf_असल_id = vf->vf_id + hw->func_caps.vf_base_id;

	/* Inक्रमm VF that it is no दीर्घer active, as a warning */
	clear_bit(ICE_VF_STATE_ACTIVE, vf->vf_states);

	/* Disable VF's configuration API during reset. The flag is re-enabled
	 * when it's safe again to access VF's VSI.
	 */
	clear_bit(ICE_VF_STATE_INIT, vf->vf_states);

	/* VF_MBX_ARQLEN and VF_MBX_ATQLEN are cleared by PFR, so the driver
	 * needs to clear them in the हाल of VFR/VFLR. If this is करोne क्रम
	 * PFR, it can mess up VF resets because the VF driver may alपढ़ोy
	 * have started cleanup by the समय we get here.
	 */
	अगर (!is_pfr) अणु
		wr32(hw, VF_MBX_ARQLEN(vf->vf_id), 0);
		wr32(hw, VF_MBX_ATQLEN(vf->vf_id), 0);
	पूर्ण

	/* In the हाल of a VFLR, the HW has alपढ़ोy reset the VF and we
	 * just need to clean up, so करोn't hit the VFRTRIG रेजिस्टर.
	 */
	अगर (!is_vflr) अणु
		/* reset VF using VPGEN_VFRTRIG reg */
		reg = rd32(hw, VPGEN_VFRTRIG(vf->vf_id));
		reg |= VPGEN_VFRTRIG_VFSWR_M;
		wr32(hw, VPGEN_VFRTRIG(vf->vf_id), reg);
	पूर्ण
	/* clear the VFLR bit in GLGEN_VFLRSTAT */
	reg_idx = (vf_असल_id) / 32;
	bit_idx = (vf_असल_id) % 32;
	wr32(hw, GLGEN_VFLRSTAT(reg_idx), BIT(bit_idx));
	ice_flush(hw);

	wr32(hw, PF_PCI_CIAA,
	     VF_DEVICE_STATUS | (vf_असल_id << PF_PCI_CIAA_VF_NUM_S));
	क्रम (i = 0; i < ICE_PCI_CIAD_WAIT_COUNT; i++) अणु
		reg = rd32(hw, PF_PCI_CIAD);
		/* no transactions pending so stop polling */
		अगर ((reg & VF_TRANS_PENDING_M) == 0)
			अवरोध;

		dev_err(dev, "VF %u PCI transactions stuck\n", vf->vf_id);
		udelay(ICE_PCI_CIAD_WAIT_DELAY_US);
	पूर्ण
पूर्ण

/**
 * ice_vsi_manage_pvid - Enable or disable port VLAN क्रम VSI
 * @vsi: the VSI to update
 * @pvid_info: VLAN ID and QoS used to set the PVID VSI context field
 * @enable: true क्रम enable PVID false क्रम disable
 */
अटल पूर्णांक ice_vsi_manage_pvid(काष्ठा ice_vsi *vsi, u16 pvid_info, bool enable)
अणु
	काष्ठा ice_hw *hw = &vsi->back->hw;
	काष्ठा ice_aqc_vsi_props *info;
	काष्ठा ice_vsi_ctx *ctxt;
	क्रमागत ice_status status;
	पूर्णांक ret = 0;

	ctxt = kzalloc(माप(*ctxt), GFP_KERNEL);
	अगर (!ctxt)
		वापस -ENOMEM;

	ctxt->info = vsi->info;
	info = &ctxt->info;
	अगर (enable) अणु
		info->vlan_flags = ICE_AQ_VSI_VLAN_MODE_UNTAGGED |
			ICE_AQ_VSI_PVLAN_INSERT_PVID |
			ICE_AQ_VSI_VLAN_EMOD_STR;
		info->sw_flags2 |= ICE_AQ_VSI_SW_FLAG_RX_VLAN_PRUNE_ENA;
	पूर्ण अन्यथा अणु
		info->vlan_flags = ICE_AQ_VSI_VLAN_EMOD_NOTHING |
			ICE_AQ_VSI_VLAN_MODE_ALL;
		info->sw_flags2 &= ~ICE_AQ_VSI_SW_FLAG_RX_VLAN_PRUNE_ENA;
	पूर्ण

	info->pvid = cpu_to_le16(pvid_info);
	info->valid_sections = cpu_to_le16(ICE_AQ_VSI_PROP_VLAN_VALID |
					   ICE_AQ_VSI_PROP_SW_VALID);

	status = ice_update_vsi(hw, vsi->idx, ctxt, शून्य);
	अगर (status) अणु
		dev_info(ice_hw_to_dev(hw), "update VSI for port VLAN failed, err %s aq_err %s\n",
			 ice_stat_str(status),
			 ice_aq_str(hw->adminq.sq_last_status));
		ret = -EIO;
		जाओ out;
	पूर्ण

	vsi->info.vlan_flags = info->vlan_flags;
	vsi->info.sw_flags2 = info->sw_flags2;
	vsi->info.pvid = info->pvid;
out:
	kमुक्त(ctxt);
	वापस ret;
पूर्ण

/**
 * ice_vf_get_port_info - Get the VF's port info काष्ठाure
 * @vf: VF used to get the port info काष्ठाure क्रम
 */
अटल काष्ठा ice_port_info *ice_vf_get_port_info(काष्ठा ice_vf *vf)
अणु
	वापस vf->pf->hw.port_info;
पूर्ण

/**
 * ice_vf_vsi_setup - Set up a VF VSI
 * @vf: VF to setup VSI क्रम
 *
 * Returns poपूर्णांकer to the successfully allocated VSI काष्ठा on success,
 * otherwise वापसs शून्य on failure.
 */
अटल काष्ठा ice_vsi *ice_vf_vsi_setup(काष्ठा ice_vf *vf)
अणु
	काष्ठा ice_port_info *pi = ice_vf_get_port_info(vf);
	काष्ठा ice_pf *pf = vf->pf;
	काष्ठा ice_vsi *vsi;

	vsi = ice_vsi_setup(pf, pi, ICE_VSI_VF, vf->vf_id);

	अगर (!vsi) अणु
		dev_err(ice_pf_to_dev(pf), "Failed to create VF VSI\n");
		ice_vf_invalidate_vsi(vf);
		वापस शून्य;
	पूर्ण

	vf->lan_vsi_idx = vsi->idx;
	vf->lan_vsi_num = vsi->vsi_num;

	वापस vsi;
पूर्ण

/**
 * ice_vf_ctrl_vsi_setup - Set up a VF control VSI
 * @vf: VF to setup control VSI क्रम
 *
 * Returns poपूर्णांकer to the successfully allocated VSI काष्ठा on success,
 * otherwise वापसs शून्य on failure.
 */
काष्ठा ice_vsi *ice_vf_ctrl_vsi_setup(काष्ठा ice_vf *vf)
अणु
	काष्ठा ice_port_info *pi = ice_vf_get_port_info(vf);
	काष्ठा ice_pf *pf = vf->pf;
	काष्ठा ice_vsi *vsi;

	vsi = ice_vsi_setup(pf, pi, ICE_VSI_CTRL, vf->vf_id);
	अगर (!vsi) अणु
		dev_err(ice_pf_to_dev(pf), "Failed to create VF control VSI\n");
		ice_vf_ctrl_invalidate_vsi(vf);
	पूर्ण

	वापस vsi;
पूर्ण

/**
 * ice_calc_vf_first_vector_idx - Calculate MSIX vector index in the PF space
 * @pf: poपूर्णांकer to PF काष्ठाure
 * @vf: poपूर्णांकer to VF that the first MSIX vector index is being calculated क्रम
 *
 * This वापसs the first MSIX vector index in PF space that is used by this VF.
 * This index is used when accessing PF relative रेजिस्टरs such as
 * GLINT_VECT2FUNC and GLINT_DYN_CTL.
 * This will always be the OICR index in the AVF driver so any functionality
 * using vf->first_vector_idx क्रम queue configuration will have to increment by
 * 1 to aव्योम meddling with the OICR index.
 */
अटल पूर्णांक ice_calc_vf_first_vector_idx(काष्ठा ice_pf *pf, काष्ठा ice_vf *vf)
अणु
	वापस pf->sriov_base_vector + vf->vf_id * pf->num_msix_per_vf;
पूर्ण

/**
 * ice_vf_rebuild_host_vlan_cfg - add VLAN 0 filter or rebuild the Port VLAN
 * @vf: VF to add MAC filters क्रम
 *
 * Called after a VF VSI has been re-added/rebuilt during reset. The PF driver
 * always re-adds either a VLAN 0 or port VLAN based filter after reset.
 */
अटल पूर्णांक ice_vf_rebuild_host_vlan_cfg(काष्ठा ice_vf *vf)
अणु
	काष्ठा device *dev = ice_pf_to_dev(vf->pf);
	काष्ठा ice_vsi *vsi = ice_get_vf_vsi(vf);
	u16 vlan_id = 0;
	पूर्णांक err;

	अगर (vf->port_vlan_info) अणु
		err = ice_vsi_manage_pvid(vsi, vf->port_vlan_info, true);
		अगर (err) अणु
			dev_err(dev, "failed to configure port VLAN via VSI parameters for VF %u, error %d\n",
				vf->vf_id, err);
			वापस err;
		पूर्ण

		vlan_id = vf->port_vlan_info & VLAN_VID_MASK;
	पूर्ण

	/* vlan_id will either be 0 or the port VLAN number */
	err = ice_vsi_add_vlan(vsi, vlan_id, ICE_FWD_TO_VSI);
	अगर (err) अणु
		dev_err(dev, "failed to add %s VLAN %u filter for VF %u, error %d\n",
			vf->port_vlan_info ? "port" : "", vlan_id, vf->vf_id,
			err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ice_vf_rebuild_host_mac_cfg - add broadcast and the VF's perm_addr/LAA
 * @vf: VF to add MAC filters क्रम
 *
 * Called after a VF VSI has been re-added/rebuilt during reset. The PF driver
 * always re-adds a broadcast filter and the VF's perm_addr/LAA after reset.
 */
अटल पूर्णांक ice_vf_rebuild_host_mac_cfg(काष्ठा ice_vf *vf)
अणु
	काष्ठा device *dev = ice_pf_to_dev(vf->pf);
	काष्ठा ice_vsi *vsi = ice_get_vf_vsi(vf);
	क्रमागत ice_status status;
	u8 broadcast[ETH_ALEN];

	eth_broadcast_addr(broadcast);
	status = ice_fltr_add_mac(vsi, broadcast, ICE_FWD_TO_VSI);
	अगर (status) अणु
		dev_err(dev, "failed to add broadcast MAC filter for VF %u, error %s\n",
			vf->vf_id, ice_stat_str(status));
		वापस ice_status_to_त्रुटि_सं(status);
	पूर्ण

	vf->num_mac++;

	अगर (is_valid_ether_addr(vf->dflt_lan_addr.addr)) अणु
		status = ice_fltr_add_mac(vsi, vf->dflt_lan_addr.addr,
					  ICE_FWD_TO_VSI);
		अगर (status) अणु
			dev_err(dev, "failed to add default unicast MAC filter %pM for VF %u, error %s\n",
				&vf->dflt_lan_addr.addr[0], vf->vf_id,
				ice_stat_str(status));
			वापस ice_status_to_त्रुटि_सं(status);
		पूर्ण
		vf->num_mac++;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ice_vf_set_host_trust_cfg - set trust setting based on pre-reset value
 * @vf: VF to configure trust setting क्रम
 */
अटल व्योम ice_vf_set_host_trust_cfg(काष्ठा ice_vf *vf)
अणु
	अगर (vf->trusted)
		set_bit(ICE_VIRTCHNL_VF_CAP_PRIVILEGE, &vf->vf_caps);
	अन्यथा
		clear_bit(ICE_VIRTCHNL_VF_CAP_PRIVILEGE, &vf->vf_caps);
पूर्ण

/**
 * ice_ena_vf_msix_mappings - enable VF MSIX mappings in hardware
 * @vf: VF to enable MSIX mappings क्रम
 *
 * Some of the रेजिस्टरs need to be indexed/configured using hardware global
 * device values and other रेजिस्टरs need 0-based values, which represent PF
 * based values.
 */
अटल व्योम ice_ena_vf_msix_mappings(काष्ठा ice_vf *vf)
अणु
	पूर्णांक device_based_first_msix, device_based_last_msix;
	पूर्णांक pf_based_first_msix, pf_based_last_msix, v;
	काष्ठा ice_pf *pf = vf->pf;
	पूर्णांक device_based_vf_id;
	काष्ठा ice_hw *hw;
	u32 reg;

	hw = &pf->hw;
	pf_based_first_msix = vf->first_vector_idx;
	pf_based_last_msix = (pf_based_first_msix + pf->num_msix_per_vf) - 1;

	device_based_first_msix = pf_based_first_msix +
		pf->hw.func_caps.common_cap.msix_vector_first_id;
	device_based_last_msix =
		(device_based_first_msix + pf->num_msix_per_vf) - 1;
	device_based_vf_id = vf->vf_id + hw->func_caps.vf_base_id;

	reg = (((device_based_first_msix << VPINT_ALLOC_FIRST_S) &
		VPINT_ALLOC_FIRST_M) |
	       ((device_based_last_msix << VPINT_ALLOC_LAST_S) &
		VPINT_ALLOC_LAST_M) | VPINT_ALLOC_VALID_M);
	wr32(hw, VPINT_ALLOC(vf->vf_id), reg);

	reg = (((device_based_first_msix << VPINT_ALLOC_PCI_FIRST_S)
		 & VPINT_ALLOC_PCI_FIRST_M) |
	       ((device_based_last_msix << VPINT_ALLOC_PCI_LAST_S) &
		VPINT_ALLOC_PCI_LAST_M) | VPINT_ALLOC_PCI_VALID_M);
	wr32(hw, VPINT_ALLOC_PCI(vf->vf_id), reg);

	/* map the पूर्णांकerrupts to its functions */
	क्रम (v = pf_based_first_msix; v <= pf_based_last_msix; v++) अणु
		reg = (((device_based_vf_id << GLINT_VECT2FUNC_VF_NUM_S) &
			GLINT_VECT2FUNC_VF_NUM_M) |
		       ((hw->pf_id << GLINT_VECT2FUNC_PF_NUM_S) &
			GLINT_VECT2FUNC_PF_NUM_M));
		wr32(hw, GLINT_VECT2FUNC(v), reg);
	पूर्ण

	/* Map mailbox पूर्णांकerrupt to VF MSI-X vector 0 */
	wr32(hw, VPINT_MBX_CTL(device_based_vf_id), VPINT_MBX_CTL_CAUSE_ENA_M);
पूर्ण

/**
 * ice_ena_vf_q_mappings - enable Rx/Tx queue mappings क्रम a VF
 * @vf: VF to enable the mappings क्रम
 * @max_txq: max Tx queues allowed on the VF's VSI
 * @max_rxq: max Rx queues allowed on the VF's VSI
 */
अटल व्योम ice_ena_vf_q_mappings(काष्ठा ice_vf *vf, u16 max_txq, u16 max_rxq)
अणु
	काष्ठा device *dev = ice_pf_to_dev(vf->pf);
	काष्ठा ice_vsi *vsi = ice_get_vf_vsi(vf);
	काष्ठा ice_hw *hw = &vf->pf->hw;
	u32 reg;

	/* set regardless of mapping mode */
	wr32(hw, VPLAN_TXQ_MAPENA(vf->vf_id), VPLAN_TXQ_MAPENA_TX_ENA_M);

	/* VF Tx queues allocation */
	अगर (vsi->tx_mapping_mode == ICE_VSI_MAP_CONTIG) अणु
		/* set the VF PF Tx queue range
		 * VFNUMQ value should be set to (number of queues - 1). A value
		 * of 0 means 1 queue and a value of 255 means 256 queues
		 */
		reg = (((vsi->txq_map[0] << VPLAN_TX_QBASE_VFFIRSTQ_S) &
			VPLAN_TX_QBASE_VFFIRSTQ_M) |
		       (((max_txq - 1) << VPLAN_TX_QBASE_VFNUMQ_S) &
			VPLAN_TX_QBASE_VFNUMQ_M));
		wr32(hw, VPLAN_TX_QBASE(vf->vf_id), reg);
	पूर्ण अन्यथा अणु
		dev_err(dev, "Scattered mode for VF Tx queues is not yet implemented\n");
	पूर्ण

	/* set regardless of mapping mode */
	wr32(hw, VPLAN_RXQ_MAPENA(vf->vf_id), VPLAN_RXQ_MAPENA_RX_ENA_M);

	/* VF Rx queues allocation */
	अगर (vsi->rx_mapping_mode == ICE_VSI_MAP_CONTIG) अणु
		/* set the VF PF Rx queue range
		 * VFNUMQ value should be set to (number of queues - 1). A value
		 * of 0 means 1 queue and a value of 255 means 256 queues
		 */
		reg = (((vsi->rxq_map[0] << VPLAN_RX_QBASE_VFFIRSTQ_S) &
			VPLAN_RX_QBASE_VFFIRSTQ_M) |
		       (((max_rxq - 1) << VPLAN_RX_QBASE_VFNUMQ_S) &
			VPLAN_RX_QBASE_VFNUMQ_M));
		wr32(hw, VPLAN_RX_QBASE(vf->vf_id), reg);
	पूर्ण अन्यथा अणु
		dev_err(dev, "Scattered mode for VF Rx queues is not yet implemented\n");
	पूर्ण
पूर्ण

/**
 * ice_ena_vf_mappings - enable VF MSIX and queue mapping
 * @vf: poपूर्णांकer to the VF काष्ठाure
 */
अटल व्योम ice_ena_vf_mappings(काष्ठा ice_vf *vf)
अणु
	काष्ठा ice_vsi *vsi = ice_get_vf_vsi(vf);

	ice_ena_vf_msix_mappings(vf);
	ice_ena_vf_q_mappings(vf, vsi->alloc_txq, vsi->alloc_rxq);
पूर्ण

/**
 * ice_determine_res
 * @pf: poपूर्णांकer to the PF काष्ठाure
 * @avail_res: available resources in the PF काष्ठाure
 * @max_res: maximum resources that can be given per VF
 * @min_res: minimum resources that can be given per VF
 *
 * Returns non-zero value अगर resources (queues/vectors) are available or
 * वापसs zero अगर PF cannot accommodate क्रम all num_alloc_vfs.
 */
अटल पूर्णांक
ice_determine_res(काष्ठा ice_pf *pf, u16 avail_res, u16 max_res, u16 min_res)
अणु
	bool checked_min_res = false;
	पूर्णांक res;

	/* start by checking अगर PF can assign max number of resources क्रम
	 * all num_alloc_vfs.
	 * अगर yes, वापस number per VF
	 * If no, भागide by 2 and roundup, check again
	 * repeat the loop till we reach a poपूर्णांक where even minimum resources
	 * are not available, in that हाल वापस 0
	 */
	res = max_res;
	जबतक ((res >= min_res) && !checked_min_res) अणु
		पूर्णांक num_all_res;

		num_all_res = pf->num_alloc_vfs * res;
		अगर (num_all_res <= avail_res)
			वापस res;

		अगर (res == min_res)
			checked_min_res = true;

		res = DIV_ROUND_UP(res, 2);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * ice_calc_vf_reg_idx - Calculate the VF's रेजिस्टर index in the PF space
 * @vf: VF to calculate the रेजिस्टर index क्रम
 * @q_vector: a q_vector associated to the VF
 */
पूर्णांक ice_calc_vf_reg_idx(काष्ठा ice_vf *vf, काष्ठा ice_q_vector *q_vector)
अणु
	काष्ठा ice_pf *pf;

	अगर (!vf || !q_vector)
		वापस -EINVAL;

	pf = vf->pf;

	/* always add one to account क्रम the OICR being the first MSIX */
	वापस pf->sriov_base_vector + pf->num_msix_per_vf * vf->vf_id +
		q_vector->v_idx + 1;
पूर्ण

/**
 * ice_get_max_valid_res_idx - Get the max valid resource index
 * @res: poपूर्णांकer to the resource to find the max valid index क्रम
 *
 * Start from the end of the ice_res_tracker and वापस right when we find the
 * first res->list entry with the ICE_RES_VALID_BIT set. This function is only
 * valid क्रम SR-IOV because it is the only consumer that manipulates the
 * res->end and this is always called when res->end is set to res->num_entries.
 */
अटल पूर्णांक ice_get_max_valid_res_idx(काष्ठा ice_res_tracker *res)
अणु
	पूर्णांक i;

	अगर (!res)
		वापस -EINVAL;

	क्रम (i = res->num_entries - 1; i >= 0; i--)
		अगर (res->list[i] & ICE_RES_VALID_BIT)
			वापस i;

	वापस 0;
पूर्ण

/**
 * ice_sriov_set_msix_res - Set any used MSIX resources
 * @pf: poपूर्णांकer to PF काष्ठाure
 * @num_msix_needed: number of MSIX vectors needed क्रम all SR-IOV VFs
 *
 * This function allows SR-IOV resources to be taken from the end of the PF's
 * allowed HW MSIX vectors so that the irq_tracker will not be affected. We
 * just set the pf->sriov_base_vector and वापस success.
 *
 * If there are not enough resources available, वापस an error. This should
 * always be caught by ice_set_per_vf_res().
 *
 * Return 0 on success, and -EINVAL when there are not enough MSIX vectors
 * in the PF's space available क्रम SR-IOV.
 */
अटल पूर्णांक ice_sriov_set_msix_res(काष्ठा ice_pf *pf, u16 num_msix_needed)
अणु
	u16 total_vectors = pf->hw.func_caps.common_cap.num_msix_vectors;
	पूर्णांक vectors_used = pf->irq_tracker->num_entries;
	पूर्णांक sriov_base_vector;

	sriov_base_vector = total_vectors - num_msix_needed;

	/* make sure we only grab irq_tracker entries from the list end and
	 * that we have enough available MSIX vectors
	 */
	अगर (sriov_base_vector < vectors_used)
		वापस -EINVAL;

	pf->sriov_base_vector = sriov_base_vector;

	वापस 0;
पूर्ण

/**
 * ice_set_per_vf_res - check अगर vectors and queues are available
 * @pf: poपूर्णांकer to the PF काष्ठाure
 *
 * First, determine HW पूर्णांकerrupts from common pool. If we allocate fewer VFs, we
 * get more vectors and can enable more queues per VF. Note that this करोes not
 * grab any vectors from the SW pool alपढ़ोy allocated. Also note, that all
 * vector counts include one क्रम each VF's miscellaneous पूर्णांकerrupt vector
 * (i.e. OICR).
 *
 * Minimum VFs - 2 vectors, 1 queue pair
 * Small VFs - 5 vectors, 4 queue pairs
 * Medium VFs - 17 vectors, 16 queue pairs
 *
 * Second, determine number of queue pairs per VF by starting with a pre-defined
 * maximum each VF supports. If this is not possible, then we adjust based on
 * queue pairs available on the device.
 *
 * Lastly, set queue and MSI-X VF variables tracked by the PF so it can be used
 * by each VF during VF initialization and reset.
 */
अटल पूर्णांक ice_set_per_vf_res(काष्ठा ice_pf *pf)
अणु
	पूर्णांक max_valid_res_idx = ice_get_max_valid_res_idx(pf->irq_tracker);
	पूर्णांक msix_avail_per_vf, msix_avail_क्रम_sriov;
	काष्ठा device *dev = ice_pf_to_dev(pf);
	u16 num_msix_per_vf, num_txq, num_rxq;

	अगर (!pf->num_alloc_vfs || max_valid_res_idx < 0)
		वापस -EINVAL;

	/* determine MSI-X resources per VF */
	msix_avail_क्रम_sriov = pf->hw.func_caps.common_cap.num_msix_vectors -
		pf->irq_tracker->num_entries;
	msix_avail_per_vf = msix_avail_क्रम_sriov / pf->num_alloc_vfs;
	अगर (msix_avail_per_vf >= ICE_NUM_VF_MSIX_MED) अणु
		num_msix_per_vf = ICE_NUM_VF_MSIX_MED;
	पूर्ण अन्यथा अगर (msix_avail_per_vf >= ICE_NUM_VF_MSIX_SMALL) अणु
		num_msix_per_vf = ICE_NUM_VF_MSIX_SMALL;
	पूर्ण अन्यथा अगर (msix_avail_per_vf >= ICE_NUM_VF_MSIX_MULTIQ_MIN) अणु
		num_msix_per_vf = ICE_NUM_VF_MSIX_MULTIQ_MIN;
	पूर्ण अन्यथा अगर (msix_avail_per_vf >= ICE_MIN_INTR_PER_VF) अणु
		num_msix_per_vf = ICE_MIN_INTR_PER_VF;
	पूर्ण अन्यथा अणु
		dev_err(dev, "Only %d MSI-X interrupts available for SR-IOV. Not enough to support minimum of %d MSI-X interrupts per VF for %d VFs\n",
			msix_avail_क्रम_sriov, ICE_MIN_INTR_PER_VF,
			pf->num_alloc_vfs);
		वापस -EIO;
	पूर्ण

	/* determine queue resources per VF */
	num_txq = ice_determine_res(pf, ice_get_avail_txq_count(pf),
				    min_t(u16,
					  num_msix_per_vf - ICE_NONQ_VECS_VF,
					  ICE_MAX_RSS_QS_PER_VF),
				    ICE_MIN_QS_PER_VF);

	num_rxq = ice_determine_res(pf, ice_get_avail_rxq_count(pf),
				    min_t(u16,
					  num_msix_per_vf - ICE_NONQ_VECS_VF,
					  ICE_MAX_RSS_QS_PER_VF),
				    ICE_MIN_QS_PER_VF);

	अगर (!num_txq || !num_rxq) अणु
		dev_err(dev, "Not enough queues to support minimum of %d queue pairs per VF for %d VFs\n",
			ICE_MIN_QS_PER_VF, pf->num_alloc_vfs);
		वापस -EIO;
	पूर्ण

	अगर (ice_sriov_set_msix_res(pf, num_msix_per_vf * pf->num_alloc_vfs)) अणु
		dev_err(dev, "Unable to set MSI-X resources for %d VFs\n",
			pf->num_alloc_vfs);
		वापस -EINVAL;
	पूर्ण

	/* only allow equal Tx/Rx queue count (i.e. queue pairs) */
	pf->num_qps_per_vf = min_t(पूर्णांक, num_txq, num_rxq);
	pf->num_msix_per_vf = num_msix_per_vf;
	dev_info(dev, "Enabling %d VFs with %d vectors and %d queues per VF\n",
		 pf->num_alloc_vfs, pf->num_msix_per_vf, pf->num_qps_per_vf);

	वापस 0;
पूर्ण

/**
 * ice_clear_vf_reset_trigger - enable VF to access hardware
 * @vf: VF to enabled hardware access क्रम
 */
अटल व्योम ice_clear_vf_reset_trigger(काष्ठा ice_vf *vf)
अणु
	काष्ठा ice_hw *hw = &vf->pf->hw;
	u32 reg;

	reg = rd32(hw, VPGEN_VFRTRIG(vf->vf_id));
	reg &= ~VPGEN_VFRTRIG_VFSWR_M;
	wr32(hw, VPGEN_VFRTRIG(vf->vf_id), reg);
	ice_flush(hw);
पूर्ण

/**
 * ice_vf_set_vsi_promisc - set given VF VSI to given promiscuous mode(s)
 * @vf: poपूर्णांकer to the VF info
 * @vsi: the VSI being configured
 * @promisc_m: mask of promiscuous config bits
 * @rm_promisc: promisc flag request from the VF to हटाओ or add filter
 *
 * This function configures VF VSI promiscuous mode, based on the VF requests,
 * क्रम Unicast, Multicast and VLAN
 */
अटल क्रमागत ice_status
ice_vf_set_vsi_promisc(काष्ठा ice_vf *vf, काष्ठा ice_vsi *vsi, u8 promisc_m,
		       bool rm_promisc)
अणु
	काष्ठा ice_pf *pf = vf->pf;
	क्रमागत ice_status status = 0;
	काष्ठा ice_hw *hw;

	hw = &pf->hw;
	अगर (vsi->num_vlan) अणु
		status = ice_set_vlan_vsi_promisc(hw, vsi->idx, promisc_m,
						  rm_promisc);
	पूर्ण अन्यथा अगर (vf->port_vlan_info) अणु
		अगर (rm_promisc)
			status = ice_clear_vsi_promisc(hw, vsi->idx, promisc_m,
						       vf->port_vlan_info);
		अन्यथा
			status = ice_set_vsi_promisc(hw, vsi->idx, promisc_m,
						     vf->port_vlan_info);
	पूर्ण अन्यथा अणु
		अगर (rm_promisc)
			status = ice_clear_vsi_promisc(hw, vsi->idx, promisc_m,
						       0);
		अन्यथा
			status = ice_set_vsi_promisc(hw, vsi->idx, promisc_m,
						     0);
	पूर्ण

	वापस status;
पूर्ण

अटल व्योम ice_vf_clear_counters(काष्ठा ice_vf *vf)
अणु
	काष्ठा ice_vsi *vsi = ice_get_vf_vsi(vf);

	vf->num_mac = 0;
	vsi->num_vlan = 0;
	स_रखो(&vf->mdd_tx_events, 0, माप(vf->mdd_tx_events));
	स_रखो(&vf->mdd_rx_events, 0, माप(vf->mdd_rx_events));
पूर्ण

/**
 * ice_vf_pre_vsi_rebuild - tasks to be करोne prior to VSI rebuild
 * @vf: VF to perक्रमm pre VSI rebuild tasks
 *
 * These tasks are items that करोn't need to be amortized since they are most
 * likely called in a क्रम loop with all VF(s) in the reset_all_vfs() हाल.
 */
अटल व्योम ice_vf_pre_vsi_rebuild(काष्ठा ice_vf *vf)
अणु
	ice_vf_clear_counters(vf);
	ice_clear_vf_reset_trigger(vf);
पूर्ण

/**
 * ice_vf_rebuild_aggregator_node_cfg - rebuild aggregator node config
 * @vsi: Poपूर्णांकer to VSI
 *
 * This function moves VSI पूर्णांकo corresponding scheduler aggregator node
 * based on cached value of "aggregator node info" per VSI
 */
अटल व्योम ice_vf_rebuild_aggregator_node_cfg(काष्ठा ice_vsi *vsi)
अणु
	काष्ठा ice_pf *pf = vsi->back;
	क्रमागत ice_status status;
	काष्ठा device *dev;

	अगर (!vsi->agg_node)
		वापस;

	dev = ice_pf_to_dev(pf);
	अगर (vsi->agg_node->num_vsis == ICE_MAX_VSIS_IN_AGG_NODE) अणु
		dev_dbg(dev,
			"agg_id %u already has reached max_num_vsis %u\n",
			vsi->agg_node->agg_id, vsi->agg_node->num_vsis);
		वापस;
	पूर्ण

	status = ice_move_vsi_to_agg(pf->hw.port_info, vsi->agg_node->agg_id,
				     vsi->idx, vsi->tc_cfg.ena_tc);
	अगर (status)
		dev_dbg(dev, "unable to move VSI idx %u into aggregator %u node",
			vsi->idx, vsi->agg_node->agg_id);
	अन्यथा
		vsi->agg_node->num_vsis++;
पूर्ण

/**
 * ice_vf_rebuild_host_cfg - host admin configuration is persistent across reset
 * @vf: VF to rebuild host configuration on
 */
अटल व्योम ice_vf_rebuild_host_cfg(काष्ठा ice_vf *vf)
अणु
	काष्ठा device *dev = ice_pf_to_dev(vf->pf);
	काष्ठा ice_vsi *vsi = ice_get_vf_vsi(vf);

	ice_vf_set_host_trust_cfg(vf);

	अगर (ice_vf_rebuild_host_mac_cfg(vf))
		dev_err(dev, "failed to rebuild default MAC configuration for VF %d\n",
			vf->vf_id);

	अगर (ice_vf_rebuild_host_vlan_cfg(vf))
		dev_err(dev, "failed to rebuild VLAN configuration for VF %u\n",
			vf->vf_id);
	/* rebuild aggregator node config क्रम मुख्य VF VSI */
	ice_vf_rebuild_aggregator_node_cfg(vsi);
पूर्ण

/**
 * ice_vf_rebuild_vsi_with_release - release and setup the VF's VSI
 * @vf: VF to release and setup the VSI क्रम
 *
 * This is only called when a single VF is being reset (i.e. VFR, VFLR, host VF
 * configuration change, etc.).
 */
अटल पूर्णांक ice_vf_rebuild_vsi_with_release(काष्ठा ice_vf *vf)
अणु
	ice_vf_vsi_release(vf);
	अगर (!ice_vf_vsi_setup(vf))
		वापस -ENOMEM;

	वापस 0;
पूर्ण

/**
 * ice_vf_rebuild_vsi - rebuild the VF's VSI
 * @vf: VF to rebuild the VSI क्रम
 *
 * This is only called when all VF(s) are being reset (i.e. PCIe Reset on the
 * host, PFR, CORER, etc.).
 */
अटल पूर्णांक ice_vf_rebuild_vsi(काष्ठा ice_vf *vf)
अणु
	काष्ठा ice_vsi *vsi = ice_get_vf_vsi(vf);
	काष्ठा ice_pf *pf = vf->pf;

	अगर (ice_vsi_rebuild(vsi, true)) अणु
		dev_err(ice_pf_to_dev(pf), "failed to rebuild VF %d VSI\n",
			vf->vf_id);
		वापस -EIO;
	पूर्ण
	/* vsi->idx will reमुख्य the same in this हाल so करोn't update
	 * vf->lan_vsi_idx
	 */
	vsi->vsi_num = ice_get_hw_vsi_num(&pf->hw, vsi->idx);
	vf->lan_vsi_num = vsi->vsi_num;

	वापस 0;
पूर्ण

/**
 * ice_vf_set_initialized - VF is पढ़ोy क्रम VIRTCHNL communication
 * @vf: VF to set in initialized state
 *
 * After this function the VF will be पढ़ोy to receive/handle the
 * VIRTCHNL_OP_GET_VF_RESOURCES message
 */
अटल व्योम ice_vf_set_initialized(काष्ठा ice_vf *vf)
अणु
	ice_set_vf_state_qs_dis(vf);
	clear_bit(ICE_VF_STATE_MC_PROMISC, vf->vf_states);
	clear_bit(ICE_VF_STATE_UC_PROMISC, vf->vf_states);
	clear_bit(ICE_VF_STATE_DIS, vf->vf_states);
	set_bit(ICE_VF_STATE_INIT, vf->vf_states);
पूर्ण

/**
 * ice_vf_post_vsi_rebuild - tasks to करो after the VF's VSI have been rebuilt
 * @vf: VF to perक्रमm tasks on
 */
अटल व्योम ice_vf_post_vsi_rebuild(काष्ठा ice_vf *vf)
अणु
	काष्ठा ice_pf *pf = vf->pf;
	काष्ठा ice_hw *hw;

	hw = &pf->hw;

	ice_vf_rebuild_host_cfg(vf);

	ice_vf_set_initialized(vf);
	ice_ena_vf_mappings(vf);
	wr32(hw, VFGEN_RSTAT(vf->vf_id), VIRTCHNL_VFR_VFACTIVE);
पूर्ण

/**
 * ice_reset_all_vfs - reset all allocated VFs in one go
 * @pf: poपूर्णांकer to the PF काष्ठाure
 * @is_vflr: true अगर VFLR was issued, false अगर not
 *
 * First, tell the hardware to reset each VF, then करो all the रुकोing in one
 * chunk, and finally finish restoring each VF after the रुको. This is useful
 * during PF routines which need to reset all VFs, as otherwise it must perक्रमm
 * these resets in a serialized fashion.
 *
 * Returns true अगर any VFs were reset, and false otherwise.
 */
bool ice_reset_all_vfs(काष्ठा ice_pf *pf, bool is_vflr)
अणु
	काष्ठा device *dev = ice_pf_to_dev(pf);
	काष्ठा ice_hw *hw = &pf->hw;
	काष्ठा ice_vf *vf;
	पूर्णांक v, i;

	/* If we करोn't have any VFs, then there is nothing to reset */
	अगर (!pf->num_alloc_vfs)
		वापस false;

	/* clear all malicious info अगर the VFs are getting reset */
	ice_क्रम_each_vf(pf, i)
		अगर (ice_mbx_clear_malvf(&hw->mbx_snapshot, pf->malvfs, ICE_MAX_VF_COUNT, i))
			dev_dbg(dev, "failed to clear malicious VF state for VF %u\n", i);

	/* If VFs have been disabled, there is no need to reset */
	अगर (test_and_set_bit(ICE_VF_DIS, pf->state))
		वापस false;

	/* Begin reset on all VFs at once */
	ice_क्रम_each_vf(pf, v)
		ice_trigger_vf_reset(&pf->vf[v], is_vflr, true);

	/* HW requires some समय to make sure it can flush the FIFO क्रम a VF
	 * when it resets it. Poll the VPGEN_VFRSTAT रेजिस्टर क्रम each VF in
	 * sequence to make sure that it has completed. We'll keep track of
	 * the VFs using a simple iterator that increments once that VF has
	 * finished resetting.
	 */
	क्रम (i = 0, v = 0; i < 10 && v < pf->num_alloc_vfs; i++) अणु
		/* Check each VF in sequence */
		जबतक (v < pf->num_alloc_vfs) अणु
			u32 reg;

			vf = &pf->vf[v];
			reg = rd32(hw, VPGEN_VFRSTAT(vf->vf_id));
			अगर (!(reg & VPGEN_VFRSTAT_VFRD_M)) अणु
				/* only delay अगर the check failed */
				usleep_range(10, 20);
				अवरोध;
			पूर्ण

			/* If the current VF has finished resetting, move on
			 * to the next VF in sequence.
			 */
			v++;
		पूर्ण
	पूर्ण

	/* Display a warning अगर at least one VF didn't manage to reset in
	 * समय, but जारी on with the operation.
	 */
	अगर (v < pf->num_alloc_vfs)
		dev_warn(dev, "VF reset check timeout\n");

	/* मुक्त VF resources to begin resetting the VSI state */
	ice_क्रम_each_vf(pf, v) अणु
		vf = &pf->vf[v];

		vf->driver_caps = 0;
		ice_vc_set_शेष_allowlist(vf);

		ice_vf_fdir_निकास(vf);
		/* clean VF control VSI when resetting VFs since it should be
		 * setup only when VF creates its first Fसूची rule.
		 */
		अगर (vf->ctrl_vsi_idx != ICE_NO_VSI)
			ice_vf_ctrl_invalidate_vsi(vf);

		ice_vf_pre_vsi_rebuild(vf);
		ice_vf_rebuild_vsi(vf);
		ice_vf_post_vsi_rebuild(vf);
	पूर्ण

	ice_flush(hw);
	clear_bit(ICE_VF_DIS, pf->state);

	वापस true;
पूर्ण

/**
 * ice_is_vf_disabled
 * @vf: poपूर्णांकer to the VF info
 *
 * Returns true अगर the PF or VF is disabled, false otherwise.
 */
अटल bool ice_is_vf_disabled(काष्ठा ice_vf *vf)
अणु
	काष्ठा ice_pf *pf = vf->pf;

	/* If the PF has been disabled, there is no need resetting VF until
	 * PF is active again. Similarly, अगर the VF has been disabled, this
	 * means something अन्यथा is resetting the VF, so we shouldn't जारी.
	 * Otherwise, set disable VF state bit क्रम actual reset, and जारी.
	 */
	वापस (test_bit(ICE_VF_DIS, pf->state) ||
		test_bit(ICE_VF_STATE_DIS, vf->vf_states));
पूर्ण

/**
 * ice_reset_vf - Reset a particular VF
 * @vf: poपूर्णांकer to the VF काष्ठाure
 * @is_vflr: true अगर VFLR was issued, false अगर not
 *
 * Returns true अगर the VF is currently in reset, resets successfully, or resets
 * are disabled and false otherwise.
 */
bool ice_reset_vf(काष्ठा ice_vf *vf, bool is_vflr)
अणु
	काष्ठा ice_pf *pf = vf->pf;
	काष्ठा ice_vsi *vsi;
	काष्ठा device *dev;
	काष्ठा ice_hw *hw;
	bool rsd = false;
	u8 promisc_m;
	u32 reg;
	पूर्णांक i;

	dev = ice_pf_to_dev(pf);

	अगर (test_bit(ICE_VF_RESETS_DISABLED, pf->state)) अणु
		dev_dbg(dev, "Trying to reset VF %d, but all VF resets are disabled\n",
			vf->vf_id);
		वापस true;
	पूर्ण

	अगर (ice_is_vf_disabled(vf)) अणु
		dev_dbg(dev, "VF is already disabled, there is no need for resetting it, telling VM, all is fine %d\n",
			vf->vf_id);
		वापस true;
	पूर्ण

	/* Set VF disable bit state here, beक्रमe triggering reset */
	set_bit(ICE_VF_STATE_DIS, vf->vf_states);
	ice_trigger_vf_reset(vf, is_vflr, false);

	vsi = ice_get_vf_vsi(vf);

	अगर (test_bit(ICE_VF_STATE_QS_ENA, vf->vf_states))
		ice_dis_vf_qs(vf);

	/* Call Disable LAN Tx queue AQ whether or not queues are
	 * enabled. This is needed क्रम successful completion of VFR.
	 */
	ice_dis_vsi_txq(vsi->port_info, vsi->idx, 0, 0, शून्य, शून्य,
			शून्य, ICE_VF_RESET, vf->vf_id, शून्य);

	hw = &pf->hw;
	/* poll VPGEN_VFRSTAT reg to make sure
	 * that reset is complete
	 */
	क्रम (i = 0; i < 10; i++) अणु
		/* VF reset requires driver to first reset the VF and then
		 * poll the status रेजिस्टर to make sure that the reset
		 * completed successfully.
		 */
		reg = rd32(hw, VPGEN_VFRSTAT(vf->vf_id));
		अगर (reg & VPGEN_VFRSTAT_VFRD_M) अणु
			rsd = true;
			अवरोध;
		पूर्ण

		/* only sleep अगर the reset is not करोne */
		usleep_range(10, 20);
	पूर्ण

	vf->driver_caps = 0;
	ice_vc_set_शेष_allowlist(vf);

	/* Display a warning अगर VF didn't manage to reset in समय, but need to
	 * जारी on with the operation.
	 */
	अगर (!rsd)
		dev_warn(dev, "VF reset check timeout on VF %d\n", vf->vf_id);

	/* disable promiscuous modes in हाल they were enabled
	 * ignore any error अगर disabling process failed
	 */
	अगर (test_bit(ICE_VF_STATE_UC_PROMISC, vf->vf_states) ||
	    test_bit(ICE_VF_STATE_MC_PROMISC, vf->vf_states)) अणु
		अगर (vf->port_vlan_info || vsi->num_vlan)
			promisc_m = ICE_UCAST_VLAN_PROMISC_BITS;
		अन्यथा
			promisc_m = ICE_UCAST_PROMISC_BITS;

		vsi = ice_get_vf_vsi(vf);
		अगर (ice_vf_set_vsi_promisc(vf, vsi, promisc_m, true))
			dev_err(dev, "disabling promiscuous mode failed\n");
	पूर्ण

	ice_vf_fdir_निकास(vf);
	/* clean VF control VSI when resetting VF since it should be setup
	 * only when VF creates its first Fसूची rule.
	 */
	अगर (vf->ctrl_vsi_idx != ICE_NO_VSI)
		ice_vf_ctrl_vsi_release(vf);

	ice_vf_pre_vsi_rebuild(vf);

	अगर (ice_vf_rebuild_vsi_with_release(vf)) अणु
		dev_err(dev, "Failed to release and setup the VF%u's VSI\n", vf->vf_id);
		वापस false;
	पूर्ण

	ice_vf_post_vsi_rebuild(vf);

	/* अगर the VF has been reset allow it to come up again */
	अगर (ice_mbx_clear_malvf(&hw->mbx_snapshot, pf->malvfs, ICE_MAX_VF_COUNT, vf->vf_id))
		dev_dbg(dev, "failed to clear malicious VF state for VF %u\n", i);

	वापस true;
पूर्ण

/**
 * ice_vc_notअगरy_link_state - Inक्रमm all VFs on a PF of link status
 * @pf: poपूर्णांकer to the PF काष्ठाure
 */
व्योम ice_vc_notअगरy_link_state(काष्ठा ice_pf *pf)
अणु
	पूर्णांक i;

	ice_क्रम_each_vf(pf, i)
		ice_vc_notअगरy_vf_link_state(&pf->vf[i]);
पूर्ण

/**
 * ice_vc_notअगरy_reset - Send pending reset message to all VFs
 * @pf: poपूर्णांकer to the PF काष्ठाure
 *
 * indicate a pending reset to all VFs on a given PF
 */
व्योम ice_vc_notअगरy_reset(काष्ठा ice_pf *pf)
अणु
	काष्ठा virtchnl_pf_event pfe;

	अगर (!pf->num_alloc_vfs)
		वापस;

	pfe.event = VIRTCHNL_EVENT_RESET_IMPENDING;
	pfe.severity = PF_EVENT_SEVERITY_CERTAIN_DOOM;
	ice_vc_vf_broadcast(pf, VIRTCHNL_OP_EVENT, VIRTCHNL_STATUS_SUCCESS,
			    (u8 *)&pfe, माप(काष्ठा virtchnl_pf_event));
पूर्ण

/**
 * ice_vc_notअगरy_vf_reset - Notअगरy VF of a reset event
 * @vf: poपूर्णांकer to the VF काष्ठाure
 */
अटल व्योम ice_vc_notअगरy_vf_reset(काष्ठा ice_vf *vf)
अणु
	काष्ठा virtchnl_pf_event pfe;
	काष्ठा ice_pf *pf;

	अगर (!vf)
		वापस;

	pf = vf->pf;
	अगर (ice_validate_vf_id(pf, vf->vf_id))
		वापस;

	/* Bail out अगर VF is in disabled state, neither initialized, nor active
	 * state - otherwise proceed with notअगरications
	 */
	अगर ((!test_bit(ICE_VF_STATE_INIT, vf->vf_states) &&
	     !test_bit(ICE_VF_STATE_ACTIVE, vf->vf_states)) ||
	    test_bit(ICE_VF_STATE_DIS, vf->vf_states))
		वापस;

	pfe.event = VIRTCHNL_EVENT_RESET_IMPENDING;
	pfe.severity = PF_EVENT_SEVERITY_CERTAIN_DOOM;
	ice_aq_send_msg_to_vf(&pf->hw, vf->vf_id, VIRTCHNL_OP_EVENT,
			      VIRTCHNL_STATUS_SUCCESS, (u8 *)&pfe, माप(pfe),
			      शून्य);
पूर्ण

/**
 * ice_init_vf_vsi_res - initialize/setup VF VSI resources
 * @vf: VF to initialize/setup the VSI क्रम
 *
 * This function creates a VSI क्रम the VF, adds a VLAN 0 filter, and sets up the
 * VF VSI's broadcast filter and is only used during initial VF creation.
 */
अटल पूर्णांक ice_init_vf_vsi_res(काष्ठा ice_vf *vf)
अणु
	काष्ठा ice_pf *pf = vf->pf;
	u8 broadcast[ETH_ALEN];
	क्रमागत ice_status status;
	काष्ठा ice_vsi *vsi;
	काष्ठा device *dev;
	पूर्णांक err;

	vf->first_vector_idx = ice_calc_vf_first_vector_idx(pf, vf);

	dev = ice_pf_to_dev(pf);
	vsi = ice_vf_vsi_setup(vf);
	अगर (!vsi)
		वापस -ENOMEM;

	err = ice_vsi_add_vlan(vsi, 0, ICE_FWD_TO_VSI);
	अगर (err) अणु
		dev_warn(dev, "Failed to add VLAN 0 filter for VF %d\n",
			 vf->vf_id);
		जाओ release_vsi;
	पूर्ण

	eth_broadcast_addr(broadcast);
	status = ice_fltr_add_mac(vsi, broadcast, ICE_FWD_TO_VSI);
	अगर (status) अणु
		dev_err(dev, "Failed to add broadcast MAC filter for VF %d, status %s\n",
			vf->vf_id, ice_stat_str(status));
		err = ice_status_to_त्रुटि_सं(status);
		जाओ release_vsi;
	पूर्ण

	vf->num_mac = 1;

	वापस 0;

release_vsi:
	ice_vf_vsi_release(vf);
	वापस err;
पूर्ण

/**
 * ice_start_vfs - start VFs so they are पढ़ोy to be used by SR-IOV
 * @pf: PF the VFs are associated with
 */
अटल पूर्णांक ice_start_vfs(काष्ठा ice_pf *pf)
अणु
	काष्ठा ice_hw *hw = &pf->hw;
	पूर्णांक retval, i;

	ice_क्रम_each_vf(pf, i) अणु
		काष्ठा ice_vf *vf = &pf->vf[i];

		ice_clear_vf_reset_trigger(vf);

		retval = ice_init_vf_vsi_res(vf);
		अगर (retval) अणु
			dev_err(ice_pf_to_dev(pf), "Failed to initialize VSI resources for VF %d, error %d\n",
				vf->vf_id, retval);
			जाओ tearकरोwn;
		पूर्ण

		set_bit(ICE_VF_STATE_INIT, vf->vf_states);
		ice_ena_vf_mappings(vf);
		wr32(hw, VFGEN_RSTAT(vf->vf_id), VIRTCHNL_VFR_VFACTIVE);
	पूर्ण

	ice_flush(hw);
	वापस 0;

tearकरोwn:
	क्रम (i = i - 1; i >= 0; i--) अणु
		काष्ठा ice_vf *vf = &pf->vf[i];

		ice_dis_vf_mappings(vf);
		ice_vf_vsi_release(vf);
	पूर्ण

	वापस retval;
पूर्ण

/**
 * ice_set_dflt_settings_vfs - set VF शेषs during initialization/creation
 * @pf: PF holding reference to all VFs क्रम शेष configuration
 */
अटल व्योम ice_set_dflt_settings_vfs(काष्ठा ice_pf *pf)
अणु
	पूर्णांक i;

	ice_क्रम_each_vf(pf, i) अणु
		काष्ठा ice_vf *vf = &pf->vf[i];

		vf->pf = pf;
		vf->vf_id = i;
		vf->vf_sw_id = pf->first_sw;
		/* assign शेष capabilities */
		set_bit(ICE_VIRTCHNL_VF_CAP_L2, &vf->vf_caps);
		vf->spoofchk = true;
		vf->num_vf_qs = pf->num_qps_per_vf;
		ice_vc_set_शेष_allowlist(vf);

		/* ctrl_vsi_idx will be set to a valid value only when VF
		 * creates its first fdir rule.
		 */
		ice_vf_ctrl_invalidate_vsi(vf);
		ice_vf_fdir_init(vf);
	पूर्ण
पूर्ण

/**
 * ice_alloc_vfs - allocate num_vfs in the PF काष्ठाure
 * @pf: PF to store the allocated VFs in
 * @num_vfs: number of VFs to allocate
 */
अटल पूर्णांक ice_alloc_vfs(काष्ठा ice_pf *pf, पूर्णांक num_vfs)
अणु
	काष्ठा ice_vf *vfs;

	vfs = devm_kसुस्मृति(ice_pf_to_dev(pf), num_vfs, माप(*vfs),
			   GFP_KERNEL);
	अगर (!vfs)
		वापस -ENOMEM;

	pf->vf = vfs;
	pf->num_alloc_vfs = num_vfs;

	वापस 0;
पूर्ण

/**
 * ice_ena_vfs - enable VFs so they are पढ़ोy to be used
 * @pf: poपूर्णांकer to the PF काष्ठाure
 * @num_vfs: number of VFs to enable
 */
अटल पूर्णांक ice_ena_vfs(काष्ठा ice_pf *pf, u16 num_vfs)
अणु
	काष्ठा device *dev = ice_pf_to_dev(pf);
	काष्ठा ice_hw *hw = &pf->hw;
	पूर्णांक ret;

	/* Disable global पूर्णांकerrupt 0 so we करोn't try to handle the VFLR. */
	wr32(hw, GLINT_DYN_CTL(pf->oicr_idx),
	     ICE_ITR_NONE << GLINT_DYN_CTL_ITR_INDX_S);
	set_bit(ICE_OICR_INTR_DIS, pf->state);
	ice_flush(hw);

	ret = pci_enable_sriov(pf->pdev, num_vfs);
	अगर (ret) अणु
		pf->num_alloc_vfs = 0;
		जाओ err_unroll_पूर्णांकr;
	पूर्ण

	ret = ice_alloc_vfs(pf, num_vfs);
	अगर (ret)
		जाओ err_pci_disable_sriov;

	अगर (ice_set_per_vf_res(pf)) अणु
		dev_err(dev, "Not enough resources for %d VFs, try with fewer number of VFs\n",
			num_vfs);
		ret = -ENOSPC;
		जाओ err_unroll_sriov;
	पूर्ण

	ice_set_dflt_settings_vfs(pf);

	अगर (ice_start_vfs(pf)) अणु
		dev_err(dev, "Failed to start VF(s)\n");
		ret = -EAGAIN;
		जाओ err_unroll_sriov;
	पूर्ण

	clear_bit(ICE_VF_DIS, pf->state);
	वापस 0;

err_unroll_sriov:
	devm_kमुक्त(dev, pf->vf);
	pf->vf = शून्य;
	pf->num_alloc_vfs = 0;
err_pci_disable_sriov:
	pci_disable_sriov(pf->pdev);
err_unroll_पूर्णांकr:
	/* rearm पूर्णांकerrupts here */
	ice_irq_dynamic_ena(hw, शून्य, शून्य);
	clear_bit(ICE_OICR_INTR_DIS, pf->state);
	वापस ret;
पूर्ण

/**
 * ice_pci_sriov_ena - Enable or change number of VFs
 * @pf: poपूर्णांकer to the PF काष्ठाure
 * @num_vfs: number of VFs to allocate
 *
 * Returns 0 on success and negative on failure
 */
अटल पूर्णांक ice_pci_sriov_ena(काष्ठा ice_pf *pf, पूर्णांक num_vfs)
अणु
	पूर्णांक pre_existing_vfs = pci_num_vf(pf->pdev);
	काष्ठा device *dev = ice_pf_to_dev(pf);
	पूर्णांक err;

	अगर (pre_existing_vfs && pre_existing_vfs != num_vfs)
		ice_मुक्त_vfs(pf);
	अन्यथा अगर (pre_existing_vfs && pre_existing_vfs == num_vfs)
		वापस 0;

	अगर (num_vfs > pf->num_vfs_supported) अणु
		dev_err(dev, "Can't enable %d VFs, max VFs supported is %d\n",
			num_vfs, pf->num_vfs_supported);
		वापस -EOPNOTSUPP;
	पूर्ण

	dev_info(dev, "Enabling %d VFs\n", num_vfs);
	err = ice_ena_vfs(pf, num_vfs);
	अगर (err) अणु
		dev_err(dev, "Failed to enable SR-IOV: %d\n", err);
		वापस err;
	पूर्ण

	set_bit(ICE_FLAG_SRIOV_ENA, pf->flags);
	वापस 0;
पूर्ण

/**
 * ice_check_sriov_allowed - check अगर SR-IOV is allowed based on various checks
 * @pf: PF to enabled SR-IOV on
 */
अटल पूर्णांक ice_check_sriov_allowed(काष्ठा ice_pf *pf)
अणु
	काष्ठा device *dev = ice_pf_to_dev(pf);

	अगर (!test_bit(ICE_FLAG_SRIOV_CAPABLE, pf->flags)) अणु
		dev_err(dev, "This device is not capable of SR-IOV\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (ice_is_safe_mode(pf)) अणु
		dev_err(dev, "SR-IOV cannot be configured - Device is in Safe Mode\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (!ice_pf_state_is_nominal(pf)) अणु
		dev_err(dev, "Cannot enable SR-IOV, device not ready\n");
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ice_sriov_configure - Enable or change number of VFs via sysfs
 * @pdev: poपूर्णांकer to a pci_dev काष्ठाure
 * @num_vfs: number of VFs to allocate or 0 to मुक्त VFs
 *
 * This function is called when the user updates the number of VFs in sysfs. On
 * success वापस whatever num_vfs was set to by the caller. Return negative on
 * failure.
 */
पूर्णांक ice_sriov_configure(काष्ठा pci_dev *pdev, पूर्णांक num_vfs)
अणु
	काष्ठा ice_pf *pf = pci_get_drvdata(pdev);
	काष्ठा device *dev = ice_pf_to_dev(pf);
	क्रमागत ice_status status;
	पूर्णांक err;

	err = ice_check_sriov_allowed(pf);
	अगर (err)
		वापस err;

	अगर (!num_vfs) अणु
		अगर (!pci_vfs_asचिन्हित(pdev)) अणु
			ice_mbx_deinit_snapshot(&pf->hw);
			ice_मुक्त_vfs(pf);
			अगर (pf->lag)
				ice_enable_lag(pf->lag);
			वापस 0;
		पूर्ण

		dev_err(dev, "can't free VFs because some are assigned to VMs.\n");
		वापस -EBUSY;
	पूर्ण

	status = ice_mbx_init_snapshot(&pf->hw, num_vfs);
	अगर (status)
		वापस ice_status_to_त्रुटि_सं(status);

	err = ice_pci_sriov_ena(pf, num_vfs);
	अगर (err) अणु
		ice_mbx_deinit_snapshot(&pf->hw);
		वापस err;
	पूर्ण

	अगर (pf->lag)
		ice_disable_lag(pf->lag);
	वापस num_vfs;
पूर्ण

/**
 * ice_process_vflr_event - Free VF resources via IRQ calls
 * @pf: poपूर्णांकer to the PF काष्ठाure
 *
 * called from the VFLR IRQ handler to
 * मुक्त up VF resources and state variables
 */
व्योम ice_process_vflr_event(काष्ठा ice_pf *pf)
अणु
	काष्ठा ice_hw *hw = &pf->hw;
	अचिन्हित पूर्णांक vf_id;
	u32 reg;

	अगर (!test_and_clear_bit(ICE_VFLR_EVENT_PENDING, pf->state) ||
	    !pf->num_alloc_vfs)
		वापस;

	ice_क्रम_each_vf(pf, vf_id) अणु
		काष्ठा ice_vf *vf = &pf->vf[vf_id];
		u32 reg_idx, bit_idx;

		reg_idx = (hw->func_caps.vf_base_id + vf_id) / 32;
		bit_idx = (hw->func_caps.vf_base_id + vf_id) % 32;
		/* पढ़ो GLGEN_VFLRSTAT रेजिस्टर to find out the flr VFs */
		reg = rd32(hw, GLGEN_VFLRSTAT(reg_idx));
		अगर (reg & BIT(bit_idx))
			/* GLGEN_VFLRSTAT bit will be cleared in ice_reset_vf */
			ice_reset_vf(vf, true);
	पूर्ण
पूर्ण

/**
 * ice_vc_reset_vf - Perक्रमm software reset on the VF after inक्रमming the AVF
 * @vf: poपूर्णांकer to the VF info
 */
अटल व्योम ice_vc_reset_vf(काष्ठा ice_vf *vf)
अणु
	ice_vc_notअगरy_vf_reset(vf);
	ice_reset_vf(vf, false);
पूर्ण

/**
 * ice_get_vf_from_pfq - get the VF who owns the PF space queue passed in
 * @pf: PF used to index all VFs
 * @pfq: queue index relative to the PF's function space
 *
 * If no VF is found who owns the pfq then वापस शून्य, otherwise वापस a
 * poपूर्णांकer to the VF who owns the pfq
 */
अटल काष्ठा ice_vf *ice_get_vf_from_pfq(काष्ठा ice_pf *pf, u16 pfq)
अणु
	अचिन्हित पूर्णांक vf_id;

	ice_क्रम_each_vf(pf, vf_id) अणु
		काष्ठा ice_vf *vf = &pf->vf[vf_id];
		काष्ठा ice_vsi *vsi;
		u16 rxq_idx;

		vsi = ice_get_vf_vsi(vf);

		ice_क्रम_each_rxq(vsi, rxq_idx)
			अगर (vsi->rxq_map[rxq_idx] == pfq)
				वापस vf;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * ice_globalq_to_pfq - convert from global queue index to PF space queue index
 * @pf: PF used क्रम conversion
 * @globalq: global queue index used to convert to PF space queue index
 */
अटल u32 ice_globalq_to_pfq(काष्ठा ice_pf *pf, u32 globalq)
अणु
	वापस globalq - pf->hw.func_caps.common_cap.rxq_first_id;
पूर्ण

/**
 * ice_vf_lan_overflow_event - handle LAN overflow event क्रम a VF
 * @pf: PF that the LAN overflow event happened on
 * @event: काष्ठाure holding the event inक्रमmation क्रम the LAN overflow event
 *
 * Determine अगर the LAN overflow event was caused by a VF queue. If it was not
 * caused by a VF, करो nothing. If a VF caused this LAN overflow event trigger a
 * reset on the offending VF.
 */
व्योम
ice_vf_lan_overflow_event(काष्ठा ice_pf *pf, काष्ठा ice_rq_event_info *event)
अणु
	u32 gldcb_rtctq, queue;
	काष्ठा ice_vf *vf;

	gldcb_rtctq = le32_to_cpu(event->desc.params.lan_overflow.prtdcb_ruptq);
	dev_dbg(ice_pf_to_dev(pf), "GLDCB_RTCTQ: 0x%08x\n", gldcb_rtctq);

	/* event वापसs device global Rx queue number */
	queue = (gldcb_rtctq & GLDCB_RTCTQ_RXQNUM_M) >>
		GLDCB_RTCTQ_RXQNUM_S;

	vf = ice_get_vf_from_pfq(pf, ice_globalq_to_pfq(pf, queue));
	अगर (!vf)
		वापस;

	ice_vc_reset_vf(vf);
पूर्ण

/**
 * ice_vc_send_msg_to_vf - Send message to VF
 * @vf: poपूर्णांकer to the VF info
 * @v_opcode: भव channel opcode
 * @v_retval: भव channel वापस value
 * @msg: poपूर्णांकer to the msg buffer
 * @msglen: msg length
 *
 * send msg to VF
 */
पूर्णांक
ice_vc_send_msg_to_vf(काष्ठा ice_vf *vf, u32 v_opcode,
		      क्रमागत virtchnl_status_code v_retval, u8 *msg, u16 msglen)
अणु
	क्रमागत ice_status aq_ret;
	काष्ठा device *dev;
	काष्ठा ice_pf *pf;

	अगर (!vf)
		वापस -EINVAL;

	pf = vf->pf;
	अगर (ice_validate_vf_id(pf, vf->vf_id))
		वापस -EINVAL;

	dev = ice_pf_to_dev(pf);

	/* single place to detect unsuccessful वापस values */
	अगर (v_retval) अणु
		vf->num_inval_msgs++;
		dev_info(dev, "VF %d failed opcode %d, retval: %d\n", vf->vf_id,
			 v_opcode, v_retval);
		अगर (vf->num_inval_msgs > ICE_DFLT_NUM_INVAL_MSGS_ALLOWED) अणु
			dev_err(dev, "Number of invalid messages exceeded for VF %d\n",
				vf->vf_id);
			dev_err(dev, "Use PF Control I/F to enable the VF\n");
			set_bit(ICE_VF_STATE_DIS, vf->vf_states);
			वापस -EIO;
		पूर्ण
	पूर्ण अन्यथा अणु
		vf->num_valid_msgs++;
		/* reset the invalid counter, अगर a valid message is received. */
		vf->num_inval_msgs = 0;
	पूर्ण

	aq_ret = ice_aq_send_msg_to_vf(&pf->hw, vf->vf_id, v_opcode, v_retval,
				       msg, msglen, शून्य);
	अगर (aq_ret && pf->hw.mailboxq.sq_last_status != ICE_AQ_RC_ENOSYS) अणु
		dev_info(dev, "Unable to send the message to VF %d ret %s aq_err %s\n",
			 vf->vf_id, ice_stat_str(aq_ret),
			 ice_aq_str(pf->hw.mailboxq.sq_last_status));
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ice_vc_get_ver_msg
 * @vf: poपूर्णांकer to the VF info
 * @msg: poपूर्णांकer to the msg buffer
 *
 * called from the VF to request the API version used by the PF
 */
अटल पूर्णांक ice_vc_get_ver_msg(काष्ठा ice_vf *vf, u8 *msg)
अणु
	काष्ठा virtchnl_version_info info = अणु
		VIRTCHNL_VERSION_MAJOR, VIRTCHNL_VERSION_MINOR
	पूर्ण;

	vf->vf_ver = *(काष्ठा virtchnl_version_info *)msg;
	/* VFs running the 1.0 API expect to get 1.0 back or they will cry. */
	अगर (VF_IS_V10(&vf->vf_ver))
		info.minor = VIRTCHNL_VERSION_MINOR_NO_VF_CAPS;

	वापस ice_vc_send_msg_to_vf(vf, VIRTCHNL_OP_VERSION,
				     VIRTCHNL_STATUS_SUCCESS, (u8 *)&info,
				     माप(काष्ठा virtchnl_version_info));
पूर्ण

/**
 * ice_vc_get_max_frame_size - get max frame size allowed क्रम VF
 * @vf: VF used to determine max frame size
 *
 * Max frame size is determined based on the current port's max frame size and
 * whether a port VLAN is configured on this VF. The VF is not aware whether
 * it's in a port VLAN so the PF needs to account क्रम this in max frame size
 * checks and sending the max frame size to the VF.
 */
अटल u16 ice_vc_get_max_frame_size(काष्ठा ice_vf *vf)
अणु
	काष्ठा ice_port_info *pi = ice_vf_get_port_info(vf);
	u16 max_frame_size;

	max_frame_size = pi->phy.link_info.max_frame_size;

	अगर (vf->port_vlan_info)
		max_frame_size -= VLAN_HLEN;

	वापस max_frame_size;
पूर्ण

/**
 * ice_vc_get_vf_res_msg
 * @vf: poपूर्णांकer to the VF info
 * @msg: poपूर्णांकer to the msg buffer
 *
 * called from the VF to request its resources
 */
अटल पूर्णांक ice_vc_get_vf_res_msg(काष्ठा ice_vf *vf, u8 *msg)
अणु
	क्रमागत virtchnl_status_code v_ret = VIRTCHNL_STATUS_SUCCESS;
	काष्ठा virtchnl_vf_resource *vfres = शून्य;
	काष्ठा ice_pf *pf = vf->pf;
	काष्ठा ice_vsi *vsi;
	पूर्णांक len = 0;
	पूर्णांक ret;

	अगर (ice_check_vf_init(pf, vf)) अणु
		v_ret = VIRTCHNL_STATUS_ERR_PARAM;
		जाओ err;
	पूर्ण

	len = माप(काष्ठा virtchnl_vf_resource);

	vfres = kzalloc(len, GFP_KERNEL);
	अगर (!vfres) अणु
		v_ret = VIRTCHNL_STATUS_ERR_NO_MEMORY;
		len = 0;
		जाओ err;
	पूर्ण
	अगर (VF_IS_V11(&vf->vf_ver))
		vf->driver_caps = *(u32 *)msg;
	अन्यथा
		vf->driver_caps = VIRTCHNL_VF_OFFLOAD_L2 |
				  VIRTCHNL_VF_OFFLOAD_RSS_REG |
				  VIRTCHNL_VF_OFFLOAD_VLAN;

	vfres->vf_cap_flags = VIRTCHNL_VF_OFFLOAD_L2;
	vsi = ice_get_vf_vsi(vf);
	अगर (!vsi) अणु
		v_ret = VIRTCHNL_STATUS_ERR_PARAM;
		जाओ err;
	पूर्ण

	अगर (!vsi->info.pvid)
		vfres->vf_cap_flags |= VIRTCHNL_VF_OFFLOAD_VLAN;

	अगर (vf->driver_caps & VIRTCHNL_VF_OFFLOAD_RSS_PF) अणु
		vfres->vf_cap_flags |= VIRTCHNL_VF_OFFLOAD_RSS_PF;
	पूर्ण अन्यथा अणु
		अगर (vf->driver_caps & VIRTCHNL_VF_OFFLOAD_RSS_AQ)
			vfres->vf_cap_flags |= VIRTCHNL_VF_OFFLOAD_RSS_AQ;
		अन्यथा
			vfres->vf_cap_flags |= VIRTCHNL_VF_OFFLOAD_RSS_REG;
	पूर्ण

	अगर (vf->driver_caps & VIRTCHNL_VF_OFFLOAD_Fसूची_PF)
		vfres->vf_cap_flags |= VIRTCHNL_VF_OFFLOAD_Fसूची_PF;

	अगर (vf->driver_caps & VIRTCHNL_VF_OFFLOAD_RSS_PCTYPE_V2)
		vfres->vf_cap_flags |= VIRTCHNL_VF_OFFLOAD_RSS_PCTYPE_V2;

	अगर (vf->driver_caps & VIRTCHNL_VF_OFFLOAD_ENCAP)
		vfres->vf_cap_flags |= VIRTCHNL_VF_OFFLOAD_ENCAP;

	अगर (vf->driver_caps & VIRTCHNL_VF_OFFLOAD_ENCAP_CSUM)
		vfres->vf_cap_flags |= VIRTCHNL_VF_OFFLOAD_ENCAP_CSUM;

	अगर (vf->driver_caps & VIRTCHNL_VF_OFFLOAD_RX_POLLING)
		vfres->vf_cap_flags |= VIRTCHNL_VF_OFFLOAD_RX_POLLING;

	अगर (vf->driver_caps & VIRTCHNL_VF_OFFLOAD_WB_ON_ITR)
		vfres->vf_cap_flags |= VIRTCHNL_VF_OFFLOAD_WB_ON_ITR;

	अगर (vf->driver_caps & VIRTCHNL_VF_OFFLOAD_REQ_QUEUES)
		vfres->vf_cap_flags |= VIRTCHNL_VF_OFFLOAD_REQ_QUEUES;

	अगर (vf->driver_caps & VIRTCHNL_VF_CAP_ADV_LINK_SPEED)
		vfres->vf_cap_flags |= VIRTCHNL_VF_CAP_ADV_LINK_SPEED;

	अगर (vf->driver_caps & VIRTCHNL_VF_OFFLOAD_ADV_RSS_PF)
		vfres->vf_cap_flags |= VIRTCHNL_VF_OFFLOAD_ADV_RSS_PF;

	अगर (vf->driver_caps & VIRTCHNL_VF_OFFLOAD_USO)
		vfres->vf_cap_flags |= VIRTCHNL_VF_OFFLOAD_USO;

	vfres->num_vsis = 1;
	/* Tx and Rx queue are equal क्रम VF */
	vfres->num_queue_pairs = vsi->num_txq;
	vfres->max_vectors = pf->num_msix_per_vf;
	vfres->rss_key_size = ICE_VSIQF_HKEY_ARRAY_SIZE;
	vfres->rss_lut_size = ICE_VSIQF_HLUT_ARRAY_SIZE;
	vfres->max_mtu = ice_vc_get_max_frame_size(vf);

	vfres->vsi_res[0].vsi_id = vf->lan_vsi_num;
	vfres->vsi_res[0].vsi_type = VIRTCHNL_VSI_SRIOV;
	vfres->vsi_res[0].num_queue_pairs = vsi->num_txq;
	ether_addr_copy(vfres->vsi_res[0].शेष_mac_addr,
			vf->dflt_lan_addr.addr);

	/* match guest capabilities */
	vf->driver_caps = vfres->vf_cap_flags;

	ice_vc_set_caps_allowlist(vf);
	ice_vc_set_working_allowlist(vf);

	set_bit(ICE_VF_STATE_ACTIVE, vf->vf_states);

err:
	/* send the response back to the VF */
	ret = ice_vc_send_msg_to_vf(vf, VIRTCHNL_OP_GET_VF_RESOURCES, v_ret,
				    (u8 *)vfres, len);

	kमुक्त(vfres);
	वापस ret;
पूर्ण

/**
 * ice_vc_reset_vf_msg
 * @vf: poपूर्णांकer to the VF info
 *
 * called from the VF to reset itself,
 * unlike other virtchnl messages, PF driver
 * करोesn't send the response back to the VF
 */
अटल व्योम ice_vc_reset_vf_msg(काष्ठा ice_vf *vf)
अणु
	अगर (test_bit(ICE_VF_STATE_INIT, vf->vf_states))
		ice_reset_vf(vf, false);
पूर्ण

/**
 * ice_find_vsi_from_id
 * @pf: the PF काष्ठाure to search क्रम the VSI
 * @id: ID of the VSI it is searching क्रम
 *
 * searches क्रम the VSI with the given ID
 */
अटल काष्ठा ice_vsi *ice_find_vsi_from_id(काष्ठा ice_pf *pf, u16 id)
अणु
	पूर्णांक i;

	ice_क्रम_each_vsi(pf, i)
		अगर (pf->vsi[i] && pf->vsi[i]->vsi_num == id)
			वापस pf->vsi[i];

	वापस शून्य;
पूर्ण

/**
 * ice_vc_isvalid_vsi_id
 * @vf: poपूर्णांकer to the VF info
 * @vsi_id: VF relative VSI ID
 *
 * check क्रम the valid VSI ID
 */
bool ice_vc_isvalid_vsi_id(काष्ठा ice_vf *vf, u16 vsi_id)
अणु
	काष्ठा ice_pf *pf = vf->pf;
	काष्ठा ice_vsi *vsi;

	vsi = ice_find_vsi_from_id(pf, vsi_id);

	वापस (vsi && (vsi->vf_id == vf->vf_id));
पूर्ण

/**
 * ice_vc_isvalid_q_id
 * @vf: poपूर्णांकer to the VF info
 * @vsi_id: VSI ID
 * @qid: VSI relative queue ID
 *
 * check क्रम the valid queue ID
 */
अटल bool ice_vc_isvalid_q_id(काष्ठा ice_vf *vf, u16 vsi_id, u8 qid)
अणु
	काष्ठा ice_vsi *vsi = ice_find_vsi_from_id(vf->pf, vsi_id);
	/* allocated Tx and Rx queues should be always equal क्रम VF VSI */
	वापस (vsi && (qid < vsi->alloc_txq));
पूर्ण

/**
 * ice_vc_isvalid_ring_len
 * @ring_len: length of ring
 *
 * check क्रम the valid ring count, should be multiple of ICE_REQ_DESC_MULTIPLE
 * or zero
 */
अटल bool ice_vc_isvalid_ring_len(u16 ring_len)
अणु
	वापस ring_len == 0 ||
	       (ring_len >= ICE_MIN_NUM_DESC &&
		ring_len <= ICE_MAX_NUM_DESC &&
		!(ring_len % ICE_REQ_DESC_MULTIPLE));
पूर्ण

/**
 * ice_vc_parse_rss_cfg - parses hash fields and headers from
 * a specअगरic virtchnl RSS cfg
 * @hw: poपूर्णांकer to the hardware
 * @rss_cfg: poपूर्णांकer to the virtchnl RSS cfg
 * @addl_hdrs: poपूर्णांकer to the protocol header fields (ICE_FLOW_SEG_HDR_*)
 * to configure
 * @hash_flds: poपूर्णांकer to the hash bit fields (ICE_FLOW_HASH_*) to configure
 *
 * Return true अगर all the protocol header and hash fields in the RSS cfg could
 * be parsed, अन्यथा वापस false
 *
 * This function parses the virtchnl RSS cfg to be the पूर्णांकended
 * hash fields and the पूर्णांकended header क्रम RSS configuration
 */
अटल bool
ice_vc_parse_rss_cfg(काष्ठा ice_hw *hw, काष्ठा virtchnl_rss_cfg *rss_cfg,
		     u32 *addl_hdrs, u64 *hash_flds)
अणु
	स्थिर काष्ठा ice_vc_hash_field_match_type *hf_list;
	स्थिर काष्ठा ice_vc_hdr_match_type *hdr_list;
	पूर्णांक i, hf_list_len, hdr_list_len;

	अगर (!म_भेदन(hw->active_pkg_name, "ICE COMMS Package",
		     माप(hw->active_pkg_name))) अणु
		hf_list = ice_vc_hash_field_list_comms;
		hf_list_len = ARRAY_SIZE(ice_vc_hash_field_list_comms);
		hdr_list = ice_vc_hdr_list_comms;
		hdr_list_len = ARRAY_SIZE(ice_vc_hdr_list_comms);
	पूर्ण अन्यथा अणु
		hf_list = ice_vc_hash_field_list_os;
		hf_list_len = ARRAY_SIZE(ice_vc_hash_field_list_os);
		hdr_list = ice_vc_hdr_list_os;
		hdr_list_len = ARRAY_SIZE(ice_vc_hdr_list_os);
	पूर्ण

	क्रम (i = 0; i < rss_cfg->proto_hdrs.count; i++) अणु
		काष्ठा virtchnl_proto_hdr *proto_hdr =
					&rss_cfg->proto_hdrs.proto_hdr[i];
		bool hdr_found = false;
		पूर्णांक j;

		/* Find matched ice headers according to virtchnl headers. */
		क्रम (j = 0; j < hdr_list_len; j++) अणु
			काष्ठा ice_vc_hdr_match_type hdr_map = hdr_list[j];

			अगर (proto_hdr->type == hdr_map.vc_hdr) अणु
				*addl_hdrs |= hdr_map.ice_hdr;
				hdr_found = true;
			पूर्ण
		पूर्ण

		अगर (!hdr_found)
			वापस false;

		/* Find matched ice hash fields according to
		 * virtchnl hash fields.
		 */
		क्रम (j = 0; j < hf_list_len; j++) अणु
			काष्ठा ice_vc_hash_field_match_type hf_map = hf_list[j];

			अगर (proto_hdr->type == hf_map.vc_hdr &&
			    proto_hdr->field_selector == hf_map.vc_hash_field) अणु
				*hash_flds |= hf_map.ice_hash_field;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

/**
 * ice_vf_adv_rss_offload_ena - determine अगर capabilities support advanced
 * RSS offloads
 * @caps: VF driver negotiated capabilities
 *
 * Return true अगर VIRTCHNL_VF_OFFLOAD_ADV_RSS_PF capability is set,
 * अन्यथा वापस false
 */
अटल bool ice_vf_adv_rss_offload_ena(u32 caps)
अणु
	वापस !!(caps & VIRTCHNL_VF_OFFLOAD_ADV_RSS_PF);
पूर्ण

/**
 * ice_vc_handle_rss_cfg
 * @vf: poपूर्णांकer to the VF info
 * @msg: poपूर्णांकer to the message buffer
 * @add: add a RSS config अगर true, otherwise delete a RSS config
 *
 * This function adds/deletes a RSS config
 */
अटल पूर्णांक ice_vc_handle_rss_cfg(काष्ठा ice_vf *vf, u8 *msg, bool add)
अणु
	u32 v_opcode = add ? VIRTCHNL_OP_ADD_RSS_CFG : VIRTCHNL_OP_DEL_RSS_CFG;
	काष्ठा virtchnl_rss_cfg *rss_cfg = (काष्ठा virtchnl_rss_cfg *)msg;
	क्रमागत virtchnl_status_code v_ret = VIRTCHNL_STATUS_SUCCESS;
	काष्ठा device *dev = ice_pf_to_dev(vf->pf);
	काष्ठा ice_hw *hw = &vf->pf->hw;
	काष्ठा ice_vsi *vsi;

	अगर (!test_bit(ICE_FLAG_RSS_ENA, vf->pf->flags)) अणु
		dev_dbg(dev, "VF %d attempting to configure RSS, but RSS is not supported by the PF\n",
			vf->vf_id);
		v_ret = VIRTCHNL_STATUS_ERR_NOT_SUPPORTED;
		जाओ error_param;
	पूर्ण

	अगर (!ice_vf_adv_rss_offload_ena(vf->driver_caps)) अणु
		dev_dbg(dev, "VF %d attempting to configure RSS, but Advanced RSS offload is not supported\n",
			vf->vf_id);
		v_ret = VIRTCHNL_STATUS_ERR_PARAM;
		जाओ error_param;
	पूर्ण

	अगर (!test_bit(ICE_VF_STATE_ACTIVE, vf->vf_states)) अणु
		v_ret = VIRTCHNL_STATUS_ERR_PARAM;
		जाओ error_param;
	पूर्ण

	अगर (rss_cfg->proto_hdrs.count > VIRTCHNL_MAX_NUM_PROTO_HDRS ||
	    rss_cfg->rss_algorithm < VIRTCHNL_RSS_ALG_TOEPLITZ_ASYMMETRIC ||
	    rss_cfg->rss_algorithm > VIRTCHNL_RSS_ALG_XOR_SYMMETRIC) अणु
		dev_dbg(dev, "VF %d attempting to configure RSS, but RSS configuration is not valid\n",
			vf->vf_id);
		v_ret = VIRTCHNL_STATUS_ERR_PARAM;
		जाओ error_param;
	पूर्ण

	vsi = ice_get_vf_vsi(vf);
	अगर (!vsi) अणु
		v_ret = VIRTCHNL_STATUS_ERR_PARAM;
		जाओ error_param;
	पूर्ण

	अगर (rss_cfg->rss_algorithm == VIRTCHNL_RSS_ALG_R_ASYMMETRIC) अणु
		काष्ठा ice_vsi_ctx *ctx;
		क्रमागत ice_status status;
		u8 lut_type, hash_type;

		lut_type = ICE_AQ_VSI_Q_OPT_RSS_LUT_VSI;
		hash_type = add ? ICE_AQ_VSI_Q_OPT_RSS_XOR :
				ICE_AQ_VSI_Q_OPT_RSS_TPLZ;

		ctx = kzalloc(माप(*ctx), GFP_KERNEL);
		अगर (!ctx) अणु
			v_ret = VIRTCHNL_STATUS_ERR_NO_MEMORY;
			जाओ error_param;
		पूर्ण

		ctx->info.q_opt_rss = ((lut_type <<
					ICE_AQ_VSI_Q_OPT_RSS_LUT_S) &
				       ICE_AQ_VSI_Q_OPT_RSS_LUT_M) |
				       (hash_type &
					ICE_AQ_VSI_Q_OPT_RSS_HASH_M);

		/* Preserve existing queueing option setting */
		ctx->info.q_opt_rss |= (vsi->info.q_opt_rss &
					  ICE_AQ_VSI_Q_OPT_RSS_GBL_LUT_M);
		ctx->info.q_opt_tc = vsi->info.q_opt_tc;
		ctx->info.q_opt_flags = vsi->info.q_opt_rss;

		ctx->info.valid_sections =
				cpu_to_le16(ICE_AQ_VSI_PROP_Q_OPT_VALID);

		status = ice_update_vsi(hw, vsi->idx, ctx, शून्य);
		अगर (status) अणु
			dev_err(dev, "update VSI for RSS failed, err %s aq_err %s\n",
				ice_stat_str(status),
				ice_aq_str(hw->adminq.sq_last_status));
			v_ret = VIRTCHNL_STATUS_ERR_PARAM;
		पूर्ण अन्यथा अणु
			vsi->info.q_opt_rss = ctx->info.q_opt_rss;
		पूर्ण

		kमुक्त(ctx);
	पूर्ण अन्यथा अणु
		u32 addl_hdrs = ICE_FLOW_SEG_HDR_NONE;
		u64 hash_flds = ICE_HASH_INVALID;

		अगर (!ice_vc_parse_rss_cfg(hw, rss_cfg, &addl_hdrs,
					  &hash_flds)) अणु
			v_ret = VIRTCHNL_STATUS_ERR_PARAM;
			जाओ error_param;
		पूर्ण

		अगर (add) अणु
			अगर (ice_add_rss_cfg(hw, vsi->idx, hash_flds,
					    addl_hdrs)) अणु
				v_ret = VIRTCHNL_STATUS_ERR_PARAM;
				dev_err(dev, "ice_add_rss_cfg failed for vsi = %d, v_ret = %d\n",
					vsi->vsi_num, v_ret);
			पूर्ण
		पूर्ण अन्यथा अणु
			क्रमागत ice_status status;

			status = ice_rem_rss_cfg(hw, vsi->idx, hash_flds,
						 addl_hdrs);
			/* We just ignore ICE_ERR_DOES_NOT_EXIST, because
			 * अगर two configurations share the same profile हटाओ
			 * one of them actually हटाओs both, since the
			 * profile is deleted.
			 */
			अगर (status && status != ICE_ERR_DOES_NOT_EXIST) अणु
				v_ret = VIRTCHNL_STATUS_ERR_PARAM;
				dev_err(dev, "ice_rem_rss_cfg failed for VF ID:%d, error:%s\n",
					vf->vf_id, ice_stat_str(status));
			पूर्ण
		पूर्ण
	पूर्ण

error_param:
	वापस ice_vc_send_msg_to_vf(vf, v_opcode, v_ret, शून्य, 0);
पूर्ण

/**
 * ice_vc_config_rss_key
 * @vf: poपूर्णांकer to the VF info
 * @msg: poपूर्णांकer to the msg buffer
 *
 * Configure the VF's RSS key
 */
अटल पूर्णांक ice_vc_config_rss_key(काष्ठा ice_vf *vf, u8 *msg)
अणु
	क्रमागत virtchnl_status_code v_ret = VIRTCHNL_STATUS_SUCCESS;
	काष्ठा virtchnl_rss_key *vrk =
		(काष्ठा virtchnl_rss_key *)msg;
	काष्ठा ice_vsi *vsi;

	अगर (!test_bit(ICE_VF_STATE_ACTIVE, vf->vf_states)) अणु
		v_ret = VIRTCHNL_STATUS_ERR_PARAM;
		जाओ error_param;
	पूर्ण

	अगर (!ice_vc_isvalid_vsi_id(vf, vrk->vsi_id)) अणु
		v_ret = VIRTCHNL_STATUS_ERR_PARAM;
		जाओ error_param;
	पूर्ण

	अगर (vrk->key_len != ICE_VSIQF_HKEY_ARRAY_SIZE) अणु
		v_ret = VIRTCHNL_STATUS_ERR_PARAM;
		जाओ error_param;
	पूर्ण

	अगर (!test_bit(ICE_FLAG_RSS_ENA, vf->pf->flags)) अणु
		v_ret = VIRTCHNL_STATUS_ERR_PARAM;
		जाओ error_param;
	पूर्ण

	vsi = ice_get_vf_vsi(vf);
	अगर (!vsi) अणु
		v_ret = VIRTCHNL_STATUS_ERR_PARAM;
		जाओ error_param;
	पूर्ण

	अगर (ice_set_rss_key(vsi, vrk->key))
		v_ret = VIRTCHNL_STATUS_ERR_ADMIN_QUEUE_ERROR;
error_param:
	वापस ice_vc_send_msg_to_vf(vf, VIRTCHNL_OP_CONFIG_RSS_KEY, v_ret,
				     शून्य, 0);
पूर्ण

/**
 * ice_vc_config_rss_lut
 * @vf: poपूर्णांकer to the VF info
 * @msg: poपूर्णांकer to the msg buffer
 *
 * Configure the VF's RSS LUT
 */
अटल पूर्णांक ice_vc_config_rss_lut(काष्ठा ice_vf *vf, u8 *msg)
अणु
	काष्ठा virtchnl_rss_lut *vrl = (काष्ठा virtchnl_rss_lut *)msg;
	क्रमागत virtchnl_status_code v_ret = VIRTCHNL_STATUS_SUCCESS;
	काष्ठा ice_vsi *vsi;

	अगर (!test_bit(ICE_VF_STATE_ACTIVE, vf->vf_states)) अणु
		v_ret = VIRTCHNL_STATUS_ERR_PARAM;
		जाओ error_param;
	पूर्ण

	अगर (!ice_vc_isvalid_vsi_id(vf, vrl->vsi_id)) अणु
		v_ret = VIRTCHNL_STATUS_ERR_PARAM;
		जाओ error_param;
	पूर्ण

	अगर (vrl->lut_entries != ICE_VSIQF_HLUT_ARRAY_SIZE) अणु
		v_ret = VIRTCHNL_STATUS_ERR_PARAM;
		जाओ error_param;
	पूर्ण

	अगर (!test_bit(ICE_FLAG_RSS_ENA, vf->pf->flags)) अणु
		v_ret = VIRTCHNL_STATUS_ERR_PARAM;
		जाओ error_param;
	पूर्ण

	vsi = ice_get_vf_vsi(vf);
	अगर (!vsi) अणु
		v_ret = VIRTCHNL_STATUS_ERR_PARAM;
		जाओ error_param;
	पूर्ण

	अगर (ice_set_rss_lut(vsi, vrl->lut, ICE_VSIQF_HLUT_ARRAY_SIZE))
		v_ret = VIRTCHNL_STATUS_ERR_ADMIN_QUEUE_ERROR;
error_param:
	वापस ice_vc_send_msg_to_vf(vf, VIRTCHNL_OP_CONFIG_RSS_LUT, v_ret,
				     शून्य, 0);
पूर्ण

/**
 * ice_रुको_on_vf_reset - poll to make sure a given VF is पढ़ोy after reset
 * @vf: The VF being resseting
 *
 * The max poll समय is about ~800ms, which is about the maximum समय it takes
 * क्रम a VF to be reset and/or a VF driver to be हटाओd.
 */
अटल व्योम ice_रुको_on_vf_reset(काष्ठा ice_vf *vf)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ICE_MAX_VF_RESET_TRIES; i++) अणु
		अगर (test_bit(ICE_VF_STATE_INIT, vf->vf_states))
			अवरोध;
		msleep(ICE_MAX_VF_RESET_SLEEP_MS);
	पूर्ण
पूर्ण

/**
 * ice_check_vf_पढ़ोy_क्रम_cfg - check अगर VF is पढ़ोy to be configured/queried
 * @vf: VF to check अगर it's पढ़ोy to be configured/queried
 *
 * The purpose of this function is to make sure the VF is not in reset, not
 * disabled, and initialized so it can be configured and/or queried by a host
 * administrator.
 */
अटल पूर्णांक ice_check_vf_पढ़ोy_क्रम_cfg(काष्ठा ice_vf *vf)
अणु
	काष्ठा ice_pf *pf;

	ice_रुको_on_vf_reset(vf);

	अगर (ice_is_vf_disabled(vf))
		वापस -EINVAL;

	pf = vf->pf;
	अगर (ice_check_vf_init(pf, vf))
		वापस -EBUSY;

	वापस 0;
पूर्ण

/**
 * ice_set_vf_spoofchk
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @vf_id: VF identअगरier
 * @ena: flag to enable or disable feature
 *
 * Enable or disable VF spoof checking
 */
पूर्णांक ice_set_vf_spoofchk(काष्ठा net_device *netdev, पूर्णांक vf_id, bool ena)
अणु
	काष्ठा ice_netdev_priv *np = netdev_priv(netdev);
	काष्ठा ice_pf *pf = np->vsi->back;
	काष्ठा ice_vsi_ctx *ctx;
	काष्ठा ice_vsi *vf_vsi;
	क्रमागत ice_status status;
	काष्ठा device *dev;
	काष्ठा ice_vf *vf;
	पूर्णांक ret;

	dev = ice_pf_to_dev(pf);
	अगर (ice_validate_vf_id(pf, vf_id))
		वापस -EINVAL;

	vf = &pf->vf[vf_id];
	ret = ice_check_vf_पढ़ोy_क्रम_cfg(vf);
	अगर (ret)
		वापस ret;

	vf_vsi = ice_get_vf_vsi(vf);
	अगर (!vf_vsi) अणु
		netdev_err(netdev, "VSI %d for VF %d is null\n",
			   vf->lan_vsi_idx, vf->vf_id);
		वापस -EINVAL;
	पूर्ण

	अगर (vf_vsi->type != ICE_VSI_VF) अणु
		netdev_err(netdev, "Type %d of VSI %d for VF %d is no ICE_VSI_VF\n",
			   vf_vsi->type, vf_vsi->vsi_num, vf->vf_id);
		वापस -ENODEV;
	पूर्ण

	अगर (ena == vf->spoofchk) अणु
		dev_dbg(dev, "VF spoofchk already %s\n", ena ? "ON" : "OFF");
		वापस 0;
	पूर्ण

	ctx = kzalloc(माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	ctx->info.sec_flags = vf_vsi->info.sec_flags;
	ctx->info.valid_sections = cpu_to_le16(ICE_AQ_VSI_PROP_SECURITY_VALID);
	अगर (ena) अणु
		ctx->info.sec_flags |=
			ICE_AQ_VSI_SEC_FLAG_ENA_MAC_ANTI_SPOOF |
			(ICE_AQ_VSI_SEC_TX_VLAN_PRUNE_ENA <<
			 ICE_AQ_VSI_SEC_TX_PRUNE_ENA_S);
	पूर्ण अन्यथा अणु
		ctx->info.sec_flags &=
			~(ICE_AQ_VSI_SEC_FLAG_ENA_MAC_ANTI_SPOOF |
			  (ICE_AQ_VSI_SEC_TX_VLAN_PRUNE_ENA <<
			   ICE_AQ_VSI_SEC_TX_PRUNE_ENA_S));
	पूर्ण

	status = ice_update_vsi(&pf->hw, vf_vsi->idx, ctx, शून्य);
	अगर (status) अणु
		dev_err(dev, "Failed to %sable spoofchk on VF %d VSI %d\n error %s\n",
			ena ? "en" : "dis", vf->vf_id, vf_vsi->vsi_num,
			ice_stat_str(status));
		ret = -EIO;
		जाओ out;
	पूर्ण

	/* only update spoofchk state and VSI context on success */
	vf_vsi->info.sec_flags = ctx->info.sec_flags;
	vf->spoofchk = ena;

out:
	kमुक्त(ctx);
	वापस ret;
पूर्ण

/**
 * ice_is_any_vf_in_promisc - check अगर any VF(s) are in promiscuous mode
 * @pf: PF काष्ठाure क्रम accessing VF(s)
 *
 * Return false अगर no VF(s) are in unicast and/or multicast promiscuous mode,
 * अन्यथा वापस true
 */
bool ice_is_any_vf_in_promisc(काष्ठा ice_pf *pf)
अणु
	पूर्णांक vf_idx;

	ice_क्रम_each_vf(pf, vf_idx) अणु
		काष्ठा ice_vf *vf = &pf->vf[vf_idx];

		/* found a VF that has promiscuous mode configured */
		अगर (test_bit(ICE_VF_STATE_UC_PROMISC, vf->vf_states) ||
		    test_bit(ICE_VF_STATE_MC_PROMISC, vf->vf_states))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/**
 * ice_vc_cfg_promiscuous_mode_msg
 * @vf: poपूर्णांकer to the VF info
 * @msg: poपूर्णांकer to the msg buffer
 *
 * called from the VF to configure VF VSIs promiscuous mode
 */
अटल पूर्णांक ice_vc_cfg_promiscuous_mode_msg(काष्ठा ice_vf *vf, u8 *msg)
अणु
	क्रमागत virtchnl_status_code v_ret = VIRTCHNL_STATUS_SUCCESS;
	bool rm_promisc, alluni = false, allmulti = false;
	काष्ठा virtchnl_promisc_info *info =
	    (काष्ठा virtchnl_promisc_info *)msg;
	काष्ठा ice_pf *pf = vf->pf;
	काष्ठा ice_vsi *vsi;
	काष्ठा device *dev;
	पूर्णांक ret = 0;

	अगर (!test_bit(ICE_VF_STATE_ACTIVE, vf->vf_states)) अणु
		v_ret = VIRTCHNL_STATUS_ERR_PARAM;
		जाओ error_param;
	पूर्ण

	अगर (!ice_vc_isvalid_vsi_id(vf, info->vsi_id)) अणु
		v_ret = VIRTCHNL_STATUS_ERR_PARAM;
		जाओ error_param;
	पूर्ण

	vsi = ice_get_vf_vsi(vf);
	अगर (!vsi) अणु
		v_ret = VIRTCHNL_STATUS_ERR_PARAM;
		जाओ error_param;
	पूर्ण

	dev = ice_pf_to_dev(pf);
	अगर (!test_bit(ICE_VIRTCHNL_VF_CAP_PRIVILEGE, &vf->vf_caps)) अणु
		dev_err(dev, "Unprivileged VF %d is attempting to configure promiscuous mode\n",
			vf->vf_id);
		/* Leave v_ret alone, lie to the VF on purpose. */
		जाओ error_param;
	पूर्ण

	अगर (info->flags & FLAG_VF_UNICAST_PROMISC)
		alluni = true;

	अगर (info->flags & FLAG_VF_MULTICAST_PROMISC)
		allmulti = true;

	rm_promisc = !allmulti && !alluni;

	अगर (vsi->num_vlan || vf->port_vlan_info) अणु
		काष्ठा ice_vsi *pf_vsi = ice_get_मुख्य_vsi(pf);
		काष्ठा net_device *pf_netdev;

		अगर (!pf_vsi) अणु
			v_ret = VIRTCHNL_STATUS_ERR_PARAM;
			जाओ error_param;
		पूर्ण

		pf_netdev = pf_vsi->netdev;

		ret = ice_set_vf_spoofchk(pf_netdev, vf->vf_id, rm_promisc);
		अगर (ret) अणु
			dev_err(dev, "Failed to update spoofchk to %s for VF %d VSI %d when setting promiscuous mode\n",
				rm_promisc ? "ON" : "OFF", vf->vf_id,
				vsi->vsi_num);
			v_ret = VIRTCHNL_STATUS_ERR_PARAM;
		पूर्ण

		ret = ice_cfg_vlan_pruning(vsi, true, !rm_promisc);
		अगर (ret) अणु
			dev_err(dev, "Failed to configure VLAN pruning in promiscuous mode\n");
			v_ret = VIRTCHNL_STATUS_ERR_PARAM;
			जाओ error_param;
		पूर्ण
	पूर्ण

	अगर (!test_bit(ICE_FLAG_VF_TRUE_PROMISC_ENA, pf->flags)) अणु
		bool set_dflt_vsi = alluni || allmulti;

		अगर (set_dflt_vsi && !ice_is_dflt_vsi_in_use(pf->first_sw))
			/* only attempt to set the शेष क्रमwarding VSI अगर
			 * it's not currently set
			 */
			ret = ice_set_dflt_vsi(pf->first_sw, vsi);
		अन्यथा अगर (!set_dflt_vsi &&
			 ice_is_vsi_dflt_vsi(pf->first_sw, vsi))
			/* only attempt to मुक्त the शेष क्रमwarding VSI अगर we
			 * are the owner
			 */
			ret = ice_clear_dflt_vsi(pf->first_sw);

		अगर (ret) अणु
			dev_err(dev, "%sable VF %d as the default VSI failed, error %d\n",
				set_dflt_vsi ? "en" : "dis", vf->vf_id, ret);
			v_ret = VIRTCHNL_STATUS_ERR_ADMIN_QUEUE_ERROR;
			जाओ error_param;
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रमागत ice_status status;
		u8 promisc_m;

		अगर (alluni) अणु
			अगर (vf->port_vlan_info || vsi->num_vlan)
				promisc_m = ICE_UCAST_VLAN_PROMISC_BITS;
			अन्यथा
				promisc_m = ICE_UCAST_PROMISC_BITS;
		पूर्ण अन्यथा अगर (allmulti) अणु
			अगर (vf->port_vlan_info || vsi->num_vlan)
				promisc_m = ICE_MCAST_VLAN_PROMISC_BITS;
			अन्यथा
				promisc_m = ICE_MCAST_PROMISC_BITS;
		पूर्ण अन्यथा अणु
			अगर (vf->port_vlan_info || vsi->num_vlan)
				promisc_m = ICE_UCAST_VLAN_PROMISC_BITS;
			अन्यथा
				promisc_m = ICE_UCAST_PROMISC_BITS;
		पूर्ण

		/* Configure multicast/unicast with or without VLAN promiscuous
		 * mode
		 */
		status = ice_vf_set_vsi_promisc(vf, vsi, promisc_m, rm_promisc);
		अगर (status) अणु
			dev_err(dev, "%sable Tx/Rx filter promiscuous mode on VF-%d failed, error: %s\n",
				rm_promisc ? "dis" : "en", vf->vf_id,
				ice_stat_str(status));
			v_ret = ice_err_to_virt_err(status);
			जाओ error_param;
		पूर्ण अन्यथा अणु
			dev_dbg(dev, "%sable Tx/Rx filter promiscuous mode on VF-%d succeeded\n",
				rm_promisc ? "dis" : "en", vf->vf_id);
		पूर्ण
	पूर्ण

	अगर (allmulti &&
	    !test_and_set_bit(ICE_VF_STATE_MC_PROMISC, vf->vf_states))
		dev_info(dev, "VF %u successfully set multicast promiscuous mode\n", vf->vf_id);
	अन्यथा अगर (!allmulti && test_and_clear_bit(ICE_VF_STATE_MC_PROMISC, vf->vf_states))
		dev_info(dev, "VF %u successfully unset multicast promiscuous mode\n", vf->vf_id);

	अगर (alluni && !test_and_set_bit(ICE_VF_STATE_UC_PROMISC, vf->vf_states))
		dev_info(dev, "VF %u successfully set unicast promiscuous mode\n", vf->vf_id);
	अन्यथा अगर (!alluni && test_and_clear_bit(ICE_VF_STATE_UC_PROMISC, vf->vf_states))
		dev_info(dev, "VF %u successfully unset unicast promiscuous mode\n", vf->vf_id);

error_param:
	वापस ice_vc_send_msg_to_vf(vf, VIRTCHNL_OP_CONFIG_PROMISCUOUS_MODE,
				     v_ret, शून्य, 0);
पूर्ण

/**
 * ice_vc_get_stats_msg
 * @vf: poपूर्णांकer to the VF info
 * @msg: poपूर्णांकer to the msg buffer
 *
 * called from the VF to get VSI stats
 */
अटल पूर्णांक ice_vc_get_stats_msg(काष्ठा ice_vf *vf, u8 *msg)
अणु
	क्रमागत virtchnl_status_code v_ret = VIRTCHNL_STATUS_SUCCESS;
	काष्ठा virtchnl_queue_select *vqs =
		(काष्ठा virtchnl_queue_select *)msg;
	काष्ठा ice_eth_stats stats = अणु 0 पूर्ण;
	काष्ठा ice_vsi *vsi;

	अगर (!test_bit(ICE_VF_STATE_ACTIVE, vf->vf_states)) अणु
		v_ret = VIRTCHNL_STATUS_ERR_PARAM;
		जाओ error_param;
	पूर्ण

	अगर (!ice_vc_isvalid_vsi_id(vf, vqs->vsi_id)) अणु
		v_ret = VIRTCHNL_STATUS_ERR_PARAM;
		जाओ error_param;
	पूर्ण

	vsi = ice_get_vf_vsi(vf);
	अगर (!vsi) अणु
		v_ret = VIRTCHNL_STATUS_ERR_PARAM;
		जाओ error_param;
	पूर्ण

	ice_update_eth_stats(vsi);

	stats = vsi->eth_stats;

error_param:
	/* send the response to the VF */
	वापस ice_vc_send_msg_to_vf(vf, VIRTCHNL_OP_GET_STATS, v_ret,
				     (u8 *)&stats, माप(stats));
पूर्ण

/**
 * ice_vc_validate_vqs_biपंचांगaps - validate Rx/Tx queue biपंचांगaps from VIRTCHNL
 * @vqs: virtchnl_queue_select काष्ठाure containing biपंचांगaps to validate
 *
 * Return true on successful validation, अन्यथा false
 */
अटल bool ice_vc_validate_vqs_biपंचांगaps(काष्ठा virtchnl_queue_select *vqs)
अणु
	अगर ((!vqs->rx_queues && !vqs->tx_queues) ||
	    vqs->rx_queues >= BIT(ICE_MAX_RSS_QS_PER_VF) ||
	    vqs->tx_queues >= BIT(ICE_MAX_RSS_QS_PER_VF))
		वापस false;

	वापस true;
पूर्ण

/**
 * ice_vf_ena_txq_पूर्णांकerrupt - enable Tx queue पूर्णांकerrupt via QINT_TQCTL
 * @vsi: VSI of the VF to configure
 * @q_idx: VF queue index used to determine the queue in the PF's space
 */
अटल व्योम ice_vf_ena_txq_पूर्णांकerrupt(काष्ठा ice_vsi *vsi, u32 q_idx)
अणु
	काष्ठा ice_hw *hw = &vsi->back->hw;
	u32 pfq = vsi->txq_map[q_idx];
	u32 reg;

	reg = rd32(hw, QINT_TQCTL(pfq));

	/* MSI-X index 0 in the VF's space is always क्रम the OICR, which means
	 * this is most likely a poll mode VF driver, so करोn't enable an
	 * पूर्णांकerrupt that was never configured via VIRTCHNL_OP_CONFIG_IRQ_MAP
	 */
	अगर (!(reg & QINT_TQCTL_MSIX_INDX_M))
		वापस;

	wr32(hw, QINT_TQCTL(pfq), reg | QINT_TQCTL_CAUSE_ENA_M);
पूर्ण

/**
 * ice_vf_ena_rxq_पूर्णांकerrupt - enable Tx queue पूर्णांकerrupt via QINT_RQCTL
 * @vsi: VSI of the VF to configure
 * @q_idx: VF queue index used to determine the queue in the PF's space
 */
अटल व्योम ice_vf_ena_rxq_पूर्णांकerrupt(काष्ठा ice_vsi *vsi, u32 q_idx)
अणु
	काष्ठा ice_hw *hw = &vsi->back->hw;
	u32 pfq = vsi->rxq_map[q_idx];
	u32 reg;

	reg = rd32(hw, QINT_RQCTL(pfq));

	/* MSI-X index 0 in the VF's space is always क्रम the OICR, which means
	 * this is most likely a poll mode VF driver, so करोn't enable an
	 * पूर्णांकerrupt that was never configured via VIRTCHNL_OP_CONFIG_IRQ_MAP
	 */
	अगर (!(reg & QINT_RQCTL_MSIX_INDX_M))
		वापस;

	wr32(hw, QINT_RQCTL(pfq), reg | QINT_RQCTL_CAUSE_ENA_M);
पूर्ण

/**
 * ice_vc_ena_qs_msg
 * @vf: poपूर्णांकer to the VF info
 * @msg: poपूर्णांकer to the msg buffer
 *
 * called from the VF to enable all or specअगरic queue(s)
 */
अटल पूर्णांक ice_vc_ena_qs_msg(काष्ठा ice_vf *vf, u8 *msg)
अणु
	क्रमागत virtchnl_status_code v_ret = VIRTCHNL_STATUS_SUCCESS;
	काष्ठा virtchnl_queue_select *vqs =
	    (काष्ठा virtchnl_queue_select *)msg;
	काष्ठा ice_vsi *vsi;
	अचिन्हित दीर्घ q_map;
	u16 vf_q_id;

	अगर (!test_bit(ICE_VF_STATE_ACTIVE, vf->vf_states)) अणु
		v_ret = VIRTCHNL_STATUS_ERR_PARAM;
		जाओ error_param;
	पूर्ण

	अगर (!ice_vc_isvalid_vsi_id(vf, vqs->vsi_id)) अणु
		v_ret = VIRTCHNL_STATUS_ERR_PARAM;
		जाओ error_param;
	पूर्ण

	अगर (!ice_vc_validate_vqs_biपंचांगaps(vqs)) अणु
		v_ret = VIRTCHNL_STATUS_ERR_PARAM;
		जाओ error_param;
	पूर्ण

	vsi = ice_get_vf_vsi(vf);
	अगर (!vsi) अणु
		v_ret = VIRTCHNL_STATUS_ERR_PARAM;
		जाओ error_param;
	पूर्ण

	/* Enable only Rx rings, Tx rings were enabled by the FW when the
	 * Tx queue group list was configured and the context bits were
	 * programmed using ice_vsi_cfg_txqs
	 */
	q_map = vqs->rx_queues;
	क्रम_each_set_bit(vf_q_id, &q_map, ICE_MAX_RSS_QS_PER_VF) अणु
		अगर (!ice_vc_isvalid_q_id(vf, vqs->vsi_id, vf_q_id)) अणु
			v_ret = VIRTCHNL_STATUS_ERR_PARAM;
			जाओ error_param;
		पूर्ण

		/* Skip queue अगर enabled */
		अगर (test_bit(vf_q_id, vf->rxq_ena))
			जारी;

		अगर (ice_vsi_ctrl_one_rx_ring(vsi, true, vf_q_id, true)) अणु
			dev_err(ice_pf_to_dev(vsi->back), "Failed to enable Rx ring %d on VSI %d\n",
				vf_q_id, vsi->vsi_num);
			v_ret = VIRTCHNL_STATUS_ERR_PARAM;
			जाओ error_param;
		पूर्ण

		ice_vf_ena_rxq_पूर्णांकerrupt(vsi, vf_q_id);
		set_bit(vf_q_id, vf->rxq_ena);
	पूर्ण

	q_map = vqs->tx_queues;
	क्रम_each_set_bit(vf_q_id, &q_map, ICE_MAX_RSS_QS_PER_VF) अणु
		अगर (!ice_vc_isvalid_q_id(vf, vqs->vsi_id, vf_q_id)) अणु
			v_ret = VIRTCHNL_STATUS_ERR_PARAM;
			जाओ error_param;
		पूर्ण

		/* Skip queue अगर enabled */
		अगर (test_bit(vf_q_id, vf->txq_ena))
			जारी;

		ice_vf_ena_txq_पूर्णांकerrupt(vsi, vf_q_id);
		set_bit(vf_q_id, vf->txq_ena);
	पूर्ण

	/* Set flag to indicate that queues are enabled */
	अगर (v_ret == VIRTCHNL_STATUS_SUCCESS)
		set_bit(ICE_VF_STATE_QS_ENA, vf->vf_states);

error_param:
	/* send the response to the VF */
	वापस ice_vc_send_msg_to_vf(vf, VIRTCHNL_OP_ENABLE_QUEUES, v_ret,
				     शून्य, 0);
पूर्ण

/**
 * ice_vc_dis_qs_msg
 * @vf: poपूर्णांकer to the VF info
 * @msg: poपूर्णांकer to the msg buffer
 *
 * called from the VF to disable all or specअगरic
 * queue(s)
 */
अटल पूर्णांक ice_vc_dis_qs_msg(काष्ठा ice_vf *vf, u8 *msg)
अणु
	क्रमागत virtchnl_status_code v_ret = VIRTCHNL_STATUS_SUCCESS;
	काष्ठा virtchnl_queue_select *vqs =
	    (काष्ठा virtchnl_queue_select *)msg;
	काष्ठा ice_vsi *vsi;
	अचिन्हित दीर्घ q_map;
	u16 vf_q_id;

	अगर (!test_bit(ICE_VF_STATE_ACTIVE, vf->vf_states) &&
	    !test_bit(ICE_VF_STATE_QS_ENA, vf->vf_states)) अणु
		v_ret = VIRTCHNL_STATUS_ERR_PARAM;
		जाओ error_param;
	पूर्ण

	अगर (!ice_vc_isvalid_vsi_id(vf, vqs->vsi_id)) अणु
		v_ret = VIRTCHNL_STATUS_ERR_PARAM;
		जाओ error_param;
	पूर्ण

	अगर (!ice_vc_validate_vqs_biपंचांगaps(vqs)) अणु
		v_ret = VIRTCHNL_STATUS_ERR_PARAM;
		जाओ error_param;
	पूर्ण

	vsi = ice_get_vf_vsi(vf);
	अगर (!vsi) अणु
		v_ret = VIRTCHNL_STATUS_ERR_PARAM;
		जाओ error_param;
	पूर्ण

	अगर (vqs->tx_queues) अणु
		q_map = vqs->tx_queues;

		क्रम_each_set_bit(vf_q_id, &q_map, ICE_MAX_RSS_QS_PER_VF) अणु
			काष्ठा ice_ring *ring = vsi->tx_rings[vf_q_id];
			काष्ठा ice_txq_meta txq_meta = अणु 0 पूर्ण;

			अगर (!ice_vc_isvalid_q_id(vf, vqs->vsi_id, vf_q_id)) अणु
				v_ret = VIRTCHNL_STATUS_ERR_PARAM;
				जाओ error_param;
			पूर्ण

			/* Skip queue अगर not enabled */
			अगर (!test_bit(vf_q_id, vf->txq_ena))
				जारी;

			ice_fill_txq_meta(vsi, ring, &txq_meta);

			अगर (ice_vsi_stop_tx_ring(vsi, ICE_NO_RESET, vf->vf_id,
						 ring, &txq_meta)) अणु
				dev_err(ice_pf_to_dev(vsi->back), "Failed to stop Tx ring %d on VSI %d\n",
					vf_q_id, vsi->vsi_num);
				v_ret = VIRTCHNL_STATUS_ERR_PARAM;
				जाओ error_param;
			पूर्ण

			/* Clear enabled queues flag */
			clear_bit(vf_q_id, vf->txq_ena);
		पूर्ण
	पूर्ण

	q_map = vqs->rx_queues;
	/* speed up Rx queue disable by batching them अगर possible */
	अगर (q_map &&
	    biपंचांगap_equal(&q_map, vf->rxq_ena, ICE_MAX_RSS_QS_PER_VF)) अणु
		अगर (ice_vsi_stop_all_rx_rings(vsi)) अणु
			dev_err(ice_pf_to_dev(vsi->back), "Failed to stop all Rx rings on VSI %d\n",
				vsi->vsi_num);
			v_ret = VIRTCHNL_STATUS_ERR_PARAM;
			जाओ error_param;
		पूर्ण

		biपंचांगap_zero(vf->rxq_ena, ICE_MAX_RSS_QS_PER_VF);
	पूर्ण अन्यथा अगर (q_map) अणु
		क्रम_each_set_bit(vf_q_id, &q_map, ICE_MAX_RSS_QS_PER_VF) अणु
			अगर (!ice_vc_isvalid_q_id(vf, vqs->vsi_id, vf_q_id)) अणु
				v_ret = VIRTCHNL_STATUS_ERR_PARAM;
				जाओ error_param;
			पूर्ण

			/* Skip queue अगर not enabled */
			अगर (!test_bit(vf_q_id, vf->rxq_ena))
				जारी;

			अगर (ice_vsi_ctrl_one_rx_ring(vsi, false, vf_q_id,
						     true)) अणु
				dev_err(ice_pf_to_dev(vsi->back), "Failed to stop Rx ring %d on VSI %d\n",
					vf_q_id, vsi->vsi_num);
				v_ret = VIRTCHNL_STATUS_ERR_PARAM;
				जाओ error_param;
			पूर्ण

			/* Clear enabled queues flag */
			clear_bit(vf_q_id, vf->rxq_ena);
		पूर्ण
	पूर्ण

	/* Clear enabled queues flag */
	अगर (v_ret == VIRTCHNL_STATUS_SUCCESS && ice_vf_has_no_qs_ena(vf))
		clear_bit(ICE_VF_STATE_QS_ENA, vf->vf_states);

error_param:
	/* send the response to the VF */
	वापस ice_vc_send_msg_to_vf(vf, VIRTCHNL_OP_DISABLE_QUEUES, v_ret,
				     शून्य, 0);
पूर्ण

/**
 * ice_cfg_पूर्णांकerrupt
 * @vf: poपूर्णांकer to the VF info
 * @vsi: the VSI being configured
 * @vector_id: vector ID
 * @map: vector map क्रम mapping vectors to queues
 * @q_vector: काष्ठाure क्रम पूर्णांकerrupt vector
 * configure the IRQ to queue map
 */
अटल पूर्णांक
ice_cfg_पूर्णांकerrupt(काष्ठा ice_vf *vf, काष्ठा ice_vsi *vsi, u16 vector_id,
		  काष्ठा virtchnl_vector_map *map,
		  काष्ठा ice_q_vector *q_vector)
अणु
	u16 vsi_q_id, vsi_q_id_idx;
	अचिन्हित दीर्घ qmap;

	q_vector->num_ring_rx = 0;
	q_vector->num_ring_tx = 0;

	qmap = map->rxq_map;
	क्रम_each_set_bit(vsi_q_id_idx, &qmap, ICE_MAX_RSS_QS_PER_VF) अणु
		vsi_q_id = vsi_q_id_idx;

		अगर (!ice_vc_isvalid_q_id(vf, vsi->vsi_num, vsi_q_id))
			वापस VIRTCHNL_STATUS_ERR_PARAM;

		q_vector->num_ring_rx++;
		q_vector->rx.itr_idx = map->rxitr_idx;
		vsi->rx_rings[vsi_q_id]->q_vector = q_vector;
		ice_cfg_rxq_पूर्णांकerrupt(vsi, vsi_q_id, vector_id,
				      q_vector->rx.itr_idx);
	पूर्ण

	qmap = map->txq_map;
	क्रम_each_set_bit(vsi_q_id_idx, &qmap, ICE_MAX_RSS_QS_PER_VF) अणु
		vsi_q_id = vsi_q_id_idx;

		अगर (!ice_vc_isvalid_q_id(vf, vsi->vsi_num, vsi_q_id))
			वापस VIRTCHNL_STATUS_ERR_PARAM;

		q_vector->num_ring_tx++;
		q_vector->tx.itr_idx = map->txitr_idx;
		vsi->tx_rings[vsi_q_id]->q_vector = q_vector;
		ice_cfg_txq_पूर्णांकerrupt(vsi, vsi_q_id, vector_id,
				      q_vector->tx.itr_idx);
	पूर्ण

	वापस VIRTCHNL_STATUS_SUCCESS;
पूर्ण

/**
 * ice_vc_cfg_irq_map_msg
 * @vf: poपूर्णांकer to the VF info
 * @msg: poपूर्णांकer to the msg buffer
 *
 * called from the VF to configure the IRQ to queue map
 */
अटल पूर्णांक ice_vc_cfg_irq_map_msg(काष्ठा ice_vf *vf, u8 *msg)
अणु
	क्रमागत virtchnl_status_code v_ret = VIRTCHNL_STATUS_SUCCESS;
	u16 num_q_vectors_mapped, vsi_id, vector_id;
	काष्ठा virtchnl_irq_map_info *irqmap_info;
	काष्ठा virtchnl_vector_map *map;
	काष्ठा ice_pf *pf = vf->pf;
	काष्ठा ice_vsi *vsi;
	पूर्णांक i;

	irqmap_info = (काष्ठा virtchnl_irq_map_info *)msg;
	num_q_vectors_mapped = irqmap_info->num_vectors;

	/* Check to make sure number of VF vectors mapped is not greater than
	 * number of VF vectors originally allocated, and check that
	 * there is actually at least a single VF queue vector mapped
	 */
	अगर (!test_bit(ICE_VF_STATE_ACTIVE, vf->vf_states) ||
	    pf->num_msix_per_vf < num_q_vectors_mapped ||
	    !num_q_vectors_mapped) अणु
		v_ret = VIRTCHNL_STATUS_ERR_PARAM;
		जाओ error_param;
	पूर्ण

	vsi = ice_get_vf_vsi(vf);
	अगर (!vsi) अणु
		v_ret = VIRTCHNL_STATUS_ERR_PARAM;
		जाओ error_param;
	पूर्ण

	क्रम (i = 0; i < num_q_vectors_mapped; i++) अणु
		काष्ठा ice_q_vector *q_vector;

		map = &irqmap_info->vecmap[i];

		vector_id = map->vector_id;
		vsi_id = map->vsi_id;
		/* vector_id is always 0-based क्रम each VF, and can never be
		 * larger than or equal to the max allowed पूर्णांकerrupts per VF
		 */
		अगर (!(vector_id < pf->num_msix_per_vf) ||
		    !ice_vc_isvalid_vsi_id(vf, vsi_id) ||
		    (!vector_id && (map->rxq_map || map->txq_map))) अणु
			v_ret = VIRTCHNL_STATUS_ERR_PARAM;
			जाओ error_param;
		पूर्ण

		/* No need to map VF miscellaneous or rogue vector */
		अगर (!vector_id)
			जारी;

		/* Subtract non queue vector from vector_id passed by VF
		 * to get actual number of VSI queue vector array index
		 */
		q_vector = vsi->q_vectors[vector_id - ICE_NONQ_VECS_VF];
		अगर (!q_vector) अणु
			v_ret = VIRTCHNL_STATUS_ERR_PARAM;
			जाओ error_param;
		पूर्ण

		/* lookout क्रम the invalid queue index */
		v_ret = (क्रमागत virtchnl_status_code)
			ice_cfg_पूर्णांकerrupt(vf, vsi, vector_id, map, q_vector);
		अगर (v_ret)
			जाओ error_param;
	पूर्ण

error_param:
	/* send the response to the VF */
	वापस ice_vc_send_msg_to_vf(vf, VIRTCHNL_OP_CONFIG_IRQ_MAP, v_ret,
				     शून्य, 0);
पूर्ण

/**
 * ice_vc_cfg_qs_msg
 * @vf: poपूर्णांकer to the VF info
 * @msg: poपूर्णांकer to the msg buffer
 *
 * called from the VF to configure the Rx/Tx queues
 */
अटल पूर्णांक ice_vc_cfg_qs_msg(काष्ठा ice_vf *vf, u8 *msg)
अणु
	क्रमागत virtchnl_status_code v_ret = VIRTCHNL_STATUS_SUCCESS;
	काष्ठा virtchnl_vsi_queue_config_info *qci =
	    (काष्ठा virtchnl_vsi_queue_config_info *)msg;
	काष्ठा virtchnl_queue_pair_info *qpi;
	u16 num_rxq = 0, num_txq = 0;
	काष्ठा ice_pf *pf = vf->pf;
	काष्ठा ice_vsi *vsi;
	पूर्णांक i;

	अगर (!test_bit(ICE_VF_STATE_ACTIVE, vf->vf_states)) अणु
		v_ret = VIRTCHNL_STATUS_ERR_PARAM;
		जाओ error_param;
	पूर्ण

	अगर (!ice_vc_isvalid_vsi_id(vf, qci->vsi_id)) अणु
		v_ret = VIRTCHNL_STATUS_ERR_PARAM;
		जाओ error_param;
	पूर्ण

	vsi = ice_get_vf_vsi(vf);
	अगर (!vsi) अणु
		v_ret = VIRTCHNL_STATUS_ERR_PARAM;
		जाओ error_param;
	पूर्ण

	अगर (qci->num_queue_pairs > ICE_MAX_RSS_QS_PER_VF ||
	    qci->num_queue_pairs > min_t(u16, vsi->alloc_txq, vsi->alloc_rxq)) अणु
		dev_err(ice_pf_to_dev(pf), "VF-%d requesting more than supported number of queues: %d\n",
			vf->vf_id, min_t(u16, vsi->alloc_txq, vsi->alloc_rxq));
		v_ret = VIRTCHNL_STATUS_ERR_PARAM;
		जाओ error_param;
	पूर्ण

	क्रम (i = 0; i < qci->num_queue_pairs; i++) अणु
		qpi = &qci->qpair[i];
		अगर (qpi->txq.vsi_id != qci->vsi_id ||
		    qpi->rxq.vsi_id != qci->vsi_id ||
		    qpi->rxq.queue_id != qpi->txq.queue_id ||
		    qpi->txq.headwb_enabled ||
		    !ice_vc_isvalid_ring_len(qpi->txq.ring_len) ||
		    !ice_vc_isvalid_ring_len(qpi->rxq.ring_len) ||
		    !ice_vc_isvalid_q_id(vf, qci->vsi_id, qpi->txq.queue_id)) अणु
			v_ret = VIRTCHNL_STATUS_ERR_PARAM;
			जाओ error_param;
		पूर्ण
		/* copy Tx queue info from VF पूर्णांकo VSI */
		अगर (qpi->txq.ring_len > 0) अणु
			num_txq++;
			vsi->tx_rings[i]->dma = qpi->txq.dma_ring_addr;
			vsi->tx_rings[i]->count = qpi->txq.ring_len;
		पूर्ण

		/* copy Rx queue info from VF पूर्णांकo VSI */
		अगर (qpi->rxq.ring_len > 0) अणु
			u16 max_frame_size = ice_vc_get_max_frame_size(vf);

			num_rxq++;
			vsi->rx_rings[i]->dma = qpi->rxq.dma_ring_addr;
			vsi->rx_rings[i]->count = qpi->rxq.ring_len;

			अगर (qpi->rxq.databuffer_size != 0 &&
			    (qpi->rxq.databuffer_size > ((16 * 1024) - 128) ||
			     qpi->rxq.databuffer_size < 1024)) अणु
				v_ret = VIRTCHNL_STATUS_ERR_PARAM;
				जाओ error_param;
			पूर्ण
			vsi->rx_buf_len = qpi->rxq.databuffer_size;
			vsi->rx_rings[i]->rx_buf_len = vsi->rx_buf_len;
			अगर (qpi->rxq.max_pkt_size > max_frame_size ||
			    qpi->rxq.max_pkt_size < 64) अणु
				v_ret = VIRTCHNL_STATUS_ERR_PARAM;
				जाओ error_param;
			पूर्ण
		पूर्ण

		vsi->max_frame = qpi->rxq.max_pkt_size;
		/* add space क्रम the port VLAN since the VF driver is not
		 * expected to account क्रम it in the MTU calculation
		 */
		अगर (vf->port_vlan_info)
			vsi->max_frame += VLAN_HLEN;
	पूर्ण

	/* VF can request to configure less than allocated queues or शेष
	 * allocated queues. So update the VSI with new number
	 */
	vsi->num_txq = num_txq;
	vsi->num_rxq = num_rxq;
	/* All queues of VF VSI are in TC 0 */
	vsi->tc_cfg.tc_info[0].qcount_tx = num_txq;
	vsi->tc_cfg.tc_info[0].qcount_rx = num_rxq;

	अगर (ice_vsi_cfg_lan_txqs(vsi) || ice_vsi_cfg_rxqs(vsi))
		v_ret = VIRTCHNL_STATUS_ERR_ADMIN_QUEUE_ERROR;

error_param:
	/* send the response to the VF */
	वापस ice_vc_send_msg_to_vf(vf, VIRTCHNL_OP_CONFIG_VSI_QUEUES, v_ret,
				     शून्य, 0);
पूर्ण

/**
 * ice_is_vf_trusted
 * @vf: poपूर्णांकer to the VF info
 */
अटल bool ice_is_vf_trusted(काष्ठा ice_vf *vf)
अणु
	वापस test_bit(ICE_VIRTCHNL_VF_CAP_PRIVILEGE, &vf->vf_caps);
पूर्ण

/**
 * ice_can_vf_change_mac
 * @vf: poपूर्णांकer to the VF info
 *
 * Return true अगर the VF is allowed to change its MAC filters, false otherwise
 */
अटल bool ice_can_vf_change_mac(काष्ठा ice_vf *vf)
अणु
	/* If the VF MAC address has been set administratively (via the
	 * nकरो_set_vf_mac command), then deny permission to the VF to
	 * add/delete unicast MAC addresses, unless the VF is trusted
	 */
	अगर (vf->pf_set_mac && !ice_is_vf_trusted(vf))
		वापस false;

	वापस true;
पूर्ण

/**
 * ice_vc_add_mac_addr - attempt to add the MAC address passed in
 * @vf: poपूर्णांकer to the VF info
 * @vsi: poपूर्णांकer to the VF's VSI
 * @mac_addr: MAC address to add
 */
अटल पूर्णांक
ice_vc_add_mac_addr(काष्ठा ice_vf *vf, काष्ठा ice_vsi *vsi, u8 *mac_addr)
अणु
	काष्ठा device *dev = ice_pf_to_dev(vf->pf);
	क्रमागत ice_status status;

	/* शेष unicast MAC alपढ़ोy added */
	अगर (ether_addr_equal(mac_addr, vf->dflt_lan_addr.addr))
		वापस 0;

	अगर (is_unicast_ether_addr(mac_addr) && !ice_can_vf_change_mac(vf)) अणु
		dev_err(dev, "VF attempting to override administratively set MAC address, bring down and up the VF interface to resume normal operation\n");
		वापस -EPERM;
	पूर्ण

	status = ice_fltr_add_mac(vsi, mac_addr, ICE_FWD_TO_VSI);
	अगर (status == ICE_ERR_ALREADY_EXISTS) अणु
		dev_err(dev, "MAC %pM already exists for VF %d\n", mac_addr,
			vf->vf_id);
		वापस -EEXIST;
	पूर्ण अन्यथा अगर (status) अणु
		dev_err(dev, "Failed to add MAC %pM for VF %d\n, error %s\n",
			mac_addr, vf->vf_id, ice_stat_str(status));
		वापस -EIO;
	पूर्ण

	/* Set the शेष LAN address to the latest unicast MAC address added
	 * by the VF. The शेष LAN address is reported by the PF via
	 * nकरो_get_vf_config.
	 */
	अगर (is_unicast_ether_addr(mac_addr))
		ether_addr_copy(vf->dflt_lan_addr.addr, mac_addr);

	vf->num_mac++;

	वापस 0;
पूर्ण

/**
 * ice_vc_del_mac_addr - attempt to delete the MAC address passed in
 * @vf: poपूर्णांकer to the VF info
 * @vsi: poपूर्णांकer to the VF's VSI
 * @mac_addr: MAC address to delete
 */
अटल पूर्णांक
ice_vc_del_mac_addr(काष्ठा ice_vf *vf, काष्ठा ice_vsi *vsi, u8 *mac_addr)
अणु
	काष्ठा device *dev = ice_pf_to_dev(vf->pf);
	क्रमागत ice_status status;

	अगर (!ice_can_vf_change_mac(vf) &&
	    ether_addr_equal(mac_addr, vf->dflt_lan_addr.addr))
		वापस 0;

	status = ice_fltr_हटाओ_mac(vsi, mac_addr, ICE_FWD_TO_VSI);
	अगर (status == ICE_ERR_DOES_NOT_EXIST) अणु
		dev_err(dev, "MAC %pM does not exist for VF %d\n", mac_addr,
			vf->vf_id);
		वापस -ENOENT;
	पूर्ण अन्यथा अगर (status) अणु
		dev_err(dev, "Failed to delete MAC %pM for VF %d, error %s\n",
			mac_addr, vf->vf_id, ice_stat_str(status));
		वापस -EIO;
	पूर्ण

	अगर (ether_addr_equal(mac_addr, vf->dflt_lan_addr.addr))
		eth_zero_addr(vf->dflt_lan_addr.addr);

	vf->num_mac--;

	वापस 0;
पूर्ण

/**
 * ice_vc_handle_mac_addr_msg
 * @vf: poपूर्णांकer to the VF info
 * @msg: poपूर्णांकer to the msg buffer
 * @set: true अगर MAC filters are being set, false otherwise
 *
 * add guest MAC address filter
 */
अटल पूर्णांक
ice_vc_handle_mac_addr_msg(काष्ठा ice_vf *vf, u8 *msg, bool set)
अणु
	पूर्णांक (*ice_vc_cfg_mac)
		(काष्ठा ice_vf *vf, काष्ठा ice_vsi *vsi, u8 *mac_addr);
	क्रमागत virtchnl_status_code v_ret = VIRTCHNL_STATUS_SUCCESS;
	काष्ठा virtchnl_ether_addr_list *al =
	    (काष्ठा virtchnl_ether_addr_list *)msg;
	काष्ठा ice_pf *pf = vf->pf;
	क्रमागत virtchnl_ops vc_op;
	काष्ठा ice_vsi *vsi;
	पूर्णांक i;

	अगर (set) अणु
		vc_op = VIRTCHNL_OP_ADD_ETH_ADDR;
		ice_vc_cfg_mac = ice_vc_add_mac_addr;
	पूर्ण अन्यथा अणु
		vc_op = VIRTCHNL_OP_DEL_ETH_ADDR;
		ice_vc_cfg_mac = ice_vc_del_mac_addr;
	पूर्ण

	अगर (!test_bit(ICE_VF_STATE_ACTIVE, vf->vf_states) ||
	    !ice_vc_isvalid_vsi_id(vf, al->vsi_id)) अणु
		v_ret = VIRTCHNL_STATUS_ERR_PARAM;
		जाओ handle_mac_निकास;
	पूर्ण

	/* If this VF is not privileged, then we can't add more than a
	 * limited number of addresses. Check to make sure that the
	 * additions करो not push us over the limit.
	 */
	अगर (set && !ice_is_vf_trusted(vf) &&
	    (vf->num_mac + al->num_elements) > ICE_MAX_MACADDR_PER_VF) अणु
		dev_err(ice_pf_to_dev(pf), "Can't add more MAC addresses, because VF-%d is not trusted, switch the VF to trusted mode in order to add more functionalities\n",
			vf->vf_id);
		v_ret = VIRTCHNL_STATUS_ERR_PARAM;
		जाओ handle_mac_निकास;
	पूर्ण

	vsi = ice_get_vf_vsi(vf);
	अगर (!vsi) अणु
		v_ret = VIRTCHNL_STATUS_ERR_PARAM;
		जाओ handle_mac_निकास;
	पूर्ण

	क्रम (i = 0; i < al->num_elements; i++) अणु
		u8 *mac_addr = al->list[i].addr;
		पूर्णांक result;

		अगर (is_broadcast_ether_addr(mac_addr) ||
		    is_zero_ether_addr(mac_addr))
			जारी;

		result = ice_vc_cfg_mac(vf, vsi, mac_addr);
		अगर (result == -EEXIST || result == -ENOENT) अणु
			जारी;
		पूर्ण अन्यथा अगर (result) अणु
			v_ret = VIRTCHNL_STATUS_ERR_ADMIN_QUEUE_ERROR;
			जाओ handle_mac_निकास;
		पूर्ण
	पूर्ण

handle_mac_निकास:
	/* send the response to the VF */
	वापस ice_vc_send_msg_to_vf(vf, vc_op, v_ret, शून्य, 0);
पूर्ण

/**
 * ice_vc_add_mac_addr_msg
 * @vf: poपूर्णांकer to the VF info
 * @msg: poपूर्णांकer to the msg buffer
 *
 * add guest MAC address filter
 */
अटल पूर्णांक ice_vc_add_mac_addr_msg(काष्ठा ice_vf *vf, u8 *msg)
अणु
	वापस ice_vc_handle_mac_addr_msg(vf, msg, true);
पूर्ण

/**
 * ice_vc_del_mac_addr_msg
 * @vf: poपूर्णांकer to the VF info
 * @msg: poपूर्णांकer to the msg buffer
 *
 * हटाओ guest MAC address filter
 */
अटल पूर्णांक ice_vc_del_mac_addr_msg(काष्ठा ice_vf *vf, u8 *msg)
अणु
	वापस ice_vc_handle_mac_addr_msg(vf, msg, false);
पूर्ण

/**
 * ice_vc_request_qs_msg
 * @vf: poपूर्णांकer to the VF info
 * @msg: poपूर्णांकer to the msg buffer
 *
 * VFs get a शेष number of queues but can use this message to request a
 * dअगरferent number. If the request is successful, PF will reset the VF and
 * वापस 0. If unsuccessful, PF will send message inक्रमming VF of number of
 * available queue pairs via virtchnl message response to VF.
 */
अटल पूर्णांक ice_vc_request_qs_msg(काष्ठा ice_vf *vf, u8 *msg)
अणु
	क्रमागत virtchnl_status_code v_ret = VIRTCHNL_STATUS_SUCCESS;
	काष्ठा virtchnl_vf_res_request *vfres =
		(काष्ठा virtchnl_vf_res_request *)msg;
	u16 req_queues = vfres->num_queue_pairs;
	काष्ठा ice_pf *pf = vf->pf;
	u16 max_allowed_vf_queues;
	u16 tx_rx_queue_left;
	काष्ठा device *dev;
	u16 cur_queues;

	dev = ice_pf_to_dev(pf);
	अगर (!test_bit(ICE_VF_STATE_ACTIVE, vf->vf_states)) अणु
		v_ret = VIRTCHNL_STATUS_ERR_PARAM;
		जाओ error_param;
	पूर्ण

	cur_queues = vf->num_vf_qs;
	tx_rx_queue_left = min_t(u16, ice_get_avail_txq_count(pf),
				 ice_get_avail_rxq_count(pf));
	max_allowed_vf_queues = tx_rx_queue_left + cur_queues;
	अगर (!req_queues) अणु
		dev_err(dev, "VF %d tried to request 0 queues. Ignoring.\n",
			vf->vf_id);
	पूर्ण अन्यथा अगर (req_queues > ICE_MAX_RSS_QS_PER_VF) अणु
		dev_err(dev, "VF %d tried to request more than %d queues.\n",
			vf->vf_id, ICE_MAX_RSS_QS_PER_VF);
		vfres->num_queue_pairs = ICE_MAX_RSS_QS_PER_VF;
	पूर्ण अन्यथा अगर (req_queues > cur_queues &&
		   req_queues - cur_queues > tx_rx_queue_left) अणु
		dev_warn(dev, "VF %d requested %u more queues, but only %u left.\n",
			 vf->vf_id, req_queues - cur_queues, tx_rx_queue_left);
		vfres->num_queue_pairs = min_t(u16, max_allowed_vf_queues,
					       ICE_MAX_RSS_QS_PER_VF);
	पूर्ण अन्यथा अणु
		/* request is successful, then reset VF */
		vf->num_req_qs = req_queues;
		ice_vc_reset_vf(vf);
		dev_info(dev, "VF %d granted request of %u queues.\n",
			 vf->vf_id, req_queues);
		वापस 0;
	पूर्ण

error_param:
	/* send the response to the VF */
	वापस ice_vc_send_msg_to_vf(vf, VIRTCHNL_OP_REQUEST_QUEUES,
				     v_ret, (u8 *)vfres, माप(*vfres));
पूर्ण

/**
 * ice_set_vf_port_vlan
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @vf_id: VF identअगरier
 * @vlan_id: VLAN ID being set
 * @qos: priority setting
 * @vlan_proto: VLAN protocol
 *
 * program VF Port VLAN ID and/or QoS
 */
पूर्णांक
ice_set_vf_port_vlan(काष्ठा net_device *netdev, पूर्णांक vf_id, u16 vlan_id, u8 qos,
		     __be16 vlan_proto)
अणु
	काष्ठा ice_pf *pf = ice_netdev_to_pf(netdev);
	काष्ठा device *dev;
	काष्ठा ice_vf *vf;
	u16 vlanprio;
	पूर्णांक ret;

	dev = ice_pf_to_dev(pf);
	अगर (ice_validate_vf_id(pf, vf_id))
		वापस -EINVAL;

	अगर (vlan_id >= VLAN_N_VID || qos > 7) अणु
		dev_err(dev, "Invalid Port VLAN parameters for VF %d, ID %d, QoS %d\n",
			vf_id, vlan_id, qos);
		वापस -EINVAL;
	पूर्ण

	अगर (vlan_proto != htons(ETH_P_8021Q)) अणु
		dev_err(dev, "VF VLAN protocol is not supported\n");
		वापस -EPROTONOSUPPORT;
	पूर्ण

	vf = &pf->vf[vf_id];
	ret = ice_check_vf_पढ़ोy_क्रम_cfg(vf);
	अगर (ret)
		वापस ret;

	vlanprio = vlan_id | (qos << VLAN_PRIO_SHIFT);

	अगर (vf->port_vlan_info == vlanprio) अणु
		/* duplicate request, so just वापस success */
		dev_dbg(dev, "Duplicate pvid %d request\n", vlanprio);
		वापस 0;
	पूर्ण

	vf->port_vlan_info = vlanprio;

	अगर (vf->port_vlan_info)
		dev_info(dev, "Setting VLAN %d, QoS 0x%x on VF %d\n",
			 vlan_id, qos, vf_id);
	अन्यथा
		dev_info(dev, "Clearing port VLAN on VF %d\n", vf_id);

	ice_vc_reset_vf(vf);

	वापस 0;
पूर्ण

/**
 * ice_vf_vlan_offload_ena - determine अगर capabilities support VLAN offloads
 * @caps: VF driver negotiated capabilities
 *
 * Return true अगर VIRTCHNL_VF_OFFLOAD_VLAN capability is set, अन्यथा वापस false
 */
अटल bool ice_vf_vlan_offload_ena(u32 caps)
अणु
	वापस !!(caps & VIRTCHNL_VF_OFFLOAD_VLAN);
पूर्ण

/**
 * ice_vc_process_vlan_msg
 * @vf: poपूर्णांकer to the VF info
 * @msg: poपूर्णांकer to the msg buffer
 * @add_v: Add VLAN अगर true, otherwise delete VLAN
 *
 * Process virtchnl op to add or हटाओ programmed guest VLAN ID
 */
अटल पूर्णांक ice_vc_process_vlan_msg(काष्ठा ice_vf *vf, u8 *msg, bool add_v)
अणु
	क्रमागत virtchnl_status_code v_ret = VIRTCHNL_STATUS_SUCCESS;
	काष्ठा virtchnl_vlan_filter_list *vfl =
	    (काष्ठा virtchnl_vlan_filter_list *)msg;
	काष्ठा ice_pf *pf = vf->pf;
	bool vlan_promisc = false;
	काष्ठा ice_vsi *vsi;
	काष्ठा device *dev;
	काष्ठा ice_hw *hw;
	पूर्णांक status = 0;
	u8 promisc_m;
	पूर्णांक i;

	dev = ice_pf_to_dev(pf);
	अगर (!test_bit(ICE_VF_STATE_ACTIVE, vf->vf_states)) अणु
		v_ret = VIRTCHNL_STATUS_ERR_PARAM;
		जाओ error_param;
	पूर्ण

	अगर (!ice_vf_vlan_offload_ena(vf->driver_caps)) अणु
		v_ret = VIRTCHNL_STATUS_ERR_PARAM;
		जाओ error_param;
	पूर्ण

	अगर (!ice_vc_isvalid_vsi_id(vf, vfl->vsi_id)) अणु
		v_ret = VIRTCHNL_STATUS_ERR_PARAM;
		जाओ error_param;
	पूर्ण

	क्रम (i = 0; i < vfl->num_elements; i++) अणु
		अगर (vfl->vlan_id[i] >= VLAN_N_VID) अणु
			v_ret = VIRTCHNL_STATUS_ERR_PARAM;
			dev_err(dev, "invalid VF VLAN id %d\n",
				vfl->vlan_id[i]);
			जाओ error_param;
		पूर्ण
	पूर्ण

	hw = &pf->hw;
	vsi = ice_get_vf_vsi(vf);
	अगर (!vsi) अणु
		v_ret = VIRTCHNL_STATUS_ERR_PARAM;
		जाओ error_param;
	पूर्ण

	अगर (add_v && !ice_is_vf_trusted(vf) &&
	    vsi->num_vlan >= ICE_MAX_VLAN_PER_VF) अणु
		dev_info(dev, "VF-%d is not trusted, switch the VF to trusted mode, in order to add more VLAN addresses\n",
			 vf->vf_id);
		/* There is no need to let VF know about being not trusted,
		 * so we can just वापस success message here
		 */
		जाओ error_param;
	पूर्ण

	अगर (vsi->info.pvid) अणु
		v_ret = VIRTCHNL_STATUS_ERR_PARAM;
		जाओ error_param;
	पूर्ण

	अगर ((test_bit(ICE_VF_STATE_UC_PROMISC, vf->vf_states) ||
	     test_bit(ICE_VF_STATE_MC_PROMISC, vf->vf_states)) &&
	    test_bit(ICE_FLAG_VF_TRUE_PROMISC_ENA, pf->flags))
		vlan_promisc = true;

	अगर (add_v) अणु
		क्रम (i = 0; i < vfl->num_elements; i++) अणु
			u16 vid = vfl->vlan_id[i];

			अगर (!ice_is_vf_trusted(vf) &&
			    vsi->num_vlan >= ICE_MAX_VLAN_PER_VF) अणु
				dev_info(dev, "VF-%d is not trusted, switch the VF to trusted mode, in order to add more VLAN addresses\n",
					 vf->vf_id);
				/* There is no need to let VF know about being
				 * not trusted, so we can just वापस success
				 * message here as well.
				 */
				जाओ error_param;
			पूर्ण

			/* we add VLAN 0 by शेष क्रम each VF so we can enable
			 * Tx VLAN anti-spoof without triggering MDD events so
			 * we करोn't need to add it again here
			 */
			अगर (!vid)
				जारी;

			status = ice_vsi_add_vlan(vsi, vid, ICE_FWD_TO_VSI);
			अगर (status) अणु
				v_ret = VIRTCHNL_STATUS_ERR_PARAM;
				जाओ error_param;
			पूर्ण

			/* Enable VLAN pruning when non-zero VLAN is added */
			अगर (!vlan_promisc && vid &&
			    !ice_vsi_is_vlan_pruning_ena(vsi)) अणु
				status = ice_cfg_vlan_pruning(vsi, true, false);
				अगर (status) अणु
					v_ret = VIRTCHNL_STATUS_ERR_PARAM;
					dev_err(dev, "Enable VLAN pruning on VLAN ID: %d failed error-%d\n",
						vid, status);
					जाओ error_param;
				पूर्ण
			पूर्ण अन्यथा अगर (vlan_promisc) अणु
				/* Enable Ucast/Mcast VLAN promiscuous mode */
				promisc_m = ICE_PROMISC_VLAN_TX |
					    ICE_PROMISC_VLAN_RX;

				status = ice_set_vsi_promisc(hw, vsi->idx,
							     promisc_m, vid);
				अगर (status) अणु
					v_ret = VIRTCHNL_STATUS_ERR_PARAM;
					dev_err(dev, "Enable Unicast/multicast promiscuous mode on VLAN ID:%d failed error-%d\n",
						vid, status);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* In हाल of non_trusted VF, number of VLAN elements passed
		 * to PF क्रम removal might be greater than number of VLANs
		 * filter programmed क्रम that VF - So, use actual number of
		 * VLANS added earlier with add VLAN opcode. In order to aव्योम
		 * removing VLAN that करोesn't exist, which result to sending
		 * erroneous failed message back to the VF
		 */
		पूर्णांक num_vf_vlan;

		num_vf_vlan = vsi->num_vlan;
		क्रम (i = 0; i < vfl->num_elements && i < num_vf_vlan; i++) अणु
			u16 vid = vfl->vlan_id[i];

			/* we add VLAN 0 by शेष क्रम each VF so we can enable
			 * Tx VLAN anti-spoof without triggering MDD events so
			 * we करोn't want a VIRTCHNL request to हटाओ it
			 */
			अगर (!vid)
				जारी;

			/* Make sure ice_vsi_समाप्त_vlan is successful beक्रमe
			 * updating VLAN inक्रमmation
			 */
			status = ice_vsi_समाप्त_vlan(vsi, vid);
			अगर (status) अणु
				v_ret = VIRTCHNL_STATUS_ERR_PARAM;
				जाओ error_param;
			पूर्ण

			/* Disable VLAN pruning when only VLAN 0 is left */
			अगर (vsi->num_vlan == 1 &&
			    ice_vsi_is_vlan_pruning_ena(vsi))
				ice_cfg_vlan_pruning(vsi, false, false);

			/* Disable Unicast/Multicast VLAN promiscuous mode */
			अगर (vlan_promisc) अणु
				promisc_m = ICE_PROMISC_VLAN_TX |
					    ICE_PROMISC_VLAN_RX;

				ice_clear_vsi_promisc(hw, vsi->idx,
						      promisc_m, vid);
			पूर्ण
		पूर्ण
	पूर्ण

error_param:
	/* send the response to the VF */
	अगर (add_v)
		वापस ice_vc_send_msg_to_vf(vf, VIRTCHNL_OP_ADD_VLAN, v_ret,
					     शून्य, 0);
	अन्यथा
		वापस ice_vc_send_msg_to_vf(vf, VIRTCHNL_OP_DEL_VLAN, v_ret,
					     शून्य, 0);
पूर्ण

/**
 * ice_vc_add_vlan_msg
 * @vf: poपूर्णांकer to the VF info
 * @msg: poपूर्णांकer to the msg buffer
 *
 * Add and program guest VLAN ID
 */
अटल पूर्णांक ice_vc_add_vlan_msg(काष्ठा ice_vf *vf, u8 *msg)
अणु
	वापस ice_vc_process_vlan_msg(vf, msg, true);
पूर्ण

/**
 * ice_vc_हटाओ_vlan_msg
 * @vf: poपूर्णांकer to the VF info
 * @msg: poपूर्णांकer to the msg buffer
 *
 * हटाओ programmed guest VLAN ID
 */
अटल पूर्णांक ice_vc_हटाओ_vlan_msg(काष्ठा ice_vf *vf, u8 *msg)
अणु
	वापस ice_vc_process_vlan_msg(vf, msg, false);
पूर्ण

/**
 * ice_vc_ena_vlan_stripping
 * @vf: poपूर्णांकer to the VF info
 *
 * Enable VLAN header stripping क्रम a given VF
 */
अटल पूर्णांक ice_vc_ena_vlan_stripping(काष्ठा ice_vf *vf)
अणु
	क्रमागत virtchnl_status_code v_ret = VIRTCHNL_STATUS_SUCCESS;
	काष्ठा ice_vsi *vsi;

	अगर (!test_bit(ICE_VF_STATE_ACTIVE, vf->vf_states)) अणु
		v_ret = VIRTCHNL_STATUS_ERR_PARAM;
		जाओ error_param;
	पूर्ण

	अगर (!ice_vf_vlan_offload_ena(vf->driver_caps)) अणु
		v_ret = VIRTCHNL_STATUS_ERR_PARAM;
		जाओ error_param;
	पूर्ण

	vsi = ice_get_vf_vsi(vf);
	अगर (ice_vsi_manage_vlan_stripping(vsi, true))
		v_ret = VIRTCHNL_STATUS_ERR_PARAM;

error_param:
	वापस ice_vc_send_msg_to_vf(vf, VIRTCHNL_OP_ENABLE_VLAN_STRIPPING,
				     v_ret, शून्य, 0);
पूर्ण

/**
 * ice_vc_dis_vlan_stripping
 * @vf: poपूर्णांकer to the VF info
 *
 * Disable VLAN header stripping क्रम a given VF
 */
अटल पूर्णांक ice_vc_dis_vlan_stripping(काष्ठा ice_vf *vf)
अणु
	क्रमागत virtchnl_status_code v_ret = VIRTCHNL_STATUS_SUCCESS;
	काष्ठा ice_vsi *vsi;

	अगर (!test_bit(ICE_VF_STATE_ACTIVE, vf->vf_states)) अणु
		v_ret = VIRTCHNL_STATUS_ERR_PARAM;
		जाओ error_param;
	पूर्ण

	अगर (!ice_vf_vlan_offload_ena(vf->driver_caps)) अणु
		v_ret = VIRTCHNL_STATUS_ERR_PARAM;
		जाओ error_param;
	पूर्ण

	vsi = ice_get_vf_vsi(vf);
	अगर (!vsi) अणु
		v_ret = VIRTCHNL_STATUS_ERR_PARAM;
		जाओ error_param;
	पूर्ण

	अगर (ice_vsi_manage_vlan_stripping(vsi, false))
		v_ret = VIRTCHNL_STATUS_ERR_PARAM;

error_param:
	वापस ice_vc_send_msg_to_vf(vf, VIRTCHNL_OP_DISABLE_VLAN_STRIPPING,
				     v_ret, शून्य, 0);
पूर्ण

/**
 * ice_vf_init_vlan_stripping - enable/disable VLAN stripping on initialization
 * @vf: VF to enable/disable VLAN stripping क्रम on initialization
 *
 * If the VIRTCHNL_VF_OFFLOAD_VLAN flag is set enable VLAN stripping, अन्यथा अगर
 * the flag is cleared then we want to disable stripping. For example, the flag
 * will be cleared when port VLANs are configured by the administrator beक्रमe
 * passing the VF to the guest or अगर the AVF driver करोesn't support VLAN
 * offloads.
 */
अटल पूर्णांक ice_vf_init_vlan_stripping(काष्ठा ice_vf *vf)
अणु
	काष्ठा ice_vsi *vsi = ice_get_vf_vsi(vf);

	अगर (!vsi)
		वापस -EINVAL;

	/* करोn't modअगरy stripping अगर port VLAN is configured */
	अगर (vsi->info.pvid)
		वापस 0;

	अगर (ice_vf_vlan_offload_ena(vf->driver_caps))
		वापस ice_vsi_manage_vlan_stripping(vsi, true);
	अन्यथा
		वापस ice_vsi_manage_vlan_stripping(vsi, false);
पूर्ण

/**
 * ice_vc_process_vf_msg - Process request from VF
 * @pf: poपूर्णांकer to the PF काष्ठाure
 * @event: poपूर्णांकer to the AQ event
 *
 * called from the common asq/arq handler to
 * process request from VF
 */
व्योम ice_vc_process_vf_msg(काष्ठा ice_pf *pf, काष्ठा ice_rq_event_info *event)
अणु
	u32 v_opcode = le32_to_cpu(event->desc.cookie_high);
	s16 vf_id = le16_to_cpu(event->desc.retval);
	u16 msglen = event->msg_len;
	u8 *msg = event->msg_buf;
	काष्ठा ice_vf *vf = शून्य;
	काष्ठा device *dev;
	पूर्णांक err = 0;

	dev = ice_pf_to_dev(pf);
	अगर (ice_validate_vf_id(pf, vf_id)) अणु
		err = -EINVAL;
		जाओ error_handler;
	पूर्ण

	vf = &pf->vf[vf_id];

	/* Check अगर VF is disabled. */
	अगर (test_bit(ICE_VF_STATE_DIS, vf->vf_states)) अणु
		err = -EPERM;
		जाओ error_handler;
	पूर्ण

	/* Perक्रमm basic checks on the msg */
	err = virtchnl_vc_validate_vf_msg(&vf->vf_ver, v_opcode, msg, msglen);
	अगर (err) अणु
		अगर (err == VIRTCHNL_STATUS_ERR_PARAM)
			err = -EPERM;
		अन्यथा
			err = -EINVAL;
	पूर्ण

	अगर (!ice_vc_is_opcode_allowed(vf, v_opcode)) अणु
		ice_vc_send_msg_to_vf(vf, v_opcode,
				      VIRTCHNL_STATUS_ERR_NOT_SUPPORTED, शून्य,
				      0);
		वापस;
	पूर्ण

error_handler:
	अगर (err) अणु
		ice_vc_send_msg_to_vf(vf, v_opcode, VIRTCHNL_STATUS_ERR_PARAM,
				      शून्य, 0);
		dev_err(dev, "Invalid message from VF %d, opcode %d, len %d, error %d\n",
			vf_id, v_opcode, msglen, err);
		वापस;
	पूर्ण

	चयन (v_opcode) अणु
	हाल VIRTCHNL_OP_VERSION:
		err = ice_vc_get_ver_msg(vf, msg);
		अवरोध;
	हाल VIRTCHNL_OP_GET_VF_RESOURCES:
		err = ice_vc_get_vf_res_msg(vf, msg);
		अगर (ice_vf_init_vlan_stripping(vf))
			dev_err(dev, "Failed to initialize VLAN stripping for VF %d\n",
				vf->vf_id);
		ice_vc_notअगरy_vf_link_state(vf);
		अवरोध;
	हाल VIRTCHNL_OP_RESET_VF:
		ice_vc_reset_vf_msg(vf);
		अवरोध;
	हाल VIRTCHNL_OP_ADD_ETH_ADDR:
		err = ice_vc_add_mac_addr_msg(vf, msg);
		अवरोध;
	हाल VIRTCHNL_OP_DEL_ETH_ADDR:
		err = ice_vc_del_mac_addr_msg(vf, msg);
		अवरोध;
	हाल VIRTCHNL_OP_CONFIG_VSI_QUEUES:
		err = ice_vc_cfg_qs_msg(vf, msg);
		अवरोध;
	हाल VIRTCHNL_OP_ENABLE_QUEUES:
		err = ice_vc_ena_qs_msg(vf, msg);
		ice_vc_notअगरy_vf_link_state(vf);
		अवरोध;
	हाल VIRTCHNL_OP_DISABLE_QUEUES:
		err = ice_vc_dis_qs_msg(vf, msg);
		अवरोध;
	हाल VIRTCHNL_OP_REQUEST_QUEUES:
		err = ice_vc_request_qs_msg(vf, msg);
		अवरोध;
	हाल VIRTCHNL_OP_CONFIG_IRQ_MAP:
		err = ice_vc_cfg_irq_map_msg(vf, msg);
		अवरोध;
	हाल VIRTCHNL_OP_CONFIG_RSS_KEY:
		err = ice_vc_config_rss_key(vf, msg);
		अवरोध;
	हाल VIRTCHNL_OP_CONFIG_RSS_LUT:
		err = ice_vc_config_rss_lut(vf, msg);
		अवरोध;
	हाल VIRTCHNL_OP_GET_STATS:
		err = ice_vc_get_stats_msg(vf, msg);
		अवरोध;
	हाल VIRTCHNL_OP_CONFIG_PROMISCUOUS_MODE:
		err = ice_vc_cfg_promiscuous_mode_msg(vf, msg);
		अवरोध;
	हाल VIRTCHNL_OP_ADD_VLAN:
		err = ice_vc_add_vlan_msg(vf, msg);
		अवरोध;
	हाल VIRTCHNL_OP_DEL_VLAN:
		err = ice_vc_हटाओ_vlan_msg(vf, msg);
		अवरोध;
	हाल VIRTCHNL_OP_ENABLE_VLAN_STRIPPING:
		err = ice_vc_ena_vlan_stripping(vf);
		अवरोध;
	हाल VIRTCHNL_OP_DISABLE_VLAN_STRIPPING:
		err = ice_vc_dis_vlan_stripping(vf);
		अवरोध;
	हाल VIRTCHNL_OP_ADD_Fसूची_FILTER:
		err = ice_vc_add_fdir_fltr(vf, msg);
		अवरोध;
	हाल VIRTCHNL_OP_DEL_Fसूची_FILTER:
		err = ice_vc_del_fdir_fltr(vf, msg);
		अवरोध;
	हाल VIRTCHNL_OP_ADD_RSS_CFG:
		err = ice_vc_handle_rss_cfg(vf, msg, true);
		अवरोध;
	हाल VIRTCHNL_OP_DEL_RSS_CFG:
		err = ice_vc_handle_rss_cfg(vf, msg, false);
		अवरोध;
	हाल VIRTCHNL_OP_UNKNOWN:
	शेष:
		dev_err(dev, "Unsupported opcode %d from VF %d\n", v_opcode,
			vf_id);
		err = ice_vc_send_msg_to_vf(vf, v_opcode,
					    VIRTCHNL_STATUS_ERR_NOT_SUPPORTED,
					    शून्य, 0);
		अवरोध;
	पूर्ण
	अगर (err) अणु
		/* Helper function cares less about error वापस values here
		 * as it is busy with pending work.
		 */
		dev_info(dev, "PF failed to honor VF %d, opcode %d, error %d\n",
			 vf_id, v_opcode, err);
	पूर्ण
पूर्ण

/**
 * ice_get_vf_cfg
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @vf_id: VF identअगरier
 * @ivi: VF configuration काष्ठाure
 *
 * वापस VF configuration
 */
पूर्णांक
ice_get_vf_cfg(काष्ठा net_device *netdev, पूर्णांक vf_id, काष्ठा अगरla_vf_info *ivi)
अणु
	काष्ठा ice_pf *pf = ice_netdev_to_pf(netdev);
	काष्ठा ice_vf *vf;

	अगर (ice_validate_vf_id(pf, vf_id))
		वापस -EINVAL;

	vf = &pf->vf[vf_id];

	अगर (ice_check_vf_init(pf, vf))
		वापस -EBUSY;

	ivi->vf = vf_id;
	ether_addr_copy(ivi->mac, vf->dflt_lan_addr.addr);

	/* VF configuration क्रम VLAN and applicable QoS */
	ivi->vlan = vf->port_vlan_info & VLAN_VID_MASK;
	ivi->qos = (vf->port_vlan_info & VLAN_PRIO_MASK) >> VLAN_PRIO_SHIFT;

	ivi->trusted = vf->trusted;
	ivi->spoofchk = vf->spoofchk;
	अगर (!vf->link_क्रमced)
		ivi->linkstate = IFLA_VF_LINK_STATE_AUTO;
	अन्यथा अगर (vf->link_up)
		ivi->linkstate = IFLA_VF_LINK_STATE_ENABLE;
	अन्यथा
		ivi->linkstate = IFLA_VF_LINK_STATE_DISABLE;
	ivi->max_tx_rate = vf->tx_rate;
	ivi->min_tx_rate = 0;
	वापस 0;
पूर्ण

/**
 * ice_unicast_mac_exists - check अगर the unicast MAC exists on the PF's चयन
 * @pf: PF used to reference the चयन's rules
 * @umac: unicast MAC to compare against existing चयन rules
 *
 * Return true on the first/any match, अन्यथा वापस false
 */
अटल bool ice_unicast_mac_exists(काष्ठा ice_pf *pf, u8 *umac)
अणु
	काष्ठा ice_sw_recipe *mac_recipe_list =
		&pf->hw.चयन_info->recp_list[ICE_SW_LKUP_MAC];
	काष्ठा ice_fltr_mgmt_list_entry *list_itr;
	काष्ठा list_head *rule_head;
	काष्ठा mutex *rule_lock; /* protect MAC filter list access */

	rule_head = &mac_recipe_list->filt_rules;
	rule_lock = &mac_recipe_list->filt_rule_lock;

	mutex_lock(rule_lock);
	list_क्रम_each_entry(list_itr, rule_head, list_entry) अणु
		u8 *existing_mac = &list_itr->fltr_info.l_data.mac.mac_addr[0];

		अगर (ether_addr_equal(existing_mac, umac)) अणु
			mutex_unlock(rule_lock);
			वापस true;
		पूर्ण
	पूर्ण

	mutex_unlock(rule_lock);

	वापस false;
पूर्ण

/**
 * ice_set_vf_mac
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @vf_id: VF identअगरier
 * @mac: MAC address
 *
 * program VF MAC address
 */
पूर्णांक ice_set_vf_mac(काष्ठा net_device *netdev, पूर्णांक vf_id, u8 *mac)
अणु
	काष्ठा ice_pf *pf = ice_netdev_to_pf(netdev);
	काष्ठा ice_vf *vf;
	पूर्णांक ret;

	अगर (ice_validate_vf_id(pf, vf_id))
		वापस -EINVAL;

	अगर (is_multicast_ether_addr(mac)) अणु
		netdev_err(netdev, "%pM not a valid unicast address\n", mac);
		वापस -EINVAL;
	पूर्ण

	vf = &pf->vf[vf_id];
	/* nothing left to करो, unicast MAC alपढ़ोy set */
	अगर (ether_addr_equal(vf->dflt_lan_addr.addr, mac))
		वापस 0;

	ret = ice_check_vf_पढ़ोy_क्रम_cfg(vf);
	अगर (ret)
		वापस ret;

	अगर (ice_unicast_mac_exists(pf, mac)) अणु
		netdev_err(netdev, "Unicast MAC %pM already exists on this PF. Preventing setting VF %u unicast MAC address to %pM\n",
			   mac, vf_id, mac);
		वापस -EINVAL;
	पूर्ण

	/* VF is notअगरied of its new MAC via the PF's response to the
	 * VIRTCHNL_OP_GET_VF_RESOURCES message after the VF has been reset
	 */
	ether_addr_copy(vf->dflt_lan_addr.addr, mac);
	अगर (is_zero_ether_addr(mac)) अणु
		/* VF will send VIRTCHNL_OP_ADD_ETH_ADDR message with its MAC */
		vf->pf_set_mac = false;
		netdev_info(netdev, "Removing MAC on VF %d. VF driver will be reinitialized\n",
			    vf->vf_id);
	पूर्ण अन्यथा अणु
		/* PF will add MAC rule क्रम the VF */
		vf->pf_set_mac = true;
		netdev_info(netdev, "Setting MAC %pM on VF %d. VF driver will be reinitialized\n",
			    mac, vf_id);
	पूर्ण

	ice_vc_reset_vf(vf);
	वापस 0;
पूर्ण

/**
 * ice_set_vf_trust
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @vf_id: VF identअगरier
 * @trusted: Boolean value to enable/disable trusted VF
 *
 * Enable or disable a given VF as trusted
 */
पूर्णांक ice_set_vf_trust(काष्ठा net_device *netdev, पूर्णांक vf_id, bool trusted)
अणु
	काष्ठा ice_pf *pf = ice_netdev_to_pf(netdev);
	काष्ठा ice_vf *vf;
	पूर्णांक ret;

	अगर (ice_validate_vf_id(pf, vf_id))
		वापस -EINVAL;

	vf = &pf->vf[vf_id];
	ret = ice_check_vf_पढ़ोy_क्रम_cfg(vf);
	अगर (ret)
		वापस ret;

	/* Check अगर alपढ़ोy trusted */
	अगर (trusted == vf->trusted)
		वापस 0;

	vf->trusted = trusted;
	ice_vc_reset_vf(vf);
	dev_info(ice_pf_to_dev(pf), "VF %u is now %strusted\n",
		 vf_id, trusted ? "" : "un");

	वापस 0;
पूर्ण

/**
 * ice_set_vf_link_state
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @vf_id: VF identअगरier
 * @link_state: required link state
 *
 * Set VF's link state, irrespective of physical link state status
 */
पूर्णांक ice_set_vf_link_state(काष्ठा net_device *netdev, पूर्णांक vf_id, पूर्णांक link_state)
अणु
	काष्ठा ice_pf *pf = ice_netdev_to_pf(netdev);
	काष्ठा ice_vf *vf;
	पूर्णांक ret;

	अगर (ice_validate_vf_id(pf, vf_id))
		वापस -EINVAL;

	vf = &pf->vf[vf_id];
	ret = ice_check_vf_पढ़ोy_क्रम_cfg(vf);
	अगर (ret)
		वापस ret;

	चयन (link_state) अणु
	हाल IFLA_VF_LINK_STATE_AUTO:
		vf->link_क्रमced = false;
		अवरोध;
	हाल IFLA_VF_LINK_STATE_ENABLE:
		vf->link_क्रमced = true;
		vf->link_up = true;
		अवरोध;
	हाल IFLA_VF_LINK_STATE_DISABLE:
		vf->link_क्रमced = true;
		vf->link_up = false;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ice_vc_notअगरy_vf_link_state(vf);

	वापस 0;
पूर्ण

/**
 * ice_get_vf_stats - populate some stats क्रम the VF
 * @netdev: the netdev of the PF
 * @vf_id: the host OS identअगरier (0-255)
 * @vf_stats: poपूर्णांकer to the OS memory to be initialized
 */
पूर्णांक ice_get_vf_stats(काष्ठा net_device *netdev, पूर्णांक vf_id,
		     काष्ठा अगरla_vf_stats *vf_stats)
अणु
	काष्ठा ice_pf *pf = ice_netdev_to_pf(netdev);
	काष्ठा ice_eth_stats *stats;
	काष्ठा ice_vsi *vsi;
	काष्ठा ice_vf *vf;
	पूर्णांक ret;

	अगर (ice_validate_vf_id(pf, vf_id))
		वापस -EINVAL;

	vf = &pf->vf[vf_id];
	ret = ice_check_vf_पढ़ोy_क्रम_cfg(vf);
	अगर (ret)
		वापस ret;

	vsi = ice_get_vf_vsi(vf);
	अगर (!vsi)
		वापस -EINVAL;

	ice_update_eth_stats(vsi);
	stats = &vsi->eth_stats;

	स_रखो(vf_stats, 0, माप(*vf_stats));

	vf_stats->rx_packets = stats->rx_unicast + stats->rx_broadcast +
		stats->rx_multicast;
	vf_stats->tx_packets = stats->tx_unicast + stats->tx_broadcast +
		stats->tx_multicast;
	vf_stats->rx_bytes   = stats->rx_bytes;
	vf_stats->tx_bytes   = stats->tx_bytes;
	vf_stats->broadcast  = stats->rx_broadcast;
	vf_stats->multicast  = stats->rx_multicast;
	vf_stats->rx_dropped = stats->rx_discards;
	vf_stats->tx_dropped = stats->tx_discards;

	वापस 0;
पूर्ण

/**
 * ice_prपूर्णांक_vf_rx_mdd_event - prपूर्णांक VF Rx malicious driver detect event
 * @vf: poपूर्णांकer to the VF काष्ठाure
 */
व्योम ice_prपूर्णांक_vf_rx_mdd_event(काष्ठा ice_vf *vf)
अणु
	काष्ठा ice_pf *pf = vf->pf;
	काष्ठा device *dev;

	dev = ice_pf_to_dev(pf);

	dev_info(dev, "%d Rx Malicious Driver Detection events detected on PF %d VF %d MAC %pM. mdd-auto-reset-vfs=%s\n",
		 vf->mdd_rx_events.count, pf->hw.pf_id, vf->vf_id,
		 vf->dflt_lan_addr.addr,
		 test_bit(ICE_FLAG_MDD_AUTO_RESET_VF, pf->flags)
			  ? "on" : "off");
पूर्ण

/**
 * ice_prपूर्णांक_vfs_mdd_events - prपूर्णांक VFs malicious driver detect event
 * @pf: poपूर्णांकer to the PF काष्ठाure
 *
 * Called from ice_handle_mdd_event to rate limit and prपूर्णांक VFs MDD events.
 */
व्योम ice_prपूर्णांक_vfs_mdd_events(काष्ठा ice_pf *pf)
अणु
	काष्ठा device *dev = ice_pf_to_dev(pf);
	काष्ठा ice_hw *hw = &pf->hw;
	पूर्णांक i;

	/* check that there are pending MDD events to prपूर्णांक */
	अगर (!test_and_clear_bit(ICE_MDD_VF_PRINT_PENDING, pf->state))
		वापस;

	/* VF MDD event logs are rate limited to one second पूर्णांकervals */
	अगर (समय_is_after_jअगरfies(pf->last_prपूर्णांकed_mdd_jअगरfies + HZ * 1))
		वापस;

	pf->last_prपूर्णांकed_mdd_jअगरfies = jअगरfies;

	ice_क्रम_each_vf(pf, i) अणु
		काष्ठा ice_vf *vf = &pf->vf[i];

		/* only prपूर्णांक Rx MDD event message अगर there are new events */
		अगर (vf->mdd_rx_events.count != vf->mdd_rx_events.last_prपूर्णांकed) अणु
			vf->mdd_rx_events.last_prपूर्णांकed =
							vf->mdd_rx_events.count;
			ice_prपूर्णांक_vf_rx_mdd_event(vf);
		पूर्ण

		/* only prपूर्णांक Tx MDD event message अगर there are new events */
		अगर (vf->mdd_tx_events.count != vf->mdd_tx_events.last_prपूर्णांकed) अणु
			vf->mdd_tx_events.last_prपूर्णांकed =
							vf->mdd_tx_events.count;

			dev_info(dev, "%d Tx Malicious Driver Detection events detected on PF %d VF %d MAC %pM.\n",
				 vf->mdd_tx_events.count, hw->pf_id, i,
				 vf->dflt_lan_addr.addr);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * ice_restore_all_vfs_msi_state - restore VF MSI state after PF FLR
 * @pdev: poपूर्णांकer to a pci_dev काष्ठाure
 *
 * Called when recovering from a PF FLR to restore पूर्णांकerrupt capability to
 * the VFs.
 */
व्योम ice_restore_all_vfs_msi_state(काष्ठा pci_dev *pdev)
अणु
	u16 vf_id;
	पूर्णांक pos;

	अगर (!pci_num_vf(pdev))
		वापस;

	pos = pci_find_ext_capability(pdev, PCI_EXT_CAP_ID_SRIOV);
	अगर (pos) अणु
		काष्ठा pci_dev *vfdev;

		pci_पढ़ो_config_word(pdev, pos + PCI_SRIOV_VF_DID,
				     &vf_id);
		vfdev = pci_get_device(pdev->venकरोr, vf_id, शून्य);
		जबतक (vfdev) अणु
			अगर (vfdev->is_virtfn && vfdev->physfn == pdev)
				pci_restore_msi_state(vfdev);
			vfdev = pci_get_device(pdev->venकरोr, vf_id,
					       vfdev);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * ice_is_malicious_vf - helper function to detect a malicious VF
 * @pf: ptr to काष्ठा ice_pf
 * @event: poपूर्णांकer to the AQ event
 * @num_msg_proc: the number of messages processed so far
 * @num_msg_pending: the number of messages peinding in admin queue
 */
bool
ice_is_malicious_vf(काष्ठा ice_pf *pf, काष्ठा ice_rq_event_info *event,
		    u16 num_msg_proc, u16 num_msg_pending)
अणु
	s16 vf_id = le16_to_cpu(event->desc.retval);
	काष्ठा device *dev = ice_pf_to_dev(pf);
	काष्ठा ice_mbx_data mbxdata;
	क्रमागत ice_status status;
	bool malvf = false;
	काष्ठा ice_vf *vf;

	अगर (ice_validate_vf_id(pf, vf_id))
		वापस false;

	vf = &pf->vf[vf_id];
	/* Check अगर VF is disabled. */
	अगर (test_bit(ICE_VF_STATE_DIS, vf->vf_states))
		वापस false;

	mbxdata.num_msg_proc = num_msg_proc;
	mbxdata.num_pending_arq = num_msg_pending;
	mbxdata.max_num_msgs_mbx = pf->hw.mailboxq.num_rq_entries;
#घोषणा ICE_MBX_OVERFLOW_WATERMARK 64
	mbxdata.async_watermark_val = ICE_MBX_OVERFLOW_WATERMARK;

	/* check to see अगर we have a malicious VF */
	status = ice_mbx_vf_state_handler(&pf->hw, &mbxdata, vf_id, &malvf);
	अगर (status)
		वापस false;

	अगर (malvf) अणु
		bool report_vf = false;

		/* अगर the VF is malicious and we haven't let the user
		 * know about it, then let them know now
		 */
		status = ice_mbx_report_malvf(&pf->hw, pf->malvfs,
					      ICE_MAX_VF_COUNT, vf_id,
					      &report_vf);
		अगर (status)
			dev_dbg(dev, "Error reporting malicious VF\n");

		अगर (report_vf) अणु
			काष्ठा ice_vsi *pf_vsi = ice_get_मुख्य_vsi(pf);

			अगर (pf_vsi)
				dev_warn(dev, "VF MAC %pM on PF MAC %pM is generating asynchronous messages and may be overflowing the PF message queue. Please see the Adapter User Guide for more information\n",
					 &vf->dflt_lan_addr.addr[0],
					 pf_vsi->netdev->dev_addr);
		पूर्ण

		वापस true;
	पूर्ण

	/* अगर there was an error in detection or the VF is not malicious then
	 * वापस false
	 */
	वापस false;
पूर्ण
