<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// ChromeOS EC keyboard driver
//
// Copyright (C) 2012 Google, Inc.
//
// This driver uses the ChromeOS EC byte-level message-based protocol क्रम
// communicating the keyboard state (which keys are pressed) from a keyboard EC
// to the AP over some bus (such as i2c, lpc, spi).  The EC करोes debouncing,
// but everything अन्यथा (including deghosting) is करोne here.  The मुख्य
// motivation क्रम this is to keep the EC firmware as simple as possible, since
// it cannot be easily upgraded and EC flash/IRAM space is relatively
// expensive.

#समावेश <linux/module.h>
#समावेश <linux/bitops.h>
#समावेश <linux/i2c.h>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysrq.h>
#समावेश <linux/input/matrix_keypad.h>
#समावेश <linux/platक्रमm_data/cros_ec_commands.h>
#समावेश <linux/platक्रमm_data/cros_ec_proto.h>

#समावेश <यंत्र/unaligned.h>

#घोषणा MAX_NUM_TOP_ROW_KEYS   15

/**
 * काष्ठा cros_ec_keyb - Structure representing EC keyboard device
 *
 * @rows: Number of rows in the keypad
 * @cols: Number of columns in the keypad
 * @row_shअगरt: log2 or number of rows, rounded up
 * @keymap_data: Matrix keymap data used to convert to keyscan values
 * @ghost_filter: true to enable the matrix key-ghosting filter
 * @valid_keys: biपंचांगap of existing keys क्रम each matrix column
 * @old_kb_state: biपंचांगap of keys pressed last scan
 * @dev: Device poपूर्णांकer
 * @ec: Top level ChromeOS device to use to talk to EC
 * @idev: The input device क्रम the matrix keys.
 * @bs_idev: The input device क्रम non-matrix buttons and चयनes (or शून्य).
 * @notअगरier: पूर्णांकerrupt event notअगरier क्रम transport devices
 * @function_row_physmap: An array of the encoded rows/columns क्रम the top
 *                        row function keys, in an order from left to right
 * @num_function_row_keys: The number of top row keys in a custom keyboard
 */
काष्ठा cros_ec_keyb अणु
	अचिन्हित पूर्णांक rows;
	अचिन्हित पूर्णांक cols;
	पूर्णांक row_shअगरt;
	स्थिर काष्ठा matrix_keymap_data *keymap_data;
	bool ghost_filter;
	uपूर्णांक8_t *valid_keys;
	uपूर्णांक8_t *old_kb_state;

	काष्ठा device *dev;
	काष्ठा cros_ec_device *ec;

	काष्ठा input_dev *idev;
	काष्ठा input_dev *bs_idev;
	काष्ठा notअगरier_block notअगरier;

	u16 function_row_physmap[MAX_NUM_TOP_ROW_KEYS];
	माप_प्रकार num_function_row_keys;
पूर्ण;

/**
 * काष्ठा cros_ec_bs_map - Mapping between Linux keycodes and EC button/चयन
 *	biपंचांगap #घोषणाs
 *
 * @ev_type: The type of the input event to generate (e.g., EV_KEY).
 * @code: A linux keycode
 * @bit: A #घोषणा like EC_MKBP_POWER_BUTTON or EC_MKBP_LID_OPEN
 * @inverted: If the #घोषणा and EV_SW have opposite meanings, this is true.
 *            Only applicable to चयनes.
 */
काष्ठा cros_ec_bs_map अणु
	अचिन्हित पूर्णांक ev_type;
	अचिन्हित पूर्णांक code;
	u8 bit;
	bool inverted;
पूर्ण;

/* cros_ec_keyb_bs - Map EC button/चयन #घोषणाs पूर्णांकo kernel ones */
अटल स्थिर काष्ठा cros_ec_bs_map cros_ec_keyb_bs[] = अणु
	/* Buttons */
	अणु
		.ev_type	= EV_KEY,
		.code		= KEY_POWER,
		.bit		= EC_MKBP_POWER_BUTTON,
	पूर्ण,
	अणु
		.ev_type	= EV_KEY,
		.code		= KEY_VOLUMEUP,
		.bit		= EC_MKBP_VOL_UP,
	पूर्ण,
	अणु
		.ev_type	= EV_KEY,
		.code		= KEY_VOLUMEDOWN,
		.bit		= EC_MKBP_VOL_DOWN,
	पूर्ण,

	/* Switches */
	अणु
		.ev_type	= EV_SW,
		.code		= SW_LID,
		.bit		= EC_MKBP_LID_OPEN,
		.inverted	= true,
	पूर्ण,
	अणु
		.ev_type	= EV_SW,
		.code		= SW_TABLET_MODE,
		.bit		= EC_MKBP_TABLET_MODE,
	पूर्ण,
पूर्ण;

/*
 * Returns true when there is at least one combination of pressed keys that
 * results in ghosting.
 */
अटल bool cros_ec_keyb_has_ghosting(काष्ठा cros_ec_keyb *ckdev, uपूर्णांक8_t *buf)
अणु
	पूर्णांक col1, col2, buf1, buf2;
	काष्ठा device *dev = ckdev->dev;
	uपूर्णांक8_t *valid_keys = ckdev->valid_keys;

	/*
	 * Ghosting happens अगर क्रम any pressed key X there are other keys
	 * pressed both in the same row and column of X as, क्रम instance,
	 * in the following diagram:
	 *
	 * . . Y . g .
	 * . . . . . .
	 * . . . . . .
	 * . . X . Z .
	 *
	 * In this हाल only X, Y, and Z are pressed, but g appears to be
	 * pressed too (see Wikipedia).
	 */
	क्रम (col1 = 0; col1 < ckdev->cols; col1++) अणु
		buf1 = buf[col1] & valid_keys[col1];
		क्रम (col2 = col1 + 1; col2 < ckdev->cols; col2++) अणु
			buf2 = buf[col2] & valid_keys[col2];
			अगर (hweight8(buf1 & buf2) > 1) अणु
				dev_dbg(dev, "ghost found at: B[%02d]:0x%02x & B[%02d]:0x%02x",
					col1, buf1, col2, buf2);
				वापस true;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण


/*
 * Compares the new keyboard state to the old one and produces key
 * press/release events accordingly.  The keyboard state is 13 bytes (one byte
 * per column)
 */
अटल व्योम cros_ec_keyb_process(काष्ठा cros_ec_keyb *ckdev,
			 uपूर्णांक8_t *kb_state, पूर्णांक len)
अणु
	काष्ठा input_dev *idev = ckdev->idev;
	पूर्णांक col, row;
	पूर्णांक new_state;
	पूर्णांक old_state;

	अगर (ckdev->ghost_filter && cros_ec_keyb_has_ghosting(ckdev, kb_state)) अणु
		/*
		 * Simple-minded solution: ignore this state. The obvious
		 * improvement is to only ignore changes to keys involved in
		 * the ghosting, but process the other changes.
		 */
		dev_dbg(ckdev->dev, "ghosting found\n");
		वापस;
	पूर्ण

	क्रम (col = 0; col < ckdev->cols; col++) अणु
		क्रम (row = 0; row < ckdev->rows; row++) अणु
			पूर्णांक pos = MATRIX_SCAN_CODE(row, col, ckdev->row_shअगरt);
			स्थिर अचिन्हित लघु *keycodes = idev->keycode;

			new_state = kb_state[col] & (1 << row);
			old_state = ckdev->old_kb_state[col] & (1 << row);
			अगर (new_state != old_state) अणु
				dev_dbg(ckdev->dev,
					"changed: [r%d c%d]: byte %02x\n",
					row, col, new_state);

				input_event(idev, EV_MSC, MSC_SCAN, pos);
				input_report_key(idev, keycodes[pos],
						 new_state);
			पूर्ण
		पूर्ण
		ckdev->old_kb_state[col] = kb_state[col];
	पूर्ण
	input_sync(ckdev->idev);
पूर्ण

/**
 * cros_ec_keyb_report_bs - Report non-matrixed buttons or चयनes
 *
 * This takes a biपंचांगap of buttons or चयनes from the EC and reports events,
 * syncing at the end.
 *
 * @ckdev: The keyboard device.
 * @ev_type: The input event type (e.g., EV_KEY).
 * @mask: A biपंचांगap of buttons from the EC.
 */
अटल व्योम cros_ec_keyb_report_bs(काष्ठा cros_ec_keyb *ckdev,
				   अचिन्हित पूर्णांक ev_type, u32 mask)

अणु
	काष्ठा input_dev *idev = ckdev->bs_idev;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(cros_ec_keyb_bs); i++) अणु
		स्थिर काष्ठा cros_ec_bs_map *map = &cros_ec_keyb_bs[i];

		अगर (map->ev_type != ev_type)
			जारी;

		input_event(idev, ev_type, map->code,
			    !!(mask & BIT(map->bit)) ^ map->inverted);
	पूर्ण
	input_sync(idev);
पूर्ण

अटल पूर्णांक cros_ec_keyb_work(काष्ठा notअगरier_block *nb,
			     अचिन्हित दीर्घ queued_during_suspend, व्योम *_notअगरy)
अणु
	काष्ठा cros_ec_keyb *ckdev = container_of(nb, काष्ठा cros_ec_keyb,
						  notअगरier);
	u32 val;
	अचिन्हित पूर्णांक ev_type;

	/*
	 * If not wake enabled, discard key state changes during
	 * suspend. Switches will be re-checked in
	 * cros_ec_keyb_resume() to be sure nothing is lost.
	 */
	अगर (queued_during_suspend && !device_may_wakeup(ckdev->dev))
		वापस NOTIFY_OK;

	चयन (ckdev->ec->event_data.event_type) अणु
	हाल EC_MKBP_EVENT_KEY_MATRIX:
		pm_wakeup_event(ckdev->dev, 0);

		अगर (ckdev->ec->event_size != ckdev->cols) अणु
			dev_err(ckdev->dev,
				"Discarded incomplete key matrix event.\n");
			वापस NOTIFY_OK;
		पूर्ण

		cros_ec_keyb_process(ckdev,
				     ckdev->ec->event_data.data.key_matrix,
				     ckdev->ec->event_size);
		अवरोध;

	हाल EC_MKBP_EVENT_SYSRQ:
		pm_wakeup_event(ckdev->dev, 0);

		val = get_unaligned_le32(&ckdev->ec->event_data.data.sysrq);
		dev_dbg(ckdev->dev, "sysrq code from EC: %#x\n", val);
		handle_sysrq(val);
		अवरोध;

	हाल EC_MKBP_EVENT_BUTTON:
	हाल EC_MKBP_EVENT_SWITCH:
		pm_wakeup_event(ckdev->dev, 0);

		अगर (ckdev->ec->event_data.event_type == EC_MKBP_EVENT_BUTTON) अणु
			val = get_unaligned_le32(
					&ckdev->ec->event_data.data.buttons);
			ev_type = EV_KEY;
		पूर्ण अन्यथा अणु
			val = get_unaligned_le32(
					&ckdev->ec->event_data.data.चयनes);
			ev_type = EV_SW;
		पूर्ण
		cros_ec_keyb_report_bs(ckdev, ev_type, val);
		अवरोध;

	शेष:
		वापस NOTIFY_DONE;
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

/*
 * Walks keycodes flipping bit in buffer COLUMNS deep where bit is ROW.  Used by
 * ghosting logic to ignore शून्य or भव keys.
 */
अटल व्योम cros_ec_keyb_compute_valid_keys(काष्ठा cros_ec_keyb *ckdev)
अणु
	पूर्णांक row, col;
	पूर्णांक row_shअगरt = ckdev->row_shअगरt;
	अचिन्हित लघु *keymap = ckdev->idev->keycode;
	अचिन्हित लघु code;

	BUG_ON(ckdev->idev->keycodesize != माप(*keymap));

	क्रम (col = 0; col < ckdev->cols; col++) अणु
		क्रम (row = 0; row < ckdev->rows; row++) अणु
			code = keymap[MATRIX_SCAN_CODE(row, col, row_shअगरt)];
			अगर (code && (code != KEY_BATTERY))
				ckdev->valid_keys[col] |= 1 << row;
		पूर्ण
		dev_dbg(ckdev->dev, "valid_keys[%02d] = 0x%02x\n",
			col, ckdev->valid_keys[col]);
	पूर्ण
पूर्ण

/**
 * cros_ec_keyb_info - Wrap the EC command EC_CMD_MKBP_INFO
 *
 * This wraps the EC_CMD_MKBP_INFO, असलtracting out all of the marshalling and
 * unmarshalling and dअगरferent version nonsense पूर्णांकo something simple.
 *
 * @ec_dev: The EC device
 * @info_type: Either EC_MKBP_INFO_SUPPORTED or EC_MKBP_INFO_CURRENT.
 * @event_type: Either EC_MKBP_EVENT_BUTTON or EC_MKBP_EVENT_SWITCH.  Actually
 *              in some हालs this could be EC_MKBP_EVENT_KEY_MATRIX or
 *              EC_MKBP_EVENT_HOST_EVENT too but we करोn't use in this driver.
 * @result: Where we'll store the result; a जोड़
 * @result_size: The size of the result.  Expected to be the size of one of
 *               the elements in the जोड़.
 *
 * Returns 0 अगर no error or -error upon error.
 */
अटल पूर्णांक cros_ec_keyb_info(काष्ठा cros_ec_device *ec_dev,
			     क्रमागत ec_mkbp_info_type info_type,
			     क्रमागत ec_mkbp_event event_type,
			     जोड़ ec_response_get_next_data *result,
			     माप_प्रकार result_size)
अणु
	काष्ठा ec_params_mkbp_info *params;
	काष्ठा cros_ec_command *msg;
	पूर्णांक ret;

	msg = kzalloc(माप(*msg) + max_t(माप_प्रकार, result_size,
					   माप(*params)), GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	msg->command = EC_CMD_MKBP_INFO;
	msg->version = 1;
	msg->outsize = माप(*params);
	msg->insize = result_size;
	params = (काष्ठा ec_params_mkbp_info *)msg->data;
	params->info_type = info_type;
	params->event_type = event_type;

	ret = cros_ec_cmd_xfer_status(ec_dev, msg);
	अगर (ret == -ENOPROTOOPT) अणु
		/* With older ECs we just वापस 0 क्रम everything */
		स_रखो(result, 0, result_size);
		ret = 0;
	पूर्ण अन्यथा अगर (ret < 0) अणु
		dev_warn(ec_dev->dev, "Transfer error %d/%d: %d\n",
			 (पूर्णांक)info_type, (पूर्णांक)event_type, ret);
	पूर्ण अन्यथा अगर (ret != result_size) अणु
		dev_warn(ec_dev->dev, "Wrong size %d/%d: %d != %zu\n",
			 (पूर्णांक)info_type, (पूर्णांक)event_type,
			 ret, result_size);
		ret = -EPROTO;
	पूर्ण अन्यथा अणु
		स_नकल(result, msg->data, result_size);
		ret = 0;
	पूर्ण

	kमुक्त(msg);

	वापस ret;
पूर्ण

/**
 * cros_ec_keyb_query_चयनes - Query the state of चयनes and report
 *
 * This will ask the EC about the current state of चयनes and report to the
 * kernel.  Note that we करोn't query क्रम buttons because they are more
 * transitory and we'll get an update on the next release / press.
 *
 * @ckdev: The keyboard device
 *
 * Returns 0 अगर no error or -error upon error.
 */
अटल पूर्णांक cros_ec_keyb_query_चयनes(काष्ठा cros_ec_keyb *ckdev)
अणु
	काष्ठा cros_ec_device *ec_dev = ckdev->ec;
	जोड़ ec_response_get_next_data event_data = अणुपूर्ण;
	पूर्णांक ret;

	ret = cros_ec_keyb_info(ec_dev, EC_MKBP_INFO_CURRENT,
				EC_MKBP_EVENT_SWITCH, &event_data,
				माप(event_data.चयनes));
	अगर (ret)
		वापस ret;

	cros_ec_keyb_report_bs(ckdev, EV_SW,
			       get_unaligned_le32(&event_data.चयनes));

	वापस 0;
पूर्ण

/**
 * cros_ec_keyb_resume - Resume the keyboard
 *
 * We use the resume notअगरication as a chance to query the EC क्रम चयनes.
 *
 * @dev: The keyboard device
 *
 * Returns 0 अगर no error or -error upon error.
 */
अटल __maybe_unused पूर्णांक cros_ec_keyb_resume(काष्ठा device *dev)
अणु
	काष्ठा cros_ec_keyb *ckdev = dev_get_drvdata(dev);

	अगर (ckdev->bs_idev)
		वापस cros_ec_keyb_query_चयनes(ckdev);

	वापस 0;
पूर्ण

/**
 * cros_ec_keyb_रेजिस्टर_bs - Register non-matrix buttons/चयनes
 *
 * Handles all the bits of the keyboard driver related to non-matrix buttons
 * and चयनes, including asking the EC about which are present and telling
 * the kernel to expect them.
 *
 * If this device has no support क्रम buttons and चयनes we'll वापस no error
 * but the ckdev->bs_idev will reमुख्य शून्य when this function निकासs.
 *
 * @ckdev: The keyboard device
 *
 * Returns 0 अगर no error or -error upon error.
 */
अटल पूर्णांक cros_ec_keyb_रेजिस्टर_bs(काष्ठा cros_ec_keyb *ckdev)
अणु
	काष्ठा cros_ec_device *ec_dev = ckdev->ec;
	काष्ठा device *dev = ckdev->dev;
	काष्ठा input_dev *idev;
	जोड़ ec_response_get_next_data event_data = अणुपूर्ण;
	स्थिर अक्षर *phys;
	u32 buttons;
	u32 चयनes;
	पूर्णांक ret;
	पूर्णांक i;

	ret = cros_ec_keyb_info(ec_dev, EC_MKBP_INFO_SUPPORTED,
				EC_MKBP_EVENT_BUTTON, &event_data,
				माप(event_data.buttons));
	अगर (ret)
		वापस ret;
	buttons = get_unaligned_le32(&event_data.buttons);

	ret = cros_ec_keyb_info(ec_dev, EC_MKBP_INFO_SUPPORTED,
				EC_MKBP_EVENT_SWITCH, &event_data,
				माप(event_data.चयनes));
	अगर (ret)
		वापस ret;
	चयनes = get_unaligned_le32(&event_data.चयनes);

	अगर (!buttons && !चयनes)
		वापस 0;

	/*
	 * We call the non-matrix buttons/चयनes 'input1', अगर present.
	 * Allocate phys beक्रमe input dev, to ensure correct tear-करोwn
	 * ordering.
	 */
	phys = devm_kaप्र_लिखो(dev, GFP_KERNEL, "%s/input1", ec_dev->phys_name);
	अगर (!phys)
		वापस -ENOMEM;

	idev = devm_input_allocate_device(dev);
	अगर (!idev)
		वापस -ENOMEM;

	idev->name = "cros_ec_buttons";
	idev->phys = phys;
	__set_bit(EV_REP, idev->evbit);

	idev->id.bustype = BUS_VIRTUAL;
	idev->id.version = 1;
	idev->id.product = 0;
	idev->dev.parent = dev;

	input_set_drvdata(idev, ckdev);
	ckdev->bs_idev = idev;

	क्रम (i = 0; i < ARRAY_SIZE(cros_ec_keyb_bs); i++) अणु
		स्थिर काष्ठा cros_ec_bs_map *map = &cros_ec_keyb_bs[i];

		अगर ((map->ev_type == EV_KEY && (buttons & BIT(map->bit))) ||
		    (map->ev_type == EV_SW && (चयनes & BIT(map->bit))))
			input_set_capability(idev, map->ev_type, map->code);
	पूर्ण

	ret = cros_ec_keyb_query_चयनes(ckdev);
	अगर (ret) अणु
		dev_err(dev, "cannot query switches\n");
		वापस ret;
	पूर्ण

	ret = input_रेजिस्टर_device(ckdev->bs_idev);
	अगर (ret) अणु
		dev_err(dev, "cannot register input device\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * cros_ec_keyb_रेजिस्टर_bs - Register matrix keys
 *
 * Handles all the bits of the keyboard driver related to matrix keys.
 *
 * @ckdev: The keyboard device
 *
 * Returns 0 अगर no error or -error upon error.
 */
अटल पूर्णांक cros_ec_keyb_रेजिस्टर_matrix(काष्ठा cros_ec_keyb *ckdev)
अणु
	काष्ठा cros_ec_device *ec_dev = ckdev->ec;
	काष्ठा device *dev = ckdev->dev;
	काष्ठा input_dev *idev;
	स्थिर अक्षर *phys;
	पूर्णांक err;
	काष्ठा property *prop;
	स्थिर __be32 *p;
	u16 *physmap;
	u32 key_pos;
	पूर्णांक row, col;

	err = matrix_keypad_parse_properties(dev, &ckdev->rows, &ckdev->cols);
	अगर (err)
		वापस err;

	ckdev->valid_keys = devm_kzalloc(dev, ckdev->cols, GFP_KERNEL);
	अगर (!ckdev->valid_keys)
		वापस -ENOMEM;

	ckdev->old_kb_state = devm_kzalloc(dev, ckdev->cols, GFP_KERNEL);
	अगर (!ckdev->old_kb_state)
		वापस -ENOMEM;

	/*
	 * We call the keyboard matrix 'input0'. Allocate phys beक्रमe input
	 * dev, to ensure correct tear-करोwn ordering.
	 */
	phys = devm_kaप्र_लिखो(dev, GFP_KERNEL, "%s/input0", ec_dev->phys_name);
	अगर (!phys)
		वापस -ENOMEM;

	idev = devm_input_allocate_device(dev);
	अगर (!idev)
		वापस -ENOMEM;

	idev->name = CROS_EC_DEV_NAME;
	idev->phys = phys;
	__set_bit(EV_REP, idev->evbit);

	idev->id.bustype = BUS_VIRTUAL;
	idev->id.version = 1;
	idev->id.product = 0;
	idev->dev.parent = dev;

	ckdev->ghost_filter = of_property_पढ़ो_bool(dev->of_node,
					"google,needs-ghost-filter");

	err = matrix_keypad_build_keymap(शून्य, शून्य, ckdev->rows, ckdev->cols,
					 शून्य, idev);
	अगर (err) अणु
		dev_err(dev, "cannot build key matrix\n");
		वापस err;
	पूर्ण

	ckdev->row_shअगरt = get_count_order(ckdev->cols);

	input_set_capability(idev, EV_MSC, MSC_SCAN);
	input_set_drvdata(idev, ckdev);
	ckdev->idev = idev;
	cros_ec_keyb_compute_valid_keys(ckdev);

	physmap = ckdev->function_row_physmap;
	of_property_क्रम_each_u32(dev->of_node, "function-row-physmap",
				 prop, p, key_pos) अणु
		अगर (ckdev->num_function_row_keys == MAX_NUM_TOP_ROW_KEYS) अणु
			dev_warn(dev, "Only support up to %d top row keys\n",
				 MAX_NUM_TOP_ROW_KEYS);
			अवरोध;
		पूर्ण
		row = KEY_ROW(key_pos);
		col = KEY_COL(key_pos);
		*physmap = MATRIX_SCAN_CODE(row, col, ckdev->row_shअगरt);
		physmap++;
		ckdev->num_function_row_keys++;
	पूर्ण

	err = input_रेजिस्टर_device(ckdev->idev);
	अगर (err) अणु
		dev_err(dev, "cannot register input device\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार function_row_physmap_show(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 अक्षर *buf)
अणु
	sमाप_प्रकार size = 0;
	पूर्णांक i;
	काष्ठा cros_ec_keyb *ckdev = dev_get_drvdata(dev);
	u16 *physmap = ckdev->function_row_physmap;

	क्रम (i = 0; i < ckdev->num_function_row_keys; i++)
		size += scnम_लिखो(buf + size, PAGE_SIZE - size,
				  "%s%02X", size ? " " : "", physmap[i]);
	अगर (size)
		size += scnम_लिखो(buf + size, PAGE_SIZE - size, "\n");

	वापस size;
पूर्ण

अटल DEVICE_ATTR_RO(function_row_physmap);

अटल काष्ठा attribute *cros_ec_keyb_attrs[] = अणु
	&dev_attr_function_row_physmap.attr,
	शून्य,
पूर्ण;

अटल umode_t cros_ec_keyb_attr_is_visible(काष्ठा kobject *kobj,
					    काष्ठा attribute *attr,
					    पूर्णांक n)
अणु
	काष्ठा device *dev = container_of(kobj, काष्ठा device, kobj);
	काष्ठा cros_ec_keyb *ckdev = dev_get_drvdata(dev);

	अगर (attr == &dev_attr_function_row_physmap.attr &&
	    !ckdev->num_function_row_keys)
		वापस 0;

	वापस attr->mode;
पूर्ण

अटल स्थिर काष्ठा attribute_group cros_ec_keyb_attr_group = अणु
	.is_visible = cros_ec_keyb_attr_is_visible,
	.attrs = cros_ec_keyb_attrs,
पूर्ण;


अटल पूर्णांक cros_ec_keyb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cros_ec_device *ec = dev_get_drvdata(pdev->dev.parent);
	काष्ठा device *dev = &pdev->dev;
	काष्ठा cros_ec_keyb *ckdev;
	पूर्णांक err;

	अगर (!dev->of_node)
		वापस -ENODEV;

	ckdev = devm_kzalloc(dev, माप(*ckdev), GFP_KERNEL);
	अगर (!ckdev)
		वापस -ENOMEM;

	ckdev->ec = ec;
	ckdev->dev = dev;
	dev_set_drvdata(dev, ckdev);

	err = cros_ec_keyb_रेजिस्टर_matrix(ckdev);
	अगर (err) अणु
		dev_err(dev, "cannot register matrix inputs: %d\n", err);
		वापस err;
	पूर्ण

	err = cros_ec_keyb_रेजिस्टर_bs(ckdev);
	अगर (err) अणु
		dev_err(dev, "cannot register non-matrix inputs: %d\n", err);
		वापस err;
	पूर्ण

	err = devm_device_add_group(dev, &cros_ec_keyb_attr_group);
	अगर (err) अणु
		dev_err(dev, "failed to create attributes. err=%d\n", err);
		वापस err;
	पूर्ण

	ckdev->notअगरier.notअगरier_call = cros_ec_keyb_work;
	err = blocking_notअगरier_chain_रेजिस्टर(&ckdev->ec->event_notअगरier,
					       &ckdev->notअगरier);
	अगर (err) अणु
		dev_err(dev, "cannot register notifier: %d\n", err);
		वापस err;
	पूर्ण

	device_init_wakeup(ckdev->dev, true);
	वापस 0;
पूर्ण

अटल पूर्णांक cros_ec_keyb_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cros_ec_keyb *ckdev = dev_get_drvdata(&pdev->dev);

	blocking_notअगरier_chain_unरेजिस्टर(&ckdev->ec->event_notअगरier,
					   &ckdev->notअगरier);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id cros_ec_keyb_of_match[] = अणु
	अणु .compatible = "google,cros-ec-keyb" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, cros_ec_keyb_of_match);
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(cros_ec_keyb_pm_ops, शून्य, cros_ec_keyb_resume);

अटल काष्ठा platक्रमm_driver cros_ec_keyb_driver = अणु
	.probe = cros_ec_keyb_probe,
	.हटाओ = cros_ec_keyb_हटाओ,
	.driver = अणु
		.name = "cros-ec-keyb",
		.of_match_table = of_match_ptr(cros_ec_keyb_of_match),
		.pm = &cros_ec_keyb_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(cros_ec_keyb_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("ChromeOS EC keyboard driver");
MODULE_ALIAS("platform:cros-ec-keyb");
