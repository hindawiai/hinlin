<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2011-2014, Intel Corporation.
 */

#अगर_अघोषित _NVME_H
#घोषणा _NVME_H

#समावेश <linux/nvme.h>
#समावेश <linux/cdev.h>
#समावेश <linux/pci.h>
#समावेश <linux/kref.h>
#समावेश <linux/blk-mq.h>
#समावेश <linux/lightnvm.h>
#समावेश <linux/sed-opal.h>
#समावेश <linux/fault-inject.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/रुको.h>
#समावेश <linux/t10-pi.h>

#समावेश <trace/events/block.h>

बाह्य अचिन्हित पूर्णांक nvme_io_समयout;
#घोषणा NVME_IO_TIMEOUT	(nvme_io_समयout * HZ)

बाह्य अचिन्हित पूर्णांक admin_समयout;
#घोषणा NVME_ADMIN_TIMEOUT	(admin_समयout * HZ)

#घोषणा NVME_DEFAULT_KATO	5

#अगर_घोषित CONFIG_ARCH_NO_SG_CHAIN
#घोषणा  NVME_INLINE_SG_CNT  0
#घोषणा  NVME_INLINE_METADATA_SG_CNT  0
#अन्यथा
#घोषणा  NVME_INLINE_SG_CNT  2
#घोषणा  NVME_INLINE_METADATA_SG_CNT  1
#पूर्ण_अगर

/*
 * Default to a 4K page size, with the पूर्णांकention to update this
 * path in the future to accommodate architectures with dअगरfering
 * kernel and IO page sizes.
 */
#घोषणा NVME_CTRL_PAGE_SHIFT	12
#घोषणा NVME_CTRL_PAGE_SIZE	(1 << NVME_CTRL_PAGE_SHIFT)

बाह्य काष्ठा workqueue_काष्ठा *nvme_wq;
बाह्य काष्ठा workqueue_काष्ठा *nvme_reset_wq;
बाह्य काष्ठा workqueue_काष्ठा *nvme_delete_wq;

क्रमागत अणु
	NVME_NS_LBA		= 0,
	NVME_NS_LIGHTNVM	= 1,
पूर्ण;

/*
 * List of workarounds क्रम devices that required behavior not specअगरied in
 * the standard.
 */
क्रमागत nvme_quirks अणु
	/*
	 * Prefers I/O aligned to a stripe size specअगरied in a venकरोr
	 * specअगरic Identअगरy field.
	 */
	NVME_QUIRK_STRIPE_SIZE			= (1 << 0),

	/*
	 * The controller करोesn't handle Identअगरy value others than 0 or 1
	 * correctly.
	 */
	NVME_QUIRK_IDENTIFY_CNS			= (1 << 1),

	/*
	 * The controller deterministically वापसs O's on पढ़ोs to
	 * logical blocks that deallocate was called on.
	 */
	NVME_QUIRK_DEALLOCATE_ZEROES		= (1 << 2),

	/*
	 * The controller needs a delay beक्रमe starts checking the device
	 * पढ़ोiness, which is करोne by पढ़ोing the NVME_CSTS_RDY bit.
	 */
	NVME_QUIRK_DELAY_BEFORE_CHK_RDY		= (1 << 3),

	/*
	 * APST should not be used.
	 */
	NVME_QUIRK_NO_APST			= (1 << 4),

	/*
	 * The deepest sleep state should not be used.
	 */
	NVME_QUIRK_NO_DEEPEST_PS		= (1 << 5),

	/*
	 * Supports the LighNVM command set अगर indicated in vs[1].
	 */
	NVME_QUIRK_LIGHTNVM			= (1 << 6),

	/*
	 * Set MEDIUM priority on SQ creation
	 */
	NVME_QUIRK_MEDIUM_PRIO_SQ		= (1 << 7),

	/*
	 * Ignore device provided subnqn.
	 */
	NVME_QUIRK_IGNORE_DEV_SUBNQN		= (1 << 8),

	/*
	 * Broken Write Zeroes.
	 */
	NVME_QUIRK_DISABLE_WRITE_ZEROES		= (1 << 9),

	/*
	 * Force simple suspend/resume path.
	 */
	NVME_QUIRK_SIMPLE_SUSPEND		= (1 << 10),

	/*
	 * Use only one पूर्णांकerrupt vector क्रम all queues
	 */
	NVME_QUIRK_SINGLE_VECTOR		= (1 << 11),

	/*
	 * Use non-standard 128 bytes SQEs.
	 */
	NVME_QUIRK_128_BYTES_SQES		= (1 << 12),

	/*
	 * Prevent tag overlap between queues
	 */
	NVME_QUIRK_SHARED_TAGS                  = (1 << 13),

	/*
	 * Don't change the value of the temperature threshold feature
	 */
	NVME_QUIRK_NO_TEMP_THRESH_CHANGE	= (1 << 14),

	/*
	 * The controller करोesn't handle the Identअगरy Namespace
	 * Identअगरication Descriptor list subcommand despite claiming
	 * NVMe 1.3 compliance.
	 */
	NVME_QUIRK_NO_NS_DESC_LIST		= (1 << 15),

	/*
	 * The controller करोes not properly handle DMA addresses over
	 * 48 bits.
	 */
	NVME_QUIRK_DMA_ADDRESS_BITS_48		= (1 << 16),
पूर्ण;

/*
 * Common request काष्ठाure क्रम NVMe passthrough.  All drivers must have
 * this काष्ठाure as the first member of their request-निजी data.
 */
काष्ठा nvme_request अणु
	काष्ठा nvme_command	*cmd;
	जोड़ nvme_result	result;
	u8			retries;
	u8			flags;
	u16			status;
	काष्ठा nvme_ctrl	*ctrl;
पूर्ण;

/*
 * Mark a bio as coming in through the mpath node.
 */
#घोषणा REQ_NVME_MPATH		REQ_DRV

क्रमागत अणु
	NVME_REQ_CANCELLED		= (1 << 0),
	NVME_REQ_USERCMD		= (1 << 1),
पूर्ण;

अटल अंतरभूत काष्ठा nvme_request *nvme_req(काष्ठा request *req)
अणु
	वापस blk_mq_rq_to_pdu(req);
पूर्ण

अटल अंतरभूत u16 nvme_req_qid(काष्ठा request *req)
अणु
	अगर (!req->q->queuedata)
		वापस 0;

	वापस req->mq_hctx->queue_num + 1;
पूर्ण

/* The below value is the specअगरic amount of delay needed beक्रमe checking
 * पढ़ोiness in हाल of the PCI_DEVICE(0x1c58, 0x0003), which needs the
 * NVME_QUIRK_DELAY_BEFORE_CHK_RDY quirk enabled. The value (in ms) was
 * found empirically.
 */
#घोषणा NVME_QUIRK_DELAY_AMOUNT		2300

/*
 * क्रमागत nvme_ctrl_state: Controller state
 *
 * @NVME_CTRL_NEW:		New controller just allocated, initial state
 * @NVME_CTRL_LIVE:		Controller is connected and I/O capable
 * @NVME_CTRL_RESETTING:	Controller is resetting (or scheduled reset)
 * @NVME_CTRL_CONNECTING:	Controller is disconnected, now connecting the
 *				transport
 * @NVME_CTRL_DELETING:		Controller is deleting (or scheduled deletion)
 * @NVME_CTRL_DELETING_NOIO:	Controller is deleting and I/O is not
 *				disabled/failed immediately. This state comes
 * 				after all async event processing took place and
 * 				beक्रमe ns removal and the controller deletion
 * 				progress
 * @NVME_CTRL_DEAD:		Controller is non-present/unresponsive during
 *				shutकरोwn or removal. In this हाल we क्रमcibly
 *				समाप्त all inflight I/O as they have no chance to
 *				complete
 */
क्रमागत nvme_ctrl_state अणु
	NVME_CTRL_NEW,
	NVME_CTRL_LIVE,
	NVME_CTRL_RESETTING,
	NVME_CTRL_CONNECTING,
	NVME_CTRL_DELETING,
	NVME_CTRL_DELETING_NOIO,
	NVME_CTRL_DEAD,
पूर्ण;

काष्ठा nvme_fault_inject अणु
#अगर_घोषित CONFIG_FAULT_INJECTION_DEBUG_FS
	काष्ठा fault_attr attr;
	काष्ठा dentry *parent;
	bool करोnt_retry;	/* DNR, करो not retry */
	u16 status;		/* status code */
#पूर्ण_अगर
पूर्ण;

काष्ठा nvme_ctrl अणु
	bool comp_seen;
	क्रमागत nvme_ctrl_state state;
	bool identअगरied;
	spinlock_t lock;
	काष्ठा mutex scan_lock;
	स्थिर काष्ठा nvme_ctrl_ops *ops;
	काष्ठा request_queue *admin_q;
	काष्ठा request_queue *connect_q;
	काष्ठा request_queue *fabrics_q;
	काष्ठा device *dev;
	पूर्णांक instance;
	पूर्णांक numa_node;
	काष्ठा blk_mq_tag_set *tagset;
	काष्ठा blk_mq_tag_set *admin_tagset;
	काष्ठा list_head namespaces;
	काष्ठा rw_semaphore namespaces_rwsem;
	काष्ठा device ctrl_device;
	काष्ठा device *device;	/* अक्षर device */
#अगर_घोषित CONFIG_NVME_HWMON
	काष्ठा device *hwmon_device;
#पूर्ण_अगर
	काष्ठा cdev cdev;
	काष्ठा work_काष्ठा reset_work;
	काष्ठा work_काष्ठा delete_work;
	रुको_queue_head_t state_wq;

	काष्ठा nvme_subप्रणाली *subsys;
	काष्ठा list_head subsys_entry;

	काष्ठा opal_dev *opal_dev;

	अक्षर name[12];
	u16 cntlid;

	u32 ctrl_config;
	u16 mtfa;
	u32 queue_count;

	u64 cap;
	u32 max_hw_sectors;
	u32 max_segments;
	u32 max_पूर्णांकegrity_segments;
	u32 max_discard_sectors;
	u32 max_discard_segments;
	u32 max_zeroes_sectors;
#अगर_घोषित CONFIG_BLK_DEV_ZONED
	u32 max_zone_append;
#पूर्ण_अगर
	u16 crdt[3];
	u16 oncs;
	u16 oacs;
	u16 nssa;
	u16 nr_streams;
	u16 sqsize;
	u32 max_namespaces;
	atomic_t पात_limit;
	u8 vwc;
	u32 vs;
	u32 sgls;
	u16 kas;
	u8 npss;
	u8 apsta;
	u16 wctemp;
	u16 cctemp;
	u32 oaes;
	u32 aen_result;
	u32 ctratt;
	अचिन्हित पूर्णांक shutकरोwn_समयout;
	अचिन्हित पूर्णांक kato;
	bool subप्रणाली;
	अचिन्हित दीर्घ quirks;
	काष्ठा nvme_id_घातer_state psd[32];
	काष्ठा nvme_effects_log *effects;
	काष्ठा xarray cels;
	काष्ठा work_काष्ठा scan_work;
	काष्ठा work_काष्ठा async_event_work;
	काष्ठा delayed_work ka_work;
	काष्ठा delayed_work failfast_work;
	काष्ठा nvme_command ka_cmd;
	काष्ठा work_काष्ठा fw_act_work;
	अचिन्हित दीर्घ events;

#अगर_घोषित CONFIG_NVME_MULTIPATH
	/* asymmetric namespace access: */
	u8 anacap;
	u8 anatt;
	u32 anagrpmax;
	u32 nanagrpid;
	काष्ठा mutex ana_lock;
	काष्ठा nvme_ana_rsp_hdr *ana_log_buf;
	माप_प्रकार ana_log_size;
	काष्ठा समयr_list anatt_समयr;
	काष्ठा work_काष्ठा ana_work;
#पूर्ण_अगर

	/* Power saving configuration */
	u64 ps_max_latency_us;
	bool apst_enabled;

	/* PCIe only: */
	u32 hmpre;
	u32 hmmin;
	u32 hmminds;
	u16 hmmaxd;

	/* Fabrics only */
	u32 ioccsz;
	u32 iorcsz;
	u16 icकरोff;
	u16 maxcmd;
	पूर्णांक nr_reconnects;
	अचिन्हित दीर्घ flags;
#घोषणा NVME_CTRL_FAILFAST_EXPIRED	0
	काष्ठा nvmf_ctrl_options *opts;

	काष्ठा page *discard_page;
	अचिन्हित दीर्घ discard_page_busy;

	काष्ठा nvme_fault_inject fault_inject;
पूर्ण;

क्रमागत nvme_iopolicy अणु
	NVME_IOPOLICY_NUMA,
	NVME_IOPOLICY_RR,
पूर्ण;

काष्ठा nvme_subप्रणाली अणु
	पूर्णांक			instance;
	काष्ठा device		dev;
	/*
	 * Because we unरेजिस्टर the device on the last put we need
	 * a separate refcount.
	 */
	काष्ठा kref		ref;
	काष्ठा list_head	entry;
	काष्ठा mutex		lock;
	काष्ठा list_head	ctrls;
	काष्ठा list_head	nsheads;
	अक्षर			subnqn[NVMF_NQN_SIZE];
	अक्षर			serial[20];
	अक्षर			model[40];
	अक्षर			firmware_rev[8];
	u8			cmic;
	u16			venकरोr_id;
	u16			awupf;	/* 0's based awupf value. */
	काष्ठा ida		ns_ida;
#अगर_घोषित CONFIG_NVME_MULTIPATH
	क्रमागत nvme_iopolicy	iopolicy;
#पूर्ण_अगर
पूर्ण;

/*
 * Container काष्ठाure क्रम uniqueue namespace identअगरiers.
 */
काष्ठा nvme_ns_ids अणु
	u8	eui64[8];
	u8	nguid[16];
	uuid_t	uuid;
	u8	csi;
पूर्ण;

/*
 * Anchor काष्ठाure क्रम namespaces.  There is one क्रम each namespace in a
 * NVMe subप्रणाली that any of our controllers can see, and the namespace
 * काष्ठाure क्रम each controller is chained of it.  For निजी namespaces
 * there is a 1:1 relation to our namespace काष्ठाures, that is ->list
 * only ever has a single entry क्रम निजी namespaces.
 */
काष्ठा nvme_ns_head अणु
	काष्ठा list_head	list;
	काष्ठा srcu_काष्ठा      srcu;
	काष्ठा nvme_subप्रणाली	*subsys;
	अचिन्हित		ns_id;
	काष्ठा nvme_ns_ids	ids;
	काष्ठा list_head	entry;
	काष्ठा kref		ref;
	bool			shared;
	पूर्णांक			instance;
	काष्ठा nvme_effects_log *effects;

	काष्ठा cdev		cdev;
	काष्ठा device		cdev_device;

	काष्ठा gendisk		*disk;
#अगर_घोषित CONFIG_NVME_MULTIPATH
	काष्ठा bio_list		requeue_list;
	spinlock_t		requeue_lock;
	काष्ठा work_काष्ठा	requeue_work;
	काष्ठा mutex		lock;
	अचिन्हित दीर्घ		flags;
#घोषणा NVME_NSHEAD_DISK_LIVE	0
	काष्ठा nvme_ns __rcu	*current_path[];
#पूर्ण_अगर
पूर्ण;

अटल अंतरभूत bool nvme_ns_head_multipath(काष्ठा nvme_ns_head *head)
अणु
	वापस IS_ENABLED(CONFIG_NVME_MULTIPATH) && head->disk;
पूर्ण

क्रमागत nvme_ns_features अणु
	NVME_NS_EXT_LBAS = 1 << 0, /* support extended LBA क्रमmat */
	NVME_NS_METADATA_SUPPORTED = 1 << 1, /* support getting generated md */
पूर्ण;

काष्ठा nvme_ns अणु
	काष्ठा list_head list;

	काष्ठा nvme_ctrl *ctrl;
	काष्ठा request_queue *queue;
	काष्ठा gendisk *disk;
#अगर_घोषित CONFIG_NVME_MULTIPATH
	क्रमागत nvme_ana_state ana_state;
	u32 ana_grpid;
#पूर्ण_अगर
	काष्ठा list_head siblings;
	काष्ठा nvm_dev *ndev;
	काष्ठा kref kref;
	काष्ठा nvme_ns_head *head;

	पूर्णांक lba_shअगरt;
	u16 ms;
	u16 sgs;
	u32 sws;
	u8 pi_type;
#अगर_घोषित CONFIG_BLK_DEV_ZONED
	u64 zsze;
#पूर्ण_अगर
	अचिन्हित दीर्घ features;
	अचिन्हित दीर्घ flags;
#घोषणा NVME_NS_REMOVING	0
#घोषणा NVME_NS_DEAD     	1
#घोषणा NVME_NS_ANA_PENDING	2
#घोषणा NVME_NS_FORCE_RO	3

	काष्ठा cdev		cdev;
	काष्ठा device		cdev_device;

	काष्ठा nvme_fault_inject fault_inject;

पूर्ण;

/* NVMe ns supports metadata actions by the controller (generate/strip) */
अटल अंतरभूत bool nvme_ns_has_pi(काष्ठा nvme_ns *ns)
अणु
	वापस ns->pi_type && ns->ms == माप(काष्ठा t10_pi_tuple);
पूर्ण

काष्ठा nvme_ctrl_ops अणु
	स्थिर अक्षर *name;
	काष्ठा module *module;
	अचिन्हित पूर्णांक flags;
#घोषणा NVME_F_FABRICS			(1 << 0)
#घोषणा NVME_F_METADATA_SUPPORTED	(1 << 1)
#घोषणा NVME_F_PCI_P2PDMA		(1 << 2)
	पूर्णांक (*reg_पढ़ो32)(काष्ठा nvme_ctrl *ctrl, u32 off, u32 *val);
	पूर्णांक (*reg_ग_लिखो32)(काष्ठा nvme_ctrl *ctrl, u32 off, u32 val);
	पूर्णांक (*reg_पढ़ो64)(काष्ठा nvme_ctrl *ctrl, u32 off, u64 *val);
	व्योम (*मुक्त_ctrl)(काष्ठा nvme_ctrl *ctrl);
	व्योम (*submit_async_event)(काष्ठा nvme_ctrl *ctrl);
	व्योम (*delete_ctrl)(काष्ठा nvme_ctrl *ctrl);
	पूर्णांक (*get_address)(काष्ठा nvme_ctrl *ctrl, अक्षर *buf, पूर्णांक size);
पूर्ण;

#अगर_घोषित CONFIG_FAULT_INJECTION_DEBUG_FS
व्योम nvme_fault_inject_init(काष्ठा nvme_fault_inject *fault_inj,
			    स्थिर अक्षर *dev_name);
व्योम nvme_fault_inject_fini(काष्ठा nvme_fault_inject *fault_inject);
व्योम nvme_should_fail(काष्ठा request *req);
#अन्यथा
अटल अंतरभूत व्योम nvme_fault_inject_init(काष्ठा nvme_fault_inject *fault_inj,
					  स्थिर अक्षर *dev_name)
अणु
पूर्ण
अटल अंतरभूत व्योम nvme_fault_inject_fini(काष्ठा nvme_fault_inject *fault_inj)
अणु
पूर्ण
अटल अंतरभूत व्योम nvme_should_fail(काष्ठा request *req) अणुपूर्ण
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक nvme_reset_subप्रणाली(काष्ठा nvme_ctrl *ctrl)
अणु
	अगर (!ctrl->subप्रणाली)
		वापस -ENOTTY;
	वापस ctrl->ops->reg_ग_लिखो32(ctrl, NVME_REG_NSSR, 0x4E564D65);
पूर्ण

/*
 * Convert a 512B sector number to a device logical block number.
 */
अटल अंतरभूत u64 nvme_sect_to_lba(काष्ठा nvme_ns *ns, sector_t sector)
अणु
	वापस sector >> (ns->lba_shअगरt - SECTOR_SHIFT);
पूर्ण

/*
 * Convert a device logical block number to a 512B sector number.
 */
अटल अंतरभूत sector_t nvme_lba_to_sect(काष्ठा nvme_ns *ns, u64 lba)
अणु
	वापस lba << (ns->lba_shअगरt - SECTOR_SHIFT);
पूर्ण

/*
 * Convert byte length to nvme's 0-based num dwords
 */
अटल अंतरभूत u32 nvme_bytes_to_numd(माप_प्रकार len)
अणु
	वापस (len >> 2) - 1;
पूर्ण

अटल अंतरभूत bool nvme_is_ana_error(u16 status)
अणु
	चयन (status & 0x7ff) अणु
	हाल NVME_SC_ANA_TRANSITION:
	हाल NVME_SC_ANA_INACCESSIBLE:
	हाल NVME_SC_ANA_PERSISTENT_LOSS:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल अंतरभूत bool nvme_is_path_error(u16 status)
अणु
	/* check क्रम a status code type of 'path related status' */
	वापस (status & 0x700) == 0x300;
पूर्ण

/*
 * Fill in the status and result inक्रमmation from the CQE, and then figure out
 * अगर blk-mq will need to use IPI magic to complete the request, and अगर yes करो
 * so.  If not let the caller complete the request without an indirect function
 * call.
 */
अटल अंतरभूत bool nvme_try_complete_req(काष्ठा request *req, __le16 status,
		जोड़ nvme_result result)
अणु
	काष्ठा nvme_request *rq = nvme_req(req);

	rq->status = le16_to_cpu(status) >> 1;
	rq->result = result;
	/* inject error when permitted by fault injection framework */
	nvme_should_fail(req);
	अगर (unlikely(blk_should_fake_समयout(req->q)))
		वापस true;
	वापस blk_mq_complete_request_remote(req);
पूर्ण

अटल अंतरभूत व्योम nvme_get_ctrl(काष्ठा nvme_ctrl *ctrl)
अणु
	get_device(ctrl->device);
पूर्ण

अटल अंतरभूत व्योम nvme_put_ctrl(काष्ठा nvme_ctrl *ctrl)
अणु
	put_device(ctrl->device);
पूर्ण

अटल अंतरभूत bool nvme_is_aen_req(u16 qid, __u16 command_id)
अणु
	वापस !qid && command_id >= NVME_AQ_BLK_MQ_DEPTH;
पूर्ण

व्योम nvme_complete_rq(काष्ठा request *req);
blk_status_t nvme_host_path_error(काष्ठा request *req);
bool nvme_cancel_request(काष्ठा request *req, व्योम *data, bool reserved);
व्योम nvme_cancel_tagset(काष्ठा nvme_ctrl *ctrl);
व्योम nvme_cancel_admin_tagset(काष्ठा nvme_ctrl *ctrl);
bool nvme_change_ctrl_state(काष्ठा nvme_ctrl *ctrl,
		क्रमागत nvme_ctrl_state new_state);
bool nvme_रुको_reset(काष्ठा nvme_ctrl *ctrl);
पूर्णांक nvme_disable_ctrl(काष्ठा nvme_ctrl *ctrl);
पूर्णांक nvme_enable_ctrl(काष्ठा nvme_ctrl *ctrl);
पूर्णांक nvme_shutकरोwn_ctrl(काष्ठा nvme_ctrl *ctrl);
पूर्णांक nvme_init_ctrl(काष्ठा nvme_ctrl *ctrl, काष्ठा device *dev,
		स्थिर काष्ठा nvme_ctrl_ops *ops, अचिन्हित दीर्घ quirks);
व्योम nvme_uninit_ctrl(काष्ठा nvme_ctrl *ctrl);
व्योम nvme_start_ctrl(काष्ठा nvme_ctrl *ctrl);
व्योम nvme_stop_ctrl(काष्ठा nvme_ctrl *ctrl);
पूर्णांक nvme_init_ctrl_finish(काष्ठा nvme_ctrl *ctrl);

व्योम nvme_हटाओ_namespaces(काष्ठा nvme_ctrl *ctrl);

पूर्णांक nvme_sec_submit(व्योम *data, u16 spsp, u8 secp, व्योम *buffer, माप_प्रकार len,
		bool send);

व्योम nvme_complete_async_event(काष्ठा nvme_ctrl *ctrl, __le16 status,
		अस्थिर जोड़ nvme_result *res);

व्योम nvme_stop_queues(काष्ठा nvme_ctrl *ctrl);
व्योम nvme_start_queues(काष्ठा nvme_ctrl *ctrl);
व्योम nvme_समाप्त_queues(काष्ठा nvme_ctrl *ctrl);
व्योम nvme_sync_queues(काष्ठा nvme_ctrl *ctrl);
व्योम nvme_sync_io_queues(काष्ठा nvme_ctrl *ctrl);
व्योम nvme_unमुक्तze(काष्ठा nvme_ctrl *ctrl);
व्योम nvme_रुको_मुक्तze(काष्ठा nvme_ctrl *ctrl);
पूर्णांक nvme_रुको_मुक्तze_समयout(काष्ठा nvme_ctrl *ctrl, दीर्घ समयout);
व्योम nvme_start_मुक्तze(काष्ठा nvme_ctrl *ctrl);

#घोषणा NVME_QID_ANY -1
काष्ठा request *nvme_alloc_request(काष्ठा request_queue *q,
		काष्ठा nvme_command *cmd, blk_mq_req_flags_t flags);
व्योम nvme_cleanup_cmd(काष्ठा request *req);
blk_status_t nvme_setup_cmd(काष्ठा nvme_ns *ns, काष्ठा request *req);
blk_status_t nvme_fail_nonपढ़ोy_command(काष्ठा nvme_ctrl *ctrl,
		काष्ठा request *req);
bool __nvme_check_पढ़ोy(काष्ठा nvme_ctrl *ctrl, काष्ठा request *rq,
		bool queue_live);

अटल अंतरभूत bool nvme_check_पढ़ोy(काष्ठा nvme_ctrl *ctrl, काष्ठा request *rq,
		bool queue_live)
अणु
	अगर (likely(ctrl->state == NVME_CTRL_LIVE))
		वापस true;
	अगर (ctrl->ops->flags & NVME_F_FABRICS &&
	    ctrl->state == NVME_CTRL_DELETING)
		वापस true;
	वापस __nvme_check_पढ़ोy(ctrl, rq, queue_live);
पूर्ण
पूर्णांक nvme_submit_sync_cmd(काष्ठा request_queue *q, काष्ठा nvme_command *cmd,
		व्योम *buf, अचिन्हित bufflen);
पूर्णांक __nvme_submit_sync_cmd(काष्ठा request_queue *q, काष्ठा nvme_command *cmd,
		जोड़ nvme_result *result, व्योम *buffer, अचिन्हित bufflen,
		अचिन्हित समयout, पूर्णांक qid, पूर्णांक at_head,
		blk_mq_req_flags_t flags, bool poll);
पूर्णांक nvme_set_features(काष्ठा nvme_ctrl *dev, अचिन्हित पूर्णांक fid,
		      अचिन्हित पूर्णांक dword11, व्योम *buffer, माप_प्रकार buflen,
		      u32 *result);
पूर्णांक nvme_get_features(काष्ठा nvme_ctrl *dev, अचिन्हित पूर्णांक fid,
		      अचिन्हित पूर्णांक dword11, व्योम *buffer, माप_प्रकार buflen,
		      u32 *result);
पूर्णांक nvme_set_queue_count(काष्ठा nvme_ctrl *ctrl, पूर्णांक *count);
व्योम nvme_stop_keep_alive(काष्ठा nvme_ctrl *ctrl);
पूर्णांक nvme_reset_ctrl(काष्ठा nvme_ctrl *ctrl);
पूर्णांक nvme_reset_ctrl_sync(काष्ठा nvme_ctrl *ctrl);
पूर्णांक nvme_try_sched_reset(काष्ठा nvme_ctrl *ctrl);
पूर्णांक nvme_delete_ctrl(काष्ठा nvme_ctrl *ctrl);
व्योम nvme_queue_scan(काष्ठा nvme_ctrl *ctrl);
पूर्णांक nvme_get_log(काष्ठा nvme_ctrl *ctrl, u32 nsid, u8 log_page, u8 lsp, u8 csi,
		व्योम *log, माप_प्रकार size, u64 offset);
काष्ठा nvme_ns *nvme_get_ns_from_disk(काष्ठा gendisk *disk,
		काष्ठा nvme_ns_head **head, पूर्णांक *srcu_idx);
व्योम nvme_put_ns_from_disk(काष्ठा nvme_ns_head *head, पूर्णांक idx);
bool nvme_tryget_ns_head(काष्ठा nvme_ns_head *head);
व्योम nvme_put_ns_head(काष्ठा nvme_ns_head *head);
पूर्णांक nvme_cdev_add(काष्ठा cdev *cdev, काष्ठा device *cdev_device,
		स्थिर काष्ठा file_operations *fops, काष्ठा module *owner);
व्योम nvme_cdev_del(काष्ठा cdev *cdev, काष्ठा device *cdev_device);
पूर्णांक nvme_ioctl(काष्ठा block_device *bdev, भ_शेषe_t mode,
		अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
दीर्घ nvme_ns_chr_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
पूर्णांक nvme_ns_head_ioctl(काष्ठा block_device *bdev, भ_शेषe_t mode,
		अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
दीर्घ nvme_ns_head_chr_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
		अचिन्हित दीर्घ arg);
दीर्घ nvme_dev_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
		अचिन्हित दीर्घ arg);
पूर्णांक nvme_getgeo(काष्ठा block_device *bdev, काष्ठा hd_geometry *geo);

बाह्य स्थिर काष्ठा attribute_group *nvme_ns_id_attr_groups[];
बाह्य स्थिर काष्ठा pr_ops nvme_pr_ops;
बाह्य स्थिर काष्ठा block_device_operations nvme_ns_head_ops;

#अगर_घोषित CONFIG_NVME_MULTIPATH
अटल अंतरभूत bool nvme_ctrl_use_ana(काष्ठा nvme_ctrl *ctrl)
अणु
	वापस ctrl->ana_log_buf != शून्य;
पूर्ण

व्योम nvme_mpath_unमुक्तze(काष्ठा nvme_subप्रणाली *subsys);
व्योम nvme_mpath_रुको_मुक्तze(काष्ठा nvme_subप्रणाली *subsys);
व्योम nvme_mpath_start_मुक्तze(काष्ठा nvme_subप्रणाली *subsys);
bool nvme_mpath_set_disk_name(काष्ठा nvme_ns *ns, अक्षर *disk_name, पूर्णांक *flags);
व्योम nvme_failover_req(काष्ठा request *req);
व्योम nvme_kick_requeue_lists(काष्ठा nvme_ctrl *ctrl);
पूर्णांक nvme_mpath_alloc_disk(काष्ठा nvme_ctrl *ctrl,काष्ठा nvme_ns_head *head);
व्योम nvme_mpath_add_disk(काष्ठा nvme_ns *ns, काष्ठा nvme_id_ns *id);
व्योम nvme_mpath_हटाओ_disk(काष्ठा nvme_ns_head *head);
पूर्णांक nvme_mpath_init_identअगरy(काष्ठा nvme_ctrl *ctrl, काष्ठा nvme_id_ctrl *id);
व्योम nvme_mpath_init_ctrl(काष्ठा nvme_ctrl *ctrl);
व्योम nvme_mpath_uninit(काष्ठा nvme_ctrl *ctrl);
व्योम nvme_mpath_stop(काष्ठा nvme_ctrl *ctrl);
bool nvme_mpath_clear_current_path(काष्ठा nvme_ns *ns);
व्योम nvme_mpath_clear_ctrl_paths(काष्ठा nvme_ctrl *ctrl);
काष्ठा nvme_ns *nvme_find_path(काष्ठा nvme_ns_head *head);

अटल अंतरभूत व्योम nvme_mpath_check_last_path(काष्ठा nvme_ns *ns)
अणु
	काष्ठा nvme_ns_head *head = ns->head;

	अगर (head->disk && list_empty(&head->list))
		kblockd_schedule_work(&head->requeue_work);
पूर्ण

अटल अंतरभूत व्योम nvme_trace_bio_complete(काष्ठा request *req)
अणु
	काष्ठा nvme_ns *ns = req->q->queuedata;

	अगर (req->cmd_flags & REQ_NVME_MPATH)
		trace_block_bio_complete(ns->head->disk->queue, req->bio);
पूर्ण

बाह्य काष्ठा device_attribute dev_attr_ana_grpid;
बाह्य काष्ठा device_attribute dev_attr_ana_state;
बाह्य काष्ठा device_attribute subsys_attr_iopolicy;

#अन्यथा
अटल अंतरभूत bool nvme_ctrl_use_ana(काष्ठा nvme_ctrl *ctrl)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत bool nvme_mpath_set_disk_name(काष्ठा nvme_ns *ns, अक्षर *disk_name,
		पूर्णांक *flags)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत व्योम nvme_failover_req(काष्ठा request *req)
अणु
पूर्ण
अटल अंतरभूत व्योम nvme_kick_requeue_lists(काष्ठा nvme_ctrl *ctrl)
अणु
पूर्ण
अटल अंतरभूत पूर्णांक nvme_mpath_alloc_disk(काष्ठा nvme_ctrl *ctrl,
		काष्ठा nvme_ns_head *head)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम nvme_mpath_add_disk(काष्ठा nvme_ns *ns,
		काष्ठा nvme_id_ns *id)
अणु
पूर्ण
अटल अंतरभूत व्योम nvme_mpath_हटाओ_disk(काष्ठा nvme_ns_head *head)
अणु
पूर्ण
अटल अंतरभूत bool nvme_mpath_clear_current_path(काष्ठा nvme_ns *ns)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत व्योम nvme_mpath_clear_ctrl_paths(काष्ठा nvme_ctrl *ctrl)
अणु
पूर्ण
अटल अंतरभूत व्योम nvme_mpath_check_last_path(काष्ठा nvme_ns *ns)
अणु
पूर्ण
अटल अंतरभूत व्योम nvme_trace_bio_complete(काष्ठा request *req)
अणु
पूर्ण
अटल अंतरभूत व्योम nvme_mpath_init_ctrl(काष्ठा nvme_ctrl *ctrl)
अणु
पूर्ण
अटल अंतरभूत पूर्णांक nvme_mpath_init_identअगरy(काष्ठा nvme_ctrl *ctrl,
		काष्ठा nvme_id_ctrl *id)
अणु
	अगर (ctrl->subsys->cmic & NVME_CTRL_CMIC_ANA)
		dev_warn(ctrl->device,
"Please enable CONFIG_NVME_MULTIPATH for full support of multi-port devices.\n");
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम nvme_mpath_uninit(काष्ठा nvme_ctrl *ctrl)
अणु
पूर्ण
अटल अंतरभूत व्योम nvme_mpath_stop(काष्ठा nvme_ctrl *ctrl)
अणु
पूर्ण
अटल अंतरभूत व्योम nvme_mpath_unमुक्तze(काष्ठा nvme_subप्रणाली *subsys)
अणु
पूर्ण
अटल अंतरभूत व्योम nvme_mpath_रुको_मुक्तze(काष्ठा nvme_subप्रणाली *subsys)
अणु
पूर्ण
अटल अंतरभूत व्योम nvme_mpath_start_मुक्तze(काष्ठा nvme_subप्रणाली *subsys)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_NVME_MULTIPATH */

पूर्णांक nvme_revalidate_zones(काष्ठा nvme_ns *ns);
#अगर_घोषित CONFIG_BLK_DEV_ZONED
पूर्णांक nvme_update_zone_info(काष्ठा nvme_ns *ns, अचिन्हित lbaf);
पूर्णांक nvme_report_zones(काष्ठा gendisk *disk, sector_t sector,
		      अचिन्हित पूर्णांक nr_zones, report_zones_cb cb, व्योम *data);

blk_status_t nvme_setup_zone_mgmt_send(काष्ठा nvme_ns *ns, काष्ठा request *req,
				       काष्ठा nvme_command *cmnd,
				       क्रमागत nvme_zone_mgmt_action action);
#अन्यथा
#घोषणा nvme_report_zones शून्य

अटल अंतरभूत blk_status_t nvme_setup_zone_mgmt_send(काष्ठा nvme_ns *ns,
		काष्ठा request *req, काष्ठा nvme_command *cmnd,
		क्रमागत nvme_zone_mgmt_action action)
अणु
	वापस BLK_STS_NOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक nvme_update_zone_info(काष्ठा nvme_ns *ns, अचिन्हित lbaf)
अणु
	dev_warn(ns->ctrl->device,
		 "Please enable CONFIG_BLK_DEV_ZONED to support ZNS devices\n");
	वापस -EPROTONOSUPPORT;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_NVM
पूर्णांक nvme_nvm_रेजिस्टर(काष्ठा nvme_ns *ns, अक्षर *disk_name, पूर्णांक node);
व्योम nvme_nvm_unरेजिस्टर(काष्ठा nvme_ns *ns);
बाह्य स्थिर काष्ठा attribute_group nvme_nvm_attr_group;
पूर्णांक nvme_nvm_ioctl(काष्ठा nvme_ns *ns, अचिन्हित पूर्णांक cmd, व्योम __user *argp);
#अन्यथा
अटल अंतरभूत पूर्णांक nvme_nvm_रेजिस्टर(काष्ठा nvme_ns *ns, अक्षर *disk_name,
				    पूर्णांक node)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम nvme_nvm_unरेजिस्टर(काष्ठा nvme_ns *ns) अणुपूर्ण;
अटल अंतरभूत पूर्णांक nvme_nvm_ioctl(काष्ठा nvme_ns *ns, अचिन्हित पूर्णांक cmd,
		व्योम __user *argp)
अणु
	वापस -ENOTTY;
पूर्ण
#पूर्ण_अगर /* CONFIG_NVM */

अटल अंतरभूत काष्ठा nvme_ns *nvme_get_ns_from_dev(काष्ठा device *dev)
अणु
	वापस dev_to_disk(dev)->निजी_data;
पूर्ण

#अगर_घोषित CONFIG_NVME_HWMON
पूर्णांक nvme_hwmon_init(काष्ठा nvme_ctrl *ctrl);
व्योम nvme_hwmon_निकास(काष्ठा nvme_ctrl *ctrl);
#अन्यथा
अटल अंतरभूत पूर्णांक nvme_hwmon_init(काष्ठा nvme_ctrl *ctrl)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम nvme_hwmon_निकास(काष्ठा nvme_ctrl *ctrl)
अणु
पूर्ण
#पूर्ण_अगर

u32 nvme_command_effects(काष्ठा nvme_ctrl *ctrl, काष्ठा nvme_ns *ns,
			 u8 opcode);
व्योम nvme_execute_passthru_rq(काष्ठा request *rq);
काष्ठा nvme_ctrl *nvme_ctrl_from_file(काष्ठा file *file);
काष्ठा nvme_ns *nvme_find_get_ns(काष्ठा nvme_ctrl *ctrl, अचिन्हित nsid);
व्योम nvme_put_ns(काष्ठा nvme_ns *ns);

#पूर्ण_अगर /* _NVME_H */
