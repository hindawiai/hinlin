<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम the Intel Broxton PMC
 *
 * (C) Copyright 2014 - 2020 Intel Corporation
 *
 * This driver is based on Intel SCU IPC driver (पूर्णांकel_scu_ipc.c) by
 * Sreedhara DS <sreedhara.ds@पूर्णांकel.com>
 *
 * The PMC (Power Management Controller) running on the ARC processor
 * communicates with another entity running in the IA (Intel Architecture)
 * core through an IPC (Intel Processor Communications) mechanism which in
 * turn sends messages between the IA and the PMC.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/io-64-nonatomic-lo-hi.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/पूर्णांकel_pmc_bxt.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/platक्रमm_data/itco_wdt.h>

#समावेश <यंत्र/पूर्णांकel_scu_ipc.h>

/* Residency with घड़ी rate at 19.2MHz to usecs */
#घोषणा S0IX_RESIDENCY_IN_USECS(d, s)		\
(अणु						\
	u64 result = 10ull * ((d) + (s));	\
	करो_भाग(result, 192);			\
	result;					\
पूर्ण)

/* Resources exported from IFWI */
#घोषणा PLAT_RESOURCE_IPC_INDEX		0
#घोषणा PLAT_RESOURCE_IPC_SIZE		0x1000
#घोषणा PLAT_RESOURCE_GCR_OFFSET	0x1000
#घोषणा PLAT_RESOURCE_GCR_SIZE		0x1000
#घोषणा PLAT_RESOURCE_BIOS_DATA_INDEX	1
#घोषणा PLAT_RESOURCE_BIOS_IFACE_INDEX	2
#घोषणा PLAT_RESOURCE_TELEM_SSRAM_INDEX	3
#घोषणा PLAT_RESOURCE_ISP_DATA_INDEX	4
#घोषणा PLAT_RESOURCE_ISP_IFACE_INDEX	5
#घोषणा PLAT_RESOURCE_GTD_DATA_INDEX	6
#घोषणा PLAT_RESOURCE_GTD_IFACE_INDEX	7
#घोषणा PLAT_RESOURCE_ACPI_IO_INDEX	0

/*
 * BIOS करोes not create an ACPI device क्रम each PMC function, but
 * exports multiple resources from one ACPI device (IPC) क्रम multiple
 * functions. This driver is responsible क्रम creating a child device and
 * to export resources क्रम those functions.
 */
#घोषणा SMI_EN_OFFSET			0x0040
#घोषणा SMI_EN_SIZE			4
#घोषणा TCO_BASE_OFFSET			0x0060
#घोषणा TCO_REGS_SIZE			16
#घोषणा TELEM_SSRAM_SIZE		240
#घोषणा TELEM_PMC_SSRAM_OFFSET		0x1b00
#घोषणा TELEM_PUNIT_SSRAM_OFFSET	0x1a00

/* Commands */
#घोषणा PMC_NORTHPEAK_CTRL		0xed

अटल अंतरभूत bool is_gcr_valid(u32 offset)
अणु
	वापस offset < PLAT_RESOURCE_GCR_SIZE - 8;
पूर्ण

/**
 * पूर्णांकel_pmc_gcr_पढ़ो64() - Read a 64-bit PMC GCR रेजिस्टर
 * @pmc: PMC device poपूर्णांकer
 * @offset: offset of GCR रेजिस्टर from GCR address base
 * @data: data poपूर्णांकer क्रम storing the रेजिस्टर output
 *
 * Reads the 64-bit PMC GCR रेजिस्टर at given offset.
 *
 * Return: Negative value on error or 0 on success.
 */
पूर्णांक पूर्णांकel_pmc_gcr_पढ़ो64(काष्ठा पूर्णांकel_pmc_dev *pmc, u32 offset, u64 *data)
अणु
	अगर (!is_gcr_valid(offset))
		वापस -EINVAL;

	spin_lock(&pmc->gcr_lock);
	*data = पढ़ोq(pmc->gcr_mem_base + offset);
	spin_unlock(&pmc->gcr_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(पूर्णांकel_pmc_gcr_पढ़ो64);

/**
 * पूर्णांकel_pmc_gcr_update() - Update PMC GCR रेजिस्टर bits
 * @pmc: PMC device poपूर्णांकer
 * @offset: offset of GCR रेजिस्टर from GCR address base
 * @mask: bit mask क्रम update operation
 * @val: update value
 *
 * Updates the bits of given GCR रेजिस्टर as specअगरied by
 * @mask and @val.
 *
 * Return: Negative value on error or 0 on success.
 */
पूर्णांक पूर्णांकel_pmc_gcr_update(काष्ठा पूर्णांकel_pmc_dev *pmc, u32 offset, u32 mask, u32 val)
अणु
	u32 new_val;

	अगर (!is_gcr_valid(offset))
		वापस -EINVAL;

	spin_lock(&pmc->gcr_lock);
	new_val = पढ़ोl(pmc->gcr_mem_base + offset);

	new_val = (new_val & ~mask) | (val & mask);
	ग_लिखोl(new_val, pmc->gcr_mem_base + offset);

	new_val = पढ़ोl(pmc->gcr_mem_base + offset);
	spin_unlock(&pmc->gcr_lock);

	/* Check whether the bit update is successful */
	वापस (new_val & mask) != (val & mask) ? -EIO : 0;
पूर्ण
EXPORT_SYMBOL_GPL(पूर्णांकel_pmc_gcr_update);

/**
 * पूर्णांकel_pmc_s0ix_counter_पढ़ो() - Read S0ix residency
 * @pmc: PMC device poपूर्णांकer
 * @data: Out param that contains current S0ix residency count.
 *
 * Writes to @data how many usecs the प्रणाली has been in low-घातer S0ix
 * state.
 *
 * Return: An error code or 0 on success.
 */
पूर्णांक पूर्णांकel_pmc_s0ix_counter_पढ़ो(काष्ठा पूर्णांकel_pmc_dev *pmc, u64 *data)
अणु
	u64 deep, shlw;

	spin_lock(&pmc->gcr_lock);
	deep = पढ़ोq(pmc->gcr_mem_base + PMC_GCR_TELEM_DEEP_S0IX_REG);
	shlw = पढ़ोq(pmc->gcr_mem_base + PMC_GCR_TELEM_SHLW_S0IX_REG);
	spin_unlock(&pmc->gcr_lock);

	*data = S0IX_RESIDENCY_IN_USECS(deep, shlw);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(पूर्णांकel_pmc_s0ix_counter_पढ़ो);

/**
 * simplecmd_store() - Send a simple IPC command
 * @dev: Device under the attribute is
 * @attr: Attribute in question
 * @buf: Buffer holding data to be stored to the attribute
 * @count: Number of bytes in @buf
 *
 * Expects a string with two पूर्णांकegers separated with space. These two
 * values hold command and subcommand that is send to PMC.
 *
 * Return: Number number of bytes written (@count) or negative त्रुटि_सं in
 *	   हाल of error.
 */
अटल sमाप_प्रकार simplecmd_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा पूर्णांकel_pmc_dev *pmc = dev_get_drvdata(dev);
	काष्ठा पूर्णांकel_scu_ipc_dev *scu = pmc->scu;
	पूर्णांक subcmd;
	पूर्णांक cmd;
	पूर्णांक ret;

	ret = माला_पूछो(buf, "%d %d", &cmd, &subcmd);
	अगर (ret != 2) अणु
		dev_err(dev, "Invalid values, expected: cmd subcmd\n");
		वापस -EINVAL;
	पूर्ण

	ret = पूर्णांकel_scu_ipc_dev_simple_command(scu, cmd, subcmd);
	अगर (ret)
		वापस ret;

	वापस count;
पूर्ण
अटल DEVICE_ATTR_WO(simplecmd);

/**
 * northpeak_store() - Enable or disable Northpeak
 * @dev: Device under the attribute is
 * @attr: Attribute in question
 * @buf: Buffer holding data to be stored to the attribute
 * @count: Number of bytes in @buf
 *
 * Expects an अचिन्हित पूर्णांकeger. Non-zero enables Northpeak and zero
 * disables it.
 *
 * Return: Number number of bytes written (@count) or negative त्रुटि_सं in
 *	   हाल of error.
 */
अटल sमाप_प्रकार northpeak_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा पूर्णांकel_pmc_dev *pmc = dev_get_drvdata(dev);
	काष्ठा पूर्णांकel_scu_ipc_dev *scu = pmc->scu;
	अचिन्हित दीर्घ val;
	पूर्णांक subcmd;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 0, &val);
	अगर (ret)
		वापस ret;

	/* Northpeak is enabled अगर subcmd == 1 and disabled अगर it is 0 */
	अगर (val)
		subcmd = 1;
	अन्यथा
		subcmd = 0;

	ret = पूर्णांकel_scu_ipc_dev_simple_command(scu, PMC_NORTHPEAK_CTRL, subcmd);
	अगर (ret)
		वापस ret;

	वापस count;
पूर्ण
अटल DEVICE_ATTR_WO(northpeak);

अटल काष्ठा attribute *पूर्णांकel_pmc_attrs[] = अणु
	&dev_attr_northpeak.attr,
	&dev_attr_simplecmd.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group पूर्णांकel_pmc_group = अणु
	.attrs = पूर्णांकel_pmc_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *पूर्णांकel_pmc_groups[] = अणु
	&पूर्णांकel_pmc_group,
	शून्य
पूर्ण;

अटल काष्ठा resource punit_res[6];

अटल काष्ठा mfd_cell punit = अणु
	.name = "intel_punit_ipc",
	.resources = punit_res,
पूर्ण;

अटल काष्ठा itco_wdt_platक्रमm_data tco_pdata = अणु
	.name = "Apollo Lake SoC",
	.version = 5,
	.no_reboot_use_pmc = true,
पूर्ण;

अटल काष्ठा resource tco_res[2];

अटल स्थिर काष्ठा mfd_cell tco = अणु
	.name = "iTCO_wdt",
	.ignore_resource_conflicts = true,
	.resources = tco_res,
	.num_resources = ARRAY_SIZE(tco_res),
	.platक्रमm_data = &tco_pdata,
	.pdata_size = माप(tco_pdata),
पूर्ण;

अटल स्थिर काष्ठा resource telem_res[] = अणु
	DEFINE_RES_MEM(TELEM_PUNIT_SSRAM_OFFSET, TELEM_SSRAM_SIZE),
	DEFINE_RES_MEM(TELEM_PMC_SSRAM_OFFSET, TELEM_SSRAM_SIZE),
पूर्ण;

अटल स्थिर काष्ठा mfd_cell telem = अणु
	.name = "intel_telemetry",
	.resources = telem_res,
	.num_resources = ARRAY_SIZE(telem_res),
पूर्ण;

अटल पूर्णांक पूर्णांकel_pmc_get_tco_resources(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;

	अगर (acpi_has_watchकरोg())
		वापस 0;

	res = platक्रमm_get_resource(pdev, IORESOURCE_IO,
				    PLAT_RESOURCE_ACPI_IO_INDEX);
	अगर (!res) अणु
		dev_err(&pdev->dev, "Failed to get IO resource\n");
		वापस -EINVAL;
	पूर्ण

	tco_res[0].flags = IORESOURCE_IO;
	tco_res[0].start = res->start + TCO_BASE_OFFSET;
	tco_res[0].end = tco_res[0].start + TCO_REGS_SIZE - 1;
	tco_res[1].flags = IORESOURCE_IO;
	tco_res[1].start = res->start + SMI_EN_OFFSET;
	tco_res[1].end = tco_res[1].start + SMI_EN_SIZE - 1;

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_pmc_get_resources(काष्ठा platक्रमm_device *pdev,
				   काष्ठा पूर्णांकel_pmc_dev *pmc,
				   काष्ठा पूर्णांकel_scu_ipc_data *scu_data)
अणु
	काष्ठा resource gcr_res;
	माप_प्रकार npunit_res = 0;
	काष्ठा resource *res;
	पूर्णांक ret;

	scu_data->irq = platक्रमm_get_irq_optional(pdev, 0);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM,
				    PLAT_RESOURCE_IPC_INDEX);
	अगर (!res) अणु
		dev_err(&pdev->dev, "Failed to get IPC resource\n");
		वापस -EINVAL;
	पूर्ण

	/* IPC रेजिस्टरs */
	scu_data->mem.flags = res->flags;
	scu_data->mem.start = res->start;
	scu_data->mem.end = res->start + PLAT_RESOURCE_IPC_SIZE - 1;

	/* GCR रेजिस्टरs */
	gcr_res.flags = res->flags;
	gcr_res.start = res->start + PLAT_RESOURCE_GCR_OFFSET;
	gcr_res.end = gcr_res.start + PLAT_RESOURCE_GCR_SIZE - 1;

	pmc->gcr_mem_base = devm_ioremap_resource(&pdev->dev, &gcr_res);
	अगर (IS_ERR(pmc->gcr_mem_base))
		वापस PTR_ERR(pmc->gcr_mem_base);

	/* Only रेजिस्टर iTCO watchकरोg अगर there is no WDAT ACPI table */
	ret = पूर्णांकel_pmc_get_tco_resources(pdev);
	अगर (ret)
		वापस ret;

	/* BIOS data रेजिस्टर */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM,
				    PLAT_RESOURCE_BIOS_DATA_INDEX);
	अगर (!res) अणु
		dev_err(&pdev->dev, "Failed to get resource of P-unit BIOS data\n");
		वापस -EINVAL;
	पूर्ण
	punit_res[npunit_res++] = *res;

	/* BIOS पूर्णांकerface रेजिस्टर */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM,
				    PLAT_RESOURCE_BIOS_IFACE_INDEX);
	अगर (!res) अणु
		dev_err(&pdev->dev, "Failed to get resource of P-unit BIOS interface\n");
		वापस -EINVAL;
	पूर्ण
	punit_res[npunit_res++] = *res;

	/* ISP data रेजिस्टर, optional */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM,
				    PLAT_RESOURCE_ISP_DATA_INDEX);
	अगर (res)
		punit_res[npunit_res++] = *res;

	/* ISP पूर्णांकerface रेजिस्टर, optional */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM,
				    PLAT_RESOURCE_ISP_IFACE_INDEX);
	अगर (res)
		punit_res[npunit_res++] = *res;

	/* GTD data रेजिस्टर, optional */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM,
				    PLAT_RESOURCE_GTD_DATA_INDEX);
	अगर (res)
		punit_res[npunit_res++] = *res;

	/* GTD पूर्णांकerface रेजिस्टर, optional */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM,
				    PLAT_RESOURCE_GTD_IFACE_INDEX);
	अगर (res)
		punit_res[npunit_res++] = *res;

	punit.num_resources = npunit_res;

	/* Telemetry SSRAM is optional */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM,
				    PLAT_RESOURCE_TELEM_SSRAM_INDEX);
	अगर (res)
		pmc->telem_base = res;

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_pmc_create_devices(काष्ठा पूर्णांकel_pmc_dev *pmc)
अणु
	पूर्णांक ret;

	अगर (!acpi_has_watchकरोg()) अणु
		ret = devm_mfd_add_devices(pmc->dev, PLATFORM_DEVID_AUTO, &tco,
					   1, शून्य, 0, शून्य);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = devm_mfd_add_devices(pmc->dev, PLATFORM_DEVID_AUTO, &punit, 1,
				   शून्य, 0, शून्य);
	अगर (ret)
		वापस ret;

	अगर (pmc->telem_base) अणु
		ret = devm_mfd_add_devices(pmc->dev, PLATFORM_DEVID_AUTO,
					   &telem, 1, pmc->telem_base, 0, शून्य);
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id पूर्णांकel_pmc_acpi_ids[] = अणु
	अणु "INT34D2" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, पूर्णांकel_pmc_acpi_ids);

अटल पूर्णांक पूर्णांकel_pmc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा पूर्णांकel_scu_ipc_data scu_data = अणुपूर्ण;
	काष्ठा पूर्णांकel_pmc_dev *pmc;
	पूर्णांक ret;

	pmc = devm_kzalloc(&pdev->dev, माप(*pmc), GFP_KERNEL);
	अगर (!pmc)
		वापस -ENOMEM;

	pmc->dev = &pdev->dev;
	spin_lock_init(&pmc->gcr_lock);

	ret = पूर्णांकel_pmc_get_resources(pdev, pmc, &scu_data);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to request resources\n");
		वापस ret;
	पूर्ण

	pmc->scu = devm_पूर्णांकel_scu_ipc_रेजिस्टर(&pdev->dev, &scu_data);
	अगर (IS_ERR(pmc->scu))
		वापस PTR_ERR(pmc->scu);

	platक्रमm_set_drvdata(pdev, pmc);

	ret = पूर्णांकel_pmc_create_devices(pmc);
	अगर (ret)
		dev_err(&pdev->dev, "Failed to create PMC devices\n");

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver पूर्णांकel_pmc_driver = अणु
	.probe = पूर्णांकel_pmc_probe,
	.driver = अणु
		.name = "intel_pmc_bxt",
		.acpi_match_table = पूर्णांकel_pmc_acpi_ids,
		.dev_groups = पूर्णांकel_pmc_groups,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(पूर्णांकel_pmc_driver);

MODULE_AUTHOR("Mika Westerberg <mika.westerberg@linux.intel.com>");
MODULE_AUTHOR("Zha Qipeng <qipeng.zha@intel.com>");
MODULE_DESCRIPTION("Intel Broxton PMC driver");
MODULE_LICENSE("GPL v2");
