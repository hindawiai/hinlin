<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/libata.h>
#समावेश <linux/cdrom.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/module.h>
#समावेश <linux/pm_qos.h>
#समावेश <scsi/scsi_device.h>

#समावेश "libata.h"

अटल पूर्णांक zpodd_घातeroff_delay = 30; /* 30 seconds क्रम घातer off delay */
module_param(zpodd_घातeroff_delay, पूर्णांक, 0644);
MODULE_PARM_DESC(zpodd_घातeroff_delay, "Poweroff delay for ZPODD in seconds");

क्रमागत odd_mech_type अणु
	ODD_MECH_TYPE_SLOT,
	ODD_MECH_TYPE_DRAWER,
	ODD_MECH_TYPE_UNSUPPORTED,
पूर्ण;

काष्ठा zpodd अणु
	क्रमागत odd_mech_type	mech_type; /* init during probe, RO afterwards */
	काष्ठा ata_device	*dev;

	/* The following fields are synchronized by PM core. */
	bool			from_notअगरy; /* resumed as a result of
					      * acpi wake notअगरication */
	bool			zp_पढ़ोy; /* ZP पढ़ोy state */
	अचिन्हित दीर्घ		last_पढ़ोy; /* last ZP पढ़ोy बारtamp */
	bool			zp_sampled; /* ZP पढ़ोy state sampled */
	bool			घातered_off; /* ODD is घातered off
					      *	during suspend */
पूर्ण;

अटल पूर्णांक eject_tray(काष्ठा ata_device *dev)
अणु
	काष्ठा ata_taskfile tf;
	अटल स्थिर अक्षर cdb[ATAPI_CDB_LEN] = अणु  GPCMD_START_STOP_UNIT,
		0, 0, 0,
		0x02,     /* LoEj */
		0, 0, 0, 0, 0, 0, 0,
	पूर्ण;

	ata_tf_init(dev, &tf);
	tf.flags = ATA_TFLAG_ISADDR | ATA_TFLAG_DEVICE;
	tf.command = ATA_CMD_PACKET;
	tf.protocol = ATAPI_PROT_NODATA;

	वापस ata_exec_पूर्णांकernal(dev, &tf, cdb, DMA_NONE, शून्य, 0, 0);
पूर्ण

/* Per the spec, only slot type and drawer type ODD can be supported */
अटल क्रमागत odd_mech_type zpodd_get_mech_type(काष्ठा ata_device *dev)
अणु
	अक्षर *buf;
	अचिन्हित पूर्णांक ret;
	काष्ठा rm_feature_desc *desc;
	काष्ठा ata_taskfile tf;
	अटल स्थिर अक्षर cdb[ATAPI_CDB_LEN] = अणु  GPCMD_GET_CONFIGURATION,
			2,      /* only 1 feature descriptor requested */
			0, 3,   /* 3, removable medium feature */
			0, 0, 0,/* reserved */
			0, 16,
			0, 0, 0,
	पूर्ण;

	buf = kzalloc(16, GFP_KERNEL);
	अगर (!buf)
		वापस ODD_MECH_TYPE_UNSUPPORTED;
	desc = (व्योम *)(buf + 8);

	ata_tf_init(dev, &tf);
	tf.flags = ATA_TFLAG_ISADDR | ATA_TFLAG_DEVICE;
	tf.command = ATA_CMD_PACKET;
	tf.protocol = ATAPI_PROT_PIO;
	tf.lbam = 16;

	ret = ata_exec_पूर्णांकernal(dev, &tf, cdb, DMA_FROM_DEVICE,
				buf, 16, 0);
	अगर (ret) अणु
		kमुक्त(buf);
		वापस ODD_MECH_TYPE_UNSUPPORTED;
	पूर्ण

	अगर (be16_to_cpu(desc->feature_code) != 3) अणु
		kमुक्त(buf);
		वापस ODD_MECH_TYPE_UNSUPPORTED;
	पूर्ण

	अगर (desc->mech_type == 0 && desc->load == 0 && desc->eject == 1) अणु
		kमुक्त(buf);
		वापस ODD_MECH_TYPE_SLOT;
	पूर्ण अन्यथा अगर (desc->mech_type == 1 && desc->load == 0 &&
		   desc->eject == 1) अणु
		kमुक्त(buf);
		वापस ODD_MECH_TYPE_DRAWER;
	पूर्ण अन्यथा अणु
		kमुक्त(buf);
		वापस ODD_MECH_TYPE_UNSUPPORTED;
	पूर्ण
पूर्ण

/* Test अगर ODD is zero घातer पढ़ोy by sense code */
अटल bool zpपढ़ोy(काष्ठा ata_device *dev)
अणु
	u8 sense_key, *sense_buf;
	अचिन्हित पूर्णांक ret, asc, ascq, add_len;
	काष्ठा zpodd *zpodd = dev->zpodd;

	ret = atapi_eh_tur(dev, &sense_key);

	अगर (!ret || sense_key != NOT_READY)
		वापस false;

	sense_buf = dev->link->ap->sector_buf;
	ret = atapi_eh_request_sense(dev, sense_buf, sense_key);
	अगर (ret)
		वापस false;

	/* sense valid */
	अगर ((sense_buf[0] & 0x7f) != 0x70)
		वापस false;

	add_len = sense_buf[7];
	/* has asc and ascq */
	अगर (add_len < 6)
		वापस false;

	asc = sense_buf[12];
	ascq = sense_buf[13];

	अगर (zpodd->mech_type == ODD_MECH_TYPE_SLOT)
		/* no media inside */
		वापस asc == 0x3a;
	अन्यथा
		/* no media inside and करोor बंदd */
		वापस asc == 0x3a && ascq == 0x01;
पूर्ण

/*
 * Update the zpodd->zp_पढ़ोy field. This field will only be set
 * अगर the ODD has stayed in ZP पढ़ोy state क्रम zpodd_घातeroff_delay
 * समय, and will be used to decide अगर घातer off is allowed. If it
 * is set, it will be cleared during resume from घातered off state.
 */
व्योम zpodd_on_suspend(काष्ठा ata_device *dev)
अणु
	काष्ठा zpodd *zpodd = dev->zpodd;
	अचिन्हित दीर्घ expires;

	अगर (!zpपढ़ोy(dev)) अणु
		zpodd->zp_sampled = false;
		zpodd->zp_पढ़ोy = false;
		वापस;
	पूर्ण

	अगर (!zpodd->zp_sampled) अणु
		zpodd->zp_sampled = true;
		zpodd->last_पढ़ोy = jअगरfies;
		वापस;
	पूर्ण

	expires = zpodd->last_पढ़ोy +
		  msecs_to_jअगरfies(zpodd_घातeroff_delay * 1000);
	अगर (समय_beक्रमe(jअगरfies, expires))
		वापस;

	zpodd->zp_पढ़ोy = true;
पूर्ण

bool zpodd_zpपढ़ोy(काष्ठा ata_device *dev)
अणु
	काष्ठा zpodd *zpodd = dev->zpodd;
	वापस zpodd->zp_पढ़ोy;
पूर्ण

/*
 * Enable runसमय wake capability through ACPI and set the घातered_off flag,
 * this flag will be used during resume to decide what operations are needed
 * to take.
 *
 * Also, media poll needs to be silenced, so that it करोesn't bring the ODD
 * back to full घातer state every few seconds.
 */
व्योम zpodd_enable_run_wake(काष्ठा ata_device *dev)
अणु
	काष्ठा zpodd *zpodd = dev->zpodd;

	sdev_disable_disk_events(dev->sdev);

	zpodd->घातered_off = true;
	acpi_pm_set_device_wakeup(&dev->tdev, true);
पूर्ण

/* Disable runसमय wake capability अगर it is enabled */
व्योम zpodd_disable_run_wake(काष्ठा ata_device *dev)
अणु
	काष्ठा zpodd *zpodd = dev->zpodd;

	अगर (zpodd->घातered_off)
		acpi_pm_set_device_wakeup(&dev->tdev, false);
पूर्ण

/*
 * Post घातer on processing after the ODD has been recovered. If the
 * ODD wasn't powered off during suspend, it doesn't करो anything.
 *
 * For drawer type ODD, अगर it is घातered on due to user pressed the
 * eject button, the tray needs to be ejected. This can only be करोne
 * after the ODD has been recovered, i.e. link is initialized and
 * device is able to process NON_DATA PIO command, as eject needs to
 * send command क्रम the ODD to process.
 *
 * The from_notअगरy flag set in wake notअगरication handler function
 * zpodd_wake_dev represents अगर घातer on is due to user's action.
 *
 * For both types of ODD, several fields need to be reset.
 */
व्योम zpodd_post_घातeron(काष्ठा ata_device *dev)
अणु
	काष्ठा zpodd *zpodd = dev->zpodd;

	अगर (!zpodd->घातered_off)
		वापस;

	zpodd->घातered_off = false;

	अगर (zpodd->from_notअगरy) अणु
		zpodd->from_notअगरy = false;
		अगर (zpodd->mech_type == ODD_MECH_TYPE_DRAWER)
			eject_tray(dev);
	पूर्ण

	zpodd->zp_sampled = false;
	zpodd->zp_पढ़ोy = false;

	sdev_enable_disk_events(dev->sdev);
पूर्ण

अटल व्योम zpodd_wake_dev(acpi_handle handle, u32 event, व्योम *context)
अणु
	काष्ठा ata_device *ata_dev = context;
	काष्ठा zpodd *zpodd = ata_dev->zpodd;
	काष्ठा device *dev = &ata_dev->sdev->sdev_gendev;

	अगर (event == ACPI_NOTIFY_DEVICE_WAKE && pm_runसमय_suspended(dev)) अणु
		zpodd->from_notअगरy = true;
		pm_runसमय_resume(dev);
	पूर्ण
पूर्ण

अटल व्योम ata_acpi_add_pm_notअगरier(काष्ठा ata_device *dev)
अणु
	acpi_handle handle = ata_dev_acpi_handle(dev);
	acpi_install_notअगरy_handler(handle, ACPI_SYSTEM_NOTIFY,
				    zpodd_wake_dev, dev);
पूर्ण

अटल व्योम ata_acpi_हटाओ_pm_notअगरier(काष्ठा ata_device *dev)
अणु
	acpi_handle handle = ata_dev_acpi_handle(dev);
	acpi_हटाओ_notअगरy_handler(handle, ACPI_SYSTEM_NOTIFY, zpodd_wake_dev);
पूर्ण

व्योम zpodd_init(काष्ठा ata_device *dev)
अणु
	काष्ठा acpi_device *adev = ACPI_COMPANION(&dev->tdev);
	क्रमागत odd_mech_type mech_type;
	काष्ठा zpodd *zpodd;

	अगर (dev->zpodd || !adev || !acpi_device_can_घातeroff(adev))
		वापस;

	mech_type = zpodd_get_mech_type(dev);
	अगर (mech_type == ODD_MECH_TYPE_UNSUPPORTED)
		वापस;

	zpodd = kzalloc(माप(काष्ठा zpodd), GFP_KERNEL);
	अगर (!zpodd)
		वापस;

	zpodd->mech_type = mech_type;

	ata_acpi_add_pm_notअगरier(dev);
	zpodd->dev = dev;
	dev->zpodd = zpodd;
	dev_pm_qos_expose_flags(&dev->tdev, 0);
पूर्ण

व्योम zpodd_निकास(काष्ठा ata_device *dev)
अणु
	ata_acpi_हटाओ_pm_notअगरier(dev);
	kमुक्त(dev->zpodd);
	dev->zpodd = शून्य;
पूर्ण
