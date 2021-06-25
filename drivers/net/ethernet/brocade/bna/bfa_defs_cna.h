<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Linux network driver क्रम QLogic BR-series Converged Network Adapter.
 */
/*
 * Copyright (c) 2005-2014 Brocade Communications Systems, Inc.
 * Copyright (c) 2014-2015 QLogic Corporation
 * All rights reserved
 * www.qlogic.com
 */
#अगर_अघोषित __BFA_DEFS_CNA_H__
#घोषणा __BFA_DEFS_CNA_H__

#समावेश "bfa_defs.h"

/* FC physical port statistics. */
काष्ठा bfa_port_fc_stats अणु
	u64	secs_reset;	/*!< Seconds since stats is reset */
	u64	tx_frames;	/*!< Tx frames			*/
	u64	tx_words;	/*!< Tx words			*/
	u64	tx_lip;		/*!< Tx LIP			*/
	u64	tx_nos;		/*!< Tx NOS			*/
	u64	tx_ols;		/*!< Tx OLS			*/
	u64	tx_lr;		/*!< Tx LR			*/
	u64	tx_lrr;		/*!< Tx LRR			*/
	u64	rx_frames;	/*!< Rx frames			*/
	u64	rx_words;	/*!< Rx words			*/
	u64	lip_count;	/*!< Rx LIP			*/
	u64	nos_count;	/*!< Rx NOS			*/
	u64	ols_count;	/*!< Rx OLS			*/
	u64	lr_count;	/*!< Rx LR			*/
	u64	lrr_count;	/*!< Rx LRR			*/
	u64	invalid_crcs;	/*!< Rx CRC err frames		*/
	u64	invalid_crc_gd_eof; /*!< Rx CRC err good खातापूर्ण frames */
	u64	undersized_frm; /*!< Rx undersized frames	*/
	u64	oversized_frm;	/*!< Rx oversized frames	*/
	u64	bad_eof_frm;	/*!< Rx frames with bad खातापूर्ण	*/
	u64	error_frames;	/*!< Errored frames		*/
	u64	dropped_frames;	/*!< Dropped frames		*/
	u64	link_failures;	/*!< Link Failure (LF) count	*/
	u64	loss_of_syncs;	/*!< Loss of sync count		*/
	u64	loss_of_संकेतs; /*!< Loss of संकेत count	*/
	u64	primseq_errs;	/*!< Primitive sequence protocol err. */
	u64	bad_os_count;	/*!< Invalid ordered sets	*/
	u64	err_enc_out;	/*!< Encoding err nonframe_8b10b */
	u64	err_enc;	/*!< Encoding err frame_8b10b	*/
	u64	bbsc_frames_lost; /*!< Credit Recovery-Frames Lost  */
	u64	bbsc_credits_lost; /*!< Credit Recovery-Credits Lost */
	u64	bbsc_link_resets; /*!< Credit Recovery-Link Resets   */
पूर्ण;

/* Eth Physical Port statistics. */
काष्ठा bfa_port_eth_stats अणु
	u64	secs_reset;	/*!< Seconds since stats is reset */
	u64	frame_64;	/*!< Frames 64 bytes		*/
	u64	frame_65_127;	/*!< Frames 65-127 bytes	*/
	u64	frame_128_255;	/*!< Frames 128-255 bytes	*/
	u64	frame_256_511;	/*!< Frames 256-511 bytes	*/
	u64	frame_512_1023;	/*!< Frames 512-1023 bytes	*/
	u64	frame_1024_1518; /*!< Frames 1024-1518 bytes	*/
	u64	frame_1519_1522; /*!< Frames 1519-1522 bytes	*/
	u64	tx_bytes;	/*!< Tx bytes			*/
	u64	tx_packets;	 /*!< Tx packets		*/
	u64	tx_mcast_packets; /*!< Tx multicast packets	*/
	u64	tx_bcast_packets; /*!< Tx broadcast packets	*/
	u64	tx_control_frame; /*!< Tx control frame		*/
	u64	tx_drop;	/*!< Tx drops			*/
	u64	tx_jabber;	/*!< Tx jabber			*/
	u64	tx_fcs_error;	/*!< Tx FCS errors		*/
	u64	tx_fragments;	/*!< Tx fragments		*/
	u64	rx_bytes;	/*!< Rx bytes			*/
	u64	rx_packets;	/*!< Rx packets			*/
	u64	rx_mcast_packets; /*!< Rx multicast packets	*/
	u64	rx_bcast_packets; /*!< Rx broadcast packets	*/
	u64	rx_control_frames; /*!< Rx control frames	*/
	u64	rx_unknown_opcode; /*!< Rx unknown opcode	*/
	u64	rx_drop;	/*!< Rx drops			*/
	u64	rx_jabber;	/*!< Rx jabber			*/
	u64	rx_fcs_error;	/*!< Rx FCS errors		*/
	u64	rx_alignment_error; /*!< Rx alignment errors	*/
	u64	rx_frame_length_error; /*!< Rx frame len errors	*/
	u64	rx_code_error;	/*!< Rx code errors		*/
	u64	rx_fragments;	/*!< Rx fragments		*/
	u64	rx_छोड़ो;	/*!< Rx छोड़ो			*/
	u64	rx_zero_छोड़ो;	/*!< Rx zero छोड़ो		*/
	u64	tx_छोड़ो;	/*!< Tx छोड़ो			*/
	u64	tx_zero_छोड़ो;	/*!< Tx zero छोड़ो		*/
	u64	rx_fcoe_छोड़ो;	/*!< Rx FCoE छोड़ो		*/
	u64	rx_fcoe_zero_छोड़ो; /*!< Rx FCoE zero छोड़ो	*/
	u64	tx_fcoe_छोड़ो;	/*!< Tx FCoE छोड़ो		*/
	u64	tx_fcoe_zero_छोड़ो; /*!< Tx FCoE zero छोड़ो	*/
	u64	rx_iscsi_छोड़ो;	/*!< Rx iSCSI छोड़ो		*/
	u64	rx_iscsi_zero_छोड़ो; /*!< Rx iSCSI zero छोड़ो	*/
	u64	tx_iscsi_छोड़ो;	/*!< Tx iSCSI छोड़ो		*/
	u64	tx_iscsi_zero_छोड़ो; /*!< Tx iSCSI zero छोड़ो	*/
पूर्ण;

/* Port statistics. */
जोड़ bfa_port_stats_u अणु
	काष्ठा bfa_port_fc_stats fc;
	काष्ठा bfa_port_eth_stats eth;
पूर्ण;

#घोषणा BFA_CEE_LLDP_MAX_STRING_LEN (128)
#घोषणा BFA_CEE_DCBX_MAX_PRIORITY	(8)
#घोषणा BFA_CEE_DCBX_MAX_PGID		(8)

#घोषणा BFA_CEE_LLDP_SYS_CAP_OTHER	0x0001
#घोषणा BFA_CEE_LLDP_SYS_CAP_REPEATER	0x0002
#घोषणा BFA_CEE_LLDP_SYS_CAP_MAC_BRIDGE	0x0004
#घोषणा BFA_CEE_LLDP_SYS_CAP_WLAN_AP	0x0008
#घोषणा BFA_CEE_LLDP_SYS_CAP_ROUTER	0x0010
#घोषणा BFA_CEE_LLDP_SYS_CAP_TELEPHONE	0x0020
#घोषणा BFA_CEE_LLDP_SYS_CAP_DOCSIS_CD	0x0040
#घोषणा BFA_CEE_LLDP_SYS_CAP_STATION	0x0080
#घोषणा BFA_CEE_LLDP_SYS_CAP_CVLAN	0x0100
#घोषणा BFA_CEE_LLDP_SYS_CAP_SVLAN	0x0200
#घोषणा BFA_CEE_LLDP_SYS_CAP_TPMR	0x0400

/* LLDP string type */
काष्ठा bfa_cee_lldp_str अणु
	u8 sub_type;
	u8 len;
	u8 rsvd[2];
	u8 value[BFA_CEE_LLDP_MAX_STRING_LEN];
पूर्ण __packed;

/* LLDP parameters */
काष्ठा bfa_cee_lldp_cfg अणु
	काष्ठा bfa_cee_lldp_str chassis_id;
	काष्ठा bfa_cee_lldp_str port_id;
	काष्ठा bfa_cee_lldp_str port_desc;
	काष्ठा bfa_cee_lldp_str sys_name;
	काष्ठा bfa_cee_lldp_str sys_desc;
	काष्ठा bfa_cee_lldp_str mgmt_addr;
	u16 समय_प्रकारo_live;
	u16 enabled_प्रणाली_cap;
पूर्ण __packed;

क्रमागत bfa_cee_dcbx_version अणु
	DCBX_PROTOCOL_PRECEE	= 1,
	DCBX_PROTOCOL_CEE	= 2,
पूर्ण;

क्रमागत bfa_cee_lls अणु
	/* LLS is करोwn because the TLV not sent by the peer */
	CEE_LLS_DOWN_NO_TLV = 0,
	/* LLS is करोwn as advertised by the peer */
	CEE_LLS_DOWN	= 1,
	CEE_LLS_UP	= 2,
पूर्ण;

/* CEE/DCBX parameters */
काष्ठा bfa_cee_dcbx_cfg अणु
	u8 pgid[BFA_CEE_DCBX_MAX_PRIORITY];
	u8 pg_percentage[BFA_CEE_DCBX_MAX_PGID];
	u8 pfc_primap; /* biपंचांगap of priorties with PFC enabled */
	u8 fcoe_primap; /* biपंचांगap of priorities used क्रम FcoE traffic */
	u8 iscsi_primap; /* biपंचांगap of priorities used क्रम iSCSI traffic */
	u8 dcbx_version; /* operating version:CEE or preCEE */
	u8 lls_fcoe; /* FCoE Logical Link Status */
	u8 lls_lan; /* LAN Logical Link Status */
	u8 rsvd[2];
पूर्ण __packed;

/* CEE status */
/* Making this to tri-state क्रम the benefit of port list command */
क्रमागत bfa_cee_status अणु
	CEE_UP = 0,
	CEE_PHY_UP = 1,
	CEE_LOOPBACK = 2,
	CEE_PHY_DOWN = 3,
पूर्ण;

/* CEE Query */
काष्ठा bfa_cee_attr अणु
	u8	cee_status;
	u8 error_reason;
	काष्ठा bfa_cee_lldp_cfg lldp_remote;
	काष्ठा bfa_cee_dcbx_cfg dcbx_remote;
	u8 src_mac[ETH_ALEN];
	u8 link_speed;
	u8 nw_priority;
	u8 filler[2];
पूर्ण __packed;

/* LLDP/DCBX/CEE Statistics */
काष्ठा bfa_cee_stats अणु
	u32	lldp_tx_frames;		/*!< LLDP Tx Frames */
	u32	lldp_rx_frames;		/*!< LLDP Rx Frames */
	u32	lldp_rx_frames_invalid;	/*!< LLDP Rx Frames invalid */
	u32	lldp_rx_frames_new;	/*!< LLDP Rx Frames new */
	u32	lldp_tlvs_unrecognized;	/*!< LLDP Rx unrecognized TLVs */
	u32	lldp_rx_shutकरोwn_tlvs;	/*!< LLDP Rx shutकरोwn TLVs */
	u32	lldp_info_aged_out;	/*!< LLDP remote info aged out */
	u32	dcbx_phylink_ups;	/*!< DCBX phy link ups */
	u32	dcbx_phylink_करोwns;	/*!< DCBX phy link करोwns */
	u32	dcbx_rx_tlvs;		/*!< DCBX Rx TLVs */
	u32	dcbx_rx_tlvs_invalid;	/*!< DCBX Rx TLVs invalid */
	u32	dcbx_control_tlv_error;	/*!< DCBX control TLV errors */
	u32	dcbx_feature_tlv_error;	/*!< DCBX feature TLV errors */
	u32	dcbx_cee_cfg_new;	/*!< DCBX new CEE cfg rcvd */
	u32	cee_status_करोwn;	/*!< CEE status करोwn */
	u32	cee_status_up;		/*!< CEE status up */
	u32	cee_hw_cfg_changed;	/*!< CEE hw cfg changed */
	u32	cee_rx_invalid_cfg;	/*!< CEE invalid cfg */
पूर्ण __packed;

#पूर्ण_अगर	/* __BFA_DEFS_CNA_H__ */
