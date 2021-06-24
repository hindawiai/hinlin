<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
#अगर_अघोषित __CARD_BASE_H__
#घोषणा __CARD_BASE_H__

/**
 * IBM Accelerator Family 'GenWQE'
 *
 * (C) Copyright IBM Corp. 2013
 *
 * Author: Frank Haverkamp <haver@linux.vnet.ibm.com>
 * Author: Joerg-Stephan Vogt <jsvogt@de.ibm.com>
 * Author: Michael Jung <mijung@gmx.net>
 * Author: Michael Ruettger <michael@ibmra.de>
 */

/*
 * Interfaces within the GenWQE module. Defines genwqe_card and
 * ddcb_queue as well as ddcb_requ.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/cdev.h>
#समावेश <linux/stringअगरy.h>
#समावेश <linux/pci.h>
#समावेश <linux/semaphore.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/पन.स>
#समावेश <linux/debugfs.h>
#समावेश <linux/slab.h>

#समावेश <linux/genwqe/genwqe_card.h>
#समावेश "genwqe_driver.h"

#घोषणा GENWQE_MSI_IRQS			4  /* Just one supported, no MSIx */

#घोषणा GENWQE_MAX_VFS			15 /* maximum 15 VFs are possible */
#घोषणा GENWQE_MAX_FUNCS		16 /* 1 PF and 15 VFs */
#घोषणा GENWQE_CARD_NO_MAX		(16 * GENWQE_MAX_FUNCS)

/* Compile parameters, some of them appear in debugfs क्रम later adjusपंचांगent */
#घोषणा GENWQE_DDCB_MAX			32 /* DDCBs on the work-queue */
#घोषणा GENWQE_POLLING_ENABLED		0  /* in हाल of irqs not working */
#घोषणा GENWQE_DDCB_SOFTWARE_TIMEOUT	10 /* समयout per DDCB in seconds */
#घोषणा GENWQE_KILL_TIMEOUT		8  /* समय until process माला_लो समाप्तed */
#घोषणा GENWQE_VF_JOBTIMEOUT_MSEC	250  /* 250 msec */
#घोषणा GENWQE_PF_JOBTIMEOUT_MSEC	8000 /* 8 sec should be ok */
#घोषणा GENWQE_HEALTH_CHECK_INTERVAL	4 /* <= 0: disabled */

/* Sysfs attribute groups used when we create the genwqe device */
बाह्य स्थिर काष्ठा attribute_group *genwqe_attribute_groups[];

/*
 * Config space क्रम Genwqe5 A7:
 * 00:[14 10 4b 04]40 00 10 00[00 00 00 12]00 00 00 00
 * 10: 0c 00 00 f0 07 3c 00 00 00 00 00 00 00 00 00 00
 * 20: 00 00 00 00 00 00 00 00 00 00 00 00[14 10 4b 04]
 * 30: 00 00 00 00 50 00 00 00 00 00 00 00 00 00 00 00
 */
#घोषणा PCI_DEVICE_GENWQE		0x044b /* Genwqe DeviceID */

#घोषणा PCI_SUBSYSTEM_ID_GENWQE5	0x035f /* Genwqe A5 Subप्रणाली-ID */
#घोषणा PCI_SUBSYSTEM_ID_GENWQE5_NEW	0x044b /* Genwqe A5 Subप्रणाली-ID */
#घोषणा PCI_CLASSCODE_GENWQE5		0x1200 /* UNKNOWN */

#घोषणा PCI_SUBVENDOR_ID_IBM_SRIOV	0x0000
#घोषणा PCI_SUBSYSTEM_ID_GENWQE5_SRIOV	0x0000 /* Genwqe A5 Subप्रणाली-ID */
#घोषणा PCI_CLASSCODE_GENWQE5_SRIOV	0x1200 /* UNKNOWN */

#घोषणा	GENWQE_SLU_ARCH_REQ		2 /* Required SLU architecture level */

/**
 * काष्ठा genwqe_reg - Genwqe data dump functionality
 */
काष्ठा genwqe_reg अणु
	u32 addr;
	u32 idx;
	u64 val;
पूर्ण;

/*
 * क्रमागत genwqe_dbg_type - Specअगरy chip unit to dump/debug
 */
क्रमागत genwqe_dbg_type अणु
	GENWQE_DBG_UNIT0 = 0,  /* captured beक्रमe prev errs cleared */
	GENWQE_DBG_UNIT1 = 1,
	GENWQE_DBG_UNIT2 = 2,
	GENWQE_DBG_UNIT3 = 3,
	GENWQE_DBG_UNIT4 = 4,
	GENWQE_DBG_UNIT5 = 5,
	GENWQE_DBG_UNIT6 = 6,
	GENWQE_DBG_UNIT7 = 7,
	GENWQE_DBG_REGS  = 8,
	GENWQE_DBG_DMA   = 9,
	GENWQE_DBG_UNITS = 10, /* max number of possible debug units  */
पूर्ण;

/* Software error injection to simulate card failures */
#घोषणा GENWQE_INJECT_HARDWARE_FAILURE	0x00000001 /* injects -1 reg पढ़ोs */
#घोषणा GENWQE_INJECT_BUS_RESET_FAILURE 0x00000002 /* pci_bus_reset fail */
#घोषणा GENWQE_INJECT_GFIR_FATAL	0x00000004 /* GFIR = 0x0000ffff */
#घोषणा GENWQE_INJECT_GFIR_INFO		0x00000008 /* GFIR = 0xffff0000 */

/*
 * Genwqe card description and management data.
 *
 * Error-handling in हाल of card malfunction
 * ------------------------------------------
 *
 * If the card is detected to be defective the outside environment
 * will cause the PCI layer to call deinit (the cleanup function क्रम
 * probe). This is the same effect like करोing a unbind/bind operation
 * on the card.
 *
 * The genwqe card driver implements a health checking thपढ़ो which
 * verअगरies the card function. If this detects a problem the cards
 * device is being shutकरोwn and restarted again, aदीर्घ with a reset of
 * the card and queue.
 *
 * All functions accessing the card device वापस either -EIO or -ENODEV
 * code to indicate the malfunction to the user. The user has to बंद
 * the file descriptor and खोलो a new one, once the card becomes
 * available again.
 *
 * If the खोलो file descriptor is setup to receive SIGIO, the संकेत is
 * genereated क्रम the application which has to provide a handler to
 * react on it. If the application करोes not बंद the खोलो
 * file descriptor a SIGKILL is send to enक्रमce मुक्तing the cards
 * resources.
 *
 * I did not find a dअगरferent way to prevent kernel problems due to
 * reference counters क्रम the cards अक्षरacter devices getting out of
 * sync. The अक्षरacter device deallocation करोes not block, even अगर
 * there is still an खोलो file descriptor pending. If this pending
 * descriptor is बंदd, the data काष्ठाures used by the अक्षरacter
 * device is reinstantiated, which will lead to the reference counter
 * dropping below the allowed values.
 *
 * Card recovery
 * -------------
 *
 * To test the पूर्णांकernal driver recovery the following command can be used:
 *   suकरो sh -c 'echo 0xfffff > /sys/class/genwqe/genwqe0_card/err_inject'
 */


/**
 * काष्ठा dma_mapping_type - Mapping type definition
 *
 * To aव्योम स_नकलing data arround we use user memory directly. To करो
 * this we need to pin/swap-in the memory and request a DMA address
 * क्रम it.
 */
क्रमागत dma_mapping_type अणु
	GENWQE_MAPPING_RAW = 0,		/* contignous memory buffer */
	GENWQE_MAPPING_SGL_TEMP,	/* sglist dynamically used */
	GENWQE_MAPPING_SGL_PINNED,	/* sglist used with pinning */
पूर्ण;

/**
 * काष्ठा dma_mapping - Inक्रमmation about memory mappings करोne by the driver
 */
काष्ठा dma_mapping अणु
	क्रमागत dma_mapping_type type;

	व्योम *u_vaddr;			/* user-space vaddr/non-aligned */
	व्योम *k_vaddr;			/* kernel-space vaddr/non-aligned */
	dma_addr_t dma_addr;		/* physical DMA address */

	काष्ठा page **page_list;	/* list of pages used by user buff */
	dma_addr_t *dma_list;		/* list of dma addresses per page */
	अचिन्हित पूर्णांक nr_pages;		/* number of pages */
	अचिन्हित पूर्णांक size;		/* size in bytes */

	काष्ठा list_head card_list;	/* list of usr_maps क्रम card */
	काष्ठा list_head pin_list;	/* list of pinned memory क्रम dev */
	पूर्णांक ग_लिखो;			/* writable map? useful in unmapping */
पूर्ण;

अटल अंतरभूत व्योम genwqe_mapping_init(काष्ठा dma_mapping *m,
				       क्रमागत dma_mapping_type type)
अणु
	स_रखो(m, 0, माप(*m));
	m->type = type;
	m->ग_लिखो = 1; /* Assume the maps we create are R/W */
पूर्ण

/**
 * काष्ठा ddcb_queue - DDCB queue data
 * @ddcb_max:          Number of DDCBs on the queue
 * @ddcb_next:         Next मुक्त DDCB
 * @ddcb_act:          Next DDCB supposed to finish
 * @ddcb_seq:          Sequence number of last DDCB
 * @ddcbs_in_flight:   Currently enqueued DDCBs
 * @ddcbs_completed:   Number of alपढ़ोy completed DDCBs
 * @वापस_on_busy:    Number of -EBUSY वापसs on full queue
 * @रुको_on_busy:      Number of रुकोs on full queue
 * @ddcb_daddr:        DMA address of first DDCB in the queue
 * @ddcb_vaddr:        Kernel भव address of first DDCB in the queue
 * @ddcb_req:          Associated requests (one per DDCB)
 * @ddcb_रुकोqs:       Associated रुको queues (one per DDCB)
 * @ddcb_lock:         Lock to protect queuing operations
 * @ddcb_रुकोq:        Wait on next DDCB finishing
 */

काष्ठा ddcb_queue अणु
	पूर्णांक ddcb_max;			/* amount of DDCBs  */
	पूर्णांक ddcb_next;			/* next available DDCB num */
	पूर्णांक ddcb_act;			/* DDCB to be processed */
	u16 ddcb_seq;			/* slc seq num */
	अचिन्हित पूर्णांक ddcbs_in_flight;	/* number of ddcbs in processing */
	अचिन्हित पूर्णांक ddcbs_completed;
	अचिन्हित पूर्णांक ddcbs_max_in_flight;
	अचिन्हित पूर्णांक वापस_on_busy;    /* how many बार -EBUSY? */
	अचिन्हित पूर्णांक रुको_on_busy;

	dma_addr_t ddcb_daddr;		/* DMA address */
	काष्ठा ddcb *ddcb_vaddr;	/* kernel भव addr क्रम DDCBs */
	काष्ठा ddcb_requ **ddcb_req;	/* ddcb processing parameter */
	रुको_queue_head_t *ddcb_रुकोqs; /* रुकोqueue per ddcb */

	spinlock_t ddcb_lock;		/* exclusive access to queue */
	रुको_queue_head_t busy_रुकोq;   /* रुको क्रम ddcb processing */

	/* रेजिस्टरs or the respective queue to be used */
	u32 IO_QUEUE_CONFIG;
	u32 IO_QUEUE_STATUS;
	u32 IO_QUEUE_SEGMENT;
	u32 IO_QUEUE_INITSQN;
	u32 IO_QUEUE_WRAP;
	u32 IO_QUEUE_OFFSET;
	u32 IO_QUEUE_WTIME;
	u32 IO_QUEUE_ERRCNTS;
	u32 IO_QUEUE_LRW;
पूर्ण;

/*
 * GFIR, SLU_UNITCFG, APP_UNITCFG
 *   8 Units with FIR/FEC + 64 * 2ndary FIRS/FEC.
 */
#घोषणा GENWQE_FFDC_REGS	(3 + (8 * (2 + 2 * 64)))

काष्ठा genwqe_ffdc अणु
	अचिन्हित पूर्णांक entries;
	काष्ठा genwqe_reg *regs;
पूर्ण;

/**
 * काष्ठा genwqe_dev - GenWQE device inक्रमmation
 * @card_state:       Card operation state, see above
 * @ffdc:             First Failure Data Capture buffers क्रम each unit
 * @card_thपढ़ो:      Working thपढ़ो to operate the DDCB queue
 * @card_रुकोq:       Wait queue used in card_thपढ़ो
 * @queue:            DDCB queue
 * @health_thपढ़ो:    Card monitoring thपढ़ो (only क्रम PFs)
 * @health_रुकोq:     Wait queue used in health_thपढ़ो
 * @pci_dev:          Associated PCI device (function)
 * @mmio:             Base address of 64-bit रेजिस्टर space
 * @mmio_len:         Length of रेजिस्टर area
 * @file_lock:        Lock to protect access to file_list
 * @file_list:        List of all processes with खोलो GenWQE file descriptors
 *
 * This काष्ठा contains all inक्रमmation needed to communicate with a
 * GenWQE card. It is initialized when a GenWQE device is found and
 * destroyed when it goes away. It holds data to मुख्यtain the queue as
 * well as data needed to feed the user पूर्णांकerfaces.
 */
काष्ठा genwqe_dev अणु
	क्रमागत genwqe_card_state card_state;
	spinlock_t prपूर्णांक_lock;

	पूर्णांक card_idx;			/* card index 0..CARD_NO_MAX-1 */
	u64 flags;			/* general flags */

	/* FFDC data gathering */
	काष्ठा genwqe_ffdc ffdc[GENWQE_DBG_UNITS];

	/* DDCB workqueue */
	काष्ठा task_काष्ठा *card_thपढ़ो;
	रुको_queue_head_t queue_रुकोq;
	काष्ठा ddcb_queue queue;	/* genwqe DDCB queue */
	अचिन्हित पूर्णांक irqs_processed;

	/* Card health checking thपढ़ो */
	काष्ठा task_काष्ठा *health_thपढ़ो;
	रुको_queue_head_t health_रुकोq;

	पूर्णांक use_platक्रमm_recovery;	/* use platक्रमm recovery mechanisms */

	/* अक्षर device */
	dev_t  devnum_genwqe;		/* major/minor num card */
	काष्ठा class *class_genwqe;	/* reference to class object */
	काष्ठा device *dev;		/* क्रम device creation */
	काष्ठा cdev cdev_genwqe;	/* अक्षर device क्रम card */

	काष्ठा dentry *debugfs_root;	/* debugfs card root directory */
	काष्ठा dentry *debugfs_genwqe;	/* debugfs driver root directory */

	/* pci resources */
	काष्ठा pci_dev *pci_dev;	/* PCI device */
	व्योम __iomem *mmio;		/* BAR-0 MMIO start */
	अचिन्हित दीर्घ mmio_len;
	पूर्णांक num_vfs;
	u32 vf_jobसमयout_msec[GENWQE_MAX_VFS];
	पूर्णांक is_privileged;		/* access to all regs possible */

	/* config regs which we need often */
	u64 slu_unitcfg;
	u64 app_unitcfg;
	u64 softreset;
	u64 err_inject;
	u64 last_gfir;
	अक्षर app_name[5];

	spinlock_t file_lock;		/* lock क्रम खोलो files */
	काष्ठा list_head file_list;	/* list of खोलो files */

	/* debugfs parameters */
	पूर्णांक ddcb_software_समयout;	/* रुको until DDCB बार out */
	पूर्णांक skip_recovery;		/* circumvention अगर recovery fails */
	पूर्णांक समाप्त_समयout;		/* रुको after sending SIGKILL */
पूर्ण;

/**
 * क्रमागत genwqe_requ_state - State of a DDCB execution request
 */
क्रमागत genwqe_requ_state अणु
	GENWQE_REQU_NEW      = 0,
	GENWQE_REQU_ENQUEUED = 1,
	GENWQE_REQU_TAPPED   = 2,
	GENWQE_REQU_FINISHED = 3,
	GENWQE_REQU_STATE_MAX,
पूर्ण;

/**
 * काष्ठा genwqe_sgl - Scatter gather list describing user-space memory
 * @sgl:            scatter gather list needs to be 128 byte aligned
 * @sgl_dma_addr:   dma address of sgl
 * @sgl_size:       size of area used क्रम sgl
 * @user_addr:      user-space address of memory area
 * @user_size:      size of user-space memory area
 * @page:           buffer क्रम partial pages अगर needed
 * @page_dma_addr:  dma address partial pages
 * @ग_लिखो:          should we ग_लिखो it back to userspace?
 */
काष्ठा genwqe_sgl अणु
	dma_addr_t sgl_dma_addr;
	काष्ठा sg_entry *sgl;
	माप_प्रकार sgl_size;	/* size of sgl */

	व्योम __user *user_addr; /* user-space base-address */
	माप_प्रकार user_size;       /* size of memory area */

	पूर्णांक ग_लिखो;

	अचिन्हित दीर्घ nr_pages;
	अचिन्हित दीर्घ fpage_offs;
	माप_प्रकार fpage_size;
	माप_प्रकार lpage_size;

	व्योम *fpage;
	dma_addr_t fpage_dma_addr;

	व्योम *lpage;
	dma_addr_t lpage_dma_addr;
पूर्ण;

पूर्णांक genwqe_alloc_sync_sgl(काष्ठा genwqe_dev *cd, काष्ठा genwqe_sgl *sgl,
			  व्योम __user *user_addr, माप_प्रकार user_size, पूर्णांक ग_लिखो);

पूर्णांक genwqe_setup_sgl(काष्ठा genwqe_dev *cd, काष्ठा genwqe_sgl *sgl,
		     dma_addr_t *dma_list);

पूर्णांक genwqe_मुक्त_sync_sgl(काष्ठा genwqe_dev *cd, काष्ठा genwqe_sgl *sgl);

/**
 * काष्ठा ddcb_requ - Kernel पूर्णांकernal representation of the DDCB request
 * @cmd:          User space representation of the DDCB execution request
 */
काष्ठा ddcb_requ अणु
	/* kernel specअगरic content */
	क्रमागत genwqe_requ_state req_state; /* request status */
	पूर्णांक num;			  /* ddcb_no क्रम this request */
	काष्ठा ddcb_queue *queue;	  /* associated queue */

	काष्ठा dma_mapping  dma_mappings[DDCB_FIXUPS];
	काष्ठा genwqe_sgl sgls[DDCB_FIXUPS];

	/* kernel/user shared content */
	काष्ठा genwqe_ddcb_cmd cmd;	/* ddcb_no क्रम this request */
	काष्ठा genwqe_debug_data debug_data;
पूर्ण;

/**
 * काष्ठा genwqe_file - Inक्रमmation क्रम खोलो GenWQE devices
 */
काष्ठा genwqe_file अणु
	काष्ठा genwqe_dev *cd;
	काष्ठा genwqe_driver *client;
	काष्ठा file *filp;

	काष्ठा fasync_काष्ठा *async_queue;
	काष्ठा pid *खोलोer;
	काष्ठा list_head list;		/* entry in list of खोलो files */

	spinlock_t map_lock;		/* lock क्रम dma_mappings */
	काष्ठा list_head map_list;	/* list of dma_mappings */

	spinlock_t pin_lock;		/* lock क्रम pinned memory */
	काष्ठा list_head pin_list;	/* list of pinned memory */
पूर्ण;

पूर्णांक  genwqe_setup_service_layer(काष्ठा genwqe_dev *cd); /* क्रम PF only */
पूर्णांक  genwqe_finish_queue(काष्ठा genwqe_dev *cd);
पूर्णांक  genwqe_release_service_layer(काष्ठा genwqe_dev *cd);

/**
 * genwqe_get_slu_id() - Read Service Layer Unit Id
 * Return: 0x00: Development code
 *         0x01: SLC1 (old)
 *         0x02: SLC2 (sept2012)
 *         0x03: SLC2 (feb2013, generic driver)
 */
अटल अंतरभूत पूर्णांक genwqe_get_slu_id(काष्ठा genwqe_dev *cd)
अणु
	वापस (पूर्णांक)((cd->slu_unitcfg >> 32) & 0xff);
पूर्ण

पूर्णांक  genwqe_ddcbs_in_flight(काष्ठा genwqe_dev *cd);

u8   genwqe_card_type(काष्ठा genwqe_dev *cd);
पूर्णांक  genwqe_card_reset(काष्ठा genwqe_dev *cd);
पूर्णांक  genwqe_set_पूर्णांकerrupt_capability(काष्ठा genwqe_dev *cd, पूर्णांक count);
व्योम genwqe_reset_पूर्णांकerrupt_capability(काष्ठा genwqe_dev *cd);

पूर्णांक  genwqe_device_create(काष्ठा genwqe_dev *cd);
पूर्णांक  genwqe_device_हटाओ(काष्ठा genwqe_dev *cd);

/* debugfs */
व्योम genwqe_init_debugfs(काष्ठा genwqe_dev *cd);
व्योम genqwe_निकास_debugfs(काष्ठा genwqe_dev *cd);

पूर्णांक  genwqe_पढ़ो_softreset(काष्ठा genwqe_dev *cd);

/* Hardware Circumventions */
पूर्णांक  genwqe_recovery_on_fatal_gfir_required(काष्ठा genwqe_dev *cd);
पूर्णांक  genwqe_flash_पढ़ोback_fails(काष्ठा genwqe_dev *cd);

/**
 * genwqe_ग_लिखो_vreg() - Write रेजिस्टर in VF winकरोw
 * @cd:    genwqe device
 * @reg:   रेजिस्टर address
 * @val:   value to ग_लिखो
 * @func:  0: PF, 1: VF0, ..., 15: VF14
 */
पूर्णांक genwqe_ग_लिखो_vreg(काष्ठा genwqe_dev *cd, u32 reg, u64 val, पूर्णांक func);

/**
 * genwqe_पढ़ो_vreg() - Read रेजिस्टर in VF winकरोw
 * @cd:    genwqe device
 * @reg:   रेजिस्टर address
 * @func:  0: PF, 1: VF0, ..., 15: VF14
 *
 * Return: content of the रेजिस्टर
 */
u64 genwqe_पढ़ो_vreg(काष्ठा genwqe_dev *cd, u32 reg, पूर्णांक func);

/* FFDC Buffer Management */
पूर्णांक  genwqe_ffdc_buff_size(काष्ठा genwqe_dev *cd, पूर्णांक unit_id);
पूर्णांक  genwqe_ffdc_buff_पढ़ो(काष्ठा genwqe_dev *cd, पूर्णांक unit_id,
			   काष्ठा genwqe_reg *regs, अचिन्हित पूर्णांक max_regs);
पूर्णांक  genwqe_पढ़ो_ffdc_regs(काष्ठा genwqe_dev *cd, काष्ठा genwqe_reg *regs,
			   अचिन्हित पूर्णांक max_regs, पूर्णांक all);
पूर्णांक  genwqe_ffdc_dump_dma(काष्ठा genwqe_dev *cd,
			  काष्ठा genwqe_reg *regs, अचिन्हित पूर्णांक max_regs);

पूर्णांक  genwqe_init_debug_data(काष्ठा genwqe_dev *cd,
			    काष्ठा genwqe_debug_data *d);

व्योम genwqe_init_crc32(व्योम);
पूर्णांक  genwqe_पढ़ो_app_id(काष्ठा genwqe_dev *cd, अक्षर *app_name, पूर्णांक len);

/* Memory allocation/deallocation; dma address handling */
पूर्णांक  genwqe_user_vmap(काष्ठा genwqe_dev *cd, काष्ठा dma_mapping *m,
		      व्योम *uaddr, अचिन्हित दीर्घ size);

पूर्णांक  genwqe_user_vunmap(काष्ठा genwqe_dev *cd, काष्ठा dma_mapping *m);

अटल अंतरभूत bool dma_mapping_used(काष्ठा dma_mapping *m)
अणु
	अगर (!m)
		वापस false;
	वापस m->size != 0;
पूर्ण

/**
 * __genwqe_execute_ddcb() - Execute DDCB request with addr translation
 *
 * This function will करो the address translation changes to the DDCBs
 * according to the definitions required by the ATS field. It looks up
 * the memory allocation buffer or करोes vmap/vunmap क्रम the respective
 * user-space buffers, inclusive page pinning and scatter gather list
 * buildup and tearकरोwn.
 */
पूर्णांक  __genwqe_execute_ddcb(काष्ठा genwqe_dev *cd,
			   काष्ठा genwqe_ddcb_cmd *cmd, अचिन्हित पूर्णांक f_flags);

/**
 * __genwqe_execute_raw_ddcb() - Execute DDCB request without addr translation
 *
 * This version will not करो address translation or any modअगरication of
 * the DDCB data. It is used e.g. क्रम the MoveFlash DDCB which is
 * entirely prepared by the driver itself. That means the appropriate
 * DMA addresses are alपढ़ोy in the DDCB and करो not need any
 * modअगरication.
 */
पूर्णांक  __genwqe_execute_raw_ddcb(काष्ठा genwqe_dev *cd,
			       काष्ठा genwqe_ddcb_cmd *cmd,
			       अचिन्हित पूर्णांक f_flags);
पूर्णांक  __genwqe_enqueue_ddcb(काष्ठा genwqe_dev *cd,
			   काष्ठा ddcb_requ *req,
			   अचिन्हित पूर्णांक f_flags);

पूर्णांक  __genwqe_रुको_ddcb(काष्ठा genwqe_dev *cd, काष्ठा ddcb_requ *req);
पूर्णांक  __genwqe_purge_ddcb(काष्ठा genwqe_dev *cd, काष्ठा ddcb_requ *req);

/* रेजिस्टर access */
पूर्णांक __genwqe_ग_लिखोq(काष्ठा genwqe_dev *cd, u64 byte_offs, u64 val);
u64 __genwqe_पढ़ोq(काष्ठा genwqe_dev *cd, u64 byte_offs);
पूर्णांक __genwqe_ग_लिखोl(काष्ठा genwqe_dev *cd, u64 byte_offs, u32 val);
u32 __genwqe_पढ़ोl(काष्ठा genwqe_dev *cd, u64 byte_offs);

व्योम *__genwqe_alloc_consistent(काष्ठा genwqe_dev *cd, माप_प्रकार size,
				 dma_addr_t *dma_handle);
व्योम __genwqe_मुक्त_consistent(काष्ठा genwqe_dev *cd, माप_प्रकार size,
			      व्योम *vaddr, dma_addr_t dma_handle);

/* Base घड़ी frequency in MHz */
पूर्णांक  genwqe_base_घड़ी_frequency(काष्ठा genwqe_dev *cd);

/* Beक्रमe FFDC is captured the traps should be stopped. */
व्योम genwqe_stop_traps(काष्ठा genwqe_dev *cd);
व्योम genwqe_start_traps(काष्ठा genwqe_dev *cd);

/* Hardware circumvention */
bool genwqe_need_err_masking(काष्ठा genwqe_dev *cd);

/**
 * genwqe_is_privileged() - Determine operation mode क्रम PCI function
 *
 * On Intel with SRIOV support we see:
 *   PF: is_physfn = 1 is_virtfn = 0
 *   VF: is_physfn = 0 is_virtfn = 1
 *
 * On Systems with no SRIOV support _and_ भवized प्रणालीs we get:
 *       is_physfn = 0 is_virtfn = 0
 *
 * Other venकरोrs have inभागidual pci device ids to distinguish between
 * भव function drivers and physical function drivers. GenWQE
 * unक्रमtunately has just on pci device id क्रम both, VFs and PF.
 *
 * The following code is used to distinguish अगर the card is running in
 * privileged mode, either as true PF or in a भवized प्रणाली with
 * full रेजिस्टर access e.g. currently on PowerPC.
 *
 * अगर (pci_dev->is_virtfn)
 *          cd->is_privileged = 0;
 *  अन्यथा
 *          cd->is_privileged = (__genwqe_पढ़ोq(cd, IO_SLU_BITSTREAM)
 *				 != IO_ILLEGAL_VALUE);
 */
अटल अंतरभूत पूर्णांक genwqe_is_privileged(काष्ठा genwqe_dev *cd)
अणु
	वापस cd->is_privileged;
पूर्ण

#पूर्ण_अगर	/* __CARD_BASE_H__ */
