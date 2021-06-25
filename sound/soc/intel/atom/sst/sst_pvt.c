<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  sst_pvt.c - Intel SST Driver क्रम audio engine
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
#समावेश <linux/kobject.h>
#समावेश <linux/pci.h>
#समावेश <linux/fs.h>
#समावेश <linux/firmware.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/sched.h>
#समावेश <linux/delay.h>
#समावेश <sound/asound.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/soc.h>
#समावेश <sound/compress_driver.h>
#समावेश <यंत्र/platक्रमm_sst_audपन.स>
#समावेश "../sst-mfld-platform.h"
#समावेश "sst.h"

पूर्णांक sst_shim_ग_लिखो(व्योम __iomem *addr, पूर्णांक offset, पूर्णांक value)
अणु
	ग_लिखोl(value, addr + offset);
	वापस 0;
पूर्ण

u32 sst_shim_पढ़ो(व्योम __iomem *addr, पूर्णांक offset)
अणु
	वापस पढ़ोl(addr + offset);
पूर्ण

u64 sst_reg_पढ़ो64(व्योम __iomem *addr, पूर्णांक offset)
अणु
	u64 val = 0;

	स_नकल_fromio(&val, addr + offset, माप(val));

	वापस val;
पूर्ण

पूर्णांक sst_shim_ग_लिखो64(व्योम __iomem *addr, पूर्णांक offset, u64 value)
अणु
	स_नकल_toio(addr + offset, &value, माप(value));
	वापस 0;
पूर्ण

u64 sst_shim_पढ़ो64(व्योम __iomem *addr, पूर्णांक offset)
अणु
	u64 val = 0;

	स_नकल_fromio(&val, addr + offset, माप(val));
	वापस val;
पूर्ण

व्योम sst_set_fw_state_locked(
		काष्ठा पूर्णांकel_sst_drv *sst_drv_ctx, पूर्णांक sst_state)
अणु
	mutex_lock(&sst_drv_ctx->sst_lock);
	sst_drv_ctx->sst_state = sst_state;
	mutex_unlock(&sst_drv_ctx->sst_lock);
पूर्ण

/*
 * sst_रुको_पूर्णांकerruptible - रुको on event
 *
 * @sst_drv_ctx: Driver context
 * @block: Driver block to रुको on
 *
 * This function रुकोs without a समयout (and is पूर्णांकerruptable) क्रम a
 * given block event
 */
पूर्णांक sst_रुको_पूर्णांकerruptible(काष्ठा पूर्णांकel_sst_drv *sst_drv_ctx,
				काष्ठा sst_block *block)
अणु
	पूर्णांक retval = 0;

	अगर (!रुको_event_पूर्णांकerruptible(sst_drv_ctx->रुको_queue,
				block->condition)) अणु
		/* event wake */
		अगर (block->ret_code < 0) अणु
			dev_err(sst_drv_ctx->dev,
				"stream failed %d\n", block->ret_code);
			retval = -EBUSY;
		पूर्ण अन्यथा अणु
			dev_dbg(sst_drv_ctx->dev, "event up\n");
			retval = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_err(sst_drv_ctx->dev, "signal interrupted\n");
		retval = -EINTR;
	पूर्ण
	वापस retval;

पूर्ण

/*
 * sst_रुको_समयout - रुको on event क्रम समयout
 *
 * @sst_drv_ctx: Driver context
 * @block: Driver block to रुको on
 *
 * This function रुकोs with a समयout value (and is not पूर्णांकerruptible) on a
 * given block event
 */
पूर्णांक sst_रुको_समयout(काष्ठा पूर्णांकel_sst_drv *sst_drv_ctx, काष्ठा sst_block *block)
अणु
	पूर्णांक retval = 0;

	/*
	 * NOTE:
	 * Observed that FW processes the alloc msg and replies even
	 * beक्रमe the alloc thपढ़ो has finished execution
	 */
	dev_dbg(sst_drv_ctx->dev,
		"waiting for condition %x ipc %d drv_id %d\n",
		block->condition, block->msg_id, block->drv_id);
	अगर (रुको_event_समयout(sst_drv_ctx->रुको_queue,
				block->condition,
				msecs_to_jअगरfies(SST_BLOCK_TIMEOUT))) अणु
		/* event wake */
		dev_dbg(sst_drv_ctx->dev, "Event wake %x\n",
				block->condition);
		dev_dbg(sst_drv_ctx->dev, "message ret: %d\n",
				block->ret_code);
		retval = -block->ret_code;
	पूर्ण अन्यथा अणु
		block->on = false;
		dev_err(sst_drv_ctx->dev,
			"Wait timed-out condition:%#x, msg_id:%#x fw_state %#x\n",
			block->condition, block->msg_id, sst_drv_ctx->sst_state);
		sst_drv_ctx->sst_state = SST_RESET;

		retval = -EBUSY;
	पूर्ण
	वापस retval;
पूर्ण

/*
 * sst_create_ipc_msg - create a IPC message
 *
 * @arg: ipc message
 * @large: large or लघु message
 *
 * this function allocates काष्ठाures to send a large or लघु
 * message to the firmware
 */
पूर्णांक sst_create_ipc_msg(काष्ठा ipc_post **arg, bool large)
अणु
	काष्ठा ipc_post *msg;

	msg = kzalloc(माप(*msg), GFP_ATOMIC);
	अगर (!msg)
		वापस -ENOMEM;
	अगर (large) अणु
		msg->mailbox_data = kzalloc(SST_MAILBOX_SIZE, GFP_ATOMIC);
		अगर (!msg->mailbox_data) अणु
			kमुक्त(msg);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण अन्यथा अणु
		msg->mailbox_data = शून्य;
	पूर्ण
	msg->is_large = large;
	*arg = msg;
	वापस 0;
पूर्ण

/*
 * sst_create_block_and_ipc_msg - Creates IPC message and sst block
 * @arg: passed to sst_create_ipc_message API
 * @large: large or लघु message
 * @sst_drv_ctx: sst driver context
 * @block: वापस block allocated
 * @msg_id: IPC
 * @drv_id: stream id or निजी id
 */
पूर्णांक sst_create_block_and_ipc_msg(काष्ठा ipc_post **arg, bool large,
		काष्ठा पूर्णांकel_sst_drv *sst_drv_ctx, काष्ठा sst_block **block,
		u32 msg_id, u32 drv_id)
अणु
	पूर्णांक retval;

	retval = sst_create_ipc_msg(arg, large);
	अगर (retval)
		वापस retval;
	*block = sst_create_block(sst_drv_ctx, msg_id, drv_id);
	अगर (*block == शून्य) अणु
		kमुक्त(*arg);
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * sst_clean_stream - clean the stream context
 *
 * @stream: stream काष्ठाure
 *
 * this function resets the stream contexts
 * should be called in मुक्त
 */
व्योम sst_clean_stream(काष्ठा stream_info *stream)
अणु
	stream->status = STREAM_UN_INIT;
	stream->prev = STREAM_UN_INIT;
	mutex_lock(&stream->lock);
	stream->cumm_bytes = 0;
	mutex_unlock(&stream->lock);
पूर्ण

पूर्णांक sst_prepare_and_post_msg(काष्ठा पूर्णांकel_sst_drv *sst,
		पूर्णांक task_id, पूर्णांक ipc_msg, पूर्णांक cmd_id, पूर्णांक pipe_id,
		माप_प्रकार mbox_data_len, स्थिर व्योम *mbox_data, व्योम **data,
		bool large, bool fill_dsp, bool sync, bool response)
अणु
	काष्ठा sst_block *block = शून्य;
	काष्ठा ipc_post *msg = शून्य;
	काष्ठा ipc_dsp_hdr dsp_hdr;
	पूर्णांक ret = 0, pvt_id;

	pvt_id = sst_assign_pvt_id(sst);
	अगर (pvt_id < 0)
		वापस pvt_id;

	अगर (response)
		ret = sst_create_block_and_ipc_msg(
				&msg, large, sst, &block, ipc_msg, pvt_id);
	अन्यथा
		ret = sst_create_ipc_msg(&msg, large);

	अगर (ret < 0) अणु
		test_and_clear_bit(pvt_id, &sst->pvt_id);
		वापस -ENOMEM;
	पूर्ण

	dev_dbg(sst->dev, "pvt_id = %d, pipe id = %d, task = %d ipc_msg: %d\n",
		 pvt_id, pipe_id, task_id, ipc_msg);
	sst_fill_header_mrfld(&msg->mrfld_header, ipc_msg,
					task_id, large, pvt_id);
	msg->mrfld_header.p.header_low_payload = माप(dsp_hdr) + mbox_data_len;
	msg->mrfld_header.p.header_high.part.res_rqd = !sync;
	dev_dbg(sst->dev, "header:%x\n",
			msg->mrfld_header.p.header_high.full);
	dev_dbg(sst->dev, "response rqd: %x",
			msg->mrfld_header.p.header_high.part.res_rqd);
	dev_dbg(sst->dev, "msg->mrfld_header.p.header_low_payload:%d",
			msg->mrfld_header.p.header_low_payload);
	अगर (fill_dsp) अणु
		sst_fill_header_dsp(&dsp_hdr, cmd_id, pipe_id, mbox_data_len);
		स_नकल(msg->mailbox_data, &dsp_hdr, माप(dsp_hdr));
		अगर (mbox_data_len) अणु
			स_नकल(msg->mailbox_data + माप(dsp_hdr),
					mbox_data, mbox_data_len);
		पूर्ण
	पूर्ण

	अगर (sync)
		sst->ops->post_message(sst, msg, true);
	अन्यथा
		sst_add_to_dispatch_list_and_post(sst, msg);

	अगर (response) अणु
		ret = sst_रुको_समयout(sst, block);
		अगर (ret < 0)
			जाओ out;

		अगर (data && block->data) अणु
			*data = kmemdup(block->data, block->size, GFP_KERNEL);
			अगर (!*data) अणु
				ret = -ENOMEM;
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण
out:
	अगर (response)
		sst_मुक्त_block(sst, block);
	test_and_clear_bit(pvt_id, &sst->pvt_id);
	वापस ret;
पूर्ण

पूर्णांक sst_pm_runसमय_put(काष्ठा पूर्णांकel_sst_drv *sst_drv)
अणु
	पूर्णांक ret;

	pm_runसमय_mark_last_busy(sst_drv->dev);
	ret = pm_runसमय_put_स्वतःsuspend(sst_drv->dev);
	अगर (ret < 0)
		वापस ret;
	वापस 0;
पूर्ण

व्योम sst_fill_header_mrfld(जोड़ ipc_header_mrfld *header,
				पूर्णांक msg, पूर्णांक task_id, पूर्णांक large, पूर्णांक drv_id)
अणु
	header->full = 0;
	header->p.header_high.part.msg_id = msg;
	header->p.header_high.part.task_id = task_id;
	header->p.header_high.part.large = large;
	header->p.header_high.part.drv_id = drv_id;
	header->p.header_high.part.करोne = 0;
	header->p.header_high.part.busy = 1;
	header->p.header_high.part.res_rqd = 1;
पूर्ण

व्योम sst_fill_header_dsp(काष्ठा ipc_dsp_hdr *dsp, पूर्णांक msg,
					पूर्णांक pipe_id, पूर्णांक len)
अणु
	dsp->cmd_id = msg;
	dsp->mod_index_id = 0xff;
	dsp->pipe_id = pipe_id;
	dsp->length = len;
	dsp->mod_id = 0;
पूर्ण

#घोषणा SST_MAX_BLOCKS 15
/*
 * sst_assign_pvt_id - assign a pvt id क्रम stream
 *
 * @sst_drv_ctx : driver context
 *
 * this function assigns a निजी id क्रम calls that करोnt have stream
 * context yet, should be called with lock held
 * uses bits क्रम the id, and finds first मुक्त bits and assigns that
 */
पूर्णांक sst_assign_pvt_id(काष्ठा पूर्णांकel_sst_drv *drv)
अणु
	पूर्णांक local;

	spin_lock(&drv->block_lock);
	/* find first zero index from lsb */
	local = ffz(drv->pvt_id);
	dev_dbg(drv->dev, "pvt_id assigned --> %d\n", local);
	अगर (local >= SST_MAX_BLOCKS)अणु
		spin_unlock(&drv->block_lock);
		dev_err(drv->dev, "PVT _ID error: no free id blocks ");
		वापस -EINVAL;
	पूर्ण
	/* toggle the index */
	change_bit(local, &drv->pvt_id);
	spin_unlock(&drv->block_lock);
	वापस local;
पूर्ण

पूर्णांक sst_validate_strid(
		काष्ठा पूर्णांकel_sst_drv *sst_drv_ctx, पूर्णांक str_id)
अणु
	अगर (str_id <= 0 || str_id > sst_drv_ctx->info.max_streams) अणु
		dev_err(sst_drv_ctx->dev,
			"SST ERR: invalid stream id : %d, max %d\n",
			str_id, sst_drv_ctx->info.max_streams);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा stream_info *get_stream_info(
		काष्ठा पूर्णांकel_sst_drv *sst_drv_ctx, पूर्णांक str_id)
अणु
	अगर (sst_validate_strid(sst_drv_ctx, str_id))
		वापस शून्य;
	वापस &sst_drv_ctx->streams[str_id];
पूर्ण

पूर्णांक get_stream_id_mrfld(काष्ठा पूर्णांकel_sst_drv *sst_drv_ctx,
		u32 pipe_id)
अणु
	पूर्णांक i;

	क्रम (i = 1; i <= sst_drv_ctx->info.max_streams; i++)
		अगर (pipe_id == sst_drv_ctx->streams[i].pipe_id)
			वापस i;

	dev_dbg(sst_drv_ctx->dev, "no such pipe_id(%u)", pipe_id);
	वापस -1;
पूर्ण

u32 relocate_imr_addr_mrfld(u32 base_addr)
अणु
	/* Get the dअगरference from 512MB aligned base addr */
	/* relocate the base */
	base_addr = MRFLD_FW_VIRTUAL_BASE + (base_addr % (512 * 1024 * 1024));
	वापस base_addr;
पूर्ण
EXPORT_SYMBOL_GPL(relocate_imr_addr_mrfld);

व्योम sst_add_to_dispatch_list_and_post(काष्ठा पूर्णांकel_sst_drv *sst,
						काष्ठा ipc_post *msg)
अणु
	अचिन्हित दीर्घ irq_flags;

	spin_lock_irqsave(&sst->ipc_spin_lock, irq_flags);
	list_add_tail(&msg->node, &sst->ipc_dispatch_list);
	spin_unlock_irqrestore(&sst->ipc_spin_lock, irq_flags);
	sst->ops->post_message(sst, शून्य, false);
पूर्ण
