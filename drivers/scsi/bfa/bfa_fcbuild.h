<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2005-2014 Brocade Communications Systems, Inc.
 * Copyright (c) 2014- QLogic Corporation.
 * All rights reserved
 * www.qlogic.com
 *
 * Linux driver क्रम QLogic BR-series Fibre Channel Host Bus Adapter.
 */
/*
 * fcbuild.h - FC link service frame building and parsing routines
 */

#अगर_अघोषित __FCBUILD_H__
#घोषणा __FCBUILD_H__

#समावेश "bfad_drv.h"
#समावेश "bfa_fc.h"
#समावेश "bfa_defs_fcs.h"

/*
 * Utility Macros/functions
 */

#घोषणा wwn_is_equal(_wwn1, _wwn2)		\
	(स_भेद(&(_wwn1), &(_wwn2), माप(wwn_t)) == 0)

#घोषणा fc_roundup(_l, _s) (((_l) + ((_s) - 1)) & ~((_s) - 1))

/*
 * Given the fc response length, this routine will वापस
 * the length of the actual payload bytes following the CT header.
 *
 * Assumes the input response length करोes not include the crc, eof, etc.
 */
अटल अंतरभूत   u32
fc_get_ctresp_pyld_len(u32 resp_len)
अणु
	वापस resp_len - माप(काष्ठा ct_hdr_s);
पूर्ण

/*
 * Convert bfa speed to rpsc speed value.
 */
अटल अंतरभूत  क्रमागत bfa_port_speed
fc_rpsc_operspeed_to_bfa_speed(क्रमागत fc_rpsc_op_speed speed)
अणु
	चयन (speed) अणु

	हाल RPSC_OP_SPEED_1G:
		वापस BFA_PORT_SPEED_1GBPS;

	हाल RPSC_OP_SPEED_2G:
		वापस BFA_PORT_SPEED_2GBPS;

	हाल RPSC_OP_SPEED_4G:
		वापस BFA_PORT_SPEED_4GBPS;

	हाल RPSC_OP_SPEED_8G:
		वापस BFA_PORT_SPEED_8GBPS;

	हाल RPSC_OP_SPEED_16G:
		वापस BFA_PORT_SPEED_16GBPS;

	हाल RPSC_OP_SPEED_10G:
		वापस BFA_PORT_SPEED_10GBPS;

	शेष:
		वापस BFA_PORT_SPEED_UNKNOWN;
	पूर्ण
पूर्ण

/*
 * Convert RPSC speed to bfa speed value.
 */
अटल अंतरभूत   क्रमागत fc_rpsc_op_speed
fc_bfa_speed_to_rpsc_operspeed(क्रमागत bfa_port_speed op_speed)
अणु
	चयन (op_speed) अणु

	हाल BFA_PORT_SPEED_1GBPS:
		वापस RPSC_OP_SPEED_1G;

	हाल BFA_PORT_SPEED_2GBPS:
		वापस RPSC_OP_SPEED_2G;

	हाल BFA_PORT_SPEED_4GBPS:
		वापस RPSC_OP_SPEED_4G;

	हाल BFA_PORT_SPEED_8GBPS:
		वापस RPSC_OP_SPEED_8G;

	हाल BFA_PORT_SPEED_16GBPS:
		वापस RPSC_OP_SPEED_16G;

	हाल BFA_PORT_SPEED_10GBPS:
		वापस RPSC_OP_SPEED_10G;

	शेष:
		वापस RPSC_OP_SPEED_NOT_EST;
	पूर्ण
पूर्ण

क्रमागत fc_parse_status अणु
	FC_PARSE_OK = 0,
	FC_PARSE_FAILURE = 1,
	FC_PARSE_BUSY = 2,
	FC_PARSE_LEN_INVAL,
	FC_PARSE_ACC_INVAL,
	FC_PARSE_PWWN_NOT_EQUAL,
	FC_PARSE_NWWN_NOT_EQUAL,
	FC_PARSE_RXSZ_INVAL,
	FC_PARSE_NOT_FCP,
	FC_PARSE_OPAFLAG_INVAL,
	FC_PARSE_RPAFLAG_INVAL,
	FC_PARSE_OPA_INVAL,
	FC_PARSE_RPA_INVAL,

पूर्ण;

काष्ठा fc_ढाँचाs_s अणु
	काष्ठा fchs_s fc_els_req;
	काष्ठा fchs_s fc_bls_req;
	काष्ठा fc_logi_s plogi;
	काष्ठा fc_rrq_s rrq;
पूर्ण;

व्योम            fcbuild_init(व्योम);

u16        fc_flogi_build(काष्ठा fchs_s *fchs, काष्ठा fc_logi_s *flogi,
			u32 s_id, u16 ox_id, wwn_t port_name, wwn_t node_name,
			       u16 pdu_size, u8 set_npiv, u8 set_auth,
			       u16 local_bb_credits);

u16        fc_fdisc_build(काष्ठा fchs_s *buf, काष्ठा fc_logi_s *flogi, u32 s_id,
			       u16 ox_id, wwn_t port_name, wwn_t node_name,
			       u16 pdu_size);

u16        fc_flogi_acc_build(काष्ठा fchs_s *fchs, काष्ठा fc_logi_s *flogi,
				   u32 s_id, __be16 ox_id,
				   wwn_t port_name, wwn_t node_name,
				   u16 pdu_size,
				   u16 local_bb_credits, u8 bb_scn);

u16        fc_plogi_build(काष्ठा fchs_s *fchs, व्योम *pld, u32 d_id,
			       u32 s_id, u16 ox_id, wwn_t port_name,
			       wwn_t node_name, u16 pdu_size, u16 bb_cr);

क्रमागत fc_parse_status fc_plogi_parse(काष्ठा fchs_s *fchs);

u16        fc_abts_build(काष्ठा fchs_s *buf, u32 d_id, u32 s_id,
			      u16 ox_id);

क्रमागत fc_parse_status fc_abts_rsp_parse(काष्ठा fchs_s *buf, पूर्णांक len);

u16        fc_rrq_build(काष्ठा fchs_s *buf, काष्ठा fc_rrq_s *rrq, u32 d_id,
			     u32 s_id, u16 ox_id, u16 rrq_oxid);

u16        fc_rspnid_build(काष्ठा fchs_s *fchs, व्योम *pld, u32 s_id,
				u16 ox_id, u8 *name);
u16	fc_rsnn_nn_build(काष्ठा fchs_s *fchs, व्योम *pld, u32 s_id,
				wwn_t node_name, u8 *name);

u16        fc_rftid_build(काष्ठा fchs_s *fchs, व्योम *pld, u32 s_id,
			       u16 ox_id, क्रमागत bfa_lport_role role);

u16       fc_rftid_build_sol(काष्ठा fchs_s *fchs, व्योम *pyld, u32 s_id,
				   u16 ox_id, u8 *fc4_biपंचांगap,
				   u32 biपंचांगap_size);

u16	fc_rffid_build(काष्ठा fchs_s *fchs, व्योम *pyld, u32 s_id,
			u16 ox_id, u8 fc4_type, u8 fc4_ftrs);

u16        fc_gidpn_build(काष्ठा fchs_s *fchs, व्योम *pyld, u32 s_id,
			       u16 ox_id, wwn_t port_name);

u16        fc_gpnid_build(काष्ठा fchs_s *fchs, व्योम *pld, u32 s_id,
			       u16 ox_id, u32 port_id);

u16	fc_gs_rjt_build(काष्ठा fchs_s *fchs, काष्ठा ct_hdr_s *cthdr,
			u32 d_id, u32 s_id, u16 ox_id,
			u8 reason_code, u8 reason_code_expl);

u16        fc_scr_build(काष्ठा fchs_s *fchs, काष्ठा fc_scr_s *scr,
			u8 set_br_reg, u32 s_id, u16 ox_id);

u16        fc_plogi_acc_build(काष्ठा fchs_s *fchs, व्योम *pld, u32 d_id,
				   u32 s_id, u16 ox_id,
				   wwn_t port_name, wwn_t node_name,
				   u16 pdu_size, u16 bb_cr);

u16        fc_adisc_build(काष्ठा fchs_s *fchs, काष्ठा fc_adisc_s *adisc,
			u32 d_id, u32 s_id, __be16 ox_id, wwn_t port_name,
			       wwn_t node_name);

क्रमागत fc_parse_status fc_adisc_parse(काष्ठा fchs_s *fchs, व्योम *pld,
			u32 host_dap, wwn_t node_name, wwn_t port_name);

क्रमागत fc_parse_status fc_adisc_rsp_parse(काष्ठा fc_adisc_s *adisc, पूर्णांक len,
				 wwn_t port_name, wwn_t node_name);

u16        fc_adisc_acc_build(काष्ठा fchs_s *fchs, काष्ठा fc_adisc_s *adisc,
				   u32 d_id, u32 s_id, __be16 ox_id,
				   wwn_t port_name, wwn_t node_name);
u16        fc_ls_rjt_build(काष्ठा fchs_s *fchs, काष्ठा fc_ls_rjt_s *ls_rjt,
				u32 d_id, u32 s_id, __be16 ox_id,
				u8 reason_code, u8 reason_code_expl);
u16        fc_ls_acc_build(काष्ठा fchs_s *fchs, काष्ठा fc_els_cmd_s *els_cmd,
				u32 d_id, u32 s_id, __be16 ox_id);
u16        fc_prli_build(काष्ठा fchs_s *fchs, व्योम *pld, u32 d_id,
			      u32 s_id, u16 ox_id);

क्रमागत fc_parse_status fc_prli_rsp_parse(काष्ठा fc_prli_s *prli, पूर्णांक len);

u16        fc_prli_acc_build(काष्ठा fchs_s *fchs, व्योम *pld, u32 d_id,
				  u32 s_id, __be16 ox_id,
				  क्रमागत bfa_lport_role role);

u16        fc_rnid_build(काष्ठा fchs_s *fchs, काष्ठा fc_rnid_cmd_s *rnid,
			      u32 d_id, u32 s_id, u16 ox_id,
			      u32 data_क्रमmat);

u16        fc_rnid_acc_build(काष्ठा fchs_s *fchs,
			काष्ठा fc_rnid_acc_s *rnid_acc, u32 d_id, u32 s_id,
			__be16 ox_id, u32 data_क्रमmat,
			काष्ठा fc_rnid_common_id_data_s *common_id_data,
			काष्ठा fc_rnid_general_topology_data_s *gen_topo_data);

u16	fc_rpsc2_build(काष्ठा fchs_s *fchs, काष्ठा fc_rpsc2_cmd_s *rps2c,
			u32 d_id, u32 s_id, u32 *pid_list, u16 npids);
u16        fc_rpsc_build(काष्ठा fchs_s *fchs, काष्ठा fc_rpsc_cmd_s *rpsc,
			      u32 d_id, u32 s_id, u16 ox_id);
u16        fc_rpsc_acc_build(काष्ठा fchs_s *fchs,
			काष्ठा fc_rpsc_acc_s *rpsc_acc, u32 d_id, u32 s_id,
			__be16 ox_id, काष्ठा fc_rpsc_speed_info_s *oper_speed);
u16        fc_gid_ft_build(काष्ठा fchs_s *fchs, व्योम *pld, u32 s_id,
				u8 fc4_type);

u16        fc_rpnid_build(काष्ठा fchs_s *fchs, व्योम *pyld, u32 s_id,
			       u32 port_id, wwn_t port_name);

u16        fc_rnnid_build(काष्ठा fchs_s *fchs, व्योम *pyld, u32 s_id,
			       u32 port_id, wwn_t node_name);

u16        fc_rcsid_build(काष्ठा fchs_s *fchs, व्योम *pyld, u32 s_id,
			       u32 port_id, u32 cos);

u16        fc_rptid_build(काष्ठा fchs_s *fchs, व्योम *pyld, u32 s_id,
			       u32 port_id, u8 port_type);

u16        fc_ganxt_build(काष्ठा fchs_s *fchs, व्योम *pyld, u32 s_id,
			       u32 port_id);

u16        fc_logo_build(काष्ठा fchs_s *fchs, काष्ठा fc_logo_s *logo, u32 d_id,
			      u32 s_id, u16 ox_id, wwn_t port_name);

u16        fc_logo_acc_build(काष्ठा fchs_s *fchs, व्योम *pld, u32 d_id,
				  u32 s_id, __be16 ox_id);

u16        fc_fdmi_reqhdr_build(काष्ठा fchs_s *fchs, व्योम *pyld, u32 s_id,
				     u16 cmd_code);
u16	fc_gmal_req_build(काष्ठा fchs_s *fchs, व्योम *pyld, u32 s_id, wwn_t wwn);
u16	fc_gfn_req_build(काष्ठा fchs_s *fchs, व्योम *pyld, u32 s_id, wwn_t wwn);

व्योम		fc_get_fc4type_biपंचांगask(u8 fc4_type, u8 *bit_mask);

व्योम		fc_els_req_build(काष्ठा fchs_s *fchs, u32 d_id, u32 s_id,
					 __be16 ox_id);

क्रमागत fc_parse_status	fc_plogi_rsp_parse(काष्ठा fchs_s *fchs, पूर्णांक len,
					wwn_t port_name);

क्रमागत fc_parse_status	fc_prli_parse(काष्ठा fc_prli_s *prli);

क्रमागत fc_parse_status	fc_pdisc_parse(काष्ठा fchs_s *fchs, wwn_t node_name,
					wwn_t port_name);

u16 fc_ba_acc_build(काष्ठा fchs_s *fchs, काष्ठा fc_ba_acc_s *ba_acc, u32 d_id,
		u32 s_id, __be16 ox_id, u16 rx_id);

पूर्णांक fc_logout_params_pages(काष्ठा fchs_s *fc_frame, u8 els_code);

u16 fc_tprlo_acc_build(काष्ठा fchs_s *fchs, काष्ठा fc_tprlo_acc_s *tprlo_acc,
		u32 d_id, u32 s_id, __be16 ox_id, पूर्णांक num_pages);

u16 fc_prlo_acc_build(काष्ठा fchs_s *fchs, काष्ठा fc_prlo_acc_s *prlo_acc,
		u32 d_id, u32 s_id, __be16 ox_id, पूर्णांक num_pages);

u16 fc_pdisc_build(काष्ठा fchs_s *fchs, u32 d_id, u32 s_id,
		u16 ox_id, wwn_t port_name, wwn_t node_name,
		u16 pdu_size);

u16 fc_pdisc_rsp_parse(काष्ठा fchs_s *fchs, पूर्णांक len, wwn_t port_name);

u16 fc_prlo_build(काष्ठा fchs_s *fchs, u32 d_id, u32 s_id,
		u16 ox_id, पूर्णांक num_pages);

u16 fc_tprlo_build(काष्ठा fchs_s *fchs, u32 d_id, u32 s_id,
		u16 ox_id, पूर्णांक num_pages, क्रमागत fc_tprlo_type tprlo_type,
		u32 tpr_id);

u16 fc_ba_rjt_build(काष्ठा fchs_s *fchs, u32 d_id, u32 s_id,
		__be16 ox_id, u32 reason_code, u32 reason_expl);

u16 fc_gnnid_build(काष्ठा fchs_s *fchs, व्योम *pyld, u32 s_id, u16 ox_id,
		u32 port_id);

u16 fc_ct_rsp_parse(काष्ठा ct_hdr_s *cthdr);

u16 fc_rscn_build(काष्ठा fchs_s *fchs, काष्ठा fc_rscn_pl_s *rscn, u32 s_id,
		u16 ox_id);
#पूर्ण_अगर
