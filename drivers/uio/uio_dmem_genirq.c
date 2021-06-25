<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * drivers/uio/uio_dmem_genirq.c
 *
 * Userspace I/O platक्रमm driver with generic IRQ handling code.
 *
 * Copyright (C) 2012 Damian Hobson-Garcia
 *
 * Based on uio_pdrv_genirq.c by Magnus Damm
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/uio_driver.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/bitops.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_data/uio_dmem_genirq.h>
#समावेश <linux/stringअगरy.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/slab.h>
#समावेश <linux/irq.h>

#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_address.h>

#घोषणा DRIVER_NAME "uio_dmem_genirq"
#घोषणा DMEM_MAP_ERROR (~0)

काष्ठा uio_dmem_genirq_platdata अणु
	काष्ठा uio_info *uioinfo;
	spinlock_t lock;
	अचिन्हित दीर्घ flags;
	काष्ठा platक्रमm_device *pdev;
	अचिन्हित पूर्णांक dmem_region_start;
	अचिन्हित पूर्णांक num_dmem_regions;
	व्योम *dmem_region_vaddr[MAX_UIO_MAPS];
	काष्ठा mutex alloc_lock;
	अचिन्हित पूर्णांक refcnt;
पूर्ण;

अटल पूर्णांक uio_dmem_genirq_खोलो(काष्ठा uio_info *info, काष्ठा inode *inode)
अणु
	काष्ठा uio_dmem_genirq_platdata *priv = info->priv;
	काष्ठा uio_mem *uiomem;
	पूर्णांक dmem_region = priv->dmem_region_start;

	uiomem = &priv->uioinfo->mem[priv->dmem_region_start];

	mutex_lock(&priv->alloc_lock);
	जबतक (!priv->refcnt && uiomem < &priv->uioinfo->mem[MAX_UIO_MAPS]) अणु
		व्योम *addr;
		अगर (!uiomem->size)
			अवरोध;

		addr = dma_alloc_coherent(&priv->pdev->dev, uiomem->size,
				(dma_addr_t *)&uiomem->addr, GFP_KERNEL);
		अगर (!addr) अणु
			uiomem->addr = DMEM_MAP_ERROR;
		पूर्ण
		priv->dmem_region_vaddr[dmem_region++] = addr;
		++uiomem;
	पूर्ण
	priv->refcnt++;

	mutex_unlock(&priv->alloc_lock);
	/* Wait until the Runसमय PM code has woken up the device */
	pm_runसमय_get_sync(&priv->pdev->dev);
	वापस 0;
पूर्ण

अटल पूर्णांक uio_dmem_genirq_release(काष्ठा uio_info *info, काष्ठा inode *inode)
अणु
	काष्ठा uio_dmem_genirq_platdata *priv = info->priv;
	काष्ठा uio_mem *uiomem;
	पूर्णांक dmem_region = priv->dmem_region_start;

	/* Tell the Runसमय PM code that the device has become idle */
	pm_runसमय_put_sync(&priv->pdev->dev);

	uiomem = &priv->uioinfo->mem[priv->dmem_region_start];

	mutex_lock(&priv->alloc_lock);

	priv->refcnt--;
	जबतक (!priv->refcnt && uiomem < &priv->uioinfo->mem[MAX_UIO_MAPS]) अणु
		अगर (!uiomem->size)
			अवरोध;
		अगर (priv->dmem_region_vaddr[dmem_region]) अणु
			dma_मुक्त_coherent(&priv->pdev->dev, uiomem->size,
					priv->dmem_region_vaddr[dmem_region],
					uiomem->addr);
		पूर्ण
		uiomem->addr = DMEM_MAP_ERROR;
		++dmem_region;
		++uiomem;
	पूर्ण

	mutex_unlock(&priv->alloc_lock);
	वापस 0;
पूर्ण

अटल irqवापस_t uio_dmem_genirq_handler(पूर्णांक irq, काष्ठा uio_info *dev_info)
अणु
	काष्ठा uio_dmem_genirq_platdata *priv = dev_info->priv;

	/* Just disable the पूर्णांकerrupt in the पूर्णांकerrupt controller, and
	 * remember the state so we can allow user space to enable it later.
	 */

	अगर (!test_and_set_bit(0, &priv->flags))
		disable_irq_nosync(irq);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक uio_dmem_genirq_irqcontrol(काष्ठा uio_info *dev_info, s32 irq_on)
अणु
	काष्ठा uio_dmem_genirq_platdata *priv = dev_info->priv;
	अचिन्हित दीर्घ flags;

	/* Allow user space to enable and disable the पूर्णांकerrupt
	 * in the पूर्णांकerrupt controller, but keep track of the
	 * state to prevent per-irq depth damage.
	 *
	 * Serialize this operation to support multiple tasks.
	 */

	spin_lock_irqsave(&priv->lock, flags);
	अगर (irq_on) अणु
		अगर (test_and_clear_bit(0, &priv->flags))
			enable_irq(dev_info->irq);
		spin_unlock_irqrestore(&priv->lock, flags);
	पूर्ण अन्यथा अणु
		अगर (!test_and_set_bit(0, &priv->flags)) अणु
			spin_unlock_irqrestore(&priv->lock, flags);
			disable_irq(dev_info->irq);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम uio_dmem_genirq_pm_disable(व्योम *data)
अणु
	काष्ठा device *dev = data;

	pm_runसमय_disable(dev);
पूर्ण

अटल पूर्णांक uio_dmem_genirq_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा uio_dmem_genirq_pdata *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा uio_info *uioinfo = &pdata->uioinfo;
	काष्ठा uio_dmem_genirq_platdata *priv;
	काष्ठा uio_mem *uiomem;
	पूर्णांक ret = -EINVAL;
	पूर्णांक i;

	अगर (pdev->dev.of_node) अणु
		/* alloc uioinfo क्रम one device */
		uioinfo = devm_kzalloc(&pdev->dev, माप(*uioinfo), GFP_KERNEL);
		अगर (!uioinfo) अणु
			dev_err(&pdev->dev, "unable to kmalloc\n");
			वापस -ENOMEM;
		पूर्ण
		uioinfo->name = devm_kaप्र_लिखो(&pdev->dev, GFP_KERNEL, "%pOFn",
					       pdev->dev.of_node);
		uioinfo->version = "devicetree";
	पूर्ण

	अगर (!uioinfo || !uioinfo->name || !uioinfo->version) अणु
		dev_err(&pdev->dev, "missing platform_data\n");
		वापस -EINVAL;
	पूर्ण

	अगर (uioinfo->handler || uioinfo->irqcontrol ||
	    uioinfo->irq_flags & IRQF_SHARED) अणु
		dev_err(&pdev->dev, "interrupt configuration error\n");
		वापस -EINVAL;
	पूर्ण

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv) अणु
		dev_err(&pdev->dev, "unable to kmalloc\n");
		वापस -ENOMEM;
	पूर्ण

	dma_set_coherent_mask(&pdev->dev, DMA_BIT_MASK(32));

	priv->uioinfo = uioinfo;
	spin_lock_init(&priv->lock);
	priv->flags = 0; /* पूर्णांकerrupt is enabled to begin with */
	priv->pdev = pdev;
	mutex_init(&priv->alloc_lock);

	अगर (!uioinfo->irq) अणु
		/* Multiple IRQs are not supported */
		ret = platक्रमm_get_irq(pdev, 0);
		अगर (ret == -ENXIO && pdev->dev.of_node)
			ret = UIO_IRQ_NONE;
		अन्यथा अगर (ret < 0)
			वापस ret;
		uioinfo->irq = ret;
	पूर्ण

	अगर (uioinfo->irq) अणु
		काष्ठा irq_data *irq_data = irq_get_irq_data(uioinfo->irq);

		/*
		 * If a level पूर्णांकerrupt, करोnt करो lazy disable. Otherwise the
		 * irq will fire again since clearing of the actual cause, on
		 * device level, is करोne in userspace
		 * irqd_is_level_type() isn't used since isn't valid until
		 * irq is configured.
		 */
		अगर (irq_data &&
		    irqd_get_trigger_type(irq_data) & IRQ_TYPE_LEVEL_MASK) अणु
			dev_dbg(&pdev->dev, "disable lazy unmask\n");
			irq_set_status_flags(uioinfo->irq, IRQ_DISABLE_UNLAZY);
		पूर्ण
	पूर्ण

	uiomem = &uioinfo->mem[0];

	क्रम (i = 0; i < pdev->num_resources; ++i) अणु
		काष्ठा resource *r = &pdev->resource[i];

		अगर (r->flags != IORESOURCE_MEM)
			जारी;

		अगर (uiomem >= &uioinfo->mem[MAX_UIO_MAPS]) अणु
			dev_warn(&pdev->dev, "device has more than "
					__stringअगरy(MAX_UIO_MAPS)
					" I/O memory resources.\n");
			अवरोध;
		पूर्ण

		uiomem->memtype = UIO_MEM_PHYS;
		uiomem->addr = r->start;
		uiomem->size = resource_size(r);
		++uiomem;
	पूर्ण

	priv->dmem_region_start = uiomem - &uioinfo->mem[0];
	priv->num_dmem_regions = pdata->num_dynamic_regions;

	क्रम (i = 0; i < pdata->num_dynamic_regions; ++i) अणु
		अगर (uiomem >= &uioinfo->mem[MAX_UIO_MAPS]) अणु
			dev_warn(&pdev->dev, "device has more than "
					__stringअगरy(MAX_UIO_MAPS)
					" dynamic and fixed memory regions.\n");
			अवरोध;
		पूर्ण
		uiomem->memtype = UIO_MEM_PHYS;
		uiomem->addr = DMEM_MAP_ERROR;
		uiomem->size = pdata->dynamic_region_sizes[i];
		++uiomem;
	पूर्ण

	जबतक (uiomem < &uioinfo->mem[MAX_UIO_MAPS]) अणु
		uiomem->size = 0;
		++uiomem;
	पूर्ण

	/* This driver requires no hardware specअगरic kernel code to handle
	 * पूर्णांकerrupts. Instead, the पूर्णांकerrupt handler simply disables the
	 * पूर्णांकerrupt in the पूर्णांकerrupt controller. User space is responsible
	 * क्रम perक्रमming hardware specअगरic acknowledge and re-enabling of
	 * the पूर्णांकerrupt in the पूर्णांकerrupt controller.
	 *
	 * Interrupt sharing is not supported.
	 */

	uioinfo->handler = uio_dmem_genirq_handler;
	uioinfo->irqcontrol = uio_dmem_genirq_irqcontrol;
	uioinfo->खोलो = uio_dmem_genirq_खोलो;
	uioinfo->release = uio_dmem_genirq_release;
	uioinfo->priv = priv;

	/* Enable Runसमय PM क्रम this device:
	 * The device starts in suspended state to allow the hardware to be
	 * turned off by शेष. The Runसमय PM bus code should घातer on the
	 * hardware and enable घड़ीs at खोलो().
	 */
	pm_runसमय_enable(&pdev->dev);

	ret = devm_add_action_or_reset(&pdev->dev, uio_dmem_genirq_pm_disable, &pdev->dev);
	अगर (ret)
		वापस ret;

	वापस devm_uio_रेजिस्टर_device(&pdev->dev, priv->uioinfo);
पूर्ण

अटल पूर्णांक uio_dmem_genirq_runसमय_nop(काष्ठा device *dev)
अणु
	/* Runसमय PM callback shared between ->runसमय_suspend()
	 * and ->runसमय_resume(). Simply वापसs success.
	 *
	 * In this driver pm_runसमय_get_sync() and pm_runसमय_put_sync()
	 * are used at खोलो() and release() समय. This allows the
	 * Runसमय PM code to turn off घातer to the device जबतक the
	 * device is unused, ie beक्रमe खोलो() and after release().
	 *
	 * This Runसमय PM callback करोes not need to save or restore
	 * any रेजिस्टरs since user space is responsbile क्रम hardware
	 * रेजिस्टर reinitialization after खोलो().
	 */
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops uio_dmem_genirq_dev_pm_ops = अणु
	.runसमय_suspend = uio_dmem_genirq_runसमय_nop,
	.runसमय_resume = uio_dmem_genirq_runसमय_nop,
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id uio_of_genirq_match[] = अणु
	अणु /* empty क्रम now */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, uio_of_genirq_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver uio_dmem_genirq = अणु
	.probe = uio_dmem_genirq_probe,
	.driver = अणु
		.name = DRIVER_NAME,
		.pm = &uio_dmem_genirq_dev_pm_ops,
		.of_match_table = of_match_ptr(uio_of_genirq_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(uio_dmem_genirq);

MODULE_AUTHOR("Damian Hobson-Garcia");
MODULE_DESCRIPTION("Userspace I/O platform driver with dynamic memory.");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:" DRIVER_NAME);
