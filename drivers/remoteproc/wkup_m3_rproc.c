<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * TI AMx3 Wakeup M3 Remote Processor driver
 *
 * Copyright (C) 2014-2015 Texas Instruments, Inc.
 *
 * Dave Gerlach <d-gerlach@ti.com>
 * Suman Anna <s-anna@ti.com>
 */

#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/remoteproc.h>
#समावेश <linux/reset.h>

#समावेश <linux/platक्रमm_data/wkup_m3.h>

#समावेश "remoteproc_internal.h"

#घोषणा WKUPM3_MEM_MAX	2

/**
 * काष्ठा wkup_m3_mem - WkupM3 पूर्णांकernal memory काष्ठाure
 * @cpu_addr: MPU भव address of the memory region
 * @bus_addr: Bus address used to access the memory region
 * @dev_addr: Device address from Wakeup M3 view
 * @size: Size of the memory region
 */
काष्ठा wkup_m3_mem अणु
	व्योम __iomem *cpu_addr;
	phys_addr_t bus_addr;
	u32 dev_addr;
	माप_प्रकार size;
पूर्ण;

/**
 * काष्ठा wkup_m3_rproc - WkupM3 remote processor state
 * @rproc: rproc handle
 * @pdev: poपूर्णांकer to platक्रमm device
 * @mem: WkupM3 memory inक्रमmation
 * @rsts: reset control
 */
काष्ठा wkup_m3_rproc अणु
	काष्ठा rproc *rproc;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा wkup_m3_mem mem[WKUPM3_MEM_MAX];
	काष्ठा reset_control *rsts;
पूर्ण;

अटल पूर्णांक wkup_m3_rproc_start(काष्ठा rproc *rproc)
अणु
	काष्ठा wkup_m3_rproc *wkupm3 = rproc->priv;
	काष्ठा platक्रमm_device *pdev = wkupm3->pdev;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा wkup_m3_platक्रमm_data *pdata = dev_get_platdata(dev);
	पूर्णांक error = 0;

	error = reset_control_deनिश्चित(wkupm3->rsts);

	अगर (!wkupm3->rsts && pdata->deनिश्चित_reset(pdev, pdata->reset_name)) अणु
		dev_err(dev, "Unable to reset wkup_m3!\n");
		error = -ENODEV;
	पूर्ण

	वापस error;
पूर्ण

अटल पूर्णांक wkup_m3_rproc_stop(काष्ठा rproc *rproc)
अणु
	काष्ठा wkup_m3_rproc *wkupm3 = rproc->priv;
	काष्ठा platक्रमm_device *pdev = wkupm3->pdev;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा wkup_m3_platक्रमm_data *pdata = dev_get_platdata(dev);
	पूर्णांक error = 0;

	error = reset_control_निश्चित(wkupm3->rsts);

	अगर (!wkupm3->rsts && pdata->निश्चित_reset(pdev, pdata->reset_name)) अणु
		dev_err(dev, "Unable to assert reset of wkup_m3!\n");
		error = -ENODEV;
	पूर्ण

	वापस error;
पूर्ण

अटल व्योम *wkup_m3_rproc_da_to_va(काष्ठा rproc *rproc, u64 da, माप_प्रकार len, bool *is_iomem)
अणु
	काष्ठा wkup_m3_rproc *wkupm3 = rproc->priv;
	व्योम *va = शून्य;
	पूर्णांक i;
	u32 offset;

	अगर (len == 0)
		वापस शून्य;

	क्रम (i = 0; i < WKUPM3_MEM_MAX; i++) अणु
		अगर (da >= wkupm3->mem[i].dev_addr && da + len <=
		    wkupm3->mem[i].dev_addr +  wkupm3->mem[i].size) अणु
			offset = da -  wkupm3->mem[i].dev_addr;
			/* __क्रमce to make sparse happy with type conversion */
			va = (__क्रमce व्योम *)(wkupm3->mem[i].cpu_addr + offset);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस va;
पूर्ण

अटल स्थिर काष्ठा rproc_ops wkup_m3_rproc_ops = अणु
	.start		= wkup_m3_rproc_start,
	.stop		= wkup_m3_rproc_stop,
	.da_to_va	= wkup_m3_rproc_da_to_va,
पूर्ण;

अटल स्थिर काष्ठा of_device_id wkup_m3_rproc_of_match[] = अणु
	अणु .compatible = "ti,am3352-wkup-m3", पूर्ण,
	अणु .compatible = "ti,am4372-wkup-m3", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, wkup_m3_rproc_of_match);

अटल पूर्णांक wkup_m3_rproc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा wkup_m3_platक्रमm_data *pdata = dev->platक्रमm_data;
	/* umem always needs to be processed first */
	स्थिर अक्षर *mem_names[WKUPM3_MEM_MAX] = अणु "umem", "dmem" पूर्ण;
	काष्ठा wkup_m3_rproc *wkupm3;
	स्थिर अक्षर *fw_name;
	काष्ठा rproc *rproc;
	काष्ठा resource *res;
	स्थिर __be32 *addrp;
	u32 l4_offset = 0;
	u64 size;
	पूर्णांक ret;
	पूर्णांक i;

	ret = of_property_पढ़ो_string(dev->of_node, "ti,pm-firmware",
				      &fw_name);
	अगर (ret) अणु
		dev_err(dev, "No firmware filename given\n");
		वापस -ENODEV;
	पूर्ण

	pm_runसमय_enable(&pdev->dev);
	ret = pm_runसमय_get_sync(&pdev->dev);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "pm_runtime_get_sync() failed\n");
		जाओ err;
	पूर्ण

	rproc = rproc_alloc(dev, "wkup_m3", &wkup_m3_rproc_ops,
			    fw_name, माप(*wkupm3));
	अगर (!rproc) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	rproc->स्वतः_boot = false;

	wkupm3 = rproc->priv;
	wkupm3->rproc = rproc;
	wkupm3->pdev = pdev;

	wkupm3->rsts = devm_reset_control_get_optional_shared(dev, "rstctrl");
	अगर (IS_ERR(wkupm3->rsts))
		वापस PTR_ERR(wkupm3->rsts);
	अगर (!wkupm3->rsts) अणु
		अगर (!(pdata && pdata->deनिश्चित_reset && pdata->निश्चित_reset &&
		      pdata->reset_name)) अणु
			dev_err(dev, "Platform data missing!\n");
			ret = -ENODEV;
			जाओ err_put_rproc;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(mem_names); i++) अणु
		res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM,
						   mem_names[i]);
		wkupm3->mem[i].cpu_addr = devm_ioremap_resource(dev, res);
		अगर (IS_ERR(wkupm3->mem[i].cpu_addr)) अणु
			dev_err(&pdev->dev, "devm_ioremap_resource failed for resource %d\n",
				i);
			ret = PTR_ERR(wkupm3->mem[i].cpu_addr);
			जाओ err_put_rproc;
		पूर्ण
		wkupm3->mem[i].bus_addr = res->start;
		wkupm3->mem[i].size = resource_size(res);
		addrp = of_get_address(dev->of_node, i, &size, शून्य);
		/*
		 * The wkupm3 has umem at address 0 in its view, so the device
		 * addresses क्रम each memory region is computed as a relative
		 * offset of the bus address क्रम umem, and thereक्रमe needs to be
		 * processed first.
		 */
		अगर (!म_भेद(mem_names[i], "umem"))
			l4_offset = be32_to_cpu(*addrp);
		wkupm3->mem[i].dev_addr = be32_to_cpu(*addrp) - l4_offset;
	पूर्ण

	dev_set_drvdata(dev, rproc);

	ret = rproc_add(rproc);
	अगर (ret) अणु
		dev_err(dev, "rproc_add failed\n");
		जाओ err_put_rproc;
	पूर्ण

	वापस 0;

err_put_rproc:
	rproc_मुक्त(rproc);
err:
	pm_runसमय_put_noidle(dev);
	pm_runसमय_disable(dev);
	वापस ret;
पूर्ण

अटल पूर्णांक wkup_m3_rproc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rproc *rproc = platक्रमm_get_drvdata(pdev);

	rproc_del(rproc);
	rproc_मुक्त(rproc);
	pm_runसमय_put_sync(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक wkup_m3_rpm_suspend(काष्ठा device *dev)
अणु
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक wkup_m3_rpm_resume(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops wkup_m3_rproc_pm_ops = अणु
	SET_RUNTIME_PM_OPS(wkup_m3_rpm_suspend, wkup_m3_rpm_resume, शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver wkup_m3_rproc_driver = अणु
	.probe = wkup_m3_rproc_probe,
	.हटाओ = wkup_m3_rproc_हटाओ,
	.driver = अणु
		.name = "wkup_m3_rproc",
		.of_match_table = wkup_m3_rproc_of_match,
		.pm = &wkup_m3_rproc_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(wkup_m3_rproc_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("TI Wakeup M3 remote processor control driver");
MODULE_AUTHOR("Dave Gerlach <d-gerlach@ti.com>");
