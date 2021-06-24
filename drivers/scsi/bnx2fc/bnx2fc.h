<शैली गुरु>
/* bnx2fc.h: QLogic Linux FCoE offload driver.
 *
 * Copyright (c) 2008-2013 Broadcom Corporation
 * Copyright (c) 2014-2016 QLogic Corporation
 * Copyright (c) 2016-2017 Cavium Inc.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 *
 * Written by: Bhanu Prakash Gollapudi (bprakash@broadcom.com)
 */

#अगर_अघोषित _BNX2FC_H_
#घोषणा _BNX2FC_H_
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kernel.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/crc32.h>
#समावेश <linux/cpu.h>
#समावेश <linux/types.h>
#समावेश <linux/list.h>
#समावेश <linux/delay.h>
#समावेश <linux/समयr.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/mutex.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/bitops.h>
#समावेश <linux/log2.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/पन.स>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_eh.h>
#समावेश <scsi/scsi_tcq.h>
#समावेश <scsi/libfc.h>
#समावेश <scsi/libfcoe.h>
#समावेश <scsi/scsi_transport.h>
#समावेश <scsi/scsi_transport_fc.h>
#समावेश <scsi/fc/fc_fip.h>
#समावेश <scsi/fc/fc_fc2.h>
#समावेश <scsi/fc_frame.h>
#समावेश <scsi/fc/fc_fcoe.h>
#समावेश <scsi/fc/fc_fcp.h>

#समावेश "57xx_hsi_bnx2fc.h"
#समावेश "../../net/ethernet/broadcom/cnic_if.h"
#समावेश  "../../net/ethernet/broadcom/bnx2x/bnx2x_mfw_req.h"
#समावेश "bnx2fc_constants.h"

#घोषणा BNX2FC_NAME		"bnx2fc"
#घोषणा BNX2FC_VERSION		"2.12.13"

#घोषणा PFX			"bnx2fc: "

#घोषणा BCM_CHIP_LEN		16

#घोषणा BNX2X_DOORBELL_PCI_BAR		2

#घोषणा BNX2FC_MAX_BD_LEN		0xffff
#घोषणा BNX2FC_BD_SPLIT_SZ		0xffff
#घोषणा BNX2FC_MAX_BDS_PER_CMD		255
#घोषणा BNX2FC_FW_MAX_BDS_PER_CMD	255

#घोषणा BNX2FC_SQ_WQES_MAX	256

#घोषणा BNX2FC_SCSI_MAX_SQES	((3 * BNX2FC_SQ_WQES_MAX) / 8)
#घोषणा BNX2FC_TM_MAX_SQES	((BNX2FC_SQ_WQES_MAX) / 2)
#घोषणा BNX2FC_ELS_MAX_SQES	(BNX2FC_TM_MAX_SQES - 1)

#घोषणा BNX2FC_RQ_WQES_MAX	16
#घोषणा BNX2FC_CQ_WQES_MAX	(BNX2FC_SQ_WQES_MAX + BNX2FC_RQ_WQES_MAX)

#घोषणा BNX2FC_NUM_MAX_SESS	1024
#घोषणा BNX2FC_NUM_MAX_SESS_LOG	(ilog2(BNX2FC_NUM_MAX_SESS))

#घोषणा BNX2FC_MAX_NPIV		256

#घोषणा BNX2FC_MIN_PAYLOAD		256
#घोषणा BNX2FC_MAX_PAYLOAD		2048
#घोषणा BNX2FC_MFS			\
			(BNX2FC_MAX_PAYLOAD + माप(काष्ठा fc_frame_header))
#घोषणा BNX2FC_MINI_JUMBO_MTU		2500


#घोषणा BNX2FC_RQ_BUF_SZ		256
#घोषणा BNX2FC_RQ_BUF_LOG_SZ		(ilog2(BNX2FC_RQ_BUF_SZ))

#घोषणा BNX2FC_SQ_WQE_SIZE		(माप(काष्ठा fcoe_sqe))
#घोषणा BNX2FC_CQ_WQE_SIZE		(माप(काष्ठा fcoe_cqe))
#घोषणा BNX2FC_RQ_WQE_SIZE		(BNX2FC_RQ_BUF_SZ)
#घोषणा BNX2FC_XFERQ_WQE_SIZE		(माप(काष्ठा fcoe_xfrqe))
#घोषणा BNX2FC_CONFQ_WQE_SIZE		(माप(काष्ठा fcoe_confqe))
#घोषणा BNX2X_DB_SHIFT			3

#घोषणा BNX2FC_TASK_SIZE		128
#घोषणा	BNX2FC_TASKS_PER_PAGE		(PAGE_SIZE/BNX2FC_TASK_SIZE)

#घोषणा BNX2FC_MAX_ROWS_IN_HASH_TBL	8
#घोषणा BNX2FC_HASH_TBL_CHUNK_SIZE	(16 * 1024)

#घोषणा BNX2FC_MAX_SEQS			255
#घोषणा BNX2FC_MAX_RETRY_CNT		3
#घोषणा BNX2FC_MAX_RPORT_RETRY_CNT	255

#घोषणा BNX2FC_READ			(1 << 1)
#घोषणा BNX2FC_WRITE			(1 << 0)

#घोषणा BNX2FC_MIN_XID			0
#घोषणा FCOE_MAX_NUM_XIDS		0x2000
#घोषणा FCOE_MAX_XID_OFFSET		(FCOE_MAX_NUM_XIDS - 1)
#घोषणा FCOE_XIDS_PER_CPU_OFFSET	((512 * nr_cpu_ids) - 1)
#घोषणा BNX2FC_MAX_LUN			0xFFFF
#घोषणा BNX2FC_MAX_FCP_TGT		256
#घोषणा BNX2FC_MAX_CMD_LEN		16

#घोषणा BNX2FC_TM_TIMEOUT		60	/* secs */
#घोषणा BNX2FC_IO_TIMEOUT		20000UL	/* msecs */

#घोषणा BNX2FC_WAIT_CNT			1200
#घोषणा BNX2FC_FW_TIMEOUT		(3 * HZ)
#घोषणा PORT_MAX			2

#घोषणा CMD_SCSI_STATUS(Cmnd)		((Cmnd)->SCp.Status)

/* FC FCP Status */
#घोषणा	FC_GOOD				0

#घोषणा BNX2FC_RNID_HBA			0x7

#घोषणा SRR_RETRY_COUNT			5
#घोषणा REC_RETRY_COUNT			1
#घोषणा BNX2FC_NUM_ERR_BITS		63

#घोषणा BNX2FC_RELOGIN_WAIT_TIME	200
#घोषणा BNX2FC_RELOGIN_WAIT_CNT		10

#घोषणा BNX2FC_STATS(hba, stat, cnt)					\
	करो अणु								\
		u32 val;						\
									\
		val = fw_stats->stat.cnt;				\
		अगर (hba->prev_stats.stat.cnt <= val)			\
			val -= hba->prev_stats.stat.cnt;		\
		अन्यथा							\
			val += (0xfffffff - hba->prev_stats.stat.cnt);	\
		hba->bfw_stats.cnt += val;				\
	पूर्ण जबतक (0)

/* bnx2fc driver uses only one instance of fcoe_percpu_s */
बाह्य काष्ठा fcoe_percpu_s bnx2fc_global;

बाह्य काष्ठा workqueue_काष्ठा *bnx2fc_wq;

काष्ठा bnx2fc_percpu_s अणु
	काष्ठा task_काष्ठा *iothपढ़ो;
	काष्ठा list_head work_list;
	spinlock_t fp_work_lock;
पूर्ण;

काष्ठा bnx2fc_fw_stats अणु
	u64	fc_crc_cnt;
	u64	fcoe_tx_pkt_cnt;
	u64	fcoe_rx_pkt_cnt;
	u64	fcoe_tx_byte_cnt;
	u64	fcoe_rx_byte_cnt;
पूर्ण;

काष्ठा bnx2fc_hba अणु
	काष्ठा list_head list;
	काष्ठा cnic_dev *cnic;
	काष्ठा pci_dev *pcidev;
	काष्ठा net_device *phys_dev;
	अचिन्हित दीर्घ reg_with_cnic;
		#घोषणा BNX2FC_CNIC_REGISTERED           1
	काष्ठा bnx2fc_cmd_mgr *cmd_mgr;
	spinlock_t hba_lock;
	काष्ठा mutex hba_mutex;
	काष्ठा mutex hba_stats_mutex;
	अचिन्हित दीर्घ adapter_state;
		#घोषणा ADAPTER_STATE_UP		0
		#घोषणा ADAPTER_STATE_GOING_DOWN	1
		#घोषणा ADAPTER_STATE_LINK_DOWN		2
		#घोषणा ADAPTER_STATE_READY		3
	अचिन्हित दीर्घ flags;
		#घोषणा BNX2FC_FLAG_FW_INIT_DONE	0
		#घोषणा BNX2FC_FLAG_DESTROY_CMPL	1
	u32 next_conn_id;

	/* xid resources */
	u16 max_xid;
	u32 max_tasks;
	u32 max_outstanding_cmds;
	u32 elsपंचांग_xids;

	काष्ठा fcoe_task_ctx_entry **task_ctx;
	dma_addr_t *task_ctx_dma;
	काष्ठा regpair *task_ctx_bd_tbl;
	dma_addr_t task_ctx_bd_dma;

	पूर्णांक hash_tbl_segment_count;
	व्योम **hash_tbl_segments;
	व्योम *hash_tbl_pbl;
	dma_addr_t hash_tbl_pbl_dma;
	काष्ठा fcoe_t2_hash_table_entry *t2_hash_tbl;
	dma_addr_t t2_hash_tbl_dma;
	अक्षर *t2_hash_tbl_ptr;
	dma_addr_t t2_hash_tbl_ptr_dma;

	अक्षर *dummy_buffer;
	dma_addr_t dummy_buf_dma;

	/* Active list of offloaded sessions */
	काष्ठा bnx2fc_rport **tgt_ofld_list;

	/* statistics */
	काष्ठा bnx2fc_fw_stats bfw_stats;
	काष्ठा fcoe_statistics_params prev_stats;
	काष्ठा fcoe_statistics_params *stats_buffer;
	dma_addr_t stats_buf_dma;
	काष्ठा completion stat_req_करोne;
	काष्ठा fcoe_capabilities fcoe_cap;

	/*destroy handling */
	काष्ठा समयr_list destroy_समयr;
	रुको_queue_head_t destroy_रुको;

	/* linkकरोwn handling */
	रुको_queue_head_t shutकरोwn_रुको;
	पूर्णांक रुको_क्रम_link_करोwn;
	पूर्णांक num_ofld_sess;
	काष्ठा list_head vports;

	अक्षर chip_num[BCM_CHIP_LEN];
पूर्ण;

काष्ठा bnx2fc_पूर्णांकerface अणु
	काष्ठा list_head list;
	अचिन्हित दीर्घ अगर_flags;
		#घोषणा BNX2FC_CTLR_INIT_DONE		0
	काष्ठा bnx2fc_hba *hba;
	काष्ठा net_device *netdev;
	काष्ठा packet_type fcoe_packet_type;
	काष्ठा packet_type fip_packet_type;
	काष्ठा workqueue_काष्ठा *समयr_work_queue;
	काष्ठा kref kref;
	u8 vlan_enabled;
	पूर्णांक vlan_id;
	bool enabled;
	u8 पंचांग_समयout;
पूर्ण;

#घोषणा bnx2fc_from_ctlr(x)			\
	((काष्ठा bnx2fc_पूर्णांकerface *)((x) + 1))

#घोषणा bnx2fc_to_ctlr(x)					\
	((काष्ठा fcoe_ctlr *)(((काष्ठा fcoe_ctlr *)(x)) - 1))

काष्ठा bnx2fc_lport अणु
	काष्ठा list_head list;
	काष्ठा fc_lport *lport;
पूर्ण;

काष्ठा bnx2fc_cmd_mgr अणु
	काष्ठा bnx2fc_hba *hba;
	u16 next_idx;
	काष्ठा list_head *मुक्त_list;
	spinlock_t *मुक्त_list_lock;
	काष्ठा io_bdt **io_bdt_pool;
	काष्ठा bnx2fc_cmd **cmds;
पूर्ण;

काष्ठा bnx2fc_rport अणु
	काष्ठा fcoe_port *port;
	काष्ठा fc_rport *rport;
	काष्ठा fc_rport_priv *rdata;
	व्योम __iomem *ctx_base;
#घोषणा DPM_TRIGER_TYPE		0x40
	u32 io_समयout;
	u32 fcoe_conn_id;
	u32 context_id;
	u32 sid;
	पूर्णांक dev_type;

	अचिन्हित दीर्घ flags;
#घोषणा BNX2FC_FLAG_SESSION_READY	0x1
#घोषणा BNX2FC_FLAG_OFFLOADED		0x2
#घोषणा BNX2FC_FLAG_DISABLED		0x3
#घोषणा BNX2FC_FLAG_DESTROYED		0x4
#घोषणा BNX2FC_FLAG_OFLD_REQ_CMPL	0x5
#घोषणा BNX2FC_FLAG_CTX_ALLOC_FAILURE	0x6
#घोषणा BNX2FC_FLAG_UPLD_REQ_COMPL	0x7
#घोषणा BNX2FC_FLAG_DISABLE_FAILED	0x9
#घोषणा BNX2FC_FLAG_ENABLED		0xa

	u8 src_addr[ETH_ALEN];
	u32 max_sqes;
	u32 max_rqes;
	u32 max_cqes;
	atomic_t मुक्त_sqes;

	काष्ठा b577xx_करोorbell_set_prod sq_db;
	काष्ठा b577xx_fcoe_rx_करोorbell rx_db;

	काष्ठा fcoe_sqe *sq;
	dma_addr_t sq_dma;
	u16 sq_prod_idx;
	u8 sq_curr_toggle_bit;
	u32 sq_mem_size;

	काष्ठा fcoe_cqe *cq;
	dma_addr_t cq_dma;
	u16 cq_cons_idx;
	u8 cq_curr_toggle_bit;
	u32 cq_mem_size;

	व्योम *rq;
	dma_addr_t rq_dma;
	u32 rq_prod_idx;
	u32 rq_cons_idx;
	u32 rq_mem_size;

	व्योम *rq_pbl;
	dma_addr_t rq_pbl_dma;
	u32 rq_pbl_size;

	काष्ठा fcoe_xfrqe *xferq;
	dma_addr_t xferq_dma;
	u32 xferq_mem_size;

	काष्ठा fcoe_confqe *confq;
	dma_addr_t confq_dma;
	u32 confq_mem_size;

	व्योम *confq_pbl;
	dma_addr_t confq_pbl_dma;
	u32 confq_pbl_size;

	काष्ठा fcoe_conn_db *conn_db;
	dma_addr_t conn_db_dma;
	u32 conn_db_mem_size;

	काष्ठा fcoe_sqe *lcq;
	dma_addr_t lcq_dma;
	u32 lcq_mem_size;

	व्योम *ofld_req[4];
	dma_addr_t ofld_req_dma[4];
	व्योम *enbl_req;
	dma_addr_t enbl_req_dma;

	spinlock_t tgt_lock;
	spinlock_t cq_lock;
	atomic_t num_active_ios;
	u32 flush_in_prog;
	अचिन्हित दीर्घ बारtamp;
	अचिन्हित दीर्घ retry_delay_बारtamp;
	काष्ठा list_head मुक्त_task_list;
	काष्ठा bnx2fc_cmd *pending_queue[BNX2FC_SQ_WQES_MAX+1];
	काष्ठा list_head active_cmd_queue;
	काष्ठा list_head els_queue;
	काष्ठा list_head io_retire_queue;
	काष्ठा list_head active_पंचांग_queue;

	काष्ठा समयr_list ofld_समयr;
	रुको_queue_head_t ofld_रुको;

	काष्ठा समयr_list upld_समयr;
	रुको_queue_head_t upld_रुको;
पूर्ण;

काष्ठा bnx2fc_mp_req अणु
	u8 पंचांग_flags;

	u32 req_len;
	व्योम *req_buf;
	dma_addr_t req_buf_dma;
	काष्ठा fcoe_bd_ctx *mp_req_bd;
	dma_addr_t mp_req_bd_dma;
	काष्ठा fc_frame_header req_fc_hdr;

	u32 resp_len;
	व्योम *resp_buf;
	dma_addr_t resp_buf_dma;
	काष्ठा fcoe_bd_ctx *mp_resp_bd;
	dma_addr_t mp_resp_bd_dma;
	काष्ठा fc_frame_header resp_fc_hdr;
पूर्ण;

काष्ठा bnx2fc_els_cb_arg अणु
	काष्ठा bnx2fc_cmd *पातed_io_req;
	काष्ठा bnx2fc_cmd *io_req;
	u16 l2_oxid;
	u32 offset;
	क्रमागत fc_rctl r_ctl;
पूर्ण;

/* bnx2fc command काष्ठाure */
काष्ठा bnx2fc_cmd अणु
	काष्ठा list_head link;
	u8 on_active_queue;
	u8 on_पंचांगf_queue;
	u8 cmd_type;
#घोषणा BNX2FC_SCSI_CMD		1
#घोषणा BNX2FC_TASK_MGMT_CMD		2
#घोषणा BNX2FC_ABTS			3
#घोषणा BNX2FC_ELS			4
#घोषणा BNX2FC_CLEANUP			5
#घोषणा BNX2FC_SEQ_CLEANUP		6
	u8 io_req_flags;
	काष्ठा kref refcount;
	काष्ठा fcoe_port *port;
	काष्ठा bnx2fc_rport *tgt;
	काष्ठा scsi_cmnd *sc_cmd;
	काष्ठा bnx2fc_cmd_mgr *cmd_mgr;
	काष्ठा bnx2fc_mp_req mp_req;
	व्योम (*cb_func)(काष्ठा bnx2fc_els_cb_arg *cb_arg);
	काष्ठा bnx2fc_els_cb_arg *cb_arg;
	काष्ठा delayed_work समयout_work; /* समयr क्रम ULP समयouts */
	काष्ठा completion abts_करोne;
	काष्ठा completion cleanup_करोne;
	पूर्णांक रुको_क्रम_abts_comp;
	पूर्णांक रुको_क्रम_cleanup_comp;
	u16 xid;
	काष्ठा fcoe_err_report_entry err_entry;
	काष्ठा fcoe_task_ctx_entry *task;
	काष्ठा io_bdt *bd_tbl;
	काष्ठा fcp_rsp *rsp;
	माप_प्रकार data_xfer_len;
	अचिन्हित दीर्घ req_flags;
#घोषणा BNX2FC_FLAG_ISSUE_RRQ		0x1
#घोषणा BNX2FC_FLAG_ISSUE_ABTS		0x2
#घोषणा BNX2FC_FLAG_ABTS_DONE		0x3
#घोषणा BNX2FC_FLAG_TM_COMPL		0x4
#घोषणा BNX2FC_FLAG_TM_TIMEOUT		0x5
#घोषणा BNX2FC_FLAG_IO_CLEANUP		0x6
#घोषणा BNX2FC_FLAG_RETIRE_OXID		0x7
#घोषणा	BNX2FC_FLAG_EH_ABORT		0x8
#घोषणा BNX2FC_FLAG_IO_COMPL		0x9
#घोषणा BNX2FC_FLAG_ELS_DONE		0xa
#घोषणा BNX2FC_FLAG_ELS_TIMEOUT		0xb
#घोषणा BNX2FC_FLAG_CMD_LOST		0xc
#घोषणा BNX2FC_FLAG_SRR_SENT		0xd
#घोषणा BNX2FC_FLAG_ISSUE_CLEANUP_REQ	0xe
	u8 rec_retry;
	u8 srr_retry;
	u32 srr_offset;
	u8 srr_rctl;
	u32 fcp_resid;
	u32 fcp_rsp_len;
	u32 fcp_sns_len;
	u8 cdb_status; /* SCSI IO status */
	u8 fcp_status; /* FCP IO status */
	u8 fcp_rsp_code;
	u8 scsi_comp_flags;
पूर्ण;

काष्ठा io_bdt अणु
	काष्ठा bnx2fc_cmd *io_req;
	काष्ठा fcoe_bd_ctx *bd_tbl;
	dma_addr_t bd_tbl_dma;
	u16 bd_valid;
पूर्ण;

काष्ठा bnx2fc_work अणु
	काष्ठा list_head list;
	काष्ठा bnx2fc_rport *tgt;
	काष्ठा fcoe_task_ctx_entry *task;
	अचिन्हित अक्षर rq_data[BNX2FC_RQ_BUF_SZ];
	u16 wqe;
	u8 num_rq;
पूर्ण;
काष्ठा bnx2fc_unsol_els अणु
	काष्ठा fc_lport *lport;
	काष्ठा fc_frame *fp;
	काष्ठा bnx2fc_hba *hba;
	काष्ठा work_काष्ठा unsol_els_work;
पूर्ण;



काष्ठा bnx2fc_cmd *bnx2fc_cmd_alloc(काष्ठा bnx2fc_rport *tgt);
काष्ठा bnx2fc_cmd *bnx2fc_elsपंचांग_alloc(काष्ठा bnx2fc_rport *tgt, पूर्णांक type);
व्योम bnx2fc_cmd_release(काष्ठा kref *ref);
पूर्णांक bnx2fc_queuecommand(काष्ठा Scsi_Host *host, काष्ठा scsi_cmnd *sc_cmd);
पूर्णांक bnx2fc_send_fw_fcoe_init_msg(काष्ठा bnx2fc_hba *hba);
पूर्णांक bnx2fc_send_fw_fcoe_destroy_msg(काष्ठा bnx2fc_hba *hba);
पूर्णांक bnx2fc_send_session_ofld_req(काष्ठा fcoe_port *port,
					काष्ठा bnx2fc_rport *tgt);
पूर्णांक bnx2fc_send_session_enable_req(काष्ठा fcoe_port *port,
					काष्ठा bnx2fc_rport *tgt);
पूर्णांक bnx2fc_send_session_disable_req(काष्ठा fcoe_port *port,
				    काष्ठा bnx2fc_rport *tgt);
पूर्णांक bnx2fc_send_session_destroy_req(काष्ठा bnx2fc_hba *hba,
					काष्ठा bnx2fc_rport *tgt);
पूर्णांक bnx2fc_map_करोorbell(काष्ठा bnx2fc_rport *tgt);
व्योम bnx2fc_indicate_kcqe(व्योम *context, काष्ठा kcqe *kcq[],
					u32 num_cqe);
पूर्णांक bnx2fc_setup_task_ctx(काष्ठा bnx2fc_hba *hba);
व्योम bnx2fc_मुक्त_task_ctx(काष्ठा bnx2fc_hba *hba);
पूर्णांक bnx2fc_setup_fw_resc(काष्ठा bnx2fc_hba *hba);
व्योम bnx2fc_मुक्त_fw_resc(काष्ठा bnx2fc_hba *hba);
काष्ठा bnx2fc_cmd_mgr *bnx2fc_cmd_mgr_alloc(काष्ठा bnx2fc_hba *hba);
व्योम bnx2fc_cmd_mgr_मुक्त(काष्ठा bnx2fc_cmd_mgr *cmgr);
व्योम bnx2fc_get_link_state(काष्ठा bnx2fc_hba *hba);
अक्षर *bnx2fc_get_next_rqe(काष्ठा bnx2fc_rport *tgt, u8 num_items);
व्योम bnx2fc_वापस_rqe(काष्ठा bnx2fc_rport *tgt, u8 num_items);
पूर्णांक bnx2fc_get_paged_crc_eof(काष्ठा sk_buff *skb, पूर्णांक tlen);
पूर्णांक bnx2fc_send_rrq(काष्ठा bnx2fc_cmd *पातed_io_req);
पूर्णांक bnx2fc_send_adisc(काष्ठा bnx2fc_rport *tgt, काष्ठा fc_frame *fp);
पूर्णांक bnx2fc_send_logo(काष्ठा bnx2fc_rport *tgt, काष्ठा fc_frame *fp);
पूर्णांक bnx2fc_send_rls(काष्ठा bnx2fc_rport *tgt, काष्ठा fc_frame *fp);
पूर्णांक bnx2fc_initiate_cleanup(काष्ठा bnx2fc_cmd *io_req);
पूर्णांक bnx2fc_initiate_abts(काष्ठा bnx2fc_cmd *io_req);
व्योम bnx2fc_cmd_समयr_set(काष्ठा bnx2fc_cmd *io_req,
			  अचिन्हित पूर्णांक समयr_msec);
पूर्णांक bnx2fc_init_mp_req(काष्ठा bnx2fc_cmd *io_req);
व्योम bnx2fc_init_cleanup_task(काष्ठा bnx2fc_cmd *io_req,
			      काष्ठा fcoe_task_ctx_entry *task,
			      u16 orig_xid);
व्योम bnx2fc_init_seq_cleanup_task(काष्ठा bnx2fc_cmd *seq_clnup_req,
				  काष्ठा fcoe_task_ctx_entry *task,
				  काष्ठा bnx2fc_cmd *orig_io_req,
				  u32 offset);
व्योम bnx2fc_init_mp_task(काष्ठा bnx2fc_cmd *io_req,
			 काष्ठा fcoe_task_ctx_entry *task);
व्योम bnx2fc_init_task(काष्ठा bnx2fc_cmd *io_req,
			     काष्ठा fcoe_task_ctx_entry *task);
व्योम bnx2fc_add_2_sq(काष्ठा bnx2fc_rport *tgt, u16 xid);
व्योम bnx2fc_ring_करोorbell(काष्ठा bnx2fc_rport *tgt);
पूर्णांक bnx2fc_eh_पात(काष्ठा scsi_cmnd *sc_cmd);
पूर्णांक bnx2fc_eh_target_reset(काष्ठा scsi_cmnd *sc_cmd);
पूर्णांक bnx2fc_eh_device_reset(काष्ठा scsi_cmnd *sc_cmd);
व्योम bnx2fc_rport_event_handler(काष्ठा fc_lport *lport,
				काष्ठा fc_rport_priv *rport,
				क्रमागत fc_rport_event event);
व्योम bnx2fc_process_scsi_cmd_compl(काष्ठा bnx2fc_cmd *io_req,
				   काष्ठा fcoe_task_ctx_entry *task,
				   u8 num_rq, अचिन्हित अक्षर *rq_data);
व्योम bnx2fc_process_cleanup_compl(काष्ठा bnx2fc_cmd *io_req,
			       काष्ठा fcoe_task_ctx_entry *task,
			       u8 num_rq);
व्योम bnx2fc_process_abts_compl(काष्ठा bnx2fc_cmd *io_req,
			       काष्ठा fcoe_task_ctx_entry *task,
			       u8 num_rq);
व्योम bnx2fc_process_पंचांग_compl(काष्ठा bnx2fc_cmd *io_req,
			     काष्ठा fcoe_task_ctx_entry *task,
			     u8 num_rq, अचिन्हित अक्षर *rq_data);
व्योम bnx2fc_process_els_compl(काष्ठा bnx2fc_cmd *els_req,
			      काष्ठा fcoe_task_ctx_entry *task,
			      u8 num_rq);
व्योम bnx2fc_build_fcp_cmnd(काष्ठा bnx2fc_cmd *io_req,
			   काष्ठा fcp_cmnd *fcp_cmnd);



व्योम bnx2fc_flush_active_ios(काष्ठा bnx2fc_rport *tgt);
काष्ठा fc_seq *bnx2fc_elsct_send(काष्ठा fc_lport *lport, u32 did,
				      काष्ठा fc_frame *fp, अचिन्हित पूर्णांक op,
				      व्योम (*resp)(काष्ठा fc_seq *,
						   काष्ठा fc_frame *,
						   व्योम *),
				      व्योम *arg, u32 समयout);
व्योम bnx2fc_arm_cq(काष्ठा bnx2fc_rport *tgt);
पूर्णांक bnx2fc_process_new_cqes(काष्ठा bnx2fc_rport *tgt);
व्योम bnx2fc_process_cq_compl(काष्ठा bnx2fc_rport *tgt, u16 wqe,
			     अचिन्हित अक्षर *rq_data, u8 num_rq,
			     काष्ठा fcoe_task_ctx_entry *task);
काष्ठा bnx2fc_rport *bnx2fc_tgt_lookup(काष्ठा fcoe_port *port,
					     u32 port_id);
व्योम bnx2fc_process_l2_frame_compl(काष्ठा bnx2fc_rport *tgt,
				   अचिन्हित अक्षर *buf,
				   u32 frame_len, u16 l2_oxid);
पूर्णांक bnx2fc_send_stat_req(काष्ठा bnx2fc_hba *hba);
पूर्णांक bnx2fc_post_io_req(काष्ठा bnx2fc_rport *tgt, काष्ठा bnx2fc_cmd *io_req);
पूर्णांक bnx2fc_send_rec(काष्ठा bnx2fc_cmd *orig_io_req);
पूर्णांक bnx2fc_send_srr(काष्ठा bnx2fc_cmd *orig_io_req, u32 offset, u8 r_ctl);
व्योम bnx2fc_process_seq_cleanup_compl(काष्ठा bnx2fc_cmd *seq_clnup_req,
				      काष्ठा fcoe_task_ctx_entry *task,
				      u8 rx_state);
पूर्णांक bnx2fc_initiate_seq_cleanup(काष्ठा bnx2fc_cmd *orig_io_req, u32 offset,
				क्रमागत fc_rctl r_ctl);


#समावेश "bnx2fc_debug.h"

#पूर्ण_अगर
