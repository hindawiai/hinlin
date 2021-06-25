<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * SCSI Zoned Block commands
 *
 * Copyright (C) 2014-2015 SUSE Linux GmbH
 * Written by: Hannes Reinecke <hare@suse.de>
 * Modअगरied by: Damien Le Moal <damien.lemoal@hgst.com>
 * Modअगरied by: Shaun Tancheff <shaun.tancheff@seagate.com>
 */

#समावेश <linux/blkdev.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/mutex.h>

#समावेश <यंत्र/unaligned.h>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>

#समावेश "sd.h"

अटल अचिन्हित पूर्णांक sd_zbc_get_zone_wp_offset(काष्ठा blk_zone *zone)
अणु
	अगर (zone->type == ZBC_ZONE_TYPE_CONV)
		वापस 0;

	चयन (zone->cond) अणु
	हाल BLK_ZONE_COND_IMP_OPEN:
	हाल BLK_ZONE_COND_EXP_OPEN:
	हाल BLK_ZONE_COND_CLOSED:
		वापस zone->wp - zone->start;
	हाल BLK_ZONE_COND_FULL:
		वापस zone->len;
	हाल BLK_ZONE_COND_EMPTY:
	हाल BLK_ZONE_COND_OFFLINE:
	हाल BLK_ZONE_COND_READONLY:
	शेष:
		/*
		 * Offline and पढ़ो-only zones करो not have a valid
		 * ग_लिखो poपूर्णांकer. Use 0 as क्रम an empty zone.
		 */
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक sd_zbc_parse_report(काष्ठा scsi_disk *sdkp, u8 *buf,
			       अचिन्हित पूर्णांक idx, report_zones_cb cb, व्योम *data)
अणु
	काष्ठा scsi_device *sdp = sdkp->device;
	काष्ठा blk_zone zone = अणु 0 पूर्ण;
	पूर्णांक ret;

	zone.type = buf[0] & 0x0f;
	zone.cond = (buf[1] >> 4) & 0xf;
	अगर (buf[1] & 0x01)
		zone.reset = 1;
	अगर (buf[1] & 0x02)
		zone.non_seq = 1;

	zone.len = logical_to_sectors(sdp, get_unaligned_be64(&buf[8]));
	zone.capacity = zone.len;
	zone.start = logical_to_sectors(sdp, get_unaligned_be64(&buf[16]));
	zone.wp = logical_to_sectors(sdp, get_unaligned_be64(&buf[24]));
	अगर (zone.type != ZBC_ZONE_TYPE_CONV &&
	    zone.cond == ZBC_ZONE_COND_FULL)
		zone.wp = zone.start + zone.len;

	ret = cb(&zone, idx, data);
	अगर (ret)
		वापस ret;

	अगर (sdkp->rev_wp_offset)
		sdkp->rev_wp_offset[idx] = sd_zbc_get_zone_wp_offset(&zone);

	वापस 0;
पूर्ण

/**
 * sd_zbc_करो_report_zones - Issue a REPORT ZONES scsi command.
 * @sdkp: The target disk
 * @buf: vदो_स्मृति-ed buffer to use क्रम the reply
 * @buflen: the buffer size
 * @lba: Start LBA of the report
 * @partial: Do partial report
 *
 * For पूर्णांकernal use during device validation.
 * Using partial=true can signअगरicantly speed up execution of a report zones
 * command because the disk करोes not have to count all possible report matching
 * zones and will only report the count of zones fitting in the command reply
 * buffer.
 */
अटल पूर्णांक sd_zbc_करो_report_zones(काष्ठा scsi_disk *sdkp, अचिन्हित अक्षर *buf,
				  अचिन्हित पूर्णांक buflen, sector_t lba,
				  bool partial)
अणु
	काष्ठा scsi_device *sdp = sdkp->device;
	स्थिर पूर्णांक समयout = sdp->request_queue->rq_समयout;
	काष्ठा scsi_sense_hdr sshdr;
	अचिन्हित अक्षर cmd[16];
	अचिन्हित पूर्णांक rep_len;
	पूर्णांक result;

	स_रखो(cmd, 0, 16);
	cmd[0] = ZBC_IN;
	cmd[1] = ZI_REPORT_ZONES;
	put_unaligned_be64(lba, &cmd[2]);
	put_unaligned_be32(buflen, &cmd[10]);
	अगर (partial)
		cmd[14] = ZBC_REPORT_ZONE_PARTIAL;

	result = scsi_execute_req(sdp, cmd, DMA_FROM_DEVICE,
				  buf, buflen, &sshdr,
				  समयout, SD_MAX_RETRIES, शून्य);
	अगर (result) अणु
		sd_prपूर्णांकk(KERN_ERR, sdkp,
			  "REPORT ZONES start lba %llu failed\n", lba);
		sd_prपूर्णांक_result(sdkp, "REPORT ZONES", result);
		अगर (driver_byte(result) == DRIVER_SENSE &&
		    scsi_sense_valid(&sshdr))
			sd_prपूर्णांक_sense_hdr(sdkp, &sshdr);
		वापस -EIO;
	पूर्ण

	rep_len = get_unaligned_be32(&buf[0]);
	अगर (rep_len < 64) अणु
		sd_prपूर्णांकk(KERN_ERR, sdkp,
			  "REPORT ZONES report invalid length %u\n",
			  rep_len);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * sd_zbc_alloc_report_buffer() - Allocate a buffer क्रम report zones reply.
 * @sdkp: The target disk
 * @nr_zones: Maximum number of zones to report
 * @buflen: Size of the buffer allocated
 *
 * Try to allocate a reply buffer क्रम the number of requested zones.
 * The size of the buffer allocated may be smaller than requested to
 * satअगरy the device स्थिरraपूर्णांक (max_hw_sectors, max_segments, etc).
 *
 * Return the address of the allocated buffer and update @buflen with
 * the size of the allocated buffer.
 */
अटल व्योम *sd_zbc_alloc_report_buffer(काष्ठा scsi_disk *sdkp,
					अचिन्हित पूर्णांक nr_zones, माप_प्रकार *buflen)
अणु
	काष्ठा request_queue *q = sdkp->disk->queue;
	माप_प्रकार bufsize;
	व्योम *buf;

	/*
	 * Report zone buffer size should be at most 64B बार the number of
	 * zones requested plus the 64B reply header, but should be at least
	 * SECTOR_SIZE क्रम ATA devices.
	 * Make sure that this size करोes not exceed the hardware capabilities.
	 * Furthermore, since the report zone command cannot be split, make
	 * sure that the allocated buffer can always be mapped by limiting the
	 * number of pages allocated to the HBA max segments limit.
	 */
	nr_zones = min(nr_zones, sdkp->nr_zones);
	bufsize = roundup((nr_zones + 1) * 64, SECTOR_SIZE);
	bufsize = min_t(माप_प्रकार, bufsize,
			queue_max_hw_sectors(q) << SECTOR_SHIFT);
	bufsize = min_t(माप_प्रकार, bufsize, queue_max_segments(q) << PAGE_SHIFT);

	जबतक (bufsize >= SECTOR_SIZE) अणु
		buf = __vदो_स्मृति(bufsize,
				GFP_KERNEL | __GFP_ZERO | __GFP_NORETRY);
		अगर (buf) अणु
			*buflen = bufsize;
			वापस buf;
		पूर्ण
		bufsize >>= 1;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * sd_zbc_zone_sectors - Get the device zone size in number of 512B sectors.
 * @sdkp: The target disk
 */
अटल अंतरभूत sector_t sd_zbc_zone_sectors(काष्ठा scsi_disk *sdkp)
अणु
	वापस logical_to_sectors(sdkp->device, sdkp->zone_blocks);
पूर्ण

पूर्णांक sd_zbc_report_zones(काष्ठा gendisk *disk, sector_t sector,
			अचिन्हित पूर्णांक nr_zones, report_zones_cb cb, व्योम *data)
अणु
	काष्ठा scsi_disk *sdkp = scsi_disk(disk);
	sector_t capacity = logical_to_sectors(sdkp->device, sdkp->capacity);
	अचिन्हित पूर्णांक nr, i;
	अचिन्हित अक्षर *buf;
	माप_प्रकार offset, buflen = 0;
	पूर्णांक zone_idx = 0;
	पूर्णांक ret;

	अगर (!sd_is_zoned(sdkp))
		/* Not a zoned device */
		वापस -EOPNOTSUPP;

	अगर (!capacity)
		/* Device gone or invalid */
		वापस -ENODEV;

	buf = sd_zbc_alloc_report_buffer(sdkp, nr_zones, &buflen);
	अगर (!buf)
		वापस -ENOMEM;

	जबतक (zone_idx < nr_zones && sector < capacity) अणु
		ret = sd_zbc_करो_report_zones(sdkp, buf, buflen,
				sectors_to_logical(sdkp->device, sector), true);
		अगर (ret)
			जाओ out;

		offset = 0;
		nr = min(nr_zones, get_unaligned_be32(&buf[0]) / 64);
		अगर (!nr)
			अवरोध;

		क्रम (i = 0; i < nr && zone_idx < nr_zones; i++) अणु
			offset += 64;
			ret = sd_zbc_parse_report(sdkp, buf + offset, zone_idx,
						  cb, data);
			अगर (ret)
				जाओ out;
			zone_idx++;
		पूर्ण

		sector += sd_zbc_zone_sectors(sdkp) * i;
	पूर्ण

	ret = zone_idx;
out:
	kvमुक्त(buf);
	वापस ret;
पूर्ण

अटल blk_status_t sd_zbc_cmnd_checks(काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा request *rq = cmd->request;
	काष्ठा scsi_disk *sdkp = scsi_disk(rq->rq_disk);
	sector_t sector = blk_rq_pos(rq);

	अगर (!sd_is_zoned(sdkp))
		/* Not a zoned device */
		वापस BLK_STS_IOERR;

	अगर (sdkp->device->changed)
		वापस BLK_STS_IOERR;

	अगर (sector & (sd_zbc_zone_sectors(sdkp) - 1))
		/* Unaligned request */
		वापस BLK_STS_IOERR;

	वापस BLK_STS_OK;
पूर्ण

#घोषणा SD_ZBC_INVALID_WP_OFST	(~0u)
#घोषणा SD_ZBC_UPDATING_WP_OFST	(SD_ZBC_INVALID_WP_OFST - 1)

अटल पूर्णांक sd_zbc_update_wp_offset_cb(काष्ठा blk_zone *zone, अचिन्हित पूर्णांक idx,
				    व्योम *data)
अणु
	काष्ठा scsi_disk *sdkp = data;

	lockdep_निश्चित_held(&sdkp->zones_wp_offset_lock);

	sdkp->zones_wp_offset[idx] = sd_zbc_get_zone_wp_offset(zone);

	वापस 0;
पूर्ण

अटल व्योम sd_zbc_update_wp_offset_workfn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा scsi_disk *sdkp;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक zno;
	पूर्णांक ret;

	sdkp = container_of(work, काष्ठा scsi_disk, zone_wp_offset_work);

	spin_lock_irqsave(&sdkp->zones_wp_offset_lock, flags);
	क्रम (zno = 0; zno < sdkp->nr_zones; zno++) अणु
		अगर (sdkp->zones_wp_offset[zno] != SD_ZBC_UPDATING_WP_OFST)
			जारी;

		spin_unlock_irqrestore(&sdkp->zones_wp_offset_lock, flags);
		ret = sd_zbc_करो_report_zones(sdkp, sdkp->zone_wp_update_buf,
					     SD_BUF_SIZE,
					     zno * sdkp->zone_blocks, true);
		spin_lock_irqsave(&sdkp->zones_wp_offset_lock, flags);
		अगर (!ret)
			sd_zbc_parse_report(sdkp, sdkp->zone_wp_update_buf + 64,
					    zno, sd_zbc_update_wp_offset_cb,
					    sdkp);
	पूर्ण
	spin_unlock_irqrestore(&sdkp->zones_wp_offset_lock, flags);

	scsi_device_put(sdkp->device);
पूर्ण

/**
 * sd_zbc_prepare_zone_append() - Prepare an emulated ZONE_APPEND command.
 * @cmd: the command to setup
 * @lba: the LBA to patch
 * @nr_blocks: the number of LBAs to be written
 *
 * Called from sd_setup_पढ़ो_ग_लिखो_cmnd() क्रम REQ_OP_ZONE_APPEND.
 * @sd_zbc_prepare_zone_append() handles the necessary zone wrote locking and
 * patching of the lba क्रम an emulated ZONE_APPEND command.
 *
 * In हाल the cached ग_लिखो poपूर्णांकer offset is %SD_ZBC_INVALID_WP_OFST it will
 * schedule a REPORT ZONES command and वापस BLK_STS_IOERR.
 */
blk_status_t sd_zbc_prepare_zone_append(काष्ठा scsi_cmnd *cmd, sector_t *lba,
					अचिन्हित पूर्णांक nr_blocks)
अणु
	काष्ठा request *rq = cmd->request;
	काष्ठा scsi_disk *sdkp = scsi_disk(rq->rq_disk);
	अचिन्हित पूर्णांक wp_offset, zno = blk_rq_zone_no(rq);
	अचिन्हित दीर्घ flags;
	blk_status_t ret;

	ret = sd_zbc_cmnd_checks(cmd);
	अगर (ret != BLK_STS_OK)
		वापस ret;

	अगर (!blk_rq_zone_is_seq(rq))
		वापस BLK_STS_IOERR;

	/* Unlock of the ग_लिखो lock will happen in sd_zbc_complete() */
	अगर (!blk_req_zone_ग_लिखो_trylock(rq))
		वापस BLK_STS_ZONE_RESOURCE;

	spin_lock_irqsave(&sdkp->zones_wp_offset_lock, flags);
	wp_offset = sdkp->zones_wp_offset[zno];
	चयन (wp_offset) अणु
	हाल SD_ZBC_INVALID_WP_OFST:
		/*
		 * We are about to schedule work to update a zone ग_लिखो poपूर्णांकer
		 * offset, which will cause the zone append command to be
		 * requeued. So make sure that the scsi device करोes not go away
		 * जबतक the work is being processed.
		 */
		अगर (scsi_device_get(sdkp->device)) अणु
			ret = BLK_STS_IOERR;
			अवरोध;
		पूर्ण
		sdkp->zones_wp_offset[zno] = SD_ZBC_UPDATING_WP_OFST;
		schedule_work(&sdkp->zone_wp_offset_work);
		fallthrough;
	हाल SD_ZBC_UPDATING_WP_OFST:
		ret = BLK_STS_DEV_RESOURCE;
		अवरोध;
	शेष:
		wp_offset = sectors_to_logical(sdkp->device, wp_offset);
		अगर (wp_offset + nr_blocks > sdkp->zone_blocks) अणु
			ret = BLK_STS_IOERR;
			अवरोध;
		पूर्ण

		*lba += wp_offset;
	पूर्ण
	spin_unlock_irqrestore(&sdkp->zones_wp_offset_lock, flags);
	अगर (ret)
		blk_req_zone_ग_लिखो_unlock(rq);
	वापस ret;
पूर्ण

/**
 * sd_zbc_setup_zone_mgmt_cmnd - Prepare a zone ZBC_OUT command. The operations
 *			can be RESET WRITE POINTER, OPEN, CLOSE or FINISH.
 * @cmd: the command to setup
 * @op: Operation to be perक्रमmed
 * @all: All zones control
 *
 * Called from sd_init_command() क्रम REQ_OP_ZONE_RESET, REQ_OP_ZONE_RESET_ALL,
 * REQ_OP_ZONE_OPEN, REQ_OP_ZONE_CLOSE or REQ_OP_ZONE_FINISH requests.
 */
blk_status_t sd_zbc_setup_zone_mgmt_cmnd(काष्ठा scsi_cmnd *cmd,
					 अचिन्हित अक्षर op, bool all)
अणु
	काष्ठा request *rq = cmd->request;
	sector_t sector = blk_rq_pos(rq);
	काष्ठा scsi_disk *sdkp = scsi_disk(rq->rq_disk);
	sector_t block = sectors_to_logical(sdkp->device, sector);
	blk_status_t ret;

	ret = sd_zbc_cmnd_checks(cmd);
	अगर (ret != BLK_STS_OK)
		वापस ret;

	cmd->cmd_len = 16;
	स_रखो(cmd->cmnd, 0, cmd->cmd_len);
	cmd->cmnd[0] = ZBC_OUT;
	cmd->cmnd[1] = op;
	अगर (all)
		cmd->cmnd[14] = 0x1;
	अन्यथा
		put_unaligned_be64(block, &cmd->cmnd[2]);

	rq->समयout = SD_TIMEOUT;
	cmd->sc_data_direction = DMA_NONE;
	cmd->transfersize = 0;
	cmd->allowed = 0;

	वापस BLK_STS_OK;
पूर्ण

अटल bool sd_zbc_need_zone_wp_update(काष्ठा request *rq)
अणु
	चयन (req_op(rq)) अणु
	हाल REQ_OP_ZONE_APPEND:
	हाल REQ_OP_ZONE_FINISH:
	हाल REQ_OP_ZONE_RESET:
	हाल REQ_OP_ZONE_RESET_ALL:
		वापस true;
	हाल REQ_OP_WRITE:
	हाल REQ_OP_WRITE_ZEROES:
	हाल REQ_OP_WRITE_SAME:
		वापस blk_rq_zone_is_seq(rq);
	शेष:
		वापस false;
	पूर्ण
पूर्ण

/**
 * sd_zbc_zone_wp_update - Update cached zone ग_लिखो poपूर्णांकer upon cmd completion
 * @cmd: Completed command
 * @good_bytes: Command reply bytes
 *
 * Called from sd_zbc_complete() to handle the update of the cached zone ग_लिखो
 * poपूर्णांकer value in हाल an update is needed.
 */
अटल अचिन्हित पूर्णांक sd_zbc_zone_wp_update(काष्ठा scsi_cmnd *cmd,
					  अचिन्हित पूर्णांक good_bytes)
अणु
	पूर्णांक result = cmd->result;
	काष्ठा request *rq = cmd->request;
	काष्ठा scsi_disk *sdkp = scsi_disk(rq->rq_disk);
	अचिन्हित पूर्णांक zno = blk_rq_zone_no(rq);
	क्रमागत req_opf op = req_op(rq);
	अचिन्हित दीर्घ flags;

	/*
	 * If we got an error क्रम a command that needs updating the ग_लिखो
	 * poपूर्णांकer offset cache, we must mark the zone wp offset entry as
	 * invalid to क्रमce an update from disk the next समय a zone append
	 * command is issued.
	 */
	spin_lock_irqsave(&sdkp->zones_wp_offset_lock, flags);

	अगर (result && op != REQ_OP_ZONE_RESET_ALL) अणु
		अगर (op == REQ_OP_ZONE_APPEND) अणु
			/* Force complete completion (no retry) */
			good_bytes = 0;
			scsi_set_resid(cmd, blk_rq_bytes(rq));
		पूर्ण

		/*
		 * Force an update of the zone ग_लिखो poपूर्णांकer offset on
		 * the next zone append access.
		 */
		अगर (sdkp->zones_wp_offset[zno] != SD_ZBC_UPDATING_WP_OFST)
			sdkp->zones_wp_offset[zno] = SD_ZBC_INVALID_WP_OFST;
		जाओ unlock_wp_offset;
	पूर्ण

	चयन (op) अणु
	हाल REQ_OP_ZONE_APPEND:
		rq->__sector += sdkp->zones_wp_offset[zno];
		fallthrough;
	हाल REQ_OP_WRITE_ZEROES:
	हाल REQ_OP_WRITE_SAME:
	हाल REQ_OP_WRITE:
		अगर (sdkp->zones_wp_offset[zno] < sd_zbc_zone_sectors(sdkp))
			sdkp->zones_wp_offset[zno] +=
						good_bytes >> SECTOR_SHIFT;
		अवरोध;
	हाल REQ_OP_ZONE_RESET:
		sdkp->zones_wp_offset[zno] = 0;
		अवरोध;
	हाल REQ_OP_ZONE_FINISH:
		sdkp->zones_wp_offset[zno] = sd_zbc_zone_sectors(sdkp);
		अवरोध;
	हाल REQ_OP_ZONE_RESET_ALL:
		स_रखो(sdkp->zones_wp_offset, 0,
		       sdkp->nr_zones * माप(अचिन्हित पूर्णांक));
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

unlock_wp_offset:
	spin_unlock_irqrestore(&sdkp->zones_wp_offset_lock, flags);

	वापस good_bytes;
पूर्ण

/**
 * sd_zbc_complete - ZBC command post processing.
 * @cmd: Completed command
 * @good_bytes: Command reply bytes
 * @sshdr: command sense header
 *
 * Called from sd_करोne() to handle zone commands errors and updates to the
 * device queue zone ग_लिखो poपूर्णांकer offset cahce.
 */
अचिन्हित पूर्णांक sd_zbc_complete(काष्ठा scsi_cmnd *cmd, अचिन्हित पूर्णांक good_bytes,
		     काष्ठा scsi_sense_hdr *sshdr)
अणु
	पूर्णांक result = cmd->result;
	काष्ठा request *rq = cmd->request;

	अगर (op_is_zone_mgmt(req_op(rq)) &&
	    result &&
	    sshdr->sense_key == ILLEGAL_REQUEST &&
	    sshdr->asc == 0x24) अणु
		/*
		 * INVALID FIELD IN CDB error: a zone management command was
		 * attempted on a conventional zone. Nothing to worry about,
		 * so be quiet about the error.
		 */
		rq->rq_flags |= RQF_QUIET;
	पूर्ण अन्यथा अगर (sd_zbc_need_zone_wp_update(rq))
		good_bytes = sd_zbc_zone_wp_update(cmd, good_bytes);

	अगर (req_op(rq) == REQ_OP_ZONE_APPEND)
		blk_req_zone_ग_लिखो_unlock(rq);

	वापस good_bytes;
पूर्ण

/**
 * sd_zbc_check_zoned_अक्षरacteristics - Check zoned block device अक्षरacteristics
 * @sdkp: Target disk
 * @buf: Buffer where to store the VPD page data
 *
 * Read VPD page B6, get inक्रमmation and check that पढ़ोs are unस्थिरrained.
 */
अटल पूर्णांक sd_zbc_check_zoned_अक्षरacteristics(काष्ठा scsi_disk *sdkp,
					      अचिन्हित अक्षर *buf)
अणु

	अगर (scsi_get_vpd_page(sdkp->device, 0xb6, buf, 64)) अणु
		sd_prपूर्णांकk(KERN_NOTICE, sdkp,
			  "Read zoned characteristics VPD page failed\n");
		वापस -ENODEV;
	पूर्ण

	अगर (sdkp->device->type != TYPE_ZBC) अणु
		/* Host-aware */
		sdkp->urswrz = 1;
		sdkp->zones_optimal_खोलो = get_unaligned_be32(&buf[8]);
		sdkp->zones_optimal_nonseq = get_unaligned_be32(&buf[12]);
		sdkp->zones_max_खोलो = 0;
	पूर्ण अन्यथा अणु
		/* Host-managed */
		sdkp->urswrz = buf[4] & 1;
		sdkp->zones_optimal_खोलो = 0;
		sdkp->zones_optimal_nonseq = 0;
		sdkp->zones_max_खोलो = get_unaligned_be32(&buf[16]);
	पूर्ण

	/*
	 * Check क्रम unस्थिरrained पढ़ोs: host-managed devices with
	 * स्थिरrained पढ़ोs (drives failing पढ़ो after ग_लिखो poपूर्णांकer)
	 * are not supported.
	 */
	अगर (!sdkp->urswrz) अणु
		अगर (sdkp->first_scan)
			sd_prपूर्णांकk(KERN_NOTICE, sdkp,
			  "constrained reads devices are not supported\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * sd_zbc_check_capacity - Check the device capacity
 * @sdkp: Target disk
 * @buf: command buffer
 * @zblocks: zone size in number of blocks
 *
 * Get the device zone size and check that the device capacity as reported
 * by READ CAPACITY matches the max_lba value (plus one) of the report zones
 * command reply क्रम devices with RC_BASIS == 0.
 *
 * Returns 0 upon success or an error code upon failure.
 */
अटल पूर्णांक sd_zbc_check_capacity(काष्ठा scsi_disk *sdkp, अचिन्हित अक्षर *buf,
				 u32 *zblocks)
अणु
	u64 zone_blocks;
	sector_t max_lba;
	अचिन्हित अक्षर *rec;
	पूर्णांक ret;

	/* Do a report zone to get max_lba and the size of the first zone */
	ret = sd_zbc_करो_report_zones(sdkp, buf, SD_BUF_SIZE, 0, false);
	अगर (ret)
		वापस ret;

	अगर (sdkp->rc_basis == 0) अणु
		/* The max_lba field is the capacity of this device */
		max_lba = get_unaligned_be64(&buf[8]);
		अगर (sdkp->capacity != max_lba + 1) अणु
			अगर (sdkp->first_scan)
				sd_prपूर्णांकk(KERN_WARNING, sdkp,
					"Changing capacity from %llu to max LBA+1 %llu\n",
					(अचिन्हित दीर्घ दीर्घ)sdkp->capacity,
					(अचिन्हित दीर्घ दीर्घ)max_lba + 1);
			sdkp->capacity = max_lba + 1;
		पूर्ण
	पूर्ण

	/* Get the size of the first reported zone */
	rec = buf + 64;
	zone_blocks = get_unaligned_be64(&rec[8]);
	अगर (logical_to_sectors(sdkp->device, zone_blocks) > अच_पूर्णांक_उच्च) अणु
		अगर (sdkp->first_scan)
			sd_prपूर्णांकk(KERN_NOTICE, sdkp,
				  "Zone size too large\n");
		वापस -EFBIG;
	पूर्ण

	*zblocks = zone_blocks;

	वापस 0;
पूर्ण

अटल व्योम sd_zbc_prपूर्णांक_zones(काष्ठा scsi_disk *sdkp)
अणु
	अगर (!sd_is_zoned(sdkp) || !sdkp->capacity)
		वापस;

	अगर (sdkp->capacity & (sdkp->zone_blocks - 1))
		sd_prपूर्णांकk(KERN_NOTICE, sdkp,
			  "%u zones of %u logical blocks + 1 runt zone\n",
			  sdkp->nr_zones - 1,
			  sdkp->zone_blocks);
	अन्यथा
		sd_prपूर्णांकk(KERN_NOTICE, sdkp,
			  "%u zones of %u logical blocks\n",
			  sdkp->nr_zones,
			  sdkp->zone_blocks);
पूर्ण

अटल पूर्णांक sd_zbc_init_disk(काष्ठा scsi_disk *sdkp)
अणु
	sdkp->zones_wp_offset = शून्य;
	spin_lock_init(&sdkp->zones_wp_offset_lock);
	sdkp->rev_wp_offset = शून्य;
	mutex_init(&sdkp->rev_mutex);
	INIT_WORK(&sdkp->zone_wp_offset_work, sd_zbc_update_wp_offset_workfn);
	sdkp->zone_wp_update_buf = kzalloc(SD_BUF_SIZE, GFP_KERNEL);
	अगर (!sdkp->zone_wp_update_buf)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम sd_zbc_clear_zone_info(काष्ठा scsi_disk *sdkp)
अणु
	/* Serialize against revalidate zones */
	mutex_lock(&sdkp->rev_mutex);

	kvमुक्त(sdkp->zones_wp_offset);
	sdkp->zones_wp_offset = शून्य;
	kमुक्त(sdkp->zone_wp_update_buf);
	sdkp->zone_wp_update_buf = शून्य;

	sdkp->nr_zones = 0;
	sdkp->rev_nr_zones = 0;
	sdkp->zone_blocks = 0;
	sdkp->rev_zone_blocks = 0;

	mutex_unlock(&sdkp->rev_mutex);
पूर्ण

व्योम sd_zbc_release_disk(काष्ठा scsi_disk *sdkp)
अणु
	अगर (sd_is_zoned(sdkp))
		sd_zbc_clear_zone_info(sdkp);
पूर्ण

अटल व्योम sd_zbc_revalidate_zones_cb(काष्ठा gendisk *disk)
अणु
	काष्ठा scsi_disk *sdkp = scsi_disk(disk);

	swap(sdkp->zones_wp_offset, sdkp->rev_wp_offset);
पूर्ण

पूर्णांक sd_zbc_revalidate_zones(काष्ठा scsi_disk *sdkp)
अणु
	काष्ठा gendisk *disk = sdkp->disk;
	काष्ठा request_queue *q = disk->queue;
	u32 zone_blocks = sdkp->rev_zone_blocks;
	अचिन्हित पूर्णांक nr_zones = sdkp->rev_nr_zones;
	u32 max_append;
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक flags;

	/*
	 * For all zoned disks, initialize zone append emulation data अगर not
	 * alपढ़ोy करोne. This is necessary also क्रम host-aware disks used as
	 * regular disks due to the presence of partitions as these partitions
	 * may be deleted and the disk zoned model changed back from
	 * BLK_ZONED_NONE to BLK_ZONED_HA.
	 */
	अगर (sd_is_zoned(sdkp) && !sdkp->zone_wp_update_buf) अणु
		ret = sd_zbc_init_disk(sdkp);
		अगर (ret)
			वापस ret;
	पूर्ण

	/*
	 * There is nothing to करो क्रम regular disks, including host-aware disks
	 * that have partitions.
	 */
	अगर (!blk_queue_is_zoned(q))
		वापस 0;

	/*
	 * Make sure revalidate zones are serialized to ensure exclusive
	 * updates of the scsi disk data.
	 */
	mutex_lock(&sdkp->rev_mutex);

	अगर (sdkp->zone_blocks == zone_blocks &&
	    sdkp->nr_zones == nr_zones &&
	    disk->queue->nr_zones == nr_zones)
		जाओ unlock;

	flags = meदो_स्मृति_noio_save();
	sdkp->zone_blocks = zone_blocks;
	sdkp->nr_zones = nr_zones;
	sdkp->rev_wp_offset = kvसुस्मृति(nr_zones, माप(u32), GFP_KERNEL);
	अगर (!sdkp->rev_wp_offset) अणु
		ret = -ENOMEM;
		meदो_स्मृति_noio_restore(flags);
		जाओ unlock;
	पूर्ण

	ret = blk_revalidate_disk_zones(disk, sd_zbc_revalidate_zones_cb);

	meदो_स्मृति_noio_restore(flags);
	kvमुक्त(sdkp->rev_wp_offset);
	sdkp->rev_wp_offset = शून्य;

	अगर (ret) अणु
		sdkp->zone_blocks = 0;
		sdkp->nr_zones = 0;
		sdkp->capacity = 0;
		जाओ unlock;
	पूर्ण

	max_append = min_t(u32, logical_to_sectors(sdkp->device, zone_blocks),
			   q->limits.max_segments << (PAGE_SHIFT - 9));
	max_append = min_t(u32, max_append, queue_max_hw_sectors(q));

	blk_queue_max_zone_append_sectors(q, max_append);

	sd_zbc_prपूर्णांक_zones(sdkp);

unlock:
	mutex_unlock(&sdkp->rev_mutex);

	वापस ret;
पूर्ण

पूर्णांक sd_zbc_पढ़ो_zones(काष्ठा scsi_disk *sdkp, अचिन्हित अक्षर *buf)
अणु
	काष्ठा gendisk *disk = sdkp->disk;
	काष्ठा request_queue *q = disk->queue;
	अचिन्हित पूर्णांक nr_zones;
	u32 zone_blocks = 0;
	पूर्णांक ret;

	अगर (!sd_is_zoned(sdkp))
		/*
		 * Device managed or normal SCSI disk,
		 * no special handling required
		 */
		वापस 0;

	/* READ16/WRITE16 is mandatory क्रम ZBC disks */
	sdkp->device->use_16_क्रम_rw = 1;
	sdkp->device->use_10_क्रम_rw = 0;

	अगर (!blk_queue_is_zoned(q)) अणु
		/*
		 * This can happen क्रम a host aware disk with partitions.
		 * The block device zone inक्रमmation was alपढ़ोy cleared
		 * by blk_queue_set_zoned(). Only clear the scsi disk zone
		 * inक्रमmation and निकास early.
		 */
		sd_zbc_clear_zone_info(sdkp);
		वापस 0;
	पूर्ण

	/* Check zoned block device अक्षरacteristics (unस्थिरrained पढ़ोs) */
	ret = sd_zbc_check_zoned_अक्षरacteristics(sdkp, buf);
	अगर (ret)
		जाओ err;

	/* Check the device capacity reported by report zones */
	ret = sd_zbc_check_capacity(sdkp, buf, &zone_blocks);
	अगर (ret != 0)
		जाओ err;

	/* The drive satisfies the kernel restrictions: set it up */
	blk_queue_flag_set(QUEUE_FLAG_ZONE_RESETALL, q);
	blk_queue_required_elevator_features(q, ELEVATOR_F_ZBD_SEQ_WRITE);
	अगर (sdkp->zones_max_खोलो == U32_MAX)
		blk_queue_max_खोलो_zones(q, 0);
	अन्यथा
		blk_queue_max_खोलो_zones(q, sdkp->zones_max_खोलो);
	blk_queue_max_active_zones(q, 0);
	nr_zones = round_up(sdkp->capacity, zone_blocks) >> ilog2(zone_blocks);

	/*
	 * Per ZBC and ZAC specअगरications, ग_लिखोs in sequential ग_लिखो required
	 * zones of host-managed devices must be aligned to the device physical
	 * block size.
	 */
	अगर (blk_queue_zoned_model(q) == BLK_ZONED_HM)
		blk_queue_zone_ग_लिखो_granularity(q, sdkp->physical_block_size);

	sdkp->rev_nr_zones = nr_zones;
	sdkp->rev_zone_blocks = zone_blocks;

	वापस 0;

err:
	sdkp->capacity = 0;

	वापस ret;
पूर्ण
