<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
//
// Copyright(c) 2020 Intel Corporation. All rights reserved.
//
// Author: Cezary Rojewski <cezary.rojewski@पूर्णांकel.com>
//
// Special thanks to:
//    Marcin Barlik <marcin.barlik@पूर्णांकel.com>
//    Piotr Papierkowski <piotr.papierkowski@पूर्णांकel.com>
//
// क्रम sharing LPT-LP and WTP-LP AudioDSP architecture expertise and
// helping backtrack its historical background
//

#समावेश <linux/acpi.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <sound/पूर्णांकel-dsp-config.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-acpi.h>
#समावेश <sound/soc-acpi-पूर्णांकel-match.h>
#समावेश "core.h"
#समावेश "registers.h"

#घोषणा CREATE_TRACE_POINTS
#समावेश "trace.h"

अटल पूर्णांक __maybe_unused catpt_suspend(काष्ठा device *dev)
अणु
	काष्ठा catpt_dev *cdev = dev_get_drvdata(dev);
	काष्ठा dma_chan *chan;
	पूर्णांक ret;

	chan = catpt_dma_request_config_chan(cdev);
	अगर (IS_ERR(chan))
		वापस PTR_ERR(chan);

	स_रखो(&cdev->dx_ctx, 0, माप(cdev->dx_ctx));
	ret = catpt_ipc_enter_dxstate(cdev, CATPT_DX_STATE_D3, &cdev->dx_ctx);
	अगर (ret) अणु
		ret = CATPT_IPC_ERROR(ret);
		जाओ release_dma_chan;
	पूर्ण

	ret = catpt_dsp_stall(cdev, true);
	अगर (ret)
		जाओ release_dma_chan;

	ret = catpt_store_memdumps(cdev, chan);
	अगर (ret) अणु
		dev_err(cdev->dev, "store memdumps failed: %d\n", ret);
		जाओ release_dma_chan;
	पूर्ण

	ret = catpt_store_module_states(cdev, chan);
	अगर (ret) अणु
		dev_err(cdev->dev, "store module states failed: %d\n", ret);
		जाओ release_dma_chan;
	पूर्ण

	ret = catpt_store_streams_context(cdev, chan);
	अगर (ret)
		dev_err(cdev->dev, "store streams ctx failed: %d\n", ret);

release_dma_chan:
	dma_release_channel(chan);
	अगर (ret)
		वापस ret;
	वापस catpt_dsp_घातer_करोwn(cdev);
पूर्ण

अटल पूर्णांक __maybe_unused catpt_resume(काष्ठा device *dev)
अणु
	काष्ठा catpt_dev *cdev = dev_get_drvdata(dev);
	पूर्णांक ret, i;

	ret = catpt_dsp_घातer_up(cdev);
	अगर (ret)
		वापस ret;

	अगर (!try_module_get(dev->driver->owner)) अणु
		dev_info(dev, "module unloading, skipping fw boot\n");
		वापस 0;
	पूर्ण
	module_put(dev->driver->owner);

	ret = catpt_boot_firmware(cdev, true);
	अगर (ret) अणु
		dev_err(cdev->dev, "boot firmware failed: %d\n", ret);
		वापस ret;
	पूर्ण

	/* reconfigure SSP devices after Dx transition */
	क्रम (i = 0; i < CATPT_SSP_COUNT; i++) अणु
		अगर (cdev->devfmt[i].अगरace == अच_पूर्णांक_उच्च)
			जारी;

		ret = catpt_ipc_set_device_क्रमmat(cdev, &cdev->devfmt[i]);
		अगर (ret)
			वापस CATPT_IPC_ERROR(ret);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused catpt_runसमय_suspend(काष्ठा device *dev)
अणु
	अगर (!try_module_get(dev->driver->owner)) अणु
		dev_info(dev, "module unloading, skipping suspend\n");
		वापस 0;
	पूर्ण
	module_put(dev->driver->owner);

	वापस catpt_suspend(dev);
पूर्ण

अटल पूर्णांक __maybe_unused catpt_runसमय_resume(काष्ठा device *dev)
अणु
	वापस catpt_resume(dev);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops catpt_dev_pm = अणु
	SET_SYSTEM_SLEEP_PM_OPS(catpt_suspend, catpt_resume)
	SET_RUNTIME_PM_OPS(catpt_runसमय_suspend, catpt_runसमय_resume, शून्य)
पूर्ण;

/* machine board owned by CATPT is हटाओd with this hook */
अटल व्योम board_pdev_unरेजिस्टर(व्योम *data)
अणु
	platक्रमm_device_unरेजिस्टर(data);
पूर्ण

अटल पूर्णांक catpt_रेजिस्टर_board(काष्ठा catpt_dev *cdev)
अणु
	स्थिर काष्ठा catpt_spec *spec = cdev->spec;
	काष्ठा snd_soc_acpi_mach *mach;
	काष्ठा platक्रमm_device *board;

	mach = snd_soc_acpi_find_machine(spec->machines);
	अगर (!mach) अणु
		dev_info(cdev->dev, "no machines present\n");
		वापस 0;
	पूर्ण

	mach->mach_params.platक्रमm = "catpt-platform";
	board = platक्रमm_device_रेजिस्टर_data(शून्य, mach->drv_name,
					PLATFORM_DEVID_NONE,
					(स्थिर व्योम *)mach, माप(*mach));
	अगर (IS_ERR(board)) अणु
		dev_err(cdev->dev, "board register failed\n");
		वापस PTR_ERR(board);
	पूर्ण

	वापस devm_add_action_or_reset(cdev->dev, board_pdev_unरेजिस्टर,
					board);
पूर्ण

अटल पूर्णांक catpt_probe_components(काष्ठा catpt_dev *cdev)
अणु
	पूर्णांक ret;

	ret = catpt_dsp_घातer_up(cdev);
	अगर (ret)
		वापस ret;

	ret = catpt_dmac_probe(cdev);
	अगर (ret) अणु
		dev_err(cdev->dev, "DMAC probe failed: %d\n", ret);
		जाओ err_dmac_probe;
	पूर्ण

	ret = catpt_first_boot_firmware(cdev);
	अगर (ret) अणु
		dev_err(cdev->dev, "first fw boot failed: %d\n", ret);
		जाओ err_boot_fw;
	पूर्ण

	ret = catpt_रेजिस्टर_plat_component(cdev);
	अगर (ret) अणु
		dev_err(cdev->dev, "register plat comp failed: %d\n", ret);
		जाओ err_boot_fw;
	पूर्ण

	ret = catpt_रेजिस्टर_board(cdev);
	अगर (ret) अणु
		dev_err(cdev->dev, "register board failed: %d\n", ret);
		जाओ err_reg_board;
	पूर्ण

	/* reflect actual ADSP state in pm_runसमय */
	pm_runसमय_set_active(cdev->dev);

	pm_runसमय_set_स्वतःsuspend_delay(cdev->dev, 2000);
	pm_runसमय_use_स्वतःsuspend(cdev->dev);
	pm_runसमय_mark_last_busy(cdev->dev);
	pm_runसमय_enable(cdev->dev);
	वापस 0;

err_reg_board:
	snd_soc_unरेजिस्टर_component(cdev->dev);
err_boot_fw:
	catpt_dmac_हटाओ(cdev);
err_dmac_probe:
	catpt_dsp_घातer_करोwn(cdev);

	वापस ret;
पूर्ण

अटल व्योम catpt_dev_init(काष्ठा catpt_dev *cdev, काष्ठा device *dev,
			   स्थिर काष्ठा catpt_spec *spec)
अणु
	cdev->dev = dev;
	cdev->spec = spec;
	init_completion(&cdev->fw_पढ़ोy);
	INIT_LIST_HEAD(&cdev->stream_list);
	spin_lock_init(&cdev->list_lock);
	mutex_init(&cdev->clk_mutex);

	/*
	 * Mark both device क्रमmats as uninitialized. Once corresponding
	 * cpu_dai's pcm is created, proper values are asचिन्हित.
	 */
	cdev->devfmt[CATPT_SSP_IFACE_0].अगरace = अच_पूर्णांक_उच्च;
	cdev->devfmt[CATPT_SSP_IFACE_1].अगरace = अच_पूर्णांक_उच्च;

	catpt_ipc_init(&cdev->ipc, dev);

	catpt_sram_init(&cdev->dram, spec->host_dram_offset,
			catpt_dram_size(cdev));
	catpt_sram_init(&cdev->iram, spec->host_iram_offset,
			catpt_iram_size(cdev));
पूर्ण

अटल पूर्णांक catpt_acpi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा catpt_spec *spec;
	काष्ठा catpt_dev *cdev;
	काष्ठा device *dev = &pdev->dev;
	स्थिर काष्ठा acpi_device_id *id;
	काष्ठा resource *res;
	पूर्णांक ret;

	id = acpi_match_device(dev->driver->acpi_match_table, dev);
	अगर (!id)
		वापस -ENODEV;

	ret = snd_पूर्णांकel_acpi_dsp_driver_probe(dev, id->id);
	अगर (ret != SND_INTEL_DSP_DRIVER_ANY && ret != SND_INTEL_DSP_DRIVER_SST) अणु
		dev_dbg(dev, "CATPT ACPI driver not selected, aborting probe\n");
		वापस -ENODEV;
	पूर्ण

	spec = device_get_match_data(dev);
	अगर (!spec)
		वापस -ENODEV;

	cdev = devm_kzalloc(dev, माप(*cdev), GFP_KERNEL);
	अगर (!cdev)
		वापस -ENOMEM;

	catpt_dev_init(cdev, dev, spec);

	/* map DSP bar address */
	cdev->lpe_ba = devm_platक्रमm_get_and_ioremap_resource(pdev, 0, &res);
	अगर (IS_ERR(cdev->lpe_ba))
		वापस PTR_ERR(cdev->lpe_ba);
	cdev->lpe_base = res->start;

	/* map PCI bar address */
	cdev->pci_ba = devm_platक्रमm_ioremap_resource(pdev, 1);
	अगर (IS_ERR(cdev->pci_ba))
		वापस PTR_ERR(cdev->pci_ba);

	/* alloc buffer क्रम storing DRAM context during dx transitions */
	cdev->dxbuf_vaddr = dmam_alloc_coherent(dev, catpt_dram_size(cdev),
						&cdev->dxbuf_paddr, GFP_KERNEL);
	अगर (!cdev->dxbuf_vaddr)
		वापस -ENOMEM;

	ret = platक्रमm_get_irq(pdev, 0);
	अगर (ret < 0)
		वापस ret;
	cdev->irq = ret;

	platक्रमm_set_drvdata(pdev, cdev);

	ret = devm_request_thपढ़ोed_irq(dev, cdev->irq, catpt_dsp_irq_handler,
					catpt_dsp_irq_thपढ़ो,
					IRQF_SHARED, "AudioDSP", cdev);
	अगर (ret)
		वापस ret;

	वापस catpt_probe_components(cdev);
पूर्ण

अटल पूर्णांक catpt_acpi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा catpt_dev *cdev = platक्रमm_get_drvdata(pdev);

	pm_runसमय_disable(cdev->dev);

	snd_soc_unरेजिस्टर_component(cdev->dev);
	catpt_dmac_हटाओ(cdev);
	catpt_dsp_घातer_करोwn(cdev);

	catpt_sram_मुक्त(&cdev->iram);
	catpt_sram_मुक्त(&cdev->dram);

	वापस 0;
पूर्ण

अटल काष्ठा catpt_spec lpt_desc = अणु
	.machines = snd_soc_acpi_पूर्णांकel_haswell_machines,
	.core_id = 0x01,
	.host_dram_offset = 0x000000,
	.host_iram_offset = 0x080000,
	.host_shim_offset = 0x0E7000,
	.host_dma_offset = अणु 0x0F0000, 0x0F8000 पूर्ण,
	.host_ssp_offset = अणु 0x0E8000, 0x0E9000 पूर्ण,
	.dram_mask = LPT_VDRTCTL0_DSRAMPGE_MASK,
	.iram_mask = LPT_VDRTCTL0_ISRAMPGE_MASK,
	.d3srampgd_bit = LPT_VDRTCTL0_D3SRAMPGD,
	.d3pgd_bit = LPT_VDRTCTL0_D3PGD,
	.pll_shutकरोwn = lpt_dsp_pll_shutकरोwn,
पूर्ण;

अटल काष्ठा catpt_spec wpt_desc = अणु
	.machines = snd_soc_acpi_पूर्णांकel_broadwell_machines,
	.core_id = 0x02,
	.host_dram_offset = 0x000000,
	.host_iram_offset = 0x0A0000,
	.host_shim_offset = 0x0FB000,
	.host_dma_offset = अणु 0x0FE000, 0x0FF000 पूर्ण,
	.host_ssp_offset = अणु 0x0FC000, 0x0FD000 पूर्ण,
	.dram_mask = WPT_VDRTCTL0_DSRAMPGE_MASK,
	.iram_mask = WPT_VDRTCTL0_ISRAMPGE_MASK,
	.d3srampgd_bit = WPT_VDRTCTL0_D3SRAMPGD,
	.d3pgd_bit = WPT_VDRTCTL0_D3PGD,
	.pll_shutकरोwn = wpt_dsp_pll_shutकरोwn,
पूर्ण;

अटल स्थिर काष्ठा acpi_device_id catpt_ids[] = अणु
	अणु "INT33C8", (अचिन्हित दीर्घ)&lpt_desc पूर्ण,
	अणु "INT3438", (अचिन्हित दीर्घ)&wpt_desc पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, catpt_ids);

अटल काष्ठा platक्रमm_driver catpt_acpi_driver = अणु
	.probe = catpt_acpi_probe,
	.हटाओ = catpt_acpi_हटाओ,
	.driver = अणु
		.name = "intel_catpt",
		.acpi_match_table = catpt_ids,
		.pm = &catpt_dev_pm,
		.dev_groups = catpt_attr_groups,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(catpt_acpi_driver);

MODULE_AUTHOR("Cezary Rojewski <cezary.rojewski@intel.com>");
MODULE_DESCRIPTION("Intel LPT/WPT AudioDSP driver");
MODULE_LICENSE("GPL v2");
