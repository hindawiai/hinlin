<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * OMAP hardware spinlock driver
 *
 * Copyright (C) 2010-2021 Texas Instruments Incorporated - https://www.ti.com
 *
 * Contact: Simon Que <sque@ti.com>
 *          Hari Kanigeri <h-kanigeri2@ti.com>
 *          Ohad Ben-Cohen <ohad@wizery.com>
 *          Suman Anna <s-anna@ti.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/bitops.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/hwspinlock.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "hwspinlock_internal.h"

/* Spinlock रेजिस्टर offsets */
#घोषणा SYSSTATUS_OFFSET		0x0014
#घोषणा LOCK_BASE_OFFSET		0x0800

#घोषणा SPINLOCK_NUMLOCKS_BIT_OFFSET	(24)

/* Possible values of SPINLOCK_LOCK_REG */
#घोषणा SPINLOCK_NOTTAKEN		(0)	/* मुक्त */
#घोषणा SPINLOCK_TAKEN			(1)	/* locked */

अटल पूर्णांक omap_hwspinlock_trylock(काष्ठा hwspinlock *lock)
अणु
	व्योम __iomem *lock_addr = lock->priv;

	/* attempt to acquire the lock by पढ़ोing its value */
	वापस (SPINLOCK_NOTTAKEN == पढ़ोl(lock_addr));
पूर्ण

अटल व्योम omap_hwspinlock_unlock(काष्ठा hwspinlock *lock)
अणु
	व्योम __iomem *lock_addr = lock->priv;

	/* release the lock by writing 0 to it */
	ग_लिखोl(SPINLOCK_NOTTAKEN, lock_addr);
पूर्ण

/*
 * relax the OMAP पूर्णांकerconnect जबतक spinning on it.
 *
 * The specs recommended that the retry delay समय will be
 * just over half of the समय that a requester would be
 * expected to hold the lock.
 *
 * The number below is taken from an hardware specs example,
 * obviously it is somewhat arbitrary.
 */
अटल व्योम omap_hwspinlock_relax(काष्ठा hwspinlock *lock)
अणु
	ndelay(50);
पूर्ण

अटल स्थिर काष्ठा hwspinlock_ops omap_hwspinlock_ops = अणु
	.trylock = omap_hwspinlock_trylock,
	.unlock = omap_hwspinlock_unlock,
	.relax = omap_hwspinlock_relax,
पूर्ण;

अटल पूर्णांक omap_hwspinlock_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा hwspinlock_device *bank;
	काष्ठा hwspinlock *hwlock;
	व्योम __iomem *io_base;
	पूर्णांक num_locks, i, ret;
	/* Only a single hwspinlock block device is supported */
	पूर्णांक base_id = 0;

	अगर (!node)
		वापस -ENODEV;

	io_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(io_base))
		वापस PTR_ERR(io_base);

	/*
	 * make sure the module is enabled and घड़ीed beक्रमe पढ़ोing
	 * the module SYSSTATUS रेजिस्टर
	 */
	pm_runसमय_enable(&pdev->dev);
	ret = pm_runसमय_get_sync(&pdev->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(&pdev->dev);
		जाओ runसमय_err;
	पूर्ण

	/* Determine number of locks */
	i = पढ़ोl(io_base + SYSSTATUS_OFFSET);
	i >>= SPINLOCK_NUMLOCKS_BIT_OFFSET;

	/*
	 * runसमय PM will make sure the घड़ी of this module is
	 * enabled again अगरf at least one lock is requested
	 */
	ret = pm_runसमय_put(&pdev->dev);
	अगर (ret < 0)
		जाओ runसमय_err;

	/* one of the four lsb's must be set, and nothing अन्यथा */
	अगर (hweight_दीर्घ(i & 0xf) != 1 || i > 8) अणु
		ret = -EINVAL;
		जाओ runसमय_err;
	पूर्ण

	num_locks = i * 32; /* actual number of locks in this device */

	bank = devm_kzalloc(&pdev->dev, काष्ठा_size(bank, lock, num_locks),
			    GFP_KERNEL);
	अगर (!bank) अणु
		ret = -ENOMEM;
		जाओ runसमय_err;
	पूर्ण

	platक्रमm_set_drvdata(pdev, bank);

	क्रम (i = 0, hwlock = &bank->lock[0]; i < num_locks; i++, hwlock++)
		hwlock->priv = io_base + LOCK_BASE_OFFSET + माप(u32) * i;

	ret = hwspin_lock_रेजिस्टर(bank, &pdev->dev, &omap_hwspinlock_ops,
						base_id, num_locks);
	अगर (ret)
		जाओ runसमय_err;

	dev_dbg(&pdev->dev, "Registered %d locks with HwSpinlock core\n",
		num_locks);

	वापस 0;

runसमय_err:
	pm_runसमय_disable(&pdev->dev);
	वापस ret;
पूर्ण

अटल पूर्णांक omap_hwspinlock_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hwspinlock_device *bank = platक्रमm_get_drvdata(pdev);
	पूर्णांक ret;

	ret = hwspin_lock_unरेजिस्टर(bank);
	अगर (ret) अणु
		dev_err(&pdev->dev, "%s failed: %d\n", __func__, ret);
		वापस ret;
	पूर्ण

	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id omap_hwspinlock_of_match[] = अणु
	अणु .compatible = "ti,omap4-hwspinlock", पूर्ण,
	अणु .compatible = "ti,am64-hwspinlock", पूर्ण,
	अणु .compatible = "ti,am654-hwspinlock", पूर्ण,
	अणु /* end */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, omap_hwspinlock_of_match);

अटल काष्ठा platक्रमm_driver omap_hwspinlock_driver = अणु
	.probe		= omap_hwspinlock_probe,
	.हटाओ		= omap_hwspinlock_हटाओ,
	.driver		= अणु
		.name	= "omap_hwspinlock",
		.of_match_table = of_match_ptr(omap_hwspinlock_of_match),
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init omap_hwspinlock_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&omap_hwspinlock_driver);
पूर्ण
/* board init code might need to reserve hwspinlocks क्रम predefined purposes */
postcore_initcall(omap_hwspinlock_init);

अटल व्योम __निकास omap_hwspinlock_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&omap_hwspinlock_driver);
पूर्ण
module_निकास(omap_hwspinlock_निकास);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Hardware spinlock driver for OMAP");
MODULE_AUTHOR("Simon Que <sque@ti.com>");
MODULE_AUTHOR("Hari Kanigeri <h-kanigeri2@ti.com>");
MODULE_AUTHOR("Ohad Ben-Cohen <ohad@wizery.com>");
