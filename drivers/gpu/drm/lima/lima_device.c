<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT
/* Copyright 2017-2019 Qiang Yu <yuq825@gmail.com> */

#समावेश <linux/regulator/consumer.h>
#समावेश <linux/reset.h>
#समावेश <linux/clk.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "lima_device.h"
#समावेश "lima_gp.h"
#समावेश "lima_pp.h"
#समावेश "lima_mmu.h"
#समावेश "lima_pmu.h"
#समावेश "lima_l2_cache.h"
#समावेश "lima_dlbu.h"
#समावेश "lima_bcast.h"
#समावेश "lima_vm.h"

काष्ठा lima_ip_desc अणु
	अक्षर *name;
	अक्षर *irq_name;
	bool must_have[lima_gpu_num];
	पूर्णांक offset[lima_gpu_num];

	पूर्णांक (*init)(काष्ठा lima_ip *ip);
	व्योम (*fini)(काष्ठा lima_ip *ip);
	पूर्णांक (*resume)(काष्ठा lima_ip *ip);
	व्योम (*suspend)(काष्ठा lima_ip *ip);
पूर्ण;

#घोषणा LIMA_IP_DESC(ipname, mst0, mst1, off0, off1, func, irq) \
	[lima_ip_##ipname] = अणु \
		.name = #ipname, \
		.irq_name = irq, \
		.must_have = अणु \
			[lima_gpu_mali400] = mst0, \
			[lima_gpu_mali450] = mst1, \
		पूर्ण, \
		.offset = अणु \
			[lima_gpu_mali400] = off0, \
			[lima_gpu_mali450] = off1, \
		पूर्ण, \
		.init = lima_##func##_init, \
		.fini = lima_##func##_fini, \
		.resume = lima_##func##_resume, \
		.suspend = lima_##func##_suspend, \
	पूर्ण

अटल काष्ठा lima_ip_desc lima_ip_desc[lima_ip_num] = अणु
	LIMA_IP_DESC(pmu,         false, false, 0x02000, 0x02000, pmu,      "pmu"),
	LIMA_IP_DESC(l2_cache0,   true,  true,  0x01000, 0x10000, l2_cache, शून्य),
	LIMA_IP_DESC(l2_cache1,   false, true,  -1,      0x01000, l2_cache, शून्य),
	LIMA_IP_DESC(l2_cache2,   false, false, -1,      0x11000, l2_cache, शून्य),
	LIMA_IP_DESC(gp,          true,  true,  0x00000, 0x00000, gp,       "gp"),
	LIMA_IP_DESC(pp0,         true,  true,  0x08000, 0x08000, pp,       "pp0"),
	LIMA_IP_DESC(pp1,         false, false, 0x0A000, 0x0A000, pp,       "pp1"),
	LIMA_IP_DESC(pp2,         false, false, 0x0C000, 0x0C000, pp,       "pp2"),
	LIMA_IP_DESC(pp3,         false, false, 0x0E000, 0x0E000, pp,       "pp3"),
	LIMA_IP_DESC(pp4,         false, false, -1,      0x28000, pp,       "pp4"),
	LIMA_IP_DESC(pp5,         false, false, -1,      0x2A000, pp,       "pp5"),
	LIMA_IP_DESC(pp6,         false, false, -1,      0x2C000, pp,       "pp6"),
	LIMA_IP_DESC(pp7,         false, false, -1,      0x2E000, pp,       "pp7"),
	LIMA_IP_DESC(gpmmu,       true,  true,  0x03000, 0x03000, mmu,      "gpmmu"),
	LIMA_IP_DESC(ppmmu0,      true,  true,  0x04000, 0x04000, mmu,      "ppmmu0"),
	LIMA_IP_DESC(ppmmu1,      false, false, 0x05000, 0x05000, mmu,      "ppmmu1"),
	LIMA_IP_DESC(ppmmu2,      false, false, 0x06000, 0x06000, mmu,      "ppmmu2"),
	LIMA_IP_DESC(ppmmu3,      false, false, 0x07000, 0x07000, mmu,      "ppmmu3"),
	LIMA_IP_DESC(ppmmu4,      false, false, -1,      0x1C000, mmu,      "ppmmu4"),
	LIMA_IP_DESC(ppmmu5,      false, false, -1,      0x1D000, mmu,      "ppmmu5"),
	LIMA_IP_DESC(ppmmu6,      false, false, -1,      0x1E000, mmu,      "ppmmu6"),
	LIMA_IP_DESC(ppmmu7,      false, false, -1,      0x1F000, mmu,      "ppmmu7"),
	LIMA_IP_DESC(dlbu,        false, true,  -1,      0x14000, dlbu,     शून्य),
	LIMA_IP_DESC(bcast,       false, true,  -1,      0x13000, bcast,    शून्य),
	LIMA_IP_DESC(pp_bcast,    false, true,  -1,      0x16000, pp_bcast, "pp"),
	LIMA_IP_DESC(ppmmu_bcast, false, true,  -1,      0x15000, mmu,      शून्य),
पूर्ण;

स्थिर अक्षर *lima_ip_name(काष्ठा lima_ip *ip)
अणु
	वापस lima_ip_desc[ip->id].name;
पूर्ण

अटल पूर्णांक lima_clk_enable(काष्ठा lima_device *dev)
अणु
	पूर्णांक err;

	err = clk_prepare_enable(dev->clk_bus);
	अगर (err)
		वापस err;

	err = clk_prepare_enable(dev->clk_gpu);
	अगर (err)
		जाओ error_out0;

	अगर (dev->reset) अणु
		err = reset_control_deनिश्चित(dev->reset);
		अगर (err) अणु
			dev_err(dev->dev,
				"reset controller deassert failed %d\n", err);
			जाओ error_out1;
		पूर्ण
	पूर्ण

	वापस 0;

error_out1:
	clk_disable_unprepare(dev->clk_gpu);
error_out0:
	clk_disable_unprepare(dev->clk_bus);
	वापस err;
पूर्ण

अटल व्योम lima_clk_disable(काष्ठा lima_device *dev)
अणु
	अगर (dev->reset)
		reset_control_निश्चित(dev->reset);
	clk_disable_unprepare(dev->clk_gpu);
	clk_disable_unprepare(dev->clk_bus);
पूर्ण

अटल पूर्णांक lima_clk_init(काष्ठा lima_device *dev)
अणु
	पूर्णांक err;

	dev->clk_bus = devm_clk_get(dev->dev, "bus");
	अगर (IS_ERR(dev->clk_bus)) अणु
		err = PTR_ERR(dev->clk_bus);
		अगर (err != -EPROBE_DEFER)
			dev_err(dev->dev, "get bus clk failed %d\n", err);
		dev->clk_bus = शून्य;
		वापस err;
	पूर्ण

	dev->clk_gpu = devm_clk_get(dev->dev, "core");
	अगर (IS_ERR(dev->clk_gpu)) अणु
		err = PTR_ERR(dev->clk_gpu);
		अगर (err != -EPROBE_DEFER)
			dev_err(dev->dev, "get core clk failed %d\n", err);
		dev->clk_gpu = शून्य;
		वापस err;
	पूर्ण

	dev->reset = devm_reset_control_array_get_optional_shared(dev->dev);
	अगर (IS_ERR(dev->reset)) अणु
		err = PTR_ERR(dev->reset);
		अगर (err != -EPROBE_DEFER)
			dev_err(dev->dev, "get reset controller failed %d\n",
				err);
		dev->reset = शून्य;
		वापस err;
	पूर्ण

	वापस lima_clk_enable(dev);
पूर्ण

अटल व्योम lima_clk_fini(काष्ठा lima_device *dev)
अणु
	lima_clk_disable(dev);
पूर्ण

अटल पूर्णांक lima_regulator_enable(काष्ठा lima_device *dev)
अणु
	पूर्णांक ret;

	अगर (!dev->regulator)
		वापस 0;

	ret = regulator_enable(dev->regulator);
	अगर (ret < 0) अणु
		dev_err(dev->dev, "failed to enable regulator: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम lima_regulator_disable(काष्ठा lima_device *dev)
अणु
	अगर (dev->regulator)
		regulator_disable(dev->regulator);
पूर्ण

अटल पूर्णांक lima_regulator_init(काष्ठा lima_device *dev)
अणु
	पूर्णांक ret;

	dev->regulator = devm_regulator_get_optional(dev->dev, "mali");
	अगर (IS_ERR(dev->regulator)) अणु
		ret = PTR_ERR(dev->regulator);
		dev->regulator = शून्य;
		अगर (ret == -ENODEV)
			वापस 0;
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev->dev, "failed to get regulator: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस lima_regulator_enable(dev);
पूर्ण

अटल व्योम lima_regulator_fini(काष्ठा lima_device *dev)
अणु
	lima_regulator_disable(dev);
पूर्ण

अटल पूर्णांक lima_init_ip(काष्ठा lima_device *dev, पूर्णांक index)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev->dev);
	काष्ठा lima_ip_desc *desc = lima_ip_desc + index;
	काष्ठा lima_ip *ip = dev->ip + index;
	स्थिर अक्षर *irq_name = desc->irq_name;
	पूर्णांक offset = desc->offset[dev->id];
	bool must = desc->must_have[dev->id];
	पूर्णांक err;

	अगर (offset < 0)
		वापस 0;

	ip->dev = dev;
	ip->id = index;
	ip->iomem = dev->iomem + offset;
	अगर (irq_name) अणु
		err = must ? platक्रमm_get_irq_byname(pdev, irq_name) :
			     platक्रमm_get_irq_byname_optional(pdev, irq_name);
		अगर (err < 0)
			जाओ out;
		ip->irq = err;
	पूर्ण

	err = desc->init(ip);
	अगर (!err) अणु
		ip->present = true;
		वापस 0;
	पूर्ण

out:
	वापस must ? err : 0;
पूर्ण

अटल व्योम lima_fini_ip(काष्ठा lima_device *ldev, पूर्णांक index)
अणु
	काष्ठा lima_ip_desc *desc = lima_ip_desc + index;
	काष्ठा lima_ip *ip = ldev->ip + index;

	अगर (ip->present)
		desc->fini(ip);
पूर्ण

अटल पूर्णांक lima_resume_ip(काष्ठा lima_device *ldev, पूर्णांक index)
अणु
	काष्ठा lima_ip_desc *desc = lima_ip_desc + index;
	काष्ठा lima_ip *ip = ldev->ip + index;
	पूर्णांक ret = 0;

	अगर (ip->present)
		ret = desc->resume(ip);

	वापस ret;
पूर्ण

अटल व्योम lima_suspend_ip(काष्ठा lima_device *ldev, पूर्णांक index)
अणु
	काष्ठा lima_ip_desc *desc = lima_ip_desc + index;
	काष्ठा lima_ip *ip = ldev->ip + index;

	अगर (ip->present)
		desc->suspend(ip);
पूर्ण

अटल पूर्णांक lima_init_gp_pipe(काष्ठा lima_device *dev)
अणु
	काष्ठा lima_sched_pipe *pipe = dev->pipe + lima_pipe_gp;
	पूर्णांक err;

	pipe->ldev = dev;

	err = lima_sched_pipe_init(pipe, "gp");
	अगर (err)
		वापस err;

	pipe->l2_cache[pipe->num_l2_cache++] = dev->ip + lima_ip_l2_cache0;
	pipe->mmu[pipe->num_mmu++] = dev->ip + lima_ip_gpmmu;
	pipe->processor[pipe->num_processor++] = dev->ip + lima_ip_gp;

	err = lima_gp_pipe_init(dev);
	अगर (err) अणु
		lima_sched_pipe_fini(pipe);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम lima_fini_gp_pipe(काष्ठा lima_device *dev)
अणु
	काष्ठा lima_sched_pipe *pipe = dev->pipe + lima_pipe_gp;

	lima_gp_pipe_fini(dev);
	lima_sched_pipe_fini(pipe);
पूर्ण

अटल पूर्णांक lima_init_pp_pipe(काष्ठा lima_device *dev)
अणु
	काष्ठा lima_sched_pipe *pipe = dev->pipe + lima_pipe_pp;
	पूर्णांक err, i;

	pipe->ldev = dev;

	err = lima_sched_pipe_init(pipe, "pp");
	अगर (err)
		वापस err;

	क्रम (i = 0; i < LIMA_SCHED_PIPE_MAX_PROCESSOR; i++) अणु
		काष्ठा lima_ip *pp = dev->ip + lima_ip_pp0 + i;
		काष्ठा lima_ip *ppmmu = dev->ip + lima_ip_ppmmu0 + i;
		काष्ठा lima_ip *l2_cache;

		अगर (dev->id == lima_gpu_mali400)
			l2_cache = dev->ip + lima_ip_l2_cache0;
		अन्यथा
			l2_cache = dev->ip + lima_ip_l2_cache1 + (i >> 2);

		अगर (pp->present && ppmmu->present && l2_cache->present) अणु
			pipe->mmu[pipe->num_mmu++] = ppmmu;
			pipe->processor[pipe->num_processor++] = pp;
			अगर (!pipe->l2_cache[i >> 2])
				pipe->l2_cache[pipe->num_l2_cache++] = l2_cache;
		पूर्ण
	पूर्ण

	अगर (dev->ip[lima_ip_bcast].present) अणु
		pipe->bcast_processor = dev->ip + lima_ip_pp_bcast;
		pipe->bcast_mmu = dev->ip + lima_ip_ppmmu_bcast;
	पूर्ण

	err = lima_pp_pipe_init(dev);
	अगर (err) अणु
		lima_sched_pipe_fini(pipe);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम lima_fini_pp_pipe(काष्ठा lima_device *dev)
अणु
	काष्ठा lima_sched_pipe *pipe = dev->pipe + lima_pipe_pp;

	lima_pp_pipe_fini(dev);
	lima_sched_pipe_fini(pipe);
पूर्ण

पूर्णांक lima_device_init(काष्ठा lima_device *ldev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(ldev->dev);
	पूर्णांक err, i;

	dma_set_coherent_mask(ldev->dev, DMA_BIT_MASK(32));

	err = lima_clk_init(ldev);
	अगर (err)
		वापस err;

	err = lima_regulator_init(ldev);
	अगर (err)
		जाओ err_out0;

	ldev->empty_vm = lima_vm_create(ldev);
	अगर (!ldev->empty_vm) अणु
		err = -ENOMEM;
		जाओ err_out1;
	पूर्ण

	ldev->बहु_शुरू = 0;
	अगर (ldev->id == lima_gpu_mali450) अणु
		ldev->बहु_पूर्ण = LIMA_VA_RESERVE_START;
		ldev->dlbu_cpu = dma_alloc_wc(
			ldev->dev, LIMA_PAGE_SIZE,
			&ldev->dlbu_dma, GFP_KERNEL | __GFP_NOWARN);
		अगर (!ldev->dlbu_cpu) अणु
			err = -ENOMEM;
			जाओ err_out2;
		पूर्ण
	पूर्ण अन्यथा
		ldev->बहु_पूर्ण = LIMA_VA_RESERVE_END;

	ldev->iomem = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(ldev->iomem)) अणु
		dev_err(ldev->dev, "fail to ioremap iomem\n");
		err = PTR_ERR(ldev->iomem);
		जाओ err_out3;
	पूर्ण

	क्रम (i = 0; i < lima_ip_num; i++) अणु
		err = lima_init_ip(ldev, i);
		अगर (err)
			जाओ err_out4;
	पूर्ण

	err = lima_init_gp_pipe(ldev);
	अगर (err)
		जाओ err_out4;

	err = lima_init_pp_pipe(ldev);
	अगर (err)
		जाओ err_out5;

	ldev->dump.magic = LIMA_DUMP_MAGIC;
	ldev->dump.version_major = LIMA_DUMP_MAJOR;
	ldev->dump.version_minor = LIMA_DUMP_MINOR;
	INIT_LIST_HEAD(&ldev->error_task_list);
	mutex_init(&ldev->error_task_list_lock);

	dev_info(ldev->dev, "bus rate = %lu\n", clk_get_rate(ldev->clk_bus));
	dev_info(ldev->dev, "mod rate = %lu", clk_get_rate(ldev->clk_gpu));

	वापस 0;

err_out5:
	lima_fini_gp_pipe(ldev);
err_out4:
	जबतक (--i >= 0)
		lima_fini_ip(ldev, i);
err_out3:
	अगर (ldev->dlbu_cpu)
		dma_मुक्त_wc(ldev->dev, LIMA_PAGE_SIZE,
			    ldev->dlbu_cpu, ldev->dlbu_dma);
err_out2:
	lima_vm_put(ldev->empty_vm);
err_out1:
	lima_regulator_fini(ldev);
err_out0:
	lima_clk_fini(ldev);
	वापस err;
पूर्ण

व्योम lima_device_fini(काष्ठा lima_device *ldev)
अणु
	पूर्णांक i;
	काष्ठा lima_sched_error_task *et, *पंचांगp;

	list_क्रम_each_entry_safe(et, पंचांगp, &ldev->error_task_list, list) अणु
		list_del(&et->list);
		kvमुक्त(et);
	पूर्ण
	mutex_destroy(&ldev->error_task_list_lock);

	lima_fini_pp_pipe(ldev);
	lima_fini_gp_pipe(ldev);

	क्रम (i = lima_ip_num - 1; i >= 0; i--)
		lima_fini_ip(ldev, i);

	अगर (ldev->dlbu_cpu)
		dma_मुक्त_wc(ldev->dev, LIMA_PAGE_SIZE,
			    ldev->dlbu_cpu, ldev->dlbu_dma);

	lima_vm_put(ldev->empty_vm);

	lima_regulator_fini(ldev);

	lima_clk_fini(ldev);
पूर्ण

पूर्णांक lima_device_resume(काष्ठा device *dev)
अणु
	काष्ठा lima_device *ldev = dev_get_drvdata(dev);
	पूर्णांक i, err;

	err = lima_clk_enable(ldev);
	अगर (err) अणु
		dev_err(dev, "resume clk fail %d\n", err);
		वापस err;
	पूर्ण

	err = lima_regulator_enable(ldev);
	अगर (err) अणु
		dev_err(dev, "resume regulator fail %d\n", err);
		जाओ err_out0;
	पूर्ण

	क्रम (i = 0; i < lima_ip_num; i++) अणु
		err = lima_resume_ip(ldev, i);
		अगर (err) अणु
			dev_err(dev, "resume ip %d fail\n", i);
			जाओ err_out1;
		पूर्ण
	पूर्ण

	err = lima_devfreq_resume(&ldev->devfreq);
	अगर (err) अणु
		dev_err(dev, "devfreq resume fail\n");
		जाओ err_out1;
	पूर्ण

	वापस 0;

err_out1:
	जबतक (--i >= 0)
		lima_suspend_ip(ldev, i);
	lima_regulator_disable(ldev);
err_out0:
	lima_clk_disable(ldev);
	वापस err;
पूर्ण

पूर्णांक lima_device_suspend(काष्ठा device *dev)
अणु
	काष्ठा lima_device *ldev = dev_get_drvdata(dev);
	पूर्णांक i, err;

	/* check any task running */
	क्रम (i = 0; i < lima_pipe_num; i++) अणु
		अगर (atomic_पढ़ो(&ldev->pipe[i].base.hw_rq_count))
			वापस -EBUSY;
	पूर्ण

	err = lima_devfreq_suspend(&ldev->devfreq);
	अगर (err) अणु
		dev_err(dev, "devfreq suspend fail\n");
		वापस err;
	पूर्ण

	क्रम (i = lima_ip_num - 1; i >= 0; i--)
		lima_suspend_ip(ldev, i);

	lima_regulator_disable(ldev);

	lima_clk_disable(ldev);

	वापस 0;
पूर्ण
