<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/*
 * Copyright (c) 2004 Mellanox Technologies Ltd.  All rights reserved.
 * Copyright (c) 2004 Infinicon Corporation.  All rights reserved.
 * Copyright (c) 2004 Intel Corporation.  All rights reserved.
 * Copyright (c) 2004 Topspin Corporation.  All rights reserved.
 * Copyright (c) 2004-2006 Voltaire Corporation.  All rights reserved.
 */

#अगर_अघोषित IB_MAD_H
#घोषणा IB_MAD_H

#समावेश <linux/list.h>

#समावेश <rdma/ib_verbs.h>
#समावेश <uapi/rdma/ib_user_mad.h>

/* Management base versions */
#घोषणा IB_MGMT_BASE_VERSION			1
#घोषणा OPA_MGMT_BASE_VERSION			0x80

#घोषणा OPA_SM_CLASS_VERSION			0x80

/* Management classes */
#घोषणा IB_MGMT_CLASS_SUBN_LID_ROUTED		0x01
#घोषणा IB_MGMT_CLASS_SUBN_सूचीECTED_ROUTE	0x81
#घोषणा IB_MGMT_CLASS_SUBN_ADM			0x03
#घोषणा IB_MGMT_CLASS_PERF_MGMT			0x04
#घोषणा IB_MGMT_CLASS_BM			0x05
#घोषणा IB_MGMT_CLASS_DEVICE_MGMT		0x06
#घोषणा IB_MGMT_CLASS_CM			0x07
#घोषणा IB_MGMT_CLASS_SNMP			0x08
#घोषणा IB_MGMT_CLASS_DEVICE_ADM		0x10
#घोषणा IB_MGMT_CLASS_BOOT_MGMT			0x11
#घोषणा IB_MGMT_CLASS_BIS			0x12
#घोषणा IB_MGMT_CLASS_CONG_MGMT			0x21
#घोषणा IB_MGMT_CLASS_VENDOR_RANGE2_START	0x30
#घोषणा IB_MGMT_CLASS_VENDOR_RANGE2_END		0x4F

#घोषणा	IB_OPENIB_OUI				(0x001405)

/* Management methods */
#घोषणा IB_MGMT_METHOD_GET			0x01
#घोषणा IB_MGMT_METHOD_SET			0x02
#घोषणा IB_MGMT_METHOD_GET_RESP			0x81
#घोषणा IB_MGMT_METHOD_SEND			0x03
#घोषणा IB_MGMT_METHOD_TRAP			0x05
#घोषणा IB_MGMT_METHOD_REPORT			0x06
#घोषणा IB_MGMT_METHOD_REPORT_RESP		0x86
#घोषणा IB_MGMT_METHOD_TRAP_REPRESS		0x07

#घोषणा IB_MGMT_METHOD_RESP			0x80
#घोषणा IB_BM_ATTR_MOD_RESP			cpu_to_be32(1)

#घोषणा IB_MGMT_MAX_METHODS			128

/* MAD Status field bit masks */
#घोषणा IB_MGMT_MAD_STATUS_SUCCESS			0x0000
#घोषणा IB_MGMT_MAD_STATUS_BUSY				0x0001
#घोषणा IB_MGMT_MAD_STATUS_REसूचीECT_REQD		0x0002
#घोषणा IB_MGMT_MAD_STATUS_BAD_VERSION			0x0004
#घोषणा IB_MGMT_MAD_STATUS_UNSUPPORTED_METHOD		0x0008
#घोषणा IB_MGMT_MAD_STATUS_UNSUPPORTED_METHOD_ATTRIB	0x000c
#घोषणा IB_MGMT_MAD_STATUS_INVALID_ATTRIB_VALUE		0x001c

/* RMPP inक्रमmation */
#घोषणा IB_MGMT_RMPP_VERSION			1

#घोषणा IB_MGMT_RMPP_TYPE_DATA			1
#घोषणा IB_MGMT_RMPP_TYPE_ACK			2
#घोषणा IB_MGMT_RMPP_TYPE_STOP			3
#घोषणा IB_MGMT_RMPP_TYPE_ABORT			4

#घोषणा IB_MGMT_RMPP_FLAG_ACTIVE		1
#घोषणा IB_MGMT_RMPP_FLAG_FIRST			(1<<1)
#घोषणा IB_MGMT_RMPP_FLAG_LAST			(1<<2)

#घोषणा IB_MGMT_RMPP_NO_RESPTIME		0x1F

#घोषणा	IB_MGMT_RMPP_STATUS_SUCCESS		0
#घोषणा	IB_MGMT_RMPP_STATUS_RESX		1
#घोषणा	IB_MGMT_RMPP_STATUS_ABORT_MIN		118
#घोषणा	IB_MGMT_RMPP_STATUS_T2L			118
#घोषणा	IB_MGMT_RMPP_STATUS_BAD_LEN		119
#घोषणा	IB_MGMT_RMPP_STATUS_BAD_SEG		120
#घोषणा	IB_MGMT_RMPP_STATUS_BADT		121
#घोषणा	IB_MGMT_RMPP_STATUS_W2S			122
#घोषणा	IB_MGMT_RMPP_STATUS_S2B			123
#घोषणा	IB_MGMT_RMPP_STATUS_BAD_STATUS		124
#घोषणा	IB_MGMT_RMPP_STATUS_UNV			125
#घोषणा	IB_MGMT_RMPP_STATUS_TMR			126
#घोषणा	IB_MGMT_RMPP_STATUS_UNSPEC		127
#घोषणा	IB_MGMT_RMPP_STATUS_ABORT_MAX		127

#घोषणा IB_QP0		0
#घोषणा IB_QP1		cpu_to_be32(1)
#घोषणा IB_QP1_QKEY	0x80010000
#घोषणा IB_QP_SET_QKEY	0x80000000

#घोषणा IB_DEFAULT_PKEY_PARTIAL 0x7FFF
#घोषणा IB_DEFAULT_PKEY_FULL	0xFFFF

/*
 * Generic trap/notice types
 */
#घोषणा IB_NOTICE_TYPE_FATAL	0x80
#घोषणा IB_NOTICE_TYPE_URGENT	0x81
#घोषणा IB_NOTICE_TYPE_SECURITY	0x82
#घोषणा IB_NOTICE_TYPE_SM	0x83
#घोषणा IB_NOTICE_TYPE_INFO	0x84

/*
 * Generic trap/notice producers
 */
#घोषणा IB_NOTICE_PROD_CA		cpu_to_be16(1)
#घोषणा IB_NOTICE_PROD_SWITCH		cpu_to_be16(2)
#घोषणा IB_NOTICE_PROD_ROUTER		cpu_to_be16(3)
#घोषणा IB_NOTICE_PROD_CLASS_MGR	cpu_to_be16(4)

क्रमागत अणु
	IB_MGMT_MAD_HDR = 24,
	IB_MGMT_MAD_DATA = 232,
	IB_MGMT_RMPP_HDR = 36,
	IB_MGMT_RMPP_DATA = 220,
	IB_MGMT_VENDOR_HDR = 40,
	IB_MGMT_VENDOR_DATA = 216,
	IB_MGMT_SA_HDR = 56,
	IB_MGMT_SA_DATA = 200,
	IB_MGMT_DEVICE_HDR = 64,
	IB_MGMT_DEVICE_DATA = 192,
	IB_MGMT_MAD_SIZE = IB_MGMT_MAD_HDR + IB_MGMT_MAD_DATA,
	OPA_MGMT_MAD_DATA = 2024,
	OPA_MGMT_RMPP_DATA = 2012,
	OPA_MGMT_MAD_SIZE = IB_MGMT_MAD_HDR + OPA_MGMT_MAD_DATA,
पूर्ण;

काष्ठा ib_mad_hdr अणु
	u8	base_version;
	u8	mgmt_class;
	u8	class_version;
	u8	method;
	__be16	status;
	__be16	class_specअगरic;
	__be64	tid;
	__be16	attr_id;
	__be16	resv;
	__be32	attr_mod;
पूर्ण;

काष्ठा ib_rmpp_hdr अणु
	u8	rmpp_version;
	u8	rmpp_type;
	u8	rmpp_rसमय_flags;
	u8	rmpp_status;
	__be32	seg_num;
	__be32	paylen_newwin;
पूर्ण;

प्रकार u64 __bitwise ib_sa_comp_mask;

#घोषणा IB_SA_COMP_MASK(n) ((__क्रमce ib_sa_comp_mask) cpu_to_be64(1ull << (n)))

/*
 * ib_sa_hdr and ib_sa_mad काष्ठाures must be packed because they have
 * 64-bit fields that are only 32-bit aligned. 64-bit architectures will
 * lay them out wrong otherwise.  (And unक्रमtunately they are sent on
 * the wire so we can't change the layout)
 */
काष्ठा ib_sa_hdr अणु
	__be64			sm_key;
	__be16			attr_offset;
	__be16			reserved;
	ib_sa_comp_mask		comp_mask;
पूर्ण __packed;

काष्ठा ib_mad अणु
	काष्ठा ib_mad_hdr	mad_hdr;
	u8			data[IB_MGMT_MAD_DATA];
पूर्ण;

काष्ठा opa_mad अणु
	काष्ठा ib_mad_hdr	mad_hdr;
	u8			data[OPA_MGMT_MAD_DATA];
पूर्ण;

काष्ठा ib_rmpp_mad अणु
	काष्ठा ib_mad_hdr	mad_hdr;
	काष्ठा ib_rmpp_hdr	rmpp_hdr;
	u8			data[IB_MGMT_RMPP_DATA];
पूर्ण;

काष्ठा opa_rmpp_mad अणु
	काष्ठा ib_mad_hdr	mad_hdr;
	काष्ठा ib_rmpp_hdr	rmpp_hdr;
	u8			data[OPA_MGMT_RMPP_DATA];
पूर्ण;

काष्ठा ib_sa_mad अणु
	काष्ठा ib_mad_hdr	mad_hdr;
	काष्ठा ib_rmpp_hdr	rmpp_hdr;
	काष्ठा ib_sa_hdr	sa_hdr;
	u8			data[IB_MGMT_SA_DATA];
पूर्ण __packed;

काष्ठा ib_venकरोr_mad अणु
	काष्ठा ib_mad_hdr	mad_hdr;
	काष्ठा ib_rmpp_hdr	rmpp_hdr;
	u8			reserved;
	u8			oui[3];
	u8			data[IB_MGMT_VENDOR_DATA];
पूर्ण;

#घोषणा IB_MGMT_CLASSPORTINFO_ATTR_ID	cpu_to_be16(0x0001)

#घोषणा IB_CLASS_PORT_INFO_RESP_TIME_MASK	0x1F
#घोषणा IB_CLASS_PORT_INFO_RESP_TIME_FIELD_SIZE 5

काष्ठा ib_class_port_info अणु
	u8			base_version;
	u8			class_version;
	__be16			capability_mask;
	  /* 27 bits क्रम cap_mask2, 5 bits क्रम resp_समय */
	__be32			cap_mask2_resp_समय;
	u8			redirect_gid[16];
	__be32			redirect_tcslfl;
	__be16			redirect_lid;
	__be16			redirect_pkey;
	__be32			redirect_qp;
	__be32			redirect_qkey;
	u8			trap_gid[16];
	__be32			trap_tcslfl;
	__be16			trap_lid;
	__be16			trap_pkey;
	__be32			trap_hlqp;
	__be32			trap_qkey;
पूर्ण;

/* PortInfo CapabilityMask */
क्रमागत ib_port_capability_mask_bits अणु
	IB_PORT_SM = 1 << 1,
	IB_PORT_NOTICE_SUP = 1 << 2,
	IB_PORT_TRAP_SUP = 1 << 3,
	IB_PORT_OPT_IPD_SUP = 1 << 4,
	IB_PORT_AUTO_MIGR_SUP = 1 << 5,
	IB_PORT_SL_MAP_SUP = 1 << 6,
	IB_PORT_MKEY_NVRAM = 1 << 7,
	IB_PORT_PKEY_NVRAM = 1 << 8,
	IB_PORT_LED_INFO_SUP = 1 << 9,
	IB_PORT_SM_DISABLED = 1 << 10,
	IB_PORT_SYS_IMAGE_GUID_SUP = 1 << 11,
	IB_PORT_PKEY_SW_EXT_PORT_TRAP_SUP = 1 << 12,
	IB_PORT_EXTENDED_SPEEDS_SUP = 1 << 14,
	IB_PORT_CAP_MASK2_SUP = 1 << 15,
	IB_PORT_CM_SUP = 1 << 16,
	IB_PORT_SNMP_TUNNEL_SUP = 1 << 17,
	IB_PORT_REINIT_SUP = 1 << 18,
	IB_PORT_DEVICE_MGMT_SUP = 1 << 19,
	IB_PORT_VENDOR_CLASS_SUP = 1 << 20,
	IB_PORT_DR_NOTICE_SUP = 1 << 21,
	IB_PORT_CAP_MASK_NOTICE_SUP = 1 << 22,
	IB_PORT_BOOT_MGMT_SUP = 1 << 23,
	IB_PORT_LINK_LATENCY_SUP = 1 << 24,
	IB_PORT_CLIENT_REG_SUP = 1 << 25,
	IB_PORT_OTHER_LOCAL_CHANGES_SUP = 1 << 26,
	IB_PORT_LINK_SPEED_WIDTH_TABLE_SUP = 1 << 27,
	IB_PORT_VENDOR_SPECIFIC_MADS_TABLE_SUP = 1 << 28,
	IB_PORT_MCAST_PKEY_TRAP_SUPPRESSION_SUP = 1 << 29,
	IB_PORT_MCAST_FDB_TOP_SUP = 1 << 30,
	IB_PORT_HIERARCHY_INFO_SUP = 1ULL << 31,
पूर्ण;

क्रमागत ib_port_capability_mask2_bits अणु
	IB_PORT_SET_NODE_DESC_SUP		= 1 << 0,
	IB_PORT_EX_PORT_INFO_EX_SUP		= 1 << 1,
	IB_PORT_VIRT_SUP			= 1 << 2,
	IB_PORT_SWITCH_PORT_STATE_TABLE_SUP	= 1 << 3,
	IB_PORT_LINK_WIDTH_2X_SUP		= 1 << 4,
	IB_PORT_LINK_SPEED_HDR_SUP		= 1 << 5,
पूर्ण;

#घोषणा OPA_CLASS_PORT_INFO_PR_SUPPORT BIT(26)

काष्ठा opa_class_port_info अणु
	u8 base_version;
	u8 class_version;
	__be16 cap_mask;
	__be32 cap_mask2_resp_समय;

	u8 redirect_gid[16];
	__be32 redirect_tc_fl;
	__be32 redirect_lid;
	__be32 redirect_sl_qp;
	__be32 redirect_qkey;

	u8 trap_gid[16];
	__be32 trap_tc_fl;
	__be32 trap_lid;
	__be32 trap_hl_qp;
	__be32 trap_qkey;

	__be16 trap_pkey;
	__be16 redirect_pkey;

	u8 trap_sl_rsvd;
	u8 reserved[3];
पूर्ण __packed;

/**
 * ib_get_cpi_resp_समय - Returns the resp_समय value from
 * cap_mask2_resp_समय in ib_class_port_info.
 * @cpi: A काष्ठा ib_class_port_info mad.
 */
अटल अंतरभूत u8 ib_get_cpi_resp_समय(काष्ठा ib_class_port_info *cpi)
अणु
	वापस (u8)(be32_to_cpu(cpi->cap_mask2_resp_समय) &
		    IB_CLASS_PORT_INFO_RESP_TIME_MASK);
पूर्ण

/**
 * ib_set_cpi_respसमय - Sets the response समय in an
 * ib_class_port_info mad.
 * @cpi: A काष्ठा ib_class_port_info.
 * @rसमय: The response समय to set.
 */
अटल अंतरभूत व्योम ib_set_cpi_resp_समय(काष्ठा ib_class_port_info *cpi,
					u8 rसमय)
अणु
	cpi->cap_mask2_resp_समय =
		(cpi->cap_mask2_resp_समय &
		 cpu_to_be32(~IB_CLASS_PORT_INFO_RESP_TIME_MASK)) |
		cpu_to_be32(rसमय & IB_CLASS_PORT_INFO_RESP_TIME_MASK);
पूर्ण

/**
 * ib_get_cpi_capmask2 - Returns the capmask2 value from
 * cap_mask2_resp_समय in ib_class_port_info.
 * @cpi: A काष्ठा ib_class_port_info mad.
 */
अटल अंतरभूत u32 ib_get_cpi_capmask2(काष्ठा ib_class_port_info *cpi)
अणु
	वापस (be32_to_cpu(cpi->cap_mask2_resp_समय) >>
		IB_CLASS_PORT_INFO_RESP_TIME_FIELD_SIZE);
पूर्ण

/**
 * ib_set_cpi_capmask2 - Sets the capmask2 in an
 * ib_class_port_info mad.
 * @cpi: A काष्ठा ib_class_port_info.
 * @capmask2: The capmask2 to set.
 */
अटल अंतरभूत व्योम ib_set_cpi_capmask2(काष्ठा ib_class_port_info *cpi,
				       u32 capmask2)
अणु
	cpi->cap_mask2_resp_समय =
		(cpi->cap_mask2_resp_समय &
		 cpu_to_be32(IB_CLASS_PORT_INFO_RESP_TIME_MASK)) |
		cpu_to_be32(capmask2 <<
			    IB_CLASS_PORT_INFO_RESP_TIME_FIELD_SIZE);
पूर्ण

/**
 * opa_get_cpi_capmask2 - Returns the capmask2 value from
 * cap_mask2_resp_समय in ib_class_port_info.
 * @cpi: A काष्ठा opa_class_port_info mad.
 */
अटल अंतरभूत u32 opa_get_cpi_capmask2(काष्ठा opa_class_port_info *cpi)
अणु
	वापस (be32_to_cpu(cpi->cap_mask2_resp_समय) >>
		IB_CLASS_PORT_INFO_RESP_TIME_FIELD_SIZE);
पूर्ण

काष्ठा ib_mad_notice_attr अणु
	u8 generic_type;
	u8 prod_type_msb;
	__be16 prod_type_lsb;
	__be16 trap_num;
	__be16 issuer_lid;
	__be16 toggle_count;

	जोड़ अणु
		काष्ठा अणु
			u8	details[54];
		पूर्ण raw_data;

		काष्ठा अणु
			__be16	reserved;
			__be16	lid;		/* where violation happened */
			u8	port_num;	/* where violation happened */
		पूर्ण __packed ntc_129_131;

		काष्ठा अणु
			__be16	reserved;
			__be16	lid;		/* LID where change occurred */
			u8	reserved2;
			u8	local_changes;	/* low bit - local changes */
			__be32	new_cap_mask;	/* new capability mask */
			u8	reserved3;
			u8	change_flags;	/* low 3 bits only */
		पूर्ण __packed ntc_144;

		काष्ठा अणु
			__be16	reserved;
			__be16	lid;		/* lid where sys guid changed */
			__be16	reserved2;
			__be64	new_sys_guid;
		पूर्ण __packed ntc_145;

		काष्ठा अणु
			__be16	reserved;
			__be16	lid;
			__be16	dr_slid;
			u8	method;
			u8	reserved2;
			__be16	attr_id;
			__be32	attr_mod;
			__be64	mkey;
			u8	reserved3;
			u8	dr_trunc_hop;
			u8	dr_rtn_path[30];
		पूर्ण __packed ntc_256;

		काष्ठा अणु
			__be16		reserved;
			__be16		lid1;
			__be16		lid2;
			__be32		key;
			__be32		sl_qp1;	/* SL: high 4 bits */
			__be32		qp2;	/* high 8 bits reserved */
			जोड़ ib_gid	gid1;
			जोड़ ib_gid	gid2;
		पूर्ण __packed ntc_257_258;

	पूर्ण details;
पूर्ण;

/**
 * ib_mad_send_buf - MAD data buffer and work request क्रम sends.
 * @next: A poपूर्णांकer used to chain together MADs क्रम posting.
 * @mad: References an allocated MAD data buffer क्रम MADs that करो not have
 *   RMPP active.  For MADs using RMPP, references the common and management
 *   class specअगरic headers.
 * @mad_agent: MAD agent that allocated the buffer.
 * @ah: The address handle to use when sending the MAD.
 * @context: User-controlled context fields.
 * @hdr_len: Indicates the size of the data header of the MAD.  This length
 *   includes the common MAD, RMPP, and class specअगरic headers.
 * @data_len: Indicates the total size of user-transferred data.
 * @seg_count: The number of RMPP segments allocated क्रम this send.
 * @seg_size: Size of the data in each RMPP segment.  This करोes not include
 *   class specअगरic headers.
 * @seg_rmpp_size: Size of each RMPP segment including the class specअगरic
 *   headers.
 * @समयout_ms: Time to रुको क्रम a response.
 * @retries: Number of बार to retry a request क्रम a response.  For MADs
 *   using RMPP, this applies per winकरोw.  On completion, वापसs the number
 *   of retries needed to complete the transfer.
 *
 * Users are responsible क्रम initializing the MAD buffer itself, with the
 * exception of any RMPP header.  Additional segment buffer space allocated
 * beyond data_len is padding.
 */
काष्ठा ib_mad_send_buf अणु
	काष्ठा ib_mad_send_buf	*next;
	व्योम			*mad;
	काष्ठा ib_mad_agent	*mad_agent;
	काष्ठा ib_ah		*ah;
	व्योम			*context[2];
	पूर्णांक			hdr_len;
	पूर्णांक			data_len;
	पूर्णांक			seg_count;
	पूर्णांक			seg_size;
	पूर्णांक			seg_rmpp_size;
	पूर्णांक			समयout_ms;
	पूर्णांक			retries;
पूर्ण;

/**
 * ib_response_mad - Returns अगर the specअगरied MAD has been generated in
 *   response to a sent request or trap.
 */
पूर्णांक ib_response_mad(स्थिर काष्ठा ib_mad_hdr *hdr);

/**
 * ib_get_rmpp_respसमय - Returns the RMPP response समय.
 * @rmpp_hdr: An RMPP header.
 */
अटल अंतरभूत u8 ib_get_rmpp_respसमय(काष्ठा ib_rmpp_hdr *rmpp_hdr)
अणु
	वापस rmpp_hdr->rmpp_rसमय_flags >> 3;
पूर्ण

/**
 * ib_get_rmpp_flags - Returns the RMPP flags.
 * @rmpp_hdr: An RMPP header.
 */
अटल अंतरभूत u8 ib_get_rmpp_flags(काष्ठा ib_rmpp_hdr *rmpp_hdr)
अणु
	वापस rmpp_hdr->rmpp_rसमय_flags & 0x7;
पूर्ण

/**
 * ib_set_rmpp_respसमय - Sets the response समय in an RMPP header.
 * @rmpp_hdr: An RMPP header.
 * @rसमय: The response समय to set.
 */
अटल अंतरभूत व्योम ib_set_rmpp_respसमय(काष्ठा ib_rmpp_hdr *rmpp_hdr, u8 rसमय)
अणु
	rmpp_hdr->rmpp_rसमय_flags = ib_get_rmpp_flags(rmpp_hdr) | (rसमय << 3);
पूर्ण

/**
 * ib_set_rmpp_flags - Sets the flags in an RMPP header.
 * @rmpp_hdr: An RMPP header.
 * @flags: The flags to set.
 */
अटल अंतरभूत व्योम ib_set_rmpp_flags(काष्ठा ib_rmpp_hdr *rmpp_hdr, u8 flags)
अणु
	rmpp_hdr->rmpp_rसमय_flags = (rmpp_hdr->rmpp_rसमय_flags & 0xF8) |
				     (flags & 0x7);
पूर्ण

काष्ठा ib_mad_agent;
काष्ठा ib_mad_send_wc;
काष्ठा ib_mad_recv_wc;

/**
 * ib_mad_send_handler - callback handler क्रम a sent MAD.
 * @mad_agent: MAD agent that sent the MAD.
 * @mad_send_wc: Send work completion inक्रमmation on the sent MAD.
 */
प्रकार व्योम (*ib_mad_send_handler)(काष्ठा ib_mad_agent *mad_agent,
				    काष्ठा ib_mad_send_wc *mad_send_wc);

/**
 * ib_mad_recv_handler - callback handler क्रम a received MAD.
 * @mad_agent: MAD agent requesting the received MAD.
 * @send_buf: Send buffer अगर found, अन्यथा शून्य
 * @mad_recv_wc: Received work completion inक्रमmation on the received MAD.
 *
 * MADs received in response to a send request operation will be handed to
 * the user beक्रमe the send operation completes.  All data buffers given
 * to रेजिस्टरed agents through this routine are owned by the receiving
 * client.
 */
प्रकार व्योम (*ib_mad_recv_handler)(काष्ठा ib_mad_agent *mad_agent,
				    काष्ठा ib_mad_send_buf *send_buf,
				    काष्ठा ib_mad_recv_wc *mad_recv_wc);

/**
 * ib_mad_agent - Used to track MAD registration with the access layer.
 * @device: Reference to device registration is on.
 * @qp: Reference to QP used क्रम sending and receiving MADs.
 * @mr: Memory region क्रम प्रणाली memory usable क्रम DMA.
 * @recv_handler: Callback handler क्रम a received MAD.
 * @send_handler: Callback handler क्रम a sent MAD.
 * @context: User-specअगरied context associated with this registration.
 * @hi_tid: Access layer asचिन्हित transaction ID क्रम this client.
 *   Unsolicited MADs sent by this client will have the upper 32-bits
 *   of their TID set to this value.
 * @flags: registration flags
 * @port_num: Port number on which QP is रेजिस्टरed
 * @rmpp_version: If set, indicates the RMPP version used by this agent.
 */
क्रमागत अणु
	IB_MAD_USER_RMPP = IB_USER_MAD_USER_RMPP,
पूर्ण;
काष्ठा ib_mad_agent अणु
	काष्ठा ib_device	*device;
	काष्ठा ib_qp		*qp;
	ib_mad_recv_handler	recv_handler;
	ib_mad_send_handler	send_handler;
	व्योम			*context;
	u32			hi_tid;
	u32			flags;
	व्योम			*security;
	काष्ठा list_head	mad_agent_sec_list;
	u8			port_num;
	u8			rmpp_version;
	bool			smp_allowed;
पूर्ण;

/**
 * ib_mad_send_wc - MAD send completion inक्रमmation.
 * @send_buf: Send MAD data buffer associated with the send MAD request.
 * @status: Completion status.
 * @venकरोr_err: Optional venकरोr error inक्रमmation वापसed with a failed
 *   request.
 */
काष्ठा ib_mad_send_wc अणु
	काष्ठा ib_mad_send_buf	*send_buf;
	क्रमागत ib_wc_status	status;
	u32			venकरोr_err;
पूर्ण;

/**
 * ib_mad_recv_buf - received MAD buffer inक्रमmation.
 * @list: Reference to next data buffer क्रम a received RMPP MAD.
 * @grh: References a data buffer containing the global route header.
 *   The data refereced by this buffer is only valid अगर the GRH is
 *   valid.
 * @mad: References the start of the received MAD.
 */
काष्ठा ib_mad_recv_buf अणु
	काष्ठा list_head	list;
	काष्ठा ib_grh		*grh;
	जोड़ अणु
		काष्ठा ib_mad	*mad;
		काष्ठा opa_mad	*opa_mad;
	पूर्ण;
पूर्ण;

/**
 * ib_mad_recv_wc - received MAD inक्रमmation.
 * @wc: Completion inक्रमmation क्रम the received data.
 * @recv_buf: Specअगरies the location of the received data buffer(s).
 * @rmpp_list: Specअगरies a list of RMPP reassembled received MAD buffers.
 * @mad_len: The length of the received MAD, without duplicated headers.
 * @mad_seg_size: The size of inभागidual MAD segments
 *
 * For received response, the wr_id contains a poपूर्णांकer to the ib_mad_send_buf
 *   क्रम the corresponding send request.
 */
काष्ठा ib_mad_recv_wc अणु
	काष्ठा ib_wc		*wc;
	काष्ठा ib_mad_recv_buf	recv_buf;
	काष्ठा list_head	rmpp_list;
	पूर्णांक			mad_len;
	माप_प्रकार			mad_seg_size;
पूर्ण;

/**
 * ib_mad_reg_req - MAD registration request
 * @mgmt_class: Indicates which management class of MADs should be receive
 *   by the caller.  This field is only required अगर the user wishes to
 *   receive unsolicited MADs, otherwise it should be 0.
 * @mgmt_class_version: Indicates which version of MADs क्रम the given
 *   management class to receive.
 * @oui: Indicates IEEE OUI when mgmt_class is a venकरोr class
 *   in the range from 0x30 to 0x4f. Otherwise not used.
 * @method_mask: The caller will receive unsolicited MADs क्रम any method
 *   where @method_mask = 1.
 *
 */
काष्ठा ib_mad_reg_req अणु
	u8	mgmt_class;
	u8	mgmt_class_version;
	u8	oui[3];
	DECLARE_BITMAP(method_mask, IB_MGMT_MAX_METHODS);
पूर्ण;

/**
 * ib_रेजिस्टर_mad_agent - Register to send/receive MADs.
 * @device: The device to रेजिस्टर with.
 * @port_num: The port on the specअगरied device to use.
 * @qp_type: Specअगरies which QP to access.  Must be either
 *   IB_QPT_SMI or IB_QPT_GSI.
 * @mad_reg_req: Specअगरies which unsolicited MADs should be received
 *   by the caller.  This parameter may be शून्य अगर the caller only
 *   wishes to receive solicited responses.
 * @rmpp_version: If set, indicates that the client will send
 *   and receive MADs that contain the RMPP header क्रम the given version.
 *   If set to 0, indicates that RMPP is not used by this client.
 * @send_handler: The completion callback routine invoked after a send
 *   request has completed.
 * @recv_handler: The completion callback routine invoked क्रम a received
 *   MAD.
 * @context: User specअगरied context associated with the registration.
 * @registration_flags: Registration flags to set क्रम this agent
 */
काष्ठा ib_mad_agent *ib_रेजिस्टर_mad_agent(काष्ठा ib_device *device,
					   u32 port_num,
					   क्रमागत ib_qp_type qp_type,
					   काष्ठा ib_mad_reg_req *mad_reg_req,
					   u8 rmpp_version,
					   ib_mad_send_handler send_handler,
					   ib_mad_recv_handler recv_handler,
					   व्योम *context,
					   u32 registration_flags);
/**
 * ib_unरेजिस्टर_mad_agent - Unरेजिस्टरs a client from using MAD services.
 * @mad_agent: Corresponding MAD registration request to deरेजिस्टर.
 *
 * After invoking this routine, MAD services are no दीर्घer usable by the
 * client on the associated QP.
 */
व्योम ib_unरेजिस्टर_mad_agent(काष्ठा ib_mad_agent *mad_agent);

/**
 * ib_post_send_mad - Posts MAD(s) to the send queue of the QP associated
 *   with the रेजिस्टरed client.
 * @send_buf: Specअगरies the inक्रमmation needed to send the MAD(s).
 * @bad_send_buf: Specअगरies the MAD on which an error was encountered.  This
 *   parameter is optional अगर only a single MAD is posted.
 *
 * Sent MADs are not guaranteed to complete in the order that they were posted.
 *
 * If the MAD requires RMPP, the data buffer should contain a single copy
 * of the common MAD, RMPP, and class specअगरic headers, followed by the class
 * defined data.  If the class defined data would not भागide evenly पूर्णांकo
 * RMPP segments, then space must be allocated at the end of the referenced
 * buffer क्रम any required padding.  To indicate the amount of class defined
 * data being transferred, the paylen_newwin field in the RMPP header should
 * be set to the size of the class specअगरic header plus the amount of class
 * defined data being transferred.  The paylen_newwin field should be
 * specअगरied in network-byte order.
 */
पूर्णांक ib_post_send_mad(काष्ठा ib_mad_send_buf *send_buf,
		     काष्ठा ib_mad_send_buf **bad_send_buf);


/**
 * ib_मुक्त_recv_mad - Returns data buffers used to receive a MAD.
 * @mad_recv_wc: Work completion inक्रमmation क्रम a received MAD.
 *
 * Clients receiving MADs through their ib_mad_recv_handler must call this
 * routine to वापस the work completion buffers to the access layer.
 */
व्योम ib_मुक्त_recv_mad(काष्ठा ib_mad_recv_wc *mad_recv_wc);

/**
 * ib_cancel_mad - Cancels an outstanding send MAD operation.
 * @mad_agent: Specअगरies the registration associated with sent MAD.
 * @send_buf: Indicates the MAD to cancel.
 *
 * MADs will be वापसed to the user through the corresponding
 * ib_mad_send_handler.
 */
व्योम ib_cancel_mad(काष्ठा ib_mad_agent *mad_agent,
		   काष्ठा ib_mad_send_buf *send_buf);

/**
 * ib_modअगरy_mad - Modअगरies an outstanding send MAD operation.
 * @mad_agent: Specअगरies the registration associated with sent MAD.
 * @send_buf: Indicates the MAD to modअगरy.
 * @समयout_ms: New समयout value क्रम sent MAD.
 *
 * This call will reset the समयout value क्रम a sent MAD to the specअगरied
 * value.
 */
पूर्णांक ib_modअगरy_mad(काष्ठा ib_mad_agent *mad_agent,
		  काष्ठा ib_mad_send_buf *send_buf, u32 समयout_ms);

/**
 * ib_create_send_mad - Allocate and initialize a data buffer and work request
 *   क्रम sending a MAD.
 * @mad_agent: Specअगरies the रेजिस्टरed MAD service to associate with the MAD.
 * @remote_qpn: Specअगरies the QPN of the receiving node.
 * @pkey_index: Specअगरies which PKey the MAD will be sent using.  This field
 *   is valid only अगर the remote_qpn is QP 1.
 * @rmpp_active: Indicates अगर the send will enable RMPP.
 * @hdr_len: Indicates the size of the data header of the MAD.  This length
 *   should include the common MAD header, RMPP header, plus any class
 *   specअगरic header.
 * @data_len: Indicates the size of any user-transferred data.  The call will
 *   स्वतःmatically adjust the allocated buffer size to account क्रम any
 *   additional padding that may be necessary.
 * @gfp_mask: GFP mask used क्रम the memory allocation.
 * @base_version: Base Version of this MAD
 *
 * This routine allocates a MAD क्रम sending.  The वापसed MAD send buffer
 * will reference a data buffer usable क्रम sending a MAD, aदीर्घ
 * with an initialized work request काष्ठाure.  Users may modअगरy the वापसed
 * MAD data buffer beक्रमe posting the send.
 *
 * The वापसed MAD header, class specअगरic headers, and any padding will be
 * cleared.  Users are responsible क्रम initializing the common MAD header,
 * any class specअगरic header, and MAD data area.
 * If @rmpp_active is set, the RMPP header will be initialized क्रम sending.
 */
काष्ठा ib_mad_send_buf *ib_create_send_mad(काष्ठा ib_mad_agent *mad_agent,
					   u32 remote_qpn, u16 pkey_index,
					   पूर्णांक rmpp_active,
					   पूर्णांक hdr_len, पूर्णांक data_len,
					   gfp_t gfp_mask,
					   u8 base_version);

/**
 * ib_is_mad_class_rmpp - वापसs whether given management class
 * supports RMPP.
 * @mgmt_class: management class
 *
 * This routine वापसs whether the management class supports RMPP.
 */
पूर्णांक ib_is_mad_class_rmpp(u8 mgmt_class);

/**
 * ib_get_mad_data_offset - वापसs the data offset क्रम a given
 * management class.
 * @mgmt_class: management class
 *
 * This routine वापसs the data offset in the MAD क्रम the management
 * class requested.
 */
पूर्णांक ib_get_mad_data_offset(u8 mgmt_class);

/**
 * ib_get_rmpp_segment - वापसs the data buffer क्रम a given RMPP segment.
 * @send_buf: Previously allocated send data buffer.
 * @seg_num: number of segment to वापस
 *
 * This routine वापसs a poपूर्णांकer to the data buffer of an RMPP MAD.
 * Users must provide synchronization to @send_buf around this call.
 */
व्योम *ib_get_rmpp_segment(काष्ठा ib_mad_send_buf *send_buf, पूर्णांक seg_num);

/**
 * ib_मुक्त_send_mad - Returns data buffers used to send a MAD.
 * @send_buf: Previously allocated send data buffer.
 */
व्योम ib_मुक्त_send_mad(काष्ठा ib_mad_send_buf *send_buf);

/**
 * ib_mad_kernel_rmpp_agent - Returns अगर the agent is perक्रमming RMPP.
 * @agent: the agent in question
 * @वापस: true अगर agent is perक्रमming rmpp, false otherwise.
 */
पूर्णांक ib_mad_kernel_rmpp_agent(स्थिर काष्ठा ib_mad_agent *agent);

#पूर्ण_अगर /* IB_MAD_H */
