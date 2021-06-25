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

#अगर_अघोषित __BFA_FCS_H__
#घोषणा __BFA_FCS_H__

#समावेश "bfa_cs.h"
#समावेश "bfa_defs.h"
#समावेश "bfa_defs_fcs.h"
#समावेश "bfa_modules.h"
#समावेश "bfa_fc.h"

#घोषणा BFA_FCS_OS_STR_LEN		64

/*
 *  lps_pvt BFA LPS निजी functions
 */

क्रमागत bfa_lps_event अणु
	BFA_LPS_SM_LOGIN	= 1,	/* login request from user      */
	BFA_LPS_SM_LOGOUT	= 2,	/* logout request from user     */
	BFA_LPS_SM_FWRSP	= 3,	/* f/w response to login/logout */
	BFA_LPS_SM_RESUME	= 4,	/* space present in reqq queue  */
	BFA_LPS_SM_DELETE	= 5,	/* lps delete from user         */
	BFA_LPS_SM_OFFLINE	= 6,	/* Link is offline              */
	BFA_LPS_SM_RX_CVL	= 7,	/* Rx clear भव link        */
	BFA_LPS_SM_SET_N2N_PID  = 8,	/* Set asचिन्हित PID क्रम n2n */
पूर्ण;


/*
 * !!! Only append to the क्रमागतs defined here to aव्योम any versioning
 * !!! needed between trace utility and driver version
 */
क्रमागत अणु
	BFA_TRC_FCS_FCS		= 1,
	BFA_TRC_FCS_PORT	= 2,
	BFA_TRC_FCS_RPORT	= 3,
	BFA_TRC_FCS_FCPIM	= 4,
पूर्ण;


काष्ठा bfa_fcs_s;

#घोषणा __fcs_min_cfg(__fcs)       ((__fcs)->min_cfg)

#घोषणा BFA_FCS_BRCD_SWITCH_OUI  0x051e
#घोषणा N2N_LOCAL_PID	    0x010000
#घोषणा N2N_REMOTE_PID		0x020000
#घोषणा	BFA_FCS_RETRY_TIMEOUT 2000
#घोषणा BFA_FCS_MAX_NS_RETRIES 5
#घोषणा BFA_FCS_PID_IS_WKA(pid)  ((bfa_ntoh3b(pid) > 0xFFF000) ?  1 : 0)
#घोषणा BFA_FCS_MAX_RPORT_LOGINS 1024

काष्ठा bfa_fcs_lport_ns_s अणु
	bfa_sm_t        sm;		/*  state machine */
	काष्ठा bfa_समयr_s समयr;
	काष्ठा bfa_fcs_lport_s *port;	/*  parent port */
	काष्ठा bfa_fcxp_s *fcxp;
	काष्ठा bfa_fcxp_wqe_s fcxp_wqe;
	u8	num_rnnid_retries;
	u8	num_rsnn_nn_retries;
पूर्ण;


काष्ठा bfa_fcs_lport_scn_s अणु
	bfa_sm_t        sm;		/*  state machine */
	काष्ठा bfa_समयr_s समयr;
	काष्ठा bfa_fcs_lport_s *port;	/*  parent port */
	काष्ठा bfa_fcxp_s *fcxp;
	काष्ठा bfa_fcxp_wqe_s fcxp_wqe;
पूर्ण;


काष्ठा bfa_fcs_lport_fdmi_s अणु
	bfa_sm_t        sm;		/*  state machine */
	काष्ठा bfa_समयr_s समयr;
	काष्ठा bfa_fcs_lport_ms_s *ms;	/*  parent ms */
	काष्ठा bfa_fcxp_s *fcxp;
	काष्ठा bfa_fcxp_wqe_s fcxp_wqe;
	u8	retry_cnt;	/*  retry count */
	u8	rsvd[3];
पूर्ण;


काष्ठा bfa_fcs_lport_ms_s अणु
	bfa_sm_t        sm;		/*  state machine */
	काष्ठा bfa_समयr_s समयr;
	काष्ठा bfa_fcs_lport_s *port;	/*  parent port */
	काष्ठा bfa_fcxp_s *fcxp;
	काष्ठा bfa_fcxp_wqe_s fcxp_wqe;
	काष्ठा bfa_fcs_lport_fdmi_s fdmi;	/*  FDMI component of MS */
	u8         retry_cnt;	/*  retry count */
	u8	rsvd[3];
पूर्ण;


काष्ठा bfa_fcs_lport_fab_s अणु
	काष्ठा bfa_fcs_lport_ns_s ns;	/*  NS component of port */
	काष्ठा bfa_fcs_lport_scn_s scn;	/*  scn component of port */
	काष्ठा bfa_fcs_lport_ms_s ms;	/*  MS component of port */
पूर्ण;

#घोषणा	MAX_ALPA_COUNT	127

काष्ठा bfa_fcs_lport_loop_s अणु
	u8	num_alpa;	/*  Num of ALPA entries in the map */
	u8	alpabm_valid;	/* alpa biपंचांगap valid or not (1 or 0) */
	u8	alpa_pos_map[MAX_ALPA_COUNT]; /*  ALPA Positional Map */
	काष्ठा bfa_fcs_lport_s *port;	/*  parent port */
पूर्ण;

काष्ठा bfa_fcs_lport_n2n_s अणु
	u32        rsvd;
	__be16     reply_oxid;	/*  ox_id from the req flogi to be
					 *used in flogi acc */
	wwn_t           rem_port_wwn;	/*  Attached port's wwn */
पूर्ण;


जोड़ bfa_fcs_lport_topo_u अणु
	काष्ठा bfa_fcs_lport_fab_s pfab;
	काष्ठा bfa_fcs_lport_loop_s ploop;
	काष्ठा bfa_fcs_lport_n2n_s pn2n;
पूर्ण;


काष्ठा bfa_fcs_lport_s अणु
	काष्ठा list_head         qe;	/*  used by port/vport */
	bfa_sm_t               sm;	/*  state machine */
	काष्ठा bfa_fcs_fabric_s *fabric;	/*  parent fabric */
	काष्ठा bfa_lport_cfg_s  port_cfg;	/*  port configuration */
	काष्ठा bfa_समयr_s link_समयr;	/*  समयr क्रम link offline */
	u32        pid:24;	/*  FC address */
	u8         lp_tag;		/*  lport tag */
	u16        num_rports;	/*  Num of r-ports */
	काष्ठा list_head         rport_q; /*  queue of discovered r-ports */
	काष्ठा bfa_fcs_s *fcs;	/*  FCS instance */
	जोड़ bfa_fcs_lport_topo_u port_topo;	/*  fabric/loop/n2n details */
	काष्ठा bfad_port_s *bfad_port;	/*  driver peer instance */
	काष्ठा bfa_fcs_vport_s *vport;	/*  शून्य क्रम base ports */
	काष्ठा bfa_fcxp_s *fcxp;
	काष्ठा bfa_fcxp_wqe_s fcxp_wqe;
	काष्ठा bfa_lport_stats_s stats;
	काष्ठा bfa_wc_s        wc;	/*  रुकोing counter क्रम events */
पूर्ण;
#घोषणा BFA_FCS_GET_HAL_FROM_PORT(port)  (port->fcs->bfa)
#घोषणा BFA_FCS_GET_NS_FROM_PORT(port)  (&port->port_topo.pfab.ns)
#घोषणा BFA_FCS_GET_SCN_FROM_PORT(port)  (&port->port_topo.pfab.scn)
#घोषणा BFA_FCS_GET_MS_FROM_PORT(port)  (&port->port_topo.pfab.ms)
#घोषणा BFA_FCS_GET_FDMI_FROM_PORT(port)  (&port->port_topo.pfab.ms.fdmi)
#घोषणा	BFA_FCS_VPORT_IS_INITIATOR_MODE(port) \
		(port->port_cfg.roles & BFA_LPORT_ROLE_FCP_IM)

/*
 * क्रमward declaration
 */
काष्ठा bfad_vf_s;

क्रमागत bfa_fcs_fabric_type अणु
	BFA_FCS_FABRIC_UNKNOWN = 0,
	BFA_FCS_FABRIC_SWITCHED = 1,
	BFA_FCS_FABRIC_N2N = 2,
	BFA_FCS_FABRIC_LOOP = 3,
पूर्ण;


काष्ठा bfa_fcs_fabric_s अणु
	काष्ठा list_head   qe;		/*  queue element */
	bfa_sm_t	 sm;		/*  state machine */
	काष्ठा bfa_fcs_s *fcs;		/*  FCS instance */
	काष्ठा bfa_fcs_lport_s  bport;	/*  base logical port */
	क्रमागत bfa_fcs_fabric_type fab_type; /*  fabric type */
	क्रमागत bfa_port_type oper_type;	/*  current link topology */
	u8         is_vf;		/*  is भव fabric? */
	u8         is_npiv;	/*  is NPIV supported ? */
	u8         is_auth;	/*  is Security/Auth supported ? */
	u16        bb_credit;	/*  BB credit from fabric */
	u16        vf_id;		/*  भव fabric ID */
	u16        num_vports;	/*  num vports */
	u16        rsvd;
	काष्ठा list_head         vport_q;	/*  queue of भव ports */
	काष्ठा list_head         vf_q;	/*  queue of भव fabrics */
	काष्ठा bfad_vf_s      *vf_drv;	/*  driver vf काष्ठाure */
	काष्ठा bfa_समयr_s link_समयr;	/*  Link Failure समयr. Vport */
	wwn_t           fabric_name;	/*  attached fabric name */
	bfa_boolean_t   auth_reqd;	/*  authentication required	*/
	काष्ठा bfa_समयr_s delay_समयr;	/*  delay समयr		*/
	जोड़ अणु
		u16        swp_vfid;/*  चयन port VF id		*/
	पूर्ण event_arg;
	काष्ठा bfa_wc_s        wc;	/*  रुको counter क्रम delete	*/
	काष्ठा bfa_vf_stats_s	stats;	/*  fabric/vf stats		*/
	काष्ठा bfa_lps_s	*lps;	/*  lport login services	*/
	u8	fabric_ip_addr[BFA_FCS_FABRIC_IPADDR_SZ];
					/*  attached fabric's ip addr  */
	काष्ठा bfa_wc_s stop_wc;	/*  रुको counter क्रम stop */
पूर्ण;

#घोषणा bfa_fcs_fabric_npiv_capable(__f)    ((__f)->is_npiv)
#घोषणा bfa_fcs_fabric_is_चयनed(__f)			\
	((__f)->fab_type == BFA_FCS_FABRIC_SWITCHED)

/*
 *   The design calls क्रम a single implementation of base fabric and vf.
 */
#घोषणा bfa_fcs_vf_t काष्ठा bfa_fcs_fabric_s

काष्ठा bfa_vf_event_s अणु
	u32        undefined;
पूर्ण;

/*
 * @toकरो : need to move to a global config file.
 * Maximum Rports supported per port (physical/logical).
 */
#घोषणा BFA_FCS_MAX_RPORTS_SUPP  256	/* @toकरो : tentative value */

#घोषणा bfa_fcs_lport_t काष्ठा bfa_fcs_lport_s

/*
 * Symbolic Name related defines
 *  Total bytes 255.
 *  Physical Port's symbolic name 128 bytes.
 *  For Vports, Vport's symbolic name is appended to the Physical port's
 *  Symbolic Name.
 *
 *  Physical Port's symbolic name Format : (Total 128 bytes)
 *  Adapter Model number/name : 16 bytes
 *  Driver Version     : 10 bytes
 *  Host Machine Name  : 30 bytes
 *  Host OS Info	   : 44 bytes
 *  Host OS PATCH Info : 16 bytes
 *  ( reमुख्यing 12 bytes reserved to be used क्रम separator)
 */
#घोषणा BFA_FCS_PORT_SYMBNAME_SEPARATOR			" | "

#घोषणा BFA_FCS_PORT_SYMBNAME_MODEL_SZ			16
#घोषणा BFA_FCS_PORT_SYMBNAME_VERSION_SZ		10
#घोषणा BFA_FCS_PORT_SYMBNAME_MACHINENAME_SZ		30
#घोषणा BFA_FCS_PORT_SYMBNAME_OSINFO_SZ			44
#घोषणा BFA_FCS_PORT_SYMBNAME_OSPATCH_SZ		16

/*
 * Get FC port ID क्रम a logical port.
 */
#घोषणा bfa_fcs_lport_get_fcid(_lport)	((_lport)->pid)
#घोषणा bfa_fcs_lport_get_pwwn(_lport)	((_lport)->port_cfg.pwwn)
#घोषणा bfa_fcs_lport_get_nwwn(_lport)	((_lport)->port_cfg.nwwn)
#घोषणा bfa_fcs_lport_get_psym_name(_lport)	((_lport)->port_cfg.sym_name)
#घोषणा bfa_fcs_lport_get_nsym_name(_lport) ((_lport)->port_cfg.node_sym_name)
#घोषणा bfa_fcs_lport_is_initiator(_lport)			\
	((_lport)->port_cfg.roles & BFA_LPORT_ROLE_FCP_IM)
#घोषणा bfa_fcs_lport_get_nrports(_lport)	\
	((_lport) ? (_lport)->num_rports : 0)

अटल अंतरभूत काष्ठा bfad_port_s *
bfa_fcs_lport_get_drvport(काष्ठा bfa_fcs_lport_s *port)
अणु
	वापस port->bfad_port;
पूर्ण

#घोषणा bfa_fcs_lport_get_opertype(_lport)	((_lport)->fabric->oper_type)
#घोषणा bfa_fcs_lport_get_fabric_name(_lport)	((_lport)->fabric->fabric_name)
#घोषणा bfa_fcs_lport_get_fabric_ipaddr(_lport)		\
		((_lport)->fabric->fabric_ip_addr)

/*
 * bfa fcs port खुला functions
 */

bfa_boolean_t   bfa_fcs_lport_is_online(काष्ठा bfa_fcs_lport_s *port);
काष्ठा bfa_fcs_lport_s *bfa_fcs_get_base_port(काष्ठा bfa_fcs_s *fcs);
व्योम bfa_fcs_lport_get_rport_quals(काष्ठा bfa_fcs_lport_s *port,
			काष्ठा bfa_rport_qualअगरier_s rport[], पूर्णांक *nrports);
wwn_t bfa_fcs_lport_get_rport(काष्ठा bfa_fcs_lport_s *port, wwn_t wwn,
			      पूर्णांक index, पूर्णांक nrports, bfa_boolean_t bwwn);

काष्ठा bfa_fcs_lport_s *bfa_fcs_lookup_port(काष्ठा bfa_fcs_s *fcs,
					    u16 vf_id, wwn_t lpwwn);

व्योम bfa_fcs_lport_set_symname(काष्ठा bfa_fcs_lport_s *port, अक्षर *symname);
व्योम bfa_fcs_lport_get_info(काष्ठा bfa_fcs_lport_s *port,
			    काष्ठा bfa_lport_info_s *port_info);
व्योम bfa_fcs_lport_get_attr(काष्ठा bfa_fcs_lport_s *port,
			    काष्ठा bfa_lport_attr_s *port_attr);
व्योम bfa_fcs_lport_get_stats(काष्ठा bfa_fcs_lport_s *fcs_port,
			     काष्ठा bfa_lport_stats_s *port_stats);
व्योम bfa_fcs_lport_clear_stats(काष्ठा bfa_fcs_lport_s *fcs_port);
क्रमागत bfa_port_speed bfa_fcs_lport_get_rport_max_speed(
			काष्ठा bfa_fcs_lport_s *port);

/* MS FCS routines */
व्योम bfa_fcs_lport_ms_init(काष्ठा bfa_fcs_lport_s *port);
व्योम bfa_fcs_lport_ms_offline(काष्ठा bfa_fcs_lport_s *port);
व्योम bfa_fcs_lport_ms_online(काष्ठा bfa_fcs_lport_s *port);
व्योम bfa_fcs_lport_ms_fabric_rscn(काष्ठा bfa_fcs_lport_s *port);

/* FDMI FCS routines */
व्योम bfa_fcs_lport_fdmi_init(काष्ठा bfa_fcs_lport_ms_s *ms);
व्योम bfa_fcs_lport_fdmi_offline(काष्ठा bfa_fcs_lport_ms_s *ms);
व्योम bfa_fcs_lport_fdmi_online(काष्ठा bfa_fcs_lport_ms_s *ms);
व्योम bfa_fcs_lport_uf_recv(काष्ठा bfa_fcs_lport_s *lport, काष्ठा fchs_s *fchs,
				     u16 len);
व्योम bfa_fcs_lport_attach(काष्ठा bfa_fcs_lport_s *lport, काष्ठा bfa_fcs_s *fcs,
			u16 vf_id, काष्ठा bfa_fcs_vport_s *vport);
व्योम bfa_fcs_lport_init(काष्ठा bfa_fcs_lport_s *lport,
				काष्ठा bfa_lport_cfg_s *port_cfg);
व्योम            bfa_fcs_lport_online(काष्ठा bfa_fcs_lport_s *port);
व्योम            bfa_fcs_lport_offline(काष्ठा bfa_fcs_lport_s *port);
व्योम            bfa_fcs_lport_delete(काष्ठा bfa_fcs_lport_s *port);
व्योम		bfa_fcs_lport_stop(काष्ठा bfa_fcs_lport_s *port);
काष्ठा bfa_fcs_rport_s *bfa_fcs_lport_get_rport_by_pid(
		काष्ठा bfa_fcs_lport_s *port, u32 pid);
काष्ठा bfa_fcs_rport_s *bfa_fcs_lport_get_rport_by_old_pid(
		काष्ठा bfa_fcs_lport_s *port, u32 pid);
काष्ठा bfa_fcs_rport_s *bfa_fcs_lport_get_rport_by_pwwn(
		काष्ठा bfa_fcs_lport_s *port, wwn_t pwwn);
काष्ठा bfa_fcs_rport_s *bfa_fcs_lport_get_rport_by_nwwn(
		काष्ठा bfa_fcs_lport_s *port, wwn_t nwwn);
काष्ठा bfa_fcs_rport_s *bfa_fcs_lport_get_rport_by_qualअगरier(
		काष्ठा bfa_fcs_lport_s *port, wwn_t pwwn, u32 pid);
व्योम            bfa_fcs_lport_add_rport(काष्ठा bfa_fcs_lport_s *port,
				       काष्ठा bfa_fcs_rport_s *rport);
व्योम            bfa_fcs_lport_del_rport(काष्ठा bfa_fcs_lport_s *port,
				       काष्ठा bfa_fcs_rport_s *rport);
व्योम            bfa_fcs_lport_ns_init(काष्ठा bfa_fcs_lport_s *vport);
व्योम            bfa_fcs_lport_ns_offline(काष्ठा bfa_fcs_lport_s *vport);
व्योम            bfa_fcs_lport_ns_online(काष्ठा bfa_fcs_lport_s *vport);
व्योम            bfa_fcs_lport_ns_query(काष्ठा bfa_fcs_lport_s *port);
व्योम		bfa_fcs_lport_ns_util_send_rspn_id(व्योम *cbarg,
				काष्ठा bfa_fcxp_s *fcxp_alloced);
व्योम            bfa_fcs_lport_scn_init(काष्ठा bfa_fcs_lport_s *vport);
व्योम            bfa_fcs_lport_scn_offline(काष्ठा bfa_fcs_lport_s *vport);
व्योम            bfa_fcs_lport_fab_scn_online(काष्ठा bfa_fcs_lport_s *vport);
व्योम            bfa_fcs_lport_scn_process_rscn(काष्ठा bfa_fcs_lport_s *port,
					      काष्ठा fchs_s *rx_frame, u32 len);
व्योम		bfa_fcs_lport_lip_scn_online(bfa_fcs_lport_t *port);

काष्ठा bfa_fcs_vport_s अणु
	काष्ठा list_head		qe;		/*  queue elem	*/
	bfa_sm_t		sm;		/*  state machine	*/
	bfa_fcs_lport_t		lport;		/*  logical port	*/
	काष्ठा bfa_समयr_s	समयr;
	काष्ठा bfad_vport_s	*vport_drv;	/*  Driver निजी	*/
	काष्ठा bfa_vport_stats_s vport_stats;	/*  vport statistics	*/
	काष्ठा bfa_lps_s	*lps;		/*  Lport login service*/
	पूर्णांक			fdisc_retries;
पूर्ण;

#घोषणा bfa_fcs_vport_get_port(vport)			\
	((काष्ठा bfa_fcs_lport_s  *)(&vport->port))

/*
 * bfa fcs vport खुला functions
 */
bfa_status_t bfa_fcs_vport_create(काष्ठा bfa_fcs_vport_s *vport,
				  काष्ठा bfa_fcs_s *fcs, u16 vf_id,
				  काष्ठा bfa_lport_cfg_s *port_cfg,
				  काष्ठा bfad_vport_s *vport_drv);
bfa_status_t bfa_fcs_pbc_vport_create(काष्ठा bfa_fcs_vport_s *vport,
				      काष्ठा bfa_fcs_s *fcs, u16 vf_id,
				      काष्ठा bfa_lport_cfg_s *port_cfg,
				      काष्ठा bfad_vport_s *vport_drv);
bfa_boolean_t bfa_fcs_is_pbc_vport(काष्ठा bfa_fcs_vport_s *vport);
bfa_status_t bfa_fcs_vport_delete(काष्ठा bfa_fcs_vport_s *vport);
bfa_status_t bfa_fcs_vport_start(काष्ठा bfa_fcs_vport_s *vport);
bfa_status_t bfa_fcs_vport_stop(काष्ठा bfa_fcs_vport_s *vport);
व्योम bfa_fcs_vport_get_attr(काष्ठा bfa_fcs_vport_s *vport,
			    काष्ठा bfa_vport_attr_s *vport_attr);
काष्ठा bfa_fcs_vport_s *bfa_fcs_vport_lookup(काष्ठा bfa_fcs_s *fcs,
					     u16 vf_id, wwn_t vpwwn);
व्योम bfa_fcs_vport_cleanup(काष्ठा bfa_fcs_vport_s *vport);
व्योम bfa_fcs_vport_online(काष्ठा bfa_fcs_vport_s *vport);
व्योम bfa_fcs_vport_offline(काष्ठा bfa_fcs_vport_s *vport);
व्योम bfa_fcs_vport_delete_comp(काष्ठा bfa_fcs_vport_s *vport);
व्योम bfa_fcs_vport_fcs_delete(काष्ठा bfa_fcs_vport_s *vport);
व्योम bfa_fcs_vport_fcs_stop(काष्ठा bfa_fcs_vport_s *vport);
व्योम bfa_fcs_vport_stop_comp(काष्ठा bfa_fcs_vport_s *vport);

#घोषणा BFA_FCS_RPORT_DEF_DEL_TIMEOUT	90	/* in secs */
#घोषणा BFA_FCS_RPORT_MAX_RETRIES	(5)

/*
 * क्रमward declarations
 */
काष्ठा bfad_rport_s;

काष्ठा bfa_fcs_itnim_s;
काष्ठा bfa_fcs_tin_s;
काष्ठा bfa_fcs_iprp_s;

/* Rport Features (RPF) */
काष्ठा bfa_fcs_rpf_s अणु
	bfa_sm_t	sm;	/*  state machine */
	काष्ठा bfa_fcs_rport_s *rport;	/*  parent rport */
	काष्ठा bfa_समयr_s	समयr;	/*  general purpose समयr */
	काष्ठा bfa_fcxp_s	*fcxp;	/*  FCXP needed क्रम discarding */
	काष्ठा bfa_fcxp_wqe_s	fcxp_wqe; /*  fcxp रुको queue element */
	पूर्णांक	rpsc_retries;	/*  max RPSC retry attempts */
	क्रमागत bfa_port_speed	rpsc_speed;
	/*  Current Speed from RPSC. O अगर RPSC fails */
	क्रमागत bfa_port_speed	asचिन्हित_speed;
	/*
	 * Speed asचिन्हित by the user.  will be used अगर RPSC is
	 * not supported by the rport.
	 */
पूर्ण;

काष्ठा bfa_fcs_rport_s अणु
	काष्ठा list_head	qe;	/*  used by port/vport */
	काष्ठा bfa_fcs_lport_s *port;	/*  parent FCS port */
	काष्ठा bfa_fcs_s	*fcs;	/*  fcs instance */
	काष्ठा bfad_rport_s	*rp_drv;	/*  driver peer instance */
	u32	pid;	/*  port ID of rport */
	u32	old_pid;	/* PID beक्रमe rport goes offline */
	u16	maxfrsize;	/*  maximum frame size */
	__be16	reply_oxid;	/*  OX_ID of inbound requests */
	क्रमागत fc_cos	fc_cos;	/*  FC classes of service supp */
	bfa_boolean_t	cisc;	/*  CISC capable device */
	bfa_boolean_t	prlo;	/*  processing prlo or LOGO */
	bfa_boolean_t	plogi_pending;	/* Rx Plogi Pending */
	wwn_t	pwwn;	/*  port wwn of rport */
	wwn_t	nwwn;	/*  node wwn of rport */
	काष्ठा bfa_rport_symname_s psym_name; /*  port symbolic name  */
	bfa_sm_t	sm;		/*  state machine */
	काष्ठा bfa_समयr_s समयr;	/*  general purpose समयr */
	काष्ठा bfa_fcs_itnim_s *itnim;	/*  ITN initiator mode role */
	काष्ठा bfa_fcs_tin_s *tin;	/*  ITN initiator mode role */
	काष्ठा bfa_fcs_iprp_s *iprp;	/*  IP/FC role */
	काष्ठा bfa_rport_s *bfa_rport;	/*  BFA Rport */
	काष्ठा bfa_fcxp_s *fcxp;	/*  FCXP needed क्रम discarding */
	पूर्णांक	plogi_retries;	/*  max plogi retry attempts */
	पूर्णांक	ns_retries;	/*  max NS query retry attempts */
	काष्ठा bfa_fcxp_wqe_s	fcxp_wqe; /*  fcxp रुको queue element */
	काष्ठा bfa_rport_stats_s stats;	/*  rport stats */
	क्रमागत bfa_rport_function	scsi_function;  /*  Initiator/Target */
	काष्ठा bfa_fcs_rpf_s rpf;	/* Rport features module */
	bfa_boolean_t   scn_online;	/* SCN online flag */
पूर्ण;

अटल अंतरभूत काष्ठा bfa_rport_s *
bfa_fcs_rport_get_halrport(काष्ठा bfa_fcs_rport_s *rport)
अणु
	वापस rport->bfa_rport;
पूर्ण

/*
 * bfa fcs rport API functions
 */
व्योम bfa_fcs_rport_get_attr(काष्ठा bfa_fcs_rport_s *rport,
			काष्ठा bfa_rport_attr_s *attr);
काष्ठा bfa_fcs_rport_s *bfa_fcs_rport_lookup(काष्ठा bfa_fcs_lport_s *port,
					     wwn_t rpwwn);
काष्ठा bfa_fcs_rport_s *bfa_fcs_rport_lookup_by_nwwn(
	काष्ठा bfa_fcs_lport_s *port, wwn_t rnwwn);
व्योम bfa_fcs_rport_set_del_समयout(u8 rport_पंचांगo);
व्योम bfa_fcs_rport_set_max_logins(u32 max_logins);
व्योम bfa_fcs_rport_uf_recv(काष्ठा bfa_fcs_rport_s *rport,
	 काष्ठा fchs_s *fchs, u16 len);
व्योम bfa_fcs_rport_scn(काष्ठा bfa_fcs_rport_s *rport);

काष्ठा bfa_fcs_rport_s *bfa_fcs_rport_create(काष्ठा bfa_fcs_lport_s *port,
	 u32 pid);
व्योम bfa_fcs_rport_start(काष्ठा bfa_fcs_lport_s *port, काष्ठा fchs_s *rx_fchs,
			 काष्ठा fc_logi_s *plogi_rsp);
व्योम bfa_fcs_rport_plogi_create(काष्ठा bfa_fcs_lport_s *port,
				काष्ठा fchs_s *rx_fchs,
				काष्ठा fc_logi_s *plogi);
व्योम bfa_fcs_rport_plogi(काष्ठा bfa_fcs_rport_s *rport, काष्ठा fchs_s *fchs,
			 काष्ठा fc_logi_s *plogi);
व्योम bfa_fcs_rport_prlo(काष्ठा bfa_fcs_rport_s *rport, __be16 ox_id);

व्योम bfa_fcs_rport_itnपंचांग_ack(काष्ठा bfa_fcs_rport_s *rport);
व्योम bfa_fcs_rport_fcpपंचांग_offline_करोne(काष्ठा bfa_fcs_rport_s *rport);
पूर्णांक  bfa_fcs_rport_get_state(काष्ठा bfa_fcs_rport_s *rport);
काष्ठा bfa_fcs_rport_s *bfa_fcs_rport_create_by_wwn(
			काष्ठा bfa_fcs_lport_s *port, wwn_t wwn);
व्योम  bfa_fcs_rpf_init(काष्ठा bfa_fcs_rport_s *rport);
व्योम  bfa_fcs_rpf_rport_online(काष्ठा bfa_fcs_rport_s *rport);
व्योम  bfa_fcs_rpf_rport_offline(काष्ठा bfa_fcs_rport_s *rport);

/*
 * क्रमward declarations
 */
काष्ठा bfad_itnim_s;

काष्ठा bfa_fcs_itnim_s अणु
	bfa_sm_t		sm;		/*  state machine */
	काष्ठा bfa_fcs_rport_s	*rport;		/*  parent remote rport  */
	काष्ठा bfad_itnim_s	*itnim_drv;	/*  driver peer instance */
	काष्ठा bfa_fcs_s	*fcs;		/*  fcs instance	*/
	काष्ठा bfa_समयr_s	समयr;		/*  समयr functions	*/
	काष्ठा bfa_itnim_s	*bfa_itnim;	/*  BFA itnim काष्ठा	*/
	u32		prli_retries;	/*  max prli retry attempts */
	bfa_boolean_t		seq_rec;	/*  seq recovery support */
	bfa_boolean_t		rec_support;	/*  REC supported	*/
	bfa_boolean_t		conf_comp;	/*  FCP_CONF	support */
	bfa_boolean_t		task_retry_id;	/*  task retry id supp	*/
	काष्ठा bfa_fcxp_wqe_s	fcxp_wqe;	/*  रुको qelem क्रम fcxp  */
	काष्ठा bfa_fcxp_s	*fcxp;		/*  FCXP in use	*/
	काष्ठा bfa_itnim_stats_s	stats;	/*  itn statistics	*/
पूर्ण;
#घोषणा bfa_fcs_fcxp_alloc(__fcs, __req)				\
	bfa_fcxp_req_rsp_alloc(शून्य, (__fcs)->bfa, 0, 0,		\
			       शून्य, शून्य, शून्य, शून्य, __req)
#घोषणा bfa_fcs_fcxp_alloc_रुको(__bfa, __wqe, __alloc_cbfn,		\
				__alloc_cbarg, __req)			\
	bfa_fcxp_req_rsp_alloc_रुको(__bfa, __wqe, __alloc_cbfn,		\
		__alloc_cbarg, शून्य, 0, 0, शून्य, शून्य, शून्य, शून्य, __req)

अटल अंतरभूत काष्ठा bfad_port_s *
bfa_fcs_itnim_get_drvport(काष्ठा bfa_fcs_itnim_s *itnim)
अणु
	वापस itnim->rport->port->bfad_port;
पूर्ण


अटल अंतरभूत काष्ठा bfa_fcs_lport_s *
bfa_fcs_itnim_get_port(काष्ठा bfa_fcs_itnim_s *itnim)
अणु
	वापस itnim->rport->port;
पूर्ण


अटल अंतरभूत wwn_t
bfa_fcs_itnim_get_nwwn(काष्ठा bfa_fcs_itnim_s *itnim)
अणु
	वापस itnim->rport->nwwn;
पूर्ण


अटल अंतरभूत wwn_t
bfa_fcs_itnim_get_pwwn(काष्ठा bfa_fcs_itnim_s *itnim)
अणु
	वापस itnim->rport->pwwn;
पूर्ण


अटल अंतरभूत u32
bfa_fcs_itnim_get_fcid(काष्ठा bfa_fcs_itnim_s *itnim)
अणु
	वापस itnim->rport->pid;
पूर्ण


अटल अंतरभूत	u32
bfa_fcs_itnim_get_maxfrsize(काष्ठा bfa_fcs_itnim_s *itnim)
अणु
	वापस itnim->rport->maxfrsize;
पूर्ण


अटल अंतरभूत	क्रमागत fc_cos
bfa_fcs_itnim_get_cos(काष्ठा bfa_fcs_itnim_s *itnim)
अणु
	वापस itnim->rport->fc_cos;
पूर्ण


अटल अंतरभूत काष्ठा bfad_itnim_s *
bfa_fcs_itnim_get_drvitn(काष्ठा bfa_fcs_itnim_s *itnim)
अणु
	वापस itnim->itnim_drv;
पूर्ण


अटल अंतरभूत काष्ठा bfa_itnim_s *
bfa_fcs_itnim_get_halitn(काष्ठा bfa_fcs_itnim_s *itnim)
अणु
	वापस itnim->bfa_itnim;
पूर्ण

/*
 * bfa fcs FCP Initiator mode API functions
 */
व्योम bfa_fcs_itnim_get_attr(काष्ठा bfa_fcs_itnim_s *itnim,
			    काष्ठा bfa_itnim_attr_s *attr);
व्योम bfa_fcs_itnim_get_stats(काष्ठा bfa_fcs_itnim_s *itnim,
			     काष्ठा bfa_itnim_stats_s *stats);
काष्ठा bfa_fcs_itnim_s *bfa_fcs_itnim_lookup(काष्ठा bfa_fcs_lport_s *port,
					     wwn_t rpwwn);
bfa_status_t bfa_fcs_itnim_attr_get(काष्ठा bfa_fcs_lport_s *port, wwn_t rpwwn,
				    काष्ठा bfa_itnim_attr_s *attr);
bfa_status_t bfa_fcs_itnim_stats_get(काष्ठा bfa_fcs_lport_s *port, wwn_t rpwwn,
				     काष्ठा bfa_itnim_stats_s *stats);
bfa_status_t bfa_fcs_itnim_stats_clear(काष्ठा bfa_fcs_lport_s *port,
				       wwn_t rpwwn);
काष्ठा bfa_fcs_itnim_s *bfa_fcs_itnim_create(काष्ठा bfa_fcs_rport_s *rport);
व्योम bfa_fcs_itnim_delete(काष्ठा bfa_fcs_itnim_s *itnim);
व्योम bfa_fcs_itnim_rport_offline(काष्ठा bfa_fcs_itnim_s *itnim);
व्योम bfa_fcs_itnim_brp_online(काष्ठा bfa_fcs_itnim_s *itnim);
bfa_status_t bfa_fcs_itnim_get_online_state(काष्ठा bfa_fcs_itnim_s *itnim);
व्योम bfa_fcs_itnim_is_initiator(काष्ठा bfa_fcs_itnim_s *itnim);
व्योम bfa_fcs_fcpim_uf_recv(काष्ठा bfa_fcs_itnim_s *itnim,
			काष्ठा fchs_s *fchs, u16 len);

#घोषणा BFA_FCS_FDMI_SUPP_SPEEDS_4G	(FDMI_TRANS_SPEED_1G  |	\
				FDMI_TRANS_SPEED_2G |		\
				FDMI_TRANS_SPEED_4G)

#घोषणा BFA_FCS_FDMI_SUPP_SPEEDS_8G	(FDMI_TRANS_SPEED_1G  |	\
				FDMI_TRANS_SPEED_2G |		\
				FDMI_TRANS_SPEED_4G |		\
				FDMI_TRANS_SPEED_8G)

#घोषणा BFA_FCS_FDMI_SUPP_SPEEDS_16G	(FDMI_TRANS_SPEED_2G  |	\
				FDMI_TRANS_SPEED_4G |		\
				FDMI_TRANS_SPEED_8G |		\
				FDMI_TRANS_SPEED_16G)

#घोषणा BFA_FCS_FDMI_SUPP_SPEEDS_10G	FDMI_TRANS_SPEED_10G

#घोषणा BFA_FCS_FDMI_VENDOR_INFO_LEN    8
#घोषणा BFA_FCS_FDMI_FC4_TYPE_LEN       32

/*
 * HBA Attribute Block : BFA पूर्णांकernal representation. Note : Some variable
 * sizes have been trimmed to suit BFA For Ex : Model will be "QLogic ". Based
 * on this the size has been reduced to 16 bytes from the standard's 64 bytes.
 */
काष्ठा bfa_fcs_fdmi_hba_attr_s अणु
	wwn_t           node_name;
	u8         manufacturer[64];
	u8         serial_num[64];
	u8         model[16];
	u8         model_desc[128];
	u8         hw_version[8];
	u8         driver_version[BFA_VERSION_LEN];
	u8         option_rom_ver[BFA_VERSION_LEN];
	u8         fw_version[BFA_VERSION_LEN];
	u8         os_name[256];
	__be32        max_ct_pyld;
	काष्ठा      bfa_lport_symname_s node_sym_name;
	u8     venकरोr_info[BFA_FCS_FDMI_VENDOR_INFO_LEN];
	__be32    num_ports;
	wwn_t       fabric_name;
	u8     bios_ver[BFA_VERSION_LEN];
पूर्ण;

/*
 * Port Attribute Block
 */
काष्ठा bfa_fcs_fdmi_port_attr_s अणु
	u8         supp_fc4_types[BFA_FCS_FDMI_FC4_TYPE_LEN];
	__be32        supp_speed;	/* supported speed */
	__be32        curr_speed;	/* current Speed */
	__be32        max_frm_size;	/* max frame size */
	u8         os_device_name[256];	/* OS device Name */
	u8         host_name[256];	/* host name */
	wwn_t       port_name;
	wwn_t       node_name;
	काष्ठा      bfa_lport_symname_s port_sym_name;
	__be32    port_type;
	क्रमागत fc_cos    scos;
	wwn_t       port_fabric_name;
	u8     port_act_fc4_type[BFA_FCS_FDMI_FC4_TYPE_LEN];
	__be32    port_state;
	__be32    num_ports;
पूर्ण;

काष्ठा bfa_fcs_stats_s अणु
	काष्ठा अणु
		u32	untagged; /*  untagged receive frames */
		u32	tagged;	/*  tagged receive frames */
		u32	vfid_unknown;	/*  VF id is unknown */
	पूर्ण uf;
पूर्ण;

काष्ठा bfa_fcs_driver_info_s अणु
	u8	 version[BFA_VERSION_LEN];		/* Driver Version */
	u8	 host_machine_name[BFA_FCS_OS_STR_LEN];
	u8	 host_os_name[BFA_FCS_OS_STR_LEN]; /* OS name and version */
	u8	 host_os_patch[BFA_FCS_OS_STR_LEN]; /* patch or service pack */
	u8	 os_device_name[BFA_FCS_OS_STR_LEN]; /* Driver Device Name */
पूर्ण;

काष्ठा bfa_fcs_s अणु
	काष्ठा bfa_s	  *bfa;	/*  corresponding BFA bfa instance */
	काष्ठा bfad_s	      *bfad; /*  corresponding BDA driver instance */
	काष्ठा bfa_trc_mod_s  *trcmod;	/*  tracing module */
	bfa_boolean_t	vf_enabled;	/*  VF mode is enabled */
	bfa_boolean_t	fdmi_enabled;	/*  FDMI is enabled */
	bfa_boolean_t min_cfg;		/* min cfg enabled/disabled */
	u16	port_vfid;	/*  port शेष VF ID */
	काष्ठा bfa_fcs_driver_info_s driver_info;
	काष्ठा bfa_fcs_fabric_s fabric; /*  base fabric state machine */
	काष्ठा bfa_fcs_stats_s	stats;	/*  FCS statistics */
	काष्ठा bfa_wc_s		wc;	/*  रुकोing counter */
	पूर्णांक			fcs_aen_seq;
	u32		num_rport_logins;
पूर्ण;

/*
 *  fcs_fabric_sm fabric state machine functions
 */

/*
 * Fabric state machine events
 */
क्रमागत bfa_fcs_fabric_event अणु
	BFA_FCS_FABRIC_SM_CREATE        = 1,    /*  create from driver        */
	BFA_FCS_FABRIC_SM_DELETE        = 2,    /*  delete from driver        */
	BFA_FCS_FABRIC_SM_LINK_DOWN     = 3,    /*  link करोwn from port      */
	BFA_FCS_FABRIC_SM_LINK_UP       = 4,    /*  link up from port         */
	BFA_FCS_FABRIC_SM_CONT_OP       = 5,    /*  flogi/auth जारी op   */
	BFA_FCS_FABRIC_SM_RETRY_OP      = 6,    /*  flogi/auth retry op      */
	BFA_FCS_FABRIC_SM_NO_FABRIC     = 7,    /*  from flogi/auth           */
	BFA_FCS_FABRIC_SM_PERF_EVFP     = 8,    /*  from flogi/auth           */
	BFA_FCS_FABRIC_SM_ISOLATE       = 9,    /*  from EVFP processing     */
	BFA_FCS_FABRIC_SM_NO_TAGGING    = 10,   /*  no VFT tagging from EVFP */
	BFA_FCS_FABRIC_SM_DELAYED       = 11,   /*  समयout delay event      */
	BFA_FCS_FABRIC_SM_AUTH_FAILED   = 12,   /*  auth failed       */
	BFA_FCS_FABRIC_SM_AUTH_SUCCESS  = 13,   /*  auth successful           */
	BFA_FCS_FABRIC_SM_DELCOMP       = 14,   /*  all vports deleted event */
	BFA_FCS_FABRIC_SM_LOOPBACK      = 15,   /*  Received our own FLOGI   */
	BFA_FCS_FABRIC_SM_START         = 16,   /*  from driver       */
	BFA_FCS_FABRIC_SM_STOP		= 17,	/*  Stop from driver	*/
	BFA_FCS_FABRIC_SM_STOPCOMP	= 18,	/*  Stop completion	*/
	BFA_FCS_FABRIC_SM_LOGOCOMP	= 19,	/*  FLOGO completion	*/
पूर्ण;

/*
 *  fcs_rport_sm FCS rport state machine events
 */

क्रमागत rport_event अणु
	RPSM_EVENT_PLOGI_SEND   = 1,    /*  new rport; start with PLOGI */
	RPSM_EVENT_PLOGI_RCVD   = 2,    /*  Inbound PLOGI from remote port */
	RPSM_EVENT_PLOGI_COMP   = 3,    /*  PLOGI completed to rport    */
	RPSM_EVENT_LOGO_RCVD    = 4,    /*  LOGO from remote device     */
	RPSM_EVENT_LOGO_IMP     = 5,    /*  implicit logo क्रम SLER      */
	RPSM_EVENT_FCXP_SENT    = 6,    /*  Frame from has been sent    */
	RPSM_EVENT_DELETE       = 7,    /*  RPORT delete request        */
	RPSM_EVENT_FAB_SCN	= 8,    /*  state change notअगरication   */
	RPSM_EVENT_ACCEPTED     = 9,    /*  Good response from remote device */
	RPSM_EVENT_FAILED       = 10,   /*  Request to rport failed.    */
	RPSM_EVENT_TIMEOUT      = 11,   /*  Rport SM समयout event      */
	RPSM_EVENT_HCB_ONLINE  = 12,    /*  BFA rport online callback   */
	RPSM_EVENT_HCB_OFFLINE = 13,    /*  BFA rport offline callback  */
	RPSM_EVENT_FC4_OFFLINE = 14,    /*  FC-4 offline complete       */
	RPSM_EVENT_ADDRESS_CHANGE = 15, /*  Rport's PID has changed     */
	RPSM_EVENT_ADDRESS_DISC = 16,   /*  Need to Discover rport's PID */
	RPSM_EVENT_PRLO_RCVD   = 17,    /*  PRLO from remote device     */
	RPSM_EVENT_PLOGI_RETRY = 18,    /*  Retry PLOGI continuously */
	RPSM_EVENT_SCN_OFFLINE = 19,	/* loop scn offline		*/
	RPSM_EVENT_SCN_ONLINE   = 20,	/* loop scn online		*/
	RPSM_EVENT_FC4_FCS_ONLINE = 21, /* FC-4 FCS online complete */
पूर्ण;

/*
 * fcs_itnim_sm FCS itnim state machine events
 */
क्रमागत bfa_fcs_itnim_event अणु
	BFA_FCS_ITNIM_SM_FCS_ONLINE = 1,        /*  rport online event */
	BFA_FCS_ITNIM_SM_OFFLINE = 2,   /*  rport offline */
	BFA_FCS_ITNIM_SM_FRMSENT = 3,   /*  prli frame is sent */
	BFA_FCS_ITNIM_SM_RSP_OK = 4,    /*  good response */
	BFA_FCS_ITNIM_SM_RSP_ERROR = 5, /*  error response */
	BFA_FCS_ITNIM_SM_TIMEOUT = 6,   /*  delay समयout */
	BFA_FCS_ITNIM_SM_HCB_OFFLINE = 7, /*  BFA online callback */
	BFA_FCS_ITNIM_SM_HCB_ONLINE = 8, /*  BFA offline callback */
	BFA_FCS_ITNIM_SM_INITIATOR = 9, /*  rport is initiator */
	BFA_FCS_ITNIM_SM_DELETE = 10,   /*  delete event from rport */
	BFA_FCS_ITNIM_SM_PRLO = 11,     /*  delete event from rport */
	BFA_FCS_ITNIM_SM_RSP_NOT_SUPP = 12, /* cmd not supported rsp */
	BFA_FCS_ITNIM_SM_HAL_ONLINE = 13, /* bfa rport online event */
पूर्ण;

/*
 * bfa fcs API functions
 */
व्योम bfa_fcs_attach(काष्ठा bfa_fcs_s *fcs, काष्ठा bfa_s *bfa,
		    काष्ठा bfad_s *bfad,
		    bfa_boolean_t min_cfg);
व्योम bfa_fcs_init(काष्ठा bfa_fcs_s *fcs);
व्योम bfa_fcs_pbc_vport_init(काष्ठा bfa_fcs_s *fcs);
व्योम bfa_fcs_update_cfg(काष्ठा bfa_fcs_s *fcs);
व्योम bfa_fcs_driver_info_init(काष्ठा bfa_fcs_s *fcs,
			      काष्ठा bfa_fcs_driver_info_s *driver_info);
व्योम bfa_fcs_निकास(काष्ठा bfa_fcs_s *fcs);
व्योम bfa_fcs_stop(काष्ठा bfa_fcs_s *fcs);

/*
 * bfa fcs vf खुला functions
 */
bfa_fcs_vf_t *bfa_fcs_vf_lookup(काष्ठा bfa_fcs_s *fcs, u16 vf_id);
व्योम bfa_fcs_vf_get_ports(bfa_fcs_vf_t *vf, wwn_t vpwwn[], पूर्णांक *nports);

/*
 * fabric रक्षित पूर्णांकerface functions
 */
व्योम bfa_fcs_fabric_modinit(काष्ठा bfa_fcs_s *fcs);
व्योम bfa_fcs_fabric_link_up(काष्ठा bfa_fcs_fabric_s *fabric);
व्योम bfa_fcs_fabric_link_करोwn(काष्ठा bfa_fcs_fabric_s *fabric);
व्योम bfa_fcs_fabric_addvport(काष्ठा bfa_fcs_fabric_s *fabric,
	काष्ठा bfa_fcs_vport_s *vport);
व्योम bfa_fcs_fabric_delvport(काष्ठा bfa_fcs_fabric_s *fabric,
	काष्ठा bfa_fcs_vport_s *vport);
काष्ठा bfa_fcs_vport_s *bfa_fcs_fabric_vport_lookup(
		काष्ठा bfa_fcs_fabric_s *fabric, wwn_t pwwn);
व्योम bfa_fcs_fabric_modstart(काष्ठा bfa_fcs_s *fcs);
व्योम bfa_fcs_fabric_uf_recv(काष्ठा bfa_fcs_fabric_s *fabric,
		काष्ठा fchs_s *fchs, u16 len);
व्योम	bfa_fcs_fabric_psymb_init(काष्ठा bfa_fcs_fabric_s *fabric);
व्योम	bfa_fcs_fabric_nsymb_init(काष्ठा bfa_fcs_fabric_s *fabric);
व्योम bfa_fcs_fabric_set_fabric_name(काष्ठा bfa_fcs_fabric_s *fabric,
	       wwn_t fabric_name);
u16 bfa_fcs_fabric_get_चयन_oui(काष्ठा bfa_fcs_fabric_s *fabric);
व्योम bfa_fcs_fabric_modstop(काष्ठा bfa_fcs_s *fcs);
व्योम bfa_fcs_fabric_sm_online(काष्ठा bfa_fcs_fabric_s *fabric,
			क्रमागत bfa_fcs_fabric_event event);
व्योम bfa_fcs_fabric_sm_loopback(काष्ठा bfa_fcs_fabric_s *fabric,
			क्रमागत bfa_fcs_fabric_event event);
व्योम bfa_fcs_fabric_sm_auth_failed(काष्ठा bfa_fcs_fabric_s *fabric,
			क्रमागत bfa_fcs_fabric_event event);

/*
 * BFA FCS callback पूर्णांकerfaces
 */

/*
 * fcb Main fcs callbacks
 */

काष्ठा bfad_port_s;
काष्ठा bfad_vf_s;
काष्ठा bfad_vport_s;
काष्ठा bfad_rport_s;

/*
 * lport callbacks
 */
काष्ठा bfad_port_s *bfa_fcb_lport_new(काष्ठा bfad_s *bfad,
				      काष्ठा bfa_fcs_lport_s *port,
				      क्रमागत bfa_lport_role roles,
				      काष्ठा bfad_vf_s *vf_drv,
				      काष्ठा bfad_vport_s *vp_drv);

/*
 * vport callbacks
 */
व्योम bfa_fcb_pbc_vport_create(काष्ठा bfad_s *bfad, काष्ठा bfi_pbc_vport_s);

/*
 * rport callbacks
 */
bfa_status_t bfa_fcb_rport_alloc(काष्ठा bfad_s *bfad,
				 काष्ठा bfa_fcs_rport_s **rport,
				 काष्ठा bfad_rport_s **rport_drv);

/*
 * itnim callbacks
 */
पूर्णांक bfa_fcb_itnim_alloc(काष्ठा bfad_s *bfad, काष्ठा bfa_fcs_itnim_s **itnim,
			काष्ठा bfad_itnim_s **itnim_drv);
व्योम bfa_fcb_itnim_मुक्त(काष्ठा bfad_s *bfad,
			काष्ठा bfad_itnim_s *itnim_drv);
व्योम bfa_fcb_itnim_online(काष्ठा bfad_itnim_s *itnim_drv);
व्योम bfa_fcb_itnim_offline(काष्ठा bfad_itnim_s *itnim_drv);

#पूर्ण_अगर /* __BFA_FCS_H__ */
