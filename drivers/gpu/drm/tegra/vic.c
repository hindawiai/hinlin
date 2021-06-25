<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015, NVIDIA Corporation.
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/host1x.h>
#समावेश <linux/iommu.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/reset.h>

#समावेश <soc/tegra/pmc.h>

#समावेश "drm.h"
#समावेश "falcon.h"
#समावेश "vic.h"

काष्ठा vic_config अणु
	स्थिर अक्षर *firmware;
	अचिन्हित पूर्णांक version;
	bool supports_sid;
पूर्ण;

काष्ठा vic अणु
	काष्ठा falcon falcon;
	bool booted;

	व्योम __iomem *regs;
	काष्ठा tegra_drm_client client;
	काष्ठा host1x_channel *channel;
	काष्ठा device *dev;
	काष्ठा clk *clk;
	काष्ठा reset_control *rst;

	/* Platक्रमm configuration */
	स्थिर काष्ठा vic_config *config;
पूर्ण;

अटल अंतरभूत काष्ठा vic *to_vic(काष्ठा tegra_drm_client *client)
अणु
	वापस container_of(client, काष्ठा vic, client);
पूर्ण

अटल व्योम vic_ग_लिखोl(काष्ठा vic *vic, u32 value, अचिन्हित पूर्णांक offset)
अणु
	ग_लिखोl(value, vic->regs + offset);
पूर्ण

अटल पूर्णांक vic_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा vic *vic = dev_get_drvdata(dev);
	पूर्णांक err;

	err = clk_prepare_enable(vic->clk);
	अगर (err < 0)
		वापस err;

	usleep_range(10, 20);

	err = reset_control_deनिश्चित(vic->rst);
	अगर (err < 0)
		जाओ disable;

	usleep_range(10, 20);

	वापस 0;

disable:
	clk_disable_unprepare(vic->clk);
	वापस err;
पूर्ण

अटल पूर्णांक vic_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा vic *vic = dev_get_drvdata(dev);
	पूर्णांक err;

	err = reset_control_निश्चित(vic->rst);
	अगर (err < 0)
		वापस err;

	usleep_range(2000, 4000);

	clk_disable_unprepare(vic->clk);

	vic->booted = false;

	वापस 0;
पूर्ण

अटल पूर्णांक vic_boot(काष्ठा vic *vic)
अणु
#अगर_घोषित CONFIG_IOMMU_API
	काष्ठा iommu_fwspec *spec = dev_iommu_fwspec_get(vic->dev);
#पूर्ण_अगर
	u32 fce_ucode_size, fce_bin_data_offset;
	व्योम *hdr;
	पूर्णांक err = 0;

	अगर (vic->booted)
		वापस 0;

#अगर_घोषित CONFIG_IOMMU_API
	अगर (vic->config->supports_sid && spec) अणु
		u32 value;

		value = TRANSCFG_ATT(1, TRANSCFG_SID_FALCON) |
			TRANSCFG_ATT(0, TRANSCFG_SID_HW);
		vic_ग_लिखोl(vic, value, VIC_TFBIF_TRANSCFG);

		अगर (spec->num_ids > 0) अणु
			value = spec->ids[0] & 0xffff;

			/*
			 * STREAMID0 is used क्रम input/output buffers.
			 * Initialize it to SID_VIC in हाल context isolation
			 * is not enabled, and SID_VIC is used क्रम both firmware
			 * and data buffers.
			 *
			 * If context isolation is enabled, it will be
			 * overridden by the SETSTREAMID opcode as part of
			 * each job.
			 */
			vic_ग_लिखोl(vic, value, VIC_THI_STREAMID0);

			/* STREAMID1 is used क्रम firmware loading. */
			vic_ग_लिखोl(vic, value, VIC_THI_STREAMID1);
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	/* setup घड़ीgating रेजिस्टरs */
	vic_ग_लिखोl(vic, CG_IDLE_CG_DLY_CNT(4) |
			CG_IDLE_CG_EN |
			CG_WAKEUP_DLY_CNT(4),
		   NV_PVIC_MISC_PRI_VIC_CG);

	err = falcon_boot(&vic->falcon);
	अगर (err < 0)
		वापस err;

	hdr = vic->falcon.firmware.virt;
	fce_bin_data_offset = *(u32 *)(hdr + VIC_UCODE_FCE_DATA_OFFSET);

	falcon_execute_method(&vic->falcon, VIC_SET_APPLICATION_ID, 1);

	/* Old VIC firmware needs kernel help with setting up FCE microcode. */
	अगर (fce_bin_data_offset != 0x0 && fce_bin_data_offset != 0xa5a5a5a5) अणु
		hdr = vic->falcon.firmware.virt +
			*(u32 *)(hdr + VIC_UCODE_FCE_HEADER_OFFSET);
		fce_ucode_size = *(u32 *)(hdr + FCE_UCODE_SIZE_OFFSET);

		falcon_execute_method(&vic->falcon, VIC_SET_FCE_UCODE_SIZE,
				      fce_ucode_size);
		falcon_execute_method(
			&vic->falcon, VIC_SET_FCE_UCODE_OFFSET,
			(vic->falcon.firmware.iova + fce_bin_data_offset) >> 8);
	पूर्ण

	err = falcon_रुको_idle(&vic->falcon);
	अगर (err < 0) अणु
		dev_err(vic->dev,
			"failed to set application ID and FCE base\n");
		वापस err;
	पूर्ण

	vic->booted = true;

	वापस 0;
पूर्ण

अटल पूर्णांक vic_init(काष्ठा host1x_client *client)
अणु
	काष्ठा tegra_drm_client *drm = host1x_to_drm_client(client);
	काष्ठा drm_device *dev = dev_get_drvdata(client->host);
	काष्ठा tegra_drm *tegra = dev->dev_निजी;
	काष्ठा vic *vic = to_vic(drm);
	पूर्णांक err;

	err = host1x_client_iommu_attach(client);
	अगर (err < 0 && err != -ENODEV) अणु
		dev_err(vic->dev, "failed to attach to domain: %d\n", err);
		वापस err;
	पूर्ण

	vic->channel = host1x_channel_request(client);
	अगर (!vic->channel) अणु
		err = -ENOMEM;
		जाओ detach;
	पूर्ण

	client->syncpts[0] = host1x_syncpt_request(client, 0);
	अगर (!client->syncpts[0]) अणु
		err = -ENOMEM;
		जाओ मुक्त_channel;
	पूर्ण

	err = tegra_drm_रेजिस्टर_client(tegra, drm);
	अगर (err < 0)
		जाओ मुक्त_syncpt;

	/*
	 * Inherit the DMA parameters (such as maximum segment size) from the
	 * parent host1x device.
	 */
	client->dev->dma_parms = client->host->dma_parms;

	वापस 0;

मुक्त_syncpt:
	host1x_syncpt_put(client->syncpts[0]);
मुक्त_channel:
	host1x_channel_put(vic->channel);
detach:
	host1x_client_iommu_detach(client);

	वापस err;
पूर्ण

अटल पूर्णांक vic_निकास(काष्ठा host1x_client *client)
अणु
	काष्ठा tegra_drm_client *drm = host1x_to_drm_client(client);
	काष्ठा drm_device *dev = dev_get_drvdata(client->host);
	काष्ठा tegra_drm *tegra = dev->dev_निजी;
	काष्ठा vic *vic = to_vic(drm);
	पूर्णांक err;

	/* aव्योम a dangling poपूर्णांकer just in हाल this disappears */
	client->dev->dma_parms = शून्य;

	err = tegra_drm_unरेजिस्टर_client(tegra, drm);
	अगर (err < 0)
		वापस err;

	host1x_syncpt_put(client->syncpts[0]);
	host1x_channel_put(vic->channel);
	host1x_client_iommu_detach(client);

	अगर (client->group) अणु
		dma_unmap_single(vic->dev, vic->falcon.firmware.phys,
				 vic->falcon.firmware.size, DMA_TO_DEVICE);
		tegra_drm_मुक्त(tegra, vic->falcon.firmware.size,
			       vic->falcon.firmware.virt,
			       vic->falcon.firmware.iova);
	पूर्ण अन्यथा अणु
		dma_मुक्त_coherent(vic->dev, vic->falcon.firmware.size,
				  vic->falcon.firmware.virt,
				  vic->falcon.firmware.iova);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा host1x_client_ops vic_client_ops = अणु
	.init = vic_init,
	.निकास = vic_निकास,
पूर्ण;

अटल पूर्णांक vic_load_firmware(काष्ठा vic *vic)
अणु
	काष्ठा host1x_client *client = &vic->client.base;
	काष्ठा tegra_drm *tegra = vic->client.drm;
	dma_addr_t iova;
	माप_प्रकार size;
	व्योम *virt;
	पूर्णांक err;

	अगर (vic->falcon.firmware.virt)
		वापस 0;

	err = falcon_पढ़ो_firmware(&vic->falcon, vic->config->firmware);
	अगर (err < 0)
		वापस err;

	size = vic->falcon.firmware.size;

	अगर (!client->group) अणु
		virt = dma_alloc_coherent(vic->dev, size, &iova, GFP_KERNEL);

		err = dma_mapping_error(vic->dev, iova);
		अगर (err < 0)
			वापस err;
	पूर्ण अन्यथा अणु
		virt = tegra_drm_alloc(tegra, size, &iova);
	पूर्ण

	vic->falcon.firmware.virt = virt;
	vic->falcon.firmware.iova = iova;

	err = falcon_load_firmware(&vic->falcon);
	अगर (err < 0)
		जाओ cleanup;

	/*
	 * In this हाल we have received an IOVA from the shared करोमुख्य, so we
	 * need to make sure to get the physical address so that the DMA API
	 * knows what memory pages to flush the cache क्रम.
	 */
	अगर (client->group) अणु
		dma_addr_t phys;

		phys = dma_map_single(vic->dev, virt, size, DMA_TO_DEVICE);

		err = dma_mapping_error(vic->dev, phys);
		अगर (err < 0)
			जाओ cleanup;

		vic->falcon.firmware.phys = phys;
	पूर्ण

	वापस 0;

cleanup:
	अगर (!client->group)
		dma_मुक्त_coherent(vic->dev, size, virt, iova);
	अन्यथा
		tegra_drm_मुक्त(tegra, size, virt, iova);

	वापस err;
पूर्ण

अटल पूर्णांक vic_खोलो_channel(काष्ठा tegra_drm_client *client,
			    काष्ठा tegra_drm_context *context)
अणु
	काष्ठा vic *vic = to_vic(client);
	पूर्णांक err;

	err = pm_runसमय_resume_and_get(vic->dev);
	अगर (err < 0)
		वापस err;

	err = vic_load_firmware(vic);
	अगर (err < 0)
		जाओ rpm_put;

	err = vic_boot(vic);
	अगर (err < 0)
		जाओ rpm_put;

	context->channel = host1x_channel_get(vic->channel);
	अगर (!context->channel) अणु
		err = -ENOMEM;
		जाओ rpm_put;
	पूर्ण

	वापस 0;

rpm_put:
	pm_runसमय_put(vic->dev);
	वापस err;
पूर्ण

अटल व्योम vic_बंद_channel(काष्ठा tegra_drm_context *context)
अणु
	काष्ठा vic *vic = to_vic(context->client);

	host1x_channel_put(context->channel);

	pm_runसमय_put(vic->dev);
पूर्ण

अटल स्थिर काष्ठा tegra_drm_client_ops vic_ops = अणु
	.खोलो_channel = vic_खोलो_channel,
	.बंद_channel = vic_बंद_channel,
	.submit = tegra_drm_submit,
पूर्ण;

#घोषणा NVIDIA_TEGRA_124_VIC_FIRMWARE "nvidia/tegra124/vic03_ucode.bin"

अटल स्थिर काष्ठा vic_config vic_t124_config = अणु
	.firmware = NVIDIA_TEGRA_124_VIC_FIRMWARE,
	.version = 0x40,
	.supports_sid = false,
पूर्ण;

#घोषणा NVIDIA_TEGRA_210_VIC_FIRMWARE "nvidia/tegra210/vic04_ucode.bin"

अटल स्थिर काष्ठा vic_config vic_t210_config = अणु
	.firmware = NVIDIA_TEGRA_210_VIC_FIRMWARE,
	.version = 0x21,
	.supports_sid = false,
पूर्ण;

#घोषणा NVIDIA_TEGRA_186_VIC_FIRMWARE "nvidia/tegra186/vic04_ucode.bin"

अटल स्थिर काष्ठा vic_config vic_t186_config = अणु
	.firmware = NVIDIA_TEGRA_186_VIC_FIRMWARE,
	.version = 0x18,
	.supports_sid = true,
पूर्ण;

#घोषणा NVIDIA_TEGRA_194_VIC_FIRMWARE "nvidia/tegra194/vic.bin"

अटल स्थिर काष्ठा vic_config vic_t194_config = अणु
	.firmware = NVIDIA_TEGRA_194_VIC_FIRMWARE,
	.version = 0x19,
	.supports_sid = true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id tegra_vic_of_match[] = अणु
	अणु .compatible = "nvidia,tegra124-vic", .data = &vic_t124_config पूर्ण,
	अणु .compatible = "nvidia,tegra210-vic", .data = &vic_t210_config पूर्ण,
	अणु .compatible = "nvidia,tegra186-vic", .data = &vic_t186_config पूर्ण,
	अणु .compatible = "nvidia,tegra194-vic", .data = &vic_t194_config पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, tegra_vic_of_match);

अटल पूर्णांक vic_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा host1x_syncpt **syncpts;
	काष्ठा resource *regs;
	काष्ठा vic *vic;
	पूर्णांक err;

	/* inherit DMA mask from host1x parent */
	err = dma_coerce_mask_and_coherent(dev, *dev->parent->dma_mask);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failed to set DMA mask: %d\n", err);
		वापस err;
	पूर्ण

	vic = devm_kzalloc(dev, माप(*vic), GFP_KERNEL);
	अगर (!vic)
		वापस -ENOMEM;

	vic->config = of_device_get_match_data(dev);

	syncpts = devm_kzalloc(dev, माप(*syncpts), GFP_KERNEL);
	अगर (!syncpts)
		वापस -ENOMEM;

	regs = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!regs) अणु
		dev_err(&pdev->dev, "failed to get registers\n");
		वापस -ENXIO;
	पूर्ण

	vic->regs = devm_ioremap_resource(dev, regs);
	अगर (IS_ERR(vic->regs))
		वापस PTR_ERR(vic->regs);

	vic->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(vic->clk)) अणु
		dev_err(&pdev->dev, "failed to get clock\n");
		वापस PTR_ERR(vic->clk);
	पूर्ण

	अगर (!dev->pm_करोमुख्य) अणु
		vic->rst = devm_reset_control_get(dev, "vic");
		अगर (IS_ERR(vic->rst)) अणु
			dev_err(&pdev->dev, "failed to get reset\n");
			वापस PTR_ERR(vic->rst);
		पूर्ण
	पूर्ण

	vic->falcon.dev = dev;
	vic->falcon.regs = vic->regs;

	err = falcon_init(&vic->falcon);
	अगर (err < 0)
		वापस err;

	platक्रमm_set_drvdata(pdev, vic);

	INIT_LIST_HEAD(&vic->client.base.list);
	vic->client.base.ops = &vic_client_ops;
	vic->client.base.dev = dev;
	vic->client.base.class = HOST1X_CLASS_VIC;
	vic->client.base.syncpts = syncpts;
	vic->client.base.num_syncpts = 1;
	vic->dev = dev;

	INIT_LIST_HEAD(&vic->client.list);
	vic->client.version = vic->config->version;
	vic->client.ops = &vic_ops;

	err = host1x_client_रेजिस्टर(&vic->client.base);
	अगर (err < 0) अणु
		dev_err(dev, "failed to register host1x client: %d\n", err);
		जाओ निकास_falcon;
	पूर्ण

	pm_runसमय_enable(&pdev->dev);
	अगर (!pm_runसमय_enabled(&pdev->dev)) अणु
		err = vic_runसमय_resume(&pdev->dev);
		अगर (err < 0)
			जाओ unरेजिस्टर_client;
	पूर्ण

	वापस 0;

unरेजिस्टर_client:
	host1x_client_unरेजिस्टर(&vic->client.base);
निकास_falcon:
	falcon_निकास(&vic->falcon);

	वापस err;
पूर्ण

अटल पूर्णांक vic_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा vic *vic = platक्रमm_get_drvdata(pdev);
	पूर्णांक err;

	err = host1x_client_unरेजिस्टर(&vic->client.base);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failed to unregister host1x client: %d\n",
			err);
		वापस err;
	पूर्ण

	अगर (pm_runसमय_enabled(&pdev->dev))
		pm_runसमय_disable(&pdev->dev);
	अन्यथा
		vic_runसमय_suspend(&pdev->dev);

	falcon_निकास(&vic->falcon);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops vic_pm_ops = अणु
	SET_RUNTIME_PM_OPS(vic_runसमय_suspend, vic_runसमय_resume, शून्य)
पूर्ण;

काष्ठा platक्रमm_driver tegra_vic_driver = अणु
	.driver = अणु
		.name = "tegra-vic",
		.of_match_table = tegra_vic_of_match,
		.pm = &vic_pm_ops
	पूर्ण,
	.probe = vic_probe,
	.हटाओ = vic_हटाओ,
पूर्ण;

#अगर IS_ENABLED(CONFIG_ARCH_TEGRA_124_SOC)
MODULE_FIRMWARE(NVIDIA_TEGRA_124_VIC_FIRMWARE);
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_ARCH_TEGRA_210_SOC)
MODULE_FIRMWARE(NVIDIA_TEGRA_210_VIC_FIRMWARE);
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_ARCH_TEGRA_186_SOC)
MODULE_FIRMWARE(NVIDIA_TEGRA_186_VIC_FIRMWARE);
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_ARCH_TEGRA_194_SOC)
MODULE_FIRMWARE(NVIDIA_TEGRA_194_VIC_FIRMWARE);
#पूर्ण_अगर
