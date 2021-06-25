<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/drivers/input/keyboard/pxa27x_keypad.c
 *
 * Driver क्रम the pxa27x matrix keyboard controller.
 *
 * Created:	Feb 22, 2007
 * Author:	Roकरोlfo Giometti <giometti@linux.it>
 *
 * Based on a previous implementations by Kevin O'Connor
 * <kevin_at_koconnor.net> and Alex Osborne <bobofकरोom@gmail.com> and
 * on some suggestions by Nicolas Pitre <nico@fluxnic.net>.
 */


#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/input.h>
#समावेश <linux/पन.स>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/input/matrix_keypad.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>

#समावेश <linux/platक्रमm_data/keypad-pxa27x.h>
/*
 * Keypad Controller रेजिस्टरs
 */
#घोषणा KPC             0x0000 /* Keypad Control रेजिस्टर */
#घोषणा KPDK            0x0008 /* Keypad Direct Key रेजिस्टर */
#घोषणा KPREC           0x0010 /* Keypad Rotary Encoder रेजिस्टर */
#घोषणा KPMK            0x0018 /* Keypad Matrix Key रेजिस्टर */
#घोषणा KPAS            0x0020 /* Keypad Automatic Scan रेजिस्टर */

/* Keypad Automatic Scan Multiple Key Presser रेजिस्टर 0-3 */
#घोषणा KPASMKP0        0x0028
#घोषणा KPASMKP1        0x0030
#घोषणा KPASMKP2        0x0038
#घोषणा KPASMKP3        0x0040
#घोषणा KPKDI           0x0048

/* bit definitions */
#घोषणा KPC_MKRN(n)	((((n) - 1) & 0x7) << 26) /* matrix key row number */
#घोषणा KPC_MKCN(n)	((((n) - 1) & 0x7) << 23) /* matrix key column number */
#घोषणा KPC_DKN(n)	((((n) - 1) & 0x7) << 6)  /* direct key number */

#घोषणा KPC_AS          (0x1 << 30)  /* Automatic Scan bit */
#घोषणा KPC_ASACT       (0x1 << 29)  /* Automatic Scan on Activity */
#घोषणा KPC_MI          (0x1 << 22)  /* Matrix पूर्णांकerrupt bit */
#घोषणा KPC_IMKP        (0x1 << 21)  /* Ignore Multiple Key Press */

#घोषणा KPC_MS(n)	(0x1 << (13 + (n)))	/* Matrix scan line 'n' */
#घोषणा KPC_MS_ALL      (0xff << 13)

#घोषणा KPC_ME          (0x1 << 12)  /* Matrix Keypad Enable */
#घोषणा KPC_MIE         (0x1 << 11)  /* Matrix Interrupt Enable */
#घोषणा KPC_DK_DEB_SEL	(0x1 <<  9)  /* Direct Keypad Debounce Select */
#घोषणा KPC_DI          (0x1 <<  5)  /* Direct key पूर्णांकerrupt bit */
#घोषणा KPC_RE_ZERO_DEB (0x1 <<  4)  /* Rotary Encoder Zero Debounce */
#घोषणा KPC_REE1        (0x1 <<  3)  /* Rotary Encoder1 Enable */
#घोषणा KPC_REE0        (0x1 <<  2)  /* Rotary Encoder0 Enable */
#घोषणा KPC_DE          (0x1 <<  1)  /* Direct Keypad Enable */
#घोषणा KPC_DIE         (0x1 <<  0)  /* Direct Keypad पूर्णांकerrupt Enable */

#घोषणा KPDK_DKP        (0x1 << 31)
#घोषणा KPDK_DK(n)	((n) & 0xff)

#घोषणा KPREC_OF1       (0x1 << 31)
#घोषणा kPREC_UF1       (0x1 << 30)
#घोषणा KPREC_OF0       (0x1 << 15)
#घोषणा KPREC_UF0       (0x1 << 14)

#घोषणा KPREC_RECOUNT0(n)	((n) & 0xff)
#घोषणा KPREC_RECOUNT1(n)	(((n) >> 16) & 0xff)

#घोषणा KPMK_MKP        (0x1 << 31)
#घोषणा KPAS_SO         (0x1 << 31)
#घोषणा KPASMKPx_SO     (0x1 << 31)

#घोषणा KPAS_MUKP(n)	(((n) >> 26) & 0x1f)
#घोषणा KPAS_RP(n)	(((n) >> 4) & 0xf)
#घोषणा KPAS_CP(n)	((n) & 0xf)

#घोषणा KPASMKP_MKC_MASK	(0xff)

#घोषणा keypad_पढ़ोl(off)	__raw_पढ़ोl(keypad->mmio_base + (off))
#घोषणा keypad_ग_लिखोl(off, v)	__raw_ग_लिखोl((v), keypad->mmio_base + (off))

#घोषणा MAX_MATRIX_KEY_NUM	(MAX_MATRIX_KEY_ROWS * MAX_MATRIX_KEY_COLS)
#घोषणा MAX_KEYPAD_KEYS		(MAX_MATRIX_KEY_NUM + MAX_सूचीECT_KEY_NUM)

काष्ठा pxa27x_keypad अणु
	स्थिर काष्ठा pxa27x_keypad_platक्रमm_data *pdata;

	काष्ठा clk *clk;
	काष्ठा input_dev *input_dev;
	व्योम __iomem *mmio_base;

	पूर्णांक irq;

	अचिन्हित लघु keycodes[MAX_KEYPAD_KEYS];
	पूर्णांक rotary_rel_code[2];

	अचिन्हित पूर्णांक row_shअगरt;

	/* state row bits of each column scan */
	uपूर्णांक32_t matrix_key_state[MAX_MATRIX_KEY_COLS];
	uपूर्णांक32_t direct_key_state;

	अचिन्हित पूर्णांक direct_key_mask;
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल पूर्णांक pxa27x_keypad_matrix_key_parse_dt(काष्ठा pxa27x_keypad *keypad,
				काष्ठा pxa27x_keypad_platक्रमm_data *pdata)
अणु
	काष्ठा input_dev *input_dev = keypad->input_dev;
	काष्ठा device *dev = input_dev->dev.parent;
	u32 rows, cols;
	पूर्णांक error;

	error = matrix_keypad_parse_properties(dev, &rows, &cols);
	अगर (error)
		वापस error;

	अगर (rows > MAX_MATRIX_KEY_ROWS || cols > MAX_MATRIX_KEY_COLS) अणु
		dev_err(dev, "rows or cols exceeds maximum value\n");
		वापस -EINVAL;
	पूर्ण

	pdata->matrix_key_rows = rows;
	pdata->matrix_key_cols = cols;

	error = matrix_keypad_build_keymap(शून्य, शून्य,
					   pdata->matrix_key_rows,
					   pdata->matrix_key_cols,
					   keypad->keycodes, input_dev);
	अगर (error)
		वापस error;

	वापस 0;
पूर्ण

अटल पूर्णांक pxa27x_keypad_direct_key_parse_dt(काष्ठा pxa27x_keypad *keypad,
				काष्ठा pxa27x_keypad_platक्रमm_data *pdata)
अणु
	काष्ठा input_dev *input_dev = keypad->input_dev;
	काष्ठा device *dev = input_dev->dev.parent;
	काष्ठा device_node *np = dev->of_node;
	स्थिर __be16 *prop;
	अचिन्हित लघु code;
	अचिन्हित पूर्णांक proplen, size;
	पूर्णांक i;
	पूर्णांक error;

	error = of_property_पढ़ो_u32(np, "marvell,direct-key-count",
				     &pdata->direct_key_num);
	अगर (error) अणु
		/*
		 * If करो not have marvel,direct-key-count defined,
		 * it means direct key is not supported.
		 */
		वापस error == -EINVAL ? 0 : error;
	पूर्ण

	error = of_property_पढ़ो_u32(np, "marvell,direct-key-mask",
				     &pdata->direct_key_mask);
	अगर (error) अणु
		अगर (error != -EINVAL)
			वापस error;

		/*
		 * If marvell,direct-key-mask is not defined, driver will use
		 * शेष value. Default value is set when configure the keypad.
		 */
		pdata->direct_key_mask = 0;
	पूर्ण

	pdata->direct_key_low_active = of_property_पढ़ो_bool(np,
					"marvell,direct-key-low-active");

	prop = of_get_property(np, "marvell,direct-key-map", &proplen);
	अगर (!prop)
		वापस -EINVAL;

	अगर (proplen % माप(u16))
		वापस -EINVAL;

	size = proplen / माप(u16);

	/* Only MAX_सूचीECT_KEY_NUM is accepted.*/
	अगर (size > MAX_सूचीECT_KEY_NUM)
		वापस -EINVAL;

	क्रम (i = 0; i < size; i++) अणु
		code = be16_to_cpup(prop + i);
		keypad->keycodes[MAX_MATRIX_KEY_NUM + i] = code;
		__set_bit(code, input_dev->keybit);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pxa27x_keypad_rotary_parse_dt(काष्ठा pxa27x_keypad *keypad,
				काष्ठा pxa27x_keypad_platक्रमm_data *pdata)
अणु
	स्थिर __be32 *prop;
	पूर्णांक i, relkey_ret;
	अचिन्हित पूर्णांक code, proplen;
	स्थिर अक्षर *rotaryname[2] = अणु
			"marvell,rotary0", "marvell,rotary1"पूर्ण;
	स्थिर अक्षर relkeyname[] = अणु"marvell,rotary-rel-key"पूर्ण;
	काष्ठा input_dev *input_dev = keypad->input_dev;
	काष्ठा device *dev = input_dev->dev.parent;
	काष्ठा device_node *np = dev->of_node;

	relkey_ret = of_property_पढ़ो_u32(np, relkeyname, &code);
	/* अगर can पढ़ो correct rotary key-code, we करो not need this. */
	अगर (relkey_ret == 0) अणु
		अचिन्हित लघु relcode;

		/* rotary0 taks lower half, rotary1 taks upper half. */
		relcode = code & 0xffff;
		pdata->rotary0_rel_code = (code & 0xffff);
		__set_bit(relcode, input_dev->relbit);

		relcode = code >> 16;
		pdata->rotary1_rel_code = relcode;
		__set_bit(relcode, input_dev->relbit);
	पूर्ण

	क्रम (i = 0; i < 2; i++) अणु
		prop = of_get_property(np, rotaryname[i], &proplen);
		/*
		 * If the prop is not set, it means keypad करोes not need
		 * initialize the rotaryX.
		 */
		अगर (!prop)
			जारी;

		code = be32_to_cpup(prop);
		/*
		 * Not all up/करोwn key code are valid.
		 * Now we depends on direct-rel-code.
		 */
		अगर ((!(code & 0xffff) || !(code >> 16)) && relkey_ret) अणु
			वापस relkey_ret;
		पूर्ण अन्यथा अणु
			अचिन्हित पूर्णांक n = MAX_MATRIX_KEY_NUM + (i << 1);
			अचिन्हित लघु keycode;

			keycode = code & 0xffff;
			keypad->keycodes[n] = keycode;
			__set_bit(keycode, input_dev->keybit);

			keycode = code >> 16;
			keypad->keycodes[n + 1] = keycode;
			__set_bit(keycode, input_dev->keybit);

			अगर (i == 0)
				pdata->rotary0_rel_code = -1;
			अन्यथा
				pdata->rotary1_rel_code = -1;
		पूर्ण
		अगर (i == 0)
			pdata->enable_rotary0 = 1;
		अन्यथा
			pdata->enable_rotary1 = 1;
	पूर्ण

	keypad->rotary_rel_code[0] = pdata->rotary0_rel_code;
	keypad->rotary_rel_code[1] = pdata->rotary1_rel_code;

	वापस 0;
पूर्ण

अटल पूर्णांक pxa27x_keypad_build_keycode_from_dt(काष्ठा pxa27x_keypad *keypad)
अणु
	काष्ठा input_dev *input_dev = keypad->input_dev;
	काष्ठा device *dev = input_dev->dev.parent;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा pxa27x_keypad_platक्रमm_data *pdata;
	पूर्णांक error;

	pdata = devm_kzalloc(dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata) अणु
		dev_err(dev, "failed to allocate memory for pdata\n");
		वापस -ENOMEM;
	पूर्ण

	error = pxa27x_keypad_matrix_key_parse_dt(keypad, pdata);
	अगर (error) अणु
		dev_err(dev, "failed to parse matrix key\n");
		वापस error;
	पूर्ण

	error = pxa27x_keypad_direct_key_parse_dt(keypad, pdata);
	अगर (error) अणु
		dev_err(dev, "failed to parse direct key\n");
		वापस error;
	पूर्ण

	error = pxa27x_keypad_rotary_parse_dt(keypad, pdata);
	अगर (error) अणु
		dev_err(dev, "failed to parse rotary key\n");
		वापस error;
	पूर्ण

	error = of_property_पढ़ो_u32(np, "marvell,debounce-interval",
				     &pdata->debounce_पूर्णांकerval);
	अगर (error) अणु
		dev_err(dev, "failed to parse debounce-interval\n");
		वापस error;
	पूर्ण

	/*
	 * The keycodes may not only includes matrix key but also the direct
	 * key or rotary key.
	 */
	input_dev->keycodemax = ARRAY_SIZE(keypad->keycodes);

	keypad->pdata = pdata;
	वापस 0;
पूर्ण

#अन्यथा

अटल पूर्णांक pxa27x_keypad_build_keycode_from_dt(काष्ठा pxa27x_keypad *keypad)
अणु
	dev_info(keypad->input_dev->dev.parent, "missing platform data\n");

	वापस -EINVAL;
पूर्ण

#पूर्ण_अगर

अटल पूर्णांक pxa27x_keypad_build_keycode(काष्ठा pxa27x_keypad *keypad)
अणु
	स्थिर काष्ठा pxa27x_keypad_platक्रमm_data *pdata = keypad->pdata;
	काष्ठा input_dev *input_dev = keypad->input_dev;
	अचिन्हित लघु keycode;
	पूर्णांक i;
	पूर्णांक error;

	error = matrix_keypad_build_keymap(pdata->matrix_keymap_data, शून्य,
					   pdata->matrix_key_rows,
					   pdata->matrix_key_cols,
					   keypad->keycodes, input_dev);
	अगर (error)
		वापस error;

	/*
	 * The keycodes may not only include matrix keys but also the direct
	 * or rotary keys.
	 */
	input_dev->keycodemax = ARRAY_SIZE(keypad->keycodes);

	/* For direct keys. */
	क्रम (i = 0; i < pdata->direct_key_num; i++) अणु
		keycode = pdata->direct_key_map[i];
		keypad->keycodes[MAX_MATRIX_KEY_NUM + i] = keycode;
		__set_bit(keycode, input_dev->keybit);
	पूर्ण

	अगर (pdata->enable_rotary0) अणु
		अगर (pdata->rotary0_up_key && pdata->rotary0_करोwn_key) अणु
			keycode = pdata->rotary0_up_key;
			keypad->keycodes[MAX_MATRIX_KEY_NUM + 0] = keycode;
			__set_bit(keycode, input_dev->keybit);

			keycode = pdata->rotary0_करोwn_key;
			keypad->keycodes[MAX_MATRIX_KEY_NUM + 1] = keycode;
			__set_bit(keycode, input_dev->keybit);

			keypad->rotary_rel_code[0] = -1;
		पूर्ण अन्यथा अणु
			keypad->rotary_rel_code[0] = pdata->rotary0_rel_code;
			__set_bit(pdata->rotary0_rel_code, input_dev->relbit);
		पूर्ण
	पूर्ण

	अगर (pdata->enable_rotary1) अणु
		अगर (pdata->rotary1_up_key && pdata->rotary1_करोwn_key) अणु
			keycode = pdata->rotary1_up_key;
			keypad->keycodes[MAX_MATRIX_KEY_NUM + 2] = keycode;
			__set_bit(keycode, input_dev->keybit);

			keycode = pdata->rotary1_करोwn_key;
			keypad->keycodes[MAX_MATRIX_KEY_NUM + 3] = keycode;
			__set_bit(keycode, input_dev->keybit);

			keypad->rotary_rel_code[1] = -1;
		पूर्ण अन्यथा अणु
			keypad->rotary_rel_code[1] = pdata->rotary1_rel_code;
			__set_bit(pdata->rotary1_rel_code, input_dev->relbit);
		पूर्ण
	पूर्ण

	__clear_bit(KEY_RESERVED, input_dev->keybit);

	वापस 0;
पूर्ण

अटल व्योम pxa27x_keypad_scan_matrix(काष्ठा pxa27x_keypad *keypad)
अणु
	स्थिर काष्ठा pxa27x_keypad_platक्रमm_data *pdata = keypad->pdata;
	काष्ठा input_dev *input_dev = keypad->input_dev;
	पूर्णांक row, col, num_keys_pressed = 0;
	uपूर्णांक32_t new_state[MAX_MATRIX_KEY_COLS];
	uपूर्णांक32_t kpas = keypad_पढ़ोl(KPAS);

	num_keys_pressed = KPAS_MUKP(kpas);

	स_रखो(new_state, 0, माप(new_state));

	अगर (num_keys_pressed == 0)
		जाओ scan;

	अगर (num_keys_pressed == 1) अणु
		col = KPAS_CP(kpas);
		row = KPAS_RP(kpas);

		/* अगर invalid row/col, treat as no key pressed */
		अगर (col >= pdata->matrix_key_cols ||
		    row >= pdata->matrix_key_rows)
			जाओ scan;

		new_state[col] = (1 << row);
		जाओ scan;
	पूर्ण

	अगर (num_keys_pressed > 1) अणु
		uपूर्णांक32_t kpयंत्रkp0 = keypad_पढ़ोl(KPASMKP0);
		uपूर्णांक32_t kpयंत्रkp1 = keypad_पढ़ोl(KPASMKP1);
		uपूर्णांक32_t kpयंत्रkp2 = keypad_पढ़ोl(KPASMKP2);
		uपूर्णांक32_t kpयंत्रkp3 = keypad_पढ़ोl(KPASMKP3);

		new_state[0] = kpयंत्रkp0 & KPASMKP_MKC_MASK;
		new_state[1] = (kpयंत्रkp0 >> 16) & KPASMKP_MKC_MASK;
		new_state[2] = kpयंत्रkp1 & KPASMKP_MKC_MASK;
		new_state[3] = (kpयंत्रkp1 >> 16) & KPASMKP_MKC_MASK;
		new_state[4] = kpयंत्रkp2 & KPASMKP_MKC_MASK;
		new_state[5] = (kpयंत्रkp2 >> 16) & KPASMKP_MKC_MASK;
		new_state[6] = kpयंत्रkp3 & KPASMKP_MKC_MASK;
		new_state[7] = (kpयंत्रkp3 >> 16) & KPASMKP_MKC_MASK;
	पूर्ण
scan:
	क्रम (col = 0; col < pdata->matrix_key_cols; col++) अणु
		uपूर्णांक32_t bits_changed;
		पूर्णांक code;

		bits_changed = keypad->matrix_key_state[col] ^ new_state[col];
		अगर (bits_changed == 0)
			जारी;

		क्रम (row = 0; row < pdata->matrix_key_rows; row++) अणु
			अगर ((bits_changed & (1 << row)) == 0)
				जारी;

			code = MATRIX_SCAN_CODE(row, col, keypad->row_shअगरt);

			input_event(input_dev, EV_MSC, MSC_SCAN, code);
			input_report_key(input_dev, keypad->keycodes[code],
					 new_state[col] & (1 << row));
		पूर्ण
	पूर्ण
	input_sync(input_dev);
	स_नकल(keypad->matrix_key_state, new_state, माप(new_state));
पूर्ण

#घोषणा DEFAULT_KPREC	(0x007f007f)

अटल अंतरभूत पूर्णांक rotary_delta(uपूर्णांक32_t kprec)
अणु
	अगर (kprec & KPREC_OF0)
		वापस (kprec & 0xff) + 0x7f;
	अन्यथा अगर (kprec & KPREC_UF0)
		वापस (kprec & 0xff) - 0x7f - 0xff;
	अन्यथा
		वापस (kprec & 0xff) - 0x7f;
पूर्ण

अटल व्योम report_rotary_event(काष्ठा pxa27x_keypad *keypad, पूर्णांक r, पूर्णांक delta)
अणु
	काष्ठा input_dev *dev = keypad->input_dev;

	अगर (delta == 0)
		वापस;

	अगर (keypad->rotary_rel_code[r] == -1) अणु
		पूर्णांक code = MAX_MATRIX_KEY_NUM + 2 * r + (delta > 0 ? 0 : 1);
		अचिन्हित अक्षर keycode = keypad->keycodes[code];

		/* simulate a press-n-release */
		input_event(dev, EV_MSC, MSC_SCAN, code);
		input_report_key(dev, keycode, 1);
		input_sync(dev);
		input_event(dev, EV_MSC, MSC_SCAN, code);
		input_report_key(dev, keycode, 0);
		input_sync(dev);
	पूर्ण अन्यथा अणु
		input_report_rel(dev, keypad->rotary_rel_code[r], delta);
		input_sync(dev);
	पूर्ण
पूर्ण

अटल व्योम pxa27x_keypad_scan_rotary(काष्ठा pxa27x_keypad *keypad)
अणु
	स्थिर काष्ठा pxa27x_keypad_platक्रमm_data *pdata = keypad->pdata;
	uपूर्णांक32_t kprec;

	/* पढ़ो and reset to शेष count value */
	kprec = keypad_पढ़ोl(KPREC);
	keypad_ग_लिखोl(KPREC, DEFAULT_KPREC);

	अगर (pdata->enable_rotary0)
		report_rotary_event(keypad, 0, rotary_delta(kprec));

	अगर (pdata->enable_rotary1)
		report_rotary_event(keypad, 1, rotary_delta(kprec >> 16));
पूर्ण

अटल व्योम pxa27x_keypad_scan_direct(काष्ठा pxa27x_keypad *keypad)
अणु
	स्थिर काष्ठा pxa27x_keypad_platक्रमm_data *pdata = keypad->pdata;
	काष्ठा input_dev *input_dev = keypad->input_dev;
	अचिन्हित पूर्णांक new_state;
	uपूर्णांक32_t kpdk, bits_changed;
	पूर्णांक i;

	kpdk = keypad_पढ़ोl(KPDK);

	अगर (pdata->enable_rotary0 || pdata->enable_rotary1)
		pxa27x_keypad_scan_rotary(keypad);

	/*
	 * The KPDR_DK only output the key pin level, so it relates to board,
	 * and low level may be active.
	 */
	अगर (pdata->direct_key_low_active)
		new_state = ~KPDK_DK(kpdk) & keypad->direct_key_mask;
	अन्यथा
		new_state = KPDK_DK(kpdk) & keypad->direct_key_mask;

	bits_changed = keypad->direct_key_state ^ new_state;

	अगर (bits_changed == 0)
		वापस;

	क्रम (i = 0; i < pdata->direct_key_num; i++) अणु
		अगर (bits_changed & (1 << i)) अणु
			पूर्णांक code = MAX_MATRIX_KEY_NUM + i;

			input_event(input_dev, EV_MSC, MSC_SCAN, code);
			input_report_key(input_dev, keypad->keycodes[code],
					 new_state & (1 << i));
		पूर्ण
	पूर्ण
	input_sync(input_dev);
	keypad->direct_key_state = new_state;
पूर्ण

अटल व्योम clear_wakeup_event(काष्ठा pxa27x_keypad *keypad)
अणु
	स्थिर काष्ठा pxa27x_keypad_platक्रमm_data *pdata = keypad->pdata;

	अगर (pdata->clear_wakeup_event)
		(pdata->clear_wakeup_event)();
पूर्ण

अटल irqवापस_t pxa27x_keypad_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा pxa27x_keypad *keypad = dev_id;
	अचिन्हित दीर्घ kpc = keypad_पढ़ोl(KPC);

	clear_wakeup_event(keypad);

	अगर (kpc & KPC_DI)
		pxa27x_keypad_scan_direct(keypad);

	अगर (kpc & KPC_MI)
		pxa27x_keypad_scan_matrix(keypad);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम pxa27x_keypad_config(काष्ठा pxa27x_keypad *keypad)
अणु
	स्थिर काष्ठा pxa27x_keypad_platक्रमm_data *pdata = keypad->pdata;
	अचिन्हित पूर्णांक mask = 0, direct_key_num = 0;
	अचिन्हित दीर्घ kpc = 0;

	/* clear pending पूर्णांकerrupt bit */
	keypad_पढ़ोl(KPC);

	/* enable matrix keys with स्वतःmatic scan */
	अगर (pdata->matrix_key_rows && pdata->matrix_key_cols) अणु
		kpc |= KPC_ASACT | KPC_MIE | KPC_ME | KPC_MS_ALL;
		kpc |= KPC_MKRN(pdata->matrix_key_rows) |
		       KPC_MKCN(pdata->matrix_key_cols);
	पूर्ण

	/* enable rotary key, debounce पूर्णांकerval same as direct keys */
	अगर (pdata->enable_rotary0) अणु
		mask |= 0x03;
		direct_key_num = 2;
		kpc |= KPC_REE0;
	पूर्ण

	अगर (pdata->enable_rotary1) अणु
		mask |= 0x0c;
		direct_key_num = 4;
		kpc |= KPC_REE1;
	पूर्ण

	अगर (pdata->direct_key_num > direct_key_num)
		direct_key_num = pdata->direct_key_num;

	/*
	 * Direct keys usage may not start from KP_DKIN0, check the platfrom
	 * mask data to config the specअगरic.
	 */
	अगर (pdata->direct_key_mask)
		keypad->direct_key_mask = pdata->direct_key_mask;
	अन्यथा
		keypad->direct_key_mask = ((1 << direct_key_num) - 1) & ~mask;

	/* enable direct key */
	अगर (direct_key_num)
		kpc |= KPC_DE | KPC_DIE | KPC_DKN(direct_key_num);

	keypad_ग_लिखोl(KPC, kpc | KPC_RE_ZERO_DEB);
	keypad_ग_लिखोl(KPREC, DEFAULT_KPREC);
	keypad_ग_लिखोl(KPKDI, pdata->debounce_पूर्णांकerval);
पूर्ण

अटल पूर्णांक pxa27x_keypad_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा pxa27x_keypad *keypad = input_get_drvdata(dev);
	पूर्णांक ret;
	/* Enable unit घड़ी */
	ret = clk_prepare_enable(keypad->clk);
	अगर (ret)
		वापस ret;

	pxa27x_keypad_config(keypad);

	वापस 0;
पूर्ण

अटल व्योम pxa27x_keypad_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा pxa27x_keypad *keypad = input_get_drvdata(dev);

	/* Disable घड़ी unit */
	clk_disable_unprepare(keypad->clk);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक pxa27x_keypad_suspend(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा pxa27x_keypad *keypad = platक्रमm_get_drvdata(pdev);

	/*
	 * If the keypad is used a wake up source, घड़ी can not be disabled.
	 * Or it can not detect the key pressing.
	 */
	अगर (device_may_wakeup(&pdev->dev))
		enable_irq_wake(keypad->irq);
	अन्यथा
		clk_disable_unprepare(keypad->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक pxa27x_keypad_resume(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा pxa27x_keypad *keypad = platक्रमm_get_drvdata(pdev);
	काष्ठा input_dev *input_dev = keypad->input_dev;
	पूर्णांक ret = 0;

	/*
	 * If the keypad is used as wake up source, the घड़ी is not turned
	 * off. So करो not need configure it again.
	 */
	अगर (device_may_wakeup(&pdev->dev)) अणु
		disable_irq_wake(keypad->irq);
	पूर्ण अन्यथा अणु
		mutex_lock(&input_dev->mutex);

		अगर (input_device_enabled(input_dev)) अणु
			/* Enable unit घड़ी */
			ret = clk_prepare_enable(keypad->clk);
			अगर (!ret)
				pxa27x_keypad_config(keypad);
		पूर्ण

		mutex_unlock(&input_dev->mutex);
	पूर्ण

	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(pxa27x_keypad_pm_ops,
			 pxa27x_keypad_suspend, pxa27x_keypad_resume);


अटल पूर्णांक pxa27x_keypad_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा pxa27x_keypad_platक्रमm_data *pdata =
					dev_get_platdata(&pdev->dev);
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा pxa27x_keypad *keypad;
	काष्ठा input_dev *input_dev;
	काष्ठा resource *res;
	पूर्णांक irq, error;

	/* Driver need build keycode from device tree or pdata */
	अगर (!np && !pdata)
		वापस -EINVAL;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस -ENXIO;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (res == शून्य) अणु
		dev_err(&pdev->dev, "failed to get I/O memory\n");
		वापस -ENXIO;
	पूर्ण

	keypad = devm_kzalloc(&pdev->dev, माप(*keypad),
			      GFP_KERNEL);
	अगर (!keypad)
		वापस -ENOMEM;

	input_dev = devm_input_allocate_device(&pdev->dev);
	अगर (!input_dev)
		वापस -ENOMEM;

	keypad->pdata = pdata;
	keypad->input_dev = input_dev;
	keypad->irq = irq;

	keypad->mmio_base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(keypad->mmio_base))
		वापस PTR_ERR(keypad->mmio_base);

	keypad->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(keypad->clk)) अणु
		dev_err(&pdev->dev, "failed to get keypad clock\n");
		वापस PTR_ERR(keypad->clk);
	पूर्ण

	input_dev->name = pdev->name;
	input_dev->id.bustype = BUS_HOST;
	input_dev->खोलो = pxa27x_keypad_खोलो;
	input_dev->बंद = pxa27x_keypad_बंद;
	input_dev->dev.parent = &pdev->dev;

	input_dev->keycode = keypad->keycodes;
	input_dev->keycodesize = माप(keypad->keycodes[0]);
	input_dev->keycodemax = ARRAY_SIZE(keypad->keycodes);

	input_set_drvdata(input_dev, keypad);

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_REP);
	input_set_capability(input_dev, EV_MSC, MSC_SCAN);

	अगर (pdata) अणु
		error = pxa27x_keypad_build_keycode(keypad);
	पूर्ण अन्यथा अणु
		error = pxa27x_keypad_build_keycode_from_dt(keypad);
		/*
		 * Data that we get from DT resides in dynamically
		 * allocated memory so we need to update our pdata
		 * poपूर्णांकer.
		 */
		pdata = keypad->pdata;
	पूर्ण
	अगर (error) अणु
		dev_err(&pdev->dev, "failed to build keycode\n");
		वापस error;
	पूर्ण

	keypad->row_shअगरt = get_count_order(pdata->matrix_key_cols);

	अगर ((pdata->enable_rotary0 && keypad->rotary_rel_code[0] != -1) ||
	    (pdata->enable_rotary1 && keypad->rotary_rel_code[1] != -1)) अणु
		input_dev->evbit[0] |= BIT_MASK(EV_REL);
	पूर्ण

	error = devm_request_irq(&pdev->dev, irq, pxa27x_keypad_irq_handler,
				 0, pdev->name, keypad);
	अगर (error) अणु
		dev_err(&pdev->dev, "failed to request IRQ\n");
		वापस error;
	पूर्ण

	/* Register the input device */
	error = input_रेजिस्टर_device(input_dev);
	अगर (error) अणु
		dev_err(&pdev->dev, "failed to register input device\n");
		वापस error;
	पूर्ण

	platक्रमm_set_drvdata(pdev, keypad);
	device_init_wakeup(&pdev->dev, 1);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id pxa27x_keypad_dt_match[] = अणु
	अणु .compatible = "marvell,pxa27x-keypad" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, pxa27x_keypad_dt_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver pxa27x_keypad_driver = अणु
	.probe		= pxa27x_keypad_probe,
	.driver		= अणु
		.name	= "pxa27x-keypad",
		.of_match_table = of_match_ptr(pxa27x_keypad_dt_match),
		.pm	= &pxa27x_keypad_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(pxa27x_keypad_driver);

MODULE_DESCRIPTION("PXA27x Keypad Controller Driver");
MODULE_LICENSE("GPL");
/* work with hotplug and coldplug */
MODULE_ALIAS("platform:pxa27x-keypad");
