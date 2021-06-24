<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Driver क्रम USB Mass Storage compliant devices
 * SCSI layer glue code
 *
 * Current development and मुख्यtenance by:
 *   (c) 1999-2002 Matthew Dharm (mdharm-usb@one-eyed-alien.net)
 *
 * Developed with the assistance of:
 *   (c) 2000 David L. Brown, Jr. (usb-storage@davidb.org)
 *   (c) 2000 Stephen J. Gowdy (SGowdy@lbl.gov)
 *
 * Initial work by:
 *   (c) 1999 Michael Gee (michael@linuxspecअगरic.com)
 *
 * This driver is based on the 'USB Mass Storage Class' करोcument. This
 * describes in detail the protocol used to communicate with such
 * devices.  Clearly, the designers had SCSI and ATAPI commands in
 * mind when they created this करोcument.  The commands are all very
 * similar to commands in the SCSI-II and ATAPI specअगरications.
 *
 * It is important to note that in a number of हालs this class
 * exhibits class-specअगरic exemptions from the USB specअगरication.
 * Notably the usage of NAK, STALL and ACK dअगरfers from the norm, in
 * that they are used to communicate रुको, failed and OK on commands.
 *
 * Also, क्रम certain devices, the पूर्णांकerrupt endpoपूर्णांक is used to convey
 * status of a command.
 */

#समावेश <linux/blkdev.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_devinfo.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_eh.h>

#समावेश "usb.h"
#समावेश <linux/usb/hcd.h>
#समावेश "scsiglue.h"
#समावेश "debug.h"
#समावेश "transport.h"
#समावेश "protocol.h"

/*
 * Venकरोr IDs क्रम companies that seem to include the READ CAPACITY bug
 * in all their devices
 */
#घोषणा VENDOR_ID_NOKIA		0x0421
#घोषणा VENDOR_ID_NIKON		0x04b0
#घोषणा VENDOR_ID_PENTAX	0x0a17
#घोषणा VENDOR_ID_MOTOROLA	0x22b8

/***********************************************************************
 * Host functions 
 ***********************************************************************/

अटल स्थिर अक्षर* host_info(काष्ठा Scsi_Host *host)
अणु
	काष्ठा us_data *us = host_to_us(host);
	वापस us->scsi_name;
पूर्ण

अटल पूर्णांक slave_alloc (काष्ठा scsi_device *sdev)
अणु
	काष्ठा us_data *us = host_to_us(sdev->host);

	/*
	 * Set the INQUIRY transfer length to 36.  We करोn't use any of
	 * the extra data and many devices choke अगर asked क्रम more or
	 * less than 36 bytes.
	 */
	sdev->inquiry_len = 36;

	/*
	 * Some host controllers may have alignment requirements.
	 * We'll play it safe by requiring 512-byte alignment always.
	 */
	blk_queue_update_dma_alignment(sdev->request_queue, (512 - 1));

	/* Tell the SCSI layer अगर we know there is more than one LUN */
	अगर (us->protocol == USB_PR_BULK && us->max_lun > 0)
		sdev->sdev_bflags |= BLIST_FORCELUN;

	वापस 0;
पूर्ण

अटल पूर्णांक slave_configure(काष्ठा scsi_device *sdev)
अणु
	काष्ठा us_data *us = host_to_us(sdev->host);
	काष्ठा device *dev = us->pusb_dev->bus->sysdev;

	/*
	 * Many devices have trouble transferring more than 32KB at a समय,
	 * जबतक others have trouble with more than 64K. At this समय we
	 * are limiting both to 32K (64 sectores).
	 */
	अगर (us->fflags & (US_FL_MAX_SECTORS_64 | US_FL_MAX_SECTORS_MIN)) अणु
		अचिन्हित पूर्णांक max_sectors = 64;

		अगर (us->fflags & US_FL_MAX_SECTORS_MIN)
			max_sectors = PAGE_SIZE >> 9;
		अगर (queue_max_hw_sectors(sdev->request_queue) > max_sectors)
			blk_queue_max_hw_sectors(sdev->request_queue,
					      max_sectors);
	पूर्ण अन्यथा अगर (sdev->type == TYPE_TAPE) अणु
		/*
		 * Tapes need much higher max_sector limits, so just
		 * उठाओ it to the maximum possible (4 GB / 512) and
		 * let the queue segment size sort out the real limit.
		 */
		blk_queue_max_hw_sectors(sdev->request_queue, 0x7FFFFF);
	पूर्ण अन्यथा अगर (us->pusb_dev->speed >= USB_SPEED_SUPER) अणु
		/*
		 * USB3 devices will be limited to 2048 sectors. This gives us
		 * better throughput on most devices.
		 */
		blk_queue_max_hw_sectors(sdev->request_queue, 2048);
	पूर्ण

	/*
	 * The max_hw_sectors should be up to maximum size of a mapping क्रम
	 * the device. Otherwise, a DMA API might fail on swiotlb environment.
	 */
	blk_queue_max_hw_sectors(sdev->request_queue,
		min_t(माप_प्रकार, queue_max_hw_sectors(sdev->request_queue),
		      dma_max_mapping_size(dev) >> SECTOR_SHIFT));

	/*
	 * Some USB host controllers can't करो DMA; they have to use PIO.
	 * For such controllers we need to make sure the block layer sets
	 * up bounce buffers in addressable memory.
	 */
	अगर (!hcd_uses_dma(bus_to_hcd(us->pusb_dev->bus)) ||
			(bus_to_hcd(us->pusb_dev->bus)->localmem_pool != शून्य))
		blk_queue_bounce_limit(sdev->request_queue, BLK_BOUNCE_HIGH);

	/*
	 * We can't put these settings in slave_alloc() because that माला_लो
	 * called beक्रमe the device type is known.  Consequently these
	 * settings can't be overridden via the scsi devinfo mechanism.
	 */
	अगर (sdev->type == TYPE_DISK) अणु

		/*
		 * Some venकरोrs seem to put the READ CAPACITY bug पूर्णांकo
		 * all their devices -- primarily makers of cell phones
		 * and digital cameras.  Since these devices always use
		 * flash media and can be expected to have an even number
		 * of sectors, we will always enable the CAPACITY_HEURISTICS
		 * flag unless told otherwise.
		 */
		चयन (le16_to_cpu(us->pusb_dev->descriptor.idVenकरोr)) अणु
		हाल VENDOR_ID_NOKIA:
		हाल VENDOR_ID_NIKON:
		हाल VENDOR_ID_PENTAX:
		हाल VENDOR_ID_MOTOROLA:
			अगर (!(us->fflags & (US_FL_FIX_CAPACITY |
					US_FL_CAPACITY_OK)))
				us->fflags |= US_FL_CAPACITY_HEURISTICS;
			अवरोध;
		पूर्ण

		/*
		 * Disk-type devices use MODE SENSE(6) अगर the protocol
		 * (SubClass) is Transparent SCSI, otherwise they use
		 * MODE SENSE(10).
		 */
		अगर (us->subclass != USB_SC_SCSI && us->subclass != USB_SC_CYP_ATACB)
			sdev->use_10_क्रम_ms = 1;

		/*
		 *Many disks only accept MODE SENSE transfer lengths of
		 * 192 bytes (that's what Winकरोws uses).
		 */
		sdev->use_192_bytes_क्रम_3f = 1;

		/*
		 * Some devices करोn't like MODE SENSE with page=0x3f,
		 * which is the command used क्रम checking अगर a device
		 * is ग_लिखो-रक्षित.  Now that we tell the sd driver
		 * to करो a 192-byte transfer with this command the
		 * majority of devices work fine, but a few still can't
		 * handle it.  The sd driver will simply assume those
		 * devices are ग_लिखो-enabled.
		 */
		अगर (us->fflags & US_FL_NO_WP_DETECT)
			sdev->skip_ms_page_3f = 1;

		/*
		 * A number of devices have problems with MODE SENSE क्रम
		 * page x08, so we will skip it.
		 */
		sdev->skip_ms_page_8 = 1;

		/*
		 * Some devices करोn't handle VPD pages correctly, so skip vpd
		 * pages अगर not क्रमced by SCSI layer.
		 */
		sdev->skip_vpd_pages = !sdev->try_vpd_pages;

		/* Do not attempt to use REPORT SUPPORTED OPERATION CODES */
		sdev->no_report_opcodes = 1;

		/* Do not attempt to use WRITE SAME */
		sdev->no_ग_लिखो_same = 1;

		/*
		 * Some disks वापस the total number of blocks in response
		 * to READ CAPACITY rather than the highest block number.
		 * If this device makes that mistake, tell the sd driver.
		 */
		अगर (us->fflags & US_FL_FIX_CAPACITY)
			sdev->fix_capacity = 1;

		/*
		 * A few disks have two indistinguishable version, one of
		 * which reports the correct capacity and the other करोes not.
		 * The sd driver has to guess which is the हाल.
		 */
		अगर (us->fflags & US_FL_CAPACITY_HEURISTICS)
			sdev->guess_capacity = 1;

		/* Some devices cannot handle READ_CAPACITY_16 */
		अगर (us->fflags & US_FL_NO_READ_CAPACITY_16)
			sdev->no_पढ़ो_capacity_16 = 1;

		/*
		 * Many devices करो not respond properly to READ_CAPACITY_16.
		 * Tell the SCSI layer to try READ_CAPACITY_10 first.
		 * However some USB 3.0 drive enclosures वापस capacity
		 * modulo 2TB. Those must use READ_CAPACITY_16
		 */
		अगर (!(us->fflags & US_FL_NEEDS_CAP16))
			sdev->try_rc_10_first = 1;

		/*
		 * assume SPC3 or latter devices support sense size > 18
		 * unless US_FL_BAD_SENSE quirk is specअगरied.
		 */
		अगर (sdev->scsi_level > SCSI_SPC_2 &&
		    !(us->fflags & US_FL_BAD_SENSE))
			us->fflags |= US_FL_SANE_SENSE;

		/*
		 * USB-IDE bridges tend to report SK = 0x04 (Non-recoverable
		 * Hardware Error) when any low-level error occurs,
		 * recoverable or not.  Setting this flag tells the SCSI
		 * midlayer to retry such commands, which frequently will
		 * succeed and fix the error.  The worst this can lead to
		 * is an occasional series of retries that will all fail.
		 */
		sdev->retry_hwerror = 1;

		/*
		 * USB disks should allow restart.  Some drives spin करोwn
		 * स्वतःmatically, requiring a START-STOP UNIT command.
		 */
		sdev->allow_restart = 1;

		/*
		 * Some USB cardपढ़ोers have trouble पढ़ोing an sdcard's last
		 * sector in a larger then 1 sector पढ़ो, since the perक्रमmance
		 * impact is negligible we set this flag क्रम all USB disks
		 */
		sdev->last_sector_bug = 1;

		/*
		 * Enable last-sector hacks क्रम single-target devices using
		 * the Bulk-only transport, unless we alपढ़ोy know the
		 * capacity will be decremented or is correct.
		 */
		अगर (!(us->fflags & (US_FL_FIX_CAPACITY | US_FL_CAPACITY_OK |
					US_FL_SCM_MULT_TARG)) &&
				us->protocol == USB_PR_BULK)
			us->use_last_sector_hacks = 1;

		/* Check अगर ग_लिखो cache शेष on flag is set or not */
		अगर (us->fflags & US_FL_WRITE_CACHE)
			sdev->wce_शेष_on = 1;

		/* A few buggy USB-ATA bridges करोn't understand FUA */
		अगर (us->fflags & US_FL_BROKEN_FUA)
			sdev->broken_fua = 1;

		/* Some even totally fail to indicate a cache */
		अगर (us->fflags & US_FL_ALWAYS_SYNC) अणु
			/* करोn't पढ़ो caching inक्रमmation */
			sdev->skip_ms_page_8 = 1;
			sdev->skip_ms_page_3f = 1;
			/* assume sync is needed */
			sdev->wce_शेष_on = 1;
		पूर्ण
	पूर्ण अन्यथा अणु

		/*
		 * Non-disk-type devices करोn't need to ignore any pages
		 * or to क्रमce 192-byte transfer lengths क्रम MODE SENSE.
		 * But they करो need to use MODE SENSE(10).
		 */
		sdev->use_10_क्रम_ms = 1;

		/* Some (fake) usb cdrom devices करोn't like READ_DISC_INFO */
		अगर (us->fflags & US_FL_NO_READ_DISC_INFO)
			sdev->no_पढ़ो_disc_info = 1;
	पूर्ण

	/*
	 * The CB and CBI transports have no way to pass LUN values
	 * other than the bits in the second byte of a CDB.  But those
	 * bits करोn't get set to the LUN value अगर the device reports
	 * scsi_level == 0 (UNKNOWN).  Hence such devices must necessarily
	 * be single-LUN.
	 */
	अगर ((us->protocol == USB_PR_CB || us->protocol == USB_PR_CBI) &&
			sdev->scsi_level == SCSI_UNKNOWN)
		us->max_lun = 0;

	/*
	 * Some devices choke when they receive a PREVENT-ALLOW MEDIUM
	 * REMOVAL command, so suppress those commands.
	 */
	अगर (us->fflags & US_FL_NOT_LOCKABLE)
		sdev->lockable = 0;

	/*
	 * this is to satisfy the compiler, tho I करोn't think the 
	 * वापस code is ever checked anywhere.
	 */
	वापस 0;
पूर्ण

अटल पूर्णांक target_alloc(काष्ठा scsi_target *starget)
अणु
	काष्ठा us_data *us = host_to_us(dev_to_shost(starget->dev.parent));

	/*
	 * Some USB drives करोn't support REPORT LUNS, even though they
	 * report a SCSI revision level above 2.  Tell the SCSI layer
	 * not to issue that command; it will perक्रमm a normal sequential
	 * scan instead.
	 */
	starget->no_report_luns = 1;

	/*
	 * The UFI spec treats the Peripheral Qualअगरier bits in an
	 * INQUIRY result as reserved and requires devices to set them
	 * to 0.  However the SCSI spec requires these bits to be set
	 * to 3 to indicate when a LUN is not present.
	 *
	 * Let the scanning code know अगर this target merely sets
	 * Peripheral Device Type to 0x1f to indicate no LUN.
	 */
	अगर (us->subclass == USB_SC_UFI)
		starget->pdt_1f_क्रम_no_lun = 1;

	वापस 0;
पूर्ण

/* queue a command */
/* This is always called with scsi_lock(host) held */
अटल पूर्णांक queuecommand_lck(काष्ठा scsi_cmnd *srb,
			व्योम (*करोne)(काष्ठा scsi_cmnd *))
अणु
	काष्ठा us_data *us = host_to_us(srb->device->host);

	/* check क्रम state-transition errors */
	अगर (us->srb != शून्य) अणु
		dev_err(&us->pusb_पूर्णांकf->dev,
			"Error in %s: us->srb = %p\n", __func__, us->srb);
		वापस SCSI_MLQUEUE_HOST_BUSY;
	पूर्ण

	/* fail the command अगर we are disconnecting */
	अगर (test_bit(US_FLIDX_DISCONNECTING, &us->dflags)) अणु
		usb_stor_dbg(us, "Fail command during disconnect\n");
		srb->result = DID_NO_CONNECT << 16;
		करोne(srb);
		वापस 0;
	पूर्ण

	अगर ((us->fflags & US_FL_NO_ATA_1X) &&
			(srb->cmnd[0] == ATA_12 || srb->cmnd[0] == ATA_16)) अणु
		स_नकल(srb->sense_buffer, usb_stor_sense_invalidCDB,
		       माप(usb_stor_sense_invalidCDB));
		srb->result = SAM_STAT_CHECK_CONDITION;
		करोne(srb);
		वापस 0;
	पूर्ण

	/* enqueue the command and wake up the control thपढ़ो */
	srb->scsi_करोne = करोne;
	us->srb = srb;
	complete(&us->cmnd_पढ़ोy);

	वापस 0;
पूर्ण

अटल DEF_SCSI_QCMD(queuecommand)

/***********************************************************************
 * Error handling functions
 ***********************************************************************/

/* Command समयout and पात */
अटल पूर्णांक command_पात(काष्ठा scsi_cmnd *srb)
अणु
	काष्ठा us_data *us = host_to_us(srb->device->host);

	usb_stor_dbg(us, "%s called\n", __func__);

	/*
	 * us->srb together with the TIMED_OUT, RESETTING, and ABORTING
	 * bits are रक्षित by the host lock.
	 */
	scsi_lock(us_to_host(us));

	/* Is this command still active? */
	अगर (us->srb != srb) अणु
		scsi_unlock(us_to_host(us));
		usb_stor_dbg(us, "-- nothing to abort\n");
		वापस FAILED;
	पूर्ण

	/*
	 * Set the TIMED_OUT bit.  Also set the ABORTING bit, but only अगर
	 * a device reset isn't alपढ़ोy in progress (to aव्योम पूर्णांकerfering
	 * with the reset).  Note that we must retain the host lock जबतक
	 * calling usb_stor_stop_transport(); otherwise it might पूर्णांकerfere
	 * with an स्वतः-reset that begins as soon as we release the lock.
	 */
	set_bit(US_FLIDX_TIMED_OUT, &us->dflags);
	अगर (!test_bit(US_FLIDX_RESETTING, &us->dflags)) अणु
		set_bit(US_FLIDX_ABORTING, &us->dflags);
		usb_stor_stop_transport(us);
	पूर्ण
	scsi_unlock(us_to_host(us));

	/* Wait क्रम the पातed command to finish */
	रुको_क्रम_completion(&us->notअगरy);
	वापस SUCCESS;
पूर्ण

/*
 * This invokes the transport reset mechanism to reset the state of the
 * device
 */
अटल पूर्णांक device_reset(काष्ठा scsi_cmnd *srb)
अणु
	काष्ठा us_data *us = host_to_us(srb->device->host);
	पूर्णांक result;

	usb_stor_dbg(us, "%s called\n", __func__);

	/* lock the device poपूर्णांकers and करो the reset */
	mutex_lock(&(us->dev_mutex));
	result = us->transport_reset(us);
	mutex_unlock(&us->dev_mutex);

	वापस result < 0 ? FAILED : SUCCESS;
पूर्ण

/* Simulate a SCSI bus reset by resetting the device's USB port. */
अटल पूर्णांक bus_reset(काष्ठा scsi_cmnd *srb)
अणु
	काष्ठा us_data *us = host_to_us(srb->device->host);
	पूर्णांक result;

	usb_stor_dbg(us, "%s called\n", __func__);

	result = usb_stor_port_reset(us);
	वापस result < 0 ? FAILED : SUCCESS;
पूर्ण

/*
 * Report a driver-initiated device reset to the SCSI layer.
 * Calling this क्रम a SCSI-initiated reset is unnecessary but harmless.
 * The caller must own the SCSI host lock.
 */
व्योम usb_stor_report_device_reset(काष्ठा us_data *us)
अणु
	पूर्णांक i;
	काष्ठा Scsi_Host *host = us_to_host(us);

	scsi_report_device_reset(host, 0, 0);
	अगर (us->fflags & US_FL_SCM_MULT_TARG) अणु
		क्रम (i = 1; i < host->max_id; ++i)
			scsi_report_device_reset(host, 0, i);
	पूर्ण
पूर्ण

/*
 * Report a driver-initiated bus reset to the SCSI layer.
 * Calling this क्रम a SCSI-initiated reset is unnecessary but harmless.
 * The caller must not own the SCSI host lock.
 */
व्योम usb_stor_report_bus_reset(काष्ठा us_data *us)
अणु
	काष्ठा Scsi_Host *host = us_to_host(us);

	scsi_lock(host);
	scsi_report_bus_reset(host, 0);
	scsi_unlock(host);
पूर्ण

/***********************************************************************
 * /proc/scsi/ functions
 ***********************************************************************/

अटल पूर्णांक ग_लिखो_info(काष्ठा Scsi_Host *host, अक्षर *buffer, पूर्णांक length)
अणु
	/* अगर someone is sending us data, just throw it away */
	वापस length;
पूर्ण

अटल पूर्णांक show_info (काष्ठा seq_file *m, काष्ठा Scsi_Host *host)
अणु
	काष्ठा us_data *us = host_to_us(host);
	स्थिर अक्षर *string;

	/* prपूर्णांक the controller name */
	seq_म_लिखो(m, "   Host scsi%d: usb-storage\n", host->host_no);

	/* prपूर्णांक product, venकरोr, and serial number strings */
	अगर (us->pusb_dev->manufacturer)
		string = us->pusb_dev->manufacturer;
	अन्यथा अगर (us->unusual_dev->venकरोrName)
		string = us->unusual_dev->venकरोrName;
	अन्यथा
		string = "Unknown";
	seq_म_लिखो(m, "       Vendor: %s\n", string);
	अगर (us->pusb_dev->product)
		string = us->pusb_dev->product;
	अन्यथा अगर (us->unusual_dev->productName)
		string = us->unusual_dev->productName;
	अन्यथा
		string = "Unknown";
	seq_म_लिखो(m, "      Product: %s\n", string);
	अगर (us->pusb_dev->serial)
		string = us->pusb_dev->serial;
	अन्यथा
		string = "None";
	seq_म_लिखो(m, "Serial Number: %s\n", string);

	/* show the protocol and transport */
	seq_म_लिखो(m, "     Protocol: %s\n", us->protocol_name);
	seq_म_लिखो(m, "    Transport: %s\n", us->transport_name);

	/* show the device flags */
	seq_म_लिखो(m, "       Quirks:");

#घोषणा US_FLAG(name, value) \
	अगर (us->fflags & value) seq_म_लिखो(m, " " #name);
US_DO_ALL_FLAGS
#अघोषित US_FLAG
	seq_अ_दो(m, '\n');
	वापस 0;
पूर्ण

/***********************************************************************
 * Sysfs पूर्णांकerface
 ***********************************************************************/

/* Output routine क्रम the sysfs max_sectors file */
अटल sमाप_प्रकार max_sectors_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(dev);

	वापस प्र_लिखो(buf, "%u\n", queue_max_hw_sectors(sdev->request_queue));
पूर्ण

/* Input routine क्रम the sysfs max_sectors file */
अटल sमाप_प्रकार max_sectors_store(काष्ठा device *dev, काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
		माप_प्रकार count)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(dev);
	अचिन्हित लघु ms;

	अगर (माला_पूछो(buf, "%hu", &ms) > 0) अणु
		blk_queue_max_hw_sectors(sdev->request_queue, ms);
		वापस count;
	पूर्ण
	वापस -EINVAL;
पूर्ण
अटल DEVICE_ATTR_RW(max_sectors);

अटल काष्ठा device_attribute *sysfs_device_attr_list[] = अणु
	&dev_attr_max_sectors,
	शून्य,
पूर्ण;

/*
 * this defines our host ढाँचा, with which we'll allocate hosts
 */

अटल स्थिर काष्ठा scsi_host_ढाँचा usb_stor_host_ढाँचा = अणु
	/* basic userland पूर्णांकerface stuff */
	.name =				"usb-storage",
	.proc_name =			"usb-storage",
	.show_info =			show_info,
	.ग_लिखो_info =			ग_लिखो_info,
	.info =				host_info,

	/* command पूर्णांकerface -- queued only */
	.queuecommand =			queuecommand,

	/* error and पात handlers */
	.eh_पात_handler =		command_पात,
	.eh_device_reset_handler =	device_reset,
	.eh_bus_reset_handler =		bus_reset,

	/* queue commands only, only one command per LUN */
	.can_queue =			1,

	/* unknown initiator id */
	.this_id =			-1,

	.slave_alloc =			slave_alloc,
	.slave_configure =		slave_configure,
	.target_alloc =			target_alloc,

	/* lots of sg segments can be handled */
	.sg_tablesize =			SG_MAX_SEGMENTS,


	/*
	 * Limit the total size of a transfer to 120 KB.
	 *
	 * Some devices are known to choke with anything larger. It seems like
	 * the problem stems from the fact that original IDE controllers had
	 * only an 8-bit रेजिस्टर to hold the number of sectors in one transfer
	 * and even those couldn't handle a full 256 sectors.
	 *
	 * Because we want to make sure we पूर्णांकeroperate with as many devices as
	 * possible, we will मुख्यtain a 240 sector transfer size limit क्रम USB
	 * Mass Storage devices.
	 *
	 * Tests show that other operating have similar limits with Microsoft
	 * Winकरोws 7 limiting transfers to 128 sectors क्रम both USB2 and USB3
	 * and Apple Mac OS X 10.11 limiting transfers to 256 sectors क्रम USB2
	 * and 2048 क्रम USB3 devices.
	 */
	.max_sectors =                  240,

	/* emulated HBA */
	.emulated =			1,

	/* we करो our own delay after a device or bus reset */
	.skip_settle_delay =		1,

	/* sysfs device attributes */
	.sdev_attrs =			sysfs_device_attr_list,

	/* module management */
	.module =			THIS_MODULE
पूर्ण;

व्योम usb_stor_host_ढाँचा_init(काष्ठा scsi_host_ढाँचा *sht,
				 स्थिर अक्षर *name, काष्ठा module *owner)
अणु
	*sht = usb_stor_host_ढाँचा;
	sht->name = name;
	sht->proc_name = name;
	sht->module = owner;
पूर्ण
EXPORT_SYMBOL_GPL(usb_stor_host_ढाँचा_init);

/* To Report "Illegal Request: Invalid Field in CDB */
अचिन्हित अक्षर usb_stor_sense_invalidCDB[18] = अणु
	[0]	= 0x70,			    /* current error */
	[2]	= ILLEGAL_REQUEST,	    /* Illegal Request = 0x05 */
	[7]	= 0x0a,			    /* additional length */
	[12]	= 0x24			    /* Invalid Field in CDB */
पूर्ण;
EXPORT_SYMBOL_GPL(usb_stor_sense_invalidCDB);
