<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  bxt-sst.c - DSP library functions क्रम BXT platक्रमm
 *
 *  Copyright (C) 2015-16 Intel Corp
 *  Author:Rafal Redzimski <rafal.f.redzimski@पूर्णांकel.com>
 *	   Jeeja KP <jeeja.kp@पूर्णांकel.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/firmware.h>
#समावेश <linux/device.h>

#समावेश "../common/sst-dsp.h"
#समावेश "../common/sst-dsp-priv.h"
#समावेश "skl.h"

#घोषणा BXT_BASEFW_TIMEOUT	3000
#घोषणा BXT_ROM_INIT_TIMEOUT	70
#घोषणा BXT_IPC_PURGE_FW	0x01004000

#घोषणा BXT_ROM_INIT		0x5
#घोषणा BXT_ADSP_SRAM0_BASE	0x80000

/* Firmware status winकरोw */
#घोषणा BXT_ADSP_FW_STATUS	BXT_ADSP_SRAM0_BASE
#घोषणा BXT_ADSP_ERROR_CODE     (BXT_ADSP_FW_STATUS + 0x4)

#घोषणा BXT_ADSP_SRAM1_BASE	0xA0000

#घोषणा BXT_INSTANCE_ID 0
#घोषणा BXT_BASE_FW_MODULE_ID 0

#घोषणा BXT_ADSP_FW_BIN_HDR_OFFSET 0x2000

/* Delay beक्रमe scheduling D0i3 entry */
#घोषणा BXT_D0I3_DELAY 5000

अटल अचिन्हित पूर्णांक bxt_get_errorcode(काष्ठा sst_dsp *ctx)
अणु
	 वापस sst_dsp_shim_पढ़ो(ctx, BXT_ADSP_ERROR_CODE);
पूर्ण

अटल पूर्णांक
bxt_load_library(काष्ठा sst_dsp *ctx, काष्ठा skl_lib_info *linfo, पूर्णांक lib_count)
अणु
	काष्ठा snd_dma_buffer dmab;
	काष्ठा skl_dev *skl = ctx->thपढ़ो_context;
	काष्ठा firmware stripped_fw;
	पूर्णांक ret = 0, i, dma_id, stream_tag;

	/* library indices start from 1 to N. 0 represents base FW */
	क्रम (i = 1; i < lib_count; i++) अणु
		ret = skl_prepare_lib_load(skl, &skl->lib_info[i], &stripped_fw,
					BXT_ADSP_FW_BIN_HDR_OFFSET, i);
		अगर (ret < 0)
			जाओ load_library_failed;

		stream_tag = ctx->dsp_ops.prepare(ctx->dev, 0x40,
					stripped_fw.size, &dmab);
		अगर (stream_tag <= 0) अणु
			dev_err(ctx->dev, "Lib prepare DMA err: %x\n",
					stream_tag);
			ret = stream_tag;
			जाओ load_library_failed;
		पूर्ण

		dma_id = stream_tag - 1;
		स_नकल(dmab.area, stripped_fw.data, stripped_fw.size);

		ctx->dsp_ops.trigger(ctx->dev, true, stream_tag);
		ret = skl_sst_ipc_load_library(&skl->ipc, dma_id, i, true);
		अगर (ret < 0)
			dev_err(ctx->dev, "IPC Load Lib for %s fail: %d\n",
					linfo[i].name, ret);

		ctx->dsp_ops.trigger(ctx->dev, false, stream_tag);
		ctx->dsp_ops.cleanup(ctx->dev, &dmab, stream_tag);
	पूर्ण

	वापस ret;

load_library_failed:
	skl_release_library(linfo, lib_count);
	वापस ret;
पूर्ण

/*
 * First boot sequence has some extra steps. Core 0 रुकोs क्रम घातer
 * status on core 1, so घातer up core 1 also momentarily, keep it in
 * reset/stall and then turn it off
 */
अटल पूर्णांक sst_bxt_prepare_fw(काष्ठा sst_dsp *ctx,
			स्थिर व्योम *fwdata, u32 fwsize)
अणु
	पूर्णांक stream_tag, ret;

	stream_tag = ctx->dsp_ops.prepare(ctx->dev, 0x40, fwsize, &ctx->dmab);
	अगर (stream_tag <= 0) अणु
		dev_err(ctx->dev, "Failed to prepare DMA FW loading err: %x\n",
				stream_tag);
		वापस stream_tag;
	पूर्ण

	ctx->dsp_ops.stream_tag = stream_tag;
	स_नकल(ctx->dmab.area, fwdata, fwsize);

	/* Step 1: Power up core 0 and core1 */
	ret = skl_dsp_core_घातer_up(ctx, SKL_DSP_CORE0_MASK |
				SKL_DSP_CORE_MASK(1));
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "dsp core0/1 power up failed\n");
		जाओ base_fw_load_failed;
	पूर्ण

	/* Step 2: Purge FW request */
	sst_dsp_shim_ग_लिखो(ctx, SKL_ADSP_REG_HIPCI, SKL_ADSP_REG_HIPCI_BUSY |
				(BXT_IPC_PURGE_FW | ((stream_tag - 1) << 9)));

	/* Step 3: Unset core0 reset state & unstall/run core0 */
	ret = skl_dsp_start_core(ctx, SKL_DSP_CORE0_MASK);
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "Start dsp core failed ret: %d\n", ret);
		ret = -EIO;
		जाओ base_fw_load_failed;
	पूर्ण

	/* Step 4: Wait क्रम DONE Bit */
	ret = sst_dsp_रेजिस्टर_poll(ctx, SKL_ADSP_REG_HIPCIE,
					SKL_ADSP_REG_HIPCIE_DONE,
					SKL_ADSP_REG_HIPCIE_DONE,
					BXT_INIT_TIMEOUT, "HIPCIE Done");
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "Timeout for Purge Request%d\n", ret);
		जाओ base_fw_load_failed;
	पूर्ण

	/* Step 5: घातer करोwn core1 */
	ret = skl_dsp_core_घातer_करोwn(ctx, SKL_DSP_CORE_MASK(1));
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "dsp core1 power down failed\n");
		जाओ base_fw_load_failed;
	पूर्ण

	/* Step 6: Enable Interrupt */
	skl_ipc_पूर्णांक_enable(ctx);
	skl_ipc_op_पूर्णांक_enable(ctx);

	/* Step 7: Wait क्रम ROM init */
	ret = sst_dsp_रेजिस्टर_poll(ctx, BXT_ADSP_FW_STATUS, SKL_FW_STS_MASK,
			SKL_FW_INIT, BXT_ROM_INIT_TIMEOUT, "ROM Load");
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "Timeout for ROM init, ret:%d\n", ret);
		जाओ base_fw_load_failed;
	पूर्ण

	वापस ret;

base_fw_load_failed:
	ctx->dsp_ops.cleanup(ctx->dev, &ctx->dmab, stream_tag);
	skl_dsp_core_घातer_करोwn(ctx, SKL_DSP_CORE_MASK(1));
	skl_dsp_disable_core(ctx, SKL_DSP_CORE0_MASK);
	वापस ret;
पूर्ण

अटल पूर्णांक sst_transfer_fw_host_dma(काष्ठा sst_dsp *ctx)
अणु
	पूर्णांक ret;

	ctx->dsp_ops.trigger(ctx->dev, true, ctx->dsp_ops.stream_tag);
	ret = sst_dsp_रेजिस्टर_poll(ctx, BXT_ADSP_FW_STATUS, SKL_FW_STS_MASK,
			BXT_ROM_INIT, BXT_BASEFW_TIMEOUT, "Firmware boot");

	ctx->dsp_ops.trigger(ctx->dev, false, ctx->dsp_ops.stream_tag);
	ctx->dsp_ops.cleanup(ctx->dev, &ctx->dmab, ctx->dsp_ops.stream_tag);

	वापस ret;
पूर्ण

अटल पूर्णांक bxt_load_base_firmware(काष्ठा sst_dsp *ctx)
अणु
	काष्ठा firmware stripped_fw;
	काष्ठा skl_dev *skl = ctx->thपढ़ो_context;
	पूर्णांक ret, i;

	अगर (ctx->fw == शून्य) अणु
		ret = request_firmware(&ctx->fw, ctx->fw_name, ctx->dev);
		अगर (ret < 0) अणु
			dev_err(ctx->dev, "Request firmware failed %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	/* prase uuids on first boot */
	अगर (skl->is_first_boot) अणु
		ret = snd_skl_parse_uuids(ctx, ctx->fw, BXT_ADSP_FW_BIN_HDR_OFFSET, 0);
		अगर (ret < 0)
			जाओ sst_load_base_firmware_failed;
	पूर्ण

	stripped_fw.data = ctx->fw->data;
	stripped_fw.size = ctx->fw->size;
	skl_dsp_strip_extended_manअगरest(&stripped_fw);


	क्रम (i = 0; i < BXT_FW_ROM_INIT_RETRY; i++) अणु
		ret = sst_bxt_prepare_fw(ctx, stripped_fw.data, stripped_fw.size);
		अगर (ret == 0)
			अवरोध;
	पूर्ण

	अगर (ret < 0) अणु
		dev_err(ctx->dev, "Error code=0x%x: FW status=0x%x\n",
			sst_dsp_shim_पढ़ो(ctx, BXT_ADSP_ERROR_CODE),
			sst_dsp_shim_पढ़ो(ctx, BXT_ADSP_FW_STATUS));

		dev_err(ctx->dev, "Core En/ROM load fail:%d\n", ret);
		जाओ sst_load_base_firmware_failed;
	पूर्ण

	ret = sst_transfer_fw_host_dma(ctx);
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "Transfer firmware failed %d\n", ret);
		dev_info(ctx->dev, "Error code=0x%x: FW status=0x%x\n",
			sst_dsp_shim_पढ़ो(ctx, BXT_ADSP_ERROR_CODE),
			sst_dsp_shim_पढ़ो(ctx, BXT_ADSP_FW_STATUS));

		skl_dsp_disable_core(ctx, SKL_DSP_CORE0_MASK);
	पूर्ण अन्यथा अणु
		dev_dbg(ctx->dev, "Firmware download successful\n");
		ret = रुको_event_समयout(skl->boot_रुको, skl->boot_complete,
					msecs_to_jअगरfies(SKL_IPC_BOOT_MSECS));
		अगर (ret == 0) अणु
			dev_err(ctx->dev, "DSP boot fail, FW Ready timeout\n");
			skl_dsp_disable_core(ctx, SKL_DSP_CORE0_MASK);
			ret = -EIO;
		पूर्ण अन्यथा अणु
			ret = 0;
			skl->fw_loaded = true;
		पूर्ण
	पूर्ण

	वापस ret;

sst_load_base_firmware_failed:
	release_firmware(ctx->fw);
	ctx->fw = शून्य;
	वापस ret;
पूर्ण

/*
 * Decide the D0i3 state that can be targeted based on the useहाल
 * ref counts and DSP state
 *
 * Decision Matrix:  (X= करोnt care; state = target state)
 *
 * DSP state != SKL_DSP_RUNNING ; state = no d0i3
 *
 * DSP state == SKL_DSP_RUNNING , the following matrix applies
 * non_d0i3 >0; streaming =X; non_streaming =X; state = no d0i3
 * non_d0i3 =X; streaming =0; non_streaming =0; state = no d0i3
 * non_d0i3 =0; streaming >0; non_streaming =X; state = streaming d0i3
 * non_d0i3 =0; streaming =0; non_streaming =X; state = non-streaming d0i3
 */
अटल पूर्णांक bxt_d0i3_target_state(काष्ठा sst_dsp *ctx)
अणु
	काष्ठा skl_dev *skl = ctx->thपढ़ो_context;
	काष्ठा skl_d0i3_data *d0i3 = &skl->d0i3;

	अगर (skl->cores.state[SKL_DSP_CORE0_ID] != SKL_DSP_RUNNING)
		वापस SKL_DSP_D0I3_NONE;

	अगर (d0i3->non_d0i3)
		वापस SKL_DSP_D0I3_NONE;
	अन्यथा अगर (d0i3->streaming)
		वापस SKL_DSP_D0I3_STREAMING;
	अन्यथा अगर (d0i3->non_streaming)
		वापस SKL_DSP_D0I3_NON_STREAMING;
	अन्यथा
		वापस SKL_DSP_D0I3_NONE;
पूर्ण

अटल व्योम bxt_set_dsp_D0i3(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक ret;
	काष्ठा skl_ipc_d0ix_msg msg;
	काष्ठा skl_dev *skl = container_of(work,
			काष्ठा skl_dev, d0i3.work.work);
	काष्ठा sst_dsp *ctx = skl->dsp;
	काष्ठा skl_d0i3_data *d0i3 = &skl->d0i3;
	पूर्णांक target_state;

	dev_dbg(ctx->dev, "In %s:\n", __func__);

	/* D0i3 entry allowed only अगर core 0 alone is running */
	अगर (skl_dsp_get_enabled_cores(ctx) !=  SKL_DSP_CORE0_MASK) अणु
		dev_warn(ctx->dev,
				"D0i3 allowed when only core0 running:Exit\n");
		वापस;
	पूर्ण

	target_state = bxt_d0i3_target_state(ctx);
	अगर (target_state == SKL_DSP_D0I3_NONE)
		वापस;

	msg.instance_id = 0;
	msg.module_id = 0;
	msg.wake = 1;
	msg.streaming = 0;
	अगर (target_state == SKL_DSP_D0I3_STREAMING)
		msg.streaming = 1;

	ret =  skl_ipc_set_d0ix(&skl->ipc, &msg);

	अगर (ret < 0) अणु
		dev_err(ctx->dev, "Failed to set DSP to D0i3 state\n");
		वापस;
	पूर्ण

	/* Set Venकरोr specअगरic रेजिस्टर D0I3C.I3 to enable D0i3*/
	अगर (skl->update_d0i3c)
		skl->update_d0i3c(skl->dev, true);

	d0i3->state = target_state;
	skl->cores.state[SKL_DSP_CORE0_ID] = SKL_DSP_RUNNING_D0I3;
पूर्ण

अटल पूर्णांक bxt_schedule_dsp_D0i3(काष्ठा sst_dsp *ctx)
अणु
	काष्ठा skl_dev *skl = ctx->thपढ़ो_context;
	काष्ठा skl_d0i3_data *d0i3 = &skl->d0i3;

	/* Schedule D0i3 only अगर the useहाल ref counts are appropriate */
	अगर (bxt_d0i3_target_state(ctx) != SKL_DSP_D0I3_NONE) अणु

		dev_dbg(ctx->dev, "%s: Schedule D0i3\n", __func__);

		schedule_delayed_work(&d0i3->work,
				msecs_to_jअगरfies(BXT_D0I3_DELAY));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bxt_set_dsp_D0i0(काष्ठा sst_dsp *ctx)
अणु
	पूर्णांक ret;
	काष्ठा skl_ipc_d0ix_msg msg;
	काष्ठा skl_dev *skl = ctx->thपढ़ो_context;

	dev_dbg(ctx->dev, "In %s:\n", __func__);

	/* First Cancel any pending attempt to put DSP to D0i3 */
	cancel_delayed_work_sync(&skl->d0i3.work);

	/* If DSP is currently in D0i3, bring it to D0i0 */
	अगर (skl->cores.state[SKL_DSP_CORE0_ID] != SKL_DSP_RUNNING_D0I3)
		वापस 0;

	dev_dbg(ctx->dev, "Set DSP to D0i0\n");

	msg.instance_id = 0;
	msg.module_id = 0;
	msg.streaming = 0;
	msg.wake = 0;

	अगर (skl->d0i3.state == SKL_DSP_D0I3_STREAMING)
		msg.streaming = 1;

	/* Clear Venकरोr specअगरic रेजिस्टर D0I3C.I3 to disable D0i3*/
	अगर (skl->update_d0i3c)
		skl->update_d0i3c(skl->dev, false);

	ret =  skl_ipc_set_d0ix(&skl->ipc, &msg);
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "Failed to set DSP to D0i0\n");
		वापस ret;
	पूर्ण

	skl->cores.state[SKL_DSP_CORE0_ID] = SKL_DSP_RUNNING;
	skl->d0i3.state = SKL_DSP_D0I3_NONE;

	वापस 0;
पूर्ण

अटल पूर्णांक bxt_set_dsp_D0(काष्ठा sst_dsp *ctx, अचिन्हित पूर्णांक core_id)
अणु
	काष्ठा skl_dev *skl = ctx->thपढ़ो_context;
	पूर्णांक ret;
	काष्ठा skl_ipc_dxstate_info dx;
	अचिन्हित पूर्णांक core_mask = SKL_DSP_CORE_MASK(core_id);

	अगर (skl->fw_loaded == false) अणु
		skl->boot_complete = false;
		ret = bxt_load_base_firmware(ctx);
		अगर (ret < 0) अणु
			dev_err(ctx->dev, "reload fw failed: %d\n", ret);
			वापस ret;
		पूर्ण

		अगर (skl->lib_count > 1) अणु
			ret = bxt_load_library(ctx, skl->lib_info,
						skl->lib_count);
			अगर (ret < 0) अणु
				dev_err(ctx->dev, "reload libs failed: %d\n", ret);
				वापस ret;
			पूर्ण
		पूर्ण
		skl->cores.state[core_id] = SKL_DSP_RUNNING;
		वापस ret;
	पूर्ण

	/* If core 0 is being turned on, turn on core 1 as well */
	अगर (core_id == SKL_DSP_CORE0_ID)
		ret = skl_dsp_core_घातer_up(ctx, core_mask |
				SKL_DSP_CORE_MASK(1));
	अन्यथा
		ret = skl_dsp_core_घातer_up(ctx, core_mask);

	अगर (ret < 0)
		जाओ err;

	अगर (core_id == SKL_DSP_CORE0_ID) अणु

		/*
		 * Enable पूर्णांकerrupt after SPA is set and beक्रमe
		 * DSP is unstalled
		 */
		skl_ipc_पूर्णांक_enable(ctx);
		skl_ipc_op_पूर्णांक_enable(ctx);
		skl->boot_complete = false;
	पूर्ण

	ret = skl_dsp_start_core(ctx, core_mask);
	अगर (ret < 0)
		जाओ err;

	अगर (core_id == SKL_DSP_CORE0_ID) अणु
		ret = रुको_event_समयout(skl->boot_रुको,
				skl->boot_complete,
				msecs_to_jअगरfies(SKL_IPC_BOOT_MSECS));

	/* If core 1 was turned on क्रम booting core 0, turn it off */
		skl_dsp_core_घातer_करोwn(ctx, SKL_DSP_CORE_MASK(1));
		अगर (ret == 0) अणु
			dev_err(ctx->dev, "%s: DSP boot timeout\n", __func__);
			dev_err(ctx->dev, "Error code=0x%x: FW status=0x%x\n",
				sst_dsp_shim_पढ़ो(ctx, BXT_ADSP_ERROR_CODE),
				sst_dsp_shim_पढ़ो(ctx, BXT_ADSP_FW_STATUS));
			dev_err(ctx->dev, "Failed to set core0 to D0 state\n");
			ret = -EIO;
			जाओ err;
		पूर्ण
	पूर्ण

	/* Tell FW अगर additional core in now On */

	अगर (core_id != SKL_DSP_CORE0_ID) अणु
		dx.core_mask = core_mask;
		dx.dx_mask = core_mask;

		ret = skl_ipc_set_dx(&skl->ipc, BXT_INSTANCE_ID,
					BXT_BASE_FW_MODULE_ID, &dx);
		अगर (ret < 0) अणु
			dev_err(ctx->dev, "IPC set_dx for core %d fail: %d\n",
								core_id, ret);
			जाओ err;
		पूर्ण
	पूर्ण

	skl->cores.state[core_id] = SKL_DSP_RUNNING;
	वापस 0;
err:
	अगर (core_id == SKL_DSP_CORE0_ID)
		core_mask |= SKL_DSP_CORE_MASK(1);
	skl_dsp_disable_core(ctx, core_mask);

	वापस ret;
पूर्ण

अटल पूर्णांक bxt_set_dsp_D3(काष्ठा sst_dsp *ctx, अचिन्हित पूर्णांक core_id)
अणु
	पूर्णांक ret;
	काष्ठा skl_ipc_dxstate_info dx;
	काष्ठा skl_dev *skl = ctx->thपढ़ो_context;
	अचिन्हित पूर्णांक core_mask = SKL_DSP_CORE_MASK(core_id);

	dx.core_mask = core_mask;
	dx.dx_mask = SKL_IPC_D3_MASK;

	dev_dbg(ctx->dev, "core mask=%x dx_mask=%x\n",
			dx.core_mask, dx.dx_mask);

	ret = skl_ipc_set_dx(&skl->ipc, BXT_INSTANCE_ID,
				BXT_BASE_FW_MODULE_ID, &dx);
	अगर (ret < 0) अणु
		dev_err(ctx->dev,
		"Failed to set DSP to D3:core id = %d;Continue reset\n",
		core_id);
		/*
		 * In हाल of D3 failure, re-करोwnload the firmware, so set
		 * fw_loaded to false.
		 */
		skl->fw_loaded = false;
	पूर्ण

	अगर (core_id == SKL_DSP_CORE0_ID) अणु
		/* disable Interrupt */
		skl_ipc_op_पूर्णांक_disable(ctx);
		skl_ipc_पूर्णांक_disable(ctx);
	पूर्ण
	ret = skl_dsp_disable_core(ctx, core_mask);
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "Failed to disable core %d\n", ret);
		वापस ret;
	पूर्ण
	skl->cores.state[core_id] = SKL_DSP_RESET;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा skl_dsp_fw_ops bxt_fw_ops = अणु
	.set_state_D0 = bxt_set_dsp_D0,
	.set_state_D3 = bxt_set_dsp_D3,
	.set_state_D0i3 = bxt_schedule_dsp_D0i3,
	.set_state_D0i0 = bxt_set_dsp_D0i0,
	.load_fw = bxt_load_base_firmware,
	.get_fw_errcode = bxt_get_errorcode,
	.load_library = bxt_load_library,
पूर्ण;

अटल काष्ठा sst_ops skl_ops = अणु
	.irq_handler = skl_dsp_sst_पूर्णांकerrupt,
	.ग_लिखो = sst_shim32_ग_लिखो,
	.पढ़ो = sst_shim32_पढ़ो,
	.मुक्त = skl_dsp_मुक्त,
पूर्ण;

अटल काष्ठा sst_dsp_device skl_dev = अणु
	.thपढ़ो = skl_dsp_irq_thपढ़ो_handler,
	.ops = &skl_ops,
पूर्ण;

पूर्णांक bxt_sst_dsp_init(काष्ठा device *dev, व्योम __iomem *mmio_base, पूर्णांक irq,
			स्थिर अक्षर *fw_name, काष्ठा skl_dsp_loader_ops dsp_ops,
			काष्ठा skl_dev **dsp)
अणु
	काष्ठा skl_dev *skl;
	काष्ठा sst_dsp *sst;
	पूर्णांक ret;

	ret = skl_sst_ctx_init(dev, irq, fw_name, dsp_ops, dsp, &skl_dev);
	अगर (ret < 0) अणु
		dev_err(dev, "%s: no device\n", __func__);
		वापस ret;
	पूर्ण

	skl = *dsp;
	sst = skl->dsp;
	sst->fw_ops = bxt_fw_ops;
	sst->addr.lpe = mmio_base;
	sst->addr.shim = mmio_base;
	sst->addr.sram0_base = BXT_ADSP_SRAM0_BASE;
	sst->addr.sram1_base = BXT_ADSP_SRAM1_BASE;
	sst->addr.w0_stat_sz = SKL_ADSP_W0_STAT_SZ;
	sst->addr.w0_up_sz = SKL_ADSP_W0_UP_SZ;

	sst_dsp_mailbox_init(sst, (BXT_ADSP_SRAM0_BASE + SKL_ADSP_W0_STAT_SZ),
			SKL_ADSP_W0_UP_SZ, BXT_ADSP_SRAM1_BASE, SKL_ADSP_W1_SZ);

	ret = skl_ipc_init(dev, skl);
	अगर (ret) अणु
		skl_dsp_मुक्त(sst);
		वापस ret;
	पूर्ण

	/* set the D0i3 check */
	skl->ipc.ops.check_dsp_lp_on = skl_ipc_check_D0i0;

	skl->boot_complete = false;
	init_रुकोqueue_head(&skl->boot_रुको);
	INIT_DELAYED_WORK(&skl->d0i3.work, bxt_set_dsp_D0i3);
	skl->d0i3.state = SKL_DSP_D0I3_NONE;

	वापस skl_dsp_acquire_irq(sst);
पूर्ण
EXPORT_SYMBOL_GPL(bxt_sst_dsp_init);

पूर्णांक bxt_sst_init_fw(काष्ठा device *dev, काष्ठा skl_dev *skl)
अणु
	पूर्णांक ret;
	काष्ठा sst_dsp *sst = skl->dsp;

	ret = sst->fw_ops.load_fw(sst);
	अगर (ret < 0) अणु
		dev_err(dev, "Load base fw failed: %x\n", ret);
		वापस ret;
	पूर्ण

	skl_dsp_init_core_state(sst);

	अगर (skl->lib_count > 1) अणु
		ret = sst->fw_ops.load_library(sst, skl->lib_info,
						skl->lib_count);
		अगर (ret < 0) अणु
			dev_err(dev, "Load Library failed : %x\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण
	skl->is_first_boot = false;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(bxt_sst_init_fw);

व्योम bxt_sst_dsp_cleanup(काष्ठा device *dev, काष्ठा skl_dev *skl)
अणु

	skl_release_library(skl->lib_info, skl->lib_count);
	अगर (skl->dsp->fw)
		release_firmware(skl->dsp->fw);
	skl_मुक्तup_uuid_list(skl);
	skl_ipc_मुक्त(&skl->ipc);
	skl->dsp->ops->मुक्त(skl->dsp);
पूर्ण
EXPORT_SYMBOL_GPL(bxt_sst_dsp_cleanup);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Intel Broxton IPC driver");
