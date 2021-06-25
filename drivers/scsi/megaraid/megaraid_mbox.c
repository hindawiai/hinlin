<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 *			Linux MegaRAID device driver
 *
 * Copyright (c) 2003-2004  LSI Logic Corporation.
 *
 * खाता		: megaraid_mbox.c
 * Version	: v2.20.5.1 (Nov 16 2006)
 *
 * Authors:
 * 	Atul Mukker		<Atul.Mukker@lsi.com>
 * 	Sreenivas Bagalkote	<Sreenivas.Bagalkote@lsi.com>
 * 	Manoj Jose		<Manoj.Jose@lsi.com>
 * 	Seokmann Ju
 *
 * List of supported controllers
 *
 * OEM	Product Name			VID	DID	SSVID	SSID
 * ---	------------			---	---	----	----
 * Dell PERC3/QC			101E	1960	1028	0471
 * Dell PERC3/DC			101E	1960	1028	0493
 * Dell PERC3/SC			101E	1960	1028	0475
 * Dell PERC3/Di			1028	1960	1028	0123
 * Dell PERC4/SC			1000	1960	1028	0520
 * Dell PERC4/DC			1000	1960	1028	0518
 * Dell PERC4/QC			1000	0407	1028	0531
 * Dell PERC4/Di			1028	000F	1028	014A
 * Dell PERC 4e/Si			1028	0013	1028	016c
 * Dell PERC 4e/Di			1028	0013	1028	016d
 * Dell PERC 4e/Di			1028	0013	1028	016e
 * Dell PERC 4e/Di			1028	0013	1028	016f
 * Dell PERC 4e/Di			1028	0013	1028	0170
 * Dell PERC 4e/DC			1000	0408	1028	0002
 * Dell PERC 4e/SC			1000	0408	1028	0001
 *
 * LSI MegaRAID SCSI 320-0		1000	1960	1000	A520
 * LSI MegaRAID SCSI 320-1		1000	1960	1000	0520
 * LSI MegaRAID SCSI 320-2		1000	1960	1000	0518
 * LSI MegaRAID SCSI 320-0X		1000	0407	1000	0530
 * LSI MegaRAID SCSI 320-2X		1000	0407	1000	0532
 * LSI MegaRAID SCSI 320-4X		1000	0407	1000	0531
 * LSI MegaRAID SCSI 320-1E		1000	0408	1000	0001
 * LSI MegaRAID SCSI 320-2E		1000	0408	1000	0002
 * LSI MegaRAID SATA 150-4		1000	1960	1000	4523
 * LSI MegaRAID SATA 150-6		1000	1960	1000	0523
 * LSI MegaRAID SATA 300-4X		1000	0409	1000	3004
 * LSI MegaRAID SATA 300-8X		1000	0409	1000	3008
 *
 * INTEL RAID Controller SRCU42X	1000	0407	8086	0532
 * INTEL RAID Controller SRCS16		1000	1960	8086	0523
 * INTEL RAID Controller SRCU42E	1000	0408	8086	0002
 * INTEL RAID Controller SRCZCRX	1000	0407	8086	0530
 * INTEL RAID Controller SRCS28X	1000	0409	8086	3008
 * INTEL RAID Controller SROMBU42E	1000	0408	8086	3431
 * INTEL RAID Controller SROMBU42E	1000	0408	8086	3499
 * INTEL RAID Controller SRCU51L	1000	1960	8086	0520
 *
 * FSC	MegaRAID PCI Express ROMB	1000	0408	1734	1065
 *
 * ACER	MegaRAID ROMB-2E		1000	0408	1025	004D
 *
 * NEC	MegaRAID PCI Express ROMB	1000	0408	1033	8287
 *
 * For history of changes, see Documentation/scsi/ChangeLog.megaraid
 */

#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश "megaraid_mbox.h"

अटल पूर्णांक megaraid_init(व्योम);
अटल व्योम megaraid_निकास(व्योम);

अटल पूर्णांक megaraid_probe_one(काष्ठा pci_dev*, स्थिर काष्ठा pci_device_id *);
अटल व्योम megaraid_detach_one(काष्ठा pci_dev *);
अटल व्योम megaraid_mbox_shutकरोwn(काष्ठा pci_dev *);

अटल पूर्णांक megaraid_io_attach(adapter_t *);
अटल व्योम megaraid_io_detach(adapter_t *);

अटल पूर्णांक megaraid_init_mbox(adapter_t *);
अटल व्योम megaraid_fini_mbox(adapter_t *);

अटल पूर्णांक megaraid_alloc_cmd_packets(adapter_t *);
अटल व्योम megaraid_मुक्त_cmd_packets(adapter_t *);

अटल पूर्णांक megaraid_mbox_setup_dma_pools(adapter_t *);
अटल व्योम megaraid_mbox_tearकरोwn_dma_pools(adapter_t *);

अटल पूर्णांक megaraid_sysfs_alloc_resources(adapter_t *);
अटल व्योम megaraid_sysfs_मुक्त_resources(adapter_t *);

अटल पूर्णांक megaraid_पात_handler(काष्ठा scsi_cmnd *);
अटल पूर्णांक megaraid_reset_handler(काष्ठा scsi_cmnd *);

अटल पूर्णांक mbox_post_sync_cmd(adapter_t *, uपूर्णांक8_t []);
अटल पूर्णांक mbox_post_sync_cmd_fast(adapter_t *, uपूर्णांक8_t []);
अटल पूर्णांक megaraid_busyरुको_mbox(mraid_device_t *);
अटल पूर्णांक megaraid_mbox_product_info(adapter_t *);
अटल पूर्णांक megaraid_mbox_extended_cdb(adapter_t *);
अटल पूर्णांक megaraid_mbox_support_ha(adapter_t *, uपूर्णांक16_t *);
अटल पूर्णांक megaraid_mbox_support_अक्रमom_del(adapter_t *);
अटल पूर्णांक megaraid_mbox_get_max_sg(adapter_t *);
अटल व्योम megaraid_mbox_क्रमागत_raid_scsi(adapter_t *);
अटल व्योम megaraid_mbox_flush_cache(adapter_t *);
अटल पूर्णांक megaraid_mbox_fire_sync_cmd(adapter_t *);

अटल व्योम megaraid_mbox_display_scb(adapter_t *, scb_t *);
अटल व्योम megaraid_mbox_setup_device_map(adapter_t *);

अटल पूर्णांक megaraid_queue_command(काष्ठा Scsi_Host *, काष्ठा scsi_cmnd *);
अटल scb_t *megaraid_mbox_build_cmd(adapter_t *, काष्ठा scsi_cmnd *, पूर्णांक *);
अटल व्योम megaraid_mbox_runpendq(adapter_t *, scb_t *);
अटल व्योम megaraid_mbox_prepare_pthru(adapter_t *, scb_t *,
		काष्ठा scsi_cmnd *);
अटल व्योम megaraid_mbox_prepare_epthru(adapter_t *, scb_t *,
		काष्ठा scsi_cmnd *);

अटल irqवापस_t megaraid_isr(पूर्णांक, व्योम *);

अटल व्योम megaraid_mbox_dpc(अचिन्हित दीर्घ);

अटल sमाप_प्रकार megaraid_sysfs_show_app_hndl(काष्ठा device *, काष्ठा device_attribute *attr, अक्षर *);
अटल sमाप_प्रकार megaraid_sysfs_show_ldnum(काष्ठा device *, काष्ठा device_attribute *attr, अक्षर *);

अटल पूर्णांक megaraid_cmm_रेजिस्टर(adapter_t *);
अटल पूर्णांक megaraid_cmm_unरेजिस्टर(adapter_t *);
अटल पूर्णांक megaraid_mbox_mm_handler(अचिन्हित दीर्घ, uioc_t *, uपूर्णांक32_t);
अटल पूर्णांक megaraid_mbox_mm_command(adapter_t *, uioc_t *);
अटल व्योम megaraid_mbox_mm_करोne(adapter_t *, scb_t *);
अटल पूर्णांक gather_hbainfo(adapter_t *, mraid_hba_info_t *);
अटल पूर्णांक रुको_till_fw_empty(adapter_t *);



MODULE_AUTHOR("megaraidlinux@lsi.com");
MODULE_DESCRIPTION("LSI Logic MegaRAID Mailbox Driver");
MODULE_LICENSE("GPL");
MODULE_VERSION(MEGARAID_VERSION);

/*
 * ### modules parameters क्रम driver ###
 */

/*
 * Set to enable driver to expose unconfigured disk to kernel
 */
अटल पूर्णांक megaraid_expose_unconf_disks = 0;
module_param_named(unconf_disks, megaraid_expose_unconf_disks, पूर्णांक, 0);
MODULE_PARM_DESC(unconf_disks,
	"Set to expose unconfigured disks to kernel (default=0)");

/*
 * driver रुको समय अगर the adapter's mailbox is busy
 */
अटल अचिन्हित पूर्णांक max_mbox_busy_रुको = MBOX_BUSY_WAIT;
module_param_named(busy_रुको, max_mbox_busy_रुको, पूर्णांक, 0);
MODULE_PARM_DESC(busy_रुको,
	"Max wait for mailbox in microseconds if busy (default=10)");

/*
 * number of sectors per IO command
 */
अटल अचिन्हित पूर्णांक megaraid_max_sectors = MBOX_MAX_SECTORS;
module_param_named(max_sectors, megaraid_max_sectors, पूर्णांक, 0);
MODULE_PARM_DESC(max_sectors,
	"Maximum number of sectors per IO command (default=128)");

/*
 * number of commands per logical unit
 */
अटल अचिन्हित पूर्णांक megaraid_cmd_per_lun = MBOX_DEF_CMD_PER_LUN;
module_param_named(cmd_per_lun, megaraid_cmd_per_lun, पूर्णांक, 0);
MODULE_PARM_DESC(cmd_per_lun,
	"Maximum number of commands per logical unit (default=64)");


/*
 * Fast driver load option, skip scanning क्रम physical devices during load.
 * This would result in non-disk devices being skipped during driver load
 * समय. These can be later added though, using /proc/scsi/scsi
 */
अटल अचिन्हित पूर्णांक megaraid_fast_load = 0;
module_param_named(fast_load, megaraid_fast_load, पूर्णांक, 0);
MODULE_PARM_DESC(fast_load,
	"Faster loading of the driver, skips physical devices! (default=0)");


/*
 * mraid_debug level - threshold क्रम amount of inक्रमmation to be displayed by
 * the driver. This level can be changed through modules parameters, ioctl or
 * sysfs/proc पूर्णांकerface. By शेष, prपूर्णांक the announcement messages only.
 */
पूर्णांक mraid_debug_level = CL_ANN;
module_param_named(debug_level, mraid_debug_level, पूर्णांक, 0);
MODULE_PARM_DESC(debug_level, "Debug level for driver (default=0)");

/*
 * PCI table क्रम all supported controllers.
 */
अटल काष्ठा pci_device_id pci_id_table_g[] =  अणु
	अणु
		PCI_VENDOR_ID_DELL,
		PCI_DEVICE_ID_PERC4_DI_DISCOVERY,
		PCI_VENDOR_ID_DELL,
		PCI_SUBSYS_ID_PERC4_DI_DISCOVERY,
	पूर्ण,
	अणु
		PCI_VENDOR_ID_LSI_LOGIC,
		PCI_DEVICE_ID_PERC4_SC,
		PCI_VENDOR_ID_DELL,
		PCI_SUBSYS_ID_PERC4_SC,
	पूर्ण,
	अणु
		PCI_VENDOR_ID_LSI_LOGIC,
		PCI_DEVICE_ID_PERC4_DC,
		PCI_VENDOR_ID_DELL,
		PCI_SUBSYS_ID_PERC4_DC,
	पूर्ण,
	अणु
		PCI_VENDOR_ID_LSI_LOGIC,
		PCI_DEVICE_ID_VERDE,
		PCI_ANY_ID,
		PCI_ANY_ID,
	पूर्ण,
	अणु
		PCI_VENDOR_ID_DELL,
		PCI_DEVICE_ID_PERC4_DI_EVERGLADES,
		PCI_VENDOR_ID_DELL,
		PCI_SUBSYS_ID_PERC4_DI_EVERGLADES,
	पूर्ण,
	अणु
		PCI_VENDOR_ID_DELL,
		PCI_DEVICE_ID_PERC4E_SI_BIGBEND,
		PCI_VENDOR_ID_DELL,
		PCI_SUBSYS_ID_PERC4E_SI_BIGBEND,
	पूर्ण,
	अणु
		PCI_VENDOR_ID_DELL,
		PCI_DEVICE_ID_PERC4E_DI_KOBUK,
		PCI_VENDOR_ID_DELL,
		PCI_SUBSYS_ID_PERC4E_DI_KOBUK,
	पूर्ण,
	अणु
		PCI_VENDOR_ID_DELL,
		PCI_DEVICE_ID_PERC4E_DI_CORVETTE,
		PCI_VENDOR_ID_DELL,
		PCI_SUBSYS_ID_PERC4E_DI_CORVETTE,
	पूर्ण,
	अणु
		PCI_VENDOR_ID_DELL,
		PCI_DEVICE_ID_PERC4E_DI_EXPEDITION,
		PCI_VENDOR_ID_DELL,
		PCI_SUBSYS_ID_PERC4E_DI_EXPEDITION,
	पूर्ण,
	अणु
		PCI_VENDOR_ID_DELL,
		PCI_DEVICE_ID_PERC4E_DI_GUADALUPE,
		PCI_VENDOR_ID_DELL,
		PCI_SUBSYS_ID_PERC4E_DI_GUADALUPE,
	पूर्ण,
	अणु
		PCI_VENDOR_ID_LSI_LOGIC,
		PCI_DEVICE_ID_DOBSON,
		PCI_ANY_ID,
		PCI_ANY_ID,
	पूर्ण,
	अणु
		PCI_VENDOR_ID_AMI,
		PCI_DEVICE_ID_AMI_MEGARAID3,
		PCI_ANY_ID,
		PCI_ANY_ID,
	पूर्ण,
	अणु
		PCI_VENDOR_ID_LSI_LOGIC,
		PCI_DEVICE_ID_AMI_MEGARAID3,
		PCI_ANY_ID,
		PCI_ANY_ID,
	पूर्ण,
	अणु
		PCI_VENDOR_ID_LSI_LOGIC,
		PCI_DEVICE_ID_LINDSAY,
		PCI_ANY_ID,
		PCI_ANY_ID,
	पूर्ण,
	अणु0पूर्ण	/* Terminating entry */
पूर्ण;
MODULE_DEVICE_TABLE(pci, pci_id_table_g);


अटल काष्ठा pci_driver megaraid_pci_driver = अणु
	.name		= "megaraid",
	.id_table	= pci_id_table_g,
	.probe		= megaraid_probe_one,
	.हटाओ		= megaraid_detach_one,
	.shutकरोwn	= megaraid_mbox_shutकरोwn,
पूर्ण;



// definitions क्रम the device attributes क्रम exporting logical drive number
// क्रम a scsi address (Host, Channel, Id, Lun)

अटल DEVICE_ATTR(megaraid_mbox_app_hndl, S_IRUSR, megaraid_sysfs_show_app_hndl,
		   शून्य);

// Host ढाँचा initializer क्रम megaraid mbox sysfs device attributes
अटल काष्ठा device_attribute *megaraid_shost_attrs[] = अणु
	&dev_attr_megaraid_mbox_app_hndl,
	शून्य,
पूर्ण;


अटल DEVICE_ATTR(megaraid_mbox_ld, S_IRUSR, megaraid_sysfs_show_ldnum, शून्य);

// Host ढाँचा initializer क्रम megaraid mbox sysfs device attributes
अटल काष्ठा device_attribute *megaraid_sdev_attrs[] = अणु
	&dev_attr_megaraid_mbox_ld,
	शून्य,
पूर्ण;

/*
 * Scsi host ढाँचा क्रम megaraid unअगरied driver
 */
अटल काष्ठा scsi_host_ढाँचा megaraid_ढाँचा_g = अणु
	.module				= THIS_MODULE,
	.name				= "LSI Logic MegaRAID driver",
	.proc_name			= "megaraid",
	.queuecommand			= megaraid_queue_command,
	.eh_पात_handler		= megaraid_पात_handler,
	.eh_host_reset_handler		= megaraid_reset_handler,
	.change_queue_depth		= scsi_change_queue_depth,
	.no_ग_लिखो_same			= 1,
	.sdev_attrs			= megaraid_sdev_attrs,
	.shost_attrs			= megaraid_shost_attrs,
पूर्ण;


/**
 * megaraid_init - module load hook
 *
 * We रेजिस्टर ourselves as hotplug enabled module and let PCI subप्रणाली
 * discover our adapters.
 */
अटल पूर्णांक __init
megaraid_init(व्योम)
अणु
	पूर्णांक	rval;

	// Announce the driver version
	con_log(CL_ANN, (KERN_INFO "megaraid: %s %s\n", MEGARAID_VERSION,
		MEGARAID_EXT_VERSION));

	// check validity of module parameters
	अगर (megaraid_cmd_per_lun > MBOX_MAX_SCSI_CMDS) अणु

		con_log(CL_ANN, (KERN_WARNING
			"megaraid mailbox: max commands per lun reset to %d\n",
			MBOX_MAX_SCSI_CMDS));

		megaraid_cmd_per_lun = MBOX_MAX_SCSI_CMDS;
	पूर्ण


	// रेजिस्टर as a PCI hot-plug driver module
	rval = pci_रेजिस्टर_driver(&megaraid_pci_driver);
	अगर (rval < 0) अणु
		con_log(CL_ANN, (KERN_WARNING
			"megaraid: could not register hotplug support.\n"));
	पूर्ण

	वापस rval;
पूर्ण


/**
 * megaraid_निकास - driver unload entry poपूर्णांक
 *
 * We simply unwrap the megaraid_init routine here.
 */
अटल व्योम __निकास
megaraid_निकास(व्योम)
अणु
	con_log(CL_DLEVEL1, (KERN_NOTICE "megaraid: unloading framework\n"));

	// unरेजिस्टर as PCI hotplug driver
	pci_unरेजिस्टर_driver(&megaraid_pci_driver);

	वापस;
पूर्ण


/**
 * megaraid_probe_one - PCI hotplug entry poपूर्णांक
 * @pdev	: handle to this controller's PCI configuration space
 * @id		: pci device id of the class of controllers
 *
 * This routine should be called whenever a new adapter is detected by the
 * PCI hotplug susbप्रणाली.
 */
अटल पूर्णांक
megaraid_probe_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	adapter_t	*adapter;


	// detected a new controller
	con_log(CL_ANN, (KERN_INFO
		"megaraid: probe new device %#4.04x:%#4.04x:%#4.04x:%#4.04x: ",
		pdev->venकरोr, pdev->device, pdev->subप्रणाली_venकरोr,
		pdev->subप्रणाली_device));

	con_log(CL_ANN, ("bus %d:slot %d:func %d\n", pdev->bus->number,
		PCI_SLOT(pdev->devfn), PCI_FUNC(pdev->devfn)));

	अगर (pci_enable_device(pdev)) अणु
		con_log(CL_ANN, (KERN_WARNING
				"megaraid: pci_enable_device failed\n"));

		वापस -ENODEV;
	पूर्ण

	// Enable bus-mastering on this controller
	pci_set_master(pdev);

	// Allocate the per driver initialization काष्ठाure
	adapter = kzalloc(माप(adapter_t), GFP_KERNEL);

	अगर (adapter == शून्य) अणु
		con_log(CL_ANN, (KERN_WARNING
		"megaraid: out of memory, %s %d.\n", __func__, __LINE__));

		जाओ out_probe_one;
	पूर्ण


	// set up PCI related soft state and other pre-known parameters
	adapter->unique_id	= pdev->bus->number << 8 | pdev->devfn;
	adapter->irq		= pdev->irq;
	adapter->pdev		= pdev;

	atomic_set(&adapter->being_detached, 0);

	// Setup the शेष DMA mask. This would be changed later on
	// depending on hardware capabilities
	अगर (dma_set_mask(&adapter->pdev->dev, DMA_BIT_MASK(32))) अणु
		con_log(CL_ANN, (KERN_WARNING
			"megaraid: dma_set_mask failed:%d\n", __LINE__));

		जाओ out_मुक्त_adapter;
	पूर्ण


	// Initialize the synchronization lock क्रम kernel and LLD
	spin_lock_init(&adapter->lock);

	// Initialize the command queues: the list of मुक्त SCBs and the list
	// of pending SCBs.
	INIT_LIST_HEAD(&adapter->kscb_pool);
	spin_lock_init(SCSI_FREE_LIST_LOCK(adapter));

	INIT_LIST_HEAD(&adapter->pend_list);
	spin_lock_init(PENDING_LIST_LOCK(adapter));

	INIT_LIST_HEAD(&adapter->completed_list);
	spin_lock_init(COMPLETED_LIST_LOCK(adapter));


	// Start the mailbox based controller
	अगर (megaraid_init_mbox(adapter) != 0) अणु
		con_log(CL_ANN, (KERN_WARNING
			"megaraid: mailbox adapter did not initialize\n"));

		जाओ out_मुक्त_adapter;
	पूर्ण

	// Register with LSI Common Management Module
	अगर (megaraid_cmm_रेजिस्टर(adapter) != 0) अणु

		con_log(CL_ANN, (KERN_WARNING
		"megaraid: could not register with management module\n"));

		जाओ out_fini_mbox;
	पूर्ण

	// setup adapter handle in PCI soft state
	pci_set_drvdata(pdev, adapter);

	// attach with scsi mid-layer
	अगर (megaraid_io_attach(adapter) != 0) अणु

		con_log(CL_ANN, (KERN_WARNING "megaraid: io attach failed\n"));

		जाओ out_cmm_unreg;
	पूर्ण

	वापस 0;

out_cmm_unreg:
	megaraid_cmm_unरेजिस्टर(adapter);
out_fini_mbox:
	megaraid_fini_mbox(adapter);
out_मुक्त_adapter:
	kमुक्त(adapter);
out_probe_one:
	pci_disable_device(pdev);

	वापस -ENODEV;
पूर्ण


/**
 * megaraid_detach_one - release framework resources and call LLD release routine
 * @pdev	: handle क्रम our PCI configuration space
 *
 * This routine is called during driver unload. We मुक्त all the allocated
 * resources and call the corresponding LLD so that it can also release all
 * its resources.
 *
 * This routine is also called from the PCI hotplug प्रणाली.
 */
अटल व्योम
megaraid_detach_one(काष्ठा pci_dev *pdev)
अणु
	adapter_t		*adapter;
	काष्ठा Scsi_Host	*host;


	// Start a rollback on this adapter
	adapter = pci_get_drvdata(pdev);

	अगर (!adapter) अणु
		con_log(CL_ANN, (KERN_CRIT
		"megaraid: Invalid detach on %#4.04x:%#4.04x:%#4.04x:%#4.04x\n",
			pdev->venकरोr, pdev->device, pdev->subप्रणाली_venकरोr,
			pdev->subप्रणाली_device));

		वापस;
	पूर्ण
	अन्यथा अणु
		con_log(CL_ANN, (KERN_NOTICE
		"megaraid: detaching device %#4.04x:%#4.04x:%#4.04x:%#4.04x\n",
			pdev->venकरोr, pdev->device, pdev->subप्रणाली_venकरोr,
			pdev->subप्रणाली_device));
	पूर्ण


	host = adapter->host;

	// करो not allow any more requests from the management module क्रम this
	// adapter.
	// FIXME: How करो we account क्रम the request which might still be
	// pending with us?
	atomic_set(&adapter->being_detached, 1);

	// detach from the IO sub-प्रणाली
	megaraid_io_detach(adapter);

	// Unरेजिस्टर from common management module
	//
	// FIXME: this must वापस success or failure क्रम conditions अगर there
	// is a command pending with LLD or not.
	megaraid_cmm_unरेजिस्टर(adapter);

	// finalize the mailbox based controller and release all resources
	megaraid_fini_mbox(adapter);

	kमुक्त(adapter);

	scsi_host_put(host);

	pci_disable_device(pdev);

	वापस;
पूर्ण


/**
 * megaraid_mbox_shutकरोwn - PCI shutकरोwn क्रम megaraid HBA
 * @pdev		: generic driver model device
 *
 * Shutकरोwn notअगरication, perक्रमm flush cache.
 */
अटल व्योम
megaraid_mbox_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	adapter_t		*adapter = pci_get_drvdata(pdev);
	अटल पूर्णांक		counter;

	अगर (!adapter) अणु
		con_log(CL_ANN, (KERN_WARNING
			"megaraid: null device in shutdown\n"));
		वापस;
	पूर्ण

	// flush caches now
	con_log(CL_ANN, (KERN_INFO "megaraid: flushing adapter %d...",
		counter++));

	megaraid_mbox_flush_cache(adapter);

	con_log(CL_ANN, ("done\n"));
पूर्ण


/**
 * megaraid_io_attach - attach a device with the IO subप्रणाली
 * @adapter		: controller's soft state
 *
 * Attach this device with the IO subप्रणाली.
 */
अटल पूर्णांक
megaraid_io_attach(adapter_t *adapter)
अणु
	काष्ठा Scsi_Host	*host;

	// Initialize SCSI Host काष्ठाure
	host = scsi_host_alloc(&megaraid_ढाँचा_g, 8);
	अगर (!host) अणु
		con_log(CL_ANN, (KERN_WARNING
			"megaraid mbox: scsi_register failed\n"));

		वापस -1;
	पूर्ण

	SCSIHOST2ADAP(host)	= (caddr_t)adapter;
	adapter->host		= host;

	host->irq		= adapter->irq;
	host->unique_id		= adapter->unique_id;
	host->can_queue		= adapter->max_cmds;
	host->this_id		= adapter->init_id;
	host->sg_tablesize	= adapter->sglen;
	host->max_sectors	= adapter->max_sectors;
	host->cmd_per_lun	= adapter->cmd_per_lun;
	host->max_channel	= adapter->max_channel;
	host->max_id		= adapter->max_target;
	host->max_lun		= adapter->max_lun;


	// notअगरy mid-layer about the new controller
	अगर (scsi_add_host(host, &adapter->pdev->dev)) अणु

		con_log(CL_ANN, (KERN_WARNING
			"megaraid mbox: scsi_add_host failed\n"));

		scsi_host_put(host);

		वापस -1;
	पूर्ण

	scsi_scan_host(host);

	वापस 0;
पूर्ण


/**
 * megaraid_io_detach - detach a device from the IO subप्रणाली
 * @adapter		: controller's soft state
 *
 * Detach this device from the IO subप्रणाली.
 */
अटल व्योम
megaraid_io_detach(adapter_t *adapter)
अणु
	काष्ठा Scsi_Host	*host;

	con_log(CL_DLEVEL1, (KERN_INFO "megaraid: io detach\n"));

	host = adapter->host;

	scsi_हटाओ_host(host);

	वापस;
पूर्ण


/*
 * START: Mailbox Low Level Driver
 *
 * This is section specअगरic to the single mailbox based controllers
 */

/**
 * megaraid_init_mbox - initialize controller
 * @adapter		: our soft state
 *
 * - Allocate 16-byte aligned mailbox memory क्रम firmware handshake
 * - Allocate controller's memory resources
 * - Find out all initialization data
 * - Allocate memory required क्रम all the commands
 * - Use पूर्णांकernal library of FW routines, build up complete soft state
 */
अटल पूर्णांक
megaraid_init_mbox(adapter_t *adapter)
अणु
	काष्ठा pci_dev		*pdev;
	mraid_device_t		*raid_dev;
	पूर्णांक			i;
	uपूर्णांक32_t		magic64;


	adapter->ito	= MBOX_TIMEOUT;
	pdev		= adapter->pdev;

	/*
	 * Allocate and initialize the init data काष्ठाure क्रम mailbox
	 * controllers
	 */
	raid_dev = kzalloc(माप(mraid_device_t), GFP_KERNEL);
	अगर (raid_dev == शून्य) वापस -1;


	/*
	 * Attach the adapter soft state to raid device soft state
	 */
	adapter->raid_device	= (caddr_t)raid_dev;
	raid_dev->fast_load	= megaraid_fast_load;


	// our baseport
	raid_dev->baseport = pci_resource_start(pdev, 0);

	अगर (pci_request_regions(pdev, "MegaRAID: LSI Logic Corporation") != 0) अणु

		con_log(CL_ANN, (KERN_WARNING
				"megaraid: mem region busy\n"));

		जाओ out_मुक्त_raid_dev;
	पूर्ण

	raid_dev->baseaddr = ioremap(raid_dev->baseport, 128);

	अगर (!raid_dev->baseaddr) अणु

		con_log(CL_ANN, (KERN_WARNING
			"megaraid: could not map hba memory\n") );

		जाओ out_release_regions;
	पूर्ण

	/* initialize the mutual exclusion lock क्रम the mailbox */
	spin_lock_init(&raid_dev->mailbox_lock);

	/* allocate memory required क्रम commands */
	अगर (megaraid_alloc_cmd_packets(adapter) != 0)
		जाओ out_iounmap;

	/*
	 * Issue SYNC cmd to flush the pending cmds in the adapter
	 * and initialize its पूर्णांकernal state
	 */

	अगर (megaraid_mbox_fire_sync_cmd(adapter))
		con_log(CL_ANN, ("megaraid: sync cmd failed\n"));

	/*
	 * Setup the rest of the soft state using the library of
	 * FW routines
	 */

	/* request IRQ and रेजिस्टर the पूर्णांकerrupt service routine */
	अगर (request_irq(adapter->irq, megaraid_isr, IRQF_SHARED, "megaraid",
		adapter)) अणु

		con_log(CL_ANN, (KERN_WARNING
			"megaraid: Couldn't register IRQ %d!\n", adapter->irq));
		जाओ out_alloc_cmds;

	पूर्ण

	// Product info
	अगर (megaraid_mbox_product_info(adapter) != 0)
		जाओ out_मुक्त_irq;

	// Do we support extended CDBs
	adapter->max_cdb_sz = 10;
	अगर (megaraid_mbox_extended_cdb(adapter) == 0) अणु
		adapter->max_cdb_sz = 16;
	पूर्ण

	/*
	 * Do we support cluster environment, अगर we करो, what is the initiator
	 * id.
	 * NOTE: In a non-cluster aware firmware environment, the LLD should
	 * वापस 7 as initiator id.
	 */
	adapter->ha		= 0;
	adapter->init_id	= -1;
	अगर (megaraid_mbox_support_ha(adapter, &adapter->init_id) == 0) अणु
		adapter->ha = 1;
	पूर्ण

	/*
	 * Prepare the device ids array to have the mapping between the kernel
	 * device address and megaraid device address.
	 * We export the physical devices on their actual addresses. The
	 * logical drives are exported on a भव SCSI channel
	 */
	megaraid_mbox_setup_device_map(adapter);

	// If the firmware supports अक्रमom deletion, update the device id map
	अगर (megaraid_mbox_support_अक्रमom_del(adapter)) अणु

		// Change the logical drives numbers in device_ids array one
		// slot in device_ids is reserved क्रम target id, that's why
		// "<=" below
		क्रम (i = 0; i <= MAX_LOGICAL_DRIVES_40LD; i++) अणु
			adapter->device_ids[adapter->max_channel][i] += 0x80;
		पूर्ण
		adapter->device_ids[adapter->max_channel][adapter->init_id] =
			0xFF;

		raid_dev->अक्रमom_del_supported = 1;
	पूर्ण

	/*
	 * find out the maximum number of scatter-gather elements supported by
	 * this firmware
	 */
	adapter->sglen = megaraid_mbox_get_max_sg(adapter);

	// क्रमागतerate RAID and SCSI channels so that all devices on SCSI
	// channels can later be exported, including disk devices
	megaraid_mbox_क्रमागत_raid_scsi(adapter);

	/*
	 * Other parameters required by upper layer
	 *
	 * maximum number of sectors per IO command
	 */
	adapter->max_sectors = megaraid_max_sectors;

	/*
	 * number of queued commands per LUN.
	 */
	adapter->cmd_per_lun = megaraid_cmd_per_lun;

	/*
	 * Allocate resources required to issue FW calls, when sysfs is
	 * accessed
	 */
	अगर (megaraid_sysfs_alloc_resources(adapter) != 0)
		जाओ out_मुक्त_irq;

	// Set the DMA mask to 64-bit. All supported controllers as capable of
	// DMA in this range
	pci_पढ़ो_config_dword(adapter->pdev, PCI_CONF_AMISIG64, &magic64);

	अगर (((magic64 == HBA_SIGNATURE_64_BIT) &&
		((adapter->pdev->subप्रणाली_device !=
		PCI_SUBSYS_ID_MEGARAID_SATA_150_6) &&
		(adapter->pdev->subप्रणाली_device !=
		PCI_SUBSYS_ID_MEGARAID_SATA_150_4))) ||
		(adapter->pdev->venकरोr == PCI_VENDOR_ID_LSI_LOGIC &&
		adapter->pdev->device == PCI_DEVICE_ID_VERDE) ||
		(adapter->pdev->venकरोr == PCI_VENDOR_ID_LSI_LOGIC &&
		adapter->pdev->device == PCI_DEVICE_ID_DOBSON) ||
		(adapter->pdev->venकरोr == PCI_VENDOR_ID_LSI_LOGIC &&
		adapter->pdev->device == PCI_DEVICE_ID_LINDSAY) ||
		(adapter->pdev->venकरोr == PCI_VENDOR_ID_DELL &&
		adapter->pdev->device == PCI_DEVICE_ID_PERC4_DI_EVERGLADES) ||
		(adapter->pdev->venकरोr == PCI_VENDOR_ID_DELL &&
		adapter->pdev->device == PCI_DEVICE_ID_PERC4E_DI_KOBUK)) अणु
		अगर (dma_set_mask(&adapter->pdev->dev, DMA_BIT_MASK(64))) अणु
			con_log(CL_ANN, (KERN_WARNING
				"megaraid: DMA mask for 64-bit failed\n"));

			अगर (dma_set_mask(&adapter->pdev->dev,
						DMA_BIT_MASK(32))) अणु
				con_log(CL_ANN, (KERN_WARNING
					"megaraid: 32-bit DMA mask failed\n"));
				जाओ out_मुक्त_sysfs_res;
			पूर्ण
		पूर्ण
	पूर्ण

	// setup tasklet क्रम DPC
	tasklet_init(&adapter->dpc_h, megaraid_mbox_dpc,
			(अचिन्हित दीर्घ)adapter);

	con_log(CL_DLEVEL1, (KERN_INFO
		"megaraid mbox hba successfully initialized\n"));

	वापस 0;

out_मुक्त_sysfs_res:
	megaraid_sysfs_मुक्त_resources(adapter);
out_मुक्त_irq:
	मुक्त_irq(adapter->irq, adapter);
out_alloc_cmds:
	megaraid_मुक्त_cmd_packets(adapter);
out_iounmap:
	iounmap(raid_dev->baseaddr);
out_release_regions:
	pci_release_regions(pdev);
out_मुक्त_raid_dev:
	kमुक्त(raid_dev);

	वापस -1;
पूर्ण


/**
 * megaraid_fini_mbox - unकरो controller initialization
 * @adapter		: our soft state
 */
अटल व्योम
megaraid_fini_mbox(adapter_t *adapter)
अणु
	mraid_device_t *raid_dev = ADAP2RAIDDEV(adapter);

	// flush all caches
	megaraid_mbox_flush_cache(adapter);

	tasklet_समाप्त(&adapter->dpc_h);

	megaraid_sysfs_मुक्त_resources(adapter);

	megaraid_मुक्त_cmd_packets(adapter);

	मुक्त_irq(adapter->irq, adapter);

	iounmap(raid_dev->baseaddr);

	pci_release_regions(adapter->pdev);

	kमुक्त(raid_dev);

	वापस;
पूर्ण


/**
 * megaraid_alloc_cmd_packets - allocate shared mailbox
 * @adapter		: soft state of the raid controller
 *
 * Allocate and align the shared mailbox. This mailbox is used to issue
 * all the commands. For IO based controllers, the mailbox is also रेजिस्टरed
 * with the FW. Allocate memory क्रम all commands as well.
 * This is our big allocator.
 */
अटल पूर्णांक
megaraid_alloc_cmd_packets(adapter_t *adapter)
अणु
	mraid_device_t		*raid_dev = ADAP2RAIDDEV(adapter);
	काष्ठा pci_dev		*pdev;
	अचिन्हित दीर्घ		align;
	scb_t			*scb;
	mbox_ccb_t		*ccb;
	काष्ठा mraid_pci_blk	*epthru_pci_blk;
	काष्ठा mraid_pci_blk	*sg_pci_blk;
	काष्ठा mraid_pci_blk	*mbox_pci_blk;
	पूर्णांक			i;

	pdev = adapter->pdev;

	/*
	 * Setup the mailbox
	 * Allocate the common 16-byte aligned memory क्रम the handshake
	 * mailbox.
	 */
	raid_dev->una_mbox64 = dma_alloc_coherent(&adapter->pdev->dev,
						  माप(mbox64_t),
						  &raid_dev->una_mbox64_dma,
						  GFP_KERNEL);

	अगर (!raid_dev->una_mbox64) अणु
		con_log(CL_ANN, (KERN_WARNING
			"megaraid: out of memory, %s %d\n", __func__,
			__LINE__));
		वापस -1;
	पूर्ण

	/*
	 * Align the mailbox at 16-byte boundary
	 */
	raid_dev->mbox	= &raid_dev->una_mbox64->mbox32;

	raid_dev->mbox	= (mbox_t *)((((अचिन्हित दीर्घ)raid_dev->mbox) + 15) &
				(~0UL ^ 0xFUL));

	raid_dev->mbox64 = (mbox64_t *)(((अचिन्हित दीर्घ)raid_dev->mbox) - 8);

	align = ((व्योम *)raid_dev->mbox -
			((व्योम *)&raid_dev->una_mbox64->mbox32));

	raid_dev->mbox_dma = (अचिन्हित दीर्घ)raid_dev->una_mbox64_dma + 8 +
			align;

	// Allocate memory क्रम commands issued पूर्णांकernally
	adapter->ibuf = dma_alloc_coherent(&pdev->dev, MBOX_IBUF_SIZE,
					   &adapter->ibuf_dma_h, GFP_KERNEL);
	अगर (!adapter->ibuf) अणु

		con_log(CL_ANN, (KERN_WARNING
			"megaraid: out of memory, %s %d\n", __func__,
			__LINE__));

		जाओ out_मुक्त_common_mbox;
	पूर्ण

	// Allocate memory क्रम our SCSI Command Blocks and their associated
	// memory

	/*
	 * Allocate memory क्रम the base list of scb. Later allocate memory क्रम
	 * CCBs and embedded components of each CCB and poपूर्णांक the poपूर्णांकers in
	 * scb to the allocated components
	 * NOTE: The code to allocate SCB will be duplicated in all the LLD
	 * since the calling routine करोes not yet know the number of available
	 * commands.
	 */
	adapter->kscb_list = kसुस्मृति(MBOX_MAX_SCSI_CMDS, माप(scb_t), GFP_KERNEL);

	अगर (adapter->kscb_list == शून्य) अणु
		con_log(CL_ANN, (KERN_WARNING
			"megaraid: out of memory, %s %d\n", __func__,
			__LINE__));
		जाओ out_मुक्त_ibuf;
	पूर्ण

	// memory allocation क्रम our command packets
	अगर (megaraid_mbox_setup_dma_pools(adapter) != 0) अणु
		con_log(CL_ANN, (KERN_WARNING
			"megaraid: out of memory, %s %d\n", __func__,
			__LINE__));
		जाओ out_मुक्त_scb_list;
	पूर्ण

	// Adjust the scb poपूर्णांकers and link in the मुक्त pool
	epthru_pci_blk	= raid_dev->epthru_pool;
	sg_pci_blk	= raid_dev->sg_pool;
	mbox_pci_blk	= raid_dev->mbox_pool;

	क्रम (i = 0; i < MBOX_MAX_SCSI_CMDS; i++) अणु
		scb			= adapter->kscb_list + i;
		ccb			= raid_dev->ccb_list + i;

		ccb->mbox	= (mbox_t *)(mbox_pci_blk[i].vaddr + 16);
		ccb->raw_mbox	= (uपूर्णांक8_t *)ccb->mbox;
		ccb->mbox64	= (mbox64_t *)(mbox_pci_blk[i].vaddr + 8);
		ccb->mbox_dma_h	= (अचिन्हित दीर्घ)mbox_pci_blk[i].dma_addr + 16;

		// make sure the mailbox is aligned properly
		अगर (ccb->mbox_dma_h & 0x0F) अणु
			con_log(CL_ANN, (KERN_CRIT
				"megaraid mbox: not aligned on 16-bytes\n"));

			जाओ out_tearकरोwn_dma_pools;
		पूर्ण

		ccb->epthru		= (mraid_epassthru_t *)
						epthru_pci_blk[i].vaddr;
		ccb->epthru_dma_h	= epthru_pci_blk[i].dma_addr;
		ccb->pthru		= (mraid_passthru_t *)ccb->epthru;
		ccb->pthru_dma_h	= ccb->epthru_dma_h;


		ccb->sgl64		= (mbox_sgl64 *)sg_pci_blk[i].vaddr;
		ccb->sgl_dma_h		= sg_pci_blk[i].dma_addr;
		ccb->sgl32		= (mbox_sgl32 *)ccb->sgl64;

		scb->ccb		= (caddr_t)ccb;
		scb->gp			= 0;

		scb->sno		= i;	// command index

		scb->scp		= शून्य;
		scb->state		= SCB_FREE;
		scb->dma_direction	= DMA_NONE;
		scb->dma_type		= MRAID_DMA_NONE;
		scb->dev_channel	= -1;
		scb->dev_target		= -1;

		// put scb in the मुक्त pool
		list_add_tail(&scb->list, &adapter->kscb_pool);
	पूर्ण

	वापस 0;

out_tearकरोwn_dma_pools:
	megaraid_mbox_tearकरोwn_dma_pools(adapter);
out_मुक्त_scb_list:
	kमुक्त(adapter->kscb_list);
out_मुक्त_ibuf:
	dma_मुक्त_coherent(&pdev->dev, MBOX_IBUF_SIZE, (व्योम *)adapter->ibuf,
		adapter->ibuf_dma_h);
out_मुक्त_common_mbox:
	dma_मुक्त_coherent(&adapter->pdev->dev, माप(mbox64_t),
		(caddr_t)raid_dev->una_mbox64, raid_dev->una_mbox64_dma);

	वापस -1;
पूर्ण


/**
 * megaraid_मुक्त_cmd_packets - मुक्त memory
 * @adapter		: soft state of the raid controller
 *
 * Release memory resources allocated क्रम commands.
 */
अटल व्योम
megaraid_मुक्त_cmd_packets(adapter_t *adapter)
अणु
	mraid_device_t *raid_dev = ADAP2RAIDDEV(adapter);

	megaraid_mbox_tearकरोwn_dma_pools(adapter);

	kमुक्त(adapter->kscb_list);

	dma_मुक्त_coherent(&adapter->pdev->dev, MBOX_IBUF_SIZE,
		(व्योम *)adapter->ibuf, adapter->ibuf_dma_h);

	dma_मुक्त_coherent(&adapter->pdev->dev, माप(mbox64_t),
		(caddr_t)raid_dev->una_mbox64, raid_dev->una_mbox64_dma);
	वापस;
पूर्ण


/**
 * megaraid_mbox_setup_dma_pools - setup dma pool क्रम command packets
 * @adapter		: HBA soft state
 *
 * Setup the dma pools क्रम mailbox, passthru and extended passthru काष्ठाures,
 * and scatter-gather lists.
 */
अटल पूर्णांक
megaraid_mbox_setup_dma_pools(adapter_t *adapter)
अणु
	mraid_device_t		*raid_dev = ADAP2RAIDDEV(adapter);
	काष्ठा mraid_pci_blk	*epthru_pci_blk;
	काष्ठा mraid_pci_blk	*sg_pci_blk;
	काष्ठा mraid_pci_blk	*mbox_pci_blk;
	पूर्णांक			i;



	// Allocate memory क्रम 16-bytes aligned mailboxes
	raid_dev->mbox_pool_handle = dma_pool_create("megaraid mbox pool",
						&adapter->pdev->dev,
						माप(mbox64_t) + 16,
						16, 0);

	अगर (raid_dev->mbox_pool_handle == शून्य) अणु
		जाओ fail_setup_dma_pool;
	पूर्ण

	mbox_pci_blk = raid_dev->mbox_pool;
	क्रम (i = 0; i < MBOX_MAX_SCSI_CMDS; i++) अणु
		mbox_pci_blk[i].vaddr = dma_pool_alloc(
						raid_dev->mbox_pool_handle,
						GFP_KERNEL,
						&mbox_pci_blk[i].dma_addr);
		अगर (!mbox_pci_blk[i].vaddr) अणु
			जाओ fail_setup_dma_pool;
		पूर्ण
	पूर्ण

	/*
	 * Allocate memory क्रम each embedded passthru strucuture poपूर्णांकer
	 * Request क्रम a 128 bytes aligned काष्ठाure क्रम each passthru command
	 * काष्ठाure
	 * Since passthru and extended passthru commands are exclusive, they
	 * share common memory pool. Passthru काष्ठाures piggyback on memory
	 * allocated to extended passthru since passthru is smaller of the two
	 */
	raid_dev->epthru_pool_handle = dma_pool_create("megaraid mbox pthru",
			&adapter->pdev->dev, माप(mraid_epassthru_t), 128, 0);

	अगर (raid_dev->epthru_pool_handle == शून्य) अणु
		जाओ fail_setup_dma_pool;
	पूर्ण

	epthru_pci_blk = raid_dev->epthru_pool;
	क्रम (i = 0; i < MBOX_MAX_SCSI_CMDS; i++) अणु
		epthru_pci_blk[i].vaddr = dma_pool_alloc(
						raid_dev->epthru_pool_handle,
						GFP_KERNEL,
						&epthru_pci_blk[i].dma_addr);
		अगर (!epthru_pci_blk[i].vaddr) अणु
			जाओ fail_setup_dma_pool;
		पूर्ण
	पूर्ण


	// Allocate memory क्रम each scatter-gather list. Request क्रम 512 bytes
	// alignment क्रम each sg list
	raid_dev->sg_pool_handle = dma_pool_create("megaraid mbox sg",
					&adapter->pdev->dev,
					माप(mbox_sgl64) * MBOX_MAX_SG_SIZE,
					512, 0);

	अगर (raid_dev->sg_pool_handle == शून्य) अणु
		जाओ fail_setup_dma_pool;
	पूर्ण

	sg_pci_blk = raid_dev->sg_pool;
	क्रम (i = 0; i < MBOX_MAX_SCSI_CMDS; i++) अणु
		sg_pci_blk[i].vaddr = dma_pool_alloc(
						raid_dev->sg_pool_handle,
						GFP_KERNEL,
						&sg_pci_blk[i].dma_addr);
		अगर (!sg_pci_blk[i].vaddr) अणु
			जाओ fail_setup_dma_pool;
		पूर्ण
	पूर्ण

	वापस 0;

fail_setup_dma_pool:
	megaraid_mbox_tearकरोwn_dma_pools(adapter);
	वापस -1;
पूर्ण


/**
 * megaraid_mbox_tearकरोwn_dma_pools - tearकरोwn dma pools क्रम command packets
 * @adapter		: HBA soft state
 *
 * Tearकरोwn the dma pool क्रम mailbox, passthru and extended passthru
 * काष्ठाures, and scatter-gather lists.
 */
अटल व्योम
megaraid_mbox_tearकरोwn_dma_pools(adapter_t *adapter)
अणु
	mraid_device_t		*raid_dev = ADAP2RAIDDEV(adapter);
	काष्ठा mraid_pci_blk	*epthru_pci_blk;
	काष्ठा mraid_pci_blk	*sg_pci_blk;
	काष्ठा mraid_pci_blk	*mbox_pci_blk;
	पूर्णांक			i;


	sg_pci_blk = raid_dev->sg_pool;
	क्रम (i = 0; i < MBOX_MAX_SCSI_CMDS && sg_pci_blk[i].vaddr; i++) अणु
		dma_pool_मुक्त(raid_dev->sg_pool_handle, sg_pci_blk[i].vaddr,
			sg_pci_blk[i].dma_addr);
	पूर्ण
	dma_pool_destroy(raid_dev->sg_pool_handle);


	epthru_pci_blk = raid_dev->epthru_pool;
	क्रम (i = 0; i < MBOX_MAX_SCSI_CMDS && epthru_pci_blk[i].vaddr; i++) अणु
		dma_pool_मुक्त(raid_dev->epthru_pool_handle,
			epthru_pci_blk[i].vaddr, epthru_pci_blk[i].dma_addr);
	पूर्ण
	dma_pool_destroy(raid_dev->epthru_pool_handle);


	mbox_pci_blk = raid_dev->mbox_pool;
	क्रम (i = 0; i < MBOX_MAX_SCSI_CMDS && mbox_pci_blk[i].vaddr; i++) अणु
		dma_pool_मुक्त(raid_dev->mbox_pool_handle,
			mbox_pci_blk[i].vaddr, mbox_pci_blk[i].dma_addr);
	पूर्ण
	dma_pool_destroy(raid_dev->mbox_pool_handle);

	वापस;
पूर्ण


/**
 * megaraid_alloc_scb - detach and वापस a scb from the मुक्त list
 * @adapter	: controller's soft state
 * @scp		: poपूर्णांकer to the scsi command to be executed
 *
 * Return the scb from the head of the मुक्त list. %शून्य अगर there are none
 * available.
 */
अटल scb_t *
megaraid_alloc_scb(adapter_t *adapter, काष्ठा scsi_cmnd *scp)
अणु
	काष्ठा list_head	*head = &adapter->kscb_pool;
	scb_t			*scb = शून्य;
	अचिन्हित दीर्घ		flags;

	// detach scb from मुक्त pool
	spin_lock_irqsave(SCSI_FREE_LIST_LOCK(adapter), flags);

	अगर (list_empty(head)) अणु
		spin_unlock_irqrestore(SCSI_FREE_LIST_LOCK(adapter), flags);
		वापस शून्य;
	पूर्ण

	scb = list_entry(head->next, scb_t, list);
	list_del_init(&scb->list);

	spin_unlock_irqrestore(SCSI_FREE_LIST_LOCK(adapter), flags);

	scb->state	= SCB_ACTIVE;
	scb->scp	= scp;
	scb->dma_type	= MRAID_DMA_NONE;

	वापस scb;
पूर्ण


/**
 * megaraid_dealloc_scb - वापस the scb to the मुक्त pool
 * @adapter	: controller's soft state
 * @scb		: scb to be मुक्तd
 *
 * Return the scb back to the मुक्त list of scbs. The caller must 'flush' the
 * SCB beक्रमe calling us. E.g., perक्रमming pci_unamp and/or pci_sync etc.
 * NOTE NOTE: Make sure the scb is not on any list beक्रमe calling this
 * routine.
 */
अटल अंतरभूत व्योम
megaraid_dealloc_scb(adapter_t *adapter, scb_t *scb)
अणु
	अचिन्हित दीर्घ		flags;

	// put scb in the मुक्त pool
	scb->state	= SCB_FREE;
	scb->scp	= शून्य;
	spin_lock_irqsave(SCSI_FREE_LIST_LOCK(adapter), flags);

	list_add(&scb->list, &adapter->kscb_pool);

	spin_unlock_irqrestore(SCSI_FREE_LIST_LOCK(adapter), flags);

	वापस;
पूर्ण


/**
 * megaraid_mbox_mksgl - make the scatter-gather list
 * @adapter	: controller's soft state
 * @scb		: scsi control block
 *
 * Prepare the scatter-gather list.
 */
अटल पूर्णांक
megaraid_mbox_mksgl(adapter_t *adapter, scb_t *scb)
अणु
	काष्ठा scatterlist	*sgl;
	mbox_ccb_t		*ccb;
	काष्ठा scsi_cmnd	*scp;
	पूर्णांक			sgcnt;
	पूर्णांक			i;


	scp	= scb->scp;
	ccb	= (mbox_ccb_t *)scb->ccb;

	sgcnt = scsi_dma_map(scp);
	BUG_ON(sgcnt < 0 || sgcnt > adapter->sglen);

	// no mapping required अगर no data to be transferred
	अगर (!sgcnt)
		वापस 0;

	scb->dma_type = MRAID_DMA_WSG;

	scsi_क्रम_each_sg(scp, sgl, sgcnt, i) अणु
		ccb->sgl64[i].address	= sg_dma_address(sgl);
		ccb->sgl64[i].length	= sg_dma_len(sgl);
	पूर्ण

	// Return count of SG nodes
	वापस sgcnt;
पूर्ण


/**
 * mbox_post_cmd - issue a mailbox command
 * @adapter	: controller's soft state
 * @scb		: command to be issued
 *
 * Post the command to the controller अगर mailbox is available.
 */
अटल पूर्णांक
mbox_post_cmd(adapter_t *adapter, scb_t *scb)
अणु
	mraid_device_t	*raid_dev = ADAP2RAIDDEV(adapter);
	mbox64_t	*mbox64;
	mbox_t		*mbox;
	mbox_ccb_t	*ccb;
	अचिन्हित दीर्घ	flags;
	अचिन्हित पूर्णांक	i = 0;


	ccb	= (mbox_ccb_t *)scb->ccb;
	mbox	= raid_dev->mbox;
	mbox64	= raid_dev->mbox64;

	/*
	 * Check क्रम busy mailbox. If it is, वापस failure - the caller
	 * should retry later.
	 */
	spin_lock_irqsave(MAILBOX_LOCK(raid_dev), flags);

	अगर (unlikely(mbox->busy)) अणु
		करो अणु
			udelay(1);
			i++;
			rmb();
		पूर्ण जबतक(mbox->busy && (i < max_mbox_busy_रुको));

		अगर (mbox->busy) अणु

			spin_unlock_irqrestore(MAILBOX_LOCK(raid_dev), flags);

			वापस -1;
		पूर्ण
	पूर्ण


	// Copy this command's mailbox data into "adapter's" mailbox
	स_नकल((caddr_t)mbox64, (caddr_t)ccb->mbox64, 22);
	mbox->cmdid = scb->sno;

	adapter->outstanding_cmds++;

	mbox->busy	= 1;	// Set busy
	mbox->poll	= 0;
	mbox->ack	= 0;
	wmb();

	WRINDOOR(raid_dev, raid_dev->mbox_dma | 0x1);

	spin_unlock_irqrestore(MAILBOX_LOCK(raid_dev), flags);

	वापस 0;
पूर्ण


/**
 * megaraid_queue_command_lck - generic queue entry poपूर्णांक क्रम all LLDs
 * @scp		: poपूर्णांकer to the scsi command to be executed
 * @करोne	: callback routine to be called after the cmd has be completed
 *
 * Queue entry poपूर्णांक क्रम mailbox based controllers.
 */
अटल पूर्णांक
megaraid_queue_command_lck(काष्ठा scsi_cmnd *scp, व्योम (*करोne)(काष्ठा scsi_cmnd *))
अणु
	adapter_t	*adapter;
	scb_t		*scb;
	पूर्णांक		अगर_busy;

	adapter		= SCP2ADAPTER(scp);
	scp->scsi_करोne	= करोne;
	scp->result	= 0;

	/*
	 * Allocate and build a SCB request
	 * अगर_busy flag will be set अगर megaraid_mbox_build_cmd() command could
	 * not allocate scb. We will वापस non-zero status in that हाल.
	 * NOTE: scb can be null even though certain commands completed
	 * successfully, e.g., MODE_SENSE and TEST_UNIT_READY, it would
	 * वापस 0 in that हाल, and we would करो the callback right away.
	 */
	अगर_busy	= 0;
	scb = megaraid_mbox_build_cmd(adapter, scp, &अगर_busy);
	अगर (!scb) अणु	// command alपढ़ोy completed
		करोne(scp);
		वापस 0;
	पूर्ण

	megaraid_mbox_runpendq(adapter, scb);
	वापस अगर_busy;
पूर्ण

अटल DEF_SCSI_QCMD(megaraid_queue_command)

/**
 * megaraid_mbox_build_cmd - transक्रमm the mid-layer scsi commands
 * @adapter	: controller's soft state
 * @scp		: mid-layer scsi command poपूर्णांकer
 * @busy	: set अगर request could not be completed because of lack of
 *		resources
 *
 * Transक्रमm the mid-layer scsi command to megaraid firmware lingua.
 * Convert the command issued by mid-layer to क्रमmat understood by megaraid
 * firmware. We also complete certain commands without sending them to firmware.
 */
अटल scb_t *
megaraid_mbox_build_cmd(adapter_t *adapter, काष्ठा scsi_cmnd *scp, पूर्णांक *busy)
अणु
	mraid_device_t		*rdev = ADAP2RAIDDEV(adapter);
	पूर्णांक			channel;
	पूर्णांक			target;
	पूर्णांक			islogical;
	mbox_ccb_t		*ccb;
	mraid_passthru_t	*pthru;
	mbox64_t		*mbox64;
	mbox_t			*mbox;
	scb_t			*scb;
	अक्षर			skip[] = "skipping";
	अक्षर			scan[] = "scanning";
	अक्षर			*ss;


	/*
	 * Get the appropriate device map क्रम the device this command is
	 * पूर्णांकended क्रम
	 */
	MRAID_GET_DEVICE_MAP(adapter, scp, channel, target, islogical);

	/*
	 * Logical drive commands
	 */
	अगर (islogical) अणु
		चयन (scp->cmnd[0]) अणु
		हाल TEST_UNIT_READY:
			/*
			 * Do we support clustering and is the support enabled
			 * If no, वापस success always
			 */
			अगर (!adapter->ha) अणु
				scp->result = (DID_OK << 16);
				वापस शून्य;
			पूर्ण

			अगर (!(scb = megaraid_alloc_scb(adapter, scp))) अणु
				scp->result = (DID_ERROR << 16);
				*busy = 1;
				वापस शून्य;
			पूर्ण

			scb->dma_direction	= scp->sc_data_direction;
			scb->dev_channel	= 0xFF;
			scb->dev_target		= target;
			ccb			= (mbox_ccb_t *)scb->ccb;

			/*
			 * The command id will be provided by the command
			 * issuance routine
			 */
			ccb->raw_mbox[0]	= CLUSTER_CMD;
			ccb->raw_mbox[2]	= RESERVATION_STATUS;
			ccb->raw_mbox[3]	= target;

			वापस scb;

		हाल MODE_SENSE:
		अणु
			काष्ठा scatterlist	*sgl;
			caddr_t			vaddr;

			sgl = scsi_sglist(scp);
			अगर (sg_page(sgl)) अणु
				vaddr = (caddr_t) sg_virt(&sgl[0]);

				स_रखो(vaddr, 0, scp->cmnd[4]);
			पूर्ण
			अन्यथा अणु
				con_log(CL_ANN, (KERN_WARNING
						 "megaraid mailbox: invalid sg:%d\n",
						 __LINE__));
			पूर्ण
		पूर्ण
		scp->result = (DID_OK << 16);
		वापस शून्य;

		हाल INQUIRY:
			/*
			 * Display the channel scan क्रम logical drives
			 * Do not display scan क्रम a channel अगर alपढ़ोy करोne.
			 */
			अगर (!(rdev->last_disp & (1L << SCP2CHANNEL(scp)))) अणु

				con_log(CL_ANN, (KERN_INFO
					"scsi[%d]: scanning scsi channel %d",
					adapter->host->host_no,
					SCP2CHANNEL(scp)));

				con_log(CL_ANN, (
					" [virtual] for logical drives\n"));

				rdev->last_disp |= (1L << SCP2CHANNEL(scp));
			पूर्ण

			अगर (scp->cmnd[1] & MEGA_SCSI_INQ_EVPD) अणु
				scp->sense_buffer[0] = 0x70;
				scp->sense_buffer[2] = ILLEGAL_REQUEST;
				scp->sense_buffer[12] = MEGA_INVALID_FIELD_IN_CDB;
				scp->result = CHECK_CONDITION << 1;
				वापस शून्य;
			पूर्ण

			fallthrough;

		हाल READ_CAPACITY:
			/*
			 * Do not allow LUN > 0 क्रम logical drives and
			 * requests क्रम more than 40 logical drives
			 */
			अगर (SCP2LUN(scp)) अणु
				scp->result = (DID_BAD_TARGET << 16);
				वापस शून्य;
			पूर्ण
			अगर ((target % 0x80) >= MAX_LOGICAL_DRIVES_40LD) अणु
				scp->result = (DID_BAD_TARGET << 16);
				वापस शून्य;
			पूर्ण


			/* Allocate a SCB and initialize passthru */
			अगर (!(scb = megaraid_alloc_scb(adapter, scp))) अणु
				scp->result = (DID_ERROR << 16);
				*busy = 1;
				वापस शून्य;
			पूर्ण

			ccb			= (mbox_ccb_t *)scb->ccb;
			scb->dev_channel	= 0xFF;
			scb->dev_target		= target;
			pthru			= ccb->pthru;
			mbox			= ccb->mbox;
			mbox64			= ccb->mbox64;

			pthru->समयout		= 0;
			pthru->ars		= 1;
			pthru->reqsenselen	= 14;
			pthru->islogical	= 1;
			pthru->logdrv		= target;
			pthru->cdblen		= scp->cmd_len;
			स_नकल(pthru->cdb, scp->cmnd, scp->cmd_len);

			mbox->cmd		= MBOXCMD_PASSTHRU64;
			scb->dma_direction	= scp->sc_data_direction;

			pthru->dataxferlen	= scsi_bufflen(scp);
			pthru->dataxferaddr	= ccb->sgl_dma_h;
			pthru->numsge		= megaraid_mbox_mksgl(adapter,
							scb);

			mbox->xferaddr		= 0xFFFFFFFF;
			mbox64->xferaddr_lo	= (uपूर्णांक32_t )ccb->pthru_dma_h;
			mbox64->xferaddr_hi	= 0;

			वापस scb;

		हाल READ_6:
		हाल WRITE_6:
		हाल READ_10:
		हाल WRITE_10:
		हाल READ_12:
		हाल WRITE_12:

			/*
			 * Allocate a SCB and initialize mailbox
			 */
			अगर (!(scb = megaraid_alloc_scb(adapter, scp))) अणु
				scp->result = (DID_ERROR << 16);
				*busy = 1;
				वापस शून्य;
			पूर्ण
			ccb			= (mbox_ccb_t *)scb->ccb;
			scb->dev_channel	= 0xFF;
			scb->dev_target		= target;
			mbox			= ccb->mbox;
			mbox64			= ccb->mbox64;
			mbox->logdrv		= target;

			/*
			 * A little HACK: 2nd bit is zero क्रम all scsi पढ़ो
			 * commands and is set क्रम all scsi ग_लिखो commands
			 */
			mbox->cmd = (scp->cmnd[0] & 0x02) ?  MBOXCMD_LWRITE64:
					MBOXCMD_LREAD64 ;

			/*
			 * 6-byte READ(0x08) or WRITE(0x0A) cdb
			 */
			अगर (scp->cmd_len == 6) अणु
				mbox->numsectors = (uपूर्णांक32_t)scp->cmnd[4];
				mbox->lba =
					((uपूर्णांक32_t)scp->cmnd[1] << 16)	|
					((uपूर्णांक32_t)scp->cmnd[2] << 8)	|
					(uपूर्णांक32_t)scp->cmnd[3];

				mbox->lba &= 0x1FFFFF;
			पूर्ण

			/*
			 * 10-byte READ(0x28) or WRITE(0x2A) cdb
			 */
			अन्यथा अगर (scp->cmd_len == 10) अणु
				mbox->numsectors =
					(uपूर्णांक32_t)scp->cmnd[8] |
					((uपूर्णांक32_t)scp->cmnd[7] << 8);
				mbox->lba =
					((uपूर्णांक32_t)scp->cmnd[2] << 24) |
					((uपूर्णांक32_t)scp->cmnd[3] << 16) |
					((uपूर्णांक32_t)scp->cmnd[4] << 8) |
					(uपूर्णांक32_t)scp->cmnd[5];
			पूर्ण

			/*
			 * 12-byte READ(0xA8) or WRITE(0xAA) cdb
			 */
			अन्यथा अगर (scp->cmd_len == 12) अणु
				mbox->lba =
					((uपूर्णांक32_t)scp->cmnd[2] << 24) |
					((uपूर्णांक32_t)scp->cmnd[3] << 16) |
					((uपूर्णांक32_t)scp->cmnd[4] << 8) |
					(uपूर्णांक32_t)scp->cmnd[5];

				mbox->numsectors =
					((uपूर्णांक32_t)scp->cmnd[6] << 24) |
					((uपूर्णांक32_t)scp->cmnd[7] << 16) |
					((uपूर्णांक32_t)scp->cmnd[8] << 8) |
					(uपूर्णांक32_t)scp->cmnd[9];
			पूर्ण
			अन्यथा अणु
				con_log(CL_ANN, (KERN_WARNING
					"megaraid: unsupported CDB length\n"));

				megaraid_dealloc_scb(adapter, scb);

				scp->result = (DID_ERROR << 16);
				वापस शून्य;
			पूर्ण

			scb->dma_direction = scp->sc_data_direction;

			// Calculate Scatter-Gather info
			mbox64->xferaddr_lo	= (uपूर्णांक32_t )ccb->sgl_dma_h;
			mbox->numsge		= megaraid_mbox_mksgl(adapter,
							scb);
			mbox->xferaddr		= 0xFFFFFFFF;
			mbox64->xferaddr_hi	= 0;

			वापस scb;

		हाल RESERVE:
		हाल RELEASE:
			/*
			 * Do we support clustering and is the support enabled
			 */
			अगर (!adapter->ha) अणु
				scp->result = (DID_BAD_TARGET << 16);
				वापस शून्य;
			पूर्ण

			/*
			 * Allocate a SCB and initialize mailbox
			 */
			अगर (!(scb = megaraid_alloc_scb(adapter, scp))) अणु
				scp->result = (DID_ERROR << 16);
				*busy = 1;
				वापस शून्य;
			पूर्ण

			ccb			= (mbox_ccb_t *)scb->ccb;
			scb->dev_channel	= 0xFF;
			scb->dev_target		= target;
			ccb->raw_mbox[0]	= CLUSTER_CMD;
			ccb->raw_mbox[2]	=  (scp->cmnd[0] == RESERVE) ?
						RESERVE_LD : RELEASE_LD;

			ccb->raw_mbox[3]	= target;
			scb->dma_direction	= scp->sc_data_direction;

			वापस scb;

		शेष:
			scp->result = (DID_BAD_TARGET << 16);
			वापस शून्य;
		पूर्ण
	पूर्ण
	अन्यथा अणु // Passthru device commands

		// Do not allow access to target id > 15 or LUN > 7
		अगर (target > 15 || SCP2LUN(scp) > 7) अणु
			scp->result = (DID_BAD_TARGET << 16);
			वापस शून्य;
		पूर्ण

		// अगर fast load option was set and scan क्रम last device is
		// over, reset the fast_load flag so that during a possible
		// next scan, devices can be made available
		अगर (rdev->fast_load && (target == 15) &&
			(SCP2CHANNEL(scp) == adapter->max_channel -1)) अणु

			con_log(CL_ANN, (KERN_INFO
			"megaraid[%d]: physical device scan re-enabled\n",
				adapter->host->host_no));
			rdev->fast_load = 0;
		पूर्ण

		/*
		 * Display the channel scan क्रम physical devices
		 */
		अगर (!(rdev->last_disp & (1L << SCP2CHANNEL(scp)))) अणु

			ss = rdev->fast_load ? skip : scan;

			con_log(CL_ANN, (KERN_INFO
				"scsi[%d]: %s scsi channel %d [Phy %d]",
				adapter->host->host_no, ss, SCP2CHANNEL(scp),
				channel));

			con_log(CL_ANN, (
				" for non-raid devices\n"));

			rdev->last_disp |= (1L << SCP2CHANNEL(scp));
		पूर्ण

		// disable channel sweep अगर fast load option given
		अगर (rdev->fast_load) अणु
			scp->result = (DID_BAD_TARGET << 16);
			वापस शून्य;
		पूर्ण

		// Allocate a SCB and initialize passthru
		अगर (!(scb = megaraid_alloc_scb(adapter, scp))) अणु
			scp->result = (DID_ERROR << 16);
			*busy = 1;
			वापस शून्य;
		पूर्ण

		ccb			= (mbox_ccb_t *)scb->ccb;
		scb->dev_channel	= channel;
		scb->dev_target		= target;
		scb->dma_direction	= scp->sc_data_direction;
		mbox			= ccb->mbox;
		mbox64			= ccb->mbox64;

		// Does this firmware support extended CDBs
		अगर (adapter->max_cdb_sz == 16) अणु
			mbox->cmd		= MBOXCMD_EXTPTHRU;

			megaraid_mbox_prepare_epthru(adapter, scb, scp);

			mbox64->xferaddr_lo	= (uपूर्णांक32_t)ccb->epthru_dma_h;
			mbox64->xferaddr_hi	= 0;
			mbox->xferaddr		= 0xFFFFFFFF;
		पूर्ण
		अन्यथा अणु
			mbox->cmd = MBOXCMD_PASSTHRU64;

			megaraid_mbox_prepare_pthru(adapter, scb, scp);

			mbox64->xferaddr_lo	= (uपूर्णांक32_t)ccb->pthru_dma_h;
			mbox64->xferaddr_hi	= 0;
			mbox->xferaddr		= 0xFFFFFFFF;
		पूर्ण
		वापस scb;
	पूर्ण

	// NOT REACHED
पूर्ण


/**
 * megaraid_mbox_runpendq - execute commands queued in the pending queue
 * @adapter	: controller's soft state
 * @scb_q	: SCB to be queued in the pending list
 *
 * Scan the pending list क्रम commands which are not yet issued and try to
 * post to the controller. The SCB can be a null poपूर्णांकer, which would indicate
 * no SCB to be queue, just try to execute the ones in the pending list.
 *
 * NOTE: We करो not actually traverse the pending list. The SCBs are plucked
 * out from the head of the pending list. If it is successfully issued, the
 * next SCB is at the head now.
 */
अटल व्योम
megaraid_mbox_runpendq(adapter_t *adapter, scb_t *scb_q)
अणु
	scb_t			*scb;
	अचिन्हित दीर्घ		flags;

	spin_lock_irqsave(PENDING_LIST_LOCK(adapter), flags);

	अगर (scb_q) अणु
		scb_q->state = SCB_PENDQ;
		list_add_tail(&scb_q->list, &adapter->pend_list);
	पूर्ण

	// अगर the adapter in not in quiescent mode, post the commands to FW
	अगर (adapter->quiescent) अणु
		spin_unlock_irqrestore(PENDING_LIST_LOCK(adapter), flags);
		वापस;
	पूर्ण

	जबतक (!list_empty(&adapter->pend_list)) अणु

		निश्चित_spin_locked(PENDING_LIST_LOCK(adapter));

		scb = list_entry(adapter->pend_list.next, scb_t, list);

		// हटाओ the scb from the pending list and try to
		// issue. If we are unable to issue it, put back in
		// the pending list and वापस

		list_del_init(&scb->list);

		spin_unlock_irqrestore(PENDING_LIST_LOCK(adapter), flags);

		// अगर mailbox was busy, वापस SCB back to pending
		// list. Make sure to add at the head, since that's
		// where it would have been हटाओd from

		scb->state = SCB_ISSUED;

		अगर (mbox_post_cmd(adapter, scb) != 0) अणु

			spin_lock_irqsave(PENDING_LIST_LOCK(adapter), flags);

			scb->state = SCB_PENDQ;

			list_add(&scb->list, &adapter->pend_list);

			spin_unlock_irqrestore(PENDING_LIST_LOCK(adapter),
				flags);

			वापस;
		पूर्ण

		spin_lock_irqsave(PENDING_LIST_LOCK(adapter), flags);
	पूर्ण

	spin_unlock_irqrestore(PENDING_LIST_LOCK(adapter), flags);


	वापस;
पूर्ण


/**
 * megaraid_mbox_prepare_pthru - prepare a command क्रम physical devices
 * @adapter	: poपूर्णांकer to controller's soft state
 * @scb		: scsi control block
 * @scp		: scsi command from the mid-layer
 *
 * Prepare a command क्रम the scsi physical devices.
 */
अटल व्योम
megaraid_mbox_prepare_pthru(adapter_t *adapter, scb_t *scb,
		काष्ठा scsi_cmnd *scp)
अणु
	mbox_ccb_t		*ccb;
	mraid_passthru_t	*pthru;
	uपूर्णांक8_t			channel;
	uपूर्णांक8_t			target;

	ccb	= (mbox_ccb_t *)scb->ccb;
	pthru	= ccb->pthru;
	channel	= scb->dev_channel;
	target	= scb->dev_target;

	// 0=6sec, 1=60sec, 2=10min, 3=3hrs, 4=NO समयout
	pthru->समयout		= 4;	
	pthru->ars		= 1;
	pthru->islogical	= 0;
	pthru->channel		= 0;
	pthru->target		= (channel << 4) | target;
	pthru->logdrv		= SCP2LUN(scp);
	pthru->reqsenselen	= 14;
	pthru->cdblen		= scp->cmd_len;

	स_नकल(pthru->cdb, scp->cmnd, scp->cmd_len);

	अगर (scsi_bufflen(scp)) अणु
		pthru->dataxferlen	= scsi_bufflen(scp);
		pthru->dataxferaddr	= ccb->sgl_dma_h;
		pthru->numsge		= megaraid_mbox_mksgl(adapter, scb);
	पूर्ण
	अन्यथा अणु
		pthru->dataxferaddr	= 0;
		pthru->dataxferlen	= 0;
		pthru->numsge		= 0;
	पूर्ण
	वापस;
पूर्ण


/**
 * megaraid_mbox_prepare_epthru - prepare a command क्रम physical devices
 * @adapter	: poपूर्णांकer to controller's soft state
 * @scb		: scsi control block
 * @scp		: scsi command from the mid-layer
 *
 * Prepare a command क्रम the scsi physical devices. This routine prepares
 * commands क्रम devices which can take extended CDBs (>10 bytes).
 */
अटल व्योम
megaraid_mbox_prepare_epthru(adapter_t *adapter, scb_t *scb,
		काष्ठा scsi_cmnd *scp)
अणु
	mbox_ccb_t		*ccb;
	mraid_epassthru_t	*epthru;
	uपूर्णांक8_t			channel;
	uपूर्णांक8_t			target;

	ccb	= (mbox_ccb_t *)scb->ccb;
	epthru	= ccb->epthru;
	channel	= scb->dev_channel;
	target	= scb->dev_target;

	// 0=6sec, 1=60sec, 2=10min, 3=3hrs, 4=NO समयout
	epthru->समयout		= 4;	
	epthru->ars		= 1;
	epthru->islogical	= 0;
	epthru->channel		= 0;
	epthru->target		= (channel << 4) | target;
	epthru->logdrv		= SCP2LUN(scp);
	epthru->reqsenselen	= 14;
	epthru->cdblen		= scp->cmd_len;

	स_नकल(epthru->cdb, scp->cmnd, scp->cmd_len);

	अगर (scsi_bufflen(scp)) अणु
		epthru->dataxferlen	= scsi_bufflen(scp);
		epthru->dataxferaddr	= ccb->sgl_dma_h;
		epthru->numsge		= megaraid_mbox_mksgl(adapter, scb);
	पूर्ण
	अन्यथा अणु
		epthru->dataxferaddr	= 0;
		epthru->dataxferlen	= 0;
		epthru->numsge		= 0;
	पूर्ण
	वापस;
पूर्ण


/**
 * megaraid_ack_sequence - पूर्णांकerrupt ack sequence क्रम memory mapped HBAs
 * @adapter	: controller's soft state
 *
 * Interrupt acknowledgement sequence क्रम memory mapped HBAs. Find out the
 * completed command and put them on the completed list क्रम later processing.
 *
 * Returns:	1 अगर the पूर्णांकerrupt is valid, 0 otherwise
 */
अटल पूर्णांक
megaraid_ack_sequence(adapter_t *adapter)
अणु
	mraid_device_t		*raid_dev = ADAP2RAIDDEV(adapter);
	mbox_t			*mbox;
	scb_t			*scb;
	uपूर्णांक8_t			nstatus;
	uपूर्णांक8_t			completed[MBOX_MAX_FIRMWARE_STATUS];
	काष्ठा list_head	clist;
	पूर्णांक			handled;
	uपूर्णांक32_t		dword;
	अचिन्हित दीर्घ		flags;
	पूर्णांक			i, j;


	mbox	= raid_dev->mbox;

	// move the SCBs from the firmware completed array to our local list
	INIT_LIST_HEAD(&clist);

	// loop till F/W has more commands क्रम us to complete
	handled = 0;
	spin_lock_irqsave(MAILBOX_LOCK(raid_dev), flags);
	करो अणु
		/*
		 * Check अगर a valid पूर्णांकerrupt is pending. If found, क्रमce the
		 * पूर्णांकerrupt line low.
		 */
		dword = RDOUTDOOR(raid_dev);
		अगर (dword != 0x10001234) अवरोध;

		handled = 1;

		WROUTDOOR(raid_dev, 0x10001234);

		nstatus = 0;
		// रुको क्रम valid numstatus to post
		क्रम (i = 0; i < 0xFFFFF; i++) अणु
			अगर (mbox->numstatus != 0xFF) अणु
				nstatus = mbox->numstatus;
				अवरोध;
			पूर्ण
			rmb();
		पूर्ण
		mbox->numstatus = 0xFF;

		adapter->outstanding_cmds -= nstatus;

		क्रम (i = 0; i < nstatus; i++) अणु

			// रुको क्रम valid command index to post
			क्रम (j = 0; j < 0xFFFFF; j++) अणु
				अगर (mbox->completed[i] != 0xFF) अवरोध;
				rmb();
			पूर्ण
			completed[i]		= mbox->completed[i];
			mbox->completed[i]	= 0xFF;

			अगर (completed[i] == 0xFF) अणु
				con_log(CL_ANN, (KERN_CRIT
				"megaraid: command posting timed out\n"));

				BUG();
				जारी;
			पूर्ण

			// Get SCB associated with this command id
			अगर (completed[i] >= MBOX_MAX_SCSI_CMDS) अणु
				// a cmm command
				scb = adapter->uscb_list + (completed[i] -
						MBOX_MAX_SCSI_CMDS);
			पूर्ण
			अन्यथा अणु
				// an os command
				scb = adapter->kscb_list + completed[i];
			पूर्ण

			scb->status = mbox->status;
			list_add_tail(&scb->list, &clist);
		पूर्ण

		// Acknowledge पूर्णांकerrupt
		WRINDOOR(raid_dev, 0x02);

	पूर्ण जबतक(1);

	spin_unlock_irqrestore(MAILBOX_LOCK(raid_dev), flags);


	// put the completed commands in the completed list. DPC would
	// complete these commands later
	spin_lock_irqsave(COMPLETED_LIST_LOCK(adapter), flags);

	list_splice(&clist, &adapter->completed_list);

	spin_unlock_irqrestore(COMPLETED_LIST_LOCK(adapter), flags);


	// schedule the DPC अगर there is some work क्रम it
	अगर (handled)
		tasklet_schedule(&adapter->dpc_h);

	वापस handled;
पूर्ण


/**
 * megaraid_isr - isr क्रम memory based mailbox based controllers
 * @irq		: irq
 * @devp	: poपूर्णांकer to our soft state
 *
 * Interrupt service routine क्रम memory-mapped mailbox controllers.
 */
अटल irqवापस_t
megaraid_isr(पूर्णांक irq, व्योम *devp)
अणु
	adapter_t	*adapter = devp;
	पूर्णांक		handled;

	handled = megaraid_ack_sequence(adapter);

	/* Loop through any pending requests */
	अगर (!adapter->quiescent) अणु
		megaraid_mbox_runpendq(adapter, शून्य);
	पूर्ण

	वापस IRQ_RETVAL(handled);
पूर्ण


/**
 * megaraid_mbox_dpc - the tasklet to complete the commands from completed list
 * @devp	: poपूर्णांकer to HBA soft state
 *
 * Pick up the commands from the completed list and send back to the owners.
 * This is a reentrant function and करोes not assume any locks are held जबतक
 * it is being called.
 */
अटल व्योम
megaraid_mbox_dpc(अचिन्हित दीर्घ devp)
अणु
	adapter_t		*adapter = (adapter_t *)devp;
	mraid_device_t		*raid_dev;
	काष्ठा list_head	clist;
	काष्ठा scatterlist	*sgl;
	scb_t			*scb;
	scb_t			*पंचांगp;
	काष्ठा scsi_cmnd	*scp;
	mraid_passthru_t	*pthru;
	mraid_epassthru_t	*epthru;
	mbox_ccb_t		*ccb;
	पूर्णांक			islogical;
	पूर्णांक			pdev_index;
	पूर्णांक			pdev_state;
	mbox_t			*mbox;
	अचिन्हित दीर्घ		flags;
	uपूर्णांक8_t			c;
	पूर्णांक			status;
	uioc_t			*kioc;


	अगर (!adapter) वापस;

	raid_dev = ADAP2RAIDDEV(adapter);

	// move the SCBs from the completed list to our local list
	INIT_LIST_HEAD(&clist);

	spin_lock_irqsave(COMPLETED_LIST_LOCK(adapter), flags);

	list_splice_init(&adapter->completed_list, &clist);

	spin_unlock_irqrestore(COMPLETED_LIST_LOCK(adapter), flags);


	list_क्रम_each_entry_safe(scb, पंचांगp, &clist, list) अणु

		status		= scb->status;
		scp		= scb->scp;
		ccb		= (mbox_ccb_t *)scb->ccb;
		pthru		= ccb->pthru;
		epthru		= ccb->epthru;
		mbox		= ccb->mbox;

		// Make sure f/w has completed a valid command
		अगर (scb->state != SCB_ISSUED) अणु
			con_log(CL_ANN, (KERN_CRIT
			"megaraid critical err: invalid command %d:%d:%p\n",
				scb->sno, scb->state, scp));
			BUG();
			जारी;	// Must never happen!
		पूर्ण

		// check क्रम the management command and complete it right away
		अगर (scb->sno >= MBOX_MAX_SCSI_CMDS) अणु
			scb->state	= SCB_FREE;
			scb->status	= status;

			// हटाओ from local clist
			list_del_init(&scb->list);

			kioc			= (uioc_t *)scb->gp;
			kioc->status		= 0;

			megaraid_mbox_mm_करोne(adapter, scb);

			जारी;
		पूर्ण

		// Was an पात issued क्रम this command earlier
		अगर (scb->state & SCB_ABORT) अणु
			con_log(CL_ANN, (KERN_NOTICE
			"megaraid: aborted cmd [%x] completed\n",
				scb->sno));
		पूर्ण

		/*
		 * If the inquiry came of a disk drive which is not part of
		 * any RAID array, expose it to the kernel. For this to be
		 * enabled, user must set the "megaraid_expose_unconf_disks"
		 * flag to 1 by specअगरying it on module parameter list.
		 * This would enable data migration off drives from other
		 * configurations.
		 */
		islogical = MRAID_IS_LOGICAL(adapter, scp);
		अगर (scp->cmnd[0] == INQUIRY && status == 0 && islogical == 0
				&& IS_RAID_CH(raid_dev, scb->dev_channel)) अणु

			sgl = scsi_sglist(scp);
			अगर (sg_page(sgl)) अणु
				c = *(अचिन्हित अक्षर *) sg_virt(&sgl[0]);
			पूर्ण अन्यथा अणु
				con_log(CL_ANN, (KERN_WARNING
						 "megaraid mailbox: invalid sg:%d\n",
						 __LINE__));
				c = 0;
			पूर्ण

			अगर ((c & 0x1F ) == TYPE_DISK) अणु
				pdev_index = (scb->dev_channel * 16) +
					scb->dev_target;
				pdev_state =
					raid_dev->pdrv_state[pdev_index] & 0x0F;

				अगर (pdev_state == PDRV_ONLINE		||
					pdev_state == PDRV_FAILED	||
					pdev_state == PDRV_RBLD		||
					pdev_state == PDRV_HOTSPARE	||
					megaraid_expose_unconf_disks == 0) अणु

					status = 0xF0;
				पूर्ण
			पूर्ण
		पूर्ण

		// Convert MegaRAID status to Linux error code
		चयन (status) अणु

		हाल 0x00:

			scp->result = (DID_OK << 16);
			अवरोध;

		हाल 0x02:

			/* set sense_buffer and result fields */
			अगर (mbox->cmd == MBOXCMD_PASSTHRU ||
				mbox->cmd == MBOXCMD_PASSTHRU64) अणु

				स_नकल(scp->sense_buffer, pthru->reqsensearea,
						14);

				scp->result = DRIVER_SENSE << 24 |
					DID_OK << 16 | CHECK_CONDITION << 1;
			पूर्ण
			अन्यथा अणु
				अगर (mbox->cmd == MBOXCMD_EXTPTHRU) अणु

					स_नकल(scp->sense_buffer,
						epthru->reqsensearea, 14);

					scp->result = DRIVER_SENSE << 24 |
						DID_OK << 16 |
						CHECK_CONDITION << 1;
				पूर्ण अन्यथा अणु
					scp->sense_buffer[0] = 0x70;
					scp->sense_buffer[2] = ABORTED_COMMAND;
					scp->result = CHECK_CONDITION << 1;
				पूर्ण
			पूर्ण
			अवरोध;

		हाल 0x08:

			scp->result = DID_BUS_BUSY << 16 | status;
			अवरोध;

		शेष:

			/*
			 * If TEST_UNIT_READY fails, we know RESERVATION_STATUS
			 * failed
			 */
			अगर (scp->cmnd[0] == TEST_UNIT_READY) अणु
				scp->result = DID_ERROR << 16 |
					RESERVATION_CONFLICT << 1;
			पूर्ण
			अन्यथा
			/*
			 * Error code वापसed is 1 अगर Reserve or Release
			 * failed or the input parameter is invalid
			 */
			अगर (status == 1 && (scp->cmnd[0] == RESERVE ||
					 scp->cmnd[0] == RELEASE)) अणु

				scp->result = DID_ERROR << 16 |
					RESERVATION_CONFLICT << 1;
			पूर्ण
			अन्यथा अणु
				scp->result = DID_BAD_TARGET << 16 | status;
			पूर्ण
		पूर्ण

		// prपूर्णांक a debug message क्रम all failed commands
		अगर (status) अणु
			megaraid_mbox_display_scb(adapter, scb);
		पूर्ण

		scsi_dma_unmap(scp);

		// हटाओ from local clist
		list_del_init(&scb->list);

		// put back in मुक्त list
		megaraid_dealloc_scb(adapter, scb);

		// send the scsi packet back to kernel
		scp->scsi_करोne(scp);
	पूर्ण

	वापस;
पूर्ण


/**
 * megaraid_पात_handler - पात the scsi command
 * @scp		: command to be पातed
 *
 * Abort a previous SCSI request. Only commands on the pending list can be
 * पातed. All the commands issued to the F/W must complete.
 **/
अटल पूर्णांक
megaraid_पात_handler(काष्ठा scsi_cmnd *scp)
अणु
	adapter_t		*adapter;
	mraid_device_t		*raid_dev;
	scb_t			*scb;
	scb_t			*पंचांगp;
	पूर्णांक			found;
	अचिन्हित दीर्घ		flags;
	पूर्णांक			i;


	adapter		= SCP2ADAPTER(scp);
	raid_dev	= ADAP2RAIDDEV(adapter);

	con_log(CL_ANN, (KERN_WARNING
		"megaraid: aborting cmd=%x <c=%d t=%d l=%d>\n",
		scp->cmnd[0], SCP2CHANNEL(scp),
		SCP2TARGET(scp), SCP2LUN(scp)));

	// If FW has stopped responding, simply वापस failure
	अगर (raid_dev->hw_error) अणु
		con_log(CL_ANN, (KERN_NOTICE
			"megaraid: hw error, not aborting\n"));
		वापस FAILED;
	पूर्ण

	// There might a race here, where the command was completed by the
	// firmware and now it is on the completed list. Beक्रमe we could
	// complete the command to the kernel in dpc, the पात came.
	// Find out अगर this is the हाल to aव्योम the race.
	scb = शून्य;
	spin_lock_irqsave(COMPLETED_LIST_LOCK(adapter), flags);
	list_क्रम_each_entry_safe(scb, पंचांगp, &adapter->completed_list, list) अणु

		अगर (scb->scp == scp) अणु	// Found command

			list_del_init(&scb->list);	// from completed list

			con_log(CL_ANN, (KERN_WARNING
			"megaraid: %d[%d:%d], abort from completed list\n",
				scb->sno, scb->dev_channel, scb->dev_target));

			scp->result = (DID_ABORT << 16);
			scp->scsi_करोne(scp);

			megaraid_dealloc_scb(adapter, scb);

			spin_unlock_irqrestore(COMPLETED_LIST_LOCK(adapter),
				flags);

			वापस SUCCESS;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(COMPLETED_LIST_LOCK(adapter), flags);


	// Find out अगर this command is still on the pending list. If it is and
	// was never issued, पात and वापस success. If the command is owned
	// by the firmware, we must रुको क्रम it to complete by the FW.
	spin_lock_irqsave(PENDING_LIST_LOCK(adapter), flags);
	list_क्रम_each_entry_safe(scb, पंचांगp, &adapter->pend_list, list) अणु

		अगर (scb->scp == scp) अणु	// Found command

			list_del_init(&scb->list);	// from pending list

			ASSERT(!(scb->state & SCB_ISSUED));

			con_log(CL_ANN, (KERN_WARNING
				"megaraid abort: [%d:%d], driver owner\n",
				scb->dev_channel, scb->dev_target));

			scp->result = (DID_ABORT << 16);
			scp->scsi_करोne(scp);

			megaraid_dealloc_scb(adapter, scb);

			spin_unlock_irqrestore(PENDING_LIST_LOCK(adapter),
				flags);

			वापस SUCCESS;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(PENDING_LIST_LOCK(adapter), flags);


	// Check करो we even own this command, in which हाल this would be
	// owned by the firmware. The only way to locate the FW scb is to
	// traverse through the list of all SCB, since driver करोes not
	// मुख्यtain these SCBs on any list
	found = 0;
	spin_lock_irq(&adapter->lock);
	क्रम (i = 0; i < MBOX_MAX_SCSI_CMDS; i++) अणु
		scb = adapter->kscb_list + i;

		अगर (scb->scp == scp) अणु

			found = 1;

			अगर (!(scb->state & SCB_ISSUED)) अणु
				con_log(CL_ANN, (KERN_WARNING
				"megaraid abort: %d[%d:%d], invalid state\n",
				scb->sno, scb->dev_channel, scb->dev_target));
				BUG();
			पूर्ण
			अन्यथा अणु
				con_log(CL_ANN, (KERN_WARNING
				"megaraid abort: %d[%d:%d], fw owner\n",
				scb->sno, scb->dev_channel, scb->dev_target));
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock_irq(&adapter->lock);

	अगर (!found) अणु
		con_log(CL_ANN, (KERN_WARNING "megaraid abort: do now own\n"));

		// FIXME: Should there be a callback क्रम this command?
		वापस SUCCESS;
	पूर्ण

	// We cannot actually पात a command owned by firmware, वापस
	// failure and रुको क्रम reset. In host reset handler, we will find out
	// अगर the HBA is still live
	वापस FAILED;
पूर्ण

/**
 * megaraid_reset_handler - device reset handler क्रम mailbox based driver
 * @scp		: reference command
 *
 * Reset handler क्रम the mailbox based controller. First try to find out अगर
 * the FW is still live, in which हाल the outstanding commands counter mut go
 * करोwn to 0. If that happens, also issue the reservation reset command to
 * relinquish (possible) reservations on the logical drives connected to this
 * host.
 **/
अटल पूर्णांक
megaraid_reset_handler(काष्ठा scsi_cmnd *scp)
अणु
	adapter_t	*adapter;
	scb_t		*scb;
	scb_t		*पंचांगp;
	mraid_device_t	*raid_dev;
	अचिन्हित दीर्घ	flags;
	uपूर्णांक8_t		raw_mbox[माप(mbox_t)];
	पूर्णांक		rval;
	पूर्णांक		recovery_winकरोw;
	पूर्णांक		i;
	uioc_t		*kioc;

	adapter		= SCP2ADAPTER(scp);
	raid_dev	= ADAP2RAIDDEV(adapter);

	// वापस failure अगर adapter is not responding
	अगर (raid_dev->hw_error) अणु
		con_log(CL_ANN, (KERN_NOTICE
			"megaraid: hw error, cannot reset\n"));
		वापस FAILED;
	पूर्ण

	// Under exceptional conditions, FW can take up to 3 minutes to
	// complete command processing. Wait क्रम additional 2 minutes क्रम the
	// pending commands counter to go करोwn to 0. If it करोesn't, let the
	// controller be marked offline
	// Also, reset all the commands currently owned by the driver
	spin_lock_irqsave(PENDING_LIST_LOCK(adapter), flags);
	list_क्रम_each_entry_safe(scb, पंचांगp, &adapter->pend_list, list) अणु
		list_del_init(&scb->list);	// from pending list

		अगर (scb->sno >= MBOX_MAX_SCSI_CMDS) अणु
			con_log(CL_ANN, (KERN_WARNING
			"megaraid: IOCTL packet with %d[%d:%d] being reset\n",
			scb->sno, scb->dev_channel, scb->dev_target));

			scb->status = -1;

			kioc			= (uioc_t *)scb->gp;
			kioc->status		= -EFAULT;

			megaraid_mbox_mm_करोne(adapter, scb);
		पूर्ण अन्यथा अणु
			अगर (scb->scp == scp) अणु	// Found command
				con_log(CL_ANN, (KERN_WARNING
					"megaraid: %d[%d:%d], reset from pending list\n",
					scb->sno, scb->dev_channel, scb->dev_target));
			पूर्ण अन्यथा अणु
				con_log(CL_ANN, (KERN_WARNING
				"megaraid: IO packet with %d[%d:%d] being reset\n",
				scb->sno, scb->dev_channel, scb->dev_target));
			पूर्ण

			scb->scp->result = (DID_RESET << 16);
			scb->scp->scsi_करोne(scb->scp);

			megaraid_dealloc_scb(adapter, scb);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(PENDING_LIST_LOCK(adapter), flags);

	अगर (adapter->outstanding_cmds) अणु
		con_log(CL_ANN, (KERN_NOTICE
			"megaraid: %d outstanding commands. Max wait %d sec\n",
			adapter->outstanding_cmds,
			(MBOX_RESET_WAIT + MBOX_RESET_EXT_WAIT)));
	पूर्ण

	recovery_winकरोw = MBOX_RESET_WAIT + MBOX_RESET_EXT_WAIT;

	क्रम (i = 0; i < recovery_winकरोw; i++) अणु

		megaraid_ack_sequence(adapter);

		// prपूर्णांक a message once every 5 seconds only
		अगर (!(i % 5)) अणु
			con_log(CL_ANN, (
			"megaraid mbox: Wait for %d commands to complete:%d\n",
				adapter->outstanding_cmds,
				(MBOX_RESET_WAIT + MBOX_RESET_EXT_WAIT) - i));
		पूर्ण

		// bailout अगर no recovery happened in reset समय
		अगर (adapter->outstanding_cmds == 0) अणु
			अवरोध;
		पूर्ण

		msleep(1000);
	पूर्ण

	spin_lock(&adapter->lock);

	// If still outstanding commands, bail out
	अगर (adapter->outstanding_cmds) अणु
		con_log(CL_ANN, (KERN_WARNING
			"megaraid mbox: critical hardware error!\n"));

		raid_dev->hw_error = 1;

		rval = FAILED;
		जाओ out;
	पूर्ण
	अन्यथा अणु
		con_log(CL_ANN, (KERN_NOTICE
		"megaraid mbox: reset sequence completed successfully\n"));
	पूर्ण


	// If the controller supports clustering, reset reservations
	अगर (!adapter->ha) अणु
		rval = SUCCESS;
		जाओ out;
	पूर्ण

	// clear reservations अगर any
	raw_mbox[0] = CLUSTER_CMD;
	raw_mbox[2] = RESET_RESERVATIONS;

	rval = SUCCESS;
	अगर (mbox_post_sync_cmd_fast(adapter, raw_mbox) == 0) अणु
		con_log(CL_ANN,
			(KERN_INFO "megaraid: reservation reset\n"));
	पूर्ण
	अन्यथा अणु
		rval = FAILED;
		con_log(CL_ANN, (KERN_WARNING
				"megaraid: reservation reset failed\n"));
	पूर्ण

 out:
	spin_unlock(&adapter->lock);
	वापस rval;
पूर्ण

/*
 * START: पूर्णांकernal commands library
 *
 * This section of the driver has the common routine used by the driver and
 * also has all the FW routines
 */

/**
 * mbox_post_sync_cmd() - blocking command to the mailbox based controllers
 * @adapter	: controller's soft state
 * @raw_mbox	: the mailbox
 *
 * Issue a scb in synchronous and non-पूर्णांकerrupt mode क्रम mailbox based
 * controllers.
 */
अटल पूर्णांक
mbox_post_sync_cmd(adapter_t *adapter, uपूर्णांक8_t raw_mbox[])
अणु
	mraid_device_t	*raid_dev = ADAP2RAIDDEV(adapter);
	mbox_t		*mbox;
	uपूर्णांक8_t		status;
	पूर्णांक		i;

	mbox	= raid_dev->mbox;

	/*
	 * Wait until mailbox is मुक्त
	 */
	अगर (megaraid_busyरुको_mbox(raid_dev) != 0)
		जाओ blocked_mailbox;

	/*
	 * Copy mailbox data पूर्णांकo host काष्ठाure
	 */
	स_नकल((caddr_t)mbox, (caddr_t)raw_mbox, 16);
	mbox->cmdid		= 0xFE;
	mbox->busy		= 1;
	mbox->poll		= 0;
	mbox->ack		= 0;
	mbox->numstatus		= 0xFF;
	mbox->status		= 0xFF;

	wmb();
	WRINDOOR(raid_dev, raid_dev->mbox_dma | 0x1);

	// रुको क्रम maximum 1 second क्रम status to post. If the status is not
	// available within 1 second, assume FW is initializing and रुको
	// क्रम an extended amount of समय
	अगर (mbox->numstatus == 0xFF) अणु	// status not yet available
		udelay(25);

		क्रम (i = 0; mbox->numstatus == 0xFF && i < 1000; i++) अणु
			rmb();
			msleep(1);
		पूर्ण


		अगर (i == 1000) अणु
			con_log(CL_ANN, (KERN_NOTICE
				"megaraid mailbox: wait for FW to boot      "));

			क्रम (i = 0; (mbox->numstatus == 0xFF) &&
					(i < MBOX_RESET_WAIT); i++) अणु
				rmb();
				con_log(CL_ANN, ("\b\b\b\b\b[%03d]",
							MBOX_RESET_WAIT - i));
				msleep(1000);
			पूर्ण

			अगर (i == MBOX_RESET_WAIT) अणु

				con_log(CL_ANN, (
				"\nmegaraid mailbox: status not available\n"));

				वापस -1;
			पूर्ण
			con_log(CL_ANN, ("\b\b\b\b\b[ok] \n"));
		पूर्ण
	पूर्ण

	// रुको क्रम maximum 1 second क्रम poll semaphore
	अगर (mbox->poll != 0x77) अणु
		udelay(25);

		क्रम (i = 0; (mbox->poll != 0x77) && (i < 1000); i++) अणु
			rmb();
			msleep(1);
		पूर्ण

		अगर (i == 1000) अणु
			con_log(CL_ANN, (KERN_WARNING
			"megaraid mailbox: could not get poll semaphore\n"));
			वापस -1;
		पूर्ण
	पूर्ण

	WRINDOOR(raid_dev, raid_dev->mbox_dma | 0x2);
	wmb();

	// रुको क्रम maximum 1 second क्रम acknowledgement
	अगर (RDINDOOR(raid_dev) & 0x2) अणु
		udelay(25);

		क्रम (i = 0; (RDINDOOR(raid_dev) & 0x2) && (i < 1000); i++) अणु
			rmb();
			msleep(1);
		पूर्ण

		अगर (i == 1000) अणु
			con_log(CL_ANN, (KERN_WARNING
				"megaraid mailbox: could not acknowledge\n"));
			वापस -1;
		पूर्ण
	पूर्ण
	mbox->poll	= 0;
	mbox->ack	= 0x77;

	status = mbox->status;

	// invalidate the completed command id array. After command
	// completion, firmware would ग_लिखो the valid id.
	mbox->numstatus	= 0xFF;
	mbox->status	= 0xFF;
	क्रम (i = 0; i < MBOX_MAX_FIRMWARE_STATUS; i++) अणु
		mbox->completed[i] = 0xFF;
	पूर्ण

	वापस status;

blocked_mailbox:

	con_log(CL_ANN, (KERN_WARNING "megaraid: blocked mailbox\n") );
	वापस -1;
पूर्ण


/**
 * mbox_post_sync_cmd_fast - blocking command to the mailbox based controllers
 * @adapter	: controller's soft state
 * @raw_mbox	: the mailbox
 *
 * Issue a scb in synchronous and non-पूर्णांकerrupt mode क्रम mailbox based
 * controllers. This is a faster version of the synchronous command and
 * thereक्रमe can be called in पूर्णांकerrupt-context as well.
 */
अटल पूर्णांक
mbox_post_sync_cmd_fast(adapter_t *adapter, uपूर्णांक8_t raw_mbox[])
अणु
	mraid_device_t	*raid_dev = ADAP2RAIDDEV(adapter);
	mbox_t		*mbox;
	दीर्घ		i;


	mbox	= raid_dev->mbox;

	// वापस immediately अगर the mailbox is busy
	अगर (mbox->busy) वापस -1;

	// Copy mailbox data पूर्णांकo host काष्ठाure
	स_नकल((caddr_t)mbox, (caddr_t)raw_mbox, 14);
	mbox->cmdid		= 0xFE;
	mbox->busy		= 1;
	mbox->poll		= 0;
	mbox->ack		= 0;
	mbox->numstatus		= 0xFF;
	mbox->status		= 0xFF;

	wmb();
	WRINDOOR(raid_dev, raid_dev->mbox_dma | 0x1);

	क्रम (i = 0; i < MBOX_SYNC_WAIT_CNT; i++) अणु
		अगर (mbox->numstatus != 0xFF) अवरोध;
		rmb();
		udelay(MBOX_SYNC_DELAY_200);
	पूर्ण

	अगर (i == MBOX_SYNC_WAIT_CNT) अणु
		// We may need to re-calibrate the counter
		con_log(CL_ANN, (KERN_CRIT
			"megaraid: fast sync command timed out\n"));
	पूर्ण

	WRINDOOR(raid_dev, raid_dev->mbox_dma | 0x2);
	wmb();

	वापस mbox->status;
पूर्ण


/**
 * megaraid_busyरुको_mbox() - Wait until the controller's mailbox is available
 * @raid_dev	: RAID device (HBA) soft state
 *
 * Wait until the controller's mailbox is available to accept more commands.
 * Wait क्रम at most 1 second.
 */
अटल पूर्णांक
megaraid_busyरुको_mbox(mraid_device_t *raid_dev)
अणु
	mbox_t	*mbox = raid_dev->mbox;
	पूर्णांक	i = 0;

	अगर (mbox->busy) अणु
		udelay(25);
		क्रम (i = 0; mbox->busy && i < 1000; i++)
			msleep(1);
	पूर्ण

	अगर (i < 1000) वापस 0;
	अन्यथा वापस -1;
पूर्ण


/**
 * megaraid_mbox_product_info - some अटल inक्रमmation about the controller
 * @adapter	: our soft state
 *
 * Issue commands to the controller to grab some parameters required by our
 * caller.
 */
अटल पूर्णांक
megaraid_mbox_product_info(adapter_t *adapter)
अणु
	mraid_device_t		*raid_dev = ADAP2RAIDDEV(adapter);
	mbox_t			*mbox;
	uपूर्णांक8_t			raw_mbox[माप(mbox_t)];
	mraid_pinfo_t		*pinfo;
	dma_addr_t		pinfo_dma_h;
	mraid_inquiry3_t	*mraid_inq3;
	पूर्णांक			i;


	स_रखो((caddr_t)raw_mbox, 0, माप(raw_mbox));
	mbox = (mbox_t *)raw_mbox;

	/*
	 * Issue an ENQUIRY3 command to find out certain adapter parameters,
	 * e.g., max channels, max commands etc.
	 */
	pinfo = dma_alloc_coherent(&adapter->pdev->dev, माप(mraid_pinfo_t),
				   &pinfo_dma_h, GFP_KERNEL);
	अगर (pinfo == शून्य) अणु
		con_log(CL_ANN, (KERN_WARNING
			"megaraid: out of memory, %s %d\n", __func__,
			__LINE__));

		वापस -1;
	पूर्ण

	mbox->xferaddr = (uपूर्णांक32_t)adapter->ibuf_dma_h;
	स_रखो((व्योम *)adapter->ibuf, 0, MBOX_IBUF_SIZE);

	raw_mbox[0] = FC_NEW_CONFIG;
	raw_mbox[2] = NC_SUBOP_ENQUIRY3;
	raw_mbox[3] = ENQ3_GET_SOLICITED_FULL;

	// Issue the command
	अगर (mbox_post_sync_cmd(adapter, raw_mbox) != 0) अणु

		con_log(CL_ANN, (KERN_WARNING "megaraid: Inquiry3 failed\n"));

		dma_मुक्त_coherent(&adapter->pdev->dev, माप(mraid_pinfo_t),
			pinfo, pinfo_dma_h);

		वापस -1;
	पूर्ण

	/*
	 * Collect inक्रमmation about state of each physical drive
	 * attached to the controller. We will expose all the disks
	 * which are not part of RAID
	 */
	mraid_inq3 = (mraid_inquiry3_t *)adapter->ibuf;
	क्रम (i = 0; i < MBOX_MAX_PHYSICAL_DRIVES; i++) अणु
		raid_dev->pdrv_state[i] = mraid_inq3->pdrv_state[i];
	पूर्ण

	/*
	 * Get product info क्रम inक्रमmation like number of channels,
	 * maximum commands supported.
	 */
	स_रखो((caddr_t)raw_mbox, 0, माप(raw_mbox));
	mbox->xferaddr = (uपूर्णांक32_t)pinfo_dma_h;

	raw_mbox[0] = FC_NEW_CONFIG;
	raw_mbox[2] = NC_SUBOP_PRODUCT_INFO;

	अगर (mbox_post_sync_cmd(adapter, raw_mbox) != 0) अणु

		con_log(CL_ANN, (KERN_WARNING
			"megaraid: product info failed\n"));

		dma_मुक्त_coherent(&adapter->pdev->dev, माप(mraid_pinfo_t),
			pinfo, pinfo_dma_h);

		वापस -1;
	पूर्ण

	/*
	 * Setup some parameters क्रम host, as required by our caller
	 */
	adapter->max_channel = pinfo->nchannels;

	/*
	 * we will export all the logical drives on a single channel.
	 * Add 1 since inquires करो not come क्रम inititor ID
	 */
	adapter->max_target	= MAX_LOGICAL_DRIVES_40LD + 1;
	adapter->max_lun	= 8;	// up to 8 LUNs क्रम non-disk devices

	/*
	 * These are the maximum outstanding commands क्रम the scsi-layer
	 */
	adapter->max_cmds	= MBOX_MAX_SCSI_CMDS;

	स_रखो(adapter->fw_version, 0, VERSION_SIZE);
	स_रखो(adapter->bios_version, 0, VERSION_SIZE);

	स_नकल(adapter->fw_version, pinfo->fw_version, 4);
	adapter->fw_version[4] = 0;

	स_नकल(adapter->bios_version, pinfo->bios_version, 4);
	adapter->bios_version[4] = 0;

	con_log(CL_ANN, (KERN_NOTICE
		"megaraid: fw version:[%s] bios version:[%s]\n",
		adapter->fw_version, adapter->bios_version));

	dma_मुक्त_coherent(&adapter->pdev->dev, माप(mraid_pinfo_t), pinfo,
			pinfo_dma_h);

	वापस 0;
पूर्ण



/**
 * megaraid_mbox_extended_cdb - check क्रम support क्रम extended CDBs
 * @adapter	: soft state क्रम the controller
 *
 * This routine check whether the controller in question supports extended
 * ( > 10 bytes ) CDBs.
 */
अटल पूर्णांक
megaraid_mbox_extended_cdb(adapter_t *adapter)
अणु
	mbox_t		*mbox;
	uपूर्णांक8_t		raw_mbox[माप(mbox_t)];
	पूर्णांक		rval;

	mbox = (mbox_t *)raw_mbox;

	स_रखो((caddr_t)raw_mbox, 0, माप(raw_mbox));
	mbox->xferaddr	= (uपूर्णांक32_t)adapter->ibuf_dma_h;

	स_रखो((व्योम *)adapter->ibuf, 0, MBOX_IBUF_SIZE);

	raw_mbox[0] = MAIN_MISC_OPCODE;
	raw_mbox[2] = SUPPORT_EXT_CDB;

	/*
	 * Issue the command
	 */
	rval = 0;
	अगर (mbox_post_sync_cmd(adapter, raw_mbox) != 0) अणु
		rval = -1;
	पूर्ण

	वापस rval;
पूर्ण


/**
 * megaraid_mbox_support_ha - Do we support clustering
 * @adapter	: soft state क्रम the controller
 * @init_id	: ID of the initiator
 *
 * Determine अगर the firmware supports clustering and the ID of the initiator.
 */
अटल पूर्णांक
megaraid_mbox_support_ha(adapter_t *adapter, uपूर्णांक16_t *init_id)
अणु
	mbox_t		*mbox;
	uपूर्णांक8_t		raw_mbox[माप(mbox_t)];
	पूर्णांक		rval;


	mbox = (mbox_t *)raw_mbox;

	स_रखो((caddr_t)raw_mbox, 0, माप(raw_mbox));

	mbox->xferaddr = (uपूर्णांक32_t)adapter->ibuf_dma_h;

	स_रखो((व्योम *)adapter->ibuf, 0, MBOX_IBUF_SIZE);

	raw_mbox[0] = GET_TARGET_ID;

	// Issue the command
	*init_id = 7;
	rval =  -1;
	अगर (mbox_post_sync_cmd(adapter, raw_mbox) == 0) अणु

		*init_id = *(uपूर्णांक8_t *)adapter->ibuf;

		con_log(CL_ANN, (KERN_INFO
			"megaraid: cluster firmware, initiator ID: %d\n",
			*init_id));

		rval =  0;
	पूर्ण

	वापस rval;
पूर्ण


/**
 * megaraid_mbox_support_अक्रमom_del - Do we support अक्रमom deletion
 * @adapter	: soft state क्रम the controller
 *
 * Determine अगर the firmware supports अक्रमom deletion.
 * Return:	1 is operation supported, 0 otherwise
 */
अटल पूर्णांक
megaraid_mbox_support_अक्रमom_del(adapter_t *adapter)
अणु
	uपूर्णांक8_t		raw_mbox[माप(mbox_t)];
	पूर्णांक		rval;

	/*
	 * Newer firmware on Dell CERC expect a dअगरferent
	 * अक्रमom deletion handling, so disable it.
	 */
	अगर (adapter->pdev->venकरोr == PCI_VENDOR_ID_AMI &&
	    adapter->pdev->device == PCI_DEVICE_ID_AMI_MEGARAID3 &&
	    adapter->pdev->subप्रणाली_venकरोr == PCI_VENDOR_ID_DELL &&
	    adapter->pdev->subप्रणाली_device == PCI_SUBSYS_ID_CERC_ATA100_4CH &&
	    (adapter->fw_version[0] > '6' ||
	     (adapter->fw_version[0] == '6' &&
	      adapter->fw_version[2] > '6') ||
	     (adapter->fw_version[0] == '6'
	      && adapter->fw_version[2] == '6'
	      && adapter->fw_version[3] > '1'))) अणु
		con_log(CL_DLEVEL1, ("megaraid: disable random deletion\n"));
		वापस 0;
	पूर्ण

	स_रखो((caddr_t)raw_mbox, 0, माप(mbox_t));

	raw_mbox[0] = FC_DEL_LOGDRV;
	raw_mbox[2] = OP_SUP_DEL_LOGDRV;

	// Issue the command
	rval = 0;
	अगर (mbox_post_sync_cmd(adapter, raw_mbox) == 0) अणु

		con_log(CL_DLEVEL1, ("megaraid: supports random deletion\n"));

		rval =  1;
	पूर्ण

	वापस rval;
पूर्ण


/**
 * megaraid_mbox_get_max_sg - maximum sg elements supported by the firmware
 * @adapter	: soft state क्रम the controller
 *
 * Find out the maximum number of scatter-gather elements supported by the
 * firmware.
 */
अटल पूर्णांक
megaraid_mbox_get_max_sg(adapter_t *adapter)
अणु
	mbox_t		*mbox;
	uपूर्णांक8_t		raw_mbox[माप(mbox_t)];
	पूर्णांक		nsg;


	mbox = (mbox_t *)raw_mbox;

	स_रखो((caddr_t)raw_mbox, 0, माप(mbox_t));

	mbox->xferaddr = (uपूर्णांक32_t)adapter->ibuf_dma_h;

	स_रखो((व्योम *)adapter->ibuf, 0, MBOX_IBUF_SIZE);

	raw_mbox[0] = MAIN_MISC_OPCODE;
	raw_mbox[2] = GET_MAX_SG_SUPPORT;

	// Issue the command
	अगर (mbox_post_sync_cmd(adapter, raw_mbox) == 0) अणु
		nsg =  *(uपूर्णांक8_t *)adapter->ibuf;
	पूर्ण
	अन्यथा अणु
		nsg =  MBOX_DEFAULT_SG_SIZE;
	पूर्ण

	अगर (nsg > MBOX_MAX_SG_SIZE) nsg = MBOX_MAX_SG_SIZE;

	वापस nsg;
पूर्ण


/**
 * megaraid_mbox_क्रमागत_raid_scsi - क्रमागतerate the RAID and SCSI channels
 * @adapter	: soft state क्रम the controller
 *
 * Enumerate the RAID and SCSI channels क्रम ROMB platक्रमms so that channels
 * can be exported as regular SCSI channels.
 */
अटल व्योम
megaraid_mbox_क्रमागत_raid_scsi(adapter_t *adapter)
अणु
	mraid_device_t	*raid_dev = ADAP2RAIDDEV(adapter);
	mbox_t		*mbox;
	uपूर्णांक8_t		raw_mbox[माप(mbox_t)];


	mbox = (mbox_t *)raw_mbox;

	स_रखो((caddr_t)raw_mbox, 0, माप(mbox_t));

	mbox->xferaddr = (uपूर्णांक32_t)adapter->ibuf_dma_h;

	स_रखो((व्योम *)adapter->ibuf, 0, MBOX_IBUF_SIZE);

	raw_mbox[0] = CHNL_CLASS;
	raw_mbox[2] = GET_CHNL_CLASS;

	// Issue the command. If the command fails, all channels are RAID
	// channels
	raid_dev->channel_class = 0xFF;
	अगर (mbox_post_sync_cmd(adapter, raw_mbox) == 0) अणु
		raid_dev->channel_class =  *(uपूर्णांक8_t *)adapter->ibuf;
	पूर्ण

	वापस;
पूर्ण


/**
 * megaraid_mbox_flush_cache - flush adapter and disks cache
 * @adapter		: soft state क्रम the controller
 *
 * Flush adapter cache followed by disks cache.
 */
अटल व्योम
megaraid_mbox_flush_cache(adapter_t *adapter)
अणु
	uपूर्णांक8_t	raw_mbox[माप(mbox_t)];

	स_रखो((caddr_t)raw_mbox, 0, माप(mbox_t));

	raw_mbox[0] = FLUSH_ADAPTER;

	अगर (mbox_post_sync_cmd(adapter, raw_mbox) != 0) अणु
		con_log(CL_ANN, ("megaraid: flush adapter failed\n"));
	पूर्ण

	raw_mbox[0] = FLUSH_SYSTEM;

	अगर (mbox_post_sync_cmd(adapter, raw_mbox) != 0) अणु
		con_log(CL_ANN, ("megaraid: flush disks cache failed\n"));
	पूर्ण

	वापस;
पूर्ण


/**
 * megaraid_mbox_fire_sync_cmd - fire the sync cmd
 * @adapter		: soft state क्रम the controller
 *
 * Clears the pending cmds in FW and reinits its RAID काष्ठाs.
 */
अटल पूर्णांक
megaraid_mbox_fire_sync_cmd(adapter_t *adapter)
अणु
	mbox_t	*mbox;
	uपूर्णांक8_t	raw_mbox[माप(mbox_t)];
	mraid_device_t	*raid_dev = ADAP2RAIDDEV(adapter);
	पूर्णांक	status = 0;
	पूर्णांक i;
	uपूर्णांक32_t dword;

	mbox = (mbox_t *)raw_mbox;

	स_रखो((caddr_t)raw_mbox, 0, माप(mbox_t));

	raw_mbox[0] = 0xFF;

	mbox	= raid_dev->mbox;

	/* Wait until mailbox is मुक्त */
	अगर (megaraid_busyरुको_mbox(raid_dev) != 0) अणु
		status = 1;
		जाओ blocked_mailbox;
	पूर्ण

	/* Copy mailbox data पूर्णांकo host काष्ठाure */
	स_नकल((caddr_t)mbox, (caddr_t)raw_mbox, 16);
	mbox->cmdid		= 0xFE;
	mbox->busy		= 1;
	mbox->poll		= 0;
	mbox->ack		= 0;
	mbox->numstatus		= 0;
	mbox->status		= 0;

	wmb();
	WRINDOOR(raid_dev, raid_dev->mbox_dma | 0x1);

	/* Wait क्रम maximum 1 min क्रम status to post.
	 * If the Firmware SUPPORTS the ABOVE COMMAND,
	 * mbox->cmd will be set to 0
	 * अन्यथा
	 * the firmware will reject the command with
	 * mbox->numstatus set to 1
	 */

	i = 0;
	status = 0;
	जबतक (!mbox->numstatus && mbox->cmd == 0xFF) अणु
		rmb();
		msleep(1);
		i++;
		अगर (i > 1000 * 60) अणु
			status = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (mbox->numstatus == 1)
		status = 1; /*cmd not supported*/

	/* Check क्रम पूर्णांकerrupt line */
	dword = RDOUTDOOR(raid_dev);
	WROUTDOOR(raid_dev, dword);
	WRINDOOR(raid_dev,2);

	वापस status;

blocked_mailbox:
	con_log(CL_ANN, (KERN_WARNING "megaraid: blocked mailbox\n"));
	वापस status;
पूर्ण

/**
 * megaraid_mbox_display_scb - display SCB inक्रमmation, mostly debug purposes
 * @adapter		: controller's soft state
 * @scb			: SCB to be displayed
 *
 * Diplay inक्रमmation about the given SCB अगरf the current debug level is
 * verbose.
 */
अटल व्योम
megaraid_mbox_display_scb(adapter_t *adapter, scb_t *scb)
अणु
	mbox_ccb_t		*ccb;
	काष्ठा scsi_cmnd	*scp;
	mbox_t			*mbox;
	पूर्णांक			level;
	पूर्णांक			i;


	ccb	= (mbox_ccb_t *)scb->ccb;
	scp	= scb->scp;
	mbox	= ccb->mbox;

	level = CL_DLEVEL3;

	con_log(level, (KERN_NOTICE
		"megaraid mailbox: status:%#x cmd:%#x id:%#x ", scb->status,
		mbox->cmd, scb->sno));

	con_log(level, ("sec:%#x lba:%#x addr:%#x ld:%d sg:%d\n",
		mbox->numsectors, mbox->lba, mbox->xferaddr, mbox->logdrv,
		mbox->numsge));

	अगर (!scp) वापस;

	con_log(level, (KERN_NOTICE "scsi cmnd: "));

	क्रम (i = 0; i < scp->cmd_len; i++) अणु
		con_log(level, ("%#2.02x ", scp->cmnd[i]));
	पूर्ण

	con_log(level, ("\n"));

	वापस;
पूर्ण


/**
 * megaraid_mbox_setup_device_map - manage device ids
 * @adapter	: Driver's soft state
 *
 * Manage the device ids to have an appropriate mapping between the kernel
 * scsi addresses and megaraid scsi and logical drive addresses. We export
 * scsi devices on their actual addresses, whereas the logical drives are
 * exported on a भव scsi channel.
 */
अटल व्योम
megaraid_mbox_setup_device_map(adapter_t *adapter)
अणु
	uपूर्णांक8_t		c;
	uपूर्णांक8_t		t;

	/*
	 * First fill the values on the logical drive channel
	 */
	क्रम (t = 0; t < LSI_MAX_LOGICAL_DRIVES_64LD; t++)
		adapter->device_ids[adapter->max_channel][t] =
			(t < adapter->init_id) ?  t : t - 1;

	adapter->device_ids[adapter->max_channel][adapter->init_id] = 0xFF;

	/*
	 * Fill the values on the physical devices channels
	 */
	क्रम (c = 0; c < adapter->max_channel; c++)
		क्रम (t = 0; t < LSI_MAX_LOGICAL_DRIVES_64LD; t++)
			adapter->device_ids[c][t] = (c << 8) | t;
पूर्ण


/*
 * END: पूर्णांकernal commands library
 */

/*
 * START: Interface क्रम the common management module
 *
 * This is the module, which पूर्णांकerfaces with the common management module to
 * provide support क्रम ioctl and sysfs
 */

/**
 * megaraid_cmm_रेजिस्टर - रेजिस्टर with the management module
 * @adapter		: HBA soft state
 *
 * Register with the management module, which allows applications to issue
 * ioctl calls to the drivers. This पूर्णांकerface is used by the management module
 * to setup sysfs support as well.
 */
अटल पूर्णांक
megaraid_cmm_रेजिस्टर(adapter_t *adapter)
अणु
	mraid_device_t	*raid_dev = ADAP2RAIDDEV(adapter);
	mraid_mmadp_t	adp;
	scb_t		*scb;
	mbox_ccb_t	*ccb;
	पूर्णांक		rval;
	पूर्णांक		i;

	// Allocate memory क्रम the base list of scb क्रम management module.
	adapter->uscb_list = kसुस्मृति(MBOX_MAX_USER_CMDS, माप(scb_t), GFP_KERNEL);

	अगर (adapter->uscb_list == शून्य) अणु
		con_log(CL_ANN, (KERN_WARNING
			"megaraid: out of memory, %s %d\n", __func__,
			__LINE__));
		वापस -1;
	पूर्ण


	// Initialize the synchronization parameters क्रम resources क्रम
	// commands क्रम management module
	INIT_LIST_HEAD(&adapter->uscb_pool);

	spin_lock_init(USER_FREE_LIST_LOCK(adapter));



	// link all the packets. Note, CCB क्रम commands, coming from the
	// commom management module, mailbox physical address are alपढ़ोy
	// setup by it. We just need placeholder क्रम that in our local command
	// control blocks
	क्रम (i = 0; i < MBOX_MAX_USER_CMDS; i++) अणु

		scb			= adapter->uscb_list + i;
		ccb			= raid_dev->uccb_list + i;

		scb->ccb		= (caddr_t)ccb;
		ccb->mbox64		= raid_dev->umbox64 + i;
		ccb->mbox		= &ccb->mbox64->mbox32;
		ccb->raw_mbox		= (uपूर्णांक8_t *)ccb->mbox;

		scb->gp			= 0;

		// COMMAND ID 0 - (MBOX_MAX_SCSI_CMDS-1) ARE RESERVED FOR
		// COMMANDS COMING FROM IO SUBSYSTEM (MID-LAYER)
		scb->sno		= i + MBOX_MAX_SCSI_CMDS;

		scb->scp		= शून्य;
		scb->state		= SCB_FREE;
		scb->dma_direction	= DMA_NONE;
		scb->dma_type		= MRAID_DMA_NONE;
		scb->dev_channel	= -1;
		scb->dev_target		= -1;

		// put scb in the मुक्त pool
		list_add_tail(&scb->list, &adapter->uscb_pool);
	पूर्ण

	adp.unique_id		= adapter->unique_id;
	adp.drvr_type		= DRVRTYPE_MBOX;
	adp.drvr_data		= (अचिन्हित दीर्घ)adapter;
	adp.pdev		= adapter->pdev;
	adp.issue_uioc		= megaraid_mbox_mm_handler;
	adp.समयout		= MBOX_RESET_WAIT + MBOX_RESET_EXT_WAIT;
	adp.max_kioc		= MBOX_MAX_USER_CMDS;

	अगर ((rval = mraid_mm_रेजिस्टर_adp(&adp)) != 0) अणु

		con_log(CL_ANN, (KERN_WARNING
			"megaraid mbox: did not register with CMM\n"));

		kमुक्त(adapter->uscb_list);
	पूर्ण

	वापस rval;
पूर्ण


/**
 * megaraid_cmm_unरेजिस्टर - un-रेजिस्टर with the management module
 * @adapter		: HBA soft state
 *
 * Un-रेजिस्टर with the management module.
 * FIXME: mgmt module must वापस failure क्रम unरेजिस्टर अगर it has pending
 * commands in LLD.
 */
अटल पूर्णांक
megaraid_cmm_unरेजिस्टर(adapter_t *adapter)
अणु
	kमुक्त(adapter->uscb_list);
	mraid_mm_unरेजिस्टर_adp(adapter->unique_id);
	वापस 0;
पूर्ण


/**
 * megaraid_mbox_mm_handler - पूर्णांकerface क्रम CMM to issue commands to LLD
 * @drvr_data		: LLD specअगरic data
 * @kioc		: CMM पूर्णांकerface packet
 * @action		: command action
 *
 * This routine is invoked whenever the Common Management Module (CMM) has a
 * command क्रम us. The 'action' parameter specअगरies अगर this is a new command
 * or otherwise.
 */
अटल पूर्णांक
megaraid_mbox_mm_handler(अचिन्हित दीर्घ drvr_data, uioc_t *kioc, uपूर्णांक32_t action)
अणु
	adapter_t *adapter;

	अगर (action != IOCTL_ISSUE) अणु
		con_log(CL_ANN, (KERN_WARNING
			"megaraid: unsupported management action:%#2x\n",
			action));
		वापस (-ENOTSUPP);
	पूर्ण

	adapter = (adapter_t *)drvr_data;

	// make sure this adapter is not being detached right now.
	अगर (atomic_पढ़ो(&adapter->being_detached)) अणु
		con_log(CL_ANN, (KERN_WARNING
			"megaraid: reject management request, detaching\n"));
		वापस (-ENODEV);
	पूर्ण

	चयन (kioc->opcode) अणु

	हाल GET_ADAP_INFO:

		kioc->status =  gather_hbainfo(adapter, (mraid_hba_info_t *)
					(अचिन्हित दीर्घ)kioc->buf_vaddr);

		kioc->करोne(kioc);

		वापस kioc->status;

	हाल MBOX_CMD:

		वापस megaraid_mbox_mm_command(adapter, kioc);

	शेष:
		kioc->status = (-EINVAL);
		kioc->करोne(kioc);
		वापस (-EINVAL);
	पूर्ण

	वापस 0;	// not reached
पूर्ण

/**
 * megaraid_mbox_mm_command - issues commands routed through CMM
 * @adapter		: HBA soft state
 * @kioc		: management command packet
 *
 * Issues commands, which are routed through the management module.
 */
अटल पूर्णांक
megaraid_mbox_mm_command(adapter_t *adapter, uioc_t *kioc)
अणु
	काष्ठा list_head	*head = &adapter->uscb_pool;
	mbox64_t		*mbox64;
	uपूर्णांक8_t			*raw_mbox;
	scb_t			*scb;
	mbox_ccb_t		*ccb;
	अचिन्हित दीर्घ		flags;

	// detach one scb from मुक्त pool
	spin_lock_irqsave(USER_FREE_LIST_LOCK(adapter), flags);

	अगर (list_empty(head)) अणु	// should never happen because of CMM

		con_log(CL_ANN, (KERN_WARNING
			"megaraid mbox: bug in cmm handler, lost resources\n"));

		spin_unlock_irqrestore(USER_FREE_LIST_LOCK(adapter), flags);

		वापस (-EINVAL);
	पूर्ण

	scb = list_entry(head->next, scb_t, list);
	list_del_init(&scb->list);

	spin_unlock_irqrestore(USER_FREE_LIST_LOCK(adapter), flags);

	scb->state		= SCB_ACTIVE;
	scb->dma_type		= MRAID_DMA_NONE;
	scb->dma_direction	= DMA_NONE;

	ccb		= (mbox_ccb_t *)scb->ccb;
	mbox64		= (mbox64_t *)(अचिन्हित दीर्घ)kioc->cmdbuf;
	raw_mbox	= (uपूर्णांक8_t *)&mbox64->mbox32;

	स_नकल(ccb->mbox64, mbox64, माप(mbox64_t));

	scb->gp		= (अचिन्हित दीर्घ)kioc;

	/*
	 * If it is a logdrv अक्रमom delete operation, we have to रुको till
	 * there are no outstanding cmds at the fw and then issue it directly
	 */
	अगर (raw_mbox[0] == FC_DEL_LOGDRV && raw_mbox[2] == OP_DEL_LOGDRV) अणु

		अगर (रुको_till_fw_empty(adapter)) अणु
			con_log(CL_ANN, (KERN_NOTICE
				"megaraid mbox: LD delete, timed out\n"));

			kioc->status = -ETIME;

			scb->status = -1;

			megaraid_mbox_mm_करोne(adapter, scb);

			वापस (-ETIME);
		पूर्ण

		INIT_LIST_HEAD(&scb->list);

		scb->state = SCB_ISSUED;
		अगर (mbox_post_cmd(adapter, scb) != 0) अणु

			con_log(CL_ANN, (KERN_NOTICE
				"megaraid mbox: LD delete, mailbox busy\n"));

			kioc->status = -EBUSY;

			scb->status = -1;

			megaraid_mbox_mm_करोne(adapter, scb);

			वापस (-EBUSY);
		पूर्ण

		वापस 0;
	पूर्ण

	// put the command on the pending list and execute
	megaraid_mbox_runpendq(adapter, scb);

	वापस 0;
पूर्ण


अटल पूर्णांक
रुको_till_fw_empty(adapter_t *adapter)
अणु
	अचिन्हित दीर्घ	flags = 0;
	पूर्णांक		i;


	/*
	 * Set the quiescent flag to stop issuing cmds to FW.
	 */
	spin_lock_irqsave(&adapter->lock, flags);
	adapter->quiescent++;
	spin_unlock_irqrestore(&adapter->lock, flags);

	/*
	 * Wait till there are no more cmds outstanding at FW. Try क्रम at most
	 * 60 seconds
	 */
	क्रम (i = 0; i < 60 && adapter->outstanding_cmds; i++) अणु
		con_log(CL_DLEVEL1, (KERN_INFO
			"megaraid: FW has %d pending commands\n",
			adapter->outstanding_cmds));

		msleep(1000);
	पूर्ण

	वापस adapter->outstanding_cmds;
पूर्ण


/**
 * megaraid_mbox_mm_करोne - callback क्रम CMM commands
 * @adapter	: HBA soft state
 * @scb		: completed command
 *
 * Callback routine क्रम पूर्णांकernal commands originated from the management
 * module.
 */
अटल व्योम
megaraid_mbox_mm_करोne(adapter_t *adapter, scb_t *scb)
अणु
	uioc_t			*kioc;
	mbox64_t		*mbox64;
	uपूर्णांक8_t			*raw_mbox;
	अचिन्हित दीर्घ		flags;

	kioc			= (uioc_t *)scb->gp;
	mbox64			= (mbox64_t *)(अचिन्हित दीर्घ)kioc->cmdbuf;
	mbox64->mbox32.status	= scb->status;
	raw_mbox		= (uपूर्णांक8_t *)&mbox64->mbox32;


	// put scb in the मुक्त pool
	scb->state	= SCB_FREE;
	scb->scp	= शून्य;

	spin_lock_irqsave(USER_FREE_LIST_LOCK(adapter), flags);

	list_add(&scb->list, &adapter->uscb_pool);

	spin_unlock_irqrestore(USER_FREE_LIST_LOCK(adapter), flags);

	// अगर a delete logical drive operation succeeded, restart the
	// controller
	अगर (raw_mbox[0] == FC_DEL_LOGDRV && raw_mbox[2] == OP_DEL_LOGDRV) अणु

		adapter->quiescent--;

		megaraid_mbox_runpendq(adapter, शून्य);
	पूर्ण

	kioc->करोne(kioc);

	वापस;
पूर्ण


/**
 * gather_hbainfo - HBA अक्षरacteristics क्रम the applications
 * @adapter		: HBA soft state
 * @hinfo		: poपूर्णांकer to the caller's host info strucuture
 */
अटल पूर्णांक
gather_hbainfo(adapter_t *adapter, mraid_hba_info_t *hinfo)
अणु
	hinfo->pci_venकरोr_id	= adapter->pdev->venकरोr;
	hinfo->pci_device_id	= adapter->pdev->device;
	hinfo->subsys_venकरोr_id	= adapter->pdev->subप्रणाली_venकरोr;
	hinfo->subsys_device_id	= adapter->pdev->subप्रणाली_device;

	hinfo->pci_bus		= adapter->pdev->bus->number;
	hinfo->pci_dev_fn	= adapter->pdev->devfn;
	hinfo->pci_slot		= PCI_SLOT(adapter->pdev->devfn);
	hinfo->irq		= adapter->host->irq;
	hinfo->baseport		= ADAP2RAIDDEV(adapter)->baseport;

	hinfo->unique_id	= (hinfo->pci_bus << 8) | adapter->pdev->devfn;
	hinfo->host_no		= adapter->host->host_no;

	वापस 0;
पूर्ण

/*
 * END: Interface क्रम the common management module
 */



/**
 * megaraid_sysfs_alloc_resources - allocate sysfs related resources
 * @adapter	: controller's soft state
 *
 * Allocate packets required to issue FW calls whenever the sysfs attributes
 * are पढ़ो. These attributes would require up-to-date inक्रमmation from the
 * FW. Also set up resources क्रम mutual exclusion to share these resources and
 * the रुको queue.
 *
 * Return 0 on success.
 * Return -ERROR_CODE on failure.
 */
अटल पूर्णांक
megaraid_sysfs_alloc_resources(adapter_t *adapter)
अणु
	mraid_device_t	*raid_dev = ADAP2RAIDDEV(adapter);
	पूर्णांक		rval = 0;

	raid_dev->sysfs_uioc = kदो_स्मृति(माप(uioc_t), GFP_KERNEL);

	raid_dev->sysfs_mbox64 = kदो_स्मृति(माप(mbox64_t), GFP_KERNEL);

	raid_dev->sysfs_buffer = dma_alloc_coherent(&adapter->pdev->dev,
			PAGE_SIZE, &raid_dev->sysfs_buffer_dma, GFP_KERNEL);

	अगर (!raid_dev->sysfs_uioc || !raid_dev->sysfs_mbox64 ||
		!raid_dev->sysfs_buffer) अणु

		con_log(CL_ANN, (KERN_WARNING
			"megaraid: out of memory, %s %d\n", __func__,
			__LINE__));

		rval = -ENOMEM;

		megaraid_sysfs_मुक्त_resources(adapter);
	पूर्ण

	mutex_init(&raid_dev->sysfs_mtx);

	init_रुकोqueue_head(&raid_dev->sysfs_रुको_q);

	वापस rval;
पूर्ण


/**
 * megaraid_sysfs_मुक्त_resources - मुक्त sysfs related resources
 * @adapter	: controller's soft state
 *
 * Free packets allocated क्रम sysfs FW commands
 */
अटल व्योम
megaraid_sysfs_मुक्त_resources(adapter_t *adapter)
अणु
	mraid_device_t	*raid_dev = ADAP2RAIDDEV(adapter);

	kमुक्त(raid_dev->sysfs_uioc);
	kमुक्त(raid_dev->sysfs_mbox64);

	अगर (raid_dev->sysfs_buffer) अणु
		dma_मुक्त_coherent(&adapter->pdev->dev, PAGE_SIZE,
			raid_dev->sysfs_buffer, raid_dev->sysfs_buffer_dma);
	पूर्ण
पूर्ण


/**
 * megaraid_sysfs_get_ldmap_करोne - callback क्रम get ldmap
 * @uioc	: completed packet
 *
 * Callback routine called in the ISR/tasklet context क्रम get ldmap call
 */
अटल व्योम
megaraid_sysfs_get_ldmap_करोne(uioc_t *uioc)
अणु
	adapter_t	*adapter = (adapter_t *)uioc->buf_vaddr;
	mraid_device_t	*raid_dev = ADAP2RAIDDEV(adapter);

	uioc->status = 0;

	wake_up(&raid_dev->sysfs_रुको_q);
पूर्ण

/**
 * megaraid_sysfs_get_ldmap_समयout - समयout handling क्रम get ldmap
 * @t	: समयd out समयr
 *
 * Timeout routine to recover and वापस to application, in हाल the adapter
 * has stopped responding. A समयout of 60 seconds क्रम this command seems like
 * a good value.
 */
अटल व्योम
megaraid_sysfs_get_ldmap_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा uioc_समयout *समयout = from_समयr(समयout, t, समयr);
	uioc_t		*uioc = समयout->uioc;
	adapter_t	*adapter = (adapter_t *)uioc->buf_vaddr;
	mraid_device_t	*raid_dev = ADAP2RAIDDEV(adapter);

	uioc->status = -ETIME;

	wake_up(&raid_dev->sysfs_रुको_q);
पूर्ण


/**
 * megaraid_sysfs_get_ldmap - get update logical drive map
 * @adapter	: controller's soft state
 *
 * This routine will be called whenever user पढ़ोs the logical drive
 * attributes, go get the current logical drive mapping table from the
 * firmware. We use the management API's to issue commands to the controller.
 *
 * NOTE: The commands issuance functionality is not generalized and
 * implemented in context of "get ld map" command only. If required, the
 * command issuance logical can be trivially pulled out and implemented as a
 * standalone library. For now, this should suffice since there is no other
 * user of this पूर्णांकerface.
 *
 * Return 0 on success.
 * Return -1 on failure.
 */
अटल पूर्णांक
megaraid_sysfs_get_ldmap(adapter_t *adapter)
अणु
	mraid_device_t		*raid_dev = ADAP2RAIDDEV(adapter);
	uioc_t			*uioc;
	mbox64_t		*mbox64;
	mbox_t			*mbox;
	अक्षर			*raw_mbox;
	काष्ठा uioc_समयout	समयout;
	caddr_t			ldmap;
	पूर्णांक			rval = 0;

	/*
	 * Allow only one पढ़ो at a समय to go through the sysfs attributes
	 */
	mutex_lock(&raid_dev->sysfs_mtx);

	uioc	= raid_dev->sysfs_uioc;
	mbox64	= raid_dev->sysfs_mbox64;
	ldmap	= raid_dev->sysfs_buffer;

	स_रखो(uioc, 0, माप(uioc_t));
	स_रखो(mbox64, 0, माप(mbox64_t));
	स_रखो(ldmap, 0, माप(raid_dev->curr_ldmap));

	mbox		= &mbox64->mbox32;
	raw_mbox	= (अक्षर *)mbox;
	uioc->cmdbuf    = (uपूर्णांक64_t)(अचिन्हित दीर्घ)mbox64;
	uioc->buf_vaddr	= (caddr_t)adapter;
	uioc->status	= -ENODATA;
	uioc->करोne	= megaraid_sysfs_get_ldmap_करोne;

	/*
	 * Prepare the mailbox packet to get the current logical drive mapping
	 * table
	 */
	mbox->xferaddr = (uपूर्णांक32_t)raid_dev->sysfs_buffer_dma;

	raw_mbox[0] = FC_DEL_LOGDRV;
	raw_mbox[2] = OP_GET_LDID_MAP;

	/*
	 * Setup a समयr to recover from a non-responding controller
	 */
	समयout.uioc = uioc;
	समयr_setup_on_stack(&समयout.समयr,
			     megaraid_sysfs_get_ldmap_समयout, 0);

	समयout.समयr.expires		= jअगरfies + 60 * HZ;
	add_समयr(&समयout.समयr);

	/*
	 * Send the command to the firmware
	 */
	rval = megaraid_mbox_mm_command(adapter, uioc);

	अगर (rval == 0) अणु	// command successfully issued
		रुको_event(raid_dev->sysfs_रुको_q, (uioc->status != -ENODATA));

		/*
		 * Check अगर the command समयd out
		 */
		अगर (uioc->status == -ETIME) अणु
			con_log(CL_ANN, (KERN_NOTICE
				"megaraid: sysfs get ld map timed out\n"));

			rval = -ETIME;
		पूर्ण
		अन्यथा अणु
			rval = mbox->status;
		पूर्ण

		अगर (rval == 0) अणु
			स_नकल(raid_dev->curr_ldmap, ldmap,
				माप(raid_dev->curr_ldmap));
		पूर्ण
		अन्यथा अणु
			con_log(CL_ANN, (KERN_NOTICE
				"megaraid: get ld map failed with %x\n", rval));
		पूर्ण
	पूर्ण
	अन्यथा अणु
		con_log(CL_ANN, (KERN_NOTICE
			"megaraid: could not issue ldmap command:%x\n", rval));
	पूर्ण


	del_समयr_sync(&समयout.समयr);
	destroy_समयr_on_stack(&समयout.समयr);

	mutex_unlock(&raid_dev->sysfs_mtx);

	वापस rval;
पूर्ण


/**
 * megaraid_sysfs_show_app_hndl - display application handle क्रम this adapter
 * @dev		: class device object representation क्रम the host
 * @attr	: device attribute (unused)
 * @buf		: buffer to send data to
 *
 * Display the handle used by the applications जबतक executing management
 * tasks on the adapter. We invoke a management module API to get the adapter
 * handle, since we करो not पूर्णांकerface with applications directly.
 */
अटल sमाप_प्रकार
megaraid_sysfs_show_app_hndl(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	adapter_t	*adapter = (adapter_t *)SCSIHOST2ADAP(shost);
	uपूर्णांक32_t	app_hndl;

	app_hndl = mraid_mm_adapter_app_handle(adapter->unique_id);

	वापस snम_लिखो(buf, 8, "%u\n", app_hndl);
पूर्ण


/**
 * megaraid_sysfs_show_ldnum - display the logical drive number क्रम this device
 * @dev		: device object representation क्रम the scsi device
 * @attr	: device attribute to show
 * @buf		: buffer to send data to
 *
 * Display the logical drive number क्रम the device in question, अगर it a valid
 * logical drive. For physical devices, "-1" is वापसed.
 *
 * The logical drive number is displayed in following क्रमmat:
 *
 * <SCSI ID> <LD NUM> <LD STICKY ID> <APP ADAPTER HANDLE>
 *
 *   <पूर्णांक>     <पूर्णांक>       <पूर्णांक>            <पूर्णांक>
 */
अटल sमाप_प्रकार
megaraid_sysfs_show_ldnum(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(dev);
	adapter_t	*adapter = (adapter_t *)SCSIHOST2ADAP(sdev->host);
	mraid_device_t	*raid_dev = ADAP2RAIDDEV(adapter);
	पूर्णांक		scsi_id = -1;
	पूर्णांक		logical_drv = -1;
	पूर्णांक		ldid_map = -1;
	uपूर्णांक32_t	app_hndl = 0;
	पूर्णांक		mapped_sdev_id;
	पूर्णांक		rval;
	पूर्णांक		i;

	अगर (raid_dev->अक्रमom_del_supported &&
			MRAID_IS_LOGICAL_SDEV(adapter, sdev)) अणु

		rval = megaraid_sysfs_get_ldmap(adapter);
		अगर (rval == 0) अणु

			क्रम (i = 0; i < MAX_LOGICAL_DRIVES_40LD; i++) अणु

				mapped_sdev_id = sdev->id;

				अगर (sdev->id > adapter->init_id) अणु
					mapped_sdev_id -= 1;
				पूर्ण

				अगर (raid_dev->curr_ldmap[i] == mapped_sdev_id) अणु

					scsi_id = sdev->id;

					logical_drv = i;

					ldid_map = raid_dev->curr_ldmap[i];

					app_hndl = mraid_mm_adapter_app_handle(
							adapter->unique_id);

					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
		अन्यथा अणु
			con_log(CL_ANN, (KERN_NOTICE
				"megaraid: sysfs get ld map failed: %x\n",
				rval));
		पूर्ण
	पूर्ण

	वापस snम_लिखो(buf, 36, "%d %d %d %d\n", scsi_id, logical_drv,
			ldid_map, app_hndl);
पूर्ण


/*
 * END: Mailbox Low Level Driver
 */
module_init(megaraid_init);
module_निकास(megaraid_निकास);
