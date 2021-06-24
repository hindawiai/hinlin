<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (c) 2012 - 2015 UNISYS CORPORATION
 * All rights reserved.
 */

#समावेश <linux/debugfs.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/idr.h>
#समावेश <linux/module.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/visorbus.h>
#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>

#समावेश "iochannel.h"

/* The Send and Receive Buffers of the IO Queue may both be full */

#घोषणा IOS_ERROR_THRESHOLD  1000
#घोषणा MAX_PENDING_REQUESTS (MIN_NUMSIGNALS * 2)
#घोषणा VISORHBA_ERROR_COUNT 30

अटल काष्ठा dentry *visorhba_debugfs_dir;

/* GUIDS क्रम HBA channel type supported by this driver */
अटल काष्ठा visor_channeltype_descriptor visorhba_channel_types[] = अणु
	/* Note that the only channel type we expect to be reported by the
	 * bus driver is the VISOR_VHBA channel.
	 */
	अणु VISOR_VHBA_CHANNEL_GUID, "sparvhba", माप(काष्ठा channel_header),
	  VISOR_VHBA_CHANNEL_VERSIONID पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(visorbus, visorhba_channel_types);
MODULE_ALIAS("visorbus:" VISOR_VHBA_CHANNEL_GUID_STR);

काष्ठा visordisk_info अणु
	काष्ठा scsi_device *sdev;
	u32 valid;
	atomic_t ios_threshold;
	atomic_t error_count;
	काष्ठा visordisk_info *next;
पूर्ण;

काष्ठा scsipending अणु
	काष्ठा uiscmdrsp cmdrsp;
	/* The Data being tracked */
	व्योम *sent;
	/* Type of poपूर्णांकer that is being stored */
	अक्षर cmdtype;
पूर्ण;

/* Each scsi_host has a host_data area that contains this काष्ठा. */
काष्ठा visorhba_devdata अणु
	काष्ठा Scsi_Host *scsihost;
	काष्ठा visor_device *dev;
	काष्ठा list_head dev_info_list;
	/* Tracks the requests that have been क्रमwarded to
	 * the IOVM and haven't वापसed yet
	 */
	काष्ठा scsipending pending[MAX_PENDING_REQUESTS];
	/* Start search क्रम next pending मुक्त slot here */
	अचिन्हित पूर्णांक nextinsert;
	/* lock to protect data in devdata */
	spinlock_t privlock;
	bool serverकरोwn;
	bool serverchangingstate;
	अचिन्हित दीर्घ दीर्घ acquire_failed_cnt;
	अचिन्हित दीर्घ दीर्घ पूर्णांकerrupts_rcvd;
	अचिन्हित दीर्घ दीर्घ पूर्णांकerrupts_noपंचांगe;
	अचिन्हित दीर्घ दीर्घ पूर्णांकerrupts_disabled;
	u64 __iomem *flags_addr;
	काष्ठा visordisk_info head;
	अचिन्हित पूर्णांक max_buff_len;
	पूर्णांक devnum;
	काष्ठा uiscmdrsp *cmdrsp;
	/*
	 * allows us to pass पूर्णांक handles back-and-क्रमth between us and
	 * iovm, instead of raw poपूर्णांकers
	 */
	काष्ठा idr idr;

	काष्ठा dentry *debugfs_dir;
	काष्ठा dentry *debugfs_info;
पूर्ण;

काष्ठा visorhba_devices_खोलो अणु
	काष्ठा visorhba_devdata *devdata;
पूर्ण;

/*
 * add_scsipending_entry - Save off io command that is pending in
 *			   Service Partition
 * @devdata: Poपूर्णांकer to devdata
 * @cmdtype: Specअगरies the type of command pending
 * @new:     The command to be saved
 *
 * Saves off the io command that is being handled by the Service
 * Partition so that it can be handled when it completes. If new is
 * शून्य it is assumed the entry refers only to the cmdrsp.
 *
 * Return: Insert_location where entry was added on success,
 *	   -EBUSY अगर it can't
 */
अटल पूर्णांक add_scsipending_entry(काष्ठा visorhba_devdata *devdata,
				 अक्षर cmdtype, व्योम *new)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा scsipending *entry;
	पूर्णांक insert_location;

	spin_lock_irqsave(&devdata->privlock, flags);
	insert_location = devdata->nextinsert;
	जबतक (devdata->pending[insert_location].sent) अणु
		insert_location = (insert_location + 1) % MAX_PENDING_REQUESTS;
		अगर (insert_location == (पूर्णांक)devdata->nextinsert) अणु
			spin_unlock_irqrestore(&devdata->privlock, flags);
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	entry = &devdata->pending[insert_location];
	स_रखो(&entry->cmdrsp, 0, माप(entry->cmdrsp));
	entry->cmdtype = cmdtype;
	अगर (new)
		entry->sent = new;
	/* wants to send cmdrsp */
	अन्यथा
		entry->sent = &entry->cmdrsp;
	devdata->nextinsert = (insert_location + 1) % MAX_PENDING_REQUESTS;
	spin_unlock_irqrestore(&devdata->privlock, flags);

	वापस insert_location;
पूर्ण

/*
 * del_scsipending_ent - Removes an entry from the pending array
 * @devdata: Device holding the pending array
 * @del:     Entry to हटाओ
 *
 * Removes the entry poपूर्णांकed at by del and वापसs it.
 *
 * Return: The scsipending entry poपूर्णांकed to on success, शून्य on failure
 */
अटल व्योम *del_scsipending_ent(काष्ठा visorhba_devdata *devdata, पूर्णांक del)
अणु
	अचिन्हित दीर्घ flags;
	व्योम *sent;

	अगर (del >= MAX_PENDING_REQUESTS)
		वापस शून्य;

	spin_lock_irqsave(&devdata->privlock, flags);
	sent = devdata->pending[del].sent;
	devdata->pending[del].cmdtype = 0;
	devdata->pending[del].sent = शून्य;
	spin_unlock_irqrestore(&devdata->privlock, flags);

	वापस sent;
पूर्ण

/*
 * get_scsipending_cmdrsp - Return the cmdrsp stored in a pending entry
 * @ddata: Device holding the pending array
 * @ent:   Entry that stores the cmdrsp
 *
 * Each scsipending entry has a cmdrsp in it. The cmdrsp is only valid
 * अगर the "sent" field is not शून्य.
 *
 * Return: A poपूर्णांकer to the cmdrsp, शून्य on failure
 */
अटल काष्ठा uiscmdrsp *get_scsipending_cmdrsp(काष्ठा visorhba_devdata *ddata,
						पूर्णांक ent)
अणु
	अगर (ddata->pending[ent].sent)
		वापस &ddata->pending[ent].cmdrsp;

	वापस शून्य;
पूर्ण

/*
 * simple_idr_get - Associate a provided poपूर्णांकer with an पूर्णांक value
 *		    1 <= value <= पूर्णांक_उच्च, and वापस this पूर्णांक value;
 *		    the poपूर्णांकer value can be obtained later by passing
 *		    this पूर्णांक value to idr_find()
 * @idrtable: The data object मुख्यtaining the poपूर्णांकer<-->पूर्णांक mappings
 * @p:	      The poपूर्णांकer value to be remembered
 * @lock:     A spinlock used when exclusive access to idrtable is needed
 *
 * Return: The id number mapped to poपूर्णांकer 'p', 0 on failure
 */
अटल अचिन्हित पूर्णांक simple_idr_get(काष्ठा idr *idrtable, व्योम *p,
				   spinlock_t *lock)
अणु
	पूर्णांक id;
	अचिन्हित दीर्घ flags;

	idr_preload(GFP_KERNEL);
	spin_lock_irqsave(lock, flags);
	id = idr_alloc(idrtable, p, 1, पूर्णांक_उच्च, GFP_NOWAIT);
	spin_unlock_irqrestore(lock, flags);
	idr_preload_end();
	/* failure */
	अगर (id < 0)
		वापस 0;
	/* idr_alloc() guarantees > 0 */
	वापस (अचिन्हित पूर्णांक)(id);
पूर्ण

/*
 * setup_scsitaskmgmt_handles - Stash the necessary handles so that the
 *				completion processing logic क्रम a taskmgmt
 *				cmd will be able to find who to wake up
 *				and where to stash the result
 * @idrtable: The data object मुख्यtaining the poपूर्णांकer<-->पूर्णांक mappings
 * @lock:     A spinlock used when exclusive access to idrtable is needed
 * @cmdrsp:   Response from the IOVM
 * @event:    The event handle to associate with an id
 * @result:   The location to place the result of the event handle पूर्णांकo
 */
अटल व्योम setup_scsitaskmgmt_handles(काष्ठा idr *idrtable, spinlock_t *lock,
				       काष्ठा uiscmdrsp *cmdrsp,
				       रुको_queue_head_t *event, पूर्णांक *result)
अणु
	/* specअगरy the event that has to be triggered when this */
	/* cmd is complete */
	cmdrsp->scsitaskmgmt.notअगरy_handle =
		simple_idr_get(idrtable, event, lock);
	cmdrsp->scsitaskmgmt.notअगरyresult_handle =
		simple_idr_get(idrtable, result, lock);
पूर्ण

/*
 * cleanup_scsitaskmgmt_handles - Forget handles created by
 *				  setup_scsitaskmgmt_handles()
 * @idrtable: The data object मुख्यtaining the poपूर्णांकer<-->पूर्णांक mappings
 * @cmdrsp:   Response from the IOVM
 */
अटल व्योम cleanup_scsitaskmgmt_handles(काष्ठा idr *idrtable,
					 काष्ठा uiscmdrsp *cmdrsp)
अणु
	अगर (cmdrsp->scsitaskmgmt.notअगरy_handle)
		idr_हटाओ(idrtable, cmdrsp->scsitaskmgmt.notअगरy_handle);
	अगर (cmdrsp->scsitaskmgmt.notअगरyresult_handle)
		idr_हटाओ(idrtable, cmdrsp->scsitaskmgmt.notअगरyresult_handle);
पूर्ण

/*
 * क्रमward_taskmgmt_command - Send taskmegmt command to the Service
 *			      Partition
 * @tasktype: Type of taskmgmt command
 * @scsidev:  Scsidev that issued command
 *
 * Create a cmdrsp packet and send it to the Service Partition
 * that will service this request.
 *
 * Return: Int representing whether command was queued successfully or not
 */
अटल पूर्णांक क्रमward_taskmgmt_command(क्रमागत task_mgmt_types tasktype,
				    काष्ठा scsi_device *scsidev)
अणु
	काष्ठा uiscmdrsp *cmdrsp;
	काष्ठा visorhba_devdata *devdata =
		(काष्ठा visorhba_devdata *)scsidev->host->hostdata;
	पूर्णांक notअगरyresult = 0xffff;
	रुको_queue_head_t notअगरyevent;
	पूर्णांक scsicmd_id;

	अगर (devdata->serverकरोwn || devdata->serverchangingstate)
		वापस FAILED;

	scsicmd_id = add_scsipending_entry(devdata, CMD_SCSITASKMGMT_TYPE,
					   शून्य);
	अगर (scsicmd_id < 0)
		वापस FAILED;

	cmdrsp = get_scsipending_cmdrsp(devdata, scsicmd_id);

	init_रुकोqueue_head(&notअगरyevent);

	/* issue TASK_MGMT_ABORT_TASK */
	cmdrsp->cmdtype = CMD_SCSITASKMGMT_TYPE;
	setup_scsitaskmgmt_handles(&devdata->idr, &devdata->privlock, cmdrsp,
				   &notअगरyevent, &notअगरyresult);

	/* save destination */
	cmdrsp->scsitaskmgmt.tasktype = tasktype;
	cmdrsp->scsitaskmgmt.vdest.channel = scsidev->channel;
	cmdrsp->scsitaskmgmt.vdest.id = scsidev->id;
	cmdrsp->scsitaskmgmt.vdest.lun = scsidev->lun;
	cmdrsp->scsitaskmgmt.handle = scsicmd_id;

	dev_dbg(&scsidev->sdev_gendev,
		"visorhba: initiating type=%d taskmgmt command\n", tasktype);
	अगर (visorchannel_संकेतinsert(devdata->dev->visorchannel,
				      IOCHAN_TO_IOPART,
				      cmdrsp))
		जाओ err_del_scsipending_ent;

	/* It can take the Service Partition up to 35 seconds to complete
	 * an IO in some हालs, so रुको 45 seconds and error out
	 */
	अगर (!रुको_event_समयout(notअगरyevent, notअगरyresult != 0xffff,
				msecs_to_jअगरfies(45000)))
		जाओ err_del_scsipending_ent;

	dev_dbg(&scsidev->sdev_gendev,
		"visorhba: taskmgmt type=%d success; result=0x%x\n",
		 tasktype, notअगरyresult);
	cleanup_scsitaskmgmt_handles(&devdata->idr, cmdrsp);
	वापस SUCCESS;

err_del_scsipending_ent:
	dev_dbg(&scsidev->sdev_gendev,
		"visorhba: taskmgmt type=%d not executed\n", tasktype);
	del_scsipending_ent(devdata, scsicmd_id);
	cleanup_scsitaskmgmt_handles(&devdata->idr, cmdrsp);
	वापस FAILED;
पूर्ण

/*
 * visorhba_पात_handler - Send TASK_MGMT_ABORT_TASK
 * @scsicmd: The scsicmd that needs पातed
 *
 * Return: SUCCESS अगर inserted, FAILED otherwise
 */
अटल पूर्णांक visorhba_पात_handler(काष्ठा scsi_cmnd *scsicmd)
अणु
	/* issue TASK_MGMT_ABORT_TASK */
	काष्ठा scsi_device *scsidev;
	काष्ठा visordisk_info *vdisk;
	पूर्णांक rtn;

	scsidev = scsicmd->device;
	vdisk = scsidev->hostdata;
	अगर (atomic_पढ़ो(&vdisk->error_count) < VISORHBA_ERROR_COUNT)
		atomic_inc(&vdisk->error_count);
	अन्यथा
		atomic_set(&vdisk->ios_threshold, IOS_ERROR_THRESHOLD);
	rtn = क्रमward_taskmgmt_command(TASK_MGMT_ABORT_TASK, scsidev);
	अगर (rtn == SUCCESS) अणु
		scsicmd->result = DID_ABORT << 16;
		scsicmd->scsi_करोne(scsicmd);
	पूर्ण
	वापस rtn;
पूर्ण

/*
 * visorhba_device_reset_handler - Send TASK_MGMT_LUN_RESET
 * @scsicmd: The scsicmd that needs पातed
 *
 * Return: SUCCESS अगर inserted, FAILED otherwise
 */
अटल पूर्णांक visorhba_device_reset_handler(काष्ठा scsi_cmnd *scsicmd)
अणु
	/* issue TASK_MGMT_LUN_RESET */
	काष्ठा scsi_device *scsidev;
	काष्ठा visordisk_info *vdisk;
	पूर्णांक rtn;

	scsidev = scsicmd->device;
	vdisk = scsidev->hostdata;
	अगर (atomic_पढ़ो(&vdisk->error_count) < VISORHBA_ERROR_COUNT)
		atomic_inc(&vdisk->error_count);
	अन्यथा
		atomic_set(&vdisk->ios_threshold, IOS_ERROR_THRESHOLD);
	rtn = क्रमward_taskmgmt_command(TASK_MGMT_LUN_RESET, scsidev);
	अगर (rtn == SUCCESS) अणु
		scsicmd->result = DID_RESET << 16;
		scsicmd->scsi_करोne(scsicmd);
	पूर्ण
	वापस rtn;
पूर्ण

/*
 * visorhba_bus_reset_handler - Send TASK_MGMT_TARGET_RESET क्रम each
 *				target on the bus
 * @scsicmd: The scsicmd that needs पातed
 *
 * Return: SUCCESS अगर inserted, FAILED otherwise
 */
अटल पूर्णांक visorhba_bus_reset_handler(काष्ठा scsi_cmnd *scsicmd)
अणु
	काष्ठा scsi_device *scsidev;
	काष्ठा visordisk_info *vdisk;
	पूर्णांक rtn;

	scsidev = scsicmd->device;
	shost_क्रम_each_device(scsidev, scsidev->host) अणु
		vdisk = scsidev->hostdata;
		अगर (atomic_पढ़ो(&vdisk->error_count) < VISORHBA_ERROR_COUNT)
			atomic_inc(&vdisk->error_count);
		अन्यथा
			atomic_set(&vdisk->ios_threshold, IOS_ERROR_THRESHOLD);
	पूर्ण
	rtn = क्रमward_taskmgmt_command(TASK_MGMT_BUS_RESET, scsidev);
	अगर (rtn == SUCCESS) अणु
		scsicmd->result = DID_RESET << 16;
		scsicmd->scsi_करोne(scsicmd);
	पूर्ण
	वापस rtn;
पूर्ण

/*
 * visorhba_host_reset_handler - Not supported
 * @scsicmd: The scsicmd that needs to be पातed
 *
 * Return: Not supported, वापस SUCCESS
 */
अटल पूर्णांक visorhba_host_reset_handler(काष्ठा scsi_cmnd *scsicmd)
अणु
	/* issue TASK_MGMT_TARGET_RESET क्रम each target on each bus क्रम host */
	वापस SUCCESS;
पूर्ण

/*
 * visorhba_get_info - Get inक्रमmation about SCSI device
 * @shp: Scsi host that is requesting inक्रमmation
 *
 * Return: String with visorhba inक्रमmation
 */
अटल स्थिर अक्षर *visorhba_get_info(काष्ठा Scsi_Host *shp)
अणु
	/* Return version string */
	वापस "visorhba";
पूर्ण

/*
 * dma_data_dir_linux_to_spar - convert dma_data_direction value to
 *				Unisys-specअगरic equivalent
 * @d: dma direction value to convert
 *
 * Returns the Unisys-specअगरic dma direction value corresponding to @d
 */
अटल u32 dma_data_dir_linux_to_spar(क्रमागत dma_data_direction d)
अणु
	चयन (d) अणु
	हाल DMA_BIसूचीECTIONAL:
		वापस UIS_DMA_BIसूचीECTIONAL;
	हाल DMA_TO_DEVICE:
		वापस UIS_DMA_TO_DEVICE;
	हाल DMA_FROM_DEVICE:
		वापस UIS_DMA_FROM_DEVICE;
	हाल DMA_NONE:
		वापस UIS_DMA_NONE;
	शेष:
		वापस UIS_DMA_NONE;
	पूर्ण
पूर्ण

/*
 * visorhba_queue_command_lck - Queues command to the Service Partition
 * @scsicmd:		Command to be queued
 * @vsiorhba_cmnd_करोne: Done command to call when scsicmd is वापसed
 *
 * Queues to scsicmd to the ServicePartition after converting it to a
 * uiscmdrsp काष्ठाure.
 *
 * Return: 0 अगर successfully queued to the Service Partition, otherwise
 *	   error code
 */
अटल पूर्णांक visorhba_queue_command_lck(काष्ठा scsi_cmnd *scsicmd,
				      व्योम (*visorhba_cmnd_करोne)
					   (काष्ठा scsi_cmnd *))
अणु
	काष्ठा uiscmdrsp *cmdrsp;
	काष्ठा scsi_device *scsidev = scsicmd->device;
	पूर्णांक insert_location;
	अचिन्हित अक्षर *cdb = scsicmd->cmnd;
	काष्ठा Scsi_Host *scsihost = scsidev->host;
	अचिन्हित पूर्णांक i;
	काष्ठा visorhba_devdata *devdata =
		(काष्ठा visorhba_devdata *)scsihost->hostdata;
	काष्ठा scatterlist *sg = शून्य;
	काष्ठा scatterlist *sglist = शून्य;

	अगर (devdata->serverकरोwn || devdata->serverchangingstate)
		वापस SCSI_MLQUEUE_DEVICE_BUSY;

	insert_location = add_scsipending_entry(devdata, CMD_SCSI_TYPE,
						(व्योम *)scsicmd);
	अगर (insert_location < 0)
		वापस SCSI_MLQUEUE_DEVICE_BUSY;

	cmdrsp = get_scsipending_cmdrsp(devdata, insert_location);
	cmdrsp->cmdtype = CMD_SCSI_TYPE;
	/* save the pending insertion location. Deletion from pending
	 * will वापस the scsicmd poपूर्णांकer क्रम completion
	 */
	cmdrsp->scsi.handle = insert_location;

	/* save करोne function that we have call when cmd is complete */
	scsicmd->scsi_करोne = visorhba_cmnd_करोne;
	/* save destination */
	cmdrsp->scsi.vdest.channel = scsidev->channel;
	cmdrsp->scsi.vdest.id = scsidev->id;
	cmdrsp->scsi.vdest.lun = scsidev->lun;
	/* save datadir */
	cmdrsp->scsi.data_dir =
		dma_data_dir_linux_to_spar(scsicmd->sc_data_direction);
	स_नकल(cmdrsp->scsi.cmnd, cdb, MAX_CMND_SIZE);
	cmdrsp->scsi.bufflen = scsi_bufflen(scsicmd);

	/* keep track of the max buffer length so far. */
	अगर (cmdrsp->scsi.bufflen > devdata->max_buff_len)
		devdata->max_buff_len = cmdrsp->scsi.bufflen;

	अगर (scsi_sg_count(scsicmd) > MAX_PHYS_INFO)
		जाओ err_del_scsipending_ent;

	/* convert buffer to phys inक्रमmation  */
	/* buffer is scatterlist - copy it out */
	sglist = scsi_sglist(scsicmd);

	क्रम_each_sg(sglist, sg, scsi_sg_count(scsicmd), i) अणु
		cmdrsp->scsi.gpi_list[i].address = sg_phys(sg);
		cmdrsp->scsi.gpi_list[i].length = sg->length;
	पूर्ण
	cmdrsp->scsi.guest_phys_entries = scsi_sg_count(scsicmd);

	अगर (visorchannel_संकेतinsert(devdata->dev->visorchannel,
				      IOCHAN_TO_IOPART,
				      cmdrsp))
		/* queue must be full and we aren't going to रुको */
		जाओ err_del_scsipending_ent;

	वापस 0;

err_del_scsipending_ent:
	del_scsipending_ent(devdata, insert_location);
	वापस SCSI_MLQUEUE_DEVICE_BUSY;
पूर्ण

#अगर_घोषित DEF_SCSI_QCMD
अटल DEF_SCSI_QCMD(visorhba_queue_command)
#अन्यथा
#घोषणा visorhba_queue_command visorhba_queue_command_lck
#पूर्ण_अगर

/*
 * visorhba_slave_alloc - Called when new disk is discovered
 * @scsidev: New disk
 *
 * Create a new visordisk_info काष्ठाure and add it to our
 * list of vdisks.
 *
 * Return: 0 on success, -ENOMEM on failure.
 */
अटल पूर्णांक visorhba_slave_alloc(काष्ठा scsi_device *scsidev)
अणु
	/* this is called by the midlayer beक्रमe scan क्रम new devices --
	 * LLD can alloc any काष्ठा & करो init अगर needed.
	 */
	काष्ठा visordisk_info *vdisk;
	काष्ठा visorhba_devdata *devdata;
	काष्ठा Scsi_Host *scsihost = (काष्ठा Scsi_Host *)scsidev->host;

	/* alपढ़ोy allocated वापस success */
	अगर (scsidev->hostdata)
		वापस 0;

	/* even though we errored, treat as success */
	devdata = (काष्ठा visorhba_devdata *)scsihost->hostdata;
	अगर (!devdata)
		वापस 0;

	vdisk = kzalloc(माप(*vdisk), GFP_ATOMIC);
	अगर (!vdisk)
		वापस -ENOMEM;

	vdisk->sdev = scsidev;
	scsidev->hostdata = vdisk;
	वापस 0;
पूर्ण

/*
 * visorhba_slave_destroy - Disk is going away, clean up resources.
 * @scsidev: Scsi device to destroy
 */
अटल व्योम visorhba_slave_destroy(काष्ठा scsi_device *scsidev)
अणु
	/* midlevel calls this after device has been quiesced and
	 * beक्रमe it is to be deleted.
	 */
	काष्ठा visordisk_info *vdisk;

	vdisk = scsidev->hostdata;
	scsidev->hostdata = शून्य;
	kमुक्त(vdisk);
पूर्ण

अटल काष्ठा scsi_host_ढाँचा visorhba_driver_ढाँचा = अणु
	.name = "Unisys Visor HBA",
	.info = visorhba_get_info,
	.queuecommand = visorhba_queue_command,
	.eh_पात_handler = visorhba_पात_handler,
	.eh_device_reset_handler = visorhba_device_reset_handler,
	.eh_bus_reset_handler = visorhba_bus_reset_handler,
	.eh_host_reset_handler = visorhba_host_reset_handler,
	.shost_attrs = शून्य,
#घोषणा visorhba_MAX_CMNDS 128
	.can_queue = visorhba_MAX_CMNDS,
	.sg_tablesize = 64,
	.this_id = -1,
	.slave_alloc = visorhba_slave_alloc,
	.slave_destroy = visorhba_slave_destroy,
पूर्ण;

/*
 * info_debugfs_show - Debugfs पूर्णांकerface to dump visorhba states
 * @seq: The sequence file to ग_लिखो inक्रमmation to
 * @v:   Unused, but needed क्रम use with seq file single_खोलो invocation
 *
 * Presents a file in the debugfs tree named: /visorhba/vbus<x>:dev<y>/info.
 *
 * Return: SUCCESS
 */
अटल पूर्णांक info_debugfs_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा visorhba_devdata *devdata = seq->निजी;

	seq_म_लिखो(seq, "max_buff_len = %u\n", devdata->max_buff_len);
	seq_म_लिखो(seq, "interrupts_rcvd = %llu\n", devdata->पूर्णांकerrupts_rcvd);
	seq_म_लिखो(seq, "interrupts_disabled = %llu\n",
		   devdata->पूर्णांकerrupts_disabled);
	seq_म_लिखो(seq, "interrupts_notme = %llu\n",
		   devdata->पूर्णांकerrupts_noपंचांगe);
	seq_म_लिखो(seq, "flags_addr = %p\n", devdata->flags_addr);
	अगर (devdata->flags_addr) अणु
		u64 phys_flags_addr =
			virt_to_phys((__क्रमce  व्योम *)devdata->flags_addr);
		seq_म_लिखो(seq, "phys_flags_addr = 0x%016llx\n",
			   phys_flags_addr);
		seq_म_लिखो(seq, "FeatureFlags = %llu\n",
			   (u64)पढ़ोq(devdata->flags_addr));
	पूर्ण
	seq_म_लिखो(seq, "acquire_failed_cnt = %llu\n",
		   devdata->acquire_failed_cnt);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(info_debugfs);

/*
 * complete_taskmgmt_command - Complete task management
 * @idrtable: The data object मुख्यtaining the poपूर्णांकer<-->पूर्णांक mappings
 * @cmdrsp:   Response from the IOVM
 * @result:   The result of the task management command
 *
 * Service Partition वापसed the result of the task management
 * command. Wake up anyone रुकोing क्रम it.
 */
अटल व्योम complete_taskmgmt_command(काष्ठा idr *idrtable,
				      काष्ठा uiscmdrsp *cmdrsp, पूर्णांक result)
अणु
	रुको_queue_head_t *wq =
		idr_find(idrtable, cmdrsp->scsitaskmgmt.notअगरy_handle);
	पूर्णांक *scsi_result_ptr =
		idr_find(idrtable, cmdrsp->scsitaskmgmt.notअगरyresult_handle);
	अगर (unlikely(!(wq && scsi_result_ptr))) अणु
		pr_err("visorhba: no completion context; cmd will time out\n");
		वापस;
	पूर्ण

	/* copy the result of the taskmgmt and
	 * wake up the error handler that is रुकोing क्रम this
	 */
	pr_debug("visorhba: notifying initiator with result=0x%x\n", result);
	*scsi_result_ptr = result;
	wake_up_all(wq);
पूर्ण

/*
 * visorhba_serverकरोwn_complete - Called when we are करोne cleaning up
 *				  from serverकरोwn
 * @devdata: Visorhba instance on which to complete serverकरोwn
 *
 * Called when we are करोne cleanning up from serverकरोwn, stop processing
 * queue, fail pending IOs.
 */
अटल व्योम visorhba_serverकरोwn_complete(काष्ठा visorhba_devdata *devdata)
अणु
	पूर्णांक i;
	काष्ठा scsipending *pendingdel = शून्य;
	काष्ठा scsi_cmnd *scsicmd = शून्य;
	काष्ठा uiscmdrsp *cmdrsp;
	अचिन्हित दीर्घ flags;

	/* Stop using the IOVM response queue (queue should be drained
	 * by the end)
	 */
	visorbus_disable_channel_पूर्णांकerrupts(devdata->dev);

	/* Fail commands that weren't completed */
	spin_lock_irqsave(&devdata->privlock, flags);
	क्रम (i = 0; i < MAX_PENDING_REQUESTS; i++) अणु
		pendingdel = &devdata->pending[i];
		चयन (pendingdel->cmdtype) अणु
		हाल CMD_SCSI_TYPE:
			scsicmd = pendingdel->sent;
			scsicmd->result = DID_RESET << 16;
			अगर (scsicmd->scsi_करोne)
				scsicmd->scsi_करोne(scsicmd);
			अवरोध;
		हाल CMD_SCSITASKMGMT_TYPE:
			cmdrsp = pendingdel->sent;
			complete_taskmgmt_command(&devdata->idr, cmdrsp,
						  TASK_MGMT_FAILED);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		pendingdel->cmdtype = 0;
		pendingdel->sent = शून्य;
	पूर्ण
	spin_unlock_irqrestore(&devdata->privlock, flags);

	devdata->serverकरोwn = true;
	devdata->serverchangingstate = false;
पूर्ण

/*
 * visorhba_serverकरोwn - Got notअगरied that the IOVM is करोwn
 * @devdata: Visorhba that is being serviced by करोwned IOVM
 *
 * Something happened to the IOVM, वापस immediately and
 * schedule cleanup work.
 *
 * Return: 0 on success, -EINVAL on failure
 */
अटल पूर्णांक visorhba_serverकरोwn(काष्ठा visorhba_devdata *devdata)
अणु
	अगर (!devdata->serverकरोwn && !devdata->serverchangingstate) अणु
		devdata->serverchangingstate = true;
		visorhba_serverकरोwn_complete(devdata);
	पूर्ण अन्यथा अगर (devdata->serverchangingstate) अणु
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * करो_scsi_linuxstat - Scsi command वापसed linuxstat
 * @cmdrsp:  Response from IOVM
 * @scsicmd: Command issued
 *
 * Don't log errors क्रम disk-not-present inquiries.
 */
अटल व्योम करो_scsi_linuxstat(काष्ठा uiscmdrsp *cmdrsp,
			      काष्ठा scsi_cmnd *scsicmd)
अणु
	काष्ठा visordisk_info *vdisk;
	काष्ठा scsi_device *scsidev;

	scsidev = scsicmd->device;
	स_नकल(scsicmd->sense_buffer, cmdrsp->scsi.sensebuf, MAX_SENSE_SIZE);

	/* Do not log errors क्रम disk-not-present inquiries */
	अगर (cmdrsp->scsi.cmnd[0] == INQUIRY &&
	    (host_byte(cmdrsp->scsi.linuxstat) == DID_NO_CONNECT) &&
	    cmdrsp->scsi.addlstat == ADDL_SEL_TIMEOUT)
		वापस;
	/* Okay see what our error_count is here.... */
	vdisk = scsidev->hostdata;
	अगर (atomic_पढ़ो(&vdisk->error_count) < VISORHBA_ERROR_COUNT) अणु
		atomic_inc(&vdisk->error_count);
		atomic_set(&vdisk->ios_threshold, IOS_ERROR_THRESHOLD);
	पूर्ण
पूर्ण

अटल पूर्णांक set_no_disk_inquiry_result(अचिन्हित अक्षर *buf, माप_प्रकार len,
				      bool is_lun0)
अणु
	अगर (len < NO_DISK_INQUIRY_RESULT_LEN)
		वापस -EINVAL;
	स_रखो(buf, 0, NO_DISK_INQUIRY_RESULT_LEN);
	buf[2] = SCSI_SPC2_VER;
	अगर (is_lun0) अणु
		buf[0] = DEV_DISK_CAPABLE_NOT_PRESENT;
		buf[3] = DEV_HISUPPORT;
	पूर्ण अन्यथा अणु
		buf[0] = DEV_NOT_CAPABLE;
	पूर्ण
	buf[4] = NO_DISK_INQUIRY_RESULT_LEN - 5;
	म_नकलन(buf + 8, "DELLPSEUDO DEVICE .", NO_DISK_INQUIRY_RESULT_LEN - 8);
	वापस 0;
पूर्ण

/*
 * करो_scsi_nolinuxstat - Scsi command didn't have linuxstat
 * @cmdrsp:  Response from IOVM
 * @scsicmd: Command issued
 *
 * Handle response when no linuxstat was वापसed.
 */
अटल व्योम करो_scsi_nolinuxstat(काष्ठा uiscmdrsp *cmdrsp,
				काष्ठा scsi_cmnd *scsicmd)
अणु
	काष्ठा scsi_device *scsidev;
	अचिन्हित अक्षर *buf;
	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक i;
	अक्षर *this_page;
	अक्षर *this_page_orig;
	पूर्णांक bufind = 0;
	काष्ठा visordisk_info *vdisk;

	scsidev = scsicmd->device;
	अगर (cmdrsp->scsi.cmnd[0] == INQUIRY &&
	    cmdrsp->scsi.bufflen >= MIN_INQUIRY_RESULT_LEN) अणु
		अगर (cmdrsp->scsi.no_disk_result == 0)
			वापस;

		buf = kzalloc(36, GFP_KERNEL);
		अगर (!buf)
			वापस;

		/* Linux scsi code wants a device at Lun 0
		 * to issue report luns, but we करोn't want
		 * a disk there so we'll present a processor
		 * there.
		 */
		set_no_disk_inquiry_result(buf, (माप_प्रकार)cmdrsp->scsi.bufflen,
					   scsidev->lun == 0);

		अगर (scsi_sg_count(scsicmd) == 0) अणु
			स_नकल(scsi_sglist(scsicmd), buf,
			       cmdrsp->scsi.bufflen);
			kमुक्त(buf);
			वापस;
		पूर्ण

		scsi_क्रम_each_sg(scsicmd, sg, scsi_sg_count(scsicmd), i) अणु
			this_page_orig = kmap_atomic(sg_page(sg));
			this_page = (व्योम *)((अचिन्हित दीर्घ)this_page_orig |
					     sg->offset);
			स_नकल(this_page, buf + bufind, sg->length);
			kunmap_atomic(this_page_orig);
		पूर्ण
		kमुक्त(buf);
	पूर्ण अन्यथा अणु
		vdisk = scsidev->hostdata;
		अगर (atomic_पढ़ो(&vdisk->ios_threshold) > 0) अणु
			atomic_dec(&vdisk->ios_threshold);
			अगर (atomic_पढ़ो(&vdisk->ios_threshold) == 0)
				atomic_set(&vdisk->error_count, 0);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * complete_scsi_command - Complete a scsi command
 * @uiscmdrsp: Response from Service Partition
 * @scsicmd:   The scsi command
 *
 * Response was वापसed by the Service Partition. Finish it and send
 * completion to the scsi midlayer.
 */
अटल व्योम complete_scsi_command(काष्ठा uiscmdrsp *cmdrsp,
				  काष्ठा scsi_cmnd *scsicmd)
अणु
	/* take what we need out of cmdrsp and complete the scsicmd */
	scsicmd->result = cmdrsp->scsi.linuxstat;
	अगर (cmdrsp->scsi.linuxstat)
		करो_scsi_linuxstat(cmdrsp, scsicmd);
	अन्यथा
		करो_scsi_nolinuxstat(cmdrsp, scsicmd);

	scsicmd->scsi_करोne(scsicmd);
पूर्ण

/*
 * drain_queue - Pull responses out of iochannel
 * @cmdrsp:  Response from the IOSP
 * @devdata: Device that owns this iochannel
 *
 * Pulls responses out of the iochannel and process the responses.
 */
अटल व्योम drain_queue(काष्ठा uiscmdrsp *cmdrsp,
			काष्ठा visorhba_devdata *devdata)
अणु
	काष्ठा scsi_cmnd *scsicmd;

	जबतक (1) अणु
		/* queue empty */
		अगर (visorchannel_संकेतहटाओ(devdata->dev->visorchannel,
					      IOCHAN_FROM_IOPART,
					      cmdrsp))
			अवरोध;
		अगर (cmdrsp->cmdtype == CMD_SCSI_TYPE) अणु
			/* scsicmd location is वापसed by the
			 * deletion
			 */
			scsicmd = del_scsipending_ent(devdata,
						      cmdrsp->scsi.handle);
			अगर (!scsicmd)
				अवरोध;
			/* complete the orig cmd */
			complete_scsi_command(cmdrsp, scsicmd);
		पूर्ण अन्यथा अगर (cmdrsp->cmdtype == CMD_SCSITASKMGMT_TYPE) अणु
			अगर (!del_scsipending_ent(devdata,
						 cmdrsp->scsitaskmgmt.handle))
				अवरोध;
			complete_taskmgmt_command(&devdata->idr, cmdrsp,
						  cmdrsp->scsitaskmgmt.result);
		पूर्ण अन्यथा अगर (cmdrsp->cmdtype == CMD_NOTIFYGUEST_TYPE)
			dev_err_once(&devdata->dev->device,
				     "ignoring unsupported NOTIFYGUEST\n");
		/* cmdrsp is now available क्रम re-use */
	पूर्ण
पूर्ण

/*
 * This is used only when this driver is active as an hba driver in the
 * client guest partition.  It is called periodically so we can obtain
 * and process the command respond from the IO Service Partition periodically.
 */
अटल व्योम visorhba_channel_पूर्णांकerrupt(काष्ठा visor_device *dev)
अणु
	काष्ठा visorhba_devdata *devdata = dev_get_drvdata(&dev->device);

	अगर (!devdata)
		वापस;

	drain_queue(devdata->cmdrsp, devdata);
पूर्ण

/*
 * visorhba_छोड़ो - Function to handle visorbus छोड़ो messages
 * @dev:	   Device that is pausing
 * @complete_func: Function to call when finished
 *
 * Something has happened to the IO Service Partition that is
 * handling this device. Quiet this device and reset commands
 * so that the Service Partition can be corrected.
 *
 * Return: SUCCESS
 */
अटल पूर्णांक visorhba_छोड़ो(काष्ठा visor_device *dev,
			  visorbus_state_complete_func complete_func)
अणु
	काष्ठा visorhba_devdata *devdata = dev_get_drvdata(&dev->device);

	visorhba_serverकरोwn(devdata);
	complete_func(dev, 0);
	वापस 0;
पूर्ण

/*
 * visorhba_resume - Function called when the IO Service Partition is back
 * @dev:	   Device that is pausing
 * @complete_func: Function to call when finished
 *
 * Yay! The IO Service Partition is back, the channel has been wiped
 * so lets re-establish connection and start processing responses.
 *
 * Return: 0 on success, -EINVAL on failure
 */
अटल पूर्णांक visorhba_resume(काष्ठा visor_device *dev,
			   visorbus_state_complete_func complete_func)
अणु
	काष्ठा visorhba_devdata *devdata;

	devdata = dev_get_drvdata(&dev->device);
	अगर (!devdata)
		वापस -EINVAL;

	अगर (devdata->serverकरोwn && !devdata->serverchangingstate)
		devdata->serverchangingstate = true;

	visorbus_enable_channel_पूर्णांकerrupts(dev);
	devdata->serverकरोwn = false;
	devdata->serverchangingstate = false;

	वापस 0;
पूर्ण

/*
 * visorhba_probe - Device has been discovered; करो acquire
 * @dev: visor_device that was discovered
 *
 * A new HBA was discovered; करो the initial connections of it.
 *
 * Return: 0 on success, otherwise error code
 */
अटल पूर्णांक visorhba_probe(काष्ठा visor_device *dev)
अणु
	काष्ठा Scsi_Host *scsihost;
	काष्ठा vhba_config_max max;
	काष्ठा visorhba_devdata *devdata = शून्य;
	पूर्णांक err, channel_offset;
	u64 features;

	scsihost = scsi_host_alloc(&visorhba_driver_ढाँचा,
				   माप(*devdata));
	अगर (!scsihost)
		वापस -ENODEV;

	channel_offset = दुरत्व(काष्ठा visor_io_channel, vhba.max);
	err = visorbus_पढ़ो_channel(dev, channel_offset, &max,
				    माप(काष्ठा vhba_config_max));
	अगर (err < 0)
		जाओ err_scsi_host_put;

	scsihost->max_id = (अचिन्हित पूर्णांक)max.max_id;
	scsihost->max_lun = (अचिन्हित पूर्णांक)max.max_lun;
	scsihost->cmd_per_lun = (अचिन्हित पूर्णांक)max.cmd_per_lun;
	scsihost->max_sectors =
	    (अचिन्हित लघु)(max.max_io_size >> 9);
	scsihost->sg_tablesize =
	    (अचिन्हित लघु)(max.max_io_size / PAGE_SIZE);
	अगर (scsihost->sg_tablesize > MAX_PHYS_INFO)
		scsihost->sg_tablesize = MAX_PHYS_INFO;
	err = scsi_add_host(scsihost, &dev->device);
	अगर (err < 0)
		जाओ err_scsi_host_put;

	devdata = (काष्ठा visorhba_devdata *)scsihost->hostdata;
	devdata->dev = dev;
	dev_set_drvdata(&dev->device, devdata);

	devdata->debugfs_dir = debugfs_create_dir(dev_name(&dev->device),
						  visorhba_debugfs_dir);
	अगर (!devdata->debugfs_dir) अणु
		err = -ENOMEM;
		जाओ err_scsi_हटाओ_host;
	पूर्ण
	devdata->debugfs_info =
		debugfs_create_file("info", 0440,
				    devdata->debugfs_dir, devdata,
				    &info_debugfs_fops);
	अगर (!devdata->debugfs_info) अणु
		err = -ENOMEM;
		जाओ err_debugfs_dir;
	पूर्ण

	spin_lock_init(&devdata->privlock);
	devdata->serverकरोwn = false;
	devdata->serverchangingstate = false;
	devdata->scsihost = scsihost;

	channel_offset = दुरत्व(काष्ठा visor_io_channel,
				  channel_header.features);
	err = visorbus_पढ़ो_channel(dev, channel_offset, &features, 8);
	अगर (err)
		जाओ err_debugfs_info;
	features |= VISOR_CHANNEL_IS_POLLING;
	err = visorbus_ग_लिखो_channel(dev, channel_offset, &features, 8);
	अगर (err)
		जाओ err_debugfs_info;

	idr_init(&devdata->idr);

	devdata->cmdrsp = kदो_स्मृति(माप(*devdata->cmdrsp), GFP_ATOMIC);
	visorbus_enable_channel_पूर्णांकerrupts(dev);

	scsi_scan_host(scsihost);

	वापस 0;

err_debugfs_info:
	debugfs_हटाओ(devdata->debugfs_info);

err_debugfs_dir:
	debugfs_हटाओ_recursive(devdata->debugfs_dir);

err_scsi_हटाओ_host:
	scsi_हटाओ_host(scsihost);

err_scsi_host_put:
	scsi_host_put(scsihost);
	वापस err;
पूर्ण

/*
 * visorhba_हटाओ - Remove a visorhba device
 * @dev: Device to हटाओ
 *
 * Removes the visorhba device.
 */
अटल व्योम visorhba_हटाओ(काष्ठा visor_device *dev)
अणु
	काष्ठा visorhba_devdata *devdata = dev_get_drvdata(&dev->device);
	काष्ठा Scsi_Host *scsihost = शून्य;

	अगर (!devdata)
		वापस;

	scsihost = devdata->scsihost;
	kमुक्त(devdata->cmdrsp);
	visorbus_disable_channel_पूर्णांकerrupts(dev);
	scsi_हटाओ_host(scsihost);
	scsi_host_put(scsihost);

	idr_destroy(&devdata->idr);

	dev_set_drvdata(&dev->device, शून्य);
	debugfs_हटाओ(devdata->debugfs_info);
	debugfs_हटाओ_recursive(devdata->debugfs_dir);
पूर्ण

/* This is used to tell the visorbus driver which types of visor devices
 * we support, and what functions to call when a visor device that we support
 * is attached or हटाओd.
 */
अटल काष्ठा visor_driver visorhba_driver = अणु
	.name = "visorhba",
	.owner = THIS_MODULE,
	.channel_types = visorhba_channel_types,
	.probe = visorhba_probe,
	.हटाओ = visorhba_हटाओ,
	.छोड़ो = visorhba_छोड़ो,
	.resume = visorhba_resume,
	.channel_पूर्णांकerrupt = visorhba_channel_पूर्णांकerrupt,
पूर्ण;

/*
 * visorhba_init - Driver init routine
 *
 * Initialize the visorhba driver and रेजिस्टर it with visorbus
 * to handle s-Par भव host bus adapter.
 *
 * Return: 0 on success, error code otherwise
 */
अटल पूर्णांक visorhba_init(व्योम)
अणु
	पूर्णांक rc;

	visorhba_debugfs_dir = debugfs_create_dir("visorhba", शून्य);
	अगर (!visorhba_debugfs_dir)
		वापस -ENOMEM;

	rc = visorbus_रेजिस्टर_visor_driver(&visorhba_driver);
	अगर (rc)
		जाओ cleanup_debugfs;

	वापस 0;

cleanup_debugfs:
	debugfs_हटाओ_recursive(visorhba_debugfs_dir);

	वापस rc;
पूर्ण

/*
 * visorhba_निकास - Driver निकास routine
 *
 * Unरेजिस्टर driver from the bus and मुक्त up memory.
 */
अटल व्योम visorhba_निकास(व्योम)
अणु
	visorbus_unरेजिस्टर_visor_driver(&visorhba_driver);
	debugfs_हटाओ_recursive(visorhba_debugfs_dir);
पूर्ण

module_init(visorhba_init);
module_निकास(visorhba_निकास);

MODULE_AUTHOR("Unisys");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("s-Par HBA driver for virtual SCSI host busses");
