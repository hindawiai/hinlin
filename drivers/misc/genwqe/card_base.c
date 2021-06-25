<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/**
 * IBM Accelerator Family 'GenWQE'
 *
 * (C) Copyright IBM Corp. 2013
 *
 * Author: Frank Haverkamp <haver@linux.vnet.ibm.com>
 * Author: Joerg-Stephan Vogt <jsvogt@de.ibm.com>
 * Author: Michael Jung <mijung@gmx.net>
 * Author: Michael Ruettger <michael@ibmra.de>
 */

/*
 * Module initialization and PCIe setup. Card health monitoring and
 * recovery functionality. Character device creation and deletion are
 * controlled from here.
 */

#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/err.h>
#समावेश <linux/aer.h>
#समावेश <linux/माला.स>
#समावेश <linux/sched.h>
#समावेश <linux/रुको.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/module.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/device.h>
#समावेश <linux/log2.h>

#समावेश "card_base.h"
#समावेश "card_ddcb.h"

MODULE_AUTHOR("Frank Haverkamp <haver@linux.vnet.ibm.com>");
MODULE_AUTHOR("Michael Ruettger <michael@ibmra.de>");
MODULE_AUTHOR("Joerg-Stephan Vogt <jsvogt@de.ibm.com>");
MODULE_AUTHOR("Michael Jung <mijung@gmx.net>");

MODULE_DESCRIPTION("GenWQE Card");
MODULE_VERSION(DRV_VERSION);
MODULE_LICENSE("GPL");

अटल अक्षर genwqe_driver_name[] = GENWQE_DEVNAME;
अटल काष्ठा class *class_genwqe;
अटल काष्ठा dentry *debugfs_genwqe;
अटल काष्ठा genwqe_dev *genwqe_devices[GENWQE_CARD_NO_MAX];

/* PCI काष्ठाure क्रम identअगरying device by PCI venकरोr and device ID */
अटल स्थिर काष्ठा pci_device_id genwqe_device_table[] = अणु
	अणु .venकरोr      = PCI_VENDOR_ID_IBM,
	  .device      = PCI_DEVICE_GENWQE,
	  .subvenकरोr   = PCI_SUBVENDOR_ID_IBM,
	  .subdevice   = PCI_SUBSYSTEM_ID_GENWQE5,
	  .class       = (PCI_CLASSCODE_GENWQE5 << 8),
	  .class_mask  = ~0,
	  .driver_data = 0 पूर्ण,

	/* Initial SR-IOV bring-up image */
	अणु .venकरोr      = PCI_VENDOR_ID_IBM,
	  .device      = PCI_DEVICE_GENWQE,
	  .subvenकरोr   = PCI_SUBVENDOR_ID_IBM_SRIOV,
	  .subdevice   = PCI_SUBSYSTEM_ID_GENWQE5_SRIOV,
	  .class       = (PCI_CLASSCODE_GENWQE5_SRIOV << 8),
	  .class_mask  = ~0,
	  .driver_data = 0 पूर्ण,

	अणु .venकरोr      = PCI_VENDOR_ID_IBM,  /* VF Venकरोr ID */
	  .device      = 0x0000,  /* VF Device ID */
	  .subvenकरोr   = PCI_SUBVENDOR_ID_IBM_SRIOV,
	  .subdevice   = PCI_SUBSYSTEM_ID_GENWQE5_SRIOV,
	  .class       = (PCI_CLASSCODE_GENWQE5_SRIOV << 8),
	  .class_mask  = ~0,
	  .driver_data = 0 पूर्ण,

	/* Fixed up image */
	अणु .venकरोr      = PCI_VENDOR_ID_IBM,
	  .device      = PCI_DEVICE_GENWQE,
	  .subvenकरोr   = PCI_SUBVENDOR_ID_IBM_SRIOV,
	  .subdevice   = PCI_SUBSYSTEM_ID_GENWQE5,
	  .class       = (PCI_CLASSCODE_GENWQE5_SRIOV << 8),
	  .class_mask  = ~0,
	  .driver_data = 0 पूर्ण,

	अणु .venकरोr      = PCI_VENDOR_ID_IBM,  /* VF Venकरोr ID */
	  .device      = 0x0000,  /* VF Device ID */
	  .subvenकरोr   = PCI_SUBVENDOR_ID_IBM_SRIOV,
	  .subdevice   = PCI_SUBSYSTEM_ID_GENWQE5,
	  .class       = (PCI_CLASSCODE_GENWQE5_SRIOV << 8),
	  .class_mask  = ~0,
	  .driver_data = 0 पूर्ण,

	/* Even one more ... */
	अणु .venकरोr      = PCI_VENDOR_ID_IBM,
	  .device      = PCI_DEVICE_GENWQE,
	  .subvenकरोr   = PCI_SUBVENDOR_ID_IBM,
	  .subdevice   = PCI_SUBSYSTEM_ID_GENWQE5_NEW,
	  .class       = (PCI_CLASSCODE_GENWQE5 << 8),
	  .class_mask  = ~0,
	  .driver_data = 0 पूर्ण,

	अणु 0, पूर्ण			/* 0 terminated list. */
पूर्ण;

MODULE_DEVICE_TABLE(pci, genwqe_device_table);

/**
 * genwqe_dev_alloc() - Create and prepare a new card descriptor
 *
 * Return: Poपूर्णांकer to card descriptor, or ERR_PTR(err) on error
 */
अटल काष्ठा genwqe_dev *genwqe_dev_alloc(व्योम)
अणु
	अचिन्हित पूर्णांक i = 0, j;
	काष्ठा genwqe_dev *cd;

	क्रम (i = 0; i < GENWQE_CARD_NO_MAX; i++) अणु
		अगर (genwqe_devices[i] == शून्य)
			अवरोध;
	पूर्ण
	अगर (i >= GENWQE_CARD_NO_MAX)
		वापस ERR_PTR(-ENODEV);

	cd = kzalloc(माप(काष्ठा genwqe_dev), GFP_KERNEL);
	अगर (!cd)
		वापस ERR_PTR(-ENOMEM);

	cd->card_idx = i;
	cd->class_genwqe = class_genwqe;
	cd->debugfs_genwqe = debugfs_genwqe;

	/*
	 * This comes from kernel config option and can be overritten via
	 * debugfs.
	 */
	cd->use_platक्रमm_recovery = CONFIG_GENWQE_PLATFORM_ERROR_RECOVERY;

	init_रुकोqueue_head(&cd->queue_रुकोq);

	spin_lock_init(&cd->file_lock);
	INIT_LIST_HEAD(&cd->file_list);

	cd->card_state = GENWQE_CARD_UNUSED;
	spin_lock_init(&cd->prपूर्णांक_lock);

	cd->ddcb_software_समयout = GENWQE_DDCB_SOFTWARE_TIMEOUT;
	cd->समाप्त_समयout = GENWQE_KILL_TIMEOUT;

	क्रम (j = 0; j < GENWQE_MAX_VFS; j++)
		cd->vf_jobसमयout_msec[j] = GENWQE_VF_JOBTIMEOUT_MSEC;

	genwqe_devices[i] = cd;
	वापस cd;
पूर्ण

अटल व्योम genwqe_dev_मुक्त(काष्ठा genwqe_dev *cd)
अणु
	अगर (!cd)
		वापस;

	genwqe_devices[cd->card_idx] = शून्य;
	kमुक्त(cd);
पूर्ण

/**
 * genwqe_bus_reset() - Card recovery
 * @cd: GenWQE device inक्रमmation
 *
 * pci_reset_function() will recover the device and ensure that the
 * रेजिस्टरs are accessible again when it completes with success. If
 * not, the card will stay dead and रेजिस्टरs will be unaccessible
 * still.
 */
अटल पूर्णांक genwqe_bus_reset(काष्ठा genwqe_dev *cd)
अणु
	पूर्णांक rc = 0;
	काष्ठा pci_dev *pci_dev = cd->pci_dev;
	व्योम __iomem *mmio;

	अगर (cd->err_inject & GENWQE_INJECT_BUS_RESET_FAILURE)
		वापस -EIO;

	mmio = cd->mmio;
	cd->mmio = शून्य;
	pci_iounmap(pci_dev, mmio);

	pci_release_mem_regions(pci_dev);

	/*
	 * Firmware/BIOS might change memory mapping during bus reset.
	 * Settings like enable bus-mastering, ... are backuped and
	 * restored by the pci_reset_function().
	 */
	dev_dbg(&pci_dev->dev, "[%s] pci_reset function ...\n", __func__);
	rc = pci_reset_function(pci_dev);
	अगर (rc) अणु
		dev_err(&pci_dev->dev,
			"[%s] err: failed reset func (rc %d)\n", __func__, rc);
		वापस rc;
	पूर्ण
	dev_dbg(&pci_dev->dev, "[%s] done with rc=%d\n", __func__, rc);

	/*
	 * Here is the right spot to clear the रेजिस्टर पढ़ो
	 * failure. pci_bus_reset() करोes this job in real प्रणालीs.
	 */
	cd->err_inject &= ~(GENWQE_INJECT_HARDWARE_FAILURE |
			    GENWQE_INJECT_GFIR_FATAL |
			    GENWQE_INJECT_GFIR_INFO);

	rc = pci_request_mem_regions(pci_dev, genwqe_driver_name);
	अगर (rc) अणु
		dev_err(&pci_dev->dev,
			"[%s] err: request bars failed (%d)\n", __func__, rc);
		वापस -EIO;
	पूर्ण

	cd->mmio = pci_iomap(pci_dev, 0, 0);
	अगर (cd->mmio == शून्य) अणु
		dev_err(&pci_dev->dev,
			"[%s] err: mapping BAR0 failed\n", __func__);
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Hardware circumvention section. Certain bitstreams in our test-lab
 * had dअगरferent kinds of problems. Here is where we adjust those
 * bitstreams to function will with this version of our device driver.
 *
 * Thise circumventions are applied to the physical function only.
 * The magical numbers below are identअगरying development/manufacturing
 * versions of the bitstream used on the card.
 *
 * Turn off error reporting क्रम old/manufacturing images.
 */

bool genwqe_need_err_masking(काष्ठा genwqe_dev *cd)
अणु
	वापस (cd->slu_unitcfg & 0xFFFF0ull) < 0x32170ull;
पूर्ण

अटल व्योम genwqe_tweak_hardware(काष्ठा genwqe_dev *cd)
अणु
	काष्ठा pci_dev *pci_dev = cd->pci_dev;

	/* Mask FIRs क्रम development images */
	अगर (((cd->slu_unitcfg & 0xFFFF0ull) >= 0x32000ull) &&
	    ((cd->slu_unitcfg & 0xFFFF0ull) <= 0x33250ull)) अणु
		dev_warn(&pci_dev->dev,
			 "FIRs masked due to bitstream %016llx.%016llx\n",
			 cd->slu_unitcfg, cd->app_unitcfg);

		__genwqe_ग_लिखोq(cd, IO_APP_SEC_LEM_DEBUG_OVR,
				0xFFFFFFFFFFFFFFFFull);

		__genwqe_ग_लिखोq(cd, IO_APP_ERR_ACT_MASK,
				0x0000000000000000ull);
	पूर्ण
पूर्ण

/**
 * genwqe_recovery_on_fatal_gfir_required() - Version depended actions
 * @cd: GenWQE device inक्रमmation
 *
 * Bitstreams older than 2013-02-17 have a bug where fatal GFIRs must
 * be ignored. This is e.g. true क्रम the bitstream we gave to the card
 * manufacturer, but also क्रम some old bitstreams we released to our
 * test-lab.
 */
पूर्णांक genwqe_recovery_on_fatal_gfir_required(काष्ठा genwqe_dev *cd)
अणु
	वापस (cd->slu_unitcfg & 0xFFFF0ull) >= 0x32170ull;
पूर्ण

पूर्णांक genwqe_flash_पढ़ोback_fails(काष्ठा genwqe_dev *cd)
अणु
	वापस (cd->slu_unitcfg & 0xFFFF0ull) < 0x32170ull;
पूर्ण

/**
 * genwqe_T_psec() - Calculate PF/VF समयout रेजिस्टर content
 * @cd: GenWQE device inक्रमmation
 *
 * Note: From a design perspective it turned out to be a bad idea to
 * use codes here to specअगरiy the frequency/speed values. An old
 * driver cannot understand new codes and is thereक्रमe always a
 * problem. Better is to measure out the value or put the
 * speed/frequency directly पूर्णांकo a रेजिस्टर which is always a valid
 * value क्रम old as well as क्रम new software.
 */
/* T = 1/f */
अटल पूर्णांक genwqe_T_psec(काष्ठा genwqe_dev *cd)
अणु
	u16 speed;	/* 1/f -> 250,  200,  166,  175 */
	अटल स्थिर पूर्णांक T[] = अणु 4000, 5000, 6000, 5714 पूर्ण;

	speed = (u16)((cd->slu_unitcfg >> 28) & 0x0full);
	अगर (speed >= ARRAY_SIZE(T))
		वापस -1;	/* illegal value */

	वापस T[speed];
पूर्ण

/**
 * genwqe_setup_pf_jसमयr() - Setup PF hardware समयouts क्रम DDCB execution
 * @cd: GenWQE device inक्रमmation
 *
 * Do this _after_ card_reset() is called. Otherwise the values will
 * vanish. The settings need to be करोne when the queues are inactive.
 *
 * The max. समयout value is 2^(10+x) * T (6ns क्रम 166MHz) * 15/16.
 * The min. समयout value is 2^(10+x) * T (6ns क्रम 166MHz) * 14/16.
 */
अटल bool genwqe_setup_pf_jसमयr(काष्ठा genwqe_dev *cd)
अणु
	u32 T = genwqe_T_psec(cd);
	u64 x;

	अगर (GENWQE_PF_JOBTIMEOUT_MSEC == 0)
		वापस false;

	/* PF: large value needed, flash update 2sec per block */
	x = ilog2(GENWQE_PF_JOBTIMEOUT_MSEC *
		  16000000000uL/(T * 15)) - 10;

	genwqe_ग_लिखो_vreg(cd, IO_SLC_VF_APPJOB_TIMEOUT,
			  0xff00 | (x & 0xff), 0);
	वापस true;
पूर्ण

/**
 * genwqe_setup_vf_jसमयr() - Setup VF hardware समयouts क्रम DDCB execution
 * @cd: GenWQE device inक्रमmation
 */
अटल bool genwqe_setup_vf_jसमयr(काष्ठा genwqe_dev *cd)
अणु
	काष्ठा pci_dev *pci_dev = cd->pci_dev;
	अचिन्हित पूर्णांक vf;
	u32 T = genwqe_T_psec(cd);
	u64 x;
	पूर्णांक totalvfs;

	totalvfs = pci_sriov_get_totalvfs(pci_dev);
	अगर (totalvfs <= 0)
		वापस false;

	क्रम (vf = 0; vf < totalvfs; vf++) अणु

		अगर (cd->vf_jobसमयout_msec[vf] == 0)
			जारी;

		x = ilog2(cd->vf_jobसमयout_msec[vf] *
			  16000000000uL/(T * 15)) - 10;

		genwqe_ग_लिखो_vreg(cd, IO_SLC_VF_APPJOB_TIMEOUT,
				  0xff00 | (x & 0xff), vf + 1);
	पूर्ण
	वापस true;
पूर्ण

अटल पूर्णांक genwqe_ffdc_buffs_alloc(काष्ठा genwqe_dev *cd)
अणु
	अचिन्हित पूर्णांक type, e = 0;

	क्रम (type = 0; type < GENWQE_DBG_UNITS; type++) अणु
		चयन (type) अणु
		हाल GENWQE_DBG_UNIT0:
			e = genwqe_ffdc_buff_size(cd, 0);
			अवरोध;
		हाल GENWQE_DBG_UNIT1:
			e = genwqe_ffdc_buff_size(cd, 1);
			अवरोध;
		हाल GENWQE_DBG_UNIT2:
			e = genwqe_ffdc_buff_size(cd, 2);
			अवरोध;
		हाल GENWQE_DBG_REGS:
			e = GENWQE_FFDC_REGS;
			अवरोध;
		पूर्ण

		/* currently support only the debug units mentioned here */
		cd->ffdc[type].entries = e;
		cd->ffdc[type].regs =
			kदो_स्मृति_array(e, माप(काष्ठा genwqe_reg),
				      GFP_KERNEL);
		/*
		 * regs == शून्य is ok, the using code treats this as no regs,
		 * Prपूर्णांकing warning is ok in this हाल.
		 */
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम genwqe_ffdc_buffs_मुक्त(काष्ठा genwqe_dev *cd)
अणु
	अचिन्हित पूर्णांक type;

	क्रम (type = 0; type < GENWQE_DBG_UNITS; type++) अणु
		kमुक्त(cd->ffdc[type].regs);
		cd->ffdc[type].regs = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक genwqe_पढ़ो_ids(काष्ठा genwqe_dev *cd)
अणु
	पूर्णांक err = 0;
	पूर्णांक slu_id;
	काष्ठा pci_dev *pci_dev = cd->pci_dev;

	cd->slu_unitcfg = __genwqe_पढ़ोq(cd, IO_SLU_UNITCFG);
	अगर (cd->slu_unitcfg == IO_ILLEGAL_VALUE) अणु
		dev_err(&pci_dev->dev,
			"err: SLUID=%016llx\n", cd->slu_unitcfg);
		err = -EIO;
		जाओ out_err;
	पूर्ण

	slu_id = genwqe_get_slu_id(cd);
	अगर (slu_id < GENWQE_SLU_ARCH_REQ || slu_id == 0xff) अणु
		dev_err(&pci_dev->dev,
			"err: incompatible SLU Architecture %u\n", slu_id);
		err = -ENOENT;
		जाओ out_err;
	पूर्ण

	cd->app_unitcfg = __genwqe_पढ़ोq(cd, IO_APP_UNITCFG);
	अगर (cd->app_unitcfg == IO_ILLEGAL_VALUE) अणु
		dev_err(&pci_dev->dev,
			"err: APPID=%016llx\n", cd->app_unitcfg);
		err = -EIO;
		जाओ out_err;
	पूर्ण
	genwqe_पढ़ो_app_id(cd, cd->app_name, माप(cd->app_name));

	/*
	 * Is access to all रेजिस्टरs possible? If we are a VF the
	 * answer is obvious. If we run fully भवized, we need to
	 * check अगर we can access all रेजिस्टरs. If we करो not have
	 * full access we will cause an UR and some inक्रमmational FIRs
	 * in the PF, but that should not harm.
	 */
	अगर (pci_dev->is_virtfn)
		cd->is_privileged = 0;
	अन्यथा
		cd->is_privileged = (__genwqe_पढ़ोq(cd, IO_SLU_BITSTREAM)
				     != IO_ILLEGAL_VALUE);

 out_err:
	वापस err;
पूर्ण

अटल पूर्णांक genwqe_start(काष्ठा genwqe_dev *cd)
अणु
	पूर्णांक err;
	काष्ठा pci_dev *pci_dev = cd->pci_dev;

	err = genwqe_पढ़ो_ids(cd);
	अगर (err)
		वापस err;

	अगर (genwqe_is_privileged(cd)) अणु
		/* करो this after the tweaks. alloc fail is acceptable */
		genwqe_ffdc_buffs_alloc(cd);
		genwqe_stop_traps(cd);

		/* Collect रेजिस्टरs e.g. FIRs, UNITIDs, traces ... */
		genwqe_पढ़ो_ffdc_regs(cd, cd->ffdc[GENWQE_DBG_REGS].regs,
				      cd->ffdc[GENWQE_DBG_REGS].entries, 0);

		genwqe_ffdc_buff_पढ़ो(cd, GENWQE_DBG_UNIT0,
				      cd->ffdc[GENWQE_DBG_UNIT0].regs,
				      cd->ffdc[GENWQE_DBG_UNIT0].entries);

		genwqe_ffdc_buff_पढ़ो(cd, GENWQE_DBG_UNIT1,
				      cd->ffdc[GENWQE_DBG_UNIT1].regs,
				      cd->ffdc[GENWQE_DBG_UNIT1].entries);

		genwqe_ffdc_buff_पढ़ो(cd, GENWQE_DBG_UNIT2,
				      cd->ffdc[GENWQE_DBG_UNIT2].regs,
				      cd->ffdc[GENWQE_DBG_UNIT2].entries);

		genwqe_start_traps(cd);

		अगर (cd->card_state == GENWQE_CARD_FATAL_ERROR) अणु
			dev_warn(&pci_dev->dev,
				 "[%s] chip reload/recovery!\n", __func__);

			/*
			 * Stealth Mode: Reload chip on either hot
			 * reset or PERST.
			 */
			cd->softreset = 0x7Cull;
			__genwqe_ग_लिखोq(cd, IO_SLC_CFGREG_SOFTRESET,
				       cd->softreset);

			err = genwqe_bus_reset(cd);
			अगर (err != 0) अणु
				dev_err(&pci_dev->dev,
					"[%s] err: bus reset failed!\n",
					__func__);
				जाओ out;
			पूर्ण

			/*
			 * Re-पढ़ो the IDs because
			 * it could happen that the bitstream load
			 * failed!
			 */
			err = genwqe_पढ़ो_ids(cd);
			अगर (err)
				जाओ out;
		पूर्ण
	पूर्ण

	err = genwqe_setup_service_layer(cd);  /* करोes a reset to the card */
	अगर (err != 0) अणु
		dev_err(&pci_dev->dev,
			"[%s] err: could not setup servicelayer!\n", __func__);
		err = -ENODEV;
		जाओ out;
	पूर्ण

	अगर (genwqe_is_privileged(cd)) अणु	 /* code is running _after_ reset */
		genwqe_tweak_hardware(cd);

		genwqe_setup_pf_jसमयr(cd);
		genwqe_setup_vf_jसमयr(cd);
	पूर्ण

	err = genwqe_device_create(cd);
	अगर (err < 0) अणु
		dev_err(&pci_dev->dev,
			"err: chdev init failed! (err=%d)\n", err);
		जाओ out_release_service_layer;
	पूर्ण
	वापस 0;

 out_release_service_layer:
	genwqe_release_service_layer(cd);
 out:
	अगर (genwqe_is_privileged(cd))
		genwqe_ffdc_buffs_मुक्त(cd);
	वापस -EIO;
पूर्ण

/**
 * genwqe_stop() - Stop card operation
 * @cd: GenWQE device inक्रमmation
 *
 * Recovery notes:
 *   As दीर्घ as genwqe_thपढ़ो runs we might access रेजिस्टरs during
 *   error data capture. Same is with the genwqe_health_thपढ़ो.
 *   When genwqe_bus_reset() fails this function might called two बार:
 *   first by the genwqe_health_thपढ़ो() and later by genwqe_हटाओ() to
 *   unbind the device. We must be able to survive that.
 *
 * This function must be robust enough to be called twice.
 */
अटल पूर्णांक genwqe_stop(काष्ठा genwqe_dev *cd)
अणु
	genwqe_finish_queue(cd);	    /* no रेजिस्टर access */
	genwqe_device_हटाओ(cd);	    /* device हटाओd, procs समाप्तed */
	genwqe_release_service_layer(cd);   /* here genwqe_thपढ़ो is stopped */

	अगर (genwqe_is_privileged(cd)) अणु
		pci_disable_sriov(cd->pci_dev);	/* access pci config space */
		genwqe_ffdc_buffs_मुक्त(cd);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * genwqe_recover_card() - Try to recover the card अगर it is possible
 * @cd: GenWQE device inक्रमmation
 * @fatal_err: Indicate whether to attempt soft reset
 *
 * If fatal_err is set no रेजिस्टर access is possible anymore. It is
 * likely that genwqe_start fails in that situation. Proper error
 * handling is required in this हाल.
 *
 * genwqe_bus_reset() will cause the pci code to call genwqe_हटाओ()
 * and later genwqe_probe() क्रम all भव functions.
 */
अटल पूर्णांक genwqe_recover_card(काष्ठा genwqe_dev *cd, पूर्णांक fatal_err)
अणु
	पूर्णांक rc;
	काष्ठा pci_dev *pci_dev = cd->pci_dev;

	genwqe_stop(cd);

	/*
	 * Make sure chip is not reloaded to मुख्यtain FFDC. Write SLU
	 * Reset Register, CPLDReset field to 0.
	 */
	अगर (!fatal_err) अणु
		cd->softreset = 0x70ull;
		__genwqe_ग_लिखोq(cd, IO_SLC_CFGREG_SOFTRESET, cd->softreset);
	पूर्ण

	rc = genwqe_bus_reset(cd);
	अगर (rc != 0) अणु
		dev_err(&pci_dev->dev,
			"[%s] err: card recovery impossible!\n", __func__);
		वापस rc;
	पूर्ण

	rc = genwqe_start(cd);
	अगर (rc < 0) अणु
		dev_err(&pci_dev->dev,
			"[%s] err: failed to launch device!\n", __func__);
		वापस rc;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक genwqe_health_check_cond(काष्ठा genwqe_dev *cd, u64 *gfir)
अणु
	*gfir = __genwqe_पढ़ोq(cd, IO_SLC_CFGREG_GFIR);
	वापस (*gfir & GFIR_ERR_TRIGGER) &&
		genwqe_recovery_on_fatal_gfir_required(cd);
पूर्ण

/**
 * genwqe_fir_checking() - Check the fault isolation रेजिस्टरs of the card
 * @cd: GenWQE device inक्रमmation
 *
 * If this code works ok, can be tried out with help of the genwqe_poke tool:
 *   suकरो ./tools/genwqe_poke 0x8 0xfefefefefef
 *
 * Now the relevant FIRs/sFIRs should be prपूर्णांकed out and the driver should
 * invoke recovery (devices are हटाओd and पढ़ोded).
 */
अटल u64 genwqe_fir_checking(काष्ठा genwqe_dev *cd)
अणु
	पूर्णांक j, iterations = 0;
	u64 mask, fir, fec, uid, gfir, gfir_masked, sfir, sfec;
	u32 fir_addr, fir_clr_addr, fec_addr, sfir_addr, sfec_addr;
	काष्ठा pci_dev *pci_dev = cd->pci_dev;

 healthMonitor:
	iterations++;
	अगर (iterations > 16) अणु
		dev_err(&pci_dev->dev, "* exit looping after %d times\n",
			iterations);
		जाओ fatal_error;
	पूर्ण

	gfir = __genwqe_पढ़ोq(cd, IO_SLC_CFGREG_GFIR);
	अगर (gfir != 0x0)
		dev_err(&pci_dev->dev, "* 0x%08x 0x%016llx\n",
				    IO_SLC_CFGREG_GFIR, gfir);
	अगर (gfir == IO_ILLEGAL_VALUE)
		जाओ fatal_error;

	/*
	 * Aव्योम prपूर्णांकing when to GFIR bit is on prevents contignous
	 * prपूर्णांकout e.g. क्रम the following bug:
	 *   FIR set without a 2ndary FIR/FIR cannot be cleared
	 * Comment out the following अगर to get the prपूर्णांकs:
	 */
	अगर (gfir == 0)
		वापस 0;

	gfir_masked = gfir & GFIR_ERR_TRIGGER;  /* fatal errors */

	क्रम (uid = 0; uid < GENWQE_MAX_UNITS; uid++) अणु /* 0..2 in zEDC */

		/* पढ़ो the primary FIR (pfir) */
		fir_addr = (uid << 24) + 0x08;
		fir = __genwqe_पढ़ोq(cd, fir_addr);
		अगर (fir == 0x0)
			जारी;  /* no error in this unit */

		dev_err(&pci_dev->dev, "* 0x%08x 0x%016llx\n", fir_addr, fir);
		अगर (fir == IO_ILLEGAL_VALUE)
			जाओ fatal_error;

		/* पढ़ो primary FEC */
		fec_addr = (uid << 24) + 0x18;
		fec = __genwqe_पढ़ोq(cd, fec_addr);

		dev_err(&pci_dev->dev, "* 0x%08x 0x%016llx\n", fec_addr, fec);
		अगर (fec == IO_ILLEGAL_VALUE)
			जाओ fatal_error;

		क्रम (j = 0, mask = 1ULL; j < 64; j++, mask <<= 1) अणु

			/* secondary fir empty, skip it */
			अगर ((fir & mask) == 0x0)
				जारी;

			sfir_addr = (uid << 24) + 0x100 + 0x08 * j;
			sfir = __genwqe_पढ़ोq(cd, sfir_addr);

			अगर (sfir == IO_ILLEGAL_VALUE)
				जाओ fatal_error;
			dev_err(&pci_dev->dev,
				"* 0x%08x 0x%016llx\n", sfir_addr, sfir);

			sfec_addr = (uid << 24) + 0x300 + 0x08 * j;
			sfec = __genwqe_पढ़ोq(cd, sfec_addr);

			अगर (sfec == IO_ILLEGAL_VALUE)
				जाओ fatal_error;
			dev_err(&pci_dev->dev,
				"* 0x%08x 0x%016llx\n", sfec_addr, sfec);

			gfir = __genwqe_पढ़ोq(cd, IO_SLC_CFGREG_GFIR);
			अगर (gfir == IO_ILLEGAL_VALUE)
				जाओ fatal_error;

			/* gfir turned on during routine! get out and
			   start over. */
			अगर ((gfir_masked == 0x0) &&
			    (gfir & GFIR_ERR_TRIGGER)) अणु
				जाओ healthMonitor;
			पूर्ण

			/* करो not clear अगर we entered with a fatal gfir */
			अगर (gfir_masked == 0x0) अणु

				/* NEW clear by mask the logged bits */
				sfir_addr = (uid << 24) + 0x100 + 0x08 * j;
				__genwqe_ग_लिखोq(cd, sfir_addr, sfir);

				dev_dbg(&pci_dev->dev,
					"[HM] Clearing  2ndary FIR 0x%08x with 0x%016llx\n",
					sfir_addr, sfir);

				/*
				 * note, these cannot be error-Firs
				 * since gfir_masked is 0 after sfir
				 * was पढ़ो. Also, it is safe to करो
				 * this ग_लिखो अगर sfir=0. Still need to
				 * clear the primary. This just means
				 * there is no secondary FIR.
				 */

				/* clear by mask the logged bit. */
				fir_clr_addr = (uid << 24) + 0x10;
				__genwqe_ग_लिखोq(cd, fir_clr_addr, mask);

				dev_dbg(&pci_dev->dev,
					"[HM] Clearing primary FIR 0x%08x with 0x%016llx\n",
					fir_clr_addr, mask);
			पूर्ण
		पूर्ण
	पूर्ण
	gfir = __genwqe_पढ़ोq(cd, IO_SLC_CFGREG_GFIR);
	अगर (gfir == IO_ILLEGAL_VALUE)
		जाओ fatal_error;

	अगर ((gfir_masked == 0x0) && (gfir & GFIR_ERR_TRIGGER)) अणु
		/*
		 * Check once more that it didn't go on after all the
		 * FIRS were cleared.
		 */
		dev_dbg(&pci_dev->dev, "ACK! Another FIR! Recursing %d!\n",
			iterations);
		जाओ healthMonitor;
	पूर्ण
	वापस gfir_masked;

 fatal_error:
	वापस IO_ILLEGAL_VALUE;
पूर्ण

/**
 * genwqe_pci_fundamental_reset() - trigger a PCIe fundamental reset on the slot
 * @pci_dev:	PCI device inक्रमmation काष्ठा
 *
 * Note: pci_set_pcie_reset_state() is not implemented on all archs, so this
 * reset method will not work in all हालs.
 *
 * Return: 0 on success or error code from pci_set_pcie_reset_state()
 */
अटल पूर्णांक genwqe_pci_fundamental_reset(काष्ठा pci_dev *pci_dev)
अणु
	पूर्णांक rc;

	/*
	 * lock pci config space access from userspace,
	 * save state and issue PCIe fundamental reset
	 */
	pci_cfg_access_lock(pci_dev);
	pci_save_state(pci_dev);
	rc = pci_set_pcie_reset_state(pci_dev, pcie_warm_reset);
	अगर (!rc) अणु
		/* keep PCIe reset निश्चितed क्रम 250ms */
		msleep(250);
		pci_set_pcie_reset_state(pci_dev, pcie_deनिश्चित_reset);
		/* Wait क्रम 2s to reload flash and train the link */
		msleep(2000);
	पूर्ण
	pci_restore_state(pci_dev);
	pci_cfg_access_unlock(pci_dev);
	वापस rc;
पूर्ण


अटल पूर्णांक genwqe_platक्रमm_recovery(काष्ठा genwqe_dev *cd)
अणु
	काष्ठा pci_dev *pci_dev = cd->pci_dev;
	पूर्णांक rc;

	dev_info(&pci_dev->dev,
		 "[%s] resetting card for error recovery\n", __func__);

	/* Clear out error injection flags */
	cd->err_inject &= ~(GENWQE_INJECT_HARDWARE_FAILURE |
			    GENWQE_INJECT_GFIR_FATAL |
			    GENWQE_INJECT_GFIR_INFO);

	genwqe_stop(cd);

	/* Try recoverying the card with fundamental reset */
	rc = genwqe_pci_fundamental_reset(pci_dev);
	अगर (!rc) अणु
		rc = genwqe_start(cd);
		अगर (!rc)
			dev_info(&pci_dev->dev,
				 "[%s] card recovered\n", __func__);
		अन्यथा
			dev_err(&pci_dev->dev,
				"[%s] err: cannot start card services! (err=%d)\n",
				__func__, rc);
	पूर्ण अन्यथा अणु
		dev_err(&pci_dev->dev,
			"[%s] card reset failed\n", __func__);
	पूर्ण

	वापस rc;
पूर्ण

/**
 * genwqe_reload_bistream() - reload card bitstream
 * @cd: GenWQE device inक्रमmation
 *
 * Set the appropriate रेजिस्टर and call fundamental reset to reaload the card
 * bitstream.
 *
 * Return: 0 on success, error code otherwise
 */
अटल पूर्णांक genwqe_reload_bistream(काष्ठा genwqe_dev *cd)
अणु
	काष्ठा pci_dev *pci_dev = cd->pci_dev;
	पूर्णांक rc;

	dev_info(&pci_dev->dev,
		 "[%s] resetting card for bitstream reload\n",
		 __func__);

	genwqe_stop(cd);

	/*
	 * Cause a CPLD reprogram with the 'next_bitstream'
	 * partition on PCIe hot or fundamental reset
	 */
	__genwqe_ग_लिखोq(cd, IO_SLC_CFGREG_SOFTRESET,
			(cd->softreset & 0xcull) | 0x70ull);

	rc = genwqe_pci_fundamental_reset(pci_dev);
	अगर (rc) अणु
		/*
		 * A fundamental reset failure can be caused
		 * by lack of support on the arch, so we just
		 * log the error and try to start the card
		 * again.
		 */
		dev_err(&pci_dev->dev,
			"[%s] err: failed to reset card for bitstream reload\n",
			__func__);
	पूर्ण

	rc = genwqe_start(cd);
	अगर (rc) अणु
		dev_err(&pci_dev->dev,
			"[%s] err: cannot start card services! (err=%d)\n",
			__func__, rc);
		वापस rc;
	पूर्ण
	dev_info(&pci_dev->dev,
		 "[%s] card reloaded\n", __func__);
	वापस 0;
पूर्ण


/**
 * genwqe_health_thपढ़ो() - Health checking thपढ़ो
 * @data: GenWQE device inक्रमmation
 *
 * This thपढ़ो is only started क्रम the PF of the card.
 *
 * This thपढ़ो monitors the health of the card. A critical situation
 * is when we पढ़ो रेजिस्टरs which contain -1 (IO_ILLEGAL_VALUE). In
 * this हाल we need to be recovered from outside. Writing to
 * रेजिस्टरs will very likely not work either.
 *
 * This thपढ़ो must only निकास अगर kthपढ़ो_should_stop() becomes true.
 *
 * Condition क्रम the health-thपढ़ो to trigger:
 *   a) when a kthपढ़ो_stop() request comes in or
 *   b) a critical GFIR occured
 *
 * Inक्रमmational GFIRs are checked and potentially prपूर्णांकed in
 * GENWQE_HEALTH_CHECK_INTERVAL seconds.
 */
अटल पूर्णांक genwqe_health_thपढ़ो(व्योम *data)
अणु
	पूर्णांक rc, should_stop = 0;
	काष्ठा genwqe_dev *cd = data;
	काष्ठा pci_dev *pci_dev = cd->pci_dev;
	u64 gfir, gfir_masked, slu_unitcfg, app_unitcfg;

 health_thपढ़ो_begin:
	जबतक (!kthपढ़ो_should_stop()) अणु
		rc = रुको_event_पूर्णांकerruptible_समयout(cd->health_रुकोq,
			 (genwqe_health_check_cond(cd, &gfir) ||
			  (should_stop = kthपढ़ो_should_stop())),
				GENWQE_HEALTH_CHECK_INTERVAL * HZ);

		अगर (should_stop)
			अवरोध;

		अगर (gfir == IO_ILLEGAL_VALUE) अणु
			dev_err(&pci_dev->dev,
				"[%s] GFIR=%016llx\n", __func__, gfir);
			जाओ fatal_error;
		पूर्ण

		slu_unitcfg = __genwqe_पढ़ोq(cd, IO_SLU_UNITCFG);
		अगर (slu_unitcfg == IO_ILLEGAL_VALUE) अणु
			dev_err(&pci_dev->dev,
				"[%s] SLU_UNITCFG=%016llx\n",
				__func__, slu_unitcfg);
			जाओ fatal_error;
		पूर्ण

		app_unitcfg = __genwqe_पढ़ोq(cd, IO_APP_UNITCFG);
		अगर (app_unitcfg == IO_ILLEGAL_VALUE) अणु
			dev_err(&pci_dev->dev,
				"[%s] APP_UNITCFG=%016llx\n",
				__func__, app_unitcfg);
			जाओ fatal_error;
		पूर्ण

		gfir = __genwqe_पढ़ोq(cd, IO_SLC_CFGREG_GFIR);
		अगर (gfir == IO_ILLEGAL_VALUE) अणु
			dev_err(&pci_dev->dev,
				"[%s] %s: GFIR=%016llx\n", __func__,
				(gfir & GFIR_ERR_TRIGGER) ? "err" : "info",
				gfir);
			जाओ fatal_error;
		पूर्ण

		gfir_masked = genwqe_fir_checking(cd);
		अगर (gfir_masked == IO_ILLEGAL_VALUE)
			जाओ fatal_error;

		/*
		 * GFIR ErrorTrigger bits set => reset the card!
		 * Never करो this क्रम old/manufacturing images!
		 */
		अगर ((gfir_masked) && !cd->skip_recovery &&
		    genwqe_recovery_on_fatal_gfir_required(cd)) अणु

			cd->card_state = GENWQE_CARD_FATAL_ERROR;

			rc = genwqe_recover_card(cd, 0);
			अगर (rc < 0) अणु
				/* FIXME Card is unusable and needs unbind! */
				जाओ fatal_error;
			पूर्ण
		पूर्ण

		अगर (cd->card_state == GENWQE_CARD_RELOAD_BITSTREAM) अणु
			/* Userspace requested card bitstream reload */
			rc = genwqe_reload_bistream(cd);
			अगर (rc)
				जाओ fatal_error;
		पूर्ण

		cd->last_gfir = gfir;
		cond_resched();
	पूर्ण

	वापस 0;

 fatal_error:
	अगर (cd->use_platक्रमm_recovery) अणु
		/*
		 * Since we use raw accessors, EEH errors won't be detected
		 * by the platक्रमm until we करो a non-raw MMIO or config space
		 * पढ़ो
		 */
		पढ़ोq(cd->mmio + IO_SLC_CFGREG_GFIR);

		/* We करो nothing अगर the card is going over PCI recovery */
		अगर (pci_channel_offline(pci_dev))
			वापस -EIO;

		/*
		 * If it's supported by the platक्रमm, we try a fundamental reset
		 * to recover from a fatal error. Otherwise, we जारी to रुको
		 * क्रम an बाह्यal recovery procedure to take care of it.
		 */
		rc = genwqe_platक्रमm_recovery(cd);
		अगर (!rc)
			जाओ health_thपढ़ो_begin;
	पूर्ण

	dev_err(&pci_dev->dev,
		"[%s] card unusable. Please trigger unbind!\n", __func__);

	/* Bring करोwn logical devices to inक्रमm user space via udev हटाओ. */
	cd->card_state = GENWQE_CARD_FATAL_ERROR;
	genwqe_stop(cd);

	/* genwqe_bus_reset failed(). Now रुको क्रम genwqe_हटाओ(). */
	जबतक (!kthपढ़ो_should_stop())
		cond_resched();

	वापस -EIO;
पूर्ण

अटल पूर्णांक genwqe_health_check_start(काष्ठा genwqe_dev *cd)
अणु
	पूर्णांक rc;

	अगर (GENWQE_HEALTH_CHECK_INTERVAL <= 0)
		वापस 0;	/* valid क्रम disabling the service */

	/* moved beक्रमe request_irq() */
	/* init_रुकोqueue_head(&cd->health_रुकोq); */

	cd->health_thपढ़ो = kthपढ़ो_run(genwqe_health_thपढ़ो, cd,
					GENWQE_DEVNAME "%d_health",
					cd->card_idx);
	अगर (IS_ERR(cd->health_thपढ़ो)) अणु
		rc = PTR_ERR(cd->health_thपढ़ो);
		cd->health_thपढ़ो = शून्य;
		वापस rc;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक genwqe_health_thपढ़ो_running(काष्ठा genwqe_dev *cd)
अणु
	वापस cd->health_thपढ़ो != शून्य;
पूर्ण

अटल पूर्णांक genwqe_health_check_stop(काष्ठा genwqe_dev *cd)
अणु
	अगर (!genwqe_health_thपढ़ो_running(cd))
		वापस -EIO;

	kthपढ़ो_stop(cd->health_thपढ़ो);
	cd->health_thपढ़ो = शून्य;
	वापस 0;
पूर्ण

/**
 * genwqe_pci_setup() - Allocate PCIe related resources क्रम our card
 * @cd: GenWQE device inक्रमmation
 */
अटल पूर्णांक genwqe_pci_setup(काष्ठा genwqe_dev *cd)
अणु
	पूर्णांक err;
	काष्ठा pci_dev *pci_dev = cd->pci_dev;

	err = pci_enable_device_mem(pci_dev);
	अगर (err) अणु
		dev_err(&pci_dev->dev,
			"err: failed to enable pci memory (err=%d)\n", err);
		जाओ err_out;
	पूर्ण

	/* Reserve PCI I/O and memory resources */
	err = pci_request_mem_regions(pci_dev, genwqe_driver_name);
	अगर (err) अणु
		dev_err(&pci_dev->dev,
			"[%s] err: request bars failed (%d)\n", __func__, err);
		err = -EIO;
		जाओ err_disable_device;
	पूर्ण

	/* check क्रम 64-bit DMA address supported (DAC) */
	/* check क्रम 32-bit DMA address supported (SAC) */
	अगर (dma_set_mask_and_coherent(&pci_dev->dev, DMA_BIT_MASK(64)) ||
	    dma_set_mask_and_coherent(&pci_dev->dev, DMA_BIT_MASK(32))) अणु
		dev_err(&pci_dev->dev,
			"err: neither DMA32 nor DMA64 supported\n");
		err = -EIO;
		जाओ out_release_resources;
	पूर्ण

	pci_set_master(pci_dev);
	pci_enable_pcie_error_reporting(pci_dev);

	/* EEH recovery requires PCIe fundamental reset */
	pci_dev->needs_freset = 1;

	/* request complete BAR-0 space (length = 0) */
	cd->mmio_len = pci_resource_len(pci_dev, 0);
	cd->mmio = pci_iomap(pci_dev, 0, 0);
	अगर (cd->mmio == शून्य) अणु
		dev_err(&pci_dev->dev,
			"[%s] err: mapping BAR0 failed\n", __func__);
		err = -ENOMEM;
		जाओ out_release_resources;
	पूर्ण

	cd->num_vfs = pci_sriov_get_totalvfs(pci_dev);
	अगर (cd->num_vfs < 0)
		cd->num_vfs = 0;

	err = genwqe_पढ़ो_ids(cd);
	अगर (err)
		जाओ out_iounmap;

	वापस 0;

 out_iounmap:
	pci_iounmap(pci_dev, cd->mmio);
 out_release_resources:
	pci_release_mem_regions(pci_dev);
 err_disable_device:
	pci_disable_device(pci_dev);
 err_out:
	वापस err;
पूर्ण

/**
 * genwqe_pci_हटाओ() - Free PCIe related resources क्रम our card
 * @cd: GenWQE device inक्रमmation
 */
अटल व्योम genwqe_pci_हटाओ(काष्ठा genwqe_dev *cd)
अणु
	काष्ठा pci_dev *pci_dev = cd->pci_dev;

	अगर (cd->mmio)
		pci_iounmap(pci_dev, cd->mmio);

	pci_release_mem_regions(pci_dev);
	pci_disable_device(pci_dev);
पूर्ण

/**
 * genwqe_probe() - Device initialization
 * @pci_dev:	PCI device inक्रमmation काष्ठा
 * @id:		PCI device ID
 *
 * Callable क्रम multiple cards. This function is called on bind.
 *
 * Return: 0 अगर succeeded, < 0 when failed
 */
अटल पूर्णांक genwqe_probe(काष्ठा pci_dev *pci_dev,
			स्थिर काष्ठा pci_device_id *id)
अणु
	पूर्णांक err;
	काष्ठा genwqe_dev *cd;

	genwqe_init_crc32();

	cd = genwqe_dev_alloc();
	अगर (IS_ERR(cd)) अणु
		dev_err(&pci_dev->dev, "err: could not alloc mem (err=%d)!\n",
			(पूर्णांक)PTR_ERR(cd));
		वापस PTR_ERR(cd);
	पूर्ण

	dev_set_drvdata(&pci_dev->dev, cd);
	cd->pci_dev = pci_dev;

	err = genwqe_pci_setup(cd);
	अगर (err < 0) अणु
		dev_err(&pci_dev->dev,
			"err: problems with PCI setup (err=%d)\n", err);
		जाओ out_मुक्त_dev;
	पूर्ण

	err = genwqe_start(cd);
	अगर (err < 0) अणु
		dev_err(&pci_dev->dev,
			"err: cannot start card services! (err=%d)\n", err);
		जाओ out_pci_हटाओ;
	पूर्ण

	अगर (genwqe_is_privileged(cd)) अणु
		err = genwqe_health_check_start(cd);
		अगर (err < 0) अणु
			dev_err(&pci_dev->dev,
				"err: cannot start health checking! (err=%d)\n",
				err);
			जाओ out_stop_services;
		पूर्ण
	पूर्ण
	वापस 0;

 out_stop_services:
	genwqe_stop(cd);
 out_pci_हटाओ:
	genwqe_pci_हटाओ(cd);
 out_मुक्त_dev:
	genwqe_dev_मुक्त(cd);
	वापस err;
पूर्ण

/**
 * genwqe_हटाओ() - Called when device is हटाओd (hot-plugable)
 * @pci_dev:	PCI device inक्रमmation काष्ठा
 *
 * Or when driver is unloaded respecitively when unbind is करोne.
 */
अटल व्योम genwqe_हटाओ(काष्ठा pci_dev *pci_dev)
अणु
	काष्ठा genwqe_dev *cd = dev_get_drvdata(&pci_dev->dev);

	genwqe_health_check_stop(cd);

	/*
	 * genwqe_stop() must survive अगर it is called twice
	 * sequentially. This happens when the health thपढ़ो calls it
	 * and fails on genwqe_bus_reset().
	 */
	genwqe_stop(cd);
	genwqe_pci_हटाओ(cd);
	genwqe_dev_मुक्त(cd);
पूर्ण

/**
 * genwqe_err_error_detected() - Error detection callback
 * @pci_dev:	PCI device inक्रमmation काष्ठा
 * @state:	PCI channel state
 *
 * This callback is called by the PCI subप्रणाली whenever a PCI bus
 * error is detected.
 */
अटल pci_ers_result_t genwqe_err_error_detected(काष्ठा pci_dev *pci_dev,
						 pci_channel_state_t state)
अणु
	काष्ठा genwqe_dev *cd;

	dev_err(&pci_dev->dev, "[%s] state=%d\n", __func__, state);

	cd = dev_get_drvdata(&pci_dev->dev);
	अगर (cd == शून्य)
		वापस PCI_ERS_RESULT_DISCONNECT;

	/* Stop the card */
	genwqe_health_check_stop(cd);
	genwqe_stop(cd);

	/*
	 * On permanent failure, the PCI code will call device हटाओ
	 * after the वापस of this function.
	 * genwqe_stop() can be called twice.
	 */
	अगर (state == pci_channel_io_perm_failure) अणु
		वापस PCI_ERS_RESULT_DISCONNECT;
	पूर्ण अन्यथा अणु
		genwqe_pci_हटाओ(cd);
		वापस PCI_ERS_RESULT_NEED_RESET;
	पूर्ण
पूर्ण

अटल pci_ers_result_t genwqe_err_slot_reset(काष्ठा pci_dev *pci_dev)
अणु
	पूर्णांक rc;
	काष्ठा genwqe_dev *cd = dev_get_drvdata(&pci_dev->dev);

	rc = genwqe_pci_setup(cd);
	अगर (!rc) अणु
		वापस PCI_ERS_RESULT_RECOVERED;
	पूर्ण अन्यथा अणु
		dev_err(&pci_dev->dev,
			"err: problems with PCI setup (err=%d)\n", rc);
		वापस PCI_ERS_RESULT_DISCONNECT;
	पूर्ण
पूर्ण

अटल pci_ers_result_t genwqe_err_result_none(काष्ठा pci_dev *dev)
अणु
	वापस PCI_ERS_RESULT_NONE;
पूर्ण

अटल व्योम genwqe_err_resume(काष्ठा pci_dev *pci_dev)
अणु
	पूर्णांक rc;
	काष्ठा genwqe_dev *cd = dev_get_drvdata(&pci_dev->dev);

	rc = genwqe_start(cd);
	अगर (!rc) अणु
		rc = genwqe_health_check_start(cd);
		अगर (rc)
			dev_err(&pci_dev->dev,
				"err: cannot start health checking! (err=%d)\n",
				rc);
	पूर्ण अन्यथा अणु
		dev_err(&pci_dev->dev,
			"err: cannot start card services! (err=%d)\n", rc);
	पूर्ण
पूर्ण

अटल पूर्णांक genwqe_sriov_configure(काष्ठा pci_dev *dev, पूर्णांक numvfs)
अणु
	पूर्णांक rc;
	काष्ठा genwqe_dev *cd = dev_get_drvdata(&dev->dev);

	अगर (numvfs > 0) अणु
		genwqe_setup_vf_jसमयr(cd);
		rc = pci_enable_sriov(dev, numvfs);
		अगर (rc < 0)
			वापस rc;
		वापस numvfs;
	पूर्ण
	अगर (numvfs == 0) अणु
		pci_disable_sriov(dev);
		वापस 0;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pci_error_handlers genwqe_err_handler = अणु
	.error_detected = genwqe_err_error_detected,
	.mmio_enabled	= genwqe_err_result_none,
	.slot_reset	= genwqe_err_slot_reset,
	.resume		= genwqe_err_resume,
पूर्ण;

अटल काष्ठा pci_driver genwqe_driver = अणु
	.name	  = genwqe_driver_name,
	.id_table = genwqe_device_table,
	.probe	  = genwqe_probe,
	.हटाओ	  = genwqe_हटाओ,
	.sriov_configure = genwqe_sriov_configure,
	.err_handler = &genwqe_err_handler,
पूर्ण;

/**
 * genwqe_devnode() - Set शेष access mode क्रम genwqe devices.
 * @dev:	Poपूर्णांकer to device (unused)
 * @mode:	Carrier to pass-back given mode (permissions)
 *
 * Default mode should be rw क्रम everybody. Do not change शेष
 * device name.
 */
अटल अक्षर *genwqe_devnode(काष्ठा device *dev, umode_t *mode)
अणु
	अगर (mode)
		*mode = 0666;
	वापस शून्य;
पूर्ण

/**
 * genwqe_init_module() - Driver registration and initialization
 */
अटल पूर्णांक __init genwqe_init_module(व्योम)
अणु
	पूर्णांक rc;

	class_genwqe = class_create(THIS_MODULE, GENWQE_DEVNAME);
	अगर (IS_ERR(class_genwqe)) अणु
		pr_err("[%s] create class failed\n", __func__);
		वापस -ENOMEM;
	पूर्ण

	class_genwqe->devnode = genwqe_devnode;

	debugfs_genwqe = debugfs_create_dir(GENWQE_DEVNAME, शून्य);

	rc = pci_रेजिस्टर_driver(&genwqe_driver);
	अगर (rc != 0) अणु
		pr_err("[%s] pci_reg_driver (rc=%d)\n", __func__, rc);
		जाओ err_out0;
	पूर्ण

	वापस rc;

 err_out0:
	debugfs_हटाओ(debugfs_genwqe);
	class_destroy(class_genwqe);
	वापस rc;
पूर्ण

/**
 * genwqe_निकास_module() - Driver निकास
 */
अटल व्योम __निकास genwqe_निकास_module(व्योम)
अणु
	pci_unरेजिस्टर_driver(&genwqe_driver);
	debugfs_हटाओ(debugfs_genwqe);
	class_destroy(class_genwqe);
पूर्ण

module_init(genwqe_init_module);
module_निकास(genwqe_निकास_module);
