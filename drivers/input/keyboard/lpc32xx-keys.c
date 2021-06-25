<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * NXP LPC32xx SoC Key Scan Interface
 *
 * Authors:
 *    Kevin Wells <kevin.wells@nxp.com>
 *    Roland Stigge <stigge@antcom.de>
 *
 * Copyright (C) 2010 NXP Semiconductors
 * Copyright (C) 2012 Roland Stigge
 *
 * This controller supports square key matrices from 1x1 up to 8x8
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/irq.h>
#समावेश <linux/pm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/input.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/input/matrix_keypad.h>

#घोषणा DRV_NAME				"lpc32xx_keys"

/*
 * Key scanner रेजिस्टर offsets
 */
#घोषणा LPC32XX_KS_DEB(x)			((x) + 0x00)
#घोषणा LPC32XX_KS_STATE_COND(x)		((x) + 0x04)
#घोषणा LPC32XX_KS_IRQ(x)			((x) + 0x08)
#घोषणा LPC32XX_KS_SCAN_CTL(x)			((x) + 0x0C)
#घोषणा LPC32XX_KS_FAST_TST(x)			((x) + 0x10)
#घोषणा LPC32XX_KS_MATRIX_DIM(x)		((x) + 0x14) /* 1..8 */
#घोषणा LPC32XX_KS_DATA(x, y)			((x) + 0x40 + ((y) << 2))

#घोषणा LPC32XX_KSCAN_DEB_NUM_DEB_PASS(n)	((n) & 0xFF)

#घोषणा LPC32XX_KSCAN_SCOND_IN_IDLE		0x0
#घोषणा LPC32XX_KSCAN_SCOND_IN_SCANONCE		0x1
#घोषणा LPC32XX_KSCAN_SCOND_IN_IRQGEN		0x2
#घोषणा LPC32XX_KSCAN_SCOND_IN_SCAN_MATRIX	0x3

#घोषणा LPC32XX_KSCAN_IRQ_PENDING_CLR		0x1

#घोषणा LPC32XX_KSCAN_SCTRL_SCAN_DELAY(n)	((n) & 0xFF)

#घोषणा LPC32XX_KSCAN_FTST_FORCESCANONCE	0x1
#घोषणा LPC32XX_KSCAN_FTST_USE32K_CLK		0x2

#घोषणा LPC32XX_KSCAN_MSEL_SELECT(n)		((n) & 0xF)

काष्ठा lpc32xx_kscan_drv अणु
	काष्ठा input_dev *input;
	काष्ठा clk *clk;
	व्योम __iomem *kscan_base;
	अचिन्हित पूर्णांक irq;

	u32 matrix_sz;		/* Size of matrix in XxY, ie. 3 = 3x3 */
	u32 deb_clks;		/* Debounce घड़ीs (based on 32KHz घड़ी) */
	u32 scan_delay;		/* Scan delay (based on 32KHz घड़ी) */

	अचिन्हित लघु *keymap;	/* Poपूर्णांकer to key map क्रम the scan matrix */
	अचिन्हित पूर्णांक row_shअगरt;

	u8 lastkeystates[8];
पूर्ण;

अटल व्योम lpc32xx_mod_states(काष्ठा lpc32xx_kscan_drv *kscandat, पूर्णांक col)
अणु
	काष्ठा input_dev *input = kscandat->input;
	अचिन्हित row, changed, scancode, keycode;
	u8 key;

	key = पढ़ोl(LPC32XX_KS_DATA(kscandat->kscan_base, col));
	changed = key ^ kscandat->lastkeystates[col];
	kscandat->lastkeystates[col] = key;

	क्रम (row = 0; changed; row++, changed >>= 1) अणु
		अगर (changed & 1) अणु
			/* Key state changed, संकेत an event */
			scancode = MATRIX_SCAN_CODE(row, col,
						    kscandat->row_shअगरt);
			keycode = kscandat->keymap[scancode];
			input_event(input, EV_MSC, MSC_SCAN, scancode);
			input_report_key(input, keycode, key & (1 << row));
		पूर्ण
	पूर्ण
पूर्ण

अटल irqवापस_t lpc32xx_kscan_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा lpc32xx_kscan_drv *kscandat = dev_id;
	पूर्णांक i;

	क्रम (i = 0; i < kscandat->matrix_sz; i++)
		lpc32xx_mod_states(kscandat, i);

	ग_लिखोl(1, LPC32XX_KS_IRQ(kscandat->kscan_base));

	input_sync(kscandat->input);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक lpc32xx_kscan_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा lpc32xx_kscan_drv *kscandat = input_get_drvdata(dev);
	पूर्णांक error;

	error = clk_prepare_enable(kscandat->clk);
	अगर (error)
		वापस error;

	ग_लिखोl(1, LPC32XX_KS_IRQ(kscandat->kscan_base));

	वापस 0;
पूर्ण

अटल व्योम lpc32xx_kscan_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा lpc32xx_kscan_drv *kscandat = input_get_drvdata(dev);

	ग_लिखोl(1, LPC32XX_KS_IRQ(kscandat->kscan_base));
	clk_disable_unprepare(kscandat->clk);
पूर्ण

अटल पूर्णांक lpc32xx_parse_dt(काष्ठा device *dev,
				      काष्ठा lpc32xx_kscan_drv *kscandat)
अणु
	काष्ठा device_node *np = dev->of_node;
	u32 rows = 0, columns = 0;
	पूर्णांक err;

	err = matrix_keypad_parse_properties(dev, &rows, &columns);
	अगर (err)
		वापस err;
	अगर (rows != columns) अणु
		dev_err(dev, "rows and columns must be equal!\n");
		वापस -EINVAL;
	पूर्ण

	kscandat->matrix_sz = rows;
	kscandat->row_shअगरt = get_count_order(columns);

	of_property_पढ़ो_u32(np, "nxp,debounce-delay-ms", &kscandat->deb_clks);
	of_property_पढ़ो_u32(np, "nxp,scan-delay-ms", &kscandat->scan_delay);
	अगर (!kscandat->deb_clks || !kscandat->scan_delay) अणु
		dev_err(dev, "debounce or scan delay not specified\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lpc32xx_kscan_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lpc32xx_kscan_drv *kscandat;
	काष्ठा input_dev *input;
	काष्ठा resource *res;
	माप_प्रकार keymap_size;
	पूर्णांक error;
	पूर्णांक irq;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		dev_err(&pdev->dev, "failed to get platform I/O memory\n");
		वापस -EINVAL;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस -EINVAL;

	kscandat = devm_kzalloc(&pdev->dev, माप(*kscandat),
				GFP_KERNEL);
	अगर (!kscandat)
		वापस -ENOMEM;

	error = lpc32xx_parse_dt(&pdev->dev, kscandat);
	अगर (error) अणु
		dev_err(&pdev->dev, "failed to parse device tree\n");
		वापस error;
	पूर्ण

	keymap_size = माप(kscandat->keymap[0]) *
				(kscandat->matrix_sz << kscandat->row_shअगरt);
	kscandat->keymap = devm_kzalloc(&pdev->dev, keymap_size, GFP_KERNEL);
	अगर (!kscandat->keymap)
		वापस -ENOMEM;

	kscandat->input = input = devm_input_allocate_device(&pdev->dev);
	अगर (!input) अणु
		dev_err(&pdev->dev, "failed to allocate input device\n");
		वापस -ENOMEM;
	पूर्ण

	/* Setup key input */
	input->name		= pdev->name;
	input->phys		= "lpc32xx/input0";
	input->id.venकरोr	= 0x0001;
	input->id.product	= 0x0001;
	input->id.version	= 0x0100;
	input->खोलो		= lpc32xx_kscan_खोलो;
	input->बंद		= lpc32xx_kscan_बंद;
	input->dev.parent	= &pdev->dev;

	input_set_capability(input, EV_MSC, MSC_SCAN);

	error = matrix_keypad_build_keymap(शून्य, शून्य,
					   kscandat->matrix_sz,
					   kscandat->matrix_sz,
					   kscandat->keymap, kscandat->input);
	अगर (error) अणु
		dev_err(&pdev->dev, "failed to build keymap\n");
		वापस error;
	पूर्ण

	input_set_drvdata(kscandat->input, kscandat);

	kscandat->kscan_base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(kscandat->kscan_base))
		वापस PTR_ERR(kscandat->kscan_base);

	/* Get the key scanner घड़ी */
	kscandat->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(kscandat->clk)) अणु
		dev_err(&pdev->dev, "failed to get clock\n");
		वापस PTR_ERR(kscandat->clk);
	पूर्ण

	/* Configure the key scanner */
	error = clk_prepare_enable(kscandat->clk);
	अगर (error)
		वापस error;

	ग_लिखोl(kscandat->deb_clks, LPC32XX_KS_DEB(kscandat->kscan_base));
	ग_लिखोl(kscandat->scan_delay, LPC32XX_KS_SCAN_CTL(kscandat->kscan_base));
	ग_लिखोl(LPC32XX_KSCAN_FTST_USE32K_CLK,
	       LPC32XX_KS_FAST_TST(kscandat->kscan_base));
	ग_लिखोl(kscandat->matrix_sz,
	       LPC32XX_KS_MATRIX_DIM(kscandat->kscan_base));
	ग_लिखोl(1, LPC32XX_KS_IRQ(kscandat->kscan_base));
	clk_disable_unprepare(kscandat->clk);

	error = devm_request_irq(&pdev->dev, irq, lpc32xx_kscan_irq, 0,
				 pdev->name, kscandat);
	अगर (error) अणु
		dev_err(&pdev->dev, "failed to request irq\n");
		वापस error;
	पूर्ण

	error = input_रेजिस्टर_device(kscandat->input);
	अगर (error) अणु
		dev_err(&pdev->dev, "failed to register input device\n");
		वापस error;
	पूर्ण

	platक्रमm_set_drvdata(pdev, kscandat);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक lpc32xx_kscan_suspend(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा lpc32xx_kscan_drv *kscandat = platक्रमm_get_drvdata(pdev);
	काष्ठा input_dev *input = kscandat->input;

	mutex_lock(&input->mutex);

	अगर (input_device_enabled(input)) अणु
		/* Clear IRQ and disable घड़ी */
		ग_लिखोl(1, LPC32XX_KS_IRQ(kscandat->kscan_base));
		clk_disable_unprepare(kscandat->clk);
	पूर्ण

	mutex_unlock(&input->mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक lpc32xx_kscan_resume(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा lpc32xx_kscan_drv *kscandat = platक्रमm_get_drvdata(pdev);
	काष्ठा input_dev *input = kscandat->input;
	पूर्णांक retval = 0;

	mutex_lock(&input->mutex);

	अगर (input_device_enabled(input)) अणु
		/* Enable घड़ी and clear IRQ */
		retval = clk_prepare_enable(kscandat->clk);
		अगर (retval == 0)
			ग_लिखोl(1, LPC32XX_KS_IRQ(kscandat->kscan_base));
	पूर्ण

	mutex_unlock(&input->mutex);
	वापस retval;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(lpc32xx_kscan_pm_ops, lpc32xx_kscan_suspend,
			 lpc32xx_kscan_resume);

अटल स्थिर काष्ठा of_device_id lpc32xx_kscan_match[] = अणु
	अणु .compatible = "nxp,lpc3220-key" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, lpc32xx_kscan_match);

अटल काष्ठा platक्रमm_driver lpc32xx_kscan_driver = अणु
	.probe		= lpc32xx_kscan_probe,
	.driver		= अणु
		.name	= DRV_NAME,
		.pm	= &lpc32xx_kscan_pm_ops,
		.of_match_table = lpc32xx_kscan_match,
	पूर्ण
पूर्ण;

module_platक्रमm_driver(lpc32xx_kscan_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kevin Wells <kevin.wells@nxp.com>");
MODULE_AUTHOR("Roland Stigge <stigge@antcom.de>");
MODULE_DESCRIPTION("Key scanner driver for LPC32XX devices");
