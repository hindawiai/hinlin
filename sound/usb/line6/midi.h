<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Line 6 Linux USB driver
 *
 * Copyright (C) 2004-2010 Markus Grabner (grabner@icg.tugraz.at)
 */

#अगर_अघोषित MIDI_H
#घोषणा MIDI_H

#समावेश <sound/rawmidi.h>

#समावेश "midibuf.h"

#घोषणा MIDI_BUFFER_SIZE 1024

काष्ठा snd_line6_midi अणु
	/* Poपूर्णांकer back to the Line 6 driver data काष्ठाure */
	काष्ठा usb_line6 *line6;

	/* MIDI substream क्रम receiving (or शून्य अगर not active) */
	काष्ठा snd_rawmidi_substream *substream_receive;

	/* MIDI substream क्रम transmitting (or शून्य अगर not active) */
	काष्ठा snd_rawmidi_substream *substream_transmit;

	/* Number of currently active MIDI send URBs */
	पूर्णांक num_active_send_urbs;

	/* Spin lock to protect MIDI buffer handling */
	spinlock_t lock;

	/* Wait queue क्रम MIDI transmission */
	रुको_queue_head_t send_रुको;

	/* Buffer क्रम incoming MIDI stream */
	काष्ठा midi_buffer midibuf_in;

	/* Buffer क्रम outgoing MIDI stream */
	काष्ठा midi_buffer midibuf_out;
पूर्ण;

बाह्य पूर्णांक line6_init_midi(काष्ठा usb_line6 *line6);
बाह्य व्योम line6_midi_receive(काष्ठा usb_line6 *line6, अचिन्हित अक्षर *data,
			       पूर्णांक length);

#पूर्ण_अगर
