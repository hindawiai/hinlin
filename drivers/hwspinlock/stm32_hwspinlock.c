<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) STMicroelectronics SA 2018
 * Author: Benjamin Gaignard <benjamin.gaignard@st.com> क्रम STMicroelectronics.
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/hwspinlock.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>

#समावेश "hwspinlock_internal.h"

#घोषणा STM32_MUTEX_COREID	BIT(8)
#घोषणा STM32_MUTEX_LOCK_BIT	BIT(31)
#घोषणा STM32_MUTEX_NUM_LOCKS	32

काष्ठा sपंचांग32_hwspinlock अणु
	काष्ठा clk *clk;
	काष्ठा hwspinlock_device bank;
पूर्ण;

अटल पूर्णांक sपंचांग32_hwspinlock_trylock(काष्ठा hwspinlock *lock)
अणु
	व्योम __iomem *lock_addr = lock->priv;
	u32 status;

	ग_लिखोl(STM32_MUTEX_LOCK_BIT | STM32_MUTEX_COREID, lock_addr);
	status = पढ़ोl(lock_addr);

	वापस status == (STM32_MUTEX_LOCK_BIT | STM32_MUTEX_COREID);
पूर्ण

अटल व्योम sपंचांग32_hwspinlock_unlock(काष्ठा hwspinlock *lock)
अणु
	व्योम __iomem *lock_addr = lock->priv;

	ग_लिखोl(STM32_MUTEX_COREID, lock_addr);
पूर्ण

अटल व्योम sपंचांग32_hwspinlock_relax(काष्ठा hwspinlock *lock)
अणु
	ndelay(50);
पूर्ण

अटल स्थिर काष्ठा hwspinlock_ops sपंचांग32_hwspinlock_ops = अणु
	.trylock	= sपंचांग32_hwspinlock_trylock,
	.unlock		= sपंचांग32_hwspinlock_unlock,
	.relax		= sपंचांग32_hwspinlock_relax,
पूर्ण;

अटल पूर्णांक sपंचांग32_hwspinlock_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sपंचांग32_hwspinlock *hw;
	व्योम __iomem *io_base;
	माप_प्रकार array_size;
	पूर्णांक i, ret;

	io_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(io_base))
		वापस PTR_ERR(io_base);

	array_size = STM32_MUTEX_NUM_LOCKS * माप(काष्ठा hwspinlock);
	hw = devm_kzalloc(&pdev->dev, माप(*hw) + array_size, GFP_KERNEL);
	अगर (!hw)
		वापस -ENOMEM;

	hw->clk = devm_clk_get(&pdev->dev, "hsem");
	अगर (IS_ERR(hw->clk))
		वापस PTR_ERR(hw->clk);

	क्रम (i = 0; i < STM32_MUTEX_NUM_LOCKS; i++)
		hw->bank.lock[i].priv = io_base + i * माप(u32);

	platक्रमm_set_drvdata(pdev, hw);
	pm_runसमय_enable(&pdev->dev);

	ret = hwspin_lock_रेजिस्टर(&hw->bank, &pdev->dev, &sपंचांग32_hwspinlock_ops,
				   0, STM32_MUTEX_NUM_LOCKS);

	अगर (ret)
		pm_runसमय_disable(&pdev->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32_hwspinlock_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sपंचांग32_hwspinlock *hw = platक्रमm_get_drvdata(pdev);
	पूर्णांक ret;

	ret = hwspin_lock_unरेजिस्टर(&hw->bank);
	अगर (ret)
		dev_err(&pdev->dev, "%s failed: %d\n", __func__, ret);

	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused sपंचांग32_hwspinlock_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा sपंचांग32_hwspinlock *hw = dev_get_drvdata(dev);

	clk_disable_unprepare(hw->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused sपंचांग32_hwspinlock_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा sपंचांग32_hwspinlock *hw = dev_get_drvdata(dev);

	clk_prepare_enable(hw->clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops sपंचांग32_hwspinlock_pm_ops = अणु
	SET_RUNTIME_PM_OPS(sपंचांग32_hwspinlock_runसमय_suspend,
			   sपंचांग32_hwspinlock_runसमय_resume,
			   शून्य)
पूर्ण;

अटल स्थिर काष्ठा of_device_id sपंचांग32_hwpinlock_ids[] = अणु
	अणु .compatible = "st,stm32-hwspinlock", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sपंचांग32_hwpinlock_ids);

अटल काष्ठा platक्रमm_driver sपंचांग32_hwspinlock_driver = अणु
	.probe		= sपंचांग32_hwspinlock_probe,
	.हटाओ		= sपंचांग32_hwspinlock_हटाओ,
	.driver		= अणु
		.name	= "stm32_hwspinlock",
		.of_match_table = sपंचांग32_hwpinlock_ids,
		.pm	= &sपंचांग32_hwspinlock_pm_ops,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init sपंचांग32_hwspinlock_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&sपंचांग32_hwspinlock_driver);
पूर्ण
/* board init code might need to reserve hwspinlocks क्रम predefined purposes */
postcore_initcall(sपंचांग32_hwspinlock_init);

अटल व्योम __निकास sपंचांग32_hwspinlock_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&sपंचांग32_hwspinlock_driver);
पूर्ण
module_निकास(sपंचांग32_hwspinlock_निकास);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Hardware spinlock driver for STM32 SoCs");
MODULE_AUTHOR("Benjamin Gaignard <benjamin.gaignard@st.com>");
