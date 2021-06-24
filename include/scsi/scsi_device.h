<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SCSI_SCSI_DEVICE_H
#घोषणा _SCSI_SCSI_DEVICE_H

#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/blkdev.h>
#समावेश <scsi/scsi.h>
#समावेश <linux/atomic.h>
#समावेश <linux/sbiपंचांगap.h>

काष्ठा device;
काष्ठा request_queue;
काष्ठा scsi_cmnd;
काष्ठा scsi_lun;
काष्ठा scsi_sense_hdr;

प्रकार __u64 __bitwise blist_flags_t;

#घोषणा SCSI_SENSE_BUFFERSIZE	96

काष्ठा scsi_mode_data अणु
	__u32	length;
	__u16	block_descriptor_length;
	__u8	medium_type;
	__u8	device_specअगरic;
	__u8	header_length;
	__u8	दीर्घlba:1;
पूर्ण;

/*
 * sdev state: If you alter this, you also need to alter scsi_sysfs.c
 * (क्रम the ascii descriptions) and the state model enक्रमcer:
 * scsi_lib:scsi_device_set_state().
 */
क्रमागत scsi_device_state अणु
	SDEV_CREATED = 1,	/* device created but not added to sysfs
				 * Only पूर्णांकernal commands allowed (क्रम inq) */
	SDEV_RUNNING,		/* device properly configured
				 * All commands allowed */
	SDEV_CANCEL,		/* beginning to delete device
				 * Only error handler commands allowed */
	SDEV_DEL,		/* device deleted 
				 * no commands allowed */
	SDEV_QUIESCE,		/* Device quiescent.  No block commands
				 * will be accepted, only specials (which
				 * originate in the mid-layer) */
	SDEV_OFFLINE,		/* Device offlined (by error handling or
				 * user request */
	SDEV_TRANSPORT_OFFLINE,	/* Offlined by transport class error handler */
	SDEV_BLOCK,		/* Device blocked by scsi lld.  No
				 * scsi commands from user or midlayer
				 * should be issued to the scsi
				 * lld. */
	SDEV_CREATED_BLOCK,	/* same as above but क्रम created devices */
पूर्ण;

क्रमागत scsi_scan_mode अणु
	SCSI_SCAN_INITIAL = 0,
	SCSI_SCAN_RESCAN,
	SCSI_SCAN_MANUAL,
पूर्ण;

क्रमागत scsi_device_event अणु
	SDEV_EVT_MEDIA_CHANGE	= 1,	/* media has changed */
	SDEV_EVT_INQUIRY_CHANGE_REPORTED,		/* 3F 03  UA reported */
	SDEV_EVT_CAPACITY_CHANGE_REPORTED,		/* 2A 09  UA reported */
	SDEV_EVT_SOFT_THRESHOLD_REACHED_REPORTED,	/* 38 07  UA reported */
	SDEV_EVT_MODE_PARAMETER_CHANGE_REPORTED,	/* 2A 01  UA reported */
	SDEV_EVT_LUN_CHANGE_REPORTED,			/* 3F 0E  UA reported */
	SDEV_EVT_ALUA_STATE_CHANGE_REPORTED,		/* 2A 06  UA reported */
	SDEV_EVT_POWER_ON_RESET_OCCURRED,		/* 29 00  UA reported */

	SDEV_EVT_FIRST		= SDEV_EVT_MEDIA_CHANGE,
	SDEV_EVT_LAST		= SDEV_EVT_POWER_ON_RESET_OCCURRED,

	SDEV_EVT_MAXBITS	= SDEV_EVT_LAST + 1
पूर्ण;

काष्ठा scsi_event अणु
	क्रमागत scsi_device_event	evt_type;
	काष्ठा list_head	node;

	/* put जोड़ of data काष्ठाures, क्रम non-simple event types,
	 * here
	 */
पूर्ण;

/**
 * काष्ठा scsi_vpd - SCSI Vital Product Data
 * @rcu: For kमुक्त_rcu().
 * @len: Length in bytes of @data.
 * @data: VPD data as defined in various T10 SCSI standard करोcuments.
 */
काष्ठा scsi_vpd अणु
	काष्ठा rcu_head	rcu;
	पूर्णांक		len;
	अचिन्हित अक्षर	data[];
पूर्ण;

काष्ठा scsi_device अणु
	काष्ठा Scsi_Host *host;
	काष्ठा request_queue *request_queue;

	/* the next two are रक्षित by the host->host_lock */
	काष्ठा list_head    siblings;   /* list of all devices on this host */
	काष्ठा list_head    same_target_siblings; /* just the devices sharing same target id */

	काष्ठा sbiपंचांगap budget_map;
	atomic_t device_blocked;	/* Device वापसed QUEUE_FULL. */

	atomic_t restarts;
	spinlock_t list_lock;
	काष्ठा list_head starved_entry;
	अचिन्हित लघु queue_depth;	/* How deep of a queue we want */
	अचिन्हित लघु max_queue_depth;	/* max queue depth */
	अचिन्हित लघु last_queue_full_depth; /* These two are used by */
	अचिन्हित लघु last_queue_full_count; /* scsi_track_queue_full() */
	अचिन्हित दीर्घ last_queue_full_समय;	/* last queue full समय */
	अचिन्हित दीर्घ queue_ramp_up_period;	/* ramp up period in jअगरfies */
#घोषणा SCSI_DEFAULT_RAMP_UP_PERIOD	(120 * HZ)

	अचिन्हित दीर्घ last_queue_ramp_up;	/* last queue ramp up समय */

	अचिन्हित पूर्णांक id, channel;
	u64 lun;
	अचिन्हित पूर्णांक manufacturer;	/* Manufacturer of device, क्रम using 
					 * venकरोr-specअगरic cmd's */
	अचिन्हित sector_size;	/* size in bytes */

	व्योम *hostdata;		/* available to low-level driver */
	अचिन्हित अक्षर type;
	अक्षर scsi_level;
	अक्षर inq_periph_qual;	/* PQ from INQUIRY data */	
	काष्ठा mutex inquiry_mutex;
	अचिन्हित अक्षर inquiry_len;	/* valid bytes in 'inquiry' */
	अचिन्हित अक्षर * inquiry;	/* INQUIRY response data */
	स्थिर अक्षर * venकरोr;		/* [back_compat] poपूर्णांक पूर्णांकo 'inquiry' ... */
	स्थिर अक्षर * model;		/* ... after scan; poपूर्णांक to अटल string */
	स्थिर अक्षर * rev;		/* ... "nullnullnullnull" beक्रमe scan */

#घोषणा SCSI_VPD_PG_LEN                255
	काष्ठा scsi_vpd __rcu *vpd_pg0;
	काष्ठा scsi_vpd __rcu *vpd_pg83;
	काष्ठा scsi_vpd __rcu *vpd_pg80;
	काष्ठा scsi_vpd __rcu *vpd_pg89;
	अचिन्हित अक्षर current_tag;	/* current tag */
	काष्ठा scsi_target      *sdev_target;

	blist_flags_t		sdev_bflags; /* black/white flags as also found in
				 * scsi_devinfo.[hc]. For now used only to
				 * pass settings from slave_alloc to scsi
				 * core. */
	अचिन्हित पूर्णांक eh_समयout; /* Error handling समयout */
	अचिन्हित removable:1;
	अचिन्हित changed:1;	/* Data invalid due to media change */
	अचिन्हित busy:1;	/* Used to prevent races */
	अचिन्हित lockable:1;	/* Able to prevent media removal */
	अचिन्हित locked:1;      /* Media removal disabled */
	अचिन्हित borken:1;	/* Tell the Seagate driver to be 
				 * painfully slow on this device */
	अचिन्हित disconnect:1;	/* can disconnect */
	अचिन्हित soft_reset:1;	/* Uses soft reset option */
	अचिन्हित sdtr:1;	/* Device supports SDTR messages */
	अचिन्हित wdtr:1;	/* Device supports WDTR messages */
	अचिन्हित ppr:1;		/* Device supports PPR messages */
	अचिन्हित tagged_supported:1;	/* Supports SCSI-II tagged queuing */
	अचिन्हित simple_tags:1;	/* simple queue tag messages are enabled */
	अचिन्हित was_reset:1;	/* There was a bus reset on the bus क्रम 
				 * this device */
	अचिन्हित expecting_cc_ua:1; /* Expecting a CHECK_CONDITION/UNIT_ATTN
				     * because we did a bus reset. */
	अचिन्हित use_10_क्रम_rw:1; /* first try 10-byte पढ़ो / ग_लिखो */
	अचिन्हित use_10_क्रम_ms:1; /* first try 10-byte mode sense/select */
	अचिन्हित set_dbd_क्रम_ms:1; /* Set "DBD" field in mode sense */
	अचिन्हित no_report_opcodes:1;	/* no REPORT SUPPORTED OPERATION CODES */
	अचिन्हित no_ग_लिखो_same:1;	/* no WRITE SAME command */
	अचिन्हित use_16_क्रम_rw:1; /* Use पढ़ो/ग_लिखो(16) over पढ़ो/ग_लिखो(10) */
	अचिन्हित skip_ms_page_8:1;	/* करो not use MODE SENSE page 0x08 */
	अचिन्हित skip_ms_page_3f:1;	/* करो not use MODE SENSE page 0x3f */
	अचिन्हित skip_vpd_pages:1;	/* करो not पढ़ो VPD pages */
	अचिन्हित try_vpd_pages:1;	/* attempt to पढ़ो VPD pages */
	अचिन्हित use_192_bytes_क्रम_3f:1; /* ask क्रम 192 bytes from page 0x3f */
	अचिन्हित no_start_on_add:1;	/* करो not issue start on add */
	अचिन्हित allow_restart:1; /* issue START_UNIT in error handler */
	अचिन्हित manage_start_stop:1;	/* Let HLD (sd) manage start/stop */
	अचिन्हित start_stop_pwr_cond:1;	/* Set घातer cond. in START_STOP_UNIT */
	अचिन्हित no_uld_attach:1; /* disable connecting to upper level drivers */
	अचिन्हित select_no_atn:1;
	अचिन्हित fix_capacity:1;	/* READ_CAPACITY is too high by 1 */
	अचिन्हित guess_capacity:1;	/* READ_CAPACITY might be too high by 1 */
	अचिन्हित retry_hwerror:1;	/* Retry HARDWARE_ERROR */
	अचिन्हित last_sector_bug:1;	/* करो not use multisector accesses on
					   SD_LAST_BUGGY_SECTORS */
	अचिन्हित no_पढ़ो_disc_info:1;	/* Aव्योम READ_DISC_INFO cmds */
	अचिन्हित no_पढ़ो_capacity_16:1; /* Aव्योम READ_CAPACITY_16 cmds */
	अचिन्हित try_rc_10_first:1;	/* Try READ_CAPACACITY_10 first */
	अचिन्हित security_supported:1;	/* Supports Security Protocols */
	अचिन्हित is_visible:1;	/* is the device visible in sysfs */
	अचिन्हित wce_शेष_on:1;	/* Cache is ON by शेष */
	अचिन्हित no_dअगर:1;	/* T10 PI (DIF) should be disabled */
	अचिन्हित broken_fua:1;		/* Don't set FUA bit */
	अचिन्हित lun_in_cdb:1;		/* Store LUN bits in CDB[1] */
	अचिन्हित unmap_limit_क्रम_ws:1;	/* Use the UNMAP limit क्रम WRITE SAME */
	अचिन्हित rpm_स्वतःsuspend:1;	/* Enable runसमय स्वतःsuspend at device
					 * creation समय */

	bool offline_alपढ़ोy;		/* Device offline message logged */

	atomic_t disk_events_disable_depth; /* disable depth क्रम disk events */

	DECLARE_BITMAP(supported_events, SDEV_EVT_MAXBITS); /* supported events */
	DECLARE_BITMAP(pending_events, SDEV_EVT_MAXBITS); /* pending events */
	काष्ठा list_head event_list;	/* निश्चितed events */
	काष्ठा work_काष्ठा event_work;

	अचिन्हित पूर्णांक max_device_blocked; /* what device_blocked counts करोwn from  */
#घोषणा SCSI_DEFAULT_DEVICE_BLOCKED	3

	atomic_t iorequest_cnt;
	atomic_t ioकरोne_cnt;
	atomic_t ioerr_cnt;

	काष्ठा device		sdev_gendev,
				sdev_dev;

	काष्ठा execute_work	ew; /* used to get process context on put */
	काष्ठा work_काष्ठा	requeue_work;

	काष्ठा scsi_device_handler *handler;
	व्योम			*handler_data;

	माप_प्रकार			dma_drain_len;
	व्योम			*dma_drain_buf;

	अचिन्हित अक्षर		access_state;
	काष्ठा mutex		state_mutex;
	क्रमागत scsi_device_state sdev_state;
	काष्ठा task_काष्ठा	*quiesced_by;
	अचिन्हित दीर्घ		sdev_data[];
पूर्ण __attribute__((aligned(माप(अचिन्हित दीर्घ))));

#घोषणा	to_scsi_device(d)	\
	container_of(d, काष्ठा scsi_device, sdev_gendev)
#घोषणा	class_to_sdev(d)	\
	container_of(d, काष्ठा scsi_device, sdev_dev)
#घोषणा transport_class_to_sdev(class_dev) \
	to_scsi_device(class_dev->parent)

#घोषणा sdev_dbg(sdev, fmt, a...) \
	dev_dbg(&(sdev)->sdev_gendev, fmt, ##a)

/*
 * like scmd_prपूर्णांकk, but the device name is passed in
 * as a string poपूर्णांकer
 */
__म_लिखो(4, 5) व्योम
sdev_prefix_prपूर्णांकk(स्थिर अक्षर *, स्थिर काष्ठा scsi_device *, स्थिर अक्षर *,
		स्थिर अक्षर *, ...);

#घोषणा sdev_prपूर्णांकk(l, sdev, fmt, a...)				\
	sdev_prefix_prपूर्णांकk(l, sdev, शून्य, fmt, ##a)

__म_लिखो(3, 4) व्योम
scmd_prपूर्णांकk(स्थिर अक्षर *, स्थिर काष्ठा scsi_cmnd *, स्थिर अक्षर *, ...);

#घोषणा scmd_dbg(scmd, fmt, a...)					   \
	करो अणु								   \
		अगर ((scmd)->request->rq_disk)				   \
			sdev_dbg((scmd)->device, "[%s] " fmt,		   \
				 (scmd)->request->rq_disk->disk_name, ##a);\
		अन्यथा							   \
			sdev_dbg((scmd)->device, fmt, ##a);		   \
	पूर्ण जबतक (0)

क्रमागत scsi_target_state अणु
	STARGET_CREATED = 1,
	STARGET_RUNNING,
	STARGET_REMOVE,
	STARGET_CREATED_REMOVE,
	STARGET_DEL,
पूर्ण;

/*
 * scsi_target: representation of a scsi target, क्रम now, this is only
 * used क्रम single_lun devices. If no one has active IO to the target,
 * starget_sdev_user is शून्य, अन्यथा it poपूर्णांकs to the active sdev.
 */
काष्ठा scsi_target अणु
	काष्ठा scsi_device	*starget_sdev_user;
	काष्ठा list_head	siblings;
	काष्ठा list_head	devices;
	काष्ठा device		dev;
	काष्ठा kref		reap_ref; /* last put renders target invisible */
	अचिन्हित पूर्णांक		channel;
	अचिन्हित पूर्णांक		id; /* target id ... replace
				     * scsi_device.id eventually */
	अचिन्हित पूर्णांक		create:1; /* संकेत that it needs to be added */
	अचिन्हित पूर्णांक		single_lun:1;	/* Indicates we should only
						 * allow I/O to one of the luns
						 * क्रम the device at a समय. */
	अचिन्हित पूर्णांक		pdt_1f_क्रम_no_lun:1;	/* PDT = 0x1f
						 * means no lun present. */
	अचिन्हित पूर्णांक		no_report_luns:1;	/* Don't use
						 * REPORT LUNS क्रम scanning. */
	अचिन्हित पूर्णांक		expecting_lun_change:1;	/* A device has reported
						 * a 3F/0E UA, other devices on
						 * the same target will also. */
	/* commands actually active on LLD. */
	atomic_t		target_busy;
	atomic_t		target_blocked;

	/*
	 * LLDs should set this in the slave_alloc host ढाँचा callout.
	 * If set to zero then there is not limit.
	 */
	अचिन्हित पूर्णांक		can_queue;
	अचिन्हित पूर्णांक		max_target_blocked;
#घोषणा SCSI_DEFAULT_TARGET_BLOCKED	3

	अक्षर			scsi_level;
	क्रमागत scsi_target_state	state;
	व्योम 			*hostdata; /* available to low-level driver */
	अचिन्हित दीर्घ		starget_data[]; /* क्रम the transport */
	/* starget_data must be the last element!!!! */
पूर्ण __attribute__((aligned(माप(अचिन्हित दीर्घ))));

#घोषणा to_scsi_target(d)	container_of(d, काष्ठा scsi_target, dev)
अटल अंतरभूत काष्ठा scsi_target *scsi_target(काष्ठा scsi_device *sdev)
अणु
	वापस to_scsi_target(sdev->sdev_gendev.parent);
पूर्ण
#घोषणा transport_class_to_starget(class_dev) \
	to_scsi_target(class_dev->parent)

#घोषणा starget_prपूर्णांकk(prefix, starget, fmt, a...)	\
	dev_prपूर्णांकk(prefix, &(starget)->dev, fmt, ##a)

बाह्य काष्ठा scsi_device *__scsi_add_device(काष्ठा Scsi_Host *,
		uपूर्णांक, uपूर्णांक, u64, व्योम *hostdata);
बाह्य पूर्णांक scsi_add_device(काष्ठा Scsi_Host *host, uपूर्णांक channel,
			   uपूर्णांक target, u64 lun);
बाह्य पूर्णांक scsi_रेजिस्टर_device_handler(काष्ठा scsi_device_handler *scsi_dh);
बाह्य व्योम scsi_हटाओ_device(काष्ठा scsi_device *);
बाह्य पूर्णांक scsi_unरेजिस्टर_device_handler(काष्ठा scsi_device_handler *scsi_dh);
व्योम scsi_attach_vpd(काष्ठा scsi_device *sdev);

बाह्य काष्ठा scsi_device *scsi_device_from_queue(काष्ठा request_queue *q);
बाह्य पूर्णांक __must_check scsi_device_get(काष्ठा scsi_device *);
बाह्य व्योम scsi_device_put(काष्ठा scsi_device *);
बाह्य काष्ठा scsi_device *scsi_device_lookup(काष्ठा Scsi_Host *,
					      uपूर्णांक, uपूर्णांक, u64);
बाह्य काष्ठा scsi_device *__scsi_device_lookup(काष्ठा Scsi_Host *,
						uपूर्णांक, uपूर्णांक, u64);
बाह्य काष्ठा scsi_device *scsi_device_lookup_by_target(काष्ठा scsi_target *,
							u64);
बाह्य काष्ठा scsi_device *__scsi_device_lookup_by_target(काष्ठा scsi_target *,
							  u64);
बाह्य व्योम starget_क्रम_each_device(काष्ठा scsi_target *, व्योम *,
		     व्योम (*fn)(काष्ठा scsi_device *, व्योम *));
बाह्य व्योम __starget_क्रम_each_device(काष्ठा scsi_target *, व्योम *,
				      व्योम (*fn)(काष्ठा scsi_device *,
						 व्योम *));

/* only exposed to implement shost_क्रम_each_device */
बाह्य काष्ठा scsi_device *__scsi_iterate_devices(काष्ठा Scsi_Host *,
						  काष्ठा scsi_device *);

/**
 * shost_क्रम_each_device - iterate over all devices of a host
 * @sdev: the &काष्ठा scsi_device to use as a cursor
 * @shost: the &काष्ठा scsi_host to iterate over
 *
 * Iterator that वापसs each device attached to @shost.  This loop
 * takes a reference on each device and releases it at the end.  If
 * you अवरोध out of the loop, you must call scsi_device_put(sdev).
 */
#घोषणा shost_क्रम_each_device(sdev, shost) \
	क्रम ((sdev) = __scsi_iterate_devices((shost), शून्य); \
	     (sdev); \
	     (sdev) = __scsi_iterate_devices((shost), (sdev)))

/**
 * __shost_क्रम_each_device - iterate over all devices of a host (UNLOCKED)
 * @sdev: the &काष्ठा scsi_device to use as a cursor
 * @shost: the &काष्ठा scsi_host to iterate over
 *
 * Iterator that वापसs each device attached to @shost.  It करोes _not_
 * take a reference on the scsi_device, so the whole loop must be
 * रक्षित by shost->host_lock.
 *
 * Note: The only reason to use this is because you need to access the
 * device list in पूर्णांकerrupt context.  Otherwise you really want to use
 * shost_क्रम_each_device instead.
 */
#घोषणा __shost_क्रम_each_device(sdev, shost) \
	list_क्रम_each_entry((sdev), &((shost)->__devices), siblings)

बाह्य पूर्णांक scsi_change_queue_depth(काष्ठा scsi_device *, पूर्णांक);
बाह्य पूर्णांक scsi_track_queue_full(काष्ठा scsi_device *, पूर्णांक);

बाह्य पूर्णांक scsi_set_medium_removal(काष्ठा scsi_device *, अक्षर);

बाह्य पूर्णांक scsi_mode_sense(काष्ठा scsi_device *sdev, पूर्णांक dbd, पूर्णांक modepage,
			   अचिन्हित अक्षर *buffer, पूर्णांक len, पूर्णांक समयout,
			   पूर्णांक retries, काष्ठा scsi_mode_data *data,
			   काष्ठा scsi_sense_hdr *);
बाह्य पूर्णांक scsi_mode_select(काष्ठा scsi_device *sdev, पूर्णांक pf, पूर्णांक sp,
			    पूर्णांक modepage, अचिन्हित अक्षर *buffer, पूर्णांक len,
			    पूर्णांक समयout, पूर्णांक retries,
			    काष्ठा scsi_mode_data *data,
			    काष्ठा scsi_sense_hdr *);
बाह्य पूर्णांक scsi_test_unit_पढ़ोy(काष्ठा scsi_device *sdev, पूर्णांक समयout,
				पूर्णांक retries, काष्ठा scsi_sense_hdr *sshdr);
बाह्य पूर्णांक scsi_get_vpd_page(काष्ठा scsi_device *, u8 page, अचिन्हित अक्षर *buf,
			     पूर्णांक buf_len);
बाह्य पूर्णांक scsi_report_opcode(काष्ठा scsi_device *sdev, अचिन्हित अक्षर *buffer,
			      अचिन्हित पूर्णांक len, अचिन्हित अक्षर opcode);
बाह्य पूर्णांक scsi_device_set_state(काष्ठा scsi_device *sdev,
				 क्रमागत scsi_device_state state);
बाह्य काष्ठा scsi_event *sdev_evt_alloc(क्रमागत scsi_device_event evt_type,
					  gfp_t gfpflags);
बाह्य व्योम sdev_evt_send(काष्ठा scsi_device *sdev, काष्ठा scsi_event *evt);
बाह्य व्योम sdev_evt_send_simple(काष्ठा scsi_device *sdev,
			  क्रमागत scsi_device_event evt_type, gfp_t gfpflags);
बाह्य पूर्णांक scsi_device_quiesce(काष्ठा scsi_device *sdev);
बाह्य व्योम scsi_device_resume(काष्ठा scsi_device *sdev);
बाह्य व्योम scsi_target_quiesce(काष्ठा scsi_target *);
बाह्य व्योम scsi_target_resume(काष्ठा scsi_target *);
बाह्य व्योम scsi_scan_target(काष्ठा device *parent, अचिन्हित पूर्णांक channel,
			     अचिन्हित पूर्णांक id, u64 lun,
			     क्रमागत scsi_scan_mode rescan);
बाह्य व्योम scsi_target_reap(काष्ठा scsi_target *);
बाह्य व्योम scsi_target_block(काष्ठा device *);
बाह्य व्योम scsi_target_unblock(काष्ठा device *, क्रमागत scsi_device_state);
बाह्य व्योम scsi_हटाओ_target(काष्ठा device *);
बाह्य स्थिर अक्षर *scsi_device_state_name(क्रमागत scsi_device_state);
बाह्य पूर्णांक scsi_is_sdev_device(स्थिर काष्ठा device *);
बाह्य पूर्णांक scsi_is_target_device(स्थिर काष्ठा device *);
बाह्य व्योम scsi_sanitize_inquiry_string(अचिन्हित अक्षर *s, पूर्णांक len);
बाह्य पूर्णांक __scsi_execute(काष्ठा scsi_device *sdev, स्थिर अचिन्हित अक्षर *cmd,
			पूर्णांक data_direction, व्योम *buffer, अचिन्हित bufflen,
			अचिन्हित अक्षर *sense, काष्ठा scsi_sense_hdr *sshdr,
			पूर्णांक समयout, पूर्णांक retries, u64 flags,
			req_flags_t rq_flags, पूर्णांक *resid);
/* Make sure any sense buffer is the correct size. */
#घोषणा scsi_execute(sdev, cmd, data_direction, buffer, bufflen, sense,	\
		     sshdr, समयout, retries, flags, rq_flags, resid)	\
(अणु									\
	BUILD_BUG_ON((sense) != शून्य &&					\
		     माप(sense) != SCSI_SENSE_BUFFERSIZE);		\
	__scsi_execute(sdev, cmd, data_direction, buffer, bufflen,	\
		       sense, sshdr, समयout, retries, flags, rq_flags,	\
		       resid);						\
पूर्ण)
अटल अंतरभूत पूर्णांक scsi_execute_req(काष्ठा scsi_device *sdev,
	स्थिर अचिन्हित अक्षर *cmd, पूर्णांक data_direction, व्योम *buffer,
	अचिन्हित bufflen, काष्ठा scsi_sense_hdr *sshdr, पूर्णांक समयout,
	पूर्णांक retries, पूर्णांक *resid)
अणु
	वापस scsi_execute(sdev, cmd, data_direction, buffer,
		bufflen, शून्य, sshdr, समयout, retries,  0, 0, resid);
पूर्ण
बाह्य व्योम sdev_disable_disk_events(काष्ठा scsi_device *sdev);
बाह्य व्योम sdev_enable_disk_events(काष्ठा scsi_device *sdev);
बाह्य पूर्णांक scsi_vpd_lun_id(काष्ठा scsi_device *, अक्षर *, माप_प्रकार);
बाह्य पूर्णांक scsi_vpd_tpg_id(काष्ठा scsi_device *, पूर्णांक *);

#अगर_घोषित CONFIG_PM
बाह्य पूर्णांक scsi_स्वतःpm_get_device(काष्ठा scsi_device *);
बाह्य व्योम scsi_स्वतःpm_put_device(काष्ठा scsi_device *);
#अन्यथा
अटल अंतरभूत पूर्णांक scsi_स्वतःpm_get_device(काष्ठा scsi_device *d) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम scsi_स्वतःpm_put_device(काष्ठा scsi_device *d) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_PM */

अटल अंतरभूत पूर्णांक __must_check scsi_device_reprobe(काष्ठा scsi_device *sdev)
अणु
	वापस device_reprobe(&sdev->sdev_gendev);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक sdev_channel(काष्ठा scsi_device *sdev)
अणु
	वापस sdev->channel;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक sdev_id(काष्ठा scsi_device *sdev)
अणु
	वापस sdev->id;
पूर्ण

#घोषणा scmd_id(scmd) sdev_id((scmd)->device)
#घोषणा scmd_channel(scmd) sdev_channel((scmd)->device)

/*
 * checks क्रम positions of the SCSI state machine
 */
अटल अंतरभूत पूर्णांक scsi_device_online(काष्ठा scsi_device *sdev)
अणु
	वापस (sdev->sdev_state != SDEV_OFFLINE &&
		sdev->sdev_state != SDEV_TRANSPORT_OFFLINE &&
		sdev->sdev_state != SDEV_DEL);
पूर्ण
अटल अंतरभूत पूर्णांक scsi_device_blocked(काष्ठा scsi_device *sdev)
अणु
	वापस sdev->sdev_state == SDEV_BLOCK ||
		sdev->sdev_state == SDEV_CREATED_BLOCK;
पूर्ण
अटल अंतरभूत पूर्णांक scsi_device_created(काष्ठा scsi_device *sdev)
अणु
	वापस sdev->sdev_state == SDEV_CREATED ||
		sdev->sdev_state == SDEV_CREATED_BLOCK;
पूर्ण

पूर्णांक scsi_पूर्णांकernal_device_block_noरुको(काष्ठा scsi_device *sdev);
पूर्णांक scsi_पूर्णांकernal_device_unblock_noरुको(काष्ठा scsi_device *sdev,
					क्रमागत scsi_device_state new_state);

/* accessor functions क्रम the SCSI parameters */
अटल अंतरभूत पूर्णांक scsi_device_sync(काष्ठा scsi_device *sdev)
अणु
	वापस sdev->sdtr;
पूर्ण
अटल अंतरभूत पूर्णांक scsi_device_wide(काष्ठा scsi_device *sdev)
अणु
	वापस sdev->wdtr;
पूर्ण
अटल अंतरभूत पूर्णांक scsi_device_dt(काष्ठा scsi_device *sdev)
अणु
	वापस sdev->ppr;
पूर्ण
अटल अंतरभूत पूर्णांक scsi_device_dt_only(काष्ठा scsi_device *sdev)
अणु
	अगर (sdev->inquiry_len < 57)
		वापस 0;
	वापस (sdev->inquiry[56] & 0x0c) == 0x04;
पूर्ण
अटल अंतरभूत पूर्णांक scsi_device_ius(काष्ठा scsi_device *sdev)
अणु
	अगर (sdev->inquiry_len < 57)
		वापस 0;
	वापस sdev->inquiry[56] & 0x01;
पूर्ण
अटल अंतरभूत पूर्णांक scsi_device_qas(काष्ठा scsi_device *sdev)
अणु
	अगर (sdev->inquiry_len < 57)
		वापस 0;
	वापस sdev->inquiry[56] & 0x02;
पूर्ण
अटल अंतरभूत पूर्णांक scsi_device_enclosure(काष्ठा scsi_device *sdev)
अणु
	वापस sdev->inquiry ? (sdev->inquiry[6] & (1<<6)) : 1;
पूर्ण

अटल अंतरभूत पूर्णांक scsi_device_protection(काष्ठा scsi_device *sdev)
अणु
	अगर (sdev->no_dअगर)
		वापस 0;

	वापस sdev->scsi_level > SCSI_2 && sdev->inquiry[5] & (1<<0);
पूर्ण

अटल अंतरभूत पूर्णांक scsi_device_tpgs(काष्ठा scsi_device *sdev)
अणु
	वापस sdev->inquiry ? (sdev->inquiry[5] >> 4) & 0x3 : 0;
पूर्ण

/**
 * scsi_device_supports_vpd - test अगर a device supports VPD pages
 * @sdev: the &काष्ठा scsi_device to test
 *
 * If the 'try_vpd_pages' flag is set it takes precedence.
 * Otherwise we will assume VPD pages are supported अगर the
 * SCSI level is at least SPC-3 and 'skip_vpd_pages' is not set.
 */
अटल अंतरभूत पूर्णांक scsi_device_supports_vpd(काष्ठा scsi_device *sdev)
अणु
	/* Attempt VPD inquiry अगर the device blacklist explicitly calls
	 * क्रम it.
	 */
	अगर (sdev->try_vpd_pages)
		वापस 1;
	/*
	 * Although VPD inquiries can go to SCSI-2 type devices,
	 * some USB ones crash on receiving them, and the pages
	 * we currently ask क्रम are mandatory क्रम SPC-2 and beyond
	 */
	अगर (sdev->scsi_level >= SCSI_SPC_2 && !sdev->skip_vpd_pages)
		वापस 1;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक scsi_device_busy(काष्ठा scsi_device *sdev)
अणु
	वापस sbiपंचांगap_weight(&sdev->budget_map);
पूर्ण

#घोषणा MODULE_ALIAS_SCSI_DEVICE(type) \
	MODULE_ALIAS("scsi:t-" __stringअगरy(type) "*")
#घोषणा SCSI_DEVICE_MODALIAS_FMT "scsi:t-0x%02x"

#पूर्ण_अगर /* _SCSI_SCSI_DEVICE_H */
