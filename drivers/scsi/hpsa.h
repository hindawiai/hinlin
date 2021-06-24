<शैली गुरु>
/*
 *    Disk Array driver क्रम HP Smart Array SAS controllers
 *    Copyright (c) 2019-2020 Microchip Technology Inc. and its subsidiaries
 *    Copyright 2016 Microsemi Corporation
 *    Copyright 2014-2015 PMC-Sierra, Inc.
 *    Copyright 2000,2009-2015 Hewlett-Packard Development Company, L.P.
 *
 *    This program is मुक्त software; you can redistribute it and/or modअगरy
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; version 2 of the License.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or
 *    NON INFRINGEMENT.  See the GNU General Public License क्रम more details.
 *
 *    Questions/Comments/Bugfixes to esc.storagedev@microsemi.com
 *
 */
#अगर_अघोषित HPSA_H
#घोषणा HPSA_H

#समावेश <scsi/scsicam.h>

#घोषणा IO_OK		0
#घोषणा IO_ERROR	1

काष्ठा ctlr_info;

काष्ठा access_method अणु
	व्योम (*submit_command)(काष्ठा ctlr_info *h,
		काष्ठा CommandList *c);
	व्योम (*set_पूर्णांकr_mask)(काष्ठा ctlr_info *h, अचिन्हित दीर्घ val);
	bool (*पूर्णांकr_pending)(काष्ठा ctlr_info *h);
	अचिन्हित दीर्घ (*command_completed)(काष्ठा ctlr_info *h, u8 q);
पूर्ण;

/* क्रम SAS hosts and SAS expanders */
काष्ठा hpsa_sas_node अणु
	काष्ठा device *parent_dev;
	काष्ठा list_head port_list_head;
पूर्ण;

काष्ठा hpsa_sas_port अणु
	काष्ठा list_head port_list_entry;
	u64 sas_address;
	काष्ठा sas_port *port;
	पूर्णांक next_phy_index;
	काष्ठा list_head phy_list_head;
	काष्ठा hpsa_sas_node *parent_node;
	काष्ठा sas_rphy *rphy;
पूर्ण;

काष्ठा hpsa_sas_phy अणु
	काष्ठा list_head phy_list_entry;
	काष्ठा sas_phy *phy;
	काष्ठा hpsa_sas_port *parent_port;
	bool added_to_port;
पूर्ण;

#घोषणा EXTERNAL_QD 128
काष्ठा hpsa_scsi_dev_t अणु
	अचिन्हित पूर्णांक devtype;
	पूर्णांक bus, target, lun;		/* as presented to the OS */
	अचिन्हित अक्षर scsi3addr[8];	/* as presented to the HW */
	u8 physical_device : 1;
	u8 expose_device;
	u8 हटाओd : 1;			/* device is marked क्रम death */
	u8 was_हटाओd : 1;		/* device actually हटाओd */
#घोषणा RAID_CTLR_LUNID "\0\0\0\0\0\0\0\0"
	अचिन्हित अक्षर device_id[16];    /* from inquiry pg. 0x83 */
	u64 sas_address;
	u64 eli;			/* from report diags. */
	अचिन्हित अक्षर venकरोr[8];        /* bytes 8-15 of inquiry data */
	अचिन्हित अक्षर model[16];        /* bytes 16-31 of inquiry data */
	अचिन्हित अक्षर rev;		/* byte 2 of inquiry data */
	अचिन्हित अक्षर raid_level;	/* from inquiry page 0xC1 */
	अचिन्हित अक्षर volume_offline;	/* discovered via TUR or VPD */
	u16 queue_depth;		/* max queue_depth क्रम this device */
	atomic_t commands_outstanding;	/* track commands sent to device */
	atomic_t ioaccel_cmds_out;	/* Only used क्रम physical devices
					 * counts commands sent to physical
					 * device via "ioaccel" path.
					 */
	bool in_reset;
	u32 ioaccel_handle;
	u8 active_path_index;
	u8 path_map;
	u8 bay;
	u8 box[8];
	u16 phys_connector[8];
	पूर्णांक offload_config;		/* I/O accel RAID offload configured */
	पूर्णांक offload_enabled;		/* I/O accel RAID offload enabled */
	पूर्णांक offload_to_be_enabled;
	पूर्णांक hba_ioaccel_enabled;
	पूर्णांक offload_to_mirror;		/* Send next I/O accelerator RAID
					 * offload request to mirror drive
					 */
	काष्ठा raid_map_data raid_map;	/* I/O accelerator RAID map */

	/*
	 * Poपूर्णांकers from logical drive map indices to the phys drives that
	 * make those logical drives.  Note, multiple logical drives may
	 * share physical drives.  You can have क्रम instance 5 physical
	 * drives with 3 logical drives each using those same 5 physical
	 * disks. We need these poपूर्णांकers क्रम counting i/o's out to physical
	 * devices in order to honor physical device queue depth limits.
	 */
	काष्ठा hpsa_scsi_dev_t *phys_disk[RAID_MAP_MAX_ENTRIES];
	पूर्णांक nphysical_disks;
	पूर्णांक supports_पातs;
	काष्ठा hpsa_sas_port *sas_port;
	पूर्णांक बाह्यal;   /* 1-from बाह्यal array 0-not <0-unknown */
पूर्ण;

काष्ठा reply_queue_buffer अणु
	u64 *head;
	माप_प्रकार size;
	u8 wraparound;
	u32 current_entry;
	dma_addr_t busaddr;
पूर्ण;

#आशय pack(1)
काष्ठा bmic_controller_parameters अणु
	u8   led_flags;
	u8   enable_command_list_verअगरication;
	u8   backed_out_ग_लिखो_drives;
	u16  stripes_क्रम_parity;
	u8   parity_distribution_mode_flags;
	u16  max_driver_requests;
	u16  elevator_trend_count;
	u8   disable_elevator;
	u8   क्रमce_scan_complete;
	u8   scsi_transfer_mode;
	u8   क्रमce_narrow;
	u8   rebuild_priority;
	u8   expand_priority;
	u8   host_sdb_asic_fix;
	u8   pdpi_burst_from_host_disabled;
	अक्षर software_name[64];
	अक्षर hardware_name[32];
	u8   bridge_revision;
	u8   snapshot_priority;
	u32  os_specअगरic;
	u8   post_prompt_समयout;
	u8   स्वतःmatic_drive_slamming;
	u8   reserved1;
	u8   nvram_flags;
	u8   cache_nvram_flags;
	u8   drive_config_flags;
	u16  reserved2;
	u8   temp_warning_level;
	u8   temp_shutकरोwn_level;
	u8   temp_condition_reset;
	u8   max_coalesce_commands;
	u32  max_coalesce_delay;
	u8   orca_password[4];
	u8   access_id[16];
	u8   reserved[356];
पूर्ण;
#आशय pack()

काष्ठा ctlr_info अणु
	अचिन्हित पूर्णांक *reply_map;
	पूर्णांक	ctlr;
	अक्षर	devname[8];
	अक्षर    *product_name;
	काष्ठा pci_dev *pdev;
	u32	board_id;
	u64	sas_address;
	व्योम __iomem *vaddr;
	अचिन्हित दीर्घ paddr;
	पूर्णांक 	nr_cmds; /* Number of commands allowed on this controller */
#घोषणा HPSA_CMDS_RESERVED_FOR_ABORTS 2
#घोषणा HPSA_CMDS_RESERVED_FOR_DRIVER 1
	काष्ठा CfgTable __iomem *cfgtable;
	पूर्णांक	पूर्णांकerrupts_enabled;
	पूर्णांक 	max_commands;
	पूर्णांक	last_collision_tag; /* tags are global */
	atomic_t commands_outstanding;
#	define PERF_MODE_INT	0
#	define DOORBELL_INT	1
#	define SIMPLE_MODE_INT	2
#	define MEMQ_MODE_INT	3
	अचिन्हित पूर्णांक msix_vectors;
	पूर्णांक पूर्णांकr_mode; /* either PERF_MODE_INT or SIMPLE_MODE_INT */
	काष्ठा access_method access;

	/* queue and queue Info */
	अचिन्हित पूर्णांक Qdepth;
	अचिन्हित पूर्णांक maxSG;
	spinlock_t lock;
	पूर्णांक maxsgentries;
	u8 max_cmd_sg_entries;
	पूर्णांक chainsize;
	काष्ठा SGDescriptor **cmd_sg_list;
	काष्ठा ioaccel2_sg_element **ioaccel2_cmd_sg_list;

	/* poपूर्णांकers to command and error info pool */
	काष्ठा CommandList 	*cmd_pool;
	dma_addr_t		cmd_pool_dhandle;
	काष्ठा io_accel1_cmd	*ioaccel_cmd_pool;
	dma_addr_t		ioaccel_cmd_pool_dhandle;
	काष्ठा io_accel2_cmd	*ioaccel2_cmd_pool;
	dma_addr_t		ioaccel2_cmd_pool_dhandle;
	काष्ठा ErrorInfo 	*errinfo_pool;
	dma_addr_t		errinfo_pool_dhandle;
	अचिन्हित दीर्घ  		*cmd_pool_bits;
	पूर्णांक			scan_finished;
	u8			scan_रुकोing : 1;
	spinlock_t		scan_lock;
	रुको_queue_head_t	scan_रुको_queue;

	काष्ठा Scsi_Host *scsi_host;
	spinlock_t devlock; /* to protect hba[ctlr]->dev[];  */
	पूर्णांक ndevices; /* number of used elements in .dev[] array. */
	काष्ठा hpsa_scsi_dev_t *dev[HPSA_MAX_DEVICES];
	/*
	 * Perक्रमmant mode tables.
	 */
	u32 trans_support;
	u32 trans_offset;
	काष्ठा TransTable_काष्ठा __iomem *transtable;
	अचिन्हित दीर्घ transMethod;

	/* cap concurrent passthrus at some reasonable maximum */
#घोषणा HPSA_MAX_CONCURRENT_PASSTHRUS (10)
	atomic_t passthru_cmds_avail;

	/*
	 * Perक्रमmant mode completion buffers
	 */
	माप_प्रकार reply_queue_size;
	काष्ठा reply_queue_buffer reply_queue[MAX_REPLY_QUEUES];
	u8 nreply_queues;
	u32 *blockFetchTable;
	u32 *ioaccel1_blockFetchTable;
	u32 *ioaccel2_blockFetchTable;
	u32 __iomem *ioaccel2_bft2_regs;
	अचिन्हित अक्षर *hba_inquiry_data;
	u32 driver_support;
	u32 fw_support;
	पूर्णांक ioaccel_support;
	पूर्णांक ioaccel_maxsg;
	u64 last_पूर्णांकr_बारtamp;
	u32 last_heartbeat;
	u64 last_heartbeat_बारtamp;
	u32 heartbeat_sample_पूर्णांकerval;
	atomic_t firmware_flash_in_progress;
	u32 __percpu *lockup_detected;
	काष्ठा delayed_work monitor_ctlr_work;
	काष्ठा delayed_work rescan_ctlr_work;
	काष्ठा delayed_work event_monitor_work;
	पूर्णांक हटाओ_in_progress;
	/* Address of h->q[x] is passed to पूर्णांकr handler to know which queue */
	u8 q[MAX_REPLY_QUEUES];
	अक्षर पूर्णांकrname[MAX_REPLY_QUEUES][16];	/* "hpsa0-msix00" names */
	u32 TMFSupportFlags; /* cache what task mgmt funcs are supported. */
#घोषणा HPSATMF_BITS_SUPPORTED  (1 << 0)
#घोषणा HPSATMF_PHYS_LUN_RESET  (1 << 1)
#घोषणा HPSATMF_PHYS_NEX_RESET  (1 << 2)
#घोषणा HPSATMF_PHYS_TASK_ABORT (1 << 3)
#घोषणा HPSATMF_PHYS_TSET_ABORT (1 << 4)
#घोषणा HPSATMF_PHYS_CLEAR_ACA  (1 << 5)
#घोषणा HPSATMF_PHYS_CLEAR_TSET (1 << 6)
#घोषणा HPSATMF_PHYS_QRY_TASK   (1 << 7)
#घोषणा HPSATMF_PHYS_QRY_TSET   (1 << 8)
#घोषणा HPSATMF_PHYS_QRY_ASYNC  (1 << 9)
#घोषणा HPSATMF_IOACCEL_ENABLED (1 << 15)
#घोषणा HPSATMF_MASK_SUPPORTED  (1 << 16)
#घोषणा HPSATMF_LOG_LUN_RESET   (1 << 17)
#घोषणा HPSATMF_LOG_NEX_RESET   (1 << 18)
#घोषणा HPSATMF_LOG_TASK_ABORT  (1 << 19)
#घोषणा HPSATMF_LOG_TSET_ABORT  (1 << 20)
#घोषणा HPSATMF_LOG_CLEAR_ACA   (1 << 21)
#घोषणा HPSATMF_LOG_CLEAR_TSET  (1 << 22)
#घोषणा HPSATMF_LOG_QRY_TASK    (1 << 23)
#घोषणा HPSATMF_LOG_QRY_TSET    (1 << 24)
#घोषणा HPSATMF_LOG_QRY_ASYNC   (1 << 25)
	u32 events;
#घोषणा CTLR_STATE_CHANGE_EVENT				(1 << 0)
#घोषणा CTLR_ENCLOSURE_HOT_PLUG_EVENT			(1 << 1)
#घोषणा CTLR_STATE_CHANGE_EVENT_PHYSICAL_DRV		(1 << 4)
#घोषणा CTLR_STATE_CHANGE_EVENT_LOGICAL_DRV		(1 << 5)
#घोषणा CTLR_STATE_CHANGE_EVENT_REDUNDANT_CNTRL		(1 << 6)
#घोषणा CTLR_STATE_CHANGE_EVENT_AIO_ENABLED_DISABLED	(1 << 30)
#घोषणा CTLR_STATE_CHANGE_EVENT_AIO_CONFIG_CHANGE	(1 << 31)

#घोषणा RESCAN_REQUIRED_EVENT_BITS \
		(CTLR_ENCLOSURE_HOT_PLUG_EVENT | \
		CTLR_STATE_CHANGE_EVENT_PHYSICAL_DRV | \
		CTLR_STATE_CHANGE_EVENT_LOGICAL_DRV | \
		CTLR_STATE_CHANGE_EVENT_AIO_ENABLED_DISABLED | \
		CTLR_STATE_CHANGE_EVENT_AIO_CONFIG_CHANGE)
	spinlock_t offline_device_lock;
	काष्ठा list_head offline_device_list;
	पूर्णांक	acciopath_status;
	पूर्णांक	drv_req_rescan;
	पूर्णांक	raid_offload_debug;
	पूर्णांक     discovery_polling;
	पूर्णांक     legacy_board;
	काष्ठा  ReportLUNdata *lastlogicals;
	पूर्णांक	needs_पात_tags_swizzled;
	काष्ठा workqueue_काष्ठा *resubmit_wq;
	काष्ठा workqueue_काष्ठा *rescan_ctlr_wq;
	काष्ठा workqueue_काष्ठा *monitor_ctlr_wq;
	atomic_t पात_cmds_available;
	रुको_queue_head_t event_sync_रुको_queue;
	काष्ठा mutex reset_mutex;
	u8 reset_in_progress;
	काष्ठा hpsa_sas_node *sas_host;
	spinlock_t reset_lock;
पूर्ण;

काष्ठा offline_device_entry अणु
	अचिन्हित अक्षर scsi3addr[8];
	काष्ठा list_head offline_list;
पूर्ण;

#घोषणा HPSA_ABORT_MSG 0
#घोषणा HPSA_DEVICE_RESET_MSG 1
#घोषणा HPSA_RESET_TYPE_CONTROLLER 0x00
#घोषणा HPSA_RESET_TYPE_BUS 0x01
#घोषणा HPSA_RESET_TYPE_LUN 0x04
#घोषणा HPSA_PHYS_TARGET_RESET 0x99 /* not defined by cciss spec */
#घोषणा HPSA_MSG_SEND_RETRY_LIMIT 10
#घोषणा HPSA_MSG_SEND_RETRY_INTERVAL_MSECS (10000)

/* Maximum समय in seconds driver will रुको क्रम command completions
 * when polling beक्रमe giving up.
 */
#घोषणा HPSA_MAX_POLL_TIME_SECS (20)

/* During SCSI error recovery, HPSA_TUR_RETRY_LIMIT defines
 * how many बार to retry TEST UNIT READY on a device
 * जबतक रुकोing क्रम it to become पढ़ोy beक्रमe giving up.
 * HPSA_MAX_WAIT_INTERVAL_SECS is the max रुको पूर्णांकerval
 * between sending TURs जबतक रुकोing क्रम a device
 * to become पढ़ोy.
 */
#घोषणा HPSA_TUR_RETRY_LIMIT (20)
#घोषणा HPSA_MAX_WAIT_INTERVAL_SECS (30)

/* HPSA_BOARD_READY_WAIT_SECS is how दीर्घ to रुको क्रम a board
 * to become पढ़ोy, in seconds, beक्रमe giving up on it.
 * HPSA_BOARD_READY_POLL_INTERVAL_MSECS * is how दीर्घ to रुको
 * between polling the board to see अगर it is पढ़ोy, in
 * milliseconds.  HPSA_BOARD_READY_POLL_INTERVAL and
 * HPSA_BOARD_READY_ITERATIONS are derived from those.
 */
#घोषणा HPSA_BOARD_READY_WAIT_SECS (120)
#घोषणा HPSA_BOARD_NOT_READY_WAIT_SECS (100)
#घोषणा HPSA_BOARD_READY_POLL_INTERVAL_MSECS (100)
#घोषणा HPSA_BOARD_READY_POLL_INTERVAL \
	((HPSA_BOARD_READY_POLL_INTERVAL_MSECS * HZ) / 1000)
#घोषणा HPSA_BOARD_READY_ITERATIONS \
	((HPSA_BOARD_READY_WAIT_SECS * 1000) / \
		HPSA_BOARD_READY_POLL_INTERVAL_MSECS)
#घोषणा HPSA_BOARD_NOT_READY_ITERATIONS \
	((HPSA_BOARD_NOT_READY_WAIT_SECS * 1000) / \
		HPSA_BOARD_READY_POLL_INTERVAL_MSECS)
#घोषणा HPSA_POST_RESET_PAUSE_MSECS (3000)
#घोषणा HPSA_POST_RESET_NOOP_RETRIES (12)

/*  Defining the dअगरfent access_menthods */
/*
 * Memory mapped FIFO पूर्णांकerface (SMART 53xx cards)
 */
#घोषणा SA5_DOORBELL	0x20
#घोषणा SA5_REQUEST_PORT_OFFSET	0x40
#घोषणा SA5_REQUEST_PORT64_LO_OFFSET 0xC0
#घोषणा SA5_REQUEST_PORT64_HI_OFFSET 0xC4
#घोषणा SA5_REPLY_INTR_MASK_OFFSET	0x34
#घोषणा SA5_REPLY_PORT_OFFSET		0x44
#घोषणा SA5_INTR_STATUS		0x30
#घोषणा SA5_SCRATCHPAD_OFFSET	0xB0

#घोषणा SA5_CTCFG_OFFSET	0xB4
#घोषणा SA5_CTMEM_OFFSET	0xB8

#घोषणा SA5_INTR_OFF		0x08
#घोषणा SA5B_INTR_OFF		0x04
#घोषणा SA5_INTR_PENDING	0x08
#घोषणा SA5B_INTR_PENDING	0x04
#घोषणा FIFO_EMPTY		0xffffffff
#घोषणा HPSA_FIRMWARE_READY	0xffff0000 /* value in scratchpad रेजिस्टर */

#घोषणा HPSA_ERROR_BIT		0x02

/* Perक्रमmant mode flags */
#घोषणा SA5_PERF_INTR_PENDING   0x04
#घोषणा SA5_PERF_INTR_OFF       0x05
#घोषणा SA5_OUTDB_STATUS_PERF_BIT       0x01
#घोषणा SA5_OUTDB_CLEAR_PERF_BIT        0x01
#घोषणा SA5_OUTDB_CLEAR         0xA0
#घोषणा SA5_OUTDB_CLEAR_PERF_BIT        0x01
#घोषणा SA5_OUTDB_STATUS        0x9C


#घोषणा HPSA_INTR_ON 	1
#घोषणा HPSA_INTR_OFF	0

/*
 * Inbound Post Queue offsets क्रम IO Accelerator Mode 2
 */
#घोषणा IOACCEL2_INBOUND_POSTQ_32	0x48
#घोषणा IOACCEL2_INBOUND_POSTQ_64_LOW	0xd0
#घोषणा IOACCEL2_INBOUND_POSTQ_64_HI	0xd4

#घोषणा HPSA_PHYSICAL_DEVICE_BUS	0
#घोषणा HPSA_RAID_VOLUME_BUS		1
#घोषणा HPSA_EXTERNAL_RAID_VOLUME_BUS	2
#घोषणा HPSA_HBA_BUS			0
#घोषणा HPSA_LEGACY_HBA_BUS		3

/*
	Send the command to the hardware
*/
अटल व्योम SA5_submit_command(काष्ठा ctlr_info *h,
	काष्ठा CommandList *c)
अणु
	ग_लिखोl(c->busaddr, h->vaddr + SA5_REQUEST_PORT_OFFSET);
	(व्योम) पढ़ोl(h->vaddr + SA5_SCRATCHPAD_OFFSET);
पूर्ण

अटल व्योम SA5_submit_command_no_पढ़ो(काष्ठा ctlr_info *h,
	काष्ठा CommandList *c)
अणु
	ग_लिखोl(c->busaddr, h->vaddr + SA5_REQUEST_PORT_OFFSET);
पूर्ण

अटल व्योम SA5_submit_command_ioaccel2(काष्ठा ctlr_info *h,
	काष्ठा CommandList *c)
अणु
	ग_लिखोl(c->busaddr, h->vaddr + SA5_REQUEST_PORT_OFFSET);
पूर्ण

/*
 *  This card is the opposite of the other cards.
 *   0 turns पूर्णांकerrupts on...
 *   0x08 turns them off...
 */
अटल व्योम SA5_पूर्णांकr_mask(काष्ठा ctlr_info *h, अचिन्हित दीर्घ val)
अणु
	अगर (val) अणु /* Turn पूर्णांकerrupts on */
		h->पूर्णांकerrupts_enabled = 1;
		ग_लिखोl(0, h->vaddr + SA5_REPLY_INTR_MASK_OFFSET);
		(व्योम) पढ़ोl(h->vaddr + SA5_REPLY_INTR_MASK_OFFSET);
	पूर्ण अन्यथा अणु /* Turn them off */
		h->पूर्णांकerrupts_enabled = 0;
		ग_लिखोl(SA5_INTR_OFF,
			h->vaddr + SA5_REPLY_INTR_MASK_OFFSET);
		(व्योम) पढ़ोl(h->vaddr + SA5_REPLY_INTR_MASK_OFFSET);
	पूर्ण
पूर्ण

/*
 *  Variant of the above; 0x04 turns पूर्णांकerrupts off...
 */
अटल व्योम SA5B_पूर्णांकr_mask(काष्ठा ctlr_info *h, अचिन्हित दीर्घ val)
अणु
	अगर (val) अणु /* Turn पूर्णांकerrupts on */
		h->पूर्णांकerrupts_enabled = 1;
		ग_लिखोl(0, h->vaddr + SA5_REPLY_INTR_MASK_OFFSET);
		(व्योम) पढ़ोl(h->vaddr + SA5_REPLY_INTR_MASK_OFFSET);
	पूर्ण अन्यथा अणु /* Turn them off */
		h->पूर्णांकerrupts_enabled = 0;
		ग_लिखोl(SA5B_INTR_OFF,
		       h->vaddr + SA5_REPLY_INTR_MASK_OFFSET);
		(व्योम) पढ़ोl(h->vaddr + SA5_REPLY_INTR_MASK_OFFSET);
	पूर्ण
पूर्ण

अटल व्योम SA5_perक्रमmant_पूर्णांकr_mask(काष्ठा ctlr_info *h, अचिन्हित दीर्घ val)
अणु
	अगर (val) अणु /* turn on पूर्णांकerrupts */
		h->पूर्णांकerrupts_enabled = 1;
		ग_लिखोl(0, h->vaddr + SA5_REPLY_INTR_MASK_OFFSET);
		(व्योम) पढ़ोl(h->vaddr + SA5_REPLY_INTR_MASK_OFFSET);
	पूर्ण अन्यथा अणु
		h->पूर्णांकerrupts_enabled = 0;
		ग_लिखोl(SA5_PERF_INTR_OFF,
			h->vaddr + SA5_REPLY_INTR_MASK_OFFSET);
		(व्योम) पढ़ोl(h->vaddr + SA5_REPLY_INTR_MASK_OFFSET);
	पूर्ण
पूर्ण

अटल अचिन्हित दीर्घ SA5_perक्रमmant_completed(काष्ठा ctlr_info *h, u8 q)
अणु
	काष्ठा reply_queue_buffer *rq = &h->reply_queue[q];
	अचिन्हित दीर्घ रेजिस्टर_value = FIFO_EMPTY;

	/* msi स्वतः clears the पूर्णांकerrupt pending bit. */
	अगर (unlikely(!(h->pdev->msi_enabled || h->msix_vectors))) अणु
		/* flush the controller ग_लिखो of the reply queue by पढ़ोing
		 * outbound करोorbell status रेजिस्टर.
		 */
		(व्योम) पढ़ोl(h->vaddr + SA5_OUTDB_STATUS);
		ग_लिखोl(SA5_OUTDB_CLEAR_PERF_BIT, h->vaddr + SA5_OUTDB_CLEAR);
		/* Do a पढ़ो in order to flush the ग_लिखो to the controller
		 * (as per spec.)
		 */
		(व्योम) पढ़ोl(h->vaddr + SA5_OUTDB_STATUS);
	पूर्ण

	अगर ((((u32) rq->head[rq->current_entry]) & 1) == rq->wraparound) अणु
		रेजिस्टर_value = rq->head[rq->current_entry];
		rq->current_entry++;
		atomic_dec(&h->commands_outstanding);
	पूर्ण अन्यथा अणु
		रेजिस्टर_value = FIFO_EMPTY;
	पूर्ण
	/* Check क्रम wraparound */
	अगर (rq->current_entry == h->max_commands) अणु
		rq->current_entry = 0;
		rq->wraparound ^= 1;
	पूर्ण
	वापस रेजिस्टर_value;
पूर्ण

/*
 *   वापसs value पढ़ो from hardware.
 *     वापसs FIFO_EMPTY अगर there is nothing to पढ़ो
 */
अटल अचिन्हित दीर्घ SA5_completed(काष्ठा ctlr_info *h,
	__attribute__((unused)) u8 q)
अणु
	अचिन्हित दीर्घ रेजिस्टर_value
		= पढ़ोl(h->vaddr + SA5_REPLY_PORT_OFFSET);

	अगर (रेजिस्टर_value != FIFO_EMPTY)
		atomic_dec(&h->commands_outstanding);

#अगर_घोषित HPSA_DEBUG
	अगर (रेजिस्टर_value != FIFO_EMPTY)
		dev_dbg(&h->pdev->dev, "Read %lx back from board\n",
			रेजिस्टर_value);
	अन्यथा
		dev_dbg(&h->pdev->dev, "FIFO Empty read\n");
#पूर्ण_अगर

	वापस रेजिस्टर_value;
पूर्ण
/*
 *	Returns true अगर an पूर्णांकerrupt is pending..
 */
अटल bool SA5_पूर्णांकr_pending(काष्ठा ctlr_info *h)
अणु
	अचिन्हित दीर्घ रेजिस्टर_value  =
		पढ़ोl(h->vaddr + SA5_INTR_STATUS);
	वापस रेजिस्टर_value & SA5_INTR_PENDING;
पूर्ण

अटल bool SA5_perक्रमmant_पूर्णांकr_pending(काष्ठा ctlr_info *h)
अणु
	अचिन्हित दीर्घ रेजिस्टर_value = पढ़ोl(h->vaddr + SA5_INTR_STATUS);

	अगर (!रेजिस्टर_value)
		वापस false;

	/* Read outbound करोorbell to flush */
	रेजिस्टर_value = पढ़ोl(h->vaddr + SA5_OUTDB_STATUS);
	वापस रेजिस्टर_value & SA5_OUTDB_STATUS_PERF_BIT;
पूर्ण

#घोषणा SA5_IOACCEL_MODE1_INTR_STATUS_CMP_BIT    0x100

अटल bool SA5_ioaccel_mode1_पूर्णांकr_pending(काष्ठा ctlr_info *h)
अणु
	अचिन्हित दीर्घ रेजिस्टर_value = पढ़ोl(h->vaddr + SA5_INTR_STATUS);

	वापस (रेजिस्टर_value & SA5_IOACCEL_MODE1_INTR_STATUS_CMP_BIT) ?
		true : false;
पूर्ण

/*
 *      Returns true अगर an पूर्णांकerrupt is pending..
 */
अटल bool SA5B_पूर्णांकr_pending(काष्ठा ctlr_info *h)
अणु
	वापस पढ़ोl(h->vaddr + SA5_INTR_STATUS) & SA5B_INTR_PENDING;
पूर्ण

#घोषणा IOACCEL_MODE1_REPLY_QUEUE_INDEX  0x1A0
#घोषणा IOACCEL_MODE1_PRODUCER_INDEX     0x1B8
#घोषणा IOACCEL_MODE1_CONSUMER_INDEX     0x1BC
#घोषणा IOACCEL_MODE1_REPLY_UNUSED       0xFFFFFFFFFFFFFFFFULL

अटल अचिन्हित दीर्घ SA5_ioaccel_mode1_completed(काष्ठा ctlr_info *h, u8 q)
अणु
	u64 रेजिस्टर_value;
	काष्ठा reply_queue_buffer *rq = &h->reply_queue[q];

	BUG_ON(q >= h->nreply_queues);

	रेजिस्टर_value = rq->head[rq->current_entry];
	अगर (रेजिस्टर_value != IOACCEL_MODE1_REPLY_UNUSED) अणु
		rq->head[rq->current_entry] = IOACCEL_MODE1_REPLY_UNUSED;
		अगर (++rq->current_entry == rq->size)
			rq->current_entry = 0;
		/*
		 * @toकरो
		 *
		 * Don't really need to ग_लिखो the new index after each command,
		 * but with current driver design this is easiest.
		 */
		wmb();
		ग_लिखोl((q << 24) | rq->current_entry, h->vaddr +
				IOACCEL_MODE1_CONSUMER_INDEX);
		atomic_dec(&h->commands_outstanding);
	पूर्ण
	वापस (अचिन्हित दीर्घ) रेजिस्टर_value;
पूर्ण

अटल काष्ठा access_method SA5_access = अणु
	.submit_command =	SA5_submit_command,
	.set_पूर्णांकr_mask =	SA5_पूर्णांकr_mask,
	.पूर्णांकr_pending =		SA5_पूर्णांकr_pending,
	.command_completed =	SA5_completed,
पूर्ण;

/* Duplicate entry of the above to mark unsupported boards */
अटल काष्ठा access_method SA5A_access = अणु
	.submit_command =	SA5_submit_command,
	.set_पूर्णांकr_mask =	SA5_पूर्णांकr_mask,
	.पूर्णांकr_pending =		SA5_पूर्णांकr_pending,
	.command_completed =	SA5_completed,
पूर्ण;

अटल काष्ठा access_method SA5B_access = अणु
	.submit_command =	SA5_submit_command,
	.set_पूर्णांकr_mask =	SA5B_पूर्णांकr_mask,
	.पूर्णांकr_pending =		SA5B_पूर्णांकr_pending,
	.command_completed =	SA5_completed,
पूर्ण;

अटल काष्ठा access_method SA5_ioaccel_mode1_access = अणु
	.submit_command =	SA5_submit_command,
	.set_पूर्णांकr_mask =	SA5_perक्रमmant_पूर्णांकr_mask,
	.पूर्णांकr_pending =		SA5_ioaccel_mode1_पूर्णांकr_pending,
	.command_completed =	SA5_ioaccel_mode1_completed,
पूर्ण;

अटल काष्ठा access_method SA5_ioaccel_mode2_access = अणु
	.submit_command =	SA5_submit_command_ioaccel2,
	.set_पूर्णांकr_mask =	SA5_perक्रमmant_पूर्णांकr_mask,
	.पूर्णांकr_pending =		SA5_perक्रमmant_पूर्णांकr_pending,
	.command_completed =	SA5_perक्रमmant_completed,
पूर्ण;

अटल काष्ठा access_method SA5_perक्रमmant_access = अणु
	.submit_command =	SA5_submit_command,
	.set_पूर्णांकr_mask =	SA5_perक्रमmant_पूर्णांकr_mask,
	.पूर्णांकr_pending =		SA5_perक्रमmant_पूर्णांकr_pending,
	.command_completed =	SA5_perक्रमmant_completed,
पूर्ण;

अटल काष्ठा access_method SA5_perक्रमmant_access_no_पढ़ो = अणु
	.submit_command =	SA5_submit_command_no_पढ़ो,
	.set_पूर्णांकr_mask =	SA5_perक्रमmant_पूर्णांकr_mask,
	.पूर्णांकr_pending =		SA5_perक्रमmant_पूर्णांकr_pending,
	.command_completed =	SA5_perक्रमmant_completed,
पूर्ण;

काष्ठा board_type अणु
	u32	board_id;
	अक्षर	*product_name;
	काष्ठा access_method *access;
पूर्ण;

#पूर्ण_अगर /* HPSA_H */

