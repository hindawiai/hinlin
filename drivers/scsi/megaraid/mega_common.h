<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *
 *			Linux MegaRAID device driver
 *
 * Copyright (c) 2003-2004  LSI Logic Corporation.
 *
 * खाता		: mega_common.h
 *
 * Libaray of common routine used by all low-level megaraid drivers
 */

#अगर_अघोषित _MEGA_COMMON_H_
#घोषणा _MEGA_COMMON_H_

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mutex.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/list.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/dma-mapping.h>
#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_host.h>


#घोषणा LSI_MAX_CHANNELS		16
#घोषणा LSI_MAX_LOGICAL_DRIVES_64LD	(64+1)

#घोषणा HBA_SIGNATURE_64_BIT		0x299
#घोषणा PCI_CONF_AMISIG64		0xa4

#घोषणा MEGA_SCSI_INQ_EVPD		1
#घोषणा MEGA_INVALID_FIELD_IN_CDB	0x24


/**
 * scb_t - scsi command control block
 * @ccb			: command control block क्रम inभागidual driver
 * @list		: list of control blocks
 * @gp			: general purpose field क्रम LLDs
 * @sno			: all SCBs have a serial number
 * @scp			: associated scsi command
 * @state		: current state of scb
 * @dma_dir		: direction of data transfer
 * @dma_type		: transfer with sg list, buffer, or no data transfer
 * @dev_channel		: actual channel on the device
 * @dev_target		: actual target on the device
 * @status		: completion status
 *
 * This is our central data काष्ठाure to issue commands the each driver.
 * Driver specअगरic data काष्ठाures are मुख्यtained in the ccb field.
 * scb provides a field 'gp', which can be used by LLD क्रम its own purposes
 *
 * dev_channel and dev_target must be initialized with the actual channel and
 * target on the controller.
 */
प्रकार काष्ठा अणु
	caddr_t			ccb;
	काष्ठा list_head	list;
	अचिन्हित दीर्घ		gp;
	अचिन्हित पूर्णांक		sno;
	काष्ठा scsi_cmnd	*scp;
	uपूर्णांक32_t		state;
	uपूर्णांक32_t		dma_direction;
	uपूर्णांक32_t		dma_type;
	uपूर्णांक16_t		dev_channel;
	uपूर्णांक16_t		dev_target;
	uपूर्णांक32_t		status;
पूर्ण scb_t;

/*
 * SCB states as it transitions from one state to another
 */
#घोषणा SCB_FREE	0x0000	/* on the मुक्त list */
#घोषणा SCB_ACTIVE	0x0001	/* off the मुक्त list */
#घोषणा SCB_PENDQ	0x0002	/* on the pending queue */
#घोषणा SCB_ISSUED	0x0004	/* issued - owner f/w */
#घोषणा SCB_ABORT	0x0008	/* Got an पात क्रम this one */
#घोषणा SCB_RESET	0x0010	/* Got a reset क्रम this one */

/*
 * DMA types क्रम scb
 */
#घोषणा MRAID_DMA_NONE	0x0000	/* no data transfer क्रम this command */
#घोषणा MRAID_DMA_WSG	0x0001	/* data transfer using a sg list */
#घोषणा MRAID_DMA_WBUF	0x0002	/* data transfer using a contiguous buffer */


/**
 * काष्ठा adapter_t - driver's initialization काष्ठाure
 * @aram dpc_h			: tasklet handle
 * @pdev			: pci configuration poपूर्णांकer क्रम kernel
 * @host			: poपूर्णांकer to host काष्ठाure of mid-layer
 * @lock			: synchronization lock क्रम mid-layer and driver
 * @quiescent			: driver is quiescent क्रम now.
 * @outstanding_cmds		: number of commands pending in the driver
 * @kscb_list			: poपूर्णांकer to the bulk of SCBs poपूर्णांकers क्रम IO
 * @kscb_pool			: pool of मुक्त scbs क्रम IO
 * @kscb_pool_lock		: lock क्रम pool of मुक्त scbs
 * @pend_list			: pending commands list
 * @pend_list_lock		: exclusion lock क्रम pending commands list
 * @completed_list		: list of completed commands
 * @completed_list_lock		: exclusion lock क्रम list of completed commands
 * @sglen			: max sg elements supported
 * @device_ids			: to convert kernel device addr to our devices.
 * @raid_device			: raid adapter specअगरic poपूर्णांकer
 * @max_channel			: maximum channel number supported - inclusive
 * @max_target			: max target supported - inclusive
 * @max_lun			: max lun supported - inclusive
 * @unique_id			: unique identअगरier क्रम each adapter
 * @irq				: IRQ क्रम this adapter
 * @ito				: पूर्णांकernal समयout value, (-1) means no समयout
 * @ibuf			: buffer to issue पूर्णांकernal commands
 * @ibuf_dma_h			: dma handle क्रम the above buffer
 * @uscb_list			: SCB poपूर्णांकers क्रम user cmds, common mgmt module
 * @uscb_pool			: pool of SCBs क्रम user commands
 * @uscb_pool_lock		: exclusion lock क्रम these SCBs
 * @max_cmds			: max outstanding commands
 * @fw_version			: firmware version
 * @bios_version		: bios version
 * @max_cdb_sz			: biggest CDB size supported.
 * @ha				: is high availability present - clustering
 * @init_id			: initiator ID, the शेष value should be 7
 * @max_sectors			: max sectors per request
 * @cmd_per_lun			: max outstanding commands per LUN
 * @being_detached		: set when unloading, no more mgmt calls
 *
 *
 * mraid_setup_device_map() can be called anyसमय after the device map is
 * available and MRAID_GET_DEVICE_MAP() can be called whenever the mapping is
 * required, usually from LLD's queue entry poपूर्णांक. The क्रमmar API sets up the
 * MRAID_IS_LOGICAL(adapter_t *, काष्ठा scsi_cmnd *) to find out अगर the
 * device in question is a logical drive.
 *
 * quiescent flag should be set by the driver अगर it is not accepting more
 * commands
 *
 * NOTE: The fields of this काष्ठाures are placed to minimize cache misses
 */

// amount of space required to store the bios and firmware version strings
#घोषणा VERSION_SIZE	16

प्रकार काष्ठा अणु
	काष्ठा tasklet_काष्ठा	dpc_h;
	काष्ठा pci_dev		*pdev;
	काष्ठा Scsi_Host	*host;
	spinlock_t		lock;
	uपूर्णांक8_t			quiescent;
	पूर्णांक			outstanding_cmds;
	scb_t			*kscb_list;
	काष्ठा list_head	kscb_pool;
	spinlock_t		kscb_pool_lock;
	काष्ठा list_head	pend_list;
	spinlock_t		pend_list_lock;
	काष्ठा list_head	completed_list;
	spinlock_t		completed_list_lock;
	uपूर्णांक16_t		sglen;
	पूर्णांक			device_ids[LSI_MAX_CHANNELS]
					[LSI_MAX_LOGICAL_DRIVES_64LD];
	caddr_t			raid_device;
	uपूर्णांक8_t			max_channel;
	uपूर्णांक16_t		max_target;
	uपूर्णांक8_t			max_lun;

	uपूर्णांक32_t		unique_id;
	पूर्णांक			irq;
	uपूर्णांक8_t			ito;
	caddr_t			ibuf;
	dma_addr_t		ibuf_dma_h;
	scb_t			*uscb_list;
	काष्ठा list_head	uscb_pool;
	spinlock_t		uscb_pool_lock;
	पूर्णांक			max_cmds;
	uपूर्णांक8_t			fw_version[VERSION_SIZE];
	uपूर्णांक8_t			bios_version[VERSION_SIZE];
	uपूर्णांक8_t			max_cdb_sz;
	uपूर्णांक8_t			ha;
	uपूर्णांक16_t		init_id;
	uपूर्णांक16_t		max_sectors;
	uपूर्णांक16_t		cmd_per_lun;
	atomic_t		being_detached;
पूर्ण adapter_t;

#घोषणा SCSI_FREE_LIST_LOCK(adapter)	(&adapter->kscb_pool_lock)
#घोषणा USER_FREE_LIST_LOCK(adapter)	(&adapter->uscb_pool_lock)
#घोषणा PENDING_LIST_LOCK(adapter)	(&adapter->pend_list_lock)
#घोषणा COMPLETED_LIST_LOCK(adapter)	(&adapter->completed_list_lock)


// conversion from scsi command
#घोषणा SCP2HOST(scp)			(scp)->device->host	// to host
#घोषणा SCP2HOSTDATA(scp)		SCP2HOST(scp)->hostdata	// to soft state
#घोषणा SCP2CHANNEL(scp)		(scp)->device->channel	// to channel
#घोषणा SCP2TARGET(scp)			(scp)->device->id	// to target
#घोषणा SCP2LUN(scp)			(u32)(scp)->device->lun	// to LUN

// generic macro to convert scsi command and host to controller's soft state
#घोषणा SCSIHOST2ADAP(host)	(((caddr_t *)(host->hostdata))[0])
#घोषणा SCP2ADAPTER(scp)	(adapter_t *)SCSIHOST2ADAP(SCP2HOST(scp))


#घोषणा MRAID_IS_LOGICAL(adp, scp)	\
	(SCP2CHANNEL(scp) == (adp)->max_channel) ? 1 : 0

#घोषणा MRAID_IS_LOGICAL_SDEV(adp, sdev)	\
	(sdev->channel == (adp)->max_channel) ? 1 : 0

/**
 * MRAID_GET_DEVICE_MAP - device ids
 * @adp			: adapter's soft state
 * @scp			: mid-layer scsi command poपूर्णांकer
 * @p_chan		: physical channel on the controller
 * @target		: target id of the device or logical drive number
 * @islogical		: set अगर the command is क्रम the logical drive
 *
 * Macro to retrieve inक्रमmation about device class, logical or physical and
 * the corresponding physical channel and target or logical drive number
 */
#घोषणा MRAID_GET_DEVICE_MAP(adp, scp, p_chan, target, islogical)	\
	/*								\
	 * Is the request coming क्रम the भव channel		\
	 */								\
	islogical = MRAID_IS_LOGICAL(adp, scp);				\
									\
	/*								\
	 * Get an index पूर्णांकo our table of drive ids mapping		\
	 */								\
	अगर (islogical) अणु						\
		p_chan = 0xFF;						\
		target =						\
		(adp)->device_ids[(adp)->max_channel][SCP2TARGET(scp)];	\
	पूर्ण								\
	अन्यथा अणु								\
		p_chan = ((adp)->device_ids[SCP2CHANNEL(scp)]		\
					[SCP2TARGET(scp)] >> 8) & 0xFF;	\
		target = ((adp)->device_ids[SCP2CHANNEL(scp)]		\
					[SCP2TARGET(scp)] & 0xFF);	\
	पूर्ण

/*
 * ### Helper routines ###
 */
#घोषणा LSI_DBGLVL mraid_debug_level	// each LLD must define a global
 					// mraid_debug_level

#अगर_घोषित DEBUG
#अगर defined (_ASSERT_PANIC)
#घोषणा ASSERT_ACTION	panic
#अन्यथा
#घोषणा ASSERT_ACTION	prपूर्णांकk
#पूर्ण_अगर

#घोषणा ASSERT(expression)						\
	अगर (!(expression)) अणु						\
	ASSERT_ACTION("assertion failed:(%s), file: %s, line: %d:%s\n",	\
			#expression, __खाता__, __LINE__, __func__);	\
	पूर्ण
#अन्यथा
#घोषणा ASSERT(expression)
#पूर्ण_अगर

/**
 * काष्ठा mraid_pci_blk - काष्ठाure holds DMA memory block info
 * @vaddr		: भव address to a memory block
 * @dma_addr		: DMA handle to a memory block
 *
 * This काष्ठाure is filled up क्रम the caller. It is the responsibilty of the
 * caller to allocate this array big enough to store addresses क्रम all
 * requested elements
 */
काष्ठा mraid_pci_blk अणु
	caddr_t		vaddr;
	dma_addr_t	dma_addr;
पूर्ण;

#पूर्ण_अगर // _MEGA_COMMON_H_
