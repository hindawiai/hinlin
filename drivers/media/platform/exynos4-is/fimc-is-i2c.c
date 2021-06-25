<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Samsung EXYNOS4x12 FIMC-IS (Imaging Subप्रणाली) driver
 *
 * Copyright (C) 2013 Samsung Electronics Co., Ltd.
 *
 * Author: Sylwester Nawrocki <s.nawrocki@samsung.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>
#समावेश "fimc-is-i2c.h"

काष्ठा fimc_is_i2c अणु
	काष्ठा i2c_adapter adapter;
	काष्ठा clk *घड़ी;
पूर्ण;

/*
 * An empty algorithm is used as the actual I2C bus controller driver
 * is implemented in the FIMC-IS subप्रणाली firmware and the host CPU
 * करोesn't access the I2C bus controller.
 */
अटल u32 is_i2c_func(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm fimc_is_i2c_algorithm = अणु
	.functionality	= is_i2c_func,
पूर्ण;

अटल पूर्णांक fimc_is_i2c_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा fimc_is_i2c *isp_i2c;
	काष्ठा i2c_adapter *i2c_adap;
	पूर्णांक ret;

	isp_i2c = devm_kzalloc(&pdev->dev, माप(*isp_i2c), GFP_KERNEL);
	अगर (!isp_i2c)
		वापस -ENOMEM;

	isp_i2c->घड़ी = devm_clk_get(&pdev->dev, "i2c_isp");
	अगर (IS_ERR(isp_i2c->घड़ी)) अणु
		dev_err(&pdev->dev, "failed to get the clock\n");
		वापस PTR_ERR(isp_i2c->घड़ी);
	पूर्ण

	i2c_adap = &isp_i2c->adapter;
	i2c_adap->dev.of_node = node;
	i2c_adap->dev.parent = &pdev->dev;
	strscpy(i2c_adap->name, "exynos4x12-isp-i2c", माप(i2c_adap->name));
	i2c_adap->owner = THIS_MODULE;
	i2c_adap->algo = &fimc_is_i2c_algorithm;
	i2c_adap->class = I2C_CLASS_SPD;

	platक्रमm_set_drvdata(pdev, isp_i2c);
	pm_runसमय_enable(&pdev->dev);

	ret = i2c_add_adapter(i2c_adap);
	अगर (ret < 0)
		जाओ err_pm_dis;
	/*
	 * Client drivers of this adapter करोn't करो any I2C transfers as that
	 * is handled by the ISP firmware.  But we rely on the runसमय PM
	 * state propagation from the clients up to the adapter driver so
	 * clear the ignore_children flags here.  PM rutnime calls are not
	 * used in probe() handler of clients of this adapter so there is
	 * no issues with clearing the flag right after रेजिस्टरing the I2C
	 * adapter.
	 */
	pm_suspend_ignore_children(&i2c_adap->dev, false);
	वापस 0;

err_pm_dis:
	pm_runसमय_disable(&pdev->dev);
	वापस ret;
पूर्ण

अटल पूर्णांक fimc_is_i2c_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fimc_is_i2c *isp_i2c = platक्रमm_get_drvdata(pdev);

	pm_runसमय_disable(&pdev->dev);
	i2c_del_adapter(&isp_i2c->adapter);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक fimc_is_i2c_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा fimc_is_i2c *isp_i2c = dev_get_drvdata(dev);

	clk_disable_unprepare(isp_i2c->घड़ी);
	वापस 0;
पूर्ण

अटल पूर्णांक fimc_is_i2c_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा fimc_is_i2c *isp_i2c = dev_get_drvdata(dev);

	वापस clk_prepare_enable(isp_i2c->घड़ी);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक fimc_is_i2c_suspend(काष्ठा device *dev)
अणु
	अगर (pm_runसमय_suspended(dev))
		वापस 0;

	वापस fimc_is_i2c_runसमय_suspend(dev);
पूर्ण

अटल पूर्णांक fimc_is_i2c_resume(काष्ठा device *dev)
अणु
	अगर (pm_runसमय_suspended(dev))
		वापस 0;

	वापस fimc_is_i2c_runसमय_resume(dev);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops fimc_is_i2c_pm_ops = अणु
	SET_RUNTIME_PM_OPS(fimc_is_i2c_runसमय_suspend,
					fimc_is_i2c_runसमय_resume, शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(fimc_is_i2c_suspend, fimc_is_i2c_resume)
पूर्ण;

अटल स्थिर काष्ठा of_device_id fimc_is_i2c_of_match[] = अणु
	अणु .compatible = FIMC_IS_I2C_COMPATIBLE पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver fimc_is_i2c_driver = अणु
	.probe		= fimc_is_i2c_probe,
	.हटाओ		= fimc_is_i2c_हटाओ,
	.driver = अणु
		.of_match_table = fimc_is_i2c_of_match,
		.name		= "fimc-isp-i2c",
		.pm		= &fimc_is_i2c_pm_ops,
	पूर्ण
पूर्ण;

पूर्णांक fimc_is_रेजिस्टर_i2c_driver(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&fimc_is_i2c_driver);
पूर्ण

व्योम fimc_is_unरेजिस्टर_i2c_driver(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&fimc_is_i2c_driver);
पूर्ण
