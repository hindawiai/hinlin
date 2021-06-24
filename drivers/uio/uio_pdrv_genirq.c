<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * drivers/uio/uio_pdrv_genirq.c
 *
 * Userspace I/O platक्रमm driver with generic IRQ handling code.
 *
 * Copyright (C) 2008 Magnus Damm
 *
 * Based on uio_pdrv.c by Uwe Kleine-Koenig,
 * Copyright (C) 2008 by Digi International Inc.
 * All rights reserved.
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/uio_driver.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/bitops.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/stringअगरy.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>
#समावेश <linux/irq.h>

#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_address.h>

#घोषणा DRIVER_NAME "uio_pdrv_genirq"

काष्ठा uio_pdrv_genirq_platdata अणु
	काष्ठा uio_info *uioinfo;
	spinlock_t lock;
	अचिन्हित दीर्घ flags;
	काष्ठा platक्रमm_device *pdev;
पूर्ण;

/* Bits in uio_pdrv_genirq_platdata.flags */
क्रमागत अणु
	UIO_IRQ_DISABLED = 0,
पूर्ण;

अटल पूर्णांक uio_pdrv_genirq_खोलो(काष्ठा uio_info *info, काष्ठा inode *inode)
अणु
	काष्ठा uio_pdrv_genirq_platdata *priv = info->priv;

	/* Wait until the Runसमय PM code has woken up the device */
	pm_runसमय_get_sync(&priv->pdev->dev);
	वापस 0;
पूर्ण

अटल पूर्णांक uio_pdrv_genirq_release(काष्ठा uio_info *info, काष्ठा inode *inode)
अणु
	काष्ठा uio_pdrv_genirq_platdata *priv = info->priv;

	/* Tell the Runसमय PM code that the device has become idle */
	pm_runसमय_put_sync(&priv->pdev->dev);
	वापस 0;
पूर्ण

अटल irqवापस_t uio_pdrv_genirq_handler(पूर्णांक irq, काष्ठा uio_info *dev_info)
अणु
	काष्ठा uio_pdrv_genirq_platdata *priv = dev_info->priv;

	/* Just disable the पूर्णांकerrupt in the पूर्णांकerrupt controller, and
	 * remember the state so we can allow user space to enable it later.
	 */

	spin_lock(&priv->lock);
	अगर (!__test_and_set_bit(UIO_IRQ_DISABLED, &priv->flags))
		disable_irq_nosync(irq);
	spin_unlock(&priv->lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक uio_pdrv_genirq_irqcontrol(काष्ठा uio_info *dev_info, s32 irq_on)
अणु
	काष्ठा uio_pdrv_genirq_platdata *priv = dev_info->priv;
	अचिन्हित दीर्घ flags;

	/* Allow user space to enable and disable the पूर्णांकerrupt
	 * in the पूर्णांकerrupt controller, but keep track of the
	 * state to prevent per-irq depth damage.
	 *
	 * Serialize this operation to support multiple tasks and concurrency
	 * with irq handler on SMP प्रणालीs.
	 */

	spin_lock_irqsave(&priv->lock, flags);
	अगर (irq_on) अणु
		अगर (__test_and_clear_bit(UIO_IRQ_DISABLED, &priv->flags))
			enable_irq(dev_info->irq);
	पूर्ण अन्यथा अणु
		अगर (!__test_and_set_bit(UIO_IRQ_DISABLED, &priv->flags))
			disable_irq_nosync(dev_info->irq);
	पूर्ण
	spin_unlock_irqrestore(&priv->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम uio_pdrv_genirq_cleanup(व्योम *data)
अणु
	काष्ठा device *dev = data;

	pm_runसमय_disable(dev);
पूर्ण

अटल पूर्णांक uio_pdrv_genirq_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा uio_info *uioinfo = dev_get_platdata(&pdev->dev);
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा uio_pdrv_genirq_platdata *priv;
	काष्ठा uio_mem *uiomem;
	पूर्णांक ret = -EINVAL;
	पूर्णांक i;

	अगर (node) अणु
		स्थिर अक्षर *name;

		/* alloc uioinfo क्रम one device */
		uioinfo = devm_kzalloc(&pdev->dev, माप(*uioinfo),
				       GFP_KERNEL);
		अगर (!uioinfo) अणु
			dev_err(&pdev->dev, "unable to kmalloc\n");
			वापस -ENOMEM;
		पूर्ण

		अगर (!of_property_पढ़ो_string(node, "linux,uio-name", &name))
			uioinfo->name = devm_kstrdup(&pdev->dev, name, GFP_KERNEL);
		अन्यथा
			uioinfo->name = devm_kaप्र_लिखो(&pdev->dev, GFP_KERNEL,
						       "%pOFn", node);

		uioinfo->version = "devicetree";
		/* Multiple IRQs are not supported */
	पूर्ण

	अगर (!uioinfo || !uioinfo->name || !uioinfo->version) अणु
		dev_err(&pdev->dev, "missing platform_data\n");
		वापस ret;
	पूर्ण

	अगर (uioinfo->handler || uioinfo->irqcontrol ||
	    uioinfo->irq_flags & IRQF_SHARED) अणु
		dev_err(&pdev->dev, "interrupt configuration error\n");
		वापस ret;
	पूर्ण

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv) अणु
		dev_err(&pdev->dev, "unable to kmalloc\n");
		वापस -ENOMEM;
	पूर्ण

	priv->uioinfo = uioinfo;
	spin_lock_init(&priv->lock);
	priv->flags = 0; /* पूर्णांकerrupt is enabled to begin with */
	priv->pdev = pdev;

	अगर (!uioinfo->irq) अणु
		ret = platक्रमm_get_irq_optional(pdev, 0);
		uioinfo->irq = ret;
		अगर (ret == -ENXIO)
			uioinfo->irq = UIO_IRQ_NONE;
		अन्यथा अगर (ret == -EPROBE_DEFER)
			वापस ret;
		अन्यथा अगर (ret < 0) अणु
			dev_err(&pdev->dev, "failed to get IRQ\n");
			वापस ret;
		पूर्ण
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
		uiomem->addr = r->start & PAGE_MASK;
		uiomem->offs = r->start & ~PAGE_MASK;
		uiomem->size = (uiomem->offs + resource_size(r)
				+ PAGE_SIZE - 1) & PAGE_MASK;
		uiomem->name = r->name;
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

	uioinfo->handler = uio_pdrv_genirq_handler;
	uioinfo->irqcontrol = uio_pdrv_genirq_irqcontrol;
	uioinfo->खोलो = uio_pdrv_genirq_खोलो;
	uioinfo->release = uio_pdrv_genirq_release;
	uioinfo->priv = priv;

	/* Enable Runसमय PM क्रम this device:
	 * The device starts in suspended state to allow the hardware to be
	 * turned off by शेष. The Runसमय PM bus code should घातer on the
	 * hardware and enable घड़ीs at खोलो().
	 */
	pm_runसमय_enable(&pdev->dev);

	ret = devm_add_action_or_reset(&pdev->dev, uio_pdrv_genirq_cleanup,
				       &pdev->dev);
	अगर (ret)
		वापस ret;

	ret = devm_uio_रेजिस्टर_device(&pdev->dev, priv->uioinfo);
	अगर (ret)
		dev_err(&pdev->dev, "unable to register uio device\n");

	वापस ret;
पूर्ण

अटल पूर्णांक uio_pdrv_genirq_runसमय_nop(काष्ठा device *dev)
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

अटल स्थिर काष्ठा dev_pm_ops uio_pdrv_genirq_dev_pm_ops = अणु
	.runसमय_suspend = uio_pdrv_genirq_runसमय_nop,
	.runसमय_resume = uio_pdrv_genirq_runसमय_nop,
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल काष्ठा of_device_id uio_of_genirq_match[] = अणु
	अणु /* This is filled with module_parm */ पूर्ण,
	अणु /* Sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, uio_of_genirq_match);
module_param_string(of_id, uio_of_genirq_match[0].compatible, 128, 0);
MODULE_PARM_DESC(of_id, "Openfirmware id of the device to be handled by uio");
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver uio_pdrv_genirq = अणु
	.probe = uio_pdrv_genirq_probe,
	.driver = अणु
		.name = DRIVER_NAME,
		.pm = &uio_pdrv_genirq_dev_pm_ops,
		.of_match_table = of_match_ptr(uio_of_genirq_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(uio_pdrv_genirq);

MODULE_AUTHOR("Magnus Damm");
MODULE_DESCRIPTION("Userspace I/O platform driver with generic IRQ handling");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:" DRIVER_NAME);
