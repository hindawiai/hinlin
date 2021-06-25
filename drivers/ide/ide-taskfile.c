<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (C) 2000-2002	   Michael Cornwell <cornwell@acm.org>
 *  Copyright (C) 2000-2002	   Andre Hedrick <andre@linux-ide.org>
 *  Copyright (C) 2001-2002	   Klaus Smolin
 *					IBM Storage Technology Division
 *  Copyright (C) 2003-2004, 2007  Bartlomiej Zolnierkiewicz
 *
 *  The big the bad and the ugly.
 */

#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/sched.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/hdreg.h>
#समावेश <linux/ide.h>
#समावेश <linux/nmi.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/पन.स>

व्योम ide_tf_पढ़ोback(ide_drive_t *drive, काष्ठा ide_cmd *cmd)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	स्थिर काष्ठा ide_tp_ops *tp_ops = hwअगर->tp_ops;

	/* Be sure we're looking at the low order bytes */
	tp_ops->ग_लिखो_devctl(hwअगर, ATA_DEVCTL_OBS);

	tp_ops->tf_पढ़ो(drive, &cmd->tf, cmd->valid.in.tf);

	अगर (cmd->tf_flags & IDE_TFLAG_LBA48) अणु
		tp_ops->ग_लिखो_devctl(hwअगर, ATA_HOB | ATA_DEVCTL_OBS);

		tp_ops->tf_पढ़ो(drive, &cmd->hob, cmd->valid.in.hob);
	पूर्ण
पूर्ण

व्योम ide_tf_dump(स्थिर अक्षर *s, काष्ठा ide_cmd *cmd)
अणु
#अगर_घोषित DEBUG
	prपूर्णांकk("%s: tf: feat 0x%02x nsect 0x%02x lbal 0x%02x "
		"lbam 0x%02x lbah 0x%02x dev 0x%02x cmd 0x%02x\n",
	       s, cmd->tf.feature, cmd->tf.nsect,
	       cmd->tf.lbal, cmd->tf.lbam, cmd->tf.lbah,
	       cmd->tf.device, cmd->tf.command);
	prपूर्णांकk("%s: hob: nsect 0x%02x lbal 0x%02x lbam 0x%02x lbah 0x%02x\n",
	       s, cmd->hob.nsect, cmd->hob.lbal, cmd->hob.lbam, cmd->hob.lbah);
#पूर्ण_अगर
पूर्ण

पूर्णांक taskfile_lib_get_identअगरy(ide_drive_t *drive, u8 *buf)
अणु
	काष्ठा ide_cmd cmd;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.tf.nsect = 0x01;
	अगर (drive->media == ide_disk)
		cmd.tf.command = ATA_CMD_ID_ATA;
	अन्यथा
		cmd.tf.command = ATA_CMD_ID_ATAPI;
	cmd.valid.out.tf = IDE_VALID_OUT_TF | IDE_VALID_DEVICE;
	cmd.valid.in.tf  = IDE_VALID_IN_TF  | IDE_VALID_DEVICE;
	cmd.protocol = ATA_PROT_PIO;

	वापस ide_raw_taskfile(drive, &cmd, buf, 1);
पूर्ण

अटल ide_startstop_t task_no_data_पूर्णांकr(ide_drive_t *);
अटल ide_startstop_t pre_task_out_पूर्णांकr(ide_drive_t *, काष्ठा ide_cmd *);
अटल ide_startstop_t task_pio_पूर्णांकr(ide_drive_t *);

ide_startstop_t करो_rw_taskfile(ide_drive_t *drive, काष्ठा ide_cmd *orig_cmd)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	काष्ठा ide_cmd *cmd = &hwअगर->cmd;
	काष्ठा ide_taskfile *tf = &cmd->tf;
	ide_handler_t *handler = शून्य;
	स्थिर काष्ठा ide_tp_ops *tp_ops = hwअगर->tp_ops;
	स्थिर काष्ठा ide_dma_ops *dma_ops = hwअगर->dma_ops;

	अगर (orig_cmd->protocol == ATA_PROT_PIO &&
	    (orig_cmd->tf_flags & IDE_TFLAG_MULTI_PIO) &&
	    drive->mult_count == 0) अणु
		pr_err("%s: multimode not set!\n", drive->name);
		वापस ide_stopped;
	पूर्ण

	अगर (orig_cmd->ftf_flags & IDE_FTFLAG_FLAGGED)
		orig_cmd->ftf_flags |= IDE_FTFLAG_SET_IN_FLAGS;

	स_नकल(cmd, orig_cmd, माप(*cmd));

	अगर ((cmd->tf_flags & IDE_TFLAG_DMA_PIO_FALLBACK) == 0) अणु
		ide_tf_dump(drive->name, cmd);
		tp_ops->ग_लिखो_devctl(hwअगर, ATA_DEVCTL_OBS);

		अगर (cmd->ftf_flags & IDE_FTFLAG_OUT_DATA) अणु
			u8 data[2] = अणु cmd->tf.data, cmd->hob.data पूर्ण;

			tp_ops->output_data(drive, cmd, data, 2);
		पूर्ण

		अगर (cmd->valid.out.tf & IDE_VALID_DEVICE) अणु
			u8 HIHI = (cmd->tf_flags & IDE_TFLAG_LBA48) ?
				  0xE0 : 0xEF;

			अगर (!(cmd->ftf_flags & IDE_FTFLAG_FLAGGED))
				cmd->tf.device &= HIHI;
			cmd->tf.device |= drive->select;
		पूर्ण

		tp_ops->tf_load(drive, &cmd->hob, cmd->valid.out.hob);
		tp_ops->tf_load(drive, &cmd->tf,  cmd->valid.out.tf);
	पूर्ण

	चयन (cmd->protocol) अणु
	हाल ATA_PROT_PIO:
		अगर (cmd->tf_flags & IDE_TFLAG_WRITE) अणु
			tp_ops->exec_command(hwअगर, tf->command);
			ndelay(400);	/* FIXME */
			वापस pre_task_out_पूर्णांकr(drive, cmd);
		पूर्ण
		handler = task_pio_पूर्णांकr;
		fallthrough;
	हाल ATA_PROT_NODATA:
		अगर (handler == शून्य)
			handler = task_no_data_पूर्णांकr;
		ide_execute_command(drive, cmd, handler, WAIT_WORSTCASE);
		वापस ide_started;
	हाल ATA_PROT_DMA:
		अगर (ide_dma_prepare(drive, cmd))
			वापस ide_stopped;
		hwअगर->expiry = dma_ops->dma_समयr_expiry;
		ide_execute_command(drive, cmd, ide_dma_पूर्णांकr, 2 * WAIT_CMD);
		dma_ops->dma_start(drive);
		fallthrough;
	शेष:
		वापस ide_started;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(करो_rw_taskfile);

अटल ide_startstop_t task_no_data_पूर्णांकr(ide_drive_t *drive)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	काष्ठा ide_cmd *cmd = &hwअगर->cmd;
	काष्ठा ide_taskfile *tf = &cmd->tf;
	पूर्णांक custom = (cmd->tf_flags & IDE_TFLAG_CUSTOM_HANDLER) ? 1 : 0;
	पूर्णांक retries = (custom && tf->command == ATA_CMD_INIT_DEV_PARAMS) ? 5 : 1;
	u8 stat;

	local_irq_enable_in_hardirq();

	जबतक (1) अणु
		stat = hwअगर->tp_ops->पढ़ो_status(hwअगर);
		अगर ((stat & ATA_BUSY) == 0 || retries-- == 0)
			अवरोध;
		udelay(10);
	पूर्ण;

	अगर (!OK_STAT(stat, ATA_DRDY, BAD_STAT)) अणु
		अगर (custom && tf->command == ATA_CMD_SET_MULTI) अणु
			drive->mult_req = drive->mult_count = 0;
			drive->special_flags |= IDE_SFLAG_RECALIBRATE;
			(व्योम)ide_dump_status(drive, __func__, stat);
			वापस ide_stopped;
		पूर्ण अन्यथा अगर (custom && tf->command == ATA_CMD_INIT_DEV_PARAMS) अणु
			अगर ((stat & (ATA_ERR | ATA_DRQ)) == 0) अणु
				ide_set_handler(drive, &task_no_data_पूर्णांकr,
						WAIT_WORSTCASE);
				वापस ide_started;
			पूर्ण
		पूर्ण
		वापस ide_error(drive, "task_no_data_intr", stat);
	पूर्ण

	अगर (custom && tf->command == ATA_CMD_SET_MULTI)
		drive->mult_count = drive->mult_req;

	अगर (custom == 0 || tf->command == ATA_CMD_IDLEIMMEDIATE ||
	    tf->command == ATA_CMD_CHK_POWER) अणु
		काष्ठा request *rq = hwअगर->rq;

		अगर (ata_pm_request(rq))
			ide_complete_pm_rq(drive, rq);
		अन्यथा
			ide_finish_cmd(drive, cmd, stat);
	पूर्ण

	वापस ide_stopped;
पूर्ण

अटल u8 रुको_drive_not_busy(ide_drive_t *drive)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	पूर्णांक retries;
	u8 stat;

	/*
	 * Last sector was transferred, रुको until device is पढ़ोy.  This can
	 * take up to 6 ms on some ATAPI devices, so we will रुको max 10 ms.
	 */
	क्रम (retries = 0; retries < 1000; retries++) अणु
		stat = hwअगर->tp_ops->पढ़ो_status(hwअगर);

		अगर (stat & ATA_BUSY)
			udelay(10);
		अन्यथा
			अवरोध;
	पूर्ण

	अगर (stat & ATA_BUSY)
		pr_err("%s: drive still BUSY!\n", drive->name);

	वापस stat;
पूर्ण

व्योम ide_pio_bytes(ide_drive_t *drive, काष्ठा ide_cmd *cmd,
		   अचिन्हित पूर्णांक ग_लिखो, अचिन्हित पूर्णांक len)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	काष्ठा scatterlist *sg = hwअगर->sg_table;
	काष्ठा scatterlist *cursg = cmd->cursg;
	काष्ठा page *page;
	अचिन्हित पूर्णांक offset;
	u8 *buf;

	अगर (cursg == शून्य)
		cursg = cmd->cursg = sg;

	जबतक (len) अणु
		अचिन्हित nr_bytes = min(len, cursg->length - cmd->cursg_ofs);

		page = sg_page(cursg);
		offset = cursg->offset + cmd->cursg_ofs;

		/* get the current page and offset */
		page = nth_page(page, (offset >> PAGE_SHIFT));
		offset %= PAGE_SIZE;

		nr_bytes = min_t(अचिन्हित, nr_bytes, (PAGE_SIZE - offset));

		buf = kmap_atomic(page) + offset;

		cmd->nleft -= nr_bytes;
		cmd->cursg_ofs += nr_bytes;

		अगर (cmd->cursg_ofs == cursg->length) अणु
			cursg = cmd->cursg = sg_next(cmd->cursg);
			cmd->cursg_ofs = 0;
		पूर्ण

		/* करो the actual data transfer */
		अगर (ग_लिखो)
			hwअगर->tp_ops->output_data(drive, cmd, buf, nr_bytes);
		अन्यथा
			hwअगर->tp_ops->input_data(drive, cmd, buf, nr_bytes);

		kunmap_atomic(buf);

		len -= nr_bytes;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(ide_pio_bytes);

अटल व्योम ide_pio_datablock(ide_drive_t *drive, काष्ठा ide_cmd *cmd,
			      अचिन्हित पूर्णांक ग_लिखो)
अणु
	अचिन्हित पूर्णांक nr_bytes;

	u8 saved_io_32bit = drive->io_32bit;

	अगर (cmd->tf_flags & IDE_TFLAG_FS)
		scsi_req(cmd->rq)->result = 0;

	अगर (cmd->tf_flags & IDE_TFLAG_IO_16BIT)
		drive->io_32bit = 0;

	touch_softlockup_watchकरोg();

	अगर (cmd->tf_flags & IDE_TFLAG_MULTI_PIO)
		nr_bytes = min_t(अचिन्हित, cmd->nleft, drive->mult_count << 9);
	अन्यथा
		nr_bytes = SECTOR_SIZE;

	ide_pio_bytes(drive, cmd, ग_लिखो, nr_bytes);

	drive->io_32bit = saved_io_32bit;
पूर्ण

अटल व्योम ide_error_cmd(ide_drive_t *drive, काष्ठा ide_cmd *cmd)
अणु
	अगर (cmd->tf_flags & IDE_TFLAG_FS) अणु
		पूर्णांक nr_bytes = cmd->nbytes - cmd->nleft;

		अगर (cmd->protocol == ATA_PROT_PIO &&
		    ((cmd->tf_flags & IDE_TFLAG_WRITE) || cmd->nleft == 0)) अणु
			अगर (cmd->tf_flags & IDE_TFLAG_MULTI_PIO)
				nr_bytes -= drive->mult_count << 9;
			अन्यथा
				nr_bytes -= SECTOR_SIZE;
		पूर्ण

		अगर (nr_bytes > 0)
			ide_complete_rq(drive, BLK_STS_OK, nr_bytes);
	पूर्ण
पूर्ण

व्योम ide_finish_cmd(ide_drive_t *drive, काष्ठा ide_cmd *cmd, u8 stat)
अणु
	काष्ठा request *rq = drive->hwअगर->rq;
	u8 err = ide_पढ़ो_error(drive), nsect = cmd->tf.nsect;
	u8 set_xfer = !!(cmd->tf_flags & IDE_TFLAG_SET_XFER);

	ide_complete_cmd(drive, cmd, stat, err);
	scsi_req(rq)->result = err;

	अगर (err == 0 && set_xfer) अणु
		ide_set_xfer_rate(drive, nsect);
		ide_driveid_update(drive);
	पूर्ण

	ide_complete_rq(drive, err ? BLK_STS_IOERR : BLK_STS_OK, blk_rq_bytes(rq));
पूर्ण

/*
 * Handler क्रम command with PIO data phase.
 */
अटल ide_startstop_t task_pio_पूर्णांकr(ide_drive_t *drive)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	काष्ठा ide_cmd *cmd = &drive->hwअगर->cmd;
	u8 stat = hwअगर->tp_ops->पढ़ो_status(hwअगर);
	u8 ग_लिखो = !!(cmd->tf_flags & IDE_TFLAG_WRITE);

	अगर (ग_लिखो == 0) अणु
		/* Error? */
		अगर (stat & ATA_ERR)
			जाओ out_err;

		/* Didn't want any data? Odd. */
		अगर ((stat & ATA_DRQ) == 0) अणु
			/* Command all करोne? */
			अगर (OK_STAT(stat, ATA_DRDY, ATA_BUSY))
				जाओ out_end;

			/* Assume it was a spurious irq */
			जाओ out_रुको;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!OK_STAT(stat, DRIVE_READY, drive->bad_wstat))
			जाओ out_err;

		/* Deal with unexpected ATA data phase. */
		अगर (((stat & ATA_DRQ) == 0) ^ (cmd->nleft == 0))
			जाओ out_err;
	पूर्ण

	अगर (ग_लिखो && cmd->nleft == 0)
		जाओ out_end;

	/* Still data left to transfer. */
	ide_pio_datablock(drive, cmd, ग_लिखो);

	/* Are we करोne? Check status and finish transfer. */
	अगर (ग_लिखो == 0 && cmd->nleft == 0) अणु
		stat = रुको_drive_not_busy(drive);
		अगर (!OK_STAT(stat, 0, BAD_STAT))
			जाओ out_err;

		जाओ out_end;
	पूर्ण
out_रुको:
	/* Still data left to transfer. */
	ide_set_handler(drive, &task_pio_पूर्णांकr, WAIT_WORSTCASE);
	वापस ide_started;
out_end:
	अगर ((cmd->tf_flags & IDE_TFLAG_FS) == 0)
		ide_finish_cmd(drive, cmd, stat);
	अन्यथा
		ide_complete_rq(drive, BLK_STS_OK, blk_rq_sectors(cmd->rq) << 9);
	वापस ide_stopped;
out_err:
	ide_error_cmd(drive, cmd);
	वापस ide_error(drive, __func__, stat);
पूर्ण

अटल ide_startstop_t pre_task_out_पूर्णांकr(ide_drive_t *drive,
					 काष्ठा ide_cmd *cmd)
अणु
	ide_startstop_t startstop;

	अगर (ide_रुको_stat(&startstop, drive, ATA_DRQ,
			  drive->bad_wstat, WAIT_DRQ)) अणु
		pr_err("%s: no DRQ after issuing %sWRITE%s\n", drive->name,
			(cmd->tf_flags & IDE_TFLAG_MULTI_PIO) ? "MULT" : "",
			(drive->dev_flags & IDE_DFLAG_LBA48) ? "_EXT" : "");
		वापस startstop;
	पूर्ण

	अगर (!क्रमce_irqthपढ़ोs && (drive->dev_flags & IDE_DFLAG_UNMASK) == 0)
		local_irq_disable();

	ide_set_handler(drive, &task_pio_पूर्णांकr, WAIT_WORSTCASE);

	ide_pio_datablock(drive, cmd, 1);

	वापस ide_started;
पूर्ण

पूर्णांक ide_raw_taskfile(ide_drive_t *drive, काष्ठा ide_cmd *cmd, u8 *buf,
		     u16 nsect)
अणु
	काष्ठा request *rq;
	पूर्णांक error;

	rq = blk_get_request(drive->queue,
		(cmd->tf_flags & IDE_TFLAG_WRITE) ?
			REQ_OP_DRV_OUT : REQ_OP_DRV_IN, 0);
	ide_req(rq)->type = ATA_PRIV_TASKखाता;

	/*
	 * (ks) We transfer currently only whole sectors.
	 * This is suffient क्रम now.  But, it would be great,
	 * अगर we would find a solution to transfer any size.
	 * To support special commands like READ LONG.
	 */
	अगर (nsect) अणु
		error = blk_rq_map_kern(drive->queue, rq, buf,
					nsect * SECTOR_SIZE, GFP_NOIO);
		अगर (error)
			जाओ put_req;
	पूर्ण

	ide_req(rq)->special = cmd;
	cmd->rq = rq;

	blk_execute_rq(शून्य, rq, 0);
	error = scsi_req(rq)->result ? -EIO : 0;
put_req:
	blk_put_request(rq);
	वापस error;
पूर्ण
EXPORT_SYMBOL(ide_raw_taskfile);

पूर्णांक ide_no_data_taskfile(ide_drive_t *drive, काष्ठा ide_cmd *cmd)
अणु
	cmd->protocol = ATA_PROT_NODATA;

	वापस ide_raw_taskfile(drive, cmd, शून्य, 0);
पूर्ण
EXPORT_SYMBOL_GPL(ide_no_data_taskfile);

#अगर_घोषित CONFIG_IDE_TASK_IOCTL
पूर्णांक ide_taskfile_ioctl(ide_drive_t *drive, अचिन्हित दीर्घ arg)
अणु
	ide_task_request_t	*req_task;
	काष्ठा ide_cmd		cmd;
	u8 *outbuf		= शून्य;
	u8 *inbuf		= शून्य;
	u8 *data_buf		= शून्य;
	पूर्णांक err			= 0;
	पूर्णांक tasksize		= माप(काष्ठा ide_task_request_s);
	अचिन्हित पूर्णांक taskin	= 0;
	अचिन्हित पूर्णांक taskout	= 0;
	u16 nsect		= 0;
	अक्षर __user *buf = (अक्षर __user *)arg;

	req_task = memdup_user(buf, tasksize);
	अगर (IS_ERR(req_task))
		वापस PTR_ERR(req_task);

	taskout = req_task->out_size;
	taskin  = req_task->in_size;

	अगर (taskin > 65536 || taskout > 65536) अणु
		err = -EINVAL;
		जाओ पात;
	पूर्ण

	अगर (taskout) अणु
		पूर्णांक outtotal = tasksize;
		outbuf = kzalloc(taskout, GFP_KERNEL);
		अगर (outbuf == शून्य) अणु
			err = -ENOMEM;
			जाओ पात;
		पूर्ण
		अगर (copy_from_user(outbuf, buf + outtotal, taskout)) अणु
			err = -EFAULT;
			जाओ पात;
		पूर्ण
	पूर्ण

	अगर (taskin) अणु
		पूर्णांक पूर्णांकotal = tasksize + taskout;
		inbuf = kzalloc(taskin, GFP_KERNEL);
		अगर (inbuf == शून्य) अणु
			err = -ENOMEM;
			जाओ पात;
		पूर्ण
		अगर (copy_from_user(inbuf, buf + पूर्णांकotal, taskin)) अणु
			err = -EFAULT;
			जाओ पात;
		पूर्ण
	पूर्ण

	स_रखो(&cmd, 0, माप(cmd));

	स_नकल(&cmd.hob, req_task->hob_ports, HDIO_DRIVE_HOB_HDR_SIZE - 2);
	स_नकल(&cmd.tf,  req_task->io_ports,  HDIO_DRIVE_TASK_HDR_SIZE);

	cmd.valid.out.tf = IDE_VALID_DEVICE;
	cmd.valid.in.tf  = IDE_VALID_DEVICE | IDE_VALID_IN_TF;
	cmd.tf_flags = IDE_TFLAG_IO_16BIT;

	अगर (drive->dev_flags & IDE_DFLAG_LBA48) अणु
		cmd.tf_flags |= IDE_TFLAG_LBA48;
		cmd.valid.in.hob = IDE_VALID_IN_HOB;
	पूर्ण

	अगर (req_task->out_flags.all) अणु
		cmd.ftf_flags |= IDE_FTFLAG_FLAGGED;

		अगर (req_task->out_flags.b.data)
			cmd.ftf_flags |= IDE_FTFLAG_OUT_DATA;

		अगर (req_task->out_flags.b.nsector_hob)
			cmd.valid.out.hob |= IDE_VALID_NSECT;
		अगर (req_task->out_flags.b.sector_hob)
			cmd.valid.out.hob |= IDE_VALID_LBAL;
		अगर (req_task->out_flags.b.lcyl_hob)
			cmd.valid.out.hob |= IDE_VALID_LBAM;
		अगर (req_task->out_flags.b.hcyl_hob)
			cmd.valid.out.hob |= IDE_VALID_LBAH;

		अगर (req_task->out_flags.b.error_feature)
			cmd.valid.out.tf  |= IDE_VALID_FEATURE;
		अगर (req_task->out_flags.b.nsector)
			cmd.valid.out.tf  |= IDE_VALID_NSECT;
		अगर (req_task->out_flags.b.sector)
			cmd.valid.out.tf  |= IDE_VALID_LBAL;
		अगर (req_task->out_flags.b.lcyl)
			cmd.valid.out.tf  |= IDE_VALID_LBAM;
		अगर (req_task->out_flags.b.hcyl)
			cmd.valid.out.tf  |= IDE_VALID_LBAH;
	पूर्ण अन्यथा अणु
		cmd.valid.out.tf |= IDE_VALID_OUT_TF;
		अगर (cmd.tf_flags & IDE_TFLAG_LBA48)
			cmd.valid.out.hob |= IDE_VALID_OUT_HOB;
	पूर्ण

	अगर (req_task->in_flags.b.data)
		cmd.ftf_flags |= IDE_FTFLAG_IN_DATA;

	अगर (req_task->req_cmd == IDE_DRIVE_TASK_RAW_WRITE) अणु
		/* fixup data phase अगर needed */
		अगर (req_task->data_phase == TASKखाता_IN_DMAQ ||
		    req_task->data_phase == TASKखाता_IN_DMA)
			cmd.tf_flags |= IDE_TFLAG_WRITE;
	पूर्ण

	cmd.protocol = ATA_PROT_DMA;

	चयन (req_task->data_phase) अणु
	हाल TASKखाता_MULTI_OUT:
		अगर (!drive->mult_count) अणु
			/* (hs): give up अगर multcount is not set */
			pr_err("%s: %s Multimode Write multcount is not set\n",
				drive->name, __func__);
			err = -EPERM;
			जाओ पात;
		पूर्ण
		cmd.tf_flags |= IDE_TFLAG_MULTI_PIO;
		fallthrough;
	हाल TASKखाता_OUT:
		cmd.protocol = ATA_PROT_PIO;
		fallthrough;
	हाल TASKखाता_OUT_DMAQ:
	हाल TASKखाता_OUT_DMA:
		cmd.tf_flags |= IDE_TFLAG_WRITE;
		nsect = taskout / SECTOR_SIZE;
		data_buf = outbuf;
		अवरोध;
	हाल TASKखाता_MULTI_IN:
		अगर (!drive->mult_count) अणु
			/* (hs): give up अगर multcount is not set */
			pr_err("%s: %s Multimode Read multcount is not set\n",
				drive->name, __func__);
			err = -EPERM;
			जाओ पात;
		पूर्ण
		cmd.tf_flags |= IDE_TFLAG_MULTI_PIO;
		fallthrough;
	हाल TASKखाता_IN:
		cmd.protocol = ATA_PROT_PIO;
		fallthrough;
	हाल TASKखाता_IN_DMAQ:
	हाल TASKखाता_IN_DMA:
		nsect = taskin / SECTOR_SIZE;
		data_buf = inbuf;
		अवरोध;
	हाल TASKखाता_NO_DATA:
		cmd.protocol = ATA_PROT_NODATA;
		अवरोध;
	शेष:
		err = -EFAULT;
		जाओ पात;
	पूर्ण

	अगर (req_task->req_cmd == IDE_DRIVE_TASK_NO_DATA)
		nsect = 0;
	अन्यथा अगर (!nsect) अणु
		nsect = (cmd.hob.nsect << 8) | cmd.tf.nsect;

		अगर (!nsect) अणु
			pr_err("%s: in/out command without data\n",
					drive->name);
			err = -EFAULT;
			जाओ पात;
		पूर्ण
	पूर्ण

	err = ide_raw_taskfile(drive, &cmd, data_buf, nsect);

	स_नकल(req_task->hob_ports, &cmd.hob, HDIO_DRIVE_HOB_HDR_SIZE - 2);
	स_नकल(req_task->io_ports,  &cmd.tf,  HDIO_DRIVE_TASK_HDR_SIZE);

	अगर ((cmd.ftf_flags & IDE_FTFLAG_SET_IN_FLAGS) &&
	    req_task->in_flags.all == 0) अणु
		req_task->in_flags.all = IDE_TASKखाता_STD_IN_FLAGS;
		अगर (drive->dev_flags & IDE_DFLAG_LBA48)
			req_task->in_flags.all |= (IDE_HOB_STD_IN_FLAGS << 8);
	पूर्ण

	अगर (copy_to_user(buf, req_task, tasksize)) अणु
		err = -EFAULT;
		जाओ पात;
	पूर्ण
	अगर (taskout) अणु
		पूर्णांक outtotal = tasksize;
		अगर (copy_to_user(buf + outtotal, outbuf, taskout)) अणु
			err = -EFAULT;
			जाओ पात;
		पूर्ण
	पूर्ण
	अगर (taskin) अणु
		पूर्णांक पूर्णांकotal = tasksize + taskout;
		अगर (copy_to_user(buf + पूर्णांकotal, inbuf, taskin)) अणु
			err = -EFAULT;
			जाओ पात;
		पूर्ण
	पूर्ण
पात:
	kमुक्त(req_task);
	kमुक्त(outbuf);
	kमुक्त(inbuf);

	वापस err;
पूर्ण
#पूर्ण_अगर
