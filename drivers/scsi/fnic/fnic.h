<शैली गुरु>
/*
 * Copyright 2008 Cisco Systems, Inc.  All rights reserved.
 * Copyright 2007 Nuova Systems, Inc.  All rights reserved.
 *
 * This program is मुक्त software; you may redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
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
#अगर_अघोषित _FNIC_H_
#घोषणा _FNIC_H_

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/bitops.h>
#समावेश <scsi/libfc.h>
#समावेश <scsi/libfcoe.h>
#समावेश "fnic_io.h"
#समावेश "fnic_res.h"
#समावेश "fnic_trace.h"
#समावेश "fnic_stats.h"
#समावेश "vnic_dev.h"
#समावेश "vnic_wq.h"
#समावेश "vnic_rq.h"
#समावेश "vnic_cq.h"
#समावेश "vnic_wq_copy.h"
#समावेश "vnic_intr.h"
#समावेश "vnic_stats.h"
#समावेश "vnic_scsi.h"

#घोषणा DRV_NAME		"fnic"
#घोषणा DRV_DESCRIPTION		"Cisco FCoE HBA Driver"
#घोषणा DRV_VERSION		"1.6.0.53"
#घोषणा PFX			DRV_NAME ": "
#घोषणा DFX                     DRV_NAME "%d: "

#घोषणा DESC_CLEAN_LOW_WATERMARK 8
#घोषणा FNIC_UCSM_DFLT_THROTTLE_CNT_BLD	16 /* UCSM शेष throttle count */
#घोषणा FNIC_MIN_IO_REQ			256 /* Min IO throttle count */
#घोषणा FNIC_MAX_IO_REQ		1024 /* scsi_cmnd tag map entries */
#घोषणा FNIC_DFLT_IO_REQ        256 /* Default scsi_cmnd tag map entries */
#घोषणा	FNIC_IO_LOCKS		64 /* IO locks: घातer of 2 */
#घोषणा FNIC_DFLT_QUEUE_DEPTH	256
#घोषणा	FNIC_STATS_RATE_LIMIT	4 /* limit rate at which stats are pulled up */

/*
 * Tag bits used क्रम special requests.
 */
#घोषणा FNIC_TAG_ABORT		BIT(30)		/* tag bit indicating पात */
#घोषणा FNIC_TAG_DEV_RST	BIT(29)		/* indicates device reset */
#घोषणा FNIC_TAG_MASK		(BIT(24) - 1)	/* mask क्रम lookup */
#घोषणा FNIC_NO_TAG             -1

/*
 * Command flags to identअगरy the type of command and क्रम other future
 * use.
 */
#घोषणा FNIC_NO_FLAGS                   0
#घोषणा FNIC_IO_INITIALIZED             BIT(0)
#घोषणा FNIC_IO_ISSUED                  BIT(1)
#घोषणा FNIC_IO_DONE                    BIT(2)
#घोषणा FNIC_IO_REQ_शून्य                BIT(3)
#घोषणा FNIC_IO_ABTS_PENDING            BIT(4)
#घोषणा FNIC_IO_ABORTED                 BIT(5)
#घोषणा FNIC_IO_ABTS_ISSUED             BIT(6)
#घोषणा FNIC_IO_TERM_ISSUED             BIT(7)
#घोषणा FNIC_IO_INTERNAL_TERM_ISSUED    BIT(8)
#घोषणा FNIC_IO_ABT_TERM_DONE           BIT(9)
#घोषणा FNIC_IO_ABT_TERM_REQ_शून्य       BIT(10)
#घोषणा FNIC_IO_ABT_TERM_TIMED_OUT      BIT(11)
#घोषणा FNIC_DEVICE_RESET               BIT(12)  /* Device reset request */
#घोषणा FNIC_DEV_RST_ISSUED             BIT(13)
#घोषणा FNIC_DEV_RST_TIMED_OUT          BIT(14)
#घोषणा FNIC_DEV_RST_ABTS_ISSUED        BIT(15)
#घोषणा FNIC_DEV_RST_TERM_ISSUED        BIT(16)
#घोषणा FNIC_DEV_RST_DONE               BIT(17)
#घोषणा FNIC_DEV_RST_REQ_शून्य           BIT(18)
#घोषणा FNIC_DEV_RST_ABTS_DONE          BIT(19)
#घोषणा FNIC_DEV_RST_TERM_DONE          BIT(20)
#घोषणा FNIC_DEV_RST_ABTS_PENDING       BIT(21)

/*
 * Usage of the scsi_cmnd scratchpad.
 * These fields are locked by the hashed io_req_lock.
 */
#घोषणा CMD_SP(Cmnd)		((Cmnd)->SCp.ptr)
#घोषणा CMD_STATE(Cmnd)		((Cmnd)->SCp.phase)
#घोषणा CMD_ABTS_STATUS(Cmnd)	((Cmnd)->SCp.Message)
#घोषणा CMD_LR_STATUS(Cmnd)	((Cmnd)->SCp.have_data_in)
#घोषणा CMD_TAG(Cmnd)           ((Cmnd)->SCp.sent_command)
#घोषणा CMD_FLAGS(Cmnd)         ((Cmnd)->SCp.Status)

#घोषणा FCPIO_INVALID_CODE 0x100 /* hdr_status value unused by firmware */

#घोषणा FNIC_LUN_RESET_TIMEOUT	     10000	/* mSec */
#घोषणा FNIC_HOST_RESET_TIMEOUT	     10000	/* mSec */
#घोषणा FNIC_RMDEVICE_TIMEOUT        1000       /* mSec */
#घोषणा FNIC_HOST_RESET_SETTLE_TIME  30         /* Sec */
#घोषणा FNIC_ABT_TERM_DELAY_TIMEOUT  500        /* mSec */

#घोषणा FNIC_MAX_FCP_TARGET     256

/**
 * state_flags to identअगरy host state aदीर्घ aदीर्घ with fnic's state
 **/
#घोषणा __FNIC_FLAGS_FWRESET		BIT(0) /* fwreset in progress */
#घोषणा __FNIC_FLAGS_BLOCK_IO		BIT(1) /* IOs are blocked */

#घोषणा FNIC_FLAGS_NONE			(0)
#घोषणा FNIC_FLAGS_FWRESET		(__FNIC_FLAGS_FWRESET | \
					__FNIC_FLAGS_BLOCK_IO)

#घोषणा FNIC_FLAGS_IO_BLOCKED		(__FNIC_FLAGS_BLOCK_IO)

#घोषणा fnic_set_state_flags(fnicp, st_flags)	\
	__fnic_set_state_flags(fnicp, st_flags, 0)

#घोषणा fnic_clear_state_flags(fnicp, st_flags)  \
	__fnic_set_state_flags(fnicp, st_flags, 1)

बाह्य अचिन्हित पूर्णांक fnic_log_level;
बाह्य अचिन्हित पूर्णांक io_completions;

#घोषणा FNIC_MAIN_LOGGING 0x01
#घोषणा FNIC_FCS_LOGGING 0x02
#घोषणा FNIC_SCSI_LOGGING 0x04
#घोषणा FNIC_ISR_LOGGING 0x08

#घोषणा FNIC_CHECK_LOGGING(LEVEL, CMD)				\
करो अणु								\
	अगर (unlikely(fnic_log_level & LEVEL))			\
		करो अणु						\
			CMD;					\
		पूर्ण जबतक (0);					\
पूर्ण जबतक (0)

#घोषणा FNIC_MAIN_DBG(kern_level, host, fmt, args...)		\
	FNIC_CHECK_LOGGING(FNIC_MAIN_LOGGING,			\
			 shost_prपूर्णांकk(kern_level, host, fmt, ##args);)

#घोषणा FNIC_FCS_DBG(kern_level, host, fmt, args...)		\
	FNIC_CHECK_LOGGING(FNIC_FCS_LOGGING,			\
			 shost_prपूर्णांकk(kern_level, host, fmt, ##args);)

#घोषणा FNIC_SCSI_DBG(kern_level, host, fmt, args...)		\
	FNIC_CHECK_LOGGING(FNIC_SCSI_LOGGING,			\
			 shost_prपूर्णांकk(kern_level, host, fmt, ##args);)

#घोषणा FNIC_ISR_DBG(kern_level, host, fmt, args...)		\
	FNIC_CHECK_LOGGING(FNIC_ISR_LOGGING,			\
			 shost_prपूर्णांकk(kern_level, host, fmt, ##args);)

#घोषणा FNIC_MAIN_NOTE(kern_level, host, fmt, args...)          \
	shost_prपूर्णांकk(kern_level, host, fmt, ##args)

बाह्य स्थिर अक्षर *fnic_state_str[];

क्रमागत fnic_पूर्णांकx_पूर्णांकr_index अणु
	FNIC_INTX_WQ_RQ_COPYWQ,
	FNIC_INTX_ERR,
	FNIC_INTX_NOTIFY,
	FNIC_INTX_INTR_MAX,
पूर्ण;

क्रमागत fnic_msix_पूर्णांकr_index अणु
	FNIC_MSIX_RQ,
	FNIC_MSIX_WQ,
	FNIC_MSIX_WQ_COPY,
	FNIC_MSIX_ERR_NOTIFY,
	FNIC_MSIX_INTR_MAX,
पूर्ण;

काष्ठा fnic_msix_entry अणु
	पूर्णांक requested;
	अक्षर devname[IFNAMSIZ + 11];
	irqवापस_t (*isr)(पूर्णांक, व्योम *);
	व्योम *devid;
पूर्ण;

क्रमागत fnic_state अणु
	FNIC_IN_FC_MODE = 0,
	FNIC_IN_FC_TRANS_ETH_MODE,
	FNIC_IN_ETH_MODE,
	FNIC_IN_ETH_TRANS_FC_MODE,
पूर्ण;

#घोषणा FNIC_WQ_COPY_MAX 1
#घोषणा FNIC_WQ_MAX 1
#घोषणा FNIC_RQ_MAX 1
#घोषणा FNIC_CQ_MAX (FNIC_WQ_COPY_MAX + FNIC_WQ_MAX + FNIC_RQ_MAX)
#घोषणा FNIC_DFLT_IO_COMPLETIONS 256

काष्ठा mempool;

क्रमागत fnic_evt अणु
	FNIC_EVT_START_VLAN_DISC = 1,
	FNIC_EVT_START_FCF_DISC = 2,
	FNIC_EVT_MAX,
पूर्ण;

काष्ठा fnic_event अणु
	काष्ठा list_head list;
	काष्ठा fnic *fnic;
	क्रमागत fnic_evt event;
पूर्ण;

/* Per-instance निजी data काष्ठाure */
काष्ठा fnic अणु
	काष्ठा fc_lport *lport;
	काष्ठा fcoe_ctlr ctlr;		/* FIP FCoE controller काष्ठाure */
	काष्ठा vnic_dev_bar bar0;

	काष्ठा fnic_msix_entry msix[FNIC_MSIX_INTR_MAX];

	काष्ठा vnic_stats *stats;
	अचिन्हित दीर्घ stats_समय;	/* समय of stats update */
	अचिन्हित दीर्घ stats_reset_समय; /* समय of stats reset */
	काष्ठा vnic_nic_cfg *nic_cfg;
	अक्षर name[IFNAMSIZ];
	काष्ठा समयr_list notअगरy_समयr; /* used क्रम MSI पूर्णांकerrupts */

	अचिन्हित पूर्णांक fnic_max_tag_id;
	अचिन्हित पूर्णांक err_पूर्णांकr_offset;
	अचिन्हित पूर्णांक link_पूर्णांकr_offset;

	अचिन्हित पूर्णांक wq_count;
	अचिन्हित पूर्णांक cq_count;

	काष्ठा dentry *fnic_stats_debugfs_host;
	काष्ठा dentry *fnic_stats_debugfs_file;
	काष्ठा dentry *fnic_reset_debugfs_file;
	अचिन्हित पूर्णांक reset_stats;
	atomic64_t io_cmpl_skip;
	काष्ठा fnic_stats fnic_stats;

	u32 vlan_hw_insert:1;	        /* let hw insert the tag */
	u32 in_हटाओ:1;                /* fnic device in removal */
	u32 stop_rx_link_events:1;      /* stop proc. rx frames, link events */
	u32 link_events:1;              /* set when we get any link event*/

	काष्ठा completion *हटाओ_रुको; /* device हटाओ thपढ़ो blocks */

	atomic_t in_flight;		/* io counter */
	bool पूर्णांकernal_reset_inprogress;
	u32 _reserved;			/* fill hole */
	अचिन्हित दीर्घ state_flags;	/* रक्षित by host lock */
	क्रमागत fnic_state state;
	spinlock_t fnic_lock;

	u16 vlan_id;	                /* VLAN tag including priority */
	u8 data_src_addr[ETH_ALEN];
	u64 fcp_input_bytes;		/* पूर्णांकernal statistic */
	u64 fcp_output_bytes;		/* पूर्णांकernal statistic */
	u32 link_करोwn_cnt;
	पूर्णांक link_status;

	काष्ठा list_head list;
	काष्ठा pci_dev *pdev;
	काष्ठा vnic_fc_config config;
	काष्ठा vnic_dev *vdev;
	अचिन्हित पूर्णांक raw_wq_count;
	अचिन्हित पूर्णांक wq_copy_count;
	अचिन्हित पूर्णांक rq_count;
	पूर्णांक fw_ack_index[FNIC_WQ_COPY_MAX];
	अचिन्हित लघु fw_ack_recd[FNIC_WQ_COPY_MAX];
	अचिन्हित लघु wq_copy_desc_low[FNIC_WQ_COPY_MAX];
	अचिन्हित पूर्णांक पूर्णांकr_count;
	u32 __iomem *legacy_pba;
	काष्ठा fnic_host_tag *tags;
	mempool_t *io_req_pool;
	mempool_t *io_sgl_pool[FNIC_SGL_NUM_CACHES];
	spinlock_t io_req_lock[FNIC_IO_LOCKS];	/* locks क्रम scsi cmnds */

	काष्ठा work_काष्ठा link_work;
	काष्ठा work_काष्ठा frame_work;
	काष्ठा sk_buff_head frame_queue;
	काष्ठा sk_buff_head tx_queue;

	/*** FIP related data members  -- start ***/
	व्योम (*set_vlan)(काष्ठा fnic *, u16 vlan);
	काष्ठा work_काष्ठा      fip_frame_work;
	काष्ठा sk_buff_head     fip_frame_queue;
	काष्ठा समयr_list       fip_समयr;
	काष्ठा list_head        vlans;
	spinlock_t              vlans_lock;

	काष्ठा work_काष्ठा      event_work;
	काष्ठा list_head        evlist;
	/*** FIP related data members  -- end ***/

	/* copy work queue cache line section */
	____cacheline_aligned काष्ठा vnic_wq_copy wq_copy[FNIC_WQ_COPY_MAX];
	/* completion queue cache line section */
	____cacheline_aligned काष्ठा vnic_cq cq[FNIC_CQ_MAX];

	spinlock_t wq_copy_lock[FNIC_WQ_COPY_MAX];

	/* work queue cache line section */
	____cacheline_aligned काष्ठा vnic_wq wq[FNIC_WQ_MAX];
	spinlock_t wq_lock[FNIC_WQ_MAX];

	/* receive queue cache line section */
	____cacheline_aligned काष्ठा vnic_rq rq[FNIC_RQ_MAX];

	/* पूर्णांकerrupt resource cache line section */
	____cacheline_aligned काष्ठा vnic_पूर्णांकr पूर्णांकr[FNIC_MSIX_INTR_MAX];
पूर्ण;

अटल अंतरभूत काष्ठा fnic *fnic_from_ctlr(काष्ठा fcoe_ctlr *fip)
अणु
	वापस container_of(fip, काष्ठा fnic, ctlr);
पूर्ण

बाह्य काष्ठा workqueue_काष्ठा *fnic_event_queue;
बाह्य काष्ठा workqueue_काष्ठा *fnic_fip_queue;
बाह्य काष्ठा device_attribute *fnic_attrs[];

व्योम fnic_clear_पूर्णांकr_mode(काष्ठा fnic *fnic);
पूर्णांक fnic_set_पूर्णांकr_mode(काष्ठा fnic *fnic);
व्योम fnic_मुक्त_पूर्णांकr(काष्ठा fnic *fnic);
पूर्णांक fnic_request_पूर्णांकr(काष्ठा fnic *fnic);

पूर्णांक fnic_send(काष्ठा fc_lport *, काष्ठा fc_frame *);
व्योम fnic_मुक्त_wq_buf(काष्ठा vnic_wq *wq, काष्ठा vnic_wq_buf *buf);
व्योम fnic_handle_frame(काष्ठा work_काष्ठा *work);
व्योम fnic_handle_link(काष्ठा work_काष्ठा *work);
व्योम fnic_handle_event(काष्ठा work_काष्ठा *work);
पूर्णांक fnic_rq_cmpl_handler(काष्ठा fnic *fnic, पूर्णांक);
पूर्णांक fnic_alloc_rq_frame(काष्ठा vnic_rq *rq);
व्योम fnic_मुक्त_rq_buf(काष्ठा vnic_rq *rq, काष्ठा vnic_rq_buf *buf);
व्योम fnic_flush_tx(काष्ठा fnic *);
व्योम fnic_eth_send(काष्ठा fcoe_ctlr *, काष्ठा sk_buff *skb);
व्योम fnic_set_port_id(काष्ठा fc_lport *, u32, काष्ठा fc_frame *);
व्योम fnic_update_mac(काष्ठा fc_lport *, u8 *new);
व्योम fnic_update_mac_locked(काष्ठा fnic *, u8 *new);

पूर्णांक fnic_queuecommand(काष्ठा Scsi_Host *, काष्ठा scsi_cmnd *);
पूर्णांक fnic_पात_cmd(काष्ठा scsi_cmnd *);
पूर्णांक fnic_device_reset(काष्ठा scsi_cmnd *);
पूर्णांक fnic_host_reset(काष्ठा scsi_cmnd *);
पूर्णांक fnic_reset(काष्ठा Scsi_Host *);
व्योम fnic_scsi_cleanup(काष्ठा fc_lport *);
व्योम fnic_scsi_पात_io(काष्ठा fc_lport *);
व्योम fnic_empty_scsi_cleanup(काष्ठा fc_lport *);
व्योम fnic_exch_mgr_reset(काष्ठा fc_lport *, u32, u32);
पूर्णांक fnic_wq_copy_cmpl_handler(काष्ठा fnic *fnic, पूर्णांक);
पूर्णांक fnic_wq_cmpl_handler(काष्ठा fnic *fnic, पूर्णांक);
पूर्णांक fnic_flogi_reg_handler(काष्ठा fnic *fnic, u32);
व्योम fnic_wq_copy_cleanup_handler(काष्ठा vnic_wq_copy *wq,
				  काष्ठा fcpio_host_req *desc);
पूर्णांक fnic_fw_reset_handler(काष्ठा fnic *fnic);
व्योम fnic_terminate_rport_io(काष्ठा fc_rport *);
स्थिर अक्षर *fnic_state_to_str(अचिन्हित पूर्णांक state);

व्योम fnic_log_q_error(काष्ठा fnic *fnic);
व्योम fnic_handle_link_event(काष्ठा fnic *fnic);

पूर्णांक fnic_is_abts_pending(काष्ठा fnic *, काष्ठा scsi_cmnd *);

व्योम fnic_handle_fip_frame(काष्ठा work_काष्ठा *work);
व्योम fnic_handle_fip_event(काष्ठा fnic *fnic);
व्योम fnic_fcoe_reset_vlans(काष्ठा fnic *fnic);
व्योम fnic_fcoe_evlist_मुक्त(काष्ठा fnic *fnic);
बाह्य व्योम fnic_handle_fip_समयr(काष्ठा fnic *fnic);

अटल अंतरभूत पूर्णांक
fnic_chk_state_flags_locked(काष्ठा fnic *fnic, अचिन्हित दीर्घ st_flags)
अणु
	वापस ((fnic->state_flags & st_flags) == st_flags);
पूर्ण
व्योम __fnic_set_state_flags(काष्ठा fnic *, अचिन्हित दीर्घ, अचिन्हित दीर्घ);
व्योम fnic_dump_fchost_stats(काष्ठा Scsi_Host *, काष्ठा fc_host_statistics *);
#पूर्ण_अगर /* _FNIC_H_ */
