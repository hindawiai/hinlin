<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * SAS host prototypes and काष्ठाures header file
 *
 * Copyright (C) 2005 Adaptec, Inc.  All rights reserved.
 * Copyright (C) 2005 Luben Tuikov <luben_tuikov@adaptec.com>
 */

#अगर_अघोषित _LIBSAS_H_
#घोषणा _LIBSAS_H_


#समावेश <linux/समयr.h>
#समावेश <linux/pci.h>
#समावेश <scsi/sas.h>
#समावेश <linux/libata.h>
#समावेश <linux/list.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_transport_sas.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/slab.h>

काष्ठा block_device;

क्रमागत sas_class अणु
	SAS,
	EXPANDER
पूर्ण;

क्रमागत sas_phy_role अणु
	PHY_ROLE_NONE = 0,
	PHY_ROLE_TARGET = 0x40,
	PHY_ROLE_INITIATOR = 0x80,
पूर्ण;

क्रमागत sas_phy_type अणु
	PHY_TYPE_PHYSICAL,
	PHY_TYPE_VIRTUAL
पूर्ण;

/* The events are mnemonically described in sas_dump.c
 * so when updating/adding events here, please also
 * update the other file too.
 */
क्रमागत port_event अणु
	PORTE_BYTES_DMAED     = 0U,
	PORTE_BROADCAST_RCVD,
	PORTE_LINK_RESET_ERR,
	PORTE_TIMER_EVENT,
	PORTE_HARD_RESET,
	PORT_NUM_EVENTS,
पूर्ण;

क्रमागत phy_event अणु
	PHYE_LOSS_OF_SIGNAL   = 0U,
	PHYE_OOB_DONE,
	PHYE_OOB_ERROR,
	PHYE_SPINUP_HOLD,             /* hot plug SATA, no COMWAKE sent */
	PHYE_RESUME_TIMEOUT,
	PHYE_SHUTDOWN,
	PHY_NUM_EVENTS,
पूर्ण;

क्रमागत discover_event अणु
	DISCE_DISCOVER_DOMAIN   = 0U,
	DISCE_REVALIDATE_DOMAIN,
	DISCE_SUSPEND,
	DISCE_RESUME,
	DISC_NUM_EVENTS,
पूर्ण;

/* ---------- Expander Devices ---------- */

#घोषणा to_करोm_device(_obj) container_of(_obj, काष्ठा करोमुख्य_device, dev_obj)
#घोषणा to_dev_attr(_attr)  container_of(_attr, काष्ठा करोमुख्य_dev_attribute,\
					 attr)

क्रमागत routing_attribute अणु
	सूचीECT_ROUTING,
	SUBTRACTIVE_ROUTING,
	TABLE_ROUTING,
पूर्ण;

क्रमागत ex_phy_state अणु
	PHY_EMPTY,
	PHY_VACANT,
	PHY_NOT_PRESENT,
	PHY_DEVICE_DISCOVERED
पूर्ण;

काष्ठा ex_phy अणु
	पूर्णांक    phy_id;

	क्रमागत ex_phy_state phy_state;

	क्रमागत sas_device_type attached_dev_type;
	क्रमागत sas_linkrate linkrate;

	u8   attached_sata_host:1;
	u8   attached_sata_dev:1;
	u8   attached_sata_ps:1;

	क्रमागत sas_protocol attached_tproto;
	क्रमागत sas_protocol attached_iproto;

	u8   attached_sas_addr[SAS_ADDR_SIZE];
	u8   attached_phy_id;

	पूर्णांक phy_change_count;
	क्रमागत routing_attribute routing_attr;
	u8   भव:1;

	पूर्णांक  last_da_index;

	काष्ठा sas_phy *phy;
	काष्ठा sas_port *port;
पूर्ण;

काष्ठा expander_device अणु
	काष्ठा list_head children;

	पूर्णांक    ex_change_count;
	u16    max_route_indexes;
	u8     num_phys;

	u8     t2t_supp:1;
	u8     configuring:1;
	u8     conf_route_table:1;

	u8     enclosure_logical_id[8];

	काष्ठा ex_phy *ex_phy;
	काष्ठा sas_port *parent_port;

	काष्ठा mutex cmd_mutex;
पूर्ण;

/* ---------- SATA device ---------- */
#घोषणा ATA_RESP_FIS_SIZE 24

काष्ठा sata_device अणु
	अचिन्हित पूर्णांक class;
	u8     port_no;        /* port number, अगर this is a PM (Port) */

	काष्ठा ata_port *ap;
	काष्ठा ata_host *ata_host;
	काष्ठा smp_resp rps_resp ____cacheline_aligned; /* report_phy_sata_resp */
	u8     fis[ATA_RESP_FIS_SIZE];
पूर्ण;

काष्ठा ssp_device अणु
	काष्ठा list_head eh_list_node; /* pending a user requested eh action */
	काष्ठा scsi_lun reset_lun;
पूर्ण;

क्रमागत अणु
	SAS_DEV_GONE,
	SAS_DEV_FOUND, /* device notअगरied to lldd */
	SAS_DEV_DESTROY,
	SAS_DEV_EH_PENDING,
	SAS_DEV_LU_RESET,
	SAS_DEV_RESET,
पूर्ण;

काष्ठा करोमुख्य_device अणु
	spinlock_t करोne_lock;
	क्रमागत sas_device_type dev_type;

	क्रमागत sas_linkrate linkrate;
	क्रमागत sas_linkrate min_linkrate;
	क्रमागत sas_linkrate max_linkrate;

	पूर्णांक  pathways;

	काष्ठा करोमुख्य_device *parent;
	काष्ठा list_head siblings; /* devices on the same level */
	काष्ठा asd_sas_port *port;        /* लघुcut to root of the tree */
	काष्ठा sas_phy *phy;

	काष्ठा list_head dev_list_node;
	काष्ठा list_head disco_list_node; /* aरुकोing probe or deकाष्ठा */

	क्रमागत sas_protocol    iproto;
	क्रमागत sas_protocol    tproto;

	काष्ठा sas_rphy *rphy;

	u8  sas_addr[SAS_ADDR_SIZE];
	u8  hashed_sas_addr[HASHED_SAS_ADDR_SIZE];

	u8  frame_rcvd[32];

	जोड़ अणु
		काष्ठा expander_device ex_dev;
		काष्ठा sata_device     sata_dev; /* STP & directly attached */
		काष्ठा ssp_device      ssp_dev;
	पूर्ण;

	व्योम *lldd_dev;
	अचिन्हित दीर्घ state;
	काष्ठा kref kref;
पूर्ण;

काष्ठा sas_work अणु
	काष्ठा list_head drain_node;
	काष्ठा work_काष्ठा work;
पूर्ण;

अटल अंतरभूत bool dev_is_expander(क्रमागत sas_device_type type)
अणु
	वापस type == SAS_EDGE_EXPANDER_DEVICE ||
	       type == SAS_FANOUT_EXPANDER_DEVICE;
पूर्ण

अटल अंतरभूत व्योम INIT_SAS_WORK(काष्ठा sas_work *sw, व्योम (*fn)(काष्ठा work_काष्ठा *))
अणु
	INIT_WORK(&sw->work, fn);
	INIT_LIST_HEAD(&sw->drain_node);
पूर्ण

काष्ठा sas_discovery_event अणु
	काष्ठा sas_work work;
	काष्ठा asd_sas_port *port;
पूर्ण;

अटल अंतरभूत काष्ठा sas_discovery_event *to_sas_discovery_event(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sas_discovery_event *ev = container_of(work, typeof(*ev), work.work);

	वापस ev;
पूर्ण

काष्ठा sas_discovery अणु
	काष्ठा sas_discovery_event disc_work[DISC_NUM_EVENTS];
	अचिन्हित दीर्घ    pending;
	u8     fanout_sas_addr[SAS_ADDR_SIZE];
	u8     eeds_a[SAS_ADDR_SIZE];
	u8     eeds_b[SAS_ADDR_SIZE];
	पूर्णांक    max_level;
पूर्ण;

/* The port काष्ठा is Class:RW, driver:RO */
काष्ठा asd_sas_port अणु
/* निजी: */
	काष्ठा sas_discovery disc;
	काष्ठा करोमुख्य_device *port_dev;
	spinlock_t dev_list_lock;
	काष्ठा list_head dev_list;
	काष्ठा list_head disco_list;
	काष्ठा list_head destroy_list;
	काष्ठा list_head sas_port_del_list;
	क्रमागत   sas_linkrate linkrate;

	काष्ठा sas_work work;
	पूर्णांक suspended;

/* खुला: */
	पूर्णांक id;

	क्रमागत sas_class   class;
	u8               sas_addr[SAS_ADDR_SIZE];
	u8               attached_sas_addr[SAS_ADDR_SIZE];
	क्रमागत sas_protocol   iproto;
	क्रमागत sas_protocol   tproto;

	क्रमागत sas_oob_mode oob_mode;

	spinlock_t       phy_list_lock;
	काष्ठा list_head phy_list;
	पूर्णांक              num_phys;
	u32              phy_mask;

	काष्ठा sas_ha_काष्ठा *ha;

	काष्ठा sas_port	*port;

	व्योम *lldd_port;	  /* not touched by the sas class code */
पूर्ण;

काष्ठा asd_sas_event अणु
	काष्ठा sas_work work;
	काष्ठा asd_sas_phy *phy;
	पूर्णांक event;
पूर्ण;

अटल अंतरभूत काष्ठा asd_sas_event *to_asd_sas_event(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा asd_sas_event *ev = container_of(work, typeof(*ev), work.work);

	वापस ev;
पूर्ण

अटल अंतरभूत व्योम INIT_SAS_EVENT(काष्ठा asd_sas_event *ev,
		व्योम (*fn)(काष्ठा work_काष्ठा *),
		काष्ठा asd_sas_phy *phy, पूर्णांक event)
अणु
	INIT_SAS_WORK(&ev->work, fn);
	ev->phy = phy;
	ev->event = event;
पूर्ण

#घोषणा SAS_PHY_SHUTDOWN_THRES   1024

/* The phy pretty much is controlled by the LLDD.
 * The class only पढ़ोs those fields.
 */
काष्ठा asd_sas_phy अणु
/* निजी: */
	atomic_t event_nr;
	पूर्णांक in_shutकरोwn;
	पूर्णांक error;
	पूर्णांक suspended;

	काष्ठा sas_phy *phy;

/* खुला: */
	/* The following are class:RO, driver:R/W */
	पूर्णांक            enabled;	  /* must be set */

	पूर्णांक            id;	  /* must be set */
	क्रमागत sas_class class;
	क्रमागत sas_protocol iproto;
	क्रमागत sas_protocol tproto;

	क्रमागत sas_phy_type  type;
	क्रमागत sas_phy_role  role;
	क्रमागत sas_oob_mode  oob_mode;
	क्रमागत sas_linkrate linkrate;

	u8   *sas_addr;		  /* must be set */
	u8   attached_sas_addr[SAS_ADDR_SIZE]; /* class:RO, driver: R/W */

	spinlock_t     frame_rcvd_lock;
	u8             *frame_rcvd; /* must be set */
	पूर्णांक            frame_rcvd_size;

	spinlock_t     sas_prim_lock;
	u32            sas_prim;

	काष्ठा list_head port_phy_el; /* driver:RO */
	काष्ठा asd_sas_port      *port; /* Class:RW, driver: RO */

	काष्ठा sas_ha_काष्ठा *ha; /* may be set; the class sets it anyway */

	व्योम *lldd_phy;		  /* not touched by the sas_class_code */
पूर्ण;

काष्ठा scsi_core अणु
	काष्ठा Scsi_Host *shost;

पूर्ण;

क्रमागत sas_ha_state अणु
	SAS_HA_REGISTERED,
	SAS_HA_DRAINING,
	SAS_HA_ATA_EH_ACTIVE,
	SAS_HA_FROZEN,
पूर्ण;

काष्ठा sas_ha_काष्ठा अणु
/* निजी: */
	काष्ठा list_head  defer_q; /* work queued जबतक draining */
	काष्ठा mutex	  drain_mutex;
	अचिन्हित दीर्घ	  state;
	spinlock_t	  lock;
	पूर्णांक		  eh_active;
	रुको_queue_head_t eh_रुको_q;
	काष्ठा list_head  eh_dev_q;

	काष्ठा mutex disco_mutex;

	काष्ठा scsi_core core;

/* खुला: */
	अक्षर *sas_ha_name;
	काष्ठा device *dev;	  /* should be set */
	काष्ठा module *lldd_module; /* should be set */

	काष्ठा workqueue_काष्ठा *event_q;
	काष्ठा workqueue_काष्ठा *disco_q;

	u8 *sas_addr;		  /* must be set */
	u8 hashed_sas_addr[HASHED_SAS_ADDR_SIZE];

	spinlock_t      phy_port_lock;
	काष्ठा asd_sas_phy  **sas_phy; /* array of valid poपूर्णांकers, must be set */
	काष्ठा asd_sas_port **sas_port; /* array of valid poपूर्णांकers, must be set */
	पूर्णांक             num_phys; /* must be set, gt 0, अटल */

	पूर्णांक strict_wide_ports; /* both sas_addr and attached_sas_addr must match
				* their siblings when क्रमming wide ports */

	व्योम *lldd_ha;		  /* not touched by sas class code */

	काष्ठा list_head eh_करोne_q;  /* complete via scsi_eh_flush_करोne_q */
	काष्ठा list_head eh_ata_q; /* scmds to promote from sas to ata eh */

	पूर्णांक event_thres;
पूर्ण;

#घोषणा SHOST_TO_SAS_HA(_shost) (*(काष्ठा sas_ha_काष्ठा **)(_shost)->hostdata)

अटल अंतरभूत काष्ठा करोमुख्य_device *
starget_to_करोमुख्य_dev(काष्ठा scsi_target *starget) अणु
	वापस starget->hostdata;
पूर्ण

अटल अंतरभूत काष्ठा करोमुख्य_device *
sdev_to_करोमुख्य_dev(काष्ठा scsi_device *sdev) अणु
	वापस starget_to_करोमुख्य_dev(sdev->sdev_target);
पूर्ण

अटल अंतरभूत काष्ठा ata_device *sas_to_ata_dev(काष्ठा करोमुख्य_device *dev)
अणु
	वापस &dev->sata_dev.ap->link.device[0];
पूर्ण

अटल अंतरभूत काष्ठा करोमुख्य_device *
cmd_to_करोमुख्य_dev(काष्ठा scsi_cmnd *cmd)
अणु
	वापस sdev_to_करोमुख्य_dev(cmd->device);
पूर्ण

व्योम sas_hash_addr(u8 *hashed, स्थिर u8 *sas_addr);

/* Beक्रमe calling a notअगरy event, LLDD should use this function
 * when the link is severed (possibly from its tasklet).
 * The idea is that the Class only पढ़ोs those, जबतक the LLDD,
 * can R/W these (thus aव्योमing a race).
 */
अटल अंतरभूत व्योम sas_phy_disconnected(काष्ठा asd_sas_phy *phy)
अणु
	phy->oob_mode = OOB_NOT_CONNECTED;
	phy->linkrate = SAS_LINK_RATE_UNKNOWN;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक to_sas_gpio_od(पूर्णांक device, पूर्णांक bit)
अणु
	वापस 3 * device + bit;
पूर्ण

अटल अंतरभूत व्योम sas_put_local_phy(काष्ठा sas_phy *phy)
अणु
	put_device(&phy->dev);
पूर्ण

#अगर_घोषित CONFIG_SCSI_SAS_HOST_SMP
पूर्णांक try_test_sas_gpio_gp_bit(अचिन्हित पूर्णांक od, u8 *data, u8 index, u8 count);
#अन्यथा
अटल अंतरभूत पूर्णांक try_test_sas_gpio_gp_bit(अचिन्हित पूर्णांक od, u8 *data, u8 index, u8 count)
अणु
	वापस -1;
पूर्ण
#पूर्ण_अगर

/* ---------- Tasks ---------- */
/*
      service_response |  SAS_TASK_COMPLETE  |  SAS_TASK_UNDELIVERED |
  exec_status          |                     |                       |
  ---------------------+---------------------+-----------------------+
       SAM_...         |         X           |                       |
       DEV_NO_RESPONSE |         X           |           X           |
       INTERRUPTED     |         X           |                       |
       QUEUE_FULL      |                     |           X           |
       DEVICE_UNKNOWN  |                     |           X           |
       SG_ERR          |                     |           X           |
  ---------------------+---------------------+-----------------------+
 */

क्रमागत service_response अणु
	SAS_TASK_COMPLETE,
	SAS_TASK_UNDELIVERED = -1,
पूर्ण;

क्रमागत exec_status अणु
	/* The SAM_STAT_.. codes fit in the lower 6 bits, alias some of
	 * them here to silence 'case value not in enumerated type' warnings
	 */
	__SAM_STAT_CHECK_CONDITION = SAM_STAT_CHECK_CONDITION,

	SAS_DEV_NO_RESPONSE = 0x80,
	SAS_DATA_UNDERRUN,
	SAS_DATA_OVERRUN,
	SAS_INTERRUPTED,
	SAS_QUEUE_FULL,
	SAS_DEVICE_UNKNOWN,
	SAS_SG_ERR,
	SAS_OPEN_REJECT,
	SAS_OPEN_TO,
	SAS_PROTO_RESPONSE,
	SAS_PHY_DOWN,
	SAS_NAK_R_ERR,
	SAS_PENDING,
	SAS_ABORTED_TASK,
पूर्ण;

/* When a task finishes with a response, the LLDD examines the
 * response:
 *	- For an ATA task task_status_काष्ठा::stat is set to
 * SAS_PROTO_RESPONSE, and the task_status_काष्ठा::buf is set to the
 * contents of काष्ठा ata_task_resp.
 *	- For SSP tasks, अगर no data is present or status/TMF response
 * is valid, task_status_काष्ठा::stat is set.  If data is present
 * (SENSE data), the LLDD copies up to SAS_STATUS_BUF_SIZE, sets
 * task_status_काष्ठा::buf_valid_size, and task_status_काष्ठा::stat is
 * set to SAM_CHECK_COND.
 *
 * "buf" has क्रमmat SCSI Sense क्रम SSP task, or काष्ठा ata_task_resp
 * क्रम ATA task.
 *
 * "frame_len" is the total frame length, which could be more or less
 * than actually copied.
 *
 * Tasks ending with response, always set the residual field.
 */
काष्ठा ata_task_resp अणु
	u16  frame_len;
	u8   ending_fis[ATA_RESP_FIS_SIZE];	  /* dev to host or data-in */
पूर्ण;

#घोषणा SAS_STATUS_BUF_SIZE 96

काष्ठा task_status_काष्ठा अणु
	क्रमागत service_response resp;
	क्रमागत exec_status      stat;
	पूर्णांक  buf_valid_size;

	u8   buf[SAS_STATUS_BUF_SIZE];

	u32  residual;
	क्रमागत sas_खोलो_rej_reason खोलो_rej_reason;
पूर्ण;

/* ATA and ATAPI task queuable to a SAS LLDD.
 */
काष्ठा sas_ata_task अणु
	काष्ठा host_to_dev_fis fis;
	u8     atapi_packet[16];  /* 0 अगर not ATAPI task */

	u8     retry_count;	  /* hardware retry, should be > 0 */

	u8     dma_xfer:1;	  /* PIO:0 or DMA:1 */
	u8     use_ncq:1;
	u8     set_affil_pol:1;
	u8     stp_affil_pol:1;

	u8     device_control_reg_update:1;
पूर्ण;

काष्ठा sas_smp_task अणु
	काष्ठा scatterlist smp_req;
	काष्ठा scatterlist smp_resp;
पूर्ण;

क्रमागत task_attribute अणु
	TASK_ATTR_SIMPLE = 0,
	TASK_ATTR_HOQ    = 1,
	TASK_ATTR_ORDERED= 2,
	TASK_ATTR_ACA    = 4,
पूर्ण;

काष्ठा sas_ssp_task अणु
	u8     retry_count;	  /* hardware retry, should be > 0 */

	u8     LUN[8];
	u8     enable_first_burst:1;
	क्रमागत   task_attribute task_attr;
	u8     task_prio;
	काष्ठा scsi_cmnd *cmd;
पूर्ण;

काष्ठा sas_task अणु
	काष्ठा करोमुख्य_device *dev;

	spinlock_t   task_state_lock;
	अचिन्हित     task_state_flags;

	क्रमागत   sas_protocol      task_proto;

	जोड़ अणु
		काष्ठा sas_ata_task ata_task;
		काष्ठा sas_smp_task smp_task;
		काष्ठा sas_ssp_task ssp_task;
	पूर्ण;

	काष्ठा scatterlist *scatter;
	पूर्णांक    num_scatter;
	u32    total_xfer_len;
	u8     data_dir:2;	  /* Use PCI_DMA_... */

	काष्ठा task_status_काष्ठा task_status;
	व्योम   (*task_करोne)(काष्ठा sas_task *);

	व्योम   *lldd_task;	  /* क्रम use by LLDDs */
	व्योम   *uldd_task;
	काष्ठा sas_task_slow *slow_task;
पूर्ण;

काष्ठा sas_task_slow अणु
	/* standard/extra infraकाष्ठाure क्रम slow path commands (SMP and
	 * पूर्णांकernal lldd commands
	 */
	काष्ठा समयr_list     समयr;
	काष्ठा completion     completion;
	काष्ठा sas_task       *task;
पूर्ण;

#घोषणा SAS_TASK_STATE_PENDING      1
#घोषणा SAS_TASK_STATE_DONE         2
#घोषणा SAS_TASK_STATE_ABORTED      4
#घोषणा SAS_TASK_NEED_DEV_RESET     8
#घोषणा SAS_TASK_AT_INITIATOR       16

बाह्य काष्ठा sas_task *sas_alloc_task(gfp_t flags);
बाह्य काष्ठा sas_task *sas_alloc_slow_task(gfp_t flags);
बाह्य व्योम sas_मुक्त_task(काष्ठा sas_task *task);

काष्ठा sas_करोमुख्य_function_ढाँचा अणु
	/* The class calls these to notअगरy the LLDD of an event. */
	व्योम (*lldd_port_क्रमmed)(काष्ठा asd_sas_phy *);
	व्योम (*lldd_port_deक्रमmed)(काष्ठा asd_sas_phy *);

	/* The class calls these when a device is found or gone. */
	पूर्णांक  (*lldd_dev_found)(काष्ठा करोमुख्य_device *);
	व्योम (*lldd_dev_gone)(काष्ठा करोमुख्य_device *);

	पूर्णांक (*lldd_execute_task)(काष्ठा sas_task *, gfp_t gfp_flags);

	/* Task Management Functions. Must be called from process context. */
	पूर्णांक (*lldd_पात_task)(काष्ठा sas_task *);
	पूर्णांक (*lldd_पात_task_set)(काष्ठा करोमुख्य_device *, u8 *lun);
	पूर्णांक (*lldd_clear_aca)(काष्ठा करोमुख्य_device *, u8 *lun);
	पूर्णांक (*lldd_clear_task_set)(काष्ठा करोमुख्य_device *, u8 *lun);
	पूर्णांक (*lldd_I_T_nexus_reset)(काष्ठा करोमुख्य_device *);
	पूर्णांक (*lldd_ata_check_पढ़ोy)(काष्ठा करोमुख्य_device *);
	व्योम (*lldd_ata_set_dmamode)(काष्ठा करोमुख्य_device *);
	पूर्णांक (*lldd_lu_reset)(काष्ठा करोमुख्य_device *, u8 *lun);
	पूर्णांक (*lldd_query_task)(काष्ठा sas_task *);

	/* Port and Adapter management */
	पूर्णांक (*lldd_clear_nexus_port)(काष्ठा asd_sas_port *);
	पूर्णांक (*lldd_clear_nexus_ha)(काष्ठा sas_ha_काष्ठा *);

	/* Phy management */
	पूर्णांक (*lldd_control_phy)(काष्ठा asd_sas_phy *, क्रमागत phy_func, व्योम *);

	/* GPIO support */
	पूर्णांक (*lldd_ग_लिखो_gpio)(काष्ठा sas_ha_काष्ठा *, u8 reg_type,
			       u8 reg_index, u8 reg_count, u8 *ग_लिखो_data);
पूर्ण;

बाह्य पूर्णांक sas_रेजिस्टर_ha(काष्ठा sas_ha_काष्ठा *);
बाह्य पूर्णांक sas_unरेजिस्टर_ha(काष्ठा sas_ha_काष्ठा *);
बाह्य व्योम sas_prep_resume_ha(काष्ठा sas_ha_काष्ठा *sas_ha);
बाह्य व्योम sas_resume_ha(काष्ठा sas_ha_काष्ठा *sas_ha);
बाह्य व्योम sas_suspend_ha(काष्ठा sas_ha_काष्ठा *sas_ha);

पूर्णांक sas_set_phy_speed(काष्ठा sas_phy *phy, काष्ठा sas_phy_linkrates *rates);
पूर्णांक sas_phy_reset(काष्ठा sas_phy *phy, पूर्णांक hard_reset);
बाह्य पूर्णांक sas_queuecommand(काष्ठा Scsi_Host *, काष्ठा scsi_cmnd *);
बाह्य पूर्णांक sas_target_alloc(काष्ठा scsi_target *);
बाह्य पूर्णांक sas_slave_configure(काष्ठा scsi_device *);
बाह्य पूर्णांक sas_change_queue_depth(काष्ठा scsi_device *, पूर्णांक new_depth);
बाह्य पूर्णांक sas_bios_param(काष्ठा scsi_device *, काष्ठा block_device *,
			  sector_t capacity, पूर्णांक *hsc);
बाह्य काष्ठा scsi_transport_ढाँचा *
sas_करोमुख्य_attach_transport(काष्ठा sas_करोमुख्य_function_ढाँचा *);
बाह्य काष्ठा device_attribute dev_attr_phy_event_threshold;

पूर्णांक  sas_discover_root_expander(काष्ठा करोमुख्य_device *);

व्योम sas_init_ex_attr(व्योम);

पूर्णांक  sas_ex_revalidate_करोमुख्य(काष्ठा करोमुख्य_device *);

व्योम sas_unरेजिस्टर_करोमुख्य_devices(काष्ठा asd_sas_port *port, पूर्णांक gone);
व्योम sas_init_disc(काष्ठा sas_discovery *disc, काष्ठा asd_sas_port *);
पूर्णांक  sas_discover_event(काष्ठा asd_sas_port *, क्रमागत discover_event ev);

पूर्णांक  sas_discover_sata(काष्ठा करोमुख्य_device *);
पूर्णांक  sas_discover_end_dev(काष्ठा करोमुख्य_device *);

व्योम sas_unरेजिस्टर_dev(काष्ठा asd_sas_port *port, काष्ठा करोमुख्य_device *);

व्योम sas_init_dev(काष्ठा करोमुख्य_device *);

व्योम sas_task_पात(काष्ठा sas_task *);
पूर्णांक sas_eh_पात_handler(काष्ठा scsi_cmnd *cmd);
पूर्णांक sas_eh_device_reset_handler(काष्ठा scsi_cmnd *cmd);
पूर्णांक sas_eh_target_reset_handler(काष्ठा scsi_cmnd *cmd);

बाह्य व्योम sas_target_destroy(काष्ठा scsi_target *);
बाह्य पूर्णांक sas_slave_alloc(काष्ठा scsi_device *);
बाह्य पूर्णांक sas_ioctl(काष्ठा scsi_device *sdev, अचिन्हित पूर्णांक cmd,
		     व्योम __user *arg);
बाह्य पूर्णांक sas_drain_work(काष्ठा sas_ha_काष्ठा *ha);

बाह्य व्योम sas_ssp_task_response(काष्ठा device *dev, काष्ठा sas_task *task,
				  काष्ठा ssp_response_iu *iu);
काष्ठा sas_phy *sas_get_local_phy(काष्ठा करोमुख्य_device *dev);

पूर्णांक sas_request_addr(काष्ठा Scsi_Host *shost, u8 *addr);

पूर्णांक sas_notअगरy_port_event(काष्ठा asd_sas_phy *phy, क्रमागत port_event event,
			  gfp_t gfp_flags);
पूर्णांक sas_notअगरy_phy_event(काष्ठा asd_sas_phy *phy, क्रमागत phy_event event,
			 gfp_t gfp_flags);

#पूर्ण_अगर /* _SASLIB_H_ */
