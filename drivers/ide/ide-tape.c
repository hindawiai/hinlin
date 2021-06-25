<शैली गुरु>
/*
 * IDE ATAPI streaming tape driver.
 *
 * Copyright (C) 1995-1999  Gadi Oxman <gadio@netvision.net.il>
 * Copyright (C) 2003-2005  Bartlomiej Zolnierkiewicz
 *
 * This driver was स्थिरructed as a student project in the software laboratory
 * of the faculty of electrical engineering in the Technion - Israel's
 * Institute Of Technology, with the guide of Avner Lottem and Dr. Ilana David.
 *
 * It is hereby placed under the terms of the GNU general खुला license.
 * (See linux/COPYING).
 *
 * For a historical changelog see
 * Documentation/ide/ChangeLog.ide-tape.1995-2002
 */

#घोषणा DRV_NAME "ide-tape"

#घोषणा IDETAPE_VERSION "1.20"

#समावेश <linux/compat.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/समयr.h>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/major.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/genhd.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>
#समावेश <linux/pci.h>
#समावेश <linux/ide.h>
#समावेश <linux/completion.h>
#समावेश <linux/bitops.h>
#समावेश <linux/mutex.h>
#समावेश <scsi/scsi.h>

#समावेश <यंत्र/byteorder.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/unaligned.h>
#समावेश <linux/mtपन.स>

/* define to see debug info */
#अघोषित IDETAPE_DEBUG_LOG

#अगर_घोषित IDETAPE_DEBUG_LOG
#घोषणा ide_debug_log(lvl, fmt, args...) __ide_debug_log(lvl, fmt, ## args)
#अन्यथा
#घोषणा ide_debug_log(lvl, fmt, args...) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

/**************************** Tunable parameters *****************************/
/*
 * After each failed packet command we issue a request sense command and retry
 * the packet command IDETAPE_MAX_PC_RETRIES बार.
 *
 * Setting IDETAPE_MAX_PC_RETRIES to 0 will disable retries.
 */
#घोषणा IDETAPE_MAX_PC_RETRIES		3

/*
 * The following parameter is used to select the poपूर्णांक in the पूर्णांकernal tape fअगरo
 * in which we will start to refill the buffer. Decreasing the following
 * parameter will improve the प्रणाली's latency and पूर्णांकeractive response, जबतक
 * using a high value might improve प्रणाली throughput.
 */
#घोषणा IDETAPE_FIFO_THRESHOLD		2

/*
 * DSC polling parameters.
 *
 * Polling क्रम DSC (a single bit in the status रेजिस्टर) is a very important
 * function in ide-tape. There are two हालs in which we poll क्रम DSC:
 *
 * 1. Beक्रमe a पढ़ो/ग_लिखो packet command, to ensure that we can transfer data
 * from/to the tape's data buffers, without causing an actual media access.
 * In हाल the tape is not पढ़ोy yet, we take out our request from the device
 * request queue, so that ide.c could service requests from the other device
 * on the same पूर्णांकerface in the meanसमय.
 *
 * 2. After the successful initialization of a "media access packet command",
 * which is a command that can take a दीर्घ समय to complete (the पूर्णांकerval can
 * range from several seconds to even an hour). Again, we postpone our request
 * in the middle to मुक्त the bus क्रम the other device. The polling frequency
 * here should be lower than the पढ़ो/ग_लिखो frequency since those media access
 * commands are slow. We start from a "fast" frequency - IDETAPE_DSC_MA_FAST
 * (1 second), and अगर we करोn't receive DSC after IDETAPE_DSC_MA_THRESHOLD
 * (5 min), we चयन it to a lower frequency - IDETAPE_DSC_MA_SLOW (1 min).
 *
 * We also set a समयout क्रम the समयr, in हाल something goes wrong. The
 * समयout should be दीर्घer then the maximum execution समय of a tape operation.
 */

/* DSC timings. */
#घोषणा IDETAPE_DSC_RW_MIN		5*HZ/100	/* 50 msec */
#घोषणा IDETAPE_DSC_RW_MAX		40*HZ/100	/* 400 msec */
#घोषणा IDETAPE_DSC_RW_TIMEOUT		2*60*HZ		/* 2 minutes */
#घोषणा IDETAPE_DSC_MA_FAST		2*HZ		/* 2 seconds */
#घोषणा IDETAPE_DSC_MA_THRESHOLD	5*60*HZ		/* 5 minutes */
#घोषणा IDETAPE_DSC_MA_SLOW		30*HZ		/* 30 seconds */
#घोषणा IDETAPE_DSC_MA_TIMEOUT		2*60*60*HZ	/* 2 hours */

/*************************** End of tunable parameters ***********************/

/* tape directions */
क्रमागत अणु
	IDETAPE_सूची_NONE  = (1 << 0),
	IDETAPE_सूची_READ  = (1 << 1),
	IDETAPE_सूची_WRITE = (1 << 2),
पूर्ण;

/* Tape करोor status */
#घोषणा DOOR_UNLOCKED			0
#घोषणा DOOR_LOCKED			1
#घोषणा DOOR_EXPLICITLY_LOCKED		2

/* Some defines क्रम the SPACE command */
#घोषणा IDETAPE_SPACE_OVER_खाताMARK	1
#घोषणा IDETAPE_SPACE_TO_EOD		3

/* Some defines क्रम the LOAD UNLOAD command */
#घोषणा IDETAPE_LU_LOAD_MASK		1
#घोषणा IDETAPE_LU_RETENSION_MASK	2
#घोषणा IDETAPE_LU_EOT_MASK		4

/* Structures related to the SELECT SENSE / MODE SENSE packet commands. */
#घोषणा IDETAPE_BLOCK_DESCRIPTOR	0
#घोषणा IDETAPE_CAPABILITIES_PAGE	0x2a

/*
 * Most of our global data which we need to save even as we leave the driver due
 * to an पूर्णांकerrupt or a समयr event is stored in the काष्ठा defined below.
 */
प्रकार काष्ठा ide_tape_obj अणु
	ide_drive_t		*drive;
	काष्ठा ide_driver	*driver;
	काष्ठा gendisk		*disk;
	काष्ठा device		dev;

	/* used by REQ_IDETAPE_अणुREAD,WRITEपूर्ण requests */
	काष्ठा ide_atapi_pc queued_pc;

	/*
	 * DSC polling variables.
	 *
	 * While polling क्रम DSC we use postponed_rq to postpone the current
	 * request so that ide.c will be able to service pending requests on the
	 * other device. Note that at most we will have only one DSC (usually
	 * data transfer) request in the device request queue.
	 */
	bool postponed_rq;

	/* The समय in which we started polling क्रम DSC */
	अचिन्हित दीर्घ dsc_polling_start;
	/* Timer used to poll क्रम dsc */
	काष्ठा समयr_list dsc_समयr;
	/* Read/Write dsc polling frequency */
	अचिन्हित दीर्घ best_dsc_rw_freq;
	अचिन्हित दीर्घ dsc_poll_freq;
	अचिन्हित दीर्घ dsc_समयout;

	/* Read position inक्रमmation */
	u8 partition;
	/* Current block */
	अचिन्हित पूर्णांक first_frame;

	/* Last error inक्रमmation */
	u8 sense_key, asc, ascq;

	/* Character device operation */
	अचिन्हित पूर्णांक minor;
	/* device name */
	अक्षर name[4];
	/* Current अक्षरacter device data transfer direction */
	u8 chrdev_dir;

	/* tape block size, usually 512 or 1024 bytes */
	अचिन्हित लघु blk_size;
	पूर्णांक user_bs_factor;

	/* Copy of the tape's Capabilities and Mechanical Page */
	u8 caps[20];

	/*
	 * Active data transfer request parameters.
	 *
	 * At most, there is only one ide-tape originated data transfer request
	 * in the device request queue. This allows ide.c to easily service
	 * requests from the other device when we postpone our active request.
	 */

	/* Data buffer size chosen based on the tape's recommendation */
	पूर्णांक buffer_size;
	/* Staging buffer of buffer_size bytes */
	व्योम *buf;
	/* The पढ़ो/ग_लिखो cursor */
	व्योम *cur;
	/* The number of valid bytes in buf */
	माप_प्रकार valid;

	/* Measures average tape speed */
	अचिन्हित दीर्घ avg_समय;
	पूर्णांक avg_size;
	पूर्णांक avg_speed;

	/* the करोor is currently locked */
	पूर्णांक करोor_locked;
	/* the tape hardware is ग_लिखो रक्षित */
	अक्षर drv_ग_लिखो_prot;
	/* the tape is ग_लिखो रक्षित (hardware or खोलोed as पढ़ो-only) */
	अक्षर ग_लिखो_prot;
पूर्ण idetape_tape_t;

अटल DEFINE_MUTEX(ide_tape_mutex);
अटल DEFINE_MUTEX(idetape_ref_mutex);

अटल DEFINE_MUTEX(idetape_chrdev_mutex);

अटल काष्ठा class *idetape_sysfs_class;

अटल व्योम ide_tape_release(काष्ठा device *);

अटल काष्ठा ide_tape_obj *idetape_devs[MAX_HWIFS * MAX_DRIVES];

अटल काष्ठा ide_tape_obj *ide_tape_get(काष्ठा gendisk *disk, bool cdev,
					 अचिन्हित पूर्णांक i)
अणु
	काष्ठा ide_tape_obj *tape = शून्य;

	mutex_lock(&idetape_ref_mutex);

	अगर (cdev)
		tape = idetape_devs[i];
	अन्यथा
		tape = ide_drv_g(disk, ide_tape_obj);

	अगर (tape) अणु
		अगर (ide_device_get(tape->drive))
			tape = शून्य;
		अन्यथा
			get_device(&tape->dev);
	पूर्ण

	mutex_unlock(&idetape_ref_mutex);
	वापस tape;
पूर्ण

अटल व्योम ide_tape_put(काष्ठा ide_tape_obj *tape)
अणु
	ide_drive_t *drive = tape->drive;

	mutex_lock(&idetape_ref_mutex);
	put_device(&tape->dev);
	ide_device_put(drive);
	mutex_unlock(&idetape_ref_mutex);
पूर्ण

/*
 * called on each failed packet command retry to analyze the request sense. We
 * currently करो not utilize this inक्रमmation.
 */
अटल व्योम idetape_analyze_error(ide_drive_t *drive)
अणु
	idetape_tape_t *tape = drive->driver_data;
	काष्ठा ide_atapi_pc *pc = drive->failed_pc;
	काष्ठा request *rq = drive->hwअगर->rq;
	u8 *sense = bio_data(rq->bio);

	tape->sense_key = sense[2] & 0xF;
	tape->asc       = sense[12];
	tape->ascq      = sense[13];

	ide_debug_log(IDE_DBG_FUNC,
		      "cmd: 0x%x, sense key = %x, asc = %x, ascq = %x",
		      rq->cmd[0], tape->sense_key, tape->asc, tape->ascq);

	/* correct reमुख्यing bytes to transfer */
	अगर (pc->flags & PC_FLAG_DMA_ERROR)
		scsi_req(rq)->resid_len = tape->blk_size * get_unaligned_be32(&sense[3]);

	/*
	 * If error was the result of a zero-length पढ़ो or ग_लिखो command,
	 * with sense key=5, asc=0x22, ascq=0, let it slide.  Some drives
	 * (i.e. Seagate STT3401A Travan) करोn't support 0-length पढ़ो/ग_लिखोs.
	 */
	अगर ((pc->c[0] == READ_6 || pc->c[0] == WRITE_6)
	    /* length == 0 */
	    && pc->c[4] == 0 && pc->c[3] == 0 && pc->c[2] == 0) अणु
		अगर (tape->sense_key == 5) अणु
			/* करोn't report an error, everything's ok */
			pc->error = 0;
			/* करोn't retry पढ़ो/ग_लिखो */
			pc->flags |= PC_FLAG_ABORT;
		पूर्ण
	पूर्ण
	अगर (pc->c[0] == READ_6 && (sense[2] & 0x80)) अणु
		pc->error = IDE_DRV_ERROR_खाताMARK;
		pc->flags |= PC_FLAG_ABORT;
	पूर्ण
	अगर (pc->c[0] == WRITE_6) अणु
		अगर ((sense[2] & 0x40) || (tape->sense_key == 0xd
		     && tape->asc == 0x0 && tape->ascq == 0x2)) अणु
			pc->error = IDE_DRV_ERROR_EOD;
			pc->flags |= PC_FLAG_ABORT;
		पूर्ण
	पूर्ण
	अगर (pc->c[0] == READ_6 || pc->c[0] == WRITE_6) अणु
		अगर (tape->sense_key == 8) अणु
			pc->error = IDE_DRV_ERROR_EOD;
			pc->flags |= PC_FLAG_ABORT;
		पूर्ण
		अगर (!(pc->flags & PC_FLAG_ABORT) &&
		    (blk_rq_bytes(rq) - scsi_req(rq)->resid_len))
			pc->retries = IDETAPE_MAX_PC_RETRIES + 1;
	पूर्ण
पूर्ण

अटल व्योम ide_tape_handle_dsc(ide_drive_t *);

अटल पूर्णांक ide_tape_callback(ide_drive_t *drive, पूर्णांक dsc)
अणु
	idetape_tape_t *tape = drive->driver_data;
	काष्ठा ide_atapi_pc *pc = drive->pc;
	काष्ठा request *rq = drive->hwअगर->rq;
	पूर्णांक uptodate = pc->error ? 0 : 1;
	पूर्णांक err = uptodate ? 0 : IDE_DRV_ERROR_GENERAL;

	ide_debug_log(IDE_DBG_FUNC, "cmd: 0x%x, dsc: %d, err: %d", rq->cmd[0],
		      dsc, err);

	अगर (dsc)
		ide_tape_handle_dsc(drive);

	अगर (drive->failed_pc == pc)
		drive->failed_pc = शून्य;

	अगर (pc->c[0] == REQUEST_SENSE) अणु
		अगर (uptodate)
			idetape_analyze_error(drive);
		अन्यथा
			prपूर्णांकk(KERN_ERR "ide-tape: Error in REQUEST SENSE "
					"itself - Aborting request!\n");
	पूर्ण अन्यथा अगर (pc->c[0] == READ_6 || pc->c[0] == WRITE_6) अणु
		अचिन्हित पूर्णांक blocks =
			(blk_rq_bytes(rq) - scsi_req(rq)->resid_len) / tape->blk_size;

		tape->avg_size += blocks * tape->blk_size;

		अगर (समय_after_eq(jअगरfies, tape->avg_समय + HZ)) अणु
			tape->avg_speed = tape->avg_size * HZ /
				(jअगरfies - tape->avg_समय) / 1024;
			tape->avg_size = 0;
			tape->avg_समय = jअगरfies;
		पूर्ण

		tape->first_frame += blocks;

		अगर (pc->error) अणु
			uptodate = 0;
			err = pc->error;
		पूर्ण
	पूर्ण
	scsi_req(rq)->result = err;

	वापस uptodate;
पूर्ण

/*
 * Postpone the current request so that ide.c will be able to service requests
 * from another device on the same port जबतक we are polling क्रम DSC.
 */
अटल व्योम ide_tape_stall_queue(ide_drive_t *drive)
अणु
	idetape_tape_t *tape = drive->driver_data;

	ide_debug_log(IDE_DBG_FUNC, "cmd: 0x%x, dsc_poll_freq: %lu",
		      drive->hwअगर->rq->cmd[0], tape->dsc_poll_freq);

	tape->postponed_rq = true;

	ide_stall_queue(drive, tape->dsc_poll_freq);
पूर्ण

अटल व्योम ide_tape_handle_dsc(ide_drive_t *drive)
अणु
	idetape_tape_t *tape = drive->driver_data;

	/* Media access command */
	tape->dsc_polling_start = jअगरfies;
	tape->dsc_poll_freq = IDETAPE_DSC_MA_FAST;
	tape->dsc_समयout = jअगरfies + IDETAPE_DSC_MA_TIMEOUT;
	/* Allow ide.c to handle other requests */
	ide_tape_stall_queue(drive);
पूर्ण

/*
 * Packet Command Interface
 *
 * The current Packet Command is available in drive->pc, and will not change
 * until we finish handling it. Each packet command is associated with a
 * callback function that will be called when the command is finished.
 *
 * The handling will be करोne in three stages:
 *
 * 1. ide_tape_issue_pc will send the packet command to the drive, and will set
 * the पूर्णांकerrupt handler to ide_pc_पूर्णांकr.
 *
 * 2. On each पूर्णांकerrupt, ide_pc_पूर्णांकr will be called. This step will be
 * repeated until the device संकेतs us that no more पूर्णांकerrupts will be issued.
 *
 * 3. ATAPI Tape media access commands have immediate status with a delayed
 * process. In हाल of a successful initiation of a media access packet command,
 * the DSC bit will be set when the actual execution of the command is finished.
 * Since the tape drive will not issue an पूर्णांकerrupt, we have to poll क्रम this
 * event. In this हाल, we define the request as "low priority request" by
 * setting rq_status to IDETAPE_RQ_POSTPONED, set a समयr to poll क्रम DSC and
 * निकास the driver.
 *
 * ide.c will then give higher priority to requests which originate from the
 * other device, until will change rq_status to RQ_ACTIVE.
 *
 * 4. When the packet command is finished, it will be checked क्रम errors.
 *
 * 5. In हाल an error was found, we queue a request sense packet command in
 * front of the request queue and retry the operation up to
 * IDETAPE_MAX_PC_RETRIES बार.
 *
 * 6. In हाल no error was found, or we decided to give up and not to retry
 * again, the callback function will be called and then we will handle the next
 * request.
 */

अटल ide_startstop_t ide_tape_issue_pc(ide_drive_t *drive,
					 काष्ठा ide_cmd *cmd,
					 काष्ठा ide_atapi_pc *pc)
अणु
	idetape_tape_t *tape = drive->driver_data;
	काष्ठा request *rq = drive->hwअगर->rq;

	अगर (drive->failed_pc == शून्य && pc->c[0] != REQUEST_SENSE)
		drive->failed_pc = pc;

	/* Set the current packet command */
	drive->pc = pc;

	अगर (pc->retries > IDETAPE_MAX_PC_RETRIES ||
		(pc->flags & PC_FLAG_ABORT)) अणु

		/*
		 * We will "abort" retrying a packet command in हाल legitimate
		 * error code was received (crossing a filemark, or end of the
		 * media, क्रम example).
		 */
		अगर (!(pc->flags & PC_FLAG_ABORT)) अणु
			अगर (!(pc->c[0] == TEST_UNIT_READY &&
			      tape->sense_key == 2 && tape->asc == 4 &&
			     (tape->ascq == 1 || tape->ascq == 8))) अणु
				prपूर्णांकk(KERN_ERR "ide-tape: %s: I/O error, "
						"pc = %2x, key = %2x, "
						"asc = %2x, ascq = %2x\n",
						tape->name, pc->c[0],
						tape->sense_key, tape->asc,
						tape->ascq);
			पूर्ण
			/* Giving up */
			pc->error = IDE_DRV_ERROR_GENERAL;
		पूर्ण

		drive->failed_pc = शून्य;
		drive->pc_callback(drive, 0);
		ide_complete_rq(drive, BLK_STS_IOERR, blk_rq_bytes(rq));
		वापस ide_stopped;
	पूर्ण
	ide_debug_log(IDE_DBG_SENSE, "retry #%d, cmd: 0x%02x", pc->retries,
		      pc->c[0]);

	pc->retries++;

	वापस ide_issue_pc(drive, cmd);
पूर्ण

/* A mode sense command is used to "sense" tape parameters. */
अटल व्योम idetape_create_mode_sense_cmd(काष्ठा ide_atapi_pc *pc, u8 page_code)
अणु
	ide_init_pc(pc);
	pc->c[0] = MODE_SENSE;
	अगर (page_code != IDETAPE_BLOCK_DESCRIPTOR)
		/* DBD = 1 - Don't वापस block descriptors */
		pc->c[1] = 8;
	pc->c[2] = page_code;
	/*
	 * Changed pc->c[3] to 0 (255 will at best वापस unused info).
	 *
	 * For SCSI this byte is defined as subpage instead of high byte
	 * of length and some IDE drives seem to पूर्णांकerpret it this way
	 * and वापस an error when 255 is used.
	 */
	pc->c[3] = 0;
	/* We will just discard data in that हाल */
	pc->c[4] = 255;
	अगर (page_code == IDETAPE_BLOCK_DESCRIPTOR)
		pc->req_xfer = 12;
	अन्यथा अगर (page_code == IDETAPE_CAPABILITIES_PAGE)
		pc->req_xfer = 24;
	अन्यथा
		pc->req_xfer = 50;
पूर्ण

अटल ide_startstop_t idetape_media_access_finished(ide_drive_t *drive)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	idetape_tape_t *tape = drive->driver_data;
	काष्ठा ide_atapi_pc *pc = drive->pc;
	u8 stat;

	stat = hwअगर->tp_ops->पढ़ो_status(hwअगर);

	अगर (stat & ATA_DSC) अणु
		अगर (stat & ATA_ERR) अणु
			/* Error detected */
			अगर (pc->c[0] != TEST_UNIT_READY)
				prपूर्णांकk(KERN_ERR "ide-tape: %s: I/O error, ",
						tape->name);
			/* Retry operation */
			ide_retry_pc(drive);
			वापस ide_stopped;
		पूर्ण
		pc->error = 0;
	पूर्ण अन्यथा अणु
		pc->error = IDE_DRV_ERROR_GENERAL;
		drive->failed_pc = शून्य;
	पूर्ण
	drive->pc_callback(drive, 0);
	वापस ide_stopped;
पूर्ण

अटल व्योम ide_tape_create_rw_cmd(idetape_tape_t *tape,
				   काष्ठा ide_atapi_pc *pc, काष्ठा request *rq,
				   u8 opcode)
अणु
	अचिन्हित पूर्णांक length = blk_rq_sectors(rq) / (tape->blk_size >> 9);

	ide_init_pc(pc);
	put_unaligned(cpu_to_be32(length), (अचिन्हित पूर्णांक *) &pc->c[1]);
	pc->c[1] = 1;

	अगर (blk_rq_bytes(rq) == tape->buffer_size)
		pc->flags |= PC_FLAG_DMA_OK;

	अगर (opcode == READ_6)
		pc->c[0] = READ_6;
	अन्यथा अगर (opcode == WRITE_6) अणु
		pc->c[0] = WRITE_6;
		pc->flags |= PC_FLAG_WRITING;
	पूर्ण

	स_नकल(scsi_req(rq)->cmd, pc->c, 12);
पूर्ण

अटल ide_startstop_t idetape_करो_request(ide_drive_t *drive,
					  काष्ठा request *rq, sector_t block)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	idetape_tape_t *tape = drive->driver_data;
	काष्ठा ide_atapi_pc *pc = शून्य;
	काष्ठा ide_cmd cmd;
	काष्ठा scsi_request *req = scsi_req(rq);
	u8 stat;

	ide_debug_log(IDE_DBG_RQ, "cmd: 0x%x, sector: %llu, nr_sectors: %u",
		      req->cmd[0], (अचिन्हित दीर्घ दीर्घ)blk_rq_pos(rq),
		      blk_rq_sectors(rq));

	BUG_ON(!blk_rq_is_निजी(rq));
	BUG_ON(ide_req(rq)->type != ATA_PRIV_MISC &&
	       ide_req(rq)->type != ATA_PRIV_SENSE);

	/* Retry a failed packet command */
	अगर (drive->failed_pc && drive->pc->c[0] == REQUEST_SENSE) अणु
		pc = drive->failed_pc;
		जाओ out;
	पूर्ण

	/*
	 * If the tape is still busy, postpone our request and service
	 * the other device meanजबतक.
	 */
	stat = hwअगर->tp_ops->पढ़ो_status(hwअगर);

	अगर ((drive->dev_flags & IDE_DFLAG_DSC_OVERLAP) == 0 &&
	    (req->cmd[13] & REQ_IDETAPE_PC2) == 0)
		drive->atapi_flags |= IDE_AFLAG_IGNORE_DSC;

	अगर (drive->dev_flags & IDE_DFLAG_POST_RESET) अणु
		drive->atapi_flags |= IDE_AFLAG_IGNORE_DSC;
		drive->dev_flags &= ~IDE_DFLAG_POST_RESET;
	पूर्ण

	अगर (!(drive->atapi_flags & IDE_AFLAG_IGNORE_DSC) &&
	    !(stat & ATA_DSC)) अणु
		अगर (!tape->postponed_rq) अणु
			tape->dsc_polling_start = jअगरfies;
			tape->dsc_poll_freq = tape->best_dsc_rw_freq;
			tape->dsc_समयout = jअगरfies + IDETAPE_DSC_RW_TIMEOUT;
		पूर्ण अन्यथा अगर (समय_after(jअगरfies, tape->dsc_समयout)) अणु
			prपूर्णांकk(KERN_ERR "ide-tape: %s: DSC timeout\n",
				tape->name);
			अगर (req->cmd[13] & REQ_IDETAPE_PC2) अणु
				idetape_media_access_finished(drive);
				वापस ide_stopped;
			पूर्ण अन्यथा अणु
				वापस ide_करो_reset(drive);
			पूर्ण
		पूर्ण अन्यथा अगर (समय_after(jअगरfies,
					tape->dsc_polling_start +
					IDETAPE_DSC_MA_THRESHOLD))
			tape->dsc_poll_freq = IDETAPE_DSC_MA_SLOW;
		ide_tape_stall_queue(drive);
		वापस ide_stopped;
	पूर्ण अन्यथा अणु
		drive->atapi_flags &= ~IDE_AFLAG_IGNORE_DSC;
		tape->postponed_rq = false;
	पूर्ण

	अगर (req->cmd[13] & REQ_IDETAPE_READ) अणु
		pc = &tape->queued_pc;
		ide_tape_create_rw_cmd(tape, pc, rq, READ_6);
		जाओ out;
	पूर्ण
	अगर (req->cmd[13] & REQ_IDETAPE_WRITE) अणु
		pc = &tape->queued_pc;
		ide_tape_create_rw_cmd(tape, pc, rq, WRITE_6);
		जाओ out;
	पूर्ण
	अगर (req->cmd[13] & REQ_IDETAPE_PC1) अणु
		pc = (काष्ठा ide_atapi_pc *)ide_req(rq)->special;
		req->cmd[13] &= ~(REQ_IDETAPE_PC1);
		req->cmd[13] |= REQ_IDETAPE_PC2;
		जाओ out;
	पूर्ण
	अगर (req->cmd[13] & REQ_IDETAPE_PC2) अणु
		idetape_media_access_finished(drive);
		वापस ide_stopped;
	पूर्ण
	BUG();

out:
	/* prepare sense request क्रम this command */
	ide_prep_sense(drive, rq);

	स_रखो(&cmd, 0, माप(cmd));

	अगर (rq_data_dir(rq))
		cmd.tf_flags |= IDE_TFLAG_WRITE;

	cmd.rq = rq;

	ide_init_sg_cmd(&cmd, blk_rq_bytes(rq));
	ide_map_sg(drive, &cmd);

	वापस ide_tape_issue_pc(drive, &cmd, pc);
पूर्ण

/*
 * Write a filemark अगर ग_लिखो_filemark=1. Flush the device buffers without
 * writing a filemark otherwise.
 */
अटल व्योम idetape_create_ग_लिखो_filemark_cmd(ide_drive_t *drive,
		काष्ठा ide_atapi_pc *pc, पूर्णांक ग_लिखो_filemark)
अणु
	ide_init_pc(pc);
	pc->c[0] = WRITE_खाताMARKS;
	pc->c[4] = ग_लिखो_filemark;
	pc->flags |= PC_FLAG_WAIT_FOR_DSC;
पूर्ण

अटल पूर्णांक idetape_रुको_पढ़ोy(ide_drive_t *drive, अचिन्हित दीर्घ समयout)
अणु
	idetape_tape_t *tape = drive->driver_data;
	काष्ठा gendisk *disk = tape->disk;
	पूर्णांक load_attempted = 0;

	/* Wait क्रम the tape to become पढ़ोy */
	set_bit(ilog2(IDE_AFLAG_MEDIUM_PRESENT), &drive->atapi_flags);
	समयout += jअगरfies;
	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		अगर (ide_करो_test_unit_पढ़ोy(drive, disk) == 0)
			वापस 0;
		अगर ((tape->sense_key == 2 && tape->asc == 4 && tape->ascq == 2)
		    || (tape->asc == 0x3A)) अणु
			/* no media */
			अगर (load_attempted)
				वापस -ENOMEDIUM;
			ide_करो_start_stop(drive, disk, IDETAPE_LU_LOAD_MASK);
			load_attempted = 1;
		/* not about to be पढ़ोy */
		पूर्ण अन्यथा अगर (!(tape->sense_key == 2 && tape->asc == 4 &&
			     (tape->ascq == 1 || tape->ascq == 8)))
			वापस -EIO;
		msleep(100);
	पूर्ण
	वापस -EIO;
पूर्ण

अटल पूर्णांक idetape_flush_tape_buffers(ide_drive_t *drive)
अणु
	काष्ठा ide_tape_obj *tape = drive->driver_data;
	काष्ठा ide_atapi_pc pc;
	पूर्णांक rc;

	idetape_create_ग_लिखो_filemark_cmd(drive, &pc, 0);
	rc = ide_queue_pc_tail(drive, tape->disk, &pc, शून्य, 0);
	अगर (rc)
		वापस rc;
	idetape_रुको_पढ़ोy(drive, 60 * 5 * HZ);
	वापस 0;
पूर्ण

अटल पूर्णांक ide_tape_पढ़ो_position(ide_drive_t *drive)
अणु
	idetape_tape_t *tape = drive->driver_data;
	काष्ठा ide_atapi_pc pc;
	u8 buf[20];

	ide_debug_log(IDE_DBG_FUNC, "enter");

	/* prep cmd */
	ide_init_pc(&pc);
	pc.c[0] = READ_POSITION;
	pc.req_xfer = 20;

	अगर (ide_queue_pc_tail(drive, tape->disk, &pc, buf, pc.req_xfer))
		वापस -1;

	अगर (!pc.error) अणु
		ide_debug_log(IDE_DBG_FUNC, "BOP - %s",
				(buf[0] & 0x80) ? "Yes" : "No");
		ide_debug_log(IDE_DBG_FUNC, "EOP - %s",
				(buf[0] & 0x40) ? "Yes" : "No");

		अगर (buf[0] & 0x4) अणु
			prपूर्णांकk(KERN_INFO "ide-tape: Block location is unknown"
					 "to the tape\n");
			clear_bit(ilog2(IDE_AFLAG_ADDRESS_VALID),
				  &drive->atapi_flags);
			वापस -1;
		पूर्ण अन्यथा अणु
			ide_debug_log(IDE_DBG_FUNC, "Block Location: %u",
				      be32_to_cpup((__be32 *)&buf[4]));

			tape->partition = buf[1];
			tape->first_frame = be32_to_cpup((__be32 *)&buf[4]);
			set_bit(ilog2(IDE_AFLAG_ADDRESS_VALID),
				&drive->atapi_flags);
		पूर्ण
	पूर्ण

	वापस tape->first_frame;
पूर्ण

अटल व्योम idetape_create_locate_cmd(ide_drive_t *drive,
		काष्ठा ide_atapi_pc *pc,
		अचिन्हित पूर्णांक block, u8 partition, पूर्णांक skip)
अणु
	ide_init_pc(pc);
	pc->c[0] = POSITION_TO_ELEMENT;
	pc->c[1] = 2;
	put_unaligned(cpu_to_be32(block), (अचिन्हित पूर्णांक *) &pc->c[3]);
	pc->c[8] = partition;
	pc->flags |= PC_FLAG_WAIT_FOR_DSC;
पूर्ण

अटल व्योम __ide_tape_discard_merge_buffer(ide_drive_t *drive)
अणु
	idetape_tape_t *tape = drive->driver_data;

	अगर (tape->chrdev_dir != IDETAPE_सूची_READ)
		वापस;

	clear_bit(ilog2(IDE_AFLAG_खाताMARK), &drive->atapi_flags);
	tape->valid = 0;
	अगर (tape->buf != शून्य) अणु
		kमुक्त(tape->buf);
		tape->buf = शून्य;
	पूर्ण

	tape->chrdev_dir = IDETAPE_सूची_NONE;
पूर्ण

/*
 * Position the tape to the requested block using the LOCATE packet command.
 * A READ POSITION command is then issued to check where we are positioned. Like
 * all higher level operations, we queue the commands at the tail of the request
 * queue and रुको क्रम their completion.
 */
अटल पूर्णांक idetape_position_tape(ide_drive_t *drive, अचिन्हित पूर्णांक block,
		u8 partition, पूर्णांक skip)
अणु
	idetape_tape_t *tape = drive->driver_data;
	काष्ठा gendisk *disk = tape->disk;
	पूर्णांक ret;
	काष्ठा ide_atapi_pc pc;

	अगर (tape->chrdev_dir == IDETAPE_सूची_READ)
		__ide_tape_discard_merge_buffer(drive);
	idetape_रुको_पढ़ोy(drive, 60 * 5 * HZ);
	idetape_create_locate_cmd(drive, &pc, block, partition, skip);
	ret = ide_queue_pc_tail(drive, disk, &pc, शून्य, 0);
	अगर (ret)
		वापस ret;

	ret = ide_tape_पढ़ो_position(drive);
	अगर (ret < 0)
		वापस ret;
	वापस 0;
पूर्ण

अटल व्योम ide_tape_discard_merge_buffer(ide_drive_t *drive,
					  पूर्णांक restore_position)
अणु
	idetape_tape_t *tape = drive->driver_data;
	पूर्णांक seek, position;

	__ide_tape_discard_merge_buffer(drive);
	अगर (restore_position) अणु
		position = ide_tape_पढ़ो_position(drive);
		seek = position > 0 ? position : 0;
		अगर (idetape_position_tape(drive, seek, 0, 0)) अणु
			prपूर्णांकk(KERN_INFO "ide-tape: %s: position_tape failed in"
					 " %s\n", tape->name, __func__);
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Generate a पढ़ो/ग_लिखो request क्रम the block device पूर्णांकerface and रुको क्रम it
 * to be serviced.
 */
अटल पूर्णांक idetape_queue_rw_tail(ide_drive_t *drive, पूर्णांक cmd, पूर्णांक size)
अणु
	idetape_tape_t *tape = drive->driver_data;
	काष्ठा request *rq;
	पूर्णांक ret;

	ide_debug_log(IDE_DBG_FUNC, "cmd: 0x%x, size: %d", cmd, size);

	BUG_ON(cmd != REQ_IDETAPE_READ && cmd != REQ_IDETAPE_WRITE);
	BUG_ON(size < 0 || size % tape->blk_size);

	rq = blk_get_request(drive->queue, REQ_OP_DRV_IN, 0);
	ide_req(rq)->type = ATA_PRIV_MISC;
	scsi_req(rq)->cmd[13] = cmd;
	rq->rq_disk = tape->disk;
	rq->__sector = tape->first_frame;

	अगर (size) अणु
		ret = blk_rq_map_kern(drive->queue, rq, tape->buf, size,
				      GFP_NOIO);
		अगर (ret)
			जाओ out_put;
	पूर्ण

	blk_execute_rq(tape->disk, rq, 0);

	/* calculate the number of transferred bytes and update buffer state */
	size -= scsi_req(rq)->resid_len;
	tape->cur = tape->buf;
	अगर (cmd == REQ_IDETAPE_READ)
		tape->valid = size;
	अन्यथा
		tape->valid = 0;

	ret = size;
	अगर (scsi_req(rq)->result == IDE_DRV_ERROR_GENERAL)
		ret = -EIO;
out_put:
	blk_put_request(rq);
	वापस ret;
पूर्ण

अटल व्योम idetape_create_inquiry_cmd(काष्ठा ide_atapi_pc *pc)
अणु
	ide_init_pc(pc);
	pc->c[0] = INQUIRY;
	pc->c[4] = 254;
	pc->req_xfer = 254;
पूर्ण

अटल व्योम idetape_create_शुरुआत_cmd(ide_drive_t *drive,
		काष्ठा ide_atapi_pc *pc)
अणु
	ide_init_pc(pc);
	pc->c[0] = REZERO_UNIT;
	pc->flags |= PC_FLAG_WAIT_FOR_DSC;
पूर्ण

अटल व्योम idetape_create_erase_cmd(काष्ठा ide_atapi_pc *pc)
अणु
	ide_init_pc(pc);
	pc->c[0] = ERASE;
	pc->c[1] = 1;
	pc->flags |= PC_FLAG_WAIT_FOR_DSC;
पूर्ण

अटल व्योम idetape_create_space_cmd(काष्ठा ide_atapi_pc *pc, पूर्णांक count, u8 cmd)
अणु
	ide_init_pc(pc);
	pc->c[0] = SPACE;
	put_unaligned(cpu_to_be32(count), (अचिन्हित पूर्णांक *) &pc->c[1]);
	pc->c[1] = cmd;
	pc->flags |= PC_FLAG_WAIT_FOR_DSC;
पूर्ण

अटल व्योम ide_tape_flush_merge_buffer(ide_drive_t *drive)
अणु
	idetape_tape_t *tape = drive->driver_data;

	अगर (tape->chrdev_dir != IDETAPE_सूची_WRITE) अणु
		prपूर्णांकk(KERN_ERR "ide-tape: bug: Trying to empty merge buffer"
				" but we are not writing.\n");
		वापस;
	पूर्ण
	अगर (tape->buf) अणु
		माप_प्रकार aligned = roundup(tape->valid, tape->blk_size);

		स_रखो(tape->cur, 0, aligned - tape->valid);
		idetape_queue_rw_tail(drive, REQ_IDETAPE_WRITE, aligned);
		kमुक्त(tape->buf);
		tape->buf = शून्य;
	पूर्ण
	tape->chrdev_dir = IDETAPE_सूची_NONE;
पूर्ण

अटल पूर्णांक idetape_init_rw(ide_drive_t *drive, पूर्णांक dir)
अणु
	idetape_tape_t *tape = drive->driver_data;
	पूर्णांक rc;

	BUG_ON(dir != IDETAPE_सूची_READ && dir != IDETAPE_सूची_WRITE);

	अगर (tape->chrdev_dir == dir)
		वापस 0;

	अगर (tape->chrdev_dir == IDETAPE_सूची_READ)
		ide_tape_discard_merge_buffer(drive, 1);
	अन्यथा अगर (tape->chrdev_dir == IDETAPE_सूची_WRITE) अणु
		ide_tape_flush_merge_buffer(drive);
		idetape_flush_tape_buffers(drive);
	पूर्ण

	अगर (tape->buf || tape->valid) अणु
		prपूर्णांकk(KERN_ERR "ide-tape: valid should be 0 now\n");
		tape->valid = 0;
	पूर्ण

	tape->buf = kदो_स्मृति(tape->buffer_size, GFP_KERNEL);
	अगर (!tape->buf)
		वापस -ENOMEM;
	tape->chrdev_dir = dir;
	tape->cur = tape->buf;

	/*
	 * Issue a 0 rw command to ensure that DSC handshake is
	 * चयनed from completion mode to buffer available mode.  No
	 * poपूर्णांक in issuing this अगर DSC overlap isn't supported, some
	 * drives (Seagate STT3401A) will वापस an error.
	 */
	अगर (drive->dev_flags & IDE_DFLAG_DSC_OVERLAP) अणु
		पूर्णांक cmd = dir == IDETAPE_सूची_READ ? REQ_IDETAPE_READ
						  : REQ_IDETAPE_WRITE;

		rc = idetape_queue_rw_tail(drive, cmd, 0);
		अगर (rc < 0) अणु
			kमुक्त(tape->buf);
			tape->buf = शून्य;
			tape->chrdev_dir = IDETAPE_सूची_NONE;
			वापस rc;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम idetape_pad_zeros(ide_drive_t *drive, पूर्णांक bcount)
अणु
	idetape_tape_t *tape = drive->driver_data;

	स_रखो(tape->buf, 0, tape->buffer_size);

	जबतक (bcount) अणु
		अचिन्हित पूर्णांक count = min(tape->buffer_size, bcount);

		idetape_queue_rw_tail(drive, REQ_IDETAPE_WRITE, count);
		bcount -= count;
	पूर्ण
पूर्ण

/*
 * Rewinds the tape to the Beginning Of the current Partition (BOP). We
 * currently support only one partition.
 */
अटल पूर्णांक idetape_शुरुआत_tape(ide_drive_t *drive)
अणु
	काष्ठा ide_tape_obj *tape = drive->driver_data;
	काष्ठा gendisk *disk = tape->disk;
	काष्ठा ide_atapi_pc pc;
	पूर्णांक ret;

	ide_debug_log(IDE_DBG_FUNC, "enter");

	idetape_create_शुरुआत_cmd(drive, &pc);
	ret = ide_queue_pc_tail(drive, disk, &pc, शून्य, 0);
	अगर (ret)
		वापस ret;

	ret = ide_tape_पढ़ो_position(drive);
	अगर (ret < 0)
		वापस ret;
	वापस 0;
पूर्ण

/* mtपन.स compatible commands should be issued to the chrdev पूर्णांकerface. */
अटल पूर्णांक idetape_blkdev_ioctl(ide_drive_t *drive, अचिन्हित पूर्णांक cmd,
				अचिन्हित दीर्घ arg)
अणु
	idetape_tape_t *tape = drive->driver_data;
	व्योम __user *argp = (व्योम __user *)arg;

	काष्ठा idetape_config अणु
		पूर्णांक dsc_rw_frequency;
		पूर्णांक dsc_media_access_frequency;
		पूर्णांक nr_stages;
	पूर्ण config;

	ide_debug_log(IDE_DBG_FUNC, "cmd: 0x%04x", cmd);

	चयन (cmd) अणु
	हाल 0x0340:
		अगर (copy_from_user(&config, argp, माप(config)))
			वापस -EFAULT;
		tape->best_dsc_rw_freq = config.dsc_rw_frequency;
		अवरोध;
	हाल 0x0350:
		स_रखो(&config, 0, माप(config));
		config.dsc_rw_frequency = (पूर्णांक) tape->best_dsc_rw_freq;
		config.nr_stages = 1;
		अगर (copy_to_user(argp, &config, माप(config)))
			वापस -EFAULT;
		अवरोध;
	शेष:
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक idetape_space_over_filemarks(ide_drive_t *drive, लघु mt_op,
					पूर्णांक mt_count)
अणु
	idetape_tape_t *tape = drive->driver_data;
	काष्ठा gendisk *disk = tape->disk;
	काष्ठा ide_atapi_pc pc;
	पूर्णांक retval, count = 0;
	पूर्णांक sprev = !!(tape->caps[4] & 0x20);


	ide_debug_log(IDE_DBG_FUNC, "mt_op: %d, mt_count: %d", mt_op, mt_count);

	अगर (mt_count == 0)
		वापस 0;
	अगर (MTBSF == mt_op || MTBSFM == mt_op) अणु
		अगर (!sprev)
			वापस -EIO;
		mt_count = -mt_count;
	पूर्ण

	अगर (tape->chrdev_dir == IDETAPE_सूची_READ) अणु
		tape->valid = 0;
		अगर (test_and_clear_bit(ilog2(IDE_AFLAG_खाताMARK),
				       &drive->atapi_flags))
			++count;
		ide_tape_discard_merge_buffer(drive, 0);
	पूर्ण

	चयन (mt_op) अणु
	हाल MTFSF:
	हाल MTBSF:
		idetape_create_space_cmd(&pc, mt_count - count,
					 IDETAPE_SPACE_OVER_खाताMARK);
		वापस ide_queue_pc_tail(drive, disk, &pc, शून्य, 0);
	हाल MTFSFM:
	हाल MTBSFM:
		अगर (!sprev)
			वापस -EIO;
		retval = idetape_space_over_filemarks(drive, MTFSF,
						      mt_count - count);
		अगर (retval)
			वापस retval;
		count = (MTBSFM == mt_op ? 1 : -1);
		वापस idetape_space_over_filemarks(drive, MTFSF, count);
	शेष:
		prपूर्णांकk(KERN_ERR "ide-tape: MTIO operation %d not supported\n",
				mt_op);
		वापस -EIO;
	पूर्ण
पूर्ण

/*
 * Our अक्षरacter device पढ़ो / ग_लिखो functions.
 *
 * The tape is optimized to maximize throughput when it is transferring an
 * पूर्णांकegral number of the "continuous transfer limit", which is a parameter of
 * the specअगरic tape (26kB on my particular tape, 32kB क्रम Onstream).
 *
 * As of version 1.3 of the driver, the अक्षरacter device provides an असलtract
 * continuous view of the media - any mix of block sizes (even 1 byte) on the
 * same backup/restore procedure is supported. The driver will पूर्णांकernally
 * convert the requests to the recommended transfer unit, so that an unmatch
 * between the user's block size to the recommended size will only result in a
 * (slightly) increased driver overhead, but will no दीर्घer hit perक्रमmance.
 * This is not applicable to Onstream.
 */
अटल sमाप_प्रकार idetape_chrdev_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ide_tape_obj *tape = file->निजी_data;
	ide_drive_t *drive = tape->drive;
	माप_प्रकार करोne = 0;
	sमाप_प्रकार ret = 0;
	पूर्णांक rc;

	ide_debug_log(IDE_DBG_FUNC, "count %zd", count);

	अगर (tape->chrdev_dir != IDETAPE_सूची_READ) अणु
		अगर (test_bit(ilog2(IDE_AFLAG_DETECT_BS), &drive->atapi_flags))
			अगर (count > tape->blk_size &&
			    (count % tape->blk_size) == 0)
				tape->user_bs_factor = count / tape->blk_size;
	पूर्ण

	rc = idetape_init_rw(drive, IDETAPE_सूची_READ);
	अगर (rc < 0)
		वापस rc;

	जबतक (करोne < count) अणु
		माप_प्रकार toकरो;

		/* refill अगर staging buffer is empty */
		अगर (!tape->valid) अणु
			/* If we are at a filemark, nothing more to पढ़ो */
			अगर (test_bit(ilog2(IDE_AFLAG_खाताMARK),
				     &drive->atapi_flags))
				अवरोध;
			/* पढ़ो */
			अगर (idetape_queue_rw_tail(drive, REQ_IDETAPE_READ,
						  tape->buffer_size) <= 0)
				अवरोध;
		पूर्ण

		/* copy out */
		toकरो = min_t(माप_प्रकार, count - करोne, tape->valid);
		अगर (copy_to_user(buf + करोne, tape->cur, toकरो))
			ret = -EFAULT;

		tape->cur += toकरो;
		tape->valid -= toकरो;
		करोne += toकरो;
	पूर्ण

	अगर (!करोne && test_bit(ilog2(IDE_AFLAG_खाताMARK), &drive->atapi_flags)) अणु
		idetape_space_over_filemarks(drive, MTFSF, 1);
		वापस 0;
	पूर्ण

	वापस ret ? ret : करोne;
पूर्ण

अटल sमाप_प्रकार idetape_chrdev_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
				     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ide_tape_obj *tape = file->निजी_data;
	ide_drive_t *drive = tape->drive;
	माप_प्रकार करोne = 0;
	sमाप_प्रकार ret = 0;
	पूर्णांक rc;

	/* The drive is ग_लिखो रक्षित. */
	अगर (tape->ग_लिखो_prot)
		वापस -EACCES;

	ide_debug_log(IDE_DBG_FUNC, "count %zd", count);

	/* Initialize ग_लिखो operation */
	rc = idetape_init_rw(drive, IDETAPE_सूची_WRITE);
	अगर (rc < 0)
		वापस rc;

	जबतक (करोne < count) अणु
		माप_प्रकार toकरो;

		/* flush अगर staging buffer is full */
		अगर (tape->valid == tape->buffer_size &&
		    idetape_queue_rw_tail(drive, REQ_IDETAPE_WRITE,
					  tape->buffer_size) <= 0)
			वापस rc;

		/* copy in */
		toकरो = min_t(माप_प्रकार, count - करोne,
			     tape->buffer_size - tape->valid);
		अगर (copy_from_user(tape->cur, buf + करोne, toकरो))
			ret = -EFAULT;

		tape->cur += toकरो;
		tape->valid += toकरो;
		करोne += toकरो;
	पूर्ण

	वापस ret ? ret : करोne;
पूर्ण

अटल पूर्णांक idetape_ग_लिखो_filemark(ide_drive_t *drive)
अणु
	काष्ठा ide_tape_obj *tape = drive->driver_data;
	काष्ठा ide_atapi_pc pc;

	/* Write a filemark */
	idetape_create_ग_लिखो_filemark_cmd(drive, &pc, 1);
	अगर (ide_queue_pc_tail(drive, tape->disk, &pc, शून्य, 0)) अणु
		prपूर्णांकk(KERN_ERR "ide-tape: Couldn't write a filemark\n");
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Called from idetape_chrdev_ioctl when the general mtio MTIOCTOP ioctl is
 * requested.
 *
 * Note: MTBSF and MTBSFM are not supported when the tape करोesn't support
 * spacing over filemarks in the reverse direction. In this हाल, MTFSFM is also
 * usually not supported.
 *
 * The following commands are currently not supported:
 *
 * MTFSS, MTBSS, MTWSM, MTSETDENSITY, MTSETDRVBUFFER, MT_ST_BOOLEANS,
 * MT_ST_WRITE_THRESHOLD.
 */
अटल पूर्णांक idetape_mtioctop(ide_drive_t *drive, लघु mt_op, पूर्णांक mt_count)
अणु
	idetape_tape_t *tape = drive->driver_data;
	काष्ठा gendisk *disk = tape->disk;
	काष्ठा ide_atapi_pc pc;
	पूर्णांक i, retval;

	ide_debug_log(IDE_DBG_FUNC, "MTIOCTOP ioctl: mt_op: %d, mt_count: %d",
		      mt_op, mt_count);

	चयन (mt_op) अणु
	हाल MTFSF:
	हाल MTFSFM:
	हाल MTBSF:
	हाल MTBSFM:
		अगर (!mt_count)
			वापस 0;
		वापस idetape_space_over_filemarks(drive, mt_op, mt_count);
	शेष:
		अवरोध;
	पूर्ण

	चयन (mt_op) अणु
	हाल MTWखातापूर्ण:
		अगर (tape->ग_लिखो_prot)
			वापस -EACCES;
		ide_tape_discard_merge_buffer(drive, 1);
		क्रम (i = 0; i < mt_count; i++) अणु
			retval = idetape_ग_लिखो_filemark(drive);
			अगर (retval)
				वापस retval;
		पूर्ण
		वापस 0;
	हाल MTREW:
		ide_tape_discard_merge_buffer(drive, 0);
		अगर (idetape_शुरुआत_tape(drive))
			वापस -EIO;
		वापस 0;
	हाल MTLOAD:
		ide_tape_discard_merge_buffer(drive, 0);
		वापस ide_करो_start_stop(drive, disk, IDETAPE_LU_LOAD_MASK);
	हाल MTUNLOAD:
	हाल MTOFFL:
		/*
		 * If करोor is locked, attempt to unlock beक्रमe
		 * attempting to eject.
		 */
		अगर (tape->करोor_locked) अणु
			अगर (!ide_set_media_lock(drive, disk, 0))
				tape->करोor_locked = DOOR_UNLOCKED;
		पूर्ण
		ide_tape_discard_merge_buffer(drive, 0);
		retval = ide_करो_start_stop(drive, disk, !IDETAPE_LU_LOAD_MASK);
		अगर (!retval)
			clear_bit(ilog2(IDE_AFLAG_MEDIUM_PRESENT),
				  &drive->atapi_flags);
		वापस retval;
	हाल MTNOP:
		ide_tape_discard_merge_buffer(drive, 0);
		वापस idetape_flush_tape_buffers(drive);
	हाल MTRETEN:
		ide_tape_discard_merge_buffer(drive, 0);
		वापस ide_करो_start_stop(drive, disk,
			IDETAPE_LU_RETENSION_MASK | IDETAPE_LU_LOAD_MASK);
	हाल MTEOM:
		idetape_create_space_cmd(&pc, 0, IDETAPE_SPACE_TO_EOD);
		वापस ide_queue_pc_tail(drive, disk, &pc, शून्य, 0);
	हाल MTERASE:
		(व्योम)idetape_शुरुआत_tape(drive);
		idetape_create_erase_cmd(&pc);
		वापस ide_queue_pc_tail(drive, disk, &pc, शून्य, 0);
	हाल MTSETBLK:
		अगर (mt_count) अणु
			अगर (mt_count < tape->blk_size ||
			    mt_count % tape->blk_size)
				वापस -EIO;
			tape->user_bs_factor = mt_count / tape->blk_size;
			clear_bit(ilog2(IDE_AFLAG_DETECT_BS),
				  &drive->atapi_flags);
		पूर्ण अन्यथा
			set_bit(ilog2(IDE_AFLAG_DETECT_BS),
				&drive->atapi_flags);
		वापस 0;
	हाल MTSEEK:
		ide_tape_discard_merge_buffer(drive, 0);
		वापस idetape_position_tape(drive,
			mt_count * tape->user_bs_factor, tape->partition, 0);
	हाल MTSETPART:
		ide_tape_discard_merge_buffer(drive, 0);
		वापस idetape_position_tape(drive, 0, mt_count, 0);
	हाल MTFSR:
	हाल MTBSR:
	हाल MTLOCK:
		retval = ide_set_media_lock(drive, disk, 1);
		अगर (retval)
			वापस retval;
		tape->करोor_locked = DOOR_EXPLICITLY_LOCKED;
		वापस 0;
	हाल MTUNLOCK:
		retval = ide_set_media_lock(drive, disk, 0);
		अगर (retval)
			वापस retval;
		tape->करोor_locked = DOOR_UNLOCKED;
		वापस 0;
	शेष:
		prपूर्णांकk(KERN_ERR "ide-tape: MTIO operation %d not supported\n",
				mt_op);
		वापस -EIO;
	पूर्ण
पूर्ण

/*
 * Our अक्षरacter device ioctls. General mtपन.स magnetic io commands are
 * supported here, and not in the corresponding block पूर्णांकerface. Our own
 * ide-tape ioctls are supported on both पूर्णांकerfaces.
 */
अटल दीर्घ करो_idetape_chrdev_ioctl(काष्ठा file *file,
				अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा ide_tape_obj *tape = file->निजी_data;
	ide_drive_t *drive = tape->drive;
	काष्ठा mtop mtop;
	काष्ठा mtget mtget;
	काष्ठा mtpos mtpos;
	पूर्णांक block_offset = 0, position = tape->first_frame;
	व्योम __user *argp = (व्योम __user *)arg;

	ide_debug_log(IDE_DBG_FUNC, "cmd: 0x%x", cmd);

	अगर (tape->chrdev_dir == IDETAPE_सूची_WRITE) अणु
		ide_tape_flush_merge_buffer(drive);
		idetape_flush_tape_buffers(drive);
	पूर्ण
	अगर (cmd == MTIOCGET || cmd == MTIOCPOS) अणु
		block_offset = tape->valid /
			(tape->blk_size * tape->user_bs_factor);
		position = ide_tape_पढ़ो_position(drive);
		अगर (position < 0)
			वापस -EIO;
	पूर्ण
	चयन (cmd) अणु
	हाल MTIOCTOP:
		अगर (copy_from_user(&mtop, argp, माप(काष्ठा mtop)))
			वापस -EFAULT;
		वापस idetape_mtioctop(drive, mtop.mt_op, mtop.mt_count);
	हाल MTIOCGET:
		स_रखो(&mtget, 0, माप(काष्ठा mtget));
		mtget.mt_type = MT_ISSCSI2;
		mtget.mt_blkno = position / tape->user_bs_factor - block_offset;
		mtget.mt_dsreg =
			((tape->blk_size * tape->user_bs_factor)
			 << MT_ST_BLKSIZE_SHIFT) & MT_ST_BLKSIZE_MASK;

		अगर (tape->drv_ग_लिखो_prot)
			mtget.mt_gstat |= GMT_WR_PROT(0xffffffff);

		वापस put_user_mtget(argp, &mtget);
	हाल MTIOCPOS:
		mtpos.mt_blkno = position / tape->user_bs_factor - block_offset;
		वापस put_user_mtpos(argp, &mtpos);
	शेष:
		अगर (tape->chrdev_dir == IDETAPE_सूची_READ)
			ide_tape_discard_merge_buffer(drive, 1);
		वापस idetape_blkdev_ioctl(drive, cmd, arg);
	पूर्ण
पूर्ण

अटल दीर्घ idetape_chrdev_ioctl(काष्ठा file *file,
				अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	दीर्घ ret;
	mutex_lock(&ide_tape_mutex);
	ret = करो_idetape_chrdev_ioctl(file, cmd, arg);
	mutex_unlock(&ide_tape_mutex);
	वापस ret;
पूर्ण

अटल दीर्घ idetape_chrdev_compat_ioctl(काष्ठा file *file,
				अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	दीर्घ ret;

	अगर (cmd == MTIOCPOS32)
		cmd = MTIOCPOS;
	अन्यथा अगर (cmd == MTIOCGET32)
		cmd = MTIOCGET;

	mutex_lock(&ide_tape_mutex);
	ret = करो_idetape_chrdev_ioctl(file, cmd, arg);
	mutex_unlock(&ide_tape_mutex);
	वापस ret;
पूर्ण

/*
 * Do a mode sense page 0 with block descriptor and अगर it succeeds set the tape
 * block size with the reported value.
 */
अटल व्योम ide_tape_get_bsize_from_bdesc(ide_drive_t *drive)
अणु
	idetape_tape_t *tape = drive->driver_data;
	काष्ठा ide_atapi_pc pc;
	u8 buf[12];

	idetape_create_mode_sense_cmd(&pc, IDETAPE_BLOCK_DESCRIPTOR);
	अगर (ide_queue_pc_tail(drive, tape->disk, &pc, buf, pc.req_xfer)) अणु
		prपूर्णांकk(KERN_ERR "ide-tape: Can't get block descriptor\n");
		अगर (tape->blk_size == 0) अणु
			prपूर्णांकk(KERN_WARNING "ide-tape: Cannot deal with zero "
					    "block size, assuming 32k\n");
			tape->blk_size = 32768;
		पूर्ण
		वापस;
	पूर्ण
	tape->blk_size = (buf[4 + 5] << 16) +
				(buf[4 + 6] << 8)  +
				 buf[4 + 7];
	tape->drv_ग_लिखो_prot = (buf[2] & 0x80) >> 7;

	ide_debug_log(IDE_DBG_FUNC, "blk_size: %d, write_prot: %d",
		      tape->blk_size, tape->drv_ग_लिखो_prot);
पूर्ण

अटल पूर्णांक idetape_chrdev_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	अचिन्हित पूर्णांक minor = iminor(inode), i = minor & ~0xc0;
	ide_drive_t *drive;
	idetape_tape_t *tape;
	पूर्णांक retval;

	अगर (i >= MAX_HWIFS * MAX_DRIVES)
		वापस -ENXIO;

	mutex_lock(&idetape_chrdev_mutex);

	tape = ide_tape_get(शून्य, true, i);
	अगर (!tape) अणु
		mutex_unlock(&idetape_chrdev_mutex);
		वापस -ENXIO;
	पूर्ण

	drive = tape->drive;
	filp->निजी_data = tape;

	ide_debug_log(IDE_DBG_FUNC, "enter");

	/*
	 * We really want to करो nonseekable_खोलो(inode, filp); here, but some
	 * versions of tar incorrectly call lseek on tapes and bail out अगर that
	 * fails.  So we disallow pपढ़ो() and pग_लिखो(), but permit lseeks.
	 */
	filp->f_mode &= ~(FMODE_PREAD | FMODE_PWRITE);


	अगर (test_and_set_bit(ilog2(IDE_AFLAG_BUSY), &drive->atapi_flags)) अणु
		retval = -EBUSY;
		जाओ out_put_tape;
	पूर्ण

	retval = idetape_रुको_पढ़ोy(drive, 60 * HZ);
	अगर (retval) अणु
		clear_bit(ilog2(IDE_AFLAG_BUSY), &drive->atapi_flags);
		prपूर्णांकk(KERN_ERR "ide-tape: %s: drive not ready\n", tape->name);
		जाओ out_put_tape;
	पूर्ण

	ide_tape_पढ़ो_position(drive);
	अगर (!test_bit(ilog2(IDE_AFLAG_ADDRESS_VALID), &drive->atapi_flags))
		(व्योम)idetape_शुरुआत_tape(drive);

	/* Read block size and ग_लिखो protect status from drive. */
	ide_tape_get_bsize_from_bdesc(drive);

	/* Set ग_लिखो protect flag अगर device is खोलोed as पढ़ो-only. */
	अगर ((filp->f_flags & O_ACCMODE) == O_RDONLY)
		tape->ग_लिखो_prot = 1;
	अन्यथा
		tape->ग_लिखो_prot = tape->drv_ग_लिखो_prot;

	/* Make sure drive isn't ग_लिखो रक्षित अगर user wants to ग_लिखो. */
	अगर (tape->ग_लिखो_prot) अणु
		अगर ((filp->f_flags & O_ACCMODE) == O_WRONLY ||
		    (filp->f_flags & O_ACCMODE) == O_RDWR) अणु
			clear_bit(ilog2(IDE_AFLAG_BUSY), &drive->atapi_flags);
			retval = -EROFS;
			जाओ out_put_tape;
		पूर्ण
	पूर्ण

	/* Lock the tape drive करोor so user can't eject. */
	अगर (tape->chrdev_dir == IDETAPE_सूची_NONE) अणु
		अगर (!ide_set_media_lock(drive, tape->disk, 1)) अणु
			अगर (tape->करोor_locked != DOOR_EXPLICITLY_LOCKED)
				tape->करोor_locked = DOOR_LOCKED;
		पूर्ण
	पूर्ण
	mutex_unlock(&idetape_chrdev_mutex);

	वापस 0;

out_put_tape:
	ide_tape_put(tape);

	mutex_unlock(&idetape_chrdev_mutex);

	वापस retval;
पूर्ण

अटल व्योम idetape_ग_लिखो_release(ide_drive_t *drive, अचिन्हित पूर्णांक minor)
अणु
	idetape_tape_t *tape = drive->driver_data;

	ide_tape_flush_merge_buffer(drive);
	tape->buf = kदो_स्मृति(tape->buffer_size, GFP_KERNEL);
	अगर (tape->buf != शून्य) अणु
		idetape_pad_zeros(drive, tape->blk_size *
				(tape->user_bs_factor - 1));
		kमुक्त(tape->buf);
		tape->buf = शून्य;
	पूर्ण
	idetape_ग_लिखो_filemark(drive);
	idetape_flush_tape_buffers(drive);
	idetape_flush_tape_buffers(drive);
पूर्ण

अटल पूर्णांक idetape_chrdev_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा ide_tape_obj *tape = filp->निजी_data;
	ide_drive_t *drive = tape->drive;
	अचिन्हित पूर्णांक minor = iminor(inode);

	mutex_lock(&idetape_chrdev_mutex);

	tape = drive->driver_data;

	ide_debug_log(IDE_DBG_FUNC, "enter");

	अगर (tape->chrdev_dir == IDETAPE_सूची_WRITE)
		idetape_ग_लिखो_release(drive, minor);
	अगर (tape->chrdev_dir == IDETAPE_सूची_READ) अणु
		अगर (minor < 128)
			ide_tape_discard_merge_buffer(drive, 1);
	पूर्ण

	अगर (minor < 128 && test_bit(ilog2(IDE_AFLAG_MEDIUM_PRESENT),
				    &drive->atapi_flags))
		(व्योम) idetape_शुरुआत_tape(drive);

	अगर (tape->chrdev_dir == IDETAPE_सूची_NONE) अणु
		अगर (tape->करोor_locked == DOOR_LOCKED) अणु
			अगर (!ide_set_media_lock(drive, tape->disk, 0))
				tape->करोor_locked = DOOR_UNLOCKED;
		पूर्ण
	पूर्ण
	clear_bit(ilog2(IDE_AFLAG_BUSY), &drive->atapi_flags);
	ide_tape_put(tape);

	mutex_unlock(&idetape_chrdev_mutex);

	वापस 0;
पूर्ण

अटल व्योम idetape_get_inquiry_results(ide_drive_t *drive)
अणु
	idetape_tape_t *tape = drive->driver_data;
	काष्ठा ide_atapi_pc pc;
	u8 pc_buf[256];
	अक्षर fw_rev[4], venकरोr_id[8], product_id[16];

	idetape_create_inquiry_cmd(&pc);
	अगर (ide_queue_pc_tail(drive, tape->disk, &pc, pc_buf, pc.req_xfer)) अणु
		prपूर्णांकk(KERN_ERR "ide-tape: %s: can't get INQUIRY results\n",
				tape->name);
		वापस;
	पूर्ण
	स_नकल(venकरोr_id, &pc_buf[8], 8);
	स_नकल(product_id, &pc_buf[16], 16);
	स_नकल(fw_rev, &pc_buf[32], 4);

	ide_fixstring(venकरोr_id, 8, 0);
	ide_fixstring(product_id, 16, 0);
	ide_fixstring(fw_rev, 4, 0);

	prपूर्णांकk(KERN_INFO "ide-tape: %s <-> %s: %.8s %.16s rev %.4s\n",
			drive->name, tape->name, venकरोr_id, product_id, fw_rev);
पूर्ण

/*
 * Ask the tape about its various parameters. In particular, we will adjust our
 * data transfer buffer	size to the recommended value as वापसed by the tape.
 */
अटल व्योम idetape_get_mode_sense_results(ide_drive_t *drive)
अणु
	idetape_tape_t *tape = drive->driver_data;
	काष्ठा ide_atapi_pc pc;
	u8 buf[24], *caps;
	u8 speed, max_speed;

	idetape_create_mode_sense_cmd(&pc, IDETAPE_CAPABILITIES_PAGE);
	अगर (ide_queue_pc_tail(drive, tape->disk, &pc, buf, pc.req_xfer)) अणु
		prपूर्णांकk(KERN_ERR "ide-tape: Can't get tape parameters - assuming"
				" some default values\n");
		tape->blk_size = 512;
		put_unaligned(52,   (u16 *)&tape->caps[12]);
		put_unaligned(540,  (u16 *)&tape->caps[14]);
		put_unaligned(6*52, (u16 *)&tape->caps[16]);
		वापस;
	पूर्ण
	caps = buf + 4 + buf[3];

	/* convert to host order and save क्रम later use */
	speed = be16_to_cpup((__be16 *)&caps[14]);
	max_speed = be16_to_cpup((__be16 *)&caps[8]);

	*(u16 *)&caps[8] = max_speed;
	*(u16 *)&caps[12] = be16_to_cpup((__be16 *)&caps[12]);
	*(u16 *)&caps[14] = speed;
	*(u16 *)&caps[16] = be16_to_cpup((__be16 *)&caps[16]);

	अगर (!speed) अणु
		prपूर्णांकk(KERN_INFO "ide-tape: %s: invalid tape speed "
				"(assuming 650KB/sec)\n", drive->name);
		*(u16 *)&caps[14] = 650;
	पूर्ण
	अगर (!max_speed) अणु
		prपूर्णांकk(KERN_INFO "ide-tape: %s: invalid max_speed "
				"(assuming 650KB/sec)\n", drive->name);
		*(u16 *)&caps[8] = 650;
	पूर्ण

	स_नकल(&tape->caps, caps, 20);

	/* device lacks locking support according to capabilities page */
	अगर ((caps[6] & 1) == 0)
		drive->dev_flags &= ~IDE_DFLAG_DOORLOCKING;

	अगर (caps[7] & 0x02)
		tape->blk_size = 512;
	अन्यथा अगर (caps[7] & 0x04)
		tape->blk_size = 1024;
पूर्ण

#अगर_घोषित CONFIG_IDE_PROC_FS
#घोषणा ide_tape_devset_get(name, field) \
अटल पूर्णांक get_##name(ide_drive_t *drive) \
अणु \
	idetape_tape_t *tape = drive->driver_data; \
	वापस tape->field; \
पूर्ण

#घोषणा ide_tape_devset_set(name, field) \
अटल पूर्णांक set_##name(ide_drive_t *drive, पूर्णांक arg) \
अणु \
	idetape_tape_t *tape = drive->driver_data; \
	tape->field = arg; \
	वापस 0; \
पूर्ण

#घोषणा ide_tape_devset_rw_field(_name, _field) \
ide_tape_devset_get(_name, _field) \
ide_tape_devset_set(_name, _field) \
IDE_DEVSET(_name, DS_SYNC, get_##_name, set_##_name)

#घोषणा ide_tape_devset_r_field(_name, _field) \
ide_tape_devset_get(_name, _field) \
IDE_DEVSET(_name, 0, get_##_name, शून्य)

अटल पूर्णांक mulf_tdsc(ide_drive_t *drive)	अणु वापस 1000; पूर्ण
अटल पूर्णांक भागf_tdsc(ide_drive_t *drive)	अणु वापस   HZ; पूर्ण
अटल पूर्णांक भागf_buffer(ide_drive_t *drive)	अणु वापस    2; पूर्ण
अटल पूर्णांक भागf_buffer_size(ide_drive_t *drive)	अणु वापस 1024; पूर्ण

ide_devset_rw_flag(dsc_overlap, IDE_DFLAG_DSC_OVERLAP);

ide_tape_devset_rw_field(tdsc, best_dsc_rw_freq);

ide_tape_devset_r_field(avg_speed, avg_speed);
ide_tape_devset_r_field(speed, caps[14]);
ide_tape_devset_r_field(buffer, caps[16]);
ide_tape_devset_r_field(buffer_size, buffer_size);

अटल स्थिर काष्ठा ide_proc_devset idetape_settings[] = अणु
	__IDE_PROC_DEVSET(avg_speed,	0, 0xffff, शून्य, शून्य),
	__IDE_PROC_DEVSET(buffer,	0, 0xffff, शून्य, भागf_buffer),
	__IDE_PROC_DEVSET(buffer_size,	0, 0xffff, शून्य, भागf_buffer_size),
	__IDE_PROC_DEVSET(dsc_overlap,	0,      1, शून्य, शून्य),
	__IDE_PROC_DEVSET(speed,	0, 0xffff, शून्य, शून्य),
	__IDE_PROC_DEVSET(tdsc,		IDETAPE_DSC_RW_MIN, IDETAPE_DSC_RW_MAX,
					mulf_tdsc, भागf_tdsc),
	अणु शून्य पूर्ण,
पूर्ण;
#पूर्ण_अगर

/*
 * The function below is called to:
 *
 * 1. Initialize our various state variables.
 * 2. Ask the tape क्रम its capabilities.
 * 3. Allocate a buffer which will be used क्रम data transfer. The buffer size
 * is chosen based on the recommendation which we received in step 2.
 *
 * Note that at this poपूर्णांक ide.c alपढ़ोy asचिन्हित us an irq, so that we can
 * queue requests here and रुको क्रम their completion.
 */
अटल व्योम idetape_setup(ide_drive_t *drive, idetape_tape_t *tape, पूर्णांक minor)
अणु
	अचिन्हित दीर्घ t;
	पूर्णांक speed;
	u16 *ctl = (u16 *)&tape->caps[12];

	ide_debug_log(IDE_DBG_FUNC, "minor: %d", minor);

	drive->pc_callback = ide_tape_callback;

	drive->dev_flags |= IDE_DFLAG_DSC_OVERLAP;

	अगर (drive->hwअगर->host_flags & IDE_HFLAG_NO_DSC) अणु
		prपूर्णांकk(KERN_INFO "ide-tape: %s: disabling DSC overlap\n",
				 tape->name);
		drive->dev_flags &= ~IDE_DFLAG_DSC_OVERLAP;
	पूर्ण

	/* Seagate Travan drives करो not support DSC overlap. */
	अगर (म_माला((अक्षर *)&drive->id[ATA_ID_PROD], "Seagate STT3401"))
		drive->dev_flags &= ~IDE_DFLAG_DSC_OVERLAP;

	tape->minor = minor;
	tape->name[0] = 'h';
	tape->name[1] = 't';
	tape->name[2] = '0' + minor;
	tape->chrdev_dir = IDETAPE_सूची_NONE;

	idetape_get_inquiry_results(drive);
	idetape_get_mode_sense_results(drive);
	ide_tape_get_bsize_from_bdesc(drive);
	tape->user_bs_factor = 1;
	tape->buffer_size = *ctl * tape->blk_size;
	जबतक (tape->buffer_size > 0xffff) अणु
		prपूर्णांकk(KERN_NOTICE "ide-tape: decreasing stage size\n");
		*ctl /= 2;
		tape->buffer_size = *ctl * tape->blk_size;
	पूर्ण

	/* select the "best" DSC पढ़ो/ग_लिखो polling freq */
	speed = max(*(u16 *)&tape->caps[14], *(u16 *)&tape->caps[8]);

	t = (IDETAPE_FIFO_THRESHOLD * tape->buffer_size * HZ) / (speed * 1000);

	/*
	 * Ensure that the number we got makes sense; limit it within
	 * IDETAPE_DSC_RW_MIN and IDETAPE_DSC_RW_MAX.
	 */
	tape->best_dsc_rw_freq = clamp_t(अचिन्हित दीर्घ, t, IDETAPE_DSC_RW_MIN,
					 IDETAPE_DSC_RW_MAX);
	prपूर्णांकk(KERN_INFO "ide-tape: %s <-> %s: %dKBps, %d*%dkB buffer, "
		"%ums tDSC%s\n",
		drive->name, tape->name, *(u16 *)&tape->caps[14],
		(*(u16 *)&tape->caps[16] * 512) / tape->buffer_size,
		tape->buffer_size / 1024,
		jअगरfies_to_msecs(tape->best_dsc_rw_freq),
		(drive->dev_flags & IDE_DFLAG_USING_DMA) ? ", DMA" : "");

	ide_proc_रेजिस्टर_driver(drive, tape->driver);
पूर्ण

अटल व्योम ide_tape_हटाओ(ide_drive_t *drive)
अणु
	idetape_tape_t *tape = drive->driver_data;

	ide_proc_unरेजिस्टर_driver(drive, tape->driver);
	device_del(&tape->dev);

	mutex_lock(&idetape_ref_mutex);
	put_device(&tape->dev);
	mutex_unlock(&idetape_ref_mutex);
पूर्ण

अटल व्योम ide_tape_release(काष्ठा device *dev)
अणु
	काष्ठा ide_tape_obj *tape = to_ide_drv(dev, ide_tape_obj);
	ide_drive_t *drive = tape->drive;
	काष्ठा gendisk *g = tape->disk;

	BUG_ON(tape->valid);

	drive->dev_flags &= ~IDE_DFLAG_DSC_OVERLAP;
	drive->driver_data = शून्य;
	device_destroy(idetape_sysfs_class, MKDEV(IDETAPE_MAJOR, tape->minor));
	device_destroy(idetape_sysfs_class,
			MKDEV(IDETAPE_MAJOR, tape->minor + 128));
	idetape_devs[tape->minor] = शून्य;
	g->निजी_data = शून्य;
	put_disk(g);
	kमुक्त(tape);
पूर्ण

#अगर_घोषित CONFIG_IDE_PROC_FS
अटल पूर्णांक idetape_name_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	ide_drive_t	*drive = (ide_drive_t *) m->निजी;
	idetape_tape_t	*tape = drive->driver_data;

	seq_म_लिखो(m, "%s\n", tape->name);
	वापस 0;
पूर्ण

अटल ide_proc_entry_t idetape_proc[] = अणु
	अणु "capacity",	S_IFREG|S_IRUGO,	ide_capacity_proc_show	पूर्ण,
	अणु "name",	S_IFREG|S_IRUGO,	idetape_name_proc_show	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल ide_proc_entry_t *ide_tape_proc_entries(ide_drive_t *drive)
अणु
	वापस idetape_proc;
पूर्ण

अटल स्थिर काष्ठा ide_proc_devset *ide_tape_proc_devsets(ide_drive_t *drive)
अणु
	वापस idetape_settings;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक ide_tape_probe(ide_drive_t *);

अटल काष्ठा ide_driver idetape_driver = अणु
	.gen_driver = अणु
		.owner		= THIS_MODULE,
		.name		= "ide-tape",
		.bus		= &ide_bus_type,
	पूर्ण,
	.probe			= ide_tape_probe,
	.हटाओ			= ide_tape_हटाओ,
	.version		= IDETAPE_VERSION,
	.करो_request		= idetape_करो_request,
#अगर_घोषित CONFIG_IDE_PROC_FS
	.proc_entries		= ide_tape_proc_entries,
	.proc_devsets		= ide_tape_proc_devsets,
#पूर्ण_अगर
पूर्ण;

/* Our अक्षरacter device supporting functions, passed to रेजिस्टर_chrdev. */
अटल स्थिर काष्ठा file_operations idetape_fops = अणु
	.owner		= THIS_MODULE,
	.पढ़ो		= idetape_chrdev_पढ़ो,
	.ग_लिखो		= idetape_chrdev_ग_लिखो,
	.unlocked_ioctl	= idetape_chrdev_ioctl,
	.compat_ioctl	= IS_ENABLED(CONFIG_COMPAT) ?
			  idetape_chrdev_compat_ioctl : शून्य,
	.खोलो		= idetape_chrdev_खोलो,
	.release	= idetape_chrdev_release,
	.llseek		= noop_llseek,
पूर्ण;

अटल पूर्णांक idetape_खोलो(काष्ठा block_device *bdev, भ_शेषe_t mode)
अणु
	काष्ठा ide_tape_obj *tape;

	mutex_lock(&ide_tape_mutex);
	tape = ide_tape_get(bdev->bd_disk, false, 0);
	mutex_unlock(&ide_tape_mutex);

	अगर (!tape)
		वापस -ENXIO;

	वापस 0;
पूर्ण

अटल व्योम idetape_release(काष्ठा gendisk *disk, भ_शेषe_t mode)
अणु
	काष्ठा ide_tape_obj *tape = ide_drv_g(disk, ide_tape_obj);

	mutex_lock(&ide_tape_mutex);
	ide_tape_put(tape);
	mutex_unlock(&ide_tape_mutex);
पूर्ण

अटल पूर्णांक idetape_ioctl(काष्ठा block_device *bdev, भ_शेषe_t mode,
			अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा ide_tape_obj *tape = ide_drv_g(bdev->bd_disk, ide_tape_obj);
	ide_drive_t *drive = tape->drive;
	पूर्णांक err;

	mutex_lock(&ide_tape_mutex);
	err = generic_ide_ioctl(drive, bdev, cmd, arg);
	अगर (err == -EINVAL)
		err = idetape_blkdev_ioctl(drive, cmd, arg);
	mutex_unlock(&ide_tape_mutex);

	वापस err;
पूर्ण

अटल पूर्णांक idetape_compat_ioctl(काष्ठा block_device *bdev, भ_शेषe_t mode,
				अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
        अगर (cmd == 0x0340 || cmd == 0x350)
		arg = (अचिन्हित दीर्घ)compat_ptr(arg);

	वापस idetape_ioctl(bdev, mode, cmd, arg);
पूर्ण

अटल स्थिर काष्ठा block_device_operations idetape_block_ops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= idetape_खोलो,
	.release	= idetape_release,
	.ioctl		= idetape_ioctl,
	.compat_ioctl	= IS_ENABLED(CONFIG_COMPAT) ?
				idetape_compat_ioctl : शून्य,
पूर्ण;

अटल पूर्णांक ide_tape_probe(ide_drive_t *drive)
अणु
	idetape_tape_t *tape;
	काष्ठा gendisk *g;
	पूर्णांक minor;

	ide_debug_log(IDE_DBG_FUNC, "enter");

	अगर (!म_माला(DRV_NAME, drive->driver_req))
		जाओ failed;

	अगर (drive->media != ide_tape)
		जाओ failed;

	अगर ((drive->dev_flags & IDE_DFLAG_ID_READ) &&
	    ide_check_atapi_device(drive, DRV_NAME) == 0) अणु
		prपूर्णांकk(KERN_ERR "ide-tape: %s: not supported by this version of"
				" the driver\n", drive->name);
		जाओ failed;
	पूर्ण
	tape = kzalloc(माप(idetape_tape_t), GFP_KERNEL);
	अगर (tape == शून्य) अणु
		prपूर्णांकk(KERN_ERR "ide-tape: %s: Can't allocate a tape struct\n",
				drive->name);
		जाओ failed;
	पूर्ण

	g = alloc_disk(1 << PARTN_BITS);
	अगर (!g)
		जाओ out_मुक्त_tape;

	ide_init_disk(g, drive);

	tape->dev.parent = &drive->gendev;
	tape->dev.release = ide_tape_release;
	dev_set_name(&tape->dev, "%s", dev_name(&drive->gendev));

	अगर (device_रेजिस्टर(&tape->dev))
		जाओ out_मुक्त_disk;

	tape->drive = drive;
	tape->driver = &idetape_driver;
	tape->disk = g;

	g->निजी_data = &tape->driver;

	drive->driver_data = tape;

	mutex_lock(&idetape_ref_mutex);
	क्रम (minor = 0; idetape_devs[minor]; minor++)
		;
	idetape_devs[minor] = tape;
	mutex_unlock(&idetape_ref_mutex);

	idetape_setup(drive, tape, minor);

	device_create(idetape_sysfs_class, &drive->gendev,
		      MKDEV(IDETAPE_MAJOR, minor), शून्य, "%s", tape->name);
	device_create(idetape_sysfs_class, &drive->gendev,
		      MKDEV(IDETAPE_MAJOR, minor + 128), शून्य,
		      "n%s", tape->name);

	g->fops = &idetape_block_ops;

	वापस 0;

out_मुक्त_disk:
	put_disk(g);
out_मुक्त_tape:
	kमुक्त(tape);
failed:
	वापस -ENODEV;
पूर्ण

अटल व्योम __निकास idetape_निकास(व्योम)
अणु
	driver_unरेजिस्टर(&idetape_driver.gen_driver);
	class_destroy(idetape_sysfs_class);
	unरेजिस्टर_chrdev(IDETAPE_MAJOR, "ht");
पूर्ण

अटल पूर्णांक __init idetape_init(व्योम)
अणु
	पूर्णांक error = 1;
	idetape_sysfs_class = class_create(THIS_MODULE, "ide_tape");
	अगर (IS_ERR(idetape_sysfs_class)) अणु
		idetape_sysfs_class = शून्य;
		prपूर्णांकk(KERN_ERR "Unable to create sysfs class for ide tapes\n");
		error = -EBUSY;
		जाओ out;
	पूर्ण

	अगर (रेजिस्टर_chrdev(IDETAPE_MAJOR, "ht", &idetape_fops)) अणु
		prपूर्णांकk(KERN_ERR "ide-tape: Failed to register chrdev"
				" interface\n");
		error = -EBUSY;
		जाओ out_मुक्त_class;
	पूर्ण

	error = driver_रेजिस्टर(&idetape_driver.gen_driver);
	अगर (error)
		जाओ out_मुक्त_chrdev;

	वापस 0;

out_मुक्त_chrdev:
	unरेजिस्टर_chrdev(IDETAPE_MAJOR, "ht");
out_मुक्त_class:
	class_destroy(idetape_sysfs_class);
out:
	वापस error;
पूर्ण

MODULE_ALIAS("ide:*m-tape*");
module_init(idetape_init);
module_निकास(idetape_निकास);
MODULE_ALIAS_CHARDEV_MAJOR(IDETAPE_MAJOR);
MODULE_DESCRIPTION("ATAPI Streaming TAPE Driver");
MODULE_LICENSE("GPL");
