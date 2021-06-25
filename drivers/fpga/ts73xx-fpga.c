<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Technologic Systems TS-73xx SBC FPGA loader
 *
 * Copyright (C) 2016 Florian Fainelli <f.fainelli@gmail.com>
 *
 * FPGA Manager Driver क्रम the on-board Altera Cyclone II FPGA found on
 * TS-7300, heavily based on load_fpga.c in their venकरोr tree.
 */

#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/माला.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/fpga/fpga-mgr.h>

#घोषणा TS73XX_FPGA_DATA_REG		0
#घोषणा TS73XX_FPGA_CONFIG_REG		1

#घोषणा TS73XX_FPGA_WRITE_DONE		0x1
#घोषणा TS73XX_FPGA_WRITE_DONE_TIMEOUT	1000	/* us */
#घोषणा TS73XX_FPGA_RESET		0x2
#घोषणा TS73XX_FPGA_RESET_LOW_DELAY	30	/* us */
#घोषणा TS73XX_FPGA_RESET_HIGH_DELAY	80	/* us */
#घोषणा TS73XX_FPGA_LOAD_OK		0x4
#घोषणा TS73XX_FPGA_CONFIG_LOAD		0x8

काष्ठा ts73xx_fpga_priv अणु
	व्योम __iomem	*io_base;
	काष्ठा device	*dev;
पूर्ण;

अटल क्रमागत fpga_mgr_states ts73xx_fpga_state(काष्ठा fpga_manager *mgr)
अणु
	वापस FPGA_MGR_STATE_UNKNOWN;
पूर्ण

अटल पूर्णांक ts73xx_fpga_ग_लिखो_init(काष्ठा fpga_manager *mgr,
				  काष्ठा fpga_image_info *info,
				  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ts73xx_fpga_priv *priv = mgr->priv;

	/* Reset the FPGA */
	ग_लिखोb(0, priv->io_base + TS73XX_FPGA_CONFIG_REG);
	udelay(TS73XX_FPGA_RESET_LOW_DELAY);
	ग_लिखोb(TS73XX_FPGA_RESET, priv->io_base + TS73XX_FPGA_CONFIG_REG);
	udelay(TS73XX_FPGA_RESET_HIGH_DELAY);

	वापस 0;
पूर्ण

अटल पूर्णांक ts73xx_fpga_ग_लिखो(काष्ठा fpga_manager *mgr, स्थिर अक्षर *buf,
			     माप_प्रकार count)
अणु
	काष्ठा ts73xx_fpga_priv *priv = mgr->priv;
	माप_प्रकार i = 0;
	पूर्णांक ret;
	u8 reg;

	जबतक (count--) अणु
		ret = पढ़ोb_poll_समयout(priv->io_base + TS73XX_FPGA_CONFIG_REG,
					 reg, !(reg & TS73XX_FPGA_WRITE_DONE),
					 1, TS73XX_FPGA_WRITE_DONE_TIMEOUT);
		अगर (ret < 0)
			वापस ret;

		ग_लिखोb(buf[i], priv->io_base + TS73XX_FPGA_DATA_REG);
		i++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ts73xx_fpga_ग_लिखो_complete(काष्ठा fpga_manager *mgr,
				      काष्ठा fpga_image_info *info)
अणु
	काष्ठा ts73xx_fpga_priv *priv = mgr->priv;
	u8 reg;

	usleep_range(1000, 2000);
	reg = पढ़ोb(priv->io_base + TS73XX_FPGA_CONFIG_REG);
	reg |= TS73XX_FPGA_CONFIG_LOAD;
	ग_लिखोb(reg, priv->io_base + TS73XX_FPGA_CONFIG_REG);

	usleep_range(1000, 2000);
	reg = पढ़ोb(priv->io_base + TS73XX_FPGA_CONFIG_REG);
	reg &= ~TS73XX_FPGA_CONFIG_LOAD;
	ग_लिखोb(reg, priv->io_base + TS73XX_FPGA_CONFIG_REG);

	reg = पढ़ोb(priv->io_base + TS73XX_FPGA_CONFIG_REG);
	अगर ((reg & TS73XX_FPGA_LOAD_OK) != TS73XX_FPGA_LOAD_OK)
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fpga_manager_ops ts73xx_fpga_ops = अणु
	.state		= ts73xx_fpga_state,
	.ग_लिखो_init	= ts73xx_fpga_ग_लिखो_init,
	.ग_लिखो		= ts73xx_fpga_ग_लिखो,
	.ग_लिखो_complete	= ts73xx_fpga_ग_लिखो_complete,
पूर्ण;

अटल पूर्णांक ts73xx_fpga_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *kdev = &pdev->dev;
	काष्ठा ts73xx_fpga_priv *priv;
	काष्ठा fpga_manager *mgr;
	काष्ठा resource *res;

	priv = devm_kzalloc(kdev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->dev = kdev;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->io_base = devm_ioremap_resource(kdev, res);
	अगर (IS_ERR(priv->io_base))
		वापस PTR_ERR(priv->io_base);

	mgr = devm_fpga_mgr_create(kdev, "TS-73xx FPGA Manager",
				   &ts73xx_fpga_ops, priv);
	अगर (!mgr)
		वापस -ENOMEM;

	वापस devm_fpga_mgr_रेजिस्टर(kdev, mgr);
पूर्ण

अटल काष्ठा platक्रमm_driver ts73xx_fpga_driver = अणु
	.driver	= अणु
		.name	= "ts73xx-fpga-mgr",
	पूर्ण,
	.probe	= ts73xx_fpga_probe,
पूर्ण;
module_platक्रमm_driver(ts73xx_fpga_driver);

MODULE_AUTHOR("Florian Fainelli <f.fainelli@gmail.com>");
MODULE_DESCRIPTION("TS-73xx FPGA Manager driver");
MODULE_LICENSE("GPL v2");
