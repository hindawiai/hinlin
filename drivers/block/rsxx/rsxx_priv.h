<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
* Filename: rsxx_priv.h
*
* Authors: Joshua Morris <josh.h.morris@us.ibm.com>
*	Philip Kelleher <pjk1939@linux.vnet.ibm.com>
*
* (C) Copyright 2013 IBM Corporation
*/

#अगर_अघोषित __RSXX_PRIV_H__
#घोषणा __RSXX_PRIV_H__

#समावेश <linux/semaphore.h>

#समावेश <linux/fs.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mutex.h>
#समावेश <linux/pci.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/bपन.स>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/समयr.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/delay.h>

#समावेश "rsxx.h"
#समावेश "rsxx_cfg.h"

काष्ठा proc_cmd;

#घोषणा PCI_DEVICE_ID_FS70_FLASH	0x04A9
#घोषणा PCI_DEVICE_ID_FS80_FLASH	0x04AA

#घोषणा RS70_PCI_REV_SUPPORTED	4

#घोषणा DRIVER_NAME "rsxx"
#घोषणा DRIVER_VERSION "4.0.3.2516"

/* Block size is 4096 */
#घोषणा RSXX_HW_BLK_SHIFT		12
#घोषणा RSXX_HW_BLK_SIZE		(1 << RSXX_HW_BLK_SHIFT)
#घोषणा RSXX_HW_BLK_MASK		(RSXX_HW_BLK_SIZE - 1)

#घोषणा MAX_CREG_DATA8	32
#घोषणा LOG_BUF_SIZE8	128

#घोषणा RSXX_MAX_OUTSTANDING_CMDS	255
#घोषणा RSXX_CS_IDX_MASK		0xff

#घोषणा STATUS_BUFFER_SIZE8     4096
#घोषणा COMMAND_BUFFER_SIZE8    4096

#घोषणा RSXX_MAX_TARGETS	8

काष्ठा dma_tracker_list;

/* DMA Command/Status Buffer काष्ठाure */
काष्ठा rsxx_cs_buffer अणु
	dma_addr_t	dma_addr;
	व्योम		*buf;
	u32		idx;
पूर्ण;

काष्ठा rsxx_dma_stats अणु
	u32 crc_errors;
	u32 hard_errors;
	u32 soft_errors;
	u32 ग_लिखोs_issued;
	u32 ग_लिखोs_failed;
	u32 पढ़ोs_issued;
	u32 पढ़ोs_failed;
	u32 पढ़ोs_retried;
	u32 discards_issued;
	u32 discards_failed;
	u32 करोne_rescheduled;
	u32 issue_rescheduled;
	u32 dma_sw_err;
	u32 dma_hw_fault;
	u32 dma_cancelled;
	u32 sw_q_depth;		/* Number of DMAs on the SW queue. */
	atomic_t hw_q_depth;	/* Number of DMAs queued to HW. */
पूर्ण;

काष्ठा rsxx_dma_ctrl अणु
	काष्ठा rsxx_cardinfo		*card;
	पूर्णांक				id;
	व्योम				__iomem *regmap;
	काष्ठा rsxx_cs_buffer		status;
	काष्ठा rsxx_cs_buffer		cmd;
	u16				e_cnt;
	spinlock_t			queue_lock;
	काष्ठा list_head		queue;
	काष्ठा workqueue_काष्ठा		*issue_wq;
	काष्ठा work_काष्ठा		issue_dma_work;
	काष्ठा workqueue_काष्ठा		*करोne_wq;
	काष्ठा work_काष्ठा		dma_करोne_work;
	काष्ठा समयr_list		activity_समयr;
	काष्ठा dma_tracker_list		*trackers;
	काष्ठा rsxx_dma_stats		stats;
	काष्ठा mutex			work_lock;
पूर्ण;

काष्ठा rsxx_cardinfo अणु
	काष्ठा pci_dev		*dev;
	अचिन्हित पूर्णांक		halt;
	अचिन्हित पूर्णांक		eeh_state;

	व्योम			__iomem *regmap;
	spinlock_t		irq_lock;
	अचिन्हित पूर्णांक		isr_mask;
	अचिन्हित पूर्णांक		ier_mask;

	काष्ठा rsxx_card_cfg	config;
	पूर्णांक			config_valid;

	/* Embedded CPU Communication */
	काष्ठा अणु
		spinlock_t		lock;
		bool			active;
		काष्ठा creg_cmd		*active_cmd;
		काष्ठा workqueue_काष्ठा	*creg_wq;
		काष्ठा work_काष्ठा	करोne_work;
		काष्ठा list_head	queue;
		अचिन्हित पूर्णांक		q_depth;
		/* Cache the creg status to prevent ioपढ़ोs */
		काष्ठा अणु
			u32		stat;
			u32		failed_cancel_समयr;
			u32		creg_समयout;
		पूर्ण creg_stats;
		काष्ठा समयr_list	cmd_समयr;
		काष्ठा mutex		reset_lock;
		पूर्णांक			reset;
	पूर्ण creg_ctrl;

	काष्ठा अणु
		अक्षर पंचांगp[MAX_CREG_DATA8];
		अक्षर buf[LOG_BUF_SIZE8]; /* terminated */
		पूर्णांक buf_len;
	पूर्ण log;

	काष्ठा workqueue_काष्ठा	*event_wq;
	काष्ठा work_काष्ठा	event_work;
	अचिन्हित पूर्णांक		state;
	u64			size8;

	/* Lock the device attach/detach function */
	काष्ठा mutex		dev_lock;

	/* Block Device Variables */
	bool			bdev_attached;
	पूर्णांक			disk_id;
	पूर्णांक			major;
	काष्ठा request_queue	*queue;
	काष्ठा gendisk		*gendisk;
	काष्ठा अणु
		/* Used to convert a byte address to a device address. */
		u64 lower_mask;
		u64 upper_shअगरt;
		u64 upper_mask;
		u64 target_mask;
		u64 target_shअगरt;
	पूर्ण _stripe;
	अचिन्हित पूर्णांक		dma_fault;

	पूर्णांक			scrub_hard;

	पूर्णांक			n_tarमाला_लो;
	काष्ठा rsxx_dma_ctrl	*ctrl;

	काष्ठा dentry		*debugfs_dir;
पूर्ण;

क्रमागत rsxx_pci_regmap अणु
	HWID		= 0x00,	/* Hardware Identअगरication Register */
	SCRATCH		= 0x04, /* Scratch/Debug Register */
	RESET		= 0x08, /* Reset Register */
	ISR		= 0x10, /* Interrupt Status Register */
	IER		= 0x14, /* Interrupt Enable Register */
	IPR		= 0x18, /* Interrupt Poll Register */
	CB_ADD_LO	= 0x20, /* Command Host Buffer Address [31:0] */
	CB_ADD_HI	= 0x24, /* Command Host Buffer Address [63:32]*/
	HW_CMD_IDX	= 0x28, /* Hardware Processed Command Index */
	SW_CMD_IDX	= 0x2C, /* Software Processed Command Index */
	SB_ADD_LO	= 0x30, /* Status Host Buffer Address [31:0] */
	SB_ADD_HI	= 0x34, /* Status Host Buffer Address [63:32] */
	HW_STATUS_CNT	= 0x38, /* Hardware Status Counter */
	SW_STATUS_CNT	= 0x3C, /* Deprecated */
	CREG_CMD	= 0x40, /* CPU Command Register */
	CREG_ADD	= 0x44, /* CPU Address Register */
	CREG_CNT	= 0x48, /* CPU Count Register */
	CREG_STAT	= 0x4C, /* CPU Status Register */
	CREG_DATA0	= 0x50, /* CPU Data Registers */
	CREG_DATA1	= 0x54,
	CREG_DATA2	= 0x58,
	CREG_DATA3	= 0x5C,
	CREG_DATA4	= 0x60,
	CREG_DATA5	= 0x64,
	CREG_DATA6	= 0x68,
	CREG_DATA7	= 0x6c,
	INTR_COAL	= 0x70, /* Interrupt Coalescing Register */
	HW_ERROR	= 0x74, /* Card Error Register */
	PCI_DEBUG0	= 0x78, /* PCI Debug Registers */
	PCI_DEBUG1	= 0x7C,
	PCI_DEBUG2	= 0x80,
	PCI_DEBUG3	= 0x84,
	PCI_DEBUG4	= 0x88,
	PCI_DEBUG5	= 0x8C,
	PCI_DEBUG6	= 0x90,
	PCI_DEBUG7	= 0x94,
	PCI_POWER_THROTTLE = 0x98,
	PERF_CTRL	= 0x9c,
	PERF_TIMER_LO	= 0xa0,
	PERF_TIMER_HI	= 0xa4,
	PERF_RD512_LO	= 0xa8,
	PERF_RD512_HI	= 0xac,
	PERF_WR512_LO	= 0xb0,
	PERF_WR512_HI	= 0xb4,
	PCI_RECONFIG	= 0xb8,
पूर्ण;

क्रमागत rsxx_पूर्णांकr अणु
	CR_INTR_DMA0	= 0x00000001,
	CR_INTR_CREG	= 0x00000002,
	CR_INTR_DMA1	= 0x00000004,
	CR_INTR_EVENT	= 0x00000008,
	CR_INTR_DMA2	= 0x00000010,
	CR_INTR_DMA3	= 0x00000020,
	CR_INTR_DMA4	= 0x00000040,
	CR_INTR_DMA5	= 0x00000080,
	CR_INTR_DMA6	= 0x00000100,
	CR_INTR_DMA7	= 0x00000200,
	CR_INTR_ALL_C	= 0x0000003f,
	CR_INTR_ALL_G	= 0x000003ff,
	CR_INTR_DMA_ALL = 0x000003f5,
	CR_INTR_ALL	= 0xffffffff,
पूर्ण;

अटल अंतरभूत पूर्णांक CR_INTR_DMA(पूर्णांक N)
अणु
	अटल स्थिर अचिन्हित पूर्णांक _CR_INTR_DMA[] = अणु
		CR_INTR_DMA0, CR_INTR_DMA1, CR_INTR_DMA2, CR_INTR_DMA3,
		CR_INTR_DMA4, CR_INTR_DMA5, CR_INTR_DMA6, CR_INTR_DMA7
	पूर्ण;
	वापस _CR_INTR_DMA[N];
पूर्ण
क्रमागत rsxx_pci_reset अणु
	DMA_QUEUE_RESET		= 0x00000001,
पूर्ण;

क्रमागत rsxx_hw_fअगरo_flush अणु
	RSXX_FLUSH_BUSY		= 0x00000002,
	RSXX_FLUSH_TIMEOUT	= 0x00000004,
पूर्ण;

क्रमागत rsxx_pci_revision अणु
	RSXX_DISCARD_SUPPORT = 2,
	RSXX_EEH_SUPPORT     = 3,
पूर्ण;

क्रमागत rsxx_creg_cmd अणु
	CREG_CMD_TAG_MASK	= 0x0000FF00,
	CREG_OP_WRITE		= 0x000000C0,
	CREG_OP_READ		= 0x000000E0,
पूर्ण;

क्रमागत rsxx_creg_addr अणु
	CREG_ADD_CARD_CMD		= 0x80001000,
	CREG_ADD_CARD_STATE		= 0x80001004,
	CREG_ADD_CARD_SIZE		= 0x8000100c,
	CREG_ADD_CAPABILITIES		= 0x80001050,
	CREG_ADD_LOG			= 0x80002000,
	CREG_ADD_NUM_TARGETS		= 0x80003000,
	CREG_ADD_CRAM			= 0xA0000000,
	CREG_ADD_CONFIG			= 0xB0000000,
पूर्ण;

क्रमागत rsxx_creg_card_cmd अणु
	CARD_CMD_STARTUP		= 1,
	CARD_CMD_SHUTDOWN		= 2,
	CARD_CMD_LOW_LEVEL_FORMAT	= 3,
	CARD_CMD_FPGA_RECONFIG_BR	= 4,
	CARD_CMD_FPGA_RECONFIG_MAIN	= 5,
	CARD_CMD_BACKUP			= 6,
	CARD_CMD_RESET			= 7,
	CARD_CMD_deprecated		= 8,
	CARD_CMD_UNINITIALIZE		= 9,
	CARD_CMD_DSTROY_EMERGENCY	= 10,
	CARD_CMD_DSTROY_NORMAL		= 11,
	CARD_CMD_DSTROY_EXTENDED	= 12,
	CARD_CMD_DSTROY_ABORT		= 13,
पूर्ण;

क्रमागत rsxx_card_state अणु
	CARD_STATE_SHUTDOWN		= 0x00000001,
	CARD_STATE_STARTING		= 0x00000002,
	CARD_STATE_FORMATTING		= 0x00000004,
	CARD_STATE_UNINITIALIZED	= 0x00000008,
	CARD_STATE_GOOD			= 0x00000010,
	CARD_STATE_SHUTTING_DOWN	= 0x00000020,
	CARD_STATE_FAULT		= 0x00000040,
	CARD_STATE_RD_ONLY_FAULT	= 0x00000080,
	CARD_STATE_DSTROYING		= 0x00000100,
पूर्ण;

क्रमागत rsxx_led अणु
	LED_DEFAULT	= 0x0,
	LED_IDENTIFY	= 0x1,
	LED_SOAK	= 0x2,
पूर्ण;

क्रमागत rsxx_creg_flash_lock अणु
	CREG_FLASH_LOCK		= 1,
	CREG_FLASH_UNLOCK	= 2,
पूर्ण;

क्रमागत rsxx_card_capabilities अणु
	CARD_CAP_SUBPAGE_WRITES = 0x00000080,
पूर्ण;

क्रमागत rsxx_creg_stat अणु
	CREG_STAT_STATUS_MASK	= 0x00000003,
	CREG_STAT_SUCCESS	= 0x1,
	CREG_STAT_ERROR		= 0x2,
	CREG_STAT_CHAR_PENDING	= 0x00000004, /* Character I/O pending bit */
	CREG_STAT_LOG_PENDING	= 0x00000008, /* HW log message pending bit */
	CREG_STAT_TAG_MASK	= 0x0000ff00,
पूर्ण;

क्रमागत rsxx_dma_finish अणु
	FREE_DMA	= 0x0,
	COMPLETE_DMA	= 0x1,
पूर्ण;

अटल अंतरभूत अचिन्हित पूर्णांक CREG_DATA(पूर्णांक N)
अणु
	वापस CREG_DATA0 + (N << 2);
पूर्ण

/*----------------- Convenient Log Wrappers -------------------*/
#घोषणा CARD_TO_DEV(__CARD)	(&(__CARD)->dev->dev)

/***** config.c *****/
पूर्णांक rsxx_load_config(काष्ठा rsxx_cardinfo *card);

/***** core.c *****/
व्योम rsxx_enable_ier(काष्ठा rsxx_cardinfo *card, अचिन्हित पूर्णांक पूर्णांकr);
व्योम rsxx_disable_ier(काष्ठा rsxx_cardinfo *card, अचिन्हित पूर्णांक पूर्णांकr);
व्योम rsxx_enable_ier_and_isr(काष्ठा rsxx_cardinfo *card,
				 अचिन्हित पूर्णांक पूर्णांकr);
व्योम rsxx_disable_ier_and_isr(काष्ठा rsxx_cardinfo *card,
				  अचिन्हित पूर्णांक पूर्णांकr);

/***** dev.c *****/
पूर्णांक rsxx_attach_dev(काष्ठा rsxx_cardinfo *card);
व्योम rsxx_detach_dev(काष्ठा rsxx_cardinfo *card);
पूर्णांक rsxx_setup_dev(काष्ठा rsxx_cardinfo *card);
व्योम rsxx_destroy_dev(काष्ठा rsxx_cardinfo *card);
पूर्णांक rsxx_dev_init(व्योम);
व्योम rsxx_dev_cleanup(व्योम);

/***** dma.c ****/
प्रकार व्योम (*rsxx_dma_cb)(काष्ठा rsxx_cardinfo *card,
				व्योम *cb_data,
				अचिन्हित पूर्णांक status);
पूर्णांक rsxx_dma_setup(काष्ठा rsxx_cardinfo *card);
व्योम rsxx_dma_destroy(काष्ठा rsxx_cardinfo *card);
पूर्णांक rsxx_dma_init(व्योम);
पूर्णांक rsxx_cleanup_dma_queue(काष्ठा rsxx_dma_ctrl *ctrl,
				काष्ठा list_head *q,
				अचिन्हित पूर्णांक करोne);
पूर्णांक rsxx_dma_cancel(काष्ठा rsxx_dma_ctrl *ctrl);
व्योम rsxx_dma_cleanup(व्योम);
व्योम rsxx_dma_queue_reset(काष्ठा rsxx_cardinfo *card);
पूर्णांक rsxx_dma_configure(काष्ठा rsxx_cardinfo *card);
blk_status_t rsxx_dma_queue_bio(काष्ठा rsxx_cardinfo *card,
			   काष्ठा bio *bio,
			   atomic_t *n_dmas,
			   rsxx_dma_cb cb,
			   व्योम *cb_data);
पूर्णांक rsxx_hw_buffers_init(काष्ठा pci_dev *dev, काष्ठा rsxx_dma_ctrl *ctrl);
पूर्णांक rsxx_eeh_save_issued_dmas(काष्ठा rsxx_cardinfo *card);
पूर्णांक rsxx_eeh_remap_dmas(काष्ठा rsxx_cardinfo *card);

/***** cregs.c *****/
पूर्णांक rsxx_creg_ग_लिखो(काष्ठा rsxx_cardinfo *card, u32 addr,
			अचिन्हित पूर्णांक size8,
			व्योम *data,
			पूर्णांक byte_stream);
पूर्णांक rsxx_creg_पढ़ो(काष्ठा rsxx_cardinfo *card,
		       u32 addr,
		       अचिन्हित पूर्णांक size8,
		       व्योम *data,
		       पूर्णांक byte_stream);
पूर्णांक rsxx_पढ़ो_hw_log(काष्ठा rsxx_cardinfo *card);
पूर्णांक rsxx_get_card_state(काष्ठा rsxx_cardinfo *card,
			    अचिन्हित पूर्णांक *state);
पूर्णांक rsxx_get_card_size8(काष्ठा rsxx_cardinfo *card, u64 *size8);
पूर्णांक rsxx_get_num_tarमाला_लो(काष्ठा rsxx_cardinfo *card,
			     अचिन्हित पूर्णांक *n_tarमाला_लो);
पूर्णांक rsxx_get_card_capabilities(काष्ठा rsxx_cardinfo *card,
				   u32 *capabilities);
पूर्णांक rsxx_issue_card_cmd(काष्ठा rsxx_cardinfo *card, u32 cmd);
पूर्णांक rsxx_creg_setup(काष्ठा rsxx_cardinfo *card);
व्योम rsxx_creg_destroy(काष्ठा rsxx_cardinfo *card);
पूर्णांक rsxx_creg_init(व्योम);
व्योम rsxx_creg_cleanup(व्योम);
पूर्णांक rsxx_reg_access(काष्ठा rsxx_cardinfo *card,
			काष्ठा rsxx_reg_access __user *ucmd,
			पूर्णांक पढ़ो);
व्योम rsxx_eeh_save_issued_creg(काष्ठा rsxx_cardinfo *card);
व्योम rsxx_kick_creg_queue(काष्ठा rsxx_cardinfo *card);



#पूर्ण_अगर /* __DRIVERS_BLOCK_RSXX_H__ */
