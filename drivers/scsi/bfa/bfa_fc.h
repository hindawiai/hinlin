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

#अगर_अघोषित __BFA_FC_H__
#घोषणा __BFA_FC_H__

#समावेश "bfad_drv.h"

प्रकार u64 wwn_t;

#घोषणा WWN_शून्य	(0)
#घोषणा FC_SYMNAME_MAX	256	/*  max name server symbolic name size */
#घोषणा FC_ALPA_MAX	128

#आशय pack(1)

#घोषणा MAC_ADDRLEN	(6)
काष्ठा mac_s अणु u8 mac[MAC_ADDRLEN]; पूर्ण;
#घोषणा mac_t काष्ठा mac_s

/*
 * generic SCSI cdb definition
 */
#घोषणा SCSI_MAX_CDBLEN     16
काष्ठा scsi_cdb_s अणु
	u8         scsi_cdb[SCSI_MAX_CDBLEN];
पूर्ण;

#घोषणा SCSI_MAX_ALLOC_LEN      0xFF    /* maximum allocarion length */

/*
 * Fibre Channel Header Structure (FCHS) definition
 */
काष्ठा fchs_s अणु
#अगर_घोषित __BIG_ENDIAN
	u32        routing:4;	/* routing bits */
	u32        cat_info:4;	/* category info */
#अन्यथा
	u32        cat_info:4;	/* category info */
	u32        routing:4;	/* routing bits */
#पूर्ण_अगर
	u32        d_id:24;	/* destination identअगरier */

	u32        cs_ctl:8;	/* class specअगरic control */
	u32        s_id:24;	/* source identअगरier */

	u32        type:8;	/* data काष्ठाure type */
	u32        f_ctl:24;	/* initial frame control */

	u8         seq_id;	/* sequence identअगरier */
	u8         df_ctl;	/* data field control */
	u16        seq_cnt;	/* sequence count */

	__be16     ox_id;	/* originator exchange ID */
	u16        rx_id;	/* responder exchange ID */

	u32        ro;		/* relative offset */
पूर्ण;

/*
 * routing bit definitions
 */
क्रमागत अणु
	FC_RTG_FC4_DEV_DATA	= 0x0,	/* FC-4 Device Data */
	FC_RTG_EXT_LINK		= 0x2,	/* Extended Link Data */
	FC_RTG_FC4_LINK_DATA	= 0x3,	/* FC-4 Link Data */
	FC_RTG_VIDEO_DATA	= 0x4,	/* Video Data */
	FC_RTG_EXT_HDR		= 0x5,	/* VFT, IFR or Encapsuled */
	FC_RTG_BASIC_LINK	= 0x8,	/* Basic Link data */
	FC_RTG_LINK_CTRL	= 0xC,	/* Link Control */
पूर्ण;

/*
 * inक्रमmation category क्रम extended link data and FC-4 Link Data
 */
क्रमागत अणु
	FC_CAT_LD_REQUEST	= 0x2,	/* Request */
	FC_CAT_LD_REPLY		= 0x3,	/* Reply */
	FC_CAT_LD_DIAG		= 0xF,	/* क्रम DIAG use only */
पूर्ण;

/*
 * inक्रमmation category क्रम extended headers (VFT, IFR or encapsulation)
 */
क्रमागत अणु
	FC_CAT_VFT_HDR = 0x0,	/* Virtual fabric tagging header */
	FC_CAT_IFR_HDR = 0x1,	/* Inter-Fabric routing header */
	FC_CAT_ENC_HDR = 0x2,	/* Encapsulation header */
पूर्ण;

/*
 * inक्रमmation category क्रम FC-4 device data
 */
क्रमागत अणु
	FC_CAT_UNCATEG_INFO	= 0x0,	/* Uncategorized inक्रमmation */
	FC_CAT_SOLICIT_DATA	= 0x1,	/* Solicited Data */
	FC_CAT_UNSOLICIT_CTRL	= 0x2,	/* Unsolicited Control */
	FC_CAT_SOLICIT_CTRL	= 0x3,	/* Solicited Control */
	FC_CAT_UNSOLICIT_DATA	= 0x4,	/* Unsolicited Data */
	FC_CAT_DATA_DESC	= 0x5,	/* Data Descriptor */
	FC_CAT_UNSOLICIT_CMD	= 0x6,	/* Unsolicited Command */
	FC_CAT_CMD_STATUS	= 0x7,	/* Command Status */
पूर्ण;

/*
 * Type Field Definitions. FC-PH Section 18.5 pg. 165
 */
क्रमागत अणु
	FC_TYPE_BLS		= 0x0,	/* Basic Link Service */
	FC_TYPE_ELS		= 0x1,	/* Extended Link Service */
	FC_TYPE_IP		= 0x5,	/* IP */
	FC_TYPE_FCP		= 0x8,	/* SCSI-FCP */
	FC_TYPE_GPP		= 0x9,	/* SCSI_GPP */
	FC_TYPE_SERVICES	= 0x20,	/* Fibre Channel Services */
	FC_TYPE_FC_FSS		= 0x22,	/* Fabric Switch Services */
	FC_TYPE_FC_AL		= 0x23,	/* FC-AL */
	FC_TYPE_FC_SNMP		= 0x24,	/* FC-SNMP */
	FC_TYPE_FC_SPINFAB	= 0xEE,	/* SPINFAB */
	FC_TYPE_FC_DIAG		= 0xEF,	/* DIAG */
	FC_TYPE_MAX		= 256,	/* 256 FC-4 types */
पूर्ण;

/*
 * Frame Control Definitions. FC-PH Table-45. pg. 168
 */
क्रमागत अणु
	FCTL_EC_ORIG = 0x000000,	/* exchange originator */
	FCTL_EC_RESP = 0x800000,	/* exchange responder */
	FCTL_SEQ_INI = 0x000000,	/* sequence initiator */
	FCTL_SEQ_REC = 0x400000,	/* sequence recipient */
	FCTL_FS_EXCH = 0x200000,	/* first sequence of xchg */
	FCTL_LS_EXCH = 0x100000,	/* last sequence of xchg */
	FCTL_END_SEQ = 0x080000,	/* last frame of sequence */
	FCTL_SI_XFER = 0x010000,	/* seq initiative transfer */
	FCTL_RO_PRESENT = 0x000008,	/* relative offset present */
	FCTL_FILLBYTE_MASK = 0x000003	/* , fill byte mask */
पूर्ण;

/*
 * Fabric Well Known Addresses
 */
क्रमागत अणु
	FC_MIN_WELL_KNOWN_ADDR		= 0xFFFFF0,
	FC_DOMAIN_CONTROLLER_MASK	= 0xFFFC00,
	FC_ALIAS_SERVER			= 0xFFFFF8,
	FC_MGMT_SERVER			= 0xFFFFFA,
	FC_TIME_SERVER			= 0xFFFFFB,
	FC_NAME_SERVER			= 0xFFFFFC,
	FC_FABRIC_CONTROLLER		= 0xFFFFFD,
	FC_FABRIC_PORT			= 0xFFFFFE,
	FC_BROADCAST_SERVER		= 0xFFFFFF
पूर्ण;

/*
 * करोमुख्य/area/port defines
 */
#घोषणा FC_DOMAIN_MASK  0xFF0000
#घोषणा FC_DOMAIN_SHIFT 16
#घोषणा FC_AREA_MASK    0x00FF00
#घोषणा FC_AREA_SHIFT   8
#घोषणा FC_PORT_MASK    0x0000FF
#घोषणा FC_PORT_SHIFT   0

#घोषणा FC_GET_DOMAIN(p)	(((p) & FC_DOMAIN_MASK) >> FC_DOMAIN_SHIFT)
#घोषणा FC_GET_AREA(p)		(((p) & FC_AREA_MASK) >> FC_AREA_SHIFT)
#घोषणा FC_GET_PORT(p)		(((p) & FC_PORT_MASK) >> FC_PORT_SHIFT)

#घोषणा FC_DOMAIN_CTRLR(p)	(FC_DOMAIN_CONTROLLER_MASK | (FC_GET_DOMAIN(p)))

क्रमागत अणु
	FC_RXID_ANY = 0xFFFFU,
पूर्ण;

/*
 * generic ELS command
 */
काष्ठा fc_els_cmd_s अणु
	u32        els_code:8;	/* ELS Command Code */
	u32        reserved:24;
पूर्ण;

/*
 * ELS Command Codes. FC-PH Table-75. pg. 223
 */
क्रमागत अणु
	FC_ELS_LS_RJT = 0x1,	/* Link Service Reject. */
	FC_ELS_ACC = 0x02,	/* Accept */
	FC_ELS_PLOGI = 0x03,	/* N_Port Login. */
	FC_ELS_FLOGI = 0x04,	/* F_Port Login. */
	FC_ELS_LOGO = 0x05,	/* Logout. */
	FC_ELS_ABTX = 0x06,	/* Abort Exchange */
	FC_ELS_RES = 0x08,	/* Read Exchange status */
	FC_ELS_RSS = 0x09,	/* Read sequence status block */
	FC_ELS_RSI = 0x0A,	/* Request Sequence Initiative */
	FC_ELS_ESTC = 0x0C,	/* Estimate Credit. */
	FC_ELS_RTV = 0x0E,	/* Read Timeout Value. */
	FC_ELS_RLS = 0x0F,	/* Read Link Status. */
	FC_ELS_ECHO = 0x10,	/* Echo */
	FC_ELS_TEST = 0x11,	/* Test */
	FC_ELS_RRQ = 0x12,	/* Reinstate Recovery Qualअगरier. */
	FC_ELS_REC = 0x13,	/* Add this क्रम TAPE support in FCR */
	FC_ELS_PRLI = 0x20,	/* Process Login */
	FC_ELS_PRLO = 0x21,	/* Process Logout. */
	FC_ELS_SCN = 0x22,	/* State Change Notअगरication. */
	FC_ELS_TPRLO = 0x24,	/* Third Party Process Logout. */
	FC_ELS_PDISC = 0x50,	/* Discover N_Port Parameters. */
	FC_ELS_FDISC = 0x51,	/* Discover F_Port Parameters. */
	FC_ELS_ADISC = 0x52,	/* Discover Address. */
	FC_ELS_FARP_REQ = 0x54,	/* FARP Request. */
	FC_ELS_FARP_REP = 0x55,	/* FARP Reply. */
	FC_ELS_FAN = 0x60,	/* Fabric Address Notअगरication */
	FC_ELS_RSCN = 0x61,	/* Reg State Change Notअगरication */
	FC_ELS_SCR = 0x62,	/* State Change Registration. */
	FC_ELS_RTIN = 0x77,	/* Mangement server request */
	FC_ELS_RNID = 0x78,	/* Mangement server request */
	FC_ELS_RLIR = 0x79,	/* Registered Link Incident Record */

	FC_ELS_RPSC = 0x7D,	/* Report Port Speed Capabilities */
	FC_ELS_QSA = 0x7E,	/* Query Security Attributes. Ref FC-SP */
	FC_ELS_E2E_LBEACON = 0x81,
				/* End-to-End Link Beacon */
	FC_ELS_AUTH = 0x90,	/* Authentication. Ref FC-SP */
	FC_ELS_RFCN = 0x97,	/* Request Fabric Change Notअगरication. Ref
				 *FC-SP */
पूर्ण;

/*
 *  Version numbers क्रम FC-PH standards,
 *  used in login to indicate what port
 *  supports. See FC-PH-X table 158.
 */
क्रमागत अणु
	FC_PH_VER_4_3 = 0x09,
	FC_PH_VER_PH_3 = 0x20,
पूर्ण;

/*
 * PDU size defines
 */
क्रमागत अणु
	FC_MIN_PDUSZ = 512,
	FC_MAX_PDUSZ = 2112,
पूर्ण;

/*
 * N_Port PLOGI Common Service Parameters.
 * FC-PH-x. Figure-76. pg. 308.
 */
काष्ठा fc_plogi_csp_s अणु
	u8		verhi;		/* FC-PH high version */
	u8		verlo;		/* FC-PH low version */
	__be16		bbcred;		/* BB_Credit */

#अगर_घोषित __BIG_ENDIAN
	u8		ciro:1,		/* continuously increasing RO */
			rro:1,		/* अक्रमom relative offset */
			npiv_supp:1,	/* NPIV supported */
			port_type:1,	/* N_Port/F_port */
			altbbcred:1,	/* alternate BB_Credit */
			resolution:1,	/* ms/ns ED_TOV resolution */
			vvl_info:1,	/* VVL Info included */
			reserved1:1;

	u8		hg_supp:1,
			query_dbc:1,
			security:1,
			sync_cap:1,
			r_t_tov:1,
			dh_dup_supp:1,
			cisc:1,		/* continuously increasing seq count */
			payload:1;
#अन्यथा
	u8		reserved2:2,
			resolution:1,	/* ms/ns ED_TOV resolution */
			altbbcred:1,	/* alternate BB_Credit */
			port_type:1,	/* N_Port/F_port */
			npiv_supp:1,	/* NPIV supported */
			rro:1,		/* अक्रमom relative offset */
			ciro:1;		/* continuously increasing RO */

	u8		payload:1,
			cisc:1,		/* continuously increasing seq count */
			dh_dup_supp:1,
			r_t_tov:1,
			sync_cap:1,
			security:1,
			query_dbc:1,
			hg_supp:1;
#पूर्ण_अगर
	__be16		rxsz;		/* receive data_field size */
	__be16		conseq;
	__be16		ro_biपंचांगap;
	__be32		e_d_tov;
पूर्ण;

/*
 * N_Port PLOGI Class Specअगरic Parameters.
 * FC-PH-x. Figure 78. pg. 318.
 */
काष्ठा fc_plogi_clp_s अणु
#अगर_घोषित __BIG_ENDIAN
	u32        class_valid:1;
	u32        पूर्णांकermix:1;	/* class पूर्णांकermix supported अगर set =1.
				 * valid only क्रम class1. Reserved क्रम
				 * class2 & class3 */
	u32        reserved1:2;
	u32        sequential:1;
	u32        reserved2:3;
#अन्यथा
	u32        reserved2:3;
	u32        sequential:1;
	u32        reserved1:2;
	u32        पूर्णांकermix:1;	/* class पूर्णांकermix supported अगर set =1.
				 * valid only क्रम class1. Reserved क्रम
				 * class2 & class3 */
	u32        class_valid:1;
#पूर्ण_अगर
	u32        reserved3:24;

	u32        reserved4:16;
	u32        rxsz:16;	/* Receive data_field size */

	u32        reserved5:8;
	u32        conseq:8;
	u32        e2e_credit:16; /* end to end credit */

	u32        reserved7:8;
	u32        ospx:8;
	u32        reserved8:16;
पूर्ण;

/* ASCII value क्रम each अक्षरacter in string "BRCD" */
#घोषणा FLOGI_VVL_BRCD    0x42524344

/*
 * PLOGI els command and reply payload
 */
काष्ठा fc_logi_s अणु
	काष्ठा fc_els_cmd_s	els_cmd;	/* ELS command code */
	काष्ठा fc_plogi_csp_s	csp;		/* common service params */
	wwn_t			port_name;
	wwn_t			node_name;
	काष्ठा fc_plogi_clp_s	class1;		/* class 1 service parameters */
	काष्ठा fc_plogi_clp_s	class2;		/* class 2 service parameters */
	काष्ठा fc_plogi_clp_s	class3;		/* class 3 service parameters */
	काष्ठा fc_plogi_clp_s	class4;		/* class 4 service parameters */
	u8			vvl[16];	/* venकरोr version level */
पूर्ण;

/*
 * LOGO els command payload
 */
काष्ठा fc_logo_s अणु
	काष्ठा fc_els_cmd_s	els_cmd;	/* ELS command code */
	u32			res1:8;
	u32		nport_id:24;	/* N_Port identअगरier of source */
	wwn_t           orig_port_name;	/* Port name of the LOGO originator */
पूर्ण;

/*
 * ADISC els command payload
 */
काष्ठा fc_adisc_s अणु
	काष्ठा fc_els_cmd_s els_cmd;	/* ELS command code */
	u32		res1:8;
	u32		orig_HA:24;	/* originator hard address */
	wwn_t		orig_port_name;	/* originator port name */
	wwn_t		orig_node_name;	/* originator node name */
	u32		res2:8;
	u32		nport_id:24;	/* originator NPortID */
पूर्ण;

/*
 * Exchange status block
 */
काष्ठा fc_exch_status_blk_s अणु
	u32        oxid:16;
	u32        rxid:16;
	u32        res1:8;
	u32        orig_np:24;	/* originator NPortID */
	u32        res2:8;
	u32        resp_np:24;	/* responder NPortID */
	u32        es_bits;
	u32        res3;
	/*
	 * un modअगरied section of the fields
	 */
पूर्ण;

/*
 * RES els command payload
 */
काष्ठा fc_res_s अणु
	काष्ठा fc_els_cmd_s els_cmd;	/* ELS command code */
	u32        res1:8;
	u32        nport_id:24;		/* N_Port identअगरier of source */
	u32        oxid:16;
	u32        rxid:16;
	u8         assoc_hdr[32];
पूर्ण;

/*
 * RES els accept payload
 */
काष्ठा fc_res_acc_s अणु
	काष्ठा fc_els_cmd_s		els_cmd;	/* ELS command code */
	काष्ठा fc_exch_status_blk_s	fc_exch_blk; /* Exchange status block */
पूर्ण;

/*
 * REC els command payload
 */
काष्ठा fc_rec_s अणु
	काष्ठा fc_els_cmd_s els_cmd;	/* ELS command code */
	u32        res1:8;
	u32        nport_id:24;	/* N_Port identअगरier of source */
	u32        oxid:16;
	u32        rxid:16;
पूर्ण;

#घोषणा FC_REC_ESB_OWN_RSP	0x80000000	/* responder owns */
#घोषणा FC_REC_ESB_SI		0x40000000	/* SI is owned	*/
#घोषणा FC_REC_ESB_COMP		0x20000000	/* exchange is complete	*/
#घोषणा FC_REC_ESB_ENDCOND_ABN	0x10000000	/* abnormal ending	*/
#घोषणा FC_REC_ESB_RQACT	0x04000000	/* recovery qual active	*/
#घोषणा FC_REC_ESB_ERRP_MSK	0x03000000
#घोषणा FC_REC_ESB_OXID_INV	0x00800000	/* invalid OXID		*/
#घोषणा FC_REC_ESB_RXID_INV	0x00400000	/* invalid RXID		*/
#घोषणा FC_REC_ESB_PRIO_INUSE	0x00200000

/*
 * REC els accept payload
 */
काष्ठा fc_rec_acc_s अणु
	काष्ठा fc_els_cmd_s els_cmd;	/* ELS command code */
	u32        oxid:16;
	u32        rxid:16;
	u32        res1:8;
	u32        orig_id:24;	/* N_Port id of exchange originator */
	u32        res2:8;
	u32        resp_id:24;	/* N_Port id of exchange responder */
	u32        count;	/* data transfer count */
	u32        e_stat;	/* exchange status */
पूर्ण;

/*
 * RSI els payload
 */
काष्ठा fc_rsi_s अणु
	काष्ठा fc_els_cmd_s els_cmd;
	u32        res1:8;
	u32        orig_sid:24;
	u32        oxid:16;
	u32        rxid:16;
पूर्ण;

/*
 * काष्ठाure क्रम PRLI paramater pages, both request & response
 * see FC-PH-X table 113 & 115 क्रम explanation also FCP table 8
 */
काष्ठा fc_prli_params_s अणु
	u32        reserved:16;
#अगर_घोषित __BIG_ENDIAN
	u32        reserved1:5;
	u32        rec_support:1;
	u32        task_retry_id:1;
	u32        retry:1;

	u32        confirm:1;
	u32        करोverlay:1;
	u32        initiator:1;
	u32        target:1;
	u32        cdmix:1;
	u32        drmix:1;
	u32        rxrdisab:1;
	u32        wxrdisab:1;
#अन्यथा
	u32        retry:1;
	u32        task_retry_id:1;
	u32        rec_support:1;
	u32        reserved1:5;

	u32        wxrdisab:1;
	u32        rxrdisab:1;
	u32        drmix:1;
	u32        cdmix:1;
	u32        target:1;
	u32        initiator:1;
	u32        करोverlay:1;
	u32        confirm:1;
#पूर्ण_अगर
पूर्ण;

/*
 * valid values क्रम rspcode in PRLI ACC payload
 */
क्रमागत अणु
	FC_PRLI_ACC_XQTD = 0x1,		/* request executed */
	FC_PRLI_ACC_PREDEF_IMG = 0x5,	/* predefined image - no prli needed */
पूर्ण;

काष्ठा fc_prli_params_page_s अणु
	u32        type:8;
	u32        codext:8;
#अगर_घोषित __BIG_ENDIAN
	u32        origprocasv:1;
	u32        rsppav:1;
	u32        imagepair:1;
	u32        reserved1:1;
	u32        rspcode:4;
#अन्यथा
	u32        rspcode:4;
	u32        reserved1:1;
	u32        imagepair:1;
	u32        rsppav:1;
	u32        origprocasv:1;
#पूर्ण_अगर
	u32        reserved2:8;

	u32        origprocas;
	u32        rspprocas;
	काष्ठा fc_prli_params_s servparams;
पूर्ण;

/*
 * PRLI request and accept payload, FC-PH-X tables 112 & 114
 */
काष्ठा fc_prli_s अणु
	u32        command:8;
	u32        pglen:8;
	u32        pagebytes:16;
	काष्ठा fc_prli_params_page_s parampage;
पूर्ण;

/*
 * PRLO logout params page
 */
काष्ठा fc_prlo_params_page_s अणु
	u32        type:8;
	u32        type_ext:8;
#अगर_घोषित __BIG_ENDIAN
	u32        opa_valid:1;	/* originator process associator valid */
	u32        rpa_valid:1;	/* responder process associator valid */
	u32        res1:14;
#अन्यथा
	u32        res1:14;
	u32        rpa_valid:1;	/* responder process associator valid */
	u32        opa_valid:1;	/* originator process associator valid */
#पूर्ण_अगर
	u32        orig_process_assc;
	u32        resp_process_assc;

	u32        res2;
पूर्ण;

/*
 * PRLO els command payload
 */
काष्ठा fc_prlo_s अणु
	u32	command:8;
	u32	page_len:8;
	u32	payload_len:16;
	काष्ठा fc_prlo_params_page_s	prlo_params[1];
पूर्ण;

/*
 * PRLO Logout response parameter page
 */
काष्ठा fc_prlo_acc_params_page_s अणु
	u32        type:8;
	u32        type_ext:8;

#अगर_घोषित __BIG_ENDIAN
	u32        opa_valid:1;	/* originator process associator valid */
	u32        rpa_valid:1;	/* responder process associator valid */
	u32        res1:14;
#अन्यथा
	u32        res1:14;
	u32        rpa_valid:1;	/* responder process associator valid */
	u32        opa_valid:1;	/* originator process associator valid */
#पूर्ण_अगर
	u32        orig_process_assc;
	u32        resp_process_assc;

	u32        fc4type_csp;
पूर्ण;

/*
 * PRLO els command ACC payload
 */
काष्ठा fc_prlo_acc_s अणु
	u32        command:8;
	u32        page_len:8;
	u32        payload_len:16;
	काष्ठा fc_prlo_acc_params_page_s prlo_acc_params[1];
पूर्ण;

/*
 * SCR els command payload
 */
क्रमागत अणु
	FC_SCR_REG_FUNC_FABRIC_DETECTED = 0x01,
	FC_SCR_REG_FUNC_N_PORT_DETECTED = 0x02,
	FC_SCR_REG_FUNC_FULL = 0x03,
	FC_SCR_REG_FUNC_CLEAR_REG = 0xFF,
पूर्ण;

/* SCR VU registrations */
क्रमागत अणु
	FC_VU_SCR_REG_FUNC_FABRIC_NAME_CHANGE = 0x01
पूर्ण;

काष्ठा fc_scr_s अणु
	u32 command:8;
	u32 res:24;
	u32 vu_reg_func:8; /* Venकरोr Unique Registrations */
	u32 res1:16;
	u32 reg_func:8;
पूर्ण;

/*
 * Inक्रमmation category क्रम Basic link data
 */
क्रमागत अणु
	FC_CAT_NOP	= 0x0,
	FC_CAT_ABTS	= 0x1,
	FC_CAT_RMC	= 0x2,
	FC_CAT_BA_ACC	= 0x4,
	FC_CAT_BA_RJT	= 0x5,
	FC_CAT_PRMT	= 0x6,
पूर्ण;

/*
 * LS_RJT els reply payload
 */
काष्ठा fc_ls_rjt_s अणु
	काष्ठा fc_els_cmd_s els_cmd;	/* ELS command code */
	u32        res1:8;
	u32        reason_code:8;	/* Reason code क्रम reject */
	u32        reason_code_expl:8;	/* Reason code explanation */
	u32        venकरोr_unique:8;	/* Venकरोr specअगरic */
पूर्ण;

/*
 * LS_RJT reason codes
 */
क्रमागत अणु
	FC_LS_RJT_RSN_INV_CMD_CODE	= 0x01,
	FC_LS_RJT_RSN_LOGICAL_ERROR	= 0x03,
	FC_LS_RJT_RSN_LOGICAL_BUSY	= 0x05,
	FC_LS_RJT_RSN_PROTOCOL_ERROR	= 0x07,
	FC_LS_RJT_RSN_UNABLE_TO_PERF_CMD = 0x09,
	FC_LS_RJT_RSN_CMD_NOT_SUPP	= 0x0B,
पूर्ण;

/*
 * LS_RJT reason code explanation
 */
क्रमागत अणु
	FC_LS_RJT_EXP_NO_ADDL_INFO		= 0x00,
	FC_LS_RJT_EXP_SPARMS_ERR_OPTIONS	= 0x01,
	FC_LS_RJT_EXP_SPARMS_ERR_INI_CTL	= 0x03,
	FC_LS_RJT_EXP_SPARMS_ERR_REC_CTL	= 0x05,
	FC_LS_RJT_EXP_SPARMS_ERR_RXSZ		= 0x07,
	FC_LS_RJT_EXP_SPARMS_ERR_CONSEQ		= 0x09,
	FC_LS_RJT_EXP_SPARMS_ERR_CREDIT		= 0x0B,
	FC_LS_RJT_EXP_INV_PORT_NAME		= 0x0D,
	FC_LS_RJT_EXP_INV_NODE_FABRIC_NAME	= 0x0E,
	FC_LS_RJT_EXP_INV_CSP			= 0x0F,
	FC_LS_RJT_EXP_INV_ASSOC_HDR		= 0x11,
	FC_LS_RJT_EXP_ASSOC_HDR_REQD		= 0x13,
	FC_LS_RJT_EXP_INV_ORIG_S_ID		= 0x15,
	FC_LS_RJT_EXP_INV_OXID_RXID_COMB	= 0x17,
	FC_LS_RJT_EXP_CMD_ALREADY_IN_PROG	= 0x19,
	FC_LS_RJT_EXP_LOGIN_REQUIRED		= 0x1E,
	FC_LS_RJT_EXP_INVALID_NPORT_ID		= 0x1F,
	FC_LS_RJT_EXP_INSUFF_RES		= 0x29,
	FC_LS_RJT_EXP_CMD_NOT_SUPP		= 0x2C,
	FC_LS_RJT_EXP_INV_PAYLOAD_LEN		= 0x2D,
पूर्ण;

/*
 * RRQ els command payload
 */
काष्ठा fc_rrq_s अणु
	काष्ठा fc_els_cmd_s els_cmd;	/* ELS command code */
	u32        res1:8;
	u32        s_id:24;	/* exchange originator S_ID */

	u32        ox_id:16;	/* originator exchange ID */
	u32        rx_id:16;	/* responder exchange ID */

	u32        res2[8];	/* optional association header */
पूर्ण;

/*
 * ABTS BA_ACC reply payload
 */
काष्ठा fc_ba_acc_s अणु
	u32        seq_id_valid:8;	/* set to 0x00 क्रम Abort Exchange */
	u32        seq_id:8;		/* invalid क्रम Abort Exchange */
	u32        res2:16;
	u32        ox_id:16;		/* OX_ID from ABTS frame */
	u32        rx_id:16;		/* RX_ID from ABTS frame */
	u32        low_seq_cnt:16;	/* set to 0x0000 क्रम Abort Exchange */
	u32        high_seq_cnt:16;	/* set to 0xFFFF क्रम Abort Exchange */
पूर्ण;

/*
 * ABTS BA_RJT reject payload
 */
काष्ठा fc_ba_rjt_s अणु
	u32        res1:8;		/* Reserved */
	u32        reason_code:8;	/* reason code क्रम reject */
	u32        reason_expl:8;	/* reason code explanation */
	u32        venकरोr_unique:8; /* venकरोr unique reason code,set to 0 */
पूर्ण;

/*
 * TPRLO logout parameter page
 */
काष्ठा fc_tprlo_params_page_s अणु
	u32        type:8;
	u32        type_ext:8;

#अगर_घोषित __BIG_ENDIAN
	u32        opa_valid:1;
	u32        rpa_valid:1;
	u32        tpo_nport_valid:1;
	u32        global_process_logout:1;
	u32        res1:12;
#अन्यथा
	u32        res1:12;
	u32        global_process_logout:1;
	u32        tpo_nport_valid:1;
	u32        rpa_valid:1;
	u32        opa_valid:1;
#पूर्ण_अगर

	u32        orig_process_assc;
	u32        resp_process_assc;

	u32        res2:8;
	u32        tpo_nport_id;
पूर्ण;

/*
 * TPRLO ELS command payload
 */
काष्ठा fc_tprlo_s अणु
	u32        command:8;
	u32        page_len:8;
	u32        payload_len:16;

	काष्ठा fc_tprlo_params_page_s tprlo_params[1];
पूर्ण;

क्रमागत fc_tprlo_type अणु
	FC_GLOBAL_LOGO = 1,
	FC_TPR_LOGO
पूर्ण;

/*
 * TPRLO els command ACC payload
 */
काष्ठा fc_tprlo_acc_s अणु
	u32	command:8;
	u32	page_len:8;
	u32	payload_len:16;
	काष्ठा fc_prlo_acc_params_page_s tprlo_acc_params[1];
पूर्ण;

/*
 * RSCN els command req payload
 */
#घोषणा FC_RSCN_PGLEN	0x4

क्रमागत fc_rscn_क्रमmat अणु
	FC_RSCN_FORMAT_PORTID	= 0x0,
	FC_RSCN_FORMAT_AREA	= 0x1,
	FC_RSCN_FORMAT_DOMAIN	= 0x2,
	FC_RSCN_FORMAT_FABRIC	= 0x3,
पूर्ण;

काष्ठा fc_rscn_event_s अणु
	u32	क्रमmat:2;
	u32	qualअगरier:4;
	u32	resvd:2;
	u32	portid:24;
पूर्ण;

काष्ठा fc_rscn_pl_s अणु
	u8	command;
	u8	pagelen;
	__be16	payldlen;
	काष्ठा fc_rscn_event_s event[1];
पूर्ण;

/*
 * ECHO els command req payload
 */
काष्ठा fc_echo_s अणु
	काष्ठा fc_els_cmd_s els_cmd;
पूर्ण;

/*
 * RNID els command
 */
#घोषणा RNID_NODEID_DATA_FORMAT_COMMON			0x00
#घोषणा RNID_NODEID_DATA_FORMAT_FCP3			0x08
#घोषणा RNID_NODEID_DATA_FORMAT_DISCOVERY		0xDF

#घोषणा RNID_ASSOCIATED_TYPE_UNKNOWN			0x00000001
#घोषणा RNID_ASSOCIATED_TYPE_OTHER                      0x00000002
#घोषणा RNID_ASSOCIATED_TYPE_HUB                        0x00000003
#घोषणा RNID_ASSOCIATED_TYPE_SWITCH                     0x00000004
#घोषणा RNID_ASSOCIATED_TYPE_GATEWAY                    0x00000005
#घोषणा RNID_ASSOCIATED_TYPE_STORAGE_DEVICE             0x00000009
#घोषणा RNID_ASSOCIATED_TYPE_HOST                       0x0000000A
#घोषणा RNID_ASSOCIATED_TYPE_STORAGE_SUBSYSTEM          0x0000000B
#घोषणा RNID_ASSOCIATED_TYPE_STORAGE_ACCESS_DEVICE      0x0000000E
#घोषणा RNID_ASSOCIATED_TYPE_NAS_SERVER                 0x00000011
#घोषणा RNID_ASSOCIATED_TYPE_BRIDGE                     0x00000002
#घोषणा RNID_ASSOCIATED_TYPE_VIRTUALIZATION_DEVICE      0x00000003
#घोषणा RNID_ASSOCIATED_TYPE_MULTI_FUNCTION_DEVICE      0x000000FF

/*
 * RNID els command payload
 */
काष्ठा fc_rnid_cmd_s अणु
	काष्ठा fc_els_cmd_s els_cmd;
	u32        node_id_data_क्रमmat:8;
	u32        reserved:24;
पूर्ण;

/*
 * RNID els response payload
 */

काष्ठा fc_rnid_common_id_data_s अणु
	wwn_t		port_name;
	wwn_t           node_name;
पूर्ण;

काष्ठा fc_rnid_general_topology_data_s अणु
	u32        venकरोr_unique[4];
	__be32     asso_type;
	u32        phy_port_num;
	__be32     num_attached_nodes;
	u32        node_mgmt:8;
	u32        ip_version:8;
	u32        udp_tcp_port_num:16;
	u32        ip_address[4];
	u32        reserved:16;
	u32        venकरोr_specअगरic:16;
पूर्ण;

काष्ठा fc_rnid_acc_s अणु
	काष्ठा fc_els_cmd_s els_cmd;
	u32        node_id_data_क्रमmat:8;
	u32        common_id_data_length:8;
	u32        reserved:8;
	u32        specअगरic_id_data_length:8;
	काष्ठा fc_rnid_common_id_data_s common_id_data;
	काष्ठा fc_rnid_general_topology_data_s gen_topology_data;
पूर्ण;

#घोषणा RNID_ASSOCIATED_TYPE_UNKNOWN                    0x00000001
#घोषणा RNID_ASSOCIATED_TYPE_OTHER                      0x00000002
#घोषणा RNID_ASSOCIATED_TYPE_HUB                        0x00000003
#घोषणा RNID_ASSOCIATED_TYPE_SWITCH                     0x00000004
#घोषणा RNID_ASSOCIATED_TYPE_GATEWAY                    0x00000005
#घोषणा RNID_ASSOCIATED_TYPE_STORAGE_DEVICE             0x00000009
#घोषणा RNID_ASSOCIATED_TYPE_HOST                       0x0000000A
#घोषणा RNID_ASSOCIATED_TYPE_STORAGE_SUBSYSTEM          0x0000000B
#घोषणा RNID_ASSOCIATED_TYPE_STORAGE_ACCESS_DEVICE      0x0000000E
#घोषणा RNID_ASSOCIATED_TYPE_NAS_SERVER                 0x00000011
#घोषणा RNID_ASSOCIATED_TYPE_BRIDGE                     0x00000002
#घोषणा RNID_ASSOCIATED_TYPE_VIRTUALIZATION_DEVICE      0x00000003
#घोषणा RNID_ASSOCIATED_TYPE_MULTI_FUNCTION_DEVICE      0x000000FF

क्रमागत fc_rpsc_speed_cap अणु
	RPSC_SPEED_CAP_1G = 0x8000,
	RPSC_SPEED_CAP_2G = 0x4000,
	RPSC_SPEED_CAP_4G = 0x2000,
	RPSC_SPEED_CAP_10G = 0x1000,
	RPSC_SPEED_CAP_8G = 0x0800,
	RPSC_SPEED_CAP_16G = 0x0400,

	RPSC_SPEED_CAP_UNKNOWN = 0x0001,
पूर्ण;

क्रमागत fc_rpsc_op_speed अणु
	RPSC_OP_SPEED_1G = 0x8000,
	RPSC_OP_SPEED_2G = 0x4000,
	RPSC_OP_SPEED_4G = 0x2000,
	RPSC_OP_SPEED_10G = 0x1000,
	RPSC_OP_SPEED_8G = 0x0800,
	RPSC_OP_SPEED_16G = 0x0400,

	RPSC_OP_SPEED_NOT_EST = 0x0001,	/* speed not established */
पूर्ण;

काष्ठा fc_rpsc_speed_info_s अणु
	__be16        port_speed_cap;	/* see क्रमागत fc_rpsc_speed_cap */
	__be16        port_op_speed;	/* see क्रमागत fc_rpsc_op_speed */
पूर्ण;

/*
 * If RPSC request is sent to the Doमुख्य Controller, the request is क्रम
 * all the ports within that करोमुख्य.
 */
काष्ठा fc_rpsc_cmd_s अणु
	काष्ठा fc_els_cmd_s els_cmd;
पूर्ण;

/*
 * RPSC Acc
 */
काष्ठा fc_rpsc_acc_s अणु
	u32        command:8;
	u32        rsvd:8;
	u32        num_entries:16;

	काष्ठा fc_rpsc_speed_info_s speed_info[1];
पूर्ण;

/*
 * If RPSC2 request is sent to the Doमुख्य Controller,
 */
#घोषणा FC_BRCD_TOKEN    0x42524344

काष्ठा fc_rpsc2_cmd_s अणु
	काष्ठा fc_els_cmd_s els_cmd;
	__be32	token;
	u16	resvd;
	__be16	num_pids;		/* Number of pids in the request */
	काष्ठा  अणु
		u32	rsvd1:8;
		u32	pid:24;		/* port identअगरier */
	पूर्ण pid_list[1];
पूर्ण;

क्रमागत fc_rpsc2_port_type अणु
	RPSC2_PORT_TYPE_UNKNOWN = 0,
	RPSC2_PORT_TYPE_NPORT   = 1,
	RPSC2_PORT_TYPE_NLPORT  = 2,
	RPSC2_PORT_TYPE_NPIV_PORT  = 0x5f,
	RPSC2_PORT_TYPE_NPORT_TRUNK  = 0x6f,
पूर्ण;

/*
 * RPSC2 portInfo entry काष्ठाure
 */
काष्ठा fc_rpsc2_port_info_s अणु
	__be32	pid;		/* PID */
	u16	resvd1;
	__be16	index;		/* port number / index */
	u8	resvd2;
	u8	type;		/* port type N/NL/... */
	__be16	speed;		/* port Operating Speed */
पूर्ण;

/*
 * RPSC2 Accept payload
 */
काष्ठा fc_rpsc2_acc_s अणु
	u8        els_cmd;
	u8        resvd;
	__be16    num_pids; /* Number of pids in the request */
	काष्ठा fc_rpsc2_port_info_s port_info[1]; /* port inक्रमmation */
पूर्ण;

/*
 * bit fields so that multiple classes can be specअगरied
 */
क्रमागत fc_cos अणु
	FC_CLASS_2	= 0x04,
	FC_CLASS_3	= 0x08,
	FC_CLASS_2_3	= 0x0C,
पूर्ण;

/*
 * symbolic name
 */
काष्ठा fc_symname_s अणु
	u8         symname[FC_SYMNAME_MAX];
पूर्ण;

काष्ठा fc_alpabm_s अणु
	u8	alpa_bm[FC_ALPA_MAX / 8];
पूर्ण;

/*
 * protocol शेष समयout values
 */
#घोषणा FC_ED_TOV	2
#घोषणा FC_REC_TOV	(FC_ED_TOV + 1)
#घोषणा FC_RA_TOV	10
#घोषणा FC_ELS_TOV	(2 * FC_RA_TOV)
#घोषणा FC_FCCT_TOV	(3 * FC_RA_TOV)

/*
 * भव fabric related defines
 */
#घोषणा FC_VF_ID_शून्य    0	/*  must not be used as VF_ID */
#घोषणा FC_VF_ID_MIN     1
#घोषणा FC_VF_ID_MAX     0xEFF
#घोषणा FC_VF_ID_CTL     0xFEF	/*  control VF_ID */

/*
 * Virtual Fabric Tagging header क्रमmat
 * @caution This is defined only in BIG ENDIAN क्रमmat.
 */
काष्ठा fc_vft_s अणु
	u32        r_ctl:8;
	u32        ver:2;
	u32        type:4;
	u32        res_a:2;
	u32        priority:3;
	u32        vf_id:12;
	u32        res_b:1;
	u32        hopct:8;
	u32        res_c:24;
पूर्ण;

/*
 * FCP_CMND definitions
 */
#घोषणा FCP_CMND_CDB_LEN    16
#घोषणा FCP_CMND_LUN_LEN    8

काष्ठा fcp_cmnd_s अणु
	काष्ठा scsi_lun	lun;		/* 64-bit LU number */
	u8		crn;		/* command reference number */
#अगर_घोषित __BIG_ENDIAN
	u8		resvd:1,
			priority:4,	/* FCP-3: SAM-3 priority */
			taskattr:3;	/* scsi task attribute */
#अन्यथा
	u8		taskattr:3,	/* scsi task attribute */
			priority:4,	/* FCP-3: SAM-3 priority */
			resvd:1;
#पूर्ण_अगर
	u8		पंचांग_flags;	/* task management flags */
#अगर_घोषित __BIG_ENDIAN
	u8		addl_cdb_len:6,	/* additional CDB length words */
			iodir:2;	/* पढ़ो/ग_लिखो FCP_DATA IUs */
#अन्यथा
	u8		iodir:2,	/* पढ़ो/ग_लिखो FCP_DATA IUs */
			addl_cdb_len:6;	/* additional CDB length */
#पूर्ण_अगर
	काष्ठा scsi_cdb_s      cdb;

	__be32        fcp_dl;	/* bytes to be transferred */
पूर्ण;

#घोषणा fcp_cmnd_cdb_len(_cmnd) ((_cmnd)->addl_cdb_len * 4 + FCP_CMND_CDB_LEN)
#घोषणा fcp_cmnd_fcpdl(_cmnd)	((&(_cmnd)->fcp_dl)[(_cmnd)->addl_cdb_len])

/*
 * काष्ठा fcp_cmnd_s .iodir field values
 */
क्रमागत fcp_iodir अणु
	FCP_IOसूची_NONE  = 0,
	FCP_IOसूची_WRITE = 1,
	FCP_IOसूची_READ  = 2,
	FCP_IOसूची_RW    = 3,
पूर्ण;

/*
 * Task management flags field - only one bit shall be set
 */
क्रमागत fcp_पंचांग_cmnd अणु
	FCP_TM_ABORT_TASK_SET	= BIT(1),
	FCP_TM_CLEAR_TASK_SET	= BIT(2),
	FCP_TM_LUN_RESET	= BIT(4),
	FCP_TM_TARGET_RESET	= BIT(5),	/* obsolete in FCP-3 */
	FCP_TM_CLEAR_ACA	= BIT(6),
पूर्ण;

/*
 * FCP_RSP residue flags
 */
क्रमागत fcp_residue अणु
	FCP_NO_RESIDUE = 0,     /* no residue */
	FCP_RESID_OVER = 1,     /* more data left that was not sent */
	FCP_RESID_UNDER = 2,    /* less data than requested */
पूर्ण;

काष्ठा fcp_rspinfo_s अणु
	u32        res0:24;
	u32        rsp_code:8;		/* response code (as above) */
	u32        res1;
पूर्ण;

काष्ठा fcp_resp_s अणु
	u32        reserved[2];		/* 2 words reserved */
	u16        reserved2;
#अगर_घोषित __BIG_ENDIAN
	u8         reserved3:3;
	u8         fcp_conf_req:1;	/* FCP_CONF is requested */
	u8         resid_flags:2;	/* underflow/overflow */
	u8         sns_len_valid:1;	/* sense len is valid */
	u8         rsp_len_valid:1;	/* response len is valid */
#अन्यथा
	u8         rsp_len_valid:1;	/* response len is valid */
	u8         sns_len_valid:1;	/* sense len is valid */
	u8         resid_flags:2;	/* underflow/overflow */
	u8         fcp_conf_req:1;	/* FCP_CONF is requested */
	u8         reserved3:3;
#पूर्ण_अगर
	u8         scsi_status;		/* one byte SCSI status */
	u32        residue;		/* residual data bytes */
	u32        sns_len;		/* length od sense info */
	u32        rsp_len;		/* length of response info */
पूर्ण;

#घोषणा fcp_snslen(__fcprsp)	((__fcprsp)->sns_len_valid ?		\
					(__fcprsp)->sns_len : 0)
#घोषणा fcp_rsplen(__fcprsp)	((__fcprsp)->rsp_len_valid ?		\
					(__fcprsp)->rsp_len : 0)
#घोषणा fcp_rspinfo(__fcprsp)	((काष्ठा fcp_rspinfo_s *)((__fcprsp) + 1))
#घोषणा fcp_snsinfo(__fcprsp)	(((u8 *)fcp_rspinfo(__fcprsp)) +	\
						fcp_rsplen(__fcprsp))
/*
 * CT
 */
काष्ठा ct_hdr_s अणु
	u32	rev_id:8;	/* Revision of the CT */
	u32	in_id:24;	/* Initiator Id */
	u32	gs_type:8;	/* Generic service Type */
	u32	gs_sub_type:8;	/* Generic service sub type */
	u32	options:8;	/* options */
	u32	rsvrd:8;	/* reserved */
	u32	cmd_rsp_code:16;/* ct command/response code */
	u32	max_res_size:16;/* maximum/residual size */
	u32	frag_id:8;	/* fragment ID */
	u32	reason_code:8;	/* reason code */
	u32	exp_code:8;	/* explanation code */
	u32	venकरोr_unq:8;	/* venकरोr unique */
पूर्ण;

/*
 * defines क्रम the Revision
 */
क्रमागत अणु
	CT_GS3_REVISION = 0x01,
पूर्ण;

/*
 * defines क्रम gs_type
 */
क्रमागत अणु
	CT_GSTYPE_KEYSERVICE	= 0xF7,
	CT_GSTYPE_ALIASSERVICE	= 0xF8,
	CT_GSTYPE_MGMTSERVICE	= 0xFA,
	CT_GSTYPE_TIMESERVICE	= 0xFB,
	CT_GSTYPE_सूचीSERVICE	= 0xFC,
पूर्ण;

/*
 * defines क्रम gs_sub_type क्रम gs type directory service
 */
क्रमागत अणु
	CT_GSSUBTYPE_NAMESERVER = 0x02,
पूर्ण;

/*
 * defines क्रम gs_sub_type क्रम gs type management service
 */
क्रमागत अणु
	CT_GSSUBTYPE_CFGSERVER	= 0x01,
	CT_GSSUBTYPE_UNZONED_NS = 0x02,
	CT_GSSUBTYPE_ZONESERVER = 0x03,
	CT_GSSUBTYPE_LOCKSERVER = 0x04,
	CT_GSSUBTYPE_HBA_MGMTSERVER = 0x10,	/* क्रम FDMI */
पूर्ण;

/*
 * defines क्रम CT response code field
 */
क्रमागत अणु
	CT_RSP_REJECT = 0x8001,
	CT_RSP_ACCEPT = 0x8002,
पूर्ण;

/*
 * definitions क्रम CT reason code
 */
क्रमागत अणु
	CT_RSN_INV_CMD		= 0x01,
	CT_RSN_INV_VER		= 0x02,
	CT_RSN_LOGIC_ERR	= 0x03,
	CT_RSN_INV_SIZE		= 0x04,
	CT_RSN_LOGICAL_BUSY	= 0x05,
	CT_RSN_PROTO_ERR	= 0x07,
	CT_RSN_UNABLE_TO_PERF	= 0x09,
	CT_RSN_NOT_SUPP		= 0x0B,
	CT_RSN_SERVER_NOT_AVBL  = 0x0D,
	CT_RSN_SESSION_COULD_NOT_BE_ESTBD = 0x0E,
	CT_RSN_VENDOR_SPECIFIC  = 0xFF,

पूर्ण;

/*
 * definitions क्रम explanations code क्रम Name server
 */
क्रमागत अणु
	CT_NS_EXP_NOADDITIONAL	= 0x00,
	CT_NS_EXP_ID_NOT_REG	= 0x01,
	CT_NS_EXP_PN_NOT_REG	= 0x02,
	CT_NS_EXP_NN_NOT_REG	= 0x03,
	CT_NS_EXP_CS_NOT_REG	= 0x04,
	CT_NS_EXP_IPN_NOT_REG	= 0x05,
	CT_NS_EXP_IPA_NOT_REG	= 0x06,
	CT_NS_EXP_FT_NOT_REG	= 0x07,
	CT_NS_EXP_SPN_NOT_REG	= 0x08,
	CT_NS_EXP_SNN_NOT_REG	= 0x09,
	CT_NS_EXP_PT_NOT_REG	= 0x0A,
	CT_NS_EXP_IPP_NOT_REG	= 0x0B,
	CT_NS_EXP_FPN_NOT_REG	= 0x0C,
	CT_NS_EXP_HA_NOT_REG	= 0x0D,
	CT_NS_EXP_FD_NOT_REG	= 0x0E,
	CT_NS_EXP_FF_NOT_REG	= 0x0F,
	CT_NS_EXP_ACCESSDENIED	= 0x10,
	CT_NS_EXP_UNACCEPTABLE_ID = 0x11,
	CT_NS_EXP_DATABASEEMPTY		= 0x12,
	CT_NS_EXP_NOT_REG_IN_SCOPE	= 0x13,
	CT_NS_EXP_DOM_ID_NOT_PRESENT	= 0x14,
	CT_NS_EXP_PORT_NUM_NOT_PRESENT	= 0x15,
	CT_NS_EXP_NO_DEVICE_ATTACHED	= 0x16
पूर्ण;

/*
 * definitions क्रम the explanation code क्रम all servers
 */
क्रमागत अणु
	CT_EXP_AUTH_EXCEPTION		= 0xF1,
	CT_EXP_DB_FULL			= 0xF2,
	CT_EXP_DB_EMPTY			= 0xF3,
	CT_EXP_PROCESSING_REQ		= 0xF4,
	CT_EXP_UNABLE_TO_VERIFY_CONN	= 0xF5,
	CT_EXP_DEVICES_NOT_IN_CMN_ZONE  = 0xF6
पूर्ण;

/*
 * Command codes क्रम Name server
 */
क्रमागत अणु
	GS_GID_PN	= 0x0121,	/* Get Id on port name */
	GS_GPN_ID	= 0x0112,	/* Get port name on ID */
	GS_GNN_ID	= 0x0113,	/* Get node name on ID */
	GS_GID_FT	= 0x0171,	/* Get Id on FC4 type */
	GS_GSPN_ID	= 0x0118,	/* Get symbolic PN on ID */
	GS_RFT_ID	= 0x0217,	/* Register fc4type on ID */
	GS_RSPN_ID	= 0x0218,	/* Register symbolic PN on ID */
	GS_RSNN_NN	= 0x0239,	/* Register symbolic NN on NN */
	GS_RPN_ID	= 0x0212,	/* Register port name */
	GS_RNN_ID	= 0x0213,	/* Register node name */
	GS_RCS_ID	= 0x0214,	/* Register class of service */
	GS_RPT_ID	= 0x021A,	/* Register port type */
	GS_GA_NXT	= 0x0100,	/* Get all next */
	GS_RFF_ID	= 0x021F,	/* Register FC4 Feature		*/
पूर्ण;

काष्ठा fcgs_id_req_s अणु
	u32 rsvd:8;
	u32 dap:24; /* port identअगरier */
पूर्ण;
#घोषणा fcgs_gpnid_req_t काष्ठा fcgs_id_req_s
#घोषणा fcgs_gnnid_req_t काष्ठा fcgs_id_req_s
#घोषणा fcgs_gspnid_req_t काष्ठा fcgs_id_req_s

काष्ठा fcgs_gidpn_req_s अणु
	wwn_t	port_name;	/* port wwn */
पूर्ण;

काष्ठा fcgs_gidpn_resp_s अणु
	u32	rsvd:8;
	u32	dap:24;		/* port identअगरier */
पूर्ण;

/*
 * RFT_ID
 */
काष्ठा fcgs_rftid_req_s अणु
	u32	rsvd:8;
	u32	dap:24;		/* port identअगरier */
	__be32	fc4_type[8];	/* fc4 types */
पूर्ण;

/*
 * RFF_ID : Register FC4 features.
 */
#घोषणा FC_GS_FCP_FC4_FEATURE_INITIATOR  0x02
#घोषणा FC_GS_FCP_FC4_FEATURE_TARGET	 0x01

काष्ठा fcgs_rffid_req_s अणु
	u32	rsvd:8;
	u32	dap:24;		/* port identअगरier */
	u32	rsvd1:16;
	u32	fc4ftr_bits:8;	/* fc4 feature bits */
	u32	fc4_type:8;		/* corresponding FC4 Type */
पूर्ण;

/*
 * GID_FT Request
 */
काष्ठा fcgs_gidft_req_s अणु
	u8	reserved;
	u8	करोमुख्य_id;	/* करोमुख्य, 0 - all fabric */
	u8	area_id;	/* area, 0 - whole करोमुख्य */
	u8	fc4_type;	/* FC_TYPE_FCP क्रम SCSI devices */
पूर्ण;

/*
 * GID_FT Response
 */
काष्ठा fcgs_gidft_resp_s अणु
	u8	last:1;		/* last port identअगरier flag */
	u8	reserved:7;
	u32	pid:24;		/* port identअगरier */
पूर्ण;

/*
 * RSPN_ID
 */
काष्ठा fcgs_rspnid_req_s अणु
	u32	rsvd:8;
	u32	dap:24;		/* port identअगरier */
	u8	spn_len;	/* symbolic port name length */
	u8	spn[256];	/* symbolic port name */
पूर्ण;

/*
 * RSNN_NN
 */
काष्ठा fcgs_rsnn_nn_req_s अणु
	wwn_t	node_name;	/* Node name */
	u8	snn_len;	/* symbolic node name length */
	u8	snn[256];	/* symbolic node name */
पूर्ण;

/*
 * RPN_ID
 */
काष्ठा fcgs_rpnid_req_s अणु
	u32	rsvd:8;
	u32	port_id:24;
	wwn_t	port_name;
पूर्ण;

/*
 * RNN_ID
 */
काष्ठा fcgs_rnnid_req_s अणु
	u32	rsvd:8;
	u32	port_id:24;
	wwn_t	node_name;
पूर्ण;

/*
 * RCS_ID
 */
काष्ठा fcgs_rcsid_req_s अणु
	u32	rsvd:8;
	u32	port_id:24;
	u32	cos;
पूर्ण;

/*
 * RPT_ID
 */
काष्ठा fcgs_rptid_req_s अणु
	u32	rsvd:8;
	u32	port_id:24;
	u32	port_type:8;
	u32	rsvd1:24;
पूर्ण;

/*
 * GA_NXT Request
 */
काष्ठा fcgs_ganxt_req_s अणु
	u32	rsvd:8;
	u32	port_id:24;
पूर्ण;

/*
 * GA_NXT Response
 */
काष्ठा fcgs_ganxt_rsp_s अणु
	u32		port_type:8;	/* Port Type */
	u32		port_id:24;	/* Port Identअगरier */
	wwn_t		port_name;	/* Port Name */
	u8		spn_len;	/* Length of Symbolic Port Name */
	अक्षर		spn[255];	/* Symbolic Port Name */
	wwn_t		node_name;	/* Node Name */
	u8		snn_len;	/* Length of Symbolic Node Name */
	अक्षर		snn[255];	/* Symbolic Node Name */
	u8		ipa[8];		/* Initial Process Associator */
	u8		ip[16];		/* IP Address */
	u32		cos;		/* Class of Service */
	u32		fc4types[8];	/* FC-4 TYPEs */
	wwn_t		fabric_port_name; /* Fabric Port Name */
	u32		rsvd:8;		/* Reserved */
	u32		hard_addr:24;	/* Hard Address */
पूर्ण;

/*
 * Command codes क्रम Fabric Configuration Server
 */
क्रमागत अणु
	GS_FC_GFN_CMD	= 0x0114,	/* GS FC Get Fabric Name  */
	GS_FC_GMAL_CMD	= 0x0116,	/* GS FC GMAL  */
	GS_FC_TRACE_CMD	= 0x0400,	/* GS FC Trace Route */
	GS_FC_PING_CMD	= 0x0401,	/* GS FC Ping */
पूर्ण;

/*
 * GMAL Command ( Get ( पूर्णांकerconnect Element) Management Address List)
 * To retrieve the IP Address of a Switch.
 */
#घोषणा CT_GMAL_RESP_PREFIX_TELNET	 "telnet://"
#घोषणा CT_GMAL_RESP_PREFIX_HTTP	 "http://"

/*  GMAL/GFN request */
काष्ठा fcgs_req_s अणु
	wwn_t    wwn;   /* PWWN/NWWN */
पूर्ण;

#घोषणा fcgs_gmal_req_t काष्ठा fcgs_req_s
#घोषणा fcgs_gfn_req_t काष्ठा fcgs_req_s

/* Accept Response to GMAL */
काष्ठा fcgs_gmal_resp_s अणु
	__be32	ms_len;   /* Num of entries */
	u8	ms_ma[256];
पूर्ण;

काष्ठा fcgs_gmal_entry_s अणु
	u8  len;
	u8  prefix[7]; /* like "http://" */
	u8  ip_addr[248];
पूर्ण;

/*
 * FDMI Command Codes
 */
#घोषणा	FDMI_GRHL		0x0100
#घोषणा	FDMI_GHAT		0x0101
#घोषणा	FDMI_GRPL		0x0102
#घोषणा	FDMI_GPAT		0x0110
#घोषणा	FDMI_RHBA		0x0200
#घोषणा	FDMI_RHAT		0x0201
#घोषणा	FDMI_RPRT		0x0210
#घोषणा	FDMI_RPA		0x0211
#घोषणा	FDMI_DHBA		0x0300
#घोषणा	FDMI_DPRT		0x0310

/*
 * FDMI reason codes
 */
#घोषणा	FDMI_NO_ADDITIONAL_EXP		0x00
#घोषणा	FDMI_HBA_ALREADY_REG		0x10
#घोषणा	FDMI_HBA_ATTRIB_NOT_REG		0x11
#घोषणा	FDMI_HBA_ATTRIB_MULTIPLE	0x12
#घोषणा	FDMI_HBA_ATTRIB_LENGTH_INVALID	0x13
#घोषणा	FDMI_HBA_ATTRIB_NOT_PRESENT	0x14
#घोषणा	FDMI_PORT_ORIG_NOT_IN_LIST	0x15
#घोषणा	FDMI_PORT_HBA_NOT_IN_LIST	0x16
#घोषणा	FDMI_PORT_ATTRIB_NOT_REG	0x20
#घोषणा	FDMI_PORT_NOT_REG		0x21
#घोषणा	FDMI_PORT_ATTRIB_MULTIPLE	0x22
#घोषणा	FDMI_PORT_ATTRIB_LENGTH_INVALID	0x23
#घोषणा	FDMI_PORT_ALREADY_REGISTEREED	0x24

/*
 * FDMI Transmission Speed Mask values
 */
#घोषणा	FDMI_TRANS_SPEED_1G		0x00000001
#घोषणा	FDMI_TRANS_SPEED_2G		0x00000002
#घोषणा	FDMI_TRANS_SPEED_10G		0x00000004
#घोषणा	FDMI_TRANS_SPEED_4G		0x00000008
#घोषणा	FDMI_TRANS_SPEED_8G		0x00000010
#घोषणा	FDMI_TRANS_SPEED_16G		0x00000020
#घोषणा	FDMI_TRANS_SPEED_UNKNOWN	0x00008000

/*
 * FDMI HBA attribute types
 */
क्रमागत fdmi_hba_attribute_type अणु
	FDMI_HBA_ATTRIB_NODENAME = 1,	/* 0x0001 */
	FDMI_HBA_ATTRIB_MANUFACTURER,	/* 0x0002 */
	FDMI_HBA_ATTRIB_SERIALNUM,	/* 0x0003 */
	FDMI_HBA_ATTRIB_MODEL,		/* 0x0004 */
	FDMI_HBA_ATTRIB_MODEL_DESC,	/* 0x0005 */
	FDMI_HBA_ATTRIB_HW_VERSION,	/* 0x0006 */
	FDMI_HBA_ATTRIB_DRIVER_VERSION,	/* 0x0007 */
	FDMI_HBA_ATTRIB_ROM_VERSION,	/* 0x0008 */
	FDMI_HBA_ATTRIB_FW_VERSION,	/* 0x0009 */
	FDMI_HBA_ATTRIB_OS_NAME,	/* 0x000A */
	FDMI_HBA_ATTRIB_MAX_CT,		/* 0x000B */
	FDMI_HBA_ATTRIB_NODE_SYM_NAME,  /* 0x000C */
	FDMI_HBA_ATTRIB_VENDOR_INFO,    /* 0x000D */
	FDMI_HBA_ATTRIB_NUM_PORTS,  /* 0x000E */
	FDMI_HBA_ATTRIB_FABRIC_NAME,    /* 0x000F */
	FDMI_HBA_ATTRIB_BIOS_VER,   /* 0x0010 */
	FDMI_HBA_ATTRIB_VENDOR_ID = 0x00E0,

	FDMI_HBA_ATTRIB_MAX_TYPE
पूर्ण;

/*
 * FDMI Port attribute types
 */
क्रमागत fdmi_port_attribute_type अणु
	FDMI_PORT_ATTRIB_FC4_TYPES = 1,	/* 0x0001 */
	FDMI_PORT_ATTRIB_SUPP_SPEED,	/* 0x0002 */
	FDMI_PORT_ATTRIB_PORT_SPEED,	/* 0x0003 */
	FDMI_PORT_ATTRIB_FRAME_SIZE,	/* 0x0004 */
	FDMI_PORT_ATTRIB_DEV_NAME,	/* 0x0005 */
	FDMI_PORT_ATTRIB_HOST_NAME,	/* 0x0006 */
	FDMI_PORT_ATTRIB_NODE_NAME,     /* 0x0007 */
	FDMI_PORT_ATTRIB_PORT_NAME,     /* 0x0008 */
	FDMI_PORT_ATTRIB_PORT_SYM_NAME, /* 0x0009 */
	FDMI_PORT_ATTRIB_PORT_TYPE,     /* 0x000A */
	FDMI_PORT_ATTRIB_SUPP_COS,      /* 0x000B */
	FDMI_PORT_ATTRIB_PORT_FAB_NAME, /* 0x000C */
	FDMI_PORT_ATTRIB_PORT_FC4_TYPE, /* 0x000D */
	FDMI_PORT_ATTRIB_PORT_STATE = 0x101,    /* 0x0101 */
	FDMI_PORT_ATTRIB_PORT_NUM_RPRT = 0x102, /* 0x0102 */

	FDMI_PORT_ATTR_MAX_TYPE
पूर्ण;

/*
 * FDMI attribute
 */
काष्ठा fdmi_attr_s अणु
	__be16        type;
	__be16        len;
	u8         value[1];
पूर्ण;

/*
 * HBA Attribute Block
 */
काष्ठा fdmi_hba_attr_s अणु
	__be32        attr_count;	/* # of attributes */
	काष्ठा fdmi_attr_s hba_attr;	/* n attributes */
पूर्ण;

/*
 * Registered Port List
 */
काष्ठा fdmi_port_list_s अणु
	__be32		num_ports;	/* number Of Port Entries */
	wwn_t		port_entry;	/* one or more */
पूर्ण;

/*
 * Port Attribute Block
 */
काष्ठा fdmi_port_attr_s अणु
	__be32        attr_count;	/* # of attributes */
	काष्ठा fdmi_attr_s port_attr;	/* n attributes */
पूर्ण;

/*
 * FDMI Register HBA Attributes
 */
काष्ठा fdmi_rhba_s अणु
	wwn_t			hba_id;		/* HBA Identअगरier */
	काष्ठा fdmi_port_list_s port_list;	/* Registered Port List */
	काष्ठा fdmi_hba_attr_s hba_attr_blk;	/* HBA attribute block */
पूर्ण;

/*
 * FDMI Register Port
 */
काष्ठा fdmi_rprt_s अणु
	wwn_t			hba_id;		/* HBA Identअगरier */
	wwn_t			port_name;	/* Port wwn */
	काष्ठा fdmi_port_attr_s port_attr_blk;	/* Port Attr Block */
पूर्ण;

/*
 * FDMI Register Port Attributes
 */
काष्ठा fdmi_rpa_s अणु
	wwn_t			port_name;	/* port wwn */
	काष्ठा fdmi_port_attr_s port_attr_blk;	/* Port Attr Block */
पूर्ण;

#आशय pack()

#पूर्ण_अगर	/* __BFA_FC_H__ */
