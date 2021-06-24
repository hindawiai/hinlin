<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright 2018-2020 Broadcom.
 */

#अगर_अघोषित BCM_VK_H
#घोषणा BCM_VK_H

#समावेश <linux/atomic.h>
#समावेश <linux/firmware.h>
#समावेश <linux/irq.h>
#समावेश <linux/kref.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/mutex.h>
#समावेश <linux/pci.h>
#समावेश <linux/poll.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/tty.h>
#समावेश <linux/uaccess.h>
#समावेश <uapi/linux/misc/bcm_vk.h>

#समावेश "bcm_vk_msg.h"

#घोषणा DRV_MODULE_NAME		"bcm-vk"

/*
 * Load Image is completed in two stages:
 *
 * 1) When the VK device boot-up, M7 CPU runs and executes the BootROM.
 * The Secure Boot Loader (SBL) as part of the BootROM will run
 * to खोलो up ITCM क्रम host to push BOOT1 image.
 * SBL will authenticate the image beक्रमe jumping to BOOT1 image.
 *
 * 2) Because BOOT1 image is a secured image, we also called it the
 * Secure Boot Image (SBI). At second stage, SBI will initialize DDR
 * and रुको क्रम host to push BOOT2 image to DDR.
 * SBI will authenticate the image beक्रमe jumping to BOOT2 image.
 *
 */
/* Location of रेजिस्टरs of पूर्णांकerest in BAR0 */

/* Request रेजिस्टर क्रम Secure Boot Loader (SBL) करोwnload */
#घोषणा BAR_CODEPUSH_SBL		0x400
/* Start of ITCM */
#घोषणा CODEPUSH_BOOT1_ENTRY		0x00400000
#घोषणा CODEPUSH_MASK		        0xfffff000
#घोषणा CODEPUSH_BOOTSTART		BIT(0)

/* Boot Status रेजिस्टर */
#घोषणा BAR_BOOT_STATUS			0x404

#घोषणा SRAM_OPEN			BIT(16)
#घोषणा DDR_OPEN			BIT(17)

/* Firmware loader progress status definitions */
#घोषणा FW_LOADER_ACK_SEND_MORE_DATA	BIT(18)
#घोषणा FW_LOADER_ACK_IN_PROGRESS	BIT(19)
#घोषणा FW_LOADER_ACK_RCVD_ALL_DATA	BIT(20)

/* Boot1/2 is running in standalone mode */
#घोषणा BOOT_STDALONE_RUNNING		BIT(21)

/* definitions क्रम boot status रेजिस्टर */
#घोषणा BOOT_STATE_MASK			(0xffffffff & \
					 ~(FW_LOADER_ACK_SEND_MORE_DATA | \
					   FW_LOADER_ACK_IN_PROGRESS | \
					   BOOT_STDALONE_RUNNING))

#घोषणा BOOT_ERR_SHIFT			4
#घोषणा BOOT_ERR_MASK			(0xf << BOOT_ERR_SHIFT)
#घोषणा BOOT_PROG_MASK			0xf

#घोषणा BROM_STATUS_NOT_RUN		0x2
#घोषणा BROM_NOT_RUN			(SRAM_OPEN | BROM_STATUS_NOT_RUN)
#घोषणा BROM_STATUS_COMPLETE		0x6
#घोषणा BROM_RUNNING			(SRAM_OPEN | BROM_STATUS_COMPLETE)
#घोषणा BOOT1_STATUS_COMPLETE		0x6
#घोषणा BOOT1_RUNNING			(DDR_OPEN | BOOT1_STATUS_COMPLETE)
#घोषणा BOOT2_STATUS_COMPLETE		0x6
#घोषणा BOOT2_RUNNING			(FW_LOADER_ACK_RCVD_ALL_DATA | \
					 BOOT2_STATUS_COMPLETE)

/* Boot request क्रम Secure Boot Image (SBI) */
#घोषणा BAR_CODEPUSH_SBI		0x408
/* 64M mapped to BAR2 */
#घोषणा CODEPUSH_BOOT2_ENTRY		0x60000000

#घोषणा BAR_CARD_STATUS			0x410
/* CARD_STATUS definitions */
#घोषणा CARD_STATUS_TTYVK0_READY	BIT(0)
#घोषणा CARD_STATUS_TTYVK1_READY	BIT(1)

#घोषणा BAR_BOOT1_STDALONE_PROGRESS	0x420
#घोषणा BOOT1_STDALONE_SUCCESS		(BIT(13) | BIT(14))
#घोषणा BOOT1_STDALONE_PROGRESS_MASK	BOOT1_STDALONE_SUCCESS

#घोषणा BAR_METADATA_VERSION		0x440
#घोषणा BAR_OS_UPTIME			0x444
#घोषणा BAR_CHIP_ID			0x448
#घोषणा MAJOR_SOC_REV(_chip_id)		(((_chip_id) >> 20) & 0xf)

#घोषणा BAR_CARD_TEMPERATURE		0x45c
/* defines क्रम all temperature sensor */
#घोषणा BCM_VK_TEMP_FIELD_MASK		0xff
#घोषणा BCM_VK_CPU_TEMP_SHIFT		0
#घोषणा BCM_VK_DDR0_TEMP_SHIFT		8
#घोषणा BCM_VK_DDR1_TEMP_SHIFT		16

#घोषणा BAR_CARD_VOLTAGE		0x460
/* defines क्रम voltage rail conversion */
#घोषणा BCM_VK_VOLT_RAIL_MASK		0xffff
#घोषणा BCM_VK_3P3_VOLT_REG_SHIFT	16

#घोषणा BAR_CARD_ERR_LOG		0x464
/* Error log रेजिस्टर bit definition - रेजिस्टर क्रम error alerts */
#घोषणा ERR_LOG_UECC			BIT(0)
#घोषणा ERR_LOG_SSIM_BUSY		BIT(1)
#घोषणा ERR_LOG_AFBC_BUSY		BIT(2)
#घोषणा ERR_LOG_HIGH_TEMP_ERR		BIT(3)
#घोषणा ERR_LOG_WDOG_TIMEOUT		BIT(4)
#घोषणा ERR_LOG_SYS_FAULT		BIT(5)
#घोषणा ERR_LOG_RAMDUMP			BIT(6)
#घोषणा ERR_LOG_COP_WDOG_TIMEOUT	BIT(7)
/* warnings */
#घोषणा ERR_LOG_MEM_ALLOC_FAIL		BIT(8)
#घोषणा ERR_LOG_LOW_TEMP_WARN		BIT(9)
#घोषणा ERR_LOG_ECC			BIT(10)
#घोषणा ERR_LOG_IPC_DWN			BIT(11)

/* Alert bit definitions detectd on host */
#घोषणा ERR_LOG_HOST_INTF_V_FAIL	BIT(13)
#घोषणा ERR_LOG_HOST_HB_FAIL		BIT(14)
#घोषणा ERR_LOG_HOST_PCIE_DWN		BIT(15)

#घोषणा BAR_CARD_ERR_MEM		0x468
/* defines क्रम mem err, all fields have same width */
#घोषणा BCM_VK_MEM_ERR_FIELD_MASK	0xff
#घोषणा BCM_VK_ECC_MEM_ERR_SHIFT	0
#घोषणा BCM_VK_UECC_MEM_ERR_SHIFT	8
/* threshold of event occurrence and logs start to come out */
#घोषणा BCM_VK_ECC_THRESHOLD		10
#घोषणा BCM_VK_UECC_THRESHOLD		1

#घोषणा BAR_CARD_PWR_AND_THRE		0x46c
/* defines क्रम घातer and temp threshold, all fields have same width */
#घोषणा BCM_VK_PWR_AND_THRE_FIELD_MASK	0xff
#घोषणा BCM_VK_LOW_TEMP_THRE_SHIFT	0
#घोषणा BCM_VK_HIGH_TEMP_THRE_SHIFT	8
#घोषणा BCM_VK_PWR_STATE_SHIFT		16

#घोषणा BAR_CARD_STATIC_INFO		0x470

#घोषणा BAR_INTF_VER			0x47c
#घोषणा BAR_INTF_VER_MAJOR_SHIFT	16
#घोषणा BAR_INTF_VER_MASK		0xffff
/*
 * major and minor semantic version numbers supported
 * Please update as required on पूर्णांकerface changes
 */
#घोषणा SEMANTIC_MAJOR			1
#घोषणा SEMANTIC_MINOR			0

/*
 * first करोor bell reg, ie क्रम queue = 0.  Only need the first one, as
 * we will use the queue number to derive the others
 */
#घोषणा VK_BAR0_REGSEG_DB_BASE		0x484
#घोषणा VK_BAR0_REGSEG_DB_REG_GAP	8 /*
					   * DB रेजिस्टर gap,
					   * DB1 at 0x48c and DB2 at 0x494
					   */

/* reset रेजिस्टर and specअगरic values */
#घोषणा VK_BAR0_RESET_DB_NUM		3
#घोषणा VK_BAR0_RESET_DB_SOFT		0xffffffff
#घोषणा VK_BAR0_RESET_DB_HARD		0xfffffffd
#घोषणा VK_BAR0_RESET_RAMPDUMP		0xa0000000

#घोषणा VK_BAR0_Q_DB_BASE(q_num)	(VK_BAR0_REGSEG_DB_BASE + \
					 ((q_num) * VK_BAR0_REGSEG_DB_REG_GAP))
#घोषणा VK_BAR0_RESET_DB_BASE		(VK_BAR0_REGSEG_DB_BASE + \
					 (VK_BAR0_RESET_DB_NUM * VK_BAR0_REGSEG_DB_REG_GAP))

#घोषणा BAR_BOOTSRC_SELECT		0xc78
/* BOOTSRC definitions */
#घोषणा BOOTSRC_SOFT_ENABLE		BIT(14)

/* Card OS Firmware version size */
#घोषणा BAR_FIRMWARE_TAG_SIZE		50
#घोषणा FIRMWARE_STATUS_PRE_INIT_DONE	0x1f

/* VK MSG_ID defines */
#घोषणा VK_MSG_ID_BITMAP_SIZE		4096
#घोषणा VK_MSG_ID_BITMAP_MASK		(VK_MSG_ID_BITMAP_SIZE - 1)
#घोषणा VK_MSG_ID_OVERFLOW		0xffff

/*
 * BAR1
 */

/* BAR1 message q definition */

/* indicate अगर msgq ctrl in BAR1 is populated */
#घोषणा VK_BAR1_MSGQ_DEF_RDY		0x60c0
/* पढ़ोy marker value क्रम the above location, normal boot2 */
#घोषणा VK_BAR1_MSGQ_RDY_MARKER		0xbeefcafe
/* पढ़ोy marker value क्रम the above location, normal boot2 */
#घोषणा VK_BAR1_DIAG_RDY_MARKER		0xdeadcafe
/* number of msgqs in BAR1 */
#घोषणा VK_BAR1_MSGQ_NR			0x60c4
/* BAR1 queue control काष्ठाure offset */
#घोषणा VK_BAR1_MSGQ_CTRL_OFF		0x60c8

/* BAR1 ucode and boot1 version tag */
#घोषणा VK_BAR1_UCODE_VER_TAG		0x6170
#घोषणा VK_BAR1_BOOT1_VER_TAG		0x61b0
#घोषणा VK_BAR1_VER_TAG_SIZE		64

/* Memory to hold the DMA buffer memory address allocated क्रम boot2 करोwnload */
#घोषणा VK_BAR1_DMA_BUF_OFF_HI		0x61e0
#घोषणा VK_BAR1_DMA_BUF_OFF_LO		(VK_BAR1_DMA_BUF_OFF_HI + 4)
#घोषणा VK_BAR1_DMA_BUF_SZ		(VK_BAR1_DMA_BUF_OFF_HI + 8)

/* Scratch memory allocated on host क्रम VK */
#घोषणा VK_BAR1_SCRATCH_OFF_HI		0x61f0
#घोषणा VK_BAR1_SCRATCH_OFF_LO		(VK_BAR1_SCRATCH_OFF_HI + 4)
#घोषणा VK_BAR1_SCRATCH_SZ_ADDR		(VK_BAR1_SCRATCH_OFF_HI + 8)
#घोषणा VK_BAR1_SCRATCH_DEF_NR_PAGES	32

/* BAR1 DAUTH info */
#घोषणा VK_BAR1_DAUTH_BASE_ADDR		0x6200
#घोषणा VK_BAR1_DAUTH_STORE_SIZE	0x48
#घोषणा VK_BAR1_DAUTH_VALID_SIZE	0x8
#घोषणा VK_BAR1_DAUTH_MAX		4
#घोषणा VK_BAR1_DAUTH_STORE_ADDR(x) \
		(VK_BAR1_DAUTH_BASE_ADDR + \
		 (x) * (VK_BAR1_DAUTH_STORE_SIZE + VK_BAR1_DAUTH_VALID_SIZE))
#घोषणा VK_BAR1_DAUTH_VALID_ADDR(x) \
		(VK_BAR1_DAUTH_STORE_ADDR(x) + VK_BAR1_DAUTH_STORE_SIZE)

/* BAR1 SOTP AUTH and REVID info */
#घोषणा VK_BAR1_SOTP_REVID_BASE_ADDR	0x6340
#घोषणा VK_BAR1_SOTP_REVID_SIZE		0x10
#घोषणा VK_BAR1_SOTP_REVID_MAX		2
#घोषणा VK_BAR1_SOTP_REVID_ADDR(x) \
		(VK_BAR1_SOTP_REVID_BASE_ADDR + (x) * VK_BAR1_SOTP_REVID_SIZE)

/* VK device supports a maximum of 3 bars */
#घोषणा MAX_BAR	3

/* शेष number of msg blk क्रम inband SGL */
#घोषणा BCM_VK_DEF_IB_SGL_BLK_LEN	 16
#घोषणा BCM_VK_IB_SGL_BLK_MAX		 24

क्रमागत pci_barno अणु
	BAR_0 = 0,
	BAR_1,
	BAR_2
पूर्ण;

#अगर_घोषित CONFIG_BCM_VK_TTY
#घोषणा BCM_VK_NUM_TTY 2
#अन्यथा
#घोषणा BCM_VK_NUM_TTY 0
#पूर्ण_अगर

काष्ठा bcm_vk_tty अणु
	काष्ठा tty_port port;
	u32 to_offset;	/* bar offset to use */
	u32 to_size;	/* to VK buffer size */
	u32 wr;		/* ग_लिखो offset shaकरोw */
	u32 from_offset;	/* bar offset to use */
	u32 from_size;	/* from VK buffer size */
	u32 rd;		/* पढ़ो offset shaकरोw */
	pid_t pid;
	bool irq_enabled;
	bool is_खोलोed;		/* tracks tty खोलो/बंद */
पूर्ण;

/* VK device max घातer state, supports 3, full, reduced and low */
#घोषणा MAX_OPP 3
#घोषणा MAX_CARD_INFO_TAG_SIZE 64

काष्ठा bcm_vk_card_info अणु
	u32 version;
	अक्षर os_tag[MAX_CARD_INFO_TAG_SIZE];
	अक्षर cmpt_tag[MAX_CARD_INFO_TAG_SIZE];
	u32 cpu_freq_mhz;
	u32 cpu_scale[MAX_OPP];
	u32 ddr_freq_mhz;
	u32 ddr_size_MB;
	u32 video_core_freq_mhz;
पूर्ण;

/* DAUTH related info */
काष्ठा bcm_vk_dauth_key अणु
	अक्षर store[VK_BAR1_DAUTH_STORE_SIZE];
	अक्षर valid[VK_BAR1_DAUTH_VALID_SIZE];
पूर्ण;

काष्ठा bcm_vk_dauth_info अणु
	काष्ठा bcm_vk_dauth_key keys[VK_BAR1_DAUTH_MAX];
पूर्ण;

/*
 * Control काष्ठाure of logging messages from the card.  This
 * buffer is क्रम logmsg that comes from vk
 */
काष्ठा bcm_vk_peer_log अणु
	u32 rd_idx;
	u32 wr_idx;
	u32 buf_size;
	u32 mask;
	अक्षर data[0];
पूर्ण;

/* max buf size allowed */
#घोषणा BCM_VK_PEER_LOG_BUF_MAX SZ_16K
/* max size per line of peer log */
#घोषणा BCM_VK_PEER_LOG_LINE_MAX  256

/*
 * single entry क्रम processing type + utilization
 */
#घोषणा BCM_VK_PROC_TYPE_TAG_LEN 8
काष्ठा bcm_vk_proc_mon_entry_t अणु
	अक्षर tag[BCM_VK_PROC_TYPE_TAG_LEN];
	u32 used;
	u32 max; /**< max capacity */
पूर्ण;

/**
 * Structure क्रम run समय utilization
 */
#घोषणा BCM_VK_PROC_MON_MAX 8 /* max entries supported */
काष्ठा bcm_vk_proc_mon_info अणु
	u32 num; /**< no of entries */
	u32 entry_size; /**< per entry size */
	काष्ठा bcm_vk_proc_mon_entry_t entries[BCM_VK_PROC_MON_MAX];
पूर्ण;

काष्ठा bcm_vk_hb_ctrl अणु
	काष्ठा समयr_list समयr;
	u32 last_upसमय;
	u32 lost_cnt;
पूर्ण;

काष्ठा bcm_vk_alert अणु
	u16 flags;
	u16 notfs;
पूर्ण;

/* some alert counters that the driver will keep track */
काष्ठा bcm_vk_alert_cnts अणु
	u16 ecc;
	u16 uecc;
पूर्ण;

काष्ठा bcm_vk अणु
	काष्ठा pci_dev *pdev;
	व्योम __iomem *bar[MAX_BAR];
	पूर्णांक num_irqs;

	काष्ठा bcm_vk_card_info card_info;
	काष्ठा bcm_vk_proc_mon_info proc_mon_info;
	काष्ठा bcm_vk_dauth_info dauth_info;

	/* mutex to protect the ioctls */
	काष्ठा mutex mutex;
	काष्ठा miscdevice miscdev;
	पूर्णांक devid; /* dev id allocated */

#अगर_घोषित CONFIG_BCM_VK_TTY
	काष्ठा tty_driver *tty_drv;
	काष्ठा समयr_list serial_समयr;
	काष्ठा bcm_vk_tty tty[BCM_VK_NUM_TTY];
	काष्ठा workqueue_काष्ठा *tty_wq_thपढ़ो;
	काष्ठा work_काष्ठा tty_wq_work;
#पूर्ण_अगर

	/* Reference-counting to handle file operations */
	काष्ठा kref kref;

	spinlock_t msg_id_lock; /* Spinlock क्रम msg_id */
	u16 msg_id;
	DECLARE_BITMAP(bmap, VK_MSG_ID_BITMAP_SIZE);
	spinlock_t ctx_lock; /* Spinlock क्रम component context */
	काष्ठा bcm_vk_ctx ctx[VK_CMPT_CTX_MAX];
	काष्ठा bcm_vk_ht_entry pid_ht[VK_PID_HT_SZ];
	pid_t reset_pid; /* process that issue reset */

	atomic_t msgq_inited; /* indicate अगर info has been synced with vk */
	काष्ठा bcm_vk_msg_chan to_v_msg_chan;
	काष्ठा bcm_vk_msg_chan to_h_msg_chan;

	काष्ठा workqueue_काष्ठा *wq_thपढ़ो;
	काष्ठा work_काष्ठा wq_work; /* work queue क्रम deferred job */
	अचिन्हित दीर्घ wq_offload[1]; /* various flags on wq requested */
	व्योम *tdma_vaddr; /* test dma segment भव addr */
	dma_addr_t tdma_addr; /* test dma segment bus addr */

	काष्ठा notअगरier_block panic_nb;
	u32 ib_sgl_size; /* size allocated क्रम inband sgl insertion */

	/* heart beat mechanism control काष्ठाure */
	काष्ठा bcm_vk_hb_ctrl hb_ctrl;
	/* house-keeping variable of error logs */
	spinlock_t host_alert_lock; /* protection to access host_alert काष्ठा */
	काष्ठा bcm_vk_alert host_alert;
	काष्ठा bcm_vk_alert peer_alert; /* bits set by the card */
	काष्ठा bcm_vk_alert_cnts alert_cnts;

	/* offset of the peer log control in BAR2 */
	u32 peerlog_off;
	काष्ठा bcm_vk_peer_log peerlog_info; /* record of peer log info */
	/* offset of processing monitoring info in BAR2 */
	u32 proc_mon_off;
पूर्ण;

/* wq offload work items bits definitions */
क्रमागत bcm_vk_wq_offload_flags अणु
	BCM_VK_WQ_DWNLD_PEND = 0,
	BCM_VK_WQ_DWNLD_AUTO = 1,
	BCM_VK_WQ_NOTF_PEND  = 2,
पूर्ण;

/* a macro to get an inभागidual field with mask and shअगरt */
#घोषणा BCM_VK_EXTRACT_FIELD(_field, _reg, _mask, _shअगरt) \
		(_field = (((_reg) >> (_shअगरt)) & (_mask)))

काष्ठा bcm_vk_entry अणु
	स्थिर u32 mask;
	स्थिर u32 exp_val;
	स्थिर अक्षर *str;
पूर्ण;

/* alerts that could be generated from peer */
#घोषणा BCM_VK_PEER_ERR_NUM 12
बाह्य काष्ठा bcm_vk_entry स्थिर bcm_vk_peer_err[BCM_VK_PEER_ERR_NUM];
/* alerts detected by the host */
#घोषणा BCM_VK_HOST_ERR_NUM 3
बाह्य काष्ठा bcm_vk_entry स्थिर bcm_vk_host_err[BCM_VK_HOST_ERR_NUM];

/*
 * check अगर PCIe पूर्णांकerface is करोwn on पढ़ो.  Use it when it is
 * certain that _val should never be all ones.
 */
#घोषणा BCM_VK_INTF_IS_DOWN(val) ((val) == 0xffffffff)

अटल अंतरभूत u32 vkपढ़ो32(काष्ठा bcm_vk *vk, क्रमागत pci_barno bar, u64 offset)
अणु
	वापस पढ़ोl(vk->bar[bar] + offset);
पूर्ण

अटल अंतरभूत व्योम vkग_लिखो32(काष्ठा bcm_vk *vk,
			     u32 value,
			     क्रमागत pci_barno bar,
			     u64 offset)
अणु
	ग_लिखोl(value, vk->bar[bar] + offset);
पूर्ण

अटल अंतरभूत u8 vkपढ़ो8(काष्ठा bcm_vk *vk, क्रमागत pci_barno bar, u64 offset)
अणु
	वापस पढ़ोb(vk->bar[bar] + offset);
पूर्ण

अटल अंतरभूत व्योम vkग_लिखो8(काष्ठा bcm_vk *vk,
			    u8 value,
			    क्रमागत pci_barno bar,
			    u64 offset)
अणु
	ग_लिखोb(value, vk->bar[bar] + offset);
पूर्ण

अटल अंतरभूत bool bcm_vk_msgq_marker_valid(काष्ठा bcm_vk *vk)
अणु
	u32 rdy_marker = 0;
	u32 fw_status;

	fw_status = vkपढ़ो32(vk, BAR_0, VK_BAR_FWSTS);

	अगर ((fw_status & VK_FWSTS_READY) == VK_FWSTS_READY)
		rdy_marker = vkपढ़ो32(vk, BAR_1, VK_BAR1_MSGQ_DEF_RDY);

	वापस (rdy_marker == VK_BAR1_MSGQ_RDY_MARKER);
पूर्ण

पूर्णांक bcm_vk_खोलो(काष्ठा inode *inode, काष्ठा file *p_file);
sमाप_प्रकार bcm_vk_पढ़ो(काष्ठा file *p_file, अक्षर __user *buf, माप_प्रकार count,
		    loff_t *f_pos);
sमाप_प्रकार bcm_vk_ग_लिखो(काष्ठा file *p_file, स्थिर अक्षर __user *buf,
		     माप_प्रकार count, loff_t *f_pos);
__poll_t bcm_vk_poll(काष्ठा file *p_file, काष्ठा poll_table_काष्ठा *रुको);
पूर्णांक bcm_vk_release(काष्ठा inode *inode, काष्ठा file *p_file);
व्योम bcm_vk_release_data(काष्ठा kref *kref);
irqवापस_t bcm_vk_msgq_irqhandler(पूर्णांक irq, व्योम *dev_id);
irqवापस_t bcm_vk_notf_irqhandler(पूर्णांक irq, व्योम *dev_id);
irqवापस_t bcm_vk_tty_irqhandler(पूर्णांक irq, व्योम *dev_id);
पूर्णांक bcm_vk_msg_init(काष्ठा bcm_vk *vk);
व्योम bcm_vk_msg_हटाओ(काष्ठा bcm_vk *vk);
व्योम bcm_vk_drain_msg_on_reset(काष्ठा bcm_vk *vk);
पूर्णांक bcm_vk_sync_msgq(काष्ठा bcm_vk *vk, bool क्रमce_sync);
व्योम bcm_vk_blk_drv_access(काष्ठा bcm_vk *vk);
s32 bcm_to_h_msg_dequeue(काष्ठा bcm_vk *vk);
पूर्णांक bcm_vk_send_shutकरोwn_msg(काष्ठा bcm_vk *vk, u32 shut_type,
			     स्थिर pid_t pid, स्थिर u32 q_num);
व्योम bcm_to_v_q_करोorbell(काष्ठा bcm_vk *vk, u32 q_num, u32 db_val);
पूर्णांक bcm_vk_स्वतः_load_all_images(काष्ठा bcm_vk *vk);
व्योम bcm_vk_hb_init(काष्ठा bcm_vk *vk);
व्योम bcm_vk_hb_deinit(काष्ठा bcm_vk *vk);
व्योम bcm_vk_handle_notf(काष्ठा bcm_vk *vk);
bool bcm_vk_drv_access_ok(काष्ठा bcm_vk *vk);
व्योम bcm_vk_set_host_alert(काष्ठा bcm_vk *vk, u32 bit_mask);

#अगर_घोषित CONFIG_BCM_VK_TTY
पूर्णांक bcm_vk_tty_init(काष्ठा bcm_vk *vk, अक्षर *name);
व्योम bcm_vk_tty_निकास(काष्ठा bcm_vk *vk);
व्योम bcm_vk_tty_terminate_tty_user(काष्ठा bcm_vk *vk);
व्योम bcm_vk_tty_wq_निकास(काष्ठा bcm_vk *vk);

अटल अंतरभूत व्योम bcm_vk_tty_set_irq_enabled(काष्ठा bcm_vk *vk, पूर्णांक index)
अणु
	vk->tty[index].irq_enabled = true;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक bcm_vk_tty_init(काष्ठा bcm_vk *vk, अक्षर *name)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम bcm_vk_tty_निकास(काष्ठा bcm_vk *vk)
अणु
पूर्ण

अटल अंतरभूत व्योम bcm_vk_tty_terminate_tty_user(काष्ठा bcm_vk *vk)
अणु
पूर्ण

अटल अंतरभूत व्योम bcm_vk_tty_wq_निकास(काष्ठा bcm_vk *vk)
अणु
पूर्ण

अटल अंतरभूत व्योम bcm_vk_tty_set_irq_enabled(काष्ठा bcm_vk *vk, पूर्णांक index)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_BCM_VK_TTY */

#पूर्ण_अगर
