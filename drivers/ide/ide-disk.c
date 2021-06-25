<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Copyright (C) 1994-1998	   Linus Torvalds & authors (see below)
 *  Copyright (C) 1998-2002	   Linux ATA Development
 *				      Andre Hedrick <andre@linux-ide.org>
 *  Copyright (C) 2003		   Red Hat
 *  Copyright (C) 2003-2005, 2007  Bartlomiej Zolnierkiewicz
 */

/*
 *  Mostly written by Mark Lord <mlord@pobox.com>
 *                and Gadi Oxman <gadio@netvision.net.il>
 *                and Andre Hedrick <andre@linux-ide.org>
 *
 * This is the IDE/ATA disk driver, as evolved from hd.c and ide.c.
 */

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
#समावेश <linux/mutex.h>
#समावेश <linux/leds.h>
#समावेश <linux/ide.h>

#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/irq.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/भाग64.h>

#समावेश "ide-disk.h"

अटल स्थिर u8 ide_rw_cmds[] = अणु
	ATA_CMD_READ_MULTI,
	ATA_CMD_WRITE_MULTI,
	ATA_CMD_READ_MULTI_EXT,
	ATA_CMD_WRITE_MULTI_EXT,
	ATA_CMD_PIO_READ,
	ATA_CMD_PIO_WRITE,
	ATA_CMD_PIO_READ_EXT,
	ATA_CMD_PIO_WRITE_EXT,
	ATA_CMD_READ,
	ATA_CMD_WRITE,
	ATA_CMD_READ_EXT,
	ATA_CMD_WRITE_EXT,
पूर्ण;

अटल व्योम ide_tf_set_cmd(ide_drive_t *drive, काष्ठा ide_cmd *cmd, u8 dma)
अणु
	u8 index, lba48, ग_लिखो;

	lba48 = (cmd->tf_flags & IDE_TFLAG_LBA48) ? 2 : 0;
	ग_लिखो = (cmd->tf_flags & IDE_TFLAG_WRITE) ? 1 : 0;

	अगर (dma) अणु
		cmd->protocol = ATA_PROT_DMA;
		index = 8;
	पूर्ण अन्यथा अणु
		cmd->protocol = ATA_PROT_PIO;
		अगर (drive->mult_count) अणु
			cmd->tf_flags |= IDE_TFLAG_MULTI_PIO;
			index = 0;
		पूर्ण अन्यथा
			index = 4;
	पूर्ण

	cmd->tf.command = ide_rw_cmds[index + lba48 + ग_लिखो];
पूर्ण

/*
 * __ide_करो_rw_disk() issues READ and WRITE commands to a disk,
 * using LBA अगर supported, or CHS otherwise, to address sectors.
 */
अटल ide_startstop_t __ide_करो_rw_disk(ide_drive_t *drive, काष्ठा request *rq,
					sector_t block)
अणु
	ide_hwअगर_t *hwअगर	= drive->hwअगर;
	u16 nsectors		= (u16)blk_rq_sectors(rq);
	u8 lba48		= !!(drive->dev_flags & IDE_DFLAG_LBA48);
	u8 dma			= !!(drive->dev_flags & IDE_DFLAG_USING_DMA);
	काष्ठा ide_cmd		cmd;
	काष्ठा ide_taskfile	*tf = &cmd.tf;
	ide_startstop_t		rc;

	अगर ((hwअगर->host_flags & IDE_HFLAG_NO_LBA48_DMA) && lba48 && dma) अणु
		अगर (block + blk_rq_sectors(rq) > 1ULL << 28)
			dma = 0;
		अन्यथा
			lba48 = 0;
	पूर्ण

	स_रखो(&cmd, 0, माप(cmd));
	cmd.valid.out.tf = IDE_VALID_OUT_TF | IDE_VALID_DEVICE;
	cmd.valid.in.tf  = IDE_VALID_IN_TF  | IDE_VALID_DEVICE;

	अगर (drive->dev_flags & IDE_DFLAG_LBA) अणु
		अगर (lba48) अणु
			pr_debug("%s: LBA=0x%012llx\n", drive->name,
					(अचिन्हित दीर्घ दीर्घ)block);

			tf->nsect  = nsectors & 0xff;
			tf->lbal   = (u8) block;
			tf->lbam   = (u8)(block >>  8);
			tf->lbah   = (u8)(block >> 16);
			tf->device = ATA_LBA;

			tf = &cmd.hob;
			tf->nsect = (nsectors >> 8) & 0xff;
			tf->lbal  = (u8)(block >> 24);
			अगर (माप(block) != 4) अणु
				tf->lbam = (u8)((u64)block >> 32);
				tf->lbah = (u8)((u64)block >> 40);
			पूर्ण

			cmd.valid.out.hob = IDE_VALID_OUT_HOB;
			cmd.valid.in.hob  = IDE_VALID_IN_HOB;
			cmd.tf_flags |= IDE_TFLAG_LBA48;
		पूर्ण अन्यथा अणु
			tf->nsect  = nsectors & 0xff;
			tf->lbal   = block;
			tf->lbam   = block >>= 8;
			tf->lbah   = block >>= 8;
			tf->device = ((block >> 8) & 0xf) | ATA_LBA;
		पूर्ण
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक sect, head, cyl, track;

		track = (पूर्णांक)block / drive->sect;
		sect  = (पूर्णांक)block % drive->sect + 1;
		head  = track % drive->head;
		cyl   = track / drive->head;

		pr_debug("%s: CHS=%u/%u/%u\n", drive->name, cyl, head, sect);

		tf->nsect  = nsectors & 0xff;
		tf->lbal   = sect;
		tf->lbam   = cyl;
		tf->lbah   = cyl >> 8;
		tf->device = head;
	पूर्ण

	cmd.tf_flags |= IDE_TFLAG_FS;

	अगर (rq_data_dir(rq))
		cmd.tf_flags |= IDE_TFLAG_WRITE;

	ide_tf_set_cmd(drive, &cmd, dma);
	cmd.rq = rq;

	अगर (dma == 0) अणु
		ide_init_sg_cmd(&cmd, nsectors << 9);
		ide_map_sg(drive, &cmd);
	पूर्ण

	rc = करो_rw_taskfile(drive, &cmd);

	अगर (rc == ide_stopped && dma) अणु
		/* fallback to PIO */
		cmd.tf_flags |= IDE_TFLAG_DMA_PIO_FALLBACK;
		ide_tf_set_cmd(drive, &cmd, 0);
		ide_init_sg_cmd(&cmd, nsectors << 9);
		rc = करो_rw_taskfile(drive, &cmd);
	पूर्ण

	वापस rc;
पूर्ण

/*
 * 268435455  == 137439 MB or 28bit limit
 * 320173056  == 163929 MB or 48bit addressing
 * 1073741822 == 549756 MB or 48bit addressing fake drive
 */

अटल ide_startstop_t ide_करो_rw_disk(ide_drive_t *drive, काष्ठा request *rq,
				      sector_t block)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;

	BUG_ON(drive->dev_flags & IDE_DFLAG_BLOCKED);
	BUG_ON(blk_rq_is_passthrough(rq));

	ledtrig_disk_activity(rq_data_dir(rq) == WRITE);

	pr_debug("%s: %sing: block=%llu, sectors=%u\n",
		 drive->name, rq_data_dir(rq) == READ ? "read" : "writ",
		 (अचिन्हित दीर्घ दीर्घ)block, blk_rq_sectors(rq));

	अगर (hwअगर->rw_disk)
		hwअगर->rw_disk(drive, rq);

	वापस __ide_करो_rw_disk(drive, rq, block);
पूर्ण

/*
 * Queries क्रम true maximum capacity of the drive.
 * Returns maximum LBA address (> 0) of the drive, 0 अगर failed.
 */
अटल u64 idedisk_पढ़ो_native_max_address(ide_drive_t *drive, पूर्णांक lba48)
अणु
	काष्ठा ide_cmd cmd;
	काष्ठा ide_taskfile *tf = &cmd.tf;
	u64 addr = 0;

	स_रखो(&cmd, 0, माप(cmd));
	अगर (lba48)
		tf->command = ATA_CMD_READ_NATIVE_MAX_EXT;
	अन्यथा
		tf->command = ATA_CMD_READ_NATIVE_MAX;
	tf->device  = ATA_LBA;

	cmd.valid.out.tf = IDE_VALID_OUT_TF | IDE_VALID_DEVICE;
	cmd.valid.in.tf  = IDE_VALID_IN_TF  | IDE_VALID_DEVICE;
	अगर (lba48) अणु
		cmd.valid.out.hob = IDE_VALID_OUT_HOB;
		cmd.valid.in.hob  = IDE_VALID_IN_HOB;
		cmd.tf_flags = IDE_TFLAG_LBA48;
	पूर्ण

	ide_no_data_taskfile(drive, &cmd);

	/* अगर OK, compute maximum address value */
	अगर (!(tf->status & ATA_ERR))
		addr = ide_get_lba_addr(&cmd, lba48) + 1;

	वापस addr;
पूर्ण

/*
 * Sets maximum भव LBA address of the drive.
 * Returns new maximum भव LBA address (> 0) or 0 on failure.
 */
अटल u64 idedisk_set_max_address(ide_drive_t *drive, u64 addr_req, पूर्णांक lba48)
अणु
	काष्ठा ide_cmd cmd;
	काष्ठा ide_taskfile *tf = &cmd.tf;
	u64 addr_set = 0;

	addr_req--;

	स_रखो(&cmd, 0, माप(cmd));
	tf->lbal     = (addr_req >>  0) & 0xff;
	tf->lbam     = (addr_req >>= 8) & 0xff;
	tf->lbah     = (addr_req >>= 8) & 0xff;
	अगर (lba48) अणु
		cmd.hob.lbal = (addr_req >>= 8) & 0xff;
		cmd.hob.lbam = (addr_req >>= 8) & 0xff;
		cmd.hob.lbah = (addr_req >>= 8) & 0xff;
		tf->command  = ATA_CMD_SET_MAX_EXT;
	पूर्ण अन्यथा अणु
		tf->device   = (addr_req >>= 8) & 0x0f;
		tf->command  = ATA_CMD_SET_MAX;
	पूर्ण
	tf->device |= ATA_LBA;

	cmd.valid.out.tf = IDE_VALID_OUT_TF | IDE_VALID_DEVICE;
	cmd.valid.in.tf  = IDE_VALID_IN_TF  | IDE_VALID_DEVICE;
	अगर (lba48) अणु
		cmd.valid.out.hob = IDE_VALID_OUT_HOB;
		cmd.valid.in.hob  = IDE_VALID_IN_HOB;
		cmd.tf_flags = IDE_TFLAG_LBA48;
	पूर्ण

	ide_no_data_taskfile(drive, &cmd);

	/* अगर OK, compute maximum address value */
	अगर (!(tf->status & ATA_ERR))
		addr_set = ide_get_lba_addr(&cmd, lba48) + 1;

	वापस addr_set;
पूर्ण

अटल अचिन्हित दीर्घ दीर्घ sectors_to_MB(अचिन्हित दीर्घ दीर्घ n)
अणु
	n <<= 9;		/* make it bytes */
	करो_भाग(n, 1000000);	/* make it MB */
	वापस n;
पूर्ण

/*
 * Some disks report total number of sectors instead of
 * maximum sector address.  We list them here.
 */
अटल स्थिर काष्ठा drive_list_entry hpa_list[] = अणु
	अणु "ST340823A",	शून्य पूर्ण,
	अणु "ST320413A",	शून्य पूर्ण,
	अणु "ST310211A",	शून्य पूर्ण,
	अणु शून्य,		शून्य पूर्ण
पूर्ण;

अटल u64 ide_disk_hpa_get_native_capacity(ide_drive_t *drive, पूर्णांक lba48)
अणु
	u64 capacity, set_max;

	capacity = drive->capacity64;
	set_max  = idedisk_पढ़ो_native_max_address(drive, lba48);

	अगर (ide_in_drive_list(drive->id, hpa_list)) अणु
		/*
		 * Since we are inclusive wrt to firmware revisions करो this
		 * extra check and apply the workaround only when needed.
		 */
		अगर (set_max == capacity + 1)
			set_max--;
	पूर्ण

	वापस set_max;
पूर्ण

अटल u64 ide_disk_hpa_set_capacity(ide_drive_t *drive, u64 set_max, पूर्णांक lba48)
अणु
	set_max = idedisk_set_max_address(drive, set_max, lba48);
	अगर (set_max)
		drive->capacity64 = set_max;

	वापस set_max;
पूर्ण

अटल व्योम idedisk_check_hpa(ide_drive_t *drive)
अणु
	u64 capacity, set_max;
	पूर्णांक lba48 = ata_id_lba48_enabled(drive->id);

	capacity = drive->capacity64;
	set_max  = ide_disk_hpa_get_native_capacity(drive, lba48);

	अगर (set_max <= capacity)
		वापस;

	drive->probed_capacity = set_max;

	prपूर्णांकk(KERN_INFO "%s: Host Protected Area detected.\n"
			 "\tcurrent capacity is %llu sectors (%llu MB)\n"
			 "\tnative  capacity is %llu sectors (%llu MB)\n",
			 drive->name,
			 capacity, sectors_to_MB(capacity),
			 set_max, sectors_to_MB(set_max));

	अगर ((drive->dev_flags & IDE_DFLAG_NOHPA) == 0)
		वापस;

	set_max = ide_disk_hpa_set_capacity(drive, set_max, lba48);
	अगर (set_max)
		prपूर्णांकk(KERN_INFO "%s: Host Protected Area disabled.\n",
				 drive->name);
पूर्ण

अटल पूर्णांक ide_disk_get_capacity(ide_drive_t *drive)
अणु
	u16 *id = drive->id;
	पूर्णांक lba;

	अगर (ata_id_lba48_enabled(id)) अणु
		/* drive speaks 48-bit LBA */
		lba = 1;
		drive->capacity64 = ata_id_u64(id, ATA_ID_LBA_CAPACITY_2);
	पूर्ण अन्यथा अगर (ata_id_has_lba(id) && ata_id_is_lba_capacity_ok(id)) अणु
		/* drive speaks 28-bit LBA */
		lba = 1;
		drive->capacity64 = ata_id_u32(id, ATA_ID_LBA_CAPACITY);
	पूर्ण अन्यथा अणु
		/* drive speaks boring old 28-bit CHS */
		lba = 0;
		drive->capacity64 = drive->cyl * drive->head * drive->sect;
	पूर्ण

	drive->probed_capacity = drive->capacity64;

	अगर (lba) अणु
		drive->dev_flags |= IDE_DFLAG_LBA;

		/*
		* If this device supports the Host Protected Area feature set,
		* then we may need to change our opinion about its capacity.
		*/
		अगर (ata_id_hpa_enabled(id))
			idedisk_check_hpa(drive);
	पूर्ण

	/* limit drive capacity to 137GB अगर LBA48 cannot be used */
	अगर ((drive->dev_flags & IDE_DFLAG_LBA48) == 0 &&
	    drive->capacity64 > 1ULL << 28) अणु
		prपूर्णांकk(KERN_WARNING "%s: cannot use LBA48 - full capacity "
		       "%llu sectors (%llu MB)\n",
		       drive->name, (अचिन्हित दीर्घ दीर्घ)drive->capacity64,
		       sectors_to_MB(drive->capacity64));
		drive->probed_capacity = drive->capacity64 = 1ULL << 28;
	पूर्ण

	अगर ((drive->hwअगर->host_flags & IDE_HFLAG_NO_LBA48_DMA) &&
	    (drive->dev_flags & IDE_DFLAG_LBA48)) अणु
		अगर (drive->capacity64 > 1ULL << 28) अणु
			prपूर्णांकk(KERN_INFO "%s: cannot use LBA48 DMA - PIO mode"
					 " will be used for accessing sectors "
					 "> %u\n", drive->name, 1 << 28);
		पूर्ण अन्यथा
			drive->dev_flags &= ~IDE_DFLAG_LBA48;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ide_disk_unlock_native_capacity(ide_drive_t *drive)
अणु
	u16 *id = drive->id;
	पूर्णांक lba48 = ata_id_lba48_enabled(id);

	अगर ((drive->dev_flags & IDE_DFLAG_LBA) == 0 ||
	    ata_id_hpa_enabled(id) == 0)
		वापस;

	/*
	 * according to the spec the SET MAX ADDRESS command shall be
	 * immediately preceded by a READ NATIVE MAX ADDRESS command
	 */
	अगर (!ide_disk_hpa_get_native_capacity(drive, lba48))
		वापस;

	अगर (ide_disk_hpa_set_capacity(drive, drive->probed_capacity, lba48))
		drive->dev_flags |= IDE_DFLAG_NOHPA; /* disable HPA on resume */
पूर्ण

अटल bool idedisk_prep_rq(ide_drive_t *drive, काष्ठा request *rq)
अणु
	काष्ठा ide_cmd *cmd;

	अगर (req_op(rq) != REQ_OP_FLUSH)
		वापस true;

	अगर (ide_req(rq)->special) अणु
		cmd = ide_req(rq)->special;
		स_रखो(cmd, 0, माप(*cmd));
	पूर्ण अन्यथा अणु
		cmd = kzalloc(माप(*cmd), GFP_ATOMIC);
	पूर्ण

	/* FIXME: map काष्ठा ide_taskfile on rq->cmd[] */
	BUG_ON(cmd == शून्य);

	अगर (ata_id_flush_ext_enabled(drive->id) &&
	    (drive->capacity64 >= (1UL << 28)))
		cmd->tf.command = ATA_CMD_FLUSH_EXT;
	अन्यथा
		cmd->tf.command = ATA_CMD_FLUSH;
	cmd->valid.out.tf = IDE_VALID_OUT_TF | IDE_VALID_DEVICE;
	cmd->tf_flags = IDE_TFLAG_DYN;
	cmd->protocol = ATA_PROT_NODATA;
	rq->cmd_flags &= ~REQ_OP_MASK;
	rq->cmd_flags |= REQ_OP_DRV_OUT;
	ide_req(rq)->type = ATA_PRIV_TASKखाता;
	ide_req(rq)->special = cmd;
	cmd->rq = rq;

	वापस true;
पूर्ण

ide_devset_get(multcount, mult_count);

/*
 * This is tightly woven पूर्णांकo the driver->करो_special can not touch.
 * DON'T करो it again until a total personality reग_लिखो is committed.
 */
अटल पूर्णांक set_multcount(ide_drive_t *drive, पूर्णांक arg)
अणु
	काष्ठा request *rq;

	अगर (arg < 0 || arg > (drive->id[ATA_ID_MAX_MULTSECT] & 0xff))
		वापस -EINVAL;

	अगर (drive->special_flags & IDE_SFLAG_SET_MULTMODE)
		वापस -EBUSY;

	rq = blk_get_request(drive->queue, REQ_OP_DRV_IN, 0);
	ide_req(rq)->type = ATA_PRIV_TASKखाता;

	drive->mult_req = arg;
	drive->special_flags |= IDE_SFLAG_SET_MULTMODE;
	blk_execute_rq(शून्य, rq, 0);
	blk_put_request(rq);

	वापस (drive->mult_count == arg) ? 0 : -EIO;
पूर्ण

ide_devset_get_flag(nowerr, IDE_DFLAG_NOWERR);

अटल पूर्णांक set_nowerr(ide_drive_t *drive, पूर्णांक arg)
अणु
	अगर (arg < 0 || arg > 1)
		वापस -EINVAL;

	अगर (arg)
		drive->dev_flags |= IDE_DFLAG_NOWERR;
	अन्यथा
		drive->dev_flags &= ~IDE_DFLAG_NOWERR;

	drive->bad_wstat = arg ? BAD_R_STAT : BAD_W_STAT;

	वापस 0;
पूर्ण

अटल पूर्णांक ide_करो_setfeature(ide_drive_t *drive, u8 feature, u8 nsect)
अणु
	काष्ठा ide_cmd cmd;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.tf.feature = feature;
	cmd.tf.nsect   = nsect;
	cmd.tf.command = ATA_CMD_SET_FEATURES;
	cmd.valid.out.tf = IDE_VALID_OUT_TF | IDE_VALID_DEVICE;
	cmd.valid.in.tf  = IDE_VALID_IN_TF  | IDE_VALID_DEVICE;

	वापस ide_no_data_taskfile(drive, &cmd);
पूर्ण

अटल व्योम update_flush(ide_drive_t *drive)
अणु
	u16 *id = drive->id;
	bool wc = false;

	अगर (drive->dev_flags & IDE_DFLAG_WCACHE) अणु
		अचिन्हित दीर्घ दीर्घ capacity;
		पूर्णांक barrier;
		/*
		 * We must aव्योम issuing commands a drive करोes not
		 * understand or we may crash it. We check flush cache
		 * is supported. We also check we have the LBA48 flush
		 * cache अगर the drive capacity is too large. By this
		 * समय we have trimmed the drive capacity अगर LBA48 is
		 * not available so we करोn't need to recheck that.
		 */
		capacity = ide_gd_capacity(drive);
		barrier = ata_id_flush_enabled(id) &&
			(drive->dev_flags & IDE_DFLAG_NOFLUSH) == 0 &&
			((drive->dev_flags & IDE_DFLAG_LBA48) == 0 ||
			 capacity <= (1ULL << 28) ||
			 ata_id_flush_ext_enabled(id));

		prपूर्णांकk(KERN_INFO "%s: cache flushes %ssupported\n",
		       drive->name, barrier ? "" : "not ");

		अगर (barrier) अणु
			wc = true;
			drive->prep_rq = idedisk_prep_rq;
		पूर्ण
	पूर्ण

	blk_queue_ग_लिखो_cache(drive->queue, wc, false);
पूर्ण

ide_devset_get_flag(wcache, IDE_DFLAG_WCACHE);

अटल पूर्णांक set_wcache(ide_drive_t *drive, पूर्णांक arg)
अणु
	पूर्णांक err = 1;

	अगर (arg < 0 || arg > 1)
		वापस -EINVAL;

	अगर (ata_id_flush_enabled(drive->id)) अणु
		err = ide_करो_setfeature(drive,
			arg ? SETFEATURES_WC_ON : SETFEATURES_WC_OFF, 0);
		अगर (err == 0) अणु
			अगर (arg)
				drive->dev_flags |= IDE_DFLAG_WCACHE;
			अन्यथा
				drive->dev_flags &= ~IDE_DFLAG_WCACHE;
		पूर्ण
	पूर्ण

	update_flush(drive);

	वापस err;
पूर्ण

अटल पूर्णांक करो_idedisk_flushcache(ide_drive_t *drive)
अणु
	काष्ठा ide_cmd cmd;

	स_रखो(&cmd, 0, माप(cmd));
	अगर (ata_id_flush_ext_enabled(drive->id))
		cmd.tf.command = ATA_CMD_FLUSH_EXT;
	अन्यथा
		cmd.tf.command = ATA_CMD_FLUSH;
	cmd.valid.out.tf = IDE_VALID_OUT_TF | IDE_VALID_DEVICE;
	cmd.valid.in.tf  = IDE_VALID_IN_TF  | IDE_VALID_DEVICE;

	वापस ide_no_data_taskfile(drive, &cmd);
पूर्ण

ide_devset_get(acoustic, acoustic);

अटल पूर्णांक set_acoustic(ide_drive_t *drive, पूर्णांक arg)
अणु
	अगर (arg < 0 || arg > 254)
		वापस -EINVAL;

	ide_करो_setfeature(drive,
		arg ? SETFEATURES_AAM_ON : SETFEATURES_AAM_OFF, arg);

	drive->acoustic = arg;

	वापस 0;
पूर्ण

ide_devset_get_flag(addressing, IDE_DFLAG_LBA48);

/*
 * drive->addressing:
 *	0: 28-bit
 *	1: 48-bit
 *	2: 48-bit capable करोing 28-bit
 */
अटल पूर्णांक set_addressing(ide_drive_t *drive, पूर्णांक arg)
अणु
	अगर (arg < 0 || arg > 2)
		वापस -EINVAL;

	अगर (arg && ((drive->hwअगर->host_flags & IDE_HFLAG_NO_LBA48) ||
	    ata_id_lba48_enabled(drive->id) == 0))
		वापस -EIO;

	अगर (arg == 2)
		arg = 0;

	अगर (arg)
		drive->dev_flags |= IDE_DFLAG_LBA48;
	अन्यथा
		drive->dev_flags &= ~IDE_DFLAG_LBA48;

	वापस 0;
पूर्ण

ide_ext_devset_rw(acoustic, acoustic);
ide_ext_devset_rw(address, addressing);
ide_ext_devset_rw(multcount, multcount);
ide_ext_devset_rw(wcache, wcache);

ide_ext_devset_rw_sync(nowerr, nowerr);

अटल पूर्णांक ide_disk_check(ide_drive_t *drive, स्थिर अक्षर *s)
अणु
	वापस 1;
पूर्ण

अटल व्योम ide_disk_setup(ide_drive_t *drive)
अणु
	काष्ठा ide_disk_obj *idkp = drive->driver_data;
	काष्ठा request_queue *q = drive->queue;
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	u16 *id = drive->id;
	अक्षर *m = (अक्षर *)&id[ATA_ID_PROD];
	अचिन्हित दीर्घ दीर्घ capacity;

	ide_proc_रेजिस्टर_driver(drive, idkp->driver);

	अगर ((drive->dev_flags & IDE_DFLAG_ID_READ) == 0)
		वापस;

	अगर (drive->dev_flags & IDE_DFLAG_REMOVABLE) अणु
		/*
		 * Removable disks (eg. SYQUEST); ignore 'WD' drives
		 */
		अगर (m[0] != 'W' || m[1] != 'D')
			drive->dev_flags |= IDE_DFLAG_DOORLOCKING;
	पूर्ण

	(व्योम)set_addressing(drive, 1);

	अगर (drive->dev_flags & IDE_DFLAG_LBA48) अणु
		पूर्णांक max_s = 2048;

		अगर (max_s > hwअगर->rqsize)
			max_s = hwअगर->rqsize;

		blk_queue_max_hw_sectors(q, max_s);
	पूर्ण

	prपूर्णांकk(KERN_INFO "%s: max request size: %dKiB\n", drive->name,
	       queue_max_sectors(q) / 2);

	अगर (ata_id_is_ssd(id)) अणु
		blk_queue_flag_set(QUEUE_FLAG_NONROT, q);
		blk_queue_flag_clear(QUEUE_FLAG_ADD_RANDOM, q);
	पूर्ण

	/* calculate drive capacity, and select LBA अगर possible */
	ide_disk_get_capacity(drive);

	/*
	 * अगर possible, give fdisk access to more of the drive,
	 * by correcting bios_cyls:
	 */
	capacity = ide_gd_capacity(drive);

	अगर ((drive->dev_flags & IDE_DFLAG_FORCED_GEOM) == 0) अणु
		अगर (ata_id_lba48_enabled(drive->id)) अणु
			/* compatibility */
			drive->bios_sect = 63;
			drive->bios_head = 255;
		पूर्ण

		अगर (drive->bios_sect && drive->bios_head) अणु
			अचिन्हित पूर्णांक cap0 = capacity; /* truncate to 32 bits */
			अचिन्हित पूर्णांक cylsz, cyl;

			अगर (cap0 != capacity)
				drive->bios_cyl = 65535;
			अन्यथा अणु
				cylsz = drive->bios_sect * drive->bios_head;
				cyl = cap0 / cylsz;
				अगर (cyl > 65535)
					cyl = 65535;
				अगर (cyl > drive->bios_cyl)
					drive->bios_cyl = cyl;
			पूर्ण
		पूर्ण
	पूर्ण
	prपूर्णांकk(KERN_INFO "%s: %llu sectors (%llu MB)",
			 drive->name, capacity, sectors_to_MB(capacity));

	/* Only prपूर्णांक cache size when it was specअगरied */
	अगर (id[ATA_ID_BUF_SIZE])
		prपूर्णांकk(KERN_CONT " w/%dKiB Cache", id[ATA_ID_BUF_SIZE] / 2);

	prपूर्णांकk(KERN_CONT ", CHS=%d/%d/%d\n",
			 drive->bios_cyl, drive->bios_head, drive->bios_sect);

	/* ग_लिखो cache enabled? */
	अगर ((id[ATA_ID_CSFO] & 1) || ata_id_wcache_enabled(id))
		drive->dev_flags |= IDE_DFLAG_WCACHE;

	set_wcache(drive, 1);

	अगर ((drive->dev_flags & IDE_DFLAG_LBA) == 0 &&
	    (drive->head == 0 || drive->head > 16))
		prपूर्णांकk(KERN_ERR "%s: invalid geometry: %d physical heads?\n",
			drive->name, drive->head);
पूर्ण

अटल व्योम ide_disk_flush(ide_drive_t *drive)
अणु
	अगर (ata_id_flush_enabled(drive->id) == 0 ||
	    (drive->dev_flags & IDE_DFLAG_WCACHE) == 0)
		वापस;

	अगर (करो_idedisk_flushcache(drive))
		prपूर्णांकk(KERN_INFO "%s: wcache flush failed!\n", drive->name);
पूर्ण

अटल पूर्णांक ide_disk_init_media(ide_drive_t *drive, काष्ठा gendisk *disk)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक ide_disk_set_करोorlock(ide_drive_t *drive, काष्ठा gendisk *disk,
				 पूर्णांक on)
अणु
	काष्ठा ide_cmd cmd;
	पूर्णांक ret;

	अगर ((drive->dev_flags & IDE_DFLAG_DOORLOCKING) == 0)
		वापस 0;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.tf.command = on ? ATA_CMD_MEDIA_LOCK : ATA_CMD_MEDIA_UNLOCK;
	cmd.valid.out.tf = IDE_VALID_OUT_TF | IDE_VALID_DEVICE;
	cmd.valid.in.tf  = IDE_VALID_IN_TF  | IDE_VALID_DEVICE;

	ret = ide_no_data_taskfile(drive, &cmd);

	अगर (ret)
		drive->dev_flags &= ~IDE_DFLAG_DOORLOCKING;

	वापस ret;
पूर्ण

स्थिर काष्ठा ide_disk_ops ide_ata_disk_ops = अणु
	.check			= ide_disk_check,
	.unlock_native_capacity	= ide_disk_unlock_native_capacity,
	.get_capacity		= ide_disk_get_capacity,
	.setup			= ide_disk_setup,
	.flush			= ide_disk_flush,
	.init_media		= ide_disk_init_media,
	.set_करोorlock		= ide_disk_set_करोorlock,
	.करो_request		= ide_करो_rw_disk,
	.ioctl			= ide_disk_ioctl,
	.compat_ioctl		= ide_disk_ioctl,
पूर्ण;
