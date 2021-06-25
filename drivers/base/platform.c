<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * platक्रमm.c - platक्रमm 'pseudo' bus क्रम legacy devices
 *
 * Copyright (c) 2002-3 Patrick Mochel
 * Copyright (c) 2002-3 Open Source Development Lअसल
 *
 * Please see Documentation/driver-api/driver-model/platक्रमm.rst क्रम more
 * inक्रमmation.
 */

#समावेश <linux/माला.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/memblock.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/idr.h>
#समावेश <linux/acpi.h>
#समावेश <linux/clk/clk-conf.h>
#समावेश <linux/सीमा.स>
#समावेश <linux/property.h>
#समावेश <linux/kmemleak.h>
#समावेश <linux/types.h>

#समावेश "base.h"
#समावेश "power/power.h"

/* For स्वतःmatically allocated device IDs */
अटल DEFINE_IDA(platक्रमm_devid_ida);

काष्ठा device platक्रमm_bus = अणु
	.init_name	= "platform",
पूर्ण;
EXPORT_SYMBOL_GPL(platक्रमm_bus);

/**
 * platक्रमm_get_resource - get a resource क्रम a device
 * @dev: platक्रमm device
 * @type: resource type
 * @num: resource index
 *
 * Return: a poपूर्णांकer to the resource or शून्य on failure.
 */
काष्ठा resource *platक्रमm_get_resource(काष्ठा platक्रमm_device *dev,
				       अचिन्हित पूर्णांक type, अचिन्हित पूर्णांक num)
अणु
	u32 i;

	क्रम (i = 0; i < dev->num_resources; i++) अणु
		काष्ठा resource *r = &dev->resource[i];

		अगर (type == resource_type(r) && num-- == 0)
			वापस r;
	पूर्ण
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(platक्रमm_get_resource);

काष्ठा resource *platक्रमm_get_mem_or_io(काष्ठा platक्रमm_device *dev,
					अचिन्हित पूर्णांक num)
अणु
	u32 i;

	क्रम (i = 0; i < dev->num_resources; i++) अणु
		काष्ठा resource *r = &dev->resource[i];

		अगर ((resource_type(r) & (IORESOURCE_MEM|IORESOURCE_IO)) && num-- == 0)
			वापस r;
	पूर्ण
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(platक्रमm_get_mem_or_io);

#अगर_घोषित CONFIG_HAS_IOMEM
/**
 * devm_platक्रमm_get_and_ioremap_resource - call devm_ioremap_resource() क्रम a
 *					    platक्रमm device and get resource
 *
 * @pdev: platक्रमm device to use both क्रम memory resource lookup as well as
 *        resource management
 * @index: resource index
 * @res: optional output parameter to store a poपूर्णांकer to the obtained resource.
 *
 * Return: a poपूर्णांकer to the remapped memory or an ERR_PTR() encoded error code
 * on failure.
 */
व्योम __iomem *
devm_platक्रमm_get_and_ioremap_resource(काष्ठा platक्रमm_device *pdev,
				अचिन्हित पूर्णांक index, काष्ठा resource **res)
अणु
	काष्ठा resource *r;

	r = platक्रमm_get_resource(pdev, IORESOURCE_MEM, index);
	अगर (res)
		*res = r;
	वापस devm_ioremap_resource(&pdev->dev, r);
पूर्ण
EXPORT_SYMBOL_GPL(devm_platक्रमm_get_and_ioremap_resource);

/**
 * devm_platक्रमm_ioremap_resource - call devm_ioremap_resource() क्रम a platक्रमm
 *				    device
 *
 * @pdev: platक्रमm device to use both क्रम memory resource lookup as well as
 *        resource management
 * @index: resource index
 *
 * Return: a poपूर्णांकer to the remapped memory or an ERR_PTR() encoded error code
 * on failure.
 */
व्योम __iomem *devm_platक्रमm_ioremap_resource(काष्ठा platक्रमm_device *pdev,
					     अचिन्हित पूर्णांक index)
अणु
	वापस devm_platक्रमm_get_and_ioremap_resource(pdev, index, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(devm_platक्रमm_ioremap_resource);

/**
 * devm_platक्रमm_ioremap_resource_wc - ग_लिखो-combined variant of
 *                                     devm_platक्रमm_ioremap_resource()
 *
 * @pdev: platक्रमm device to use both क्रम memory resource lookup as well as
 *        resource management
 * @index: resource index
 *
 * Return: a poपूर्णांकer to the remapped memory or an ERR_PTR() encoded error code
 * on failure.
 */
व्योम __iomem *devm_platक्रमm_ioremap_resource_wc(काष्ठा platक्रमm_device *pdev,
						अचिन्हित पूर्णांक index)
अणु
	काष्ठा resource *res;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, index);
	वापस devm_ioremap_resource_wc(&pdev->dev, res);
पूर्ण

/**
 * devm_platक्रमm_ioremap_resource_byname - call devm_ioremap_resource क्रम
 *					   a platक्रमm device, retrieve the
 *					   resource by name
 *
 * @pdev: platक्रमm device to use both क्रम memory resource lookup as well as
 *	  resource management
 * @name: name of the resource
 *
 * Return: a poपूर्णांकer to the remapped memory or an ERR_PTR() encoded error code
 * on failure.
 */
व्योम __iomem *
devm_platक्रमm_ioremap_resource_byname(काष्ठा platक्रमm_device *pdev,
				      स्थिर अक्षर *name)
अणु
	काष्ठा resource *res;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, name);
	वापस devm_ioremap_resource(&pdev->dev, res);
पूर्ण
EXPORT_SYMBOL_GPL(devm_platक्रमm_ioremap_resource_byname);
#पूर्ण_अगर /* CONFIG_HAS_IOMEM */

/**
 * platक्रमm_get_irq_optional - get an optional IRQ क्रम a device
 * @dev: platक्रमm device
 * @num: IRQ number index
 *
 * Gets an IRQ क्रम a platक्रमm device. Device drivers should check the वापस
 * value क्रम errors so as to not pass a negative पूर्णांकeger value to the
 * request_irq() APIs. This is the same as platक्रमm_get_irq(), except that it
 * करोes not prपूर्णांक an error message अगर an IRQ can not be obtained.
 *
 * For example::
 *
 *		पूर्णांक irq = platक्रमm_get_irq_optional(pdev, 0);
 *		अगर (irq < 0)
 *			वापस irq;
 *
 * Return: non-zero IRQ number on success, negative error number on failure.
 */
पूर्णांक platक्रमm_get_irq_optional(काष्ठा platक्रमm_device *dev, अचिन्हित पूर्णांक num)
अणु
	पूर्णांक ret;
#अगर_घोषित CONFIG_SPARC
	/* sparc करोes not have irqs represented as IORESOURCE_IRQ resources */
	अगर (!dev || num >= dev->archdata.num_irqs)
		जाओ out_not_found;
	ret = dev->archdata.irqs[num];
	जाओ out;
#अन्यथा
	काष्ठा resource *r;

	अगर (IS_ENABLED(CONFIG_OF_IRQ) && dev->dev.of_node) अणु
		ret = of_irq_get(dev->dev.of_node, num);
		अगर (ret > 0 || ret == -EPROBE_DEFER)
			जाओ out;
	पूर्ण

	r = platक्रमm_get_resource(dev, IORESOURCE_IRQ, num);
	अगर (has_acpi_companion(&dev->dev)) अणु
		अगर (r && r->flags & IORESOURCE_DISABLED) अणु
			ret = acpi_irq_get(ACPI_HANDLE(&dev->dev), num, r);
			अगर (ret)
				जाओ out;
		पूर्ण
	पूर्ण

	/*
	 * The resources may pass trigger flags to the irqs that need
	 * to be set up. It so happens that the trigger flags क्रम
	 * IORESOURCE_BITS correspond 1-to-1 to the IRQF_TRIGGER*
	 * settings.
	 */
	अगर (r && r->flags & IORESOURCE_BITS) अणु
		काष्ठा irq_data *irqd;

		irqd = irq_get_irq_data(r->start);
		अगर (!irqd)
			जाओ out_not_found;
		irqd_set_trigger_type(irqd, r->flags & IORESOURCE_BITS);
	पूर्ण

	अगर (r) अणु
		ret = r->start;
		जाओ out;
	पूर्ण

	/*
	 * For the index 0 पूर्णांकerrupt, allow falling back to GpioInt
	 * resources. While a device could have both Interrupt and GpioInt
	 * resources, making this fallback ambiguous, in many common हालs
	 * the device will only expose one IRQ, and this fallback
	 * allows a common code path across either kind of resource.
	 */
	अगर (num == 0 && has_acpi_companion(&dev->dev)) अणु
		ret = acpi_dev_gpio_irq_get(ACPI_COMPANION(&dev->dev), num);
		/* Our callers expect -ENXIO क्रम missing IRQs. */
		अगर (ret >= 0 || ret == -EPROBE_DEFER)
			जाओ out;
	पूर्ण

#पूर्ण_अगर
out_not_found:
	ret = -ENXIO;
out:
	WARN(ret == 0, "0 is an invalid IRQ number\n");
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(platक्रमm_get_irq_optional);

/**
 * platक्रमm_get_irq - get an IRQ क्रम a device
 * @dev: platक्रमm device
 * @num: IRQ number index
 *
 * Gets an IRQ क्रम a platक्रमm device and prपूर्णांकs an error message अगर finding the
 * IRQ fails. Device drivers should check the वापस value क्रम errors so as to
 * not pass a negative पूर्णांकeger value to the request_irq() APIs.
 *
 * For example::
 *
 *		पूर्णांक irq = platक्रमm_get_irq(pdev, 0);
 *		अगर (irq < 0)
 *			वापस irq;
 *
 * Return: non-zero IRQ number on success, negative error number on failure.
 */
पूर्णांक platक्रमm_get_irq(काष्ठा platक्रमm_device *dev, अचिन्हित पूर्णांक num)
अणु
	पूर्णांक ret;

	ret = platक्रमm_get_irq_optional(dev, num);
	अगर (ret < 0 && ret != -EPROBE_DEFER)
		dev_err(&dev->dev, "IRQ index %u not found\n", num);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(platक्रमm_get_irq);

/**
 * platक्रमm_irq_count - Count the number of IRQs a platक्रमm device uses
 * @dev: platक्रमm device
 *
 * Return: Number of IRQs a platक्रमm device uses or EPROBE_DEFER
 */
पूर्णांक platक्रमm_irq_count(काष्ठा platक्रमm_device *dev)
अणु
	पूर्णांक ret, nr = 0;

	जबतक ((ret = platक्रमm_get_irq_optional(dev, nr)) >= 0)
		nr++;

	अगर (ret == -EPROBE_DEFER)
		वापस ret;

	वापस nr;
पूर्ण
EXPORT_SYMBOL_GPL(platक्रमm_irq_count);

काष्ठा irq_affinity_devres अणु
	अचिन्हित पूर्णांक count;
	अचिन्हित पूर्णांक irq[];
पूर्ण;

अटल व्योम platक्रमm_disable_acpi_irq(काष्ठा platक्रमm_device *pdev, पूर्णांक index)
अणु
	काष्ठा resource *r;

	r = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, index);
	अगर (r)
		irqresource_disabled(r, 0);
पूर्ण

अटल व्योम devm_platक्रमm_get_irqs_affinity_release(काष्ठा device *dev,
						    व्योम *res)
अणु
	काष्ठा irq_affinity_devres *ptr = res;
	पूर्णांक i;

	क्रम (i = 0; i < ptr->count; i++) अणु
		irq_dispose_mapping(ptr->irq[i]);

		अगर (has_acpi_companion(dev))
			platक्रमm_disable_acpi_irq(to_platक्रमm_device(dev), i);
	पूर्ण
पूर्ण

/**
 * devm_platक्रमm_get_irqs_affinity - devm method to get a set of IRQs क्रम a
 *				device using an पूर्णांकerrupt affinity descriptor
 * @dev: platक्रमm device poपूर्णांकer
 * @affd: affinity descriptor
 * @minvec: minimum count of पूर्णांकerrupt vectors
 * @maxvec: maximum count of पूर्णांकerrupt vectors
 * @irqs: poपूर्णांकer holder क्रम IRQ numbers
 *
 * Gets a set of IRQs क्रम a platक्रमm device, and updates IRQ afffपूर्णांकy according
 * to the passed affinity descriptor
 *
 * Return: Number of vectors on success, negative error number on failure.
 */
पूर्णांक devm_platक्रमm_get_irqs_affinity(काष्ठा platक्रमm_device *dev,
				    काष्ठा irq_affinity *affd,
				    अचिन्हित पूर्णांक minvec,
				    अचिन्हित पूर्णांक maxvec,
				    पूर्णांक **irqs)
अणु
	काष्ठा irq_affinity_devres *ptr;
	काष्ठा irq_affinity_desc *desc;
	माप_प्रकार size;
	पूर्णांक i, ret, nvec;

	अगर (!affd)
		वापस -EPERM;

	अगर (maxvec < minvec)
		वापस -दुस्फल;

	nvec = platक्रमm_irq_count(dev);
	अगर (nvec < 0)
		वापस nvec;

	अगर (nvec < minvec)
		वापस -ENOSPC;

	nvec = irq_calc_affinity_vectors(minvec, nvec, affd);
	अगर (nvec < minvec)
		वापस -ENOSPC;

	अगर (nvec > maxvec)
		nvec = maxvec;

	size = माप(*ptr) + माप(अचिन्हित पूर्णांक) * nvec;
	ptr = devres_alloc(devm_platक्रमm_get_irqs_affinity_release, size,
			   GFP_KERNEL);
	अगर (!ptr)
		वापस -ENOMEM;

	ptr->count = nvec;

	क्रम (i = 0; i < nvec; i++) अणु
		पूर्णांक irq = platक्रमm_get_irq(dev, i);
		अगर (irq < 0) अणु
			ret = irq;
			जाओ err_मुक्त_devres;
		पूर्ण
		ptr->irq[i] = irq;
	पूर्ण

	desc = irq_create_affinity_masks(nvec, affd);
	अगर (!desc) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_devres;
	पूर्ण

	क्रम (i = 0; i < nvec; i++) अणु
		ret = irq_update_affinity_desc(ptr->irq[i], &desc[i]);
		अगर (ret) अणु
			dev_err(&dev->dev, "failed to update irq%d affinity descriptor (%d)\n",
				ptr->irq[i], ret);
			जाओ err_मुक्त_desc;
		पूर्ण
	पूर्ण

	devres_add(&dev->dev, ptr);

	kमुक्त(desc);

	*irqs = ptr->irq;

	वापस nvec;

err_मुक्त_desc:
	kमुक्त(desc);
err_मुक्त_devres:
	devres_मुक्त(ptr);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(devm_platक्रमm_get_irqs_affinity);

/**
 * platक्रमm_get_resource_byname - get a resource क्रम a device by name
 * @dev: platक्रमm device
 * @type: resource type
 * @name: resource name
 */
काष्ठा resource *platक्रमm_get_resource_byname(काष्ठा platक्रमm_device *dev,
					      अचिन्हित पूर्णांक type,
					      स्थिर अक्षर *name)
अणु
	u32 i;

	क्रम (i = 0; i < dev->num_resources; i++) अणु
		काष्ठा resource *r = &dev->resource[i];

		अगर (unlikely(!r->name))
			जारी;

		अगर (type == resource_type(r) && !म_भेद(r->name, name))
			वापस r;
	पूर्ण
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(platक्रमm_get_resource_byname);

अटल पूर्णांक __platक्रमm_get_irq_byname(काष्ठा platक्रमm_device *dev,
				     स्थिर अक्षर *name)
अणु
	काष्ठा resource *r;
	पूर्णांक ret;

	अगर (IS_ENABLED(CONFIG_OF_IRQ) && dev->dev.of_node) अणु
		ret = of_irq_get_byname(dev->dev.of_node, name);
		अगर (ret > 0 || ret == -EPROBE_DEFER)
			वापस ret;
	पूर्ण

	r = platक्रमm_get_resource_byname(dev, IORESOURCE_IRQ, name);
	अगर (r) अणु
		WARN(r->start == 0, "0 is an invalid IRQ number\n");
		वापस r->start;
	पूर्ण

	वापस -ENXIO;
पूर्ण

/**
 * platक्रमm_get_irq_byname - get an IRQ क्रम a device by name
 * @dev: platक्रमm device
 * @name: IRQ name
 *
 * Get an IRQ like platक्रमm_get_irq(), but then by name rather then by index.
 *
 * Return: non-zero IRQ number on success, negative error number on failure.
 */
पूर्णांक platक्रमm_get_irq_byname(काष्ठा platक्रमm_device *dev, स्थिर अक्षर *name)
अणु
	पूर्णांक ret;

	ret = __platक्रमm_get_irq_byname(dev, name);
	अगर (ret < 0 && ret != -EPROBE_DEFER)
		dev_err(&dev->dev, "IRQ %s not found\n", name);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(platक्रमm_get_irq_byname);

/**
 * platक्रमm_get_irq_byname_optional - get an optional IRQ क्रम a device by name
 * @dev: platक्रमm device
 * @name: IRQ name
 *
 * Get an optional IRQ by name like platक्रमm_get_irq_byname(). Except that it
 * करोes not prपूर्णांक an error message अगर an IRQ can not be obtained.
 *
 * Return: non-zero IRQ number on success, negative error number on failure.
 */
पूर्णांक platक्रमm_get_irq_byname_optional(काष्ठा platक्रमm_device *dev,
				     स्थिर अक्षर *name)
अणु
	वापस __platक्रमm_get_irq_byname(dev, name);
पूर्ण
EXPORT_SYMBOL_GPL(platक्रमm_get_irq_byname_optional);

/**
 * platक्रमm_add_devices - add a numbers of platक्रमm devices
 * @devs: array of platक्रमm devices to add
 * @num: number of platक्रमm devices in array
 */
पूर्णांक platक्रमm_add_devices(काष्ठा platक्रमm_device **devs, पूर्णांक num)
अणु
	पूर्णांक i, ret = 0;

	क्रम (i = 0; i < num; i++) अणु
		ret = platक्रमm_device_रेजिस्टर(devs[i]);
		अगर (ret) अणु
			जबतक (--i >= 0)
				platक्रमm_device_unरेजिस्टर(devs[i]);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(platक्रमm_add_devices);

काष्ठा platक्रमm_object अणु
	काष्ठा platक्रमm_device pdev;
	अक्षर name[];
पूर्ण;

/*
 * Set up शेष DMA mask क्रम platक्रमm devices अगर the they weren't
 * previously set by the architecture / DT.
 */
अटल व्योम setup_pdev_dma_masks(काष्ठा platक्रमm_device *pdev)
अणु
	pdev->dev.dma_parms = &pdev->dma_parms;

	अगर (!pdev->dev.coherent_dma_mask)
		pdev->dev.coherent_dma_mask = DMA_BIT_MASK(32);
	अगर (!pdev->dev.dma_mask) अणु
		pdev->platक्रमm_dma_mask = DMA_BIT_MASK(32);
		pdev->dev.dma_mask = &pdev->platक्रमm_dma_mask;
	पूर्ण
पूर्ण;

/**
 * platक्रमm_device_put - destroy a platक्रमm device
 * @pdev: platक्रमm device to मुक्त
 *
 * Free all memory associated with a platक्रमm device.  This function must
 * _only_ be बाह्यally called in error हालs.  All other usage is a bug.
 */
व्योम platक्रमm_device_put(काष्ठा platक्रमm_device *pdev)
अणु
	अगर (!IS_ERR_OR_शून्य(pdev))
		put_device(&pdev->dev);
पूर्ण
EXPORT_SYMBOL_GPL(platक्रमm_device_put);

अटल व्योम platक्रमm_device_release(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_object *pa = container_of(dev, काष्ठा platक्रमm_object,
						  pdev.dev);

	of_node_put(pa->pdev.dev.of_node);
	kमुक्त(pa->pdev.dev.platक्रमm_data);
	kमुक्त(pa->pdev.mfd_cell);
	kमुक्त(pa->pdev.resource);
	kमुक्त(pa->pdev.driver_override);
	kमुक्त(pa);
पूर्ण

/**
 * platक्रमm_device_alloc - create a platक्रमm device
 * @name: base name of the device we're adding
 * @id: instance id
 *
 * Create a platक्रमm device object which can have other objects attached
 * to it, and which will have attached objects मुक्तd when it is released.
 */
काष्ठा platक्रमm_device *platक्रमm_device_alloc(स्थिर अक्षर *name, पूर्णांक id)
अणु
	काष्ठा platक्रमm_object *pa;

	pa = kzalloc(माप(*pa) + म_माप(name) + 1, GFP_KERNEL);
	अगर (pa) अणु
		म_नकल(pa->name, name);
		pa->pdev.name = pa->name;
		pa->pdev.id = id;
		device_initialize(&pa->pdev.dev);
		pa->pdev.dev.release = platक्रमm_device_release;
		setup_pdev_dma_masks(&pa->pdev);
	पूर्ण

	वापस pa ? &pa->pdev : शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(platक्रमm_device_alloc);

/**
 * platक्रमm_device_add_resources - add resources to a platक्रमm device
 * @pdev: platक्रमm device allocated by platक्रमm_device_alloc to add resources to
 * @res: set of resources that needs to be allocated क्रम the device
 * @num: number of resources
 *
 * Add a copy of the resources to the platक्रमm device.  The memory
 * associated with the resources will be मुक्तd when the platक्रमm device is
 * released.
 */
पूर्णांक platक्रमm_device_add_resources(काष्ठा platक्रमm_device *pdev,
				  स्थिर काष्ठा resource *res, अचिन्हित पूर्णांक num)
अणु
	काष्ठा resource *r = शून्य;

	अगर (res) अणु
		r = kmemdup(res, माप(काष्ठा resource) * num, GFP_KERNEL);
		अगर (!r)
			वापस -ENOMEM;
	पूर्ण

	kमुक्त(pdev->resource);
	pdev->resource = r;
	pdev->num_resources = num;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(platक्रमm_device_add_resources);

/**
 * platक्रमm_device_add_data - add platक्रमm-specअगरic data to a platक्रमm device
 * @pdev: platक्रमm device allocated by platक्रमm_device_alloc to add resources to
 * @data: platक्रमm specअगरic data क्रम this platक्रमm device
 * @size: size of platक्रमm specअगरic data
 *
 * Add a copy of platक्रमm specअगरic data to the platक्रमm device's
 * platक्रमm_data poपूर्णांकer.  The memory associated with the platक्रमm data
 * will be मुक्तd when the platक्रमm device is released.
 */
पूर्णांक platक्रमm_device_add_data(काष्ठा platक्रमm_device *pdev, स्थिर व्योम *data,
			     माप_प्रकार size)
अणु
	व्योम *d = शून्य;

	अगर (data) अणु
		d = kmemdup(data, size, GFP_KERNEL);
		अगर (!d)
			वापस -ENOMEM;
	पूर्ण

	kमुक्त(pdev->dev.platक्रमm_data);
	pdev->dev.platक्रमm_data = d;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(platक्रमm_device_add_data);

/**
 * platक्रमm_device_add_properties - add built-in properties to a platक्रमm device
 * @pdev: platक्रमm device to add properties to
 * @properties: null terminated array of properties to add
 *
 * The function will take deep copy of @properties and attach the copy to the
 * platक्रमm device. The memory associated with properties will be मुक्तd when the
 * platक्रमm device is released.
 */
पूर्णांक platक्रमm_device_add_properties(काष्ठा platक्रमm_device *pdev,
				   स्थिर काष्ठा property_entry *properties)
अणु
	वापस device_add_properties(&pdev->dev, properties);
पूर्ण
EXPORT_SYMBOL_GPL(platक्रमm_device_add_properties);

/**
 * platक्रमm_device_add - add a platक्रमm device to device hierarchy
 * @pdev: platक्रमm device we're adding
 *
 * This is part 2 of platक्रमm_device_रेजिस्टर(), though may be called
 * separately _अगरf_ pdev was allocated by platक्रमm_device_alloc().
 */
पूर्णांक platक्रमm_device_add(काष्ठा platक्रमm_device *pdev)
अणु
	u32 i;
	पूर्णांक ret;

	अगर (!pdev)
		वापस -EINVAL;

	अगर (!pdev->dev.parent)
		pdev->dev.parent = &platक्रमm_bus;

	pdev->dev.bus = &platक्रमm_bus_type;

	चयन (pdev->id) अणु
	शेष:
		dev_set_name(&pdev->dev, "%s.%d", pdev->name,  pdev->id);
		अवरोध;
	हाल PLATFORM_DEVID_NONE:
		dev_set_name(&pdev->dev, "%s", pdev->name);
		अवरोध;
	हाल PLATFORM_DEVID_AUTO:
		/*
		 * Automatically allocated device ID. We mark it as such so
		 * that we remember it must be मुक्तd, and we append a suffix
		 * to aव्योम namespace collision with explicit IDs.
		 */
		ret = ida_alloc(&platक्रमm_devid_ida, GFP_KERNEL);
		अगर (ret < 0)
			जाओ err_out;
		pdev->id = ret;
		pdev->id_स्वतः = true;
		dev_set_name(&pdev->dev, "%s.%d.auto", pdev->name, pdev->id);
		अवरोध;
	पूर्ण

	क्रम (i = 0; i < pdev->num_resources; i++) अणु
		काष्ठा resource *p, *r = &pdev->resource[i];

		अगर (r->name == शून्य)
			r->name = dev_name(&pdev->dev);

		p = r->parent;
		अगर (!p) अणु
			अगर (resource_type(r) == IORESOURCE_MEM)
				p = &iomem_resource;
			अन्यथा अगर (resource_type(r) == IORESOURCE_IO)
				p = &ioport_resource;
		पूर्ण

		अगर (p) अणु
			ret = insert_resource(p, r);
			अगर (ret) अणु
				dev_err(&pdev->dev, "failed to claim resource %d: %pR\n", i, r);
				जाओ failed;
			पूर्ण
		पूर्ण
	पूर्ण

	pr_debug("Registering platform device '%s'. Parent at %s\n",
		 dev_name(&pdev->dev), dev_name(pdev->dev.parent));

	ret = device_add(&pdev->dev);
	अगर (ret == 0)
		वापस ret;

 failed:
	अगर (pdev->id_स्वतः) अणु
		ida_मुक्त(&platक्रमm_devid_ida, pdev->id);
		pdev->id = PLATFORM_DEVID_AUTO;
	पूर्ण

	जबतक (i--) अणु
		काष्ठा resource *r = &pdev->resource[i];
		अगर (r->parent)
			release_resource(r);
	पूर्ण

 err_out:
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(platक्रमm_device_add);

/**
 * platक्रमm_device_del - हटाओ a platक्रमm-level device
 * @pdev: platक्रमm device we're removing
 *
 * Note that this function will also release all memory- and port-based
 * resources owned by the device (@dev->resource).  This function must
 * _only_ be बाह्यally called in error हालs.  All other usage is a bug.
 */
व्योम platक्रमm_device_del(काष्ठा platक्रमm_device *pdev)
अणु
	u32 i;

	अगर (!IS_ERR_OR_शून्य(pdev)) अणु
		device_del(&pdev->dev);

		अगर (pdev->id_स्वतः) अणु
			ida_मुक्त(&platक्रमm_devid_ida, pdev->id);
			pdev->id = PLATFORM_DEVID_AUTO;
		पूर्ण

		क्रम (i = 0; i < pdev->num_resources; i++) अणु
			काष्ठा resource *r = &pdev->resource[i];
			अगर (r->parent)
				release_resource(r);
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(platक्रमm_device_del);

/**
 * platक्रमm_device_रेजिस्टर - add a platक्रमm-level device
 * @pdev: platक्रमm device we're adding
 */
पूर्णांक platक्रमm_device_रेजिस्टर(काष्ठा platक्रमm_device *pdev)
अणु
	device_initialize(&pdev->dev);
	setup_pdev_dma_masks(pdev);
	वापस platक्रमm_device_add(pdev);
पूर्ण
EXPORT_SYMBOL_GPL(platक्रमm_device_रेजिस्टर);

/**
 * platक्रमm_device_unरेजिस्टर - unरेजिस्टर a platक्रमm-level device
 * @pdev: platक्रमm device we're unरेजिस्टरing
 *
 * Unregistration is करोne in 2 steps. First we release all resources
 * and हटाओ it from the subप्रणाली, then we drop reference count by
 * calling platक्रमm_device_put().
 */
व्योम platक्रमm_device_unरेजिस्टर(काष्ठा platक्रमm_device *pdev)
अणु
	platक्रमm_device_del(pdev);
	platक्रमm_device_put(pdev);
पूर्ण
EXPORT_SYMBOL_GPL(platक्रमm_device_unरेजिस्टर);

/**
 * platक्रमm_device_रेजिस्टर_full - add a platक्रमm-level device with
 * resources and platक्रमm-specअगरic data
 *
 * @pdevinfo: data used to create device
 *
 * Returns &काष्ठा platक्रमm_device poपूर्णांकer on success, or ERR_PTR() on error.
 */
काष्ठा platक्रमm_device *platक्रमm_device_रेजिस्टर_full(
		स्थिर काष्ठा platक्रमm_device_info *pdevinfo)
अणु
	पूर्णांक ret;
	काष्ठा platक्रमm_device *pdev;

	pdev = platक्रमm_device_alloc(pdevinfo->name, pdevinfo->id);
	अगर (!pdev)
		वापस ERR_PTR(-ENOMEM);

	pdev->dev.parent = pdevinfo->parent;
	pdev->dev.fwnode = pdevinfo->fwnode;
	pdev->dev.of_node = of_node_get(to_of_node(pdev->dev.fwnode));
	pdev->dev.of_node_reused = pdevinfo->of_node_reused;

	अगर (pdevinfo->dma_mask) अणु
		pdev->platक्रमm_dma_mask = pdevinfo->dma_mask;
		pdev->dev.dma_mask = &pdev->platक्रमm_dma_mask;
		pdev->dev.coherent_dma_mask = pdevinfo->dma_mask;
	पूर्ण

	ret = platक्रमm_device_add_resources(pdev,
			pdevinfo->res, pdevinfo->num_res);
	अगर (ret)
		जाओ err;

	ret = platक्रमm_device_add_data(pdev,
			pdevinfo->data, pdevinfo->size_data);
	अगर (ret)
		जाओ err;

	अगर (pdevinfo->properties) अणु
		ret = platक्रमm_device_add_properties(pdev,
						     pdevinfo->properties);
		अगर (ret)
			जाओ err;
	पूर्ण

	ret = platक्रमm_device_add(pdev);
	अगर (ret) अणु
err:
		ACPI_COMPANION_SET(&pdev->dev, शून्य);
		platक्रमm_device_put(pdev);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस pdev;
पूर्ण
EXPORT_SYMBOL_GPL(platक्रमm_device_रेजिस्टर_full);

/**
 * __platक्रमm_driver_रेजिस्टर - रेजिस्टर a driver क्रम platक्रमm-level devices
 * @drv: platक्रमm driver काष्ठाure
 * @owner: owning module/driver
 */
पूर्णांक __platक्रमm_driver_रेजिस्टर(काष्ठा platक्रमm_driver *drv,
				काष्ठा module *owner)
अणु
	drv->driver.owner = owner;
	drv->driver.bus = &platक्रमm_bus_type;

	वापस driver_रेजिस्टर(&drv->driver);
पूर्ण
EXPORT_SYMBOL_GPL(__platक्रमm_driver_रेजिस्टर);

/**
 * platक्रमm_driver_unरेजिस्टर - unरेजिस्टर a driver क्रम platक्रमm-level devices
 * @drv: platक्रमm driver काष्ठाure
 */
व्योम platक्रमm_driver_unरेजिस्टर(काष्ठा platक्रमm_driver *drv)
अणु
	driver_unरेजिस्टर(&drv->driver);
पूर्ण
EXPORT_SYMBOL_GPL(platक्रमm_driver_unरेजिस्टर);

अटल पूर्णांक platक्रमm_probe_fail(काष्ठा platक्रमm_device *pdev)
अणु
	वापस -ENXIO;
पूर्ण

/**
 * __platक्रमm_driver_probe - रेजिस्टर driver क्रम non-hotpluggable device
 * @drv: platक्रमm driver काष्ठाure
 * @probe: the driver probe routine, probably from an __init section
 * @module: module which will be the owner of the driver
 *
 * Use this instead of platक्रमm_driver_रेजिस्टर() when you know the device
 * is not hotpluggable and has alपढ़ोy been रेजिस्टरed, and you want to
 * हटाओ its run-once probe() infraकाष्ठाure from memory after the driver
 * has bound to the device.
 *
 * One typical use क्रम this would be with drivers क्रम controllers पूर्णांकegrated
 * पूर्णांकo प्रणाली-on-chip processors, where the controller devices have been
 * configured as part of board setup.
 *
 * Note that this is incompatible with deferred probing.
 *
 * Returns zero अगर the driver रेजिस्टरed and bound to a device, अन्यथा वापसs
 * a negative error code and with the driver not रेजिस्टरed.
 */
पूर्णांक __init_or_module __platक्रमm_driver_probe(काष्ठा platक्रमm_driver *drv,
		पूर्णांक (*probe)(काष्ठा platक्रमm_device *), काष्ठा module *module)
अणु
	पूर्णांक retval, code;

	अगर (drv->driver.probe_type == PROBE_PREFER_ASYNCHRONOUS) अणु
		pr_err("%s: drivers registered with %s can not be probed asynchronously\n",
			 drv->driver.name, __func__);
		वापस -EINVAL;
	पूर्ण

	/*
	 * We have to run our probes synchronously because we check अगर
	 * we find any devices to bind to and निकास with error अगर there
	 * are any.
	 */
	drv->driver.probe_type = PROBE_FORCE_SYNCHRONOUS;

	/*
	 * Prevent driver from requesting probe deferral to aव्योम further
	 * futile probe attempts.
	 */
	drv->prevent_deferred_probe = true;

	/* make sure driver won't have bind/unbind attributes */
	drv->driver.suppress_bind_attrs = true;

	/* temporary section violation during probe() */
	drv->probe = probe;
	retval = code = __platक्रमm_driver_रेजिस्टर(drv, module);
	अगर (retval)
		वापस retval;

	/*
	 * Fixup that section violation, being paranoid about code scanning
	 * the list of drivers in order to probe new devices.  Check to see
	 * अगर the probe was successful, and make sure any क्रमced probes of
	 * new devices fail.
	 */
	spin_lock(&drv->driver.bus->p->klist_drivers.k_lock);
	drv->probe = platक्रमm_probe_fail;
	अगर (code == 0 && list_empty(&drv->driver.p->klist_devices.k_list))
		retval = -ENODEV;
	spin_unlock(&drv->driver.bus->p->klist_drivers.k_lock);

	अगर (code != retval)
		platक्रमm_driver_unरेजिस्टर(drv);
	वापस retval;
पूर्ण
EXPORT_SYMBOL_GPL(__platक्रमm_driver_probe);

/**
 * __platक्रमm_create_bundle - रेजिस्टर driver and create corresponding device
 * @driver: platक्रमm driver काष्ठाure
 * @probe: the driver probe routine, probably from an __init section
 * @res: set of resources that needs to be allocated क्रम the device
 * @n_res: number of resources
 * @data: platक्रमm specअगरic data क्रम this platक्रमm device
 * @size: size of platक्रमm specअगरic data
 * @module: module which will be the owner of the driver
 *
 * Use this in legacy-style modules that probe hardware directly and
 * रेजिस्टर a single platक्रमm device and corresponding platक्रमm driver.
 *
 * Returns &काष्ठा platक्रमm_device poपूर्णांकer on success, or ERR_PTR() on error.
 */
काष्ठा platक्रमm_device * __init_or_module __platक्रमm_create_bundle(
			काष्ठा platक्रमm_driver *driver,
			पूर्णांक (*probe)(काष्ठा platक्रमm_device *),
			काष्ठा resource *res, अचिन्हित पूर्णांक n_res,
			स्थिर व्योम *data, माप_प्रकार size, काष्ठा module *module)
अणु
	काष्ठा platक्रमm_device *pdev;
	पूर्णांक error;

	pdev = platक्रमm_device_alloc(driver->driver.name, -1);
	अगर (!pdev) अणु
		error = -ENOMEM;
		जाओ err_out;
	पूर्ण

	error = platक्रमm_device_add_resources(pdev, res, n_res);
	अगर (error)
		जाओ err_pdev_put;

	error = platक्रमm_device_add_data(pdev, data, size);
	अगर (error)
		जाओ err_pdev_put;

	error = platक्रमm_device_add(pdev);
	अगर (error)
		जाओ err_pdev_put;

	error = __platक्रमm_driver_probe(driver, probe, module);
	अगर (error)
		जाओ err_pdev_del;

	वापस pdev;

err_pdev_del:
	platक्रमm_device_del(pdev);
err_pdev_put:
	platक्रमm_device_put(pdev);
err_out:
	वापस ERR_PTR(error);
पूर्ण
EXPORT_SYMBOL_GPL(__platक्रमm_create_bundle);

/**
 * __platक्रमm_रेजिस्टर_drivers - रेजिस्टर an array of platक्रमm drivers
 * @drivers: an array of drivers to रेजिस्टर
 * @count: the number of drivers to रेजिस्टर
 * @owner: module owning the drivers
 *
 * Registers platक्रमm drivers specअगरied by an array. On failure to रेजिस्टर a
 * driver, all previously रेजिस्टरed drivers will be unरेजिस्टरed. Callers of
 * this API should use platक्रमm_unरेजिस्टर_drivers() to unरेजिस्टर drivers in
 * the reverse order.
 *
 * Returns: 0 on success or a negative error code on failure.
 */
पूर्णांक __platक्रमm_रेजिस्टर_drivers(काष्ठा platक्रमm_driver * स्थिर *drivers,
				अचिन्हित पूर्णांक count, काष्ठा module *owner)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	क्रम (i = 0; i < count; i++) अणु
		pr_debug("registering platform driver %ps\n", drivers[i]);

		err = __platक्रमm_driver_रेजिस्टर(drivers[i], owner);
		अगर (err < 0) अणु
			pr_err("failed to register platform driver %ps: %d\n",
			       drivers[i], err);
			जाओ error;
		पूर्ण
	पूर्ण

	वापस 0;

error:
	जबतक (i--) अणु
		pr_debug("unregistering platform driver %ps\n", drivers[i]);
		platक्रमm_driver_unरेजिस्टर(drivers[i]);
	पूर्ण

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(__platक्रमm_रेजिस्टर_drivers);

/**
 * platक्रमm_unरेजिस्टर_drivers - unरेजिस्टर an array of platक्रमm drivers
 * @drivers: an array of drivers to unरेजिस्टर
 * @count: the number of drivers to unरेजिस्टर
 *
 * Unरेजिस्टरs platक्रमm drivers specअगरied by an array. This is typically used
 * to complement an earlier call to platक्रमm_रेजिस्टर_drivers(). Drivers are
 * unरेजिस्टरed in the reverse order in which they were रेजिस्टरed.
 */
व्योम platक्रमm_unरेजिस्टर_drivers(काष्ठा platक्रमm_driver * स्थिर *drivers,
				 अचिन्हित पूर्णांक count)
अणु
	जबतक (count--) अणु
		pr_debug("unregistering platform driver %ps\n", drivers[count]);
		platक्रमm_driver_unरेजिस्टर(drivers[count]);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(platक्रमm_unरेजिस्टर_drivers);

अटल स्थिर काष्ठा platक्रमm_device_id *platक्रमm_match_id(
			स्थिर काष्ठा platक्रमm_device_id *id,
			काष्ठा platक्रमm_device *pdev)
अणु
	जबतक (id->name[0]) अणु
		अगर (म_भेद(pdev->name, id->name) == 0) अणु
			pdev->id_entry = id;
			वापस id;
		पूर्ण
		id++;
	पूर्ण
	वापस शून्य;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP

अटल पूर्णांक platक्रमm_legacy_suspend(काष्ठा device *dev, pm_message_t mesg)
अणु
	काष्ठा platक्रमm_driver *pdrv = to_platक्रमm_driver(dev->driver);
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	पूर्णांक ret = 0;

	अगर (dev->driver && pdrv->suspend)
		ret = pdrv->suspend(pdev, mesg);

	वापस ret;
पूर्ण

अटल पूर्णांक platक्रमm_legacy_resume(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_driver *pdrv = to_platक्रमm_driver(dev->driver);
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	पूर्णांक ret = 0;

	अगर (dev->driver && pdrv->resume)
		ret = pdrv->resume(pdev);

	वापस ret;
पूर्ण

#पूर्ण_अगर /* CONFIG_PM_SLEEP */

#अगर_घोषित CONFIG_SUSPEND

पूर्णांक platक्रमm_pm_suspend(काष्ठा device *dev)
अणु
	काष्ठा device_driver *drv = dev->driver;
	पूर्णांक ret = 0;

	अगर (!drv)
		वापस 0;

	अगर (drv->pm) अणु
		अगर (drv->pm->suspend)
			ret = drv->pm->suspend(dev);
	पूर्ण अन्यथा अणु
		ret = platक्रमm_legacy_suspend(dev, PMSG_SUSPEND);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक platक्रमm_pm_resume(काष्ठा device *dev)
अणु
	काष्ठा device_driver *drv = dev->driver;
	पूर्णांक ret = 0;

	अगर (!drv)
		वापस 0;

	अगर (drv->pm) अणु
		अगर (drv->pm->resume)
			ret = drv->pm->resume(dev);
	पूर्ण अन्यथा अणु
		ret = platक्रमm_legacy_resume(dev);
	पूर्ण

	वापस ret;
पूर्ण

#पूर्ण_अगर /* CONFIG_SUSPEND */

#अगर_घोषित CONFIG_HIBERNATE_CALLBACKS

पूर्णांक platक्रमm_pm_मुक्तze(काष्ठा device *dev)
अणु
	काष्ठा device_driver *drv = dev->driver;
	पूर्णांक ret = 0;

	अगर (!drv)
		वापस 0;

	अगर (drv->pm) अणु
		अगर (drv->pm->मुक्तze)
			ret = drv->pm->मुक्तze(dev);
	पूर्ण अन्यथा अणु
		ret = platक्रमm_legacy_suspend(dev, PMSG_FREEZE);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक platक्रमm_pm_thaw(काष्ठा device *dev)
अणु
	काष्ठा device_driver *drv = dev->driver;
	पूर्णांक ret = 0;

	अगर (!drv)
		वापस 0;

	अगर (drv->pm) अणु
		अगर (drv->pm->thaw)
			ret = drv->pm->thaw(dev);
	पूर्ण अन्यथा अणु
		ret = platक्रमm_legacy_resume(dev);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक platक्रमm_pm_घातeroff(काष्ठा device *dev)
अणु
	काष्ठा device_driver *drv = dev->driver;
	पूर्णांक ret = 0;

	अगर (!drv)
		वापस 0;

	अगर (drv->pm) अणु
		अगर (drv->pm->घातeroff)
			ret = drv->pm->घातeroff(dev);
	पूर्ण अन्यथा अणु
		ret = platक्रमm_legacy_suspend(dev, PMSG_HIBERNATE);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक platक्रमm_pm_restore(काष्ठा device *dev)
अणु
	काष्ठा device_driver *drv = dev->driver;
	पूर्णांक ret = 0;

	अगर (!drv)
		वापस 0;

	अगर (drv->pm) अणु
		अगर (drv->pm->restore)
			ret = drv->pm->restore(dev);
	पूर्ण अन्यथा अणु
		ret = platक्रमm_legacy_resume(dev);
	पूर्ण

	वापस ret;
पूर्ण

#पूर्ण_अगर /* CONFIG_HIBERNATE_CALLBACKS */

/* modalias support enables more hands-off userspace setup:
 * (a) environment variable lets new-style hotplug events work once प्रणाली is
 *     fully running:  "modprobe $MODALIAS"
 * (b) sysfs attribute lets new-style coldplug recover from hotplug events
 *     mishandled beक्रमe प्रणाली is fully running:  "modprobe $(cat modalias)"
 */
अटल sमाप_प्रकार modalias_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	पूर्णांक len;

	len = of_device_modalias(dev, buf, PAGE_SIZE);
	अगर (len != -ENODEV)
		वापस len;

	len = acpi_device_modalias(dev, buf, PAGE_SIZE - 1);
	अगर (len != -ENODEV)
		वापस len;

	वापस sysfs_emit(buf, "platform:%s\n", pdev->name);
पूर्ण
अटल DEVICE_ATTR_RO(modalias);

अटल sमाप_प्रकार numa_node_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%d\n", dev_to_node(dev));
पूर्ण
अटल DEVICE_ATTR_RO(numa_node);

अटल sमाप_प्रकार driver_override_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	sमाप_प्रकार len;

	device_lock(dev);
	len = sysfs_emit(buf, "%s\n", pdev->driver_override);
	device_unlock(dev);

	वापस len;
पूर्ण

अटल sमाप_प्रकार driver_override_store(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	अक्षर *driver_override, *old, *cp;

	/* We need to keep extra room क्रम a newline */
	अगर (count >= (PAGE_SIZE - 1))
		वापस -EINVAL;

	driver_override = kstrndup(buf, count, GFP_KERNEL);
	अगर (!driver_override)
		वापस -ENOMEM;

	cp = म_अक्षर(driver_override, '\n');
	अगर (cp)
		*cp = '\0';

	device_lock(dev);
	old = pdev->driver_override;
	अगर (म_माप(driver_override)) अणु
		pdev->driver_override = driver_override;
	पूर्ण अन्यथा अणु
		kमुक्त(driver_override);
		pdev->driver_override = शून्य;
	पूर्ण
	device_unlock(dev);

	kमुक्त(old);

	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(driver_override);

अटल काष्ठा attribute *platक्रमm_dev_attrs[] = अणु
	&dev_attr_modalias.attr,
	&dev_attr_numa_node.attr,
	&dev_attr_driver_override.attr,
	शून्य,
पूर्ण;

अटल umode_t platक्रमm_dev_attrs_visible(काष्ठा kobject *kobj, काष्ठा attribute *a,
		पूर्णांक n)
अणु
	काष्ठा device *dev = container_of(kobj, typeof(*dev), kobj);

	अगर (a == &dev_attr_numa_node.attr &&
			dev_to_node(dev) == NUMA_NO_NODE)
		वापस 0;

	वापस a->mode;
पूर्ण

अटल काष्ठा attribute_group platक्रमm_dev_group = अणु
	.attrs = platक्रमm_dev_attrs,
	.is_visible = platक्रमm_dev_attrs_visible,
पूर्ण;
__ATTRIBUTE_GROUPS(platक्रमm_dev);


/**
 * platक्रमm_match - bind platक्रमm device to platक्रमm driver.
 * @dev: device.
 * @drv: driver.
 *
 * Platक्रमm device IDs are assumed to be encoded like this:
 * "<name><instance>", where <name> is a लघु description of the type of
 * device, like "pci" or "floppy", and <instance> is the क्रमागतerated
 * instance of the device, like '0' or '42'.  Driver IDs are simply
 * "<name>".  So, extract the <name> from the platक्रमm_device काष्ठाure,
 * and compare it against the name of the driver. Return whether they match
 * or not.
 */
अटल पूर्णांक platक्रमm_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा platक्रमm_driver *pdrv = to_platक्रमm_driver(drv);

	/* When driver_override is set, only bind to the matching driver */
	अगर (pdev->driver_override)
		वापस !म_भेद(pdev->driver_override, drv->name);

	/* Attempt an OF style match first */
	अगर (of_driver_match_device(dev, drv))
		वापस 1;

	/* Then try ACPI style match */
	अगर (acpi_driver_match_device(dev, drv))
		वापस 1;

	/* Then try to match against the id table */
	अगर (pdrv->id_table)
		वापस platक्रमm_match_id(pdrv->id_table, pdev) != शून्य;

	/* fall-back to driver name match */
	वापस (म_भेद(pdev->name, drv->name) == 0);
पूर्ण

अटल पूर्णांक platक्रमm_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा platक्रमm_device	*pdev = to_platक्रमm_device(dev);
	पूर्णांक rc;

	/* Some devices have extra OF data and an OF-style MODALIAS */
	rc = of_device_uevent_modalias(dev, env);
	अगर (rc != -ENODEV)
		वापस rc;

	rc = acpi_device_uevent_modalias(dev, env);
	अगर (rc != -ENODEV)
		वापस rc;

	add_uevent_var(env, "MODALIAS=%s%s", PLATFORM_MODULE_PREFIX,
			pdev->name);
	वापस 0;
पूर्ण

अटल पूर्णांक platक्रमm_probe(काष्ठा device *_dev)
अणु
	काष्ठा platक्रमm_driver *drv = to_platक्रमm_driver(_dev->driver);
	काष्ठा platक्रमm_device *dev = to_platक्रमm_device(_dev);
	पूर्णांक ret;

	/*
	 * A driver रेजिस्टरed using platक्रमm_driver_probe() cannot be bound
	 * again later because the probe function usually lives in __init code
	 * and so is gone. For these drivers .probe is set to
	 * platक्रमm_probe_fail in __platक्रमm_driver_probe(). Don't even prepare
	 * घड़ीs and PM करोमुख्यs क्रम these to match the traditional behaviour.
	 */
	अगर (unlikely(drv->probe == platक्रमm_probe_fail))
		वापस -ENXIO;

	ret = of_clk_set_शेषs(_dev->of_node, false);
	अगर (ret < 0)
		वापस ret;

	ret = dev_pm_करोमुख्य_attach(_dev, true);
	अगर (ret)
		जाओ out;

	अगर (drv->probe) अणु
		ret = drv->probe(dev);
		अगर (ret)
			dev_pm_करोमुख्य_detach(_dev, true);
	पूर्ण

out:
	अगर (drv->prevent_deferred_probe && ret == -EPROBE_DEFER) अणु
		dev_warn(_dev, "probe deferral not supported\n");
		ret = -ENXIO;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक platक्रमm_हटाओ(काष्ठा device *_dev)
अणु
	काष्ठा platक्रमm_driver *drv = to_platक्रमm_driver(_dev->driver);
	काष्ठा platक्रमm_device *dev = to_platक्रमm_device(_dev);

	अगर (drv->हटाओ) अणु
		पूर्णांक ret = drv->हटाओ(dev);

		अगर (ret)
			dev_warn(_dev, "remove callback returned a non-zero value. This will be ignored.\n");
	पूर्ण
	dev_pm_करोमुख्य_detach(_dev, true);

	वापस 0;
पूर्ण

अटल व्योम platक्रमm_shutकरोwn(काष्ठा device *_dev)
अणु
	काष्ठा platक्रमm_device *dev = to_platक्रमm_device(_dev);
	काष्ठा platक्रमm_driver *drv;

	अगर (!_dev->driver)
		वापस;

	drv = to_platक्रमm_driver(_dev->driver);
	अगर (drv->shutकरोwn)
		drv->shutकरोwn(dev);
पूर्ण


पूर्णांक platक्रमm_dma_configure(काष्ठा device *dev)
अणु
	क्रमागत dev_dma_attr attr;
	पूर्णांक ret = 0;

	अगर (dev->of_node) अणु
		ret = of_dma_configure(dev, dev->of_node, true);
	पूर्ण अन्यथा अगर (has_acpi_companion(dev)) अणु
		attr = acpi_get_dma_attr(to_acpi_device_node(dev->fwnode));
		ret = acpi_dma_configure(dev, attr);
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops platक्रमm_dev_pm_ops = अणु
	.runसमय_suspend = pm_generic_runसमय_suspend,
	.runसमय_resume = pm_generic_runसमय_resume,
	USE_PLATFORM_PM_SLEEP_OPS
पूर्ण;

काष्ठा bus_type platक्रमm_bus_type = अणु
	.name		= "platform",
	.dev_groups	= platक्रमm_dev_groups,
	.match		= platक्रमm_match,
	.uevent		= platक्रमm_uevent,
	.probe		= platक्रमm_probe,
	.हटाओ		= platक्रमm_हटाओ,
	.shutकरोwn	= platक्रमm_shutकरोwn,
	.dma_configure	= platक्रमm_dma_configure,
	.pm		= &platक्रमm_dev_pm_ops,
पूर्ण;
EXPORT_SYMBOL_GPL(platक्रमm_bus_type);

अटल अंतरभूत पूर्णांक __platक्रमm_match(काष्ठा device *dev, स्थिर व्योम *drv)
अणु
	वापस platक्रमm_match(dev, (काष्ठा device_driver *)drv);
पूर्ण

/**
 * platक्रमm_find_device_by_driver - Find a platक्रमm device with a given
 * driver.
 * @start: The device to start the search from.
 * @drv: The device driver to look क्रम.
 */
काष्ठा device *platक्रमm_find_device_by_driver(काष्ठा device *start,
					      स्थिर काष्ठा device_driver *drv)
अणु
	वापस bus_find_device(&platक्रमm_bus_type, start, drv,
			       __platक्रमm_match);
पूर्ण
EXPORT_SYMBOL_GPL(platक्रमm_find_device_by_driver);

व्योम __weak __init early_platक्रमm_cleanup(व्योम) अणु पूर्ण

पूर्णांक __init platक्रमm_bus_init(व्योम)
अणु
	पूर्णांक error;

	early_platक्रमm_cleanup();

	error = device_रेजिस्टर(&platक्रमm_bus);
	अगर (error) अणु
		put_device(&platक्रमm_bus);
		वापस error;
	पूर्ण
	error =  bus_रेजिस्टर(&platक्रमm_bus_type);
	अगर (error)
		device_unरेजिस्टर(&platक्रमm_bus);
	of_platक्रमm_रेजिस्टर_reconfig_notअगरier();
	वापस error;
पूर्ण
