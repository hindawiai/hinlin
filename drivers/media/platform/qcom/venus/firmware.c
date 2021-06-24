<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2017 Linaro Ltd.
 */

#समावेश <linux/device.h>
#समावेश <linux/firmware.h>
#समावेश <linux/kernel.h>
#समावेश <linux/iommu.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of_device.h>
#समावेश <linux/qcom_scm.h>
#समावेश <linux/sizes.h>
#समावेश <linux/soc/qcom/mdt_loader.h>

#समावेश "core.h"
#समावेश "firmware.h"
#समावेश "hfi_venus_io.h"

#घोषणा VENUS_PAS_ID			9
#घोषणा VENUS_FW_MEM_SIZE		(6 * SZ_1M)
#घोषणा VENUS_FW_START_ADDR		0x0

अटल व्योम venus_reset_cpu(काष्ठा venus_core *core)
अणु
	u32 fw_size = core->fw.mapped_mem_size;
	व्योम __iomem *wrapper_base = core->wrapper_base;

	ग_लिखोl(0, wrapper_base + WRAPPER_FW_START_ADDR);
	ग_लिखोl(fw_size, wrapper_base + WRAPPER_FW_END_ADDR);
	ग_लिखोl(0, wrapper_base + WRAPPER_CPA_START_ADDR);
	ग_लिखोl(fw_size, wrapper_base + WRAPPER_CPA_END_ADDR);
	ग_लिखोl(fw_size, wrapper_base + WRAPPER_NONPIX_START_ADDR);
	ग_लिखोl(fw_size, wrapper_base + WRAPPER_NONPIX_END_ADDR);
	ग_लिखोl(0x0, wrapper_base + WRAPPER_CPU_CGC_DIS);
	ग_लिखोl(0x0, wrapper_base + WRAPPER_CPU_CLOCK_CONFIG);

	/* Bring ARM9 out of reset */
	ग_लिखोl(0, wrapper_base + WRAPPER_A9SS_SW_RESET);
पूर्ण

पूर्णांक venus_set_hw_state(काष्ठा venus_core *core, bool resume)
अणु
	पूर्णांक ret;

	अगर (core->use_tz) अणु
		ret = qcom_scm_set_remote_state(resume, 0);
		अगर (resume && ret == -EINVAL)
			ret = 0;
		वापस ret;
	पूर्ण

	अगर (resume) अणु
		venus_reset_cpu(core);
	पूर्ण अन्यथा अणु
		अगर (!IS_V6(core))
			ग_लिखोl(1, core->wrapper_base + WRAPPER_A9SS_SW_RESET);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक venus_load_fw(काष्ठा venus_core *core, स्थिर अक्षर *fwname,
			 phys_addr_t *mem_phys, माप_प्रकार *mem_size)
अणु
	स्थिर काष्ठा firmware *mdt;
	काष्ठा device_node *node;
	काष्ठा device *dev;
	काष्ठा resource r;
	sमाप_प्रकार fw_size;
	व्योम *mem_va;
	पूर्णांक ret;

	*mem_phys = 0;
	*mem_size = 0;

	dev = core->dev;
	node = of_parse_phandle(dev->of_node, "memory-region", 0);
	अगर (!node) अणु
		dev_err(dev, "no memory-region specified\n");
		वापस -EINVAL;
	पूर्ण

	ret = of_address_to_resource(node, 0, &r);
	अगर (ret)
		जाओ err_put_node;

	ret = request_firmware(&mdt, fwname, dev);
	अगर (ret < 0)
		जाओ err_put_node;

	fw_size = qcom_mdt_get_size(mdt);
	अगर (fw_size < 0) अणु
		ret = fw_size;
		जाओ err_release_fw;
	पूर्ण

	*mem_phys = r.start;
	*mem_size = resource_size(&r);

	अगर (*mem_size < fw_size || fw_size > VENUS_FW_MEM_SIZE) अणु
		ret = -EINVAL;
		जाओ err_release_fw;
	पूर्ण

	mem_va = memremap(r.start, *mem_size, MEMREMAP_WC);
	अगर (!mem_va) अणु
		dev_err(dev, "unable to map memory region: %pR\n", &r);
		ret = -ENOMEM;
		जाओ err_release_fw;
	पूर्ण

	अगर (core->use_tz)
		ret = qcom_mdt_load(dev, mdt, fwname, VENUS_PAS_ID,
				    mem_va, *mem_phys, *mem_size, शून्य);
	अन्यथा
		ret = qcom_mdt_load_no_init(dev, mdt, fwname, VENUS_PAS_ID,
					    mem_va, *mem_phys, *mem_size, शून्य);

	memunmap(mem_va);
err_release_fw:
	release_firmware(mdt);
err_put_node:
	of_node_put(node);
	वापस ret;
पूर्ण

अटल पूर्णांक venus_boot_no_tz(काष्ठा venus_core *core, phys_addr_t mem_phys,
			    माप_प्रकार mem_size)
अणु
	काष्ठा iommu_करोमुख्य *iommu;
	काष्ठा device *dev;
	पूर्णांक ret;

	dev = core->fw.dev;
	अगर (!dev)
		वापस -EPROBE_DEFER;

	iommu = core->fw.iommu_करोमुख्य;
	core->fw.mapped_mem_size = mem_size;

	ret = iommu_map(iommu, VENUS_FW_START_ADDR, mem_phys, mem_size,
			IOMMU_READ | IOMMU_WRITE | IOMMU_PRIV);
	अगर (ret) अणु
		dev_err(dev, "could not map video firmware region\n");
		वापस ret;
	पूर्ण

	venus_reset_cpu(core);

	वापस 0;
पूर्ण

अटल पूर्णांक venus_shutकरोwn_no_tz(काष्ठा venus_core *core)
अणु
	स्थिर माप_प्रकार mapped = core->fw.mapped_mem_size;
	काष्ठा iommu_करोमुख्य *iommu;
	माप_प्रकार unmapped;
	u32 reg;
	काष्ठा device *dev = core->fw.dev;
	व्योम __iomem *wrapper_base = core->wrapper_base;

	/* Assert the reset to ARM9 */
	reg = पढ़ोl_relaxed(wrapper_base + WRAPPER_A9SS_SW_RESET);
	reg |= WRAPPER_A9SS_SW_RESET_BIT;
	ग_लिखोl_relaxed(reg, wrapper_base + WRAPPER_A9SS_SW_RESET);

	/* Make sure reset is निश्चितed beक्रमe the mapping is हटाओd */
	mb();

	iommu = core->fw.iommu_करोमुख्य;

	अगर (core->fw.mapped_mem_size && iommu) अणु
		unmapped = iommu_unmap(iommu, VENUS_FW_START_ADDR, mapped);

		अगर (unmapped != mapped)
			dev_err(dev, "failed to unmap firmware\n");
		अन्यथा
			core->fw.mapped_mem_size = 0;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक venus_boot(काष्ठा venus_core *core)
अणु
	काष्ठा device *dev = core->dev;
	स्थिर काष्ठा venus_resources *res = core->res;
	स्थिर अक्षर *fwpath = शून्य;
	phys_addr_t mem_phys;
	माप_प्रकार mem_size;
	पूर्णांक ret;

	अगर (!IS_ENABLED(CONFIG_QCOM_MDT_LOADER) ||
	    (core->use_tz && !qcom_scm_is_available()))
		वापस -EPROBE_DEFER;

	ret = of_property_पढ़ो_string_index(dev->of_node, "firmware-name", 0,
					    &fwpath);
	अगर (ret)
		fwpath = core->res->fwname;

	ret = venus_load_fw(core, fwpath, &mem_phys, &mem_size);
	अगर (ret) अणु
		dev_err(dev, "fail to load video firmware\n");
		वापस -EINVAL;
	पूर्ण

	core->fw.mem_size = mem_size;
	core->fw.mem_phys = mem_phys;

	अगर (core->use_tz)
		ret = qcom_scm_pas_auth_and_reset(VENUS_PAS_ID);
	अन्यथा
		ret = venus_boot_no_tz(core, mem_phys, mem_size);

	अगर (ret)
		वापस ret;

	अगर (core->use_tz && res->cp_size) अणु
		ret = qcom_scm_mem_protect_video_var(res->cp_start,
						     res->cp_size,
						     res->cp_nonpixel_start,
						     res->cp_nonpixel_size);
		अगर (ret) अणु
			qcom_scm_pas_shutकरोwn(VENUS_PAS_ID);
			dev_err(dev, "set virtual address ranges fail (%d)\n",
				ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक venus_shutकरोwn(काष्ठा venus_core *core)
अणु
	पूर्णांक ret;

	अगर (core->use_tz)
		ret = qcom_scm_pas_shutकरोwn(VENUS_PAS_ID);
	अन्यथा
		ret = venus_shutकरोwn_no_tz(core);

	वापस ret;
पूर्ण

पूर्णांक venus_firmware_init(काष्ठा venus_core *core)
अणु
	काष्ठा platक्रमm_device_info info;
	काष्ठा iommu_करोमुख्य *iommu_करोm;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा device_node *np;
	पूर्णांक ret;

	np = of_get_child_by_name(core->dev->of_node, "video-firmware");
	अगर (!np) अणु
		core->use_tz = true;
		वापस 0;
	पूर्ण

	स_रखो(&info, 0, माप(info));
	info.fwnode = &np->fwnode;
	info.parent = core->dev;
	info.name = np->name;
	info.dma_mask = DMA_BIT_MASK(32);

	pdev = platक्रमm_device_रेजिस्टर_full(&info);
	अगर (IS_ERR(pdev)) अणु
		of_node_put(np);
		वापस PTR_ERR(pdev);
	पूर्ण

	pdev->dev.of_node = np;

	ret = of_dma_configure(&pdev->dev, np, true);
	अगर (ret) अणु
		dev_err(core->dev, "dma configure fail\n");
		जाओ err_unरेजिस्टर;
	पूर्ण

	core->fw.dev = &pdev->dev;

	iommu_करोm = iommu_करोमुख्य_alloc(&platक्रमm_bus_type);
	अगर (!iommu_करोm) अणु
		dev_err(core->fw.dev, "Failed to allocate iommu domain\n");
		ret = -ENOMEM;
		जाओ err_unरेजिस्टर;
	पूर्ण

	ret = iommu_attach_device(iommu_करोm, core->fw.dev);
	अगर (ret) अणु
		dev_err(core->fw.dev, "could not attach device\n");
		जाओ err_iommu_मुक्त;
	पूर्ण

	core->fw.iommu_करोमुख्य = iommu_करोm;

	of_node_put(np);

	वापस 0;

err_iommu_मुक्त:
	iommu_करोमुख्य_मुक्त(iommu_करोm);
err_unरेजिस्टर:
	platक्रमm_device_unरेजिस्टर(pdev);
	of_node_put(np);
	वापस ret;
पूर्ण

व्योम venus_firmware_deinit(काष्ठा venus_core *core)
अणु
	काष्ठा iommu_करोमुख्य *iommu;

	अगर (!core->fw.dev)
		वापस;

	iommu = core->fw.iommu_करोमुख्य;

	iommu_detach_device(iommu, core->fw.dev);

	अगर (core->fw.iommu_करोमुख्य) अणु
		iommu_करोमुख्य_मुक्त(iommu);
		core->fw.iommu_करोमुख्य = शून्य;
	पूर्ण

	platक्रमm_device_unरेजिस्टर(to_platक्रमm_device(core->fw.dev));
पूर्ण
