<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  sst.c - Intel SST Driver क्रम audio engine
 *
 *  Copyright (C) 2008-14	Intel Corp
 *  Authors:	Vinod Koul <vinod.koul@पूर्णांकel.com>
 *		Harsha Priya <priya.harsha@पूर्णांकel.com>
 *		Dharageswari R <dharageswari.r@पूर्णांकel.com>
 *		KP Jeeja <jeeja.kp@पूर्णांकel.com>
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
#समावेश <linux/module.h>
#समावेश <linux/fs.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/firmware.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/pm_qos.h>
#समावेश <linux/async.h>
#समावेश <linux/acpi.h>
#समावेश <linux/sysfs.h>
#समावेश <sound/core.h>
#समावेश <sound/soc.h>
#समावेश <यंत्र/platक्रमm_sst_audपन.स>
#समावेश "../sst-mfld-platform.h"
#समावेश "sst.h"

MODULE_AUTHOR("Vinod Koul <vinod.koul@intel.com>");
MODULE_AUTHOR("Harsha Priya <priya.harsha@intel.com>");
MODULE_DESCRIPTION("Intel (R) SST(R) Audio Engine Driver");
MODULE_LICENSE("GPL v2");

अटल अंतरभूत bool sst_is_process_reply(u32 msg_id)
अणु
	वापस ((msg_id & PROCESS_MSG) ? true : false);
पूर्ण

अटल अंतरभूत bool sst_validate_mailbox_size(अचिन्हित पूर्णांक size)
अणु
	वापस ((size <= SST_MAILBOX_SIZE) ? true : false);
पूर्ण

अटल irqवापस_t पूर्णांकel_sst_पूर्णांकerrupt_mrfld(पूर्णांक irq, व्योम *context)
अणु
	जोड़ पूर्णांकerrupt_reg_mrfld isr;
	जोड़ ipc_header_mrfld header;
	जोड़ sst_imr_reg_mrfld imr;
	काष्ठा ipc_post *msg = शून्य;
	अचिन्हित पूर्णांक size;
	काष्ठा पूर्णांकel_sst_drv *drv = (काष्ठा पूर्णांकel_sst_drv *) context;
	irqवापस_t retval = IRQ_HANDLED;

	/* Interrupt arrived, check src */
	isr.full = sst_shim_पढ़ो64(drv->shim, SST_ISRX);

	अगर (isr.part.करोne_पूर्णांकerrupt) अणु
		/* Clear करोne bit */
		spin_lock(&drv->ipc_spin_lock);
		header.full = sst_shim_पढ़ो64(drv->shim,
					drv->ipc_reg.ipcx);
		header.p.header_high.part.करोne = 0;
		sst_shim_ग_लिखो64(drv->shim, drv->ipc_reg.ipcx, header.full);

		/* ग_लिखो 1 to clear status रेजिस्टर */;
		isr.part.करोne_पूर्णांकerrupt = 1;
		sst_shim_ग_लिखो64(drv->shim, SST_ISRX, isr.full);
		spin_unlock(&drv->ipc_spin_lock);

		/* we can send more messages to DSP so trigger work */
		queue_work(drv->post_msg_wq, &drv->ipc_post_msg_wq);
		retval = IRQ_HANDLED;
	पूर्ण

	अगर (isr.part.busy_पूर्णांकerrupt) अणु
		/* message from dsp so copy that */
		spin_lock(&drv->ipc_spin_lock);
		imr.full = sst_shim_पढ़ो64(drv->shim, SST_IMRX);
		imr.part.busy_पूर्णांकerrupt = 1;
		sst_shim_ग_लिखो64(drv->shim, SST_IMRX, imr.full);
		spin_unlock(&drv->ipc_spin_lock);
		header.full =  sst_shim_पढ़ो64(drv->shim, drv->ipc_reg.ipcd);

		अगर (sst_create_ipc_msg(&msg, header.p.header_high.part.large)) अणु
			drv->ops->clear_पूर्णांकerrupt(drv);
			वापस IRQ_HANDLED;
		पूर्ण

		अगर (header.p.header_high.part.large) अणु
			size = header.p.header_low_payload;
			अगर (sst_validate_mailbox_size(size)) अणु
				स_नकल_fromio(msg->mailbox_data,
					drv->mailbox + drv->mailbox_recv_offset, size);
			पूर्ण अन्यथा अणु
				dev_err(drv->dev,
					"Mailbox not copied, payload size is: %u\n", size);
				header.p.header_low_payload = 0;
			पूर्ण
		पूर्ण

		msg->mrfld_header = header;
		msg->is_process_reply =
			sst_is_process_reply(header.p.header_high.part.msg_id);
		spin_lock(&drv->rx_msg_lock);
		list_add_tail(&msg->node, &drv->rx_list);
		spin_unlock(&drv->rx_msg_lock);
		drv->ops->clear_पूर्णांकerrupt(drv);
		retval = IRQ_WAKE_THREAD;
	पूर्ण
	वापस retval;
पूर्ण

अटल irqवापस_t पूर्णांकel_sst_irq_thपढ़ो_mrfld(पूर्णांक irq, व्योम *context)
अणु
	काष्ठा पूर्णांकel_sst_drv *drv = (काष्ठा पूर्णांकel_sst_drv *) context;
	काष्ठा ipc_post *__msg, *msg = शून्य;
	अचिन्हित दीर्घ irq_flags;

	spin_lock_irqsave(&drv->rx_msg_lock, irq_flags);
	अगर (list_empty(&drv->rx_list)) अणु
		spin_unlock_irqrestore(&drv->rx_msg_lock, irq_flags);
		वापस IRQ_HANDLED;
	पूर्ण

	list_क्रम_each_entry_safe(msg, __msg, &drv->rx_list, node) अणु
		list_del(&msg->node);
		spin_unlock_irqrestore(&drv->rx_msg_lock, irq_flags);
		अगर (msg->is_process_reply)
			drv->ops->process_message(msg);
		अन्यथा
			drv->ops->process_reply(drv, msg);

		अगर (msg->is_large)
			kमुक्त(msg->mailbox_data);
		kमुक्त(msg);
		spin_lock_irqsave(&drv->rx_msg_lock, irq_flags);
	पूर्ण
	spin_unlock_irqrestore(&drv->rx_msg_lock, irq_flags);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक sst_save_dsp_context_v2(काष्ठा पूर्णांकel_sst_drv *sst)
अणु
	पूर्णांक ret = 0;

	ret = sst_prepare_and_post_msg(sst, SST_TASK_ID_MEDIA, IPC_CMD,
			IPC_PREP_D3, PIPE_RSVD, 0, शून्य, शून्य,
			true, true, false, true);

	अगर (ret < 0) अणु
		dev_err(sst->dev, "not suspending FW!!, Err: %d\n", ret);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण


अटल काष्ठा पूर्णांकel_sst_ops mrfld_ops = अणु
	.पूर्णांकerrupt = पूर्णांकel_sst_पूर्णांकerrupt_mrfld,
	.irq_thपढ़ो = पूर्णांकel_sst_irq_thपढ़ो_mrfld,
	.clear_पूर्णांकerrupt = पूर्णांकel_sst_clear_पूर्णांकr_mrfld,
	.start = sst_start_mrfld,
	.reset = पूर्णांकel_sst_reset_dsp_mrfld,
	.post_message = sst_post_message_mrfld,
	.process_reply = sst_process_reply_mrfld,
	.save_dsp_context =  sst_save_dsp_context_v2,
	.alloc_stream = sst_alloc_stream_mrfld,
	.post_करोwnload = sst_post_करोwnload_mrfld,
पूर्ण;

पूर्णांक sst_driver_ops(काष्ठा पूर्णांकel_sst_drv *sst)
अणु

	चयन (sst->dev_id) अणु
	हाल SST_MRFLD_PCI_ID:
	हाल SST_BYT_ACPI_ID:
	हाल SST_CHV_ACPI_ID:
		sst->tstamp = SST_TIME_STAMP_MRFLD;
		sst->ops = &mrfld_ops;
		वापस 0;

	शेष:
		dev_err(sst->dev,
			"SST Driver capabilities missing for dev_id: %x",
			sst->dev_id);
		वापस -EINVAL;
	पूर्ण
पूर्ण

व्योम sst_process_pending_msg(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा पूर्णांकel_sst_drv *ctx = container_of(work,
			काष्ठा पूर्णांकel_sst_drv, ipc_post_msg_wq);

	ctx->ops->post_message(ctx, शून्य, false);
पूर्ण

अटल पूर्णांक sst_workqueue_init(काष्ठा पूर्णांकel_sst_drv *ctx)
अणु
	INIT_LIST_HEAD(&ctx->स_नकल_list);
	INIT_LIST_HEAD(&ctx->rx_list);
	INIT_LIST_HEAD(&ctx->ipc_dispatch_list);
	INIT_LIST_HEAD(&ctx->block_list);
	INIT_WORK(&ctx->ipc_post_msg_wq, sst_process_pending_msg);
	init_रुकोqueue_head(&ctx->रुको_queue);

	ctx->post_msg_wq =
		create_singlethपढ़ो_workqueue("sst_post_msg_wq");
	अगर (!ctx->post_msg_wq)
		वापस -EBUSY;
	वापस 0;
पूर्ण

अटल व्योम sst_init_locks(काष्ठा पूर्णांकel_sst_drv *ctx)
अणु
	mutex_init(&ctx->sst_lock);
	spin_lock_init(&ctx->rx_msg_lock);
	spin_lock_init(&ctx->ipc_spin_lock);
	spin_lock_init(&ctx->block_lock);
पूर्ण

पूर्णांक sst_alloc_drv_context(काष्ठा पूर्णांकel_sst_drv **ctx,
		काष्ठा device *dev, अचिन्हित पूर्णांक dev_id)
अणु
	*ctx = devm_kzalloc(dev, माप(काष्ठा पूर्णांकel_sst_drv), GFP_KERNEL);
	अगर (!(*ctx))
		वापस -ENOMEM;

	(*ctx)->dev = dev;
	(*ctx)->dev_id = dev_id;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(sst_alloc_drv_context);

अटल sमाप_प्रकार firmware_version_show(काष्ठा device *dev,
			    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा पूर्णांकel_sst_drv *ctx = dev_get_drvdata(dev);

	अगर (ctx->fw_version.type == 0 && ctx->fw_version.major == 0 &&
	    ctx->fw_version.minor == 0 && ctx->fw_version.build == 0)
		वापस प्र_लिखो(buf, "FW not yet loaded\n");
	अन्यथा
		वापस प्र_लिखो(buf, "v%02x.%02x.%02x.%02x\n",
			       ctx->fw_version.type, ctx->fw_version.major,
			       ctx->fw_version.minor, ctx->fw_version.build);

पूर्ण

अटल DEVICE_ATTR_RO(firmware_version);

अटल स्थिर काष्ठा attribute *sst_fw_version_attrs[] = अणु
	&dev_attr_firmware_version.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group sst_fw_version_attr_group = अणु
	.attrs = (काष्ठा attribute **)sst_fw_version_attrs,
पूर्ण;

पूर्णांक sst_context_init(काष्ठा पूर्णांकel_sst_drv *ctx)
अणु
	पूर्णांक ret = 0, i;

	अगर (!ctx->pdata)
		वापस -EINVAL;

	अगर (!ctx->pdata->probe_data)
		वापस -EINVAL;

	स_नकल(&ctx->info, ctx->pdata->probe_data, माप(ctx->info));

	ret = sst_driver_ops(ctx);
	अगर (ret != 0)
		वापस -EINVAL;

	sst_init_locks(ctx);
	sst_set_fw_state_locked(ctx, SST_RESET);

	/* pvt_id 0 reserved क्रम async messages */
	ctx->pvt_id = 1;
	ctx->stream_cnt = 0;
	ctx->fw_in_mem = शून्य;
	/* we use स_नकल, so set to 0 */
	ctx->use_dma = 0;
	ctx->use_lli = 0;

	अगर (sst_workqueue_init(ctx))
		वापस -EINVAL;

	ctx->mailbox_recv_offset = ctx->pdata->ipc_info->mbox_recv_off;
	ctx->ipc_reg.ipcx = SST_IPCX + ctx->pdata->ipc_info->ipc_offset;
	ctx->ipc_reg.ipcd = SST_IPCD + ctx->pdata->ipc_info->ipc_offset;

	dev_info(ctx->dev, "Got drv data max stream %d\n",
				ctx->info.max_streams);

	क्रम (i = 1; i <= ctx->info.max_streams; i++) अणु
		काष्ठा stream_info *stream = &ctx->streams[i];

		स_रखो(stream, 0, माप(*stream));
		stream->pipe_id = PIPE_RSVD;
		mutex_init(&stream->lock);
	पूर्ण

	/* Register the ISR */
	ret = devm_request_thपढ़ोed_irq(ctx->dev, ctx->irq_num, ctx->ops->पूर्णांकerrupt,
					ctx->ops->irq_thपढ़ो, 0, SST_DRV_NAME,
					ctx);
	अगर (ret)
		जाओ करो_मुक्त_mem;

	dev_dbg(ctx->dev, "Registered IRQ %#x\n", ctx->irq_num);

	/* शेष पूर्णांकr are unmasked so set this as masked */
	sst_shim_ग_लिखो64(ctx->shim, SST_IMRX, 0xFFFF0038);

	ctx->qos = devm_kzalloc(ctx->dev,
		माप(काष्ठा pm_qos_request), GFP_KERNEL);
	अगर (!ctx->qos) अणु
		ret = -ENOMEM;
		जाओ करो_मुक्त_mem;
	पूर्ण
	cpu_latency_qos_add_request(ctx->qos, PM_QOS_DEFAULT_VALUE);

	dev_dbg(ctx->dev, "Requesting FW %s now...\n", ctx->firmware_name);
	ret = request_firmware_noरुको(THIS_MODULE, true, ctx->firmware_name,
				      ctx->dev, GFP_KERNEL, ctx, sst_firmware_load_cb);
	अगर (ret) अणु
		dev_err(ctx->dev, "Firmware download failed:%d\n", ret);
		जाओ करो_मुक्त_mem;
	पूर्ण

	ret = sysfs_create_group(&ctx->dev->kobj,
				 &sst_fw_version_attr_group);
	अगर (ret) अणु
		dev_err(ctx->dev,
			"Unable to create sysfs\n");
		जाओ err_sysfs;
	पूर्ण

	sst_रेजिस्टर(ctx->dev);
	वापस 0;
err_sysfs:
	sysfs_हटाओ_group(&ctx->dev->kobj, &sst_fw_version_attr_group);

करो_मुक्त_mem:
	destroy_workqueue(ctx->post_msg_wq);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(sst_context_init);

व्योम sst_context_cleanup(काष्ठा पूर्णांकel_sst_drv *ctx)
अणु
	pm_runसमय_get_noresume(ctx->dev);
	pm_runसमय_disable(ctx->dev);
	sst_unरेजिस्टर(ctx->dev);
	sst_set_fw_state_locked(ctx, SST_SHUTDOWN);
	sysfs_हटाओ_group(&ctx->dev->kobj, &sst_fw_version_attr_group);
	flush_scheduled_work();
	destroy_workqueue(ctx->post_msg_wq);
	cpu_latency_qos_हटाओ_request(ctx->qos);
	kमुक्त(ctx->fw_sg_list.src);
	kमुक्त(ctx->fw_sg_list.dst);
	ctx->fw_sg_list.list_len = 0;
	kमुक्त(ctx->fw_in_mem);
	ctx->fw_in_mem = शून्य;
	sst_स_नकल_मुक्त_resources(ctx);
पूर्ण
EXPORT_SYMBOL_GPL(sst_context_cleanup);

व्योम sst_configure_runसमय_pm(काष्ठा पूर्णांकel_sst_drv *ctx)
अणु
	pm_runसमय_set_स्वतःsuspend_delay(ctx->dev, SST_SUSPEND_DELAY);
	pm_runसमय_use_स्वतःsuspend(ctx->dev);
	/*
	 * For acpi devices, the actual physical device state is
	 * initially active. So change the state to active beक्रमe
	 * enabling the pm
	 */

	अगर (!acpi_disabled)
		pm_runसमय_set_active(ctx->dev);

	pm_runसमय_enable(ctx->dev);

	अगर (acpi_disabled)
		pm_runसमय_set_active(ctx->dev);
	अन्यथा
		pm_runसमय_put_noidle(ctx->dev);
पूर्ण
EXPORT_SYMBOL_GPL(sst_configure_runसमय_pm);

अटल पूर्णांक पूर्णांकel_sst_runसमय_suspend(काष्ठा device *dev)
अणु
	पूर्णांक ret = 0;
	काष्ठा पूर्णांकel_sst_drv *ctx = dev_get_drvdata(dev);

	अगर (ctx->sst_state == SST_RESET) अणु
		dev_dbg(dev, "LPE is already in RESET state, No action\n");
		वापस 0;
	पूर्ण
	/* save fw context */
	अगर (ctx->ops->save_dsp_context(ctx))
		वापस -EBUSY;

	/* Move the SST state to Reset */
	sst_set_fw_state_locked(ctx, SST_RESET);

	synchronize_irq(ctx->irq_num);
	flush_workqueue(ctx->post_msg_wq);

	ctx->ops->reset(ctx);

	वापस ret;
पूर्ण

अटल पूर्णांक पूर्णांकel_sst_suspend(काष्ठा device *dev)
अणु
	काष्ठा पूर्णांकel_sst_drv *ctx = dev_get_drvdata(dev);
	काष्ठा sst_fw_save *fw_save;
	पूर्णांक i, ret;

	/* check first अगर we are alपढ़ोy in SW reset */
	अगर (ctx->sst_state == SST_RESET)
		वापस 0;

	/*
	 * check अगर any stream is active and running
	 * they should alपढ़ोy by suspend by soc_suspend
	 */
	क्रम (i = 1; i <= ctx->info.max_streams; i++) अणु
		काष्ठा stream_info *stream = &ctx->streams[i];

		अगर (stream->status == STREAM_RUNNING) अणु
			dev_err(dev, "stream %d is running, can't suspend, abort\n", i);
			वापस -EBUSY;
		पूर्ण

		अगर (ctx->pdata->streams_lost_on_suspend) अणु
			stream->resume_status = stream->status;
			stream->resume_prev = stream->prev;
			अगर (stream->status != STREAM_UN_INIT)
				sst_मुक्त_stream(ctx, i);
		पूर्ण
	पूर्ण
	synchronize_irq(ctx->irq_num);
	flush_workqueue(ctx->post_msg_wq);

	/* Move the SST state to Reset */
	sst_set_fw_state_locked(ctx, SST_RESET);

	/* tell DSP we are suspending */
	अगर (ctx->ops->save_dsp_context(ctx))
		वापस -EBUSY;

	/* save the memories */
	fw_save = kzalloc(माप(*fw_save), GFP_KERNEL);
	अगर (!fw_save)
		वापस -ENOMEM;
	fw_save->iram = kvzalloc(ctx->iram_end - ctx->iram_base, GFP_KERNEL);
	अगर (!fw_save->iram) अणु
		ret = -ENOMEM;
		जाओ iram;
	पूर्ण
	fw_save->dram = kvzalloc(ctx->dram_end - ctx->dram_base, GFP_KERNEL);
	अगर (!fw_save->dram) अणु
		ret = -ENOMEM;
		जाओ dram;
	पूर्ण
	fw_save->sram = kvzalloc(SST_MAILBOX_SIZE, GFP_KERNEL);
	अगर (!fw_save->sram) अणु
		ret = -ENOMEM;
		जाओ sram;
	पूर्ण

	fw_save->ddr = kvzalloc(ctx->ddr_end - ctx->ddr_base, GFP_KERNEL);
	अगर (!fw_save->ddr) अणु
		ret = -ENOMEM;
		जाओ ddr;
	पूर्ण

	स_नकल32_fromio(fw_save->iram, ctx->iram, ctx->iram_end - ctx->iram_base);
	स_नकल32_fromio(fw_save->dram, ctx->dram, ctx->dram_end - ctx->dram_base);
	स_नकल32_fromio(fw_save->sram, ctx->mailbox, SST_MAILBOX_SIZE);
	स_नकल32_fromio(fw_save->ddr, ctx->ddr, ctx->ddr_end - ctx->ddr_base);

	ctx->fw_save = fw_save;
	ctx->ops->reset(ctx);
	वापस 0;
ddr:
	kvमुक्त(fw_save->sram);
sram:
	kvमुक्त(fw_save->dram);
dram:
	kvमुक्त(fw_save->iram);
iram:
	kमुक्त(fw_save);
	वापस ret;
पूर्ण

अटल पूर्णांक पूर्णांकel_sst_resume(काष्ठा device *dev)
अणु
	काष्ठा पूर्णांकel_sst_drv *ctx = dev_get_drvdata(dev);
	काष्ठा sst_fw_save *fw_save = ctx->fw_save;
	काष्ठा sst_block *block;
	पूर्णांक i, ret = 0;

	अगर (!fw_save)
		वापस 0;

	sst_set_fw_state_locked(ctx, SST_FW_LOADING);

	/* we have to restore the memory saved */
	ctx->ops->reset(ctx);

	ctx->fw_save = शून्य;

	स_नकल32_toio(ctx->iram, fw_save->iram, ctx->iram_end - ctx->iram_base);
	स_नकल32_toio(ctx->dram, fw_save->dram, ctx->dram_end - ctx->dram_base);
	स_नकल32_toio(ctx->mailbox, fw_save->sram, SST_MAILBOX_SIZE);
	स_नकल32_toio(ctx->ddr, fw_save->ddr, ctx->ddr_end - ctx->ddr_base);

	kvमुक्त(fw_save->sram);
	kvमुक्त(fw_save->dram);
	kvमुक्त(fw_save->iram);
	kvमुक्त(fw_save->ddr);
	kमुक्त(fw_save);

	block = sst_create_block(ctx, 0, FW_DWNL_ID);
	अगर (block == शून्य)
		वापस -ENOMEM;


	/* start and रुको क्रम ack */
	ctx->ops->start(ctx);
	ret = sst_रुको_समयout(ctx, block);
	अगर (ret) अणु
		dev_err(ctx->dev, "fw download failed %d\n", ret);
		/* FW करोwnload failed due to समयout */
		ret = -EBUSY;

	पूर्ण अन्यथा अणु
		sst_set_fw_state_locked(ctx, SST_FW_RUNNING);
	पूर्ण

	अगर (ctx->pdata->streams_lost_on_suspend) अणु
		क्रम (i = 1; i <= ctx->info.max_streams; i++) अणु
			काष्ठा stream_info *stream = &ctx->streams[i];

			अगर (stream->resume_status != STREAM_UN_INIT) अणु
				dev_dbg(ctx->dev, "Re-allocing stream %d status %d prev %d\n",
					i, stream->resume_status,
					stream->resume_prev);
				sst_पुनः_स्मृति_stream(ctx, i);
				stream->status = stream->resume_status;
				stream->prev = stream->resume_prev;
			पूर्ण
		पूर्ण
	पूर्ण

	sst_मुक्त_block(ctx, block);
	वापस ret;
पूर्ण

स्थिर काष्ठा dev_pm_ops पूर्णांकel_sst_pm = अणु
	.suspend = पूर्णांकel_sst_suspend,
	.resume = पूर्णांकel_sst_resume,
	.runसमय_suspend = पूर्णांकel_sst_runसमय_suspend,
पूर्ण;
EXPORT_SYMBOL_GPL(पूर्णांकel_sst_pm);
