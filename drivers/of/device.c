<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_iommu.h>
#समावेश <linux/dma-direct.h> /* क्रम bus_dma_region */
#समावेश <linux/dma-map-ops.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <यंत्र/त्रुटिसं.स>
#समावेश "of_private.h"

/**
 * of_match_device - Tell अगर a काष्ठा device matches an of_device_id list
 * @matches: array of of device match काष्ठाures to search in
 * @dev: the of device काष्ठाure to match against
 *
 * Used by a driver to check whether an platक्रमm_device present in the
 * प्रणाली is in its list of supported devices.
 */
स्थिर काष्ठा of_device_id *of_match_device(स्थिर काष्ठा of_device_id *matches,
					   स्थिर काष्ठा device *dev)
अणु
	अगर ((!matches) || (!dev->of_node))
		वापस शून्य;
	वापस of_match_node(matches, dev->of_node);
पूर्ण
EXPORT_SYMBOL(of_match_device);

पूर्णांक of_device_add(काष्ठा platक्रमm_device *ofdev)
अणु
	BUG_ON(ofdev->dev.of_node == शून्य);

	/* name and id have to be set so that the platक्रमm bus करोesn't get
	 * confused on matching */
	ofdev->name = dev_name(&ofdev->dev);
	ofdev->id = PLATFORM_DEVID_NONE;

	/*
	 * If this device has not binding numa node in devicetree, that is
	 * of_node_to_nid वापसs NUMA_NO_NODE. device_add will assume that this
	 * device is on the same node as the parent.
	 */
	set_dev_node(&ofdev->dev, of_node_to_nid(ofdev->dev.of_node));

	वापस device_add(&ofdev->dev);
पूर्ण

/**
 * of_dma_configure_id - Setup DMA configuration
 * @dev:	Device to apply DMA configuration
 * @np:		Poपूर्णांकer to OF node having DMA configuration
 * @क्रमce_dma:  Whether device is to be set up by of_dma_configure() even अगर
 *		DMA capability is not explicitly described by firmware.
 * @id:		Optional स्थिर poपूर्णांकer value input id
 *
 * Try to get devices's DMA configuration from DT and update it
 * accordingly.
 *
 * If platक्रमm code needs to use its own special DMA configuration, it
 * can use a platक्रमm bus notअगरier and handle BUS_NOTIFY_ADD_DEVICE events
 * to fix up DMA configuration.
 */
पूर्णांक of_dma_configure_id(काष्ठा device *dev, काष्ठा device_node *np,
			bool क्रमce_dma, स्थिर u32 *id)
अणु
	स्थिर काष्ठा iommu_ops *iommu;
	स्थिर काष्ठा bus_dma_region *map = शून्य;
	u64 dma_start = 0;
	u64 mask, end, size = 0;
	bool coherent;
	पूर्णांक ret;

	ret = of_dma_get_range(np, &map);
	अगर (ret < 0) अणु
		/*
		 * For legacy reasons, we have to assume some devices need
		 * DMA configuration regardless of whether "dma-ranges" is
		 * correctly specअगरied or not.
		 */
		अगर (!क्रमce_dma)
			वापस ret == -ENODEV ? 0 : ret;
	पूर्ण अन्यथा अणु
		स्थिर काष्ठा bus_dma_region *r = map;
		u64 dma_end = 0;

		/* Determine the overall bounds of all DMA regions */
		क्रम (dma_start = ~0; r->size; r++) अणु
			/* Take lower and upper limits */
			अगर (r->dma_start < dma_start)
				dma_start = r->dma_start;
			अगर (r->dma_start + r->size > dma_end)
				dma_end = r->dma_start + r->size;
		पूर्ण
		size = dma_end - dma_start;

		/*
		 * Add a work around to treat the size as mask + 1 in हाल
		 * it is defined in DT as a mask.
		 */
		अगर (size & 1) अणु
			dev_warn(dev, "Invalid size 0x%llx for dma-range(s)\n",
				 size);
			size = size + 1;
		पूर्ण

		अगर (!size) अणु
			dev_err(dev, "Adjusted size 0x%llx invalid\n", size);
			kमुक्त(map);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/*
	 * If @dev is expected to be DMA-capable then the bus code that created
	 * it should have initialised its dma_mask poपूर्णांकer by this poपूर्णांक. For
	 * now, we'll जारी the legacy behaviour of coercing it to the
	 * coherent mask अगर not, but we'll no दीर्घer करो so quietly.
	 */
	अगर (!dev->dma_mask) अणु
		dev_warn(dev, "DMA mask not set\n");
		dev->dma_mask = &dev->coherent_dma_mask;
	पूर्ण

	अगर (!size && dev->coherent_dma_mask)
		size = max(dev->coherent_dma_mask, dev->coherent_dma_mask + 1);
	अन्यथा अगर (!size)
		size = 1ULL << 32;

	/*
	 * Limit coherent and dma mask based on size and शेष mask
	 * set by the driver.
	 */
	end = dma_start + size - 1;
	mask = DMA_BIT_MASK(ilog2(end) + 1);
	dev->coherent_dma_mask &= mask;
	*dev->dma_mask &= mask;
	/* ...but only set bus limit and range map अगर we found valid dma-ranges earlier */
	अगर (!ret) अणु
		dev->bus_dma_limit = end;
		dev->dma_range_map = map;
	पूर्ण

	coherent = of_dma_is_coherent(np);
	dev_dbg(dev, "device is%sdma coherent\n",
		coherent ? " " : " not ");

	iommu = of_iommu_configure(dev, np, id);
	अगर (PTR_ERR(iommu) == -EPROBE_DEFER) अणु
		/* Don't touch range map if it wasn't set from a valid dma-ranges */
		अगर (!ret)
			dev->dma_range_map = शून्य;
		kमुक्त(map);
		वापस -EPROBE_DEFER;
	पूर्ण

	dev_dbg(dev, "device is%sbehind an iommu\n",
		iommu ? " " : " not ");

	arch_setup_dma_ops(dev, dma_start, size, iommu, coherent);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(of_dma_configure_id);

पूर्णांक of_device_रेजिस्टर(काष्ठा platक्रमm_device *pdev)
अणु
	device_initialize(&pdev->dev);
	वापस of_device_add(pdev);
पूर्ण
EXPORT_SYMBOL(of_device_रेजिस्टर);

व्योम of_device_unरेजिस्टर(काष्ठा platक्रमm_device *ofdev)
अणु
	device_unरेजिस्टर(&ofdev->dev);
पूर्ण
EXPORT_SYMBOL(of_device_unरेजिस्टर);

स्थिर व्योम *of_device_get_match_data(स्थिर काष्ठा device *dev)
अणु
	स्थिर काष्ठा of_device_id *match;

	match = of_match_device(dev->driver->of_match_table, dev);
	अगर (!match)
		वापस शून्य;

	वापस match->data;
पूर्ण
EXPORT_SYMBOL(of_device_get_match_data);

अटल sमाप_प्रकार of_device_get_modalias(काष्ठा device *dev, अक्षर *str, sमाप_प्रकार len)
अणु
	स्थिर अक्षर *compat;
	अक्षर *c;
	काष्ठा property *p;
	sमाप_प्रकार csize;
	sमाप_प्रकार tsize;

	अगर ((!dev) || (!dev->of_node))
		वापस -ENODEV;

	/* Name & Type */
	/* %p eats all alphanum अक्षरacters, so %c must be used here */
	csize = snम_लिखो(str, len, "of:N%pOFn%c%s", dev->of_node, 'T',
			 of_node_get_device_type(dev->of_node));
	tsize = csize;
	len -= csize;
	अगर (str)
		str += csize;

	of_property_क्रम_each_string(dev->of_node, "compatible", p, compat) अणु
		csize = म_माप(compat) + 1;
		tsize += csize;
		अगर (csize > len)
			जारी;

		csize = snम_लिखो(str, len, "C%s", compat);
		क्रम (c = str; c; ) अणु
			c = म_अक्षर(c, ' ');
			अगर (c)
				*c++ = '_';
		पूर्ण
		len -= csize;
		str += csize;
	पूर्ण

	वापस tsize;
पूर्ण

पूर्णांक of_device_request_module(काष्ठा device *dev)
अणु
	अक्षर *str;
	sमाप_प्रकार size;
	पूर्णांक ret;

	size = of_device_get_modalias(dev, शून्य, 0);
	अगर (size < 0)
		वापस size;

	str = kदो_स्मृति(size + 1, GFP_KERNEL);
	अगर (!str)
		वापस -ENOMEM;

	of_device_get_modalias(dev, str, size);
	str[size] = '\0';
	ret = request_module(str);
	kमुक्त(str);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(of_device_request_module);

/**
 * of_device_modalias - Fill buffer with newline terminated modalias string
 * @dev:	Calling device
 * @str:	Modalias string
 * @len:	Size of @str
 */
sमाप_प्रकार of_device_modalias(काष्ठा device *dev, अक्षर *str, sमाप_प्रकार len)
अणु
	sमाप_प्रकार sl = of_device_get_modalias(dev, str, len - 2);
	अगर (sl < 0)
		वापस sl;
	अगर (sl > len - 2)
		वापस -ENOMEM;

	str[sl++] = '\n';
	str[sl] = 0;
	वापस sl;
पूर्ण
EXPORT_SYMBOL_GPL(of_device_modalias);

/**
 * of_device_uevent - Display OF related uevent inक्रमmation
 * @dev:	Device to apply DMA configuration
 * @env:	Kernel object's userspace event reference
 */
व्योम of_device_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	स्थिर अक्षर *compat, *type;
	काष्ठा alias_prop *app;
	काष्ठा property *p;
	पूर्णांक seen = 0;

	अगर ((!dev) || (!dev->of_node))
		वापस;

	add_uevent_var(env, "OF_NAME=%pOFn", dev->of_node);
	add_uevent_var(env, "OF_FULLNAME=%pOF", dev->of_node);
	type = of_node_get_device_type(dev->of_node);
	अगर (type)
		add_uevent_var(env, "OF_TYPE=%s", type);

	/* Since the compatible field can contain pretty much anything
	 * it's not really legal to split it out with commas. We split it
	 * up using a number of environment variables instead. */
	of_property_क्रम_each_string(dev->of_node, "compatible", p, compat) अणु
		add_uevent_var(env, "OF_COMPATIBLE_%d=%s", seen, compat);
		seen++;
	पूर्ण
	add_uevent_var(env, "OF_COMPATIBLE_N=%d", seen);

	seen = 0;
	mutex_lock(&of_mutex);
	list_क्रम_each_entry(app, &aliases_lookup, link) अणु
		अगर (dev->of_node == app->np) अणु
			add_uevent_var(env, "OF_ALIAS_%d=%s", seen,
				       app->alias);
			seen++;
		पूर्ण
	पूर्ण
	mutex_unlock(&of_mutex);
पूर्ण

पूर्णांक of_device_uevent_modalias(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	पूर्णांक sl;

	अगर ((!dev) || (!dev->of_node))
		वापस -ENODEV;

	/* Devicetree modalias is tricky, we add it in 2 steps */
	अगर (add_uevent_var(env, "MODALIAS="))
		वापस -ENOMEM;

	sl = of_device_get_modalias(dev, &env->buf[env->buflen-1],
				    माप(env->buf) - env->buflen);
	अगर (sl >= (माप(env->buf) - env->buflen))
		वापस -ENOMEM;
	env->buflen += sl;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(of_device_uevent_modalias);
