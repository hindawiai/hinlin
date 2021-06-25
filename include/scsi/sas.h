<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * SAS काष्ठाures and definitions header file
 *
 * Copyright (C) 2005 Adaptec, Inc.  All rights reserved.
 * Copyright (C) 2005 Luben Tuikov <luben_tuikov@adaptec.com>
 */

#अगर_अघोषित _SAS_H_
#घोषणा _SAS_H_

#समावेश <linux/types.h>
#समावेश <यंत्र/byteorder.h>

#घोषणा SAS_ADDR_SIZE        8
#घोषणा HASHED_SAS_ADDR_SIZE 3
#घोषणा SAS_ADDR(_sa) ((अचिन्हित दीर्घ दीर्घ) be64_to_cpu(*(__be64 *)(_sa)))

#घोषणा SMP_REQUEST             0x40
#घोषणा SMP_RESPONSE            0x41

#घोषणा SSP_DATA                0x01
#घोषणा SSP_XFER_RDY            0x05
#घोषणा SSP_COMMAND             0x06
#घोषणा SSP_RESPONSE            0x07
#घोषणा SSP_TASK                0x16

#घोषणा SMP_REPORT_GENERAL       0x00
#घोषणा SMP_REPORT_MANUF_INFO    0x01
#घोषणा SMP_READ_GPIO_REG        0x02
#घोषणा SMP_DISCOVER             0x10
#घोषणा SMP_REPORT_PHY_ERR_LOG   0x11
#घोषणा SMP_REPORT_PHY_SATA      0x12
#घोषणा SMP_REPORT_ROUTE_INFO    0x13
#घोषणा SMP_WRITE_GPIO_REG       0x82
#घोषणा SMP_CONF_ROUTE_INFO      0x90
#घोषणा SMP_PHY_CONTROL          0x91
#घोषणा SMP_PHY_TEST_FUNCTION    0x92

#घोषणा SMP_RESP_FUNC_ACC        0x00
#घोषणा SMP_RESP_FUNC_UNK        0x01
#घोषणा SMP_RESP_FUNC_FAILED     0x02
#घोषणा SMP_RESP_INV_FRM_LEN     0x03
#घोषणा SMP_RESP_NO_PHY          0x10
#घोषणा SMP_RESP_NO_INDEX        0x11
#घोषणा SMP_RESP_PHY_NO_SATA     0x12
#घोषणा SMP_RESP_PHY_UNK_OP      0x13
#घोषणा SMP_RESP_PHY_UNK_TESTF   0x14
#घोषणा SMP_RESP_PHY_TEST_INPROG 0x15
#घोषणा SMP_RESP_PHY_VACANT      0x16

/* SAM TMFs */
#घोषणा TMF_ABORT_TASK      0x01
#घोषणा TMF_ABORT_TASK_SET  0x02
#घोषणा TMF_CLEAR_TASK_SET  0x04
#घोषणा TMF_LU_RESET        0x08
#घोषणा TMF_CLEAR_ACA       0x40
#घोषणा TMF_QUERY_TASK      0x80

/* SAS TMF responses */
#घोषणा TMF_RESP_FUNC_COMPLETE   0x00
#घोषणा TMF_RESP_INVALID_FRAME   0x02
#घोषणा TMF_RESP_FUNC_ESUPP      0x04
#घोषणा TMF_RESP_FUNC_FAILED     0x05
#घोषणा TMF_RESP_FUNC_SUCC       0x08
#घोषणा TMF_RESP_NO_LUN          0x09
#घोषणा TMF_RESP_OVERLAPPED_TAG  0x0A

क्रमागत sas_oob_mode अणु
	OOB_NOT_CONNECTED,
	SATA_OOB_MODE,
	SAS_OOB_MODE
पूर्ण;

/* See sas_discover.c अगर you plan on changing these */
क्रमागत sas_device_type अणु
	/* these are SAS protocol defined (attached device type field) */
	SAS_PHY_UNUSED = 0,
	SAS_END_DEVICE = 1,
	SAS_EDGE_EXPANDER_DEVICE = 2,
	SAS_FANOUT_EXPANDER_DEVICE = 3,
	/* these are पूर्णांकernal to libsas */
	SAS_HA = 4,
	SAS_SATA_DEV = 5,
	SAS_SATA_PM = 7,
	SAS_SATA_PM_PORT = 8,
	SAS_SATA_PENDING = 9,
पूर्ण;

क्रमागत sas_protocol अणु
	SAS_PROTOCOL_NONE		= 0,
	SAS_PROTOCOL_SATA		= 0x01,
	SAS_PROTOCOL_SMP		= 0x02,
	SAS_PROTOCOL_STP		= 0x04,
	SAS_PROTOCOL_SSP		= 0x08,
	SAS_PROTOCOL_ALL		= 0x0E,
	SAS_PROTOCOL_STP_ALL		= SAS_PROTOCOL_STP|SAS_PROTOCOL_SATA,
पूर्ण;

/* From the spec; local phys only */
क्रमागत phy_func अणु
	PHY_FUNC_NOP,
	PHY_FUNC_LINK_RESET,		  /* Enables the phy */
	PHY_FUNC_HARD_RESET,
	PHY_FUNC_DISABLE,
	PHY_FUNC_CLEAR_ERROR_LOG = 5,
	PHY_FUNC_CLEAR_AFFIL,
	PHY_FUNC_TX_SATA_PS_SIGNAL,
	PHY_FUNC_RELEASE_SPINUP_HOLD = 0x10, /* LOCAL PORT ONLY! */
	PHY_FUNC_SET_LINK_RATE,
	PHY_FUNC_GET_EVENTS,
पूर्ण;

/* SAS LLDD would need to report only _very_few_ of those, like BROADCAST.
 * Most of those are here क्रम completeness.
 */
क्रमागत sas_prim अणु
	SAS_PRIM_AIP_NORMAL = 1,
	SAS_PRIM_AIP_R0     = 2,
	SAS_PRIM_AIP_R1     = 3,
	SAS_PRIM_AIP_R2     = 4,
	SAS_PRIM_AIP_WC     = 5,
	SAS_PRIM_AIP_WD     = 6,
	SAS_PRIM_AIP_WP     = 7,
	SAS_PRIM_AIP_RWP    = 8,

	SAS_PRIM_BC_CH      = 9,
	SAS_PRIM_BC_RCH0    = 10,
	SAS_PRIM_BC_RCH1    = 11,
	SAS_PRIM_BC_R0      = 12,
	SAS_PRIM_BC_R1      = 13,
	SAS_PRIM_BC_R2      = 14,
	SAS_PRIM_BC_R3      = 15,
	SAS_PRIM_BC_R4      = 16,

	SAS_PRIM_NOTIFY_ENSP= 17,
	SAS_PRIM_NOTIFY_R0  = 18,
	SAS_PRIM_NOTIFY_R1  = 19,
	SAS_PRIM_NOTIFY_R2  = 20,

	SAS_PRIM_CLOSE_CLAF = 21,
	SAS_PRIM_CLOSE_NORM = 22,
	SAS_PRIM_CLOSE_R0   = 23,
	SAS_PRIM_CLOSE_R1   = 24,

	SAS_PRIM_OPEN_RTRY  = 25,
	SAS_PRIM_OPEN_RJCT  = 26,
	SAS_PRIM_OPEN_ACPT  = 27,

	SAS_PRIM_DONE       = 28,
	SAS_PRIM_BREAK      = 29,

	SATA_PRIM_DMAT      = 33,
	SATA_PRIM_PMNAK     = 34,
	SATA_PRIM_PMACK     = 35,
	SATA_PRIM_PMREQ_S   = 36,
	SATA_PRIM_PMREQ_P   = 37,
	SATA_SATA_R_ERR     = 38,
पूर्ण;

क्रमागत sas_खोलो_rej_reason अणु
	/* Abanकरोn खोलो */
	SAS_OREJ_UNKNOWN   = 0,
	SAS_OREJ_BAD_DEST  = 1,
	SAS_OREJ_CONN_RATE = 2,
	SAS_OREJ_EPROTO    = 3,
	SAS_OREJ_RESV_AB0  = 4,
	SAS_OREJ_RESV_AB1  = 5,
	SAS_OREJ_RESV_AB2  = 6,
	SAS_OREJ_RESV_AB3  = 7,
	SAS_OREJ_WRONG_DEST= 8,
	SAS_OREJ_STP_NORES = 9,

	/* Retry खोलो */
	SAS_OREJ_NO_DEST   = 10,
	SAS_OREJ_PATH_BLOCKED = 11,
	SAS_OREJ_RSVD_CONT0 = 12,
	SAS_OREJ_RSVD_CONT1 = 13,
	SAS_OREJ_RSVD_INIT0 = 14,
	SAS_OREJ_RSVD_INIT1 = 15,
	SAS_OREJ_RSVD_STOP0 = 16,
	SAS_OREJ_RSVD_STOP1 = 17,
	SAS_OREJ_RSVD_RETRY = 18,
पूर्ण;

क्रमागत sas_gpio_reg_type अणु
	SAS_GPIO_REG_CFG   = 0,
	SAS_GPIO_REG_RX    = 1,
	SAS_GPIO_REG_RX_GP = 2,
	SAS_GPIO_REG_TX    = 3,
	SAS_GPIO_REG_TX_GP = 4,
पूर्ण;

काष्ठा  dev_to_host_fis अणु
	u8     fis_type;	  /* 0x34 */
	u8     flags;
	u8     status;
	u8     error;

	u8     lbal;
	जोड़ अणु u8 lbam; u8 byte_count_low; पूर्ण;
	जोड़ अणु u8 lbah; u8 byte_count_high; पूर्ण;
	u8     device;

	u8     lbal_exp;
	u8     lbam_exp;
	u8     lbah_exp;
	u8     _r_a;

	जोड़ अणु u8  sector_count; u8 पूर्णांकerrupt_reason; पूर्ण;
	u8     sector_count_exp;
	u8     _r_b;
	u8     _r_c;

	u32    _r_d;
पूर्ण __attribute__ ((packed));

काष्ठा host_to_dev_fis अणु
	u8     fis_type;	  /* 0x27 */
	u8     flags;
	u8     command;
	u8     features;

	u8     lbal;
	जोड़ अणु u8 lbam; u8 byte_count_low; पूर्ण;
	जोड़ अणु u8 lbah; u8 byte_count_high; पूर्ण;
	u8     device;

	u8     lbal_exp;
	u8     lbam_exp;
	u8     lbah_exp;
	u8     features_exp;

	जोड़ अणु u8  sector_count; u8 पूर्णांकerrupt_reason; पूर्ण;
	u8     sector_count_exp;
	u8     _r_a;
	u8     control;

	u32    _r_b;
पूर्ण __attribute__ ((packed));

/* Prefer to have code clarity over header file clarity.
 */
#अगर_घोषित __LITTLE_ENDIAN_BITFIELD
काष्ठा sas_identअगरy_frame अणु
	/* Byte 0 */
	u8  frame_type:4;
	u8  dev_type:3;
	u8  _un0:1;

	/* Byte 1 */
	u8  _un1;

	/* Byte 2 */
	जोड़ अणु
		काष्ठा अणु
			u8  _un20:1;
			u8  smp_iport:1;
			u8  stp_iport:1;
			u8  ssp_iport:1;
			u8  _un247:4;
		पूर्ण;
		u8 initiator_bits;
	पूर्ण;

	/* Byte 3 */
	जोड़ अणु
		काष्ठा अणु
			u8  _un30:1;
			u8 smp_tport:1;
			u8 stp_tport:1;
			u8 ssp_tport:1;
			u8 _un347:4;
		पूर्ण;
		u8 target_bits;
	पूर्ण;

	/* Byte 4 - 11 */
	u8 _un4_11[8];

	/* Byte 12 - 19 */
	u8 sas_addr[SAS_ADDR_SIZE];

	/* Byte 20 */
	u8 phy_id;

	u8 _un21_27[7];

	__be32 crc;
पूर्ण __attribute__ ((packed));

काष्ठा ssp_frame_hdr अणु
	u8     frame_type;
	u8     hashed_dest_addr[HASHED_SAS_ADDR_SIZE];
	u8     _r_a;
	u8     hashed_src_addr[HASHED_SAS_ADDR_SIZE];
	__be16 _r_b;

	u8     changing_data_ptr:1;
	u8     retransmit:1;
	u8     retry_data_frames:1;
	u8     _r_c:5;

	u8     num_fill_bytes:2;
	u8     _r_d:6;

	u32    _r_e;
	__be16 tag;
	__be16 tptt;
	__be32 data_offs;
पूर्ण __attribute__ ((packed));

काष्ठा ssp_response_iu अणु
	u8     _r_a[10];

	u8     datapres:2;
	u8     _r_b:6;

	u8     status;

	u32    _r_c;

	__be32 sense_data_len;
	__be32 response_data_len;

	u8     resp_data[0];
	u8     sense_data[];
पूर्ण __attribute__ ((packed));

काष्ठा ssp_command_iu अणु
	u8     lun[8];
	u8     _r_a;

	जोड़ अणु
		काष्ठा अणु
			u8  attr:3;
			u8  prio:4;
			u8  efb:1;
		पूर्ण;
		u8 efb_prio_attr;
	पूर्ण;

	u8    _r_b;

	u8    _r_c:2;
	u8    add_cdb_len:6;

	u8    cdb[16];
	u8    add_cdb[];
पूर्ण __attribute__ ((packed));

काष्ठा xfer_rdy_iu अणु
	__be32 requested_offset;
	__be32 ग_लिखो_data_len;
	__be32 _r_a;
पूर्ण __attribute__ ((packed));

काष्ठा ssp_पंचांगf_iu अणु
	u8     lun[8];
	u16    _r_a;
	u8     पंचांगf;
	u8     _r_b;
	__be16 tag;
	u8     _r_c[14];
पूर्ण __attribute__ ((packed));

/* ---------- SMP ---------- */

काष्ठा report_general_resp अणु
	__be16  change_count;
	__be16  route_indexes;
	u8      _r_a;
	u8      num_phys;

	u8      conf_route_table:1;
	u8      configuring:1;
	u8	config_others:1;
	u8	orej_retry_supp:1;
	u8	stp_cont_awt:1;
	u8	self_config:1;
	u8	zone_config:1;
	u8	t2t_supp:1;

	u8      _r_c;

	u8      enclosure_logical_id[8];

	u8      _r_d[12];
पूर्ण __attribute__ ((packed));

काष्ठा discover_resp अणु
	u8    _r_a[5];

	u8    phy_id;
	__be16 _r_b;

	u8    _r_c:4;
	u8    attached_dev_type:3;
	u8    _r_d:1;

	u8    linkrate:4;
	u8    _r_e:4;

	u8    attached_sata_host:1;
	u8    iproto:3;
	u8    _r_f:4;

	u8    attached_sata_dev:1;
	u8    tproto:3;
	u8    _r_g:3;
	u8    attached_sata_ps:1;

	u8    sas_addr[8];
	u8    attached_sas_addr[8];
	u8    attached_phy_id;

	u8    _r_h[7];

	u8    hmin_linkrate:4;
	u8    pmin_linkrate:4;
	u8    hmax_linkrate:4;
	u8    pmax_linkrate:4;

	u8    change_count;

	u8    pptv:4;
	u8    _r_i:3;
	u8    भव:1;

	u8    routing_attr:4;
	u8    _r_j:4;

	u8    conn_type;
	u8    conn_el_index;
	u8    conn_phy_link;

	u8    _r_k[8];
पूर्ण __attribute__ ((packed));

काष्ठा report_phy_sata_resp अणु
	u8    _r_a[5];

	u8    phy_id;
	u8    _r_b;

	u8    affil_valid:1;
	u8    affil_supp:1;
	u8    _r_c:6;

	u32    _r_d;

	u8    stp_sas_addr[8];

	काष्ठा dev_to_host_fis fis;

	u32   _r_e;

	u8    affil_stp_ini_addr[8];

	__be32 crc;
पूर्ण __attribute__ ((packed));

काष्ठा smp_resp अणु
	u8    frame_type;
	u8    function;
	u8    result;
	u8    reserved;
	जोड़ अणु
		काष्ठा report_general_resp  rg;
		काष्ठा discover_resp        disc;
		काष्ठा report_phy_sata_resp rps;
	पूर्ण;
पूर्ण __attribute__ ((packed));

#या_अगर defined(__BIG_ENDIAN_BITFIELD)
काष्ठा sas_identअगरy_frame अणु
	/* Byte 0 */
	u8  _un0:1;
	u8  dev_type:3;
	u8  frame_type:4;

	/* Byte 1 */
	u8  _un1;

	/* Byte 2 */
	जोड़ अणु
		काष्ठा अणु
			u8  _un247:4;
			u8  ssp_iport:1;
			u8  stp_iport:1;
			u8  smp_iport:1;
			u8  _un20:1;
		पूर्ण;
		u8 initiator_bits;
	पूर्ण;

	/* Byte 3 */
	जोड़ अणु
		काष्ठा अणु
			u8 _un347:4;
			u8 ssp_tport:1;
			u8 stp_tport:1;
			u8 smp_tport:1;
			u8 _un30:1;
		पूर्ण;
		u8 target_bits;
	पूर्ण;

	/* Byte 4 - 11 */
	u8 _un4_11[8];

	/* Byte 12 - 19 */
	u8 sas_addr[SAS_ADDR_SIZE];

	/* Byte 20 */
	u8 phy_id;

	u8 _un21_27[7];

	__be32 crc;
पूर्ण __attribute__ ((packed));

काष्ठा ssp_frame_hdr अणु
	u8     frame_type;
	u8     hashed_dest_addr[HASHED_SAS_ADDR_SIZE];
	u8     _r_a;
	u8     hashed_src_addr[HASHED_SAS_ADDR_SIZE];
	__be16 _r_b;

	u8     _r_c:5;
	u8     retry_data_frames:1;
	u8     retransmit:1;
	u8     changing_data_ptr:1;

	u8     _r_d:6;
	u8     num_fill_bytes:2;

	u32    _r_e;
	__be16 tag;
	__be16 tptt;
	__be32 data_offs;
पूर्ण __attribute__ ((packed));

काष्ठा ssp_response_iu अणु
	u8     _r_a[10];

	u8     _r_b:6;
	u8     datapres:2;

	u8     status;

	u32    _r_c;

	__be32 sense_data_len;
	__be32 response_data_len;

	u8     resp_data[0];
	u8     sense_data[];
पूर्ण __attribute__ ((packed));

काष्ठा ssp_command_iu अणु
	u8     lun[8];
	u8     _r_a;

	जोड़ अणु
		काष्ठा अणु
			u8  efb:1;
			u8  prio:4;
			u8  attr:3;
		पूर्ण;
		u8 efb_prio_attr;
	पूर्ण;

	u8    _r_b;

	u8    add_cdb_len:6;
	u8    _r_c:2;

	u8    cdb[16];
	u8    add_cdb[];
पूर्ण __attribute__ ((packed));

काष्ठा xfer_rdy_iu अणु
	__be32 requested_offset;
	__be32 ग_लिखो_data_len;
	__be32 _r_a;
पूर्ण __attribute__ ((packed));

काष्ठा ssp_पंचांगf_iu अणु
	u8     lun[8];
	u16    _r_a;
	u8     पंचांगf;
	u8     _r_b;
	__be16 tag;
	u8     _r_c[14];
पूर्ण __attribute__ ((packed));

/* ---------- SMP ---------- */

काष्ठा report_general_resp अणु
	__be16  change_count;
	__be16  route_indexes;
	u8      _r_a;
	u8      num_phys;

	u8	t2t_supp:1;
	u8	zone_config:1;
	u8	self_config:1;
	u8	stp_cont_awt:1;
	u8	orej_retry_supp:1;
	u8	config_others:1;
	u8      configuring:1;
	u8      conf_route_table:1;

	u8      _r_c;

	u8      enclosure_logical_id[8];

	u8      _r_d[12];
पूर्ण __attribute__ ((packed));

काष्ठा discover_resp अणु
	u8    _r_a[5];

	u8    phy_id;
	__be16 _r_b;

	u8    _r_d:1;
	u8    attached_dev_type:3;
	u8    _r_c:4;

	u8    _r_e:4;
	u8    linkrate:4;

	u8    _r_f:4;
	u8    iproto:3;
	u8    attached_sata_host:1;

	u8    attached_sata_ps:1;
	u8    _r_g:3;
	u8    tproto:3;
	u8    attached_sata_dev:1;

	u8    sas_addr[8];
	u8    attached_sas_addr[8];
	u8    attached_phy_id;

	u8    _r_h[7];

	u8    pmin_linkrate:4;
	u8    hmin_linkrate:4;
	u8    pmax_linkrate:4;
	u8    hmax_linkrate:4;

	u8    change_count;

	u8    भव:1;
	u8    _r_i:3;
	u8    pptv:4;

	u8    _r_j:4;
	u8    routing_attr:4;

	u8    conn_type;
	u8    conn_el_index;
	u8    conn_phy_link;

	u8    _r_k[8];
पूर्ण __attribute__ ((packed));

काष्ठा report_phy_sata_resp अणु
	u8    _r_a[5];

	u8    phy_id;
	u8    _r_b;

	u8    _r_c:6;
	u8    affil_supp:1;
	u8    affil_valid:1;

	u32   _r_d;

	u8    stp_sas_addr[8];

	काष्ठा dev_to_host_fis fis;

	u32   _r_e;

	u8    affil_stp_ini_addr[8];

	__be32 crc;
पूर्ण __attribute__ ((packed));

काष्ठा smp_resp अणु
	u8    frame_type;
	u8    function;
	u8    result;
	u8    reserved;
	जोड़ अणु
		काष्ठा report_general_resp  rg;
		काष्ठा discover_resp        disc;
		काष्ठा report_phy_sata_resp rps;
	पूर्ण;
पूर्ण __attribute__ ((packed));

#अन्यथा
#त्रुटि "Bitfield order not defined!"
#पूर्ण_अगर

#पूर्ण_अगर /* _SAS_H_ */
