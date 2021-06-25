<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SCSI_SCSI_HOST_H
#घोषणा _SCSI_SCSI_HOST_H

#समावेश <linux/device.h>
#समावेश <linux/list.h>
#समावेश <linux/types.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/mutex.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/blk-mq.h>
#समावेश <scsi/scsi.h>

काष्ठा block_device;
काष्ठा completion;
काष्ठा module;
काष्ठा scsi_cmnd;
काष्ठा scsi_device;
काष्ठा scsi_host_cmd_pool;
काष्ठा scsi_target;
काष्ठा Scsi_Host;
काष्ठा scsi_transport_ढाँचा;


#घोषणा SG_ALL	SG_CHUNK_SIZE

#घोषणा MODE_UNKNOWN 0x00
#घोषणा MODE_INITIATOR 0x01
#घोषणा MODE_TARGET 0x02

काष्ठा scsi_host_ढाँचा अणु
	/*
	 * Put fields referenced in IO submission path together in
	 * same cacheline
	 */

	/*
	 * Additional per-command data allocated क्रम the driver.
	 */
	अचिन्हित पूर्णांक cmd_size;

	/*
	 * The queuecommand function is used to queue up a scsi
	 * command block to the LLDD.  When the driver finished
	 * processing the command the करोne callback is invoked.
	 *
	 * If queuecommand वापसs 0, then the driver has accepted the
	 * command.  It must also push it to the HBA अगर the scsi_cmnd
	 * flag SCMD_LAST is set, or अगर the driver करोes not implement
	 * commit_rqs.  The करोne() function must be called on the command
	 * when the driver has finished with it. (you may call करोne on the
	 * command beक्रमe queuecommand वापसs, but in this हाल you
	 * *must* वापस 0 from queuecommand).
	 *
	 * Queuecommand may also reject the command, in which हाल it may
	 * not touch the command and must not call करोne() क्रम it.
	 *
	 * There are two possible rejection वापसs:
	 *
	 *   SCSI_MLQUEUE_DEVICE_BUSY: Block this device temporarily, but
	 *   allow commands to other devices serviced by this host.
	 *
	 *   SCSI_MLQUEUE_HOST_BUSY: Block all devices served by this
	 *   host temporarily.
	 *
         * For compatibility, any other non-zero वापस is treated the
         * same as SCSI_MLQUEUE_HOST_BUSY.
	 *
	 * NOTE: "temporarily" means either until the next command क्रम#
	 * this device/host completes, or a period of समय determined by
	 * I/O pressure in the प्रणाली अगर there are no other outstanding
	 * commands.
	 *
	 * STATUS: REQUIRED
	 */
	पूर्णांक (* queuecommand)(काष्ठा Scsi_Host *, काष्ठा scsi_cmnd *);

	/*
	 * The commit_rqs function is used to trigger a hardware
	 * करोorbell after some requests have been queued with
	 * queuecommand, when an error is encountered beक्रमe sending
	 * the request with SCMD_LAST set.
	 *
	 * STATUS: OPTIONAL
	 */
	व्योम (*commit_rqs)(काष्ठा Scsi_Host *, u16);

	काष्ठा module *module;
	स्थिर अक्षर *name;

	/*
	 * The info function will वापस whatever useful inक्रमmation the
	 * developer sees fit.  If not provided, then the name field will
	 * be used instead.
	 *
	 * Status: OPTIONAL
	 */
	स्थिर अक्षर *(*info)(काष्ठा Scsi_Host *);

	/*
	 * Ioctl पूर्णांकerface
	 *
	 * Status: OPTIONAL
	 */
	पूर्णांक (*ioctl)(काष्ठा scsi_device *dev, अचिन्हित पूर्णांक cmd,
		     व्योम __user *arg);


#अगर_घोषित CONFIG_COMPAT
	/*
	 * Compat handler. Handle 32bit ABI.
	 * When unknown ioctl is passed वापस -ENOIOCTLCMD.
	 *
	 * Status: OPTIONAL
	 */
	पूर्णांक (*compat_ioctl)(काष्ठा scsi_device *dev, अचिन्हित पूर्णांक cmd,
			    व्योम __user *arg);
#पूर्ण_अगर

	पूर्णांक (*init_cmd_priv)(काष्ठा Scsi_Host *shost, काष्ठा scsi_cmnd *cmd);
	पूर्णांक (*निकास_cmd_priv)(काष्ठा Scsi_Host *shost, काष्ठा scsi_cmnd *cmd);

	/*
	 * This is an error handling strategy routine.  You करोn't need to
	 * define one of these अगर you करोn't want to - there is a शेष
	 * routine that is present that should work in most हालs.  For those
	 * driver authors that have the inclination and ability to ग_लिखो their
	 * own strategy routine, this is where it is specअगरied.  Note - the
	 * strategy routine is *ALWAYS* run in the context of the kernel eh
	 * thपढ़ो.  Thus you are guaranteed to *NOT* be in an पूर्णांकerrupt
	 * handler when you execute this, and you are also guaranteed to
	 * *NOT* have any other commands being queued जबतक you are in the
	 * strategy routine. When you वापस from this function, operations
	 * वापस to normal.
	 *
	 * See scsi_error.c scsi_unjam_host क्रम additional comments about
	 * what this function should and should not be attempting to करो.
	 *
	 * Status: REQUIRED	(at least one of them)
	 */
	पूर्णांक (* eh_पात_handler)(काष्ठा scsi_cmnd *);
	पूर्णांक (* eh_device_reset_handler)(काष्ठा scsi_cmnd *);
	पूर्णांक (* eh_target_reset_handler)(काष्ठा scsi_cmnd *);
	पूर्णांक (* eh_bus_reset_handler)(काष्ठा scsi_cmnd *);
	पूर्णांक (* eh_host_reset_handler)(काष्ठा scsi_cmnd *);

	/*
	 * Beक्रमe the mid layer attempts to scan क्रम a new device where none
	 * currently exists, it will call this entry in your driver.  Should
	 * your driver need to allocate any काष्ठाs or perक्रमm any other init
	 * items in order to send commands to a currently unused target/lun
	 * combo, then this is where you can perक्रमm those allocations.  This
	 * is specअगरically so that drivers won't have to perक्रमm any kind of
	 * "is this a new device" checks in their queuecommand routine,
	 * thereby making the hot path a bit quicker.
	 *
	 * Return values: 0 on success, non-0 on failure
	 *
	 * Deallocation:  If we didn't find any devices at this ID, you will
	 * get an immediate call to slave_destroy().  If we find something
	 * here then you will get a call to slave_configure(), then the
	 * device will be used क्रम however दीर्घ it is kept around, then when
	 * the device is हटाओd from the प्रणाली (or * possibly at reboot
	 * समय), you will then get a call to slave_destroy().  This is
	 * assuming you implement slave_configure and slave_destroy.
	 * However, अगर you allocate memory and hang it off the device काष्ठा,
	 * then you must implement the slave_destroy() routine at a minimum
	 * in order to aव्योम leaking memory
	 * each समय a device is tore करोwn.
	 *
	 * Status: OPTIONAL
	 */
	पूर्णांक (* slave_alloc)(काष्ठा scsi_device *);

	/*
	 * Once the device has responded to an INQUIRY and we know the
	 * device is online, we call पूर्णांकo the low level driver with the
	 * काष्ठा scsi_device *.  If the low level device driver implements
	 * this function, it *must* perक्रमm the task of setting the queue
	 * depth on the device.  All other tasks are optional and depend
	 * on what the driver supports and various implementation details.
	 * 
	 * Things currently recommended to be handled at this समय include:
	 *
	 * 1.  Setting the device queue depth.  Proper setting of this is
	 *     described in the comments क्रम scsi_change_queue_depth.
	 * 2.  Determining अगर the device supports the various synchronous
	 *     negotiation protocols.  The device काष्ठा will alपढ़ोy have
	 *     responded to INQUIRY and the results of the standard items
	 *     will have been shoved पूर्णांकo the various device flag bits, eg.
	 *     device->sdtr will be true अगर the device supports SDTR messages.
	 * 3.  Allocating command काष्ठाs that the device will need.
	 * 4.  Setting the शेष समयout on this device (अगर needed).
	 * 5.  Anything अन्यथा the low level driver might want to करो on a device
	 *     specअगरic setup basis...
	 * 6.  Return 0 on success, non-0 on error.  The device will be marked
	 *     as offline on error so that no access will occur.  If you वापस
	 *     non-0, your slave_destroy routine will never get called क्रम this
	 *     device, so करोn't leave any loose memory hanging around, clean
	 *     up after yourself beक्रमe वापसing non-0
	 *
	 * Status: OPTIONAL
	 */
	पूर्णांक (* slave_configure)(काष्ठा scsi_device *);

	/*
	 * Immediately prior to deallocating the device and after all activity
	 * has ceased the mid layer calls this poपूर्णांक so that the low level
	 * driver may completely detach itself from the scsi device and vice
	 * versa.  The low level driver is responsible क्रम मुक्तing any memory
	 * it allocated in the slave_alloc or slave_configure calls. 
	 *
	 * Status: OPTIONAL
	 */
	व्योम (* slave_destroy)(काष्ठा scsi_device *);

	/*
	 * Beक्रमe the mid layer attempts to scan क्रम a new device attached
	 * to a target where no target currently exists, it will call this
	 * entry in your driver.  Should your driver need to allocate any
	 * काष्ठाs or perक्रमm any other init items in order to send commands
	 * to a currently unused target, then this is where you can perक्रमm
	 * those allocations.
	 *
	 * Return values: 0 on success, non-0 on failure
	 *
	 * Status: OPTIONAL
	 */
	पूर्णांक (* target_alloc)(काष्ठा scsi_target *);

	/*
	 * Immediately prior to deallocating the target काष्ठाure, and
	 * after all activity to attached scsi devices has ceased, the
	 * midlayer calls this poपूर्णांक so that the driver may deallocate
	 * and terminate any references to the target.
	 *
	 * Status: OPTIONAL
	 */
	व्योम (* target_destroy)(काष्ठा scsi_target *);

	/*
	 * If a host has the ability to discover tarमाला_लो on its own instead
	 * of scanning the entire bus, it can fill in this function and
	 * call scsi_scan_host().  This function will be called periodically
	 * until it वापसs 1 with the scsi_host and the elapsed समय of
	 * the scan in jअगरfies.
	 *
	 * Status: OPTIONAL
	 */
	पूर्णांक (* scan_finished)(काष्ठा Scsi_Host *, अचिन्हित दीर्घ);

	/*
	 * If the host wants to be called beक्रमe the scan starts, but
	 * after the midlayer has set up पढ़ोy क्रम the scan, it can fill
	 * in this function.
	 *
	 * Status: OPTIONAL
	 */
	व्योम (* scan_start)(काष्ठा Scsi_Host *);

	/*
	 * Fill in this function to allow the queue depth of this host
	 * to be changeable (on a per device basis).  Returns either
	 * the current queue depth setting (may be dअगरferent from what
	 * was passed in) or an error.  An error should only be
	 * वापसed अगर the requested depth is legal but the driver was
	 * unable to set it.  If the requested depth is illegal, the
	 * driver should set and वापस the बंदst legal queue depth.
	 *
	 * Status: OPTIONAL
	 */
	पूर्णांक (* change_queue_depth)(काष्ठा scsi_device *, पूर्णांक);

	/*
	 * This functions lets the driver expose the queue mapping
	 * to the block layer.
	 *
	 * Status: OPTIONAL
	 */
	पूर्णांक (* map_queues)(काष्ठा Scsi_Host *shost);

	/*
	 * SCSI पूर्णांकerface of blk_poll - poll क्रम IO completions.
	 * Only applicable अगर SCSI LLD exposes multiple h/w queues.
	 *
	 * Return value: Number of completed entries found.
	 *
	 * Status: OPTIONAL
	 */
	पूर्णांक (* mq_poll)(काष्ठा Scsi_Host *shost, अचिन्हित पूर्णांक queue_num);

	/*
	 * Check अगर scatterlists need to be padded क्रम DMA draining.
	 *
	 * Status: OPTIONAL
	 */
	bool (* dma_need_drain)(काष्ठा request *rq);

	/*
	 * This function determines the BIOS parameters क्रम a given
	 * harddisk.  These tend to be numbers that are made up by
	 * the host adapter.  Parameters:
	 * size, device, list (heads, sectors, cylinders)
	 *
	 * Status: OPTIONAL
	 */
	पूर्णांक (* bios_param)(काष्ठा scsi_device *, काष्ठा block_device *,
			sector_t, पूर्णांक []);

	/*
	 * This function is called when one or more partitions on the
	 * device reach beyond the end of the device.
	 *
	 * Status: OPTIONAL
	 */
	व्योम (*unlock_native_capacity)(काष्ठा scsi_device *);

	/*
	 * Can be used to export driver statistics and other infos to the
	 * world outside the kernel ie. userspace and it also provides an
	 * पूर्णांकerface to feed the driver with inक्रमmation.
	 *
	 * Status: OBSOLETE
	 */
	पूर्णांक (*show_info)(काष्ठा seq_file *, काष्ठा Scsi_Host *);
	पूर्णांक (*ग_लिखो_info)(काष्ठा Scsi_Host *, अक्षर *, पूर्णांक);

	/*
	 * This is an optional routine that allows the transport to become
	 * involved when a scsi io समयr fires. The वापस value tells the
	 * समयr routine how to finish the io समयout handling.
	 *
	 * Status: OPTIONAL
	 */
	क्रमागत blk_eh_समयr_वापस (*eh_समयd_out)(काष्ठा scsi_cmnd *);
	/*
	 * Optional routine that allows the transport to decide अगर a cmd
	 * is retryable. Return true अगर the transport is in a state the
	 * cmd should be retried on.
	 */
	bool (*eh_should_retry_cmd)(काष्ठा scsi_cmnd *scmd);

	/* This is an optional routine that allows transport to initiate
	 * LLD adapter or firmware reset using sysfs attribute.
	 *
	 * Return values: 0 on success, -ve value on failure.
	 *
	 * Status: OPTIONAL
	 */

	पूर्णांक (*host_reset)(काष्ठा Scsi_Host *shost, पूर्णांक reset_type);
#घोषणा SCSI_ADAPTER_RESET	1
#घोषणा SCSI_FIRMWARE_RESET	2


	/*
	 * Name of proc directory
	 */
	स्थिर अक्षर *proc_name;

	/*
	 * Used to store the procfs directory अगर a driver implements the
	 * show_info method.
	 */
	काष्ठा proc_dir_entry *proc_dir;

	/*
	 * This determines अगर we will use a non-पूर्णांकerrupt driven
	 * or an पूर्णांकerrupt driven scheme.  It is set to the maximum number
	 * of simultaneous commands a single hw queue in HBA will accept.
	 */
	पूर्णांक can_queue;

	/*
	 * In many instances, especially where disconnect / reconnect are
	 * supported, our host also has an ID on the SCSI bus.  If this is
	 * the हाल, then it must be reserved.  Please set this_id to -1 अगर
	 * your setup is in single initiator mode, and the host lacks an
	 * ID.
	 */
	पूर्णांक this_id;

	/*
	 * This determines the degree to which the host adapter is capable
	 * of scatter-gather.
	 */
	अचिन्हित लघु sg_tablesize;
	अचिन्हित लघु sg_prot_tablesize;

	/*
	 * Set this अगर the host adapter has limitations beside segment count.
	 */
	अचिन्हित पूर्णांक max_sectors;

	/*
	 * Maximum size in bytes of a single segment.
	 */
	अचिन्हित पूर्णांक max_segment_size;

	/*
	 * DMA scatter gather segment boundary limit. A segment crossing this
	 * boundary will be split in two.
	 */
	अचिन्हित दीर्घ dma_boundary;

	अचिन्हित दीर्घ virt_boundary_mask;

	/*
	 * This specअगरies "machine infinity" क्रम host ढाँचाs which करोn't
	 * limit the transfer size.  Note this limit represents an असलolute
	 * maximum, and may be over the transfer limits allowed क्रम
	 * inभागidual devices (e.g. 256 क्रम SCSI-1).
	 */
#घोषणा SCSI_DEFAULT_MAX_SECTORS	1024

	/*
	 * True अगर this host adapter can make good use of linked commands.
	 * This will allow more than one command to be queued to a given
	 * unit on a given host.  Set this to the maximum number of command
	 * blocks to be provided क्रम each device.  Set this to 1 क्रम one
	 * command block per lun, 2 क्रम two, etc.  Do not set this to 0.
	 * You should make sure that the host adapter will करो the right thing
	 * beक्रमe you try setting this above 1.
	 */
	लघु cmd_per_lun;

	/*
	 * present contains counter indicating how many boards of this
	 * type were found when we did the scan.
	 */
	अचिन्हित अक्षर present;

	/* If use block layer to manage tags, this is tag allocation policy */
	पूर्णांक tag_alloc_policy;

	/*
	 * Track QUEUE_FULL events and reduce queue depth on demand.
	 */
	अचिन्हित track_queue_depth:1;

	/*
	 * This specअगरies the mode that a LLD supports.
	 */
	अचिन्हित supported_mode:2;

	/*
	 * True क्रम emulated SCSI host adapters (e.g. ATAPI).
	 */
	अचिन्हित emulated:1;

	/*
	 * True अगर the low-level driver perक्रमms its own reset-settle delays.
	 */
	अचिन्हित skip_settle_delay:1;

	/* True अगर the controller करोes not support WRITE SAME */
	अचिन्हित no_ग_लिखो_same:1;

	/* True अगर the host uses host-wide tagspace */
	अचिन्हित host_tagset:1;

	/*
	 * Countकरोwn क्रम host blocking with no commands outstanding.
	 */
	अचिन्हित पूर्णांक max_host_blocked;

	/*
	 * Default value क्रम the blocking.  If the queue is empty,
	 * host_blocked counts करोwn in the request_fn until it restarts
	 * host operations as zero is reached.  
	 *
	 * FIXME: This should probably be a value in the ढाँचा
	 */
#घोषणा SCSI_DEFAULT_HOST_BLOCKED	7

	/*
	 * Poपूर्णांकer to the sysfs class properties क्रम this host, शून्य terminated.
	 */
	काष्ठा device_attribute **shost_attrs;

	/*
	 * Poपूर्णांकer to the SCSI device properties क्रम this host, शून्य terminated.
	 */
	काष्ठा device_attribute **sdev_attrs;

	/*
	 * Poपूर्णांकer to the SCSI device attribute groups क्रम this host,
	 * शून्य terminated.
	 */
	स्थिर काष्ठा attribute_group **sdev_groups;

	/*
	 * Venकरोr Identअगरier associated with the host
	 *
	 * Note: When specअगरying venकरोr_id, be sure to पढ़ो the
	 *   Venकरोr Type and ID क्रमmatting requirements specअगरied in
	 *   scsi_netlink.h
	 */
	u64 venकरोr_id;

	काष्ठा scsi_host_cmd_pool *cmd_pool;

	/* Delay क्रम runसमय स्वतःsuspend */
	पूर्णांक rpm_स्वतःsuspend_delay;
पूर्ण;

/*
 * Temporary #घोषणा क्रम host lock push करोwn. Can be हटाओd when all
 * drivers have been updated to take advantage of unlocked
 * queuecommand.
 *
 */
#घोषणा DEF_SCSI_QCMD(func_name) \
	पूर्णांक func_name(काष्ठा Scsi_Host *shost, काष्ठा scsi_cmnd *cmd)	\
	अणु								\
		अचिन्हित दीर्घ irq_flags;				\
		पूर्णांक rc;							\
		spin_lock_irqsave(shost->host_lock, irq_flags);		\
		rc = func_name##_lck (cmd, cmd->scsi_करोne);			\
		spin_unlock_irqrestore(shost->host_lock, irq_flags);	\
		वापस rc;						\
	पूर्ण


/*
 * shost state: If you alter this, you also need to alter scsi_sysfs.c
 * (क्रम the ascii descriptions) and the state model enक्रमcer:
 * scsi_host_set_state()
 */
क्रमागत scsi_host_state अणु
	SHOST_CREATED = 1,
	SHOST_RUNNING,
	SHOST_CANCEL,
	SHOST_DEL,
	SHOST_RECOVERY,
	SHOST_CANCEL_RECOVERY,
	SHOST_DEL_RECOVERY,
पूर्ण;

काष्ठा Scsi_Host अणु
	/*
	 * __devices is रक्षित by the host_lock, but you should
	 * usually use scsi_device_lookup / shost_क्रम_each_device
	 * to access it and करोn't care about locking yourself.
	 * In the rare हाल of being in irq context you can use
	 * their __ prefixed variants with the lock held. NEVER
	 * access this list directly from a driver.
	 */
	काष्ठा list_head	__devices;
	काष्ठा list_head	__tarमाला_लो;
	
	काष्ठा list_head	starved_list;

	spinlock_t		शेष_lock;
	spinlock_t		*host_lock;

	काष्ठा mutex		scan_mutex;/* serialize scanning activity */

	काष्ठा list_head	eh_cmd_q;
	काष्ठा task_काष्ठा    * ehandler;  /* Error recovery thपढ़ो. */
	काष्ठा completion     * eh_action; /* Wait क्रम specअगरic actions on the
					      host. */
	रुको_queue_head_t       host_रुको;
	काष्ठा scsi_host_ढाँचा *hostt;
	काष्ठा scsi_transport_ढाँचा *transportt;

	/* Area to keep a shared tag map */
	काष्ठा blk_mq_tag_set	tag_set;

	atomic_t host_blocked;

	अचिन्हित पूर्णांक host_failed;	   /* commands that failed.
					      रक्षित by host_lock */
	अचिन्हित पूर्णांक host_eh_scheduled;    /* EH scheduled without command */
    
	अचिन्हित पूर्णांक host_no;  /* Used क्रम IOCTL_GET_IDLUN, /proc/scsi et al. */

	/* next two fields are used to bound the समय spent in error handling */
	पूर्णांक eh_deadline;
	अचिन्हित दीर्घ last_reset;


	/*
	 * These three parameters can be used to allow क्रम wide scsi,
	 * and क्रम host adapters that support multiple busses
	 * The last two should be set to 1 more than the actual max id
	 * or lun (e.g. 8 क्रम SCSI parallel प्रणालीs).
	 */
	अचिन्हित पूर्णांक max_channel;
	अचिन्हित पूर्णांक max_id;
	u64 max_lun;

	/*
	 * This is a unique identअगरier that must be asचिन्हित so that we
	 * have some way of identअगरying each detected host adapter properly
	 * and uniquely.  For hosts that करो not support more than one card
	 * in the प्रणाली at one समय, this करोes not need to be set.  It is
	 * initialized to 0 in scsi_रेजिस्टर.
	 */
	अचिन्हित पूर्णांक unique_id;

	/*
	 * The maximum length of SCSI commands that this host can accept.
	 * Probably 12 क्रम most host adapters, but could be 16 क्रम others.
	 * or 260 अगर the driver supports variable length cdbs.
	 * For drivers that करोn't set this field, a value of 12 is
	 * assumed.
	 */
	अचिन्हित लघु max_cmd_len;

	पूर्णांक this_id;
	पूर्णांक can_queue;
	लघु cmd_per_lun;
	लघु अचिन्हित पूर्णांक sg_tablesize;
	लघु अचिन्हित पूर्णांक sg_prot_tablesize;
	अचिन्हित पूर्णांक max_sectors;
	अचिन्हित पूर्णांक max_segment_size;
	अचिन्हित दीर्घ dma_boundary;
	अचिन्हित दीर्घ virt_boundary_mask;
	/*
	 * In scsi-mq mode, the number of hardware queues supported by the LLD.
	 *
	 * Note: it is assumed that each hardware queue has a queue depth of
	 * can_queue. In other words, the total queue depth per host
	 * is nr_hw_queues * can_queue. However, क्रम when host_tagset is set,
	 * the total queue depth is can_queue.
	 */
	अचिन्हित nr_hw_queues;
	अचिन्हित nr_maps;
	अचिन्हित active_mode:2;

	/*
	 * Host has requested that no further requests come through क्रम the
	 * समय being.
	 */
	अचिन्हित host_self_blocked:1;
    
	/*
	 * Host uses correct SCSI ordering not PC ordering. The bit is
	 * set क्रम the minority of drivers whose authors actually पढ़ो
	 * the spec ;).
	 */
	अचिन्हित reverse_ordering:1;

	/* Task mgmt function in progress */
	अचिन्हित पंचांगf_in_progress:1;

	/* Asynchronous scan in progress */
	अचिन्हित async_scan:1;

	/* Don't resume host in EH */
	अचिन्हित eh_noresume:1;

	/* The controller करोes not support WRITE SAME */
	अचिन्हित no_ग_लिखो_same:1;

	/* True अगर the host uses host-wide tagspace */
	अचिन्हित host_tagset:1;

	/* Host responded with लघु (<36 bytes) INQUIRY result */
	अचिन्हित लघु_inquiry:1;

	/* The transport requires the LUN bits NOT to be stored in CDB[1] */
	अचिन्हित no_scsi2_lun_in_cdb:1;

	/*
	 * Optional work queue to be utilized by the transport
	 */
	अक्षर work_q_name[20];
	काष्ठा workqueue_काष्ठा *work_q;

	/*
	 * Task management function work queue
	 */
	काष्ठा workqueue_काष्ठा *पंचांगf_work_q;

	/*
	 * Value host_blocked counts करोwn from
	 */
	अचिन्हित पूर्णांक max_host_blocked;

	/* Protection Inक्रमmation */
	अचिन्हित पूर्णांक prot_capabilities;
	अचिन्हित अक्षर prot_guard_type;

	/* legacy crap */
	अचिन्हित दीर्घ base;
	अचिन्हित दीर्घ io_port;
	अचिन्हित अक्षर n_io_port;
	अचिन्हित अक्षर dma_channel;
	अचिन्हित पूर्णांक  irq;
	

	क्रमागत scsi_host_state shost_state;

	/* ldm bits */
	काष्ठा device		shost_gendev, shost_dev;

	/*
	 * Poपूर्णांकs to the transport data (अगर any) which is allocated
	 * separately
	 */
	व्योम *shost_data;

	/*
	 * Poपूर्णांकs to the physical bus device we'd use to करो DMA
	 * Needed just in हाल we have भव hosts.
	 */
	काष्ठा device *dma_dev;

	/*
	 * We should ensure that this is aligned, both क्रम better perक्रमmance
	 * and also because some compilers (m68k) करोn't स्वतःmatically क्रमce
	 * alignment to a दीर्घ boundary.
	 */
	अचिन्हित दीर्घ hostdata[]  /* Used क्रम storage of host specअगरic stuff */
		__attribute__ ((aligned (माप(अचिन्हित दीर्घ))));
पूर्ण;

#घोषणा		class_to_shost(d)	\
	container_of(d, काष्ठा Scsi_Host, shost_dev)

#घोषणा shost_prपूर्णांकk(prefix, shost, fmt, a...)	\
	dev_prपूर्णांकk(prefix, &(shost)->shost_gendev, fmt, ##a)

अटल अंतरभूत व्योम *shost_priv(काष्ठा Scsi_Host *shost)
अणु
	वापस (व्योम *)shost->hostdata;
पूर्ण

पूर्णांक scsi_is_host_device(स्थिर काष्ठा device *);

अटल अंतरभूत काष्ठा Scsi_Host *dev_to_shost(काष्ठा device *dev)
अणु
	जबतक (!scsi_is_host_device(dev)) अणु
		अगर (!dev->parent)
			वापस शून्य;
		dev = dev->parent;
	पूर्ण
	वापस container_of(dev, काष्ठा Scsi_Host, shost_gendev);
पूर्ण

अटल अंतरभूत पूर्णांक scsi_host_in_recovery(काष्ठा Scsi_Host *shost)
अणु
	वापस shost->shost_state == SHOST_RECOVERY ||
		shost->shost_state == SHOST_CANCEL_RECOVERY ||
		shost->shost_state == SHOST_DEL_RECOVERY ||
		shost->पंचांगf_in_progress;
पूर्ण

बाह्य पूर्णांक scsi_queue_work(काष्ठा Scsi_Host *, काष्ठा work_काष्ठा *);
बाह्य व्योम scsi_flush_work(काष्ठा Scsi_Host *);

बाह्य काष्ठा Scsi_Host *scsi_host_alloc(काष्ठा scsi_host_ढाँचा *, पूर्णांक);
बाह्य पूर्णांक __must_check scsi_add_host_with_dma(काष्ठा Scsi_Host *,
					       काष्ठा device *,
					       काष्ठा device *);
बाह्य व्योम scsi_scan_host(काष्ठा Scsi_Host *);
बाह्य व्योम scsi_rescan_device(काष्ठा device *);
बाह्य व्योम scsi_हटाओ_host(काष्ठा Scsi_Host *);
बाह्य काष्ठा Scsi_Host *scsi_host_get(काष्ठा Scsi_Host *);
बाह्य पूर्णांक scsi_host_busy(काष्ठा Scsi_Host *shost);
बाह्य व्योम scsi_host_put(काष्ठा Scsi_Host *t);
बाह्य काष्ठा Scsi_Host *scsi_host_lookup(अचिन्हित लघु);
बाह्य स्थिर अक्षर *scsi_host_state_name(क्रमागत scsi_host_state);
बाह्य व्योम scsi_host_complete_all_commands(काष्ठा Scsi_Host *shost,
					    पूर्णांक status);

अटल अंतरभूत पूर्णांक __must_check scsi_add_host(काष्ठा Scsi_Host *host,
					     काष्ठा device *dev)
अणु
	वापस scsi_add_host_with_dma(host, dev, dev);
पूर्ण

अटल अंतरभूत काष्ठा device *scsi_get_device(काष्ठा Scsi_Host *shost)
अणु
        वापस shost->shost_gendev.parent;
पूर्ण

/**
 * scsi_host_scan_allowed - Is scanning of this host allowed
 * @shost:	Poपूर्णांकer to Scsi_Host.
 **/
अटल अंतरभूत पूर्णांक scsi_host_scan_allowed(काष्ठा Scsi_Host *shost)
अणु
	वापस shost->shost_state == SHOST_RUNNING ||
	       shost->shost_state == SHOST_RECOVERY;
पूर्ण

बाह्य व्योम scsi_unblock_requests(काष्ठा Scsi_Host *);
बाह्य व्योम scsi_block_requests(काष्ठा Scsi_Host *);
बाह्य पूर्णांक scsi_host_block(काष्ठा Scsi_Host *shost);
बाह्य पूर्णांक scsi_host_unblock(काष्ठा Scsi_Host *shost, पूर्णांक new_state);

व्योम scsi_host_busy_iter(काष्ठा Scsi_Host *,
			 bool (*fn)(काष्ठा scsi_cmnd *, व्योम *, bool), व्योम *priv);

काष्ठा class_container;

/*
 * These two functions are used to allocate and मुक्त a pseuकरो device
 * which will connect to the host adapter itself rather than any
 * physical device.  You must deallocate when you are करोne with the
 * thing.  This physical pseuकरो-device isn't real and won't be available
 * from any high-level drivers.
 */
बाह्य व्योम scsi_मुक्त_host_dev(काष्ठा scsi_device *);
बाह्य काष्ठा scsi_device *scsi_get_host_dev(काष्ठा Scsi_Host *);

/*
 * DIF defines the exchange of protection inक्रमmation between
 * initiator and SBC block device.
 *
 * DIX defines the exchange of protection inक्रमmation between OS and
 * initiator.
 */
क्रमागत scsi_host_prot_capabilities अणु
	SHOST_DIF_TYPE1_PROTECTION = 1 << 0, /* T10 DIF Type 1 */
	SHOST_DIF_TYPE2_PROTECTION = 1 << 1, /* T10 DIF Type 2 */
	SHOST_DIF_TYPE3_PROTECTION = 1 << 2, /* T10 DIF Type 3 */

	SHOST_DIX_TYPE0_PROTECTION = 1 << 3, /* DIX between OS and HBA only */
	SHOST_DIX_TYPE1_PROTECTION = 1 << 4, /* DIX with DIF Type 1 */
	SHOST_DIX_TYPE2_PROTECTION = 1 << 5, /* DIX with DIF Type 2 */
	SHOST_DIX_TYPE3_PROTECTION = 1 << 6, /* DIX with DIF Type 3 */
पूर्ण;

/*
 * SCSI hosts which support the Data Integrity Extensions must
 * indicate their capabilities by setting the prot_capabilities using
 * this call.
 */
अटल अंतरभूत व्योम scsi_host_set_prot(काष्ठा Scsi_Host *shost, अचिन्हित पूर्णांक mask)
अणु
	shost->prot_capabilities = mask;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक scsi_host_get_prot(काष्ठा Scsi_Host *shost)
अणु
	वापस shost->prot_capabilities;
पूर्ण

अटल अंतरभूत पूर्णांक scsi_host_prot_dma(काष्ठा Scsi_Host *shost)
अणु
	वापस shost->prot_capabilities >= SHOST_DIX_TYPE0_PROTECTION;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक scsi_host_dअगर_capable(काष्ठा Scsi_Host *shost, अचिन्हित पूर्णांक target_type)
अणु
	अटल अचिन्हित अक्षर cap[] = अणु 0,
				       SHOST_DIF_TYPE1_PROTECTION,
				       SHOST_DIF_TYPE2_PROTECTION,
				       SHOST_DIF_TYPE3_PROTECTION पूर्ण;

	अगर (target_type >= ARRAY_SIZE(cap))
		वापस 0;

	वापस shost->prot_capabilities & cap[target_type] ? target_type : 0;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक scsi_host_dix_capable(काष्ठा Scsi_Host *shost, अचिन्हित पूर्णांक target_type)
अणु
#अगर defined(CONFIG_BLK_DEV_INTEGRITY)
	अटल अचिन्हित अक्षर cap[] = अणु SHOST_DIX_TYPE0_PROTECTION,
				       SHOST_DIX_TYPE1_PROTECTION,
				       SHOST_DIX_TYPE2_PROTECTION,
				       SHOST_DIX_TYPE3_PROTECTION पूर्ण;

	अगर (target_type >= ARRAY_SIZE(cap))
		वापस 0;

	वापस shost->prot_capabilities & cap[target_type];
#पूर्ण_अगर
	वापस 0;
पूर्ण

/*
 * All DIX-capable initiators must support the T10-mandated CRC
 * checksum.  Controllers can optionally implement the IP checksum
 * scheme which has much lower impact on प्रणाली perक्रमmance.  Note
 * that the मुख्य rationale क्रम the checksum is to match पूर्णांकegrity
 * metadata with data.  Detecting bit errors are a job क्रम ECC memory
 * and buses.
 */

क्रमागत scsi_host_guard_type अणु
	SHOST_DIX_GUARD_CRC = 1 << 0,
	SHOST_DIX_GUARD_IP  = 1 << 1,
पूर्ण;

अटल अंतरभूत व्योम scsi_host_set_guard(काष्ठा Scsi_Host *shost, अचिन्हित अक्षर type)
अणु
	shost->prot_guard_type = type;
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर scsi_host_get_guard(काष्ठा Scsi_Host *shost)
अणु
	वापस shost->prot_guard_type;
पूर्ण

बाह्य पूर्णांक scsi_host_set_state(काष्ठा Scsi_Host *, क्रमागत scsi_host_state);

#पूर्ण_अगर /* _SCSI_SCSI_HOST_H */
