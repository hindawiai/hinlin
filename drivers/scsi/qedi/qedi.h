<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * QLogic iSCSI Offload Driver
 * Copyright (c) 2016 Cavium Inc.
 */

#अगर_अघोषित _QEDI_H_
#घोषणा _QEDI_H_

#घोषणा __PREVENT_QED_HSI__

#समावेश <scsi/scsi_transport_iscsi.h>
#समावेश <scsi/libiscsi.h>
#समावेश <scsi/scsi_host.h>
#समावेश <linux/uio_driver.h>

#समावेश "qedi_hsi.h"
#समावेश <linux/qed/qed_अगर.h>
#समावेश "qedi_dbg.h"
#समावेश <linux/qed/qed_iscsi_अगर.h>
#समावेश <linux/qed/qed_ll2_अगर.h>
#समावेश "qedi_version.h"
#समावेश "qedi_nvm_iscsi_cfg.h"

#घोषणा QEDI_MODULE_NAME		"qedi"

काष्ठा qedi_endpoपूर्णांक;

#अगर_अघोषित GET_FIELD2
#घोषणा GET_FIELD2(value, name) \
	(((value) & (name ## _MASK)) >> (name ## _OFFSET))
#पूर्ण_अगर

/*
 * PCI function probe defines
 */
#घोषणा QEDI_MODE_NORMAL	0
#घोषणा QEDI_MODE_RECOVERY	1
#घोषणा QEDI_MODE_SHUTDOWN	2

#घोषणा ISCSI_WQE_SET_PTU_INVALIDATE	1
#घोषणा QEDI_MAX_ISCSI_TASK		4096
#घोषणा QEDI_MAX_TASK_NUM		0x0FFF
#घोषणा QEDI_MAX_ISCSI_CONNS_PER_HBA	1024
#घोषणा QEDI_ISCSI_MAX_BDS_PER_CMD	255	/* Firmware max BDs is 255 */
#घोषणा MAX_OUTSTANDING_TASKS_PER_CON	1024

#घोषणा QEDI_MAX_BD_LEN		0xffff
#घोषणा QEDI_BD_SPLIT_SZ	0x1000
#घोषणा QEDI_PAGE_SIZE		4096
#घोषणा QEDI_FAST_SGE_COUNT	4
/* MAX Length क्रम cached SGL */
#घोषणा MAX_SGLEN_FOR_CACHESGL	((1U << 16) - 1)

#घोषणा MIN_NUM_CPUS_MSIX(x)	min_t(u32, x->dev_info.num_cqs, \
					num_online_cpus())

#घोषणा QEDI_LOCAL_PORT_MIN     60000
#घोषणा QEDI_LOCAL_PORT_MAX     61024
#घोषणा QEDI_LOCAL_PORT_RANGE   (QEDI_LOCAL_PORT_MAX - QEDI_LOCAL_PORT_MIN)
#घोषणा QEDI_LOCAL_PORT_INVALID	0xffff
#घोषणा TX_RX_RING		16
#घोषणा RX_RING			(TX_RX_RING - 1)
#घोषणा QEDI_PAGE_ALIGN(addr)	ALIGN(addr, QEDI_PAGE_SIZE)
#घोषणा QEDI_PAGE_MASK		(~((QEDI_PAGE_SIZE) - 1))

#घोषणा QEDI_HW_DMA_BOUNDARY	0xfff
#घोषणा QEDI_PATH_HANDLE	0xFE0000000UL

क्रमागत qedi_nvm_tgts अणु
	QEDI_NVM_TGT_PRI,
	QEDI_NVM_TGT_SEC,
पूर्ण;

काष्ठा qedi_nvm_iscsi_image अणु
	काष्ठा nvm_iscsi_cfg iscsi_cfg;
	u32 crc;
पूर्ण;

काष्ठा qedi_uio_ctrl अणु
	/* meta data */
	u32 uio_hsi_version;

	/* user ग_लिखोs */
	u32 host_tx_prod;
	u32 host_rx_cons;
	u32 host_rx_bd_cons;
	u32 host_tx_pkt_len;
	u32 host_rx_cons_cnt;

	/* driver ग_लिखोs */
	u32 hw_tx_cons;
	u32 hw_rx_prod;
	u32 hw_rx_bd_prod;
	u32 hw_rx_prod_cnt;

	/* other */
	u8 mac_addr[6];
	u8 reserve[2];
पूर्ण;

काष्ठा qedi_rx_bd अणु
	u32 rx_pkt_index;
	u32 rx_pkt_len;
	u16 vlan_id;
पूर्ण;

#घोषणा QEDI_RX_DESC_CNT	(QEDI_PAGE_SIZE / माप(काष्ठा qedi_rx_bd))
#घोषणा QEDI_MAX_RX_DESC_CNT	(QEDI_RX_DESC_CNT - 1)
#घोषणा QEDI_NUM_RX_BD		(QEDI_RX_DESC_CNT * 1)
#घोषणा QEDI_MAX_RX_BD		(QEDI_NUM_RX_BD - 1)

#घोषणा QEDI_NEXT_RX_IDX(x)	((((x) & (QEDI_MAX_RX_DESC_CNT)) ==	\
				  (QEDI_MAX_RX_DESC_CNT - 1)) ?		\
				 (x) + 2 : (x) + 1)

काष्ठा qedi_uio_dev अणु
	काष्ठा uio_info		qedi_uinfo;
	u32			uio_dev;
	काष्ठा list_head	list;

	u32			ll2_ring_size;
	व्योम			*ll2_ring;

	u32			ll2_buf_size;
	व्योम			*ll2_buf;

	व्योम			*rx_pkt;
	व्योम			*tx_pkt;

	काष्ठा qedi_ctx		*qedi;
	काष्ठा pci_dev		*pdev;
	व्योम			*uctrl;
पूर्ण;

/* List to मुख्यtain the skb poपूर्णांकers */
काष्ठा skb_work_list अणु
	काष्ठा list_head list;
	काष्ठा sk_buff *skb;
	u16 vlan_id;
पूर्ण;

/* Queue sizes in number of elements */
#घोषणा QEDI_SQ_SIZE		MAX_OUTSTANDING_TASKS_PER_CON
#घोषणा QEDI_CQ_SIZE		2048
#घोषणा QEDI_CMDQ_SIZE		QEDI_MAX_ISCSI_TASK
#घोषणा QEDI_PROTO_CQ_PROD_IDX	0

काष्ठा qedi_glbl_q_params अणु
	u64 hw_p_cq;	/* Completion queue PBL */
	u64 hw_p_rq;	/* Request queue PBL */
	u64 hw_p_cmdq;	/* Command queue PBL */
पूर्ण;

काष्ठा global_queue अणु
	जोड़ iscsi_cqe *cq;
	dma_addr_t cq_dma;
	u32 cq_mem_size;
	u32 cq_cons_idx; /* Completion queue consumer index */

	व्योम *cq_pbl;
	dma_addr_t cq_pbl_dma;
	u32 cq_pbl_size;

पूर्ण;

काष्ठा qedi_fastpath अणु
	काष्ठा qed_sb_info	*sb_info;
	u16			sb_id;
#घोषणा QEDI_NAME_SIZE		16
	अक्षर			name[QEDI_NAME_SIZE];
	काष्ठा qedi_ctx         *qedi;
पूर्ण;

/* Used to pass fastpath inक्रमmation needed to process CQEs */
काष्ठा qedi_io_work अणु
	काष्ठा list_head list;
	काष्ठा iscsi_cqe_solicited cqe;
	u16	que_idx;
पूर्ण;

/**
 * काष्ठा iscsi_cid_queue - Per adapter iscsi cid queue
 *
 * @cid_que_base:           queue base memory
 * @cid_que:                queue memory poपूर्णांकer
 * @cid_q_prod_idx:         produce index
 * @cid_q_cons_idx:         consumer index
 * @cid_q_max_idx:          max index. used to detect wrap around condition
 * @cid_मुक्त_cnt:           queue size
 * @conn_cid_tbl:           iscsi cid to conn काष्ठाure mapping table
 *
 * Per adapter iSCSI CID Queue
 */
काष्ठा iscsi_cid_queue अणु
	व्योम *cid_que_base;
	u32 *cid_que;
	u32 cid_q_prod_idx;
	u32 cid_q_cons_idx;
	u32 cid_q_max_idx;
	u32 cid_मुक्त_cnt;
	काष्ठा qedi_conn **conn_cid_tbl;
पूर्ण;

काष्ठा qedi_portid_tbl अणु
	spinlock_t      lock;	/* Port id lock */
	u16             start;
	u16             max;
	u16             next;
	अचिन्हित दीर्घ   *table;
पूर्ण;

काष्ठा qedi_itt_map अणु
	__le32	itt;
	काष्ठा qedi_cmd *p_cmd;
पूर्ण;

/* I/O tracing entry */
#घोषणा QEDI_IO_TRACE_SIZE             2048
काष्ठा qedi_io_log अणु
#घोषणा QEDI_IO_TRACE_REQ              0
#घोषणा QEDI_IO_TRACE_RSP              1
	u8 direction;
	u16 task_id;
	u32 cid;
	u32 port_id;	/* Remote port fabric ID */
	पूर्णांक lun;
	u8 op;		/* SCSI CDB */
	u8 lba[4];
	अचिन्हित पूर्णांक bufflen;	/* SCSI buffer length */
	अचिन्हित पूर्णांक sg_count;	/* Number of SG elements */
	u8 fast_sgs;		/* number of fast sgls */
	u8 slow_sgs;		/* number of slow sgls */
	u8 cached_sgs;		/* number of cached sgls */
	पूर्णांक result;		/* Result passed back to mid-layer */
	अचिन्हित दीर्घ jअगरfies;	/* Time stamp when I/O logged */
	पूर्णांक refcount;		/* Reference count क्रम task id */
	अचिन्हित पूर्णांक blk_req_cpu; /* CPU that the task is queued on by
				   * blk layer
				   */
	अचिन्हित पूर्णांक req_cpu;	/* CPU that the task is queued on */
	अचिन्हित पूर्णांक पूर्णांकr_cpu;	/* Interrupt CPU that the task is received on */
	अचिन्हित पूर्णांक blk_rsp_cpu;/* CPU that task is actually processed and
				  * वापसed to blk layer
				  */
	bool cached_sge;
	bool slow_sge;
	bool fast_sge;
पूर्ण;

/* Number of entries in BDQ */
#घोषणा QEDI_BDQ_NUM		256
#घोषणा QEDI_BDQ_BUF_SIZE	256

/* DMA coherent buffers क्रम BDQ */
काष्ठा qedi_bdq_buf अणु
	व्योम *buf_addr;
	dma_addr_t buf_dma;
पूर्ण;

/* Main port level काष्ठा */
काष्ठा qedi_ctx अणु
	काष्ठा qedi_dbg_ctx dbg_ctx;
	काष्ठा Scsi_Host *shost;
	काष्ठा pci_dev *pdev;
	काष्ठा qed_dev *cdev;
	काष्ठा qed_dev_iscsi_info dev_info;
	काष्ठा qed_पूर्णांक_info पूर्णांक_info;
	काष्ठा qedi_glbl_q_params *p_cpuq;
	काष्ठा global_queue **global_queues;
	/* uio declaration */
	काष्ठा qedi_uio_dev *udev;
	काष्ठा list_head ll2_skb_list;
	spinlock_t ll2_lock;	/* Light L2 lock */
	spinlock_t hba_lock;	/* per port lock */
	काष्ठा task_काष्ठा *ll2_recv_thपढ़ो;
	अचिन्हित दीर्घ qedi_err_flags;
#घोषणा QEDI_ERR_ATTN_CLR_EN	0
#घोषणा QEDI_ERR_IS_RECOVERABLE	2
#घोषणा QEDI_ERR_OVERRIDE_EN	31
	अचिन्हित दीर्घ flags;
#घोषणा UIO_DEV_OPENED		1
#घोषणा QEDI_IOTHREAD_WAKE	2
#घोषणा QEDI_IN_RECOVERY	5
#घोषणा QEDI_IN_OFFLINE		6
#घोषणा QEDI_IN_SHUTDOWN	7

	u8 mac[ETH_ALEN];
	u32 src_ip[4];
	u8 ip_type;

	/* Physical address of above array */
	dma_addr_t hw_p_cpuq;

	काष्ठा qedi_bdq_buf bdq[QEDI_BDQ_NUM];
	व्योम *bdq_pbl;
	dma_addr_t bdq_pbl_dma;
	माप_प्रकार bdq_pbl_mem_size;
	व्योम *bdq_pbl_list;
	dma_addr_t bdq_pbl_list_dma;
	u8 bdq_pbl_list_num_entries;
	काष्ठा qedi_nvm_iscsi_image *iscsi_image;
	dma_addr_t nvm_buf_dma;
	व्योम __iomem *bdq_primary_prod;
	व्योम __iomem *bdq_secondary_prod;
	u16 bdq_prod_idx;
	u16 rq_num_entries;

	u32 max_sqes;
	u8 num_queues;
	u32 max_active_conns;
	s32 msix_count;

	काष्ठा iscsi_cid_queue cid_que;
	काष्ठा qedi_endpoपूर्णांक **ep_tbl;
	काष्ठा qedi_portid_tbl lcl_port_tbl;

	/* Rx fast path पूर्णांकr context */
	काष्ठा qed_sb_info	*sb_array;
	काष्ठा qedi_fastpath	*fp_array;
	काष्ठा qed_iscsi_tid	tasks;

#घोषणा QEDI_LINK_DOWN		0
#घोषणा QEDI_LINK_UP		1
	atomic_t link_state;

#घोषणा QEDI_RESERVE_TASK_ID	0
#घोषणा MAX_ISCSI_TASK_ENTRIES	4096
#घोषणा QEDI_INVALID_TASK_ID	(MAX_ISCSI_TASK_ENTRIES + 1)
	अचिन्हित दीर्घ task_idx_map[MAX_ISCSI_TASK_ENTRIES / BITS_PER_LONG];
	काष्ठा qedi_itt_map *itt_map;
	u16 tid_reuse_count[QEDI_MAX_ISCSI_TASK];
	काष्ठा qed_pf_params pf_params;

	काष्ठा workqueue_काष्ठा *पंचांगf_thपढ़ो;
	काष्ठा workqueue_काष्ठा *offload_thपढ़ो;

	u16 ll2_mtu;

	काष्ठा workqueue_काष्ठा *dpc_wq;
	काष्ठा delayed_work recovery_work;
	काष्ठा delayed_work board_disable_work;

	spinlock_t task_idx_lock;	/* To protect gbl context */
	s32 last_tidx_alloc;
	s32 last_tidx_clear;

	काष्ठा qedi_io_log io_trace_buf[QEDI_IO_TRACE_SIZE];
	spinlock_t io_trace_lock;	/* prtect trace Log buf */
	u16 io_trace_idx;
	अचिन्हित पूर्णांक पूर्णांकr_cpu;
	u32 cached_sgls;
	bool use_cached_sge;
	u32 slow_sgls;
	bool use_slow_sge;
	u32 fast_sgls;
	bool use_fast_sge;

	atomic_t num_offloads;
#घोषणा SYSFS_FLAG_FW_SEL_BOOT 2
#घोषणा IPV6_LEN	41
#घोषणा IPV4_LEN	17
	काष्ठा iscsi_boot_kset *boot_kset;

	/* Used क्रम iscsi statistics */
	काष्ठा mutex stats_lock;
पूर्ण;

काष्ठा qedi_work अणु
	काष्ठा list_head list;
	काष्ठा qedi_ctx *qedi;
	जोड़ iscsi_cqe cqe;
	u16     que_idx;
	bool is_solicited;
पूर्ण;

काष्ठा qedi_percpu_s अणु
	काष्ठा task_काष्ठा *iothपढ़ो;
	काष्ठा list_head work_list;
	spinlock_t p_work_lock;		/* Per cpu worker lock */
पूर्ण;

अटल अंतरभूत व्योम *qedi_get_task_mem(काष्ठा qed_iscsi_tid *info, u32 tid)
अणु
	वापस (info->blocks[tid / info->num_tids_per_block] +
		(tid % info->num_tids_per_block) * info->size);
पूर्ण

#घोषणा QEDI_U64_HI(val) ((u32)(((u64)(val)) >> 32))
#घोषणा QEDI_U64_LO(val) ((u32)(((u64)(val)) & 0xffffffff))

#पूर्ण_अगर /* _QEDI_H_ */
