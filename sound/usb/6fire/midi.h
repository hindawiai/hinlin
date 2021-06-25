<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Linux driver क्रम TerraTec DMX 6Fire USB
 *
 * Author:	Torsten Schenk <torsten.schenk@zoho.com>
 * Created:	Jan 01, 2011
 * Copyright:	(C) Torsten Schenk
 */

#अगर_अघोषित USB6FIRE_MIDI_H
#घोषणा USB6FIRE_MIDI_H

#समावेश "common.h"

काष्ठा midi_runसमय अणु
	काष्ठा sfire_chip *chip;
	काष्ठा snd_rawmidi *instance;

	काष्ठा snd_rawmidi_substream *in;
	अक्षर in_active;

	spinlock_t in_lock;
	spinlock_t out_lock;
	काष्ठा snd_rawmidi_substream *out;
	काष्ठा urb out_urb;
	u8 out_serial; /* serial number of out packet */
	u8 *out_buffer;
	पूर्णांक buffer_offset;

	व्योम (*in_received)(काष्ठा midi_runसमय *rt, u8 *data, पूर्णांक length);
पूर्ण;

पूर्णांक usb6fire_midi_init(काष्ठा sfire_chip *chip);
व्योम usb6fire_midi_पात(काष्ठा sfire_chip *chip);
व्योम usb6fire_midi_destroy(काष्ठा sfire_chip *chip);
#पूर्ण_अगर /* USB6FIRE_MIDI_H */

