<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2020 Nicolas Saenz Julienne <nsaenzjulienne@suse.de>
 */

#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/nvmem-provider.h>
#समावेश <linux/of_reserved_स्मृति.स>
#समावेश <linux/platक्रमm_device.h>

काष्ठा rmem अणु
	काष्ठा device *dev;
	काष्ठा nvmem_device *nvmem;
	काष्ठा reserved_mem *mem;

	phys_addr_t size;
पूर्ण;

अटल पूर्णांक rmem_पढ़ो(व्योम *context, अचिन्हित पूर्णांक offset,
		     व्योम *val, माप_प्रकार bytes)
अणु
	काष्ठा rmem *priv = context;
	माप_प्रकार available = priv->mem->size;
	loff_t off = offset;
	व्योम *addr;
	पूर्णांक count;

	/*
	 * Only map the reserved memory at this poपूर्णांक to aव्योम potential rogue
	 * kernel thपढ़ोs inadvertently modअगरying it. Based on the current
	 * uses-हालs क्रम this driver, the perक्रमmance hit isn't a concern.
	 * Nor is likely to be, given the nature of the subप्रणाली. Most nvmem
	 * devices operate over slow buses to begin with.
	 *
	 * An alternative would be setting the memory as RO, set_memory_ro(),
	 * but as of Dec 2020 this isn't possible on arm64.
	 */
	addr = memremap(priv->mem->base, available, MEMREMAP_WB);
	अगर (IS_ERR(addr)) अणु
		dev_err(priv->dev, "Failed to remap memory region\n");
		वापस PTR_ERR(addr);
	पूर्ण

	count = memory_पढ़ो_from_buffer(val, bytes, &off, addr, available);

	memunmap(addr);

	वापस count;
पूर्ण

अटल पूर्णांक rmem_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा nvmem_config config = अणु पूर्ण;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा reserved_mem *mem;
	काष्ठा rmem *priv;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;
	priv->dev = dev;

	mem = of_reserved_mem_lookup(dev->of_node);
	अगर (!mem) अणु
		dev_err(dev, "Failed to lookup reserved memory\n");
		वापस -EINVAL;
	पूर्ण
	priv->mem = mem;

	config.dev = dev;
	config.priv = priv;
	config.name = "rmem";
	config.size = mem->size;
	config.reg_पढ़ो = rmem_पढ़ो;

	वापस PTR_ERR_OR_ZERO(devm_nvmem_रेजिस्टर(dev, &config));
पूर्ण

अटल स्थिर काष्ठा of_device_id rmem_match[] = अणु
	अणु .compatible = "nvmem-rmem", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, rmem_match);

अटल काष्ठा platक्रमm_driver rmem_driver = अणु
	.probe = rmem_probe,
	.driver = अणु
		.name = "rmem",
		.of_match_table = rmem_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(rmem_driver);

MODULE_AUTHOR("Nicolas Saenz Julienne <nsaenzjulienne@suse.de>");
MODULE_DESCRIPTION("Reserved Memory Based nvmem Driver");
MODULE_LICENSE("GPL");
