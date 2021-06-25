<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (C) 2012-2019 ARM Limited (or its affiliates). */

#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pm_runसमय.स>
#समावेश "cc_driver.h"
#समावेश "cc_buffer_mgr.h"
#समावेश "cc_request_mgr.h"
#समावेश "cc_sram_mgr.h"
#समावेश "cc_hash.h"
#समावेश "cc_pm.h"
#समावेश "cc_fips.h"

#घोषणा POWER_DOWN_ENABLE 0x01
#घोषणा POWER_DOWN_DISABLE 0x00

अटल पूर्णांक cc_pm_suspend(काष्ठा device *dev)
अणु
	काष्ठा cc_drvdata *drvdata = dev_get_drvdata(dev);

	dev_dbg(dev, "set HOST_POWER_DOWN_EN\n");
	fini_cc_regs(drvdata);
	cc_ioग_लिखो(drvdata, CC_REG(HOST_POWER_DOWN_EN), POWER_DOWN_ENABLE);
	clk_disable_unprepare(drvdata->clk);
	वापस 0;
पूर्ण

अटल पूर्णांक cc_pm_resume(काष्ठा device *dev)
अणु
	पूर्णांक rc;
	काष्ठा cc_drvdata *drvdata = dev_get_drvdata(dev);

	dev_dbg(dev, "unset HOST_POWER_DOWN_EN\n");
	/* Enables the device source clk */
	rc = clk_prepare_enable(drvdata->clk);
	अगर (rc) अणु
		dev_err(dev, "failed getting clock back on. We're toast.\n");
		वापस rc;
	पूर्ण
	/* रुको क्रम Cryptocell reset completion */
	अगर (!cc_रुको_क्रम_reset_completion(drvdata)) अणु
		dev_err(dev, "Cryptocell reset not completed");
		वापस -EBUSY;
	पूर्ण

	cc_ioग_लिखो(drvdata, CC_REG(HOST_POWER_DOWN_EN), POWER_DOWN_DISABLE);
	rc = init_cc_regs(drvdata);
	अगर (rc) अणु
		dev_err(dev, "init_cc_regs (%x)\n", rc);
		वापस rc;
	पूर्ण
	/* check अगर tee fips error occurred during घातer करोwn */
	cc_tee_handle_fips_error(drvdata);

	cc_init_hash_sram(drvdata);

	वापस 0;
पूर्ण

स्थिर काष्ठा dev_pm_ops ccree_pm = अणु
	SET_RUNTIME_PM_OPS(cc_pm_suspend, cc_pm_resume, शून्य)
पूर्ण;

पूर्णांक cc_pm_get(काष्ठा device *dev)
अणु
	पूर्णांक rc = pm_runसमय_get_sync(dev);
	अगर (rc < 0) अणु
		pm_runसमय_put_noidle(dev);
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

व्योम cc_pm_put_suspend(काष्ठा device *dev)
अणु
	pm_runसमय_mark_last_busy(dev);
	pm_runसमय_put_स्वतःsuspend(dev);
पूर्ण
