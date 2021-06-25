<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (C) 2000-2002	Andre Hedrick <andre@linux-ide.org>
 *  Copyright (C) 2003		Red Hat
 *
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
#समावेश <linux/blkpg.h>
#समावेश <linux/slab.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/ide.h>
#समावेश <linux/bitops.h>
#समावेश <linux/nmi.h>

#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/irq.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/पन.स>

व्योम SELECT_MASK(ide_drive_t *drive, पूर्णांक mask)
अणु
	स्थिर काष्ठा ide_port_ops *port_ops = drive->hwअगर->port_ops;

	अगर (port_ops && port_ops->maskproc)
		port_ops->maskproc(drive, mask);
पूर्ण

u8 ide_पढ़ो_error(ide_drive_t *drive)
अणु
	काष्ठा ide_taskfile tf;

	drive->hwअगर->tp_ops->tf_पढ़ो(drive, &tf, IDE_VALID_ERROR);

	वापस tf.error;
पूर्ण
EXPORT_SYMBOL_GPL(ide_पढ़ो_error);

व्योम ide_fix_driveid(u16 *id)
अणु
#अगर_अघोषित __LITTLE_ENDIAN
# अगरdef __BIG_ENDIAN
	पूर्णांक i;

	क्रम (i = 0; i < 256; i++)
		id[i] = __le16_to_cpu(id[i]);
# अन्यथा
#  error "Please fix <asm/byteorder.h>"
# endअगर
#पूर्ण_अगर
पूर्ण

/*
 * ide_fixstring() cleans up and (optionally) byte-swaps a text string,
 * removing leading/trailing blanks and compressing पूर्णांकernal blanks.
 * It is primarily used to tidy up the model name/number fields as
 * वापसed by the ATA_CMD_ID_ATA[PI] commands.
 */

व्योम ide_fixstring(u8 *s, स्थिर पूर्णांक bytecount, स्थिर पूर्णांक byteswap)
अणु
	u8 *p, *end = &s[bytecount & ~1]; /* bytecount must be even */

	अगर (byteswap) अणु
		/* convert from big-endian to host byte order */
		क्रम (p = s ; p != end ; p += 2)
			be16_to_cpus((u16 *) p);
	पूर्ण

	/* strip leading blanks */
	p = s;
	जबतक (s != end && *s == ' ')
		++s;
	/* compress पूर्णांकernal blanks and strip trailing blanks */
	जबतक (s != end && *s) अणु
		अगर (*s++ != ' ' || (s != end && *s && *s != ' '))
			*p++ = *(s-1);
	पूर्ण
	/* wipe out trailing garbage */
	जबतक (p != end)
		*p++ = '\0';
पूर्ण
EXPORT_SYMBOL(ide_fixstring);

/*
 * This routine busy-रुकोs क्रम the drive status to be not "busy".
 * It then checks the status क्रम all of the "good" bits and none
 * of the "bad" bits, and अगर all is okay it वापसs 0.  All other
 * हालs वापस error -- caller may then invoke ide_error().
 *
 * This routine should get fixed to not hog the cpu during extra दीर्घ रुकोs..
 * That could be करोne by busy-रुकोing क्रम the first jअगरfy or two, and then
 * setting a समयr to wake up at half second पूर्णांकervals thereafter,
 * until समयout is achieved, beक्रमe timing out.
 */
पूर्णांक __ide_रुको_stat(ide_drive_t *drive, u8 good, u8 bad,
		    अचिन्हित दीर्घ समयout, u8 *rstat)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	स्थिर काष्ठा ide_tp_ops *tp_ops = hwअगर->tp_ops;
	अचिन्हित दीर्घ flags;
	bool irqs_thपढ़ोed = क्रमce_irqthपढ़ोs;
	पूर्णांक i;
	u8 stat;

	udelay(1);	/* spec allows drive 400ns to निश्चित "BUSY" */
	stat = tp_ops->पढ़ो_status(hwअगर);

	अगर (stat & ATA_BUSY) अणु
		अगर (!irqs_thपढ़ोed) अणु
			local_save_flags(flags);
			local_irq_enable_in_hardirq();
		पूर्ण
		समयout += jअगरfies;
		जबतक ((stat = tp_ops->पढ़ो_status(hwअगर)) & ATA_BUSY) अणु
			अगर (समय_after(jअगरfies, समयout)) अणु
				/*
				 * One last पढ़ो after the समयout in हाल
				 * heavy पूर्णांकerrupt load made us not make any
				 * progress during the समयout..
				 */
				stat = tp_ops->पढ़ो_status(hwअगर);
				अगर ((stat & ATA_BUSY) == 0)
					अवरोध;

				अगर (!irqs_thपढ़ोed)
					local_irq_restore(flags);
				*rstat = stat;
				वापस -EBUSY;
			पूर्ण
		पूर्ण
		अगर (!irqs_thपढ़ोed)
			local_irq_restore(flags);
	पूर्ण
	/*
	 * Allow status to settle, then पढ़ो it again.
	 * A few rare drives vastly violate the 400ns spec here,
	 * so we'll रुको up to 10usec क्रम a "good" status
	 * rather than expensively fail things immediately.
	 * This fix courtesy of Matthew Faupel & Niccolo Rigacci.
	 */
	क्रम (i = 0; i < 10; i++) अणु
		udelay(1);
		stat = tp_ops->पढ़ो_status(hwअगर);

		अगर (OK_STAT(stat, good, bad)) अणु
			*rstat = stat;
			वापस 0;
		पूर्ण
	पूर्ण
	*rstat = stat;
	वापस -EFAULT;
पूर्ण

/*
 * In हाल of error वापसs error value after करोing "*startstop = ide_error()".
 * The caller should वापस the updated value of "startstop" in this हाल,
 * "startstop" is unchanged when the function वापसs 0.
 */
पूर्णांक ide_रुको_stat(ide_startstop_t *startstop, ide_drive_t *drive, u8 good,
		  u8 bad, अचिन्हित दीर्घ समयout)
अणु
	पूर्णांक err;
	u8 stat;

	/* bail early अगर we've exceeded max_failures */
	अगर (drive->max_failures && (drive->failures > drive->max_failures)) अणु
		*startstop = ide_stopped;
		वापस 1;
	पूर्ण

	err = __ide_रुको_stat(drive, good, bad, समयout, &stat);

	अगर (err) अणु
		अक्षर *s = (err == -EBUSY) ? "status timeout" : "status error";
		*startstop = ide_error(drive, s, stat);
	पूर्ण

	वापस err;
पूर्ण
EXPORT_SYMBOL(ide_रुको_stat);

/**
 *	ide_in_drive_list	-	look क्रम drive in black/white list
 *	@id: drive identअगरier
 *	@table: list to inspect
 *
 *	Look क्रम a drive in the blacklist and the whitelist tables
 *	Returns 1 अगर the drive is found in the table.
 */

पूर्णांक ide_in_drive_list(u16 *id, स्थिर काष्ठा drive_list_entry *table)
अणु
	क्रम ( ; table->id_model; table++)
		अगर ((!म_भेद(table->id_model, (अक्षर *)&id[ATA_ID_PROD])) &&
		    (!table->id_firmware ||
		     म_माला((अक्षर *)&id[ATA_ID_FW_REV], table->id_firmware)))
			वापस 1;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ide_in_drive_list);

/*
 * Early UDMA66 devices करोn't set bit14 to 1, only bit13 is valid.
 * Some optical devices with the buggy firmwares have the same problem.
 */
अटल स्थिर काष्ठा drive_list_entry ivb_list[] = अणु
	अणु "QUANTUM FIREBALLlct10 05"	, "A03.0900"	पूर्ण,
	अणु "QUANTUM FIREBALLlct20 30"	, "APL.0900"	पूर्ण,
	अणु "TSSTcorp CDDVDW SH-S202J"	, "SB00"	पूर्ण,
	अणु "TSSTcorp CDDVDW SH-S202J"	, "SB01"	पूर्ण,
	अणु "TSSTcorp CDDVDW SH-S202N"	, "SB00"	पूर्ण,
	अणु "TSSTcorp CDDVDW SH-S202N"	, "SB01"	पूर्ण,
	अणु "TSSTcorp CDDVDW SH-S202H"	, "SB00"	पूर्ण,
	अणु "TSSTcorp CDDVDW SH-S202H"	, "SB01"	पूर्ण,
	अणु "SAMSUNG SP0822N"		, "WA100-10"	पूर्ण,
	अणु शून्य				, शून्य		पूर्ण
पूर्ण;

/*
 *  All hosts that use the 80c ribbon must use!
 *  The name is derived from upper byte of word 93 and the 80c ribbon.
 */
u8 eighty_nपूर्णांकy_three(ide_drive_t *drive)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	u16 *id = drive->id;
	पूर्णांक ivb = ide_in_drive_list(id, ivb_list);

	अगर (hwअगर->cbl == ATA_CBL_SATA || hwअगर->cbl == ATA_CBL_PATA40_SHORT)
		वापस 1;

	अगर (ivb)
		prपूर्णांकk(KERN_DEBUG "%s: skipping word 93 validity check\n",
				  drive->name);

	अगर (ata_id_is_sata(id) && !ivb)
		वापस 1;

	अगर (hwअगर->cbl != ATA_CBL_PATA80 && !ivb)
		जाओ no_80w;

	/*
	 * FIXME:
	 * - change master/slave IDENTIFY order
	 * - क्रमce bit13 (80c cable present) check also क्रम !ivb devices
	 *   (unless the slave device is pre-ATA3)
	 */
	अगर (id[ATA_ID_HW_CONFIG] & 0x4000)
		वापस 1;

	अगर (ivb) अणु
		स्थिर अक्षर *model = (अक्षर *)&id[ATA_ID_PROD];

		अगर (म_माला(model, "TSSTcorp CDDVDW SH-S202")) अणु
			/*
			 * These ATAPI devices always report 80c cable
			 * so we have to depend on the host in this हाल.
			 */
			अगर (hwअगर->cbl == ATA_CBL_PATA80)
				वापस 1;
		पूर्ण अन्यथा अणु
			/* Depend on the device side cable detection. */
			अगर (id[ATA_ID_HW_CONFIG] & 0x2000)
				वापस 1;
		पूर्ण
	पूर्ण
no_80w:
	अगर (drive->dev_flags & IDE_DFLAG_UDMA33_WARNED)
		वापस 0;

	prपूर्णांकk(KERN_WARNING "%s: %s side 80-wire cable detection failed, "
			    "limiting max speed to UDMA33\n",
			    drive->name,
			    hwअगर->cbl == ATA_CBL_PATA80 ? "drive" : "host");

	drive->dev_flags |= IDE_DFLAG_UDMA33_WARNED;

	वापस 0;
पूर्ण

अटल स्थिर अक्षर *nien_quirk_list[] = अणु
	"QUANTUM FIREBALLlct08 08",
	"QUANTUM FIREBALLP KA6.4",
	"QUANTUM FIREBALLP KA9.1",
	"QUANTUM FIREBALLP KX13.6",
	"QUANTUM FIREBALLP KX20.5",
	"QUANTUM FIREBALLP KX27.3",
	"QUANTUM FIREBALLP LM20.4",
	"QUANTUM FIREBALLP LM20.5",
	"FUJITSU MHZ2160BH G2",
	शून्य
पूर्ण;

व्योम ide_check_nien_quirk_list(ide_drive_t *drive)
अणु
	स्थिर अक्षर **list, *m = (अक्षर *)&drive->id[ATA_ID_PROD];

	क्रम (list = nien_quirk_list; *list != शून्य; list++)
		अगर (म_माला(m, *list) != शून्य) अणु
			drive->dev_flags |= IDE_DFLAG_NIEN_QUIRK;
			वापस;
		पूर्ण
पूर्ण

पूर्णांक ide_driveid_update(ide_drive_t *drive)
अणु
	u16 *id;
	पूर्णांक rc;

	id = kदो_स्मृति(SECTOR_SIZE, GFP_ATOMIC);
	अगर (id == शून्य)
		वापस 0;

	SELECT_MASK(drive, 1);
	rc = ide_dev_पढ़ो_id(drive, ATA_CMD_ID_ATA, id, 1);
	SELECT_MASK(drive, 0);

	अगर (rc)
		जाओ out_err;

	drive->id[ATA_ID_UDMA_MODES]  = id[ATA_ID_UDMA_MODES];
	drive->id[ATA_ID_MWDMA_MODES] = id[ATA_ID_MWDMA_MODES];
	drive->id[ATA_ID_SWDMA_MODES] = id[ATA_ID_SWDMA_MODES];
	drive->id[ATA_ID_CFA_MODES]   = id[ATA_ID_CFA_MODES];
	/* anything more ? */

	kमुक्त(id);

	वापस 1;
out_err:
	अगर (rc == 2)
		prपूर्णांकk(KERN_ERR "%s: %s: bad status\n", drive->name, __func__);
	kमुक्त(id);
	वापस 0;
पूर्ण

पूर्णांक ide_config_drive_speed(ide_drive_t *drive, u8 speed)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	स्थिर काष्ठा ide_tp_ops *tp_ops = hwअगर->tp_ops;
	काष्ठा ide_taskfile tf;
	u16 *id = drive->id, i;
	पूर्णांक error = 0;
	u8 stat;

#अगर_घोषित CONFIG_BLK_DEV_IDEDMA
	अगर (hwअगर->dma_ops)	/* check अगर host supports DMA */
		hwअगर->dma_ops->dma_host_set(drive, 0);
#पूर्ण_अगर

	/* Skip setting PIO flow-control modes on pre-EIDE drives */
	अगर ((speed & 0xf8) == XFER_PIO_0 && ata_id_has_iordy(drive->id) == 0)
		जाओ skip;

	/*
	 * Don't use ide_रुको_cmd here - it will
	 * attempt to set_geometry and recalibrate,
	 * but क्रम some reason these करोn't work at
	 * this poपूर्णांक (lost पूर्णांकerrupt).
	 */

	udelay(1);
	tp_ops->dev_select(drive);
	SELECT_MASK(drive, 1);
	udelay(1);
	tp_ops->ग_लिखो_devctl(hwअगर, ATA_NIEN | ATA_DEVCTL_OBS);

	स_रखो(&tf, 0, माप(tf));
	tf.feature = SETFEATURES_XFER;
	tf.nsect   = speed;

	tp_ops->tf_load(drive, &tf, IDE_VALID_FEATURE | IDE_VALID_NSECT);

	tp_ops->exec_command(hwअगर, ATA_CMD_SET_FEATURES);

	अगर (drive->dev_flags & IDE_DFLAG_NIEN_QUIRK)
		tp_ops->ग_लिखो_devctl(hwअगर, ATA_DEVCTL_OBS);

	error = __ide_रुको_stat(drive, drive->पढ़ोy_stat,
				ATA_BUSY | ATA_DRQ | ATA_ERR,
				WAIT_CMD, &stat);

	SELECT_MASK(drive, 0);

	अगर (error) अणु
		(व्योम) ide_dump_status(drive, "set_drive_speed_status", stat);
		वापस error;
	पूर्ण

	अगर (speed >= XFER_SW_DMA_0) अणु
		id[ATA_ID_UDMA_MODES]  &= ~0xFF00;
		id[ATA_ID_MWDMA_MODES] &= ~0x0700;
		id[ATA_ID_SWDMA_MODES] &= ~0x0700;
		अगर (ata_id_is_cfa(id))
			id[ATA_ID_CFA_MODES] &= ~0x0E00;
	पूर्ण अन्यथा	अगर (ata_id_is_cfa(id))
		id[ATA_ID_CFA_MODES] &= ~0x01C0;

 skip:
#अगर_घोषित CONFIG_BLK_DEV_IDEDMA
	अगर (speed >= XFER_SW_DMA_0 && (drive->dev_flags & IDE_DFLAG_USING_DMA))
		hwअगर->dma_ops->dma_host_set(drive, 1);
	अन्यथा अगर (hwअगर->dma_ops)	/* check अगर host supports DMA */
		ide_dma_off_quietly(drive);
#पूर्ण_अगर

	अगर (speed >= XFER_UDMA_0) अणु
		i = 1 << (speed - XFER_UDMA_0);
		id[ATA_ID_UDMA_MODES] |= (i << 8 | i);
	पूर्ण अन्यथा अगर (ata_id_is_cfa(id) && speed >= XFER_MW_DMA_3) अणु
		i = speed - XFER_MW_DMA_2;
		id[ATA_ID_CFA_MODES] |= i << 9;
	पूर्ण अन्यथा अगर (speed >= XFER_MW_DMA_0) अणु
		i = 1 << (speed - XFER_MW_DMA_0);
		id[ATA_ID_MWDMA_MODES] |= (i << 8 | i);
	पूर्ण अन्यथा अगर (speed >= XFER_SW_DMA_0) अणु
		i = 1 << (speed - XFER_SW_DMA_0);
		id[ATA_ID_SWDMA_MODES] |= (i << 8 | i);
	पूर्ण अन्यथा अगर (ata_id_is_cfa(id) && speed >= XFER_PIO_5) अणु
		i = speed - XFER_PIO_4;
		id[ATA_ID_CFA_MODES] |= i << 6;
	पूर्ण

	अगर (!drive->init_speed)
		drive->init_speed = speed;
	drive->current_speed = speed;
	वापस error;
पूर्ण

/*
 * This should get invoked any समय we निकास the driver to
 * रुको क्रम an पूर्णांकerrupt response from a drive.  handler() poपूर्णांकs
 * at the appropriate code to handle the next पूर्णांकerrupt, and a
 * समयr is started to prevent us from रुकोing क्रमever in हाल
 * something goes wrong (see the ide_समयr_expiry() handler later on).
 *
 * See also ide_execute_command
 */
व्योम __ide_set_handler(ide_drive_t *drive, ide_handler_t *handler,
		       अचिन्हित पूर्णांक समयout)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;

	BUG_ON(hwअगर->handler);
	hwअगर->handler		= handler;
	hwअगर->समयr.expires	= jअगरfies + समयout;
	hwअगर->req_gen_समयr	= hwअगर->req_gen;
	add_समयr(&hwअगर->समयr);
पूर्ण

व्योम ide_set_handler(ide_drive_t *drive, ide_handler_t *handler,
		     अचिन्हित पूर्णांक समयout)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&hwअगर->lock, flags);
	__ide_set_handler(drive, handler, समयout);
	spin_unlock_irqrestore(&hwअगर->lock, flags);
पूर्ण
EXPORT_SYMBOL(ide_set_handler);

/**
 *	ide_execute_command	-	execute an IDE command
 *	@drive: IDE drive to issue the command against
 *	@cmd: command
 *	@handler: handler क्रम next phase
 *	@समयout: समयout क्रम command
 *
 *	Helper function to issue an IDE command. This handles the
 *	atomicity requirements, command timing and ensures that the
 *	handler and IRQ setup करो not race. All IDE command kick off
 *	should go via this function or करो equivalent locking.
 */

व्योम ide_execute_command(ide_drive_t *drive, काष्ठा ide_cmd *cmd,
			 ide_handler_t *handler, अचिन्हित समयout)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&hwअगर->lock, flags);
	अगर ((cmd->protocol != ATAPI_PROT_DMA &&
	     cmd->protocol != ATAPI_PROT_PIO) ||
	    (drive->atapi_flags & IDE_AFLAG_DRQ_INTERRUPT))
		__ide_set_handler(drive, handler, समयout);
	hwअगर->tp_ops->exec_command(hwअगर, cmd->tf.command);
	/*
	 * Drive takes 400nS to respond, we must aव्योम the IRQ being
	 * serviced beक्रमe that.
	 *
	 * FIXME: we could skip this delay with care on non shared devices
	 */
	ndelay(400);
	spin_unlock_irqrestore(&hwअगर->lock, flags);
पूर्ण

/*
 * ide_रुको_not_busy() रुकोs क्रम the currently selected device on the hwअगर
 * to report a non-busy status, see comments in ide_probe_port().
 */
पूर्णांक ide_रुको_not_busy(ide_hwअगर_t *hwअगर, अचिन्हित दीर्घ समयout)
अणु
	u8 stat = 0;

	जबतक (समयout--) अणु
		/*
		 * Turn this पूर्णांकo a schedule() sleep once I'm sure
		 * about locking issues (2.5 work ?).
		 */
		mdelay(1);
		stat = hwअगर->tp_ops->पढ़ो_status(hwअगर);
		अगर ((stat & ATA_BUSY) == 0)
			वापस 0;
		/*
		 * Assume a value of 0xff means nothing is connected to
		 * the पूर्णांकerface and it करोesn't implement the pull-करोwn
		 * resistor on D7.
		 */
		अगर (stat == 0xff)
			वापस -ENODEV;
		touch_nmi_watchकरोg();
	पूर्ण
	वापस -EBUSY;
पूर्ण
