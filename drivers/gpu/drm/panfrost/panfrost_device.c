<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright 2018 Marty E. Plummer <hanetzer@starपंचांगail.com> */
/* Copyright 2019 Linaro, Ltd, Rob Herring <robh@kernel.org> */

#समावेश <linux/clk.h>
#समावेश <linux/reset.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/regulator/consumer.h>

#समावेश "panfrost_device.h"
#समावेश "panfrost_devfreq.h"
#समावेश "panfrost_features.h"
#समावेश "panfrost_gpu.h"
#समावेश "panfrost_job.h"
#समावेश "panfrost_mmu.h"
#समावेश "panfrost_perfcnt.h"

अटल पूर्णांक panfrost_reset_init(काष्ठा panfrost_device *pfdev)
अणु
	pfdev->rstc = devm_reset_control_array_get_optional_exclusive(pfdev->dev);
	अगर (IS_ERR(pfdev->rstc)) अणु
		dev_err(pfdev->dev, "get reset failed %ld\n", PTR_ERR(pfdev->rstc));
		वापस PTR_ERR(pfdev->rstc);
	पूर्ण

	वापस reset_control_deनिश्चित(pfdev->rstc);
पूर्ण

अटल व्योम panfrost_reset_fini(काष्ठा panfrost_device *pfdev)
अणु
	reset_control_निश्चित(pfdev->rstc);
पूर्ण

अटल पूर्णांक panfrost_clk_init(काष्ठा panfrost_device *pfdev)
अणु
	पूर्णांक err;
	अचिन्हित दीर्घ rate;

	pfdev->घड़ी = devm_clk_get(pfdev->dev, शून्य);
	अगर (IS_ERR(pfdev->घड़ी)) अणु
		dev_err(pfdev->dev, "get clock failed %ld\n", PTR_ERR(pfdev->घड़ी));
		वापस PTR_ERR(pfdev->घड़ी);
	पूर्ण

	rate = clk_get_rate(pfdev->घड़ी);
	dev_info(pfdev->dev, "clock rate = %lu\n", rate);

	err = clk_prepare_enable(pfdev->घड़ी);
	अगर (err)
		वापस err;

	pfdev->bus_घड़ी = devm_clk_get_optional(pfdev->dev, "bus");
	अगर (IS_ERR(pfdev->bus_घड़ी)) अणु
		dev_err(pfdev->dev, "get bus_clock failed %ld\n",
			PTR_ERR(pfdev->bus_घड़ी));
		वापस PTR_ERR(pfdev->bus_घड़ी);
	पूर्ण

	अगर (pfdev->bus_घड़ी) अणु
		rate = clk_get_rate(pfdev->bus_घड़ी);
		dev_info(pfdev->dev, "bus_clock rate = %lu\n", rate);

		err = clk_prepare_enable(pfdev->bus_घड़ी);
		अगर (err)
			जाओ disable_घड़ी;
	पूर्ण

	वापस 0;

disable_घड़ी:
	clk_disable_unprepare(pfdev->घड़ी);

	वापस err;
पूर्ण

अटल व्योम panfrost_clk_fini(काष्ठा panfrost_device *pfdev)
अणु
	clk_disable_unprepare(pfdev->bus_घड़ी);
	clk_disable_unprepare(pfdev->घड़ी);
पूर्ण

अटल पूर्णांक panfrost_regulator_init(काष्ठा panfrost_device *pfdev)
अणु
	पूर्णांक ret, i;

	pfdev->regulators = devm_kसुस्मृति(pfdev->dev, pfdev->comp->num_supplies,
					 माप(*pfdev->regulators),
					 GFP_KERNEL);
	अगर (!pfdev->regulators)
		वापस -ENOMEM;

	क्रम (i = 0; i < pfdev->comp->num_supplies; i++)
		pfdev->regulators[i].supply = pfdev->comp->supply_names[i];

	ret = devm_regulator_bulk_get(pfdev->dev,
				      pfdev->comp->num_supplies,
				      pfdev->regulators);
	अगर (ret < 0) अणु
		अगर (ret != -EPROBE_DEFER)
			dev_err(pfdev->dev, "failed to get regulators: %d\n",
				ret);
		वापस ret;
	पूर्ण

	ret = regulator_bulk_enable(pfdev->comp->num_supplies,
				    pfdev->regulators);
	अगर (ret < 0) अणु
		dev_err(pfdev->dev, "failed to enable regulators: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम panfrost_regulator_fini(काष्ठा panfrost_device *pfdev)
अणु
	अगर (!pfdev->regulators)
		वापस;

	regulator_bulk_disable(pfdev->comp->num_supplies, pfdev->regulators);
पूर्ण

अटल व्योम panfrost_pm_करोमुख्य_fini(काष्ठा panfrost_device *pfdev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(pfdev->pm_करोमुख्य_devs); i++) अणु
		अगर (!pfdev->pm_करोमुख्य_devs[i])
			अवरोध;

		अगर (pfdev->pm_करोमुख्य_links[i])
			device_link_del(pfdev->pm_करोमुख्य_links[i]);

		dev_pm_करोमुख्य_detach(pfdev->pm_करोमुख्य_devs[i], true);
	पूर्ण
पूर्ण

अटल पूर्णांक panfrost_pm_करोमुख्य_init(काष्ठा panfrost_device *pfdev)
अणु
	पूर्णांक err;
	पूर्णांक i, num_करोमुख्यs;

	num_करोमुख्यs = of_count_phandle_with_args(pfdev->dev->of_node,
						 "power-domains",
						 "#power-domain-cells");

	/*
	 * Single करोमुख्य is handled by the core, and, अगर only a single घातer
	 * the घातer करोमुख्य is requested, the property is optional.
	 */
	अगर (num_करोमुख्यs < 2 && pfdev->comp->num_pm_करोमुख्यs < 2)
		वापस 0;

	अगर (num_करोमुख्यs != pfdev->comp->num_pm_करोमुख्यs) अणु
		dev_err(pfdev->dev,
			"Incorrect number of power domains: %d provided, %d needed\n",
			num_करोमुख्यs, pfdev->comp->num_pm_करोमुख्यs);
		वापस -EINVAL;
	पूर्ण

	अगर (WARN(num_करोमुख्यs > ARRAY_SIZE(pfdev->pm_करोमुख्य_devs),
			"Too many supplies in compatible structure.\n"))
		वापस -EINVAL;

	क्रम (i = 0; i < num_करोमुख्यs; i++) अणु
		pfdev->pm_करोमुख्य_devs[i] =
			dev_pm_करोमुख्य_attach_by_name(pfdev->dev,
					pfdev->comp->pm_करोमुख्य_names[i]);
		अगर (IS_ERR_OR_शून्य(pfdev->pm_करोमुख्य_devs[i])) अणु
			err = PTR_ERR(pfdev->pm_करोमुख्य_devs[i]) ? : -ENODATA;
			pfdev->pm_करोमुख्य_devs[i] = शून्य;
			dev_err(pfdev->dev,
				"failed to get pm-domain %s(%d): %d\n",
				pfdev->comp->pm_करोमुख्य_names[i], i, err);
			जाओ err;
		पूर्ण

		pfdev->pm_करोमुख्य_links[i] = device_link_add(pfdev->dev,
				pfdev->pm_करोमुख्य_devs[i], DL_FLAG_PM_RUNTIME |
				DL_FLAG_STATELESS | DL_FLAG_RPM_ACTIVE);
		अगर (!pfdev->pm_करोमुख्य_links[i]) अणु
			dev_err(pfdev->pm_करोमुख्य_devs[i],
				"adding device link failed!\n");
			err = -ENODEV;
			जाओ err;
		पूर्ण
	पूर्ण

	वापस 0;

err:
	panfrost_pm_करोमुख्य_fini(pfdev);
	वापस err;
पूर्ण

पूर्णांक panfrost_device_init(काष्ठा panfrost_device *pfdev)
अणु
	पूर्णांक err;
	काष्ठा resource *res;

	mutex_init(&pfdev->sched_lock);
	INIT_LIST_HEAD(&pfdev->scheduled_jobs);
	INIT_LIST_HEAD(&pfdev->as_lru_list);

	spin_lock_init(&pfdev->as_lock);

	err = panfrost_clk_init(pfdev);
	अगर (err) अणु
		dev_err(pfdev->dev, "clk init failed %d\n", err);
		वापस err;
	पूर्ण

	err = panfrost_devfreq_init(pfdev);
	अगर (err) अणु
		अगर (err != -EPROBE_DEFER)
			dev_err(pfdev->dev, "devfreq init failed %d\n", err);
		जाओ out_clk;
	पूर्ण

	/* OPP will handle regulators */
	अगर (!pfdev->pfdevfreq.opp_of_table_added) अणु
		err = panfrost_regulator_init(pfdev);
		अगर (err)
			जाओ out_devfreq;
	पूर्ण

	err = panfrost_reset_init(pfdev);
	अगर (err) अणु
		dev_err(pfdev->dev, "reset init failed %d\n", err);
		जाओ out_regulator;
	पूर्ण

	err = panfrost_pm_करोमुख्य_init(pfdev);
	अगर (err)
		जाओ out_reset;

	res = platक्रमm_get_resource(pfdev->pdev, IORESOURCE_MEM, 0);
	pfdev->iomem = devm_ioremap_resource(pfdev->dev, res);
	अगर (IS_ERR(pfdev->iomem)) अणु
		dev_err(pfdev->dev, "failed to ioremap iomem\n");
		err = PTR_ERR(pfdev->iomem);
		जाओ out_pm_करोमुख्य;
	पूर्ण

	err = panfrost_gpu_init(pfdev);
	अगर (err)
		जाओ out_pm_करोमुख्य;

	err = panfrost_mmu_init(pfdev);
	अगर (err)
		जाओ out_gpu;

	err = panfrost_job_init(pfdev);
	अगर (err)
		जाओ out_mmu;

	err = panfrost_perfcnt_init(pfdev);
	अगर (err)
		जाओ out_job;

	वापस 0;
out_job:
	panfrost_job_fini(pfdev);
out_mmu:
	panfrost_mmu_fini(pfdev);
out_gpu:
	panfrost_gpu_fini(pfdev);
out_pm_करोमुख्य:
	panfrost_pm_करोमुख्य_fini(pfdev);
out_reset:
	panfrost_reset_fini(pfdev);
out_regulator:
	panfrost_regulator_fini(pfdev);
out_devfreq:
	panfrost_devfreq_fini(pfdev);
out_clk:
	panfrost_clk_fini(pfdev);
	वापस err;
पूर्ण

व्योम panfrost_device_fini(काष्ठा panfrost_device *pfdev)
अणु
	panfrost_perfcnt_fini(pfdev);
	panfrost_job_fini(pfdev);
	panfrost_mmu_fini(pfdev);
	panfrost_gpu_fini(pfdev);
	panfrost_pm_करोमुख्य_fini(pfdev);
	panfrost_reset_fini(pfdev);
	panfrost_devfreq_fini(pfdev);
	panfrost_regulator_fini(pfdev);
	panfrost_clk_fini(pfdev);
पूर्ण

स्थिर अक्षर *panfrost_exception_name(काष्ठा panfrost_device *pfdev, u32 exception_code)
अणु
	चयन (exception_code) अणु
		/* Non-Fault Status code */
	हाल 0x00: वापस "NOT_STARTED/IDLE/OK";
	हाल 0x01: वापस "DONE";
	हाल 0x02: वापस "INTERRUPTED";
	हाल 0x03: वापस "STOPPED";
	हाल 0x04: वापस "TERMINATED";
	हाल 0x08: वापस "ACTIVE";
		/* Job exceptions */
	हाल 0x40: वापस "JOB_CONFIG_FAULT";
	हाल 0x41: वापस "JOB_POWER_FAULT";
	हाल 0x42: वापस "JOB_READ_FAULT";
	हाल 0x43: वापस "JOB_WRITE_FAULT";
	हाल 0x44: वापस "JOB_AFFINITY_FAULT";
	हाल 0x48: वापस "JOB_BUS_FAULT";
	हाल 0x50: वापस "INSTR_INVALID_PC";
	हाल 0x51: वापस "INSTR_INVALID_ENC";
	हाल 0x52: वापस "INSTR_TYPE_MISMATCH";
	हाल 0x53: वापस "INSTR_OPERAND_FAULT";
	हाल 0x54: वापस "INSTR_TLS_FAULT";
	हाल 0x55: वापस "INSTR_BARRIER_FAULT";
	हाल 0x56: वापस "INSTR_ALIGN_FAULT";
	हाल 0x58: वापस "DATA_INVALID_FAULT";
	हाल 0x59: वापस "TILE_RANGE_FAULT";
	हाल 0x5A: वापस "ADDR_RANGE_FAULT";
	हाल 0x60: वापस "OUT_OF_MEMORY";
		/* GPU exceptions */
	हाल 0x80: वापस "DELAYED_BUS_FAULT";
	हाल 0x88: वापस "SHAREABILITY_FAULT";
		/* MMU exceptions */
	हाल 0xC1: वापस "TRANSLATION_FAULT_LEVEL1";
	हाल 0xC2: वापस "TRANSLATION_FAULT_LEVEL2";
	हाल 0xC3: वापस "TRANSLATION_FAULT_LEVEL3";
	हाल 0xC4: वापस "TRANSLATION_FAULT_LEVEL4";
	हाल 0xC8: वापस "PERMISSION_FAULT";
	हाल 0xC9 ... 0xCF: वापस "PERMISSION_FAULT";
	हाल 0xD1: वापस "TRANSTAB_BUS_FAULT_LEVEL1";
	हाल 0xD2: वापस "TRANSTAB_BUS_FAULT_LEVEL2";
	हाल 0xD3: वापस "TRANSTAB_BUS_FAULT_LEVEL3";
	हाल 0xD4: वापस "TRANSTAB_BUS_FAULT_LEVEL4";
	हाल 0xD8: वापस "ACCESS_FLAG";
	हाल 0xD9 ... 0xDF: वापस "ACCESS_FLAG";
	हाल 0xE0 ... 0xE7: वापस "ADDRESS_SIZE_FAULT";
	हाल 0xE8 ... 0xEF: वापस "MEMORY_ATTRIBUTES_FAULT";
	पूर्ण

	वापस "UNKNOWN";
पूर्ण

व्योम panfrost_device_reset(काष्ठा panfrost_device *pfdev)
अणु
	panfrost_gpu_soft_reset(pfdev);

	panfrost_gpu_घातer_on(pfdev);
	panfrost_mmu_reset(pfdev);
	panfrost_job_enable_पूर्णांकerrupts(pfdev);
पूर्ण

#अगर_घोषित CONFIG_PM
पूर्णांक panfrost_device_resume(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा panfrost_device *pfdev = platक्रमm_get_drvdata(pdev);

	panfrost_device_reset(pfdev);
	panfrost_devfreq_resume(pfdev);

	वापस 0;
पूर्ण

पूर्णांक panfrost_device_suspend(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा panfrost_device *pfdev = platक्रमm_get_drvdata(pdev);

	अगर (!panfrost_job_is_idle(pfdev))
		वापस -EBUSY;

	panfrost_devfreq_suspend(pfdev);
	panfrost_gpu_घातer_off(pfdev);

	वापस 0;
पूर्ण
#पूर्ण_अगर
