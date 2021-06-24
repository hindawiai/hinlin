<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ImgTec IR Decoder found in PowerDown Controller.
 *
 * Copyright 2010-2014 Imagination Technologies Ltd.
 *
 * This contains core img-ir code क्रम setting up the driver. The two पूर्णांकerfaces
 * (raw and hardware decode) are handled separately.
 */

#समावेश <linux/clk.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश "img-ir.h"

अटल irqवापस_t img_ir_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा img_ir_priv *priv = dev_id;
	u32 irq_status;

	spin_lock(&priv->lock);
	/* we have to clear irqs beक्रमe पढ़ोing */
	irq_status = img_ir_पढ़ो(priv, IMG_IR_IRQ_STATUS);
	img_ir_ग_लिखो(priv, IMG_IR_IRQ_CLEAR, irq_status);

	/* करोn't handle valid data irqs if we're only पूर्णांकerested in matches */
	irq_status &= img_ir_पढ़ो(priv, IMG_IR_IRQ_ENABLE);

	/* hand off edge पूर्णांकerrupts to raw decode handler */
	अगर (irq_status & IMG_IR_IRQ_EDGE && img_ir_raw_enabled(&priv->raw))
		img_ir_isr_raw(priv, irq_status);

	/* hand off hardware match पूर्णांकerrupts to hardware decode handler */
	अगर (irq_status & (IMG_IR_IRQ_DATA_MATCH |
			  IMG_IR_IRQ_DATA_VALID |
			  IMG_IR_IRQ_DATA2_VALID) &&
	    img_ir_hw_enabled(&priv->hw))
		img_ir_isr_hw(priv, irq_status);

	spin_unlock(&priv->lock);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम img_ir_setup(काष्ठा img_ir_priv *priv)
अणु
	/* start off with पूर्णांकerrupts disabled */
	img_ir_ग_लिखो(priv, IMG_IR_IRQ_ENABLE, 0);

	img_ir_setup_raw(priv);
	img_ir_setup_hw(priv);

	अगर (!IS_ERR(priv->clk))
		clk_prepare_enable(priv->clk);
पूर्ण

अटल व्योम img_ir_ident(काष्ठा img_ir_priv *priv)
अणु
	u32 core_rev = img_ir_पढ़ो(priv, IMG_IR_CORE_REV);

	dev_info(priv->dev,
		 "IMG IR Decoder (%d.%d.%d.%d) probed successfully\n",
		 (core_rev & IMG_IR_DESIGNER) >> IMG_IR_DESIGNER_SHIFT,
		 (core_rev & IMG_IR_MAJOR_REV) >> IMG_IR_MAJOR_REV_SHIFT,
		 (core_rev & IMG_IR_MINOR_REV) >> IMG_IR_MINOR_REV_SHIFT,
		 (core_rev & IMG_IR_MAINT_REV) >> IMG_IR_MAINT_REV_SHIFT);
	dev_info(priv->dev, "Modes:%s%s\n",
		 img_ir_hw_enabled(&priv->hw) ? " hardware" : "",
		 img_ir_raw_enabled(&priv->raw) ? " raw" : "");
पूर्ण

अटल पूर्णांक img_ir_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा img_ir_priv *priv;
	काष्ठा resource *res_regs;
	पूर्णांक irq, error, error2;

	/* Get resources from platक्रमm device */
	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	/* Private driver data */
	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, priv);
	priv->dev = &pdev->dev;
	spin_lock_init(&priv->lock);

	/* Ioremap the रेजिस्टरs */
	res_regs = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->reg_base = devm_ioremap_resource(&pdev->dev, res_regs);
	अगर (IS_ERR(priv->reg_base))
		वापस PTR_ERR(priv->reg_base);

	/* Get core घड़ी */
	priv->clk = devm_clk_get(&pdev->dev, "core");
	अगर (IS_ERR(priv->clk))
		dev_warn(&pdev->dev, "cannot get core clock resource\n");

	/* Get sys घड़ी */
	priv->sys_clk = devm_clk_get(&pdev->dev, "sys");
	अगर (IS_ERR(priv->sys_clk))
		dev_warn(&pdev->dev, "cannot get sys clock resource\n");
	/*
	 * Enabling the प्रणाली घड़ी beक्रमe the रेजिस्टर पूर्णांकerface is
	 * accessed. ISR shouldn't get called with Sys Clock disabled,
	 * hence निकासing probe with an error.
	 */
	अगर (!IS_ERR(priv->sys_clk)) अणु
		error = clk_prepare_enable(priv->sys_clk);
		अगर (error) अणु
			dev_err(&pdev->dev, "cannot enable sys clock\n");
			वापस error;
		पूर्ण
	पूर्ण

	/* Set up raw & hw decoder */
	error = img_ir_probe_raw(priv);
	error2 = img_ir_probe_hw(priv);
	अगर (error && error2) अणु
		अगर (error == -ENODEV)
			error = error2;
		जाओ err_probe;
	पूर्ण

	/* Get the IRQ */
	priv->irq = irq;
	error = request_irq(priv->irq, img_ir_isr, 0, "img-ir", priv);
	अगर (error) अणु
		dev_err(&pdev->dev, "cannot register IRQ %u\n",
			priv->irq);
		error = -EIO;
		जाओ err_irq;
	पूर्ण

	img_ir_ident(priv);
	img_ir_setup(priv);

	वापस 0;

err_irq:
	img_ir_हटाओ_hw(priv);
	img_ir_हटाओ_raw(priv);
err_probe:
	अगर (!IS_ERR(priv->sys_clk))
		clk_disable_unprepare(priv->sys_clk);
	वापस error;
पूर्ण

अटल पूर्णांक img_ir_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा img_ir_priv *priv = platक्रमm_get_drvdata(pdev);

	मुक्त_irq(priv->irq, priv);
	img_ir_हटाओ_hw(priv);
	img_ir_हटाओ_raw(priv);

	अगर (!IS_ERR(priv->clk))
		clk_disable_unprepare(priv->clk);
	अगर (!IS_ERR(priv->sys_clk))
		clk_disable_unprepare(priv->sys_clk);
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(img_ir_pmops, img_ir_suspend, img_ir_resume);

अटल स्थिर काष्ठा of_device_id img_ir_match[] = अणु
	अणु .compatible = "img,ir-rev1" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, img_ir_match);

अटल काष्ठा platक्रमm_driver img_ir_driver = अणु
	.driver = अणु
		.name = "img-ir",
		.of_match_table	= img_ir_match,
		.pm = &img_ir_pmops,
	पूर्ण,
	.probe = img_ir_probe,
	.हटाओ = img_ir_हटाओ,
पूर्ण;

module_platक्रमm_driver(img_ir_driver);

MODULE_AUTHOR("Imagination Technologies Ltd.");
MODULE_DESCRIPTION("ImgTec IR");
MODULE_LICENSE("GPL");
