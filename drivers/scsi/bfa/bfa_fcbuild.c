<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2005-2014 Brocade Communications Systems, Inc.
 * Copyright (c) 2014- QLogic Corporation.
 * All rights reserved
 * www.qlogic.com
 *
 * Linux driver क्रम QLogic BR-series Fibre Channel Host Bus Adapter.
 */
/*
 * fcbuild.c - FC link service frame building and parsing routines
 */

#समावेश "bfad_drv.h"
#समावेश "bfa_fcbuild.h"

/*
 * अटल build functions
 */
अटल व्योम     fc_els_rsp_build(काष्ठा fchs_s *fchs, u32 d_id, u32 s_id,
				 __be16 ox_id);
अटल व्योम     fc_bls_rsp_build(काष्ठा fchs_s *fchs, u32 d_id, u32 s_id,
				 __be16 ox_id);
अटल काष्ठा fchs_s fc_els_req_पंचांगpl;
अटल काष्ठा fchs_s fc_els_rsp_पंचांगpl;
अटल काष्ठा fchs_s fc_bls_req_पंचांगpl;
अटल काष्ठा fchs_s fc_bls_rsp_पंचांगpl;
अटल काष्ठा fc_ba_acc_s ba_acc_पंचांगpl;
अटल काष्ठा fc_logi_s plogi_पंचांगpl;
अटल काष्ठा fc_prli_s prli_पंचांगpl;
अटल काष्ठा fc_rrq_s rrq_पंचांगpl;
अटल काष्ठा fchs_s fcp_fchs_पंचांगpl;

व्योम
fcbuild_init(व्योम)
अणु
	/*
	 * fc_els_req_पंचांगpl
	 */
	fc_els_req_पंचांगpl.routing = FC_RTG_EXT_LINK;
	fc_els_req_पंचांगpl.cat_info = FC_CAT_LD_REQUEST;
	fc_els_req_पंचांगpl.type = FC_TYPE_ELS;
	fc_els_req_पंचांगpl.f_ctl =
		bfa_hton3b(FCTL_SEQ_INI | FCTL_FS_EXCH | FCTL_END_SEQ |
			      FCTL_SI_XFER);
	fc_els_req_पंचांगpl.rx_id = FC_RXID_ANY;

	/*
	 * fc_els_rsp_पंचांगpl
	 */
	fc_els_rsp_पंचांगpl.routing = FC_RTG_EXT_LINK;
	fc_els_rsp_पंचांगpl.cat_info = FC_CAT_LD_REPLY;
	fc_els_rsp_पंचांगpl.type = FC_TYPE_ELS;
	fc_els_rsp_पंचांगpl.f_ctl =
		bfa_hton3b(FCTL_EC_RESP | FCTL_SEQ_INI | FCTL_LS_EXCH |
			      FCTL_END_SEQ | FCTL_SI_XFER);
	fc_els_rsp_पंचांगpl.rx_id = FC_RXID_ANY;

	/*
	 * fc_bls_req_पंचांगpl
	 */
	fc_bls_req_पंचांगpl.routing = FC_RTG_BASIC_LINK;
	fc_bls_req_पंचांगpl.type = FC_TYPE_BLS;
	fc_bls_req_पंचांगpl.f_ctl = bfa_hton3b(FCTL_END_SEQ | FCTL_SI_XFER);
	fc_bls_req_पंचांगpl.rx_id = FC_RXID_ANY;

	/*
	 * fc_bls_rsp_पंचांगpl
	 */
	fc_bls_rsp_पंचांगpl.routing = FC_RTG_BASIC_LINK;
	fc_bls_rsp_पंचांगpl.cat_info = FC_CAT_BA_ACC;
	fc_bls_rsp_पंचांगpl.type = FC_TYPE_BLS;
	fc_bls_rsp_पंचांगpl.f_ctl =
		bfa_hton3b(FCTL_EC_RESP | FCTL_SEQ_INI | FCTL_LS_EXCH |
			      FCTL_END_SEQ | FCTL_SI_XFER);
	fc_bls_rsp_पंचांगpl.rx_id = FC_RXID_ANY;

	/*
	 * ba_acc_पंचांगpl
	 */
	ba_acc_पंचांगpl.seq_id_valid = 0;
	ba_acc_पंचांगpl.low_seq_cnt = 0;
	ba_acc_पंचांगpl.high_seq_cnt = 0xFFFF;

	/*
	 * plogi_पंचांगpl
	 */
	plogi_पंचांगpl.csp.verhi = FC_PH_VER_PH_3;
	plogi_पंचांगpl.csp.verlo = FC_PH_VER_4_3;
	plogi_पंचांगpl.csp.ciro = 0x1;
	plogi_पंचांगpl.csp.cisc = 0x0;
	plogi_पंचांगpl.csp.altbbcred = 0x0;
	plogi_पंचांगpl.csp.conseq = cpu_to_be16(0x00FF);
	plogi_पंचांगpl.csp.ro_biपंचांगap = cpu_to_be16(0x0002);
	plogi_पंचांगpl.csp.e_d_tov = cpu_to_be32(2000);

	plogi_पंचांगpl.class3.class_valid = 1;
	plogi_पंचांगpl.class3.sequential = 1;
	plogi_पंचांगpl.class3.conseq = 0xFF;
	plogi_पंचांगpl.class3.ospx = 1;

	/*
	 * prli_पंचांगpl
	 */
	prli_पंचांगpl.command = FC_ELS_PRLI;
	prli_पंचांगpl.pglen = 0x10;
	prli_पंचांगpl.pagebytes = cpu_to_be16(0x0014);
	prli_पंचांगpl.parampage.type = FC_TYPE_FCP;
	prli_पंचांगpl.parampage.imagepair = 1;
	prli_पंचांगpl.parampage.servparams.rxrdisab = 1;

	/*
	 * rrq_पंचांगpl
	 */
	rrq_पंचांगpl.els_cmd.els_code = FC_ELS_RRQ;

	/*
	 * fcp_काष्ठा fchs_s mpl
	 */
	fcp_fchs_पंचांगpl.routing = FC_RTG_FC4_DEV_DATA;
	fcp_fchs_पंचांगpl.cat_info = FC_CAT_UNSOLICIT_CMD;
	fcp_fchs_पंचांगpl.type = FC_TYPE_FCP;
	fcp_fchs_पंचांगpl.f_ctl =
		bfa_hton3b(FCTL_FS_EXCH | FCTL_END_SEQ | FCTL_SI_XFER);
	fcp_fchs_पंचांगpl.seq_id = 1;
	fcp_fchs_पंचांगpl.rx_id = FC_RXID_ANY;
पूर्ण

अटल व्योम
fc_gs_fchdr_build(काष्ठा fchs_s *fchs, u32 d_id, u32 s_id, u32 ox_id)
अणु
	स_रखो(fchs, 0, माप(काष्ठा fchs_s));

	fchs->routing = FC_RTG_FC4_DEV_DATA;
	fchs->cat_info = FC_CAT_UNSOLICIT_CTRL;
	fchs->type = FC_TYPE_SERVICES;
	fchs->f_ctl =
		bfa_hton3b(FCTL_SEQ_INI | FCTL_FS_EXCH | FCTL_END_SEQ |
			      FCTL_SI_XFER);
	fchs->rx_id = FC_RXID_ANY;
	fchs->d_id = (d_id);
	fchs->s_id = (s_id);
	fchs->ox_id = cpu_to_be16(ox_id);

	/*
	 * @toकरो no need to set ox_id क्रम request
	 *       no need to set rx_id क्रम response
	 */
पूर्ण

अटल व्योम
fc_gsresp_fchdr_build(काष्ठा fchs_s *fchs, u32 d_id, u32 s_id, u16 ox_id)
अणु
	स_रखो(fchs, 0, माप(काष्ठा fchs_s));

	fchs->routing = FC_RTG_FC4_DEV_DATA;
	fchs->cat_info = FC_CAT_SOLICIT_CTRL;
	fchs->type = FC_TYPE_SERVICES;
	fchs->f_ctl =
		bfa_hton3b(FCTL_EC_RESP | FCTL_SEQ_INI | FCTL_LS_EXCH |
			   FCTL_END_SEQ | FCTL_SI_XFER);
	fchs->d_id = d_id;
	fchs->s_id = s_id;
	fchs->ox_id = ox_id;
पूर्ण

व्योम
fc_els_req_build(काष्ठा fchs_s *fchs, u32 d_id, u32 s_id, __be16 ox_id)
अणु
	स_नकल(fchs, &fc_els_req_पंचांगpl, माप(काष्ठा fchs_s));
	fchs->d_id = (d_id);
	fchs->s_id = (s_id);
	fchs->ox_id = cpu_to_be16(ox_id);
पूर्ण

अटल व्योम
fc_els_rsp_build(काष्ठा fchs_s *fchs, u32 d_id, u32 s_id, __be16 ox_id)
अणु
	स_नकल(fchs, &fc_els_rsp_पंचांगpl, माप(काष्ठा fchs_s));
	fchs->d_id = d_id;
	fchs->s_id = s_id;
	fchs->ox_id = ox_id;
पूर्ण

अटल व्योम
fc_bls_rsp_build(काष्ठा fchs_s *fchs, u32 d_id, u32 s_id, __be16 ox_id)
अणु
	स_नकल(fchs, &fc_bls_rsp_पंचांगpl, माप(काष्ठा fchs_s));
	fchs->d_id = d_id;
	fchs->s_id = s_id;
	fchs->ox_id = ox_id;
पूर्ण

अटल          u16
fc_plogi_x_build(काष्ठा fchs_s *fchs, व्योम *pld, u32 d_id, u32 s_id,
		 __be16 ox_id, wwn_t port_name, wwn_t node_name,
		 u16 pdu_size, u16 bb_cr, u8 els_code)
अणु
	काष्ठा fc_logi_s *plogi = (काष्ठा fc_logi_s *) (pld);

	स_नकल(plogi, &plogi_पंचांगpl, माप(काष्ठा fc_logi_s));

	/* For FC AL bb_cr is 0 and altbbcred is 1 */
	अगर (!bb_cr)
		plogi->csp.altbbcred = 1;

	plogi->els_cmd.els_code = els_code;
	अगर (els_code == FC_ELS_PLOGI)
		fc_els_req_build(fchs, d_id, s_id, ox_id);
	अन्यथा
		fc_els_rsp_build(fchs, d_id, s_id, ox_id);

	plogi->csp.rxsz = plogi->class3.rxsz = cpu_to_be16(pdu_size);
	plogi->csp.bbcred  = cpu_to_be16(bb_cr);

	स_नकल(&plogi->port_name, &port_name, माप(wwn_t));
	स_नकल(&plogi->node_name, &node_name, माप(wwn_t));

	वापस माप(काष्ठा fc_logi_s);
पूर्ण

u16
fc_flogi_build(काष्ठा fchs_s *fchs, काष्ठा fc_logi_s *flogi, u32 s_id,
		u16 ox_id, wwn_t port_name, wwn_t node_name, u16 pdu_size,
	       u8 set_npiv, u8 set_auth, u16 local_bb_credits)
अणु
	u32        d_id = bfa_hton3b(FC_FABRIC_PORT);
	__be32	*vvl_info;

	स_नकल(flogi, &plogi_पंचांगpl, माप(काष्ठा fc_logi_s));

	flogi->els_cmd.els_code = FC_ELS_FLOGI;
	fc_els_req_build(fchs, d_id, s_id, ox_id);

	flogi->csp.rxsz = flogi->class3.rxsz = cpu_to_be16(pdu_size);
	flogi->port_name = port_name;
	flogi->node_name = node_name;

	/*
	 * Set the NPIV Capability Bit ( word 1, bit 31) of Common
	 * Service Parameters.
	 */
	flogi->csp.ciro = set_npiv;

	/* set AUTH capability */
	flogi->csp.security = set_auth;

	flogi->csp.bbcred = cpu_to_be16(local_bb_credits);

	/* Set brcd token in VVL */
	vvl_info = (u32 *)&flogi->vvl[0];

	/* set the flag to indicate the presence of VVL */
	flogi->csp.npiv_supp    = 1; /* @toकरो. field name is not correct */
	vvl_info[0]	= cpu_to_be32(FLOGI_VVL_BRCD);

	वापस माप(काष्ठा fc_logi_s);
पूर्ण

u16
fc_flogi_acc_build(काष्ठा fchs_s *fchs, काष्ठा fc_logi_s *flogi, u32 s_id,
		   __be16 ox_id, wwn_t port_name, wwn_t node_name,
		   u16 pdu_size, u16 local_bb_credits, u8 bb_scn)
अणु
	u32        d_id = 0;
	u16	   bbscn_rxsz = (bb_scn << 12) | pdu_size;

	स_नकल(flogi, &plogi_पंचांगpl, माप(काष्ठा fc_logi_s));
	fc_els_rsp_build(fchs, d_id, s_id, ox_id);

	flogi->els_cmd.els_code = FC_ELS_ACC;
	flogi->class3.rxsz = cpu_to_be16(pdu_size);
	flogi->csp.rxsz  = cpu_to_be16(bbscn_rxsz);	/* bb_scn/rxsz */
	flogi->port_name = port_name;
	flogi->node_name = node_name;

	flogi->csp.bbcred = cpu_to_be16(local_bb_credits);

	वापस माप(काष्ठा fc_logi_s);
पूर्ण

u16
fc_fdisc_build(काष्ठा fchs_s *fchs, काष्ठा fc_logi_s *flogi, u32 s_id,
		u16 ox_id, wwn_t port_name, wwn_t node_name, u16 pdu_size)
अणु
	u32        d_id = bfa_hton3b(FC_FABRIC_PORT);

	स_नकल(flogi, &plogi_पंचांगpl, माप(काष्ठा fc_logi_s));

	flogi->els_cmd.els_code = FC_ELS_FDISC;
	fc_els_req_build(fchs, d_id, s_id, ox_id);

	flogi->csp.rxsz = flogi->class3.rxsz = cpu_to_be16(pdu_size);
	flogi->port_name = port_name;
	flogi->node_name = node_name;

	वापस माप(काष्ठा fc_logi_s);
पूर्ण

u16
fc_plogi_build(काष्ठा fchs_s *fchs, व्योम *pld, u32 d_id, u32 s_id,
	       u16 ox_id, wwn_t port_name, wwn_t node_name,
	       u16 pdu_size, u16 bb_cr)
अणु
	वापस fc_plogi_x_build(fchs, pld, d_id, s_id, ox_id, port_name,
				node_name, pdu_size, bb_cr, FC_ELS_PLOGI);
पूर्ण

u16
fc_plogi_acc_build(काष्ठा fchs_s *fchs, व्योम *pld, u32 d_id, u32 s_id,
		   u16 ox_id, wwn_t port_name, wwn_t node_name,
		   u16 pdu_size, u16 bb_cr)
अणु
	वापस fc_plogi_x_build(fchs, pld, d_id, s_id, ox_id, port_name,
				node_name, pdu_size, bb_cr, FC_ELS_ACC);
पूर्ण

क्रमागत fc_parse_status
fc_plogi_rsp_parse(काष्ठा fchs_s *fchs, पूर्णांक len, wwn_t port_name)
अणु
	काष्ठा fc_els_cmd_s *els_cmd = (काष्ठा fc_els_cmd_s *) (fchs + 1);
	काष्ठा fc_logi_s *plogi;
	काष्ठा fc_ls_rjt_s *ls_rjt;

	चयन (els_cmd->els_code) अणु
	हाल FC_ELS_LS_RJT:
		ls_rjt = (काष्ठा fc_ls_rjt_s *) (fchs + 1);
		अगर (ls_rjt->reason_code == FC_LS_RJT_RSN_LOGICAL_BUSY)
			वापस FC_PARSE_BUSY;
		अन्यथा
			वापस FC_PARSE_FAILURE;
	हाल FC_ELS_ACC:
		plogi = (काष्ठा fc_logi_s *) (fchs + 1);
		अगर (len < माप(काष्ठा fc_logi_s))
			वापस FC_PARSE_FAILURE;

		अगर (!wwn_is_equal(plogi->port_name, port_name))
			वापस FC_PARSE_FAILURE;

		अगर (!plogi->class3.class_valid)
			वापस FC_PARSE_FAILURE;

		अगर (be16_to_cpu(plogi->class3.rxsz) < (FC_MIN_PDUSZ))
			वापस FC_PARSE_FAILURE;

		वापस FC_PARSE_OK;
	शेष:
		वापस FC_PARSE_FAILURE;
	पूर्ण
पूर्ण

क्रमागत fc_parse_status
fc_plogi_parse(काष्ठा fchs_s *fchs)
अणु
	काष्ठा fc_logi_s *plogi = (काष्ठा fc_logi_s *) (fchs + 1);

	अगर (plogi->class3.class_valid != 1)
		वापस FC_PARSE_FAILURE;

	अगर ((be16_to_cpu(plogi->class3.rxsz) < FC_MIN_PDUSZ)
	    || (be16_to_cpu(plogi->class3.rxsz) > FC_MAX_PDUSZ)
	    || (plogi->class3.rxsz == 0))
		वापस FC_PARSE_FAILURE;

	वापस FC_PARSE_OK;
पूर्ण

u16
fc_prli_build(काष्ठा fchs_s *fchs, व्योम *pld, u32 d_id, u32 s_id,
	      u16 ox_id)
अणु
	काष्ठा fc_prli_s *prli = (काष्ठा fc_prli_s *) (pld);

	fc_els_req_build(fchs, d_id, s_id, ox_id);
	स_नकल(prli, &prli_पंचांगpl, माप(काष्ठा fc_prli_s));

	prli->command = FC_ELS_PRLI;
	prli->parampage.servparams.initiator     = 1;
	prli->parampage.servparams.retry         = 1;
	prli->parampage.servparams.rec_support   = 1;
	prli->parampage.servparams.task_retry_id = 0;
	prli->parampage.servparams.confirm       = 1;

	वापस माप(काष्ठा fc_prli_s);
पूर्ण

u16
fc_prli_acc_build(काष्ठा fchs_s *fchs, व्योम *pld, u32 d_id, u32 s_id,
		  __be16 ox_id, क्रमागत bfa_lport_role role)
अणु
	काष्ठा fc_prli_s *prli = (काष्ठा fc_prli_s *) (pld);

	fc_els_rsp_build(fchs, d_id, s_id, ox_id);
	स_नकल(prli, &prli_पंचांगpl, माप(काष्ठा fc_prli_s));

	prli->command = FC_ELS_ACC;

	prli->parampage.servparams.initiator = 1;

	prli->parampage.rspcode = FC_PRLI_ACC_XQTD;

	वापस माप(काष्ठा fc_prli_s);
पूर्ण

क्रमागत fc_parse_status
fc_prli_rsp_parse(काष्ठा fc_prli_s *prli, पूर्णांक len)
अणु
	अगर (len < माप(काष्ठा fc_prli_s))
		वापस FC_PARSE_FAILURE;

	अगर (prli->command != FC_ELS_ACC)
		वापस FC_PARSE_FAILURE;

	अगर ((prli->parampage.rspcode != FC_PRLI_ACC_XQTD)
	    && (prli->parampage.rspcode != FC_PRLI_ACC_PREDEF_IMG))
		वापस FC_PARSE_FAILURE;

	अगर (prli->parampage.servparams.target != 1)
		वापस FC_PARSE_FAILURE;

	वापस FC_PARSE_OK;
पूर्ण

क्रमागत fc_parse_status
fc_prli_parse(काष्ठा fc_prli_s *prli)
अणु
	अगर (prli->parampage.type != FC_TYPE_FCP)
		वापस FC_PARSE_FAILURE;

	अगर (!prli->parampage.imagepair)
		वापस FC_PARSE_FAILURE;

	अगर (!prli->parampage.servparams.initiator)
		वापस FC_PARSE_FAILURE;

	वापस FC_PARSE_OK;
पूर्ण

u16
fc_logo_build(काष्ठा fchs_s *fchs, काष्ठा fc_logo_s *logo, u32 d_id, u32 s_id,
	      u16 ox_id, wwn_t port_name)
अणु
	fc_els_req_build(fchs, d_id, s_id, ox_id);

	स_रखो(logo, '\0', माप(काष्ठा fc_logo_s));
	logo->els_cmd.els_code = FC_ELS_LOGO;
	logo->nport_id = (s_id);
	logo->orig_port_name = port_name;

	वापस माप(काष्ठा fc_logo_s);
पूर्ण

अटल u16
fc_adisc_x_build(काष्ठा fchs_s *fchs, काष्ठा fc_adisc_s *adisc, u32 d_id,
		 u32 s_id, __be16 ox_id, wwn_t port_name,
		 wwn_t node_name, u8 els_code)
अणु
	स_रखो(adisc, '\0', माप(काष्ठा fc_adisc_s));

	adisc->els_cmd.els_code = els_code;

	अगर (els_code == FC_ELS_ADISC)
		fc_els_req_build(fchs, d_id, s_id, ox_id);
	अन्यथा
		fc_els_rsp_build(fchs, d_id, s_id, ox_id);

	adisc->orig_HA = 0;
	adisc->orig_port_name = port_name;
	adisc->orig_node_name = node_name;
	adisc->nport_id = (s_id);

	वापस माप(काष्ठा fc_adisc_s);
पूर्ण

u16
fc_adisc_build(काष्ठा fchs_s *fchs, काष्ठा fc_adisc_s *adisc, u32 d_id,
		u32 s_id, __be16 ox_id, wwn_t port_name, wwn_t node_name)
अणु
	वापस fc_adisc_x_build(fchs, adisc, d_id, s_id, ox_id, port_name,
				node_name, FC_ELS_ADISC);
पूर्ण

u16
fc_adisc_acc_build(काष्ठा fchs_s *fchs, काष्ठा fc_adisc_s *adisc, u32 d_id,
		   u32 s_id, __be16 ox_id, wwn_t port_name,
		   wwn_t node_name)
अणु
	वापस fc_adisc_x_build(fchs, adisc, d_id, s_id, ox_id, port_name,
				node_name, FC_ELS_ACC);
पूर्ण

क्रमागत fc_parse_status
fc_adisc_rsp_parse(काष्ठा fc_adisc_s *adisc, पूर्णांक len, wwn_t port_name,
				 wwn_t node_name)
अणु

	अगर (len < माप(काष्ठा fc_adisc_s))
		वापस FC_PARSE_FAILURE;

	अगर (adisc->els_cmd.els_code != FC_ELS_ACC)
		वापस FC_PARSE_FAILURE;

	अगर (!wwn_is_equal(adisc->orig_port_name, port_name))
		वापस FC_PARSE_FAILURE;

	वापस FC_PARSE_OK;
पूर्ण

क्रमागत fc_parse_status
fc_adisc_parse(काष्ठा fchs_s *fchs, व्योम *pld, u32 host_dap, wwn_t node_name,
	       wwn_t port_name)
अणु
	काष्ठा fc_adisc_s *adisc = (काष्ठा fc_adisc_s *) pld;

	अगर (adisc->els_cmd.els_code != FC_ELS_ACC)
		वापस FC_PARSE_FAILURE;

	अगर ((adisc->nport_id == (host_dap))
	    && wwn_is_equal(adisc->orig_port_name, port_name)
	    && wwn_is_equal(adisc->orig_node_name, node_name))
		वापस FC_PARSE_OK;

	वापस FC_PARSE_FAILURE;
पूर्ण

क्रमागत fc_parse_status
fc_pdisc_parse(काष्ठा fchs_s *fchs, wwn_t node_name, wwn_t port_name)
अणु
	काष्ठा fc_logi_s *pdisc = (काष्ठा fc_logi_s *) (fchs + 1);

	अगर (pdisc->class3.class_valid != 1)
		वापस FC_PARSE_FAILURE;

	अगर ((be16_to_cpu(pdisc->class3.rxsz) <
		(FC_MIN_PDUSZ - माप(काष्ठा fchs_s)))
	    || (pdisc->class3.rxsz == 0))
		वापस FC_PARSE_FAILURE;

	अगर (!wwn_is_equal(pdisc->port_name, port_name))
		वापस FC_PARSE_FAILURE;

	अगर (!wwn_is_equal(pdisc->node_name, node_name))
		वापस FC_PARSE_FAILURE;

	वापस FC_PARSE_OK;
पूर्ण

u16
fc_abts_build(काष्ठा fchs_s *fchs, u32 d_id, u32 s_id, u16 ox_id)
अणु
	स_नकल(fchs, &fc_bls_req_पंचांगpl, माप(काष्ठा fchs_s));
	fchs->cat_info = FC_CAT_ABTS;
	fchs->d_id = (d_id);
	fchs->s_id = (s_id);
	fchs->ox_id = cpu_to_be16(ox_id);

	वापस माप(काष्ठा fchs_s);
पूर्ण

क्रमागत fc_parse_status
fc_abts_rsp_parse(काष्ठा fchs_s *fchs, पूर्णांक len)
अणु
	अगर ((fchs->cat_info == FC_CAT_BA_ACC)
	    || (fchs->cat_info == FC_CAT_BA_RJT))
		वापस FC_PARSE_OK;

	वापस FC_PARSE_FAILURE;
पूर्ण

u16
fc_rrq_build(काष्ठा fchs_s *fchs, काष्ठा fc_rrq_s *rrq, u32 d_id, u32 s_id,
	     u16 ox_id, u16 rrq_oxid)
अणु
	fc_els_req_build(fchs, d_id, s_id, ox_id);

	/*
	 * build rrq payload
	 */
	स_नकल(rrq, &rrq_पंचांगpl, माप(काष्ठा fc_rrq_s));
	rrq->s_id = (s_id);
	rrq->ox_id = cpu_to_be16(rrq_oxid);
	rrq->rx_id = FC_RXID_ANY;

	वापस माप(काष्ठा fc_rrq_s);
पूर्ण

u16
fc_logo_acc_build(काष्ठा fchs_s *fchs, व्योम *pld, u32 d_id, u32 s_id,
		  __be16 ox_id)
अणु
	काष्ठा fc_els_cmd_s *acc = pld;

	fc_els_rsp_build(fchs, d_id, s_id, ox_id);

	स_रखो(acc, 0, माप(काष्ठा fc_els_cmd_s));
	acc->els_code = FC_ELS_ACC;

	वापस माप(काष्ठा fc_els_cmd_s);
पूर्ण

u16
fc_ls_rjt_build(काष्ठा fchs_s *fchs, काष्ठा fc_ls_rjt_s *ls_rjt, u32 d_id,
		u32 s_id, __be16 ox_id, u8 reason_code,
		u8 reason_code_expl)
अणु
	fc_els_rsp_build(fchs, d_id, s_id, ox_id);
	स_रखो(ls_rjt, 0, माप(काष्ठा fc_ls_rjt_s));

	ls_rjt->els_cmd.els_code = FC_ELS_LS_RJT;
	ls_rjt->reason_code = reason_code;
	ls_rjt->reason_code_expl = reason_code_expl;
	ls_rjt->venकरोr_unique = 0x00;

	वापस माप(काष्ठा fc_ls_rjt_s);
पूर्ण

u16
fc_ba_acc_build(काष्ठा fchs_s *fchs, काष्ठा fc_ba_acc_s *ba_acc, u32 d_id,
		u32 s_id, __be16 ox_id, u16 rx_id)
अणु
	fc_bls_rsp_build(fchs, d_id, s_id, ox_id);

	स_नकल(ba_acc, &ba_acc_पंचांगpl, माप(काष्ठा fc_ba_acc_s));

	fchs->rx_id = rx_id;

	ba_acc->ox_id = fchs->ox_id;
	ba_acc->rx_id = fchs->rx_id;

	वापस माप(काष्ठा fc_ba_acc_s);
पूर्ण

u16
fc_ls_acc_build(काष्ठा fchs_s *fchs, काष्ठा fc_els_cmd_s *els_cmd, u32 d_id,
		u32 s_id, __be16 ox_id)
अणु
	fc_els_rsp_build(fchs, d_id, s_id, ox_id);
	स_रखो(els_cmd, 0, माप(काष्ठा fc_els_cmd_s));
	els_cmd->els_code = FC_ELS_ACC;

	वापस माप(काष्ठा fc_els_cmd_s);
पूर्ण

पूर्णांक
fc_logout_params_pages(काष्ठा fchs_s *fc_frame, u8 els_code)
अणु
	पूर्णांक             num_pages = 0;
	काष्ठा fc_prlo_s *prlo;
	काष्ठा fc_tprlo_s *tprlo;

	अगर (els_code == FC_ELS_PRLO) अणु
		prlo = (काष्ठा fc_prlo_s *) (fc_frame + 1);
		num_pages = (be16_to_cpu(prlo->payload_len) - 4) / 16;
	पूर्ण अन्यथा अणु
		tprlo = (काष्ठा fc_tprlo_s *) (fc_frame + 1);
		num_pages = (be16_to_cpu(tprlo->payload_len) - 4) / 16;
	पूर्ण
	वापस num_pages;
पूर्ण

u16
fc_tprlo_acc_build(काष्ठा fchs_s *fchs, काष्ठा fc_tprlo_acc_s *tprlo_acc,
		u32 d_id, u32 s_id, __be16 ox_id, पूर्णांक num_pages)
अणु
	पूर्णांक             page;

	fc_els_rsp_build(fchs, d_id, s_id, ox_id);

	स_रखो(tprlo_acc, 0, (num_pages * 16) + 4);
	tprlo_acc->command = FC_ELS_ACC;

	tprlo_acc->page_len = 0x10;
	tprlo_acc->payload_len = cpu_to_be16((num_pages * 16) + 4);

	क्रम (page = 0; page < num_pages; page++) अणु
		tprlo_acc->tprlo_acc_params[page].opa_valid = 0;
		tprlo_acc->tprlo_acc_params[page].rpa_valid = 0;
		tprlo_acc->tprlo_acc_params[page].fc4type_csp = FC_TYPE_FCP;
		tprlo_acc->tprlo_acc_params[page].orig_process_assc = 0;
		tprlo_acc->tprlo_acc_params[page].resp_process_assc = 0;
	पूर्ण
	वापस be16_to_cpu(tprlo_acc->payload_len);
पूर्ण

u16
fc_prlo_acc_build(काष्ठा fchs_s *fchs, काष्ठा fc_prlo_acc_s *prlo_acc, u32 d_id,
		  u32 s_id, __be16 ox_id, पूर्णांक num_pages)
अणु
	पूर्णांक             page;

	fc_els_rsp_build(fchs, d_id, s_id, ox_id);

	स_रखो(prlo_acc, 0, (num_pages * 16) + 4);
	prlo_acc->command = FC_ELS_ACC;
	prlo_acc->page_len = 0x10;
	prlo_acc->payload_len = cpu_to_be16((num_pages * 16) + 4);

	क्रम (page = 0; page < num_pages; page++) अणु
		prlo_acc->prlo_acc_params[page].opa_valid = 0;
		prlo_acc->prlo_acc_params[page].rpa_valid = 0;
		prlo_acc->prlo_acc_params[page].fc4type_csp = FC_TYPE_FCP;
		prlo_acc->prlo_acc_params[page].orig_process_assc = 0;
		prlo_acc->prlo_acc_params[page].resp_process_assc = 0;
	पूर्ण

	वापस be16_to_cpu(prlo_acc->payload_len);
पूर्ण

u16
fc_rnid_build(काष्ठा fchs_s *fchs, काष्ठा fc_rnid_cmd_s *rnid, u32 d_id,
		u32 s_id, u16 ox_id, u32 data_क्रमmat)
अणु
	fc_els_req_build(fchs, d_id, s_id, ox_id);

	स_रखो(rnid, 0, माप(काष्ठा fc_rnid_cmd_s));

	rnid->els_cmd.els_code = FC_ELS_RNID;
	rnid->node_id_data_क्रमmat = data_क्रमmat;

	वापस माप(काष्ठा fc_rnid_cmd_s);
पूर्ण

u16
fc_rnid_acc_build(काष्ठा fchs_s *fchs, काष्ठा fc_rnid_acc_s *rnid_acc, u32 d_id,
		  u32 s_id, __be16 ox_id, u32 data_क्रमmat,
		  काष्ठा fc_rnid_common_id_data_s *common_id_data,
		  काष्ठा fc_rnid_general_topology_data_s *gen_topo_data)
अणु
	स_रखो(rnid_acc, 0, माप(काष्ठा fc_rnid_acc_s));

	fc_els_rsp_build(fchs, d_id, s_id, ox_id);

	rnid_acc->els_cmd.els_code = FC_ELS_ACC;
	rnid_acc->node_id_data_क्रमmat = data_क्रमmat;
	rnid_acc->common_id_data_length =
			माप(काष्ठा fc_rnid_common_id_data_s);
	rnid_acc->common_id_data = *common_id_data;

	अगर (data_क्रमmat == RNID_NODEID_DATA_FORMAT_DISCOVERY) अणु
		rnid_acc->specअगरic_id_data_length =
			माप(काष्ठा fc_rnid_general_topology_data_s);
		rnid_acc->gen_topology_data = *gen_topo_data;
		वापस माप(काष्ठा fc_rnid_acc_s);
	पूर्ण अन्यथा अणु
		वापस माप(काष्ठा fc_rnid_acc_s) -
			माप(काष्ठा fc_rnid_general_topology_data_s);
	पूर्ण

पूर्ण

u16
fc_rpsc_build(काष्ठा fchs_s *fchs, काष्ठा fc_rpsc_cmd_s *rpsc, u32 d_id,
		u32 s_id, u16 ox_id)
अणु
	fc_els_req_build(fchs, d_id, s_id, ox_id);

	स_रखो(rpsc, 0, माप(काष्ठा fc_rpsc_cmd_s));

	rpsc->els_cmd.els_code = FC_ELS_RPSC;
	वापस माप(काष्ठा fc_rpsc_cmd_s);
पूर्ण

u16
fc_rpsc2_build(काष्ठा fchs_s *fchs, काष्ठा fc_rpsc2_cmd_s *rpsc2, u32 d_id,
		u32 s_id, u32 *pid_list, u16 npids)
अणु
	u32 dctlr_id = FC_DOMAIN_CTRLR(bfa_hton3b(d_id));
	पूर्णांक i = 0;

	fc_els_req_build(fchs, bfa_hton3b(dctlr_id), s_id, 0);

	स_रखो(rpsc2, 0, माप(काष्ठा fc_rpsc2_cmd_s));

	rpsc2->els_cmd.els_code = FC_ELS_RPSC;
	rpsc2->token = cpu_to_be32(FC_BRCD_TOKEN);
	rpsc2->num_pids  = cpu_to_be16(npids);
	क्रम (i = 0; i < npids; i++)
		rpsc2->pid_list[i].pid = pid_list[i];

	वापस माप(काष्ठा fc_rpsc2_cmd_s) + ((npids - 1) * (माप(u32)));
पूर्ण

u16
fc_rpsc_acc_build(काष्ठा fchs_s *fchs, काष्ठा fc_rpsc_acc_s *rpsc_acc,
		u32 d_id, u32 s_id, __be16 ox_id,
		  काष्ठा fc_rpsc_speed_info_s *oper_speed)
अणु
	स_रखो(rpsc_acc, 0, माप(काष्ठा fc_rpsc_acc_s));

	fc_els_rsp_build(fchs, d_id, s_id, ox_id);

	rpsc_acc->command = FC_ELS_ACC;
	rpsc_acc->num_entries = cpu_to_be16(1);

	rpsc_acc->speed_info[0].port_speed_cap =
		cpu_to_be16(oper_speed->port_speed_cap);

	rpsc_acc->speed_info[0].port_op_speed =
		cpu_to_be16(oper_speed->port_op_speed);

	वापस माप(काष्ठा fc_rpsc_acc_s);
पूर्ण

u16
fc_pdisc_build(काष्ठा fchs_s *fchs, u32 d_id, u32 s_id, u16 ox_id,
	       wwn_t port_name, wwn_t node_name, u16 pdu_size)
अणु
	काष्ठा fc_logi_s *pdisc = (काष्ठा fc_logi_s *) (fchs + 1);

	स_नकल(pdisc, &plogi_पंचांगpl, माप(काष्ठा fc_logi_s));

	pdisc->els_cmd.els_code = FC_ELS_PDISC;
	fc_els_req_build(fchs, d_id, s_id, ox_id);

	pdisc->csp.rxsz = pdisc->class3.rxsz = cpu_to_be16(pdu_size);
	pdisc->port_name = port_name;
	pdisc->node_name = node_name;

	वापस माप(काष्ठा fc_logi_s);
पूर्ण

u16
fc_pdisc_rsp_parse(काष्ठा fchs_s *fchs, पूर्णांक len, wwn_t port_name)
अणु
	काष्ठा fc_logi_s *pdisc = (काष्ठा fc_logi_s *) (fchs + 1);

	अगर (len < माप(काष्ठा fc_logi_s))
		वापस FC_PARSE_LEN_INVAL;

	अगर (pdisc->els_cmd.els_code != FC_ELS_ACC)
		वापस FC_PARSE_ACC_INVAL;

	अगर (!wwn_is_equal(pdisc->port_name, port_name))
		वापस FC_PARSE_PWWN_NOT_EQUAL;

	अगर (!pdisc->class3.class_valid)
		वापस FC_PARSE_NWWN_NOT_EQUAL;

	अगर (be16_to_cpu(pdisc->class3.rxsz) < (FC_MIN_PDUSZ))
		वापस FC_PARSE_RXSZ_INVAL;

	वापस FC_PARSE_OK;
पूर्ण

u16
fc_prlo_build(काष्ठा fchs_s *fchs, u32 d_id, u32 s_id, u16 ox_id,
	      पूर्णांक num_pages)
अणु
	काष्ठा fc_prlo_s *prlo = (काष्ठा fc_prlo_s *) (fchs + 1);
	पूर्णांक             page;

	fc_els_req_build(fchs, d_id, s_id, ox_id);
	स_रखो(prlo, 0, (num_pages * 16) + 4);
	prlo->command = FC_ELS_PRLO;
	prlo->page_len = 0x10;
	prlo->payload_len = cpu_to_be16((num_pages * 16) + 4);

	क्रम (page = 0; page < num_pages; page++) अणु
		prlo->prlo_params[page].type = FC_TYPE_FCP;
		prlo->prlo_params[page].opa_valid = 0;
		prlo->prlo_params[page].rpa_valid = 0;
		prlo->prlo_params[page].orig_process_assc = 0;
		prlo->prlo_params[page].resp_process_assc = 0;
	पूर्ण

	वापस be16_to_cpu(prlo->payload_len);
पूर्ण

u16
fc_tprlo_build(काष्ठा fchs_s *fchs, u32 d_id, u32 s_id, u16 ox_id,
	       पूर्णांक num_pages, क्रमागत fc_tprlo_type tprlo_type, u32 tpr_id)
अणु
	काष्ठा fc_tprlo_s *tprlo = (काष्ठा fc_tprlo_s *) (fchs + 1);
	पूर्णांक             page;

	fc_els_req_build(fchs, d_id, s_id, ox_id);
	स_रखो(tprlo, 0, (num_pages * 16) + 4);
	tprlo->command = FC_ELS_TPRLO;
	tprlo->page_len = 0x10;
	tprlo->payload_len = cpu_to_be16((num_pages * 16) + 4);

	क्रम (page = 0; page < num_pages; page++) अणु
		tprlo->tprlo_params[page].type = FC_TYPE_FCP;
		tprlo->tprlo_params[page].opa_valid = 0;
		tprlo->tprlo_params[page].rpa_valid = 0;
		tprlo->tprlo_params[page].orig_process_assc = 0;
		tprlo->tprlo_params[page].resp_process_assc = 0;
		अगर (tprlo_type == FC_GLOBAL_LOGO) अणु
			tprlo->tprlo_params[page].global_process_logout = 1;
		पूर्ण अन्यथा अगर (tprlo_type == FC_TPR_LOGO) अणु
			tprlo->tprlo_params[page].tpo_nport_valid = 1;
			tprlo->tprlo_params[page].tpo_nport_id = (tpr_id);
		पूर्ण
	पूर्ण

	वापस be16_to_cpu(tprlo->payload_len);
पूर्ण

u16
fc_ba_rjt_build(काष्ठा fchs_s *fchs, u32 d_id, u32 s_id, __be16 ox_id,
		u32 reason_code, u32 reason_expl)
अणु
	काष्ठा fc_ba_rjt_s *ba_rjt = (काष्ठा fc_ba_rjt_s *) (fchs + 1);

	fc_bls_rsp_build(fchs, d_id, s_id, ox_id);

	fchs->cat_info = FC_CAT_BA_RJT;
	ba_rjt->reason_code = reason_code;
	ba_rjt->reason_expl = reason_expl;
	वापस माप(काष्ठा fc_ba_rjt_s);
पूर्ण

अटल व्योम
fc_gs_cthdr_build(काष्ठा ct_hdr_s *cthdr, u32 s_id, u16 cmd_code)
अणु
	स_रखो(cthdr, 0, माप(काष्ठा ct_hdr_s));
	cthdr->rev_id = CT_GS3_REVISION;
	cthdr->gs_type = CT_GSTYPE_सूचीSERVICE;
	cthdr->gs_sub_type = CT_GSSUBTYPE_NAMESERVER;
	cthdr->cmd_rsp_code = cpu_to_be16(cmd_code);
पूर्ण

अटल व्योम
fc_gs_fdmi_cthdr_build(काष्ठा ct_hdr_s *cthdr, u32 s_id, u16 cmd_code)
अणु
	स_रखो(cthdr, 0, माप(काष्ठा ct_hdr_s));
	cthdr->rev_id = CT_GS3_REVISION;
	cthdr->gs_type = CT_GSTYPE_MGMTSERVICE;
	cthdr->gs_sub_type = CT_GSSUBTYPE_HBA_MGMTSERVER;
	cthdr->cmd_rsp_code = cpu_to_be16(cmd_code);
पूर्ण

अटल व्योम
fc_gs_ms_cthdr_build(काष्ठा ct_hdr_s *cthdr, u32 s_id, u16 cmd_code,
					 u8 sub_type)
अणु
	स_रखो(cthdr, 0, माप(काष्ठा ct_hdr_s));
	cthdr->rev_id = CT_GS3_REVISION;
	cthdr->gs_type = CT_GSTYPE_MGMTSERVICE;
	cthdr->gs_sub_type = sub_type;
	cthdr->cmd_rsp_code = cpu_to_be16(cmd_code);
पूर्ण

u16
fc_gidpn_build(काष्ठा fchs_s *fchs, व्योम *pyld, u32 s_id, u16 ox_id,
	       wwn_t port_name)
अणु
	काष्ठा ct_hdr_s *cthdr = (काष्ठा ct_hdr_s *) pyld;
	काष्ठा fcgs_gidpn_req_s *gidpn = (काष्ठा fcgs_gidpn_req_s *)(cthdr + 1);
	u32        d_id = bfa_hton3b(FC_NAME_SERVER);

	fc_gs_fchdr_build(fchs, d_id, s_id, ox_id);
	fc_gs_cthdr_build(cthdr, s_id, GS_GID_PN);

	स_रखो(gidpn, 0, माप(काष्ठा fcgs_gidpn_req_s));
	gidpn->port_name = port_name;
	वापस माप(काष्ठा fcgs_gidpn_req_s) + माप(काष्ठा ct_hdr_s);
पूर्ण

u16
fc_gpnid_build(काष्ठा fchs_s *fchs, व्योम *pyld, u32 s_id, u16 ox_id,
	       u32 port_id)
अणु
	काष्ठा ct_hdr_s *cthdr = (काष्ठा ct_hdr_s *) pyld;
	fcgs_gpnid_req_t *gpnid = (fcgs_gpnid_req_t *) (cthdr + 1);
	u32        d_id = bfa_hton3b(FC_NAME_SERVER);

	fc_gs_fchdr_build(fchs, d_id, s_id, ox_id);
	fc_gs_cthdr_build(cthdr, s_id, GS_GPN_ID);

	स_रखो(gpnid, 0, माप(fcgs_gpnid_req_t));
	gpnid->dap = port_id;
	वापस माप(fcgs_gpnid_req_t) + माप(काष्ठा ct_hdr_s);
पूर्ण

u16
fc_gnnid_build(काष्ठा fchs_s *fchs, व्योम *pyld, u32 s_id, u16 ox_id,
	       u32 port_id)
अणु
	काष्ठा ct_hdr_s *cthdr = (काष्ठा ct_hdr_s *) pyld;
	fcgs_gnnid_req_t *gnnid = (fcgs_gnnid_req_t *) (cthdr + 1);
	u32        d_id = bfa_hton3b(FC_NAME_SERVER);

	fc_gs_fchdr_build(fchs, d_id, s_id, ox_id);
	fc_gs_cthdr_build(cthdr, s_id, GS_GNN_ID);

	स_रखो(gnnid, 0, माप(fcgs_gnnid_req_t));
	gnnid->dap = port_id;
	वापस माप(fcgs_gnnid_req_t) + माप(काष्ठा ct_hdr_s);
पूर्ण

u16
fc_ct_rsp_parse(काष्ठा ct_hdr_s *cthdr)
अणु
	अगर (be16_to_cpu(cthdr->cmd_rsp_code) != CT_RSP_ACCEPT) अणु
		अगर (cthdr->reason_code == CT_RSN_LOGICAL_BUSY)
			वापस FC_PARSE_BUSY;
		अन्यथा
			वापस FC_PARSE_FAILURE;
	पूर्ण

	वापस FC_PARSE_OK;
पूर्ण

u16
fc_gs_rjt_build(काष्ठा fchs_s *fchs,  काष्ठा ct_hdr_s *cthdr,
		u32 d_id, u32 s_id, u16 ox_id, u8 reason_code,
		u8 reason_code_expl)
अणु
	fc_gsresp_fchdr_build(fchs, d_id, s_id, ox_id);

	cthdr->cmd_rsp_code = cpu_to_be16(CT_RSP_REJECT);
	cthdr->rev_id = CT_GS3_REVISION;

	cthdr->reason_code = reason_code;
	cthdr->exp_code    = reason_code_expl;
	वापस माप(काष्ठा ct_hdr_s);
पूर्ण

u16
fc_scr_build(काष्ठा fchs_s *fchs, काष्ठा fc_scr_s *scr,
		u8 set_br_reg, u32 s_id, u16 ox_id)
अणु
	u32        d_id = bfa_hton3b(FC_FABRIC_CONTROLLER);

	fc_els_req_build(fchs, d_id, s_id, ox_id);

	स_रखो(scr, 0, माप(काष्ठा fc_scr_s));
	scr->command = FC_ELS_SCR;
	scr->reg_func = FC_SCR_REG_FUNC_FULL;
	अगर (set_br_reg)
		scr->vu_reg_func = FC_VU_SCR_REG_FUNC_FABRIC_NAME_CHANGE;

	वापस माप(काष्ठा fc_scr_s);
पूर्ण

u16
fc_rscn_build(काष्ठा fchs_s *fchs, काष्ठा fc_rscn_pl_s *rscn,
		u32 s_id, u16 ox_id)
अणु
	u32        d_id = bfa_hton3b(FC_FABRIC_CONTROLLER);
	u16        payldlen;

	fc_els_req_build(fchs, d_id, s_id, ox_id);
	rscn->command = FC_ELS_RSCN;
	rscn->pagelen = माप(rscn->event[0]);

	payldlen = माप(u32) + rscn->pagelen;
	rscn->payldlen = cpu_to_be16(payldlen);

	rscn->event[0].क्रमmat = FC_RSCN_FORMAT_PORTID;
	rscn->event[0].portid = s_id;

	वापस माप(काष्ठा fc_rscn_pl_s);
पूर्ण

u16
fc_rftid_build(काष्ठा fchs_s *fchs, व्योम *pyld, u32 s_id, u16 ox_id,
	       क्रमागत bfa_lport_role roles)
अणु
	काष्ठा ct_hdr_s *cthdr = (काष्ठा ct_hdr_s *) pyld;
	काष्ठा fcgs_rftid_req_s *rftid = (काष्ठा fcgs_rftid_req_s *)(cthdr + 1);
	u32        type_value, d_id = bfa_hton3b(FC_NAME_SERVER);
	u8         index;

	fc_gs_fchdr_build(fchs, d_id, s_id, ox_id);
	fc_gs_cthdr_build(cthdr, s_id, GS_RFT_ID);

	स_रखो(rftid, 0, माप(काष्ठा fcgs_rftid_req_s));

	rftid->dap = s_id;

	/* By शेष, FCP FC4 Type is रेजिस्टरed */
	index = FC_TYPE_FCP >> 5;
	type_value = 1 << (FC_TYPE_FCP % 32);
	rftid->fc4_type[index] = cpu_to_be32(type_value);

	वापस माप(काष्ठा fcgs_rftid_req_s) + माप(काष्ठा ct_hdr_s);
पूर्ण

u16
fc_rftid_build_sol(काष्ठा fchs_s *fchs, व्योम *pyld, u32 s_id, u16 ox_id,
		   u8 *fc4_biपंचांगap, u32 biपंचांगap_size)
अणु
	काष्ठा ct_hdr_s *cthdr = (काष्ठा ct_hdr_s *) pyld;
	काष्ठा fcgs_rftid_req_s *rftid = (काष्ठा fcgs_rftid_req_s *)(cthdr + 1);
	u32        d_id = bfa_hton3b(FC_NAME_SERVER);

	fc_gs_fchdr_build(fchs, d_id, s_id, ox_id);
	fc_gs_cthdr_build(cthdr, s_id, GS_RFT_ID);

	स_रखो(rftid, 0, माप(काष्ठा fcgs_rftid_req_s));

	rftid->dap = s_id;
	स_नकल((व्योम *)rftid->fc4_type, (व्योम *)fc4_biपंचांगap,
		(biपंचांगap_size < 32 ? biपंचांगap_size : 32));

	वापस माप(काष्ठा fcgs_rftid_req_s) + माप(काष्ठा ct_hdr_s);
पूर्ण

u16
fc_rffid_build(काष्ठा fchs_s *fchs, व्योम *pyld, u32 s_id, u16 ox_id,
	       u8 fc4_type, u8 fc4_ftrs)
अणु
	काष्ठा ct_hdr_s *cthdr = (काष्ठा ct_hdr_s *) pyld;
	काष्ठा fcgs_rffid_req_s *rffid = (काष्ठा fcgs_rffid_req_s *)(cthdr + 1);
	u32         d_id = bfa_hton3b(FC_NAME_SERVER);

	fc_gs_fchdr_build(fchs, d_id, s_id, ox_id);
	fc_gs_cthdr_build(cthdr, s_id, GS_RFF_ID);

	स_रखो(rffid, 0, माप(काष्ठा fcgs_rffid_req_s));

	rffid->dap	    = s_id;
	rffid->fc4ftr_bits  = fc4_ftrs;
	rffid->fc4_type	    = fc4_type;

	वापस माप(काष्ठा fcgs_rffid_req_s) + माप(काष्ठा ct_hdr_s);
पूर्ण

u16
fc_rspnid_build(काष्ठा fchs_s *fchs, व्योम *pyld, u32 s_id, u16 ox_id,
		u8 *name)
अणु

	काष्ठा ct_hdr_s *cthdr = (काष्ठा ct_hdr_s *) pyld;
	काष्ठा fcgs_rspnid_req_s *rspnid =
			(काष्ठा fcgs_rspnid_req_s *)(cthdr + 1);
	u32        d_id = bfa_hton3b(FC_NAME_SERVER);

	fc_gs_fchdr_build(fchs, d_id, s_id, ox_id);
	fc_gs_cthdr_build(cthdr, s_id, GS_RSPN_ID);

	स_रखो(rspnid, 0, माप(काष्ठा fcgs_rspnid_req_s));

	rspnid->dap = s_id;
	strlcpy(rspnid->spn, name, माप(rspnid->spn));
	rspnid->spn_len = (u8) म_माप(rspnid->spn);

	वापस माप(काष्ठा fcgs_rspnid_req_s) + माप(काष्ठा ct_hdr_s);
पूर्ण

u16
fc_rsnn_nn_build(काष्ठा fchs_s *fchs, व्योम *pyld, u32 s_id,
			wwn_t node_name, u8 *name)
अणु
	काष्ठा ct_hdr_s *cthdr = (काष्ठा ct_hdr_s *) pyld;
	काष्ठा fcgs_rsnn_nn_req_s *rsnn_nn =
		(काष्ठा fcgs_rsnn_nn_req_s *) (cthdr + 1);
	u32	d_id = bfa_hton3b(FC_NAME_SERVER);

	fc_gs_fchdr_build(fchs, d_id, s_id, 0);
	fc_gs_cthdr_build(cthdr, s_id, GS_RSNN_NN);

	स_रखो(rsnn_nn, 0, माप(काष्ठा fcgs_rsnn_nn_req_s));

	rsnn_nn->node_name = node_name;
	strlcpy(rsnn_nn->snn, name, माप(rsnn_nn->snn));
	rsnn_nn->snn_len = (u8) म_माप(rsnn_nn->snn);

	वापस माप(काष्ठा fcgs_rsnn_nn_req_s) + माप(काष्ठा ct_hdr_s);
पूर्ण

u16
fc_gid_ft_build(काष्ठा fchs_s *fchs, व्योम *pyld, u32 s_id, u8 fc4_type)
अणु

	काष्ठा ct_hdr_s *cthdr = (काष्ठा ct_hdr_s *) pyld;
	काष्ठा fcgs_gidft_req_s *gidft = (काष्ठा fcgs_gidft_req_s *)(cthdr + 1);
	u32        d_id = bfa_hton3b(FC_NAME_SERVER);

	fc_gs_fchdr_build(fchs, d_id, s_id, 0);

	fc_gs_cthdr_build(cthdr, s_id, GS_GID_FT);

	स_रखो(gidft, 0, माप(काष्ठा fcgs_gidft_req_s));
	gidft->fc4_type = fc4_type;
	gidft->करोमुख्य_id = 0;
	gidft->area_id = 0;

	वापस माप(काष्ठा fcgs_gidft_req_s) + माप(काष्ठा ct_hdr_s);
पूर्ण

u16
fc_rpnid_build(काष्ठा fchs_s *fchs, व्योम *pyld, u32 s_id, u32 port_id,
	       wwn_t port_name)
अणु
	काष्ठा ct_hdr_s *cthdr = (काष्ठा ct_hdr_s *) pyld;
	काष्ठा fcgs_rpnid_req_s *rpnid = (काष्ठा fcgs_rpnid_req_s *)(cthdr + 1);
	u32        d_id = bfa_hton3b(FC_NAME_SERVER);

	fc_gs_fchdr_build(fchs, d_id, s_id, 0);
	fc_gs_cthdr_build(cthdr, s_id, GS_RPN_ID);

	स_रखो(rpnid, 0, माप(काष्ठा fcgs_rpnid_req_s));
	rpnid->port_id = port_id;
	rpnid->port_name = port_name;

	वापस माप(काष्ठा fcgs_rpnid_req_s) + माप(काष्ठा ct_hdr_s);
पूर्ण

u16
fc_rnnid_build(काष्ठा fchs_s *fchs, व्योम *pyld, u32 s_id, u32 port_id,
	       wwn_t node_name)
अणु
	काष्ठा ct_hdr_s *cthdr = (काष्ठा ct_hdr_s *) pyld;
	काष्ठा fcgs_rnnid_req_s *rnnid = (काष्ठा fcgs_rnnid_req_s *)(cthdr + 1);
	u32        d_id = bfa_hton3b(FC_NAME_SERVER);

	fc_gs_fchdr_build(fchs, d_id, s_id, 0);
	fc_gs_cthdr_build(cthdr, s_id, GS_RNN_ID);

	स_रखो(rnnid, 0, माप(काष्ठा fcgs_rnnid_req_s));
	rnnid->port_id = port_id;
	rnnid->node_name = node_name;

	वापस माप(काष्ठा fcgs_rnnid_req_s) + माप(काष्ठा ct_hdr_s);
पूर्ण

u16
fc_rcsid_build(काष्ठा fchs_s *fchs, व्योम *pyld, u32 s_id, u32 port_id,
	       u32 cos)
अणु
	काष्ठा ct_hdr_s *cthdr = (काष्ठा ct_hdr_s *) pyld;
	काष्ठा fcgs_rcsid_req_s *rcsid =
			(काष्ठा fcgs_rcsid_req_s *) (cthdr + 1);
	u32        d_id = bfa_hton3b(FC_NAME_SERVER);

	fc_gs_fchdr_build(fchs, d_id, s_id, 0);
	fc_gs_cthdr_build(cthdr, s_id, GS_RCS_ID);

	स_रखो(rcsid, 0, माप(काष्ठा fcgs_rcsid_req_s));
	rcsid->port_id = port_id;
	rcsid->cos = cos;

	वापस माप(काष्ठा fcgs_rcsid_req_s) + माप(काष्ठा ct_hdr_s);
पूर्ण

u16
fc_rptid_build(काष्ठा fchs_s *fchs, व्योम *pyld, u32 s_id, u32 port_id,
	       u8 port_type)
अणु
	काष्ठा ct_hdr_s *cthdr = (काष्ठा ct_hdr_s *) pyld;
	काष्ठा fcgs_rptid_req_s *rptid = (काष्ठा fcgs_rptid_req_s *)(cthdr + 1);
	u32        d_id = bfa_hton3b(FC_NAME_SERVER);

	fc_gs_fchdr_build(fchs, d_id, s_id, 0);
	fc_gs_cthdr_build(cthdr, s_id, GS_RPT_ID);

	स_रखो(rptid, 0, माप(काष्ठा fcgs_rptid_req_s));
	rptid->port_id = port_id;
	rptid->port_type = port_type;

	वापस माप(काष्ठा fcgs_rptid_req_s) + माप(काष्ठा ct_hdr_s);
पूर्ण

u16
fc_ganxt_build(काष्ठा fchs_s *fchs, व्योम *pyld, u32 s_id, u32 port_id)
अणु
	काष्ठा ct_hdr_s *cthdr = (काष्ठा ct_hdr_s *) pyld;
	काष्ठा fcgs_ganxt_req_s *ganxt = (काष्ठा fcgs_ganxt_req_s *)(cthdr + 1);
	u32        d_id = bfa_hton3b(FC_NAME_SERVER);

	fc_gs_fchdr_build(fchs, d_id, s_id, 0);
	fc_gs_cthdr_build(cthdr, s_id, GS_GA_NXT);

	स_रखो(ganxt, 0, माप(काष्ठा fcgs_ganxt_req_s));
	ganxt->port_id = port_id;

	वापस माप(काष्ठा ct_hdr_s) + माप(काष्ठा fcgs_ganxt_req_s);
पूर्ण

/*
 * Builds fc hdr and ct hdr क्रम FDMI requests.
 */
u16
fc_fdmi_reqhdr_build(काष्ठा fchs_s *fchs, व्योम *pyld, u32 s_id,
		     u16 cmd_code)
अणु

	काष्ठा ct_hdr_s *cthdr = (काष्ठा ct_hdr_s *) pyld;
	u32        d_id = bfa_hton3b(FC_MGMT_SERVER);

	fc_gs_fchdr_build(fchs, d_id, s_id, 0);
	fc_gs_fdmi_cthdr_build(cthdr, s_id, cmd_code);

	वापस माप(काष्ठा ct_hdr_s);
पूर्ण

/*
 * Given a FC4 Type, this function वापसs a fc4 type biपंचांगask
 */
व्योम
fc_get_fc4type_biपंचांगask(u8 fc4_type, u8 *bit_mask)
अणु
	u8         index;
	__be32       *ptr = (__be32 *) bit_mask;
	u32        type_value;

	/*
	 * @toकरो : Check क्रम biपंचांगask size
	 */

	index = fc4_type >> 5;
	type_value = 1 << (fc4_type % 32);
	ptr[index] = cpu_to_be32(type_value);

पूर्ण

/*
 *	GMAL Request
 */
u16
fc_gmal_req_build(काष्ठा fchs_s *fchs, व्योम *pyld, u32 s_id, wwn_t wwn)
अणु
	काष्ठा ct_hdr_s *cthdr = (काष्ठा ct_hdr_s *) pyld;
	fcgs_gmal_req_t *gmal = (fcgs_gmal_req_t *) (cthdr + 1);
	u32        d_id = bfa_hton3b(FC_MGMT_SERVER);

	fc_gs_fchdr_build(fchs, d_id, s_id, 0);
	fc_gs_ms_cthdr_build(cthdr, s_id, GS_FC_GMAL_CMD,
			CT_GSSUBTYPE_CFGSERVER);

	स_रखो(gmal, 0, माप(fcgs_gmal_req_t));
	gmal->wwn = wwn;

	वापस माप(काष्ठा ct_hdr_s) + माप(fcgs_gmal_req_t);
पूर्ण

/*
 * GFN (Get Fabric Name) Request
 */
u16
fc_gfn_req_build(काष्ठा fchs_s *fchs, व्योम *pyld, u32 s_id, wwn_t wwn)
अणु
	काष्ठा ct_hdr_s *cthdr = (काष्ठा ct_hdr_s *) pyld;
	fcgs_gfn_req_t *gfn = (fcgs_gfn_req_t *) (cthdr + 1);
	u32        d_id = bfa_hton3b(FC_MGMT_SERVER);

	fc_gs_fchdr_build(fchs, d_id, s_id, 0);
	fc_gs_ms_cthdr_build(cthdr, s_id, GS_FC_GFN_CMD,
			CT_GSSUBTYPE_CFGSERVER);

	स_रखो(gfn, 0, माप(fcgs_gfn_req_t));
	gfn->wwn = wwn;

	वापस माप(काष्ठा ct_hdr_s) + माप(fcgs_gfn_req_t);
पूर्ण
