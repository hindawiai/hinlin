<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Helpers क्रम matrix keyboard bindings
 *
 * Copyright (C) 2012 Google, Inc
 *
 * Author:
 *	Olof Johansson <olof@lixom.net>
 */

#समावेश <linux/device.h>
#समावेश <linux/export.h>
#समावेश <linux/gfp.h>
#समावेश <linux/input.h>
#समावेश <linux/input/matrix_keypad.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/property.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>

अटल bool matrix_keypad_map_key(काष्ठा input_dev *input_dev,
				  अचिन्हित पूर्णांक rows, अचिन्हित पूर्णांक cols,
				  अचिन्हित पूर्णांक row_shअगरt, अचिन्हित पूर्णांक key)
अणु
	अचिन्हित लघु *keymap = input_dev->keycode;
	अचिन्हित पूर्णांक row = KEY_ROW(key);
	अचिन्हित पूर्णांक col = KEY_COL(key);
	अचिन्हित लघु code = KEY_VAL(key);

	अगर (row >= rows || col >= cols) अणु
		dev_err(input_dev->dev.parent,
			"%s: invalid keymap entry 0x%x (row: %d, col: %d, rows: %d, cols: %d)\n",
			__func__, key, row, col, rows, cols);
		वापस false;
	पूर्ण

	keymap[MATRIX_SCAN_CODE(row, col, row_shअगरt)] = code;
	__set_bit(code, input_dev->keybit);

	वापस true;
पूर्ण

/**
 * matrix_keypad_parse_properties() - Read properties of matrix keypad
 *
 * @dev: Device containing properties
 * @rows: Returns number of matrix rows
 * @cols: Returns number of matrix columns
 * @वापस 0 अगर OK, <0 on error
 */
पूर्णांक matrix_keypad_parse_properties(काष्ठा device *dev,
				   अचिन्हित पूर्णांक *rows, अचिन्हित पूर्णांक *cols)
अणु
	*rows = *cols = 0;

	device_property_पढ़ो_u32(dev, "keypad,num-rows", rows);
	device_property_पढ़ो_u32(dev, "keypad,num-columns", cols);

	अगर (!*rows || !*cols) अणु
		dev_err(dev, "number of keypad rows/columns not specified\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(matrix_keypad_parse_properties);

अटल पूर्णांक matrix_keypad_parse_keymap(स्थिर अक्षर *propname,
				      अचिन्हित पूर्णांक rows, अचिन्हित पूर्णांक cols,
				      काष्ठा input_dev *input_dev)
अणु
	काष्ठा device *dev = input_dev->dev.parent;
	अचिन्हित पूर्णांक row_shअगरt = get_count_order(cols);
	अचिन्हित पूर्णांक max_keys = rows << row_shअगरt;
	u32 *keys;
	पूर्णांक i;
	पूर्णांक size;
	पूर्णांक retval;

	अगर (!propname)
		propname = "linux,keymap";

	size = device_property_count_u32(dev, propname);
	अगर (size <= 0) अणु
		dev_err(dev, "missing or malformed property %s: %d\n",
			propname, size);
		वापस size < 0 ? size : -EINVAL;
	पूर्ण

	अगर (size > max_keys) अणु
		dev_err(dev, "%s size overflow (%d vs max %u)\n",
			propname, size, max_keys);
		वापस -EINVAL;
	पूर्ण

	keys = kदो_स्मृति_array(size, माप(u32), GFP_KERNEL);
	अगर (!keys)
		वापस -ENOMEM;

	retval = device_property_पढ़ो_u32_array(dev, propname, keys, size);
	अगर (retval) अणु
		dev_err(dev, "failed to read %s property: %d\n",
			propname, retval);
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < size; i++) अणु
		अगर (!matrix_keypad_map_key(input_dev, rows, cols,
					   row_shअगरt, keys[i])) अणु
			retval = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण

	retval = 0;

out:
	kमुक्त(keys);
	वापस retval;
पूर्ण

/**
 * matrix_keypad_build_keymap - convert platक्रमm keymap पूर्णांकo matrix keymap
 * @keymap_data: keymap supplied by the platक्रमm code
 * @keymap_name: name of device tree property containing keymap (अगर device
 *	tree support is enabled).
 * @rows: number of rows in target keymap array
 * @cols: number of cols in target keymap array
 * @keymap: expanded version of keymap that is suitable क्रम use by
 * matrix keyboard driver
 * @input_dev: input devices क्रम which we are setting up the keymap
 *
 * This function converts platक्रमm keymap (encoded with KEY() macro) पूर्णांकo
 * an array of keycodes that is suitable क्रम using in a standard matrix
 * keyboard driver that uses row and col as indices.
 *
 * If @keymap_data is not supplied and device tree support is enabled
 * it will attempt load the keymap from property specअगरied by @keymap_name
 * argument (or "linux,keymap" अगर @keymap_name is %शून्य).
 *
 * If @keymap is %शून्य the function will स्वतःmatically allocate managed
 * block of memory to store the keymap. This memory will be associated with
 * the parent device and स्वतःmatically मुक्तd when device unbinds from the
 * driver.
 *
 * Callers are expected to set up input_dev->dev.parent beक्रमe calling this
 * function.
 */
पूर्णांक matrix_keypad_build_keymap(स्थिर काष्ठा matrix_keymap_data *keymap_data,
			       स्थिर अक्षर *keymap_name,
			       अचिन्हित पूर्णांक rows, अचिन्हित पूर्णांक cols,
			       अचिन्हित लघु *keymap,
			       काष्ठा input_dev *input_dev)
अणु
	अचिन्हित पूर्णांक row_shअगरt = get_count_order(cols);
	माप_प्रकार max_keys = rows << row_shअगरt;
	पूर्णांक i;
	पूर्णांक error;

	अगर (WARN_ON(!input_dev->dev.parent))
		वापस -EINVAL;

	अगर (!keymap) अणु
		keymap = devm_kसुस्मृति(input_dev->dev.parent,
				      max_keys, माप(*keymap),
				      GFP_KERNEL);
		अगर (!keymap) अणु
			dev_err(input_dev->dev.parent,
				"Unable to allocate memory for keymap");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	input_dev->keycode = keymap;
	input_dev->keycodesize = माप(*keymap);
	input_dev->keycodemax = max_keys;

	__set_bit(EV_KEY, input_dev->evbit);

	अगर (keymap_data) अणु
		क्रम (i = 0; i < keymap_data->keymap_size; i++) अणु
			अचिन्हित पूर्णांक key = keymap_data->keymap[i];

			अगर (!matrix_keypad_map_key(input_dev, rows, cols,
						   row_shअगरt, key))
				वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		error = matrix_keypad_parse_keymap(keymap_name, rows, cols,
						   input_dev);
		अगर (error)
			वापस error;
	पूर्ण

	__clear_bit(KEY_RESERVED, input_dev->keybit);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(matrix_keypad_build_keymap);

MODULE_LICENSE("GPL");
