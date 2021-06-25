<शैली गुरु>
/*
 * Copyright (c) 2004, 2005 Topspin Communications.  All rights reserved.
 * Copyright (c) 2005 Sun Microप्रणालीs, Inc. All rights reserved.
 * Copyright (c) 2005, 2006, 2007 Cisco Systems.  All rights reserved.
 * Copyright (c) 2005, 2006, 2007, 2008 Mellanox Technologies. All rights reserved.
 * Copyright (c) 2004 Voltaire, Inc. All rights reserved.
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

#अगर_अघोषित MLX4_H
#घोषणा MLX4_H

#समावेश <linux/mutex.h>
#समावेश <linux/radix-tree.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/समयr.h>
#समावेश <linux/semaphore.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spinlock.h>
#समावेश <net/devlink.h>
#समावेश <linux/rwsem.h>

#समावेश <linux/mlx4/device.h>
#समावेश <linux/mlx4/driver.h>
#समावेश <linux/mlx4/करोorbell.h>
#समावेश <linux/mlx4/cmd.h>
#समावेश "fw_qos.h"

#घोषणा DRV_NAME	"mlx4_core"
#घोषणा DRV_VERSION	"4.0-0"
#घोषणा DRV_NAME_FOR_FW		"Linux," DRV_NAME "," DRV_VERSION

#घोषणा MLX4_FS_UDP_UC_EN		(1 << 1)
#घोषणा MLX4_FS_TCP_UC_EN		(1 << 2)
#घोषणा MLX4_FS_NUM_OF_L2_ADDR		8
#घोषणा MLX4_FS_MGM_LOG_ENTRY_SIZE	7
#घोषणा MLX4_FS_NUM_MCG			(1 << 17)

#घोषणा INIT_HCA_TPT_MW_ENABLE          (1 << 7)

#घोषणा MLX4_QUERY_IF_STAT_RESET	BIT(31)

क्रमागत अणु
	MLX4_HCR_BASE		= 0x80680,
	MLX4_HCR_SIZE		= 0x0001c,
	MLX4_CLR_INT_SIZE	= 0x00008,
	MLX4_SLAVE_COMM_BASE	= 0x0,
	MLX4_COMM_PAGESIZE	= 0x1000,
	MLX4_CLOCK_SIZE		= 0x00008,
	MLX4_COMM_CHAN_CAPS	= 0x8,
	MLX4_COMM_CHAN_FLAGS	= 0xc
पूर्ण;

क्रमागत अणु
	MLX4_DEFAULT_MGM_LOG_ENTRY_SIZE = 10,
	MLX4_MIN_MGM_LOG_ENTRY_SIZE = 7,
	MLX4_MAX_MGM_LOG_ENTRY_SIZE = 12,
	MLX4_MAX_QP_PER_MGM = 4 * ((1 << MLX4_MAX_MGM_LOG_ENTRY_SIZE) / 16 - 2),
पूर्ण;

क्रमागत अणु
	MLX4_NUM_PDS		= 1 << 15
पूर्ण;

क्रमागत अणु
	MLX4_CMPT_TYPE_QP	= 0,
	MLX4_CMPT_TYPE_SRQ	= 1,
	MLX4_CMPT_TYPE_CQ	= 2,
	MLX4_CMPT_TYPE_EQ	= 3,
	MLX4_CMPT_NUM_TYPE
पूर्ण;

क्रमागत अणु
	MLX4_CMPT_SHIFT		= 24,
	MLX4_NUM_CMPTS		= MLX4_CMPT_NUM_TYPE << MLX4_CMPT_SHIFT
पूर्ण;

क्रमागत mlx4_mpt_state अणु
	MLX4_MPT_DISABLED = 0,
	MLX4_MPT_EN_HW,
	MLX4_MPT_EN_SW
पूर्ण;

#घोषणा MLX4_COMM_TIME		10000
#घोषणा MLX4_COMM_OFFLINE_TIME_OUT 30000
#घोषणा MLX4_COMM_CMD_NA_OP    0x0


क्रमागत अणु
	MLX4_COMM_CMD_RESET,
	MLX4_COMM_CMD_VHCR0,
	MLX4_COMM_CMD_VHCR1,
	MLX4_COMM_CMD_VHCR2,
	MLX4_COMM_CMD_VHCR_EN,
	MLX4_COMM_CMD_VHCR_POST,
	MLX4_COMM_CMD_FLR = 254
पूर्ण;

क्रमागत अणु
	MLX4_VF_SMI_DISABLED,
	MLX4_VF_SMI_ENABLED
पूर्ण;

/*The flag indicates that the slave should delay the RESET cmd*/
#घोषणा MLX4_DELAY_RESET_SLAVE 0xbbbbbbb
/*indicates how many retries will be करोne अगर we are in the middle of FLR*/
#घोषणा NUM_OF_RESET_RETRIES	10
#घोषणा SLEEP_TIME_IN_RESET	(2 * 1000)
क्रमागत mlx4_resource अणु
	RES_QP,
	RES_CQ,
	RES_SRQ,
	RES_XRCD,
	RES_MPT,
	RES_MTT,
	RES_MAC,
	RES_VLAN,
	RES_NPORT_ID,
	RES_COUNTER,
	RES_FS_RULE,
	RES_EQ,
	MLX4_NUM_OF_RESOURCE_TYPE
पूर्ण;

क्रमागत mlx4_alloc_mode अणु
	RES_OP_RESERVE,
	RES_OP_RESERVE_AND_MAP,
	RES_OP_MAP_ICM,
पूर्ण;

क्रमागत mlx4_res_tracker_मुक्त_type अणु
	RES_TR_FREE_ALL,
	RES_TR_FREE_SLAVES_ONLY,
	RES_TR_FREE_STRUCTS_ONLY,
पूर्ण;

/*
 *Virtual HCR काष्ठाures.
 * mlx4_vhcr is the sw representation, in machine endianness
 *
 * mlx4_vhcr_cmd is the क्रमmalized काष्ठाure, the one that is passed
 * to FW to go through communication channel.
 * It is big endian, and has the same काष्ठाure as the physical HCR
 * used by command पूर्णांकerface
 */
काष्ठा mlx4_vhcr अणु
	u64	in_param;
	u64	out_param;
	u32	in_modअगरier;
	u32	त्रुटि_सं;
	u16	op;
	u16	token;
	u8	op_modअगरier;
	u8	e_bit;
पूर्ण;

काष्ठा mlx4_vhcr_cmd अणु
	__be64 in_param;
	__be32 in_modअगरier;
	u32 reserved1;
	__be64 out_param;
	__be16 token;
	u16 reserved;
	u8 status;
	u8 flags;
	__be16 opcode;
पूर्ण;

काष्ठा mlx4_cmd_info अणु
	u16 opcode;
	bool has_inbox;
	bool has_outbox;
	bool out_is_imm;
	bool encode_slave_id;
	पूर्णांक (*verअगरy)(काष्ठा mlx4_dev *dev, पूर्णांक slave, काष्ठा mlx4_vhcr *vhcr,
		      काष्ठा mlx4_cmd_mailbox *inbox);
	पूर्णांक (*wrapper)(काष्ठा mlx4_dev *dev, पूर्णांक slave, काष्ठा mlx4_vhcr *vhcr,
		       काष्ठा mlx4_cmd_mailbox *inbox,
		       काष्ठा mlx4_cmd_mailbox *outbox,
		       काष्ठा mlx4_cmd_info *cmd);
पूर्ण;

#अगर_घोषित CONFIG_MLX4_DEBUG
बाह्य पूर्णांक mlx4_debug_level;
#अन्यथा /* CONFIG_MLX4_DEBUG */
#घोषणा mlx4_debug_level	(0)
#पूर्ण_अगर /* CONFIG_MLX4_DEBUG */

#घोषणा mlx4_dbg(mdev, क्रमmat, ...)					\
करो अणु									\
	अगर (mlx4_debug_level)						\
		dev_prपूर्णांकk(KERN_DEBUG,					\
			   &(mdev)->persist->pdev->dev, क्रमmat,		\
			   ##__VA_ARGS__);				\
पूर्ण जबतक (0)

#घोषणा mlx4_err(mdev, क्रमmat, ...)					\
	dev_err(&(mdev)->persist->pdev->dev, क्रमmat, ##__VA_ARGS__)
#घोषणा mlx4_info(mdev, क्रमmat, ...)					\
	dev_info(&(mdev)->persist->pdev->dev, क्रमmat, ##__VA_ARGS__)
#घोषणा mlx4_warn(mdev, क्रमmat, ...)					\
	dev_warn(&(mdev)->persist->pdev->dev, क्रमmat, ##__VA_ARGS__)

बाह्य पूर्णांक log_mtts_per_seg;
बाह्य पूर्णांक mlx4_पूर्णांकernal_err_reset;

#घोषणा MLX4_MAX_NUM_SLAVES	(min(MLX4_MAX_NUM_PF + MLX4_MAX_NUM_VF, \
				     MLX4_MFUNC_MAX))
#घोषणा ALL_SLAVES 0xff

काष्ठा mlx4_biपंचांगap अणु
	u32			last;
	u32			top;
	u32			max;
	u32                     reserved_top;
	u32			mask;
	u32			avail;
	u32			effective_len;
	spinlock_t		lock;
	अचिन्हित दीर्घ	       *table;
पूर्ण;

काष्ठा mlx4_buddy अणु
	अचिन्हित दीर्घ	      **bits;
	अचिन्हित पूर्णांक	       *num_मुक्त;
	u32			max_order;
	spinlock_t		lock;
पूर्ण;

काष्ठा mlx4_icm;

काष्ठा mlx4_icm_table अणु
	u64			virt;
	पूर्णांक			num_icm;
	u32			num_obj;
	पूर्णांक			obj_size;
	पूर्णांक			lowmem;
	पूर्णांक			coherent;
	काष्ठा mutex		mutex;
	काष्ठा mlx4_icm	      **icm;
पूर्ण;

#घोषणा MLX4_MPT_FLAG_SW_OWNS	    (0xfUL << 28)
#घोषणा MLX4_MPT_FLAG_FREE	    (0x3UL << 28)
#घोषणा MLX4_MPT_FLAG_MIO	    (1 << 17)
#घोषणा MLX4_MPT_FLAG_BIND_ENABLE   (1 << 15)
#घोषणा MLX4_MPT_FLAG_PHYSICAL	    (1 <<  9)
#घोषणा MLX4_MPT_FLAG_REGION	    (1 <<  8)

#घोषणा MLX4_MPT_PD_MASK	    (0x1FFFFUL)
#घोषणा MLX4_MPT_PD_VF_MASK	    (0xFE0000UL)
#घोषणा MLX4_MPT_PD_FLAG_FAST_REG   (1 << 27)
#घोषणा MLX4_MPT_PD_FLAG_RAE	    (1 << 28)
#घोषणा MLX4_MPT_PD_FLAG_EN_INV	    (3 << 24)

#घोषणा MLX4_MPT_QP_FLAG_BOUND_QP   (1 << 7)

#घोषणा MLX4_MPT_STATUS_SW		0xF0
#घोषणा MLX4_MPT_STATUS_HW		0x00

#घोषणा MLX4_CQE_SIZE_MASK_STRIDE	0x3
#घोषणा MLX4_EQE_SIZE_MASK_STRIDE	0x30

#घोषणा MLX4_EQ_ASYNC			0
#घोषणा MLX4_EQ_TO_CQ_VECTOR(vector)	((vector) - \
					 !!((पूर्णांक)(vector) >= MLX4_EQ_ASYNC))
#घोषणा MLX4_CQ_TO_EQ_VECTOR(vector)	((vector) + \
					 !!((पूर्णांक)(vector) >= MLX4_EQ_ASYNC))

/*
 * Must be packed because mtt_seg is 64 bits but only aligned to 32 bits.
 */
काष्ठा mlx4_mpt_entry अणु
	__be32 flags;
	__be32 qpn;
	__be32 key;
	__be32 pd_flags;
	__be64 start;
	__be64 length;
	__be32 lkey;
	__be32 win_cnt;
	u8	reserved1[3];
	u8	mtt_rep;
	__be64 mtt_addr;
	__be32 mtt_sz;
	__be32 entity_size;
	__be32 first_byte_offset;
पूर्ण __packed;

/*
 * Must be packed because start is 64 bits but only aligned to 32 bits.
 */
काष्ठा mlx4_eq_context अणु
	__be32			flags;
	u16			reserved1[3];
	__be16			page_offset;
	u8			log_eq_size;
	u8			reserved2[4];
	u8			eq_period;
	u8			reserved3;
	u8			eq_max_count;
	u8			reserved4[3];
	u8			पूर्णांकr;
	u8			log_page_size;
	u8			reserved5[2];
	u8			mtt_base_addr_h;
	__be32			mtt_base_addr_l;
	u32			reserved6[2];
	__be32			consumer_index;
	__be32			producer_index;
	u32			reserved7[4];
पूर्ण;

काष्ठा mlx4_cq_context अणु
	__be32			flags;
	u16			reserved1[3];
	__be16			page_offset;
	__be32			logsize_usrpage;
	__be16			cq_period;
	__be16			cq_max_count;
	u8			reserved2[3];
	u8			comp_eqn;
	u8			log_page_size;
	u8			reserved3[2];
	u8			mtt_base_addr_h;
	__be32			mtt_base_addr_l;
	__be32			last_notअगरied_index;
	__be32			solicit_producer_index;
	__be32			consumer_index;
	__be32			producer_index;
	u32			reserved4[2];
	__be64			db_rec_addr;
पूर्ण;

काष्ठा mlx4_srq_context अणु
	__be32			state_logsize_srqn;
	u8			logstride;
	u8			reserved1;
	__be16			xrcd;
	__be32			pg_offset_cqn;
	u32			reserved2;
	u8			log_page_size;
	u8			reserved3[2];
	u8			mtt_base_addr_h;
	__be32			mtt_base_addr_l;
	__be32			pd;
	__be16			limit_watermark;
	__be16			wqe_cnt;
	u16			reserved4;
	__be16			wqe_counter;
	u32			reserved5;
	__be64			db_rec_addr;
पूर्ण;

काष्ठा mlx4_eq_tasklet अणु
	काष्ठा list_head list;
	काष्ठा list_head process_list;
	काष्ठा tasklet_काष्ठा task;
	/* lock on completion tasklet list */
	spinlock_t lock;
पूर्ण;

काष्ठा mlx4_eq अणु
	काष्ठा mlx4_dev	       *dev;
	व्योम __iomem	       *करोorbell;
	पूर्णांक			eqn;
	u32			cons_index;
	u16			irq;
	u16			have_irq;
	पूर्णांक			nent;
	काष्ठा mlx4_buf_list   *page_list;
	काष्ठा mlx4_mtt		mtt;
	काष्ठा mlx4_eq_tasklet	tasklet_ctx;
	काष्ठा mlx4_active_ports actv_ports;
	u32			ref_count;
	cpumask_var_t		affinity_mask;
पूर्ण;

काष्ठा mlx4_slave_eqe अणु
	u8 type;
	u8 port;
	u32 param;
पूर्ण;

काष्ठा mlx4_slave_event_eq_info अणु
	पूर्णांक eqn;
	u16 token;
पूर्ण;

काष्ठा mlx4_profile अणु
	पूर्णांक			num_qp;
	पूर्णांक			rdmarc_per_qp;
	पूर्णांक			num_srq;
	पूर्णांक			num_cq;
	पूर्णांक			num_mcg;
	पूर्णांक			num_mpt;
	अचिन्हित		num_mtt;
पूर्ण;

काष्ठा mlx4_fw अणु
	u64			clr_पूर्णांक_base;
	u64			catas_offset;
	u64			comm_base;
	u64			घड़ी_offset;
	काष्ठा mlx4_icm	       *fw_icm;
	काष्ठा mlx4_icm	       *aux_icm;
	u32			catas_size;
	u16			fw_pages;
	u8			clr_पूर्णांक_bar;
	u8			catas_bar;
	u8			comm_bar;
	u8			घड़ी_bar;
पूर्ण;

काष्ठा mlx4_comm अणु
	u32			slave_ग_लिखो;
	u32			slave_पढ़ो;
पूर्ण;

क्रमागत अणु
	MLX4_MCAST_CONFIG       = 0,
	MLX4_MCAST_DISABLE      = 1,
	MLX4_MCAST_ENABLE       = 2,
पूर्ण;

#घोषणा VLAN_FLTR_SIZE	128

काष्ठा mlx4_vlan_fltr अणु
	__be32 entry[VLAN_FLTR_SIZE];
पूर्ण;

काष्ठा mlx4_mcast_entry अणु
	काष्ठा list_head list;
	u64 addr;
पूर्ण;

काष्ठा mlx4_promisc_qp अणु
	काष्ठा list_head list;
	u32 qpn;
पूर्ण;

काष्ठा mlx4_steer_index अणु
	काष्ठा list_head list;
	अचिन्हित पूर्णांक index;
	काष्ठा list_head duplicates;
पूर्ण;

#घोषणा MLX4_EVENT_TYPES_NUM 64

काष्ठा mlx4_slave_state अणु
	u8 comm_toggle;
	u8 last_cmd;
	u8 init_port_mask;
	bool active;
	bool old_vlan_api;
	bool vst_qinq_supported;
	u8 function;
	dma_addr_t vhcr_dma;
	u16 user_mtu[MLX4_MAX_PORTS + 1];
	u16 mtu[MLX4_MAX_PORTS + 1];
	__be32 ib_cap_mask[MLX4_MAX_PORTS + 1];
	काष्ठा mlx4_slave_eqe eq[MLX4_MFUNC_MAX_EQES];
	काष्ठा list_head mcast_filters[MLX4_MAX_PORTS + 1];
	काष्ठा mlx4_vlan_fltr *vlan_filter[MLX4_MAX_PORTS + 1];
	/* event type to eq number lookup */
	काष्ठा mlx4_slave_event_eq_info event_eq[MLX4_EVENT_TYPES_NUM];
	u16 eq_pi;
	u16 eq_ci;
	spinlock_t lock;
	/*initialized via the kzalloc*/
	u8 is_slave_going_करोwn;
	u32 cookie;
	क्रमागत slave_port_state port_state[MLX4_MAX_PORTS + 1];
पूर्ण;

#घोषणा MLX4_VGT 4095
#घोषणा NO_INDX  (-1)

काष्ठा mlx4_vport_state अणु
	u64 mac;
	u16 शेष_vlan;
	u8  शेष_qos;
	__be16 vlan_proto;
	u32 tx_rate;
	bool spoofchk;
	u32 link_state;
	u8 qos_vport;
	__be64 guid;
पूर्ण;

काष्ठा mlx4_vf_admin_state अणु
	काष्ठा mlx4_vport_state vport[MLX4_MAX_PORTS + 1];
	u8 enable_smi[MLX4_MAX_PORTS + 1];
पूर्ण;

काष्ठा mlx4_vport_oper_state अणु
	काष्ठा mlx4_vport_state state;
	पूर्णांक mac_idx;
	पूर्णांक vlan_idx;
पूर्ण;

काष्ठा mlx4_vf_oper_state अणु
	काष्ठा mlx4_vport_oper_state vport[MLX4_MAX_PORTS + 1];
	u8 smi_enabled[MLX4_MAX_PORTS + 1];
पूर्ण;

काष्ठा slave_list अणु
	काष्ठा mutex mutex;
	काष्ठा list_head res_list[MLX4_NUM_OF_RESOURCE_TYPE];
पूर्ण;

काष्ठा resource_allocator अणु
	spinlock_t alloc_lock; /* protect quotas */
	जोड़ अणु
		अचिन्हित पूर्णांक res_reserved;
		अचिन्हित पूर्णांक res_port_rsvd[MLX4_MAX_PORTS];
	पूर्ण;
	जोड़ अणु
		पूर्णांक res_मुक्त;
		पूर्णांक res_port_मुक्त[MLX4_MAX_PORTS];
	पूर्ण;
	पूर्णांक *quota;
	पूर्णांक *allocated;
	पूर्णांक *guaranteed;
पूर्ण;

काष्ठा mlx4_resource_tracker अणु
	spinlock_t lock;
	/* tree क्रम each resources */
	काष्ठा rb_root res_tree[MLX4_NUM_OF_RESOURCE_TYPE];
	/* num_of_slave's lists, one per slave */
	काष्ठा slave_list *slave_list;
	काष्ठा resource_allocator res_alloc[MLX4_NUM_OF_RESOURCE_TYPE];
पूर्ण;

#घोषणा SLAVE_EVENT_EQ_SIZE	128
काष्ठा mlx4_slave_event_eq अणु
	u32 eqn;
	u32 cons;
	u32 prod;
	spinlock_t event_lock;
	काष्ठा mlx4_eqe event_eqe[SLAVE_EVENT_EQ_SIZE];
पूर्ण;

काष्ठा mlx4_qos_manager अणु
	पूर्णांक num_of_qos_vfs;
	DECLARE_BITMAP(priority_bm, MLX4_NUM_UP);
पूर्ण;

काष्ठा mlx4_master_qp0_state अणु
	पूर्णांक proxy_qp0_active;
	पूर्णांक qp0_active;
	पूर्णांक port_active;
पूर्ण;

काष्ठा mlx4_mfunc_master_ctx अणु
	काष्ठा mlx4_slave_state *slave_state;
	काष्ठा mlx4_vf_admin_state *vf_admin;
	काष्ठा mlx4_vf_oper_state *vf_oper;
	काष्ठा mlx4_master_qp0_state qp0_state[MLX4_MAX_PORTS + 1];
	पूर्णांक			init_port_ref[MLX4_MAX_PORTS + 1];
	u16			max_mtu[MLX4_MAX_PORTS + 1];
	u16			max_user_mtu[MLX4_MAX_PORTS + 1];
	u8			pptx;
	u8			pprx;
	पूर्णांक			disable_mcast_ref[MLX4_MAX_PORTS + 1];
	काष्ठा mlx4_resource_tracker res_tracker;
	काष्ठा workqueue_काष्ठा *comm_wq;
	काष्ठा work_काष्ठा	comm_work;
	काष्ठा work_काष्ठा	slave_event_work;
	काष्ठा work_काष्ठा	slave_flr_event_work;
	spinlock_t		slave_state_lock;
	__be32			comm_arm_bit_vector[4];
	काष्ठा mlx4_eqe		cmd_eqe;
	काष्ठा mlx4_slave_event_eq slave_eq;
	काष्ठा mutex		gen_eqe_mutex[MLX4_MFUNC_MAX];
	काष्ठा mlx4_qos_manager qos_ctl[MLX4_MAX_PORTS + 1];
	u32			next_slave; /* mlx4_master_comm_channel */
पूर्ण;

काष्ठा mlx4_mfunc अणु
	काष्ठा mlx4_comm __iomem       *comm;
	काष्ठा mlx4_vhcr_cmd	       *vhcr;
	dma_addr_t			vhcr_dma;

	काष्ठा mlx4_mfunc_master_ctx	master;
पूर्ण;

#घोषणा MGM_QPN_MASK       0x00FFFFFF
#घोषणा MGM_BLCK_LB_BIT    30

काष्ठा mlx4_mgm अणु
	__be32			next_gid_index;
	__be32			members_count;
	u32			reserved[2];
	u8			gid[16];
	__be32			qp[MLX4_MAX_QP_PER_MGM];
पूर्ण;

काष्ठा mlx4_cmd अणु
	काष्ठा dma_pool	       *pool;
	व्योम __iomem	       *hcr;
	काष्ठा mutex		slave_cmd_mutex;
	काष्ठा semaphore	poll_sem;
	काष्ठा semaphore	event_sem;
	काष्ठा rw_semaphore	चयन_sem;
	पूर्णांक			max_cmds;
	spinlock_t		context_lock;
	पूर्णांक			मुक्त_head;
	काष्ठा mlx4_cmd_context *context;
	u16			token_mask;
	u8			use_events;
	u8			toggle;
	u8			comm_toggle;
	u8			initialized;
पूर्ण;

क्रमागत अणु
	MLX4_VF_IMMED_VLAN_FLAG_VLAN = 1 << 0,
	MLX4_VF_IMMED_VLAN_FLAG_QOS = 1 << 1,
	MLX4_VF_IMMED_VLAN_FLAG_LINK_DISABLE = 1 << 2,
पूर्ण;
काष्ठा mlx4_vf_immed_vlan_work अणु
	काष्ठा work_काष्ठा	work;
	काष्ठा mlx4_priv	*priv;
	पूर्णांक			flags;
	पूर्णांक			slave;
	पूर्णांक			vlan_ix;
	पूर्णांक			orig_vlan_ix;
	u8			port;
	u8			qos;
	u8                      qos_vport;
	u16			vlan_id;
	u16			orig_vlan_id;
	__be16			vlan_proto;
पूर्ण;


काष्ठा mlx4_uar_table अणु
	काष्ठा mlx4_biपंचांगap	biपंचांगap;
पूर्ण;

काष्ठा mlx4_mr_table अणु
	काष्ठा mlx4_biपंचांगap	mpt_biपंचांगap;
	काष्ठा mlx4_buddy	mtt_buddy;
	u64			mtt_base;
	u64			mpt_base;
	काष्ठा mlx4_icm_table	mtt_table;
	काष्ठा mlx4_icm_table	dmpt_table;
पूर्ण;

काष्ठा mlx4_cq_table अणु
	काष्ठा mlx4_biपंचांगap	biपंचांगap;
	spinlock_t		lock;
	काष्ठा radix_tree_root	tree;
	काष्ठा mlx4_icm_table	table;
	काष्ठा mlx4_icm_table	cmpt_table;
पूर्ण;

काष्ठा mlx4_eq_table अणु
	काष्ठा mlx4_biपंचांगap	biपंचांगap;
	अक्षर		       *irq_names;
	व्योम __iomem	       *clr_पूर्णांक;
	व्योम __iomem	      **uar_map;
	u32			clr_mask;
	काष्ठा mlx4_eq	       *eq;
	काष्ठा mlx4_icm_table	table;
	काष्ठा mlx4_icm_table	cmpt_table;
	पूर्णांक			have_irq;
	u8			पूर्णांकa_pin;
पूर्ण;

काष्ठा mlx4_srq_table अणु
	काष्ठा mlx4_biपंचांगap	biपंचांगap;
	spinlock_t		lock;
	काष्ठा radix_tree_root	tree;
	काष्ठा mlx4_icm_table	table;
	काष्ठा mlx4_icm_table	cmpt_table;
पूर्ण;

क्रमागत mlx4_qp_table_zones अणु
	MLX4_QP_TABLE_ZONE_GENERAL,
	MLX4_QP_TABLE_ZONE_RSS,
	MLX4_QP_TABLE_ZONE_RAW_ETH,
	MLX4_QP_TABLE_ZONE_NUM
पूर्ण;

काष्ठा mlx4_qp_table अणु
	काष्ठा mlx4_biपंचांगap	*biपंचांगap_gen;
	काष्ठा mlx4_zone_allocator *zones;
	u32			zones_uids[MLX4_QP_TABLE_ZONE_NUM];
	u32			rdmarc_base;
	पूर्णांक			rdmarc_shअगरt;
	spinlock_t		lock;
	काष्ठा mlx4_icm_table	qp_table;
	काष्ठा mlx4_icm_table	auxc_table;
	काष्ठा mlx4_icm_table	altc_table;
	काष्ठा mlx4_icm_table	rdmarc_table;
	काष्ठा mlx4_icm_table	cmpt_table;
पूर्ण;

काष्ठा mlx4_mcg_table अणु
	काष्ठा mutex		mutex;
	काष्ठा mlx4_biपंचांगap	biपंचांगap;
	काष्ठा mlx4_icm_table	table;
पूर्ण;

काष्ठा mlx4_catas_err अणु
	u32 __iomem	       *map;
	काष्ठा समयr_list	समयr;
	काष्ठा list_head	list;
पूर्ण;

#घोषणा MLX4_MAX_MAC_NUM	128
#घोषणा MLX4_MAC_TABLE_SIZE	(MLX4_MAX_MAC_NUM << 3)

काष्ठा mlx4_mac_table अणु
	__be64			entries[MLX4_MAX_MAC_NUM];
	पूर्णांक			refs[MLX4_MAX_MAC_NUM];
	bool			is_dup[MLX4_MAX_MAC_NUM];
	काष्ठा mutex		mutex;
	पूर्णांक			total;
	पूर्णांक			max;
पूर्ण;

#घोषणा MLX4_ROCE_GID_ENTRY_SIZE	16

काष्ठा mlx4_roce_gid_entry अणु
	u8 raw[MLX4_ROCE_GID_ENTRY_SIZE];
पूर्ण;

काष्ठा mlx4_roce_gid_table अणु
	काष्ठा mlx4_roce_gid_entry	roce_gids[MLX4_ROCE_MAX_GIDS];
	काष्ठा mutex			mutex;
पूर्ण;

#घोषणा MLX4_MAX_VLAN_NUM	128
#घोषणा MLX4_VLAN_TABLE_SIZE	(MLX4_MAX_VLAN_NUM << 2)

काष्ठा mlx4_vlan_table अणु
	__be32			entries[MLX4_MAX_VLAN_NUM];
	पूर्णांक			refs[MLX4_MAX_VLAN_NUM];
	पूर्णांक			is_dup[MLX4_MAX_VLAN_NUM];
	काष्ठा mutex		mutex;
	पूर्णांक			total;
	पूर्णांक			max;
पूर्ण;

#घोषणा SET_PORT_GEN_ALL_VALID	(MLX4_FLAG_V_MTU_MASK	| \
				 MLX4_FLAG_V_PPRX_MASK	| \
				 MLX4_FLAG_V_PPTX_MASK)
#घोषणा SET_PORT_PROMISC_SHIFT		31
#घोषणा SET_PORT_MC_PROMISC_SHIFT	30

क्रमागत अणु
	MCAST_सूचीECT_ONLY	= 0,
	MCAST_सूचीECT		= 1,
	MCAST_DEFAULT		= 2
पूर्ण;


काष्ठा mlx4_set_port_general_context अणु
	u16 reserved1;
	u8 flags2;
	u8 flags;
	जोड़ अणु
		u8 ignore_fcs;
		u8 roce_mode;
	पूर्ण;
	u8 reserved2;
	__be16 mtu;
	u8 pptx;
	u8 pfctx;
	u16 reserved3;
	u8 pprx;
	u8 pfcrx;
	u16 reserved4;
	u32 reserved5;
	u8 phv_en;
	u8 reserved6[5];
	__be16 user_mtu;
	u16 reserved7;
	u8 user_mac[6];
पूर्ण;

काष्ठा mlx4_set_port_rqp_calc_context अणु
	__be32 base_qpn;
	u8 rererved;
	u8 n_mac;
	u8 n_vlan;
	u8 n_prio;
	u8 reserved2[3];
	u8 mac_miss;
	u8 पूर्णांकra_no_vlan;
	u8 no_vlan;
	u8 पूर्णांकra_vlan_miss;
	u8 vlan_miss;
	u8 reserved3[3];
	u8 no_vlan_prio;
	__be32 promisc;
	__be32 mcast;
पूर्ण;

काष्ठा mlx4_port_info अणु
	काष्ठा mlx4_dev	       *dev;
	पूर्णांक			port;
	अक्षर			dev_name[16];
	काष्ठा device_attribute port_attr;
	क्रमागत mlx4_port_type	पंचांगp_type;
	अक्षर			dev_mtu_name[16];
	काष्ठा device_attribute port_mtu_attr;
	काष्ठा mlx4_mac_table	mac_table;
	काष्ठा mlx4_vlan_table	vlan_table;
	काष्ठा mlx4_roce_gid_table gid_table;
	पूर्णांक			base_qpn;
	काष्ठा cpu_rmap		*rmap;
	काष्ठा devlink_port	devlink_port;
पूर्ण;

काष्ठा mlx4_sense अणु
	काष्ठा mlx4_dev		*dev;
	u8			करो_sense_port[MLX4_MAX_PORTS + 1];
	u8			sense_allowed[MLX4_MAX_PORTS + 1];
	काष्ठा delayed_work	sense_poll;
पूर्ण;

काष्ठा mlx4_msix_ctl अणु
	DECLARE_BITMAP(pool_bm, MAX_MSIX);
	काष्ठा mutex	pool_lock;
पूर्ण;

काष्ठा mlx4_steer अणु
	काष्ठा list_head promisc_qps[MLX4_NUM_STEERS];
	काष्ठा list_head steer_entries[MLX4_NUM_STEERS];
पूर्ण;

क्रमागत अणु
	MLX4_PCI_DEV_IS_VF		= 1 << 0,
	MLX4_PCI_DEV_FORCE_SENSE_PORT	= 1 << 1,
पूर्ण;

क्रमागत अणु
	MLX4_NO_RR	= 0,
	MLX4_USE_RR	= 1,
पूर्ण;

काष्ठा mlx4_priv अणु
	काष्ठा mlx4_dev		dev;

	काष्ठा list_head	dev_list;
	काष्ठा list_head	ctx_list;
	spinlock_t		ctx_lock;

	पूर्णांक			pci_dev_data;
	पूर्णांक                     हटाओd;

	काष्ठा list_head        pgdir_list;
	काष्ठा mutex            pgdir_mutex;

	काष्ठा mlx4_fw		fw;
	काष्ठा mlx4_cmd		cmd;
	काष्ठा mlx4_mfunc	mfunc;

	काष्ठा mlx4_biपंचांगap	pd_biपंचांगap;
	काष्ठा mlx4_biपंचांगap	xrcd_biपंचांगap;
	काष्ठा mlx4_uar_table	uar_table;
	काष्ठा mlx4_mr_table	mr_table;
	काष्ठा mlx4_cq_table	cq_table;
	काष्ठा mlx4_eq_table	eq_table;
	काष्ठा mlx4_srq_table	srq_table;
	काष्ठा mlx4_qp_table	qp_table;
	काष्ठा mlx4_mcg_table	mcg_table;
	काष्ठा mlx4_biपंचांगap	counters_biपंचांगap;
	पूर्णांक			def_counter[MLX4_MAX_PORTS];

	काष्ठा mlx4_catas_err	catas_err;

	व्योम __iomem	       *clr_base;

	काष्ठा mlx4_uar		driver_uar;
	व्योम __iomem	       *kar;
	काष्ठा mlx4_port_info	port[MLX4_MAX_PORTS + 1];
	काष्ठा mlx4_sense       sense;
	काष्ठा mutex		port_mutex;
	काष्ठा mlx4_msix_ctl	msix_ctl;
	काष्ठा mlx4_steer	*steer;
	काष्ठा list_head	bf_list;
	काष्ठा mutex		bf_mutex;
	काष्ठा io_mapping	*bf_mapping;
	व्योम __iomem            *घड़ी_mapping;
	पूर्णांक			reserved_mtts;
	पूर्णांक			fs_hash_mode;
	u8 virt2phys_pkey[MLX4_MFUNC_MAX][MLX4_MAX_PORTS][MLX4_MAX_PORT_PKEYS];
	काष्ठा mlx4_port_map	v2p; /* cached port mapping configuration */
	काष्ठा mutex		bond_mutex; /* क्रम bond mode */
	__be64			slave_node_guids[MLX4_MFUNC_MAX];

	atomic_t		opreq_count;
	काष्ठा work_काष्ठा	opreq_task;
पूर्ण;

अटल अंतरभूत काष्ठा mlx4_priv *mlx4_priv(काष्ठा mlx4_dev *dev)
अणु
	वापस container_of(dev, काष्ठा mlx4_priv, dev);
पूर्ण

#घोषणा MLX4_SENSE_RANGE	(HZ * 3)

बाह्य काष्ठा workqueue_काष्ठा *mlx4_wq;

u32 mlx4_biपंचांगap_alloc(काष्ठा mlx4_biपंचांगap *biपंचांगap);
व्योम mlx4_biपंचांगap_मुक्त(काष्ठा mlx4_biपंचांगap *biपंचांगap, u32 obj, पूर्णांक use_rr);
u32 mlx4_biपंचांगap_alloc_range(काष्ठा mlx4_biपंचांगap *biपंचांगap, पूर्णांक cnt,
			    पूर्णांक align, u32 skip_mask);
व्योम mlx4_biपंचांगap_मुक्त_range(काष्ठा mlx4_biपंचांगap *biपंचांगap, u32 obj, पूर्णांक cnt,
			    पूर्णांक use_rr);
u32 mlx4_biपंचांगap_avail(काष्ठा mlx4_biपंचांगap *biपंचांगap);
पूर्णांक mlx4_biपंचांगap_init(काष्ठा mlx4_biपंचांगap *biपंचांगap, u32 num, u32 mask,
		     u32 reserved_bot, u32 resetrved_top);
व्योम mlx4_biपंचांगap_cleanup(काष्ठा mlx4_biपंचांगap *biपंचांगap);

पूर्णांक mlx4_reset(काष्ठा mlx4_dev *dev);

पूर्णांक mlx4_alloc_eq_table(काष्ठा mlx4_dev *dev);
व्योम mlx4_मुक्त_eq_table(काष्ठा mlx4_dev *dev);

पूर्णांक mlx4_init_pd_table(काष्ठा mlx4_dev *dev);
पूर्णांक mlx4_init_xrcd_table(काष्ठा mlx4_dev *dev);
पूर्णांक mlx4_init_uar_table(काष्ठा mlx4_dev *dev);
पूर्णांक mlx4_init_mr_table(काष्ठा mlx4_dev *dev);
पूर्णांक mlx4_init_eq_table(काष्ठा mlx4_dev *dev);
पूर्णांक mlx4_init_cq_table(काष्ठा mlx4_dev *dev);
पूर्णांक mlx4_init_qp_table(काष्ठा mlx4_dev *dev);
पूर्णांक mlx4_init_srq_table(काष्ठा mlx4_dev *dev);
पूर्णांक mlx4_init_mcg_table(काष्ठा mlx4_dev *dev);

व्योम mlx4_cleanup_pd_table(काष्ठा mlx4_dev *dev);
व्योम mlx4_cleanup_xrcd_table(काष्ठा mlx4_dev *dev);
व्योम mlx4_cleanup_uar_table(काष्ठा mlx4_dev *dev);
व्योम mlx4_cleanup_mr_table(काष्ठा mlx4_dev *dev);
व्योम mlx4_cleanup_eq_table(काष्ठा mlx4_dev *dev);
व्योम mlx4_cleanup_cq_table(काष्ठा mlx4_dev *dev);
व्योम mlx4_cleanup_qp_table(काष्ठा mlx4_dev *dev);
व्योम mlx4_cleanup_srq_table(काष्ठा mlx4_dev *dev);
व्योम mlx4_cleanup_mcg_table(काष्ठा mlx4_dev *dev);
पूर्णांक __mlx4_qp_alloc_icm(काष्ठा mlx4_dev *dev, पूर्णांक qpn);
व्योम __mlx4_qp_मुक्त_icm(काष्ठा mlx4_dev *dev, पूर्णांक qpn);
पूर्णांक __mlx4_cq_alloc_icm(काष्ठा mlx4_dev *dev, पूर्णांक *cqn);
व्योम __mlx4_cq_मुक्त_icm(काष्ठा mlx4_dev *dev, पूर्णांक cqn);
पूर्णांक __mlx4_srq_alloc_icm(काष्ठा mlx4_dev *dev, पूर्णांक *srqn);
व्योम __mlx4_srq_मुक्त_icm(काष्ठा mlx4_dev *dev, पूर्णांक srqn);
पूर्णांक __mlx4_mpt_reserve(काष्ठा mlx4_dev *dev);
व्योम __mlx4_mpt_release(काष्ठा mlx4_dev *dev, u32 index);
पूर्णांक __mlx4_mpt_alloc_icm(काष्ठा mlx4_dev *dev, u32 index);
व्योम __mlx4_mpt_मुक्त_icm(काष्ठा mlx4_dev *dev, u32 index);
u32 __mlx4_alloc_mtt_range(काष्ठा mlx4_dev *dev, पूर्णांक order);
व्योम __mlx4_मुक्त_mtt_range(काष्ठा mlx4_dev *dev, u32 first_seg, पूर्णांक order);

पूर्णांक mlx4_WRITE_MTT_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			   काष्ठा mlx4_vhcr *vhcr,
			   काष्ठा mlx4_cmd_mailbox *inbox,
			   काष्ठा mlx4_cmd_mailbox *outbox,
			   काष्ठा mlx4_cmd_info *cmd);
पूर्णांक mlx4_SYNC_TPT_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			   काष्ठा mlx4_vhcr *vhcr,
			   काष्ठा mlx4_cmd_mailbox *inbox,
			   काष्ठा mlx4_cmd_mailbox *outbox,
			   काष्ठा mlx4_cmd_info *cmd);
पूर्णांक mlx4_SW2HW_MPT_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			   काष्ठा mlx4_vhcr *vhcr,
			   काष्ठा mlx4_cmd_mailbox *inbox,
			   काष्ठा mlx4_cmd_mailbox *outbox,
			   काष्ठा mlx4_cmd_info *cmd);
पूर्णांक mlx4_HW2SW_MPT_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			   काष्ठा mlx4_vhcr *vhcr,
			   काष्ठा mlx4_cmd_mailbox *inbox,
			   काष्ठा mlx4_cmd_mailbox *outbox,
			   काष्ठा mlx4_cmd_info *cmd);
पूर्णांक mlx4_QUERY_MPT_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			   काष्ठा mlx4_vhcr *vhcr,
			   काष्ठा mlx4_cmd_mailbox *inbox,
			   काष्ठा mlx4_cmd_mailbox *outbox,
			   काष्ठा mlx4_cmd_info *cmd);
पूर्णांक mlx4_SW2HW_EQ_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			  काष्ठा mlx4_vhcr *vhcr,
			  काष्ठा mlx4_cmd_mailbox *inbox,
			  काष्ठा mlx4_cmd_mailbox *outbox,
			  काष्ठा mlx4_cmd_info *cmd);
पूर्णांक mlx4_CONFIG_DEV_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			    काष्ठा mlx4_vhcr *vhcr,
			    काष्ठा mlx4_cmd_mailbox *inbox,
			    काष्ठा mlx4_cmd_mailbox *outbox,
			    काष्ठा mlx4_cmd_info *cmd);
पूर्णांक mlx4_DMA_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
		     काष्ठा mlx4_vhcr *vhcr,
		     काष्ठा mlx4_cmd_mailbox *inbox,
		     काष्ठा mlx4_cmd_mailbox *outbox,
		     काष्ठा mlx4_cmd_info *cmd);
पूर्णांक __mlx4_qp_reserve_range(काष्ठा mlx4_dev *dev, पूर्णांक cnt, पूर्णांक align,
			    पूर्णांक *base, u8 flags);
व्योम __mlx4_qp_release_range(काष्ठा mlx4_dev *dev, पूर्णांक base_qpn, पूर्णांक cnt);
पूर्णांक __mlx4_रेजिस्टर_mac(काष्ठा mlx4_dev *dev, u8 port, u64 mac);
व्योम __mlx4_unरेजिस्टर_mac(काष्ठा mlx4_dev *dev, u8 port, u64 mac);
पूर्णांक __mlx4_ग_लिखो_mtt(काष्ठा mlx4_dev *dev, काष्ठा mlx4_mtt *mtt,
		     पूर्णांक start_index, पूर्णांक npages, u64 *page_list);
पूर्णांक __mlx4_counter_alloc(काष्ठा mlx4_dev *dev, u32 *idx);
व्योम __mlx4_counter_मुक्त(काष्ठा mlx4_dev *dev, u32 idx);
पूर्णांक mlx4_calc_vf_counters(काष्ठा mlx4_dev *dev, पूर्णांक slave, पूर्णांक port,
			  काष्ठा mlx4_counter *data);
पूर्णांक __mlx4_xrcd_alloc(काष्ठा mlx4_dev *dev, u32 *xrcdn);
व्योम __mlx4_xrcd_मुक्त(काष्ठा mlx4_dev *dev, u32 xrcdn);

व्योम mlx4_start_catas_poll(काष्ठा mlx4_dev *dev);
व्योम mlx4_stop_catas_poll(काष्ठा mlx4_dev *dev);
पूर्णांक mlx4_catas_init(काष्ठा mlx4_dev *dev);
व्योम mlx4_catas_end(काष्ठा mlx4_dev *dev);
पूर्णांक mlx4_crdump_init(काष्ठा mlx4_dev *dev);
व्योम mlx4_crdump_end(काष्ठा mlx4_dev *dev);
पूर्णांक mlx4_restart_one(काष्ठा pci_dev *pdev);
पूर्णांक mlx4_रेजिस्टर_device(काष्ठा mlx4_dev *dev);
व्योम mlx4_unरेजिस्टर_device(काष्ठा mlx4_dev *dev);
व्योम mlx4_dispatch_event(काष्ठा mlx4_dev *dev, क्रमागत mlx4_dev_event type,
			 अचिन्हित दीर्घ param);

काष्ठा mlx4_dev_cap;
काष्ठा mlx4_init_hca_param;

u64 mlx4_make_profile(काष्ठा mlx4_dev *dev,
		      काष्ठा mlx4_profile *request,
		      काष्ठा mlx4_dev_cap *dev_cap,
		      काष्ठा mlx4_init_hca_param *init_hca);
व्योम mlx4_master_comm_channel(काष्ठा work_काष्ठा *work);
व्योम mlx4_gen_slave_eqe(काष्ठा work_काष्ठा *work);
व्योम mlx4_master_handle_slave_flr(काष्ठा work_काष्ठा *work);

पूर्णांक mlx4_ALLOC_RES_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			   काष्ठा mlx4_vhcr *vhcr,
			   काष्ठा mlx4_cmd_mailbox *inbox,
			   काष्ठा mlx4_cmd_mailbox *outbox,
			   काष्ठा mlx4_cmd_info *cmd);
पूर्णांक mlx4_FREE_RES_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			  काष्ठा mlx4_vhcr *vhcr,
			  काष्ठा mlx4_cmd_mailbox *inbox,
			  काष्ठा mlx4_cmd_mailbox *outbox,
			  काष्ठा mlx4_cmd_info *cmd);
पूर्णांक mlx4_MAP_EQ_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			काष्ठा mlx4_vhcr *vhcr, काष्ठा mlx4_cmd_mailbox *inbox,
			काष्ठा mlx4_cmd_mailbox *outbox,
			काष्ठा mlx4_cmd_info *cmd);
पूर्णांक mlx4_COMM_INT_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			  काष्ठा mlx4_vhcr *vhcr,
			  काष्ठा mlx4_cmd_mailbox *inbox,
			  काष्ठा mlx4_cmd_mailbox *outbox,
			  काष्ठा mlx4_cmd_info *cmd);
पूर्णांक mlx4_HW2SW_EQ_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			    काष्ठा mlx4_vhcr *vhcr,
			    काष्ठा mlx4_cmd_mailbox *inbox,
			    काष्ठा mlx4_cmd_mailbox *outbox,
			  काष्ठा mlx4_cmd_info *cmd);
पूर्णांक mlx4_QUERY_EQ_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			  काष्ठा mlx4_vhcr *vhcr,
			  काष्ठा mlx4_cmd_mailbox *inbox,
			  काष्ठा mlx4_cmd_mailbox *outbox,
			  काष्ठा mlx4_cmd_info *cmd);
पूर्णांक mlx4_SW2HW_CQ_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			  काष्ठा mlx4_vhcr *vhcr,
			  काष्ठा mlx4_cmd_mailbox *inbox,
			  काष्ठा mlx4_cmd_mailbox *outbox,
			  काष्ठा mlx4_cmd_info *cmd);
पूर्णांक mlx4_HW2SW_CQ_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			  काष्ठा mlx4_vhcr *vhcr,
			  काष्ठा mlx4_cmd_mailbox *inbox,
			  काष्ठा mlx4_cmd_mailbox *outbox,
			  काष्ठा mlx4_cmd_info *cmd);
पूर्णांक mlx4_QUERY_CQ_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			  काष्ठा mlx4_vhcr *vhcr,
			  काष्ठा mlx4_cmd_mailbox *inbox,
			  काष्ठा mlx4_cmd_mailbox *outbox,
			  काष्ठा mlx4_cmd_info *cmd);
पूर्णांक mlx4_MODIFY_CQ_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			  काष्ठा mlx4_vhcr *vhcr,
			  काष्ठा mlx4_cmd_mailbox *inbox,
			  काष्ठा mlx4_cmd_mailbox *outbox,
			   काष्ठा mlx4_cmd_info *cmd);
पूर्णांक mlx4_SW2HW_SRQ_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			   काष्ठा mlx4_vhcr *vhcr,
			   काष्ठा mlx4_cmd_mailbox *inbox,
			   काष्ठा mlx4_cmd_mailbox *outbox,
			   काष्ठा mlx4_cmd_info *cmd);
पूर्णांक mlx4_HW2SW_SRQ_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			   काष्ठा mlx4_vhcr *vhcr,
			   काष्ठा mlx4_cmd_mailbox *inbox,
			   काष्ठा mlx4_cmd_mailbox *outbox,
			   काष्ठा mlx4_cmd_info *cmd);
पूर्णांक mlx4_QUERY_SRQ_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			   काष्ठा mlx4_vhcr *vhcr,
			   काष्ठा mlx4_cmd_mailbox *inbox,
			   काष्ठा mlx4_cmd_mailbox *outbox,
			   काष्ठा mlx4_cmd_info *cmd);
पूर्णांक mlx4_ARM_SRQ_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			 काष्ठा mlx4_vhcr *vhcr,
			 काष्ठा mlx4_cmd_mailbox *inbox,
			 काष्ठा mlx4_cmd_mailbox *outbox,
			 काष्ठा mlx4_cmd_info *cmd);
पूर्णांक mlx4_GEN_QP_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			काष्ठा mlx4_vhcr *vhcr,
			काष्ठा mlx4_cmd_mailbox *inbox,
			काष्ठा mlx4_cmd_mailbox *outbox,
			काष्ठा mlx4_cmd_info *cmd);
पूर्णांक mlx4_RST2INIT_QP_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			     काष्ठा mlx4_vhcr *vhcr,
			     काष्ठा mlx4_cmd_mailbox *inbox,
			     काष्ठा mlx4_cmd_mailbox *outbox,
			     काष्ठा mlx4_cmd_info *cmd);
पूर्णांक mlx4_INIT2INIT_QP_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			      काष्ठा mlx4_vhcr *vhcr,
			      काष्ठा mlx4_cmd_mailbox *inbox,
			      काष्ठा mlx4_cmd_mailbox *outbox,
			      काष्ठा mlx4_cmd_info *cmd);
पूर्णांक mlx4_INIT2RTR_QP_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			     काष्ठा mlx4_vhcr *vhcr,
			     काष्ठा mlx4_cmd_mailbox *inbox,
			     काष्ठा mlx4_cmd_mailbox *outbox,
			     काष्ठा mlx4_cmd_info *cmd);
पूर्णांक mlx4_RTR2RTS_QP_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			    काष्ठा mlx4_vhcr *vhcr,
			    काष्ठा mlx4_cmd_mailbox *inbox,
			    काष्ठा mlx4_cmd_mailbox *outbox,
			    काष्ठा mlx4_cmd_info *cmd);
पूर्णांक mlx4_RTS2RTS_QP_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			    काष्ठा mlx4_vhcr *vhcr,
			    काष्ठा mlx4_cmd_mailbox *inbox,
			    काष्ठा mlx4_cmd_mailbox *outbox,
			    काष्ठा mlx4_cmd_info *cmd);
पूर्णांक mlx4_SQERR2RTS_QP_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			      काष्ठा mlx4_vhcr *vhcr,
			      काष्ठा mlx4_cmd_mailbox *inbox,
			      काष्ठा mlx4_cmd_mailbox *outbox,
			      काष्ठा mlx4_cmd_info *cmd);
पूर्णांक mlx4_2ERR_QP_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			 काष्ठा mlx4_vhcr *vhcr,
			 काष्ठा mlx4_cmd_mailbox *inbox,
			 काष्ठा mlx4_cmd_mailbox *outbox,
			 काष्ठा mlx4_cmd_info *cmd);
पूर्णांक mlx4_RTS2SQD_QP_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			    काष्ठा mlx4_vhcr *vhcr,
			    काष्ठा mlx4_cmd_mailbox *inbox,
			    काष्ठा mlx4_cmd_mailbox *outbox,
			    काष्ठा mlx4_cmd_info *cmd);
पूर्णांक mlx4_SQD2SQD_QP_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			    काष्ठा mlx4_vhcr *vhcr,
			    काष्ठा mlx4_cmd_mailbox *inbox,
			    काष्ठा mlx4_cmd_mailbox *outbox,
			    काष्ठा mlx4_cmd_info *cmd);
पूर्णांक mlx4_SQD2RTS_QP_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			    काष्ठा mlx4_vhcr *vhcr,
			    काष्ठा mlx4_cmd_mailbox *inbox,
			    काष्ठा mlx4_cmd_mailbox *outbox,
			    काष्ठा mlx4_cmd_info *cmd);
पूर्णांक mlx4_2RST_QP_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			 काष्ठा mlx4_vhcr *vhcr,
			 काष्ठा mlx4_cmd_mailbox *inbox,
			 काष्ठा mlx4_cmd_mailbox *outbox,
			 काष्ठा mlx4_cmd_info *cmd);
पूर्णांक mlx4_QUERY_QP_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			  काष्ठा mlx4_vhcr *vhcr,
			  काष्ठा mlx4_cmd_mailbox *inbox,
			  काष्ठा mlx4_cmd_mailbox *outbox,
			  काष्ठा mlx4_cmd_info *cmd);

पूर्णांक mlx4_GEN_EQE(काष्ठा mlx4_dev *dev, पूर्णांक slave, काष्ठा mlx4_eqe *eqe);

क्रमागत अणु
	MLX4_CMD_CLEANUP_STRUCT = 1UL << 0,
	MLX4_CMD_CLEANUP_POOL	= 1UL << 1,
	MLX4_CMD_CLEANUP_HCR	= 1UL << 2,
	MLX4_CMD_CLEANUP_VHCR	= 1UL << 3,
	MLX4_CMD_CLEANUP_ALL	= (MLX4_CMD_CLEANUP_VHCR << 1) - 1
पूर्ण;

पूर्णांक mlx4_cmd_init(काष्ठा mlx4_dev *dev);
व्योम mlx4_cmd_cleanup(काष्ठा mlx4_dev *dev, पूर्णांक cleanup_mask);
पूर्णांक mlx4_multi_func_init(काष्ठा mlx4_dev *dev);
पूर्णांक mlx4_ARM_COMM_CHANNEL(काष्ठा mlx4_dev *dev);
व्योम mlx4_multi_func_cleanup(काष्ठा mlx4_dev *dev);
व्योम mlx4_cmd_event(काष्ठा mlx4_dev *dev, u16 token, u8 status, u64 out_param);
पूर्णांक mlx4_cmd_use_events(काष्ठा mlx4_dev *dev);
व्योम mlx4_cmd_use_polling(काष्ठा mlx4_dev *dev);

पूर्णांक mlx4_comm_cmd(काष्ठा mlx4_dev *dev, u8 cmd, u16 param,
		  u16 op, अचिन्हित दीर्घ समयout);

व्योम mlx4_cq_tasklet_cb(काष्ठा tasklet_काष्ठा *t);
व्योम mlx4_cq_completion(काष्ठा mlx4_dev *dev, u32 cqn);
व्योम mlx4_cq_event(काष्ठा mlx4_dev *dev, u32 cqn, पूर्णांक event_type);

व्योम mlx4_qp_event(काष्ठा mlx4_dev *dev, u32 qpn, पूर्णांक event_type);

व्योम mlx4_srq_event(काष्ठा mlx4_dev *dev, u32 srqn, पूर्णांक event_type);

व्योम mlx4_enter_error_state(काष्ठा mlx4_dev_persistent *persist);
पूर्णांक mlx4_comm_पूर्णांकernal_err(u32 slave_पढ़ो);

पूर्णांक mlx4_crdump_collect(काष्ठा mlx4_dev *dev);

पूर्णांक mlx4_SENSE_PORT(काष्ठा mlx4_dev *dev, पूर्णांक port,
		    क्रमागत mlx4_port_type *type);
व्योम mlx4_करो_sense_ports(काष्ठा mlx4_dev *dev,
			 क्रमागत mlx4_port_type *stype,
			 क्रमागत mlx4_port_type *शेषs);
व्योम mlx4_start_sense(काष्ठा mlx4_dev *dev);
व्योम mlx4_stop_sense(काष्ठा mlx4_dev *dev);
व्योम mlx4_sense_init(काष्ठा mlx4_dev *dev);
पूर्णांक mlx4_check_port_params(काष्ठा mlx4_dev *dev,
			   क्रमागत mlx4_port_type *port_type);
पूर्णांक mlx4_change_port_types(काष्ठा mlx4_dev *dev,
			   क्रमागत mlx4_port_type *port_types);

व्योम mlx4_init_mac_table(काष्ठा mlx4_dev *dev, काष्ठा mlx4_mac_table *table);
व्योम mlx4_init_vlan_table(काष्ठा mlx4_dev *dev, काष्ठा mlx4_vlan_table *table);
व्योम mlx4_init_roce_gid_table(काष्ठा mlx4_dev *dev,
			      काष्ठा mlx4_roce_gid_table *table);
व्योम __mlx4_unरेजिस्टर_vlan(काष्ठा mlx4_dev *dev, u8 port, u16 vlan);
पूर्णांक __mlx4_रेजिस्टर_vlan(काष्ठा mlx4_dev *dev, u8 port, u16 vlan, पूर्णांक *index);
पूर्णांक mlx4_bond_vlan_table(काष्ठा mlx4_dev *dev);
पूर्णांक mlx4_unbond_vlan_table(काष्ठा mlx4_dev *dev);
पूर्णांक mlx4_bond_mac_table(काष्ठा mlx4_dev *dev);
पूर्णांक mlx4_unbond_mac_table(काष्ठा mlx4_dev *dev);

पूर्णांक mlx4_SET_PORT(काष्ठा mlx4_dev *dev, u8 port, पूर्णांक pkey_tbl_sz);
/* resource tracker functions*/
पूर्णांक mlx4_get_slave_from_resource_id(काष्ठा mlx4_dev *dev,
				    क्रमागत mlx4_resource resource_type,
				    u64 resource_id, पूर्णांक *slave);
व्योम mlx4_delete_all_resources_क्रम_slave(काष्ठा mlx4_dev *dev, पूर्णांक slave_id);
व्योम mlx4_reset_roce_gids(काष्ठा mlx4_dev *dev, पूर्णांक slave);
पूर्णांक mlx4_init_resource_tracker(काष्ठा mlx4_dev *dev);

व्योम mlx4_मुक्त_resource_tracker(काष्ठा mlx4_dev *dev,
				क्रमागत mlx4_res_tracker_मुक्त_type type);

पूर्णांक mlx4_QUERY_FW_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			  काष्ठा mlx4_vhcr *vhcr,
			  काष्ठा mlx4_cmd_mailbox *inbox,
			  काष्ठा mlx4_cmd_mailbox *outbox,
			  काष्ठा mlx4_cmd_info *cmd);
पूर्णांक mlx4_SET_PORT_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			  काष्ठा mlx4_vhcr *vhcr,
			  काष्ठा mlx4_cmd_mailbox *inbox,
			  काष्ठा mlx4_cmd_mailbox *outbox,
			  काष्ठा mlx4_cmd_info *cmd);
पूर्णांक mlx4_INIT_PORT_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			   काष्ठा mlx4_vhcr *vhcr,
			   काष्ठा mlx4_cmd_mailbox *inbox,
			   काष्ठा mlx4_cmd_mailbox *outbox,
			   काष्ठा mlx4_cmd_info *cmd);
पूर्णांक mlx4_CLOSE_PORT_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			    काष्ठा mlx4_vhcr *vhcr,
			    काष्ठा mlx4_cmd_mailbox *inbox,
			    काष्ठा mlx4_cmd_mailbox *outbox,
			    काष्ठा mlx4_cmd_info *cmd);
पूर्णांक mlx4_QUERY_DEV_CAP_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			       काष्ठा mlx4_vhcr *vhcr,
			       काष्ठा mlx4_cmd_mailbox *inbox,
			       काष्ठा mlx4_cmd_mailbox *outbox,
			       काष्ठा mlx4_cmd_info *cmd);
पूर्णांक mlx4_QUERY_PORT_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			    काष्ठा mlx4_vhcr *vhcr,
			    काष्ठा mlx4_cmd_mailbox *inbox,
			    काष्ठा mlx4_cmd_mailbox *outbox,
			    काष्ठा mlx4_cmd_info *cmd);
पूर्णांक mlx4_get_port_ib_caps(काष्ठा mlx4_dev *dev, u8 port, __be32 *caps);

पूर्णांक mlx4_get_slave_pkey_gid_tbl_len(काष्ठा mlx4_dev *dev, u8 port,
				    पूर्णांक *gid_tbl_len, पूर्णांक *pkey_tbl_len);

पूर्णांक mlx4_QP_ATTACH_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			   काष्ठा mlx4_vhcr *vhcr,
			   काष्ठा mlx4_cmd_mailbox *inbox,
			   काष्ठा mlx4_cmd_mailbox *outbox,
			   काष्ठा mlx4_cmd_info *cmd);

पूर्णांक mlx4_UPDATE_QP_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			   काष्ठा mlx4_vhcr *vhcr,
			   काष्ठा mlx4_cmd_mailbox *inbox,
			   काष्ठा mlx4_cmd_mailbox *outbox,
			   काष्ठा mlx4_cmd_info *cmd);

पूर्णांक mlx4_PROMISC_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			 काष्ठा mlx4_vhcr *vhcr,
			 काष्ठा mlx4_cmd_mailbox *inbox,
			 काष्ठा mlx4_cmd_mailbox *outbox,
			 काष्ठा mlx4_cmd_info *cmd);
पूर्णांक mlx4_qp_detach_common(काष्ठा mlx4_dev *dev, काष्ठा mlx4_qp *qp, u8 gid[16],
			  क्रमागत mlx4_protocol prot, क्रमागत mlx4_steer_type steer);
पूर्णांक mlx4_qp_attach_common(काष्ठा mlx4_dev *dev, काष्ठा mlx4_qp *qp, u8 gid[16],
			  पूर्णांक block_mcast_loopback, क्रमागत mlx4_protocol prot,
			  क्रमागत mlx4_steer_type steer);
पूर्णांक mlx4_trans_to_dmfs_attach(काष्ठा mlx4_dev *dev, काष्ठा mlx4_qp *qp,
			      u8 gid[16], u8 port,
			      पूर्णांक block_mcast_loopback,
			      क्रमागत mlx4_protocol prot, u64 *reg_id);
पूर्णांक mlx4_SET_MCAST_FLTR_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
				काष्ठा mlx4_vhcr *vhcr,
				काष्ठा mlx4_cmd_mailbox *inbox,
				काष्ठा mlx4_cmd_mailbox *outbox,
				काष्ठा mlx4_cmd_info *cmd);
पूर्णांक mlx4_SET_VLAN_FLTR_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			       काष्ठा mlx4_vhcr *vhcr,
			       काष्ठा mlx4_cmd_mailbox *inbox,
			       काष्ठा mlx4_cmd_mailbox *outbox,
			       काष्ठा mlx4_cmd_info *cmd);
पूर्णांक mlx4_common_set_vlan_fltr(काष्ठा mlx4_dev *dev, पूर्णांक function,
				     पूर्णांक port, व्योम *buf);
पूर्णांक mlx4_DUMP_ETH_STATS_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
				   काष्ठा mlx4_vhcr *vhcr,
				   काष्ठा mlx4_cmd_mailbox *inbox,
				   काष्ठा mlx4_cmd_mailbox *outbox,
				काष्ठा mlx4_cmd_info *cmd);
पूर्णांक mlx4_PKEY_TABLE_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			    काष्ठा mlx4_vhcr *vhcr,
			    काष्ठा mlx4_cmd_mailbox *inbox,
			    काष्ठा mlx4_cmd_mailbox *outbox,
			    काष्ठा mlx4_cmd_info *cmd);
पूर्णांक mlx4_QUERY_IF_STAT_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			       काष्ठा mlx4_vhcr *vhcr,
			       काष्ठा mlx4_cmd_mailbox *inbox,
			       काष्ठा mlx4_cmd_mailbox *outbox,
			       काष्ठा mlx4_cmd_info *cmd);
पूर्णांक mlx4_QP_FLOW_STEERING_ATTACH_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
					 काष्ठा mlx4_vhcr *vhcr,
					 काष्ठा mlx4_cmd_mailbox *inbox,
					 काष्ठा mlx4_cmd_mailbox *outbox,
					 काष्ठा mlx4_cmd_info *cmd);
पूर्णांक mlx4_QP_FLOW_STEERING_DETACH_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
					 काष्ठा mlx4_vhcr *vhcr,
					 काष्ठा mlx4_cmd_mailbox *inbox,
					 काष्ठा mlx4_cmd_mailbox *outbox,
					 काष्ठा mlx4_cmd_info *cmd);
पूर्णांक mlx4_ACCESS_REG_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			    काष्ठा mlx4_vhcr *vhcr,
			    काष्ठा mlx4_cmd_mailbox *inbox,
			    काष्ठा mlx4_cmd_mailbox *outbox,
			    काष्ठा mlx4_cmd_info *cmd);

पूर्णांक mlx4_get_mgm_entry_size(काष्ठा mlx4_dev *dev);
पूर्णांक mlx4_get_qp_per_mgm(काष्ठा mlx4_dev *dev);

अटल अंतरभूत व्योम set_param_l(u64 *arg, u32 val)
अणु
	*arg = (*arg & 0xffffffff00000000ULL) | (u64) val;
पूर्ण

अटल अंतरभूत व्योम set_param_h(u64 *arg, u32 val)
अणु
	*arg = (*arg & 0xffffffff) | ((u64) val << 32);
पूर्ण

अटल अंतरभूत u32 get_param_l(u64 *arg)
अणु
	वापस (u32) (*arg & 0xffffffff);
पूर्ण

अटल अंतरभूत u32 get_param_h(u64 *arg)
अणु
	वापस (u32)(*arg >> 32);
पूर्ण

अटल अंतरभूत spinlock_t *mlx4_tlock(काष्ठा mlx4_dev *dev)
अणु
	वापस &mlx4_priv(dev)->mfunc.master.res_tracker.lock;
पूर्ण

#घोषणा NOT_MASKED_PD_BITS 17

व्योम mlx4_vf_immed_vlan_work_handler(काष्ठा work_काष्ठा *_work);

व्योम mlx4_init_quotas(काष्ठा mlx4_dev *dev);

/* क्रम VFs, replace zero MACs with अक्रमomly-generated MACs at driver start */
व्योम mlx4_replace_zero_macs(काष्ठा mlx4_dev *dev);
पूर्णांक mlx4_get_slave_num_gids(काष्ठा mlx4_dev *dev, पूर्णांक slave, पूर्णांक port);
/* Returns the VF index of slave */
पूर्णांक mlx4_get_vf_indx(काष्ठा mlx4_dev *dev, पूर्णांक slave);
पूर्णांक mlx4_config_mad_demux(काष्ठा mlx4_dev *dev);
पूर्णांक mlx4_करो_bond(काष्ठा mlx4_dev *dev, bool enable);
पूर्णांक mlx4_bond_fs_rules(काष्ठा mlx4_dev *dev);
पूर्णांक mlx4_unbond_fs_rules(काष्ठा mlx4_dev *dev);

क्रमागत mlx4_zone_flags अणु
	MLX4_ZONE_ALLOW_ALLOC_FROM_LOWER_PRIO	= 1UL << 0,
	MLX4_ZONE_ALLOW_ALLOC_FROM_EQ_PRIO	= 1UL << 1,
	MLX4_ZONE_FALLBACK_TO_HIGHER_PRIO	= 1UL << 2,
	MLX4_ZONE_USE_RR			= 1UL << 3,
पूर्ण;

क्रमागत mlx4_zone_alloc_flags अणु
	/* No two objects could overlap between zones. UID
	 * could be left unused. If this flag is given and
	 * two overlapped zones are used, an object will be मुक्त'd
	 * from the smallest possible matching zone.
	 */
	MLX4_ZONE_ALLOC_FLAGS_NO_OVERLAP	= 1UL << 0,
पूर्ण;

काष्ठा mlx4_zone_allocator;

/* Create a new zone allocator */
काष्ठा mlx4_zone_allocator *mlx4_zone_allocator_create(क्रमागत mlx4_zone_alloc_flags flags);

/* Attach a mlx4_biपंचांगap <biपंचांगap> of priority <priority> to the zone allocator
 * <zone_alloc>. Allocating an object from this zone adds an offset <offset>.
 * Similarly, when searching क्रम an object to मुक्त, this offset it taken पूर्णांकo
 * account. The use_rr mlx4_ib parameter क्रम allocating objects from this <biपंचांगap>
 * is given through the MLX4_ZONE_USE_RR flag in <flags>.
 * When an allocation fails, <zone_alloc> tries to allocate from other zones
 * according to the policy set by <flags>. <puid> is the unique identअगरier
 * received to this zone.
 */
पूर्णांक mlx4_zone_add_one(काष्ठा mlx4_zone_allocator *zone_alloc,
		      काष्ठा mlx4_biपंचांगap *biपंचांगap,
		      u32 flags,
		      पूर्णांक priority,
		      पूर्णांक offset,
		      u32 *puid);

/* Remove biपंचांगap indicated by <uid> from <zone_alloc> */
पूर्णांक mlx4_zone_हटाओ_one(काष्ठा mlx4_zone_allocator *zone_alloc, u32 uid);

/* Delete the zone allocator <zone_alloc. This function करोesn't destroy
 * the attached biपंचांगaps.
 */
व्योम mlx4_zone_allocator_destroy(काष्ठा mlx4_zone_allocator *zone_alloc);

/* Allocate <count> objects with align <align> and skip_mask <skip_mask>
 * from the mlx4_biपंचांगap whose uid is <uid>. The biपंचांगap which we actually
 * allocated from is वापसed in <puid>. If the allocation fails, a negative
 * number is वापसed. Otherwise, the offset of the first object is वापसed.
 */
u32 mlx4_zone_alloc_entries(काष्ठा mlx4_zone_allocator *zones, u32 uid, पूर्णांक count,
			    पूर्णांक align, u32 skip_mask, u32 *puid);

/* Free <count> objects, start from <obj> of the uid <uid> from zone_allocator
 * <zones>.
 */
u32 mlx4_zone_मुक्त_entries(काष्ठा mlx4_zone_allocator *zones,
			   u32 uid, u32 obj, u32 count);

/* If <zones> was allocated with MLX4_ZONE_ALLOC_FLAGS_NO_OVERLAP, instead of
 * specअगरying the uid when मुक्तing an object, zone allocator could figure it by
 * itself. Other parameters are similar to mlx4_zone_मुक्त.
 */
u32 mlx4_zone_मुक्त_entries_unique(काष्ठा mlx4_zone_allocator *zones, u32 obj, u32 count);

/* Returns a poपूर्णांकer to mlx4_biपंचांगap that was attached to <zones> with <uid> */
काष्ठा mlx4_biपंचांगap *mlx4_zone_get_biपंचांगap(काष्ठा mlx4_zone_allocator *zones, u32 uid);

#पूर्ण_अगर /* MLX4_H */
