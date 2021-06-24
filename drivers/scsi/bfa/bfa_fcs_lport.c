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

#समावेश "bfad_drv.h"
#समावेश "bfad_im.h"
#समावेश "bfa_fcs.h"
#समावेश "bfa_fcbuild.h"
#समावेश "bfa_fc.h"

BFA_TRC_खाता(FCS, PORT);

/*
 * ALPA to LIXA biपंचांगap mapping
 *
 * ALPA 0x00 (Word 0, Bit 30) is invalid क्रम N_Ports. Also Word 0 Bit 31
 * is क्रम L_bit (login required) and is filled as ALPA 0x00 here.
 */
अटल स्थिर u8 loop_alpa_map[] = अणु
	0x00, 0x00, 0x01, 0x02, 0x04, 0x08, 0x0F, 0x10, /* Word 0 Bits 31..24 */
	0x17, 0x18, 0x1B, 0x1D, 0x1E, 0x1F, 0x23, 0x25, /* Word 0 Bits 23..16 */
	0x26, 0x27, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, /* Word 0 Bits 15..08 */
	0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x39, 0x3A, /* Word 0 Bits 07..00 */

	0x3C, 0x43, 0x45, 0x46, 0x47, 0x49, 0x4A, 0x4B, /* Word 1 Bits 31..24 */
	0x4C, 0x4D, 0x4E, 0x51, 0x52, 0x53, 0x54, 0x55, /* Word 1 Bits 23..16 */
	0x56, 0x59, 0x5A, 0x5C, 0x63, 0x65, 0x66, 0x67, /* Word 1 Bits 15..08 */
	0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x71, 0x72, /* Word 1 Bits 07..00 */

	0x73, 0x74, 0x75, 0x76, 0x79, 0x7A, 0x7C, 0x80, /* Word 2 Bits 31..24 */
	0x81, 0x82, 0x84, 0x88, 0x8F, 0x90, 0x97, 0x98, /* Word 2 Bits 23..16 */
	0x9B, 0x9D, 0x9E, 0x9F, 0xA3, 0xA5, 0xA6, 0xA7, /* Word 2 Bits 15..08 */
	0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xB1, 0xB2, /* Word 2 Bits 07..00 */

	0xB3, 0xB4, 0xB5, 0xB6, 0xB9, 0xBA, 0xBC, 0xC3, /* Word 3 Bits 31..24 */
	0xC5, 0xC6, 0xC7, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, /* Word 3 Bits 23..16 */
	0xCE, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD9, /* Word 3 Bits 15..08 */
	0xDA, 0xDC, 0xE0, 0xE1, 0xE2, 0xE4, 0xE8, 0xEF, /* Word 3 Bits 07..00 */
पूर्ण;

अटल व्योम     bfa_fcs_lport_send_ls_rjt(काष्ठा bfa_fcs_lport_s *port,
					 काष्ठा fchs_s *rx_fchs, u8 reason_code,
					 u8 reason_code_expl);
अटल व्योम     bfa_fcs_lport_plogi(काष्ठा bfa_fcs_lport_s *port,
			काष्ठा fchs_s *rx_fchs, काष्ठा fc_logi_s *plogi);
अटल व्योम     bfa_fcs_lport_online_actions(काष्ठा bfa_fcs_lport_s *port);
अटल व्योम     bfa_fcs_lport_offline_actions(काष्ठा bfa_fcs_lport_s *port);
अटल व्योम     bfa_fcs_lport_unknown_init(काष्ठा bfa_fcs_lport_s *port);
अटल व्योम     bfa_fcs_lport_unknown_online(काष्ठा bfa_fcs_lport_s *port);
अटल व्योम     bfa_fcs_lport_unknown_offline(काष्ठा bfa_fcs_lport_s *port);
अटल व्योम     bfa_fcs_lport_deleted(काष्ठा bfa_fcs_lport_s *port);
अटल व्योम     bfa_fcs_lport_echo(काष्ठा bfa_fcs_lport_s *port,
			काष्ठा fchs_s *rx_fchs,
			काष्ठा fc_echo_s *echo, u16 len);
अटल व्योम     bfa_fcs_lport_rnid(काष्ठा bfa_fcs_lport_s *port,
			काष्ठा fchs_s *rx_fchs,
			काष्ठा fc_rnid_cmd_s *rnid, u16 len);
अटल व्योम     bfa_fs_port_get_gen_topo_data(काष्ठा bfa_fcs_lport_s *port,
			काष्ठा fc_rnid_general_topology_data_s *gen_topo_data);

अटल व्योम	bfa_fcs_lport_fab_init(काष्ठा bfa_fcs_lport_s *port);
अटल व्योम	bfa_fcs_lport_fab_online(काष्ठा bfa_fcs_lport_s *port);
अटल व्योम	bfa_fcs_lport_fab_offline(काष्ठा bfa_fcs_lport_s *port);

अटल व्योम	bfa_fcs_lport_n2n_init(काष्ठा bfa_fcs_lport_s *port);
अटल व्योम	bfa_fcs_lport_n2n_online(काष्ठा bfa_fcs_lport_s *port);
अटल व्योम	bfa_fcs_lport_n2n_offline(काष्ठा bfa_fcs_lport_s *port);

अटल व्योम	bfa_fcs_lport_loop_init(काष्ठा bfa_fcs_lport_s *port);
अटल व्योम	bfa_fcs_lport_loop_online(काष्ठा bfa_fcs_lport_s *port);
अटल व्योम	bfa_fcs_lport_loop_offline(काष्ठा bfa_fcs_lport_s *port);

अटल काष्ठा अणु
	व्योम		(*init) (काष्ठा bfa_fcs_lport_s *port);
	व्योम		(*online) (काष्ठा bfa_fcs_lport_s *port);
	व्योम		(*offline) (काष्ठा bfa_fcs_lport_s *port);
पूर्ण __port_action[] = अणु
	[BFA_FCS_FABRIC_UNKNOWN] = अणु
		.init = bfa_fcs_lport_unknown_init,
		.online = bfa_fcs_lport_unknown_online,
		.offline = bfa_fcs_lport_unknown_offline
	पूर्ण,
	[BFA_FCS_FABRIC_SWITCHED] = अणु
		.init = bfa_fcs_lport_fab_init,
		.online = bfa_fcs_lport_fab_online,
		.offline = bfa_fcs_lport_fab_offline
	पूर्ण,
	[BFA_FCS_FABRIC_N2N] = अणु
		.init = bfa_fcs_lport_n2n_init,
		.online = bfa_fcs_lport_n2n_online,
		.offline = bfa_fcs_lport_n2n_offline
	पूर्ण,
	[BFA_FCS_FABRIC_LOOP] = अणु
		.init = bfa_fcs_lport_loop_init,
		.online = bfa_fcs_lport_loop_online,
		.offline = bfa_fcs_lport_loop_offline
	पूर्ण,
पूर्ण;

/*
 *  fcs_port_sm FCS logical port state machine
 */

क्रमागत bfa_fcs_lport_event अणु
	BFA_FCS_PORT_SM_CREATE = 1,
	BFA_FCS_PORT_SM_ONLINE = 2,
	BFA_FCS_PORT_SM_OFFLINE = 3,
	BFA_FCS_PORT_SM_DELETE = 4,
	BFA_FCS_PORT_SM_DELRPORT = 5,
	BFA_FCS_PORT_SM_STOP = 6,
पूर्ण;

अटल व्योम     bfa_fcs_lport_sm_uninit(काष्ठा bfa_fcs_lport_s *port,
					क्रमागत bfa_fcs_lport_event event);
अटल व्योम     bfa_fcs_lport_sm_init(काष्ठा bfa_fcs_lport_s *port,
					क्रमागत bfa_fcs_lport_event event);
अटल व्योम     bfa_fcs_lport_sm_online(काष्ठा bfa_fcs_lport_s *port,
					क्रमागत bfa_fcs_lport_event event);
अटल व्योम     bfa_fcs_lport_sm_offline(काष्ठा bfa_fcs_lport_s *port,
					क्रमागत bfa_fcs_lport_event event);
अटल व्योम     bfa_fcs_lport_sm_deleting(काष्ठा bfa_fcs_lport_s *port,
					क्रमागत bfa_fcs_lport_event event);
अटल व्योम	bfa_fcs_lport_sm_stopping(काष्ठा bfa_fcs_lport_s *port,
					क्रमागत bfa_fcs_lport_event event);

अटल व्योम
bfa_fcs_lport_sm_uninit(
	काष्ठा bfa_fcs_lport_s *port,
	क्रमागत bfa_fcs_lport_event event)
अणु
	bfa_trc(port->fcs, port->port_cfg.pwwn);
	bfa_trc(port->fcs, event);

	चयन (event) अणु
	हाल BFA_FCS_PORT_SM_CREATE:
		bfa_sm_set_state(port, bfa_fcs_lport_sm_init);
		अवरोध;

	शेष:
		bfa_sm_fault(port->fcs, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcs_lport_sm_init(काष्ठा bfa_fcs_lport_s *port,
			क्रमागत bfa_fcs_lport_event event)
अणु
	bfa_trc(port->fcs, port->port_cfg.pwwn);
	bfa_trc(port->fcs, event);

	चयन (event) अणु
	हाल BFA_FCS_PORT_SM_ONLINE:
		bfa_sm_set_state(port, bfa_fcs_lport_sm_online);
		bfa_fcs_lport_online_actions(port);
		अवरोध;

	हाल BFA_FCS_PORT_SM_DELETE:
		bfa_sm_set_state(port, bfa_fcs_lport_sm_uninit);
		bfa_fcs_lport_deleted(port);
		अवरोध;

	हाल BFA_FCS_PORT_SM_STOP:
		/* If vport - send completion call back */
		अगर (port->vport)
			bfa_fcs_vport_stop_comp(port->vport);
		अन्यथा
			bfa_wc_करोwn(&(port->fabric->stop_wc));
		अवरोध;

	हाल BFA_FCS_PORT_SM_OFFLINE:
		अवरोध;

	शेष:
		bfa_sm_fault(port->fcs, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcs_lport_sm_online(
	काष्ठा bfa_fcs_lport_s *port,
	क्रमागत bfa_fcs_lport_event event)
अणु
	काष्ठा bfa_fcs_rport_s *rport;
	काष्ठा list_head		*qe, *qen;

	bfa_trc(port->fcs, port->port_cfg.pwwn);
	bfa_trc(port->fcs, event);

	चयन (event) अणु
	हाल BFA_FCS_PORT_SM_OFFLINE:
		bfa_sm_set_state(port, bfa_fcs_lport_sm_offline);
		bfa_fcs_lport_offline_actions(port);
		अवरोध;

	हाल BFA_FCS_PORT_SM_STOP:
		__port_action[port->fabric->fab_type].offline(port);

		अगर (port->num_rports == 0) अणु
			bfa_sm_set_state(port, bfa_fcs_lport_sm_init);
			/* If vport - send completion call back */
			अगर (port->vport)
				bfa_fcs_vport_stop_comp(port->vport);
			अन्यथा
				bfa_wc_करोwn(&(port->fabric->stop_wc));
		पूर्ण अन्यथा अणु
			bfa_sm_set_state(port, bfa_fcs_lport_sm_stopping);
			list_क्रम_each_safe(qe, qen, &port->rport_q) अणु
				rport = (काष्ठा bfa_fcs_rport_s *) qe;
				bfa_sm_send_event(rport, RPSM_EVENT_DELETE);
			पूर्ण
		पूर्ण
		अवरोध;

	हाल BFA_FCS_PORT_SM_DELETE:

		__port_action[port->fabric->fab_type].offline(port);

		अगर (port->num_rports == 0) अणु
			bfa_sm_set_state(port, bfa_fcs_lport_sm_uninit);
			bfa_fcs_lport_deleted(port);
		पूर्ण अन्यथा अणु
			bfa_sm_set_state(port, bfa_fcs_lport_sm_deleting);
			list_क्रम_each_safe(qe, qen, &port->rport_q) अणु
				rport = (काष्ठा bfa_fcs_rport_s *) qe;
				bfa_sm_send_event(rport, RPSM_EVENT_DELETE);
			पूर्ण
		पूर्ण
		अवरोध;

	हाल BFA_FCS_PORT_SM_DELRPORT:
		अवरोध;

	शेष:
		bfa_sm_fault(port->fcs, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcs_lport_sm_offline(
	काष्ठा bfa_fcs_lport_s *port,
	क्रमागत bfa_fcs_lport_event event)
अणु
	काष्ठा bfa_fcs_rport_s *rport;
	काष्ठा list_head		*qe, *qen;

	bfa_trc(port->fcs, port->port_cfg.pwwn);
	bfa_trc(port->fcs, event);

	चयन (event) अणु
	हाल BFA_FCS_PORT_SM_ONLINE:
		bfa_sm_set_state(port, bfa_fcs_lport_sm_online);
		bfa_fcs_lport_online_actions(port);
		अवरोध;

	हाल BFA_FCS_PORT_SM_STOP:
		अगर (port->num_rports == 0) अणु
			bfa_sm_set_state(port, bfa_fcs_lport_sm_init);
			/* If vport - send completion call back */
			अगर (port->vport)
				bfa_fcs_vport_stop_comp(port->vport);
			अन्यथा
				bfa_wc_करोwn(&(port->fabric->stop_wc));
		पूर्ण अन्यथा अणु
			bfa_sm_set_state(port, bfa_fcs_lport_sm_stopping);
			list_क्रम_each_safe(qe, qen, &port->rport_q) अणु
				rport = (काष्ठा bfa_fcs_rport_s *) qe;
				bfa_sm_send_event(rport, RPSM_EVENT_DELETE);
			पूर्ण
		पूर्ण
		अवरोध;

	हाल BFA_FCS_PORT_SM_DELETE:
		अगर (port->num_rports == 0) अणु
			bfa_sm_set_state(port, bfa_fcs_lport_sm_uninit);
			bfa_fcs_lport_deleted(port);
		पूर्ण अन्यथा अणु
			bfa_sm_set_state(port, bfa_fcs_lport_sm_deleting);
			list_क्रम_each_safe(qe, qen, &port->rport_q) अणु
				rport = (काष्ठा bfa_fcs_rport_s *) qe;
				bfa_sm_send_event(rport, RPSM_EVENT_DELETE);
			पूर्ण
		पूर्ण
		अवरोध;

	हाल BFA_FCS_PORT_SM_DELRPORT:
	हाल BFA_FCS_PORT_SM_OFFLINE:
		अवरोध;

	शेष:
		bfa_sm_fault(port->fcs, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcs_lport_sm_stopping(काष्ठा bfa_fcs_lport_s *port,
			  क्रमागत bfa_fcs_lport_event event)
अणु
	bfa_trc(port->fcs, port->port_cfg.pwwn);
	bfa_trc(port->fcs, event);

	चयन (event) अणु
	हाल BFA_FCS_PORT_SM_DELRPORT:
		अगर (port->num_rports == 0) अणु
			bfa_sm_set_state(port, bfa_fcs_lport_sm_init);
			/* If vport - send completion call back */
			अगर (port->vport)
				bfa_fcs_vport_stop_comp(port->vport);
			अन्यथा
				bfa_wc_करोwn(&(port->fabric->stop_wc));
		पूर्ण
		अवरोध;

	शेष:
		bfa_sm_fault(port->fcs, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcs_lport_sm_deleting(
	काष्ठा bfa_fcs_lport_s *port,
	क्रमागत bfa_fcs_lport_event event)
अणु
	bfa_trc(port->fcs, port->port_cfg.pwwn);
	bfa_trc(port->fcs, event);

	चयन (event) अणु
	हाल BFA_FCS_PORT_SM_DELRPORT:
		अगर (port->num_rports == 0) अणु
			bfa_sm_set_state(port, bfa_fcs_lport_sm_uninit);
			bfa_fcs_lport_deleted(port);
		पूर्ण
		अवरोध;

	शेष:
		bfa_sm_fault(port->fcs, event);
	पूर्ण
पूर्ण

/*
 *  fcs_port_pvt
 */

/*
 * Send AEN notअगरication
 */
अटल व्योम
bfa_fcs_lport_aen_post(काष्ठा bfa_fcs_lport_s *port,
			क्रमागत bfa_lport_aen_event event)
अणु
	काष्ठा bfad_s *bfad = (काष्ठा bfad_s *)port->fabric->fcs->bfad;
	काष्ठा bfa_aen_entry_s  *aen_entry;

	bfad_get_aen_entry(bfad, aen_entry);
	अगर (!aen_entry)
		वापस;

	aen_entry->aen_data.lport.vf_id = port->fabric->vf_id;
	aen_entry->aen_data.lport.roles = port->port_cfg.roles;
	aen_entry->aen_data.lport.ppwwn = bfa_fcs_lport_get_pwwn(
					bfa_fcs_get_base_port(port->fcs));
	aen_entry->aen_data.lport.lpwwn = bfa_fcs_lport_get_pwwn(port);

	/* Send the AEN notअगरication */
	bfad_im_post_venकरोr_event(aen_entry, bfad, ++port->fcs->fcs_aen_seq,
				  BFA_AEN_CAT_LPORT, event);
पूर्ण

/*
 * Send a LS reject
 */
अटल व्योम
bfa_fcs_lport_send_ls_rjt(काष्ठा bfa_fcs_lport_s *port, काष्ठा fchs_s *rx_fchs,
			 u8 reason_code, u8 reason_code_expl)
अणु
	काष्ठा fchs_s	fchs;
	काष्ठा bfa_fcxp_s *fcxp;
	काष्ठा bfa_rport_s *bfa_rport = शून्य;
	पूर्णांक		len;

	bfa_trc(port->fcs, rx_fchs->d_id);
	bfa_trc(port->fcs, rx_fchs->s_id);

	fcxp = bfa_fcs_fcxp_alloc(port->fcs, BFA_FALSE);
	अगर (!fcxp)
		वापस;

	len = fc_ls_rjt_build(&fchs, bfa_fcxp_get_reqbuf(fcxp),
			      rx_fchs->s_id, bfa_fcs_lport_get_fcid(port),
			      rx_fchs->ox_id, reason_code, reason_code_expl);

	bfa_fcxp_send(fcxp, bfa_rport, port->fabric->vf_id, port->lp_tag,
			  BFA_FALSE, FC_CLASS_3, len, &fchs, शून्य, शून्य,
			  FC_MAX_PDUSZ, 0);
पूर्ण

/*
 * Send a FCCT Reject
 */
अटल व्योम
bfa_fcs_lport_send_fcgs_rjt(काष्ठा bfa_fcs_lport_s *port,
	काष्ठा fchs_s *rx_fchs, u8 reason_code, u8 reason_code_expl)
अणु
	काष्ठा fchs_s   fchs;
	काष्ठा bfa_fcxp_s *fcxp;
	काष्ठा bfa_rport_s *bfa_rport = शून्य;
	पूर्णांक             len;
	काष्ठा ct_hdr_s *rx_cthdr = (काष्ठा ct_hdr_s *)(rx_fchs + 1);
	काष्ठा ct_hdr_s *ct_hdr;

	bfa_trc(port->fcs, rx_fchs->d_id);
	bfa_trc(port->fcs, rx_fchs->s_id);

	fcxp = bfa_fcs_fcxp_alloc(port->fcs, BFA_FALSE);
	अगर (!fcxp)
		वापस;

	ct_hdr = bfa_fcxp_get_reqbuf(fcxp);
	ct_hdr->gs_type = rx_cthdr->gs_type;
	ct_hdr->gs_sub_type = rx_cthdr->gs_sub_type;

	len = fc_gs_rjt_build(&fchs, ct_hdr, rx_fchs->s_id,
			bfa_fcs_lport_get_fcid(port),
			rx_fchs->ox_id, reason_code, reason_code_expl);

	bfa_fcxp_send(fcxp, bfa_rport, port->fabric->vf_id, port->lp_tag,
			BFA_FALSE, FC_CLASS_3, len, &fchs, शून्य, शून्य,
			FC_MAX_PDUSZ, 0);
पूर्ण

/*
 * Process incoming plogi from a remote port.
 */
अटल व्योम
bfa_fcs_lport_plogi(काष्ठा bfa_fcs_lport_s *port,
		काष्ठा fchs_s *rx_fchs, काष्ठा fc_logi_s *plogi)
अणु
	काष्ठा bfa_fcs_rport_s *rport;

	bfa_trc(port->fcs, rx_fchs->d_id);
	bfa_trc(port->fcs, rx_fchs->s_id);

	/*
	 * If min cfg mode is enabled, drop any incoming PLOGIs
	 */
	अगर (__fcs_min_cfg(port->fcs)) अणु
		bfa_trc(port->fcs, rx_fchs->s_id);
		वापस;
	पूर्ण

	अगर (fc_plogi_parse(rx_fchs) != FC_PARSE_OK) अणु
		bfa_trc(port->fcs, rx_fchs->s_id);
		/*
		 * send a LS reject
		 */
		bfa_fcs_lport_send_ls_rjt(port, rx_fchs,
					FC_LS_RJT_RSN_PROTOCOL_ERROR,
					FC_LS_RJT_EXP_SPARMS_ERR_OPTIONS);
		वापस;
	पूर्ण

	/*
	 * Direct Attach P2P mode : verअगरy address asचिन्हित by the r-port.
	 */
	अगर ((!bfa_fcs_fabric_is_चयनed(port->fabric)) &&
		(स_भेद((व्योम *)&bfa_fcs_lport_get_pwwn(port),
			   (व्योम *)&plogi->port_name, माप(wwn_t)) < 0)) अणु
		अगर (BFA_FCS_PID_IS_WKA(rx_fchs->d_id)) अणु
			/* Address asचिन्हित to us cannot be a WKA */
			bfa_fcs_lport_send_ls_rjt(port, rx_fchs,
					FC_LS_RJT_RSN_PROTOCOL_ERROR,
					FC_LS_RJT_EXP_INVALID_NPORT_ID);
			वापस;
		पूर्ण
		port->pid  = rx_fchs->d_id;
		bfa_lps_set_n2n_pid(port->fabric->lps, rx_fchs->d_id);
	पूर्ण

	/*
	 * First, check अगर we know the device by pwwn.
	 */
	rport = bfa_fcs_lport_get_rport_by_pwwn(port, plogi->port_name);
	अगर (rport) अणु
		/*
		 * Direct Attach P2P mode : handle address asचिन्हित by r-port.
		 */
		अगर ((!bfa_fcs_fabric_is_चयनed(port->fabric)) &&
			(स_भेद((व्योम *)&bfa_fcs_lport_get_pwwn(port),
			(व्योम *)&plogi->port_name, माप(wwn_t)) < 0)) अणु
			port->pid  = rx_fchs->d_id;
			bfa_lps_set_n2n_pid(port->fabric->lps, rx_fchs->d_id);
			rport->pid = rx_fchs->s_id;
		पूर्ण
		bfa_fcs_rport_plogi(rport, rx_fchs, plogi);
		वापस;
	पूर्ण

	/*
	 * Next, lookup rport by PID.
	 */
	rport = bfa_fcs_lport_get_rport_by_pid(port, rx_fchs->s_id);
	अगर (!rport) अणु
		/*
		 * Inbound PLOGI from a new device.
		 */
		bfa_fcs_rport_plogi_create(port, rx_fchs, plogi);
		वापस;
	पूर्ण

	/*
	 * Rport is known only by PID.
	 */
	अगर (rport->pwwn) अणु
		/*
		 * This is a dअगरferent device with the same pid. Old device
		 * disappeared. Send implicit LOGO to old device.
		 */
		WARN_ON(rport->pwwn == plogi->port_name);
		bfa_sm_send_event(rport, RPSM_EVENT_LOGO_IMP);

		/*
		 * Inbound PLOGI from a new device (with old PID).
		 */
		bfa_fcs_rport_plogi_create(port, rx_fchs, plogi);
		वापस;
	पूर्ण

	/*
	 * PLOGI crossing each other.
	 */
	WARN_ON(rport->pwwn != WWN_शून्य);
	bfa_fcs_rport_plogi(rport, rx_fchs, plogi);
पूर्ण

/*
 * Process incoming ECHO.
 * Since it करोes not require a login, it is processed here.
 */
अटल व्योम
bfa_fcs_lport_echo(काष्ठा bfa_fcs_lport_s *port, काष्ठा fchs_s *rx_fchs,
		काष्ठा fc_echo_s *echo, u16 rx_len)
अणु
	काष्ठा fchs_s		fchs;
	काष्ठा bfa_fcxp_s	*fcxp;
	काष्ठा bfa_rport_s	*bfa_rport = शून्य;
	पूर्णांक			len, pyld_len;

	bfa_trc(port->fcs, rx_fchs->s_id);
	bfa_trc(port->fcs, rx_fchs->d_id);

	fcxp = bfa_fcs_fcxp_alloc(port->fcs, BFA_FALSE);
	अगर (!fcxp)
		वापस;

	len = fc_ls_acc_build(&fchs, bfa_fcxp_get_reqbuf(fcxp),
				rx_fchs->s_id, bfa_fcs_lport_get_fcid(port),
				rx_fchs->ox_id);

	/*
	 * Copy the payload (अगर any) from the echo frame
	 */
	pyld_len = rx_len - माप(काष्ठा fchs_s);
	bfa_trc(port->fcs, rx_len);
	bfa_trc(port->fcs, pyld_len);

	अगर (pyld_len > len)
		स_नकल(((u8 *) bfa_fcxp_get_reqbuf(fcxp)) +
			माप(काष्ठा fc_echo_s), (echo + 1),
			(pyld_len - माप(काष्ठा fc_echo_s)));

	bfa_fcxp_send(fcxp, bfa_rport, port->fabric->vf_id, port->lp_tag,
			BFA_FALSE, FC_CLASS_3, pyld_len, &fchs, शून्य, शून्य,
			FC_MAX_PDUSZ, 0);
पूर्ण

/*
 * Process incoming RNID.
 * Since it करोes not require a login, it is processed here.
 */
अटल व्योम
bfa_fcs_lport_rnid(काष्ठा bfa_fcs_lport_s *port, काष्ठा fchs_s *rx_fchs,
		काष्ठा fc_rnid_cmd_s *rnid, u16 rx_len)
अणु
	काष्ठा fc_rnid_common_id_data_s common_id_data;
	काष्ठा fc_rnid_general_topology_data_s gen_topo_data;
	काष्ठा fchs_s	fchs;
	काष्ठा bfa_fcxp_s *fcxp;
	काष्ठा bfa_rport_s *bfa_rport = शून्य;
	u16	len;
	u32	data_क्रमmat;

	bfa_trc(port->fcs, rx_fchs->s_id);
	bfa_trc(port->fcs, rx_fchs->d_id);
	bfa_trc(port->fcs, rx_len);

	fcxp = bfa_fcs_fcxp_alloc(port->fcs, BFA_FALSE);
	अगर (!fcxp)
		वापस;

	/*
	 * Check Node Indentअगरication Data Format
	 * We only support General Topology Discovery Format.
	 * For any other requested Data Formats, we वापस Common Node Id Data
	 * only, as per FC-LS.
	 */
	bfa_trc(port->fcs, rnid->node_id_data_क्रमmat);
	अगर (rnid->node_id_data_क्रमmat == RNID_NODEID_DATA_FORMAT_DISCOVERY) अणु
		data_क्रमmat = RNID_NODEID_DATA_FORMAT_DISCOVERY;
		/*
		 * Get General topology data क्रम this port
		 */
		bfa_fs_port_get_gen_topo_data(port, &gen_topo_data);
	पूर्ण अन्यथा अणु
		data_क्रमmat = RNID_NODEID_DATA_FORMAT_COMMON;
	पूर्ण

	/*
	 * Copy the Node Id Info
	 */
	common_id_data.port_name = bfa_fcs_lport_get_pwwn(port);
	common_id_data.node_name = bfa_fcs_lport_get_nwwn(port);

	len = fc_rnid_acc_build(&fchs, bfa_fcxp_get_reqbuf(fcxp),
				rx_fchs->s_id, bfa_fcs_lport_get_fcid(port),
				rx_fchs->ox_id, data_क्रमmat, &common_id_data,
				&gen_topo_data);

	bfa_fcxp_send(fcxp, bfa_rport, port->fabric->vf_id, port->lp_tag,
			BFA_FALSE, FC_CLASS_3, len, &fchs, शून्य, शून्य,
			FC_MAX_PDUSZ, 0);
पूर्ण

/*
 *  Fill out General Topolpgy Discovery Data क्रम RNID ELS.
 */
अटल व्योम
bfa_fs_port_get_gen_topo_data(काष्ठा bfa_fcs_lport_s *port,
			काष्ठा fc_rnid_general_topology_data_s *gen_topo_data)
अणु
	स_रखो(gen_topo_data, 0,
		      माप(काष्ठा fc_rnid_general_topology_data_s));

	gen_topo_data->asso_type = cpu_to_be32(RNID_ASSOCIATED_TYPE_HOST);
	gen_topo_data->phy_port_num = 0;	/* @toकरो */
	gen_topo_data->num_attached_nodes = cpu_to_be32(1);
पूर्ण

अटल व्योम
bfa_fcs_lport_online_actions(काष्ठा bfa_fcs_lport_s *port)
अणु
	काष्ठा bfad_s *bfad = (काष्ठा bfad_s *)port->fcs->bfad;
	अक्षर	lpwwn_buf[BFA_STRING_32];

	bfa_trc(port->fcs, port->fabric->oper_type);

	__port_action[port->fabric->fab_type].init(port);
	__port_action[port->fabric->fab_type].online(port);

	wwn2str(lpwwn_buf, bfa_fcs_lport_get_pwwn(port));
	BFA_LOG(KERN_WARNING, bfad, bfa_log_level,
		"Logical port online: WWN = %s Role = %s\n",
		lpwwn_buf, "Initiator");
	bfa_fcs_lport_aen_post(port, BFA_LPORT_AEN_ONLINE);

	bfad->bfad_flags |= BFAD_PORT_ONLINE;
पूर्ण

अटल व्योम
bfa_fcs_lport_offline_actions(काष्ठा bfa_fcs_lport_s *port)
अणु
	काष्ठा list_head	*qe, *qen;
	काष्ठा bfa_fcs_rport_s *rport;
	काष्ठा bfad_s *bfad = (काष्ठा bfad_s *)port->fcs->bfad;
	अक्षर    lpwwn_buf[BFA_STRING_32];

	bfa_trc(port->fcs, port->fabric->oper_type);

	__port_action[port->fabric->fab_type].offline(port);

	wwn2str(lpwwn_buf, bfa_fcs_lport_get_pwwn(port));
	अगर (bfa_sm_cmp_state(port->fabric,
			bfa_fcs_fabric_sm_online) == BFA_TRUE) अणु
		BFA_LOG(KERN_WARNING, bfad, bfa_log_level,
		"Logical port lost fabric connectivity: WWN = %s Role = %s\n",
		lpwwn_buf, "Initiator");
		bfa_fcs_lport_aen_post(port, BFA_LPORT_AEN_DISCONNECT);
	पूर्ण अन्यथा अणु
		BFA_LOG(KERN_WARNING, bfad, bfa_log_level,
		"Logical port taken offline: WWN = %s Role = %s\n",
		lpwwn_buf, "Initiator");
		bfa_fcs_lport_aen_post(port, BFA_LPORT_AEN_OFFLINE);
	पूर्ण

	list_क्रम_each_safe(qe, qen, &port->rport_q) अणु
		rport = (काष्ठा bfa_fcs_rport_s *) qe;
		bfa_sm_send_event(rport, RPSM_EVENT_LOGO_IMP);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcs_lport_unknown_init(काष्ठा bfa_fcs_lport_s *port)
अणु
	WARN_ON(1);
पूर्ण

अटल व्योम
bfa_fcs_lport_unknown_online(काष्ठा bfa_fcs_lport_s *port)
अणु
	WARN_ON(1);
पूर्ण

अटल व्योम
bfa_fcs_lport_unknown_offline(काष्ठा bfa_fcs_lport_s *port)
अणु
	WARN_ON(1);
पूर्ण

अटल व्योम
bfa_fcs_lport_abts_acc(काष्ठा bfa_fcs_lport_s *port, काष्ठा fchs_s *rx_fchs)
अणु
	काष्ठा fchs_s fchs;
	काष्ठा bfa_fcxp_s *fcxp;
	पूर्णांक		len;

	bfa_trc(port->fcs, rx_fchs->d_id);
	bfa_trc(port->fcs, rx_fchs->s_id);

	fcxp = bfa_fcs_fcxp_alloc(port->fcs, BFA_FALSE);
	अगर (!fcxp)
		वापस;

	len = fc_ba_acc_build(&fchs, bfa_fcxp_get_reqbuf(fcxp),
			rx_fchs->s_id, bfa_fcs_lport_get_fcid(port),
			rx_fchs->ox_id, 0);

	bfa_fcxp_send(fcxp, शून्य, port->fabric->vf_id, port->lp_tag,
			  BFA_FALSE, FC_CLASS_3, len, &fchs, शून्य, शून्य,
			  FC_MAX_PDUSZ, 0);
पूर्ण
अटल व्योम
bfa_fcs_lport_deleted(काष्ठा bfa_fcs_lport_s *port)
अणु
	काष्ठा bfad_s *bfad = (काष्ठा bfad_s *)port->fcs->bfad;
	अक्षर    lpwwn_buf[BFA_STRING_32];

	wwn2str(lpwwn_buf, bfa_fcs_lport_get_pwwn(port));
	BFA_LOG(KERN_INFO, bfad, bfa_log_level,
		"Logical port deleted: WWN = %s Role = %s\n",
		lpwwn_buf, "Initiator");
	bfa_fcs_lport_aen_post(port, BFA_LPORT_AEN_DELETE);

	/* Base port will be deleted by the OS driver */
	अगर (port->vport)
		bfa_fcs_vport_delete_comp(port->vport);
	अन्यथा
		bfa_wc_करोwn(&port->fabric->wc);
पूर्ण


/*
 * Unsolicited frame receive handling.
 */
व्योम
bfa_fcs_lport_uf_recv(काष्ठा bfa_fcs_lport_s *lport,
			काष्ठा fchs_s *fchs, u16 len)
अणु
	u32	pid = fchs->s_id;
	काष्ठा bfa_fcs_rport_s *rport = शून्य;
	काष्ठा fc_els_cmd_s *els_cmd = (काष्ठा fc_els_cmd_s *) (fchs + 1);

	bfa_stats(lport, uf_recvs);
	bfa_trc(lport->fcs, fchs->type);

	अगर (!bfa_fcs_lport_is_online(lport)) अणु
		/*
		 * In direct attach topology, it is possible to get a PLOGI
		 * beक्रमe the lport is online due to port feature
		 * (QoS/Trunk/FEC/CR), so send a rjt
		 */
		अगर ((fchs->type == FC_TYPE_ELS) &&
			(els_cmd->els_code == FC_ELS_PLOGI)) अणु
			bfa_fcs_lport_send_ls_rjt(lport, fchs,
				FC_LS_RJT_RSN_UNABLE_TO_PERF_CMD,
				FC_LS_RJT_EXP_NO_ADDL_INFO);
			bfa_stats(lport, plogi_rcvd);
		पूर्ण अन्यथा
			bfa_stats(lport, uf_recv_drops);

		वापस;
	पूर्ण

	/*
	 * First, handle ELSs that करोnot require a login.
	 */
	/*
	 * Handle PLOGI first
	 */
	अगर ((fchs->type == FC_TYPE_ELS) &&
		(els_cmd->els_code == FC_ELS_PLOGI)) अणु
		bfa_fcs_lport_plogi(lport, fchs, (काष्ठा fc_logi_s *) els_cmd);
		वापस;
	पूर्ण

	/*
	 * Handle ECHO separately.
	 */
	अगर ((fchs->type == FC_TYPE_ELS) && (els_cmd->els_code == FC_ELS_ECHO)) अणु
		bfa_fcs_lport_echo(lport, fchs,
				(काष्ठा fc_echo_s *)els_cmd, len);
		वापस;
	पूर्ण

	/*
	 * Handle RNID separately.
	 */
	अगर ((fchs->type == FC_TYPE_ELS) && (els_cmd->els_code == FC_ELS_RNID)) अणु
		bfa_fcs_lport_rnid(lport, fchs,
			(काष्ठा fc_rnid_cmd_s *) els_cmd, len);
		वापस;
	पूर्ण

	अगर (fchs->type == FC_TYPE_BLS) अणु
		अगर ((fchs->routing == FC_RTG_BASIC_LINK) &&
				(fchs->cat_info == FC_CAT_ABTS))
			bfa_fcs_lport_abts_acc(lport, fchs);
		वापस;
	पूर्ण

	अगर (fchs->type == FC_TYPE_SERVICES) अणु
		/*
		 * Unhandled FC-GS frames. Send a FC-CT Reject
		 */
		bfa_fcs_lport_send_fcgs_rjt(lport, fchs, CT_RSN_NOT_SUPP,
				CT_NS_EXP_NOADDITIONAL);
		वापस;
	पूर्ण

	/*
	 * look क्रम a matching remote port ID
	 */
	rport = bfa_fcs_lport_get_rport_by_pid(lport, pid);
	अगर (rport) अणु
		bfa_trc(rport->fcs, fchs->s_id);
		bfa_trc(rport->fcs, fchs->d_id);
		bfa_trc(rport->fcs, fchs->type);

		bfa_fcs_rport_uf_recv(rport, fchs, len);
		वापस;
	पूर्ण

	/*
	 * Only handles ELS frames क्रम now.
	 */
	अगर (fchs->type != FC_TYPE_ELS) अणु
		bfa_trc(lport->fcs, fchs->s_id);
		bfa_trc(lport->fcs, fchs->d_id);
		/* ignore type FC_TYPE_FC_FSS */
		अगर (fchs->type != FC_TYPE_FC_FSS)
			bfa_sm_fault(lport->fcs, fchs->type);
		वापस;
	पूर्ण

	bfa_trc(lport->fcs, els_cmd->els_code);
	अगर (els_cmd->els_code == FC_ELS_RSCN) अणु
		bfa_fcs_lport_scn_process_rscn(lport, fchs, len);
		वापस;
	पूर्ण

	अगर (els_cmd->els_code == FC_ELS_LOGO) अणु
		/*
		 * @toकरो Handle LOGO frames received.
		 */
		वापस;
	पूर्ण

	अगर (els_cmd->els_code == FC_ELS_PRLI) अणु
		/*
		 * @toकरो Handle PRLI frames received.
		 */
		वापस;
	पूर्ण

	/*
	 * Unhandled ELS frames. Send a LS_RJT.
	 */
	bfa_fcs_lport_send_ls_rjt(lport, fchs, FC_LS_RJT_RSN_CMD_NOT_SUPP,
				 FC_LS_RJT_EXP_NO_ADDL_INFO);

पूर्ण

/*
 *   PID based Lookup क्रम a R-Port in the Port R-Port Queue
 */
काष्ठा bfa_fcs_rport_s *
bfa_fcs_lport_get_rport_by_pid(काष्ठा bfa_fcs_lport_s *port, u32 pid)
अणु
	काष्ठा bfa_fcs_rport_s *rport;
	काष्ठा list_head	*qe;

	list_क्रम_each(qe, &port->rport_q) अणु
		rport = (काष्ठा bfa_fcs_rport_s *) qe;
		अगर (rport->pid == pid)
			वापस rport;
	पूर्ण

	bfa_trc(port->fcs, pid);
	वापस शून्य;
पूर्ण

/*
 * OLD_PID based Lookup क्रम a R-Port in the Port R-Port Queue
 */
काष्ठा bfa_fcs_rport_s *
bfa_fcs_lport_get_rport_by_old_pid(काष्ठा bfa_fcs_lport_s *port, u32 pid)
अणु
	काष्ठा bfa_fcs_rport_s *rport;
	काष्ठा list_head	*qe;

	list_क्रम_each(qe, &port->rport_q) अणु
		rport = (काष्ठा bfa_fcs_rport_s *) qe;
		अगर (rport->old_pid == pid)
			वापस rport;
	पूर्ण

	bfa_trc(port->fcs, pid);
	वापस शून्य;
पूर्ण

/*
 *   PWWN based Lookup क्रम a R-Port in the Port R-Port Queue
 */
काष्ठा bfa_fcs_rport_s *
bfa_fcs_lport_get_rport_by_pwwn(काष्ठा bfa_fcs_lport_s *port, wwn_t pwwn)
अणु
	काष्ठा bfa_fcs_rport_s *rport;
	काष्ठा list_head	*qe;

	list_क्रम_each(qe, &port->rport_q) अणु
		rport = (काष्ठा bfa_fcs_rport_s *) qe;
		अगर (wwn_is_equal(rport->pwwn, pwwn))
			वापस rport;
	पूर्ण

	bfa_trc(port->fcs, pwwn);
	वापस शून्य;
पूर्ण

/*
 *   NWWN based Lookup क्रम a R-Port in the Port R-Port Queue
 */
काष्ठा bfa_fcs_rport_s *
bfa_fcs_lport_get_rport_by_nwwn(काष्ठा bfa_fcs_lport_s *port, wwn_t nwwn)
अणु
	काष्ठा bfa_fcs_rport_s *rport;
	काष्ठा list_head	*qe;

	list_क्रम_each(qe, &port->rport_q) अणु
		rport = (काष्ठा bfa_fcs_rport_s *) qe;
		अगर (wwn_is_equal(rport->nwwn, nwwn))
			वापस rport;
	पूर्ण

	bfa_trc(port->fcs, nwwn);
	वापस शून्य;
पूर्ण

/*
 * PWWN & PID based Lookup क्रम a R-Port in the Port R-Port Queue
 */
काष्ठा bfa_fcs_rport_s *
bfa_fcs_lport_get_rport_by_qualअगरier(काष्ठा bfa_fcs_lport_s *port,
				     wwn_t pwwn, u32 pid)
अणु
	काष्ठा bfa_fcs_rport_s *rport;
	काष्ठा list_head	*qe;

	list_क्रम_each(qe, &port->rport_q) अणु
		rport = (काष्ठा bfa_fcs_rport_s *) qe;
		अगर (wwn_is_equal(rport->pwwn, pwwn) && rport->pid == pid)
			वापस rport;
	पूर्ण

	bfa_trc(port->fcs, pwwn);
	वापस शून्य;
पूर्ण

/*
 * Called by rport module when new rports are discovered.
 */
व्योम
bfa_fcs_lport_add_rport(
	काष्ठा bfa_fcs_lport_s *port,
	काष्ठा bfa_fcs_rport_s *rport)
अणु
	list_add_tail(&rport->qe, &port->rport_q);
	port->num_rports++;
पूर्ण

/*
 * Called by rport module to when rports are deleted.
 */
व्योम
bfa_fcs_lport_del_rport(
	काष्ठा bfa_fcs_lport_s *port,
	काष्ठा bfa_fcs_rport_s *rport)
अणु
	WARN_ON(!bfa_q_is_on_q(&port->rport_q, rport));
	list_del(&rport->qe);
	port->num_rports--;

	bfa_sm_send_event(port, BFA_FCS_PORT_SM_DELRPORT);
पूर्ण

/*
 * Called by fabric क्रम base port when fabric login is complete.
 * Called by vport क्रम भव ports when FDISC is complete.
 */
व्योम
bfa_fcs_lport_online(काष्ठा bfa_fcs_lport_s *port)
अणु
	bfa_sm_send_event(port, BFA_FCS_PORT_SM_ONLINE);
पूर्ण

/*
 * Called by fabric क्रम base port when fabric goes offline.
 * Called by vport क्रम भव ports when भव port becomes offline.
 */
व्योम
bfa_fcs_lport_offline(काष्ठा bfa_fcs_lport_s *port)
अणु
	bfa_sm_send_event(port, BFA_FCS_PORT_SM_OFFLINE);
पूर्ण

/*
 * Called by fabric क्रम base port and by vport क्रम भव ports
 * when target mode driver is unloaded.
 */
व्योम
bfa_fcs_lport_stop(काष्ठा bfa_fcs_lport_s *port)
अणु
	bfa_sm_send_event(port, BFA_FCS_PORT_SM_STOP);
पूर्ण

/*
 * Called by fabric to delete base lport and associated resources.
 *
 * Called by vport to delete lport and associated resources. Should call
 * bfa_fcs_vport_delete_comp() क्रम vports on completion.
 */
व्योम
bfa_fcs_lport_delete(काष्ठा bfa_fcs_lport_s *port)
अणु
	bfa_sm_send_event(port, BFA_FCS_PORT_SM_DELETE);
पूर्ण

/*
 * Return TRUE अगर port is online, अन्यथा वापस FALSE
 */
bfa_boolean_t
bfa_fcs_lport_is_online(काष्ठा bfa_fcs_lport_s *port)
अणु
	वापस bfa_sm_cmp_state(port, bfa_fcs_lport_sm_online);
पूर्ण

/*
  * Attach समय initialization of logical ports.
 */
व्योम
bfa_fcs_lport_attach(काष्ठा bfa_fcs_lport_s *lport, काष्ठा bfa_fcs_s *fcs,
		   u16 vf_id, काष्ठा bfa_fcs_vport_s *vport)
अणु
	lport->fcs = fcs;
	lport->fabric = bfa_fcs_vf_lookup(fcs, vf_id);
	lport->vport = vport;
	lport->lp_tag = (vport) ? vport->lps->bfa_tag :
				  lport->fabric->lps->bfa_tag;

	INIT_LIST_HEAD(&lport->rport_q);
	lport->num_rports = 0;
पूर्ण

/*
 * Logical port initialization of base or भव port.
 * Called by fabric क्रम base port or by vport क्रम भव ports.
 */

व्योम
bfa_fcs_lport_init(काष्ठा bfa_fcs_lport_s *lport,
	काष्ठा bfa_lport_cfg_s *port_cfg)
अणु
	काष्ठा bfa_fcs_vport_s *vport = lport->vport;
	काष्ठा bfad_s *bfad = (काष्ठा bfad_s *)lport->fcs->bfad;
	अक्षर    lpwwn_buf[BFA_STRING_32];

	lport->port_cfg = *port_cfg;

	lport->bfad_port = bfa_fcb_lport_new(lport->fcs->bfad, lport,
					lport->port_cfg.roles,
					lport->fabric->vf_drv,
					vport ? vport->vport_drv : शून्य);

	wwn2str(lpwwn_buf, bfa_fcs_lport_get_pwwn(lport));
	BFA_LOG(KERN_INFO, bfad, bfa_log_level,
		"New logical port created: WWN = %s Role = %s\n",
		lpwwn_buf, "Initiator");
	bfa_fcs_lport_aen_post(lport, BFA_LPORT_AEN_NEW);

	bfa_sm_set_state(lport, bfa_fcs_lport_sm_uninit);
	bfa_sm_send_event(lport, BFA_FCS_PORT_SM_CREATE);
पूर्ण

व्योम
bfa_fcs_lport_set_symname(काष्ठा bfa_fcs_lport_s *port,
				अक्षर *symname)
अणु
	म_नकल(port->port_cfg.sym_name.symname, symname);

	अगर (bfa_sm_cmp_state(port, bfa_fcs_lport_sm_online))
		bfa_fcs_lport_ns_util_send_rspn_id(
			BFA_FCS_GET_NS_FROM_PORT(port), शून्य);
पूर्ण

/*
 *  fcs_lport_api
 */

व्योम
bfa_fcs_lport_get_attr(
	काष्ठा bfa_fcs_lport_s *port,
	काष्ठा bfa_lport_attr_s *port_attr)
अणु
	अगर (bfa_sm_cmp_state(port, bfa_fcs_lport_sm_online))
		port_attr->pid = port->pid;
	अन्यथा
		port_attr->pid = 0;

	port_attr->port_cfg = port->port_cfg;

	अगर (port->fabric) अणु
		port_attr->port_type = port->fabric->oper_type;
		port_attr->loopback = bfa_sm_cmp_state(port->fabric,
				bfa_fcs_fabric_sm_loopback);
		port_attr->authfail =
			bfa_sm_cmp_state(port->fabric,
				bfa_fcs_fabric_sm_auth_failed);
		port_attr->fabric_name  = bfa_fcs_lport_get_fabric_name(port);
		स_नकल(port_attr->fabric_ip_addr,
			bfa_fcs_lport_get_fabric_ipaddr(port),
			BFA_FCS_FABRIC_IPADDR_SZ);

		अगर (port->vport != शून्य) अणु
			port_attr->port_type = BFA_PORT_TYPE_VPORT;
			port_attr->fpma_mac =
				port->vport->lps->lp_mac;
		पूर्ण अन्यथा अणु
			port_attr->fpma_mac =
				port->fabric->lps->lp_mac;
		पूर्ण
	पूर्ण अन्यथा अणु
		port_attr->port_type = BFA_PORT_TYPE_UNKNOWN;
		port_attr->state = BFA_LPORT_UNINIT;
	पूर्ण
पूर्ण

/*
 *  bfa_fcs_lport_fab port fab functions
 */

/*
 *   Called by port to initialize fabric services of the base port.
 */
अटल व्योम
bfa_fcs_lport_fab_init(काष्ठा bfa_fcs_lport_s *port)
अणु
	bfa_fcs_lport_ns_init(port);
	bfa_fcs_lport_scn_init(port);
	bfa_fcs_lport_ms_init(port);
पूर्ण

/*
 *   Called by port to notअगरy transition to online state.
 */
अटल व्योम
bfa_fcs_lport_fab_online(काष्ठा bfa_fcs_lport_s *port)
अणु
	bfa_fcs_lport_ns_online(port);
	bfa_fcs_lport_fab_scn_online(port);
पूर्ण

/*
 *   Called by port to notअगरy transition to offline state.
 */
अटल व्योम
bfa_fcs_lport_fab_offline(काष्ठा bfa_fcs_lport_s *port)
अणु
	bfa_fcs_lport_ns_offline(port);
	bfa_fcs_lport_scn_offline(port);
	bfa_fcs_lport_ms_offline(port);
पूर्ण

/*
 *  bfa_fcs_lport_n2n  functions
 */

/*
 *   Called by fcs/port to initialize N2N topology.
 */
अटल व्योम
bfa_fcs_lport_n2n_init(काष्ठा bfa_fcs_lport_s *port)
अणु
पूर्ण

/*
 *   Called by fcs/port to notअगरy transition to online state.
 */
अटल व्योम
bfa_fcs_lport_n2n_online(काष्ठा bfa_fcs_lport_s *port)
अणु
	काष्ठा bfa_fcs_lport_n2n_s *n2n_port = &port->port_topo.pn2n;
	काष्ठा bfa_lport_cfg_s *pcfg = &port->port_cfg;
	काष्ठा bfa_fcs_rport_s *rport;

	bfa_trc(port->fcs, pcfg->pwwn);

	/*
	 * If our PWWN is > than that of the r-port, we have to initiate PLOGI
	 * and assign an Address. अगर not, we need to रुको क्रम its PLOGI.
	 *
	 * If our PWWN is < than that of the remote port, it will send a PLOGI
	 * with the PIDs asचिन्हित. The rport state machine take care of this
	 * incoming PLOGI.
	 */
	अगर (स_भेद
	    ((व्योम *)&pcfg->pwwn, (व्योम *)&n2n_port->rem_port_wwn,
	     माप(wwn_t)) > 0) अणु
		port->pid = N2N_LOCAL_PID;
		bfa_lps_set_n2n_pid(port->fabric->lps, N2N_LOCAL_PID);
		/*
		 * First, check अगर we know the device by pwwn.
		 */
		rport = bfa_fcs_lport_get_rport_by_pwwn(port,
							n2n_port->rem_port_wwn);
		अगर (rport) अणु
			bfa_trc(port->fcs, rport->pid);
			bfa_trc(port->fcs, rport->pwwn);
			rport->pid = N2N_REMOTE_PID;
			bfa_sm_send_event(rport, RPSM_EVENT_PLOGI_SEND);
			वापस;
		पूर्ण

		/*
		 * In n2n there can be only one rport. Delete the old one
		 * whose pid should be zero, because it is offline.
		 */
		अगर (port->num_rports > 0) अणु
			rport = bfa_fcs_lport_get_rport_by_pid(port, 0);
			WARN_ON(rport == शून्य);
			अगर (rport) अणु
				bfa_trc(port->fcs, rport->pwwn);
				bfa_sm_send_event(rport, RPSM_EVENT_DELETE);
			पूर्ण
		पूर्ण
		bfa_fcs_rport_create(port, N2N_REMOTE_PID);
	पूर्ण
पूर्ण

/*
 *   Called by fcs/port to notअगरy transition to offline state.
 */
अटल व्योम
bfa_fcs_lport_n2n_offline(काष्ठा bfa_fcs_lport_s *port)
अणु
	काष्ठा bfa_fcs_lport_n2n_s *n2n_port = &port->port_topo.pn2n;

	bfa_trc(port->fcs, port->pid);
	port->pid = 0;
	n2n_port->rem_port_wwn = 0;
	n2n_port->reply_oxid = 0;
पूर्ण

अटल व्योम
bfa_fcport_get_loop_attr(काष्ठा bfa_fcs_lport_s *port)
अणु
	पूर्णांक i = 0, j = 0, bit = 0, alpa_bit = 0;
	u8 k = 0;
	काष्ठा bfa_fcport_s *fcport = BFA_FCPORT_MOD(port->fcs->bfa);

	port->port_topo.ploop.alpabm_valid = fcport->alpabm_valid;
	port->pid = fcport->myalpa;
	port->pid = bfa_hton3b(port->pid);

	क्रम (i = 0; i < (FC_ALPA_MAX / 8); i++) अणु
		क्रम (j = 0, alpa_bit = 0; j < 8; j++, alpa_bit++) अणु
			bfa_trc(port->fcs->bfa, fcport->alpabm.alpa_bm[i]);
			bit = (fcport->alpabm.alpa_bm[i] & (1 << (7 - j)));
			अगर (bit) अणु
				port->port_topo.ploop.alpa_pos_map[k] =
					loop_alpa_map[(i * 8) + alpa_bit];
				k++;
				bfa_trc(port->fcs->bfa, k);
				bfa_trc(port->fcs->bfa,
					 port->port_topo.ploop.alpa_pos_map[k]);
			पूर्ण
		पूर्ण
	पूर्ण
	port->port_topo.ploop.num_alpa = k;
पूर्ण

/*
 * Called by fcs/port to initialize Loop topology.
 */
अटल व्योम
bfa_fcs_lport_loop_init(काष्ठा bfa_fcs_lport_s *port)
अणु
पूर्ण

/*
 * Called by fcs/port to notअगरy transition to online state.
 */
अटल व्योम
bfa_fcs_lport_loop_online(काष्ठा bfa_fcs_lport_s *port)
अणु
	u8 num_alpa = 0, alpabm_valid = 0;
	काष्ठा bfa_fcs_rport_s *rport;
	u8 *alpa_map = शून्य;
	पूर्णांक i = 0;
	u32 pid;

	bfa_fcport_get_loop_attr(port);

	num_alpa = port->port_topo.ploop.num_alpa;
	alpabm_valid = port->port_topo.ploop.alpabm_valid;
	alpa_map = port->port_topo.ploop.alpa_pos_map;

	bfa_trc(port->fcs->bfa, port->pid);
	bfa_trc(port->fcs->bfa, num_alpa);
	अगर (alpabm_valid == 1) अणु
		क्रम (i = 0; i < num_alpa; i++) अणु
			bfa_trc(port->fcs->bfa, alpa_map[i]);
			अगर (alpa_map[i] != bfa_hton3b(port->pid)) अणु
				pid = alpa_map[i];
				bfa_trc(port->fcs->bfa, pid);
				rport = bfa_fcs_lport_get_rport_by_pid(port,
						bfa_hton3b(pid));
				अगर (!rport)
					rport = bfa_fcs_rport_create(port,
						bfa_hton3b(pid));
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < MAX_ALPA_COUNT; i++) अणु
			अगर (alpa_map[i] != port->pid) अणु
				pid = loop_alpa_map[i];
				bfa_trc(port->fcs->bfa, pid);
				rport = bfa_fcs_lport_get_rport_by_pid(port,
						bfa_hton3b(pid));
				अगर (!rport)
					rport = bfa_fcs_rport_create(port,
						bfa_hton3b(pid));
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Called by fcs/port to notअगरy transition to offline state.
 */
अटल व्योम
bfa_fcs_lport_loop_offline(काष्ठा bfa_fcs_lport_s *port)
अणु
पूर्ण

#घोषणा BFA_FCS_FDMI_CMD_MAX_RETRIES 2

/*
 * क्रमward declarations
 */
अटल व्योम     bfa_fcs_lport_fdmi_send_rhba(व्योम *fdmi_cbarg,
					    काष्ठा bfa_fcxp_s *fcxp_alloced);
अटल व्योम     bfa_fcs_lport_fdmi_send_rprt(व्योम *fdmi_cbarg,
					    काष्ठा bfa_fcxp_s *fcxp_alloced);
अटल व्योम     bfa_fcs_lport_fdmi_send_rpa(व्योम *fdmi_cbarg,
					   काष्ठा bfa_fcxp_s *fcxp_alloced);
अटल व्योम     bfa_fcs_lport_fdmi_rhba_response(व्योम *fcsarg,
						काष्ठा bfa_fcxp_s *fcxp,
						व्योम *cbarg,
						bfa_status_t req_status,
						u32 rsp_len,
						u32 resid_len,
						काष्ठा fchs_s *rsp_fchs);
अटल व्योम     bfa_fcs_lport_fdmi_rprt_response(व्योम *fcsarg,
						काष्ठा bfa_fcxp_s *fcxp,
						व्योम *cbarg,
						bfa_status_t req_status,
						u32 rsp_len,
						u32 resid_len,
						काष्ठा fchs_s *rsp_fchs);
अटल व्योम     bfa_fcs_lport_fdmi_rpa_response(व्योम *fcsarg,
					       काष्ठा bfa_fcxp_s *fcxp,
					       व्योम *cbarg,
					       bfa_status_t req_status,
					       u32 rsp_len,
					       u32 resid_len,
					       काष्ठा fchs_s *rsp_fchs);
अटल व्योम     bfa_fcs_lport_fdmi_समयout(व्योम *arg);
अटल पूर्णांक bfa_fcs_lport_fdmi_build_rhba_pyld(काष्ठा bfa_fcs_lport_fdmi_s *fdmi,
						  u8 *pyld);
अटल u16 bfa_fcs_lport_fdmi_build_rprt_pyld(काष्ठा bfa_fcs_lport_fdmi_s *fdmi,
						  u8 *pyld);
अटल u16 bfa_fcs_lport_fdmi_build_rpa_pyld(काष्ठा bfa_fcs_lport_fdmi_s *fdmi,
						 u8 *pyld);
अटल u16 bfa_fcs_lport_fdmi_build_portattr_block(काष्ठा bfa_fcs_lport_fdmi_s *
						       fdmi, u8 *pyld);
अटल व्योम	bfa_fcs_fdmi_get_hbaattr(काष्ठा bfa_fcs_lport_fdmi_s *fdmi,
				 काष्ठा bfa_fcs_fdmi_hba_attr_s *hba_attr);
अटल व्योम	bfa_fcs_fdmi_get_portattr(काष्ठा bfa_fcs_lport_fdmi_s *fdmi,
				  काष्ठा bfa_fcs_fdmi_port_attr_s *port_attr);
u32	bfa_fcs_fdmi_convert_speed(क्रमागत bfa_port_speed pport_speed);

/*
 *  fcs_fdmi_sm FCS FDMI state machine
 */

/*
 *  FDMI State Machine events
 */
क्रमागत port_fdmi_event अणु
	FDMISM_EVENT_PORT_ONLINE = 1,
	FDMISM_EVENT_PORT_OFFLINE = 2,
	FDMISM_EVENT_RSP_OK = 4,
	FDMISM_EVENT_RSP_ERROR = 5,
	FDMISM_EVENT_TIMEOUT = 6,
	FDMISM_EVENT_RHBA_SENT = 7,
	FDMISM_EVENT_RPRT_SENT = 8,
	FDMISM_EVENT_RPA_SENT = 9,
पूर्ण;

अटल व्योम     bfa_fcs_lport_fdmi_sm_offline(काष्ठा bfa_fcs_lport_fdmi_s *fdmi,
					     क्रमागत port_fdmi_event event);
अटल व्योम     bfa_fcs_lport_fdmi_sm_sending_rhba(
				काष्ठा bfa_fcs_lport_fdmi_s *fdmi,
				क्रमागत port_fdmi_event event);
अटल व्योम     bfa_fcs_lport_fdmi_sm_rhba(काष्ठा bfa_fcs_lport_fdmi_s *fdmi,
					  क्रमागत port_fdmi_event event);
अटल व्योम     bfa_fcs_lport_fdmi_sm_rhba_retry(
				काष्ठा bfa_fcs_lport_fdmi_s *fdmi,
				क्रमागत port_fdmi_event event);
अटल व्योम     bfa_fcs_lport_fdmi_sm_sending_rprt(
				काष्ठा bfa_fcs_lport_fdmi_s *fdmi,
				क्रमागत port_fdmi_event event);
अटल व्योम     bfa_fcs_lport_fdmi_sm_rprt(काष्ठा bfa_fcs_lport_fdmi_s *fdmi,
					  क्रमागत port_fdmi_event event);
अटल व्योम     bfa_fcs_lport_fdmi_sm_rprt_retry(
				काष्ठा bfa_fcs_lport_fdmi_s *fdmi,
				क्रमागत port_fdmi_event event);
अटल व्योम     bfa_fcs_lport_fdmi_sm_sending_rpa(
				काष्ठा bfa_fcs_lport_fdmi_s *fdmi,
				क्रमागत port_fdmi_event event);
अटल व्योम     bfa_fcs_lport_fdmi_sm_rpa(काष्ठा bfa_fcs_lport_fdmi_s *fdmi,
					 क्रमागत port_fdmi_event event);
अटल व्योम     bfa_fcs_lport_fdmi_sm_rpa_retry(
				काष्ठा bfa_fcs_lport_fdmi_s *fdmi,
				क्रमागत port_fdmi_event event);
अटल व्योम     bfa_fcs_lport_fdmi_sm_online(काष्ठा bfa_fcs_lport_fdmi_s *fdmi,
					    क्रमागत port_fdmi_event event);
अटल व्योम     bfa_fcs_lport_fdmi_sm_disabled(
				काष्ठा bfa_fcs_lport_fdmi_s *fdmi,
				क्रमागत port_fdmi_event event);
/*
 *	Start in offline state - aरुकोing MS to send start.
 */
अटल व्योम
bfa_fcs_lport_fdmi_sm_offline(काष्ठा bfa_fcs_lport_fdmi_s *fdmi,
			     क्रमागत port_fdmi_event event)
अणु
	काष्ठा bfa_fcs_lport_s *port = fdmi->ms->port;

	bfa_trc(port->fcs, port->port_cfg.pwwn);
	bfa_trc(port->fcs, event);

	fdmi->retry_cnt = 0;

	चयन (event) अणु
	हाल FDMISM_EVENT_PORT_ONLINE:
		अगर (port->vport) अणु
			/*
			 * For Vports, रेजिस्टर a new port.
			 */
			bfa_sm_set_state(fdmi,
					 bfa_fcs_lport_fdmi_sm_sending_rprt);
			bfa_fcs_lport_fdmi_send_rprt(fdmi, शून्य);
		पूर्ण अन्यथा अणु
			/*
			 * For a base port, we should first रेजिस्टर the HBA
			 * attribute. The HBA attribute also contains the base
			 *  port registration.
			 */
			bfa_sm_set_state(fdmi,
					 bfa_fcs_lport_fdmi_sm_sending_rhba);
			bfa_fcs_lport_fdmi_send_rhba(fdmi, शून्य);
		पूर्ण
		अवरोध;

	हाल FDMISM_EVENT_PORT_OFFLINE:
		अवरोध;

	शेष:
		bfa_sm_fault(port->fcs, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcs_lport_fdmi_sm_sending_rhba(काष्ठा bfa_fcs_lport_fdmi_s *fdmi,
				  क्रमागत port_fdmi_event event)
अणु
	काष्ठा bfa_fcs_lport_s *port = fdmi->ms->port;

	bfa_trc(port->fcs, port->port_cfg.pwwn);
	bfa_trc(port->fcs, event);

	चयन (event) अणु
	हाल FDMISM_EVENT_RHBA_SENT:
		bfa_sm_set_state(fdmi, bfa_fcs_lport_fdmi_sm_rhba);
		अवरोध;

	हाल FDMISM_EVENT_PORT_OFFLINE:
		bfa_sm_set_state(fdmi, bfa_fcs_lport_fdmi_sm_offline);
		bfa_fcxp_walloc_cancel(BFA_FCS_GET_HAL_FROM_PORT(port),
					   &fdmi->fcxp_wqe);
		अवरोध;

	शेष:
		bfa_sm_fault(port->fcs, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcs_lport_fdmi_sm_rhba(काष्ठा bfa_fcs_lport_fdmi_s *fdmi,
			क्रमागत port_fdmi_event event)
अणु
	काष्ठा bfa_fcs_lport_s *port = fdmi->ms->port;

	bfa_trc(port->fcs, port->port_cfg.pwwn);
	bfa_trc(port->fcs, event);

	चयन (event) अणु
	हाल FDMISM_EVENT_RSP_ERROR:
		/*
		 * अगर max retries have not been reached, start समयr क्रम a
		 * delayed retry
		 */
		अगर (fdmi->retry_cnt++ < BFA_FCS_FDMI_CMD_MAX_RETRIES) अणु
			bfa_sm_set_state(fdmi,
					bfa_fcs_lport_fdmi_sm_rhba_retry);
			bfa_समयr_start(BFA_FCS_GET_HAL_FROM_PORT(port),
					    &fdmi->समयr,
					    bfa_fcs_lport_fdmi_समयout, fdmi,
					    BFA_FCS_RETRY_TIMEOUT);
		पूर्ण अन्यथा अणु
			/*
			 * set state to offline
			 */
			bfa_sm_set_state(fdmi, bfa_fcs_lport_fdmi_sm_offline);
		पूर्ण
		अवरोध;

	हाल FDMISM_EVENT_RSP_OK:
		/*
		 * Initiate Register Port Attributes
		 */
		bfa_sm_set_state(fdmi, bfa_fcs_lport_fdmi_sm_sending_rpa);
		fdmi->retry_cnt = 0;
		bfa_fcs_lport_fdmi_send_rpa(fdmi, शून्य);
		अवरोध;

	हाल FDMISM_EVENT_PORT_OFFLINE:
		bfa_fcxp_discard(fdmi->fcxp);
		bfa_sm_set_state(fdmi, bfa_fcs_lport_fdmi_sm_offline);
		अवरोध;

	शेष:
		bfa_sm_fault(port->fcs, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcs_lport_fdmi_sm_rhba_retry(काष्ठा bfa_fcs_lport_fdmi_s *fdmi,
				क्रमागत port_fdmi_event event)
अणु
	काष्ठा bfa_fcs_lport_s *port = fdmi->ms->port;

	bfa_trc(port->fcs, port->port_cfg.pwwn);
	bfa_trc(port->fcs, event);

	चयन (event) अणु
	हाल FDMISM_EVENT_TIMEOUT:
		/*
		 * Retry Timer Expired. Re-send
		 */
		bfa_sm_set_state(fdmi, bfa_fcs_lport_fdmi_sm_sending_rhba);
		bfa_fcs_lport_fdmi_send_rhba(fdmi, शून्य);
		अवरोध;

	हाल FDMISM_EVENT_PORT_OFFLINE:
		bfa_sm_set_state(fdmi, bfa_fcs_lport_fdmi_sm_offline);
		bfa_समयr_stop(&fdmi->समयr);
		अवरोध;

	शेष:
		bfa_sm_fault(port->fcs, event);
	पूर्ण
पूर्ण

/*
* RPRT : Register Port
 */
अटल व्योम
bfa_fcs_lport_fdmi_sm_sending_rprt(काष्ठा bfa_fcs_lport_fdmi_s *fdmi,
				  क्रमागत port_fdmi_event event)
अणु
	काष्ठा bfa_fcs_lport_s *port = fdmi->ms->port;

	bfa_trc(port->fcs, port->port_cfg.pwwn);
	bfa_trc(port->fcs, event);

	चयन (event) अणु
	हाल FDMISM_EVENT_RPRT_SENT:
		bfa_sm_set_state(fdmi, bfa_fcs_lport_fdmi_sm_rprt);
		अवरोध;

	हाल FDMISM_EVENT_PORT_OFFLINE:
		bfa_sm_set_state(fdmi, bfa_fcs_lport_fdmi_sm_offline);
		bfa_fcxp_walloc_cancel(BFA_FCS_GET_HAL_FROM_PORT(port),
					   &fdmi->fcxp_wqe);
		अवरोध;

	शेष:
		bfa_sm_fault(port->fcs, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcs_lport_fdmi_sm_rprt(काष्ठा bfa_fcs_lport_fdmi_s *fdmi,
			क्रमागत port_fdmi_event event)
अणु
	काष्ठा bfa_fcs_lport_s *port = fdmi->ms->port;

	bfa_trc(port->fcs, port->port_cfg.pwwn);
	bfa_trc(port->fcs, event);

	चयन (event) अणु
	हाल FDMISM_EVENT_RSP_ERROR:
		/*
		 * अगर max retries have not been reached, start समयr क्रम a
		 * delayed retry
		 */
		अगर (fdmi->retry_cnt++ < BFA_FCS_FDMI_CMD_MAX_RETRIES) अणु
			bfa_sm_set_state(fdmi,
					bfa_fcs_lport_fdmi_sm_rprt_retry);
			bfa_समयr_start(BFA_FCS_GET_HAL_FROM_PORT(port),
					    &fdmi->समयr,
					    bfa_fcs_lport_fdmi_समयout, fdmi,
					    BFA_FCS_RETRY_TIMEOUT);

		पूर्ण अन्यथा अणु
			/*
			 * set state to offline
			 */
			bfa_sm_set_state(fdmi, bfa_fcs_lport_fdmi_sm_offline);
			fdmi->retry_cnt = 0;
		पूर्ण
		अवरोध;

	हाल FDMISM_EVENT_RSP_OK:
		fdmi->retry_cnt = 0;
		bfa_sm_set_state(fdmi, bfa_fcs_lport_fdmi_sm_online);
		अवरोध;

	हाल FDMISM_EVENT_PORT_OFFLINE:
		bfa_fcxp_discard(fdmi->fcxp);
		bfa_sm_set_state(fdmi, bfa_fcs_lport_fdmi_sm_offline);
		अवरोध;

	शेष:
		bfa_sm_fault(port->fcs, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcs_lport_fdmi_sm_rprt_retry(काष्ठा bfa_fcs_lport_fdmi_s *fdmi,
				क्रमागत port_fdmi_event event)
अणु
	काष्ठा bfa_fcs_lport_s *port = fdmi->ms->port;

	bfa_trc(port->fcs, port->port_cfg.pwwn);
	bfa_trc(port->fcs, event);

	चयन (event) अणु
	हाल FDMISM_EVENT_TIMEOUT:
		/*
		 * Retry Timer Expired. Re-send
		 */
		bfa_sm_set_state(fdmi, bfa_fcs_lport_fdmi_sm_sending_rprt);
		bfa_fcs_lport_fdmi_send_rprt(fdmi, शून्य);
		अवरोध;

	हाल FDMISM_EVENT_PORT_OFFLINE:
		bfa_sm_set_state(fdmi, bfa_fcs_lport_fdmi_sm_offline);
		bfa_समयr_stop(&fdmi->समयr);
		अवरोध;

	शेष:
		bfa_sm_fault(port->fcs, event);
	पूर्ण
पूर्ण

/*
 * Register Port Attributes
 */
अटल व्योम
bfa_fcs_lport_fdmi_sm_sending_rpa(काष्ठा bfa_fcs_lport_fdmi_s *fdmi,
				 क्रमागत port_fdmi_event event)
अणु
	काष्ठा bfa_fcs_lport_s *port = fdmi->ms->port;

	bfa_trc(port->fcs, port->port_cfg.pwwn);
	bfa_trc(port->fcs, event);

	चयन (event) अणु
	हाल FDMISM_EVENT_RPA_SENT:
		bfa_sm_set_state(fdmi, bfa_fcs_lport_fdmi_sm_rpa);
		अवरोध;

	हाल FDMISM_EVENT_PORT_OFFLINE:
		bfa_sm_set_state(fdmi, bfa_fcs_lport_fdmi_sm_offline);
		bfa_fcxp_walloc_cancel(BFA_FCS_GET_HAL_FROM_PORT(port),
					   &fdmi->fcxp_wqe);
		अवरोध;

	शेष:
		bfa_sm_fault(port->fcs, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcs_lport_fdmi_sm_rpa(काष्ठा bfa_fcs_lport_fdmi_s *fdmi,
			क्रमागत port_fdmi_event event)
अणु
	काष्ठा bfa_fcs_lport_s *port = fdmi->ms->port;

	bfa_trc(port->fcs, port->port_cfg.pwwn);
	bfa_trc(port->fcs, event);

	चयन (event) अणु
	हाल FDMISM_EVENT_RSP_ERROR:
		/*
		 * अगर max retries have not been reached, start समयr क्रम a
		 * delayed retry
		 */
		अगर (fdmi->retry_cnt++ < BFA_FCS_FDMI_CMD_MAX_RETRIES) अणु
			bfa_sm_set_state(fdmi, bfa_fcs_lport_fdmi_sm_rpa_retry);
			bfa_समयr_start(BFA_FCS_GET_HAL_FROM_PORT(port),
					    &fdmi->समयr,
					    bfa_fcs_lport_fdmi_समयout, fdmi,
					    BFA_FCS_RETRY_TIMEOUT);
		पूर्ण अन्यथा अणु
			/*
			 * set state to offline
			 */
			bfa_sm_set_state(fdmi, bfa_fcs_lport_fdmi_sm_offline);
			fdmi->retry_cnt = 0;
		पूर्ण
		अवरोध;

	हाल FDMISM_EVENT_RSP_OK:
		bfa_sm_set_state(fdmi, bfa_fcs_lport_fdmi_sm_online);
		fdmi->retry_cnt = 0;
		अवरोध;

	हाल FDMISM_EVENT_PORT_OFFLINE:
		bfa_fcxp_discard(fdmi->fcxp);
		bfa_sm_set_state(fdmi, bfa_fcs_lport_fdmi_sm_offline);
		अवरोध;

	शेष:
		bfa_sm_fault(port->fcs, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcs_lport_fdmi_sm_rpa_retry(काष्ठा bfa_fcs_lport_fdmi_s *fdmi,
			       क्रमागत port_fdmi_event event)
अणु
	काष्ठा bfa_fcs_lport_s *port = fdmi->ms->port;

	bfa_trc(port->fcs, port->port_cfg.pwwn);
	bfa_trc(port->fcs, event);

	चयन (event) अणु
	हाल FDMISM_EVENT_TIMEOUT:
		/*
		 * Retry Timer Expired. Re-send
		 */
		bfa_sm_set_state(fdmi, bfa_fcs_lport_fdmi_sm_sending_rpa);
		bfa_fcs_lport_fdmi_send_rpa(fdmi, शून्य);
		अवरोध;

	हाल FDMISM_EVENT_PORT_OFFLINE:
		bfa_sm_set_state(fdmi, bfa_fcs_lport_fdmi_sm_offline);
		bfa_समयr_stop(&fdmi->समयr);
		अवरोध;

	शेष:
		bfa_sm_fault(port->fcs, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcs_lport_fdmi_sm_online(काष्ठा bfa_fcs_lport_fdmi_s *fdmi,
				क्रमागत port_fdmi_event event)
अणु
	काष्ठा bfa_fcs_lport_s *port = fdmi->ms->port;

	bfa_trc(port->fcs, port->port_cfg.pwwn);
	bfa_trc(port->fcs, event);

	चयन (event) अणु
	हाल FDMISM_EVENT_PORT_OFFLINE:
		bfa_sm_set_state(fdmi, bfa_fcs_lport_fdmi_sm_offline);
		अवरोध;

	शेष:
		bfa_sm_fault(port->fcs, event);
	पूर्ण
पूर्ण
/*
 *  FDMI is disabled state.
 */
अटल व्योम
bfa_fcs_lport_fdmi_sm_disabled(काष्ठा bfa_fcs_lport_fdmi_s *fdmi,
			     क्रमागत port_fdmi_event event)
अणु
	काष्ठा bfa_fcs_lport_s *port = fdmi->ms->port;

	bfa_trc(port->fcs, port->port_cfg.pwwn);
	bfa_trc(port->fcs, event);

	/* No op State. It can only be enabled at Driver Init. */
पूर्ण

/*
*  RHBA : Register HBA Attributes.
 */
अटल व्योम
bfa_fcs_lport_fdmi_send_rhba(व्योम *fdmi_cbarg, काष्ठा bfa_fcxp_s *fcxp_alloced)
अणु
	काष्ठा bfa_fcs_lport_fdmi_s *fdmi = fdmi_cbarg;
	काष्ठा bfa_fcs_lport_s *port = fdmi->ms->port;
	काष्ठा fchs_s fchs;
	पूर्णांक             len, attr_len;
	काष्ठा bfa_fcxp_s *fcxp;
	u8        *pyld;

	bfa_trc(port->fcs, port->port_cfg.pwwn);

	fcxp = fcxp_alloced ? fcxp_alloced :
	       bfa_fcs_fcxp_alloc(port->fcs, BFA_TRUE);
	अगर (!fcxp) अणु
		bfa_fcs_fcxp_alloc_रुको(port->fcs->bfa, &fdmi->fcxp_wqe,
				bfa_fcs_lport_fdmi_send_rhba, fdmi, BFA_TRUE);
		वापस;
	पूर्ण
	fdmi->fcxp = fcxp;

	pyld = bfa_fcxp_get_reqbuf(fcxp);
	स_रखो(pyld, 0, FC_MAX_PDUSZ);

	len = fc_fdmi_reqhdr_build(&fchs, pyld, bfa_fcs_lport_get_fcid(port),
				   FDMI_RHBA);

	attr_len =
		bfa_fcs_lport_fdmi_build_rhba_pyld(fdmi,
					  (u8 *) ((काष्ठा ct_hdr_s *) pyld
						       + 1));
	अगर (attr_len < 0)
		वापस;

	bfa_fcxp_send(fcxp, शून्य, port->fabric->vf_id, port->lp_tag, BFA_FALSE,
			  FC_CLASS_3, (len + attr_len), &fchs,
			  bfa_fcs_lport_fdmi_rhba_response, (व्योम *)fdmi,
			  FC_MAX_PDUSZ, FC_FCCT_TOV);

	bfa_sm_send_event(fdmi, FDMISM_EVENT_RHBA_SENT);
पूर्ण

अटल पूर्णांक
bfa_fcs_lport_fdmi_build_rhba_pyld(काष्ठा bfa_fcs_lport_fdmi_s *fdmi, u8 *pyld)
अणु
	काष्ठा bfa_fcs_lport_s *port = fdmi->ms->port;
	काष्ठा bfa_fcs_fdmi_hba_attr_s *fcs_hba_attr;
	काष्ठा fdmi_rhba_s *rhba = (काष्ठा fdmi_rhba_s *) pyld;
	काष्ठा fdmi_attr_s *attr;
	पूर्णांक        len;
	u8        *curr_ptr;
	u16	templen, count;

	fcs_hba_attr = kzalloc(माप(*fcs_hba_attr), GFP_KERNEL);
	अगर (!fcs_hba_attr)
		वापस -ENOMEM;

	/*
	 * get hba attributes
	 */
	bfa_fcs_fdmi_get_hbaattr(fdmi, fcs_hba_attr);

	rhba->hba_id = bfa_fcs_lport_get_pwwn(port);
	rhba->port_list.num_ports = cpu_to_be32(1);
	rhba->port_list.port_entry = bfa_fcs_lport_get_pwwn(port);

	len = माप(rhba->hba_id) + माप(rhba->port_list);

	count = 0;
	len += माप(rhba->hba_attr_blk.attr_count);

	/*
	 * fill out the invididual entries of the HBA attrib Block
	 */
	curr_ptr = (u8 *) &rhba->hba_attr_blk.hba_attr;

	/*
	 * Node Name
	 */
	attr = (काष्ठा fdmi_attr_s *) curr_ptr;
	attr->type = cpu_to_be16(FDMI_HBA_ATTRIB_NODENAME);
	templen = माप(wwn_t);
	स_नकल(attr->value, &bfa_fcs_lport_get_nwwn(port), templen);
	curr_ptr += माप(attr->type) + माप(templen) + templen;
	len += templen;
	count++;
	attr->len = cpu_to_be16(templen + माप(attr->type) +
			     माप(templen));

	/*
	 * Manufacturer
	 */
	attr = (काष्ठा fdmi_attr_s *) curr_ptr;
	attr->type = cpu_to_be16(FDMI_HBA_ATTRIB_MANUFACTURER);
	templen = (u16) म_माप(fcs_hba_attr->manufacturer);
	स_नकल(attr->value, fcs_hba_attr->manufacturer, templen);
	templen = fc_roundup(templen, माप(u32));
	curr_ptr += माप(attr->type) + माप(templen) + templen;
	len += templen;
	count++;
	attr->len = cpu_to_be16(templen + माप(attr->type) +
			     माप(templen));

	/*
	 * Serial Number
	 */
	attr = (काष्ठा fdmi_attr_s *) curr_ptr;
	attr->type = cpu_to_be16(FDMI_HBA_ATTRIB_SERIALNUM);
	templen = (u16) म_माप(fcs_hba_attr->serial_num);
	स_नकल(attr->value, fcs_hba_attr->serial_num, templen);
	templen = fc_roundup(templen, माप(u32));
	curr_ptr += माप(attr->type) + माप(templen) + templen;
	len += templen;
	count++;
	attr->len = cpu_to_be16(templen + माप(attr->type) +
			     माप(templen));

	/*
	 * Model
	 */
	attr = (काष्ठा fdmi_attr_s *) curr_ptr;
	attr->type = cpu_to_be16(FDMI_HBA_ATTRIB_MODEL);
	templen = (u16) म_माप(fcs_hba_attr->model);
	स_नकल(attr->value, fcs_hba_attr->model, templen);
	templen = fc_roundup(templen, माप(u32));
	curr_ptr += माप(attr->type) + माप(templen) + templen;
	len += templen;
	count++;
	attr->len = cpu_to_be16(templen + माप(attr->type) +
			     माप(templen));

	/*
	 * Model Desc
	 */
	attr = (काष्ठा fdmi_attr_s *) curr_ptr;
	attr->type = cpu_to_be16(FDMI_HBA_ATTRIB_MODEL_DESC);
	templen = (u16) म_माप(fcs_hba_attr->model_desc);
	स_नकल(attr->value, fcs_hba_attr->model_desc, templen);
	templen = fc_roundup(templen, माप(u32));
	curr_ptr += माप(attr->type) + माप(templen) + templen;
	len += templen;
	count++;
	attr->len = cpu_to_be16(templen + माप(attr->type) +
			     माप(templen));

	/*
	 * H/W Version
	 */
	अगर (fcs_hba_attr->hw_version[0] != '\0') अणु
		attr = (काष्ठा fdmi_attr_s *) curr_ptr;
		attr->type = cpu_to_be16(FDMI_HBA_ATTRIB_HW_VERSION);
		templen = (u16) म_माप(fcs_hba_attr->hw_version);
		स_नकल(attr->value, fcs_hba_attr->hw_version, templen);
		templen = fc_roundup(templen, माप(u32));
		curr_ptr += माप(attr->type) + माप(templen) + templen;
		len += templen;
		count++;
		attr->len = cpu_to_be16(templen + माप(attr->type) +
					 माप(templen));
	पूर्ण

	/*
	 * Driver Version
	 */
	attr = (काष्ठा fdmi_attr_s *) curr_ptr;
	attr->type = cpu_to_be16(FDMI_HBA_ATTRIB_DRIVER_VERSION);
	templen = (u16) म_माप(fcs_hba_attr->driver_version);
	स_नकल(attr->value, fcs_hba_attr->driver_version, templen);
	templen = fc_roundup(templen, माप(u32));
	curr_ptr += माप(attr->type) + माप(templen) + templen;
	len += templen;
	count++;
	attr->len = cpu_to_be16(templen + माप(attr->type) +
			     माप(templen));

	/*
	 * Option Rom Version
	 */
	अगर (fcs_hba_attr->option_rom_ver[0] != '\0') अणु
		attr = (काष्ठा fdmi_attr_s *) curr_ptr;
		attr->type = cpu_to_be16(FDMI_HBA_ATTRIB_ROM_VERSION);
		templen = (u16) म_माप(fcs_hba_attr->option_rom_ver);
		स_नकल(attr->value, fcs_hba_attr->option_rom_ver, templen);
		templen = fc_roundup(templen, माप(u32));
		curr_ptr += माप(attr->type) + माप(templen) + templen;
		len += templen;
		count++;
		attr->len = cpu_to_be16(templen + माप(attr->type) +
					 माप(templen));
	पूर्ण

	attr = (काष्ठा fdmi_attr_s *) curr_ptr;
	attr->type = cpu_to_be16(FDMI_HBA_ATTRIB_FW_VERSION);
	templen = (u16) म_माप(fcs_hba_attr->fw_version);
	स_नकल(attr->value, fcs_hba_attr->fw_version, templen);
	templen = fc_roundup(templen, माप(u32));
	curr_ptr += माप(attr->type) + माप(templen) + templen;
	len += templen;
	count++;
	attr->len = cpu_to_be16(templen + माप(attr->type) +
			     माप(templen));

	/*
	 * OS Name
	 */
	अगर (fcs_hba_attr->os_name[0] != '\0') अणु
		attr = (काष्ठा fdmi_attr_s *) curr_ptr;
		attr->type = cpu_to_be16(FDMI_HBA_ATTRIB_OS_NAME);
		templen = (u16) म_माप(fcs_hba_attr->os_name);
		स_नकल(attr->value, fcs_hba_attr->os_name, templen);
		templen = fc_roundup(templen, माप(u32));
		curr_ptr += माप(attr->type) + माप(templen) + templen;
		len += templen;
		count++;
		attr->len = cpu_to_be16(templen + माप(attr->type) +
					माप(templen));
	पूर्ण

	/*
	 * MAX_CT_PAYLOAD
	 */
	attr = (काष्ठा fdmi_attr_s *) curr_ptr;
	attr->type = cpu_to_be16(FDMI_HBA_ATTRIB_MAX_CT);
	templen = माप(fcs_hba_attr->max_ct_pyld);
	स_नकल(attr->value, &fcs_hba_attr->max_ct_pyld, templen);
	templen = fc_roundup(templen, माप(u32));
	curr_ptr += माप(attr->type) + माप(templen) + templen;
	len += templen;
	count++;
	attr->len = cpu_to_be16(templen + माप(attr->type) +
			     माप(templen));
	/*
	 * Send extended attributes ( FOS 7.1 support )
	 */
	अगर (fdmi->retry_cnt == 0) अणु
		attr = (काष्ठा fdmi_attr_s *) curr_ptr;
		attr->type = cpu_to_be16(FDMI_HBA_ATTRIB_NODE_SYM_NAME);
		templen = माप(fcs_hba_attr->node_sym_name);
		स_नकल(attr->value, &fcs_hba_attr->node_sym_name, templen);
		templen = fc_roundup(templen, माप(u32));
		curr_ptr += माप(attr->type) + माप(templen) + templen;
		len += templen;
		count++;
		attr->len = cpu_to_be16(templen + माप(attr->type) +
					माप(templen));

		attr = (काष्ठा fdmi_attr_s *) curr_ptr;
		attr->type = cpu_to_be16(FDMI_HBA_ATTRIB_VENDOR_ID);
		templen = माप(fcs_hba_attr->venकरोr_info);
		स_नकल(attr->value, &fcs_hba_attr->venकरोr_info, templen);
		templen = fc_roundup(templen, माप(u32));
		curr_ptr += माप(attr->type) + माप(templen) + templen;
		len += templen;
		count++;
		attr->len = cpu_to_be16(templen + माप(attr->type) +
					माप(templen));

		attr = (काष्ठा fdmi_attr_s *) curr_ptr;
		attr->type = cpu_to_be16(FDMI_HBA_ATTRIB_NUM_PORTS);
		templen = माप(fcs_hba_attr->num_ports);
		स_नकल(attr->value, &fcs_hba_attr->num_ports, templen);
		templen = fc_roundup(templen, माप(u32));
		curr_ptr += माप(attr->type) + माप(templen) + templen;
		len += templen;
		count++;
		attr->len = cpu_to_be16(templen + माप(attr->type) +
					माप(templen));

		attr = (काष्ठा fdmi_attr_s *) curr_ptr;
		attr->type = cpu_to_be16(FDMI_HBA_ATTRIB_FABRIC_NAME);
		templen = माप(fcs_hba_attr->fabric_name);
		स_नकल(attr->value, &fcs_hba_attr->fabric_name, templen);
		templen = fc_roundup(templen, माप(u32));
		curr_ptr += माप(attr->type) + माप(templen) + templen;
		len += templen;
		count++;
		attr->len = cpu_to_be16(templen + माप(attr->type) +
					माप(templen));

		attr = (काष्ठा fdmi_attr_s *) curr_ptr;
		attr->type = cpu_to_be16(FDMI_HBA_ATTRIB_BIOS_VER);
		templen = माप(fcs_hba_attr->bios_ver);
		स_नकल(attr->value, &fcs_hba_attr->bios_ver, templen);
		templen = fc_roundup(attr->len, माप(u32));
		curr_ptr += माप(attr->type) + माप(templen) + templen;
		len += templen;
		count++;
		attr->len = cpu_to_be16(templen + माप(attr->type) +
					माप(templen));
	पूर्ण

	/*
	 * Update size of payload
	 */
	len += ((माप(attr->type) + माप(attr->len)) * count);

	rhba->hba_attr_blk.attr_count = cpu_to_be32(count);

	kमुक्त(fcs_hba_attr);

	वापस len;
पूर्ण

अटल व्योम
bfa_fcs_lport_fdmi_rhba_response(व्योम *fcsarg, काष्ठा bfa_fcxp_s *fcxp,
				व्योम *cbarg, bfa_status_t req_status,
				u32 rsp_len, u32 resid_len,
				काष्ठा fchs_s *rsp_fchs)
अणु
	काष्ठा bfa_fcs_lport_fdmi_s *fdmi =
				(काष्ठा bfa_fcs_lport_fdmi_s *) cbarg;
	काष्ठा bfa_fcs_lport_s *port = fdmi->ms->port;
	काष्ठा ct_hdr_s *cthdr = शून्य;

	bfa_trc(port->fcs, port->port_cfg.pwwn);

	/*
	 * Sanity Checks
	 */
	अगर (req_status != BFA_STATUS_OK) अणु
		bfa_trc(port->fcs, req_status);
		bfa_sm_send_event(fdmi, FDMISM_EVENT_RSP_ERROR);
		वापस;
	पूर्ण

	cthdr = (काष्ठा ct_hdr_s *) BFA_FCXP_RSP_PLD(fcxp);
	cthdr->cmd_rsp_code = be16_to_cpu(cthdr->cmd_rsp_code);

	अगर (cthdr->cmd_rsp_code == CT_RSP_ACCEPT) अणु
		bfa_sm_send_event(fdmi, FDMISM_EVENT_RSP_OK);
		वापस;
	पूर्ण

	bfa_trc(port->fcs, cthdr->reason_code);
	bfa_trc(port->fcs, cthdr->exp_code);
	bfa_sm_send_event(fdmi, FDMISM_EVENT_RSP_ERROR);
पूर्ण

/*
*  RPRT : Register Port
 */
अटल व्योम
bfa_fcs_lport_fdmi_send_rprt(व्योम *fdmi_cbarg, काष्ठा bfa_fcxp_s *fcxp_alloced)
अणु
	काष्ठा bfa_fcs_lport_fdmi_s *fdmi = fdmi_cbarg;
	काष्ठा bfa_fcs_lport_s *port = fdmi->ms->port;
	काष्ठा fchs_s fchs;
	u16        len, attr_len;
	काष्ठा bfa_fcxp_s *fcxp;
	u8        *pyld;

	bfa_trc(port->fcs, port->port_cfg.pwwn);

	fcxp = fcxp_alloced ? fcxp_alloced :
	       bfa_fcs_fcxp_alloc(port->fcs, BFA_TRUE);
	अगर (!fcxp) अणु
		bfa_fcs_fcxp_alloc_रुको(port->fcs->bfa, &fdmi->fcxp_wqe,
				bfa_fcs_lport_fdmi_send_rprt, fdmi, BFA_TRUE);
		वापस;
	पूर्ण
	fdmi->fcxp = fcxp;

	pyld = bfa_fcxp_get_reqbuf(fcxp);
	स_रखो(pyld, 0, FC_MAX_PDUSZ);

	len = fc_fdmi_reqhdr_build(&fchs, pyld, bfa_fcs_lport_get_fcid(port),
				   FDMI_RPRT);

	attr_len =
		bfa_fcs_lport_fdmi_build_rprt_pyld(fdmi,
					  (u8 *) ((काष्ठा ct_hdr_s *) pyld
						       + 1));

	bfa_fcxp_send(fcxp, शून्य, port->fabric->vf_id, port->lp_tag, BFA_FALSE,
			  FC_CLASS_3, len + attr_len, &fchs,
			  bfa_fcs_lport_fdmi_rprt_response, (व्योम *)fdmi,
			  FC_MAX_PDUSZ, FC_FCCT_TOV);

	bfa_sm_send_event(fdmi, FDMISM_EVENT_RPRT_SENT);
पूर्ण

/*
 * This routine builds Port Attribute Block that used in RPA, RPRT commands.
 */
अटल          u16
bfa_fcs_lport_fdmi_build_portattr_block(काष्ठा bfa_fcs_lport_fdmi_s *fdmi,
				       u8 *pyld)
अणु
	काष्ठा bfa_fcs_fdmi_port_attr_s fcs_port_attr;
	काष्ठा fdmi_port_attr_s *port_attrib = (काष्ठा fdmi_port_attr_s *) pyld;
	काष्ठा fdmi_attr_s *attr;
	u8        *curr_ptr;
	u16        len;
	u8	count = 0;
	u16	templen;

	/*
	 * get port attributes
	 */
	bfa_fcs_fdmi_get_portattr(fdmi, &fcs_port_attr);

	len = माप(port_attrib->attr_count);

	/*
	 * fill out the invididual entries
	 */
	curr_ptr = (u8 *) &port_attrib->port_attr;

	/*
	 * FC4 Types
	 */
	attr = (काष्ठा fdmi_attr_s *) curr_ptr;
	attr->type = cpu_to_be16(FDMI_PORT_ATTRIB_FC4_TYPES);
	templen = माप(fcs_port_attr.supp_fc4_types);
	स_नकल(attr->value, fcs_port_attr.supp_fc4_types, templen);
	curr_ptr += माप(attr->type) + माप(templen) + templen;
	len += templen;
	++count;
	attr->len =
		cpu_to_be16(templen + माप(attr->type) +
			     माप(templen));

	/*
	 * Supported Speed
	 */
	attr = (काष्ठा fdmi_attr_s *) curr_ptr;
	attr->type = cpu_to_be16(FDMI_PORT_ATTRIB_SUPP_SPEED);
	templen = माप(fcs_port_attr.supp_speed);
	स_नकल(attr->value, &fcs_port_attr.supp_speed, templen);
	curr_ptr += माप(attr->type) + माप(templen) + templen;
	len += templen;
	++count;
	attr->len =
		cpu_to_be16(templen + माप(attr->type) +
			     माप(templen));

	/*
	 * current Port Speed
	 */
	attr = (काष्ठा fdmi_attr_s *) curr_ptr;
	attr->type = cpu_to_be16(FDMI_PORT_ATTRIB_PORT_SPEED);
	templen = माप(fcs_port_attr.curr_speed);
	स_नकल(attr->value, &fcs_port_attr.curr_speed, templen);
	curr_ptr += माप(attr->type) + माप(templen) + templen;
	len += templen;
	++count;
	attr->len = cpu_to_be16(templen + माप(attr->type) +
			     माप(templen));

	/*
	 * max frame size
	 */
	attr = (काष्ठा fdmi_attr_s *) curr_ptr;
	attr->type = cpu_to_be16(FDMI_PORT_ATTRIB_FRAME_SIZE);
	templen = माप(fcs_port_attr.max_frm_size);
	स_नकल(attr->value, &fcs_port_attr.max_frm_size, templen);
	curr_ptr += माप(attr->type) + माप(templen) + templen;
	len += templen;
	++count;
	attr->len = cpu_to_be16(templen + माप(attr->type) +
			     माप(templen));

	/*
	 * OS Device Name
	 */
	अगर (fcs_port_attr.os_device_name[0] != '\0') अणु
		attr = (काष्ठा fdmi_attr_s *) curr_ptr;
		attr->type = cpu_to_be16(FDMI_PORT_ATTRIB_DEV_NAME);
		templen = (u16) म_माप(fcs_port_attr.os_device_name);
		स_नकल(attr->value, fcs_port_attr.os_device_name, templen);
		templen = fc_roundup(templen, माप(u32));
		curr_ptr += माप(attr->type) + माप(templen) + templen;
		len += templen;
		++count;
		attr->len = cpu_to_be16(templen + माप(attr->type) +
					माप(templen));
	पूर्ण
	/*
	 * Host Name
	 */
	अगर (fcs_port_attr.host_name[0] != '\0') अणु
		attr = (काष्ठा fdmi_attr_s *) curr_ptr;
		attr->type = cpu_to_be16(FDMI_PORT_ATTRIB_HOST_NAME);
		templen = (u16) म_माप(fcs_port_attr.host_name);
		स_नकल(attr->value, fcs_port_attr.host_name, templen);
		templen = fc_roundup(templen, माप(u32));
		curr_ptr += माप(attr->type) + माप(templen) + templen;
		len += templen;
		++count;
		attr->len = cpu_to_be16(templen + माप(attr->type) +
				माप(templen));
	पूर्ण

	अगर (fdmi->retry_cnt == 0) अणु
		attr = (काष्ठा fdmi_attr_s *) curr_ptr;
		attr->type = cpu_to_be16(FDMI_PORT_ATTRIB_NODE_NAME);
		templen = माप(fcs_port_attr.node_name);
		स_नकल(attr->value, &fcs_port_attr.node_name, templen);
		templen = fc_roundup(templen, माप(u32));
		curr_ptr += माप(attr->type) + माप(templen) + templen;
		len += templen;
		++count;
		attr->len = cpu_to_be16(templen + माप(attr->type) +
				 माप(templen));

		attr = (काष्ठा fdmi_attr_s *) curr_ptr;
		attr->type = cpu_to_be16(FDMI_PORT_ATTRIB_PORT_NAME);
		templen = माप(fcs_port_attr.port_name);
		स_नकल(attr->value, &fcs_port_attr.port_name, templen);
		templen = fc_roundup(templen, माप(u32));
		curr_ptr += माप(attr->type) + माप(attr->len) + templen;
		len += templen;
		++count;
		attr->len = cpu_to_be16(templen + माप(attr->type) +
				 माप(templen));

		अगर (fcs_port_attr.port_sym_name.symname[0] != '\0') अणु
			attr = (काष्ठा fdmi_attr_s *) curr_ptr;
			attr->type =
				cpu_to_be16(FDMI_PORT_ATTRIB_PORT_SYM_NAME);
			templen = माप(fcs_port_attr.port_sym_name);
			स_नकल(attr->value,
				&fcs_port_attr.port_sym_name, templen);
			templen = fc_roundup(templen, माप(u32));
			curr_ptr += माप(attr->type) +
					माप(templen) + templen;
			len += templen;
			++count;
			attr->len = cpu_to_be16(templen +
				माप(attr->type) + माप(templen));
		पूर्ण

		attr = (काष्ठा fdmi_attr_s *) curr_ptr;
		attr->type = cpu_to_be16(FDMI_PORT_ATTRIB_PORT_TYPE);
		templen = माप(fcs_port_attr.port_type);
		स_नकल(attr->value, &fcs_port_attr.port_type, templen);
		templen = fc_roundup(templen, माप(u32));
		curr_ptr += माप(attr->type) + माप(templen) + templen;
		len += templen;
		++count;
		attr->len = cpu_to_be16(templen + माप(attr->type) +
				 माप(templen));

		attr = (काष्ठा fdmi_attr_s *) curr_ptr;
		attr->type = cpu_to_be16(FDMI_PORT_ATTRIB_SUPP_COS);
		templen = माप(fcs_port_attr.scos);
		स_नकल(attr->value, &fcs_port_attr.scos, templen);
		templen = fc_roundup(templen, माप(u32));
		curr_ptr += माप(attr->type) + माप(templen) + templen;
		len += templen;
		++count;
		attr->len = cpu_to_be16(templen + माप(attr->type) +
				 माप(templen));

		attr = (काष्ठा fdmi_attr_s *) curr_ptr;
		attr->type = cpu_to_be16(FDMI_PORT_ATTRIB_PORT_FAB_NAME);
		templen = माप(fcs_port_attr.port_fabric_name);
		स_नकल(attr->value, &fcs_port_attr.port_fabric_name, templen);
		templen = fc_roundup(templen, माप(u32));
		curr_ptr += माप(attr->type) + माप(templen) + templen;
		len += templen;
		++count;
		attr->len = cpu_to_be16(templen + माप(attr->type) +
				 माप(templen));

		attr = (काष्ठा fdmi_attr_s *) curr_ptr;
		attr->type = cpu_to_be16(FDMI_PORT_ATTRIB_PORT_FC4_TYPE);
		templen = माप(fcs_port_attr.port_act_fc4_type);
		स_नकल(attr->value, fcs_port_attr.port_act_fc4_type,
				templen);
		templen = fc_roundup(templen, माप(u32));
		curr_ptr += माप(attr->type) + माप(templen) + templen;
		len += templen;
		++count;
		attr->len = cpu_to_be16(templen + माप(attr->type) +
				 माप(templen));

		attr = (काष्ठा fdmi_attr_s *) curr_ptr;
		attr->type = cpu_to_be16(FDMI_PORT_ATTRIB_PORT_STATE);
		templen = माप(fcs_port_attr.port_state);
		स_नकल(attr->value, &fcs_port_attr.port_state, templen);
		templen = fc_roundup(templen, माप(u32));
		curr_ptr += माप(attr->type) + माप(templen) + templen;
		len += templen;
		++count;
		attr->len = cpu_to_be16(templen + माप(attr->type) +
				 माप(templen));

		attr = (काष्ठा fdmi_attr_s *) curr_ptr;
		attr->type = cpu_to_be16(FDMI_PORT_ATTRIB_PORT_NUM_RPRT);
		templen = माप(fcs_port_attr.num_ports);
		स_नकल(attr->value, &fcs_port_attr.num_ports, templen);
		templen = fc_roundup(templen, माप(u32));
		curr_ptr += माप(attr->type) + माप(templen) + templen;
		len += templen;
		++count;
		attr->len = cpu_to_be16(templen + माप(attr->type) +
				माप(templen));
	पूर्ण

	/*
	 * Update size of payload
	 */
	port_attrib->attr_count = cpu_to_be32(count);
	len += ((माप(attr->type) + माप(attr->len)) * count);
	वापस len;
पूर्ण

अटल          u16
bfa_fcs_lport_fdmi_build_rprt_pyld(काष्ठा bfa_fcs_lport_fdmi_s *fdmi, u8 *pyld)
अणु
	काष्ठा bfa_fcs_lport_s *port = fdmi->ms->port;
	काष्ठा fdmi_rprt_s *rprt = (काष्ठा fdmi_rprt_s *) pyld;
	u16        len;

	rprt->hba_id = bfa_fcs_lport_get_pwwn(bfa_fcs_get_base_port(port->fcs));
	rprt->port_name = bfa_fcs_lport_get_pwwn(port);

	len = bfa_fcs_lport_fdmi_build_portattr_block(fdmi,
				(u8 *) &rprt->port_attr_blk);

	len += माप(rprt->hba_id) + माप(rprt->port_name);

	वापस len;
पूर्ण

अटल व्योम
bfa_fcs_lport_fdmi_rprt_response(व्योम *fcsarg, काष्ठा bfa_fcxp_s *fcxp,
				व्योम *cbarg, bfa_status_t req_status,
				u32 rsp_len, u32 resid_len,
				काष्ठा fchs_s *rsp_fchs)
अणु
	काष्ठा bfa_fcs_lport_fdmi_s *fdmi =
			(काष्ठा bfa_fcs_lport_fdmi_s *) cbarg;
	काष्ठा bfa_fcs_lport_s *port = fdmi->ms->port;
	काष्ठा ct_hdr_s *cthdr = शून्य;

	bfa_trc(port->fcs, port->port_cfg.pwwn);

	/*
	 * Sanity Checks
	 */
	अगर (req_status != BFA_STATUS_OK) अणु
		bfa_trc(port->fcs, req_status);
		bfa_sm_send_event(fdmi, FDMISM_EVENT_RSP_ERROR);
		वापस;
	पूर्ण

	cthdr = (काष्ठा ct_hdr_s *) BFA_FCXP_RSP_PLD(fcxp);
	cthdr->cmd_rsp_code = be16_to_cpu(cthdr->cmd_rsp_code);

	अगर (cthdr->cmd_rsp_code == CT_RSP_ACCEPT) अणु
		bfa_sm_send_event(fdmi, FDMISM_EVENT_RSP_OK);
		वापस;
	पूर्ण

	bfa_trc(port->fcs, cthdr->reason_code);
	bfa_trc(port->fcs, cthdr->exp_code);
	bfa_sm_send_event(fdmi, FDMISM_EVENT_RSP_ERROR);
पूर्ण

/*
*  RPA : Register Port Attributes.
 */
अटल व्योम
bfa_fcs_lport_fdmi_send_rpa(व्योम *fdmi_cbarg, काष्ठा bfa_fcxp_s *fcxp_alloced)
अणु
	काष्ठा bfa_fcs_lport_fdmi_s *fdmi = fdmi_cbarg;
	काष्ठा bfa_fcs_lport_s *port = fdmi->ms->port;
	काष्ठा fchs_s fchs;
	u16        len, attr_len;
	काष्ठा bfa_fcxp_s *fcxp;
	u8        *pyld;

	bfa_trc(port->fcs, port->port_cfg.pwwn);

	fcxp = fcxp_alloced ? fcxp_alloced :
	       bfa_fcs_fcxp_alloc(port->fcs, BFA_TRUE);
	अगर (!fcxp) अणु
		bfa_fcs_fcxp_alloc_रुको(port->fcs->bfa, &fdmi->fcxp_wqe,
				bfa_fcs_lport_fdmi_send_rpa, fdmi, BFA_TRUE);
		वापस;
	पूर्ण
	fdmi->fcxp = fcxp;

	pyld = bfa_fcxp_get_reqbuf(fcxp);
	स_रखो(pyld, 0, FC_MAX_PDUSZ);

	len = fc_fdmi_reqhdr_build(&fchs, pyld, bfa_fcs_lport_get_fcid(port),
				   FDMI_RPA);

	attr_len = bfa_fcs_lport_fdmi_build_rpa_pyld(fdmi,
				(u8 *) ((काष्ठा ct_hdr_s *) pyld + 1));

	bfa_fcxp_send(fcxp, शून्य, port->fabric->vf_id, port->lp_tag, BFA_FALSE,
			  FC_CLASS_3, len + attr_len, &fchs,
			  bfa_fcs_lport_fdmi_rpa_response, (व्योम *)fdmi,
			  FC_MAX_PDUSZ, FC_FCCT_TOV);

	bfa_sm_send_event(fdmi, FDMISM_EVENT_RPA_SENT);
पूर्ण

अटल          u16
bfa_fcs_lport_fdmi_build_rpa_pyld(काष्ठा bfa_fcs_lport_fdmi_s *fdmi, u8 *pyld)
अणु
	काष्ठा bfa_fcs_lport_s *port = fdmi->ms->port;
	काष्ठा fdmi_rpa_s *rpa = (काष्ठा fdmi_rpa_s *) pyld;
	u16        len;

	rpa->port_name = bfa_fcs_lport_get_pwwn(port);

	len = bfa_fcs_lport_fdmi_build_portattr_block(fdmi,
				(u8 *) &rpa->port_attr_blk);

	len += माप(rpa->port_name);

	वापस len;
पूर्ण

अटल व्योम
bfa_fcs_lport_fdmi_rpa_response(व्योम *fcsarg, काष्ठा bfa_fcxp_s *fcxp,
			व्योम *cbarg, bfa_status_t req_status, u32 rsp_len,
			u32 resid_len, काष्ठा fchs_s *rsp_fchs)
अणु
	काष्ठा bfa_fcs_lport_fdmi_s *fdmi =
				(काष्ठा bfa_fcs_lport_fdmi_s *) cbarg;
	काष्ठा bfa_fcs_lport_s *port = fdmi->ms->port;
	काष्ठा ct_hdr_s *cthdr = शून्य;

	bfa_trc(port->fcs, port->port_cfg.pwwn);

	/*
	 * Sanity Checks
	 */
	अगर (req_status != BFA_STATUS_OK) अणु
		bfa_trc(port->fcs, req_status);
		bfa_sm_send_event(fdmi, FDMISM_EVENT_RSP_ERROR);
		वापस;
	पूर्ण

	cthdr = (काष्ठा ct_hdr_s *) BFA_FCXP_RSP_PLD(fcxp);
	cthdr->cmd_rsp_code = be16_to_cpu(cthdr->cmd_rsp_code);

	अगर (cthdr->cmd_rsp_code == CT_RSP_ACCEPT) अणु
		bfa_sm_send_event(fdmi, FDMISM_EVENT_RSP_OK);
		वापस;
	पूर्ण

	bfa_trc(port->fcs, cthdr->reason_code);
	bfa_trc(port->fcs, cthdr->exp_code);
	bfa_sm_send_event(fdmi, FDMISM_EVENT_RSP_ERROR);
पूर्ण

अटल व्योम
bfa_fcs_lport_fdmi_समयout(व्योम *arg)
अणु
	काष्ठा bfa_fcs_lport_fdmi_s *fdmi = (काष्ठा bfa_fcs_lport_fdmi_s *) arg;

	bfa_sm_send_event(fdmi, FDMISM_EVENT_TIMEOUT);
पूर्ण

अटल व्योम
bfa_fcs_fdmi_get_hbaattr(काष्ठा bfa_fcs_lport_fdmi_s *fdmi,
			 काष्ठा bfa_fcs_fdmi_hba_attr_s *hba_attr)
अणु
	काष्ठा bfa_fcs_lport_s *port = fdmi->ms->port;
	काष्ठा bfa_fcs_driver_info_s  *driver_info = &port->fcs->driver_info;
	काष्ठा bfa_fcs_fdmi_port_attr_s fcs_port_attr;

	स_रखो(hba_attr, 0, माप(काष्ठा bfa_fcs_fdmi_hba_attr_s));

	bfa_ioc_get_adapter_manufacturer(&port->fcs->bfa->ioc,
					hba_attr->manufacturer);
	bfa_ioc_get_adapter_serial_num(&port->fcs->bfa->ioc,
					hba_attr->serial_num);
	bfa_ioc_get_adapter_model(&port->fcs->bfa->ioc,
					hba_attr->model);
	bfa_ioc_get_adapter_model(&port->fcs->bfa->ioc,
					hba_attr->model_desc);
	bfa_ioc_get_pci_chip_rev(&port->fcs->bfa->ioc,
					hba_attr->hw_version);
	bfa_ioc_get_adapter_optrom_ver(&port->fcs->bfa->ioc,
					hba_attr->option_rom_ver);
	bfa_ioc_get_adapter_fw_ver(&port->fcs->bfa->ioc,
					hba_attr->fw_version);

	strlcpy(hba_attr->driver_version, (अक्षर *)driver_info->version,
		माप(hba_attr->driver_version));

	strlcpy(hba_attr->os_name, driver_info->host_os_name,
		माप(hba_attr->os_name));

	/*
	 * If there is a patch level, append it
	 * to the os name aदीर्घ with a separator
	 */
	अगर (driver_info->host_os_patch[0] != '\0') अणु
		strlcat(hba_attr->os_name, BFA_FCS_PORT_SYMBNAME_SEPARATOR,
			माप(hba_attr->os_name));
		strlcat(hba_attr->os_name, driver_info->host_os_patch,
				माप(hba_attr->os_name));
	पूर्ण

	/* Retrieve the max frame size from the port attr */
	bfa_fcs_fdmi_get_portattr(fdmi, &fcs_port_attr);
	hba_attr->max_ct_pyld = fcs_port_attr.max_frm_size;

	strlcpy(hba_attr->node_sym_name.symname,
		port->port_cfg.node_sym_name.symname, BFA_SYMNAME_MAXLEN);
	म_नकल(hba_attr->venकरोr_info, "QLogic");
	hba_attr->num_ports =
		cpu_to_be32(bfa_ioc_get_nports(&port->fcs->bfa->ioc));
	hba_attr->fabric_name = port->fabric->lps->pr_nwwn;
	strlcpy(hba_attr->bios_ver, hba_attr->option_rom_ver, BFA_VERSION_LEN);

पूर्ण

अटल व्योम
bfa_fcs_fdmi_get_portattr(काष्ठा bfa_fcs_lport_fdmi_s *fdmi,
			  काष्ठा bfa_fcs_fdmi_port_attr_s *port_attr)
अणु
	काष्ठा bfa_fcs_lport_s *port = fdmi->ms->port;
	काष्ठा bfa_fcs_driver_info_s  *driver_info = &port->fcs->driver_info;
	काष्ठा bfa_port_attr_s pport_attr;
	काष्ठा bfa_lport_attr_s lport_attr;

	स_रखो(port_attr, 0, माप(काष्ठा bfa_fcs_fdmi_port_attr_s));

	/*
	 * get pport attributes from hal
	 */
	bfa_fcport_get_attr(port->fcs->bfa, &pport_attr);

	/*
	 * get FC4 type Biपंचांगask
	 */
	fc_get_fc4type_biपंचांगask(FC_TYPE_FCP, port_attr->supp_fc4_types);

	/*
	 * Supported Speeds
	 */
	चयन (pport_attr.speed_supported) अणु
	हाल BFA_PORT_SPEED_16GBPS:
		port_attr->supp_speed =
			cpu_to_be32(BFA_FCS_FDMI_SUPP_SPEEDS_16G);
		अवरोध;

	हाल BFA_PORT_SPEED_10GBPS:
		port_attr->supp_speed =
			cpu_to_be32(BFA_FCS_FDMI_SUPP_SPEEDS_10G);
		अवरोध;

	हाल BFA_PORT_SPEED_8GBPS:
		port_attr->supp_speed =
			cpu_to_be32(BFA_FCS_FDMI_SUPP_SPEEDS_8G);
		अवरोध;

	हाल BFA_PORT_SPEED_4GBPS:
		port_attr->supp_speed =
			cpu_to_be32(BFA_FCS_FDMI_SUPP_SPEEDS_4G);
		अवरोध;

	शेष:
		bfa_sm_fault(port->fcs, pport_attr.speed_supported);
	पूर्ण

	/*
	 * Current Speed
	 */
	port_attr->curr_speed = cpu_to_be32(
				bfa_fcs_fdmi_convert_speed(pport_attr.speed));

	/*
	 * Max PDU Size.
	 */
	port_attr->max_frm_size = cpu_to_be32(pport_attr.pport_cfg.maxfrsize);

	/*
	 * OS device Name
	 */
	strlcpy(port_attr->os_device_name, driver_info->os_device_name,
		माप(port_attr->os_device_name));

	/*
	 * Host name
	 */
	strlcpy(port_attr->host_name, driver_info->host_machine_name,
		माप(port_attr->host_name));

	port_attr->node_name = bfa_fcs_lport_get_nwwn(port);
	port_attr->port_name = bfa_fcs_lport_get_pwwn(port);

	strlcpy(port_attr->port_sym_name.symname,
		bfa_fcs_lport_get_psym_name(port).symname, BFA_SYMNAME_MAXLEN);
	bfa_fcs_lport_get_attr(port, &lport_attr);
	port_attr->port_type = cpu_to_be32(lport_attr.port_type);
	port_attr->scos = pport_attr.cos_supported;
	port_attr->port_fabric_name = port->fabric->lps->pr_nwwn;
	fc_get_fc4type_biपंचांगask(FC_TYPE_FCP, port_attr->port_act_fc4_type);
	port_attr->port_state = cpu_to_be32(pport_attr.port_state);
	port_attr->num_ports = cpu_to_be32(port->num_rports);
पूर्ण

/*
 * Convert BFA speed to FDMI क्रमmat.
 */
u32
bfa_fcs_fdmi_convert_speed(bfa_port_speed_t pport_speed)
अणु
	u32	ret;

	चयन (pport_speed) अणु
	हाल BFA_PORT_SPEED_1GBPS:
	हाल BFA_PORT_SPEED_2GBPS:
		ret = pport_speed;
		अवरोध;

	हाल BFA_PORT_SPEED_4GBPS:
		ret = FDMI_TRANS_SPEED_4G;
		अवरोध;

	हाल BFA_PORT_SPEED_8GBPS:
		ret = FDMI_TRANS_SPEED_8G;
		अवरोध;

	हाल BFA_PORT_SPEED_10GBPS:
		ret = FDMI_TRANS_SPEED_10G;
		अवरोध;

	हाल BFA_PORT_SPEED_16GBPS:
		ret = FDMI_TRANS_SPEED_16G;
		अवरोध;

	शेष:
		ret = FDMI_TRANS_SPEED_UNKNOWN;
	पूर्ण
	वापस ret;
पूर्ण

व्योम
bfa_fcs_lport_fdmi_init(काष्ठा bfa_fcs_lport_ms_s *ms)
अणु
	काष्ठा bfa_fcs_lport_fdmi_s *fdmi = &ms->fdmi;

	fdmi->ms = ms;
	अगर (ms->port->fcs->fdmi_enabled)
		bfa_sm_set_state(fdmi, bfa_fcs_lport_fdmi_sm_offline);
	अन्यथा
		bfa_sm_set_state(fdmi, bfa_fcs_lport_fdmi_sm_disabled);
पूर्ण

व्योम
bfa_fcs_lport_fdmi_offline(काष्ठा bfa_fcs_lport_ms_s *ms)
अणु
	काष्ठा bfa_fcs_lport_fdmi_s *fdmi = &ms->fdmi;

	fdmi->ms = ms;
	bfa_sm_send_event(fdmi, FDMISM_EVENT_PORT_OFFLINE);
पूर्ण

व्योम
bfa_fcs_lport_fdmi_online(काष्ठा bfa_fcs_lport_ms_s *ms)
अणु
	काष्ठा bfa_fcs_lport_fdmi_s *fdmi = &ms->fdmi;

	fdmi->ms = ms;
	bfa_sm_send_event(fdmi, FDMISM_EVENT_PORT_ONLINE);
पूर्ण

#घोषणा BFA_FCS_MS_CMD_MAX_RETRIES  2

/*
 * क्रमward declarations
 */
अटल व्योम     bfa_fcs_lport_ms_send_plogi(व्योम *ms_cbarg,
					   काष्ठा bfa_fcxp_s *fcxp_alloced);
अटल व्योम     bfa_fcs_lport_ms_समयout(व्योम *arg);
अटल व्योम     bfa_fcs_lport_ms_plogi_response(व्योम *fcsarg,
					       काष्ठा bfa_fcxp_s *fcxp,
					       व्योम *cbarg,
					       bfa_status_t req_status,
					       u32 rsp_len,
					       u32 resid_len,
					       काष्ठा fchs_s *rsp_fchs);

अटल व्योम	bfa_fcs_lport_ms_send_gmal(व्योम *ms_cbarg,
					काष्ठा bfa_fcxp_s *fcxp_alloced);
अटल व्योम     bfa_fcs_lport_ms_gmal_response(व्योम *fcsarg,
					       काष्ठा bfa_fcxp_s *fcxp,
					       व्योम *cbarg,
					       bfa_status_t req_status,
					       u32 rsp_len,
					       u32 resid_len,
					       काष्ठा fchs_s *rsp_fchs);
अटल व्योम	bfa_fcs_lport_ms_send_gfn(व्योम *ms_cbarg,
					काष्ठा bfa_fcxp_s *fcxp_alloced);
अटल व्योम     bfa_fcs_lport_ms_gfn_response(व्योम *fcsarg,
					       काष्ठा bfa_fcxp_s *fcxp,
					       व्योम *cbarg,
					       bfa_status_t req_status,
					       u32 rsp_len,
					       u32 resid_len,
					       काष्ठा fchs_s *rsp_fchs);
/*
 *  fcs_ms_sm FCS MS state machine
 */

/*
 *  MS State Machine events
 */
क्रमागत port_ms_event अणु
	MSSM_EVENT_PORT_ONLINE = 1,
	MSSM_EVENT_PORT_OFFLINE = 2,
	MSSM_EVENT_RSP_OK = 3,
	MSSM_EVENT_RSP_ERROR = 4,
	MSSM_EVENT_TIMEOUT = 5,
	MSSM_EVENT_FCXP_SENT = 6,
	MSSM_EVENT_PORT_FABRIC_RSCN = 7
पूर्ण;

अटल व्योम     bfa_fcs_lport_ms_sm_offline(काष्ठा bfa_fcs_lport_ms_s *ms,
					   क्रमागत port_ms_event event);
अटल व्योम     bfa_fcs_lport_ms_sm_plogi_sending(काष्ठा bfa_fcs_lport_ms_s *ms,
						 क्रमागत port_ms_event event);
अटल व्योम     bfa_fcs_lport_ms_sm_plogi(काष्ठा bfa_fcs_lport_ms_s *ms,
					 क्रमागत port_ms_event event);
अटल व्योम     bfa_fcs_lport_ms_sm_plogi_retry(काष्ठा bfa_fcs_lport_ms_s *ms,
					       क्रमागत port_ms_event event);
अटल व्योम     bfa_fcs_lport_ms_sm_gmal_sending(काष्ठा bfa_fcs_lport_ms_s *ms,
						 क्रमागत port_ms_event event);
अटल व्योम     bfa_fcs_lport_ms_sm_gmal(काष्ठा bfa_fcs_lport_ms_s *ms,
					 क्रमागत port_ms_event event);
अटल व्योम     bfa_fcs_lport_ms_sm_gmal_retry(काष्ठा bfa_fcs_lport_ms_s *ms,
					       क्रमागत port_ms_event event);
अटल व्योम     bfa_fcs_lport_ms_sm_gfn_sending(काष्ठा bfa_fcs_lport_ms_s *ms,
						 क्रमागत port_ms_event event);
अटल व्योम     bfa_fcs_lport_ms_sm_gfn(काष्ठा bfa_fcs_lport_ms_s *ms,
					 क्रमागत port_ms_event event);
अटल व्योम     bfa_fcs_lport_ms_sm_gfn_retry(काष्ठा bfa_fcs_lport_ms_s *ms,
					       क्रमागत port_ms_event event);
अटल व्योम     bfa_fcs_lport_ms_sm_online(काष्ठा bfa_fcs_lport_ms_s *ms,
					  क्रमागत port_ms_event event);
/*
 *	Start in offline state - aरुकोing NS to send start.
 */
अटल व्योम
bfa_fcs_lport_ms_sm_offline(काष्ठा bfa_fcs_lport_ms_s *ms,
				क्रमागत port_ms_event event)
अणु
	bfa_trc(ms->port->fcs, ms->port->port_cfg.pwwn);
	bfa_trc(ms->port->fcs, event);

	चयन (event) अणु
	हाल MSSM_EVENT_PORT_ONLINE:
		bfa_sm_set_state(ms, bfa_fcs_lport_ms_sm_plogi_sending);
		bfa_fcs_lport_ms_send_plogi(ms, शून्य);
		अवरोध;

	हाल MSSM_EVENT_PORT_OFFLINE:
		अवरोध;

	शेष:
		bfa_sm_fault(ms->port->fcs, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcs_lport_ms_sm_plogi_sending(काष्ठा bfa_fcs_lport_ms_s *ms,
				क्रमागत port_ms_event event)
अणु
	bfa_trc(ms->port->fcs, ms->port->port_cfg.pwwn);
	bfa_trc(ms->port->fcs, event);

	चयन (event) अणु
	हाल MSSM_EVENT_FCXP_SENT:
		bfa_sm_set_state(ms, bfa_fcs_lport_ms_sm_plogi);
		अवरोध;

	हाल MSSM_EVENT_PORT_OFFLINE:
		bfa_sm_set_state(ms, bfa_fcs_lport_ms_sm_offline);
		bfa_fcxp_walloc_cancel(BFA_FCS_GET_HAL_FROM_PORT(ms->port),
					   &ms->fcxp_wqe);
		अवरोध;

	शेष:
		bfa_sm_fault(ms->port->fcs, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcs_lport_ms_sm_plogi(काष्ठा bfa_fcs_lport_ms_s *ms,
			क्रमागत port_ms_event event)
अणु
	bfa_trc(ms->port->fcs, ms->port->port_cfg.pwwn);
	bfa_trc(ms->port->fcs, event);

	चयन (event) अणु
	हाल MSSM_EVENT_RSP_ERROR:
		/*
		 * Start समयr क्रम a delayed retry
		 */
		bfa_sm_set_state(ms, bfa_fcs_lport_ms_sm_plogi_retry);
		ms->port->stats.ms_retries++;
		bfa_समयr_start(BFA_FCS_GET_HAL_FROM_PORT(ms->port),
				    &ms->समयr, bfa_fcs_lport_ms_समयout, ms,
				    BFA_FCS_RETRY_TIMEOUT);
		अवरोध;

	हाल MSSM_EVENT_RSP_OK:
		/*
		 * since plogi is करोne, now invoke MS related sub-modules
		 */
		bfa_fcs_lport_fdmi_online(ms);

		/*
		 * अगर this is a Vport, go to online state.
		 */
		अगर (ms->port->vport) अणु
			bfa_sm_set_state(ms, bfa_fcs_lport_ms_sm_online);
			अवरोध;
		पूर्ण

		/*
		 * For a base port we need to get the
		 * चयन's IP address.
		 */
		bfa_sm_set_state(ms, bfa_fcs_lport_ms_sm_gmal_sending);
		bfa_fcs_lport_ms_send_gmal(ms, शून्य);
		अवरोध;

	हाल MSSM_EVENT_PORT_OFFLINE:
		bfa_sm_set_state(ms, bfa_fcs_lport_ms_sm_offline);
		bfa_fcxp_discard(ms->fcxp);
		अवरोध;

	शेष:
		bfa_sm_fault(ms->port->fcs, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcs_lport_ms_sm_plogi_retry(काष्ठा bfa_fcs_lport_ms_s *ms,
			क्रमागत port_ms_event event)
अणु
	bfa_trc(ms->port->fcs, ms->port->port_cfg.pwwn);
	bfa_trc(ms->port->fcs, event);

	चयन (event) अणु
	हाल MSSM_EVENT_TIMEOUT:
		/*
		 * Retry Timer Expired. Re-send
		 */
		bfa_sm_set_state(ms, bfa_fcs_lport_ms_sm_plogi_sending);
		bfa_fcs_lport_ms_send_plogi(ms, शून्य);
		अवरोध;

	हाल MSSM_EVENT_PORT_OFFLINE:
		bfa_sm_set_state(ms, bfa_fcs_lport_ms_sm_offline);
		bfa_समयr_stop(&ms->समयr);
		अवरोध;

	शेष:
		bfa_sm_fault(ms->port->fcs, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcs_lport_ms_sm_online(काष्ठा bfa_fcs_lport_ms_s *ms,
			क्रमागत port_ms_event event)
अणु
	bfa_trc(ms->port->fcs, ms->port->port_cfg.pwwn);
	bfa_trc(ms->port->fcs, event);

	चयन (event) अणु
	हाल MSSM_EVENT_PORT_OFFLINE:
		bfa_sm_set_state(ms, bfa_fcs_lport_ms_sm_offline);
		अवरोध;

	हाल MSSM_EVENT_PORT_FABRIC_RSCN:
		bfa_sm_set_state(ms, bfa_fcs_lport_ms_sm_gfn_sending);
		ms->retry_cnt = 0;
		bfa_fcs_lport_ms_send_gfn(ms, शून्य);
		अवरोध;

	शेष:
		bfa_sm_fault(ms->port->fcs, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcs_lport_ms_sm_gmal_sending(काष्ठा bfa_fcs_lport_ms_s *ms,
				क्रमागत port_ms_event event)
अणु
	bfa_trc(ms->port->fcs, ms->port->port_cfg.pwwn);
	bfa_trc(ms->port->fcs, event);

	चयन (event) अणु
	हाल MSSM_EVENT_FCXP_SENT:
		bfa_sm_set_state(ms, bfa_fcs_lport_ms_sm_gmal);
		अवरोध;

	हाल MSSM_EVENT_PORT_OFFLINE:
		bfa_sm_set_state(ms, bfa_fcs_lport_ms_sm_offline);
		bfa_fcxp_walloc_cancel(BFA_FCS_GET_HAL_FROM_PORT(ms->port),
					   &ms->fcxp_wqe);
		अवरोध;

	शेष:
		bfa_sm_fault(ms->port->fcs, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcs_lport_ms_sm_gmal(काष्ठा bfa_fcs_lport_ms_s *ms,
				क्रमागत port_ms_event event)
अणु
	bfa_trc(ms->port->fcs, ms->port->port_cfg.pwwn);
	bfa_trc(ms->port->fcs, event);

	चयन (event) अणु
	हाल MSSM_EVENT_RSP_ERROR:
		/*
		 * Start समयr क्रम a delayed retry
		 */
		अगर (ms->retry_cnt++ < BFA_FCS_MS_CMD_MAX_RETRIES) अणु
			bfa_sm_set_state(ms, bfa_fcs_lport_ms_sm_gmal_retry);
			ms->port->stats.ms_retries++;
			bfa_समयr_start(BFA_FCS_GET_HAL_FROM_PORT(ms->port),
				&ms->समयr, bfa_fcs_lport_ms_समयout, ms,
				BFA_FCS_RETRY_TIMEOUT);
		पूर्ण अन्यथा अणु
			bfa_sm_set_state(ms, bfa_fcs_lport_ms_sm_gfn_sending);
			bfa_fcs_lport_ms_send_gfn(ms, शून्य);
			ms->retry_cnt = 0;
		पूर्ण
		अवरोध;

	हाल MSSM_EVENT_RSP_OK:
		bfa_sm_set_state(ms, bfa_fcs_lport_ms_sm_gfn_sending);
		bfa_fcs_lport_ms_send_gfn(ms, शून्य);
		अवरोध;

	हाल MSSM_EVENT_PORT_OFFLINE:
		bfa_sm_set_state(ms, bfa_fcs_lport_ms_sm_offline);
		bfa_fcxp_discard(ms->fcxp);
		अवरोध;

	शेष:
		bfa_sm_fault(ms->port->fcs, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcs_lport_ms_sm_gmal_retry(काष्ठा bfa_fcs_lport_ms_s *ms,
				क्रमागत port_ms_event event)
अणु
	bfa_trc(ms->port->fcs, ms->port->port_cfg.pwwn);
	bfa_trc(ms->port->fcs, event);

	चयन (event) अणु
	हाल MSSM_EVENT_TIMEOUT:
		/*
		 * Retry Timer Expired. Re-send
		 */
		bfa_sm_set_state(ms, bfa_fcs_lport_ms_sm_gmal_sending);
		bfa_fcs_lport_ms_send_gmal(ms, शून्य);
		अवरोध;

	हाल MSSM_EVENT_PORT_OFFLINE:
		bfa_sm_set_state(ms, bfa_fcs_lport_ms_sm_offline);
		bfa_समयr_stop(&ms->समयr);
		अवरोध;

	शेष:
		bfa_sm_fault(ms->port->fcs, event);
	पूर्ण
पूर्ण
/*
 *  ms_pvt MS local functions
 */

अटल व्योम
bfa_fcs_lport_ms_send_gmal(व्योम *ms_cbarg, काष्ठा bfa_fcxp_s *fcxp_alloced)
अणु
	काष्ठा bfa_fcs_lport_ms_s *ms = ms_cbarg;
	bfa_fcs_lport_t *port = ms->port;
	काष्ठा fchs_s	fchs;
	पूर्णांक		len;
	काष्ठा bfa_fcxp_s *fcxp;

	bfa_trc(port->fcs, port->pid);

	fcxp = fcxp_alloced ? fcxp_alloced :
	       bfa_fcs_fcxp_alloc(port->fcs, BFA_TRUE);
	अगर (!fcxp) अणु
		bfa_fcs_fcxp_alloc_रुको(port->fcs->bfa, &ms->fcxp_wqe,
				bfa_fcs_lport_ms_send_gmal, ms, BFA_TRUE);
		वापस;
	पूर्ण
	ms->fcxp = fcxp;

	len = fc_gmal_req_build(&fchs, bfa_fcxp_get_reqbuf(fcxp),
			     bfa_fcs_lport_get_fcid(port),
				 port->fabric->lps->pr_nwwn);

	bfa_fcxp_send(fcxp, शून्य, port->fabric->vf_id, port->lp_tag, BFA_FALSE,
			  FC_CLASS_3, len, &fchs,
			  bfa_fcs_lport_ms_gmal_response, (व्योम *)ms,
			  FC_MAX_PDUSZ, FC_FCCT_TOV);

	bfa_sm_send_event(ms, MSSM_EVENT_FCXP_SENT);
पूर्ण

अटल व्योम
bfa_fcs_lport_ms_gmal_response(व्योम *fcsarg, काष्ठा bfa_fcxp_s *fcxp,
				व्योम *cbarg, bfa_status_t req_status,
				u32 rsp_len, u32 resid_len,
				काष्ठा fchs_s *rsp_fchs)
अणु
	काष्ठा bfa_fcs_lport_ms_s *ms = (काष्ठा bfa_fcs_lport_ms_s *) cbarg;
	bfa_fcs_lport_t *port = ms->port;
	काष्ठा ct_hdr_s		*cthdr = शून्य;
	काष्ठा fcgs_gmal_resp_s *gmal_resp;
	काष्ठा fcgs_gmal_entry_s *gmal_entry;
	u32		num_entries;
	u8			*rsp_str;

	bfa_trc(port->fcs, req_status);
	bfa_trc(port->fcs, port->port_cfg.pwwn);

	/*
	 * Sanity Checks
	 */
	अगर (req_status != BFA_STATUS_OK) अणु
		bfa_trc(port->fcs, req_status);
		bfa_sm_send_event(ms, MSSM_EVENT_RSP_ERROR);
		वापस;
	पूर्ण

	cthdr = (काष्ठा ct_hdr_s *) BFA_FCXP_RSP_PLD(fcxp);
	cthdr->cmd_rsp_code = be16_to_cpu(cthdr->cmd_rsp_code);

	अगर (cthdr->cmd_rsp_code == CT_RSP_ACCEPT) अणु
		gmal_resp = (काष्ठा fcgs_gmal_resp_s *)(cthdr + 1);

		num_entries = be32_to_cpu(gmal_resp->ms_len);
		अगर (num_entries == 0) अणु
			bfa_sm_send_event(ms, MSSM_EVENT_RSP_ERROR);
			वापस;
		पूर्ण
		/*
		* The response could contain multiple Entries.
		* Entries क्रम SNMP पूर्णांकerface, etc.
		* We look क्रम the entry with a telnet prefix.
		* First "http://" entry refers to IP addr
		*/

		gmal_entry = (काष्ठा fcgs_gmal_entry_s *)gmal_resp->ms_ma;
		जबतक (num_entries > 0) अणु
			अगर (म_भेदन(gmal_entry->prefix,
				CT_GMAL_RESP_PREFIX_HTTP,
				माप(gmal_entry->prefix)) == 0) अणु

				/*
				* अगर the IP address is terminating with a '/',
				* हटाओ it.
				* Byte 0 consists of the length of the string.
				*/
				rsp_str = &(gmal_entry->prefix[0]);
				अगर (rsp_str[gmal_entry->len-1] == '/')
					rsp_str[gmal_entry->len-1] = 0;

				/* copy IP Address to fabric */
				strlcpy(bfa_fcs_lport_get_fabric_ipaddr(port),
					gmal_entry->ip_addr,
					BFA_FCS_FABRIC_IPADDR_SZ);
				अवरोध;
			पूर्ण अन्यथा अणु
				--num_entries;
				++gmal_entry;
			पूर्ण
		पूर्ण

		bfa_sm_send_event(ms, MSSM_EVENT_RSP_OK);
		वापस;
	पूर्ण

	bfa_trc(port->fcs, cthdr->reason_code);
	bfa_trc(port->fcs, cthdr->exp_code);
	bfa_sm_send_event(ms, MSSM_EVENT_RSP_ERROR);
पूर्ण

अटल व्योम
bfa_fcs_lport_ms_sm_gfn_sending(काष्ठा bfa_fcs_lport_ms_s *ms,
			क्रमागत port_ms_event event)
अणु
	bfa_trc(ms->port->fcs, ms->port->port_cfg.pwwn);
	bfa_trc(ms->port->fcs, event);

	चयन (event) अणु
	हाल MSSM_EVENT_FCXP_SENT:
		bfa_sm_set_state(ms, bfa_fcs_lport_ms_sm_gfn);
		अवरोध;

	हाल MSSM_EVENT_PORT_OFFLINE:
		bfa_sm_set_state(ms, bfa_fcs_lport_ms_sm_offline);
		bfa_fcxp_walloc_cancel(BFA_FCS_GET_HAL_FROM_PORT(ms->port),
					   &ms->fcxp_wqe);
		अवरोध;

	शेष:
		bfa_sm_fault(ms->port->fcs, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcs_lport_ms_sm_gfn(काष्ठा bfa_fcs_lport_ms_s *ms,
			क्रमागत port_ms_event event)
अणु
	bfa_trc(ms->port->fcs, ms->port->port_cfg.pwwn);
	bfa_trc(ms->port->fcs, event);

	चयन (event) अणु
	हाल MSSM_EVENT_RSP_ERROR:
		/*
		 * Start समयr क्रम a delayed retry
		 */
		अगर (ms->retry_cnt++ < BFA_FCS_MS_CMD_MAX_RETRIES) अणु
			bfa_sm_set_state(ms, bfa_fcs_lport_ms_sm_gfn_retry);
			ms->port->stats.ms_retries++;
			bfa_समयr_start(BFA_FCS_GET_HAL_FROM_PORT(ms->port),
				&ms->समयr, bfa_fcs_lport_ms_समयout, ms,
				BFA_FCS_RETRY_TIMEOUT);
		पूर्ण अन्यथा अणु
			bfa_sm_set_state(ms, bfa_fcs_lport_ms_sm_online);
			ms->retry_cnt = 0;
		पूर्ण
		अवरोध;

	हाल MSSM_EVENT_RSP_OK:
		bfa_sm_set_state(ms, bfa_fcs_lport_ms_sm_online);
		अवरोध;

	हाल MSSM_EVENT_PORT_OFFLINE:
		bfa_sm_set_state(ms, bfa_fcs_lport_ms_sm_offline);
		bfa_fcxp_discard(ms->fcxp);
		अवरोध;

	शेष:
		bfa_sm_fault(ms->port->fcs, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcs_lport_ms_sm_gfn_retry(काष्ठा bfa_fcs_lport_ms_s *ms,
				क्रमागत port_ms_event event)
अणु
	bfa_trc(ms->port->fcs, ms->port->port_cfg.pwwn);
	bfa_trc(ms->port->fcs, event);

	चयन (event) अणु
	हाल MSSM_EVENT_TIMEOUT:
		/*
		 * Retry Timer Expired. Re-send
		 */
		bfa_sm_set_state(ms, bfa_fcs_lport_ms_sm_gfn_sending);
		bfa_fcs_lport_ms_send_gfn(ms, शून्य);
		अवरोध;

	हाल MSSM_EVENT_PORT_OFFLINE:
		bfa_sm_set_state(ms, bfa_fcs_lport_ms_sm_offline);
		bfa_समयr_stop(&ms->समयr);
		अवरोध;

	शेष:
		bfa_sm_fault(ms->port->fcs, event);
	पूर्ण
पूर्ण
/*
 *  ms_pvt MS local functions
 */

अटल व्योम
bfa_fcs_lport_ms_send_gfn(व्योम *ms_cbarg, काष्ठा bfa_fcxp_s *fcxp_alloced)
अणु
	काष्ठा bfa_fcs_lport_ms_s *ms = ms_cbarg;
	bfa_fcs_lport_t *port = ms->port;
	काष्ठा fchs_s		fchs;
	पूर्णांक			len;
	काष्ठा bfa_fcxp_s *fcxp;

	bfa_trc(port->fcs, port->pid);

	fcxp = fcxp_alloced ? fcxp_alloced :
	       bfa_fcs_fcxp_alloc(port->fcs, BFA_TRUE);
	अगर (!fcxp) अणु
		bfa_fcs_fcxp_alloc_रुको(port->fcs->bfa, &ms->fcxp_wqe,
				bfa_fcs_lport_ms_send_gfn, ms, BFA_TRUE);
		वापस;
	पूर्ण
	ms->fcxp = fcxp;

	len = fc_gfn_req_build(&fchs, bfa_fcxp_get_reqbuf(fcxp),
			     bfa_fcs_lport_get_fcid(port),
				 port->fabric->lps->pr_nwwn);

	bfa_fcxp_send(fcxp, शून्य, port->fabric->vf_id, port->lp_tag, BFA_FALSE,
			  FC_CLASS_3, len, &fchs,
			  bfa_fcs_lport_ms_gfn_response, (व्योम *)ms,
			  FC_MAX_PDUSZ, FC_FCCT_TOV);

	bfa_sm_send_event(ms, MSSM_EVENT_FCXP_SENT);
पूर्ण

अटल व्योम
bfa_fcs_lport_ms_gfn_response(व्योम *fcsarg, काष्ठा bfa_fcxp_s *fcxp,
			व्योम *cbarg, bfa_status_t req_status, u32 rsp_len,
			u32 resid_len, काष्ठा fchs_s *rsp_fchs)
अणु
	काष्ठा bfa_fcs_lport_ms_s *ms = (काष्ठा bfa_fcs_lport_ms_s *) cbarg;
	bfa_fcs_lport_t *port = ms->port;
	काष्ठा ct_hdr_s	*cthdr = शून्य;
	wwn_t	       *gfn_resp;

	bfa_trc(port->fcs, req_status);
	bfa_trc(port->fcs, port->port_cfg.pwwn);

	/*
	 * Sanity Checks
	 */
	अगर (req_status != BFA_STATUS_OK) अणु
		bfa_trc(port->fcs, req_status);
		bfa_sm_send_event(ms, MSSM_EVENT_RSP_ERROR);
		वापस;
	पूर्ण

	cthdr = (काष्ठा ct_hdr_s *) BFA_FCXP_RSP_PLD(fcxp);
	cthdr->cmd_rsp_code = be16_to_cpu(cthdr->cmd_rsp_code);

	अगर (cthdr->cmd_rsp_code == CT_RSP_ACCEPT) अणु
		gfn_resp = (wwn_t *)(cthdr + 1);
		/* check अगर it has actually changed */
		अगर ((स_भेद((व्योम *)&bfa_fcs_lport_get_fabric_name(port),
				gfn_resp, माप(wwn_t)) != 0)) अणु
			bfa_fcs_fabric_set_fabric_name(port->fabric, *gfn_resp);
		पूर्ण
		bfa_sm_send_event(ms, MSSM_EVENT_RSP_OK);
		वापस;
	पूर्ण

	bfa_trc(port->fcs, cthdr->reason_code);
	bfa_trc(port->fcs, cthdr->exp_code);
	bfa_sm_send_event(ms, MSSM_EVENT_RSP_ERROR);
पूर्ण

/*
 *  ms_pvt MS local functions
 */

अटल व्योम
bfa_fcs_lport_ms_send_plogi(व्योम *ms_cbarg, काष्ठा bfa_fcxp_s *fcxp_alloced)
अणु
	काष्ठा bfa_fcs_lport_ms_s *ms = ms_cbarg;
	काष्ठा bfa_fcs_lport_s *port = ms->port;
	काष्ठा fchs_s	fchs;
	पूर्णांक	len;
	काष्ठा bfa_fcxp_s *fcxp;

	bfa_trc(port->fcs, port->pid);

	fcxp = fcxp_alloced ? fcxp_alloced :
	       bfa_fcs_fcxp_alloc(port->fcs, BFA_TRUE);
	अगर (!fcxp) अणु
		port->stats.ms_plogi_alloc_रुको++;
		bfa_fcs_fcxp_alloc_रुको(port->fcs->bfa, &ms->fcxp_wqe,
				bfa_fcs_lport_ms_send_plogi, ms, BFA_TRUE);
		वापस;
	पूर्ण
	ms->fcxp = fcxp;

	len = fc_plogi_build(&fchs, bfa_fcxp_get_reqbuf(fcxp),
			     bfa_hton3b(FC_MGMT_SERVER),
			     bfa_fcs_lport_get_fcid(port), 0,
			     port->port_cfg.pwwn, port->port_cfg.nwwn,
			     bfa_fcport_get_maxfrsize(port->fcs->bfa),
			     bfa_fcport_get_rx_bbcredit(port->fcs->bfa));

	bfa_fcxp_send(fcxp, शून्य, port->fabric->vf_id, port->lp_tag, BFA_FALSE,
			  FC_CLASS_3, len, &fchs,
			  bfa_fcs_lport_ms_plogi_response, (व्योम *)ms,
			  FC_MAX_PDUSZ, FC_ELS_TOV);

	port->stats.ms_plogi_sent++;
	bfa_sm_send_event(ms, MSSM_EVENT_FCXP_SENT);
पूर्ण

अटल व्योम
bfa_fcs_lport_ms_plogi_response(व्योम *fcsarg, काष्ठा bfa_fcxp_s *fcxp,
			व्योम *cbarg, bfa_status_t req_status,
			u32 rsp_len, u32 resid_len, काष्ठा fchs_s *rsp_fchs)
अणु
	काष्ठा bfa_fcs_lport_ms_s *ms = (काष्ठा bfa_fcs_lport_ms_s *) cbarg;
	काष्ठा bfa_fcs_lport_s *port = ms->port;
	काष्ठा fc_els_cmd_s *els_cmd;
	काष्ठा fc_ls_rjt_s *ls_rjt;

	bfa_trc(port->fcs, req_status);
	bfa_trc(port->fcs, port->port_cfg.pwwn);

	/*
	 * Sanity Checks
	 */
	अगर (req_status != BFA_STATUS_OK) अणु
		port->stats.ms_plogi_rsp_err++;
		bfa_trc(port->fcs, req_status);
		bfa_sm_send_event(ms, MSSM_EVENT_RSP_ERROR);
		वापस;
	पूर्ण

	els_cmd = (काष्ठा fc_els_cmd_s *) BFA_FCXP_RSP_PLD(fcxp);

	चयन (els_cmd->els_code) अणु

	हाल FC_ELS_ACC:
		अगर (rsp_len < माप(काष्ठा fc_logi_s)) अणु
			bfa_trc(port->fcs, rsp_len);
			port->stats.ms_plogi_acc_err++;
			bfa_sm_send_event(ms, MSSM_EVENT_RSP_ERROR);
			अवरोध;
		पूर्ण
		port->stats.ms_plogi_accepts++;
		bfa_sm_send_event(ms, MSSM_EVENT_RSP_OK);
		अवरोध;

	हाल FC_ELS_LS_RJT:
		ls_rjt = (काष्ठा fc_ls_rjt_s *) BFA_FCXP_RSP_PLD(fcxp);

		bfa_trc(port->fcs, ls_rjt->reason_code);
		bfa_trc(port->fcs, ls_rjt->reason_code_expl);

		port->stats.ms_rejects++;
		bfa_sm_send_event(ms, MSSM_EVENT_RSP_ERROR);
		अवरोध;

	शेष:
		port->stats.ms_plogi_unknown_rsp++;
		bfa_trc(port->fcs, els_cmd->els_code);
		bfa_sm_send_event(ms, MSSM_EVENT_RSP_ERROR);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcs_lport_ms_समयout(व्योम *arg)
अणु
	काष्ठा bfa_fcs_lport_ms_s *ms = (काष्ठा bfa_fcs_lport_ms_s *) arg;

	ms->port->stats.ms_समयouts++;
	bfa_sm_send_event(ms, MSSM_EVENT_TIMEOUT);
पूर्ण


व्योम
bfa_fcs_lport_ms_init(काष्ठा bfa_fcs_lport_s *port)
अणु
	काष्ठा bfa_fcs_lport_ms_s *ms = BFA_FCS_GET_MS_FROM_PORT(port);

	ms->port = port;
	bfa_sm_set_state(ms, bfa_fcs_lport_ms_sm_offline);

	/*
	 * Invoke init routines of sub modules.
	 */
	bfa_fcs_lport_fdmi_init(ms);
पूर्ण

व्योम
bfa_fcs_lport_ms_offline(काष्ठा bfa_fcs_lport_s *port)
अणु
	काष्ठा bfa_fcs_lport_ms_s *ms = BFA_FCS_GET_MS_FROM_PORT(port);

	ms->port = port;
	bfa_sm_send_event(ms, MSSM_EVENT_PORT_OFFLINE);
	bfa_fcs_lport_fdmi_offline(ms);
पूर्ण

व्योम
bfa_fcs_lport_ms_online(काष्ठा bfa_fcs_lport_s *port)
अणु
	काष्ठा bfa_fcs_lport_ms_s *ms = BFA_FCS_GET_MS_FROM_PORT(port);

	ms->port = port;
	bfa_sm_send_event(ms, MSSM_EVENT_PORT_ONLINE);
पूर्ण
व्योम
bfa_fcs_lport_ms_fabric_rscn(काष्ठा bfa_fcs_lport_s *port)
अणु
	काष्ठा bfa_fcs_lport_ms_s *ms = BFA_FCS_GET_MS_FROM_PORT(port);

	/* toकरो.  Handle this only  when in Online state */
	अगर (bfa_sm_cmp_state(ms, bfa_fcs_lport_ms_sm_online))
		bfa_sm_send_event(ms, MSSM_EVENT_PORT_FABRIC_RSCN);
पूर्ण

/*
 * @page ns_sm_info VPORT NS State Machine
 *
 * @section ns_sm_पूर्णांकeractions VPORT NS State Machine Interactions
 *
 * @section ns_sm VPORT NS State Machine
 * img ns_sm.jpg
 */

/*
 * क्रमward declarations
 */
अटल व्योम     bfa_fcs_lport_ns_send_plogi(व्योम *ns_cbarg,
					   काष्ठा bfa_fcxp_s *fcxp_alloced);
अटल व्योम     bfa_fcs_lport_ns_send_rspn_id(व्योम *ns_cbarg,
					     काष्ठा bfa_fcxp_s *fcxp_alloced);
अटल व्योम     bfa_fcs_lport_ns_send_rft_id(व्योम *ns_cbarg,
					    काष्ठा bfa_fcxp_s *fcxp_alloced);
अटल व्योम     bfa_fcs_lport_ns_send_rff_id(व्योम *ns_cbarg,
					    काष्ठा bfa_fcxp_s *fcxp_alloced);
अटल व्योम     bfa_fcs_lport_ns_send_gid_ft(व्योम *ns_cbarg,
					    काष्ठा bfa_fcxp_s *fcxp_alloced);
अटल व्योम	bfa_fcs_lport_ns_send_rnn_id(व्योम *ns_cbarg,
					काष्ठा bfa_fcxp_s *fcxp_alloced);
अटल व्योम	bfa_fcs_lport_ns_send_rsnn_nn(व्योम *ns_cbarg,
					काष्ठा bfa_fcxp_s *fcxp_alloced);
अटल व्योम     bfa_fcs_lport_ns_समयout(व्योम *arg);
अटल व्योम     bfa_fcs_lport_ns_plogi_response(व्योम *fcsarg,
					       काष्ठा bfa_fcxp_s *fcxp,
					       व्योम *cbarg,
					       bfa_status_t req_status,
					       u32 rsp_len,
					       u32 resid_len,
					       काष्ठा fchs_s *rsp_fchs);
अटल व्योम     bfa_fcs_lport_ns_rspn_id_response(व्योम *fcsarg,
						 काष्ठा bfa_fcxp_s *fcxp,
						 व्योम *cbarg,
						 bfa_status_t req_status,
						 u32 rsp_len,
						 u32 resid_len,
						 काष्ठा fchs_s *rsp_fchs);
अटल व्योम     bfa_fcs_lport_ns_rft_id_response(व्योम *fcsarg,
						काष्ठा bfa_fcxp_s *fcxp,
						व्योम *cbarg,
						bfa_status_t req_status,
						u32 rsp_len,
						u32 resid_len,
						काष्ठा fchs_s *rsp_fchs);
अटल व्योम     bfa_fcs_lport_ns_rff_id_response(व्योम *fcsarg,
						काष्ठा bfa_fcxp_s *fcxp,
						व्योम *cbarg,
						bfa_status_t req_status,
						u32 rsp_len,
						u32 resid_len,
						काष्ठा fchs_s *rsp_fchs);
अटल व्योम     bfa_fcs_lport_ns_gid_ft_response(व्योम *fcsarg,
						काष्ठा bfa_fcxp_s *fcxp,
						व्योम *cbarg,
						bfa_status_t req_status,
						u32 rsp_len,
						u32 resid_len,
						काष्ठा fchs_s *rsp_fchs);
अटल व्योम     bfa_fcs_lport_ns_rnn_id_response(व्योम *fcsarg,
						काष्ठा bfa_fcxp_s *fcxp,
						व्योम *cbarg,
						bfa_status_t req_status,
						u32 rsp_len,
						u32 resid_len,
						काष्ठा fchs_s *rsp_fchs);
अटल व्योम     bfa_fcs_lport_ns_rsnn_nn_response(व्योम *fcsarg,
						काष्ठा bfa_fcxp_s *fcxp,
						व्योम *cbarg,
						bfa_status_t req_status,
						u32 rsp_len,
						u32 resid_len,
						काष्ठा fchs_s *rsp_fchs);
अटल व्योम     bfa_fcs_lport_ns_process_gidft_pids(
				काष्ठा bfa_fcs_lport_s *port,
				u32 *pid_buf, u32 n_pids);

अटल व्योम bfa_fcs_lport_ns_boot_target_disc(bfa_fcs_lport_t *port);
/*
 *  fcs_ns_sm FCS nameserver पूर्णांकerface state machine
 */

/*
 * VPort NS State Machine events
 */
क्रमागत vport_ns_event अणु
	NSSM_EVENT_PORT_ONLINE = 1,
	NSSM_EVENT_PORT_OFFLINE = 2,
	NSSM_EVENT_PLOGI_SENT = 3,
	NSSM_EVENT_RSP_OK = 4,
	NSSM_EVENT_RSP_ERROR = 5,
	NSSM_EVENT_TIMEOUT = 6,
	NSSM_EVENT_NS_QUERY = 7,
	NSSM_EVENT_RSPNID_SENT = 8,
	NSSM_EVENT_RFTID_SENT = 9,
	NSSM_EVENT_RFFID_SENT = 10,
	NSSM_EVENT_GIDFT_SENT = 11,
	NSSM_EVENT_RNNID_SENT = 12,
	NSSM_EVENT_RSNN_NN_SENT = 13,
पूर्ण;

अटल व्योम     bfa_fcs_lport_ns_sm_offline(काष्ठा bfa_fcs_lport_ns_s *ns,
					   क्रमागत vport_ns_event event);
अटल व्योम     bfa_fcs_lport_ns_sm_plogi_sending(काष्ठा bfa_fcs_lport_ns_s *ns,
						 क्रमागत vport_ns_event event);
अटल व्योम     bfa_fcs_lport_ns_sm_plogi(काष्ठा bfa_fcs_lport_ns_s *ns,
					 क्रमागत vport_ns_event event);
अटल व्योम     bfa_fcs_lport_ns_sm_plogi_retry(काष्ठा bfa_fcs_lport_ns_s *ns,
					       क्रमागत vport_ns_event event);
अटल व्योम     bfa_fcs_lport_ns_sm_sending_rspn_id(
					काष्ठा bfa_fcs_lport_ns_s *ns,
					क्रमागत vport_ns_event event);
अटल व्योम     bfa_fcs_lport_ns_sm_rspn_id(काष्ठा bfa_fcs_lport_ns_s *ns,
					   क्रमागत vport_ns_event event);
अटल व्योम     bfa_fcs_lport_ns_sm_rspn_id_retry(काष्ठा bfa_fcs_lport_ns_s *ns,
						 क्रमागत vport_ns_event event);
अटल व्योम     bfa_fcs_lport_ns_sm_sending_rft_id(
					काष्ठा bfa_fcs_lport_ns_s *ns,
					क्रमागत vport_ns_event event);
अटल व्योम     bfa_fcs_lport_ns_sm_rft_id_retry(काष्ठा bfa_fcs_lport_ns_s *ns,
						क्रमागत vport_ns_event event);
अटल व्योम     bfa_fcs_lport_ns_sm_rft_id(काष्ठा bfa_fcs_lport_ns_s *ns,
					  क्रमागत vport_ns_event event);
अटल व्योम     bfa_fcs_lport_ns_sm_sending_rff_id(
					काष्ठा bfa_fcs_lport_ns_s *ns,
					क्रमागत vport_ns_event event);
अटल व्योम     bfa_fcs_lport_ns_sm_rff_id_retry(काष्ठा bfa_fcs_lport_ns_s *ns,
						क्रमागत vport_ns_event event);
अटल व्योम     bfa_fcs_lport_ns_sm_rff_id(काष्ठा bfa_fcs_lport_ns_s *ns,
					  क्रमागत vport_ns_event event);
अटल व्योम     bfa_fcs_lport_ns_sm_sending_gid_ft(
					काष्ठा bfa_fcs_lport_ns_s *ns,
					क्रमागत vport_ns_event event);
अटल व्योम     bfa_fcs_lport_ns_sm_gid_ft(काष्ठा bfa_fcs_lport_ns_s *ns,
					  क्रमागत vport_ns_event event);
अटल व्योम     bfa_fcs_lport_ns_sm_gid_ft_retry(काष्ठा bfa_fcs_lport_ns_s *ns,
						क्रमागत vport_ns_event event);
अटल व्योम     bfa_fcs_lport_ns_sm_online(काष्ठा bfa_fcs_lport_ns_s *ns,
					  क्रमागत vport_ns_event event);
अटल व्योम     bfa_fcs_lport_ns_sm_sending_rnn_id(
					काष्ठा bfa_fcs_lport_ns_s *ns,
					क्रमागत vport_ns_event event);
अटल व्योम     bfa_fcs_lport_ns_sm_rnn_id(काष्ठा bfa_fcs_lport_ns_s *ns,
					क्रमागत vport_ns_event event);
अटल व्योम     bfa_fcs_lport_ns_sm_rnn_id_retry(काष्ठा bfa_fcs_lport_ns_s *ns,
						क्रमागत vport_ns_event event);
अटल व्योम     bfa_fcs_lport_ns_sm_sending_rsnn_nn(
					काष्ठा bfa_fcs_lport_ns_s *ns,
					क्रमागत vport_ns_event event);
अटल व्योम     bfa_fcs_lport_ns_sm_rsnn_nn(काष्ठा bfa_fcs_lport_ns_s *ns,
						क्रमागत vport_ns_event event);
अटल व्योम     bfa_fcs_lport_ns_sm_rsnn_nn_retry(
					काष्ठा bfa_fcs_lport_ns_s *ns,
					क्रमागत vport_ns_event event);
/*
 *	Start in offline state - aरुकोing linkup
 */
अटल व्योम
bfa_fcs_lport_ns_sm_offline(काष्ठा bfa_fcs_lport_ns_s *ns,
			क्रमागत vport_ns_event event)
अणु
	bfa_trc(ns->port->fcs, ns->port->port_cfg.pwwn);
	bfa_trc(ns->port->fcs, event);

	चयन (event) अणु
	हाल NSSM_EVENT_PORT_ONLINE:
		bfa_sm_set_state(ns, bfa_fcs_lport_ns_sm_plogi_sending);
		bfa_fcs_lport_ns_send_plogi(ns, शून्य);
		अवरोध;

	हाल NSSM_EVENT_PORT_OFFLINE:
		अवरोध;

	शेष:
		bfa_sm_fault(ns->port->fcs, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcs_lport_ns_sm_plogi_sending(काष्ठा bfa_fcs_lport_ns_s *ns,
			क्रमागत vport_ns_event event)
अणु
	bfa_trc(ns->port->fcs, ns->port->port_cfg.pwwn);
	bfa_trc(ns->port->fcs, event);

	चयन (event) अणु
	हाल NSSM_EVENT_PLOGI_SENT:
		bfa_sm_set_state(ns, bfa_fcs_lport_ns_sm_plogi);
		अवरोध;

	हाल NSSM_EVENT_PORT_OFFLINE:
		bfa_sm_set_state(ns, bfa_fcs_lport_ns_sm_offline);
		bfa_fcxp_walloc_cancel(BFA_FCS_GET_HAL_FROM_PORT(ns->port),
					   &ns->fcxp_wqe);
		अवरोध;

	शेष:
		bfa_sm_fault(ns->port->fcs, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcs_lport_ns_sm_plogi(काष्ठा bfa_fcs_lport_ns_s *ns,
			क्रमागत vport_ns_event event)
अणु
	bfa_trc(ns->port->fcs, ns->port->port_cfg.pwwn);
	bfa_trc(ns->port->fcs, event);

	चयन (event) अणु
	हाल NSSM_EVENT_RSP_ERROR:
		/*
		 * Start समयr क्रम a delayed retry
		 */
		bfa_sm_set_state(ns, bfa_fcs_lport_ns_sm_plogi_retry);
		ns->port->stats.ns_retries++;
		bfa_समयr_start(BFA_FCS_GET_HAL_FROM_PORT(ns->port),
				    &ns->समयr, bfa_fcs_lport_ns_समयout, ns,
				    BFA_FCS_RETRY_TIMEOUT);
		अवरोध;

	हाल NSSM_EVENT_RSP_OK:
		bfa_sm_set_state(ns, bfa_fcs_lport_ns_sm_sending_rnn_id);
		ns->num_rnnid_retries = 0;
		bfa_fcs_lport_ns_send_rnn_id(ns, शून्य);
		अवरोध;

	हाल NSSM_EVENT_PORT_OFFLINE:
		bfa_sm_set_state(ns, bfa_fcs_lport_ns_sm_offline);
		bfa_fcxp_discard(ns->fcxp);
		अवरोध;

	शेष:
		bfa_sm_fault(ns->port->fcs, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcs_lport_ns_sm_plogi_retry(काष्ठा bfa_fcs_lport_ns_s *ns,
				क्रमागत vport_ns_event event)
अणु
	bfa_trc(ns->port->fcs, ns->port->port_cfg.pwwn);
	bfa_trc(ns->port->fcs, event);

	चयन (event) अणु
	हाल NSSM_EVENT_TIMEOUT:
		/*
		 * Retry Timer Expired. Re-send
		 */
		bfa_sm_set_state(ns, bfa_fcs_lport_ns_sm_plogi_sending);
		bfa_fcs_lport_ns_send_plogi(ns, शून्य);
		अवरोध;

	हाल NSSM_EVENT_PORT_OFFLINE:
		bfa_sm_set_state(ns, bfa_fcs_lport_ns_sm_offline);
		bfa_समयr_stop(&ns->समयr);
		अवरोध;

	शेष:
		bfa_sm_fault(ns->port->fcs, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcs_lport_ns_sm_sending_rnn_id(काष्ठा bfa_fcs_lport_ns_s *ns,
					क्रमागत vport_ns_event event)
अणु
	bfa_trc(ns->port->fcs, ns->port->port_cfg.pwwn);
	bfa_trc(ns->port->fcs, event);

	चयन (event) अणु
	हाल NSSM_EVENT_RNNID_SENT:
		bfa_sm_set_state(ns, bfa_fcs_lport_ns_sm_rnn_id);
		अवरोध;

	हाल NSSM_EVENT_PORT_OFFLINE:
		bfa_sm_set_state(ns, bfa_fcs_lport_ns_sm_offline);
		bfa_fcxp_walloc_cancel(BFA_FCS_GET_HAL_FROM_PORT(ns->port),
						&ns->fcxp_wqe);
		अवरोध;
	शेष:
		bfa_sm_fault(ns->port->fcs, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcs_lport_ns_sm_rnn_id(काष्ठा bfa_fcs_lport_ns_s *ns,
				क्रमागत vport_ns_event event)
अणु
	bfa_trc(ns->port->fcs, ns->port->port_cfg.pwwn);
	bfa_trc(ns->port->fcs, event);

	चयन (event) अणु
	हाल NSSM_EVENT_RSP_OK:
		bfa_sm_set_state(ns, bfa_fcs_lport_ns_sm_sending_rsnn_nn);
		ns->num_rnnid_retries = 0;
		ns->num_rsnn_nn_retries = 0;
		bfa_fcs_lport_ns_send_rsnn_nn(ns, शून्य);
		अवरोध;

	हाल NSSM_EVENT_RSP_ERROR:
		अगर (ns->num_rnnid_retries < BFA_FCS_MAX_NS_RETRIES) अणु
			bfa_sm_set_state(ns, bfa_fcs_lport_ns_sm_rnn_id_retry);
			ns->port->stats.ns_retries++;
			ns->num_rnnid_retries++;
			bfa_समयr_start(BFA_FCS_GET_HAL_FROM_PORT(ns->port),
				&ns->समयr, bfa_fcs_lport_ns_समयout, ns,
				BFA_FCS_RETRY_TIMEOUT);
		पूर्ण अन्यथा अणु
			bfa_sm_set_state(ns,
				bfa_fcs_lport_ns_sm_sending_rspn_id);
			bfa_fcs_lport_ns_send_rspn_id(ns, शून्य);
		पूर्ण
		अवरोध;

	हाल NSSM_EVENT_PORT_OFFLINE:
		bfa_fcxp_discard(ns->fcxp);
		bfa_sm_set_state(ns, bfa_fcs_lport_ns_sm_offline);
		अवरोध;

	शेष:
		bfa_sm_fault(ns->port->fcs, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcs_lport_ns_sm_rnn_id_retry(काष्ठा bfa_fcs_lport_ns_s *ns,
				क्रमागत vport_ns_event event)
अणु
	bfa_trc(ns->port->fcs, ns->port->port_cfg.pwwn);
	bfa_trc(ns->port->fcs, event);

	चयन (event) अणु
	हाल NSSM_EVENT_TIMEOUT:
		bfa_sm_set_state(ns, bfa_fcs_lport_ns_sm_sending_rnn_id);
		bfa_fcs_lport_ns_send_rnn_id(ns, शून्य);
		अवरोध;

	हाल NSSM_EVENT_PORT_OFFLINE:
		bfa_sm_set_state(ns, bfa_fcs_lport_ns_sm_offline);
		bfa_समयr_stop(&ns->समयr);
		अवरोध;

	शेष:
		bfa_sm_fault(ns->port->fcs, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcs_lport_ns_sm_sending_rsnn_nn(काष्ठा bfa_fcs_lport_ns_s *ns,
					क्रमागत vport_ns_event event)
अणु
	bfa_trc(ns->port->fcs, ns->port->port_cfg.pwwn);
	bfa_trc(ns->port->fcs, event);

	चयन (event) अणु
	हाल NSSM_EVENT_RSNN_NN_SENT:
		bfa_sm_set_state(ns, bfa_fcs_lport_ns_sm_rsnn_nn);
		अवरोध;

	हाल NSSM_EVENT_PORT_OFFLINE:
		bfa_sm_set_state(ns, bfa_fcs_lport_ns_sm_offline);
		bfa_fcxp_walloc_cancel(BFA_FCS_GET_HAL_FROM_PORT(ns->port),
			&ns->fcxp_wqe);
		अवरोध;

	शेष:
		bfa_sm_fault(ns->port->fcs, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcs_lport_ns_sm_rsnn_nn(काष्ठा bfa_fcs_lport_ns_s *ns,
				क्रमागत vport_ns_event event)
अणु
	bfa_trc(ns->port->fcs, ns->port->port_cfg.pwwn);
	bfa_trc(ns->port->fcs, event);

	चयन (event) अणु
	हाल NSSM_EVENT_RSP_OK:
		bfa_sm_set_state(ns, bfa_fcs_lport_ns_sm_sending_rspn_id);
		ns->num_rsnn_nn_retries = 0;
		bfa_fcs_lport_ns_send_rspn_id(ns, शून्य);
		अवरोध;

	हाल NSSM_EVENT_RSP_ERROR:
		अगर (ns->num_rsnn_nn_retries < BFA_FCS_MAX_NS_RETRIES) अणु
			bfa_sm_set_state(ns, bfa_fcs_lport_ns_sm_rsnn_nn_retry);
			ns->port->stats.ns_retries++;
			ns->num_rsnn_nn_retries++;
			bfa_समयr_start(BFA_FCS_GET_HAL_FROM_PORT(ns->port),
					&ns->समयr, bfa_fcs_lport_ns_समयout,
					ns, BFA_FCS_RETRY_TIMEOUT);
		पूर्ण अन्यथा अणु
			bfa_sm_set_state(ns,
				bfa_fcs_lport_ns_sm_sending_rspn_id);
			bfa_fcs_lport_ns_send_rspn_id(ns, शून्य);
		पूर्ण
		अवरोध;

	हाल NSSM_EVENT_PORT_OFFLINE:
		bfa_sm_set_state(ns, bfa_fcs_lport_ns_sm_offline);
		bfa_fcxp_discard(ns->fcxp);
		अवरोध;

	शेष:
		bfa_sm_fault(ns->port->fcs, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcs_lport_ns_sm_rsnn_nn_retry(काष्ठा bfa_fcs_lport_ns_s *ns,
					क्रमागत vport_ns_event event)
अणु
	bfa_trc(ns->port->fcs, ns->port->port_cfg.pwwn);
	bfa_trc(ns->port->fcs, event);

	चयन (event) अणु
	हाल NSSM_EVENT_TIMEOUT:
		bfa_sm_set_state(ns, bfa_fcs_lport_ns_sm_sending_rsnn_nn);
		bfa_fcs_lport_ns_send_rsnn_nn(ns, शून्य);
		अवरोध;

	हाल NSSM_EVENT_PORT_OFFLINE:
		bfa_sm_set_state(ns, bfa_fcs_lport_ns_sm_offline);
		bfa_समयr_stop(&ns->समयr);
		अवरोध;

	शेष:
		bfa_sm_fault(ns->port->fcs, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcs_lport_ns_sm_sending_rspn_id(काष्ठा bfa_fcs_lport_ns_s *ns,
				   क्रमागत vport_ns_event event)
अणु
	bfa_trc(ns->port->fcs, ns->port->port_cfg.pwwn);
	bfa_trc(ns->port->fcs, event);

	चयन (event) अणु
	हाल NSSM_EVENT_RSPNID_SENT:
		bfa_sm_set_state(ns, bfa_fcs_lport_ns_sm_rspn_id);
		अवरोध;

	हाल NSSM_EVENT_PORT_OFFLINE:
		bfa_sm_set_state(ns, bfa_fcs_lport_ns_sm_offline);
		bfa_fcxp_walloc_cancel(BFA_FCS_GET_HAL_FROM_PORT(ns->port),
					   &ns->fcxp_wqe);
		अवरोध;

	शेष:
		bfa_sm_fault(ns->port->fcs, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcs_lport_ns_sm_rspn_id(काष्ठा bfa_fcs_lport_ns_s *ns,
			क्रमागत vport_ns_event event)
अणु
	bfa_trc(ns->port->fcs, ns->port->port_cfg.pwwn);
	bfa_trc(ns->port->fcs, event);

	चयन (event) अणु
	हाल NSSM_EVENT_RSP_ERROR:
		/*
		 * Start समयr क्रम a delayed retry
		 */
		bfa_sm_set_state(ns, bfa_fcs_lport_ns_sm_rspn_id_retry);
		ns->port->stats.ns_retries++;
		bfa_समयr_start(BFA_FCS_GET_HAL_FROM_PORT(ns->port),
				    &ns->समयr, bfa_fcs_lport_ns_समयout, ns,
				    BFA_FCS_RETRY_TIMEOUT);
		अवरोध;

	हाल NSSM_EVENT_RSP_OK:
		bfa_sm_set_state(ns, bfa_fcs_lport_ns_sm_sending_rft_id);
		bfa_fcs_lport_ns_send_rft_id(ns, शून्य);
		अवरोध;

	हाल NSSM_EVENT_PORT_OFFLINE:
		bfa_fcxp_discard(ns->fcxp);
		bfa_sm_set_state(ns, bfa_fcs_lport_ns_sm_offline);
		अवरोध;

	शेष:
		bfa_sm_fault(ns->port->fcs, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcs_lport_ns_sm_rspn_id_retry(काष्ठा bfa_fcs_lport_ns_s *ns,
				क्रमागत vport_ns_event event)
अणु
	bfa_trc(ns->port->fcs, ns->port->port_cfg.pwwn);
	bfa_trc(ns->port->fcs, event);

	चयन (event) अणु
	हाल NSSM_EVENT_TIMEOUT:
		/*
		 * Retry Timer Expired. Re-send
		 */
		bfa_sm_set_state(ns, bfa_fcs_lport_ns_sm_sending_rspn_id);
		bfa_fcs_lport_ns_send_rspn_id(ns, शून्य);
		अवरोध;

	हाल NSSM_EVENT_PORT_OFFLINE:
		bfa_sm_set_state(ns, bfa_fcs_lport_ns_sm_offline);
		bfa_समयr_stop(&ns->समयr);
		अवरोध;

	शेष:
		bfa_sm_fault(ns->port->fcs, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcs_lport_ns_sm_sending_rft_id(काष्ठा bfa_fcs_lport_ns_s *ns,
				  क्रमागत vport_ns_event event)
अणु
	bfa_trc(ns->port->fcs, ns->port->port_cfg.pwwn);
	bfa_trc(ns->port->fcs, event);

	चयन (event) अणु
	हाल NSSM_EVENT_RFTID_SENT:
		bfa_sm_set_state(ns, bfa_fcs_lport_ns_sm_rft_id);
		अवरोध;

	हाल NSSM_EVENT_PORT_OFFLINE:
		bfa_sm_set_state(ns, bfa_fcs_lport_ns_sm_offline);
		bfa_fcxp_walloc_cancel(BFA_FCS_GET_HAL_FROM_PORT(ns->port),
					   &ns->fcxp_wqe);
		अवरोध;

	शेष:
		bfa_sm_fault(ns->port->fcs, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcs_lport_ns_sm_rft_id(काष्ठा bfa_fcs_lport_ns_s *ns,
			क्रमागत vport_ns_event event)
अणु
	bfa_trc(ns->port->fcs, ns->port->port_cfg.pwwn);
	bfa_trc(ns->port->fcs, event);

	चयन (event) अणु
	हाल NSSM_EVENT_RSP_OK:
		/* Now move to रेजिस्टर FC4 Features */
		bfa_sm_set_state(ns, bfa_fcs_lport_ns_sm_sending_rff_id);
		bfa_fcs_lport_ns_send_rff_id(ns, शून्य);
		अवरोध;

	हाल NSSM_EVENT_RSP_ERROR:
		/*
		 * Start समयr क्रम a delayed retry
		 */
		bfa_sm_set_state(ns, bfa_fcs_lport_ns_sm_rft_id_retry);
		ns->port->stats.ns_retries++;
		bfa_समयr_start(BFA_FCS_GET_HAL_FROM_PORT(ns->port),
				    &ns->समयr, bfa_fcs_lport_ns_समयout, ns,
				    BFA_FCS_RETRY_TIMEOUT);
		अवरोध;

	हाल NSSM_EVENT_PORT_OFFLINE:
		bfa_sm_set_state(ns, bfa_fcs_lport_ns_sm_offline);
		bfa_fcxp_discard(ns->fcxp);
		अवरोध;

	शेष:
		bfa_sm_fault(ns->port->fcs, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcs_lport_ns_sm_rft_id_retry(काष्ठा bfa_fcs_lport_ns_s *ns,
				क्रमागत vport_ns_event event)
अणु
	bfa_trc(ns->port->fcs, ns->port->port_cfg.pwwn);
	bfa_trc(ns->port->fcs, event);

	चयन (event) अणु
	हाल NSSM_EVENT_TIMEOUT:
		bfa_sm_set_state(ns, bfa_fcs_lport_ns_sm_sending_rft_id);
		bfa_fcs_lport_ns_send_rft_id(ns, शून्य);
		अवरोध;

	हाल NSSM_EVENT_PORT_OFFLINE:
		bfa_sm_set_state(ns, bfa_fcs_lport_ns_sm_offline);
		bfa_समयr_stop(&ns->समयr);
		अवरोध;

	शेष:
		bfa_sm_fault(ns->port->fcs, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcs_lport_ns_sm_sending_rff_id(काष्ठा bfa_fcs_lport_ns_s *ns,
				  क्रमागत vport_ns_event event)
अणु
	bfa_trc(ns->port->fcs, ns->port->port_cfg.pwwn);
	bfa_trc(ns->port->fcs, event);

	चयन (event) अणु
	हाल NSSM_EVENT_RFFID_SENT:
		bfa_sm_set_state(ns, bfa_fcs_lport_ns_sm_rff_id);
		अवरोध;

	हाल NSSM_EVENT_PORT_OFFLINE:
		bfa_sm_set_state(ns, bfa_fcs_lport_ns_sm_offline);
		bfa_fcxp_walloc_cancel(BFA_FCS_GET_HAL_FROM_PORT(ns->port),
					   &ns->fcxp_wqe);
		अवरोध;

	शेष:
		bfa_sm_fault(ns->port->fcs, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcs_lport_ns_sm_rff_id(काष्ठा bfa_fcs_lport_ns_s *ns,
			क्रमागत vport_ns_event event)
अणु
	bfa_trc(ns->port->fcs, ns->port->port_cfg.pwwn);
	bfa_trc(ns->port->fcs, event);

	चयन (event) अणु
	हाल NSSM_EVENT_RSP_OK:

		/*
		 * If min cfg mode is enabled, we करोnot initiate rport
		 * discovery with the fabric. Instead, we will retrieve the
		 * boot tarमाला_लो from HAL/FW.
		 */
		अगर (__fcs_min_cfg(ns->port->fcs)) अणु
			bfa_fcs_lport_ns_boot_target_disc(ns->port);
			bfa_sm_set_state(ns, bfa_fcs_lport_ns_sm_online);
			वापस;
		पूर्ण

		/*
		 * If the port role is Initiator Mode issue NS query.
		 * If it is Target Mode, skip this and go to online.
		 */
		अगर (BFA_FCS_VPORT_IS_INITIATOR_MODE(ns->port)) अणु
			bfa_sm_set_state(ns,
				bfa_fcs_lport_ns_sm_sending_gid_ft);
			bfa_fcs_lport_ns_send_gid_ft(ns, शून्य);
		पूर्ण
		/*
		 * kick off mgmt srvr state machine
		 */
		bfa_fcs_lport_ms_online(ns->port);
		अवरोध;

	हाल NSSM_EVENT_RSP_ERROR:
		/*
		 * Start समयr क्रम a delayed retry
		 */
		bfa_sm_set_state(ns, bfa_fcs_lport_ns_sm_rff_id_retry);
		ns->port->stats.ns_retries++;
		bfa_समयr_start(BFA_FCS_GET_HAL_FROM_PORT(ns->port),
				    &ns->समयr, bfa_fcs_lport_ns_समयout, ns,
				    BFA_FCS_RETRY_TIMEOUT);
		अवरोध;

	हाल NSSM_EVENT_PORT_OFFLINE:
		bfa_sm_set_state(ns, bfa_fcs_lport_ns_sm_offline);
		bfa_fcxp_discard(ns->fcxp);
		अवरोध;

	शेष:
		bfa_sm_fault(ns->port->fcs, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcs_lport_ns_sm_rff_id_retry(काष्ठा bfa_fcs_lport_ns_s *ns,
				क्रमागत vport_ns_event event)
अणु
	bfa_trc(ns->port->fcs, ns->port->port_cfg.pwwn);
	bfa_trc(ns->port->fcs, event);

	चयन (event) अणु
	हाल NSSM_EVENT_TIMEOUT:
		bfa_sm_set_state(ns, bfa_fcs_lport_ns_sm_sending_rff_id);
		bfa_fcs_lport_ns_send_rff_id(ns, शून्य);
		अवरोध;

	हाल NSSM_EVENT_PORT_OFFLINE:
		bfa_sm_set_state(ns, bfa_fcs_lport_ns_sm_offline);
		bfa_समयr_stop(&ns->समयr);
		अवरोध;

	शेष:
		bfa_sm_fault(ns->port->fcs, event);
	पूर्ण
पूर्ण
अटल व्योम
bfa_fcs_lport_ns_sm_sending_gid_ft(काष्ठा bfa_fcs_lport_ns_s *ns,
				  क्रमागत vport_ns_event event)
अणु
	bfa_trc(ns->port->fcs, ns->port->port_cfg.pwwn);
	bfa_trc(ns->port->fcs, event);

	चयन (event) अणु
	हाल NSSM_EVENT_GIDFT_SENT:
		bfa_sm_set_state(ns, bfa_fcs_lport_ns_sm_gid_ft);
		अवरोध;

	हाल NSSM_EVENT_PORT_OFFLINE:
		bfa_sm_set_state(ns, bfa_fcs_lport_ns_sm_offline);
		bfa_fcxp_walloc_cancel(BFA_FCS_GET_HAL_FROM_PORT(ns->port),
					   &ns->fcxp_wqe);
		अवरोध;

	शेष:
		bfa_sm_fault(ns->port->fcs, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcs_lport_ns_sm_gid_ft(काष्ठा bfa_fcs_lport_ns_s *ns,
			क्रमागत vport_ns_event event)
अणु
	bfa_trc(ns->port->fcs, ns->port->port_cfg.pwwn);
	bfa_trc(ns->port->fcs, event);

	चयन (event) अणु
	हाल NSSM_EVENT_RSP_OK:
		bfa_sm_set_state(ns, bfa_fcs_lport_ns_sm_online);
		अवरोध;

	हाल NSSM_EVENT_RSP_ERROR:
		/*
		 * TBD: क्रम certain reject codes, we करोn't need to retry
		 */
		/*
		 * Start समयr क्रम a delayed retry
		 */
		bfa_sm_set_state(ns, bfa_fcs_lport_ns_sm_gid_ft_retry);
		ns->port->stats.ns_retries++;
		bfa_समयr_start(BFA_FCS_GET_HAL_FROM_PORT(ns->port),
				    &ns->समयr, bfa_fcs_lport_ns_समयout, ns,
				    BFA_FCS_RETRY_TIMEOUT);
		अवरोध;

	हाल NSSM_EVENT_PORT_OFFLINE:
		bfa_sm_set_state(ns, bfa_fcs_lport_ns_sm_offline);
		bfa_fcxp_discard(ns->fcxp);
		अवरोध;

	हाल  NSSM_EVENT_NS_QUERY:
		अवरोध;

	शेष:
		bfa_sm_fault(ns->port->fcs, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcs_lport_ns_sm_gid_ft_retry(काष्ठा bfa_fcs_lport_ns_s *ns,
				क्रमागत vport_ns_event event)
अणु
	bfa_trc(ns->port->fcs, ns->port->port_cfg.pwwn);
	bfa_trc(ns->port->fcs, event);

	चयन (event) अणु
	हाल NSSM_EVENT_TIMEOUT:
		bfa_sm_set_state(ns, bfa_fcs_lport_ns_sm_sending_gid_ft);
		bfa_fcs_lport_ns_send_gid_ft(ns, शून्य);
		अवरोध;

	हाल NSSM_EVENT_PORT_OFFLINE:
		bfa_sm_set_state(ns, bfa_fcs_lport_ns_sm_offline);
		bfa_समयr_stop(&ns->समयr);
		अवरोध;

	शेष:
		bfa_sm_fault(ns->port->fcs, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcs_lport_ns_sm_online(काष्ठा bfa_fcs_lport_ns_s *ns,
			क्रमागत vport_ns_event event)
अणु
	bfa_trc(ns->port->fcs, ns->port->port_cfg.pwwn);
	bfa_trc(ns->port->fcs, event);

	चयन (event) अणु
	हाल NSSM_EVENT_PORT_OFFLINE:
		bfa_sm_set_state(ns, bfa_fcs_lport_ns_sm_offline);
		अवरोध;

	हाल NSSM_EVENT_NS_QUERY:
		/*
		 * If the port role is Initiator Mode issue NS query.
		 * If it is Target Mode, skip this and go to online.
		 */
		अगर (BFA_FCS_VPORT_IS_INITIATOR_MODE(ns->port)) अणु
			bfa_sm_set_state(ns,
				bfa_fcs_lport_ns_sm_sending_gid_ft);
			bfa_fcs_lport_ns_send_gid_ft(ns, शून्य);
		पूर्ण
		अवरोध;

	शेष:
		bfa_sm_fault(ns->port->fcs, event);
	पूर्ण
पूर्ण



/*
 *  ns_pvt Nameserver local functions
 */

अटल व्योम
bfa_fcs_lport_ns_send_plogi(व्योम *ns_cbarg, काष्ठा bfa_fcxp_s *fcxp_alloced)
अणु
	काष्ठा bfa_fcs_lport_ns_s *ns = ns_cbarg;
	काष्ठा bfa_fcs_lport_s *port = ns->port;
	काष्ठा fchs_s fchs;
	पूर्णांक             len;
	काष्ठा bfa_fcxp_s *fcxp;

	bfa_trc(port->fcs, port->pid);

	fcxp = fcxp_alloced ? fcxp_alloced :
	       bfa_fcs_fcxp_alloc(port->fcs, BFA_TRUE);
	अगर (!fcxp) अणु
		port->stats.ns_plogi_alloc_रुको++;
		bfa_fcs_fcxp_alloc_रुको(port->fcs->bfa, &ns->fcxp_wqe,
				bfa_fcs_lport_ns_send_plogi, ns, BFA_TRUE);
		वापस;
	पूर्ण
	ns->fcxp = fcxp;

	len = fc_plogi_build(&fchs, bfa_fcxp_get_reqbuf(fcxp),
			     bfa_hton3b(FC_NAME_SERVER),
			     bfa_fcs_lport_get_fcid(port), 0,
			     port->port_cfg.pwwn, port->port_cfg.nwwn,
			     bfa_fcport_get_maxfrsize(port->fcs->bfa),
			     bfa_fcport_get_rx_bbcredit(port->fcs->bfa));

	bfa_fcxp_send(fcxp, शून्य, port->fabric->vf_id, port->lp_tag, BFA_FALSE,
			  FC_CLASS_3, len, &fchs,
			  bfa_fcs_lport_ns_plogi_response, (व्योम *)ns,
			  FC_MAX_PDUSZ, FC_ELS_TOV);
	port->stats.ns_plogi_sent++;

	bfa_sm_send_event(ns, NSSM_EVENT_PLOGI_SENT);
पूर्ण

अटल व्योम
bfa_fcs_lport_ns_plogi_response(व्योम *fcsarg, काष्ठा bfa_fcxp_s *fcxp,
			व्योम *cbarg, bfa_status_t req_status, u32 rsp_len,
		       u32 resid_len, काष्ठा fchs_s *rsp_fchs)
अणु
	काष्ठा bfa_fcs_lport_ns_s *ns = (काष्ठा bfa_fcs_lport_ns_s *) cbarg;
	काष्ठा bfa_fcs_lport_s *port = ns->port;
	/* काष्ठा fc_logi_s *plogi_resp; */
	काष्ठा fc_els_cmd_s *els_cmd;
	काष्ठा fc_ls_rjt_s *ls_rjt;

	bfa_trc(port->fcs, req_status);
	bfa_trc(port->fcs, port->port_cfg.pwwn);

	/*
	 * Sanity Checks
	 */
	अगर (req_status != BFA_STATUS_OK) अणु
		bfa_trc(port->fcs, req_status);
		port->stats.ns_plogi_rsp_err++;
		bfa_sm_send_event(ns, NSSM_EVENT_RSP_ERROR);
		वापस;
	पूर्ण

	els_cmd = (काष्ठा fc_els_cmd_s *) BFA_FCXP_RSP_PLD(fcxp);

	चयन (els_cmd->els_code) अणु

	हाल FC_ELS_ACC:
		अगर (rsp_len < माप(काष्ठा fc_logi_s)) अणु
			bfa_trc(port->fcs, rsp_len);
			port->stats.ns_plogi_acc_err++;
			bfa_sm_send_event(ns, NSSM_EVENT_RSP_ERROR);
			अवरोध;
		पूर्ण
		port->stats.ns_plogi_accepts++;
		bfa_sm_send_event(ns, NSSM_EVENT_RSP_OK);
		अवरोध;

	हाल FC_ELS_LS_RJT:
		ls_rjt = (काष्ठा fc_ls_rjt_s *) BFA_FCXP_RSP_PLD(fcxp);

		bfa_trc(port->fcs, ls_rjt->reason_code);
		bfa_trc(port->fcs, ls_rjt->reason_code_expl);

		port->stats.ns_rejects++;

		bfa_sm_send_event(ns, NSSM_EVENT_RSP_ERROR);
		अवरोध;

	शेष:
		port->stats.ns_plogi_unknown_rsp++;
		bfa_trc(port->fcs, els_cmd->els_code);
		bfa_sm_send_event(ns, NSSM_EVENT_RSP_ERROR);
	पूर्ण
पूर्ण

/*
 * Register node name क्रम port_id
 */
अटल व्योम
bfa_fcs_lport_ns_send_rnn_id(व्योम *ns_cbarg, काष्ठा bfa_fcxp_s *fcxp_alloced)
अणु
	काष्ठा bfa_fcs_lport_ns_s *ns = ns_cbarg;
	काष्ठा bfa_fcs_lport_s *port = ns->port;
	काष्ठा fchs_s  fchs;
	पूर्णांक	len;
	काष्ठा bfa_fcxp_s *fcxp;

	bfa_trc(port->fcs, port->port_cfg.pwwn);

	fcxp = fcxp_alloced ? fcxp_alloced :
			bfa_fcs_fcxp_alloc(port->fcs, BFA_TRUE);
	अगर (!fcxp) अणु
		port->stats.ns_rnnid_alloc_रुको++;
		bfa_fcs_fcxp_alloc_रुको(port->fcs->bfa, &ns->fcxp_wqe,
				bfa_fcs_lport_ns_send_rnn_id, ns, BFA_TRUE);
		वापस;
	पूर्ण

	ns->fcxp = fcxp;

	len = fc_rnnid_build(&fchs, bfa_fcxp_get_reqbuf(fcxp),
				bfa_fcs_lport_get_fcid(port),
				bfa_fcs_lport_get_fcid(port),
				bfa_fcs_lport_get_nwwn(port));

	bfa_fcxp_send(fcxp, शून्य, port->fabric->vf_id, port->lp_tag, BFA_FALSE,
			  FC_CLASS_3, len, &fchs,
			  bfa_fcs_lport_ns_rnn_id_response, (व्योम *)ns,
			  FC_MAX_PDUSZ, FC_FCCT_TOV);

	port->stats.ns_rnnid_sent++;
	bfa_sm_send_event(ns, NSSM_EVENT_RNNID_SENT);
पूर्ण

अटल व्योम
bfa_fcs_lport_ns_rnn_id_response(व्योम *fcsarg, काष्ठा bfa_fcxp_s *fcxp,
				व्योम *cbarg, bfa_status_t req_status,
				u32 rsp_len, u32 resid_len,
				काष्ठा fchs_s *rsp_fchs)

अणु
	काष्ठा bfa_fcs_lport_ns_s *ns = (काष्ठा bfa_fcs_lport_ns_s *) cbarg;
	काष्ठा bfa_fcs_lport_s *port = ns->port;
	काष्ठा ct_hdr_s	*cthdr = शून्य;

	bfa_trc(port->fcs, port->port_cfg.pwwn);

	/*
	 * Sanity Checks
	 */
	अगर (req_status != BFA_STATUS_OK) अणु
		bfa_trc(port->fcs, req_status);
		port->stats.ns_rnnid_rsp_err++;
		bfa_sm_send_event(ns, NSSM_EVENT_RSP_ERROR);
		वापस;
	पूर्ण

	cthdr = (काष्ठा ct_hdr_s *) BFA_FCXP_RSP_PLD(fcxp);
	cthdr->cmd_rsp_code = be16_to_cpu(cthdr->cmd_rsp_code);

	अगर (cthdr->cmd_rsp_code == CT_RSP_ACCEPT) अणु
		port->stats.ns_rnnid_accepts++;
		bfa_sm_send_event(ns, NSSM_EVENT_RSP_OK);
		वापस;
	पूर्ण

	port->stats.ns_rnnid_rejects++;
	bfa_trc(port->fcs, cthdr->reason_code);
	bfa_trc(port->fcs, cthdr->exp_code);
	bfa_sm_send_event(ns, NSSM_EVENT_RSP_ERROR);
पूर्ण

/*
 * Register the symbolic node name क्रम a given node name.
 */
अटल व्योम
bfa_fcs_lport_ns_send_rsnn_nn(व्योम *ns_cbarg, काष्ठा bfa_fcxp_s *fcxp_alloced)
अणु
	काष्ठा bfa_fcs_lport_ns_s *ns = ns_cbarg;
	काष्ठा bfa_fcs_lport_s *port = ns->port;
	काष्ठा fchs_s  fchs;
	पूर्णांक     len;
	काष्ठा bfa_fcxp_s *fcxp;
	u8 *nsymbl;

	bfa_trc(port->fcs, port->port_cfg.pwwn);

	fcxp = fcxp_alloced ? fcxp_alloced :
			bfa_fcs_fcxp_alloc(port->fcs, BFA_TRUE);
	अगर (!fcxp) अणु
		port->stats.ns_rsnn_nn_alloc_रुको++;
		bfa_fcs_fcxp_alloc_रुको(port->fcs->bfa, &ns->fcxp_wqe,
				bfa_fcs_lport_ns_send_rsnn_nn, ns, BFA_TRUE);
		वापस;
	पूर्ण
	ns->fcxp = fcxp;

	nsymbl = (u8 *) &(bfa_fcs_lport_get_nsym_name(
					bfa_fcs_get_base_port(port->fcs)));

	len = fc_rsnn_nn_build(&fchs, bfa_fcxp_get_reqbuf(fcxp),
				bfa_fcs_lport_get_fcid(port),
				bfa_fcs_lport_get_nwwn(port), nsymbl);

	bfa_fcxp_send(fcxp, शून्य, port->fabric->vf_id, port->lp_tag, BFA_FALSE,
			  FC_CLASS_3, len, &fchs,
			  bfa_fcs_lport_ns_rsnn_nn_response, (व्योम *)ns,
			  FC_MAX_PDUSZ, FC_FCCT_TOV);

	port->stats.ns_rsnn_nn_sent++;

	bfa_sm_send_event(ns, NSSM_EVENT_RSNN_NN_SENT);
पूर्ण

अटल व्योम
bfa_fcs_lport_ns_rsnn_nn_response(व्योम *fcsarg, काष्ठा bfa_fcxp_s *fcxp,
				व्योम *cbarg, bfa_status_t req_status,
				u32 rsp_len, u32 resid_len,
				काष्ठा fchs_s *rsp_fchs)
अणु
	काष्ठा bfa_fcs_lport_ns_s *ns = (काष्ठा bfa_fcs_lport_ns_s *) cbarg;
	काष्ठा bfa_fcs_lport_s *port = ns->port;
	काष्ठा ct_hdr_s	*cthdr = शून्य;

	bfa_trc(port->fcs, port->port_cfg.pwwn);

	/*
	 * Sanity Checks
	 */
	अगर (req_status != BFA_STATUS_OK) अणु
		bfa_trc(port->fcs, req_status);
		port->stats.ns_rsnn_nn_rsp_err++;
		bfa_sm_send_event(ns, NSSM_EVENT_RSP_ERROR);
		वापस;
	पूर्ण

	cthdr = (काष्ठा ct_hdr_s *) BFA_FCXP_RSP_PLD(fcxp);
	cthdr->cmd_rsp_code = be16_to_cpu(cthdr->cmd_rsp_code);

	अगर (cthdr->cmd_rsp_code == CT_RSP_ACCEPT) अणु
		port->stats.ns_rsnn_nn_accepts++;
		bfa_sm_send_event(ns, NSSM_EVENT_RSP_OK);
		वापस;
	पूर्ण

	port->stats.ns_rsnn_nn_rejects++;
	bfa_trc(port->fcs, cthdr->reason_code);
	bfa_trc(port->fcs, cthdr->exp_code);
	bfa_sm_send_event(ns, NSSM_EVENT_RSP_ERROR);
पूर्ण

/*
 * Register the symbolic port name.
 */
अटल व्योम
bfa_fcs_lport_ns_send_rspn_id(व्योम *ns_cbarg, काष्ठा bfa_fcxp_s *fcxp_alloced)
अणु
	काष्ठा bfa_fcs_lport_ns_s *ns = ns_cbarg;
	काष्ठा bfa_fcs_lport_s *port = ns->port;
	काष्ठा fchs_s fchs;
	पूर्णांक             len;
	काष्ठा bfa_fcxp_s *fcxp;
	u8         symbl[256];
	u8         *psymbl = &symbl[0];

	स_रखो(symbl, 0, माप(symbl));

	bfa_trc(port->fcs, port->port_cfg.pwwn);

	fcxp = fcxp_alloced ? fcxp_alloced :
	       bfa_fcs_fcxp_alloc(port->fcs, BFA_TRUE);
	अगर (!fcxp) अणु
		port->stats.ns_rspnid_alloc_रुको++;
		bfa_fcs_fcxp_alloc_रुको(port->fcs->bfa, &ns->fcxp_wqe,
				bfa_fcs_lport_ns_send_rspn_id, ns, BFA_TRUE);
		वापस;
	पूर्ण
	ns->fcxp = fcxp;

	/*
	 * क्रम V-Port, क्रमm a Port Symbolic Name
	 */
	अगर (port->vport) अणु
		/*
		 * For Vports, we append the vport's port symbolic name
		 * to that of the base port.
		 */

		strlcpy(symbl,
			(अक्षर *)&(bfa_fcs_lport_get_psym_name
			 (bfa_fcs_get_base_port(port->fcs))),
			माप(symbl));

		strlcat(symbl, (अक्षर *)&(bfa_fcs_lport_get_psym_name(port)),
			माप(symbl));
	पूर्ण अन्यथा अणु
		psymbl = (u8 *) &(bfa_fcs_lport_get_psym_name(port));
	पूर्ण

	len = fc_rspnid_build(&fchs, bfa_fcxp_get_reqbuf(fcxp),
			      bfa_fcs_lport_get_fcid(port), 0, psymbl);

	bfa_fcxp_send(fcxp, शून्य, port->fabric->vf_id, port->lp_tag, BFA_FALSE,
			  FC_CLASS_3, len, &fchs,
			  bfa_fcs_lport_ns_rspn_id_response, (व्योम *)ns,
			  FC_MAX_PDUSZ, FC_FCCT_TOV);

	port->stats.ns_rspnid_sent++;

	bfa_sm_send_event(ns, NSSM_EVENT_RSPNID_SENT);
पूर्ण

अटल व्योम
bfa_fcs_lport_ns_rspn_id_response(व्योम *fcsarg, काष्ठा bfa_fcxp_s *fcxp,
				 व्योम *cbarg, bfa_status_t req_status,
				 u32 rsp_len, u32 resid_len,
				 काष्ठा fchs_s *rsp_fchs)
अणु
	काष्ठा bfa_fcs_lport_ns_s *ns = (काष्ठा bfa_fcs_lport_ns_s *) cbarg;
	काष्ठा bfa_fcs_lport_s *port = ns->port;
	काष्ठा ct_hdr_s *cthdr = शून्य;

	bfa_trc(port->fcs, port->port_cfg.pwwn);

	/*
	 * Sanity Checks
	 */
	अगर (req_status != BFA_STATUS_OK) अणु
		bfa_trc(port->fcs, req_status);
		port->stats.ns_rspnid_rsp_err++;
		bfa_sm_send_event(ns, NSSM_EVENT_RSP_ERROR);
		वापस;
	पूर्ण

	cthdr = (काष्ठा ct_hdr_s *) BFA_FCXP_RSP_PLD(fcxp);
	cthdr->cmd_rsp_code = be16_to_cpu(cthdr->cmd_rsp_code);

	अगर (cthdr->cmd_rsp_code == CT_RSP_ACCEPT) अणु
		port->stats.ns_rspnid_accepts++;
		bfa_sm_send_event(ns, NSSM_EVENT_RSP_OK);
		वापस;
	पूर्ण

	port->stats.ns_rspnid_rejects++;
	bfa_trc(port->fcs, cthdr->reason_code);
	bfa_trc(port->fcs, cthdr->exp_code);
	bfa_sm_send_event(ns, NSSM_EVENT_RSP_ERROR);
पूर्ण

/*
 * Register FC4-Types
 */
अटल व्योम
bfa_fcs_lport_ns_send_rft_id(व्योम *ns_cbarg, काष्ठा bfa_fcxp_s *fcxp_alloced)
अणु
	काष्ठा bfa_fcs_lport_ns_s *ns = ns_cbarg;
	काष्ठा bfa_fcs_lport_s *port = ns->port;
	काष्ठा fchs_s fchs;
	पूर्णांक             len;
	काष्ठा bfa_fcxp_s *fcxp;

	bfa_trc(port->fcs, port->port_cfg.pwwn);

	fcxp = fcxp_alloced ? fcxp_alloced :
	       bfa_fcs_fcxp_alloc(port->fcs, BFA_TRUE);
	अगर (!fcxp) अणु
		port->stats.ns_rftid_alloc_रुको++;
		bfa_fcs_fcxp_alloc_रुको(port->fcs->bfa, &ns->fcxp_wqe,
				bfa_fcs_lport_ns_send_rft_id, ns, BFA_TRUE);
		वापस;
	पूर्ण
	ns->fcxp = fcxp;

	len = fc_rftid_build(&fchs, bfa_fcxp_get_reqbuf(fcxp),
		     bfa_fcs_lport_get_fcid(port), 0, port->port_cfg.roles);

	bfa_fcxp_send(fcxp, शून्य, port->fabric->vf_id, port->lp_tag, BFA_FALSE,
			  FC_CLASS_3, len, &fchs,
			  bfa_fcs_lport_ns_rft_id_response, (व्योम *)ns,
			  FC_MAX_PDUSZ, FC_FCCT_TOV);

	port->stats.ns_rftid_sent++;
	bfa_sm_send_event(ns, NSSM_EVENT_RFTID_SENT);
पूर्ण

अटल व्योम
bfa_fcs_lport_ns_rft_id_response(व्योम *fcsarg, काष्ठा bfa_fcxp_s *fcxp,
				व्योम *cbarg, bfa_status_t req_status,
				u32 rsp_len, u32 resid_len,
				काष्ठा fchs_s *rsp_fchs)
अणु
	काष्ठा bfa_fcs_lport_ns_s *ns = (काष्ठा bfa_fcs_lport_ns_s *) cbarg;
	काष्ठा bfa_fcs_lport_s *port = ns->port;
	काष्ठा ct_hdr_s *cthdr = शून्य;

	bfa_trc(port->fcs, port->port_cfg.pwwn);

	/*
	 * Sanity Checks
	 */
	अगर (req_status != BFA_STATUS_OK) अणु
		bfa_trc(port->fcs, req_status);
		port->stats.ns_rftid_rsp_err++;
		bfa_sm_send_event(ns, NSSM_EVENT_RSP_ERROR);
		वापस;
	पूर्ण

	cthdr = (काष्ठा ct_hdr_s *) BFA_FCXP_RSP_PLD(fcxp);
	cthdr->cmd_rsp_code = be16_to_cpu(cthdr->cmd_rsp_code);

	अगर (cthdr->cmd_rsp_code == CT_RSP_ACCEPT) अणु
		port->stats.ns_rftid_accepts++;
		bfa_sm_send_event(ns, NSSM_EVENT_RSP_OK);
		वापस;
	पूर्ण

	port->stats.ns_rftid_rejects++;
	bfa_trc(port->fcs, cthdr->reason_code);
	bfa_trc(port->fcs, cthdr->exp_code);
	bfa_sm_send_event(ns, NSSM_EVENT_RSP_ERROR);
पूर्ण

/*
 * Register FC4-Features : Should be करोne after RFT_ID
 */
अटल व्योम
bfa_fcs_lport_ns_send_rff_id(व्योम *ns_cbarg, काष्ठा bfa_fcxp_s *fcxp_alloced)
अणु
	काष्ठा bfa_fcs_lport_ns_s *ns = ns_cbarg;
	काष्ठा bfa_fcs_lport_s *port = ns->port;
	काष्ठा fchs_s fchs;
	पूर्णांक             len;
	काष्ठा bfa_fcxp_s *fcxp;
	u8			fc4_ftrs = 0;

	bfa_trc(port->fcs, port->port_cfg.pwwn);

	fcxp = fcxp_alloced ? fcxp_alloced :
	       bfa_fcs_fcxp_alloc(port->fcs, BFA_TRUE);
	अगर (!fcxp) अणु
		port->stats.ns_rffid_alloc_रुको++;
		bfa_fcs_fcxp_alloc_रुको(port->fcs->bfa, &ns->fcxp_wqe,
				bfa_fcs_lport_ns_send_rff_id, ns, BFA_TRUE);
		वापस;
	पूर्ण
	ns->fcxp = fcxp;

	अगर (BFA_FCS_VPORT_IS_INITIATOR_MODE(ns->port))
		fc4_ftrs = FC_GS_FCP_FC4_FEATURE_INITIATOR;

	len = fc_rffid_build(&fchs, bfa_fcxp_get_reqbuf(fcxp),
			     bfa_fcs_lport_get_fcid(port), 0,
				 FC_TYPE_FCP, fc4_ftrs);

	bfa_fcxp_send(fcxp, शून्य, port->fabric->vf_id, port->lp_tag, BFA_FALSE,
			  FC_CLASS_3, len, &fchs,
			  bfa_fcs_lport_ns_rff_id_response, (व्योम *)ns,
			  FC_MAX_PDUSZ, FC_FCCT_TOV);

	port->stats.ns_rffid_sent++;
	bfa_sm_send_event(ns, NSSM_EVENT_RFFID_SENT);
पूर्ण

अटल व्योम
bfa_fcs_lport_ns_rff_id_response(व्योम *fcsarg, काष्ठा bfa_fcxp_s *fcxp,
				व्योम *cbarg, bfa_status_t req_status,
				u32 rsp_len, u32 resid_len,
				काष्ठा fchs_s *rsp_fchs)
अणु
	काष्ठा bfa_fcs_lport_ns_s *ns = (काष्ठा bfa_fcs_lport_ns_s *) cbarg;
	काष्ठा bfa_fcs_lport_s *port = ns->port;
	काष्ठा ct_hdr_s *cthdr = शून्य;

	bfa_trc(port->fcs, port->port_cfg.pwwn);

	/*
	 * Sanity Checks
	 */
	अगर (req_status != BFA_STATUS_OK) अणु
		bfa_trc(port->fcs, req_status);
		port->stats.ns_rffid_rsp_err++;
		bfa_sm_send_event(ns, NSSM_EVENT_RSP_ERROR);
		वापस;
	पूर्ण

	cthdr = (काष्ठा ct_hdr_s *) BFA_FCXP_RSP_PLD(fcxp);
	cthdr->cmd_rsp_code = be16_to_cpu(cthdr->cmd_rsp_code);

	अगर (cthdr->cmd_rsp_code == CT_RSP_ACCEPT) अणु
		port->stats.ns_rffid_accepts++;
		bfa_sm_send_event(ns, NSSM_EVENT_RSP_OK);
		वापस;
	पूर्ण

	port->stats.ns_rffid_rejects++;
	bfa_trc(port->fcs, cthdr->reason_code);
	bfa_trc(port->fcs, cthdr->exp_code);

	अगर (cthdr->reason_code == CT_RSN_NOT_SUPP) अणु
		/* अगर this command is not supported, we करोn't retry */
		bfa_sm_send_event(ns, NSSM_EVENT_RSP_OK);
	पूर्ण अन्यथा
		bfa_sm_send_event(ns, NSSM_EVENT_RSP_ERROR);
पूर्ण
/*
 * Query Fabric क्रम FC4-Types Devices.
 *
* TBD : Need to use a local (FCS निजी) response buffer, since the response
 * can be larger than 2K.
 */
अटल व्योम
bfa_fcs_lport_ns_send_gid_ft(व्योम *ns_cbarg, काष्ठा bfa_fcxp_s *fcxp_alloced)
अणु
	काष्ठा bfa_fcs_lport_ns_s *ns = ns_cbarg;
	काष्ठा bfa_fcs_lport_s *port = ns->port;
	काष्ठा fchs_s fchs;
	पूर्णांक             len;
	काष्ठा bfa_fcxp_s *fcxp;

	bfa_trc(port->fcs, port->pid);

	fcxp = fcxp_alloced ? fcxp_alloced :
	       bfa_fcs_fcxp_alloc(port->fcs, BFA_TRUE);
	अगर (!fcxp) अणु
		port->stats.ns_gidft_alloc_रुको++;
		bfa_fcs_fcxp_alloc_रुको(port->fcs->bfa, &ns->fcxp_wqe,
				bfa_fcs_lport_ns_send_gid_ft, ns, BFA_TRUE);
		वापस;
	पूर्ण
	ns->fcxp = fcxp;

	/*
	 * This query is only initiated क्रम FCP initiator mode.
	 */
	len = fc_gid_ft_build(&fchs, bfa_fcxp_get_reqbuf(fcxp),
			      ns->port->pid, FC_TYPE_FCP);

	bfa_fcxp_send(fcxp, शून्य, port->fabric->vf_id, port->lp_tag, BFA_FALSE,
			  FC_CLASS_3, len, &fchs,
			  bfa_fcs_lport_ns_gid_ft_response, (व्योम *)ns,
			  bfa_fcxp_get_maxrsp(port->fcs->bfa), FC_FCCT_TOV);

	port->stats.ns_gidft_sent++;

	bfa_sm_send_event(ns, NSSM_EVENT_GIDFT_SENT);
पूर्ण

अटल व्योम
bfa_fcs_lport_ns_gid_ft_response(व्योम *fcsarg, काष्ठा bfa_fcxp_s *fcxp,
				व्योम *cbarg, bfa_status_t req_status,
				u32 rsp_len, u32 resid_len,
				काष्ठा fchs_s *rsp_fchs)
अणु
	काष्ठा bfa_fcs_lport_ns_s *ns = (काष्ठा bfa_fcs_lport_ns_s *) cbarg;
	काष्ठा bfa_fcs_lport_s *port = ns->port;
	काष्ठा ct_hdr_s *cthdr = शून्य;
	u32        n_pids;

	bfa_trc(port->fcs, port->port_cfg.pwwn);

	/*
	 * Sanity Checks
	 */
	अगर (req_status != BFA_STATUS_OK) अणु
		bfa_trc(port->fcs, req_status);
		port->stats.ns_gidft_rsp_err++;
		bfa_sm_send_event(ns, NSSM_EVENT_RSP_ERROR);
		वापस;
	पूर्ण

	अगर (resid_len != 0) अणु
		/*
		 * TBD : we will need to allocate a larger buffer & retry the
		 * command
		 */
		bfa_trc(port->fcs, rsp_len);
		bfa_trc(port->fcs, resid_len);
		वापस;
	पूर्ण

	cthdr = (काष्ठा ct_hdr_s *) BFA_FCXP_RSP_PLD(fcxp);
	cthdr->cmd_rsp_code = be16_to_cpu(cthdr->cmd_rsp_code);

	चयन (cthdr->cmd_rsp_code) अणु

	हाल CT_RSP_ACCEPT:

		port->stats.ns_gidft_accepts++;
		n_pids = (fc_get_ctresp_pyld_len(rsp_len) / माप(u32));
		bfa_trc(port->fcs, n_pids);
		bfa_fcs_lport_ns_process_gidft_pids(port,
						   (u32 *) (cthdr + 1),
						   n_pids);
		bfa_sm_send_event(ns, NSSM_EVENT_RSP_OK);
		अवरोध;

	हाल CT_RSP_REJECT:

		/*
		 * Check the reason code  & explanation.
		 * There may not have been any FC4 devices in the fabric
		 */
		port->stats.ns_gidft_rejects++;
		bfa_trc(port->fcs, cthdr->reason_code);
		bfa_trc(port->fcs, cthdr->exp_code);

		अगर ((cthdr->reason_code == CT_RSN_UNABLE_TO_PERF)
		    && (cthdr->exp_code == CT_NS_EXP_FT_NOT_REG)) अणु

			bfa_sm_send_event(ns, NSSM_EVENT_RSP_OK);
		पूर्ण अन्यथा अणु
			/*
			 * क्रम all other errors, retry
			 */
			bfa_sm_send_event(ns, NSSM_EVENT_RSP_ERROR);
		पूर्ण
		अवरोध;

	शेष:
		port->stats.ns_gidft_unknown_rsp++;
		bfa_trc(port->fcs, cthdr->cmd_rsp_code);
		bfa_sm_send_event(ns, NSSM_EVENT_RSP_ERROR);
	पूर्ण
पूर्ण

/*
 *     This routine will be called by bfa_समयr on समयr समयouts.
 *
 *	param[in]	port - poपूर्णांकer to bfa_fcs_lport_t.
 *
 *	वापस
 *		व्योम
 *
 *	Special Considerations:
 *
 *	note
 */
अटल व्योम
bfa_fcs_lport_ns_समयout(व्योम *arg)
अणु
	काष्ठा bfa_fcs_lport_ns_s *ns = (काष्ठा bfa_fcs_lport_ns_s *) arg;

	ns->port->stats.ns_समयouts++;
	bfa_sm_send_event(ns, NSSM_EVENT_TIMEOUT);
पूर्ण

/*
 * Process the PID list in GID_FT response
 */
अटल व्योम
bfa_fcs_lport_ns_process_gidft_pids(काष्ठा bfa_fcs_lport_s *port, u32 *pid_buf,
				   u32 n_pids)
अणु
	काष्ठा fcgs_gidft_resp_s *gidft_entry;
	काष्ठा bfa_fcs_rport_s *rport;
	u32        ii;
	काष्ठा bfa_fcs_fabric_s *fabric = port->fabric;
	काष्ठा bfa_fcs_vport_s *vport;
	काष्ठा list_head *qe;
	u8 found = 0;

	क्रम (ii = 0; ii < n_pids; ii++) अणु
		gidft_entry = (काष्ठा fcgs_gidft_resp_s *) &pid_buf[ii];

		अगर (gidft_entry->pid == port->pid)
			जारी;

		/*
		 * Ignore PID अगर it is of base port
		 * (Aव्योम vports discovering base port as remote port)
		 */
		अगर (gidft_entry->pid == fabric->bport.pid)
			जारी;

		/*
		 * Ignore PID अगर it is of vport created on the same base port
		 * (Aव्योम vport discovering every other vport created on the
		 * same port as remote port)
		 */
		list_क्रम_each(qe, &fabric->vport_q) अणु
			vport = (काष्ठा bfa_fcs_vport_s *) qe;
			अगर (vport->lport.pid == gidft_entry->pid)
				found = 1;
		पूर्ण

		अगर (found) अणु
			found = 0;
			जारी;
		पूर्ण

		/*
		 * Check अगर this rport alपढ़ोy exists
		 */
		rport = bfa_fcs_lport_get_rport_by_pid(port, gidft_entry->pid);
		अगर (rport == शून्य) अणु
			/*
			 * this is a new device. create rport
			 */
			rport = bfa_fcs_rport_create(port, gidft_entry->pid);
		पूर्ण अन्यथा अणु
			/*
			 * this rport alपढ़ोy exists
			 */
			bfa_fcs_rport_scn(rport);
		पूर्ण

		bfa_trc(port->fcs, gidft_entry->pid);

		/*
		 * अगर the last entry bit is set, bail out.
		 */
		अगर (gidft_entry->last)
			वापस;
	पूर्ण
पूर्ण

/*
 *  fcs_ns_खुला FCS nameserver खुला पूर्णांकerfaces
 */

/*
 * Functions called by port/fab.
 * These will send relevant Events to the ns state machine.
 */
व्योम
bfa_fcs_lport_ns_init(काष्ठा bfa_fcs_lport_s *port)
अणु
	काष्ठा bfa_fcs_lport_ns_s *ns = BFA_FCS_GET_NS_FROM_PORT(port);

	ns->port = port;
	bfa_sm_set_state(ns, bfa_fcs_lport_ns_sm_offline);
पूर्ण

व्योम
bfa_fcs_lport_ns_offline(काष्ठा bfa_fcs_lport_s *port)
अणु
	काष्ठा bfa_fcs_lport_ns_s *ns = BFA_FCS_GET_NS_FROM_PORT(port);

	ns->port = port;
	bfa_sm_send_event(ns, NSSM_EVENT_PORT_OFFLINE);
पूर्ण

व्योम
bfa_fcs_lport_ns_online(काष्ठा bfa_fcs_lport_s *port)
अणु
	काष्ठा bfa_fcs_lport_ns_s *ns = BFA_FCS_GET_NS_FROM_PORT(port);

	ns->port = port;
	bfa_sm_send_event(ns, NSSM_EVENT_PORT_ONLINE);
पूर्ण

व्योम
bfa_fcs_lport_ns_query(काष्ठा bfa_fcs_lport_s *port)
अणु
	काष्ठा bfa_fcs_lport_ns_s *ns = BFA_FCS_GET_NS_FROM_PORT(port);

	bfa_trc(port->fcs, port->pid);
	अगर (bfa_sm_cmp_state(ns, bfa_fcs_lport_ns_sm_online))
		bfa_sm_send_event(ns, NSSM_EVENT_NS_QUERY);
पूर्ण

अटल व्योम
bfa_fcs_lport_ns_boot_target_disc(bfa_fcs_lport_t *port)
अणु

	काष्ठा bfa_fcs_rport_s *rport;
	u8 nwwns;
	wwn_t  wwns[BFA_PREBOOT_BOOTLUN_MAX];
	पूर्णांक ii;

	bfa_iocfc_get_bootwwns(port->fcs->bfa, &nwwns, wwns);

	क्रम (ii = 0 ; ii < nwwns; ++ii) अणु
		rport = bfa_fcs_rport_create_by_wwn(port, wwns[ii]);
		WARN_ON(!rport);
	पूर्ण
पूर्ण

व्योम
bfa_fcs_lport_ns_util_send_rspn_id(व्योम *cbarg, काष्ठा bfa_fcxp_s *fcxp_alloced)
अणु
	काष्ठा bfa_fcs_lport_ns_s *ns = cbarg;
	काष्ठा bfa_fcs_lport_s *port = ns->port;
	काष्ठा fchs_s fchs;
	काष्ठा bfa_fcxp_s *fcxp;
	u8 symbl[256];
	पूर्णांक len;

	/* Aव्योम sending RSPN in the following states. */
	अगर (bfa_sm_cmp_state(ns, bfa_fcs_lport_ns_sm_offline) ||
	    bfa_sm_cmp_state(ns, bfa_fcs_lport_ns_sm_plogi_sending) ||
	    bfa_sm_cmp_state(ns, bfa_fcs_lport_ns_sm_plogi) ||
	    bfa_sm_cmp_state(ns, bfa_fcs_lport_ns_sm_plogi_retry) ||
	    bfa_sm_cmp_state(ns, bfa_fcs_lport_ns_sm_rspn_id_retry))
		वापस;

	स_रखो(symbl, 0, माप(symbl));
	bfa_trc(port->fcs, port->port_cfg.pwwn);

	fcxp = fcxp_alloced ? fcxp_alloced :
	       bfa_fcs_fcxp_alloc(port->fcs, BFA_FALSE);
	अगर (!fcxp) अणु
		port->stats.ns_rspnid_alloc_रुको++;
		bfa_fcs_fcxp_alloc_रुको(port->fcs->bfa, &ns->fcxp_wqe,
			bfa_fcs_lport_ns_util_send_rspn_id, ns, BFA_FALSE);
		वापस;
	पूर्ण

	ns->fcxp = fcxp;

	अगर (port->vport) अणु
		/*
		 * For Vports, we append the vport's port symbolic name
		 * to that of the base port.
		 */
		strlcpy(symbl, (अक्षर *)&(bfa_fcs_lport_get_psym_name
			(bfa_fcs_get_base_port(port->fcs))),
			माप(symbl));

		strlcat(symbl,
			(अक्षर *)&(bfa_fcs_lport_get_psym_name(port)),
			माप(symbl));
	पूर्ण

	len = fc_rspnid_build(&fchs, bfa_fcxp_get_reqbuf(fcxp),
			      bfa_fcs_lport_get_fcid(port), 0, symbl);

	bfa_fcxp_send(fcxp, शून्य, port->fabric->vf_id, port->lp_tag, BFA_FALSE,
		      FC_CLASS_3, len, &fchs, शून्य, शून्य, FC_MAX_PDUSZ, 0);

	port->stats.ns_rspnid_sent++;
पूर्ण

/*
 * FCS SCN
 */

#घोषणा FC_QOS_RSCN_EVENT		0x0c
#घोषणा FC_FABRIC_NAME_RSCN_EVENT	0x0d

/*
 * क्रमward declarations
 */
अटल व्योम     bfa_fcs_lport_scn_send_scr(व्योम *scn_cbarg,
					  काष्ठा bfa_fcxp_s *fcxp_alloced);
अटल व्योम     bfa_fcs_lport_scn_scr_response(व्योम *fcsarg,
					      काष्ठा bfa_fcxp_s *fcxp,
					      व्योम *cbarg,
					      bfa_status_t req_status,
					      u32 rsp_len,
					      u32 resid_len,
					      काष्ठा fchs_s *rsp_fchs);
अटल व्योम     bfa_fcs_lport_scn_send_ls_acc(काष्ठा bfa_fcs_lport_s *port,
					     काष्ठा fchs_s *rx_fchs);
अटल व्योम     bfa_fcs_lport_scn_समयout(व्योम *arg);

/*
 *  fcs_scm_sm FCS SCN state machine
 */

/*
 * VPort SCN State Machine events
 */
क्रमागत port_scn_event अणु
	SCNSM_EVENT_PORT_ONLINE = 1,
	SCNSM_EVENT_PORT_OFFLINE = 2,
	SCNSM_EVENT_RSP_OK = 3,
	SCNSM_EVENT_RSP_ERROR = 4,
	SCNSM_EVENT_TIMEOUT = 5,
	SCNSM_EVENT_SCR_SENT = 6,
पूर्ण;

अटल व्योम     bfa_fcs_lport_scn_sm_offline(काष्ठा bfa_fcs_lport_scn_s *scn,
					    क्रमागत port_scn_event event);
अटल व्योम     bfa_fcs_lport_scn_sm_sending_scr(
					काष्ठा bfa_fcs_lport_scn_s *scn,
					क्रमागत port_scn_event event);
अटल व्योम     bfa_fcs_lport_scn_sm_scr(काष्ठा bfa_fcs_lport_scn_s *scn,
					क्रमागत port_scn_event event);
अटल व्योम     bfa_fcs_lport_scn_sm_scr_retry(काष्ठा bfa_fcs_lport_scn_s *scn,
					      क्रमागत port_scn_event event);
अटल व्योम     bfa_fcs_lport_scn_sm_online(काष्ठा bfa_fcs_lport_scn_s *scn,
					   क्रमागत port_scn_event event);

/*
 *	Starting state - aरुकोing link up.
 */
अटल व्योम
bfa_fcs_lport_scn_sm_offline(काष्ठा bfa_fcs_lport_scn_s *scn,
			क्रमागत port_scn_event event)
अणु
	चयन (event) अणु
	हाल SCNSM_EVENT_PORT_ONLINE:
		bfa_sm_set_state(scn, bfa_fcs_lport_scn_sm_sending_scr);
		bfa_fcs_lport_scn_send_scr(scn, शून्य);
		अवरोध;

	हाल SCNSM_EVENT_PORT_OFFLINE:
		अवरोध;

	शेष:
		bfa_sm_fault(scn->port->fcs, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcs_lport_scn_sm_sending_scr(काष्ठा bfa_fcs_lport_scn_s *scn,
				क्रमागत port_scn_event event)
अणु
	चयन (event) अणु
	हाल SCNSM_EVENT_SCR_SENT:
		bfa_sm_set_state(scn, bfa_fcs_lport_scn_sm_scr);
		अवरोध;

	हाल SCNSM_EVENT_PORT_OFFLINE:
		bfa_sm_set_state(scn, bfa_fcs_lport_scn_sm_offline);
		bfa_fcxp_walloc_cancel(scn->port->fcs->bfa, &scn->fcxp_wqe);
		अवरोध;

	शेष:
		bfa_sm_fault(scn->port->fcs, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcs_lport_scn_sm_scr(काष्ठा bfa_fcs_lport_scn_s *scn,
			क्रमागत port_scn_event event)
अणु
	काष्ठा bfa_fcs_lport_s *port = scn->port;

	चयन (event) अणु
	हाल SCNSM_EVENT_RSP_OK:
		bfa_sm_set_state(scn, bfa_fcs_lport_scn_sm_online);
		अवरोध;

	हाल SCNSM_EVENT_RSP_ERROR:
		bfa_sm_set_state(scn, bfa_fcs_lport_scn_sm_scr_retry);
		bfa_समयr_start(port->fcs->bfa, &scn->समयr,
				    bfa_fcs_lport_scn_समयout, scn,
				    BFA_FCS_RETRY_TIMEOUT);
		अवरोध;

	हाल SCNSM_EVENT_PORT_OFFLINE:
		bfa_sm_set_state(scn, bfa_fcs_lport_scn_sm_offline);
		bfa_fcxp_discard(scn->fcxp);
		अवरोध;

	शेष:
		bfa_sm_fault(port->fcs, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcs_lport_scn_sm_scr_retry(काष्ठा bfa_fcs_lport_scn_s *scn,
				क्रमागत port_scn_event event)
अणु
	चयन (event) अणु
	हाल SCNSM_EVENT_TIMEOUT:
		bfa_sm_set_state(scn, bfa_fcs_lport_scn_sm_sending_scr);
		bfa_fcs_lport_scn_send_scr(scn, शून्य);
		अवरोध;

	हाल SCNSM_EVENT_PORT_OFFLINE:
		bfa_sm_set_state(scn, bfa_fcs_lport_scn_sm_offline);
		bfa_समयr_stop(&scn->समयr);
		अवरोध;

	शेष:
		bfa_sm_fault(scn->port->fcs, event);
	पूर्ण
पूर्ण

अटल व्योम
bfa_fcs_lport_scn_sm_online(काष्ठा bfa_fcs_lport_scn_s *scn,
			क्रमागत port_scn_event event)
अणु
	चयन (event) अणु
	हाल SCNSM_EVENT_PORT_OFFLINE:
		bfa_sm_set_state(scn, bfa_fcs_lport_scn_sm_offline);
		अवरोध;

	शेष:
		bfa_sm_fault(scn->port->fcs, event);
	पूर्ण
पूर्ण



/*
 *  fcs_scn_निजी FCS SCN निजी functions
 */

/*
 * This routine will be called to send a SCR command.
 */
अटल व्योम
bfa_fcs_lport_scn_send_scr(व्योम *scn_cbarg, काष्ठा bfa_fcxp_s *fcxp_alloced)
अणु
	काष्ठा bfa_fcs_lport_scn_s *scn = scn_cbarg;
	काष्ठा bfa_fcs_lport_s *port = scn->port;
	काष्ठा fchs_s fchs;
	पूर्णांक             len;
	काष्ठा bfa_fcxp_s *fcxp;

	bfa_trc(port->fcs, port->pid);
	bfa_trc(port->fcs, port->port_cfg.pwwn);

	fcxp = fcxp_alloced ? fcxp_alloced :
	       bfa_fcs_fcxp_alloc(port->fcs, BFA_TRUE);
	अगर (!fcxp) अणु
		bfa_fcs_fcxp_alloc_रुको(port->fcs->bfa, &scn->fcxp_wqe,
				bfa_fcs_lport_scn_send_scr, scn, BFA_TRUE);
		वापस;
	पूर्ण
	scn->fcxp = fcxp;

	/* Handle VU registrations क्रम Base port only */
	अगर ((!port->vport) && bfa_ioc_get_fcmode(&port->fcs->bfa->ioc)) अणु
		len = fc_scr_build(&fchs, bfa_fcxp_get_reqbuf(fcxp),
				port->fabric->lps->brcd_चयन,
				port->pid, 0);
	पूर्ण अन्यथा अणु
	    len = fc_scr_build(&fchs, bfa_fcxp_get_reqbuf(fcxp),
				    BFA_FALSE,
				    port->pid, 0);
	पूर्ण

	bfa_fcxp_send(fcxp, शून्य, port->fabric->vf_id, port->lp_tag, BFA_FALSE,
			  FC_CLASS_3, len, &fchs,
			  bfa_fcs_lport_scn_scr_response,
			  (व्योम *)scn, FC_MAX_PDUSZ, FC_ELS_TOV);

	bfa_sm_send_event(scn, SCNSM_EVENT_SCR_SENT);
पूर्ण

अटल व्योम
bfa_fcs_lport_scn_scr_response(व्योम *fcsarg, काष्ठा bfa_fcxp_s *fcxp,
			व्योम *cbarg, bfa_status_t req_status, u32 rsp_len,
			      u32 resid_len, काष्ठा fchs_s *rsp_fchs)
अणु
	काष्ठा bfa_fcs_lport_scn_s *scn = (काष्ठा bfa_fcs_lport_scn_s *) cbarg;
	काष्ठा bfa_fcs_lport_s *port = scn->port;
	काष्ठा fc_els_cmd_s *els_cmd;
	काष्ठा fc_ls_rjt_s *ls_rjt;

	bfa_trc(port->fcs, port->port_cfg.pwwn);

	/*
	 * Sanity Checks
	 */
	अगर (req_status != BFA_STATUS_OK) अणु
		bfa_trc(port->fcs, req_status);
		bfa_sm_send_event(scn, SCNSM_EVENT_RSP_ERROR);
		वापस;
	पूर्ण

	els_cmd = (काष्ठा fc_els_cmd_s *) BFA_FCXP_RSP_PLD(fcxp);

	चयन (els_cmd->els_code) अणु

	हाल FC_ELS_ACC:
		bfa_sm_send_event(scn, SCNSM_EVENT_RSP_OK);
		अवरोध;

	हाल FC_ELS_LS_RJT:

		ls_rjt = (काष्ठा fc_ls_rjt_s *) BFA_FCXP_RSP_PLD(fcxp);

		bfa_trc(port->fcs, ls_rjt->reason_code);
		bfa_trc(port->fcs, ls_rjt->reason_code_expl);

		bfa_sm_send_event(scn, SCNSM_EVENT_RSP_ERROR);
		अवरोध;

	शेष:
		bfa_sm_send_event(scn, SCNSM_EVENT_RSP_ERROR);
	पूर्ण
पूर्ण

/*
 * Send a LS Accept
 */
अटल व्योम
bfa_fcs_lport_scn_send_ls_acc(काष्ठा bfa_fcs_lport_s *port,
				काष्ठा fchs_s *rx_fchs)
अणु
	काष्ठा fchs_s fchs;
	काष्ठा bfa_fcxp_s *fcxp;
	काष्ठा bfa_rport_s *bfa_rport = शून्य;
	पूर्णांक             len;

	bfa_trc(port->fcs, rx_fchs->s_id);

	fcxp = bfa_fcs_fcxp_alloc(port->fcs, BFA_FALSE);
	अगर (!fcxp)
		वापस;

	len = fc_ls_acc_build(&fchs, bfa_fcxp_get_reqbuf(fcxp),
			      rx_fchs->s_id, bfa_fcs_lport_get_fcid(port),
			      rx_fchs->ox_id);

	bfa_fcxp_send(fcxp, bfa_rport, port->fabric->vf_id, port->lp_tag,
			  BFA_FALSE, FC_CLASS_3, len, &fchs, शून्य, शून्य,
			  FC_MAX_PDUSZ, 0);
पूर्ण

/*
 *     This routine will be called by bfa_समयr on समयr समयouts.
 *
 *	param[in]	vport		- poपूर्णांकer to bfa_fcs_lport_t.
 *	param[out]	vport_status	- poपूर्णांकer to वापस vport status in
 *
 *	वापस
 *		व्योम
 *
 *	Special Considerations:
 *
 *	note
 */
अटल व्योम
bfa_fcs_lport_scn_समयout(व्योम *arg)
अणु
	काष्ठा bfa_fcs_lport_scn_s *scn = (काष्ठा bfa_fcs_lport_scn_s *) arg;

	bfa_sm_send_event(scn, SCNSM_EVENT_TIMEOUT);
पूर्ण



/*
 *  fcs_scn_खुला FCS state change notअगरication खुला पूर्णांकerfaces
 */

/*
 * Functions called by port/fab
 */
व्योम
bfa_fcs_lport_scn_init(काष्ठा bfa_fcs_lport_s *port)
अणु
	काष्ठा bfa_fcs_lport_scn_s *scn = BFA_FCS_GET_SCN_FROM_PORT(port);

	scn->port = port;
	bfa_sm_set_state(scn, bfa_fcs_lport_scn_sm_offline);
पूर्ण

व्योम
bfa_fcs_lport_scn_offline(काष्ठा bfa_fcs_lport_s *port)
अणु
	काष्ठा bfa_fcs_lport_scn_s *scn = BFA_FCS_GET_SCN_FROM_PORT(port);

	scn->port = port;
	bfa_sm_send_event(scn, SCNSM_EVENT_PORT_OFFLINE);
पूर्ण

व्योम
bfa_fcs_lport_fab_scn_online(काष्ठा bfa_fcs_lport_s *port)
अणु
	काष्ठा bfa_fcs_lport_scn_s *scn = BFA_FCS_GET_SCN_FROM_PORT(port);

	scn->port = port;
	bfa_sm_send_event(scn, SCNSM_EVENT_PORT_ONLINE);
पूर्ण

अटल व्योम
bfa_fcs_lport_scn_portid_rscn(काष्ठा bfa_fcs_lport_s *port, u32 rpid)
अणु
	काष्ठा bfa_fcs_rport_s *rport;
	काष्ठा bfa_fcs_fabric_s *fabric = port->fabric;
	काष्ठा bfa_fcs_vport_s *vport;
	काष्ठा list_head *qe;

	bfa_trc(port->fcs, rpid);

	/*
	 * Ignore PID अगर it is of base port or of vports created on the
	 * same base port. It is to aव्योम vports discovering base port or
	 * other vports created on same base port as remote port
	 */
	अगर (rpid == fabric->bport.pid)
		वापस;

	list_क्रम_each(qe, &fabric->vport_q) अणु
		vport = (काष्ठा bfa_fcs_vport_s *) qe;
		अगर (vport->lport.pid == rpid)
			वापस;
	पूर्ण
	/*
	 * If this is an unknown device, then it just came online.
	 * Otherwise let rport handle the RSCN event.
	 */
	rport = bfa_fcs_lport_get_rport_by_pid(port, rpid);
	अगर (!rport)
		rport = bfa_fcs_lport_get_rport_by_old_pid(port, rpid);

	अगर (rport == शून्य) अणु
		/*
		 * If min cfg mode is enabled, we करोnot need to
		 * discover any new rports.
		 */
		अगर (!__fcs_min_cfg(port->fcs))
			rport = bfa_fcs_rport_create(port, rpid);
	पूर्ण अन्यथा
		bfa_fcs_rport_scn(rport);
पूर्ण

/*
 * rscn क्रमmat based PID comparison
 */
#घोषणा __fc_pid_match(__c0, __c1, __fmt)		\
	(((__fmt) == FC_RSCN_FORMAT_FABRIC) ||		\
	 (((__fmt) == FC_RSCN_FORMAT_DOMAIN) &&		\
	  ((__c0)[0] == (__c1)[0])) ||				\
	 (((__fmt) == FC_RSCN_FORMAT_AREA) &&		\
	  ((__c0)[0] == (__c1)[0]) &&				\
	  ((__c0)[1] == (__c1)[1])))

अटल व्योम
bfa_fcs_lport_scn_multiport_rscn(काष्ठा bfa_fcs_lport_s *port,
				क्रमागत fc_rscn_क्रमmat क्रमmat,
				u32 rscn_pid)
अणु
	काष्ठा bfa_fcs_rport_s *rport;
	काष्ठा list_head        *qe, *qe_next;
	u8        *c0, *c1;

	bfa_trc(port->fcs, क्रमmat);
	bfa_trc(port->fcs, rscn_pid);

	c0 = (u8 *) &rscn_pid;

	list_क्रम_each_safe(qe, qe_next, &port->rport_q) अणु
		rport = (काष्ठा bfa_fcs_rport_s *) qe;
		c1 = (u8 *) &rport->pid;
		अगर (__fc_pid_match(c0, c1, क्रमmat))
			bfa_fcs_rport_scn(rport);
	पूर्ण
पूर्ण


व्योम
bfa_fcs_lport_scn_process_rscn(काष्ठा bfa_fcs_lport_s *port,
			काष्ठा fchs_s *fchs, u32 len)
अणु
	काष्ठा fc_rscn_pl_s *rscn = (काष्ठा fc_rscn_pl_s *) (fchs + 1);
	पूर्णांक             num_entries;
	u32        rscn_pid;
	bfa_boolean_t   nsquery = BFA_FALSE, found;
	पूर्णांक             i = 0, j;

	num_entries =
		(be16_to_cpu(rscn->payldlen) -
		 माप(u32)) / माप(rscn->event[0]);

	bfa_trc(port->fcs, num_entries);

	port->stats.num_rscn++;

	bfa_fcs_lport_scn_send_ls_acc(port, fchs);

	क्रम (i = 0; i < num_entries; i++) अणु
		rscn_pid = rscn->event[i].portid;

		bfa_trc(port->fcs, rscn->event[i].क्रमmat);
		bfa_trc(port->fcs, rscn_pid);

		/* check क्रम duplicate entries in the list */
		found = BFA_FALSE;
		क्रम (j = 0; j < i; j++) अणु
			अगर (rscn->event[j].portid == rscn_pid) अणु
				found = BFA_TRUE;
				अवरोध;
			पूर्ण
		पूर्ण

		/* अगर found in करोwn the list, pid has been alपढ़ोy processed */
		अगर (found) अणु
			bfa_trc(port->fcs, rscn_pid);
			जारी;
		पूर्ण

		चयन (rscn->event[i].क्रमmat) अणु
		हाल FC_RSCN_FORMAT_PORTID:
			अगर (rscn->event[i].qualअगरier == FC_QOS_RSCN_EVENT) अणु
				/*
				 * Ignore this event.
				 * f/w would have processed it
				 */
				bfa_trc(port->fcs, rscn_pid);
			पूर्ण अन्यथा अणु
				port->stats.num_portid_rscn++;
				bfa_fcs_lport_scn_portid_rscn(port, rscn_pid);
			पूर्ण
		अवरोध;

		हाल FC_RSCN_FORMAT_FABRIC:
			अगर (rscn->event[i].qualअगरier ==
					FC_FABRIC_NAME_RSCN_EVENT) अणु
				bfa_fcs_lport_ms_fabric_rscn(port);
				अवरोध;
			पूर्ण
			fallthrough;

		हाल FC_RSCN_FORMAT_AREA:
		हाल FC_RSCN_FORMAT_DOMAIN:
			nsquery = BFA_TRUE;
			bfa_fcs_lport_scn_multiport_rscn(port,
							rscn->event[i].क्रमmat,
							rscn_pid);
			अवरोध;


		शेष:
			WARN_ON(1);
			nsquery = BFA_TRUE;
		पूर्ण
	पूर्ण

	/*
	 * If any of area, करोमुख्य or fabric RSCN is received, करो a fresh
	 * discovery to find new devices.
	 */
	अगर (nsquery)
		bfa_fcs_lport_ns_query(port);
पूर्ण

/*
 * BFA FCS port
 */
/*
 *  fcs_port_api BFA FCS port API
 */
काष्ठा bfa_fcs_lport_s *
bfa_fcs_get_base_port(काष्ठा bfa_fcs_s *fcs)
अणु
	वापस &fcs->fabric.bport;
पूर्ण

wwn_t
bfa_fcs_lport_get_rport(काष्ठा bfa_fcs_lport_s *port, wwn_t wwn, पूर्णांक index,
		पूर्णांक nrports, bfa_boolean_t bwwn)
अणु
	काष्ठा list_head	*qh, *qe;
	काष्ठा bfa_fcs_rport_s *rport = शून्य;
	पूर्णांक	i;
	काष्ठा bfa_fcs_s	*fcs;

	अगर (port == शून्य || nrports == 0)
		वापस (wwn_t) 0;

	fcs = port->fcs;
	bfa_trc(fcs, (u32) nrports);

	i = 0;
	qh = &port->rport_q;
	qe = bfa_q_first(qh);

	जबतक ((qe != qh) && (i < nrports)) अणु
		rport = (काष्ठा bfa_fcs_rport_s *) qe;
		अगर (bfa_ntoh3b(rport->pid) > 0xFFF000) अणु
			qe = bfa_q_next(qe);
			bfa_trc(fcs, (u32) rport->pwwn);
			bfa_trc(fcs, rport->pid);
			bfa_trc(fcs, i);
			जारी;
		पूर्ण

		अगर (bwwn) अणु
			अगर (!स_भेद(&wwn, &rport->pwwn, 8))
				अवरोध;
		पूर्ण अन्यथा अणु
			अगर (i == index)
				अवरोध;
		पूर्ण

		i++;
		qe = bfa_q_next(qe);
	पूर्ण

	bfa_trc(fcs, i);
	अगर (rport)
		वापस rport->pwwn;
	अन्यथा
		वापस (wwn_t) 0;
पूर्ण

व्योम
bfa_fcs_lport_get_rport_quals(काष्ठा bfa_fcs_lport_s *port,
		काष्ठा bfa_rport_qualअगरier_s rports[], पूर्णांक *nrports)
अणु
	काष्ठा list_head	*qh, *qe;
	काष्ठा bfa_fcs_rport_s *rport = शून्य;
	पूर्णांक	i;
	काष्ठा bfa_fcs_s	*fcs;

	अगर (port == शून्य || rports == शून्य || *nrports == 0)
		वापस;

	fcs = port->fcs;
	bfa_trc(fcs, (u32) *nrports);

	i = 0;
	qh = &port->rport_q;
	qe = bfa_q_first(qh);

	जबतक ((qe != qh) && (i < *nrports)) अणु
		rport = (काष्ठा bfa_fcs_rport_s *) qe;
		अगर (bfa_ntoh3b(rport->pid) > 0xFFF000) अणु
			qe = bfa_q_next(qe);
			bfa_trc(fcs, (u32) rport->pwwn);
			bfa_trc(fcs, rport->pid);
			bfa_trc(fcs, i);
			जारी;
		पूर्ण

		अगर (!rport->pwwn && !rport->pid) अणु
			qe = bfa_q_next(qe);
			जारी;
		पूर्ण

		rports[i].pwwn = rport->pwwn;
		rports[i].pid = rport->pid;

		i++;
		qe = bfa_q_next(qe);
	पूर्ण

	bfa_trc(fcs, i);
	*nrports = i;
पूर्ण

/*
 * Iterate's through all the rport's in the given port to
 * determine the maximum operating speed.
 *
 * !!!! To be used in TRL Functionality only !!!!
 */
bfa_port_speed_t
bfa_fcs_lport_get_rport_max_speed(bfa_fcs_lport_t *port)
अणु
	काष्ठा list_head *qh, *qe;
	काष्ठा bfa_fcs_rport_s *rport = शून्य;
	काष्ठा bfa_fcs_s	*fcs;
	bfa_port_speed_t max_speed = 0;
	काष्ठा bfa_port_attr_s port_attr;
	bfa_port_speed_t port_speed, rport_speed;
	bfa_boolean_t trl_enabled;

	अगर (port == शून्य)
		वापस 0;

	fcs = port->fcs;
	trl_enabled = bfa_fcport_is_ratelim(port->fcs->bfa);

	/* Get Physical port's current speed */
	bfa_fcport_get_attr(port->fcs->bfa, &port_attr);
	port_speed = port_attr.speed;
	bfa_trc(fcs, port_speed);

	qh = &port->rport_q;
	qe = bfa_q_first(qh);

	जबतक (qe != qh) अणु
		rport = (काष्ठा bfa_fcs_rport_s *) qe;
		अगर ((bfa_ntoh3b(rport->pid) > 0xFFF000) ||
			(bfa_fcs_rport_get_state(rport) == BFA_RPORT_OFFLINE) ||
			(rport->scsi_function != BFA_RPORT_TARGET)) अणु
			qe = bfa_q_next(qe);
			जारी;
		पूर्ण

		rport_speed = rport->rpf.rpsc_speed;
		अगर ((trl_enabled) && (rport_speed ==
			BFA_PORT_SPEED_UNKNOWN)) अणु
			/* Use शेष ratelim speed setting */
			rport_speed =
				bfa_fcport_get_ratelim_speed(port->fcs->bfa);
		पूर्ण

		अगर (rport_speed > max_speed)
			max_speed = rport_speed;

		qe = bfa_q_next(qe);
	पूर्ण

	अगर (max_speed > port_speed)
		max_speed = port_speed;

	bfa_trc(fcs, max_speed);
	वापस max_speed;
पूर्ण

काष्ठा bfa_fcs_lport_s *
bfa_fcs_lookup_port(काष्ठा bfa_fcs_s *fcs, u16 vf_id, wwn_t lpwwn)
अणु
	काष्ठा bfa_fcs_vport_s *vport;
	bfa_fcs_vf_t   *vf;

	WARN_ON(fcs == शून्य);

	vf = bfa_fcs_vf_lookup(fcs, vf_id);
	अगर (vf == शून्य) अणु
		bfa_trc(fcs, vf_id);
		वापस शून्य;
	पूर्ण

	अगर (!lpwwn || (vf->bport.port_cfg.pwwn == lpwwn))
		वापस &vf->bport;

	vport = bfa_fcs_fabric_vport_lookup(vf, lpwwn);
	अगर (vport)
		वापस &vport->lport;

	वापस शून्य;
पूर्ण

/*
 *  API corresponding to NPIV_VPORT_GETINFO.
 */
व्योम
bfa_fcs_lport_get_info(काष्ठा bfa_fcs_lport_s *port,
	 काष्ठा bfa_lport_info_s *port_info)
अणु

	bfa_trc(port->fcs, port->fabric->fabric_name);

	अगर (port->vport == शून्य) अणु
		/*
		 * This is a Physical port
		 */
		port_info->port_type = BFA_LPORT_TYPE_PHYSICAL;

		/*
		 * @toकरो : need to fix the state & reason
		 */
		port_info->port_state = 0;
		port_info->offline_reason = 0;

		port_info->port_wwn = bfa_fcs_lport_get_pwwn(port);
		port_info->node_wwn = bfa_fcs_lport_get_nwwn(port);

		port_info->max_vports_supp =
			bfa_lps_get_max_vport(port->fcs->bfa);
		port_info->num_vports_inuse =
			port->fabric->num_vports;
		port_info->max_rports_supp = BFA_FCS_MAX_RPORTS_SUPP;
		port_info->num_rports_inuse = port->num_rports;
	पूर्ण अन्यथा अणु
		/*
		 * This is a भव port
		 */
		port_info->port_type = BFA_LPORT_TYPE_VIRTUAL;

		/*
		 * @toकरो : need to fix the state & reason
		 */
		port_info->port_state = 0;
		port_info->offline_reason = 0;

		port_info->port_wwn = bfa_fcs_lport_get_pwwn(port);
		port_info->node_wwn = bfa_fcs_lport_get_nwwn(port);
	पूर्ण
पूर्ण

व्योम
bfa_fcs_lport_get_stats(काष्ठा bfa_fcs_lport_s *fcs_port,
	 काष्ठा bfa_lport_stats_s *port_stats)
अणु
	*port_stats = fcs_port->stats;
पूर्ण

व्योम
bfa_fcs_lport_clear_stats(काष्ठा bfa_fcs_lport_s *fcs_port)
अणु
	स_रखो(&fcs_port->stats, 0, माप(काष्ठा bfa_lport_stats_s));
पूर्ण

/*
 * Let new loop map create missing rports
 */
व्योम
bfa_fcs_lport_lip_scn_online(काष्ठा bfa_fcs_lport_s *port)
अणु
	bfa_fcs_lport_loop_online(port);
पूर्ण

/*
 * FCS भव port state machine
 */

#घोषणा __vport_fcs(__vp)       ((__vp)->lport.fcs)
#घोषणा __vport_pwwn(__vp)      ((__vp)->lport.port_cfg.pwwn)
#घोषणा __vport_nwwn(__vp)      ((__vp)->lport.port_cfg.nwwn)
#घोषणा __vport_bfa(__vp)       ((__vp)->lport.fcs->bfa)
#घोषणा __vport_fcid(__vp)      ((__vp)->lport.pid)
#घोषणा __vport_fabric(__vp)    ((__vp)->lport.fabric)
#घोषणा __vport_vfid(__vp)      ((__vp)->lport.fabric->vf_id)

#घोषणा BFA_FCS_VPORT_MAX_RETRIES  5
/*
 * Forward declarations
 */
अटल व्योम     bfa_fcs_vport_करो_fdisc(काष्ठा bfa_fcs_vport_s *vport);
अटल व्योम     bfa_fcs_vport_समयout(व्योम *vport_arg);
अटल व्योम     bfa_fcs_vport_करो_logo(काष्ठा bfa_fcs_vport_s *vport);
अटल व्योम     bfa_fcs_vport_मुक्त(काष्ठा bfa_fcs_vport_s *vport);

/*
 *  fcs_vport_sm FCS भव port state machine
 */

/*
 * VPort State Machine events
 */
क्रमागत bfa_fcs_vport_event अणु
	BFA_FCS_VPORT_SM_CREATE = 1,	/*  vport create event */
	BFA_FCS_VPORT_SM_DELETE = 2,	/*  vport delete event */
	BFA_FCS_VPORT_SM_START = 3,	/*  vport start request */
	BFA_FCS_VPORT_SM_STOP = 4,	/*  stop: unsupported */
	BFA_FCS_VPORT_SM_ONLINE = 5,	/*  fabric online */
	BFA_FCS_VPORT_SM_OFFLINE = 6,	/*  fabric offline event */
	BFA_FCS_VPORT_SM_FRMSENT = 7,	/*  fdisc/logo sent events */
	BFA_FCS_VPORT_SM_RSP_OK = 8,	/*  good response */
	BFA_FCS_VPORT_SM_RSP_ERROR = 9,	/*  error/bad response */
	BFA_FCS_VPORT_SM_TIMEOUT = 10,	/*  delay समयr event */
	BFA_FCS_VPORT_SM_DELCOMP = 11,	/*  lport delete completion */
	BFA_FCS_VPORT_SM_RSP_DUP_WWN = 12,	/*  Dup wnn error*/
	BFA_FCS_VPORT_SM_RSP_FAILED = 13,	/*  non-retryable failure */
	BFA_FCS_VPORT_SM_STOPCOMP = 14,	/* vport delete completion */
	BFA_FCS_VPORT_SM_FABRIC_MAX = 15, /* max vports on fabric */
पूर्ण;

अटल व्योम     bfa_fcs_vport_sm_uninit(काष्ठा bfa_fcs_vport_s *vport,
					क्रमागत bfa_fcs_vport_event event);
अटल व्योम     bfa_fcs_vport_sm_created(काष्ठा bfa_fcs_vport_s *vport,
					 क्रमागत bfa_fcs_vport_event event);
अटल व्योम     bfa_fcs_vport_sm_offline(काष्ठा bfa_fcs_vport_s *vport,
					 क्रमागत bfa_fcs_vport_event event);
अटल व्योम     bfa_fcs_vport_sm_fdisc(काष्ठा bfa_fcs_vport_s *vport,
				       क्रमागत bfa_fcs_vport_event event);
अटल व्योम     bfa_fcs_vport_sm_fdisc_retry(काष्ठा bfa_fcs_vport_s *vport,
					     क्रमागत bfa_fcs_vport_event event);
अटल व्योम	bfa_fcs_vport_sm_fdisc_rsp_रुको(काष्ठा bfa_fcs_vport_s *vport,
					क्रमागत bfa_fcs_vport_event event);
अटल व्योम     bfa_fcs_vport_sm_online(काष्ठा bfa_fcs_vport_s *vport,
					क्रमागत bfa_fcs_vport_event event);
अटल व्योम     bfa_fcs_vport_sm_deleting(काष्ठा bfa_fcs_vport_s *vport,
					  क्रमागत bfa_fcs_vport_event event);
अटल व्योम     bfa_fcs_vport_sm_cleanup(काष्ठा bfa_fcs_vport_s *vport,
					 क्रमागत bfa_fcs_vport_event event);
अटल व्योम     bfa_fcs_vport_sm_logo(काष्ठा bfa_fcs_vport_s *vport,
				      क्रमागत bfa_fcs_vport_event event);
अटल व्योम     bfa_fcs_vport_sm_error(काष्ठा bfa_fcs_vport_s *vport,
				      क्रमागत bfa_fcs_vport_event event);
अटल व्योम	bfa_fcs_vport_sm_stopping(काष्ठा bfa_fcs_vport_s *vport,
					क्रमागत bfa_fcs_vport_event event);
अटल व्योम	bfa_fcs_vport_sm_logo_क्रम_stop(काष्ठा bfa_fcs_vport_s *vport,
					क्रमागत bfa_fcs_vport_event event);

अटल काष्ठा bfa_sm_table_s  vport_sm_table[] = अणु
	अणुBFA_SM(bfa_fcs_vport_sm_uninit), BFA_FCS_VPORT_UNINITपूर्ण,
	अणुBFA_SM(bfa_fcs_vport_sm_created), BFA_FCS_VPORT_CREATEDपूर्ण,
	अणुBFA_SM(bfa_fcs_vport_sm_offline), BFA_FCS_VPORT_OFFLINEपूर्ण,
	अणुBFA_SM(bfa_fcs_vport_sm_fdisc), BFA_FCS_VPORT_FDISCपूर्ण,
	अणुBFA_SM(bfa_fcs_vport_sm_fdisc_retry), BFA_FCS_VPORT_FDISC_RETRYपूर्ण,
	अणुBFA_SM(bfa_fcs_vport_sm_fdisc_rsp_रुको), BFA_FCS_VPORT_FDISC_RSP_WAITपूर्ण,
	अणुBFA_SM(bfa_fcs_vport_sm_online), BFA_FCS_VPORT_ONLINEपूर्ण,
	अणुBFA_SM(bfa_fcs_vport_sm_deleting), BFA_FCS_VPORT_DELETINGपूर्ण,
	अणुBFA_SM(bfa_fcs_vport_sm_cleanup), BFA_FCS_VPORT_CLEANUPपूर्ण,
	अणुBFA_SM(bfa_fcs_vport_sm_logo), BFA_FCS_VPORT_LOGOपूर्ण,
	अणुBFA_SM(bfa_fcs_vport_sm_error), BFA_FCS_VPORT_ERRORपूर्ण
पूर्ण;

/*
 * Beginning state.
 */
अटल व्योम
bfa_fcs_vport_sm_uninit(काष्ठा bfa_fcs_vport_s *vport,
			क्रमागत bfa_fcs_vport_event event)
अणु
	bfa_trc(__vport_fcs(vport), __vport_pwwn(vport));
	bfa_trc(__vport_fcs(vport), event);

	चयन (event) अणु
	हाल BFA_FCS_VPORT_SM_CREATE:
		bfa_sm_set_state(vport, bfa_fcs_vport_sm_created);
		bfa_fcs_fabric_addvport(__vport_fabric(vport), vport);
		अवरोध;

	शेष:
		bfa_sm_fault(__vport_fcs(vport), event);
	पूर्ण
पूर्ण

/*
 * Created state - a start event is required to start up the state machine.
 */
अटल व्योम
bfa_fcs_vport_sm_created(काष्ठा bfa_fcs_vport_s *vport,
			क्रमागत bfa_fcs_vport_event event)
अणु
	bfa_trc(__vport_fcs(vport), __vport_pwwn(vport));
	bfa_trc(__vport_fcs(vport), event);

	चयन (event) अणु
	हाल BFA_FCS_VPORT_SM_START:
		अगर (bfa_sm_cmp_state(__vport_fabric(vport),
					bfa_fcs_fabric_sm_online)
		    && bfa_fcs_fabric_npiv_capable(__vport_fabric(vport))) अणु
			bfa_sm_set_state(vport, bfa_fcs_vport_sm_fdisc);
			bfa_fcs_vport_करो_fdisc(vport);
		पूर्ण अन्यथा अणु
			/*
			 * Fabric is offline or not NPIV capable, stay in
			 * offline state.
			 */
			vport->vport_stats.fab_no_npiv++;
			bfa_sm_set_state(vport, bfa_fcs_vport_sm_offline);
		पूर्ण
		अवरोध;

	हाल BFA_FCS_VPORT_SM_DELETE:
		bfa_sm_set_state(vport, bfa_fcs_vport_sm_cleanup);
		bfa_fcs_lport_delete(&vport->lport);
		अवरोध;

	हाल BFA_FCS_VPORT_SM_ONLINE:
	हाल BFA_FCS_VPORT_SM_OFFLINE:
		/*
		 * Ignore ONLINE/OFFLINE events from fabric
		 * till vport is started.
		 */
		अवरोध;

	शेष:
		bfa_sm_fault(__vport_fcs(vport), event);
	पूर्ण
पूर्ण

/*
 * Offline state - aरुकोing ONLINE event from fabric SM.
 */
अटल व्योम
bfa_fcs_vport_sm_offline(काष्ठा bfa_fcs_vport_s *vport,
			क्रमागत bfa_fcs_vport_event event)
अणु
	bfa_trc(__vport_fcs(vport), __vport_pwwn(vport));
	bfa_trc(__vport_fcs(vport), event);

	चयन (event) अणु
	हाल BFA_FCS_VPORT_SM_DELETE:
		bfa_sm_set_state(vport, bfa_fcs_vport_sm_cleanup);
		bfa_fcs_lport_delete(&vport->lport);
		अवरोध;

	हाल BFA_FCS_VPORT_SM_ONLINE:
		bfa_sm_set_state(vport, bfa_fcs_vport_sm_fdisc);
		vport->fdisc_retries = 0;
		bfa_fcs_vport_करो_fdisc(vport);
		अवरोध;

	हाल BFA_FCS_VPORT_SM_STOP:
		bfa_sm_set_state(vport, bfa_fcs_vport_sm_cleanup);
		bfa_sm_send_event(&vport->lport, BFA_FCS_PORT_SM_STOP);
		अवरोध;

	हाल BFA_FCS_VPORT_SM_OFFLINE:
		/*
		 * This can happen अगर the vport couldn't be initialzied
		 * due the fact that the npiv was not enabled on the चयन.
		 * In that हाल we will put the vport in offline state.
		 * However, the link can go करोwn and cause the this event to
		 * be sent when we are alपढ़ोy offline. Ignore it.
		 */
		अवरोध;

	शेष:
		bfa_sm_fault(__vport_fcs(vport), event);
	पूर्ण
पूर्ण


/*
 * FDISC is sent and aरुकोing reply from fabric.
 */
अटल व्योम
bfa_fcs_vport_sm_fdisc(काष्ठा bfa_fcs_vport_s *vport,
			क्रमागत bfa_fcs_vport_event event)
अणु
	bfa_trc(__vport_fcs(vport), __vport_pwwn(vport));
	bfa_trc(__vport_fcs(vport), event);

	चयन (event) अणु
	हाल BFA_FCS_VPORT_SM_DELETE:
		bfa_sm_set_state(vport, bfa_fcs_vport_sm_fdisc_rsp_रुको);
		अवरोध;

	हाल BFA_FCS_VPORT_SM_OFFLINE:
		bfa_sm_set_state(vport, bfa_fcs_vport_sm_offline);
		bfa_sm_send_event(vport->lps, BFA_LPS_SM_OFFLINE);
		अवरोध;

	हाल BFA_FCS_VPORT_SM_RSP_OK:
		bfa_sm_set_state(vport, bfa_fcs_vport_sm_online);
		bfa_fcs_lport_online(&vport->lport);
		अवरोध;

	हाल BFA_FCS_VPORT_SM_RSP_ERROR:
		bfa_sm_set_state(vport, bfa_fcs_vport_sm_fdisc_retry);
		bfa_समयr_start(__vport_bfa(vport), &vport->समयr,
				    bfa_fcs_vport_समयout, vport,
				    BFA_FCS_RETRY_TIMEOUT);
		अवरोध;

	हाल BFA_FCS_VPORT_SM_RSP_FAILED:
	हाल BFA_FCS_VPORT_SM_FABRIC_MAX:
		bfa_sm_set_state(vport, bfa_fcs_vport_sm_offline);
		अवरोध;

	हाल BFA_FCS_VPORT_SM_RSP_DUP_WWN:
		bfa_sm_set_state(vport, bfa_fcs_vport_sm_error);
		अवरोध;

	शेष:
		bfa_sm_fault(__vport_fcs(vport), event);
	पूर्ण
पूर्ण

/*
 * FDISC attempt failed - a समयr is active to retry FDISC.
 */
अटल व्योम
bfa_fcs_vport_sm_fdisc_retry(काष्ठा bfa_fcs_vport_s *vport,
			     क्रमागत bfa_fcs_vport_event event)
अणु
	bfa_trc(__vport_fcs(vport), __vport_pwwn(vport));
	bfa_trc(__vport_fcs(vport), event);

	चयन (event) अणु
	हाल BFA_FCS_VPORT_SM_DELETE:
		bfa_sm_set_state(vport, bfa_fcs_vport_sm_cleanup);
		bfa_समयr_stop(&vport->समयr);
		bfa_fcs_lport_delete(&vport->lport);
		अवरोध;

	हाल BFA_FCS_VPORT_SM_OFFLINE:
		bfa_sm_set_state(vport, bfa_fcs_vport_sm_offline);
		bfa_समयr_stop(&vport->समयr);
		अवरोध;

	हाल BFA_FCS_VPORT_SM_TIMEOUT:
		bfa_sm_set_state(vport, bfa_fcs_vport_sm_fdisc);
		vport->vport_stats.fdisc_retries++;
		vport->fdisc_retries++;
		bfa_fcs_vport_करो_fdisc(vport);
		अवरोध;

	शेष:
		bfa_sm_fault(__vport_fcs(vport), event);
	पूर्ण
पूर्ण

/*
 * FDISC is in progress and we got a vport delete request -
 * this is a रुको state जबतक we रुको क्रम fdisc response and
 * we will transition to the appropriate state - on rsp status.
 */
अटल व्योम
bfa_fcs_vport_sm_fdisc_rsp_रुको(काष्ठा bfa_fcs_vport_s *vport,
				क्रमागत bfa_fcs_vport_event event)
अणु
	bfa_trc(__vport_fcs(vport), __vport_pwwn(vport));
	bfa_trc(__vport_fcs(vport), event);

	चयन (event) अणु
	हाल BFA_FCS_VPORT_SM_RSP_OK:
		bfa_sm_set_state(vport, bfa_fcs_vport_sm_deleting);
		bfa_fcs_lport_delete(&vport->lport);
		अवरोध;

	हाल BFA_FCS_VPORT_SM_DELETE:
		अवरोध;

	हाल BFA_FCS_VPORT_SM_OFFLINE:
	हाल BFA_FCS_VPORT_SM_RSP_ERROR:
	हाल BFA_FCS_VPORT_SM_RSP_FAILED:
	हाल BFA_FCS_VPORT_SM_FABRIC_MAX:
	हाल BFA_FCS_VPORT_SM_RSP_DUP_WWN:
		bfa_sm_set_state(vport, bfa_fcs_vport_sm_cleanup);
		bfa_sm_send_event(vport->lps, BFA_LPS_SM_OFFLINE);
		bfa_fcs_lport_delete(&vport->lport);
		अवरोध;

	शेष:
		bfa_sm_fault(__vport_fcs(vport), event);
	पूर्ण
पूर्ण

/*
 * Vport is online (FDISC is complete).
 */
अटल व्योम
bfa_fcs_vport_sm_online(काष्ठा bfa_fcs_vport_s *vport,
			क्रमागत bfa_fcs_vport_event event)
अणु
	bfa_trc(__vport_fcs(vport), __vport_pwwn(vport));
	bfa_trc(__vport_fcs(vport), event);

	चयन (event) अणु
	हाल BFA_FCS_VPORT_SM_DELETE:
		bfa_sm_set_state(vport, bfa_fcs_vport_sm_deleting);
		bfa_fcs_lport_delete(&vport->lport);
		अवरोध;

	हाल BFA_FCS_VPORT_SM_STOP:
		bfa_sm_set_state(vport, bfa_fcs_vport_sm_stopping);
		bfa_sm_send_event(&vport->lport, BFA_FCS_PORT_SM_STOP);
		अवरोध;

	हाल BFA_FCS_VPORT_SM_OFFLINE:
		bfa_sm_set_state(vport, bfa_fcs_vport_sm_offline);
		bfa_sm_send_event(vport->lps, BFA_LPS_SM_OFFLINE);
		bfa_fcs_lport_offline(&vport->lport);
		अवरोध;

	शेष:
		bfa_sm_fault(__vport_fcs(vport), event);
	पूर्ण
पूर्ण

/*
 * Vport is being stopped - aरुकोing lport stop completion to send
 * LOGO to fabric.
 */
अटल व्योम
bfa_fcs_vport_sm_stopping(काष्ठा bfa_fcs_vport_s *vport,
			  क्रमागत bfa_fcs_vport_event event)
अणु
	bfa_trc(__vport_fcs(vport), __vport_pwwn(vport));
	bfa_trc(__vport_fcs(vport), event);

	चयन (event) अणु
	हाल BFA_FCS_VPORT_SM_STOPCOMP:
		bfa_sm_set_state(vport, bfa_fcs_vport_sm_logo_क्रम_stop);
		bfa_fcs_vport_करो_logo(vport);
		अवरोध;

	हाल BFA_FCS_VPORT_SM_OFFLINE:
		bfa_sm_set_state(vport, bfa_fcs_vport_sm_cleanup);
		अवरोध;

	शेष:
		bfa_sm_fault(__vport_fcs(vport), event);
	पूर्ण
पूर्ण

/*
 * Vport is being deleted - aरुकोing lport delete completion to send
 * LOGO to fabric.
 */
अटल व्योम
bfa_fcs_vport_sm_deleting(काष्ठा bfa_fcs_vport_s *vport,
			क्रमागत bfa_fcs_vport_event event)
अणु
	bfa_trc(__vport_fcs(vport), __vport_pwwn(vport));
	bfa_trc(__vport_fcs(vport), event);

	चयन (event) अणु
	हाल BFA_FCS_VPORT_SM_DELETE:
		अवरोध;

	हाल BFA_FCS_VPORT_SM_DELCOMP:
		bfa_sm_set_state(vport, bfa_fcs_vport_sm_logo);
		bfa_fcs_vport_करो_logo(vport);
		अवरोध;

	हाल BFA_FCS_VPORT_SM_OFFLINE:
		bfa_sm_set_state(vport, bfa_fcs_vport_sm_cleanup);
		अवरोध;

	शेष:
		bfa_sm_fault(__vport_fcs(vport), event);
	पूर्ण
पूर्ण

/*
 * Error State.
 * This state will be set when the Vport Creation fails due
 * to errors like Dup WWN. In this state only operation allowed
 * is a Vport Delete.
 */
अटल व्योम
bfa_fcs_vport_sm_error(काष्ठा bfa_fcs_vport_s *vport,
			क्रमागत bfa_fcs_vport_event event)
अणु
	bfa_trc(__vport_fcs(vport), __vport_pwwn(vport));
	bfa_trc(__vport_fcs(vport), event);

	चयन (event) अणु
	हाल BFA_FCS_VPORT_SM_DELETE:
		bfa_sm_set_state(vport, bfa_fcs_vport_sm_cleanup);
		bfa_fcs_lport_delete(&vport->lport);
		अवरोध;

	शेष:
		bfa_trc(__vport_fcs(vport), event);
	पूर्ण
पूर्ण

/*
 * Lport cleanup is in progress since vport is being deleted. Fabric is
 * offline, so no LOGO is needed to complete vport deletion.
 */
अटल व्योम
bfa_fcs_vport_sm_cleanup(काष्ठा bfa_fcs_vport_s *vport,
			क्रमागत bfa_fcs_vport_event event)
अणु
	bfa_trc(__vport_fcs(vport), __vport_pwwn(vport));
	bfa_trc(__vport_fcs(vport), event);

	चयन (event) अणु
	हाल BFA_FCS_VPORT_SM_DELCOMP:
		bfa_sm_set_state(vport, bfa_fcs_vport_sm_uninit);
		bfa_fcs_vport_मुक्त(vport);
		अवरोध;

	हाल BFA_FCS_VPORT_SM_STOPCOMP:
		bfa_sm_set_state(vport, bfa_fcs_vport_sm_created);
		अवरोध;

	हाल BFA_FCS_VPORT_SM_DELETE:
		अवरोध;

	शेष:
		bfa_sm_fault(__vport_fcs(vport), event);
	पूर्ण
पूर्ण

/*
 * LOGO is sent to fabric. Vport stop is in progress. Lport stop cleanup
 * is करोne.
 */
अटल व्योम
bfa_fcs_vport_sm_logo_क्रम_stop(काष्ठा bfa_fcs_vport_s *vport,
			       क्रमागत bfa_fcs_vport_event event)
अणु
	bfa_trc(__vport_fcs(vport), __vport_pwwn(vport));
	bfa_trc(__vport_fcs(vport), event);

	चयन (event) अणु
	हाल BFA_FCS_VPORT_SM_OFFLINE:
		bfa_sm_send_event(vport->lps, BFA_LPS_SM_OFFLINE);
		fallthrough;

	हाल BFA_FCS_VPORT_SM_RSP_OK:
	हाल BFA_FCS_VPORT_SM_RSP_ERROR:
		bfa_sm_set_state(vport, bfa_fcs_vport_sm_created);
		अवरोध;

	शेष:
		bfa_sm_fault(__vport_fcs(vport), event);
	पूर्ण
पूर्ण

/*
 * LOGO is sent to fabric. Vport delete is in progress. Lport delete cleanup
 * is करोne.
 */
अटल व्योम
bfa_fcs_vport_sm_logo(काष्ठा bfa_fcs_vport_s *vport,
			क्रमागत bfa_fcs_vport_event event)
अणु
	bfa_trc(__vport_fcs(vport), __vport_pwwn(vport));
	bfa_trc(__vport_fcs(vport), event);

	चयन (event) अणु
	हाल BFA_FCS_VPORT_SM_OFFLINE:
		bfa_sm_send_event(vport->lps, BFA_LPS_SM_OFFLINE);
		fallthrough;

	हाल BFA_FCS_VPORT_SM_RSP_OK:
	हाल BFA_FCS_VPORT_SM_RSP_ERROR:
		bfa_sm_set_state(vport, bfa_fcs_vport_sm_uninit);
		bfa_fcs_vport_मुक्त(vport);
		अवरोध;

	हाल BFA_FCS_VPORT_SM_DELETE:
		अवरोध;

	शेष:
		bfa_sm_fault(__vport_fcs(vport), event);
	पूर्ण
पूर्ण



/*
 *  fcs_vport_निजी FCS भव port निजी functions
 */
/*
 * Send AEN notअगरication
 */
अटल व्योम
bfa_fcs_vport_aen_post(काष्ठा bfa_fcs_lport_s *port,
		       क्रमागत bfa_lport_aen_event event)
अणु
	काष्ठा bfad_s *bfad = (काष्ठा bfad_s *)port->fabric->fcs->bfad;
	काष्ठा bfa_aen_entry_s  *aen_entry;

	bfad_get_aen_entry(bfad, aen_entry);
	अगर (!aen_entry)
		वापस;

	aen_entry->aen_data.lport.vf_id = port->fabric->vf_id;
	aen_entry->aen_data.lport.roles = port->port_cfg.roles;
	aen_entry->aen_data.lport.ppwwn = bfa_fcs_lport_get_pwwn(
					bfa_fcs_get_base_port(port->fcs));
	aen_entry->aen_data.lport.lpwwn = bfa_fcs_lport_get_pwwn(port);

	/* Send the AEN notअगरication */
	bfad_im_post_venकरोr_event(aen_entry, bfad, ++port->fcs->fcs_aen_seq,
				  BFA_AEN_CAT_LPORT, event);
पूर्ण

/*
 * This routine will be called to send a FDISC command.
 */
अटल व्योम
bfa_fcs_vport_करो_fdisc(काष्ठा bfa_fcs_vport_s *vport)
अणु
	bfa_lps_fdisc(vport->lps, vport,
		bfa_fcport_get_maxfrsize(__vport_bfa(vport)),
		__vport_pwwn(vport), __vport_nwwn(vport));
	vport->vport_stats.fdisc_sent++;
पूर्ण

अटल व्योम
bfa_fcs_vport_fdisc_rejected(काष्ठा bfa_fcs_vport_s *vport)
अणु
	u8		lsrjt_rsn = vport->lps->lsrjt_rsn;
	u8		lsrjt_expl = vport->lps->lsrjt_expl;

	bfa_trc(__vport_fcs(vport), lsrjt_rsn);
	bfa_trc(__vport_fcs(vport), lsrjt_expl);

	/* For certain reason codes, we करोn't want to retry. */
	चयन (vport->lps->lsrjt_expl) अणु
	हाल FC_LS_RJT_EXP_INV_PORT_NAME: /* by brocade */
	हाल FC_LS_RJT_EXP_INVALID_NPORT_ID: /* by Cisco */
		अगर (vport->fdisc_retries < BFA_FCS_VPORT_MAX_RETRIES)
			bfa_sm_send_event(vport, BFA_FCS_VPORT_SM_RSP_ERROR);
		अन्यथा अणु
			bfa_fcs_vport_aen_post(&vport->lport,
					BFA_LPORT_AEN_NPIV_DUP_WWN);
			bfa_sm_send_event(vport, BFA_FCS_VPORT_SM_RSP_DUP_WWN);
		पूर्ण
		अवरोध;

	हाल FC_LS_RJT_EXP_INSUFF_RES:
		/*
		 * This means max logins per port/चयन setting on the
		 * चयन was exceeded.
		 */
		अगर (vport->fdisc_retries < BFA_FCS_VPORT_MAX_RETRIES)
			bfa_sm_send_event(vport, BFA_FCS_VPORT_SM_RSP_ERROR);
		अन्यथा अणु
			bfa_fcs_vport_aen_post(&vport->lport,
					BFA_LPORT_AEN_NPIV_FABRIC_MAX);
			bfa_sm_send_event(vport, BFA_FCS_VPORT_SM_FABRIC_MAX);
		पूर्ण
		अवरोध;

	शेष:
		अगर (vport->fdisc_retries == 0)
			bfa_fcs_vport_aen_post(&vport->lport,
					BFA_LPORT_AEN_NPIV_UNKNOWN);
		bfa_sm_send_event(vport, BFA_FCS_VPORT_SM_RSP_ERROR);
	पूर्ण
पूर्ण

/*
 *	Called to send a logout to the fabric. Used when a V-Port is
 *	deleted/stopped.
 */
अटल व्योम
bfa_fcs_vport_करो_logo(काष्ठा bfa_fcs_vport_s *vport)
अणु
	bfa_trc(__vport_fcs(vport), __vport_pwwn(vport));

	vport->vport_stats.logo_sent++;
	bfa_lps_fdisclogo(vport->lps);
पूर्ण


/*
 *     This routine will be called by bfa_समयr on समयr समयouts.
 *
 *	param[in]	vport		- poपूर्णांकer to bfa_fcs_vport_t.
 *	param[out]	vport_status	- poपूर्णांकer to वापस vport status in
 *
 *	वापस
 *		व्योम
 *
 *	Special Considerations:
 *
 *	note
 */
अटल व्योम
bfa_fcs_vport_समयout(व्योम *vport_arg)
अणु
	काष्ठा bfa_fcs_vport_s *vport = (काष्ठा bfa_fcs_vport_s *) vport_arg;

	vport->vport_stats.fdisc_समयouts++;
	bfa_sm_send_event(vport, BFA_FCS_VPORT_SM_TIMEOUT);
पूर्ण

अटल व्योम
bfa_fcs_vport_मुक्त(काष्ठा bfa_fcs_vport_s *vport)
अणु
	काष्ठा bfad_vport_s *vport_drv =
			(काष्ठा bfad_vport_s *)vport->vport_drv;

	bfa_fcs_fabric_delvport(__vport_fabric(vport), vport);
	bfa_lps_delete(vport->lps);

	अगर (vport_drv->comp_del) अणु
		complete(vport_drv->comp_del);
		वापस;
	पूर्ण

	/*
	 * We queue the vport delete work to the IM work_q from here.
	 * The memory क्रम the bfad_vport_s is मुक्तd from the FC function
	 * ढाँचा vport_delete entry poपूर्णांक.
	 */
	bfad_im_port_delete(vport_drv->drv_port.bfad, &vport_drv->drv_port);
पूर्ण

/*
 *  fcs_vport_खुला FCS भव port खुला पूर्णांकerfaces
 */

/*
 * Online notअगरication from fabric SM.
 */
व्योम
bfa_fcs_vport_online(काष्ठा bfa_fcs_vport_s *vport)
अणु
	vport->vport_stats.fab_online++;
	अगर (bfa_fcs_fabric_npiv_capable(__vport_fabric(vport)))
		bfa_sm_send_event(vport, BFA_FCS_VPORT_SM_ONLINE);
	अन्यथा
		vport->vport_stats.fab_no_npiv++;
पूर्ण

/*
 * Offline notअगरication from fabric SM.
 */
व्योम
bfa_fcs_vport_offline(काष्ठा bfa_fcs_vport_s *vport)
अणु
	vport->vport_stats.fab_offline++;
	bfa_sm_send_event(vport, BFA_FCS_VPORT_SM_OFFLINE);
पूर्ण

/*
 * Cleanup notअगरication from fabric SM on link समयr expiry.
 */
व्योम
bfa_fcs_vport_cleanup(काष्ठा bfa_fcs_vport_s *vport)
अणु
	vport->vport_stats.fab_cleanup++;
पूर्ण

/*
 * Stop notअगरication from fabric SM. To be invoked from within FCS.
 */
व्योम
bfa_fcs_vport_fcs_stop(काष्ठा bfa_fcs_vport_s *vport)
अणु
	bfa_sm_send_event(vport, BFA_FCS_VPORT_SM_STOP);
पूर्ण

/*
 * delete notअगरication from fabric SM. To be invoked from within FCS.
 */
व्योम
bfa_fcs_vport_fcs_delete(काष्ठा bfa_fcs_vport_s *vport)
अणु
	bfa_sm_send_event(vport, BFA_FCS_VPORT_SM_DELETE);
पूर्ण

/*
 * Stop completion callback from associated lport
 */
व्योम
bfa_fcs_vport_stop_comp(काष्ठा bfa_fcs_vport_s *vport)
अणु
	bfa_sm_send_event(vport, BFA_FCS_VPORT_SM_STOPCOMP);
पूर्ण

/*
 * Delete completion callback from associated lport
 */
व्योम
bfa_fcs_vport_delete_comp(काष्ठा bfa_fcs_vport_s *vport)
अणु
	bfa_sm_send_event(vport, BFA_FCS_VPORT_SM_DELCOMP);
पूर्ण



/*
 *  fcs_vport_api Virtual port API
 */

/*
 *	Use this function to instantiate a new FCS vport object. This
 *	function will not trigger any HW initialization process (which will be
 *	करोne in vport_start() call)
 *
 *	param[in] vport	-		poपूर्णांकer to bfa_fcs_vport_t. This space
 *					needs to be allocated by the driver.
 *	param[in] fcs		-	FCS instance
 *	param[in] vport_cfg	-	vport configuration
 *	param[in] vf_id		-	VF_ID अगर vport is created within a VF.
 *					FC_VF_ID_शून्य to specअगरy base fabric.
 *	param[in] vport_drv	-	Opaque handle back to the driver's vport
 *					काष्ठाure
 *
 *	retval BFA_STATUS_OK - on success.
 *	retval BFA_STATUS_FAILED - on failure.
 */
bfa_status_t
bfa_fcs_vport_create(काष्ठा bfa_fcs_vport_s *vport, काष्ठा bfa_fcs_s *fcs,
		u16 vf_id, काष्ठा bfa_lport_cfg_s *vport_cfg,
		काष्ठा bfad_vport_s *vport_drv)
अणु
	अगर (vport_cfg->pwwn == 0)
		वापस BFA_STATUS_INVALID_WWN;

	अगर (bfa_fcs_lport_get_pwwn(&fcs->fabric.bport) == vport_cfg->pwwn)
		वापस BFA_STATUS_VPORT_WWN_BP;

	अगर (bfa_fcs_vport_lookup(fcs, vf_id, vport_cfg->pwwn) != शून्य)
		वापस BFA_STATUS_VPORT_EXISTS;

	अगर (fcs->fabric.num_vports ==
			bfa_lps_get_max_vport(fcs->bfa))
		वापस BFA_STATUS_VPORT_MAX;

	vport->lps = bfa_lps_alloc(fcs->bfa);
	अगर (!vport->lps)
		वापस BFA_STATUS_VPORT_MAX;

	vport->vport_drv = vport_drv;
	vport_cfg->preboot_vp = BFA_FALSE;

	bfa_sm_set_state(vport, bfa_fcs_vport_sm_uninit);
	bfa_fcs_lport_attach(&vport->lport, fcs, vf_id, vport);
	bfa_fcs_lport_init(&vport->lport, vport_cfg);
	bfa_sm_send_event(vport, BFA_FCS_VPORT_SM_CREATE);

	वापस BFA_STATUS_OK;
पूर्ण

/*
 *	Use this function to instantiate a new FCS PBC vport object. This
 *	function will not trigger any HW initialization process (which will be
 *	करोne in vport_start() call)
 *
 *	param[in] vport	-	poपूर्णांकer to bfa_fcs_vport_t. This space
 *				needs to be allocated by the driver.
 *	param[in] fcs	-	FCS instance
 *	param[in] vport_cfg	-	vport configuration
 *	param[in] vf_id		-	VF_ID अगर vport is created within a VF.
 *					FC_VF_ID_शून्य to specअगरy base fabric.
 *	param[in] vport_drv	-	Opaque handle back to the driver's vport
 *					काष्ठाure
 *
 *	retval BFA_STATUS_OK - on success.
 *	retval BFA_STATUS_FAILED - on failure.
 */
bfa_status_t
bfa_fcs_pbc_vport_create(काष्ठा bfa_fcs_vport_s *vport, काष्ठा bfa_fcs_s *fcs,
			u16 vf_id, काष्ठा bfa_lport_cfg_s *vport_cfg,
			काष्ठा bfad_vport_s *vport_drv)
अणु
	bfa_status_t rc;

	rc = bfa_fcs_vport_create(vport, fcs, vf_id, vport_cfg, vport_drv);
	vport->lport.port_cfg.preboot_vp = BFA_TRUE;

	वापस rc;
पूर्ण

/*
 *	Use this function to finकरोut अगर this is a pbc vport or not.
 *
 * @param[in] vport - poपूर्णांकer to bfa_fcs_vport_t.
 *
 * @वापसs None
 */
bfa_boolean_t
bfa_fcs_is_pbc_vport(काष्ठा bfa_fcs_vport_s *vport)
अणु

	अगर (vport && (vport->lport.port_cfg.preboot_vp == BFA_TRUE))
		वापस BFA_TRUE;
	अन्यथा
		वापस BFA_FALSE;

पूर्ण

/*
 * Use this function initialize the vport.
 *
 * @param[in] vport - poपूर्णांकer to bfa_fcs_vport_t.
 *
 * @वापसs None
 */
bfa_status_t
bfa_fcs_vport_start(काष्ठा bfa_fcs_vport_s *vport)
अणु
	bfa_sm_send_event(vport, BFA_FCS_VPORT_SM_START);

	वापस BFA_STATUS_OK;
पूर्ण

/*
 *	Use this function quiese the vport object. This function will वापस
 *	immediately, when the vport is actually stopped, the
 *	bfa_drv_vport_stop_cb() will be called.
 *
 *	param[in] vport - poपूर्णांकer to bfa_fcs_vport_t.
 *
 *	वापस None
 */
bfa_status_t
bfa_fcs_vport_stop(काष्ठा bfa_fcs_vport_s *vport)
अणु
	bfa_sm_send_event(vport, BFA_FCS_VPORT_SM_STOP);

	वापस BFA_STATUS_OK;
पूर्ण

/*
 *	Use this function to delete a vport object. Fabric object should
 *	be stopped beक्रमe this function call.
 *
 *	!!!!!!! Donot invoke this from within FCS  !!!!!!!
 *
 *	param[in] vport - poपूर्णांकer to bfa_fcs_vport_t.
 *
 *	वापस     None
 */
bfa_status_t
bfa_fcs_vport_delete(काष्ठा bfa_fcs_vport_s *vport)
अणु

	अगर (vport->lport.port_cfg.preboot_vp)
		वापस BFA_STATUS_PBC;

	bfa_sm_send_event(vport, BFA_FCS_VPORT_SM_DELETE);

	वापस BFA_STATUS_OK;
पूर्ण

/*
 *	Use this function to get vport's current status info.
 *
 *	param[in] vport		poपूर्णांकer to bfa_fcs_vport_t.
 *	param[out] attr		poपूर्णांकer to वापस vport attributes
 *
 *	वापस None
 */
व्योम
bfa_fcs_vport_get_attr(काष्ठा bfa_fcs_vport_s *vport,
			काष्ठा bfa_vport_attr_s *attr)
अणु
	अगर (vport == शून्य || attr == शून्य)
		वापस;

	स_रखो(attr, 0, माप(काष्ठा bfa_vport_attr_s));

	bfa_fcs_lport_get_attr(&vport->lport, &attr->port_attr);
	attr->vport_state = bfa_sm_to_state(vport_sm_table, vport->sm);
पूर्ण


/*
 *	Lookup a भव port. Excludes base port from lookup.
 */
काष्ठा bfa_fcs_vport_s *
bfa_fcs_vport_lookup(काष्ठा bfa_fcs_s *fcs, u16 vf_id, wwn_t vpwwn)
अणु
	काष्ठा bfa_fcs_vport_s *vport;
	काष्ठा bfa_fcs_fabric_s *fabric;

	bfa_trc(fcs, vf_id);
	bfa_trc(fcs, vpwwn);

	fabric = bfa_fcs_vf_lookup(fcs, vf_id);
	अगर (!fabric) अणु
		bfa_trc(fcs, vf_id);
		वापस शून्य;
	पूर्ण

	vport = bfa_fcs_fabric_vport_lookup(fabric, vpwwn);
	वापस vport;
पूर्ण

/*
 * FDISC Response
 */
व्योम
bfa_cb_lps_fdisc_comp(व्योम *bfad, व्योम *uarg, bfa_status_t status)
अणु
	काष्ठा bfa_fcs_vport_s *vport = uarg;

	bfa_trc(__vport_fcs(vport), __vport_pwwn(vport));
	bfa_trc(__vport_fcs(vport), status);

	चयन (status) अणु
	हाल BFA_STATUS_OK:
		/*
		 * Initialize the V-Port fields
		 */
		__vport_fcid(vport) = vport->lps->lp_pid;
		vport->vport_stats.fdisc_accepts++;
		bfa_sm_send_event(vport, BFA_FCS_VPORT_SM_RSP_OK);
		अवरोध;

	हाल BFA_STATUS_INVALID_MAC:
		/* Only क्रम CNA */
		vport->vport_stats.fdisc_acc_bad++;
		bfa_sm_send_event(vport, BFA_FCS_VPORT_SM_RSP_ERROR);

		अवरोध;

	हाल BFA_STATUS_EPROTOCOL:
		चयन (vport->lps->ext_status) अणु
		हाल BFA_EPROTO_BAD_ACCEPT:
			vport->vport_stats.fdisc_acc_bad++;
			अवरोध;

		हाल BFA_EPROTO_UNKNOWN_RSP:
			vport->vport_stats.fdisc_unknown_rsp++;
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण

		अगर (vport->fdisc_retries < BFA_FCS_VPORT_MAX_RETRIES)
			bfa_sm_send_event(vport, BFA_FCS_VPORT_SM_RSP_ERROR);
		अन्यथा
			bfa_sm_send_event(vport, BFA_FCS_VPORT_SM_RSP_FAILED);

		अवरोध;

	हाल BFA_STATUS_ETIMER:
		vport->vport_stats.fdisc_समयouts++;
		अगर (vport->fdisc_retries < BFA_FCS_VPORT_MAX_RETRIES)
			bfa_sm_send_event(vport, BFA_FCS_VPORT_SM_RSP_ERROR);
		अन्यथा
			bfa_sm_send_event(vport, BFA_FCS_VPORT_SM_RSP_FAILED);
		अवरोध;

	हाल BFA_STATUS_FABRIC_RJT:
		vport->vport_stats.fdisc_rejects++;
		bfa_fcs_vport_fdisc_rejected(vport);
		अवरोध;

	शेष:
		vport->vport_stats.fdisc_rsp_err++;
		bfa_sm_send_event(vport, BFA_FCS_VPORT_SM_RSP_ERROR);
	पूर्ण
पूर्ण

/*
 * LOGO response
 */
व्योम
bfa_cb_lps_fdisclogo_comp(व्योम *bfad, व्योम *uarg)
अणु
	काष्ठा bfa_fcs_vport_s *vport = uarg;
	bfa_sm_send_event(vport, BFA_FCS_VPORT_SM_RSP_OK);
पूर्ण

/*
 * Received clear भव link
 */
व्योम
bfa_cb_lps_cvl_event(व्योम *bfad, व्योम *uarg)
अणु
	काष्ठा bfa_fcs_vport_s *vport = uarg;

	/* Send an Offline followed by an ONLINE */
	bfa_sm_send_event(vport, BFA_FCS_VPORT_SM_OFFLINE);
	bfa_sm_send_event(vport, BFA_FCS_VPORT_SM_ONLINE);
पूर्ण
