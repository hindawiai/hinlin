<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Intel Quark MFD PCI driver क्रम I2C & GPIO
 *
 * Copyright(c) 2014 Intel Corporation.
 *
 * Intel Quark PCI device क्रम I2C and GPIO controller sharing the same
 * PCI function. This PCI driver will split the 2 devices पूर्णांकo their
 * respective drivers.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/dmi.h>
#समावेश <linux/i2c.h>
#समावेश <linux/platक्रमm_data/gpio-dwapb.h>
#समावेश <linux/property.h>

/* PCI BAR क्रम रेजिस्टर base address */
#घोषणा MFD_I2C_BAR		0
#घोषणा MFD_GPIO_BAR		1

/* ACPI _ADR value to match the child node */
#घोषणा MFD_ACPI_MATCH_GPIO	0ULL
#घोषणा MFD_ACPI_MATCH_I2C	1ULL

/* The base GPIO number under GPIOLIB framework */
#घोषणा INTEL_QUARK_MFD_GPIO_BASE	8

/* The शेष number of South-Cluster GPIO on Quark. */
#घोषणा INTEL_QUARK_MFD_NGPIO		8

/* The DesignWare GPIO ports on Quark. */
#घोषणा INTEL_QUARK_GPIO_NPORTS	1

#घोषणा INTEL_QUARK_IORES_MEM	0
#घोषणा INTEL_QUARK_IORES_IRQ	1

#घोषणा INTEL_QUARK_I2C_CONTROLLER_CLK "i2c_designware.0"

/* The Quark I2C controller source घड़ी */
#घोषणा INTEL_QUARK_I2C_CLK_HZ	33000000

काष्ठा पूर्णांकel_quark_mfd अणु
	काष्ठा clk		*i2c_clk;
	काष्ठा clk_lookup	*i2c_clk_lookup;
पूर्ण;

अटल स्थिर काष्ठा property_entry पूर्णांकel_quark_i2c_controller_standard_properties[] = अणु
	PROPERTY_ENTRY_U32("clock-frequency", I2C_MAX_STANDARD_MODE_FREQ),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा software_node पूर्णांकel_quark_i2c_controller_standard_node = अणु
	.name = "intel-quark-i2c-controller",
	.properties = पूर्णांकel_quark_i2c_controller_standard_properties,
पूर्ण;

अटल स्थिर काष्ठा property_entry पूर्णांकel_quark_i2c_controller_fast_properties[] = अणु
	PROPERTY_ENTRY_U32("clock-frequency", I2C_MAX_FAST_MODE_FREQ),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा software_node पूर्णांकel_quark_i2c_controller_fast_node = अणु
	.name = "intel-quark-i2c-controller",
	.properties = पूर्णांकel_quark_i2c_controller_fast_properties,
पूर्ण;

अटल स्थिर काष्ठा dmi_प्रणाली_id dmi_platक्रमm_info[] = अणु
	अणु
		.matches = अणु
			DMI_EXACT_MATCH(DMI_BOARD_NAME, "Galileo"),
		पूर्ण,
		.driver_data = (व्योम *)&पूर्णांकel_quark_i2c_controller_standard_node,
	पूर्ण,
	अणु
		.matches = अणु
			DMI_EXACT_MATCH(DMI_BOARD_NAME, "GalileoGen2"),
		पूर्ण,
		.driver_data = (व्योम *)&पूर्णांकel_quark_i2c_controller_fast_node,
	पूर्ण,
	अणु
		.matches = अणु
			DMI_EXACT_MATCH(DMI_BOARD_NAME, "SIMATIC IOT2000"),
		पूर्ण,
		.driver_data = (व्योम *)&पूर्णांकel_quark_i2c_controller_fast_node,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

/* This is used as a place holder and will be modअगरied at run-समय */
अटल काष्ठा resource पूर्णांकel_quark_i2c_res[] = अणु
	[INTEL_QUARK_IORES_MEM] = अणु
		.flags = IORESOURCE_MEM,
	पूर्ण,
	[INTEL_QUARK_IORES_IRQ] = अणु
		.flags = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा mfd_cell_acpi_match पूर्णांकel_quark_acpi_match_i2c = अणु
	.adr = MFD_ACPI_MATCH_I2C,
पूर्ण;

/* This is used as a place holder and will be modअगरied at run-समय */
अटल काष्ठा resource पूर्णांकel_quark_gpio_res[] = अणु
	[INTEL_QUARK_IORES_MEM] = अणु
		.flags = IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा mfd_cell_acpi_match पूर्णांकel_quark_acpi_match_gpio = अणु
	.adr = MFD_ACPI_MATCH_GPIO,
पूर्ण;

अटल काष्ठा mfd_cell पूर्णांकel_quark_mfd_cells[] = अणु
	[MFD_I2C_BAR] = अणु
		.id = MFD_I2C_BAR,
		.name = "i2c_designware",
		.acpi_match = &पूर्णांकel_quark_acpi_match_i2c,
		.num_resources = ARRAY_SIZE(पूर्णांकel_quark_i2c_res),
		.resources = पूर्णांकel_quark_i2c_res,
		.ignore_resource_conflicts = true,
	पूर्ण,
	[MFD_GPIO_BAR] = अणु
		.id = MFD_GPIO_BAR,
		.name = "gpio-dwapb",
		.acpi_match = &पूर्णांकel_quark_acpi_match_gpio,
		.num_resources = ARRAY_SIZE(पूर्णांकel_quark_gpio_res),
		.resources = पूर्णांकel_quark_gpio_res,
		.ignore_resource_conflicts = true,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id पूर्णांकel_quark_mfd_ids[] = अणु
	अणु PCI_VDEVICE(INTEL, 0x0934), पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, पूर्णांकel_quark_mfd_ids);

अटल पूर्णांक पूर्णांकel_quark_रेजिस्टर_i2c_clk(काष्ठा device *dev)
अणु
	काष्ठा पूर्णांकel_quark_mfd *quark_mfd = dev_get_drvdata(dev);
	काष्ठा clk *i2c_clk;

	i2c_clk = clk_रेजिस्टर_fixed_rate(dev,
					  INTEL_QUARK_I2C_CONTROLLER_CLK, शून्य,
					  0, INTEL_QUARK_I2C_CLK_HZ);
	अगर (IS_ERR(i2c_clk))
		वापस PTR_ERR(i2c_clk);

	quark_mfd->i2c_clk = i2c_clk;
	quark_mfd->i2c_clk_lookup = clkdev_create(i2c_clk, शून्य,
						INTEL_QUARK_I2C_CONTROLLER_CLK);

	अगर (!quark_mfd->i2c_clk_lookup) अणु
		clk_unरेजिस्टर(quark_mfd->i2c_clk);
		dev_err(dev, "Fixed clk register failed\n");
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम पूर्णांकel_quark_unरेजिस्टर_i2c_clk(काष्ठा device *dev)
अणु
	काष्ठा पूर्णांकel_quark_mfd *quark_mfd = dev_get_drvdata(dev);

	अगर (!quark_mfd->i2c_clk_lookup)
		वापस;

	clkdev_drop(quark_mfd->i2c_clk_lookup);
	clk_unरेजिस्टर(quark_mfd->i2c_clk);
पूर्ण

अटल पूर्णांक पूर्णांकel_quark_i2c_setup(काष्ठा pci_dev *pdev)
अणु
	काष्ठा mfd_cell *cell = &पूर्णांकel_quark_mfd_cells[MFD_I2C_BAR];
	काष्ठा resource *res = पूर्णांकel_quark_i2c_res;
	स्थिर काष्ठा dmi_प्रणाली_id *dmi_id;

	res[INTEL_QUARK_IORES_MEM].start = pci_resource_start(pdev, MFD_I2C_BAR);
	res[INTEL_QUARK_IORES_MEM].end = pci_resource_end(pdev, MFD_I2C_BAR);

	res[INTEL_QUARK_IORES_IRQ].start = pci_irq_vector(pdev, 0);
	res[INTEL_QUARK_IORES_IRQ].end = pci_irq_vector(pdev, 0);

	/* Normal mode by शेष */
	cell->swnode = &पूर्णांकel_quark_i2c_controller_standard_node;

	dmi_id = dmi_first_match(dmi_platक्रमm_info);
	अगर (dmi_id)
		cell->swnode = (काष्ठा software_node *)dmi_id->driver_data;

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_quark_gpio_setup(काष्ठा pci_dev *pdev)
अणु
	काष्ठा mfd_cell *cell = &पूर्णांकel_quark_mfd_cells[MFD_GPIO_BAR];
	काष्ठा resource *res = पूर्णांकel_quark_gpio_res;
	काष्ठा dwapb_platक्रमm_data *pdata;
	काष्ठा device *dev = &pdev->dev;

	res[INTEL_QUARK_IORES_MEM].start = pci_resource_start(pdev, MFD_GPIO_BAR);
	res[INTEL_QUARK_IORES_MEM].end = pci_resource_end(pdev, MFD_GPIO_BAR);

	pdata = devm_kzalloc(dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस -ENOMEM;

	/* For पूर्णांकel quark x1000, it has only one port: portA */
	pdata->nports = INTEL_QUARK_GPIO_NPORTS;
	pdata->properties = devm_kसुस्मृति(dev, pdata->nports,
					 माप(*pdata->properties),
					 GFP_KERNEL);
	अगर (!pdata->properties)
		वापस -ENOMEM;

	/* Set the properties क्रम portA */
	pdata->properties->fwnode	= शून्य;
	pdata->properties->idx		= 0;
	pdata->properties->ngpio	= INTEL_QUARK_MFD_NGPIO;
	pdata->properties->gpio_base	= INTEL_QUARK_MFD_GPIO_BASE;
	pdata->properties->irq[0]	= pci_irq_vector(pdev, 0);
	pdata->properties->irq_shared	= true;

	cell->platक्रमm_data = pdata;
	cell->pdata_size = माप(*pdata);

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_quark_mfd_probe(काष्ठा pci_dev *pdev,
				 स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा पूर्णांकel_quark_mfd *quark_mfd;
	पूर्णांक ret;

	ret = pcim_enable_device(pdev);
	अगर (ret)
		वापस ret;

	quark_mfd = devm_kzalloc(&pdev->dev, माप(*quark_mfd), GFP_KERNEL);
	अगर (!quark_mfd)
		वापस -ENOMEM;

	dev_set_drvdata(&pdev->dev, quark_mfd);

	ret = पूर्णांकel_quark_रेजिस्टर_i2c_clk(&pdev->dev);
	अगर (ret)
		वापस ret;

	pci_set_master(pdev);

	/* This driver only requires 1 IRQ vector */
	ret = pci_alloc_irq_vectors(pdev, 1, 1, PCI_IRQ_ALL_TYPES);
	अगर (ret < 0)
		जाओ err_unरेजिस्टर_i2c_clk;

	ret = पूर्णांकel_quark_i2c_setup(pdev);
	अगर (ret)
		जाओ err_मुक्त_irq_vectors;

	ret = पूर्णांकel_quark_gpio_setup(pdev);
	अगर (ret)
		जाओ err_मुक्त_irq_vectors;

	ret = mfd_add_devices(&pdev->dev, 0, पूर्णांकel_quark_mfd_cells,
			      ARRAY_SIZE(पूर्णांकel_quark_mfd_cells), शून्य, 0,
			      शून्य);
	अगर (ret)
		जाओ err_मुक्त_irq_vectors;

	वापस 0;

err_मुक्त_irq_vectors:
	pci_मुक्त_irq_vectors(pdev);
err_unरेजिस्टर_i2c_clk:
	पूर्णांकel_quark_unरेजिस्टर_i2c_clk(&pdev->dev);
	वापस ret;
पूर्ण

अटल व्योम पूर्णांकel_quark_mfd_हटाओ(काष्ठा pci_dev *pdev)
अणु
	mfd_हटाओ_devices(&pdev->dev);
	pci_मुक्त_irq_vectors(pdev);
	पूर्णांकel_quark_unरेजिस्टर_i2c_clk(&pdev->dev);
पूर्ण

अटल काष्ठा pci_driver पूर्णांकel_quark_mfd_driver = अणु
	.name		= "intel_quark_mfd_i2c_gpio",
	.id_table	= पूर्णांकel_quark_mfd_ids,
	.probe		= पूर्णांकel_quark_mfd_probe,
	.हटाओ		= पूर्णांकel_quark_mfd_हटाओ,
पूर्ण;

module_pci_driver(पूर्णांकel_quark_mfd_driver);

MODULE_AUTHOR("Raymond Tan <raymond.tan@intel.com>");
MODULE_DESCRIPTION("Intel Quark MFD PCI driver for I2C & GPIO");
MODULE_LICENSE("GPL v2");
