<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * skl-sst.c - HDA DSP library functions क्रम SKL platक्रमm
 *
 * Copyright (C) 2014-15, Intel Corporation.
 * Author:Rafal Redzimski <rafal.f.redzimski@पूर्णांकel.com>
 *	Jeeja KP <jeeja.kp@पूर्णांकel.com>
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/uuid.h>
#समावेश "../common/sst-dsp.h"
#समावेश "../common/sst-dsp-priv.h"
#समावेश "../common/sst-ipc.h"
#समावेश "skl.h"

#घोषणा SKL_BASEFW_TIMEOUT	300
#घोषणा SKL_INIT_TIMEOUT	1000

/* Intel HD Audio SRAM Winकरोw 0*/
#घोषणा SKL_ADSP_SRAM0_BASE	0x8000

/* Firmware status winकरोw */
#घोषणा SKL_ADSP_FW_STATUS	SKL_ADSP_SRAM0_BASE
#घोषणा SKL_ADSP_ERROR_CODE	(SKL_ADSP_FW_STATUS + 0x4)

#घोषणा SKL_NUM_MODULES		1

अटल bool skl_check_fw_status(काष्ठा sst_dsp *ctx, u32 status)
अणु
	u32 cur_sts;

	cur_sts = sst_dsp_shim_पढ़ो(ctx, SKL_ADSP_FW_STATUS) & SKL_FW_STS_MASK;

	वापस (cur_sts == status);
पूर्ण

अटल पूर्णांक skl_transfer_firmware(काष्ठा sst_dsp *ctx,
		स्थिर व्योम *basefw, u32 base_fw_size)
अणु
	पूर्णांक ret = 0;

	ret = ctx->cl_dev.ops.cl_copy_to_dmabuf(ctx, basefw, base_fw_size,
								true);
	अगर (ret < 0)
		वापस ret;

	ret = sst_dsp_रेजिस्टर_poll(ctx,
			SKL_ADSP_FW_STATUS,
			SKL_FW_STS_MASK,
			SKL_FW_RFW_START,
			SKL_BASEFW_TIMEOUT,
			"Firmware boot");

	ctx->cl_dev.ops.cl_stop_dma(ctx);

	वापस ret;
पूर्ण

#घोषणा SKL_ADSP_FW_BIN_HDR_OFFSET 0x284

अटल पूर्णांक skl_load_base_firmware(काष्ठा sst_dsp *ctx)
अणु
	पूर्णांक ret = 0, i;
	काष्ठा skl_dev *skl = ctx->thपढ़ो_context;
	काष्ठा firmware stripped_fw;
	u32 reg;

	skl->boot_complete = false;
	init_रुकोqueue_head(&skl->boot_रुको);

	अगर (ctx->fw == शून्य) अणु
		ret = request_firmware(&ctx->fw, ctx->fw_name, ctx->dev);
		अगर (ret < 0) अणु
			dev_err(ctx->dev, "Request firmware failed %d\n", ret);
			वापस -EIO;
		पूर्ण
	पूर्ण

	/* prase uuids on first boot */
	अगर (skl->is_first_boot) अणु
		ret = snd_skl_parse_uuids(ctx, ctx->fw, SKL_ADSP_FW_BIN_HDR_OFFSET, 0);
		अगर (ret < 0) अणु
			dev_err(ctx->dev, "UUID parsing err: %d\n", ret);
			release_firmware(ctx->fw);
			skl_dsp_disable_core(ctx, SKL_DSP_CORE0_MASK);
			वापस ret;
		पूर्ण
	पूर्ण

	/* check क्रम extended manअगरest */
	stripped_fw.data = ctx->fw->data;
	stripped_fw.size = ctx->fw->size;

	skl_dsp_strip_extended_manअगरest(&stripped_fw);

	ret = skl_dsp_boot(ctx);
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "Boot dsp core failed ret: %d\n", ret);
		जाओ skl_load_base_firmware_failed;
	पूर्ण

	ret = skl_cldma_prepare(ctx);
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "CL dma prepare failed : %d\n", ret);
		जाओ skl_load_base_firmware_failed;
	पूर्ण

	/* enable Interrupt */
	skl_ipc_पूर्णांक_enable(ctx);
	skl_ipc_op_पूर्णांक_enable(ctx);

	/* check ROM Status */
	क्रम (i = SKL_INIT_TIMEOUT; i > 0; --i) अणु
		अगर (skl_check_fw_status(ctx, SKL_FW_INIT)) अणु
			dev_dbg(ctx->dev,
				"ROM loaded, we can continue with FW loading\n");
			अवरोध;
		पूर्ण
		mdelay(1);
	पूर्ण
	अगर (!i) अणु
		reg = sst_dsp_shim_पढ़ो(ctx, SKL_ADSP_FW_STATUS);
		dev_err(ctx->dev,
			"Timeout waiting for ROM init done, reg:0x%x\n", reg);
		ret = -EIO;
		जाओ transfer_firmware_failed;
	पूर्ण

	ret = skl_transfer_firmware(ctx, stripped_fw.data, stripped_fw.size);
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "Transfer firmware failed%d\n", ret);
		जाओ transfer_firmware_failed;
	पूर्ण अन्यथा अणु
		ret = रुको_event_समयout(skl->boot_रुको, skl->boot_complete,
					msecs_to_jअगरfies(SKL_IPC_BOOT_MSECS));
		अगर (ret == 0) अणु
			dev_err(ctx->dev, "DSP boot failed, FW Ready timed-out\n");
			ret = -EIO;
			जाओ transfer_firmware_failed;
		पूर्ण

		dev_dbg(ctx->dev, "Download firmware successful%d\n", ret);
		skl->fw_loaded = true;
	पूर्ण
	वापस 0;
transfer_firmware_failed:
	ctx->cl_dev.ops.cl_cleanup_controller(ctx);
skl_load_base_firmware_failed:
	skl_dsp_disable_core(ctx, SKL_DSP_CORE0_MASK);
	release_firmware(ctx->fw);
	ctx->fw = शून्य;
	वापस ret;
पूर्ण

अटल पूर्णांक skl_set_dsp_D0(काष्ठा sst_dsp *ctx, अचिन्हित पूर्णांक core_id)
अणु
	पूर्णांक ret;
	काष्ठा skl_ipc_dxstate_info dx;
	काष्ठा skl_dev *skl = ctx->thपढ़ो_context;
	अचिन्हित पूर्णांक core_mask = SKL_DSP_CORE_MASK(core_id);

	/* If core0 is being turned on, we need to load the FW */
	अगर (core_id == SKL_DSP_CORE0_ID) अणु
		ret = skl_load_base_firmware(ctx);
		अगर (ret < 0) अणु
			dev_err(ctx->dev, "unable to load firmware\n");
			वापस ret;
		पूर्ण

		/* load libs as they are also lost on D3 */
		अगर (skl->lib_count > 1) अणु
			ret = ctx->fw_ops.load_library(ctx, skl->lib_info,
							skl->lib_count);
			अगर (ret < 0) अणु
				dev_err(ctx->dev, "reload libs failed: %d\n",
						ret);
				वापस ret;
			पूर्ण

		पूर्ण
	पूर्ण

	/*
	 * If any core other than core 0 is being moved to D0, enable the
	 * core and send the set dx IPC क्रम the core.
	 */
	अगर (core_id != SKL_DSP_CORE0_ID) अणु
		ret = skl_dsp_enable_core(ctx, core_mask);
		अगर (ret < 0)
			वापस ret;

		dx.core_mask = core_mask;
		dx.dx_mask = core_mask;

		ret = skl_ipc_set_dx(&skl->ipc, SKL_INSTANCE_ID,
					SKL_BASE_FW_MODULE_ID, &dx);
		अगर (ret < 0) अणु
			dev_err(ctx->dev, "Failed to set dsp to D0:core id= %d\n",
					core_id);
			skl_dsp_disable_core(ctx, core_mask);
		पूर्ण
	पूर्ण

	skl->cores.state[core_id] = SKL_DSP_RUNNING;

	वापस 0;
पूर्ण

अटल पूर्णांक skl_set_dsp_D3(काष्ठा sst_dsp *ctx, अचिन्हित पूर्णांक core_id)
अणु
	पूर्णांक ret;
	काष्ठा skl_ipc_dxstate_info dx;
	काष्ठा skl_dev *skl = ctx->thपढ़ो_context;
	अचिन्हित पूर्णांक core_mask = SKL_DSP_CORE_MASK(core_id);

	dx.core_mask = core_mask;
	dx.dx_mask = SKL_IPC_D3_MASK;

	ret = skl_ipc_set_dx(&skl->ipc, SKL_INSTANCE_ID, SKL_BASE_FW_MODULE_ID, &dx);
	अगर (ret < 0)
		dev_err(ctx->dev, "set Dx core %d fail: %d\n", core_id, ret);

	अगर (core_id == SKL_DSP_CORE0_ID) अणु
		/* disable Interrupt */
		ctx->cl_dev.ops.cl_cleanup_controller(ctx);
		skl_cldma_पूर्णांक_disable(ctx);
		skl_ipc_op_पूर्णांक_disable(ctx);
		skl_ipc_पूर्णांक_disable(ctx);
	पूर्ण

	ret = skl_dsp_disable_core(ctx, core_mask);
	अगर (ret < 0)
		वापस ret;

	skl->cores.state[core_id] = SKL_DSP_RESET;
	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक skl_get_errorcode(काष्ठा sst_dsp *ctx)
अणु
	 वापस sst_dsp_shim_पढ़ो(ctx, SKL_ADSP_ERROR_CODE);
पूर्ण

/*
 * since get/set_module are called from DAPM context,
 * we करोn't need lock क्रम usage count
 */
अटल पूर्णांक skl_get_module(काष्ठा sst_dsp *ctx, u16 mod_id)
अणु
	काष्ठा skl_module_table *module;

	list_क्रम_each_entry(module, &ctx->module_list, list) अणु
		अगर (module->mod_info->mod_id == mod_id)
			वापस ++module->usage_cnt;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक skl_put_module(काष्ठा sst_dsp *ctx, u16 mod_id)
अणु
	काष्ठा skl_module_table *module;

	list_क्रम_each_entry(module, &ctx->module_list, list) अणु
		अगर (module->mod_info->mod_id == mod_id)
			वापस --module->usage_cnt;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल काष्ठा skl_module_table *skl_fill_module_table(काष्ठा sst_dsp *ctx,
						अक्षर *mod_name, पूर्णांक mod_id)
अणु
	स्थिर काष्ठा firmware *fw;
	काष्ठा skl_module_table *skl_module;
	अचिन्हित पूर्णांक size;
	पूर्णांक ret;

	ret = request_firmware(&fw, mod_name, ctx->dev);
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "Request Module %s failed :%d\n",
							mod_name, ret);
		वापस शून्य;
	पूर्ण

	skl_module = devm_kzalloc(ctx->dev, माप(*skl_module), GFP_KERNEL);
	अगर (skl_module == शून्य) अणु
		release_firmware(fw);
		वापस शून्य;
	पूर्ण

	size = माप(*skl_module->mod_info);
	skl_module->mod_info = devm_kzalloc(ctx->dev, size, GFP_KERNEL);
	अगर (skl_module->mod_info == शून्य) अणु
		release_firmware(fw);
		वापस शून्य;
	पूर्ण

	skl_module->mod_info->mod_id = mod_id;
	skl_module->mod_info->fw = fw;
	list_add(&skl_module->list, &ctx->module_list);

	वापस skl_module;
पूर्ण

/* get a module from it's unique ID */
अटल काष्ठा skl_module_table *skl_module_get_from_id(
			काष्ठा sst_dsp *ctx, u16 mod_id)
अणु
	काष्ठा skl_module_table *module;

	अगर (list_empty(&ctx->module_list)) अणु
		dev_err(ctx->dev, "Module list is empty\n");
		वापस शून्य;
	पूर्ण

	list_क्रम_each_entry(module, &ctx->module_list, list) अणु
		अगर (module->mod_info->mod_id == mod_id)
			वापस module;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक skl_transfer_module(काष्ठा sst_dsp *ctx, स्थिर व्योम *data,
			u32 size, u16 mod_id, u8 table_id, bool is_module)
अणु
	पूर्णांक ret, bytes_left, curr_pos;
	काष्ठा skl_dev *skl = ctx->thपढ़ो_context;
	skl->mod_load_complete = false;

	bytes_left = ctx->cl_dev.ops.cl_copy_to_dmabuf(ctx, data, size, false);
	अगर (bytes_left < 0)
		वापस bytes_left;

	/* check is_module flag to load module or library */
	अगर (is_module)
		ret = skl_ipc_load_modules(&skl->ipc, SKL_NUM_MODULES, &mod_id);
	अन्यथा
		ret = skl_sst_ipc_load_library(&skl->ipc, 0, table_id, false);

	अगर (ret < 0) अणु
		dev_err(ctx->dev, "Failed to Load %s with err %d\n",
				is_module ? "module" : "lib", ret);
		जाओ out;
	पूर्ण

	/*
	 * अगर bytes_left > 0 then रुको क्रम BDL complete पूर्णांकerrupt and
	 * copy the next chunk till bytes_left is 0. अगर bytes_left is
	 * zero, then रुको क्रम load module IPC reply
	 */
	जबतक (bytes_left > 0) अणु
		curr_pos = size - bytes_left;

		ret = skl_cldma_रुको_पूर्णांकerruptible(ctx);
		अगर (ret < 0)
			जाओ out;

		bytes_left = ctx->cl_dev.ops.cl_copy_to_dmabuf(ctx,
							data + curr_pos,
							bytes_left, false);
	पूर्ण

	ret = रुको_event_समयout(skl->mod_load_रुको, skl->mod_load_complete,
				msecs_to_jअगरfies(SKL_IPC_BOOT_MSECS));
	अगर (ret == 0 || !skl->mod_load_status) अणु
		dev_err(ctx->dev, "Module Load failed\n");
		ret = -EIO;
	पूर्ण

out:
	ctx->cl_dev.ops.cl_stop_dma(ctx);

	वापस ret;
पूर्ण

अटल पूर्णांक
skl_load_library(काष्ठा sst_dsp *ctx, काष्ठा skl_lib_info *linfo, पूर्णांक lib_count)
अणु
	काष्ठा skl_dev *skl = ctx->thपढ़ो_context;
	काष्ठा firmware stripped_fw;
	पूर्णांक ret, i;

	/* library indices start from 1 to N. 0 represents base FW */
	क्रम (i = 1; i < lib_count; i++) अणु
		ret = skl_prepare_lib_load(skl, &skl->lib_info[i], &stripped_fw,
					SKL_ADSP_FW_BIN_HDR_OFFSET, i);
		अगर (ret < 0)
			जाओ load_library_failed;
		ret = skl_transfer_module(ctx, stripped_fw.data,
				stripped_fw.size, 0, i, false);
		अगर (ret < 0)
			जाओ load_library_failed;
	पूर्ण

	वापस 0;

load_library_failed:
	skl_release_library(linfo, lib_count);
	वापस ret;
पूर्ण

अटल पूर्णांक skl_load_module(काष्ठा sst_dsp *ctx, u16 mod_id, u8 *guid)
अणु
	काष्ठा skl_module_table *module_entry = शून्य;
	पूर्णांक ret = 0;
	अक्षर mod_name[64]; /* guid str = 32 अक्षरs + 4 hyphens */

	snम_लिखो(mod_name, माप(mod_name), "intel/dsp_fw_%pUL.bin", guid);

	module_entry = skl_module_get_from_id(ctx, mod_id);
	अगर (module_entry == शून्य) अणु
		module_entry = skl_fill_module_table(ctx, mod_name, mod_id);
		अगर (module_entry == शून्य) अणु
			dev_err(ctx->dev, "Failed to Load module\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (!module_entry->usage_cnt) अणु
		ret = skl_transfer_module(ctx, module_entry->mod_info->fw->data,
				module_entry->mod_info->fw->size,
				mod_id, 0, true);
		अगर (ret < 0) अणु
			dev_err(ctx->dev, "Failed to Load module\n");
			वापस ret;
		पूर्ण
	पूर्ण

	ret = skl_get_module(ctx, mod_id);

	वापस ret;
पूर्ण

अटल पूर्णांक skl_unload_module(काष्ठा sst_dsp *ctx, u16 mod_id)
अणु
	पूर्णांक usage_cnt;
	काष्ठा skl_dev *skl = ctx->thपढ़ो_context;
	पूर्णांक ret = 0;

	usage_cnt = skl_put_module(ctx, mod_id);
	अगर (usage_cnt < 0) अणु
		dev_err(ctx->dev, "Module bad usage cnt!:%d\n", usage_cnt);
		वापस -EIO;
	पूर्ण

	/* अगर module is used by others वापस, no need to unload */
	अगर (usage_cnt > 0)
		वापस 0;

	ret = skl_ipc_unload_modules(&skl->ipc,
			SKL_NUM_MODULES, &mod_id);
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "Failed to UnLoad module\n");
		skl_get_module(ctx, mod_id);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

व्योम skl_clear_module_cnt(काष्ठा sst_dsp *ctx)
अणु
	काष्ठा skl_module_table *module;

	अगर (list_empty(&ctx->module_list))
		वापस;

	list_क्रम_each_entry(module, &ctx->module_list, list) अणु
		module->usage_cnt = 0;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(skl_clear_module_cnt);

अटल व्योम skl_clear_module_table(काष्ठा sst_dsp *ctx)
अणु
	काष्ठा skl_module_table *module, *पंचांगp;

	अगर (list_empty(&ctx->module_list))
		वापस;

	list_क्रम_each_entry_safe(module, पंचांगp, &ctx->module_list, list) अणु
		list_del(&module->list);
		release_firmware(module->mod_info->fw);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा skl_dsp_fw_ops skl_fw_ops = अणु
	.set_state_D0 = skl_set_dsp_D0,
	.set_state_D3 = skl_set_dsp_D3,
	.load_fw = skl_load_base_firmware,
	.get_fw_errcode = skl_get_errorcode,
	.load_library = skl_load_library,
	.load_mod = skl_load_module,
	.unload_mod = skl_unload_module,
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

पूर्णांक skl_sst_dsp_init(काष्ठा device *dev, व्योम __iomem *mmio_base, पूर्णांक irq,
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
	sst->addr.lpe = mmio_base;
	sst->addr.shim = mmio_base;
	sst->addr.sram0_base = SKL_ADSP_SRAM0_BASE;
	sst->addr.sram1_base = SKL_ADSP_SRAM1_BASE;
	sst->addr.w0_stat_sz = SKL_ADSP_W0_STAT_SZ;
	sst->addr.w0_up_sz = SKL_ADSP_W0_UP_SZ;

	sst_dsp_mailbox_init(sst, (SKL_ADSP_SRAM0_BASE + SKL_ADSP_W0_STAT_SZ),
			SKL_ADSP_W0_UP_SZ, SKL_ADSP_SRAM1_BASE, SKL_ADSP_W1_SZ);

	ret = skl_ipc_init(dev, skl);
	अगर (ret) अणु
		skl_dsp_मुक्त(sst);
		वापस ret;
	पूर्ण

	sst->fw_ops = skl_fw_ops;

	वापस skl_dsp_acquire_irq(sst);
पूर्ण
EXPORT_SYMBOL_GPL(skl_sst_dsp_init);

पूर्णांक skl_sst_init_fw(काष्ठा device *dev, काष्ठा skl_dev *skl)
अणु
	पूर्णांक ret;
	काष्ठा sst_dsp *sst = skl->dsp;

	ret = sst->fw_ops.load_fw(sst);
	अगर (ret < 0) अणु
		dev_err(dev, "Load base fw failed : %d\n", ret);
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
EXPORT_SYMBOL_GPL(skl_sst_init_fw);

व्योम skl_sst_dsp_cleanup(काष्ठा device *dev, काष्ठा skl_dev *skl)
अणु

	अगर (skl->dsp->fw)
		release_firmware(skl->dsp->fw);
	skl_clear_module_table(skl->dsp);
	skl_मुक्तup_uuid_list(skl);
	skl_ipc_मुक्त(&skl->ipc);
	skl->dsp->ops->मुक्त(skl->dsp);
	अगर (skl->boot_complete) अणु
		skl->dsp->cl_dev.ops.cl_cleanup_controller(skl->dsp);
		skl_cldma_पूर्णांक_disable(skl->dsp);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(skl_sst_dsp_cleanup);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Intel Skylake IPC driver");
