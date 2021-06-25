<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Generic support क्रम sparse keymaps
 *
 * Copyright (c) 2009 Dmitry Torokhov
 *
 * Derived from wistron button driver:
 * Copyright (C) 2005 Miloslav Trmac <mitr@volny.cz>
 * Copyright (C) 2005 Bernhard Rosenkraenzer <bero@arklinux.org>
 * Copyright (C) 2005 Dmitry Torokhov <dtor@mail.ru>
 */

#समावेश <linux/input.h>
#समावेश <linux/input/sparse-keymap.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

MODULE_AUTHOR("Dmitry Torokhov <dtor@mail.ru>");
MODULE_DESCRIPTION("Generic support for sparse keymaps");
MODULE_LICENSE("GPL v2");

अटल अचिन्हित पूर्णांक sparse_keymap_get_key_index(काष्ठा input_dev *dev,
						स्थिर काष्ठा key_entry *k)
अणु
	काष्ठा key_entry *key;
	अचिन्हित पूर्णांक idx = 0;

	क्रम (key = dev->keycode; key->type != KE_END; key++) अणु
		अगर (key->type == KE_KEY) अणु
			अगर (key == k)
				अवरोध;
			idx++;
		पूर्ण
	पूर्ण

	वापस idx;
पूर्ण

अटल काष्ठा key_entry *sparse_keymap_entry_by_index(काष्ठा input_dev *dev,
						      अचिन्हित पूर्णांक index)
अणु
	काष्ठा key_entry *key;
	अचिन्हित पूर्णांक key_cnt = 0;

	क्रम (key = dev->keycode; key->type != KE_END; key++)
		अगर (key->type == KE_KEY)
			अगर (key_cnt++ == index)
				वापस key;

	वापस शून्य;
पूर्ण

/**
 * sparse_keymap_entry_from_scancode - perक्रमm sparse keymap lookup
 * @dev: Input device using sparse keymap
 * @code: Scan code
 *
 * This function is used to perक्रमm &काष्ठा key_entry lookup in an
 * input device using sparse keymap.
 */
काष्ठा key_entry *sparse_keymap_entry_from_scancode(काष्ठा input_dev *dev,
						    अचिन्हित पूर्णांक code)
अणु
	काष्ठा key_entry *key;

	क्रम (key = dev->keycode; key->type != KE_END; key++)
		अगर (code == key->code)
			वापस key;

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(sparse_keymap_entry_from_scancode);

/**
 * sparse_keymap_entry_from_keycode - perक्रमm sparse keymap lookup
 * @dev: Input device using sparse keymap
 * @keycode: Key code
 *
 * This function is used to perक्रमm &काष्ठा key_entry lookup in an
 * input device using sparse keymap.
 */
काष्ठा key_entry *sparse_keymap_entry_from_keycode(काष्ठा input_dev *dev,
						   अचिन्हित पूर्णांक keycode)
अणु
	काष्ठा key_entry *key;

	क्रम (key = dev->keycode; key->type != KE_END; key++)
		अगर (key->type == KE_KEY && keycode == key->keycode)
			वापस key;

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(sparse_keymap_entry_from_keycode);

अटल काष्ठा key_entry *sparse_keymap_locate(काष्ठा input_dev *dev,
					स्थिर काष्ठा input_keymap_entry *ke)
अणु
	काष्ठा key_entry *key;
	अचिन्हित पूर्णांक scancode;

	अगर (ke->flags & INPUT_KEYMAP_BY_INDEX)
		key = sparse_keymap_entry_by_index(dev, ke->index);
	अन्यथा अगर (input_scancode_to_scalar(ke, &scancode) == 0)
		key = sparse_keymap_entry_from_scancode(dev, scancode);
	अन्यथा
		key = शून्य;

	वापस key;
पूर्ण

अटल पूर्णांक sparse_keymap_getkeycode(काष्ठा input_dev *dev,
				    काष्ठा input_keymap_entry *ke)
अणु
	स्थिर काष्ठा key_entry *key;

	अगर (dev->keycode) अणु
		key = sparse_keymap_locate(dev, ke);
		अगर (key && key->type == KE_KEY) अणु
			ke->keycode = key->keycode;
			अगर (!(ke->flags & INPUT_KEYMAP_BY_INDEX))
				ke->index =
					sparse_keymap_get_key_index(dev, key);
			ke->len = माप(key->code);
			स_नकल(ke->scancode, &key->code, माप(key->code));
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक sparse_keymap_setkeycode(काष्ठा input_dev *dev,
				    स्थिर काष्ठा input_keymap_entry *ke,
				    अचिन्हित पूर्णांक *old_keycode)
अणु
	काष्ठा key_entry *key;

	अगर (dev->keycode) अणु
		key = sparse_keymap_locate(dev, ke);
		अगर (key && key->type == KE_KEY) अणु
			*old_keycode = key->keycode;
			key->keycode = ke->keycode;
			set_bit(ke->keycode, dev->keybit);
			अगर (!sparse_keymap_entry_from_keycode(dev, *old_keycode))
				clear_bit(*old_keycode, dev->keybit);
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

/**
 * sparse_keymap_setup - set up sparse keymap क्रम an input device
 * @dev: Input device
 * @keymap: Keymap in क्रमm of array of &key_entry काष्ठाures ending
 *	with %KE_END type entry
 * @setup: Function that can be used to adjust keymap entries
 *	depending on device's needs, may be %शून्य
 *
 * The function calculates size and allocates copy of the original
 * keymap after which sets up input device event bits appropriately.
 * The allocated copy of the keymap is स्वतःmatically मुक्तd when it
 * is no दीर्घer needed.
 */
पूर्णांक sparse_keymap_setup(काष्ठा input_dev *dev,
			स्थिर काष्ठा key_entry *keymap,
			पूर्णांक (*setup)(काष्ठा input_dev *, काष्ठा key_entry *))
अणु
	माप_प्रकार map_size = 1; /* to account क्रम the last KE_END entry */
	स्थिर काष्ठा key_entry *e;
	काष्ठा key_entry *map, *entry;
	पूर्णांक i;
	पूर्णांक error;

	क्रम (e = keymap; e->type != KE_END; e++)
		map_size++;

	map = devm_kmemdup(&dev->dev, keymap, map_size * माप(*map),
			   GFP_KERNEL);
	अगर (!map)
		वापस -ENOMEM;

	क्रम (i = 0; i < map_size; i++) अणु
		entry = &map[i];

		अगर (setup) अणु
			error = setup(dev, entry);
			अगर (error)
				वापस error;
		पूर्ण

		चयन (entry->type) अणु
		हाल KE_KEY:
			__set_bit(EV_KEY, dev->evbit);
			__set_bit(entry->keycode, dev->keybit);
			अवरोध;

		हाल KE_SW:
		हाल KE_VSW:
			__set_bit(EV_SW, dev->evbit);
			__set_bit(entry->sw.code, dev->swbit);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (test_bit(EV_KEY, dev->evbit)) अणु
		__set_bit(KEY_UNKNOWN, dev->keybit);
		__set_bit(EV_MSC, dev->evbit);
		__set_bit(MSC_SCAN, dev->mscbit);
	पूर्ण

	dev->keycode = map;
	dev->keycodemax = map_size;
	dev->getkeycode = sparse_keymap_getkeycode;
	dev->setkeycode = sparse_keymap_setkeycode;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(sparse_keymap_setup);

/**
 * sparse_keymap_report_entry - report event corresponding to given key entry
 * @dev: Input device क्रम which event should be reported
 * @ke: key entry describing event
 * @value: Value that should be reported (ignored by %KE_SW entries)
 * @स्वतःrelease: Signals whether release event should be emitted क्रम %KE_KEY
 *	entries right after reporting press event, ignored by all other
 *	entries
 *
 * This function is used to report input event described by given
 * &काष्ठा key_entry.
 */
व्योम sparse_keymap_report_entry(काष्ठा input_dev *dev, स्थिर काष्ठा key_entry *ke,
				अचिन्हित पूर्णांक value, bool स्वतःrelease)
अणु
	चयन (ke->type) अणु
	हाल KE_KEY:
		input_event(dev, EV_MSC, MSC_SCAN, ke->code);
		input_report_key(dev, ke->keycode, value);
		input_sync(dev);
		अगर (value && स्वतःrelease) अणु
			input_report_key(dev, ke->keycode, 0);
			input_sync(dev);
		पूर्ण
		अवरोध;

	हाल KE_SW:
		value = ke->sw.value;
		fallthrough;

	हाल KE_VSW:
		input_report_चयन(dev, ke->sw.code, value);
		input_sync(dev);
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(sparse_keymap_report_entry);

/**
 * sparse_keymap_report_event - report event corresponding to given scancode
 * @dev: Input device using sparse keymap
 * @code: Scan code
 * @value: Value that should be reported (ignored by %KE_SW entries)
 * @स्वतःrelease: Signals whether release event should be emitted क्रम %KE_KEY
 *	entries right after reporting press event, ignored by all other
 *	entries
 *
 * This function is used to perक्रमm lookup in an input device using sparse
 * keymap and report corresponding event. Returns %true अगर lookup was
 * successful and %false otherwise.
 */
bool sparse_keymap_report_event(काष्ठा input_dev *dev, अचिन्हित पूर्णांक code,
				अचिन्हित पूर्णांक value, bool स्वतःrelease)
अणु
	स्थिर काष्ठा key_entry *ke =
		sparse_keymap_entry_from_scancode(dev, code);
	काष्ठा key_entry unknown_ke;

	अगर (ke) अणु
		sparse_keymap_report_entry(dev, ke, value, स्वतःrelease);
		वापस true;
	पूर्ण

	/* Report an unknown key event as a debugging aid */
	unknown_ke.type = KE_KEY;
	unknown_ke.code = code;
	unknown_ke.keycode = KEY_UNKNOWN;
	sparse_keymap_report_entry(dev, &unknown_ke, value, true);

	वापस false;
पूर्ण
EXPORT_SYMBOL(sparse_keymap_report_event);

