<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * RNG driver क्रम Freescale RNGA
 *
 * Copyright 2008-2009 Freescale Semiconductor, Inc. All Rights Reserved.
 * Author: Alan Carvalho de Assis <acassis@gmail.com>
 */

/*
 *
 * This driver is based on other RNG drivers.
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/hw_अक्रमom.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>

/* RNGA Registers */
#घोषणा RNGA_CONTROL			0x00
#घोषणा RNGA_STATUS			0x04
#घोषणा RNGA_ENTROPY			0x08
#घोषणा RNGA_OUTPUT_FIFO		0x0c
#घोषणा RNGA_MODE			0x10
#घोषणा RNGA_VERIFICATION_CONTROL	0x14
#घोषणा RNGA_OSC_CONTROL_COUNTER	0x18
#घोषणा RNGA_OSC1_COUNTER		0x1c
#घोषणा RNGA_OSC2_COUNTER		0x20
#घोषणा RNGA_OSC_COUNTER_STATUS		0x24

/* RNGA Registers Range */
#घोषणा RNG_ADDR_RANGE			0x28

/* RNGA Control Register */
#घोषणा RNGA_CONTROL_SLEEP		0x00000010
#घोषणा RNGA_CONTROL_CLEAR_INT		0x00000008
#घोषणा RNGA_CONTROL_MASK_INTS		0x00000004
#घोषणा RNGA_CONTROL_HIGH_ASSURANCE	0x00000002
#घोषणा RNGA_CONTROL_GO			0x00000001

#घोषणा RNGA_STATUS_LEVEL_MASK		0x0000ff00

/* RNGA Status Register */
#घोषणा RNGA_STATUS_OSC_DEAD		0x80000000
#घोषणा RNGA_STATUS_SLEEP		0x00000010
#घोषणा RNGA_STATUS_ERROR_INT		0x00000008
#घोषणा RNGA_STATUS_FIFO_UNDERFLOW	0x00000004
#घोषणा RNGA_STATUS_LAST_READ_STATUS	0x00000002
#घोषणा RNGA_STATUS_SECURITY_VIOLATION	0x00000001

काष्ठा mxc_rng अणु
	काष्ठा device *dev;
	काष्ठा hwrng rng;
	व्योम __iomem *mem;
	काष्ठा clk *clk;
पूर्ण;

अटल पूर्णांक mxc_rnga_data_present(काष्ठा hwrng *rng, पूर्णांक रुको)
अणु
	पूर्णांक i;
	काष्ठा mxc_rng *mxc_rng = container_of(rng, काष्ठा mxc_rng, rng);

	क्रम (i = 0; i < 20; i++) अणु
		/* how many अक्रमom numbers are in FIFO? [0-16] */
		पूर्णांक level = (__raw_पढ़ोl(mxc_rng->mem + RNGA_STATUS) &
				RNGA_STATUS_LEVEL_MASK) >> 8;
		अगर (level || !रुको)
			वापस !!level;
		udelay(10);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mxc_rnga_data_पढ़ो(काष्ठा hwrng *rng, u32 * data)
अणु
	पूर्णांक err;
	u32 ctrl;
	काष्ठा mxc_rng *mxc_rng = container_of(rng, काष्ठा mxc_rng, rng);

	/* retrieve a अक्रमom number from FIFO */
	*data = __raw_पढ़ोl(mxc_rng->mem + RNGA_OUTPUT_FIFO);

	/* some error जबतक पढ़ोing this अक्रमom number? */
	err = __raw_पढ़ोl(mxc_rng->mem + RNGA_STATUS) & RNGA_STATUS_ERROR_INT;

	/* अगर error: clear error पूर्णांकerrupt, but करोesn't वापस अक्रमom number */
	अगर (err) अणु
		dev_dbg(mxc_rng->dev, "Error while reading random number!\n");
		ctrl = __raw_पढ़ोl(mxc_rng->mem + RNGA_CONTROL);
		__raw_ग_लिखोl(ctrl | RNGA_CONTROL_CLEAR_INT,
					mxc_rng->mem + RNGA_CONTROL);
		वापस 0;
	पूर्ण अन्यथा
		वापस 4;
पूर्ण

अटल पूर्णांक mxc_rnga_init(काष्ठा hwrng *rng)
अणु
	u32 ctrl, osc;
	काष्ठा mxc_rng *mxc_rng = container_of(rng, काष्ठा mxc_rng, rng);

	/* wake up */
	ctrl = __raw_पढ़ोl(mxc_rng->mem + RNGA_CONTROL);
	__raw_ग_लिखोl(ctrl & ~RNGA_CONTROL_SLEEP, mxc_rng->mem + RNGA_CONTROL);

	/* verअगरy अगर oscillator is working */
	osc = __raw_पढ़ोl(mxc_rng->mem + RNGA_STATUS);
	अगर (osc & RNGA_STATUS_OSC_DEAD) अणु
		dev_err(mxc_rng->dev, "RNGA Oscillator is dead!\n");
		वापस -ENODEV;
	पूर्ण

	/* go running */
	ctrl = __raw_पढ़ोl(mxc_rng->mem + RNGA_CONTROL);
	__raw_ग_लिखोl(ctrl | RNGA_CONTROL_GO, mxc_rng->mem + RNGA_CONTROL);

	वापस 0;
पूर्ण

अटल व्योम mxc_rnga_cleanup(काष्ठा hwrng *rng)
अणु
	u32 ctrl;
	काष्ठा mxc_rng *mxc_rng = container_of(rng, काष्ठा mxc_rng, rng);

	ctrl = __raw_पढ़ोl(mxc_rng->mem + RNGA_CONTROL);

	/* stop rnga */
	__raw_ग_लिखोl(ctrl & ~RNGA_CONTROL_GO, mxc_rng->mem + RNGA_CONTROL);
पूर्ण

अटल पूर्णांक __init mxc_rnga_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक err;
	काष्ठा mxc_rng *mxc_rng;

	mxc_rng = devm_kzalloc(&pdev->dev, माप(*mxc_rng), GFP_KERNEL);
	अगर (!mxc_rng)
		वापस -ENOMEM;

	mxc_rng->dev = &pdev->dev;
	mxc_rng->rng.name = "mxc-rnga";
	mxc_rng->rng.init = mxc_rnga_init;
	mxc_rng->rng.cleanup = mxc_rnga_cleanup;
	mxc_rng->rng.data_present = mxc_rnga_data_present;
	mxc_rng->rng.data_पढ़ो = mxc_rnga_data_पढ़ो;

	mxc_rng->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(mxc_rng->clk)) अणु
		dev_err(&pdev->dev, "Could not get rng_clk!\n");
		वापस PTR_ERR(mxc_rng->clk);
	पूर्ण

	err = clk_prepare_enable(mxc_rng->clk);
	अगर (err)
		वापस err;

	mxc_rng->mem = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(mxc_rng->mem)) अणु
		err = PTR_ERR(mxc_rng->mem);
		जाओ err_ioremap;
	पूर्ण

	err = hwrng_रेजिस्टर(&mxc_rng->rng);
	अगर (err) अणु
		dev_err(&pdev->dev, "MXC RNGA registering failed (%d)\n", err);
		जाओ err_ioremap;
	पूर्ण

	वापस 0;

err_ioremap:
	clk_disable_unprepare(mxc_rng->clk);
	वापस err;
पूर्ण

अटल पूर्णांक __निकास mxc_rnga_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mxc_rng *mxc_rng = platक्रमm_get_drvdata(pdev);

	hwrng_unरेजिस्टर(&mxc_rng->rng);

	clk_disable_unprepare(mxc_rng->clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mxc_rnga_of_match[] = अणु
	अणु .compatible = "fsl,imx21-rnga", पूर्ण,
	अणु .compatible = "fsl,imx31-rnga", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mxc_rnga_of_match);

अटल काष्ठा platक्रमm_driver mxc_rnga_driver = अणु
	.driver = अणु
		.name = "mxc_rnga",
		.of_match_table = mxc_rnga_of_match,
	पूर्ण,
	.हटाओ = __निकास_p(mxc_rnga_हटाओ),
पूर्ण;

module_platक्रमm_driver_probe(mxc_rnga_driver, mxc_rnga_probe);

MODULE_AUTHOR("Freescale Semiconductor, Inc.");
MODULE_DESCRIPTION("H/W RNGA driver for i.MX");
MODULE_LICENSE("GPL");
