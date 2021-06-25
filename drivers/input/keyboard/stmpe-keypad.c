<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) ST-Ericsson SA 2010
 *
 * Author: Rabin Vincent <rabin.vincent@stericsson.com> क्रम ST-Ericsson
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/input/matrix_keypad.h>
#समावेश <linux/mfd/sपंचांगpe.h>

/* These are at the same addresses in all STMPE variants */
#घोषणा STMPE_KPC_COL			0x60
#घोषणा STMPE_KPC_ROW_MSB		0x61
#घोषणा STMPE_KPC_ROW_LSB		0x62
#घोषणा STMPE_KPC_CTRL_MSB		0x63
#घोषणा STMPE_KPC_CTRL_LSB		0x64
#घोषणा STMPE_KPC_COMBI_KEY_0		0x65
#घोषणा STMPE_KPC_COMBI_KEY_1		0x66
#घोषणा STMPE_KPC_COMBI_KEY_2		0x67
#घोषणा STMPE_KPC_DATA_BYTE0		0x68
#घोषणा STMPE_KPC_DATA_BYTE1		0x69
#घोषणा STMPE_KPC_DATA_BYTE2		0x6a
#घोषणा STMPE_KPC_DATA_BYTE3		0x6b
#घोषणा STMPE_KPC_DATA_BYTE4		0x6c

#घोषणा STMPE_KPC_CTRL_LSB_SCAN		(0x1 << 0)
#घोषणा STMPE_KPC_CTRL_LSB_DEBOUNCE	(0x7f << 1)
#घोषणा STMPE_KPC_CTRL_MSB_SCAN_COUNT	(0xf << 4)

#घोषणा STMPE_KPC_ROW_MSB_ROWS		0xff

#घोषणा STMPE_KPC_DATA_UP		(0x1 << 7)
#घोषणा STMPE_KPC_DATA_ROW		(0xf << 3)
#घोषणा STMPE_KPC_DATA_COL		(0x7 << 0)
#घोषणा STMPE_KPC_DATA_NOKEY_MASK	0x78

#घोषणा STMPE_KEYPAD_MAX_DEBOUNCE	127
#घोषणा STMPE_KEYPAD_MAX_SCAN_COUNT	15

#घोषणा STMPE_KEYPAD_MAX_ROWS		8
#घोषणा STMPE_KEYPAD_MAX_COLS		8
#घोषणा STMPE_KEYPAD_ROW_SHIFT		3
#घोषणा STMPE_KEYPAD_KEYMAP_MAX_SIZE \
	(STMPE_KEYPAD_MAX_ROWS * STMPE_KEYPAD_MAX_COLS)


#घोषणा STMPE1601_NUM_DATA	5
#घोषणा STMPE2401_NUM_DATA	3
#घोषणा STMPE2403_NUM_DATA	5

/* Make sure it covers all हालs above */
#घोषणा MAX_NUM_DATA		5

/**
 * काष्ठा sपंचांगpe_keypad_variant - model-specअगरic attributes
 * @स्वतः_increment: whether the KPC_DATA_BYTE रेजिस्टर address
 *		    स्वतः-increments on multiple पढ़ो
 * @set_pullup: whether the pins need to have their pull-ups set
 * @num_data: number of data bytes
 * @num_normal_data: number of normal keys' data bytes
 * @max_cols: maximum number of columns supported
 * @max_rows: maximum number of rows supported
 * @col_gpios: biपंचांगask of gpios which can be used क्रम columns
 * @row_gpios: biपंचांगask of gpios which can be used क्रम rows
 */
काष्ठा sपंचांगpe_keypad_variant अणु
	bool		स्वतः_increment;
	bool		set_pullup;
	पूर्णांक		num_data;
	पूर्णांक		num_normal_data;
	पूर्णांक		max_cols;
	पूर्णांक		max_rows;
	अचिन्हित पूर्णांक	col_gpios;
	अचिन्हित पूर्णांक	row_gpios;
पूर्ण;

अटल स्थिर काष्ठा sपंचांगpe_keypad_variant sपंचांगpe_keypad_variants[] = अणु
	[STMPE1601] = अणु
		.स्वतः_increment		= true,
		.num_data		= STMPE1601_NUM_DATA,
		.num_normal_data	= 3,
		.max_cols		= 8,
		.max_rows		= 8,
		.col_gpios		= 0x000ff,	/* GPIO 0 - 7 */
		.row_gpios		= 0x0ff00,	/* GPIO 8 - 15 */
	पूर्ण,
	[STMPE2401] = अणु
		.स्वतः_increment		= false,
		.set_pullup		= true,
		.num_data		= STMPE2401_NUM_DATA,
		.num_normal_data	= 2,
		.max_cols		= 8,
		.max_rows		= 12,
		.col_gpios		= 0x0000ff,	/* GPIO 0 - 7*/
		.row_gpios		= 0x1f7f00,	/* GPIO 8-14, 16-20 */
	पूर्ण,
	[STMPE2403] = अणु
		.स्वतः_increment		= true,
		.set_pullup		= true,
		.num_data		= STMPE2403_NUM_DATA,
		.num_normal_data	= 3,
		.max_cols		= 8,
		.max_rows		= 12,
		.col_gpios		= 0x0000ff,	/* GPIO 0 - 7*/
		.row_gpios		= 0x1fef00,	/* GPIO 8-14, 16-20 */
	पूर्ण,
पूर्ण;

/**
 * काष्ठा sपंचांगpe_keypad - STMPE keypad state container
 * @sपंचांगpe: poपूर्णांकer to parent STMPE device
 * @input: spawned input device
 * @variant: STMPE variant
 * @debounce_ms: debounce पूर्णांकerval, in ms.  Maximum is
 *		 %STMPE_KEYPAD_MAX_DEBOUNCE.
 * @scan_count: number of key scanning cycles to confirm key data.
 *		Maximum is %STMPE_KEYPAD_MAX_SCAN_COUNT.
 * @no_स्वतःrepeat: disable key स्वतःrepeat
 * @rows: biपंचांगask क्रम the rows
 * @cols: biपंचांगask क्रम the columns
 * @keymap: the keymap
 */
काष्ठा sपंचांगpe_keypad अणु
	काष्ठा sपंचांगpe *sपंचांगpe;
	काष्ठा input_dev *input;
	स्थिर काष्ठा sपंचांगpe_keypad_variant *variant;
	अचिन्हित पूर्णांक debounce_ms;
	अचिन्हित पूर्णांक scan_count;
	bool no_स्वतःrepeat;
	अचिन्हित पूर्णांक rows;
	अचिन्हित पूर्णांक cols;
	अचिन्हित लघु keymap[STMPE_KEYPAD_KEYMAP_MAX_SIZE];
पूर्ण;

अटल पूर्णांक sपंचांगpe_keypad_पढ़ो_data(काष्ठा sपंचांगpe_keypad *keypad, u8 *data)
अणु
	स्थिर काष्ठा sपंचांगpe_keypad_variant *variant = keypad->variant;
	काष्ठा sपंचांगpe *sपंचांगpe = keypad->sपंचांगpe;
	पूर्णांक ret;
	पूर्णांक i;

	अगर (variant->स्वतः_increment)
		वापस sपंचांगpe_block_पढ़ो(sपंचांगpe, STMPE_KPC_DATA_BYTE0,
					variant->num_data, data);

	क्रम (i = 0; i < variant->num_data; i++) अणु
		ret = sपंचांगpe_reg_पढ़ो(sपंचांगpe, STMPE_KPC_DATA_BYTE0 + i);
		अगर (ret < 0)
			वापस ret;

		data[i] = ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल irqवापस_t sपंचांगpe_keypad_irq(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा sपंचांगpe_keypad *keypad = dev;
	काष्ठा input_dev *input = keypad->input;
	स्थिर काष्ठा sपंचांगpe_keypad_variant *variant = keypad->variant;
	u8 fअगरo[MAX_NUM_DATA];
	पूर्णांक ret;
	पूर्णांक i;

	ret = sपंचांगpe_keypad_पढ़ो_data(keypad, fअगरo);
	अगर (ret < 0)
		वापस IRQ_NONE;

	क्रम (i = 0; i < variant->num_normal_data; i++) अणु
		u8 data = fअगरo[i];
		पूर्णांक row = (data & STMPE_KPC_DATA_ROW) >> 3;
		पूर्णांक col = data & STMPE_KPC_DATA_COL;
		पूर्णांक code = MATRIX_SCAN_CODE(row, col, STMPE_KEYPAD_ROW_SHIFT);
		bool up = data & STMPE_KPC_DATA_UP;

		अगर ((data & STMPE_KPC_DATA_NOKEY_MASK)
			== STMPE_KPC_DATA_NOKEY_MASK)
			जारी;

		input_event(input, EV_MSC, MSC_SCAN, code);
		input_report_key(input, keypad->keymap[code], !up);
		input_sync(input);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक sपंचांगpe_keypad_altfunc_init(काष्ठा sपंचांगpe_keypad *keypad)
अणु
	स्थिर काष्ठा sपंचांगpe_keypad_variant *variant = keypad->variant;
	अचिन्हित पूर्णांक col_gpios = variant->col_gpios;
	अचिन्हित पूर्णांक row_gpios = variant->row_gpios;
	काष्ठा sपंचांगpe *sपंचांगpe = keypad->sपंचांगpe;
	u8 pureg = sपंचांगpe->regs[STMPE_IDX_GPPUR_LSB];
	अचिन्हित पूर्णांक pins = 0;
	अचिन्हित पूर्णांक pu_pins = 0;
	पूर्णांक ret;
	पूर्णांक i;

	/*
	 * Figure out which pins need to be set to the keypad alternate
	 * function.
	 *
	 * अणुcols,rowsपूर्ण_gpios are biपंचांगasks of which pins on the chip can be used
	 * क्रम the keypad.
	 *
	 * keypad->अणुcols,rowsपूर्ण are a biपंचांगask of which pins (of the ones useable
	 * क्रम the keypad) are used on the board.
	 */

	क्रम (i = 0; i < variant->max_cols; i++) अणु
		पूर्णांक num = __ffs(col_gpios);

		अगर (keypad->cols & (1 << i)) अणु
			pins |= 1 << num;
			pu_pins |= 1 << num;
		पूर्ण

		col_gpios &= ~(1 << num);
	पूर्ण

	क्रम (i = 0; i < variant->max_rows; i++) अणु
		पूर्णांक num = __ffs(row_gpios);

		अगर (keypad->rows & (1 << i))
			pins |= 1 << num;

		row_gpios &= ~(1 << num);
	पूर्ण

	ret = sपंचांगpe_set_altfunc(sपंचांगpe, pins, STMPE_BLOCK_KEYPAD);
	अगर (ret)
		वापस ret;

	/*
	 * On STMPE24xx, set pin bias to pull-up on all keypad input
	 * pins (columns), this incidentally happen to be maximum 8 pins
	 * and placed at GPIO0-7 so only the LSB of the pull up रेजिस्टर
	 * ever needs to be written.
	 */
	अगर (variant->set_pullup) अणु
		u8 val;

		ret = sपंचांगpe_reg_पढ़ो(sपंचांगpe, pureg);
		अगर (ret)
			वापस ret;

		/* Do not touch unused pins, may be used क्रम GPIO */
		val = ret & ~pu_pins;
		val |= pu_pins;

		ret = sपंचांगpe_reg_ग_लिखो(sपंचांगpe, pureg, val);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांगpe_keypad_chip_init(काष्ठा sपंचांगpe_keypad *keypad)
अणु
	स्थिर काष्ठा sपंचांगpe_keypad_variant *variant = keypad->variant;
	काष्ठा sपंचांगpe *sपंचांगpe = keypad->sपंचांगpe;
	पूर्णांक ret;

	अगर (keypad->debounce_ms > STMPE_KEYPAD_MAX_DEBOUNCE)
		वापस -EINVAL;

	अगर (keypad->scan_count > STMPE_KEYPAD_MAX_SCAN_COUNT)
		वापस -EINVAL;

	ret = sपंचांगpe_enable(sपंचांगpe, STMPE_BLOCK_KEYPAD);
	अगर (ret < 0)
		वापस ret;

	ret = sपंचांगpe_keypad_altfunc_init(keypad);
	अगर (ret < 0)
		वापस ret;

	ret = sपंचांगpe_reg_ग_लिखो(sपंचांगpe, STMPE_KPC_COL, keypad->cols);
	अगर (ret < 0)
		वापस ret;

	ret = sपंचांगpe_reg_ग_लिखो(sपंचांगpe, STMPE_KPC_ROW_LSB, keypad->rows);
	अगर (ret < 0)
		वापस ret;

	अगर (variant->max_rows > 8) अणु
		ret = sपंचांगpe_set_bits(sपंचांगpe, STMPE_KPC_ROW_MSB,
				     STMPE_KPC_ROW_MSB_ROWS,
				     keypad->rows >> 8);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	ret = sपंचांगpe_set_bits(sपंचांगpe, STMPE_KPC_CTRL_MSB,
			     STMPE_KPC_CTRL_MSB_SCAN_COUNT,
			     keypad->scan_count << 4);
	अगर (ret < 0)
		वापस ret;

	वापस sपंचांगpe_set_bits(sपंचांगpe, STMPE_KPC_CTRL_LSB,
			      STMPE_KPC_CTRL_LSB_SCAN |
			      STMPE_KPC_CTRL_LSB_DEBOUNCE,
			      STMPE_KPC_CTRL_LSB_SCAN |
			      (keypad->debounce_ms << 1));
पूर्ण

अटल व्योम sपंचांगpe_keypad_fill_used_pins(काष्ठा sपंचांगpe_keypad *keypad,
					u32 used_rows, u32 used_cols)
अणु
	पूर्णांक row, col;

	क्रम (row = 0; row < used_rows; row++) अणु
		क्रम (col = 0; col < used_cols; col++) अणु
			पूर्णांक code = MATRIX_SCAN_CODE(row, col,
						    STMPE_KEYPAD_ROW_SHIFT);
			अगर (keypad->keymap[code] != KEY_RESERVED) अणु
				keypad->rows |= 1 << row;
				keypad->cols |= 1 << col;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक sपंचांगpe_keypad_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sपंचांगpe *sपंचांगpe = dev_get_drvdata(pdev->dev.parent);
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा sपंचांगpe_keypad *keypad;
	काष्ठा input_dev *input;
	u32 rows;
	u32 cols;
	पूर्णांक error;
	पूर्णांक irq;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	keypad = devm_kzalloc(&pdev->dev, माप(काष्ठा sपंचांगpe_keypad),
			      GFP_KERNEL);
	अगर (!keypad)
		वापस -ENOMEM;

	keypad->sपंचांगpe = sपंचांगpe;
	keypad->variant = &sपंचांगpe_keypad_variants[sपंचांगpe->partnum];

	of_property_पढ़ो_u32(np, "debounce-interval", &keypad->debounce_ms);
	of_property_पढ़ो_u32(np, "st,scan-count", &keypad->scan_count);
	keypad->no_स्वतःrepeat = of_property_पढ़ो_bool(np, "st,no-autorepeat");

	input = devm_input_allocate_device(&pdev->dev);
	अगर (!input)
		वापस -ENOMEM;

	input->name = "STMPE keypad";
	input->id.bustype = BUS_I2C;
	input->dev.parent = &pdev->dev;

	error = matrix_keypad_parse_properties(&pdev->dev, &rows, &cols);
	अगर (error)
		वापस error;

	error = matrix_keypad_build_keymap(शून्य, शून्य, rows, cols,
					   keypad->keymap, input);
	अगर (error)
		वापस error;

	input_set_capability(input, EV_MSC, MSC_SCAN);
	अगर (!keypad->no_स्वतःrepeat)
		__set_bit(EV_REP, input->evbit);

	sपंचांगpe_keypad_fill_used_pins(keypad, rows, cols);

	keypad->input = input;

	error = sपंचांगpe_keypad_chip_init(keypad);
	अगर (error < 0)
		वापस error;

	error = devm_request_thपढ़ोed_irq(&pdev->dev, irq,
					  शून्य, sपंचांगpe_keypad_irq,
					  IRQF_ONESHOT, "stmpe-keypad", keypad);
	अगर (error) अणु
		dev_err(&pdev->dev, "unable to get irq: %d\n", error);
		वापस error;
	पूर्ण

	error = input_रेजिस्टर_device(input);
	अगर (error) अणु
		dev_err(&pdev->dev,
			"unable to register input device: %d\n", error);
		वापस error;
	पूर्ण

	platक्रमm_set_drvdata(pdev, keypad);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांगpe_keypad_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sपंचांगpe_keypad *keypad = platक्रमm_get_drvdata(pdev);

	sपंचांगpe_disable(keypad->sपंचांगpe, STMPE_BLOCK_KEYPAD);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver sपंचांगpe_keypad_driver = अणु
	.driver.name	= "stmpe-keypad",
	.driver.owner	= THIS_MODULE,
	.probe		= sपंचांगpe_keypad_probe,
	.हटाओ		= sपंचांगpe_keypad_हटाओ,
पूर्ण;
module_platक्रमm_driver(sपंचांगpe_keypad_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("STMPExxxx keypad driver");
MODULE_AUTHOR("Rabin Vincent <rabin.vincent@stericsson.com>");
