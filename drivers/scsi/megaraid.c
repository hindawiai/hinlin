<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 *			Linux MegaRAID device driver
 *
 * Copyright (c) 2002  LSI Logic Corporation.
 *
 * Copyright (c) 2002  Red Hat, Inc. All rights reserved.
 *	  - fixes
 *	  - speed-ups (list handling fixes, issued_list, optimizations.)
 *	  - lots of cleanups.
 *
 * Copyright (c) 2003  Christoph Hellwig  <hch@lst.de>
 *	  - new-style, hotplug-aware pci probing and scsi registration
 *
 * Version : v2.00.4 Mon Nov 14 14:02:43 EST 2005 - Seokmann Ju
 * 						<Seokmann.Ju@lsil.com>
 *
 * Description: Linux device driver क्रम LSI Logic MegaRAID controller
 *
 * Supported controllers: MegaRAID 418, 428, 438, 466, 762, 467, 471, 490, 493
 *					518, 520, 531, 532
 *
 * This driver is supported by LSI Logic, with assistance from Red Hat, Dell,
 * and others. Please send updates to the mailing list
 * linux-scsi@vger.kernel.org .
 */

#समावेश <linux/mm.h>
#समावेश <linux/fs.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/पन.स>
#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/reboot.h>
#समावेश <linux/module.h>
#समावेश <linux/list.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <scsi/scsicam.h>

#समावेश "scsi.h"
#समावेश <scsi/scsi_host.h>

#समावेश "megaraid.h"

#घोषणा MEGARAID_MODULE_VERSION "2.00.4"

MODULE_AUTHOR ("sju@lsil.com");
MODULE_DESCRIPTION ("LSI Logic MegaRAID legacy driver");
MODULE_LICENSE ("GPL");
MODULE_VERSION(MEGARAID_MODULE_VERSION);

अटल DEFINE_MUTEX(megadev_mutex);
अटल अचिन्हित पूर्णांक max_cmd_per_lun = DEF_CMD_PER_LUN;
module_param(max_cmd_per_lun, uपूर्णांक, 0);
MODULE_PARM_DESC(max_cmd_per_lun, "Maximum number of commands which can be issued to a single LUN (default=DEF_CMD_PER_LUN=63)");

अटल अचिन्हित लघु पूर्णांक max_sectors_per_io = MAX_SECTORS_PER_IO;
module_param(max_sectors_per_io, uलघु, 0);
MODULE_PARM_DESC(max_sectors_per_io, "Maximum number of sectors per I/O request (default=MAX_SECTORS_PER_IO=128)");


अटल अचिन्हित लघु पूर्णांक max_mbox_busy_रुको = MBOX_BUSY_WAIT;
module_param(max_mbox_busy_रुको, uलघु, 0);
MODULE_PARM_DESC(max_mbox_busy_रुको, "Maximum wait for mailbox in microseconds if busy (default=MBOX_BUSY_WAIT=10)");

#घोषणा RDINDOOR(adapter)	पढ़ोl((adapter)->mmio_base + 0x20)
#घोषणा RDOUTDOOR(adapter)	पढ़ोl((adapter)->mmio_base + 0x2C)
#घोषणा WRINDOOR(adapter,value)	 ग_लिखोl(value, (adapter)->mmio_base + 0x20)
#घोषणा WROUTDOOR(adapter,value) ग_लिखोl(value, (adapter)->mmio_base + 0x2C)

/*
 * Global variables
 */

अटल पूर्णांक hba_count;
अटल adapter_t *hba_soft_state[MAX_CONTROLLERS];
अटल काष्ठा proc_dir_entry *mega_proc_dir_entry;

/* For controller re-ordering */
अटल काष्ठा mega_hbas mega_hbas[MAX_CONTROLLERS];

अटल दीर्घ
megadev_unlocked_ioctl(काष्ठा file *filep, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);

/*
 * The File Operations काष्ठाure क्रम the serial/ioctl पूर्णांकerface of the driver
 */
अटल स्थिर काष्ठा file_operations megadev_fops = अणु
	.owner		= THIS_MODULE,
	.unlocked_ioctl	= megadev_unlocked_ioctl,
	.खोलो		= megadev_खोलो,
	.llseek		= noop_llseek,
पूर्ण;

/*
 * Array to काष्ठाures क्रम storing the inक्रमmation about the controllers. This
 * inक्रमmation is sent to the user level applications, when they करो an ioctl
 * क्रम this inक्रमmation.
 */
अटल काष्ठा mcontroller mcontroller[MAX_CONTROLLERS];

/* The current driver version */
अटल u32 driver_ver = 0x02000000;

/* major number used by the device क्रम अक्षरacter पूर्णांकerface */
अटल पूर्णांक major;

#घोषणा IS_RAID_CH(hba, ch)	(((hba)->mega_ch_class >> (ch)) & 0x01)


/*
 * Debug variable to prपूर्णांक some diagnostic messages
 */
अटल पूर्णांक trace_level;

/**
 * mega_setup_mailbox()
 * @adapter: poपूर्णांकer to our soft state
 *
 * Allocates a 8 byte aligned memory क्रम the handshake mailbox.
 */
अटल पूर्णांक
mega_setup_mailbox(adapter_t *adapter)
अणु
	अचिन्हित दीर्घ	align;

	adapter->una_mbox64 = dma_alloc_coherent(&adapter->dev->dev,
						 माप(mbox64_t),
						 &adapter->una_mbox64_dma,
						 GFP_KERNEL);

	अगर( !adapter->una_mbox64 ) वापस -1;
		
	adapter->mbox = &adapter->una_mbox64->mbox;

	adapter->mbox = (mbox_t *)((((अचिन्हित दीर्घ) adapter->mbox) + 15) &
			(~0UL ^ 0xFUL));

	adapter->mbox64 = (mbox64_t *)(((अचिन्हित दीर्घ)adapter->mbox) - 8);

	align = ((व्योम *)adapter->mbox) - ((व्योम *)&adapter->una_mbox64->mbox);

	adapter->mbox_dma = adapter->una_mbox64_dma + 8 + align;

	/*
	 * Register the mailbox अगर the controller is an io-mapped controller
	 */
	अगर( adapter->flag & BOARD_IOMAP ) अणु

		outb(adapter->mbox_dma & 0xFF,
				adapter->host->io_port + MBOX_PORT0);

		outb((adapter->mbox_dma >> 8) & 0xFF,
				adapter->host->io_port + MBOX_PORT1);

		outb((adapter->mbox_dma >> 16) & 0xFF,
				adapter->host->io_port + MBOX_PORT2);

		outb((adapter->mbox_dma >> 24) & 0xFF,
				adapter->host->io_port + MBOX_PORT3);

		outb(ENABLE_MBOX_BYTE,
				adapter->host->io_port + ENABLE_MBOX_REGION);

		irq_ack(adapter);

		irq_enable(adapter);
	पूर्ण

	वापस 0;
पूर्ण


/*
 * mega_query_adapter()
 * @adapter - poपूर्णांकer to our soft state
 *
 * Issue the adapter inquiry commands to the controller and find out
 * inक्रमmation and parameter about the devices attached
 */
अटल पूर्णांक
mega_query_adapter(adapter_t *adapter)
अणु
	dma_addr_t	prod_info_dma_handle;
	mega_inquiry3	*inquiry3;
	u8	raw_mbox[माप(काष्ठा mbox_out)];
	mbox_t	*mbox;
	पूर्णांक	retval;

	/* Initialize adapter inquiry mailbox */

	mbox = (mbox_t *)raw_mbox;

	स_रखो((व्योम *)adapter->mega_buffer, 0, MEGA_BUFFER_SIZE);
	स_रखो(&mbox->m_out, 0, माप(raw_mbox));

	/*
	 * Try to issue Inquiry3 command
	 * अगर not succeeded, then issue MEGA_MBOXCMD_ADAPTERINQ command and
	 * update enquiry3 काष्ठाure
	 */
	mbox->m_out.xferaddr = (u32)adapter->buf_dma_handle;

	inquiry3 = (mega_inquiry3 *)adapter->mega_buffer;

	raw_mbox[0] = FC_NEW_CONFIG;		/* i.e. mbox->cmd=0xA1 */
	raw_mbox[2] = NC_SUBOP_ENQUIRY3;	/* i.e. 0x0F */
	raw_mbox[3] = ENQ3_GET_SOLICITED_FULL;	/* i.e. 0x02 */

	/* Issue a blocking command to the card */
	अगर ((retval = issue_scb_block(adapter, raw_mbox))) अणु
		/* the adapter करोes not support 40ld */

		mraid_ext_inquiry	*ext_inq;
		mraid_inquiry		*inq;
		dma_addr_t		dma_handle;

		ext_inq = dma_alloc_coherent(&adapter->dev->dev,
					     माप(mraid_ext_inquiry),
					     &dma_handle, GFP_KERNEL);

		अगर( ext_inq == शून्य ) वापस -1;

		inq = &ext_inq->raid_inq;

		mbox->m_out.xferaddr = (u32)dma_handle;

		/*issue old 0x04 command to adapter */
		mbox->m_out.cmd = MEGA_MBOXCMD_ADPEXTINQ;

		issue_scb_block(adapter, raw_mbox);

		/*
		 * update Enquiry3 and ProductInfo काष्ठाures with
		 * mraid_inquiry काष्ठाure
		 */
		mega_8_to_40ld(inq, inquiry3,
				(mega_product_info *)&adapter->product_info);

		dma_मुक्त_coherent(&adapter->dev->dev,
				  माप(mraid_ext_inquiry), ext_inq,
				  dma_handle);

	पूर्ण अन्यथा अणु		/*adapter supports 40ld */
		adapter->flag |= BOARD_40LD;

		/*
		 * get product_info, which is अटल inक्रमmation and will be
		 * unchanged
		 */
		prod_info_dma_handle = dma_map_single(&adapter->dev->dev,
						      (व्योम *)&adapter->product_info,
						      माप(mega_product_info),
						      DMA_FROM_DEVICE);

		mbox->m_out.xferaddr = prod_info_dma_handle;

		raw_mbox[0] = FC_NEW_CONFIG;	/* i.e. mbox->cmd=0xA1 */
		raw_mbox[2] = NC_SUBOP_PRODUCT_INFO;	/* i.e. 0x0E */

		अगर ((retval = issue_scb_block(adapter, raw_mbox)))
			dev_warn(&adapter->dev->dev,
				"Product_info cmd failed with error: %d\n",
				retval);

		dma_unmap_single(&adapter->dev->dev, prod_info_dma_handle,
				 माप(mega_product_info), DMA_FROM_DEVICE);
	पूर्ण


	/*
	 * kernel scans the channels from 0 to <= max_channel
	 */
	adapter->host->max_channel =
		adapter->product_info.nchannels + NVIRT_CHAN -1;

	adapter->host->max_id = 16;	/* max tarमाला_लो per channel */

	adapter->host->max_lun = 7;	/* Up to 7 luns क्रम non disk devices */

	adapter->host->cmd_per_lun = max_cmd_per_lun;

	adapter->numldrv = inquiry3->num_ldrv;

	adapter->max_cmds = adapter->product_info.max_commands;

	अगर(adapter->max_cmds > MAX_COMMANDS)
		adapter->max_cmds = MAX_COMMANDS;

	adapter->host->can_queue = adapter->max_cmds - 1;

	/*
	 * Get the maximum number of scatter-gather elements supported by this
	 * firmware
	 */
	mega_get_max_sgl(adapter);

	adapter->host->sg_tablesize = adapter->sglen;

	/* use HP firmware and bios version encoding
	   Note: fw_version[0|1] and bios_version[0|1] were originally shअगरted
	   right 8 bits making them zero. This 0 value was hardcoded to fix
	   sparse warnings. */
	अगर (adapter->product_info.subsysvid == PCI_VENDOR_ID_HP) अणु
		snम_लिखो(adapter->fw_version, माप(adapter->fw_version),
			 "%c%d%d.%d%d",
			 adapter->product_info.fw_version[2],
			 0,
			 adapter->product_info.fw_version[1] & 0x0f,
			 0,
			 adapter->product_info.fw_version[0] & 0x0f);
		snम_लिखो(adapter->bios_version, माप(adapter->fw_version),
			 "%c%d%d.%d%d",
			 adapter->product_info.bios_version[2],
			 0,
			 adapter->product_info.bios_version[1] & 0x0f,
			 0,
			 adapter->product_info.bios_version[0] & 0x0f);
	पूर्ण अन्यथा अणु
		स_नकल(adapter->fw_version,
				(अक्षर *)adapter->product_info.fw_version, 4);
		adapter->fw_version[4] = 0;

		स_नकल(adapter->bios_version,
				(अक्षर *)adapter->product_info.bios_version, 4);

		adapter->bios_version[4] = 0;
	पूर्ण

	dev_notice(&adapter->dev->dev, "[%s:%s] detected %d logical drives\n",
		adapter->fw_version, adapter->bios_version, adapter->numldrv);

	/*
	 * Do we support extended (>10 bytes) cdbs
	 */
	adapter->support_ext_cdb = mega_support_ext_cdb(adapter);
	अगर (adapter->support_ext_cdb)
		dev_notice(&adapter->dev->dev, "supports extended CDBs\n");


	वापस 0;
पूर्ण

/**
 * mega_runpendq()
 * @adapter: poपूर्णांकer to our soft state
 *
 * Runs through the list of pending requests.
 */
अटल अंतरभूत व्योम
mega_runpendq(adapter_t *adapter)
अणु
	अगर(!list_empty(&adapter->pending_list))
		__mega_runpendq(adapter);
पूर्ण

/*
 * megaraid_queue()
 * @scmd - Issue this scsi command
 * @करोne - the callback hook पूर्णांकo the scsi mid-layer
 *
 * The command queuing entry poपूर्णांक क्रम the mid-layer.
 */
अटल पूर्णांक
megaraid_queue_lck(काष्ठा scsi_cmnd *scmd, व्योम (*करोne)(काष्ठा scsi_cmnd *))
अणु
	adapter_t	*adapter;
	scb_t	*scb;
	पूर्णांक	busy=0;
	अचिन्हित दीर्घ flags;

	adapter = (adapter_t *)scmd->device->host->hostdata;

	scmd->scsi_करोne = करोne;


	/*
	 * Allocate and build a SCB request
	 * busy flag will be set अगर mega_build_cmd() command could not
	 * allocate scb. We will वापस non-zero status in that हाल.
	 * NOTE: scb can be null even though certain commands completed
	 * successfully, e.g., MODE_SENSE and TEST_UNIT_READY, we would
	 * वापस 0 in that हाल.
	 */

	spin_lock_irqsave(&adapter->lock, flags);
	scb = mega_build_cmd(adapter, scmd, &busy);
	अगर (!scb)
		जाओ out;

	scb->state |= SCB_PENDQ;
	list_add_tail(&scb->list, &adapter->pending_list);

	/*
	 * Check अगर the HBA is in quiescent state, e.g., during a
	 * delete logical drive opertion. If it is, करोn't run
	 * the pending_list.
	 */
	अगर (atomic_पढ़ो(&adapter->quiescent) == 0)
		mega_runpendq(adapter);

	busy = 0;
 out:
	spin_unlock_irqrestore(&adapter->lock, flags);
	वापस busy;
पूर्ण

अटल DEF_SCSI_QCMD(megaraid_queue)

/**
 * mega_allocate_scb()
 * @adapter: poपूर्णांकer to our soft state
 * @cmd: scsi command from the mid-layer
 *
 * Allocate a SCB काष्ठाure. This is the central काष्ठाure क्रम controller
 * commands.
 */
अटल अंतरभूत scb_t *
mega_allocate_scb(adapter_t *adapter, काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा list_head *head = &adapter->मुक्त_list;
	scb_t	*scb;

	/* Unlink command from Free List */
	अगर( !list_empty(head) ) अणु

		scb = list_entry(head->next, scb_t, list);

		list_del_init(head->next);

		scb->state = SCB_ACTIVE;
		scb->cmd = cmd;
		scb->dma_type = MEGA_DMA_TYPE_NONE;

		वापस scb;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * mega_get_ldrv_num()
 * @adapter: poपूर्णांकer to our soft state
 * @cmd: scsi mid layer command
 * @channel: channel on the controller
 *
 * Calculate the logical drive number based on the inक्रमmation in scsi command
 * and the channel number.
 */
अटल अंतरभूत पूर्णांक
mega_get_ldrv_num(adapter_t *adapter, काष्ठा scsi_cmnd *cmd, पूर्णांक channel)
अणु
	पूर्णांक		tgt;
	पूर्णांक		ldrv_num;

	tgt = cmd->device->id;
	
	अगर ( tgt > adapter->this_id )
		tgt--;	/* we करो not get inquires क्रम initiator id */

	ldrv_num = (channel * 15) + tgt;


	/*
	 * If we have a logical drive with boot enabled, project it first
	 */
	अगर( adapter->boot_ldrv_enabled ) अणु
		अगर( ldrv_num == 0 ) अणु
			ldrv_num = adapter->boot_ldrv;
		पूर्ण
		अन्यथा अणु
			अगर( ldrv_num <= adapter->boot_ldrv ) अणु
				ldrv_num--;
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * If "delete logical drive" feature is enabled on this controller.
	 * Do only अगर at least one delete logical drive operation was करोne.
	 *
	 * Also, after logical drive deletion, instead of logical drive number,
	 * the value वापसed should be 0x80+logical drive id.
	 *
	 * These is valid only क्रम IO commands.
	 */

	अगर (adapter->support_अक्रमom_del && adapter->पढ़ो_ldidmap )
		चयन (cmd->cmnd[0]) अणु
		हाल READ_6:
		हाल WRITE_6:
		हाल READ_10:
		हाल WRITE_10:
			ldrv_num += 0x80;
		पूर्ण

	वापस ldrv_num;
पूर्ण

/**
 * mega_build_cmd()
 * @adapter: poपूर्णांकer to our soft state
 * @cmd: Prepare using this scsi command
 * @busy: busy flag अगर no resources
 *
 * Prepares a command and scatter gather list क्रम the controller. This routine
 * also finds out अगर the commands is पूर्णांकended क्रम a logical drive or a
 * physical device and prepares the controller command accordingly.
 *
 * We also re-order the logical drives and physical devices based on their
 * boot settings.
 */
अटल scb_t *
mega_build_cmd(adapter_t *adapter, काष्ठा scsi_cmnd *cmd, पूर्णांक *busy)
अणु
	mega_passthru	*pthru;
	scb_t	*scb;
	mbox_t	*mbox;
	u32	seg;
	अक्षर	islogical;
	पूर्णांक	max_ldrv_num;
	पूर्णांक	channel = 0;
	पूर्णांक	target = 0;
	पूर्णांक	ldrv_num = 0;   /* logical drive number */

	/*
	 * We know what channels our logical drives are on - mega_find_card()
	 */
	islogical = adapter->logdrv_chan[cmd->device->channel];

	/*
	 * The theory: If physical drive is chosen क्रम boot, all the physical
	 * devices are exported beक्रमe the logical drives, otherwise physical
	 * devices are pushed after logical drives, in which हाल - Kernel sees
	 * the physical devices on भव channel which is obviously converted
	 * to actual channel on the HBA.
	 */
	अगर( adapter->boot_pdrv_enabled ) अणु
		अगर( islogical ) अणु
			/* logical channel */
			channel = cmd->device->channel -
				adapter->product_info.nchannels;
		पूर्ण
		अन्यथा अणु
			/* this is physical channel */
			channel = cmd->device->channel; 
			target = cmd->device->id;

			/*
			 * boot from a physical disk, that disk needs to be
			 * exposed first IF both the channels are SCSI, then
			 * booting from the second channel is not allowed.
			 */
			अगर( target == 0 ) अणु
				target = adapter->boot_pdrv_tgt;
			पूर्ण
			अन्यथा अगर( target == adapter->boot_pdrv_tgt ) अणु
				target = 0;
			पूर्ण
		पूर्ण
	पूर्ण
	अन्यथा अणु
		अगर( islogical ) अणु
			/* this is the logical channel */
			channel = cmd->device->channel;	
		पूर्ण
		अन्यथा अणु
			/* physical channel */
			channel = cmd->device->channel - NVIRT_CHAN;	
			target = cmd->device->id;
		पूर्ण
	पूर्ण


	अगर(islogical) अणु

		/* have just LUN 0 क्रम each target on भव channels */
		अगर (cmd->device->lun) अणु
			cmd->result = (DID_BAD_TARGET << 16);
			cmd->scsi_करोne(cmd);
			वापस शून्य;
		पूर्ण

		ldrv_num = mega_get_ldrv_num(adapter, cmd, channel);


		max_ldrv_num = (adapter->flag & BOARD_40LD) ?
			MAX_LOGICAL_DRIVES_40LD : MAX_LOGICAL_DRIVES_8LD;

		/*
		 * max_ldrv_num increases by 0x80 अगर some logical drive was
		 * deleted.
		 */
		अगर(adapter->पढ़ो_ldidmap)
			max_ldrv_num += 0x80;

		अगर(ldrv_num > max_ldrv_num ) अणु
			cmd->result = (DID_BAD_TARGET << 16);
			cmd->scsi_करोne(cmd);
			वापस शून्य;
		पूर्ण

	पूर्ण
	अन्यथा अणु
		अगर( cmd->device->lun > 7) अणु
			/*
			 * Do not support lun >7 क्रम physically accessed
			 * devices
			 */
			cmd->result = (DID_BAD_TARGET << 16);
			cmd->scsi_करोne(cmd);
			वापस शून्य;
		पूर्ण
	पूर्ण

	/*
	 *
	 * Logical drive commands
	 *
	 */
	अगर(islogical) अणु
		चयन (cmd->cmnd[0]) अणु
		हाल TEST_UNIT_READY:
#अगर MEGA_HAVE_CLUSTERING
			/*
			 * Do we support clustering and is the support enabled
			 * If no, वापस success always
			 */
			अगर( !adapter->has_cluster ) अणु
				cmd->result = (DID_OK << 16);
				cmd->scsi_करोne(cmd);
				वापस शून्य;
			पूर्ण

			अगर(!(scb = mega_allocate_scb(adapter, cmd))) अणु
				*busy = 1;
				वापस शून्य;
			पूर्ण

			scb->raw_mbox[0] = MEGA_CLUSTER_CMD;
			scb->raw_mbox[2] = MEGA_RESERVATION_STATUS;
			scb->raw_mbox[3] = ldrv_num;

			scb->dma_direction = DMA_NONE;

			वापस scb;
#अन्यथा
			cmd->result = (DID_OK << 16);
			cmd->scsi_करोne(cmd);
			वापस शून्य;
#पूर्ण_अगर

		हाल MODE_SENSE: अणु
			अक्षर *buf;
			काष्ठा scatterlist *sg;

			sg = scsi_sglist(cmd);
			buf = kmap_atomic(sg_page(sg)) + sg->offset;

			स_रखो(buf, 0, cmd->cmnd[4]);
			kunmap_atomic(buf - sg->offset);

			cmd->result = (DID_OK << 16);
			cmd->scsi_करोne(cmd);
			वापस शून्य;
		पूर्ण

		हाल READ_CAPACITY:
		हाल INQUIRY:

			अगर(!(adapter->flag & (1L << cmd->device->channel))) अणु

				dev_notice(&adapter->dev->dev,
					"scsi%d: scanning scsi channel %d "
					"for logical drives\n",
						adapter->host->host_no,
						cmd->device->channel);

				adapter->flag |= (1L << cmd->device->channel);
			पूर्ण

			/* Allocate a SCB and initialize passthru */
			अगर(!(scb = mega_allocate_scb(adapter, cmd))) अणु
				*busy = 1;
				वापस शून्य;
			पूर्ण
			pthru = scb->pthru;

			mbox = (mbox_t *)scb->raw_mbox;
			स_रखो(mbox, 0, माप(scb->raw_mbox));
			स_रखो(pthru, 0, माप(mega_passthru));

			pthru->समयout = 0;
			pthru->ars = 1;
			pthru->reqsenselen = 14;
			pthru->islogical = 1;
			pthru->logdrv = ldrv_num;
			pthru->cdblen = cmd->cmd_len;
			स_नकल(pthru->cdb, cmd->cmnd, cmd->cmd_len);

			अगर( adapter->has_64bit_addr ) अणु
				mbox->m_out.cmd = MEGA_MBOXCMD_PASSTHRU64;
			पूर्ण
			अन्यथा अणु
				mbox->m_out.cmd = MEGA_MBOXCMD_PASSTHRU;
			पूर्ण

			scb->dma_direction = DMA_FROM_DEVICE;

			pthru->numsgelements = mega_build_sglist(adapter, scb,
				&pthru->dataxferaddr, &pthru->dataxferlen);

			mbox->m_out.xferaddr = scb->pthru_dma_addr;

			वापस scb;

		हाल READ_6:
		हाल WRITE_6:
		हाल READ_10:
		हाल WRITE_10:
		हाल READ_12:
		हाल WRITE_12:

			/* Allocate a SCB and initialize mailbox */
			अगर(!(scb = mega_allocate_scb(adapter, cmd))) अणु
				*busy = 1;
				वापस शून्य;
			पूर्ण
			mbox = (mbox_t *)scb->raw_mbox;

			स_रखो(mbox, 0, माप(scb->raw_mbox));
			mbox->m_out.logdrv = ldrv_num;

			/*
			 * A little hack: 2nd bit is zero क्रम all scsi पढ़ो
			 * commands and is set क्रम all scsi ग_लिखो commands
			 */
			अगर( adapter->has_64bit_addr ) अणु
				mbox->m_out.cmd = (*cmd->cmnd & 0x02) ?
					MEGA_MBOXCMD_LWRITE64:
					MEGA_MBOXCMD_LREAD64 ;
			पूर्ण
			अन्यथा अणु
				mbox->m_out.cmd = (*cmd->cmnd & 0x02) ?
					MEGA_MBOXCMD_LWRITE:
					MEGA_MBOXCMD_LREAD ;
			पूर्ण

			/*
			 * 6-byte READ(0x08) or WRITE(0x0A) cdb
			 */
			अगर( cmd->cmd_len == 6 ) अणु
				mbox->m_out.numsectors = (u32) cmd->cmnd[4];
				mbox->m_out.lba =
					((u32)cmd->cmnd[1] << 16) |
					((u32)cmd->cmnd[2] << 8) |
					(u32)cmd->cmnd[3];

				mbox->m_out.lba &= 0x1FFFFF;

#अगर MEGA_HAVE_STATS
				/*
				 * Take modulo 0x80, since the logical drive
				 * number increases by 0x80 when a logical
				 * drive was deleted
				 */
				अगर (*cmd->cmnd == READ_6) अणु
					adapter->nपढ़ोs[ldrv_num%0x80]++;
					adapter->nपढ़ोblocks[ldrv_num%0x80] +=
						mbox->m_out.numsectors;
				पूर्ण अन्यथा अणु
					adapter->nग_लिखोs[ldrv_num%0x80]++;
					adapter->nग_लिखोblocks[ldrv_num%0x80] +=
						mbox->m_out.numsectors;
				पूर्ण
#पूर्ण_अगर
			पूर्ण

			/*
			 * 10-byte READ(0x28) or WRITE(0x2A) cdb
			 */
			अगर( cmd->cmd_len == 10 ) अणु
				mbox->m_out.numsectors =
					(u32)cmd->cmnd[8] |
					((u32)cmd->cmnd[7] << 8);
				mbox->m_out.lba =
					((u32)cmd->cmnd[2] << 24) |
					((u32)cmd->cmnd[3] << 16) |
					((u32)cmd->cmnd[4] << 8) |
					(u32)cmd->cmnd[5];

#अगर MEGA_HAVE_STATS
				अगर (*cmd->cmnd == READ_10) अणु
					adapter->nपढ़ोs[ldrv_num%0x80]++;
					adapter->nपढ़ोblocks[ldrv_num%0x80] +=
						mbox->m_out.numsectors;
				पूर्ण अन्यथा अणु
					adapter->nग_लिखोs[ldrv_num%0x80]++;
					adapter->nग_लिखोblocks[ldrv_num%0x80] +=
						mbox->m_out.numsectors;
				पूर्ण
#पूर्ण_अगर
			पूर्ण

			/*
			 * 12-byte READ(0xA8) or WRITE(0xAA) cdb
			 */
			अगर( cmd->cmd_len == 12 ) अणु
				mbox->m_out.lba =
					((u32)cmd->cmnd[2] << 24) |
					((u32)cmd->cmnd[3] << 16) |
					((u32)cmd->cmnd[4] << 8) |
					(u32)cmd->cmnd[5];

				mbox->m_out.numsectors =
					((u32)cmd->cmnd[6] << 24) |
					((u32)cmd->cmnd[7] << 16) |
					((u32)cmd->cmnd[8] << 8) |
					(u32)cmd->cmnd[9];

#अगर MEGA_HAVE_STATS
				अगर (*cmd->cmnd == READ_12) अणु
					adapter->nपढ़ोs[ldrv_num%0x80]++;
					adapter->nपढ़ोblocks[ldrv_num%0x80] +=
						mbox->m_out.numsectors;
				पूर्ण अन्यथा अणु
					adapter->nग_लिखोs[ldrv_num%0x80]++;
					adapter->nग_लिखोblocks[ldrv_num%0x80] +=
						mbox->m_out.numsectors;
				पूर्ण
#पूर्ण_अगर
			पूर्ण

			/*
			 * If it is a पढ़ो command
			 */
			अगर( (*cmd->cmnd & 0x0F) == 0x08 ) अणु
				scb->dma_direction = DMA_FROM_DEVICE;
			पूर्ण
			अन्यथा अणु
				scb->dma_direction = DMA_TO_DEVICE;
			पूर्ण

			/* Calculate Scatter-Gather info */
			mbox->m_out.numsgelements = mega_build_sglist(adapter, scb,
					(u32 *)&mbox->m_out.xferaddr, &seg);

			वापस scb;

#अगर MEGA_HAVE_CLUSTERING
		हाल RESERVE:
		हाल RELEASE:

			/*
			 * Do we support clustering and is the support enabled
			 */
			अगर( ! adapter->has_cluster ) अणु

				cmd->result = (DID_BAD_TARGET << 16);
				cmd->scsi_करोne(cmd);
				वापस शून्य;
			पूर्ण

			/* Allocate a SCB and initialize mailbox */
			अगर(!(scb = mega_allocate_scb(adapter, cmd))) अणु
				*busy = 1;
				वापस शून्य;
			पूर्ण

			scb->raw_mbox[0] = MEGA_CLUSTER_CMD;
			scb->raw_mbox[2] = ( *cmd->cmnd == RESERVE ) ?
				MEGA_RESERVE_LD : MEGA_RELEASE_LD;

			scb->raw_mbox[3] = ldrv_num;

			scb->dma_direction = DMA_NONE;

			वापस scb;
#पूर्ण_अगर

		शेष:
			cmd->result = (DID_BAD_TARGET << 16);
			cmd->scsi_करोne(cmd);
			वापस शून्य;
		पूर्ण
	पूर्ण

	/*
	 * Passthru drive commands
	 */
	अन्यथा अणु
		/* Allocate a SCB and initialize passthru */
		अगर(!(scb = mega_allocate_scb(adapter, cmd))) अणु
			*busy = 1;
			वापस शून्य;
		पूर्ण

		mbox = (mbox_t *)scb->raw_mbox;
		स_रखो(mbox, 0, माप(scb->raw_mbox));

		अगर( adapter->support_ext_cdb ) अणु

			mega_prepare_extpassthru(adapter, scb, cmd,
					channel, target);

			mbox->m_out.cmd = MEGA_MBOXCMD_EXTPTHRU;

			mbox->m_out.xferaddr = scb->epthru_dma_addr;

		पूर्ण
		अन्यथा अणु

			pthru = mega_prepare_passthru(adapter, scb, cmd,
					channel, target);

			/* Initialize mailbox */
			अगर( adapter->has_64bit_addr ) अणु
				mbox->m_out.cmd = MEGA_MBOXCMD_PASSTHRU64;
			पूर्ण
			अन्यथा अणु
				mbox->m_out.cmd = MEGA_MBOXCMD_PASSTHRU;
			पूर्ण

			mbox->m_out.xferaddr = scb->pthru_dma_addr;

		पूर्ण
		वापस scb;
	पूर्ण
	वापस शून्य;
पूर्ण


/**
 * mega_prepare_passthru()
 * @adapter: poपूर्णांकer to our soft state
 * @scb: our scsi control block
 * @cmd: scsi command from the mid-layer
 * @channel: actual channel on the controller
 * @target: actual id on the controller.
 *
 * prepare a command क्रम the scsi physical devices.
 */
अटल mega_passthru *
mega_prepare_passthru(adapter_t *adapter, scb_t *scb, काष्ठा scsi_cmnd *cmd,
		      पूर्णांक channel, पूर्णांक target)
अणु
	mega_passthru *pthru;

	pthru = scb->pthru;
	स_रखो(pthru, 0, माप (mega_passthru));

	/* 0=6sec/1=60sec/2=10min/3=3hrs */
	pthru->समयout = 2;

	pthru->ars = 1;
	pthru->reqsenselen = 14;
	pthru->islogical = 0;

	pthru->channel = (adapter->flag & BOARD_40LD) ? 0 : channel;

	pthru->target = (adapter->flag & BOARD_40LD) ?
		(channel << 4) | target : target;

	pthru->cdblen = cmd->cmd_len;
	pthru->logdrv = cmd->device->lun;

	स_नकल(pthru->cdb, cmd->cmnd, cmd->cmd_len);

	/* Not sure about the direction */
	scb->dma_direction = DMA_BIसूचीECTIONAL;

	/* Special Code क्रम Handling READ_CAPA/ INQ using bounce buffers */
	चयन (cmd->cmnd[0]) अणु
	हाल INQUIRY:
	हाल READ_CAPACITY:
		अगर(!(adapter->flag & (1L << cmd->device->channel))) अणु

			dev_notice(&adapter->dev->dev,
				"scsi%d: scanning scsi channel %d [P%d] "
				"for physical devices\n",
					adapter->host->host_no,
					cmd->device->channel, channel);

			adapter->flag |= (1L << cmd->device->channel);
		पूर्ण
		fallthrough;
	शेष:
		pthru->numsgelements = mega_build_sglist(adapter, scb,
				&pthru->dataxferaddr, &pthru->dataxferlen);
		अवरोध;
	पूर्ण
	वापस pthru;
पूर्ण


/**
 * mega_prepare_extpassthru()
 * @adapter: poपूर्णांकer to our soft state
 * @scb: our scsi control block
 * @cmd: scsi command from the mid-layer
 * @channel: actual channel on the controller
 * @target: actual id on the controller.
 *
 * prepare a command क्रम the scsi physical devices. This rountine prepares
 * commands क्रम devices which can take extended CDBs (>10 bytes)
 */
अटल mega_ext_passthru *
mega_prepare_extpassthru(adapter_t *adapter, scb_t *scb,
			 काष्ठा scsi_cmnd *cmd,
			 पूर्णांक channel, पूर्णांक target)
अणु
	mega_ext_passthru	*epthru;

	epthru = scb->epthru;
	स_रखो(epthru, 0, माप(mega_ext_passthru));

	/* 0=6sec/1=60sec/2=10min/3=3hrs */
	epthru->समयout = 2;

	epthru->ars = 1;
	epthru->reqsenselen = 14;
	epthru->islogical = 0;

	epthru->channel = (adapter->flag & BOARD_40LD) ? 0 : channel;
	epthru->target = (adapter->flag & BOARD_40LD) ?
		(channel << 4) | target : target;

	epthru->cdblen = cmd->cmd_len;
	epthru->logdrv = cmd->device->lun;

	स_नकल(epthru->cdb, cmd->cmnd, cmd->cmd_len);

	/* Not sure about the direction */
	scb->dma_direction = DMA_BIसूचीECTIONAL;

	चयन(cmd->cmnd[0]) अणु
	हाल INQUIRY:
	हाल READ_CAPACITY:
		अगर(!(adapter->flag & (1L << cmd->device->channel))) अणु

			dev_notice(&adapter->dev->dev,
				"scsi%d: scanning scsi channel %d [P%d] "
				"for physical devices\n",
					adapter->host->host_no,
					cmd->device->channel, channel);

			adapter->flag |= (1L << cmd->device->channel);
		पूर्ण
		fallthrough;
	शेष:
		epthru->numsgelements = mega_build_sglist(adapter, scb,
				&epthru->dataxferaddr, &epthru->dataxferlen);
		अवरोध;
	पूर्ण

	वापस epthru;
पूर्ण

अटल व्योम
__mega_runpendq(adapter_t *adapter)
अणु
	scb_t *scb;
	काष्ठा list_head *pos, *next;

	/* Issue any pending commands to the card */
	list_क्रम_each_safe(pos, next, &adapter->pending_list) अणु

		scb = list_entry(pos, scb_t, list);

		अगर( !(scb->state & SCB_ISSUED) ) अणु

			अगर( issue_scb(adapter, scb) != 0 )
				वापस;
		पूर्ण
	पूर्ण

	वापस;
पूर्ण


/**
 * issue_scb()
 * @adapter: poपूर्णांकer to our soft state
 * @scb: scsi control block
 *
 * Post a command to the card अगर the mailbox is available, otherwise वापस
 * busy. We also take the scb from the pending list अगर the mailbox is
 * available.
 */
अटल पूर्णांक
issue_scb(adapter_t *adapter, scb_t *scb)
अणु
	अस्थिर mbox64_t	*mbox64 = adapter->mbox64;
	अस्थिर mbox_t		*mbox = adapter->mbox;
	अचिन्हित पूर्णांक	i = 0;

	अगर(unlikely(mbox->m_in.busy)) अणु
		करो अणु
			udelay(1);
			i++;
		पूर्ण जबतक( mbox->m_in.busy && (i < max_mbox_busy_रुको) );

		अगर(mbox->m_in.busy) वापस -1;
	पूर्ण

	/* Copy mailbox data पूर्णांकo host काष्ठाure */
	स_नकल((अक्षर *)&mbox->m_out, (अक्षर *)scb->raw_mbox, 
			माप(काष्ठा mbox_out));

	mbox->m_out.cmdid = scb->idx;	/* Set cmdid */
	mbox->m_in.busy = 1;		/* Set busy */


	/*
	 * Increment the pending queue counter
	 */
	atomic_inc(&adapter->pend_cmds);

	चयन (mbox->m_out.cmd) अणु
	हाल MEGA_MBOXCMD_LREAD64:
	हाल MEGA_MBOXCMD_LWRITE64:
	हाल MEGA_MBOXCMD_PASSTHRU64:
	हाल MEGA_MBOXCMD_EXTPTHRU:
		mbox64->xfer_segment_lo = mbox->m_out.xferaddr;
		mbox64->xfer_segment_hi = 0;
		mbox->m_out.xferaddr = 0xFFFFFFFF;
		अवरोध;
	शेष:
		mbox64->xfer_segment_lo = 0;
		mbox64->xfer_segment_hi = 0;
	पूर्ण

	/*
	 * post the command
	 */
	scb->state |= SCB_ISSUED;

	अगर( likely(adapter->flag & BOARD_MEMMAP) ) अणु
		mbox->m_in.poll = 0;
		mbox->m_in.ack = 0;
		WRINDOOR(adapter, adapter->mbox_dma | 0x1);
	पूर्ण
	अन्यथा अणु
		irq_enable(adapter);
		issue_command(adapter);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Wait until the controller's mailbox is available
 */
अटल अंतरभूत पूर्णांक
mega_busyरुको_mbox (adapter_t *adapter)
अणु
	अगर (adapter->mbox->m_in.busy)
		वापस __mega_busyरुको_mbox(adapter);
	वापस 0;
पूर्ण

/**
 * issue_scb_block()
 * @adapter: poपूर्णांकer to our soft state
 * @raw_mbox: the mailbox
 *
 * Issue a scb in synchronous and non-पूर्णांकerrupt mode
 */
अटल पूर्णांक
issue_scb_block(adapter_t *adapter, u_अक्षर *raw_mbox)
अणु
	अस्थिर mbox64_t *mbox64 = adapter->mbox64;
	अस्थिर mbox_t *mbox = adapter->mbox;
	u8	byte;

	/* Wait until mailbox is मुक्त */
	अगर(mega_busyरुको_mbox (adapter))
		जाओ bug_blocked_mailbox;

	/* Copy mailbox data पूर्णांकo host काष्ठाure */
	स_नकल((अक्षर *) mbox, raw_mbox, माप(काष्ठा mbox_out));
	mbox->m_out.cmdid = 0xFE;
	mbox->m_in.busy = 1;

	चयन (raw_mbox[0]) अणु
	हाल MEGA_MBOXCMD_LREAD64:
	हाल MEGA_MBOXCMD_LWRITE64:
	हाल MEGA_MBOXCMD_PASSTHRU64:
	हाल MEGA_MBOXCMD_EXTPTHRU:
		mbox64->xfer_segment_lo = mbox->m_out.xferaddr;
		mbox64->xfer_segment_hi = 0;
		mbox->m_out.xferaddr = 0xFFFFFFFF;
		अवरोध;
	शेष:
		mbox64->xfer_segment_lo = 0;
		mbox64->xfer_segment_hi = 0;
	पूर्ण

	अगर( likely(adapter->flag & BOARD_MEMMAP) ) अणु
		mbox->m_in.poll = 0;
		mbox->m_in.ack = 0;
		mbox->m_in.numstatus = 0xFF;
		mbox->m_in.status = 0xFF;
		WRINDOOR(adapter, adapter->mbox_dma | 0x1);

		जबतक((अस्थिर u8)mbox->m_in.numstatus == 0xFF)
			cpu_relax();

		mbox->m_in.numstatus = 0xFF;

		जबतक( (अस्थिर u8)mbox->m_in.poll != 0x77 )
			cpu_relax();

		mbox->m_in.poll = 0;
		mbox->m_in.ack = 0x77;

		WRINDOOR(adapter, adapter->mbox_dma | 0x2);

		जबतक(RDINDOOR(adapter) & 0x2)
			cpu_relax();
	पूर्ण
	अन्यथा अणु
		irq_disable(adapter);
		issue_command(adapter);

		जबतक (!((byte = irq_state(adapter)) & INTR_VALID))
			cpu_relax();

		set_irq_state(adapter, byte);
		irq_enable(adapter);
		irq_ack(adapter);
	पूर्ण

	वापस mbox->m_in.status;

bug_blocked_mailbox:
	dev_warn(&adapter->dev->dev, "Blocked mailbox......!!\n");
	udelay (1000);
	वापस -1;
पूर्ण


/**
 * megaraid_isr_iomapped()
 * @irq: irq
 * @devp: poपूर्णांकer to our soft state
 *
 * Interrupt service routine क्रम io-mapped controllers.
 * Find out अगर our device is पूर्णांकerrupting. If yes, acknowledge the पूर्णांकerrupt
 * and service the completed commands.
 */
अटल irqवापस_t
megaraid_isr_iomapped(पूर्णांक irq, व्योम *devp)
अणु
	adapter_t	*adapter = devp;
	अचिन्हित दीर्घ	flags;
	u8	status;
	u8	nstatus;
	u8	completed[MAX_FIRMWARE_STATUS];
	u8	byte;
	पूर्णांक	handled = 0;


	/*
	 * loop till F/W has more commands क्रम us to complete.
	 */
	spin_lock_irqsave(&adapter->lock, flags);

	करो अणु
		/* Check अगर a valid पूर्णांकerrupt is pending */
		byte = irq_state(adapter);
		अगर( (byte & VALID_INTR_BYTE) == 0 ) अणु
			/*
			 * No more pending commands
			 */
			जाओ out_unlock;
		पूर्ण
		set_irq_state(adapter, byte);

		जबतक((nstatus = (अस्थिर u8)adapter->mbox->m_in.numstatus)
				== 0xFF)
			cpu_relax();
		adapter->mbox->m_in.numstatus = 0xFF;

		status = adapter->mbox->m_in.status;

		/*
		 * decrement the pending queue counter
		 */
		atomic_sub(nstatus, &adapter->pend_cmds);

		स_नकल(completed, (व्योम *)adapter->mbox->m_in.completed, 
				nstatus);

		/* Acknowledge पूर्णांकerrupt */
		irq_ack(adapter);

		mega_cmd_करोne(adapter, completed, nstatus, status);

		mega_runकरोneq(adapter);

		handled = 1;

		/* Loop through any pending requests */
		अगर(atomic_पढ़ो(&adapter->quiescent) == 0) अणु
			mega_runpendq(adapter);
		पूर्ण

	पूर्ण जबतक(1);

 out_unlock:

	spin_unlock_irqrestore(&adapter->lock, flags);

	वापस IRQ_RETVAL(handled);
पूर्ण


/**
 * megaraid_isr_memmapped()
 * @irq: irq
 * @devp: poपूर्णांकer to our soft state
 *
 * Interrupt service routine क्रम memory-mapped controllers.
 * Find out अगर our device is पूर्णांकerrupting. If yes, acknowledge the पूर्णांकerrupt
 * and service the completed commands.
 */
अटल irqवापस_t
megaraid_isr_memmapped(पूर्णांक irq, व्योम *devp)
अणु
	adapter_t	*adapter = devp;
	अचिन्हित दीर्घ	flags;
	u8	status;
	u32	dword = 0;
	u8	nstatus;
	u8	completed[MAX_FIRMWARE_STATUS];
	पूर्णांक	handled = 0;


	/*
	 * loop till F/W has more commands क्रम us to complete.
	 */
	spin_lock_irqsave(&adapter->lock, flags);

	करो अणु
		/* Check अगर a valid पूर्णांकerrupt is pending */
		dword = RDOUTDOOR(adapter);
		अगर(dword != 0x10001234) अणु
			/*
			 * No more pending commands
			 */
			जाओ out_unlock;
		पूर्ण
		WROUTDOOR(adapter, 0x10001234);

		जबतक((nstatus = (अस्थिर u8)adapter->mbox->m_in.numstatus)
				== 0xFF) अणु
			cpu_relax();
		पूर्ण
		adapter->mbox->m_in.numstatus = 0xFF;

		status = adapter->mbox->m_in.status;

		/*
		 * decrement the pending queue counter
		 */
		atomic_sub(nstatus, &adapter->pend_cmds);

		स_नकल(completed, (व्योम *)adapter->mbox->m_in.completed, 
				nstatus);

		/* Acknowledge पूर्णांकerrupt */
		WRINDOOR(adapter, 0x2);

		handled = 1;

		जबतक( RDINDOOR(adapter) & 0x02 )
			cpu_relax();

		mega_cmd_करोne(adapter, completed, nstatus, status);

		mega_runकरोneq(adapter);

		/* Loop through any pending requests */
		अगर(atomic_पढ़ो(&adapter->quiescent) == 0) अणु
			mega_runpendq(adapter);
		पूर्ण

	पूर्ण जबतक(1);

 out_unlock:

	spin_unlock_irqrestore(&adapter->lock, flags);

	वापस IRQ_RETVAL(handled);
पूर्ण
/**
 * mega_cmd_करोne()
 * @adapter: poपूर्णांकer to our soft state
 * @completed: array of ids of completed commands
 * @nstatus: number of completed commands
 * @status: status of the last command completed
 *
 * Complete the commands and call the scsi mid-layer callback hooks.
 */
अटल व्योम
mega_cmd_करोne(adapter_t *adapter, u8 completed[], पूर्णांक nstatus, पूर्णांक status)
अणु
	mega_ext_passthru	*epthru = शून्य;
	काष्ठा scatterlist	*sgl;
	काष्ठा scsi_cmnd	*cmd = शून्य;
	mega_passthru	*pthru = शून्य;
	mbox_t	*mbox = शून्य;
	u8	c;
	scb_t	*scb;
	पूर्णांक	islogical;
	पूर्णांक	cmdid;
	पूर्णांक	i;

	/*
	 * क्रम all the commands completed, call the mid-layer callback routine
	 * and मुक्त the scb.
	 */
	क्रम( i = 0; i < nstatus; i++ ) अणु

		cmdid = completed[i];

		/*
		 * Only मुक्त SCBs क्रम the commands coming करोwn from the
		 * mid-layer, not क्रम which were issued पूर्णांकernally
		 *
		 * For पूर्णांकernal command, restore the status वापसed by the
		 * firmware so that user can पूर्णांकerpret it.
		 */
		अगर (cmdid == CMDID_INT_CMDS) अणु
			scb = &adapter->पूर्णांक_scb;

			list_del_init(&scb->list);
			scb->state = SCB_FREE;

			adapter->पूर्णांक_status = status;
			complete(&adapter->पूर्णांक_रुकोq);
		पूर्ण अन्यथा अणु
			scb = &adapter->scb_list[cmdid];

			/*
			 * Make sure f/w has completed a valid command
			 */
			अगर( !(scb->state & SCB_ISSUED) || scb->cmd == शून्य ) अणु
				dev_crit(&adapter->dev->dev, "invalid command "
					"Id %d, scb->state:%x, scsi cmd:%p\n",
					cmdid, scb->state, scb->cmd);

				जारी;
			पूर्ण

			/*
			 * Was a पात issued क्रम this command
			 */
			अगर( scb->state & SCB_ABORT ) अणु

				dev_warn(&adapter->dev->dev,
					"aborted cmd [%x] complete\n",
					scb->idx);

				scb->cmd->result = (DID_ABORT << 16);

				list_add_tail(SCSI_LIST(scb->cmd),
						&adapter->completed_list);

				mega_मुक्त_scb(adapter, scb);

				जारी;
			पूर्ण

			/*
			 * Was a reset issued क्रम this command
			 */
			अगर( scb->state & SCB_RESET ) अणु

				dev_warn(&adapter->dev->dev,
					"reset cmd [%x] complete\n",
					scb->idx);

				scb->cmd->result = (DID_RESET << 16);

				list_add_tail(SCSI_LIST(scb->cmd),
						&adapter->completed_list);

				mega_मुक्त_scb (adapter, scb);

				जारी;
			पूर्ण

			cmd = scb->cmd;
			pthru = scb->pthru;
			epthru = scb->epthru;
			mbox = (mbox_t *)scb->raw_mbox;

#अगर MEGA_HAVE_STATS
			अणु

			पूर्णांक	logdrv = mbox->m_out.logdrv;

			islogical = adapter->logdrv_chan[cmd->channel];
			/*
			 * Maपूर्णांकain an error counter क्रम the logical drive.
			 * Some application like SNMP agent need such
			 * statistics
			 */
			अगर( status && islogical && (cmd->cmnd[0] == READ_6 ||
						cmd->cmnd[0] == READ_10 ||
						cmd->cmnd[0] == READ_12)) अणु
				/*
				 * Logical drive number increases by 0x80 when
				 * a logical drive is deleted
				 */
				adapter->rd_errors[logdrv%0x80]++;
			पूर्ण

			अगर( status && islogical && (cmd->cmnd[0] == WRITE_6 ||
						cmd->cmnd[0] == WRITE_10 ||
						cmd->cmnd[0] == WRITE_12)) अणु
				/*
				 * Logical drive number increases by 0x80 when
				 * a logical drive is deleted
				 */
				adapter->wr_errors[logdrv%0x80]++;
			पूर्ण

			पूर्ण
#पूर्ण_अगर
		पूर्ण

		/*
		 * Do not वापस the presence of hard disk on the channel so,
		 * inquiry sent, and वापसed data==hard disk or removable
		 * hard disk and not logical, request should वापस failure! -
		 * PJ
		 */
		islogical = adapter->logdrv_chan[cmd->device->channel];
		अगर( cmd->cmnd[0] == INQUIRY && !islogical ) अणु

			sgl = scsi_sglist(cmd);
			अगर( sg_page(sgl) ) अणु
				c = *(अचिन्हित अक्षर *) sg_virt(&sgl[0]);
			पूर्ण अन्यथा अणु
				dev_warn(&adapter->dev->dev, "invalid sg\n");
				c = 0;
			पूर्ण

			अगर(IS_RAID_CH(adapter, cmd->device->channel) &&
					((c & 0x1F ) == TYPE_DISK)) अणु
				status = 0xF0;
			पूर्ण
		पूर्ण

		/* clear result; otherwise, success वापसs corrupt value */
		cmd->result = 0;

		/* Convert MegaRAID status to Linux error code */
		चयन (status) अणु
		हाल 0x00:	/* SUCCESS , i.e. SCSI_STATUS_GOOD */
			cmd->result |= (DID_OK << 16);
			अवरोध;

		हाल 0x02:	/* ERROR_ABORTED, i.e.
				   SCSI_STATUS_CHECK_CONDITION */

			/* set sense_buffer and result fields */
			अगर( mbox->m_out.cmd == MEGA_MBOXCMD_PASSTHRU ||
				mbox->m_out.cmd == MEGA_MBOXCMD_PASSTHRU64 ) अणु

				स_नकल(cmd->sense_buffer, pthru->reqsensearea,
						14);

				cmd->result = (DRIVER_SENSE << 24) |
					(DID_OK << 16) |
					(CHECK_CONDITION << 1);
			पूर्ण
			अन्यथा अणु
				अगर (mbox->m_out.cmd == MEGA_MBOXCMD_EXTPTHRU) अणु

					स_नकल(cmd->sense_buffer,
						epthru->reqsensearea, 14);

					cmd->result = (DRIVER_SENSE << 24) |
						(DID_OK << 16) |
						(CHECK_CONDITION << 1);
				पूर्ण अन्यथा अणु
					cmd->sense_buffer[0] = 0x70;
					cmd->sense_buffer[2] = ABORTED_COMMAND;
					cmd->result |= (CHECK_CONDITION << 1);
				पूर्ण
			पूर्ण
			अवरोध;

		हाल 0x08:	/* ERR_DEST_DRIVE_FAILED, i.e.
				   SCSI_STATUS_BUSY */
			cmd->result |= (DID_BUS_BUSY << 16) | status;
			अवरोध;

		शेष:
#अगर MEGA_HAVE_CLUSTERING
			/*
			 * If TEST_UNIT_READY fails, we know
			 * MEGA_RESERVATION_STATUS failed
			 */
			अगर( cmd->cmnd[0] == TEST_UNIT_READY ) अणु
				cmd->result |= (DID_ERROR << 16) |
					(RESERVATION_CONFLICT << 1);
			पूर्ण
			अन्यथा
			/*
			 * Error code वापसed is 1 अगर Reserve or Release
			 * failed or the input parameter is invalid
			 */
			अगर( status == 1 &&
				(cmd->cmnd[0] == RESERVE ||
					 cmd->cmnd[0] == RELEASE) ) अणु

				cmd->result |= (DID_ERROR << 16) |
					(RESERVATION_CONFLICT << 1);
			पूर्ण
			अन्यथा
#पूर्ण_अगर
				cmd->result |= (DID_BAD_TARGET << 16)|status;
		पूर्ण

		mega_मुक्त_scb(adapter, scb);

		/* Add Scsi_Command to end of completed queue */
		list_add_tail(SCSI_LIST(cmd), &adapter->completed_list);
	पूर्ण
पूर्ण


/*
 * mega_runpendq()
 *
 * Run through the list of completed requests and finish it
 */
अटल व्योम
mega_runकरोneq (adapter_t *adapter)
अणु
	काष्ठा scsi_cmnd *cmd;
	काष्ठा list_head *pos;

	list_क्रम_each(pos, &adapter->completed_list) अणु

		काष्ठा scsi_poपूर्णांकer* spos = (काष्ठा scsi_poपूर्णांकer *)pos;

		cmd = list_entry(spos, काष्ठा scsi_cmnd, SCp);
		cmd->scsi_करोne(cmd);
	पूर्ण

	INIT_LIST_HEAD(&adapter->completed_list);
पूर्ण


/*
 * Free a SCB काष्ठाure
 * Note: We assume the scsi commands associated with this scb is not मुक्त yet.
 */
अटल व्योम
mega_मुक्त_scb(adapter_t *adapter, scb_t *scb)
अणु
	चयन( scb->dma_type ) अणु

	हाल MEGA_DMA_TYPE_NONE:
		अवरोध;

	हाल MEGA_SGLIST:
		scsi_dma_unmap(scb->cmd);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/*
	 * Remove from the pending list
	 */
	list_del_init(&scb->list);

	/* Link the scb back पूर्णांकo मुक्त list */
	scb->state = SCB_FREE;
	scb->cmd = शून्य;

	list_add(&scb->list, &adapter->मुक्त_list);
पूर्ण


अटल पूर्णांक
__mega_busyरुको_mbox (adapter_t *adapter)
अणु
	अस्थिर mbox_t *mbox = adapter->mbox;
	दीर्घ counter;

	क्रम (counter = 0; counter < 10000; counter++) अणु
		अगर (!mbox->m_in.busy)
			वापस 0;
		udelay(100);
		cond_resched();
	पूर्ण
	वापस -1;		/* give up after 1 second */
पूर्ण

/*
 * Copies data to SGLIST
 * Note: For 64 bit cards, we need a minimum of one SG element क्रम पढ़ो/ग_लिखो
 */
अटल पूर्णांक
mega_build_sglist(adapter_t *adapter, scb_t *scb, u32 *buf, u32 *len)
अणु
	काष्ठा scatterlist *sg;
	काष्ठा scsi_cmnd	*cmd;
	पूर्णांक	sgcnt;
	पूर्णांक	idx;

	cmd = scb->cmd;

	/*
	 * Copy Scatter-Gather list info पूर्णांकo controller काष्ठाure.
	 *
	 * The number of sg elements वापसed must not exceed our limit
	 */
	sgcnt = scsi_dma_map(cmd);

	scb->dma_type = MEGA_SGLIST;

	BUG_ON(sgcnt > adapter->sglen || sgcnt < 0);

	*len = 0;

	अगर (scsi_sg_count(cmd) == 1 && !adapter->has_64bit_addr) अणु
		sg = scsi_sglist(cmd);
		scb->dma_h_bulkdata = sg_dma_address(sg);
		*buf = (u32)scb->dma_h_bulkdata;
		*len = sg_dma_len(sg);
		वापस 0;
	पूर्ण

	scsi_क्रम_each_sg(cmd, sg, sgcnt, idx) अणु
		अगर (adapter->has_64bit_addr) अणु
			scb->sgl64[idx].address = sg_dma_address(sg);
			*len += scb->sgl64[idx].length = sg_dma_len(sg);
		पूर्ण अन्यथा अणु
			scb->sgl[idx].address = sg_dma_address(sg);
			*len += scb->sgl[idx].length = sg_dma_len(sg);
		पूर्ण
	पूर्ण

	/* Reset poपूर्णांकer and length fields */
	*buf = scb->sgl_dma_addr;

	/* Return count of SG requests */
	वापस sgcnt;
पूर्ण


/*
 * mega_8_to_40ld()
 *
 * takes all info in AdapterInquiry काष्ठाure and माला_दो it पूर्णांकo ProductInfo and
 * Enquiry3 काष्ठाures क्रम later use
 */
अटल व्योम
mega_8_to_40ld(mraid_inquiry *inquiry, mega_inquiry3 *enquiry3,
		mega_product_info *product_info)
अणु
	पूर्णांक i;

	product_info->max_commands = inquiry->adapter_info.max_commands;
	enquiry3->rebuild_rate = inquiry->adapter_info.rebuild_rate;
	product_info->nchannels = inquiry->adapter_info.nchannels;

	क्रम (i = 0; i < 4; i++) अणु
		product_info->fw_version[i] =
			inquiry->adapter_info.fw_version[i];

		product_info->bios_version[i] =
			inquiry->adapter_info.bios_version[i];
	पूर्ण
	enquiry3->cache_flush_पूर्णांकerval =
		inquiry->adapter_info.cache_flush_पूर्णांकerval;

	product_info->dram_size = inquiry->adapter_info.dram_size;

	enquiry3->num_ldrv = inquiry->logdrv_info.num_ldrv;

	क्रम (i = 0; i < MAX_LOGICAL_DRIVES_8LD; i++) अणु
		enquiry3->ldrv_size[i] = inquiry->logdrv_info.ldrv_size[i];
		enquiry3->ldrv_prop[i] = inquiry->logdrv_info.ldrv_prop[i];
		enquiry3->ldrv_state[i] = inquiry->logdrv_info.ldrv_state[i];
	पूर्ण

	क्रम (i = 0; i < (MAX_PHYSICAL_DRIVES); i++)
		enquiry3->pdrv_state[i] = inquiry->pdrv_info.pdrv_state[i];
पूर्ण

अटल अंतरभूत व्योम
mega_मुक्त_sgl(adapter_t *adapter)
अणु
	scb_t	*scb;
	पूर्णांक	i;

	क्रम(i = 0; i < adapter->max_cmds; i++) अणु

		scb = &adapter->scb_list[i];

		अगर( scb->sgl64 ) अणु
			dma_मुक्त_coherent(&adapter->dev->dev,
					  माप(mega_sgl64) * adapter->sglen,
					  scb->sgl64, scb->sgl_dma_addr);

			scb->sgl64 = शून्य;
		पूर्ण

		अगर( scb->pthru ) अणु
			dma_मुक्त_coherent(&adapter->dev->dev,
					  माप(mega_passthru), scb->pthru,
					  scb->pthru_dma_addr);

			scb->pthru = शून्य;
		पूर्ण

		अगर( scb->epthru ) अणु
			dma_मुक्त_coherent(&adapter->dev->dev,
					  माप(mega_ext_passthru),
					  scb->epthru, scb->epthru_dma_addr);

			scb->epthru = शून्य;
		पूर्ण

	पूर्ण
पूर्ण


/*
 * Get inक्रमmation about the card/driver
 */
स्थिर अक्षर *
megaraid_info(काष्ठा Scsi_Host *host)
अणु
	अटल अक्षर buffer[512];
	adapter_t *adapter;

	adapter = (adapter_t *)host->hostdata;

	प्र_लिखो (buffer,
		 "LSI Logic MegaRAID %s %d commands %d targs %d chans %d luns",
		 adapter->fw_version, adapter->product_info.max_commands,
		 adapter->host->max_id, adapter->host->max_channel,
		 (u32)adapter->host->max_lun);
	वापस buffer;
पूर्ण

/*
 * Abort a previous SCSI request. Only commands on the pending list can be
 * पातed. All the commands issued to the F/W must complete.
 */
अटल पूर्णांक
megaraid_पात(काष्ठा scsi_cmnd *cmd)
अणु
	adapter_t	*adapter;
	पूर्णांक		rval;

	adapter = (adapter_t *)cmd->device->host->hostdata;

	rval =  megaraid_पात_and_reset(adapter, cmd, SCB_ABORT);

	/*
	 * This is required here to complete any completed requests
	 * to be communicated over to the mid layer.
	 */
	mega_runकरोneq(adapter);

	वापस rval;
पूर्ण


अटल पूर्णांक
megaraid_reset(काष्ठा scsi_cmnd *cmd)
अणु
	adapter_t	*adapter;
	megacmd_t	mc;
	पूर्णांक		rval;

	adapter = (adapter_t *)cmd->device->host->hostdata;

#अगर MEGA_HAVE_CLUSTERING
	mc.cmd = MEGA_CLUSTER_CMD;
	mc.opcode = MEGA_RESET_RESERVATIONS;

	अगर( mega_पूर्णांकernal_command(adapter, &mc, शून्य) != 0 ) अणु
		dev_warn(&adapter->dev->dev, "reservation reset failed\n");
	पूर्ण
	अन्यथा अणु
		dev_info(&adapter->dev->dev, "reservation reset\n");
	पूर्ण
#पूर्ण_अगर

	spin_lock_irq(&adapter->lock);

	rval =  megaraid_पात_and_reset(adapter, cmd, SCB_RESET);

	/*
	 * This is required here to complete any completed requests
	 * to be communicated over to the mid layer.
	 */
	mega_runकरोneq(adapter);
	spin_unlock_irq(&adapter->lock);

	वापस rval;
पूर्ण

/**
 * megaraid_पात_and_reset()
 * @adapter: megaraid soft state
 * @cmd: scsi command to be पातed or reset
 * @aor: पात or reset flag
 *
 * Try to locate the scsi command in the pending queue. If found and is not
 * issued to the controller, पात/reset it. Otherwise वापस failure
 */
अटल पूर्णांक
megaraid_पात_and_reset(adapter_t *adapter, काष्ठा scsi_cmnd *cmd, पूर्णांक aor)
अणु
	काष्ठा list_head	*pos, *next;
	scb_t			*scb;

	dev_warn(&adapter->dev->dev, "%s cmd=%x <c=%d t=%d l=%d>\n",
	     (aor == SCB_ABORT)? "ABORTING":"RESET",
	     cmd->cmnd[0], cmd->device->channel,
	     cmd->device->id, (u32)cmd->device->lun);

	अगर(list_empty(&adapter->pending_list))
		वापस FAILED;

	list_क्रम_each_safe(pos, next, &adapter->pending_list) अणु

		scb = list_entry(pos, scb_t, list);

		अगर (scb->cmd == cmd) अणु /* Found command */

			scb->state |= aor;

			/*
			 * Check अगर this command has firmware ownership. If
			 * yes, we cannot reset this command. Whenever f/w
			 * completes this command, we will वापस appropriate
			 * status from ISR.
			 */
			अगर( scb->state & SCB_ISSUED ) अणु

				dev_warn(&adapter->dev->dev,
					"%s[%x], fw owner\n",
					(aor==SCB_ABORT) ? "ABORTING":"RESET",
					scb->idx);

				वापस FAILED;
			पूर्ण
			अन्यथा अणु

				/*
				 * Not yet issued! Remove from the pending
				 * list
				 */
				dev_warn(&adapter->dev->dev,
					"%s-[%x], driver owner\n",
					(aor==SCB_ABORT) ? "ABORTING":"RESET",
					scb->idx);

				mega_मुक्त_scb(adapter, scb);

				अगर( aor == SCB_ABORT ) अणु
					cmd->result = (DID_ABORT << 16);
				पूर्ण
				अन्यथा अणु
					cmd->result = (DID_RESET << 16);
				पूर्ण

				list_add_tail(SCSI_LIST(cmd),
						&adapter->completed_list);

				वापस SUCCESS;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस FAILED;
पूर्ण

अटल अंतरभूत पूर्णांक
make_local_pdev(adapter_t *adapter, काष्ठा pci_dev **pdev)
अणु
	*pdev = pci_alloc_dev(शून्य);

	अगर( *pdev == शून्य ) वापस -1;

	स_नकल(*pdev, adapter->dev, माप(काष्ठा pci_dev));

	अगर (dma_set_mask(&(*pdev)->dev, DMA_BIT_MASK(32)) != 0) अणु
		kमुक्त(*pdev);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम
मुक्त_local_pdev(काष्ठा pci_dev *pdev)
अणु
	kमुक्त(pdev);
पूर्ण

/**
 * mega_allocate_inquiry()
 * @dma_handle: handle वापसed क्रम dma address
 * @pdev: handle to pci device
 *
 * allocates memory क्रम inquiry काष्ठाure
 */
अटल अंतरभूत व्योम *
mega_allocate_inquiry(dma_addr_t *dma_handle, काष्ठा pci_dev *pdev)
अणु
	वापस dma_alloc_coherent(&pdev->dev, माप(mega_inquiry3),
				  dma_handle, GFP_KERNEL);
पूर्ण


अटल अंतरभूत व्योम
mega_मुक्त_inquiry(व्योम *inquiry, dma_addr_t dma_handle, काष्ठा pci_dev *pdev)
अणु
	dma_मुक्त_coherent(&pdev->dev, माप(mega_inquiry3), inquiry,
			  dma_handle);
पूर्ण


#अगर_घोषित CONFIG_PROC_FS
/* Following code handles /proc fs  */

/**
 * proc_show_config()
 * @m: Synthetic file स्थिरruction data
 * @v: File iterator
 *
 * Display configuration inक्रमmation about the controller.
 */
अटल पूर्णांक
proc_show_config(काष्ठा seq_file *m, व्योम *v)
अणु

	adapter_t *adapter = m->निजी;

	seq_माला_दो(m, MEGARAID_VERSION);
	अगर(adapter->product_info.product_name[0])
		seq_म_लिखो(m, "%s\n", adapter->product_info.product_name);

	seq_माला_दो(m, "Controller Type: ");

	अगर( adapter->flag & BOARD_MEMMAP )
		seq_माला_दो(m, "438/466/467/471/493/518/520/531/532\n");
	अन्यथा
		seq_माला_दो(m, "418/428/434\n");

	अगर(adapter->flag & BOARD_40LD)
		seq_माला_दो(m, "Controller Supports 40 Logical Drives\n");

	अगर(adapter->flag & BOARD_64BIT)
		seq_माला_दो(m, "Controller capable of 64-bit memory addressing\n");
	अगर( adapter->has_64bit_addr )
		seq_माला_दो(m, "Controller using 64-bit memory addressing\n");
	अन्यथा
		seq_माला_दो(m, "Controller is not using 64-bit memory addressing\n");

	seq_म_लिखो(m, "Base = %08lx, Irq = %d, ",
		   adapter->base, adapter->host->irq);

	seq_म_लिखो(m, "Logical Drives = %d, Channels = %d\n",
		   adapter->numldrv, adapter->product_info.nchannels);

	seq_म_लिखो(m, "Version =%s:%s, DRAM = %dMb\n",
		   adapter->fw_version, adapter->bios_version,
		   adapter->product_info.dram_size);

	seq_म_लिखो(m, "Controller Queue Depth = %d, Driver Queue Depth = %d\n",
		   adapter->product_info.max_commands, adapter->max_cmds);

	seq_म_लिखो(m, "support_ext_cdb    = %d\n", adapter->support_ext_cdb);
	seq_म_लिखो(m, "support_random_del = %d\n", adapter->support_अक्रमom_del);
	seq_म_लिखो(m, "boot_ldrv_enabled  = %d\n", adapter->boot_ldrv_enabled);
	seq_म_लिखो(m, "boot_ldrv          = %d\n", adapter->boot_ldrv);
	seq_म_लिखो(m, "boot_pdrv_enabled  = %d\n", adapter->boot_pdrv_enabled);
	seq_म_लिखो(m, "boot_pdrv_ch       = %d\n", adapter->boot_pdrv_ch);
	seq_म_लिखो(m, "boot_pdrv_tgt      = %d\n", adapter->boot_pdrv_tgt);
	seq_म_लिखो(m, "quiescent          = %d\n",
		   atomic_पढ़ो(&adapter->quiescent));
	seq_म_लिखो(m, "has_cluster        = %d\n", adapter->has_cluster);

	seq_माला_दो(m, "\nModule Parameters:\n");
	seq_म_लिखो(m, "max_cmd_per_lun    = %d\n", max_cmd_per_lun);
	seq_म_लिखो(m, "max_sectors_per_io = %d\n", max_sectors_per_io);
	वापस 0;
पूर्ण

/**
 * proc_show_stat()
 * @m: Synthetic file स्थिरruction data
 * @v: File iterator
 *
 * Display statistical inक्रमmation about the I/O activity.
 */
अटल पूर्णांक
proc_show_stat(काष्ठा seq_file *m, व्योम *v)
अणु
	adapter_t *adapter = m->निजी;
#अगर MEGA_HAVE_STATS
	पूर्णांक	i;
#पूर्ण_अगर

	seq_माला_दो(m, "Statistical Information for this controller\n");
	seq_म_लिखो(m, "pend_cmds = %d\n", atomic_पढ़ो(&adapter->pend_cmds));
#अगर MEGA_HAVE_STATS
	क्रम(i = 0; i < adapter->numldrv; i++) अणु
		seq_म_लिखो(m, "Logical Drive %d:\n", i);
		seq_म_लिखो(m, "\tReads Issued = %lu, Writes Issued = %lu\n",
			   adapter->nपढ़ोs[i], adapter->nग_लिखोs[i]);
		seq_म_लिखो(m, "\tSectors Read = %lu, Sectors Written = %lu\n",
			   adapter->nपढ़ोblocks[i], adapter->nग_लिखोblocks[i]);
		seq_म_लिखो(m, "\tRead errors = %lu, Write errors = %lu\n\n",
			   adapter->rd_errors[i], adapter->wr_errors[i]);
	पूर्ण
#अन्यथा
	seq_माला_दो(m, "IO and error counters not compiled in driver.\n");
#पूर्ण_अगर
	वापस 0;
पूर्ण


/**
 * proc_show_mbox()
 * @m: Synthetic file स्थिरruction data
 * @v: File iterator
 *
 * Display mailbox inक्रमmation क्रम the last command issued. This inक्रमmation
 * is good क्रम debugging.
 */
अटल पूर्णांक
proc_show_mbox(काष्ठा seq_file *m, व्योम *v)
अणु
	adapter_t	*adapter = m->निजी;
	अस्थिर mbox_t	*mbox = adapter->mbox;

	seq_माला_दो(m, "Contents of Mail Box Structure\n");
	seq_म_लिखो(m, "  Fw Command   = 0x%02x\n", mbox->m_out.cmd);
	seq_म_लिखो(m, "  Cmd Sequence = 0x%02x\n", mbox->m_out.cmdid);
	seq_म_लिखो(m, "  No of Sectors= %04d\n", mbox->m_out.numsectors);
	seq_म_लिखो(m, "  LBA          = 0x%02x\n", mbox->m_out.lba);
	seq_म_लिखो(m, "  DTA          = 0x%08x\n", mbox->m_out.xferaddr);
	seq_म_लिखो(m, "  Logical Drive= 0x%02x\n", mbox->m_out.logdrv);
	seq_म_लिखो(m, "  No of SG Elmt= 0x%02x\n", mbox->m_out.numsgelements);
	seq_म_लिखो(m, "  Busy         = %01x\n", mbox->m_in.busy);
	seq_म_लिखो(m, "  Status       = 0x%02x\n", mbox->m_in.status);
	वापस 0;
पूर्ण


/**
 * proc_show_rebuild_rate()
 * @m: Synthetic file स्थिरruction data
 * @v: File iterator
 *
 * Display current rebuild rate
 */
अटल पूर्णांक
proc_show_rebuild_rate(काष्ठा seq_file *m, व्योम *v)
अणु
	adapter_t	*adapter = m->निजी;
	dma_addr_t	dma_handle;
	caddr_t		inquiry;
	काष्ठा pci_dev	*pdev;

	अगर( make_local_pdev(adapter, &pdev) != 0 )
		वापस 0;

	अगर( (inquiry = mega_allocate_inquiry(&dma_handle, pdev)) == शून्य )
		जाओ मुक्त_pdev;

	अगर( mega_adapinq(adapter, dma_handle) != 0 ) अणु
		seq_माला_दो(m, "Adapter inquiry failed.\n");
		dev_warn(&adapter->dev->dev, "inquiry failed\n");
		जाओ मुक्त_inquiry;
	पूर्ण

	अगर( adapter->flag & BOARD_40LD )
		seq_म_लिखो(m, "Rebuild Rate: [%d%%]\n",
			   ((mega_inquiry3 *)inquiry)->rebuild_rate);
	अन्यथा
		seq_म_लिखो(m, "Rebuild Rate: [%d%%]\n",
			((mraid_ext_inquiry *)
			 inquiry)->raid_inq.adapter_info.rebuild_rate);

मुक्त_inquiry:
	mega_मुक्त_inquiry(inquiry, dma_handle, pdev);
मुक्त_pdev:
	मुक्त_local_pdev(pdev);
	वापस 0;
पूर्ण


/**
 * proc_show_battery()
 * @m: Synthetic file स्थिरruction data
 * @v: File iterator
 *
 * Display inक्रमmation about the battery module on the controller.
 */
अटल पूर्णांक
proc_show_battery(काष्ठा seq_file *m, व्योम *v)
अणु
	adapter_t	*adapter = m->निजी;
	dma_addr_t	dma_handle;
	caddr_t		inquiry;
	काष्ठा pci_dev	*pdev;
	u8	battery_status;

	अगर( make_local_pdev(adapter, &pdev) != 0 )
		वापस 0;

	अगर( (inquiry = mega_allocate_inquiry(&dma_handle, pdev)) == शून्य )
		जाओ मुक्त_pdev;

	अगर( mega_adapinq(adapter, dma_handle) != 0 ) अणु
		seq_माला_दो(m, "Adapter inquiry failed.\n");
		dev_warn(&adapter->dev->dev, "inquiry failed\n");
		जाओ मुक्त_inquiry;
	पूर्ण

	अगर( adapter->flag & BOARD_40LD ) अणु
		battery_status = ((mega_inquiry3 *)inquiry)->battery_status;
	पूर्ण
	अन्यथा अणु
		battery_status = ((mraid_ext_inquiry *)inquiry)->
			raid_inq.adapter_info.battery_status;
	पूर्ण

	/*
	 * Decode the battery status
	 */
	seq_म_लिखो(m, "Battery Status:[%d]", battery_status);

	अगर(battery_status == MEGA_BATT_CHARGE_DONE)
		seq_माला_दो(m, " Charge Done");

	अगर(battery_status & MEGA_BATT_MODULE_MISSING)
		seq_माला_दो(m, " Module Missing");
	
	अगर(battery_status & MEGA_BATT_LOW_VOLTAGE)
		seq_माला_दो(m, " Low Voltage");
	
	अगर(battery_status & MEGA_BATT_TEMP_HIGH)
		seq_माला_दो(m, " Temperature High");
	
	अगर(battery_status & MEGA_BATT_PACK_MISSING)
		seq_माला_दो(m, " Pack Missing");
	
	अगर(battery_status & MEGA_BATT_CHARGE_INPROG)
		seq_माला_दो(m, " Charge In-progress");
	
	अगर(battery_status & MEGA_BATT_CHARGE_FAIL)
		seq_माला_दो(m, " Charge Fail");
	
	अगर(battery_status & MEGA_BATT_CYCLES_EXCEEDED)
		seq_माला_दो(m, " Cycles Exceeded");

	seq_अ_दो(m, '\n');

मुक्त_inquiry:
	mega_मुक्त_inquiry(inquiry, dma_handle, pdev);
मुक्त_pdev:
	मुक्त_local_pdev(pdev);
	वापस 0;
पूर्ण


/*
 * Display scsi inquiry
 */
अटल व्योम
mega_prपूर्णांक_inquiry(काष्ठा seq_file *m, अक्षर *scsi_inq)
अणु
	पूर्णांक	i;

	seq_माला_दो(m, "  Vendor: ");
	seq_ग_लिखो(m, scsi_inq + 8, 8);
	seq_माला_दो(m, "  Model: ");
	seq_ग_लिखो(m, scsi_inq + 16, 16);
	seq_माला_दो(m, "  Rev: ");
	seq_ग_लिखो(m, scsi_inq + 32, 4);
	seq_अ_दो(m, '\n');

	i = scsi_inq[0] & 0x1f;
	seq_म_लिखो(m, "  Type:   %s ", scsi_device_type(i));

	seq_म_लिखो(m, "                 ANSI SCSI revision: %02x",
		   scsi_inq[2] & 0x07);

	अगर( (scsi_inq[2] & 0x07) == 1 && (scsi_inq[3] & 0x0f) == 1 )
		seq_माला_दो(m, " CCS\n");
	अन्यथा
		seq_अ_दो(m, '\n');
पूर्ण

/**
 * proc_show_pdrv()
 * @m: Synthetic file स्थिरruction data
 * @adapter: poपूर्णांकer to our soft state
 * @channel: channel
 *
 * Display inक्रमmation about the physical drives.
 */
अटल पूर्णांक
proc_show_pdrv(काष्ठा seq_file *m, adapter_t *adapter, पूर्णांक channel)
अणु
	dma_addr_t	dma_handle;
	अक्षर		*scsi_inq;
	dma_addr_t	scsi_inq_dma_handle;
	caddr_t		inquiry;
	काष्ठा pci_dev	*pdev;
	u8	*pdrv_state;
	u8	state;
	पूर्णांक	tgt;
	पूर्णांक	max_channels;
	पूर्णांक	i;

	अगर( make_local_pdev(adapter, &pdev) != 0 )
		वापस 0;

	अगर( (inquiry = mega_allocate_inquiry(&dma_handle, pdev)) == शून्य )
		जाओ मुक्त_pdev;

	अगर( mega_adapinq(adapter, dma_handle) != 0 ) अणु
		seq_माला_दो(m, "Adapter inquiry failed.\n");
		dev_warn(&adapter->dev->dev, "inquiry failed\n");
		जाओ मुक्त_inquiry;
	पूर्ण


	scsi_inq = dma_alloc_coherent(&pdev->dev, 256, &scsi_inq_dma_handle,
				      GFP_KERNEL);
	अगर( scsi_inq == शून्य ) अणु
		seq_माला_दो(m, "memory not available for scsi inq.\n");
		जाओ मुक्त_inquiry;
	पूर्ण

	अगर( adapter->flag & BOARD_40LD ) अणु
		pdrv_state = ((mega_inquiry3 *)inquiry)->pdrv_state;
	पूर्ण
	अन्यथा अणु
		pdrv_state = ((mraid_ext_inquiry *)inquiry)->
			raid_inq.pdrv_info.pdrv_state;
	पूर्ण

	max_channels = adapter->product_info.nchannels;

	अगर( channel >= max_channels ) अणु
		जाओ मुक्त_pci;
	पूर्ण

	क्रम( tgt = 0; tgt <= MAX_TARGET; tgt++ ) अणु

		i = channel*16 + tgt;

		state = *(pdrv_state + i);
		चयन( state & 0x0F ) अणु
		हाल PDRV_ONLINE:
			seq_म_लिखो(m, "Channel:%2d Id:%2d State: Online",
				   channel, tgt);
			अवरोध;

		हाल PDRV_FAILED:
			seq_म_लिखो(m, "Channel:%2d Id:%2d State: Failed",
				   channel, tgt);
			अवरोध;

		हाल PDRV_RBLD:
			seq_म_लिखो(m, "Channel:%2d Id:%2d State: Rebuild",
				   channel, tgt);
			अवरोध;

		हाल PDRV_HOTSPARE:
			seq_म_लिखो(m, "Channel:%2d Id:%2d State: Hot spare",
				   channel, tgt);
			अवरोध;

		शेष:
			seq_म_लिखो(m, "Channel:%2d Id:%2d State: Un-configured",
				   channel, tgt);
			अवरोध;
		पूर्ण

		/*
		 * This पूर्णांकerface displays inquiries क्रम disk drives
		 * only. Inquries क्रम logical drives and non-disk
		 * devices are available through /proc/scsi/scsi
		 */
		स_रखो(scsi_inq, 0, 256);
		अगर( mega_पूर्णांकernal_dev_inquiry(adapter, channel, tgt,
				scsi_inq_dma_handle) ||
				(scsi_inq[0] & 0x1F) != TYPE_DISK ) अणु
			जारी;
		पूर्ण

		/*
		 * Check क्रम overflow. We prपूर्णांक less than 240
		 * अक्षरacters क्रम inquiry
		 */
		seq_माला_दो(m, ".\n");
		mega_prपूर्णांक_inquiry(m, scsi_inq);
	पूर्ण

मुक्त_pci:
	dma_मुक्त_coherent(&pdev->dev, 256, scsi_inq, scsi_inq_dma_handle);
मुक्त_inquiry:
	mega_मुक्त_inquiry(inquiry, dma_handle, pdev);
मुक्त_pdev:
	मुक्त_local_pdev(pdev);
	वापस 0;
पूर्ण

/**
 * proc_show_pdrv_ch0()
 * @m: Synthetic file स्थिरruction data
 * @v: File iterator
 *
 * Display inक्रमmation about the physical drives on physical channel 0.
 */
अटल पूर्णांक
proc_show_pdrv_ch0(काष्ठा seq_file *m, व्योम *v)
अणु
	वापस proc_show_pdrv(m, m->निजी, 0);
पूर्ण


/**
 * proc_show_pdrv_ch1()
 * @m: Synthetic file स्थिरruction data
 * @v: File iterator
 *
 * Display inक्रमmation about the physical drives on physical channel 1.
 */
अटल पूर्णांक
proc_show_pdrv_ch1(काष्ठा seq_file *m, व्योम *v)
अणु
	वापस proc_show_pdrv(m, m->निजी, 1);
पूर्ण


/**
 * proc_show_pdrv_ch2()
 * @m: Synthetic file स्थिरruction data
 * @v: File iterator
 *
 * Display inक्रमmation about the physical drives on physical channel 2.
 */
अटल पूर्णांक
proc_show_pdrv_ch2(काष्ठा seq_file *m, व्योम *v)
अणु
	वापस proc_show_pdrv(m, m->निजी, 2);
पूर्ण


/**
 * proc_show_pdrv_ch3()
 * @m: Synthetic file स्थिरruction data
 * @v: File iterator
 *
 * Display inक्रमmation about the physical drives on physical channel 3.
 */
अटल पूर्णांक
proc_show_pdrv_ch3(काष्ठा seq_file *m, व्योम *v)
अणु
	वापस proc_show_pdrv(m, m->निजी, 3);
पूर्ण


/**
 * proc_show_rdrv()
 * @m: Synthetic file स्थिरruction data
 * @adapter: poपूर्णांकer to our soft state
 * @start: starting logical drive to display
 * @end: ending logical drive to display
 *
 * We करो not prपूर्णांक the inquiry inक्रमmation since its alपढ़ोy available through
 * /proc/scsi/scsi पूर्णांकerface
 */
अटल पूर्णांक
proc_show_rdrv(काष्ठा seq_file *m, adapter_t *adapter, पूर्णांक start, पूर्णांक end )
अणु
	dma_addr_t	dma_handle;
	logdrv_param	*lparam;
	megacmd_t	mc;
	अक्षर		*disk_array;
	dma_addr_t	disk_array_dma_handle;
	caddr_t		inquiry;
	काष्ठा pci_dev	*pdev;
	u8	*rdrv_state;
	पूर्णांक	num_ldrv;
	u32	array_sz;
	पूर्णांक	i;

	अगर( make_local_pdev(adapter, &pdev) != 0 )
		वापस 0;

	अगर( (inquiry = mega_allocate_inquiry(&dma_handle, pdev)) == शून्य )
		जाओ मुक्त_pdev;

	अगर( mega_adapinq(adapter, dma_handle) != 0 ) अणु
		seq_माला_दो(m, "Adapter inquiry failed.\n");
		dev_warn(&adapter->dev->dev, "inquiry failed\n");
		जाओ मुक्त_inquiry;
	पूर्ण

	स_रखो(&mc, 0, माप(megacmd_t));

	अगर( adapter->flag & BOARD_40LD ) अणु
		array_sz = माप(disk_array_40ld);

		rdrv_state = ((mega_inquiry3 *)inquiry)->ldrv_state;

		num_ldrv = ((mega_inquiry3 *)inquiry)->num_ldrv;
	पूर्ण
	अन्यथा अणु
		array_sz = माप(disk_array_8ld);

		rdrv_state = ((mraid_ext_inquiry *)inquiry)->
			raid_inq.logdrv_info.ldrv_state;

		num_ldrv = ((mraid_ext_inquiry *)inquiry)->
			raid_inq.logdrv_info.num_ldrv;
	पूर्ण

	disk_array = dma_alloc_coherent(&pdev->dev, array_sz,
					&disk_array_dma_handle, GFP_KERNEL);

	अगर( disk_array == शून्य ) अणु
		seq_माला_दो(m, "memory not available.\n");
		जाओ मुक्त_inquiry;
	पूर्ण

	mc.xferaddr = (u32)disk_array_dma_handle;

	अगर( adapter->flag & BOARD_40LD ) अणु
		mc.cmd = FC_NEW_CONFIG;
		mc.opcode = OP_DCMD_READ_CONFIG;

		अगर( mega_पूर्णांकernal_command(adapter, &mc, शून्य) ) अणु
			seq_माला_दो(m, "40LD read config failed.\n");
			जाओ मुक्त_pci;
		पूर्ण

	पूर्ण
	अन्यथा अणु
		mc.cmd = NEW_READ_CONFIG_8LD;

		अगर( mega_पूर्णांकernal_command(adapter, &mc, शून्य) ) अणु
			mc.cmd = READ_CONFIG_8LD;
			अगर( mega_पूर्णांकernal_command(adapter, &mc, शून्य) ) अणु
				seq_माला_दो(m, "8LD read config failed.\n");
				जाओ मुक्त_pci;
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम( i = start; i < ( (end+1 < num_ldrv) ? end+1 : num_ldrv ); i++ ) अणु

		अगर( adapter->flag & BOARD_40LD ) अणु
			lparam =
			&((disk_array_40ld *)disk_array)->ldrv[i].lparam;
		पूर्ण
		अन्यथा अणु
			lparam =
			&((disk_array_8ld *)disk_array)->ldrv[i].lparam;
		पूर्ण

		/*
		 * Check क्रम overflow. We prपूर्णांक less than 240 अक्षरacters क्रम
		 * inक्रमmation about each logical drive.
		 */
		seq_म_लिखो(m, "Logical drive:%2d:, ", i);

		चयन( rdrv_state[i] & 0x0F ) अणु
		हाल RDRV_OFFLINE:
			seq_माला_दो(m, "state: offline");
			अवरोध;
		हाल RDRV_DEGRADED:
			seq_माला_दो(m, "state: degraded");
			अवरोध;
		हाल RDRV_OPTIMAL:
			seq_माला_दो(m, "state: optimal");
			अवरोध;
		हाल RDRV_DELETED:
			seq_माला_दो(m, "state: deleted");
			अवरोध;
		शेष:
			seq_माला_दो(m, "state: unknown");
			अवरोध;
		पूर्ण

		/*
		 * Check अगर check consistency or initialization is going on
		 * क्रम this logical drive.
		 */
		अगर( (rdrv_state[i] & 0xF0) == 0x20 )
			seq_माला_दो(m, ", check-consistency in progress");
		अन्यथा अगर( (rdrv_state[i] & 0xF0) == 0x10 )
			seq_माला_दो(m, ", initialization in progress");
		
		seq_अ_दो(m, '\n');

		seq_म_लिखो(m, "Span depth:%3d, ", lparam->span_depth);
		seq_म_लिखो(m, "RAID level:%3d, ", lparam->level);
		seq_म_लिखो(m, "Stripe size:%3d, ",
			   lparam->stripe_sz ? lparam->stripe_sz/2: 128);
		seq_म_लिखो(m, "Row size:%3d\n", lparam->row_size);

		seq_माला_दो(m, "Read Policy: ");
		चयन(lparam->पढ़ो_ahead) अणु
		हाल NO_READ_AHEAD:
			seq_माला_दो(m, "No read ahead, ");
			अवरोध;
		हाल READ_AHEAD:
			seq_माला_दो(m, "Read ahead, ");
			अवरोध;
		हाल ADAP_READ_AHEAD:
			seq_माला_दो(m, "Adaptive, ");
			अवरोध;

		पूर्ण

		seq_माला_दो(m, "Write Policy: ");
		चयन(lparam->ग_लिखो_mode) अणु
		हाल WRMODE_WRITE_THRU:
			seq_माला_दो(m, "Write thru, ");
			अवरोध;
		हाल WRMODE_WRITE_BACK:
			seq_माला_दो(m, "Write back, ");
			अवरोध;
		पूर्ण

		seq_माला_दो(m, "Cache Policy: ");
		चयन(lparam->direct_io) अणु
		हाल CACHED_IO:
			seq_माला_दो(m, "Cached IO\n\n");
			अवरोध;
		हाल सूचीECT_IO:
			seq_माला_दो(m, "Direct IO\n\n");
			अवरोध;
		पूर्ण
	पूर्ण

मुक्त_pci:
	dma_मुक्त_coherent(&pdev->dev, array_sz, disk_array,
			  disk_array_dma_handle);
मुक्त_inquiry:
	mega_मुक्त_inquiry(inquiry, dma_handle, pdev);
मुक्त_pdev:
	मुक्त_local_pdev(pdev);
	वापस 0;
पूर्ण

/**
 * proc_show_rdrv_10()
 * @m: Synthetic file स्थिरruction data
 * @v: File iterator
 *
 * Display real समय inक्रमmation about the logical drives 0 through 9.
 */
अटल पूर्णांक
proc_show_rdrv_10(काष्ठा seq_file *m, व्योम *v)
अणु
	वापस proc_show_rdrv(m, m->निजी, 0, 9);
पूर्ण


/**
 * proc_show_rdrv_20()
 * @m: Synthetic file स्थिरruction data
 * @v: File iterator
 *
 * Display real समय inक्रमmation about the logical drives 0 through 9.
 */
अटल पूर्णांक
proc_show_rdrv_20(काष्ठा seq_file *m, व्योम *v)
अणु
	वापस proc_show_rdrv(m, m->निजी, 10, 19);
पूर्ण


/**
 * proc_show_rdrv_30()
 * @m: Synthetic file स्थिरruction data
 * @v: File iterator
 *
 * Display real समय inक्रमmation about the logical drives 0 through 9.
 */
अटल पूर्णांक
proc_show_rdrv_30(काष्ठा seq_file *m, व्योम *v)
अणु
	वापस proc_show_rdrv(m, m->निजी, 20, 29);
पूर्ण


/**
 * proc_show_rdrv_40()
 * @m: Synthetic file स्थिरruction data
 * @v: File iterator
 *
 * Display real समय inक्रमmation about the logical drives 0 through 9.
 */
अटल पूर्णांक
proc_show_rdrv_40(काष्ठा seq_file *m, व्योम *v)
अणु
	वापस proc_show_rdrv(m, m->निजी, 30, 39);
पूर्ण

/**
 * mega_create_proc_entry()
 * @index: index in soft state array
 * @parent: parent node क्रम this /proc entry
 *
 * Creates /proc entries क्रम our controllers.
 */
अटल व्योम
mega_create_proc_entry(पूर्णांक index, काष्ठा proc_dir_entry *parent)
अणु
	adapter_t *adapter = hba_soft_state[index];
	काष्ठा proc_dir_entry *dir;
	u8 string[16];

	प्र_लिखो(string, "hba%d", adapter->host->host_no);
	dir = proc_सूची_गढ़ो_data(string, 0, parent, adapter);
	अगर (!dir) अणु
		dev_warn(&adapter->dev->dev, "proc_mkdir failed\n");
		वापस;
	पूर्ण

	proc_create_single_data("config", S_IRUSR, dir,
			proc_show_config, adapter);
	proc_create_single_data("stat", S_IRUSR, dir,
			proc_show_stat, adapter);
	proc_create_single_data("mailbox", S_IRUSR, dir,
			proc_show_mbox, adapter);
#अगर MEGA_HAVE_ENH_PROC
	proc_create_single_data("rebuild-rate", S_IRUSR, dir,
			proc_show_rebuild_rate, adapter);
	proc_create_single_data("battery-status", S_IRUSR, dir,
			proc_show_battery, adapter);
	proc_create_single_data("diskdrives-ch0", S_IRUSR, dir,
			proc_show_pdrv_ch0, adapter);
	proc_create_single_data("diskdrives-ch1", S_IRUSR, dir,
			proc_show_pdrv_ch1, adapter);
	proc_create_single_data("diskdrives-ch2", S_IRUSR, dir,
			proc_show_pdrv_ch2, adapter);
	proc_create_single_data("diskdrives-ch3", S_IRUSR, dir,
			proc_show_pdrv_ch3, adapter);
	proc_create_single_data("raiddrives-0-9", S_IRUSR, dir,
			proc_show_rdrv_10, adapter);
	proc_create_single_data("raiddrives-10-19", S_IRUSR, dir,
			proc_show_rdrv_20, adapter);
	proc_create_single_data("raiddrives-20-29", S_IRUSR, dir,
			proc_show_rdrv_30, adapter);
	proc_create_single_data("raiddrives-30-39", S_IRUSR, dir,
			proc_show_rdrv_40, adapter);
#पूर्ण_अगर
पूर्ण

#अन्यथा
अटल अंतरभूत व्योम mega_create_proc_entry(पूर्णांक index, काष्ठा proc_dir_entry *parent)
अणु
पूर्ण
#पूर्ण_अगर


/*
 * megaraid_biosparam()
 *
 * Return the disk geometry क्रम a particular disk
 */
अटल पूर्णांक
megaraid_biosparam(काष्ठा scsi_device *sdev, काष्ठा block_device *bdev,
		    sector_t capacity, पूर्णांक geom[])
अणु
	adapter_t	*adapter;
	पूर्णांक	heads;
	पूर्णांक	sectors;
	पूर्णांक	cylinders;

	/* Get poपूर्णांकer to host config काष्ठाure */
	adapter = (adapter_t *)sdev->host->hostdata;

	अगर (IS_RAID_CH(adapter, sdev->channel)) अणु
			/* Default heads (64) & sectors (32) */
			heads = 64;
			sectors = 32;
			cylinders = (uदीर्घ)capacity / (heads * sectors);

			/*
			 * Handle extended translation size क्रम logical drives
			 * > 1Gb
			 */
			अगर ((uदीर्घ)capacity >= 0x200000) अणु
				heads = 255;
				sectors = 63;
				cylinders = (uदीर्घ)capacity / (heads * sectors);
			पूर्ण

			/* वापस result */
			geom[0] = heads;
			geom[1] = sectors;
			geom[2] = cylinders;
	पूर्ण
	अन्यथा अणु
		अगर (scsi_partsize(bdev, capacity, geom))
			वापस 0;

		dev_info(&adapter->dev->dev,
			 "invalid partition on this disk on channel %d\n",
			 sdev->channel);

		/* Default heads (64) & sectors (32) */
		heads = 64;
		sectors = 32;
		cylinders = (uदीर्घ)capacity / (heads * sectors);

		/* Handle extended translation size क्रम logical drives > 1Gb */
		अगर ((uदीर्घ)capacity >= 0x200000) अणु
			heads = 255;
			sectors = 63;
			cylinders = (uदीर्घ)capacity / (heads * sectors);
		पूर्ण

		/* वापस result */
		geom[0] = heads;
		geom[1] = sectors;
		geom[2] = cylinders;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * mega_init_scb()
 * @adapter: poपूर्णांकer to our soft state
 *
 * Allocate memory क्रम the various poपूर्णांकers in the scb काष्ठाures:
 * scatter-gather list poपूर्णांकer, passthru and extended passthru काष्ठाure
 * poपूर्णांकers.
 */
अटल पूर्णांक
mega_init_scb(adapter_t *adapter)
अणु
	scb_t	*scb;
	पूर्णांक	i;

	क्रम( i = 0; i < adapter->max_cmds; i++ ) अणु

		scb = &adapter->scb_list[i];

		scb->sgl64 = शून्य;
		scb->sgl = शून्य;
		scb->pthru = शून्य;
		scb->epthru = शून्य;
	पूर्ण

	क्रम( i = 0; i < adapter->max_cmds; i++ ) अणु

		scb = &adapter->scb_list[i];

		scb->idx = i;

		scb->sgl64 = dma_alloc_coherent(&adapter->dev->dev,
						माप(mega_sgl64) * adapter->sglen,
						&scb->sgl_dma_addr, GFP_KERNEL);

		scb->sgl = (mega_sglist *)scb->sgl64;

		अगर( !scb->sgl ) अणु
			dev_warn(&adapter->dev->dev, "RAID: Can't allocate sglist\n");
			mega_मुक्त_sgl(adapter);
			वापस -1;
		पूर्ण

		scb->pthru = dma_alloc_coherent(&adapter->dev->dev,
						माप(mega_passthru),
						&scb->pthru_dma_addr, GFP_KERNEL);

		अगर( !scb->pthru ) अणु
			dev_warn(&adapter->dev->dev, "RAID: Can't allocate passthru\n");
			mega_मुक्त_sgl(adapter);
			वापस -1;
		पूर्ण

		scb->epthru = dma_alloc_coherent(&adapter->dev->dev,
						 माप(mega_ext_passthru),
						 &scb->epthru_dma_addr, GFP_KERNEL);

		अगर( !scb->epthru ) अणु
			dev_warn(&adapter->dev->dev,
				"Can't allocate extended passthru\n");
			mega_मुक्त_sgl(adapter);
			वापस -1;
		पूर्ण


		scb->dma_type = MEGA_DMA_TYPE_NONE;

		/*
		 * Link to मुक्त list
		 * lock not required since we are loading the driver, so no
		 * commands possible right now.
		 */
		scb->state = SCB_FREE;
		scb->cmd = शून्य;
		list_add(&scb->list, &adapter->मुक्त_list);
	पूर्ण

	वापस 0;
पूर्ण


/**
 * megadev_खोलो()
 * @inode: unused
 * @filep: unused
 *
 * Routines क्रम the अक्षरacter/ioctl पूर्णांकerface to the driver. Find out अगर this
 * is a valid खोलो. 
 */
अटल पूर्णांक
megadev_खोलो (काष्ठा inode *inode, काष्ठा file *filep)
अणु
	/*
	 * Only allow superuser to access निजी ioctl पूर्णांकerface
	 */
	अगर( !capable(CAP_SYS_ADMIN) ) वापस -EACCES;

	वापस 0;
पूर्ण


/**
 * megadev_ioctl()
 * @filep: Our device file
 * @cmd: ioctl command
 * @arg: user buffer
 *
 * ioctl entry poपूर्णांक क्रम our निजी ioctl पूर्णांकerface. We move the data in from
 * the user space, prepare the command (अगर necessary, convert the old MIMD
 * ioctl to new ioctl command), and issue a synchronous command to the
 * controller.
 */
अटल पूर्णांक
megadev_ioctl(काष्ठा file *filep, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	adapter_t	*adapter;
	nitioctl_t	uioc;
	पूर्णांक		adapno;
	पूर्णांक		rval;
	mega_passthru	__user *upthru;	/* user address क्रम passthru */
	mega_passthru	*pthru;		/* copy user passthru here */
	dma_addr_t	pthru_dma_hndl;
	व्योम		*data = शून्य;	/* data to be transferred */
	dma_addr_t	data_dma_hndl;	/* dma handle क्रम data xfer area */
	megacmd_t	mc;
#अगर MEGA_HAVE_STATS
	megastat_t	__user *ustats = शून्य;
	पूर्णांक		num_ldrv = 0;
#पूर्ण_अगर
	u32		uxferaddr = 0;
	काष्ठा pci_dev	*pdev;

	/*
	 * Make sure only USCSICMD are issued through this पूर्णांकerface.
	 * MIMD application would still fire dअगरferent command.
	 */
	अगर( (_IOC_TYPE(cmd) != MEGAIOC_MAGIC) && (cmd != USCSICMD) ) अणु
		वापस -EINVAL;
	पूर्ण

	/*
	 * Check and convert a possible MIMD command to NIT command.
	 * mega_m_to_n() copies the data from the user space, so we करो not
	 * have to करो it here.
	 * NOTE: We will need some user address to copyout the data, thereक्रमe
	 * the पूर्णांकeface layer will also provide us with the required user
	 * addresses.
	 */
	स_रखो(&uioc, 0, माप(nitioctl_t));
	अगर( (rval = mega_m_to_n( (व्योम __user *)arg, &uioc)) != 0 )
		वापस rval;


	चयन( uioc.opcode ) अणु

	हाल GET_DRIVER_VER:
		अगर( put_user(driver_ver, (u32 __user *)uioc.uioc_uaddr) )
			वापस (-EFAULT);

		अवरोध;

	हाल GET_N_ADAP:
		अगर( put_user(hba_count, (u32 __user *)uioc.uioc_uaddr) )
			वापस (-EFAULT);

		/*
		 * Shucks. MIMD पूर्णांकerface वापसs a positive value क्रम number
		 * of adapters. TODO: Change it to वापस 0 when there is no
		 * applicatio using mimd पूर्णांकerface.
		 */
		वापस hba_count;

	हाल GET_ADAP_INFO:

		/*
		 * Which adapter
		 */
		अगर( (adapno = GETADAP(uioc.adapno)) >= hba_count )
			वापस (-ENODEV);

		अगर( copy_to_user(uioc.uioc_uaddr, mcontroller+adapno,
				माप(काष्ठा mcontroller)) )
			वापस (-EFAULT);
		अवरोध;

#अगर MEGA_HAVE_STATS

	हाल GET_STATS:
		/*
		 * Which adapter
		 */
		अगर( (adapno = GETADAP(uioc.adapno)) >= hba_count )
			वापस (-ENODEV);

		adapter = hba_soft_state[adapno];

		ustats = uioc.uioc_uaddr;

		अगर( copy_from_user(&num_ldrv, &ustats->num_ldrv, माप(पूर्णांक)) )
			वापस (-EFAULT);

		/*
		 * Check क्रम the validity of the logical drive number
		 */
		अगर( num_ldrv >= MAX_LOGICAL_DRIVES_40LD ) वापस -EINVAL;

		अगर( copy_to_user(ustats->nपढ़ोs, adapter->nपढ़ोs,
					num_ldrv*माप(u32)) )
			वापस -EFAULT;

		अगर( copy_to_user(ustats->nपढ़ोblocks, adapter->nपढ़ोblocks,
					num_ldrv*माप(u32)) )
			वापस -EFAULT;

		अगर( copy_to_user(ustats->nग_लिखोs, adapter->nग_लिखोs,
					num_ldrv*माप(u32)) )
			वापस -EFAULT;

		अगर( copy_to_user(ustats->nग_लिखोblocks, adapter->nग_लिखोblocks,
					num_ldrv*माप(u32)) )
			वापस -EFAULT;

		अगर( copy_to_user(ustats->rd_errors, adapter->rd_errors,
					num_ldrv*माप(u32)) )
			वापस -EFAULT;

		अगर( copy_to_user(ustats->wr_errors, adapter->wr_errors,
					num_ldrv*माप(u32)) )
			वापस -EFAULT;

		वापस 0;

#पूर्ण_अगर
	हाल MBOX_CMD:

		/*
		 * Which adapter
		 */
		अगर( (adapno = GETADAP(uioc.adapno)) >= hba_count )
			वापस (-ENODEV);

		adapter = hba_soft_state[adapno];

		/*
		 * Deletion of logical drive is a special हाल. The adapter
		 * should be quiescent beक्रमe this command is issued.
		 */
		अगर( uioc.uioc_rmbox[0] == FC_DEL_LOGDRV &&
				uioc.uioc_rmbox[2] == OP_DEL_LOGDRV ) अणु

			/*
			 * Do we support this feature
			 */
			अगर( !adapter->support_अक्रमom_del ) अणु
				dev_warn(&adapter->dev->dev, "logdrv "
					"delete on non-supporting F/W\n");

				वापस (-EINVAL);
			पूर्ण

			rval = mega_del_logdrv( adapter, uioc.uioc_rmbox[3] );

			अगर( rval == 0 ) अणु
				स_रखो(&mc, 0, माप(megacmd_t));

				mc.status = rval;

				rval = mega_n_to_m((व्योम __user *)arg, &mc);
			पूर्ण

			वापस rval;
		पूर्ण
		/*
		 * This पूर्णांकerface only support the regular passthru commands.
		 * Reject extended passthru and 64-bit passthru
		 */
		अगर( uioc.uioc_rmbox[0] == MEGA_MBOXCMD_PASSTHRU64 ||
			uioc.uioc_rmbox[0] == MEGA_MBOXCMD_EXTPTHRU ) अणु

			dev_warn(&adapter->dev->dev, "rejected passthru\n");

			वापस (-EINVAL);
		पूर्ण

		/*
		 * For all पूर्णांकernal commands, the buffer must be allocated in
		 * <4GB address range
		 */
		अगर( make_local_pdev(adapter, &pdev) != 0 )
			वापस -EIO;

		/* Is it a passthru command or a DCMD */
		अगर( uioc.uioc_rmbox[0] == MEGA_MBOXCMD_PASSTHRU ) अणु
			/* Passthru commands */

			pthru = dma_alloc_coherent(&pdev->dev,
						   माप(mega_passthru),
						   &pthru_dma_hndl, GFP_KERNEL);

			अगर( pthru == शून्य ) अणु
				मुक्त_local_pdev(pdev);
				वापस (-ENOMEM);
			पूर्ण

			/*
			 * The user passthru काष्ठाure
			 */
			upthru = (mega_passthru __user *)(अचिन्हित दीर्घ)MBOX(uioc)->xferaddr;

			/*
			 * Copy in the user passthru here.
			 */
			अगर( copy_from_user(pthru, upthru,
						माप(mega_passthru)) ) अणु

				dma_मुक्त_coherent(&pdev->dev,
						  माप(mega_passthru),
						  pthru, pthru_dma_hndl);

				मुक्त_local_pdev(pdev);

				वापस (-EFAULT);
			पूर्ण

			/*
			 * Is there a data transfer
			 */
			अगर( pthru->dataxferlen ) अणु
				data = dma_alloc_coherent(&pdev->dev,
							  pthru->dataxferlen,
							  &data_dma_hndl,
							  GFP_KERNEL);

				अगर( data == शून्य ) अणु
					dma_मुक्त_coherent(&pdev->dev,
							  माप(mega_passthru),
							  pthru,
							  pthru_dma_hndl);

					मुक्त_local_pdev(pdev);

					वापस (-ENOMEM);
				पूर्ण

				/*
				 * Save the user address and poपूर्णांक the kernel
				 * address at just allocated memory
				 */
				uxferaddr = pthru->dataxferaddr;
				pthru->dataxferaddr = data_dma_hndl;
			पूर्ण


			/*
			 * Is data coming करोwn-stream
			 */
			अगर( pthru->dataxferlen && (uioc.flags & UIOC_WR) ) अणु
				/*
				 * Get the user data
				 */
				अगर( copy_from_user(data, (अक्षर __user *)(अचिन्हित दीर्घ) uxferaddr,
							pthru->dataxferlen) ) अणु
					rval = (-EFAULT);
					जाओ मुक्तmem_and_वापस;
				पूर्ण
			पूर्ण

			स_रखो(&mc, 0, माप(megacmd_t));

			mc.cmd = MEGA_MBOXCMD_PASSTHRU;
			mc.xferaddr = (u32)pthru_dma_hndl;

			/*
			 * Issue the command
			 */
			mega_पूर्णांकernal_command(adapter, &mc, pthru);

			rval = mega_n_to_m((व्योम __user *)arg, &mc);

			अगर( rval ) जाओ मुक्तmem_and_वापस;


			/*
			 * Is data going up-stream
			 */
			अगर( pthru->dataxferlen && (uioc.flags & UIOC_RD) ) अणु
				अगर( copy_to_user((अक्षर __user *)(अचिन्हित दीर्घ) uxferaddr, data,
							pthru->dataxferlen) ) अणु
					rval = (-EFAULT);
				पूर्ण
			पूर्ण

			/*
			 * Send the request sense data also, irrespective of
			 * whether the user has asked क्रम it or not.
			 */
			अगर (copy_to_user(upthru->reqsensearea,
					pthru->reqsensearea, 14))
				rval = -EFAULT;

मुक्तmem_and_वापस:
			अगर( pthru->dataxferlen ) अणु
				dma_मुक्त_coherent(&pdev->dev,
						  pthru->dataxferlen, data,
						  data_dma_hndl);
			पूर्ण

			dma_मुक्त_coherent(&pdev->dev, माप(mega_passthru),
					  pthru, pthru_dma_hndl);

			मुक्त_local_pdev(pdev);

			वापस rval;
		पूर्ण
		अन्यथा अणु
			/* DCMD commands */

			/*
			 * Is there a data transfer
			 */
			अगर( uioc.xferlen ) अणु
				data = dma_alloc_coherent(&pdev->dev,
							  uioc.xferlen,
							  &data_dma_hndl,
							  GFP_KERNEL);

				अगर( data == शून्य ) अणु
					मुक्त_local_pdev(pdev);
					वापस (-ENOMEM);
				पूर्ण

				uxferaddr = MBOX(uioc)->xferaddr;
			पूर्ण

			/*
			 * Is data coming करोwn-stream
			 */
			अगर( uioc.xferlen && (uioc.flags & UIOC_WR) ) अणु
				/*
				 * Get the user data
				 */
				अगर( copy_from_user(data, (अक्षर __user *)(अचिन्हित दीर्घ) uxferaddr,
							uioc.xferlen) ) अणु

					dma_मुक्त_coherent(&pdev->dev,
							  uioc.xferlen, data,
							  data_dma_hndl);

					मुक्त_local_pdev(pdev);

					वापस (-EFAULT);
				पूर्ण
			पूर्ण

			स_नकल(&mc, MBOX(uioc), माप(megacmd_t));

			mc.xferaddr = (u32)data_dma_hndl;

			/*
			 * Issue the command
			 */
			mega_पूर्णांकernal_command(adapter, &mc, शून्य);

			rval = mega_n_to_m((व्योम __user *)arg, &mc);

			अगर( rval ) अणु
				अगर( uioc.xferlen ) अणु
					dma_मुक्त_coherent(&pdev->dev,
							  uioc.xferlen, data,
							  data_dma_hndl);
				पूर्ण

				मुक्त_local_pdev(pdev);

				वापस rval;
			पूर्ण

			/*
			 * Is data going up-stream
			 */
			अगर( uioc.xferlen && (uioc.flags & UIOC_RD) ) अणु
				अगर( copy_to_user((अक्षर __user *)(अचिन्हित दीर्घ) uxferaddr, data,
							uioc.xferlen) ) अणु

					rval = (-EFAULT);
				पूर्ण
			पूर्ण

			अगर( uioc.xferlen ) अणु
				dma_मुक्त_coherent(&pdev->dev, uioc.xferlen,
						  data, data_dma_hndl);
			पूर्ण

			मुक्त_local_pdev(pdev);

			वापस rval;
		पूर्ण

	शेष:
		वापस (-EINVAL);
	पूर्ण

	वापस 0;
पूर्ण

अटल दीर्घ
megadev_unlocked_ioctl(काष्ठा file *filep, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	पूर्णांक ret;

	mutex_lock(&megadev_mutex);
	ret = megadev_ioctl(filep, cmd, arg);
	mutex_unlock(&megadev_mutex);

	वापस ret;
पूर्ण

/**
 * mega_m_to_n()
 * @arg: user address
 * @uioc: new ioctl काष्ठाure
 *
 * A thin layer to convert older mimd पूर्णांकerface ioctl काष्ठाure to NIT ioctl
 * काष्ठाure
 *
 * Converts the older mimd ioctl काष्ठाure to newer NIT काष्ठाure
 */
अटल पूर्णांक
mega_m_to_n(व्योम __user *arg, nitioctl_t *uioc)
अणु
	काष्ठा uioctl_t	uioc_mimd;
	अक्षर	signature[8] = अणु0पूर्ण;
	u8	opcode;
	u8	subopcode;


	/*
	 * check is the application conक्रमms to NIT. We करो not have to करो much
	 * in that हाल.
	 * We exploit the fact that the signature is stored in the very
	 * beginning of the काष्ठाure.
	 */

	अगर( copy_from_user(signature, arg, 7) )
		वापस (-EFAULT);

	अगर( स_भेद(signature, "MEGANIT", 7) == 0 ) अणु

		/*
		 * NOTE NOTE: The nit ioctl is still under flux because of
		 * change of mailbox definition, in HPE. No applications yet
		 * use this पूर्णांकerface and let's not have applications use this
		 * पूर्णांकerface till the new specअगरitions are in place.
		 */
		वापस -EINVAL;
#अगर 0
		अगर( copy_from_user(uioc, arg, माप(nitioctl_t)) )
			वापस (-EFAULT);
		वापस 0;
#पूर्ण_अगर
	पूर्ण

	/*
	 * Else assume we have mimd uioctl_t as arg. Convert to nitioctl_t
	 *
	 * Get the user ioctl काष्ठाure
	 */
	अगर( copy_from_user(&uioc_mimd, arg, माप(काष्ठा uioctl_t)) )
		वापस (-EFAULT);


	/*
	 * Get the opcode and subopcode क्रम the commands
	 */
	opcode = uioc_mimd.ui.fcs.opcode;
	subopcode = uioc_mimd.ui.fcs.subopcode;

	चयन (opcode) अणु
	हाल 0x82:

		चयन (subopcode) अणु

		हाल MEGAIOC_QDRVRVER:	/* Query driver version */
			uioc->opcode = GET_DRIVER_VER;
			uioc->uioc_uaddr = uioc_mimd.data;
			अवरोध;

		हाल MEGAIOC_QNADAP:	/* Get # of adapters */
			uioc->opcode = GET_N_ADAP;
			uioc->uioc_uaddr = uioc_mimd.data;
			अवरोध;

		हाल MEGAIOC_QADAPINFO:	/* Get adapter inक्रमmation */
			uioc->opcode = GET_ADAP_INFO;
			uioc->adapno = uioc_mimd.ui.fcs.adapno;
			uioc->uioc_uaddr = uioc_mimd.data;
			अवरोध;

		शेष:
			वापस(-EINVAL);
		पूर्ण

		अवरोध;


	हाल 0x81:

		uioc->opcode = MBOX_CMD;
		uioc->adapno = uioc_mimd.ui.fcs.adapno;

		स_नकल(uioc->uioc_rmbox, uioc_mimd.mbox, 18);

		uioc->xferlen = uioc_mimd.ui.fcs.length;

		अगर( uioc_mimd.outlen ) uioc->flags = UIOC_RD;
		अगर( uioc_mimd.inlen ) uioc->flags |= UIOC_WR;

		अवरोध;

	हाल 0x80:

		uioc->opcode = MBOX_CMD;
		uioc->adapno = uioc_mimd.ui.fcs.adapno;

		स_नकल(uioc->uioc_rmbox, uioc_mimd.mbox, 18);

		/*
		 * Choose the xferlen bigger of input and output data
		 */
		uioc->xferlen = uioc_mimd.outlen > uioc_mimd.inlen ?
			uioc_mimd.outlen : uioc_mimd.inlen;

		अगर( uioc_mimd.outlen ) uioc->flags = UIOC_RD;
		अगर( uioc_mimd.inlen ) uioc->flags |= UIOC_WR;

		अवरोध;

	शेष:
		वापस (-EINVAL);

	पूर्ण

	वापस 0;
पूर्ण

/*
 * mega_n_to_m()
 * @arg: user address
 * @mc: mailbox command
 *
 * Updates the status inक्रमmation to the application, depending on application
 * conक्रमms to older mimd ioctl पूर्णांकerface or newer NIT ioctl पूर्णांकerface
 */
अटल पूर्णांक
mega_n_to_m(व्योम __user *arg, megacmd_t *mc)
अणु
	nitioctl_t	__user *uiocp;
	megacmd_t	__user *umc;
	mega_passthru	__user *upthru;
	काष्ठा uioctl_t	__user *uioc_mimd;
	अक्षर	signature[8] = अणु0पूर्ण;

	/*
	 * check is the application conक्रमms to NIT.
	 */
	अगर( copy_from_user(signature, arg, 7) )
		वापस -EFAULT;

	अगर( स_भेद(signature, "MEGANIT", 7) == 0 ) अणु

		uiocp = arg;

		अगर( put_user(mc->status, (u8 __user *)&MBOX_P(uiocp)->status) )
			वापस (-EFAULT);

		अगर( mc->cmd == MEGA_MBOXCMD_PASSTHRU ) अणु

			umc = MBOX_P(uiocp);

			अगर (get_user(upthru, (mega_passthru __user * __user *)&umc->xferaddr))
				वापस -EFAULT;

			अगर( put_user(mc->status, (u8 __user *)&upthru->scsistatus))
				वापस (-EFAULT);
		पूर्ण
	पूर्ण
	अन्यथा अणु
		uioc_mimd = arg;

		अगर( put_user(mc->status, (u8 __user *)&uioc_mimd->mbox[17]) )
			वापस (-EFAULT);

		अगर( mc->cmd == MEGA_MBOXCMD_PASSTHRU ) अणु

			umc = (megacmd_t __user *)uioc_mimd->mbox;

			अगर (get_user(upthru, (mega_passthru __user * __user *)&umc->xferaddr))
				वापस (-EFAULT);

			अगर( put_user(mc->status, (u8 __user *)&upthru->scsistatus) )
				वापस (-EFAULT);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण


/*
 * MEGARAID 'FW' commands.
 */

/**
 * mega_is_bios_enabled()
 * @adapter: poपूर्णांकer to our soft state
 *
 * issue command to find out अगर the BIOS is enabled क्रम this controller
 */
अटल पूर्णांक
mega_is_bios_enabled(adapter_t *adapter)
अणु
	अचिन्हित अक्षर	raw_mbox[माप(काष्ठा mbox_out)];
	mbox_t	*mbox;

	mbox = (mbox_t *)raw_mbox;

	स_रखो(&mbox->m_out, 0, माप(raw_mbox));

	स_रखो((व्योम *)adapter->mega_buffer, 0, MEGA_BUFFER_SIZE);

	mbox->m_out.xferaddr = (u32)adapter->buf_dma_handle;

	raw_mbox[0] = IS_BIOS_ENABLED;
	raw_mbox[2] = GET_BIOS;

	issue_scb_block(adapter, raw_mbox);

	वापस *(अक्षर *)adapter->mega_buffer;
पूर्ण


/**
 * mega_क्रमागत_raid_scsi()
 * @adapter: poपूर्णांकer to our soft state
 *
 * Find out what channels are RAID/SCSI. This inक्रमmation is used to
 * dअगरferentiate the भव channels and physical channels and to support
 * ROMB feature and non-disk devices.
 */
अटल व्योम
mega_क्रमागत_raid_scsi(adapter_t *adapter)
अणु
	अचिन्हित अक्षर raw_mbox[माप(काष्ठा mbox_out)];
	mbox_t *mbox;
	पूर्णांक i;

	mbox = (mbox_t *)raw_mbox;

	स_रखो(&mbox->m_out, 0, माप(raw_mbox));

	/*
	 * issue command to find out what channels are raid/scsi
	 */
	raw_mbox[0] = CHNL_CLASS;
	raw_mbox[2] = GET_CHNL_CLASS;

	स_रखो((व्योम *)adapter->mega_buffer, 0, MEGA_BUFFER_SIZE);

	mbox->m_out.xferaddr = (u32)adapter->buf_dma_handle;

	/*
	 * Non-ROMB firmware fail this command, so all channels
	 * must be shown RAID
	 */
	adapter->mega_ch_class = 0xFF;

	अगर(!issue_scb_block(adapter, raw_mbox)) अणु
		adapter->mega_ch_class = *((अक्षर *)adapter->mega_buffer);

	पूर्ण

	क्रम( i = 0; i < adapter->product_info.nchannels; i++ ) अणु 
		अगर( (adapter->mega_ch_class >> i) & 0x01 ) अणु
			dev_info(&adapter->dev->dev, "channel[%d] is raid\n",
					i);
		पूर्ण
		अन्यथा अणु
			dev_info(&adapter->dev->dev, "channel[%d] is scsi\n",
					i);
		पूर्ण
	पूर्ण

	वापस;
पूर्ण


/**
 * mega_get_boot_drv()
 * @adapter: poपूर्णांकer to our soft state
 *
 * Find out which device is the boot device. Note, any logical drive or any
 * phyical device (e.g., a CDROM) can be designated as a boot device.
 */
अटल व्योम
mega_get_boot_drv(adapter_t *adapter)
अणु
	काष्ठा निजी_bios_data	*prv_bios_data;
	अचिन्हित अक्षर	raw_mbox[माप(काष्ठा mbox_out)];
	mbox_t	*mbox;
	u16	cksum = 0;
	u8	*cksum_p;
	u8	boot_pdrv;
	पूर्णांक	i;

	mbox = (mbox_t *)raw_mbox;

	स_रखो(&mbox->m_out, 0, माप(raw_mbox));

	raw_mbox[0] = BIOS_PVT_DATA;
	raw_mbox[2] = GET_BIOS_PVT_DATA;

	स_रखो((व्योम *)adapter->mega_buffer, 0, MEGA_BUFFER_SIZE);

	mbox->m_out.xferaddr = (u32)adapter->buf_dma_handle;

	adapter->boot_ldrv_enabled = 0;
	adapter->boot_ldrv = 0;

	adapter->boot_pdrv_enabled = 0;
	adapter->boot_pdrv_ch = 0;
	adapter->boot_pdrv_tgt = 0;

	अगर(issue_scb_block(adapter, raw_mbox) == 0) अणु
		prv_bios_data =
			(काष्ठा निजी_bios_data *)adapter->mega_buffer;

		cksum = 0;
		cksum_p = (अक्षर *)prv_bios_data;
		क्रम (i = 0; i < 14; i++ ) अणु
			cksum += (u16)(*cksum_p++);
		पूर्ण

		अगर (prv_bios_data->cksum == (u16)(0-cksum) ) अणु

			/*
			 * If MSB is set, a physical drive is set as boot
			 * device
			 */
			अगर( prv_bios_data->boot_drv & 0x80 ) अणु
				adapter->boot_pdrv_enabled = 1;
				boot_pdrv = prv_bios_data->boot_drv & 0x7F;
				adapter->boot_pdrv_ch = boot_pdrv / 16;
				adapter->boot_pdrv_tgt = boot_pdrv % 16;
			पूर्ण
			अन्यथा अणु
				adapter->boot_ldrv_enabled = 1;
				adapter->boot_ldrv = prv_bios_data->boot_drv;
			पूर्ण
		पूर्ण
	पूर्ण

पूर्ण

/**
 * mega_support_अक्रमom_del()
 * @adapter: poपूर्णांकer to our soft state
 *
 * Find out अगर this controller supports अक्रमom deletion and addition of
 * logical drives
 */
अटल पूर्णांक
mega_support_अक्रमom_del(adapter_t *adapter)
अणु
	अचिन्हित अक्षर raw_mbox[माप(काष्ठा mbox_out)];
	mbox_t *mbox;
	पूर्णांक rval;

	mbox = (mbox_t *)raw_mbox;

	स_रखो(&mbox->m_out, 0, माप(raw_mbox));

	/*
	 * issue command
	 */
	raw_mbox[0] = FC_DEL_LOGDRV;
	raw_mbox[2] = OP_SUP_DEL_LOGDRV;

	rval = issue_scb_block(adapter, raw_mbox);

	वापस !rval;
पूर्ण


/**
 * mega_support_ext_cdb()
 * @adapter: poपूर्णांकer to our soft state
 *
 * Find out अगर this firmware support cdblen > 10
 */
अटल पूर्णांक
mega_support_ext_cdb(adapter_t *adapter)
अणु
	अचिन्हित अक्षर raw_mbox[माप(काष्ठा mbox_out)];
	mbox_t *mbox;
	पूर्णांक rval;

	mbox = (mbox_t *)raw_mbox;

	स_रखो(&mbox->m_out, 0, माप(raw_mbox));
	/*
	 * issue command to find out अगर controller supports extended CDBs.
	 */
	raw_mbox[0] = 0xA4;
	raw_mbox[2] = 0x16;

	rval = issue_scb_block(adapter, raw_mbox);

	वापस !rval;
पूर्ण


/**
 * mega_del_logdrv()
 * @adapter: poपूर्णांकer to our soft state
 * @logdrv: logical drive to be deleted
 *
 * Delete the specअगरied logical drive. It is the responsibility of the user
 * app to let the OS know about this operation.
 */
अटल पूर्णांक
mega_del_logdrv(adapter_t *adapter, पूर्णांक logdrv)
अणु
	अचिन्हित दीर्घ flags;
	scb_t *scb;
	पूर्णांक rval;

	/*
	 * Stop sending commands to the controller, queue them पूर्णांकernally.
	 * When deletion is complete, ISR will flush the queue.
	 */
	atomic_set(&adapter->quiescent, 1);

	/*
	 * Wait till all the issued commands are complete and there are no
	 * commands in the pending queue
	 */
	जबतक (atomic_पढ़ो(&adapter->pend_cmds) > 0 ||
	       !list_empty(&adapter->pending_list))
		msleep(1000);	/* sleep क्रम 1s */

	rval = mega_करो_del_logdrv(adapter, logdrv);

	spin_lock_irqsave(&adapter->lock, flags);

	/*
	 * If delete operation was successful, add 0x80 to the logical drive
	 * ids क्रम commands in the pending queue.
	 */
	अगर (adapter->पढ़ो_ldidmap) अणु
		काष्ठा list_head *pos;
		list_क्रम_each(pos, &adapter->pending_list) अणु
			scb = list_entry(pos, scb_t, list);
			अगर (scb->pthru->logdrv < 0x80 )
				scb->pthru->logdrv += 0x80;
		पूर्ण
	पूर्ण

	atomic_set(&adapter->quiescent, 0);

	mega_runpendq(adapter);

	spin_unlock_irqrestore(&adapter->lock, flags);

	वापस rval;
पूर्ण


अटल पूर्णांक
mega_करो_del_logdrv(adapter_t *adapter, पूर्णांक logdrv)
अणु
	megacmd_t	mc;
	पूर्णांक	rval;

	स_रखो( &mc, 0, माप(megacmd_t));

	mc.cmd = FC_DEL_LOGDRV;
	mc.opcode = OP_DEL_LOGDRV;
	mc.subopcode = logdrv;

	rval = mega_पूर्णांकernal_command(adapter, &mc, शून्य);

	/* log this event */
	अगर(rval) अणु
		dev_warn(&adapter->dev->dev, "Delete LD-%d failed", logdrv);
		वापस rval;
	पूर्ण

	/*
	 * After deleting first logical drive, the logical drives must be
	 * addressed by adding 0x80 to the logical drive id.
	 */
	adapter->पढ़ो_ldidmap = 1;

	वापस rval;
पूर्ण


/**
 * mega_get_max_sgl()
 * @adapter: poपूर्णांकer to our soft state
 *
 * Find out the maximum number of scatter-gather elements supported by this
 * version of the firmware
 */
अटल व्योम
mega_get_max_sgl(adapter_t *adapter)
अणु
	अचिन्हित अक्षर	raw_mbox[माप(काष्ठा mbox_out)];
	mbox_t	*mbox;

	mbox = (mbox_t *)raw_mbox;

	स_रखो(mbox, 0, माप(raw_mbox));

	स_रखो((व्योम *)adapter->mega_buffer, 0, MEGA_BUFFER_SIZE);

	mbox->m_out.xferaddr = (u32)adapter->buf_dma_handle;

	raw_mbox[0] = MAIN_MISC_OPCODE;
	raw_mbox[2] = GET_MAX_SG_SUPPORT;


	अगर( issue_scb_block(adapter, raw_mbox) ) अणु
		/*
		 * f/w करोes not support this command. Choose the शेष value
		 */
		adapter->sglen = MIN_SGLIST;
	पूर्ण
	अन्यथा अणु
		adapter->sglen = *((अक्षर *)adapter->mega_buffer);
		
		/*
		 * Make sure this is not more than the resources we are
		 * planning to allocate
		 */
		अगर ( adapter->sglen > MAX_SGLIST )
			adapter->sglen = MAX_SGLIST;
	पूर्ण

	वापस;
पूर्ण


/**
 * mega_support_cluster()
 * @adapter: poपूर्णांकer to our soft state
 *
 * Find out अगर this firmware support cluster calls.
 */
अटल पूर्णांक
mega_support_cluster(adapter_t *adapter)
अणु
	अचिन्हित अक्षर	raw_mbox[माप(काष्ठा mbox_out)];
	mbox_t	*mbox;

	mbox = (mbox_t *)raw_mbox;

	स_रखो(mbox, 0, माप(raw_mbox));

	स_रखो((व्योम *)adapter->mega_buffer, 0, MEGA_BUFFER_SIZE);

	mbox->m_out.xferaddr = (u32)adapter->buf_dma_handle;

	/*
	 * Try to get the initiator id. This command will succeed अगरf the
	 * clustering is available on this HBA.
	 */
	raw_mbox[0] = MEGA_GET_TARGET_ID;

	अगर( issue_scb_block(adapter, raw_mbox) == 0 ) अणु

		/*
		 * Cluster support available. Get the initiator target id.
		 * Tell our id to mid-layer too.
		 */
		adapter->this_id = *(u32 *)adapter->mega_buffer;
		adapter->host->this_id = adapter->this_id;

		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PROC_FS
/**
 * mega_adapinq()
 * @adapter: poपूर्णांकer to our soft state
 * @dma_handle: DMA address of the buffer
 *
 * Issue पूर्णांकernal commands जबतक पूर्णांकerrupts are available.
 * We only issue direct mailbox commands from within the driver. ioctl()
 * पूर्णांकerface using these routines can issue passthru commands.
 */
अटल पूर्णांक
mega_adapinq(adapter_t *adapter, dma_addr_t dma_handle)
अणु
	megacmd_t	mc;

	स_रखो(&mc, 0, माप(megacmd_t));

	अगर( adapter->flag & BOARD_40LD ) अणु
		mc.cmd = FC_NEW_CONFIG;
		mc.opcode = NC_SUBOP_ENQUIRY3;
		mc.subopcode = ENQ3_GET_SOLICITED_FULL;
	पूर्ण
	अन्यथा अणु
		mc.cmd = MEGA_MBOXCMD_ADPEXTINQ;
	पूर्ण

	mc.xferaddr = (u32)dma_handle;

	अगर ( mega_पूर्णांकernal_command(adapter, &mc, शून्य) != 0 ) अणु
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण


/**
 * mega_पूर्णांकernal_dev_inquiry()
 * @adapter: poपूर्णांकer to our soft state
 * @ch: channel क्रम this device
 * @tgt: ID of this device
 * @buf_dma_handle: DMA address of the buffer
 *
 * Issue the scsi inquiry क्रम the specअगरied device.
 */
अटल पूर्णांक
mega_पूर्णांकernal_dev_inquiry(adapter_t *adapter, u8 ch, u8 tgt,
		dma_addr_t buf_dma_handle)
अणु
	mega_passthru	*pthru;
	dma_addr_t	pthru_dma_handle;
	megacmd_t	mc;
	पूर्णांक		rval;
	काष्ठा pci_dev	*pdev;


	/*
	 * For all पूर्णांकernal commands, the buffer must be allocated in <4GB
	 * address range
	 */
	अगर( make_local_pdev(adapter, &pdev) != 0 ) वापस -1;

	pthru = dma_alloc_coherent(&pdev->dev, माप(mega_passthru),
				   &pthru_dma_handle, GFP_KERNEL);

	अगर( pthru == शून्य ) अणु
		मुक्त_local_pdev(pdev);
		वापस -1;
	पूर्ण

	pthru->समयout = 2;
	pthru->ars = 1;
	pthru->reqsenselen = 14;
	pthru->islogical = 0;

	pthru->channel = (adapter->flag & BOARD_40LD) ? 0 : ch;

	pthru->target = (adapter->flag & BOARD_40LD) ? (ch << 4)|tgt : tgt;

	pthru->cdblen = 6;

	pthru->cdb[0] = INQUIRY;
	pthru->cdb[1] = 0;
	pthru->cdb[2] = 0;
	pthru->cdb[3] = 0;
	pthru->cdb[4] = 255;
	pthru->cdb[5] = 0;


	pthru->dataxferaddr = (u32)buf_dma_handle;
	pthru->dataxferlen = 256;

	स_रखो(&mc, 0, माप(megacmd_t));

	mc.cmd = MEGA_MBOXCMD_PASSTHRU;
	mc.xferaddr = (u32)pthru_dma_handle;

	rval = mega_पूर्णांकernal_command(adapter, &mc, pthru);

	dma_मुक्त_coherent(&pdev->dev, माप(mega_passthru), pthru,
			  pthru_dma_handle);

	मुक्त_local_pdev(pdev);

	वापस rval;
पूर्ण
#पूर्ण_अगर

/**
 * mega_पूर्णांकernal_command()
 * @adapter: poपूर्णांकer to our soft state
 * @mc: the mailbox command
 * @pthru: Passthru काष्ठाure क्रम DCDB commands
 *
 * Issue the पूर्णांकernal commands in पूर्णांकerrupt mode.
 * The last argument is the address of the passthru काष्ठाure अगर the command
 * to be fired is a passthru command
 *
 * Note: parameter 'pthru' is null क्रम non-passthru commands.
 */
अटल पूर्णांक
mega_पूर्णांकernal_command(adapter_t *adapter, megacmd_t *mc, mega_passthru *pthru)
अणु
	अचिन्हित दीर्घ flags;
	scb_t	*scb;
	पूर्णांक	rval;

	/*
	 * The पूर्णांकernal commands share one command id and hence are
	 * serialized. This is so because we want to reserve maximum number of
	 * available command ids क्रम the I/O commands.
	 */
	mutex_lock(&adapter->पूर्णांक_mtx);

	scb = &adapter->पूर्णांक_scb;
	स_रखो(scb, 0, माप(scb_t));

	scb->idx = CMDID_INT_CMDS;
	scb->state |= SCB_ACTIVE | SCB_PENDQ;

	स_नकल(scb->raw_mbox, mc, माप(megacmd_t));

	/*
	 * Is it a passthru command
	 */
	अगर (mc->cmd == MEGA_MBOXCMD_PASSTHRU)
		scb->pthru = pthru;

	spin_lock_irqsave(&adapter->lock, flags);
	list_add_tail(&scb->list, &adapter->pending_list);
	/*
	 * Check अगर the HBA is in quiescent state, e.g., during a
	 * delete logical drive opertion. If it is, करोn't run
	 * the pending_list.
	 */
	अगर (atomic_पढ़ो(&adapter->quiescent) == 0)
		mega_runpendq(adapter);
	spin_unlock_irqrestore(&adapter->lock, flags);

	रुको_क्रम_completion(&adapter->पूर्णांक_रुकोq);

	mc->status = rval = adapter->पूर्णांक_status;

	/*
	 * Prपूर्णांक a debug message क्रम all failed commands. Applications can use
	 * this inक्रमmation.
	 */
	अगर (rval && trace_level) अणु
		dev_info(&adapter->dev->dev, "cmd [%x, %x, %x] status:[%x]\n",
			mc->cmd, mc->opcode, mc->subopcode, rval);
	पूर्ण

	mutex_unlock(&adapter->पूर्णांक_mtx);
	वापस rval;
पूर्ण

अटल काष्ठा scsi_host_ढाँचा megaraid_ढाँचा = अणु
	.module				= THIS_MODULE,
	.name				= "MegaRAID",
	.proc_name			= "megaraid_legacy",
	.info				= megaraid_info,
	.queuecommand			= megaraid_queue,	
	.bios_param			= megaraid_biosparam,
	.max_sectors			= MAX_SECTORS_PER_IO,
	.can_queue			= MAX_COMMANDS,
	.this_id			= DEFAULT_INITIATOR_ID,
	.sg_tablesize			= MAX_SGLIST,
	.cmd_per_lun			= DEF_CMD_PER_LUN,
	.eh_पात_handler		= megaraid_पात,
	.eh_device_reset_handler	= megaraid_reset,
	.eh_bus_reset_handler		= megaraid_reset,
	.eh_host_reset_handler		= megaraid_reset,
	.no_ग_लिखो_same			= 1,
पूर्ण;

अटल पूर्णांक
megaraid_probe_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा Scsi_Host *host;
	adapter_t *adapter;
	अचिन्हित दीर्घ mega_baseport, tbase, flag = 0;
	u16 subsysid, subsysvid;
	u8 pci_bus, pci_dev_func;
	पूर्णांक irq, i, j;
	पूर्णांक error = -ENODEV;

	अगर (hba_count >= MAX_CONTROLLERS)
		जाओ out;

	अगर (pci_enable_device(pdev))
		जाओ out;
	pci_set_master(pdev);

	pci_bus = pdev->bus->number;
	pci_dev_func = pdev->devfn;

	/*
	 * The megaraid3 stuff reports the ID of the Intel part which is not
	 * remotely specअगरic to the megaraid
	 */
	अगर (pdev->venकरोr == PCI_VENDOR_ID_INTEL) अणु
		u16 magic;
		/*
		 * Don't fall over the Compaq management cards using the same
		 * PCI identअगरier
		 */
		अगर (pdev->subप्रणाली_venकरोr == PCI_VENDOR_ID_COMPAQ &&
		    pdev->subप्रणाली_device == 0xC000)
			जाओ out_disable_device;
		/* Now check the magic signature byte */
		pci_पढ़ो_config_word(pdev, PCI_CONF_AMISIG, &magic);
		अगर (magic != HBA_SIGNATURE_471 && magic != HBA_SIGNATURE)
			जाओ out_disable_device;
		/* Ok it is probably a megaraid */
	पूर्ण

	/*
	 * For these venकरोr and device ids, signature offsets are not
	 * valid and 64 bit is implicit
	 */
	अगर (id->driver_data & BOARD_64BIT)
		flag |= BOARD_64BIT;
	अन्यथा अणु
		u32 magic64;

		pci_पढ़ो_config_dword(pdev, PCI_CONF_AMISIG64, &magic64);
		अगर (magic64 == HBA_SIGNATURE_64BIT)
			flag |= BOARD_64BIT;
	पूर्ण

	subsysvid = pdev->subप्रणाली_venकरोr;
	subsysid = pdev->subप्रणाली_device;

	dev_notice(&pdev->dev, "found 0x%4.04x:0x%4.04x\n",
		id->venकरोr, id->device);

	/* Read the base port and IRQ from PCI */
	mega_baseport = pci_resource_start(pdev, 0);
	irq = pdev->irq;

	tbase = mega_baseport;
	अगर (pci_resource_flags(pdev, 0) & IORESOURCE_MEM) अणु
		flag |= BOARD_MEMMAP;

		अगर (!request_mem_region(mega_baseport, 128, "megaraid")) अणु
			dev_warn(&pdev->dev, "mem region busy!\n");
			जाओ out_disable_device;
		पूर्ण

		mega_baseport = (अचिन्हित दीर्घ)ioremap(mega_baseport, 128);
		अगर (!mega_baseport) अणु
			dev_warn(&pdev->dev, "could not map hba memory\n");
			जाओ out_release_region;
		पूर्ण
	पूर्ण अन्यथा अणु
		flag |= BOARD_IOMAP;
		mega_baseport += 0x10;

		अगर (!request_region(mega_baseport, 16, "megaraid"))
			जाओ out_disable_device;
	पूर्ण

	/* Initialize SCSI Host काष्ठाure */
	host = scsi_host_alloc(&megaraid_ढाँचा, माप(adapter_t));
	अगर (!host)
		जाओ out_iounmap;

	adapter = (adapter_t *)host->hostdata;
	स_रखो(adapter, 0, माप(adapter_t));

	dev_notice(&pdev->dev,
		"scsi%d:Found MegaRAID controller at 0x%lx, IRQ:%d\n",
		host->host_no, mega_baseport, irq);

	adapter->base = mega_baseport;
	अगर (flag & BOARD_MEMMAP)
		adapter->mmio_base = (व्योम __iomem *) mega_baseport;

	INIT_LIST_HEAD(&adapter->मुक्त_list);
	INIT_LIST_HEAD(&adapter->pending_list);
	INIT_LIST_HEAD(&adapter->completed_list);

	adapter->flag = flag;
	spin_lock_init(&adapter->lock);

	host->cmd_per_lun = max_cmd_per_lun;
	host->max_sectors = max_sectors_per_io;

	adapter->dev = pdev;
	adapter->host = host;

	adapter->host->irq = irq;

	अगर (flag & BOARD_MEMMAP)
		adapter->host->base = tbase;
	अन्यथा अणु
		adapter->host->io_port = tbase;
		adapter->host->n_io_port = 16;
	पूर्ण

	adapter->host->unique_id = (pci_bus << 8) | pci_dev_func;

	/*
	 * Allocate buffer to issue पूर्णांकernal commands.
	 */
	adapter->mega_buffer = dma_alloc_coherent(&adapter->dev->dev,
						  MEGA_BUFFER_SIZE,
						  &adapter->buf_dma_handle,
						  GFP_KERNEL);
	अगर (!adapter->mega_buffer) अणु
		dev_warn(&pdev->dev, "out of RAM\n");
		जाओ out_host_put;
	पूर्ण

	adapter->scb_list = kदो_स्मृति_array(MAX_COMMANDS, माप(scb_t),
					  GFP_KERNEL);
	अगर (!adapter->scb_list) अणु
		dev_warn(&pdev->dev, "out of RAM\n");
		जाओ out_मुक्त_cmd_buffer;
	पूर्ण

	अगर (request_irq(irq, (adapter->flag & BOARD_MEMMAP) ?
				megaraid_isr_memmapped : megaraid_isr_iomapped,
					IRQF_SHARED, "megaraid", adapter)) अणु
		dev_warn(&pdev->dev, "Couldn't register IRQ %d!\n", irq);
		जाओ out_मुक्त_scb_list;
	पूर्ण

	अगर (mega_setup_mailbox(adapter))
		जाओ out_मुक्त_irq;

	अगर (mega_query_adapter(adapter))
		जाओ out_मुक्त_mbox;

	/*
	 * Have checks क्रम some buggy f/w
	 */
	अगर ((subsysid == 0x1111) && (subsysvid == 0x1111)) अणु
		/*
		 * Which firmware
		 */
		अगर (!म_भेद(adapter->fw_version, "3.00") ||
				!म_भेद(adapter->fw_version, "3.01")) अणु

			dev_warn(&pdev->dev,
				"Your card is a Dell PERC "
				"2/SC RAID controller with "
				"firmware\nmegaraid: 3.00 or 3.01.  "
				"This driver is known to have "
				"corruption issues\nmegaraid: with "
				"those firmware versions on this "
				"specific card.  In order\nmegaraid: "
				"to protect your data, please upgrade "
				"your firmware to version\nmegaraid: "
				"3.10 or later, available from the "
				"Dell Technical Support web\n"
				"megaraid: site at\nhttp://support."
				"dell.com/us/en/filelib/download/"
				"index.asp?fileid=2940\n"
			);
		पूर्ण
	पूर्ण

	/*
	 * If we have a HP 1M(0x60E7)/2M(0x60E8) controller with
	 * firmware H.01.07, H.01.08, and H.01.09 disable 64 bit
	 * support, since this firmware cannot handle 64 bit
	 * addressing
	 */
	अगर ((subsysvid == PCI_VENDOR_ID_HP) &&
	    ((subsysid == 0x60E7) || (subsysid == 0x60E8))) अणु
		/*
		 * which firmware
		 */
		अगर (!म_भेद(adapter->fw_version, "H01.07") ||
		    !म_भेद(adapter->fw_version, "H01.08") ||
		    !म_भेद(adapter->fw_version, "H01.09") ) अणु
			dev_warn(&pdev->dev,
				"Firmware H.01.07, "
				"H.01.08, and H.01.09 on 1M/2M "
				"controllers\n"
				"do not support 64 bit "
				"addressing.\nDISABLING "
				"64 bit support.\n");
			adapter->flag &= ~BOARD_64BIT;
		पूर्ण
	पूर्ण

	अगर (mega_is_bios_enabled(adapter))
		mega_hbas[hba_count].is_bios_enabled = 1;
	mega_hbas[hba_count].hostdata_addr = adapter;

	/*
	 * Find out which channel is raid and which is scsi. This is
	 * क्रम ROMB support.
	 */
	mega_क्रमागत_raid_scsi(adapter);

	/*
	 * Find out अगर a logical drive is set as the boot drive. If
	 * there is one, will make that as the first logical drive.
	 * ROMB: Do we have to boot from a physical drive. Then all
	 * the physical drives would appear beक्रमe the logical disks.
	 * Else, all the physical drives would be exported to the mid
	 * layer after logical drives.
	 */
	mega_get_boot_drv(adapter);

	अगर (adapter->boot_pdrv_enabled) अणु
		j = adapter->product_info.nchannels;
		क्रम( i = 0; i < j; i++ )
			adapter->logdrv_chan[i] = 0;
		क्रम( i = j; i < NVIRT_CHAN + j; i++ )
			adapter->logdrv_chan[i] = 1;
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < NVIRT_CHAN; i++)
			adapter->logdrv_chan[i] = 1;
		क्रम (i = NVIRT_CHAN; i < MAX_CHANNELS+NVIRT_CHAN; i++)
			adapter->logdrv_chan[i] = 0;
		adapter->mega_ch_class <<= NVIRT_CHAN;
	पूर्ण

	/*
	 * Do we support अक्रमom deletion and addition of logical
	 * drives
	 */
	adapter->पढ़ो_ldidmap = 0;	/* set it after first logdrv
						   delete cmd */
	adapter->support_अक्रमom_del = mega_support_अक्रमom_del(adapter);

	/* Initialize SCBs */
	अगर (mega_init_scb(adapter))
		जाओ out_मुक्त_mbox;

	/*
	 * Reset the pending commands counter
	 */
	atomic_set(&adapter->pend_cmds, 0);

	/*
	 * Reset the adapter quiescent flag
	 */
	atomic_set(&adapter->quiescent, 0);

	hba_soft_state[hba_count] = adapter;

	/*
	 * Fill in the काष्ठाure which needs to be passed back to the
	 * application when it करोes an ioctl() क्रम controller related
	 * inक्रमmation.
	 */
	i = hba_count;

	mcontroller[i].base = mega_baseport;
	mcontroller[i].irq = irq;
	mcontroller[i].numldrv = adapter->numldrv;
	mcontroller[i].pcibus = pci_bus;
	mcontroller[i].pcidev = id->device;
	mcontroller[i].pcअगरun = PCI_FUNC (pci_dev_func);
	mcontroller[i].pciid = -1;
	mcontroller[i].pcivenकरोr = id->venकरोr;
	mcontroller[i].pcislot = PCI_SLOT(pci_dev_func);
	mcontroller[i].uid = (pci_bus << 8) | pci_dev_func;


	/* Set the Mode of addressing to 64 bit अगर we can */
	अगर ((adapter->flag & BOARD_64BIT) && (माप(dma_addr_t) == 8)) अणु
		dma_set_mask(&pdev->dev, DMA_BIT_MASK(64));
		adapter->has_64bit_addr = 1;
	पूर्ण अन्यथा  अणु
		dma_set_mask(&pdev->dev, DMA_BIT_MASK(32));
		adapter->has_64bit_addr = 0;
	पूर्ण
		
	mutex_init(&adapter->पूर्णांक_mtx);
	init_completion(&adapter->पूर्णांक_रुकोq);

	adapter->this_id = DEFAULT_INITIATOR_ID;
	adapter->host->this_id = DEFAULT_INITIATOR_ID;

#अगर MEGA_HAVE_CLUSTERING
	/*
	 * Is cluster support enabled on this controller
	 * Note: In a cluster the HBAs ( the initiators ) will have
	 * dअगरferent target IDs and we cannot assume it to be 7. Call
	 * to mega_support_cluster() will get the target ids also अगर
	 * the cluster support is available
	 */
	adapter->has_cluster = mega_support_cluster(adapter);
	अगर (adapter->has_cluster) अणु
		dev_notice(&pdev->dev,
			"Cluster driver, initiator id:%d\n",
			adapter->this_id);
	पूर्ण
#पूर्ण_अगर

	pci_set_drvdata(pdev, host);

	mega_create_proc_entry(hba_count, mega_proc_dir_entry);

	error = scsi_add_host(host, &pdev->dev);
	अगर (error)
		जाओ out_मुक्त_mbox;

	scsi_scan_host(host);
	hba_count++;
	वापस 0;

 out_मुक्त_mbox:
	dma_मुक्त_coherent(&adapter->dev->dev, माप(mbox64_t),
			  adapter->una_mbox64, adapter->una_mbox64_dma);
 out_मुक्त_irq:
	मुक्त_irq(adapter->host->irq, adapter);
 out_मुक्त_scb_list:
	kमुक्त(adapter->scb_list);
 out_मुक्त_cmd_buffer:
	dma_मुक्त_coherent(&adapter->dev->dev, MEGA_BUFFER_SIZE,
			  adapter->mega_buffer, adapter->buf_dma_handle);
 out_host_put:
	scsi_host_put(host);
 out_iounmap:
	अगर (flag & BOARD_MEMMAP)
		iounmap((व्योम *)mega_baseport);
 out_release_region:
	अगर (flag & BOARD_MEMMAP)
		release_mem_region(tbase, 128);
	अन्यथा
		release_region(mega_baseport, 16);
 out_disable_device:
	pci_disable_device(pdev);
 out:
	वापस error;
पूर्ण

अटल व्योम
__megaraid_shutकरोwn(adapter_t *adapter)
अणु
	u_अक्षर	raw_mbox[माप(काष्ठा mbox_out)];
	mbox_t	*mbox = (mbox_t *)raw_mbox;
	पूर्णांक	i;

	/* Flush adapter cache */
	स_रखो(&mbox->m_out, 0, माप(raw_mbox));
	raw_mbox[0] = FLUSH_ADAPTER;

	मुक्त_irq(adapter->host->irq, adapter);

	/* Issue a blocking (पूर्णांकerrupts disabled) command to the card */
	issue_scb_block(adapter, raw_mbox);

	/* Flush disks cache */
	स_रखो(&mbox->m_out, 0, माप(raw_mbox));
	raw_mbox[0] = FLUSH_SYSTEM;

	/* Issue a blocking (पूर्णांकerrupts disabled) command to the card */
	issue_scb_block(adapter, raw_mbox);
	
	अगर (atomic_पढ़ो(&adapter->pend_cmds) > 0)
		dev_warn(&adapter->dev->dev, "pending commands!!\n");

	/*
	 * Have a delibrate delay to make sure all the caches are
	 * actually flushed.
	 */
	क्रम (i = 0; i <= 10; i++)
		mdelay(1000);
पूर्ण

अटल व्योम
megaraid_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा Scsi_Host *host = pci_get_drvdata(pdev);
	adapter_t *adapter = (adapter_t *)host->hostdata;
	अक्षर buf[12] = अणु 0 पूर्ण;

	scsi_हटाओ_host(host);

	__megaraid_shutकरोwn(adapter);

	/* Free our resources */
	अगर (adapter->flag & BOARD_MEMMAP) अणु
		iounmap((व्योम *)adapter->base);
		release_mem_region(adapter->host->base, 128);
	पूर्ण अन्यथा
		release_region(adapter->base, 16);

	mega_मुक्त_sgl(adapter);

	प्र_लिखो(buf, "hba%d", adapter->host->host_no);
	हटाओ_proc_subtree(buf, mega_proc_dir_entry);

	dma_मुक्त_coherent(&adapter->dev->dev, MEGA_BUFFER_SIZE,
			  adapter->mega_buffer, adapter->buf_dma_handle);
	kमुक्त(adapter->scb_list);
	dma_मुक्त_coherent(&adapter->dev->dev, माप(mbox64_t),
			  adapter->una_mbox64, adapter->una_mbox64_dma);

	scsi_host_put(host);
	pci_disable_device(pdev);

	hba_count--;
पूर्ण

अटल व्योम
megaraid_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	काष्ठा Scsi_Host *host = pci_get_drvdata(pdev);
	adapter_t *adapter = (adapter_t *)host->hostdata;

	__megaraid_shutकरोwn(adapter);
पूर्ण

अटल काष्ठा pci_device_id megaraid_pci_tbl[] = अणु
	अणुPCI_VENDOR_ID_AMI, PCI_DEVICE_ID_AMI_MEGARAID,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0पूर्ण,
	अणुPCI_VENDOR_ID_AMI, PCI_DEVICE_ID_AMI_MEGARAID2,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0पूर्ण,
	अणुPCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_AMI_MEGARAID3,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0पूर्ण,
	अणु0,पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, megaraid_pci_tbl);

अटल काष्ठा pci_driver megaraid_pci_driver = अणु
	.name		= "megaraid_legacy",
	.id_table	= megaraid_pci_tbl,
	.probe		= megaraid_probe_one,
	.हटाओ		= megaraid_हटाओ_one,
	.shutकरोwn	= megaraid_shutकरोwn,
पूर्ण;

अटल पूर्णांक __init megaraid_init(व्योम)
अणु
	पूर्णांक error;

	अगर ((max_cmd_per_lun <= 0) || (max_cmd_per_lun > MAX_CMD_PER_LUN))
		max_cmd_per_lun = MAX_CMD_PER_LUN;
	अगर (max_mbox_busy_रुको > MBOX_BUSY_WAIT)
		max_mbox_busy_रुको = MBOX_BUSY_WAIT;

#अगर_घोषित CONFIG_PROC_FS
	mega_proc_dir_entry = proc_सूची_गढ़ो("megaraid", शून्य);
	अगर (!mega_proc_dir_entry) अणु
		prपूर्णांकk(KERN_WARNING
				"megaraid: failed to create megaraid root\n");
	पूर्ण
#पूर्ण_अगर
	error = pci_रेजिस्टर_driver(&megaraid_pci_driver);
	अगर (error) अणु
#अगर_घोषित CONFIG_PROC_FS
		हटाओ_proc_entry("megaraid", शून्य);
#पूर्ण_अगर
		वापस error;
	पूर्ण

	/*
	 * Register the driver as a अक्षरacter device, क्रम applications
	 * to access it क्रम ioctls.
	 * First argument (major) to रेजिस्टर_chrdev implies a dynamic
	 * major number allocation.
	 */
	major = रेजिस्टर_chrdev(0, "megadev_legacy", &megadev_fops);
	अगर (!major) अणु
		prपूर्णांकk(KERN_WARNING
				"megaraid: failed to register char device\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास megaraid_निकास(व्योम)
अणु
	/*
	 * Unरेजिस्टर the अक्षरacter device पूर्णांकerface to the driver.
	 */
	unरेजिस्टर_chrdev(major, "megadev_legacy");

	pci_unरेजिस्टर_driver(&megaraid_pci_driver);

#अगर_घोषित CONFIG_PROC_FS
	हटाओ_proc_entry("megaraid", शून्य);
#पूर्ण_अगर
पूर्ण

module_init(megaraid_init);
module_निकास(megaraid_निकास);

/* vi: set ts=8 sw=8 tw=78: */
