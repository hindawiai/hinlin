<शैली गुरु>
/*
 * Copyright (c) 2006, 2007 Cisco Systems, Inc.  All rights reserved.
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

#अगर_अघोषित MLX4_DEVICE_H
#घोषणा MLX4_DEVICE_H

#समावेश <linux/अगर_ether.h>
#समावेश <linux/pci.h>
#समावेश <linux/completion.h>
#समावेश <linux/radix-tree.h>
#समावेश <linux/cpu_rmap.h>
#समावेश <linux/crash_dump.h>

#समावेश <linux/refcount.h>

#समावेश <linux/समयcounter.h>

#घोषणा DEFAULT_UAR_PAGE_SHIFT  12

#घोषणा MAX_MSIX		128
#घोषणा MIN_MSIX_P_PORT		5
#घोषणा MLX4_IS_LEGACY_EQ_MODE(dev_cap) ((dev_cap).num_comp_vectors < \
					 (dev_cap).num_ports * MIN_MSIX_P_PORT)

#घोषणा MLX4_MAX_100M_UNITS_VAL		255	/*
						 * work around: can't set values
						 * greater then this value when
						 * using 100 Mbps units.
						 */
#घोषणा MLX4_RATELIMIT_100M_UNITS	3	/* 100 Mbps */
#घोषणा MLX4_RATELIMIT_1G_UNITS		4	/* 1 Gbps */
#घोषणा MLX4_RATELIMIT_DEFAULT		0x00ff

#घोषणा MLX4_ROCE_MAX_GIDS	128
#घोषणा MLX4_ROCE_PF_GIDS	16

क्रमागत अणु
	MLX4_FLAG_MSI_X		= 1 << 0,
	MLX4_FLAG_OLD_PORT_CMDS	= 1 << 1,
	MLX4_FLAG_MASTER	= 1 << 2,
	MLX4_FLAG_SLAVE		= 1 << 3,
	MLX4_FLAG_SRIOV		= 1 << 4,
	MLX4_FLAG_OLD_REG_MAC	= 1 << 6,
	MLX4_FLAG_BONDED	= 1 << 7,
	MLX4_FLAG_SECURE_HOST	= 1 << 8,
पूर्ण;

क्रमागत अणु
	MLX4_PORT_CAP_IS_SM	= 1 << 1,
	MLX4_PORT_CAP_DEV_MGMT_SUP = 1 << 19,
पूर्ण;

क्रमागत अणु
	MLX4_MAX_PORTS		= 2,
	MLX4_MAX_PORT_PKEYS	= 128,
	MLX4_MAX_PORT_GIDS	= 128
पूर्ण;

/* base qkey क्रम use in sriov tunnel-qp/proxy-qp communication.
 * These qkeys must not be allowed क्रम general use. This is a 64k range,
 * and to test क्रम violation, we use the mask (protect against future chg).
 */
#घोषणा MLX4_RESERVED_QKEY_BASE  (0xFFFF0000)
#घोषणा MLX4_RESERVED_QKEY_MASK  (0xFFFF0000)

क्रमागत अणु
	MLX4_BOARD_ID_LEN = 64
पूर्ण;

क्रमागत अणु
	MLX4_MAX_NUM_PF		= 16,
	MLX4_MAX_NUM_VF		= 126,
	MLX4_MAX_NUM_VF_P_PORT  = 64,
	MLX4_MFUNC_MAX		= 128,
	MLX4_MAX_EQ_NUM		= 1024,
	MLX4_MFUNC_EQ_NUM	= 4,
	MLX4_MFUNC_MAX_EQES     = 8,
	MLX4_MFUNC_EQE_MASK     = (MLX4_MFUNC_MAX_EQES - 1)
पूर्ण;

/* Driver supports 3 dअगरferent device methods to manage traffic steering:
 *	-device managed - High level API क्रम ib and eth flow steering. FW is
 *			  managing flow steering tables.
 *	- B0 steering mode - Common low level API क्रम ib and (अगर supported) eth.
 *	- A0 steering mode - Limited low level API क्रम eth. In हाल of IB,
 *			     B0 mode is in use.
 */
क्रमागत अणु
	MLX4_STEERING_MODE_A0,
	MLX4_STEERING_MODE_B0,
	MLX4_STEERING_MODE_DEVICE_MANAGED
पूर्ण;

क्रमागत अणु
	MLX4_STEERING_DMFS_A0_DEFAULT,
	MLX4_STEERING_DMFS_A0_DYNAMIC,
	MLX4_STEERING_DMFS_A0_STATIC,
	MLX4_STEERING_DMFS_A0_DISABLE,
	MLX4_STEERING_DMFS_A0_NOT_SUPPORTED
पूर्ण;

अटल अंतरभूत स्थिर अक्षर *mlx4_steering_mode_str(पूर्णांक steering_mode)
अणु
	चयन (steering_mode) अणु
	हाल MLX4_STEERING_MODE_A0:
		वापस "A0 steering";

	हाल MLX4_STEERING_MODE_B0:
		वापस "B0 steering";

	हाल MLX4_STEERING_MODE_DEVICE_MANAGED:
		वापस "Device managed flow steering";

	शेष:
		वापस "Unrecognize steering mode";
	पूर्ण
पूर्ण

क्रमागत अणु
	MLX4_TUNNEL_OFFLOAD_MODE_NONE,
	MLX4_TUNNEL_OFFLOAD_MODE_VXLAN
पूर्ण;

क्रमागत अणु
	MLX4_DEV_CAP_FLAG_RC		= 1LL <<  0,
	MLX4_DEV_CAP_FLAG_UC		= 1LL <<  1,
	MLX4_DEV_CAP_FLAG_UD		= 1LL <<  2,
	MLX4_DEV_CAP_FLAG_XRC		= 1LL <<  3,
	MLX4_DEV_CAP_FLAG_SRQ		= 1LL <<  6,
	MLX4_DEV_CAP_FLAG_IPOIB_CSUM	= 1LL <<  7,
	MLX4_DEV_CAP_FLAG_BAD_PKEY_CNTR	= 1LL <<  8,
	MLX4_DEV_CAP_FLAG_BAD_QKEY_CNTR	= 1LL <<  9,
	MLX4_DEV_CAP_FLAG_DPDP		= 1LL << 12,
	MLX4_DEV_CAP_FLAG_BLH		= 1LL << 15,
	MLX4_DEV_CAP_FLAG_MEM_WINDOW	= 1LL << 16,
	MLX4_DEV_CAP_FLAG_APM		= 1LL << 17,
	MLX4_DEV_CAP_FLAG_ATOMIC	= 1LL << 18,
	MLX4_DEV_CAP_FLAG_RAW_MCAST	= 1LL << 19,
	MLX4_DEV_CAP_FLAG_UD_AV_PORT	= 1LL << 20,
	MLX4_DEV_CAP_FLAG_UD_MCAST	= 1LL << 21,
	MLX4_DEV_CAP_FLAG_IBOE		= 1LL << 30,
	MLX4_DEV_CAP_FLAG_UC_LOOPBACK	= 1LL << 32,
	MLX4_DEV_CAP_FLAG_FCS_KEEP	= 1LL << 34,
	MLX4_DEV_CAP_FLAG_WOL_PORT1	= 1LL << 37,
	MLX4_DEV_CAP_FLAG_WOL_PORT2	= 1LL << 38,
	MLX4_DEV_CAP_FLAG_UDP_RSS	= 1LL << 40,
	MLX4_DEV_CAP_FLAG_VEP_UC_STEER	= 1LL << 41,
	MLX4_DEV_CAP_FLAG_VEP_MC_STEER	= 1LL << 42,
	MLX4_DEV_CAP_FLAG_COUNTERS	= 1LL << 48,
	MLX4_DEV_CAP_FLAG_RSS_IP_FRAG   = 1LL << 52,
	MLX4_DEV_CAP_FLAG_SET_ETH_SCHED = 1LL << 53,
	MLX4_DEV_CAP_FLAG_SENSE_SUPPORT	= 1LL << 55,
	MLX4_DEV_CAP_FLAG_PORT_MNG_CHG_EV = 1LL << 59,
	MLX4_DEV_CAP_FLAG_64B_EQE	= 1LL << 61,
	MLX4_DEV_CAP_FLAG_64B_CQE	= 1LL << 62
पूर्ण;

क्रमागत अणु
	MLX4_DEV_CAP_FLAG2_RSS			= 1LL <<  0,
	MLX4_DEV_CAP_FLAG2_RSS_TOP		= 1LL <<  1,
	MLX4_DEV_CAP_FLAG2_RSS_XOR		= 1LL <<  2,
	MLX4_DEV_CAP_FLAG2_FS_EN		= 1LL <<  3,
	MLX4_DEV_CAP_FLAG2_REASSIGN_MAC_EN	= 1LL <<  4,
	MLX4_DEV_CAP_FLAG2_TS			= 1LL <<  5,
	MLX4_DEV_CAP_FLAG2_VLAN_CONTROL		= 1LL <<  6,
	MLX4_DEV_CAP_FLAG2_FSM			= 1LL <<  7,
	MLX4_DEV_CAP_FLAG2_UPDATE_QP		= 1LL <<  8,
	MLX4_DEV_CAP_FLAG2_DMFS_IPOIB		= 1LL <<  9,
	MLX4_DEV_CAP_FLAG2_VXLAN_OFFLOADS	= 1LL <<  10,
	MLX4_DEV_CAP_FLAG2_MAD_DEMUX		= 1LL <<  11,
	MLX4_DEV_CAP_FLAG2_CQE_STRIDE		= 1LL <<  12,
	MLX4_DEV_CAP_FLAG2_EQE_STRIDE		= 1LL <<  13,
	MLX4_DEV_CAP_FLAG2_ETH_PROT_CTRL        = 1LL <<  14,
	MLX4_DEV_CAP_FLAG2_ETH_BACKPL_AN_REP	= 1LL <<  15,
	MLX4_DEV_CAP_FLAG2_CONFIG_DEV		= 1LL <<  16,
	MLX4_DEV_CAP_FLAG2_SYS_EQS		= 1LL <<  17,
	MLX4_DEV_CAP_FLAG2_80_VFS		= 1LL <<  18,
	MLX4_DEV_CAP_FLAG2_FS_A0		= 1LL <<  19,
	MLX4_DEV_CAP_FLAG2_RECOVERABLE_ERROR_EVENT = 1LL << 20,
	MLX4_DEV_CAP_FLAG2_PORT_REMAP		= 1LL <<  21,
	MLX4_DEV_CAP_FLAG2_QCN			= 1LL <<  22,
	MLX4_DEV_CAP_FLAG2_QP_RATE_LIMIT	= 1LL <<  23,
	MLX4_DEV_CAP_FLAG2_FLOWSTATS_EN         = 1LL <<  24,
	MLX4_DEV_CAP_FLAG2_QOS_VPP		= 1LL <<  25,
	MLX4_DEV_CAP_FLAG2_ETS_CFG		= 1LL <<  26,
	MLX4_DEV_CAP_FLAG2_PORT_BEACON		= 1LL <<  27,
	MLX4_DEV_CAP_FLAG2_IGNORE_FCS		= 1LL <<  28,
	MLX4_DEV_CAP_FLAG2_PHV_EN		= 1LL <<  29,
	MLX4_DEV_CAP_FLAG2_SKIP_OUTER_VLAN	= 1LL <<  30,
	MLX4_DEV_CAP_FLAG2_UPDATE_QP_SRC_CHECK_LB = 1ULL << 31,
	MLX4_DEV_CAP_FLAG2_LB_SRC_CHK           = 1ULL << 32,
	MLX4_DEV_CAP_FLAG2_ROCE_V1_V2		= 1ULL <<  33,
	MLX4_DEV_CAP_FLAG2_DMFS_UC_MC_SNIFFER   = 1ULL <<  34,
	MLX4_DEV_CAP_FLAG2_DIAG_PER_PORT	= 1ULL <<  35,
	MLX4_DEV_CAP_FLAG2_SVLAN_BY_QP          = 1ULL <<  36,
	MLX4_DEV_CAP_FLAG2_SL_TO_VL_CHANGE_EVENT = 1ULL << 37,
	MLX4_DEV_CAP_FLAG2_USER_MAC_EN		= 1ULL << 38,
	MLX4_DEV_CAP_FLAG2_DRIVER_VERSION_TO_FW = 1ULL << 39,
	MLX4_DEV_CAP_FLAG2_SW_CQ_INIT           = 1ULL << 40,
पूर्ण;

क्रमागत अणु
	MLX4_QUERY_FUNC_FLAGS_BF_RES_QP		= 1LL << 0,
	MLX4_QUERY_FUNC_FLAGS_A0_RES_QP		= 1LL << 1
पूर्ण;

क्रमागत अणु
	MLX4_VF_CAP_FLAG_RESET			= 1 << 0
पूर्ण;

/* bit क्रमागतs क्रम an 8-bit flags field indicating special use
 * QPs which require special handling in qp_reserve_range.
 * Currently, this only includes QPs used by the ETH पूर्णांकerface,
 * where we expect to use blueflame.  These QPs must not have
 * bits 6 and 7 set in their qp number.
 *
 * This क्रमागत may use only bits 0..7.
 */
क्रमागत अणु
	MLX4_RESERVE_A0_QP	= 1 << 6,
	MLX4_RESERVE_ETH_BF_QP	= 1 << 7,
पूर्ण;

क्रमागत अणु
	MLX4_DEV_CAP_64B_EQE_ENABLED	= 1LL << 0,
	MLX4_DEV_CAP_64B_CQE_ENABLED	= 1LL << 1,
	MLX4_DEV_CAP_CQE_STRIDE_ENABLED	= 1LL << 2,
	MLX4_DEV_CAP_EQE_STRIDE_ENABLED	= 1LL << 3
पूर्ण;

क्रमागत अणु
	MLX4_FUNC_CAP_64B_EQE_CQE	= 1L << 0,
	MLX4_FUNC_CAP_EQE_CQE_STRIDE	= 1L << 1,
	MLX4_FUNC_CAP_DMFS_A0_STATIC	= 1L << 2
पूर्ण;


#घोषणा MLX4_ATTR_EXTENDED_PORT_INFO	cpu_to_be16(0xff90)

क्रमागत अणु
	MLX4_BMME_FLAG_WIN_TYPE_2B	= 1 <<  1,
	MLX4_BMME_FLAG_LOCAL_INV	= 1 <<  6,
	MLX4_BMME_FLAG_REMOTE_INV	= 1 <<  7,
	MLX4_BMME_FLAG_TYPE_2_WIN	= 1 <<  9,
	MLX4_BMME_FLAG_RESERVED_LKEY	= 1 << 10,
	MLX4_BMME_FLAG_FAST_REG_WR	= 1 << 11,
	MLX4_BMME_FLAG_ROCE_V1_V2	= 1 << 19,
	MLX4_BMME_FLAG_PORT_REMAP	= 1 << 24,
	MLX4_BMME_FLAG_VSD_INIT2RTR	= 1 << 28,
पूर्ण;

क्रमागत अणु
	MLX4_FLAG_PORT_REMAP		= MLX4_BMME_FLAG_PORT_REMAP,
	MLX4_FLAG_ROCE_V1_V2		= MLX4_BMME_FLAG_ROCE_V1_V2
पूर्ण;

क्रमागत mlx4_event अणु
	MLX4_EVENT_TYPE_COMP		   = 0x00,
	MLX4_EVENT_TYPE_PATH_MIG	   = 0x01,
	MLX4_EVENT_TYPE_COMM_EST	   = 0x02,
	MLX4_EVENT_TYPE_SQ_DRAINED	   = 0x03,
	MLX4_EVENT_TYPE_SRQ_QP_LAST_WQE	   = 0x13,
	MLX4_EVENT_TYPE_SRQ_LIMIT	   = 0x14,
	MLX4_EVENT_TYPE_CQ_ERROR	   = 0x04,
	MLX4_EVENT_TYPE_WQ_CATAS_ERROR	   = 0x05,
	MLX4_EVENT_TYPE_EEC_CATAS_ERROR	   = 0x06,
	MLX4_EVENT_TYPE_PATH_MIG_FAILED	   = 0x07,
	MLX4_EVENT_TYPE_WQ_INVAL_REQ_ERROR = 0x10,
	MLX4_EVENT_TYPE_WQ_ACCESS_ERROR	   = 0x11,
	MLX4_EVENT_TYPE_SRQ_CATAS_ERROR	   = 0x12,
	MLX4_EVENT_TYPE_LOCAL_CATAS_ERROR  = 0x08,
	MLX4_EVENT_TYPE_PORT_CHANGE	   = 0x09,
	MLX4_EVENT_TYPE_EQ_OVERFLOW	   = 0x0f,
	MLX4_EVENT_TYPE_ECC_DETECT	   = 0x0e,
	MLX4_EVENT_TYPE_CMD		   = 0x0a,
	MLX4_EVENT_TYPE_VEP_UPDATE	   = 0x19,
	MLX4_EVENT_TYPE_COMM_CHANNEL	   = 0x18,
	MLX4_EVENT_TYPE_OP_REQUIRED	   = 0x1a,
	MLX4_EVENT_TYPE_FATAL_WARNING	   = 0x1b,
	MLX4_EVENT_TYPE_FLR_EVENT	   = 0x1c,
	MLX4_EVENT_TYPE_PORT_MNG_CHG_EVENT = 0x1d,
	MLX4_EVENT_TYPE_RECOVERABLE_ERROR_EVENT  = 0x3e,
	MLX4_EVENT_TYPE_NONE		   = 0xff,
पूर्ण;

क्रमागत अणु
	MLX4_PORT_CHANGE_SUBTYPE_DOWN	= 1,
	MLX4_PORT_CHANGE_SUBTYPE_ACTIVE	= 4
पूर्ण;

क्रमागत अणु
	MLX4_RECOVERABLE_ERROR_EVENT_SUBTYPE_BAD_CABLE		= 1,
	MLX4_RECOVERABLE_ERROR_EVENT_SUBTYPE_UNSUPPORTED_CABLE	= 2,
पूर्ण;

क्रमागत अणु
	MLX4_FATAL_WARNING_SUBTYPE_WARMING = 0,
पूर्ण;

क्रमागत slave_port_state अणु
	SLAVE_PORT_DOWN = 0,
	SLAVE_PENDING_UP,
	SLAVE_PORT_UP,
पूर्ण;

क्रमागत slave_port_gen_event अणु
	SLAVE_PORT_GEN_EVENT_DOWN = 0,
	SLAVE_PORT_GEN_EVENT_UP,
	SLAVE_PORT_GEN_EVENT_NONE,
पूर्ण;

क्रमागत slave_port_state_event अणु
	MLX4_PORT_STATE_DEV_EVENT_PORT_DOWN,
	MLX4_PORT_STATE_DEV_EVENT_PORT_UP,
	MLX4_PORT_STATE_IB_PORT_STATE_EVENT_GID_VALID,
	MLX4_PORT_STATE_IB_EVENT_GID_INVALID,
पूर्ण;

क्रमागत अणु
	MLX4_PERM_LOCAL_READ	= 1 << 10,
	MLX4_PERM_LOCAL_WRITE	= 1 << 11,
	MLX4_PERM_REMOTE_READ	= 1 << 12,
	MLX4_PERM_REMOTE_WRITE	= 1 << 13,
	MLX4_PERM_ATOMIC	= 1 << 14,
	MLX4_PERM_BIND_MW	= 1 << 15,
	MLX4_PERM_MASK		= 0xFC00
पूर्ण;

क्रमागत अणु
	MLX4_OPCODE_NOP			= 0x00,
	MLX4_OPCODE_SEND_INVAL		= 0x01,
	MLX4_OPCODE_RDMA_WRITE		= 0x08,
	MLX4_OPCODE_RDMA_WRITE_IMM	= 0x09,
	MLX4_OPCODE_SEND		= 0x0a,
	MLX4_OPCODE_SEND_IMM		= 0x0b,
	MLX4_OPCODE_LSO			= 0x0e,
	MLX4_OPCODE_RDMA_READ		= 0x10,
	MLX4_OPCODE_ATOMIC_CS		= 0x11,
	MLX4_OPCODE_ATOMIC_FA		= 0x12,
	MLX4_OPCODE_MASKED_ATOMIC_CS	= 0x14,
	MLX4_OPCODE_MASKED_ATOMIC_FA	= 0x15,
	MLX4_OPCODE_BIND_MW		= 0x18,
	MLX4_OPCODE_FMR			= 0x19,
	MLX4_OPCODE_LOCAL_INVAL		= 0x1b,
	MLX4_OPCODE_CONFIG_CMD		= 0x1f,

	MLX4_RECV_OPCODE_RDMA_WRITE_IMM	= 0x00,
	MLX4_RECV_OPCODE_SEND		= 0x01,
	MLX4_RECV_OPCODE_SEND_IMM	= 0x02,
	MLX4_RECV_OPCODE_SEND_INVAL	= 0x03,

	MLX4_CQE_OPCODE_ERROR		= 0x1e,
	MLX4_CQE_OPCODE_RESIZE		= 0x16,
पूर्ण;

क्रमागत अणु
	MLX4_STAT_RATE_OFFSET	= 5
पूर्ण;

क्रमागत mlx4_protocol अणु
	MLX4_PROT_IB_IPV6 = 0,
	MLX4_PROT_ETH,
	MLX4_PROT_IB_IPV4,
	MLX4_PROT_FCOE
पूर्ण;

क्रमागत अणु
	MLX4_MTT_FLAG_PRESENT		= 1
पूर्ण;

क्रमागत mlx4_qp_region अणु
	MLX4_QP_REGION_FW = 0,
	MLX4_QP_REGION_RSS_RAW_ETH,
	MLX4_QP_REGION_BOTTOM = MLX4_QP_REGION_RSS_RAW_ETH,
	MLX4_QP_REGION_ETH_ADDR,
	MLX4_QP_REGION_FC_ADDR,
	MLX4_QP_REGION_FC_EXCH,
	MLX4_NUM_QP_REGION
पूर्ण;

क्रमागत mlx4_port_type अणु
	MLX4_PORT_TYPE_NONE	= 0,
	MLX4_PORT_TYPE_IB	= 1,
	MLX4_PORT_TYPE_ETH	= 2,
	MLX4_PORT_TYPE_AUTO	= 3
पूर्ण;

क्रमागत mlx4_special_vlan_idx अणु
	MLX4_NO_VLAN_IDX        = 0,
	MLX4_VLAN_MISS_IDX,
	MLX4_VLAN_REGULAR
पूर्ण;

क्रमागत mlx4_steer_type अणु
	MLX4_MC_STEER = 0,
	MLX4_UC_STEER,
	MLX4_NUM_STEERS
पूर्ण;

क्रमागत mlx4_resource_usage अणु
	MLX4_RES_USAGE_NONE,
	MLX4_RES_USAGE_DRIVER,
	MLX4_RES_USAGE_USER_VERBS,
पूर्ण;

क्रमागत अणु
	MLX4_NUM_FEXCH          = 64 * 1024,
पूर्ण;

क्रमागत अणु
	MLX4_MAX_FAST_REG_PAGES = 511,
पूर्ण;

क्रमागत अणु
	/*
	 * Max wqe size क्रम rdma पढ़ो is 512 bytes, so this
	 * limits our max_sge_rd as the wqe needs to fit:
	 * - ctrl segment (16 bytes)
	 * - rdma segment (16 bytes)
	 * - scatter elements (16 bytes each)
	 */
	MLX4_MAX_SGE_RD	= (512 - 16 - 16) / 16
पूर्ण;

क्रमागत अणु
	MLX4_DEV_PMC_SUBTYPE_GUID_INFO	 = 0x14,
	MLX4_DEV_PMC_SUBTYPE_PORT_INFO	 = 0x15,
	MLX4_DEV_PMC_SUBTYPE_PKEY_TABLE	 = 0x16,
	MLX4_DEV_PMC_SUBTYPE_SL_TO_VL_MAP = 0x17,
पूर्ण;

/* Port mgmt change event handling */
क्रमागत अणु
	MLX4_EQ_PORT_INFO_MSTR_SM_LID_CHANGE_MASK	= 1 << 0,
	MLX4_EQ_PORT_INFO_GID_PFX_CHANGE_MASK		= 1 << 1,
	MLX4_EQ_PORT_INFO_LID_CHANGE_MASK		= 1 << 2,
	MLX4_EQ_PORT_INFO_CLIENT_REREG_MASK		= 1 << 3,
	MLX4_EQ_PORT_INFO_MSTR_SM_SL_CHANGE_MASK	= 1 << 4,
पूर्ण;

जोड़ sl2vl_tbl_to_u64 अणु
	u8	sl8[8];
	u64	sl64;
पूर्ण;

क्रमागत अणु
	MLX4_DEVICE_STATE_UP			= 1 << 0,
	MLX4_DEVICE_STATE_INTERNAL_ERROR	= 1 << 1,
पूर्ण;

क्रमागत अणु
	MLX4_INTERFACE_STATE_UP		= 1 << 0,
	MLX4_INTERFACE_STATE_DELETION	= 1 << 1,
	MLX4_INTERFACE_STATE_NOWAIT	= 1 << 2,
पूर्ण;

#घोषणा MSTR_SM_CHANGE_MASK (MLX4_EQ_PORT_INFO_MSTR_SM_SL_CHANGE_MASK | \
			     MLX4_EQ_PORT_INFO_MSTR_SM_LID_CHANGE_MASK)

क्रमागत mlx4_module_id अणु
	MLX4_MODULE_ID_SFP              = 0x3,
	MLX4_MODULE_ID_QSFP             = 0xC,
	MLX4_MODULE_ID_QSFP_PLUS        = 0xD,
	MLX4_MODULE_ID_QSFP28           = 0x11,
पूर्ण;

क्रमागत अणु /* rl */
	MLX4_QP_RATE_LIMIT_NONE		= 0,
	MLX4_QP_RATE_LIMIT_KBS		= 1,
	MLX4_QP_RATE_LIMIT_MBS		= 2,
	MLX4_QP_RATE_LIMIT_GBS		= 3
पूर्ण;

काष्ठा mlx4_rate_limit_caps अणु
	u16	num_rates; /* Number of dअगरferent rates */
	u8	min_unit;
	u16	min_val;
	u8	max_unit;
	u16	max_val;
पूर्ण;

अटल अंतरभूत u64 mlx4_fw_ver(u64 major, u64 minor, u64 subminor)
अणु
	वापस (major << 32) | (minor << 16) | subminor;
पूर्ण

काष्ठा mlx4_phys_caps अणु
	u32			gid_phys_table_len[MLX4_MAX_PORTS + 1];
	u32			pkey_phys_table_len[MLX4_MAX_PORTS + 1];
	u32			num_phys_eqs;
	u32			base_sqpn;
	u32			base_proxy_sqpn;
	u32			base_tunnel_sqpn;
पूर्ण;

काष्ठा mlx4_spec_qps अणु
	u32 qp0_qkey;
	u32 qp0_proxy;
	u32 qp0_tunnel;
	u32 qp1_proxy;
	u32 qp1_tunnel;
पूर्ण;

काष्ठा mlx4_caps अणु
	u64			fw_ver;
	u32			function;
	पूर्णांक			num_ports;
	पूर्णांक			vl_cap[MLX4_MAX_PORTS + 1];
	पूर्णांक			ib_mtu_cap[MLX4_MAX_PORTS + 1];
	__be32			ib_port_def_cap[MLX4_MAX_PORTS + 1];
	u64			def_mac[MLX4_MAX_PORTS + 1];
	पूर्णांक			eth_mtu_cap[MLX4_MAX_PORTS + 1];
	पूर्णांक			gid_table_len[MLX4_MAX_PORTS + 1];
	पूर्णांक			pkey_table_len[MLX4_MAX_PORTS + 1];
	पूर्णांक			trans_type[MLX4_MAX_PORTS + 1];
	पूर्णांक			venकरोr_oui[MLX4_MAX_PORTS + 1];
	पूर्णांक			wavelength[MLX4_MAX_PORTS + 1];
	u64			trans_code[MLX4_MAX_PORTS + 1];
	पूर्णांक			local_ca_ack_delay;
	पूर्णांक			num_uars;
	u32			uar_page_size;
	पूर्णांक			bf_reg_size;
	पूर्णांक			bf_regs_per_page;
	पूर्णांक			max_sq_sg;
	पूर्णांक			max_rq_sg;
	पूर्णांक			num_qps;
	पूर्णांक			max_wqes;
	पूर्णांक			max_sq_desc_sz;
	पूर्णांक			max_rq_desc_sz;
	पूर्णांक			max_qp_init_rdma;
	पूर्णांक			max_qp_dest_rdma;
	पूर्णांक			max_tc_eth;
	काष्ठा mlx4_spec_qps   *spec_qps;
	पूर्णांक			num_srqs;
	पूर्णांक			max_srq_wqes;
	पूर्णांक			max_srq_sge;
	पूर्णांक			reserved_srqs;
	पूर्णांक			num_cqs;
	पूर्णांक			max_cqes;
	पूर्णांक			reserved_cqs;
	पूर्णांक			num_sys_eqs;
	पूर्णांक			num_eqs;
	पूर्णांक			reserved_eqs;
	पूर्णांक			num_comp_vectors;
	पूर्णांक			num_mpts;
	पूर्णांक			num_mtts;
	पूर्णांक			fmr_reserved_mtts;
	पूर्णांक			reserved_mtts;
	पूर्णांक			reserved_mrws;
	पूर्णांक			reserved_uars;
	पूर्णांक			num_mgms;
	पूर्णांक			num_amgms;
	पूर्णांक			reserved_mcgs;
	पूर्णांक			num_qp_per_mgm;
	पूर्णांक			steering_mode;
	पूर्णांक			dmfs_high_steer_mode;
	पूर्णांक			fs_log_max_ucast_qp_range_size;
	पूर्णांक			num_pds;
	पूर्णांक			reserved_pds;
	पूर्णांक			max_xrcds;
	पूर्णांक			reserved_xrcds;
	पूर्णांक			mtt_entry_sz;
	u32			max_msg_sz;
	u32			page_size_cap;
	u64			flags;
	u64			flags2;
	u32			bmme_flags;
	u32			reserved_lkey;
	u16			stat_rate_support;
	u8			port_width_cap[MLX4_MAX_PORTS + 1];
	पूर्णांक			max_gso_sz;
	पूर्णांक			max_rss_tbl_sz;
	पूर्णांक                     reserved_qps_cnt[MLX4_NUM_QP_REGION];
	पूर्णांक			reserved_qps;
	पूर्णांक                     reserved_qps_base[MLX4_NUM_QP_REGION];
	पूर्णांक                     log_num_macs;
	पूर्णांक                     log_num_vlans;
	क्रमागत mlx4_port_type	port_type[MLX4_MAX_PORTS + 1];
	u8			supported_type[MLX4_MAX_PORTS + 1];
	u8                      suggested_type[MLX4_MAX_PORTS + 1];
	u8                      शेष_sense[MLX4_MAX_PORTS + 1];
	u32			port_mask[MLX4_MAX_PORTS + 1];
	क्रमागत mlx4_port_type	possible_type[MLX4_MAX_PORTS + 1];
	u32			max_counters;
	u8			port_ib_mtu[MLX4_MAX_PORTS + 1];
	u16			sqp_demux;
	u32			eqe_size;
	u32			cqe_size;
	u8			eqe_factor;
	u32			userspace_caps; /* userspace must be aware of these */
	u32			function_caps;  /* VFs must be aware of these */
	u16			hca_core_घड़ी;
	u64			phys_port_id[MLX4_MAX_PORTS + 1];
	पूर्णांक			tunnel_offload_mode;
	u8			rx_checksum_flags_port[MLX4_MAX_PORTS + 1];
	u8			phv_bit[MLX4_MAX_PORTS + 1];
	u8			alloc_res_qp_mask;
	u32			dmfs_high_rate_qpn_base;
	u32			dmfs_high_rate_qpn_range;
	u32			vf_caps;
	bool			wol_port[MLX4_MAX_PORTS + 1];
	काष्ठा mlx4_rate_limit_caps rl_caps;
	u32			health_buffer_addrs;
	bool			map_घड़ी_प्रकारo_user;
पूर्ण;

काष्ठा mlx4_buf_list अणु
	व्योम		       *buf;
	dma_addr_t		map;
पूर्ण;

काष्ठा mlx4_buf अणु
	काष्ठा mlx4_buf_list	direct;
	काष्ठा mlx4_buf_list   *page_list;
	पूर्णांक			nbufs;
	पूर्णांक			npages;
	पूर्णांक			page_shअगरt;
पूर्ण;

काष्ठा mlx4_mtt अणु
	u32			offset;
	पूर्णांक			order;
	पूर्णांक			page_shअगरt;
पूर्ण;

क्रमागत अणु
	MLX4_DB_PER_PAGE = PAGE_SIZE / 4
पूर्ण;

काष्ठा mlx4_db_pgdir अणु
	काष्ठा list_head	list;
	DECLARE_BITMAP(order0, MLX4_DB_PER_PAGE);
	DECLARE_BITMAP(order1, MLX4_DB_PER_PAGE / 2);
	अचिन्हित दीर्घ	       *bits[2];
	__be32		       *db_page;
	dma_addr_t		db_dma;
पूर्ण;

काष्ठा mlx4_ib_user_db_page;

काष्ठा mlx4_db अणु
	__be32			*db;
	जोड़ अणु
		काष्ठा mlx4_db_pgdir		*pgdir;
		काष्ठा mlx4_ib_user_db_page	*user_page;
	पूर्ण			u;
	dma_addr_t		dma;
	पूर्णांक			index;
	पूर्णांक			order;
पूर्ण;

काष्ठा mlx4_hwq_resources अणु
	काष्ठा mlx4_db		db;
	काष्ठा mlx4_mtt		mtt;
	काष्ठा mlx4_buf		buf;
पूर्ण;

काष्ठा mlx4_mr अणु
	काष्ठा mlx4_mtt		mtt;
	u64			iova;
	u64			size;
	u32			key;
	u32			pd;
	u32			access;
	पूर्णांक			enabled;
पूर्ण;

क्रमागत mlx4_mw_type अणु
	MLX4_MW_TYPE_1 = 1,
	MLX4_MW_TYPE_2 = 2,
पूर्ण;

काष्ठा mlx4_mw अणु
	u32			key;
	u32			pd;
	क्रमागत mlx4_mw_type	type;
	पूर्णांक			enabled;
पूर्ण;

काष्ठा mlx4_uar अणु
	अचिन्हित दीर्घ		pfn;
	पूर्णांक			index;
	काष्ठा list_head	bf_list;
	अचिन्हित		मुक्त_bf_bmap;
	व्योम __iomem	       *map;
	व्योम __iomem	       *bf_map;
पूर्ण;

काष्ठा mlx4_bf अणु
	अचिन्हित पूर्णांक		offset;
	पूर्णांक			buf_size;
	काष्ठा mlx4_uar	       *uar;
	व्योम __iomem	       *reg;
पूर्ण;

काष्ठा mlx4_cq अणु
	व्योम (*comp)		(काष्ठा mlx4_cq *);
	व्योम (*event)		(काष्ठा mlx4_cq *, क्रमागत mlx4_event);

	काष्ठा mlx4_uar	       *uar;

	u32			cons_index;

	u16                     irq;
	__be32		       *set_ci_db;
	__be32		       *arm_db;
	पूर्णांक			arm_sn;

	पूर्णांक			cqn;
	अचिन्हित		vector;

	refcount_t		refcount;
	काष्ठा completion	मुक्त;
	काष्ठा अणु
		काष्ठा list_head list;
		व्योम (*comp)(काष्ठा mlx4_cq *);
		व्योम		*priv;
	पूर्ण tasklet_ctx;
	पूर्णांक		reset_notअगरy_added;
	काष्ठा list_head	reset_notअगरy;
	u8			usage;
पूर्ण;

काष्ठा mlx4_qp अणु
	व्योम (*event)		(काष्ठा mlx4_qp *, क्रमागत mlx4_event);

	पूर्णांक			qpn;

	refcount_t		refcount;
	काष्ठा completion	मुक्त;
	u8			usage;
पूर्ण;

काष्ठा mlx4_srq अणु
	व्योम (*event)		(काष्ठा mlx4_srq *, क्रमागत mlx4_event);

	पूर्णांक			srqn;
	पूर्णांक			max;
	पूर्णांक			max_gs;
	पूर्णांक			wqe_shअगरt;

	refcount_t		refcount;
	काष्ठा completion	मुक्त;
पूर्ण;

काष्ठा mlx4_av अणु
	__be32			port_pd;
	u8			reserved1;
	u8			g_slid;
	__be16			dlid;
	u8			reserved2;
	u8			gid_index;
	u8			stat_rate;
	u8			hop_limit;
	__be32			sl_tclass_flowlabel;
	u8			dgid[16];
पूर्ण;

काष्ठा mlx4_eth_av अणु
	__be32		port_pd;
	u8		reserved1;
	u8		smac_idx;
	u16		reserved2;
	u8		reserved3;
	u8		gid_index;
	u8		stat_rate;
	u8		hop_limit;
	__be32		sl_tclass_flowlabel;
	u8		dgid[16];
	u8		s_mac[6];
	u8		reserved4[2];
	__be16		vlan;
	u8		mac[ETH_ALEN];
पूर्ण;

जोड़ mlx4_ext_av अणु
	काष्ठा mlx4_av		ib;
	काष्ठा mlx4_eth_av	eth;
पूर्ण;

/* Counters should be saturate once they reach their maximum value */
#घोषणा ASSIGN_32BIT_COUNTER(counter, value) करो अणु	\
	अगर ((value) > U32_MAX)				\
		counter = cpu_to_be32(U32_MAX);		\
	अन्यथा						\
		counter = cpu_to_be32(value);		\
पूर्ण जबतक (0)

काष्ठा mlx4_counter अणु
	u8	reserved1[3];
	u8	counter_mode;
	__be32	num_अगरc;
	u32	reserved2[2];
	__be64	rx_frames;
	__be64	rx_bytes;
	__be64	tx_frames;
	__be64	tx_bytes;
पूर्ण;

काष्ठा mlx4_quotas अणु
	पूर्णांक qp;
	पूर्णांक cq;
	पूर्णांक srq;
	पूर्णांक mpt;
	पूर्णांक mtt;
	पूर्णांक counter;
	पूर्णांक xrcd;
पूर्ण;

काष्ठा mlx4_vf_dev अणु
	u8			min_port;
	u8			n_ports;
पूर्ण;

काष्ठा mlx4_fw_crdump अणु
	bool snapshot_enable;
	काष्ठा devlink_region *region_crspace;
	काष्ठा devlink_region *region_fw_health;
पूर्ण;

क्रमागत mlx4_pci_status अणु
	MLX4_PCI_STATUS_DISABLED,
	MLX4_PCI_STATUS_ENABLED,
पूर्ण;

काष्ठा mlx4_dev_persistent अणु
	काष्ठा pci_dev	       *pdev;
	काष्ठा mlx4_dev	       *dev;
	पूर्णांक                     nvfs[MLX4_MAX_PORTS + 1];
	पूर्णांक			num_vfs;
	क्रमागत mlx4_port_type curr_port_type[MLX4_MAX_PORTS + 1];
	क्रमागत mlx4_port_type curr_port_poss_type[MLX4_MAX_PORTS + 1];
	काष्ठा work_काष्ठा      catas_work;
	काष्ठा workqueue_काष्ठा *catas_wq;
	काष्ठा mutex	device_state_mutex; /* protect HW state */
	u8		state;
	काष्ठा mutex	पूर्णांकerface_state_mutex; /* protect SW state */
	u8	पूर्णांकerface_state;
	काष्ठा mutex		pci_status_mutex; /* sync pci state */
	क्रमागत mlx4_pci_status	pci_status;
	काष्ठा mlx4_fw_crdump	crdump;
पूर्ण;

काष्ठा mlx4_dev अणु
	काष्ठा mlx4_dev_persistent *persist;
	अचिन्हित दीर्घ		flags;
	अचिन्हित दीर्घ		num_slaves;
	काष्ठा mlx4_caps	caps;
	काष्ठा mlx4_phys_caps	phys_caps;
	काष्ठा mlx4_quotas	quotas;
	काष्ठा radix_tree_root	qp_table_tree;
	u8			rev_id;
	u8			port_अक्रमom_macs;
	अक्षर			board_id[MLX4_BOARD_ID_LEN];
	पूर्णांक			numa_node;
	पूर्णांक			oper_log_mgm_entry_size;
	u64			regid_promisc_array[MLX4_MAX_PORTS + 1];
	u64			regid_allmulti_array[MLX4_MAX_PORTS + 1];
	काष्ठा mlx4_vf_dev     *dev_vfs;
	u8  uar_page_shअगरt;
पूर्ण;

काष्ठा mlx4_घड़ी_params अणु
	u64 offset;
	u8 bar;
	u8 size;
पूर्ण;

काष्ठा mlx4_eqe अणु
	u8			reserved1;
	u8			type;
	u8			reserved2;
	u8			subtype;
	जोड़ अणु
		u32		raw[6];
		काष्ठा अणु
			__be32	cqn;
		पूर्ण __packed comp;
		काष्ठा अणु
			u16	reserved1;
			__be16	token;
			u32	reserved2;
			u8	reserved3[3];
			u8	status;
			__be64	out_param;
		पूर्ण __packed cmd;
		काष्ठा अणु
			__be32	qpn;
		पूर्ण __packed qp;
		काष्ठा अणु
			__be32	srqn;
		पूर्ण __packed srq;
		काष्ठा अणु
			__be32	cqn;
			u32	reserved1;
			u8	reserved2[3];
			u8	syndrome;
		पूर्ण __packed cq_err;
		काष्ठा अणु
			u32	reserved1[2];
			__be32	port;
		पूर्ण __packed port_change;
		काष्ठा अणु
			#घोषणा COMM_CHANNEL_BIT_ARRAY_SIZE	4
			u32 reserved;
			u32 bit_vec[COMM_CHANNEL_BIT_ARRAY_SIZE];
		पूर्ण __packed comm_channel_arm;
		काष्ठा अणु
			u8	port;
			u8	reserved[3];
			__be64	mac;
		पूर्ण __packed mac_update;
		काष्ठा अणु
			__be32	slave_id;
		पूर्ण __packed flr_event;
		काष्ठा अणु
			__be16  current_temperature;
			__be16  warning_threshold;
		पूर्ण __packed warming;
		काष्ठा अणु
			u8 reserved[3];
			u8 port;
			जोड़ अणु
				काष्ठा अणु
					__be16 mstr_sm_lid;
					__be16 port_lid;
					__be32 changed_attr;
					u8 reserved[3];
					u8 mstr_sm_sl;
					__be64 gid_prefix;
				पूर्ण __packed port_info;
				काष्ठा अणु
					__be32 block_ptr;
					__be32 tbl_entries_mask;
				पूर्ण __packed tbl_change_info;
				काष्ठा अणु
					u8 sl2vl_table[8];
				पूर्ण __packed sl2vl_tbl_change_info;
			पूर्ण params;
		पूर्ण __packed port_mgmt_change;
		काष्ठा अणु
			u8 reserved[3];
			u8 port;
			u32 reserved1[5];
		पूर्ण __packed bad_cable;
	पूर्ण			event;
	u8			slave_id;
	u8			reserved3[2];
	u8			owner;
पूर्ण __packed;

काष्ठा mlx4_init_port_param अणु
	पूर्णांक			set_guid0;
	पूर्णांक			set_node_guid;
	पूर्णांक			set_si_guid;
	u16			mtu;
	पूर्णांक			port_width_cap;
	u16			vl_cap;
	u16			max_gid;
	u16			max_pkey;
	u64			guid0;
	u64			node_guid;
	u64			si_guid;
पूर्ण;

#घोषणा MAD_IFC_DATA_SZ 192
/* MAD IFC Mailbox */
काष्ठा mlx4_mad_अगरc अणु
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
	__be64	mkey;
	__be16	dr_slid;
	__be16	dr_dlid;
	u8	reserved[28];
	u8	data[MAD_IFC_DATA_SZ];
पूर्ण __packed;

#घोषणा mlx4_क्रमeach_port(port, dev, type)				\
	क्रम ((port) = 1; (port) <= (dev)->caps.num_ports; (port)++)	\
		अगर ((type) == (dev)->caps.port_mask[(port)])

#घोषणा mlx4_क्रमeach_ib_transport_port(port, dev)                         \
	क्रम ((port) = 1; (port) <= (dev)->caps.num_ports; (port)++)       \
		अगर (((dev)->caps.port_mask[port] == MLX4_PORT_TYPE_IB) || \
		    ((dev)->caps.port_mask[port] == MLX4_PORT_TYPE_ETH))

#घोषणा MLX4_INVALID_SLAVE_ID	0xFF
#घोषणा MLX4_SINK_COUNTER_INDEX(dev)	(dev->caps.max_counters - 1)

व्योम handle_port_mgmt_change_event(काष्ठा work_काष्ठा *work);

अटल अंतरभूत पूर्णांक mlx4_master_func_num(काष्ठा mlx4_dev *dev)
अणु
	वापस dev->caps.function;
पूर्ण

अटल अंतरभूत पूर्णांक mlx4_is_master(काष्ठा mlx4_dev *dev)
अणु
	वापस dev->flags & MLX4_FLAG_MASTER;
पूर्ण

अटल अंतरभूत पूर्णांक mlx4_num_reserved_sqps(काष्ठा mlx4_dev *dev)
अणु
	वापस dev->phys_caps.base_sqpn + 8 +
		16 * MLX4_MFUNC_MAX * !!mlx4_is_master(dev);
पूर्ण

अटल अंतरभूत पूर्णांक mlx4_is_qp_reserved(काष्ठा mlx4_dev *dev, u32 qpn)
अणु
	वापस (qpn < dev->phys_caps.base_sqpn + 8 +
		16 * MLX4_MFUNC_MAX * !!mlx4_is_master(dev) &&
		qpn >= dev->phys_caps.base_sqpn) ||
	       (qpn < dev->caps.reserved_qps_cnt[MLX4_QP_REGION_FW]);
पूर्ण

अटल अंतरभूत पूर्णांक mlx4_is_guest_proxy(काष्ठा mlx4_dev *dev, पूर्णांक slave, u32 qpn)
अणु
	पूर्णांक guest_proxy_base = dev->phys_caps.base_proxy_sqpn + slave * 8;

	अगर (qpn >= guest_proxy_base && qpn < guest_proxy_base + 8)
		वापस 1;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक mlx4_is_mfunc(काष्ठा mlx4_dev *dev)
अणु
	वापस dev->flags & (MLX4_FLAG_SLAVE | MLX4_FLAG_MASTER);
पूर्ण

अटल अंतरभूत पूर्णांक mlx4_is_slave(काष्ठा mlx4_dev *dev)
अणु
	वापस dev->flags & MLX4_FLAG_SLAVE;
पूर्ण

अटल अंतरभूत पूर्णांक mlx4_is_eth(काष्ठा mlx4_dev *dev, पूर्णांक port)
अणु
	वापस dev->caps.port_type[port] == MLX4_PORT_TYPE_IB ? 0 : 1;
पूर्ण

पूर्णांक mlx4_buf_alloc(काष्ठा mlx4_dev *dev, पूर्णांक size, पूर्णांक max_direct,
		   काष्ठा mlx4_buf *buf);
व्योम mlx4_buf_मुक्त(काष्ठा mlx4_dev *dev, पूर्णांक size, काष्ठा mlx4_buf *buf);
अटल अंतरभूत व्योम *mlx4_buf_offset(काष्ठा mlx4_buf *buf, पूर्णांक offset)
अणु
	अगर (buf->nbufs == 1)
		वापस buf->direct.buf + offset;
	अन्यथा
		वापस buf->page_list[offset >> PAGE_SHIFT].buf +
			(offset & (PAGE_SIZE - 1));
पूर्ण

पूर्णांक mlx4_pd_alloc(काष्ठा mlx4_dev *dev, u32 *pdn);
व्योम mlx4_pd_मुक्त(काष्ठा mlx4_dev *dev, u32 pdn);
पूर्णांक mlx4_xrcd_alloc(काष्ठा mlx4_dev *dev, u32 *xrcdn);
व्योम mlx4_xrcd_मुक्त(काष्ठा mlx4_dev *dev, u32 xrcdn);

पूर्णांक mlx4_uar_alloc(काष्ठा mlx4_dev *dev, काष्ठा mlx4_uar *uar);
व्योम mlx4_uar_मुक्त(काष्ठा mlx4_dev *dev, काष्ठा mlx4_uar *uar);
पूर्णांक mlx4_bf_alloc(काष्ठा mlx4_dev *dev, काष्ठा mlx4_bf *bf, पूर्णांक node);
व्योम mlx4_bf_मुक्त(काष्ठा mlx4_dev *dev, काष्ठा mlx4_bf *bf);

पूर्णांक mlx4_mtt_init(काष्ठा mlx4_dev *dev, पूर्णांक npages, पूर्णांक page_shअगरt,
		  काष्ठा mlx4_mtt *mtt);
व्योम mlx4_mtt_cleanup(काष्ठा mlx4_dev *dev, काष्ठा mlx4_mtt *mtt);
u64 mlx4_mtt_addr(काष्ठा mlx4_dev *dev, काष्ठा mlx4_mtt *mtt);

पूर्णांक mlx4_mr_alloc(काष्ठा mlx4_dev *dev, u32 pd, u64 iova, u64 size, u32 access,
		  पूर्णांक npages, पूर्णांक page_shअगरt, काष्ठा mlx4_mr *mr);
पूर्णांक mlx4_mr_मुक्त(काष्ठा mlx4_dev *dev, काष्ठा mlx4_mr *mr);
पूर्णांक mlx4_mr_enable(काष्ठा mlx4_dev *dev, काष्ठा mlx4_mr *mr);
पूर्णांक mlx4_mw_alloc(काष्ठा mlx4_dev *dev, u32 pd, क्रमागत mlx4_mw_type type,
		  काष्ठा mlx4_mw *mw);
व्योम mlx4_mw_मुक्त(काष्ठा mlx4_dev *dev, काष्ठा mlx4_mw *mw);
पूर्णांक mlx4_mw_enable(काष्ठा mlx4_dev *dev, काष्ठा mlx4_mw *mw);
पूर्णांक mlx4_ग_लिखो_mtt(काष्ठा mlx4_dev *dev, काष्ठा mlx4_mtt *mtt,
		   पूर्णांक start_index, पूर्णांक npages, u64 *page_list);
पूर्णांक mlx4_buf_ग_लिखो_mtt(काष्ठा mlx4_dev *dev, काष्ठा mlx4_mtt *mtt,
		       काष्ठा mlx4_buf *buf);

पूर्णांक mlx4_db_alloc(काष्ठा mlx4_dev *dev, काष्ठा mlx4_db *db, पूर्णांक order);
व्योम mlx4_db_मुक्त(काष्ठा mlx4_dev *dev, काष्ठा mlx4_db *db);

पूर्णांक mlx4_alloc_hwq_res(काष्ठा mlx4_dev *dev, काष्ठा mlx4_hwq_resources *wqres,
		       पूर्णांक size);
व्योम mlx4_मुक्त_hwq_res(काष्ठा mlx4_dev *mdev, काष्ठा mlx4_hwq_resources *wqres,
		       पूर्णांक size);

पूर्णांक mlx4_cq_alloc(काष्ठा mlx4_dev *dev, पूर्णांक nent, काष्ठा mlx4_mtt *mtt,
		  काष्ठा mlx4_uar *uar, u64 db_rec, काष्ठा mlx4_cq *cq,
		  अचिन्हित पूर्णांक vector, पूर्णांक collapsed, पूर्णांक बारtamp_en,
		  व्योम *buf_addr, bool user_cq);
व्योम mlx4_cq_मुक्त(काष्ठा mlx4_dev *dev, काष्ठा mlx4_cq *cq);
पूर्णांक mlx4_qp_reserve_range(काष्ठा mlx4_dev *dev, पूर्णांक cnt, पूर्णांक align,
			  पूर्णांक *base, u8 flags, u8 usage);
व्योम mlx4_qp_release_range(काष्ठा mlx4_dev *dev, पूर्णांक base_qpn, पूर्णांक cnt);

पूर्णांक mlx4_qp_alloc(काष्ठा mlx4_dev *dev, पूर्णांक qpn, काष्ठा mlx4_qp *qp);
व्योम mlx4_qp_मुक्त(काष्ठा mlx4_dev *dev, काष्ठा mlx4_qp *qp);

पूर्णांक mlx4_srq_alloc(काष्ठा mlx4_dev *dev, u32 pdn, u32 cqn, u16 xrcdn,
		   काष्ठा mlx4_mtt *mtt, u64 db_rec, काष्ठा mlx4_srq *srq);
व्योम mlx4_srq_मुक्त(काष्ठा mlx4_dev *dev, काष्ठा mlx4_srq *srq);
पूर्णांक mlx4_srq_arm(काष्ठा mlx4_dev *dev, काष्ठा mlx4_srq *srq, पूर्णांक limit_watermark);
पूर्णांक mlx4_srq_query(काष्ठा mlx4_dev *dev, काष्ठा mlx4_srq *srq, पूर्णांक *limit_watermark);

पूर्णांक mlx4_INIT_PORT(काष्ठा mlx4_dev *dev, पूर्णांक port);
पूर्णांक mlx4_CLOSE_PORT(काष्ठा mlx4_dev *dev, पूर्णांक port);

पूर्णांक mlx4_unicast_attach(काष्ठा mlx4_dev *dev, काष्ठा mlx4_qp *qp, u8 gid[16],
			पूर्णांक block_mcast_loopback, क्रमागत mlx4_protocol prot);
पूर्णांक mlx4_unicast_detach(काष्ठा mlx4_dev *dev, काष्ठा mlx4_qp *qp, u8 gid[16],
			क्रमागत mlx4_protocol prot);
पूर्णांक mlx4_multicast_attach(काष्ठा mlx4_dev *dev, काष्ठा mlx4_qp *qp, u8 gid[16],
			  u8 port, पूर्णांक block_mcast_loopback,
			  क्रमागत mlx4_protocol protocol, u64 *reg_id);
पूर्णांक mlx4_multicast_detach(काष्ठा mlx4_dev *dev, काष्ठा mlx4_qp *qp, u8 gid[16],
			  क्रमागत mlx4_protocol protocol, u64 reg_id);

क्रमागत अणु
	MLX4_DOMAIN_UVERBS	= 0x1000,
	MLX4_DOMAIN_ETHTOOL     = 0x2000,
	MLX4_DOMAIN_RFS         = 0x3000,
	MLX4_DOMAIN_NIC    = 0x5000,
पूर्ण;

क्रमागत mlx4_net_trans_rule_id अणु
	MLX4_NET_TRANS_RULE_ID_ETH = 0,
	MLX4_NET_TRANS_RULE_ID_IB,
	MLX4_NET_TRANS_RULE_ID_IPV6,
	MLX4_NET_TRANS_RULE_ID_IPV4,
	MLX4_NET_TRANS_RULE_ID_TCP,
	MLX4_NET_TRANS_RULE_ID_UDP,
	MLX4_NET_TRANS_RULE_ID_VXLAN,
	MLX4_NET_TRANS_RULE_NUM, /* should be last */
पूर्ण;

बाह्य स्थिर u16 __sw_id_hw[];

अटल अंतरभूत पूर्णांक map_hw_to_sw_id(u16 header_id)
अणु

	पूर्णांक i;
	क्रम (i = 0; i < MLX4_NET_TRANS_RULE_NUM; i++) अणु
		अगर (header_id == __sw_id_hw[i])
			वापस i;
	पूर्ण
	वापस -EINVAL;
पूर्ण

क्रमागत mlx4_net_trans_promisc_mode अणु
	MLX4_FS_REGULAR = 1,
	MLX4_FS_ALL_DEFAULT,
	MLX4_FS_MC_DEFAULT,
	MLX4_FS_MIRROR_RX_PORT,
	MLX4_FS_MIRROR_SX_PORT,
	MLX4_FS_UC_SNIFFER,
	MLX4_FS_MC_SNIFFER,
	MLX4_FS_MODE_NUM, /* should be last */
पूर्ण;

काष्ठा mlx4_spec_eth अणु
	u8	dst_mac[ETH_ALEN];
	u8	dst_mac_msk[ETH_ALEN];
	u8	src_mac[ETH_ALEN];
	u8	src_mac_msk[ETH_ALEN];
	u8	ether_type_enable;
	__be16	ether_type;
	__be16	vlan_id_msk;
	__be16	vlan_id;
पूर्ण;

काष्ठा mlx4_spec_tcp_udp अणु
	__be16 dst_port;
	__be16 dst_port_msk;
	__be16 src_port;
	__be16 src_port_msk;
पूर्ण;

काष्ठा mlx4_spec_ipv4 अणु
	__be32 dst_ip;
	__be32 dst_ip_msk;
	__be32 src_ip;
	__be32 src_ip_msk;
पूर्ण;

काष्ठा mlx4_spec_ib अणु
	__be32  l3_qpn;
	__be32	qpn_msk;
	u8	dst_gid[16];
	u8	dst_gid_msk[16];
पूर्ण;

काष्ठा mlx4_spec_vxlan अणु
	__be32 vni;
	__be32 vni_mask;

पूर्ण;

काष्ठा mlx4_spec_list अणु
	काष्ठा	list_head list;
	क्रमागत	mlx4_net_trans_rule_id id;
	जोड़ अणु
		काष्ठा mlx4_spec_eth eth;
		काष्ठा mlx4_spec_ib ib;
		काष्ठा mlx4_spec_ipv4 ipv4;
		काष्ठा mlx4_spec_tcp_udp tcp_udp;
		काष्ठा mlx4_spec_vxlan vxlan;
	पूर्ण;
पूर्ण;

क्रमागत mlx4_net_trans_hw_rule_queue अणु
	MLX4_NET_TRANS_Q_FIFO,
	MLX4_NET_TRANS_Q_LIFO,
पूर्ण;

काष्ठा mlx4_net_trans_rule अणु
	काष्ठा	list_head list;
	क्रमागत	mlx4_net_trans_hw_rule_queue queue_mode;
	bool	exclusive;
	bool	allow_loopback;
	क्रमागत	mlx4_net_trans_promisc_mode promisc_mode;
	u8	port;
	u16	priority;
	u32	qpn;
पूर्ण;

काष्ठा mlx4_net_trans_rule_hw_ctrl अणु
	__be16 prio;
	u8 type;
	u8 flags;
	u8 rsvd1;
	u8 funcid;
	u8 vep;
	u8 port;
	__be32 qpn;
	__be32 rsvd2;
पूर्ण;

काष्ठा mlx4_net_trans_rule_hw_ib अणु
	u8 size;
	u8 rsvd1;
	__be16 id;
	u32 rsvd2;
	__be32 l3_qpn;
	__be32 qpn_mask;
	u8 dst_gid[16];
	u8 dst_gid_msk[16];
पूर्ण __packed;

काष्ठा mlx4_net_trans_rule_hw_eth अणु
	u8	size;
	u8	rsvd;
	__be16	id;
	u8	rsvd1[6];
	u8	dst_mac[6];
	u16	rsvd2;
	u8	dst_mac_msk[6];
	u16	rsvd3;
	u8	src_mac[6];
	u16	rsvd4;
	u8	src_mac_msk[6];
	u8      rsvd5;
	u8      ether_type_enable;
	__be16  ether_type;
	__be16  vlan_tag_msk;
	__be16  vlan_tag;
पूर्ण __packed;

काष्ठा mlx4_net_trans_rule_hw_tcp_udp अणु
	u8	size;
	u8	rsvd;
	__be16	id;
	__be16	rsvd1[3];
	__be16	dst_port;
	__be16	rsvd2;
	__be16	dst_port_msk;
	__be16	rsvd3;
	__be16	src_port;
	__be16	rsvd4;
	__be16	src_port_msk;
पूर्ण __packed;

काष्ठा mlx4_net_trans_rule_hw_ipv4 अणु
	u8	size;
	u8	rsvd;
	__be16	id;
	__be32	rsvd1;
	__be32	dst_ip;
	__be32	dst_ip_msk;
	__be32	src_ip;
	__be32	src_ip_msk;
पूर्ण __packed;

काष्ठा mlx4_net_trans_rule_hw_vxlan अणु
	u8	size;
	u8	rsvd;
	__be16	id;
	__be32	rsvd1;
	__be32	vni;
	__be32	vni_mask;
पूर्ण __packed;

काष्ठा _rule_hw अणु
	जोड़ अणु
		काष्ठा अणु
			u8 size;
			u8 rsvd;
			__be16 id;
		पूर्ण;
		काष्ठा mlx4_net_trans_rule_hw_eth eth;
		काष्ठा mlx4_net_trans_rule_hw_ib ib;
		काष्ठा mlx4_net_trans_rule_hw_ipv4 ipv4;
		काष्ठा mlx4_net_trans_rule_hw_tcp_udp tcp_udp;
		काष्ठा mlx4_net_trans_rule_hw_vxlan vxlan;
	पूर्ण;
पूर्ण;

क्रमागत अणु
	VXLAN_STEER_BY_OUTER_MAC	= 1 << 0,
	VXLAN_STEER_BY_OUTER_VLAN	= 1 << 1,
	VXLAN_STEER_BY_VSID_VNI		= 1 << 2,
	VXLAN_STEER_BY_INNER_MAC	= 1 << 3,
	VXLAN_STEER_BY_INNER_VLAN	= 1 << 4,
पूर्ण;

क्रमागत अणु
	MLX4_OP_MOD_QUERY_TRANSPORT_CI_ERRORS = 0x2,
पूर्ण;

पूर्णांक mlx4_flow_steer_promisc_add(काष्ठा mlx4_dev *dev, u8 port, u32 qpn,
				क्रमागत mlx4_net_trans_promisc_mode mode);
पूर्णांक mlx4_flow_steer_promisc_हटाओ(काष्ठा mlx4_dev *dev, u8 port,
				   क्रमागत mlx4_net_trans_promisc_mode mode);
पूर्णांक mlx4_multicast_promisc_add(काष्ठा mlx4_dev *dev, u32 qpn, u8 port);
पूर्णांक mlx4_multicast_promisc_हटाओ(काष्ठा mlx4_dev *dev, u32 qpn, u8 port);
पूर्णांक mlx4_unicast_promisc_add(काष्ठा mlx4_dev *dev, u32 qpn, u8 port);
पूर्णांक mlx4_unicast_promisc_हटाओ(काष्ठा mlx4_dev *dev, u32 qpn, u8 port);
पूर्णांक mlx4_SET_MCAST_FLTR(काष्ठा mlx4_dev *dev, u8 port, u64 mac, u64 clear, u8 mode);

पूर्णांक mlx4_रेजिस्टर_mac(काष्ठा mlx4_dev *dev, u8 port, u64 mac);
व्योम mlx4_unरेजिस्टर_mac(काष्ठा mlx4_dev *dev, u8 port, u64 mac);
पूर्णांक mlx4_get_base_qpn(काष्ठा mlx4_dev *dev, u8 port);
पूर्णांक __mlx4_replace_mac(काष्ठा mlx4_dev *dev, u8 port, पूर्णांक qpn, u64 new_mac);
पूर्णांक mlx4_SET_PORT_general(काष्ठा mlx4_dev *dev, u8 port, पूर्णांक mtu,
			  u8 pptx, u8 pfctx, u8 pprx, u8 pfcrx);
पूर्णांक mlx4_SET_PORT_user_mac(काष्ठा mlx4_dev *dev, u8 port, u8 *user_mac);
पूर्णांक mlx4_SET_PORT_user_mtu(काष्ठा mlx4_dev *dev, u8 port, u16 user_mtu);
पूर्णांक mlx4_SET_PORT_qpn_calc(काष्ठा mlx4_dev *dev, u8 port, u32 base_qpn,
			   u8 promisc);
पूर्णांक mlx4_SET_PORT_BEACON(काष्ठा mlx4_dev *dev, u8 port, u16 समय);
पूर्णांक mlx4_SET_PORT_fcs_check(काष्ठा mlx4_dev *dev, u8 port,
			    u8 ignore_fcs_value);
पूर्णांक mlx4_SET_PORT_VXLAN(काष्ठा mlx4_dev *dev, u8 port, u8 steering, पूर्णांक enable);
पूर्णांक set_phv_bit(काष्ठा mlx4_dev *dev, u8 port, पूर्णांक new_val);
पूर्णांक get_phv_bit(काष्ठा mlx4_dev *dev, u8 port, पूर्णांक *phv);
पूर्णांक mlx4_get_is_vlan_offload_disabled(काष्ठा mlx4_dev *dev, u8 port,
				      bool *vlan_offload_disabled);
व्योम mlx4_handle_eth_header_mcast_prio(काष्ठा mlx4_net_trans_rule_hw_ctrl *ctrl,
				       काष्ठा _rule_hw *eth_header);
पूर्णांक mlx4_find_cached_mac(काष्ठा mlx4_dev *dev, u8 port, u64 mac, पूर्णांक *idx);
पूर्णांक mlx4_find_cached_vlan(काष्ठा mlx4_dev *dev, u8 port, u16 vid, पूर्णांक *idx);
पूर्णांक mlx4_रेजिस्टर_vlan(काष्ठा mlx4_dev *dev, u8 port, u16 vlan, पूर्णांक *index);
व्योम mlx4_unरेजिस्टर_vlan(काष्ठा mlx4_dev *dev, u8 port, u16 vlan);

पूर्णांक mlx4_SYNC_TPT(काष्ठा mlx4_dev *dev);
पूर्णांक mlx4_test_पूर्णांकerrupt(काष्ठा mlx4_dev *dev, पूर्णांक vector);
पूर्णांक mlx4_test_async(काष्ठा mlx4_dev *dev);
पूर्णांक mlx4_query_diag_counters(काष्ठा mlx4_dev *dev, u8 op_modअगरier,
			     स्थिर u32 offset[], u32 value[],
			     माप_प्रकार array_len, u8 port);
u32 mlx4_get_eqs_per_port(काष्ठा mlx4_dev *dev, u8 port);
bool mlx4_is_eq_vector_valid(काष्ठा mlx4_dev *dev, u8 port, पूर्णांक vector);
काष्ठा cpu_rmap *mlx4_get_cpu_rmap(काष्ठा mlx4_dev *dev, पूर्णांक port);
पूर्णांक mlx4_assign_eq(काष्ठा mlx4_dev *dev, u8 port, पूर्णांक *vector);
व्योम mlx4_release_eq(काष्ठा mlx4_dev *dev, पूर्णांक vec);

पूर्णांक mlx4_is_eq_shared(काष्ठा mlx4_dev *dev, पूर्णांक vector);
पूर्णांक mlx4_eq_get_irq(काष्ठा mlx4_dev *dev, पूर्णांक vec);

पूर्णांक mlx4_get_phys_port_id(काष्ठा mlx4_dev *dev);
पूर्णांक mlx4_wol_पढ़ो(काष्ठा mlx4_dev *dev, u64 *config, पूर्णांक port);
पूर्णांक mlx4_wol_ग_लिखो(काष्ठा mlx4_dev *dev, u64 config, पूर्णांक port);

पूर्णांक mlx4_counter_alloc(काष्ठा mlx4_dev *dev, u32 *idx, u8 usage);
व्योम mlx4_counter_मुक्त(काष्ठा mlx4_dev *dev, u32 idx);
पूर्णांक mlx4_get_शेष_counter_index(काष्ठा mlx4_dev *dev, पूर्णांक port);

व्योम mlx4_set_admin_guid(काष्ठा mlx4_dev *dev, __be64 guid, पूर्णांक entry,
			 पूर्णांक port);
__be64 mlx4_get_admin_guid(काष्ठा mlx4_dev *dev, पूर्णांक entry, पूर्णांक port);
व्योम mlx4_set_अक्रमom_admin_guid(काष्ठा mlx4_dev *dev, पूर्णांक entry, पूर्णांक port);
पूर्णांक mlx4_flow_attach(काष्ठा mlx4_dev *dev,
		     काष्ठा mlx4_net_trans_rule *rule, u64 *reg_id);
पूर्णांक mlx4_flow_detach(काष्ठा mlx4_dev *dev, u64 reg_id);
पूर्णांक mlx4_map_sw_to_hw_steering_mode(काष्ठा mlx4_dev *dev,
				    क्रमागत mlx4_net_trans_promisc_mode flow_type);
पूर्णांक mlx4_map_sw_to_hw_steering_id(काष्ठा mlx4_dev *dev,
				  क्रमागत mlx4_net_trans_rule_id id);
पूर्णांक mlx4_hw_rule_sz(काष्ठा mlx4_dev *dev, क्रमागत mlx4_net_trans_rule_id id);

पूर्णांक mlx4_tunnel_steer_add(काष्ठा mlx4_dev *dev, अचिन्हित अक्षर *addr,
			  पूर्णांक port, पूर्णांक qpn, u16 prio, u64 *reg_id);

व्योम mlx4_sync_pkey_table(काष्ठा mlx4_dev *dev, पूर्णांक slave, पूर्णांक port,
			  पूर्णांक i, पूर्णांक val);

पूर्णांक mlx4_get_parav_qkey(काष्ठा mlx4_dev *dev, u32 qpn, u32 *qkey);

पूर्णांक mlx4_is_slave_active(काष्ठा mlx4_dev *dev, पूर्णांक slave);
पूर्णांक mlx4_gen_pkey_eqe(काष्ठा mlx4_dev *dev, पूर्णांक slave, u8 port);
पूर्णांक mlx4_gen_guid_change_eqe(काष्ठा mlx4_dev *dev, पूर्णांक slave, u8 port);
पूर्णांक mlx4_gen_slaves_port_mgt_ev(काष्ठा mlx4_dev *dev, u8 port, पूर्णांक attr);
पूर्णांक mlx4_gen_port_state_change_eqe(काष्ठा mlx4_dev *dev, पूर्णांक slave, u8 port, u8 port_subtype_change);
क्रमागत slave_port_state mlx4_get_slave_port_state(काष्ठा mlx4_dev *dev, पूर्णांक slave, u8 port);
पूर्णांक set_and_calc_slave_port_state(काष्ठा mlx4_dev *dev, पूर्णांक slave, u8 port, पूर्णांक event, क्रमागत slave_port_gen_event *gen_event);

व्योम mlx4_put_slave_node_guid(काष्ठा mlx4_dev *dev, पूर्णांक slave, __be64 guid);
__be64 mlx4_get_slave_node_guid(काष्ठा mlx4_dev *dev, पूर्णांक slave);

पूर्णांक mlx4_get_slave_from_roce_gid(काष्ठा mlx4_dev *dev, पूर्णांक port, u8 *gid,
				 पूर्णांक *slave_id);
पूर्णांक mlx4_get_roce_gid_from_slave(काष्ठा mlx4_dev *dev, पूर्णांक port, पूर्णांक slave_id,
				 u8 *gid);

पूर्णांक mlx4_FLOW_STEERING_IB_UC_QP_RANGE(काष्ठा mlx4_dev *dev, u32 min_range_qpn,
				      u32 max_range_qpn);

u64 mlx4_पढ़ो_घड़ी(काष्ठा mlx4_dev *dev);

काष्ठा mlx4_active_ports अणु
	DECLARE_BITMAP(ports, MLX4_MAX_PORTS);
पूर्ण;
/* Returns a biपंचांगap of the physical ports which are asचिन्हित to slave */
काष्ठा mlx4_active_ports mlx4_get_active_ports(काष्ठा mlx4_dev *dev, पूर्णांक slave);

/* Returns the physical port that represents the भव port of the slave, */
/* or a value < 0 in हाल of an error. If a slave has 2 ports, the identity */
/* mapping is वापसed.							    */
पूर्णांक mlx4_slave_convert_port(काष्ठा mlx4_dev *dev, पूर्णांक slave, पूर्णांक port);

काष्ठा mlx4_slaves_pport अणु
	DECLARE_BITMAP(slaves, MLX4_MFUNC_MAX);
पूर्ण;
/* Returns a biपंचांगap of all slaves that are asचिन्हित to port. */
काष्ठा mlx4_slaves_pport mlx4_phys_to_slaves_pport(काष्ठा mlx4_dev *dev,
						   पूर्णांक port);

/* Returns a biपंचांगap of all slaves that are asचिन्हित exactly to all the */
/* the ports that are set in crit_ports.			       */
काष्ठा mlx4_slaves_pport mlx4_phys_to_slaves_pport_actv(
		काष्ठा mlx4_dev *dev,
		स्थिर काष्ठा mlx4_active_ports *crit_ports);

/* Returns the slave's भव port that represents the physical port. */
पूर्णांक mlx4_phys_to_slave_port(काष्ठा mlx4_dev *dev, पूर्णांक slave, पूर्णांक port);

पूर्णांक mlx4_get_base_gid_ix(काष्ठा mlx4_dev *dev, पूर्णांक slave, पूर्णांक port);

पूर्णांक mlx4_config_vxlan_port(काष्ठा mlx4_dev *dev, __be16 udp_port);
पूर्णांक mlx4_disable_rx_port_check(काष्ठा mlx4_dev *dev, bool dis);
पूर्णांक mlx4_config_roce_v2_port(काष्ठा mlx4_dev *dev, u16 udp_port);
पूर्णांक mlx4_virt2phy_port_map(काष्ठा mlx4_dev *dev, u32 port1, u32 port2);
पूर्णांक mlx4_vf_smi_enabled(काष्ठा mlx4_dev *dev, पूर्णांक slave, पूर्णांक port);
पूर्णांक mlx4_vf_get_enable_smi_admin(काष्ठा mlx4_dev *dev, पूर्णांक slave, पूर्णांक port);
पूर्णांक mlx4_vf_set_enable_smi_admin(काष्ठा mlx4_dev *dev, पूर्णांक slave, पूर्णांक port,
				 पूर्णांक enable);

काष्ठा mlx4_mpt_entry;
पूर्णांक mlx4_mr_hw_get_mpt(काष्ठा mlx4_dev *dev, काष्ठा mlx4_mr *mmr,
		       काष्ठा mlx4_mpt_entry ***mpt_entry);
पूर्णांक mlx4_mr_hw_ग_लिखो_mpt(काष्ठा mlx4_dev *dev, काष्ठा mlx4_mr *mmr,
			 काष्ठा mlx4_mpt_entry **mpt_entry);
पूर्णांक mlx4_mr_hw_change_pd(काष्ठा mlx4_dev *dev, काष्ठा mlx4_mpt_entry *mpt_entry,
			 u32 pdn);
पूर्णांक mlx4_mr_hw_change_access(काष्ठा mlx4_dev *dev,
			     काष्ठा mlx4_mpt_entry *mpt_entry,
			     u32 access);
व्योम mlx4_mr_hw_put_mpt(काष्ठा mlx4_dev *dev,
			काष्ठा mlx4_mpt_entry **mpt_entry);
व्योम mlx4_mr_rereg_mem_cleanup(काष्ठा mlx4_dev *dev, काष्ठा mlx4_mr *mr);
पूर्णांक mlx4_mr_rereg_mem_ग_लिखो(काष्ठा mlx4_dev *dev, काष्ठा mlx4_mr *mr,
			    u64 iova, u64 size, पूर्णांक npages,
			    पूर्णांक page_shअगरt, काष्ठा mlx4_mpt_entry *mpt_entry);

पूर्णांक mlx4_get_module_info(काष्ठा mlx4_dev *dev, u8 port,
			 u16 offset, u16 size, u8 *data);
पूर्णांक mlx4_max_tc(काष्ठा mlx4_dev *dev);

/* Returns true अगर running in low memory profile (kdump kernel) */
अटल अंतरभूत bool mlx4_low_memory_profile(व्योम)
अणु
	वापस is_kdump_kernel();
पूर्ण

/* ACCESS REG commands */
क्रमागत mlx4_access_reg_method अणु
	MLX4_ACCESS_REG_QUERY = 0x1,
	MLX4_ACCESS_REG_WRITE = 0x2,
पूर्ण;

/* ACCESS PTYS Reg command */
क्रमागत mlx4_ptys_proto अणु
	MLX4_PTYS_IB = 1<<0,
	MLX4_PTYS_EN = 1<<2,
पूर्ण;

क्रमागत mlx4_ptys_flags अणु
	MLX4_PTYS_AN_DISABLE_CAP   = 1 << 5,
	MLX4_PTYS_AN_DISABLE_ADMIN = 1 << 6,
पूर्ण;

काष्ठा mlx4_ptys_reg अणु
	u8 flags;
	u8 local_port;
	u8 resrvd2;
	u8 proto_mask;
	__be32 resrvd3[2];
	__be32 eth_proto_cap;
	__be16 ib_width_cap;
	__be16 ib_speed_cap;
	__be32 resrvd4;
	__be32 eth_proto_admin;
	__be16 ib_width_admin;
	__be16 ib_speed_admin;
	__be32 resrvd5;
	__be32 eth_proto_oper;
	__be16 ib_width_oper;
	__be16 ib_speed_oper;
	__be32 resrvd6;
	__be32 eth_proto_lp_adv;
पूर्ण __packed;

पूर्णांक mlx4_ACCESS_PTYS_REG(काष्ठा mlx4_dev *dev,
			 क्रमागत mlx4_access_reg_method method,
			 काष्ठा mlx4_ptys_reg *ptys_reg);

पूर्णांक mlx4_get_पूर्णांकernal_घड़ी_params(काष्ठा mlx4_dev *dev,
				   काष्ठा mlx4_घड़ी_params *params);

अटल अंतरभूत पूर्णांक mlx4_to_hw_uar_index(काष्ठा mlx4_dev *dev, पूर्णांक index)
अणु
	वापस (index << (PAGE_SHIFT - dev->uar_page_shअगरt));
पूर्ण

अटल अंतरभूत पूर्णांक mlx4_get_num_reserved_uar(काष्ठा mlx4_dev *dev)
अणु
	/* The first 128 UARs are used क्रम EQ करोorbells */
	वापस (128 >> (PAGE_SHIFT - dev->uar_page_shअगरt));
पूर्ण
#पूर्ण_अगर /* MLX4_DEVICE_H */
