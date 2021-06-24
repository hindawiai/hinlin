<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
#अगर_अघोषित _INPUT_MT_H
#घोषणा _INPUT_MT_H

/*
 * Input Multitouch Library
 *
 * Copyright (c) 2010 Henrik Rydberg
 */

#समावेश <linux/input.h>

#घोषणा TRKID_MAX	0xffff

#घोषणा INPUT_MT_POINTER	0x0001	/* poपूर्णांकer device, e.g. trackpad */
#घोषणा INPUT_MT_सूचीECT		0x0002	/* direct device, e.g. touchscreen */
#घोषणा INPUT_MT_DROP_UNUSED	0x0004	/* drop contacts not seen in frame */
#घोषणा INPUT_MT_TRACK		0x0008	/* use in-kernel tracking */
#घोषणा INPUT_MT_SEMI_MT	0x0010	/* semi-mt device, finger count handled manually */

/**
 * काष्ठा input_mt_slot - represents the state of an input MT slot
 * @असल: holds current values of ABS_MT axes क्रम this slot
 * @frame: last frame at which input_mt_report_slot_state() was called
 * @key: optional driver designation of this slot
 */
काष्ठा input_mt_slot अणु
	पूर्णांक असल[ABS_MT_LAST - ABS_MT_FIRST + 1];
	अचिन्हित पूर्णांक frame;
	अचिन्हित पूर्णांक key;
पूर्ण;

/**
 * काष्ठा input_mt - state of tracked contacts
 * @trkid: stores MT tracking ID क्रम the next contact
 * @num_slots: number of MT slots the device uses
 * @slot: MT slot currently being transmitted
 * @flags: input_mt operation flags
 * @frame: increases every समय input_mt_sync_frame() is called
 * @red: reduced cost matrix क्रम in-kernel tracking
 * @slots: array of slots holding current values of tracked contacts
 */
काष्ठा input_mt अणु
	पूर्णांक trkid;
	पूर्णांक num_slots;
	पूर्णांक slot;
	अचिन्हित पूर्णांक flags;
	अचिन्हित पूर्णांक frame;
	पूर्णांक *red;
	काष्ठा input_mt_slot slots[];
पूर्ण;

अटल अंतरभूत व्योम input_mt_set_value(काष्ठा input_mt_slot *slot,
				      अचिन्हित code, पूर्णांक value)
अणु
	slot->असल[code - ABS_MT_FIRST] = value;
पूर्ण

अटल अंतरभूत पूर्णांक input_mt_get_value(स्थिर काष्ठा input_mt_slot *slot,
				     अचिन्हित code)
अणु
	वापस slot->असल[code - ABS_MT_FIRST];
पूर्ण

अटल अंतरभूत bool input_mt_is_active(स्थिर काष्ठा input_mt_slot *slot)
अणु
	वापस input_mt_get_value(slot, ABS_MT_TRACKING_ID) >= 0;
पूर्ण

अटल अंतरभूत bool input_mt_is_used(स्थिर काष्ठा input_mt *mt,
				    स्थिर काष्ठा input_mt_slot *slot)
अणु
	वापस slot->frame == mt->frame;
पूर्ण

पूर्णांक input_mt_init_slots(काष्ठा input_dev *dev, अचिन्हित पूर्णांक num_slots,
			अचिन्हित पूर्णांक flags);
व्योम input_mt_destroy_slots(काष्ठा input_dev *dev);

अटल अंतरभूत पूर्णांक input_mt_new_trkid(काष्ठा input_mt *mt)
अणु
	वापस mt->trkid++ & TRKID_MAX;
पूर्ण

अटल अंतरभूत व्योम input_mt_slot(काष्ठा input_dev *dev, पूर्णांक slot)
अणु
	input_event(dev, EV_ABS, ABS_MT_SLOT, slot);
पूर्ण

अटल अंतरभूत bool input_is_mt_value(पूर्णांक axis)
अणु
	वापस axis >= ABS_MT_FIRST && axis <= ABS_MT_LAST;
पूर्ण

अटल अंतरभूत bool input_is_mt_axis(पूर्णांक axis)
अणु
	वापस axis == ABS_MT_SLOT || input_is_mt_value(axis);
पूर्ण

bool input_mt_report_slot_state(काष्ठा input_dev *dev,
				अचिन्हित पूर्णांक tool_type, bool active);

अटल अंतरभूत व्योम input_mt_report_slot_inactive(काष्ठा input_dev *dev)
अणु
	input_mt_report_slot_state(dev, 0, false);
पूर्ण

व्योम input_mt_report_finger_count(काष्ठा input_dev *dev, पूर्णांक count);
व्योम input_mt_report_poपूर्णांकer_emulation(काष्ठा input_dev *dev, bool use_count);
व्योम input_mt_drop_unused(काष्ठा input_dev *dev);

व्योम input_mt_sync_frame(काष्ठा input_dev *dev);

/**
 * काष्ठा input_mt_pos - contact position
 * @x: horizontal coordinate
 * @y: vertical coordinate
 */
काष्ठा input_mt_pos अणु
	s16 x, y;
पूर्ण;

पूर्णांक input_mt_assign_slots(काष्ठा input_dev *dev, पूर्णांक *slots,
			  स्थिर काष्ठा input_mt_pos *pos, पूर्णांक num_pos,
			  पूर्णांक dmax);

पूर्णांक input_mt_get_slot_by_key(काष्ठा input_dev *dev, पूर्णांक key);

#पूर्ण_अगर
