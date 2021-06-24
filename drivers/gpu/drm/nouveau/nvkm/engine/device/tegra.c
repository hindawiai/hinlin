<शैली गुरु>
/*
 * Copyright (c) 2014, NVIDIA CORPORATION. All rights reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
#समावेश <core/tegra.h>
#अगर_घोषित CONFIG_NOUVEAU_PLATFORM_DRIVER
#समावेश "priv.h"

#अगर IS_ENABLED(CONFIG_ARM_DMA_USE_IOMMU)
#समावेश <यंत्र/dma-iommu.h>
#पूर्ण_अगर

अटल पूर्णांक
nvkm_device_tegra_घातer_up(काष्ठा nvkm_device_tegra *tdev)
अणु
	पूर्णांक ret;

	अगर (tdev->vdd) अणु
		ret = regulator_enable(tdev->vdd);
		अगर (ret)
			जाओ err_घातer;
	पूर्ण

	ret = clk_prepare_enable(tdev->clk);
	अगर (ret)
		जाओ err_clk;
	अगर (tdev->clk_ref) अणु
		ret = clk_prepare_enable(tdev->clk_ref);
		अगर (ret)
			जाओ err_clk_ref;
	पूर्ण
	ret = clk_prepare_enable(tdev->clk_pwr);
	अगर (ret)
		जाओ err_clk_pwr;
	clk_set_rate(tdev->clk_pwr, 204000000);
	udelay(10);

	अगर (!tdev->pdev->dev.pm_करोमुख्य) अणु
		reset_control_निश्चित(tdev->rst);
		udelay(10);

		ret = tegra_घातergate_हटाओ_clamping(TEGRA_POWERGATE_3D);
		अगर (ret)
			जाओ err_clamp;
		udelay(10);

		reset_control_deनिश्चित(tdev->rst);
		udelay(10);
	पूर्ण

	वापस 0;

err_clamp:
	clk_disable_unprepare(tdev->clk_pwr);
err_clk_pwr:
	अगर (tdev->clk_ref)
		clk_disable_unprepare(tdev->clk_ref);
err_clk_ref:
	clk_disable_unprepare(tdev->clk);
err_clk:
	अगर (tdev->vdd)
		regulator_disable(tdev->vdd);
err_घातer:
	वापस ret;
पूर्ण

अटल पूर्णांक
nvkm_device_tegra_घातer_करोwn(काष्ठा nvkm_device_tegra *tdev)
अणु
	पूर्णांक ret;

	clk_disable_unprepare(tdev->clk_pwr);
	अगर (tdev->clk_ref)
		clk_disable_unprepare(tdev->clk_ref);
	clk_disable_unprepare(tdev->clk);
	udelay(10);

	अगर (tdev->vdd) अणु
		ret = regulator_disable(tdev->vdd);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
nvkm_device_tegra_probe_iommu(काष्ठा nvkm_device_tegra *tdev)
अणु
#अगर IS_ENABLED(CONFIG_IOMMU_API)
	काष्ठा device *dev = &tdev->pdev->dev;
	अचिन्हित दीर्घ pgsize_biपंचांगap;
	पूर्णांक ret;

#अगर IS_ENABLED(CONFIG_ARM_DMA_USE_IOMMU)
	अगर (dev->archdata.mapping) अणु
		काष्ठा dma_iommu_mapping *mapping = to_dma_iommu_mapping(dev);

		arm_iommu_detach_device(dev);
		arm_iommu_release_mapping(mapping);
	पूर्ण
#पूर्ण_अगर

	अगर (!tdev->func->iommu_bit)
		वापस;

	mutex_init(&tdev->iommu.mutex);

	अगर (iommu_present(&platक्रमm_bus_type)) अणु
		tdev->iommu.करोमुख्य = iommu_करोमुख्य_alloc(&platक्रमm_bus_type);
		अगर (!tdev->iommu.करोमुख्य)
			जाओ error;

		/*
		 * A IOMMU is only usable अगर it supports page sizes smaller
		 * or equal to the प्रणाली's PAGE_SIZE, with a preference अगर
		 * both are equal.
		 */
		pgsize_biपंचांगap = tdev->iommu.करोमुख्य->ops->pgsize_biपंचांगap;
		अगर (pgsize_biपंचांगap & PAGE_SIZE) अणु
			tdev->iommu.pgshअगरt = PAGE_SHIFT;
		पूर्ण अन्यथा अणु
			tdev->iommu.pgshअगरt = fls(pgsize_biपंचांगap & ~PAGE_MASK);
			अगर (tdev->iommu.pgshअगरt == 0) अणु
				dev_warn(dev, "unsupported IOMMU page size\n");
				जाओ मुक्त_करोमुख्य;
			पूर्ण
			tdev->iommu.pgshअगरt -= 1;
		पूर्ण

		ret = iommu_attach_device(tdev->iommu.करोमुख्य, dev);
		अगर (ret)
			जाओ मुक्त_करोमुख्य;

		ret = nvkm_mm_init(&tdev->iommu.mm, 0, 0,
				   (1ULL << tdev->func->iommu_bit) >>
				   tdev->iommu.pgshअगरt, 1);
		अगर (ret)
			जाओ detach_device;
	पूर्ण

	वापस;

detach_device:
	iommu_detach_device(tdev->iommu.करोमुख्य, dev);

मुक्त_करोमुख्य:
	iommu_करोमुख्य_मुक्त(tdev->iommu.करोमुख्य);

error:
	tdev->iommu.करोमुख्य = शून्य;
	tdev->iommu.pgshअगरt = 0;
	dev_err(dev, "cannot initialize IOMMU MM\n");
#पूर्ण_अगर
पूर्ण

अटल व्योम
nvkm_device_tegra_हटाओ_iommu(काष्ठा nvkm_device_tegra *tdev)
अणु
#अगर IS_ENABLED(CONFIG_IOMMU_API)
	अगर (tdev->iommu.करोमुख्य) अणु
		nvkm_mm_fini(&tdev->iommu.mm);
		iommu_detach_device(tdev->iommu.करोमुख्य, tdev->device.dev);
		iommu_करोमुख्य_मुक्त(tdev->iommu.करोमुख्य);
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल काष्ठा nvkm_device_tegra *
nvkm_device_tegra(काष्ठा nvkm_device *device)
अणु
	वापस container_of(device, काष्ठा nvkm_device_tegra, device);
पूर्ण

अटल काष्ठा resource *
nvkm_device_tegra_resource(काष्ठा nvkm_device *device, अचिन्हित bar)
अणु
	काष्ठा nvkm_device_tegra *tdev = nvkm_device_tegra(device);
	वापस platक्रमm_get_resource(tdev->pdev, IORESOURCE_MEM, bar);
पूर्ण

अटल resource_माप_प्रकार
nvkm_device_tegra_resource_addr(काष्ठा nvkm_device *device, अचिन्हित bar)
अणु
	काष्ठा resource *res = nvkm_device_tegra_resource(device, bar);
	वापस res ? res->start : 0;
पूर्ण

अटल resource_माप_प्रकार
nvkm_device_tegra_resource_size(काष्ठा nvkm_device *device, अचिन्हित bar)
अणु
	काष्ठा resource *res = nvkm_device_tegra_resource(device, bar);
	वापस res ? resource_size(res) : 0;
पूर्ण

अटल irqवापस_t
nvkm_device_tegra_पूर्णांकr(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा nvkm_device_tegra *tdev = arg;
	काष्ठा nvkm_device *device = &tdev->device;
	bool handled = false;
	nvkm_mc_पूर्णांकr_unarm(device);
	nvkm_mc_पूर्णांकr(device, &handled);
	nvkm_mc_पूर्णांकr_rearm(device);
	वापस handled ? IRQ_HANDLED : IRQ_NONE;
पूर्ण

अटल व्योम
nvkm_device_tegra_fini(काष्ठा nvkm_device *device, bool suspend)
अणु
	काष्ठा nvkm_device_tegra *tdev = nvkm_device_tegra(device);
	अगर (tdev->irq) अणु
		मुक्त_irq(tdev->irq, tdev);
		tdev->irq = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक
nvkm_device_tegra_init(काष्ठा nvkm_device *device)
अणु
	काष्ठा nvkm_device_tegra *tdev = nvkm_device_tegra(device);
	पूर्णांक irq, ret;

	irq = platक्रमm_get_irq_byname(tdev->pdev, "stall");
	अगर (irq < 0)
		वापस irq;

	ret = request_irq(irq, nvkm_device_tegra_पूर्णांकr,
			  IRQF_SHARED, "nvkm", tdev);
	अगर (ret)
		वापस ret;

	tdev->irq = irq;
	वापस 0;
पूर्ण

अटल व्योम *
nvkm_device_tegra_dtor(काष्ठा nvkm_device *device)
अणु
	काष्ठा nvkm_device_tegra *tdev = nvkm_device_tegra(device);
	nvkm_device_tegra_घातer_करोwn(tdev);
	nvkm_device_tegra_हटाओ_iommu(tdev);
	वापस tdev;
पूर्ण

अटल स्थिर काष्ठा nvkm_device_func
nvkm_device_tegra_func = अणु
	.tegra = nvkm_device_tegra,
	.dtor = nvkm_device_tegra_dtor,
	.init = nvkm_device_tegra_init,
	.fini = nvkm_device_tegra_fini,
	.resource_addr = nvkm_device_tegra_resource_addr,
	.resource_size = nvkm_device_tegra_resource_size,
	.cpu_coherent = false,
पूर्ण;

पूर्णांक
nvkm_device_tegra_new(स्थिर काष्ठा nvkm_device_tegra_func *func,
		      काष्ठा platक्रमm_device *pdev,
		      स्थिर अक्षर *cfg, स्थिर अक्षर *dbg,
		      bool detect, bool mmio, u64 subdev_mask,
		      काष्ठा nvkm_device **pdevice)
अणु
	काष्ठा nvkm_device_tegra *tdev;
	अचिन्हित दीर्घ rate;
	पूर्णांक ret;

	अगर (!(tdev = kzalloc(माप(*tdev), GFP_KERNEL)))
		वापस -ENOMEM;

	tdev->func = func;
	tdev->pdev = pdev;

	अगर (func->require_vdd) अणु
		tdev->vdd = devm_regulator_get(&pdev->dev, "vdd");
		अगर (IS_ERR(tdev->vdd)) अणु
			ret = PTR_ERR(tdev->vdd);
			जाओ मुक्त;
		पूर्ण
	पूर्ण

	tdev->rst = devm_reset_control_get(&pdev->dev, "gpu");
	अगर (IS_ERR(tdev->rst)) अणु
		ret = PTR_ERR(tdev->rst);
		जाओ मुक्त;
	पूर्ण

	tdev->clk = devm_clk_get(&pdev->dev, "gpu");
	अगर (IS_ERR(tdev->clk)) अणु
		ret = PTR_ERR(tdev->clk);
		जाओ मुक्त;
	पूर्ण

	rate = clk_get_rate(tdev->clk);
	अगर (rate == 0) अणु
		ret = clk_set_rate(tdev->clk, अच_दीर्घ_उच्च);
		अगर (ret < 0)
			जाओ मुक्त;

		rate = clk_get_rate(tdev->clk);

		dev_dbg(&pdev->dev, "GPU clock set to %lu\n", rate);
	पूर्ण

	अगर (func->require_ref_clk)
		tdev->clk_ref = devm_clk_get(&pdev->dev, "ref");
	अगर (IS_ERR(tdev->clk_ref)) अणु
		ret = PTR_ERR(tdev->clk_ref);
		जाओ मुक्त;
	पूर्ण

	tdev->clk_pwr = devm_clk_get(&pdev->dev, "pwr");
	अगर (IS_ERR(tdev->clk_pwr)) अणु
		ret = PTR_ERR(tdev->clk_pwr);
		जाओ मुक्त;
	पूर्ण

	/**
	 * The IOMMU bit defines the upper limit of the GPU-addressable space.
	 */
	ret = dma_set_mask(&pdev->dev, DMA_BIT_MASK(tdev->func->iommu_bit));
	अगर (ret)
		जाओ मुक्त;

	nvkm_device_tegra_probe_iommu(tdev);

	ret = nvkm_device_tegra_घातer_up(tdev);
	अगर (ret)
		जाओ हटाओ;

	tdev->gpu_speeकरो = tegra_sku_info.gpu_speeकरो_value;
	tdev->gpu_speeकरो_id = tegra_sku_info.gpu_speeकरो_id;
	ret = nvkm_device_ctor(&nvkm_device_tegra_func, शून्य, &pdev->dev,
			       NVKM_DEVICE_TEGRA, pdev->id, शून्य,
			       cfg, dbg, detect, mmio, subdev_mask,
			       &tdev->device);
	अगर (ret)
		जाओ घातerकरोwn;

	*pdevice = &tdev->device;

	वापस 0;

घातerकरोwn:
	nvkm_device_tegra_घातer_करोwn(tdev);
हटाओ:
	nvkm_device_tegra_हटाओ_iommu(tdev);
मुक्त:
	kमुक्त(tdev);
	वापस ret;
पूर्ण
#अन्यथा
पूर्णांक
nvkm_device_tegra_new(स्थिर काष्ठा nvkm_device_tegra_func *func,
		      काष्ठा platक्रमm_device *pdev,
		      स्थिर अक्षर *cfg, स्थिर अक्षर *dbg,
		      bool detect, bool mmio, u64 subdev_mask,
		      काष्ठा nvkm_device **pdevice)
अणु
	वापस -ENOSYS;
पूर्ण
#पूर्ण_अगर
