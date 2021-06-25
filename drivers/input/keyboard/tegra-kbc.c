<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Keyboard class input driver क्रम the NVIDIA Tegra SoC पूर्णांकernal matrix
 * keyboard controller
 *
 * Copyright (c) 2009-2011, NVIDIA Corporation.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/input.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/slab.h>
#समावेश <linux/input/matrix_keypad.h>
#समावेश <linux/reset.h>
#समावेश <linux/err.h>

#घोषणा KBC_MAX_KPENT	8

/* Maximum row/column supported by Tegra KBC yet  is 16x8 */
#घोषणा KBC_MAX_GPIO	24
/* Maximum keys supported by Tegra KBC yet is 16 x 8*/
#घोषणा KBC_MAX_KEY	(16 * 8)

#घोषणा KBC_MAX_DEBOUNCE_CNT	0x3ffu

/* KBC row scan समय and delay क्रम beginning the row scan. */
#घोषणा KBC_ROW_SCAN_TIME	16
#घोषणा KBC_ROW_SCAN_DLY	5

/* KBC uses a 32KHz घड़ी so a cycle = 1/32Khz */
#घोषणा KBC_CYCLE_MS	32

/* KBC Registers */

/* KBC Control Register */
#घोषणा KBC_CONTROL_0	0x0
#घोषणा KBC_FIFO_TH_CNT_SHIFT(cnt)	(cnt << 14)
#घोषणा KBC_DEBOUNCE_CNT_SHIFT(cnt)	(cnt << 4)
#घोषणा KBC_CONTROL_FIFO_CNT_INT_EN	(1 << 3)
#घोषणा KBC_CONTROL_KEYPRESS_INT_EN	(1 << 1)
#घोषणा KBC_CONTROL_KBC_EN		(1 << 0)

/* KBC Interrupt Register */
#घोषणा KBC_INT_0	0x4
#घोषणा KBC_INT_FIFO_CNT_INT_STATUS	(1 << 2)
#घोषणा KBC_INT_KEYPRESS_INT_STATUS	(1 << 0)

#घोषणा KBC_ROW_CFG0_0	0x8
#घोषणा KBC_COL_CFG0_0	0x18
#घोषणा KBC_TO_CNT_0	0x24
#घोषणा KBC_INIT_DLY_0	0x28
#घोषणा KBC_RPT_DLY_0	0x2c
#घोषणा KBC_KP_ENT0_0	0x30
#घोषणा KBC_KP_ENT1_0	0x34
#घोषणा KBC_ROW0_MASK_0	0x38

#घोषणा KBC_ROW_SHIFT	3

क्रमागत tegra_pin_type अणु
	PIN_CFG_IGNORE,
	PIN_CFG_COL,
	PIN_CFG_ROW,
पूर्ण;

/* Tegra KBC hw support */
काष्ठा tegra_kbc_hw_support अणु
	पूर्णांक max_rows;
	पूर्णांक max_columns;
पूर्ण;

काष्ठा tegra_kbc_pin_cfg अणु
	क्रमागत tegra_pin_type type;
	अचिन्हित अक्षर num;
पूर्ण;

काष्ठा tegra_kbc अणु
	काष्ठा device *dev;
	अचिन्हित पूर्णांक debounce_cnt;
	अचिन्हित पूर्णांक repeat_cnt;
	काष्ठा tegra_kbc_pin_cfg pin_cfg[KBC_MAX_GPIO];
	स्थिर काष्ठा matrix_keymap_data *keymap_data;
	bool wakeup;
	व्योम __iomem *mmio;
	काष्ठा input_dev *idev;
	पूर्णांक irq;
	spinlock_t lock;
	अचिन्हित पूर्णांक repoll_dly;
	अचिन्हित दीर्घ cp_dly_jअगरfies;
	अचिन्हित पूर्णांक cp_to_wkup_dly;
	bool use_fn_map;
	bool use_ghost_filter;
	bool keypress_caused_wake;
	अचिन्हित लघु keycode[KBC_MAX_KEY * 2];
	अचिन्हित लघु current_keys[KBC_MAX_KPENT];
	अचिन्हित पूर्णांक num_pressed_keys;
	u32 wakeup_key;
	काष्ठा समयr_list समयr;
	काष्ठा clk *clk;
	काष्ठा reset_control *rst;
	स्थिर काष्ठा tegra_kbc_hw_support *hw_support;
	पूर्णांक max_keys;
	पूर्णांक num_rows_and_columns;
पूर्ण;

अटल व्योम tegra_kbc_report_released_keys(काष्ठा input_dev *input,
					   अचिन्हित लघु old_keycodes[],
					   अचिन्हित पूर्णांक old_num_keys,
					   अचिन्हित लघु new_keycodes[],
					   अचिन्हित पूर्णांक new_num_keys)
अणु
	अचिन्हित पूर्णांक i, j;

	क्रम (i = 0; i < old_num_keys; i++) अणु
		क्रम (j = 0; j < new_num_keys; j++)
			अगर (old_keycodes[i] == new_keycodes[j])
				अवरोध;

		अगर (j == new_num_keys)
			input_report_key(input, old_keycodes[i], 0);
	पूर्ण
पूर्ण

अटल व्योम tegra_kbc_report_pressed_keys(काष्ठा input_dev *input,
					  अचिन्हित अक्षर scancodes[],
					  अचिन्हित लघु keycodes[],
					  अचिन्हित पूर्णांक num_pressed_keys)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < num_pressed_keys; i++) अणु
		input_event(input, EV_MSC, MSC_SCAN, scancodes[i]);
		input_report_key(input, keycodes[i], 1);
	पूर्ण
पूर्ण

अटल व्योम tegra_kbc_report_keys(काष्ठा tegra_kbc *kbc)
अणु
	अचिन्हित अक्षर scancodes[KBC_MAX_KPENT];
	अचिन्हित लघु keycodes[KBC_MAX_KPENT];
	u32 val = 0;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक num_करोwn = 0;
	bool fn_keypress = false;
	bool key_in_same_row = false;
	bool key_in_same_col = false;

	क्रम (i = 0; i < KBC_MAX_KPENT; i++) अणु
		अगर ((i % 4) == 0)
			val = पढ़ोl(kbc->mmio + KBC_KP_ENT0_0 + i);

		अगर (val & 0x80) अणु
			अचिन्हित पूर्णांक col = val & 0x07;
			अचिन्हित पूर्णांक row = (val >> 3) & 0x0f;
			अचिन्हित अक्षर scancode =
				MATRIX_SCAN_CODE(row, col, KBC_ROW_SHIFT);

			scancodes[num_करोwn] = scancode;
			keycodes[num_करोwn] = kbc->keycode[scancode];
			/* If driver uses Fn map, करो not report the Fn key. */
			अगर ((keycodes[num_करोwn] == KEY_FN) && kbc->use_fn_map)
				fn_keypress = true;
			अन्यथा
				num_करोwn++;
		पूर्ण

		val >>= 8;
	पूर्ण

	/*
	 * Matrix keyboard designs are prone to keyboard ghosting.
	 * Ghosting occurs अगर there are 3 keys such that -
	 * any 2 of the 3 keys share a row, and any 2 of them share a column.
	 * If so ignore the key presses क्रम this iteration.
	 */
	अगर (kbc->use_ghost_filter && num_करोwn >= 3) अणु
		क्रम (i = 0; i < num_करोwn; i++) अणु
			अचिन्हित पूर्णांक j;
			u8 curr_col = scancodes[i] & 0x07;
			u8 curr_row = scancodes[i] >> KBC_ROW_SHIFT;

			/*
			 * Find 2 keys such that one key is in the same row
			 * and the other is in the same column as the i-th key.
			 */
			क्रम (j = i + 1; j < num_करोwn; j++) अणु
				u8 col = scancodes[j] & 0x07;
				u8 row = scancodes[j] >> KBC_ROW_SHIFT;

				अगर (col == curr_col)
					key_in_same_col = true;
				अगर (row == curr_row)
					key_in_same_row = true;
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * If the platक्रमm uses Fn keymaps, translate keys on a Fn keypress.
	 * Function keycodes are max_keys apart from the plain keycodes.
	 */
	अगर (fn_keypress) अणु
		क्रम (i = 0; i < num_करोwn; i++) अणु
			scancodes[i] += kbc->max_keys;
			keycodes[i] = kbc->keycode[scancodes[i]];
		पूर्ण
	पूर्ण

	/* Ignore the key presses क्रम this iteration? */
	अगर (key_in_same_col && key_in_same_row)
		वापस;

	tegra_kbc_report_released_keys(kbc->idev,
				       kbc->current_keys, kbc->num_pressed_keys,
				       keycodes, num_करोwn);
	tegra_kbc_report_pressed_keys(kbc->idev, scancodes, keycodes, num_करोwn);
	input_sync(kbc->idev);

	स_नकल(kbc->current_keys, keycodes, माप(kbc->current_keys));
	kbc->num_pressed_keys = num_करोwn;
पूर्ण

अटल व्योम tegra_kbc_set_fअगरo_पूर्णांकerrupt(काष्ठा tegra_kbc *kbc, bool enable)
अणु
	u32 val;

	val = पढ़ोl(kbc->mmio + KBC_CONTROL_0);
	अगर (enable)
		val |= KBC_CONTROL_FIFO_CNT_INT_EN;
	अन्यथा
		val &= ~KBC_CONTROL_FIFO_CNT_INT_EN;
	ग_लिखोl(val, kbc->mmio + KBC_CONTROL_0);
पूर्ण

अटल व्योम tegra_kbc_keypress_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा tegra_kbc *kbc = from_समयr(kbc, t, समयr);
	अचिन्हित दीर्घ flags;
	u32 val;
	अचिन्हित पूर्णांक i;

	spin_lock_irqsave(&kbc->lock, flags);

	val = (पढ़ोl(kbc->mmio + KBC_INT_0) >> 4) & 0xf;
	अगर (val) अणु
		अचिन्हित दीर्घ dly;

		tegra_kbc_report_keys(kbc);

		/*
		 * If more than one keys are pressed we need not रुको
		 * क्रम the repoll delay.
		 */
		dly = (val == 1) ? kbc->repoll_dly : 1;
		mod_समयr(&kbc->समयr, jअगरfies + msecs_to_jअगरfies(dly));
	पूर्ण अन्यथा अणु
		/* Release any pressed keys and निकास the polling loop */
		क्रम (i = 0; i < kbc->num_pressed_keys; i++)
			input_report_key(kbc->idev, kbc->current_keys[i], 0);
		input_sync(kbc->idev);

		kbc->num_pressed_keys = 0;

		/* All keys are released so enable the keypress पूर्णांकerrupt */
		tegra_kbc_set_fअगरo_पूर्णांकerrupt(kbc, true);
	पूर्ण

	spin_unlock_irqrestore(&kbc->lock, flags);
पूर्ण

अटल irqवापस_t tegra_kbc_isr(पूर्णांक irq, व्योम *args)
अणु
	काष्ठा tegra_kbc *kbc = args;
	अचिन्हित दीर्घ flags;
	u32 val;

	spin_lock_irqsave(&kbc->lock, flags);

	/*
	 * Quickly bail out & reenable पूर्णांकerrupts अगर the fअगरo threshold
	 * count पूर्णांकerrupt wasn't the पूर्णांकerrupt source
	 */
	val = पढ़ोl(kbc->mmio + KBC_INT_0);
	ग_लिखोl(val, kbc->mmio + KBC_INT_0);

	अगर (val & KBC_INT_FIFO_CNT_INT_STATUS) अणु
		/*
		 * Until all keys are released, defer further processing to
		 * the polling loop in tegra_kbc_keypress_समयr.
		 */
		tegra_kbc_set_fअगरo_पूर्णांकerrupt(kbc, false);
		mod_समयr(&kbc->समयr, jअगरfies + kbc->cp_dly_jअगरfies);
	पूर्ण अन्यथा अगर (val & KBC_INT_KEYPRESS_INT_STATUS) अणु
		/* We can be here only through प्रणाली resume path */
		kbc->keypress_caused_wake = true;
	पूर्ण

	spin_unlock_irqrestore(&kbc->lock, flags);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम tegra_kbc_setup_wakekeys(काष्ठा tegra_kbc *kbc, bool filter)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक rst_val;

	/* Either mask all keys or none. */
	rst_val = (filter && !kbc->wakeup) ? ~0 : 0;

	क्रम (i = 0; i < kbc->hw_support->max_rows; i++)
		ग_लिखोl(rst_val, kbc->mmio + KBC_ROW0_MASK_0 + i * 4);
पूर्ण

अटल व्योम tegra_kbc_config_pins(काष्ठा tegra_kbc *kbc)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < KBC_MAX_GPIO; i++) अणु
		u32 r_shft = 5 * (i % 6);
		u32 c_shft = 4 * (i % 8);
		u32 r_mask = 0x1f << r_shft;
		u32 c_mask = 0x0f << c_shft;
		u32 r_offs = (i / 6) * 4 + KBC_ROW_CFG0_0;
		u32 c_offs = (i / 8) * 4 + KBC_COL_CFG0_0;
		u32 row_cfg = पढ़ोl(kbc->mmio + r_offs);
		u32 col_cfg = पढ़ोl(kbc->mmio + c_offs);

		row_cfg &= ~r_mask;
		col_cfg &= ~c_mask;

		चयन (kbc->pin_cfg[i].type) अणु
		हाल PIN_CFG_ROW:
			row_cfg |= ((kbc->pin_cfg[i].num << 1) | 1) << r_shft;
			अवरोध;

		हाल PIN_CFG_COL:
			col_cfg |= ((kbc->pin_cfg[i].num << 1) | 1) << c_shft;
			अवरोध;

		हाल PIN_CFG_IGNORE:
			अवरोध;
		पूर्ण

		ग_लिखोl(row_cfg, kbc->mmio + r_offs);
		ग_लिखोl(col_cfg, kbc->mmio + c_offs);
	पूर्ण
पूर्ण

अटल पूर्णांक tegra_kbc_start(काष्ठा tegra_kbc *kbc)
अणु
	अचिन्हित पूर्णांक debounce_cnt;
	u32 val = 0;
	पूर्णांक ret;

	ret = clk_prepare_enable(kbc->clk);
	अगर (ret)
		वापस ret;

	/* Reset the KBC controller to clear all previous status.*/
	reset_control_निश्चित(kbc->rst);
	udelay(100);
	reset_control_deनिश्चित(kbc->rst);
	udelay(100);

	tegra_kbc_config_pins(kbc);
	tegra_kbc_setup_wakekeys(kbc, false);

	ग_लिखोl(kbc->repeat_cnt, kbc->mmio + KBC_RPT_DLY_0);

	/* Keyboard debounce count is maximum of 12 bits. */
	debounce_cnt = min(kbc->debounce_cnt, KBC_MAX_DEBOUNCE_CNT);
	val = KBC_DEBOUNCE_CNT_SHIFT(debounce_cnt);
	val |= KBC_FIFO_TH_CNT_SHIFT(1); /* set fअगरo पूर्णांकerrupt threshold to 1 */
	val |= KBC_CONTROL_FIFO_CNT_INT_EN;  /* पूर्णांकerrupt on FIFO threshold */
	val |= KBC_CONTROL_KBC_EN;     /* enable */
	ग_लिखोl(val, kbc->mmio + KBC_CONTROL_0);

	/*
	 * Compute the delay(ns) from पूर्णांकerrupt mode to continuous polling
	 * mode so the समयr routine is scheduled appropriately.
	 */
	val = पढ़ोl(kbc->mmio + KBC_INIT_DLY_0);
	kbc->cp_dly_jअगरfies = usecs_to_jअगरfies((val & 0xfffff) * 32);

	kbc->num_pressed_keys = 0;

	/*
	 * Atomically clear out any reमुख्यing entries in the key FIFO
	 * and enable keyboard पूर्णांकerrupts.
	 */
	जबतक (1) अणु
		val = पढ़ोl(kbc->mmio + KBC_INT_0);
		val >>= 4;
		अगर (!val)
			अवरोध;

		val = पढ़ोl(kbc->mmio + KBC_KP_ENT0_0);
		val = पढ़ोl(kbc->mmio + KBC_KP_ENT1_0);
	पूर्ण
	ग_लिखोl(0x7, kbc->mmio + KBC_INT_0);

	enable_irq(kbc->irq);

	वापस 0;
पूर्ण

अटल व्योम tegra_kbc_stop(काष्ठा tegra_kbc *kbc)
अणु
	अचिन्हित दीर्घ flags;
	u32 val;

	spin_lock_irqsave(&kbc->lock, flags);
	val = पढ़ोl(kbc->mmio + KBC_CONTROL_0);
	val &= ~1;
	ग_लिखोl(val, kbc->mmio + KBC_CONTROL_0);
	spin_unlock_irqrestore(&kbc->lock, flags);

	disable_irq(kbc->irq);
	del_समयr_sync(&kbc->समयr);

	clk_disable_unprepare(kbc->clk);
पूर्ण

अटल पूर्णांक tegra_kbc_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा tegra_kbc *kbc = input_get_drvdata(dev);

	वापस tegra_kbc_start(kbc);
पूर्ण

अटल व्योम tegra_kbc_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा tegra_kbc *kbc = input_get_drvdata(dev);

	वापस tegra_kbc_stop(kbc);
पूर्ण

अटल bool tegra_kbc_check_pin_cfg(स्थिर काष्ठा tegra_kbc *kbc,
					अचिन्हित पूर्णांक *num_rows)
अणु
	पूर्णांक i;

	*num_rows = 0;

	क्रम (i = 0; i < KBC_MAX_GPIO; i++) अणु
		स्थिर काष्ठा tegra_kbc_pin_cfg *pin_cfg = &kbc->pin_cfg[i];

		चयन (pin_cfg->type) अणु
		हाल PIN_CFG_ROW:
			अगर (pin_cfg->num >= kbc->hw_support->max_rows) अणु
				dev_err(kbc->dev,
					"pin_cfg[%d]: invalid row number %d\n",
					i, pin_cfg->num);
				वापस false;
			पूर्ण
			(*num_rows)++;
			अवरोध;

		हाल PIN_CFG_COL:
			अगर (pin_cfg->num >= kbc->hw_support->max_columns) अणु
				dev_err(kbc->dev,
					"pin_cfg[%d]: invalid column number %d\n",
					i, pin_cfg->num);
				वापस false;
			पूर्ण
			अवरोध;

		हाल PIN_CFG_IGNORE:
			अवरोध;

		शेष:
			dev_err(kbc->dev,
				"pin_cfg[%d]: invalid entry type %d\n",
				pin_cfg->type, pin_cfg->num);
			वापस false;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक tegra_kbc_parse_dt(काष्ठा tegra_kbc *kbc)
अणु
	काष्ठा device_node *np = kbc->dev->of_node;
	u32 prop;
	पूर्णांक i;
	u32 num_rows = 0;
	u32 num_cols = 0;
	u32 cols_cfg[KBC_MAX_GPIO];
	u32 rows_cfg[KBC_MAX_GPIO];
	पूर्णांक proplen;
	पूर्णांक ret;

	अगर (!of_property_पढ़ो_u32(np, "nvidia,debounce-delay-ms", &prop))
		kbc->debounce_cnt = prop;

	अगर (!of_property_पढ़ो_u32(np, "nvidia,repeat-delay-ms", &prop))
		kbc->repeat_cnt = prop;

	अगर (of_find_property(np, "nvidia,needs-ghost-filter", शून्य))
		kbc->use_ghost_filter = true;

	अगर (of_property_पढ़ो_bool(np, "wakeup-source") ||
	    of_property_पढ़ो_bool(np, "nvidia,wakeup-source")) /* legacy */
		kbc->wakeup = true;

	अगर (!of_get_property(np, "nvidia,kbc-row-pins", &proplen)) अणु
		dev_err(kbc->dev, "property nvidia,kbc-row-pins not found\n");
		वापस -ENOENT;
	पूर्ण
	num_rows = proplen / माप(u32);

	अगर (!of_get_property(np, "nvidia,kbc-col-pins", &proplen)) अणु
		dev_err(kbc->dev, "property nvidia,kbc-col-pins not found\n");
		वापस -ENOENT;
	पूर्ण
	num_cols = proplen / माप(u32);

	अगर (num_rows > kbc->hw_support->max_rows) अणु
		dev_err(kbc->dev,
			"Number of rows is more than supported by hardware\n");
		वापस -EINVAL;
	पूर्ण

	अगर (num_cols > kbc->hw_support->max_columns) अणु
		dev_err(kbc->dev,
			"Number of cols is more than supported by hardware\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!of_get_property(np, "linux,keymap", &proplen)) अणु
		dev_err(kbc->dev, "property linux,keymap not found\n");
		वापस -ENOENT;
	पूर्ण

	अगर (!num_rows || !num_cols || ((num_rows + num_cols) > KBC_MAX_GPIO)) अणु
		dev_err(kbc->dev,
			"keypad rows/columns not properly specified\n");
		वापस -EINVAL;
	पूर्ण

	/* Set all pins as non-configured */
	क्रम (i = 0; i < kbc->num_rows_and_columns; i++)
		kbc->pin_cfg[i].type = PIN_CFG_IGNORE;

	ret = of_property_पढ़ो_u32_array(np, "nvidia,kbc-row-pins",
				rows_cfg, num_rows);
	अगर (ret < 0) अणु
		dev_err(kbc->dev, "Rows configurations are not proper\n");
		वापस -EINVAL;
	पूर्ण

	ret = of_property_पढ़ो_u32_array(np, "nvidia,kbc-col-pins",
				cols_cfg, num_cols);
	अगर (ret < 0) अणु
		dev_err(kbc->dev, "Cols configurations are not proper\n");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < num_rows; i++) अणु
		kbc->pin_cfg[rows_cfg[i]].type = PIN_CFG_ROW;
		kbc->pin_cfg[rows_cfg[i]].num = i;
	पूर्ण

	क्रम (i = 0; i < num_cols; i++) अणु
		kbc->pin_cfg[cols_cfg[i]].type = PIN_CFG_COL;
		kbc->pin_cfg[cols_cfg[i]].num = i;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा tegra_kbc_hw_support tegra20_kbc_hw_support = अणु
	.max_rows	= 16,
	.max_columns	= 8,
पूर्ण;

अटल स्थिर काष्ठा tegra_kbc_hw_support tegra11_kbc_hw_support = अणु
	.max_rows	= 11,
	.max_columns	= 8,
पूर्ण;

अटल स्थिर काष्ठा of_device_id tegra_kbc_of_match[] = अणु
	अणु .compatible = "nvidia,tegra114-kbc", .data = &tegra11_kbc_hw_supportपूर्ण,
	अणु .compatible = "nvidia,tegra30-kbc", .data = &tegra20_kbc_hw_supportपूर्ण,
	अणु .compatible = "nvidia,tegra20-kbc", .data = &tegra20_kbc_hw_supportपूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, tegra_kbc_of_match);

अटल पूर्णांक tegra_kbc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra_kbc *kbc;
	काष्ठा resource *res;
	पूर्णांक err;
	पूर्णांक num_rows = 0;
	अचिन्हित पूर्णांक debounce_cnt;
	अचिन्हित पूर्णांक scan_समय_rows;
	अचिन्हित पूर्णांक keymap_rows;
	स्थिर काष्ठा of_device_id *match;

	match = of_match_device(tegra_kbc_of_match, &pdev->dev);

	kbc = devm_kzalloc(&pdev->dev, माप(*kbc), GFP_KERNEL);
	अगर (!kbc) अणु
		dev_err(&pdev->dev, "failed to alloc memory for kbc\n");
		वापस -ENOMEM;
	पूर्ण

	kbc->dev = &pdev->dev;
	kbc->hw_support = match->data;
	kbc->max_keys = kbc->hw_support->max_rows *
				kbc->hw_support->max_columns;
	kbc->num_rows_and_columns = kbc->hw_support->max_rows +
					kbc->hw_support->max_columns;
	keymap_rows = kbc->max_keys;
	spin_lock_init(&kbc->lock);

	err = tegra_kbc_parse_dt(kbc);
	अगर (err)
		वापस err;

	अगर (!tegra_kbc_check_pin_cfg(kbc, &num_rows))
		वापस -EINVAL;

	kbc->irq = platक्रमm_get_irq(pdev, 0);
	अगर (kbc->irq < 0)
		वापस -ENXIO;

	kbc->idev = devm_input_allocate_device(&pdev->dev);
	अगर (!kbc->idev) अणु
		dev_err(&pdev->dev, "failed to allocate input device\n");
		वापस -ENOMEM;
	पूर्ण

	समयr_setup(&kbc->समयr, tegra_kbc_keypress_समयr, 0);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	kbc->mmio = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(kbc->mmio))
		वापस PTR_ERR(kbc->mmio);

	kbc->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(kbc->clk)) अणु
		dev_err(&pdev->dev, "failed to get keyboard clock\n");
		वापस PTR_ERR(kbc->clk);
	पूर्ण

	kbc->rst = devm_reset_control_get(&pdev->dev, "kbc");
	अगर (IS_ERR(kbc->rst)) अणु
		dev_err(&pdev->dev, "failed to get keyboard reset\n");
		वापस PTR_ERR(kbc->rst);
	पूर्ण

	/*
	 * The समय delay between two consecutive पढ़ोs of the FIFO is
	 * the sum of the repeat समय and the समय taken क्रम scanning
	 * the rows. There is an additional delay beक्रमe the row scanning
	 * starts. The repoll delay is computed in milliseconds.
	 */
	debounce_cnt = min(kbc->debounce_cnt, KBC_MAX_DEBOUNCE_CNT);
	scan_समय_rows = (KBC_ROW_SCAN_TIME + debounce_cnt) * num_rows;
	kbc->repoll_dly = KBC_ROW_SCAN_DLY + scan_समय_rows + kbc->repeat_cnt;
	kbc->repoll_dly = DIV_ROUND_UP(kbc->repoll_dly, KBC_CYCLE_MS);

	kbc->idev->name = pdev->name;
	kbc->idev->id.bustype = BUS_HOST;
	kbc->idev->dev.parent = &pdev->dev;
	kbc->idev->खोलो = tegra_kbc_खोलो;
	kbc->idev->बंद = tegra_kbc_बंद;

	अगर (kbc->keymap_data && kbc->use_fn_map)
		keymap_rows *= 2;

	err = matrix_keypad_build_keymap(kbc->keymap_data, शून्य,
					 keymap_rows,
					 kbc->hw_support->max_columns,
					 kbc->keycode, kbc->idev);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to setup keymap\n");
		वापस err;
	पूर्ण

	__set_bit(EV_REP, kbc->idev->evbit);
	input_set_capability(kbc->idev, EV_MSC, MSC_SCAN);

	input_set_drvdata(kbc->idev, kbc);

	err = devm_request_irq(&pdev->dev, kbc->irq, tegra_kbc_isr,
			       IRQF_TRIGGER_HIGH | IRQF_NO_AUTOEN,
			       pdev->name, kbc);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to request keyboard IRQ\n");
		वापस err;
	पूर्ण

	err = input_रेजिस्टर_device(kbc->idev);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to register input device\n");
		वापस err;
	पूर्ण

	platक्रमm_set_drvdata(pdev, kbc);
	device_init_wakeup(&pdev->dev, kbc->wakeup);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल व्योम tegra_kbc_set_keypress_पूर्णांकerrupt(काष्ठा tegra_kbc *kbc, bool enable)
अणु
	u32 val;

	val = पढ़ोl(kbc->mmio + KBC_CONTROL_0);
	अगर (enable)
		val |= KBC_CONTROL_KEYPRESS_INT_EN;
	अन्यथा
		val &= ~KBC_CONTROL_KEYPRESS_INT_EN;
	ग_लिखोl(val, kbc->mmio + KBC_CONTROL_0);
पूर्ण

अटल पूर्णांक tegra_kbc_suspend(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा tegra_kbc *kbc = platक्रमm_get_drvdata(pdev);

	mutex_lock(&kbc->idev->mutex);
	अगर (device_may_wakeup(&pdev->dev)) अणु
		disable_irq(kbc->irq);
		del_समयr_sync(&kbc->समयr);
		tegra_kbc_set_fअगरo_पूर्णांकerrupt(kbc, false);

		/* Forcefully clear the पूर्णांकerrupt status */
		ग_लिखोl(0x7, kbc->mmio + KBC_INT_0);
		/*
		 * Store the previous resident समय of continuous polling mode.
		 * Force the keyboard पूर्णांकo पूर्णांकerrupt mode.
		 */
		kbc->cp_to_wkup_dly = पढ़ोl(kbc->mmio + KBC_TO_CNT_0);
		ग_लिखोl(0, kbc->mmio + KBC_TO_CNT_0);

		tegra_kbc_setup_wakekeys(kbc, true);
		msleep(30);

		kbc->keypress_caused_wake = false;
		/* Enable keypress पूर्णांकerrupt beक्रमe going पूर्णांकo suspend. */
		tegra_kbc_set_keypress_पूर्णांकerrupt(kbc, true);
		enable_irq(kbc->irq);
		enable_irq_wake(kbc->irq);
	पूर्ण अन्यथा अणु
		अगर (input_device_enabled(kbc->idev))
			tegra_kbc_stop(kbc);
	पूर्ण
	mutex_unlock(&kbc->idev->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_kbc_resume(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा tegra_kbc *kbc = platक्रमm_get_drvdata(pdev);
	पूर्णांक err = 0;

	mutex_lock(&kbc->idev->mutex);
	अगर (device_may_wakeup(&pdev->dev)) अणु
		disable_irq_wake(kbc->irq);
		tegra_kbc_setup_wakekeys(kbc, false);
		/* We will use fअगरo पूर्णांकerrupts क्रम key detection. */
		tegra_kbc_set_keypress_पूर्णांकerrupt(kbc, false);

		/* Restore the resident समय of continuous polling mode. */
		ग_लिखोl(kbc->cp_to_wkup_dly, kbc->mmio + KBC_TO_CNT_0);

		tegra_kbc_set_fअगरo_पूर्णांकerrupt(kbc, true);

		अगर (kbc->keypress_caused_wake && kbc->wakeup_key) अणु
			/*
			 * We can't report events directly from the ISR
			 * because समयkeeping is stopped when processing
			 * wakeup request and we get a nasty warning when
			 * we try to call करो_समय_लोofday() in evdev
			 * handler.
			 */
			input_report_key(kbc->idev, kbc->wakeup_key, 1);
			input_sync(kbc->idev);
			input_report_key(kbc->idev, kbc->wakeup_key, 0);
			input_sync(kbc->idev);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (input_device_enabled(kbc->idev))
			err = tegra_kbc_start(kbc);
	पूर्ण
	mutex_unlock(&kbc->idev->mutex);

	वापस err;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(tegra_kbc_pm_ops, tegra_kbc_suspend, tegra_kbc_resume);

अटल काष्ठा platक्रमm_driver tegra_kbc_driver = अणु
	.probe		= tegra_kbc_probe,
	.driver	= अणु
		.name	= "tegra-kbc",
		.pm	= &tegra_kbc_pm_ops,
		.of_match_table = tegra_kbc_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(tegra_kbc_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rakesh Iyer <riyer@nvidia.com>");
MODULE_DESCRIPTION("Tegra matrix keyboard controller driver");
MODULE_ALIAS("platform:tegra-kbc");
