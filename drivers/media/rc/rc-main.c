<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// rc-मुख्य.c - Remote Controller core module
//
// Copyright (C) 2009-2010 by Mauro Carvalho Chehab

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <media/rc-core.h>
#समावेश <linux/द्वा_खोज.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/delay.h>
#समावेश <linux/input.h>
#समावेश <linux/leds.h>
#समावेश <linux/slab.h>
#समावेश <linux/idr.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश "rc-core-priv.h"

/* Sizes are in bytes, 256 bytes allows क्रम 32 entries on x64 */
#घोषणा IR_TAB_MIN_SIZE	256
#घोषणा IR_TAB_MAX_SIZE	8192

अटल स्थिर काष्ठा अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक repeat_period;
	अचिन्हित पूर्णांक scancode_bits;
पूर्ण protocols[] = अणु
	[RC_PROTO_UNKNOWN] = अणु .name = "unknown", .repeat_period = 125 पूर्ण,
	[RC_PROTO_OTHER] = अणु .name = "other", .repeat_period = 125 पूर्ण,
	[RC_PROTO_RC5] = अणु .name = "rc-5",
		.scancode_bits = 0x1f7f, .repeat_period = 114 पूर्ण,
	[RC_PROTO_RC5X_20] = अणु .name = "rc-5x-20",
		.scancode_bits = 0x1f7f3f, .repeat_period = 114 पूर्ण,
	[RC_PROTO_RC5_SZ] = अणु .name = "rc-5-sz",
		.scancode_bits = 0x2fff, .repeat_period = 114 पूर्ण,
	[RC_PROTO_JVC] = अणु .name = "jvc",
		.scancode_bits = 0xffff, .repeat_period = 125 पूर्ण,
	[RC_PROTO_SONY12] = अणु .name = "sony-12",
		.scancode_bits = 0x1f007f, .repeat_period = 100 पूर्ण,
	[RC_PROTO_SONY15] = अणु .name = "sony-15",
		.scancode_bits = 0xff007f, .repeat_period = 100 पूर्ण,
	[RC_PROTO_SONY20] = अणु .name = "sony-20",
		.scancode_bits = 0x1fff7f, .repeat_period = 100 पूर्ण,
	[RC_PROTO_NEC] = अणु .name = "nec",
		.scancode_bits = 0xffff, .repeat_period = 110 पूर्ण,
	[RC_PROTO_NECX] = अणु .name = "nec-x",
		.scancode_bits = 0xffffff, .repeat_period = 110 पूर्ण,
	[RC_PROTO_NEC32] = अणु .name = "nec-32",
		.scancode_bits = 0xffffffff, .repeat_period = 110 पूर्ण,
	[RC_PROTO_SANYO] = अणु .name = "sanyo",
		.scancode_bits = 0x1fffff, .repeat_period = 125 पूर्ण,
	[RC_PROTO_MCIR2_KBD] = अणु .name = "mcir2-kbd",
		.scancode_bits = 0xffffff, .repeat_period = 100 पूर्ण,
	[RC_PROTO_MCIR2_MSE] = अणु .name = "mcir2-mse",
		.scancode_bits = 0x1fffff, .repeat_period = 100 पूर्ण,
	[RC_PROTO_RC6_0] = अणु .name = "rc-6-0",
		.scancode_bits = 0xffff, .repeat_period = 114 पूर्ण,
	[RC_PROTO_RC6_6A_20] = अणु .name = "rc-6-6a-20",
		.scancode_bits = 0xfffff, .repeat_period = 114 पूर्ण,
	[RC_PROTO_RC6_6A_24] = अणु .name = "rc-6-6a-24",
		.scancode_bits = 0xffffff, .repeat_period = 114 पूर्ण,
	[RC_PROTO_RC6_6A_32] = अणु .name = "rc-6-6a-32",
		.scancode_bits = 0xffffffff, .repeat_period = 114 पूर्ण,
	[RC_PROTO_RC6_MCE] = अणु .name = "rc-6-mce",
		.scancode_bits = 0xffff7fff, .repeat_period = 114 पूर्ण,
	[RC_PROTO_SHARP] = अणु .name = "sharp",
		.scancode_bits = 0x1fff, .repeat_period = 125 पूर्ण,
	[RC_PROTO_XMP] = अणु .name = "xmp", .repeat_period = 125 पूर्ण,
	[RC_PROTO_CEC] = अणु .name = "cec", .repeat_period = 0 पूर्ण,
	[RC_PROTO_IMON] = अणु .name = "imon",
		.scancode_bits = 0x7fffffff, .repeat_period = 114 पूर्ण,
	[RC_PROTO_RCMM12] = अणु .name = "rc-mm-12",
		.scancode_bits = 0x00000fff, .repeat_period = 114 पूर्ण,
	[RC_PROTO_RCMM24] = अणु .name = "rc-mm-24",
		.scancode_bits = 0x00ffffff, .repeat_period = 114 पूर्ण,
	[RC_PROTO_RCMM32] = अणु .name = "rc-mm-32",
		.scancode_bits = 0xffffffff, .repeat_period = 114 पूर्ण,
	[RC_PROTO_XBOX_DVD] = अणु .name = "xbox-dvd", .repeat_period = 64 पूर्ण,
पूर्ण;

/* Used to keep track of known keymaps */
अटल LIST_HEAD(rc_map_list);
अटल DEFINE_SPINLOCK(rc_map_lock);
अटल काष्ठा led_trigger *led_feedback;

/* Used to keep track of rc devices */
अटल DEFINE_IDA(rc_ida);

अटल काष्ठा rc_map_list *seek_rc_map(स्थिर अक्षर *name)
अणु
	काष्ठा rc_map_list *map = शून्य;

	spin_lock(&rc_map_lock);
	list_क्रम_each_entry(map, &rc_map_list, list) अणु
		अगर (!म_भेद(name, map->map.name)) अणु
			spin_unlock(&rc_map_lock);
			वापस map;
		पूर्ण
	पूर्ण
	spin_unlock(&rc_map_lock);

	वापस शून्य;
पूर्ण

काष्ठा rc_map *rc_map_get(स्थिर अक्षर *name)
अणु

	काष्ठा rc_map_list *map;

	map = seek_rc_map(name);
#अगर_घोषित CONFIG_MODULES
	अगर (!map) अणु
		पूर्णांक rc = request_module("%s", name);
		अगर (rc < 0) अणु
			pr_err("Couldn't load IR keymap %s\n", name);
			वापस शून्य;
		पूर्ण
		msleep(20);	/* Give some समय क्रम IR to रेजिस्टर */

		map = seek_rc_map(name);
	पूर्ण
#पूर्ण_अगर
	अगर (!map) अणु
		pr_err("IR keymap %s not found\n", name);
		वापस शून्य;
	पूर्ण

	prपूर्णांकk(KERN_INFO "Registered IR keymap %s\n", map->map.name);

	वापस &map->map;
पूर्ण
EXPORT_SYMBOL_GPL(rc_map_get);

पूर्णांक rc_map_रेजिस्टर(काष्ठा rc_map_list *map)
अणु
	spin_lock(&rc_map_lock);
	list_add_tail(&map->list, &rc_map_list);
	spin_unlock(&rc_map_lock);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rc_map_रेजिस्टर);

व्योम rc_map_unरेजिस्टर(काष्ठा rc_map_list *map)
अणु
	spin_lock(&rc_map_lock);
	list_del(&map->list);
	spin_unlock(&rc_map_lock);
पूर्ण
EXPORT_SYMBOL_GPL(rc_map_unरेजिस्टर);


अटल काष्ठा rc_map_table empty[] = अणु
	अणु 0x2a, KEY_COFFEE पूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list empty_map = अणु
	.map = अणु
		.scan     = empty,
		.size     = ARRAY_SIZE(empty),
		.rc_proto = RC_PROTO_UNKNOWN,	/* Legacy IR type */
		.name     = RC_MAP_EMPTY,
	पूर्ण
पूर्ण;

/**
 * scancode_to_u64() - converts scancode in &काष्ठा input_keymap_entry
 * @ke: keymap entry containing scancode to be converted.
 * @scancode: poपूर्णांकer to the location where converted scancode should
 *	be stored.
 *
 * This function is a version of input_scancode_to_scalar specialized क्रम
 * rc-core.
 */
अटल पूर्णांक scancode_to_u64(स्थिर काष्ठा input_keymap_entry *ke, u64 *scancode)
अणु
	चयन (ke->len) अणु
	हाल 1:
		*scancode = *((u8 *)ke->scancode);
		अवरोध;

	हाल 2:
		*scancode = *((u16 *)ke->scancode);
		अवरोध;

	हाल 4:
		*scancode = *((u32 *)ke->scancode);
		अवरोध;

	हाल 8:
		*scancode = *((u64 *)ke->scancode);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ir_create_table() - initializes a scancode table
 * @dev:	the rc_dev device
 * @rc_map:	the rc_map to initialize
 * @name:	name to assign to the table
 * @rc_proto:	ir type to assign to the new table
 * @size:	initial size of the table
 *
 * This routine will initialize the rc_map and will allocate
 * memory to hold at least the specअगरied number of elements.
 *
 * वापस:	zero on success or a negative error code
 */
अटल पूर्णांक ir_create_table(काष्ठा rc_dev *dev, काष्ठा rc_map *rc_map,
			   स्थिर अक्षर *name, u64 rc_proto, माप_प्रकार size)
अणु
	rc_map->name = kstrdup(name, GFP_KERNEL);
	अगर (!rc_map->name)
		वापस -ENOMEM;
	rc_map->rc_proto = rc_proto;
	rc_map->alloc = roundup_घात_of_two(size * माप(काष्ठा rc_map_table));
	rc_map->size = rc_map->alloc / माप(काष्ठा rc_map_table);
	rc_map->scan = kदो_स्मृति(rc_map->alloc, GFP_KERNEL);
	अगर (!rc_map->scan) अणु
		kमुक्त(rc_map->name);
		rc_map->name = शून्य;
		वापस -ENOMEM;
	पूर्ण

	dev_dbg(&dev->dev, "Allocated space for %u keycode entries (%u bytes)\n",
		rc_map->size, rc_map->alloc);
	वापस 0;
पूर्ण

/**
 * ir_मुक्त_table() - मुक्तs memory allocated by a scancode table
 * @rc_map:	the table whose mappings need to be मुक्तd
 *
 * This routine will मुक्त memory alloctaed क्रम key mappings used by given
 * scancode table.
 */
अटल व्योम ir_मुक्त_table(काष्ठा rc_map *rc_map)
अणु
	rc_map->size = 0;
	kमुक्त(rc_map->name);
	rc_map->name = शून्य;
	kमुक्त(rc_map->scan);
	rc_map->scan = शून्य;
पूर्ण

/**
 * ir_reमाप_प्रकारable() - resizes a scancode table अगर necessary
 * @dev:	the rc_dev device
 * @rc_map:	the rc_map to resize
 * @gfp_flags:	gfp flags to use when allocating memory
 *
 * This routine will shrink the rc_map अगर it has lots of
 * unused entries and grow it अगर it is full.
 *
 * वापस:	zero on success or a negative error code
 */
अटल पूर्णांक ir_reमाप_प्रकारable(काष्ठा rc_dev *dev, काष्ठा rc_map *rc_map,
			   gfp_t gfp_flags)
अणु
	अचिन्हित पूर्णांक oldalloc = rc_map->alloc;
	अचिन्हित पूर्णांक newalloc = oldalloc;
	काष्ठा rc_map_table *oldscan = rc_map->scan;
	काष्ठा rc_map_table *newscan;

	अगर (rc_map->size == rc_map->len) अणु
		/* All entries in use -> grow keytable */
		अगर (rc_map->alloc >= IR_TAB_MAX_SIZE)
			वापस -ENOMEM;

		newalloc *= 2;
		dev_dbg(&dev->dev, "Growing table to %u bytes\n", newalloc);
	पूर्ण

	अगर ((rc_map->len * 3 < rc_map->size) && (oldalloc > IR_TAB_MIN_SIZE)) अणु
		/* Less than 1/3 of entries in use -> shrink keytable */
		newalloc /= 2;
		dev_dbg(&dev->dev, "Shrinking table to %u bytes\n", newalloc);
	पूर्ण

	अगर (newalloc == oldalloc)
		वापस 0;

	newscan = kदो_स्मृति(newalloc, gfp_flags);
	अगर (!newscan)
		वापस -ENOMEM;

	स_नकल(newscan, rc_map->scan, rc_map->len * माप(काष्ठा rc_map_table));
	rc_map->scan = newscan;
	rc_map->alloc = newalloc;
	rc_map->size = rc_map->alloc / माप(काष्ठा rc_map_table);
	kमुक्त(oldscan);
	वापस 0;
पूर्ण

/**
 * ir_update_mapping() - set a keycode in the scancode->keycode table
 * @dev:	the काष्ठा rc_dev device descriptor
 * @rc_map:	scancode table to be adjusted
 * @index:	index of the mapping that needs to be updated
 * @new_keycode: the desired keycode
 *
 * This routine is used to update scancode->keycode mapping at given
 * position.
 *
 * वापस:	previous keycode asचिन्हित to the mapping
 *
 */
अटल अचिन्हित पूर्णांक ir_update_mapping(काष्ठा rc_dev *dev,
				      काष्ठा rc_map *rc_map,
				      अचिन्हित पूर्णांक index,
				      अचिन्हित पूर्णांक new_keycode)
अणु
	पूर्णांक old_keycode = rc_map->scan[index].keycode;
	पूर्णांक i;

	/* Did the user wish to हटाओ the mapping? */
	अगर (new_keycode == KEY_RESERVED || new_keycode == KEY_UNKNOWN) अणु
		dev_dbg(&dev->dev, "#%d: Deleting scan 0x%04llx\n",
			index, rc_map->scan[index].scancode);
		rc_map->len--;
		स_हटाओ(&rc_map->scan[index], &rc_map->scan[index+ 1],
			(rc_map->len - index) * माप(काष्ठा rc_map_table));
	पूर्ण अन्यथा अणु
		dev_dbg(&dev->dev, "#%d: %s scan 0x%04llx with key 0x%04x\n",
			index,
			old_keycode == KEY_RESERVED ? "New" : "Replacing",
			rc_map->scan[index].scancode, new_keycode);
		rc_map->scan[index].keycode = new_keycode;
		__set_bit(new_keycode, dev->input_dev->keybit);
	पूर्ण

	अगर (old_keycode != KEY_RESERVED) अणु
		/* A previous mapping was updated... */
		__clear_bit(old_keycode, dev->input_dev->keybit);
		/* ... but another scancode might use the same keycode */
		क्रम (i = 0; i < rc_map->len; i++) अणु
			अगर (rc_map->scan[i].keycode == old_keycode) अणु
				__set_bit(old_keycode, dev->input_dev->keybit);
				अवरोध;
			पूर्ण
		पूर्ण

		/* Possibly shrink the keytable, failure is not a problem */
		ir_reमाप_प्रकारable(dev, rc_map, GFP_ATOMIC);
	पूर्ण

	वापस old_keycode;
पूर्ण

/**
 * ir_establish_scancode() - set a keycode in the scancode->keycode table
 * @dev:	the काष्ठा rc_dev device descriptor
 * @rc_map:	scancode table to be searched
 * @scancode:	the desired scancode
 * @resize:	controls whether we allowed to resize the table to
 *		accommodate not yet present scancodes
 *
 * This routine is used to locate given scancode in rc_map.
 * If scancode is not yet present the routine will allocate a new slot
 * क्रम it.
 *
 * वापस:	index of the mapping containing scancode in question
 *		or -1U in हाल of failure.
 */
अटल अचिन्हित पूर्णांक ir_establish_scancode(काष्ठा rc_dev *dev,
					  काष्ठा rc_map *rc_map,
					  u64 scancode, bool resize)
अणु
	अचिन्हित पूर्णांक i;

	/*
	 * Unक्रमtunately, some hardware-based IR decoders करोn't provide
	 * all bits क्रम the complete IR code. In general, they provide only
	 * the command part of the IR code. Yet, as it is possible to replace
	 * the provided IR with another one, it is needed to allow loading
	 * IR tables from other remotes. So, we support specअगरying a mask to
	 * indicate the valid bits of the scancodes.
	 */
	अगर (dev->scancode_mask)
		scancode &= dev->scancode_mask;

	/* First check अगर we alपढ़ोy have a mapping क्रम this ir command */
	क्रम (i = 0; i < rc_map->len; i++) अणु
		अगर (rc_map->scan[i].scancode == scancode)
			वापस i;

		/* Keytable is sorted from lowest to highest scancode */
		अगर (rc_map->scan[i].scancode >= scancode)
			अवरोध;
	पूर्ण

	/* No previous mapping found, we might need to grow the table */
	अगर (rc_map->size == rc_map->len) अणु
		अगर (!resize || ir_reमाप_प्रकारable(dev, rc_map, GFP_ATOMIC))
			वापस -1U;
	पूर्ण

	/* i is the proper index to insert our new keycode */
	अगर (i < rc_map->len)
		स_हटाओ(&rc_map->scan[i + 1], &rc_map->scan[i],
			(rc_map->len - i) * माप(काष्ठा rc_map_table));
	rc_map->scan[i].scancode = scancode;
	rc_map->scan[i].keycode = KEY_RESERVED;
	rc_map->len++;

	वापस i;
पूर्ण

/**
 * ir_setkeycode() - set a keycode in the scancode->keycode table
 * @idev:	the काष्ठा input_dev device descriptor
 * @ke:		Input keymap entry
 * @old_keycode: result
 *
 * This routine is used to handle evdev EVIOCSKEY ioctl.
 *
 * वापस:	-EINVAL अगर the keycode could not be inserted, otherwise zero.
 */
अटल पूर्णांक ir_setkeycode(काष्ठा input_dev *idev,
			 स्थिर काष्ठा input_keymap_entry *ke,
			 अचिन्हित पूर्णांक *old_keycode)
अणु
	काष्ठा rc_dev *rdev = input_get_drvdata(idev);
	काष्ठा rc_map *rc_map = &rdev->rc_map;
	अचिन्हित पूर्णांक index;
	u64 scancode;
	पूर्णांक retval = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rc_map->lock, flags);

	अगर (ke->flags & INPUT_KEYMAP_BY_INDEX) अणु
		index = ke->index;
		अगर (index >= rc_map->len) अणु
			retval = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		retval = scancode_to_u64(ke, &scancode);
		अगर (retval)
			जाओ out;

		index = ir_establish_scancode(rdev, rc_map, scancode, true);
		अगर (index >= rc_map->len) अणु
			retval = -ENOMEM;
			जाओ out;
		पूर्ण
	पूर्ण

	*old_keycode = ir_update_mapping(rdev, rc_map, index, ke->keycode);

out:
	spin_unlock_irqrestore(&rc_map->lock, flags);
	वापस retval;
पूर्ण

/**
 * ir_setkeytable() - sets several entries in the scancode->keycode table
 * @dev:	the काष्ठा rc_dev device descriptor
 * @from:	the काष्ठा rc_map to copy entries from
 *
 * This routine is used to handle table initialization.
 *
 * वापस:	-ENOMEM अगर all keycodes could not be inserted, otherwise zero.
 */
अटल पूर्णांक ir_setkeytable(काष्ठा rc_dev *dev, स्थिर काष्ठा rc_map *from)
अणु
	काष्ठा rc_map *rc_map = &dev->rc_map;
	अचिन्हित पूर्णांक i, index;
	पूर्णांक rc;

	rc = ir_create_table(dev, rc_map, from->name, from->rc_proto,
			     from->size);
	अगर (rc)
		वापस rc;

	क्रम (i = 0; i < from->size; i++) अणु
		index = ir_establish_scancode(dev, rc_map,
					      from->scan[i].scancode, false);
		अगर (index >= rc_map->len) अणु
			rc = -ENOMEM;
			अवरोध;
		पूर्ण

		ir_update_mapping(dev, rc_map, index,
				  from->scan[i].keycode);
	पूर्ण

	अगर (rc)
		ir_मुक्त_table(rc_map);

	वापस rc;
पूर्ण

अटल पूर्णांक rc_map_cmp(स्थिर व्योम *key, स्थिर व्योम *elt)
अणु
	स्थिर u64 *scancode = key;
	स्थिर काष्ठा rc_map_table *e = elt;

	अगर (*scancode < e->scancode)
		वापस -1;
	अन्यथा अगर (*scancode > e->scancode)
		वापस 1;
	वापस 0;
पूर्ण

/**
 * ir_lookup_by_scancode() - locate mapping by scancode
 * @rc_map:	the काष्ठा rc_map to search
 * @scancode:	scancode to look क्रम in the table
 *
 * This routine perक्रमms binary search in RC keykeymap table क्रम
 * given scancode.
 *
 * वापस:	index in the table, -1U अगर not found
 */
अटल अचिन्हित पूर्णांक ir_lookup_by_scancode(स्थिर काष्ठा rc_map *rc_map,
					  u64 scancode)
अणु
	काष्ठा rc_map_table *res;

	res = द्वा_खोज(&scancode, rc_map->scan, rc_map->len,
		      माप(काष्ठा rc_map_table), rc_map_cmp);
	अगर (!res)
		वापस -1U;
	अन्यथा
		वापस res - rc_map->scan;
पूर्ण

/**
 * ir_getkeycode() - get a keycode from the scancode->keycode table
 * @idev:	the काष्ठा input_dev device descriptor
 * @ke:		Input keymap entry
 *
 * This routine is used to handle evdev EVIOCGKEY ioctl.
 *
 * वापस:	always वापसs zero.
 */
अटल पूर्णांक ir_getkeycode(काष्ठा input_dev *idev,
			 काष्ठा input_keymap_entry *ke)
अणु
	काष्ठा rc_dev *rdev = input_get_drvdata(idev);
	काष्ठा rc_map *rc_map = &rdev->rc_map;
	काष्ठा rc_map_table *entry;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक index;
	u64 scancode;
	पूर्णांक retval;

	spin_lock_irqsave(&rc_map->lock, flags);

	अगर (ke->flags & INPUT_KEYMAP_BY_INDEX) अणु
		index = ke->index;
	पूर्ण अन्यथा अणु
		retval = scancode_to_u64(ke, &scancode);
		अगर (retval)
			जाओ out;

		index = ir_lookup_by_scancode(rc_map, scancode);
	पूर्ण

	अगर (index < rc_map->len) अणु
		entry = &rc_map->scan[index];

		ke->index = index;
		ke->keycode = entry->keycode;
		ke->len = माप(entry->scancode);
		स_नकल(ke->scancode, &entry->scancode, माप(entry->scancode));
	पूर्ण अन्यथा अगर (!(ke->flags & INPUT_KEYMAP_BY_INDEX)) अणु
		/*
		 * We करो not really know the valid range of scancodes
		 * so let's respond with KEY_RESERVED to anything we
		 * करो not have mapping क्रम [yet].
		 */
		ke->index = index;
		ke->keycode = KEY_RESERVED;
	पूर्ण अन्यथा अणु
		retval = -EINVAL;
		जाओ out;
	पूर्ण

	retval = 0;

out:
	spin_unlock_irqrestore(&rc_map->lock, flags);
	वापस retval;
पूर्ण

/**
 * rc_g_keycode_from_table() - माला_लो the keycode that corresponds to a scancode
 * @dev:	the काष्ठा rc_dev descriptor of the device
 * @scancode:	the scancode to look क्रम
 *
 * This routine is used by drivers which need to convert a scancode to a
 * keycode. Normally it should not be used since drivers should have no
 * पूर्णांकerest in keycodes.
 *
 * वापस:	the corresponding keycode, or KEY_RESERVED
 */
u32 rc_g_keycode_from_table(काष्ठा rc_dev *dev, u64 scancode)
अणु
	काष्ठा rc_map *rc_map = &dev->rc_map;
	अचिन्हित पूर्णांक keycode;
	अचिन्हित पूर्णांक index;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rc_map->lock, flags);

	index = ir_lookup_by_scancode(rc_map, scancode);
	keycode = index < rc_map->len ?
			rc_map->scan[index].keycode : KEY_RESERVED;

	spin_unlock_irqrestore(&rc_map->lock, flags);

	अगर (keycode != KEY_RESERVED)
		dev_dbg(&dev->dev, "%s: scancode 0x%04llx keycode 0x%02x\n",
			dev->device_name, scancode, keycode);

	वापस keycode;
पूर्ण
EXPORT_SYMBOL_GPL(rc_g_keycode_from_table);

/**
 * ir_करो_keyup() - पूर्णांकernal function to संकेत the release of a keypress
 * @dev:	the काष्ठा rc_dev descriptor of the device
 * @sync:	whether or not to call input_sync
 *
 * This function is used पूर्णांकernally to release a keypress, it must be
 * called with keylock held.
 */
अटल व्योम ir_करो_keyup(काष्ठा rc_dev *dev, bool sync)
अणु
	अगर (!dev->keypressed)
		वापस;

	dev_dbg(&dev->dev, "keyup key 0x%04x\n", dev->last_keycode);
	del_समयr(&dev->समयr_repeat);
	input_report_key(dev->input_dev, dev->last_keycode, 0);
	led_trigger_event(led_feedback, LED_OFF);
	अगर (sync)
		input_sync(dev->input_dev);
	dev->keypressed = false;
पूर्ण

/**
 * rc_keyup() - संकेतs the release of a keypress
 * @dev:	the काष्ठा rc_dev descriptor of the device
 *
 * This routine is used to संकेत that a key has been released on the
 * remote control.
 */
व्योम rc_keyup(काष्ठा rc_dev *dev)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->keylock, flags);
	ir_करो_keyup(dev, true);
	spin_unlock_irqrestore(&dev->keylock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(rc_keyup);

/**
 * ir_समयr_keyup() - generates a keyup event after a समयout
 *
 * @t:		a poपूर्णांकer to the काष्ठा समयr_list
 *
 * This routine will generate a keyup event some समय after a keyकरोwn event
 * is generated when no further activity has been detected.
 */
अटल व्योम ir_समयr_keyup(काष्ठा समयr_list *t)
अणु
	काष्ठा rc_dev *dev = from_समयr(dev, t, समयr_keyup);
	अचिन्हित दीर्घ flags;

	/*
	 * ir->keyup_jअगरfies is used to prevent a race condition अगर a
	 * hardware पूर्णांकerrupt occurs at this poपूर्णांक and the keyup समयr
	 * event is moved further पूर्णांकo the future as a result.
	 *
	 * The समयr will then be reactivated and this function called
	 * again in the future. We need to निकास gracefully in that हाल
	 * to allow the input subप्रणाली to करो its स्वतः-repeat magic or
	 * a keyup event might follow immediately after the keyकरोwn.
	 */
	spin_lock_irqsave(&dev->keylock, flags);
	अगर (समय_is_beक्रमe_eq_jअगरfies(dev->keyup_jअगरfies))
		ir_करो_keyup(dev, true);
	spin_unlock_irqrestore(&dev->keylock, flags);
पूर्ण

/**
 * ir_समयr_repeat() - generates a repeat event after a समयout
 *
 * @t:		a poपूर्णांकer to the काष्ठा समयr_list
 *
 * This routine will generate a soft repeat event every REP_PERIOD
 * milliseconds.
 */
अटल व्योम ir_समयr_repeat(काष्ठा समयr_list *t)
अणु
	काष्ठा rc_dev *dev = from_समयr(dev, t, समयr_repeat);
	काष्ठा input_dev *input = dev->input_dev;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->keylock, flags);
	अगर (dev->keypressed) अणु
		input_event(input, EV_KEY, dev->last_keycode, 2);
		input_sync(input);
		अगर (input->rep[REP_PERIOD])
			mod_समयr(&dev->समयr_repeat, jअगरfies +
				  msecs_to_jअगरfies(input->rep[REP_PERIOD]));
	पूर्ण
	spin_unlock_irqrestore(&dev->keylock, flags);
पूर्ण

अटल अचिन्हित पूर्णांक repeat_period(पूर्णांक protocol)
अणु
	अगर (protocol >= ARRAY_SIZE(protocols))
		वापस 100;

	वापस protocols[protocol].repeat_period;
पूर्ण

/**
 * rc_repeat() - संकेतs that a key is still pressed
 * @dev:	the काष्ठा rc_dev descriptor of the device
 *
 * This routine is used by IR decoders when a repeat message which करोes
 * not include the necessary bits to reproduce the scancode has been
 * received.
 */
व्योम rc_repeat(काष्ठा rc_dev *dev)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक समयout = usecs_to_jअगरfies(dev->समयout) +
		msecs_to_jअगरfies(repeat_period(dev->last_protocol));
	काष्ठा lirc_scancode sc = अणु
		.scancode = dev->last_scancode, .rc_proto = dev->last_protocol,
		.keycode = dev->keypressed ? dev->last_keycode : KEY_RESERVED,
		.flags = LIRC_SCANCODE_FLAG_REPEAT |
			 (dev->last_toggle ? LIRC_SCANCODE_FLAG_TOGGLE : 0)
	पूर्ण;

	अगर (dev->allowed_protocols != RC_PROTO_BIT_CEC)
		lirc_scancode_event(dev, &sc);

	spin_lock_irqsave(&dev->keylock, flags);

	अगर (dev->last_scancode <= U32_MAX) अणु
		input_event(dev->input_dev, EV_MSC, MSC_SCAN,
			    dev->last_scancode);
		input_sync(dev->input_dev);
	पूर्ण

	अगर (dev->keypressed) अणु
		dev->keyup_jअगरfies = jअगरfies + समयout;
		mod_समयr(&dev->समयr_keyup, dev->keyup_jअगरfies);
	पूर्ण

	spin_unlock_irqrestore(&dev->keylock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(rc_repeat);

/**
 * ir_करो_keyकरोwn() - पूर्णांकernal function to process a keypress
 * @dev:	the काष्ठा rc_dev descriptor of the device
 * @protocol:	the protocol of the keypress
 * @scancode:   the scancode of the keypress
 * @keycode:    the keycode of the keypress
 * @toggle:     the toggle value of the keypress
 *
 * This function is used पूर्णांकernally to रेजिस्टर a keypress, it must be
 * called with keylock held.
 */
अटल व्योम ir_करो_keyकरोwn(काष्ठा rc_dev *dev, क्रमागत rc_proto protocol,
			  u64 scancode, u32 keycode, u8 toggle)
अणु
	bool new_event = (!dev->keypressed		 ||
			  dev->last_protocol != protocol ||
			  dev->last_scancode != scancode ||
			  dev->last_toggle   != toggle);
	काष्ठा lirc_scancode sc = अणु
		.scancode = scancode, .rc_proto = protocol,
		.flags = toggle ? LIRC_SCANCODE_FLAG_TOGGLE : 0,
		.keycode = keycode
	पूर्ण;

	अगर (dev->allowed_protocols != RC_PROTO_BIT_CEC)
		lirc_scancode_event(dev, &sc);

	अगर (new_event && dev->keypressed)
		ir_करो_keyup(dev, false);

	अगर (scancode <= U32_MAX)
		input_event(dev->input_dev, EV_MSC, MSC_SCAN, scancode);

	dev->last_protocol = protocol;
	dev->last_scancode = scancode;
	dev->last_toggle = toggle;
	dev->last_keycode = keycode;

	अगर (new_event && keycode != KEY_RESERVED) अणु
		/* Register a keypress */
		dev->keypressed = true;

		dev_dbg(&dev->dev, "%s: key down event, key 0x%04x, protocol 0x%04x, scancode 0x%08llx\n",
			dev->device_name, keycode, protocol, scancode);
		input_report_key(dev->input_dev, keycode, 1);

		led_trigger_event(led_feedback, LED_FULL);
	पूर्ण

	/*
	 * For CEC, start sending repeat messages as soon as the first
	 * repeated message is sent, as दीर्घ as REP_DELAY = 0 and REP_PERIOD
	 * is non-zero. Otherwise, the input layer will generate repeat
	 * messages.
	 */
	अगर (!new_event && keycode != KEY_RESERVED &&
	    dev->allowed_protocols == RC_PROTO_BIT_CEC &&
	    !समयr_pending(&dev->समयr_repeat) &&
	    dev->input_dev->rep[REP_PERIOD] &&
	    !dev->input_dev->rep[REP_DELAY]) अणु
		input_event(dev->input_dev, EV_KEY, keycode, 2);
		mod_समयr(&dev->समयr_repeat, jअगरfies +
			  msecs_to_jअगरfies(dev->input_dev->rep[REP_PERIOD]));
	पूर्ण

	input_sync(dev->input_dev);
पूर्ण

/**
 * rc_keyकरोwn() - generates input event क्रम a key press
 * @dev:	the काष्ठा rc_dev descriptor of the device
 * @protocol:	the protocol क्रम the keypress
 * @scancode:	the scancode क्रम the keypress
 * @toggle:     the toggle value (protocol dependent, अगर the protocol करोesn't
 *              support toggle values, this should be set to zero)
 *
 * This routine is used to संकेत that a key has been pressed on the
 * remote control.
 */
व्योम rc_keyकरोwn(काष्ठा rc_dev *dev, क्रमागत rc_proto protocol, u64 scancode,
		u8 toggle)
अणु
	अचिन्हित दीर्घ flags;
	u32 keycode = rc_g_keycode_from_table(dev, scancode);

	spin_lock_irqsave(&dev->keylock, flags);
	ir_करो_keyकरोwn(dev, protocol, scancode, keycode, toggle);

	अगर (dev->keypressed) अणु
		dev->keyup_jअगरfies = jअगरfies + usecs_to_jअगरfies(dev->समयout) +
			msecs_to_jअगरfies(repeat_period(protocol));
		mod_समयr(&dev->समयr_keyup, dev->keyup_jअगरfies);
	पूर्ण
	spin_unlock_irqrestore(&dev->keylock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(rc_keyकरोwn);

/**
 * rc_keyकरोwn_noसमयout() - generates input event क्रम a key press without
 *                          an स्वतःmatic keyup event at a later समय
 * @dev:	the काष्ठा rc_dev descriptor of the device
 * @protocol:	the protocol क्रम the keypress
 * @scancode:	the scancode क्रम the keypress
 * @toggle:     the toggle value (protocol dependent, अगर the protocol करोesn't
 *              support toggle values, this should be set to zero)
 *
 * This routine is used to संकेत that a key has been pressed on the
 * remote control. The driver must manually call rc_keyup() at a later stage.
 */
व्योम rc_keyकरोwn_noसमयout(काष्ठा rc_dev *dev, क्रमागत rc_proto protocol,
			  u64 scancode, u8 toggle)
अणु
	अचिन्हित दीर्घ flags;
	u32 keycode = rc_g_keycode_from_table(dev, scancode);

	spin_lock_irqsave(&dev->keylock, flags);
	ir_करो_keyकरोwn(dev, protocol, scancode, keycode, toggle);
	spin_unlock_irqrestore(&dev->keylock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(rc_keyकरोwn_noसमयout);

/**
 * rc_validate_scancode() - checks that a scancode is valid क्रम a protocol.
 *	For nec, it should करो the opposite of ir_nec_bytes_to_scancode()
 * @proto:	protocol
 * @scancode:	scancode
 */
bool rc_validate_scancode(क्रमागत rc_proto proto, u32 scancode)
अणु
	चयन (proto) अणु
	/*
	 * NECX has a 16-bit address; अगर the lower 8 bits match the upper
	 * 8 bits inverted, then the address would match regular nec.
	 */
	हाल RC_PROTO_NECX:
		अगर ((((scancode >> 16) ^ ~(scancode >> 8)) & 0xff) == 0)
			वापस false;
		अवरोध;
	/*
	 * NEC32 has a 16 bit address and 16 bit command. If the lower 8 bits
	 * of the command match the upper 8 bits inverted, then it would
	 * be either NEC or NECX.
	 */
	हाल RC_PROTO_NEC32:
		अगर ((((scancode >> 8) ^ ~scancode) & 0xff) == 0)
			वापस false;
		अवरोध;
	/*
	 * If the customer code (top 32-bit) is 0x800f, it is MCE अन्यथा it
	 * is regular mode-6a 32 bit
	 */
	हाल RC_PROTO_RC6_MCE:
		अगर ((scancode & 0xffff0000) != 0x800f0000)
			वापस false;
		अवरोध;
	हाल RC_PROTO_RC6_6A_32:
		अगर ((scancode & 0xffff0000) == 0x800f0000)
			वापस false;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस true;
पूर्ण

/**
 * rc_validate_filter() - checks that the scancode and mask are valid and
 *			  provides sensible शेषs
 * @dev:	the काष्ठा rc_dev descriptor of the device
 * @filter:	the scancode and mask
 *
 * वापस:	0 or -EINVAL अगर the filter is not valid
 */
अटल पूर्णांक rc_validate_filter(काष्ठा rc_dev *dev,
			      काष्ठा rc_scancode_filter *filter)
अणु
	u32 mask, s = filter->data;
	क्रमागत rc_proto protocol = dev->wakeup_protocol;

	अगर (protocol >= ARRAY_SIZE(protocols))
		वापस -EINVAL;

	mask = protocols[protocol].scancode_bits;

	अगर (!rc_validate_scancode(protocol, s))
		वापस -EINVAL;

	filter->data &= mask;
	filter->mask &= mask;

	/*
	 * If we have to raw encode the IR क्रम wakeup, we cannot have a mask
	 */
	अगर (dev->encode_wakeup && filter->mask != 0 && filter->mask != mask)
		वापस -EINVAL;

	वापस 0;
पूर्ण

पूर्णांक rc_खोलो(काष्ठा rc_dev *rdev)
अणु
	पूर्णांक rval = 0;

	अगर (!rdev)
		वापस -EINVAL;

	mutex_lock(&rdev->lock);

	अगर (!rdev->रेजिस्टरed) अणु
		rval = -ENODEV;
	पूर्ण अन्यथा अणु
		अगर (!rdev->users++ && rdev->खोलो)
			rval = rdev->खोलो(rdev);

		अगर (rval)
			rdev->users--;
	पूर्ण

	mutex_unlock(&rdev->lock);

	वापस rval;
पूर्ण

अटल पूर्णांक ir_खोलो(काष्ठा input_dev *idev)
अणु
	काष्ठा rc_dev *rdev = input_get_drvdata(idev);

	वापस rc_खोलो(rdev);
पूर्ण

व्योम rc_बंद(काष्ठा rc_dev *rdev)
अणु
	अगर (rdev) अणु
		mutex_lock(&rdev->lock);

		अगर (!--rdev->users && rdev->बंद && rdev->रेजिस्टरed)
			rdev->बंद(rdev);

		mutex_unlock(&rdev->lock);
	पूर्ण
पूर्ण

अटल व्योम ir_बंद(काष्ठा input_dev *idev)
अणु
	काष्ठा rc_dev *rdev = input_get_drvdata(idev);
	rc_बंद(rdev);
पूर्ण

/* class क्रम /sys/class/rc */
अटल अक्षर *rc_devnode(काष्ठा device *dev, umode_t *mode)
अणु
	वापस kaप्र_लिखो(GFP_KERNEL, "rc/%s", dev_name(dev));
पूर्ण

अटल काष्ठा class rc_class = अणु
	.name		= "rc",
	.devnode	= rc_devnode,
पूर्ण;

/*
 * These are the protocol textual descriptions that are
 * used by the sysfs protocols file. Note that the order
 * of the entries is relevant.
 */
अटल स्थिर काष्ठा अणु
	u64	type;
	स्थिर अक्षर	*name;
	स्थिर अक्षर	*module_name;
पूर्ण proto_names[] = अणु
	अणु RC_PROTO_BIT_NONE,	"none",		शून्य			पूर्ण,
	अणु RC_PROTO_BIT_OTHER,	"other",	शून्य			पूर्ण,
	अणु RC_PROTO_BIT_UNKNOWN,	"unknown",	शून्य			पूर्ण,
	अणु RC_PROTO_BIT_RC5 |
	  RC_PROTO_BIT_RC5X_20,	"rc-5",		"ir-rc5-decoder"	पूर्ण,
	अणु RC_PROTO_BIT_NEC |
	  RC_PROTO_BIT_NECX |
	  RC_PROTO_BIT_NEC32,	"nec",		"ir-nec-decoder"	पूर्ण,
	अणु RC_PROTO_BIT_RC6_0 |
	  RC_PROTO_BIT_RC6_6A_20 |
	  RC_PROTO_BIT_RC6_6A_24 |
	  RC_PROTO_BIT_RC6_6A_32 |
	  RC_PROTO_BIT_RC6_MCE,	"rc-6",		"ir-rc6-decoder"	पूर्ण,
	अणु RC_PROTO_BIT_JVC,	"jvc",		"ir-jvc-decoder"	पूर्ण,
	अणु RC_PROTO_BIT_SONY12 |
	  RC_PROTO_BIT_SONY15 |
	  RC_PROTO_BIT_SONY20,	"sony",		"ir-sony-decoder"	पूर्ण,
	अणु RC_PROTO_BIT_RC5_SZ,	"rc-5-sz",	"ir-rc5-decoder"	पूर्ण,
	अणु RC_PROTO_BIT_SANYO,	"sanyo",	"ir-sanyo-decoder"	पूर्ण,
	अणु RC_PROTO_BIT_SHARP,	"sharp",	"ir-sharp-decoder"	पूर्ण,
	अणु RC_PROTO_BIT_MCIR2_KBD |
	  RC_PROTO_BIT_MCIR2_MSE, "mce_kbd",	"ir-mce_kbd-decoder"	पूर्ण,
	अणु RC_PROTO_BIT_XMP,	"xmp",		"ir-xmp-decoder"	पूर्ण,
	अणु RC_PROTO_BIT_CEC,	"cec",		शून्य			पूर्ण,
	अणु RC_PROTO_BIT_IMON,	"imon",		"ir-imon-decoder"	पूर्ण,
	अणु RC_PROTO_BIT_RCMM12 |
	  RC_PROTO_BIT_RCMM24 |
	  RC_PROTO_BIT_RCMM32,	"rc-mm",	"ir-rcmm-decoder"	पूर्ण,
	अणु RC_PROTO_BIT_XBOX_DVD, "xbox-dvd",	शून्य			पूर्ण,
पूर्ण;

/**
 * काष्ठा rc_filter_attribute - Device attribute relating to a filter type.
 * @attr:	Device attribute.
 * @type:	Filter type.
 * @mask:	false क्रम filter value, true क्रम filter mask.
 */
काष्ठा rc_filter_attribute अणु
	काष्ठा device_attribute		attr;
	क्रमागत rc_filter_type		type;
	bool				mask;
पूर्ण;
#घोषणा to_rc_filter_attr(a) container_of(a, काष्ठा rc_filter_attribute, attr)

#घोषणा RC_FILTER_ATTR(_name, _mode, _show, _store, _type, _mask)	\
	काष्ठा rc_filter_attribute dev_attr_##_name = अणु			\
		.attr = __ATTR(_name, _mode, _show, _store),		\
		.type = (_type),					\
		.mask = (_mask),					\
	पूर्ण

/**
 * show_protocols() - shows the current IR protocol(s)
 * @device:	the device descriptor
 * @mattr:	the device attribute काष्ठा
 * @buf:	a poपूर्णांकer to the output buffer
 *
 * This routine is a callback routine क्रम input पढ़ो the IR protocol type(s).
 * it is triggered by पढ़ोing /sys/class/rc/rc?/protocols.
 * It वापसs the protocol names of supported protocols.
 * Enabled protocols are prपूर्णांकed in brackets.
 *
 * dev->lock is taken to guard against races between
 * store_protocols and show_protocols.
 */
अटल sमाप_प्रकार show_protocols(काष्ठा device *device,
			      काष्ठा device_attribute *mattr, अक्षर *buf)
अणु
	काष्ठा rc_dev *dev = to_rc_dev(device);
	u64 allowed, enabled;
	अक्षर *पंचांगp = buf;
	पूर्णांक i;

	mutex_lock(&dev->lock);

	enabled = dev->enabled_protocols;
	allowed = dev->allowed_protocols;
	अगर (dev->raw && !allowed)
		allowed = ir_raw_get_allowed_protocols();

	mutex_unlock(&dev->lock);

	dev_dbg(&dev->dev, "%s: allowed - 0x%llx, enabled - 0x%llx\n",
		__func__, (दीर्घ दीर्घ)allowed, (दीर्घ दीर्घ)enabled);

	क्रम (i = 0; i < ARRAY_SIZE(proto_names); i++) अणु
		अगर (allowed & enabled & proto_names[i].type)
			पंचांगp += प्र_लिखो(पंचांगp, "[%s] ", proto_names[i].name);
		अन्यथा अगर (allowed & proto_names[i].type)
			पंचांगp += प्र_लिखो(पंचांगp, "%s ", proto_names[i].name);

		अगर (allowed & proto_names[i].type)
			allowed &= ~proto_names[i].type;
	पूर्ण

#अगर_घोषित CONFIG_LIRC
	अगर (dev->driver_type == RC_DRIVER_IR_RAW)
		पंचांगp += प्र_लिखो(पंचांगp, "[lirc] ");
#पूर्ण_अगर

	अगर (पंचांगp != buf)
		पंचांगp--;
	*पंचांगp = '\n';

	वापस पंचांगp + 1 - buf;
पूर्ण

/**
 * parse_protocol_change() - parses a protocol change request
 * @dev:	rc_dev device
 * @protocols:	poपूर्णांकer to the biपंचांगask of current protocols
 * @buf:	poपूर्णांकer to the buffer with a list of changes
 *
 * Writing "+proto" will add a protocol to the protocol mask.
 * Writing "-proto" will हटाओ a protocol from protocol mask.
 * Writing "proto" will enable only "proto".
 * Writing "none" will disable all protocols.
 * Returns the number of changes perक्रमmed or a negative error code.
 */
अटल पूर्णांक parse_protocol_change(काष्ठा rc_dev *dev, u64 *protocols,
				 स्थिर अक्षर *buf)
अणु
	स्थिर अक्षर *पंचांगp;
	अचिन्हित count = 0;
	bool enable, disable;
	u64 mask;
	पूर्णांक i;

	जबतक ((पंचांगp = strsep((अक्षर **)&buf, " \n")) != शून्य) अणु
		अगर (!*पंचांगp)
			अवरोध;

		अगर (*पंचांगp == '+') अणु
			enable = true;
			disable = false;
			पंचांगp++;
		पूर्ण अन्यथा अगर (*पंचांगp == '-') अणु
			enable = false;
			disable = true;
			पंचांगp++;
		पूर्ण अन्यथा अणु
			enable = false;
			disable = false;
		पूर्ण

		क्रम (i = 0; i < ARRAY_SIZE(proto_names); i++) अणु
			अगर (!strहालcmp(पंचांगp, proto_names[i].name)) अणु
				mask = proto_names[i].type;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (i == ARRAY_SIZE(proto_names)) अणु
			अगर (!strहालcmp(पंचांगp, "lirc"))
				mask = 0;
			अन्यथा अणु
				dev_dbg(&dev->dev, "Unknown protocol: '%s'\n",
					पंचांगp);
				वापस -EINVAL;
			पूर्ण
		पूर्ण

		count++;

		अगर (enable)
			*protocols |= mask;
		अन्यथा अगर (disable)
			*protocols &= ~mask;
		अन्यथा
			*protocols = mask;
	पूर्ण

	अगर (!count) अणु
		dev_dbg(&dev->dev, "Protocol not specified\n");
		वापस -EINVAL;
	पूर्ण

	वापस count;
पूर्ण

व्योम ir_raw_load_modules(u64 *protocols)
अणु
	u64 available;
	पूर्णांक i, ret;

	क्रम (i = 0; i < ARRAY_SIZE(proto_names); i++) अणु
		अगर (proto_names[i].type == RC_PROTO_BIT_NONE ||
		    proto_names[i].type & (RC_PROTO_BIT_OTHER |
					   RC_PROTO_BIT_UNKNOWN))
			जारी;

		available = ir_raw_get_allowed_protocols();
		अगर (!(*protocols & proto_names[i].type & ~available))
			जारी;

		अगर (!proto_names[i].module_name) अणु
			pr_err("Can't enable IR protocol %s\n",
			       proto_names[i].name);
			*protocols &= ~proto_names[i].type;
			जारी;
		पूर्ण

		ret = request_module("%s", proto_names[i].module_name);
		अगर (ret < 0) अणु
			pr_err("Couldn't load IR protocol module %s\n",
			       proto_names[i].module_name);
			*protocols &= ~proto_names[i].type;
			जारी;
		पूर्ण
		msleep(20);
		available = ir_raw_get_allowed_protocols();
		अगर (!(*protocols & proto_names[i].type & ~available))
			जारी;

		pr_err("Loaded IR protocol module %s, but protocol %s still not available\n",
		       proto_names[i].module_name,
		       proto_names[i].name);
		*protocols &= ~proto_names[i].type;
	पूर्ण
पूर्ण

/**
 * store_protocols() - changes the current/wakeup IR protocol(s)
 * @device:	the device descriptor
 * @mattr:	the device attribute काष्ठा
 * @buf:	a poपूर्णांकer to the input buffer
 * @len:	length of the input buffer
 *
 * This routine is क्रम changing the IR protocol type.
 * It is triggered by writing to /sys/class/rc/rc?/[wakeup_]protocols.
 * See parse_protocol_change() क्रम the valid commands.
 * Returns @len on success or a negative error code.
 *
 * dev->lock is taken to guard against races between
 * store_protocols and show_protocols.
 */
अटल sमाप_प्रकार store_protocols(काष्ठा device *device,
			       काष्ठा device_attribute *mattr,
			       स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा rc_dev *dev = to_rc_dev(device);
	u64 *current_protocols;
	काष्ठा rc_scancode_filter *filter;
	u64 old_protocols, new_protocols;
	sमाप_प्रकार rc;

	dev_dbg(&dev->dev, "Normal protocol change requested\n");
	current_protocols = &dev->enabled_protocols;
	filter = &dev->scancode_filter;

	अगर (!dev->change_protocol) अणु
		dev_dbg(&dev->dev, "Protocol switching not supported\n");
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&dev->lock);
	अगर (!dev->रेजिस्टरed) अणु
		mutex_unlock(&dev->lock);
		वापस -ENODEV;
	पूर्ण

	old_protocols = *current_protocols;
	new_protocols = old_protocols;
	rc = parse_protocol_change(dev, &new_protocols, buf);
	अगर (rc < 0)
		जाओ out;

	अगर (dev->driver_type == RC_DRIVER_IR_RAW)
		ir_raw_load_modules(&new_protocols);

	rc = dev->change_protocol(dev, &new_protocols);
	अगर (rc < 0) अणु
		dev_dbg(&dev->dev, "Error setting protocols to 0x%llx\n",
			(दीर्घ दीर्घ)new_protocols);
		जाओ out;
	पूर्ण

	अगर (new_protocols != old_protocols) अणु
		*current_protocols = new_protocols;
		dev_dbg(&dev->dev, "Protocols changed to 0x%llx\n",
			(दीर्घ दीर्घ)new_protocols);
	पूर्ण

	/*
	 * If a protocol change was attempted the filter may need updating, even
	 * अगर the actual protocol mask hasn't changed (since the driver may have
	 * cleared the filter).
	 * Try setting the same filter with the new protocol (अगर any).
	 * Fall back to clearing the filter.
	 */
	अगर (dev->s_filter && filter->mask) अणु
		अगर (new_protocols)
			rc = dev->s_filter(dev, filter);
		अन्यथा
			rc = -1;

		अगर (rc < 0) अणु
			filter->data = 0;
			filter->mask = 0;
			dev->s_filter(dev, filter);
		पूर्ण
	पूर्ण

	rc = len;

out:
	mutex_unlock(&dev->lock);
	वापस rc;
पूर्ण

/**
 * show_filter() - shows the current scancode filter value or mask
 * @device:	the device descriptor
 * @attr:	the device attribute काष्ठा
 * @buf:	a poपूर्णांकer to the output buffer
 *
 * This routine is a callback routine to पढ़ो a scancode filter value or mask.
 * It is triggered by पढ़ोing /sys/class/rc/rc?/[wakeup_]filter[_mask].
 * It prपूर्णांकs the current scancode filter value or mask of the appropriate filter
 * type in hexadecimal पूर्णांकo @buf and वापसs the size of the buffer.
 *
 * Bits of the filter value corresponding to set bits in the filter mask are
 * compared against input scancodes and non-matching scancodes are discarded.
 *
 * dev->lock is taken to guard against races between
 * store_filter and show_filter.
 */
अटल sमाप_प्रकार show_filter(काष्ठा device *device,
			   काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा rc_dev *dev = to_rc_dev(device);
	काष्ठा rc_filter_attribute *fattr = to_rc_filter_attr(attr);
	काष्ठा rc_scancode_filter *filter;
	u32 val;

	mutex_lock(&dev->lock);

	अगर (fattr->type == RC_FILTER_NORMAL)
		filter = &dev->scancode_filter;
	अन्यथा
		filter = &dev->scancode_wakeup_filter;

	अगर (fattr->mask)
		val = filter->mask;
	अन्यथा
		val = filter->data;
	mutex_unlock(&dev->lock);

	वापस प्र_लिखो(buf, "%#x\n", val);
पूर्ण

/**
 * store_filter() - changes the scancode filter value
 * @device:	the device descriptor
 * @attr:	the device attribute काष्ठा
 * @buf:	a poपूर्णांकer to the input buffer
 * @len:	length of the input buffer
 *
 * This routine is क्रम changing a scancode filter value or mask.
 * It is triggered by writing to /sys/class/rc/rc?/[wakeup_]filter[_mask].
 * Returns -EINVAL अगर an invalid filter value क्रम the current protocol was
 * specअगरied or अगर scancode filtering is not supported by the driver, otherwise
 * वापसs @len.
 *
 * Bits of the filter value corresponding to set bits in the filter mask are
 * compared against input scancodes and non-matching scancodes are discarded.
 *
 * dev->lock is taken to guard against races between
 * store_filter and show_filter.
 */
अटल sमाप_प्रकार store_filter(काष्ठा device *device,
			    काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा rc_dev *dev = to_rc_dev(device);
	काष्ठा rc_filter_attribute *fattr = to_rc_filter_attr(attr);
	काष्ठा rc_scancode_filter new_filter, *filter;
	पूर्णांक ret;
	अचिन्हित दीर्घ val;
	पूर्णांक (*set_filter)(काष्ठा rc_dev *dev, काष्ठा rc_scancode_filter *filter);

	ret = kम_से_अदीर्घ(buf, 0, &val);
	अगर (ret < 0)
		वापस ret;

	अगर (fattr->type == RC_FILTER_NORMAL) अणु
		set_filter = dev->s_filter;
		filter = &dev->scancode_filter;
	पूर्ण अन्यथा अणु
		set_filter = dev->s_wakeup_filter;
		filter = &dev->scancode_wakeup_filter;
	पूर्ण

	अगर (!set_filter)
		वापस -EINVAL;

	mutex_lock(&dev->lock);
	अगर (!dev->रेजिस्टरed) अणु
		mutex_unlock(&dev->lock);
		वापस -ENODEV;
	पूर्ण

	new_filter = *filter;
	अगर (fattr->mask)
		new_filter.mask = val;
	अन्यथा
		new_filter.data = val;

	अगर (fattr->type == RC_FILTER_WAKEUP) अणु
		/*
		 * Refuse to set a filter unless a protocol is enabled
		 * and the filter is valid क्रम that protocol
		 */
		अगर (dev->wakeup_protocol != RC_PROTO_UNKNOWN)
			ret = rc_validate_filter(dev, &new_filter);
		अन्यथा
			ret = -EINVAL;

		अगर (ret != 0)
			जाओ unlock;
	पूर्ण

	अगर (fattr->type == RC_FILTER_NORMAL && !dev->enabled_protocols &&
	    val) अणु
		/* refuse to set a filter unless a protocol is enabled */
		ret = -EINVAL;
		जाओ unlock;
	पूर्ण

	ret = set_filter(dev, &new_filter);
	अगर (ret < 0)
		जाओ unlock;

	*filter = new_filter;

unlock:
	mutex_unlock(&dev->lock);
	वापस (ret < 0) ? ret : len;
पूर्ण

/**
 * show_wakeup_protocols() - shows the wakeup IR protocol
 * @device:	the device descriptor
 * @mattr:	the device attribute काष्ठा
 * @buf:	a poपूर्णांकer to the output buffer
 *
 * This routine is a callback routine क्रम input पढ़ो the IR protocol type(s).
 * it is triggered by पढ़ोing /sys/class/rc/rc?/wakeup_protocols.
 * It वापसs the protocol names of supported protocols.
 * The enabled protocols are prपूर्णांकed in brackets.
 *
 * dev->lock is taken to guard against races between
 * store_wakeup_protocols and show_wakeup_protocols.
 */
अटल sमाप_प्रकार show_wakeup_protocols(काष्ठा device *device,
				     काष्ठा device_attribute *mattr,
				     अक्षर *buf)
अणु
	काष्ठा rc_dev *dev = to_rc_dev(device);
	u64 allowed;
	क्रमागत rc_proto enabled;
	अक्षर *पंचांगp = buf;
	पूर्णांक i;

	mutex_lock(&dev->lock);

	allowed = dev->allowed_wakeup_protocols;
	enabled = dev->wakeup_protocol;

	mutex_unlock(&dev->lock);

	dev_dbg(&dev->dev, "%s: allowed - 0x%llx, enabled - %d\n",
		__func__, (दीर्घ दीर्घ)allowed, enabled);

	क्रम (i = 0; i < ARRAY_SIZE(protocols); i++) अणु
		अगर (allowed & (1ULL << i)) अणु
			अगर (i == enabled)
				पंचांगp += प्र_लिखो(पंचांगp, "[%s] ", protocols[i].name);
			अन्यथा
				पंचांगp += प्र_लिखो(पंचांगp, "%s ", protocols[i].name);
		पूर्ण
	पूर्ण

	अगर (पंचांगp != buf)
		पंचांगp--;
	*पंचांगp = '\n';

	वापस पंचांगp + 1 - buf;
पूर्ण

/**
 * store_wakeup_protocols() - changes the wakeup IR protocol(s)
 * @device:	the device descriptor
 * @mattr:	the device attribute काष्ठा
 * @buf:	a poपूर्णांकer to the input buffer
 * @len:	length of the input buffer
 *
 * This routine is क्रम changing the IR protocol type.
 * It is triggered by writing to /sys/class/rc/rc?/wakeup_protocols.
 * Returns @len on success or a negative error code.
 *
 * dev->lock is taken to guard against races between
 * store_wakeup_protocols and show_wakeup_protocols.
 */
अटल sमाप_प्रकार store_wakeup_protocols(काष्ठा device *device,
				      काष्ठा device_attribute *mattr,
				      स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा rc_dev *dev = to_rc_dev(device);
	क्रमागत rc_proto protocol = RC_PROTO_UNKNOWN;
	sमाप_प्रकार rc;
	u64 allowed;
	पूर्णांक i;

	mutex_lock(&dev->lock);
	अगर (!dev->रेजिस्टरed) अणु
		mutex_unlock(&dev->lock);
		वापस -ENODEV;
	पूर्ण

	allowed = dev->allowed_wakeup_protocols;

	अगर (!sysfs_streq(buf, "none")) अणु
		क्रम (i = 0; i < ARRAY_SIZE(protocols); i++) अणु
			अगर ((allowed & (1ULL << i)) &&
			    sysfs_streq(buf, protocols[i].name)) अणु
				protocol = i;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (i == ARRAY_SIZE(protocols)) अणु
			rc = -EINVAL;
			जाओ out;
		पूर्ण

		अगर (dev->encode_wakeup) अणु
			u64 mask = 1ULL << protocol;

			ir_raw_load_modules(&mask);
			अगर (!mask) अणु
				rc = -EINVAL;
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (dev->wakeup_protocol != protocol) अणु
		dev->wakeup_protocol = protocol;
		dev_dbg(&dev->dev, "Wakeup protocol changed to %d\n", protocol);

		अगर (protocol == RC_PROTO_RC6_MCE)
			dev->scancode_wakeup_filter.data = 0x800f0000;
		अन्यथा
			dev->scancode_wakeup_filter.data = 0;
		dev->scancode_wakeup_filter.mask = 0;

		rc = dev->s_wakeup_filter(dev, &dev->scancode_wakeup_filter);
		अगर (rc == 0)
			rc = len;
	पूर्ण अन्यथा अणु
		rc = len;
	पूर्ण

out:
	mutex_unlock(&dev->lock);
	वापस rc;
पूर्ण

अटल व्योम rc_dev_release(काष्ठा device *device)
अणु
	काष्ठा rc_dev *dev = to_rc_dev(device);

	kमुक्त(dev);
पूर्ण

अटल पूर्णांक rc_dev_uevent(काष्ठा device *device, काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा rc_dev *dev = to_rc_dev(device);
	पूर्णांक ret = 0;

	mutex_lock(&dev->lock);

	अगर (!dev->रेजिस्टरed)
		ret = -ENODEV;
	अगर (ret == 0 && dev->rc_map.name)
		ret = add_uevent_var(env, "NAME=%s", dev->rc_map.name);
	अगर (ret == 0 && dev->driver_name)
		ret = add_uevent_var(env, "DRV_NAME=%s", dev->driver_name);
	अगर (ret == 0 && dev->device_name)
		ret = add_uevent_var(env, "DEV_NAME=%s", dev->device_name);

	mutex_unlock(&dev->lock);

	वापस ret;
पूर्ण

/*
 * Static device attribute काष्ठा with the sysfs attributes क्रम IR's
 */
अटल काष्ठा device_attribute dev_attr_ro_protocols =
__ATTR(protocols, 0444, show_protocols, शून्य);
अटल काष्ठा device_attribute dev_attr_rw_protocols =
__ATTR(protocols, 0644, show_protocols, store_protocols);
अटल DEVICE_ATTR(wakeup_protocols, 0644, show_wakeup_protocols,
		   store_wakeup_protocols);
अटल RC_FILTER_ATTR(filter, S_IRUGO|S_IWUSR,
		      show_filter, store_filter, RC_FILTER_NORMAL, false);
अटल RC_FILTER_ATTR(filter_mask, S_IRUGO|S_IWUSR,
		      show_filter, store_filter, RC_FILTER_NORMAL, true);
अटल RC_FILTER_ATTR(wakeup_filter, S_IRUGO|S_IWUSR,
		      show_filter, store_filter, RC_FILTER_WAKEUP, false);
अटल RC_FILTER_ATTR(wakeup_filter_mask, S_IRUGO|S_IWUSR,
		      show_filter, store_filter, RC_FILTER_WAKEUP, true);

अटल काष्ठा attribute *rc_dev_rw_protocol_attrs[] = अणु
	&dev_attr_rw_protocols.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group rc_dev_rw_protocol_attr_grp = अणु
	.attrs	= rc_dev_rw_protocol_attrs,
पूर्ण;

अटल काष्ठा attribute *rc_dev_ro_protocol_attrs[] = अणु
	&dev_attr_ro_protocols.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group rc_dev_ro_protocol_attr_grp = अणु
	.attrs	= rc_dev_ro_protocol_attrs,
पूर्ण;

अटल काष्ठा attribute *rc_dev_filter_attrs[] = अणु
	&dev_attr_filter.attr.attr,
	&dev_attr_filter_mask.attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group rc_dev_filter_attr_grp = अणु
	.attrs	= rc_dev_filter_attrs,
पूर्ण;

अटल काष्ठा attribute *rc_dev_wakeup_filter_attrs[] = अणु
	&dev_attr_wakeup_filter.attr.attr,
	&dev_attr_wakeup_filter_mask.attr.attr,
	&dev_attr_wakeup_protocols.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group rc_dev_wakeup_filter_attr_grp = अणु
	.attrs	= rc_dev_wakeup_filter_attrs,
पूर्ण;

अटल स्थिर काष्ठा device_type rc_dev_type = अणु
	.release	= rc_dev_release,
	.uevent		= rc_dev_uevent,
पूर्ण;

काष्ठा rc_dev *rc_allocate_device(क्रमागत rc_driver_type type)
अणु
	काष्ठा rc_dev *dev;

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस शून्य;

	अगर (type != RC_DRIVER_IR_RAW_TX) अणु
		dev->input_dev = input_allocate_device();
		अगर (!dev->input_dev) अणु
			kमुक्त(dev);
			वापस शून्य;
		पूर्ण

		dev->input_dev->getkeycode = ir_getkeycode;
		dev->input_dev->setkeycode = ir_setkeycode;
		input_set_drvdata(dev->input_dev, dev);

		dev->समयout = IR_DEFAULT_TIMEOUT;
		समयr_setup(&dev->समयr_keyup, ir_समयr_keyup, 0);
		समयr_setup(&dev->समयr_repeat, ir_समयr_repeat, 0);

		spin_lock_init(&dev->rc_map.lock);
		spin_lock_init(&dev->keylock);
	पूर्ण
	mutex_init(&dev->lock);

	dev->dev.type = &rc_dev_type;
	dev->dev.class = &rc_class;
	device_initialize(&dev->dev);

	dev->driver_type = type;

	__module_get(THIS_MODULE);
	वापस dev;
पूर्ण
EXPORT_SYMBOL_GPL(rc_allocate_device);

व्योम rc_मुक्त_device(काष्ठा rc_dev *dev)
अणु
	अगर (!dev)
		वापस;

	input_मुक्त_device(dev->input_dev);

	put_device(&dev->dev);

	/* kमुक्त(dev) will be called by the callback function
	   rc_dev_release() */

	module_put(THIS_MODULE);
पूर्ण
EXPORT_SYMBOL_GPL(rc_मुक्त_device);

अटल व्योम devm_rc_alloc_release(काष्ठा device *dev, व्योम *res)
अणु
	rc_मुक्त_device(*(काष्ठा rc_dev **)res);
पूर्ण

काष्ठा rc_dev *devm_rc_allocate_device(काष्ठा device *dev,
				       क्रमागत rc_driver_type type)
अणु
	काष्ठा rc_dev **dr, *rc;

	dr = devres_alloc(devm_rc_alloc_release, माप(*dr), GFP_KERNEL);
	अगर (!dr)
		वापस शून्य;

	rc = rc_allocate_device(type);
	अगर (!rc) अणु
		devres_मुक्त(dr);
		वापस शून्य;
	पूर्ण

	rc->dev.parent = dev;
	rc->managed_alloc = true;
	*dr = rc;
	devres_add(dev, dr);

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(devm_rc_allocate_device);

अटल पूर्णांक rc_prepare_rx_device(काष्ठा rc_dev *dev)
अणु
	पूर्णांक rc;
	काष्ठा rc_map *rc_map;
	u64 rc_proto;

	अगर (!dev->map_name)
		वापस -EINVAL;

	rc_map = rc_map_get(dev->map_name);
	अगर (!rc_map)
		rc_map = rc_map_get(RC_MAP_EMPTY);
	अगर (!rc_map || !rc_map->scan || rc_map->size == 0)
		वापस -EINVAL;

	rc = ir_setkeytable(dev, rc_map);
	अगर (rc)
		वापस rc;

	rc_proto = BIT_ULL(rc_map->rc_proto);

	अगर (dev->driver_type == RC_DRIVER_SCANCODE && !dev->change_protocol)
		dev->enabled_protocols = dev->allowed_protocols;

	अगर (dev->driver_type == RC_DRIVER_IR_RAW)
		ir_raw_load_modules(&rc_proto);

	अगर (dev->change_protocol) अणु
		rc = dev->change_protocol(dev, &rc_proto);
		अगर (rc < 0)
			जाओ out_table;
		dev->enabled_protocols = rc_proto;
	पूर्ण

	/* Keyboard events */
	set_bit(EV_KEY, dev->input_dev->evbit);
	set_bit(EV_REP, dev->input_dev->evbit);
	set_bit(EV_MSC, dev->input_dev->evbit);
	set_bit(MSC_SCAN, dev->input_dev->mscbit);

	/* Poपूर्णांकer/mouse events */
	set_bit(INPUT_PROP_POINTING_STICK, dev->input_dev->propbit);
	set_bit(EV_REL, dev->input_dev->evbit);
	set_bit(REL_X, dev->input_dev->relbit);
	set_bit(REL_Y, dev->input_dev->relbit);

	अगर (dev->खोलो)
		dev->input_dev->खोलो = ir_खोलो;
	अगर (dev->बंद)
		dev->input_dev->बंद = ir_बंद;

	dev->input_dev->dev.parent = &dev->dev;
	स_नकल(&dev->input_dev->id, &dev->input_id, माप(dev->input_id));
	dev->input_dev->phys = dev->input_phys;
	dev->input_dev->name = dev->device_name;

	वापस 0;

out_table:
	ir_मुक्त_table(&dev->rc_map);

	वापस rc;
पूर्ण

अटल पूर्णांक rc_setup_rx_device(काष्ठा rc_dev *dev)
अणु
	पूर्णांक rc;

	/* rc_खोलो will be called here */
	rc = input_रेजिस्टर_device(dev->input_dev);
	अगर (rc)
		वापस rc;

	/*
	 * Default delay of 250ms is too लघु क्रम some protocols, especially
	 * since the समयout is currently set to 250ms. Increase it to 500ms,
	 * to aव्योम wrong repetition of the keycodes. Note that this must be
	 * set after the call to input_रेजिस्टर_device().
	 */
	अगर (dev->allowed_protocols == RC_PROTO_BIT_CEC)
		dev->input_dev->rep[REP_DELAY] = 0;
	अन्यथा
		dev->input_dev->rep[REP_DELAY] = 500;

	/*
	 * As a repeat event on protocols like RC-5 and NEC take as दीर्घ as
	 * 110/114ms, using 33ms as a repeat period is not the right thing
	 * to करो.
	 */
	dev->input_dev->rep[REP_PERIOD] = 125;

	वापस 0;
पूर्ण

अटल व्योम rc_मुक्त_rx_device(काष्ठा rc_dev *dev)
अणु
	अगर (!dev)
		वापस;

	अगर (dev->input_dev) अणु
		input_unरेजिस्टर_device(dev->input_dev);
		dev->input_dev = शून्य;
	पूर्ण

	ir_मुक्त_table(&dev->rc_map);
पूर्ण

पूर्णांक rc_रेजिस्टर_device(काष्ठा rc_dev *dev)
अणु
	स्थिर अक्षर *path;
	पूर्णांक attr = 0;
	पूर्णांक minor;
	पूर्णांक rc;

	अगर (!dev)
		वापस -EINVAL;

	minor = ida_simple_get(&rc_ida, 0, RC_DEV_MAX, GFP_KERNEL);
	अगर (minor < 0)
		वापस minor;

	dev->minor = minor;
	dev_set_name(&dev->dev, "rc%u", dev->minor);
	dev_set_drvdata(&dev->dev, dev);

	dev->dev.groups = dev->sysfs_groups;
	अगर (dev->driver_type == RC_DRIVER_SCANCODE && !dev->change_protocol)
		dev->sysfs_groups[attr++] = &rc_dev_ro_protocol_attr_grp;
	अन्यथा अगर (dev->driver_type != RC_DRIVER_IR_RAW_TX)
		dev->sysfs_groups[attr++] = &rc_dev_rw_protocol_attr_grp;
	अगर (dev->s_filter)
		dev->sysfs_groups[attr++] = &rc_dev_filter_attr_grp;
	अगर (dev->s_wakeup_filter)
		dev->sysfs_groups[attr++] = &rc_dev_wakeup_filter_attr_grp;
	dev->sysfs_groups[attr++] = शून्य;

	अगर (dev->driver_type == RC_DRIVER_IR_RAW) अणु
		rc = ir_raw_event_prepare(dev);
		अगर (rc < 0)
			जाओ out_minor;
	पूर्ण

	अगर (dev->driver_type != RC_DRIVER_IR_RAW_TX) अणु
		rc = rc_prepare_rx_device(dev);
		अगर (rc)
			जाओ out_raw;
	पूर्ण

	dev->रेजिस्टरed = true;

	rc = device_add(&dev->dev);
	अगर (rc)
		जाओ out_rx_मुक्त;

	path = kobject_get_path(&dev->dev.kobj, GFP_KERNEL);
	dev_info(&dev->dev, "%s as %s\n",
		 dev->device_name ?: "Unspecified device", path ?: "N/A");
	kमुक्त(path);

	/*
	 * once the the input device is रेजिस्टरed in rc_setup_rx_device,
	 * userspace can खोलो the input device and rc_खोलो() will be called
	 * as a result. This results in driver code being allowed to submit
	 * keycodes with rc_keyकरोwn, so lirc must be रेजिस्टरed first.
	 */
	अगर (dev->allowed_protocols != RC_PROTO_BIT_CEC) अणु
		rc = lirc_रेजिस्टर(dev);
		अगर (rc < 0)
			जाओ out_dev;
	पूर्ण

	अगर (dev->driver_type != RC_DRIVER_IR_RAW_TX) अणु
		rc = rc_setup_rx_device(dev);
		अगर (rc)
			जाओ out_lirc;
	पूर्ण

	अगर (dev->driver_type == RC_DRIVER_IR_RAW) अणु
		rc = ir_raw_event_रेजिस्टर(dev);
		अगर (rc < 0)
			जाओ out_rx;
	पूर्ण

	dev_dbg(&dev->dev, "Registered rc%u (driver: %s)\n", dev->minor,
		dev->driver_name ? dev->driver_name : "unknown");

	वापस 0;

out_rx:
	rc_मुक्त_rx_device(dev);
out_lirc:
	अगर (dev->allowed_protocols != RC_PROTO_BIT_CEC)
		lirc_unरेजिस्टर(dev);
out_dev:
	device_del(&dev->dev);
out_rx_मुक्त:
	ir_मुक्त_table(&dev->rc_map);
out_raw:
	ir_raw_event_मुक्त(dev);
out_minor:
	ida_simple_हटाओ(&rc_ida, minor);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(rc_रेजिस्टर_device);

अटल व्योम devm_rc_release(काष्ठा device *dev, व्योम *res)
अणु
	rc_unरेजिस्टर_device(*(काष्ठा rc_dev **)res);
पूर्ण

पूर्णांक devm_rc_रेजिस्टर_device(काष्ठा device *parent, काष्ठा rc_dev *dev)
अणु
	काष्ठा rc_dev **dr;
	पूर्णांक ret;

	dr = devres_alloc(devm_rc_release, माप(*dr), GFP_KERNEL);
	अगर (!dr)
		वापस -ENOMEM;

	ret = rc_रेजिस्टर_device(dev);
	अगर (ret) अणु
		devres_मुक्त(dr);
		वापस ret;
	पूर्ण

	*dr = dev;
	devres_add(parent, dr);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(devm_rc_रेजिस्टर_device);

व्योम rc_unरेजिस्टर_device(काष्ठा rc_dev *dev)
अणु
	अगर (!dev)
		वापस;

	अगर (dev->driver_type == RC_DRIVER_IR_RAW)
		ir_raw_event_unरेजिस्टर(dev);

	del_समयr_sync(&dev->समयr_keyup);
	del_समयr_sync(&dev->समयr_repeat);

	mutex_lock(&dev->lock);
	अगर (dev->users && dev->बंद)
		dev->बंद(dev);
	dev->रेजिस्टरed = false;
	mutex_unlock(&dev->lock);

	rc_मुक्त_rx_device(dev);

	/*
	 * lirc device should be मुक्तd with dev->रेजिस्टरed = false, so
	 * that userspace polling will get notअगरied.
	 */
	अगर (dev->allowed_protocols != RC_PROTO_BIT_CEC)
		lirc_unरेजिस्टर(dev);

	device_del(&dev->dev);

	ida_simple_हटाओ(&rc_ida, dev->minor);

	अगर (!dev->managed_alloc)
		rc_मुक्त_device(dev);
पूर्ण

EXPORT_SYMBOL_GPL(rc_unरेजिस्टर_device);

/*
 * Init/निकास code क्रम the module. Basically, creates/हटाओs /sys/class/rc
 */

अटल पूर्णांक __init rc_core_init(व्योम)
अणु
	पूर्णांक rc = class_रेजिस्टर(&rc_class);
	अगर (rc) अणु
		pr_err("rc_core: unable to register rc class\n");
		वापस rc;
	पूर्ण

	rc = lirc_dev_init();
	अगर (rc) अणु
		pr_err("rc_core: unable to init lirc\n");
		class_unरेजिस्टर(&rc_class);
		वापस rc;
	पूर्ण

	led_trigger_रेजिस्टर_simple("rc-feedback", &led_feedback);
	rc_map_रेजिस्टर(&empty_map);
#अगर_घोषित CONFIG_MEDIA_CEC_RC
	rc_map_रेजिस्टर(&cec_map);
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल व्योम __निकास rc_core_निकास(व्योम)
अणु
	lirc_dev_निकास();
	class_unरेजिस्टर(&rc_class);
	led_trigger_unरेजिस्टर_simple(led_feedback);
#अगर_घोषित CONFIG_MEDIA_CEC_RC
	rc_map_unरेजिस्टर(&cec_map);
#पूर्ण_अगर
	rc_map_unरेजिस्टर(&empty_map);
पूर्ण

subsys_initcall(rc_core_init);
module_निकास(rc_core_निकास);

MODULE_AUTHOR("Mauro Carvalho Chehab");
MODULE_LICENSE("GPL v2");
