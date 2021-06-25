<शैली गुरु>
/*
 * Copyright 2014 Cisco Systems, Inc.  All rights reserved.
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

#अगर_अघोषित _SNIC_H_
#घोषणा _SNIC_H_

#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/bitops.h>
#समावेश <linux/mempool.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_host.h>

#समावेश "snic_disc.h"
#समावेश "snic_io.h"
#समावेश "snic_res.h"
#समावेश "snic_trc.h"
#समावेश "snic_stats.h"
#समावेश "vnic_dev.h"
#समावेश "vnic_wq.h"
#समावेश "vnic_cq.h"
#समावेश "vnic_intr.h"
#समावेश "vnic_stats.h"
#समावेश "vnic_snic.h"

#घोषणा SNIC_DRV_NAME		"snic"
#घोषणा SNIC_DRV_DESCRIPTION	"Cisco SCSI NIC Driver"
#घोषणा SNIC_DRV_VERSION	"0.0.1.18"
#घोषणा PFX			SNIC_DRV_NAME ":"
#घोषणा DFX			SNIC_DRV_NAME "%d: "

#घोषणा DESC_CLEAN_LOW_WATERMARK	8
#घोषणा SNIC_UCSM_DFLT_THROTTLE_CNT_BLD 16 /* UCSM शेष throttle count */
#घोषणा SNIC_MAX_IO_REQ			50 /* scsi_cmnd tag map entries */
#घोषणा SNIC_MIN_IO_REQ			8  /* Min IO throttle count */
#घोषणा SNIC_IO_LOCKS			64 /* IO locks: घातer of 2 */
#घोषणा SNIC_DFLT_QUEUE_DEPTH		32 /* Default Queue Depth */
#घोषणा SNIC_MAX_QUEUE_DEPTH		64 /* Max Queue Depth */
#घोषणा SNIC_DFLT_CMD_TIMEOUT		90 /* Extended पंचांगo क्रम FW */

/*
 * Tag bits used क्रम special requests.
 */
#घोषणा SNIC_TAG_ABORT		BIT(30)		/* Tag indicating पात */
#घोषणा SNIC_TAG_DEV_RST	BIT(29)		/* Tag क्रम device reset */
#घोषणा SNIC_TAG_IOCTL_DEV_RST	BIT(28)		/* Tag क्रम User Device Reset */
#घोषणा SNIC_TAG_MASK		(BIT(24) - 1)	/* Mask क्रम lookup */
#घोषणा SNIC_NO_TAG		-1

/*
 * Command flags to identअगरy the type of command and क्रम other future use
 */
#घोषणा SNIC_NO_FLAGS			0
#घोषणा SNIC_IO_INITIALIZED		BIT(0)
#घोषणा SNIC_IO_ISSUED			BIT(1)
#घोषणा SNIC_IO_DONE			BIT(2)
#घोषणा SNIC_IO_REQ_शून्य		BIT(3)
#घोषणा SNIC_IO_ABTS_PENDING		BIT(4)
#घोषणा SNIC_IO_ABORTED			BIT(5)
#घोषणा SNIC_IO_ABTS_ISSUED		BIT(6)
#घोषणा SNIC_IO_TERM_ISSUED		BIT(7)
#घोषणा SNIC_IO_ABTS_TIMEDOUT		BIT(8)
#घोषणा SNIC_IO_ABTS_TERM_DONE		BIT(9)
#घोषणा SNIC_IO_ABTS_TERM_REQ_शून्य	BIT(10)
#घोषणा SNIC_IO_ABTS_TERM_TIMEDOUT	BIT(11)
#घोषणा SNIC_IO_INTERNAL_TERM_PENDING	BIT(12)
#घोषणा SNIC_IO_INTERNAL_TERM_ISSUED	BIT(13)
#घोषणा SNIC_DEVICE_RESET		BIT(14)
#घोषणा SNIC_DEV_RST_ISSUED		BIT(15)
#घोषणा SNIC_DEV_RST_TIMEDOUT		BIT(16)
#घोषणा SNIC_DEV_RST_ABTS_ISSUED	BIT(17)
#घोषणा SNIC_DEV_RST_TERM_ISSUED	BIT(18)
#घोषणा SNIC_DEV_RST_DONE		BIT(19)
#घोषणा SNIC_DEV_RST_REQ_शून्य		BIT(20)
#घोषणा SNIC_DEV_RST_ABTS_DONE		BIT(21)
#घोषणा SNIC_DEV_RST_TERM_DONE		BIT(22)
#घोषणा SNIC_DEV_RST_ABTS_PENDING	BIT(23)
#घोषणा SNIC_DEV_RST_PENDING		BIT(24)
#घोषणा SNIC_DEV_RST_NOTSUP		BIT(25)
#घोषणा SNIC_SCSI_CLEANUP		BIT(26)
#घोषणा SNIC_HOST_RESET_ISSUED		BIT(27)
#घोषणा SNIC_HOST_RESET_CMD_TERM	\
	(SNIC_DEV_RST_NOTSUP | SNIC_SCSI_CLEANUP | SNIC_HOST_RESET_ISSUED)

#घोषणा SNIC_ABTS_TIMEOUT		30000		/* msec */
#घोषणा SNIC_LUN_RESET_TIMEOUT		30000		/* msec */
#घोषणा SNIC_HOST_RESET_TIMEOUT		30000		/* msec */


/*
 * These are रक्षित by the hashed req_lock.
 */
#घोषणा CMD_SP(Cmnd)		\
	(((काष्ठा snic_पूर्णांकernal_io_state *)scsi_cmd_priv(Cmnd))->rqi)
#घोषणा CMD_STATE(Cmnd)		\
	(((काष्ठा snic_पूर्णांकernal_io_state *)scsi_cmd_priv(Cmnd))->state)
#घोषणा CMD_ABTS_STATUS(Cmnd)	\
	(((काष्ठा snic_पूर्णांकernal_io_state *)scsi_cmd_priv(Cmnd))->abts_status)
#घोषणा CMD_LR_STATUS(Cmnd)	\
	(((काष्ठा snic_पूर्णांकernal_io_state *)scsi_cmd_priv(Cmnd))->lr_status)
#घोषणा CMD_FLAGS(Cmnd)	\
	(((काष्ठा snic_पूर्णांकernal_io_state *)scsi_cmd_priv(Cmnd))->flags)

#घोषणा SNIC_INVALID_CODE 0x100	/* Hdr Status val unused by firmware */

#घोषणा SNIC_MAX_TARGET			256
#घोषणा SNIC_FLAGS_NONE			(0)

/* snic module params */
बाह्य अचिन्हित पूर्णांक snic_max_qdepth;

/* snic debugging */
बाह्य अचिन्हित पूर्णांक snic_log_level;

#घोषणा SNIC_MAIN_LOGGING	0x1
#घोषणा SNIC_SCSI_LOGGING	0x2
#घोषणा SNIC_ISR_LOGGING	0x8
#घोषणा SNIC_DESC_LOGGING	0x10

#घोषणा SNIC_CHECK_LOGGING(LEVEL, CMD)		\
करो अणु						\
	अगर (unlikely(snic_log_level & LEVEL))	\
		करो अणु				\
			CMD;			\
		पूर्ण जबतक (0);			\
पूर्ण जबतक (0)

#घोषणा SNIC_MAIN_DBG(host, fmt, args...)	\
	SNIC_CHECK_LOGGING(SNIC_MAIN_LOGGING,		\
		shost_prपूर्णांकk(KERN_INFO, host, fmt, ## args);)

#घोषणा SNIC_SCSI_DBG(host, fmt, args...)	\
	SNIC_CHECK_LOGGING(SNIC_SCSI_LOGGING,		\
		shost_prपूर्णांकk(KERN_INFO, host, fmt, ##args);)

#घोषणा SNIC_DISC_DBG(host, fmt, args...)	\
	SNIC_CHECK_LOGGING(SNIC_SCSI_LOGGING,		\
		shost_prपूर्णांकk(KERN_INFO, host, fmt, ##args);)

#घोषणा SNIC_ISR_DBG(host, fmt, args...)	\
	SNIC_CHECK_LOGGING(SNIC_ISR_LOGGING,		\
		shost_prपूर्णांकk(KERN_INFO, host, fmt, ##args);)

#घोषणा SNIC_HOST_ERR(host, fmt, args...)		\
	shost_prपूर्णांकk(KERN_ERR, host, fmt, ##args)

#घोषणा SNIC_HOST_INFO(host, fmt, args...)		\
	shost_prपूर्णांकk(KERN_INFO, host, fmt, ##args)

#घोषणा SNIC_INFO(fmt, args...)				\
	pr_info(PFX fmt, ## args)

#घोषणा SNIC_DBG(fmt, args...)				\
	pr_info(PFX fmt, ## args)

#घोषणा SNIC_ERR(fmt, args...)				\
	pr_err(PFX fmt, ## args)

#अगर_घोषित DEBUG
#घोषणा SNIC_BUG_ON(EXPR) \
	(अणु \
		अगर (EXPR) अणु \
			SNIC_ERR("SNIC BUG(%s)\n", #EXPR); \
			BUG_ON(EXPR); \
		पूर्ण \
	पूर्ण)
#अन्यथा
#घोषणा SNIC_BUG_ON(EXPR) \
	(अणु \
		अगर (EXPR) अणु \
			SNIC_ERR("SNIC BUG(%s) at %s : %d\n", \
				 #EXPR, __func__, __LINE__); \
			WARN_ON_ONCE(EXPR); \
		पूर्ण \
	पूर्ण)
#पूर्ण_अगर

/* Soft निश्चित */
#घोषणा SNIC_ASSERT_NOT_IMPL(EXPR) \
	(अणु \
		अगर (EXPR) अणु\
			SNIC_INFO("Functionality not impl'ed at %s:%d\n", \
				  __func__, __LINE__); \
			WARN_ON_ONCE(EXPR); \
		पूर्ण \
	 पूर्ण)


बाह्य स्थिर अक्षर *snic_state_str[];

क्रमागत snic_पूर्णांकx_पूर्णांकr_index अणु
	SNIC_INTX_WQ_RQ_COPYWQ,
	SNIC_INTX_ERR,
	SNIC_INTX_NOTIFY,
	SNIC_INTX_INTR_MAX,
पूर्ण;

क्रमागत snic_msix_पूर्णांकr_index अणु
	SNIC_MSIX_WQ,
	SNIC_MSIX_IO_CMPL,
	SNIC_MSIX_ERR_NOTIFY,
	SNIC_MSIX_INTR_MAX,
पूर्ण;

#घोषणा SNIC_INTRHDLR_NAMSZ	(2 * IFNAMSIZ)
काष्ठा snic_msix_entry अणु
	पूर्णांक requested;
	अक्षर devname[SNIC_INTRHDLR_NAMSZ];
	irqवापस_t (*isr)(पूर्णांक, व्योम *);
	व्योम *devid;
पूर्ण;

क्रमागत snic_state अणु
	SNIC_INIT = 0,
	SNIC_ERROR,
	SNIC_ONLINE,
	SNIC_OFFLINE,
	SNIC_FWRESET,
पूर्ण;

#घोषणा SNIC_WQ_MAX		1
#घोषणा SNIC_CQ_IO_CMPL_MAX	1
#घोषणा SNIC_CQ_MAX		(SNIC_WQ_MAX + SNIC_CQ_IO_CMPL_MAX)

/* firmware version inक्रमmation */
काष्ठा snic_fw_info अणु
	u32	fw_ver;
	u32	hid;			/* u16 hid | u16 vnic id */
	u32	max_concur_ios;		/* max concurrent ios */
	u32	max_sgs_per_cmd;	/* max sgls per IO */
	u32	max_io_sz;		/* max io size supported */
	u32	hba_cap;		/* hba capabilities */
	u32	max_tgts;		/* max tgts supported */
	u16	io_पंचांगo;			/* FW Extended समयout */
	काष्ठा completion *रुको;	/* रक्षित by snic lock*/
पूर्ण;

/*
 * snic_work item : defined to process asynchronous events
 */
काष्ठा snic_work अणु
	काष्ठा work_काष्ठा work;
	u16	ev_id;
	u64	*ev_data;
पूर्ण;

/*
 * snic काष्ठाure to represent SCSI vNIC
 */
काष्ठा snic अणु
	/* snic specअगरic members */
	काष्ठा list_head list;
	अक्षर name[IFNAMSIZ];
	atomic_t state;
	spinlock_t snic_lock;
	काष्ठा completion *हटाओ_रुको;
	bool in_हटाओ;
	bool stop_link_events;		/* stop processing link events */

	/* discovery related */
	काष्ठा snic_disc disc;

	/* Scsi Host info */
	काष्ठा Scsi_Host *shost;

	/* vnic related काष्ठाures */
	काष्ठा vnic_dev_bar bar0;

	काष्ठा vnic_stats *stats;
	अचिन्हित दीर्घ stats_समय;
	अचिन्हित दीर्घ stats_reset_समय;

	काष्ठा vnic_dev *vdev;

	/* hw resource info */
	अचिन्हित पूर्णांक wq_count;
	अचिन्हित पूर्णांक cq_count;
	अचिन्हित पूर्णांक पूर्णांकr_count;
	अचिन्हित पूर्णांक err_पूर्णांकr_offset;

	पूर्णांक link_status; /* retrieved from svnic_dev_link_status() */
	u32 link_करोwn_cnt;

	/* pci related */
	काष्ठा pci_dev *pdev;
	काष्ठा snic_msix_entry msix[SNIC_MSIX_INTR_MAX];

	/* io related info */
	mempool_t *req_pool[SNIC_REQ_MAX_CACHES]; /* (??) */
	____cacheline_aligned spinlock_t io_req_lock[SNIC_IO_LOCKS];

	/* Maपूर्णांकain snic specअगरic commands, cmds with no tag in spl_cmd_list */
	____cacheline_aligned spinlock_t spl_cmd_lock;
	काष्ठा list_head spl_cmd_list;

	अचिन्हित पूर्णांक max_tag_id;
	atomic_t ios_inflight;		/* io in flight counter */

	काष्ठा vnic_snic_config config;

	काष्ठा work_काष्ठा link_work;

	/* firmware inक्रमmation */
	काष्ठा snic_fw_info fwinfo;

	/* Work क्रम processing Target related work */
	काष्ठा work_काष्ठा tgt_work;

	/* Work क्रम processing Discovery */
	काष्ठा work_काष्ठा disc_work;

	/* stats related */
	अचिन्हित पूर्णांक reset_stats;
	atomic64_t io_cmpl_skip;
	काष्ठा snic_stats s_stats;	/* Per SNIC driver stats */

	/* platक्रमm specअगरic */
#अगर_घोषित CONFIG_SCSI_SNIC_DEBUG_FS
	काष्ठा dentry *stats_host;	/* Per snic debugfs root */
	काष्ठा dentry *stats_file;	/* Per snic debugfs file */
	काष्ठा dentry *reset_stats_file;/* Per snic reset stats file */
#पूर्ण_अगर

	/* completion queue cache line section */
	____cacheline_aligned काष्ठा vnic_cq cq[SNIC_CQ_MAX];

	/* work queue cache line section */
	____cacheline_aligned काष्ठा vnic_wq wq[SNIC_WQ_MAX];
	spinlock_t wq_lock[SNIC_WQ_MAX];

	/* पूर्णांकerrupt resource cache line section */
	____cacheline_aligned काष्ठा vnic_पूर्णांकr पूर्णांकr[SNIC_MSIX_INTR_MAX];
पूर्ण; /* end of snic काष्ठाure */

/*
 * SNIC Driver's Global Data
 */
काष्ठा snic_global अणु
	काष्ठा list_head snic_list;
	spinlock_t snic_list_lock;

	काष्ठा kmem_cache *req_cache[SNIC_REQ_MAX_CACHES];

	काष्ठा workqueue_काष्ठा *event_q;

#अगर_घोषित CONFIG_SCSI_SNIC_DEBUG_FS
	/* debugfs related global data */
	काष्ठा dentry *trc_root;
	काष्ठा dentry *stats_root;

	काष्ठा snic_trc trc ____cacheline_aligned;
#पूर्ण_अगर
पूर्ण;

बाह्य काष्ठा snic_global *snic_glob;

पूर्णांक snic_glob_init(व्योम);
व्योम snic_glob_cleanup(व्योम);

बाह्य काष्ठा workqueue_काष्ठा *snic_event_queue;
बाह्य काष्ठा device_attribute *snic_attrs[];

पूर्णांक snic_queuecommand(काष्ठा Scsi_Host *, काष्ठा scsi_cmnd *);
पूर्णांक snic_पात_cmd(काष्ठा scsi_cmnd *);
पूर्णांक snic_device_reset(काष्ठा scsi_cmnd *);
पूर्णांक snic_host_reset(काष्ठा scsi_cmnd *);
पूर्णांक snic_reset(काष्ठा Scsi_Host *, काष्ठा scsi_cmnd *);
व्योम snic_shutकरोwn_scsi_cleanup(काष्ठा snic *);


पूर्णांक snic_request_पूर्णांकr(काष्ठा snic *);
व्योम snic_मुक्त_पूर्णांकr(काष्ठा snic *);
पूर्णांक snic_set_पूर्णांकr_mode(काष्ठा snic *);
व्योम snic_clear_पूर्णांकr_mode(काष्ठा snic *);

पूर्णांक snic_fwcq_cmpl_handler(काष्ठा snic *, पूर्णांक);
पूर्णांक snic_wq_cmpl_handler(काष्ठा snic *, पूर्णांक);
व्योम snic_मुक्त_wq_buf(काष्ठा vnic_wq *, काष्ठा vnic_wq_buf *);


व्योम snic_log_q_error(काष्ठा snic *);
व्योम snic_handle_link_event(काष्ठा snic *);
व्योम snic_handle_link(काष्ठा work_काष्ठा *);

पूर्णांक snic_queue_exch_ver_req(काष्ठा snic *);
व्योम snic_io_exch_ver_cmpl_handler(काष्ठा snic *, काष्ठा snic_fw_req *);

पूर्णांक snic_queue_wq_desc(काष्ठा snic *, व्योम *os_buf, u16 len);

व्योम snic_handle_untagged_req(काष्ठा snic *, काष्ठा snic_req_info *);
व्योम snic_release_untagged_req(काष्ठा snic *, काष्ठा snic_req_info *);
व्योम snic_मुक्त_all_untagged_reqs(काष्ठा snic *);
पूर्णांक snic_get_conf(काष्ठा snic *);
व्योम snic_set_state(काष्ठा snic *, क्रमागत snic_state);
पूर्णांक snic_get_state(काष्ठा snic *);
स्थिर अक्षर *snic_state_to_str(अचिन्हित पूर्णांक);
व्योम snic_hex_dump(अक्षर *, अक्षर *, पूर्णांक);
व्योम snic_prपूर्णांक_desc(स्थिर अक्षर *fn, अक्षर *os_buf, पूर्णांक len);
स्थिर अक्षर *show_opcode_name(पूर्णांक val);
#पूर्ण_अगर /* _SNIC_H */
