<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2013-2014, NVIDIA CORPORATION.  All rights reserved.
 */

#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/kobject.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/nvmem-consumer.h>
#समावेश <linux/nvmem-provider.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/sys_soc.h>

#समावेश <soc/tegra/common.h>
#समावेश <soc/tegra/fuse.h>

#समावेश "fuse.h"

काष्ठा tegra_sku_info tegra_sku_info;
EXPORT_SYMBOL(tegra_sku_info);

अटल स्थिर अक्षर *tegra_revision_name[TEGRA_REVISION_MAX] = अणु
	[TEGRA_REVISION_UNKNOWN] = "unknown",
	[TEGRA_REVISION_A01]     = "A01",
	[TEGRA_REVISION_A02]     = "A02",
	[TEGRA_REVISION_A03]     = "A03",
	[TEGRA_REVISION_A03p]    = "A03 prime",
	[TEGRA_REVISION_A04]     = "A04",
पूर्ण;

अटल स्थिर काष्ठा of_device_id car_match[] __initस्थिर = अणु
	अणु .compatible = "nvidia,tegra20-car", पूर्ण,
	अणु .compatible = "nvidia,tegra30-car", पूर्ण,
	अणु .compatible = "nvidia,tegra114-car", पूर्ण,
	अणु .compatible = "nvidia,tegra124-car", पूर्ण,
	अणु .compatible = "nvidia,tegra132-car", पूर्ण,
	अणु .compatible = "nvidia,tegra210-car", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा tegra_fuse *fuse = &(काष्ठा tegra_fuse) अणु
	.base = शून्य,
	.soc = शून्य,
पूर्ण;

अटल स्थिर काष्ठा of_device_id tegra_fuse_match[] = अणु
#अगर_घोषित CONFIG_ARCH_TEGRA_234_SOC
	अणु .compatible = "nvidia,tegra234-efuse", .data = &tegra234_fuse_soc पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_TEGRA_194_SOC
	अणु .compatible = "nvidia,tegra194-efuse", .data = &tegra194_fuse_soc पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_TEGRA_186_SOC
	अणु .compatible = "nvidia,tegra186-efuse", .data = &tegra186_fuse_soc पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_TEGRA_210_SOC
	अणु .compatible = "nvidia,tegra210-efuse", .data = &tegra210_fuse_soc पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_TEGRA_132_SOC
	अणु .compatible = "nvidia,tegra132-efuse", .data = &tegra124_fuse_soc पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_TEGRA_124_SOC
	अणु .compatible = "nvidia,tegra124-efuse", .data = &tegra124_fuse_soc पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_TEGRA_114_SOC
	अणु .compatible = "nvidia,tegra114-efuse", .data = &tegra114_fuse_soc पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_TEGRA_3x_SOC
	अणु .compatible = "nvidia,tegra30-efuse", .data = &tegra30_fuse_soc पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARCH_TEGRA_2x_SOC
	अणु .compatible = "nvidia,tegra20-efuse", .data = &tegra20_fuse_soc पूर्ण,
#पूर्ण_अगर
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल पूर्णांक tegra_fuse_पढ़ो(व्योम *priv, अचिन्हित पूर्णांक offset, व्योम *value,
			   माप_प्रकार bytes)
अणु
	अचिन्हित पूर्णांक count = bytes / 4, i;
	काष्ठा tegra_fuse *fuse = priv;
	u32 *buffer = value;

	क्रम (i = 0; i < count; i++)
		buffer[i] = fuse->पढ़ो(fuse, offset + i * 4);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nvmem_cell_info tegra_fuse_cells[] = अणु
	अणु
		.name = "tsensor-cpu1",
		.offset = 0x084,
		.bytes = 4,
		.bit_offset = 0,
		.nbits = 32,
	पूर्ण, अणु
		.name = "tsensor-cpu2",
		.offset = 0x088,
		.bytes = 4,
		.bit_offset = 0,
		.nbits = 32,
	पूर्ण, अणु
		.name = "tsensor-cpu0",
		.offset = 0x098,
		.bytes = 4,
		.bit_offset = 0,
		.nbits = 32,
	पूर्ण, अणु
		.name = "xusb-pad-calibration",
		.offset = 0x0f0,
		.bytes = 4,
		.bit_offset = 0,
		.nbits = 32,
	पूर्ण, अणु
		.name = "tsensor-cpu3",
		.offset = 0x12c,
		.bytes = 4,
		.bit_offset = 0,
		.nbits = 32,
	पूर्ण, अणु
		.name = "sata-calibration",
		.offset = 0x124,
		.bytes = 1,
		.bit_offset = 0,
		.nbits = 2,
	पूर्ण, अणु
		.name = "tsensor-gpu",
		.offset = 0x154,
		.bytes = 4,
		.bit_offset = 0,
		.nbits = 32,
	पूर्ण, अणु
		.name = "tsensor-mem0",
		.offset = 0x158,
		.bytes = 4,
		.bit_offset = 0,
		.nbits = 32,
	पूर्ण, अणु
		.name = "tsensor-mem1",
		.offset = 0x15c,
		.bytes = 4,
		.bit_offset = 0,
		.nbits = 32,
	पूर्ण, अणु
		.name = "tsensor-pllx",
		.offset = 0x160,
		.bytes = 4,
		.bit_offset = 0,
		.nbits = 32,
	पूर्ण, अणु
		.name = "tsensor-common",
		.offset = 0x180,
		.bytes = 4,
		.bit_offset = 0,
		.nbits = 32,
	पूर्ण, अणु
		.name = "tsensor-realignment",
		.offset = 0x1fc,
		.bytes = 4,
		.bit_offset = 0,
		.nbits = 32,
	पूर्ण, अणु
		.name = "gpu-calibration",
		.offset = 0x204,
		.bytes = 4,
		.bit_offset = 0,
		.nbits = 32,
	पूर्ण, अणु
		.name = "xusb-pad-calibration-ext",
		.offset = 0x250,
		.bytes = 4,
		.bit_offset = 0,
		.nbits = 32,
	पूर्ण,
पूर्ण;

अटल पूर्णांक tegra_fuse_probe(काष्ठा platक्रमm_device *pdev)
अणु
	व्योम __iomem *base = fuse->base;
	काष्ठा nvmem_config nvmem;
	काष्ठा resource *res;
	पूर्णांक err;

	/* take over the memory region from the early initialization */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	fuse->phys = res->start;
	fuse->base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(fuse->base)) अणु
		err = PTR_ERR(fuse->base);
		fuse->base = base;
		वापस err;
	पूर्ण

	fuse->clk = devm_clk_get(&pdev->dev, "fuse");
	अगर (IS_ERR(fuse->clk)) अणु
		अगर (PTR_ERR(fuse->clk) != -EPROBE_DEFER)
			dev_err(&pdev->dev, "failed to get FUSE clock: %ld",
				PTR_ERR(fuse->clk));

		fuse->base = base;
		वापस PTR_ERR(fuse->clk);
	पूर्ण

	platक्रमm_set_drvdata(pdev, fuse);
	fuse->dev = &pdev->dev;

	अगर (fuse->soc->probe) अणु
		err = fuse->soc->probe(fuse);
		अगर (err < 0)
			जाओ restore;
	पूर्ण

	स_रखो(&nvmem, 0, माप(nvmem));
	nvmem.dev = &pdev->dev;
	nvmem.name = "fuse";
	nvmem.id = -1;
	nvmem.owner = THIS_MODULE;
	nvmem.cells = tegra_fuse_cells;
	nvmem.ncells = ARRAY_SIZE(tegra_fuse_cells);
	nvmem.type = NVMEM_TYPE_OTP;
	nvmem.पढ़ो_only = true;
	nvmem.root_only = true;
	nvmem.reg_पढ़ो = tegra_fuse_पढ़ो;
	nvmem.size = fuse->soc->info->size;
	nvmem.word_size = 4;
	nvmem.stride = 4;
	nvmem.priv = fuse;

	fuse->nvmem = devm_nvmem_रेजिस्टर(&pdev->dev, &nvmem);
	अगर (IS_ERR(fuse->nvmem)) अणु
		err = PTR_ERR(fuse->nvmem);
		dev_err(&pdev->dev, "failed to register NVMEM device: %d\n",
			err);
		जाओ restore;
	पूर्ण

	/* release the early I/O memory mapping */
	iounmap(base);

	वापस 0;

restore:
	fuse->base = base;
	वापस err;
पूर्ण

अटल काष्ठा platक्रमm_driver tegra_fuse_driver = अणु
	.driver = अणु
		.name = "tegra-fuse",
		.of_match_table = tegra_fuse_match,
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe = tegra_fuse_probe,
पूर्ण;
builtin_platक्रमm_driver(tegra_fuse_driver);

bool __init tegra_fuse_पढ़ो_spare(अचिन्हित पूर्णांक spare)
अणु
	अचिन्हित पूर्णांक offset = fuse->soc->info->spare + spare * 4;

	वापस fuse->पढ़ो_early(fuse, offset) & 1;
पूर्ण

u32 __init tegra_fuse_पढ़ो_early(अचिन्हित पूर्णांक offset)
अणु
	वापस fuse->पढ़ो_early(fuse, offset);
पूर्ण

पूर्णांक tegra_fuse_पढ़ोl(अचिन्हित दीर्घ offset, u32 *value)
अणु
	अगर (!fuse->पढ़ो || !fuse->clk)
		वापस -EPROBE_DEFER;

	अगर (IS_ERR(fuse->clk))
		वापस PTR_ERR(fuse->clk);

	*value = fuse->पढ़ो(fuse, offset);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(tegra_fuse_पढ़ोl);

अटल व्योम tegra_enable_fuse_clk(व्योम __iomem *base)
अणु
	u32 reg;

	reg = पढ़ोl_relaxed(base + 0x48);
	reg |= 1 << 28;
	ग_लिखोl(reg, base + 0x48);

	/*
	 * Enable FUSE घड़ी. This needs to be hardcoded because the घड़ी
	 * subप्रणाली is not active during early boot.
	 */
	reg = पढ़ोl(base + 0x14);
	reg |= 1 << 7;
	ग_लिखोl(reg, base + 0x14);
पूर्ण

अटल sमाप_प्रकार major_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", tegra_get_major_rev());
पूर्ण

अटल DEVICE_ATTR_RO(major);

अटल sमाप_प्रकार minor_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", tegra_get_minor_rev());
पूर्ण

अटल DEVICE_ATTR_RO(minor);

अटल काष्ठा attribute *tegra_soc_attr[] = अणु
	&dev_attr_major.attr,
	&dev_attr_minor.attr,
	शून्य,
पूर्ण;

स्थिर काष्ठा attribute_group tegra_soc_attr_group = अणु
	.attrs = tegra_soc_attr,
पूर्ण;

#अगर IS_ENABLED(CONFIG_ARCH_TEGRA_194_SOC) || \
    IS_ENABLED(CONFIG_ARCH_TEGRA_234_SOC)
अटल sमाप_प्रकार platक्रमm_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	/*
	 * Displays the value in the 'pre_si_platform' field of the HIDREV
	 * रेजिस्टर क्रम Tegra194 devices. A value of 0 indicates that the
	 * platक्रमm type is silicon and all other non-zero values indicate
	 * the type of simulation platक्रमm is being used.
	 */
	वापस प्र_लिखो(buf, "%d\n", tegra_get_platक्रमm());
पूर्ण

अटल DEVICE_ATTR_RO(platक्रमm);

अटल काष्ठा attribute *tegra194_soc_attr[] = अणु
	&dev_attr_major.attr,
	&dev_attr_minor.attr,
	&dev_attr_platक्रमm.attr,
	शून्य,
पूर्ण;

स्थिर काष्ठा attribute_group tegra194_soc_attr_group = अणु
	.attrs = tegra194_soc_attr,
पूर्ण;
#पूर्ण_अगर

काष्ठा device * __init tegra_soc_device_रेजिस्टर(व्योम)
अणु
	काष्ठा soc_device_attribute *attr;
	काष्ठा soc_device *dev;

	attr = kzalloc(माप(*attr), GFP_KERNEL);
	अगर (!attr)
		वापस शून्य;

	attr->family = kaप्र_लिखो(GFP_KERNEL, "Tegra");
	attr->revision = kaप्र_लिखो(GFP_KERNEL, "%s",
		tegra_revision_name[tegra_sku_info.revision]);
	attr->soc_id = kaप्र_लिखो(GFP_KERNEL, "%u", tegra_get_chip_id());
	attr->custom_attr_group = fuse->soc->soc_attr_group;

	dev = soc_device_रेजिस्टर(attr);
	अगर (IS_ERR(dev)) अणु
		kमुक्त(attr->soc_id);
		kमुक्त(attr->revision);
		kमुक्त(attr->family);
		kमुक्त(attr);
		वापस ERR_CAST(dev);
	पूर्ण

	वापस soc_device_to_device(dev);
पूर्ण

अटल पूर्णांक __init tegra_init_fuse(व्योम)
अणु
	स्थिर काष्ठा of_device_id *match;
	काष्ठा device_node *np;
	काष्ठा resource regs;

	tegra_init_apbmisc();

	np = of_find_matching_node_and_match(शून्य, tegra_fuse_match, &match);
	अगर (!np) अणु
		/*
		 * Fall back to legacy initialization क्रम 32-bit ARM only. All
		 * 64-bit ARM device tree files क्रम Tegra are required to have
		 * a FUSE node.
		 *
		 * This is क्रम backwards-compatibility with old device trees
		 * that didn't contain a FUSE node.
		 */
		अगर (IS_ENABLED(CONFIG_ARM) && soc_is_tegra()) अणु
			u8 chip = tegra_get_chip_id();

			regs.start = 0x7000f800;
			regs.end = 0x7000fbff;
			regs.flags = IORESOURCE_MEM;

			चयन (chip) अणु
#अगर_घोषित CONFIG_ARCH_TEGRA_2x_SOC
			हाल TEGRA20:
				fuse->soc = &tegra20_fuse_soc;
				अवरोध;
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_TEGRA_3x_SOC
			हाल TEGRA30:
				fuse->soc = &tegra30_fuse_soc;
				अवरोध;
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_TEGRA_114_SOC
			हाल TEGRA114:
				fuse->soc = &tegra114_fuse_soc;
				अवरोध;
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_TEGRA_124_SOC
			हाल TEGRA124:
				fuse->soc = &tegra124_fuse_soc;
				अवरोध;
#पूर्ण_अगर

			शेष:
				pr_warn("Unsupported SoC: %02x\n", chip);
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			 * At this poपूर्णांक we're not running on Tegra, so play
			 * nice with multi-platक्रमm kernels.
			 */
			वापस 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * Extract inक्रमmation from the device tree अगर we've found a
		 * matching node.
		 */
		अगर (of_address_to_resource(np, 0, &regs) < 0) अणु
			pr_err("failed to get FUSE register\n");
			वापस -ENXIO;
		पूर्ण

		fuse->soc = match->data;
	पूर्ण

	np = of_find_matching_node(शून्य, car_match);
	अगर (np) अणु
		व्योम __iomem *base = of_iomap(np, 0);
		अगर (base) अणु
			tegra_enable_fuse_clk(base);
			iounmap(base);
		पूर्ण अन्यथा अणु
			pr_err("failed to map clock registers\n");
			वापस -ENXIO;
		पूर्ण
	पूर्ण

	fuse->base = ioremap(regs.start, resource_size(&regs));
	अगर (!fuse->base) अणु
		pr_err("failed to map FUSE registers\n");
		वापस -ENXIO;
	पूर्ण

	fuse->soc->init(fuse);

	pr_info("Tegra Revision: %s SKU: %d CPU Process: %d SoC Process: %d\n",
		tegra_revision_name[tegra_sku_info.revision],
		tegra_sku_info.sku_id, tegra_sku_info.cpu_process_id,
		tegra_sku_info.soc_process_id);
	pr_debug("Tegra CPU Speedo ID %d, SoC Speedo ID %d\n",
		 tegra_sku_info.cpu_speeकरो_id, tegra_sku_info.soc_speeकरो_id);

	अगर (fuse->soc->lookups) अणु
		माप_प्रकार size = माप(*fuse->lookups) * fuse->soc->num_lookups;

		fuse->lookups = kmemdup(fuse->soc->lookups, size, GFP_KERNEL);
		अगर (!fuse->lookups)
			वापस -ENOMEM;

		nvmem_add_cell_lookups(fuse->lookups, fuse->soc->num_lookups);
	पूर्ण

	वापस 0;
पूर्ण
early_initcall(tegra_init_fuse);

#अगर_घोषित CONFIG_ARM64
अटल पूर्णांक __init tegra_init_soc(व्योम)
अणु
	काष्ठा device_node *np;
	काष्ठा device *soc;

	/* make sure we're running on Tegra */
	np = of_find_matching_node(शून्य, tegra_fuse_match);
	अगर (!np)
		वापस 0;

	of_node_put(np);

	soc = tegra_soc_device_रेजिस्टर();
	अगर (IS_ERR(soc)) अणु
		pr_err("failed to register SoC device: %ld\n", PTR_ERR(soc));
		वापस PTR_ERR(soc);
	पूर्ण

	वापस 0;
पूर्ण
device_initcall(tegra_init_soc);
#पूर्ण_अगर
