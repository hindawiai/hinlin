<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * RNG driver क्रम Freescale RNGC
 *
 * Copyright (C) 2008-2012 Freescale Semiconductor, Inc.
 * Copyright (C) 2017 Martin Kaiser <martin@kaiser.cx>
 */

#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/hw_अक्रमom.h>
#समावेश <linux/completion.h>
#समावेश <linux/पन.स>

#घोषणा RNGC_VER_ID			0x0000
#घोषणा RNGC_COMMAND			0x0004
#घोषणा RNGC_CONTROL			0x0008
#घोषणा RNGC_STATUS			0x000C
#घोषणा RNGC_ERROR			0x0010
#घोषणा RNGC_FIFO			0x0014

/* the fields in the ver id रेजिस्टर */
#घोषणा RNGC_TYPE_SHIFT		28
#घोषणा RNGC_VER_MAJ_SHIFT		8

/* the rng_type field */
#घोषणा RNGC_TYPE_RNGB			0x1
#घोषणा RNGC_TYPE_RNGC			0x2


#घोषणा RNGC_CMD_CLR_ERR		0x00000020
#घोषणा RNGC_CMD_CLR_INT		0x00000010
#घोषणा RNGC_CMD_SEED			0x00000002
#घोषणा RNGC_CMD_SELF_TEST		0x00000001

#घोषणा RNGC_CTRL_MASK_ERROR		0x00000040
#घोषणा RNGC_CTRL_MASK_DONE		0x00000020
#घोषणा RNGC_CTRL_AUTO_SEED		0x00000010

#घोषणा RNGC_STATUS_ERROR		0x00010000
#घोषणा RNGC_STATUS_FIFO_LEVEL_MASK	0x00000f00
#घोषणा RNGC_STATUS_FIFO_LEVEL_SHIFT	8
#घोषणा RNGC_STATUS_SEED_DONE		0x00000020
#घोषणा RNGC_STATUS_ST_DONE		0x00000010

#घोषणा RNGC_ERROR_STATUS_STAT_ERR	0x00000008

#घोषणा RNGC_TIMEOUT  3000 /* 3 sec */


अटल bool self_test = true;
module_param(self_test, bool, 0);

काष्ठा imx_rngc अणु
	काष्ठा device		*dev;
	काष्ठा clk		*clk;
	व्योम __iomem		*base;
	काष्ठा hwrng		rng;
	काष्ठा completion	rng_op_करोne;
	/*
	 * err_reg is written only by the irq handler and पढ़ो only
	 * when पूर्णांकerrupts are masked, we need no spinlock
	 */
	u32			err_reg;
पूर्ण;


अटल अंतरभूत व्योम imx_rngc_irq_mask_clear(काष्ठा imx_rngc *rngc)
अणु
	u32 ctrl, cmd;

	/* mask पूर्णांकerrupts */
	ctrl = पढ़ोl(rngc->base + RNGC_CONTROL);
	ctrl |= RNGC_CTRL_MASK_DONE | RNGC_CTRL_MASK_ERROR;
	ग_लिखोl(ctrl, rngc->base + RNGC_CONTROL);

	/*
	 * CLR_INT clears the पूर्णांकerrupt only अगर there's no error
	 * CLR_ERR clear the पूर्णांकerrupt and the error रेजिस्टर अगर there
	 * is an error
	 */
	cmd = पढ़ोl(rngc->base + RNGC_COMMAND);
	cmd |= RNGC_CMD_CLR_INT | RNGC_CMD_CLR_ERR;
	ग_लिखोl(cmd, rngc->base + RNGC_COMMAND);
पूर्ण

अटल अंतरभूत व्योम imx_rngc_irq_unmask(काष्ठा imx_rngc *rngc)
अणु
	u32 ctrl;

	ctrl = पढ़ोl(rngc->base + RNGC_CONTROL);
	ctrl &= ~(RNGC_CTRL_MASK_DONE | RNGC_CTRL_MASK_ERROR);
	ग_लिखोl(ctrl, rngc->base + RNGC_CONTROL);
पूर्ण

अटल पूर्णांक imx_rngc_self_test(काष्ठा imx_rngc *rngc)
अणु
	u32 cmd;
	पूर्णांक ret;

	imx_rngc_irq_unmask(rngc);

	/* run self test */
	cmd = पढ़ोl(rngc->base + RNGC_COMMAND);
	ग_लिखोl(cmd | RNGC_CMD_SELF_TEST, rngc->base + RNGC_COMMAND);

	ret = रुको_क्रम_completion_समयout(&rngc->rng_op_करोne, RNGC_TIMEOUT);
	imx_rngc_irq_mask_clear(rngc);
	अगर (!ret)
		वापस -ETIMEDOUT;

	वापस rngc->err_reg ? -EIO : 0;
पूर्ण

अटल पूर्णांक imx_rngc_पढ़ो(काष्ठा hwrng *rng, व्योम *data, माप_प्रकार max, bool रुको)
अणु
	काष्ठा imx_rngc *rngc = container_of(rng, काष्ठा imx_rngc, rng);
	अचिन्हित पूर्णांक status;
	अचिन्हित पूर्णांक level;
	पूर्णांक retval = 0;

	जबतक (max >= माप(u32)) अणु
		status = पढ़ोl(rngc->base + RNGC_STATUS);

		/* is there some error जबतक पढ़ोing this अक्रमom number? */
		अगर (status & RNGC_STATUS_ERROR)
			अवरोध;

		/* how many अक्रमom numbers are in FIFO? [0-16] */
		level = (status & RNGC_STATUS_FIFO_LEVEL_MASK) >>
			RNGC_STATUS_FIFO_LEVEL_SHIFT;

		अगर (level) अणु
			/* retrieve a अक्रमom number from FIFO */
			*(u32 *)data = पढ़ोl(rngc->base + RNGC_FIFO);

			retval += माप(u32);
			data += माप(u32);
			max -= माप(u32);
		पूर्ण
	पूर्ण

	वापस retval ? retval : -EIO;
पूर्ण

अटल irqवापस_t imx_rngc_irq(पूर्णांक irq, व्योम *priv)
अणु
	काष्ठा imx_rngc *rngc = (काष्ठा imx_rngc *)priv;
	u32 status;

	/*
	 * clearing the पूर्णांकerrupt will also clear the error रेजिस्टर
	 * पढ़ो error and status beक्रमe clearing
	 */
	status = पढ़ोl(rngc->base + RNGC_STATUS);
	rngc->err_reg = पढ़ोl(rngc->base + RNGC_ERROR);

	imx_rngc_irq_mask_clear(rngc);

	अगर (status & (RNGC_STATUS_SEED_DONE | RNGC_STATUS_ST_DONE))
		complete(&rngc->rng_op_करोne);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक imx_rngc_init(काष्ठा hwrng *rng)
अणु
	काष्ठा imx_rngc *rngc = container_of(rng, काष्ठा imx_rngc, rng);
	u32 cmd, ctrl;
	पूर्णांक ret;

	/* clear error */
	cmd = पढ़ोl(rngc->base + RNGC_COMMAND);
	ग_लिखोl(cmd | RNGC_CMD_CLR_ERR, rngc->base + RNGC_COMMAND);

	imx_rngc_irq_unmask(rngc);

	/* create seed, repeat जबतक there is some statistical error */
	करो अणु
		/* seed creation */
		cmd = पढ़ोl(rngc->base + RNGC_COMMAND);
		ग_लिखोl(cmd | RNGC_CMD_SEED, rngc->base + RNGC_COMMAND);

		ret = रुको_क्रम_completion_समयout(&rngc->rng_op_करोne,
				RNGC_TIMEOUT);

		अगर (!ret) अणु
			ret = -ETIMEDOUT;
			जाओ err;
		पूर्ण

	पूर्ण जबतक (rngc->err_reg == RNGC_ERROR_STATUS_STAT_ERR);

	अगर (rngc->err_reg) अणु
		ret = -EIO;
		जाओ err;
	पूर्ण

	/*
	 * enable स्वतःmatic seeding, the rngc creates a new seed स्वतःmatically
	 * after serving 2^20 अक्रमom 160-bit words
	 */
	ctrl = पढ़ोl(rngc->base + RNGC_CONTROL);
	ctrl |= RNGC_CTRL_AUTO_SEED;
	ग_लिखोl(ctrl, rngc->base + RNGC_CONTROL);

	/*
	 * अगर initialisation was successful, we keep the पूर्णांकerrupt
	 * unmasked until imx_rngc_cleanup is called
	 * we mask the पूर्णांकerrupt ourselves अगर we वापस an error
	 */
	वापस 0;

err:
	imx_rngc_irq_mask_clear(rngc);
	वापस ret;
पूर्ण

अटल व्योम imx_rngc_cleanup(काष्ठा hwrng *rng)
अणु
	काष्ठा imx_rngc *rngc = container_of(rng, काष्ठा imx_rngc, rng);

	imx_rngc_irq_mask_clear(rngc);
पूर्ण

अटल पूर्णांक imx_rngc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा imx_rngc *rngc;
	पूर्णांक ret;
	पूर्णांक irq;
	u32 ver_id;
	u8  rng_type;

	rngc = devm_kzalloc(&pdev->dev, माप(*rngc), GFP_KERNEL);
	अगर (!rngc)
		वापस -ENOMEM;

	rngc->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(rngc->base))
		वापस PTR_ERR(rngc->base);

	rngc->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(rngc->clk)) अणु
		dev_err(&pdev->dev, "Can not get rng_clk\n");
		वापस PTR_ERR(rngc->clk);
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	ret = clk_prepare_enable(rngc->clk);
	अगर (ret)
		वापस ret;

	ver_id = पढ़ोl(rngc->base + RNGC_VER_ID);
	rng_type = ver_id >> RNGC_TYPE_SHIFT;
	/*
	 * This driver supports only RNGC and RNGB. (There's a dअगरferent
	 * driver क्रम RNGA.)
	 */
	अगर (rng_type != RNGC_TYPE_RNGC && rng_type != RNGC_TYPE_RNGB) अणु
		ret = -ENODEV;
		जाओ err;
	पूर्ण

	ret = devm_request_irq(&pdev->dev,
			irq, imx_rngc_irq, 0, pdev->name, (व्योम *)rngc);
	अगर (ret) अणु
		dev_err(rngc->dev, "Can't get interrupt working.\n");
		जाओ err;
	पूर्ण

	init_completion(&rngc->rng_op_करोne);

	rngc->rng.name = pdev->name;
	rngc->rng.init = imx_rngc_init;
	rngc->rng.पढ़ो = imx_rngc_पढ़ो;
	rngc->rng.cleanup = imx_rngc_cleanup;
	rngc->rng.quality = 19;

	rngc->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, rngc);

	imx_rngc_irq_mask_clear(rngc);

	अगर (self_test) अणु
		ret = imx_rngc_self_test(rngc);
		अगर (ret) अणु
			dev_err(rngc->dev, "self test failed\n");
			जाओ err;
		पूर्ण
	पूर्ण

	ret = hwrng_रेजिस्टर(&rngc->rng);
	अगर (ret) अणु
		dev_err(&pdev->dev, "hwrng registration failed\n");
		जाओ err;
	पूर्ण

	dev_info(&pdev->dev,
		"Freescale RNG%c registered (HW revision %d.%02d)\n",
		rng_type == RNGC_TYPE_RNGB ? 'B' : 'C',
		(ver_id >> RNGC_VER_MAJ_SHIFT) & 0xff, ver_id & 0xff);
	वापस 0;

err:
	clk_disable_unprepare(rngc->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक __निकास imx_rngc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा imx_rngc *rngc = platक्रमm_get_drvdata(pdev);

	hwrng_unरेजिस्टर(&rngc->rng);

	clk_disable_unprepare(rngc->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused imx_rngc_suspend(काष्ठा device *dev)
अणु
	काष्ठा imx_rngc *rngc = dev_get_drvdata(dev);

	clk_disable_unprepare(rngc->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused imx_rngc_resume(काष्ठा device *dev)
अणु
	काष्ठा imx_rngc *rngc = dev_get_drvdata(dev);

	clk_prepare_enable(rngc->clk);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(imx_rngc_pm_ops, imx_rngc_suspend, imx_rngc_resume);

अटल स्थिर काष्ठा of_device_id imx_rngc_dt_ids[] = अणु
	अणु .compatible = "fsl,imx25-rngb", .data = शून्य, पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, imx_rngc_dt_ids);

अटल काष्ठा platक्रमm_driver imx_rngc_driver = अणु
	.driver = अणु
		.name = "imx_rngc",
		.pm = &imx_rngc_pm_ops,
		.of_match_table = imx_rngc_dt_ids,
	पूर्ण,
	.हटाओ = __निकास_p(imx_rngc_हटाओ),
पूर्ण;

module_platक्रमm_driver_probe(imx_rngc_driver, imx_rngc_probe);

MODULE_AUTHOR("Freescale Semiconductor, Inc.");
MODULE_DESCRIPTION("H/W RNGC driver for i.MX");
MODULE_LICENSE("GPL");
