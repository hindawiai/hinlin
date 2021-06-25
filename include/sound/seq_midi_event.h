<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __SOUND_SEQ_MIDI_EVENT_H
#घोषणा __SOUND_SEQ_MIDI_EVENT_H

/*
 *  MIDI byte <-> sequencer event coder
 *
 *  Copyright (C) 1998,99 Takashi Iwai <tiwai@suse.de>,
 *                        Jaroslav Kysela <perex@perex.cz>
 */

#समावेश <sound/asequencer.h>

#घोषणा MAX_MIDI_EVENT_BUF	256

/* midi status */
काष्ठा snd_midi_event अणु
	पूर्णांक qlen;		/* queue length */
	पूर्णांक पढ़ो;		/* अक्षरs पढ़ो */
	पूर्णांक type;		/* current event type */
	अचिन्हित अक्षर lastcmd;	/* last command (क्रम MIDI state handling) */
	अचिन्हित अक्षर nostat;	/* no state flag */
	पूर्णांक bufsize;		/* allocated buffer size */
	अचिन्हित अक्षर *buf;	/* input buffer */
	spinlock_t lock;
पूर्ण;

पूर्णांक snd_midi_event_new(पूर्णांक bufsize, काष्ठा snd_midi_event **rdev);
व्योम snd_midi_event_मुक्त(काष्ठा snd_midi_event *dev);
व्योम snd_midi_event_reset_encode(काष्ठा snd_midi_event *dev);
व्योम snd_midi_event_reset_decode(काष्ठा snd_midi_event *dev);
व्योम snd_midi_event_no_status(काष्ठा snd_midi_event *dev, पूर्णांक on);
bool snd_midi_event_encode_byte(काष्ठा snd_midi_event *dev, अचिन्हित अक्षर c,
				काष्ठा snd_seq_event *ev);
/* decode from event to bytes - वापस number of written bytes अगर success */
दीर्घ snd_midi_event_decode(काष्ठा snd_midi_event *dev, अचिन्हित अक्षर *buf, दीर्घ count,
			   काष्ठा snd_seq_event *ev);

#पूर्ण_अगर /* __SOUND_SEQ_MIDI_EVENT_H */
