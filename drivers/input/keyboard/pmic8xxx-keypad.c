<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2009-2011, Code Aurora Forum. All rights reserved.
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/input.h>
#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>
#समावेश <linux/mutex.h>
#समावेश <linux/regmap.h>
#समावेश <linux/of.h>
#समावेश <linux/input/matrix_keypad.h>

#घोषणा PM8XXX_MAX_ROWS		18
#घोषणा PM8XXX_MAX_COLS		8
#घोषणा PM8XXX_ROW_SHIFT	3
#घोषणा PM8XXX_MATRIX_MAX_SIZE	(PM8XXX_MAX_ROWS * PM8XXX_MAX_COLS)

#घोषणा PM8XXX_MIN_ROWS		5
#घोषणा PM8XXX_MIN_COLS		5

#घोषणा MAX_SCAN_DELAY		128
#घोषणा MIN_SCAN_DELAY		1

/* in nanoseconds */
#घोषणा MAX_ROW_HOLD_DELAY	122000
#घोषणा MIN_ROW_HOLD_DELAY	30500

#घोषणा MAX_DEBOUNCE_TIME	20
#घोषणा MIN_DEBOUNCE_TIME	5

#घोषणा KEYP_CTRL			0x148

#घोषणा KEYP_CTRL_EVNTS			BIT(0)
#घोषणा KEYP_CTRL_EVNTS_MASK		0x3

#घोषणा KEYP_CTRL_SCAN_COLS_SHIFT	5
#घोषणा KEYP_CTRL_SCAN_COLS_MIN		5
#घोषणा KEYP_CTRL_SCAN_COLS_BITS	0x3

#घोषणा KEYP_CTRL_SCAN_ROWS_SHIFT	2
#घोषणा KEYP_CTRL_SCAN_ROWS_MIN		5
#घोषणा KEYP_CTRL_SCAN_ROWS_BITS	0x7

#घोषणा KEYP_CTRL_KEYP_EN		BIT(7)

#घोषणा KEYP_SCAN			0x149

#घोषणा KEYP_SCAN_READ_STATE		BIT(0)
#घोषणा KEYP_SCAN_DBOUNCE_SHIFT		1
#घोषणा KEYP_SCAN_PAUSE_SHIFT		3
#घोषणा KEYP_SCAN_ROW_HOLD_SHIFT	6

#घोषणा KEYP_TEST			0x14A

#घोषणा KEYP_TEST_CLEAR_RECENT_SCAN	BIT(6)
#घोषणा KEYP_TEST_CLEAR_OLD_SCAN	BIT(5)
#घोषणा KEYP_TEST_READ_RESET		BIT(4)
#घोषणा KEYP_TEST_DTEST_EN		BIT(3)
#घोषणा KEYP_TEST_ABORT_READ		BIT(0)

#घोषणा KEYP_TEST_DBG_SELECT_SHIFT	1

/* bits of these रेजिस्टरs represent
 * '0' क्रम key press
 * '1' क्रम key release
 */
#घोषणा KEYP_RECENT_DATA		0x14B
#घोषणा KEYP_OLD_DATA			0x14C

#घोषणा KEYP_CLOCK_FREQ			32768

/**
 * काष्ठा pmic8xxx_kp - पूर्णांकernal keypad data काष्ठाure
 * @num_cols: number of columns of keypad
 * @num_rows: number of row of keypad
 * @input: input device poपूर्णांकer क्रम keypad
 * @regmap: regmap handle
 * @key_sense_irq: key press/release irq number
 * @key_stuck_irq: key stuck notअगरication irq number
 * @keycodes: array to hold the key codes
 * @dev: parent device poपूर्णांकer
 * @keystate: present key press/release state
 * @stuckstate: present state when key stuck irq
 * @ctrl_reg: control रेजिस्टर value
 */
काष्ठा pmic8xxx_kp अणु
	अचिन्हित पूर्णांक num_rows;
	अचिन्हित पूर्णांक num_cols;
	काष्ठा input_dev *input;
	काष्ठा regmap *regmap;
	पूर्णांक key_sense_irq;
	पूर्णांक key_stuck_irq;

	अचिन्हित लघु keycodes[PM8XXX_MATRIX_MAX_SIZE];

	काष्ठा device *dev;
	u16 keystate[PM8XXX_MAX_ROWS];
	u16 stuckstate[PM8XXX_MAX_ROWS];

	u8 ctrl_reg;
पूर्ण;

अटल u8 pmic8xxx_col_state(काष्ठा pmic8xxx_kp *kp, u8 col)
अणु
	/* all keys pressed on that particular row? */
	अगर (col == 0x00)
		वापस 1 << kp->num_cols;
	अन्यथा
		वापस col & ((1 << kp->num_cols) - 1);
पूर्ण

/*
 * Synchronous पढ़ो protocol क्रम RevB0 onwards:
 *
 * 1. Write '1' to ReadState bit in KEYP_SCAN रेजिस्टर
 * 2. Wait 2*32KHz घड़ीs, so that HW can successfully enter पढ़ो mode
 *    synchronously
 * 3. Read rows in old array first अगर events are more than one
 * 4. Read rows in recent array
 * 5. Wait 4*32KHz घड़ीs
 * 6. Write '0' to ReadState bit of KEYP_SCAN रेजिस्टर so that hw can
 *    synchronously निकास पढ़ो mode.
 */
अटल पूर्णांक pmic8xxx_chk_sync_पढ़ो(काष्ठा pmic8xxx_kp *kp)
अणु
	पूर्णांक rc;
	अचिन्हित पूर्णांक scan_val;

	rc = regmap_पढ़ो(kp->regmap, KEYP_SCAN, &scan_val);
	अगर (rc < 0) अणु
		dev_err(kp->dev, "Error reading KEYP_SCAN reg, rc=%d\n", rc);
		वापस rc;
	पूर्ण

	scan_val |= 0x1;

	rc = regmap_ग_लिखो(kp->regmap, KEYP_SCAN, scan_val);
	अगर (rc < 0) अणु
		dev_err(kp->dev, "Error writing KEYP_SCAN reg, rc=%d\n", rc);
		वापस rc;
	पूर्ण

	/* 2 * 32KHz घड़ीs */
	udelay((2 * DIV_ROUND_UP(USEC_PER_SEC, KEYP_CLOCK_FREQ)) + 1);

	वापस rc;
पूर्ण

अटल पूर्णांक pmic8xxx_kp_पढ़ो_data(काष्ठा pmic8xxx_kp *kp, u16 *state,
					u16 data_reg, पूर्णांक पढ़ो_rows)
अणु
	पूर्णांक rc, row;
	अचिन्हित पूर्णांक val;

	क्रम (row = 0; row < पढ़ो_rows; row++) अणु
		rc = regmap_पढ़ो(kp->regmap, data_reg, &val);
		अगर (rc)
			वापस rc;
		dev_dbg(kp->dev, "%d = %d\n", row, val);
		state[row] = pmic8xxx_col_state(kp, val);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pmic8xxx_kp_पढ़ो_matrix(काष्ठा pmic8xxx_kp *kp, u16 *new_state,
					 u16 *old_state)
अणु
	पूर्णांक rc, पढ़ो_rows;
	अचिन्हित पूर्णांक scan_val;

	अगर (kp->num_rows < PM8XXX_MIN_ROWS)
		पढ़ो_rows = PM8XXX_MIN_ROWS;
	अन्यथा
		पढ़ो_rows = kp->num_rows;

	pmic8xxx_chk_sync_पढ़ो(kp);

	अगर (old_state) अणु
		rc = pmic8xxx_kp_पढ़ो_data(kp, old_state, KEYP_OLD_DATA,
						पढ़ो_rows);
		अगर (rc < 0) अणु
			dev_err(kp->dev,
				"Error reading KEYP_OLD_DATA, rc=%d\n", rc);
			वापस rc;
		पूर्ण
	पूर्ण

	rc = pmic8xxx_kp_पढ़ो_data(kp, new_state, KEYP_RECENT_DATA,
					 पढ़ो_rows);
	अगर (rc < 0) अणु
		dev_err(kp->dev,
			"Error reading KEYP_RECENT_DATA, rc=%d\n", rc);
		वापस rc;
	पूर्ण

	/* 4 * 32KHz घड़ीs */
	udelay((4 * DIV_ROUND_UP(USEC_PER_SEC, KEYP_CLOCK_FREQ)) + 1);

	rc = regmap_पढ़ो(kp->regmap, KEYP_SCAN, &scan_val);
	अगर (rc < 0) अणु
		dev_err(kp->dev, "Error reading KEYP_SCAN reg, rc=%d\n", rc);
		वापस rc;
	पूर्ण

	scan_val &= 0xFE;
	rc = regmap_ग_लिखो(kp->regmap, KEYP_SCAN, scan_val);
	अगर (rc < 0)
		dev_err(kp->dev, "Error writing KEYP_SCAN reg, rc=%d\n", rc);

	वापस rc;
पूर्ण

अटल व्योम __pmic8xxx_kp_scan_matrix(काष्ठा pmic8xxx_kp *kp, u16 *new_state,
					 u16 *old_state)
अणु
	पूर्णांक row, col, code;

	क्रम (row = 0; row < kp->num_rows; row++) अणु
		पूर्णांक bits_changed = new_state[row] ^ old_state[row];

		अगर (!bits_changed)
			जारी;

		क्रम (col = 0; col < kp->num_cols; col++) अणु
			अगर (!(bits_changed & (1 << col)))
				जारी;

			dev_dbg(kp->dev, "key [%d:%d] %s\n", row, col,
					!(new_state[row] & (1 << col)) ?
					"pressed" : "released");

			code = MATRIX_SCAN_CODE(row, col, PM8XXX_ROW_SHIFT);

			input_event(kp->input, EV_MSC, MSC_SCAN, code);
			input_report_key(kp->input,
					kp->keycodes[code],
					!(new_state[row] & (1 << col)));

			input_sync(kp->input);
		पूर्ण
	पूर्ण
पूर्ण

अटल bool pmic8xxx_detect_ghost_keys(काष्ठा pmic8xxx_kp *kp, u16 *new_state)
अणु
	पूर्णांक row, found_first = -1;
	u16 check, row_state;

	check = 0;
	क्रम (row = 0; row < kp->num_rows; row++) अणु
		row_state = (~new_state[row]) &
				 ((1 << kp->num_cols) - 1);

		अगर (hweight16(row_state) > 1) अणु
			अगर (found_first == -1)
				found_first = row;
			अगर (check & row_state) अणु
				dev_dbg(kp->dev, "detected ghost key on row[%d]"
					 " and row[%d]\n", found_first, row);
				वापस true;
			पूर्ण
		पूर्ण
		check |= row_state;
	पूर्ण
	वापस false;
पूर्ण

अटल पूर्णांक pmic8xxx_kp_scan_matrix(काष्ठा pmic8xxx_kp *kp, अचिन्हित पूर्णांक events)
अणु
	u16 new_state[PM8XXX_MAX_ROWS];
	u16 old_state[PM8XXX_MAX_ROWS];
	पूर्णांक rc;

	चयन (events) अणु
	हाल 0x1:
		rc = pmic8xxx_kp_पढ़ो_matrix(kp, new_state, शून्य);
		अगर (rc < 0)
			वापस rc;

		/* detecting ghost key is not an error */
		अगर (pmic8xxx_detect_ghost_keys(kp, new_state))
			वापस 0;
		__pmic8xxx_kp_scan_matrix(kp, new_state, kp->keystate);
		स_नकल(kp->keystate, new_state, माप(new_state));
	अवरोध;
	हाल 0x3: /* two events - eventcounter is gray-coded */
		rc = pmic8xxx_kp_पढ़ो_matrix(kp, new_state, old_state);
		अगर (rc < 0)
			वापस rc;

		__pmic8xxx_kp_scan_matrix(kp, old_state, kp->keystate);
		__pmic8xxx_kp_scan_matrix(kp, new_state, old_state);
		स_नकल(kp->keystate, new_state, माप(new_state));
	अवरोध;
	हाल 0x2:
		dev_dbg(kp->dev, "Some key events were lost\n");
		rc = pmic8xxx_kp_पढ़ो_matrix(kp, new_state, old_state);
		अगर (rc < 0)
			वापस rc;
		__pmic8xxx_kp_scan_matrix(kp, old_state, kp->keystate);
		__pmic8xxx_kp_scan_matrix(kp, new_state, old_state);
		स_नकल(kp->keystate, new_state, माप(new_state));
	अवरोध;
	शेष:
		rc = -EINVAL;
	पूर्ण
	वापस rc;
पूर्ण

/*
 * NOTE: We are पढ़ोing recent and old data रेजिस्टरs blindly
 * whenever key-stuck पूर्णांकerrupt happens, because events counter करोesn't
 * get updated when this पूर्णांकerrupt happens due to key stuck करोesn't get
 * considered as key state change.
 *
 * We are not using old data रेजिस्टर contents after they are being पढ़ो
 * because it might report the key which was pressed beक्रमe the key being stuck
 * as stuck key because it's pressed status is stored in the old data
 * रेजिस्टर.
 */
अटल irqवापस_t pmic8xxx_kp_stuck_irq(पूर्णांक irq, व्योम *data)
अणु
	u16 new_state[PM8XXX_MAX_ROWS];
	u16 old_state[PM8XXX_MAX_ROWS];
	पूर्णांक rc;
	काष्ठा pmic8xxx_kp *kp = data;

	rc = pmic8xxx_kp_पढ़ो_matrix(kp, new_state, old_state);
	अगर (rc < 0) अणु
		dev_err(kp->dev, "failed to read keypad matrix\n");
		वापस IRQ_HANDLED;
	पूर्ण

	__pmic8xxx_kp_scan_matrix(kp, new_state, kp->stuckstate);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t pmic8xxx_kp_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा pmic8xxx_kp *kp = data;
	अचिन्हित पूर्णांक ctrl_val, events;
	पूर्णांक rc;

	rc = regmap_पढ़ो(kp->regmap, KEYP_CTRL, &ctrl_val);
	अगर (rc < 0) अणु
		dev_err(kp->dev, "failed to read keyp_ctrl register\n");
		वापस IRQ_HANDLED;
	पूर्ण

	events = ctrl_val & KEYP_CTRL_EVNTS_MASK;

	rc = pmic8xxx_kp_scan_matrix(kp, events);
	अगर (rc < 0)
		dev_err(kp->dev, "failed to scan matrix\n");

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक pmic8xxx_kpd_init(काष्ठा pmic8xxx_kp *kp,
			     काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा device_node *of_node = pdev->dev.of_node;
	अचिन्हित पूर्णांक scan_delay_ms;
	अचिन्हित पूर्णांक row_hold_ns;
	अचिन्हित पूर्णांक debounce_ms;
	पूर्णांक bits, rc, cycles;
	u8 scan_val = 0, ctrl_val = 0;
	अटल स्थिर u8 row_bits[] = अणु
		0, 1, 2, 3, 4, 4, 5, 5, 6, 6, 6, 7, 7, 7,
	पूर्ण;

	/* Find column bits */
	अगर (kp->num_cols < KEYP_CTRL_SCAN_COLS_MIN)
		bits = 0;
	अन्यथा
		bits = kp->num_cols - KEYP_CTRL_SCAN_COLS_MIN;
	ctrl_val = (bits & KEYP_CTRL_SCAN_COLS_BITS) <<
		KEYP_CTRL_SCAN_COLS_SHIFT;

	/* Find row bits */
	अगर (kp->num_rows < KEYP_CTRL_SCAN_ROWS_MIN)
		bits = 0;
	अन्यथा
		bits = row_bits[kp->num_rows - KEYP_CTRL_SCAN_ROWS_MIN];

	ctrl_val |= (bits << KEYP_CTRL_SCAN_ROWS_SHIFT);

	rc = regmap_ग_लिखो(kp->regmap, KEYP_CTRL, ctrl_val);
	अगर (rc < 0) अणु
		dev_err(kp->dev, "Error writing KEYP_CTRL reg, rc=%d\n", rc);
		वापस rc;
	पूर्ण

	अगर (of_property_पढ़ो_u32(of_node, "scan-delay", &scan_delay_ms))
		scan_delay_ms = MIN_SCAN_DELAY;

	अगर (scan_delay_ms > MAX_SCAN_DELAY || scan_delay_ms < MIN_SCAN_DELAY ||
	    !is_घातer_of_2(scan_delay_ms)) अणु
		dev_err(&pdev->dev, "invalid keypad scan time supplied\n");
		वापस -EINVAL;
	पूर्ण

	अगर (of_property_पढ़ो_u32(of_node, "row-hold", &row_hold_ns))
		row_hold_ns = MIN_ROW_HOLD_DELAY;

	अगर (row_hold_ns > MAX_ROW_HOLD_DELAY ||
	    row_hold_ns < MIN_ROW_HOLD_DELAY ||
	    ((row_hold_ns % MIN_ROW_HOLD_DELAY) != 0)) अणु
		dev_err(&pdev->dev, "invalid keypad row hold time supplied\n");
		वापस -EINVAL;
	पूर्ण

	अगर (of_property_पढ़ो_u32(of_node, "debounce", &debounce_ms))
		debounce_ms = MIN_DEBOUNCE_TIME;

	अगर (((debounce_ms % 5) != 0) ||
	    debounce_ms > MAX_DEBOUNCE_TIME ||
	    debounce_ms < MIN_DEBOUNCE_TIME) अणु
		dev_err(&pdev->dev, "invalid debounce time supplied\n");
		वापस -EINVAL;
	पूर्ण

	bits = (debounce_ms / 5) - 1;

	scan_val |= (bits << KEYP_SCAN_DBOUNCE_SHIFT);

	bits = fls(scan_delay_ms) - 1;
	scan_val |= (bits << KEYP_SCAN_PAUSE_SHIFT);

	/* Row hold समय is a multiple of 32KHz cycles. */
	cycles = (row_hold_ns * KEYP_CLOCK_FREQ) / NSEC_PER_SEC;

	scan_val |= (cycles << KEYP_SCAN_ROW_HOLD_SHIFT);

	rc = regmap_ग_लिखो(kp->regmap, KEYP_SCAN, scan_val);
	अगर (rc)
		dev_err(kp->dev, "Error writing KEYP_SCAN reg, rc=%d\n", rc);

	वापस rc;

पूर्ण

अटल पूर्णांक pmic8xxx_kp_enable(काष्ठा pmic8xxx_kp *kp)
अणु
	पूर्णांक rc;

	kp->ctrl_reg |= KEYP_CTRL_KEYP_EN;

	rc = regmap_ग_लिखो(kp->regmap, KEYP_CTRL, kp->ctrl_reg);
	अगर (rc < 0)
		dev_err(kp->dev, "Error writing KEYP_CTRL reg, rc=%d\n", rc);

	वापस rc;
पूर्ण

अटल पूर्णांक pmic8xxx_kp_disable(काष्ठा pmic8xxx_kp *kp)
अणु
	पूर्णांक rc;

	kp->ctrl_reg &= ~KEYP_CTRL_KEYP_EN;

	rc = regmap_ग_लिखो(kp->regmap, KEYP_CTRL, kp->ctrl_reg);
	अगर (rc < 0)
		वापस rc;

	वापस rc;
पूर्ण

अटल पूर्णांक pmic8xxx_kp_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा pmic8xxx_kp *kp = input_get_drvdata(dev);

	वापस pmic8xxx_kp_enable(kp);
पूर्ण

अटल व्योम pmic8xxx_kp_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा pmic8xxx_kp *kp = input_get_drvdata(dev);

	pmic8xxx_kp_disable(kp);
पूर्ण

/*
 * keypad controller should be initialized in the following sequence
 * only, otherwise it might get पूर्णांकo FSM stuck state.
 *
 * - Initialize keypad control parameters, like no. of rows, columns,
 *   timing values etc.,
 * - configure rows and column gpios pull up/करोwn.
 * - set irq edge type.
 * - enable the keypad controller.
 */
अटल पूर्णांक pmic8xxx_kp_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	अचिन्हित पूर्णांक rows, cols;
	bool repeat;
	bool wakeup;
	काष्ठा pmic8xxx_kp *kp;
	पूर्णांक rc;
	अचिन्हित पूर्णांक ctrl_val;

	rc = matrix_keypad_parse_properties(&pdev->dev, &rows, &cols);
	अगर (rc)
		वापस rc;

	अगर (cols > PM8XXX_MAX_COLS || rows > PM8XXX_MAX_ROWS ||
	    cols < PM8XXX_MIN_COLS) अणु
		dev_err(&pdev->dev, "invalid platform data\n");
		वापस -EINVAL;
	पूर्ण

	repeat = !of_property_पढ़ो_bool(np, "linux,input-no-autorepeat");

	wakeup = of_property_पढ़ो_bool(np, "wakeup-source") ||
		 /* legacy name */
		 of_property_पढ़ो_bool(np, "linux,keypad-wakeup");

	kp = devm_kzalloc(&pdev->dev, माप(*kp), GFP_KERNEL);
	अगर (!kp)
		वापस -ENOMEM;

	kp->regmap = dev_get_regmap(pdev->dev.parent, शून्य);
	अगर (!kp->regmap)
		वापस -ENODEV;

	platक्रमm_set_drvdata(pdev, kp);

	kp->num_rows	= rows;
	kp->num_cols	= cols;
	kp->dev		= &pdev->dev;

	kp->input = devm_input_allocate_device(&pdev->dev);
	अगर (!kp->input) अणु
		dev_err(&pdev->dev, "unable to allocate input device\n");
		वापस -ENOMEM;
	पूर्ण

	kp->key_sense_irq = platक्रमm_get_irq(pdev, 0);
	अगर (kp->key_sense_irq < 0)
		वापस kp->key_sense_irq;

	kp->key_stuck_irq = platक्रमm_get_irq(pdev, 1);
	अगर (kp->key_stuck_irq < 0)
		वापस kp->key_stuck_irq;

	kp->input->name = "PMIC8XXX keypad";
	kp->input->phys = "pmic8xxx_keypad/input0";

	kp->input->id.bustype	= BUS_I2C;
	kp->input->id.version	= 0x0001;
	kp->input->id.product	= 0x0001;
	kp->input->id.venकरोr	= 0x0001;

	kp->input->खोलो		= pmic8xxx_kp_खोलो;
	kp->input->बंद	= pmic8xxx_kp_बंद;

	rc = matrix_keypad_build_keymap(शून्य, शून्य,
					PM8XXX_MAX_ROWS, PM8XXX_MAX_COLS,
					kp->keycodes, kp->input);
	अगर (rc) अणु
		dev_err(&pdev->dev, "failed to build keymap\n");
		वापस rc;
	पूर्ण

	अगर (repeat)
		__set_bit(EV_REP, kp->input->evbit);
	input_set_capability(kp->input, EV_MSC, MSC_SCAN);

	input_set_drvdata(kp->input, kp);

	/* initialize keypad state */
	स_रखो(kp->keystate, 0xff, माप(kp->keystate));
	स_रखो(kp->stuckstate, 0xff, माप(kp->stuckstate));

	rc = pmic8xxx_kpd_init(kp, pdev);
	अगर (rc < 0) अणु
		dev_err(&pdev->dev, "unable to initialize keypad controller\n");
		वापस rc;
	पूर्ण

	rc = devm_request_any_context_irq(&pdev->dev, kp->key_sense_irq,
			pmic8xxx_kp_irq, IRQF_TRIGGER_RISING, "pmic-keypad",
			kp);
	अगर (rc < 0) अणु
		dev_err(&pdev->dev, "failed to request keypad sense irq\n");
		वापस rc;
	पूर्ण

	rc = devm_request_any_context_irq(&pdev->dev, kp->key_stuck_irq,
			pmic8xxx_kp_stuck_irq, IRQF_TRIGGER_RISING,
			"pmic-keypad-stuck", kp);
	अगर (rc < 0) अणु
		dev_err(&pdev->dev, "failed to request keypad stuck irq\n");
		वापस rc;
	पूर्ण

	rc = regmap_पढ़ो(kp->regmap, KEYP_CTRL, &ctrl_val);
	अगर (rc < 0) अणु
		dev_err(&pdev->dev, "failed to read KEYP_CTRL register\n");
		वापस rc;
	पूर्ण

	kp->ctrl_reg = ctrl_val;

	rc = input_रेजिस्टर_device(kp->input);
	अगर (rc < 0) अणु
		dev_err(&pdev->dev, "unable to register keypad input device\n");
		वापस rc;
	पूर्ण

	device_init_wakeup(&pdev->dev, wakeup);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक pmic8xxx_kp_suspend(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा pmic8xxx_kp *kp = platक्रमm_get_drvdata(pdev);
	काष्ठा input_dev *input_dev = kp->input;

	अगर (device_may_wakeup(dev)) अणु
		enable_irq_wake(kp->key_sense_irq);
	पूर्ण अन्यथा अणु
		mutex_lock(&input_dev->mutex);

		अगर (input_device_enabled(input_dev))
			pmic8xxx_kp_disable(kp);

		mutex_unlock(&input_dev->mutex);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pmic8xxx_kp_resume(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा pmic8xxx_kp *kp = platक्रमm_get_drvdata(pdev);
	काष्ठा input_dev *input_dev = kp->input;

	अगर (device_may_wakeup(dev)) अणु
		disable_irq_wake(kp->key_sense_irq);
	पूर्ण अन्यथा अणु
		mutex_lock(&input_dev->mutex);

		अगर (input_device_enabled(input_dev))
			pmic8xxx_kp_enable(kp);

		mutex_unlock(&input_dev->mutex);
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(pm8xxx_kp_pm_ops,
			 pmic8xxx_kp_suspend, pmic8xxx_kp_resume);

अटल स्थिर काष्ठा of_device_id pm8xxx_match_table[] = अणु
	अणु .compatible = "qcom,pm8058-keypad" पूर्ण,
	अणु .compatible = "qcom,pm8921-keypad" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, pm8xxx_match_table);

अटल काष्ठा platक्रमm_driver pmic8xxx_kp_driver = अणु
	.probe		= pmic8xxx_kp_probe,
	.driver		= अणु
		.name = "pm8xxx-keypad",
		.pm = &pm8xxx_kp_pm_ops,
		.of_match_table = pm8xxx_match_table,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(pmic8xxx_kp_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("PMIC8XXX keypad driver");
MODULE_ALIAS("platform:pmic8xxx_keypad");
MODULE_AUTHOR("Trilok Soni <tsoni@codeaurora.org>");
