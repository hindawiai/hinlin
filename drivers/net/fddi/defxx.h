<शैली गुरु>
/*
 * File Name:
 *   defxx.h
 *
 * Copyright Inक्रमmation:
 *   Copyright Digital Equipment Corporation 1996.
 *
 *   This software may be used and distributed according to the terms of
 *   the GNU General Public License, incorporated herein by reference.
 *
 * Abstract:
 *   Contains all definitions specअगरied by port specअगरication and required
 *   by the defxx.c driver.
 *
 * The original author:
 *   LVS	Lawrence V. Stefani <lstefani@yahoo.com>
 *
 * Maपूर्णांकainers:
 *   macro	Maciej W. Rozycki <macro@orcam.me.uk>
 *
 * Modअगरication History:
 *		Date		Name	Description
 *		16-Aug-96	LVS		Created.
 *		09-Sep-96	LVS		Added group_prom field.  Moved पढ़ो/ग_लिखो I/O
 *							macros to DEFXX.C.
 *		12-Sep-96	LVS		Removed packet request header poपूर्णांकers.
 *		04 Aug 2003	macro		Converted to the DMA API.
 *		23 Oct 2006	macro		Big-endian host support.
 *		14 Dec 2006	macro		TURBOchannel support.
 *		10 Mar 2021	macro		Dynamic MMIO vs port I/O.
 */

#अगर_अघोषित _DEFXX_H_
#घोषणा _DEFXX_H_

/* Define basic types क्रम अचिन्हित अक्षरs, लघुs, दीर्घs */

प्रकार u8	PI_UINT8;
प्रकार u16	PI_UINT16;
प्रकार u32	PI_UINT32;

/* Define general काष्ठाures */

प्रकार काष्ठा							/* 64-bit counter */
	अणु
	PI_UINT32  ms;
	PI_UINT32  ls;
	पूर्ण PI_CNTR;

प्रकार काष्ठा							/* LAN address */
	अणु
	PI_UINT32  lwrd_0;
	PI_UINT32  lwrd_1;
	पूर्ण PI_LAN_ADDR;

प्रकार काष्ठा							/* Station ID address */
	अणु
	PI_UINT32  octet_7_4;
	PI_UINT32  octet_3_0;
	पूर्ण PI_STATION_ID;


/* Define general स्थिरants */

#घोषणा PI_ALIGN_K_DESC_BLK	  			8192	/* Descriptor block boundary		*/
#घोषणा PI_ALIGN_K_CONS_BLK	  	 		64		/* Consumer block boundary		  	*/
#घोषणा PI_ALIGN_K_CMD_REQ_BUFF  		128	 	/* Xmt Command que buffer alignment */
#घोषणा PI_ALIGN_K_CMD_RSP_BUFF	 		128	 	/* Rcv Command que buffer alignment */
#घोषणा PI_ALIGN_K_UNSOL_BUFF	 		128	 	/* Unsol que buffer alignment	   	*/
#घोषणा PI_ALIGN_K_XMT_DATA_BUFF 		0	   	/* Xmt data que buffer alignment	*/
#घोषणा PI_ALIGN_K_RCV_DATA_BUFF 		128	 	/* Rcv que buffer alignment			*/

/* Define PHY index values */

#घोषणा PI_PHY_K_S						0		/* Index to S phy */
#घोषणा PI_PHY_K_A						0		/* Index to A phy */
#घोषणा PI_PHY_K_B						1		/* Index to B phy */
#घोषणा PI_PHY_K_MAX					2		/* Max number of phys */

/* Define FMC descriptor fields */

#घोषणा PI_FMC_DESCR_V_SOP				31
#घोषणा PI_FMC_DESCR_V_EOP				30
#घोषणा PI_FMC_DESCR_V_FSC				27
#घोषणा PI_FMC_DESCR_V_FSB_ERROR		26
#घोषणा PI_FMC_DESCR_V_FSB_ADDR_RECOG	25
#घोषणा PI_FMC_DESCR_V_FSB_ADDR_COPIED	24
#घोषणा PI_FMC_DESCR_V_FSB				22
#घोषणा PI_FMC_DESCR_V_RCC_FLUSH		21
#घोषणा PI_FMC_DESCR_V_RCC_CRC			20
#घोषणा PI_FMC_DESCR_V_RCC_RRR			17
#घोषणा PI_FMC_DESCR_V_RCC_DD			15
#घोषणा PI_FMC_DESCR_V_RCC_SS			13
#घोषणा PI_FMC_DESCR_V_RCC				13
#घोषणा PI_FMC_DESCR_V_LEN				0

#घोषणा PI_FMC_DESCR_M_SOP				0x80000000
#घोषणा PI_FMC_DESCR_M_EOP				0x40000000
#घोषणा PI_FMC_DESCR_M_FSC				0x38000000
#घोषणा PI_FMC_DESCR_M_FSB_ERROR		0x04000000
#घोषणा PI_FMC_DESCR_M_FSB_ADDR_RECOG	0x02000000
#घोषणा PI_FMC_DESCR_M_FSB_ADDR_COPIED	0x01000000
#घोषणा PI_FMC_DESCR_M_FSB				0x07C00000
#घोषणा PI_FMC_DESCR_M_RCC_FLUSH		0x00200000
#घोषणा PI_FMC_DESCR_M_RCC_CRC			0x00100000
#घोषणा PI_FMC_DESCR_M_RCC_RRR			0x000E0000
#घोषणा PI_FMC_DESCR_M_RCC_DD			0x00018000
#घोषणा PI_FMC_DESCR_M_RCC_SS			0x00006000
#घोषणा PI_FMC_DESCR_M_RCC				0x003FE000
#घोषणा PI_FMC_DESCR_M_LEN				0x00001FFF

#घोषणा PI_FMC_DESCR_K_RCC_FMC_INT_ERR	0x01AA

#घोषणा PI_FMC_DESCR_K_RRR_SUCCESS		0x00
#घोषणा PI_FMC_DESCR_K_RRR_SA_MATCH		0x01
#घोषणा PI_FMC_DESCR_K_RRR_DA_MATCH		0x02
#घोषणा PI_FMC_DESCR_K_RRR_FMC_ABORT	0x03
#घोषणा PI_FMC_DESCR_K_RRR_LENGTH_BAD	0x04
#घोषणा PI_FMC_DESCR_K_RRR_FRAGMENT		0x05
#घोषणा PI_FMC_DESCR_K_RRR_FORMAT_ERR	0x06
#घोषणा PI_FMC_DESCR_K_RRR_MAC_RESET	0x07

#घोषणा PI_FMC_DESCR_K_DD_NO_MATCH		0x0
#घोषणा PI_FMC_DESCR_K_DD_PROMISCUOUS	0x1
#घोषणा PI_FMC_DESCR_K_DD_CAM_MATCH		0x2
#घोषणा PI_FMC_DESCR_K_DD_LOCAL_MATCH	0x3

#घोषणा PI_FMC_DESCR_K_SS_NO_MATCH		0x0
#घोषणा PI_FMC_DESCR_K_SS_BRIDGE_MATCH	0x1
#घोषणा PI_FMC_DESCR_K_SS_NOT_POSSIBLE	0x2
#घोषणा PI_FMC_DESCR_K_SS_LOCAL_MATCH	0x3

/* Define some max buffer sizes */

#घोषणा PI_CMD_REQ_K_SIZE_MAX			512
#घोषणा PI_CMD_RSP_K_SIZE_MAX			512
#घोषणा PI_UNSOL_K_SIZE_MAX				512
#घोषणा PI_SMT_HOST_K_SIZE_MAX			4608		/* 4 1/2 K */
#घोषणा PI_RCV_DATA_K_SIZE_MAX			4608		/* 4 1/2 K */
#घोषणा PI_XMT_DATA_K_SIZE_MAX			4608		/* 4 1/2 K */

/* Define adapter states */

#घोषणा PI_STATE_K_RESET				0
#घोषणा PI_STATE_K_UPGRADE		  		1
#घोषणा PI_STATE_K_DMA_UNAVAIL			2
#घोषणा PI_STATE_K_DMA_AVAIL			3
#घोषणा PI_STATE_K_LINK_AVAIL			4
#घोषणा PI_STATE_K_LINK_UNAVAIL	 		5
#घोषणा PI_STATE_K_HALTED		   		6
#घोषणा PI_STATE_K_RING_MEMBER			7
#घोषणा PI_STATE_K_NUMBER				8

/* Define codes क्रम command type */

#घोषणा PI_CMD_K_START					0x00
#घोषणा PI_CMD_K_FILTERS_SET			0x01
#घोषणा PI_CMD_K_FILTERS_GET			0x02
#घोषणा PI_CMD_K_CHARS_SET				0x03
#घोषणा PI_CMD_K_STATUS_CHARS_GET		0x04
#घोषणा PI_CMD_K_CNTRS_GET				0x05
#घोषणा PI_CMD_K_CNTRS_SET				0x06
#घोषणा PI_CMD_K_ADDR_FILTER_SET		0x07
#घोषणा PI_CMD_K_ADDR_FILTER_GET		0x08
#घोषणा PI_CMD_K_ERROR_LOG_CLEAR		0x09
#घोषणा PI_CMD_K_ERROR_LOG_GET			0x0A
#घोषणा PI_CMD_K_FDDI_MIB_GET			0x0B
#घोषणा PI_CMD_K_DEC_EXT_MIB_GET		0x0C
#घोषणा PI_CMD_K_DEVICE_SPECIFIC_GET	0x0D
#घोषणा PI_CMD_K_SNMP_SET				0x0E
#घोषणा PI_CMD_K_UNSOL_TEST				0x0F
#घोषणा PI_CMD_K_SMT_MIB_GET			0x10
#घोषणा PI_CMD_K_SMT_MIB_SET			0x11
#घोषणा PI_CMD_K_MAX					0x11	/* Must match last */

/* Define item codes क्रम Chars_Set and Filters_Set commands */

#घोषणा PI_ITEM_K_EOL					0x00 	/* End-of-Item list 		  */
#घोषणा PI_ITEM_K_T_REQ					0x01 	/* DECnet T_REQ 			  */
#घोषणा PI_ITEM_K_TVX					0x02 	/* DECnet TVX 				  */
#घोषणा PI_ITEM_K_RESTRICTED_TOKEN		0x03 	/* DECnet Restricted Token 	  */
#घोषणा PI_ITEM_K_LEM_THRESHOLD			0x04 	/* DECnet LEM Threshold 	  */
#घोषणा PI_ITEM_K_RING_PURGER			0x05 	/* DECnet Ring Purger Enable  */
#घोषणा PI_ITEM_K_CNTR_INTERVAL			0x06 	/* Chars_Set 				  */
#घोषणा PI_ITEM_K_IND_GROUP_PROM		0x07 	/* Filters_Set 				  */
#घोषणा PI_ITEM_K_GROUP_PROM			0x08 	/* Filters_Set 				  */
#घोषणा PI_ITEM_K_BROADCAST				0x09 	/* Filters_Set 				  */
#घोषणा PI_ITEM_K_SMT_PROM				0x0A 	/* Filters_Set				  */
#घोषणा PI_ITEM_K_SMT_USER				0x0B 	/* Filters_Set 				  */
#घोषणा PI_ITEM_K_RESERVED				0x0C 	/* Filters_Set 				  */
#घोषणा PI_ITEM_K_IMPLEMENTOR			0x0D 	/* Filters_Set 				  */
#घोषणा PI_ITEM_K_LOOPBACK_MODE			0x0E 	/* Chars_Set 				  */
#घोषणा PI_ITEM_K_CONFIG_POLICY			0x10 	/* SMTConfigPolicy 			  */
#घोषणा PI_ITEM_K_CON_POLICY			0x11 	/* SMTConnectionPolicy 		  */
#घोषणा PI_ITEM_K_T_NOTIFY				0x12 	/* SMTTNotअगरy 				  */
#घोषणा PI_ITEM_K_STATION_ACTION		0x13 	/* SMTStationAction			  */
#घोषणा PI_ITEM_K_MAC_PATHS_REQ	   		0x15 	/* MACPathsRequested 		  */
#घोषणा PI_ITEM_K_MAC_ACTION			0x17 	/* MACAction 				  */
#घोषणा PI_ITEM_K_CON_POLICIES			0x18 	/* PORTConnectionPolicies	  */
#घोषणा PI_ITEM_K_PORT_PATHS_REQ		0x19 	/* PORTPathsRequested 		  */
#घोषणा PI_ITEM_K_MAC_LOOP_TIME			0x1A 	/* PORTMACLoopTime 			  */
#घोषणा PI_ITEM_K_TB_MAX				0x1B 	/* PORTTBMax 				  */
#घोषणा PI_ITEM_K_LER_CUTOFF			0x1C 	/* PORTLerCutoff 			  */
#घोषणा PI_ITEM_K_LER_ALARM				0x1D 	/* PORTLerAlarm 			  */
#घोषणा PI_ITEM_K_PORT_ACTION			0x1E 	/* PORTAction 				  */
#घोषणा PI_ITEM_K_FLUSH_TIME			0x20 	/* Chars_Set 				  */
#घोषणा PI_ITEM_K_MAC_T_REQ				0x29 	/* MACTReq 					  */
#घोषणा PI_ITEM_K_EMAC_RING_PURGER		0x2A 	/* eMACRingPurgerEnable		  */
#घोषणा PI_ITEM_K_EMAC_RTOKEN_TIMEOUT	0x2B 	/* eMACRestrictedTokenTimeout */
#घोषणा PI_ITEM_K_FDX_ENB_DIS			0x2C 	/* eFDXEnable				  */
#घोषणा PI_ITEM_K_MAX					0x2C 	/* Must equal high item		  */

/* Values क्रम some of the items */

#घोषणा PI_K_FALSE						0	   /* Generic false */
#घोषणा PI_K_TRUE						1	   /* Generic true  */

#घोषणा PI_SNMP_K_TRUE					1	   /* SNMP true/false values */
#घोषणा PI_SNMP_K_FALSE					2

#घोषणा PI_FSTATE_K_BLOCK				0	   /* Filter State */
#घोषणा PI_FSTATE_K_PASS				1

/* Define command वापस codes */

#घोषणा PI_RSP_K_SUCCESS				0x00
#घोषणा PI_RSP_K_FAILURE				0x01
#घोषणा PI_RSP_K_WARNING				0x02
#घोषणा PI_RSP_K_LOOP_MODE_BAD			0x03
#घोषणा PI_RSP_K_ITEM_CODE_BAD			0x04
#घोषणा PI_RSP_K_TVX_BAD				0x05
#घोषणा PI_RSP_K_TREQ_BAD				0x06
#घोषणा PI_RSP_K_TOKEN_BAD				0x07
#घोषणा PI_RSP_K_NO_EOL					0x0C
#घोषणा PI_RSP_K_FILTER_STATE_BAD		0x0D
#घोषणा PI_RSP_K_CMD_TYPE_BAD			0x0E
#घोषणा PI_RSP_K_ADAPTER_STATE_BAD		0x0F
#घोषणा PI_RSP_K_RING_PURGER_BAD		0x10
#घोषणा PI_RSP_K_LEM_THRESHOLD_BAD		0x11
#घोषणा PI_RSP_K_LOOP_NOT_SUPPORTED		0x12
#घोषणा PI_RSP_K_FLUSH_TIME_BAD			0x13
#घोषणा PI_RSP_K_NOT_IMPLEMENTED		0x14
#घोषणा PI_RSP_K_CONFIG_POLICY_BAD		0x15
#घोषणा PI_RSP_K_STATION_ACTION_BAD		0x16
#घोषणा PI_RSP_K_MAC_ACTION_BAD			0x17
#घोषणा PI_RSP_K_CON_POLICIES_BAD		0x18
#घोषणा PI_RSP_K_MAC_LOOP_TIME_BAD		0x19
#घोषणा PI_RSP_K_TB_MAX_BAD				0x1A
#घोषणा PI_RSP_K_LER_CUTOFF_BAD			0x1B
#घोषणा PI_RSP_K_LER_ALARM_BAD			0x1C
#घोषणा PI_RSP_K_MAC_PATHS_REQ_BAD		0x1D
#घोषणा PI_RSP_K_MAC_T_REQ_BAD			0x1E
#घोषणा PI_RSP_K_EMAC_RING_PURGER_BAD	0x1F
#घोषणा PI_RSP_K_EMAC_RTOKEN_TIME_BAD	0x20
#घोषणा PI_RSP_K_NO_SUCH_ENTRY			0x21
#घोषणा PI_RSP_K_T_NOTIFY_BAD			0x22
#घोषणा PI_RSP_K_TR_MAX_EXP_BAD			0x23
#घोषणा PI_RSP_K_MAC_FRM_ERR_THR_BAD	0x24
#घोषणा PI_RSP_K_MAX_T_REQ_BAD			0x25
#घोषणा PI_RSP_K_FDX_ENB_DIS_BAD		0x26
#घोषणा PI_RSP_K_ITEM_INDEX_BAD			0x27
#घोषणा PI_RSP_K_PORT_ACTION_BAD		0x28

/* Commonly used काष्ठाures */

प्रकार काष्ठा									/* Item list */
	अणु
	PI_UINT32  item_code;
	PI_UINT32  value;
	पूर्ण PI_ITEM_LIST;

प्रकार काष्ठा									/* Response header */
	अणु
	PI_UINT32  reserved;
	PI_UINT32  cmd_type;
	PI_UINT32  status;
	पूर्ण PI_RSP_HEADER;


/* Start Command */

प्रकार काष्ठा
	अणु
	PI_UINT32  cmd_type;
	पूर्ण PI_CMD_START_REQ;

/* Start Response */

प्रकार काष्ठा
	अणु
	PI_RSP_HEADER   header;
	पूर्ण PI_CMD_START_RSP;

/* Filters_Set Request */

#घोषणा PI_CMD_FILTERS_SET_K_ITEMS_MAX  63		/* Fits in a 512 byte buffer */

प्रकार काष्ठा
	अणु
	PI_UINT32		cmd_type;
	PI_ITEM_LIST	item[PI_CMD_FILTERS_SET_K_ITEMS_MAX];
	पूर्ण PI_CMD_FILTERS_SET_REQ;

/* Filters_Set Response */

प्रकार काष्ठा
	अणु
	PI_RSP_HEADER   header;
	पूर्ण PI_CMD_FILTERS_SET_RSP;

/* Filters_Get Request */

प्रकार काष्ठा
	अणु
	PI_UINT32		cmd_type;
	पूर्ण PI_CMD_FILTERS_GET_REQ;

/* Filters_Get Response */

प्रकार काष्ठा
	अणु
	PI_RSP_HEADER   header;
	PI_UINT32		ind_group_prom;
	PI_UINT32		group_prom;
	PI_UINT32		broadcast_all;
	PI_UINT32		smt_all;
	PI_UINT32		smt_user;
	PI_UINT32		reserved_all;
	PI_UINT32		implementor_all;
	पूर्ण PI_CMD_FILTERS_GET_RSP;


/* Chars_Set Request */

#घोषणा PI_CMD_CHARS_SET_K_ITEMS_MAX 42		/* Fits in a 512 byte buffer */

प्रकार काष्ठा
	अणु
	PI_UINT32		cmd_type;
	काष्ठा							  		/* Item list */
		अणु
		PI_UINT32	item_code;
		PI_UINT32	value;
		PI_UINT32	item_index;
		पूर्ण item[PI_CMD_CHARS_SET_K_ITEMS_MAX];
	पूर्ण PI_CMD_CHARS_SET_REQ;

/* Chars_Set Response */

प्रकार काष्ठा
	अणु
	PI_RSP_HEADER   header;
	पूर्ण PI_CMD_CHARS_SET_RSP;


/* SNMP_Set Request */

#घोषणा PI_CMD_SNMP_SET_K_ITEMS_MAX 42	   	/* Fits in a 512 byte buffer */

प्रकार काष्ठा
	अणु
	PI_UINT32		cmd_type;
	काष्ठा							   		/* Item list */
		अणु
		PI_UINT32	item_code;
		PI_UINT32	value;
		PI_UINT32	item_index;
		पूर्ण item[PI_CMD_SNMP_SET_K_ITEMS_MAX];
	पूर्ण PI_CMD_SNMP_SET_REQ;

/* SNMP_Set Response */

प्रकार काष्ठा
	अणु
	PI_RSP_HEADER   header;
	पूर्ण PI_CMD_SNMP_SET_RSP;


/* SMT_MIB_Set Request */

#घोषणा PI_CMD_SMT_MIB_SET_K_ITEMS_MAX 42	/* Max number of items */

प्रकार काष्ठा
	अणु
	PI_UINT32	cmd_type;
	काष्ठा
		अणु
		PI_UINT32	item_code;
		PI_UINT32	value;
		PI_UINT32	item_index;
		पूर्ण item[PI_CMD_SMT_MIB_SET_K_ITEMS_MAX];
	पूर्ण PI_CMD_SMT_MIB_SET_REQ;

/* SMT_MIB_Set Response */

प्रकार काष्ठा
	अणु
	PI_RSP_HEADER   header;
	पूर्ण PI_CMD_SMT_MIB_SET_RSP;

/* SMT_MIB_Get Request */

प्रकार काष्ठा
	अणु
	PI_UINT32  cmd_type;
	पूर्ण PI_CMD_SMT_MIB_GET_REQ;

/* SMT_MIB_Get Response */

प्रकार काष्ठा						  /* Refer to ANSI FDDI SMT Rev. 7.3 */
	अणु
	PI_RSP_HEADER  header;

	/* SMT GROUP */

	PI_STATION_ID  	smt_station_id;
	PI_UINT32 		smt_op_version_id;
	PI_UINT32	   	smt_hi_version_id;
	PI_UINT32	   	smt_lo_version_id;
	PI_UINT32	   	smt_user_data[8];
	PI_UINT32	   	smt_mib_version_id;
	PI_UINT32	   	smt_mac_ct;
	PI_UINT32	   	smt_non_master_ct;
	PI_UINT32	   	smt_master_ct;
	PI_UINT32	   	smt_available_paths;
	PI_UINT32	   	smt_config_capabilities;
	PI_UINT32	   	smt_config_policy;
	PI_UINT32	   	smt_connection_policy;
	PI_UINT32	   	smt_t_notअगरy;
	PI_UINT32	   	smt_stat_rpt_policy;
	PI_UINT32	   	smt_trace_max_expiration;
	PI_UINT32	   	smt_bypass_present;
	PI_UINT32	  	smt_ecm_state;
	PI_UINT32	   	smt_cf_state;
	PI_UINT32	   	smt_remote_disconnect_flag;
	PI_UINT32	   	smt_station_status;
	PI_UINT32	   	smt_peer_wrap_flag;
	PI_CNTR	   		smt_msg_समय_stamp;
	PI_CNTR	  		smt_transition_समय_stamp;

	/* MAC GROUP */

	PI_UINT32		mac_frame_status_functions;
	PI_UINT32		mac_t_max_capability;
	PI_UINT32		mac_tvx_capability;
	PI_UINT32		mac_available_paths;
	PI_UINT32		mac_current_path;
	PI_LAN_ADDR		mac_upstream_nbr;
	PI_LAN_ADDR		mac_करोwnstream_nbr;
	PI_LAN_ADDR		mac_old_upstream_nbr;
	PI_LAN_ADDR		mac_old_करोwnstream_nbr;
	PI_UINT32	   	mac_dup_address_test;
	PI_UINT32	   	mac_requested_paths;
	PI_UINT32	   	mac_करोwnstream_port_type;
	PI_LAN_ADDR		mac_smt_address;
	PI_UINT32		mac_t_req;
	PI_UINT32		mac_t_neg;
	PI_UINT32		mac_t_max;
	PI_UINT32		mac_tvx_value;
	PI_UINT32		mac_frame_error_threshold;
	PI_UINT32		mac_frame_error_ratio;
	PI_UINT32		mac_rmt_state;
	PI_UINT32		mac_da_flag;
	PI_UINT32		mac_unda_flag;
	PI_UINT32		mac_frame_error_flag;
	PI_UINT32		mac_ma_unitdata_available;
	PI_UINT32		mac_hardware_present;
	PI_UINT32		mac_ma_unitdata_enable;

	/* PATH GROUP */

	PI_UINT32		path_configuration[8];
	PI_UINT32		path_tvx_lower_bound;
	PI_UINT32		path_t_max_lower_bound;
	PI_UINT32		path_max_t_req;

	/* PORT GROUP */

	PI_UINT32		port_my_type[PI_PHY_K_MAX];
	PI_UINT32		port_neighbor_type[PI_PHY_K_MAX];
	PI_UINT32		port_connection_policies[PI_PHY_K_MAX];
	PI_UINT32		port_mac_indicated[PI_PHY_K_MAX];
	PI_UINT32		port_current_path[PI_PHY_K_MAX];
	PI_UINT32		port_requested_paths[PI_PHY_K_MAX];
	PI_UINT32		port_mac_placement[PI_PHY_K_MAX];
	PI_UINT32		port_available_paths[PI_PHY_K_MAX];
	PI_UINT32		port_pmd_class[PI_PHY_K_MAX];
	PI_UINT32		port_connection_capabilities[PI_PHY_K_MAX];
	PI_UINT32		port_bs_flag[PI_PHY_K_MAX];
	PI_UINT32		port_ler_estimate[PI_PHY_K_MAX];
	PI_UINT32		port_ler_cutoff[PI_PHY_K_MAX];
	PI_UINT32		port_ler_alarm[PI_PHY_K_MAX];
	PI_UINT32		port_connect_state[PI_PHY_K_MAX];
	PI_UINT32		port_pcm_state[PI_PHY_K_MAX];
	PI_UINT32		port_pc_withhold[PI_PHY_K_MAX];
	PI_UINT32		port_ler_flag[PI_PHY_K_MAX];
	PI_UINT32		port_hardware_present[PI_PHY_K_MAX];

	/* GROUP क्रम things that were added later, so must be at the end. */

	PI_CNTR	   		path_ring_latency;

	पूर्ण PI_CMD_SMT_MIB_GET_RSP;


/*
 *  Item and group code definitions क्रम SMT 7.3 mandatory objects.  These
 *  definitions are to be used as appropriate in SMT_MIB_SET commands and
 *  certain host-sent SMT frames such as PMF Get and Set requests.  The
 *  codes have been taken from the MIB summary section of ANSI SMT 7.3.
 */

#घोषणा PI_GRP_K_SMT_STATION_ID			0x100A
#घोषणा PI_ITEM_K_SMT_STATION_ID		0x100B
#घोषणा PI_ITEM_K_SMT_OP_VERS_ID		0x100D
#घोषणा PI_ITEM_K_SMT_HI_VERS_ID		0x100E
#घोषणा PI_ITEM_K_SMT_LO_VERS_ID		0x100F
#घोषणा PI_ITEM_K_SMT_USER_DATA			0x1011
#घोषणा PI_ITEM_K_SMT_MIB_VERS_ID	  	0x1012

#घोषणा PI_GRP_K_SMT_STATION_CONFIG		0x1014
#घोषणा PI_ITEM_K_SMT_MAC_CT			0x1015
#घोषणा PI_ITEM_K_SMT_NON_MASTER_CT		0x1016
#घोषणा PI_ITEM_K_SMT_MASTER_CT			0x1017
#घोषणा PI_ITEM_K_SMT_AVAIL_PATHS		0x1018
#घोषणा PI_ITEM_K_SMT_CONFIG_CAPS		0x1019
#घोषणा PI_ITEM_K_SMT_CONFIG_POL		0x101A
#घोषणा PI_ITEM_K_SMT_CONN_POL			0x101B
#घोषणा PI_ITEM_K_SMT_T_NOTIFY			0x101D
#घोषणा PI_ITEM_K_SMT_STAT_POL			0x101E
#घोषणा PI_ITEM_K_SMT_TR_MAX_EXP		0x101F
#घोषणा PI_ITEM_K_SMT_PORT_INDEXES		0x1020
#घोषणा PI_ITEM_K_SMT_MAC_INDEXES		0x1021
#घोषणा PI_ITEM_K_SMT_BYPASS_PRESENT	0x1022

#घोषणा PI_GRP_K_SMT_STATUS				0x1028
#घोषणा PI_ITEM_K_SMT_ECM_STATE			0x1029
#घोषणा PI_ITEM_K_SMT_CF_STATE		 	0x102A
#घोषणा PI_ITEM_K_SMT_REM_DISC_FLAG		0x102C
#घोषणा PI_ITEM_K_SMT_STATION_STATUS	0x102D
#घोषणा PI_ITEM_K_SMT_PEER_WRAP_FLAG	0x102E

#घोषणा PI_GRP_K_SMT_MIB_OPERATION	 	0x1032
#घोषणा PI_ITEM_K_SMT_MSG_TIME_STAMP 	0x1033
#घोषणा PI_ITEM_K_SMT_TRN_TIME_STAMP 	0x1034

#घोषणा PI_ITEM_K_SMT_STATION_ACT		0x103C

#घोषणा PI_GRP_K_MAC_CAPABILITIES	  	0x200A
#घोषणा PI_ITEM_K_MAC_FRM_STAT_FUNC		0x200B
#घोषणा PI_ITEM_K_MAC_T_MAX_CAP			0x200D
#घोषणा PI_ITEM_K_MAC_TVX_CAP		  	0x200E

#घोषणा PI_GRP_K_MAC_CONFIG				0x2014
#घोषणा PI_ITEM_K_MAC_AVAIL_PATHS	  	0x2016
#घोषणा PI_ITEM_K_MAC_CURRENT_PATH	 	0x2017
#घोषणा PI_ITEM_K_MAC_UP_NBR			0x2018
#घोषणा PI_ITEM_K_MAC_DOWN_NBR			0x2019
#घोषणा PI_ITEM_K_MAC_OLD_UP_NBR	 	0x201A
#घोषणा PI_ITEM_K_MAC_OLD_DOWN_NBR	 	0x201B
#घोषणा PI_ITEM_K_MAC_DUP_ADDR_TEST		0x201D
#घोषणा PI_ITEM_K_MAC_REQ_PATHS			0x2020
#घोषणा PI_ITEM_K_MAC_DOWN_PORT_TYPE   	0x2021
#घोषणा PI_ITEM_K_MAC_INDEX				0x2022

#घोषणा PI_GRP_K_MAC_ADDRESS			0x2028
#घोषणा PI_ITEM_K_MAC_SMT_ADDRESS		0x2029

#घोषणा PI_GRP_K_MAC_OPERATION			0x2032
#घोषणा PI_ITEM_K_MAC_TREQ				0x2033
#घोषणा PI_ITEM_K_MAC_TNEG				0x2034
#घोषणा PI_ITEM_K_MAC_TMAX				0x2035
#घोषणा PI_ITEM_K_MAC_TVX_VALUE			0x2036

#घोषणा PI_GRP_K_MAC_COUNTERS			0x2046
#घोषणा PI_ITEM_K_MAC_FRAME_CT			0x2047
#घोषणा PI_ITEM_K_MAC_COPIED_CT			0x2048
#घोषणा PI_ITEM_K_MAC_TRANSMIT_CT		0x2049
#घोषणा PI_ITEM_K_MAC_ERROR_CT			0x2051
#घोषणा PI_ITEM_K_MAC_LOST_CT			0x2052

#घोषणा PI_GRP_K_MAC_FRM_ERR_COND		0x205A
#घोषणा PI_ITEM_K_MAC_FRM_ERR_THR		0x205F
#घोषणा PI_ITEM_K_MAC_FRM_ERR_RAT		0x2060

#घोषणा PI_GRP_K_MAC_STATUS				0x206E
#घोषणा PI_ITEM_K_MAC_RMT_STATE			0x206F
#घोषणा PI_ITEM_K_MAC_DA_FLAG			0x2070
#घोषणा PI_ITEM_K_MAC_UNDA_FLAG			0x2071
#घोषणा PI_ITEM_K_MAC_FRM_ERR_FLAG		0x2072
#घोषणा PI_ITEM_K_MAC_MA_UNIT_AVAIL		0x2074
#घोषणा PI_ITEM_K_MAC_HW_PRESENT		0x2075
#घोषणा PI_ITEM_K_MAC_MA_UNIT_ENAB		0x2076

#घोषणा PI_GRP_K_PATH_CONFIG			0x320A
#घोषणा PI_ITEM_K_PATH_INDEX			0x320B
#घोषणा PI_ITEM_K_PATH_CONFIGURATION 	0x3212
#घोषणा PI_ITEM_K_PATH_TVX_LB			0x3215
#घोषणा PI_ITEM_K_PATH_T_MAX_LB			0x3216
#घोषणा PI_ITEM_K_PATH_MAX_T_REQ		0x3217

#घोषणा PI_GRP_K_PORT_CONFIG			0x400A
#घोषणा PI_ITEM_K_PORT_MY_TYPE			0x400C
#घोषणा PI_ITEM_K_PORT_NBR_TYPE			0x400D
#घोषणा PI_ITEM_K_PORT_CONN_POLS		0x400E
#घोषणा PI_ITEM_K_PORT_MAC_INDICATED  	0x400F
#घोषणा PI_ITEM_K_PORT_CURRENT_PATH		0x4010
#घोषणा PI_ITEM_K_PORT_REQ_PATHS		0x4011
#घोषणा PI_ITEM_K_PORT_MAC_PLACEMENT 	0x4012
#घोषणा PI_ITEM_K_PORT_AVAIL_PATHS		0x4013
#घोषणा PI_ITEM_K_PORT_PMD_CLASS		0x4016
#घोषणा PI_ITEM_K_PORT_CONN_CAPS		0x4017
#घोषणा PI_ITEM_K_PORT_INDEX			0x401D

#घोषणा PI_GRP_K_PORT_OPERATION			0x401E
#घोषणा PI_ITEM_K_PORT_BS_FLAG		 	0x4021

#घोषणा PI_GRP_K_PORT_ERR_CNTRS			0x4028
#घोषणा PI_ITEM_K_PORT_LCT_FAIL_CT	 	0x402A

#घोषणा PI_GRP_K_PORT_LER			  	0x4032
#घोषणा PI_ITEM_K_PORT_LER_ESTIMATE		0x4033
#घोषणा PI_ITEM_K_PORT_LEM_REJ_CT		0x4034
#घोषणा PI_ITEM_K_PORT_LEM_CT			0x4035
#घोषणा PI_ITEM_K_PORT_LER_CUTOFF		0x403A
#घोषणा PI_ITEM_K_PORT_LER_ALARM		0x403B

#घोषणा PI_GRP_K_PORT_STATUS			0x403C
#घोषणा PI_ITEM_K_PORT_CONNECT_STATE	0x403D
#घोषणा PI_ITEM_K_PORT_PCM_STATE		0x403E
#घोषणा PI_ITEM_K_PORT_PC_WITHHOLD		0x403F
#घोषणा PI_ITEM_K_PORT_LER_FLAG			0x4040
#घोषणा PI_ITEM_K_PORT_HW_PRESENT		0x4041

#घोषणा PI_ITEM_K_PORT_ACT				0x4046

/* Addr_Filter_Set Request */

#घोषणा PI_CMD_ADDR_FILTER_K_SIZE   62

प्रकार काष्ठा
	अणु
	PI_UINT32	cmd_type;
	PI_LAN_ADDR	entry[PI_CMD_ADDR_FILTER_K_SIZE];
	पूर्ण PI_CMD_ADDR_FILTER_SET_REQ;

/* Addr_Filter_Set Response */

प्रकार काष्ठा
	अणु
	PI_RSP_HEADER   header;
	पूर्ण PI_CMD_ADDR_FILTER_SET_RSP;

/* Addr_Filter_Get Request */

प्रकार काष्ठा
	अणु
	PI_UINT32	cmd_type;
	पूर्ण PI_CMD_ADDR_FILTER_GET_REQ;

/* Addr_Filter_Get Response */

प्रकार काष्ठा
	अणु
	PI_RSP_HEADER   header;
	PI_LAN_ADDR		entry[PI_CMD_ADDR_FILTER_K_SIZE];
	पूर्ण PI_CMD_ADDR_FILTER_GET_RSP;

/* Status_Chars_Get Request */

प्रकार काष्ठा
	अणु
	PI_UINT32  cmd_type;
	पूर्ण PI_CMD_STATUS_CHARS_GET_REQ;

/* Status_Chars_Get Response */

प्रकार काष्ठा
	अणु
	PI_RSP_HEADER   header;
	PI_STATION_ID   station_id;						/* Station */
	PI_UINT32		station_type;
	PI_UINT32		smt_ver_id;
	PI_UINT32		smt_ver_id_max;
	PI_UINT32		smt_ver_id_min;
	PI_UINT32		station_state;
	PI_LAN_ADDR		link_addr;						/* Link */
	PI_UINT32		t_req;
	PI_UINT32		tvx;
	PI_UINT32		token_समयout;
	PI_UINT32		purger_enb;
	PI_UINT32		link_state;
	PI_UINT32		tneg;
	PI_UINT32		dup_addr_flag;
	PI_LAN_ADDR		una;
	PI_LAN_ADDR		una_old;
	PI_UINT32		un_dup_addr_flag;
	PI_LAN_ADDR		dna;
	PI_LAN_ADDR		dna_old;
	PI_UINT32		purger_state;
	PI_UINT32		fci_mode;
	PI_UINT32		error_reason;
	PI_UINT32		loopback;
	PI_UINT32		ring_latency;
	PI_LAN_ADDR		last_dir_beacon_sa;
	PI_LAN_ADDR		last_dir_beacon_una;
	PI_UINT32		phy_type[PI_PHY_K_MAX];			/* Phy */
	PI_UINT32		pmd_type[PI_PHY_K_MAX];
	PI_UINT32		lem_threshold[PI_PHY_K_MAX];
	PI_UINT32		phy_state[PI_PHY_K_MAX];
	PI_UINT32		nbor_phy_type[PI_PHY_K_MAX];
	PI_UINT32		link_error_est[PI_PHY_K_MAX];
	PI_UINT32		broken_reason[PI_PHY_K_MAX];
	PI_UINT32		reject_reason[PI_PHY_K_MAX];
	PI_UINT32		cntr_पूर्णांकerval;					/* Miscellaneous */
	PI_UINT32		module_rev;
	PI_UINT32		firmware_rev;
	PI_UINT32		mop_device_type;
	PI_UINT32		phy_led[PI_PHY_K_MAX];
	PI_UINT32		flush_समय;
	पूर्ण PI_CMD_STATUS_CHARS_GET_RSP;

/* FDDI_MIB_Get Request */

प्रकार काष्ठा
	अणु
	PI_UINT32  cmd_type;
	पूर्ण PI_CMD_FDDI_MIB_GET_REQ;

/* FDDI_MIB_Get Response */

प्रकार काष्ठा
	अणु
	PI_RSP_HEADER   header;

	/* SMT GROUP */

	PI_STATION_ID   smt_station_id;
	PI_UINT32		smt_op_version_id;
	PI_UINT32		smt_hi_version_id;
	PI_UINT32		smt_lo_version_id;
	PI_UINT32		smt_mac_ct;
	PI_UINT32		smt_non_master_ct;
	PI_UINT32		smt_master_ct;
	PI_UINT32		smt_paths_available;
	PI_UINT32		smt_config_capabilities;
	PI_UINT32		smt_config_policy;
	PI_UINT32		smt_connection_policy;
	PI_UINT32		smt_t_notअगरy;
	PI_UINT32		smt_status_reporting;
	PI_UINT32		smt_ecm_state;
	PI_UINT32		smt_cf_state;
	PI_UINT32		smt_hold_state;
	PI_UINT32		smt_remote_disconnect_flag;
	PI_UINT32		smt_station_action;

	/* MAC GROUP */

	PI_UINT32		mac_frame_status_capabilities;
	PI_UINT32		mac_t_max_greatest_lower_bound;
	PI_UINT32		mac_tvx_greatest_lower_bound;
	PI_UINT32		mac_paths_available;
	PI_UINT32		mac_current_path;
	PI_LAN_ADDR		mac_upstream_nbr;
	PI_LAN_ADDR		mac_old_upstream_nbr;
	PI_UINT32		mac_dup_addr_test;
	PI_UINT32		mac_paths_requested;
	PI_UINT32		mac_करोwnstream_port_type;
	PI_LAN_ADDR		mac_smt_address;
	PI_UINT32		mac_t_req;
	PI_UINT32		mac_t_neg;
	PI_UINT32		mac_t_max;
	PI_UINT32		mac_tvx_value;
	PI_UINT32		mac_t_min;
	PI_UINT32		mac_current_frame_status;
	/*			  	mac_frame_cts 			*/
	/* 				mac_error_cts 			*/
	/* 		   		mac_lost_cts 			*/
	PI_UINT32		mac_frame_error_threshold;
	PI_UINT32		mac_frame_error_ratio;
	PI_UINT32		mac_rmt_state;
	PI_UINT32		mac_da_flag;
	PI_UINT32		mac_una_da_flag;
	PI_UINT32		mac_frame_condition;
	PI_UINT32		mac_chip_set;
	PI_UINT32		mac_action;

	/* PATH GROUP => Does not need to be implemented */

	/* PORT GROUP */

	PI_UINT32		port_pc_type[PI_PHY_K_MAX];
	PI_UINT32		port_pc_neighbor[PI_PHY_K_MAX];
	PI_UINT32		port_connection_policies[PI_PHY_K_MAX];
	PI_UINT32		port_remote_mac_indicated[PI_PHY_K_MAX];
	PI_UINT32		port_ce_state[PI_PHY_K_MAX];
	PI_UINT32		port_paths_requested[PI_PHY_K_MAX];
	PI_UINT32		port_mac_placement[PI_PHY_K_MAX];
	PI_UINT32		port_available_paths[PI_PHY_K_MAX];
	PI_UINT32		port_mac_loop_समय[PI_PHY_K_MAX];
	PI_UINT32		port_tb_max[PI_PHY_K_MAX];
	PI_UINT32		port_bs_flag[PI_PHY_K_MAX];
	/*				port_lct_fail_cts[PI_PHY_K_MAX];	*/
	PI_UINT32		port_ler_estimate[PI_PHY_K_MAX];
	/*				port_lem_reject_cts[PI_PHY_K_MAX];	*/
	/*				port_lem_cts[PI_PHY_K_MAX];		*/
	PI_UINT32		port_ler_cutoff[PI_PHY_K_MAX];
	PI_UINT32		port_ler_alarm[PI_PHY_K_MAX];
	PI_UINT32		port_connect_state[PI_PHY_K_MAX];
	PI_UINT32		port_pcm_state[PI_PHY_K_MAX];
	PI_UINT32		port_pc_withhold[PI_PHY_K_MAX];
	PI_UINT32		port_ler_condition[PI_PHY_K_MAX];
	PI_UINT32		port_chip_set[PI_PHY_K_MAX];
	PI_UINT32		port_action[PI_PHY_K_MAX];

	/* ATTACHMENT GROUP */

	PI_UINT32		attachment_class;
	PI_UINT32		attachment_ob_present;
	PI_UINT32		attachment_imax_expiration;
	PI_UINT32		attachment_inserted_status;
	PI_UINT32		attachment_insert_policy;

	/* CHIP SET GROUP => Does not need to be implemented */

	पूर्ण PI_CMD_FDDI_MIB_GET_RSP;

/* DEC_Ext_MIB_Get Request */

प्रकार काष्ठा
	अणु
	PI_UINT32  cmd_type;
	पूर्ण PI_CMD_DEC_EXT_MIB_GET_REQ;

/* DEC_Ext_MIB_Get (efddi and efdx groups only) Response */

प्रकार काष्ठा
	अणु
	PI_RSP_HEADER   header;

	/* SMT GROUP */

	PI_UINT32		esmt_station_type;

	/* MAC GROUP */

	PI_UINT32		emac_link_state;
	PI_UINT32		emac_ring_purger_state;
	PI_UINT32		emac_ring_purger_enable;
	PI_UINT32		emac_frame_strip_mode;
	PI_UINT32		emac_ring_error_reason;
	PI_UINT32		emac_up_nbr_dup_addr_flag;
	PI_UINT32		emac_restricted_token_समयout;

	/* PORT GROUP */

	PI_UINT32		eport_pmd_type[PI_PHY_K_MAX];
	PI_UINT32		eport_phy_state[PI_PHY_K_MAX];
	PI_UINT32		eport_reject_reason[PI_PHY_K_MAX];

	/* FDX (Full-Duplex) GROUP */

	PI_UINT32		efdx_enable;				/* Valid only in SMT 7.3 */
	PI_UINT32		efdx_op;					/* Valid only in SMT 7.3 */
	PI_UINT32		efdx_state;					/* Valid only in SMT 7.3 */

	पूर्ण PI_CMD_DEC_EXT_MIB_GET_RSP;

प्रकार काष्ठा
	अणु
	PI_CNTR		traces_rcvd;					/* Station */
	PI_CNTR		frame_cnt;						/* Link */
	PI_CNTR		error_cnt;
	PI_CNTR		lost_cnt;
	PI_CNTR		octets_rcvd;
	PI_CNTR		octets_sent;
	PI_CNTR		pdus_rcvd;
	PI_CNTR		pdus_sent;
	PI_CNTR		mcast_octets_rcvd;
	PI_CNTR		mcast_octets_sent;
	PI_CNTR		mcast_pdus_rcvd;
	PI_CNTR		mcast_pdus_sent;
	PI_CNTR		xmt_underruns;
	PI_CNTR		xmt_failures;
	PI_CNTR		block_check_errors;
	PI_CNTR		frame_status_errors;
	PI_CNTR		pdu_length_errors;
	PI_CNTR		rcv_overruns;
	PI_CNTR		user_buff_unavailable;
	PI_CNTR		inits_initiated;
	PI_CNTR		inits_rcvd;
	PI_CNTR		beacons_initiated;
	PI_CNTR		dup_addrs;
	PI_CNTR		dup_tokens;
	PI_CNTR		purge_errors;
	PI_CNTR		fci_strip_errors;
	PI_CNTR		traces_initiated;
	PI_CNTR		directed_beacons_rcvd;
	PI_CNTR		emac_frame_alignment_errors;
	PI_CNTR		ebuff_errors[PI_PHY_K_MAX];		/* Phy */
	PI_CNTR		lct_rejects[PI_PHY_K_MAX];
	PI_CNTR		lem_rejects[PI_PHY_K_MAX];
	PI_CNTR		link_errors[PI_PHY_K_MAX];
	PI_CNTR		connections[PI_PHY_K_MAX];
	PI_CNTR		copied_cnt;			 			/* Valid only अगर using SMT 7.3 */
	PI_CNTR		transmit_cnt;					/* Valid only अगर using SMT 7.3 */
	PI_CNTR		tokens;
	पूर्ण PI_CNTR_BLK;

/* Counters_Get Request */

प्रकार काष्ठा
	अणु
	PI_UINT32  cmd_type;
	पूर्ण PI_CMD_CNTRS_GET_REQ;

/* Counters_Get Response */

प्रकार काष्ठा
	अणु
	PI_RSP_HEADER   header;
	PI_CNTR		समय_since_reset;
	PI_CNTR_BLK		cntrs;
	पूर्ण PI_CMD_CNTRS_GET_RSP;

/* Counters_Set Request */

प्रकार काष्ठा
	अणु
	PI_UINT32	cmd_type;
	PI_CNTR_BLK	cntrs;
	पूर्ण PI_CMD_CNTRS_SET_REQ;

/* Counters_Set Response */

प्रकार काष्ठा
	अणु
	PI_RSP_HEADER   header;
	पूर्ण PI_CMD_CNTRS_SET_RSP;

/* Error_Log_Clear Request */

प्रकार काष्ठा
	अणु
	PI_UINT32  cmd_type;
	पूर्ण PI_CMD_ERROR_LOG_CLEAR_REQ;

/* Error_Log_Clear Response */

प्रकार काष्ठा
	अणु
	PI_RSP_HEADER   header;
	पूर्ण PI_CMD_ERROR_LOG_CLEAR_RSP;

/* Error_Log_Get Request */

#घोषणा PI_LOG_ENTRY_K_INDEX_MIN	0		/* Minimum index क्रम entry */

प्रकार काष्ठा
	अणु
	PI_UINT32  cmd_type;
	PI_UINT32  entry_index;
	पूर्ण PI_CMD_ERROR_LOG_GET_REQ;

/* Error_Log_Get Response */

#घोषणा PI_K_LOG_FW_SIZE			111		/* Max number of fw दीर्घwords */
#घोषणा PI_K_LOG_DIAG_SIZE	 		6		/* Max number of diag दीर्घwords */

प्रकार काष्ठा
	अणु
	काष्ठा
		अणु
		PI_UINT32	fru_imp_mask;
		PI_UINT32	test_id;
		PI_UINT32	reserved[PI_K_LOG_DIAG_SIZE];
		पूर्ण diag;
	PI_UINT32		fw[PI_K_LOG_FW_SIZE];
	पूर्ण PI_LOG_ENTRY;

प्रकार काष्ठा
	अणु
	PI_RSP_HEADER   header;
	PI_UINT32		event_status;
	PI_UINT32		caller_id;
	PI_UINT32		बारtamp_l;
	PI_UINT32		बारtamp_h;
	PI_UINT32		ग_लिखो_count;
	PI_LOG_ENTRY	entry_info;
	पूर्ण PI_CMD_ERROR_LOG_GET_RSP;

/* Define error log related स्थिरants and types.					*/
/*   Not all of the caller id's can occur.  The only ones currently */
/*   implemented are: none, selftest, mfg, fw, console				*/

#घोषणा PI_LOG_EVENT_STATUS_K_VALID		0	/* Valid Event Status 		*/
#घोषणा PI_LOG_EVENT_STATUS_K_INVALID	1	/* Invalid Event Status 	*/
#घोषणा PI_LOG_CALLER_ID_K_NONE		 	0	/* No caller 				*/
#घोषणा PI_LOG_CALLER_ID_K_SELFTEST	 	1	/* Normal घातer-up selftest */
#घोषणा PI_LOG_CALLER_ID_K_MFG		 	2	/* Mfg घातer-up selftest 	*/
#घोषणा PI_LOG_CALLER_ID_K_ONLINE		3	/* On-line diagnostics 		*/
#घोषणा PI_LOG_CALLER_ID_K_HW			4	/* Hardware 				*/
#घोषणा PI_LOG_CALLER_ID_K_FW			5	/* Firmware 				*/
#घोषणा PI_LOG_CALLER_ID_K_CNS_HW		6	/* CNS firmware 			*/
#घोषणा PI_LOG_CALLER_ID_K_CNS_FW		7	/* CNS hardware 			*/
#घोषणा PI_LOG_CALLER_ID_K_CONSOLE	 	8   /* Console Caller Id 		*/

/*
 *  Place all DMA commands in the following request and response काष्ठाures
 *  to simplअगरy code.
 */

प्रकार जोड़
	अणु
	PI_UINT32					cmd_type;
	PI_CMD_START_REQ			start;
	PI_CMD_FILTERS_SET_REQ		filter_set;
	PI_CMD_FILTERS_GET_REQ		filter_get;
	PI_CMD_CHARS_SET_REQ		अक्षर_set;
	PI_CMD_ADDR_FILTER_SET_REQ	addr_filter_set;
	PI_CMD_ADDR_FILTER_GET_REQ	addr_filter_get;
	PI_CMD_STATUS_CHARS_GET_REQ	stat_अक्षर_get;
	PI_CMD_CNTRS_GET_REQ		cntrs_get;
	PI_CMD_CNTRS_SET_REQ		cntrs_set;
	PI_CMD_ERROR_LOG_CLEAR_REQ	error_log_clear;
	PI_CMD_ERROR_LOG_GET_REQ	error_log_पढ़ो;
	PI_CMD_SNMP_SET_REQ			snmp_set;
	PI_CMD_FDDI_MIB_GET_REQ		fddi_mib_get;
	PI_CMD_DEC_EXT_MIB_GET_REQ	dec_mib_get;
	PI_CMD_SMT_MIB_SET_REQ		smt_mib_set;
	PI_CMD_SMT_MIB_GET_REQ		smt_mib_get;
	अक्षर						pad[PI_CMD_REQ_K_SIZE_MAX];
	पूर्ण PI_DMA_CMD_REQ;

प्रकार जोड़
	अणु
	PI_RSP_HEADER				header;
	PI_CMD_START_RSP			start;
	PI_CMD_FILTERS_SET_RSP		filter_set;
	PI_CMD_FILTERS_GET_RSP		filter_get;
	PI_CMD_CHARS_SET_RSP		अक्षर_set;
	PI_CMD_ADDR_FILTER_SET_RSP	addr_filter_set;
	PI_CMD_ADDR_FILTER_GET_RSP	addr_filter_get;
	PI_CMD_STATUS_CHARS_GET_RSP	stat_अक्षर_get;
	PI_CMD_CNTRS_GET_RSP		cntrs_get;
	PI_CMD_CNTRS_SET_RSP		cntrs_set;
	PI_CMD_ERROR_LOG_CLEAR_RSP	error_log_clear;
	PI_CMD_ERROR_LOG_GET_RSP	error_log_get;
	PI_CMD_SNMP_SET_RSP			snmp_set;
	PI_CMD_FDDI_MIB_GET_RSP		fddi_mib_get;
	PI_CMD_DEC_EXT_MIB_GET_RSP	dec_mib_get;
	PI_CMD_SMT_MIB_SET_RSP		smt_mib_set;
	PI_CMD_SMT_MIB_GET_RSP		smt_mib_get;
	अक्षर						pad[PI_CMD_RSP_K_SIZE_MAX];
	पूर्ण PI_DMA_CMD_RSP;

प्रकार जोड़
	अणु
	PI_DMA_CMD_REQ	request;
	PI_DMA_CMD_RSP	response;
	पूर्ण PI_DMA_CMD_BUFFER;


/* Define क्रमmat of Consumer Block (resident in host memory) */

प्रकार काष्ठा
	अणु
	अस्थिर PI_UINT32	xmt_rcv_data;
	अस्थिर PI_UINT32	reserved_1;
	अस्थिर PI_UINT32	smt_host;
	अस्थिर PI_UINT32	reserved_2;
	अस्थिर PI_UINT32	unsol;
	अस्थिर PI_UINT32	reserved_3;
	अस्थिर PI_UINT32	cmd_rsp;
	अस्थिर PI_UINT32	reserved_4;
	अस्थिर PI_UINT32	cmd_req;
	अस्थिर PI_UINT32	reserved_5;
	पूर्ण PI_CONSUMER_BLOCK;

#घोषणा PI_CONS_M_RCV_INDEX			0x000000FF
#घोषणा PI_CONS_M_XMT_INDEX			0x00FF0000
#घोषणा PI_CONS_V_RCV_INDEX			0
#घोषणा PI_CONS_V_XMT_INDEX			16

/* Offsets पूर्णांकo consumer block */

#घोषणा PI_CONS_BLK_K_XMT_RCV		0x00
#घोषणा PI_CONS_BLK_K_SMT_HOST		0x08
#घोषणा PI_CONS_BLK_K_UNSOL			0x10
#घोषणा PI_CONS_BLK_K_CMD_RSP		0x18
#घोषणा PI_CONS_BLK_K_CMD_REQ		0x20

/* Offsets पूर्णांकo descriptor block */

#घोषणा PI_DESCR_BLK_K_RCV_DATA		0x0000
#घोषणा PI_DESCR_BLK_K_XMT_DATA		0x0800
#घोषणा PI_DESCR_BLK_K_SMT_HOST 	0x1000
#घोषणा PI_DESCR_BLK_K_UNSOL		0x1200
#घोषणा PI_DESCR_BLK_K_CMD_RSP		0x1280
#घोषणा PI_DESCR_BLK_K_CMD_REQ		0x1300

/* Define क्रमmat of a rcv descr (Rcv Data, Cmd Rsp, Unsolicited, SMT Host)   */
/*   Note a field has been added क्रम later versions of the PDQ to allow क्रम  */
/*   finer granularity of the rcv buffer alignment.  For backwards		 	 */
/*   compatibility, the two bits (which allow the rcv buffer to be दीर्घword  */
/*   aligned) have been added at the MBZ bits.  To support previous drivers, */
/*   the MBZ definition is left पूर्णांकact.									  	 */

प्रकार काष्ठा
	अणु
	PI_UINT32	दीर्घ_0;
	PI_UINT32	दीर्घ_1;
	पूर्ण PI_RCV_DESCR;

#घोषणा	PI_RCV_DESCR_M_SOP	  		0x80000000
#घोषणा PI_RCV_DESCR_M_SEG_LEN_LO 	0x60000000
#घोषणा PI_RCV_DESCR_M_MBZ	  		0x60000000
#घोषणा PI_RCV_DESCR_M_SEG_LEN		0x1F800000
#घोषणा PI_RCV_DESCR_M_SEG_LEN_HI	0x1FF00000
#घोषणा PI_RCV_DESCR_M_SEG_CNT	  	0x000F0000
#घोषणा PI_RCV_DESCR_M_BUFF_HI	  	0x0000FFFF

#घोषणा	PI_RCV_DESCR_V_SOP	  		31
#घोषणा PI_RCV_DESCR_V_SEG_LEN_LO 	29
#घोषणा PI_RCV_DESCR_V_MBZ	  		29
#घोषणा PI_RCV_DESCR_V_SEG_LEN	  	23
#घोषणा PI_RCV_DESCR_V_SEG_LEN_HI 	20
#घोषणा PI_RCV_DESCR_V_SEG_CNT	  	16
#घोषणा PI_RCV_DESCR_V_BUFF_HI	 	0

/* Define the क्रमmat of a transmit descriptor (Xmt Data, Cmd Req) */

प्रकार काष्ठा
	अणु
	PI_UINT32	दीर्घ_0;
	PI_UINT32	दीर्घ_1;
	पूर्ण PI_XMT_DESCR;

#घोषणा	PI_XMT_DESCR_M_SOP			0x80000000
#घोषणा PI_XMT_DESCR_M_EOP			0x40000000
#घोषणा PI_XMT_DESCR_M_MBZ			0x20000000
#घोषणा PI_XMT_DESCR_M_SEG_LEN		0x1FFF0000
#घोषणा PI_XMT_DESCR_M_BUFF_HI		0x0000FFFF

#घोषणा	PI_XMT_DESCR_V_SOP			31
#घोषणा	PI_XMT_DESCR_V_EOP			30
#घोषणा PI_XMT_DESCR_V_MBZ			29
#घोषणा PI_XMT_DESCR_V_SEG_LEN		16
#घोषणा PI_XMT_DESCR_V_BUFF_HI		0

/* Define क्रमmat of the Descriptor Block (resident in host memory) */

#घोषणा PI_RCV_DATA_K_NUM_ENTRIES			256
#घोषणा PI_XMT_DATA_K_NUM_ENTRIES			256
#घोषणा PI_SMT_HOST_K_NUM_ENTRIES			64
#घोषणा PI_UNSOL_K_NUM_ENTRIES				16
#घोषणा PI_CMD_RSP_K_NUM_ENTRIES			16
#घोषणा PI_CMD_REQ_K_NUM_ENTRIES			16

प्रकार काष्ठा
	अणु
	PI_RCV_DESCR  rcv_data[PI_RCV_DATA_K_NUM_ENTRIES];
	PI_XMT_DESCR  xmt_data[PI_XMT_DATA_K_NUM_ENTRIES];
	PI_RCV_DESCR  smt_host[PI_SMT_HOST_K_NUM_ENTRIES];
	PI_RCV_DESCR  unsol[PI_UNSOL_K_NUM_ENTRIES];
	PI_RCV_DESCR  cmd_rsp[PI_CMD_RSP_K_NUM_ENTRIES];
	PI_XMT_DESCR  cmd_req[PI_CMD_REQ_K_NUM_ENTRIES];
	पूर्ण PI_DESCR_BLOCK;

/* Define Port Registers - offsets from PDQ Base address */

#घोषणा PI_PDQ_K_REG_PORT_RESET			0x00000000
#घोषणा PI_PDQ_K_REG_HOST_DATA			0x00000004
#घोषणा PI_PDQ_K_REG_PORT_CTRL			0x00000008
#घोषणा PI_PDQ_K_REG_PORT_DATA_A		0x0000000C
#घोषणा PI_PDQ_K_REG_PORT_DATA_B		0x00000010
#घोषणा PI_PDQ_K_REG_PORT_STATUS		0x00000014
#घोषणा PI_PDQ_K_REG_TYPE_0_STATUS 		0x00000018
#घोषणा PI_PDQ_K_REG_HOST_INT_ENB	  	0x0000001C
#घोषणा PI_PDQ_K_REG_TYPE_2_PROD_NOINT 	0x00000020
#घोषणा PI_PDQ_K_REG_TYPE_2_PROD		0x00000024
#घोषणा PI_PDQ_K_REG_CMD_RSP_PROD		0x00000028
#घोषणा PI_PDQ_K_REG_CMD_REQ_PROD		0x0000002C
#घोषणा PI_PDQ_K_REG_SMT_HOST_PROD   	0x00000030
#घोषणा PI_PDQ_K_REG_UNSOL_PROD			0x00000034

/* Port Control Register - Command codes क्रम primary commands */

#घोषणा PI_PCTRL_M_CMD_ERROR			0x8000
#घोषणा PI_PCTRL_M_BLAST_FLASH			0x4000
#घोषणा PI_PCTRL_M_HALT					0x2000
#घोषणा PI_PCTRL_M_COPY_DATA			0x1000
#घोषणा PI_PCTRL_M_ERROR_LOG_START		0x0800
#घोषणा PI_PCTRL_M_ERROR_LOG_READ		0x0400
#घोषणा PI_PCTRL_M_XMT_DATA_FLUSH_DONE	0x0200
#घोषणा PI_PCTRL_M_INIT					0x0100
#घोषणा PI_PCTRL_M_INIT_START		    0x0080
#घोषणा PI_PCTRL_M_CONS_BLOCK			0x0040
#घोषणा PI_PCTRL_M_UNINIT				0x0020
#घोषणा PI_PCTRL_M_RING_MEMBER			0x0010
#घोषणा PI_PCTRL_M_MLA					0x0008
#घोषणा PI_PCTRL_M_FW_REV_READ			0x0004
#घोषणा PI_PCTRL_M_DEV_SPECIFIC			0x0002
#घोषणा PI_PCTRL_M_SUB_CMD				0x0001

/* Define sub-commands accessed via the PI_PCTRL_M_SUB_CMD command */

#घोषणा PI_SUB_CMD_K_LINK_UNINIT		0x0001
#घोषणा PI_SUB_CMD_K_BURST_SIZE_SET		0x0002
#घोषणा PI_SUB_CMD_K_PDQ_REV_GET		0x0004
#घोषणा PI_SUB_CMD_K_HW_REV_GET			0x0008

/* Define some Port Data B values */

#घोषणा PI_PDATA_B_DMA_BURST_SIZE_4	 	0		/* valid values क्रम command */
#घोषणा PI_PDATA_B_DMA_BURST_SIZE_8	 	1
#घोषणा PI_PDATA_B_DMA_BURST_SIZE_16	2
#घोषणा PI_PDATA_B_DMA_BURST_SIZE_32	3		/* not supported on PCI */
#घोषणा PI_PDATA_B_DMA_BURST_SIZE_DEF	PI_PDATA_B_DMA_BURST_SIZE_16

/* Port Data A Reset state */

#घोषणा PI_PDATA_A_RESET_M_UPGRADE		0x00000001
#घोषणा PI_PDATA_A_RESET_M_SOFT_RESET	0x00000002
#घोषणा PI_PDATA_A_RESET_M_SKIP_ST		0x00000004

/* Read adapter MLA address port control command स्थिरants */

#घोषणा PI_PDATA_A_MLA_K_LO				0
#घोषणा PI_PDATA_A_MLA_K_HI				1

/* Byte Swap values क्रम init command */

#घोषणा PI_PDATA_A_INIT_M_DESC_BLK_ADDR			0x0FFFFE000
#घोषणा PI_PDATA_A_INIT_M_RESERVED				0x000001FFC
#घोषणा PI_PDATA_A_INIT_M_BSWAP_DATA			0x000000002
#घोषणा PI_PDATA_A_INIT_M_BSWAP_LITERAL			0x000000001

#घोषणा PI_PDATA_A_INIT_V_DESC_BLK_ADDR			13
#घोषणा PI_PDATA_A_INIT_V_RESERVED				3
#घोषणा PI_PDATA_A_INIT_V_BSWAP_DATA			1
#घोषणा PI_PDATA_A_INIT_V_BSWAP_LITERAL			0

/* Port Reset Register */

#घोषणा PI_RESET_M_ASSERT_RESET			1

/* Port Status रेजिस्टर */

#घोषणा PI_PSTATUS_V_RCV_DATA_PENDING	31
#घोषणा PI_PSTATUS_V_XMT_DATA_PENDING	30
#घोषणा PI_PSTATUS_V_SMT_HOST_PENDING	29
#घोषणा PI_PSTATUS_V_UNSOL_PENDING		28
#घोषणा PI_PSTATUS_V_CMD_RSP_PENDING	27
#घोषणा PI_PSTATUS_V_CMD_REQ_PENDING	26
#घोषणा PI_PSTATUS_V_TYPE_0_PENDING		25
#घोषणा PI_PSTATUS_V_RESERVED_1			16
#घोषणा PI_PSTATUS_V_RESERVED_2			11
#घोषणा PI_PSTATUS_V_STATE				8
#घोषणा PI_PSTATUS_V_HALT_ID			0

#घोषणा PI_PSTATUS_M_RCV_DATA_PENDING	0x80000000
#घोषणा PI_PSTATUS_M_XMT_DATA_PENDING	0x40000000
#घोषणा PI_PSTATUS_M_SMT_HOST_PENDING	0x20000000
#घोषणा PI_PSTATUS_M_UNSOL_PENDING		0x10000000
#घोषणा PI_PSTATUS_M_CMD_RSP_PENDING	0x08000000
#घोषणा PI_PSTATUS_M_CMD_REQ_PENDING	0x04000000
#घोषणा PI_PSTATUS_M_TYPE_0_PENDING		0x02000000
#घोषणा PI_PSTATUS_M_RESERVED_1			0x01FF0000
#घोषणा PI_PSTATUS_M_RESERVED_2			0x0000F800
#घोषणा PI_PSTATUS_M_STATE				0x00000700
#घोषणा PI_PSTATUS_M_HALT_ID			0x000000FF

/* Define Halt Id's			 					*/
/*   Do not insert पूर्णांकo this list, only append. */

#घोषणा PI_HALT_ID_K_SELFTEST_TIMEOUT	0
#घोषणा PI_HALT_ID_K_PARITY_ERROR		1
#घोषणा PI_HALT_ID_K_HOST_सूची_HALT		2
#घोषणा PI_HALT_ID_K_SW_FAULT			3
#घोषणा PI_HALT_ID_K_HW_FAULT			4
#घोषणा PI_HALT_ID_K_PC_TRACE			5
#घोषणा PI_HALT_ID_K_DMA_ERROR			6			/* Host Data has error reg */
#घोषणा PI_HALT_ID_K_IMAGE_CRC_ERROR	7   		/* Image is bad, update it */
#घोषणा PI_HALT_ID_K_BUS_EXCEPTION	 	8   		/* 68K bus exception	   */

/* Host Interrupt Enable Register as seen by host */

#घोषणा PI_HOST_INT_M_XMT_DATA_ENB		0x80000000	/* Type 2 Enables */
#घोषणा PI_HOST_INT_M_RCV_DATA_ENB		0x40000000
#घोषणा PI_HOST_INT_M_SMT_HOST_ENB		0x10000000	/* Type 1 Enables */
#घोषणा PI_HOST_INT_M_UNSOL_ENB			0x20000000
#घोषणा PI_HOST_INT_M_CMD_RSP_ENB		0x08000000
#घोषणा PI_HOST_INT_M_CMD_REQ_ENB		0x04000000
#घोषणा	PI_HOST_INT_M_TYPE_1_RESERVED	0x00FF0000
#घोषणा	PI_HOST_INT_M_TYPE_0_RESERVED	0x0000FF00	/* Type 0 Enables */
#घोषणा PI_HOST_INT_M_1MS				0x00000080
#घोषणा PI_HOST_INT_M_20MS				0x00000040
#घोषणा PI_HOST_INT_M_CSR_CMD_DONE		0x00000020
#घोषणा PI_HOST_INT_M_STATE_CHANGE		0x00000010
#घोषणा PI_HOST_INT_M_XMT_FLUSH			0x00000008
#घोषणा PI_HOST_INT_M_NXM				0x00000004
#घोषणा PI_HOST_INT_M_PM_PAR_ERR		0x00000002
#घोषणा PI_HOST_INT_M_BUS_PAR_ERR		0x00000001

#घोषणा PI_HOST_INT_V_XMT_DATA_ENB		31			/* Type 2 Enables */
#घोषणा PI_HOST_INT_V_RCV_DATA_ENB		30
#घोषणा PI_HOST_INT_V_SMT_HOST_ENB		29			/* Type 1 Enables */
#घोषणा PI_HOST_INT_V_UNSOL_ENB			28
#घोषणा PI_HOST_INT_V_CMD_RSP_ENB		27
#घोषणा PI_HOST_INT_V_CMD_REQ_ENB		26
#घोषणा	PI_HOST_INT_V_TYPE_1_RESERVED	16
#घोषणा	PI_HOST_INT_V_TYPE_0_RESERVED   8			/* Type 0 Enables */
#घोषणा PI_HOST_INT_V_1MS_ENB			7
#घोषणा PI_HOST_INT_V_20MS_ENB			6
#घोषणा PI_HOST_INT_V_CSR_CMD_DONE_ENB	5
#घोषणा PI_HOST_INT_V_STATE_CHANGE_ENB	4
#घोषणा PI_HOST_INT_V_XMT_FLUSH_ENB 	3
#घोषणा PI_HOST_INT_V_NXM_ENB			2
#घोषणा PI_HOST_INT_V_PM_PAR_ERR_ENB	1
#घोषणा PI_HOST_INT_V_BUS_PAR_ERR_ENB	0

#घोषणा PI_HOST_INT_K_ACK_ALL_TYPE_0	0x000000FF
#घोषणा PI_HOST_INT_K_DISABLE_ALL_INTS	0x00000000
#घोषणा PI_HOST_INT_K_ENABLE_ALL_INTS	0xFFFFFFFF
#घोषणा PI_HOST_INT_K_ENABLE_DEF_INTS	0xC000001F

/* Type 0 Interrupt Status Register */

#घोषणा PI_TYPE_0_STAT_M_1MS			0x00000080
#घोषणा PI_TYPE_0_STAT_M_20MS			0x00000040
#घोषणा PI_TYPE_0_STAT_M_CSR_CMD_DONE	0x00000020
#घोषणा PI_TYPE_0_STAT_M_STATE_CHANGE	0x00000010
#घोषणा PI_TYPE_0_STAT_M_XMT_FLUSH		0x00000008
#घोषणा PI_TYPE_0_STAT_M_NXM			0x00000004
#घोषणा PI_TYPE_0_STAT_M_PM_PAR_ERR		0x00000002
#घोषणा PI_TYPE_0_STAT_M_BUS_PAR_ERR	0x00000001

#घोषणा PI_TYPE_0_STAT_V_1MS			7
#घोषणा PI_TYPE_0_STAT_V_20MS			6
#घोषणा PI_TYPE_0_STAT_V_CSR_CMD_DONE	5
#घोषणा PI_TYPE_0_STAT_V_STATE_CHANGE	4
#घोषणा PI_TYPE_0_STAT_V_XMT_FLUSH		3
#घोषणा PI_TYPE_0_STAT_V_NXM			2
#घोषणा PI_TYPE_0_STAT_V_PM_PAR_ERR		1
#घोषणा PI_TYPE_0_STAT_V_BUS_PAR_ERR	0

/* Register definition काष्ठाures are defined क्रम both big and little endian प्रणालीs */

#अगर_अघोषित __BIG_ENDIAN

/* Little endian क्रमmat of Type 1 Producer रेजिस्टर */

प्रकार जोड़
	अणु
	PI_UINT32	lword;
	काष्ठा
		अणु
		PI_UINT8	prod;
		PI_UINT8	comp;
		PI_UINT8	mbz_1;
		PI_UINT8	mbz_2;
		पूर्ण index;
	पूर्ण PI_TYPE_1_PROD_REG;

/* Little endian क्रमmat of Type 2 Producer रेजिस्टर */

प्रकार जोड़
	अणु
	PI_UINT32	lword;
	काष्ठा
		अणु
		PI_UINT8	rcv_prod;
		PI_UINT8	xmt_prod;
		PI_UINT8	rcv_comp;
		PI_UINT8	xmt_comp;
		पूर्ण index;
	पूर्ण PI_TYPE_2_PROD_REG;

/* Little endian क्रमmat of Type 1 Consumer Block दीर्घword */

प्रकार जोड़
	अणु
	PI_UINT32	lword;
	काष्ठा
		अणु
		PI_UINT8	cons;
		PI_UINT8	res0;
		PI_UINT8	res1;
		PI_UINT8	res2;
		पूर्ण index;
	पूर्ण PI_TYPE_1_CONSUMER;

/* Little endian क्रमmat of Type 2 Consumer Block दीर्घword */

प्रकार जोड़
	अणु
	PI_UINT32	lword;
	काष्ठा
		अणु
		PI_UINT8	rcv_cons;
		PI_UINT8	res0;
		PI_UINT8	xmt_cons;
		PI_UINT8	res1;
		पूर्ण index;
	पूर्ण PI_TYPE_2_CONSUMER;

/* Define swapping required by DMA transfers.  */
#घोषणा PI_PDATA_A_INIT_M_BSWAP_INIT	\
	(PI_PDATA_A_INIT_M_BSWAP_DATA)

#अन्यथा /* __BIG_ENDIAN */

/* Big endian क्रमmat of Type 1 Producer रेजिस्टर */

प्रकार जोड़
	अणु
	PI_UINT32	lword;
	काष्ठा
		अणु
		PI_UINT8	mbz_2;
		PI_UINT8	mbz_1;
		PI_UINT8	comp;
		PI_UINT8	prod;
		पूर्ण index;
	पूर्ण PI_TYPE_1_PROD_REG;

/* Big endian क्रमmat of Type 2 Producer रेजिस्टर */

प्रकार जोड़
	अणु
	PI_UINT32	lword;
	काष्ठा
		अणु
		PI_UINT8	xmt_comp;
		PI_UINT8	rcv_comp;
		PI_UINT8	xmt_prod;
		PI_UINT8	rcv_prod;
		पूर्ण index;
	पूर्ण PI_TYPE_2_PROD_REG;

/* Big endian क्रमmat of Type 1 Consumer Block दीर्घword */

प्रकार जोड़
	अणु
	PI_UINT32	lword;
	काष्ठा
		अणु
		PI_UINT8	res2;
		PI_UINT8	res1;
		PI_UINT8	res0;
		PI_UINT8	cons;
		पूर्ण index;
	पूर्ण PI_TYPE_1_CONSUMER;

/* Big endian क्रमmat of Type 2 Consumer Block दीर्घword */

प्रकार जोड़
	अणु
	PI_UINT32	lword;
	काष्ठा
		अणु
		PI_UINT8	res1;
		PI_UINT8	xmt_cons;
		PI_UINT8	res0;
		PI_UINT8	rcv_cons;
		पूर्ण index;
	पूर्ण PI_TYPE_2_CONSUMER;

/* Define swapping required by DMA transfers.  */
#घोषणा PI_PDATA_A_INIT_M_BSWAP_INIT	\
	(PI_PDATA_A_INIT_M_BSWAP_DATA | PI_PDATA_A_INIT_M_BSWAP_LITERAL)

#पूर्ण_अगर /* __BIG_ENDIAN */

/* Define TC PDQ CSR offset and length */

#घोषणा PI_TC_K_CSR_OFFSET		0x100000
#घोषणा PI_TC_K_CSR_LEN			0x40		/* 64 bytes */

/* Define EISA controller रेजिस्टर offsets */

#घोषणा PI_ESIC_K_CSR_IO_LEN		0x40		/* 64 bytes */
#घोषणा PI_ESIC_K_BURST_HOLDOFF_LEN	0x04		/* 4 bytes */
#घोषणा PI_ESIC_K_ESIC_CSR_LEN		0x40		/* 64 bytes */

#घोषणा PI_DEFEA_K_CSR_IO		0x000
#घोषणा PI_DEFEA_K_BURST_HOLDOFF	0x040
#घोषणा PI_ESIC_K_ESIC_CSR		0xC80

#घोषणा PI_ESIC_K_SLOT_ID            	0xC80
#घोषणा PI_ESIC_K_SLOT_CNTRL		0xC84
#घोषणा PI_ESIC_K_MEM_ADD_CMP_0     	0xC85
#घोषणा PI_ESIC_K_MEM_ADD_CMP_1     	0xC86
#घोषणा PI_ESIC_K_MEM_ADD_CMP_2     	0xC87
#घोषणा PI_ESIC_K_MEM_ADD_HI_CMP_0  	0xC88
#घोषणा PI_ESIC_K_MEM_ADD_HI_CMP_1  	0xC89
#घोषणा PI_ESIC_K_MEM_ADD_HI_CMP_2  	0xC8A
#घोषणा PI_ESIC_K_MEM_ADD_MASK_0     	0xC8B
#घोषणा PI_ESIC_K_MEM_ADD_MASK_1     	0xC8C
#घोषणा PI_ESIC_K_MEM_ADD_MASK_2     	0xC8D
#घोषणा PI_ESIC_K_MEM_ADD_LO_CMP_0  	0xC8E
#घोषणा PI_ESIC_K_MEM_ADD_LO_CMP_1  	0xC8F
#घोषणा PI_ESIC_K_MEM_ADD_LO_CMP_2  	0xC90
#घोषणा PI_ESIC_K_IO_ADD_CMP_0_0	0xC91
#घोषणा PI_ESIC_K_IO_ADD_CMP_0_1	0xC92
#घोषणा PI_ESIC_K_IO_ADD_CMP_1_0	0xC93
#घोषणा PI_ESIC_K_IO_ADD_CMP_1_1	0xC94
#घोषणा PI_ESIC_K_IO_ADD_CMP_2_0	0xC95
#घोषणा PI_ESIC_K_IO_ADD_CMP_2_1	0xC96
#घोषणा PI_ESIC_K_IO_ADD_CMP_3_0	0xC97
#घोषणा PI_ESIC_K_IO_ADD_CMP_3_1	0xC98
#घोषणा PI_ESIC_K_IO_ADD_MASK_0_0    	0xC99
#घोषणा PI_ESIC_K_IO_ADD_MASK_0_1    	0xC9A
#घोषणा PI_ESIC_K_IO_ADD_MASK_1_0    	0xC9B
#घोषणा PI_ESIC_K_IO_ADD_MASK_1_1    	0xC9C
#घोषणा PI_ESIC_K_IO_ADD_MASK_2_0    	0xC9D
#घोषणा PI_ESIC_K_IO_ADD_MASK_2_1    	0xC9E
#घोषणा PI_ESIC_K_IO_ADD_MASK_3_0    	0xC9F
#घोषणा PI_ESIC_K_IO_ADD_MASK_3_1    	0xCA0
#घोषणा PI_ESIC_K_MOD_CONFIG_1		0xCA1
#घोषणा PI_ESIC_K_MOD_CONFIG_2		0xCA2
#घोषणा PI_ESIC_K_MOD_CONFIG_3		0xCA3
#घोषणा PI_ESIC_K_MOD_CONFIG_4		0xCA4
#घोषणा PI_ESIC_K_MOD_CONFIG_5    	0xCA5
#घोषणा PI_ESIC_K_MOD_CONFIG_6		0xCA6
#घोषणा PI_ESIC_K_MOD_CONFIG_7		0xCA7
#घोषणा PI_ESIC_K_DIP_SWITCH         	0xCA8
#घोषणा PI_ESIC_K_IO_CONFIG_STAT_0   	0xCA9
#घोषणा PI_ESIC_K_IO_CONFIG_STAT_1   	0xCAA
#घोषणा PI_ESIC_K_DMA_CONFIG         	0xCAB
#घोषणा PI_ESIC_K_INPUT_PORT         	0xCAC
#घोषणा PI_ESIC_K_OUTPUT_PORT        	0xCAD
#घोषणा PI_ESIC_K_FUNCTION_CNTRL	0xCAE

/* Define the bits in the function control रेजिस्टर. */

#घोषणा PI_FUNCTION_CNTRL_M_IOCS0	0x01
#घोषणा PI_FUNCTION_CNTRL_M_IOCS1	0x02
#घोषणा PI_FUNCTION_CNTRL_M_IOCS2	0x04
#घोषणा PI_FUNCTION_CNTRL_M_IOCS3	0x08
#घोषणा PI_FUNCTION_CNTRL_M_MEMCS0	0x10
#घोषणा PI_FUNCTION_CNTRL_M_MEMCS1	0x20
#घोषणा PI_FUNCTION_CNTRL_M_DMA		0x80

/* Define the bits in the slot control रेजिस्टर. */

#घोषणा PI_SLOT_CNTRL_M_RESET		0x04	/* Don't use.       */
#घोषणा PI_SLOT_CNTRL_M_ERROR		0x02	/* Not implemented. */
#घोषणा PI_SLOT_CNTRL_M_ENB		0x01	/* Must be set.     */

/* Define the bits in the burst holकरोff रेजिस्टर. */

#घोषणा PI_BURST_HOLDOFF_M_HOLDOFF	0xFC
#घोषणा PI_BURST_HOLDOFF_M_RESERVED	0x02
#घोषणा PI_BURST_HOLDOFF_M_MEM_MAP	0x01

#घोषणा PI_BURST_HOLDOFF_V_HOLDOFF	2
#घोषणा PI_BURST_HOLDOFF_V_RESERVED	1
#घोषणा PI_BURST_HOLDOFF_V_MEM_MAP	0

/* Define the implicit mask of the Memory Address Compare रेजिस्टरs.  */

#घोषणा PI_MEM_ADD_MASK_M		0x3ff

/* Define the fields in the I/O Address Compare and Mask रेजिस्टरs.  */

#घोषणा PI_IO_CMP_M_SLOT		0xf0

#घोषणा PI_IO_CMP_V_SLOT		4

/* Define the fields in the Interrupt Channel Configuration and Status reg */

#घोषणा PI_CONFIG_STAT_0_M_PEND			0x80
#घोषणा PI_CONFIG_STAT_0_M_RES_1		0x40
#घोषणा PI_CONFIG_STAT_0_M_IREQ_OUT		0x20
#घोषणा PI_CONFIG_STAT_0_M_IREQ_IN		0x10
#घोषणा PI_CONFIG_STAT_0_M_INT_ENB		0x08
#घोषणा PI_CONFIG_STAT_0_M_RES_0		0x04
#घोषणा PI_CONFIG_STAT_0_M_IRQ			0x03

#घोषणा PI_CONFIG_STAT_0_V_PEND			7
#घोषणा PI_CONFIG_STAT_0_V_RES_1		6
#घोषणा PI_CONFIG_STAT_0_V_IREQ_OUT		5
#घोषणा PI_CONFIG_STAT_0_V_IREQ_IN		4
#घोषणा PI_CONFIG_STAT_0_V_INT_ENB		3
#घोषणा PI_CONFIG_STAT_0_V_RES_0		2
#घोषणा PI_CONFIG_STAT_0_V_IRQ			0

#घोषणा PI_CONFIG_STAT_0_IRQ_K_9		0
#घोषणा PI_CONFIG_STAT_0_IRQ_K_10		1
#घोषणा PI_CONFIG_STAT_0_IRQ_K_11		2
#घोषणा PI_CONFIG_STAT_0_IRQ_K_15		3

/* Define DEC FDDIcontroller/EISA (DEFEA) EISA hardware ID's */

#घोषणा DEFEA_PRODUCT_ID	0x0030A310		/* DEC product 300 (no rev)	*/
#घोषणा DEFEA_PROD_ID_1		0x0130A310		/* DEC product 300, rev 1	*/
#घोषणा DEFEA_PROD_ID_2		0x0230A310		/* DEC product 300, rev 2	*/
#घोषणा DEFEA_PROD_ID_3		0x0330A310		/* DEC product 300, rev 3	*/
#घोषणा DEFEA_PROD_ID_4		0x0430A310		/* DEC product 300, rev 4	*/

/**********************************************/
/* Digital PFI Specअगरication v1.0 Definitions */
/**********************************************/

/* PCI Configuration Space Constants */

#घोषणा PFI_K_LAT_TIMER_DEF			0x88	/* def max master latency समयr */
#घोषणा PFI_K_LAT_TIMER_MIN			0x20	/* min max master latency समयr */
#घोषणा PFI_K_CSR_MEM_LEN			0x80	/* 128 bytes */
#घोषणा PFI_K_CSR_IO_LEN			0x80	/* 128 bytes */
#घोषणा PFI_K_PKT_MEM_LEN			0x10000	/* 64K bytes */

/* PFI Register Offsets (starting at PDQ Register Base Address) */

#घोषणा PFI_K_REG_RESERVED_0		 0X00000038
#घोषणा PFI_K_REG_RESERVED_1		 0X0000003C
#घोषणा PFI_K_REG_MODE_CTRL		 0X00000040
#घोषणा PFI_K_REG_STATUS		 0X00000044
#घोषणा PFI_K_REG_FIFO_WRITE		 0X00000048
#घोषणा PFI_K_REG_FIFO_READ		 0X0000004C

/* PFI Mode Control Register Constants */

#घोषणा PFI_MODE_M_RESERVED		 0XFFFFFFF0
#घोषणा PFI_MODE_M_TGT_ABORT_ENB	 0X00000008
#घोषणा PFI_MODE_M_PDQ_INT_ENB		 0X00000004
#घोषणा PFI_MODE_M_PFI_INT_ENB		 0X00000002
#घोषणा PFI_MODE_M_DMA_ENB		 0X00000001

#घोषणा PFI_MODE_V_RESERVED		 4
#घोषणा PFI_MODE_V_TGT_ABORT_ENB	 3
#घोषणा PFI_MODE_V_PDQ_INT_ENB		 2
#घोषणा PFI_MODE_V_PFI_INT_ENB		 1
#घोषणा PFI_MODE_V_DMA_ENB		 0

#घोषणा PFI_MODE_K_ALL_DISABLE		 0X00000000

/* PFI Status Register Constants */

#घोषणा PFI_STATUS_M_RESERVED		 0XFFFFFFC0
#घोषणा PFI_STATUS_M_PFI_ERROR		 0X00000020		/* only valid in rev 1 or later PFI */
#घोषणा PFI_STATUS_M_PDQ_INT		 0X00000010
#घोषणा PFI_STATUS_M_PDQ_DMA_ABORT	 0X00000008
#घोषणा PFI_STATUS_M_FIFO_FULL		 0X00000004
#घोषणा PFI_STATUS_M_FIFO_EMPTY		 0X00000002
#घोषणा PFI_STATUS_M_DMA_IN_PROGRESS	 0X00000001

#घोषणा PFI_STATUS_V_RESERVED		 6
#घोषणा PFI_STATUS_V_PFI_ERROR		 5			/* only valid in rev 1 or later PFI */
#घोषणा PFI_STATUS_V_PDQ_INT		 4
#घोषणा PFI_STATUS_V_PDQ_DMA_ABORT	 3
#घोषणा PFI_STATUS_V_FIFO_FULL		 2
#घोषणा PFI_STATUS_V_FIFO_EMPTY		 1
#घोषणा PFI_STATUS_V_DMA_IN_PROGRESS 0

#घोषणा DFX_FC_PRH2_PRH1_PRH0		0x54003820	/* Packet Request Header bytes + FC */
#घोषणा DFX_PRH0_BYTE			0x20		/* Packet Request Header byte 0 */
#घोषणा DFX_PRH1_BYTE			0x38		/* Packet Request Header byte 1 */
#घोषणा DFX_PRH2_BYTE			0x00		/* Packet Request Header byte 2 */

/* Driver routine status (वापस) codes */

#घोषणा DFX_K_SUCCESS			0			/* routine succeeded */
#घोषणा DFX_K_FAILURE			1			/* routine failed */
#घोषणा DFX_K_OUTSTATE			2			/* bad state क्रम command */
#घोषणा DFX_K_HW_TIMEOUT		3			/* command समयd out */

/* Define LLC host receive buffer min/max/शेष values */

#घोषणा RCV_BUFS_MIN	2					/* minimum pre-allocated receive buffers */
#घोषणा RCV_BUFS_MAX	32					/* maximum pre-allocated receive buffers */
#घोषणा RCV_BUFS_DEF	8					/* शेष pre-allocated receive buffers */

/* Define offsets पूर्णांकo FDDI LLC or SMT receive frame buffers - used when indicating frames */

#घोषणा RCV_BUFF_K_DESCR	0				/* four byte FMC descriptor */
#घोषणा RCV_BUFF_K_PADDING	4				/* three null bytes */
#घोषणा RCV_BUFF_K_FC		7				/* one byte frame control */
#घोषणा RCV_BUFF_K_DA		8				/* six byte destination address */
#घोषणा RCV_BUFF_K_SA		14				/* six byte source address */
#घोषणा RCV_BUFF_K_DATA		20				/* offset to start of packet data */

/* Define offsets पूर्णांकo FDDI LLC transmit frame buffers - used when sending frames */

#घोषणा XMT_BUFF_K_FC		0				/* one byte frame control */
#घोषणा XMT_BUFF_K_DA		1				/* six byte destination address */
#घोषणा XMT_BUFF_K_SA		7				/* six byte source address */
#घोषणा XMT_BUFF_K_DATA		13				/* offset to start of packet data */

/* Macro क्रम checking a "value" is within a specअगरic range */

#घोषणा IN_RANGE(value,low,high) ((value >= low) && (value <= high))

/* Only execute special prपूर्णांक call when debug driver was built */

#अगर_घोषित DEFXX_DEBUG
#घोषणा DBG_prपूर्णांकk(args...) prपूर्णांकk(args)
#अन्यथा
#घोषणा DBG_prपूर्णांकk(args...)
#पूर्ण_अगर

/* Define स्थिरants क्रम masking/unmasking पूर्णांकerrupts */

#घोषणा DFX_MASK_INTERRUPTS		1
#घोषणा DFX_UNMASK_INTERRUPTS		0

/* Define काष्ठाure क्रम driver transmit descriptor block */

प्रकार काष्ठा
	अणु
	काष्ठा sk_buff	*p_skb;					/* ptr to skb */
	पूर्ण XMT_DRIVER_DESCR;

प्रकार काष्ठा DFX_board_tag
	अणु
	/* Keep भव and physical poपूर्णांकers to locked, physically contiguous memory */

	अक्षर				*kदो_स्मृतिed;					/* pci_मुक्त_consistent this on unload */
	dma_addr_t			kदो_स्मृतिed_dma;
	/* DMA handle क्रम the above */
	PI_DESCR_BLOCK			*descr_block_virt;				/* PDQ descriptor block virt address */
	dma_addr_t			descr_block_phys;				/* PDQ descriptor block phys address */
	PI_DMA_CMD_REQ			*cmd_req_virt;					/* Command request buffer virt address */
	dma_addr_t			cmd_req_phys;					/* Command request buffer phys address */
	PI_DMA_CMD_RSP			*cmd_rsp_virt;					/* Command response buffer virt address */
	dma_addr_t			cmd_rsp_phys;					/* Command response buffer phys address */
	अक्षर				*rcv_block_virt;				/* LLC host receive queue buf blk virt */
	dma_addr_t			rcv_block_phys;					/* LLC host receive queue buf blk phys */
	PI_CONSUMER_BLOCK		*cons_block_virt;				/* PDQ consumer block virt address */
	dma_addr_t			cons_block_phys;				/* PDQ consumer block phys address */

	/* Keep local copies of Type 1 and Type 2 रेजिस्टर data */

	PI_TYPE_1_PROD_REG		cmd_req_reg;					/* Command Request रेजिस्टर */
	PI_TYPE_1_PROD_REG		cmd_rsp_reg;					/* Command Response रेजिस्टर */
	PI_TYPE_2_PROD_REG		rcv_xmt_reg;					/* Type 2 (RCV/XMT) रेजिस्टर */

	/* Storage क्रम unicast and multicast address entries in adapter CAM */

	u8				uc_table[1*FDDI_K_ALEN];
	u32				uc_count;						/* number of unicast addresses */
	u8				mc_table[PI_CMD_ADDR_FILTER_K_SIZE*FDDI_K_ALEN];
	u32				mc_count;						/* number of multicast addresses */

	/* Current packet filter settings */

	u32				ind_group_prom;					/* LLC inभागidual & group frame prom mode */
	u32				group_prom;					/* LLC group (multicast) frame prom mode */

	/* Link available flag needed to determine whether to drop outgoing packet requests */

	u32				link_available;					/* is link available? */

	/* Resources to indicate reset type when resetting adapter */

	u32				reset_type;					/* skip or rerun diagnostics */

	/* Store poपूर्णांकers to receive buffers क्रम queue processing code */

	अक्षर				*p_rcv_buff_va[PI_RCV_DATA_K_NUM_ENTRIES];

	/* Store poपूर्णांकers to transmit buffers क्रम transmit completion code */

	XMT_DRIVER_DESCR		xmt_drv_descr_blk[PI_XMT_DATA_K_NUM_ENTRIES];

	/* Transmit spinlocks */

	spinlock_t			lock;

	/* Store device, bus-specअगरic, and parameter inक्रमmation क्रम this adapter */

	काष्ठा net_device		*dev;						/* poपूर्णांकer to device काष्ठाure */
	जोड़ अणु
		व्योम __iomem *mem;
		पूर्णांक port;
	पूर्ण base;										/* base address */
	काष्ठा device			*bus_dev;
	/* Whether to use MMIO or port I/O.  */
	bool				mmio;
	u32				full_duplex_enb;				/* FDDI Full Duplex enable (1 == on, 2 == off) */
	u32				req_ttrt;					/* requested TTRT value (in 80ns units) */
	u32				burst_size;					/* adapter burst size (क्रमागतerated) */
	u32				rcv_bufs_to_post;				/* receive buffers to post क्रम LLC host queue */
	u8				factory_mac_addr[FDDI_K_ALEN];			/* factory (on-board) MAC address */

	/* Common FDDI statistics काष्ठाure and निजी counters */

	काष्ठा fddi_statistics	stats;

	u32				rcv_discards;
	u32				rcv_crc_errors;
	u32				rcv_frame_status_errors;
	u32				rcv_length_errors;
	u32				rcv_total_frames;
	u32				rcv_multicast_frames;
	u32				rcv_total_bytes;

	u32				xmt_discards;
	u32				xmt_length_errors;
	u32				xmt_total_frames;
	u32				xmt_total_bytes;
	पूर्ण DFX_board_t;

#पूर्ण_अगर	/* #अगर_अघोषित _DEFXX_H_ */
