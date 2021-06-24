<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2012-2016, The Linux Foundation. All rights reserved.
 * Copyright (C) 2017 Linaro Ltd.
 */
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerconnect.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioctl.h>
#समावेश <linux/delay.h>
#समावेश <linux/devcoredump.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <media/videobuf2-v4l2.h>
#समावेश <media/v4l2-mem2स्मृति.स>
#समावेश <media/v4l2-ioctl.h>

#समावेश "core.h"
#समावेश "firmware.h"
#समावेश "pm_helpers.h"
#समावेश "hfi_venus_io.h"

अटल व्योम venus_coredump(काष्ठा venus_core *core)
अणु
	काष्ठा device *dev;
	phys_addr_t mem_phys;
	माप_प्रकार mem_size;
	व्योम *mem_va;
	व्योम *data;

	dev = core->dev;
	mem_phys = core->fw.mem_phys;
	mem_size = core->fw.mem_size;

	mem_va = memremap(mem_phys, mem_size, MEMREMAP_WC);
	अगर (!mem_va)
		वापस;

	data = vदो_स्मृति(mem_size);
	अगर (!data) अणु
		memunmap(mem_va);
		वापस;
	पूर्ण

	स_नकल(data, mem_va, mem_size);
	memunmap(mem_va);
	dev_coredumpv(dev, data, mem_size, GFP_KERNEL);
पूर्ण

अटल व्योम venus_event_notअगरy(काष्ठा venus_core *core, u32 event)
अणु
	काष्ठा venus_inst *inst;

	चयन (event) अणु
	हाल EVT_SYS_WATCHDOG_TIMEOUT:
	हाल EVT_SYS_ERROR:
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	mutex_lock(&core->lock);
	core->sys_error = true;
	list_क्रम_each_entry(inst, &core->instances, list)
		inst->ops->event_notअगरy(inst, EVT_SESSION_ERROR, शून्य);
	mutex_unlock(&core->lock);

	disable_irq_nosync(core->irq);
	schedule_delayed_work(&core->work, msecs_to_jअगरfies(10));
पूर्ण

अटल स्थिर काष्ठा hfi_core_ops venus_core_ops = अणु
	.event_notअगरy = venus_event_notअगरy,
पूर्ण;

अटल व्योम venus_sys_error_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा venus_core *core =
			container_of(work, काष्ठा venus_core, work.work);
	पूर्णांक ret = 0;

	pm_runसमय_get_sync(core->dev);

	hfi_core_deinit(core, true);

	dev_warn(core->dev, "system error has occurred, starting recovery!\n");

	mutex_lock(&core->lock);

	जबतक (pm_runसमय_active(core->dev_dec) || pm_runसमय_active(core->dev_enc))
		msleep(10);

	venus_shutकरोwn(core);

	venus_coredump(core);

	pm_runसमय_put_sync(core->dev);

	जबतक (core->pmकरोमुख्यs[0] && pm_runसमय_active(core->pmकरोमुख्यs[0]))
		usleep_range(1000, 1500);

	hfi_reinit(core);

	pm_runसमय_get_sync(core->dev);

	ret |= venus_boot(core);
	ret |= hfi_core_resume(core, true);

	enable_irq(core->irq);

	mutex_unlock(&core->lock);

	ret |= hfi_core_init(core);

	pm_runसमय_put_sync(core->dev);

	अगर (ret) अणु
		disable_irq_nosync(core->irq);
		dev_warn(core->dev, "recovery failed (%d)\n", ret);
		schedule_delayed_work(&core->work, msecs_to_jअगरfies(10));
		वापस;
	पूर्ण

	mutex_lock(&core->lock);
	core->sys_error = false;
	mutex_unlock(&core->lock);
पूर्ण

अटल u32 to_v4l2_codec_type(u32 codec)
अणु
	चयन (codec) अणु
	हाल HFI_VIDEO_CODEC_H264:
		वापस V4L2_PIX_FMT_H264;
	हाल HFI_VIDEO_CODEC_H263:
		वापस V4L2_PIX_FMT_H263;
	हाल HFI_VIDEO_CODEC_MPEG1:
		वापस V4L2_PIX_FMT_MPEG1;
	हाल HFI_VIDEO_CODEC_MPEG2:
		वापस V4L2_PIX_FMT_MPEG2;
	हाल HFI_VIDEO_CODEC_MPEG4:
		वापस V4L2_PIX_FMT_MPEG4;
	हाल HFI_VIDEO_CODEC_VC1:
		वापस V4L2_PIX_FMT_VC1_ANNEX_G;
	हाल HFI_VIDEO_CODEC_VP8:
		वापस V4L2_PIX_FMT_VP8;
	हाल HFI_VIDEO_CODEC_VP9:
		वापस V4L2_PIX_FMT_VP9;
	हाल HFI_VIDEO_CODEC_DIVX:
	हाल HFI_VIDEO_CODEC_DIVX_311:
		वापस V4L2_PIX_FMT_XVID;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक venus_क्रमागतerate_codecs(काष्ठा venus_core *core, u32 type)
अणु
	स्थिर काष्ठा hfi_inst_ops dummy_ops = अणुपूर्ण;
	काष्ठा venus_inst *inst;
	u32 codec, codecs;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	अगर (core->res->hfi_version != HFI_VERSION_1XX)
		वापस 0;

	inst = kzalloc(माप(*inst), GFP_KERNEL);
	अगर (!inst)
		वापस -ENOMEM;

	mutex_init(&inst->lock);
	inst->core = core;
	inst->session_type = type;
	अगर (type == VIDC_SESSION_TYPE_DEC)
		codecs = core->dec_codecs;
	अन्यथा
		codecs = core->enc_codecs;

	ret = hfi_session_create(inst, &dummy_ops);
	अगर (ret)
		जाओ err;

	क्रम (i = 0; i < MAX_CODEC_NUM; i++) अणु
		codec = (1UL << i) & codecs;
		अगर (!codec)
			जारी;

		ret = hfi_session_init(inst, to_v4l2_codec_type(codec));
		अगर (ret)
			जाओ करोne;

		ret = hfi_session_deinit(inst);
		अगर (ret)
			जाओ करोne;
	पूर्ण

करोne:
	hfi_session_destroy(inst);
err:
	mutex_destroy(&inst->lock);
	kमुक्त(inst);

	वापस ret;
पूर्ण

अटल व्योम venus_assign_रेजिस्टर_offsets(काष्ठा venus_core *core)
अणु
	अगर (IS_V6(core)) अणु
		core->vbअगर_base = core->base + VBIF_BASE;
		core->cpu_base = core->base + CPU_BASE_V6;
		core->cpu_cs_base = core->base + CPU_CS_BASE_V6;
		core->cpu_ic_base = core->base + CPU_IC_BASE_V6;
		core->wrapper_base = core->base + WRAPPER_BASE_V6;
		core->wrapper_tz_base = core->base + WRAPPER_TZ_BASE_V6;
		core->aon_base = core->base + AON_BASE_V6;
	पूर्ण अन्यथा अणु
		core->vbअगर_base = core->base + VBIF_BASE;
		core->cpu_base = core->base + CPU_BASE;
		core->cpu_cs_base = core->base + CPU_CS_BASE;
		core->cpu_ic_base = core->base + CPU_IC_BASE;
		core->wrapper_base = core->base + WRAPPER_BASE;
		core->wrapper_tz_base = शून्य;
		core->aon_base = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक venus_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा venus_core *core;
	काष्ठा resource *r;
	पूर्णांक ret;

	core = devm_kzalloc(dev, माप(*core), GFP_KERNEL);
	अगर (!core)
		वापस -ENOMEM;

	core->dev = dev;

	r = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	core->base = devm_ioremap_resource(dev, r);
	अगर (IS_ERR(core->base))
		वापस PTR_ERR(core->base);

	core->video_path = devm_of_icc_get(dev, "video-mem");
	अगर (IS_ERR(core->video_path))
		वापस PTR_ERR(core->video_path);

	core->cpucfg_path = devm_of_icc_get(dev, "cpu-cfg");
	अगर (IS_ERR(core->cpucfg_path))
		वापस PTR_ERR(core->cpucfg_path);

	core->irq = platक्रमm_get_irq(pdev, 0);
	अगर (core->irq < 0)
		वापस core->irq;

	core->res = of_device_get_match_data(dev);
	अगर (!core->res)
		वापस -ENODEV;

	mutex_init(&core->pm_lock);

	core->pm_ops = venus_pm_get(core->res->hfi_version);
	अगर (!core->pm_ops)
		वापस -ENODEV;

	अगर (core->pm_ops->core_get) अणु
		ret = core->pm_ops->core_get(core);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = dma_set_mask_and_coherent(dev, core->res->dma_mask);
	अगर (ret)
		जाओ err_core_put;

	dma_set_max_seg_size(dev, अच_पूर्णांक_उच्च);

	INIT_LIST_HEAD(&core->instances);
	mutex_init(&core->lock);
	INIT_DELAYED_WORK(&core->work, venus_sys_error_handler);

	ret = devm_request_thपढ़ोed_irq(dev, core->irq, hfi_isr, hfi_isr_thपढ़ो,
					IRQF_TRIGGER_HIGH | IRQF_ONESHOT,
					"venus", core);
	अगर (ret)
		जाओ err_core_put;

	ret = hfi_create(core, &venus_core_ops);
	अगर (ret)
		जाओ err_core_put;

	venus_assign_रेजिस्टर_offsets(core);

	ret = v4l2_device_रेजिस्टर(dev, &core->v4l2_dev);
	अगर (ret)
		जाओ err_core_deinit;

	platक्रमm_set_drvdata(pdev, core);

	pm_runसमय_enable(dev);

	ret = pm_runसमय_get_sync(dev);
	अगर (ret < 0)
		जाओ err_runसमय_disable;

	ret = of_platक्रमm_populate(dev->of_node, शून्य, शून्य, dev);
	अगर (ret)
		जाओ err_runसमय_disable;

	ret = venus_firmware_init(core);
	अगर (ret)
		जाओ err_runसमय_disable;

	ret = venus_boot(core);
	अगर (ret)
		जाओ err_runसमय_disable;

	ret = hfi_core_resume(core, true);
	अगर (ret)
		जाओ err_venus_shutकरोwn;

	ret = hfi_core_init(core);
	अगर (ret)
		जाओ err_venus_shutकरोwn;

	ret = venus_क्रमागतerate_codecs(core, VIDC_SESSION_TYPE_DEC);
	अगर (ret)
		जाओ err_venus_shutकरोwn;

	ret = venus_क्रमागतerate_codecs(core, VIDC_SESSION_TYPE_ENC);
	अगर (ret)
		जाओ err_venus_shutकरोwn;

	ret = pm_runसमय_put_sync(dev);
	अगर (ret) अणु
		pm_runसमय_get_noresume(dev);
		जाओ err_dev_unरेजिस्टर;
	पूर्ण

	venus_dbgfs_init(core);

	वापस 0;

err_dev_unरेजिस्टर:
	v4l2_device_unरेजिस्टर(&core->v4l2_dev);
err_venus_shutकरोwn:
	venus_shutकरोwn(core);
err_runसमय_disable:
	pm_runसमय_put_noidle(dev);
	pm_runसमय_set_suspended(dev);
	pm_runसमय_disable(dev);
	hfi_destroy(core);
err_core_deinit:
	hfi_core_deinit(core, false);
err_core_put:
	अगर (core->pm_ops->core_put)
		core->pm_ops->core_put(core);
	वापस ret;
पूर्ण

अटल पूर्णांक venus_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा venus_core *core = platक्रमm_get_drvdata(pdev);
	स्थिर काष्ठा venus_pm_ops *pm_ops = core->pm_ops;
	काष्ठा device *dev = core->dev;
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(dev);
	WARN_ON(ret < 0);

	ret = hfi_core_deinit(core, true);
	WARN_ON(ret);

	venus_shutकरोwn(core);
	of_platक्रमm_depopulate(dev);

	venus_firmware_deinit(core);

	pm_runसमय_put_sync(dev);
	pm_runसमय_disable(dev);

	अगर (pm_ops->core_put)
		pm_ops->core_put(core);

	v4l2_device_unरेजिस्टर(&core->v4l2_dev);

	hfi_destroy(core);

	mutex_destroy(&core->pm_lock);
	mutex_destroy(&core->lock);
	venus_dbgfs_deinit(core);

	वापस ret;
पूर्ण

अटल व्योम venus_core_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा venus_core *core = platक्रमm_get_drvdata(pdev);

	pm_runसमय_get_sync(core->dev);
	venus_shutकरोwn(core);
	venus_firmware_deinit(core);
	pm_runसमय_put_sync(core->dev);
पूर्ण

अटल __maybe_unused पूर्णांक venus_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा venus_core *core = dev_get_drvdata(dev);
	स्थिर काष्ठा venus_pm_ops *pm_ops = core->pm_ops;
	पूर्णांक ret;

	ret = hfi_core_suspend(core);
	अगर (ret)
		वापस ret;

	अगर (pm_ops->core_घातer) अणु
		ret = pm_ops->core_घातer(core, POWER_OFF);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = icc_set_bw(core->cpucfg_path, 0, 0);
	अगर (ret)
		जाओ err_cpucfg_path;

	ret = icc_set_bw(core->video_path, 0, 0);
	अगर (ret)
		जाओ err_video_path;

	वापस ret;

err_video_path:
	icc_set_bw(core->cpucfg_path, kbps_to_icc(1000), 0);
err_cpucfg_path:
	pm_ops->core_घातer(core, POWER_ON);

	वापस ret;
पूर्ण

अटल __maybe_unused पूर्णांक venus_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा venus_core *core = dev_get_drvdata(dev);
	स्थिर काष्ठा venus_pm_ops *pm_ops = core->pm_ops;
	पूर्णांक ret;

	ret = icc_set_bw(core->video_path, kbps_to_icc(20000), 0);
	अगर (ret)
		वापस ret;

	ret = icc_set_bw(core->cpucfg_path, kbps_to_icc(1000), 0);
	अगर (ret)
		वापस ret;

	अगर (pm_ops->core_घातer) अणु
		ret = pm_ops->core_घातer(core, POWER_ON);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस hfi_core_resume(core, false);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops venus_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
	SET_RUNTIME_PM_OPS(venus_runसमय_suspend, venus_runसमय_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा freq_tbl msm8916_freq_table[] = अणु
	अणु 352800, 228570000 पूर्ण,	/* 1920x1088 @ 30 + 1280x720 @ 30 */
	अणु 244800, 160000000 पूर्ण,	/* 1920x1088 @ 30 */
	अणु 108000, 100000000 पूर्ण,	/* 1280x720 @ 30 */
पूर्ण;

अटल स्थिर काष्ठा reg_val msm8916_reg_preset[] = अणु
	अणु 0xe0020, 0x05555556 पूर्ण,
	अणु 0xe0024, 0x05555556 पूर्ण,
	अणु 0x80124, 0x00000003 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा venus_resources msm8916_res = अणु
	.freq_tbl = msm8916_freq_table,
	.freq_tbl_size = ARRAY_SIZE(msm8916_freq_table),
	.reg_tbl = msm8916_reg_preset,
	.reg_tbl_size = ARRAY_SIZE(msm8916_reg_preset),
	.clks = अणु "core", "iface", "bus", पूर्ण,
	.clks_num = 3,
	.max_load = 352800, /* 720p@30 + 1080p@30 */
	.hfi_version = HFI_VERSION_1XX,
	.vmem_id = VIDC_RESOURCE_NONE,
	.vmem_size = 0,
	.vmem_addr = 0,
	.dma_mask = 0xddc00000 - 1,
	.fwname = "qcom/venus-1.8/venus.mdt",
पूर्ण;

अटल स्थिर काष्ठा freq_tbl msm8996_freq_table[] = अणु
	अणु 1944000, 520000000 पूर्ण,	/* 4k UHD @ 60 (decode only) */
	अणु  972000, 520000000 पूर्ण,	/* 4k UHD @ 30 */
	अणु  489600, 346666667 पूर्ण,	/* 1080p @ 60 */
	अणु  244800, 150000000 पूर्ण,	/* 1080p @ 30 */
	अणु  108000,  75000000 पूर्ण,	/* 720p @ 30 */
पूर्ण;

अटल स्थिर काष्ठा reg_val msm8996_reg_preset[] = अणु
	अणु 0x80010, 0xffffffff पूर्ण,
	अणु 0x80018, 0x00001556 पूर्ण,
	अणु 0x8001C, 0x00001556 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा venus_resources msm8996_res = अणु
	.freq_tbl = msm8996_freq_table,
	.freq_tbl_size = ARRAY_SIZE(msm8996_freq_table),
	.reg_tbl = msm8996_reg_preset,
	.reg_tbl_size = ARRAY_SIZE(msm8996_reg_preset),
	.clks = अणु"core", "iface", "bus", "mbus" पूर्ण,
	.clks_num = 4,
	.vcodec0_clks = अणु "core" पूर्ण,
	.vcodec1_clks = अणु "core" पूर्ण,
	.vcodec_clks_num = 1,
	.max_load = 2563200,
	.hfi_version = HFI_VERSION_3XX,
	.vmem_id = VIDC_RESOURCE_NONE,
	.vmem_size = 0,
	.vmem_addr = 0,
	.dma_mask = 0xddc00000 - 1,
	.fwname = "qcom/venus-4.2/venus.mdt",
पूर्ण;

अटल स्थिर काष्ठा freq_tbl sdm845_freq_table[] = अणु
	अणु 3110400, 533000000 पूर्ण,	/* 4096x2160@90 */
	अणु 2073600, 444000000 पूर्ण,	/* 4096x2160@60 */
	अणु 1944000, 404000000 पूर्ण,	/* 3840x2160@60 */
	अणु  972000, 330000000 पूर्ण,	/* 3840x2160@30 */
	अणु  489600, 200000000 पूर्ण,	/* 1920x1080@60 */
	अणु  244800, 100000000 पूर्ण,	/* 1920x1080@30 */
पूर्ण;

अटल स्थिर काष्ठा bw_tbl sdm845_bw_table_enc[] = अणु
	अणु 1944000, 1612000, 0, 2416000, 0 पूर्ण,	/* 3840x2160@60 */
	अणु  972000,  951000, 0, 1434000, 0 पूर्ण,	/* 3840x2160@30 */
	अणु  489600,  723000, 0,  973000, 0 पूर्ण,	/* 1920x1080@60 */
	अणु  244800,  370000, 0,	495000, 0 पूर्ण,	/* 1920x1080@30 */
पूर्ण;

अटल स्थिर काष्ठा bw_tbl sdm845_bw_table_dec[] = अणु
	अणु 2073600, 3929000, 0, 5551000, 0 पूर्ण,	/* 4096x2160@60 */
	अणु 1036800, 1987000, 0, 2797000, 0 पूर्ण,	/* 4096x2160@30 */
	अणु  489600, 1040000, 0, 1298000, 0 पूर्ण,	/* 1920x1080@60 */
	अणु  244800,  530000, 0,  659000, 0 पूर्ण,	/* 1920x1080@30 */
पूर्ण;

अटल स्थिर काष्ठा venus_resources sdm845_res = अणु
	.freq_tbl = sdm845_freq_table,
	.freq_tbl_size = ARRAY_SIZE(sdm845_freq_table),
	.bw_tbl_enc = sdm845_bw_table_enc,
	.bw_tbl_enc_size = ARRAY_SIZE(sdm845_bw_table_enc),
	.bw_tbl_dec = sdm845_bw_table_dec,
	.bw_tbl_dec_size = ARRAY_SIZE(sdm845_bw_table_dec),
	.clks = अणु"core", "iface", "bus" पूर्ण,
	.clks_num = 3,
	.vcodec0_clks = अणु "core", "bus" पूर्ण,
	.vcodec1_clks = अणु "core", "bus" पूर्ण,
	.vcodec_clks_num = 2,
	.max_load = 3110400,	/* 4096x2160@90 */
	.hfi_version = HFI_VERSION_4XX,
	.vmem_id = VIDC_RESOURCE_NONE,
	.vmem_size = 0,
	.vmem_addr = 0,
	.dma_mask = 0xe0000000 - 1,
	.fwname = "qcom/venus-5.2/venus.mdt",
पूर्ण;

अटल स्थिर काष्ठा venus_resources sdm845_res_v2 = अणु
	.freq_tbl = sdm845_freq_table,
	.freq_tbl_size = ARRAY_SIZE(sdm845_freq_table),
	.bw_tbl_enc = sdm845_bw_table_enc,
	.bw_tbl_enc_size = ARRAY_SIZE(sdm845_bw_table_enc),
	.bw_tbl_dec = sdm845_bw_table_dec,
	.bw_tbl_dec_size = ARRAY_SIZE(sdm845_bw_table_dec),
	.clks = अणु"core", "iface", "bus" पूर्ण,
	.clks_num = 3,
	.vcodec0_clks = अणु "vcodec0_core", "vcodec0_bus" पूर्ण,
	.vcodec1_clks = अणु "vcodec1_core", "vcodec1_bus" पूर्ण,
	.vcodec_clks_num = 2,
	.vcodec_pmकरोमुख्यs = अणु "venus", "vcodec0", "vcodec1" पूर्ण,
	.vcodec_pmकरोमुख्यs_num = 3,
	.opp_pmकरोमुख्य = (स्थिर अक्षर *[]) अणु "cx", शून्य पूर्ण,
	.vcodec_num = 2,
	.max_load = 3110400,	/* 4096x2160@90 */
	.hfi_version = HFI_VERSION_4XX,
	.vmem_id = VIDC_RESOURCE_NONE,
	.vmem_size = 0,
	.vmem_addr = 0,
	.dma_mask = 0xe0000000 - 1,
	.cp_start = 0,
	.cp_size = 0x70800000,
	.cp_nonpixel_start = 0x1000000,
	.cp_nonpixel_size = 0x24800000,
	.fwname = "qcom/venus-5.2/venus.mdt",
पूर्ण;

अटल स्थिर काष्ठा freq_tbl sc7180_freq_table[] = अणु
	अणु  0, 500000000 पूर्ण,
	अणु  0, 434000000 पूर्ण,
	अणु  0, 340000000 पूर्ण,
	अणु  0, 270000000 पूर्ण,
	अणु  0, 150000000 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा bw_tbl sc7180_bw_table_enc[] = अणु
	अणु  972000,  750000, 0, 0, 0 पूर्ण,	/* 3840x2160@30 */
	अणु  489600,  451000, 0, 0, 0 पूर्ण,	/* 1920x1080@60 */
	अणु  244800,  234000, 0, 0, 0 पूर्ण,	/* 1920x1080@30 */
पूर्ण;

अटल स्थिर काष्ठा bw_tbl sc7180_bw_table_dec[] = अणु
	अणु 1036800, 1386000, 0, 1875000, 0 पूर्ण,	/* 4096x2160@30 */
	अणु  489600,  865000, 0, 1146000, 0 पूर्ण,	/* 1920x1080@60 */
	अणु  244800,  530000, 0,  583000, 0 पूर्ण,	/* 1920x1080@30 */
पूर्ण;

अटल स्थिर काष्ठा venus_resources sc7180_res = अणु
	.freq_tbl = sc7180_freq_table,
	.freq_tbl_size = ARRAY_SIZE(sc7180_freq_table),
	.bw_tbl_enc = sc7180_bw_table_enc,
	.bw_tbl_enc_size = ARRAY_SIZE(sc7180_bw_table_enc),
	.bw_tbl_dec = sc7180_bw_table_dec,
	.bw_tbl_dec_size = ARRAY_SIZE(sc7180_bw_table_dec),
	.clks = अणु"core", "iface", "bus" पूर्ण,
	.clks_num = 3,
	.vcodec0_clks = अणु "vcodec0_core", "vcodec0_bus" पूर्ण,
	.vcodec_clks_num = 2,
	.vcodec_pmकरोमुख्यs = अणु "venus", "vcodec0" पूर्ण,
	.vcodec_pmकरोमुख्यs_num = 2,
	.opp_pmकरोमुख्य = (स्थिर अक्षर *[]) अणु "cx", शून्य पूर्ण,
	.vcodec_num = 1,
	.hfi_version = HFI_VERSION_4XX,
	.vmem_id = VIDC_RESOURCE_NONE,
	.vmem_size = 0,
	.vmem_addr = 0,
	.dma_mask = 0xe0000000 - 1,
	.fwname = "qcom/venus-5.4/venus.mdt",
पूर्ण;

अटल स्थिर काष्ठा freq_tbl sm8250_freq_table[] = अणु
	अणु 0, 444000000 पूर्ण,
	अणु 0, 366000000 पूर्ण,
	अणु 0, 338000000 पूर्ण,
	अणु 0, 240000000 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा bw_tbl sm8250_bw_table_enc[] = अणु
	अणु 1944000, 1954000, 0, 3711000, 0 पूर्ण,	/* 3840x2160@60 */
	अणु  972000,  996000, 0, 1905000, 0 पूर्ण,	/* 3840x2160@30 */
	अणु  489600,  645000, 0,  977000, 0 पूर्ण,	/* 1920x1080@60 */
	अणु  244800,  332000, 0,	498000, 0 पूर्ण,	/* 1920x1080@30 */
पूर्ण;

अटल स्थिर काष्ठा bw_tbl sm8250_bw_table_dec[] = अणु
	अणु 2073600, 2403000, 0, 4113000, 0 पूर्ण,	/* 4096x2160@60 */
	अणु 1036800, 1224000, 0, 2079000, 0 पूर्ण,	/* 4096x2160@30 */
	अणु  489600,  812000, 0,  998000, 0 पूर्ण,	/* 1920x1080@60 */
	अणु  244800,  416000, 0,  509000, 0 पूर्ण,	/* 1920x1080@30 */
पूर्ण;

अटल स्थिर काष्ठा reg_val sm8250_reg_preset[] = अणु
	अणु 0xb0088, 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा venus_resources sm8250_res = अणु
	.freq_tbl = sm8250_freq_table,
	.freq_tbl_size = ARRAY_SIZE(sm8250_freq_table),
	.reg_tbl = sm8250_reg_preset,
	.reg_tbl_size = ARRAY_SIZE(sm8250_reg_preset),
	.bw_tbl_enc = sm8250_bw_table_enc,
	.bw_tbl_enc_size = ARRAY_SIZE(sm8250_bw_table_enc),
	.bw_tbl_dec = sm8250_bw_table_dec,
	.bw_tbl_dec_size = ARRAY_SIZE(sm8250_bw_table_dec),
	.clks = अणु"core", "iface"पूर्ण,
	.clks_num = 2,
	.resets = अणु "bus", "core" पूर्ण,
	.resets_num = 2,
	.vcodec0_clks = अणु "vcodec0_core" पूर्ण,
	.vcodec_clks_num = 1,
	.vcodec_pmकरोमुख्यs = अणु "venus", "vcodec0" पूर्ण,
	.vcodec_pmकरोमुख्यs_num = 2,
	.opp_pmकरोमुख्य = (स्थिर अक्षर *[]) अणु "mx", शून्य पूर्ण,
	.vcodec_num = 1,
	.max_load = 7833600,
	.hfi_version = HFI_VERSION_6XX,
	.vmem_id = VIDC_RESOURCE_NONE,
	.vmem_size = 0,
	.vmem_addr = 0,
	.dma_mask = 0xe0000000 - 1,
	.fwname = "qcom/vpu-1.0/venus.mdt",
पूर्ण;

अटल स्थिर काष्ठा of_device_id venus_dt_match[] = अणु
	अणु .compatible = "qcom,msm8916-venus", .data = &msm8916_res, पूर्ण,
	अणु .compatible = "qcom,msm8996-venus", .data = &msm8996_res, पूर्ण,
	अणु .compatible = "qcom,sdm845-venus", .data = &sdm845_res, पूर्ण,
	अणु .compatible = "qcom,sdm845-venus-v2", .data = &sdm845_res_v2, पूर्ण,
	अणु .compatible = "qcom,sc7180-venus", .data = &sc7180_res, पूर्ण,
	अणु .compatible = "qcom,sm8250-venus", .data = &sm8250_res, पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, venus_dt_match);

अटल काष्ठा platक्रमm_driver qcom_venus_driver = अणु
	.probe = venus_probe,
	.हटाओ = venus_हटाओ,
	.driver = अणु
		.name = "qcom-venus",
		.of_match_table = venus_dt_match,
		.pm = &venus_pm_ops,
	पूर्ण,
	.shutकरोwn = venus_core_shutकरोwn,
पूर्ण;
module_platक्रमm_driver(qcom_venus_driver);

MODULE_ALIAS("platform:qcom-venus");
MODULE_DESCRIPTION("Qualcomm Venus video encoder and decoder driver");
MODULE_LICENSE("GPL v2");
