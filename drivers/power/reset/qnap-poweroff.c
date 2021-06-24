<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * QNAP Turbo NAS Board घातer off. Can also be used on Synology devices.
 *
 * Copyright (C) 2012 Andrew Lunn <andrew@lunn.ch>
 *
 * Based on the code from:
 *
 * Copyright (C) 2009  Martin Michlmayr <tbm@cyrius.com>
 * Copyright (C) 2008  Byron Bradley <byron.bbradley@gmail.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/serial_reg.h>
#समावेश <linux/of.h>
#समावेश <linux/पन.स>
#समावेश <linux/clk.h>

#घोषणा UART1_REG(x)	(base + ((UART_##x) << 2))

काष्ठा घातer_off_cfg अणु
	u32 baud;
	अक्षर cmd;
पूर्ण;

अटल स्थिर काष्ठा घातer_off_cfg qnap_घातer_off_cfg = अणु
	.baud = 19200,
	.cmd = 'A',
पूर्ण;

अटल स्थिर काष्ठा घातer_off_cfg synology_घातer_off_cfg = अणु
	.baud = 9600,
	.cmd = '1',
पूर्ण;

अटल स्थिर काष्ठा of_device_id qnap_घातer_off_of_match_table[] = अणु
	अणु .compatible = "qnap,power-off",
	  .data = &qnap_घातer_off_cfg,
	पूर्ण,
	अणु .compatible = "synology,power-off",
	  .data = &synology_घातer_off_cfg,
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, qnap_घातer_off_of_match_table);

अटल व्योम __iomem *base;
अटल अचिन्हित दीर्घ tclk;
अटल स्थिर काष्ठा घातer_off_cfg *cfg;

अटल व्योम qnap_घातer_off(व्योम)
अणु
	स्थिर अचिन्हित भागisor = ((tclk + (8 * cfg->baud)) / (16 * cfg->baud));

	pr_err("%s: triggering power-off...\n", __func__);

	/* hijack UART1 and reset पूर्णांकo sane state */
	ग_लिखोl(0x83, UART1_REG(LCR));
	ग_लिखोl(भागisor & 0xff, UART1_REG(DLL));
	ग_लिखोl((भागisor >> 8) & 0xff, UART1_REG(DLM));
	ग_लिखोl(0x03, UART1_REG(LCR));
	ग_लिखोl(0x00, UART1_REG(IER));
	ग_लिखोl(0x00, UART1_REG(FCR));
	ग_लिखोl(0x00, UART1_REG(MCR));

	/* send the घातer-off command to PIC */
	ग_लिखोl(cfg->cmd, UART1_REG(TX));
पूर्ण

अटल पूर्णांक qnap_घातer_off_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा resource *res;
	काष्ठा clk *clk;

	स्थिर काष्ठा of_device_id *match =
		of_match_node(qnap_घातer_off_of_match_table, np);
	cfg = match->data;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		dev_err(&pdev->dev, "Missing resource");
		वापस -EINVAL;
	पूर्ण

	base = devm_ioremap(&pdev->dev, res->start, resource_size(res));
	अगर (!base) अणु
		dev_err(&pdev->dev, "Unable to map resource");
		वापस -EINVAL;
	पूर्ण

	/* We need to know tclk in order to calculate the UART भागisor */
	clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(clk)) अणु
		dev_err(&pdev->dev, "Clk missing");
		वापस PTR_ERR(clk);
	पूर्ण

	tclk = clk_get_rate(clk);

	/* Check that nothing अन्यथा has alपढ़ोy setup a handler */
	अगर (pm_घातer_off) अणु
		dev_err(&pdev->dev, "pm_power_off already claimed for %ps",
			pm_घातer_off);
		वापस -EBUSY;
	पूर्ण
	pm_घातer_off = qnap_घातer_off;

	वापस 0;
पूर्ण

अटल पूर्णांक qnap_घातer_off_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	pm_घातer_off = शून्य;
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver qnap_घातer_off_driver = अणु
	.probe	= qnap_घातer_off_probe,
	.हटाओ	= qnap_घातer_off_हटाओ,
	.driver	= अणु
		.name	= "qnap_power_off",
		.of_match_table = of_match_ptr(qnap_घातer_off_of_match_table),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(qnap_घातer_off_driver);

MODULE_AUTHOR("Andrew Lunn <andrew@lunn.ch>");
MODULE_DESCRIPTION("QNAP Power off driver");
MODULE_LICENSE("GPL v2");
