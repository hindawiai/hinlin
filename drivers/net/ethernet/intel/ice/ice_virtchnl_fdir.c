<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (C) 2021, Intel Corporation. */

#समावेश "ice.h"
#समावेश "ice_base.h"
#समावेश "ice_lib.h"
#समावेश "ice_flow.h"

#घोषणा to_fltr_conf_from_desc(p) \
	container_of(p, काष्ठा virtchnl_fdir_fltr_conf, input)

#घोषणा ICE_FLOW_PROF_TYPE_S	0
#घोषणा ICE_FLOW_PROF_TYPE_M	(0xFFFFFFFFULL << ICE_FLOW_PROF_TYPE_S)
#घोषणा ICE_FLOW_PROF_VSI_S	32
#घोषणा ICE_FLOW_PROF_VSI_M	(0xFFFFFFFFULL << ICE_FLOW_PROF_VSI_S)

/* Flow profile ID क्रमmat:
 * [0:31] - flow type, flow + tun_offs
 * [32:63] - VSI index
 */
#घोषणा ICE_FLOW_PROF_FD(vsi, flow, tun_offs) \
	((u64)(((((flow) + (tun_offs)) & ICE_FLOW_PROF_TYPE_M)) | \
	      (((u64)(vsi) << ICE_FLOW_PROF_VSI_S) & ICE_FLOW_PROF_VSI_M)))

#घोषणा GTPU_TEID_OFFSET 4
#घोषणा GTPU_EH_QFI_OFFSET 1
#घोषणा GTPU_EH_QFI_MASK 0x3F
#घोषणा PFCP_S_OFFSET 0
#घोषणा PFCP_S_MASK 0x1
#घोषणा PFCP_PORT_NR 8805

#घोषणा Fसूची_INSET_FLAG_ESP_S 0
#घोषणा Fसूची_INSET_FLAG_ESP_M BIT_ULL(Fसूची_INSET_FLAG_ESP_S)
#घोषणा Fसूची_INSET_FLAG_ESP_UDP BIT_ULL(Fसूची_INSET_FLAG_ESP_S)
#घोषणा Fसूची_INSET_FLAG_ESP_IPSEC (0ULL << Fसूची_INSET_FLAG_ESP_S)

क्रमागत ice_fdir_tunnel_type अणु
	ICE_Fसूची_TUNNEL_TYPE_NONE = 0,
	ICE_Fसूची_TUNNEL_TYPE_GTPU,
	ICE_Fसूची_TUNNEL_TYPE_GTPU_EH,
पूर्ण;

काष्ठा virtchnl_fdir_fltr_conf अणु
	काष्ठा ice_fdir_fltr input;
	क्रमागत ice_fdir_tunnel_type ttype;
	u64 inset_flag;
	u32 flow_id;
पूर्ण;

अटल क्रमागत virtchnl_proto_hdr_type vc_pattern_ether[] = अणु
	VIRTCHNL_PROTO_HDR_ETH,
	VIRTCHNL_PROTO_HDR_NONE,
पूर्ण;

अटल क्रमागत virtchnl_proto_hdr_type vc_pattern_ipv4[] = अणु
	VIRTCHNL_PROTO_HDR_ETH,
	VIRTCHNL_PROTO_HDR_IPV4,
	VIRTCHNL_PROTO_HDR_NONE,
पूर्ण;

अटल क्रमागत virtchnl_proto_hdr_type vc_pattern_ipv4_tcp[] = अणु
	VIRTCHNL_PROTO_HDR_ETH,
	VIRTCHNL_PROTO_HDR_IPV4,
	VIRTCHNL_PROTO_HDR_TCP,
	VIRTCHNL_PROTO_HDR_NONE,
पूर्ण;

अटल क्रमागत virtchnl_proto_hdr_type vc_pattern_ipv4_udp[] = अणु
	VIRTCHNL_PROTO_HDR_ETH,
	VIRTCHNL_PROTO_HDR_IPV4,
	VIRTCHNL_PROTO_HDR_UDP,
	VIRTCHNL_PROTO_HDR_NONE,
पूर्ण;

अटल क्रमागत virtchnl_proto_hdr_type vc_pattern_ipv4_sctp[] = अणु
	VIRTCHNL_PROTO_HDR_ETH,
	VIRTCHNL_PROTO_HDR_IPV4,
	VIRTCHNL_PROTO_HDR_SCTP,
	VIRTCHNL_PROTO_HDR_NONE,
पूर्ण;

अटल क्रमागत virtchnl_proto_hdr_type vc_pattern_ipv6[] = अणु
	VIRTCHNL_PROTO_HDR_ETH,
	VIRTCHNL_PROTO_HDR_IPV6,
	VIRTCHNL_PROTO_HDR_NONE,
पूर्ण;

अटल क्रमागत virtchnl_proto_hdr_type vc_pattern_ipv6_tcp[] = अणु
	VIRTCHNL_PROTO_HDR_ETH,
	VIRTCHNL_PROTO_HDR_IPV6,
	VIRTCHNL_PROTO_HDR_TCP,
	VIRTCHNL_PROTO_HDR_NONE,
पूर्ण;

अटल क्रमागत virtchnl_proto_hdr_type vc_pattern_ipv6_udp[] = अणु
	VIRTCHNL_PROTO_HDR_ETH,
	VIRTCHNL_PROTO_HDR_IPV6,
	VIRTCHNL_PROTO_HDR_UDP,
	VIRTCHNL_PROTO_HDR_NONE,
पूर्ण;

अटल क्रमागत virtchnl_proto_hdr_type vc_pattern_ipv6_sctp[] = अणु
	VIRTCHNL_PROTO_HDR_ETH,
	VIRTCHNL_PROTO_HDR_IPV6,
	VIRTCHNL_PROTO_HDR_SCTP,
	VIRTCHNL_PROTO_HDR_NONE,
पूर्ण;

अटल क्रमागत virtchnl_proto_hdr_type vc_pattern_ipv4_gtpu[] = अणु
	VIRTCHNL_PROTO_HDR_ETH,
	VIRTCHNL_PROTO_HDR_IPV4,
	VIRTCHNL_PROTO_HDR_UDP,
	VIRTCHNL_PROTO_HDR_GTPU_IP,
	VIRTCHNL_PROTO_HDR_NONE,
पूर्ण;

अटल क्रमागत virtchnl_proto_hdr_type vc_pattern_ipv4_gtpu_eh[] = अणु
	VIRTCHNL_PROTO_HDR_ETH,
	VIRTCHNL_PROTO_HDR_IPV4,
	VIRTCHNL_PROTO_HDR_UDP,
	VIRTCHNL_PROTO_HDR_GTPU_IP,
	VIRTCHNL_PROTO_HDR_GTPU_EH,
	VIRTCHNL_PROTO_HDR_NONE,
पूर्ण;

अटल क्रमागत virtchnl_proto_hdr_type vc_pattern_ipv4_l2tpv3[] = अणु
	VIRTCHNL_PROTO_HDR_ETH,
	VIRTCHNL_PROTO_HDR_IPV4,
	VIRTCHNL_PROTO_HDR_L2TPV3,
	VIRTCHNL_PROTO_HDR_NONE,
पूर्ण;

अटल क्रमागत virtchnl_proto_hdr_type vc_pattern_ipv6_l2tpv3[] = अणु
	VIRTCHNL_PROTO_HDR_ETH,
	VIRTCHNL_PROTO_HDR_IPV6,
	VIRTCHNL_PROTO_HDR_L2TPV3,
	VIRTCHNL_PROTO_HDR_NONE,
पूर्ण;

अटल क्रमागत virtchnl_proto_hdr_type vc_pattern_ipv4_esp[] = अणु
	VIRTCHNL_PROTO_HDR_ETH,
	VIRTCHNL_PROTO_HDR_IPV4,
	VIRTCHNL_PROTO_HDR_ESP,
	VIRTCHNL_PROTO_HDR_NONE,
पूर्ण;

अटल क्रमागत virtchnl_proto_hdr_type vc_pattern_ipv6_esp[] = अणु
	VIRTCHNL_PROTO_HDR_ETH,
	VIRTCHNL_PROTO_HDR_IPV6,
	VIRTCHNL_PROTO_HDR_ESP,
	VIRTCHNL_PROTO_HDR_NONE,
पूर्ण;

अटल क्रमागत virtchnl_proto_hdr_type vc_pattern_ipv4_ah[] = अणु
	VIRTCHNL_PROTO_HDR_ETH,
	VIRTCHNL_PROTO_HDR_IPV4,
	VIRTCHNL_PROTO_HDR_AH,
	VIRTCHNL_PROTO_HDR_NONE,
पूर्ण;

अटल क्रमागत virtchnl_proto_hdr_type vc_pattern_ipv6_ah[] = अणु
	VIRTCHNL_PROTO_HDR_ETH,
	VIRTCHNL_PROTO_HDR_IPV6,
	VIRTCHNL_PROTO_HDR_AH,
	VIRTCHNL_PROTO_HDR_NONE,
पूर्ण;

अटल क्रमागत virtchnl_proto_hdr_type vc_pattern_ipv4_nat_t_esp[] = अणु
	VIRTCHNL_PROTO_HDR_ETH,
	VIRTCHNL_PROTO_HDR_IPV4,
	VIRTCHNL_PROTO_HDR_UDP,
	VIRTCHNL_PROTO_HDR_ESP,
	VIRTCHNL_PROTO_HDR_NONE,
पूर्ण;

अटल क्रमागत virtchnl_proto_hdr_type vc_pattern_ipv6_nat_t_esp[] = अणु
	VIRTCHNL_PROTO_HDR_ETH,
	VIRTCHNL_PROTO_HDR_IPV6,
	VIRTCHNL_PROTO_HDR_UDP,
	VIRTCHNL_PROTO_HDR_ESP,
	VIRTCHNL_PROTO_HDR_NONE,
पूर्ण;

अटल क्रमागत virtchnl_proto_hdr_type vc_pattern_ipv4_pfcp[] = अणु
	VIRTCHNL_PROTO_HDR_ETH,
	VIRTCHNL_PROTO_HDR_IPV4,
	VIRTCHNL_PROTO_HDR_UDP,
	VIRTCHNL_PROTO_HDR_PFCP,
	VIRTCHNL_PROTO_HDR_NONE,
पूर्ण;

अटल क्रमागत virtchnl_proto_hdr_type vc_pattern_ipv6_pfcp[] = अणु
	VIRTCHNL_PROTO_HDR_ETH,
	VIRTCHNL_PROTO_HDR_IPV6,
	VIRTCHNL_PROTO_HDR_UDP,
	VIRTCHNL_PROTO_HDR_PFCP,
	VIRTCHNL_PROTO_HDR_NONE,
पूर्ण;

काष्ठा virtchnl_fdir_pattern_match_item अणु
	क्रमागत virtchnl_proto_hdr_type *list;
	u64 input_set;
	u64 *meta;
पूर्ण;

अटल स्थिर काष्ठा virtchnl_fdir_pattern_match_item vc_fdir_pattern_os[] = अणु
	अणुvc_pattern_ipv4,                     0,         शून्यपूर्ण,
	अणुvc_pattern_ipv4_tcp,                 0,         शून्यपूर्ण,
	अणुvc_pattern_ipv4_udp,                 0,         शून्यपूर्ण,
	अणुvc_pattern_ipv4_sctp,                0,         शून्यपूर्ण,
	अणुvc_pattern_ipv6,                     0,         शून्यपूर्ण,
	अणुvc_pattern_ipv6_tcp,                 0,         शून्यपूर्ण,
	अणुvc_pattern_ipv6_udp,                 0,         शून्यपूर्ण,
	अणुvc_pattern_ipv6_sctp,                0,         शून्यपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा virtchnl_fdir_pattern_match_item vc_fdir_pattern_comms[] = अणु
	अणुvc_pattern_ipv4,                     0,         शून्यपूर्ण,
	अणुvc_pattern_ipv4_tcp,                 0,         शून्यपूर्ण,
	अणुvc_pattern_ipv4_udp,                 0,         शून्यपूर्ण,
	अणुvc_pattern_ipv4_sctp,                0,         शून्यपूर्ण,
	अणुvc_pattern_ipv6,                     0,         शून्यपूर्ण,
	अणुvc_pattern_ipv6_tcp,                 0,         शून्यपूर्ण,
	अणुvc_pattern_ipv6_udp,                 0,         शून्यपूर्ण,
	अणुvc_pattern_ipv6_sctp,                0,         शून्यपूर्ण,
	अणुvc_pattern_ether,                    0,         शून्यपूर्ण,
	अणुvc_pattern_ipv4_gtpu,                0,         शून्यपूर्ण,
	अणुvc_pattern_ipv4_gtpu_eh,             0,         शून्यपूर्ण,
	अणुvc_pattern_ipv4_l2tpv3,              0,         शून्यपूर्ण,
	अणुvc_pattern_ipv6_l2tpv3,              0,         शून्यपूर्ण,
	अणुvc_pattern_ipv4_esp,                 0,         शून्यपूर्ण,
	अणुvc_pattern_ipv6_esp,                 0,         शून्यपूर्ण,
	अणुvc_pattern_ipv4_ah,                  0,         शून्यपूर्ण,
	अणुvc_pattern_ipv6_ah,                  0,         शून्यपूर्ण,
	अणुvc_pattern_ipv4_nat_t_esp,           0,         शून्यपूर्ण,
	अणुvc_pattern_ipv6_nat_t_esp,           0,         शून्यपूर्ण,
	अणुvc_pattern_ipv4_pfcp,                0,         शून्यपूर्ण,
	अणुvc_pattern_ipv6_pfcp,                0,         शून्यपूर्ण,
पूर्ण;

काष्ठा virtchnl_fdir_inset_map अणु
	क्रमागत virtchnl_proto_hdr_field field;
	क्रमागत ice_flow_field fld;
	u64 flag;
	u64 mask;
पूर्ण;

अटल स्थिर काष्ठा virtchnl_fdir_inset_map fdir_inset_map[] = अणु
	अणुVIRTCHNL_PROTO_HDR_ETH_ETHERTYPE, ICE_FLOW_FIELD_IDX_ETH_TYPE, 0, 0पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_IPV4_SRC, ICE_FLOW_FIELD_IDX_IPV4_SA, 0, 0पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_IPV4_DST, ICE_FLOW_FIELD_IDX_IPV4_DA, 0, 0पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_IPV4_DSCP, ICE_FLOW_FIELD_IDX_IPV4_DSCP, 0, 0पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_IPV4_TTL, ICE_FLOW_FIELD_IDX_IPV4_TTL, 0, 0पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_IPV4_PROT, ICE_FLOW_FIELD_IDX_IPV4_PROT, 0, 0पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_IPV6_SRC, ICE_FLOW_FIELD_IDX_IPV6_SA, 0, 0पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_IPV6_DST, ICE_FLOW_FIELD_IDX_IPV6_DA, 0, 0पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_IPV6_TC, ICE_FLOW_FIELD_IDX_IPV6_DSCP, 0, 0पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_IPV6_HOP_LIMIT, ICE_FLOW_FIELD_IDX_IPV6_TTL, 0, 0पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_IPV6_PROT, ICE_FLOW_FIELD_IDX_IPV6_PROT, 0, 0पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_UDP_SRC_PORT, ICE_FLOW_FIELD_IDX_UDP_SRC_PORT, 0, 0पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_UDP_DST_PORT, ICE_FLOW_FIELD_IDX_UDP_DST_PORT, 0, 0पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_TCP_SRC_PORT, ICE_FLOW_FIELD_IDX_TCP_SRC_PORT, 0, 0पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_TCP_DST_PORT, ICE_FLOW_FIELD_IDX_TCP_DST_PORT, 0, 0पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_SCTP_SRC_PORT, ICE_FLOW_FIELD_IDX_SCTP_SRC_PORT, 0, 0पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_SCTP_DST_PORT, ICE_FLOW_FIELD_IDX_SCTP_DST_PORT, 0, 0पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_GTPU_IP_TEID, ICE_FLOW_FIELD_IDX_GTPU_IP_TEID, 0, 0पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_GTPU_EH_QFI, ICE_FLOW_FIELD_IDX_GTPU_EH_QFI, 0, 0पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_ESP_SPI, ICE_FLOW_FIELD_IDX_ESP_SPI,
		Fसूची_INSET_FLAG_ESP_IPSEC, Fसूची_INSET_FLAG_ESP_Mपूर्ण,
	अणुVIRTCHNL_PROTO_HDR_ESP_SPI, ICE_FLOW_FIELD_IDX_NAT_T_ESP_SPI,
		Fसूची_INSET_FLAG_ESP_UDP, Fसूची_INSET_FLAG_ESP_Mपूर्ण,
	अणुVIRTCHNL_PROTO_HDR_AH_SPI, ICE_FLOW_FIELD_IDX_AH_SPI, 0, 0पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_L2TPV3_SESS_ID, ICE_FLOW_FIELD_IDX_L2TPV3_SESS_ID, 0, 0पूर्ण,
	अणुVIRTCHNL_PROTO_HDR_PFCP_S_FIELD, ICE_FLOW_FIELD_IDX_UDP_DST_PORT, 0, 0पूर्ण,
पूर्ण;

/**
 * ice_vc_fdir_param_check
 * @vf: poपूर्णांकer to the VF काष्ठाure
 * @vsi_id: VF relative VSI ID
 *
 * Check क्रम the valid VSI ID, PF's state and VF's state
 *
 * Return: 0 on success, and -EINVAL on error.
 */
अटल पूर्णांक
ice_vc_fdir_param_check(काष्ठा ice_vf *vf, u16 vsi_id)
अणु
	काष्ठा ice_pf *pf = vf->pf;

	अगर (!test_bit(ICE_FLAG_FD_ENA, pf->flags))
		वापस -EINVAL;

	अगर (!test_bit(ICE_VF_STATE_ACTIVE, vf->vf_states))
		वापस -EINVAL;

	अगर (!(vf->driver_caps & VIRTCHNL_VF_OFFLOAD_Fसूची_PF))
		वापस -EINVAL;

	अगर (vsi_id != vf->lan_vsi_num)
		वापस -EINVAL;

	अगर (!ice_vc_isvalid_vsi_id(vf, vsi_id))
		वापस -EINVAL;

	अगर (!pf->vsi[vf->lan_vsi_idx])
		वापस -EINVAL;

	वापस 0;
पूर्ण

/**
 * ice_vf_start_ctrl_vsi
 * @vf: poपूर्णांकer to the VF काष्ठाure
 *
 * Allocate ctrl_vsi क्रम the first समय and खोलो the ctrl_vsi port क्रम VF
 *
 * Return: 0 on success, and other on error.
 */
अटल पूर्णांक ice_vf_start_ctrl_vsi(काष्ठा ice_vf *vf)
अणु
	काष्ठा ice_pf *pf = vf->pf;
	काष्ठा ice_vsi *ctrl_vsi;
	काष्ठा device *dev;
	पूर्णांक err;

	dev = ice_pf_to_dev(pf);
	अगर (vf->ctrl_vsi_idx != ICE_NO_VSI)
		वापस -EEXIST;

	ctrl_vsi = ice_vf_ctrl_vsi_setup(vf);
	अगर (!ctrl_vsi) अणु
		dev_dbg(dev, "Could not setup control VSI for VF %d\n",
			vf->vf_id);
		वापस -ENOMEM;
	पूर्ण

	err = ice_vsi_खोलो_ctrl(ctrl_vsi);
	अगर (err) अणु
		dev_dbg(dev, "Could not open control VSI for VF %d\n",
			vf->vf_id);
		जाओ err_vsi_खोलो;
	पूर्ण

	वापस 0;

err_vsi_खोलो:
	ice_vsi_release(ctrl_vsi);
	अगर (vf->ctrl_vsi_idx != ICE_NO_VSI) अणु
		pf->vsi[vf->ctrl_vsi_idx] = शून्य;
		vf->ctrl_vsi_idx = ICE_NO_VSI;
	पूर्ण
	वापस err;
पूर्ण

/**
 * ice_vc_fdir_alloc_prof - allocate profile क्रम this filter flow type
 * @vf: poपूर्णांकer to the VF काष्ठाure
 * @flow: filter flow type
 *
 * Return: 0 on success, and other on error.
 */
अटल पूर्णांक
ice_vc_fdir_alloc_prof(काष्ठा ice_vf *vf, क्रमागत ice_fltr_ptype flow)
अणु
	काष्ठा ice_vf_fdir *fdir = &vf->fdir;

	अगर (!fdir->fdir_prof) अणु
		fdir->fdir_prof = devm_kसुस्मृति(ice_pf_to_dev(vf->pf),
					       ICE_FLTR_PTYPE_MAX,
					       माप(*fdir->fdir_prof),
					       GFP_KERNEL);
		अगर (!fdir->fdir_prof)
			वापस -ENOMEM;
	पूर्ण

	अगर (!fdir->fdir_prof[flow]) अणु
		fdir->fdir_prof[flow] = devm_kzalloc(ice_pf_to_dev(vf->pf),
						     माप(**fdir->fdir_prof),
						     GFP_KERNEL);
		अगर (!fdir->fdir_prof[flow])
			वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ice_vc_fdir_मुक्त_prof - मुक्त profile क्रम this filter flow type
 * @vf: poपूर्णांकer to the VF काष्ठाure
 * @flow: filter flow type
 */
अटल व्योम
ice_vc_fdir_मुक्त_prof(काष्ठा ice_vf *vf, क्रमागत ice_fltr_ptype flow)
अणु
	काष्ठा ice_vf_fdir *fdir = &vf->fdir;

	अगर (!fdir->fdir_prof)
		वापस;

	अगर (!fdir->fdir_prof[flow])
		वापस;

	devm_kमुक्त(ice_pf_to_dev(vf->pf), fdir->fdir_prof[flow]);
	fdir->fdir_prof[flow] = शून्य;
पूर्ण

/**
 * ice_vc_fdir_मुक्त_prof_all - मुक्त all the profile क्रम this VF
 * @vf: poपूर्णांकer to the VF काष्ठाure
 */
अटल व्योम ice_vc_fdir_मुक्त_prof_all(काष्ठा ice_vf *vf)
अणु
	काष्ठा ice_vf_fdir *fdir = &vf->fdir;
	क्रमागत ice_fltr_ptype flow;

	अगर (!fdir->fdir_prof)
		वापस;

	क्रम (flow = ICE_FLTR_PTYPE_NONF_NONE; flow < ICE_FLTR_PTYPE_MAX; flow++)
		ice_vc_fdir_मुक्त_prof(vf, flow);

	devm_kमुक्त(ice_pf_to_dev(vf->pf), fdir->fdir_prof);
	fdir->fdir_prof = शून्य;
पूर्ण

/**
 * ice_vc_fdir_parse_flow_fld
 * @proto_hdr: भव channel protocol filter header
 * @conf: Fसूची configuration क्रम each filter
 * @fld: field type array
 * @fld_cnt: field counter
 *
 * Parse the भव channel filter header and store them पूर्णांकo field type array
 *
 * Return: 0 on success, and other on error.
 */
अटल पूर्णांक
ice_vc_fdir_parse_flow_fld(काष्ठा virtchnl_proto_hdr *proto_hdr,
			   काष्ठा virtchnl_fdir_fltr_conf *conf,
			   क्रमागत ice_flow_field *fld, पूर्णांक *fld_cnt)
अणु
	काष्ठा virtchnl_proto_hdr hdr;
	u32 i;

	स_नकल(&hdr, proto_hdr, माप(hdr));

	क्रम (i = 0; (i < ARRAY_SIZE(fdir_inset_map)) &&
	     VIRTCHNL_GET_PROTO_HDR_FIELD(&hdr); i++)
		अगर (VIRTCHNL_TEST_PROTO_HDR(&hdr, fdir_inset_map[i].field)) अणु
			अगर (fdir_inset_map[i].mask &&
			    ((fdir_inset_map[i].mask & conf->inset_flag) !=
			     fdir_inset_map[i].flag))
				जारी;

			fld[*fld_cnt] = fdir_inset_map[i].fld;
			*fld_cnt += 1;
			अगर (*fld_cnt >= ICE_FLOW_FIELD_IDX_MAX)
				वापस -EINVAL;
			VIRTCHNL_DEL_PROTO_HDR_FIELD(&hdr,
						     fdir_inset_map[i].field);
		पूर्ण

	वापस 0;
पूर्ण

/**
 * ice_vc_fdir_set_flow_fld
 * @vf: poपूर्णांकer to the VF काष्ठाure
 * @fltr: भव channel add cmd buffer
 * @conf: Fसूची configuration क्रम each filter
 * @seg: array of one or more packet segments that describe the flow
 *
 * Parse the भव channel add msg buffer's field vector and store them पूर्णांकo
 * flow's packet segment field
 *
 * Return: 0 on success, and other on error.
 */
अटल पूर्णांक
ice_vc_fdir_set_flow_fld(काष्ठा ice_vf *vf, काष्ठा virtchnl_fdir_add *fltr,
			 काष्ठा virtchnl_fdir_fltr_conf *conf,
			 काष्ठा ice_flow_seg_info *seg)
अणु
	काष्ठा virtchnl_fdir_rule *rule = &fltr->rule_cfg;
	क्रमागत ice_flow_field fld[ICE_FLOW_FIELD_IDX_MAX];
	काष्ठा device *dev = ice_pf_to_dev(vf->pf);
	काष्ठा virtchnl_proto_hdrs *proto;
	पूर्णांक fld_cnt = 0;
	पूर्णांक i;

	proto = &rule->proto_hdrs;
	क्रम (i = 0; i < proto->count; i++) अणु
		काष्ठा virtchnl_proto_hdr *hdr = &proto->proto_hdr[i];
		पूर्णांक ret;

		ret = ice_vc_fdir_parse_flow_fld(hdr, conf, fld, &fld_cnt);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (fld_cnt == 0) अणु
		dev_dbg(dev, "Empty input set for VF %d\n", vf->vf_id);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < fld_cnt; i++)
		ice_flow_set_fld(seg, fld[i],
				 ICE_FLOW_FLD_OFF_INVAL,
				 ICE_FLOW_FLD_OFF_INVAL,
				 ICE_FLOW_FLD_OFF_INVAL, false);

	वापस 0;
पूर्ण

/**
 * ice_vc_fdir_set_flow_hdr - config the flow's packet segment header
 * @vf: poपूर्णांकer to the VF काष्ठाure
 * @conf: Fसूची configuration क्रम each filter
 * @seg: array of one or more packet segments that describe the flow
 *
 * Return: 0 on success, and other on error.
 */
अटल पूर्णांक
ice_vc_fdir_set_flow_hdr(काष्ठा ice_vf *vf,
			 काष्ठा virtchnl_fdir_fltr_conf *conf,
			 काष्ठा ice_flow_seg_info *seg)
अणु
	क्रमागत ice_fltr_ptype flow = conf->input.flow_type;
	क्रमागत ice_fdir_tunnel_type ttype = conf->ttype;
	काष्ठा device *dev = ice_pf_to_dev(vf->pf);

	चयन (flow) अणु
	हाल ICE_FLTR_PTYPE_NON_IP_L2:
		ICE_FLOW_SET_HDRS(seg, ICE_FLOW_SEG_HDR_ETH_NON_IP);
		अवरोध;
	हाल ICE_FLTR_PTYPE_NONF_IPV4_L2TPV3:
		ICE_FLOW_SET_HDRS(seg, ICE_FLOW_SEG_HDR_L2TPV3 |
				  ICE_FLOW_SEG_HDR_IPV4 |
				  ICE_FLOW_SEG_HDR_IPV_OTHER);
		अवरोध;
	हाल ICE_FLTR_PTYPE_NONF_IPV4_ESP:
		ICE_FLOW_SET_HDRS(seg, ICE_FLOW_SEG_HDR_ESP |
				  ICE_FLOW_SEG_HDR_IPV4 |
				  ICE_FLOW_SEG_HDR_IPV_OTHER);
		अवरोध;
	हाल ICE_FLTR_PTYPE_NONF_IPV4_AH:
		ICE_FLOW_SET_HDRS(seg, ICE_FLOW_SEG_HDR_AH |
				  ICE_FLOW_SEG_HDR_IPV4 |
				  ICE_FLOW_SEG_HDR_IPV_OTHER);
		अवरोध;
	हाल ICE_FLTR_PTYPE_NONF_IPV4_NAT_T_ESP:
		ICE_FLOW_SET_HDRS(seg, ICE_FLOW_SEG_HDR_NAT_T_ESP |
				  ICE_FLOW_SEG_HDR_IPV4 |
				  ICE_FLOW_SEG_HDR_IPV_OTHER);
		अवरोध;
	हाल ICE_FLTR_PTYPE_NONF_IPV4_PFCP_NODE:
		ICE_FLOW_SET_HDRS(seg, ICE_FLOW_SEG_HDR_PFCP_NODE |
				  ICE_FLOW_SEG_HDR_IPV4 |
				  ICE_FLOW_SEG_HDR_IPV_OTHER);
		अवरोध;
	हाल ICE_FLTR_PTYPE_NONF_IPV4_PFCP_SESSION:
		ICE_FLOW_SET_HDRS(seg, ICE_FLOW_SEG_HDR_PFCP_SESSION |
				  ICE_FLOW_SEG_HDR_IPV4 |
				  ICE_FLOW_SEG_HDR_IPV_OTHER);
		अवरोध;
	हाल ICE_FLTR_PTYPE_NONF_IPV4_OTHER:
		ICE_FLOW_SET_HDRS(seg, ICE_FLOW_SEG_HDR_IPV4 |
				  ICE_FLOW_SEG_HDR_IPV_OTHER);
		अवरोध;
	हाल ICE_FLTR_PTYPE_NONF_IPV4_TCP:
		ICE_FLOW_SET_HDRS(seg, ICE_FLOW_SEG_HDR_TCP |
				  ICE_FLOW_SEG_HDR_IPV4 |
				  ICE_FLOW_SEG_HDR_IPV_OTHER);
		अवरोध;
	हाल ICE_FLTR_PTYPE_NONF_IPV4_UDP:
		ICE_FLOW_SET_HDRS(seg, ICE_FLOW_SEG_HDR_UDP |
				  ICE_FLOW_SEG_HDR_IPV4 |
				  ICE_FLOW_SEG_HDR_IPV_OTHER);
		अवरोध;
	हाल ICE_FLTR_PTYPE_NONF_IPV4_GTPU_IPV4_UDP:
	हाल ICE_FLTR_PTYPE_NONF_IPV4_GTPU_IPV4_TCP:
	हाल ICE_FLTR_PTYPE_NONF_IPV4_GTPU_IPV4_ICMP:
	हाल ICE_FLTR_PTYPE_NONF_IPV4_GTPU_IPV4_OTHER:
		अगर (ttype == ICE_Fसूची_TUNNEL_TYPE_GTPU) अणु
			ICE_FLOW_SET_HDRS(seg, ICE_FLOW_SEG_HDR_GTPU_IP |
					  ICE_FLOW_SEG_HDR_IPV4 |
					  ICE_FLOW_SEG_HDR_IPV_OTHER);
		पूर्ण अन्यथा अगर (ttype == ICE_Fसूची_TUNNEL_TYPE_GTPU_EH) अणु
			ICE_FLOW_SET_HDRS(seg, ICE_FLOW_SEG_HDR_GTPU_EH |
					  ICE_FLOW_SEG_HDR_GTPU_IP |
					  ICE_FLOW_SEG_HDR_IPV4 |
					  ICE_FLOW_SEG_HDR_IPV_OTHER);
		पूर्ण अन्यथा अणु
			dev_dbg(dev, "Invalid tunnel type 0x%x for VF %d\n",
				flow, vf->vf_id);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल ICE_FLTR_PTYPE_NONF_IPV4_SCTP:
		ICE_FLOW_SET_HDRS(seg, ICE_FLOW_SEG_HDR_SCTP |
				  ICE_FLOW_SEG_HDR_IPV4 |
				  ICE_FLOW_SEG_HDR_IPV_OTHER);
		अवरोध;
	हाल ICE_FLTR_PTYPE_NONF_IPV6_L2TPV3:
		ICE_FLOW_SET_HDRS(seg, ICE_FLOW_SEG_HDR_L2TPV3 |
				  ICE_FLOW_SEG_HDR_IPV6 |
				  ICE_FLOW_SEG_HDR_IPV_OTHER);
		अवरोध;
	हाल ICE_FLTR_PTYPE_NONF_IPV6_ESP:
		ICE_FLOW_SET_HDRS(seg, ICE_FLOW_SEG_HDR_ESP |
				  ICE_FLOW_SEG_HDR_IPV6 |
				  ICE_FLOW_SEG_HDR_IPV_OTHER);
		अवरोध;
	हाल ICE_FLTR_PTYPE_NONF_IPV6_AH:
		ICE_FLOW_SET_HDRS(seg, ICE_FLOW_SEG_HDR_AH |
				  ICE_FLOW_SEG_HDR_IPV6 |
				  ICE_FLOW_SEG_HDR_IPV_OTHER);
		अवरोध;
	हाल ICE_FLTR_PTYPE_NONF_IPV6_NAT_T_ESP:
		ICE_FLOW_SET_HDRS(seg, ICE_FLOW_SEG_HDR_NAT_T_ESP |
				  ICE_FLOW_SEG_HDR_IPV6 |
				  ICE_FLOW_SEG_HDR_IPV_OTHER);
		अवरोध;
	हाल ICE_FLTR_PTYPE_NONF_IPV6_PFCP_NODE:
		ICE_FLOW_SET_HDRS(seg, ICE_FLOW_SEG_HDR_PFCP_NODE |
				  ICE_FLOW_SEG_HDR_IPV6 |
				  ICE_FLOW_SEG_HDR_IPV_OTHER);
		अवरोध;
	हाल ICE_FLTR_PTYPE_NONF_IPV6_PFCP_SESSION:
		ICE_FLOW_SET_HDRS(seg, ICE_FLOW_SEG_HDR_PFCP_SESSION |
				  ICE_FLOW_SEG_HDR_IPV6 |
				  ICE_FLOW_SEG_HDR_IPV_OTHER);
		अवरोध;
	हाल ICE_FLTR_PTYPE_NONF_IPV6_OTHER:
		ICE_FLOW_SET_HDRS(seg, ICE_FLOW_SEG_HDR_IPV6 |
				  ICE_FLOW_SEG_HDR_IPV_OTHER);
		अवरोध;
	हाल ICE_FLTR_PTYPE_NONF_IPV6_TCP:
		ICE_FLOW_SET_HDRS(seg, ICE_FLOW_SEG_HDR_TCP |
				  ICE_FLOW_SEG_HDR_IPV6 |
				  ICE_FLOW_SEG_HDR_IPV_OTHER);
		अवरोध;
	हाल ICE_FLTR_PTYPE_NONF_IPV6_UDP:
		ICE_FLOW_SET_HDRS(seg, ICE_FLOW_SEG_HDR_UDP |
				  ICE_FLOW_SEG_HDR_IPV6 |
				  ICE_FLOW_SEG_HDR_IPV_OTHER);
		अवरोध;
	हाल ICE_FLTR_PTYPE_NONF_IPV6_SCTP:
		ICE_FLOW_SET_HDRS(seg, ICE_FLOW_SEG_HDR_SCTP |
				  ICE_FLOW_SEG_HDR_IPV6 |
				  ICE_FLOW_SEG_HDR_IPV_OTHER);
		अवरोध;
	शेष:
		dev_dbg(dev, "Invalid flow type 0x%x for VF %d failed\n",
			flow, vf->vf_id);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ice_vc_fdir_rem_prof - हटाओ profile क्रम this filter flow type
 * @vf: poपूर्णांकer to the VF काष्ठाure
 * @flow: filter flow type
 * @tun: 0 implies non-tunnel type filter, 1 implies tunnel type filter
 */
अटल व्योम
ice_vc_fdir_rem_prof(काष्ठा ice_vf *vf, क्रमागत ice_fltr_ptype flow, पूर्णांक tun)
अणु
	काष्ठा ice_vf_fdir *fdir = &vf->fdir;
	काष्ठा ice_fd_hw_prof *vf_prof;
	काष्ठा ice_pf *pf = vf->pf;
	काष्ठा ice_vsi *vf_vsi;
	काष्ठा device *dev;
	काष्ठा ice_hw *hw;
	u64 prof_id;
	पूर्णांक i;

	dev = ice_pf_to_dev(pf);
	hw = &pf->hw;
	अगर (!fdir->fdir_prof || !fdir->fdir_prof[flow])
		वापस;

	vf_prof = fdir->fdir_prof[flow];

	vf_vsi = pf->vsi[vf->lan_vsi_idx];
	अगर (!vf_vsi) अणु
		dev_dbg(dev, "NULL vf %d vsi pointer\n", vf->vf_id);
		वापस;
	पूर्ण

	अगर (!fdir->prof_entry_cnt[flow][tun])
		वापस;

	prof_id = ICE_FLOW_PROF_FD(vf_vsi->vsi_num,
				   flow, tun ? ICE_FLTR_PTYPE_MAX : 0);

	क्रम (i = 0; i < fdir->prof_entry_cnt[flow][tun]; i++)
		अगर (vf_prof->entry_h[i][tun]) अणु
			u16 vsi_num = ice_get_hw_vsi_num(hw, vf_prof->vsi_h[i]);

			ice_rem_prof_id_flow(hw, ICE_BLK_FD, vsi_num, prof_id);
			ice_flow_rem_entry(hw, ICE_BLK_FD,
					   vf_prof->entry_h[i][tun]);
			vf_prof->entry_h[i][tun] = 0;
		पूर्ण

	ice_flow_rem_prof(hw, ICE_BLK_FD, prof_id);
	devm_kमुक्त(dev, vf_prof->fdir_seg[tun]);
	vf_prof->fdir_seg[tun] = शून्य;

	क्रम (i = 0; i < vf_prof->cnt; i++)
		vf_prof->vsi_h[i] = 0;

	fdir->prof_entry_cnt[flow][tun] = 0;
पूर्ण

/**
 * ice_vc_fdir_rem_prof_all - हटाओ profile क्रम this VF
 * @vf: poपूर्णांकer to the VF काष्ठाure
 */
अटल व्योम ice_vc_fdir_rem_prof_all(काष्ठा ice_vf *vf)
अणु
	क्रमागत ice_fltr_ptype flow;

	क्रम (flow = ICE_FLTR_PTYPE_NONF_NONE;
	     flow < ICE_FLTR_PTYPE_MAX; flow++) अणु
		ice_vc_fdir_rem_prof(vf, flow, 0);
		ice_vc_fdir_rem_prof(vf, flow, 1);
	पूर्ण
पूर्ण

/**
 * ice_vc_fdir_ग_लिखो_flow_prof
 * @vf: poपूर्णांकer to the VF काष्ठाure
 * @flow: filter flow type
 * @seg: array of one or more packet segments that describe the flow
 * @tun: 0 implies non-tunnel type filter, 1 implies tunnel type filter
 *
 * Write the flow's profile config and packet segment पूर्णांकo the hardware
 *
 * Return: 0 on success, and other on error.
 */
अटल पूर्णांक
ice_vc_fdir_ग_लिखो_flow_prof(काष्ठा ice_vf *vf, क्रमागत ice_fltr_ptype flow,
			    काष्ठा ice_flow_seg_info *seg, पूर्णांक tun)
अणु
	काष्ठा ice_vf_fdir *fdir = &vf->fdir;
	काष्ठा ice_vsi *vf_vsi, *ctrl_vsi;
	काष्ठा ice_flow_seg_info *old_seg;
	काष्ठा ice_flow_prof *prof = शून्य;
	काष्ठा ice_fd_hw_prof *vf_prof;
	क्रमागत ice_status status;
	काष्ठा device *dev;
	काष्ठा ice_pf *pf;
	काष्ठा ice_hw *hw;
	u64 entry1_h = 0;
	u64 entry2_h = 0;
	u64 prof_id;
	पूर्णांक ret;

	pf = vf->pf;
	dev = ice_pf_to_dev(pf);
	hw = &pf->hw;
	vf_vsi = pf->vsi[vf->lan_vsi_idx];
	अगर (!vf_vsi)
		वापस -EINVAL;

	ctrl_vsi = pf->vsi[vf->ctrl_vsi_idx];
	अगर (!ctrl_vsi)
		वापस -EINVAL;

	vf_prof = fdir->fdir_prof[flow];
	old_seg = vf_prof->fdir_seg[tun];
	अगर (old_seg) अणु
		अगर (!स_भेद(old_seg, seg, माप(*seg))) अणु
			dev_dbg(dev, "Duplicated profile for VF %d!\n",
				vf->vf_id);
			वापस -EEXIST;
		पूर्ण

		अगर (fdir->fdir_fltr_cnt[flow][tun]) अणु
			ret = -EINVAL;
			dev_dbg(dev, "Input set conflicts for VF %d\n",
				vf->vf_id);
			जाओ err_निकास;
		पूर्ण

		/* हटाओ previously allocated profile */
		ice_vc_fdir_rem_prof(vf, flow, tun);
	पूर्ण

	prof_id = ICE_FLOW_PROF_FD(vf_vsi->vsi_num, flow,
				   tun ? ICE_FLTR_PTYPE_MAX : 0);

	status = ice_flow_add_prof(hw, ICE_BLK_FD, ICE_FLOW_RX, prof_id, seg,
				   tun + 1, &prof);
	ret = ice_status_to_त्रुटि_सं(status);
	अगर (ret) अणु
		dev_dbg(dev, "Could not add VSI flow 0x%x for VF %d\n",
			flow, vf->vf_id);
		जाओ err_निकास;
	पूर्ण

	status = ice_flow_add_entry(hw, ICE_BLK_FD, prof_id, vf_vsi->idx,
				    vf_vsi->idx, ICE_FLOW_PRIO_NORMAL,
				    seg, &entry1_h);
	ret = ice_status_to_त्रुटि_सं(status);
	अगर (ret) अणु
		dev_dbg(dev, "Could not add flow 0x%x VSI entry for VF %d\n",
			flow, vf->vf_id);
		जाओ err_prof;
	पूर्ण

	status = ice_flow_add_entry(hw, ICE_BLK_FD, prof_id, vf_vsi->idx,
				    ctrl_vsi->idx, ICE_FLOW_PRIO_NORMAL,
				    seg, &entry2_h);
	ret = ice_status_to_त्रुटि_सं(status);
	अगर (ret) अणु
		dev_dbg(dev,
			"Could not add flow 0x%x Ctrl VSI entry for VF %d\n",
			flow, vf->vf_id);
		जाओ err_entry_1;
	पूर्ण

	vf_prof->fdir_seg[tun] = seg;
	vf_prof->cnt = 0;
	fdir->prof_entry_cnt[flow][tun] = 0;

	vf_prof->entry_h[vf_prof->cnt][tun] = entry1_h;
	vf_prof->vsi_h[vf_prof->cnt] = vf_vsi->idx;
	vf_prof->cnt++;
	fdir->prof_entry_cnt[flow][tun]++;

	vf_prof->entry_h[vf_prof->cnt][tun] = entry2_h;
	vf_prof->vsi_h[vf_prof->cnt] = ctrl_vsi->idx;
	vf_prof->cnt++;
	fdir->prof_entry_cnt[flow][tun]++;

	वापस 0;

err_entry_1:
	ice_rem_prof_id_flow(hw, ICE_BLK_FD,
			     ice_get_hw_vsi_num(hw, vf_vsi->idx), prof_id);
	ice_flow_rem_entry(hw, ICE_BLK_FD, entry1_h);
err_prof:
	ice_flow_rem_prof(hw, ICE_BLK_FD, prof_id);
err_निकास:
	वापस ret;
पूर्ण

/**
 * ice_vc_fdir_config_input_set
 * @vf: poपूर्णांकer to the VF काष्ठाure
 * @fltr: भव channel add cmd buffer
 * @conf: Fसूची configuration क्रम each filter
 * @tun: 0 implies non-tunnel type filter, 1 implies tunnel type filter
 *
 * Config the input set type and value क्रम भव channel add msg buffer
 *
 * Return: 0 on success, and other on error.
 */
अटल पूर्णांक
ice_vc_fdir_config_input_set(काष्ठा ice_vf *vf, काष्ठा virtchnl_fdir_add *fltr,
			     काष्ठा virtchnl_fdir_fltr_conf *conf, पूर्णांक tun)
अणु
	काष्ठा ice_fdir_fltr *input = &conf->input;
	काष्ठा device *dev = ice_pf_to_dev(vf->pf);
	काष्ठा ice_flow_seg_info *seg;
	क्रमागत ice_fltr_ptype flow;
	पूर्णांक ret;

	flow = input->flow_type;
	ret = ice_vc_fdir_alloc_prof(vf, flow);
	अगर (ret) अणु
		dev_dbg(dev, "Alloc flow prof for VF %d failed\n", vf->vf_id);
		वापस ret;
	पूर्ण

	seg = devm_kzalloc(dev, माप(*seg), GFP_KERNEL);
	अगर (!seg)
		वापस -ENOMEM;

	ret = ice_vc_fdir_set_flow_fld(vf, fltr, conf, seg);
	अगर (ret) अणु
		dev_dbg(dev, "Set flow field for VF %d failed\n", vf->vf_id);
		जाओ err_निकास;
	पूर्ण

	ret = ice_vc_fdir_set_flow_hdr(vf, conf, seg);
	अगर (ret) अणु
		dev_dbg(dev, "Set flow hdr for VF %d failed\n", vf->vf_id);
		जाओ err_निकास;
	पूर्ण

	ret = ice_vc_fdir_ग_लिखो_flow_prof(vf, flow, seg, tun);
	अगर (ret == -EEXIST) अणु
		devm_kमुक्त(dev, seg);
	पूर्ण अन्यथा अगर (ret) अणु
		dev_dbg(dev, "Write flow profile for VF %d failed\n",
			vf->vf_id);
		जाओ err_निकास;
	पूर्ण

	वापस 0;

err_निकास:
	devm_kमुक्त(dev, seg);
	वापस ret;
पूर्ण

/**
 * ice_vc_fdir_match_pattern
 * @fltr: भव channel add cmd buffer
 * @type: भव channel protocol filter header type
 *
 * Matching the header type by comparing fltr and type's value.
 *
 * Return: true on success, and false on error.
 */
अटल bool
ice_vc_fdir_match_pattern(काष्ठा virtchnl_fdir_add *fltr,
			  क्रमागत virtchnl_proto_hdr_type *type)
अणु
	काष्ठा virtchnl_proto_hdrs *proto = &fltr->rule_cfg.proto_hdrs;
	पूर्णांक i = 0;

	जबतक ((i < proto->count) &&
	       (*type == proto->proto_hdr[i].type) &&
	       (*type != VIRTCHNL_PROTO_HDR_NONE)) अणु
		type++;
		i++;
	पूर्ण

	वापस ((i == proto->count) && (*type == VIRTCHNL_PROTO_HDR_NONE));
पूर्ण

/**
 * ice_vc_fdir_get_pattern - get जबतक list pattern
 * @vf: poपूर्णांकer to the VF info
 * @len: filter list length
 *
 * Return: poपूर्णांकer to allowed filter list
 */
अटल स्थिर काष्ठा virtchnl_fdir_pattern_match_item *
ice_vc_fdir_get_pattern(काष्ठा ice_vf *vf, पूर्णांक *len)
अणु
	स्थिर काष्ठा virtchnl_fdir_pattern_match_item *item;
	काष्ठा ice_pf *pf = vf->pf;
	काष्ठा ice_hw *hw;

	hw = &pf->hw;
	अगर (!म_भेदन(hw->active_pkg_name, "ICE COMMS Package",
		     माप(hw->active_pkg_name))) अणु
		item = vc_fdir_pattern_comms;
		*len = ARRAY_SIZE(vc_fdir_pattern_comms);
	पूर्ण अन्यथा अणु
		item = vc_fdir_pattern_os;
		*len = ARRAY_SIZE(vc_fdir_pattern_os);
	पूर्ण

	वापस item;
पूर्ण

/**
 * ice_vc_fdir_search_pattern
 * @vf: poपूर्णांकer to the VF info
 * @fltr: भव channel add cmd buffer
 *
 * Search क्रम matched pattern from supported pattern list
 *
 * Return: 0 on success, and other on error.
 */
अटल पूर्णांक
ice_vc_fdir_search_pattern(काष्ठा ice_vf *vf, काष्ठा virtchnl_fdir_add *fltr)
अणु
	स्थिर काष्ठा virtchnl_fdir_pattern_match_item *pattern;
	पूर्णांक len, i;

	pattern = ice_vc_fdir_get_pattern(vf, &len);

	क्रम (i = 0; i < len; i++)
		अगर (ice_vc_fdir_match_pattern(fltr, pattern[i].list))
			वापस 0;

	वापस -EINVAL;
पूर्ण

/**
 * ice_vc_fdir_parse_pattern
 * @vf: poपूर्णांकer to the VF info
 * @fltr: भव channel add cmd buffer
 * @conf: Fसूची configuration क्रम each filter
 *
 * Parse the भव channel filter's pattern and store them पूर्णांकo conf
 *
 * Return: 0 on success, and other on error.
 */
अटल पूर्णांक
ice_vc_fdir_parse_pattern(काष्ठा ice_vf *vf, काष्ठा virtchnl_fdir_add *fltr,
			  काष्ठा virtchnl_fdir_fltr_conf *conf)
अणु
	काष्ठा virtchnl_proto_hdrs *proto = &fltr->rule_cfg.proto_hdrs;
	क्रमागत virtchnl_proto_hdr_type l3 = VIRTCHNL_PROTO_HDR_NONE;
	क्रमागत virtchnl_proto_hdr_type l4 = VIRTCHNL_PROTO_HDR_NONE;
	काष्ठा device *dev = ice_pf_to_dev(vf->pf);
	काष्ठा ice_fdir_fltr *input = &conf->input;
	पूर्णांक i;

	अगर (proto->count > VIRTCHNL_MAX_NUM_PROTO_HDRS) अणु
		dev_dbg(dev, "Invalid protocol count:0x%x for VF %d\n",
			proto->count, vf->vf_id);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < proto->count; i++) अणु
		काष्ठा virtchnl_proto_hdr *hdr = &proto->proto_hdr[i];
		काष्ठा ip_esp_hdr *esph;
		काष्ठा ip_auth_hdr *ah;
		काष्ठा sctphdr *sctph;
		काष्ठा ipv6hdr *ip6h;
		काष्ठा udphdr *udph;
		काष्ठा tcphdr *tcph;
		काष्ठा ethhdr *eth;
		काष्ठा iphdr *iph;
		u8 s_field;
		u8 *rawh;

		चयन (hdr->type) अणु
		हाल VIRTCHNL_PROTO_HDR_ETH:
			eth = (काष्ठा ethhdr *)hdr->buffer;
			input->flow_type = ICE_FLTR_PTYPE_NON_IP_L2;

			अगर (hdr->field_selector)
				input->ext_data.ether_type = eth->h_proto;
			अवरोध;
		हाल VIRTCHNL_PROTO_HDR_IPV4:
			iph = (काष्ठा iphdr *)hdr->buffer;
			l3 = VIRTCHNL_PROTO_HDR_IPV4;
			input->flow_type = ICE_FLTR_PTYPE_NONF_IPV4_OTHER;

			अगर (hdr->field_selector) अणु
				input->ip.v4.src_ip = iph->saddr;
				input->ip.v4.dst_ip = iph->daddr;
				input->ip.v4.tos = iph->tos;
				input->ip.v4.proto = iph->protocol;
			पूर्ण
			अवरोध;
		हाल VIRTCHNL_PROTO_HDR_IPV6:
			ip6h = (काष्ठा ipv6hdr *)hdr->buffer;
			l3 = VIRTCHNL_PROTO_HDR_IPV6;
			input->flow_type = ICE_FLTR_PTYPE_NONF_IPV6_OTHER;

			अगर (hdr->field_selector) अणु
				स_नकल(input->ip.v6.src_ip,
				       ip6h->saddr.in6_u.u6_addr8,
				       माप(ip6h->saddr));
				स_नकल(input->ip.v6.dst_ip,
				       ip6h->daddr.in6_u.u6_addr8,
				       माप(ip6h->daddr));
				input->ip.v6.tc = ((u8)(ip6h->priority) << 4) |
						  (ip6h->flow_lbl[0] >> 4);
				input->ip.v6.proto = ip6h->nexthdr;
			पूर्ण
			अवरोध;
		हाल VIRTCHNL_PROTO_HDR_TCP:
			tcph = (काष्ठा tcphdr *)hdr->buffer;
			अगर (l3 == VIRTCHNL_PROTO_HDR_IPV4)
				input->flow_type = ICE_FLTR_PTYPE_NONF_IPV4_TCP;
			अन्यथा अगर (l3 == VIRTCHNL_PROTO_HDR_IPV6)
				input->flow_type = ICE_FLTR_PTYPE_NONF_IPV6_TCP;

			अगर (hdr->field_selector) अणु
				अगर (l3 == VIRTCHNL_PROTO_HDR_IPV4) अणु
					input->ip.v4.src_port = tcph->source;
					input->ip.v4.dst_port = tcph->dest;
				पूर्ण अन्यथा अगर (l3 == VIRTCHNL_PROTO_HDR_IPV6) अणु
					input->ip.v6.src_port = tcph->source;
					input->ip.v6.dst_port = tcph->dest;
				पूर्ण
			पूर्ण
			अवरोध;
		हाल VIRTCHNL_PROTO_HDR_UDP:
			udph = (काष्ठा udphdr *)hdr->buffer;
			अगर (l3 == VIRTCHNL_PROTO_HDR_IPV4)
				input->flow_type = ICE_FLTR_PTYPE_NONF_IPV4_UDP;
			अन्यथा अगर (l3 == VIRTCHNL_PROTO_HDR_IPV6)
				input->flow_type = ICE_FLTR_PTYPE_NONF_IPV6_UDP;

			अगर (hdr->field_selector) अणु
				अगर (l3 == VIRTCHNL_PROTO_HDR_IPV4) अणु
					input->ip.v4.src_port = udph->source;
					input->ip.v4.dst_port = udph->dest;
				पूर्ण अन्यथा अगर (l3 == VIRTCHNL_PROTO_HDR_IPV6) अणु
					input->ip.v6.src_port = udph->source;
					input->ip.v6.dst_port = udph->dest;
				पूर्ण
			पूर्ण
			अवरोध;
		हाल VIRTCHNL_PROTO_HDR_SCTP:
			sctph = (काष्ठा sctphdr *)hdr->buffer;
			अगर (l3 == VIRTCHNL_PROTO_HDR_IPV4)
				input->flow_type =
					ICE_FLTR_PTYPE_NONF_IPV4_SCTP;
			अन्यथा अगर (l3 == VIRTCHNL_PROTO_HDR_IPV6)
				input->flow_type =
					ICE_FLTR_PTYPE_NONF_IPV6_SCTP;

			अगर (hdr->field_selector) अणु
				अगर (l3 == VIRTCHNL_PROTO_HDR_IPV4) अणु
					input->ip.v4.src_port = sctph->source;
					input->ip.v4.dst_port = sctph->dest;
				पूर्ण अन्यथा अगर (l3 == VIRTCHNL_PROTO_HDR_IPV6) अणु
					input->ip.v6.src_port = sctph->source;
					input->ip.v6.dst_port = sctph->dest;
				पूर्ण
			पूर्ण
			अवरोध;
		हाल VIRTCHNL_PROTO_HDR_L2TPV3:
			अगर (l3 == VIRTCHNL_PROTO_HDR_IPV4)
				input->flow_type = ICE_FLTR_PTYPE_NONF_IPV4_L2TPV3;
			अन्यथा अगर (l3 == VIRTCHNL_PROTO_HDR_IPV6)
				input->flow_type = ICE_FLTR_PTYPE_NONF_IPV6_L2TPV3;

			अगर (hdr->field_selector)
				input->l2tpv3_data.session_id = *((__be32 *)hdr->buffer);
			अवरोध;
		हाल VIRTCHNL_PROTO_HDR_ESP:
			esph = (काष्ठा ip_esp_hdr *)hdr->buffer;
			अगर (l3 == VIRTCHNL_PROTO_HDR_IPV4 &&
			    l4 == VIRTCHNL_PROTO_HDR_UDP)
				input->flow_type = ICE_FLTR_PTYPE_NONF_IPV4_NAT_T_ESP;
			अन्यथा अगर (l3 == VIRTCHNL_PROTO_HDR_IPV6 &&
				 l4 == VIRTCHNL_PROTO_HDR_UDP)
				input->flow_type = ICE_FLTR_PTYPE_NONF_IPV6_NAT_T_ESP;
			अन्यथा अगर (l3 == VIRTCHNL_PROTO_HDR_IPV4 &&
				 l4 == VIRTCHNL_PROTO_HDR_NONE)
				input->flow_type = ICE_FLTR_PTYPE_NONF_IPV4_ESP;
			अन्यथा अगर (l3 == VIRTCHNL_PROTO_HDR_IPV6 &&
				 l4 == VIRTCHNL_PROTO_HDR_NONE)
				input->flow_type = ICE_FLTR_PTYPE_NONF_IPV6_ESP;

			अगर (l4 == VIRTCHNL_PROTO_HDR_UDP)
				conf->inset_flag |= Fसूची_INSET_FLAG_ESP_UDP;
			अन्यथा
				conf->inset_flag |= Fसूची_INSET_FLAG_ESP_IPSEC;

			अगर (hdr->field_selector) अणु
				अगर (l3 == VIRTCHNL_PROTO_HDR_IPV4)
					input->ip.v4.sec_parm_idx = esph->spi;
				अन्यथा अगर (l3 == VIRTCHNL_PROTO_HDR_IPV6)
					input->ip.v6.sec_parm_idx = esph->spi;
			पूर्ण
			अवरोध;
		हाल VIRTCHNL_PROTO_HDR_AH:
			ah = (काष्ठा ip_auth_hdr *)hdr->buffer;
			अगर (l3 == VIRTCHNL_PROTO_HDR_IPV4)
				input->flow_type = ICE_FLTR_PTYPE_NONF_IPV4_AH;
			अन्यथा अगर (l3 == VIRTCHNL_PROTO_HDR_IPV6)
				input->flow_type = ICE_FLTR_PTYPE_NONF_IPV6_AH;

			अगर (hdr->field_selector) अणु
				अगर (l3 == VIRTCHNL_PROTO_HDR_IPV4)
					input->ip.v4.sec_parm_idx = ah->spi;
				अन्यथा अगर (l3 == VIRTCHNL_PROTO_HDR_IPV6)
					input->ip.v6.sec_parm_idx = ah->spi;
			पूर्ण
			अवरोध;
		हाल VIRTCHNL_PROTO_HDR_PFCP:
			rawh = (u8 *)hdr->buffer;
			s_field = (rawh[0] >> PFCP_S_OFFSET) & PFCP_S_MASK;
			अगर (l3 == VIRTCHNL_PROTO_HDR_IPV4 && s_field == 0)
				input->flow_type = ICE_FLTR_PTYPE_NONF_IPV4_PFCP_NODE;
			अन्यथा अगर (l3 == VIRTCHNL_PROTO_HDR_IPV4 && s_field == 1)
				input->flow_type = ICE_FLTR_PTYPE_NONF_IPV4_PFCP_SESSION;
			अन्यथा अगर (l3 == VIRTCHNL_PROTO_HDR_IPV6 && s_field == 0)
				input->flow_type = ICE_FLTR_PTYPE_NONF_IPV6_PFCP_NODE;
			अन्यथा अगर (l3 == VIRTCHNL_PROTO_HDR_IPV6 && s_field == 1)
				input->flow_type = ICE_FLTR_PTYPE_NONF_IPV6_PFCP_SESSION;

			अगर (hdr->field_selector) अणु
				अगर (l3 == VIRTCHNL_PROTO_HDR_IPV4)
					input->ip.v4.dst_port = cpu_to_be16(PFCP_PORT_NR);
				अन्यथा अगर (l3 == VIRTCHNL_PROTO_HDR_IPV6)
					input->ip.v6.dst_port = cpu_to_be16(PFCP_PORT_NR);
			पूर्ण
			अवरोध;
		हाल VIRTCHNL_PROTO_HDR_GTPU_IP:
			rawh = (u8 *)hdr->buffer;
			input->flow_type = ICE_FLTR_PTYPE_NONF_IPV4_GTPU_IPV4_OTHER;

			अगर (hdr->field_selector)
				input->gtpu_data.teid = *(__be32 *)(&rawh[GTPU_TEID_OFFSET]);
			conf->ttype = ICE_Fसूची_TUNNEL_TYPE_GTPU;
			अवरोध;
		हाल VIRTCHNL_PROTO_HDR_GTPU_EH:
			rawh = (u8 *)hdr->buffer;

			अगर (hdr->field_selector)
				input->gtpu_data.qfi = rawh[GTPU_EH_QFI_OFFSET] & GTPU_EH_QFI_MASK;
			conf->ttype = ICE_Fसूची_TUNNEL_TYPE_GTPU_EH;
			अवरोध;
		शेष:
			dev_dbg(dev, "Invalid header type 0x:%x for VF %d\n",
				hdr->type, vf->vf_id);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ice_vc_fdir_parse_action
 * @vf: poपूर्णांकer to the VF info
 * @fltr: भव channel add cmd buffer
 * @conf: Fसूची configuration क्रम each filter
 *
 * Parse the भव channel filter's action and store them पूर्णांकo conf
 *
 * Return: 0 on success, and other on error.
 */
अटल पूर्णांक
ice_vc_fdir_parse_action(काष्ठा ice_vf *vf, काष्ठा virtchnl_fdir_add *fltr,
			 काष्ठा virtchnl_fdir_fltr_conf *conf)
अणु
	काष्ठा virtchnl_filter_action_set *as = &fltr->rule_cfg.action_set;
	काष्ठा device *dev = ice_pf_to_dev(vf->pf);
	काष्ठा ice_fdir_fltr *input = &conf->input;
	u32 dest_num = 0;
	u32 mark_num = 0;
	पूर्णांक i;

	अगर (as->count > VIRTCHNL_MAX_NUM_ACTIONS) अणु
		dev_dbg(dev, "Invalid action numbers:0x%x for VF %d\n",
			as->count, vf->vf_id);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < as->count; i++) अणु
		काष्ठा virtchnl_filter_action *action = &as->actions[i];

		चयन (action->type) अणु
		हाल VIRTCHNL_ACTION_PASSTHRU:
			dest_num++;
			input->dest_ctl = ICE_FLTR_PRGM_DESC_DEST_सूचीECT_PKT_OTHER;
			अवरोध;
		हाल VIRTCHNL_ACTION_DROP:
			dest_num++;
			input->dest_ctl = ICE_FLTR_PRGM_DESC_DEST_DROP_PKT;
			अवरोध;
		हाल VIRTCHNL_ACTION_QUEUE:
			dest_num++;
			input->dest_ctl = ICE_FLTR_PRGM_DESC_DEST_सूचीECT_PKT_QINDEX;
			input->q_index = action->act_conf.queue.index;
			अवरोध;
		हाल VIRTCHNL_ACTION_Q_REGION:
			dest_num++;
			input->dest_ctl = ICE_FLTR_PRGM_DESC_DEST_सूचीECT_PKT_QGROUP;
			input->q_index = action->act_conf.queue.index;
			input->q_region = action->act_conf.queue.region;
			अवरोध;
		हाल VIRTCHNL_ACTION_MARK:
			mark_num++;
			input->fltr_id = action->act_conf.mark_id;
			input->fdid_prio = ICE_FXD_FLTR_QW1_FDID_PRI_THREE;
			अवरोध;
		शेष:
			dev_dbg(dev, "Invalid action type:0x%x for VF %d\n",
				action->type, vf->vf_id);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (dest_num == 0 || dest_num >= 2) अणु
		dev_dbg(dev, "Invalid destination action for VF %d\n",
			vf->vf_id);
		वापस -EINVAL;
	पूर्ण

	अगर (mark_num >= 2) अणु
		dev_dbg(dev, "Too many mark actions for VF %d\n", vf->vf_id);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ice_vc_validate_fdir_fltr - validate the भव channel filter
 * @vf: poपूर्णांकer to the VF info
 * @fltr: भव channel add cmd buffer
 * @conf: Fसूची configuration क्रम each filter
 *
 * Return: 0 on success, and other on error.
 */
अटल पूर्णांक
ice_vc_validate_fdir_fltr(काष्ठा ice_vf *vf, काष्ठा virtchnl_fdir_add *fltr,
			  काष्ठा virtchnl_fdir_fltr_conf *conf)
अणु
	पूर्णांक ret;

	ret = ice_vc_fdir_search_pattern(vf, fltr);
	अगर (ret)
		वापस ret;

	ret = ice_vc_fdir_parse_pattern(vf, fltr, conf);
	अगर (ret)
		वापस ret;

	वापस ice_vc_fdir_parse_action(vf, fltr, conf);
पूर्ण

/**
 * ice_vc_fdir_comp_rules - compare अगर two filter rules have the same value
 * @conf_a: Fसूची configuration क्रम filter a
 * @conf_b: Fसूची configuration क्रम filter b
 *
 * Return: 0 on success, and other on error.
 */
अटल bool
ice_vc_fdir_comp_rules(काष्ठा virtchnl_fdir_fltr_conf *conf_a,
		       काष्ठा virtchnl_fdir_fltr_conf *conf_b)
अणु
	काष्ठा ice_fdir_fltr *a = &conf_a->input;
	काष्ठा ice_fdir_fltr *b = &conf_b->input;

	अगर (conf_a->ttype != conf_b->ttype)
		वापस false;
	अगर (a->flow_type != b->flow_type)
		वापस false;
	अगर (स_भेद(&a->ip, &b->ip, माप(a->ip)))
		वापस false;
	अगर (स_भेद(&a->mask, &b->mask, माप(a->mask)))
		वापस false;
	अगर (स_भेद(&a->gtpu_data, &b->gtpu_data, माप(a->gtpu_data)))
		वापस false;
	अगर (स_भेद(&a->gtpu_mask, &b->gtpu_mask, माप(a->gtpu_mask)))
		वापस false;
	अगर (स_भेद(&a->l2tpv3_data, &b->l2tpv3_data, माप(a->l2tpv3_data)))
		वापस false;
	अगर (स_भेद(&a->l2tpv3_mask, &b->l2tpv3_mask, माप(a->l2tpv3_mask)))
		वापस false;
	अगर (स_भेद(&a->ext_data, &b->ext_data, माप(a->ext_data)))
		वापस false;
	अगर (स_भेद(&a->ext_mask, &b->ext_mask, माप(a->ext_mask)))
		वापस false;

	वापस true;
पूर्ण

/**
 * ice_vc_fdir_is_dup_fltr
 * @vf: poपूर्णांकer to the VF info
 * @conf: Fसूची configuration क्रम each filter
 *
 * Check अगर there is duplicated rule with same conf value
 *
 * Return: 0 true success, and false on error.
 */
अटल bool
ice_vc_fdir_is_dup_fltr(काष्ठा ice_vf *vf, काष्ठा virtchnl_fdir_fltr_conf *conf)
अणु
	काष्ठा ice_fdir_fltr *desc;
	bool ret;

	list_क्रम_each_entry(desc, &vf->fdir.fdir_rule_list, fltr_node) अणु
		काष्ठा virtchnl_fdir_fltr_conf *node =
				to_fltr_conf_from_desc(desc);

		ret = ice_vc_fdir_comp_rules(node, conf);
		अगर (ret)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/**
 * ice_vc_fdir_insert_entry
 * @vf: poपूर्णांकer to the VF info
 * @conf: Fसूची configuration क्रम each filter
 * @id: poपूर्णांकer to ID value allocated by driver
 *
 * Insert Fसूची conf entry पूर्णांकo list and allocate ID क्रम this filter
 *
 * Return: 0 true success, and other on error.
 */
अटल पूर्णांक
ice_vc_fdir_insert_entry(काष्ठा ice_vf *vf,
			 काष्ठा virtchnl_fdir_fltr_conf *conf, u32 *id)
अणु
	काष्ठा ice_fdir_fltr *input = &conf->input;
	पूर्णांक i;

	/* alloc ID corresponding with conf */
	i = idr_alloc(&vf->fdir.fdir_rule_idr, conf, 0,
		      ICE_Fसूची_MAX_FLTRS, GFP_KERNEL);
	अगर (i < 0)
		वापस -EINVAL;
	*id = i;

	list_add(&input->fltr_node, &vf->fdir.fdir_rule_list);
	वापस 0;
पूर्ण

/**
 * ice_vc_fdir_हटाओ_entry - हटाओ Fसूची conf entry by ID value
 * @vf: poपूर्णांकer to the VF info
 * @conf: Fसूची configuration क्रम each filter
 * @id: filter rule's ID
 */
अटल व्योम
ice_vc_fdir_हटाओ_entry(काष्ठा ice_vf *vf,
			 काष्ठा virtchnl_fdir_fltr_conf *conf, u32 id)
अणु
	काष्ठा ice_fdir_fltr *input = &conf->input;

	idr_हटाओ(&vf->fdir.fdir_rule_idr, id);
	list_del(&input->fltr_node);
पूर्ण

/**
 * ice_vc_fdir_lookup_entry - lookup Fसूची conf entry by ID value
 * @vf: poपूर्णांकer to the VF info
 * @id: filter rule's ID
 *
 * Return: शून्य on error, and other on success.
 */
अटल काष्ठा virtchnl_fdir_fltr_conf *
ice_vc_fdir_lookup_entry(काष्ठा ice_vf *vf, u32 id)
अणु
	वापस idr_find(&vf->fdir.fdir_rule_idr, id);
पूर्ण

/**
 * ice_vc_fdir_flush_entry - हटाओ all Fसूची conf entry
 * @vf: poपूर्णांकer to the VF info
 */
अटल व्योम ice_vc_fdir_flush_entry(काष्ठा ice_vf *vf)
अणु
	काष्ठा virtchnl_fdir_fltr_conf *conf;
	काष्ठा ice_fdir_fltr *desc, *temp;

	list_क्रम_each_entry_safe(desc, temp,
				 &vf->fdir.fdir_rule_list, fltr_node) अणु
		conf = to_fltr_conf_from_desc(desc);
		list_del(&desc->fltr_node);
		devm_kमुक्त(ice_pf_to_dev(vf->pf), conf);
	पूर्ण
पूर्ण

/**
 * ice_vc_fdir_ग_लिखो_fltr - ग_लिखो filter rule पूर्णांकo hardware
 * @vf: poपूर्णांकer to the VF info
 * @conf: Fसूची configuration क्रम each filter
 * @add: true implies add rule, false implies del rules
 * @is_tun: false implies non-tunnel type filter, true implies tunnel filter
 *
 * Return: 0 on success, and other on error.
 */
अटल पूर्णांक ice_vc_fdir_ग_लिखो_fltr(काष्ठा ice_vf *vf,
				  काष्ठा virtchnl_fdir_fltr_conf *conf,
				  bool add, bool is_tun)
अणु
	काष्ठा ice_fdir_fltr *input = &conf->input;
	काष्ठा ice_vsi *vsi, *ctrl_vsi;
	काष्ठा ice_fltr_desc desc;
	क्रमागत ice_status status;
	काष्ठा device *dev;
	काष्ठा ice_pf *pf;
	काष्ठा ice_hw *hw;
	पूर्णांक ret;
	u8 *pkt;

	pf = vf->pf;
	dev = ice_pf_to_dev(pf);
	hw = &pf->hw;
	vsi = pf->vsi[vf->lan_vsi_idx];
	अगर (!vsi) अणु
		dev_dbg(dev, "Invalid vsi for VF %d\n", vf->vf_id);
		वापस -EINVAL;
	पूर्ण

	input->dest_vsi = vsi->idx;
	input->comp_report = ICE_FXD_FLTR_QW0_COMP_REPORT_SW;

	ctrl_vsi = pf->vsi[vf->ctrl_vsi_idx];
	अगर (!ctrl_vsi) अणु
		dev_dbg(dev, "Invalid ctrl_vsi for VF %d\n", vf->vf_id);
		वापस -EINVAL;
	पूर्ण

	pkt = devm_kzalloc(dev, ICE_Fसूची_MAX_RAW_PKT_SIZE, GFP_KERNEL);
	अगर (!pkt)
		वापस -ENOMEM;

	ice_fdir_get_prgm_desc(hw, input, &desc, add);
	status = ice_fdir_get_gen_prgm_pkt(hw, input, pkt, false, is_tun);
	ret = ice_status_to_त्रुटि_सं(status);
	अगर (ret) अणु
		dev_dbg(dev, "Gen training pkt for VF %d ptype %d failed\n",
			vf->vf_id, input->flow_type);
		जाओ err_मुक्त_pkt;
	पूर्ण

	ret = ice_prgm_fdir_fltr(ctrl_vsi, &desc, pkt);
	अगर (ret)
		जाओ err_मुक्त_pkt;

	वापस 0;

err_मुक्त_pkt:
	devm_kमुक्त(dev, pkt);
	वापस ret;
पूर्ण

/**
 * ice_vf_fdir_समयr - Fसूची program रुकोing समयr पूर्णांकerrupt handler
 * @t: poपूर्णांकer to समयr_list
 */
अटल व्योम ice_vf_fdir_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा ice_vf_fdir_ctx *ctx_irq = from_समयr(ctx_irq, t, rx_पंचांगr);
	काष्ठा ice_vf_fdir_ctx *ctx_करोne;
	काष्ठा ice_vf_fdir *fdir;
	अचिन्हित दीर्घ flags;
	काष्ठा ice_vf *vf;
	काष्ठा ice_pf *pf;

	fdir = container_of(ctx_irq, काष्ठा ice_vf_fdir, ctx_irq);
	vf = container_of(fdir, काष्ठा ice_vf, fdir);
	ctx_करोne = &fdir->ctx_करोne;
	pf = vf->pf;
	spin_lock_irqsave(&fdir->ctx_lock, flags);
	अगर (!(ctx_irq->flags & ICE_VF_Fसूची_CTX_VALID)) अणु
		spin_unlock_irqrestore(&fdir->ctx_lock, flags);
		WARN_ON_ONCE(1);
		वापस;
	पूर्ण

	ctx_irq->flags &= ~ICE_VF_Fसूची_CTX_VALID;

	ctx_करोne->flags |= ICE_VF_Fसूची_CTX_VALID;
	ctx_करोne->conf = ctx_irq->conf;
	ctx_करोne->stat = ICE_Fसूची_CTX_TIMEOUT;
	ctx_करोne->v_opcode = ctx_irq->v_opcode;
	spin_unlock_irqrestore(&fdir->ctx_lock, flags);

	set_bit(ICE_FD_VF_FLUSH_CTX, pf->state);
	ice_service_task_schedule(pf);
पूर्ण

/**
 * ice_vc_fdir_irq_handler - ctrl_vsi Rx queue पूर्णांकerrupt handler
 * @ctrl_vsi: poपूर्णांकer to a VF's CTRL VSI
 * @rx_desc: poपूर्णांकer to Fसूची Rx queue descriptor
 */
व्योम
ice_vc_fdir_irq_handler(काष्ठा ice_vsi *ctrl_vsi,
			जोड़ ice_32b_rx_flex_desc *rx_desc)
अणु
	काष्ठा ice_pf *pf = ctrl_vsi->back;
	काष्ठा ice_vf_fdir_ctx *ctx_करोne;
	काष्ठा ice_vf_fdir_ctx *ctx_irq;
	काष्ठा ice_vf_fdir *fdir;
	अचिन्हित दीर्घ flags;
	काष्ठा device *dev;
	काष्ठा ice_vf *vf;
	पूर्णांक ret;

	vf = &pf->vf[ctrl_vsi->vf_id];

	fdir = &vf->fdir;
	ctx_करोne = &fdir->ctx_करोne;
	ctx_irq = &fdir->ctx_irq;
	dev = ice_pf_to_dev(pf);
	spin_lock_irqsave(&fdir->ctx_lock, flags);
	अगर (!(ctx_irq->flags & ICE_VF_Fसूची_CTX_VALID)) अणु
		spin_unlock_irqrestore(&fdir->ctx_lock, flags);
		WARN_ON_ONCE(1);
		वापस;
	पूर्ण

	ctx_irq->flags &= ~ICE_VF_Fसूची_CTX_VALID;

	ctx_करोne->flags |= ICE_VF_Fसूची_CTX_VALID;
	ctx_करोne->conf = ctx_irq->conf;
	ctx_करोne->stat = ICE_Fसूची_CTX_IRQ;
	ctx_करोne->v_opcode = ctx_irq->v_opcode;
	स_नकल(&ctx_करोne->rx_desc, rx_desc, माप(*rx_desc));
	spin_unlock_irqrestore(&fdir->ctx_lock, flags);

	ret = del_समयr(&ctx_irq->rx_पंचांगr);
	अगर (!ret)
		dev_err(dev, "VF %d: Unexpected inactive timer!\n", vf->vf_id);

	set_bit(ICE_FD_VF_FLUSH_CTX, pf->state);
	ice_service_task_schedule(pf);
पूर्ण

/**
 * ice_vf_fdir_dump_info - dump Fसूची inक्रमmation क्रम diagnosis
 * @vf: poपूर्णांकer to the VF info
 */
अटल व्योम ice_vf_fdir_dump_info(काष्ठा ice_vf *vf)
अणु
	काष्ठा ice_vsi *vf_vsi;
	u32 fd_size, fd_cnt;
	काष्ठा device *dev;
	काष्ठा ice_pf *pf;
	काष्ठा ice_hw *hw;
	u16 vsi_num;

	pf = vf->pf;
	hw = &pf->hw;
	dev = ice_pf_to_dev(pf);
	vf_vsi = pf->vsi[vf->lan_vsi_idx];
	vsi_num = ice_get_hw_vsi_num(hw, vf_vsi->idx);

	fd_size = rd32(hw, VSIQF_FD_SIZE(vsi_num));
	fd_cnt = rd32(hw, VSIQF_FD_CNT(vsi_num));
	dev_dbg(dev, "VF %d: space allocated: guar:0x%x, be:0x%x, space consumed: guar:0x%x, be:0x%x",
		vf->vf_id,
		(fd_size & VSIQF_FD_CNT_FD_GCNT_M) >> VSIQF_FD_CNT_FD_GCNT_S,
		(fd_size & VSIQF_FD_CNT_FD_BCNT_M) >> VSIQF_FD_CNT_FD_BCNT_S,
		(fd_cnt & VSIQF_FD_CNT_FD_GCNT_M) >> VSIQF_FD_CNT_FD_GCNT_S,
		(fd_cnt & VSIQF_FD_CNT_FD_BCNT_M) >> VSIQF_FD_CNT_FD_BCNT_S);
पूर्ण

/**
 * ice_vf_verअगरy_rx_desc - verअगरy received Fसूची programming status descriptor
 * @vf: poपूर्णांकer to the VF info
 * @ctx: Fसूची context info क्रम post processing
 * @status: virtchnl Fसूची program status
 *
 * Return: 0 on success, and other on error.
 */
अटल पूर्णांक
ice_vf_verअगरy_rx_desc(काष्ठा ice_vf *vf, काष्ठा ice_vf_fdir_ctx *ctx,
		      क्रमागत virtchnl_fdir_prgm_status *status)
अणु
	काष्ठा device *dev = ice_pf_to_dev(vf->pf);
	u32 stat_err, error, prog_id;
	पूर्णांक ret;

	stat_err = le16_to_cpu(ctx->rx_desc.wb.status_error0);
	अगर (((stat_err & ICE_FXD_FLTR_WB_QW1_DD_M) >>
	    ICE_FXD_FLTR_WB_QW1_DD_S) != ICE_FXD_FLTR_WB_QW1_DD_YES) अणु
		*status = VIRTCHNL_Fसूची_FAILURE_RULE_NORESOURCE;
		dev_err(dev, "VF %d: Desc Done not set\n", vf->vf_id);
		ret = -EINVAL;
		जाओ err_निकास;
	पूर्ण

	prog_id = (stat_err & ICE_FXD_FLTR_WB_QW1_PROG_ID_M) >>
		ICE_FXD_FLTR_WB_QW1_PROG_ID_S;
	अगर (prog_id == ICE_FXD_FLTR_WB_QW1_PROG_ADD &&
	    ctx->v_opcode != VIRTCHNL_OP_ADD_Fसूची_FILTER) अणु
		dev_err(dev, "VF %d: Desc show add, but ctx not",
			vf->vf_id);
		*status = VIRTCHNL_Fसूची_FAILURE_RULE_INVALID;
		ret = -EINVAL;
		जाओ err_निकास;
	पूर्ण

	अगर (prog_id == ICE_FXD_FLTR_WB_QW1_PROG_DEL &&
	    ctx->v_opcode != VIRTCHNL_OP_DEL_Fसूची_FILTER) अणु
		dev_err(dev, "VF %d: Desc show del, but ctx not",
			vf->vf_id);
		*status = VIRTCHNL_Fसूची_FAILURE_RULE_INVALID;
		ret = -EINVAL;
		जाओ err_निकास;
	पूर्ण

	error = (stat_err & ICE_FXD_FLTR_WB_QW1_FAIL_M) >>
		ICE_FXD_FLTR_WB_QW1_FAIL_S;
	अगर (error == ICE_FXD_FLTR_WB_QW1_FAIL_YES) अणु
		अगर (prog_id == ICE_FXD_FLTR_WB_QW1_PROG_ADD) अणु
			dev_err(dev, "VF %d, Failed to add FDIR rule due to no space in the table",
				vf->vf_id);
			*status = VIRTCHNL_Fसूची_FAILURE_RULE_NORESOURCE;
		पूर्ण अन्यथा अणु
			dev_err(dev, "VF %d, Failed to remove FDIR rule, attempt to remove non-existent entry",
				vf->vf_id);
			*status = VIRTCHNL_Fसूची_FAILURE_RULE_NONEXIST;
		पूर्ण
		ret = -EINVAL;
		जाओ err_निकास;
	पूर्ण

	error = (stat_err & ICE_FXD_FLTR_WB_QW1_FAIL_PROF_M) >>
		ICE_FXD_FLTR_WB_QW1_FAIL_PROF_S;
	अगर (error == ICE_FXD_FLTR_WB_QW1_FAIL_PROF_YES) अणु
		dev_err(dev, "VF %d: Profile matching error", vf->vf_id);
		*status = VIRTCHNL_Fसूची_FAILURE_RULE_NORESOURCE;
		ret = -EINVAL;
		जाओ err_निकास;
	पूर्ण

	*status = VIRTCHNL_Fसूची_SUCCESS;

	वापस 0;

err_निकास:
	ice_vf_fdir_dump_info(vf);
	वापस ret;
पूर्ण

/**
 * ice_vc_add_fdir_fltr_post
 * @vf: poपूर्णांकer to the VF काष्ठाure
 * @ctx: Fसूची context info क्रम post processing
 * @status: virtchnl Fसूची program status
 * @success: true implies success, false implies failure
 *
 * Post process क्रम flow director add command. If success, then करो post process
 * and send back success msg by virtchnl. Otherwise, करो context reversion and
 * send back failure msg by virtchnl.
 *
 * Return: 0 on success, and other on error.
 */
अटल पूर्णांक
ice_vc_add_fdir_fltr_post(काष्ठा ice_vf *vf, काष्ठा ice_vf_fdir_ctx *ctx,
			  क्रमागत virtchnl_fdir_prgm_status status,
			  bool success)
अणु
	काष्ठा virtchnl_fdir_fltr_conf *conf = ctx->conf;
	काष्ठा device *dev = ice_pf_to_dev(vf->pf);
	क्रमागत virtchnl_status_code v_ret;
	काष्ठा virtchnl_fdir_add *resp;
	पूर्णांक ret, len, is_tun;

	v_ret = VIRTCHNL_STATUS_SUCCESS;
	len = माप(*resp);
	resp = kzalloc(len, GFP_KERNEL);
	अगर (!resp) अणु
		len = 0;
		v_ret = VIRTCHNL_STATUS_ERR_NO_MEMORY;
		dev_dbg(dev, "VF %d: Alloc resp buf fail", vf->vf_id);
		जाओ err_निकास;
	पूर्ण

	अगर (!success)
		जाओ err_निकास;

	is_tun = 0;
	resp->status = status;
	resp->flow_id = conf->flow_id;
	vf->fdir.fdir_fltr_cnt[conf->input.flow_type][is_tun]++;

	ret = ice_vc_send_msg_to_vf(vf, ctx->v_opcode, v_ret,
				    (u8 *)resp, len);
	kमुक्त(resp);

	dev_dbg(dev, "VF %d: flow_id:0x%X, FDIR %s success!\n",
		vf->vf_id, conf->flow_id,
		(ctx->v_opcode == VIRTCHNL_OP_ADD_Fसूची_FILTER) ?
		"add" : "del");
	वापस ret;

err_निकास:
	अगर (resp)
		resp->status = status;
	ice_vc_fdir_हटाओ_entry(vf, conf, conf->flow_id);
	devm_kमुक्त(dev, conf);

	ret = ice_vc_send_msg_to_vf(vf, ctx->v_opcode, v_ret,
				    (u8 *)resp, len);
	kमुक्त(resp);
	वापस ret;
पूर्ण

/**
 * ice_vc_del_fdir_fltr_post
 * @vf: poपूर्णांकer to the VF काष्ठाure
 * @ctx: Fसूची context info क्रम post processing
 * @status: virtchnl Fसूची program status
 * @success: true implies success, false implies failure
 *
 * Post process क्रम flow director del command. If success, then करो post process
 * and send back success msg by virtchnl. Otherwise, करो context reversion and
 * send back failure msg by virtchnl.
 *
 * Return: 0 on success, and other on error.
 */
अटल पूर्णांक
ice_vc_del_fdir_fltr_post(काष्ठा ice_vf *vf, काष्ठा ice_vf_fdir_ctx *ctx,
			  क्रमागत virtchnl_fdir_prgm_status status,
			  bool success)
अणु
	काष्ठा virtchnl_fdir_fltr_conf *conf = ctx->conf;
	काष्ठा device *dev = ice_pf_to_dev(vf->pf);
	क्रमागत virtchnl_status_code v_ret;
	काष्ठा virtchnl_fdir_del *resp;
	पूर्णांक ret, len, is_tun;

	v_ret = VIRTCHNL_STATUS_SUCCESS;
	len = माप(*resp);
	resp = kzalloc(len, GFP_KERNEL);
	अगर (!resp) अणु
		len = 0;
		v_ret = VIRTCHNL_STATUS_ERR_NO_MEMORY;
		dev_dbg(dev, "VF %d: Alloc resp buf fail", vf->vf_id);
		जाओ err_निकास;
	पूर्ण

	अगर (!success)
		जाओ err_निकास;

	is_tun = 0;
	resp->status = status;
	ice_vc_fdir_हटाओ_entry(vf, conf, conf->flow_id);
	vf->fdir.fdir_fltr_cnt[conf->input.flow_type][is_tun]--;

	ret = ice_vc_send_msg_to_vf(vf, ctx->v_opcode, v_ret,
				    (u8 *)resp, len);
	kमुक्त(resp);

	dev_dbg(dev, "VF %d: flow_id:0x%X, FDIR %s success!\n",
		vf->vf_id, conf->flow_id,
		(ctx->v_opcode == VIRTCHNL_OP_ADD_Fसूची_FILTER) ?
		"add" : "del");
	devm_kमुक्त(dev, conf);
	वापस ret;

err_निकास:
	अगर (resp)
		resp->status = status;
	अगर (success)
		devm_kमुक्त(dev, conf);

	ret = ice_vc_send_msg_to_vf(vf, ctx->v_opcode, v_ret,
				    (u8 *)resp, len);
	kमुक्त(resp);
	वापस ret;
पूर्ण

/**
 * ice_flush_fdir_ctx
 * @pf: poपूर्णांकer to the PF काष्ठाure
 *
 * Flush all the pending event on ctx_करोne list and process them.
 */
व्योम ice_flush_fdir_ctx(काष्ठा ice_pf *pf)
अणु
	पूर्णांक i;

	अगर (!test_and_clear_bit(ICE_FD_VF_FLUSH_CTX, pf->state))
		वापस;

	ice_क्रम_each_vf(pf, i) अणु
		काष्ठा device *dev = ice_pf_to_dev(pf);
		क्रमागत virtchnl_fdir_prgm_status status;
		काष्ठा ice_vf *vf = &pf->vf[i];
		काष्ठा ice_vf_fdir_ctx *ctx;
		अचिन्हित दीर्घ flags;
		पूर्णांक ret;

		अगर (!test_bit(ICE_VF_STATE_ACTIVE, vf->vf_states))
			जारी;

		अगर (vf->ctrl_vsi_idx == ICE_NO_VSI)
			जारी;

		ctx = &vf->fdir.ctx_करोne;
		spin_lock_irqsave(&vf->fdir.ctx_lock, flags);
		अगर (!(ctx->flags & ICE_VF_Fसूची_CTX_VALID)) अणु
			spin_unlock_irqrestore(&vf->fdir.ctx_lock, flags);
			जारी;
		पूर्ण
		spin_unlock_irqrestore(&vf->fdir.ctx_lock, flags);

		WARN_ON(ctx->stat == ICE_Fसूची_CTX_READY);
		अगर (ctx->stat == ICE_Fसूची_CTX_TIMEOUT) अणु
			status = VIRTCHNL_Fसूची_FAILURE_RULE_TIMEOUT;
			dev_err(dev, "VF %d: ctrl_vsi irq timeout\n",
				vf->vf_id);
			जाओ err_निकास;
		पूर्ण

		ret = ice_vf_verअगरy_rx_desc(vf, ctx, &status);
		अगर (ret)
			जाओ err_निकास;

		अगर (ctx->v_opcode == VIRTCHNL_OP_ADD_Fसूची_FILTER)
			ice_vc_add_fdir_fltr_post(vf, ctx, status, true);
		अन्यथा अगर (ctx->v_opcode == VIRTCHNL_OP_DEL_Fसूची_FILTER)
			ice_vc_del_fdir_fltr_post(vf, ctx, status, true);
		अन्यथा
			dev_err(dev, "VF %d: Unsupported opcode\n", vf->vf_id);

		spin_lock_irqsave(&vf->fdir.ctx_lock, flags);
		ctx->flags &= ~ICE_VF_Fसूची_CTX_VALID;
		spin_unlock_irqrestore(&vf->fdir.ctx_lock, flags);
		जारी;
err_निकास:
		अगर (ctx->v_opcode == VIRTCHNL_OP_ADD_Fसूची_FILTER)
			ice_vc_add_fdir_fltr_post(vf, ctx, status, false);
		अन्यथा अगर (ctx->v_opcode == VIRTCHNL_OP_DEL_Fसूची_FILTER)
			ice_vc_del_fdir_fltr_post(vf, ctx, status, false);
		अन्यथा
			dev_err(dev, "VF %d: Unsupported opcode\n", vf->vf_id);

		spin_lock_irqsave(&vf->fdir.ctx_lock, flags);
		ctx->flags &= ~ICE_VF_Fसूची_CTX_VALID;
		spin_unlock_irqrestore(&vf->fdir.ctx_lock, flags);
	पूर्ण
पूर्ण

/**
 * ice_vc_fdir_set_irq_ctx - set Fसूची context info क्रम later IRQ handler
 * @vf: poपूर्णांकer to the VF काष्ठाure
 * @conf: Fसूची configuration क्रम each filter
 * @v_opcode: भव channel operation code
 *
 * Return: 0 on success, and other on error.
 */
अटल पूर्णांक
ice_vc_fdir_set_irq_ctx(काष्ठा ice_vf *vf, काष्ठा virtchnl_fdir_fltr_conf *conf,
			क्रमागत virtchnl_ops v_opcode)
अणु
	काष्ठा device *dev = ice_pf_to_dev(vf->pf);
	काष्ठा ice_vf_fdir_ctx *ctx;
	अचिन्हित दीर्घ flags;

	ctx = &vf->fdir.ctx_irq;
	spin_lock_irqsave(&vf->fdir.ctx_lock, flags);
	अगर ((vf->fdir.ctx_irq.flags & ICE_VF_Fसूची_CTX_VALID) ||
	    (vf->fdir.ctx_करोne.flags & ICE_VF_Fसूची_CTX_VALID)) अणु
		spin_unlock_irqrestore(&vf->fdir.ctx_lock, flags);
		dev_dbg(dev, "VF %d: Last request is still in progress\n",
			vf->vf_id);
		वापस -EBUSY;
	पूर्ण
	ctx->flags |= ICE_VF_Fसूची_CTX_VALID;
	spin_unlock_irqrestore(&vf->fdir.ctx_lock, flags);

	ctx->conf = conf;
	ctx->v_opcode = v_opcode;
	ctx->stat = ICE_Fसूची_CTX_READY;
	समयr_setup(&ctx->rx_पंचांगr, ice_vf_fdir_समयr, 0);

	mod_समयr(&ctx->rx_पंचांगr, round_jअगरfies(msecs_to_jअगरfies(10) + jअगरfies));

	वापस 0;
पूर्ण

/**
 * ice_vc_fdir_clear_irq_ctx - clear Fसूची context info क्रम IRQ handler
 * @vf: poपूर्णांकer to the VF काष्ठाure
 *
 * Return: 0 on success, and other on error.
 */
अटल व्योम ice_vc_fdir_clear_irq_ctx(काष्ठा ice_vf *vf)
अणु
	काष्ठा ice_vf_fdir_ctx *ctx = &vf->fdir.ctx_irq;
	अचिन्हित दीर्घ flags;

	del_समयr(&ctx->rx_पंचांगr);
	spin_lock_irqsave(&vf->fdir.ctx_lock, flags);
	ctx->flags &= ~ICE_VF_Fसूची_CTX_VALID;
	spin_unlock_irqrestore(&vf->fdir.ctx_lock, flags);
पूर्ण

/**
 * ice_vc_add_fdir_fltr - add a Fसूची filter क्रम VF by the msg buffer
 * @vf: poपूर्णांकer to the VF info
 * @msg: poपूर्णांकer to the msg buffer
 *
 * Return: 0 on success, and other on error.
 */
पूर्णांक ice_vc_add_fdir_fltr(काष्ठा ice_vf *vf, u8 *msg)
अणु
	काष्ठा virtchnl_fdir_add *fltr = (काष्ठा virtchnl_fdir_add *)msg;
	काष्ठा virtchnl_fdir_add *stat = शून्य;
	काष्ठा virtchnl_fdir_fltr_conf *conf;
	क्रमागत virtchnl_status_code v_ret;
	काष्ठा device *dev;
	काष्ठा ice_pf *pf;
	पूर्णांक is_tun = 0;
	पूर्णांक len = 0;
	पूर्णांक ret;

	pf = vf->pf;
	dev = ice_pf_to_dev(pf);
	ret = ice_vc_fdir_param_check(vf, fltr->vsi_id);
	अगर (ret) अणु
		v_ret = VIRTCHNL_STATUS_ERR_PARAM;
		dev_dbg(dev, "Parameter check for VF %d failed\n", vf->vf_id);
		जाओ err_निकास;
	पूर्ण

	ret = ice_vf_start_ctrl_vsi(vf);
	अगर (ret && (ret != -EEXIST)) अणु
		v_ret = VIRTCHNL_STATUS_ERR_PARAM;
		dev_err(dev, "Init FDIR for VF %d failed, ret:%d\n",
			vf->vf_id, ret);
		जाओ err_निकास;
	पूर्ण

	stat = kzalloc(माप(*stat), GFP_KERNEL);
	अगर (!stat) अणु
		v_ret = VIRTCHNL_STATUS_ERR_NO_MEMORY;
		dev_dbg(dev, "Alloc stat for VF %d failed\n", vf->vf_id);
		जाओ err_निकास;
	पूर्ण

	conf = devm_kzalloc(dev, माप(*conf), GFP_KERNEL);
	अगर (!conf) अणु
		v_ret = VIRTCHNL_STATUS_ERR_NO_MEMORY;
		dev_dbg(dev, "Alloc conf for VF %d failed\n", vf->vf_id);
		जाओ err_निकास;
	पूर्ण

	len = माप(*stat);
	ret = ice_vc_validate_fdir_fltr(vf, fltr, conf);
	अगर (ret) अणु
		v_ret = VIRTCHNL_STATUS_SUCCESS;
		stat->status = VIRTCHNL_Fसूची_FAILURE_RULE_INVALID;
		dev_dbg(dev, "Invalid FDIR filter from VF %d\n", vf->vf_id);
		जाओ err_मुक्त_conf;
	पूर्ण

	अगर (fltr->validate_only) अणु
		v_ret = VIRTCHNL_STATUS_SUCCESS;
		stat->status = VIRTCHNL_Fसूची_SUCCESS;
		devm_kमुक्त(dev, conf);
		ret = ice_vc_send_msg_to_vf(vf, VIRTCHNL_OP_ADD_Fसूची_FILTER,
					    v_ret, (u8 *)stat, len);
		जाओ निकास;
	पूर्ण

	ret = ice_vc_fdir_config_input_set(vf, fltr, conf, is_tun);
	अगर (ret) अणु
		v_ret = VIRTCHNL_STATUS_SUCCESS;
		stat->status = VIRTCHNL_Fसूची_FAILURE_RULE_CONFLICT;
		dev_err(dev, "VF %d: FDIR input set configure failed, ret:%d\n",
			vf->vf_id, ret);
		जाओ err_मुक्त_conf;
	पूर्ण

	ret = ice_vc_fdir_is_dup_fltr(vf, conf);
	अगर (ret) अणु
		v_ret = VIRTCHNL_STATUS_SUCCESS;
		stat->status = VIRTCHNL_Fसूची_FAILURE_RULE_EXIST;
		dev_dbg(dev, "VF %d: duplicated FDIR rule detected\n",
			vf->vf_id);
		जाओ err_मुक्त_conf;
	पूर्ण

	ret = ice_vc_fdir_insert_entry(vf, conf, &conf->flow_id);
	अगर (ret) अणु
		v_ret = VIRTCHNL_STATUS_SUCCESS;
		stat->status = VIRTCHNL_Fसूची_FAILURE_RULE_NORESOURCE;
		dev_dbg(dev, "VF %d: insert FDIR list failed\n", vf->vf_id);
		जाओ err_मुक्त_conf;
	पूर्ण

	ret = ice_vc_fdir_set_irq_ctx(vf, conf, VIRTCHNL_OP_ADD_Fसूची_FILTER);
	अगर (ret) अणु
		v_ret = VIRTCHNL_STATUS_SUCCESS;
		stat->status = VIRTCHNL_Fसूची_FAILURE_RULE_NORESOURCE;
		dev_dbg(dev, "VF %d: set FDIR context failed\n", vf->vf_id);
		जाओ err_मुक्त_conf;
	पूर्ण

	ret = ice_vc_fdir_ग_लिखो_fltr(vf, conf, true, is_tun);
	अगर (ret) अणु
		v_ret = VIRTCHNL_STATUS_SUCCESS;
		stat->status = VIRTCHNL_Fसूची_FAILURE_RULE_NORESOURCE;
		dev_err(dev, "VF %d: writing FDIR rule failed, ret:%d\n",
			vf->vf_id, ret);
		जाओ err_rem_entry;
	पूर्ण

निकास:
	kमुक्त(stat);
	वापस ret;

err_rem_entry:
	ice_vc_fdir_clear_irq_ctx(vf);
	ice_vc_fdir_हटाओ_entry(vf, conf, conf->flow_id);
err_मुक्त_conf:
	devm_kमुक्त(dev, conf);
err_निकास:
	ret = ice_vc_send_msg_to_vf(vf, VIRTCHNL_OP_ADD_Fसूची_FILTER, v_ret,
				    (u8 *)stat, len);
	kमुक्त(stat);
	वापस ret;
पूर्ण

/**
 * ice_vc_del_fdir_fltr - delete a Fसूची filter क्रम VF by the msg buffer
 * @vf: poपूर्णांकer to the VF info
 * @msg: poपूर्णांकer to the msg buffer
 *
 * Return: 0 on success, and other on error.
 */
पूर्णांक ice_vc_del_fdir_fltr(काष्ठा ice_vf *vf, u8 *msg)
अणु
	काष्ठा virtchnl_fdir_del *fltr = (काष्ठा virtchnl_fdir_del *)msg;
	काष्ठा virtchnl_fdir_del *stat = शून्य;
	काष्ठा virtchnl_fdir_fltr_conf *conf;
	क्रमागत virtchnl_status_code v_ret;
	काष्ठा device *dev;
	काष्ठा ice_pf *pf;
	पूर्णांक is_tun = 0;
	पूर्णांक len = 0;
	पूर्णांक ret;

	pf = vf->pf;
	dev = ice_pf_to_dev(pf);
	ret = ice_vc_fdir_param_check(vf, fltr->vsi_id);
	अगर (ret) अणु
		v_ret = VIRTCHNL_STATUS_ERR_PARAM;
		dev_dbg(dev, "Parameter check for VF %d failed\n", vf->vf_id);
		जाओ err_निकास;
	पूर्ण

	stat = kzalloc(माप(*stat), GFP_KERNEL);
	अगर (!stat) अणु
		v_ret = VIRTCHNL_STATUS_ERR_NO_MEMORY;
		dev_dbg(dev, "Alloc stat for VF %d failed\n", vf->vf_id);
		जाओ err_निकास;
	पूर्ण

	len = माप(*stat);

	conf = ice_vc_fdir_lookup_entry(vf, fltr->flow_id);
	अगर (!conf) अणु
		v_ret = VIRTCHNL_STATUS_SUCCESS;
		stat->status = VIRTCHNL_Fसूची_FAILURE_RULE_NONEXIST;
		dev_dbg(dev, "VF %d: FDIR invalid flow_id:0x%X\n",
			vf->vf_id, fltr->flow_id);
		जाओ err_निकास;
	पूर्ण

	/* Just वापस failure when ctrl_vsi idx is invalid */
	अगर (vf->ctrl_vsi_idx == ICE_NO_VSI) अणु
		v_ret = VIRTCHNL_STATUS_SUCCESS;
		stat->status = VIRTCHNL_Fसूची_FAILURE_RULE_NORESOURCE;
		dev_err(dev, "Invalid FDIR ctrl_vsi for VF %d\n", vf->vf_id);
		जाओ err_निकास;
	पूर्ण

	ret = ice_vc_fdir_set_irq_ctx(vf, conf, VIRTCHNL_OP_DEL_Fसूची_FILTER);
	अगर (ret) अणु
		v_ret = VIRTCHNL_STATUS_SUCCESS;
		stat->status = VIRTCHNL_Fसूची_FAILURE_RULE_NORESOURCE;
		dev_dbg(dev, "VF %d: set FDIR context failed\n", vf->vf_id);
		जाओ err_निकास;
	पूर्ण

	ret = ice_vc_fdir_ग_लिखो_fltr(vf, conf, false, is_tun);
	अगर (ret) अणु
		v_ret = VIRTCHNL_STATUS_SUCCESS;
		stat->status = VIRTCHNL_Fसूची_FAILURE_RULE_NORESOURCE;
		dev_err(dev, "VF %d: writing FDIR rule failed, ret:%d\n",
			vf->vf_id, ret);
		जाओ err_del_पंचांगr;
	पूर्ण

	kमुक्त(stat);

	वापस ret;

err_del_पंचांगr:
	ice_vc_fdir_clear_irq_ctx(vf);
err_निकास:
	ret = ice_vc_send_msg_to_vf(vf, VIRTCHNL_OP_DEL_Fसूची_FILTER, v_ret,
				    (u8 *)stat, len);
	kमुक्त(stat);
	वापस ret;
पूर्ण

/**
 * ice_vf_fdir_init - init Fसूची resource क्रम VF
 * @vf: poपूर्णांकer to the VF info
 */
व्योम ice_vf_fdir_init(काष्ठा ice_vf *vf)
अणु
	काष्ठा ice_vf_fdir *fdir = &vf->fdir;

	idr_init(&fdir->fdir_rule_idr);
	INIT_LIST_HEAD(&fdir->fdir_rule_list);

	spin_lock_init(&fdir->ctx_lock);
	fdir->ctx_irq.flags = 0;
	fdir->ctx_करोne.flags = 0;
पूर्ण

/**
 * ice_vf_fdir_निकास - destroy Fसूची resource क्रम VF
 * @vf: poपूर्णांकer to the VF info
 */
व्योम ice_vf_fdir_निकास(काष्ठा ice_vf *vf)
अणु
	ice_vc_fdir_flush_entry(vf);
	idr_destroy(&vf->fdir.fdir_rule_idr);
	ice_vc_fdir_rem_prof_all(vf);
	ice_vc_fdir_मुक्त_prof_all(vf);
पूर्ण
