<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * cnl-sst.c - DSP library functions क्रम CNL platक्रमm
 *
 * Copyright (C) 2016-17, Intel Corporation.
 *
 * Author: Guneshwor Singh <guneshwor.o.singh@पूर्णांकel.com>
 *
 * Modअगरied from:
 *	HDA DSP library functions क्रम SKL platक्रमm
 *	Copyright (C) 2014-15, Intel Corporation.
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/firmware.h>
#समावेश <linux/device.h>

#समावेश "../common/sst-dsp.h"
#समावेश "../common/sst-dsp-priv.h"
#समावेश "../common/sst-ipc.h"
#समावेश "cnl-sst-dsp.h"
#समावेश "skl.h"

#घोषणा CNL_FW_ROM_INIT		0x1
#घोषणा CNL_FW_INIT		0x5
#घोषणा CNL_IPC_PURGE		0x01004000
#घोषणा CNL_INIT_TIMEOUT	300
#घोषणा CNL_BASEFW_TIMEOUT	3000

#घोषणा CNL_ADSP_SRAM0_BASE	0x80000

/* Firmware status winकरोw */
#घोषणा CNL_ADSP_FW_STATUS	CNL_ADSP_SRAM0_BASE
#घोषणा CNL_ADSP_ERROR_CODE	(CNL_ADSP_FW_STATUS + 0x4)

#घोषणा CNL_INSTANCE_ID		0
#घोषणा CNL_BASE_FW_MODULE_ID	0
#घोषणा CNL_ADSP_FW_HDR_OFFSET	0x2000
#घोषणा CNL_ROM_CTRL_DMA_ID	0x9

अटल पूर्णांक cnl_prepare_fw(काष्ठा sst_dsp *ctx, स्थिर व्योम *fwdata, u32 fwsize)
अणु

	पूर्णांक ret, stream_tag;

	stream_tag = ctx->dsp_ops.prepare(ctx->dev, 0x40, fwsize, &ctx->dmab);
	अगर (stream_tag <= 0) अणु
		dev_err(ctx->dev, "dma prepare failed: 0%#x\n", stream_tag);
		वापस stream_tag;
	पूर्ण

	ctx->dsp_ops.stream_tag = stream_tag;
	स_नकल(ctx->dmab.area, fwdata, fwsize);

	ret = skl_dsp_core_घातer_up(ctx, SKL_DSP_CORE0_MASK);
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "dsp core0 power up failed\n");
		ret = -EIO;
		जाओ base_fw_load_failed;
	पूर्ण

	/* purge FW request */
	sst_dsp_shim_ग_लिखो(ctx, CNL_ADSP_REG_HIPCIDR,
			   CNL_ADSP_REG_HIPCIDR_BUSY | (CNL_IPC_PURGE |
			   ((stream_tag - 1) << CNL_ROM_CTRL_DMA_ID)));

	ret = skl_dsp_start_core(ctx, SKL_DSP_CORE0_MASK);
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "Start dsp core failed ret: %d\n", ret);
		ret = -EIO;
		जाओ base_fw_load_failed;
	पूर्ण

	ret = sst_dsp_रेजिस्टर_poll(ctx, CNL_ADSP_REG_HIPCIDA,
				    CNL_ADSP_REG_HIPCIDA_DONE,
				    CNL_ADSP_REG_HIPCIDA_DONE,
				    BXT_INIT_TIMEOUT, "HIPCIDA Done");
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "timeout for purge request: %d\n", ret);
		जाओ base_fw_load_failed;
	पूर्ण

	/* enable पूर्णांकerrupt */
	cnl_ipc_पूर्णांक_enable(ctx);
	cnl_ipc_op_पूर्णांक_enable(ctx);

	ret = sst_dsp_रेजिस्टर_poll(ctx, CNL_ADSP_FW_STATUS, CNL_FW_STS_MASK,
				    CNL_FW_ROM_INIT, CNL_INIT_TIMEOUT,
				    "rom load");
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "rom init timeout, ret: %d\n", ret);
		जाओ base_fw_load_failed;
	पूर्ण

	वापस 0;

base_fw_load_failed:
	ctx->dsp_ops.cleanup(ctx->dev, &ctx->dmab, stream_tag);
	cnl_dsp_disable_core(ctx, SKL_DSP_CORE0_MASK);

	वापस ret;
पूर्ण

अटल पूर्णांक sst_transfer_fw_host_dma(काष्ठा sst_dsp *ctx)
अणु
	पूर्णांक ret;

	ctx->dsp_ops.trigger(ctx->dev, true, ctx->dsp_ops.stream_tag);
	ret = sst_dsp_रेजिस्टर_poll(ctx, CNL_ADSP_FW_STATUS, CNL_FW_STS_MASK,
				    CNL_FW_INIT, CNL_BASEFW_TIMEOUT,
				    "firmware boot");

	ctx->dsp_ops.trigger(ctx->dev, false, ctx->dsp_ops.stream_tag);
	ctx->dsp_ops.cleanup(ctx->dev, &ctx->dmab, ctx->dsp_ops.stream_tag);

	वापस ret;
पूर्ण

अटल पूर्णांक cnl_load_base_firmware(काष्ठा sst_dsp *ctx)
अणु
	काष्ठा firmware stripped_fw;
	काष्ठा skl_dev *cnl = ctx->thपढ़ो_context;
	पूर्णांक ret, i;

	अगर (!ctx->fw) अणु
		ret = request_firmware(&ctx->fw, ctx->fw_name, ctx->dev);
		अगर (ret < 0) अणु
			dev_err(ctx->dev, "request firmware failed: %d\n", ret);
			जाओ cnl_load_base_firmware_failed;
		पूर्ण
	पूर्ण

	/* parse uuids अगर first boot */
	अगर (cnl->is_first_boot) अणु
		ret = snd_skl_parse_uuids(ctx, ctx->fw,
					  CNL_ADSP_FW_HDR_OFFSET, 0);
		अगर (ret < 0)
			जाओ cnl_load_base_firmware_failed;
	पूर्ण

	stripped_fw.data = ctx->fw->data;
	stripped_fw.size = ctx->fw->size;
	skl_dsp_strip_extended_manअगरest(&stripped_fw);

	क्रम (i = 0; i < BXT_FW_ROM_INIT_RETRY; i++) अणु
		ret = cnl_prepare_fw(ctx, stripped_fw.data, stripped_fw.size);
		अगर (!ret)
			अवरोध;
		dev_dbg(ctx->dev, "prepare firmware failed: %d\n", ret);
	पूर्ण

	अगर (ret < 0)
		जाओ cnl_load_base_firmware_failed;

	ret = sst_transfer_fw_host_dma(ctx);
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "transfer firmware failed: %d\n", ret);
		cnl_dsp_disable_core(ctx, SKL_DSP_CORE0_MASK);
		जाओ cnl_load_base_firmware_failed;
	पूर्ण

	ret = रुको_event_समयout(cnl->boot_रुको, cnl->boot_complete,
				 msecs_to_jअगरfies(SKL_IPC_BOOT_MSECS));
	अगर (ret == 0) अणु
		dev_err(ctx->dev, "FW ready timed-out\n");
		cnl_dsp_disable_core(ctx, SKL_DSP_CORE0_MASK);
		ret = -EIO;
		जाओ cnl_load_base_firmware_failed;
	पूर्ण

	cnl->fw_loaded = true;

	वापस 0;

cnl_load_base_firmware_failed:
	dev_err(ctx->dev, "firmware load failed: %d\n", ret);
	release_firmware(ctx->fw);
	ctx->fw = शून्य;

	वापस ret;
पूर्ण

अटल पूर्णांक cnl_set_dsp_D0(काष्ठा sst_dsp *ctx, अचिन्हित पूर्णांक core_id)
अणु
	काष्ठा skl_dev *cnl = ctx->thपढ़ो_context;
	अचिन्हित पूर्णांक core_mask = SKL_DSP_CORE_MASK(core_id);
	काष्ठा skl_ipc_dxstate_info dx;
	पूर्णांक ret;

	अगर (!cnl->fw_loaded) अणु
		cnl->boot_complete = false;
		ret = cnl_load_base_firmware(ctx);
		अगर (ret < 0) अणु
			dev_err(ctx->dev, "fw reload failed: %d\n", ret);
			वापस ret;
		पूर्ण

		cnl->cores.state[core_id] = SKL_DSP_RUNNING;
		वापस ret;
	पूर्ण

	ret = cnl_dsp_enable_core(ctx, core_mask);
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "enable dsp core %d failed: %d\n",
			core_id, ret);
		जाओ err;
	पूर्ण

	अगर (core_id == SKL_DSP_CORE0_ID) अणु
		/* enable पूर्णांकerrupt */
		cnl_ipc_पूर्णांक_enable(ctx);
		cnl_ipc_op_पूर्णांक_enable(ctx);
		cnl->boot_complete = false;

		ret = रुको_event_समयout(cnl->boot_रुको, cnl->boot_complete,
					 msecs_to_jअगरfies(SKL_IPC_BOOT_MSECS));
		अगर (ret == 0) अणु
			dev_err(ctx->dev,
				"dsp boot timeout, status=%#x error=%#x\n",
				sst_dsp_shim_पढ़ो(ctx, CNL_ADSP_FW_STATUS),
				sst_dsp_shim_पढ़ो(ctx, CNL_ADSP_ERROR_CODE));
			ret = -ETIMEDOUT;
			जाओ err;
		पूर्ण
	पूर्ण अन्यथा अणु
		dx.core_mask = core_mask;
		dx.dx_mask = core_mask;

		ret = skl_ipc_set_dx(&cnl->ipc, CNL_INSTANCE_ID,
				     CNL_BASE_FW_MODULE_ID, &dx);
		अगर (ret < 0) अणु
			dev_err(ctx->dev, "set_dx failed, core: %d ret: %d\n",
				core_id, ret);
			जाओ err;
		पूर्ण
	पूर्ण
	cnl->cores.state[core_id] = SKL_DSP_RUNNING;

	वापस 0;
err:
	cnl_dsp_disable_core(ctx, core_mask);

	वापस ret;
पूर्ण

अटल पूर्णांक cnl_set_dsp_D3(काष्ठा sst_dsp *ctx, अचिन्हित पूर्णांक core_id)
अणु
	काष्ठा skl_dev *cnl = ctx->thपढ़ो_context;
	अचिन्हित पूर्णांक core_mask = SKL_DSP_CORE_MASK(core_id);
	काष्ठा skl_ipc_dxstate_info dx;
	पूर्णांक ret;

	dx.core_mask = core_mask;
	dx.dx_mask = SKL_IPC_D3_MASK;

	ret = skl_ipc_set_dx(&cnl->ipc, CNL_INSTANCE_ID,
			     CNL_BASE_FW_MODULE_ID, &dx);
	अगर (ret < 0) अणु
		dev_err(ctx->dev,
			"dsp core %d to d3 failed; continue reset\n",
			core_id);
		cnl->fw_loaded = false;
	पूर्ण

	/* disable पूर्णांकerrupts अगर core 0 */
	अगर (core_id == SKL_DSP_CORE0_ID) अणु
		skl_ipc_op_पूर्णांक_disable(ctx);
		skl_ipc_पूर्णांक_disable(ctx);
	पूर्ण

	ret = cnl_dsp_disable_core(ctx, core_mask);
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "disable dsp core %d failed: %d\n",
			core_id, ret);
		वापस ret;
	पूर्ण

	cnl->cores.state[core_id] = SKL_DSP_RESET;

	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक cnl_get_त्रुटि_सं(काष्ठा sst_dsp *ctx)
अणु
	वापस sst_dsp_shim_पढ़ो(ctx, CNL_ADSP_ERROR_CODE);
पूर्ण

अटल स्थिर काष्ठा skl_dsp_fw_ops cnl_fw_ops = अणु
	.set_state_D0 = cnl_set_dsp_D0,
	.set_state_D3 = cnl_set_dsp_D3,
	.load_fw = cnl_load_base_firmware,
	.get_fw_errcode = cnl_get_त्रुटि_सं,
पूर्ण;

अटल काष्ठा sst_ops cnl_ops = अणु
	.irq_handler = cnl_dsp_sst_पूर्णांकerrupt,
	.ग_लिखो = sst_shim32_ग_लिखो,
	.पढ़ो = sst_shim32_पढ़ो,
	.मुक्त = cnl_dsp_मुक्त,
पूर्ण;

#घोषणा CNL_IPC_GLB_NOTIFY_RSP_SHIFT	29
#घोषणा CNL_IPC_GLB_NOTIFY_RSP_MASK	0x1
#घोषणा CNL_IPC_GLB_NOTIFY_RSP_TYPE(x)	(((x) >> CNL_IPC_GLB_NOTIFY_RSP_SHIFT) \
					& CNL_IPC_GLB_NOTIFY_RSP_MASK)

अटल irqवापस_t cnl_dsp_irq_thपढ़ो_handler(पूर्णांक irq, व्योम *context)
अणु
	काष्ठा sst_dsp *dsp = context;
	काष्ठा skl_dev *cnl = dsp->thपढ़ो_context;
	काष्ठा sst_generic_ipc *ipc = &cnl->ipc;
	काष्ठा skl_ipc_header header = अणु0पूर्ण;
	u32 hipcida, hipctdr, hipctdd;
	पूर्णांक ipc_irq = 0;

	/* here we handle ipc पूर्णांकerrupts only */
	अगर (!(dsp->पूर्णांकr_status & CNL_ADSPIS_IPC))
		वापस IRQ_NONE;

	hipcida = sst_dsp_shim_पढ़ो_unlocked(dsp, CNL_ADSP_REG_HIPCIDA);
	hipctdr = sst_dsp_shim_पढ़ो_unlocked(dsp, CNL_ADSP_REG_HIPCTDR);
	hipctdd = sst_dsp_shim_पढ़ो_unlocked(dsp, CNL_ADSP_REG_HIPCTDD);

	/* reply message from dsp */
	अगर (hipcida & CNL_ADSP_REG_HIPCIDA_DONE) अणु
		sst_dsp_shim_update_bits(dsp, CNL_ADSP_REG_HIPCCTL,
			CNL_ADSP_REG_HIPCCTL_DONE, 0);

		/* clear करोne bit - tell dsp operation is complete */
		sst_dsp_shim_update_bits_क्रमced(dsp, CNL_ADSP_REG_HIPCIDA,
			CNL_ADSP_REG_HIPCIDA_DONE, CNL_ADSP_REG_HIPCIDA_DONE);

		ipc_irq = 1;

		/* unmask करोne पूर्णांकerrupt */
		sst_dsp_shim_update_bits(dsp, CNL_ADSP_REG_HIPCCTL,
			CNL_ADSP_REG_HIPCCTL_DONE, CNL_ADSP_REG_HIPCCTL_DONE);
	पूर्ण

	/* new message from dsp */
	अगर (hipctdr & CNL_ADSP_REG_HIPCTDR_BUSY) अणु
		header.primary = hipctdr;
		header.extension = hipctdd;
		dev_dbg(dsp->dev, "IPC irq: Firmware respond primary:%x",
						header.primary);
		dev_dbg(dsp->dev, "IPC irq: Firmware respond extension:%x",
						header.extension);

		अगर (CNL_IPC_GLB_NOTIFY_RSP_TYPE(header.primary)) अणु
			/* Handle Immediate reply from DSP Core */
			skl_ipc_process_reply(ipc, header);
		पूर्ण अन्यथा अणु
			dev_dbg(dsp->dev, "IPC irq: Notification from firmware\n");
			skl_ipc_process_notअगरication(ipc, header);
		पूर्ण
		/* clear busy पूर्णांकerrupt */
		sst_dsp_shim_update_bits_क्रमced(dsp, CNL_ADSP_REG_HIPCTDR,
			CNL_ADSP_REG_HIPCTDR_BUSY, CNL_ADSP_REG_HIPCTDR_BUSY);

		/* set करोne bit to ack dsp */
		sst_dsp_shim_update_bits_क्रमced(dsp, CNL_ADSP_REG_HIPCTDA,
			CNL_ADSP_REG_HIPCTDA_DONE, CNL_ADSP_REG_HIPCTDA_DONE);
		ipc_irq = 1;
	पूर्ण

	अगर (ipc_irq == 0)
		वापस IRQ_NONE;

	cnl_ipc_पूर्णांक_enable(dsp);

	/* जारी to send any reमुख्यing messages */
	schedule_work(&ipc->kwork);

	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा sst_dsp_device cnl_dev = अणु
	.thपढ़ो = cnl_dsp_irq_thपढ़ो_handler,
	.ops = &cnl_ops,
पूर्ण;

अटल व्योम cnl_ipc_tx_msg(काष्ठा sst_generic_ipc *ipc, काष्ठा ipc_message *msg)
अणु
	काष्ठा skl_ipc_header *header = (काष्ठा skl_ipc_header *)(&msg->tx.header);

	अगर (msg->tx.size)
		sst_dsp_outbox_ग_लिखो(ipc->dsp, msg->tx.data, msg->tx.size);
	sst_dsp_shim_ग_लिखो_unlocked(ipc->dsp, CNL_ADSP_REG_HIPCIDD,
				    header->extension);
	sst_dsp_shim_ग_लिखो_unlocked(ipc->dsp, CNL_ADSP_REG_HIPCIDR,
				header->primary | CNL_ADSP_REG_HIPCIDR_BUSY);
पूर्ण

अटल bool cnl_ipc_is_dsp_busy(काष्ठा sst_dsp *dsp)
अणु
	u32 hipcidr;

	hipcidr = sst_dsp_shim_पढ़ो_unlocked(dsp, CNL_ADSP_REG_HIPCIDR);

	वापस (hipcidr & CNL_ADSP_REG_HIPCIDR_BUSY);
पूर्ण

अटल पूर्णांक cnl_ipc_init(काष्ठा device *dev, काष्ठा skl_dev *cnl)
अणु
	काष्ठा sst_generic_ipc *ipc;
	पूर्णांक err;

	ipc = &cnl->ipc;
	ipc->dsp = cnl->dsp;
	ipc->dev = dev;

	ipc->tx_data_max_size = CNL_ADSP_W1_SZ;
	ipc->rx_data_max_size = CNL_ADSP_W0_UP_SZ;

	err = sst_ipc_init(ipc);
	अगर (err)
		वापस err;

	/*
	 * overriding tx_msg and is_dsp_busy since
	 * ipc रेजिस्टरs are dअगरferent क्रम cnl
	 */
	ipc->ops.tx_msg = cnl_ipc_tx_msg;
	ipc->ops.tx_data_copy = skl_ipc_tx_data_copy;
	ipc->ops.is_dsp_busy = cnl_ipc_is_dsp_busy;

	वापस 0;
पूर्ण

पूर्णांक cnl_sst_dsp_init(काष्ठा device *dev, व्योम __iomem *mmio_base, पूर्णांक irq,
		     स्थिर अक्षर *fw_name, काष्ठा skl_dsp_loader_ops dsp_ops,
		     काष्ठा skl_dev **dsp)
अणु
	काष्ठा skl_dev *cnl;
	काष्ठा sst_dsp *sst;
	पूर्णांक ret;

	ret = skl_sst_ctx_init(dev, irq, fw_name, dsp_ops, dsp, &cnl_dev);
	अगर (ret < 0) अणु
		dev_err(dev, "%s: no device\n", __func__);
		वापस ret;
	पूर्ण

	cnl = *dsp;
	sst = cnl->dsp;
	sst->fw_ops = cnl_fw_ops;
	sst->addr.lpe = mmio_base;
	sst->addr.shim = mmio_base;
	sst->addr.sram0_base = CNL_ADSP_SRAM0_BASE;
	sst->addr.sram1_base = CNL_ADSP_SRAM1_BASE;
	sst->addr.w0_stat_sz = CNL_ADSP_W0_STAT_SZ;
	sst->addr.w0_up_sz = CNL_ADSP_W0_UP_SZ;

	sst_dsp_mailbox_init(sst, (CNL_ADSP_SRAM0_BASE + CNL_ADSP_W0_STAT_SZ),
			     CNL_ADSP_W0_UP_SZ, CNL_ADSP_SRAM1_BASE,
			     CNL_ADSP_W1_SZ);

	ret = cnl_ipc_init(dev, cnl);
	अगर (ret) अणु
		skl_dsp_मुक्त(sst);
		वापस ret;
	पूर्ण

	cnl->boot_complete = false;
	init_रुकोqueue_head(&cnl->boot_रुको);

	वापस skl_dsp_acquire_irq(sst);
पूर्ण
EXPORT_SYMBOL_GPL(cnl_sst_dsp_init);

पूर्णांक cnl_sst_init_fw(काष्ठा device *dev, काष्ठा skl_dev *skl)
अणु
	पूर्णांक ret;
	काष्ठा sst_dsp *sst = skl->dsp;

	ret = skl->dsp->fw_ops.load_fw(sst);
	अगर (ret < 0) अणु
		dev_err(dev, "load base fw failed: %d", ret);
		वापस ret;
	पूर्ण

	skl_dsp_init_core_state(sst);

	skl->is_first_boot = false;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(cnl_sst_init_fw);

व्योम cnl_sst_dsp_cleanup(काष्ठा device *dev, काष्ठा skl_dev *skl)
अणु
	अगर (skl->dsp->fw)
		release_firmware(skl->dsp->fw);

	skl_मुक्तup_uuid_list(skl);
	cnl_ipc_मुक्त(&skl->ipc);

	skl->dsp->ops->मुक्त(skl->dsp);
पूर्ण
EXPORT_SYMBOL_GPL(cnl_sst_dsp_cleanup);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Intel Cannonlake IPC driver");
