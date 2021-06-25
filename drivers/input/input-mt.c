<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Input Multitouch Library
 *
 * Copyright (c) 2008-2010 Henrik Rydberg
 */

#समावेश <linux/input/mt.h>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>

#घोषणा TRKID_SGN	((TRKID_MAX + 1) >> 1)

अटल व्योम copy_असल(काष्ठा input_dev *dev, अचिन्हित पूर्णांक dst, अचिन्हित पूर्णांक src)
अणु
	अगर (dev->असलinfo && test_bit(src, dev->असलbit)) अणु
		dev->असलinfo[dst] = dev->असलinfo[src];
		dev->असलinfo[dst].fuzz = 0;
		__set_bit(dst, dev->असलbit);
	पूर्ण
पूर्ण

/**
 * input_mt_init_slots() - initialize MT input slots
 * @dev: input device supporting MT events and finger tracking
 * @num_slots: number of slots used by the device
 * @flags: mt tasks to handle in core
 *
 * This function allocates all necessary memory क्रम MT slot handling
 * in the input device, prepares the ABS_MT_SLOT and
 * ABS_MT_TRACKING_ID events क्रम use and sets up appropriate buffers.
 * Depending on the flags set, it also perक्रमms poपूर्णांकer emulation and
 * frame synchronization.
 *
 * May be called repeatedly. Returns -EINVAL अगर attempting to
 * reinitialize with a dअगरferent number of slots.
 */
पूर्णांक input_mt_init_slots(काष्ठा input_dev *dev, अचिन्हित पूर्णांक num_slots,
			अचिन्हित पूर्णांक flags)
अणु
	काष्ठा input_mt *mt = dev->mt;
	पूर्णांक i;

	अगर (!num_slots)
		वापस 0;
	अगर (mt)
		वापस mt->num_slots != num_slots ? -EINVAL : 0;

	mt = kzalloc(काष्ठा_size(mt, slots, num_slots), GFP_KERNEL);
	अगर (!mt)
		जाओ err_mem;

	mt->num_slots = num_slots;
	mt->flags = flags;
	input_set_असल_params(dev, ABS_MT_SLOT, 0, num_slots - 1, 0, 0);
	input_set_असल_params(dev, ABS_MT_TRACKING_ID, 0, TRKID_MAX, 0, 0);

	अगर (flags & (INPUT_MT_POINTER | INPUT_MT_सूचीECT)) अणु
		__set_bit(EV_KEY, dev->evbit);
		__set_bit(BTN_TOUCH, dev->keybit);

		copy_असल(dev, ABS_X, ABS_MT_POSITION_X);
		copy_असल(dev, ABS_Y, ABS_MT_POSITION_Y);
		copy_असल(dev, ABS_PRESSURE, ABS_MT_PRESSURE);
	पूर्ण
	अगर (flags & INPUT_MT_POINTER) अणु
		__set_bit(BTN_TOOL_FINGER, dev->keybit);
		__set_bit(BTN_TOOL_DOUBLETAP, dev->keybit);
		अगर (num_slots >= 3)
			__set_bit(BTN_TOOL_TRIPLETAP, dev->keybit);
		अगर (num_slots >= 4)
			__set_bit(BTN_TOOL_QUADTAP, dev->keybit);
		अगर (num_slots >= 5)
			__set_bit(BTN_TOOL_QUINTTAP, dev->keybit);
		__set_bit(INPUT_PROP_POINTER, dev->propbit);
	पूर्ण
	अगर (flags & INPUT_MT_सूचीECT)
		__set_bit(INPUT_PROP_सूचीECT, dev->propbit);
	अगर (flags & INPUT_MT_SEMI_MT)
		__set_bit(INPUT_PROP_SEMI_MT, dev->propbit);
	अगर (flags & INPUT_MT_TRACK) अणु
		अचिन्हित पूर्णांक n2 = num_slots * num_slots;
		mt->red = kसुस्मृति(n2, माप(*mt->red), GFP_KERNEL);
		अगर (!mt->red)
			जाओ err_mem;
	पूर्ण

	/* Mark slots as 'inactive' */
	क्रम (i = 0; i < num_slots; i++)
		input_mt_set_value(&mt->slots[i], ABS_MT_TRACKING_ID, -1);

	/* Mark slots as 'unused' */
	mt->frame = 1;

	dev->mt = mt;
	वापस 0;
err_mem:
	kमुक्त(mt);
	वापस -ENOMEM;
पूर्ण
EXPORT_SYMBOL(input_mt_init_slots);

/**
 * input_mt_destroy_slots() - मुक्तs the MT slots of the input device
 * @dev: input device with allocated MT slots
 *
 * This function is only needed in error path as the input core will
 * स्वतःmatically मुक्त the MT slots when the device is destroyed.
 */
व्योम input_mt_destroy_slots(काष्ठा input_dev *dev)
अणु
	अगर (dev->mt) अणु
		kमुक्त(dev->mt->red);
		kमुक्त(dev->mt);
	पूर्ण
	dev->mt = शून्य;
पूर्ण
EXPORT_SYMBOL(input_mt_destroy_slots);

/**
 * input_mt_report_slot_state() - report contact state
 * @dev: input device with allocated MT slots
 * @tool_type: the tool type to use in this slot
 * @active: true अगर contact is active, false otherwise
 *
 * Reports a contact via ABS_MT_TRACKING_ID, and optionally
 * ABS_MT_TOOL_TYPE. If active is true and the slot is currently
 * inactive, or अगर the tool type is changed, a new tracking id is
 * asचिन्हित to the slot. The tool type is only reported अगर the
 * corresponding असलbit field is set.
 *
 * Returns true अगर contact is active.
 */
bool input_mt_report_slot_state(काष्ठा input_dev *dev,
				अचिन्हित पूर्णांक tool_type, bool active)
अणु
	काष्ठा input_mt *mt = dev->mt;
	काष्ठा input_mt_slot *slot;
	पूर्णांक id;

	अगर (!mt)
		वापस false;

	slot = &mt->slots[mt->slot];
	slot->frame = mt->frame;

	अगर (!active) अणु
		input_event(dev, EV_ABS, ABS_MT_TRACKING_ID, -1);
		वापस false;
	पूर्ण

	id = input_mt_get_value(slot, ABS_MT_TRACKING_ID);
	अगर (id < 0)
		id = input_mt_new_trkid(mt);

	input_event(dev, EV_ABS, ABS_MT_TRACKING_ID, id);
	input_event(dev, EV_ABS, ABS_MT_TOOL_TYPE, tool_type);

	वापस true;
पूर्ण
EXPORT_SYMBOL(input_mt_report_slot_state);

/**
 * input_mt_report_finger_count() - report contact count
 * @dev: input device with allocated MT slots
 * @count: the number of contacts
 *
 * Reports the contact count via BTN_TOOL_FINGER, BTN_TOOL_DOUBLETAP,
 * BTN_TOOL_TRIPLETAP and BTN_TOOL_QUADTAP.
 *
 * The input core ensures only the KEY events alपढ़ोy setup क्रम
 * this device will produce output.
 */
व्योम input_mt_report_finger_count(काष्ठा input_dev *dev, पूर्णांक count)
अणु
	input_event(dev, EV_KEY, BTN_TOOL_FINGER, count == 1);
	input_event(dev, EV_KEY, BTN_TOOL_DOUBLETAP, count == 2);
	input_event(dev, EV_KEY, BTN_TOOL_TRIPLETAP, count == 3);
	input_event(dev, EV_KEY, BTN_TOOL_QUADTAP, count == 4);
	input_event(dev, EV_KEY, BTN_TOOL_QUINTTAP, count == 5);
पूर्ण
EXPORT_SYMBOL(input_mt_report_finger_count);

/**
 * input_mt_report_poपूर्णांकer_emulation() - common poपूर्णांकer emulation
 * @dev: input device with allocated MT slots
 * @use_count: report number of active contacts as finger count
 *
 * Perक्रमms legacy poपूर्णांकer emulation via BTN_TOUCH, ABS_X, ABS_Y and
 * ABS_PRESSURE. Touchpad finger count is emulated अगर use_count is true.
 *
 * The input core ensures only the KEY and ABS axes alपढ़ोy setup क्रम
 * this device will produce output.
 */
व्योम input_mt_report_poपूर्णांकer_emulation(काष्ठा input_dev *dev, bool use_count)
अणु
	काष्ठा input_mt *mt = dev->mt;
	काष्ठा input_mt_slot *oldest;
	पूर्णांक oldid, count, i;

	अगर (!mt)
		वापस;

	oldest = शून्य;
	oldid = mt->trkid;
	count = 0;

	क्रम (i = 0; i < mt->num_slots; ++i) अणु
		काष्ठा input_mt_slot *ps = &mt->slots[i];
		पूर्णांक id = input_mt_get_value(ps, ABS_MT_TRACKING_ID);

		अगर (id < 0)
			जारी;
		अगर ((id - oldid) & TRKID_SGN) अणु
			oldest = ps;
			oldid = id;
		पूर्ण
		count++;
	पूर्ण

	input_event(dev, EV_KEY, BTN_TOUCH, count > 0);

	अगर (use_count) अणु
		अगर (count == 0 &&
		    !test_bit(ABS_MT_DISTANCE, dev->असलbit) &&
		    test_bit(ABS_DISTANCE, dev->असलbit) &&
		    input_असल_get_val(dev, ABS_DISTANCE) != 0) अणु
			/*
			 * Force reporting BTN_TOOL_FINGER क्रम devices that
			 * only report general hover (and not per-contact
			 * distance) when contact is in proximity but not
			 * on the surface.
			 */
			count = 1;
		पूर्ण

		input_mt_report_finger_count(dev, count);
	पूर्ण

	अगर (oldest) अणु
		पूर्णांक x = input_mt_get_value(oldest, ABS_MT_POSITION_X);
		पूर्णांक y = input_mt_get_value(oldest, ABS_MT_POSITION_Y);

		input_event(dev, EV_ABS, ABS_X, x);
		input_event(dev, EV_ABS, ABS_Y, y);

		अगर (test_bit(ABS_MT_PRESSURE, dev->असलbit)) अणु
			पूर्णांक p = input_mt_get_value(oldest, ABS_MT_PRESSURE);
			input_event(dev, EV_ABS, ABS_PRESSURE, p);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (test_bit(ABS_MT_PRESSURE, dev->असलbit))
			input_event(dev, EV_ABS, ABS_PRESSURE, 0);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(input_mt_report_poपूर्णांकer_emulation);

अटल व्योम __input_mt_drop_unused(काष्ठा input_dev *dev, काष्ठा input_mt *mt)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < mt->num_slots; i++) अणु
		अगर (!input_mt_is_used(mt, &mt->slots[i])) अणु
			input_mt_slot(dev, i);
			input_event(dev, EV_ABS, ABS_MT_TRACKING_ID, -1);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * input_mt_drop_unused() - Inactivate slots not seen in this frame
 * @dev: input device with allocated MT slots
 *
 * Lअगरt all slots not seen since the last call to this function.
 */
व्योम input_mt_drop_unused(काष्ठा input_dev *dev)
अणु
	काष्ठा input_mt *mt = dev->mt;

	अगर (mt) अणु
		__input_mt_drop_unused(dev, mt);
		mt->frame++;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(input_mt_drop_unused);

/**
 * input_mt_sync_frame() - synchronize mt frame
 * @dev: input device with allocated MT slots
 *
 * Close the frame and prepare the पूर्णांकernal state क्रम a new one.
 * Depending on the flags, marks unused slots as inactive and perक्रमms
 * poपूर्णांकer emulation.
 */
व्योम input_mt_sync_frame(काष्ठा input_dev *dev)
अणु
	काष्ठा input_mt *mt = dev->mt;
	bool use_count = false;

	अगर (!mt)
		वापस;

	अगर (mt->flags & INPUT_MT_DROP_UNUSED)
		__input_mt_drop_unused(dev, mt);

	अगर ((mt->flags & INPUT_MT_POINTER) && !(mt->flags & INPUT_MT_SEMI_MT))
		use_count = true;

	input_mt_report_poपूर्णांकer_emulation(dev, use_count);

	mt->frame++;
पूर्ण
EXPORT_SYMBOL(input_mt_sync_frame);

अटल पूर्णांक adjust_dual(पूर्णांक *begin, पूर्णांक step, पूर्णांक *end, पूर्णांक eq, पूर्णांक mu)
अणु
	पूर्णांक f, *p, s, c;

	अगर (begin == end)
		वापस 0;

	f = *begin;
	p = begin + step;
	s = p == end ? f + 1 : *p;

	क्रम (; p != end; p += step) अणु
		अगर (*p < f) अणु
			s = f;
			f = *p;
		पूर्ण अन्यथा अगर (*p < s) अणु
			s = *p;
		पूर्ण
	पूर्ण

	c = (f + s + 1) / 2;
	अगर (c == 0 || (c > mu && (!eq || mu > 0)))
		वापस 0;
	/* Improve convergence क्रम positive matrices by penalizing overcovers */
	अगर (s < 0 && mu <= 0)
		c *= 2;

	क्रम (p = begin; p != end; p += step)
		*p -= c;

	वापस (c < s && s <= 0) || (f >= 0 && f < c);
पूर्ण

अटल व्योम find_reduced_matrix(पूर्णांक *w, पूर्णांक nr, पूर्णांक nc, पूर्णांक nrc, पूर्णांक mu)
अणु
	पूर्णांक i, k, sum;

	क्रम (k = 0; k < nrc; k++) अणु
		क्रम (i = 0; i < nr; i++)
			adjust_dual(w + i, nr, w + i + nrc, nr <= nc, mu);
		sum = 0;
		क्रम (i = 0; i < nrc; i += nr)
			sum += adjust_dual(w + i, 1, w + i + nr, nc <= nr, mu);
		अगर (!sum)
			अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक input_mt_set_matrix(काष्ठा input_mt *mt,
			       स्थिर काष्ठा input_mt_pos *pos, पूर्णांक num_pos,
			       पूर्णांक mu)
अणु
	स्थिर काष्ठा input_mt_pos *p;
	काष्ठा input_mt_slot *s;
	पूर्णांक *w = mt->red;
	पूर्णांक x, y;

	क्रम (s = mt->slots; s != mt->slots + mt->num_slots; s++) अणु
		अगर (!input_mt_is_active(s))
			जारी;
		x = input_mt_get_value(s, ABS_MT_POSITION_X);
		y = input_mt_get_value(s, ABS_MT_POSITION_Y);
		क्रम (p = pos; p != pos + num_pos; p++) अणु
			पूर्णांक dx = x - p->x, dy = y - p->y;
			*w++ = dx * dx + dy * dy - mu;
		पूर्ण
	पूर्ण

	वापस w - mt->red;
पूर्ण

अटल व्योम input_mt_set_slots(काष्ठा input_mt *mt,
			       पूर्णांक *slots, पूर्णांक num_pos)
अणु
	काष्ठा input_mt_slot *s;
	पूर्णांक *w = mt->red, j;

	क्रम (j = 0; j != num_pos; j++)
		slots[j] = -1;

	क्रम (s = mt->slots; s != mt->slots + mt->num_slots; s++) अणु
		अगर (!input_mt_is_active(s))
			जारी;

		क्रम (j = 0; j != num_pos; j++) अणु
			अगर (w[j] < 0) अणु
				slots[j] = s - mt->slots;
				अवरोध;
			पूर्ण
		पूर्ण

		w += num_pos;
	पूर्ण

	क्रम (s = mt->slots; s != mt->slots + mt->num_slots; s++) अणु
		अगर (input_mt_is_active(s))
			जारी;

		क्रम (j = 0; j != num_pos; j++) अणु
			अगर (slots[j] < 0) अणु
				slots[j] = s - mt->slots;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/**
 * input_mt_assign_slots() - perक्रमm a best-match assignment
 * @dev: input device with allocated MT slots
 * @slots: the slot assignment to be filled
 * @pos: the position array to match
 * @num_pos: number of positions
 * @dmax: maximum ABS_MT_POSITION displacement (zero क्रम infinite)
 *
 * Perक्रमms a best match against the current contacts and वापसs
 * the slot assignment list. New contacts are asचिन्हित to unused
 * slots.
 *
 * The assignments are balanced so that all coordinate displacements are
 * below the euclidian distance dmax. If no such assignment can be found,
 * some contacts are asचिन्हित to unused slots.
 *
 * Returns zero on success, or negative error in हाल of failure.
 */
पूर्णांक input_mt_assign_slots(काष्ठा input_dev *dev, पूर्णांक *slots,
			  स्थिर काष्ठा input_mt_pos *pos, पूर्णांक num_pos,
			  पूर्णांक dmax)
अणु
	काष्ठा input_mt *mt = dev->mt;
	पूर्णांक mu = 2 * dmax * dmax;
	पूर्णांक nrc;

	अगर (!mt || !mt->red)
		वापस -ENXIO;
	अगर (num_pos > mt->num_slots)
		वापस -EINVAL;
	अगर (num_pos < 1)
		वापस 0;

	nrc = input_mt_set_matrix(mt, pos, num_pos, mu);
	find_reduced_matrix(mt->red, num_pos, nrc / num_pos, nrc, mu);
	input_mt_set_slots(mt, slots, num_pos);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(input_mt_assign_slots);

/**
 * input_mt_get_slot_by_key() - वापस slot matching key
 * @dev: input device with allocated MT slots
 * @key: the key of the sought slot
 *
 * Returns the slot of the given key, अगर it exists, otherwise
 * set the key on the first unused slot and वापस.
 *
 * If no available slot can be found, -1 is वापसed.
 * Note that क्रम this function to work properly, input_mt_sync_frame() has
 * to be called at each frame.
 */
पूर्णांक input_mt_get_slot_by_key(काष्ठा input_dev *dev, पूर्णांक key)
अणु
	काष्ठा input_mt *mt = dev->mt;
	काष्ठा input_mt_slot *s;

	अगर (!mt)
		वापस -1;

	क्रम (s = mt->slots; s != mt->slots + mt->num_slots; s++)
		अगर (input_mt_is_active(s) && s->key == key)
			वापस s - mt->slots;

	क्रम (s = mt->slots; s != mt->slots + mt->num_slots; s++)
		अगर (!input_mt_is_active(s) && !input_mt_is_used(mt, s)) अणु
			s->key = key;
			वापस s - mt->slots;
		पूर्ण

	वापस -1;
पूर्ण
EXPORT_SYMBOL(input_mt_get_slot_by_key);
