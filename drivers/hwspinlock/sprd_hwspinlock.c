<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Spपढ़ोtrum hardware spinlock driver
 * Copyright (C) 2017 Spपढ़ोtrum  - http://www.spपढ़ोtrum.com
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/hwspinlock.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "hwspinlock_internal.h"

/* hwspinlock रेजिस्टरs definition */
#घोषणा HWSPINLOCK_RECCTRL		0x4
#घोषणा HWSPINLOCK_MASTERID(_X_)	(0x80 + 0x4 * (_X_))
#घोषणा HWSPINLOCK_TOKEN(_X_)		(0x800 + 0x4 * (_X_))

/* unlocked value */
#घोषणा HWSPINLOCK_NOTTAKEN		0x55aa10c5
/* bits definition of RECCTRL reg */
#घोषणा HWSPINLOCK_USER_BITS		0x1

/* hwspinlock number */
#घोषणा SPRD_HWLOCKS_NUM		32

काष्ठा sprd_hwspinlock_dev अणु
	व्योम __iomem *base;
	काष्ठा clk *clk;
	काष्ठा hwspinlock_device bank;
पूर्ण;

/* try to lock the hardware spinlock */
अटल पूर्णांक sprd_hwspinlock_trylock(काष्ठा hwspinlock *lock)
अणु
	काष्ठा sprd_hwspinlock_dev *sprd_hwlock =
		dev_get_drvdata(lock->bank->dev);
	व्योम __iomem *addr = lock->priv;
	पूर्णांक user_id, lock_id;

	अगर (!पढ़ोl(addr))
		वापस 1;

	lock_id = hwlock_to_id(lock);
	/* get the hardware spinlock master/user id */
	user_id = पढ़ोl(sprd_hwlock->base + HWSPINLOCK_MASTERID(lock_id));
	dev_warn(sprd_hwlock->bank.dev,
		 "hwspinlock [%d] lock failed and master/user id = %d!\n",
		 lock_id, user_id);
	वापस 0;
पूर्ण

/* unlock the hardware spinlock */
अटल व्योम sprd_hwspinlock_unlock(काष्ठा hwspinlock *lock)
अणु
	व्योम __iomem *lock_addr = lock->priv;

	ग_लिखोl(HWSPINLOCK_NOTTAKEN, lock_addr);
पूर्ण

/* The specs recommended below number as the retry delay समय */
अटल व्योम sprd_hwspinlock_relax(काष्ठा hwspinlock *lock)
अणु
	ndelay(10);
पूर्ण

अटल स्थिर काष्ठा hwspinlock_ops sprd_hwspinlock_ops = अणु
	.trylock = sprd_hwspinlock_trylock,
	.unlock = sprd_hwspinlock_unlock,
	.relax = sprd_hwspinlock_relax,
पूर्ण;

अटल व्योम sprd_hwspinlock_disable(व्योम *data)
अणु
	काष्ठा sprd_hwspinlock_dev *sprd_hwlock = data;

	clk_disable_unprepare(sprd_hwlock->clk);
पूर्ण

अटल पूर्णांक sprd_hwspinlock_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sprd_hwspinlock_dev *sprd_hwlock;
	काष्ठा hwspinlock *lock;
	पूर्णांक i, ret;

	अगर (!pdev->dev.of_node)
		वापस -ENODEV;

	sprd_hwlock = devm_kzalloc(&pdev->dev,
				   माप(काष्ठा sprd_hwspinlock_dev) +
				   SPRD_HWLOCKS_NUM * माप(*lock),
				   GFP_KERNEL);
	अगर (!sprd_hwlock)
		वापस -ENOMEM;

	sprd_hwlock->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(sprd_hwlock->base))
		वापस PTR_ERR(sprd_hwlock->base);

	sprd_hwlock->clk = devm_clk_get(&pdev->dev, "enable");
	अगर (IS_ERR(sprd_hwlock->clk)) अणु
		dev_err(&pdev->dev, "get hwspinlock clock failed!\n");
		वापस PTR_ERR(sprd_hwlock->clk);
	पूर्ण

	ret = clk_prepare_enable(sprd_hwlock->clk);
	अगर (ret)
		वापस ret;

	ret = devm_add_action_or_reset(&pdev->dev, sprd_hwspinlock_disable,
				       sprd_hwlock);
	अगर (ret) अणु
		dev_err(&pdev->dev,
			"Failed to add hwspinlock disable action\n");
		वापस ret;
	पूर्ण

	/* set the hwspinlock to record user id to identअगरy subप्रणालीs */
	ग_लिखोl(HWSPINLOCK_USER_BITS, sprd_hwlock->base + HWSPINLOCK_RECCTRL);

	क्रम (i = 0; i < SPRD_HWLOCKS_NUM; i++) अणु
		lock = &sprd_hwlock->bank.lock[i];
		lock->priv = sprd_hwlock->base + HWSPINLOCK_TOKEN(i);
	पूर्ण

	platक्रमm_set_drvdata(pdev, sprd_hwlock);

	वापस devm_hwspin_lock_रेजिस्टर(&pdev->dev, &sprd_hwlock->bank,
					 &sprd_hwspinlock_ops, 0,
					 SPRD_HWLOCKS_NUM);
पूर्ण

अटल स्थिर काष्ठा of_device_id sprd_hwspinlock_of_match[] = अणु
	अणु .compatible = "sprd,hwspinlock-r3p0", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sprd_hwspinlock_of_match);

अटल काष्ठा platक्रमm_driver sprd_hwspinlock_driver = अणु
	.probe = sprd_hwspinlock_probe,
	.driver = अणु
		.name = "sprd_hwspinlock",
		.of_match_table = sprd_hwspinlock_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sprd_hwspinlock_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Hardware spinlock driver for Spreadtrum");
MODULE_AUTHOR("Baolin Wang <baolin.wang@spreadtrum.com>");
MODULE_AUTHOR("Lanqing Liu <lanqing.liu@spreadtrum.com>");
MODULE_AUTHOR("Long Cheng <aiden.cheng@spreadtrum.com>");
