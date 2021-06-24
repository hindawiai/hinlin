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

#अगर_अघोषित MLX5_DRIVER_H
#घोषणा MLX5_DRIVER_H

#समावेश <linux/kernel.h>
#समावेश <linux/completion.h>
#समावेश <linux/pci.h>
#समावेश <linux/irq.h>
#समावेश <linux/spinlock_types.h>
#समावेश <linux/semaphore.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/xarray.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/mempool.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/idr.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/refcount.h>
#समावेश <linux/auxiliary_bus.h>

#समावेश <linux/mlx5/device.h>
#समावेश <linux/mlx5/करोorbell.h>
#समावेश <linux/mlx5/eq.h>
#समावेश <linux/समयcounter.h>
#समावेश <linux/ptp_घड़ी_kernel.h>
#समावेश <net/devlink.h>

#घोषणा MLX5_ADEV_NAME "mlx5_core"

क्रमागत अणु
	MLX5_BOARD_ID_LEN = 64,
पूर्ण;

क्रमागत अणु
	/* one minute क्रम the sake of bringup. Generally, commands must always
	 * complete and we may need to increase this समयout value
	 */
	MLX5_CMD_TIMEOUT_MSEC	= 60 * 1000,
	MLX5_CMD_WQ_MAX_NAME	= 32,
पूर्ण;

क्रमागत अणु
	CMD_OWNER_SW		= 0x0,
	CMD_OWNER_HW		= 0x1,
	CMD_STATUS_SUCCESS	= 0,
पूर्ण;

क्रमागत mlx5_sqp_t अणु
	MLX5_SQP_SMI		= 0,
	MLX5_SQP_GSI		= 1,
	MLX5_SQP_IEEE_1588	= 2,
	MLX5_SQP_SNIFFER	= 3,
	MLX5_SQP_SYNC_UMR	= 4,
पूर्ण;

क्रमागत अणु
	MLX5_MAX_PORTS	= 2,
पूर्ण;

क्रमागत अणु
	MLX5_ATOMIC_MODE_OFFSET = 16,
	MLX5_ATOMIC_MODE_IB_COMP = 1,
	MLX5_ATOMIC_MODE_CX = 2,
	MLX5_ATOMIC_MODE_8B = 3,
	MLX5_ATOMIC_MODE_16B = 4,
	MLX5_ATOMIC_MODE_32B = 5,
	MLX5_ATOMIC_MODE_64B = 6,
	MLX5_ATOMIC_MODE_128B = 7,
	MLX5_ATOMIC_MODE_256B = 8,
पूर्ण;

क्रमागत अणु
	MLX5_REG_QPTS            = 0x4002,
	MLX5_REG_QETCR		 = 0x4005,
	MLX5_REG_QTCT		 = 0x400a,
	MLX5_REG_QPDPM           = 0x4013,
	MLX5_REG_QCAM            = 0x4019,
	MLX5_REG_DCBX_PARAM      = 0x4020,
	MLX5_REG_DCBX_APP        = 0x4021,
	MLX5_REG_FPGA_CAP	 = 0x4022,
	MLX5_REG_FPGA_CTRL	 = 0x4023,
	MLX5_REG_FPGA_ACCESS_REG = 0x4024,
	MLX5_REG_CORE_DUMP	 = 0x402e,
	MLX5_REG_PCAP		 = 0x5001,
	MLX5_REG_PMTU		 = 0x5003,
	MLX5_REG_PTYS		 = 0x5004,
	MLX5_REG_PAOS		 = 0x5006,
	MLX5_REG_PFCC            = 0x5007,
	MLX5_REG_PPCNT		 = 0x5008,
	MLX5_REG_PPTB            = 0x500b,
	MLX5_REG_PBMC            = 0x500c,
	MLX5_REG_PMAOS		 = 0x5012,
	MLX5_REG_PUDE		 = 0x5009,
	MLX5_REG_PMPE		 = 0x5010,
	MLX5_REG_PELC		 = 0x500e,
	MLX5_REG_PVLC		 = 0x500f,
	MLX5_REG_PCMR		 = 0x5041,
	MLX5_REG_PDDR		 = 0x5031,
	MLX5_REG_PMLP		 = 0x5002,
	MLX5_REG_PPLM		 = 0x5023,
	MLX5_REG_PCAM		 = 0x507f,
	MLX5_REG_NODE_DESC	 = 0x6001,
	MLX5_REG_HOST_ENDIANNESS = 0x7004,
	MLX5_REG_MCIA		 = 0x9014,
	MLX5_REG_MFRL		 = 0x9028,
	MLX5_REG_MLCR		 = 0x902b,
	MLX5_REG_MTRC_CAP	 = 0x9040,
	MLX5_REG_MTRC_CONF	 = 0x9041,
	MLX5_REG_MTRC_STDB	 = 0x9042,
	MLX5_REG_MTRC_CTRL	 = 0x9043,
	MLX5_REG_MPEIN		 = 0x9050,
	MLX5_REG_MPCNT		 = 0x9051,
	MLX5_REG_MTPPS		 = 0x9053,
	MLX5_REG_MTPPSE		 = 0x9054,
	MLX5_REG_MTUTC		 = 0x9055,
	MLX5_REG_MPEGC		 = 0x9056,
	MLX5_REG_MCQS		 = 0x9060,
	MLX5_REG_MCQI		 = 0x9061,
	MLX5_REG_MCC		 = 0x9062,
	MLX5_REG_MCDA		 = 0x9063,
	MLX5_REG_MCAM		 = 0x907f,
	MLX5_REG_MIRC		 = 0x9162,
	MLX5_REG_SBCAM		 = 0xB01F,
	MLX5_REG_RESOURCE_DUMP   = 0xC000,
पूर्ण;

क्रमागत mlx5_qpts_trust_state अणु
	MLX5_QPTS_TRUST_PCP  = 1,
	MLX5_QPTS_TRUST_DSCP = 2,
पूर्ण;

क्रमागत mlx5_dcbx_oper_mode अणु
	MLX5E_DCBX_PARAM_VER_OPER_HOST  = 0x0,
	MLX5E_DCBX_PARAM_VER_OPER_AUTO  = 0x3,
पूर्ण;

क्रमागत अणु
	MLX5_ATOMIC_OPS_CMP_SWAP	= 1 << 0,
	MLX5_ATOMIC_OPS_FETCH_ADD	= 1 << 1,
	MLX5_ATOMIC_OPS_EXTENDED_CMP_SWAP = 1 << 2,
	MLX5_ATOMIC_OPS_EXTENDED_FETCH_ADD = 1 << 3,
पूर्ण;

क्रमागत mlx5_page_fault_resume_flags अणु
	MLX5_PAGE_FAULT_RESUME_REQUESTOR = 1 << 0,
	MLX5_PAGE_FAULT_RESUME_WRITE	 = 1 << 1,
	MLX5_PAGE_FAULT_RESUME_RDMA	 = 1 << 2,
	MLX5_PAGE_FAULT_RESUME_ERROR	 = 1 << 7,
पूर्ण;

क्रमागत dbg_rsc_type अणु
	MLX5_DBG_RSC_QP,
	MLX5_DBG_RSC_EQ,
	MLX5_DBG_RSC_CQ,
पूर्ण;

क्रमागत port_state_policy अणु
	MLX5_POLICY_DOWN	= 0,
	MLX5_POLICY_UP		= 1,
	MLX5_POLICY_FOLLOW	= 2,
	MLX5_POLICY_INVALID	= 0xffffffff
पूर्ण;

क्रमागत mlx5_coredev_type अणु
	MLX5_COREDEV_PF,
	MLX5_COREDEV_VF,
	MLX5_COREDEV_SF,
पूर्ण;

काष्ठा mlx5_field_desc अणु
	पूर्णांक			i;
पूर्ण;

काष्ठा mlx5_rsc_debug अणु
	काष्ठा mlx5_core_dev   *dev;
	व्योम		       *object;
	क्रमागत dbg_rsc_type	type;
	काष्ठा dentry	       *root;
	काष्ठा mlx5_field_desc	fields[];
पूर्ण;

क्रमागत mlx5_dev_event अणु
	MLX5_DEV_EVENT_SYS_ERROR = 128, /* 0 - 127 are FW events */
	MLX5_DEV_EVENT_PORT_AFFINITY = 129,
पूर्ण;

क्रमागत mlx5_port_status अणु
	MLX5_PORT_UP        = 1,
	MLX5_PORT_DOWN      = 2,
पूर्ण;

क्रमागत mlx5_cmdअगर_state अणु
	MLX5_CMDIF_STATE_UNINITIALIZED,
	MLX5_CMDIF_STATE_UP,
	MLX5_CMDIF_STATE_DOWN,
पूर्ण;

काष्ठा mlx5_cmd_first अणु
	__be32		data[4];
पूर्ण;

काष्ठा mlx5_cmd_msg अणु
	काष्ठा list_head		list;
	काष्ठा cmd_msg_cache	       *parent;
	u32				len;
	काष्ठा mlx5_cmd_first		first;
	काष्ठा mlx5_cmd_mailbox	       *next;
पूर्ण;

काष्ठा mlx5_cmd_debug अणु
	काष्ठा dentry	       *dbg_root;
	व्योम		       *in_msg;
	व्योम		       *out_msg;
	u8			status;
	u16			inlen;
	u16			outlen;
पूर्ण;

काष्ठा cmd_msg_cache अणु
	/* protect block chain allocations
	 */
	spinlock_t		lock;
	काष्ठा list_head	head;
	अचिन्हित पूर्णांक		max_inbox_size;
	अचिन्हित पूर्णांक		num_ent;
पूर्ण;

क्रमागत अणु
	MLX5_NUM_COMMAND_CACHES = 5,
पूर्ण;

काष्ठा mlx5_cmd_stats अणु
	u64		sum;
	u64		n;
	काष्ठा dentry  *root;
	/* protect command average calculations */
	spinlock_t	lock;
पूर्ण;

काष्ठा mlx5_cmd अणु
	काष्ठा mlx5_nb    nb;

	क्रमागत mlx5_cmdअगर_state	state;
	व्योम	       *cmd_alloc_buf;
	dma_addr_t	alloc_dma;
	पूर्णांक		alloc_size;
	व्योम	       *cmd_buf;
	dma_addr_t	dma;
	u16		cmdअगर_rev;
	u8		log_sz;
	u8		log_stride;
	पूर्णांक		max_reg_cmds;
	पूर्णांक		events;
	u32 __iomem    *vector;

	/* protect command queue allocations
	 */
	spinlock_t	alloc_lock;

	/* protect token allocations
	 */
	spinlock_t	token_lock;
	u8		token;
	अचिन्हित दीर्घ	biपंचांगask;
	अक्षर		wq_name[MLX5_CMD_WQ_MAX_NAME];
	काष्ठा workqueue_काष्ठा *wq;
	काष्ठा semaphore sem;
	काष्ठा semaphore pages_sem;
	पूर्णांक	mode;
	u16     allowed_opcode;
	काष्ठा mlx5_cmd_work_ent *ent_arr[MLX5_MAX_COMMANDS];
	काष्ठा dma_pool *pool;
	काष्ठा mlx5_cmd_debug dbg;
	काष्ठा cmd_msg_cache cache[MLX5_NUM_COMMAND_CACHES];
	पूर्णांक checksum_disabled;
	काष्ठा mlx5_cmd_stats *stats;
पूर्ण;

काष्ठा mlx5_cmd_mailbox अणु
	व्योम	       *buf;
	dma_addr_t	dma;
	काष्ठा mlx5_cmd_mailbox *next;
पूर्ण;

काष्ठा mlx5_buf_list अणु
	व्योम		       *buf;
	dma_addr_t		map;
पूर्ण;

काष्ठा mlx5_frag_buf अणु
	काष्ठा mlx5_buf_list	*frags;
	पूर्णांक			npages;
	पूर्णांक			size;
	u8			page_shअगरt;
पूर्ण;

काष्ठा mlx5_frag_buf_ctrl अणु
	काष्ठा mlx5_buf_list   *frags;
	u32			sz_m1;
	u16			frag_sz_m1;
	u16			strides_offset;
	u8			log_sz;
	u8			log_stride;
	u8			log_frag_strides;
पूर्ण;

काष्ठा mlx5_core_psv अणु
	u32	psv_idx;
	काष्ठा psv_layout अणु
		u32	pd;
		u16	syndrome;
		u16	reserved;
		u16	bg;
		u16	app_tag;
		u32	ref_tag;
	पूर्ण psv;
पूर्ण;

काष्ठा mlx5_core_sig_ctx अणु
	काष्ठा mlx5_core_psv	psv_memory;
	काष्ठा mlx5_core_psv	psv_wire;
	काष्ठा ib_sig_err       err_item;
	bool			sig_status_checked;
	bool			sig_err_exists;
	u32			sigerr_count;
पूर्ण;

क्रमागत अणु
	MLX5_MKEY_MR = 1,
	MLX5_MKEY_MW,
	MLX5_MKEY_INसूचीECT_DEVX,
पूर्ण;

काष्ठा mlx5_core_mkey अणु
	u64			iova;
	u64			size;
	u32			key;
	u32			pd;
	u32			type;
	काष्ठा रुको_queue_head रुको;
	refcount_t usecount;
पूर्ण;

#घोषणा MLX5_24BIT_MASK		((1 << 24) - 1)

क्रमागत mlx5_res_type अणु
	MLX5_RES_QP	= MLX5_EVENT_QUEUE_TYPE_QP,
	MLX5_RES_RQ	= MLX5_EVENT_QUEUE_TYPE_RQ,
	MLX5_RES_SQ	= MLX5_EVENT_QUEUE_TYPE_SQ,
	MLX5_RES_SRQ	= 3,
	MLX5_RES_XSRQ	= 4,
	MLX5_RES_XRQ	= 5,
	MLX5_RES_DCT	= MLX5_EVENT_QUEUE_TYPE_DCT,
पूर्ण;

काष्ठा mlx5_core_rsc_common अणु
	क्रमागत mlx5_res_type	res;
	refcount_t		refcount;
	काष्ठा completion	मुक्त;
पूर्ण;

काष्ठा mlx5_uars_page अणु
	व्योम __iomem	       *map;
	bool			wc;
	u32			index;
	काष्ठा list_head	list;
	अचिन्हित पूर्णांक		bfregs;
	अचिन्हित दीर्घ	       *reg_biपंचांगap; /* क्रम non fast path bf regs */
	अचिन्हित दीर्घ	       *fp_biपंचांगap;
	अचिन्हित पूर्णांक		reg_avail;
	अचिन्हित पूर्णांक		fp_avail;
	काष्ठा kref		ref_count;
	काष्ठा mlx5_core_dev   *mdev;
पूर्ण;

काष्ठा mlx5_bfreg_head अणु
	/* protect blue flame रेजिस्टरs allocations */
	काष्ठा mutex		lock;
	काष्ठा list_head	list;
पूर्ण;

काष्ठा mlx5_bfreg_data अणु
	काष्ठा mlx5_bfreg_head	reg_head;
	काष्ठा mlx5_bfreg_head	wc_head;
पूर्ण;

काष्ठा mlx5_sq_bfreg अणु
	व्योम __iomem	       *map;
	काष्ठा mlx5_uars_page  *up;
	bool			wc;
	u32			index;
	अचिन्हित पूर्णांक		offset;
पूर्ण;

काष्ठा mlx5_core_health अणु
	काष्ठा health_buffer __iomem   *health;
	__be32 __iomem		       *health_counter;
	काष्ठा समयr_list		समयr;
	u32				prev;
	पूर्णांक				miss_counter;
	u8				synd;
	u32				fatal_error;
	u32				crdump_size;
	/* wq spinlock to synchronize draining */
	spinlock_t			wq_lock;
	काष्ठा workqueue_काष्ठा	       *wq;
	अचिन्हित दीर्घ			flags;
	काष्ठा work_काष्ठा		fatal_report_work;
	काष्ठा work_काष्ठा		report_work;
	काष्ठा devlink_health_reporter *fw_reporter;
	काष्ठा devlink_health_reporter *fw_fatal_reporter;
पूर्ण;

काष्ठा mlx5_qp_table अणु
	काष्ठा notअगरier_block   nb;

	/* protect radix tree
	 */
	spinlock_t		lock;
	काष्ठा radix_tree_root	tree;
पूर्ण;

काष्ठा mlx5_vf_context अणु
	पूर्णांक	enabled;
	u64	port_guid;
	u64	node_guid;
	/* Valid bits are used to validate administrative guid only.
	 * Enabled after nकरो_set_vf_guid
	 */
	u8	port_guid_valid:1;
	u8	node_guid_valid:1;
	क्रमागत port_state_policy	policy;
पूर्ण;

काष्ठा mlx5_core_sriov अणु
	काष्ठा mlx5_vf_context	*vfs_ctx;
	पूर्णांक			num_vfs;
	u16			max_vfs;
पूर्ण;

काष्ठा mlx5_fc_pool अणु
	काष्ठा mlx5_core_dev *dev;
	काष्ठा mutex pool_lock; /* protects pool lists */
	काष्ठा list_head fully_used;
	काष्ठा list_head partially_used;
	काष्ठा list_head unused;
	पूर्णांक available_fcs;
	पूर्णांक used_fcs;
	पूर्णांक threshold;
पूर्ण;

काष्ठा mlx5_fc_stats अणु
	spinlock_t counters_idr_lock; /* protects counters_idr */
	काष्ठा idr counters_idr;
	काष्ठा list_head counters;
	काष्ठा llist_head addlist;
	काष्ठा llist_head dellist;

	काष्ठा workqueue_काष्ठा *wq;
	काष्ठा delayed_work work;
	अचिन्हित दीर्घ next_query;
	अचिन्हित दीर्घ sampling_पूर्णांकerval; /* jअगरfies */
	u32 *bulk_query_out;
	काष्ठा mlx5_fc_pool fc_pool;
पूर्ण;

काष्ठा mlx5_events;
काष्ठा mlx5_mpfs;
काष्ठा mlx5_eचयन;
काष्ठा mlx5_lag;
काष्ठा mlx5_devcom;
काष्ठा mlx5_fw_reset;
काष्ठा mlx5_eq_table;
काष्ठा mlx5_irq_table;
काष्ठा mlx5_vhca_state_notअगरier;
काष्ठा mlx5_sf_dev_table;
काष्ठा mlx5_sf_hw_table;
काष्ठा mlx5_sf_table;

काष्ठा mlx5_rate_limit अणु
	u32			rate;
	u32			max_burst_sz;
	u16			typical_pkt_sz;
पूर्ण;

काष्ठा mlx5_rl_entry अणु
	u8 rl_raw[MLX5_ST_SZ_BYTES(set_pp_rate_limit_context)];
	u64 refcount;
	u16 index;
	u16 uid;
	u8 dedicated : 1;
पूर्ण;

काष्ठा mlx5_rl_table अणु
	/* protect rate limit table */
	काष्ठा mutex            rl_lock;
	u16                     max_size;
	u32                     max_rate;
	u32                     min_rate;
	काष्ठा mlx5_rl_entry   *rl_entry;
	u64 refcount;
पूर्ण;

काष्ठा mlx5_core_roce अणु
	काष्ठा mlx5_flow_table *ft;
	काष्ठा mlx5_flow_group *fg;
	काष्ठा mlx5_flow_handle *allow_rule;
पूर्ण;

क्रमागत अणु
	MLX5_PRIV_FLAGS_DISABLE_IB_ADEV = 1 << 0,
	MLX5_PRIV_FLAGS_DISABLE_ALL_ADEV = 1 << 1,
	/* Set during device detach to block any further devices
	 * creation/deletion on drivers rescan. Unset during device attach.
	 */
	MLX5_PRIV_FLAGS_DETACH = 1 << 2,
पूर्ण;

काष्ठा mlx5_adev अणु
	काष्ठा auxiliary_device adev;
	काष्ठा mlx5_core_dev *mdev;
	पूर्णांक idx;
पूर्ण;

काष्ठा mlx5_priv अणु
	/* IRQ table valid only क्रम real pci devices PF or VF */
	काष्ठा mlx5_irq_table   *irq_table;
	काष्ठा mlx5_eq_table	*eq_table;

	/* pages stuff */
	काष्ठा mlx5_nb          pg_nb;
	काष्ठा workqueue_काष्ठा *pg_wq;
	काष्ठा xarray           page_root_xa;
	पूर्णांक			fw_pages;
	atomic_t		reg_pages;
	काष्ठा list_head	मुक्त_list;
	पूर्णांक			vfs_pages;
	पूर्णांक			host_pf_pages;

	काष्ठा mlx5_core_health health;
	काष्ठा list_head	traps;

	/* start: qp staff */
	काष्ठा dentry	       *qp_debugfs;
	काष्ठा dentry	       *eq_debugfs;
	काष्ठा dentry	       *cq_debugfs;
	काष्ठा dentry	       *cmdअगर_debugfs;
	/* end: qp staff */

	/* start: alloc staff */
	/* protect buffer alocation according to numa node */
	काष्ठा mutex            alloc_mutex;
	पूर्णांक                     numa_node;

	काष्ठा mutex            pgdir_mutex;
	काष्ठा list_head        pgdir_list;
	/* end: alloc staff */
	काष्ठा dentry	       *dbg_root;

	काष्ठा list_head        ctx_list;
	spinlock_t              ctx_lock;
	काष्ठा mlx5_adev       **adev;
	पूर्णांक			adev_idx;
	काष्ठा mlx5_events      *events;

	काष्ठा mlx5_flow_steering *steering;
	काष्ठा mlx5_mpfs        *mpfs;
	काष्ठा mlx5_eचयन     *eचयन;
	काष्ठा mlx5_core_sriov	sriov;
	काष्ठा mlx5_lag		*lag;
	u32			flags;
	काष्ठा mlx5_devcom	*devcom;
	काष्ठा mlx5_fw_reset	*fw_reset;
	काष्ठा mlx5_core_roce	roce;
	काष्ठा mlx5_fc_stats		fc_stats;
	काष्ठा mlx5_rl_table            rl_table;

	काष्ठा mlx5_bfreg_data		bfregs;
	काष्ठा mlx5_uars_page	       *uar;
#अगर_घोषित CONFIG_MLX5_SF
	काष्ठा mlx5_vhca_state_notअगरier *vhca_state_notअगरier;
	काष्ठा mlx5_sf_dev_table *sf_dev_table;
	काष्ठा mlx5_core_dev *parent_mdev;
#पूर्ण_अगर
#अगर_घोषित CONFIG_MLX5_SF_MANAGER
	काष्ठा mlx5_sf_hw_table *sf_hw_table;
	काष्ठा mlx5_sf_table *sf_table;
#पूर्ण_अगर
पूर्ण;

क्रमागत mlx5_device_state अणु
	MLX5_DEVICE_STATE_UNINITIALIZED,
	MLX5_DEVICE_STATE_UP,
	MLX5_DEVICE_STATE_INTERNAL_ERROR,
पूर्ण;

क्रमागत mlx5_पूर्णांकerface_state अणु
	MLX5_INTERFACE_STATE_UP = BIT(0),
पूर्ण;

क्रमागत mlx5_pci_status अणु
	MLX5_PCI_STATUS_DISABLED,
	MLX5_PCI_STATUS_ENABLED,
पूर्ण;

क्रमागत mlx5_pagefault_type_flags अणु
	MLX5_PFAULT_REQUESTOR = 1 << 0,
	MLX5_PFAULT_WRITE     = 1 << 1,
	MLX5_PFAULT_RDMA      = 1 << 2,
पूर्ण;

काष्ठा mlx5_td अणु
	/* protects tirs list changes जबतक tirs refresh */
	काष्ठा mutex     list_lock;
	काष्ठा list_head tirs_list;
	u32              tdn;
पूर्ण;

काष्ठा mlx5e_resources अणु
	काष्ठा mlx5e_hw_objs अणु
		u32                        pdn;
		काष्ठा mlx5_td             td;
		काष्ठा mlx5_core_mkey      mkey;
		काष्ठा mlx5_sq_bfreg       bfreg;
	पूर्ण hw_objs;
	काष्ठा devlink_port dl_port;
	काष्ठा net_device *uplink_netdev;
पूर्ण;

क्रमागत mlx5_sw_icm_type अणु
	MLX5_SW_ICM_TYPE_STEERING,
	MLX5_SW_ICM_TYPE_HEADER_MODIFY,
पूर्ण;

#घोषणा MLX5_MAX_RESERVED_GIDS 8

काष्ठा mlx5_rsvd_gids अणु
	अचिन्हित पूर्णांक start;
	अचिन्हित पूर्णांक count;
	काष्ठा ida ida;
पूर्ण;

#घोषणा MAX_PIN_NUM	8
काष्ठा mlx5_pps अणु
	u8                         pin_caps[MAX_PIN_NUM];
	काष्ठा work_काष्ठा         out_work;
	u64                        start[MAX_PIN_NUM];
	u8                         enabled;
पूर्ण;

काष्ठा mlx5_समयr अणु
	काष्ठा cyclecounter        cycles;
	काष्ठा समयcounter         tc;
	u32                        nominal_c_mult;
	अचिन्हित दीर्घ              overflow_period;
	काष्ठा delayed_work        overflow_work;
पूर्ण;

काष्ठा mlx5_घड़ी अणु
	काष्ठा mlx5_nb             pps_nb;
	seqlock_t                  lock;
	काष्ठा hwtstamp_config     hwtstamp_config;
	काष्ठा ptp_घड़ी          *ptp;
	काष्ठा ptp_घड़ी_info      ptp_info;
	काष्ठा mlx5_pps            pps_info;
	काष्ठा mlx5_समयr          समयr;
पूर्ण;

काष्ठा mlx5_dm;
काष्ठा mlx5_fw_tracer;
काष्ठा mlx5_vxlan;
काष्ठा mlx5_geneve;
काष्ठा mlx5_hv_vhca;

#घोषणा MLX5_LOG_SW_ICM_BLOCK_SIZE(dev) (MLX5_CAP_DEV_MEM(dev, log_sw_icm_alloc_granularity))
#घोषणा MLX5_SW_ICM_BLOCK_SIZE(dev) (1 << MLX5_LOG_SW_ICM_BLOCK_SIZE(dev))

क्रमागत अणु
	MLX5_PROF_MASK_QP_SIZE		= (u64)1 << 0,
	MLX5_PROF_MASK_MR_CACHE		= (u64)1 << 1,
पूर्ण;

क्रमागत अणु
	MR_CACHE_LAST_STD_ENTRY = 20,
	MLX5_IMR_MTT_CACHE_ENTRY,
	MLX5_IMR_KSM_CACHE_ENTRY,
	MAX_MR_CACHE_ENTRIES
पूर्ण;

काष्ठा mlx5_profile अणु
	u64	mask;
	u8	log_max_qp;
	काष्ठा अणु
		पूर्णांक	size;
		पूर्णांक	limit;
	पूर्ण mr_cache[MAX_MR_CACHE_ENTRIES];
पूर्ण;

काष्ठा mlx5_core_dev अणु
	काष्ठा device *device;
	क्रमागत mlx5_coredev_type coredev_type;
	काष्ठा pci_dev	       *pdev;
	/* sync pci state */
	काष्ठा mutex		pci_status_mutex;
	क्रमागत mlx5_pci_status	pci_status;
	u8			rev_id;
	अक्षर			board_id[MLX5_BOARD_ID_LEN];
	काष्ठा mlx5_cmd		cmd;
	काष्ठा अणु
		u32 hca_cur[MLX5_CAP_NUM][MLX5_UN_SZ_DW(hca_cap_जोड़)];
		u32 hca_max[MLX5_CAP_NUM][MLX5_UN_SZ_DW(hca_cap_जोड़)];
		u32 pcam[MLX5_ST_SZ_DW(pcam_reg)];
		u32 mcam[MLX5_MCAM_REGS_NUM][MLX5_ST_SZ_DW(mcam_reg)];
		u32 fpga[MLX5_ST_SZ_DW(fpga_cap)];
		u32 qcam[MLX5_ST_SZ_DW(qcam_reg)];
		u8  embedded_cpu;
	पूर्ण caps;
	u64			sys_image_guid;
	phys_addr_t		iseg_base;
	काष्ठा mlx5_init_seg __iomem *iseg;
	phys_addr_t             bar_addr;
	क्रमागत mlx5_device_state	state;
	/* sync पूर्णांकerface state */
	काष्ठा mutex		पूर्णांकf_state_mutex;
	अचिन्हित दीर्घ		पूर्णांकf_state;
	काष्ठा mlx5_priv	priv;
	काष्ठा mlx5_profile	profile;
	u32			issi;
	काष्ठा mlx5e_resources  mlx5e_res;
	काष्ठा mlx5_dm          *dm;
	काष्ठा mlx5_vxlan       *vxlan;
	काष्ठा mlx5_geneve      *geneve;
	काष्ठा अणु
		काष्ठा mlx5_rsvd_gids	reserved_gids;
		u32			roce_en;
	पूर्ण roce;
#अगर_घोषित CONFIG_MLX5_FPGA
	काष्ठा mlx5_fpga_device *fpga;
#पूर्ण_अगर
#अगर_घोषित CONFIG_MLX5_ACCEL
	स्थिर काष्ठा mlx5_accel_ipsec_ops *ipsec_ops;
#पूर्ण_अगर
	काष्ठा mlx5_घड़ी        घड़ी;
	काष्ठा mlx5_ib_घड़ी_info  *घड़ी_info;
	काष्ठा mlx5_fw_tracer   *tracer;
	काष्ठा mlx5_rsc_dump    *rsc_dump;
	u32                      vsc_addr;
	काष्ठा mlx5_hv_vhca	*hv_vhca;
पूर्ण;

काष्ठा mlx5_db अणु
	__be32			*db;
	जोड़ अणु
		काष्ठा mlx5_db_pgdir		*pgdir;
		काष्ठा mlx5_ib_user_db_page	*user_page;
	पूर्ण			u;
	dma_addr_t		dma;
	पूर्णांक			index;
पूर्ण;

क्रमागत अणु
	MLX5_COMP_EQ_SIZE = 1024,
पूर्ण;

क्रमागत अणु
	MLX5_PTYS_IB = 1 << 0,
	MLX5_PTYS_EN = 1 << 2,
पूर्ण;

प्रकार व्योम (*mlx5_cmd_cbk_t)(पूर्णांक status, व्योम *context);

क्रमागत अणु
	MLX5_CMD_ENT_STATE_PENDING_COMP,
पूर्ण;

काष्ठा mlx5_cmd_work_ent अणु
	अचिन्हित दीर्घ		state;
	काष्ठा mlx5_cmd_msg    *in;
	काष्ठा mlx5_cmd_msg    *out;
	व्योम		       *uout;
	पूर्णांक			uout_size;
	mlx5_cmd_cbk_t		callback;
	काष्ठा delayed_work	cb_समयout_work;
	व्योम		       *context;
	पूर्णांक			idx;
	काष्ठा completion	handling;
	काष्ठा completion	करोne;
	काष्ठा mlx5_cmd        *cmd;
	काष्ठा work_काष्ठा	work;
	काष्ठा mlx5_cmd_layout *lay;
	पूर्णांक			ret;
	पूर्णांक			page_queue;
	u8			status;
	u8			token;
	u64			ts1;
	u64			ts2;
	u16			op;
	bool			polling;
	/* Track the max comp handlers */
	refcount_t              refcnt;
पूर्ण;

काष्ठा mlx5_pas अणु
	u64	pa;
	u8	log_sz;
पूर्ण;

क्रमागत phy_port_state अणु
	MLX5_AAA_111
पूर्ण;

काष्ठा mlx5_hca_vport_context अणु
	u32			field_select;
	bool			sm_virt_aware;
	bool			has_smi;
	bool			has_raw;
	क्रमागत port_state_policy	policy;
	क्रमागत phy_port_state	phys_state;
	क्रमागत ib_port_state	vport_state;
	u8			port_physical_state;
	u64			sys_image_guid;
	u64			port_guid;
	u64			node_guid;
	u32			cap_mask1;
	u32			cap_mask1_perm;
	u16			cap_mask2;
	u16			cap_mask2_perm;
	u16			lid;
	u8			init_type_reply; /* biपंचांगask: see ib spec 14.2.5.6 InitTypeReply */
	u8			lmc;
	u8			subnet_समयout;
	u16			sm_lid;
	u8			sm_sl;
	u16			qkey_violation_counter;
	u16			pkey_violation_counter;
	bool			grh_required;
पूर्ण;

अटल अंतरभूत व्योम *mlx5_buf_offset(काष्ठा mlx5_frag_buf *buf, पूर्णांक offset)
अणु
		वापस buf->frags->buf + offset;
पूर्ण

#घोषणा STRUCT_FIELD(header, field) \
	.काष्ठा_offset_bytes = दुरत्व(काष्ठा ib_unpacked_ ## header, field),      \
	.काष्ठा_size_bytes   = माप((काष्ठा ib_unpacked_ ## header *)0)->field

अटल अंतरभूत काष्ठा mlx5_core_dev *pci2mlx5_core_dev(काष्ठा pci_dev *pdev)
अणु
	वापस pci_get_drvdata(pdev);
पूर्ण

बाह्य काष्ठा dentry *mlx5_debugfs_root;

अटल अंतरभूत u16 fw_rev_maj(काष्ठा mlx5_core_dev *dev)
अणु
	वापस ioपढ़ो32be(&dev->iseg->fw_rev) & 0xffff;
पूर्ण

अटल अंतरभूत u16 fw_rev_min(काष्ठा mlx5_core_dev *dev)
अणु
	वापस ioपढ़ो32be(&dev->iseg->fw_rev) >> 16;
पूर्ण

अटल अंतरभूत u16 fw_rev_sub(काष्ठा mlx5_core_dev *dev)
अणु
	वापस ioपढ़ो32be(&dev->iseg->cmdअगर_rev_fw_sub) & 0xffff;
पूर्ण

अटल अंतरभूत u32 mlx5_base_mkey(स्थिर u32 key)
अणु
	वापस key & 0xffffff00u;
पूर्ण

अटल अंतरभूत u32 wq_get_byte_sz(u8 log_sz, u8 log_stride)
अणु
	वापस ((u32)1 << log_sz) << log_stride;
पूर्ण

अटल अंतरभूत व्योम mlx5_init_fbc_offset(काष्ठा mlx5_buf_list *frags,
					u8 log_stride, u8 log_sz,
					u16 strides_offset,
					काष्ठा mlx5_frag_buf_ctrl *fbc)
अणु
	fbc->frags      = frags;
	fbc->log_stride = log_stride;
	fbc->log_sz     = log_sz;
	fbc->sz_m1	= (1 << fbc->log_sz) - 1;
	fbc->log_frag_strides = PAGE_SHIFT - fbc->log_stride;
	fbc->frag_sz_m1	= (1 << fbc->log_frag_strides) - 1;
	fbc->strides_offset = strides_offset;
पूर्ण

अटल अंतरभूत व्योम mlx5_init_fbc(काष्ठा mlx5_buf_list *frags,
				 u8 log_stride, u8 log_sz,
				 काष्ठा mlx5_frag_buf_ctrl *fbc)
अणु
	mlx5_init_fbc_offset(frags, log_stride, log_sz, 0, fbc);
पूर्ण

अटल अंतरभूत व्योम *mlx5_frag_buf_get_wqe(काष्ठा mlx5_frag_buf_ctrl *fbc,
					  u32 ix)
अणु
	अचिन्हित पूर्णांक frag;

	ix  += fbc->strides_offset;
	frag = ix >> fbc->log_frag_strides;

	वापस fbc->frags[frag].buf + ((fbc->frag_sz_m1 & ix) << fbc->log_stride);
पूर्ण

अटल अंतरभूत u32
mlx5_frag_buf_get_idx_last_contig_stride(काष्ठा mlx5_frag_buf_ctrl *fbc, u32 ix)
अणु
	u32 last_frag_stride_idx = (ix + fbc->strides_offset) | fbc->frag_sz_m1;

	वापस min_t(u32, last_frag_stride_idx - fbc->strides_offset, fbc->sz_m1);
पूर्ण

क्रमागत अणु
	CMD_ALLOWED_OPCODE_ALL,
पूर्ण;

व्योम mlx5_cmd_use_events(काष्ठा mlx5_core_dev *dev);
व्योम mlx5_cmd_use_polling(काष्ठा mlx5_core_dev *dev);
व्योम mlx5_cmd_allowed_opcode(काष्ठा mlx5_core_dev *dev, u16 opcode);

काष्ठा mlx5_async_ctx अणु
	काष्ठा mlx5_core_dev *dev;
	atomic_t num_inflight;
	काष्ठा रुको_queue_head रुको;
पूर्ण;

काष्ठा mlx5_async_work;

प्रकार व्योम (*mlx5_async_cbk_t)(पूर्णांक status, काष्ठा mlx5_async_work *context);

काष्ठा mlx5_async_work अणु
	काष्ठा mlx5_async_ctx *ctx;
	mlx5_async_cbk_t user_callback;
पूर्ण;

व्योम mlx5_cmd_init_async_ctx(काष्ठा mlx5_core_dev *dev,
			     काष्ठा mlx5_async_ctx *ctx);
व्योम mlx5_cmd_cleanup_async_ctx(काष्ठा mlx5_async_ctx *ctx);
पूर्णांक mlx5_cmd_exec_cb(काष्ठा mlx5_async_ctx *ctx, व्योम *in, पूर्णांक in_size,
		     व्योम *out, पूर्णांक out_size, mlx5_async_cbk_t callback,
		     काष्ठा mlx5_async_work *work);

पूर्णांक mlx5_cmd_exec(काष्ठा mlx5_core_dev *dev, व्योम *in, पूर्णांक in_size, व्योम *out,
		  पूर्णांक out_size);

#घोषणा mlx5_cmd_exec_inout(dev, अगरc_cmd, in, out)                             \
	(अणु                                                                     \
		mlx5_cmd_exec(dev, in, MLX5_ST_SZ_BYTES(अगरc_cmd##_in), out,    \
			      MLX5_ST_SZ_BYTES(अगरc_cmd##_out));                \
	पूर्ण)

#घोषणा mlx5_cmd_exec_in(dev, अगरc_cmd, in)                                     \
	(अणु                                                                     \
		u32 _out[MLX5_ST_SZ_DW(अगरc_cmd##_out)] = अणुपूर्ण;                   \
		mlx5_cmd_exec_inout(dev, अगरc_cmd, in, _out);                   \
	पूर्ण)

पूर्णांक mlx5_cmd_exec_polling(काष्ठा mlx5_core_dev *dev, व्योम *in, पूर्णांक in_size,
			  व्योम *out, पूर्णांक out_size);
व्योम mlx5_cmd_mbox_status(व्योम *out, u8 *status, u32 *syndrome);
bool mlx5_cmd_is_करोwn(काष्ठा mlx5_core_dev *dev);

पूर्णांक mlx5_core_get_caps(काष्ठा mlx5_core_dev *dev, क्रमागत mlx5_cap_type cap_type);
पूर्णांक mlx5_cmd_alloc_uar(काष्ठा mlx5_core_dev *dev, u32 *uarn);
पूर्णांक mlx5_cmd_मुक्त_uar(काष्ठा mlx5_core_dev *dev, u32 uarn);
व्योम mlx5_health_flush(काष्ठा mlx5_core_dev *dev);
व्योम mlx5_health_cleanup(काष्ठा mlx5_core_dev *dev);
पूर्णांक mlx5_health_init(काष्ठा mlx5_core_dev *dev);
व्योम mlx5_start_health_poll(काष्ठा mlx5_core_dev *dev);
व्योम mlx5_stop_health_poll(काष्ठा mlx5_core_dev *dev, bool disable_health);
व्योम mlx5_drain_health_wq(काष्ठा mlx5_core_dev *dev);
व्योम mlx5_trigger_health_work(काष्ठा mlx5_core_dev *dev);
पूर्णांक mlx5_buf_alloc(काष्ठा mlx5_core_dev *dev,
		   पूर्णांक size, काष्ठा mlx5_frag_buf *buf);
व्योम mlx5_buf_मुक्त(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_frag_buf *buf);
पूर्णांक mlx5_frag_buf_alloc_node(काष्ठा mlx5_core_dev *dev, पूर्णांक size,
			     काष्ठा mlx5_frag_buf *buf, पूर्णांक node);
व्योम mlx5_frag_buf_मुक्त(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_frag_buf *buf);
काष्ठा mlx5_cmd_mailbox *mlx5_alloc_cmd_mailbox_chain(काष्ठा mlx5_core_dev *dev,
						      gfp_t flags, पूर्णांक npages);
व्योम mlx5_मुक्त_cmd_mailbox_chain(काष्ठा mlx5_core_dev *dev,
				 काष्ठा mlx5_cmd_mailbox *head);
पूर्णांक mlx5_core_create_mkey(काष्ठा mlx5_core_dev *dev,
			  काष्ठा mlx5_core_mkey *mkey,
			  u32 *in, पूर्णांक inlen);
पूर्णांक mlx5_core_destroy_mkey(काष्ठा mlx5_core_dev *dev,
			   काष्ठा mlx5_core_mkey *mkey);
पूर्णांक mlx5_core_query_mkey(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_core_mkey *mkey,
			 u32 *out, पूर्णांक outlen);
पूर्णांक mlx5_core_alloc_pd(काष्ठा mlx5_core_dev *dev, u32 *pdn);
पूर्णांक mlx5_core_dealloc_pd(काष्ठा mlx5_core_dev *dev, u32 pdn);
पूर्णांक mlx5_pagealloc_init(काष्ठा mlx5_core_dev *dev);
व्योम mlx5_pagealloc_cleanup(काष्ठा mlx5_core_dev *dev);
व्योम mlx5_pagealloc_start(काष्ठा mlx5_core_dev *dev);
व्योम mlx5_pagealloc_stop(काष्ठा mlx5_core_dev *dev);
व्योम mlx5_core_req_pages_handler(काष्ठा mlx5_core_dev *dev, u16 func_id,
				 s32 npages, bool ec_function);
पूर्णांक mlx5_satisfy_startup_pages(काष्ठा mlx5_core_dev *dev, पूर्णांक boot);
पूर्णांक mlx5_reclaim_startup_pages(काष्ठा mlx5_core_dev *dev);
व्योम mlx5_रेजिस्टर_debugfs(व्योम);
व्योम mlx5_unरेजिस्टर_debugfs(व्योम);

व्योम mlx5_fill_page_array(काष्ठा mlx5_frag_buf *buf, __be64 *pas);
व्योम mlx5_fill_page_frag_array_perm(काष्ठा mlx5_frag_buf *buf, __be64 *pas, u8 perm);
व्योम mlx5_fill_page_frag_array(काष्ठा mlx5_frag_buf *frag_buf, __be64 *pas);
पूर्णांक mlx5_vector2eqn(काष्ठा mlx5_core_dev *dev, पूर्णांक vector, पूर्णांक *eqn,
		    अचिन्हित पूर्णांक *irqn);
पूर्णांक mlx5_core_attach_mcg(काष्ठा mlx5_core_dev *dev, जोड़ ib_gid *mgid, u32 qpn);
पूर्णांक mlx5_core_detach_mcg(काष्ठा mlx5_core_dev *dev, जोड़ ib_gid *mgid, u32 qpn);

व्योम mlx5_qp_debugfs_init(काष्ठा mlx5_core_dev *dev);
व्योम mlx5_qp_debugfs_cleanup(काष्ठा mlx5_core_dev *dev);
पूर्णांक mlx5_core_access_reg(काष्ठा mlx5_core_dev *dev, व्योम *data_in,
			 पूर्णांक size_in, व्योम *data_out, पूर्णांक size_out,
			 u16 reg_num, पूर्णांक arg, पूर्णांक ग_लिखो);

पूर्णांक mlx5_db_alloc(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_db *db);
पूर्णांक mlx5_db_alloc_node(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_db *db,
		       पूर्णांक node);
व्योम mlx5_db_मुक्त(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_db *db);

स्थिर अक्षर *mlx5_command_str(पूर्णांक command);
व्योम mlx5_cmdअगर_debugfs_init(काष्ठा mlx5_core_dev *dev);
व्योम mlx5_cmdअगर_debugfs_cleanup(काष्ठा mlx5_core_dev *dev);
पूर्णांक mlx5_core_create_psv(काष्ठा mlx5_core_dev *dev, u32 pdn,
			 पूर्णांक npsvs, u32 *sig_index);
पूर्णांक mlx5_core_destroy_psv(काष्ठा mlx5_core_dev *dev, पूर्णांक psv_num);
व्योम mlx5_core_put_rsc(काष्ठा mlx5_core_rsc_common *common);
पूर्णांक mlx5_query_odp_caps(काष्ठा mlx5_core_dev *dev,
			काष्ठा mlx5_odp_caps *odp_caps);
पूर्णांक mlx5_core_query_ib_ppcnt(काष्ठा mlx5_core_dev *dev,
			     u8 port_num, व्योम *out, माप_प्रकार sz);

पूर्णांक mlx5_init_rl_table(काष्ठा mlx5_core_dev *dev);
व्योम mlx5_cleanup_rl_table(काष्ठा mlx5_core_dev *dev);
पूर्णांक mlx5_rl_add_rate(काष्ठा mlx5_core_dev *dev, u16 *index,
		     काष्ठा mlx5_rate_limit *rl);
व्योम mlx5_rl_हटाओ_rate(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_rate_limit *rl);
bool mlx5_rl_is_in_range(काष्ठा mlx5_core_dev *dev, u32 rate);
पूर्णांक mlx5_rl_add_rate_raw(काष्ठा mlx5_core_dev *dev, व्योम *rl_in, u16 uid,
			 bool dedicated_entry, u16 *index);
व्योम mlx5_rl_हटाओ_rate_raw(काष्ठा mlx5_core_dev *dev, u16 index);
bool mlx5_rl_are_equal(काष्ठा mlx5_rate_limit *rl_0,
		       काष्ठा mlx5_rate_limit *rl_1);
पूर्णांक mlx5_alloc_bfreg(काष्ठा mlx5_core_dev *mdev, काष्ठा mlx5_sq_bfreg *bfreg,
		     bool map_wc, bool fast_path);
व्योम mlx5_मुक्त_bfreg(काष्ठा mlx5_core_dev *mdev, काष्ठा mlx5_sq_bfreg *bfreg);

अचिन्हित पूर्णांक mlx5_comp_vectors_count(काष्ठा mlx5_core_dev *dev);
काष्ठा cpumask *
mlx5_comp_irq_get_affinity_mask(काष्ठा mlx5_core_dev *dev, पूर्णांक vector);
अचिन्हित पूर्णांक mlx5_core_reserved_gids_count(काष्ठा mlx5_core_dev *dev);
पूर्णांक mlx5_core_roce_gid_set(काष्ठा mlx5_core_dev *dev, अचिन्हित पूर्णांक index,
			   u8 roce_version, u8 roce_l3_type, स्थिर u8 *gid,
			   स्थिर u8 *mac, bool vlan, u16 vlan_id, u8 port_num);

अटल अंतरभूत u32 mlx5_mkey_to_idx(u32 mkey)
अणु
	वापस mkey >> 8;
पूर्ण

अटल अंतरभूत u32 mlx5_idx_to_mkey(u32 mkey_idx)
अणु
	वापस mkey_idx << 8;
पूर्ण

अटल अंतरभूत u8 mlx5_mkey_variant(u32 mkey)
अणु
	वापस mkey & 0xff;
पूर्ण

/* Async-atomic event notअगरier used by mlx5 core to क्रमward FW
 * evetns recived from event queue to mlx5 consumers.
 * Optimise event queue dipatching.
 */
पूर्णांक mlx5_notअगरier_रेजिस्टर(काष्ठा mlx5_core_dev *dev, काष्ठा notअगरier_block *nb);
पूर्णांक mlx5_notअगरier_unरेजिस्टर(काष्ठा mlx5_core_dev *dev, काष्ठा notअगरier_block *nb);

/* Async-atomic event notअगरier used क्रम क्रमwarding
 * evetns from the event queue पूर्णांकo the to mlx5 events dispatcher,
 * eचयन, घड़ी and others.
 */
पूर्णांक mlx5_eq_notअगरier_रेजिस्टर(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_nb *nb);
पूर्णांक mlx5_eq_notअगरier_unरेजिस्टर(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_nb *nb);

/* Blocking event notअगरier used to क्रमward SW events, used क्रम slow path */
पूर्णांक mlx5_blocking_notअगरier_रेजिस्टर(काष्ठा mlx5_core_dev *dev, काष्ठा notअगरier_block *nb);
पूर्णांक mlx5_blocking_notअगरier_unरेजिस्टर(काष्ठा mlx5_core_dev *dev, काष्ठा notअगरier_block *nb);
पूर्णांक mlx5_blocking_notअगरier_call_chain(काष्ठा mlx5_core_dev *dev, अचिन्हित पूर्णांक event,
				      व्योम *data);

पूर्णांक mlx5_core_query_venकरोr_id(काष्ठा mlx5_core_dev *mdev, u32 *venकरोr_id);

पूर्णांक mlx5_cmd_create_vport_lag(काष्ठा mlx5_core_dev *dev);
पूर्णांक mlx5_cmd_destroy_vport_lag(काष्ठा mlx5_core_dev *dev);
bool mlx5_lag_is_roce(काष्ठा mlx5_core_dev *dev);
bool mlx5_lag_is_sriov(काष्ठा mlx5_core_dev *dev);
bool mlx5_lag_is_multipath(काष्ठा mlx5_core_dev *dev);
bool mlx5_lag_is_active(काष्ठा mlx5_core_dev *dev);
काष्ठा net_device *mlx5_lag_get_roce_netdev(काष्ठा mlx5_core_dev *dev);
u8 mlx5_lag_get_slave_port(काष्ठा mlx5_core_dev *dev,
			   काष्ठा net_device *slave);
पूर्णांक mlx5_lag_query_cong_counters(काष्ठा mlx5_core_dev *dev,
				 u64 *values,
				 पूर्णांक num_counters,
				 माप_प्रकार *offsets);
काष्ठा mlx5_uars_page *mlx5_get_uars_page(काष्ठा mlx5_core_dev *mdev);
व्योम mlx5_put_uars_page(काष्ठा mlx5_core_dev *mdev, काष्ठा mlx5_uars_page *up);
पूर्णांक mlx5_dm_sw_icm_alloc(काष्ठा mlx5_core_dev *dev, क्रमागत mlx5_sw_icm_type type,
			 u64 length, u32 log_alignment, u16 uid,
			 phys_addr_t *addr, u32 *obj_id);
पूर्णांक mlx5_dm_sw_icm_dealloc(काष्ठा mlx5_core_dev *dev, क्रमागत mlx5_sw_icm_type type,
			   u64 length, u16 uid, phys_addr_t addr, u32 obj_id);

#अगर_घोषित CONFIG_MLX5_CORE_IPOIB
काष्ठा net_device *mlx5_rdma_netdev_alloc(काष्ठा mlx5_core_dev *mdev,
					  काष्ठा ib_device *ibdev,
					  स्थिर अक्षर *name,
					  व्योम (*setup)(काष्ठा net_device *));
#पूर्ण_अगर /* CONFIG_MLX5_CORE_IPOIB */
पूर्णांक mlx5_rdma_rn_get_params(काष्ठा mlx5_core_dev *mdev,
			    काष्ठा ib_device *device,
			    काष्ठा rdma_netdev_alloc_params *params);

क्रमागत अणु
	MLX5_PCI_DEV_IS_VF		= 1 << 0,
पूर्ण;

अटल अंतरभूत bool mlx5_core_is_pf(स्थिर काष्ठा mlx5_core_dev *dev)
अणु
	वापस dev->coredev_type == MLX5_COREDEV_PF;
पूर्ण

अटल अंतरभूत bool mlx5_core_is_vf(स्थिर काष्ठा mlx5_core_dev *dev)
अणु
	वापस dev->coredev_type == MLX5_COREDEV_VF;
पूर्ण

अटल अंतरभूत bool mlx5_core_is_ecpf(स्थिर काष्ठा mlx5_core_dev *dev)
अणु
	वापस dev->caps.embedded_cpu;
पूर्ण

अटल अंतरभूत bool
mlx5_core_is_ecpf_esw_manager(स्थिर काष्ठा mlx5_core_dev *dev)
अणु
	वापस dev->caps.embedded_cpu && MLX5_CAP_GEN(dev, eचयन_manager);
पूर्ण

अटल अंतरभूत bool mlx5_ecpf_vport_exists(स्थिर काष्ठा mlx5_core_dev *dev)
अणु
	वापस mlx5_core_is_pf(dev) && MLX5_CAP_ESW(dev, ecpf_vport_exists);
पूर्ण

अटल अंतरभूत u16 mlx5_core_max_vfs(स्थिर काष्ठा mlx5_core_dev *dev)
अणु
	वापस dev->priv.sriov.max_vfs;
पूर्ण

अटल अंतरभूत पूर्णांक mlx5_get_gid_table_len(u16 param)
अणु
	अगर (param > 4) अणु
		pr_warn("gid table length is zero\n");
		वापस 0;
	पूर्ण

	वापस 8 * (1 << param);
पूर्ण

अटल अंतरभूत bool mlx5_rl_is_supported(काष्ठा mlx5_core_dev *dev)
अणु
	वापस !!(dev->priv.rl_table.max_size);
पूर्ण

अटल अंतरभूत पूर्णांक mlx5_core_is_mp_slave(काष्ठा mlx5_core_dev *dev)
अणु
	वापस MLX5_CAP_GEN(dev, affiliate_nic_vport_criteria) &&
	       MLX5_CAP_GEN(dev, num_vhca_ports) <= 1;
पूर्ण

अटल अंतरभूत पूर्णांक mlx5_core_is_mp_master(काष्ठा mlx5_core_dev *dev)
अणु
	वापस MLX5_CAP_GEN(dev, num_vhca_ports) > 1;
पूर्ण

अटल अंतरभूत पूर्णांक mlx5_core_mp_enabled(काष्ठा mlx5_core_dev *dev)
अणु
	वापस mlx5_core_is_mp_slave(dev) ||
	       mlx5_core_is_mp_master(dev);
पूर्ण

अटल अंतरभूत पूर्णांक mlx5_core_native_port_num(काष्ठा mlx5_core_dev *dev)
अणु
	अगर (!mlx5_core_mp_enabled(dev))
		वापस 1;

	वापस MLX5_CAP_GEN(dev, native_port_num);
पूर्ण

क्रमागत अणु
	MLX5_TRIGGERED_CMD_COMP = (u64)1 << 32,
पूर्ण;

अटल अंतरभूत bool mlx5_is_roce_init_enabled(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा devlink *devlink = priv_to_devlink(dev);
	जोड़ devlink_param_value val;

	devlink_param_driverinit_value_get(devlink,
					   DEVLINK_PARAM_GENERIC_ID_ENABLE_ROCE,
					   &val);
	वापस val.vbool;
पूर्ण

#पूर्ण_अगर /* MLX5_DRIVER_H */
