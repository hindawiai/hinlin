<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2005-2008 Freescale Semiconductor, Inc. All Rights Reserved.
 * Copyright 2008 Luotao Fu, kernel@pengutronix.de
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/kसमय.स>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <linux/w1.h>

/*
 * MXC W1 Register offsets
 */
#घोषणा MXC_W1_CONTROL		0x00
# define MXC_W1_CONTROL_RDST	BIT(3)
# define MXC_W1_CONTROL_WR(x)	BIT(5 - (x))
# define MXC_W1_CONTROL_PST	BIT(6)
# define MXC_W1_CONTROL_RPP	BIT(7)
#घोषणा MXC_W1_TIME_DIVIDER	0x02
#घोषणा MXC_W1_RESET		0x04
# define MXC_W1_RESET_RST	BIT(0)

काष्ठा mxc_w1_device अणु
	व्योम __iomem *regs;
	काष्ठा clk *clk;
	काष्ठा w1_bus_master bus_master;
पूर्ण;

/*
 * this is the low level routine to
 * reset the device on the One Wire पूर्णांकerface
 * on the hardware
 */
अटल u8 mxc_w1_ds2_reset_bus(व्योम *data)
अणु
	काष्ठा mxc_w1_device *dev = data;
	kसमय_प्रकार समयout;

	ग_लिखोb(MXC_W1_CONTROL_RPP, dev->regs + MXC_W1_CONTROL);

	/* Wait क्रम reset sequence 511+512us, use 1500us क्रम sure */
	समयout = kसमय_add_us(kसमय_get(), 1500);

	udelay(511 + 512);

	करो अणु
		u8 ctrl = पढ़ोb(dev->regs + MXC_W1_CONTROL);

		/* PST bit is valid after the RPP bit is self-cleared */
		अगर (!(ctrl & MXC_W1_CONTROL_RPP))
			वापस !(ctrl & MXC_W1_CONTROL_PST);
	पूर्ण जबतक (kसमय_beक्रमe(kसमय_get(), समयout));

	वापस 1;
पूर्ण

/*
 * this is the low level routine to पढ़ो/ग_लिखो a bit on the One Wire
 * पूर्णांकerface on the hardware. It करोes ग_लिखो 0 अगर parameter bit is set
 * to 0, otherwise a ग_लिखो 1/पढ़ो.
 */
अटल u8 mxc_w1_ds2_touch_bit(व्योम *data, u8 bit)
अणु
	काष्ठा mxc_w1_device *dev = data;
	kसमय_प्रकार समयout;

	ग_लिखोb(MXC_W1_CONTROL_WR(bit), dev->regs + MXC_W1_CONTROL);

	/* Wait क्रम पढ़ो/ग_लिखो bit (60us, Max 120us), use 200us क्रम sure */
	समयout = kसमय_add_us(kसमय_get(), 200);

	udelay(60);

	करो अणु
		u8 ctrl = पढ़ोb(dev->regs + MXC_W1_CONTROL);

		/* RDST bit is valid after the WR1/RD bit is self-cleared */
		अगर (!(ctrl & MXC_W1_CONTROL_WR(bit)))
			वापस !!(ctrl & MXC_W1_CONTROL_RDST);
	पूर्ण जबतक (kसमय_beक्रमe(kसमय_get(), समयout));

	वापस 0;
पूर्ण

अटल पूर्णांक mxc_w1_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mxc_w1_device *mdev;
	अचिन्हित दीर्घ clkrate;
	अचिन्हित पूर्णांक clkभाग;
	पूर्णांक err;

	mdev = devm_kzalloc(&pdev->dev, माप(काष्ठा mxc_w1_device),
			    GFP_KERNEL);
	अगर (!mdev)
		वापस -ENOMEM;

	mdev->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(mdev->clk))
		वापस PTR_ERR(mdev->clk);

	err = clk_prepare_enable(mdev->clk);
	अगर (err)
		वापस err;

	clkrate = clk_get_rate(mdev->clk);
	अगर (clkrate < 10000000)
		dev_warn(&pdev->dev,
			 "Low clock frequency causes improper function\n");

	clkभाग = DIV_ROUND_CLOSEST(clkrate, 1000000);
	clkrate /= clkभाग;
	अगर ((clkrate < 980000) || (clkrate > 1020000))
		dev_warn(&pdev->dev,
			 "Incorrect time base frequency %lu Hz\n", clkrate);

	mdev->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(mdev->regs)) अणु
		err = PTR_ERR(mdev->regs);
		जाओ out_disable_clk;
	पूर्ण

	/* Software reset 1-Wire module */
	ग_लिखोb(MXC_W1_RESET_RST, mdev->regs + MXC_W1_RESET);
	ग_लिखोb(0, mdev->regs + MXC_W1_RESET);

	ग_लिखोb(clkभाग - 1, mdev->regs + MXC_W1_TIME_DIVIDER);

	mdev->bus_master.data = mdev;
	mdev->bus_master.reset_bus = mxc_w1_ds2_reset_bus;
	mdev->bus_master.touch_bit = mxc_w1_ds2_touch_bit;

	platक्रमm_set_drvdata(pdev, mdev);

	err = w1_add_master_device(&mdev->bus_master);
	अगर (err)
		जाओ out_disable_clk;

	वापस 0;

out_disable_clk:
	clk_disable_unprepare(mdev->clk);
	वापस err;
पूर्ण

/*
 * disassociate the w1 device from the driver
 */
अटल पूर्णांक mxc_w1_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mxc_w1_device *mdev = platक्रमm_get_drvdata(pdev);

	w1_हटाओ_master_device(&mdev->bus_master);

	clk_disable_unprepare(mdev->clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mxc_w1_dt_ids[] = अणु
	अणु .compatible = "fsl,imx21-owire" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mxc_w1_dt_ids);

अटल काष्ठा platक्रमm_driver mxc_w1_driver = अणु
	.driver = अणु
		.name = "mxc_w1",
		.of_match_table = mxc_w1_dt_ids,
	पूर्ण,
	.probe = mxc_w1_probe,
	.हटाओ = mxc_w1_हटाओ,
पूर्ण;
module_platक्रमm_driver(mxc_w1_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Freescale Semiconductors Inc");
MODULE_DESCRIPTION("Driver for One-Wire on MXC");
