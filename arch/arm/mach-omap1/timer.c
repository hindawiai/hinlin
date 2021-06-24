<शैली गुरु>
/*
 * OMAP1 Dual-Mode Timers - platक्रमm device registration
 *
 * Contains first level initialization routines which पूर्णांकernally
 * generates समयr device inक्रमmation and रेजिस्टरs with linux
 * device model. It also has a low level function to change the समयr
 * input घड़ी source.
 *
 * Copyright (C) 2011 Texas Instruments Incorporated - https://www.ti.com/
 * Tarun Kanti DebBarma <tarun.kanti@ti.com>
 * Thara Gopinath <thara@ti.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/platक्रमm_data/dmसमयr-omap.h>

#समावेश <घड़ीsource/समयr-ti-dm.h>

#समावेश "soc.h"

#घोषणा OMAP1610_GPTIMER1_BASE		0xfffb1400
#घोषणा OMAP1610_GPTIMER2_BASE		0xfffb1c00
#घोषणा OMAP1610_GPTIMER3_BASE		0xfffb2400
#घोषणा OMAP1610_GPTIMER4_BASE		0xfffb2c00
#घोषणा OMAP1610_GPTIMER5_BASE		0xfffb3400
#घोषणा OMAP1610_GPTIMER6_BASE		0xfffb3c00
#घोषणा OMAP1610_GPTIMER7_BASE		0xfffb7400
#घोषणा OMAP1610_GPTIMER8_BASE		0xfffbd400

#घोषणा OMAP1_DM_TIMER_COUNT		8

अटल पूर्णांक omap1_dm_समयr_set_src(काष्ठा platक्रमm_device *pdev,
				पूर्णांक source)
अणु
	पूर्णांक n = (pdev->id - 1) << 1;
	u32 l;

	l = omap_पढ़ोl(MOD_CONF_CTRL_1) & ~(0x03 << n);
	l |= source << n;
	omap_ग_लिखोl(l, MOD_CONF_CTRL_1);

	वापस 0;
पूर्ण

अटल पूर्णांक __init omap1_dm_समयr_init(व्योम)
अणु
	पूर्णांक i;
	पूर्णांक ret;
	काष्ठा dmसमयr_platक्रमm_data *pdata;
	काष्ठा platक्रमm_device *pdev;

	अगर (!cpu_is_omap16xx())
		वापस 0;

	क्रम (i = 1; i <= OMAP1_DM_TIMER_COUNT; i++) अणु
		काष्ठा resource res[2];
		u32 base, irq;

		चयन (i) अणु
		हाल 1:
			base = OMAP1610_GPTIMER1_BASE;
			irq = INT_1610_GPTIMER1;
			अवरोध;
		हाल 2:
			base = OMAP1610_GPTIMER2_BASE;
			irq = INT_1610_GPTIMER2;
			अवरोध;
		हाल 3:
			base = OMAP1610_GPTIMER3_BASE;
			irq = INT_1610_GPTIMER3;
			अवरोध;
		हाल 4:
			base = OMAP1610_GPTIMER4_BASE;
			irq = INT_1610_GPTIMER4;
			अवरोध;
		हाल 5:
			base = OMAP1610_GPTIMER5_BASE;
			irq = INT_1610_GPTIMER5;
			अवरोध;
		हाल 6:
			base = OMAP1610_GPTIMER6_BASE;
			irq = INT_1610_GPTIMER6;
			अवरोध;
		हाल 7:
			base = OMAP1610_GPTIMER7_BASE;
			irq = INT_1610_GPTIMER7;
			अवरोध;
		हाल 8:
			base = OMAP1610_GPTIMER8_BASE;
			irq = INT_1610_GPTIMER8;
			अवरोध;
		शेष:
			/*
			 * not supposed to reach here.
			 * this is to हटाओ warning.
			 */
			वापस -EINVAL;
		पूर्ण

		pdev = platक्रमm_device_alloc("omap_timer", i);
		अगर (!pdev) अणु
			pr_err("%s: Failed to device alloc for dmtimer%d\n",
				__func__, i);
			वापस -ENOMEM;
		पूर्ण

		स_रखो(res, 0, 2 * माप(काष्ठा resource));
		res[0].start = base;
		res[0].end = base + 0x46;
		res[0].flags = IORESOURCE_MEM;
		res[1].start = irq;
		res[1].end = irq;
		res[1].flags = IORESOURCE_IRQ;
		ret = platक्रमm_device_add_resources(pdev, res,
				ARRAY_SIZE(res));
		अगर (ret) अणु
			dev_err(&pdev->dev, "%s: Failed to add resources.\n",
				__func__);
			जाओ err_मुक्त_pdev;
		पूर्ण

		pdata = kzalloc(माप(*pdata), GFP_KERNEL);
		अगर (!pdata) अणु
			ret = -ENOMEM;
			जाओ err_मुक्त_pdata;
		पूर्ण

		pdata->set_समयr_src = omap1_dm_समयr_set_src;
		pdata->समयr_capability = OMAP_TIMER_ALWON |
				OMAP_TIMER_NEEDS_RESET | OMAP_TIMER_HAS_DSP_IRQ;

		ret = platक्रमm_device_add_data(pdev, pdata, माप(*pdata));
		अगर (ret) अणु
			dev_err(&pdev->dev, "%s: Failed to add platform data.\n",
				__func__);
			जाओ err_मुक्त_pdata;
		पूर्ण

		ret = platक्रमm_device_add(pdev);
		अगर (ret) अणु
			dev_err(&pdev->dev, "%s: Failed to add platform device.\n",
				__func__);
			जाओ err_मुक्त_pdata;
		पूर्ण

		dev_dbg(&pdev->dev, " Registered.\n");
	पूर्ण

	वापस 0;

err_मुक्त_pdata:
	kमुक्त(pdata);

err_मुक्त_pdev:
	platक्रमm_device_unरेजिस्टर(pdev);

	वापस ret;
पूर्ण
arch_initcall(omap1_dm_समयr_init);
