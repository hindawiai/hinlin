<शैली गुरु>
/*
 * Copyright (c) 2013-2015, Mellanox Technologies. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#अगर_अघोषित MLX5_QP_H
#घोषणा MLX5_QP_H

#समावेश <linux/mlx5/device.h>
#समावेश <linux/mlx5/driver.h>

#घोषणा MLX5_INVALID_LKEY	0x100
/* UMR (3 WQE_BB's) + SIG (3 WQE_BB's) + PSV (mem) + PSV (wire) */
#घोषणा MLX5_SIG_WQE_SIZE	(MLX5_SEND_WQE_BB * 8)
#घोषणा MLX5_DIF_SIZE		8
#घोषणा MLX5_STRIDE_BLOCK_OP	0x400
#घोषणा MLX5_CPY_GRD_MASK	0xc0
#घोषणा MLX5_CPY_APP_MASK	0x30
#घोषणा MLX5_CPY_REF_MASK	0x0f
#घोषणा MLX5_BSF_INC_REFTAG	(1 << 6)
#घोषणा MLX5_BSF_INL_VALID	(1 << 15)
#घोषणा MLX5_BSF_REFRESH_DIF	(1 << 14)
#घोषणा MLX5_BSF_REPEAT_BLOCK	(1 << 7)
#घोषणा MLX5_BSF_APPTAG_ESCAPE	0x1
#घोषणा MLX5_BSF_APPREF_ESCAPE	0x2

क्रमागत mlx5_qp_optpar अणु
	MLX5_QP_OPTPAR_ALT_ADDR_PATH		= 1 << 0,
	MLX5_QP_OPTPAR_RRE			= 1 << 1,
	MLX5_QP_OPTPAR_RAE			= 1 << 2,
	MLX5_QP_OPTPAR_RWE			= 1 << 3,
	MLX5_QP_OPTPAR_PKEY_INDEX		= 1 << 4,
	MLX5_QP_OPTPAR_Q_KEY			= 1 << 5,
	MLX5_QP_OPTPAR_RNR_TIMEOUT		= 1 << 6,
	MLX5_QP_OPTPAR_PRIMARY_ADDR_PATH	= 1 << 7,
	MLX5_QP_OPTPAR_SRA_MAX			= 1 << 8,
	MLX5_QP_OPTPAR_RRA_MAX			= 1 << 9,
	MLX5_QP_OPTPAR_PM_STATE			= 1 << 10,
	MLX5_QP_OPTPAR_RETRY_COUNT		= 1 << 12,
	MLX5_QP_OPTPAR_RNR_RETRY		= 1 << 13,
	MLX5_QP_OPTPAR_ACK_TIMEOUT		= 1 << 14,
	MLX5_QP_OPTPAR_LAG_TX_AFF		= 1 << 15,
	MLX5_QP_OPTPAR_PRI_PORT			= 1 << 16,
	MLX5_QP_OPTPAR_SRQN			= 1 << 18,
	MLX5_QP_OPTPAR_CQN_RCV			= 1 << 19,
	MLX5_QP_OPTPAR_DC_HS			= 1 << 20,
	MLX5_QP_OPTPAR_DC_KEY			= 1 << 21,
	MLX5_QP_OPTPAR_COUNTER_SET_ID		= 1 << 25,
पूर्ण;

क्रमागत mlx5_qp_state अणु
	MLX5_QP_STATE_RST			= 0,
	MLX5_QP_STATE_INIT			= 1,
	MLX5_QP_STATE_RTR			= 2,
	MLX5_QP_STATE_RTS			= 3,
	MLX5_QP_STATE_SQER			= 4,
	MLX5_QP_STATE_SQD			= 5,
	MLX5_QP_STATE_ERR			= 6,
	MLX5_QP_STATE_SQ_DRAINING		= 7,
	MLX5_QP_STATE_SUSPENDED			= 9,
	MLX5_QP_NUM_STATE,
	MLX5_QP_STATE,
	MLX5_QP_STATE_BAD,
पूर्ण;

क्रमागत अणु
	MLX5_SQ_STATE_NA	= MLX5_SQC_STATE_ERR + 1,
	MLX5_SQ_NUM_STATE	= MLX5_SQ_STATE_NA + 1,
	MLX5_RQ_STATE_NA	= MLX5_RQC_STATE_ERR + 1,
	MLX5_RQ_NUM_STATE	= MLX5_RQ_STATE_NA + 1,
पूर्ण;

क्रमागत अणु
	MLX5_QP_ST_RC				= 0x0,
	MLX5_QP_ST_UC				= 0x1,
	MLX5_QP_ST_UD				= 0x2,
	MLX5_QP_ST_XRC				= 0x3,
	MLX5_QP_ST_MLX				= 0x4,
	MLX5_QP_ST_DCI				= 0x5,
	MLX5_QP_ST_DCT				= 0x6,
	MLX5_QP_ST_QP0				= 0x7,
	MLX5_QP_ST_QP1				= 0x8,
	MLX5_QP_ST_RAW_ETHERTYPE		= 0x9,
	MLX5_QP_ST_RAW_IPV6			= 0xa,
	MLX5_QP_ST_SNIFFER			= 0xb,
	MLX5_QP_ST_SYNC_UMR			= 0xe,
	MLX5_QP_ST_PTP_1588			= 0xd,
	MLX5_QP_ST_REG_UMR			= 0xc,
	MLX5_QP_ST_MAX
पूर्ण;

क्रमागत अणु
	MLX5_QP_PM_MIGRATED			= 0x3,
	MLX5_QP_PM_ARMED			= 0x0,
	MLX5_QP_PM_REARM			= 0x1
पूर्ण;

क्रमागत अणु
	MLX5_NON_ZERO_RQ	= 0x0,
	MLX5_SRQ_RQ		= 0x1,
	MLX5_CRQ_RQ		= 0x2,
	MLX5_ZERO_LEN_RQ	= 0x3
पूर्ण;

/* TODO REM */
क्रमागत अणु
	/* params1 */
	MLX5_QP_BIT_SRE				= 1 << 15,
	MLX5_QP_BIT_SWE				= 1 << 14,
	MLX5_QP_BIT_SAE				= 1 << 13,
	/* params2 */
	MLX5_QP_BIT_RRE				= 1 << 15,
	MLX5_QP_BIT_RWE				= 1 << 14,
	MLX5_QP_BIT_RAE				= 1 << 13,
	MLX5_QP_BIT_RIC				= 1 <<	4,
	MLX5_QP_BIT_CC_SLAVE_RECV		= 1 <<  2,
	MLX5_QP_BIT_CC_SLAVE_SEND		= 1 <<  1,
	MLX5_QP_BIT_CC_MASTER			= 1 <<  0
पूर्ण;

क्रमागत अणु
	MLX5_WQE_CTRL_CQ_UPDATE		= 2 << 2,
	MLX5_WQE_CTRL_CQ_UPDATE_AND_EQE	= 3 << 2,
	MLX5_WQE_CTRL_SOLICITED		= 1 << 1,
पूर्ण;

क्रमागत अणु
	MLX5_SEND_WQE_DS	= 16,
	MLX5_SEND_WQE_BB	= 64,
पूर्ण;

#घोषणा MLX5_SEND_WQEBB_NUM_DS	(MLX5_SEND_WQE_BB / MLX5_SEND_WQE_DS)

क्रमागत अणु
	MLX5_SEND_WQE_MAX_WQEBBS	= 16,
पूर्ण;

क्रमागत अणु
	MLX5_WQE_FMR_PERM_LOCAL_READ	= 1 << 27,
	MLX5_WQE_FMR_PERM_LOCAL_WRITE	= 1 << 28,
	MLX5_WQE_FMR_PERM_REMOTE_READ	= 1 << 29,
	MLX5_WQE_FMR_PERM_REMOTE_WRITE	= 1 << 30,
	MLX5_WQE_FMR_PERM_ATOMIC	= 1 << 31
पूर्ण;

क्रमागत अणु
	MLX5_FENCE_MODE_NONE			= 0 << 5,
	MLX5_FENCE_MODE_INITIATOR_SMALL		= 1 << 5,
	MLX5_FENCE_MODE_FENCE			= 2 << 5,
	MLX5_FENCE_MODE_STRONG_ORDERING		= 3 << 5,
	MLX5_FENCE_MODE_SMALL_AND_FENCE		= 4 << 5,
पूर्ण;

क्रमागत अणु
	MLX5_RCV_DBR	= 0,
	MLX5_SND_DBR	= 1,
पूर्ण;

क्रमागत अणु
	MLX5_FLAGS_INLINE	= 1<<7,
	MLX5_FLAGS_CHECK_FREE   = 1<<5,
पूर्ण;

काष्ठा mlx5_wqe_fmr_seg अणु
	__be32			flags;
	__be32			mem_key;
	__be64			buf_list;
	__be64			start_addr;
	__be64			reg_len;
	__be32			offset;
	__be32			page_size;
	u32			reserved[2];
पूर्ण;

काष्ठा mlx5_wqe_ctrl_seg अणु
	__be32			opmod_idx_opcode;
	__be32			qpn_ds;
	u8			signature;
	u8			rsvd[2];
	u8			fm_ce_se;
	जोड़ अणु
		__be32		general_id;
		__be32		imm;
		__be32		umr_mkey;
		__be32		tis_tir_num;
	पूर्ण;
पूर्ण;

#घोषणा MLX5_WQE_CTRL_DS_MASK 0x3f
#घोषणा MLX5_WQE_CTRL_QPN_MASK 0xffffff00
#घोषणा MLX5_WQE_CTRL_QPN_SHIFT 8
#घोषणा MLX5_WQE_DS_UNITS 16
#घोषणा MLX5_WQE_CTRL_OPCODE_MASK 0xff
#घोषणा MLX5_WQE_CTRL_WQE_INDEX_MASK 0x00ffff00
#घोषणा MLX5_WQE_CTRL_WQE_INDEX_SHIFT 8

क्रमागत अणु
	MLX5_ETH_WQE_L3_INNER_CSUM      = 1 << 4,
	MLX5_ETH_WQE_L4_INNER_CSUM      = 1 << 5,
	MLX5_ETH_WQE_L3_CSUM            = 1 << 6,
	MLX5_ETH_WQE_L4_CSUM            = 1 << 7,
पूर्ण;

क्रमागत अणु
	MLX5_ETH_WQE_SVLAN              = 1 << 0,
	MLX5_ETH_WQE_TRAILER_HDR_OUTER_IP_ASSOC = 1 << 26,
	MLX5_ETH_WQE_TRAILER_HDR_OUTER_L4_ASSOC = 1 << 27,
	MLX5_ETH_WQE_TRAILER_HDR_INNER_IP_ASSOC = 3 << 26,
	MLX5_ETH_WQE_TRAILER_HDR_INNER_L4_ASSOC = 1 << 28,
	MLX5_ETH_WQE_INSERT_TRAILER     = 1 << 30,
	MLX5_ETH_WQE_INSERT_VLAN        = 1 << 15,
पूर्ण;

क्रमागत अणु
	MLX5_ETH_WQE_SWP_INNER_L3_IPV6  = 1 << 0,
	MLX5_ETH_WQE_SWP_INNER_L4_UDP   = 1 << 1,
	MLX5_ETH_WQE_SWP_OUTER_L3_IPV6  = 1 << 4,
	MLX5_ETH_WQE_SWP_OUTER_L4_UDP   = 1 << 5,
पूर्ण;

क्रमागत अणु
	MLX5_ETH_WQE_FT_META_IPSEC = BIT(0),
पूर्ण;

काष्ठा mlx5_wqe_eth_seg अणु
	u8              swp_outer_l4_offset;
	u8              swp_outer_l3_offset;
	u8              swp_inner_l4_offset;
	u8              swp_inner_l3_offset;
	u8              cs_flags;
	u8              swp_flags;
	__be16          mss;
	__be32          flow_table_metadata;
	जोड़ अणु
		काष्ठा अणु
			__be16 sz;
			u8     start[2];
		पूर्ण अंतरभूत_hdr;
		काष्ठा अणु
			__be16 type;
			__be16 vlan_tci;
		पूर्ण insert;
		__be32 trailer;
	पूर्ण;
पूर्ण;

काष्ठा mlx5_wqe_xrc_seg अणु
	__be32			xrc_srqn;
	u8			rsvd[12];
पूर्ण;

काष्ठा mlx5_wqe_masked_atomic_seg अणु
	__be64			swap_add;
	__be64			compare;
	__be64			swap_add_mask;
	__be64			compare_mask;
पूर्ण;

काष्ठा mlx5_base_av अणु
	जोड़ अणु
		काष्ठा अणु
			__be32	qkey;
			__be32	reserved;
		पूर्ण qkey;
		__be64	dc_key;
	पूर्ण key;
	__be32	dqp_dct;
	u8	stat_rate_sl;
	u8	fl_mlid;
	जोड़ अणु
		__be16	rlid;
		__be16  udp_sport;
	पूर्ण;
पूर्ण;

काष्ठा mlx5_av अणु
	जोड़ अणु
		काष्ठा अणु
			__be32	qkey;
			__be32	reserved;
		पूर्ण qkey;
		__be64	dc_key;
	पूर्ण key;
	__be32	dqp_dct;
	u8	stat_rate_sl;
	u8	fl_mlid;
	जोड़ अणु
		__be16	rlid;
		__be16  udp_sport;
	पूर्ण;
	u8	reserved0[4];
	u8	rmac[6];
	u8	tclass;
	u8	hop_limit;
	__be32	grh_gid_fl;
	u8	rgid[16];
पूर्ण;

काष्ठा mlx5_ib_ah अणु
	काष्ठा ib_ah		ibah;
	काष्ठा mlx5_av		av;
	u8			xmit_port;
पूर्ण;

अटल अंतरभूत काष्ठा mlx5_ib_ah *to_mah(काष्ठा ib_ah *ibah)
अणु
	वापस container_of(ibah, काष्ठा mlx5_ib_ah, ibah);
पूर्ण

काष्ठा mlx5_wqe_datagram_seg अणु
	काष्ठा mlx5_av	av;
पूर्ण;

काष्ठा mlx5_wqe_raddr_seg अणु
	__be64			raddr;
	__be32			rkey;
	u32			reserved;
पूर्ण;

काष्ठा mlx5_wqe_atomic_seg अणु
	__be64			swap_add;
	__be64			compare;
पूर्ण;

काष्ठा mlx5_wqe_data_seg अणु
	__be32			byte_count;
	__be32			lkey;
	__be64			addr;
पूर्ण;

काष्ठा mlx5_wqe_umr_ctrl_seg अणु
	u8		flags;
	u8		rsvd0[3];
	__be16		xlt_octowords;
	जोड़ अणु
		__be16	xlt_offset;
		__be16	bsf_octowords;
	पूर्ण;
	__be64		mkey_mask;
	__be32		xlt_offset_47_16;
	u8		rsvd1[28];
पूर्ण;

काष्ठा mlx5_seg_set_psv अणु
	__be32		psv_num;
	__be16		syndrome;
	__be16		status;
	__be32		transient_sig;
	__be32		ref_tag;
पूर्ण;

काष्ठा mlx5_seg_get_psv अणु
	u8		rsvd[19];
	u8		num_psv;
	__be32		l_key;
	__be64		va;
	__be32		psv_index[4];
पूर्ण;

काष्ठा mlx5_seg_check_psv अणु
	u8		rsvd0[2];
	__be16		err_coalescing_op;
	u8		rsvd1[2];
	__be16		xport_err_op;
	u8		rsvd2[2];
	__be16		xport_err_mask;
	u8		rsvd3[7];
	u8		num_psv;
	__be32		l_key;
	__be64		va;
	__be32		psv_index[4];
पूर्ण;

काष्ठा mlx5_rwqe_sig अणु
	u8	rsvd0[4];
	u8	signature;
	u8	rsvd1[11];
पूर्ण;

काष्ठा mlx5_wqe_signature_seg अणु
	u8	rsvd0[4];
	u8	signature;
	u8	rsvd1[11];
पूर्ण;

#घोषणा MLX5_WQE_INLINE_SEG_BYTE_COUNT_MASK 0x3ff

काष्ठा mlx5_wqe_अंतरभूत_seg अणु
	__be32	byte_count;
	__be32	data[];
पूर्ण;

क्रमागत mlx5_sig_type अणु
	MLX5_DIF_CRC = 0x1,
	MLX5_DIF_IPCS = 0x2,
पूर्ण;

काष्ठा mlx5_bsf_inl अणु
	__be16		vld_refresh;
	__be16		dअगर_apptag;
	__be32		dअगर_reftag;
	u8		sig_type;
	u8		rp_inv_seed;
	u8		rsvd[3];
	u8		dअगर_inc_ref_guard_check;
	__be16		dअगर_app_biपंचांगask_check;
पूर्ण;

काष्ठा mlx5_bsf अणु
	काष्ठा mlx5_bsf_basic अणु
		u8		bsf_size_sbs;
		u8		check_byte_mask;
		जोड़ अणु
			u8	copy_byte_mask;
			u8	bs_selector;
			u8	rsvd_wflags;
		पूर्ण wire;
		जोड़ अणु
			u8	bs_selector;
			u8	rsvd_mflags;
		पूर्ण mem;
		__be32		raw_data_size;
		__be32		w_bfs_psv;
		__be32		m_bfs_psv;
	पूर्ण basic;
	काष्ठा mlx5_bsf_ext अणु
		__be32		t_init_gen_pro_size;
		__be32		rsvd_epi_size;
		__be32		w_tfs_psv;
		__be32		m_tfs_psv;
	पूर्ण ext;
	काष्ठा mlx5_bsf_inl	w_inl;
	काष्ठा mlx5_bsf_inl	m_inl;
पूर्ण;

काष्ठा mlx5_mtt अणु
	__be64		ptag;
पूर्ण;

काष्ठा mlx5_klm अणु
	__be32		bcount;
	__be32		key;
	__be64		va;
पूर्ण;

काष्ठा mlx5_stride_block_entry अणु
	__be16		stride;
	__be16		bcount;
	__be32		key;
	__be64		va;
पूर्ण;

काष्ठा mlx5_stride_block_ctrl_seg अणु
	__be32		bcount_per_cycle;
	__be32		op;
	__be32		repeat_count;
	u16		rsvd;
	__be16		num_entries;
पूर्ण;

काष्ठा mlx5_core_qp अणु
	काष्ठा mlx5_core_rsc_common	common; /* must be first */
	व्योम (*event)		(काष्ठा mlx5_core_qp *, पूर्णांक);
	पूर्णांक			qpn;
	काष्ठा mlx5_rsc_debug	*dbg;
	पूर्णांक			pid;
	u16			uid;
पूर्ण;

काष्ठा mlx5_core_dct अणु
	काष्ठा mlx5_core_qp	mqp;
	काष्ठा completion	drained;
पूर्ण;

पूर्णांक mlx5_debug_qp_add(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_core_qp *qp);
व्योम mlx5_debug_qp_हटाओ(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_core_qp *qp);

अटल अंतरभूत स्थिर अक्षर *mlx5_qp_type_str(पूर्णांक type)
अणु
	चयन (type) अणु
	हाल MLX5_QP_ST_RC: वापस "RC";
	हाल MLX5_QP_ST_UC: वापस "C";
	हाल MLX5_QP_ST_UD: वापस "UD";
	हाल MLX5_QP_ST_XRC: वापस "XRC";
	हाल MLX5_QP_ST_MLX: वापस "MLX";
	हाल MLX5_QP_ST_QP0: वापस "QP0";
	हाल MLX5_QP_ST_QP1: वापस "QP1";
	हाल MLX5_QP_ST_RAW_ETHERTYPE: वापस "RAW_ETHERTYPE";
	हाल MLX5_QP_ST_RAW_IPV6: वापस "RAW_IPV6";
	हाल MLX5_QP_ST_SNIFFER: वापस "SNIFFER";
	हाल MLX5_QP_ST_SYNC_UMR: वापस "SYNC_UMR";
	हाल MLX5_QP_ST_PTP_1588: वापस "PTP_1588";
	हाल MLX5_QP_ST_REG_UMR: वापस "REG_UMR";
	शेष: वापस "Invalid transport type";
	पूर्ण
पूर्ण

अटल अंतरभूत स्थिर अक्षर *mlx5_qp_state_str(पूर्णांक state)
अणु
	चयन (state) अणु
	हाल MLX5_QP_STATE_RST:
	वापस "RST";
	हाल MLX5_QP_STATE_INIT:
	वापस "INIT";
	हाल MLX5_QP_STATE_RTR:
	वापस "RTR";
	हाल MLX5_QP_STATE_RTS:
	वापस "RTS";
	हाल MLX5_QP_STATE_SQER:
	वापस "SQER";
	हाल MLX5_QP_STATE_SQD:
	वापस "SQD";
	हाल MLX5_QP_STATE_ERR:
	वापस "ERR";
	हाल MLX5_QP_STATE_SQ_DRAINING:
	वापस "SQ_DRAINING";
	हाल MLX5_QP_STATE_SUSPENDED:
	वापस "SUSPENDED";
	शेष: वापस "Invalid QP state";
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक mlx5_get_qp_शेष_ts(काष्ठा mlx5_core_dev *dev)
अणु
	वापस !MLX5_CAP_ROCE(dev, qp_ts_क्रमmat) ?
		       MLX5_QPC_TIMESTAMP_FORMAT_FREE_RUNNING :
		       MLX5_QPC_TIMESTAMP_FORMAT_DEFAULT;
पूर्ण

#पूर्ण_अगर /* MLX5_QP_H */
