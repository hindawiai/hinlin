<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * CXL Flash Device Driver
 *
 * Written by: Manoj N. Kumar <manoj@linux.vnet.ibm.com>, IBM Corporation
 *             Matthew R. Ochs <mrochs@linux.vnet.ibm.com>, IBM Corporation
 *
 * Copyright (C) 2015 IBM Corporation
 */

#अगर_अघोषित _CXLFLASH_COMMON_H
#घोषणा _CXLFLASH_COMMON_H

#समावेश <linux/async.h>
#समावेश <linux/cdev.h>
#समावेश <linux/irq_poll.h>
#समावेश <linux/list.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/types.h>
#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>

#समावेश "backend.h"

बाह्य स्थिर काष्ठा file_operations cxlflash_cxl_fops;

#घोषणा MAX_CONTEXT	CXLFLASH_MAX_CONTEXT	/* num contexts per afu */
#घोषणा MAX_FC_PORTS	CXLFLASH_MAX_FC_PORTS	/* max ports per AFU */
#घोषणा LEGACY_FC_PORTS	2			/* legacy ports per AFU */

#घोषणा CHAN2PORTBANK(_x)	((_x) >> ilog2(CXLFLASH_NUM_FC_PORTS_PER_BANK))
#घोषणा CHAN2BANKPORT(_x)	((_x) & (CXLFLASH_NUM_FC_PORTS_PER_BANK - 1))

#घोषणा CHAN2PORTMASK(_x)	(1 << (_x))	/* channel to port mask */
#घोषणा PORTMASK2CHAN(_x)	(ilog2((_x)))	/* port mask to channel */
#घोषणा PORTNUM2CHAN(_x)	((_x) - 1)	/* port number to channel */

#घोषणा CXLFLASH_BLOCK_SIZE	4096		/* 4K blocks */
#घोषणा CXLFLASH_MAX_XFER_SIZE	16777216	/* 16MB transfer */
#घोषणा CXLFLASH_MAX_SECTORS	(CXLFLASH_MAX_XFER_SIZE/512)	/* SCSI wants
								 * max_sectors
								 * in units of
								 * 512 byte
								 * sectors
								 */

#घोषणा MAX_RHT_PER_CONTEXT (PAGE_SIZE / माप(काष्ठा sisl_rht_entry))

/* AFU command retry limit */
#घोषणा MC_RETRY_CNT	5	/* Sufficient क्रम SCSI and certain AFU errors */

/* Command management definitions */
#घोषणा CXLFLASH_MAX_CMDS               256
#घोषणा CXLFLASH_MAX_CMDS_PER_LUN       CXLFLASH_MAX_CMDS

/* RRQ क्रम master issued cmds */
#घोषणा NUM_RRQ_ENTRY                   CXLFLASH_MAX_CMDS

/* SQ क्रम master issued cmds */
#घोषणा NUM_SQ_ENTRY			CXLFLASH_MAX_CMDS

/* Hardware queue definitions */
#घोषणा CXLFLASH_DEF_HWQS		1
#घोषणा CXLFLASH_MAX_HWQS		8
#घोषणा PRIMARY_HWQ			0


अटल अंतरभूत व्योम check_sizes(व्योम)
अणु
	BUILD_BUG_ON_NOT_POWER_OF_2(CXLFLASH_NUM_FC_PORTS_PER_BANK);
	BUILD_BUG_ON_NOT_POWER_OF_2(CXLFLASH_MAX_CMDS);
पूर्ण

/* AFU defines a fixed size of 4K क्रम command buffers (borrow 4K page define) */
#घोषणा CMD_बफ_मानE     SIZE_4K

क्रमागत cxlflash_lr_state अणु
	LINK_RESET_INVALID,
	LINK_RESET_REQUIRED,
	LINK_RESET_COMPLETE
पूर्ण;

क्रमागत cxlflash_init_state अणु
	INIT_STATE_NONE,
	INIT_STATE_PCI,
	INIT_STATE_AFU,
	INIT_STATE_SCSI,
	INIT_STATE_CDEV
पूर्ण;

क्रमागत cxlflash_state अणु
	STATE_PROBING,	/* Initial state during probe */
	STATE_PROBED,	/* Temporary state, probe completed but EEH occurred */
	STATE_NORMAL,	/* Normal running state, everything good */
	STATE_RESET,	/* Reset state, trying to reset/recover */
	STATE_FAILTERM	/* Failed/terminating state, error out users/thपढ़ोs */
पूर्ण;

क्रमागत cxlflash_hwq_mode अणु
	HWQ_MODE_RR,	/* Roundrobin (शेष) */
	HWQ_MODE_TAG,	/* Distribute based on block MQ tag */
	HWQ_MODE_CPU,	/* CPU affinity */
	MAX_HWQ_MODE
पूर्ण;

/*
 * Each context has its own set of resource handles that is visible
 * only from that context.
 */

काष्ठा cxlflash_cfg अणु
	काष्ठा afu *afu;

	स्थिर काष्ठा cxlflash_backend_ops *ops;
	काष्ठा pci_dev *dev;
	काष्ठा pci_device_id *dev_id;
	काष्ठा Scsi_Host *host;
	पूर्णांक num_fc_ports;
	काष्ठा cdev cdev;
	काष्ठा device *अक्षरdev;

	uदीर्घ cxlflash_regs_pci;

	काष्ठा work_काष्ठा work_q;
	क्रमागत cxlflash_init_state init_state;
	क्रमागत cxlflash_lr_state lr_state;
	पूर्णांक lr_port;
	atomic_t scan_host_needed;

	व्योम *afu_cookie;

	atomic_t recovery_thपढ़ोs;
	काष्ठा mutex ctx_recovery_mutex;
	काष्ठा mutex ctx_tbl_list_mutex;
	काष्ठा rw_semaphore ioctl_rwsem;
	काष्ठा ctx_info *ctx_tbl[MAX_CONTEXT];
	काष्ठा list_head ctx_err_recovery; /* contexts w/ recovery pending */
	काष्ठा file_operations cxl_fops;

	/* Parameters that are LUN table related */
	पूर्णांक last_lun_index[MAX_FC_PORTS];
	पूर्णांक promote_lun_index;
	काष्ठा list_head lluns; /* list of llun_info काष्ठाs */

	रुको_queue_head_t पंचांगf_रुकोq;
	spinlock_t पंचांगf_slock;
	bool पंचांगf_active;
	bool ws_unmap;		/* Write-same unmap supported */
	रुको_queue_head_t reset_रुकोq;
	क्रमागत cxlflash_state state;
	async_cookie_t async_reset_cookie;
पूर्ण;

काष्ठा afu_cmd अणु
	काष्ठा sisl_ioarcb rcb;	/* IOARCB (cache line aligned) */
	काष्ठा sisl_ioasa sa;	/* IOASA must follow IOARCB */
	काष्ठा afu *parent;
	काष्ठा scsi_cmnd *scp;
	काष्ठा completion cevent;
	काष्ठा list_head queue;
	u32 hwq_index;

	u8 cmd_पंचांगf:1,
	   cmd_पातed:1;

	काष्ठा list_head list;	/* Pending commands link */

	/* As per the SISLITE spec the IOARCB EA has to be 16-byte aligned.
	 * However क्रम perक्रमmance reasons the IOARCB/IOASA should be
	 * cache line aligned.
	 */
पूर्ण __aligned(cache_line_size());

अटल अंतरभूत काष्ठा afu_cmd *sc_to_afuc(काष्ठा scsi_cmnd *sc)
अणु
	वापस PTR_ALIGN(scsi_cmd_priv(sc), __alignof__(काष्ठा afu_cmd));
पूर्ण

अटल अंतरभूत काष्ठा afu_cmd *sc_to_afuci(काष्ठा scsi_cmnd *sc)
अणु
	काष्ठा afu_cmd *afuc = sc_to_afuc(sc);

	INIT_LIST_HEAD(&afuc->queue);
	वापस afuc;
पूर्ण

अटल अंतरभूत काष्ठा afu_cmd *sc_to_afucz(काष्ठा scsi_cmnd *sc)
अणु
	काष्ठा afu_cmd *afuc = sc_to_afuc(sc);

	स_रखो(afuc, 0, माप(*afuc));
	वापस sc_to_afuci(sc);
पूर्ण

काष्ठा hwq अणु
	/* Stuff requiring alignment go first. */
	काष्ठा sisl_ioarcb sq[NUM_SQ_ENTRY];		/* 16K SQ */
	u64 rrq_entry[NUM_RRQ_ENTRY];			/* 2K RRQ */

	/* Beware of alignment till here. Preferably पूर्णांकroduce new
	 * fields after this poपूर्णांक
	 */
	काष्ठा afu *afu;
	व्योम *ctx_cookie;
	काष्ठा sisl_host_map __iomem *host_map;		/* MC host map */
	काष्ठा sisl_ctrl_map __iomem *ctrl_map;		/* MC control map */
	ctx_hndl_t ctx_hndl;	/* master's context handle */
	u32 index;		/* Index of this hwq */
	पूर्णांक num_irqs;		/* Number of पूर्णांकerrupts requested क्रम context */
	काष्ठा list_head pending_cmds;	/* Commands pending completion */

	atomic_t hsq_credits;
	spinlock_t hsq_slock;	/* Hardware send queue lock */
	काष्ठा sisl_ioarcb *hsq_start;
	काष्ठा sisl_ioarcb *hsq_end;
	काष्ठा sisl_ioarcb *hsq_curr;
	spinlock_t hrrq_slock;
	u64 *hrrq_start;
	u64 *hrrq_end;
	u64 *hrrq_curr;
	bool toggle;
	bool hrrq_online;

	s64 room;

	काष्ठा irq_poll irqpoll;
पूर्ण __aligned(cache_line_size());

काष्ठा afu अणु
	काष्ठा hwq hwqs[CXLFLASH_MAX_HWQS];
	पूर्णांक (*send_cmd)(काष्ठा afu *afu, काष्ठा afu_cmd *cmd);
	पूर्णांक (*context_reset)(काष्ठा hwq *hwq);

	/* AFU HW */
	काष्ठा cxlflash_afu_map __iomem *afu_map;	/* entire MMIO map */

	atomic_t cmds_active;	/* Number of currently active AFU commands */
	काष्ठा mutex sync_active;	/* Mutex to serialize AFU commands */
	u64 hb;
	u32 पूर्णांकernal_lun;	/* User-desired LUN mode क्रम this AFU */

	u32 num_hwqs;		/* Number of hardware queues */
	u32 desired_hwqs;	/* Desired h/w queues, effective on AFU reset */
	क्रमागत cxlflash_hwq_mode hwq_mode; /* Steering mode क्रम h/w queues */
	u32 hwq_rr_count;	/* Count to distribute traffic क्रम roundrobin */

	अक्षर version[16];
	u64 पूर्णांकerface_version;

	u32 irqpoll_weight;
	काष्ठा cxlflash_cfg *parent; /* Poपूर्णांकer back to parent cxlflash_cfg */
पूर्ण;

अटल अंतरभूत काष्ठा hwq *get_hwq(काष्ठा afu *afu, u32 index)
अणु
	WARN_ON(index >= CXLFLASH_MAX_HWQS);

	वापस &afu->hwqs[index];
पूर्ण

अटल अंतरभूत bool afu_is_irqpoll_enabled(काष्ठा afu *afu)
अणु
	वापस !!afu->irqpoll_weight;
पूर्ण

अटल अंतरभूत bool afu_has_cap(काष्ठा afu *afu, u64 cap)
अणु
	u64 afu_cap = afu->पूर्णांकerface_version >> SISL_INTVER_CAP_SHIFT;

	वापस afu_cap & cap;
पूर्ण

अटल अंतरभूत bool afu_is_ocxl_lisn(काष्ठा afu *afu)
अणु
	वापस afu_has_cap(afu, SISL_INTVER_CAP_OCXL_LISN);
पूर्ण

अटल अंतरभूत bool afu_is_afu_debug(काष्ठा afu *afu)
अणु
	वापस afu_has_cap(afu, SISL_INTVER_CAP_AFU_DEBUG);
पूर्ण

अटल अंतरभूत bool afu_is_lun_provision(काष्ठा afu *afu)
अणु
	वापस afu_has_cap(afu, SISL_INTVER_CAP_LUN_PROVISION);
पूर्ण

अटल अंतरभूत bool afu_is_sq_cmd_mode(काष्ठा afu *afu)
अणु
	वापस afu_has_cap(afu, SISL_INTVER_CAP_SQ_CMD_MODE);
पूर्ण

अटल अंतरभूत bool afu_is_ioarrin_cmd_mode(काष्ठा afu *afu)
अणु
	वापस afu_has_cap(afu, SISL_INTVER_CAP_IOARRIN_CMD_MODE);
पूर्ण

अटल अंतरभूत u64 lun_to_lunid(u64 lun)
अणु
	__be64 lun_id;

	पूर्णांक_to_scsilun(lun, (काष्ठा scsi_lun *)&lun_id);
	वापस be64_to_cpu(lun_id);
पूर्ण

अटल अंतरभूत काष्ठा fc_port_bank __iomem *get_fc_port_bank(
					    काष्ठा cxlflash_cfg *cfg, पूर्णांक i)
अणु
	काष्ठा afu *afu = cfg->afu;

	वापस &afu->afu_map->global.bank[CHAN2PORTBANK(i)];
पूर्ण

अटल अंतरभूत __be64 __iomem *get_fc_port_regs(काष्ठा cxlflash_cfg *cfg, पूर्णांक i)
अणु
	काष्ठा fc_port_bank __iomem *fcpb = get_fc_port_bank(cfg, i);

	वापस &fcpb->fc_port_regs[CHAN2BANKPORT(i)][0];
पूर्ण

अटल अंतरभूत __be64 __iomem *get_fc_port_luns(काष्ठा cxlflash_cfg *cfg, पूर्णांक i)
अणु
	काष्ठा fc_port_bank __iomem *fcpb = get_fc_port_bank(cfg, i);

	वापस &fcpb->fc_port_luns[CHAN2BANKPORT(i)][0];
पूर्ण

पूर्णांक cxlflash_afu_sync(काष्ठा afu *afu, ctx_hndl_t c, res_hndl_t r, u8 mode);
व्योम cxlflash_list_init(व्योम);
व्योम cxlflash_term_global_luns(व्योम);
व्योम cxlflash_मुक्त_errpage(व्योम);
पूर्णांक cxlflash_ioctl(काष्ठा scsi_device *sdev, अचिन्हित पूर्णांक cmd,
		   व्योम __user *arg);
व्योम cxlflash_stop_term_user_contexts(काष्ठा cxlflash_cfg *cfg);
पूर्णांक cxlflash_mark_contexts_error(काष्ठा cxlflash_cfg *cfg);
व्योम cxlflash_term_local_luns(काष्ठा cxlflash_cfg *cfg);
व्योम cxlflash_restore_luntable(काष्ठा cxlflash_cfg *cfg);

#पूर्ण_अगर /* अगरndef _CXLFLASH_COMMON_H */
