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

#अगर_अघोषित _CXLFLASH_SUPERPIPE_H
#घोषणा _CXLFLASH_SUPERPIPE_H

बाह्य काष्ठा cxlflash_global global;

/*
 * Terminology: use afu (and not adapter) to refer to the HW.
 * Adapter is the entire slot and includes PSL out of which
 * only the AFU is visible to user space.
 */

/* Chunk size parms: note sislite minimum chunk size is
 * 0x10000 LBAs corresponding to a NMASK or 16.
 */
#घोषणा MC_CHUNK_SIZE     (1 << MC_RHT_NMASK)	/* in LBAs */

#घोषणा CMD_TIMEOUT 30  /* 30 secs */
#घोषणा CMD_RETRIES 5   /* 5 retries क्रम scsi_execute */

#घोषणा MAX_SECTOR_UNIT  512 /* max_sector is in 512 byte multiples */

क्रमागत lun_mode अणु
	MODE_NONE = 0,
	MODE_VIRTUAL,
	MODE_PHYSICAL
पूर्ण;

/* Global (entire driver, spans adapters) lun_info काष्ठाure */
काष्ठा glun_info अणु
	u64 max_lba;		/* from पढ़ो cap(16) */
	u32 blk_len;		/* from पढ़ो cap(16) */
	क्रमागत lun_mode mode;	/* NONE, VIRTUAL, PHYSICAL */
	पूर्णांक users;		/* Number of users w/ references to LUN */

	u8 wwid[16];

	काष्ठा mutex mutex;

	काष्ठा blka blka;
	काष्ठा list_head list;
पूर्ण;

/* Local (per-adapter) lun_info काष्ठाure */
काष्ठा llun_info अणु
	u64 lun_id[MAX_FC_PORTS]; /* from REPORT_LUNS */
	u32 lun_index;		/* Index in the LUN table */
	u32 host_no;		/* host_no from Scsi_host */
	u32 port_sel;		/* What port to use क्रम this LUN */
	bool in_table;		/* Whether a LUN table entry was created */

	u8 wwid[16];		/* Keep a duplicate copy here? */

	काष्ठा glun_info *parent; /* Poपूर्णांकer to entry in global LUN काष्ठाure */
	काष्ठा scsi_device *sdev;
	काष्ठा list_head list;
पूर्ण;

काष्ठा lun_access अणु
	काष्ठा llun_info *lli;
	काष्ठा scsi_device *sdev;
	काष्ठा list_head list;
पूर्ण;

क्रमागत ctx_ctrl अणु
	CTX_CTRL_CLONE		= (1 << 1),
	CTX_CTRL_ERR		= (1 << 2),
	CTX_CTRL_ERR_FALLBACK	= (1 << 3),
	CTX_CTRL_NOPID		= (1 << 4),
	CTX_CTRL_खाता		= (1 << 5)
पूर्ण;

#घोषणा ENCODE_CTXID(_ctx, _id)	(((((u64)_ctx) & 0xFFFFFFFF0ULL) << 28) | _id)
#घोषणा DECODE_CTXID(_val)	(_val & 0xFFFFFFFF)

काष्ठा ctx_info अणु
	काष्ठा sisl_ctrl_map __iomem *ctrl_map; /* initialized at startup */
	काष्ठा sisl_rht_entry *rht_start; /* 1 page (req'd क्रम alignment),
					   * alloc/मुक्त on attach/detach
					   */
	u32 rht_out;		/* Number of checked out RHT entries */
	u32 rht_perms;		/* User-defined permissions क्रम RHT entries */
	काष्ठा llun_info **rht_lun;       /* Mapping of RHT entries to LUNs */
	u8 *rht_needs_ws;	/* User-desired ग_लिखो-same function per RHTE */

	u64 ctxid;
	u64 irqs; /* Number of पूर्णांकerrupts requested क्रम context */
	pid_t pid;
	bool initialized;
	bool unavail;
	bool err_recovery_active;
	काष्ठा mutex mutex; /* Context protection */
	काष्ठा kref kref;
	व्योम *ctx;
	काष्ठा cxlflash_cfg *cfg;
	काष्ठा list_head luns;	/* LUNs attached to this context */
	स्थिर काष्ठा vm_operations_काष्ठा *cxl_mmap_vmops;
	काष्ठा file *file;
	काष्ठा list_head list; /* Link contexts in error recovery */
पूर्ण;

काष्ठा cxlflash_global अणु
	काष्ठा mutex mutex;
	काष्ठा list_head gluns;/* list of glun_info काष्ठाs */
	काष्ठा page *err_page; /* One page of all 0xF क्रम error notअगरication */
पूर्ण;

पूर्णांक cxlflash_vlun_resize(काष्ठा scsi_device *sdev,
			 काष्ठा dk_cxlflash_resize *resize);
पूर्णांक _cxlflash_vlun_resize(काष्ठा scsi_device *sdev, काष्ठा ctx_info *ctxi,
			  काष्ठा dk_cxlflash_resize *resize);

पूर्णांक cxlflash_disk_release(काष्ठा scsi_device *sdev,
			  काष्ठा dk_cxlflash_release *release);
पूर्णांक _cxlflash_disk_release(काष्ठा scsi_device *sdev, काष्ठा ctx_info *ctxi,
			   काष्ठा dk_cxlflash_release *release);

पूर्णांक cxlflash_disk_clone(काष्ठा scsi_device *sdev,
			काष्ठा dk_cxlflash_clone *clone);

पूर्णांक cxlflash_disk_भव_खोलो(काष्ठा scsi_device *sdev, व्योम *arg);

पूर्णांक cxlflash_lun_attach(काष्ठा glun_info *gli, क्रमागत lun_mode mode, bool locked);
व्योम cxlflash_lun_detach(काष्ठा glun_info *gli);

काष्ठा ctx_info *get_context(काष्ठा cxlflash_cfg *cfg, u64 rctxit, व्योम *arg,
			     क्रमागत ctx_ctrl ctrl);
व्योम put_context(काष्ठा ctx_info *ctxi);

काष्ठा sisl_rht_entry *get_rhte(काष्ठा ctx_info *ctxi, res_hndl_t rhndl,
				काष्ठा llun_info *lli);

काष्ठा sisl_rht_entry *rhte_checkout(काष्ठा ctx_info *ctxi,
				     काष्ठा llun_info *lli);
व्योम rhte_checkin(काष्ठा ctx_info *ctxi, काष्ठा sisl_rht_entry *rhte);

व्योम cxlflash_ba_terminate(काष्ठा ba_lun *ba_lun);

पूर्णांक cxlflash_manage_lun(काष्ठा scsi_device *sdev,
			काष्ठा dk_cxlflash_manage_lun *manage);

पूर्णांक check_state(काष्ठा cxlflash_cfg *cfg);

#पूर्ण_अगर /* अगरndef _CXLFLASH_SUPERPIPE_H */
