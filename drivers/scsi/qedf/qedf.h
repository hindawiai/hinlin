<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  QLogic FCoE Offload Driver
 *  Copyright (c) 2016-2018 Cavium Inc.
 */
#अगर_अघोषित _QEDFC_H_
#घोषणा _QEDFC_H_

#समावेश <scsi/libfcoe.h>
#समावेश <scsi/libfc.h>
#समावेश <scsi/fc/fc_fip.h>
#समावेश <scsi/fc/fc_fc2.h>
#समावेश <scsi/scsi_tcq.h>

/* qedf_hsi.h needs to beक्रमe included any qed includes */
#समावेश "qedf_hsi.h"

#समावेश <linux/qed/qed_अगर.h>
#समावेश <linux/qed/qed_fcoe_अगर.h>
#समावेश <linux/qed/qed_ll2_अगर.h>
#समावेश "qedf_version.h"
#समावेश "qedf_dbg.h"
#समावेश "drv_fcoe_fw_funcs.h"

/* Helpers to extract upper and lower 32-bits of poपूर्णांकer */
#घोषणा U64_HI(val) ((u32)(((u64)(val)) >> 32))
#घोषणा U64_LO(val) ((u32)(((u64)(val)) & 0xffffffff))

#घोषणा QEDF_DESCR "QLogic FCoE Offload Driver"
#घोषणा QEDF_MODULE_NAME "qedf"

#घोषणा QEDF_FLOGI_RETRY_CNT	3
#घोषणा QEDF_RPORT_RETRY_CNT	255
#घोषणा QEDF_MAX_SESSIONS	1024
#घोषणा QEDF_MAX_PAYLOAD	2048
#घोषणा QEDF_MAX_BDS_PER_CMD	256
#घोषणा QEDF_MAX_BD_LEN		0xffff
#घोषणा QEDF_BD_SPLIT_SZ	0x1000
#घोषणा QEDF_PAGE_SIZE		4096
#घोषणा QED_HW_DMA_BOUNDARY     0xfff
#घोषणा QEDF_MAX_SGLEN_FOR_CACHESGL		((1U << 16) - 1)
#घोषणा QEDF_MFS		(QEDF_MAX_PAYLOAD + \
	माप(काष्ठा fc_frame_header))
#घोषणा QEDF_MAX_NPIV		64
#घोषणा QEDF_TM_TIMEOUT		10
#घोषणा QEDF_ABORT_TIMEOUT	(10 * 1000)
#घोषणा QEDF_CLEANUP_TIMEOUT	1
#घोषणा QEDF_MAX_CDB_LEN	16
#घोषणा QEDF_LL2_BUF_SIZE	2500	/* Buffer size required क्रम LL2 Rx */

#घोषणा UPSTREAM_REMOVE		1
#घोषणा UPSTREAM_KEEP		1

काष्ठा qedf_mp_req अणु
	uपूर्णांक32_t req_len;
	व्योम *req_buf;
	dma_addr_t req_buf_dma;
	काष्ठा scsi_sge *mp_req_bd;
	dma_addr_t mp_req_bd_dma;
	काष्ठा fc_frame_header req_fc_hdr;

	uपूर्णांक32_t resp_len;
	व्योम *resp_buf;
	dma_addr_t resp_buf_dma;
	काष्ठा scsi_sge *mp_resp_bd;
	dma_addr_t mp_resp_bd_dma;
	काष्ठा fc_frame_header resp_fc_hdr;
पूर्ण;

काष्ठा qedf_els_cb_arg अणु
	काष्ठा qedf_ioreq *पातed_io_req;
	काष्ठा qedf_ioreq *io_req;
	u8 op; /* Used to keep track of ELS op */
	uपूर्णांक16_t l2_oxid;
	u32 offset; /* Used क्रम sequence cleanup */
	u8 r_ctl; /* Used क्रम sequence cleanup */
पूर्ण;

क्रमागत qedf_ioreq_event अणु
	QEDF_IOREQ_EV_NONE,
	QEDF_IOREQ_EV_ABORT_SUCCESS,
	QEDF_IOREQ_EV_ABORT_FAILED,
	QEDF_IOREQ_EV_SEND_RRQ,
	QEDF_IOREQ_EV_ELS_TMO,
	QEDF_IOREQ_EV_ELS_ERR_DETECT,
	QEDF_IOREQ_EV_ELS_FLUSH,
	QEDF_IOREQ_EV_CLEANUP_SUCCESS,
	QEDF_IOREQ_EV_CLEANUP_FAILED,
पूर्ण;

#घोषणा FC_GOOD		0
#घोषणा FCOE_FCP_RSP_FLAGS_FCP_RESID_OVER	(0x1<<2)
#घोषणा FCOE_FCP_RSP_FLAGS_FCP_RESID_UNDER	(0x1<<3)
#घोषणा CMD_SCSI_STATUS(Cmnd)			((Cmnd)->SCp.Status)
#घोषणा FCOE_FCP_RSP_FLAGS_FCP_RSP_LEN_VALID	(0x1<<0)
#घोषणा FCOE_FCP_RSP_FLAGS_FCP_SNS_LEN_VALID	(0x1<<1)
काष्ठा qedf_ioreq अणु
	काष्ठा list_head link;
	uपूर्णांक16_t xid;
	काष्ठा scsi_cmnd *sc_cmd;
#घोषणा QEDF_SCSI_CMD		1
#घोषणा QEDF_TASK_MGMT_CMD	2
#घोषणा QEDF_ABTS		3
#घोषणा QEDF_ELS		4
#घोषणा QEDF_CLEANUP		5
#घोषणा QEDF_SEQ_CLEANUP	6
	u8 cmd_type;
#घोषणा QEDF_CMD_OUTSTANDING		0x0
#घोषणा QEDF_CMD_IN_ABORT		0x1
#घोषणा QEDF_CMD_IN_CLEANUP		0x2
#घोषणा QEDF_CMD_SRR_SENT		0x3
#घोषणा QEDF_CMD_सूचीTY			0x4
#घोषणा QEDF_CMD_ERR_SCSI_DONE		0x5
	u8 io_req_flags;
	uपूर्णांक8_t पंचांग_flags;
	काष्ठा qedf_rport *fcport;
#घोषणा	QEDF_CMD_ST_INACTIVE		0
#घोषणा	QEDFC_CMD_ST_IO_ACTIVE		1
#घोषणा	QEDFC_CMD_ST_ABORT_ACTIVE	2
#घोषणा	QEDFC_CMD_ST_ABORT_ACTIVE_EH	3
#घोषणा	QEDFC_CMD_ST_CLEANUP_ACTIVE	4
#घोषणा	QEDFC_CMD_ST_CLEANUP_ACTIVE_EH	5
#घोषणा	QEDFC_CMD_ST_RRQ_ACTIVE		6
#घोषणा	QEDFC_CMD_ST_RRQ_WAIT		7
#घोषणा	QEDFC_CMD_ST_OXID_RETIRE_WAIT	8
#घोषणा	QEDFC_CMD_ST_TMF_ACTIVE		9
#घोषणा	QEDFC_CMD_ST_DRAIN_ACTIVE	10
#घोषणा	QEDFC_CMD_ST_CLEANED		11
#घोषणा	QEDFC_CMD_ST_ELS_ACTIVE		12
	atomic_t state;
	अचिन्हित दीर्घ flags;
	क्रमागत qedf_ioreq_event event;
	माप_प्रकार data_xfer_len;
	/* ID: 001: Alloc cmd (qedf_alloc_cmd) */
	/* ID: 002: Initiate ABTS (qedf_initiate_abts) */
	/* ID: 003: For RRQ (qedf_process_abts_compl) */
	काष्ठा kref refcount;
	काष्ठा qedf_cmd_mgr *cmd_mgr;
	काष्ठा io_bdt *bd_tbl;
	काष्ठा delayed_work समयout_work;
	काष्ठा completion पंचांग_करोne;
	काष्ठा completion abts_करोne;
	काष्ठा completion cleanup_करोne;
	काष्ठा e4_fcoe_task_context *task;
	काष्ठा fcoe_task_params *task_params;
	काष्ठा scsi_sgl_task_params *sgl_task_params;
	पूर्णांक idx;
	पूर्णांक lun;
/*
 * Need to allocate enough room क्रम both sense data and FCP response data
 * which has a max length of 8 bytes according to spec.
 */
#घोषणा QEDF_SCSI_SENSE_BUFFERSIZE	(SCSI_SENSE_BUFFERSIZE + 8)
	uपूर्णांक8_t *sense_buffer;
	dma_addr_t sense_buffer_dma;
	u32 fcp_resid;
	u32 fcp_rsp_len;
	u32 fcp_sns_len;
	u8 cdb_status;
	u8 fcp_status;
	u8 fcp_rsp_code;
	u8 scsi_comp_flags;
#घोषणा QEDF_MAX_REUSE		0xfff
	u16 reuse_count;
	काष्ठा qedf_mp_req mp_req;
	व्योम (*cb_func)(काष्ठा qedf_els_cb_arg *cb_arg);
	काष्ठा qedf_els_cb_arg *cb_arg;
	पूर्णांक fp_idx;
	अचिन्हित पूर्णांक cpu;
	अचिन्हित पूर्णांक पूर्णांक_cpu;
#घोषणा QEDF_IOREQ_UNKNOWN_SGE		1
#घोषणा QEDF_IOREQ_SLOW_SGE		2
#घोषणा QEDF_IOREQ_FAST_SGE		3
	u8 sge_type;
	काष्ठा delayed_work rrq_work;

	/* Used क्रम sequence level recovery; i.e. REC/SRR */
	uपूर्णांक32_t rx_buf_off;
	uपूर्णांक32_t tx_buf_off;
	uपूर्णांक32_t rx_id;
	uपूर्णांक32_t task_retry_identअगरier;

	/*
	 * Used to tell अगर we need to वापस a SCSI command
	 * during some क्रमm of error processing.
	 */
	bool वापस_scsi_cmd_on_abts;

	अचिन्हित पूर्णांक alloc;
पूर्ण;

बाह्य काष्ठा workqueue_काष्ठा *qedf_io_wq;

काष्ठा qedf_rport अणु
	spinlock_t rport_lock;
#घोषणा QEDF_RPORT_SESSION_READY 1
#घोषणा QEDF_RPORT_UPLOADING_CONNECTION	2
#घोषणा QEDF_RPORT_IN_RESET 3
#घोषणा QEDF_RPORT_IN_LUN_RESET 4
#घोषणा QEDF_RPORT_IN_TARGET_RESET 5
	अचिन्हित दीर्घ flags;
	पूर्णांक lun_reset_lun;
	अचिन्हित दीर्घ retry_delay_बारtamp;
	काष्ठा fc_rport *rport;
	काष्ठा fc_rport_priv *rdata;
	काष्ठा qedf_ctx *qedf;
	u32 handle; /* Handle from qed */
	u32 fw_cid; /* fw_cid from qed */
	व्योम __iomem *p_करोorbell;
	/* Send queue management */
	atomic_t मुक्त_sqes;
	atomic_t ios_to_queue;
	atomic_t num_active_ios;
	काष्ठा fcoe_wqe *sq;
	dma_addr_t sq_dma;
	u16 sq_prod_idx;
	u16 fw_sq_prod_idx;
	u16 sq_con_idx;
	u32 sq_mem_size;
	व्योम *sq_pbl;
	dma_addr_t sq_pbl_dma;
	u32 sq_pbl_size;
	u32 sid;
#घोषणा	QEDF_RPORT_TYPE_DISK		0
#घोषणा	QEDF_RPORT_TYPE_TAPE		1
	uपूर्णांक dev_type; /* Disk or tape */
	काष्ठा list_head peers;
पूर्ण;

/* Used to contain LL2 skb's in ll2_skb_list */
काष्ठा qedf_skb_work अणु
	काष्ठा work_काष्ठा work;
	काष्ठा sk_buff *skb;
	काष्ठा qedf_ctx *qedf;
पूर्ण;

काष्ठा qedf_fastpath अणु
#घोषणा	QEDF_SB_ID_शून्य		0xffff
	u16		sb_id;
	काष्ठा qed_sb_info	*sb_info;
	काष्ठा qedf_ctx *qedf;
	/* Keep track of number of completions on this fastpath */
	अचिन्हित दीर्घ completions;
	uपूर्णांक32_t cq_num_entries;
पूर्ण;

/* Used to pass fastpath inक्रमmation needed to process CQEs */
काष्ठा qedf_io_work अणु
	काष्ठा work_काष्ठा work;
	काष्ठा fcoe_cqe cqe;
	काष्ठा qedf_ctx *qedf;
	काष्ठा fc_frame *fp;
पूर्ण;

काष्ठा qedf_glbl_q_params अणु
	u64	hw_p_cq;	/* Completion queue PBL */
	u64	hw_p_rq;	/* Request queue PBL */
	u64	hw_p_cmdq;	/* Command queue PBL */
पूर्ण;

काष्ठा global_queue अणु
	काष्ठा fcoe_cqe *cq;
	dma_addr_t cq_dma;
	u32 cq_mem_size;
	u32 cq_cons_idx; /* Completion queue consumer index */
	u32 cq_prod_idx;

	व्योम *cq_pbl;
	dma_addr_t cq_pbl_dma;
	u32 cq_pbl_size;
पूर्ण;

/* I/O tracing entry */
#घोषणा QEDF_IO_TRACE_SIZE		2048
काष्ठा qedf_io_log अणु
#घोषणा QEDF_IO_TRACE_REQ		0
#घोषणा QEDF_IO_TRACE_RSP		1
	uपूर्णांक8_t direction;
	uपूर्णांक16_t task_id;
	uपूर्णांक32_t port_id; /* Remote port fabric ID */
	पूर्णांक lun;
	अचिन्हित अक्षर op; /* SCSI CDB */
	uपूर्णांक8_t lba[4];
	अचिन्हित पूर्णांक bufflen; /* SCSI buffer length */
	अचिन्हित पूर्णांक sg_count; /* Number of SG elements */
	पूर्णांक result; /* Result passed back to mid-layer */
	अचिन्हित दीर्घ jअगरfies; /* Time stamp when I/O logged */
	पूर्णांक refcount; /* Reference count क्रम task id */
	अचिन्हित पूर्णांक req_cpu; /* CPU that the task is queued on */
	अचिन्हित पूर्णांक पूर्णांक_cpu; /* Interrupt CPU that the task is received on */
	अचिन्हित पूर्णांक rsp_cpu; /* CPU that task is वापसed on */
	u8 sge_type; /* Did we take the slow, single or fast SGE path */
पूर्ण;

/* Number of entries in BDQ */
#घोषणा QEDF_BDQ_SIZE			256
#घोषणा QEDF_BDQ_BUF_SIZE		2072

/* DMA coherent buffers क्रम BDQ */
काष्ठा qedf_bdq_buf अणु
	व्योम *buf_addr;
	dma_addr_t buf_dma;
पूर्ण;

/* Main adapter काष्ठा */
काष्ठा qedf_ctx अणु
	काष्ठा qedf_dbg_ctx dbg_ctx;
	काष्ठा fcoe_ctlr ctlr;
	काष्ठा fc_lport *lport;
	u8 data_src_addr[ETH_ALEN];
#घोषणा QEDF_LINK_DOWN		0
#घोषणा QEDF_LINK_UP		1
	atomic_t link_state;
#घोषणा QEDF_DCBX_PENDING	0
#घोषणा QEDF_DCBX_DONE		1
	atomic_t dcbx;
#घोषणा QEDF_शून्य_VLAN_ID	-1
#घोषणा QEDF_FALLBACK_VLAN	1002
#घोषणा QEDF_DEFAULT_PRIO	3
	पूर्णांक vlan_id;
	u8 prio;
	काष्ठा qed_dev *cdev;
	काष्ठा qed_dev_fcoe_info dev_info;
	काष्ठा qed_पूर्णांक_info पूर्णांक_info;
	uपूर्णांक16_t last_command;
	spinlock_t hba_lock;
	काष्ठा pci_dev *pdev;
	u64 wwnn;
	u64 wwpn;
	u8 __aligned(16) mac[ETH_ALEN];
	काष्ठा list_head fcports;
	atomic_t num_offloads;
	अचिन्हित पूर्णांक curr_conn_id;
	काष्ठा workqueue_काष्ठा *ll2_recv_wq;
	काष्ठा workqueue_काष्ठा *link_update_wq;
	काष्ठा devlink *devlink;
	काष्ठा delayed_work link_update;
	काष्ठा delayed_work link_recovery;
	काष्ठा completion flogi_compl;
	काष्ठा completion fipvlan_compl;

	/*
	 * Used to tell अगर we're in the winकरोw where we are रुकोing क्रम
	 * the link to come back up beक्रमe inक्रमmting fcoe that the link is
	 * करोne.
	 */
	atomic_t link_करोwn_पंचांगo_valid;
#घोषणा QEDF_TIMER_INTERVAL		(1 * HZ)
	काष्ठा समयr_list समयr; /* One second book keeping समयr */
#घोषणा QEDF_DRAIN_ACTIVE		1
#घोषणा QEDF_LL2_STARTED		2
#घोषणा QEDF_UNLOADING			3
#घोषणा QEDF_GRCDUMP_CAPTURE		4
#घोषणा QEDF_IN_RECOVERY		5
#घोषणा QEDF_DBG_STOP_IO		6
#घोषणा QEDF_PROBING			8
	अचिन्हित दीर्घ flags; /* Miscellaneous state flags */
	पूर्णांक fipvlan_retries;
	u8 num_queues;
	काष्ठा global_queue **global_queues;
	/* Poपूर्णांकer to array of queue काष्ठाures */
	काष्ठा qedf_glbl_q_params *p_cpuq;
	/* Physical address of array of queue काष्ठाures */
	dma_addr_t hw_p_cpuq;

	काष्ठा qedf_bdq_buf bdq[QEDF_BDQ_SIZE];
	व्योम *bdq_pbl;
	dma_addr_t bdq_pbl_dma;
	माप_प्रकार bdq_pbl_mem_size;
	व्योम *bdq_pbl_list;
	dma_addr_t bdq_pbl_list_dma;
	u8 bdq_pbl_list_num_entries;
	व्योम __iomem *bdq_primary_prod;
	व्योम __iomem *bdq_secondary_prod;
	uपूर्णांक16_t bdq_prod_idx;

	/* Structure क्रम holding all the fastpath क्रम this qedf_ctx */
	काष्ठा qedf_fastpath *fp_array;
	काष्ठा qed_fcoe_tid tasks;
	काष्ठा qedf_cmd_mgr *cmd_mgr;
	/* Holds the PF parameters we pass to qed to start he FCoE function */
	काष्ठा qed_pf_params pf_params;
	/* Used to समय middle path ELS and TM commands */
	काष्ठा workqueue_काष्ठा *समयr_work_queue;

#घोषणा QEDF_IO_WORK_MIN		64
	mempool_t *io_mempool;
	काष्ठा workqueue_काष्ठा *dpc_wq;
	काष्ठा delayed_work recovery_work;
	काष्ठा delayed_work board_disable_work;
	काष्ठा delayed_work grcdump_work;
	काष्ठा delayed_work stag_work;

	u32 slow_sge_ios;
	u32 fast_sge_ios;

	uपूर्णांक8_t	*grcdump;
	uपूर्णांक32_t grcdump_size;

	काष्ठा qedf_io_log io_trace_buf[QEDF_IO_TRACE_SIZE];
	spinlock_t io_trace_lock;
	uपूर्णांक16_t io_trace_idx;

	bool stop_io_on_error;

	u32 flogi_cnt;
	u32 flogi_failed;
	u32 flogi_pending;

	/* Used क्रम fc statistics */
	काष्ठा mutex stats_mutex;
	u64 input_requests;
	u64 output_requests;
	u64 control_requests;
	u64 packet_पातs;
	u64 alloc_failures;
	u8 lun_resets;
	u8 target_resets;
	u8 task_set_fulls;
	u8 busy;
	/* Used क्रम flush routine */
	काष्ठा mutex flush_mutex;
पूर्ण;

काष्ठा io_bdt अणु
	काष्ठा qedf_ioreq *io_req;
	काष्ठा scsi_sge *bd_tbl;
	dma_addr_t bd_tbl_dma;
	u16 bd_valid;
पूर्ण;

काष्ठा qedf_cmd_mgr अणु
	काष्ठा qedf_ctx *qedf;
	u16 idx;
	काष्ठा io_bdt **io_bdt_pool;
#घोषणा FCOE_PARAMS_NUM_TASKS		2048
	काष्ठा qedf_ioreq cmds[FCOE_PARAMS_NUM_TASKS];
	spinlock_t lock;
	atomic_t मुक्त_list_cnt;
पूर्ण;

/* Stolen from qed_cxt_api.h and adapted क्रम qed_fcoe_info
 * Usage:
 *
 * व्योम *ptr;
 * ptr = qedf_get_task_mem(&qedf->tasks, 128);
 */
अटल अंतरभूत व्योम *qedf_get_task_mem(काष्ठा qed_fcoe_tid *info, u32 tid)
अणु
	वापस (व्योम *)(info->blocks[tid / info->num_tids_per_block] +
			(tid % info->num_tids_per_block) * info->size);
पूर्ण

अटल अंतरभूत व्योम qedf_stop_all_io(काष्ठा qedf_ctx *qedf)
अणु
	set_bit(QEDF_DBG_STOP_IO, &qedf->flags);
पूर्ण

/*
 * Externs
 */

/*
 * (QEDF_LOG_NPIV | QEDF_LOG_SESS | QEDF_LOG_LPORT | QEDF_LOG_ELS | QEDF_LOG_MQ
 * | QEDF_LOG_IO | QEDF_LOG_UNSOL | QEDF_LOG_SCSI_TM | QEDF_LOG_MP_REQ |
 * QEDF_LOG_EVT | QEDF_LOG_CONN | QEDF_LOG_DISC | QEDF_LOG_INFO)
 */
#घोषणा QEDF_DEFAULT_LOG_MASK		0x3CFB6
बाह्य स्थिर काष्ठा qed_fcoe_ops *qed_ops;
बाह्य uपूर्णांक qedf_dump_frames;
बाह्य uपूर्णांक qedf_io_tracing;
बाह्य uपूर्णांक qedf_stop_io_on_error;
बाह्य uपूर्णांक qedf_link_करोwn_पंचांगo;
#घोषणा QEDF_RETRY_DELAY_MAX		600 /* 60 seconds */
बाह्य bool qedf_retry_delay;
बाह्य uपूर्णांक qedf_debug;

बाह्य काष्ठा qedf_cmd_mgr *qedf_cmd_mgr_alloc(काष्ठा qedf_ctx *qedf);
बाह्य व्योम qedf_cmd_mgr_मुक्त(काष्ठा qedf_cmd_mgr *cmgr);
बाह्य पूर्णांक qedf_queuecommand(काष्ठा Scsi_Host *host,
	काष्ठा scsi_cmnd *sc_cmd);
बाह्य व्योम qedf_fip_send(काष्ठा fcoe_ctlr *fip, काष्ठा sk_buff *skb);
बाह्य u8 *qedf_get_src_mac(काष्ठा fc_lport *lport);
बाह्य व्योम qedf_fip_recv(काष्ठा qedf_ctx *qedf, काष्ठा sk_buff *skb);
बाह्य व्योम qedf_fcoe_send_vlan_req(काष्ठा qedf_ctx *qedf);
बाह्य व्योम qedf_scsi_completion(काष्ठा qedf_ctx *qedf, काष्ठा fcoe_cqe *cqe,
	काष्ठा qedf_ioreq *io_req);
बाह्य व्योम qedf_process_warning_compl(काष्ठा qedf_ctx *qedf,
	काष्ठा fcoe_cqe *cqe, काष्ठा qedf_ioreq *io_req);
बाह्य व्योम qedf_process_error_detect(काष्ठा qedf_ctx *qedf,
	काष्ठा fcoe_cqe *cqe, काष्ठा qedf_ioreq *io_req);
बाह्य व्योम qedf_flush_active_ios(काष्ठा qedf_rport *fcport, पूर्णांक lun);
बाह्य व्योम qedf_release_cmd(काष्ठा kref *ref);
बाह्य पूर्णांक qedf_initiate_abts(काष्ठा qedf_ioreq *io_req,
	bool वापस_scsi_cmd_on_abts);
बाह्य व्योम qedf_process_abts_compl(काष्ठा qedf_ctx *qedf, काष्ठा fcoe_cqe *cqe,
	काष्ठा qedf_ioreq *io_req);
बाह्य काष्ठा qedf_ioreq *qedf_alloc_cmd(काष्ठा qedf_rport *fcport,
	u8 cmd_type);

बाह्य काष्ठा device_attribute *qedf_host_attrs[];
बाह्य व्योम qedf_cmd_समयr_set(काष्ठा qedf_ctx *qedf, काष्ठा qedf_ioreq *io_req,
	अचिन्हित पूर्णांक समयr_msec);
बाह्य पूर्णांक qedf_init_mp_req(काष्ठा qedf_ioreq *io_req);
बाह्य व्योम qedf_init_mp_task(काष्ठा qedf_ioreq *io_req,
	काष्ठा e4_fcoe_task_context *task_ctx, काष्ठा fcoe_wqe *sqe);
बाह्य u16 qedf_get_sqe_idx(काष्ठा qedf_rport *fcport);
बाह्य व्योम qedf_ring_करोorbell(काष्ठा qedf_rport *fcport);
बाह्य व्योम qedf_process_els_compl(काष्ठा qedf_ctx *qedf, काष्ठा fcoe_cqe *cqe,
	काष्ठा qedf_ioreq *els_req);
बाह्य पूर्णांक qedf_send_rrq(काष्ठा qedf_ioreq *पातed_io_req);
बाह्य पूर्णांक qedf_send_adisc(काष्ठा qedf_rport *fcport, काष्ठा fc_frame *fp);
बाह्य पूर्णांक qedf_initiate_cleanup(काष्ठा qedf_ioreq *io_req,
	bool वापस_scsi_cmd_on_abts);
बाह्य व्योम qedf_process_cleanup_compl(काष्ठा qedf_ctx *qedf,
	काष्ठा fcoe_cqe *cqe, काष्ठा qedf_ioreq *io_req);
बाह्य पूर्णांक qedf_initiate_पंचांगf(काष्ठा scsi_cmnd *sc_cmd, u8 पंचांग_flags);
बाह्य व्योम qedf_process_पंचांगf_compl(काष्ठा qedf_ctx *qedf, काष्ठा fcoe_cqe *cqe,
	काष्ठा qedf_ioreq *io_req);
बाह्य व्योम qedf_process_cqe(काष्ठा qedf_ctx *qedf, काष्ठा fcoe_cqe *cqe);
बाह्य व्योम qedf_scsi_करोne(काष्ठा qedf_ctx *qedf, काष्ठा qedf_ioreq *io_req,
	पूर्णांक result);
बाह्य व्योम qedf_set_vlan_id(काष्ठा qedf_ctx *qedf, पूर्णांक vlan_id);
बाह्य व्योम qedf_create_sysfs_ctx_attr(काष्ठा qedf_ctx *qedf);
बाह्य व्योम qedf_हटाओ_sysfs_ctx_attr(काष्ठा qedf_ctx *qedf);
बाह्य व्योम qedf_capture_grc_dump(काष्ठा qedf_ctx *qedf);
bool qedf_रुको_क्रम_upload(काष्ठा qedf_ctx *qedf);
बाह्य व्योम qedf_process_unsol_compl(काष्ठा qedf_ctx *qedf, uपूर्णांक16_t que_idx,
	काष्ठा fcoe_cqe *cqe);
बाह्य व्योम qedf_restart_rport(काष्ठा qedf_rport *fcport);
बाह्य पूर्णांक qedf_send_rec(काष्ठा qedf_ioreq *orig_io_req);
बाह्य पूर्णांक qedf_post_io_req(काष्ठा qedf_rport *fcport,
	काष्ठा qedf_ioreq *io_req);
बाह्य व्योम qedf_process_seq_cleanup_compl(काष्ठा qedf_ctx *qedf,
	काष्ठा fcoe_cqe *cqe, काष्ठा qedf_ioreq *io_req);
बाह्य पूर्णांक qedf_send_flogi(काष्ठा qedf_ctx *qedf);
बाह्य व्योम qedf_get_protocol_tlv_data(व्योम *dev, व्योम *data);
बाह्य व्योम qedf_fp_io_handler(काष्ठा work_काष्ठा *work);
बाह्य व्योम qedf_get_generic_tlv_data(व्योम *dev, काष्ठा qed_generic_tlvs *data);
बाह्य व्योम qedf_wq_grcdump(काष्ठा work_काष्ठा *work);
व्योम qedf_stag_change_work(काष्ठा work_काष्ठा *work);
व्योम qedf_ctx_soft_reset(काष्ठा fc_lport *lport);
बाह्य व्योम qedf_board_disable_work(काष्ठा work_काष्ठा *work);
बाह्य व्योम qedf_schedule_hw_err_handler(व्योम *dev,
		क्रमागत qed_hw_err_type err_type);

#घोषणा FCOE_WORD_TO_BYTE  4
#घोषणा QEDF_MAX_TASK_NUM	0xFFFF
#घोषणा QL45xxx			0x165C
#घोषणा QL41xxx			0x8080
#घोषणा MAX_CT_PAYLOAD		2048
#घोषणा DISCOVERED_PORTS	4
#घोषणा NUMBER_OF_PORTS		1

काष्ठा fip_vlan अणु
	काष्ठा ethhdr eth;
	काष्ठा fip_header fip;
	काष्ठा अणु
		काष्ठा fip_mac_desc mac;
		काष्ठा fip_wwn_desc wwnn;
	पूर्ण desc;
पूर्ण;

/* SQ/CQ Sizes */
#घोषणा GBL_RSVD_TASKS			16
#घोषणा NUM_TASKS_PER_CONNECTION	1024
#घोषणा NUM_RW_TASKS_PER_CONNECTION	512
#घोषणा FCOE_PARAMS_CQ_NUM_ENTRIES	FCOE_PARAMS_NUM_TASKS

#घोषणा FCOE_PARAMS_CMDQ_NUM_ENTRIES	FCOE_PARAMS_NUM_TASKS
#घोषणा SQ_NUM_ENTRIES			NUM_TASKS_PER_CONNECTION

#घोषणा QEDF_FCOE_PARAMS_GL_RQ_PI              0
#घोषणा QEDF_FCOE_PARAMS_GL_CMD_PI             1

#घोषणा QEDF_READ                     (1 << 1)
#घोषणा QEDF_WRITE                    (1 << 0)
#घोषणा MAX_FIBRE_LUNS			0xffffffff

#घोषणा MIN_NUM_CPUS_MSIX(x)	min_t(u32, x->dev_info.num_cqs, \
					num_online_cpus())

/*
 * PCI function probe defines
 */
/* Probe/हटाओ called during normal PCI probe */
#घोषणा	QEDF_MODE_NORMAL		0
/* Probe/हटाओ called from qed error recovery */
#घोषणा QEDF_MODE_RECOVERY		1

#घोषणा SUPPORTED_25000baseKR_Full    (1<<27)
#घोषणा SUPPORTED_50000baseKR2_Full   (1<<28)
#घोषणा SUPPORTED_100000baseKR4_Full  (1<<29)
#घोषणा SUPPORTED_100000baseCR4_Full  (1<<30)

#पूर्ण_अगर
