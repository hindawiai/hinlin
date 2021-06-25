<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * twl4030_keypad.c - driver क्रम 8x8 keypad controller in twl4030 chips
 *
 * Copyright (C) 2007 Texas Instruments, Inc.
 * Copyright (C) 2008 Nokia Corporation
 *
 * Code re-written क्रम 2430SDP by:
 * Syed Mohammed Khasim <x0khasim@ti.com>
 *
 * Initial Code:
 * Manjunatha G K <manjugk@ti.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/input.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mfd/twl.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>

/*
 * The TWL4030 family chips include a keypad controller that supports
 * up to an 8x8 चयन matrix.  The controller can issue प्रणाली wakeup
 * events, since it uses only the always-on 32KiHz oscillator, and has
 * an पूर्णांकernal state machine that decodes pressed keys, including
 * multi-key combinations.
 *
 * This driver lets boards define what keycodes they wish to report क्रम
 * which scancodes, as part of the "struct twl4030_keypad_data" used in
 * the probe() routine.
 *
 * See the TPS65950 करोcumentation; that's the general availability
 * version of the TWL5030 second generation part.
 */
#घोषणा TWL4030_MAX_ROWS	8	/* TWL4030 hard limit */
#घोषणा TWL4030_MAX_COLS	8
/*
 * Note that we add space क्रम an extra column so that we can handle
 * row lines connected to the gnd (see twl4030_col_xlate()).
 */
#घोषणा TWL4030_ROW_SHIFT	4
#घोषणा TWL4030_KEYMAP_SIZE	(TWL4030_MAX_ROWS << TWL4030_ROW_SHIFT)

काष्ठा twl4030_keypad अणु
	अचिन्हित लघु	keymap[TWL4030_KEYMAP_SIZE];
	u16		kp_state[TWL4030_MAX_ROWS];
	bool		स्वतःrepeat;
	अचिन्हित पूर्णांक	n_rows;
	अचिन्हित पूर्णांक	n_cols;
	पूर्णांक		irq;

	काष्ठा device *dbg_dev;
	काष्ठा input_dev *input;
पूर्ण;

/*----------------------------------------------------------------------*/

/* arbitrary prescaler value 0..7 */
#घोषणा PTV_PRESCALER			4

/* Register Offsets */
#घोषणा KEYP_CTRL			0x00
#घोषणा KEYP_DEB			0x01
#घोषणा KEYP_LONG_KEY			0x02
#घोषणा KEYP_LK_PTV			0x03
#घोषणा KEYP_TIMEOUT_L			0x04
#घोषणा KEYP_TIMEOUT_H			0x05
#घोषणा KEYP_KBC			0x06
#घोषणा KEYP_KBR			0x07
#घोषणा KEYP_SMS			0x08
#घोषणा KEYP_FULL_CODE_7_0		0x09	/* row 0 column status */
#घोषणा KEYP_FULL_CODE_15_8		0x0a	/* ... row 1 ... */
#घोषणा KEYP_FULL_CODE_23_16		0x0b
#घोषणा KEYP_FULL_CODE_31_24		0x0c
#घोषणा KEYP_FULL_CODE_39_32		0x0d
#घोषणा KEYP_FULL_CODE_47_40		0x0e
#घोषणा KEYP_FULL_CODE_55_48		0x0f
#घोषणा KEYP_FULL_CODE_63_56		0x10
#घोषणा KEYP_ISR1			0x11
#घोषणा KEYP_IMR1			0x12
#घोषणा KEYP_ISR2			0x13
#घोषणा KEYP_IMR2			0x14
#घोषणा KEYP_SIR			0x15
#घोषणा KEYP_EDR			0x16	/* edge triggers */
#घोषणा KEYP_SIH_CTRL			0x17

/* KEYP_CTRL_REG Fields */
#घोषणा KEYP_CTRL_SOFT_NRST		BIT(0)
#घोषणा KEYP_CTRL_SOFTMODEN		BIT(1)
#घोषणा KEYP_CTRL_LK_EN			BIT(2)
#घोषणा KEYP_CTRL_TOE_EN		BIT(3)
#घोषणा KEYP_CTRL_TOLE_EN		BIT(4)
#घोषणा KEYP_CTRL_RP_EN			BIT(5)
#घोषणा KEYP_CTRL_KBD_ON		BIT(6)

/* KEYP_DEB, KEYP_LONG_KEY, KEYP_TIMEOUT_x*/
#घोषणा KEYP_PERIOD_US(t, prescale)	((t) / (31 << ((prescale) + 1)) - 1)

/* KEYP_LK_PTV_REG Fields */
#घोषणा KEYP_LK_PTV_PTV_SHIFT		5

/* KEYP_अणुIMR,ISR,SIRपूर्ण Fields */
#घोषणा KEYP_IMR1_MIS			BIT(3)
#घोषणा KEYP_IMR1_TO			BIT(2)
#घोषणा KEYP_IMR1_LK			BIT(1)
#घोषणा KEYP_IMR1_KP			BIT(0)

/* KEYP_EDR Fields */
#घोषणा KEYP_EDR_KP_FALLING		0x01
#घोषणा KEYP_EDR_KP_RISING		0x02
#घोषणा KEYP_EDR_KP_BOTH		0x03
#घोषणा KEYP_EDR_LK_FALLING		0x04
#घोषणा KEYP_EDR_LK_RISING		0x08
#घोषणा KEYP_EDR_TO_FALLING		0x10
#घोषणा KEYP_EDR_TO_RISING		0x20
#घोषणा KEYP_EDR_MIS_FALLING		0x40
#घोषणा KEYP_EDR_MIS_RISING		0x80


/*----------------------------------------------------------------------*/

अटल पूर्णांक twl4030_kpपढ़ो(काष्ठा twl4030_keypad *kp,
		u8 *data, u32 reg, u8 num_bytes)
अणु
	पूर्णांक ret = twl_i2c_पढ़ो(TWL4030_MODULE_KEYPAD, data, reg, num_bytes);

	अगर (ret < 0)
		dev_warn(kp->dbg_dev,
			"Couldn't read TWL4030: %X - ret %d[%x]\n",
			 reg, ret, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक twl4030_kpग_लिखो_u8(काष्ठा twl4030_keypad *kp, u8 data, u32 reg)
अणु
	पूर्णांक ret = twl_i2c_ग_लिखो_u8(TWL4030_MODULE_KEYPAD, data, reg);

	अगर (ret < 0)
		dev_warn(kp->dbg_dev,
			"Could not write TWL4030: %X - ret %d[%x]\n",
			 reg, ret, ret);

	वापस ret;
पूर्ण

अटल अंतरभूत u16 twl4030_col_xlate(काष्ठा twl4030_keypad *kp, u8 col)
अणु
	/*
	 * If all bits in a row are active क्रम all columns then
	 * we have that row line connected to gnd. Mark this
	 * key on as अगर it was on matrix position n_cols (i.e.
	 * one higher than the size of the matrix).
	 */
	अगर (col == 0xFF)
		वापस 1 << kp->n_cols;
	अन्यथा
		वापस col & ((1 << kp->n_cols) - 1);
पूर्ण

अटल पूर्णांक twl4030_पढ़ो_kp_matrix_state(काष्ठा twl4030_keypad *kp, u16 *state)
अणु
	u8 new_state[TWL4030_MAX_ROWS];
	पूर्णांक row;
	पूर्णांक ret = twl4030_kpपढ़ो(kp, new_state,
				 KEYP_FULL_CODE_7_0, kp->n_rows);
	अगर (ret >= 0)
		क्रम (row = 0; row < kp->n_rows; row++)
			state[row] = twl4030_col_xlate(kp, new_state[row]);

	वापस ret;
पूर्ण

अटल bool twl4030_is_in_ghost_state(काष्ठा twl4030_keypad *kp, u16 *key_state)
अणु
	पूर्णांक i;
	u16 check = 0;

	क्रम (i = 0; i < kp->n_rows; i++) अणु
		u16 col = key_state[i];

		अगर ((col & check) && hweight16(col) > 1)
			वापस true;

		check |= col;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम twl4030_kp_scan(काष्ठा twl4030_keypad *kp, bool release_all)
अणु
	काष्ठा input_dev *input = kp->input;
	u16 new_state[TWL4030_MAX_ROWS];
	पूर्णांक col, row;

	अगर (release_all) अणु
		स_रखो(new_state, 0, माप(new_state));
	पूर्ण अन्यथा अणु
		/* check क्रम any changes */
		पूर्णांक ret = twl4030_पढ़ो_kp_matrix_state(kp, new_state);

		अगर (ret < 0)	/* panic ... */
			वापस;

		अगर (twl4030_is_in_ghost_state(kp, new_state))
			वापस;
	पूर्ण

	/* check क्रम changes and prपूर्णांक those */
	क्रम (row = 0; row < kp->n_rows; row++) अणु
		पूर्णांक changed = new_state[row] ^ kp->kp_state[row];

		अगर (!changed)
			जारी;

		/* Extra column handles "all gnd" rows */
		क्रम (col = 0; col < kp->n_cols + 1; col++) अणु
			पूर्णांक code;

			अगर (!(changed & (1 << col)))
				जारी;

			dev_dbg(kp->dbg_dev, "key [%d:%d] %s\n", row, col,
				(new_state[row] & (1 << col)) ?
				"press" : "release");

			code = MATRIX_SCAN_CODE(row, col, TWL4030_ROW_SHIFT);
			input_event(input, EV_MSC, MSC_SCAN, code);
			input_report_key(input, kp->keymap[code],
					 new_state[row] & (1 << col));
		पूर्ण
		kp->kp_state[row] = new_state[row];
	पूर्ण
	input_sync(input);
पूर्ण

/*
 * Keypad पूर्णांकerrupt handler
 */
अटल irqवापस_t करो_kp_irq(पूर्णांक irq, व्योम *_kp)
अणु
	काष्ठा twl4030_keypad *kp = _kp;
	u8 reg;
	पूर्णांक ret;

	/* Read & Clear TWL4030 pending पूर्णांकerrupt */
	ret = twl4030_kpपढ़ो(kp, &reg, KEYP_ISR1, 1);

	/*
	 * Release all keys अगर I2C has gone bad or
	 * the KEYP has gone to idle state.
	 */
	अगर (ret >= 0 && (reg & KEYP_IMR1_KP))
		twl4030_kp_scan(kp, false);
	अन्यथा
		twl4030_kp_scan(kp, true);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक twl4030_kp_program(काष्ठा twl4030_keypad *kp)
अणु
	u8 reg;
	पूर्णांक i;

	/* Enable controller, with hardware decoding but not स्वतःrepeat */
	reg = KEYP_CTRL_SOFT_NRST | KEYP_CTRL_SOFTMODEN
		| KEYP_CTRL_TOE_EN | KEYP_CTRL_KBD_ON;
	अगर (twl4030_kpग_लिखो_u8(kp, reg, KEYP_CTRL) < 0)
		वापस -EIO;

	/*
	 * NOTE: we could use sih_setup() here to package keypad
	 * event sources as four dअगरferent IRQs ... but we करोn't.
	 */

	/* Enable TO rising and KP rising and falling edge detection */
	reg = KEYP_EDR_KP_BOTH | KEYP_EDR_TO_RISING;
	अगर (twl4030_kpग_लिखो_u8(kp, reg, KEYP_EDR) < 0)
		वापस -EIO;

	/* Set PTV prescaler Field */
	reg = (PTV_PRESCALER << KEYP_LK_PTV_PTV_SHIFT);
	अगर (twl4030_kpग_लिखो_u8(kp, reg, KEYP_LK_PTV) < 0)
		वापस -EIO;

	/* Set key debounce समय to 20 ms */
	i = KEYP_PERIOD_US(20000, PTV_PRESCALER);
	अगर (twl4030_kpग_लिखो_u8(kp, i, KEYP_DEB) < 0)
		वापस -EIO;

	/* Set समयout period to 200 ms */
	i = KEYP_PERIOD_US(200000, PTV_PRESCALER);
	अगर (twl4030_kpग_लिखो_u8(kp, (i & 0xFF), KEYP_TIMEOUT_L) < 0)
		वापस -EIO;

	अगर (twl4030_kpग_लिखो_u8(kp, (i >> 8), KEYP_TIMEOUT_H) < 0)
		वापस -EIO;

	/*
	 * Enable Clear-on-Read; disable remembering events that fire
	 * after the IRQ but beक्रमe our handler acks (पढ़ोs) them.
	 */
	reg = TWL4030_SIH_CTRL_COR_MASK | TWL4030_SIH_CTRL_PENDDIS_MASK;
	अगर (twl4030_kpग_लिखो_u8(kp, reg, KEYP_SIH_CTRL) < 0)
		वापस -EIO;

	/* initialize key state; irqs update it from here on */
	अगर (twl4030_पढ़ो_kp_matrix_state(kp, kp->kp_state) < 0)
		वापस -EIO;

	वापस 0;
पूर्ण

/*
 * Registers keypad device with input subप्रणाली
 * and configures TWL4030 keypad रेजिस्टरs
 */
अटल पूर्णांक twl4030_kp_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा twl4030_keypad_data *pdata = dev_get_platdata(&pdev->dev);
	स्थिर काष्ठा matrix_keymap_data *keymap_data = शून्य;
	काष्ठा twl4030_keypad *kp;
	काष्ठा input_dev *input;
	u8 reg;
	पूर्णांक error;

	kp = devm_kzalloc(&pdev->dev, माप(*kp), GFP_KERNEL);
	अगर (!kp)
		वापस -ENOMEM;

	input = devm_input_allocate_device(&pdev->dev);
	अगर (!input)
		वापस -ENOMEM;

	/* get the debug device */
	kp->dbg_dev		= &pdev->dev;
	kp->input		= input;

	/* setup input device */
	input->name		= "TWL4030 Keypad";
	input->phys		= "twl4030_keypad/input0";

	input->id.bustype	= BUS_HOST;
	input->id.venकरोr	= 0x0001;
	input->id.product	= 0x0001;
	input->id.version	= 0x0003;

	अगर (pdata) अणु
		अगर (!pdata->rows || !pdata->cols || !pdata->keymap_data) अणु
			dev_err(&pdev->dev, "Missing platform_data\n");
			वापस -EINVAL;
		पूर्ण

		kp->n_rows = pdata->rows;
		kp->n_cols = pdata->cols;
		kp->स्वतःrepeat = pdata->rep;
		keymap_data = pdata->keymap_data;
	पूर्ण अन्यथा अणु
		error = matrix_keypad_parse_properties(&pdev->dev, &kp->n_rows,
						       &kp->n_cols);
		अगर (error)
			वापस error;

		kp->स्वतःrepeat = true;
	पूर्ण

	अगर (kp->n_rows > TWL4030_MAX_ROWS || kp->n_cols > TWL4030_MAX_COLS) अणु
		dev_err(&pdev->dev,
			"Invalid rows/cols amount specified in platform/devicetree data\n");
		वापस -EINVAL;
	पूर्ण

	kp->irq = platक्रमm_get_irq(pdev, 0);
	अगर (kp->irq < 0)
		वापस kp->irq;

	error = matrix_keypad_build_keymap(keymap_data, शून्य,
					   TWL4030_MAX_ROWS,
					   1 << TWL4030_ROW_SHIFT,
					   kp->keymap, input);
	अगर (error) अणु
		dev_err(kp->dbg_dev, "Failed to build keymap\n");
		वापस error;
	पूर्ण

	input_set_capability(input, EV_MSC, MSC_SCAN);
	/* Enable स्वतः repeat feature of Linux input subप्रणाली */
	अगर (kp->स्वतःrepeat)
		__set_bit(EV_REP, input->evbit);

	error = input_रेजिस्टर_device(input);
	अगर (error) अणु
		dev_err(kp->dbg_dev,
			"Unable to register twl4030 keypad device\n");
		वापस error;
	पूर्ण

	error = twl4030_kp_program(kp);
	अगर (error)
		वापस error;

	/*
	 * This ISR will always execute in kernel thपढ़ो context because of
	 * the need to access the TWL4030 over the I2C bus.
	 *
	 * NOTE:  we assume this host is wired to TWL4040 INT1, not INT2 ...
	 */
	error = devm_request_thपढ़ोed_irq(&pdev->dev, kp->irq, शून्य, करो_kp_irq,
					  0, pdev->name, kp);
	अगर (error) अणु
		dev_info(kp->dbg_dev, "request_irq failed for irq no=%d: %d\n",
			kp->irq, error);
		वापस error;
	पूर्ण

	/* Enable KP and TO पूर्णांकerrupts now. */
	reg = (u8) ~(KEYP_IMR1_KP | KEYP_IMR1_TO);
	अगर (twl4030_kpग_लिखो_u8(kp, reg, KEYP_IMR1)) अणु
		/* mask all events - we करोn't care about the result */
		(व्योम) twl4030_kpग_लिखो_u8(kp, 0xff, KEYP_IMR1);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id twl4030_keypad_dt_match_table[] = अणु
	अणु .compatible = "ti,twl4030-keypad" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, twl4030_keypad_dt_match_table);
#पूर्ण_अगर

/*
 * NOTE: twl4030 are multi-function devices connected via I2C.
 * So this device is a child of an I2C parent, thus it needs to
 * support unplug/replug (which most platक्रमm devices करोn't).
 */

अटल काष्ठा platक्रमm_driver twl4030_kp_driver = अणु
	.probe		= twl4030_kp_probe,
	.driver		= अणु
		.name	= "twl4030_keypad",
		.of_match_table = of_match_ptr(twl4030_keypad_dt_match_table),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(twl4030_kp_driver);

MODULE_AUTHOR("Texas Instruments");
MODULE_DESCRIPTION("TWL4030 Keypad Driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:twl4030_keypad");
