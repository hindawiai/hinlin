<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  scsi.c Copyright (C) 1992 Drew Eckhardt
 *         Copyright (C) 1993, 1994, 1995, 1999 Eric Youngdale
 *         Copyright (C) 2002, 2003 Christoph Hellwig
 *
 *  generic mid-level SCSI driver
 *      Initial versions: Drew Eckhardt
 *      Subsequent revisions: Eric Youngdale
 *
 *  <drew@coloraकरो.edu>
 *
 *  Bug correction thanks go to :
 *      Rik Faith <faith@cs.unc.edu>
 *      Tommy Thorn <tthorn>
 *      Thomas Wuensche <tw@fgb1.fgb.mw.tu-muenchen.de>
 *
 *  Modअगरied by Eric Youngdale eric@andante.org or ericy@gnu.ai.mit.edu to
 *  add scatter-gather, multiple outstanding request, and other
 *  enhancements.
 *
 *  Native multichannel, wide scsi, /proc/scsi and hot plugging
 *  support added by Michael Neuffer <mike@i-connect.net>
 *
 *  Added request_module("scsi_hostadapter") क्रम kerneld:
 *  (Put an "alias scsi_hostadapter your_hostadapter" in /etc/modprobe.conf)
 *  Bjorn Ekwall  <bj0rn@blox.se>
 *  (changed to kmod)
 *
 *  Major improvements to the समयout, पात, and reset processing,
 *  as well as perक्रमmance modअगरications क्रम large queue depths by
 *  Leonard N. Zubkoff <lnz@dandelion.com>
 *
 *  Converted cli() code to spinlocks, Ingo Molnar
 *
 *  Jअगरfies wrap fixes (host->resetting), 3 Dec 1998 Andrea Arcangeli
 *
 *  out_of_space hacks, D. Gilbert (dpg) 990608
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kernel.h>
#समावेश <linux/समयr.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/completion.h>
#समावेश <linux/unistd.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/kmod.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/cpu.h>
#समावेश <linux/mutex.h>
#समावेश <linux/async.h>
#समावेश <यंत्र/unaligned.h>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_dbg.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_driver.h>
#समावेश <scsi/scsi_eh.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_tcq.h>

#समावेश "scsi_priv.h"
#समावेश "scsi_logging.h"

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/scsi.h>

/*
 * Definitions and स्थिरants.
 */

/*
 * Note - the initial logging level can be set here to log events at boot समय.
 * After the प्रणाली is up, you may enable logging via the /proc पूर्णांकerface.
 */
अचिन्हित पूर्णांक scsi_logging_level;
#अगर defined(CONFIG_SCSI_LOGGING)
EXPORT_SYMBOL(scsi_logging_level);
#पूर्ण_अगर

/*
 * Doमुख्य क्रम asynchronous प्रणाली resume operations.  It is marked 'exclusive'
 * to aव्योम being included in the async_synchronize_full() that is invoked by
 * dpm_resume().
 */
ASYNC_DOMAIN_EXCLUSIVE(scsi_sd_pm_करोमुख्य);
EXPORT_SYMBOL(scsi_sd_pm_करोमुख्य);

#अगर_घोषित CONFIG_SCSI_LOGGING
व्योम scsi_log_send(काष्ठा scsi_cmnd *cmd)
अणु
	अचिन्हित पूर्णांक level;

	/*
	 * If ML QUEUE log level is greater than or equal to:
	 *
	 * 1: nothing (match completion)
	 *
	 * 2: log opcode + command of all commands + cmd address
	 *
	 * 3: same as 2
	 *
	 * 4: same as 3
	 */
	अगर (unlikely(scsi_logging_level)) अणु
		level = SCSI_LOG_LEVEL(SCSI_LOG_MLQUEUE_SHIFT,
				       SCSI_LOG_MLQUEUE_BITS);
		अगर (level > 1) अणु
			scmd_prपूर्णांकk(KERN_INFO, cmd,
				    "Send: scmd 0x%p\n", cmd);
			scsi_prपूर्णांक_command(cmd);
		पूर्ण
	पूर्ण
पूर्ण

व्योम scsi_log_completion(काष्ठा scsi_cmnd *cmd, पूर्णांक disposition)
अणु
	अचिन्हित पूर्णांक level;

	/*
	 * If ML COMPLETE log level is greater than or equal to:
	 *
	 * 1: log disposition, result, opcode + command, and conditionally
	 * sense data क्रम failures or non SUCCESS dispositions.
	 *
	 * 2: same as 1 but क्रम all command completions.
	 *
	 * 3: same as 2
	 *
	 * 4: same as 3 plus dump extra junk
	 */
	अगर (unlikely(scsi_logging_level)) अणु
		level = SCSI_LOG_LEVEL(SCSI_LOG_MLCOMPLETE_SHIFT,
				       SCSI_LOG_MLCOMPLETE_BITS);
		अगर (((level > 0) && (cmd->result || disposition != SUCCESS)) ||
		    (level > 1)) अणु
			scsi_prपूर्णांक_result(cmd, "Done", disposition);
			scsi_prपूर्णांक_command(cmd);
			अगर (status_byte(cmd->result) == CHECK_CONDITION)
				scsi_prपूर्णांक_sense(cmd);
			अगर (level > 3)
				scmd_prपूर्णांकk(KERN_INFO, cmd,
					    "scsi host busy %d failed %d\n",
					    scsi_host_busy(cmd->device->host),
					    cmd->device->host->host_failed);
		पूर्ण
	पूर्ण
पूर्ण
#पूर्ण_अगर

/**
 * scsi_finish_command - cleanup and pass command back to upper layer
 * @cmd: the command
 *
 * Description: Pass command off to upper layer क्रम finishing of I/O
 *              request, waking processes that are रुकोing on results,
 *              etc.
 */
व्योम scsi_finish_command(काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा scsi_device *sdev = cmd->device;
	काष्ठा scsi_target *starget = scsi_target(sdev);
	काष्ठा Scsi_Host *shost = sdev->host;
	काष्ठा scsi_driver *drv;
	अचिन्हित पूर्णांक good_bytes;

	scsi_device_unbusy(sdev, cmd);

	/*
	 * Clear the flags that say that the device/target/host is no दीर्घer
	 * capable of accepting new commands.
	 */
	अगर (atomic_पढ़ो(&shost->host_blocked))
		atomic_set(&shost->host_blocked, 0);
	अगर (atomic_पढ़ो(&starget->target_blocked))
		atomic_set(&starget->target_blocked, 0);
	अगर (atomic_पढ़ो(&sdev->device_blocked))
		atomic_set(&sdev->device_blocked, 0);

	/*
	 * If we have valid sense inक्रमmation, then some kind of recovery
	 * must have taken place.  Make a note of this.
	 */
	अगर (SCSI_SENSE_VALID(cmd))
		cmd->result |= (DRIVER_SENSE << 24);

	SCSI_LOG_MLCOMPLETE(4, sdev_prपूर्णांकk(KERN_INFO, sdev,
				"Notifying upper driver of completion "
				"(result %x)\n", cmd->result));

	good_bytes = scsi_bufflen(cmd);
	अगर (!blk_rq_is_passthrough(cmd->request)) अणु
		पूर्णांक old_good_bytes = good_bytes;
		drv = scsi_cmd_to_driver(cmd);
		अगर (drv->करोne)
			good_bytes = drv->करोne(cmd);
		/*
		 * USB may not give sense identअगरying bad sector and
		 * simply वापस a residue instead, so subtract off the
		 * residue अगर drv->करोne() error processing indicates no
		 * change to the completion length.
		 */
		अगर (good_bytes == old_good_bytes)
			good_bytes -= scsi_get_resid(cmd);
	पूर्ण
	scsi_io_completion(cmd, good_bytes);
पूर्ण


/*
 * 1024 is big enough क्रम saturating the fast scsi LUN now
 */
पूर्णांक scsi_device_max_queue_depth(काष्ठा scsi_device *sdev)
अणु
	वापस max_t(पूर्णांक, sdev->host->can_queue, 1024);
पूर्ण

/**
 * scsi_change_queue_depth - change a device's queue depth
 * @sdev: SCSI Device in question
 * @depth: number of commands allowed to be queued to the driver
 *
 * Sets the device queue depth and वापसs the new value.
 */
पूर्णांक scsi_change_queue_depth(काष्ठा scsi_device *sdev, पूर्णांक depth)
अणु
	depth = min_t(पूर्णांक, depth, scsi_device_max_queue_depth(sdev));

	अगर (depth > 0) अणु
		sdev->queue_depth = depth;
		wmb();
	पूर्ण

	अगर (sdev->request_queue)
		blk_set_queue_depth(sdev->request_queue, depth);

	sbiपंचांगap_resize(&sdev->budget_map, sdev->queue_depth);

	वापस sdev->queue_depth;
पूर्ण
EXPORT_SYMBOL(scsi_change_queue_depth);

/**
 * scsi_track_queue_full - track QUEUE_FULL events to adjust queue depth
 * @sdev: SCSI Device in question
 * @depth: Current number of outstanding SCSI commands on this device,
 *         not counting the one वापसed as QUEUE_FULL.
 *
 * Description:	This function will track successive QUEUE_FULL events on a
 * 		specअगरic SCSI device to determine अगर and when there is a
 * 		need to adjust the queue depth on the device.
 *
 * Returns:	0 - No change needed, >0 - Adjust queue depth to this new depth,
 * 		-1 - Drop back to untagged operation using host->cmd_per_lun
 * 			as the untagged command depth
 *
 * Lock Status:	None held on entry
 *
 * Notes:	Low level drivers may call this at any समय and we will करो
 * 		"The Right Thing."  We are पूर्णांकerrupt context safe.
 */
पूर्णांक scsi_track_queue_full(काष्ठा scsi_device *sdev, पूर्णांक depth)
अणु

	/*
	 * Don't let QUEUE_FULLs on the same
	 * jअगरfies count, they could all be from
	 * same event.
	 */
	अगर ((jअगरfies >> 4) == (sdev->last_queue_full_समय >> 4))
		वापस 0;

	sdev->last_queue_full_समय = jअगरfies;
	अगर (sdev->last_queue_full_depth != depth) अणु
		sdev->last_queue_full_count = 1;
		sdev->last_queue_full_depth = depth;
	पूर्ण अन्यथा अणु
		sdev->last_queue_full_count++;
	पूर्ण

	अगर (sdev->last_queue_full_count <= 10)
		वापस 0;

	वापस scsi_change_queue_depth(sdev, depth);
पूर्ण
EXPORT_SYMBOL(scsi_track_queue_full);

/**
 * scsi_vpd_inquiry - Request a device provide us with a VPD page
 * @sdev: The device to ask
 * @buffer: Where to put the result
 * @page: Which Vital Product Data to वापस
 * @len: The length of the buffer
 *
 * This is an पूर्णांकernal helper function.  You probably want to use
 * scsi_get_vpd_page instead.
 *
 * Returns size of the vpd page on success or a negative error number.
 */
अटल पूर्णांक scsi_vpd_inquiry(काष्ठा scsi_device *sdev, अचिन्हित अक्षर *buffer,
							u8 page, अचिन्हित len)
अणु
	पूर्णांक result;
	अचिन्हित अक्षर cmd[16];

	अगर (len < 4)
		वापस -EINVAL;

	cmd[0] = INQUIRY;
	cmd[1] = 1;		/* EVPD */
	cmd[2] = page;
	cmd[3] = len >> 8;
	cmd[4] = len & 0xff;
	cmd[5] = 0;		/* Control byte */

	/*
	 * I'm not convinced we need to try quite this hard to get VPD, but
	 * all the existing users tried this hard.
	 */
	result = scsi_execute_req(sdev, cmd, DMA_FROM_DEVICE, buffer,
				  len, शून्य, 30 * HZ, 3, शून्य);
	अगर (result)
		वापस -EIO;

	/* Sanity check that we got the page back that we asked क्रम */
	अगर (buffer[1] != page)
		वापस -EIO;

	वापस get_unaligned_be16(&buffer[2]) + 4;
पूर्ण

/**
 * scsi_get_vpd_page - Get Vital Product Data from a SCSI device
 * @sdev: The device to ask
 * @page: Which Vital Product Data to वापस
 * @buf: where to store the VPD
 * @buf_len: number of bytes in the VPD buffer area
 *
 * SCSI devices may optionally supply Vital Product Data.  Each 'page'
 * of VPD is defined in the appropriate SCSI करोcument (eg SPC, SBC).
 * If the device supports this VPD page, this routine वापसs a poपूर्णांकer
 * to a buffer containing the data from that page.  The caller is
 * responsible क्रम calling kमुक्त() on this poपूर्णांकer when it is no दीर्घer
 * needed.  If we cannot retrieve the VPD page this routine वापसs %शून्य.
 */
पूर्णांक scsi_get_vpd_page(काष्ठा scsi_device *sdev, u8 page, अचिन्हित अक्षर *buf,
		      पूर्णांक buf_len)
अणु
	पूर्णांक i, result;

	अगर (sdev->skip_vpd_pages)
		जाओ fail;

	/* Ask क्रम all the pages supported by this device */
	result = scsi_vpd_inquiry(sdev, buf, 0, buf_len);
	अगर (result < 4)
		जाओ fail;

	/* If the user actually wanted this page, we can skip the rest */
	अगर (page == 0)
		वापस 0;

	क्रम (i = 4; i < min(result, buf_len); i++)
		अगर (buf[i] == page)
			जाओ found;

	अगर (i < result && i >= buf_len)
		/* ran off the end of the buffer, give us benefit of करोubt */
		जाओ found;
	/* The device claims it करोesn't support the requested page */
	जाओ fail;

 found:
	result = scsi_vpd_inquiry(sdev, buf, page, buf_len);
	अगर (result < 0)
		जाओ fail;

	वापस 0;

 fail:
	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL_GPL(scsi_get_vpd_page);

/**
 * scsi_get_vpd_buf - Get Vital Product Data from a SCSI device
 * @sdev: The device to ask
 * @page: Which Vital Product Data to वापस
 *
 * Returns %शून्य upon failure.
 */
अटल काष्ठा scsi_vpd *scsi_get_vpd_buf(काष्ठा scsi_device *sdev, u8 page)
अणु
	काष्ठा scsi_vpd *vpd_buf;
	पूर्णांक vpd_len = SCSI_VPD_PG_LEN, result;

retry_pg:
	vpd_buf = kदो_स्मृति(माप(*vpd_buf) + vpd_len, GFP_KERNEL);
	अगर (!vpd_buf)
		वापस शून्य;

	result = scsi_vpd_inquiry(sdev, vpd_buf->data, page, vpd_len);
	अगर (result < 0) अणु
		kमुक्त(vpd_buf);
		वापस शून्य;
	पूर्ण
	अगर (result > vpd_len) अणु
		vpd_len = result;
		kमुक्त(vpd_buf);
		जाओ retry_pg;
	पूर्ण

	vpd_buf->len = result;

	वापस vpd_buf;
पूर्ण

अटल व्योम scsi_update_vpd_page(काष्ठा scsi_device *sdev, u8 page,
				 काष्ठा scsi_vpd __rcu **sdev_vpd_buf)
अणु
	काष्ठा scsi_vpd *vpd_buf;

	vpd_buf = scsi_get_vpd_buf(sdev, page);
	अगर (!vpd_buf)
		वापस;

	mutex_lock(&sdev->inquiry_mutex);
	vpd_buf = rcu_replace_poपूर्णांकer(*sdev_vpd_buf, vpd_buf,
				      lockdep_is_held(&sdev->inquiry_mutex));
	mutex_unlock(&sdev->inquiry_mutex);

	अगर (vpd_buf)
		kमुक्त_rcu(vpd_buf, rcu);
पूर्ण

/**
 * scsi_attach_vpd - Attach Vital Product Data to a SCSI device काष्ठाure
 * @sdev: The device to ask
 *
 * Attach the 'Device Identification' VPD page (0x83) and the
 * 'Unit Serial Number' VPD page (0x80) to a SCSI device
 * काष्ठाure. This inक्रमmation can be used to identअगरy the device
 * uniquely.
 */
व्योम scsi_attach_vpd(काष्ठा scsi_device *sdev)
अणु
	पूर्णांक i;
	काष्ठा scsi_vpd *vpd_buf;

	अगर (!scsi_device_supports_vpd(sdev))
		वापस;

	/* Ask क्रम all the pages supported by this device */
	vpd_buf = scsi_get_vpd_buf(sdev, 0);
	अगर (!vpd_buf)
		वापस;

	क्रम (i = 4; i < vpd_buf->len; i++) अणु
		अगर (vpd_buf->data[i] == 0x0)
			scsi_update_vpd_page(sdev, 0x0, &sdev->vpd_pg0);
		अगर (vpd_buf->data[i] == 0x80)
			scsi_update_vpd_page(sdev, 0x80, &sdev->vpd_pg80);
		अगर (vpd_buf->data[i] == 0x83)
			scsi_update_vpd_page(sdev, 0x83, &sdev->vpd_pg83);
		अगर (vpd_buf->data[i] == 0x89)
			scsi_update_vpd_page(sdev, 0x89, &sdev->vpd_pg89);
	पूर्ण
	kमुक्त(vpd_buf);
पूर्ण

/**
 * scsi_report_opcode - Find out अगर a given command opcode is supported
 * @sdev:	scsi device to query
 * @buffer:	scratch buffer (must be at least 20 bytes दीर्घ)
 * @len:	length of buffer
 * @opcode:	opcode क्रम command to look up
 *
 * Uses the REPORT SUPPORTED OPERATION CODES to look up the given
 * opcode. Returns -EINVAL अगर RSOC fails, 0 अगर the command opcode is
 * unsupported and 1 अगर the device claims to support the command.
 */
पूर्णांक scsi_report_opcode(काष्ठा scsi_device *sdev, अचिन्हित अक्षर *buffer,
		       अचिन्हित पूर्णांक len, अचिन्हित अक्षर opcode)
अणु
	अचिन्हित अक्षर cmd[16];
	काष्ठा scsi_sense_hdr sshdr;
	पूर्णांक result;

	अगर (sdev->no_report_opcodes || sdev->scsi_level < SCSI_SPC_3)
		वापस -EINVAL;

	स_रखो(cmd, 0, 16);
	cmd[0] = MAINTEन_अंकCE_IN;
	cmd[1] = MI_REPORT_SUPPORTED_OPERATION_CODES;
	cmd[2] = 1;		/* One command क्रमmat */
	cmd[3] = opcode;
	put_unaligned_be32(len, &cmd[6]);
	स_रखो(buffer, 0, len);

	result = scsi_execute_req(sdev, cmd, DMA_FROM_DEVICE, buffer, len,
				  &sshdr, 30 * HZ, 3, शून्य);

	अगर (result && scsi_sense_valid(&sshdr) &&
	    sshdr.sense_key == ILLEGAL_REQUEST &&
	    (sshdr.asc == 0x20 || sshdr.asc == 0x24) && sshdr.ascq == 0x00)
		वापस -EINVAL;

	अगर ((buffer[1] & 3) == 3) /* Command supported */
		वापस 1;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(scsi_report_opcode);

/**
 * scsi_device_get  -  get an additional reference to a scsi_device
 * @sdev:	device to get a reference to
 *
 * Description: Gets a reference to the scsi_device and increments the use count
 * of the underlying LLDD module.  You must hold host_lock of the
 * parent Scsi_Host or alपढ़ोy have a reference when calling this.
 *
 * This will fail अगर a device is deleted or cancelled, or when the LLD module
 * is in the process of being unloaded.
 */
पूर्णांक scsi_device_get(काष्ठा scsi_device *sdev)
अणु
	अगर (sdev->sdev_state == SDEV_DEL || sdev->sdev_state == SDEV_CANCEL)
		जाओ fail;
	अगर (!get_device(&sdev->sdev_gendev))
		जाओ fail;
	अगर (!try_module_get(sdev->host->hostt->module))
		जाओ fail_put_device;
	वापस 0;

fail_put_device:
	put_device(&sdev->sdev_gendev);
fail:
	वापस -ENXIO;
पूर्ण
EXPORT_SYMBOL(scsi_device_get);

/**
 * scsi_device_put  -  release a reference to a scsi_device
 * @sdev:	device to release a reference on.
 *
 * Description: Release a reference to the scsi_device and decrements the use
 * count of the underlying LLDD module.  The device is मुक्तd once the last
 * user vanishes.
 */
व्योम scsi_device_put(काष्ठा scsi_device *sdev)
अणु
	module_put(sdev->host->hostt->module);
	put_device(&sdev->sdev_gendev);
पूर्ण
EXPORT_SYMBOL(scsi_device_put);

/* helper क्रम shost_क्रम_each_device, see that क्रम करोcumentation */
काष्ठा scsi_device *__scsi_iterate_devices(काष्ठा Scsi_Host *shost,
					   काष्ठा scsi_device *prev)
अणु
	काष्ठा list_head *list = (prev ? &prev->siblings : &shost->__devices);
	काष्ठा scsi_device *next = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(shost->host_lock, flags);
	जबतक (list->next != &shost->__devices) अणु
		next = list_entry(list->next, काष्ठा scsi_device, siblings);
		/* skip devices that we can't get a reference to */
		अगर (!scsi_device_get(next))
			अवरोध;
		next = शून्य;
		list = list->next;
	पूर्ण
	spin_unlock_irqrestore(shost->host_lock, flags);

	अगर (prev)
		scsi_device_put(prev);
	वापस next;
पूर्ण
EXPORT_SYMBOL(__scsi_iterate_devices);

/**
 * starget_क्रम_each_device  -  helper to walk all devices of a target
 * @starget:	target whose devices we want to iterate over.
 * @data:	Opaque passed to each function call.
 * @fn:		Function to call on each device
 *
 * This traverses over each device of @starget.  The devices have
 * a reference that must be released by scsi_host_put when अवरोधing
 * out of the loop.
 */
व्योम starget_क्रम_each_device(काष्ठा scsi_target *starget, व्योम *data,
		     व्योम (*fn)(काष्ठा scsi_device *, व्योम *))
अणु
	काष्ठा Scsi_Host *shost = dev_to_shost(starget->dev.parent);
	काष्ठा scsi_device *sdev;

	shost_क्रम_each_device(sdev, shost) अणु
		अगर ((sdev->channel == starget->channel) &&
		    (sdev->id == starget->id))
			fn(sdev, data);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(starget_क्रम_each_device);

/**
 * __starget_क्रम_each_device - helper to walk all devices of a target (UNLOCKED)
 * @starget:	target whose devices we want to iterate over.
 * @data:	parameter क्रम callback @fn()
 * @fn:		callback function that is invoked क्रम each device
 *
 * This traverses over each device of @starget.  It करोes _not_
 * take a reference on the scsi_device, so the whole loop must be
 * रक्षित by shost->host_lock.
 *
 * Note:  The only reason why drivers would want to use this is because
 * they need to access the device list in irq context.  Otherwise you
 * really want to use starget_क्रम_each_device instead.
 **/
व्योम __starget_क्रम_each_device(काष्ठा scsi_target *starget, व्योम *data,
			       व्योम (*fn)(काष्ठा scsi_device *, व्योम *))
अणु
	काष्ठा Scsi_Host *shost = dev_to_shost(starget->dev.parent);
	काष्ठा scsi_device *sdev;

	__shost_क्रम_each_device(sdev, shost) अणु
		अगर ((sdev->channel == starget->channel) &&
		    (sdev->id == starget->id))
			fn(sdev, data);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(__starget_क्रम_each_device);

/**
 * __scsi_device_lookup_by_target - find a device given the target (UNLOCKED)
 * @starget:	SCSI target poपूर्णांकer
 * @lun:	SCSI Logical Unit Number
 *
 * Description: Looks up the scsi_device with the specअगरied @lun क्रम a given
 * @starget.  The वापसed scsi_device करोes not have an additional
 * reference.  You must hold the host's host_lock over this call and
 * any access to the वापसed scsi_device. A scsi_device in state
 * SDEV_DEL is skipped.
 *
 * Note:  The only reason why drivers should use this is because
 * they need to access the device list in irq context.  Otherwise you
 * really want to use scsi_device_lookup_by_target instead.
 **/
काष्ठा scsi_device *__scsi_device_lookup_by_target(काष्ठा scsi_target *starget,
						   u64 lun)
अणु
	काष्ठा scsi_device *sdev;

	list_क्रम_each_entry(sdev, &starget->devices, same_target_siblings) अणु
		अगर (sdev->sdev_state == SDEV_DEL)
			जारी;
		अगर (sdev->lun ==lun)
			वापस sdev;
	पूर्ण

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(__scsi_device_lookup_by_target);

/**
 * scsi_device_lookup_by_target - find a device given the target
 * @starget:	SCSI target poपूर्णांकer
 * @lun:	SCSI Logical Unit Number
 *
 * Description: Looks up the scsi_device with the specअगरied @lun क्रम a given
 * @starget.  The वापसed scsi_device has an additional reference that
 * needs to be released with scsi_device_put once you're करोne with it.
 **/
काष्ठा scsi_device *scsi_device_lookup_by_target(काष्ठा scsi_target *starget,
						 u64 lun)
अणु
	काष्ठा scsi_device *sdev;
	काष्ठा Scsi_Host *shost = dev_to_shost(starget->dev.parent);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(shost->host_lock, flags);
	sdev = __scsi_device_lookup_by_target(starget, lun);
	अगर (sdev && scsi_device_get(sdev))
		sdev = शून्य;
	spin_unlock_irqrestore(shost->host_lock, flags);

	वापस sdev;
पूर्ण
EXPORT_SYMBOL(scsi_device_lookup_by_target);

/**
 * __scsi_device_lookup - find a device given the host (UNLOCKED)
 * @shost:	SCSI host poपूर्णांकer
 * @channel:	SCSI channel (zero अगर only one channel)
 * @id:		SCSI target number (physical unit number)
 * @lun:	SCSI Logical Unit Number
 *
 * Description: Looks up the scsi_device with the specअगरied @channel, @id, @lun
 * क्रम a given host. The वापसed scsi_device करोes not have an additional
 * reference.  You must hold the host's host_lock over this call and any access
 * to the वापसed scsi_device.
 *
 * Note:  The only reason why drivers would want to use this is because
 * they need to access the device list in irq context.  Otherwise you
 * really want to use scsi_device_lookup instead.
 **/
काष्ठा scsi_device *__scsi_device_lookup(काष्ठा Scsi_Host *shost,
		uपूर्णांक channel, uपूर्णांक id, u64 lun)
अणु
	काष्ठा scsi_device *sdev;

	list_क्रम_each_entry(sdev, &shost->__devices, siblings) अणु
		अगर (sdev->sdev_state == SDEV_DEL)
			जारी;
		अगर (sdev->channel == channel && sdev->id == id &&
				sdev->lun ==lun)
			वापस sdev;
	पूर्ण

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(__scsi_device_lookup);

/**
 * scsi_device_lookup - find a device given the host
 * @shost:	SCSI host poपूर्णांकer
 * @channel:	SCSI channel (zero अगर only one channel)
 * @id:		SCSI target number (physical unit number)
 * @lun:	SCSI Logical Unit Number
 *
 * Description: Looks up the scsi_device with the specअगरied @channel, @id, @lun
 * क्रम a given host.  The वापसed scsi_device has an additional reference that
 * needs to be released with scsi_device_put once you're करोne with it.
 **/
काष्ठा scsi_device *scsi_device_lookup(काष्ठा Scsi_Host *shost,
		uपूर्णांक channel, uपूर्णांक id, u64 lun)
अणु
	काष्ठा scsi_device *sdev;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(shost->host_lock, flags);
	sdev = __scsi_device_lookup(shost, channel, id, lun);
	अगर (sdev && scsi_device_get(sdev))
		sdev = शून्य;
	spin_unlock_irqrestore(shost->host_lock, flags);

	वापस sdev;
पूर्ण
EXPORT_SYMBOL(scsi_device_lookup);

MODULE_DESCRIPTION("SCSI core");
MODULE_LICENSE("GPL");

module_param(scsi_logging_level, पूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(scsi_logging_level, "a bit mask of logging levels");

अटल पूर्णांक __init init_scsi(व्योम)
अणु
	पूर्णांक error;

	error = scsi_init_procfs();
	अगर (error)
		जाओ cleanup_queue;
	error = scsi_init_devinfo();
	अगर (error)
		जाओ cleanup_procfs;
	error = scsi_init_hosts();
	अगर (error)
		जाओ cleanup_devlist;
	error = scsi_init_sysctl();
	अगर (error)
		जाओ cleanup_hosts;
	error = scsi_sysfs_रेजिस्टर();
	अगर (error)
		जाओ cleanup_sysctl;

	scsi_netlink_init();

	prपूर्णांकk(KERN_NOTICE "SCSI subsystem initialized\n");
	वापस 0;

cleanup_sysctl:
	scsi_निकास_sysctl();
cleanup_hosts:
	scsi_निकास_hosts();
cleanup_devlist:
	scsi_निकास_devinfo();
cleanup_procfs:
	scsi_निकास_procfs();
cleanup_queue:
	scsi_निकास_queue();
	prपूर्णांकk(KERN_ERR "SCSI subsystem failed to initialize, error = %d\n",
	       -error);
	वापस error;
पूर्ण

अटल व्योम __निकास निकास_scsi(व्योम)
अणु
	scsi_netlink_निकास();
	scsi_sysfs_unरेजिस्टर();
	scsi_निकास_sysctl();
	scsi_निकास_hosts();
	scsi_निकास_devinfo();
	scsi_निकास_procfs();
	scsi_निकास_queue();
पूर्ण

subsys_initcall(init_scsi);
module_निकास(निकास_scsi);
