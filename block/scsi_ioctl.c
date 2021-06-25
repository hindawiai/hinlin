<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2001 Jens Axboe <axboe@suse.de>
 */
#समावेश <linux/compat.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/module.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/capability.h>
#समावेश <linux/completion.h>
#समावेश <linux/cdrom.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/slab.h>
#समावेश <linux/बार.h>
#समावेश <linux/uपन.स>
#समावेश <linux/uaccess.h>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_ioctl.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/sg.h>

काष्ठा blk_cmd_filter अणु
	अचिन्हित दीर्घ पढ़ो_ok[BLK_SCSI_CMD_PER_LONG];
	अचिन्हित दीर्घ ग_लिखो_ok[BLK_SCSI_CMD_PER_LONG];
पूर्ण;

अटल काष्ठा blk_cmd_filter blk_शेष_cmd_filter;

/* Command group 3 is reserved and should never be used.  */
स्थिर अचिन्हित अक्षर scsi_command_माप_प्रकारbl[8] =
अणु
	6, 10, 10, 12,
	16, 12, 10, 10
पूर्ण;
EXPORT_SYMBOL(scsi_command_माप_प्रकारbl);

अटल पूर्णांक sg_get_version(पूर्णांक __user *p)
अणु
	अटल स्थिर पूर्णांक sg_version_num = 30527;
	वापस put_user(sg_version_num, p);
पूर्ण

अटल पूर्णांक scsi_get_idlun(काष्ठा request_queue *q, पूर्णांक __user *p)
अणु
	वापस put_user(0, p);
पूर्ण

अटल पूर्णांक scsi_get_bus(काष्ठा request_queue *q, पूर्णांक __user *p)
अणु
	वापस put_user(0, p);
पूर्ण

अटल पूर्णांक sg_get_समयout(काष्ठा request_queue *q)
अणु
	वापस jअगरfies_to_घड़ी_प्रकार(q->sg_समयout);
पूर्ण

अटल पूर्णांक sg_set_समयout(काष्ठा request_queue *q, पूर्णांक __user *p)
अणु
	पूर्णांक समयout, err = get_user(समयout, p);

	अगर (!err)
		q->sg_समयout = घड़ी_प्रकार_to_jअगरfies(समयout);

	वापस err;
पूर्ण

अटल पूर्णांक max_sectors_bytes(काष्ठा request_queue *q)
अणु
	अचिन्हित पूर्णांक max_sectors = queue_max_sectors(q);

	max_sectors = min_t(अचिन्हित पूर्णांक, max_sectors, पूर्णांक_उच्च >> 9);

	वापस max_sectors << 9;
पूर्ण

अटल पूर्णांक sg_get_reserved_size(काष्ठा request_queue *q, पूर्णांक __user *p)
अणु
	पूर्णांक val = min_t(पूर्णांक, q->sg_reserved_size, max_sectors_bytes(q));

	वापस put_user(val, p);
पूर्ण

अटल पूर्णांक sg_set_reserved_size(काष्ठा request_queue *q, पूर्णांक __user *p)
अणु
	पूर्णांक size, err = get_user(size, p);

	अगर (err)
		वापस err;

	अगर (size < 0)
		वापस -EINVAL;

	q->sg_reserved_size = min(size, max_sectors_bytes(q));
	वापस 0;
पूर्ण

/*
 * will always वापस that we are ATAPI even क्रम a real SCSI drive, I'm not
 * so sure this is worth करोing anything about (why would you care??)
 */
अटल पूर्णांक sg_emulated_host(काष्ठा request_queue *q, पूर्णांक __user *p)
अणु
	वापस put_user(1, p);
पूर्ण

अटल व्योम blk_set_cmd_filter_शेषs(काष्ठा blk_cmd_filter *filter)
अणु
	/* Basic पढ़ो-only commands */
	__set_bit(TEST_UNIT_READY, filter->पढ़ो_ok);
	__set_bit(REQUEST_SENSE, filter->पढ़ो_ok);
	__set_bit(READ_6, filter->पढ़ो_ok);
	__set_bit(READ_10, filter->पढ़ो_ok);
	__set_bit(READ_12, filter->पढ़ो_ok);
	__set_bit(READ_16, filter->पढ़ो_ok);
	__set_bit(READ_BUFFER, filter->पढ़ो_ok);
	__set_bit(READ_DEFECT_DATA, filter->पढ़ो_ok);
	__set_bit(READ_CAPACITY, filter->पढ़ो_ok);
	__set_bit(READ_LONG, filter->पढ़ो_ok);
	__set_bit(INQUIRY, filter->पढ़ो_ok);
	__set_bit(MODE_SENSE, filter->पढ़ो_ok);
	__set_bit(MODE_SENSE_10, filter->पढ़ो_ok);
	__set_bit(LOG_SENSE, filter->पढ़ो_ok);
	__set_bit(START_STOP, filter->पढ़ो_ok);
	__set_bit(GPCMD_VERIFY_10, filter->पढ़ो_ok);
	__set_bit(VERIFY_16, filter->पढ़ो_ok);
	__set_bit(REPORT_LUNS, filter->पढ़ो_ok);
	__set_bit(SERVICE_ACTION_IN_16, filter->पढ़ो_ok);
	__set_bit(RECEIVE_DIAGNOSTIC, filter->पढ़ो_ok);
	__set_bit(MAINTEन_अंकCE_IN, filter->पढ़ो_ok);
	__set_bit(GPCMD_READ_BUFFER_CAPACITY, filter->पढ़ो_ok);

	/* Audio CD commands */
	__set_bit(GPCMD_PLAY_CD, filter->पढ़ो_ok);
	__set_bit(GPCMD_PLAY_AUDIO_10, filter->पढ़ो_ok);
	__set_bit(GPCMD_PLAY_AUDIO_MSF, filter->पढ़ो_ok);
	__set_bit(GPCMD_PLAY_AUDIO_TI, filter->पढ़ो_ok);
	__set_bit(GPCMD_PAUSE_RESUME, filter->पढ़ो_ok);

	/* CD/DVD data पढ़ोing */
	__set_bit(GPCMD_READ_CD, filter->पढ़ो_ok);
	__set_bit(GPCMD_READ_CD_MSF, filter->पढ़ो_ok);
	__set_bit(GPCMD_READ_DISC_INFO, filter->पढ़ो_ok);
	__set_bit(GPCMD_READ_CDVD_CAPACITY, filter->पढ़ो_ok);
	__set_bit(GPCMD_READ_DVD_STRUCTURE, filter->पढ़ो_ok);
	__set_bit(GPCMD_READ_HEADER, filter->पढ़ो_ok);
	__set_bit(GPCMD_READ_TRACK_RZONE_INFO, filter->पढ़ो_ok);
	__set_bit(GPCMD_READ_SUBCHANNEL, filter->पढ़ो_ok);
	__set_bit(GPCMD_READ_TOC_PMA_ATIP, filter->पढ़ो_ok);
	__set_bit(GPCMD_REPORT_KEY, filter->पढ़ो_ok);
	__set_bit(GPCMD_SCAN, filter->पढ़ो_ok);
	__set_bit(GPCMD_GET_CONFIGURATION, filter->पढ़ो_ok);
	__set_bit(GPCMD_READ_FORMAT_CAPACITIES, filter->पढ़ो_ok);
	__set_bit(GPCMD_GET_EVENT_STATUS_NOTIFICATION, filter->पढ़ो_ok);
	__set_bit(GPCMD_GET_PERFORMANCE, filter->पढ़ो_ok);
	__set_bit(GPCMD_SEEK, filter->पढ़ो_ok);
	__set_bit(GPCMD_STOP_PLAY_SCAN, filter->पढ़ो_ok);

	/* Basic writing commands */
	__set_bit(WRITE_6, filter->ग_लिखो_ok);
	__set_bit(WRITE_10, filter->ग_लिखो_ok);
	__set_bit(WRITE_VERIFY, filter->ग_लिखो_ok);
	__set_bit(WRITE_12, filter->ग_लिखो_ok);
	__set_bit(WRITE_VERIFY_12, filter->ग_लिखो_ok);
	__set_bit(WRITE_16, filter->ग_लिखो_ok);
	__set_bit(WRITE_LONG, filter->ग_लिखो_ok);
	__set_bit(WRITE_LONG_2, filter->ग_लिखो_ok);
	__set_bit(WRITE_SAME, filter->ग_लिखो_ok);
	__set_bit(WRITE_SAME_16, filter->ग_लिखो_ok);
	__set_bit(WRITE_SAME_32, filter->ग_लिखो_ok);
	__set_bit(ERASE, filter->ग_लिखो_ok);
	__set_bit(GPCMD_MODE_SELECT_10, filter->ग_लिखो_ok);
	__set_bit(MODE_SELECT, filter->ग_लिखो_ok);
	__set_bit(LOG_SELECT, filter->ग_लिखो_ok);
	__set_bit(GPCMD_BLANK, filter->ग_लिखो_ok);
	__set_bit(GPCMD_CLOSE_TRACK, filter->ग_लिखो_ok);
	__set_bit(GPCMD_FLUSH_CACHE, filter->ग_लिखो_ok);
	__set_bit(GPCMD_FORMAT_UNIT, filter->ग_लिखो_ok);
	__set_bit(GPCMD_REPAIR_RZONE_TRACK, filter->ग_लिखो_ok);
	__set_bit(GPCMD_RESERVE_RZONE_TRACK, filter->ग_लिखो_ok);
	__set_bit(GPCMD_SEND_DVD_STRUCTURE, filter->ग_लिखो_ok);
	__set_bit(GPCMD_SEND_EVENT, filter->ग_लिखो_ok);
	__set_bit(GPCMD_SEND_KEY, filter->ग_लिखो_ok);
	__set_bit(GPCMD_SEND_OPC, filter->ग_लिखो_ok);
	__set_bit(GPCMD_SEND_CUE_SHEET, filter->ग_लिखो_ok);
	__set_bit(GPCMD_SET_SPEED, filter->ग_लिखो_ok);
	__set_bit(GPCMD_PREVENT_ALLOW_MEDIUM_REMOVAL, filter->ग_लिखो_ok);
	__set_bit(GPCMD_LOAD_UNLOAD, filter->ग_लिखो_ok);
	__set_bit(GPCMD_SET_STREAMING, filter->ग_लिखो_ok);
	__set_bit(GPCMD_SET_READ_AHEAD, filter->ग_लिखो_ok);

	/* ZBC Commands */
	__set_bit(ZBC_OUT, filter->ग_लिखो_ok);
	__set_bit(ZBC_IN, filter->पढ़ो_ok);
पूर्ण

पूर्णांक blk_verअगरy_command(अचिन्हित अक्षर *cmd, भ_शेषe_t mode)
अणु
	काष्ठा blk_cmd_filter *filter = &blk_शेष_cmd_filter;

	/* root can करो any command. */
	अगर (capable(CAP_SYS_RAWIO))
		वापस 0;

	/* Anybody who can खोलो the device can करो a पढ़ो-safe command */
	अगर (test_bit(cmd[0], filter->पढ़ो_ok))
		वापस 0;

	/* Write-safe commands require a writable खोलो */
	अगर (test_bit(cmd[0], filter->ग_लिखो_ok) && (mode & FMODE_WRITE))
		वापस 0;

	वापस -EPERM;
पूर्ण
EXPORT_SYMBOL(blk_verअगरy_command);

अटल पूर्णांक blk_fill_sghdr_rq(काष्ठा request_queue *q, काष्ठा request *rq,
			     काष्ठा sg_io_hdr *hdr, भ_शेषe_t mode)
अणु
	काष्ठा scsi_request *req = scsi_req(rq);

	अगर (copy_from_user(req->cmd, hdr->cmdp, hdr->cmd_len))
		वापस -EFAULT;
	अगर (blk_verअगरy_command(req->cmd, mode))
		वापस -EPERM;

	/*
	 * fill in request काष्ठाure
	 */
	req->cmd_len = hdr->cmd_len;

	rq->समयout = msecs_to_jअगरfies(hdr->समयout);
	अगर (!rq->समयout)
		rq->समयout = q->sg_समयout;
	अगर (!rq->समयout)
		rq->समयout = BLK_DEFAULT_SG_TIMEOUT;
	अगर (rq->समयout < BLK_MIN_SG_TIMEOUT)
		rq->समयout = BLK_MIN_SG_TIMEOUT;

	वापस 0;
पूर्ण

अटल पूर्णांक blk_complete_sghdr_rq(काष्ठा request *rq, काष्ठा sg_io_hdr *hdr,
				 काष्ठा bio *bio)
अणु
	काष्ठा scsi_request *req = scsi_req(rq);
	पूर्णांक r, ret = 0;

	/*
	 * fill in all the output members
	 */
	hdr->status = req->result & 0xff;
	hdr->masked_status = status_byte(req->result);
	hdr->msg_status = msg_byte(req->result);
	hdr->host_status = host_byte(req->result);
	hdr->driver_status = driver_byte(req->result);
	hdr->info = 0;
	अगर (hdr->masked_status || hdr->host_status || hdr->driver_status)
		hdr->info |= SG_INFO_CHECK;
	hdr->resid = req->resid_len;
	hdr->sb_len_wr = 0;

	अगर (req->sense_len && hdr->sbp) अणु
		पूर्णांक len = min((अचिन्हित पूर्णांक) hdr->mx_sb_len, req->sense_len);

		अगर (!copy_to_user(hdr->sbp, req->sense, len))
			hdr->sb_len_wr = len;
		अन्यथा
			ret = -EFAULT;
	पूर्ण

	r = blk_rq_unmap_user(bio);
	अगर (!ret)
		ret = r;

	वापस ret;
पूर्ण

अटल पूर्णांक sg_io(काष्ठा request_queue *q, काष्ठा gendisk *bd_disk,
		काष्ठा sg_io_hdr *hdr, भ_शेषe_t mode)
अणु
	अचिन्हित दीर्घ start_समय;
	sमाप_प्रकार ret = 0;
	पूर्णांक writing = 0;
	पूर्णांक at_head = 0;
	काष्ठा request *rq;
	काष्ठा scsi_request *req;
	काष्ठा bio *bio;

	अगर (hdr->पूर्णांकerface_id != 'S')
		वापस -EINVAL;

	अगर (hdr->dxfer_len > (queue_max_hw_sectors(q) << 9))
		वापस -EIO;

	अगर (hdr->dxfer_len)
		चयन (hdr->dxfer_direction) अणु
		शेष:
			वापस -EINVAL;
		हाल SG_DXFER_TO_DEV:
			writing = 1;
			अवरोध;
		हाल SG_DXFER_TO_FROM_DEV:
		हाल SG_DXFER_FROM_DEV:
			अवरोध;
		पूर्ण
	अगर (hdr->flags & SG_FLAG_Q_AT_HEAD)
		at_head = 1;

	ret = -ENOMEM;
	rq = blk_get_request(q, writing ? REQ_OP_SCSI_OUT : REQ_OP_SCSI_IN, 0);
	अगर (IS_ERR(rq))
		वापस PTR_ERR(rq);
	req = scsi_req(rq);

	अगर (hdr->cmd_len > BLK_MAX_CDB) अणु
		req->cmd = kzalloc(hdr->cmd_len, GFP_KERNEL);
		अगर (!req->cmd)
			जाओ out_put_request;
	पूर्ण

	ret = blk_fill_sghdr_rq(q, rq, hdr, mode);
	अगर (ret < 0)
		जाओ out_मुक्त_cdb;

	ret = 0;
	अगर (hdr->iovec_count) अणु
		काष्ठा iov_iter i;
		काष्ठा iovec *iov = शून्य;

		ret = import_iovec(rq_data_dir(rq), hdr->dxferp,
				   hdr->iovec_count, 0, &iov, &i);
		अगर (ret < 0)
			जाओ out_मुक्त_cdb;

		/* SG_IO howto says that the लघुer of the two wins */
		iov_iter_truncate(&i, hdr->dxfer_len);

		ret = blk_rq_map_user_iov(q, rq, शून्य, &i, GFP_KERNEL);
		kमुक्त(iov);
	पूर्ण अन्यथा अगर (hdr->dxfer_len)
		ret = blk_rq_map_user(q, rq, शून्य, hdr->dxferp, hdr->dxfer_len,
				      GFP_KERNEL);

	अगर (ret)
		जाओ out_मुक्त_cdb;

	bio = rq->bio;
	req->retries = 0;

	start_समय = jअगरfies;

	blk_execute_rq(bd_disk, rq, at_head);

	hdr->duration = jअगरfies_to_msecs(jअगरfies - start_समय);

	ret = blk_complete_sghdr_rq(rq, hdr, bio);

out_मुक्त_cdb:
	scsi_req_मुक्त_cmd(req);
out_put_request:
	blk_put_request(rq);
	वापस ret;
पूर्ण

/**
 * sg_scsi_ioctl  --  handle deprecated SCSI_IOCTL_SEND_COMMAND ioctl
 * @q:		request queue to send scsi commands करोwn
 * @disk:	gendisk to operate on (option)
 * @mode:	mode used to खोलो the file through which the ioctl has been
 *		submitted
 * @sic:	userspace काष्ठाure describing the command to perक्रमm
 *
 * Send करोwn the scsi command described by @sic to the device below
 * the request queue @q.  If @file is non-शून्य it's used to perक्रमm
 * fine-grained permission checks that allow users to send करोwn
 * non-deकाष्ठाive SCSI commands.  If the caller has a काष्ठा gendisk
 * available it should be passed in as @disk to allow the low level
 * driver to use the inक्रमmation contained in it.  A non-शून्य @disk
 * is only allowed अगर the caller knows that the low level driver करोesn't
 * need it (e.g. in the scsi subप्रणाली).
 *
 * Notes:
 *   -  This पूर्णांकerface is deprecated - users should use the SG_IO
 *      पूर्णांकerface instead, as this is a more flexible approach to
 *      perक्रमming SCSI commands on a device.
 *   -  The SCSI command length is determined by examining the 1st byte
 *      of the given command. There is no way to override this.
 *   -  Data transfers are limited to PAGE_SIZE
 *   -  The length (x + y) must be at least OMAX_SB_LEN bytes दीर्घ to
 *      accommodate the sense buffer when an error occurs.
 *      The sense buffer is truncated to OMAX_SB_LEN (16) bytes so that
 *      old code will not be surprised.
 *   -  If a Unix error occurs (e.g. ENOMEM) then the user will receive
 *      a negative वापस and the Unix error code in 'errno'.
 *      If the SCSI command succeeds then 0 is वापसed.
 *      Positive numbers वापसed are the compacted SCSI error codes (4
 *      bytes in one पूर्णांक) where the lowest byte is the SCSI status.
 */
पूर्णांक sg_scsi_ioctl(काष्ठा request_queue *q, काष्ठा gendisk *disk, भ_शेषe_t mode,
		काष्ठा scsi_ioctl_command __user *sic)
अणु
	क्रमागत अणु OMAX_SB_LEN = 16 पूर्ण;	/* For backward compatibility */
	काष्ठा request *rq;
	काष्ठा scsi_request *req;
	पूर्णांक err;
	अचिन्हित पूर्णांक in_len, out_len, bytes, opcode, cmdlen;
	अक्षर *buffer = शून्य;

	अगर (!sic)
		वापस -EINVAL;

	/*
	 * get in an out lengths, verअगरy they करोn't exceed a page worth of data
	 */
	अगर (get_user(in_len, &sic->inlen))
		वापस -EFAULT;
	अगर (get_user(out_len, &sic->outlen))
		वापस -EFAULT;
	अगर (in_len > PAGE_SIZE || out_len > PAGE_SIZE)
		वापस -EINVAL;
	अगर (get_user(opcode, sic->data))
		वापस -EFAULT;

	bytes = max(in_len, out_len);
	अगर (bytes) अणु
		buffer = kzalloc(bytes, GFP_NOIO | GFP_USER | __GFP_NOWARN);
		अगर (!buffer)
			वापस -ENOMEM;

	पूर्ण

	rq = blk_get_request(q, in_len ? REQ_OP_SCSI_OUT : REQ_OP_SCSI_IN, 0);
	अगर (IS_ERR(rq)) अणु
		err = PTR_ERR(rq);
		जाओ error_मुक्त_buffer;
	पूर्ण
	req = scsi_req(rq);

	cmdlen = COMMAND_SIZE(opcode);

	/*
	 * get command and data to send to device, अगर any
	 */
	err = -EFAULT;
	req->cmd_len = cmdlen;
	अगर (copy_from_user(req->cmd, sic->data, cmdlen))
		जाओ error;

	अगर (in_len && copy_from_user(buffer, sic->data + cmdlen, in_len))
		जाओ error;

	err = blk_verअगरy_command(req->cmd, mode);
	अगर (err)
		जाओ error;

	/* शेष.  possible overriden later */
	req->retries = 5;

	चयन (opcode) अणु
	हाल SEND_DIAGNOSTIC:
	हाल FORMAT_UNIT:
		rq->समयout = FORMAT_UNIT_TIMEOUT;
		req->retries = 1;
		अवरोध;
	हाल START_STOP:
		rq->समयout = START_STOP_TIMEOUT;
		अवरोध;
	हाल MOVE_MEDIUM:
		rq->समयout = MOVE_MEDIUM_TIMEOUT;
		अवरोध;
	हाल READ_ELEMENT_STATUS:
		rq->समयout = READ_ELEMENT_STATUS_TIMEOUT;
		अवरोध;
	हाल READ_DEFECT_DATA:
		rq->समयout = READ_DEFECT_DATA_TIMEOUT;
		req->retries = 1;
		अवरोध;
	शेष:
		rq->समयout = BLK_DEFAULT_SG_TIMEOUT;
		अवरोध;
	पूर्ण

	अगर (bytes && blk_rq_map_kern(q, rq, buffer, bytes, GFP_NOIO)) अणु
		err = DRIVER_ERROR << 24;
		जाओ error;
	पूर्ण

	blk_execute_rq(disk, rq, 0);

	err = req->result & 0xff;	/* only 8 bit SCSI status */
	अगर (err) अणु
		अगर (req->sense_len && req->sense) अणु
			bytes = (OMAX_SB_LEN > req->sense_len) ?
				req->sense_len : OMAX_SB_LEN;
			अगर (copy_to_user(sic->data, req->sense, bytes))
				err = -EFAULT;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (copy_to_user(sic->data, buffer, out_len))
			err = -EFAULT;
	पूर्ण
	
error:
	blk_put_request(rq);

error_मुक्त_buffer:
	kमुक्त(buffer);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(sg_scsi_ioctl);

/* Send basic block requests */
अटल पूर्णांक __blk_send_generic(काष्ठा request_queue *q, काष्ठा gendisk *bd_disk,
			      पूर्णांक cmd, पूर्णांक data)
अणु
	काष्ठा request *rq;
	पूर्णांक err;

	rq = blk_get_request(q, REQ_OP_SCSI_OUT, 0);
	अगर (IS_ERR(rq))
		वापस PTR_ERR(rq);
	rq->समयout = BLK_DEFAULT_SG_TIMEOUT;
	scsi_req(rq)->cmd[0] = cmd;
	scsi_req(rq)->cmd[4] = data;
	scsi_req(rq)->cmd_len = 6;
	blk_execute_rq(bd_disk, rq, 0);
	err = scsi_req(rq)->result ? -EIO : 0;
	blk_put_request(rq);

	वापस err;
पूर्ण

अटल अंतरभूत पूर्णांक blk_send_start_stop(काष्ठा request_queue *q,
				      काष्ठा gendisk *bd_disk, पूर्णांक data)
अणु
	वापस __blk_send_generic(q, bd_disk, GPCMD_START_STOP_UNIT, data);
पूर्ण

पूर्णांक put_sg_io_hdr(स्थिर काष्ठा sg_io_hdr *hdr, व्योम __user *argp)
अणु
#अगर_घोषित CONFIG_COMPAT
	अगर (in_compat_syscall()) अणु
		काष्ठा compat_sg_io_hdr hdr32 =  अणु
			.पूर्णांकerface_id	 = hdr->पूर्णांकerface_id,
			.dxfer_direction = hdr->dxfer_direction,
			.cmd_len	 = hdr->cmd_len,
			.mx_sb_len	 = hdr->mx_sb_len,
			.iovec_count	 = hdr->iovec_count,
			.dxfer_len	 = hdr->dxfer_len,
			.dxferp		 = (uपूर्णांकptr_t)hdr->dxferp,
			.cmdp		 = (uपूर्णांकptr_t)hdr->cmdp,
			.sbp		 = (uपूर्णांकptr_t)hdr->sbp,
			.समयout	 = hdr->समयout,
			.flags		 = hdr->flags,
			.pack_id	 = hdr->pack_id,
			.usr_ptr	 = (uपूर्णांकptr_t)hdr->usr_ptr,
			.status		 = hdr->status,
			.masked_status	 = hdr->masked_status,
			.msg_status	 = hdr->msg_status,
			.sb_len_wr	 = hdr->sb_len_wr,
			.host_status	 = hdr->host_status,
			.driver_status	 = hdr->driver_status,
			.resid		 = hdr->resid,
			.duration	 = hdr->duration,
			.info		 = hdr->info,
		पूर्ण;

		अगर (copy_to_user(argp, &hdr32, माप(hdr32)))
			वापस -EFAULT;

		वापस 0;
	पूर्ण
#पूर्ण_अगर

	अगर (copy_to_user(argp, hdr, माप(*hdr)))
		वापस -EFAULT;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(put_sg_io_hdr);

पूर्णांक get_sg_io_hdr(काष्ठा sg_io_hdr *hdr, स्थिर व्योम __user *argp)
अणु
#अगर_घोषित CONFIG_COMPAT
	काष्ठा compat_sg_io_hdr hdr32;

	अगर (in_compat_syscall()) अणु
		अगर (copy_from_user(&hdr32, argp, माप(hdr32)))
			वापस -EFAULT;

		*hdr = (काष्ठा sg_io_hdr) अणु
			.पूर्णांकerface_id	 = hdr32.पूर्णांकerface_id,
			.dxfer_direction = hdr32.dxfer_direction,
			.cmd_len	 = hdr32.cmd_len,
			.mx_sb_len	 = hdr32.mx_sb_len,
			.iovec_count	 = hdr32.iovec_count,
			.dxfer_len	 = hdr32.dxfer_len,
			.dxferp		 = compat_ptr(hdr32.dxferp),
			.cmdp		 = compat_ptr(hdr32.cmdp),
			.sbp		 = compat_ptr(hdr32.sbp),
			.समयout	 = hdr32.समयout,
			.flags		 = hdr32.flags,
			.pack_id	 = hdr32.pack_id,
			.usr_ptr	 = compat_ptr(hdr32.usr_ptr),
			.status		 = hdr32.status,
			.masked_status	 = hdr32.masked_status,
			.msg_status	 = hdr32.msg_status,
			.sb_len_wr	 = hdr32.sb_len_wr,
			.host_status	 = hdr32.host_status,
			.driver_status	 = hdr32.driver_status,
			.resid		 = hdr32.resid,
			.duration	 = hdr32.duration,
			.info		 = hdr32.info,
		पूर्ण;

		वापस 0;
	पूर्ण
#पूर्ण_अगर

	अगर (copy_from_user(hdr, argp, माप(*hdr)))
		वापस -EFAULT;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(get_sg_io_hdr);

#अगर_घोषित CONFIG_COMPAT
काष्ठा compat_cdrom_generic_command अणु
	अचिन्हित अक्षर	cmd[CDROM_PACKET_SIZE];
	compat_caddr_t	buffer;
	compat_uपूर्णांक_t	buflen;
	compat_पूर्णांक_t	stat;
	compat_caddr_t	sense;
	अचिन्हित अक्षर	data_direction;
	अचिन्हित अक्षर	pad[3];
	compat_पूर्णांक_t	quiet;
	compat_पूर्णांक_t	समयout;
	compat_caddr_t	unused;
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक scsi_get_cdrom_generic_arg(काष्ठा cdrom_generic_command *cgc,
				      स्थिर व्योम __user *arg)
अणु
#अगर_घोषित CONFIG_COMPAT
	अगर (in_compat_syscall()) अणु
		काष्ठा compat_cdrom_generic_command cgc32;

		अगर (copy_from_user(&cgc32, arg, माप(cgc32)))
			वापस -EFAULT;

		*cgc = (काष्ठा cdrom_generic_command) अणु
			.buffer		= compat_ptr(cgc32.buffer),
			.buflen		= cgc32.buflen,
			.stat		= cgc32.stat,
			.sense		= compat_ptr(cgc32.sense),
			.data_direction	= cgc32.data_direction,
			.quiet		= cgc32.quiet,
			.समयout	= cgc32.समयout,
			.unused		= compat_ptr(cgc32.unused),
		पूर्ण;
		स_नकल(&cgc->cmd, &cgc32.cmd, CDROM_PACKET_SIZE);
		वापस 0;
	पूर्ण
#पूर्ण_अगर
	अगर (copy_from_user(cgc, arg, माप(*cgc)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक scsi_put_cdrom_generic_arg(स्थिर काष्ठा cdrom_generic_command *cgc,
				      व्योम __user *arg)
अणु
#अगर_घोषित CONFIG_COMPAT
	अगर (in_compat_syscall()) अणु
		काष्ठा compat_cdrom_generic_command cgc32 = अणु
			.buffer		= (uपूर्णांकptr_t)(cgc->buffer),
			.buflen		= cgc->buflen,
			.stat		= cgc->stat,
			.sense		= (uपूर्णांकptr_t)(cgc->sense),
			.data_direction	= cgc->data_direction,
			.quiet		= cgc->quiet,
			.समयout	= cgc->समयout,
			.unused		= (uपूर्णांकptr_t)(cgc->unused),
		पूर्ण;
		स_नकल(&cgc32.cmd, &cgc->cmd, CDROM_PACKET_SIZE);

		अगर (copy_to_user(arg, &cgc32, माप(cgc32)))
			वापस -EFAULT;

		वापस 0;
	पूर्ण
#पूर्ण_अगर
	अगर (copy_to_user(arg, cgc, माप(*cgc)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक scsi_cdrom_send_packet(काष्ठा request_queue *q,
				  काष्ठा gendisk *bd_disk,
				  भ_शेषe_t mode, व्योम __user *arg)
अणु
	काष्ठा cdrom_generic_command cgc;
	काष्ठा sg_io_hdr hdr;
	पूर्णांक err;

	err = scsi_get_cdrom_generic_arg(&cgc, arg);
	अगर (err)
		वापस err;

	cgc.समयout = घड़ी_प्रकार_to_jअगरfies(cgc.समयout);
	स_रखो(&hdr, 0, माप(hdr));
	hdr.पूर्णांकerface_id = 'S';
	hdr.cmd_len = माप(cgc.cmd);
	hdr.dxfer_len = cgc.buflen;
	चयन (cgc.data_direction) अणु
		हाल CGC_DATA_UNKNOWN:
			hdr.dxfer_direction = SG_DXFER_UNKNOWN;
			अवरोध;
		हाल CGC_DATA_WRITE:
			hdr.dxfer_direction = SG_DXFER_TO_DEV;
			अवरोध;
		हाल CGC_DATA_READ:
			hdr.dxfer_direction = SG_DXFER_FROM_DEV;
			अवरोध;
		हाल CGC_DATA_NONE:
			hdr.dxfer_direction = SG_DXFER_NONE;
			अवरोध;
		शेष:
			वापस -EINVAL;
	पूर्ण

	hdr.dxferp = cgc.buffer;
	hdr.sbp = cgc.sense;
	अगर (hdr.sbp)
		hdr.mx_sb_len = माप(काष्ठा request_sense);
	hdr.समयout = jअगरfies_to_msecs(cgc.समयout);
	hdr.cmdp = ((काष्ठा cdrom_generic_command __user*) arg)->cmd;
	hdr.cmd_len = माप(cgc.cmd);

	err = sg_io(q, bd_disk, &hdr, mode);
	अगर (err == -EFAULT)
		वापस -EFAULT;

	अगर (hdr.status)
		वापस -EIO;

	cgc.stat = err;
	cgc.buflen = hdr.resid;
	अगर (scsi_put_cdrom_generic_arg(&cgc, arg))
		वापस -EFAULT;

	वापस err;
पूर्ण

पूर्णांक scsi_cmd_ioctl(काष्ठा request_queue *q, काष्ठा gendisk *bd_disk, भ_शेषe_t mode,
		   अचिन्हित पूर्णांक cmd, व्योम __user *arg)
अणु
	पूर्णांक err;

	अगर (!q)
		वापस -ENXIO;

	चयन (cmd) अणु
		/*
		 * new sgv3 पूर्णांकerface
		 */
		हाल SG_GET_VERSION_NUM:
			err = sg_get_version(arg);
			अवरोध;
		हाल SCSI_IOCTL_GET_IDLUN:
			err = scsi_get_idlun(q, arg);
			अवरोध;
		हाल SCSI_IOCTL_GET_BUS_NUMBER:
			err = scsi_get_bus(q, arg);
			अवरोध;
		हाल SG_SET_TIMEOUT:
			err = sg_set_समयout(q, arg);
			अवरोध;
		हाल SG_GET_TIMEOUT:
			err = sg_get_समयout(q);
			अवरोध;
		हाल SG_GET_RESERVED_SIZE:
			err = sg_get_reserved_size(q, arg);
			अवरोध;
		हाल SG_SET_RESERVED_SIZE:
			err = sg_set_reserved_size(q, arg);
			अवरोध;
		हाल SG_EMULATED_HOST:
			err = sg_emulated_host(q, arg);
			अवरोध;
		हाल SG_IO: अणु
			काष्ठा sg_io_hdr hdr;

			err = get_sg_io_hdr(&hdr, arg);
			अगर (err)
				अवरोध;
			err = sg_io(q, bd_disk, &hdr, mode);
			अगर (err == -EFAULT)
				अवरोध;

			अगर (put_sg_io_hdr(&hdr, arg))
				err = -EFAULT;
			अवरोध;
		पूर्ण
		हाल CDROM_SEND_PACKET:
			err = scsi_cdrom_send_packet(q, bd_disk, mode, arg);
			अवरोध;

		/*
		 * old junk scsi send command ioctl
		 */
		हाल SCSI_IOCTL_SEND_COMMAND:
			prपूर्णांकk(KERN_WARNING "program %s is using a deprecated SCSI ioctl, please convert it to SG_IO\n", current->comm);
			err = -EINVAL;
			अगर (!arg)
				अवरोध;

			err = sg_scsi_ioctl(q, bd_disk, mode, arg);
			अवरोध;
		हाल CDROMCLOSETRAY:
			err = blk_send_start_stop(q, bd_disk, 0x03);
			अवरोध;
		हाल CDROMEJECT:
			err = blk_send_start_stop(q, bd_disk, 0x02);
			अवरोध;
		शेष:
			err = -ENOTTY;
	पूर्ण

	वापस err;
पूर्ण
EXPORT_SYMBOL(scsi_cmd_ioctl);

पूर्णांक scsi_verअगरy_blk_ioctl(काष्ठा block_device *bd, अचिन्हित पूर्णांक cmd)
अणु
	अगर (bd && !bdev_is_partition(bd))
		वापस 0;

	अगर (capable(CAP_SYS_RAWIO))
		वापस 0;

	वापस -ENOIOCTLCMD;
पूर्ण
EXPORT_SYMBOL(scsi_verअगरy_blk_ioctl);

पूर्णांक scsi_cmd_blk_ioctl(काष्ठा block_device *bd, भ_शेषe_t mode,
		       अचिन्हित पूर्णांक cmd, व्योम __user *arg)
अणु
	पूर्णांक ret;

	ret = scsi_verअगरy_blk_ioctl(bd, cmd);
	अगर (ret < 0)
		वापस ret;

	वापस scsi_cmd_ioctl(bd->bd_disk->queue, bd->bd_disk, mode, cmd, arg);
पूर्ण
EXPORT_SYMBOL(scsi_cmd_blk_ioctl);

/**
 * scsi_req_init - initialize certain fields of a scsi_request काष्ठाure
 * @req: Poपूर्णांकer to a scsi_request काष्ठाure.
 * Initializes .__cmd[], .cmd, .cmd_len and .sense_len but no other members
 * of काष्ठा scsi_request.
 */
व्योम scsi_req_init(काष्ठा scsi_request *req)
अणु
	स_रखो(req->__cmd, 0, माप(req->__cmd));
	req->cmd = req->__cmd;
	req->cmd_len = BLK_MAX_CDB;
	req->sense_len = 0;
पूर्ण
EXPORT_SYMBOL(scsi_req_init);

अटल पूर्णांक __init blk_scsi_ioctl_init(व्योम)
अणु
	blk_set_cmd_filter_शेषs(&blk_शेष_cmd_filter);
	वापस 0;
पूर्ण
fs_initcall(blk_scsi_ioctl_init);
