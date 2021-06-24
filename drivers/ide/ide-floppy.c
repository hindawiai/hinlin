<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * IDE ATAPI floppy driver.
 *
 * Copyright (C) 1996-1999  Gadi Oxman <gadio@netvision.net.il>
 * Copyright (C) 2000-2002  Paul Bristow <paul@paulbristow.net>
 * Copyright (C) 2005       Bartlomiej Zolnierkiewicz
 *
 * This driver supports the following IDE floppy drives:
 *
 * LS-120/240 SuperDisk
 * Iomega Zip 100/250
 * Iomega PC Card Clik!/PocketZip
 *
 * For a historical changelog see
 * Documentation/ide/ChangeLog.ide-floppy.1996-2002
 */

#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>
#समावेश <linux/compat.h>
#समावेश <linux/delay.h>
#समावेश <linux/समयr.h>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/major.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/genhd.h>
#समावेश <linux/cdrom.h>
#समावेश <linux/ide.h>
#समावेश <linux/hdreg.h>
#समावेश <linux/bitops.h>
#समावेश <linux/mutex.h>
#समावेश <linux/scatterlist.h>

#समावेश <scsi/scsi_ioctl.h>

#समावेश <यंत्र/byteorder.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/unaligned.h>

#समावेश "ide-floppy.h"

/*
 * After each failed packet command we issue a request sense command and retry
 * the packet command IDEFLOPPY_MAX_PC_RETRIES बार.
 */
#घोषणा IDEFLOPPY_MAX_PC_RETRIES	3

/* क्रमmat capacities descriptor codes */
#घोषणा CAPACITY_INVALID	0x00
#घोषणा CAPACITY_UNFORMATTED	0x01
#घोषणा CAPACITY_CURRENT	0x02
#घोषणा CAPACITY_NO_CARTRIDGE	0x03

/*
 * The following delay solves a problem with ATAPI Zip 100 drive where BSY bit
 * was apparently being deनिश्चितed beक्रमe the unit was पढ़ोy to receive data.
 */
#घोषणा IDEFLOPPY_PC_DELAY	(HZ/20)	/* शेष delay क्रम ZIP 100 (50ms) */

अटल पूर्णांक ide_floppy_callback(ide_drive_t *drive, पूर्णांक dsc)
अणु
	काष्ठा ide_disk_obj *floppy = drive->driver_data;
	काष्ठा ide_atapi_pc *pc = drive->pc;
	काष्ठा request *rq = pc->rq;
	पूर्णांक uptodate = pc->error ? 0 : 1;

	ide_debug_log(IDE_DBG_FUNC, "enter");

	अगर (drive->failed_pc == pc)
		drive->failed_pc = शून्य;

	अगर (pc->c[0] == GPCMD_READ_10 || pc->c[0] == GPCMD_WRITE_10 ||
	    blk_rq_is_scsi(rq))
		uptodate = 1; /* FIXME */
	अन्यथा अगर (pc->c[0] == GPCMD_REQUEST_SENSE) अणु

		u8 *buf = bio_data(rq->bio);

		अगर (!pc->error) अणु
			floppy->sense_key = buf[2] & 0x0F;
			floppy->asc = buf[12];
			floppy->ascq = buf[13];
			floppy->progress_indication = buf[15] & 0x80 ?
				(u16)get_unaligned((u16 *)&buf[16]) : 0x10000;

			अगर (drive->failed_pc)
				ide_debug_log(IDE_DBG_PC, "pc = %x",
					      drive->failed_pc->c[0]);

			ide_debug_log(IDE_DBG_SENSE, "sense key = %x, asc = %x,"
				      "ascq = %x", floppy->sense_key,
				      floppy->asc, floppy->ascq);
		पूर्ण अन्यथा
			prपूर्णांकk(KERN_ERR PFX "Error in REQUEST SENSE itself - "
			       "Aborting request!\n");
	पूर्ण

	अगर (ata_misc_request(rq))
		scsi_req(rq)->result = uptodate ? 0 : IDE_DRV_ERROR_GENERAL;

	वापस uptodate;
पूर्ण

अटल व्योम ide_floppy_report_error(काष्ठा ide_disk_obj *floppy,
				    काष्ठा ide_atapi_pc *pc)
अणु
	/* suppress error messages resulting from Medium not present */
	अगर (floppy->sense_key == 0x02 &&
	    floppy->asc       == 0x3a &&
	    floppy->ascq      == 0x00)
		वापस;

	prपूर्णांकk(KERN_ERR PFX "%s: I/O error, pc = %2x, key = %2x, "
			"asc = %2x, ascq = %2x\n",
			floppy->drive->name, pc->c[0], floppy->sense_key,
			floppy->asc, floppy->ascq);

पूर्ण

अटल ide_startstop_t ide_floppy_issue_pc(ide_drive_t *drive,
					   काष्ठा ide_cmd *cmd,
					   काष्ठा ide_atapi_pc *pc)
अणु
	काष्ठा ide_disk_obj *floppy = drive->driver_data;

	अगर (drive->failed_pc == शून्य &&
	    pc->c[0] != GPCMD_REQUEST_SENSE)
		drive->failed_pc = pc;

	/* Set the current packet command */
	drive->pc = pc;

	अगर (pc->retries > IDEFLOPPY_MAX_PC_RETRIES) अणु
		अचिन्हित पूर्णांक करोne = blk_rq_bytes(drive->hwअगर->rq);

		अगर (!(pc->flags & PC_FLAG_SUPPRESS_ERROR))
			ide_floppy_report_error(floppy, pc);

		/* Giving up */
		pc->error = IDE_DRV_ERROR_GENERAL;

		drive->failed_pc = शून्य;
		drive->pc_callback(drive, 0);
		ide_complete_rq(drive, BLK_STS_IOERR, करोne);
		वापस ide_stopped;
	पूर्ण

	ide_debug_log(IDE_DBG_FUNC, "retry #%d", pc->retries);

	pc->retries++;

	वापस ide_issue_pc(drive, cmd);
पूर्ण

व्योम ide_floppy_create_पढ़ो_capacity_cmd(काष्ठा ide_atapi_pc *pc)
अणु
	ide_init_pc(pc);
	pc->c[0] = GPCMD_READ_FORMAT_CAPACITIES;
	pc->c[7] = 255;
	pc->c[8] = 255;
	pc->req_xfer = 255;
पूर्ण

/* A mode sense command is used to "sense" floppy parameters. */
व्योम ide_floppy_create_mode_sense_cmd(काष्ठा ide_atapi_pc *pc, u8 page_code)
अणु
	u16 length = 8; /* माप(Mode Parameter Header) = 8 Bytes */

	ide_init_pc(pc);
	pc->c[0] = GPCMD_MODE_SENSE_10;
	pc->c[1] = 0;
	pc->c[2] = page_code;

	चयन (page_code) अणु
	हाल IDEFLOPPY_CAPABILITIES_PAGE:
		length += 12;
		अवरोध;
	हाल IDEFLOPPY_FLEXIBLE_DISK_PAGE:
		length += 32;
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR PFX "unsupported page code in %s\n", __func__);
	पूर्ण
	put_unaligned(cpu_to_be16(length), (u16 *) &pc->c[7]);
	pc->req_xfer = length;
पूर्ण

अटल व्योम idefloppy_create_rw_cmd(ide_drive_t *drive,
				    काष्ठा ide_atapi_pc *pc, काष्ठा request *rq,
				    अचिन्हित दीर्घ sector)
अणु
	काष्ठा ide_disk_obj *floppy = drive->driver_data;
	पूर्णांक block = sector / floppy->bs_factor;
	पूर्णांक blocks = blk_rq_sectors(rq) / floppy->bs_factor;
	पूर्णांक cmd = rq_data_dir(rq);

	ide_debug_log(IDE_DBG_FUNC, "block: %d, blocks: %d", block, blocks);

	ide_init_pc(pc);
	pc->c[0] = cmd == READ ? GPCMD_READ_10 : GPCMD_WRITE_10;
	put_unaligned(cpu_to_be16(blocks), (अचिन्हित लघु *)&pc->c[7]);
	put_unaligned(cpu_to_be32(block), (अचिन्हित पूर्णांक *) &pc->c[2]);

	स_नकल(scsi_req(rq)->cmd, pc->c, 12);

	pc->rq = rq;
	अगर (cmd == WRITE)
		pc->flags |= PC_FLAG_WRITING;

	pc->flags |= PC_FLAG_DMA_OK;
पूर्ण

अटल व्योम idefloppy_blockpc_cmd(काष्ठा ide_disk_obj *floppy,
		काष्ठा ide_atapi_pc *pc, काष्ठा request *rq)
अणु
	ide_init_pc(pc);
	स_नकल(pc->c, scsi_req(rq)->cmd, माप(pc->c));
	pc->rq = rq;
	अगर (blk_rq_bytes(rq)) अणु
		pc->flags |= PC_FLAG_DMA_OK;
		अगर (rq_data_dir(rq) == WRITE)
			pc->flags |= PC_FLAG_WRITING;
	पूर्ण
पूर्ण

अटल ide_startstop_t ide_floppy_करो_request(ide_drive_t *drive,
					     काष्ठा request *rq, sector_t block)
अणु
	काष्ठा ide_disk_obj *floppy = drive->driver_data;
	काष्ठा ide_cmd cmd;
	काष्ठा ide_atapi_pc *pc;

	ide_debug_log(IDE_DBG_FUNC, "enter, cmd: 0x%x\n", rq->cmd[0]);

	अगर (drive->debug_mask & IDE_DBG_RQ)
		blk_dump_rq_flags(rq, (rq->rq_disk
					? rq->rq_disk->disk_name
					: "dev?"));

	अगर (scsi_req(rq)->result >= ERROR_MAX) अणु
		अगर (drive->failed_pc) अणु
			ide_floppy_report_error(floppy, drive->failed_pc);
			drive->failed_pc = शून्य;
		पूर्ण अन्यथा
			prपूर्णांकk(KERN_ERR PFX "%s: I/O error\n", drive->name);

		अगर (ata_misc_request(rq)) अणु
			scsi_req(rq)->result = 0;
			ide_complete_rq(drive, BLK_STS_OK, blk_rq_bytes(rq));
			वापस ide_stopped;
		पूर्ण अन्यथा
			जाओ out_end;
	पूर्ण

	चयन (req_op(rq)) अणु
	शेष:
		अगर (((दीर्घ)blk_rq_pos(rq) % floppy->bs_factor) ||
		    (blk_rq_sectors(rq) % floppy->bs_factor)) अणु
			prपूर्णांकk(KERN_ERR PFX "%s: unsupported r/w rq size\n",
				drive->name);
			जाओ out_end;
		पूर्ण
		pc = &floppy->queued_pc;
		idefloppy_create_rw_cmd(drive, pc, rq, (अचिन्हित दीर्घ)block);
		अवरोध;
	हाल REQ_OP_SCSI_IN:
	हाल REQ_OP_SCSI_OUT:
		pc = &floppy->queued_pc;
		idefloppy_blockpc_cmd(floppy, pc, rq);
		अवरोध;
	हाल REQ_OP_DRV_IN:
	हाल REQ_OP_DRV_OUT:
		चयन (ide_req(rq)->type) अणु
		हाल ATA_PRIV_MISC:
		हाल ATA_PRIV_SENSE:
			pc = (काष्ठा ide_atapi_pc *)ide_req(rq)->special;
			अवरोध;
		शेष:
			BUG();
		पूर्ण
	पूर्ण

	ide_prep_sense(drive, rq);

	स_रखो(&cmd, 0, माप(cmd));

	अगर (rq_data_dir(rq))
		cmd.tf_flags |= IDE_TFLAG_WRITE;

	cmd.rq = rq;

	अगर (!blk_rq_is_passthrough(rq) || blk_rq_bytes(rq)) अणु
		ide_init_sg_cmd(&cmd, blk_rq_bytes(rq));
		ide_map_sg(drive, &cmd);
	पूर्ण

	pc->rq = rq;

	वापस ide_floppy_issue_pc(drive, &cmd, pc);
out_end:
	drive->failed_pc = शून्य;
	अगर (blk_rq_is_passthrough(rq) && scsi_req(rq)->result == 0)
		scsi_req(rq)->result = -EIO;
	ide_complete_rq(drive, BLK_STS_IOERR, blk_rq_bytes(rq));
	वापस ide_stopped;
पूर्ण

/*
 * Look at the flexible disk page parameters. We ignore the CHS capacity
 * parameters and use the LBA parameters instead.
 */
अटल पूर्णांक ide_floppy_get_flexible_disk_page(ide_drive_t *drive,
					     काष्ठा ide_atapi_pc *pc)
अणु
	काष्ठा ide_disk_obj *floppy = drive->driver_data;
	काष्ठा gendisk *disk = floppy->disk;
	u8 *page, buf[40];
	पूर्णांक capacity, lba_capacity;
	u16 transfer_rate, sector_size, cyls, rpm;
	u8 heads, sectors;

	ide_floppy_create_mode_sense_cmd(pc, IDEFLOPPY_FLEXIBLE_DISK_PAGE);

	अगर (ide_queue_pc_tail(drive, disk, pc, buf, pc->req_xfer)) अणु
		prपूर्णांकk(KERN_ERR PFX "Can't get flexible disk page params\n");
		वापस 1;
	पूर्ण

	अगर (buf[3] & 0x80)
		drive->dev_flags |= IDE_DFLAG_WP;
	अन्यथा
		drive->dev_flags &= ~IDE_DFLAG_WP;

	set_disk_ro(disk, !!(drive->dev_flags & IDE_DFLAG_WP));

	page = &buf[8];

	transfer_rate = be16_to_cpup((__be16 *)&buf[8 + 2]);
	sector_size   = be16_to_cpup((__be16 *)&buf[8 + 6]);
	cyls          = be16_to_cpup((__be16 *)&buf[8 + 8]);
	rpm           = be16_to_cpup((__be16 *)&buf[8 + 28]);
	heads         = buf[8 + 4];
	sectors       = buf[8 + 5];

	capacity = cyls * heads * sectors * sector_size;

	अगर (स_भेद(page, &floppy->flexible_disk_page, 32))
		prपूर्णांकk(KERN_INFO PFX "%s: %dkB, %d/%d/%d CHS, %d kBps, "
				"%d sector size, %d rpm\n",
				drive->name, capacity / 1024, cyls, heads,
				sectors, transfer_rate / 8, sector_size, rpm);

	स_नकल(&floppy->flexible_disk_page, page, 32);
	drive->bios_cyl = cyls;
	drive->bios_head = heads;
	drive->bios_sect = sectors;
	lba_capacity = floppy->blocks * floppy->block_size;

	अगर (capacity < lba_capacity) अणु
		prपूर्णांकk(KERN_NOTICE PFX "%s: The disk reports a capacity of %d "
			"bytes, but the drive only handles %d\n",
			drive->name, lba_capacity, capacity);
		floppy->blocks = floppy->block_size ?
			capacity / floppy->block_size : 0;
		drive->capacity64 = floppy->blocks * floppy->bs_factor;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Determine अगर a media is present in the floppy drive, and अगर so, its LBA
 * capacity.
 */
अटल पूर्णांक ide_floppy_get_capacity(ide_drive_t *drive)
अणु
	काष्ठा ide_disk_obj *floppy = drive->driver_data;
	काष्ठा gendisk *disk = floppy->disk;
	काष्ठा ide_atapi_pc pc;
	u8 *cap_desc;
	u8 pc_buf[256], header_len, desc_cnt;
	पूर्णांक i, rc = 1, blocks, length;

	ide_debug_log(IDE_DBG_FUNC, "enter");

	drive->bios_cyl = 0;
	drive->bios_head = drive->bios_sect = 0;
	floppy->blocks = 0;
	floppy->bs_factor = 1;
	drive->capacity64 = 0;

	ide_floppy_create_पढ़ो_capacity_cmd(&pc);
	अगर (ide_queue_pc_tail(drive, disk, &pc, pc_buf, pc.req_xfer)) अणु
		prपूर्णांकk(KERN_ERR PFX "Can't get floppy parameters\n");
		वापस 1;
	पूर्ण
	header_len = pc_buf[3];
	cap_desc = &pc_buf[4];
	desc_cnt = header_len / 8; /* capacity descriptor of 8 bytes */

	क्रम (i = 0; i < desc_cnt; i++) अणु
		अचिन्हित पूर्णांक desc_start = 4 + i*8;

		blocks = be32_to_cpup((__be32 *)&pc_buf[desc_start]);
		length = be16_to_cpup((__be16 *)&pc_buf[desc_start + 6]);

		ide_debug_log(IDE_DBG_PROBE, "Descriptor %d: %dkB, %d blocks, "
					     "%d sector size",
					     i, blocks * length / 1024,
					     blocks, length);

		अगर (i)
			जारी;
		/*
		 * the code below is valid only क्रम the 1st descriptor, ie i=0
		 */

		चयन (pc_buf[desc_start + 4] & 0x03) अणु
		/* Clik! drive वापसs this instead of CAPACITY_CURRENT */
		हाल CAPACITY_UNFORMATTED:
			अगर (!(drive->atapi_flags & IDE_AFLAG_CLIK_DRIVE))
				/*
				 * If it is not a clik drive, अवरोध out
				 * (मुख्यtains previous driver behaviour)
				 */
				अवरोध;
			fallthrough;
		हाल CAPACITY_CURRENT:
			/* Normal Zip/LS-120 disks */
			अगर (स_भेद(cap_desc, &floppy->cap_desc, 8))
				prपूर्णांकk(KERN_INFO PFX "%s: %dkB, %d blocks, %d "
				       "sector size\n",
				       drive->name, blocks * length / 1024,
				       blocks, length);
			स_नकल(&floppy->cap_desc, cap_desc, 8);

			अगर (!length || length % 512) अणु
				prपूर्णांकk(KERN_NOTICE PFX "%s: %d bytes block size"
				       " not supported\n", drive->name, length);
			पूर्ण अन्यथा अणु
				floppy->blocks = blocks;
				floppy->block_size = length;
				floppy->bs_factor = length / 512;
				अगर (floppy->bs_factor != 1)
					prपूर्णांकk(KERN_NOTICE PFX "%s: Warning: "
					       "non 512 bytes block size not "
					       "fully supported\n",
					       drive->name);
				drive->capacity64 =
					floppy->blocks * floppy->bs_factor;
				rc = 0;
			पूर्ण
			अवरोध;
		हाल CAPACITY_NO_CARTRIDGE:
			/*
			 * This is a KERN_ERR so it appears on screen
			 * क्रम the user to see
			 */
			prपूर्णांकk(KERN_ERR PFX "%s: No disk in drive\n",
			       drive->name);
			अवरोध;
		हाल CAPACITY_INVALID:
			prपूर्णांकk(KERN_ERR PFX "%s: Invalid capacity for disk "
				"in drive\n", drive->name);
			अवरोध;
		पूर्ण
		ide_debug_log(IDE_DBG_PROBE, "Descriptor 0 Code: %d",
					     pc_buf[desc_start + 4] & 0x03);
	पूर्ण

	/* Clik! disk करोes not support get_flexible_disk_page */
	अगर (!(drive->atapi_flags & IDE_AFLAG_CLIK_DRIVE))
		(व्योम) ide_floppy_get_flexible_disk_page(drive, &pc);

	वापस rc;
पूर्ण

अटल व्योम ide_floppy_setup(ide_drive_t *drive)
अणु
	काष्ठा ide_disk_obj *floppy = drive->driver_data;
	u16 *id = drive->id;

	drive->pc_callback	 = ide_floppy_callback;

	/*
	 * We used to check revisions here. At this poपूर्णांक however I'm giving up.
	 * Just assume they are all broken, its easier.
	 *
	 * The actual reason क्रम the workarounds was likely a driver bug after
	 * all rather than a firmware bug, and the workaround below used to hide
	 * it. It should be fixed as of version 1.9, but to be on the safe side
	 * we'll leave the limitation below क्रम the 2.2.x tree.
	 */
	अगर (strstarts((अक्षर *)&id[ATA_ID_PROD], "IOMEGA ZIP 100 ATAPI")) अणु
		drive->atapi_flags |= IDE_AFLAG_ZIP_DRIVE;
		/* This value will be visible in the /proc/ide/hdx/settings */
		drive->pc_delay = IDEFLOPPY_PC_DELAY;
		blk_queue_max_hw_sectors(drive->queue, 64);
	पूर्ण

	/*
	 * Guess what? The IOMEGA Clik! drive also needs the above fix. It makes
	 * nasty clicking noises without it, so please करोn't हटाओ this.
	 */
	अगर (strstarts((अक्षर *)&id[ATA_ID_PROD], "IOMEGA Clik!")) अणु
		blk_queue_max_hw_sectors(drive->queue, 64);
		drive->atapi_flags |= IDE_AFLAG_CLIK_DRIVE;
		/* IOMEGA Clik! drives करो not support lock/unlock commands */
		drive->dev_flags &= ~IDE_DFLAG_DOORLOCKING;
	पूर्ण

	(व्योम) ide_floppy_get_capacity(drive);

	ide_proc_रेजिस्टर_driver(drive, floppy->driver);
पूर्ण

अटल व्योम ide_floppy_flush(ide_drive_t *drive)
अणु
पूर्ण

अटल पूर्णांक ide_floppy_init_media(ide_drive_t *drive, काष्ठा gendisk *disk)
अणु
	पूर्णांक ret = 0;

	अगर (ide_करो_test_unit_पढ़ोy(drive, disk))
		ide_करो_start_stop(drive, disk, 1);

	ret = ide_floppy_get_capacity(drive);

	set_capacity(disk, ide_gd_capacity(drive));

	वापस ret;
पूर्ण

स्थिर काष्ठा ide_disk_ops ide_atapi_disk_ops = अणु
	.check		= ide_check_atapi_device,
	.get_capacity	= ide_floppy_get_capacity,
	.setup		= ide_floppy_setup,
	.flush		= ide_floppy_flush,
	.init_media	= ide_floppy_init_media,
	.set_करोorlock	= ide_set_media_lock,
	.करो_request	= ide_floppy_करो_request,
	.ioctl		= ide_floppy_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl	= ide_floppy_compat_ioctl,
#पूर्ण_अगर
पूर्ण;
