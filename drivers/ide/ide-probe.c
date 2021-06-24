<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (C) 1994-1998   Linus Torvalds & authors (see below)
 *  Copyright (C) 2005, 2007  Bartlomiej Zolnierkiewicz
 */

/*
 *  Mostly written by Mark Lord <mlord@pobox.com>
 *                and Gadi Oxman <gadio@netvision.net.il>
 *                and Andre Hedrick <andre@linux-ide.org>
 *
 *  See linux/MAINTAINERS क्रम address of current मुख्यtainer.
 *
 * This is the IDE probe module, as evolved from hd.c and ide.c.
 *
 * -- increase WAIT_PIDENTIFY to aव्योम CD-ROM locking at boot
 *	 by Andrea Arcangeli
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>
#समावेश <linux/समयr.h>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/major.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/genhd.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/ide.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/kmod.h>
#समावेश <linux/pci.h>
#समावेश <linux/scatterlist.h>

#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/irq.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/पन.स>

/**
 *	generic_id		-	add a generic drive id
 *	@drive:	drive to make an ID block क्रम
 *	
 *	Add a fake id field to the drive we are passed. This allows
 *	use to skip a ton of शून्य checks (which people always miss) 
 *	and make drive properties unconditional outside of this file
 */
 
अटल व्योम generic_id(ide_drive_t *drive)
अणु
	u16 *id = drive->id;

	id[ATA_ID_CUR_CYLS]	= id[ATA_ID_CYLS]	= drive->cyl;
	id[ATA_ID_CUR_HEADS]	= id[ATA_ID_HEADS]	= drive->head;
	id[ATA_ID_CUR_SECTORS]	= id[ATA_ID_SECTORS]	= drive->sect;
पूर्ण

अटल व्योम ide_disk_init_chs(ide_drive_t *drive)
अणु
	u16 *id = drive->id;

	/* Extract geometry अगर we did not alपढ़ोy have one क्रम the drive */
	अगर (!drive->cyl || !drive->head || !drive->sect) अणु
		drive->cyl  = drive->bios_cyl  = id[ATA_ID_CYLS];
		drive->head = drive->bios_head = id[ATA_ID_HEADS];
		drive->sect = drive->bios_sect = id[ATA_ID_SECTORS];
	पूर्ण

	/* Handle logical geometry translation by the drive */
	अगर (ata_id_current_chs_valid(id)) अणु
		drive->cyl  = id[ATA_ID_CUR_CYLS];
		drive->head = id[ATA_ID_CUR_HEADS];
		drive->sect = id[ATA_ID_CUR_SECTORS];
	पूर्ण

	/* Use physical geometry अगर what we have still makes no sense */
	अगर (drive->head > 16 && id[ATA_ID_HEADS] && id[ATA_ID_HEADS] <= 16) अणु
		drive->cyl  = id[ATA_ID_CYLS];
		drive->head = id[ATA_ID_HEADS];
		drive->sect = id[ATA_ID_SECTORS];
	पूर्ण
पूर्ण

अटल व्योम ide_disk_init_mult_count(ide_drive_t *drive)
अणु
	u16 *id = drive->id;
	u8 max_multsect = id[ATA_ID_MAX_MULTSECT] & 0xff;

	अगर (max_multsect) अणु
		अगर ((max_multsect / 2) > 1)
			id[ATA_ID_MULTSECT] = max_multsect | 0x100;
		अन्यथा
			id[ATA_ID_MULTSECT] &= ~0x1ff;

		drive->mult_req = id[ATA_ID_MULTSECT] & 0xff;

		अगर (drive->mult_req)
			drive->special_flags |= IDE_SFLAG_SET_MULTMODE;
	पूर्ण
पूर्ण

अटल व्योम ide_classअगरy_ata_dev(ide_drive_t *drive)
अणु
	u16 *id = drive->id;
	अक्षर *m = (अक्षर *)&id[ATA_ID_PROD];
	पूर्णांक is_cfa = ata_id_is_cfa(id);

	/* CF devices are *not* removable in Linux definition of the term */
	अगर (is_cfa == 0 && (id[ATA_ID_CONFIG] & (1 << 7)))
		drive->dev_flags |= IDE_DFLAG_REMOVABLE;

	drive->media = ide_disk;

	अगर (!ata_id_has_unload(drive->id))
		drive->dev_flags |= IDE_DFLAG_NO_UNLOAD;

	prपूर्णांकk(KERN_INFO "%s: %s, %s DISK drive\n", drive->name, m,
		is_cfa ? "CFA" : "ATA");
पूर्ण

अटल व्योम ide_classअगरy_atapi_dev(ide_drive_t *drive)
अणु
	u16 *id = drive->id;
	अक्षर *m = (अक्षर *)&id[ATA_ID_PROD];
	u8 type = (id[ATA_ID_CONFIG] >> 8) & 0x1f;

	prपूर्णांकk(KERN_INFO "%s: %s, ATAPI ", drive->name, m);
	चयन (type) अणु
	हाल ide_floppy:
		अगर (!म_माला(m, "CD-ROM")) अणु
			अगर (!म_माला(m, "oppy") &&
			    !म_माला(m, "poyp") &&
			    !म_माला(m, "ZIP"))
				prपूर्णांकk(KERN_CONT "cdrom or floppy?, assuming ");
			अगर (drive->media != ide_cdrom) अणु
				prपूर्णांकk(KERN_CONT "FLOPPY");
				drive->dev_flags |= IDE_DFLAG_REMOVABLE;
				अवरोध;
			पूर्ण
		पूर्ण
		/* Early cdrom models used zero */
		type = ide_cdrom;
		fallthrough;
	हाल ide_cdrom:
		drive->dev_flags |= IDE_DFLAG_REMOVABLE;
#अगर_घोषित CONFIG_PPC
		/* kludge क्रम Apple PowerBook पूर्णांकernal zip */
		अगर (!म_माला(m, "CD-ROM") && म_माला(m, "ZIP")) अणु
			prपूर्णांकk(KERN_CONT "FLOPPY");
			type = ide_floppy;
			अवरोध;
		पूर्ण
#पूर्ण_अगर
		prपूर्णांकk(KERN_CONT "CD/DVD-ROM");
		अवरोध;
	हाल ide_tape:
		prपूर्णांकk(KERN_CONT "TAPE");
		अवरोध;
	हाल ide_optical:
		prपूर्णांकk(KERN_CONT "OPTICAL");
		drive->dev_flags |= IDE_DFLAG_REMOVABLE;
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_CONT "UNKNOWN (type %d)", type);
		अवरोध;
	पूर्ण

	prपूर्णांकk(KERN_CONT " drive\n");
	drive->media = type;
	/* an ATAPI device ignores DRDY */
	drive->पढ़ोy_stat = 0;
	अगर (ata_id_cdb_पूर्णांकr(id))
		drive->atapi_flags |= IDE_AFLAG_DRQ_INTERRUPT;
	drive->dev_flags |= IDE_DFLAG_DOORLOCKING;
	/* we करोn't करो head unloading on ATAPI devices */
	drive->dev_flags |= IDE_DFLAG_NO_UNLOAD;
पूर्ण

/**
 *	करो_identअगरy	-	identअगरy a drive
 *	@drive: drive to identअगरy 
 *	@cmd: command used
 *	@id: buffer क्रम IDENTIFY data
 *
 *	Called when we have issued a drive identअगरy command to
 *	पढ़ो and parse the results. This function is run with
 *	पूर्णांकerrupts disabled. 
 */

अटल व्योम करो_identअगरy(ide_drive_t *drive, u8 cmd, u16 *id)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	अक्षर *m = (अक्षर *)&id[ATA_ID_PROD];
	अचिन्हित दीर्घ flags;
	पूर्णांक bswap = 1;

	/* local CPU only; some प्रणालीs need this */
	local_irq_save(flags);
	/* पढ़ो 512 bytes of id info */
	hwअगर->tp_ops->input_data(drive, शून्य, id, SECTOR_SIZE);
	local_irq_restore(flags);

	drive->dev_flags |= IDE_DFLAG_ID_READ;
#अगर_घोषित DEBUG
	prपूर्णांकk(KERN_INFO "%s: dumping identify data\n", drive->name);
	ide_dump_identअगरy((u8 *)id);
#पूर्ण_अगर
	ide_fix_driveid(id);

	/*
	 *  ATA_CMD_ID_ATA वापसs little-endian info,
	 *  ATA_CMD_ID_ATAPI *usually* वापसs little-endian info.
	 */
	अगर (cmd == ATA_CMD_ID_ATAPI) अणु
		अगर ((m[0] == 'N' && m[1] == 'E') ||  /* NEC */
		    (m[0] == 'F' && m[1] == 'X') ||  /* Mitsumi */
		    (m[0] == 'P' && m[1] == 'i'))    /* Pioneer */
			/* Vertos drives may still be weird */
			bswap ^= 1;
	पूर्ण

	ide_fixstring(m, ATA_ID_PROD_LEN, bswap);
	ide_fixstring((अक्षर *)&id[ATA_ID_FW_REV], ATA_ID_FW_REV_LEN, bswap);
	ide_fixstring((अक्षर *)&id[ATA_ID_SERNO], ATA_ID_SERNO_LEN, bswap);

	/* we depend on this a lot! */
	m[ATA_ID_PROD_LEN - 1] = '\0';

	अगर (म_माला(m, "E X A B Y T E N E S T"))
		drive->dev_flags &= ~IDE_DFLAG_PRESENT;
	अन्यथा
		drive->dev_flags |= IDE_DFLAG_PRESENT;
पूर्ण

/**
 *	ide_dev_पढ़ो_id	-	send ATA/ATAPI IDENTIFY command
 *	@drive: drive to identअगरy
 *	@cmd: command to use
 *	@id: buffer क्रम IDENTIFY data
 *	@irq_ctx: flag set when called from the IRQ context
 *
 *	Sends an ATA(PI) IDENTIFY request to a drive and रुकोs क्रम a response.
 *
 *	Returns:	0  device was identअगरied
 *			1  device समयd-out (no response to identअगरy request)
 *			2  device पातed the command (refused to identअगरy itself)
 */

पूर्णांक ide_dev_पढ़ो_id(ide_drive_t *drive, u8 cmd, u16 *id, पूर्णांक irq_ctx)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	काष्ठा ide_io_ports *io_ports = &hwअगर->io_ports;
	स्थिर काष्ठा ide_tp_ops *tp_ops = hwअगर->tp_ops;
	पूर्णांक use_altstatus = 0, rc;
	अचिन्हित दीर्घ समयout;
	u8 s = 0, a = 0;

	/*
	 * Disable device IRQ.  Otherwise we'll get spurious पूर्णांकerrupts
	 * during the identअगरy phase that the IRQ handler isn't expecting.
	 */
	अगर (io_ports->ctl_addr)
		tp_ops->ग_लिखो_devctl(hwअगर, ATA_NIEN | ATA_DEVCTL_OBS);

	/* take a deep breath */
	अगर (irq_ctx)
		mdelay(50);
	अन्यथा
		msleep(50);

	अगर (io_ports->ctl_addr &&
	    (hwअगर->host_flags & IDE_HFLAG_BROKEN_ALTSTATUS) == 0) अणु
		a = tp_ops->पढ़ो_altstatus(hwअगर);
		s = tp_ops->पढ़ो_status(hwअगर);
		अगर ((a ^ s) & ~ATA_SENSE)
			/* ancient Seagate drives, broken पूर्णांकerfaces */
			prपूर्णांकk(KERN_INFO "%s: probing with STATUS(0x%02x) "
					 "instead of ALTSTATUS(0x%02x)\n",
					 drive->name, s, a);
		अन्यथा
			/* use non-पूर्णांकrusive polling */
			use_altstatus = 1;
	पूर्ण

	/* set features रेजिस्टर क्रम atapi
	 * identअगरy command to be sure of reply
	 */
	अगर (cmd == ATA_CMD_ID_ATAPI) अणु
		काष्ठा ide_taskfile tf;

		स_रखो(&tf, 0, माप(tf));
		/* disable DMA & overlap */
		tp_ops->tf_load(drive, &tf, IDE_VALID_FEATURE);
	पूर्ण

	/* ask drive क्रम ID */
	tp_ops->exec_command(hwअगर, cmd);

	समयout = ((cmd == ATA_CMD_ID_ATA) ? WAIT_WORSTCASE : WAIT_PIDENTIFY) / 2;

	/* रुको क्रम IRQ and ATA_DRQ */
	अगर (irq_ctx) अणु
		rc = __ide_रुको_stat(drive, ATA_DRQ, BAD_R_STAT, समयout, &s);
		अगर (rc)
			वापस 1;
	पूर्ण अन्यथा अणु
		rc = ide_busy_sleep(drive, समयout, use_altstatus);
		अगर (rc)
			वापस 1;

		msleep(50);
		s = tp_ops->पढ़ो_status(hwअगर);
	पूर्ण

	अगर (OK_STAT(s, ATA_DRQ, BAD_R_STAT)) अणु
		/* drive वापसed ID */
		करो_identअगरy(drive, cmd, id);
		/* drive responded with ID */
		rc = 0;
		/* clear drive IRQ */
		(व्योम)tp_ops->पढ़ो_status(hwअगर);
	पूर्ण अन्यथा अणु
		/* drive refused ID */
		rc = 2;
	पूर्ण
	वापस rc;
पूर्ण

पूर्णांक ide_busy_sleep(ide_drive_t *drive, अचिन्हित दीर्घ समयout, पूर्णांक altstatus)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	u8 stat;

	समयout += jअगरfies;

	करो अणु
		msleep(50);	/* give drive a breather */
		stat = altstatus ? hwअगर->tp_ops->पढ़ो_altstatus(hwअगर)
				 : hwअगर->tp_ops->पढ़ो_status(hwअगर);
		अगर ((stat & ATA_BUSY) == 0)
			वापस 0;
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, समयout));

	prपूर्णांकk(KERN_ERR "%s: timeout in %s\n", drive->name, __func__);

	वापस 1;	/* drive समयd-out */
पूर्ण

अटल u8 ide_पढ़ो_device(ide_drive_t *drive)
अणु
	काष्ठा ide_taskfile tf;

	drive->hwअगर->tp_ops->tf_पढ़ो(drive, &tf, IDE_VALID_DEVICE);

	वापस tf.device;
पूर्ण

/**
 *	करो_probe		-	probe an IDE device
 *	@drive: drive to probe
 *	@cmd: command to use
 *
 *	करो_probe() has the dअगरficult job of finding a drive अगर it exists,
 *	without getting hung up अगर it करोesn't exist, without trampling on
 *	ethernet cards, and without leaving any IRQs dangling to haunt us later.
 *
 *	If a drive is "known" to exist (from CMOS or kernel parameters),
 *	but करोes not respond right away, the probe will "hang in there"
 *	क्रम the maximum रुको समय (about 30 seconds), otherwise it will
 *	निकास much more quickly.
 *
 * Returns:	0  device was identअगरied
 *		1  device समयd-out (no response to identअगरy request)
 *		2  device पातed the command (refused to identअगरy itself)
 *		3  bad status from device (possible क्रम ATAPI drives)
 *		4  probe was not attempted because failure was obvious
 */

अटल पूर्णांक करो_probe (ide_drive_t *drive, u8 cmd)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	स्थिर काष्ठा ide_tp_ops *tp_ops = hwअगर->tp_ops;
	u16 *id = drive->id;
	पूर्णांक rc;
	u8 present = !!(drive->dev_flags & IDE_DFLAG_PRESENT), stat;

	/* aव्योम रुकोing क्रम inappropriate probes */
	अगर (present && drive->media != ide_disk && cmd == ATA_CMD_ID_ATA)
		वापस 4;

#अगर_घोषित DEBUG
	prपूर्णांकk(KERN_INFO "probing for %s: present=%d, media=%d, probetype=%s\n",
		drive->name, present, drive->media,
		(cmd == ATA_CMD_ID_ATA) ? "ATA" : "ATAPI");
#पूर्ण_अगर

	/* needed क्रम some प्रणालीs
	 * (e.g. crw9624 as drive0 with disk as slave)
	 */
	msleep(50);
	tp_ops->dev_select(drive);
	msleep(50);

	अगर (ide_पढ़ो_device(drive) != drive->select && present == 0) अणु
		अगर (drive->dn & 1) अणु
			/* निकास with drive0 selected */
			tp_ops->dev_select(hwअगर->devices[0]);
			/* allow ATA_BUSY to निश्चित & clear */
			msleep(50);
		पूर्ण
		/* no i/f present: mmm.. this should be a 4 -ml */
		वापस 3;
	पूर्ण

	stat = tp_ops->पढ़ो_status(hwअगर);

	अगर (OK_STAT(stat, ATA_DRDY, ATA_BUSY) ||
	    present || cmd == ATA_CMD_ID_ATAPI) अणु
		rc = ide_dev_पढ़ो_id(drive, cmd, id, 0);
		अगर (rc)
			/* failed: try again */
			rc = ide_dev_पढ़ो_id(drive, cmd, id, 0);

		stat = tp_ops->पढ़ो_status(hwअगर);

		अगर (stat == (ATA_BUSY | ATA_DRDY))
			वापस 4;

		अगर (rc == 1 && cmd == ATA_CMD_ID_ATAPI) अणु
			prपूर्णांकk(KERN_ERR "%s: no response (status = 0x%02x), "
					"resetting drive\n", drive->name, stat);
			msleep(50);
			tp_ops->dev_select(drive);
			msleep(50);
			tp_ops->exec_command(hwअगर, ATA_CMD_DEV_RESET);
			(व्योम)ide_busy_sleep(drive, WAIT_WORSTCASE, 0);
			rc = ide_dev_पढ़ो_id(drive, cmd, id, 0);
		पूर्ण

		/* ensure drive IRQ is clear */
		stat = tp_ops->पढ़ो_status(hwअगर);

		अगर (rc == 1)
			prपूर्णांकk(KERN_ERR "%s: no response (status = 0x%02x)\n",
					drive->name, stat);
	पूर्ण अन्यथा अणु
		/* not present or maybe ATAPI */
		rc = 3;
	पूर्ण
	अगर (drive->dn & 1) अणु
		/* निकास with drive0 selected */
		tp_ops->dev_select(hwअगर->devices[0]);
		msleep(50);
		/* ensure drive irq is clear */
		(व्योम)tp_ops->पढ़ो_status(hwअगर);
	पूर्ण
	वापस rc;
पूर्ण

/**
 *	probe_क्रम_drives	-	upper level drive probe
 *	@drive: drive to probe क्रम
 *
 *	probe_क्रम_drive() tests क्रम existence of a given drive using करो_probe()
 *	and presents things to the user as needed.
 *
 *	Returns:	0  no device was found
 *			1  device was found
 *			   (note: IDE_DFLAG_PRESENT might still be not set)
 */

अटल u8 probe_क्रम_drive(ide_drive_t *drive)
अणु
	अक्षर *m;
	पूर्णांक rc;
	u8 cmd;

	drive->dev_flags &= ~IDE_DFLAG_ID_READ;

	m = (अक्षर *)&drive->id[ATA_ID_PROD];
	म_नकल(m, "UNKNOWN");

	/* skip probing? */
	अगर ((drive->dev_flags & IDE_DFLAG_NOPROBE) == 0) अणु
		/* अगर !(success||समयd-out) */
		cmd = ATA_CMD_ID_ATA;
		rc = करो_probe(drive, cmd);
		अगर (rc >= 2) अणु
			/* look क्रम ATAPI device */
			cmd = ATA_CMD_ID_ATAPI;
			rc = करो_probe(drive, cmd);
		पूर्ण

		अगर ((drive->dev_flags & IDE_DFLAG_PRESENT) == 0)
			वापस 0;

		/* identअगरication failed? */
		अगर ((drive->dev_flags & IDE_DFLAG_ID_READ) == 0) अणु
			अगर (drive->media == ide_disk) अणु
				prपूर्णांकk(KERN_INFO "%s: non-IDE drive, CHS=%d/%d/%d\n",
					drive->name, drive->cyl,
					drive->head, drive->sect);
			पूर्ण अन्यथा अगर (drive->media == ide_cdrom) अणु
				prपूर्णांकk(KERN_INFO "%s: ATAPI cdrom (?)\n", drive->name);
			पूर्ण अन्यथा अणु
				/* nuke it */
				prपूर्णांकk(KERN_WARNING "%s: Unknown device on bus refused identification. Ignoring.\n", drive->name);
				drive->dev_flags &= ~IDE_DFLAG_PRESENT;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (cmd == ATA_CMD_ID_ATAPI)
				ide_classअगरy_atapi_dev(drive);
			अन्यथा
				ide_classअगरy_ata_dev(drive);
		पूर्ण
	पूर्ण

	अगर ((drive->dev_flags & IDE_DFLAG_PRESENT) == 0)
		वापस 0;

	/* The drive wasn't being helpful. Add generic info only */
	अगर ((drive->dev_flags & IDE_DFLAG_ID_READ) == 0) अणु
		generic_id(drive);
		वापस 1;
	पूर्ण

	अगर (drive->media == ide_disk) अणु
		ide_disk_init_chs(drive);
		ide_disk_init_mult_count(drive);
	पूर्ण

	वापस 1;
पूर्ण

अटल व्योम hwअगर_release_dev(काष्ठा device *dev)
अणु
	ide_hwअगर_t *hwअगर = container_of(dev, ide_hwअगर_t, gendev);

	complete(&hwअगर->gendev_rel_comp);
पूर्ण

अटल पूर्णांक ide_रेजिस्टर_port(ide_hwअगर_t *hwअगर)
अणु
	पूर्णांक ret;

	/* रेजिस्टर with global device tree */
	dev_set_name(&hwअगर->gendev, "%s", hwअगर->name);
	dev_set_drvdata(&hwअगर->gendev, hwअगर);
	अगर (hwअगर->gendev.parent == शून्य)
		hwअगर->gendev.parent = hwअगर->dev;
	hwअगर->gendev.release = hwअगर_release_dev;

	ret = device_रेजिस्टर(&hwअगर->gendev);
	अगर (ret < 0) अणु
		prपूर्णांकk(KERN_WARNING "IDE: %s: device_register error: %d\n",
			__func__, ret);
		जाओ out;
	पूर्ण

	hwअगर->portdev = device_create(ide_port_class, &hwअगर->gendev,
				      MKDEV(0, 0), hwअगर, "%s", hwअगर->name);
	अगर (IS_ERR(hwअगर->portdev)) अणु
		ret = PTR_ERR(hwअगर->portdev);
		device_unरेजिस्टर(&hwअगर->gendev);
	पूर्ण
out:
	वापस ret;
पूर्ण

/**
 *	ide_port_रुको_पढ़ोy	-	रुको क्रम port to become पढ़ोy
 *	@hwअगर: IDE port
 *
 *	This is needed on some PPCs and a bunch of BIOS-less embedded
 *	platक्रमms.  Typical हालs are:
 *
 *	- The firmware hard reset the disk beक्रमe booting the kernel,
 *	  the drive is still करोing it's घातeron-reset sequence, that
 *	  can take up to 30 seconds.
 *
 *	- The firmware करोes nothing (or no firmware), the device is
 *	  still in POST state (same as above actually).
 *
 *	- Some CD/DVD/Writer combo drives tend to drive the bus during
 *	  their reset sequence even when they are non-selected slave
 *	  devices, thus preventing discovery of the मुख्य HD.
 *
 *	Doing this रुको-क्रम-non-busy should not harm any existing
 *	configuration and fix some issues like the above.
 *
 *	BenH.
 *
 *	Returns 0 on success, error code (< 0) otherwise.
 */

अटल पूर्णांक ide_port_रुको_पढ़ोy(ide_hwअगर_t *hwअगर)
अणु
	स्थिर काष्ठा ide_tp_ops *tp_ops = hwअगर->tp_ops;
	ide_drive_t *drive;
	पूर्णांक i, rc;

	prपूर्णांकk(KERN_DEBUG "Probing IDE interface %s...\n", hwअगर->name);

	/* Let HW settle करोwn a bit from whatever init state we
	 * come from */
	mdelay(2);

	/* Wait क्रम BSY bit to go away, spec समयout is 30 seconds,
	 * I know of at least one disk who takes 31 seconds, I use 35
	 * here to be safe
	 */
	rc = ide_रुको_not_busy(hwअगर, 35000);
	अगर (rc)
		वापस rc;

	/* Now make sure both master & slave are पढ़ोy */
	ide_port_क्रम_each_dev(i, drive, hwअगर) अणु
		/* Ignore disks that we will not probe क्रम later. */
		अगर ((drive->dev_flags & IDE_DFLAG_NOPROBE) == 0 ||
		    (drive->dev_flags & IDE_DFLAG_PRESENT)) अणु
			tp_ops->dev_select(drive);
			tp_ops->ग_लिखो_devctl(hwअगर, ATA_DEVCTL_OBS);
			mdelay(2);
			rc = ide_रुको_not_busy(hwअगर, 35000);
			अगर (rc)
				जाओ out;
		पूर्ण अन्यथा
			prपूर्णांकk(KERN_DEBUG "%s: ide_wait_not_busy() skipped\n",
					  drive->name);
	पूर्ण
out:
	/* Exit function with master reselected (let's be sane) */
	अगर (i)
		tp_ops->dev_select(hwअगर->devices[0]);

	वापस rc;
पूर्ण

/**
 *	ide_undecoded_slave	-	look क्रम bad CF adapters
 *	@dev1: slave device
 *
 *	Analyse the drives on the पूर्णांकerface and attempt to decide अगर we
 *	have the same drive viewed twice. This occurs with crap CF adapters
 *	and PCMCIA someबार.
 */

व्योम ide_undecoded_slave(ide_drive_t *dev1)
अणु
	ide_drive_t *dev0 = dev1->hwअगर->devices[0];

	अगर ((dev1->dn & 1) == 0 || (dev0->dev_flags & IDE_DFLAG_PRESENT) == 0)
		वापस;

	/* If the models करोn't match they are not the same product */
	अगर (म_भेद((अक्षर *)&dev0->id[ATA_ID_PROD],
		   (अक्षर *)&dev1->id[ATA_ID_PROD]))
		वापस;

	/* Serial numbers करो not match */
	अगर (म_भेदन((अक्षर *)&dev0->id[ATA_ID_SERNO],
		    (अक्षर *)&dev1->id[ATA_ID_SERNO], ATA_ID_SERNO_LEN))
		वापस;

	/* No serial number, thankfully very rare क्रम CF */
	अगर (*(अक्षर *)&dev0->id[ATA_ID_SERNO] == 0)
		वापस;

	/* Appears to be an IDE flash adapter with decode bugs */
	prपूर्णांकk(KERN_WARNING "ide-probe: ignoring undecoded slave\n");

	dev1->dev_flags &= ~IDE_DFLAG_PRESENT;
पूर्ण

EXPORT_SYMBOL_GPL(ide_undecoded_slave);

अटल पूर्णांक ide_probe_port(ide_hwअगर_t *hwअगर)
अणु
	ide_drive_t *drive;
	अचिन्हित पूर्णांक irqd;
	पूर्णांक i, rc = -ENODEV;

	BUG_ON(hwअगर->present);

	अगर ((hwअगर->devices[0]->dev_flags & IDE_DFLAG_NOPROBE) &&
	    (hwअगर->devices[1]->dev_flags & IDE_DFLAG_NOPROBE))
		वापस -EACCES;

	/*
	 * We must always disable IRQ, as probe_क्रम_drive will निश्चित IRQ, but
	 * we'll install our IRQ driver much later...
	 */
	irqd = hwअगर->irq;
	अगर (irqd)
		disable_irq(hwअगर->irq);

	अगर (ide_port_रुको_पढ़ोy(hwअगर) == -EBUSY)
		prपूर्णांकk(KERN_DEBUG "%s: Wait for ready failed before probe !\n", hwअगर->name);

	/*
	 * Second drive should only exist अगर first drive was found,
	 * but a lot of cdrom drives are configured as single slaves.
	 */
	ide_port_क्रम_each_dev(i, drive, hwअगर) अणु
		(व्योम) probe_क्रम_drive(drive);
		अगर (drive->dev_flags & IDE_DFLAG_PRESENT)
			rc = 0;
	पूर्ण

	/*
	 * Use cached IRQ number. It might be (and is...) changed by probe
	 * code above
	 */
	अगर (irqd)
		enable_irq(irqd);

	वापस rc;
पूर्ण

अटल व्योम ide_port_tune_devices(ide_hwअगर_t *hwअगर)
अणु
	स्थिर काष्ठा ide_port_ops *port_ops = hwअगर->port_ops;
	ide_drive_t *drive;
	पूर्णांक i;

	ide_port_क्रम_each_present_dev(i, drive, hwअगर) अणु
		ide_check_nien_quirk_list(drive);

		अगर (port_ops && port_ops->quirkproc)
			port_ops->quirkproc(drive);
	पूर्ण

	ide_port_क्रम_each_present_dev(i, drive, hwअगर) अणु
		ide_set_max_pio(drive);

		drive->dev_flags |= IDE_DFLAG_NICE1;

		अगर (hwअगर->dma_ops)
			ide_set_dma(drive);
	पूर्ण
पूर्ण

अटल व्योम ide_initialize_rq(काष्ठा request *rq)
अणु
	काष्ठा ide_request *req = blk_mq_rq_to_pdu(rq);

	req->special = शून्य;
	scsi_req_init(&req->sreq);
	req->sreq.sense = req->sense;
पूर्ण

अटल स्थिर काष्ठा blk_mq_ops ide_mq_ops = अणु
	.queue_rq		= ide_queue_rq,
	.initialize_rq_fn	= ide_initialize_rq,
पूर्ण;

/*
 * init request queue
 */
अटल पूर्णांक ide_init_queue(ide_drive_t *drive)
अणु
	काष्ठा request_queue *q;
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	पूर्णांक max_sectors = 256;
	पूर्णांक max_sg_entries = PRD_ENTRIES;
	काष्ठा blk_mq_tag_set *set;

	/*
	 *	Our शेष set up assumes the normal IDE हाल,
	 *	that is 64K segmenting, standard PRD setup
	 *	and LBA28. Some drivers then impose their own
	 *	limits and LBA48 we could उठाओ it but as yet
	 *	करो not.
	 */

	set = &drive->tag_set;
	set->ops = &ide_mq_ops;
	set->nr_hw_queues = 1;
	set->queue_depth = 32;
	set->reserved_tags = 1;
	set->cmd_size = माप(काष्ठा ide_request);
	set->numa_node = hwअगर_to_node(hwअगर);
	set->flags = BLK_MQ_F_SHOULD_MERGE | BLK_MQ_F_BLOCKING;
	अगर (blk_mq_alloc_tag_set(set))
		वापस 1;

	q = blk_mq_init_queue(set);
	अगर (IS_ERR(q)) अणु
		blk_mq_मुक्त_tag_set(set);
		वापस 1;
	पूर्ण

	blk_queue_flag_set(QUEUE_FLAG_SCSI_PASSTHROUGH, q);

	q->queuedata = drive;
	blk_queue_segment_boundary(q, 0xffff);

	अगर (hwअगर->rqsize < max_sectors)
		max_sectors = hwअगर->rqsize;
	blk_queue_max_hw_sectors(q, max_sectors);

#अगर_घोषित CONFIG_PCI
	/* When we have an IOMMU, we may have a problem where pci_map_sg()
	 * creates segments that करोn't completely match our boundary
	 * requirements and thus need to be broken up again. Because it
	 * करोesn't align properly either, we may actually have to अवरोध up
	 * to more segments than what was we got in the first place, a max
	 * worst हाल is twice as many.
	 * This will be fixed once we teach pci_map_sg() about our boundary
	 * requirements, hopefully soon. *FIXME*
	 */
	max_sg_entries >>= 1;
#पूर्ण_अगर /* CONFIG_PCI */

	blk_queue_max_segments(q, max_sg_entries);

	/* assign drive queue */
	drive->queue = q;

	वापस 0;
पूर्ण

अटल DEFINE_MUTEX(ide_cfg_mtx);

/*
 * For any present drive:
 * - allocate the block device queue
 */
अटल पूर्णांक ide_port_setup_devices(ide_hwअगर_t *hwअगर)
अणु
	ide_drive_t *drive;
	पूर्णांक i, j = 0;

	mutex_lock(&ide_cfg_mtx);
	ide_port_क्रम_each_present_dev(i, drive, hwअगर) अणु
		अगर (ide_init_queue(drive)) अणु
			prपूर्णांकk(KERN_ERR "ide: failed to init %s\n",
					drive->name);
			drive->dev_flags &= ~IDE_DFLAG_PRESENT;
			जारी;
		पूर्ण

		j++;
	पूर्ण
	mutex_unlock(&ide_cfg_mtx);

	वापस j;
पूर्ण

अटल व्योम ide_host_enable_irqs(काष्ठा ide_host *host)
अणु
	ide_hwअगर_t *hwअगर;
	पूर्णांक i;

	ide_host_क्रम_each_port(i, hwअगर, host) अणु
		अगर (hwअगर == शून्य)
			जारी;

		/* clear any pending IRQs */
		hwअगर->tp_ops->पढ़ो_status(hwअगर);

		/* unmask IRQs */
		अगर (hwअगर->io_ports.ctl_addr)
			hwअगर->tp_ops->ग_लिखो_devctl(hwअगर, ATA_DEVCTL_OBS);
	पूर्ण
पूर्ण

/*
 * This routine sets up the IRQ क्रम an IDE पूर्णांकerface.
 */
अटल पूर्णांक init_irq (ide_hwअगर_t *hwअगर)
अणु
	काष्ठा ide_io_ports *io_ports = &hwअगर->io_ports;
	काष्ठा ide_host *host = hwअगर->host;
	irq_handler_t irq_handler = host->irq_handler;
	पूर्णांक sa = host->irq_flags;

	अगर (irq_handler == शून्य)
		irq_handler = ide_पूर्णांकr;

	अगर (!host->get_lock)
		अगर (request_irq(hwअगर->irq, irq_handler, sa, hwअगर->name, hwअगर))
			जाओ out_up;

#अगर !defined(__mc68000__)
	prपूर्णांकk(KERN_INFO "%s at 0x%03lx-0x%03lx,0x%03lx on irq %d", hwअगर->name,
		io_ports->data_addr, io_ports->status_addr,
		io_ports->ctl_addr, hwअगर->irq);
#अन्यथा
	prपूर्णांकk(KERN_INFO "%s at 0x%08lx on irq %d", hwअगर->name,
		io_ports->data_addr, hwअगर->irq);
#पूर्ण_अगर /* __mc68000__ */
	अगर (hwअगर->host->host_flags & IDE_HFLAG_SERIALIZE)
		prपूर्णांकk(KERN_CONT " (serialized)");
	prपूर्णांकk(KERN_CONT "\n");

	वापस 0;
out_up:
	वापस 1;
पूर्ण

अटल व्योम ata_probe(dev_t dev)
अणु
	request_module("ide-disk");
	request_module("ide-cd");
	request_module("ide-tape");
	request_module("ide-floppy");
पूर्ण

व्योम ide_init_disk(काष्ठा gendisk *disk, ide_drive_t *drive)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	अचिन्हित पूर्णांक unit = drive->dn & 1;

	disk->major = hwअगर->major;
	disk->first_minor = unit << PARTN_BITS;
	प्र_लिखो(disk->disk_name, "hd%c", 'a' + hwअगर->index * MAX_DRIVES + unit);
	disk->queue = drive->queue;
पूर्ण

EXPORT_SYMBOL_GPL(ide_init_disk);

अटल व्योम drive_release_dev (काष्ठा device *dev)
अणु
	ide_drive_t *drive = container_of(dev, ide_drive_t, gendev);

	ide_proc_unरेजिस्टर_device(drive);

	अगर (drive->sense_rq)
		blk_mq_मुक्त_request(drive->sense_rq);

	blk_cleanup_queue(drive->queue);
	drive->queue = शून्य;
	blk_mq_मुक्त_tag_set(&drive->tag_set);

	drive->dev_flags &= ~IDE_DFLAG_PRESENT;

	complete(&drive->gendev_rel_comp);
पूर्ण

अटल पूर्णांक hwअगर_init(ide_hwअगर_t *hwअगर)
अणु
	अगर (!hwअगर->irq) अणु
		prपूर्णांकk(KERN_ERR "%s: disabled, no IRQ\n", hwअगर->name);
		वापस 0;
	पूर्ण

	अगर (__रेजिस्टर_blkdev(hwअगर->major, hwअगर->name, ata_probe))
		वापस 0;

	अगर (!hwअगर->sg_max_nents)
		hwअगर->sg_max_nents = PRD_ENTRIES;

	hwअगर->sg_table = kदो_स्मृति_array(hwअगर->sg_max_nents,
				       माप(काष्ठा scatterlist),
				       GFP_KERNEL);
	अगर (!hwअगर->sg_table) अणु
		prपूर्णांकk(KERN_ERR "%s: unable to allocate SG table.\n", hwअगर->name);
		जाओ out;
	पूर्ण

	sg_init_table(hwअगर->sg_table, hwअगर->sg_max_nents);
	
	अगर (init_irq(hwअगर)) अणु
		prपूर्णांकk(KERN_ERR "%s: disabled, unable to get IRQ %d\n",
			hwअगर->name, hwअगर->irq);
		जाओ out;
	पूर्ण

	वापस 1;

out:
	unरेजिस्टर_blkdev(hwअगर->major, hwअगर->name);
	वापस 0;
पूर्ण

अटल व्योम hwअगर_रेजिस्टर_devices(ide_hwअगर_t *hwअगर)
अणु
	ide_drive_t *drive;
	अचिन्हित पूर्णांक i;

	ide_port_क्रम_each_present_dev(i, drive, hwअगर) अणु
		काष्ठा device *dev = &drive->gendev;
		पूर्णांक ret;

		dev_set_name(dev, "%u.%u", hwअगर->index, i);
		dev_set_drvdata(dev, drive);
		dev->parent = &hwअगर->gendev;
		dev->bus = &ide_bus_type;
		dev->release = drive_release_dev;

		ret = device_रेजिस्टर(dev);
		अगर (ret < 0)
			prपूर्णांकk(KERN_WARNING "IDE: %s: device_register error: "
					    "%d\n", __func__, ret);
	पूर्ण
पूर्ण

अटल व्योम ide_port_init_devices(ide_hwअगर_t *hwअगर)
अणु
	स्थिर काष्ठा ide_port_ops *port_ops = hwअगर->port_ops;
	ide_drive_t *drive;
	पूर्णांक i;

	ide_port_क्रम_each_dev(i, drive, hwअगर) अणु
		drive->dn = i + hwअगर->channel * 2;

		अगर (hwअगर->host_flags & IDE_HFLAG_IO_32BIT)
			drive->io_32bit = 1;
		अगर (hwअगर->host_flags & IDE_HFLAG_NO_IO_32BIT)
			drive->dev_flags |= IDE_DFLAG_NO_IO_32BIT;
		अगर (hwअगर->host_flags & IDE_HFLAG_UNMASK_IRQS)
			drive->dev_flags |= IDE_DFLAG_UNMASK;
		अगर (hwअगर->host_flags & IDE_HFLAG_NO_UNMASK_IRQS)
			drive->dev_flags |= IDE_DFLAG_NO_UNMASK;

		drive->pio_mode = XFER_PIO_0;

		अगर (port_ops && port_ops->init_dev)
			port_ops->init_dev(drive);
	पूर्ण
पूर्ण

अटल व्योम ide_init_port(ide_hwअगर_t *hwअगर, अचिन्हित पूर्णांक port,
			  स्थिर काष्ठा ide_port_info *d)
अणु
	hwअगर->channel = port;

	hwअगर->chipset = d->chipset ? d->chipset : ide_pci;

	अगर (d->init_iops)
		d->init_iops(hwअगर);

	/* ->host_flags may be set by ->init_iops (or even earlier...) */
	hwअगर->host_flags |= d->host_flags;
	hwअगर->pio_mask = d->pio_mask;

	अगर (d->tp_ops)
		hwअगर->tp_ops = d->tp_ops;

	/* ->set_pio_mode क्रम DTC2278 is currently limited to port 0 */
	अगर ((hwअगर->host_flags & IDE_HFLAG_DTC2278) == 0 || hwअगर->channel == 0)
		hwअगर->port_ops = d->port_ops;

	hwअगर->swdma_mask = d->swdma_mask;
	hwअगर->mwdma_mask = d->mwdma_mask;
	hwअगर->ultra_mask = d->udma_mask;

	अगर ((d->host_flags & IDE_HFLAG_NO_DMA) == 0) अणु
		पूर्णांक rc;

		hwअगर->dma_ops = d->dma_ops;

		अगर (d->init_dma)
			rc = d->init_dma(hwअगर, d);
		अन्यथा
			rc = ide_hwअगर_setup_dma(hwअगर, d);

		अगर (rc < 0) अणु
			prपूर्णांकk(KERN_INFO "%s: DMA disabled\n", hwअगर->name);

			hwअगर->dma_ops = शून्य;
			hwअगर->dma_base = 0;
			hwअगर->swdma_mask = 0;
			hwअगर->mwdma_mask = 0;
			hwअगर->ultra_mask = 0;
		पूर्ण
	पूर्ण

	अगर ((d->host_flags & IDE_HFLAG_SERIALIZE) ||
	    ((d->host_flags & IDE_HFLAG_SERIALIZE_DMA) && hwअगर->dma_base))
		hwअगर->host->host_flags |= IDE_HFLAG_SERIALIZE;

	अगर (d->max_sectors)
		hwअगर->rqsize = d->max_sectors;
	अन्यथा अणु
		अगर ((hwअगर->host_flags & IDE_HFLAG_NO_LBA48) ||
		    (hwअगर->host_flags & IDE_HFLAG_NO_LBA48_DMA))
			hwअगर->rqsize = 256;
		अन्यथा
			hwअगर->rqsize = 65536;
	पूर्ण

	/* call chipset specअगरic routine क्रम each enabled port */
	अगर (d->init_hwअगर)
		d->init_hwअगर(hwअगर);
पूर्ण

अटल व्योम ide_port_cable_detect(ide_hwअगर_t *hwअगर)
अणु
	स्थिर काष्ठा ide_port_ops *port_ops = hwअगर->port_ops;

	अगर (port_ops && port_ops->cable_detect && (hwअगर->ultra_mask & 0x78)) अणु
		अगर (hwअगर->cbl != ATA_CBL_PATA40_SHORT)
			hwअगर->cbl = port_ops->cable_detect(hwअगर);
	पूर्ण
पूर्ण

/*
 * Deferred request list insertion handler
 */
अटल व्योम drive_rq_insert_work(काष्ठा work_काष्ठा *work)
अणु
	ide_drive_t *drive = container_of(work, ide_drive_t, rq_work);
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	काष्ठा request *rq;
	blk_status_t ret;
	LIST_HEAD(list);

	blk_mq_quiesce_queue(drive->queue);

	ret = BLK_STS_OK;
	spin_lock_irq(&hwअगर->lock);
	जबतक (!list_empty(&drive->rq_list)) अणु
		rq = list_first_entry(&drive->rq_list, काष्ठा request, queuelist);
		list_del_init(&rq->queuelist);

		spin_unlock_irq(&hwअगर->lock);
		ret = ide_issue_rq(drive, rq, true);
		spin_lock_irq(&hwअगर->lock);
	पूर्ण
	spin_unlock_irq(&hwअगर->lock);

	blk_mq_unquiesce_queue(drive->queue);

	अगर (ret != BLK_STS_OK)
		kblockd_schedule_work(&drive->rq_work);
पूर्ण

अटल स्थिर u8 ide_hwअगर_to_major[] =
	अणु IDE0_MAJOR, IDE1_MAJOR, IDE2_MAJOR, IDE3_MAJOR, IDE4_MAJOR,
	  IDE5_MAJOR, IDE6_MAJOR, IDE7_MAJOR, IDE8_MAJOR, IDE9_MAJOR पूर्ण;

अटल व्योम ide_port_init_devices_data(ide_hwअगर_t *hwअगर)
अणु
	ide_drive_t *drive;
	पूर्णांक i;

	ide_port_क्रम_each_dev(i, drive, hwअगर) अणु
		u8 j = (hwअगर->index * MAX_DRIVES) + i;
		u16 *saved_id = drive->id;

		स_रखो(drive, 0, माप(*drive));
		स_रखो(saved_id, 0, SECTOR_SIZE);
		drive->id = saved_id;

		drive->media			= ide_disk;
		drive->select			= (i << 4) | ATA_DEVICE_OBS;
		drive->hwअगर			= hwअगर;
		drive->पढ़ोy_stat		= ATA_DRDY;
		drive->bad_wstat		= BAD_W_STAT;
		drive->special_flags		= IDE_SFLAG_RECALIBRATE |
						  IDE_SFLAG_SET_GEOMETRY;
		drive->name[0]			= 'h';
		drive->name[1]			= 'd';
		drive->name[2]			= 'a' + j;
		drive->max_failures		= IDE_DEFAULT_MAX_FAILURES;

		INIT_LIST_HEAD(&drive->list);
		init_completion(&drive->gendev_rel_comp);

		INIT_WORK(&drive->rq_work, drive_rq_insert_work);
		INIT_LIST_HEAD(&drive->rq_list);
	पूर्ण
पूर्ण

अटल व्योम ide_init_port_data(ide_hwअगर_t *hwअगर, अचिन्हित पूर्णांक index)
अणु
	/* fill in any non-zero initial values */
	hwअगर->index	= index;
	hwअगर->major	= ide_hwअगर_to_major[index];

	hwअगर->name[0]	= 'i';
	hwअगर->name[1]	= 'd';
	hwअगर->name[2]	= 'e';
	hwअगर->name[3]	= '0' + index;

	spin_lock_init(&hwअगर->lock);

	समयr_setup(&hwअगर->समयr, ide_समयr_expiry, 0);

	init_completion(&hwअगर->gendev_rel_comp);

	hwअगर->tp_ops = &शेष_tp_ops;

	ide_port_init_devices_data(hwअगर);
पूर्ण

अटल व्योम ide_init_port_hw(ide_hwअगर_t *hwअगर, काष्ठा ide_hw *hw)
अणु
	स_नकल(&hwअगर->io_ports, &hw->io_ports, माप(hwअगर->io_ports));
	hwअगर->irq = hw->irq;
	hwअगर->dev = hw->dev;
	hwअगर->gendev.parent = hw->parent ? hw->parent : hw->dev;
	hwअगर->config_data = hw->config;
पूर्ण

अटल अचिन्हित पूर्णांक ide_indexes;

/**
 *	ide_find_port_slot	-	find मुक्त port slot
 *	@d: IDE port info
 *
 *	Return the new port slot index or -ENOENT अगर we are out of मुक्त slots.
 */

अटल पूर्णांक ide_find_port_slot(स्थिर काष्ठा ide_port_info *d)
अणु
	पूर्णांक idx = -ENOENT;
	u8 bootable = (d && (d->host_flags & IDE_HFLAG_NON_BOOTABLE)) ? 0 : 1;
	u8 i = (d && (d->host_flags & IDE_HFLAG_QD_2ND_PORT)) ? 1 : 0;

	/*
	 * Claim an unasचिन्हित slot.
	 *
	 * Give preference to claiming other slots beक्रमe claiming ide0/ide1,
	 * just in हाल there's another पूर्णांकerface yet-to-be-scanned
	 * which uses ports 0x1f0/0x170 (the ide0/ide1 शेषs).
	 *
	 * Unless there is a bootable card that करोes not use the standard
	 * ports 0x1f0/0x170 (the ide0/ide1 शेषs).
	 */
	mutex_lock(&ide_cfg_mtx);
	अगर (bootable) अणु
		अगर ((ide_indexes | i) != (1 << MAX_HWIFS) - 1)
			idx = ffz(ide_indexes | i);
	पूर्ण अन्यथा अणु
		अगर ((ide_indexes | 3) != (1 << MAX_HWIFS) - 1)
			idx = ffz(ide_indexes | 3);
		अन्यथा अगर ((ide_indexes & 3) != 3)
			idx = ffz(ide_indexes);
	पूर्ण
	अगर (idx >= 0)
		ide_indexes |= (1 << idx);
	mutex_unlock(&ide_cfg_mtx);

	वापस idx;
पूर्ण

अटल व्योम ide_मुक्त_port_slot(पूर्णांक idx)
अणु
	mutex_lock(&ide_cfg_mtx);
	ide_indexes &= ~(1 << idx);
	mutex_unlock(&ide_cfg_mtx);
पूर्ण

अटल व्योम ide_port_मुक्त_devices(ide_hwअगर_t *hwअगर)
अणु
	ide_drive_t *drive;
	पूर्णांक i;

	ide_port_क्रम_each_dev(i, drive, hwअगर) अणु
		kमुक्त(drive->id);
		kमुक्त(drive);
	पूर्ण
पूर्ण

अटल पूर्णांक ide_port_alloc_devices(ide_hwअगर_t *hwअगर, पूर्णांक node)
अणु
	ide_drive_t *drive;
	पूर्णांक i;

	क्रम (i = 0; i < MAX_DRIVES; i++) अणु
		drive = kzalloc_node(माप(*drive), GFP_KERNEL, node);
		अगर (drive == शून्य)
			जाओ out_nomem;

		/*
		 * In order to keep things simple we have an id
		 * block क्रम all drives at all बार. If the device
		 * is pre ATA or refuses ATA/ATAPI identअगरy we
		 * will add faked data to this.
		 *
		 * Also note that 0 everywhere means "can't do X"
		 */
		drive->id = kzalloc_node(SECTOR_SIZE, GFP_KERNEL, node);
		अगर (drive->id == शून्य)
			जाओ out_मुक्त_drive;

		hwअगर->devices[i] = drive;
	पूर्ण
	वापस 0;

out_मुक्त_drive:
	kमुक्त(drive);
out_nomem:
	ide_port_मुक्त_devices(hwअगर);
	वापस -ENOMEM;
पूर्ण

काष्ठा ide_host *ide_host_alloc(स्थिर काष्ठा ide_port_info *d,
				काष्ठा ide_hw **hws, अचिन्हित पूर्णांक n_ports)
अणु
	काष्ठा ide_host *host;
	काष्ठा device *dev = hws[0] ? hws[0]->dev : शून्य;
	पूर्णांक node = dev ? dev_to_node(dev) : -1;
	पूर्णांक i;

	host = kzalloc_node(माप(*host), GFP_KERNEL, node);
	अगर (host == शून्य)
		वापस शून्य;

	क्रम (i = 0; i < n_ports; i++) अणु
		ide_hwअगर_t *hwअगर;
		पूर्णांक idx;

		अगर (hws[i] == शून्य)
			जारी;

		hwअगर = kzalloc_node(माप(*hwअगर), GFP_KERNEL, node);
		अगर (hwअगर == शून्य)
			जारी;

		अगर (ide_port_alloc_devices(hwअगर, node) < 0) अणु
			kमुक्त(hwअगर);
			जारी;
		पूर्ण

		idx = ide_find_port_slot(d);
		अगर (idx < 0) अणु
			prपूर्णांकk(KERN_ERR "%s: no free slot for interface\n",
					d ? d->name : "ide");
			ide_port_मुक्त_devices(hwअगर);
			kमुक्त(hwअगर);
			जारी;
		पूर्ण

		ide_init_port_data(hwअगर, idx);

		hwअगर->host = host;

		host->ports[i] = hwअगर;
		host->n_ports++;
	पूर्ण

	अगर (host->n_ports == 0) अणु
		kमुक्त(host);
		वापस शून्य;
	पूर्ण

	host->dev[0] = dev;

	अगर (d) अणु
		host->init_chipset = d->init_chipset;
		host->get_lock     = d->get_lock;
		host->release_lock = d->release_lock;
		host->host_flags = d->host_flags;
		host->irq_flags = d->irq_flags;
	पूर्ण

	वापस host;
पूर्ण
EXPORT_SYMBOL_GPL(ide_host_alloc);

अटल व्योम ide_port_मुक्त(ide_hwअगर_t *hwअगर)
अणु
	ide_port_मुक्त_devices(hwअगर);
	ide_मुक्त_port_slot(hwअगर->index);
	kमुक्त(hwअगर);
पूर्ण

अटल व्योम ide_disable_port(ide_hwअगर_t *hwअगर)
अणु
	काष्ठा ide_host *host = hwअगर->host;
	पूर्णांक i;

	prपूर्णांकk(KERN_INFO "%s: disabling port\n", hwअगर->name);

	क्रम (i = 0; i < MAX_HOST_PORTS; i++) अणु
		अगर (host->ports[i] == hwअगर) अणु
			host->ports[i] = शून्य;
			host->n_ports--;
		पूर्ण
	पूर्ण

	ide_port_मुक्त(hwअगर);
पूर्ण

पूर्णांक ide_host_रेजिस्टर(काष्ठा ide_host *host, स्थिर काष्ठा ide_port_info *d,
		      काष्ठा ide_hw **hws)
अणु
	ide_hwअगर_t *hwअगर, *mate = शून्य;
	पूर्णांक i, j = 0;

	pr_warn("legacy IDE will be removed in 2021, please switch to libata\n"
		"Report any missing HW support to linux-ide@vger.kernel.org\n");

	ide_host_क्रम_each_port(i, hwअगर, host) अणु
		अगर (hwअगर == शून्य) अणु
			mate = शून्य;
			जारी;
		पूर्ण

		ide_init_port_hw(hwअगर, hws[i]);
		ide_port_apply_params(hwअगर);

		अगर ((i & 1) && mate) अणु
			hwअगर->mate = mate;
			mate->mate = hwअगर;
		पूर्ण

		mate = (i & 1) ? शून्य : hwअगर;

		ide_init_port(hwअगर, i & 1, d);
		ide_port_cable_detect(hwअगर);

		hwअगर->port_flags |= IDE_PFLAG_PROBING;

		ide_port_init_devices(hwअगर);
	पूर्ण

	ide_host_क्रम_each_port(i, hwअगर, host) अणु
		अगर (hwअगर == शून्य)
			जारी;

		अगर (ide_probe_port(hwअगर) == 0)
			hwअगर->present = 1;

		hwअगर->port_flags &= ~IDE_PFLAG_PROBING;

		अगर ((hwअगर->host_flags & IDE_HFLAG_4DRIVES) == 0 ||
		    hwअगर->mate == शून्य || hwअगर->mate->present == 0) अणु
			अगर (ide_रेजिस्टर_port(hwअगर)) अणु
				ide_disable_port(hwअगर);
				जारी;
			पूर्ण
		पूर्ण

		अगर (hwअगर->present)
			ide_port_tune_devices(hwअगर);
	पूर्ण

	ide_host_enable_irqs(host);

	ide_host_क्रम_each_port(i, hwअगर, host) अणु
		अगर (hwअगर == शून्य)
			जारी;

		अगर (hwअगर_init(hwअगर) == 0) अणु
			prपूर्णांकk(KERN_INFO "%s: failed to initialize IDE "
					 "interface\n", hwअगर->name);
			device_unरेजिस्टर(hwअगर->portdev);
			device_unरेजिस्टर(&hwअगर->gendev);
			ide_disable_port(hwअगर);
			जारी;
		पूर्ण

		अगर (hwअगर->present)
			अगर (ide_port_setup_devices(hwअगर) == 0) अणु
				hwअगर->present = 0;
				जारी;
			पूर्ण

		j++;

		ide_acpi_init_port(hwअगर);

		अगर (hwअगर->present)
			ide_acpi_port_init_devices(hwअगर);
	पूर्ण

	ide_host_क्रम_each_port(i, hwअगर, host) अणु
		अगर (hwअगर == शून्य)
			जारी;

		ide_sysfs_रेजिस्टर_port(hwअगर);
		ide_proc_रेजिस्टर_port(hwअगर);

		अगर (hwअगर->present) अणु
			ide_proc_port_रेजिस्टर_devices(hwअगर);
			hwअगर_रेजिस्टर_devices(hwअगर);
		पूर्ण
	पूर्ण

	वापस j ? 0 : -1;
पूर्ण
EXPORT_SYMBOL_GPL(ide_host_रेजिस्टर);

पूर्णांक ide_host_add(स्थिर काष्ठा ide_port_info *d, काष्ठा ide_hw **hws,
		 अचिन्हित पूर्णांक n_ports, काष्ठा ide_host **hostp)
अणु
	काष्ठा ide_host *host;
	पूर्णांक rc;

	host = ide_host_alloc(d, hws, n_ports);
	अगर (host == शून्य)
		वापस -ENOMEM;

	rc = ide_host_रेजिस्टर(host, d, hws);
	अगर (rc) अणु
		ide_host_मुक्त(host);
		वापस rc;
	पूर्ण

	अगर (hostp)
		*hostp = host;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ide_host_add);

अटल व्योम __ide_port_unरेजिस्टर_devices(ide_hwअगर_t *hwअगर)
अणु
	ide_drive_t *drive;
	पूर्णांक i;

	ide_port_क्रम_each_present_dev(i, drive, hwअगर) अणु
		device_unरेजिस्टर(&drive->gendev);
		रुको_क्रम_completion(&drive->gendev_rel_comp);
	पूर्ण
पूर्ण

व्योम ide_port_unरेजिस्टर_devices(ide_hwअगर_t *hwअगर)
अणु
	mutex_lock(&ide_cfg_mtx);
	__ide_port_unरेजिस्टर_devices(hwअगर);
	hwअगर->present = 0;
	ide_port_init_devices_data(hwअगर);
	mutex_unlock(&ide_cfg_mtx);
पूर्ण
EXPORT_SYMBOL_GPL(ide_port_unरेजिस्टर_devices);

/**
 *	ide_unरेजिस्टर		-	मुक्त an IDE पूर्णांकerface
 *	@hwअगर: IDE पूर्णांकerface
 *
 *	Perक्रमm the final unरेजिस्टर of an IDE पूर्णांकerface.
 *
 *	Locking:
 *	The caller must not hold the IDE locks.
 *
 *	It is up to the caller to be sure there is no pending I/O here,
 *	and that the पूर्णांकerface will not be reखोलोed (present/vanishing
 *	locking isn't yet करोne BTW).
 */

अटल व्योम ide_unरेजिस्टर(ide_hwअगर_t *hwअगर)
अणु
	mutex_lock(&ide_cfg_mtx);

	अगर (hwअगर->present) अणु
		__ide_port_unरेजिस्टर_devices(hwअगर);
		hwअगर->present = 0;
	पूर्ण

	ide_proc_unरेजिस्टर_port(hwअगर);

	अगर (!hwअगर->host->get_lock)
		मुक्त_irq(hwअगर->irq, hwअगर);

	device_unरेजिस्टर(hwअगर->portdev);
	device_unरेजिस्टर(&hwअगर->gendev);
	रुको_क्रम_completion(&hwअगर->gendev_rel_comp);

	/*
	 * Remove us from the kernel's knowledge
	 */
	kमुक्त(hwअगर->sg_table);
	unरेजिस्टर_blkdev(hwअगर->major, hwअगर->name);

	ide_release_dma_engine(hwअगर);

	mutex_unlock(&ide_cfg_mtx);
पूर्ण

व्योम ide_host_मुक्त(काष्ठा ide_host *host)
अणु
	ide_hwअगर_t *hwअगर;
	पूर्णांक i;

	ide_host_क्रम_each_port(i, hwअगर, host) अणु
		अगर (hwअगर)
			ide_port_मुक्त(hwअगर);
	पूर्ण

	kमुक्त(host);
पूर्ण
EXPORT_SYMBOL_GPL(ide_host_मुक्त);

व्योम ide_host_हटाओ(काष्ठा ide_host *host)
अणु
	ide_hwअगर_t *hwअगर;
	पूर्णांक i;

	ide_host_क्रम_each_port(i, hwअगर, host) अणु
		अगर (hwअगर)
			ide_unरेजिस्टर(hwअगर);
	पूर्ण

	ide_host_मुक्त(host);
पूर्ण
EXPORT_SYMBOL_GPL(ide_host_हटाओ);

व्योम ide_port_scan(ide_hwअगर_t *hwअगर)
अणु
	पूर्णांक rc;

	ide_port_apply_params(hwअगर);
	ide_port_cable_detect(hwअगर);

	hwअगर->port_flags |= IDE_PFLAG_PROBING;

	ide_port_init_devices(hwअगर);

	rc = ide_probe_port(hwअगर);

	hwअगर->port_flags &= ~IDE_PFLAG_PROBING;

	अगर (rc < 0)
		वापस;

	hwअगर->present = 1;

	ide_port_tune_devices(hwअगर);
	ide_port_setup_devices(hwअगर);
	ide_acpi_port_init_devices(hwअगर);
	hwअगर_रेजिस्टर_devices(hwअगर);
	ide_proc_port_रेजिस्टर_devices(hwअगर);
पूर्ण
EXPORT_SYMBOL_GPL(ide_port_scan);
