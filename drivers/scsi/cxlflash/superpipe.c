<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * CXL Flash Device Driver
 *
 * Written by: Manoj N. Kumar <manoj@linux.vnet.ibm.com>, IBM Corporation
 *             Matthew R. Ochs <mrochs@linux.vnet.ibm.com>, IBM Corporation
 *
 * Copyright (C) 2015 IBM Corporation
 */

#समावेश <linux/delay.h>
#समावेश <linux/file.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/syscalls.h>
#समावेश <यंत्र/unaligned.h>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_eh.h>
#समावेश <uapi/scsi/cxlflash_ioctl.h>

#समावेश "sislite.h"
#समावेश "common.h"
#समावेश "vlun.h"
#समावेश "superpipe.h"

काष्ठा cxlflash_global global;

/**
 * marshal_rele_to_resize() - translate release to resize काष्ठाure
 * @release:	Source काष्ठाure from which to translate/copy.
 * @resize:	Destination काष्ठाure क्रम the translate/copy.
 */
अटल व्योम marshal_rele_to_resize(काष्ठा dk_cxlflash_release *release,
				   काष्ठा dk_cxlflash_resize *resize)
अणु
	resize->hdr = release->hdr;
	resize->context_id = release->context_id;
	resize->rsrc_handle = release->rsrc_handle;
पूर्ण

/**
 * marshal_det_to_rele() - translate detach to release काष्ठाure
 * @detach:	Destination काष्ठाure क्रम the translate/copy.
 * @release:	Source काष्ठाure from which to translate/copy.
 */
अटल व्योम marshal_det_to_rele(काष्ठा dk_cxlflash_detach *detach,
				काष्ठा dk_cxlflash_release *release)
अणु
	release->hdr = detach->hdr;
	release->context_id = detach->context_id;
पूर्ण

/**
 * marshal_udir_to_rele() - translate udirect to release काष्ठाure
 * @udirect:	Source काष्ठाure from which to translate/copy.
 * @release:	Destination काष्ठाure क्रम the translate/copy.
 */
अटल व्योम marshal_udir_to_rele(काष्ठा dk_cxlflash_udirect *udirect,
				 काष्ठा dk_cxlflash_release *release)
अणु
	release->hdr = udirect->hdr;
	release->context_id = udirect->context_id;
	release->rsrc_handle = udirect->rsrc_handle;
पूर्ण

/**
 * cxlflash_मुक्त_errpage() - मुक्तs resources associated with global error page
 */
व्योम cxlflash_मुक्त_errpage(व्योम)
अणु

	mutex_lock(&global.mutex);
	अगर (global.err_page) अणु
		__मुक्त_page(global.err_page);
		global.err_page = शून्य;
	पूर्ण
	mutex_unlock(&global.mutex);
पूर्ण

/**
 * cxlflash_stop_term_user_contexts() - stops/terminates known user contexts
 * @cfg:	Internal काष्ठाure associated with the host.
 *
 * When the host needs to go करोwn, all users must be quiesced and their
 * memory मुक्तd. This is accomplished by putting the contexts in error
 * state which will notअगरy the user and let them 'drive' the tear करोwn.
 * Meanजबतक, this routine camps until all user contexts have been हटाओd.
 *
 * Note that the मुख्य loop in this routine will always execute at least once
 * to flush the reset_रुकोq.
 */
व्योम cxlflash_stop_term_user_contexts(काष्ठा cxlflash_cfg *cfg)
अणु
	काष्ठा device *dev = &cfg->dev->dev;
	पूर्णांक i, found = true;

	cxlflash_mark_contexts_error(cfg);

	जबतक (true) अणु
		क्रम (i = 0; i < MAX_CONTEXT; i++)
			अगर (cfg->ctx_tbl[i]) अणु
				found = true;
				अवरोध;
			पूर्ण

		अगर (!found && list_empty(&cfg->ctx_err_recovery))
			वापस;

		dev_dbg(dev, "%s: Wait for user contexts to quiesce...\n",
			__func__);
		wake_up_all(&cfg->reset_रुकोq);
		ssleep(1);
		found = false;
	पूर्ण
पूर्ण

/**
 * find_error_context() - locates a context by cookie on the error recovery list
 * @cfg:	Internal काष्ठाure associated with the host.
 * @rctxid:	Desired context by id.
 * @file:	Desired context by file.
 *
 * Return: Found context on success, शून्य on failure
 */
अटल काष्ठा ctx_info *find_error_context(काष्ठा cxlflash_cfg *cfg, u64 rctxid,
					   काष्ठा file *file)
अणु
	काष्ठा ctx_info *ctxi;

	list_क्रम_each_entry(ctxi, &cfg->ctx_err_recovery, list)
		अगर ((ctxi->ctxid == rctxid) || (ctxi->file == file))
			वापस ctxi;

	वापस शून्य;
पूर्ण

/**
 * get_context() - obtains a validated and locked context reference
 * @cfg:	Internal काष्ठाure associated with the host.
 * @rctxid:	Desired context (raw, un-decoded क्रमmat).
 * @arg:	LUN inक्रमmation or file associated with request.
 * @ctx_ctrl:	Control inक्रमmation to 'steer' desired lookup.
 *
 * NOTE: despite the name pid, in linux, current->pid actually refers
 * to the lightweight process id (tid) and can change अगर the process is
 * multi thपढ़ोed. The tgid reमुख्यs स्थिरant क्रम the process and only changes
 * when the process of विभाजन. For all पूर्णांकents and purposes, think of tgid
 * as a pid in the traditional sense.
 *
 * Return: Validated context on success, शून्य on failure
 */
काष्ठा ctx_info *get_context(काष्ठा cxlflash_cfg *cfg, u64 rctxid,
			     व्योम *arg, क्रमागत ctx_ctrl ctx_ctrl)
अणु
	काष्ठा device *dev = &cfg->dev->dev;
	काष्ठा ctx_info *ctxi = शून्य;
	काष्ठा lun_access *lun_access = शून्य;
	काष्ठा file *file = शून्य;
	काष्ठा llun_info *lli = arg;
	u64 ctxid = DECODE_CTXID(rctxid);
	पूर्णांक rc;
	pid_t pid = task_tgid_nr(current), ctxpid = 0;

	अगर (ctx_ctrl & CTX_CTRL_खाता) अणु
		lli = शून्य;
		file = (काष्ठा file *)arg;
	पूर्ण

	अगर (ctx_ctrl & CTX_CTRL_CLONE)
		pid = task_ppid_nr(current);

	अगर (likely(ctxid < MAX_CONTEXT)) अणु
		जबतक (true) अणु
			mutex_lock(&cfg->ctx_tbl_list_mutex);
			ctxi = cfg->ctx_tbl[ctxid];
			अगर (ctxi)
				अगर ((file && (ctxi->file != file)) ||
				    (!file && (ctxi->ctxid != rctxid)))
					ctxi = शून्य;

			अगर ((ctx_ctrl & CTX_CTRL_ERR) ||
			    (!ctxi && (ctx_ctrl & CTX_CTRL_ERR_FALLBACK)))
				ctxi = find_error_context(cfg, rctxid, file);
			अगर (!ctxi) अणु
				mutex_unlock(&cfg->ctx_tbl_list_mutex);
				जाओ out;
			पूर्ण

			/*
			 * Need to acquire ownership of the context जबतक still
			 * under the table/list lock to serialize with a हटाओ
			 * thपढ़ो. Use the 'try' to aव्योम stalling the
			 * table/list lock क्रम a single context.
			 *
			 * Note that the lock order is:
			 *
			 *	cfg->ctx_tbl_list_mutex -> ctxi->mutex
			 *
			 * Thereक्रमe release ctx_tbl_list_mutex beक्रमe retrying.
			 */
			rc = mutex_trylock(&ctxi->mutex);
			mutex_unlock(&cfg->ctx_tbl_list_mutex);
			अगर (rc)
				अवरोध; /* got the context's lock! */
		पूर्ण

		अगर (ctxi->unavail)
			जाओ denied;

		ctxpid = ctxi->pid;
		अगर (likely(!(ctx_ctrl & CTX_CTRL_NOPID)))
			अगर (pid != ctxpid)
				जाओ denied;

		अगर (lli) अणु
			list_क्रम_each_entry(lun_access, &ctxi->luns, list)
				अगर (lun_access->lli == lli)
					जाओ out;
			जाओ denied;
		पूर्ण
	पूर्ण

out:
	dev_dbg(dev, "%s: rctxid=%016llx ctxinfo=%p ctxpid=%u pid=%u "
		"ctx_ctrl=%u\n", __func__, rctxid, ctxi, ctxpid, pid,
		ctx_ctrl);

	वापस ctxi;

denied:
	mutex_unlock(&ctxi->mutex);
	ctxi = शून्य;
	जाओ out;
पूर्ण

/**
 * put_context() - release a context that was retrieved from get_context()
 * @ctxi:	Context to release.
 *
 * For now, releasing the context equates to unlocking it's mutex.
 */
व्योम put_context(काष्ठा ctx_info *ctxi)
अणु
	mutex_unlock(&ctxi->mutex);
पूर्ण

/**
 * afu_attach() - attach a context to the AFU
 * @cfg:	Internal काष्ठाure associated with the host.
 * @ctxi:	Context to attach.
 *
 * Upon setting the context capabilities, they must be confirmed with
 * a पढ़ो back operation as the context might have been बंदd since
 * the mailbox was unlocked. When this occurs, registration is failed.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
अटल पूर्णांक afu_attach(काष्ठा cxlflash_cfg *cfg, काष्ठा ctx_info *ctxi)
अणु
	काष्ठा device *dev = &cfg->dev->dev;
	काष्ठा afu *afu = cfg->afu;
	काष्ठा sisl_ctrl_map __iomem *ctrl_map = ctxi->ctrl_map;
	पूर्णांक rc = 0;
	काष्ठा hwq *hwq = get_hwq(afu, PRIMARY_HWQ);
	u64 val;
	पूर्णांक i;

	/* Unlock cap and restrict user to पढ़ो/ग_लिखो cmds in translated mode */
	पढ़ोq_be(&ctrl_map->mbox_r);
	val = (SISL_CTX_CAP_READ_CMD | SISL_CTX_CAP_WRITE_CMD);
	ग_लिखोq_be(val, &ctrl_map->ctx_cap);
	val = पढ़ोq_be(&ctrl_map->ctx_cap);
	अगर (val != (SISL_CTX_CAP_READ_CMD | SISL_CTX_CAP_WRITE_CMD)) अणु
		dev_err(dev, "%s: ctx may be closed val=%016llx\n",
			__func__, val);
		rc = -EAGAIN;
		जाओ out;
	पूर्ण

	अगर (afu_is_ocxl_lisn(afu)) अणु
		/* Set up the LISN effective address क्रम each पूर्णांकerrupt */
		क्रम (i = 0; i < ctxi->irqs; i++) अणु
			val = cfg->ops->get_irq_objhndl(ctxi->ctx, i);
			ग_लिखोq_be(val, &ctrl_map->lisn_ea[i]);
		पूर्ण

		/* Use primary HWQ PASID as identअगरier क्रम all पूर्णांकerrupts */
		val = hwq->ctx_hndl;
		ग_लिखोq_be(SISL_LISN_PASID(val, val), &ctrl_map->lisn_pasid[0]);
		ग_लिखोq_be(SISL_LISN_PASID(0UL, val), &ctrl_map->lisn_pasid[1]);
	पूर्ण

	/* Set up MMIO रेजिस्टरs poपूर्णांकing to the RHT */
	ग_लिखोq_be((u64)ctxi->rht_start, &ctrl_map->rht_start);
	val = SISL_RHT_CNT_ID((u64)MAX_RHT_PER_CONTEXT, (u64)(hwq->ctx_hndl));
	ग_लिखोq_be(val, &ctrl_map->rht_cnt_id);
out:
	dev_dbg(dev, "%s: returning rc=%d\n", __func__, rc);
	वापस rc;
पूर्ण

/**
 * पढ़ो_cap16() - issues a SCSI READ_CAP16 command
 * @sdev:	SCSI device associated with LUN.
 * @lli:	LUN destined क्रम capacity request.
 *
 * The READ_CAP16 can take quite a जबतक to complete. Should an EEH occur जबतक
 * in scsi_execute(), the EEH handler will attempt to recover. As part of the
 * recovery, the handler drains all currently running ioctls, रुकोing until they
 * have completed beक्रमe proceeding with a reset. As this routine is used on the
 * ioctl path, this can create a condition where the EEH handler becomes stuck,
 * infinitely रुकोing क्रम this ioctl thपढ़ो. To aव्योम this behavior, temporarily
 * unmark this thपढ़ो as an ioctl thपढ़ो by releasing the ioctl पढ़ो semaphore.
 * This will allow the EEH handler to proceed with a recovery जबतक this thपढ़ो
 * is still running. Once the scsi_execute() वापसs, reacquire the ioctl पढ़ो
 * semaphore and check the adapter state in हाल it changed जबतक inside of
 * scsi_execute(). The state check will रुको अगर the adapter is still being
 * recovered or वापस a failure अगर the recovery failed. In the event that the
 * adapter reset failed, simply वापस the failure as the ioctl would be unable
 * to जारी.
 *
 * Note that the above माला_दो a requirement on this routine to only be called on
 * an ioctl thपढ़ो.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
अटल पूर्णांक पढ़ो_cap16(काष्ठा scsi_device *sdev, काष्ठा llun_info *lli)
अणु
	काष्ठा cxlflash_cfg *cfg = shost_priv(sdev->host);
	काष्ठा device *dev = &cfg->dev->dev;
	काष्ठा glun_info *gli = lli->parent;
	काष्ठा scsi_sense_hdr sshdr;
	u8 *cmd_buf = शून्य;
	u8 *scsi_cmd = शून्य;
	पूर्णांक rc = 0;
	पूर्णांक result = 0;
	पूर्णांक retry_cnt = 0;
	u32 to = CMD_TIMEOUT * HZ;

retry:
	cmd_buf = kzalloc(CMD_बफ_मानE, GFP_KERNEL);
	scsi_cmd = kzalloc(MAX_COMMAND_SIZE, GFP_KERNEL);
	अगर (unlikely(!cmd_buf || !scsi_cmd)) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	scsi_cmd[0] = SERVICE_ACTION_IN_16;	/* पढ़ो cap(16) */
	scsi_cmd[1] = SAI_READ_CAPACITY_16;	/* service action */
	put_unaligned_be32(CMD_बफ_मानE, &scsi_cmd[10]);

	dev_dbg(dev, "%s: %ssending cmd(%02x)\n", __func__,
		retry_cnt ? "re" : "", scsi_cmd[0]);

	/* Drop the ioctl पढ़ो semahpore across lengthy call */
	up_पढ़ो(&cfg->ioctl_rwsem);
	result = scsi_execute(sdev, scsi_cmd, DMA_FROM_DEVICE, cmd_buf,
			      CMD_बफ_मानE, शून्य, &sshdr, to, CMD_RETRIES,
			      0, 0, शून्य);
	करोwn_पढ़ो(&cfg->ioctl_rwsem);
	rc = check_state(cfg);
	अगर (rc) अणु
		dev_err(dev, "%s: Failed state result=%08x\n",
			__func__, result);
		rc = -ENODEV;
		जाओ out;
	पूर्ण

	अगर (driver_byte(result) == DRIVER_SENSE) अणु
		result &= ~(0xFF<<24); /* DRIVER_SENSE is not an error */
		अगर (result & SAM_STAT_CHECK_CONDITION) अणु
			चयन (sshdr.sense_key) अणु
			हाल NO_SENSE:
			हाल RECOVERED_ERROR:
			हाल NOT_READY:
				result &= ~SAM_STAT_CHECK_CONDITION;
				अवरोध;
			हाल UNIT_ATTENTION:
				चयन (sshdr.asc) अणु
				हाल 0x29: /* Power on Reset or Device Reset */
					fallthrough;
				हाल 0x2A: /* Device capacity changed */
				हाल 0x3F: /* Report LUNs changed */
					/* Retry the command once more */
					अगर (retry_cnt++ < 1) अणु
						kमुक्त(cmd_buf);
						kमुक्त(scsi_cmd);
						जाओ retry;
					पूर्ण
				पूर्ण
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (result) अणु
		dev_err(dev, "%s: command failed, result=%08x\n",
			__func__, result);
		rc = -EIO;
		जाओ out;
	पूर्ण

	/*
	 * Read cap was successful, grab values from the buffer;
	 * note that we करोn't need to worry about unaligned access
	 * as the buffer is allocated on an aligned boundary.
	 */
	mutex_lock(&gli->mutex);
	gli->max_lba = be64_to_cpu(*((__be64 *)&cmd_buf[0]));
	gli->blk_len = be32_to_cpu(*((__be32 *)&cmd_buf[8]));
	mutex_unlock(&gli->mutex);

out:
	kमुक्त(cmd_buf);
	kमुक्त(scsi_cmd);

	dev_dbg(dev, "%s: maxlba=%lld blklen=%d rc=%d\n",
		__func__, gli->max_lba, gli->blk_len, rc);
	वापस rc;
पूर्ण

/**
 * get_rhte() - obtains validated resource handle table entry reference
 * @ctxi:	Context owning the resource handle.
 * @rhndl:	Resource handle associated with entry.
 * @lli:	LUN associated with request.
 *
 * Return: Validated RHTE on success, शून्य on failure
 */
काष्ठा sisl_rht_entry *get_rhte(काष्ठा ctx_info *ctxi, res_hndl_t rhndl,
				काष्ठा llun_info *lli)
अणु
	काष्ठा cxlflash_cfg *cfg = ctxi->cfg;
	काष्ठा device *dev = &cfg->dev->dev;
	काष्ठा sisl_rht_entry *rhte = शून्य;

	अगर (unlikely(!ctxi->rht_start)) अणु
		dev_dbg(dev, "%s: Context does not have allocated RHT\n",
			 __func__);
		जाओ out;
	पूर्ण

	अगर (unlikely(rhndl >= MAX_RHT_PER_CONTEXT)) अणु
		dev_dbg(dev, "%s: Bad resource handle rhndl=%d\n",
			__func__, rhndl);
		जाओ out;
	पूर्ण

	अगर (unlikely(ctxi->rht_lun[rhndl] != lli)) अणु
		dev_dbg(dev, "%s: Bad resource handle LUN rhndl=%d\n",
			__func__, rhndl);
		जाओ out;
	पूर्ण

	rhte = &ctxi->rht_start[rhndl];
	अगर (unlikely(rhte->nmask == 0)) अणु
		dev_dbg(dev, "%s: Unopened resource handle rhndl=%d\n",
			__func__, rhndl);
		rhte = शून्य;
		जाओ out;
	पूर्ण

out:
	वापस rhte;
पूर्ण

/**
 * rhte_checkout() - obtains मुक्त/empty resource handle table entry
 * @ctxi:	Context owning the resource handle.
 * @lli:	LUN associated with request.
 *
 * Return: Free RHTE on success, शून्य on failure
 */
काष्ठा sisl_rht_entry *rhte_checkout(काष्ठा ctx_info *ctxi,
				     काष्ठा llun_info *lli)
अणु
	काष्ठा cxlflash_cfg *cfg = ctxi->cfg;
	काष्ठा device *dev = &cfg->dev->dev;
	काष्ठा sisl_rht_entry *rhte = शून्य;
	पूर्णांक i;

	/* Find a मुक्त RHT entry */
	क्रम (i = 0; i < MAX_RHT_PER_CONTEXT; i++)
		अगर (ctxi->rht_start[i].nmask == 0) अणु
			rhte = &ctxi->rht_start[i];
			ctxi->rht_out++;
			अवरोध;
		पूर्ण

	अगर (likely(rhte))
		ctxi->rht_lun[i] = lli;

	dev_dbg(dev, "%s: returning rhte=%p index=%d\n", __func__, rhte, i);
	वापस rhte;
पूर्ण

/**
 * rhte_checkin() - releases a resource handle table entry
 * @ctxi:	Context owning the resource handle.
 * @rhte:	RHTE to release.
 */
व्योम rhte_checkin(काष्ठा ctx_info *ctxi,
		  काष्ठा sisl_rht_entry *rhte)
अणु
	u32 rsrc_handle = rhte - ctxi->rht_start;

	rhte->nmask = 0;
	rhte->fp = 0;
	ctxi->rht_out--;
	ctxi->rht_lun[rsrc_handle] = शून्य;
	ctxi->rht_needs_ws[rsrc_handle] = false;
पूर्ण

/**
 * rht_क्रमmat1() - populates a RHTE क्रम क्रमmat 1
 * @rhte:	RHTE to populate.
 * @lun_id:	LUN ID of LUN associated with RHTE.
 * @perm:	Desired permissions क्रम RHTE.
 * @port_sel:	Port selection mask
 */
अटल व्योम rht_क्रमmat1(काष्ठा sisl_rht_entry *rhte, u64 lun_id, u32 perm,
			u32 port_sel)
अणु
	/*
	 * Populate the Format 1 RHT entry क्रम direct access (physical
	 * LUN) using the synchronization sequence defined in the
	 * SISLite specअगरication.
	 */
	काष्ठा sisl_rht_entry_f1 dummy = अणु 0 पूर्ण;
	काष्ठा sisl_rht_entry_f1 *rhte_f1 = (काष्ठा sisl_rht_entry_f1 *)rhte;

	स_रखो(rhte_f1, 0, माप(*rhte_f1));
	rhte_f1->fp = SISL_RHT_FP(1U, 0);
	dma_wmb(); /* Make setting of क्रमmat bit visible */

	rhte_f1->lun_id = lun_id;
	dma_wmb(); /* Make setting of LUN id visible */

	/*
	 * Use a dummy RHT Format 1 entry to build the second dword
	 * of the entry that must be populated in a single ग_लिखो when
	 * enabled (valid bit set to TRUE).
	 */
	dummy.valid = 0x80;
	dummy.fp = SISL_RHT_FP(1U, perm);
	dummy.port_sel = port_sel;
	rhte_f1->dw = dummy.dw;

	dma_wmb(); /* Make reमुख्यing RHT entry fields visible */
पूर्ण

/**
 * cxlflash_lun_attach() - attaches a user to a LUN and manages the LUN's mode
 * @gli:	LUN to attach.
 * @mode:	Desired mode of the LUN.
 * @locked:	Mutex status on current thपढ़ो.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
पूर्णांक cxlflash_lun_attach(काष्ठा glun_info *gli, क्रमागत lun_mode mode, bool locked)
अणु
	पूर्णांक rc = 0;

	अगर (!locked)
		mutex_lock(&gli->mutex);

	अगर (gli->mode == MODE_NONE)
		gli->mode = mode;
	अन्यथा अगर (gli->mode != mode) अणु
		pr_debug("%s: gli_mode=%d requested_mode=%d\n",
			 __func__, gli->mode, mode);
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	gli->users++;
	WARN_ON(gli->users <= 0);
out:
	pr_debug("%s: Returning rc=%d gli->mode=%u gli->users=%u\n",
		 __func__, rc, gli->mode, gli->users);
	अगर (!locked)
		mutex_unlock(&gli->mutex);
	वापस rc;
पूर्ण

/**
 * cxlflash_lun_detach() - detaches a user from a LUN and resets the LUN's mode
 * @gli:	LUN to detach.
 *
 * When resetting the mode, terminate block allocation resources as they
 * are no दीर्घer required (service is safe to call even when block allocation
 * resources were not present - such as when transitioning from physical mode).
 * These resources will be पुनः_स्मृतिated when needed (subsequent transition to
 * भव mode).
 */
व्योम cxlflash_lun_detach(काष्ठा glun_info *gli)
अणु
	mutex_lock(&gli->mutex);
	WARN_ON(gli->mode == MODE_NONE);
	अगर (--gli->users == 0) अणु
		gli->mode = MODE_NONE;
		cxlflash_ba_terminate(&gli->blka.ba_lun);
	पूर्ण
	pr_debug("%s: gli->users=%u\n", __func__, gli->users);
	WARN_ON(gli->users < 0);
	mutex_unlock(&gli->mutex);
पूर्ण

/**
 * _cxlflash_disk_release() - releases the specअगरied resource entry
 * @sdev:	SCSI device associated with LUN.
 * @ctxi:	Context owning resources.
 * @release:	Release ioctl data काष्ठाure.
 *
 * For LUNs in भव mode, the भव LUN associated with the specअगरied
 * resource handle is resized to 0 prior to releasing the RHTE. Note that the
 * AFU sync should _not_ be perक्रमmed when the context is sitting on the error
 * recovery list. A context on the error recovery list is not known to the AFU
 * due to reset. When the context is recovered, it will be reattached and made
 * known again to the AFU.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
पूर्णांक _cxlflash_disk_release(काष्ठा scsi_device *sdev,
			   काष्ठा ctx_info *ctxi,
			   काष्ठा dk_cxlflash_release *release)
अणु
	काष्ठा cxlflash_cfg *cfg = shost_priv(sdev->host);
	काष्ठा device *dev = &cfg->dev->dev;
	काष्ठा llun_info *lli = sdev->hostdata;
	काष्ठा glun_info *gli = lli->parent;
	काष्ठा afu *afu = cfg->afu;
	bool put_ctx = false;

	काष्ठा dk_cxlflash_resize size;
	res_hndl_t rhndl = release->rsrc_handle;

	पूर्णांक rc = 0;
	पूर्णांक rcr = 0;
	u64 ctxid = DECODE_CTXID(release->context_id),
	    rctxid = release->context_id;

	काष्ठा sisl_rht_entry *rhte;
	काष्ठा sisl_rht_entry_f1 *rhte_f1;

	dev_dbg(dev, "%s: ctxid=%llu rhndl=%llu gli->mode=%u gli->users=%u\n",
		__func__, ctxid, release->rsrc_handle, gli->mode, gli->users);

	अगर (!ctxi) अणु
		ctxi = get_context(cfg, rctxid, lli, CTX_CTRL_ERR_FALLBACK);
		अगर (unlikely(!ctxi)) अणु
			dev_dbg(dev, "%s: Bad context ctxid=%llu\n",
				__func__, ctxid);
			rc = -EINVAL;
			जाओ out;
		पूर्ण

		put_ctx = true;
	पूर्ण

	rhte = get_rhte(ctxi, rhndl, lli);
	अगर (unlikely(!rhte)) अणु
		dev_dbg(dev, "%s: Bad resource handle rhndl=%d\n",
			__func__, rhndl);
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	/*
	 * Resize to 0 क्रम भव LUNS by setting the size
	 * to 0. This will clear LXT_START and LXT_CNT fields
	 * in the RHT entry and properly sync with the AFU.
	 *
	 * Afterwards we clear the reमुख्यing fields.
	 */
	चयन (gli->mode) अणु
	हाल MODE_VIRTUAL:
		marshal_rele_to_resize(release, &size);
		size.req_size = 0;
		rc = _cxlflash_vlun_resize(sdev, ctxi, &size);
		अगर (rc) अणु
			dev_dbg(dev, "%s: resize failed rc %d\n", __func__, rc);
			जाओ out;
		पूर्ण

		अवरोध;
	हाल MODE_PHYSICAL:
		/*
		 * Clear the Format 1 RHT entry क्रम direct access
		 * (physical LUN) using the synchronization sequence
		 * defined in the SISLite specअगरication.
		 */
		rhte_f1 = (काष्ठा sisl_rht_entry_f1 *)rhte;

		rhte_f1->valid = 0;
		dma_wmb(); /* Make revocation of RHT entry visible */

		rhte_f1->lun_id = 0;
		dma_wmb(); /* Make clearing of LUN id visible */

		rhte_f1->dw = 0;
		dma_wmb(); /* Make RHT entry bottom-half clearing visible */

		अगर (!ctxi->err_recovery_active) अणु
			rcr = cxlflash_afu_sync(afu, ctxid, rhndl, AFU_HW_SYNC);
			अगर (unlikely(rcr))
				dev_dbg(dev, "%s: AFU sync failed rc=%d\n",
					__func__, rcr);
		पूर्ण
		अवरोध;
	शेष:
		WARN(1, "Unsupported LUN mode!");
		जाओ out;
	पूर्ण

	rhte_checkin(ctxi, rhte);
	cxlflash_lun_detach(gli);

out:
	अगर (put_ctx)
		put_context(ctxi);
	dev_dbg(dev, "%s: returning rc=%d\n", __func__, rc);
	वापस rc;
पूर्ण

पूर्णांक cxlflash_disk_release(काष्ठा scsi_device *sdev,
			  काष्ठा dk_cxlflash_release *release)
अणु
	वापस _cxlflash_disk_release(sdev, शून्य, release);
पूर्ण

/**
 * destroy_context() - releases a context
 * @cfg:	Internal काष्ठाure associated with the host.
 * @ctxi:	Context to release.
 *
 * This routine is safe to be called with a a non-initialized context.
 * Also note that the routine conditionally checks क्रम the existence
 * of the context control map beक्रमe clearing the RHT रेजिस्टरs and
 * context capabilities because it is possible to destroy a context
 * जबतक the context is in the error state (previous mapping was
 * हटाओd [so there is no need to worry about clearing] and context
 * is रुकोing क्रम a new mapping).
 */
अटल व्योम destroy_context(काष्ठा cxlflash_cfg *cfg,
			    काष्ठा ctx_info *ctxi)
अणु
	काष्ठा afu *afu = cfg->afu;

	अगर (ctxi->initialized) अणु
		WARN_ON(!list_empty(&ctxi->luns));

		/* Clear RHT रेजिस्टरs and drop all capabilities क्रम context */
		अगर (afu->afu_map && ctxi->ctrl_map) अणु
			ग_लिखोq_be(0, &ctxi->ctrl_map->rht_start);
			ग_लिखोq_be(0, &ctxi->ctrl_map->rht_cnt_id);
			ग_लिखोq_be(0, &ctxi->ctrl_map->ctx_cap);
		पूर्ण
	पूर्ण

	/* Free memory associated with context */
	मुक्त_page((uदीर्घ)ctxi->rht_start);
	kमुक्त(ctxi->rht_needs_ws);
	kमुक्त(ctxi->rht_lun);
	kमुक्त(ctxi);
पूर्ण

/**
 * create_context() - allocates and initializes a context
 * @cfg:	Internal काष्ठाure associated with the host.
 *
 * Return: Allocated context on success, शून्य on failure
 */
अटल काष्ठा ctx_info *create_context(काष्ठा cxlflash_cfg *cfg)
अणु
	काष्ठा device *dev = &cfg->dev->dev;
	काष्ठा ctx_info *ctxi = शून्य;
	काष्ठा llun_info **lli = शून्य;
	u8 *ws = शून्य;
	काष्ठा sisl_rht_entry *rhte;

	ctxi = kzalloc(माप(*ctxi), GFP_KERNEL);
	lli = kzalloc((MAX_RHT_PER_CONTEXT * माप(*lli)), GFP_KERNEL);
	ws = kzalloc((MAX_RHT_PER_CONTEXT * माप(*ws)), GFP_KERNEL);
	अगर (unlikely(!ctxi || !lli || !ws)) अणु
		dev_err(dev, "%s: Unable to allocate context\n", __func__);
		जाओ err;
	पूर्ण

	rhte = (काष्ठा sisl_rht_entry *)get_zeroed_page(GFP_KERNEL);
	अगर (unlikely(!rhte)) अणु
		dev_err(dev, "%s: Unable to allocate RHT\n", __func__);
		जाओ err;
	पूर्ण

	ctxi->rht_lun = lli;
	ctxi->rht_needs_ws = ws;
	ctxi->rht_start = rhte;
out:
	वापस ctxi;

err:
	kमुक्त(ws);
	kमुक्त(lli);
	kमुक्त(ctxi);
	ctxi = शून्य;
	जाओ out;
पूर्ण

/**
 * init_context() - initializes a previously allocated context
 * @ctxi:	Previously allocated context
 * @cfg:	Internal काष्ठाure associated with the host.
 * @ctx:	Previously obtained context cookie.
 * @ctxid:	Previously obtained process element associated with CXL context.
 * @file:	Previously obtained file associated with CXL context.
 * @perms:	User-specअगरied permissions.
 * @irqs:	User-specअगरied number of पूर्णांकerrupts.
 */
अटल व्योम init_context(काष्ठा ctx_info *ctxi, काष्ठा cxlflash_cfg *cfg,
			 व्योम *ctx, पूर्णांक ctxid, काष्ठा file *file, u32 perms,
			 u64 irqs)
अणु
	काष्ठा afu *afu = cfg->afu;

	ctxi->rht_perms = perms;
	ctxi->ctrl_map = &afu->afu_map->ctrls[ctxid].ctrl;
	ctxi->ctxid = ENCODE_CTXID(ctxi, ctxid);
	ctxi->irqs = irqs;
	ctxi->pid = task_tgid_nr(current); /* tgid = pid */
	ctxi->ctx = ctx;
	ctxi->cfg = cfg;
	ctxi->file = file;
	ctxi->initialized = true;
	mutex_init(&ctxi->mutex);
	kref_init(&ctxi->kref);
	INIT_LIST_HEAD(&ctxi->luns);
	INIT_LIST_HEAD(&ctxi->list); /* initialize क्रम list_empty() */
पूर्ण

/**
 * हटाओ_context() - context kref release handler
 * @kref:	Kernel reference associated with context to be हटाओd.
 *
 * When a context no दीर्घer has any references it can safely be हटाओd
 * from global access and destroyed. Note that it is assumed the thपढ़ो
 * relinquishing access to the context holds its mutex.
 */
अटल व्योम हटाओ_context(काष्ठा kref *kref)
अणु
	काष्ठा ctx_info *ctxi = container_of(kref, काष्ठा ctx_info, kref);
	काष्ठा cxlflash_cfg *cfg = ctxi->cfg;
	u64 ctxid = DECODE_CTXID(ctxi->ctxid);

	/* Remove context from table/error list */
	WARN_ON(!mutex_is_locked(&ctxi->mutex));
	ctxi->unavail = true;
	mutex_unlock(&ctxi->mutex);
	mutex_lock(&cfg->ctx_tbl_list_mutex);
	mutex_lock(&ctxi->mutex);

	अगर (!list_empty(&ctxi->list))
		list_del(&ctxi->list);
	cfg->ctx_tbl[ctxid] = शून्य;
	mutex_unlock(&cfg->ctx_tbl_list_mutex);
	mutex_unlock(&ctxi->mutex);

	/* Context now completely uncoupled/unreachable */
	destroy_context(cfg, ctxi);
पूर्ण

/**
 * _cxlflash_disk_detach() - detaches a LUN from a context
 * @sdev:	SCSI device associated with LUN.
 * @ctxi:	Context owning resources.
 * @detach:	Detach ioctl data काष्ठाure.
 *
 * As part of the detach, all per-context resources associated with the LUN
 * are cleaned up. When detaching the last LUN क्रम a context, the context
 * itself is cleaned up and released.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
अटल पूर्णांक _cxlflash_disk_detach(काष्ठा scsi_device *sdev,
				 काष्ठा ctx_info *ctxi,
				 काष्ठा dk_cxlflash_detach *detach)
अणु
	काष्ठा cxlflash_cfg *cfg = shost_priv(sdev->host);
	काष्ठा device *dev = &cfg->dev->dev;
	काष्ठा llun_info *lli = sdev->hostdata;
	काष्ठा lun_access *lun_access, *t;
	काष्ठा dk_cxlflash_release rel;
	bool put_ctx = false;

	पूर्णांक i;
	पूर्णांक rc = 0;
	u64 ctxid = DECODE_CTXID(detach->context_id),
	    rctxid = detach->context_id;

	dev_dbg(dev, "%s: ctxid=%llu\n", __func__, ctxid);

	अगर (!ctxi) अणु
		ctxi = get_context(cfg, rctxid, lli, CTX_CTRL_ERR_FALLBACK);
		अगर (unlikely(!ctxi)) अणु
			dev_dbg(dev, "%s: Bad context ctxid=%llu\n",
				__func__, ctxid);
			rc = -EINVAL;
			जाओ out;
		पूर्ण

		put_ctx = true;
	पूर्ण

	/* Cleanup outstanding resources tied to this LUN */
	अगर (ctxi->rht_out) अणु
		marshal_det_to_rele(detach, &rel);
		क्रम (i = 0; i < MAX_RHT_PER_CONTEXT; i++) अणु
			अगर (ctxi->rht_lun[i] == lli) अणु
				rel.rsrc_handle = i;
				_cxlflash_disk_release(sdev, ctxi, &rel);
			पूर्ण

			/* No need to loop further अगर we're करोne */
			अगर (ctxi->rht_out == 0)
				अवरोध;
		पूर्ण
	पूर्ण

	/* Take our LUN out of context, मुक्त the node */
	list_क्रम_each_entry_safe(lun_access, t, &ctxi->luns, list)
		अगर (lun_access->lli == lli) अणु
			list_del(&lun_access->list);
			kमुक्त(lun_access);
			lun_access = शून्य;
			अवरोध;
		पूर्ण

	/*
	 * Release the context reference and the sdev reference that
	 * bound this LUN to the context.
	 */
	अगर (kref_put(&ctxi->kref, हटाओ_context))
		put_ctx = false;
	scsi_device_put(sdev);
out:
	अगर (put_ctx)
		put_context(ctxi);
	dev_dbg(dev, "%s: returning rc=%d\n", __func__, rc);
	वापस rc;
पूर्ण

अटल पूर्णांक cxlflash_disk_detach(काष्ठा scsi_device *sdev,
				काष्ठा dk_cxlflash_detach *detach)
अणु
	वापस _cxlflash_disk_detach(sdev, शून्य, detach);
पूर्ण

/**
 * cxlflash_cxl_release() - release handler क्रम adapter file descriptor
 * @inode:	File-प्रणाली inode associated with fd.
 * @file:	File installed with adapter file descriptor.
 *
 * This routine is the release handler क्रम the fops रेजिस्टरed with
 * the CXL services on an initial attach क्रम a context. It is called
 * when a बंद (explicity by the user or as part of a process tear
 * करोwn) is perक्रमmed on the adapter file descriptor वापसed to the
 * user. The user should be aware that explicitly perक्रमming a बंद
 * considered catastrophic and subsequent usage of the superpipe API
 * with previously saved off tokens will fail.
 *
 * This routine derives the context reference and calls detach क्रम
 * each LUN associated with the context.The final detach operation
 * causes the context itself to be मुक्तd. With exception to when the
 * CXL process element (context id) lookup fails (a हाल that should
 * theoretically never occur), every call पूर्णांकo this routine results
 * in a complete मुक्तing of a context.
 *
 * Detaching the LUN is typically an ioctl() operation and the underlying
 * code assumes that ioctl_rwsem has been acquired as a पढ़ोer. To support
 * that design poपूर्णांक, the semaphore is acquired and released around detach.
 *
 * Return: 0 on success
 */
अटल पूर्णांक cxlflash_cxl_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा cxlflash_cfg *cfg = container_of(file->f_op, काष्ठा cxlflash_cfg,
						cxl_fops);
	व्योम *ctx = cfg->ops->fops_get_context(file);
	काष्ठा device *dev = &cfg->dev->dev;
	काष्ठा ctx_info *ctxi = शून्य;
	काष्ठा dk_cxlflash_detach detach = अणु अणु 0 पूर्ण, 0 पूर्ण;
	काष्ठा lun_access *lun_access, *t;
	क्रमागत ctx_ctrl ctrl = CTX_CTRL_ERR_FALLBACK | CTX_CTRL_खाता;
	पूर्णांक ctxid;

	ctxid = cfg->ops->process_element(ctx);
	अगर (unlikely(ctxid < 0)) अणु
		dev_err(dev, "%s: Context %p was closed ctxid=%d\n",
			__func__, ctx, ctxid);
		जाओ out;
	पूर्ण

	ctxi = get_context(cfg, ctxid, file, ctrl);
	अगर (unlikely(!ctxi)) अणु
		ctxi = get_context(cfg, ctxid, file, ctrl | CTX_CTRL_CLONE);
		अगर (!ctxi) अणु
			dev_dbg(dev, "%s: ctxid=%d already free\n",
				__func__, ctxid);
			जाओ out_release;
		पूर्ण

		dev_dbg(dev, "%s: Another process owns ctxid=%d\n",
			__func__, ctxid);
		put_context(ctxi);
		जाओ out;
	पूर्ण

	dev_dbg(dev, "%s: close for ctxid=%d\n", __func__, ctxid);

	करोwn_पढ़ो(&cfg->ioctl_rwsem);
	detach.context_id = ctxi->ctxid;
	list_क्रम_each_entry_safe(lun_access, t, &ctxi->luns, list)
		_cxlflash_disk_detach(lun_access->sdev, ctxi, &detach);
	up_पढ़ो(&cfg->ioctl_rwsem);
out_release:
	cfg->ops->fd_release(inode, file);
out:
	dev_dbg(dev, "%s: returning\n", __func__);
	वापस 0;
पूर्ण

/**
 * unmap_context() - clears a previously established mapping
 * @ctxi:	Context owning the mapping.
 *
 * This routine is used to चयन between the error notअगरication page
 * (dummy page of all 1's) and the real mapping (established by the CXL
 * fault handler).
 */
अटल व्योम unmap_context(काष्ठा ctx_info *ctxi)
अणु
	unmap_mapping_range(ctxi->file->f_mapping, 0, 0, 1);
पूर्ण

/**
 * get_err_page() - obtains and allocates the error notअगरication page
 * @cfg:	Internal काष्ठाure associated with the host.
 *
 * Return: error notअगरication page on success, शून्य on failure
 */
अटल काष्ठा page *get_err_page(काष्ठा cxlflash_cfg *cfg)
अणु
	काष्ठा page *err_page = global.err_page;
	काष्ठा device *dev = &cfg->dev->dev;

	अगर (unlikely(!err_page)) अणु
		err_page = alloc_page(GFP_KERNEL);
		अगर (unlikely(!err_page)) अणु
			dev_err(dev, "%s: Unable to allocate err_page\n",
				__func__);
			जाओ out;
		पूर्ण

		स_रखो(page_address(err_page), -1, PAGE_SIZE);

		/* Serialize update w/ other thपढ़ोs to aव्योम a leak */
		mutex_lock(&global.mutex);
		अगर (likely(!global.err_page))
			global.err_page = err_page;
		अन्यथा अणु
			__मुक्त_page(err_page);
			err_page = global.err_page;
		पूर्ण
		mutex_unlock(&global.mutex);
	पूर्ण

out:
	dev_dbg(dev, "%s: returning err_page=%p\n", __func__, err_page);
	वापस err_page;
पूर्ण

/**
 * cxlflash_mmap_fault() - mmap fault handler क्रम adapter file descriptor
 * @vmf:	VM fault associated with current fault.
 *
 * To support error notअगरication via MMIO, faults are 'caught' by this routine
 * that was inserted beक्रमe passing back the adapter file descriptor on attach.
 * When a fault occurs, this routine evaluates अगर error recovery is active and
 * अगर so, installs the error page to 'notify' the user about the error state.
 * During normal operation, the fault is simply handled by the original fault
 * handler that was installed by CXL services as part of initializing the
 * adapter file descriptor. The VMA's page protection bits are toggled to
 * indicate cached/not-cached depending on the memory backing the fault.
 *
 * Return: 0 on success, VM_FAULT_SIGBUS on failure
 */
अटल vm_fault_t cxlflash_mmap_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	काष्ठा file *file = vma->vm_file;
	काष्ठा cxlflash_cfg *cfg = container_of(file->f_op, काष्ठा cxlflash_cfg,
						cxl_fops);
	व्योम *ctx = cfg->ops->fops_get_context(file);
	काष्ठा device *dev = &cfg->dev->dev;
	काष्ठा ctx_info *ctxi = शून्य;
	काष्ठा page *err_page = शून्य;
	क्रमागत ctx_ctrl ctrl = CTX_CTRL_ERR_FALLBACK | CTX_CTRL_खाता;
	vm_fault_t rc = 0;
	पूर्णांक ctxid;

	ctxid = cfg->ops->process_element(ctx);
	अगर (unlikely(ctxid < 0)) अणु
		dev_err(dev, "%s: Context %p was closed ctxid=%d\n",
			__func__, ctx, ctxid);
		जाओ err;
	पूर्ण

	ctxi = get_context(cfg, ctxid, file, ctrl);
	अगर (unlikely(!ctxi)) अणु
		dev_dbg(dev, "%s: Bad context ctxid=%d\n", __func__, ctxid);
		जाओ err;
	पूर्ण

	dev_dbg(dev, "%s: fault for context %d\n", __func__, ctxid);

	अगर (likely(!ctxi->err_recovery_active)) अणु
		vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
		rc = ctxi->cxl_mmap_vmops->fault(vmf);
	पूर्ण अन्यथा अणु
		dev_dbg(dev, "%s: err recovery active, use err_page\n",
			__func__);

		err_page = get_err_page(cfg);
		अगर (unlikely(!err_page)) अणु
			dev_err(dev, "%s: Could not get err_page\n", __func__);
			rc = VM_FAULT_RETRY;
			जाओ out;
		पूर्ण

		get_page(err_page);
		vmf->page = err_page;
		vma->vm_page_prot = pgprot_cached(vma->vm_page_prot);
	पूर्ण

out:
	अगर (likely(ctxi))
		put_context(ctxi);
	dev_dbg(dev, "%s: returning rc=%x\n", __func__, rc);
	वापस rc;

err:
	rc = VM_FAULT_SIGBUS;
	जाओ out;
पूर्ण

/*
 * Local MMAP vmops to 'catch' faults
 */
अटल स्थिर काष्ठा vm_operations_काष्ठा cxlflash_mmap_vmops = अणु
	.fault = cxlflash_mmap_fault,
पूर्ण;

/**
 * cxlflash_cxl_mmap() - mmap handler क्रम adapter file descriptor
 * @file:	File installed with adapter file descriptor.
 * @vma:	VM area associated with mapping.
 *
 * Installs local mmap vmops to 'catch' faults क्रम error notअगरication support.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
अटल पूर्णांक cxlflash_cxl_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा cxlflash_cfg *cfg = container_of(file->f_op, काष्ठा cxlflash_cfg,
						cxl_fops);
	व्योम *ctx = cfg->ops->fops_get_context(file);
	काष्ठा device *dev = &cfg->dev->dev;
	काष्ठा ctx_info *ctxi = शून्य;
	क्रमागत ctx_ctrl ctrl = CTX_CTRL_ERR_FALLBACK | CTX_CTRL_खाता;
	पूर्णांक ctxid;
	पूर्णांक rc = 0;

	ctxid = cfg->ops->process_element(ctx);
	अगर (unlikely(ctxid < 0)) अणु
		dev_err(dev, "%s: Context %p was closed ctxid=%d\n",
			__func__, ctx, ctxid);
		rc = -EIO;
		जाओ out;
	पूर्ण

	ctxi = get_context(cfg, ctxid, file, ctrl);
	अगर (unlikely(!ctxi)) अणु
		dev_dbg(dev, "%s: Bad context ctxid=%d\n", __func__, ctxid);
		rc = -EIO;
		जाओ out;
	पूर्ण

	dev_dbg(dev, "%s: mmap for context %d\n", __func__, ctxid);

	rc = cfg->ops->fd_mmap(file, vma);
	अगर (likely(!rc)) अणु
		/* Insert ourself in the mmap fault handler path */
		ctxi->cxl_mmap_vmops = vma->vm_ops;
		vma->vm_ops = &cxlflash_mmap_vmops;
	पूर्ण

out:
	अगर (likely(ctxi))
		put_context(ctxi);
	वापस rc;
पूर्ण

स्थिर काष्ठा file_operations cxlflash_cxl_fops = अणु
	.owner = THIS_MODULE,
	.mmap = cxlflash_cxl_mmap,
	.release = cxlflash_cxl_release,
पूर्ण;

/**
 * cxlflash_mark_contexts_error() - move contexts to error state and list
 * @cfg:	Internal काष्ठाure associated with the host.
 *
 * A context is only moved over to the error list when there are no outstanding
 * references to it. This ensures that a running operation has completed.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
पूर्णांक cxlflash_mark_contexts_error(काष्ठा cxlflash_cfg *cfg)
अणु
	पूर्णांक i, rc = 0;
	काष्ठा ctx_info *ctxi = शून्य;

	mutex_lock(&cfg->ctx_tbl_list_mutex);

	क्रम (i = 0; i < MAX_CONTEXT; i++) अणु
		ctxi = cfg->ctx_tbl[i];
		अगर (ctxi) अणु
			mutex_lock(&ctxi->mutex);
			cfg->ctx_tbl[i] = शून्य;
			list_add(&ctxi->list, &cfg->ctx_err_recovery);
			ctxi->err_recovery_active = true;
			ctxi->ctrl_map = शून्य;
			unmap_context(ctxi);
			mutex_unlock(&ctxi->mutex);
		पूर्ण
	पूर्ण

	mutex_unlock(&cfg->ctx_tbl_list_mutex);
	वापस rc;
पूर्ण

/*
 * Dummy शून्य fops
 */
अटल स्थिर काष्ठा file_operations null_fops = अणु
	.owner = THIS_MODULE,
पूर्ण;

/**
 * check_state() - checks and responds to the current adapter state
 * @cfg:	Internal काष्ठाure associated with the host.
 *
 * This routine can block and should only be used on process context.
 * It assumes that the caller is an ioctl thपढ़ो and holding the ioctl
 * पढ़ो semaphore. This is temporarily let up across the रुको to allow
 * क्रम draining actively running ioctls. Also note that when waking up
 * from रुकोing in reset, the state is unknown and must be checked again
 * beक्रमe proceeding.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
पूर्णांक check_state(काष्ठा cxlflash_cfg *cfg)
अणु
	काष्ठा device *dev = &cfg->dev->dev;
	पूर्णांक rc = 0;

retry:
	चयन (cfg->state) अणु
	हाल STATE_RESET:
		dev_dbg(dev, "%s: Reset state, going to wait...\n", __func__);
		up_पढ़ो(&cfg->ioctl_rwsem);
		rc = रुको_event_पूर्णांकerruptible(cfg->reset_रुकोq,
					      cfg->state != STATE_RESET);
		करोwn_पढ़ो(&cfg->ioctl_rwsem);
		अगर (unlikely(rc))
			अवरोध;
		जाओ retry;
	हाल STATE_FAILTERM:
		dev_dbg(dev, "%s: Failed/Terminating\n", __func__);
		rc = -ENODEV;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

/**
 * cxlflash_disk_attach() - attach a LUN to a context
 * @sdev:	SCSI device associated with LUN.
 * @attach:	Attach ioctl data काष्ठाure.
 *
 * Creates a context and attaches LUN to it. A LUN can only be attached
 * one समय to a context (subsequent attaches क्रम the same context/LUN pair
 * are not supported). Additional LUNs can be attached to a context by
 * specअगरying the 'reuse' flag defined in the cxlflash_ioctl.h header.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
अटल पूर्णांक cxlflash_disk_attach(काष्ठा scsi_device *sdev,
				काष्ठा dk_cxlflash_attach *attach)
अणु
	काष्ठा cxlflash_cfg *cfg = shost_priv(sdev->host);
	काष्ठा device *dev = &cfg->dev->dev;
	काष्ठा afu *afu = cfg->afu;
	काष्ठा llun_info *lli = sdev->hostdata;
	काष्ठा glun_info *gli = lli->parent;
	काष्ठा ctx_info *ctxi = शून्य;
	काष्ठा lun_access *lun_access = शून्य;
	पूर्णांक rc = 0;
	u32 perms;
	पूर्णांक ctxid = -1;
	u64 irqs = attach->num_पूर्णांकerrupts;
	u64 flags = 0UL;
	u64 rctxid = 0UL;
	काष्ठा file *file = शून्य;

	व्योम *ctx = शून्य;

	पूर्णांक fd = -1;

	अगर (irqs > 4) अणु
		dev_dbg(dev, "%s: Cannot support this many interrupts %llu\n",
			__func__, irqs);
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (gli->max_lba == 0) अणु
		dev_dbg(dev, "%s: No capacity info for LUN=%016llx\n",
			__func__, lli->lun_id[sdev->channel]);
		rc = पढ़ो_cap16(sdev, lli);
		अगर (rc) अणु
			dev_err(dev, "%s: Invalid device rc=%d\n",
				__func__, rc);
			rc = -ENODEV;
			जाओ out;
		पूर्ण
		dev_dbg(dev, "%s: LBA = %016llx\n", __func__, gli->max_lba);
		dev_dbg(dev, "%s: BLK_LEN = %08x\n", __func__, gli->blk_len);
	पूर्ण

	अगर (attach->hdr.flags & DK_CXLFLASH_ATTACH_REUSE_CONTEXT) अणु
		rctxid = attach->context_id;
		ctxi = get_context(cfg, rctxid, शून्य, 0);
		अगर (!ctxi) अणु
			dev_dbg(dev, "%s: Bad context rctxid=%016llx\n",
				__func__, rctxid);
			rc = -EINVAL;
			जाओ out;
		पूर्ण

		list_क्रम_each_entry(lun_access, &ctxi->luns, list)
			अगर (lun_access->lli == lli) अणु
				dev_dbg(dev, "%s: Already attached\n",
					__func__);
				rc = -EINVAL;
				जाओ out;
			पूर्ण
	पूर्ण

	rc = scsi_device_get(sdev);
	अगर (unlikely(rc)) अणु
		dev_err(dev, "%s: Unable to get sdev reference\n", __func__);
		जाओ out;
	पूर्ण

	lun_access = kzalloc(माप(*lun_access), GFP_KERNEL);
	अगर (unlikely(!lun_access)) अणु
		dev_err(dev, "%s: Unable to allocate lun_access\n", __func__);
		rc = -ENOMEM;
		जाओ err;
	पूर्ण

	lun_access->lli = lli;
	lun_access->sdev = sdev;

	/* Non-शून्य context indicates reuse (another context reference) */
	अगर (ctxi) अणु
		dev_dbg(dev, "%s: Reusing context for LUN rctxid=%016llx\n",
			__func__, rctxid);
		kref_get(&ctxi->kref);
		list_add(&lun_access->list, &ctxi->luns);
		जाओ out_attach;
	पूर्ण

	ctxi = create_context(cfg);
	अगर (unlikely(!ctxi)) अणु
		dev_err(dev, "%s: Failed to create context ctxid=%d\n",
			__func__, ctxid);
		rc = -ENOMEM;
		जाओ err;
	पूर्ण

	ctx = cfg->ops->dev_context_init(cfg->dev, cfg->afu_cookie);
	अगर (IS_ERR_OR_शून्य(ctx)) अणु
		dev_err(dev, "%s: Could not initialize context %p\n",
			__func__, ctx);
		rc = -ENODEV;
		जाओ err;
	पूर्ण

	rc = cfg->ops->start_work(ctx, irqs);
	अगर (unlikely(rc)) अणु
		dev_dbg(dev, "%s: Could not start context rc=%d\n",
			__func__, rc);
		जाओ err;
	पूर्ण

	ctxid = cfg->ops->process_element(ctx);
	अगर (unlikely((ctxid >= MAX_CONTEXT) || (ctxid < 0))) अणु
		dev_err(dev, "%s: ctxid=%d invalid\n", __func__, ctxid);
		rc = -EPERM;
		जाओ err;
	पूर्ण

	file = cfg->ops->get_fd(ctx, &cfg->cxl_fops, &fd);
	अगर (unlikely(fd < 0)) अणु
		rc = -ENODEV;
		dev_err(dev, "%s: Could not get file descriptor\n", __func__);
		जाओ err;
	पूर्ण

	/* Translate पढ़ो/ग_लिखो O_* flags from fcntl.h to AFU permission bits */
	perms = SISL_RHT_PERM(attach->hdr.flags + 1);

	/* Context mutex is locked upon वापस */
	init_context(ctxi, cfg, ctx, ctxid, file, perms, irqs);

	rc = afu_attach(cfg, ctxi);
	अगर (unlikely(rc)) अणु
		dev_err(dev, "%s: Could not attach AFU rc %d\n", __func__, rc);
		जाओ err;
	पूर्ण

	/*
	 * No error paths after this poपूर्णांक. Once the fd is installed it's
	 * visible to user space and can't be unकरोne safely on this thपढ़ो.
	 * There is no need to worry about a deadlock here because no one
	 * knows about us yet; we can be the only one holding our mutex.
	 */
	list_add(&lun_access->list, &ctxi->luns);
	mutex_lock(&cfg->ctx_tbl_list_mutex);
	mutex_lock(&ctxi->mutex);
	cfg->ctx_tbl[ctxid] = ctxi;
	mutex_unlock(&cfg->ctx_tbl_list_mutex);
	fd_install(fd, file);

out_attach:
	अगर (fd != -1)
		flags |= DK_CXLFLASH_APP_CLOSE_ADAP_FD;
	अगर (afu_is_sq_cmd_mode(afu))
		flags |= DK_CXLFLASH_CONTEXT_SQ_CMD_MODE;

	attach->hdr.वापस_flags = flags;
	attach->context_id = ctxi->ctxid;
	attach->block_size = gli->blk_len;
	attach->mmio_size = माप(afu->afu_map->hosts[0].harea);
	attach->last_lba = gli->max_lba;
	attach->max_xfer = sdev->host->max_sectors * MAX_SECTOR_UNIT;
	attach->max_xfer /= gli->blk_len;

out:
	attach->adap_fd = fd;

	अगर (ctxi)
		put_context(ctxi);

	dev_dbg(dev, "%s: returning ctxid=%d fd=%d bs=%lld rc=%d llba=%lld\n",
		__func__, ctxid, fd, attach->block_size, rc, attach->last_lba);
	वापस rc;

err:
	/* Cleanup CXL context; okay to 'stop' even अगर it was not started */
	अगर (!IS_ERR_OR_शून्य(ctx)) अणु
		cfg->ops->stop_context(ctx);
		cfg->ops->release_context(ctx);
		ctx = शून्य;
	पूर्ण

	/*
	 * Here, we're overriding the fops with a dummy all-शून्य fops because
	 * fput() calls the release fop, which will cause us to mistakenly
	 * call पूर्णांकo the CXL code. Rather than try to add yet more complनिकासy
	 * to that routine (cxlflash_cxl_release) we should try to fix the
	 * issue here.
	 */
	अगर (fd > 0) अणु
		file->f_op = &null_fops;
		fput(file);
		put_unused_fd(fd);
		fd = -1;
		file = शून्य;
	पूर्ण

	/* Cleanup our context */
	अगर (ctxi) अणु
		destroy_context(cfg, ctxi);
		ctxi = शून्य;
	पूर्ण

	kमुक्त(lun_access);
	scsi_device_put(sdev);
	जाओ out;
पूर्ण

/**
 * recover_context() - recovers a context in error
 * @cfg:	Internal काष्ठाure associated with the host.
 * @ctxi:	Context to release.
 * @adap_fd:	Adapter file descriptor associated with new/recovered context.
 *
 * Restablishes the state क्रम a context-in-error.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
अटल पूर्णांक recover_context(काष्ठा cxlflash_cfg *cfg,
			   काष्ठा ctx_info *ctxi,
			   पूर्णांक *adap_fd)
अणु
	काष्ठा device *dev = &cfg->dev->dev;
	पूर्णांक rc = 0;
	पूर्णांक fd = -1;
	पूर्णांक ctxid = -1;
	काष्ठा file *file;
	व्योम *ctx;
	काष्ठा afu *afu = cfg->afu;

	ctx = cfg->ops->dev_context_init(cfg->dev, cfg->afu_cookie);
	अगर (IS_ERR_OR_शून्य(ctx)) अणु
		dev_err(dev, "%s: Could not initialize context %p\n",
			__func__, ctx);
		rc = -ENODEV;
		जाओ out;
	पूर्ण

	rc = cfg->ops->start_work(ctx, ctxi->irqs);
	अगर (unlikely(rc)) अणु
		dev_dbg(dev, "%s: Could not start context rc=%d\n",
			__func__, rc);
		जाओ err1;
	पूर्ण

	ctxid = cfg->ops->process_element(ctx);
	अगर (unlikely((ctxid >= MAX_CONTEXT) || (ctxid < 0))) अणु
		dev_err(dev, "%s: ctxid=%d invalid\n", __func__, ctxid);
		rc = -EPERM;
		जाओ err2;
	पूर्ण

	file = cfg->ops->get_fd(ctx, &cfg->cxl_fops, &fd);
	अगर (unlikely(fd < 0)) अणु
		rc = -ENODEV;
		dev_err(dev, "%s: Could not get file descriptor\n", __func__);
		जाओ err2;
	पूर्ण

	/* Update with new MMIO area based on updated context id */
	ctxi->ctrl_map = &afu->afu_map->ctrls[ctxid].ctrl;

	rc = afu_attach(cfg, ctxi);
	अगर (rc) अणु
		dev_err(dev, "%s: Could not attach AFU rc %d\n", __func__, rc);
		जाओ err3;
	पूर्ण

	/*
	 * No error paths after this poपूर्णांक. Once the fd is installed it's
	 * visible to user space and can't be unकरोne safely on this thपढ़ो.
	 */
	ctxi->ctxid = ENCODE_CTXID(ctxi, ctxid);
	ctxi->ctx = ctx;
	ctxi->file = file;

	/*
	 * Put context back in table (note the reinit of the context list);
	 * we must first drop the context's mutex and then acquire it in
	 * order with the table/list mutex to aव्योम a deadlock - safe to करो
	 * here because no one can find us at this moment in समय.
	 */
	mutex_unlock(&ctxi->mutex);
	mutex_lock(&cfg->ctx_tbl_list_mutex);
	mutex_lock(&ctxi->mutex);
	list_del_init(&ctxi->list);
	cfg->ctx_tbl[ctxid] = ctxi;
	mutex_unlock(&cfg->ctx_tbl_list_mutex);
	fd_install(fd, file);
	*adap_fd = fd;
out:
	dev_dbg(dev, "%s: returning ctxid=%d fd=%d rc=%d\n",
		__func__, ctxid, fd, rc);
	वापस rc;

err3:
	fput(file);
	put_unused_fd(fd);
err2:
	cfg->ops->stop_context(ctx);
err1:
	cfg->ops->release_context(ctx);
	जाओ out;
पूर्ण

/**
 * cxlflash_afu_recover() - initiates AFU recovery
 * @sdev:	SCSI device associated with LUN.
 * @recover:	Recover ioctl data काष्ठाure.
 *
 * Only a single recovery is allowed at a समय to aव्योम exhausting CXL
 * resources (leading to recovery failure) in the event that we're up
 * against the maximum number of contexts limit. For similar reasons,
 * a context recovery is retried अगर there are multiple recoveries taking
 * place at the same समय and the failure was due to CXL services being
 * unable to keep up.
 *
 * As this routine is called on ioctl context, it holds the ioctl r/w
 * semaphore that is used to drain ioctls in recovery scenarios. The
 * implementation to achieve the pacing described above (a local mutex)
 * requires that the ioctl r/w semaphore be dropped and reacquired to
 * aव्योम a 3-way deadlock when multiple process recoveries operate in
 * parallel.
 *
 * Because a user can detect an error condition beक्रमe the kernel, it is
 * quite possible क्रम this routine to act as the kernel's EEH detection
 * source (MMIO पढ़ो of mbox_r). Because of this, there is a winकरोw of
 * समय where an EEH might have been detected but not yet 'serviced'
 * (callback invoked, causing the device to enter reset state). To aव्योम
 * looping in this routine during that winकरोw, a 1 second sleep is in place
 * between the समय the MMIO failure is detected and the समय a रुको on the
 * reset रुको queue is attempted via check_state().
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
अटल पूर्णांक cxlflash_afu_recover(काष्ठा scsi_device *sdev,
				काष्ठा dk_cxlflash_recover_afu *recover)
अणु
	काष्ठा cxlflash_cfg *cfg = shost_priv(sdev->host);
	काष्ठा device *dev = &cfg->dev->dev;
	काष्ठा llun_info *lli = sdev->hostdata;
	काष्ठा afu *afu = cfg->afu;
	काष्ठा ctx_info *ctxi = शून्य;
	काष्ठा mutex *mutex = &cfg->ctx_recovery_mutex;
	काष्ठा hwq *hwq = get_hwq(afu, PRIMARY_HWQ);
	u64 flags;
	u64 ctxid = DECODE_CTXID(recover->context_id),
	    rctxid = recover->context_id;
	दीर्घ reg;
	bool locked = true;
	पूर्णांक lretry = 20; /* up to 2 seconds */
	पूर्णांक new_adap_fd = -1;
	पूर्णांक rc = 0;

	atomic_inc(&cfg->recovery_thपढ़ोs);
	up_पढ़ो(&cfg->ioctl_rwsem);
	rc = mutex_lock_पूर्णांकerruptible(mutex);
	करोwn_पढ़ो(&cfg->ioctl_rwsem);
	अगर (rc) अणु
		locked = false;
		जाओ out;
	पूर्ण

	rc = check_state(cfg);
	अगर (rc) अणु
		dev_err(dev, "%s: Failed state rc=%d\n", __func__, rc);
		rc = -ENODEV;
		जाओ out;
	पूर्ण

	dev_dbg(dev, "%s: reason=%016llx rctxid=%016llx\n",
		__func__, recover->reason, rctxid);

retry:
	/* Ensure that this process is attached to the context */
	ctxi = get_context(cfg, rctxid, lli, CTX_CTRL_ERR_FALLBACK);
	अगर (unlikely(!ctxi)) अणु
		dev_dbg(dev, "%s: Bad context ctxid=%llu\n", __func__, ctxid);
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (ctxi->err_recovery_active) अणु
retry_recover:
		rc = recover_context(cfg, ctxi, &new_adap_fd);
		अगर (unlikely(rc)) अणु
			dev_err(dev, "%s: Recovery failed ctxid=%llu rc=%d\n",
				__func__, ctxid, rc);
			अगर ((rc == -ENODEV) &&
			    ((atomic_पढ़ो(&cfg->recovery_thपढ़ोs) > 1) ||
			     (lretry--))) अणु
				dev_dbg(dev, "%s: Going to try again\n",
					__func__);
				mutex_unlock(mutex);
				msleep(100);
				rc = mutex_lock_पूर्णांकerruptible(mutex);
				अगर (rc) अणु
					locked = false;
					जाओ out;
				पूर्ण
				जाओ retry_recover;
			पूर्ण

			जाओ out;
		पूर्ण

		ctxi->err_recovery_active = false;

		flags = DK_CXLFLASH_APP_CLOSE_ADAP_FD |
			DK_CXLFLASH_RECOVER_AFU_CONTEXT_RESET;
		अगर (afu_is_sq_cmd_mode(afu))
			flags |= DK_CXLFLASH_CONTEXT_SQ_CMD_MODE;

		recover->hdr.वापस_flags = flags;
		recover->context_id = ctxi->ctxid;
		recover->adap_fd = new_adap_fd;
		recover->mmio_size = माप(afu->afu_map->hosts[0].harea);
		जाओ out;
	पूर्ण

	/* Test अगर in error state */
	reg = पढ़ोq_be(&hwq->ctrl_map->mbox_r);
	अगर (reg == -1) अणु
		dev_dbg(dev, "%s: MMIO fail, wait for recovery.\n", __func__);

		/*
		 * Beक्रमe checking the state, put back the context obtained with
		 * get_context() as it is no दीर्घer needed and sleep क्रम a लघु
		 * period of समय (see prolog notes).
		 */
		put_context(ctxi);
		ctxi = शून्य;
		ssleep(1);
		rc = check_state(cfg);
		अगर (unlikely(rc))
			जाओ out;
		जाओ retry;
	पूर्ण

	dev_dbg(dev, "%s: MMIO working, no recovery required\n", __func__);
out:
	अगर (likely(ctxi))
		put_context(ctxi);
	अगर (locked)
		mutex_unlock(mutex);
	atomic_dec_अगर_positive(&cfg->recovery_thपढ़ोs);
	वापस rc;
पूर्ण

/**
 * process_sense() - evaluates and processes sense data
 * @sdev:	SCSI device associated with LUN.
 * @verअगरy:	Verअगरy ioctl data काष्ठाure.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
अटल पूर्णांक process_sense(काष्ठा scsi_device *sdev,
			 काष्ठा dk_cxlflash_verअगरy *verअगरy)
अणु
	काष्ठा cxlflash_cfg *cfg = shost_priv(sdev->host);
	काष्ठा device *dev = &cfg->dev->dev;
	काष्ठा llun_info *lli = sdev->hostdata;
	काष्ठा glun_info *gli = lli->parent;
	u64 prev_lba = gli->max_lba;
	काष्ठा scsi_sense_hdr sshdr = अणु 0 पूर्ण;
	पूर्णांक rc = 0;

	rc = scsi_normalize_sense((स्थिर u8 *)&verअगरy->sense_data,
				  DK_CXLFLASH_VERIFY_SENSE_LEN, &sshdr);
	अगर (!rc) अणु
		dev_err(dev, "%s: Failed to normalize sense data\n", __func__);
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	चयन (sshdr.sense_key) अणु
	हाल NO_SENSE:
	हाल RECOVERED_ERROR:
	हाल NOT_READY:
		अवरोध;
	हाल UNIT_ATTENTION:
		चयन (sshdr.asc) अणु
		हाल 0x29: /* Power on Reset or Device Reset */
			fallthrough;
		हाल 0x2A: /* Device settings/capacity changed */
			rc = पढ़ो_cap16(sdev, lli);
			अगर (rc) अणु
				rc = -ENODEV;
				अवरोध;
			पूर्ण
			अगर (prev_lba != gli->max_lba)
				dev_dbg(dev, "%s: Capacity changed old=%lld "
					"new=%lld\n", __func__, prev_lba,
					gli->max_lba);
			अवरोध;
		हाल 0x3F: /* Report LUNs changed, Rescan. */
			scsi_scan_host(cfg->host);
			अवरोध;
		शेष:
			rc = -EIO;
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		rc = -EIO;
		अवरोध;
	पूर्ण
out:
	dev_dbg(dev, "%s: sense_key %x asc %x ascq %x rc %d\n", __func__,
		sshdr.sense_key, sshdr.asc, sshdr.ascq, rc);
	वापस rc;
पूर्ण

/**
 * cxlflash_disk_verअगरy() - verअगरies a LUN is the same and handle size changes
 * @sdev:	SCSI device associated with LUN.
 * @verअगरy:	Verअगरy ioctl data काष्ठाure.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
अटल पूर्णांक cxlflash_disk_verअगरy(काष्ठा scsi_device *sdev,
				काष्ठा dk_cxlflash_verअगरy *verअगरy)
अणु
	पूर्णांक rc = 0;
	काष्ठा ctx_info *ctxi = शून्य;
	काष्ठा cxlflash_cfg *cfg = shost_priv(sdev->host);
	काष्ठा device *dev = &cfg->dev->dev;
	काष्ठा llun_info *lli = sdev->hostdata;
	काष्ठा glun_info *gli = lli->parent;
	काष्ठा sisl_rht_entry *rhte = शून्य;
	res_hndl_t rhndl = verअगरy->rsrc_handle;
	u64 ctxid = DECODE_CTXID(verअगरy->context_id),
	    rctxid = verअगरy->context_id;
	u64 last_lba = 0;

	dev_dbg(dev, "%s: ctxid=%llu rhndl=%016llx, hint=%016llx, "
		"flags=%016llx\n", __func__, ctxid, verअगरy->rsrc_handle,
		verअगरy->hपूर्णांक, verअगरy->hdr.flags);

	ctxi = get_context(cfg, rctxid, lli, 0);
	अगर (unlikely(!ctxi)) अणु
		dev_dbg(dev, "%s: Bad context ctxid=%llu\n", __func__, ctxid);
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	rhte = get_rhte(ctxi, rhndl, lli);
	अगर (unlikely(!rhte)) अणु
		dev_dbg(dev, "%s: Bad resource handle rhndl=%d\n",
			__func__, rhndl);
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	/*
	 * Look at the hपूर्णांक/sense to see अगर it requires us to redrive
	 * inquiry (i.e. the Unit attention is due to the WWN changing).
	 */
	अगर (verअगरy->hपूर्णांक & DK_CXLFLASH_VERIFY_HINT_SENSE) अणु
		/* Can't hold mutex across process_sense/पढ़ो_cap16,
		 * since we could have an पूर्णांकervening EEH event.
		 */
		ctxi->unavail = true;
		mutex_unlock(&ctxi->mutex);
		rc = process_sense(sdev, verअगरy);
		अगर (unlikely(rc)) अणु
			dev_err(dev, "%s: Failed to validate sense data (%d)\n",
				__func__, rc);
			mutex_lock(&ctxi->mutex);
			ctxi->unavail = false;
			जाओ out;
		पूर्ण
		mutex_lock(&ctxi->mutex);
		ctxi->unavail = false;
	पूर्ण

	चयन (gli->mode) अणु
	हाल MODE_PHYSICAL:
		last_lba = gli->max_lba;
		अवरोध;
	हाल MODE_VIRTUAL:
		/* Cast lxt_cnt to u64 क्रम multiply to be treated as 64bit op */
		last_lba = ((u64)rhte->lxt_cnt * MC_CHUNK_SIZE * gli->blk_len);
		last_lba /= CXLFLASH_BLOCK_SIZE;
		last_lba--;
		अवरोध;
	शेष:
		WARN(1, "Unsupported LUN mode!");
	पूर्ण

	verअगरy->last_lba = last_lba;

out:
	अगर (likely(ctxi))
		put_context(ctxi);
	dev_dbg(dev, "%s: returning rc=%d llba=%llx\n",
		__func__, rc, verअगरy->last_lba);
	वापस rc;
पूर्ण

/**
 * decode_ioctl() - translates an encoded ioctl to an easily identअगरiable string
 * @cmd:	The ioctl command to decode.
 *
 * Return: A string identअगरying the decoded ioctl.
 */
अटल अक्षर *decode_ioctl(अचिन्हित पूर्णांक cmd)
अणु
	चयन (cmd) अणु
	हाल DK_CXLFLASH_ATTACH:
		वापस __stringअगरy_1(DK_CXLFLASH_ATTACH);
	हाल DK_CXLFLASH_USER_सूचीECT:
		वापस __stringअगरy_1(DK_CXLFLASH_USER_सूचीECT);
	हाल DK_CXLFLASH_USER_VIRTUAL:
		वापस __stringअगरy_1(DK_CXLFLASH_USER_VIRTUAL);
	हाल DK_CXLFLASH_VLUN_RESIZE:
		वापस __stringअगरy_1(DK_CXLFLASH_VLUN_RESIZE);
	हाल DK_CXLFLASH_RELEASE:
		वापस __stringअगरy_1(DK_CXLFLASH_RELEASE);
	हाल DK_CXLFLASH_DETACH:
		वापस __stringअगरy_1(DK_CXLFLASH_DETACH);
	हाल DK_CXLFLASH_VERIFY:
		वापस __stringअगरy_1(DK_CXLFLASH_VERIFY);
	हाल DK_CXLFLASH_VLUN_CLONE:
		वापस __stringअगरy_1(DK_CXLFLASH_VLUN_CLONE);
	हाल DK_CXLFLASH_RECOVER_AFU:
		वापस __stringअगरy_1(DK_CXLFLASH_RECOVER_AFU);
	हाल DK_CXLFLASH_MANAGE_LUN:
		वापस __stringअगरy_1(DK_CXLFLASH_MANAGE_LUN);
	पूर्ण

	वापस "UNKNOWN";
पूर्ण

/**
 * cxlflash_disk_direct_खोलो() - खोलोs a direct (physical) disk
 * @sdev:	SCSI device associated with LUN.
 * @arg:	UDirect ioctl data काष्ठाure.
 *
 * On successful वापस, the user is inक्रमmed of the resource handle
 * to be used to identअगरy the direct lun and the size (in blocks) of
 * the direct lun in last LBA क्रमmat.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
अटल पूर्णांक cxlflash_disk_direct_खोलो(काष्ठा scsi_device *sdev, व्योम *arg)
अणु
	काष्ठा cxlflash_cfg *cfg = shost_priv(sdev->host);
	काष्ठा device *dev = &cfg->dev->dev;
	काष्ठा afu *afu = cfg->afu;
	काष्ठा llun_info *lli = sdev->hostdata;
	काष्ठा glun_info *gli = lli->parent;
	काष्ठा dk_cxlflash_release rel = अणु अणु 0 पूर्ण, 0 पूर्ण;

	काष्ठा dk_cxlflash_udirect *pphys = (काष्ठा dk_cxlflash_udirect *)arg;

	u64 ctxid = DECODE_CTXID(pphys->context_id),
	    rctxid = pphys->context_id;
	u64 lun_size = 0;
	u64 last_lba = 0;
	u64 rsrc_handle = -1;
	u32 port = CHAN2PORTMASK(sdev->channel);

	पूर्णांक rc = 0;

	काष्ठा ctx_info *ctxi = शून्य;
	काष्ठा sisl_rht_entry *rhte = शून्य;

	dev_dbg(dev, "%s: ctxid=%llu ls=%llu\n", __func__, ctxid, lun_size);

	rc = cxlflash_lun_attach(gli, MODE_PHYSICAL, false);
	अगर (unlikely(rc)) अणु
		dev_dbg(dev, "%s: Failed attach to LUN (PHYSICAL)\n", __func__);
		जाओ out;
	पूर्ण

	ctxi = get_context(cfg, rctxid, lli, 0);
	अगर (unlikely(!ctxi)) अणु
		dev_dbg(dev, "%s: Bad context ctxid=%llu\n", __func__, ctxid);
		rc = -EINVAL;
		जाओ err1;
	पूर्ण

	rhte = rhte_checkout(ctxi, lli);
	अगर (unlikely(!rhte)) अणु
		dev_dbg(dev, "%s: Too many opens ctxid=%lld\n",
			__func__, ctxid);
		rc = -EMखाता;	/* too many खोलोs  */
		जाओ err1;
	पूर्ण

	rsrc_handle = (rhte - ctxi->rht_start);

	rht_क्रमmat1(rhte, lli->lun_id[sdev->channel], ctxi->rht_perms, port);

	last_lba = gli->max_lba;
	pphys->hdr.वापस_flags = 0;
	pphys->last_lba = last_lba;
	pphys->rsrc_handle = rsrc_handle;

	rc = cxlflash_afu_sync(afu, ctxid, rsrc_handle, AFU_LW_SYNC);
	अगर (unlikely(rc)) अणु
		dev_dbg(dev, "%s: AFU sync failed rc=%d\n", __func__, rc);
		जाओ err2;
	पूर्ण

out:
	अगर (likely(ctxi))
		put_context(ctxi);
	dev_dbg(dev, "%s: returning handle=%llu rc=%d llba=%llu\n",
		__func__, rsrc_handle, rc, last_lba);
	वापस rc;

err2:
	marshal_udir_to_rele(pphys, &rel);
	_cxlflash_disk_release(sdev, ctxi, &rel);
	जाओ out;
err1:
	cxlflash_lun_detach(gli);
	जाओ out;
पूर्ण

/**
 * ioctl_common() - common IOCTL handler क्रम driver
 * @sdev:	SCSI device associated with LUN.
 * @cmd:	IOCTL command.
 *
 * Handles common fencing operations that are valid क्रम multiple ioctls. Always
 * allow through ioctls that are cleanup oriented in nature, even when operating
 * in a failed/terminating state.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
अटल पूर्णांक ioctl_common(काष्ठा scsi_device *sdev, अचिन्हित पूर्णांक cmd)
अणु
	काष्ठा cxlflash_cfg *cfg = shost_priv(sdev->host);
	काष्ठा device *dev = &cfg->dev->dev;
	काष्ठा llun_info *lli = sdev->hostdata;
	पूर्णांक rc = 0;

	अगर (unlikely(!lli)) अणु
		dev_dbg(dev, "%s: Unknown LUN\n", __func__);
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	rc = check_state(cfg);
	अगर (unlikely(rc) && (cfg->state == STATE_FAILTERM)) अणु
		चयन (cmd) अणु
		हाल DK_CXLFLASH_VLUN_RESIZE:
		हाल DK_CXLFLASH_RELEASE:
		हाल DK_CXLFLASH_DETACH:
			dev_dbg(dev, "%s: Command override rc=%d\n",
				__func__, rc);
			rc = 0;
			अवरोध;
		पूर्ण
	पूर्ण
out:
	वापस rc;
पूर्ण

/**
 * cxlflash_ioctl() - IOCTL handler क्रम driver
 * @sdev:	SCSI device associated with LUN.
 * @cmd:	IOCTL command.
 * @arg:	Userspace ioctl data काष्ठाure.
 *
 * A पढ़ो/ग_लिखो semaphore is used to implement a 'drain' of currently
 * running ioctls. The पढ़ो semaphore is taken at the beginning of each
 * ioctl thपढ़ो and released upon concluding execution. Additionally the
 * semaphore should be released and then reacquired in any ioctl execution
 * path which will रुको क्रम an event to occur that is outside the scope of
 * the ioctl (i.e. an adapter reset). To drain the ioctls currently running,
 * a thपढ़ो simply needs to acquire the ग_लिखो semaphore.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
पूर्णांक cxlflash_ioctl(काष्ठा scsi_device *sdev, अचिन्हित पूर्णांक cmd, व्योम __user *arg)
अणु
	प्रकार पूर्णांक (*sioctl) (काष्ठा scsi_device *, व्योम *);

	काष्ठा cxlflash_cfg *cfg = shost_priv(sdev->host);
	काष्ठा device *dev = &cfg->dev->dev;
	काष्ठा afu *afu = cfg->afu;
	काष्ठा dk_cxlflash_hdr *hdr;
	अक्षर buf[माप(जोड़ cxlflash_ioctls)];
	माप_प्रकार size = 0;
	bool known_ioctl = false;
	पूर्णांक idx;
	पूर्णांक rc = 0;
	काष्ठा Scsi_Host *shost = sdev->host;
	sioctl करो_ioctl = शून्य;

	अटल स्थिर काष्ठा अणु
		माप_प्रकार size;
		sioctl ioctl;
	पूर्ण ioctl_tbl[] = अणु	/* NOTE: order matters here */
	अणुमाप(काष्ठा dk_cxlflash_attach), (sioctl)cxlflash_disk_attachपूर्ण,
	अणुमाप(काष्ठा dk_cxlflash_udirect), cxlflash_disk_direct_खोलोपूर्ण,
	अणुमाप(काष्ठा dk_cxlflash_release), (sioctl)cxlflash_disk_releaseपूर्ण,
	अणुमाप(काष्ठा dk_cxlflash_detach), (sioctl)cxlflash_disk_detachपूर्ण,
	अणुमाप(काष्ठा dk_cxlflash_verअगरy), (sioctl)cxlflash_disk_verअगरyपूर्ण,
	अणुमाप(काष्ठा dk_cxlflash_recover_afu), (sioctl)cxlflash_afu_recoverपूर्ण,
	अणुमाप(काष्ठा dk_cxlflash_manage_lun), (sioctl)cxlflash_manage_lunपूर्ण,
	अणुमाप(काष्ठा dk_cxlflash_uभव), cxlflash_disk_भव_खोलोपूर्ण,
	अणुमाप(काष्ठा dk_cxlflash_resize), (sioctl)cxlflash_vlun_resizeपूर्ण,
	अणुमाप(काष्ठा dk_cxlflash_clone), (sioctl)cxlflash_disk_cloneपूर्ण,
	पूर्ण;

	/* Hold पढ़ो semaphore so we can drain अगर needed */
	करोwn_पढ़ो(&cfg->ioctl_rwsem);

	/* Restrict command set to physical support only क्रम पूर्णांकernal LUN */
	अगर (afu->पूर्णांकernal_lun)
		चयन (cmd) अणु
		हाल DK_CXLFLASH_RELEASE:
		हाल DK_CXLFLASH_USER_VIRTUAL:
		हाल DK_CXLFLASH_VLUN_RESIZE:
		हाल DK_CXLFLASH_VLUN_CLONE:
			dev_dbg(dev, "%s: %s not supported for lun_mode=%d\n",
				__func__, decode_ioctl(cmd), afu->पूर्णांकernal_lun);
			rc = -EINVAL;
			जाओ cxlflash_ioctl_निकास;
		पूर्ण

	चयन (cmd) अणु
	हाल DK_CXLFLASH_ATTACH:
	हाल DK_CXLFLASH_USER_सूचीECT:
	हाल DK_CXLFLASH_RELEASE:
	हाल DK_CXLFLASH_DETACH:
	हाल DK_CXLFLASH_VERIFY:
	हाल DK_CXLFLASH_RECOVER_AFU:
	हाल DK_CXLFLASH_USER_VIRTUAL:
	हाल DK_CXLFLASH_VLUN_RESIZE:
	हाल DK_CXLFLASH_VLUN_CLONE:
		dev_dbg(dev, "%s: %s (%08X) on dev(%d/%d/%d/%llu)\n",
			__func__, decode_ioctl(cmd), cmd, shost->host_no,
			sdev->channel, sdev->id, sdev->lun);
		rc = ioctl_common(sdev, cmd);
		अगर (unlikely(rc))
			जाओ cxlflash_ioctl_निकास;

		fallthrough;

	हाल DK_CXLFLASH_MANAGE_LUN:
		known_ioctl = true;
		idx = _IOC_NR(cmd) - _IOC_NR(DK_CXLFLASH_ATTACH);
		size = ioctl_tbl[idx].size;
		करो_ioctl = ioctl_tbl[idx].ioctl;

		अगर (likely(करो_ioctl))
			अवरोध;

		fallthrough;
	शेष:
		rc = -EINVAL;
		जाओ cxlflash_ioctl_निकास;
	पूर्ण

	अगर (unlikely(copy_from_user(&buf, arg, size))) अणु
		dev_err(dev, "%s: copy_from_user() fail size=%lu cmd=%u (%s) arg=%p\n",
			__func__, size, cmd, decode_ioctl(cmd), arg);
		rc = -EFAULT;
		जाओ cxlflash_ioctl_निकास;
	पूर्ण

	hdr = (काष्ठा dk_cxlflash_hdr *)&buf;
	अगर (hdr->version != DK_CXLFLASH_VERSION_0) अणु
		dev_dbg(dev, "%s: Version %u not supported for %s\n",
			__func__, hdr->version, decode_ioctl(cmd));
		rc = -EINVAL;
		जाओ cxlflash_ioctl_निकास;
	पूर्ण

	अगर (hdr->rsvd[0] || hdr->rsvd[1] || hdr->rsvd[2] || hdr->वापस_flags) अणु
		dev_dbg(dev, "%s: Reserved/rflags populated\n", __func__);
		rc = -EINVAL;
		जाओ cxlflash_ioctl_निकास;
	पूर्ण

	rc = करो_ioctl(sdev, (व्योम *)&buf);
	अगर (likely(!rc))
		अगर (unlikely(copy_to_user(arg, &buf, size))) अणु
			dev_err(dev, "%s: copy_to_user() fail size=%lu cmd=%u (%s) arg=%p\n",
				__func__, size, cmd, decode_ioctl(cmd), arg);
			rc = -EFAULT;
		पूर्ण

	/* fall through to निकास */

cxlflash_ioctl_निकास:
	up_पढ़ो(&cfg->ioctl_rwsem);
	अगर (unlikely(rc && known_ioctl))
		dev_err(dev, "%s: ioctl %s (%08X) on dev(%d/%d/%d/%llu) "
			"returned rc %d\n", __func__,
			decode_ioctl(cmd), cmd, shost->host_no,
			sdev->channel, sdev->id, sdev->lun, rc);
	अन्यथा
		dev_dbg(dev, "%s: ioctl %s (%08X) on dev(%d/%d/%d/%llu) "
			"returned rc %d\n", __func__, decode_ioctl(cmd),
			cmd, shost->host_no, sdev->channel, sdev->id,
			sdev->lun, rc);
	वापस rc;
पूर्ण
