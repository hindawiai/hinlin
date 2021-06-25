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

#अगर_अघोषित __BFA_DEFS_FCS_H__
#घोषणा __BFA_DEFS_FCS_H__

#समावेश "bfa_fc.h"
#समावेश "bfa_defs_svc.h"

/*
 * VF states
 */
क्रमागत bfa_vf_state अणु
	BFA_VF_UNINIT    = 0,	/*  fabric is not yet initialized */
	BFA_VF_LINK_DOWN = 1,	/*  link is करोwn */
	BFA_VF_FLOGI     = 2,	/*  flogi is in progress */
	BFA_VF_AUTH      = 3,	/*  authentication in progress */
	BFA_VF_NOFABRIC  = 4,	/*  fabric is not present */
	BFA_VF_ONLINE    = 5,	/*  login to fabric is complete */
	BFA_VF_EVFP      = 6,	/*  EVFP is in progress */
	BFA_VF_ISOLATED  = 7,	/*  port isolated due to vf_id mismatch */
पूर्ण;

/*
 * VF statistics
 */
काष्ठा bfa_vf_stats_s अणु
	u32	flogi_sent;	/*  Num FLOGIs sent */
	u32	flogi_rsp_err;	/*  FLOGI response errors */
	u32	flogi_acc_err;	/*  FLOGI accept errors */
	u32	flogi_accepts;	/*  FLOGI accepts received */
	u32	flogi_rejects;	/*  FLOGI rejects received */
	u32	flogi_unknown_rsp; /*  Unknown responses क्रम FLOGI */
	u32	flogi_alloc_रुको; /*  Allocation रुकोs prior to sending FLOGI */
	u32	flogi_rcvd;	/*  FLOGIs received */
	u32	flogi_rejected;	/*  Incoming FLOGIs rejected */
	u32	fabric_onlines;	/*  Internal fabric online notअगरication sent
				 *  to other modules */
	u32	fabric_offlines; /* Internal fabric offline notअगरication sent
				  * to other modules */
	u32	resvd; /*  padding क्रम 64 bit alignment */
पूर्ण;

/*
 * VF attributes वापसed in queries
 */
काष्ठा bfa_vf_attr_s अणु
	क्रमागत bfa_vf_state  state;		/*  VF state */
	u32        rsvd;
	wwn_t           fabric_name;	/*  fabric name */
पूर्ण;

#घोषणा BFA_FCS_MAX_LPORTS 256
#घोषणा BFA_FCS_FABRIC_IPADDR_SZ  16

/*
 * symbolic names क्रम base port/भव port
 */
#घोषणा BFA_SYMNAME_MAXLEN	128	/* 128 bytes */
काष्ठा bfa_lport_symname_s अणु
	अक्षर	    symname[BFA_SYMNAME_MAXLEN];
पूर्ण;

/*
* Roles of FCS port:
 *     - FCP IM and FCP TM roles cannot be enabled together क्रम a FCS port
 *     - Create multiple ports अगर both IM and TM functions required.
 *     - Atleast one role must be specअगरied.
 */
क्रमागत bfa_lport_role अणु
	BFA_LPORT_ROLE_FCP_IM	= 0x01,	/*  FCP initiator role */
	BFA_LPORT_ROLE_FCP_MAX	= BFA_LPORT_ROLE_FCP_IM,
पूर्ण;

/*
 * FCS port configuration.
 */
काष्ठा bfa_lport_cfg_s अणु
	wwn_t	       pwwn;       /*  port wwn */
	wwn_t	       nwwn;       /*  node wwn */
	काष्ठा bfa_lport_symname_s  sym_name;   /*  vm port symbolic name */
	काष्ठा bfa_lport_symname_s node_sym_name; /* Node symbolic name */
	क्रमागत bfa_lport_role roles;      /* FCS port roles */
	u32     rsvd;
	bfa_boolean_t   preboot_vp;  /*  vport created from PBC */
	u8	tag[16];        /* opaque tag from application */
	u8	padding[4];
पूर्ण;

/*
 * FCS port states
 */
क्रमागत bfa_lport_state अणु
	BFA_LPORT_UNINIT  = 0,	/*  PORT is not yet initialized */
	BFA_LPORT_FDISC   = 1,	/*  FDISC is in progress */
	BFA_LPORT_ONLINE  = 2,	/*  login to fabric is complete */
	BFA_LPORT_OFFLINE = 3,	/*  No login to fabric */
पूर्ण;

/*
 * FCS port type.
 */
क्रमागत bfa_lport_type अणु
	BFA_LPORT_TYPE_PHYSICAL = 0,
	BFA_LPORT_TYPE_VIRTUAL,
पूर्ण;

/*
 * FCS port offline reason.
 */
क्रमागत bfa_lport_offline_reason अणु
	BFA_LPORT_OFFLINE_UNKNOWN = 0,
	BFA_LPORT_OFFLINE_LINKDOWN,
	BFA_LPORT_OFFLINE_FAB_UNSUPPORTED,	/*  NPIV not supported by the
	 *    fabric */
	BFA_LPORT_OFFLINE_FAB_NORESOURCES,
	BFA_LPORT_OFFLINE_FAB_LOGOUT,
पूर्ण;

/*
 * FCS lport info.
 */
काष्ठा bfa_lport_info_s अणु
	u8	 port_type;	/* bfa_lport_type_t : physical or
	 * भव */
	u8	 port_state;	/* one of bfa_lport_state values */
	u8	 offline_reason;	/* one of bfa_lport_offline_reason_t
	 * values */
	wwn_t	   port_wwn;
	wwn_t	   node_wwn;

	/*
	 * following 4 feilds are valid क्रम Physical Ports only
	 */
	u32	max_vports_supp;	/* Max supported vports */
	u32	num_vports_inuse;	/* Num of in use vports */
	u32	max_rports_supp;	/* Max supported rports */
	u32	num_rports_inuse;	/* Num of करोscovered rports */

पूर्ण;

/*
 * FCS port statistics
 */
काष्ठा bfa_lport_stats_s अणु
	u32	ns_plogi_sent;
	u32	ns_plogi_rsp_err;
	u32	ns_plogi_acc_err;
	u32	ns_plogi_accepts;
	u32	ns_rejects;	/* NS command rejects */
	u32	ns_plogi_unknown_rsp;
	u32	ns_plogi_alloc_रुको;

	u32	ns_retries;	/* NS command retries */
	u32	ns_समयouts;	/* NS command समयouts */

	u32	ns_rspnid_sent;
	u32	ns_rspnid_accepts;
	u32	ns_rspnid_rsp_err;
	u32	ns_rspnid_rejects;
	u32	ns_rspnid_alloc_रुको;

	u32	ns_rftid_sent;
	u32	ns_rftid_accepts;
	u32	ns_rftid_rsp_err;
	u32	ns_rftid_rejects;
	u32	ns_rftid_alloc_रुको;

	u32	ns_rffid_sent;
	u32	ns_rffid_accepts;
	u32	ns_rffid_rsp_err;
	u32	ns_rffid_rejects;
	u32	ns_rffid_alloc_रुको;

	u32	ns_gidft_sent;
	u32	ns_gidft_accepts;
	u32	ns_gidft_rsp_err;
	u32	ns_gidft_rejects;
	u32	ns_gidft_unknown_rsp;
	u32	ns_gidft_alloc_रुको;

	u32	ns_rnnid_sent;
	u32	ns_rnnid_accepts;
	u32	ns_rnnid_rsp_err;
	u32	ns_rnnid_rejects;
	u32	ns_rnnid_alloc_रुको;

	u32	ns_rsnn_nn_sent;
	u32	ns_rsnn_nn_accepts;
	u32	ns_rsnn_nn_rsp_err;
	u32	ns_rsnn_nn_rejects;
	u32	ns_rsnn_nn_alloc_रुको;

	/*
	 * Mgmt Server stats
	 */
	u32	ms_retries;	/* MS command retries */
	u32	ms_समयouts;	/* MS command समयouts */
	u32	ms_plogi_sent;
	u32	ms_plogi_rsp_err;
	u32	ms_plogi_acc_err;
	u32	ms_plogi_accepts;
	u32	ms_rejects;	/* MS command rejects */
	u32	ms_plogi_unknown_rsp;
	u32	ms_plogi_alloc_रुको;

	u32	num_rscn;	/* Num of RSCN received */
	u32	num_portid_rscn;/* Num portid क्रमmat RSCN
	* received */

	u32	uf_recvs;	/* Unsolicited recv frames	*/
	u32	uf_recv_drops;	/* Dropped received frames	*/

	u32	plogi_rcvd;	/* Received plogi	*/
	u32	prli_rcvd;	/* Received prli	*/
	u32	adisc_rcvd;	/* Received adisc	*/
	u32	prlo_rcvd;	/* Received prlo	*/
	u32	logo_rcvd;	/* Received logo	*/
	u32	rpsc_rcvd;	/* Received rpsc	*/
	u32	un_handled_els_rcvd;	/* Received unhandled ELS	*/
	u32	rport_plogi_समयouts; /* Rport plogi retry समयout count */
	u32	rport_del_max_plogi_retry; /* Deleted rport
					    * (max retry of plogi) */
पूर्ण;

/*
 * BFA port attribute वापसed in queries
 */
काष्ठा bfa_lport_attr_s अणु
	क्रमागत bfa_lport_state state;	/*  port state */
	u32	 pid;	/*  port ID */
	काष्ठा bfa_lport_cfg_s   port_cfg;	/*  port configuration */
	क्रमागत bfa_port_type port_type;	/*  current topology */
	u32	 loopback;	/*  cable is बाह्यally looped back */
	wwn_t	fabric_name; /*  attached चयन's nwwn */
	u8	fabric_ip_addr[BFA_FCS_FABRIC_IPADDR_SZ]; /*  attached
	* fabric's ip addr */
	mac_t	   fpma_mac;	/*  Lport's FPMA Mac address */
	u16	authfail;	/*  auth failed state */
पूर्ण;


/*
 * VPORT states
 */
क्रमागत bfa_vport_state अणु
	BFA_FCS_VPORT_UNINIT		= 0,
	BFA_FCS_VPORT_CREATED		= 1,
	BFA_FCS_VPORT_OFFLINE		= 1,
	BFA_FCS_VPORT_FDISC_SEND	= 2,
	BFA_FCS_VPORT_FDISC		= 3,
	BFA_FCS_VPORT_FDISC_RETRY	= 4,
	BFA_FCS_VPORT_FDISC_RSP_WAIT	= 5,
	BFA_FCS_VPORT_ONLINE		= 6,
	BFA_FCS_VPORT_DELETING		= 7,
	BFA_FCS_VPORT_CLEANUP		= 8,
	BFA_FCS_VPORT_LOGO_SEND		= 9,
	BFA_FCS_VPORT_LOGO		= 10,
	BFA_FCS_VPORT_ERROR		= 11,
	BFA_FCS_VPORT_MAX_STATE,
पूर्ण;

/*
 * vport statistics
 */
काष्ठा bfa_vport_stats_s अणु
	काष्ठा bfa_lport_stats_s port_stats;	/*  base class (port) stats */
	/*
	 * TODO - हटाओ
	 */

	u32        fdisc_sent;	/*  num fdisc sent */
	u32        fdisc_accepts;	/*  fdisc accepts */
	u32        fdisc_retries;	/*  fdisc retries */
	u32        fdisc_समयouts;	/*  fdisc समयouts */
	u32        fdisc_rsp_err;	/*  fdisc response error */
	u32        fdisc_acc_bad;	/*  bad fdisc accepts */
	u32        fdisc_rejects;	/*  fdisc rejects */
	u32        fdisc_unknown_rsp;
	/*
	 *!< fdisc rsp unknown error
	 */
	u32        fdisc_alloc_रुको;/*  fdisc req (fcxp)alloc रुको */

	u32        logo_alloc_रुको;/*  logo req (fcxp) alloc रुको */
	u32        logo_sent;	/*  logo sent */
	u32        logo_accepts;	/*  logo accepts */
	u32        logo_rejects;	/*  logo rejects */
	u32        logo_rsp_err;	/*  logo rsp errors */
	u32        logo_unknown_rsp;
			/*  logo rsp unknown errors */

	u32        fab_no_npiv;	/*  fabric करोes not support npiv */

	u32        fab_offline;	/*  offline events from fab SM */
	u32        fab_online;	/*  online events from fab SM */
	u32        fab_cleanup;	/*  cleanup request from fab SM */
	u32        rsvd;
पूर्ण;

/*
 * BFA vport attribute वापसed in queries
 */
काष्ठा bfa_vport_attr_s अणु
	काष्ठा bfa_lport_attr_s   port_attr; /*  base class (port) attributes */
	क्रमागत bfa_vport_state vport_state; /*  vport state */
	u32          rsvd;
पूर्ण;

/*
 * FCS remote port states
 */
क्रमागत bfa_rport_state अणु
	BFA_RPORT_UNINIT	= 0,	/*  PORT is not yet initialized */
	BFA_RPORT_OFFLINE	= 1,	/*  rport is offline */
	BFA_RPORT_PLOGI		= 2,	/*  PLOGI to rport is in progress */
	BFA_RPORT_ONLINE	= 3,	/*  login to rport is complete */
	BFA_RPORT_PLOGI_RETRY	= 4,	/*  retrying login to rport */
	BFA_RPORT_NSQUERY	= 5,	/*  nameserver query */
	BFA_RPORT_ADISC		= 6,	/*  ADISC authentication */
	BFA_RPORT_LOGO		= 7,	/*  logging out with rport */
	BFA_RPORT_LOGORCV	= 8,	/*  handling LOGO from rport */
	BFA_RPORT_NSDISC	= 9,	/*  re-discover rport */
पूर्ण;

/*
 *  Rport Scsi Function : Initiator/Target.
 */
क्रमागत bfa_rport_function अणु
	BFA_RPORT_INITIATOR	= 0x01,	/*  SCSI Initiator	*/
	BFA_RPORT_TARGET	= 0x02,	/*  SCSI Target	*/
पूर्ण;

/*
 * port/node symbolic names क्रम rport
 */
#घोषणा BFA_RPORT_SYMNAME_MAXLEN	255
काष्ठा bfa_rport_symname_s अणु
	अक्षर            symname[BFA_RPORT_SYMNAME_MAXLEN];
पूर्ण;

/*
 * FCS remote port statistics
 */
काष्ठा bfa_rport_stats_s अणु
	u32        offlines;           /*  remote port offline count  */
	u32        onlines;            /*  remote port online count   */
	u32        rscns;              /*  RSCN affecting rport       */
	u32        plogis;		    /*  plogis sent                */
	u32        plogi_accs;	    /*  plogi accepts              */
	u32        plogi_समयouts;	    /*  plogi समयouts             */
	u32        plogi_rejects;	    /*  rcvd plogi rejects         */
	u32        plogi_failed;	    /*  local failure              */
	u32        plogi_rcvd;	    /*  plogis rcvd                */
	u32        prli_rcvd;          /*  inbound PRLIs              */
	u32        adisc_rcvd;         /*  ADISCs received            */
	u32        adisc_rejects;      /*  recvd  ADISC rejects       */
	u32        adisc_sent;         /*  ADISC requests sent        */
	u32        adisc_accs;         /*  ADISC accepted by rport    */
	u32        adisc_failed;       /*  ADISC failed (no response) */
	u32        adisc_rejected;     /*  ADISC rejected by us    */
	u32        logos;              /*  logos sent                 */
	u32        logo_accs;          /*  LOGO accepts from rport    */
	u32        logo_failed;        /*  LOGO failures              */
	u32        logo_rejected;      /*  LOGO rejects from rport    */
	u32        logo_rcvd;          /*  LOGO from remote port      */

	u32        rpsc_rcvd;         /*  RPSC received            */
	u32        rpsc_rejects;      /*  recvd  RPSC rejects       */
	u32        rpsc_sent;         /*  RPSC requests sent        */
	u32        rpsc_accs;         /*  RPSC accepted by rport    */
	u32        rpsc_failed;       /*  RPSC failed (no response) */
	u32        rpsc_rejected;     /*  RPSC rejected by us    */

	u32	rjt_insuff_res;	/*  LS RJT with insuff resources */
	काष्ठा bfa_rport_hal_stats_s	hal_stats;  /*  BFA rport stats    */
पूर्ण;

/*
 * FCS remote port attributes वापसed in queries
 */
काष्ठा bfa_rport_attr_s अणु
	wwn_t		nwwn;	/*  node wwn */
	wwn_t		pwwn;	/*  port wwn */
	क्रमागत fc_cos cos_supported;	/*  supported class of services */
	u32		pid;	/*  port ID */
	u32		df_sz;	/*  Max payload size */
	क्रमागत bfa_rport_state	state;	/*  Rport State machine state */
	क्रमागत fc_cos	fc_cos;	/*  FC classes of services */
	bfa_boolean_t	cisc;	/*  CISC capable device */
	काष्ठा bfa_rport_symname_s symname; /*  Symbolic Name */
	क्रमागत bfa_rport_function	scsi_function; /*  Initiator/Target */
	काष्ठा bfa_rport_qos_attr_s qos_attr; /*  qos attributes  */
	क्रमागत bfa_port_speed curr_speed;   /*  operating speed got from
					    * RPSC ELS. UNKNOWN, अगर RPSC
					    * is not supported */
	bfa_boolean_t	trl_enक्रमced;	/*  TRL enक्रमced ? TRUE/FALSE */
	क्रमागत bfa_port_speed	asचिन्हित_speed;	/* Speed asचिन्हित by the user.
						 * will be used अगर RPSC is not
						 * supported by the rport */
पूर्ण;

काष्ठा bfa_rport_remote_link_stats_s अणु
	u32 lfc; /*  Link Failure Count */
	u32 lsyc; /*  Loss of Synchronization Count */
	u32 lsic; /*  Loss of Signal Count */
	u32 pspec; /*  Primitive Sequence Protocol Error Count */
	u32 itwc; /*  Invalid Transmission Word Count */
	u32 icc; /*  Invalid CRC Count */
पूर्ण;

काष्ठा bfa_rport_qualअगरier_s अणु
	wwn_t	pwwn;	/* Port WWN */
	u32	pid;	/* port ID */
	u32	rsvd;
पूर्ण;

#घोषणा BFA_MAX_IO_INDEX 7
#घोषणा BFA_NO_IO_INDEX 9

/*
 * FCS itnim states
 */
क्रमागत bfa_itnim_state अणु
	BFA_ITNIM_OFFLINE	= 0,	/*  offline */
	BFA_ITNIM_PRLI_SEND	= 1,	/*  prli send */
	BFA_ITNIM_PRLI_SENT	= 2,	/*  prli sent */
	BFA_ITNIM_PRLI_RETRY	= 3,	/*  prli retry */
	BFA_ITNIM_HCB_ONLINE	= 4,	/*  online callback */
	BFA_ITNIM_ONLINE	= 5,	/*  online */
	BFA_ITNIM_HCB_OFFLINE	= 6,	/*  offline callback */
	BFA_ITNIM_INITIATIOR	= 7,	/*  initiator */
पूर्ण;

/*
 * FCS remote port statistics
 */
काष्ठा bfa_itnim_stats_s अणु
	u32        onlines;	/*  num rport online */
	u32        offlines;	/*  num rport offline */
	u32        prli_sent;	/*  num prli sent out */
	u32        fcxp_alloc_रुको;/*  num fcxp alloc रुकोs */
	u32        prli_rsp_err;	/*  num prli rsp errors */
	u32        prli_rsp_acc;	/*  num prli rsp accepts */
	u32        initiator;	/*  rport is an initiator */
	u32        prli_rsp_parse_err;	/*  prli rsp parsing errors */
	u32        prli_rsp_rjt;	/*  num prli rsp rejects */
	u32        समयout;	/*  num समयouts detected */
	u32        sler;		/*  num sler notअगरication from BFA */
	u32	rsvd;		/* padding क्रम 64 bit alignment */
पूर्ण;

/*
 * FCS itnim attributes वापसed in queries
 */
काष्ठा bfa_itnim_attr_s अणु
	क्रमागत bfa_itnim_state state; /*  FCS itnim state        */
	u8 retry;		/*  data retransmision support */
	u8	task_retry_id;  /*  task retry ident support   */
	u8 rec_support;    /*  REC supported              */
	u8 conf_comp;      /*  confirmed completion supp  */
पूर्ण;

#पूर्ण_अगर /* __BFA_DEFS_FCS_H__ */
