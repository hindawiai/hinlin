<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ide.h>
#समावेश <linux/bitops.h>

u64 ide_get_lba_addr(काष्ठा ide_cmd *cmd, पूर्णांक lba48)
अणु
	काष्ठा ide_taskfile *tf = &cmd->tf;
	u32 high, low;

	low  = (tf->lbah << 16) | (tf->lbam << 8) | tf->lbal;
	अगर (lba48) अणु
		tf = &cmd->hob;
		high = (tf->lbah << 16) | (tf->lbam << 8) | tf->lbal;
	पूर्ण अन्यथा
		high = tf->device & 0xf;

	वापस ((u64)high << 24) | low;
पूर्ण
EXPORT_SYMBOL_GPL(ide_get_lba_addr);

अटल व्योम ide_dump_sector(ide_drive_t *drive)
अणु
	काष्ठा ide_cmd cmd;
	काष्ठा ide_taskfile *tf = &cmd.tf;
	u8 lba48 = !!(drive->dev_flags & IDE_DFLAG_LBA48);

	स_रखो(&cmd, 0, माप(cmd));
	अगर (lba48) अणु
		cmd.valid.in.tf  = IDE_VALID_LBA;
		cmd.valid.in.hob = IDE_VALID_LBA;
		cmd.tf_flags = IDE_TFLAG_LBA48;
	पूर्ण अन्यथा
		cmd.valid.in.tf  = IDE_VALID_LBA | IDE_VALID_DEVICE;

	ide_tf_पढ़ोback(drive, &cmd);

	अगर (lba48 || (tf->device & ATA_LBA))
		prपूर्णांकk(KERN_CONT ", LBAsect=%llu",
			(अचिन्हित दीर्घ दीर्घ)ide_get_lba_addr(&cmd, lba48));
	अन्यथा
		prपूर्णांकk(KERN_CONT ", CHS=%d/%d/%d", (tf->lbah << 8) + tf->lbam,
			tf->device & 0xf, tf->lbal);
पूर्ण

अटल व्योम ide_dump_ata_error(ide_drive_t *drive, u8 err)
अणु
	prपूर्णांकk(KERN_CONT "{ ");
	अगर (err & ATA_ABORTED)
		prपूर्णांकk(KERN_CONT "DriveStatusError ");
	अगर (err & ATA_ICRC)
		prपूर्णांकk(KERN_CONT "%s",
			(err & ATA_ABORTED) ? "BadCRC " : "BadSector ");
	अगर (err & ATA_UNC)
		prपूर्णांकk(KERN_CONT "UncorrectableError ");
	अगर (err & ATA_IDNF)
		prपूर्णांकk(KERN_CONT "SectorIdNotFound ");
	अगर (err & ATA_TRK0NF)
		prपूर्णांकk(KERN_CONT "TrackZeroNotFound ");
	अगर (err & ATA_AMNF)
		prपूर्णांकk(KERN_CONT "AddrMarkNotFound ");
	prपूर्णांकk(KERN_CONT "}");
	अगर ((err & (ATA_BBK | ATA_ABORTED)) == ATA_BBK ||
	    (err & (ATA_UNC | ATA_IDNF | ATA_AMNF))) अणु
		काष्ठा request *rq = drive->hwअगर->rq;

		ide_dump_sector(drive);

		अगर (rq)
			prपूर्णांकk(KERN_CONT ", sector=%llu",
			       (अचिन्हित दीर्घ दीर्घ)blk_rq_pos(rq));
	पूर्ण
	prपूर्णांकk(KERN_CONT "\n");
पूर्ण

अटल व्योम ide_dump_atapi_error(ide_drive_t *drive, u8 err)
अणु
	prपूर्णांकk(KERN_CONT "{ ");
	अगर (err & ATAPI_ILI)
		prपूर्णांकk(KERN_CONT "IllegalLengthIndication ");
	अगर (err & ATAPI_EOM)
		prपूर्णांकk(KERN_CONT "EndOfMedia ");
	अगर (err & ATA_ABORTED)
		prपूर्णांकk(KERN_CONT "AbortedCommand ");
	अगर (err & ATA_MCR)
		prपूर्णांकk(KERN_CONT "MediaChangeRequested ");
	अगर (err & ATAPI_LFS)
		prपूर्णांकk(KERN_CONT "LastFailedSense=0x%02x ",
			(err & ATAPI_LFS) >> 4);
	prपूर्णांकk(KERN_CONT "}\n");
पूर्ण

/**
 *	ide_dump_status		-	translate ATA/ATAPI error
 *	@drive: drive that status applies to
 *	@msg: text message to prपूर्णांक
 *	@stat: status byte to decode
 *
 *	Error reporting, in human पढ़ोable क्रमm (luxurious, but a memory hog).
 *	Combines the drive name, message and status byte to provide a
 *	user understandable explanation of the device error.
 */

u8 ide_dump_status(ide_drive_t *drive, स्थिर अक्षर *msg, u8 stat)
अणु
	u8 err = 0;

	prपूर्णांकk(KERN_ERR "%s: %s: status=0x%02x { ", drive->name, msg, stat);
	अगर (stat & ATA_BUSY)
		prपूर्णांकk(KERN_CONT "Busy ");
	अन्यथा अणु
		अगर (stat & ATA_DRDY)
			prपूर्णांकk(KERN_CONT "DriveReady ");
		अगर (stat & ATA_DF)
			prपूर्णांकk(KERN_CONT "DeviceFault ");
		अगर (stat & ATA_DSC)
			prपूर्णांकk(KERN_CONT "SeekComplete ");
		अगर (stat & ATA_DRQ)
			prपूर्णांकk(KERN_CONT "DataRequest ");
		अगर (stat & ATA_CORR)
			prपूर्णांकk(KERN_CONT "CorrectedError ");
		अगर (stat & ATA_SENSE)
			prपूर्णांकk(KERN_CONT "Sense ");
		अगर (stat & ATA_ERR)
			prपूर्णांकk(KERN_CONT "Error ");
	पूर्ण
	prपूर्णांकk(KERN_CONT "}\n");
	अगर ((stat & (ATA_BUSY | ATA_ERR)) == ATA_ERR) अणु
		err = ide_पढ़ो_error(drive);
		prपूर्णांकk(KERN_ERR "%s: %s: error=0x%02x ", drive->name, msg, err);
		अगर (drive->media == ide_disk)
			ide_dump_ata_error(drive, err);
		अन्यथा
			ide_dump_atapi_error(drive, err);
	पूर्ण

	prपूर्णांकk(KERN_ERR "%s: possibly failed opcode: 0x%02x\n",
		drive->name, drive->hwअगर->cmd.tf.command);

	वापस err;
पूर्ण
EXPORT_SYMBOL(ide_dump_status);
