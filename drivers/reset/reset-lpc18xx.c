<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Reset driver क्रम NXP LPC18xx/43xx Reset Generation Unit (RGU).
 *
 * Copyright (C) 2015 Joachim Eastwood <manabian@gmail.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/init.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reboot.h>
#समावेश <linux/reset-controller.h>
#समावेश <linux/spinlock.h>

/* LPC18xx RGU रेजिस्टरs */
#घोषणा LPC18XX_RGU_CTRL0		0x100
#घोषणा LPC18XX_RGU_CTRL1		0x104
#घोषणा LPC18XX_RGU_ACTIVE_STATUS0	0x150
#घोषणा LPC18XX_RGU_ACTIVE_STATUS1	0x154

#घोषणा LPC18XX_RGU_RESETS_PER_REG	32

/* Internal reset outमाला_दो */
#घोषणा LPC18XX_RGU_CORE_RST	0
#घोषणा LPC43XX_RGU_M0SUB_RST	12
#घोषणा LPC43XX_RGU_M0APP_RST	56

काष्ठा lpc18xx_rgu_data अणु
	काष्ठा reset_controller_dev rcdev;
	काष्ठा notअगरier_block restart_nb;
	काष्ठा clk *clk_delay;
	काष्ठा clk *clk_reg;
	व्योम __iomem *base;
	spinlock_t lock;
	u32 delay_us;
पूर्ण;

#घोषणा to_rgu_data(p) container_of(p, काष्ठा lpc18xx_rgu_data, rcdev)

अटल पूर्णांक lpc18xx_rgu_restart(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ mode,
			       व्योम *cmd)
अणु
	काष्ठा lpc18xx_rgu_data *rc = container_of(nb, काष्ठा lpc18xx_rgu_data,
						   restart_nb);

	ग_लिखोl(BIT(LPC18XX_RGU_CORE_RST), rc->base + LPC18XX_RGU_CTRL0);
	mdelay(2000);

	pr_emerg("%s: unable to restart system\n", __func__);

	वापस NOTIFY_DONE;
पूर्ण

/*
 * The LPC18xx RGU has mostly self-deनिश्चितing resets except क्रम the
 * two reset lines going to the पूर्णांकernal Cortex-M0 cores.
 *
 * To prevent the M0 core resets from accidentally getting deनिश्चितed
 * status रेजिस्टर must be check and bits in control रेजिस्टर set to
 * preserve the state.
 */
अटल पूर्णांक lpc18xx_rgu_setclear_reset(काष्ठा reset_controller_dev *rcdev,
				      अचिन्हित दीर्घ id, bool set)
अणु
	काष्ठा lpc18xx_rgu_data *rc = to_rgu_data(rcdev);
	u32 stat_offset = LPC18XX_RGU_ACTIVE_STATUS0;
	u32 ctrl_offset = LPC18XX_RGU_CTRL0;
	अचिन्हित दीर्घ flags;
	u32 stat, rst_bit;

	stat_offset += (id / LPC18XX_RGU_RESETS_PER_REG) * माप(u32);
	ctrl_offset += (id / LPC18XX_RGU_RESETS_PER_REG) * माप(u32);
	rst_bit = 1 << (id % LPC18XX_RGU_RESETS_PER_REG);

	spin_lock_irqsave(&rc->lock, flags);
	stat = ~पढ़ोl(rc->base + stat_offset);
	अगर (set)
		ग_लिखोl(stat | rst_bit, rc->base + ctrl_offset);
	अन्यथा
		ग_लिखोl(stat & ~rst_bit, rc->base + ctrl_offset);
	spin_unlock_irqrestore(&rc->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक lpc18xx_rgu_निश्चित(काष्ठा reset_controller_dev *rcdev,
			      अचिन्हित दीर्घ id)
अणु
	वापस lpc18xx_rgu_setclear_reset(rcdev, id, true);
पूर्ण

अटल पूर्णांक lpc18xx_rgu_deनिश्चित(काष्ठा reset_controller_dev *rcdev,
				अचिन्हित दीर्घ id)
अणु
	वापस lpc18xx_rgu_setclear_reset(rcdev, id, false);
पूर्ण

/* Only M0 cores require explicit reset deनिश्चित */
अटल पूर्णांक lpc18xx_rgu_reset(काष्ठा reset_controller_dev *rcdev,
			     अचिन्हित दीर्घ id)
अणु
	काष्ठा lpc18xx_rgu_data *rc = to_rgu_data(rcdev);

	lpc18xx_rgu_निश्चित(rcdev, id);
	udelay(rc->delay_us);

	चयन (id) अणु
	हाल LPC43XX_RGU_M0SUB_RST:
	हाल LPC43XX_RGU_M0APP_RST:
		lpc18xx_rgu_setclear_reset(rcdev, id, false);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lpc18xx_rgu_status(काष्ठा reset_controller_dev *rcdev,
			      अचिन्हित दीर्घ id)
अणु
	काष्ठा lpc18xx_rgu_data *rc = to_rgu_data(rcdev);
	u32 bit, offset = LPC18XX_RGU_ACTIVE_STATUS0;

	offset += (id / LPC18XX_RGU_RESETS_PER_REG) * माप(u32);
	bit = 1 << (id % LPC18XX_RGU_RESETS_PER_REG);

	वापस !(पढ़ोl(rc->base + offset) & bit);
पूर्ण

अटल स्थिर काष्ठा reset_control_ops lpc18xx_rgu_ops = अणु
	.reset		= lpc18xx_rgu_reset,
	.निश्चित		= lpc18xx_rgu_निश्चित,
	.deनिश्चित	= lpc18xx_rgu_deनिश्चित,
	.status		= lpc18xx_rgu_status,
पूर्ण;

अटल पूर्णांक lpc18xx_rgu_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lpc18xx_rgu_data *rc;
	काष्ठा resource *res;
	u32 fcclk, firc;
	पूर्णांक ret;

	rc = devm_kzalloc(&pdev->dev, माप(*rc), GFP_KERNEL);
	अगर (!rc)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	rc->base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(rc->base))
		वापस PTR_ERR(rc->base);

	rc->clk_reg = devm_clk_get(&pdev->dev, "reg");
	अगर (IS_ERR(rc->clk_reg)) अणु
		dev_err(&pdev->dev, "reg clock not found\n");
		वापस PTR_ERR(rc->clk_reg);
	पूर्ण

	rc->clk_delay = devm_clk_get(&pdev->dev, "delay");
	अगर (IS_ERR(rc->clk_delay)) अणु
		dev_err(&pdev->dev, "delay clock not found\n");
		वापस PTR_ERR(rc->clk_delay);
	पूर्ण

	ret = clk_prepare_enable(rc->clk_reg);
	अगर (ret) अणु
		dev_err(&pdev->dev, "unable to enable reg clock\n");
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(rc->clk_delay);
	अगर (ret) अणु
		dev_err(&pdev->dev, "unable to enable delay clock\n");
		जाओ dis_clk_reg;
	पूर्ण

	fcclk = clk_get_rate(rc->clk_reg) / USEC_PER_SEC;
	firc = clk_get_rate(rc->clk_delay) / USEC_PER_SEC;
	अगर (fcclk == 0 || firc == 0)
		rc->delay_us = 2;
	अन्यथा
		rc->delay_us = DIV_ROUND_UP(fcclk, firc * firc);

	spin_lock_init(&rc->lock);

	rc->rcdev.owner = THIS_MODULE;
	rc->rcdev.nr_resets = 64;
	rc->rcdev.ops = &lpc18xx_rgu_ops;
	rc->rcdev.of_node = pdev->dev.of_node;

	platक्रमm_set_drvdata(pdev, rc);

	ret = reset_controller_रेजिस्टर(&rc->rcdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "unable to register device\n");
		जाओ dis_clks;
	पूर्ण

	rc->restart_nb.priority = 192,
	rc->restart_nb.notअगरier_call = lpc18xx_rgu_restart,
	ret = रेजिस्टर_restart_handler(&rc->restart_nb);
	अगर (ret)
		dev_warn(&pdev->dev, "failed to register restart handler\n");

	वापस 0;

dis_clks:
	clk_disable_unprepare(rc->clk_delay);
dis_clk_reg:
	clk_disable_unprepare(rc->clk_reg);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id lpc18xx_rgu_match[] = अणु
	अणु .compatible = "nxp,lpc1850-rgu" पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver lpc18xx_rgu_driver = अणु
	.probe	= lpc18xx_rgu_probe,
	.driver	= अणु
		.name			= "lpc18xx-reset",
		.of_match_table		= lpc18xx_rgu_match,
		.suppress_bind_attrs	= true,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(lpc18xx_rgu_driver);
