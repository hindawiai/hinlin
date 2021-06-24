<शैली गुरु>
/*
 * Copyright (c) 2007 Cisco Systems, Inc.  All rights reserved.
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
 *	- Redistributions of source code must retain the above
 *	  copyright notice, this list of conditions and the following
 *	  disclaimer.
 *
 *	- Redistributions in binary क्रमm must reproduce the above
 *	  copyright notice, this list of conditions and the following
 *	  disclaimer in the करोcumentation and/or other materials
 *	  provided with the distribution.
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

#अगर_अघोषित MLX4_QP_H
#घोषणा MLX4_QP_H

#समावेश <linux/types.h>
#समावेश <linux/अगर_ether.h>

#समावेश <linux/mlx4/device.h>

#घोषणा MLX4_INVALID_LKEY	0x100

क्रमागत mlx4_qp_optpar अणु
	MLX4_QP_OPTPAR_ALT_ADDR_PATH		= 1 << 0,
	MLX4_QP_OPTPAR_RRE			= 1 << 1,
	MLX4_QP_OPTPAR_RAE			= 1 << 2,
	MLX4_QP_OPTPAR_RWE			= 1 << 3,
	MLX4_QP_OPTPAR_PKEY_INDEX		= 1 << 4,
	MLX4_QP_OPTPAR_Q_KEY			= 1 << 5,
	MLX4_QP_OPTPAR_RNR_TIMEOUT		= 1 << 6,
	MLX4_QP_OPTPAR_PRIMARY_ADDR_PATH	= 1 << 7,
	MLX4_QP_OPTPAR_SRA_MAX			= 1 << 8,
	MLX4_QP_OPTPAR_RRA_MAX			= 1 << 9,
	MLX4_QP_OPTPAR_PM_STATE			= 1 << 10,
	MLX4_QP_OPTPAR_RETRY_COUNT		= 1 << 12,
	MLX4_QP_OPTPAR_RNR_RETRY		= 1 << 13,
	MLX4_QP_OPTPAR_ACK_TIMEOUT		= 1 << 14,
	MLX4_QP_OPTPAR_SCHED_QUEUE		= 1 << 16,
	MLX4_QP_OPTPAR_COUNTER_INDEX		= 1 << 20,
	MLX4_QP_OPTPAR_VLAN_STRIPPING		= 1 << 21,
पूर्ण;

क्रमागत mlx4_qp_state अणु
	MLX4_QP_STATE_RST			= 0,
	MLX4_QP_STATE_INIT			= 1,
	MLX4_QP_STATE_RTR			= 2,
	MLX4_QP_STATE_RTS			= 3,
	MLX4_QP_STATE_SQER			= 4,
	MLX4_QP_STATE_SQD			= 5,
	MLX4_QP_STATE_ERR			= 6,
	MLX4_QP_STATE_SQ_DRAINING		= 7,
	MLX4_QP_NUM_STATE
पूर्ण;

क्रमागत अणु
	MLX4_QP_ST_RC				= 0x0,
	MLX4_QP_ST_UC				= 0x1,
	MLX4_QP_ST_RD				= 0x2,
	MLX4_QP_ST_UD				= 0x3,
	MLX4_QP_ST_XRC				= 0x6,
	MLX4_QP_ST_MLX				= 0x7
पूर्ण;

क्रमागत अणु
	MLX4_QP_PM_MIGRATED			= 0x3,
	MLX4_QP_PM_ARMED			= 0x0,
	MLX4_QP_PM_REARM			= 0x1
पूर्ण;

क्रमागत अणु
	/* params1 */
	MLX4_QP_BIT_SRE				= 1 << 15,
	MLX4_QP_BIT_SWE				= 1 << 14,
	MLX4_QP_BIT_SAE				= 1 << 13,
	/* params2 */
	MLX4_QP_BIT_RRE				= 1 << 15,
	MLX4_QP_BIT_RWE				= 1 << 14,
	MLX4_QP_BIT_RAE				= 1 << 13,
	MLX4_QP_BIT_FPP				= 1 <<	3,
	MLX4_QP_BIT_RIC				= 1 <<	4,
पूर्ण;

क्रमागत अणु
	MLX4_RSS_HASH_XOR			= 0,
	MLX4_RSS_HASH_TOP			= 1,

	MLX4_RSS_UDP_IPV6			= 1 << 0,
	MLX4_RSS_UDP_IPV4			= 1 << 1,
	MLX4_RSS_TCP_IPV6			= 1 << 2,
	MLX4_RSS_IPV6				= 1 << 3,
	MLX4_RSS_TCP_IPV4			= 1 << 4,
	MLX4_RSS_IPV4				= 1 << 5,

	MLX4_RSS_BY_OUTER_HEADERS		= 0 << 6,
	MLX4_RSS_BY_INNER_HEADERS		= 2 << 6,
	MLX4_RSS_BY_INNER_HEADERS_IPONLY	= 3 << 6,

	/* offset of mlx4_rss_context within mlx4_qp_context.pri_path */
	MLX4_RSS_OFFSET_IN_QPC_PRI_PATH		= 0x24,
	/* offset of being RSS indirection QP within mlx4_qp_context.flags */
	MLX4_RSS_QPC_FLAG_OFFSET		= 13,
पूर्ण;

#घोषणा MLX4_EN_RSS_KEY_SIZE 40

काष्ठा mlx4_rss_context अणु
	__be32			base_qpn;
	__be32			शेष_qpn;
	u16			reserved;
	u8			hash_fn;
	u8			flags;
	__be32			rss_key[MLX4_EN_RSS_KEY_SIZE / माप(__be32)];
	__be32			base_qpn_udp;
पूर्ण;

काष्ठा mlx4_qp_path अणु
	u8			fl;
	जोड़ अणु
		u8			vlan_control;
		u8			control;
	पूर्ण;
	u8			disable_pkey_check;
	u8			pkey_index;
	u8			counter_index;
	u8			grh_mylmc;
	__be16			rlid;
	u8			ackto;
	u8			mgid_index;
	u8			अटल_rate;
	u8			hop_limit;
	__be32			tclass_flowlabel;
	u8			rgid[16];
	u8			sched_queue;
	u8			vlan_index;
	u8			feup;
	u8			fvl_rx;
	u8			reserved4[2];
	u8			dmac[ETH_ALEN];
पूर्ण;

क्रमागत अणु /* fl */
	MLX4_FL_CV	= 1 << 6,
	MLX4_FL_SV	= 1 << 5,
	MLX4_FL_ETH_HIDE_CQE_VLAN	= 1 << 2,
	MLX4_FL_ETH_SRC_CHECK_MC_LB	= 1 << 1,
	MLX4_FL_ETH_SRC_CHECK_UC_LB	= 1 << 0,
पूर्ण;

क्रमागत अणु /* control */
	MLX4_CTRL_ETH_SRC_CHECK_IF_COUNTER	= 1 << 7,
पूर्ण;

क्रमागत अणु /* vlan_control */
	MLX4_VLAN_CTRL_ETH_TX_BLOCK_TAGGED	= 1 << 6,
	MLX4_VLAN_CTRL_ETH_TX_BLOCK_PRIO_TAGGED	= 1 << 5, /* 802.1p priority tag */
	MLX4_VLAN_CTRL_ETH_TX_BLOCK_UNTAGGED	= 1 << 4,
	MLX4_VLAN_CTRL_ETH_RX_BLOCK_TAGGED	= 1 << 2,
	MLX4_VLAN_CTRL_ETH_RX_BLOCK_PRIO_TAGGED	= 1 << 1, /* 802.1p priority tag */
	MLX4_VLAN_CTRL_ETH_RX_BLOCK_UNTAGGED	= 1 << 0
पूर्ण;

क्रमागत अणु /* feup */
	MLX4_FEUP_FORCE_ETH_UP          = 1 << 6, /* क्रमce Eth UP */
	MLX4_FSM_FORCE_ETH_SRC_MAC      = 1 << 5, /* क्रमce Source MAC */
	MLX4_FVL_FORCE_ETH_VLAN         = 1 << 3  /* क्रमce Eth vlan */
पूर्ण;

क्रमागत अणु /* fvl_rx */
	MLX4_FVL_RX_FORCE_ETH_VLAN      = 1 << 0 /* enक्रमce Eth rx vlan */
पूर्ण;

काष्ठा mlx4_qp_context अणु
	__be32			flags;
	__be32			pd;
	u8			mtu_msgmax;
	u8			rq_size_stride;
	u8			sq_size_stride;
	u8			rlkey_roce_mode;
	__be32			usr_page;
	__be32			local_qpn;
	__be32			remote_qpn;
	काष्ठा			mlx4_qp_path pri_path;
	काष्ठा			mlx4_qp_path alt_path;
	__be32			params1;
	u32			reserved1;
	__be32			next_send_psn;
	__be32			cqn_send;
	__be16                  roce_entropy;
	__be16                  reserved2[3];
	__be32			last_acked_psn;
	__be32			ssn;
	__be32			params2;
	__be32			rnr_nextrecvpsn;
	__be32			xrcd;
	__be32			cqn_recv;
	__be64			db_rec_addr;
	__be32			qkey;
	__be32			srqn;
	__be32			msn;
	__be16			rq_wqe_counter;
	__be16			sq_wqe_counter;
	u32			reserved3;
	__be16			rate_limit_params;
	u8			reserved4;
	u8			qos_vport;
	__be32			param3;
	__be32			nummmcpeers_basemkey;
	u8			log_page_size;
	u8			reserved5[2];
	u8			mtt_base_addr_h;
	__be32			mtt_base_addr_l;
	u32			reserved6[10];
पूर्ण;

काष्ठा mlx4_update_qp_context अणु
	__be64			qp_mask;
	__be64			primary_addr_path_mask;
	__be64			secondary_addr_path_mask;
	u64			reserved1;
	काष्ठा mlx4_qp_context	qp_context;
	u64			reserved2[58];
पूर्ण;

क्रमागत अणु
	MLX4_UPD_QP_MASK_PM_STATE	= 32,
	MLX4_UPD_QP_MASK_VSD		= 33,
	MLX4_UPD_QP_MASK_QOS_VPP	= 34,
	MLX4_UPD_QP_MASK_RATE_LIMIT	= 35,
पूर्ण;

क्रमागत अणु
	MLX4_UPD_QP_PATH_MASK_PKEY_INDEX		= 0 + 32,
	MLX4_UPD_QP_PATH_MASK_FSM			= 1 + 32,
	MLX4_UPD_QP_PATH_MASK_MAC_INDEX			= 2 + 32,
	MLX4_UPD_QP_PATH_MASK_FVL			= 3 + 32,
	MLX4_UPD_QP_PATH_MASK_CV			= 4 + 32,
	MLX4_UPD_QP_PATH_MASK_VLAN_INDEX		= 5 + 32,
	MLX4_UPD_QP_PATH_MASK_ETH_HIDE_CQE_VLAN		= 6 + 32,
	MLX4_UPD_QP_PATH_MASK_ETH_TX_BLOCK_UNTAGGED	= 7 + 32,
	MLX4_UPD_QP_PATH_MASK_ETH_TX_BLOCK_1P		= 8 + 32,
	MLX4_UPD_QP_PATH_MASK_ETH_TX_BLOCK_TAGGED	= 9 + 32,
	MLX4_UPD_QP_PATH_MASK_ETH_RX_BLOCK_UNTAGGED	= 10 + 32,
	MLX4_UPD_QP_PATH_MASK_ETH_RX_BLOCK_1P		= 11 + 32,
	MLX4_UPD_QP_PATH_MASK_ETH_RX_BLOCK_TAGGED	= 12 + 32,
	MLX4_UPD_QP_PATH_MASK_FEUP			= 13 + 32,
	MLX4_UPD_QP_PATH_MASK_SCHED_QUEUE		= 14 + 32,
	MLX4_UPD_QP_PATH_MASK_IF_COUNTER_INDEX		= 15 + 32,
	MLX4_UPD_QP_PATH_MASK_FVL_RX			= 16 + 32,
	MLX4_UPD_QP_PATH_MASK_ETH_SRC_CHECK_UC_LB	= 18 + 32,
	MLX4_UPD_QP_PATH_MASK_ETH_SRC_CHECK_MC_LB	= 19 + 32,
	MLX4_UPD_QP_PATH_MASK_SV			= 22 + 32,
पूर्ण;

क्रमागत अणु /* param3 */
	MLX4_STRIP_VLAN = 1 << 30
पूर्ण;

/* Which firmware version adds support क्रम NEC (NoErrorCompletion) bit */
#घोषणा MLX4_FW_VER_WQE_CTRL_NEC mlx4_fw_ver(2, 2, 232)

क्रमागत अणु
	MLX4_WQE_CTRL_NEC		= 1 << 29,
	MLX4_WQE_CTRL_IIP		= 1 << 28,
	MLX4_WQE_CTRL_ILP		= 1 << 27,
	MLX4_WQE_CTRL_FENCE		= 1 << 6,
	MLX4_WQE_CTRL_CQ_UPDATE		= 3 << 2,
	MLX4_WQE_CTRL_SOLICITED		= 1 << 1,
	MLX4_WQE_CTRL_IP_CSUM		= 1 << 4,
	MLX4_WQE_CTRL_TCP_UDP_CSUM	= 1 << 5,
	MLX4_WQE_CTRL_INS_CVLAN		= 1 << 6,
	MLX4_WQE_CTRL_INS_SVLAN		= 1 << 7,
	MLX4_WQE_CTRL_STRONG_ORDER	= 1 << 7,
	MLX4_WQE_CTRL_FORCE_LOOPBACK	= 1 << 0,
पूर्ण;

जोड़ mlx4_wqe_qpn_vlan अणु
	काष्ठा अणु
		__be16	vlan_tag;
		u8	ins_vlan;
		u8	fence_size;
	पूर्ण;
	__be32		bf_qpn;
पूर्ण;

काष्ठा mlx4_wqe_ctrl_seg अणु
	__be32			owner_opcode;
	जोड़ mlx4_wqe_qpn_vlan	qpn_vlan;
	/*
	 * High 24 bits are SRC remote buffer; low 8 bits are flags:
	 * [7]   SO (strong ordering)
	 * [5]   TCP/UDP checksum
	 * [4]   IP checksum
	 * [3:2] C (generate completion queue entry)
	 * [1]   SE (solicited event)
	 * [0]   FL (क्रमce loopback)
	 */
	जोड़ अणु
		__be32			srcrb_flags;
		__be16			srcrb_flags16[2];
	पूर्ण;
	/*
	 * imm is immediate data क्रम send/RDMA ग_लिखो w/ immediate;
	 * also invalidation key क्रम send with invalidate; input
	 * modअगरier क्रम WQEs on CCQs.
	 */
	__be32			imm;
पूर्ण;

क्रमागत अणु
	MLX4_WQE_MLX_VL15	= 1 << 17,
	MLX4_WQE_MLX_SLR	= 1 << 16
पूर्ण;

काष्ठा mlx4_wqe_mlx_seg अणु
	u8			owner;
	u8			reserved1[2];
	u8			opcode;
	__be16			sched_prio;
	u8			reserved2;
	u8			size;
	/*
	 * [17]    VL15
	 * [16]    SLR
	 * [15:12] अटल rate
	 * [11:8]  SL
	 * [4]     ICRC
	 * [3:2]   C
	 * [0]     FL (क्रमce loopback)
	 */
	__be32			flags;
	__be16			rlid;
	u16			reserved3;
पूर्ण;

काष्ठा mlx4_wqe_datagram_seg अणु
	__be32			av[8];
	__be32			dqpn;
	__be32			qkey;
	__be16			vlan;
	u8			mac[ETH_ALEN];
पूर्ण;

काष्ठा mlx4_wqe_lso_seg अणु
	__be32			mss_hdr_size;
	__be32			header[];
पूर्ण;

क्रमागत mlx4_wqe_bind_seg_flags2 अणु
	MLX4_WQE_BIND_ZERO_BASED = (1 << 30),
	MLX4_WQE_BIND_TYPE_2     = (1 << 31),
पूर्ण;

काष्ठा mlx4_wqe_bind_seg अणु
	__be32			flags1;
	__be32			flags2;
	__be32			new_rkey;
	__be32			lkey;
	__be64			addr;
	__be64			length;
पूर्ण;

क्रमागत अणु
	MLX4_WQE_FMR_PERM_LOCAL_READ	= 1 << 27,
	MLX4_WQE_FMR_PERM_LOCAL_WRITE	= 1 << 28,
	MLX4_WQE_FMR_AND_BIND_PERM_REMOTE_READ	= 1 << 29,
	MLX4_WQE_FMR_AND_BIND_PERM_REMOTE_WRITE	= 1 << 30,
	MLX4_WQE_FMR_AND_BIND_PERM_ATOMIC	= 1 << 31
पूर्ण;

काष्ठा mlx4_wqe_fmr_seg अणु
	__be32			flags;
	__be32			mem_key;
	__be64			buf_list;
	__be64			start_addr;
	__be64			reg_len;
	__be32			offset;
	__be32			page_size;
	u32			reserved[2];
पूर्ण;

काष्ठा mlx4_wqe_fmr_ext_seg अणु
	u8			flags;
	u8			reserved;
	__be16			app_mask;
	__be16			wire_app_tag;
	__be16			mem_app_tag;
	__be32			wire_ref_tag_base;
	__be32			mem_ref_tag_base;
पूर्ण;

काष्ठा mlx4_wqe_local_inval_seg अणु
	u64			reserved1;
	__be32			mem_key;
	u32			reserved2;
	u64			reserved3[2];
पूर्ण;

काष्ठा mlx4_wqe_raddr_seg अणु
	__be64			raddr;
	__be32			rkey;
	u32			reserved;
पूर्ण;

काष्ठा mlx4_wqe_atomic_seg अणु
	__be64			swap_add;
	__be64			compare;
पूर्ण;

काष्ठा mlx4_wqe_masked_atomic_seg अणु
	__be64			swap_add;
	__be64			compare;
	__be64			swap_add_mask;
	__be64			compare_mask;
पूर्ण;

काष्ठा mlx4_wqe_data_seg अणु
	__be32			byte_count;
	__be32			lkey;
	__be64			addr;
पूर्ण;

क्रमागत अणु
	MLX4_INLINE_ALIGN	= 64,
	MLX4_INLINE_SEG		= 1 << 31,
पूर्ण;

काष्ठा mlx4_wqe_अंतरभूत_seg अणु
	__be32			byte_count;
पूर्ण;

क्रमागत mlx4_update_qp_attr अणु
	MLX4_UPDATE_QP_SMAC		= 1 << 0,
	MLX4_UPDATE_QP_VSD		= 1 << 1,
	MLX4_UPDATE_QP_RATE_LIMIT	= 1 << 2,
	MLX4_UPDATE_QP_QOS_VPORT	= 1 << 3,
	MLX4_UPDATE_QP_ETH_SRC_CHECK_MC_LB      = 1 << 4,
	MLX4_UPDATE_QP_SUPPORTED_ATTRS	= (1 << 5) - 1
पूर्ण;

क्रमागत mlx4_update_qp_params_flags अणु
	MLX4_UPDATE_QP_PARAMS_FLAGS_ETH_CHECK_MC_LB     = 1 << 0,
	MLX4_UPDATE_QP_PARAMS_FLAGS_VSD_ENABLE		= 1 << 1,
पूर्ण;

काष्ठा mlx4_update_qp_params अणु
	u8	smac_index;
	u8	qos_vport;
	u32	flags;
	u16	rate_unit;
	u16	rate_val;
पूर्ण;

काष्ठा mlx4_qp *mlx4_qp_lookup(काष्ठा mlx4_dev *dev, u32 qpn);
पूर्णांक mlx4_update_qp(काष्ठा mlx4_dev *dev, u32 qpn,
		   क्रमागत mlx4_update_qp_attr attr,
		   काष्ठा mlx4_update_qp_params *params);
पूर्णांक mlx4_qp_modअगरy(काष्ठा mlx4_dev *dev, काष्ठा mlx4_mtt *mtt,
		   क्रमागत mlx4_qp_state cur_state, क्रमागत mlx4_qp_state new_state,
		   काष्ठा mlx4_qp_context *context, क्रमागत mlx4_qp_optpar optpar,
		   पूर्णांक sqd_event, काष्ठा mlx4_qp *qp);

पूर्णांक mlx4_qp_query(काष्ठा mlx4_dev *dev, काष्ठा mlx4_qp *qp,
		  काष्ठा mlx4_qp_context *context);

पूर्णांक mlx4_qp_to_पढ़ोy(काष्ठा mlx4_dev *dev, काष्ठा mlx4_mtt *mtt,
		     काष्ठा mlx4_qp_context *context,
		     काष्ठा mlx4_qp *qp, क्रमागत mlx4_qp_state *qp_state);

अटल अंतरभूत काष्ठा mlx4_qp *__mlx4_qp_lookup(काष्ठा mlx4_dev *dev, u32 qpn)
अणु
	वापस radix_tree_lookup(&dev->qp_table_tree, qpn & (dev->caps.num_qps - 1));
पूर्ण

व्योम mlx4_qp_हटाओ(काष्ठा mlx4_dev *dev, काष्ठा mlx4_qp *qp);

अटल अंतरभूत u16 folded_qp(u32 q)
अणु
	u16 res;

	res = ((q & 0xff) ^ ((q & 0xff0000) >> 16)) | (q & 0xff00);
	वापस res;
पूर्ण

u16 mlx4_qp_roce_entropy(काष्ठा mlx4_dev *dev, u32 qpn);

#पूर्ण_अगर /* MLX4_QP_H */
