<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * TI AM33XX SRAM EMIF Driver
 *
 * Copyright (C) 2016-2017 Texas Instruments Inc.
 *	Dave Gerlach
 */

#समावेश <linux/err.h>
#समावेश <linux/genभाग.स>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sram.h>
#समावेश <linux/ti-emअगर-sram.h>

#समावेश "emif.h"

#घोषणा TI_EMIF_SRAM_SYMBOL_OFFSET(sym) ((अचिन्हित दीर्घ)(sym) - \
					 (अचिन्हित दीर्घ)&ti_emअगर_sram)

#घोषणा EMIF_POWER_MGMT_WAIT_SELF_REFRESH_8192_CYCLES		0x00a0

काष्ठा ti_emअगर_data अणु
	phys_addr_t ti_emअगर_sram_phys;
	phys_addr_t ti_emअगर_sram_data_phys;
	अचिन्हित दीर्घ ti_emअगर_sram_virt;
	अचिन्हित दीर्घ ti_emअगर_sram_data_virt;
	काष्ठा gen_pool *sram_pool_code;
	काष्ठा gen_pool	*sram_pool_data;
	काष्ठा ti_emअगर_pm_data pm_data;
	काष्ठा ti_emअगर_pm_functions pm_functions;
पूर्ण;

अटल काष्ठा ti_emअगर_data *emअगर_instance;

अटल u32 sram_suspend_address(काष्ठा ti_emअगर_data *emअगर_data,
				अचिन्हित दीर्घ addr)
अणु
	वापस (emअगर_data->ti_emअगर_sram_virt +
		TI_EMIF_SRAM_SYMBOL_OFFSET(addr));
पूर्ण

अटल phys_addr_t sram_resume_address(काष्ठा ti_emअगर_data *emअगर_data,
				       अचिन्हित दीर्घ addr)
अणु
	वापस ((अचिन्हित दीर्घ)emअगर_data->ti_emअगर_sram_phys +
		TI_EMIF_SRAM_SYMBOL_OFFSET(addr));
पूर्ण

अटल व्योम ti_emअगर_मुक्त_sram(काष्ठा ti_emअगर_data *emअगर_data)
अणु
	gen_pool_मुक्त(emअगर_data->sram_pool_code, emअगर_data->ti_emअगर_sram_virt,
		      ti_emअगर_sram_sz);
	gen_pool_मुक्त(emअगर_data->sram_pool_data,
		      emअगर_data->ti_emअगर_sram_data_virt,
		      माप(काष्ठा emअगर_regs_amx3));
पूर्ण

अटल पूर्णांक ti_emअगर_alloc_sram(काष्ठा device *dev,
			      काष्ठा ti_emअगर_data *emअगर_data)
अणु
	काष्ठा device_node *np = dev->of_node;
	पूर्णांक ret;

	emअगर_data->sram_pool_code = of_gen_pool_get(np, "sram", 0);
	अगर (!emअगर_data->sram_pool_code) अणु
		dev_err(dev, "Unable to get sram pool for ocmcram code\n");
		वापस -ENODEV;
	पूर्ण

	emअगर_data->ti_emअगर_sram_virt =
			gen_pool_alloc(emअगर_data->sram_pool_code,
				       ti_emअगर_sram_sz);
	अगर (!emअगर_data->ti_emअगर_sram_virt) अणु
		dev_err(dev, "Unable to allocate code memory from ocmcram\n");
		वापस -ENOMEM;
	पूर्ण

	/* Save physical address to calculate resume offset during pm init */
	emअगर_data->ti_emअगर_sram_phys =
			gen_pool_virt_to_phys(emअगर_data->sram_pool_code,
					      emअगर_data->ti_emअगर_sram_virt);

	/* Get sram pool क्रम data section and allocate space */
	emअगर_data->sram_pool_data = of_gen_pool_get(np, "sram", 1);
	अगर (!emअगर_data->sram_pool_data) अणु
		dev_err(dev, "Unable to get sram pool for ocmcram data\n");
		ret = -ENODEV;
		जाओ err_मुक्त_sram_code;
	पूर्ण

	emअगर_data->ti_emअगर_sram_data_virt =
				gen_pool_alloc(emअगर_data->sram_pool_data,
					       माप(काष्ठा emअगर_regs_amx3));
	अगर (!emअगर_data->ti_emअगर_sram_data_virt) अणु
		dev_err(dev, "Unable to allocate data memory from ocmcram\n");
		ret = -ENOMEM;
		जाओ err_मुक्त_sram_code;
	पूर्ण

	/* Save physical address to calculate resume offset during pm init */
	emअगर_data->ti_emअगर_sram_data_phys =
		gen_pool_virt_to_phys(emअगर_data->sram_pool_data,
				      emअगर_data->ti_emअगर_sram_data_virt);
	/*
	 * These functions are called during suspend path जबतक MMU is
	 * still on so add भव base to offset क्रम असलolute address
	 */
	emअगर_data->pm_functions.save_context =
		sram_suspend_address(emअगर_data,
				     (अचिन्हित दीर्घ)ti_emअगर_save_context);
	emअगर_data->pm_functions.enter_sr =
		sram_suspend_address(emअगर_data,
				     (अचिन्हित दीर्घ)ti_emअगर_enter_sr);
	emअगर_data->pm_functions.पात_sr =
		sram_suspend_address(emअगर_data,
				     (अचिन्हित दीर्घ)ti_emअगर_पात_sr);

	/*
	 * These are called during resume path when MMU is not enabled
	 * so physical address is used instead
	 */
	emअगर_data->pm_functions.restore_context =
		sram_resume_address(emअगर_data,
				    (अचिन्हित दीर्घ)ti_emअगर_restore_context);
	emअगर_data->pm_functions.निकास_sr =
		sram_resume_address(emअगर_data,
				    (अचिन्हित दीर्घ)ti_emअगर_निकास_sr);
	emअगर_data->pm_functions.run_hw_leveling =
		sram_resume_address(emअगर_data,
				    (अचिन्हित दीर्घ)ti_emअगर_run_hw_leveling);

	emअगर_data->pm_data.regs_virt =
		(काष्ठा emअगर_regs_amx3 *)emअगर_data->ti_emअगर_sram_data_virt;
	emअगर_data->pm_data.regs_phys = emअगर_data->ti_emअगर_sram_data_phys;

	वापस 0;

err_मुक्त_sram_code:
	gen_pool_मुक्त(emअगर_data->sram_pool_code, emअगर_data->ti_emअगर_sram_virt,
		      ti_emअगर_sram_sz);
	वापस ret;
पूर्ण

अटल पूर्णांक ti_emअगर_push_sram(काष्ठा device *dev, काष्ठा ti_emअगर_data *emअगर_data)
अणु
	व्योम *copy_addr;
	u32 data_addr;

	copy_addr = sram_exec_copy(emअगर_data->sram_pool_code,
				   (व्योम *)emअगर_data->ti_emअगर_sram_virt,
				   &ti_emअगर_sram, ti_emअगर_sram_sz);
	अगर (!copy_addr) अणु
		dev_err(dev, "Cannot copy emif code to sram\n");
		वापस -ENODEV;
	पूर्ण

	data_addr = sram_suspend_address(emअगर_data,
					 (अचिन्हित दीर्घ)&ti_emअगर_pm_sram_data);
	copy_addr = sram_exec_copy(emअगर_data->sram_pool_code,
				   (व्योम *)data_addr,
				   &emअगर_data->pm_data,
				   माप(emअगर_data->pm_data));
	अगर (!copy_addr) अणु
		dev_err(dev, "Cannot copy emif data to code sram\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Due to Usage Note 3.1.2 "DDR3: JEDEC Compliance क्रम Maximum
 * Self-Refresh Command Limit" found in AM335x Silicon Errata
 * (Document SPRZ360F Revised November 2013) we must configure
 * the self refresh delay समयr to 0xA (8192 cycles) to aव्योम
 * generating too many refresh command from the EMIF.
 */
अटल व्योम ti_emअगर_configure_sr_delay(काष्ठा ti_emअगर_data *emअगर_data)
अणु
	ग_लिखोl(EMIF_POWER_MGMT_WAIT_SELF_REFRESH_8192_CYCLES,
	       (emअगर_data->pm_data.ti_emअगर_base_addr_virt +
		EMIF_POWER_MANAGEMENT_CONTROL));

	ग_लिखोl(EMIF_POWER_MGMT_WAIT_SELF_REFRESH_8192_CYCLES,
	       (emअगर_data->pm_data.ti_emअगर_base_addr_virt +
		EMIF_POWER_MANAGEMENT_CTRL_SHDW));
पूर्ण

/**
 * ti_emअगर_copy_pm_function_table - copy mapping of pm funcs in sram
 * @sram_pool: poपूर्णांकer to काष्ठा gen_pool where dst resides
 * @dst: व्योम * to address that table should be copied
 *
 * Returns 0 अगर success other error code अगर table is not available
 */
पूर्णांक ti_emअगर_copy_pm_function_table(काष्ठा gen_pool *sram_pool, व्योम *dst)
अणु
	व्योम *copy_addr;

	अगर (!emअगर_instance)
		वापस -ENODEV;

	copy_addr = sram_exec_copy(sram_pool, dst,
				   &emअगर_instance->pm_functions,
				   माप(emअगर_instance->pm_functions));
	अगर (!copy_addr)
		वापस -ENODEV;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ti_emअगर_copy_pm_function_table);

/**
 * ti_emअगर_get_mem_type - वापस type क्रम memory type in use
 *
 * Returns memory type value पढ़ो from EMIF or error code अगर fails
 */
पूर्णांक ti_emअगर_get_mem_type(व्योम)
अणु
	अचिन्हित दीर्घ temp;

	अगर (!emअगर_instance)
		वापस -ENODEV;

	temp = पढ़ोl(emअगर_instance->pm_data.ti_emअगर_base_addr_virt +
		     EMIF_SDRAM_CONFIG);

	temp = (temp & SDRAM_TYPE_MASK) >> SDRAM_TYPE_SHIFT;
	वापस temp;
पूर्ण
EXPORT_SYMBOL_GPL(ti_emअगर_get_mem_type);

अटल स्थिर काष्ठा of_device_id ti_emअगर_of_match[] = अणु
	अणु .compatible = "ti,emif-am3352", .data =
					(व्योम *)EMIF_SRAM_AM33_REG_LAYOUT, पूर्ण,
	अणु .compatible = "ti,emif-am4372", .data =
					(व्योम *)EMIF_SRAM_AM43_REG_LAYOUT, पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ti_emअगर_of_match);

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक ti_emअगर_resume(काष्ठा device *dev)
अणु
	अचिन्हित दीर्घ पंचांगp =
			__raw_पढ़ोl((व्योम __iomem *)emअगर_instance->ti_emअगर_sram_virt);

	/*
	 * Check to see अगर what we are copying is alपढ़ोy present in the
	 * first byte at the destination, only copy अगर it is not which
	 * indicates we have lost context and sram no दीर्घer contains
	 * the PM code
	 */
	अगर (पंचांगp != ti_emअगर_sram)
		ti_emअगर_push_sram(dev, emअगर_instance);

	वापस 0;
पूर्ण

अटल पूर्णांक ti_emअगर_suspend(काष्ठा device *dev)
अणु
	/*
	 * The contents will be present in DDR hence no need to
	 * explicitly save
	 */
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल पूर्णांक ti_emअगर_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	काष्ठा resource *res;
	काष्ठा device *dev = &pdev->dev;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा ti_emअगर_data *emअगर_data;

	emअगर_data = devm_kzalloc(dev, माप(*emअगर_data), GFP_KERNEL);
	अगर (!emअगर_data)
		वापस -ENOMEM;

	match = of_match_device(ti_emअगर_of_match, &pdev->dev);
	अगर (!match)
		वापस -ENODEV;

	emअगर_data->pm_data.ti_emअगर_sram_config = (अचिन्हित दीर्घ)match->data;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	emअगर_data->pm_data.ti_emअगर_base_addr_virt = devm_ioremap_resource(dev,
									  res);
	अगर (IS_ERR(emअगर_data->pm_data.ti_emअगर_base_addr_virt)) अणु
		ret = PTR_ERR(emअगर_data->pm_data.ti_emअगर_base_addr_virt);
		वापस ret;
	पूर्ण

	emअगर_data->pm_data.ti_emअगर_base_addr_phys = res->start;

	ti_emअगर_configure_sr_delay(emअगर_data);

	ret = ti_emअगर_alloc_sram(dev, emअगर_data);
	अगर (ret)
		वापस ret;

	ret = ti_emअगर_push_sram(dev, emअगर_data);
	अगर (ret)
		जाओ fail_मुक्त_sram;

	emअगर_instance = emअगर_data;

	वापस 0;

fail_मुक्त_sram:
	ti_emअगर_मुक्त_sram(emअगर_data);

	वापस ret;
पूर्ण

अटल पूर्णांक ti_emअगर_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ti_emअगर_data *emअगर_data = emअगर_instance;

	emअगर_instance = शून्य;

	ti_emअगर_मुक्त_sram(emअगर_data);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops ti_emअगर_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(ti_emअगर_suspend, ti_emअगर_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver ti_emअगर_driver = अणु
	.probe = ti_emअगर_probe,
	.हटाओ = ti_emअगर_हटाओ,
	.driver = अणु
		.name = KBUILD_MODNAME,
		.of_match_table = ti_emअगर_of_match,
		.pm = &ti_emअगर_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(ti_emअगर_driver);

MODULE_AUTHOR("Dave Gerlach <d-gerlach@ti.com>");
MODULE_DESCRIPTION("Texas Instruments SRAM EMIF driver");
MODULE_LICENSE("GPL v2");
