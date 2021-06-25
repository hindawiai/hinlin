<शैली गुरु>
/*
* Copyright (C) 2015 Broadcom Corporation
*
* This program is मुक्त software; you can redistribute it and/or
* modअगरy it under the terms of the GNU General Public License as
* published by the Free Software Foundation version 2.
*
* This program is distributed "as is" WITHOUT ANY WARRANTY of any
* kind, whether express or implied; without even the implied warranty
* of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License क्रम more details.
*/
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/input.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/keyboard.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <यंत्र/irq.h>
#समावेश <linux/पन.स>
#समावेश <linux/clk.h>
#समावेश <linux/serपन.स>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>

#घोषणा IPROC_TS_NAME "iproc-ts"

#घोषणा PEN_DOWN_STATUS     1
#घोषणा PEN_UP_STATUS       0

#घोषणा X_MIN               0
#घोषणा Y_MIN               0
#घोषणा X_MAX               0xFFF
#घोषणा Y_MAX               0xFFF

/* Value given by controller क्रम invalid coordinate. */
#घोषणा INVALID_COORD       0xFFFFFFFF

/* Register offsets */
#घोषणा REGCTL1             0x00
#घोषणा REGCTL2             0x04
#घोषणा INTERRUPT_THRES     0x08
#घोषणा INTERRUPT_MASK      0x0c

#घोषणा INTERRUPT_STATUS    0x10
#घोषणा CONTROLLER_STATUS   0x14
#घोषणा FIFO_DATA           0x18
#घोषणा FIFO_DATA_X_Y_MASK  0xFFFF
#घोषणा ANALOG_CONTROL      0x1c

#घोषणा AUX_DATA            0x20
#घोषणा DEBOUNCE_CNTR_STAT  0x24
#घोषणा SCAN_CNTR_STAT      0x28
#घोषणा REM_CNTR_STAT       0x2c

#घोषणा SETTLING_TIMER_STAT 0x30
#घोषणा SPARE_REG           0x34
#घोषणा SOFT_BYPASS_CONTROL 0x38
#घोषणा SOFT_BYPASS_DATA    0x3c


/* Bit values क्रम INTERRUPT_MASK and INTERRUPT_STATUS regs */
#घोषणा TS_PEN_INTR_MASK        BIT(0)
#घोषणा TS_FIFO_INTR_MASK       BIT(2)

/* Bit values क्रम CONTROLLER_STATUS reg1 */
#घोषणा TS_PEN_DOWN             BIT(0)

/* Shअगरt values क्रम control reg1 */
#घोषणा SCANNING_PERIOD_SHIFT   24
#घोषणा DEBOUNCE_TIMEOUT_SHIFT  16
#घोषणा SETTLING_TIMEOUT_SHIFT  8
#घोषणा TOUCH_TIMEOUT_SHIFT     0

/* Shअगरt values क्रम coordinates from fअगरo */
#घोषणा X_COORD_SHIFT  0
#घोषणा Y_COORD_SHIFT  16

/* Bit values क्रम REGCTL2 */
#घोषणा TS_CONTROLLER_EN_BIT    BIT(16)
#घोषणा TS_CONTROLLER_AVGDATA_SHIFT 8
#घोषणा TS_CONTROLLER_AVGDATA_MASK (0x7 << TS_CONTROLLER_AVGDATA_SHIFT)
#घोषणा TS_CONTROLLER_PWR_LDO   BIT(5)
#घोषणा TS_CONTROLLER_PWR_ADC   BIT(4)
#घोषणा TS_CONTROLLER_PWR_BGP   BIT(3)
#घोषणा TS_CONTROLLER_PWR_TS    BIT(2)
#घोषणा TS_WIRE_MODE_BIT        BIT(1)

#घोषणा dbg_reg(dev, priv, reg) \
करो अणु \
	u32 val; \
	regmap_पढ़ो(priv->regmap, reg, &val); \
	dev_dbg(dev, "%20s= 0x%08x\n", #reg, val); \
पूर्ण जबतक (0)

काष्ठा tsc_param अणु
	/* Each step is 1024 us.  Valid 1-256 */
	u32 scanning_period;

	/*  Each step is 512 us.  Valid 0-255 */
	u32 debounce_समयout;

	/*
	 * The settling duration (in ms) is the amount of समय the tsc
	 * रुकोs to allow the voltage to settle after turning on the
	 * drivers in detection mode. Valid values: 0-11
	 *   0 =  0.008 ms
	 *   1 =  0.01 ms
	 *   2 =  0.02 ms
	 *   3 =  0.04 ms
	 *   4 =  0.08 ms
	 *   5 =  0.16 ms
	 *   6 =  0.32 ms
	 *   7 =  0.64 ms
	 *   8 =  1.28 ms
	 *   9 =  2.56 ms
	 *   10 = 5.12 ms
	 *   11 = 10.24 ms
	 */
	u32 settling_समयout;

	/* touch समयout in sample counts */
	u32 touch_समयout;

	/*
	 * Number of data samples which are averaged beक्रमe a final data poपूर्णांक
	 * is placed पूर्णांकo the FIFO
	 */
	u32 average_data;

	/* FIFO threshold */
	u32 fअगरo_threshold;

	/* Optional standard touchscreen properties. */
	u32 max_x;
	u32 max_y;
	u32 fuzz_x;
	u32 fuzz_y;
	bool invert_x;
	bool invert_y;
पूर्ण;

काष्ठा iproc_ts_priv अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा input_dev *idev;

	काष्ठा regmap *regmap;
	काष्ठा clk *tsc_clk;

	पूर्णांक  pen_status;
	काष्ठा tsc_param cfg_params;
पूर्ण;

/*
 * Set शेष values the same as hardware reset values
 * except क्रम fअगरo_threshold with is set to 1.
 */
अटल स्थिर काष्ठा tsc_param iproc_शेष_config = अणु
	.scanning_period  = 0x5,  /* 1 to 256 */
	.debounce_समयout = 0x28, /* 0 to 255 */
	.settling_समयout = 0x7,  /* 0 to 11 */
	.touch_समयout    = 0xa,  /* 0 to 255 */
	.average_data     = 5,    /* entry 5 = 32 pts */
	.fअगरo_threshold   = 1,    /* 0 to 31 */
	.max_x            = X_MAX,
	.max_y            = Y_MAX,
पूर्ण;

अटल व्योम ts_reg_dump(काष्ठा iproc_ts_priv *priv)
अणु
	काष्ठा device *dev = &priv->pdev->dev;

	dbg_reg(dev, priv, REGCTL1);
	dbg_reg(dev, priv, REGCTL2);
	dbg_reg(dev, priv, INTERRUPT_THRES);
	dbg_reg(dev, priv, INTERRUPT_MASK);
	dbg_reg(dev, priv, INTERRUPT_STATUS);
	dbg_reg(dev, priv, CONTROLLER_STATUS);
	dbg_reg(dev, priv, FIFO_DATA);
	dbg_reg(dev, priv, ANALOG_CONTROL);
	dbg_reg(dev, priv, AUX_DATA);
	dbg_reg(dev, priv, DEBOUNCE_CNTR_STAT);
	dbg_reg(dev, priv, SCAN_CNTR_STAT);
	dbg_reg(dev, priv, REM_CNTR_STAT);
	dbg_reg(dev, priv, SETTLING_TIMER_STAT);
	dbg_reg(dev, priv, SPARE_REG);
	dbg_reg(dev, priv, SOFT_BYPASS_CONTROL);
	dbg_reg(dev, priv, SOFT_BYPASS_DATA);
पूर्ण

अटल irqवापस_t iproc_touchscreen_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा platक्रमm_device *pdev = data;
	काष्ठा iproc_ts_priv *priv = platक्रमm_get_drvdata(pdev);
	u32 पूर्णांकr_status;
	u32 raw_coordinate;
	u16 x;
	u16 y;
	पूर्णांक i;
	bool needs_sync = false;

	regmap_पढ़ो(priv->regmap, INTERRUPT_STATUS, &पूर्णांकr_status);
	पूर्णांकr_status &= TS_PEN_INTR_MASK | TS_FIFO_INTR_MASK;
	अगर (पूर्णांकr_status == 0)
		वापस IRQ_NONE;

	/* Clear all पूर्णांकerrupt status bits, ग_लिखो-1-clear */
	regmap_ग_लिखो(priv->regmap, INTERRUPT_STATUS, पूर्णांकr_status);
	/* Pen up/करोwn */
	अगर (पूर्णांकr_status & TS_PEN_INTR_MASK) अणु
		regmap_पढ़ो(priv->regmap, CONTROLLER_STATUS, &priv->pen_status);
		अगर (priv->pen_status & TS_PEN_DOWN)
			priv->pen_status = PEN_DOWN_STATUS;
		अन्यथा
			priv->pen_status = PEN_UP_STATUS;

		input_report_key(priv->idev, BTN_TOUCH,	priv->pen_status);
		needs_sync = true;

		dev_dbg(&priv->pdev->dev,
			"pen up-down (%d)\n", priv->pen_status);
	पूर्ण

	/* coordinates in FIFO exceed the theshold */
	अगर (पूर्णांकr_status & TS_FIFO_INTR_MASK) अणु
		क्रम (i = 0; i < priv->cfg_params.fअगरo_threshold; i++) अणु
			regmap_पढ़ो(priv->regmap, FIFO_DATA, &raw_coordinate);
			अगर (raw_coordinate == INVALID_COORD)
				जारी;

			/*
			 * The x and y coordinate are 16 bits each
			 * with the x in the lower 16 bits and y in the
			 * upper 16 bits.
			 */
			x = (raw_coordinate >> X_COORD_SHIFT) &
				FIFO_DATA_X_Y_MASK;
			y = (raw_coordinate >> Y_COORD_SHIFT) &
				FIFO_DATA_X_Y_MASK;

			/* We only want to retain the 12 msb of the 16 */
			x = (x >> 4) & 0x0FFF;
			y = (y >> 4) & 0x0FFF;

			/* Adjust x y according to LCD tsc mount angle. */
			अगर (priv->cfg_params.invert_x)
				x = priv->cfg_params.max_x - x;

			अगर (priv->cfg_params.invert_y)
				y = priv->cfg_params.max_y - y;

			input_report_असल(priv->idev, ABS_X, x);
			input_report_असल(priv->idev, ABS_Y, y);
			needs_sync = true;

			dev_dbg(&priv->pdev->dev, "xy (0x%x 0x%x)\n", x, y);
		पूर्ण
	पूर्ण

	अगर (needs_sync)
		input_sync(priv->idev);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक iproc_ts_start(काष्ठा input_dev *idev)
अणु
	u32 val;
	u32 mask;
	पूर्णांक error;
	काष्ठा iproc_ts_priv *priv = input_get_drvdata(idev);

	/* Enable घड़ी */
	error = clk_prepare_enable(priv->tsc_clk);
	अगर (error) अणु
		dev_err(&priv->pdev->dev, "%s clk_prepare_enable failed %d\n",
			__func__, error);
		वापस error;
	पूर्ण

	/*
	 * Interrupt is generated when:
	 *  FIFO reaches the पूर्णांक_th value, and pen event(up/करोwn)
	 */
	val = TS_PEN_INTR_MASK | TS_FIFO_INTR_MASK;
	regmap_update_bits(priv->regmap, INTERRUPT_MASK, val, val);

	val = priv->cfg_params.fअगरo_threshold;
	regmap_ग_लिखो(priv->regmap, INTERRUPT_THRES, val);

	/* Initialize control reg1 */
	val = 0;
	val |= priv->cfg_params.scanning_period << SCANNING_PERIOD_SHIFT;
	val |= priv->cfg_params.debounce_समयout << DEBOUNCE_TIMEOUT_SHIFT;
	val |= priv->cfg_params.settling_समयout << SETTLING_TIMEOUT_SHIFT;
	val |= priv->cfg_params.touch_समयout << TOUCH_TIMEOUT_SHIFT;
	regmap_ग_लिखो(priv->regmap, REGCTL1, val);

	/* Try to clear all पूर्णांकerrupt status */
	val = TS_FIFO_INTR_MASK | TS_PEN_INTR_MASK;
	regmap_update_bits(priv->regmap, INTERRUPT_STATUS, val, val);

	/* Initialize control reg2 */
	val = TS_CONTROLLER_EN_BIT | TS_WIRE_MODE_BIT;
	val |= priv->cfg_params.average_data << TS_CONTROLLER_AVGDATA_SHIFT;

	mask = (TS_CONTROLLER_AVGDATA_MASK);
	mask |= (TS_CONTROLLER_PWR_LDO |	/* PWR up LDO */
		   TS_CONTROLLER_PWR_ADC |	/* PWR up ADC */
		   TS_CONTROLLER_PWR_BGP |	/* PWR up BGP */
		   TS_CONTROLLER_PWR_TS);	/* PWR up TS */
	mask |= val;
	regmap_update_bits(priv->regmap, REGCTL2, mask, val);

	ts_reg_dump(priv);

	वापस 0;
पूर्ण

अटल व्योम iproc_ts_stop(काष्ठा input_dev *dev)
अणु
	u32 val;
	काष्ठा iproc_ts_priv *priv = input_get_drvdata(dev);

	/*
	 * Disable FIFO पूर्णांक_th and pen event(up/करोwn)Interrupts only
	 * as the पूर्णांकerrupt mask रेजिस्टर is shared between ADC, TS and
	 * flexसमयr.
	 */
	val = TS_PEN_INTR_MASK | TS_FIFO_INTR_MASK;
	regmap_update_bits(priv->regmap, INTERRUPT_MASK, val, 0);

	/* Only घातer करोwn touch screen controller */
	val = TS_CONTROLLER_PWR_TS;
	regmap_update_bits(priv->regmap, REGCTL2, val, val);

	clk_disable(priv->tsc_clk);
पूर्ण

अटल पूर्णांक iproc_get_tsc_config(काष्ठा device *dev, काष्ठा iproc_ts_priv *priv)
अणु
	काष्ठा device_node *np = dev->of_node;
	u32 val;

	priv->cfg_params = iproc_शेष_config;

	अगर (!np)
		वापस 0;

	अगर (of_property_पढ़ो_u32(np, "scanning_period", &val) >= 0) अणु
		अगर (val < 1 || val > 256) अणु
			dev_err(dev, "scanning_period (%u) must be [1-256]\n",
				val);
			वापस -EINVAL;
		पूर्ण
		priv->cfg_params.scanning_period = val;
	पूर्ण

	अगर (of_property_पढ़ो_u32(np, "debounce_timeout", &val) >= 0) अणु
		अगर (val > 255) अणु
			dev_err(dev, "debounce_timeout (%u) must be [0-255]\n",
				val);
			वापस -EINVAL;
		पूर्ण
		priv->cfg_params.debounce_समयout = val;
	पूर्ण

	अगर (of_property_पढ़ो_u32(np, "settling_timeout", &val) >= 0) अणु
		अगर (val > 11) अणु
			dev_err(dev, "settling_timeout (%u) must be [0-11]\n",
				val);
			वापस -EINVAL;
		पूर्ण
		priv->cfg_params.settling_समयout = val;
	पूर्ण

	अगर (of_property_पढ़ो_u32(np, "touch_timeout", &val) >= 0) अणु
		अगर (val > 255) अणु
			dev_err(dev, "touch_timeout (%u) must be [0-255]\n",
				val);
			वापस -EINVAL;
		पूर्ण
		priv->cfg_params.touch_समयout = val;
	पूर्ण

	अगर (of_property_पढ़ो_u32(np, "average_data", &val) >= 0) अणु
		अगर (val > 8) अणु
			dev_err(dev, "average_data (%u) must be [0-8]\n", val);
			वापस -EINVAL;
		पूर्ण
		priv->cfg_params.average_data = val;
	पूर्ण

	अगर (of_property_पढ़ो_u32(np, "fifo_threshold", &val) >= 0) अणु
		अगर (val > 31) अणु
			dev_err(dev, "fifo_threshold (%u)) must be [0-31]\n",
				val);
			वापस -EINVAL;
		पूर्ण
		priv->cfg_params.fअगरo_threshold = val;
	पूर्ण

	/* Parse optional properties. */
	of_property_पढ़ो_u32(np, "touchscreen-size-x", &priv->cfg_params.max_x);
	of_property_पढ़ो_u32(np, "touchscreen-size-y", &priv->cfg_params.max_y);

	of_property_पढ़ो_u32(np, "touchscreen-fuzz-x",
			     &priv->cfg_params.fuzz_x);
	of_property_पढ़ो_u32(np, "touchscreen-fuzz-y",
			     &priv->cfg_params.fuzz_y);

	priv->cfg_params.invert_x =
		of_property_पढ़ो_bool(np, "touchscreen-inverted-x");
	priv->cfg_params.invert_y =
		of_property_पढ़ो_bool(np, "touchscreen-inverted-y");

	वापस 0;
पूर्ण

अटल पूर्णांक iproc_ts_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iproc_ts_priv *priv;
	काष्ठा input_dev *idev;
	पूर्णांक irq;
	पूर्णांक error;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	/* touchscreen controller memory mapped regs via syscon*/
	priv->regmap = syscon_regmap_lookup_by_phandle(pdev->dev.of_node,
							"ts_syscon");
	अगर (IS_ERR(priv->regmap)) अणु
		error = PTR_ERR(priv->regmap);
		dev_err(&pdev->dev, "unable to map I/O memory:%d\n", error);
		वापस error;
	पूर्ण

	priv->tsc_clk = devm_clk_get(&pdev->dev, "tsc_clk");
	अगर (IS_ERR(priv->tsc_clk)) अणु
		error = PTR_ERR(priv->tsc_clk);
		dev_err(&pdev->dev,
			"failed getting clock tsc_clk: %d\n", error);
		वापस error;
	पूर्ण

	priv->pdev = pdev;
	error = iproc_get_tsc_config(&pdev->dev, priv);
	अगर (error) अणु
		dev_err(&pdev->dev, "get_tsc_config failed: %d\n", error);
		वापस error;
	पूर्ण

	idev = devm_input_allocate_device(&pdev->dev);
	अगर (!idev) अणु
		dev_err(&pdev->dev, "failed to allocate input device\n");
		वापस -ENOMEM;
	पूर्ण

	priv->idev = idev;
	priv->pen_status = PEN_UP_STATUS;

	/* Set input device info  */
	idev->name = IPROC_TS_NAME;
	idev->dev.parent = &pdev->dev;

	idev->id.bustype = BUS_HOST;
	idev->id.venकरोr = SERIO_UNKNOWN;
	idev->id.product = 0;
	idev->id.version = 0;

	idev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
	__set_bit(BTN_TOUCH, idev->keybit);

	input_set_असल_params(idev, ABS_X, X_MIN, priv->cfg_params.max_x,
			     priv->cfg_params.fuzz_x, 0);
	input_set_असल_params(idev, ABS_Y, Y_MIN, priv->cfg_params.max_y,
			     priv->cfg_params.fuzz_y, 0);

	idev->खोलो = iproc_ts_start;
	idev->बंद = iproc_ts_stop;

	input_set_drvdata(idev, priv);
	platक्रमm_set_drvdata(pdev, priv);

	/* get पूर्णांकerrupt */
	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	error = devm_request_irq(&pdev->dev, irq,
				 iproc_touchscreen_पूर्णांकerrupt,
				 IRQF_SHARED, IPROC_TS_NAME, pdev);
	अगर (error)
		वापस error;

	error = input_रेजिस्टर_device(priv->idev);
	अगर (error) अणु
		dev_err(&pdev->dev,
			"failed to register input device: %d\n", error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id iproc_ts_of_match[] = अणु
	अणु.compatible = "brcm,iproc-touchscreen", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, iproc_ts_of_match);

अटल काष्ठा platक्रमm_driver iproc_ts_driver = अणु
	.probe = iproc_ts_probe,
	.driver = अणु
		.name	= IPROC_TS_NAME,
		.of_match_table = of_match_ptr(iproc_ts_of_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(iproc_ts_driver);

MODULE_DESCRIPTION("IPROC Touchscreen driver");
MODULE_AUTHOR("Broadcom");
MODULE_LICENSE("GPL v2");
