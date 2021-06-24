<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  sst_ipc.c - Intel SST Driver क्रम audio engine
 *
 *  Copyright (C) 2008-14 Intel Corporation
 *  Authors:	Vinod Koul <vinod.koul@पूर्णांकel.com>
 *		Harsha Priya <priya.harsha@पूर्णांकel.com>
 *		Dharageswari R <dharageswari.r@पूर्णांकel.com>
 *		KP Jeeja <jeeja.kp@पूर्णांकel.com>
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
#समावेश <linux/pci.h>
#समावेश <linux/firmware.h>
#समावेश <linux/sched.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/soc.h>
#समावेश <sound/compress_driver.h>
#समावेश <यंत्र/पूर्णांकel-mid.h>
#समावेश <यंत्र/platक्रमm_sst_audपन.स>
#समावेश "../sst-mfld-platform.h"
#समावेश "sst.h"

काष्ठा sst_block *sst_create_block(काष्ठा पूर्णांकel_sst_drv *ctx,
					u32 msg_id, u32 drv_id)
अणु
	काष्ठा sst_block *msg = शून्य;

	dev_dbg(ctx->dev, "Enter\n");
	msg = kzalloc(माप(*msg), GFP_KERNEL);
	अगर (!msg)
		वापस शून्य;
	msg->condition = false;
	msg->on = true;
	msg->msg_id = msg_id;
	msg->drv_id = drv_id;
	spin_lock_bh(&ctx->block_lock);
	list_add_tail(&msg->node, &ctx->block_list);
	spin_unlock_bh(&ctx->block_lock);

	वापस msg;
पूर्ण

/*
 * जबतक handling the पूर्णांकerrupts, we need to check क्रम message status and
 * then अगर we are blocking क्रम a message
 *
 * here we are unblocking the blocked ones, this is based on id we have
 * passed and search that क्रम block thपढ़ोs.
 * We will not find block in two हालs
 *  a) when its small message and block in not there, so silently ignore
 *  them
 *  b) when we are actually not able to find the block (bug perhaps)
 *
 *  Since we have bit of small messages we can spam kernel log with err
 *  prपूर्णांक on above so need to keep as debug prपूर्णांकs which should be enabled
 *  via dynamic debug जबतक debugging IPC issues
 */
पूर्णांक sst_wake_up_block(काष्ठा पूर्णांकel_sst_drv *ctx, पूर्णांक result,
		u32 drv_id, u32 ipc, व्योम *data, u32 size)
अणु
	काष्ठा sst_block *block = शून्य;

	dev_dbg(ctx->dev, "Enter\n");

	spin_lock_bh(&ctx->block_lock);
	list_क्रम_each_entry(block, &ctx->block_list, node) अणु
		dev_dbg(ctx->dev, "Block ipc %d, drv_id %d\n", block->msg_id,
							block->drv_id);
		अगर (block->msg_id == ipc && block->drv_id == drv_id) अणु
			dev_dbg(ctx->dev, "free up the block\n");
			block->ret_code = result;
			block->data = data;
			block->size = size;
			block->condition = true;
			spin_unlock_bh(&ctx->block_lock);
			wake_up(&ctx->रुको_queue);
			वापस 0;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&ctx->block_lock);
	dev_dbg(ctx->dev,
		"Block not found or a response received for a short msg for ipc %d, drv_id %d\n",
		ipc, drv_id);
	वापस -EINVAL;
पूर्ण

पूर्णांक sst_मुक्त_block(काष्ठा पूर्णांकel_sst_drv *ctx, काष्ठा sst_block *मुक्तd)
अणु
	काष्ठा sst_block *block = शून्य, *__block;

	dev_dbg(ctx->dev, "Enter\n");
	spin_lock_bh(&ctx->block_lock);
	list_क्रम_each_entry_safe(block, __block, &ctx->block_list, node) अणु
		अगर (block == मुक्तd) अणु
			pr_debug("pvt_id freed --> %d\n", मुक्तd->drv_id);
			/* toggle the index position of pvt_id */
			list_del(&मुक्तd->node);
			spin_unlock_bh(&ctx->block_lock);
			kमुक्त(मुक्तd->data);
			मुक्तd->data = शून्य;
			kमुक्त(मुक्तd);
			वापस 0;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&ctx->block_lock);
	dev_err(ctx->dev, "block is already freed!!!\n");
	वापस -EINVAL;
पूर्ण

पूर्णांक sst_post_message_mrfld(काष्ठा पूर्णांकel_sst_drv *sst_drv_ctx,
		काष्ठा ipc_post *ipc_msg, bool sync)
अणु
	काष्ठा ipc_post *msg = ipc_msg;
	जोड़ ipc_header_mrfld header;
	अचिन्हित पूर्णांक loop_count = 0;
	पूर्णांक retval = 0;
	अचिन्हित दीर्घ irq_flags;

	dev_dbg(sst_drv_ctx->dev, "Enter: sync: %d\n", sync);
	spin_lock_irqsave(&sst_drv_ctx->ipc_spin_lock, irq_flags);
	header.full = sst_shim_पढ़ो64(sst_drv_ctx->shim, SST_IPCX);
	अगर (sync) अणु
		जबतक (header.p.header_high.part.busy) अणु
			अगर (loop_count > 25) अणु
				dev_err(sst_drv_ctx->dev,
					"sst: Busy wait failed, cant send this msg\n");
				retval = -EBUSY;
				जाओ out;
			पूर्ण
			cpu_relax();
			loop_count++;
			header.full = sst_shim_पढ़ो64(sst_drv_ctx->shim, SST_IPCX);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (list_empty(&sst_drv_ctx->ipc_dispatch_list)) अणु
			/* queue is empty, nothing to send */
			spin_unlock_irqrestore(&sst_drv_ctx->ipc_spin_lock, irq_flags);
			dev_dbg(sst_drv_ctx->dev,
					"Empty msg queue... NO Action\n");
			वापस 0;
		पूर्ण

		अगर (header.p.header_high.part.busy) अणु
			spin_unlock_irqrestore(&sst_drv_ctx->ipc_spin_lock, irq_flags);
			dev_dbg(sst_drv_ctx->dev, "Busy not free... post later\n");
			वापस 0;
		पूर्ण

		/* copy msg from list */
		msg = list_entry(sst_drv_ctx->ipc_dispatch_list.next,
				काष्ठा ipc_post, node);
		list_del(&msg->node);
	पूर्ण
	dev_dbg(sst_drv_ctx->dev, "sst: Post message: header = %x\n",
				msg->mrfld_header.p.header_high.full);
	dev_dbg(sst_drv_ctx->dev, "sst: size = 0x%x\n",
			msg->mrfld_header.p.header_low_payload);

	अगर (msg->mrfld_header.p.header_high.part.large)
		स_नकल_toio(sst_drv_ctx->mailbox + SST_MAILBOX_SEND,
			msg->mailbox_data,
			msg->mrfld_header.p.header_low_payload);

	sst_shim_ग_लिखो64(sst_drv_ctx->shim, SST_IPCX, msg->mrfld_header.full);

out:
	spin_unlock_irqrestore(&sst_drv_ctx->ipc_spin_lock, irq_flags);
	kमुक्त(msg->mailbox_data);
	kमुक्त(msg);
	वापस retval;
पूर्ण

व्योम पूर्णांकel_sst_clear_पूर्णांकr_mrfld(काष्ठा पूर्णांकel_sst_drv *sst_drv_ctx)
अणु
	जोड़ पूर्णांकerrupt_reg_mrfld isr;
	जोड़ पूर्णांकerrupt_reg_mrfld imr;
	जोड़ ipc_header_mrfld clear_ipc;
	अचिन्हित दीर्घ irq_flags;

	spin_lock_irqsave(&sst_drv_ctx->ipc_spin_lock, irq_flags);
	imr.full = sst_shim_पढ़ो64(sst_drv_ctx->shim, SST_IMRX);
	isr.full = sst_shim_पढ़ो64(sst_drv_ctx->shim, SST_ISRX);

	/* ग_लिखो 1 to clear*/
	isr.part.busy_पूर्णांकerrupt = 1;
	sst_shim_ग_लिखो64(sst_drv_ctx->shim, SST_ISRX, isr.full);

	/* Set IA करोne bit */
	clear_ipc.full = sst_shim_पढ़ो64(sst_drv_ctx->shim, SST_IPCD);

	clear_ipc.p.header_high.part.busy = 0;
	clear_ipc.p.header_high.part.करोne = 1;
	clear_ipc.p.header_low_payload = IPC_ACK_SUCCESS;
	sst_shim_ग_लिखो64(sst_drv_ctx->shim, SST_IPCD, clear_ipc.full);
	/* un mask busy पूर्णांकerrupt */
	imr.part.busy_पूर्णांकerrupt = 0;
	sst_shim_ग_लिखो64(sst_drv_ctx->shim, SST_IMRX, imr.full);
	spin_unlock_irqrestore(&sst_drv_ctx->ipc_spin_lock, irq_flags);
पूर्ण


/*
 * process_fw_init - process the FW init msg
 *
 * @msg: IPC message mailbox data from FW
 *
 * This function processes the FW init msg from FW
 * marks FW state and prपूर्णांकs debug info of loaded FW
 */
अटल व्योम process_fw_init(काष्ठा पूर्णांकel_sst_drv *sst_drv_ctx,
			व्योम *msg)
अणु
	काष्ठा ipc_header_fw_init *init =
		(काष्ठा ipc_header_fw_init *)msg;
	पूर्णांक retval = 0;

	dev_dbg(sst_drv_ctx->dev, "*** FW Init msg came***\n");
	अगर (init->result) अणु
		sst_set_fw_state_locked(sst_drv_ctx, SST_RESET);
		dev_err(sst_drv_ctx->dev, "FW Init failed, Error %x\n",
				init->result);
		retval = init->result;
		जाओ ret;
	पूर्ण
	अगर (स_भेद(&sst_drv_ctx->fw_version, &init->fw_version,
		   माप(init->fw_version)))
		dev_info(sst_drv_ctx->dev, "FW Version %02x.%02x.%02x.%02x\n",
			init->fw_version.type, init->fw_version.major,
			init->fw_version.minor, init->fw_version.build);
	dev_dbg(sst_drv_ctx->dev, "Build date %s Time %s\n",
			init->build_info.date, init->build_info.समय);

	/* Save FW version */
	sst_drv_ctx->fw_version.type = init->fw_version.type;
	sst_drv_ctx->fw_version.major = init->fw_version.major;
	sst_drv_ctx->fw_version.minor = init->fw_version.minor;
	sst_drv_ctx->fw_version.build = init->fw_version.build;

ret:
	sst_wake_up_block(sst_drv_ctx, retval, FW_DWNL_ID, 0 , शून्य, 0);
पूर्ण

अटल व्योम process_fw_async_msg(काष्ठा पूर्णांकel_sst_drv *sst_drv_ctx,
			काष्ठा ipc_post *msg)
अणु
	u32 msg_id;
	पूर्णांक str_id;
	u32 data_size, i;
	व्योम *data_offset;
	काष्ठा stream_info *stream;
	u32 msg_low, pipe_id;

	msg_low = msg->mrfld_header.p.header_low_payload;
	msg_id = ((काष्ठा ipc_dsp_hdr *)msg->mailbox_data)->cmd_id;
	data_offset = (msg->mailbox_data + माप(काष्ठा ipc_dsp_hdr));
	data_size =  msg_low - (माप(काष्ठा ipc_dsp_hdr));

	चयन (msg_id) अणु
	हाल IPC_SST_PERIOD_ELAPSED_MRFLD:
		pipe_id = ((काष्ठा ipc_dsp_hdr *)msg->mailbox_data)->pipe_id;
		str_id = get_stream_id_mrfld(sst_drv_ctx, pipe_id);
		अगर (str_id > 0) अणु
			dev_dbg(sst_drv_ctx->dev,
				"Period elapsed rcvd for pipe id 0x%x\n",
				pipe_id);
			stream = &sst_drv_ctx->streams[str_id];
			/* If stream is dropped, skip processing this message*/
			अगर (stream->status == STREAM_INIT)
				अवरोध;
			अगर (stream->period_elapsed)
				stream->period_elapsed(stream->pcm_substream);
			अगर (stream->compr_cb)
				stream->compr_cb(stream->compr_cb_param);
		पूर्ण
		अवरोध;

	हाल IPC_IA_DRAIN_STREAM_MRFLD:
		pipe_id = ((काष्ठा ipc_dsp_hdr *)msg->mailbox_data)->pipe_id;
		str_id = get_stream_id_mrfld(sst_drv_ctx, pipe_id);
		अगर (str_id > 0) अणु
			stream = &sst_drv_ctx->streams[str_id];
			अगर (stream->drain_notअगरy)
				stream->drain_notअगरy(stream->drain_cb_param);
		पूर्ण
		अवरोध;

	हाल IPC_IA_FW_ASYNC_ERR_MRFLD:
		dev_err(sst_drv_ctx->dev, "FW sent async error msg:\n");
		क्रम (i = 0; i < (data_size/4); i++)
			prपूर्णांक_hex_dump(KERN_DEBUG, शून्य, DUMP_PREFIX_NONE,
					16, 4, data_offset, data_size, false);
		अवरोध;

	हाल IPC_IA_FW_INIT_CMPLT_MRFLD:
		process_fw_init(sst_drv_ctx, data_offset);
		अवरोध;

	हाल IPC_IA_BUF_UNDER_RUN_MRFLD:
		pipe_id = ((काष्ठा ipc_dsp_hdr *)msg->mailbox_data)->pipe_id;
		str_id = get_stream_id_mrfld(sst_drv_ctx, pipe_id);
		अगर (str_id > 0)
			dev_err(sst_drv_ctx->dev,
				"Buffer under-run for pipe:%#x str_id:%d\n",
				pipe_id, str_id);
		अवरोध;

	शेष:
		dev_err(sst_drv_ctx->dev,
			"Unrecognized async msg from FW msg_id %#x\n", msg_id);
	पूर्ण
पूर्ण

व्योम sst_process_reply_mrfld(काष्ठा पूर्णांकel_sst_drv *sst_drv_ctx,
		काष्ठा ipc_post *msg)
अणु
	अचिन्हित पूर्णांक drv_id;
	व्योम *data;
	जोड़ ipc_header_high msg_high;
	u32 msg_low;
	काष्ठा ipc_dsp_hdr *dsp_hdr;

	msg_high = msg->mrfld_header.p.header_high;
	msg_low = msg->mrfld_header.p.header_low_payload;

	dev_dbg(sst_drv_ctx->dev, "IPC process message header %x payload %x\n",
			msg->mrfld_header.p.header_high.full,
			msg->mrfld_header.p.header_low_payload);

	drv_id = msg_high.part.drv_id;

	/* Check क्रम async messages first */
	अगर (drv_id == SST_ASYNC_DRV_ID) अणु
		/*FW sent async large message*/
		process_fw_async_msg(sst_drv_ctx, msg);
		वापस;
	पूर्ण

	/* FW sent लघु error response क्रम an IPC */
	अगर (msg_high.part.result && drv_id && !msg_high.part.large) अणु
		/* 32-bit FW error code in msg_low */
		dev_err(sst_drv_ctx->dev, "FW sent error response 0x%x", msg_low);
		sst_wake_up_block(sst_drv_ctx, msg_high.part.result,
			msg_high.part.drv_id,
			msg_high.part.msg_id, शून्य, 0);
		वापस;
	पूर्ण

	/*
	 * Process all valid responses
	 * अगर it is a large message, the payload contains the size to
	 * copy from mailbox
	 **/
	अगर (msg_high.part.large) अणु
		data = kmemdup((व्योम *)msg->mailbox_data, msg_low, GFP_KERNEL);
		अगर (!data)
			वापस;
		/* Copy command id so that we can use to put sst to reset */
		dsp_hdr = (काष्ठा ipc_dsp_hdr *)data;
		dev_dbg(sst_drv_ctx->dev, "cmd_id %d\n", dsp_hdr->cmd_id);
		अगर (sst_wake_up_block(sst_drv_ctx, msg_high.part.result,
				msg_high.part.drv_id,
				msg_high.part.msg_id, data, msg_low))
			kमुक्त(data);
	पूर्ण अन्यथा अणु
		sst_wake_up_block(sst_drv_ctx, msg_high.part.result,
				msg_high.part.drv_id,
				msg_high.part.msg_id, शून्य, 0);
	पूर्ण

पूर्ण
