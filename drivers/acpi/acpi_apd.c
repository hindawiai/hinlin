<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AMD ACPI support क्रम ACPI2platक्रमm device.
 *
 * Copyright (c) 2014,2015 AMD Corporation.
 * Authors: Ken Xue <Ken.Xue@amd.com>
 *	Wu, Jeff <Jeff.Wu@amd.com>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_data/clk-fch.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "internal.h"

काष्ठा apd_निजी_data;

/**
 * काष्ठा apd_device_desc - a descriptor क्रम apd device
 * @fixed_clk_rate: fixed rate input घड़ी source क्रम acpi device;
 *			0 means no fixed rate input घड़ी source
 * @properties: build-in properties of the device such as UART
 * @setup: a hook routine to set device resource during create platक्रमm device
 *
 * Device description defined as acpi_device_id.driver_data
 */
काष्ठा apd_device_desc अणु
	अचिन्हित पूर्णांक fixed_clk_rate;
	काष्ठा property_entry *properties;
	पूर्णांक (*setup)(काष्ठा apd_निजी_data *pdata);
पूर्ण;

काष्ठा apd_निजी_data अणु
	काष्ठा clk *clk;
	काष्ठा acpi_device *adev;
	स्थिर काष्ठा apd_device_desc *dev_desc;
पूर्ण;

#अगर defined(CONFIG_X86_AMD_PLATFORM_DEVICE) || defined(CONFIG_ARM64)
#घोषणा APD_ADDR(desc)	((अचिन्हित दीर्घ)&desc)

अटल पूर्णांक acpi_apd_setup(काष्ठा apd_निजी_data *pdata)
अणु
	स्थिर काष्ठा apd_device_desc *dev_desc = pdata->dev_desc;
	काष्ठा clk *clk;

	अगर (dev_desc->fixed_clk_rate) अणु
		clk = clk_रेजिस्टर_fixed_rate(&pdata->adev->dev,
					dev_name(&pdata->adev->dev),
					शून्य, 0, dev_desc->fixed_clk_rate);
		clk_रेजिस्टर_clkdev(clk, शून्य, dev_name(&pdata->adev->dev));
		pdata->clk = clk;
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_X86_AMD_PLATFORM_DEVICE
अटल पूर्णांक misc_check_res(काष्ठा acpi_resource *ares, व्योम *data)
अणु
	काष्ठा resource res;

	वापस !acpi_dev_resource_memory(ares, &res);
पूर्ण

अटल पूर्णांक fch_misc_setup(काष्ठा apd_निजी_data *pdata)
अणु
	काष्ठा acpi_device *adev = pdata->adev;
	स्थिर जोड़ acpi_object *obj;
	काष्ठा platक्रमm_device *clkdev;
	काष्ठा fch_clk_data *clk_data;
	काष्ठा resource_entry *rentry;
	काष्ठा list_head resource_list;
	पूर्णांक ret;

	clk_data = devm_kzalloc(&adev->dev, माप(*clk_data), GFP_KERNEL);
	अगर (!clk_data)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&resource_list);
	ret = acpi_dev_get_resources(adev, &resource_list, misc_check_res,
				     शून्य);
	अगर (ret < 0)
		वापस -ENOENT;

	अगर (!acpi_dev_get_property(adev, "is-rv", ACPI_TYPE_INTEGER, &obj))
		clk_data->is_rv = obj->पूर्णांकeger.value;

	list_क्रम_each_entry(rentry, &resource_list, node) अणु
		clk_data->base = devm_ioremap(&adev->dev, rentry->res->start,
					      resource_size(rentry->res));
		अवरोध;
	पूर्ण

	acpi_dev_मुक्त_resource_list(&resource_list);

	clkdev = platक्रमm_device_रेजिस्टर_data(&adev->dev, "clk-fch",
					       PLATFORM_DEVID_NONE, clk_data,
					       माप(*clk_data));
	वापस PTR_ERR_OR_ZERO(clkdev);
पूर्ण

अटल स्थिर काष्ठा apd_device_desc cz_i2c_desc = अणु
	.setup = acpi_apd_setup,
	.fixed_clk_rate = 133000000,
पूर्ण;

अटल स्थिर काष्ठा apd_device_desc wt_i2c_desc = अणु
	.setup = acpi_apd_setup,
	.fixed_clk_rate = 150000000,
पूर्ण;

अटल काष्ठा property_entry uart_properties[] = अणु
	PROPERTY_ENTRY_U32("reg-io-width", 4),
	PROPERTY_ENTRY_U32("reg-shift", 2),
	PROPERTY_ENTRY_BOOL("snps,uart-16550-compatible"),
	अणु पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा apd_device_desc cz_uart_desc = अणु
	.setup = acpi_apd_setup,
	.fixed_clk_rate = 48000000,
	.properties = uart_properties,
पूर्ण;

अटल स्थिर काष्ठा apd_device_desc fch_misc_desc = अणु
	.setup = fch_misc_setup,
पूर्ण;
#पूर्ण_अगर /* CONFIG_X86_AMD_PLATFORM_DEVICE */

#अगर_घोषित CONFIG_ARM64
अटल स्थिर काष्ठा apd_device_desc xgene_i2c_desc = अणु
	.setup = acpi_apd_setup,
	.fixed_clk_rate = 100000000,
पूर्ण;

अटल स्थिर काष्ठा apd_device_desc vulcan_spi_desc = अणु
	.setup = acpi_apd_setup,
	.fixed_clk_rate = 133000000,
पूर्ण;

अटल स्थिर काष्ठा apd_device_desc hip07_i2c_desc = अणु
	.setup = acpi_apd_setup,
	.fixed_clk_rate = 200000000,
पूर्ण;

अटल स्थिर काष्ठा apd_device_desc hip08_i2c_desc = अणु
	.setup = acpi_apd_setup,
	.fixed_clk_rate = 250000000,
पूर्ण;

अटल स्थिर काष्ठा apd_device_desc hip08_lite_i2c_desc = अणु
	.setup = acpi_apd_setup,
	.fixed_clk_rate = 125000000,
पूर्ण;

अटल स्थिर काष्ठा apd_device_desc thunderx2_i2c_desc = अणु
	.setup = acpi_apd_setup,
	.fixed_clk_rate = 125000000,
पूर्ण;

अटल स्थिर काष्ठा apd_device_desc nxp_i2c_desc = अणु
	.setup = acpi_apd_setup,
	.fixed_clk_rate = 350000000,
पूर्ण;

अटल स्थिर काष्ठा apd_device_desc hip08_spi_desc = अणु
	.setup = acpi_apd_setup,
	.fixed_clk_rate = 250000000,
पूर्ण;
#पूर्ण_अगर /* CONFIG_ARM64 */

#पूर्ण_अगर

/*
 * Create platक्रमm device during acpi scan attach handle.
 * Return value > 0 on success of creating device.
 */
अटल पूर्णांक acpi_apd_create_device(काष्ठा acpi_device *adev,
				   स्थिर काष्ठा acpi_device_id *id)
अणु
	स्थिर काष्ठा apd_device_desc *dev_desc = (व्योम *)id->driver_data;
	काष्ठा apd_निजी_data *pdata;
	काष्ठा platक्रमm_device *pdev;
	पूर्णांक ret;

	अगर (!dev_desc) अणु
		pdev = acpi_create_platक्रमm_device(adev, शून्य);
		वापस IS_ERR_OR_शून्य(pdev) ? PTR_ERR(pdev) : 1;
	पूर्ण

	pdata = kzalloc(माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस -ENOMEM;

	pdata->adev = adev;
	pdata->dev_desc = dev_desc;

	अगर (dev_desc->setup) अणु
		ret = dev_desc->setup(pdata);
		अगर (ret)
			जाओ err_out;
	पूर्ण

	adev->driver_data = pdata;
	pdev = acpi_create_platक्रमm_device(adev, dev_desc->properties);
	अगर (!IS_ERR_OR_शून्य(pdev))
		वापस 1;

	ret = PTR_ERR(pdev);
	adev->driver_data = शून्य;

 err_out:
	kमुक्त(pdata);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id acpi_apd_device_ids[] = अणु
	/* Generic apd devices */
#अगर_घोषित CONFIG_X86_AMD_PLATFORM_DEVICE
	अणु "AMD0010", APD_ADDR(cz_i2c_desc) पूर्ण,
	अणु "AMDI0010", APD_ADDR(wt_i2c_desc) पूर्ण,
	अणु "AMD0020", APD_ADDR(cz_uart_desc) पूर्ण,
	अणु "AMDI0020", APD_ADDR(cz_uart_desc) पूर्ण,
	अणु "AMDI0022", APD_ADDR(cz_uart_desc) पूर्ण,
	अणु "AMD0030", पूर्ण,
	अणु "AMD0040", APD_ADDR(fch_misc_desc)पूर्ण,
	अणु "HYGO0010", APD_ADDR(wt_i2c_desc) पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARM64
	अणु "APMC0D0F", APD_ADDR(xgene_i2c_desc) पूर्ण,
	अणु "BRCM900D", APD_ADDR(vulcan_spi_desc) पूर्ण,
	अणु "CAV900D",  APD_ADDR(vulcan_spi_desc) पूर्ण,
	अणु "CAV9007",  APD_ADDR(thunderx2_i2c_desc) पूर्ण,
	अणु "HISI02A1", APD_ADDR(hip07_i2c_desc) पूर्ण,
	अणु "HISI02A2", APD_ADDR(hip08_i2c_desc) पूर्ण,
	अणु "HISI02A3", APD_ADDR(hip08_lite_i2c_desc) पूर्ण,
	अणु "HISI0173", APD_ADDR(hip08_spi_desc) पूर्ण,
	अणु "NXP0001", APD_ADDR(nxp_i2c_desc) पूर्ण,
#पूर्ण_अगर
	अणु पूर्ण
पूर्ण;

अटल काष्ठा acpi_scan_handler apd_handler = अणु
	.ids = acpi_apd_device_ids,
	.attach = acpi_apd_create_device,
पूर्ण;

व्योम __init acpi_apd_init(व्योम)
अणु
	acpi_scan_add_handler(&apd_handler);
पूर्ण
